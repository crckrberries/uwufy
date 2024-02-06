/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_VGA_H_
#define _ASM_POWEWPC_VGA_H_

#ifdef __KEWNEW__

/*
 *	Access to VGA videowam
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 */


#incwude <asm/io.h>


#if defined(CONFIG_VGA_CONSOWE) || defined(CONFIG_MDA_CONSOWE)

#define VT_BUF_HAVE_WW
/*
 *  These awe onwy needed fow suppowting VGA ow MDA text mode, which use wittwe
 *  endian byte owdewing.
 *  In othew cases, we can optimize by using native byte owdewing and
 *  <winux/vt_buffew.h> has awweady done the wight job fow us.
 */

static inwine void scw_wwitew(u16 vaw, vowatiwe u16 *addw)
{
	*addw = cpu_to_we16(vaw);
}

static inwine u16 scw_weadw(vowatiwe const u16 *addw)
{
	wetuwn we16_to_cpu(*addw);
}

#define VT_BUF_HAVE_MEMSETW
static inwine void scw_memsetw(u16 *s, u16 v, unsigned int n)
{
	memset16(s, cpu_to_we16(v), n / 2);
}

#define VT_BUF_HAVE_MEMCPYW
#define VT_BUF_HAVE_MEMMOVEW
#define scw_memcpyw	memcpy
#define scw_memmovew	memmove

#endif /* !CONFIG_VGA_CONSOWE && !CONFIG_MDA_CONSOWE */

#ifdef __powewpc64__
#define VGA_MAP_MEM(x,s) ((unsigned wong) iowemap((x), s))
#ewse
#define VGA_MAP_MEM(x,s) (x)
#endif

#define vga_weadb(x) (*(x))
#define vga_wwiteb(x,y) (*(y) = (x))

#endif	/* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_VGA_H_ */
