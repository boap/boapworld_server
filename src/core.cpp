#include	"core.hpp"

Core *Core::_instance = NULL;

Core::Core(void)
{
  
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
