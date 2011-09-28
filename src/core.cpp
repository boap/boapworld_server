#include	"core.hpp"
#include	"network.hpp"
#include	"log.hpp"
#include	<QThread>
#include	<QThreadPool>

Core *Core::_instance = NULL;

Core::Core(void)
{
  Log::Info("Server will run with " + QString::number(QThread::idealThreadCount())+ " threads.");
  // Tells the thread pool to never unspawn threads.
  QThreadPool::globalInstance()->setExpiryTimeout(-1);
  _network = Network::GetInstance();
  _network->BindServer();
}

Core::Core(__attribute__((unused))const Core &ref)
{
  
}

Core::~Core(void)
{

}

Core	*Core::GetInstance(void)
{
  if (_instance)
    return (_instance);
  _instance = new Core();
  return (_instance);
}
