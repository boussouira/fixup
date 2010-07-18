/**
* Copyright (C) 2009 FixUp Team
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* butWITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef STARTUPMANAGERINPUT_H
#define STARTUPMANAGERINPUT_H

#include <windows.h>
#include <QtGui>

class QWidget;
class QDialog;
class QVariant;
class QAction;
class QApplication;
class QButtonGroup;
class QFormLayout;
class QHeaderView;
class QLabel;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QMessageBox;
class QComboBox;
class QGridLayout;
class QFileDialog;
class QDir;
class QSpacerItem;
class QMessageBox;


class StartupManagerInput : public QDialog
{
    Q_OBJECT

public:
    StartupManagerInput(QWidget *p, QString *na, QString *va, QString *sect);
    QString GetCurrentUserName();
    void SetComboText(QString *qtxt);
    void GetComboText(QString *qtxt);
public slots:
    void OKPushx();
    void BrowseFiles();

private:

    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    // QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QComboBox *combobox;
    QWidget *parentx;
    QString *TmpName;
    QString *TmpValue;
    QString *TmpSect;
};

#endif // STARTUPMANAGERINPUT_H
