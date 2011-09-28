#include        "db/handler.hpp"
#include        "log.hpp"
#include        "network.hpp"
#include        <QThread>
#include        <QSqlDatabase>

DB::Handler::Handler(void)
{

}

DB::Handler::~Handler(void)
{

}

QSqlDatabase            *DB::Handler::GetDb(void)
{
    QMutexLocker        locker(&_mutex);
    QThread             *thread;
    QSqlDatabase        *db;

    thread = QThread::currentThread();
    if (_dbs.contains(thread))
        return (_dbs.value(thread));
    Log::Info("Creating new SQL connection.");
    db = new QSqlDatabase();
    db->setDatabaseName("mmo");
    db->setHostName("xaqq.fr");
    db->setPassword("mmo");
    db->setUserName("mmo");
    if (!db->open())
    {
        Log::Critical("Cannot open new SQL connection.");
        free(db);
        return (NULL);
    }
    _dbs.insert(thread, db);
    return (db);
}
