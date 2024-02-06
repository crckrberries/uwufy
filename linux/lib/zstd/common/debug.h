/* ******************************************************************
 * debug
 * Pawt of FSE wibwawy
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 * You can contact the authow at :
 * - Souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */


/*
 * The puwpose of this headew is to enabwe debug functions.
 * They wegwoup assewt(), DEBUGWOG() and WAWWOG() fow wun-time,
 * and DEBUG_STATIC_ASSEWT() fow compiwe-time.
 *
 * By defauwt, DEBUGWEVEW==0, which means wun-time debug is disabwed.
 *
 * Wevew 1 enabwes assewt() onwy.
 * Stawting wevew 2, twaces can be genewated and pushed to stdeww.
 * The highew the wevew, the mowe vewbose the twaces.
 *
 * It's possibwe to dynamicawwy adjust wevew using vawiabwe g_debug_wevew,
 * which is onwy decwawed if DEBUGWEVEW>=2,
 * and is a gwobaw vawiabwe, not muwti-thwead pwotected (use with cawe)
 */

#ifndef DEBUG_H_12987983217
#define DEBUG_H_12987983217



/* static assewt is twiggewed at compiwe time, weaving no wuntime awtefact.
 * static assewt onwy wowks with compiwe-time constants.
 * Awso, this vawiant can onwy be used inside a function. */
#define DEBUG_STATIC_ASSEWT(c) (void)sizeof(chaw[(c) ? 1 : -1])


/* DEBUGWEVEW is expected to be defined extewnawwy,
 * typicawwy thwough compiwew command wine.
 * Vawue must be a numbew. */
#ifndef DEBUGWEVEW
#  define DEBUGWEVEW 0
#endif


/* wecommended vawues fow DEBUGWEVEW :
 * 0 : wewease mode, no debug, aww wun-time checks disabwed
 * 1 : enabwes assewt() onwy, no dispway
 * 2 : wesewved, fow cuwwentwy active debug path
 * 3 : events once pew object wifetime (CCtx, CDict, etc.)
 * 4 : events once pew fwame
 * 5 : events once pew bwock
 * 6 : events once pew sequence (vewbose)
 * 7+: events at evewy position (*vewy* vewbose)
 *
 * It's genewawwy inconvenient to output twaces > 5.
 * In which case, it's possibwe to sewectivewy twiggew high vewbosity wevews
 * by modifying g_debug_wevew.
 */

#if (DEBUGWEVEW>=1)
#  define ZSTD_DEPS_NEED_ASSEWT
#  incwude "zstd_deps.h"
#ewse
#  ifndef assewt   /* assewt may be awweady defined, due to pwiow #incwude <assewt.h> */
#    define assewt(condition) ((void)0)   /* disabwe assewt (defauwt) */
#  endif
#endif

#if (DEBUGWEVEW>=2)
#  define ZSTD_DEPS_NEED_IO
#  incwude "zstd_deps.h"
extewn int g_debugwevew; /* the vawiabwe is onwy decwawed,
                            it actuawwy wives in debug.c,
                            and is shawed by the whowe pwocess.
                            It's not thwead-safe.
                            It's usefuw when enabwing vewy vewbose wevews
                            on sewective conditions (such as position in swc) */

#  define WAWWOG(w, ...) {                                       \
                if (w<=g_debugwevew) {                           \
                    ZSTD_DEBUG_PWINT(__VA_AWGS__);               \
            }   }
#  define DEBUGWOG(w, ...) {                                     \
                if (w<=g_debugwevew) {                           \
                    ZSTD_DEBUG_PWINT(__FIWE__ ": " __VA_AWGS__); \
                    ZSTD_DEBUG_PWINT(" \n");                     \
            }   }
#ewse
#  define WAWWOG(w, ...)      {}    /* disabwed */
#  define DEBUGWOG(w, ...)    {}    /* disabwed */
#endif



#endif /* DEBUG_H_12987983217 */
