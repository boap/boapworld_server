#include "db/client.hpp"
<<<<<<< HEAD
#include "log.hpp"

DB::Client::Client(void)
{
  Log::Warning("FAIL");
}

DB::Client::~Client(void)
=======

DB::Client::Client()
>>>>>>> 312f5df1a9bc8306e41fc19722727cc42f5ff820
{

}

<<<<<<< HEAD
QSharedPointer<QString> DB::Client::FetchPasswordFromUsername(const QString &username)
{
  new Client();
=======
DB::Client::~Client()
{

>>>>>>> 312f5df1a9bc8306e41fc19722727cc42f5ff820
}
