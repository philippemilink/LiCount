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



#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("logo128.png"));

    ui->labelIcon->setPixmap(QPixmap("logo-text.png"));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
