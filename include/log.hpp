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
  static void	Info(const QString &s);
  static void	Warning(const QString &s);
  static void	Critical(const QString &s);
};

#endif
