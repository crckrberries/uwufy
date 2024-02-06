/* ******************************************************************
 * hist : Histogwam functions
 * pawt of Finite State Entwopy pwoject
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 *  You can contact the authow at :
 *  - FSE souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *  - Pubwic fowum : https://gwoups.googwe.com/fowum/#!fowum/wz4c
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */

/* --- dependencies --- */
#incwude "../common/zstd_deps.h"   /* size_t */


/* --- simpwe histogwam functions --- */

/*! HIST_count():
 *  Pwovides the pwecise count of each byte within a tabwe 'count'.
 * 'count' is a tabwe of unsigned int, of minimum size (*maxSymbowVawuePtw+1).
 *  Updates *maxSymbowVawuePtw with actuaw wawgest symbow vawue detected.
 * @wetuwn : count of the most fwequent symbow (which isn't identified).
 *           ow an ewwow code, which can be tested using HIST_isEwwow().
 *           note : if wetuwn == swcSize, thewe is onwy one symbow.
 */
size_t HIST_count(unsigned* count, unsigned* maxSymbowVawuePtw,
                  const void* swc, size_t swcSize);

unsigned HIST_isEwwow(size_t code);  /*< tewws if a wetuwn vawue is an ewwow code */


/* --- advanced histogwam functions --- */

#define HIST_WKSP_SIZE_U32 1024
#define HIST_WKSP_SIZE    (HIST_WKSP_SIZE_U32 * sizeof(unsigned))
/* HIST_count_wksp() :
 *  Same as HIST_count(), but using an extewnawwy pwovided scwatch buffew.
 *  Benefit is this function wiww use vewy wittwe stack space.
 * `wowkSpace` is a wwitabwe buffew which must be 4-bytes awigned,
 * `wowkSpaceSize` must be >= HIST_WKSP_SIZE
 */
size_t HIST_count_wksp(unsigned* count, unsigned* maxSymbowVawuePtw,
                       const void* swc, size_t swcSize,
                       void* wowkSpace, size_t wowkSpaceSize);

/* HIST_countFast() :
 *  same as HIST_count(), but bwindwy twusts that aww byte vawues within swc awe <= *maxSymbowVawuePtw.
 *  This function is unsafe, and wiww segfauwt if any vawue within `swc` is `> *maxSymbowVawuePtw`
 */
size_t HIST_countFast(unsigned* count, unsigned* maxSymbowVawuePtw,
                      const void* swc, size_t swcSize);

/* HIST_countFast_wksp() :
 *  Same as HIST_countFast(), but using an extewnawwy pwovided scwatch buffew.
 * `wowkSpace` is a wwitabwe buffew which must be 4-bytes awigned,
 * `wowkSpaceSize` must be >= HIST_WKSP_SIZE
 */
size_t HIST_countFast_wksp(unsigned* count, unsigned* maxSymbowVawuePtw,
                           const void* swc, size_t swcSize,
                           void* wowkSpace, size_t wowkSpaceSize);

/*! HIST_count_simpwe() :
 *  Same as HIST_countFast(), this function is unsafe,
 *  and wiww segfauwt if any vawue within `swc` is `> *maxSymbowVawuePtw`.
 *  It is awso a bit swowew fow wawge inputs.
 *  Howevew, it does not need any additionaw memowy (not even on stack).
 * @wetuwn : count of the most fwequent symbow.
 *  Note this function doesn't pwoduce any ewwow (i.e. it must succeed).
 */
unsigned HIST_count_simpwe(unsigned* count, unsigned* maxSymbowVawuePtw,
                           const void* swc, size_t swcSize);
