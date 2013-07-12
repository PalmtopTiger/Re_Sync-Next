#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logic.h"
#include <QMainWindow>
#include <QGraphicsItem>


class GraphStruct
{
public:
    GraphStruct() :
        position(0u),
        connected(false),
        graph(NULL)
    {}

    uint position;
    bool connected;
    QString title;
    QColor borderColor;
    QColor bgColor;
    QColor hlColor;

    EventGroupList groups;
    QList<QGraphicsItem *> items;
    QGraphicsItemGroup *graph;

    void clear()
    {
        if (NULL != this->graph)
        {
            foreach (QGraphicsItem *item, this->items)
            {
                this->graph->removeFromGroup(item);
                delete item;
            }
            this->items.clear();

            delete this->graph;
            this->graph = NULL;
        }

        this->groups.clear();
    }
};

class FileStruct : public GraphStruct
{
public:
    FileStruct() :
        scriptType(Script::SCR_UNKNOWN)
    {}

    QString fileName;
    Script::Script script;
    Script::ScriptType scriptType;

    void clear()
    {
        dynamic_cast<GraphStruct *>(this)->clear();

        this->script.clear();
        this->fileName.clear();
        scriptType = Script::SCR_UNKNOWN;
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btOpenSynced_clicked();
    void on_btOpenDesynced_clicked();
    void on_btAutosync_clicked();
    void on_btSave_clicked();
    void on_btSvg_clicked();

private:
    Ui::MainWindow *ui;
    uchar _openState;
    FileStruct _sync, _desync;
    GraphStruct _result;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    void openFile(const QString &fileName, FileStruct &obj);
    void drawGraph(GraphStruct &obj, const DesyncGroupList * const highligted = NULL);
};

#endif // MAINWINDOW_H