#ifndef	_CLIENT_HPP_
#define	_CLIENT_HPP_

#include <QMutex>
#include <QTcpSocket>
#include <QSharedPointer>

class   Client
{
public:
  ~Client(void);
  static QSharedPointer<Client> create(QSharedPointer<QTcpSocket> &sock);
  const QSharedPointer<QTcpSocket> &GetSocket(void) const;

  void		ReceiveData(void);
  enum State
    {
      CONNECTED = 0x01, // Connection established but not logged in
      LOGGED    = 0x02,
    };

private:
  Client(QSharedPointer<QTcpSocket> &sock);
  Client(const Client &ref);
  mutable QMutex _mutex;
  QSharedPointer<QTcpSocket>    _socket;
  State         _state;

  QWeakPointer<Client> _this;
};

#endif
