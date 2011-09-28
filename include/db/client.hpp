#ifndef	_DB_CLIENT_HPP_
#define	_DB_CLIENT_HPP_

#include "db/db.hpp"
#include <QSharedPointer>

namespace DB
{

    class Client
    {
    public:
        Client(void);
        ~Client(void);

        static QSharedPointer<QString> FetchPasswordFromUsername(const QString &username);
    };
}
#endif
