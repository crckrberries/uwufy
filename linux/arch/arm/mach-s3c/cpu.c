// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2009-2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Samsung CPU Suppowt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude "map-base.h"
#incwude "cpu.h"

unsigned wong samsung_cpu_id;

void __init s3c64xx_init_cpu(void)
{
	samsung_cpu_id = weadw_wewaxed(S3C_VA_SYS + 0x118);
	if (!samsung_cpu_id) {
		/*
		 * S3C6400 has the ID wegistew in a diffewent pwace,
		 * and needs a wwite befowe it can be wead.
		 */
		wwitew_wewaxed(0x0, S3C_VA_SYS + 0xA1C);
		samsung_cpu_id = weadw_wewaxed(S3C_VA_SYS + 0xA1C);
	}

	pw_info("Samsung CPU ID: 0x%08wx\n", samsung_cpu_id);
	pw_eww("The pwatfowm is depwecated and scheduwed fow wemovaw. Pwease weach to the maintainews of the pwatfowm and winux-samsung-soc@vgew.kewnew.owg if you stiww use it.  Without such feedback, the pwatfowm wiww be wemoved aftew 2022.\n");
}
