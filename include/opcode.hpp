#ifndef		_OPCODE_HPP_
#define		_OPCODE_HPP_

namespace Op
{
  const int handledOpcodeMin = 0x0001;
  const int handledOpcodeMax = 0x0002;

  enum
    {
      /**
       * Send by client when trying to log in
       * @notes it uses a t_2strings
       */
      CMSG_TRY_AUTHENTIFICATION                 = (qint16) 0x0001,
      /**
       * Response to the authentification attemps.
       * @notes it uses a qint8.
       */
      SMSG_AUTHENTIFICATION_RESPONSE            = (qint16) 0x0002 
    };
  
  namespace Connection
  {
    enum
      {
	WRONG_USERNAME                  = (qint8) 0x0001,
	WRONG_PASSWORD                  = (qint8) 0x0002,
	ALREADY_LOGGED_IN               = (qint8) 0x0003,
	OK                              = (qint8) 0x0004
      };
  };

};

#endif
