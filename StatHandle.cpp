
#include "StatHandle.h"
#include <string.h>

StatHandle * StatHandle::allStats_;
int StatHandle::numStats_;
StatHandle ** StatHandle::handles_;

StatHandle::StatHandle( char const * name ) : name_( name ) {
  ++numStats_;
  next_ = allStats_;
  allStats_ = this;
}

void StatHandle::doInit( int max ) {
  assert( numStats_ <= max );
  //  You must not have called INIT_ALL_STATS before this
  //  (i e, you can only init stats once).
  assert( handles_ == 0 );
  handles_ = new StatHandle *[ numStats_ ];
  int i = numStats_;
  StatHandle * sh = allStats_;
  while( i > 0 ) {
    --i;
    handles_[i] = sh;
    sh->ix_ = i;
    sh = sh->next_;
  }
}

StatHandle & StatHandle::byName( char const * name )
{
  //  You must have called INIT_ALL_STATS to use this
  assert( handles_ != 0 );
  StatHandle * sh = allStats_;
  while( sh ) {
    if( !strcmp( name, sh->name_ ) ) {
      break;
    }
    sh = sh->next_;
  }
  assert( sh != 0 );  //  Illegal to use a name that doesn't exist.
  return *sh;         //  NULL reference if we go past the end!
}

