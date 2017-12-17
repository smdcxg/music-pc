#ifndef APPSEARCHLINE_H
#define APPSEARCHLINE_H

#include <QLineEdit>
#include <QWidget>

class AppSearchLine : public QLineEdit
{
    Q_OBJECT
public:
    AppSearchLine(QWidget *parent = 0);
};

#endif // APPSEARCHLINE_H
