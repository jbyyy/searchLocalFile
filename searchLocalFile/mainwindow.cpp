#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDebug>
#include <QFileDialog>

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

void MainWindow::findAllFiles(QString folder)
{
    //qDebug() << "读取路径" << folder;
    //添加当前路径下所有的文件
    QStringList Files =findFile(folder);
    for(int i=0; i<Files.size(); i++)
    {
        FolderPath.append(QPair<QString,QString>(folder,Files.at(i)));
    }

    // 获取所有文件夹名
    QStringList Folder = findFolder(folder);        //根目录下的子文件夹
    //遍历子文件夹 获取里面的文件和文件夹
    for (int i = 0; i < Folder.size(); ++i)
    {
        findAllFiles(folder+"/"+Folder[i]);
    }
}

QStringList MainWindow::findFolder(QString folder)
{
    // 获取所有文件夹名
    QDir dir(folder);
    folder = dir.fromNativeSeparators(folder);//  "\\"转为"/"
    QStringList allFolder = QStringList("");
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    allFolder = dir.entryList();
    return  allFolder;
}

QStringList MainWindow::findFile(QString path)
{
    // 获取所有文件夹名
    QDir dir(path);
    path = dir.fromNativeSeparators(path);//  "\\"转为"/"
    QStringList allFile = QStringList("");
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    allFile = dir.entryList();
    return  allFile;
}
//查找当前路径下的文件
void MainWindow::on_pushButton_findFile_clicked()
{
    QString FileFolder = QFileDialog::getExistingDirectory( this, "choose Directory",  "/");
    if(!FileFolder.isEmpty())
    {
        QStringList files = findFile(FileFolder);
        for(int i=0; i<files.size(); i++)
            ui->textEdit->append(QString("文件名:%1").arg(files.at(i)));
    }
}
//查找当前路径下的子目录
void MainWindow::on_pushButton_fileDir_clicked()
{
    QString FileFolder = QFileDialog::getExistingDirectory( this, "choose Directory",  "/");
    if(!FileFolder.isEmpty())
    {
        QStringList folders = findFolder(FileFolder);
        for(int i=0; i<folders.size(); i++)
            ui->textEdit->append(QString("子目录:%1").arg(folders.at(i)));
    }
}
//递归查找当前路径下所有文件
void MainWindow::on_pushButton_findAllFiles_clicked()
{
    FolderPath.clear();
    QString FileFolder = QFileDialog::getExistingDirectory( this, "choose Directory",  "/");
    if(!FileFolder.isEmpty())
        findAllFiles(FileFolder);
    for(int i=0; i<FolderPath.size(); i++)
    {
        ui->textEdit->append(QString("文件名:%1\n文件路径:%2\n").arg(FolderPath.at(i).second).arg(FolderPath.at(i).first));
    }
}
//清空
void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
}

