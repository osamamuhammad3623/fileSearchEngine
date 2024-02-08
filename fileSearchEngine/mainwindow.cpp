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

static vector<string> processExcludedExtensions(QString userInput){
    vector<string> result{};

    userInput.replace(" ", "");
    QStringList extensions  = userInput.split(',');

    for(auto &ext : extensions){
        result.push_back(ext.toStdString());
    }

    return result;
}

void MainWindow::on_searchBtn_clicked()
{
    if((engine.getDirPath() != "") ){
        engine.setKeyword(ui->keyword->text().toStdString());

        // get user input for excluded extensions
        QString userExcludedExt = ui->excludeExtensions->text();

        // process the user input and convert it to vector<string>
        userFilters.excludedExtensions = processExcludedExtensions(userExcludedExt);

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


void MainWindow::on_en_regex_stateChanged(int arg1)
{
    if(ui->en_regex->isChecked()){
        userFilters.regex_enabled = 1;
    }else{
        userFilters.regex_enabled = 0;
    }
}

