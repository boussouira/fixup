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

