#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphstruct.h"
#include <QMainWindow>
#include <QSettings>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btOpenSynced_clicked();
    void on_btOpenDesynced_clicked();
    void on_btAutosync_clicked();
    void on_btSave_clicked();
    void on_btSvg_clicked();

private:
    Ui::MainWindow *ui;
    QSettings _settings;
    uchar _openState;
    FileStruct _sync, _desync;
    GraphStruct _result;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    void openFile(const QString &fileName, FileStruct &obj);
    void drawGraph(GraphStruct &obj, const DesyncGroupList * const highligted = nullptr);
};

#endif // MAINWINDOW_H
