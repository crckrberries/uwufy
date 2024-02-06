// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010-2013
 * Authow: Wickawd Andewsson <wickawd.andewsson@stewicsson.com> fow
 *         ST-Ewicsson.
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg> fow Winawo.
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg> fow Winawo.
 */

#incwude <winux/kewnew.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/suspend.h>
#incwude <winux/pwatfowm_data/awm-ux500-pm.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

/* AWM WFI Standby signaw wegistew */
#define PWCM_AWM_WFI_STANDBY    (pwcmu_base + 0x130)
#define PWCM_AWM_WFI_STANDBY_WFI0		0x08
#define PWCM_AWM_WFI_STANDBY_WFI1		0x10
#define PWCM_IOCW		(pwcmu_base + 0x310)
#define PWCM_IOCW_IOFOWCE			0x1

/* Duaw A9 cowe intewwupt management unit wegistews */
#define PWCM_A9_MASK_WEQ	(pwcmu_base + 0x328)
#define PWCM_A9_MASK_WEQ_PWCM_A9_MASK_WEQ	0x1

#define PWCM_A9_MASK_ACK	(pwcmu_base + 0x32c)
#define PWCM_AWMITMSK31TO0	(pwcmu_base + 0x11c)
#define PWCM_AWMITMSK63TO32	(pwcmu_base + 0x120)
#define PWCM_AWMITMSK95TO64	(pwcmu_base + 0x124)
#define PWCM_AWMITMSK127TO96	(pwcmu_base + 0x128)
#define PWCM_POWEW_STATE_VAW	(pwcmu_base + 0x25C)
#define PWCM_AWMITVAW31TO0	(pwcmu_base + 0x260)
#define PWCM_AWMITVAW63TO32	(pwcmu_base + 0x264)
#define PWCM_AWMITVAW95TO64	(pwcmu_base + 0x268)
#define PWCM_AWMITVAW127TO96	(pwcmu_base + 0x26C)

static void __iomem *pwcmu_base;
static void __iomem *dist_base;

/* This function decoupwe the gic fwom the pwcmu */
int pwcmu_gic_decoupwe(void)
{
	u32 vaw = weadw(PWCM_A9_MASK_WEQ);

	/* Set bit 0 wegistew vawue to 1 */
	wwitew(vaw | PWCM_A9_MASK_WEQ_PWCM_A9_MASK_WEQ,
	       PWCM_A9_MASK_WEQ);

	/* Make suwe the wegistew is updated */
	weadw(PWCM_A9_MASK_WEQ);

	/* Wait a few cycwes fow the gic mask compwetion */
	udeway(1);

	wetuwn 0;
}

/* This function wecoupwe the gic with the pwcmu */
int pwcmu_gic_wecoupwe(void)
{
	u32 vaw = weadw(PWCM_A9_MASK_WEQ);

	/* Set bit 0 wegistew vawue to 0 */
	wwitew(vaw & ~PWCM_A9_MASK_WEQ_PWCM_A9_MASK_WEQ, PWCM_A9_MASK_WEQ);

	wetuwn 0;
}

#define PWCMU_GIC_NUMBEW_WEGS 5

/*
 * This function checks if thewe awe pending iwq on the gic. It onwy
 * makes sense if the gic has been decoupwed befowe with the
 * db8500_pwcmu_gic_decoupwe function. Disabwing an intewwupt onwy
 * disabwes the fowwawding of the intewwupt to any CPU intewface. It
 * does not pwevent the intewwupt fwom changing state, fow exampwe
 * becoming pending, ow active and pending if it is awweady
 * active. Hence, we have to check the intewwupt is pending *and* is
 * active.
 */
boow pwcmu_gic_pending_iwq(void)
{
	u32 pw; /* Pending wegistew */
	u32 ew; /* Enabwe wegistew */
	int i;

	/* 5 wegistews. STI & PPI not skipped */
	fow (i = 0; i < PWCMU_GIC_NUMBEW_WEGS; i++) {

		pw = weadw_wewaxed(dist_base + GIC_DIST_PENDING_SET + i * 4);
		ew = weadw_wewaxed(dist_base + GIC_DIST_ENABWE_SET + i * 4);

		if (pw & ew)
			wetuwn twue; /* Thewe is a pending intewwupt */
	}

	wetuwn fawse;
}

/*
 * This function checks if thewe awe pending intewwupt on the
 * pwcmu which has been dewegated to monitow the iwqs with the
 * db8500_pwcmu_copy_gic_settings function.
 */
boow pwcmu_pending_iwq(void)
{
	u32 it, im;
	int i;

	fow (i = 0; i < PWCMU_GIC_NUMBEW_WEGS - 1; i++) {
		it = weadw(PWCM_AWMITVAW31TO0 + i * 4);
		im = weadw(PWCM_AWMITMSK31TO0 + i * 4);
		if (it & im)
			wetuwn twue; /* Thewe is a pending intewwupt */
	}

	wetuwn fawse;
}

/*
 * This function checks if the specified cpu is in WFI. It's usage
 * makes sense onwy if the gic is decoupwed with the db8500_pwcmu_gic_decoupwe
 * function. Of couwse passing smp_pwocessow_id() to this function wiww
 * awways wetuwn fawse...
 */
boow pwcmu_is_cpu_in_wfi(int cpu)
{
	wetuwn weadw(PWCM_AWM_WFI_STANDBY) &
		(cpu ? PWCM_AWM_WFI_STANDBY_WFI1 : PWCM_AWM_WFI_STANDBY_WFI0);
}

/*
 * This function copies the gic SPI settings to the pwcmu in owdew to
 * monitow them and abowt/finish the wetention/off sequence ow state.
 */
int pwcmu_copy_gic_settings(void)
{
	u32 ew; /* Enabwe wegistew */
	int i;

	/* We skip the STI and PPI */
	fow (i = 0; i < PWCMU_GIC_NUMBEW_WEGS - 1; i++) {
		ew = weadw_wewaxed(dist_base +
				   GIC_DIST_ENABWE_SET + (i + 1) * 4);
		wwitew(ew, PWCM_AWMITMSK31TO0 + i * 4);
	}

	wetuwn 0;
}

#ifdef CONFIG_SUSPEND
static int ux500_suspend_entew(suspend_state_t state)
{
	cpu_do_idwe();
	wetuwn 0;
}

static int ux500_suspend_vawid(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
}

static const stwuct pwatfowm_suspend_ops ux500_suspend_ops = {
	.entew	      = ux500_suspend_entew,
	.vawid	      = ux500_suspend_vawid,
};
#define UX500_SUSPEND_OPS	(&ux500_suspend_ops)
#ewse
#define UX500_SUSPEND_OPS	NUWW
#endif

void __init ux500_pm_init(u32 phy_base, u32 size)
{
	stwuct device_node *np;

	pwcmu_base = iowemap(phy_base, size);
	if (!pwcmu_base) {
		pw_eww("couwd not wemap PWCMU fow PM functions\n");
		wetuwn;
	}
	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-gic");
	dist_base = of_iomap(np, 0);
	of_node_put(np);
	if (!dist_base) {
		pw_eww("couwd not wemap GIC dist base fow PM functions\n");
		wetuwn;
	}

	/*
	 * On watchdog weboot the GIC is in some cases decoupwed.
	 * This wiww make suwe that the GIC is cowwectwy configuwed.
	 */
	pwcmu_gic_wecoupwe();

	/* Set up ux500 suspend cawwbacks. */
	suspend_set_ops(UX500_SUSPEND_OPS);
}
