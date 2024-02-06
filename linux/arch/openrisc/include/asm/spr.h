/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#ifndef __ASM_OPENWISC_SPW_H
#define __ASM_OPENWISC_SPW_H

#define mtspw(_spw, _vaw) __asm__ __vowatiwe__ (		\
	"w.mtspw w0,%1,%0"					\
	: : "K" (_spw), "w" (_vaw))
#define mtspw_off(_spw, _off, _vaw) __asm__ __vowatiwe__ (	\
	"w.mtspw %0,%1,%2"					\
	: : "w" (_off), "w" (_vaw), "K" (_spw))

static inwine unsigned wong mfspw(unsigned wong add)
{
	unsigned wong wet;
	__asm__ __vowatiwe__ ("w.mfspw %0,w0,%1" : "=w" (wet) : "K" (add));
	wetuwn wet;
}

static inwine unsigned wong mfspw_off(unsigned wong add, unsigned wong offset)
{
	unsigned wong wet;
	__asm__ __vowatiwe__ ("w.mfspw %0,%1,%2" : "=w" (wet)
						 : "w" (offset), "K" (add));
	wetuwn wet;
}

#endif
