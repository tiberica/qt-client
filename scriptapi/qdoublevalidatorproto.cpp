/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2018 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#include "scriptapi_internal.h"
#include "qdoublevalidatorproto.h"

#define DEBUG false

QScriptValue QDoubleValidatorToScriptValue(QScriptEngine *engine, QDoubleValidator* const &in)
 { return engine->newQObject(in); }

void QDoubleValidatorFromScriptValue(const QScriptValue &object, QDoubleValidator* &out)
 { out = qobject_cast<QDoubleValidator*>(object.toQObject()); }

static QScriptValue NotationToScriptValue(QScriptEngine *engine, const enum QDoubleValidator::Notation &p)
{
  return QScriptValue(engine, (int)p);
}
static void NotationFromScriptValue(const QScriptValue &obj, enum QDoubleValidator::Notation &p)
{
  p = (enum QDoubleValidator::Notation)obj.toInt32();
}

void setupQDoubleValidatorProto(QScriptEngine *engine)
{
  qScriptRegisterMetaType(engine, QDoubleValidatorToScriptValue, QDoubleValidatorFromScriptValue);

  QScriptValue proto       = engine->newQObject(new QDoubleValidatorProto(engine));
  QScriptValue constructor = engine->newFunction(constructQDoubleValidator, proto);
  engine->globalObject().setProperty("QDoubleValidator", constructor);

  qScriptRegisterMetaType(engine, NotationToScriptValue, NotationFromScriptValue);
  constructor.setProperty("StandardNotation",   QScriptValue(engine, QDoubleValidator::StandardNotation),   ENUMPROPFLAGS);
  constructor.setProperty("ScientificNotation", QScriptValue(engine, QDoubleValidator::ScientificNotation), ENUMPROPFLAGS);

}

QScriptValue constructQDoubleValidator(QScriptContext *context,
                                       QScriptEngine  *engine)
{
  QDoubleValidator *obj = 0;

  if (DEBUG)
  {
    qDebug("constructQDoubleValidator() entered");
    for (int i = 0; i < context->argumentCount(); i++)
      qDebug("context->argument(%d) = %s", i,
             qPrintable(context->argument(i).toString()));
  }

  if (context->argumentCount() >= 4)
    obj = new QDoubleValidator(context->argument(0).toNumber(),
                    context->argument(1).toNumber(),
                    context->argument(2).toInt32(),
                    context->argument(3).toQObject());
  else if (context->argumentCount() == 1)
    obj = new QDoubleValidator(context->argument(0).toQObject());
  else
    context->throwError(QScriptContext::UnknownError,
                        "QDoubleValidator() constructor is not yet supported");

  return engine->toScriptValue(obj);
}

QDoubleValidatorProto::QDoubleValidatorProto(QObject *parent)
    : QObject(parent)
{
}

