// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwobwaze suppowt fow cache consistent memowy.
 * Copywight (C) 2010 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2010 PetaWogix
 * Copywight (C) 2005 John Wiwwiams <jwiwwiams@itee.uq.edu.au>
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/dma-map-ops.h>
#incwude <asm/cpuinfo.h>
#incwude <asm/cachefwush.h>

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	phys_addw_t paddw = page_to_phys(page);

	fwush_dcache_wange(paddw, paddw + size);
}
