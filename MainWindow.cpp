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



#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QDialog(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("logo128.png"));

    connect(ui->buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonSelect_clicked()
{
    QString newPath;
    newPath = QFileDialog::getExistingDirectory(this, "Select a folder");

    if(newPath.isEmpty())
    {
        if(m_path.isEmpty())
            return;
    }
    else
        m_path = newPath;

    ui->lineEditPath->setText(m_path);
    ui->textEdit->clear();

    ui->checkC->setChecked(false);
    ui->checkCpp->setChecked(false);
    ui->checkCss->setChecked(false);
    ui->checkH->setChecked(false);
    ui->checkHtml->setChecked(false);
    ui->checkPhp->setChecked(false);
    ui->checkUi->setChecked(false);

    ui->groupBox->setEnabled(true);
    ui->textEdit->setEnabled(true);
    ui->checkSub->setEnabled(true);
}


void MainWindow::on_checkC_stateChanged(int state)
{
    m_cFiles = 0;
    m_cLines = 0;

    if(state)
        getFiles(C);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::on_checkCpp_stateChanged(int state)
{
    m_cppFiles = 0;
    m_cppLines = 0;

    if(state)
        getFiles(CPP);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::on_checkH_stateChanged(int state)
{
    m_hFiles = 0;
    m_hLines = 0;

    if(state)
        getFiles(H);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::on_checkUi_stateChanged(int state)
{
    m_uiFiles = 0;

    if(state)
        getFiles(UI);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::on_checkHtml_stateChanged(int state)
{
    m_htmlFiles = 0;
    m_htmlLines = 0;

    if(state)
        getFiles(HTML);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::on_checkCss_stateChanged(int state)
{
    m_cssFiles = 0;
    m_cssLines = 0;

    if(state)
        getFiles(CSS);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::on_checkPhp_stateChanged(int state)
{
    m_phpFiles = 0;
    m_phpLines = 0;

    if(state)
        getFiles(PHP);

    updateStats();
    ui->checkSub->setEnabled(false);
}


void MainWindow::getFiles(TYPES type)
{
    getCountFile(type, m_path);

    if(ui->checkSub->isChecked())
    {
        QDirIterator* dirIt = new QDirIterator(m_path, QDir::Dirs|QDir::NoDot|QDir::NoDotAndDotDot|QDir::NoDotDot, QDirIterator::Subdirectories);
        while(dirIt->hasNext())
        {
            getCountFile(type, dirIt->next());
        }
    }
}


void MainWindow::getCountFile(TYPES type, QString path)
{
    QStringList filters;
    switch(type)
    {
        case C:
            filters << "*.c";
            break;
        case CPP:
            filters << "*.cpp";
            break;
        case H:
            filters << "*.h";
            break;
        case UI:
            filters << "*.ui";
            break;
        case HTML:
            filters << "*.html";
            break;
        case CSS:
            filters << "*.css";
            break;
        case PHP:
            filters << "*.php";
            break;
    }

    QDir* dir = new QDir(path);
    QStringList files = dir->entryList(filters);

    QStringList::Iterator it = files.begin();
    while(it != files.end())
    {
        switch(type)
        {
            case C:
                m_cFiles++;
                getCountLines(C, path + "/" + *it);
                break;
            case CPP:
                m_cppFiles++;
                getCountLines(CPP, path + "/" + *it);
                break;
            case H:
                m_hFiles++;
                getCountLines(H, path + "/" + *it);
                break;
            case UI:
                m_uiFiles++;
                break;
            case HTML:
                m_htmlFiles++;
                getCountLines(HTML, path + "/" + *it);
                break;
            case CSS:
                m_cssFiles++;
                getCountLines(CSS, path + "/" + *it);
                break;
            case PHP:
                m_phpFiles++;
                getCountLines(PHP, path + "/" + *it);
                break;
        }
        ++it;
    }
}


void MainWindow::getCountLines(TYPES type, QString path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            in.readLine();
            switch(type)
            {
                case C:
                    m_cLines++;
                    break;
                case CPP:
                    m_cppLines++;
                    break;
                case H:
                    m_hLines++;
                    break;
                case HTML:
                    m_htmlLines++;
                    break;
                case CSS:
                    m_cssLines++;
                    break;
                case PHP:
                    m_phpLines++;
                    break;
                default:
                    break;
            }
        }
    }
}


void MainWindow::updateStats()
{
    bool empty = true;

    ui->textEdit->clear();

    if(ui->checkC->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_cFiles, m_cLines, FILES_LINES, "C"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_cFiles, m_cLines, FILES_LINES, "C"));
    }
    if(ui->checkCpp->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_cppFiles, m_cppLines, FILES_LINES, "CPP"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_cppFiles, m_cppLines, FILES_LINES, "CPP"));
    }
    if(ui->checkH->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_hFiles, m_hLines, FILES_LINES, "H"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_hFiles, m_hLines, FILES_LINES, "H"));
    }
    if(ui->checkUi->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_uiFiles, 0, FILES, "Qt User Interface"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_uiFiles, 0, FILES, "Qt User Interface"));
    }
    if(ui->checkHtml->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_htmlFiles, m_htmlLines, FILES_LINES, "HTML"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_htmlFiles, m_htmlLines, FILES_LINES, "HTML"));
    }
    if(ui->checkCss->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_cssFiles, m_cssLines, FILES_LINES, "CSS"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_cssFiles, m_cssLines, FILES_LINES, "CSS"));
    }
    if(ui->checkPhp->isChecked())
    {
        if(empty)
        {
            ui->textEdit->setText(getPhrase(m_phpFiles, m_phpLines, FILES_LINES, "PHP"));
            empty = false;
        }
        else
            ui->textEdit->setText(ui->textEdit->toHtml() + getPhrase(m_phpFiles, m_phpLines, FILES_LINES, "PHP"));
    }
}


QString MainWindow::getPhrase(int nbFiles, int nbLines, PHRASE type, QString fileType)
{
    QString phrase;

    if(nbFiles == 0)
        phrase = "0 " + fileType + " file<br />";
    else if(nbFiles == 1)
    {
        phrase = "1 " + fileType + " file<br />";
        if(type == FILES_LINES)
        {
            if(nbLines <= 1)
                phrase += QString::number(nbLines) + " line<br />";
            else
                phrase += QString::number(nbLines) + " lines<br />";
        }
    }
    else
    {
        phrase = QString::number(nbFiles) + " " + fileType + " files<br />";
        if(type == FILES_LINES)
        {
            if(nbLines <= 1)
                phrase += QString::number(nbLines) + " line<br />";
            else
                phrase += QString::number(nbLines) + " lines<br />";
        }
    }

    return phrase;
}


void MainWindow::on_buttonAbout_clicked()
{
    AboutDialog* about = new AboutDialog(this);
    about->show();
}



