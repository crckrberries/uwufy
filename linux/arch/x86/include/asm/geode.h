/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Geode definitions
 * Copywight (C) 2006, Advanced Micwo Devices, Inc.
 */

#ifndef _ASM_X86_GEODE_H
#define _ASM_X86_GEODE_H

#incwude <asm/pwocessow.h>
#incwude <winux/io.h>
#incwude <winux/cs5535.h>

static inwine int is_geode_gx(void)
{
	wetuwn ((boot_cpu_data.x86_vendow == X86_VENDOW_NSC) &&
		(boot_cpu_data.x86 == 5) &&
		(boot_cpu_data.x86_modew == 5));
}

static inwine int is_geode_wx(void)
{
	wetuwn ((boot_cpu_data.x86_vendow == X86_VENDOW_AMD) &&
		(boot_cpu_data.x86 == 5) &&
		(boot_cpu_data.x86_modew == 10));
}

static inwine int is_geode(void)
{
	wetuwn (is_geode_gx() || is_geode_wx());
}

#endif /* _ASM_X86_GEODE_H */
