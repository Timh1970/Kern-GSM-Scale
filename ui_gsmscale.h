/********************************************************************************
** Form generated from reading UI file 'gsmscale.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSMSCALE_H
#define UI_GSMSCALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gsmscale
{
public:
    QWidget *centralwidget;
    QComboBox *CB_PageSize;
    QLabel *LAB_CB_PageSize;
    QLabel *LAB_TXT_Length;
    QLabel *LAB_TXT_Width;
    QLabel *LAB_X;
    QTextEdit *TXT_CUR_Weight;
    QLabel *LAB_CUR_Weight;
    QLCDNumber *LCD_GSM;
    QLabel *LAB_GSM;
    QDoubleSpinBox *SPIN_Length;
    QDoubleSpinBox *SPIN_Width;
    QMenuBar *menubar;
    QMenu *menuInplicare_GSM_Calculator;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gsmscale)
    {
        if (gsmscale->objectName().isEmpty())
            gsmscale->setObjectName(QString::fromUtf8("gsmscale"));
        gsmscale->resize(455, 530);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gsmscale->sizePolicy().hasHeightForWidth());
        gsmscale->setSizePolicy(sizePolicy);
        gsmscale->setMinimumSize(QSize(455, 530));
        gsmscale->setMaximumSize(QSize(455, 530));
        centralwidget = new QWidget(gsmscale);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CB_PageSize = new QComboBox(centralwidget);
        CB_PageSize->setObjectName(QString::fromUtf8("CB_PageSize"));
        CB_PageSize->setGeometry(QRect(150, 70, 261, 23));
        LAB_CB_PageSize = new QLabel(centralwidget);
        LAB_CB_PageSize->setObjectName(QString::fromUtf8("LAB_CB_PageSize"));
        LAB_CB_PageSize->setGeometry(QRect(40, 70, 111, 16));
        LAB_TXT_Length = new QLabel(centralwidget);
        LAB_TXT_Length->setObjectName(QString::fromUtf8("LAB_TXT_Length"));
        LAB_TXT_Length->setGeometry(QRect(40, 120, 81, 16));
        LAB_TXT_Width = new QLabel(centralwidget);
        LAB_TXT_Width->setObjectName(QString::fromUtf8("LAB_TXT_Width"));
        LAB_TXT_Width->setGeometry(QRect(260, 120, 71, 16));
        LAB_X = new QLabel(centralwidget);
        LAB_X->setObjectName(QString::fromUtf8("LAB_X"));
        LAB_X->setGeometry(QRect(190, 160, 71, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Serif Telugu Light")});
        font.setPointSize(36);
        font.setBold(false);
        LAB_X->setFont(font);
        LAB_X->setAlignment(Qt::AlignCenter);
        TXT_CUR_Weight = new QTextEdit(centralwidget);
        TXT_CUR_Weight->setObjectName(QString::fromUtf8("TXT_CUR_Weight"));
        TXT_CUR_Weight->setEnabled(false);
        TXT_CUR_Weight->setGeometry(QRect(40, 250, 371, 70));
        sizePolicy.setHeightForWidth(TXT_CUR_Weight->sizePolicy().hasHeightForWidth());
        TXT_CUR_Weight->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Cantarell")});
        font1.setPointSize(36);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setKerning(false);
        font1.setStyleStrategy(QFont::PreferAntialias);
        TXT_CUR_Weight->setFont(font1);
        TXT_CUR_Weight->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"	text-align: left;\n"
"}"));
        TXT_CUR_Weight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TXT_CUR_Weight->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LAB_CUR_Weight = new QLabel(centralwidget);
        LAB_CUR_Weight->setObjectName(QString::fromUtf8("LAB_CUR_Weight"));
        LAB_CUR_Weight->setGeometry(QRect(40, 230, 121, 16));
        LCD_GSM = new QLCDNumber(centralwidget);
        LCD_GSM->setObjectName(QString::fromUtf8("LCD_GSM"));
        LCD_GSM->setGeometry(QRect(40, 360, 371, 70));
        LCD_GSM->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"	color:rgb(0, 170, 0);\n"
"	background:black;\n"
"	text-align:center;\n"
"}"));
        LAB_GSM = new QLabel(centralwidget);
        LAB_GSM->setObjectName(QString::fromUtf8("LAB_GSM"));
        LAB_GSM->setGeometry(QRect(40, 340, 56, 15));
        SPIN_Length = new QDoubleSpinBox(centralwidget);
        SPIN_Length->setObjectName(QString::fromUtf8("SPIN_Length"));
        SPIN_Length->setGeometry(QRect(40, 140, 151, 70));
        sizePolicy.setHeightForWidth(SPIN_Length->sizePolicy().hasHeightForWidth());
        SPIN_Length->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Cantarell")});
        font2.setPointSize(36);
        SPIN_Length->setFont(font2);
        SPIN_Length->setDecimals(1);
        SPIN_Length->setMinimum(1.000000000000000);
        SPIN_Length->setMaximum(9999.000000000000000);
        SPIN_Width = new QDoubleSpinBox(centralwidget);
        SPIN_Width->setObjectName(QString::fromUtf8("SPIN_Width"));
        SPIN_Width->setGeometry(QRect(260, 140, 151, 70));
        sizePolicy.setHeightForWidth(SPIN_Width->sizePolicy().hasHeightForWidth());
        SPIN_Width->setSizePolicy(sizePolicy);
        SPIN_Width->setFont(font2);
        SPIN_Width->setDecimals(1);
        SPIN_Width->setMinimum(1.000000000000000);
        SPIN_Width->setMaximum(9999.000000000000000);
        gsmscale->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gsmscale);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 455, 20));
        menuInplicare_GSM_Calculator = new QMenu(menubar);
        menuInplicare_GSM_Calculator->setObjectName(QString::fromUtf8("menuInplicare_GSM_Calculator"));
        gsmscale->setMenuBar(menubar);
        statusbar = new QStatusBar(gsmscale);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        gsmscale->setStatusBar(statusbar);
        QWidget::setTabOrder(CB_PageSize, TXT_CUR_Weight);

        menubar->addAction(menuInplicare_GSM_Calculator->menuAction());

        retranslateUi(gsmscale);

        QMetaObject::connectSlotsByName(gsmscale);
    } // setupUi

    void retranslateUi(QMainWindow *gsmscale)
    {
        gsmscale->setWindowTitle(QCoreApplication::translate("gsmscale", "gsmscale", nullptr));
        LAB_CB_PageSize->setText(QCoreApplication::translate("gsmscale", "Select page size:", nullptr));
        LAB_TXT_Length->setText(QCoreApplication::translate("gsmscale", "Length (mm)", nullptr));
        LAB_TXT_Width->setText(QCoreApplication::translate("gsmscale", "Width (mm)", nullptr));
        LAB_X->setText(QCoreApplication::translate("gsmscale", "X", nullptr));
        LAB_CUR_Weight->setText(QCoreApplication::translate("gsmscale", "Current Weight (g)", nullptr));
        LAB_GSM->setText(QCoreApplication::translate("gsmscale", "GSM", nullptr));
        menuInplicare_GSM_Calculator->setTitle(QCoreApplication::translate("gsmscale", "Inplicare GSM Calculator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gsmscale: public Ui_gsmscale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSMSCALE_H
