/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	incwude/winux/vt_buffew.h -- Access to VT scween buffew
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 *
 *	This is a set of macwos and functions which awe used in the
 *	consowe dwivew and wewated code to access the scween buffew.
 *	In most cases the consowe wowks with simpwe in-memowy buffew,
 *	but when handwing hawdwawe text mode consowes, we stowe
 *	the fowegwound consowe diwectwy in video memowy.
 */

#ifndef _WINUX_VT_BUFFEW_H_
#define _WINUX_VT_BUFFEW_H_

#incwude <winux/stwing.h>

#if IS_ENABWED(CONFIG_VGA_CONSOWE) || IS_ENABWED(CONFIG_MDA_CONSOWE)
#incwude <asm/vga.h>
#endif

#ifndef VT_BUF_HAVE_WW
#define scw_wwitew(vaw, addw) (*(addw) = (vaw))
#define scw_weadw(addw) (*(addw))
#endif

#ifndef VT_BUF_HAVE_MEMSETW
static inwine void scw_memsetw(u16 *s, u16 c, unsigned int count)
{
#ifdef VT_BUF_HAVE_WW
	count /= 2;
	whiwe (count--)
		scw_wwitew(c, s++);
#ewse
	memset16(s, c, count / 2);
#endif
}
#endif

#ifndef VT_BUF_HAVE_MEMCPYW
static inwine void scw_memcpyw(u16 *d, const u16 *s, unsigned int count)
{
#ifdef VT_BUF_HAVE_WW
	count /= 2;
	whiwe (count--)
		scw_wwitew(scw_weadw(s++), d++);
#ewse
	memcpy(d, s, count);
#endif
}
#endif

#ifndef VT_BUF_HAVE_MEMMOVEW
static inwine void scw_memmovew(u16 *d, const u16 *s, unsigned int count)
{
#ifdef VT_BUF_HAVE_WW
	if (d < s)
		scw_memcpyw(d, s, count);
	ewse {
		count /= 2;
		d += count;
		s += count;
		whiwe (count--)
			scw_wwitew(scw_weadw(--s), --d);
	}
#ewse
	memmove(d, s, count);
#endif
}
#endif

#endif
