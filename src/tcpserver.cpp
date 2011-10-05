#include "tcpserver.hpp"
#include "log.hpp"
#include "network.hpp"
#include "exception.hpp"
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
  QTcpSocket *sock = new QTcpSocket;
  QSharedPointer<Client> client = Client::create(sock);

  if (!sock->setSocketDescriptor(s, QAbstractSocket::ConnectedState,
				 QIODevice::ReadWrite))
    {
      Log::Critical("Cannot set socket descriptor");
      return;
    }
  QObject::connect(sock, SIGNAL(disconnected()), this, SLOT(SlotSocketDisconnected()));
  QObject::connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotSocketError()));
  QObject::connect(sock, SIGNAL(readyRead()), this, SLOT(SlotReceiveData()));
  Network::GetInstance()->AddClient(client);
}

void	TcpServer::CallClientReceiveData(QSharedPointer<Client> c)
{
  if (!c.data())
    {
      Log::Warning("Call CallClientReceiveData with a NULL client.");
      return;
    }
  try
    {
      c->ReceiveData();
    }
  catch (const Exception e)
    {
      Log::Critical("An exception has been raised: " + e.GetMessage());
    }
}

void	TcpServer::SlotSocketError(void)
{
  QTcpSocket *s = qobject_cast<QTcpSocket *>(QObject::sender());
  
  Network::GetInstance()->RemoveClient(s);
}

void	TcpServer::SlotSocketDisconnected(void)
{
  QTcpSocket *s = qobject_cast<QTcpSocket *>(QObject::sender());

  Network::GetInstance()->RemoveClient(s);
}

void	TcpServer::SlotReceiveData(void)
{
  QTcpSocket *s = qobject_cast<QTcpSocket *>(QObject::sender());

  QSharedPointer<Client> client = Network::GetInstance()->FindClientFromSocket(s);
  QtConcurrent::run(TcpServer::CallClientReceiveData, client);
}
