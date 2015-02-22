
#include "MyCharacter.h"

#include <stdio.h>

USE_STAT_HANDLE( Gullibility );

extern void InitAllStats( int max );

int main()
{
  InitAllStats( MY_MAX_NUM_STATS );
  MyCharacter ch;
  ch.doStuff();
  Gullibility( ch ) = 3;
  printf( "Gullibilty (method 1): %d\n", Gullibility( ch ) );
  for( int i = 0; i < StatHandle::numStats(); ++i ) {
    printf( "%s (method 2): %d\n", StatHandle::byIndex( i ).name(), StatHandle::byIndex( i )( ch ) );
  }
  printf( "Wisdom (method 3): %d\n", StatHandle::byName( "Wisdom" )( ch ) );
  return 0;
}
