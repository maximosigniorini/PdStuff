/* Definition of EXPORT, needed for functions which must be explicitly exported
(global visibility) when compiler flag -fvisibility=hidden is set. */

#ifndef export_h
#define export_h

#ifdef __GNUC__
#define EXPORT __attribute__((visibility("default")))
#endif
#ifndef EXPORT
#define EXPORT    // empty definition for other cases
#endif

#endif // ifndef export_h
