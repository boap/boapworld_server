#ifndef	_CLIENT_HPP_
#define	_CLIENT_HPP_

#include <QMutex>
#include <QTcpSocket>
#include <QSharedPointer>
#include "opcode.hpp"

class   Client
{
public:
  ~Client(void);
  static QSharedPointer<Client> create(QTcpSocket *sock);
  static void (Client::*packetHandler[Op::handledOpcodeMax - Op::handledOpcodeMin + 1])(QByteArray &data);

  const QTcpSocket *GetSocket(void) const;

  void		ReceiveData(void);
  enum State
    {
      CONNECTED = 0x01, // Connection established but not logged in
      LOGGED    = 0x02,
    };

  /* Network packet handlers */
  void		Handle_CMSG_TRY_AUTHENTIFICATION(QByteArray &data);

private:
  Client(QTcpSocket *sock);
  Client(const Client &ref);
  mutable QMutex _mutex;
  QTcpSocket   * _socket;
  State         _state;

  qint32	_packetSize;
  qint16	_opcode;
  QWeakPointer<Client> _this;

};

#endif
