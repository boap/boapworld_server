#include <iostream>
#include <QString>
#include "log.hpp"

Log::Log(void)
{
  
}

Log::Log(__attribute__((unused))const Log &ref)
{
  
}

Log::~Log(void)
{

}

void	Log::Debug(const QString &s)
{
  std::cout << s.toStdString() << std::endl;
}
