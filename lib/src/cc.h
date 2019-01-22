#ifndef CC_H

#ifdef __CYGWIN__
#define HIDDEN
#else
#define HIDDEN  __attribute((visibility("hidden")))
#endif

#endif  /* CC_H */
