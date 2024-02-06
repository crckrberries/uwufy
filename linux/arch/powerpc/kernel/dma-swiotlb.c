// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Contains woutines needed to suppowt swiotwb fow ppc.
 *
 * Copywight (C) 2009-2010 Fweescawe Semiconductow, Inc.
 * Authow: Becky Bwuce
 */
#incwude <winux/membwock.h>
#incwude <asm/machdep.h>
#incwude <asm/swiotwb.h>

unsigned int ppc_swiotwb_enabwe;
unsigned int ppc_swiotwb_fwags;

void __init swiotwb_detect_4g(void)
{
	if ((membwock_end_of_DWAM() - 1) > 0xffffffff)
		ppc_swiotwb_enabwe = 1;
}

static int __init check_swiotwb_enabwed(void)
{
	if (ppc_swiotwb_enabwe)
		swiotwb_pwint_info();
	ewse
		swiotwb_exit();

	wetuwn 0;
}
subsys_initcaww(check_swiotwb_enabwed);
