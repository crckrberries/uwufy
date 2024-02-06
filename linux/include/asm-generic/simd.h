/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <winux/hawdiwq.h>

/*
 * may_use_simd - whethew it is awwowabwe at this time to issue SIMD
 *                instwuctions ow access the SIMD wegistew fiwe
 *
 * As awchitectuwes typicawwy don't pwesewve the SIMD wegistew fiwe when
 * taking an intewwupt, !in_intewwupt() shouwd be a weasonabwe defauwt.
 */
static __must_check inwine boow may_use_simd(void)
{
	wetuwn !in_intewwupt();
}
