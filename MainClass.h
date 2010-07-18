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

#ifndef HEADER_MAINCLASS
#define HEADER_MAINCLASS

#include <windows.h>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QInputDialog>
#include <QFileIconProvider>

#include "ui_mainform.h"
#include "Registry.h"
#include "StartupManager.h"

class MainClass : public QWidget, private Ui::form
{
    Q_OBJECT

public:
    MainClass(QWidget *parent = 0);
    void Restricitions();


private slots:
    void Scan();
    void Remove();
    void Check();
    void RefreshSetting();
    void AutoScanSetting();
    void AutoRemoveSetting();
    //void GoDonate();
    void ButtonApp(int TabsIndex);
    //startup slots..
    void StartUpRefresh();
    void StartUpEdit();
    void StartUpDelete();
    void StartUpAdd();

private:
    StartupMananger *StarMan;
    RegistryFixer *Reg ;
    QTimer *AutoScanTimer ;
    QTimer *AutoRemoveTimer ;
    int CheckState;
    bool ShowMsg;
    bool AutoRemoveEnablde;

};


#endif

