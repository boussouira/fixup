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

#include "Registry.h"

RegistryFixer::RegistryFixer()
{
    this->par = NULL;
    TmpShowMsg = true;
    TmpAutoRemoveEnablde = false;
    TmpShowRestrictionsOnly = false;
    DoScan();
}

RegistryFixer::RegistryFixer(QWidget *p)
{
    this->par = p;
    TmpShowMsg = true;
    TmpAutoRemoveEnablde = false;
    TmpShowRestrictionsOnly = false;
    DoScan();
}

void RegistryFixer::Do(char *path, char *name ,QCheckBox *chekO, DWORD RepValue )
{
    if (State == 1) {    // Scan for restrictions

        int founded = 0 ;
        DWORD value;

        RegOpenKeyExA(HKEY_LOCAL_MACHINE, path , 0, KEY_ALL_ACCESS, &h_HKLM);
        RegRep = RegQueryValueExA(h_HKLM, name, 0, &dwType, (LPBYTE)&value, &dwSize);
        if (RegRep == ERROR_SUCCESS) {
            if (value != RepValue) {
                founded++ ;
            }
        }
        RegOpenKeyExA(HKEY_CURRENT_USER, path , 0, KEY_ALL_ACCESS, &h_HKCU);
        RegRep = RegQueryValueExA(h_HKCU, name, 0, &dwType, (LPBYTE)&value, &dwSize);
        if (RegRep == ERROR_SUCCESS) {
            if (value != RepValue) {
                founded++ ;
            }
        }
        RegCloseKey(h_HKLM);
        RegCloseKey(h_HKCU);

        ColorChekO(chekO, founded);

    }
    else if (State == 2) { // Remove Resrictions

        if (chekO->isChecked() || (chekO->isEnabled() && TmpAutoRemoveEnablde)) {

            int founded = 0 ;
            DWORD value ;

            RegOpenKeyExA(HKEY_LOCAL_MACHINE, path , 0, KEY_ALL_ACCESS, &h_HKLM);
            RegRep = RegQueryValueExA(h_HKLM, name, 0, &dwType, (LPBYTE)&value, &dwSize);
            if ((RegRep == ERROR_SUCCESS) && (value != RepValue)) {
                RegRep = RegSetValueExA(h_HKLM, name, 0, REG_DWORD, (CONST BYTE*)&RepValue, sizeof(DWORD));
                if (RegRep == ERROR_SUCCESS) {
                    founded++ ;
                    if (TmpShowMsg) {
                        TmpAlertMsg.append(QString::fromUtf8("<span style=\"color:green\">%1</span> - For All Users<br />").arg(chekO->text()));
                    }
                }
            }

            RegOpenKeyExA(HKEY_CURRENT_USER, path , 0, KEY_ALL_ACCESS, &h_HKCU);
            RegRep = RegQueryValueExA(h_HKCU, name, 0, &dwType, (LPBYTE)&value, &dwSize);
            if ((RegRep == ERROR_SUCCESS) && (value != RepValue)) {
                RegRep = RegSetValueExA(h_HKCU, name, 0, REG_DWORD, (CONST BYTE*)&RepValue, sizeof(DWORD));
                if (RegRep == ERROR_SUCCESS) {
                    founded++ ;
                    if (TmpShowMsg) {
                        TmpAlertMsg.append(QString::fromUtf8("<span style=\"color:green\">%1</span> - For Current User<br />").arg(chekO->text()));
                    }
                }
            }
            RegCloseKey(h_HKLM);
            RegCloseKey(h_HKCU);

            ColorChekO(chekO, founded);

        }

    }
    else if (State == 3) { //check all

        chekO->setChecked(chekO->isEnabled());
    }
    else if (State == 4) { //Uncheck all
        if (chekO->isEnabled())
            chekO->setChecked(false);
    }
}

void RegistryFixer::UpDateSetting(bool TSRO, bool TARE, bool TSM)
{
    TmpShowRestrictionsOnly = TSRO ;
    TmpShowMsg = TSM ;
    TmpAutoRemoveEnablde = TARE;
}

void RegistryFixer::ShowCofirmingMsg()
{
    if (TmpShowMsg) {
        if (TmpAlertMsg.count() != 0) {

            QMessageBox::information(par ,"FixUp Restrictions" ,
                                     QString("The following restrictions :<br /><br />") + TmpAlertMsg + QString("<br />was successful removed.<br />You may need to restart your system."));
        }
        else {
            QMessageBox::warning(par ,"FixUp Restrictions","You havn't choose any restriction to remove !");
        }
    }
    TmpAlertMsg.clear();
}

void RegistryFixer::ColorChekO(QCheckBox *TmpchekO, int found)
{
    if (found == 0) {

        if (TmpShowRestrictionsOnly) {
            TmpchekO->hide();
        }
        else {
            TmpchekO->show();
        }
        if (!TmpchekO->isEnabled() && !TmpchekO->isChecked()) {
            return ;
        }

        TmpchekO->setEnabled(false);
        TmpchekO->setChecked(false);
        TmpchekO->setStyleSheet(QString::fromUtf8("color:rgb(135, 135, 135);"));
    }
    else {
        TmpchekO->show();
        TmpchekO->setEnabled(true);
        TmpchekO->setStyleSheet(QString::fromUtf8("color:red;"));
    }
}

void RegistryFixer::DoScan()
{
    State = 1;
}

void RegistryFixer::DoRemove()
{
    State = 2;
}

void RegistryFixer::DoCheckAll()
{
    State = 3;
}

void RegistryFixer::DoUnCheckAll()
{
    State = 4;
}


