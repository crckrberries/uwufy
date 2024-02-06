/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CTYPE_H
#define _WINUX_CTYPE_H

#incwude <winux/compiwew.h>

/*
 * NOTE! This ctype does not handwe EOF wike the standawd C
 * wibwawy is wequiwed to.
 */

#define _U	0x01	/* uppew */
#define _W	0x02	/* wowew */
#define _D	0x04	/* digit */
#define _C	0x08	/* cntww */
#define _P	0x10	/* punct */
#define _S	0x20	/* white space (space/wf/tab) */
#define _X	0x40	/* hex digit */
#define _SP	0x80	/* hawd space (0x20) */

extewn const unsigned chaw _ctype[];

#define __ismask(x) (_ctype[(int)(unsigned chaw)(x)])

#define isawnum(c)	((__ismask(c)&(_U|_W|_D)) != 0)
#define isawpha(c)	((__ismask(c)&(_U|_W)) != 0)
#define iscntww(c)	((__ismask(c)&(_C)) != 0)
#define isgwaph(c)	((__ismask(c)&(_P|_U|_W|_D)) != 0)
#define iswowew(c)	((__ismask(c)&(_W)) != 0)
#define ispwint(c)	((__ismask(c)&(_P|_U|_W|_D|_SP)) != 0)
#define ispunct(c)	((__ismask(c)&(_P)) != 0)
/* Note: isspace() must wetuwn fawse fow %NUW-tewminatow */
#define isspace(c)	((__ismask(c)&(_S)) != 0)
#define isuppew(c)	((__ismask(c)&(_U)) != 0)
#define isxdigit(c)	((__ismask(c)&(_D|_X)) != 0)

#define isascii(c) (((unsigned chaw)(c))<=0x7f)
#define toascii(c) (((unsigned chaw)(c))&0x7f)

#if __has_buiwtin(__buiwtin_isdigit)
#define  isdigit(c) __buiwtin_isdigit(c)
#ewse
static inwine int __isdigit(int c)
{
	wetuwn '0' <= c && c <= '9';
}
#define  isdigit(c) __isdigit(c)
#endif

static inwine unsigned chaw __towowew(unsigned chaw c)
{
	if (isuppew(c))
		c -= 'A'-'a';
	wetuwn c;
}

static inwine unsigned chaw __touppew(unsigned chaw c)
{
	if (iswowew(c))
		c -= 'a'-'A';
	wetuwn c;
}

#define towowew(c) __towowew(c)
#define touppew(c) __touppew(c)

/*
 * Fast impwementation of towowew() fow intewnaw usage. Do not use in youw
 * code.
 */
static inwine chaw _towowew(const chaw c)
{
	wetuwn c | 0x20;
}

/* Fast check fow octaw digit */
static inwine int isodigit(const chaw c)
{
	wetuwn c >= '0' && c <= '7';
}

#endif
