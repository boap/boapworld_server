#ifndef	_CLIENT_HPP_
#define	_CLIENT_HPP_

#include <QMutex>
#include <QTcpSocket>
#include <QSharedPointer>
#include "opcode.hpp"

class   Client
{
public:
    ~Client(void);

    /**
     * A factory method to create a new client.
     * @param socket
     * @return A client
     */
    static QSharedPointer<Client> create(QTcpSocket *sock);

    /**
     * This is a static array of methods' pointers to handler packet based
     * on their opcodes.
     */
    static void (Client::*packetHandler[Op::handledOpcodeMax - Op::handledOpcodeMin + 1])(QByteArray &data);
    
    const QTcpSocket *GetSocket(void) const;
  const QString		&GetUsername(void) const;

    /**
     * This method is called in a worker thread by the TcpServer whenever
     * new data are available for reading on the client's socket.
     */
    void		ReceiveData(void);

    /**
     * An enumeration to describe connection state of the client.
     */
    enum State
    {
        CONNECTED = 0x01, // Connection established but not logged in
        LOGGED    = 0x02,
    } ;

    /**
     * This method locks the client's mutex.
     */
    void		Lock(void)
    {
        _mutex.lock();
    }

    /**
     * This method unlocks the client's mutex.
     */
    void		Unlock(void)
    {
        _mutex.unlock();
    }


    /* Network packet handlers */
    
    /**
     * Handle data for opcode CMSG_TRY_AUTHENTIFICATION (ie a client is trying
     * to log in).
     * @param data
     */
    void		Handle_CMSG_TRY_AUTHENTIFICATION(QByteArray &data);
    
    /**
     * This is the default method for packet with non-valid opcode.
     * @param data
     */
    void		Handle_STFU(QByteArray &data);

private:
    Client(QTcpSocket *sock);
    Client(const Client &ref);

    mutable QMutex        _mutex;
    QTcpSocket            *_socket;
    State                 _state;
    QString               _username;

    qint32                _packetSize;
    qint16                _opcode;
    QWeakPointer<Client>  _this;

} ;

#endif
