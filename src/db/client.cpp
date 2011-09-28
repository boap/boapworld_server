#include "db/client.hpp"

DB::Client::Client(void)
{

}

DB::Client::~Client(void)
{

}

QSharedPointer<QString> DB::Client::FetchPasswordFromUsername(const QString &username)
{
    return (QSharedPointer<QString>(0));
}
