/**********************************************************************
LiCount, a software to count lines and files in your projects !
    Copyright (C) 2013  Philippe SWARTVAGHER

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/


#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>


#include "MainWindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Select the language:
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);


    MainWindow* mainWindow = new MainWindow;
    mainWindow->show();


    return app.exec();
}
