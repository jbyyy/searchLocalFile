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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList findFile(QString path);
    QStringList findFolder(QString folder);
    void findAllFiles(QString folder);
private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_findFile_clicked();

    void on_pushButton_fileDir_clicked();

    void on_pushButton_findAllFiles_clicked();

private:
    Ui::MainWindow *ui;
    QList<QPair<QString,QString>> FolderPath;       //不包含根目录的文件夹位置  文件位置
};

#endif // MAINWINDOW_H
