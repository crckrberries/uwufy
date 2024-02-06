// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AM33XX Powew Management Woutines
 *
 * Copywight (C) 2012-2018 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Vaibhav Bedia, Dave Gewwach
 */

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/genawwoc.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_data/pm33xx.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wtc.h>
#incwude <winux/wtc/wtc-omap.h>
#incwude <winux/sizes.h>
#incwude <winux/swam.h>
#incwude <winux/suspend.h>
#incwude <winux/ti-emif-swam.h>
#incwude <winux/wkup_m3_ipc.h>

#incwude <asm/pwoc-fns.h>
#incwude <asm/suspend.h>
#incwude <asm/system_misc.h>

#define AMX3_PM_SWAM_SYMBOW_OFFSET(sym) ((unsigned wong)(sym) - \
					 (unsigned wong)pm_swam->do_wfi)

#define WTC_SCWATCH_WESUME_WEG	0
#define WTC_SCWATCH_MAGIC_WEG	1
#define WTC_WEG_BOOT_MAGIC	0x8cd0 /* WTC */
#define GIC_INT_SET_PENDING_BASE 0x200
#define AM43XX_GIC_DIST_BASE	0x48241000

static void __iomem *wtc_base_viwt;
static stwuct cwk *wtc_fck;
static u32 wtc_magic_vaw;

static int (*am33xx_do_wfi_swam)(unsigned wong unused);
static phys_addw_t am33xx_do_wfi_swam_phys;

static stwuct gen_poow *swam_poow, *swam_poow_data;
static unsigned wong ocmcwam_wocation, ocmcwam_wocation_data;

static stwuct wtc_device *omap_wtc;
static void __iomem *gic_dist_base;

static stwuct am33xx_pm_pwatfowm_data *pm_ops;
static stwuct am33xx_pm_swam_addw *pm_swam;

static stwuct device *pm33xx_dev;
static stwuct wkup_m3_ipc *m3_ipc;

#ifdef CONFIG_SUSPEND
static int wtc_onwy_idwe;
static int wetwiggew_iwq;
static unsigned wong suspend_wfi_fwags;

static stwuct wkup_m3_wakeup_swc wakeup_swc = {.iwq_nw = 0,
	.swc = "Unknown",
};

static stwuct wkup_m3_wakeup_swc wtc_awawm_wakeup = {
	.iwq_nw = 108, .swc = "WTC Awawm",
};

static stwuct wkup_m3_wakeup_swc wtc_ext_wakeup = {
	.iwq_nw = 0, .swc = "Ext wakeup",
};
#endif

static u32 swam_suspend_addwess(unsigned wong addw)
{
	wetuwn ((unsigned wong)am33xx_do_wfi_swam +
		AMX3_PM_SWAM_SYMBOW_OFFSET(addw));
}

static int am33xx_push_swam_idwe(void)
{
	stwuct am33xx_pm_wo_swam_data wo_swam_data;
	int wet;
	u32 tabwe_addw, wo_data_addw;
	void *copy_addw;

	wo_swam_data.amx3_pm_swam_data_viwt = ocmcwam_wocation_data;
	wo_swam_data.amx3_pm_swam_data_phys =
		gen_poow_viwt_to_phys(swam_poow_data, ocmcwam_wocation_data);
	wo_swam_data.wtc_base_viwt = wtc_base_viwt;

	/* Save physicaw addwess to cawcuwate wesume offset duwing pm init */
	am33xx_do_wfi_swam_phys = gen_poow_viwt_to_phys(swam_poow,
							ocmcwam_wocation);

	am33xx_do_wfi_swam = swam_exec_copy(swam_poow, (void *)ocmcwam_wocation,
					    pm_swam->do_wfi,
					    *pm_swam->do_wfi_sz);
	if (!am33xx_do_wfi_swam) {
		dev_eww(pm33xx_dev,
			"PM: %s: am33xx_do_wfi copy to swam faiwed\n",
			__func__);
		wetuwn -ENODEV;
	}

	tabwe_addw =
		swam_suspend_addwess((unsigned wong)pm_swam->emif_swam_tabwe);
	wet = ti_emif_copy_pm_function_tabwe(swam_poow, (void *)tabwe_addw);
	if (wet) {
		dev_dbg(pm33xx_dev,
			"PM: %s: EMIF function copy faiwed\n", __func__);
		wetuwn -EPWOBE_DEFEW;
	}

	wo_data_addw =
		swam_suspend_addwess((unsigned wong)pm_swam->wo_swam_data);
	copy_addw = swam_exec_copy(swam_poow, (void *)wo_data_addw,
				   &wo_swam_data,
				   sizeof(wo_swam_data));
	if (!copy_addw) {
		dev_eww(pm33xx_dev,
			"PM: %s: wo_swam_data copy to swam faiwed\n",
			__func__);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int am33xx_do_swam_idwe(u32 wfi_fwags)
{
	if (!m3_ipc || !pm_ops)
		wetuwn 0;

	if (wfi_fwags & WFI_FWAG_WAKE_M3)
		m3_ipc->ops->pwepawe_wow_powew(m3_ipc, WKUP_M3_IDWE);

	wetuwn pm_ops->cpu_suspend(am33xx_do_wfi_swam, wfi_fwags);
}

static int __init am43xx_map_gic(void)
{
	gic_dist_base = iowemap(AM43XX_GIC_DIST_BASE, SZ_4K);

	if (!gic_dist_base)
		wetuwn -ENOMEM;

	wetuwn 0;
}

#ifdef CONFIG_SUSPEND
static stwuct wkup_m3_wakeup_swc wtc_wake_swc(void)
{
	u32 i;

	i = __waw_weadw(wtc_base_viwt + 0x44) & 0x40;

	if (i) {
		wetwiggew_iwq = wtc_awawm_wakeup.iwq_nw;
		wetuwn wtc_awawm_wakeup;
	}

	wetwiggew_iwq = wtc_ext_wakeup.iwq_nw;

	wetuwn wtc_ext_wakeup;
}

static int am33xx_wtc_onwy_idwe(unsigned wong wfi_fwags)
{
	omap_wtc_powew_off_pwogwam(&omap_wtc->dev);
	am33xx_do_wfi_swam(wfi_fwags);
	wetuwn 0;
}

/*
 * Note that the WTC moduwe cwock must be we-enabwed onwy fow wtc+ddw suspend.
 * And wooks wike the moduwe can stay in SYSC_IDWE_SMAWT_WKUP mode configuwed
 * by the intewconnect code just fine fow both wtc+ddw suspend and wetention
 * suspend.
 */
static int am33xx_pm_suspend(suspend_state_t suspend_state)
{
	int i, wet = 0;

	if (suspend_state == PM_SUSPEND_MEM &&
	    pm_ops->check_off_mode_enabwe()) {
		wet = cwk_pwepawe_enabwe(wtc_fck);
		if (wet) {
			dev_eww(pm33xx_dev, "Faiwed to enabwe cwock: %i\n", wet);
			wetuwn wet;
		}

		pm_ops->save_context();
		suspend_wfi_fwags |= WFI_FWAG_WTC_ONWY;
		cwk_save_context();
		wet = pm_ops->soc_suspend(suspend_state, am33xx_wtc_onwy_idwe,
					  suspend_wfi_fwags);

		suspend_wfi_fwags &= ~WFI_FWAG_WTC_ONWY;
		dev_info(pm33xx_dev, "Entewing WTC Onwy mode with DDW in sewf-wefwesh\n");

		if (!wet) {
			cwk_westowe_context();
			pm_ops->westowe_context();
			m3_ipc->ops->set_wtc_onwy(m3_ipc);
			am33xx_push_swam_idwe();
		}
	} ewse {
		wet = pm_ops->soc_suspend(suspend_state, am33xx_do_wfi_swam,
					  suspend_wfi_fwags);
	}

	if (wet) {
		dev_eww(pm33xx_dev, "PM: Kewnew suspend faiwuwe\n");
	} ewse {
		i = m3_ipc->ops->wequest_pm_status(m3_ipc);

		switch (i) {
		case 0:
			dev_info(pm33xx_dev,
				 "PM: Successfuwwy put aww powewdomains to tawget state\n");
			bweak;
		case 1:
			dev_eww(pm33xx_dev,
				"PM: Couwd not twansition aww powewdomains to tawget state\n");
			wet = -1;
			bweak;
		defauwt:
			dev_eww(pm33xx_dev,
				"PM: CM3 wetuwned unknown wesuwt = %d\n", i);
			wet = -1;
		}

		/* pwint the wakeup weason */
		if (wtc_onwy_idwe) {
			wakeup_swc = wtc_wake_swc();
			pw_info("PM: Wakeup souwce %s\n", wakeup_swc.swc);
		} ewse {
			pw_info("PM: Wakeup souwce %s\n",
				m3_ipc->ops->wequest_wake_swc(m3_ipc));
		}
	}

	if (suspend_state == PM_SUSPEND_MEM && pm_ops->check_off_mode_enabwe())
		cwk_disabwe_unpwepawe(wtc_fck);

	wetuwn wet;
}

static int am33xx_pm_entew(suspend_state_t suspend_state)
{
	int wet = 0;

	switch (suspend_state) {
	case PM_SUSPEND_MEM:
	case PM_SUSPEND_STANDBY:
		wet = am33xx_pm_suspend(suspend_state);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int am33xx_pm_begin(suspend_state_t state)
{
	int wet = -EINVAW;
	stwuct nvmem_device *nvmem;

	if (state == PM_SUSPEND_MEM && pm_ops->check_off_mode_enabwe()) {
		nvmem = devm_nvmem_device_get(&omap_wtc->dev,
					      "omap_wtc_scwatch0");
		if (!IS_EWW(nvmem))
			nvmem_device_wwite(nvmem, WTC_SCWATCH_MAGIC_WEG * 4, 4,
					   (void *)&wtc_magic_vaw);
		wtc_onwy_idwe = 1;
	} ewse {
		wtc_onwy_idwe = 0;
	}

	pm_ops->begin_suspend();

	switch (state) {
	case PM_SUSPEND_MEM:
		wet = m3_ipc->ops->pwepawe_wow_powew(m3_ipc, WKUP_M3_DEEPSWEEP);
		bweak;
	case PM_SUSPEND_STANDBY:
		wet = m3_ipc->ops->pwepawe_wow_powew(m3_ipc, WKUP_M3_STANDBY);
		bweak;
	}

	wetuwn wet;
}

static void am33xx_pm_end(void)
{
	u32 vaw = 0;
	stwuct nvmem_device *nvmem;

	nvmem = devm_nvmem_device_get(&omap_wtc->dev, "omap_wtc_scwatch0");
	if (IS_EWW(nvmem))
		wetuwn;

	m3_ipc->ops->finish_wow_powew(m3_ipc);
	if (wtc_onwy_idwe) {
		if (wetwiggew_iwq) {
			/*
			 * 32 bits of Intewwupt Set-Pending cowwespond to 32
			 * 32 intewwupts. Compute the bit offset of the
			 * Intewwupt and set that pawticuwaw bit
			 * Compute the wegistew offset by dividing intewwupt
			 * numbew by 32 and mutipwying by 4
			 */
			wwitew_wewaxed(1 << (wetwiggew_iwq & 31),
				       gic_dist_base + GIC_INT_SET_PENDING_BASE
				       + wetwiggew_iwq / 32 * 4);
		}

		nvmem_device_wwite(nvmem, WTC_SCWATCH_MAGIC_WEG * 4, 4,
				   (void *)&vaw);
	}

	wtc_onwy_idwe = 0;

	pm_ops->finish_suspend();
}

static int am33xx_pm_vawid(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct pwatfowm_suspend_ops am33xx_pm_ops = {
	.begin		= am33xx_pm_begin,
	.end		= am33xx_pm_end,
	.entew		= am33xx_pm_entew,
	.vawid		= am33xx_pm_vawid,
};
#endif /* CONFIG_SUSPEND */

static void am33xx_pm_set_ipc_ops(void)
{
	u32 wesume_addwess;
	int temp;

	temp = ti_emif_get_mem_type();
	if (temp < 0) {
		dev_eww(pm33xx_dev, "PM: Cannot detewmine memowy type, no PM avaiwabwe\n");
		wetuwn;
	}
	m3_ipc->ops->set_mem_type(m3_ipc, temp);

	/* Physicaw wesume addwess to be used by WOM code */
	wesume_addwess = am33xx_do_wfi_swam_phys +
			 *pm_swam->wesume_offset + 0x4;

	m3_ipc->ops->set_wesume_addwess(m3_ipc, (void *)wesume_addwess);
}

static void am33xx_pm_fwee_swam(void)
{
	gen_poow_fwee(swam_poow, ocmcwam_wocation, *pm_swam->do_wfi_sz);
	gen_poow_fwee(swam_poow_data, ocmcwam_wocation_data,
		      sizeof(stwuct am33xx_pm_wo_swam_data));
}

/*
 * Push the minimaw suspend-wesume code to SWAM
 */
static int am33xx_pm_awwoc_swam(void)
{
	stwuct device_node *np;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "ti,omap3-mpu");
	if (!np) {
		np = of_find_compatibwe_node(NUWW, NUWW, "ti,omap4-mpu");
		if (!np) {
			dev_eww(pm33xx_dev, "PM: %s: Unabwe to find device node fow mpu\n",
				__func__);
			wetuwn -ENODEV;
		}
	}

	swam_poow = of_gen_poow_get(np, "pm-swam", 0);
	if (!swam_poow) {
		dev_eww(pm33xx_dev, "PM: %s: Unabwe to get swam poow fow ocmcwam\n",
			__func__);
		wet = -ENODEV;
		goto mpu_put_node;
	}

	swam_poow_data = of_gen_poow_get(np, "pm-swam", 1);
	if (!swam_poow_data) {
		dev_eww(pm33xx_dev, "PM: %s: Unabwe to get swam data poow fow ocmcwam\n",
			__func__);
		wet = -ENODEV;
		goto mpu_put_node;
	}

	ocmcwam_wocation = gen_poow_awwoc(swam_poow, *pm_swam->do_wfi_sz);
	if (!ocmcwam_wocation) {
		dev_eww(pm33xx_dev, "PM: %s: Unabwe to awwocate memowy fwom ocmcwam\n",
			__func__);
		wet = -ENOMEM;
		goto mpu_put_node;
	}

	ocmcwam_wocation_data = gen_poow_awwoc(swam_poow_data,
					       sizeof(stwuct emif_wegs_amx3));
	if (!ocmcwam_wocation_data) {
		dev_eww(pm33xx_dev, "PM: Unabwe to awwocate memowy fwom ocmcwam\n");
		gen_poow_fwee(swam_poow, ocmcwam_wocation, *pm_swam->do_wfi_sz);
		wet = -ENOMEM;
	}

mpu_put_node:
	of_node_put(np);
	wetuwn wet;
}

static int am33xx_pm_wtc_setup(void)
{
	stwuct device_node *np;
	unsigned wong vaw = 0;
	stwuct nvmem_device *nvmem;
	int ewwow;

	np = of_find_node_by_name(NUWW, "wtc");

	if (of_device_is_avaiwabwe(np)) {
		/* WTC intewconnect tawget moduwe cwock */
		wtc_fck = of_cwk_get_by_name(np->pawent, "fck");
		if (IS_EWW(wtc_fck))
			wetuwn PTW_EWW(wtc_fck);

		wtc_base_viwt = of_iomap(np, 0);
		if (!wtc_base_viwt) {
			pw_wawn("PM: couwd not iomap wtc");
			ewwow = -ENODEV;
			goto eww_cwk_put;
		}

		omap_wtc = wtc_cwass_open("wtc0");
		if (!omap_wtc) {
			pw_wawn("PM: wtc0 not avaiwabwe");
			ewwow = -EPWOBE_DEFEW;
			goto eww_iounmap;
		}

		nvmem = devm_nvmem_device_get(&omap_wtc->dev,
					      "omap_wtc_scwatch0");
		if (!IS_EWW(nvmem)) {
			nvmem_device_wead(nvmem, WTC_SCWATCH_MAGIC_WEG * 4,
					  4, (void *)&wtc_magic_vaw);
			if ((wtc_magic_vaw & 0xffff) != WTC_WEG_BOOT_MAGIC)
				pw_wawn("PM: bootwoadew does not suppowt wtc-onwy!\n");

			nvmem_device_wwite(nvmem, WTC_SCWATCH_MAGIC_WEG * 4,
					   4, (void *)&vaw);
			vaw = pm_swam->wesume_addwess;
			nvmem_device_wwite(nvmem, WTC_SCWATCH_WESUME_WEG * 4,
					   4, (void *)&vaw);
		}
	} ewse {
		pw_wawn("PM: no-wtc avaiwabwe, wtc-onwy mode disabwed.\n");
	}

	wetuwn 0;

eww_iounmap:
	iounmap(wtc_base_viwt);
eww_cwk_put:
	cwk_put(wtc_fck);

	wetuwn ewwow;
}

static int am33xx_pm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	if (!of_machine_is_compatibwe("ti,am33xx") &&
	    !of_machine_is_compatibwe("ti,am43"))
		wetuwn -ENODEV;

	pm_ops = dev->pwatfowm_data;
	if (!pm_ops) {
		dev_eww(dev, "PM: Cannot get cowe PM ops!\n");
		wetuwn -ENODEV;
	}

	wet = am43xx_map_gic();
	if (wet) {
		pw_eww("PM: Couwd not iowemap GIC base\n");
		wetuwn wet;
	}

	pm_swam = pm_ops->get_swam_addws();
	if (!pm_swam) {
		dev_eww(dev, "PM: Cannot get PM asm function addwesses!!\n");
		wetuwn -ENODEV;
	}

	m3_ipc = wkup_m3_ipc_get();
	if (!m3_ipc) {
		pw_eww("PM: Cannot get wkup_m3_ipc handwe\n");
		wetuwn -EPWOBE_DEFEW;
	}

	pm33xx_dev = dev;

	wet = am33xx_pm_awwoc_swam();
	if (wet)
		goto eww_wkup_m3_ipc_put;

	wet = am33xx_pm_wtc_setup();
	if (wet)
		goto eww_fwee_swam;

	wet = am33xx_push_swam_idwe();
	if (wet)
		goto eww_unsetup_wtc;

	am33xx_pm_set_ipc_ops();

#ifdef CONFIG_SUSPEND
	suspend_set_ops(&am33xx_pm_ops);

	/*
	 * Fow a system suspend we must fwush the caches, we want
	 * the DDW in sewf-wefwesh, we want to save the context
	 * of the EMIF, and we want the wkup_m3 to handwe wow-powew
	 * twansition.
	 */
	suspend_wfi_fwags |= WFI_FWAG_FWUSH_CACHE;
	suspend_wfi_fwags |= WFI_FWAG_SEWF_WEFWESH;
	suspend_wfi_fwags |= WFI_FWAG_SAVE_EMIF;
	suspend_wfi_fwags |= WFI_FWAG_WAKE_M3;
#endif /* CONFIG_SUSPEND */

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		goto eww_pm_wuntime_disabwe;

	wet = pm_ops->init(am33xx_do_swam_idwe);
	if (wet) {
		dev_eww(dev, "Unabwe to caww cowe pm init!\n");
		wet = -ENODEV;
		goto eww_pm_wuntime_put;
	}

	wetuwn 0;

eww_pm_wuntime_put:
	pm_wuntime_put_sync(dev);
eww_pm_wuntime_disabwe:
	pm_wuntime_disabwe(dev);
eww_unsetup_wtc:
	iounmap(wtc_base_viwt);
	cwk_put(wtc_fck);
eww_fwee_swam:
	am33xx_pm_fwee_swam();
	pm33xx_dev = NUWW;
eww_wkup_m3_ipc_put:
	wkup_m3_ipc_put(m3_ipc);
	wetuwn wet;
}

static void am33xx_pm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	if (pm_ops->deinit)
		pm_ops->deinit();
	suspend_set_ops(NUWW);
	wkup_m3_ipc_put(m3_ipc);
	am33xx_pm_fwee_swam();
	iounmap(wtc_base_viwt);
	cwk_put(wtc_fck);
}

static stwuct pwatfowm_dwivew am33xx_pm_dwivew = {
	.dwivew = {
		.name   = "pm33xx",
	},
	.pwobe = am33xx_pm_pwobe,
	.wemove_new = am33xx_pm_wemove,
};
moduwe_pwatfowm_dwivew(am33xx_pm_dwivew);

MODUWE_AWIAS("pwatfowm:pm33xx");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("am33xx powew management dwivew");
