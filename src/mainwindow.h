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

    void ResetSampleInfo();
    void ShowSample(struct Stream* s, int index);
    struct Stream* GetShowingStream();

private slots:
    void on_openButton_clicked();
    void on_structTree_itemClicked(QTreeWidgetItem * item, int column);

    void on_homeButton_clicked();
    void on_endButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();

    void on_radioVideo_clicked();
    void on_radioAudio_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    class FileReader* reader;
    class mp4Parser* parser;

    bool bShowVideoSample;

    int sampleCount;
    int curSample;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
