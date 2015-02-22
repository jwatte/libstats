
#include "MyStats.h"

DEFINE_STAT_HANDLE( Strength );
DEFINE_STAT_HANDLE( Wisdom );
DEFINE_STAT_HANDLE( Gullibility );

void InitAllStats( int max )
{
  INIT_STAT_HANDLES( max );
}

