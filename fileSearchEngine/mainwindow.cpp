#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dirBtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"));
    if(dir.isEmpty()){
        ui->status->setText("Choose valid directory!");
        ui->dir->setText("N/A");
    }else{
        engine.setDirPath(dir.toStdString());
        ui->dir->setText(dir);
        ui->status->setText("");
    }
}


void MainWindow::on_dirName_stateChanged(int arg1)
{
    if(ui->dirName->isChecked()){
        userFilters.directoryName = 1;
    }else{
        userFilters.directoryName = 0;
    }
}


void MainWindow::on_fileName_stateChanged(int arg1)
{
    if(ui->fileName->isChecked()){
        userFilters.fileName = 1;
    }else{
        userFilters.fileName = 0;
    }
}


void MainWindow::on_infile_stateChanged(int arg1)
{
    if(ui->infile->isChecked()){
        userFilters.infile = 1;
    }else{
        userFilters.infile = 0;
    }
}


void MainWindow::on_caseSensitive_stateChanged(int arg1)
{
    if(ui->caseSensitive->isChecked()){
        userFilters.caseSensitive = 1;
    }else{
        userFilters.caseSensitive = 0;
    }
}


void MainWindow::on_recursive_stateChanged(int arg1)
{
    if(ui->recursive->isChecked()){
        userFilters.recursive = 1;
    }else{
        userFilters.recursive = 0;
    }
}


void MainWindow::on_headerfile_stateChanged(int arg1)
{
    if(ui->headerfile->isChecked()){
        userFilters.headerfile = 1;
    }else{
        userFilters.headerfile = 0;
    }
}


void MainWindow::on_cPlusPlus_stateChanged(int arg1)
{
    if(ui->cPlusPlus->isChecked()){
        userFilters.cPlusPlus = 1;
    }else{
        userFilters.cPlusPlus = 0;
    }
}


void MainWindow::on_python_stateChanged(int arg1)
{
    if(ui->python->isChecked()){
        userFilters.python = 1;
    }else{
        userFilters.python = 0;
    }
}


void MainWindow::on_txt_stateChanged(int arg1)
{
    if(ui->txt->isChecked()){
        userFilters.txt = 1;
    }else{
        userFilters.txt = 0;
    }
}


void MainWindow::on_searchBtn_clicked()
{
    if(engine.getDirPath() != ""){
        engine.setKeyword(ui->keyword->text().toStdString());
        engine.setFilters(userFilters);

        engine.search();

        if(engine.getStatus() == Status_Search_Completed){
            vector<pair<string,string>> outputResult = engine.getResult();

            auto model = ui->table->model();
            ui->table->setRowCount(engine.getResult().size());

            for(int index = 0; index < engine.getResult().size(); index++){
                model->setData(model->index(index,0), QString::fromStdString(outputResult[index].first));
                model->setData(model->index(index,1), QString::fromStdString(outputResult[index].second));
            }

            ui->status->setText("Search completed successfully");

        }else{
            ui->status->setText("Search not completed successfully");
        }
    }
}

