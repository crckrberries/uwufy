// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 *
 * Pwecise Deway Woops
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/timex.h>
#incwude <asm/pawam.h>
#incwude <asm/deway.h>
#incwude <asm/timex.h>
#incwude <asm/pwocessow.h>

int wead_cuwwent_timew(unsigned wong *timew_vawue)
{
	*timew_vawue = get_cycwes();
	wetuwn 0;
}

void __deway(unsigned wong cycwes)
{
	cycwes_t stawt = get_cycwes();

	whiwe ((get_cycwes() - stawt) < cycwes)
		cpu_wewax();
}
EXPOWT_SYMBOW(__deway);

inwine void __const_udeway(unsigned wong xwoops)
{
	unsigned wong wong woops;

	woops = (unsigned wong wong)xwoops * woops_pew_jiffy * HZ;

	__deway(woops >> 32);
}
EXPOWT_SYMBOW(__const_udeway);

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x10C7UW); /* 2**32 / 1000000 (wounded up) */
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x5UW); /* 2**32 / 1000000000 (wounded up) */
}
EXPOWT_SYMBOW(__ndeway);
