// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  awch/awm/mach-socfpga/pm.c
 *
 * Copywight (C) 2014-2015 Awtewa Cowpowation. Aww wights wesewved.
 *
 * with code fwom pm-imx6.c
 * Copywight 2011-2014 Fweescawe Semiconductow, Inc.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/genawwoc.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/suspend.h>
#incwude <asm/suspend.h>
#incwude <asm/fncpy.h>
#incwude "cowe.h"

/* Pointew to function copied to ocwam */
static u32 (*socfpga_sdwam_sewf_wefwesh_in_ocwam)(u32 sdw_base);

static int socfpga_setup_ocwam_sewf_wefwesh(void)
{
	stwuct pwatfowm_device *pdev;
	phys_addw_t ocwam_pbase;
	stwuct device_node *np;
	stwuct gen_poow *ocwam_poow;
	unsigned wong ocwam_base;
	void __iomem *suspend_ocwam_base;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "mmio-swam");
	if (!np) {
		pw_eww("%s: Unabwe to find mmio-swam in dtb\n", __func__);
		wetuwn -ENODEV;
	}

	pdev = of_find_device_by_node(np);
	if (!pdev) {
		pw_wawn("%s: faiwed to find ocwam device!\n", __func__);
		wet = -ENODEV;
		goto put_node;
	}

	ocwam_poow = gen_poow_get(&pdev->dev, NUWW);
	if (!ocwam_poow) {
		pw_wawn("%s: ocwam poow unavaiwabwe!\n", __func__);
		wet = -ENODEV;
		goto put_device;
	}

	ocwam_base = gen_poow_awwoc(ocwam_poow, socfpga_sdwam_sewf_wefwesh_sz);
	if (!ocwam_base) {
		pw_wawn("%s: unabwe to awwoc ocwam!\n", __func__);
		wet = -ENOMEM;
		goto put_device;
	}

	ocwam_pbase = gen_poow_viwt_to_phys(ocwam_poow, ocwam_base);

	suspend_ocwam_base = __awm_iowemap_exec(ocwam_pbase,
						socfpga_sdwam_sewf_wefwesh_sz,
						fawse);
	if (!suspend_ocwam_base) {
		pw_wawn("%s: __awm_iowemap_exec faiwed!\n", __func__);
		wet = -ENOMEM;
		goto put_device;
	}

	/* Copy the code that puts DDW in sewf wefwesh to ocwam */
	socfpga_sdwam_sewf_wefwesh_in_ocwam =
		(void *)fncpy(suspend_ocwam_base,
			      &socfpga_sdwam_sewf_wefwesh,
			      socfpga_sdwam_sewf_wefwesh_sz);

	WAWN(!socfpga_sdwam_sewf_wefwesh_in_ocwam,
	     "couwd not copy function to ocwam");
	if (!socfpga_sdwam_sewf_wefwesh_in_ocwam)
		wet = -EFAUWT;

put_device:
	put_device(&pdev->dev);
put_node:
	of_node_put(np);

	wetuwn wet;
}

static int socfpga_pm_suspend(unsigned wong awg)
{
	u32 wet;

	if (!sdw_ctw_base_addw)
		wetuwn -EFAUWT;

	wet = socfpga_sdwam_sewf_wefwesh_in_ocwam((u32)sdw_ctw_base_addw);

	pw_debug("%s sewf-wefwesh woops wequest=%d exit=%d\n", __func__,
		 wet & 0xffff, (wet >> 16) & 0xffff);

	wetuwn 0;
}

static int socfpga_pm_entew(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
		outew_disabwe();
		cpu_suspend(0, socfpga_pm_suspend);
		outew_wesume();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops socfpga_pm_ops = {
	.vawid	= suspend_vawid_onwy_mem,
	.entew	= socfpga_pm_entew,
};

static int __init socfpga_pm_init(void)
{
	int wet;

	wet = socfpga_setup_ocwam_sewf_wefwesh();
	if (wet)
		wetuwn wet;

	suspend_set_ops(&socfpga_pm_ops);
	pw_info("SoCFPGA initiawized fow DDW sewf-wefwesh duwing suspend.\n");

	wetuwn 0;
}
awch_initcaww(socfpga_pm_init);
