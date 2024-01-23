#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "fileSearchEngine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dirBtn_clicked();

    void on_dirName_stateChanged(int arg1);

    void on_fileName_stateChanged(int arg1);

    void on_infile_stateChanged(int arg1);

    void on_caseSensitive_stateChanged(int arg1);

    void on_recursive_stateChanged(int arg1);

    void on_headerfile_stateChanged(int arg1);

    void on_cPlusPlus_stateChanged(int arg1);

    void on_python_stateChanged(int arg1);

    void on_txt_stateChanged(int arg1);

    void on_searchBtn_clicked();

private:
    Ui::MainWindow *ui;
    FileSearchEngine engine;
    EngineSearchFilters userFilters;
};
#endif // MAINWINDOW_H
