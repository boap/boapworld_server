#include        "db/handler.hpp"
#include        "log.hpp"
#include        "network.hpp"
#include	"exception.hpp"
#include        <QThread>
#include        <QSqlDatabase>
#include	<QSqlError>

DB::Handler::Handler(void)
{

}

DB::Handler::~Handler(void)
{

}

QMutex & DB::Handler::_mutex()
{
  static QMutex *ptr = new QMutex();
  return (*ptr);
}

QSqlDatabase          DB::Handler::GetDb(void)
{
  QMutexLocker        locker(&_mutex());
  QThread             *thread;
  QSqlDatabase        db;
  QString	      name;

  thread = QThread::currentThread();
  name = "Connection_" + QString::number(reinterpret_cast<long>(thread));
  if (QSqlDatabase::contains(name))
    {
      db = QSqlDatabase::database(name, false);
      if (db.isOpen() || db.open())
	return (db);
      else
	throw Exception("Cannot open the thread connection to SQL database: "
			+ db.lastError().text());
    }
  Log::Info("Creating new SQL connection...");
  db = QSqlDatabase::addDatabase("QMYSQL", name);
  db.setDatabaseName("boap");
  db.setHostName("xaqq.fr");
  db.setPassword("test");
  db.setUserName("test");
  if (!db.open())
    throw Exception("Cannot create a valid connection to SQL database: "
		    + db.lastError().text());
  return (db);
}
