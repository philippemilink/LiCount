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



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QDirIterator>

#include "AboutDialog.h"

using namespace std;

namespace Ui
{
    class MainWindow;
}

enum TYPES
{
    C,
    CPP,
    H,
    UI,
    PHP,
    HTML,
    CSS
};

enum PHRASE
{
    FILES,
    FILES_LINES
};

class MainWindow : public QDialog
{
    Q_OBJECT
    
    public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    private slots:
    void on_buttonSelect_clicked();
    void on_checkC_stateChanged(int state);
    void on_checkCpp_stateChanged(int state);
    void on_checkH_stateChanged(int state);
    void on_checkUi_stateChanged(int state);
    void on_checkHtml_stateChanged(int state);
    void on_checkCss_stateChanged(int state);
    void on_checkPhp_stateChanged(int state);
    void on_buttonAbout_clicked();

    
    private:
    void getFiles(TYPES type);
    void getCountFile(TYPES type, QString path);
    void getCountLines(TYPES type, QString path);
    void updateStats();
    QString getPhrase(int nbFiles, int nbLines, PHRASE type, QString fileType);

    Ui::MainWindow *ui;
    QString m_path;

    int m_cFiles;
    int m_cLines;
    int m_cppFiles;
    int m_cppLines;
    int m_hFiles;
    int m_hLines;
    int m_uiFiles;
    int m_htmlFiles;
    int m_htmlLines;
    int m_cssFiles;
    int m_cssLines;
    int m_phpFiles;
    int m_phpLines;
};

#endif // MAINWINDOW_H
