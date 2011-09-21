#ifndef	_CORE_HPP_
#define _CORE_HPP_

class   Network;

class   Core
{
private:
  Core(void);
  Core(const Core &ref);
  static Core   *_instance;
  
  Network       *_network;
  
public:
  ~Core(void);
  static Core  *GetInstance(void);
};

#endif
