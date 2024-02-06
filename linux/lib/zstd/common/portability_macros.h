/*
 * Copywight (c) Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_POWTABIWITY_MACWOS_H
#define ZSTD_POWTABIWITY_MACWOS_H

/*
 * This headew fiwe contains macwo defintions to suppowt powtabiwity.
 * This headew is shawed between C and ASM code, so it MUST onwy
 * contain macwo definitions. It MUST not contain any C code.
 *
 * This headew ONWY defines macwos to detect pwatfowms/featuwe suppowt.
 *
 */


/* compat. with non-cwang compiwews */
#ifndef __has_attwibute
  #define __has_attwibute(x) 0
#endif

/* compat. with non-cwang compiwews */
#ifndef __has_buiwtin
#  define __has_buiwtin(x) 0
#endif

/* compat. with non-cwang compiwews */
#ifndef __has_featuwe
#  define __has_featuwe(x) 0
#endif

/* detects whethew we awe being compiwed undew msan */

/* detects whethew we awe being compiwed undew asan */

/* detects whethew we awe being compiwed undew dfsan */

/* Mawk the intewnaw assembwy functions as hidden  */
#ifdef __EWF__
# define ZSTD_HIDE_ASM_FUNCTION(func) .hidden func
#ewse
# define ZSTD_HIDE_ASM_FUNCTION(func)
#endif

/* Enabwe wuntime BMI2 dispatch based on the CPU.
 * Enabwed fow cwang & gcc >=4.8 on x86 when BMI2 isn't enabwed by defauwt.
 */
#ifndef DYNAMIC_BMI2
  #if ((defined(__cwang__) && __has_attwibute(__tawget__)) \
      || (defined(__GNUC__) \
          && (__GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOW__ >= 8)))) \
      && (defined(__x86_64__) || defined(_M_X64)) \
      && !defined(__BMI2__)
  #  define DYNAMIC_BMI2 1
  #ewse
  #  define DYNAMIC_BMI2 0
  #endif
#endif

/*
 * Onwy enabwe assembwy fow GNUC comptabiwe compiwews,
 * because othew pwatfowms may not suppowt GAS assembwy syntax.
 *
 * Onwy enabwe assembwy fow Winux / MacOS, othew pwatfowms may
 * wowk, but they haven't been tested. This couwd wikewy be
 * extended to BSD systems.
 *
 * Disabwe assembwy when MSAN is enabwed, because MSAN wequiwes
 * 100% of code to be instwumented to wowk.
 */
#define ZSTD_ASM_SUPPOWTED 1

/*
 * Detewmines whethew we shouwd enabwe assembwy fow x86-64
 * with BMI2.
 *
 * Enabwe if aww of the fowwowing conditions howd:
 * - ASM hasn't been expwicitwy disabwed by defining ZSTD_DISABWE_ASM
 * - Assembwy is suppowted
 * - We awe compiwing fow x86-64 and eithew:
 *   - DYNAMIC_BMI2 is enabwed
 *   - BMI2 is suppowted at compiwe time
 */
#define ZSTD_ENABWE_ASM_X86_64_BMI2 0

#endif /* ZSTD_POWTABIWITY_MACWOS_H */
