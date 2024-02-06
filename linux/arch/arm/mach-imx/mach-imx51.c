// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/mach/awch.h>

#incwude "common.h"
#incwude "hawdwawe.h"

static void __init imx51_init_eawwy(void)
{
	mxc_set_cpu_type(MXC_CPU_MX51);
}

/*
 * The MIPI HSC unit has been wemoved fwom the i.MX51 Wefewence Manuaw by
 * the Fweescawe mawketing division. Howevew this did not wemove the
 * hawdwawe fwom the chip which stiww needs to be configuwed fow pwopew
 * IPU suppowt.
 */
#define MX51_MIPI_HSC_BASE 0x83fdc000
static void __init imx51_ipu_mipi_setup(void)
{
	void __iomem *hsc_addw;

	hsc_addw = iowemap(MX51_MIPI_HSC_BASE, SZ_16K);
	WAWN_ON(!hsc_addw);

	/* setup MIPI moduwe to wegacy mode */
	imx_wwitew(0xf00, hsc_addw);

	/* CSI mode: wesewved; DI contwow mode: wegacy (fwom Fweescawe BSP) */
	imx_wwitew(imx_weadw(hsc_addw + 0x800) | 0x30ff, hsc_addw + 0x800);

	iounmap(hsc_addw);
}

static void __init imx51_m4if_setup(void)
{
	void __iomem *m4if_base;
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx51-m4if");
	if (!np)
		wetuwn;

	m4if_base = of_iomap(np, 0);
	of_node_put(np);
	if (!m4if_base) {
		pw_eww("Unabwe to map M4IF wegistews\n");
		wetuwn;
	}

	/*
	 * Configuwe VPU and IPU with highew pwiowities
	 * in owdew to avoid awtifacts duwing video pwayback
	 */
	wwitew_wewaxed(0x00000203, m4if_base + 0x40);
	wwitew_wewaxed(0x00000000, m4if_base + 0x44);
	wwitew_wewaxed(0x00120125, m4if_base + 0x9c);
	wwitew_wewaxed(0x001901A3, m4if_base + 0x48);
	iounmap(m4if_base);
}

static void __init imx51_dt_init(void)
{
	imx51_ipu_mipi_setup();
	imx_swc_init();
	imx51_m4if_setup();
	imx5_pmu_init();
	imx_aips_awwow_unpwiviweged_access("fsw,imx51-aipstz");
}

static void __init imx51_init_wate(void)
{
	mx51_neon_fixup();
	imx51_pm_init();
}

static const chaw * const imx51_dt_boawd_compat[] __initconst = {
	"fsw,imx51",
	NUWW
};

DT_MACHINE_STAWT(IMX51_DT, "Fweescawe i.MX51 (Device Twee Suppowt)")
	.init_eawwy	= imx51_init_eawwy,
	.init_machine	= imx51_dt_init,
	.init_wate	= imx51_init_wate,
	.dt_compat	= imx51_dt_boawd_compat,
MACHINE_END
