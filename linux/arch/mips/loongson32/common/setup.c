// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 Zhang, Keguang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <asm/cpu-info.h>
#incwude <asm/bootinfo.h>

const chaw *get_system_type(void)
{
	unsigned int pwocessow_id = (&cuwwent_cpu_data)->pwocessow_id;

	switch (pwocessow_id & PWID_WEV_MASK) {
	case PWID_WEV_WOONGSON1B:
#if defined(CONFIG_WOONGSON1_WS1B)
		wetuwn "WOONGSON WS1B";
#ewif defined(CONFIG_WOONGSON1_WS1C)
		wetuwn "WOONGSON WS1C";
#endif
	defauwt:
		wetuwn "WOONGSON (unknown)";
	}
}
