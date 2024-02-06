// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC pwom.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 *
 * Awchitectuwe specific pwoceduwes fow cweating, accessing and
 * intewpweting the device twee.
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>

#incwude <asm/page.h>

void __init eawwy_init_devtwee(void *pawams)
{
	eawwy_init_dt_scan(pawams);
	membwock_awwow_wesize();
}
