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
    if((engine.getDirPath() != "") && checkIncludeExcludeContradiction()){
        engine.setKeyword(ui->keyword->text().toStdString());
        engine.setFilters(userFilters);

        if((ui->en_regex->isChecked() == 1) && (engine.validateRegex() == 0)){
            ui->status->setText("Invalid RegEx!");
            return;
        }

        engine.search();

        if(engine.getStatus() == Status_Search_Completed){
            vector<tuple<string,string,string>> outputResult = engine.getResult();

            auto model = ui->table->model();
            ui->table->setRowCount(engine.getResult().size());

            for(int index = 0; index < engine.getResult().size(); index++){
                model->setData(model->index(index,0), QString::fromStdString(get<0>(outputResult[index])));
                model->setData(model->index(index,1), QString::fromStdString(get<1>(outputResult[index])));
                model->setData(model->index(index,2), QString::fromStdString(get<2>(outputResult[index])));

            }

            ui->status->setText("Search completed successfully");

        }else{
            ui->status->setText("Search not completed successfully");
        }

    }else{
        ui->status->setText("Invalid inputs!");
    }
}


void MainWindow::on_exc_headerfile_stateChanged(int arg1)
{
    if(ui->exc_headerfile->isChecked()){
        userFilters.exc_headerfile = 1;
    }else{
        userFilters.exc_headerfile = 0;
    }
}


void MainWindow::on_exc_cPlusPlus_stateChanged(int arg1)
{
    if(ui->exc_cPlusPlus->isChecked()){
        userFilters.exc_cPlusPlus= 1;
    }else{
        userFilters.exc_cPlusPlus = 0;
    }
}


void MainWindow::on_exc_python_stateChanged(int arg1)
{
    if(ui->exc_python->isChecked()){
        userFilters.exc_python= 1;
    }else{
        userFilters.exc_python= 0;
    }
}


void MainWindow::on_exc_txt_stateChanged(int arg1)
{
    if(ui->exc_txt->isChecked()){
        userFilters.exc_txt= 1;
    }else{
        userFilters.exc_txt= 0;
    }
}

bool MainWindow::checkIncludeExcludeContradiction()
{
    bool res = true;
    if(ui->headerfile->isChecked() && ui->exc_headerfile->isChecked()){
        res = false;

    }else if(ui->cPlusPlus->isChecked() && ui->exc_cPlusPlus->isChecked()){
        res = false;

    }else if(ui->python->isChecked() && ui->exc_python->isChecked()){
        res = false;

    }else if(ui->txt->isChecked() && ui->exc_txt->isChecked()){
        res = false;
    }

    return res;
}

void MainWindow::on_en_regex_stateChanged(int arg1)
{
    if(ui->en_regex->isChecked()){
        userFilters.regex_enabled = 1;
    }else{
        userFilters.regex_enabled = 0;
    }
}

