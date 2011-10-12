#ifndef	_NETWORK_HPP_
#define	_NETWORK_HPP_

#include <QMutex>
#include <QList>
#include <QTimer>
#include <QSharedPointer>
#include "client.hpp"
#include "tcpserver.hpp"
#include "packet.hpp"
#include "operators.hpp"

class   Network : public QObject
{
  Q_OBJECT
private:
  Network(int port = 4242);
  Network(const Network &ref);
  static Network        *_instance;
  static QMutex		_mutex;
  
  TcpServer             _server;
  int			_port;
  QHash<const QTcpSocket *, QSharedPointer<Client> >		_clients;
  QList<t_queued>	_queue;
  QTimer		_queueTimer;

public:
  ~Network();
  static Network	*GetInstance(void);
  static void		Lock(void) { _mutex.lock(); };
  static void		Unlock(void) { _mutex.unlock(); };

  bool			BindServer(void);
  void			AddClient(QSharedPointer<Client> &client);
  void			RemoveClient(const QTcpSocket *sock);
  QSharedPointer<Client> FindClientFromSocket(const QTcpSocket *s);

  bool			HasClientWithUsername(const QString &ref) const;
  /**
   * Prepare the packet by filling the ByteArray.
   * @param data
   * @param packet
   * @param opcode
   */
  template	<typename PacketType>
  static void		PrepPacket(QSharedPointer<QByteArray> &data, const PacketType &packet, qint16 opcode)
  {
    QDataStream   s(data.data(), QIODevice::WriteOnly);

    s << (qint32) 0;
    s << opcode;
    s << packet;
    s.device()->seek(0);
    s << (qint32) (data->size() - (sizeof (qint32) + sizeof (qint16)));
  }

  void		SendPacket(QSharedPointer<QByteArray> &data, QTcpSocket *s);
								 
public slots:
  void			FlushQueue(void);
};

#endif
