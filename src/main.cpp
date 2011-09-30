#include        <QSharedPointer>
#include        <QCoreApplication>
#include        "core.hpp"
#include        "db/handler.hpp"
#include	"exception.hpp"
#include	"log.hpp"

int             main(int ac, char **av)
{
  QCoreApplication app(ac, av);
  QSharedPointer<Core> c(Core::GetInstance());

  return (app.exec());
}
