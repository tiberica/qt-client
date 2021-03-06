/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2019 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#ifndef BANKACCOUNTS_H
#define BANKACCOUNTS_H

#include "guiclient.h"
#include "xwidget.h"
#include <parameter.h>

#include "ui_bankAccounts.h"

class bankAccounts : public XWidget, public Ui::bankAccounts
{
    Q_OBJECT

public:
    bankAccounts(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::Window);
    ~bankAccounts();

protected slots:
    virtual void languageChange();

    virtual void sNew();
    virtual void sEdit();
    virtual void sView();
    virtual void sFillList();
    virtual void sDelete();
    virtual void sPopulateMenu( QMenu * );
    virtual void sPrint();


};

#endif // BANKACCOUNTS_H
