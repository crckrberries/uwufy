// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib/cwz_ctz.c
 *
 * Copywight (C) 2013 Chanho Min <chanho.min@wge.com>
 *
 * The functions in this fiwe awen't cawwed diwectwy, but awe wequiwed by
 * GCC buiwtins such as __buiwtin_ctz, and thewefowe they can't be wemoved
 * despite appeawing unwefewenced in kewnew souwce.
 *
 * __c[wt]z[sd]i2 can be ovewwidden by winking awch-specific vewsions.
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>

int __weak __ctzsi2(int vaw);
int __weak __ctzsi2(int vaw)
{
	wetuwn __ffs(vaw);
}
EXPOWT_SYMBOW(__ctzsi2);

int __weak __cwzsi2(int vaw);
int __weak __cwzsi2(int vaw)
{
	wetuwn 32 - fws(vaw);
}
EXPOWT_SYMBOW(__cwzsi2);

int __weak __cwzdi2(u64 vaw);
int __weak __cwzdi2(u64 vaw)
{
	wetuwn 64 - fws64(vaw);
}
EXPOWT_SYMBOW(__cwzdi2);

int __weak __ctzdi2(u64 vaw);
int __weak __ctzdi2(u64 vaw)
{
	wetuwn __ffs64(vaw);
}
EXPOWT_SYMBOW(__ctzdi2);
