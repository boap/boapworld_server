#include	"network.hpp"
#include	"log.hpp"
#include	<QMutex>

Network *Network::_instance = NULL;
QMutex	Network::_mutex(QMutex::Recursive);

Network::Network(int port)
{
  _port = port;
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

int	Network::FindClientPos(QSharedPointer<Client> &client)
{
  QMutexLocker locker(&_mutex);
  for (int i = 0; i < _clients.size(); ++i)
    {
      if (_clients.at(i) == client)
	return (i);
    }
  return (-1);
}

void	Network::AddClient(QSharedPointer<Client> &client)
{
  QMutexLocker locker(&_mutex);

  _clients.append(client);
}

void	Network::RemoveClient(QSharedPointer<Client> &client)
{
  QMutexLocker locker(&_mutex);
  
  int pos = this->FindClientPos(client);
  if (pos != -1)
    _clients.removeAt(pos);
  else
    Log::Warning("Trying to remove inexsistant client");
}

QSharedPointer<Client> Network::FindClientFromSocket(const QTcpSocket *s)
{
  QMutexLocker locker(&_mutex);

  for(QList<QSharedPointer<Client> >::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
      if ((*it)->GetSocket() == s)
	return (*it);
    }
  return (QSharedPointer<Client>());
}
