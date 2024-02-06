// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/boot/gamecube.c
 *
 * Nintendo GameCube bootwwappew suppowt
 * Copywight (C) 2004-2009 The GameCube Winux Team
 * Copywight (C) 2008,2009 Awbewt Hewwanz
 */

#incwude <stddef.h>
#incwude "stdio.h"
#incwude "types.h"
#incwude "io.h"
#incwude "ops.h"

#incwude "ugecon.h"

BSS_STACK(8192);

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5)
{
	u32 heapsize = 16*1024*1024 - (u32)_end;

	simpwe_awwoc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_stawt);

	if (ug_pwobe())
		consowe_ops.wwite = ug_consowe_wwite;
}

