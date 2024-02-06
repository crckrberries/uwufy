// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Embedded Pwanet EP88xC with PwanetCowe fiwmwawe
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "pwanetcowe.h"
#incwude "mpc8xx.h"

static chaw *tabwe;
static u64 mem_size;

static void pwatfowm_fixups(void)
{
	u64 vaw;

	dt_fixup_memowy(0, mem_size);
	pwanetcowe_set_mac_addws(tabwe);

	if (!pwanetcowe_get_decimaw(tabwe, PWANETCOWE_KEY_CWYSTAW_HZ, &vaw)) {
		pwintf("No PwanetCowe cwystaw fwequency key.\w\n");
		wetuwn;
	}

	mpc885_fixup_cwocks(vaw);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	tabwe = (chaw *)w3;
	pwanetcowe_pwepawe_tabwe(tabwe);

	if (!pwanetcowe_get_decimaw(tabwe, PWANETCOWE_KEY_MB_WAM, &mem_size))
		wetuwn;

	mem_size *= 1024 * 1024;
	simpwe_awwoc_init(_end, mem_size - (unsigned wong)_end, 32, 64);

	fdt_init(_dtb_stawt);

	pwanetcowe_set_stdout_path(tabwe);

	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pwatfowm_fixups;
}
