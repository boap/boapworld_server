#include "client.hpp"
#include "log.hpp"
#include "packet.hpp"
#include "operators.hpp"
#include "db/client.hpp"
#include <QThread>

/* Method pointer initialization */
void (Client::*Client::packetHandler[Op::handledOpcodeMax - Op::handledOpcodeMin + 1])(QByteArray &data);


QSharedPointer<Client> Client::create(QTcpSocket *s)
{
  Client::packetHandler[Op::CMSG_TRY_AUTHENTIFICATION] = &Client::Handle_CMSG_TRY_AUTHENTIFICATION;
  Client::packetHandler[Op::SMSG_AUTHENTIFICATION_RESPONSE] = &Client::Handle_STFU;

  QSharedPointer<Client> ptr(new Client(s));
  ptr->_this = ptr.toWeakRef();
  return (ptr);
}

Client::Client(QTcpSocket *sock)
{
  Log::Debug("New client created!");
  _socket = sock;
  _state = Client::CONNECTED;
  _packetSize = -1;
  _opcode = -1;
}

Client::Client(__attribute__((unused)) const Client &ref)
{
  Log::Critical("New client created per copy!");
}

Client::~Client()
{
  QMutexLocker locker(&_mutex);
  Log::Debug("Client destroyed!");
  _socket->deleteLater();
}

const QTcpSocket *Client::GetSocket(void) const
{
  QMutexLocker locker(&_mutex);
  return (_socket);
}

void	Client::ReceiveData(void)
{
  QMutexLocker locker(&_mutex);
  QDataStream   stream(_socket);
  QByteArray    data;

  Log::Debug("Data received.");
  
  stream.setVersion(QDataStream::Qt_4_0);
  while (_socket->bytesAvailable())
    {
      if (_packetSize == -1)
        {
          if (_socket->bytesAvailable() < (qint64)sizeof (qint32))
            return;
          stream >> _packetSize;
        }
      if (_opcode == -1)
        {
          if (_socket->bytesAvailable() < (qint64)sizeof (qint16))
            return;
          stream >> _opcode;
        }
      if (_socket->bytesAvailable() < _packetSize)
        return;
      data = _socket->read(_packetSize);

      if (_opcode <= Op::handledOpcodeMax
      	  && _opcode >= Op::handledOpcodeMin)
	(this->*packetHandler[_opcode])(data);
      else
	this->Handle_STFU(data);
      _opcode = -1;
      _packetSize = -1;
    }
  Log::Debug("done!");
}

void	Client::Handle_STFU(QByteArray &data)
{
  Log::Warning("Opcode not handled by server. Probably a server opcode.");
}

void	Client::Handle_CMSG_TRY_AUTHENTIFICATION(QByteArray &data)
{
  t_2strings pack;

  //  Log::Debug("Handling CMSG_TRY_AUTHENTIFICATION");  
  
  //  data >> pack;
  //  DB::Client toto;
  //  Log::Debug("Client try to connect with username \"" + pack.str1 + "\" and" +
  //	     " password \"" + pack.str2 + "\"");
}
