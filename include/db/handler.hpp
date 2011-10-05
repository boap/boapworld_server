#ifndef	_DB_HANDLER_HPP_
#define	_DB_HANDLER_HPP_

#include "db/db.hpp"
#include <QMutex>
#include <QMap>

class QSqlDatabase;
class QThread;

namespace DB
{

    class Handler
    {
    public:
        /**
         * This method is called by worker thread to get a valid connection
         * (in their context) to the database.
         * @notes Thread-safe
         * @throw An exception if it can get a valid (and openned) connection
         * @return A valid MySQL connection.
         */
        static QSqlDatabase GetDb(void);

    private:
        Handler();
        ~Handler();

      static QMutex & _mutex();
    } ;
}
#endif
