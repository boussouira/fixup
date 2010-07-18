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
