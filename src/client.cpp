#include "client.hpp"
#include "log.hpp"

QSharedPointer<Client> Client::create(QSharedPointer<QTcpSocket> &s)
{
  QSharedPointer<Client> ptr(new Client(s));
  ptr->_this = ptr.toWeakRef();
  return (ptr);
}

Client::Client(QSharedPointer<QTcpSocket> &sock)
{
  Log::Debug("New client created!");
  _socket = sock;
}

Client::Client(__attribute__((unused)) const Client &ref)
{

}

Client::~Client()
{
  Log::Debug("Client destroyed!");
}

const QSharedPointer<QTcpSocket> &Client::GetSocket(void) const
{
  QMutexLocker locker(&_mutex);
  return (_socket);
}

void	Client::ReceiveData(void)
{
  QMutexLocker locker(&_mutex);
  Log::Debug("data received");
  sleep(5);
  Log::Debug("done!");
}
