#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <qtextedit.h>
#include <qtreewidget.h>
#include <qtextcursor.h>
#include <qfiledialog.h>
#include <QtGlobal>
#include "BaseBox.h"
#include "Mp4Parser.h"
#include "Mp4Display.h"

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

#define MKTAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
//    QFileDialog *dlg = new QFileDialog(this);
//    if (dlg->exec() == QFileDialog::Accepted)
//    {
//        QStringList files = dlg->selectedFiles();
//        QString fileName = files.at(0);
//        this->ui->filePathEdit->setText(fileName);
//        QMessageBox::information(this, "dd", fileName);
//    }

    mp4Parser parser;
    parser.Parse("/Users/mayudong/Movies/1.mp4");
    mp4Display display;
    display.Display(ui->structTree, ui->hexView, &parser);
}

QString convert(unsigned char* pData, int len)
{
    QString strResult;
    for (int i = 0; i < len; i++)
    {
        QString tmp;
        tmp.sprintf("%02X ", pData[i]);
        strResult.append(tmp);
    }
    return strResult;
}

void MainWindow::displayHex(unsigned char* pData, int& len)
{
    Q_ASSERT(pData && len >= 0);

    len = MIN(len, 1024);
    QString str = convert(pData, len);
    this->ui->hexView->setText(str);
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
