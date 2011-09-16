#ifndef	_LOG_H_
#define _LOG_H_

class QString;
class QMutex;

class Log
{
private:
  Log(void);
  Log(const Log &ref);
  static void	SetColor(int color);
  static void	ResetColor(void);
  static QMutex	_mutex;

public:
  ~Log(void);
  static void	Lock(void);
  static void	Unlock(void);

  static void	Debug(const QString &s);
  static void	Warning(const QString &s);
  static void	Critical(const QString &s);
};

/*!
 * Some define for colors
 */
namespace Color
{
  enum
  {
    Black               = 30,
    Red                 = 31,
    Green               = 32,
    Yellow              = 33,
    Blue                = 34,
    White               = 37
  };
};

#endif
