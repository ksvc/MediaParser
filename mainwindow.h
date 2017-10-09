#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void displayHex(unsigned char* pData, int& len);
    void setHighlight(int start, int len);
    void clearDisplay();

private slots:
    void on_openButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
