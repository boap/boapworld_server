#ifndef	__EXCEPTION_HPP__
#define	__EXCEPTION_HPP__

#include <QString>

class Exception
{
public:
  Exception(const QString &str);
  ~Exception(void);

  const QString &	GetMessage(void) const;
private:
  QString	_msg;
};

#endif
