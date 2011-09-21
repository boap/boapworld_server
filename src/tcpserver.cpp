#include "tcpserver.hpp"
#include "log.hpp"
#include "network.hpp"
#include <QSharedPointer>
#include <QtConcurrentRun>

TcpServer::TcpServer(void)
{
  Log::Debug("TcpServer's constructor");
}

TcpServer::TcpServer(__attribute__((unused))const TcpServer &ref) : QTcpServer()
{
  
}

TcpServer::~TcpServer(void)
{

}

void	TcpServer::incomingConnection(int s)
{
  QSharedPointer<QTcpSocket> sock(new QTcpSocket);
  QSharedPointer<Client> client = Client::create(sock);

  Log::Debug("New incoming connection");
  if (!sock->setSocketDescriptor(s))
    {
      Log::Critical("Cannot set socket descriptor");
      return;
    }
  QObject::connect(sock.data(), SIGNAL(disconnected()), this, SLOT(SlotSocketDisconnected()), Qt::QueuedConnection);
  QObject::connect(sock.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotSocketError()), Qt::QueuedConnection);
  QObject::connect(sock.data(), SIGNAL(readyRead()), this,
  		   SLOT(SlotReceiveData()));
  Network::GetInstance()->AddClient(client);
}

void	TcpServer::SlotSocketError(void)
{
  QTcpSocket *s = qobject_cast<QTcpSocket *>(QObject::sender());

  QSharedPointer<Client> client = Network::GetInstance()->FindClientFromSocket(s);
  Network::GetInstance()->RemoveClient(client);
}

void	TcpServer::SlotSocketDisconnected(void)
{
  QTcpSocket *s = qobject_cast<QTcpSocket *>(QObject::sender());

  QSharedPointer<Client> client = Network::GetInstance()->FindClientFromSocket(s);
  Network::GetInstance()->RemoveClient(client);
}

void	TcpServer::SlotReceiveData(void)
{
  QTcpSocket *s = qobject_cast<QTcpSocket *>(QObject::sender());

  QSharedPointer<Client> client = Network::GetInstance()->FindClientFromSocket(s);
  QtConcurrent::run(client.data(), &Client::ReceiveData);
}
