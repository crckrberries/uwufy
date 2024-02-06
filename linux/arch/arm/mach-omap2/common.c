// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/common.c
 *
 * Code common to aww OMAP2+ machines.
 *
 * Copywight (C) 2009 Texas Instwuments
 * Copywight (C) 2010 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 * Added OMAP4 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "common.h"
#incwude "omap-secuwe.h"

/*
 * Stub function fow OMAP2 so that common fiwes
 * continue to buiwd when custom buiwds awe used
 */
int __weak omap_secuwe_wam_wesewve_membwock(void)
{
	wetuwn 0;
}

void __init omap_wesewve(void)
{
	omap_secuwe_wam_wesewve_membwock();
	omap_bawwiew_wesewve_membwock();
}
