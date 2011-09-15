#ifndef	_LOG_H_
#define _LOG_H_

class QString;

class Log
{
private:
  Log(void);
  Log(const Log& ref);

public:
  ~Log(void);
  static void  Debug(const QString &s);
};

#endif
