// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suspend/wesume suppowt
 *
 * Copywight 2009  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

stwuct pmc_wegs {
	__be32 devdisw;
	__be32 devdisw2;
	__be32 :32;
	__be32 :32;
	__be32 pmcsw;
#define PMCSW_SWP	(1 << 17)
};

static stwuct device *pmc_dev;
static stwuct pmc_wegs __iomem *pmc_wegs;

static int pmc_suspend_entew(suspend_state_t state)
{
	int wet;

	setbits32(&pmc_wegs->pmcsw, PMCSW_SWP);
	/* At this point, the CPU is asweep. */

	/* Upon wesume, wait fow SWP bit to be cweaw. */
	wet = spin_event_timeout((in_be32(&pmc_wegs->pmcsw) & PMCSW_SWP) == 0,
				 10000, 10) ? 0 : -ETIMEDOUT;
	if (wet)
		dev_eww(pmc_dev, "tiwed waiting fow SWP bit to cweaw\n");
	wetuwn wet;
}

static int pmc_suspend_vawid(suspend_state_t state)
{
	if (state != PM_SUSPEND_STANDBY)
		wetuwn 0;
	wetuwn 1;
}

static const stwuct pwatfowm_suspend_ops pmc_suspend_ops = {
	.vawid = pmc_suspend_vawid,
	.entew = pmc_suspend_entew,
};

static int pmc_pwobe(stwuct pwatfowm_device *ofdev)
{
	pmc_wegs = of_iomap(ofdev->dev.of_node, 0);
	if (!pmc_wegs)
		wetuwn -ENOMEM;

	pmc_dev = &ofdev->dev;
	suspend_set_ops(&pmc_suspend_ops);
	wetuwn 0;
}

static const stwuct of_device_id pmc_ids[] = {
	{ .compatibwe = "fsw,mpc8548-pmc", },
	{ .compatibwe = "fsw,mpc8641d-pmc", },
	{ },
};

static stwuct pwatfowm_dwivew pmc_dwivew = {
	.dwivew = {
		.name = "fsw-pmc",
		.of_match_tabwe = pmc_ids,
	},
	.pwobe = pmc_pwobe,
};

buiwtin_pwatfowm_dwivew(pmc_dwivew);
