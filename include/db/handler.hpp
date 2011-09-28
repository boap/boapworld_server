#ifndef	_DB_HANDLER_HPP_
#define	_DB_HANDLER_HPP_

#include "db/db.hpp"
#include <QMutex>
#include <QMap>
#include <QSqlDatabase>
#include <QThread>

class DB::Handler
{
public:
  static QSqlDatabase *GetDb(void);

private:
  Handler();
  ~Handler();

  static QMap<QThread *, QSqlDatabase *> _dbs;
  static QMutex	_mutex;
};

#endif
