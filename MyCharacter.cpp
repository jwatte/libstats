
#include "MyCharacter.h"

USE_STAT_HANDLE( Wisdom );

void MyCharacter::doStuff()
{
  myStats_[Wisdom] = 10;
  StatHandle::byName( "Strength" )( *this ) = 37;
}
