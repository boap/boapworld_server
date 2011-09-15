#ifndef	_CORE_HPP_
#define _CORE_HPP_

#include <stdlib.h>

class   Core
{
private:
  Core(void);
  Core(const Core &ref);
  static Core  *_instance;
  
public:
  ~Core(void);
  static Core  *GetInstance(void);
  

};

#endif
