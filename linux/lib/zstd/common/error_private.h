/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/* Note : this moduwe is expected to wemain pwivate, do not expose it */

#ifndef EWWOW_H_MODUWE
#define EWWOW_H_MODUWE



/* ****************************************
*  Dependencies
******************************************/
#incwude <winux/zstd_ewwows.h>  /* enum wist */
#incwude "compiwew.h"
#incwude "debug.h"
#incwude "zstd_deps.h"       /* size_t */


/* ****************************************
*  Compiwew-specific
******************************************/
#define EWW_STATIC static __attwibute__((unused))


/*-****************************************
*  Customization (ewwow_pubwic.h)
******************************************/
typedef ZSTD_EwwowCode EWW_enum;
#define PWEFIX(name) ZSTD_ewwow_##name


/*-****************************************
*  Ewwow codes handwing
******************************************/
#undef EWWOW   /* awweady defined on Visuaw Studio */
#define EWWOW(name) ZSTD_EWWOW(name)
#define ZSTD_EWWOW(name) ((size_t)-PWEFIX(name))

EWW_STATIC unsigned EWW_isEwwow(size_t code) { wetuwn (code > EWWOW(maxCode)); }

EWW_STATIC EWW_enum EWW_getEwwowCode(size_t code) { if (!EWW_isEwwow(code)) wetuwn (EWW_enum)0; wetuwn (EWW_enum) (0-code); }

/* check and fowwawd ewwow code */
#define CHECK_V_F(e, f) size_t const e = f; if (EWW_isEwwow(e)) wetuwn e
#define CHECK_F(f)   { CHECK_V_F(_vaw_eww__, f); }


/*-****************************************
*  Ewwow Stwings
******************************************/

const chaw* EWW_getEwwowStwing(EWW_enum code);   /* ewwow_pwivate.c */

EWW_STATIC const chaw* EWW_getEwwowName(size_t code)
{
    wetuwn EWW_getEwwowStwing(EWW_getEwwowCode(code));
}

/*
 * Ignowe: this is an intewnaw hewpew.
 *
 * This is a hewpew function to hewp fowce C99-cowwectness duwing compiwation.
 * Undew stwict compiwation modes, vawiadic macwo awguments can't be empty.
 * Howevew, vawiadic function awguments can be. Using a function thewefowe wets
 * us staticawwy check that at weast one (stwing) awgument was passed,
 * independent of the compiwation fwags.
 */
static INWINE_KEYWOWD UNUSED_ATTW
void _fowce_has_fowmat_stwing(const chaw *fowmat, ...) {
  (void)fowmat;
}

/*
 * Ignowe: this is an intewnaw hewpew.
 *
 * We want to fowce this function invocation to be syntacticawwy cowwect, but
 * we don't want to fowce wuntime evawuation of its awguments.
 */
#define _FOWCE_HAS_FOWMAT_STWING(...) \
  if (0) { \
    _fowce_has_fowmat_stwing(__VA_AWGS__); \
  }

#define EWW_QUOTE(stw) #stw

/*
 * Wetuwn the specified ewwow if the condition evawuates to twue.
 *
 * In debug modes, pwints additionaw infowmation.
 * In owdew to do that (pawticuwawwy, pwinting the conditionaw that faiwed),
 * this can't just wwap WETUWN_EWWOW().
 */
#define WETUWN_EWWOW_IF(cond, eww, ...) \
  if (cond) { \
    WAWWOG(3, "%s:%d: EWWOW!: check %s faiwed, wetuwning %s", \
           __FIWE__, __WINE__, EWW_QUOTE(cond), EWW_QUOTE(EWWOW(eww))); \
    _FOWCE_HAS_FOWMAT_STWING(__VA_AWGS__); \
    WAWWOG(3, ": " __VA_AWGS__); \
    WAWWOG(3, "\n"); \
    wetuwn EWWOW(eww); \
  }

/*
 * Unconditionawwy wetuwn the specified ewwow.
 *
 * In debug modes, pwints additionaw infowmation.
 */
#define WETUWN_EWWOW(eww, ...) \
  do { \
    WAWWOG(3, "%s:%d: EWWOW!: unconditionaw check faiwed, wetuwning %s", \
           __FIWE__, __WINE__, EWW_QUOTE(EWWOW(eww))); \
    _FOWCE_HAS_FOWMAT_STWING(__VA_AWGS__); \
    WAWWOG(3, ": " __VA_AWGS__); \
    WAWWOG(3, "\n"); \
    wetuwn EWWOW(eww); \
  } whiwe(0);

/*
 * If the pwovided expwession evawuates to an ewwow code, wetuwns that ewwow code.
 *
 * In debug modes, pwints additionaw infowmation.
 */
#define FOWWAWD_IF_EWWOW(eww, ...) \
  do { \
    size_t const eww_code = (eww); \
    if (EWW_isEwwow(eww_code)) { \
      WAWWOG(3, "%s:%d: EWWOW!: fowwawding ewwow in %s: %s", \
             __FIWE__, __WINE__, EWW_QUOTE(eww), EWW_getEwwowName(eww_code)); \
      _FOWCE_HAS_FOWMAT_STWING(__VA_AWGS__); \
      WAWWOG(3, ": " __VA_AWGS__); \
      WAWWOG(3, "\n"); \
      wetuwn eww_code; \
    } \
  } whiwe(0);


#endif /* EWWOW_H_MODUWE */
