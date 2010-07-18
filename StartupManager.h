#ifndef STARTUPMANAGER_H
#define STARTUPMANAGER_H

#include <windows.h>
#include <string>
#include <QtGui/QMainWindow>
#include <QFileIconProvider>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "StartupManagerInput.h"

class StartupMananger
{
public :
    /**
    *@brief The constructor.
    *@param p pointer to the parent widget.
    *@param TreeW pointer to the QTreeWiget.
    */

    StartupMananger(QWidget *p, QTreeWidget *TreeW);

    /**
    *@brief Scan for start with windows programmes.
    */

    void QuickScan();

    /**
    *@brief Clear our treewiget items.
    */

    void ClearTreeWidget();

    /**
    *@brief Get the treewiget items count
    *@return items count (int).
    */

    int GetTotalFound();

    /**
    *@brief Edit an item from the registry
    *@param sec the item section to get a handle to the parent key.
    *@param val item's name.
    *@param NewName item's value.
    *@return 0  if the edit succeed.
             1  if canceled.
             -1 if an error occurred.
    */


    int EditValue(QString sec, QString val, QString NewName);

    /**
    *@brief Create a new Entry int the registry
    *@return 0  if the edit succeed.
             1  if canceled.
             -1 if an error occurred.
    */

    int AddNewValue();
    /**
    *@brief Delete an item from the registry
    *@param sec the item section to get a handle to the parent key.
    *@param val item's name.
    *@return true if succeed. false on error occurred.
    */

    bool DeleteKeyValue(QString sec, QString val);

    /**
    *@brief Get only a file path.
    *@param s file path.
    *@return The path file as QString .
    *@example ("c:\windows\explorer.exe" -h) ==> (c:\windows\explorer.exe) : without the quotes and the flags
    */

    QString OnlyPath(QString s);

    /**
    *@brief Get a QTreeWidget column's text.
    *@details this function remove this string : "File not found: ".
    *@param c the column index.
    *@return Column text as QString .
    *@example column N° 2 (File not found: c:\windows\explorer.exe) ==> (c:\windows\explorer.exe)
    */

    QString GetSelectedColumnText(int c);

    /**
    *@brief Get the handle of the given section.
    *@details well to edit or remove any registry value we need a handle to that value's parent KEY .
    *@param sec the section.
    *@return a HANDLE.
    */

    HKEY GetKeyHandle(QString sec);


private:
    void LookAt(HKEY RootKey, char *PathKey, char *KeySection);
    int TotalFound;
    QWidget *par;
    QTreeWidget *TreeWidget;
    QFileIconProvider test;
};

#endif // STARTUPMANAGER_H
