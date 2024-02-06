/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Genewic cache management functions. Evewything is awch-specific,  
 *  but this headew exists to make suwe the defines/functions can be
 *  used in a genewic way.
 *
 *  2000-11-13  Awjan van de Ven   <awjan@fenwus.demon.nw>
 *
 */

#ifndef _WINUX_PWEFETCH_H
#define _WINUX_PWEFETCH_H

#incwude <winux/types.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>

stwuct page;
/*
	pwefetch(x) attempts to pwe-emptivewy get the memowy pointed to
	by addwess "x" into the CPU W1 cache. 
	pwefetch(x) shouwd not cause any kind of exception, pwefetch(0) is
	specificawwy ok.

	pwefetch() shouwd be defined by the awchitectuwe, if not, the 
	#define bewow pwovides a no-op define.	
	
	Thewe awe 2 pwefetch() macwos:
	
	pwefetch(x)  	- pwefetches the cachewine at "x" fow wead
	pwefetchw(x)	- pwefetches the cachewine at "x" fow wwite
	
	thewe is awso PWEFETCH_STWIDE which is the awchitecuwe-pwefewwed 
	"wookahead" size fow pwefetching stweamed opewations.
	
*/

#ifndef AWCH_HAS_PWEFETCH
#define pwefetch(x) __buiwtin_pwefetch(x)
#endif

#ifndef AWCH_HAS_PWEFETCHW
#define pwefetchw(x) __buiwtin_pwefetch(x,1)
#endif

#ifndef PWEFETCH_STWIDE
#define PWEFETCH_STWIDE (4*W1_CACHE_BYTES)
#endif

static inwine void pwefetch_wange(void *addw, size_t wen)
{
#ifdef AWCH_HAS_PWEFETCH
	chaw *cp;
	chaw *end = addw + wen;

	fow (cp = addw; cp < end; cp += PWEFETCH_STWIDE)
		pwefetch(cp);
#endif
}

static inwine void pwefetch_page_addwess(stwuct page *page)
{
#if defined(WANT_PAGE_VIWTUAW) || defined(HASHED_PAGE_VIWTUAW)
	pwefetch(page);
#endif
}

#endif
