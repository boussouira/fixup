#include "MainClass.h"
#define FIXUP_VERSION 0.3


MainClass::MainClass(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    this->setWindowTitle(QString::fromUtf8("FixUp Restrictions %1").arg(QString::number(FIXUP_VERSION)));
    ChekRestrictionsOnly->hide();
    AutoScanTimer = new QTimer();
    AutoRemoveTimer = new QTimer();
    CheckState = 0;
    //Fixup stuff
    connect(ScanButton, SIGNAL(clicked()), this, SLOT(Scan()));
    connect(RemoveButton, SIGNAL(clicked()), this, SLOT(Remove()));
    connect(CheckUnChekButton, SIGNAL(clicked()), this, SLOT(Check()));
    //connect(ExitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    //connect(DonateButton, SIGNAL(clicked()), this, SLOT(GoDonate()));
    connect(AutoScanTimer, SIGNAL(timeout()), this, SLOT(Scan()));
    connect(AutoRemoveTimer, SIGNAL(timeout()), this, SLOT(Remove()));
    connect(ChekConfMsg, SIGNAL(stateChanged(int)), this, SLOT(RefreshSetting()));
    connect(ChekRestrictionsOnly, SIGNAL(stateChanged(int)), this, SLOT(RefreshSetting()));
    connect(ChekAutoScan, SIGNAL(clicked()), this, SLOT(AutoScanSetting()));
    connect(ChekAutoRemove, SIGNAL(clicked()), this, SLOT(AutoRemoveSetting()));
    connect(SilderAutoScanFrequency, SIGNAL(valueChanged(int)), this, SLOT(AutoScanSetting()));
    connect(SilderAutoScanFrequency, SIGNAL(valueChanged(int)), this, SLOT(AutoRemoveSetting()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(ButtonApp(int)));
    //Regstartup stuff..
    connect(StartUpRefreshButton , SIGNAL(clicked()), this, SLOT(StartUpRefresh()));
    connect(StartUpEditButton    , SIGNAL(clicked()), this, SLOT(StartUpEdit()));
    connect(StartUpDeleteButton  , SIGNAL(clicked()), this, SLOT(StartUpDelete()));
    connect(StartUpAddButton     , SIGNAL(clicked()), this, SLOT(StartUpAdd()));
    connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(StartUpEdit()));
    Reg = new RegistryFixer(this);
    StarMan = new StartupMananger(this, this->treeWidget);
    ChekAutoScan->setChecked(true);
    RefreshSetting();
    Scan();
    AutoScanSetting();
    AutoRemoveSetting();
    ButtonApp(0);
}

void MainClass::Scan()
{
    if (!AutoRemoveEnablde) {
        Reg->DoScan();
        Restricitions();
    }
}

void MainClass::Remove()
{
    Reg->DoRemove();
    Restricitions();
    Reg->ShowCofirmingMsg();
}

void MainClass::Check()
{
    /* No need for this...
    	if(CheckState == 0){
    */
    Reg->DoCheckAll();
    Restricitions();
    /*
    		CheckState = 1 ;
    		CheckUnChekButton->setText(QString::fromUtf8("&UnCheck All"));

                }
            else{

    		Reg->DoUnCheckAll();
    		Restricitions();
                    CheckState = 0 ;
                    CheckUnChekButton->setText(QString::fromUtf8("&Check All"));
            }
     */
}

void MainClass::Restricitions()
{
    //Windows Restrictions
    Reg->Do("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer", "NoRun"                  , checkBox  );
    Reg->Do("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\sYsTem"  , "DisableTaskMgr"         , checkBox_2);
    Reg->Do("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer", "NoFolderOptions"        , checkBox_3);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoControlPanel"         , checkBox_4);
    Reg->Do("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"  , "DisableRegistryTools"   , checkBox_5);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "HideIcons"              , checkBox_6);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "StartMenuLogoff"        , checkBox_7);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoDrives"               , checkBox_8);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoViewOnDrive"          , checkBox_9);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoFind"                 , checkBox_10);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoClose"                , checkBox_11);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"  , "NoDispCPL"              , checkBox_12);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoSetTaskbar"           , checkBox_13);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoTrayContextMenu"      , checkBox_14);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoViewContextMenu"      , checkBox_15);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoToolbarsOnTaskbar"    , checkBox_16);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoPropertiesMyComputer" , checkBox_17);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Uninstall", "NoAddRemovePrograms"   , checkBox_18);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoSaveSettings"         , checkBox_19);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Hidden"                 , checkBox_38, 1);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSuperHidden"        , checkBox_39, 1);
    Reg->Do("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\Hidden\\SHOWALL"  , "CheckedValue"  , checkBox_40, 1);
    Reg->Do("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\Hidden\\NOHIDDEN" , "CheckedValue"  , checkBox_41, 2);
    Reg->Do("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoDriveTypeAutoRun"     , checkBox_42, 255);
    //IE Restrictions
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "AlwaysPromptWhenDownload", checkBox_20);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoBrowserBars",            checkBox_21);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoBrowserClose",           checkBox_22);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoBrowserContextMenu",     checkBox_23);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoBrowserOptions",         checkBox_24);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoBrowserSaveAs",          checkBox_25);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoFileNew",                checkBox_26);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoFindFiles",              checkBox_27);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoNavButtons",             checkBox_28);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoOpeninNewWnd",           checkBox_29);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoSelectDownloadDir",      checkBox_30);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoTheaterMode",            checkBox_31);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoViewSource",             checkBox_32);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Restrictions", "NoFavorites",              checkBox_33);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Toolbars\\Restrictions", "NoToolbarOptions", checkBox_34);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Toolbars\\Restrictions", "NoAddressBar",     checkBox_35);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Toolbars\\Restrictions", "NoToolBar",        checkBox_36);
    Reg->Do("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Toolbars\\Restrictions", "NoLinksBar",       checkBox_37);


}

void MainClass::RefreshSetting()
{
    if (ChekConfMsg->isChecked() && !AutoRemoveEnablde) {
        ShowMsg = true ;
    }
    else {
        ShowMsg = false ;
    }
    AutoRemoveEnablde = (ChekAutoRemove->isChecked()) ? true : false ;
    Reg->UpDateSetting(ChekRestrictionsOnly->isChecked(), AutoRemoveEnablde, ShowMsg);
}

void MainClass::AutoScanSetting()
{
    ScanButton->setDisabled(ChekAutoScan->isChecked());
    if (ChekAutoScan->isChecked()) {
        AutoScanTimer->setInterval(SilderAutoScanFrequency->value());
        AutoScanTimer->start();
    }
    else {
        AutoScanTimer->stop();
    }
}

void MainClass::AutoRemoveSetting()
{
    RemoveButton->setDisabled(ChekAutoRemove->isChecked());
    CheckUnChekButton->setDisabled(ChekAutoRemove->isChecked());
    if (ChekAutoRemove->isChecked()) {
        ShowMsg = false ;
        AutoRemoveTimer->setInterval(SilderAutoScanFrequency->value());
        AutoRemoveTimer->start();
        AutoRemoveEnablde = true;
    }
    else {
        ShowMsg = (ChekConfMsg->isChecked()) ? true : false ;
        AutoRemoveTimer->stop();
        AutoRemoveEnablde = false;
    }
    Reg->UpDateSetting(ChekRestrictionsOnly->isChecked(), AutoRemoveEnablde, ShowMsg);

}
/*
void MainClass::GoDonate()
{
	ShellExecuteA( NULL, "open" , "http://sourceforge.net/donate/index.php?group_id=237758" , NULL, NULL, SW_SHOW );
}
*/
void MainClass::ButtonApp(int TabsIndex)
{
    if (TabsIndex == 1) {
        this->StartUpRefresh();
    }

}

void MainClass::StartUpRefresh() {
    StarMan->ClearTreeWidget();
    StarMan->QuickScan();
    // this->label_2->setText(QString::number(StarMan->GetTotalFound()));
}

void MainClass::StartUpEdit() {

    if (this->treeWidget->selectedItems().count() <=0) {
        QMessageBox::warning(this, "FixUp Restrictions", "Select something first!");
        return ;
    }

    int r = StarMan->EditValue(StarMan->GetSelectedColumnText(1),
                               StarMan->GetSelectedColumnText(0),
                               StarMan->GetSelectedColumnText(2));

    if (r == 0) {
        this->StartUpRefresh();
    }
    else if (r == 1) {
        //QMessageBox::information(this, "FixUp Restrictions", "Canceled");
    }
    else {
        QMessageBox::warning(this, "FixUp Restrictions", "Error<br>please Try again");
    }

}

void MainClass::StartUpDelete() {

    if (this->treeWidget->selectedItems().count() <=0) {
        QMessageBox::warning(this, "FixUp Restrictions", "Select something first!");
        return ;
    }

    int rep = QMessageBox::question(this, "FixUp Restrictions", "Are you sure you want to delete this key ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::No) {
        return ;
    }
    if (StarMan->DeleteKeyValue( StarMan->GetSelectedColumnText(1),
                                 StarMan->GetSelectedColumnText(0))) {
        //QMessageBox::information(this, "FixUp Restrictions", "The Key Was Deleted.");
        this->StartUpRefresh();
    }
    else {
        QMessageBox::warning(this, "FixUp Restrictions", "Error<br>Please try again");
    }
}

void MainClass::StartUpAdd() {
    int r = StarMan->AddNewValue();
    if (r == 0) {
        this->StartUpRefresh();
    }
    else if (r == 1) {
        //QMessageBox::information(this, "FixUp Restrictions", "Canceled");
    }
    else {
        QMessageBox::warning(this, "FixUp Restrictions", "Error<br>Please try again");
    }
}

