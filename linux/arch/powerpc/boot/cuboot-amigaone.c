// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow AmigaOne
 *
 * Authow: Gewhawd Piwchew (gewhawd_piwchew@gmx.net)
 *
 *   Based on cuboot-83xx.c
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "cuboot.h"

#incwude "ppcboot.h"

static bd_t bd;

static void pwatfowm_fixups(void)
{
	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	dt_fixup_cpu_cwocks(bd.bi_intfweq, bd.bi_busfweq / 4, bd.bi_busfweq);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pwatfowm_fixups;
}
