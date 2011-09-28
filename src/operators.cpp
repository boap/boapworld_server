#include "operators.hpp"
#include "packet.hpp"

#include <QDataStream>
QByteArray & operator<< (QByteArray &data, const t_2strings &packet)
{
  QDataStream s(data);
  s << packet.str1;
  s << packet.str2;
  return (data);
}

QByteArray & operator>> (QByteArray &data, t_2strings &packet)
{
  QDataStream s(data);

  s >> packet.str1;
  s >> packet.str2;
  return (data);
}
