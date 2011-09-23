#ifndef	_PACKET_HPP_
#define _PACKET_HPP_

#include <QString>
#include <qnumeric.h>

typedef struct s_2strings
{
  QString	str1;
  QString	str2;
}		t_2strings;		

typedef struct s_short
{
  qint16	data;
}		t_short;

#endif
