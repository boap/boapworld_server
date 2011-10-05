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

        /**
         * Fetch the user's password from the database. It returns NULL
         * if the user is not found.
         * @param username const QString & 
         * @return Password or NULL if no user was found. 
         */
        static QSharedPointer<QString> FetchPasswordFromUsername(const QString &username);
    };
}
#endif
