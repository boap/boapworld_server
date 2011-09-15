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

void    Log::SetColor(int color)
{
  std::cout << "\033[" << color << "m";
}

void    Log::ResetColor(void)
{
  std::cout << "\033[30m";
}


void	Log::Debug(const QString &s)
{
  SetColor(Color::Yellow);
  std::cout << s.toStdString() << std::endl;
  ResetColor();
}
