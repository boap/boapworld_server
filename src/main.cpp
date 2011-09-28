#include        <QSharedPointer>
#include        <QCoreApplication>
#include        "core.hpp"
#include        "log.hpp"
#include        "db/client.hpp"

int             main(int ac, char **av)
{
  QCoreApplication app(ac, av);
  QSharedPointer<Core> c(Core::GetInstance());

  return (app.exec());
}
