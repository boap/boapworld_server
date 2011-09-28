#ifndef	_DB_CLIENT_HPP_
#define	_DB_CLIENT_HPP_

#include "db/db.hpp"
<<<<<<< HEAD
#include <QSharedPointer>
=======
>>>>>>> 312f5df1a9bc8306e41fc19722727cc42f5ff820

class DB::Client
{
public:
<<<<<<< HEAD
  Client(void);
  ~Client(void);

  static QSharedPointer<QString> FetchPasswordFromUsername(const QString &username);
=======
  Client();
  ~Client();
>>>>>>> 312f5df1a9bc8306e41fc19722727cc42f5ff820
};

#endif
