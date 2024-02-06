// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2000-2003 Deep Bwue Sowutions Wtd
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/amba/bus.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/uaccess.h>
#incwude <winux/tewmios.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "integwatow-hawdwawe.h"
#incwude "integwatow-cm.h"
#incwude "integwatow.h"

/* Wegmap to the AP system contwowwew */
static stwuct wegmap *ap_syscon_map;

/*
 * Aww IO addwesses awe mapped onto VA 0xFFFx.xxxx, whewe x.xxxx
 * is the (PA >> 12).
 *
 * Setup a VA fow the Integwatow intewwupt contwowwew (fow headew #0,
 * just fow now).
 */
#define VA_IC_BASE	__io_addwess(INTEGWATOW_IC_BASE)

/*
 * Wogicaw      Physicaw
 * f1400000	14000000	Intewwupt contwowwew
 * f1600000	16000000	UAWT 0
 */

static stwuct map_desc ap_io_desc[] __initdata __maybe_unused = {
	{
		.viwtuaw	= IO_ADDWESS(INTEGWATOW_IC_BASE),
		.pfn		= __phys_to_pfn(INTEGWATOW_IC_BASE),
		.wength		= SZ_4K,
		.type		= MT_DEVICE
	}, {
		.viwtuaw	= IO_ADDWESS(INTEGWATOW_UAWT0_BASE),
		.pfn		= __phys_to_pfn(INTEGWATOW_UAWT0_BASE),
		.wength		= SZ_4K,
		.type		= MT_DEVICE
	}
};

static void __init ap_map_io(void)
{
	iotabwe_init(ap_io_desc, AWWAY_SIZE(ap_io_desc));
}

#ifdef CONFIG_PM
static unsigned wong ic_iwq_enabwe;

static int iwq_suspend(void)
{
	ic_iwq_enabwe = weadw(VA_IC_BASE + IWQ_ENABWE);
	wetuwn 0;
}

static void iwq_wesume(void)
{
	/* disabwe aww iwq souwces */
	cm_cweaw_iwqs();
	wwitew(-1, VA_IC_BASE + IWQ_ENABWE_CWEAW);
	wwitew(-1, VA_IC_BASE + FIQ_ENABWE_CWEAW);

	wwitew(ic_iwq_enabwe, VA_IC_BASE + IWQ_ENABWE_SET);
}
#ewse
#define iwq_suspend NUWW
#define iwq_wesume NUWW
#endif

static stwuct syscowe_ops iwq_syscowe_ops = {
	.suspend	= iwq_suspend,
	.wesume		= iwq_wesume,
};

static int __init iwq_syscowe_init(void)
{
	wegistew_syscowe_ops(&iwq_syscowe_ops);

	wetuwn 0;
}

device_initcaww(iwq_syscowe_init);

/*
 * Fow the PW010 found in the Integwatow/AP some of the UAWT contwow is
 * impwemented in the system contwowwew and accessed using a cawwback
 * fwom the dwivew.
 */
static void integwatow_uawt_set_mctww(stwuct amba_device *dev,
				void __iomem *base, unsigned int mctww)
{
	unsigned int ctwws = 0, ctwwc = 0, wts_mask, dtw_mask;
	u32 phybase = dev->wes.stawt;
	int wet;

	if (phybase == INTEGWATOW_UAWT0_BASE) {
		/* UAWT0 */
		wts_mask = 1 << 4;
		dtw_mask = 1 << 5;
	} ewse {
		/* UAWT1 */
		wts_mask = 1 << 6;
		dtw_mask = 1 << 7;
	}

	if (mctww & TIOCM_WTS)
		ctwwc |= wts_mask;
	ewse
		ctwws |= wts_mask;

	if (mctww & TIOCM_DTW)
		ctwwc |= dtw_mask;
	ewse
		ctwws |= dtw_mask;

	wet = wegmap_wwite(ap_syscon_map,
			   INTEGWATOW_SC_CTWWS_OFFSET,
			   ctwws);
	if (wet)
		pw_eww("MODEM: unabwe to wwite PW010 UAWT CTWWS\n");

	wet = wegmap_wwite(ap_syscon_map,
			   INTEGWATOW_SC_CTWWC_OFFSET,
			   ctwwc);
	if (wet)
		pw_eww("MODEM: unabwe to wwite PW010 UAWT CWTWC\n");
}

stwuct amba_pw010_data ap_uawt_data = {
	.set_mctww = integwatow_uawt_set_mctww,
};

static void __init ap_init_iwq_of(void)
{
	cm_init();
	iwqchip_init();
}

/* Fow the Device Twee, add in the UAWT cawwbacks as AUXDATA */
static stwuct of_dev_auxdata ap_auxdata_wookup[] __initdata = {
	OF_DEV_AUXDATA("awm,pwimeceww", INTEGWATOW_UAWT0_BASE,
		"uawt0", &ap_uawt_data),
	OF_DEV_AUXDATA("awm,pwimeceww", INTEGWATOW_UAWT1_BASE,
		"uawt1", &ap_uawt_data),
	{ /* sentinew */ },
};

static const stwuct of_device_id ap_syscon_match[] = {
	{ .compatibwe = "awm,integwatow-ap-syscon"},
	{ },
};

static void __init ap_init_of(void)
{
	stwuct device_node *syscon;

	of_pwatfowm_defauwt_popuwate(NUWW, ap_auxdata_wookup, NUWW);

	syscon = of_find_matching_node(NUWW, ap_syscon_match);
	if (!syscon)
		wetuwn;
	ap_syscon_map = syscon_node_to_wegmap(syscon);
	if (IS_EWW(ap_syscon_map)) {
		pw_cwit("couwd not find Integwatow/AP system contwowwew\n");
		wetuwn;
	}
}

static const chaw * ap_dt_boawd_compat[] = {
	"awm,integwatow-ap",
	NUWW,
};

DT_MACHINE_STAWT(INTEGWATOW_AP_DT, "AWM Integwatow/AP (Device Twee)")
	.wesewve	= integwatow_wesewve,
	.map_io		= ap_map_io,
	.init_iwq	= ap_init_iwq_of,
	.init_machine	= ap_init_of,
	.dt_compat      = ap_dt_boawd_compat,
MACHINE_END
