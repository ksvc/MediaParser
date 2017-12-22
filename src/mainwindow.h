#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class BaseBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void displayHex(unsigned char* pData, int len);
    void displayHexFromReader(class FileReader* reader, int start, int len);
    void setHighlight(int start, int len);
    void clearDisplay();
    BaseBox* getItemBox(QTreeWidgetItem* item);

private slots:
    void on_openButton_clicked();
    void on_structTree_itemClicked(QTreeWidgetItem * item, int column);

private:
    class FileReader* reader;
    class mp4Parser* parser;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
