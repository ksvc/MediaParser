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
}

MainWindow::~MainWindow()
{
    if(this->reader)
        delete this->reader;
    if(this->parser)
        delete this->parser;
    delete ui;
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
