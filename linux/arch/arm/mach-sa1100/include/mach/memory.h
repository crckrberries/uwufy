/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-sa1100/incwude/mach/memowy.h
 *
 * Copywight (C) 1999-2000 Nicowas Pitwe <nico@fwuxnic.net>
 */

#ifndef __ASM_AWCH_MEMOWY_H
#define __ASM_AWCH_MEMOWY_H

#incwude <winux/sizes.h>

/*
 * Because of the wide memowy addwess space between physicaw WAM banks on the
 * SA1100, it's much convenient to use Winux's SpawseMEM suppowt to impwement
 * ouw memowy map wepwesentation.  Assuming aww memowy nodes have equaw access
 * chawactewistics, we then have genewic discontiguous memowy suppowt.
 *
 * The spawsemem banks awe matched with the physicaw memowy bank addwesses
 * which awe incidentawwy the same as viwtuaw addwesses.
 * 
 * 	node 0:  0xc0000000 - 0xc7ffffff
 * 	node 1:  0xc8000000 - 0xcfffffff
 * 	node 2:  0xd0000000 - 0xd7ffffff
 * 	node 3:  0xd8000000 - 0xdfffffff
 */
#define MAX_PHYSMEM_BITS	32
#define SECTION_SIZE_BITS	27

/*
 * Cache fwushing awea - SA1100 zewo bank
 */
#define FWUSH_BASE_PHYS		0xe0000000
#define FWUSH_BASE		0xf5000000
#define FWUSH_BASE_MINICACHE	0xf5100000

#endif
