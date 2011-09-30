#include "db/client.hpp"
#include "db/handler.hpp"
#include "exception.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

DB::Client::Client(void)
{

}

DB::Client::~Client(void)
{

}

QSharedPointer<QString> DB::Client::FetchPasswordFromUsername(const QString &username)
{
  QSqlQuery		q(Handler::GetDb());

  q.prepare("SELECT passwd FROM users WHERE username = :username");
  q.bindValue(":username", username);
  if (!q.exec())
    throw Exception("Cannot execute SQL query: " + q.lastQuery() + ". Error: "
		    + q.lastError().text());
  if (q.first())
    return (QSharedPointer<QString>(new QString(q.value(0).toString())));
  return (QSharedPointer<QString>(0));
}
