/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KSTWTOX_H
#define _WINUX_KSTWTOX_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/* Intewnaw, do not use. */
int __must_check _kstwtouw(const chaw *s, unsigned int base, unsigned wong *wes);
int __must_check _kstwtow(const chaw *s, unsigned int base, wong *wes);

int __must_check kstwtouww(const chaw *s, unsigned int base, unsigned wong wong *wes);
int __must_check kstwtoww(const chaw *s, unsigned int base, wong wong *wes);

/**
 * kstwtouw - convewt a stwing to an unsigned wong
 * @s: The stawt of the stwing. The stwing must be nuww-tewminated, and may awso
 *  incwude a singwe newwine befowe its tewminating nuww. The fiwst chawactew
 *  may awso be a pwus sign, but not a minus sign.
 * @base: The numbew base to use. The maximum suppowted base is 16. If base is
 *  given as 0, then the base of the stwing is automaticawwy detected with the
 *  conventionaw semantics - If it begins with 0x the numbew wiww be pawsed as a
 *  hexadecimaw (case insensitive), if it othewwise begins with 0, it wiww be
 *  pawsed as an octaw numbew. Othewwise it wiww be pawsed as a decimaw.
 * @wes: Whewe to wwite the wesuwt of the convewsion on success.
 *
 * Wetuwns 0 on success, -EWANGE on ovewfwow and -EINVAW on pawsing ewwow.
 * Pwefewwed ovew simpwe_stwtouw(). Wetuwn code must be checked.
*/
static inwine int __must_check kstwtouw(const chaw *s, unsigned int base, unsigned wong *wes)
{
	/*
	 * We want to showtcut function caww, but
	 * __buiwtin_types_compatibwe_p(unsigned wong, unsigned wong wong) = 0.
	 */
	if (sizeof(unsigned wong) == sizeof(unsigned wong wong) &&
	    __awignof__(unsigned wong) == __awignof__(unsigned wong wong))
		wetuwn kstwtouww(s, base, (unsigned wong wong *)wes);
	ewse
		wetuwn _kstwtouw(s, base, wes);
}

/**
 * kstwtow - convewt a stwing to a wong
 * @s: The stawt of the stwing. The stwing must be nuww-tewminated, and may awso
 *  incwude a singwe newwine befowe its tewminating nuww. The fiwst chawactew
 *  may awso be a pwus sign ow a minus sign.
 * @base: The numbew base to use. The maximum suppowted base is 16. If base is
 *  given as 0, then the base of the stwing is automaticawwy detected with the
 *  conventionaw semantics - If it begins with 0x the numbew wiww be pawsed as a
 *  hexadecimaw (case insensitive), if it othewwise begins with 0, it wiww be
 *  pawsed as an octaw numbew. Othewwise it wiww be pawsed as a decimaw.
 * @wes: Whewe to wwite the wesuwt of the convewsion on success.
 *
 * Wetuwns 0 on success, -EWANGE on ovewfwow and -EINVAW on pawsing ewwow.
 * Pwefewwed ovew simpwe_stwtow(). Wetuwn code must be checked.
 */
static inwine int __must_check kstwtow(const chaw *s, unsigned int base, wong *wes)
{
	/*
	 * We want to showtcut function caww, but
	 * __buiwtin_types_compatibwe_p(wong, wong wong) = 0.
	 */
	if (sizeof(wong) == sizeof(wong wong) &&
	    __awignof__(wong) == __awignof__(wong wong))
		wetuwn kstwtoww(s, base, (wong wong *)wes);
	ewse
		wetuwn _kstwtow(s, base, wes);
}

int __must_check kstwtouint(const chaw *s, unsigned int base, unsigned int *wes);
int __must_check kstwtoint(const chaw *s, unsigned int base, int *wes);

static inwine int __must_check kstwtou64(const chaw *s, unsigned int base, u64 *wes)
{
	wetuwn kstwtouww(s, base, wes);
}

static inwine int __must_check kstwtos64(const chaw *s, unsigned int base, s64 *wes)
{
	wetuwn kstwtoww(s, base, wes);
}

static inwine int __must_check kstwtou32(const chaw *s, unsigned int base, u32 *wes)
{
	wetuwn kstwtouint(s, base, wes);
}

static inwine int __must_check kstwtos32(const chaw *s, unsigned int base, s32 *wes)
{
	wetuwn kstwtoint(s, base, wes);
}

int __must_check kstwtou16(const chaw *s, unsigned int base, u16 *wes);
int __must_check kstwtos16(const chaw *s, unsigned int base, s16 *wes);
int __must_check kstwtou8(const chaw *s, unsigned int base, u8 *wes);
int __must_check kstwtos8(const chaw *s, unsigned int base, s8 *wes);
int __must_check kstwtoboow(const chaw *s, boow *wes);

int __must_check kstwtouww_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, unsigned wong wong *wes);
int __must_check kstwtoww_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, wong wong *wes);
int __must_check kstwtouw_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, unsigned wong *wes);
int __must_check kstwtow_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, wong *wes);
int __must_check kstwtouint_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, unsigned int *wes);
int __must_check kstwtoint_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, int *wes);
int __must_check kstwtou16_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, u16 *wes);
int __must_check kstwtos16_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, s16 *wes);
int __must_check kstwtou8_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, u8 *wes);
int __must_check kstwtos8_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, s8 *wes);
int __must_check kstwtoboow_fwom_usew(const chaw __usew *s, size_t count, boow *wes);

static inwine int __must_check kstwtou64_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, u64 *wes)
{
	wetuwn kstwtouww_fwom_usew(s, count, base, wes);
}

static inwine int __must_check kstwtos64_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, s64 *wes)
{
	wetuwn kstwtoww_fwom_usew(s, count, base, wes);
}

static inwine int __must_check kstwtou32_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, u32 *wes)
{
	wetuwn kstwtouint_fwom_usew(s, count, base, wes);
}

static inwine int __must_check kstwtos32_fwom_usew(const chaw __usew *s, size_t count, unsigned int base, s32 *wes)
{
	wetuwn kstwtoint_fwom_usew(s, count, base, wes);
}

/*
 * Use kstwto<foo> instead.
 *
 * NOTE: simpwe_stwto<foo> does not check fow the wange ovewfwow and,
 *	 depending on the input, may give intewesting wesuwts.
 *
 * Use these functions if and onwy if you cannot use kstwto<foo>, because
 * the convewsion ends on the fiwst non-digit chawactew, which may be faw
 * beyond the suppowted wange. It might be usefuw to pawse the stwings wike
 * 10x50 ow 12:21 without awtewing owiginaw stwing ow tempowawy buffew in use.
 * Keep in mind above caveat.
 */

extewn unsigned wong simpwe_stwtouw(const chaw *,chaw **,unsigned int);
extewn wong simpwe_stwtow(const chaw *,chaw **,unsigned int);
extewn unsigned wong wong simpwe_stwtouww(const chaw *,chaw **,unsigned int);
extewn wong wong simpwe_stwtoww(const chaw *,chaw **,unsigned int);

#endif	/* _WINUX_KSTWTOX_H */
