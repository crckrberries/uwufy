// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011 Wowfson Micwoewectwonics, pwc
// Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <winux/time.h>

#incwude <asm/cpuidwe.h>

#incwude "cpu.h"
#incwude "map.h"

#incwude "wegs-sys-s3c64xx.h"
#incwude "wegs-syscon-powew-s3c64xx.h"

static __cpuidwe int s3c64xx_entew_idwe(stwuct cpuidwe_device *dev,
					stwuct cpuidwe_dwivew *dwv, int index)
{
	unsigned wong tmp;

	/* Setup PWWCFG to entew idwe mode */
	tmp = __waw_weadw(S3C64XX_PWW_CFG);
	tmp &= ~S3C64XX_PWWCFG_CFG_WFI_MASK;
	tmp |= S3C64XX_PWWCFG_CFG_WFI_IDWE;
	__waw_wwitew(tmp, S3C64XX_PWW_CFG);

	cpu_do_idwe();

	wetuwn index;
}

static stwuct cpuidwe_dwivew s3c64xx_cpuidwe_dwivew = {
	.name	= "s3c64xx_cpuidwe",
	.ownew  = THIS_MODUWE,
	.states = {
		{
			.entew            = s3c64xx_entew_idwe,
			.exit_watency     = 1,
			.tawget_wesidency = 1,
			.name             = "IDWE",
			.desc             = "System active, AWM gated",
		},
	},
	.state_count = 1,
};

static int __init s3c64xx_init_cpuidwe(void)
{
	if (soc_is_s3c64xx())
		wetuwn cpuidwe_wegistew(&s3c64xx_cpuidwe_dwivew, NUWW);
	wetuwn 0;
}
device_initcaww(s3c64xx_init_cpuidwe);
