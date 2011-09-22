#ifndef		_OPCODE_HPP_
#define		_OPCODE_HPP_

namespace Op
{
  const int handledOpcodeMin = 0x0001;
  const int handledOpcodeMax = 0x0001;

  enum
    {
      CMSG_TRY_AUTHENTIFICATION = (qint16) 0x0001
    };
  
  namespace Connection
  {
    enum
      {
	BAD_PASSWORD                  = (qint8) 0x0001,
	ALREADY_LOGGED_IN             = (qint8) 0x0002,
	OK                            = (qint8) 0x0003
      };
  };

};

#endif
