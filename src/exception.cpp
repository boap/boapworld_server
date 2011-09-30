#include	"exception.hpp"
#include	<QString>

Exception::Exception(const QString &str)
{
  _msg = str;
}

Exception::~Exception(void)
{
}

const QString & Exception::GetMessage(void) const
{
  return (_msg);
}
