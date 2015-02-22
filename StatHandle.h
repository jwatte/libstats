
#if !defined( StatHandle_h )
#define StatHandle_h

#include <assert.h>

typedef int StatType;

//  Your class must provide a conversion operator to 
//  StatAccessor instance, or be derived from StatAccessor.
//  This library could be re-written using template magic 
//  to avoid StatAccessor. Or StatHandle could get an 
//  operator int() to just return the index, and you deal 
//  with indexing yourself.
class StatAccessor {
  public:
    StatAccessor( StatType * base ) : base_( base ) {}
    StatType & operator[]( int i ) {
      return base_[ i ];
    }
    StatType operator[]( int i ) const {
      return base_[ i ];
    }
  private:
    StatType * base_;
};

class StatHandle {
  public:

    //  StatHandle constructor should only be called by the 
    //  DEFINE_STAT_HANDLE macro.
    StatHandle( char const * name );

    inline static int numStats() {
      //  You must have called INIT_ALL_STATS to use this
      assert( handles_ != 0 );
      return numStats_;
    }

    //  If you want to do stat access yourself, the stat index is 
    //  available to you. (myArray[ StatName ] should work)
    inline operator int() const {
      //  You must have called INIT_ALL_STATS to use this
      assert( handles_ != 0 );
      return ix_;
    }

    //  Get the name of a stat
    inline char const * name() const {
      return name_;
    }

    //  I could turn this into a template type, for different stat types.
    //  meanwhile, they're all integers.
    inline StatType & operator()( StatAccessor & a ) const {
      //  You must have called INIT_ALL_STATS to use this
      assert( handles_ != 0 );
      return a[ ix_ ];
    }

    //  Given an index in [0,numStats_), return a reference to the 
    //  actual stat handle. This can access data on an object of 
    //  your choice, using operator().
    static StatHandle & byIndex( int ix ) {
      assert( ix >= 0 && ix < numStats_ );
      //  this will crash if stats are not inited
      return *handles_[ix];
    }
    
    //  You can look up a stat by name -- this is slow, so it's 
    //  mostly used for file I/O, and/or when you cache the results.
    static StatHandle & byName( char const * name );

    //  doInit() should only be called by INIT_STAT_HANDLES, from 
    //  a function in your global stat definition file (to get rid 
    //  of linker optimizations that may strip global instances).
    static void doInit( int max );

  private:
    char const * name_;
    StatHandle * next_;
    int ix_;
    static StatHandle * allStats_;
    static int numStats_;
    static StatHandle ** handles_;
};


#define USE_STAT_HANDLE(x) extern StatHandle x
#define DEFINE_STAT_HANDLE(x) StatHandle x ( #x );
#define INIT_STAT_HANDLES(n) StatHandle::doInit( n )


#endif  //  StatHandle_h

