#include "client.hpp"
#include "log.hpp"

/* Method pointer initialization */
void (Client::*Client::packetHandler[Op::handledOpcodeMax - Op::handledOpcodeMin + 1])(QByteArray &data) =
{&Client::Handle_CMSG_TRY_AUTHENTIFICATION};

QSharedPointer<Client> Client::create(QTcpSocket *s)
{
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
	Log::Warning("Wrong opcode");
      _opcode = -1;
      _packetSize = -1;
    }
  Log::Debug("done!");
}

void	Client::Handle_CMSG_TRY_AUTHENTIFICATION(QByteArray &data)
{
  Log::Debug("Handling CMSG_TRY_AUTHENTIFICATION");
}
