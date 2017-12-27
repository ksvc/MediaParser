#include "mainwindow.h"
#include <QMessageBox>
#include <qtextedit.h>
#include <qtreewidget.h>
#include <qtextcursor.h>
#include <qfiledialog.h>
#include <QtGlobal>
#include "mov/BaseBox.h"
#include "mov/Mp4Parser.h"
#include "Mp4Display.h"

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

#define MKTAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->reader = NULL;
    this->parser = NULL;
    ui->setupUi(this);
#ifdef Q_OS_DARWIN
    QFont font("SimSun",14,QFont::Normal);
    ui->hexView->setFont(font);
#endif

    ResetSampleInfo();

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    if(this->reader)
        delete this->reader;
    if(this->parser)
        delete this->parser;
    delete ui;
}

void MainWindow::ResetSampleInfo()
{
    bShowVideoSample = true;
    sampleCount = 0;
    curSample = 0;

    ui->lineEditSample->setText("0/0");
    ui->radioAudio->setChecked(false);
    ui->radioVideo->setChecked(true);
    ui->textEditSampleInfo->clear();
}

void MainWindow::on_openButton_clicked()
{
    QFileDialog *dlg = new QFileDialog(this);
    if (dlg->exec() == QFileDialog::Accepted)
    {
        QStringList files = dlg->selectedFiles();
        QString fileName = files.at(0);
        this->ui->filePathEdit->setText(fileName);

		if (parser != NULL)
		{
			delete parser;
		}
		if (reader != NULL)
		{
			delete reader;
		}

        this->reader = new FileReader();
        this->parser = new mp4Parser(reader);

        ResetSampleInfo();
        ui->tabWidget->setCurrentIndex(0);
        ui->hexView->clear();

        parser->Parse(fileName.toLocal8Bit().data());
        mp4Display display;
        display.Display(ui->structTree, ui->baseInfoTextEdit, parser);
        displayHexFromReader(reader, 0, 1024);


    }

}

char get_printable_char(unsigned char c)
{
    if(c >= 128 || c <=32)
        return '.';
    else
        return c;
}

void MainWindow::displayHexFromReader(class FileReader* reader, int start, int len)
{
    unsigned char* buffer = new unsigned char[len];
    reader->SetPos(start);
    reader->ReadBuffer((char*)buffer, len);
    this->displayHex(buffer, len);
    delete[] buffer;
    setHighlight(0, 0);
}

void MainWindow::displayHex(unsigned char* pData, int len)
{
    Q_ASSERT(pData && len >= 0);

	len = MIN(len, 4096);
    int rows = len / 16 + (len%16==0?0:1);
    int index = 0;
    for(int i=0;i<rows;i++)
    {
        QString str;
        QString str1;
        QString str2;
        int num = 16;
        if((i+1)*16 > len)
        {
            num = len - i*16;
        }
        for(int j=0;j<num;j++)
        {
            QString tmp;
            tmp.sprintf("%02X ", pData[index]);
            str1.append(tmp);
            tmp.sprintf("%c", get_printable_char(pData[index]));
            str2.append(tmp);
            index++;
        }
        if(num < 16)
        {
            for(int x=0;x<16-num;x++)
            {
                str1 += "   ";
            }
        }
        str = str1 + "    " + str2;
        ui->hexView->append(str);
    }
}

void MainWindow::setHighlight(int start, int len)
{
    QTextEdit* edit = this->ui->hexView;
    QTextCursor cur = edit->textCursor();

    int startTextPos = start * 3;
    int lenText = len * 3 - 1;

    cur.setPosition(startTextPos);
    cur.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, lenText);
    QTextEdit::ExtraSelection selection;
    selection.cursor = cur;
    QColor lineColor = QColor(Qt::yellow).lighter(160);
    selection.format.setBackground(lineColor);
    QList<QTextEdit::ExtraSelection> extraSelections;
    extraSelections.append(selection);
    edit->setExtraSelections(extraSelections);

    cur.clearSelection();
    cur.setPosition(startTextPos);
    edit->setTextCursor(cur);
}

void MainWindow::clearDisplay()
{
    QTreeWidget* tree = this->ui->structTree;
    tree->clear();
    this->ui->hexView->clear();
}


BaseBox* MainWindow::getItemBox(QTreeWidgetItem* item)
{
    BaseBox* box = NULL;
    QVariant value = item->data(0, Qt::UserRole);
    box = (BaseBox*)value.value<void *>();
    return box;
}

void MainWindow::on_structTree_itemClicked(QTreeWidgetItem * item, int column)
{
    ui->hexView->clear();
    BaseBox* box = getItemBox(item);
    if(box == NULL)
        return;

    ui->baseInfoTextEdit->setText(box->GetDescription().c_str());
    this->displayHexFromReader(reader, box->start_pos, box->size);
}

void MainWindow::on_radioVideo_clicked()
{
    this->bShowVideoSample = true;
    on_homeButton_clicked();
}

void MainWindow::on_radioAudio_clicked()
{
    this->bShowVideoSample = false;
    on_homeButton_clicked();
}

Stream* MainWindow::GetShowingStream()
{
    if(this->parser == NULL)
        return NULL;

    Stream* s = NULL;
    if(this->bShowVideoSample)
        s = this->parser->GetVideoStream();
    else
        s = this->parser->GetAudioStream();

    return s;
}


void MainWindow::ShowSample(Stream* s, int index)
{
    this->sampleCount = s->stsz_count;
    if(index > this->sampleCount)
        index = this->sampleCount;
    if(index <= 0)
        index = 1;

    this->curSample = index;
    char tmp[128];
    sprintf(tmp, "%d/%d", this->curSample, this->sampleCount);
    ui->lineEditSample->setText(tmp);

    this->ui->hexView->clear();
    int start = s->sample_position[index-1];
    int len = s->stsz_data[index-1];
    this->displayHexFromReader(this->reader, start, len);

    char sampleInfo[1024];
    sprintf(sampleInfo, "Position = %d\nLength = %d (0x%02X)\n", start, len, len);
    ui->textEditSampleInfo->setText(sampleInfo);
}

void MainWindow::on_homeButton_clicked()
{
    Stream* s = GetShowingStream();
    if(s == NULL)
        return;

    ShowSample(s, 1);
}

void MainWindow::on_endButton_clicked()
{
    Stream* s = GetShowingStream();
    if(s == NULL)
        return;

    ShowSample(s, s->stsz_count);
}

void MainWindow::on_prevButton_clicked()
{
    Stream* s = GetShowingStream();
    if(s == NULL)
        return;

    ShowSample(s, this->curSample-1);
}

void MainWindow::on_nextButton_clicked()
{
    Stream* s = GetShowingStream();
    if(s == NULL)
        return;

    ShowSample(s, this->curSample+1);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1 && curSample == 0)
    {
        on_homeButton_clicked();
    }
}

void MainWindow::on_lineEditSample_returnPressed()
{
    Stream* s = GetShowingStream();
    if(s == NULL)
        return;

    QString strSampleIndex = ui->lineEditSample->text();
    QString strIndex = strSampleIndex;
    if(strSampleIndex.contains('/'))
    {
        int left = strSampleIndex.indexOf('/');
        strIndex = strSampleIndex.left(left);
    }
    int index = strIndex.toInt();
    if(index <= 0)
        index = 1;
    else if(index > this->sampleCount)
        index = this->sampleCount;

    ShowSample(s, index);
}
