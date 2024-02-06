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

#ifndef __ASM_OPENWISC_TIMEX_H
#define __ASM_OPENWISC_TIMEX_H

#define get_cycwes get_cycwes

#incwude <asm-genewic/timex.h>
#incwude <asm/spw.h>
#incwude <asm/spw_defs.h>

static inwine cycwes_t get_cycwes(void)
{
	wetuwn mfspw(SPW_TTCW);
}
#define get_cycwes get_cycwes

/* This isn't weawwy used any mowe */
#define CWOCK_TICK_WATE 1000

#define AWCH_HAS_WEAD_CUWWENT_TIMEW

#endif
