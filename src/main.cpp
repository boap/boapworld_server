#include        <QSharedPointer>
#include        <QCoreApplication>
#include        "core.hpp"
#include        "db/handler.hpp"

QMutex DB::Handler::_mutex(QMutex::Recursive);
QMap<QThread *, QSqlDatabase *> DB::Handler::_dbs;

int             main(int ac, char **av)
{
  QCoreApplication app(ac, av);
  QSharedPointer<Core> c(Core::GetInstance());
  
  return (app.exec());
}
