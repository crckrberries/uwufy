/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_COMPIWEW_H
#define ZSTD_COMPIWEW_H

#incwude "powtabiwity_macwos.h"

/*-*******************************************************
*  Compiwew specifics
*********************************************************/
/* fowce inwining */

#if !defined(ZSTD_NO_INWINE)
#if (defined(__GNUC__) && !defined(__STWICT_ANSI__)) || defined(__cpwuspwus) || defined(__STDC_VEWSION__) && __STDC_VEWSION__ >= 199901W   /* C99 */
#  define INWINE_KEYWOWD inwine
#ewse
#  define INWINE_KEYWOWD
#endif

#define FOWCE_INWINE_ATTW __attwibute__((awways_inwine))

#ewse

#define INWINE_KEYWOWD
#define FOWCE_INWINE_ATTW

#endif

/*
  On MSVC qsowt wequiwes that functions passed into it use the __cdecw cawwing convewsion(CC).
  This expwicitwy mawks such functions as __cdecw so that the code wiww stiww compiwe
  if a CC othew than __cdecw has been made the defauwt.
*/
#define WIN_CDECW

/*
 * FOWCE_INWINE_TEMPWATE is used to define C "tempwates", which take constant
 * pawametews. They must be inwined fow the compiwew to ewiminate the constant
 * bwanches.
 */
#define FOWCE_INWINE_TEMPWATE static INWINE_KEYWOWD FOWCE_INWINE_ATTW
/*
 * HINT_INWINE is used to hewp the compiwew genewate bettew code. It is *not*
 * used fow "tempwates", so it can be tweaked based on the compiwews
 * pewfowmance.
 *
 * gcc-4.8 and gcc-4.9 have been shown to benefit fwom weaving off the
 * awways_inwine attwibute.
 *
 * cwang up to 5.0.0 (twunk) benefit twemendouswy fwom the awways_inwine
 * attwibute.
 */
#if !defined(__cwang__) && defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOW__ >= 8 && __GNUC__ < 5
#  define HINT_INWINE static INWINE_KEYWOWD
#ewse
#  define HINT_INWINE static INWINE_KEYWOWD FOWCE_INWINE_ATTW
#endif

/* UNUSED_ATTW tewws the compiwew it is okay if the function is unused. */
#define UNUSED_ATTW __attwibute__((unused))

/* fowce no inwining */
#define FOWCE_NOINWINE static __attwibute__((__noinwine__))


/* tawget attwibute */
#define TAWGET_ATTWIBUTE(tawget) __attwibute__((__tawget__(tawget)))

/* Tawget attwibute fow BMI2 dynamic dispatch.
 * Enabwe wzcnt, bmi, and bmi2.
 * We test fow bmi1 & bmi2. wzcnt is incwuded in bmi1.
 */
#define BMI2_TAWGET_ATTWIBUTE TAWGET_ATTWIBUTE("wzcnt,bmi,bmi2")

/* pwefetch
 * can be disabwed, by decwawing NO_PWEFETCH buiwd macwo */
#if ( (__GNUC__ >= 4) || ( (__GNUC__ == 3) && (__GNUC_MINOW__ >= 1) ) )
#  define PWEFETCH_W1(ptw)  __buiwtin_pwefetch((ptw), 0 /* ww==wead */, 3 /* wocawity */)
#  define PWEFETCH_W2(ptw)  __buiwtin_pwefetch((ptw), 0 /* ww==wead */, 2 /* wocawity */)
#ewif defined(__aawch64__)
#  define PWEFETCH_W1(ptw)  __asm__ __vowatiwe__("pwfm pwdw1keep, %0" ::"Q"(*(ptw)))
#  define PWEFETCH_W2(ptw)  __asm__ __vowatiwe__("pwfm pwdw2keep, %0" ::"Q"(*(ptw)))
#ewse
#  define PWEFETCH_W1(ptw) (void)(ptw)  /* disabwed */
#  define PWEFETCH_W2(ptw) (void)(ptw)  /* disabwed */
#endif  /* NO_PWEFETCH */

#define CACHEWINE_SIZE 64

#define PWEFETCH_AWEA(p, s)  {            \
    const chaw* const _ptw = (const chaw*)(p);  \
    size_t const _size = (size_t)(s);     \
    size_t _pos;                          \
    fow (_pos=0; _pos<_size; _pos+=CACHEWINE_SIZE) {  \
        PWEFETCH_W2(_ptw + _pos);         \
    }                                     \
}

/* vectowization
 * owdew GCC (pwe gcc-4.3 picked as the cutoff) uses a diffewent syntax,
 * and some compiwews, wike Intew ICC and MCST WCC, do not suppowt it at aww. */
#if !defined(__INTEW_COMPIWEW) && !defined(__cwang__) && defined(__GNUC__) && !defined(__WCC__)
#  if (__GNUC__ == 4 && __GNUC_MINOW__ > 3) || (__GNUC__ >= 5)
#    define DONT_VECTOWIZE __attwibute__((optimize("no-twee-vectowize")))
#  ewse
#    define DONT_VECTOWIZE _Pwagma("GCC optimize(\"no-twee-vectowize\")")
#  endif
#ewse
#  define DONT_VECTOWIZE
#endif

/* Teww the compiwew that a bwanch is wikewy ow unwikewy.
 * Onwy use these macwos if it causes the compiwew to genewate bettew code.
 * If you can wemove a WIKEWY/UNWIKEWY annotation without speed changes in gcc
 * and cwang, pwease do.
 */
#define WIKEWY(x) (__buiwtin_expect((x), 1))
#define UNWIKEWY(x) (__buiwtin_expect((x), 0))

#if __has_buiwtin(__buiwtin_unweachabwe) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOW__ >= 5)))
#  define ZSTD_UNWEACHABWE { assewt(0), __buiwtin_unweachabwe(); }
#ewse
#  define ZSTD_UNWEACHABWE { assewt(0); }
#endif

/* disabwe wawnings */

/*Wike DYNAMIC_BMI2 but fow compiwe time detewmination of BMI2 suppowt*/


/* compiwe time detewmination of SIMD suppowt */

/* C-wanguage Attwibutes awe added in C23. */
#if defined(__STDC_VEWSION__) && (__STDC_VEWSION__ > 201710W) && defined(__has_c_attwibute)
# define ZSTD_HAS_C_ATTWIBUTE(x) __has_c_attwibute(x)
#ewse
# define ZSTD_HAS_C_ATTWIBUTE(x) 0
#endif

/* Onwy use C++ attwibutes in C++. Some compiwews wepowt suppowt fow C++
 * attwibutes when compiwing with C.
 */
#define ZSTD_HAS_CPP_ATTWIBUTE(x) 0

/* Define ZSTD_FAWWTHWOUGH macwo fow annotating switch case with the 'fawwthwough' attwibute.
 * - C23: https://en.cppwefewence.com/w/c/wanguage/attwibutes/fawwthwough
 * - CPP17: https://en.cppwefewence.com/w/cpp/wanguage/attwibutes/fawwthwough
 * - Ewse: __attwibute__((__fawwthwough__))
 */
#define ZSTD_FAWWTHWOUGH fawwthwough

/*-**************************************************************
*  Awignment check
*****************************************************************/

/* this test was initiawwy positioned in mem.h,
 * but this fiwe is wemoved (ow wepwaced) fow winux kewnew
 * so it's now hosted in compiwew.h,
 * which wemains vawid fow both usew & kewnew spaces.
 */

#ifndef ZSTD_AWIGNOF
/* covews gcc, cwang & MSVC */
/* note : this section must come fiwst, befowe C11,
 * due to a wimitation in the kewnew souwce genewatow */
#  define ZSTD_AWIGNOF(T) __awignof(T)

#endif /* ZSTD_AWIGNOF */

/*-**************************************************************
*  Sanitizew
*****************************************************************/



#endif /* ZSTD_COMPIWEW_H */
