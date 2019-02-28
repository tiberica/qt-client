/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2019 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#ifndef DYNAMICFILTERS_H
#define DYNAMICFILTERS_H

#include "xwidget.h"

#include "ui_dynamicfilters.h"

class dynamicfilters : public XWidget, public Ui::dynamicfilters
{
    Q_OBJECT

public:
    dynamicfilters(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::Window);
    ~dynamicfilters();

public slots:
    virtual void sNew();
    virtual void sEdit();
    virtual void sDelete();
    virtual void sFillList();

protected slots:
    virtual void languageChange();

};

#endif // DYNAMICFILTERS_H