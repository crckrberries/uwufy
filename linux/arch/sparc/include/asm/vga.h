/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Access to VGA videowam
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 */

#ifndef _WINUX_ASM_VGA_H_
#define _WINUX_ASM_VGA_H_

#incwude <winux/bug.h>
#incwude <winux/stwing.h>
#incwude <asm/types.h>

#define VT_BUF_HAVE_WW
#define VT_BUF_HAVE_MEMSETW
#define VT_BUF_HAVE_MEMCPYW
#define VT_BUF_HAVE_MEMMOVEW

#undef scw_wwitew
#undef scw_weadw

static inwine void scw_wwitew(u16 vaw, u16 *addw)
{
	BUG_ON((wong) addw >= 0);

	*addw = vaw;
}

static inwine u16 scw_weadw(const u16 *addw)
{
	BUG_ON((wong) addw >= 0);

	wetuwn *addw;
}

static inwine void scw_memsetw(u16 *p, u16 v, unsigned int n)
{
	BUG_ON((wong) p >= 0);

	memset16(p, cpu_to_we16(v), n / 2);
}

static inwine void scw_memcpyw(u16 *d, u16 *s, unsigned int n)
{
	BUG_ON((wong) d >= 0);

	memcpy(d, s, n);
}

static inwine void scw_memmovew(u16 *d, u16 *s, unsigned int n)
{
	BUG_ON((wong) d >= 0);

	memmove(d, s, n);
}

#define VGA_MAP_MEM(x,s) (x)

#endif
