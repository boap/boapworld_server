#ifndef	_NETWORK_HPP_
#define	_NETWORK_HPP_

#include <QMutex>
#include <QList>
#include <QSharedPointer>
#include "client.hpp"
#include "tcpserver.hpp"

class   Network : public QObject
{
private:
  Network(int port = 4242);
  Network(const Network &ref);
  static Network        *_instance;
  static QMutex		_mutex;
  
  TcpServer             _server;
  int			_port;
  QHash<const QTcpSocket *, QSharedPointer<Client> >		_clients;

public:
  ~Network();
  static Network	*GetInstance(void);
  static void		Lock(void) { _mutex.lock(); };
  static void		Unlock(void) { _mutex.unlock(); };

  bool			BindServer(void);
  void			AddClient(QSharedPointer<Client> &client);
  void			RemoveClient(const QTcpSocket *sock);
  QSharedPointer<Client> FindClientFromSocket(const QTcpSocket *s);
								 
public slots:
  void			SlotNewConnection(void);
};

#endif
