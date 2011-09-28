#include "db/client.hpp"
#include "log.hpp"

DB::Client::Client(void)
{
  Log::Warning("FAIL");
}

DB::Client::~Client(void)
{

}

QSharedPointer<QString> DB::Client::FetchPasswordFromUsername(const QString &username)
{
  new Client();
}
