#ifndef	_PACKET_HPP_
#define _PACKET_HPP_

#include <QString>
#include <QSharedPointer>
#include <qnumeric.h>

class QTcpSocket;

typedef struct s_2strings
{
  QString	str1;
  QString	str2;
}		t_2strings;		

typedef struct s_queued
{
  QSharedPointer<QByteArray> data;
  QTcpSocket			*sock;
  bool operator ==(const struct s_queued &t1)
  {
    if (this->data.data() == t1.data.data() && this->sock == t1.sock)
      return (true);
    return (false);
  }
}		t_queued;

#endif
