/********************************************************************************
** Form generated from reading UI file 'progressor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSOR_H
#define UI_PROGRESSOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Progressor
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QProgressBar *bar;

    void setupUi(QWidget *Progressor)
    {
        if (Progressor->objectName().isEmpty())
            Progressor->setObjectName(QStringLiteral("Progressor"));
        Progressor->resize(400, 84);
        verticalLayout = new QVBoxLayout(Progressor);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        title = new QLabel(Progressor);
        title->setObjectName(QStringLiteral("title"));

        verticalLayout->addWidget(title, 0, Qt::AlignHCenter);

        bar = new QProgressBar(Progressor);
        bar->setObjectName(QStringLiteral("bar"));
        bar->setValue(24);

        verticalLayout->addWidget(bar);


        retranslateUi(Progressor);

        QMetaObject::connectSlotsByName(Progressor);
    } // setupUi

    void retranslateUi(QWidget *Progressor)
    {
        Progressor->setWindowTitle(QApplication::translate("Progressor", "Form", Q_NULLPTR));
        title->setText(QApplication::translate("Progressor", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Progressor: public Ui_Progressor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSOR_H
