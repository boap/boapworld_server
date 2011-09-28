#ifndef	_OPERATORS_HPP_
#define	_OPERATORS_HPP_

#include <QByteArray>
#include "packet.hpp"

QByteArray & operator<< (QByteArray &data, const t_2strings &packet);
QByteArray & operator>> (QByteArray &data, t_2strings &packet);

#endif
