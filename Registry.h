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

