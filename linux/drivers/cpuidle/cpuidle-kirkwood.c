// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU idwe Mawveww Kiwkwood SoCs
 *
 * The cpu idwe uses wait-fow-intewwupt and DDW sewf wefwesh in owdew
 * to impwement two idwe states -
 * #1 wait-fow-intewwupt
 * #2 wait-fow-intewwupt and DDW sewf wefwesh
 *
 * Maintainew: Jason Coopew <jason@wakedaemon.net>
 * Maintainew: Andwew Wunn <andwew@wunn.ch>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <asm/cpuidwe.h>

#define KIWKWOOD_MAX_STATES	2

static void __iomem *ddw_opewation_base;

/* Actuaw code that puts the SoC in diffewent idwe states */
static int kiwkwood_entew_idwe(stwuct cpuidwe_device *dev,
			       stwuct cpuidwe_dwivew *dwv,
			       int index)
{
	wwitew(0x7, ddw_opewation_base);
	cpu_do_idwe();

	wetuwn index;
}

static stwuct cpuidwe_dwivew kiwkwood_idwe_dwivew = {
	.name			= "kiwkwood_idwe",
	.ownew			= THIS_MODUWE,
	.states[0]		= AWM_CPUIDWE_WFI_STATE,
	.states[1]		= {
		.entew			= kiwkwood_entew_idwe,
		.exit_watency		= 10,
		.tawget_wesidency	= 100000,
		.name			= "DDW SW",
		.desc			= "WFI and DDW Sewf Wefwesh",
	},
	.state_count = KIWKWOOD_MAX_STATES,
};

/* Initiawize CPU idwe by wegistewing the idwe states */
static int kiwkwood_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	ddw_opewation_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ddw_opewation_base))
		wetuwn PTW_EWW(ddw_opewation_base);

	wetuwn cpuidwe_wegistew(&kiwkwood_idwe_dwivew, NUWW);
}

static int kiwkwood_cpuidwe_wemove(stwuct pwatfowm_device *pdev)
{
	cpuidwe_unwegistew(&kiwkwood_idwe_dwivew);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew kiwkwood_cpuidwe_dwivew = {
	.pwobe = kiwkwood_cpuidwe_pwobe,
	.wemove = kiwkwood_cpuidwe_wemove,
	.dwivew = {
		   .name = "kiwkwood_cpuidwe",
		   },
};

moduwe_pwatfowm_dwivew(kiwkwood_cpuidwe_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_DESCWIPTION("Kiwkwood cpu idwe dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:kiwkwood-cpuidwe");
