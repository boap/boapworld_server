#ifndef	_TCPSERVER_HPP_
#define _TCPSERVER_HPP_

#include <QTcpServer>
#include <QSharedPointer>
#include <QTcpSocket>

class   TcpServer : public QTcpServer
{
  Q_OBJECT

private:
  TcpServer(const TcpServer &ref);

  void	incomingConnection(int s);

public:
  TcpServer(void);
  ~TcpServer(void);

public slots:
  void SlotReceiveData(void);
  void SlotSocketError(void);
  void SlotSocketDisconnected(void);
};

#endif
