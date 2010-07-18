#include "StartupManager.h"
#include "StartupManagerInput.h"
#define FIXUP_VERSION "0.1"
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

using namespace std;

StartupMananger::StartupMananger(QWidget *p, QTreeWidget *TreeW)
        : par(p), TreeWidget(TreeW)
{
    this->par = p;
    this->TreeWidget = TreeW;
}

void StartupMananger::LookAt(HKEY RootKey, char *PathKey, char *KeySection) {
    HKEY hKey;
    if ( RegOpenKeyExA ( RootKey, PathKey, 0, KEY_READ, &hKey)== ERROR_SUCCESS) {
        TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
        DWORD    cchClassName = MAX_PATH;  // size of class string
        DWORD    cSubKeys=0;               // number of subkeys
        DWORD    cbMaxSubKey;              // longest subkey size
        DWORD    cchMaxClass;              // longest class string
        DWORD    cValues;              // number of values for key
        DWORD    cchMaxValue;          // longest value name
        DWORD    cbMaxValueData;       // longest value data
        DWORD    cbSecurityDescriptor; // size of security descriptor
        FILETIME ftLastWriteTime;      // last write time
        DWORD dwSize = 256;
        DWORD i, retCode;

        char nomd[256];
        char  achValue[MAX_VALUE_NAME];
        DWORD cchValue = MAX_VALUE_NAME;
        long ec;


        // Get the class name and the value count.
        retCode = RegQueryInfoKey(
                      hKey,                    // key handle
                      achClass,                // buffer for class name
                      &cchClassName,           // size of class string
                      NULL,                    // reserved
                      &cSubKeys,               // number of subkeys
                      &cbMaxSubKey,            // longest subkey size
                      &cchMaxClass,            // longest class string
                      &cValues,                // number of values for this key
                      &cchMaxValue,            // longest value name
                      &cbMaxValueData,         // longest value data
                      &cbSecurityDescriptor,   // security descriptor
                      &ftLastWriteTime);       // last write time

        // Enumerate the key values.

        if (cValues)
        {
            this->TotalFound += (int)cValues ;
            for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
            {
                cchValue = MAX_VALUE_NAME;
                achValue[0] = '\0';
                retCode = RegEnumValueA(hKey, i, achValue, &cchValue,NULL, NULL,
                                        NULL, NULL);

                if (retCode == ERROR_SUCCESS )
                {
                    dwSize = sizeof(nomd); // Very important to fix ERROR_MORE_DATA error..
                    ec = RegQueryValueExA(hKey, achValue, 0, 0, (BYTE*)nomd, &dwSize);
                    if (ec == ERROR_SUCCESS) {
                        QTreeWidgetItem *item = new QTreeWidgetItem;

                        QString FilePath(OnlyPath(QString(nomd)));
                        QFileInfo FileInfo(FilePath);
                        item->setText(0, QString(achValue));
                        item->setText(1, QString(KeySection));
                        if (FileInfo.exists()) {
                            item->setText(2, QString(nomd));
                            item->setIcon(0, test.icon(FileInfo));
                        }
                        else {
                            item->setText(2, QString("File not found: %1").arg(nomd));
                            item->setIcon(0, QIcon(":/Icons/NOTFOUND.png"));
                        }

                        this->TreeWidget->addTopLevelItem(item);
                    }

                }
            }
        }
    }

    RegCloseKey(hKey);
}

QString StartupMananger::OnlyPath(QString s) {

    QString f;
    QRegExp rxlen("(.:(?:[\\\\][^\\\\]+)+[.][^ ]+)+");
    s.remove("\"");
    rxlen.indexIn(s);
    f = rxlen.cap(1);

    return f ;
}

QString StartupMananger::GetSelectedColumnText(int c) {
    QList<QTreeWidgetItem*> SList;

    if (this->TreeWidget->selectedItems().count() <=0) {
        return QString("");
    }
    SList = this->TreeWidget->selectedItems() ;
    if (c == 2) {
        return SList[0]->text(c).remove(QString("File not found: "));
    }
    return SList[0]->text(c);
}

void StartupMananger::QuickScan() {
    this->TotalFound = 0;
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run",   "Registry\\All Users\\Policies");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce",           "Registry\\All Users\\Run Services Once");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices",               "Registry\\All Users\\Run Services");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx",                 "Registry\\All Users\\Run Once Ex");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup",            "Registry\\All Users\\Run Once (Setup)");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce",                   "Registry\\All Users\\Run Once");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunEx",                     "Registry\\All Users\\Run Ex");
    this->LookAt(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",                       "Registry\\All Users\\Run");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run",   "Registry\\Current User\\Policies");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce",           "Registry\\Current User\\Run Services Once");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices",               "Registry\\Current User\\Run Services");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx",                 "Registry\\Current User\\Run Once Ex");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup",            "Registry\\Current User\\Run Once (Setup)");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce",                   "Registry\\Current User\\Run Once");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunEx",                     "Registry\\Current User\\Run Ex");
    this->LookAt(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",                       "Registry\\Current User\\Run");

}

void StartupMananger::ClearTreeWidget() {
    this->TreeWidget->clear();
}

int StartupMananger::GetTotalFound() {
    return this->TotalFound ;

}

HKEY StartupMananger::GetKeyHandle(QString sec) {
    HKEY TmpHandle;

    if (sec == QString("Registry\\All Users\\Policies")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\All Users\\Run Services Once")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\All Users\\Run Services")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\All Users\\Run Once Ex")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\All Users\\Run Once (Setup)")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }
    else if (sec == QString("Registry\\All Users\\Run Once")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\All Users\\Run Ex")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunEx" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }
    else if (sec == QString("Registry\\All Users\\Run")) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }
// current user
    else if (sec == QString("Registry\\Current User\\Policies")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run Services Once")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run Services")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run Once Ex")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run Once (Setup)")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER,  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run Once")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run Ex")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunEx" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    else if (sec == QString("Registry\\Current User\\Run")) {
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run" , 0, KEY_ALL_ACCESS, &TmpHandle) == ERROR_SUCCESS) {
            return TmpHandle ;
        }
    }

    return TmpHandle;

}

bool StartupMananger::DeleteKeyValue(QString sec, QString val) {

    HKEY TKey = this->GetKeyHandle(sec);

    long ec = RegDeleteValueA (TKey, val.toStdString().c_str()) ;
    if (ec == ERROR_SUCCESS) {
        return true;
    }
    else {
        return false ;
    }

}

int StartupMananger::EditValue(QString sec, QString val, QString NewVal) {
    QString OldVal = val;
    QString OldSec = sec;
    StartupManagerInput d(this->par, &val, &NewVal, &sec);
    if (d.exec() == 1) {
        HKEY TKey = this->GetKeyHandle(sec);
        this->DeleteKeyValue(OldSec, OldVal);
        LONG result = RegSetValueExA(TKey, val.toStdString().c_str(), 0, REG_SZ, (BYTE*)NewVal.toStdString().c_str(), strlen(NewVal.toStdString().c_str())+1);
        if (result == ERROR_SUCCESS) { // success
            return 0;
        }
        else {  // failed
            return -1;
        }
    }
    else {
        return 1;
    }
}
int StartupMananger::AddNewValue() {
    QString NewName ;
    QString NewSec ;
    QString NewVal ;
    StartupManagerInput d(this->par, &NewName, &NewVal, &NewSec);
    if (d.exec() == 1) {
        HKEY TKey = this->GetKeyHandle(NewSec);
        //this->DeleteKeyValue(OldSec, OldVal);
        LONG result = RegSetValueExA(TKey, NewName.toStdString().c_str(), 0, REG_SZ, (BYTE*)NewVal.toStdString().c_str(), strlen(NewVal.toStdString().c_str())+1);
        if (result == ERROR_SUCCESS) { // success
            return 0;
        }
        else {  // failed
            return -1;
        }
    }
    else {
        return 1;
    }
}

