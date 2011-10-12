#include        "network.hpp"
#include        "log.hpp"
#include        "client.hpp"
#include        <QMutex>
#include	<QThread>

Network *Network::_instance = NULL;
QMutex	Network::_mutex(QMutex::Recursive);

Network::Network(int port)
{
  _port = port;
  _queueTimer.setInterval(0);
  _queueTimer.setSingleShot(false);
  QObject::connect(&_queueTimer, SIGNAL(timeout()), this, SLOT(FlushQueue()));
  _queueTimer.start();
}

Network::Network(__attribute__((unused)) const Network& ref) : QObject()
{
  
}

Network::~Network(void)
{

}

Network	*Network::GetInstance(void)
{
  QMutexLocker	locker(&_mutex);

  if (_instance)
    return (_instance);
  _instance = new Network();
  return (_instance);
}

bool	Network::BindServer(void)
{
  QMutexLocker	locker(&_mutex);

  if (!_server.listen(QHostAddress::Any, _port))
    {
      Log::Critical("Cannot bind server to port " + QString::number(_port));
      return (false);
    }
  Log::Debug("Server is listening");
  return (true);
}

void	Network::AddClient(QSharedPointer<Client> &client)
{
  QMutexLocker locker(&_mutex);

  _clients.insert(client->GetSocket(), client);
}

void	Network::RemoveClient(const QTcpSocket *client_sock)
{
  QMutexLocker locker(&_mutex);
  
  if (_clients.contains(client_sock))
    _clients.remove(client_sock);
  else
    Log::Warning("Trying to remove non-existing client.");
}

QSharedPointer<Client> Network::FindClientFromSocket(const QTcpSocket *s)
{
  QMutexLocker locker(&_mutex);

  if (_clients.contains(s))
    return (_clients.value(s));
  return (QSharedPointer<Client>());
}

bool		Network::HasClientWithUsername(const QString &ref) const
{
  QMutexLocker locker(&_mutex);

  for (QHash<const QTcpSocket *, QSharedPointer<Client> >::const_iterator it = _clients.constBegin();
       it != _clients.end(); ++it)
    {
      if ((*it)->GetUsername() == ref)
	return (true);
    }
  return (false);
}

void		Network::SendPacket(QSharedPointer<QByteArray> &data, QTcpSocket *s)
{
  QMutexLocker	lock(&_mutex);
  t_queued	p;
    
  p.sock = s;
  p.data = data;
  _queue.append(p);
}

void		Network::FlushQueue()
{
  QMutexLocker lock(&_mutex);

  for (QList<t_queued>::iterator it = _queue.begin(); it != _queue.end(); ++it)
    {
      Log::Debug("Sending packet");
      QSharedPointer<Client>	c = FindClientFromSocket((*it).sock);
      if (c)
	{
	  c->Lock();
	  (*it).sock->write(*((*it).data.data()));
	  c->Unlock();
	}
      _queue.removeAll(*it);
    }
}
