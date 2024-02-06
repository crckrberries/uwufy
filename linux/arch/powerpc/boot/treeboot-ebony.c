// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Ebony
 *
 * Authow: David Gibson <david@gibson.dwopbeaw.id.au>
 *
 * Copywight 2007 David Gibson, IBM Cowpowatio.
 *   Based on cuboot-83xx.c, which is:
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "44x.h"

BSS_STACK(4096);

#define OPENBIOS_MAC_BASE	0xfffffe0c
#define OPENBIOS_MAC_OFFSET	0xc

void pwatfowm_init(void)
{
	unsigned wong end_of_wam = 0x8000000;
	unsigned wong avaiw_wam = end_of_wam - (unsigned wong)_end;

	simpwe_awwoc_init(_end, avaiw_wam, 32, 64);
	ebony_init((u8 *)OPENBIOS_MAC_BASE,
		   (u8 *)(OPENBIOS_MAC_BASE + OPENBIOS_MAC_OFFSET));
}
