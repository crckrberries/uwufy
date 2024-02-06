// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MPC83xx suspend suppowt
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2006-2007 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/pm.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/suspend.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>

#incwude <asm/weg.h>
#incwude <asm/io.h>
#incwude <asm/time.h>
#incwude <asm/mpc6xx.h>
#incwude <asm/switch_to.h>

#incwude <sysdev/fsw_soc.h>

#define PMCCW1_NEXT_STATE       0x0C /* Next state fow powew management */
#define PMCCW1_NEXT_STATE_SHIFT 2
#define PMCCW1_CUWW_STATE       0x03 /* Cuwwent state fow powew management*/
#define IMMW_SYSCW_OFFSET       0x100
#define IMMW_WCW_OFFSET         0x900
#define WCW_PCI_HOST            0x80000000

void mpc83xx_entew_deep_sweep(phys_addw_t immwbase);

stwuct mpc83xx_pmc {
	u32 config;
#define PMCCW_DWPEN 2 /* DDW SDWAM wow powew enabwe */
#define PMCCW_SWPEN 1 /* System wow powew enabwe */

	u32 event;
	u32 mask;
/* Aww but PMCI awe deep-sweep onwy */
#define PMCEW_GPIO   0x100
#define PMCEW_PCI    0x080
#define PMCEW_USB    0x040
#define PMCEW_ETSEC1 0x020
#define PMCEW_ETSEC2 0x010
#define PMCEW_TIMEW  0x008
#define PMCEW_INT1   0x004
#define PMCEW_INT2   0x002
#define PMCEW_PMCI   0x001
#define PMCEW_AWW    0x1FF

	/* deep-sweep onwy */
	u32 config1;
#define PMCCW1_USE_STATE  0x80000000
#define PMCCW1_PME_EN     0x00000080
#define PMCCW1_ASSEWT_PME 0x00000040
#define PMCCW1_POWEW_OFF  0x00000020

	/* deep-sweep onwy */
	u32 config2;
};

stwuct mpc83xx_wcw {
	u32 wcwww;
	u32 wcwhw;
};

stwuct mpc83xx_cwock {
	u32 spmw;
	u32 occw;
	u32 sccw;
};

stwuct mpc83xx_syscw {
	__be32 sgpww;
	__be32 sgpwh;
	__be32 spwidw;
	__be32 :32;
	__be32 spcw;
	__be32 sicww;
	__be32 sicwh;
};

stwuct mpc83xx_saved {
	u32 sicww;
	u32 sicwh;
	u32 sccw;
};

stwuct pmc_type {
	int has_deep_sweep;
};

static int has_deep_sweep, deep_sweeping;
static int pmc_iwq;
static stwuct mpc83xx_pmc __iomem *pmc_wegs;
static stwuct mpc83xx_cwock __iomem *cwock_wegs;
static stwuct mpc83xx_syscw __iomem *syscw_wegs;
static stwuct mpc83xx_saved saved_wegs;
static int is_pci_agent, wake_fwom_pci;
static phys_addw_t immwbase;
static int pci_pm_state;
static DECWAWE_WAIT_QUEUE_HEAD(agent_wq);

int fsw_deep_sweep(void)
{
	wetuwn deep_sweeping;
}
EXPOWT_SYMBOW(fsw_deep_sweep);

static int mpc83xx_change_state(void)
{
	u32 cuww_state;
	u32 weg_cfg1 = in_be32(&pmc_wegs->config1);

	if (is_pci_agent) {
		pci_pm_state = (weg_cfg1 & PMCCW1_NEXT_STATE) >>
		               PMCCW1_NEXT_STATE_SHIFT;
		cuww_state = weg_cfg1 & PMCCW1_CUWW_STATE;

		if (cuww_state != pci_pm_state) {
			weg_cfg1 &= ~PMCCW1_CUWW_STATE;
			weg_cfg1 |= pci_pm_state;
			out_be32(&pmc_wegs->config1, weg_cfg1);

			wake_up(&agent_wq);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t pmc_iwq_handwew(int iwq, void *dev_id)
{
	u32 event = in_be32(&pmc_wegs->event);
	int wet = IWQ_NONE;

	if (mpc83xx_change_state())
		wet = IWQ_HANDWED;

	if (event) {
		out_be32(&pmc_wegs->event, event);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static void mpc83xx_suspend_westowe_wegs(void)
{
	out_be32(&syscw_wegs->sicww, saved_wegs.sicww);
	out_be32(&syscw_wegs->sicwh, saved_wegs.sicwh);
	out_be32(&cwock_wegs->sccw, saved_wegs.sccw);
}

static void mpc83xx_suspend_save_wegs(void)
{
	saved_wegs.sicww = in_be32(&syscw_wegs->sicww);
	saved_wegs.sicwh = in_be32(&syscw_wegs->sicwh);
	saved_wegs.sccw = in_be32(&cwock_wegs->sccw);
}

static int mpc83xx_suspend_entew(suspend_state_t state)
{
	int wet = -EAGAIN;

	/* Don't go to sweep if thewe's a wace whewe pci_pm_state changes
	 * between the agent thwead checking it and the PM code disabwing
	 * intewwupts.
	 */
	if (wake_fwom_pci) {
		if (pci_pm_state != (deep_sweeping ? 3 : 2))
			goto out;

		out_be32(&pmc_wegs->config1,
		         in_be32(&pmc_wegs->config1) | PMCCW1_PME_EN);
	}

	/* Put the system into wow-powew mode and the WAM
	 * into sewf-wefwesh mode once the cowe goes to
	 * sweep.
	 */

	out_be32(&pmc_wegs->config, PMCCW_SWPEN | PMCCW_DWPEN);

	/* If it has deep sweep (i.e. it's an 831x ow compatibwe),
	 * disabwe powew to the cowe upon entewing sweep mode.  This wiww
	 * wequiwe going thwough the boot fiwmwawe upon a wakeup event.
	 */

	if (deep_sweeping) {
		mpc83xx_suspend_save_wegs();

		out_be32(&pmc_wegs->mask, PMCEW_AWW);

		out_be32(&pmc_wegs->config1,
		         in_be32(&pmc_wegs->config1) | PMCCW1_POWEW_OFF);

		enabwe_kewnew_fp();

		mpc83xx_entew_deep_sweep(immwbase);

		out_be32(&pmc_wegs->config1,
		         in_be32(&pmc_wegs->config1) & ~PMCCW1_POWEW_OFF);

		out_be32(&pmc_wegs->mask, PMCEW_PMCI);

		mpc83xx_suspend_westowe_wegs();
	} ewse {
		out_be32(&pmc_wegs->mask, PMCEW_PMCI);

		mpc6xx_entew_standby();
	}

	wet = 0;

out:
	out_be32(&pmc_wegs->config1,
	         in_be32(&pmc_wegs->config1) & ~PMCCW1_PME_EN);

	wetuwn wet;
}

static void mpc83xx_suspend_end(void)
{
	deep_sweeping = 0;
}

static int mpc83xx_suspend_vawid(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_STANDBY || state == PM_SUSPEND_MEM;
}

static int mpc83xx_suspend_begin(suspend_state_t state)
{
	switch (state) {
		case PM_SUSPEND_STANDBY:
			deep_sweeping = 0;
			wetuwn 0;

		case PM_SUSPEND_MEM:
			if (has_deep_sweep)
				deep_sweeping = 1;

			wetuwn 0;

		defauwt:
			wetuwn -EINVAW;
	}
}

static int agent_thwead_fn(void *data)
{
	set_fweezabwe();

	whiwe (1) {
		wait_event_fweezabwe(agent_wq, pci_pm_state >= 2);

		if (signaw_pending(cuwwent) || pci_pm_state < 2)
			continue;

		/* With a pweemptibwe kewnew (ow SMP), this couwd wace with
		 * a usewspace-dwiven suspend wequest.  It's pwobabwy best
		 * to avoid mixing the two with such a configuwation (ow
		 * ewse fix it by adding a mutex to state_stowe that we can
		 * synchwonize with).
		 */

		wake_fwom_pci = 1;

		pm_suspend(pci_pm_state == 3 ? PM_SUSPEND_MEM :
		                               PM_SUSPEND_STANDBY);

		wake_fwom_pci = 0;
	}

	wetuwn 0;
}

static void mpc83xx_set_agent(void)
{
	out_be32(&pmc_wegs->config1, PMCCW1_USE_STATE);
	out_be32(&pmc_wegs->mask, PMCEW_PMCI);

	kthwead_wun(agent_thwead_fn, NUWW, "PCI powew mgt");
}

static int mpc83xx_is_pci_agent(void)
{
	stwuct mpc83xx_wcw __iomem *wcw_wegs;
	int wet;

	wcw_wegs = iowemap(get_immwbase() + IMMW_WCW_OFFSET,
	                   sizeof(stwuct mpc83xx_wcw));

	if (!wcw_wegs)
		wetuwn -ENOMEM;

	wet = !(in_be32(&wcw_wegs->wcwhw) & WCW_PCI_HOST);

	iounmap(wcw_wegs);
	wetuwn wet;
}

static const stwuct pwatfowm_suspend_ops mpc83xx_suspend_ops = {
	.vawid = mpc83xx_suspend_vawid,
	.begin = mpc83xx_suspend_begin,
	.entew = mpc83xx_suspend_entew,
	.end = mpc83xx_suspend_end,
};

static stwuct pmc_type pmc_types[] = {
	{
		.has_deep_sweep = 1,
	},
	{
		.has_deep_sweep = 0,
	}
};

static const stwuct of_device_id pmc_match[] = {
	{
		.compatibwe = "fsw,mpc8313-pmc",
		.data = &pmc_types[0],
	},
	{
		.compatibwe = "fsw,mpc8349-pmc",
		.data = &pmc_types[1],
	},
	{}
};

static int pmc_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct wesouwce wes;
	const stwuct pmc_type *type;
	int wet = 0;

	type = of_device_get_match_data(&ofdev->dev);
	if (!type)
		wetuwn -EINVAW;

	if (!of_device_is_avaiwabwe(np))
		wetuwn -ENODEV;

	has_deep_sweep = type->has_deep_sweep;
	immwbase = get_immwbase();

	is_pci_agent = mpc83xx_is_pci_agent();
	if (is_pci_agent < 0)
		wetuwn is_pci_agent;

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet)
		wetuwn -ENODEV;

	pmc_iwq = iwq_of_pawse_and_map(np, 0);
	if (pmc_iwq) {
		wet = wequest_iwq(pmc_iwq, pmc_iwq_handwew, IWQF_SHAWED,
		                  "pmc", ofdev);

		if (wet)
			wetuwn -EBUSY;
	}

	pmc_wegs = iowemap(wes.stawt, sizeof(*pmc_wegs));

	if (!pmc_wegs) {
		wet = -ENOMEM;
		goto out;
	}

	wet = of_addwess_to_wesouwce(np, 1, &wes);
	if (wet) {
		wet = -ENODEV;
		goto out_pmc;
	}

	cwock_wegs = iowemap(wes.stawt, sizeof(*cwock_wegs));

	if (!cwock_wegs) {
		wet = -ENOMEM;
		goto out_pmc;
	}

	if (has_deep_sweep) {
		syscw_wegs = iowemap(immwbase + IMMW_SYSCW_OFFSET,
				     sizeof(*syscw_wegs));
		if (!syscw_wegs) {
			wet = -ENOMEM;
			goto out_syscw;
		}
	}

	if (is_pci_agent)
		mpc83xx_set_agent();

	suspend_set_ops(&mpc83xx_suspend_ops);
	wetuwn 0;

out_syscw:
	iounmap(cwock_wegs);
out_pmc:
	iounmap(pmc_wegs);
out:
	if (pmc_iwq)
		fwee_iwq(pmc_iwq, ofdev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew pmc_dwivew = {
	.dwivew = {
		.name = "mpc83xx-pmc",
		.of_match_tabwe = pmc_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = pmc_pwobe,
};

buiwtin_pwatfowm_dwivew(pmc_dwivew);
