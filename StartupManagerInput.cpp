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

#include "StartupManagerInput.h"

StartupManagerInput::StartupManagerInput(QWidget *p, QString *na, QString *va, QString *sect)
        : QDialog(p), TmpName(na), TmpValue(va), TmpSect(sect)
{
    /*this->parentx = p;   //Set The widget parent
    this->TmpName = na;  // pointer to the key name
    this->TmpValue = va; // pointer to the key value
    this->TmpSect = sect;*/

    this->resize(326, 103);
    this->setMinimumSize(QSize(267, 0));
    this->setMaximumSize(QSize(16777215, 103));
    label = new QLabel(this);

    lineEdit = new QLineEdit(this);
    label_2 = new QLabel(this);
    lineEdit_2 = new QLineEdit(this);
    pushButton_3 = new QPushButton(QString("..."), this);
    pushButton_3->setMaximumWidth(25);
    pushButton_3->setMaximumHeight(20);
    combobox = new QComboBox(this);
    combobox->setMaximumWidth(150);
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pushButton_2 = new QPushButton(this);
    pushButton_2->setMaximumSize(QSize(75, 23));
    pushButton = new QPushButton(this);
    pushButton->setMaximumSize(QSize(75, 23));
    this->setWindowTitle(QApplication::translate("this",  "Fixup Restrictions",       0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("this",        "Name :",  0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("this",      "Value :",  0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("this", "&Ok", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("this",   "&Cancel", 0, QApplication::UnicodeUTF8));
    combobox->addItem(QApplication::translate("this",   "All users", 0, QApplication::UnicodeUTF8));
    combobox->addItem(QString("%1 (%2)").arg(QApplication::translate("this",   "Current user", 0, QApplication::UnicodeUTF8),this->GetCurrentUserName()));
    pushButton_2->setDefault(true); // Set the "OK" button as defaut..
    this->SetComboText(sect);
    //combobox->hide(); // Next version..
    //we set the 2 lines text to the value of our 2 pointers..
    this->lineEdit->setText(QString(TmpName->toUtf8()));
    this->lineEdit_2->setText(QString(TmpValue->toUtf8()));

    //layout management
    gridLayout = new QGridLayout();
    verticalLayout = new QVBoxLayout(this);
    horizontalLayout = new QHBoxLayout();
    gridLayout->addWidget(lineEdit,0,1);
    gridLayout->addWidget(label,0,0);
    gridLayout->addWidget(label_2,1,0);
    gridLayout->addWidget(lineEdit_2,1,1);
    gridLayout->addWidget(combobox,2,1);
    gridLayout->addWidget(pushButton_3,1,2);
    verticalLayout->addLayout(gridLayout);
    horizontalLayout->addItem(horizontalSpacer);
    horizontalLayout->addWidget(pushButton);
    horizontalLayout->addWidget(pushButton_2);
    verticalLayout->addLayout(horizontalLayout);

    //signals/slots
    this->connect(this->pushButton_2, SIGNAL(clicked()), this, SLOT(OKPushx())); // connect the "OK" button to our slot
    this->connect(this->pushButton  , SIGNAL(clicked()), this, SLOT(reject())); // connect "Cancel" button to reject slot that hides the modal dialog and sets the result code to a 0
    this->connect(this->pushButton_3, SIGNAL(clicked()), this, SLOT(BrowseFiles()));
    //this->setModal(true); // no need for this.. we well use .exec() to show the dialog, that set model as true..

}
void StartupManagerInput::OKPushx() {

    //clear the 2 pointers..
    ///this->lineEdit->setInputMask(QString("000.000.000.000;_"));
    this->TmpName->clear();
    this->TmpValue->clear();
    this->TmpSect->clear();
    this->TmpName->append(this->lineEdit->text());
    if (TmpName->isEmpty()) {
        QMessageBox::warning(this,"FixUp Restrictions", "Name field is empty.");
        return ;
    }
    this->TmpValue->append(this->lineEdit_2->text());
    this->GetComboText(this->TmpSect);
    //hides the modal dialog and sets the result code to 1
    this->accept();
}

void StartupManagerInput::BrowseFiles() {
    QString fileNamex = QFileDialog::getOpenFileName(this,
                        tr("Choose a file"), this->lineEdit_2->text(), tr("All files(*.*)"));
    if (fileNamex.isNull()) {
        return ;
    }
    fileNamex.replace(QString("/"), QString("\\"));
    this->lineEdit_2->setText(fileNamex);
}

QString StartupManagerInput::GetCurrentUserName() {
    char acUserName[256];
    DWORD nUserName = sizeof(acUserName);
    GetUserNameA(acUserName, &nUserName);
    return QString(acUserName);
}

void StartupManagerInput::SetComboText(QString *qtxt) {
    if (qtxt == QString("Registry\\All Users\\Run")) {
        this->combobox->setCurrentIndex(0);
    }
    else if (qtxt == QString("Registry\\Current User\\Run")) {
        this->combobox->setCurrentIndex(1);
    }
    else if (qtxt->isEmpty()) {
        this->combobox->setCurrentIndex(1);
    }
    else {
        this->combobox->hide();
    }
}
void StartupManagerInput::GetComboText(QString *qtxtp) {
    if (this->combobox->currentIndex() == 0) {
        qtxtp->append(QString("Registry\\All Users\\Run"));
    }
    else if (this->combobox->currentIndex() == 1) {
        qtxtp->append(QString("Registry\\Current User\\Run"));
    }

}
