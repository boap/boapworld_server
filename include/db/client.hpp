#ifndef	_DB_CLIENT_HPP_
#define	_DB_CLIENT_HPP_

#include "db/db.hpp"
#include <QSharedPointer>

class DB::Client
{
public:
  Client(void);
  ~Client(void);

  static QSharedPointer<QString> FetchPasswordFromUsername(const QString &username);
};

#endif
