/*******************************************************************************
 * Re_Sync:
 * Synchronize subtitles with the video using the timing of other subtitles.
 *
 * This file is part of Re_Sync Next.
 *
 * Copyright (C) 2011-2013  Andrey Efremov <duxus@yandex.ru>
 *
 * Re_Sync is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Re_Sync is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Re_Sync.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Re_Sync");
    a.setApplicationVersion("2.0");
    a.setOrganizationName("Unlimited Web Works");
    a.setWindowIcon(QIcon(":/main.ico"));

    MainWindow w;
    w.show();
    
    return a.exec();
}
