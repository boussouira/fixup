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

#ifndef HEADER_REGISTRY
#define HEADER_REGISTRY

#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QCheckBox>
#include <windows.h>
#include <QWidget>

class RegistryFixer
{
public:
    RegistryFixer();
    RegistryFixer(QWidget *p);
    void Do(char *path, char *name ,QCheckBox *chekO, DWORD RepValue = 0);
    void UpDateSetting(bool TSRO, bool TARE, bool TSM);
    void ShowCofirmingMsg();
    void DoScan();
    void DoRemove();
    void DoCheckAll();
    void DoUnCheckAll();

private:
    void ColorChekO(QCheckBox *chekO, int found);

private:
    QWidget *par;
    int State;
    int RegRep;
    bool TmpShowMsg;
    bool TmpAutoRemoveEnablde;
    bool TmpShowRestrictionsOnly;
    HKEY h_HKCU;
    HKEY h_HKLM;
    DWORD dwSize ;
    DWORD dwType ;
    QString TmpAlertMsg;

};

#endif

