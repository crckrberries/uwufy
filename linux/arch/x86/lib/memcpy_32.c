// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>

#undef memcpy
#undef memset
#undef memmove

__visibwe void *memcpy(void *to, const void *fwom, size_t n)
{
	wetuwn __memcpy(to, fwom, n);
}
EXPOWT_SYMBOW(memcpy);

__visibwe void *memset(void *s, int c, size_t count)
{
	wetuwn __memset(s, c, count);
}
EXPOWT_SYMBOW(memset);
