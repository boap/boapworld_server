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
    Log::Warning("Trying to remove inexsistant client");
}

QSharedPointer<Client> Network::FindClientFromSocket(const QTcpSocket *s)
{
  QMutexLocker locker(&_mutex);

  if (_clients.contains(s))
    return (_clients.value(s));
  return (QSharedPointer<Client>());
}
