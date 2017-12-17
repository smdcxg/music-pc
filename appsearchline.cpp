#include "appsearchline.h"
#include <QHBoxLayout>
#include <QPushButton>
AppSearchLine::AppSearchLine(QWidget *parent)
    :QLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QPushButton *searchBtn = new QPushButton;
    searchBtn->setFixedSize(13,13);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setToolTip(tr("搜索"));
    searchBtn->setStyleSheet("QPushButton{border-image:url(:/icon/icon/search.png);"
                             "background:transparent;cursor:pointer;"
                             "}");
    setPlaceholderText(tr("搜索音乐"));
    mainLayout->addWidget(searchBtn);
    mainLayout->addStretch();
    //mainLayout->setContentsMargins(8,8,8,8);
    mainLayout->setContentsMargins(8,0,0,0);
    setTextMargins(13+8+2,0,0,0);
    setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
}
