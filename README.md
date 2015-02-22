
# libstats
A library to manage statistics for role playing game implementation.

September 12, 2004
Copyright 2004 Jon Watte


LIBSTATS AND THE SAMPLE CODE IS PUT UNDER THE MIT LICENSE, AND MAY 
BE USED BY YOU FOR COMMERCIAL OR OTHER PURPOSES FREE OF CHARGE, 
PROVIDED THAT CERTAIN CONDITIONS ON SUCH USE ARE MET. ONE SUCH 
CONDITION IS THAT YOU ACCEPT THAT THE LIBRARY IS PROVIDED AS-IS, 
FREE OF CHARGE, WITHOUT ANY GUARANTEE OR WARRANTY OF MERCHANTABILITY 
OR FITNESS FOR A PARTICULAR PURPOSE. FURTHERMORE, YOU ACCEPT TO 
BEAR ANY LIABILITY ARISING OUT OF YOUR DIRECT OR INDIRECT USE OF 
THE LIBRARY AND THE SAMPLE CODE, INCLUDING DIRECT, INDIRECT, SPECIAL 
OR CONSEQUENTIAL DAMAGES.


"libstats" is a simple implementation of a system to implement stats 
in a role-playing game. The system allows you to define stats in a 
single C++ file, and then reference them and use them in other files. 
It furthermore allows you to add a new kind of stat, and the only 
files that need to be re-compiled are the files that use the new 
stat, and the file that defines all stats (which is a .cpp, not a 
.h file!).

This project compiles a sample program which minimally excercises 
the library to make sure it works right.

The value of stats is currently an integer -- you can change the 
typedef of StatType in StatHandle.h to change this.

To access stats, you either use operator() on a StatHandle, in 
which case the argument needs to be derived from StatAccessor, or 
you call StatHandle::operator int(), for example, by using the 
StatHandle as an index in an array subscript.

You can get a StatHandle statically by forwad declaring it using 
the USE_STAT_HANDLE() macro, or by index using StatHandle::byIndex(), 
or by name using StatHandle::byName().


The files main.cpp, MyStats.cpp, MyCharacter.cpp, MyStats.h and 
MyCharacter.h are part of the test application, although they may 
provide an easy way to start your own project off (they're pretty 
small, so there's not much there). Pay attention to the way that 
MyCharacter derives from StatAccessor and initializes it in its 
constructor.

The files StatHandle.h and StatHandle.cpp are the actualy "libstats" 
library.

To define a new stat, you need to add the macro DEFINE_STAT_HANDLE() 
to one C++ file in your project (like MyStats.cpp in this sample 
project). Use the actual name you want to use for the stat as the 
argument for the macro.

To use a stat in another C++ file, you use the macro USE_STAT_HANDLE() 
in that file, giving the same name you gave to DEFINE_STAT_HANDLE(). 
If you spell it wrong, the linker will tell you by giving you a link 
error.

You should define a function called InitAllStats() (or something 
similar) at the bottom of the C++ file where you put all your 
DEFINE_STAT_HANDLE() macros. This function should call 
INIT_STAT_HANDLES() passing the maximum number of stat handles you 
will accept being registered. This should during development be 
bigger than the number you currently have, so that you can add more 
stats without having to re-compile all files depending on your 
character class (stat container). Libstats will not allocate more 
memory than the actual number of stat handles declared, so you can 
make this really big, as long as your character class can take it 
(or you use a dynamically allocated array of StatTypes using the 
StatHandle::numStats() function to get the size).

Your main() should call InitAllStats() before actually using any 
stat handle. This means that you should not use stat handles from 
static constructors -- the reason for this is that static construction 
order is not guaranteed, and you want to avoid bugs. No, really, you 
do!

Please send any feedback to jwatte-libstats (at) mindcontrol.org 
and perhaps there might be an update some day. But, seeing how 
small and specialized this library is, probably there won't be any.
