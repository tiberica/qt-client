/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2019 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#ifndef DSPPOSBYDATE_H
#define DSPPOSBYDATE_H

#include "display.h"

#include "ui_dspPOsByDate.h"

class dspPOsByDate : public display, public Ui::dspPOsByDate
{
    Q_OBJECT

public:
    dspPOsByDate(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::Window);

    virtual bool setParams(ParameterList &);

public slots:
    virtual void sEditOrder();
    virtual void sViewOrder();
    virtual void sPopulateMenu(QMenu * pMenu, QTreeWidgetItem * pSelected, int);

protected slots:
    virtual void languageChange();

};

#endif // DSPPOSBYDATE_H
