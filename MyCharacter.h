
#if !defined( MyCharacter_h )
#define MyCharacter_h

#include "MyStats.h"
#include <string.h>

class MyCharacter : public StatAccessor {
  public:
    MyCharacter() : StatAccessor( myStats_ ) {
      memset( myStats_, 0, sizeof( myStats_ ) );
    }
    void doStuff();
    StatType myStats_[ MY_MAX_NUM_STATS ];
};


#endif   // MyCharacter_h
