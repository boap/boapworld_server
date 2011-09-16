#include <iostream>
#include <QString>
#include <QMutex>
#include "log.hpp"

QMutex Log::_mutex(QMutex::Recursive);

Log::Log(void)
{
  
}

Log::Log(__attribute__((unused))const Log &ref)
{
  
}

Log::~Log(void)
{

}

void    Log::Lock(void)
{
  _mutex.lock();
}

void    Log::Unlock(void)
{
  _mutex.unlock();
}

void    Log::SetColor(int color)
{
  std::cout << "\033[" << color << "m";
}

void    Log::ResetColor(void)
{
  std::cout << "\033[37m" << std::endl;
}

void	Log::Debug(const QString &s)
{
  _mutex.lock();
  SetColor(Color::White);
  std::cout << s.toStdString();
  ResetColor();
  _mutex.unlock();
}

void	Log::Warning(const QString &s)
{
  _mutex.lock();
  SetColor(Color::Yellow);
  std::cout << s.toStdString();
  ResetColor();
  _mutex.unlock();
}

void	Log::Critical(const QString &s)
{
  _mutex.lock();
  SetColor(Color::Red);
  std::cout << s.toStdString();
  ResetColor();
  _mutex.unlock();
}
