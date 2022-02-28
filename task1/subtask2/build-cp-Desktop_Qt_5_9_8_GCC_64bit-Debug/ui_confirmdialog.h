/********************************************************************************
** Form generated from reading UI file 'confirmdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMDIALOG_H
#define UI_CONFIRMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConfirmDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *srcPath;
    QLabel *label_3;
    QLabel *desPath;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConfirmDialog)
    {
        if (ConfirmDialog->objectName().isEmpty())
            ConfirmDialog->setObjectName(QStringLiteral("ConfirmDialog"));
        ConfirmDialog->resize(400, 253);
        verticalLayout = new QVBoxLayout(ConfirmDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ConfirmDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        srcPath = new QLabel(ConfirmDialog);
        srcPath->setObjectName(QStringLiteral("srcPath"));

        verticalLayout->addWidget(srcPath, 0, Qt::AlignHCenter);

        label_3 = new QLabel(ConfirmDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3, 0, Qt::AlignHCenter);

        desPath = new QLabel(ConfirmDialog);
        desPath->setObjectName(QStringLiteral("desPath"));

        verticalLayout->addWidget(desPath, 0, Qt::AlignHCenter);

        buttonBox = new QDialogButtonBox(ConfirmDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox, 0, Qt::AlignHCenter);


        retranslateUi(ConfirmDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfirmDialog, SLOT(close()));
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfirmDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(ConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfirmDialog)
    {
        ConfirmDialog->setWindowTitle(QApplication::translate("ConfirmDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("ConfirmDialog", "COPY FROM", Q_NULLPTR));
        srcPath->setText(QApplication::translate("ConfirmDialog", "source file name", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConfirmDialog", "TO", Q_NULLPTR));
        desPath->setText(QApplication::translate("ConfirmDialog", "destinate file name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfirmDialog: public Ui_ConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMDIALOG_H
