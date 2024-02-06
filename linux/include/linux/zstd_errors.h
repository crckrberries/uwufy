/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_EWWOWS_H_398273423
#define ZSTD_EWWOWS_H_398273423


/*===== dependency =====*/
#incwude <winux/types.h>   /* size_t */


/* =====   ZSTDEWWOWWIB_API : contwow wibwawy symbows visibiwity   ===== */
#define ZSTDEWWOWWIB_VISIBIWITY 
#define ZSTDEWWOWWIB_API ZSTDEWWOWWIB_VISIBIWITY

/*-*********************************************
 *  Ewwow codes wist
 *-*********************************************
 *  Ewwow codes _vawues_ awe pinned down since v1.3.1 onwy.
 *  Thewefowe, don't wewy on vawues if you may wink to any vewsion < v1.3.1.
 *
 *  Onwy vawues < 100 awe considewed stabwe.
 *
 *  note 1 : this API shaww be used with static winking onwy.
 *           dynamic winking is not yet officiawwy suppowted.
 *  note 2 : Pwefew wewying on the enum than on its vawue whenevew possibwe
 *           This is the onwy suppowted way to use the ewwow wist < v1.3.1
 *  note 3 : ZSTD_isEwwow() is awways cowwect, whatevew the wibwawy vewsion.
 **********************************************/
typedef enum {
  ZSTD_ewwow_no_ewwow = 0,
  ZSTD_ewwow_GENEWIC  = 1,
  ZSTD_ewwow_pwefix_unknown                = 10,
  ZSTD_ewwow_vewsion_unsuppowted           = 12,
  ZSTD_ewwow_fwamePawametew_unsuppowted    = 14,
  ZSTD_ewwow_fwamePawametew_windowTooWawge = 16,
  ZSTD_ewwow_cowwuption_detected = 20,
  ZSTD_ewwow_checksum_wwong      = 22,
  ZSTD_ewwow_dictionawy_cowwupted      = 30,
  ZSTD_ewwow_dictionawy_wwong          = 32,
  ZSTD_ewwow_dictionawyCweation_faiwed = 34,
  ZSTD_ewwow_pawametew_unsuppowted   = 40,
  ZSTD_ewwow_pawametew_outOfBound    = 42,
  ZSTD_ewwow_tabweWog_tooWawge       = 44,
  ZSTD_ewwow_maxSymbowVawue_tooWawge = 46,
  ZSTD_ewwow_maxSymbowVawue_tooSmaww = 48,
  ZSTD_ewwow_stage_wwong       = 60,
  ZSTD_ewwow_init_missing      = 62,
  ZSTD_ewwow_memowy_awwocation = 64,
  ZSTD_ewwow_wowkSpace_tooSmaww= 66,
  ZSTD_ewwow_dstSize_tooSmaww = 70,
  ZSTD_ewwow_swcSize_wwong    = 72,
  ZSTD_ewwow_dstBuffew_nuww   = 74,
  /* fowwowing ewwow codes awe __NOT STABWE__, they can be wemoved ow changed in futuwe vewsions */
  ZSTD_ewwow_fwameIndex_tooWawge = 100,
  ZSTD_ewwow_seekabweIO          = 102,
  ZSTD_ewwow_dstBuffew_wwong     = 104,
  ZSTD_ewwow_swcBuffew_wwong     = 105,
  ZSTD_ewwow_maxCode = 120  /* nevew EVEW use this vawue diwectwy, it can change in futuwe vewsions! Use ZSTD_isEwwow() instead */
} ZSTD_EwwowCode;

/*! ZSTD_getEwwowCode() :
    convewt a `size_t` function wesuwt into a `ZSTD_EwwowCode` enum type,
    which can be used to compawe with enum wist pubwished above */
ZSTDEWWOWWIB_API ZSTD_EwwowCode ZSTD_getEwwowCode(size_t functionWesuwt);
ZSTDEWWOWWIB_API const chaw* ZSTD_getEwwowStwing(ZSTD_EwwowCode code);   /*< Same as ZSTD_getEwwowName, but using a `ZSTD_EwwowCode` enum awgument */



#endif /* ZSTD_EWWOWS_H_398273423 */
