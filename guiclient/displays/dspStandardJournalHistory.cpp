/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2019 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#include "dspStandardJournalHistory.h"

#include <QAction>
#include <QMenu>
#include "guiErrorCheck.h"
#include <QSqlError>
#include <QVariant>

#include "guiclient.h"
#include "xtreewidget.h"
#include "metasql.h"
#include "mqlutil.h"
#include "reverseGLSeries.h"
#include "errorReporter.h"

dspStandardJournalHistory::dspStandardJournalHistory(QWidget* parent, const char*, Qt::WindowFlags fl)
  : display(parent, "dspStandardJournalHistory", fl)
{
  setupUi(optionsWidget());
  setWindowTitle(tr("Standard Journal History"));
  setListLabel(tr("G/L Transactions"));
  setReportName("StandardJournalHistory");
  setMetaSQLOptions("standardJournalHistory", "detail");
  setUseAltId(true);

  list()->setRootIsDecorated(true);
  list()->addColumn(tr("Date"),         _dateColumn,     Qt::AlignCenter, true,  "gltrans_date" );
  list()->addColumn(tr("Journal #"),    _itemColumn,     Qt::AlignCenter, true,  "gltrans_journalnumber" );
  list()->addColumn(tr("Posted"),       _ynColumn,       Qt::AlignCenter, true,  "gltrans_posted" );
  list()->addColumn(tr("Journal Name"), _orderColumn,    Qt::AlignCenter, true,  "gltrans_docnumber" );
  list()->addColumn(tr("Account"),      -1,              Qt::AlignLeft,   true,  "account"   );
  list()->addColumn(tr("Debit"),        _bigMoneyColumn, Qt::AlignRight,  true,  "debit"  );
  list()->addColumn(tr("Credit"),       _bigMoneyColumn, Qt::AlignRight,  true,  "credit"  );
}

void dspStandardJournalHistory::languageChange()
{
  display::languageChange();
  retranslateUi(this);
}

void dspStandardJournalHistory::sPopulateMenu(QMenu * pMenu, QTreeWidgetItem*, int)
{
  bool deletable = false;

  // Make sure there is nothing to restricting deletes
  ParameterList params;
  params.append("glSequence", list()->id());
  MetaSQLQuery mql = mqlLoad("glseries", "checkeditable");
  XSqlQuery qry = mql.toQuery(params);
  if (!qry.first())
    deletable = true;

  QAction *menuItem;

  menuItem = pMenu->addAction(tr("Delete Journal..."), this, SLOT(sDelete()));
  menuItem->setEnabled(_privileges->check("DeletePostedJournals") && deletable);

  pMenu->addSeparator();

  menuItem = pMenu->addAction(tr("Reverse Journal..."), this, SLOT(sReverse()));
  menuItem->setEnabled(_privileges->check("PostStandardJournals"));
}

bool dspStandardJournalHistory::setParams(ParameterList &params)
{
  QList<GuiErrorCheck> errors;
  errors<< GuiErrorCheck(!_dates->allValid(), _dates,
                         tr("Please enter a valid Start Date & End Date."))
  ;
  if (GuiErrorCheck::reportErrors(this, tr("Enter Date"), errors))
    return false;

  params.append("startDate", _dates->startDate());
  params.append("endDate", _dates->endDate());

  return true;
}

void dspStandardJournalHistory::sReverse()
{
  ParameterList params;
  params.append("glseries", list()->id());  

  reverseGLSeries newdlg(this);
  if(newdlg.set(params) != NoError)
    return;
  if(newdlg.exec() == XDialog::Accepted)
    sFillList();
}

void dspStandardJournalHistory::sDelete()
{
  ParameterList params;
  params.append("glseries", list()->id());
  params.append("notes", tr("Journal deleted by %1 on %2")
                .arg(omfgThis->username())
                .arg(omfgThis->dbDate().toString()));

  MetaSQLQuery mql("SELECT deleteGlSeries(<? value(\"glseries\") ?>,"
                   "<? value(\"notes\") ?>) AS result;");
  XSqlQuery del;
  del = mql.toQuery(params);
  if (ErrorReporter::error(QtCriticalMsg, this, tr("Error Deleting GL Series Information"),
                                del, __FILE__, __LINE__))
  {
    return;
  }

  omfgThis->sGlSeriesUpdated();
  sFillList();
}
