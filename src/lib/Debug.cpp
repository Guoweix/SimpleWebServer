#include "Debug.hpp"


#ifdef DEBUG
    bool Debug::DebugFlag=true;
#else
    bool Debug::DebugFlag=false;
#endif


Debug debug;
