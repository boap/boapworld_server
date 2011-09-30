#ifndef	_TCPSERVER_HPP_
#define _TCPSERVER_HPP_

#include <QTcpServer>
#include <QSharedPointer>
#include <QTcpSocket>

class Client;

class   TcpServer : public QTcpServer
{
  Q_OBJECT

private:
  TcpServer(const TcpServer &ref);

  void	incomingConnection(int s);

public:
  TcpServer(void);
  ~TcpServer(void);

  /**
   * It'll call the Client::ReceiveData method.
   * The purpose of this function, which is run in a thread
   * is to try/catch the Client::ReceiveData method.
   */
  static void CallClientReceiveData(Client *);

public slots:
  void SlotReceiveData(void);
  void SlotSocketError(void);
  void SlotSocketDisconnected(void);
};

#endif
