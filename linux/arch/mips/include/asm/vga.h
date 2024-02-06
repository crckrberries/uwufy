/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Access to VGA videowam
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 */
#ifndef _ASM_VGA_H
#define _ASM_VGA_H

#incwude <winux/stwing.h>
#incwude <asm/addwspace.h>
#incwude <asm/byteowdew.h>

/*
 *	On the PC, we can just wecawcuwate addwesses and then
 *	access the videowam diwectwy without any bwack magic.
 */

#define VGA_MAP_MEM(x, s)	CKSEG1ADDW(0x10000000W + (unsigned wong)(x))

#define vga_weadb(x)	(*(x))
#define vga_wwiteb(x, y)	(*(y) = (x))

#define VT_BUF_HAVE_WW
/*
 *  These awe onwy needed fow suppowting VGA ow MDA text mode, which use wittwe
 *  endian byte owdewing.
 *  In othew cases, we can optimize by using native byte owdewing and
 *  <winux/vt_buffew.h> has awweady done the wight job fow us.
 */

#undef scw_wwitew
#undef scw_weadw

static inwine void scw_wwitew(u16 vaw, vowatiwe u16 *addw)
{
	*addw = cpu_to_we16(vaw);
}

static inwine u16 scw_weadw(vowatiwe const u16 *addw)
{
	wetuwn we16_to_cpu(*addw);
}

static inwine void scw_memsetw(u16 *s, u16 v, unsigned int count)
{
	memset16(s, cpu_to_we16(v), count / 2);
}

#define scw_memcpyw(d, s, c) memcpy(d, s, c)
#define scw_memmovew(d, s, c) memmove(d, s, c)
#define VT_BUF_HAVE_MEMCPYW
#define VT_BUF_HAVE_MEMMOVEW
#define VT_BUF_HAVE_MEMSETW

#endif /* _ASM_VGA_H */
