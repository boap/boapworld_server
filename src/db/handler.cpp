#include        "db/handler.hpp"

QMutex DB::Handler::_mutex;

DB::Handler::Handler(void)
{

}

DB::Handler::~Handler(void)
{

}

QSqlDatabase *DB::Handler::GetDb(void)
{
}
