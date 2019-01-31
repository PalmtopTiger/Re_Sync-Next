/*
 * This file is part of Re_Sync Next.
 * Copyright (C) 2011-2019  Andrey Efremov <duxus@yandex.ru>
 *
 * Re_Sync Next is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Re_Sync Next is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Re_Sync Next.  If not, see <https://www.gnu.org/licenses/>.
 */

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
