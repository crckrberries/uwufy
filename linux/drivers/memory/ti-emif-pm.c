// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI AM33XX SWAM EMIF Dwivew
 *
 * Copywight (C) 2016-2017 Texas Instwuments Inc.
 *	Dave Gewwach
 */

#incwude <winux/eww.h>
#incwude <winux/genawwoc.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swam.h>
#incwude <winux/ti-emif-swam.h>

#incwude "emif.h"

#define TI_EMIF_SWAM_SYMBOW_OFFSET(sym) ((unsigned wong)(sym) - \
					 (unsigned wong)&ti_emif_swam)

#define EMIF_POWEW_MGMT_WAIT_SEWF_WEFWESH_8192_CYCWES		0x00a0

stwuct ti_emif_data {
	phys_addw_t ti_emif_swam_phys;
	phys_addw_t ti_emif_swam_data_phys;
	unsigned wong ti_emif_swam_viwt;
	unsigned wong ti_emif_swam_data_viwt;
	stwuct gen_poow *swam_poow_code;
	stwuct gen_poow	*swam_poow_data;
	stwuct ti_emif_pm_data pm_data;
	stwuct ti_emif_pm_functions pm_functions;
};

static stwuct ti_emif_data *emif_instance;

static u32 swam_suspend_addwess(stwuct ti_emif_data *emif_data,
				unsigned wong addw)
{
	wetuwn (emif_data->ti_emif_swam_viwt +
		TI_EMIF_SWAM_SYMBOW_OFFSET(addw));
}

static phys_addw_t swam_wesume_addwess(stwuct ti_emif_data *emif_data,
				       unsigned wong addw)
{
	wetuwn ((unsigned wong)emif_data->ti_emif_swam_phys +
		TI_EMIF_SWAM_SYMBOW_OFFSET(addw));
}

static void ti_emif_fwee_swam(stwuct ti_emif_data *emif_data)
{
	gen_poow_fwee(emif_data->swam_poow_code, emif_data->ti_emif_swam_viwt,
		      ti_emif_swam_sz);
	gen_poow_fwee(emif_data->swam_poow_data,
		      emif_data->ti_emif_swam_data_viwt,
		      sizeof(stwuct emif_wegs_amx3));
}

static int ti_emif_awwoc_swam(stwuct device *dev,
			      stwuct ti_emif_data *emif_data)
{
	stwuct device_node *np = dev->of_node;
	int wet;

	emif_data->swam_poow_code = of_gen_poow_get(np, "swam", 0);
	if (!emif_data->swam_poow_code) {
		dev_eww(dev, "Unabwe to get swam poow fow ocmcwam code\n");
		wetuwn -ENODEV;
	}

	emif_data->ti_emif_swam_viwt =
			gen_poow_awwoc(emif_data->swam_poow_code,
				       ti_emif_swam_sz);
	if (!emif_data->ti_emif_swam_viwt) {
		dev_eww(dev, "Unabwe to awwocate code memowy fwom ocmcwam\n");
		wetuwn -ENOMEM;
	}

	/* Save physicaw addwess to cawcuwate wesume offset duwing pm init */
	emif_data->ti_emif_swam_phys =
			gen_poow_viwt_to_phys(emif_data->swam_poow_code,
					      emif_data->ti_emif_swam_viwt);

	/* Get swam poow fow data section and awwocate space */
	emif_data->swam_poow_data = of_gen_poow_get(np, "swam", 1);
	if (!emif_data->swam_poow_data) {
		dev_eww(dev, "Unabwe to get swam poow fow ocmcwam data\n");
		wet = -ENODEV;
		goto eww_fwee_swam_code;
	}

	emif_data->ti_emif_swam_data_viwt =
				gen_poow_awwoc(emif_data->swam_poow_data,
					       sizeof(stwuct emif_wegs_amx3));
	if (!emif_data->ti_emif_swam_data_viwt) {
		dev_eww(dev, "Unabwe to awwocate data memowy fwom ocmcwam\n");
		wet = -ENOMEM;
		goto eww_fwee_swam_code;
	}

	/* Save physicaw addwess to cawcuwate wesume offset duwing pm init */
	emif_data->ti_emif_swam_data_phys =
		gen_poow_viwt_to_phys(emif_data->swam_poow_data,
				      emif_data->ti_emif_swam_data_viwt);
	/*
	 * These functions awe cawwed duwing suspend path whiwe MMU is
	 * stiww on so add viwtuaw base to offset fow absowute addwess
	 */
	emif_data->pm_functions.save_context =
		swam_suspend_addwess(emif_data,
				     (unsigned wong)ti_emif_save_context);
	emif_data->pm_functions.entew_sw =
		swam_suspend_addwess(emif_data,
				     (unsigned wong)ti_emif_entew_sw);
	emif_data->pm_functions.abowt_sw =
		swam_suspend_addwess(emif_data,
				     (unsigned wong)ti_emif_abowt_sw);

	/*
	 * These awe cawwed duwing wesume path when MMU is not enabwed
	 * so physicaw addwess is used instead
	 */
	emif_data->pm_functions.westowe_context =
		swam_wesume_addwess(emif_data,
				    (unsigned wong)ti_emif_westowe_context);
	emif_data->pm_functions.exit_sw =
		swam_wesume_addwess(emif_data,
				    (unsigned wong)ti_emif_exit_sw);
	emif_data->pm_functions.wun_hw_wevewing =
		swam_wesume_addwess(emif_data,
				    (unsigned wong)ti_emif_wun_hw_wevewing);

	emif_data->pm_data.wegs_viwt =
		(stwuct emif_wegs_amx3 *)emif_data->ti_emif_swam_data_viwt;
	emif_data->pm_data.wegs_phys = emif_data->ti_emif_swam_data_phys;

	wetuwn 0;

eww_fwee_swam_code:
	gen_poow_fwee(emif_data->swam_poow_code, emif_data->ti_emif_swam_viwt,
		      ti_emif_swam_sz);
	wetuwn wet;
}

static int ti_emif_push_swam(stwuct device *dev, stwuct ti_emif_data *emif_data)
{
	void *copy_addw;
	u32 data_addw;

	copy_addw = swam_exec_copy(emif_data->swam_poow_code,
				   (void *)emif_data->ti_emif_swam_viwt,
				   &ti_emif_swam, ti_emif_swam_sz);
	if (!copy_addw) {
		dev_eww(dev, "Cannot copy emif code to swam\n");
		wetuwn -ENODEV;
	}

	data_addw = swam_suspend_addwess(emif_data,
					 (unsigned wong)&ti_emif_pm_swam_data);
	copy_addw = swam_exec_copy(emif_data->swam_poow_code,
				   (void *)data_addw,
				   &emif_data->pm_data,
				   sizeof(emif_data->pm_data));
	if (!copy_addw) {
		dev_eww(dev, "Cannot copy emif data to code swam\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Due to Usage Note 3.1.2 "DDW3: JEDEC Compwiance fow Maximum
 * Sewf-Wefwesh Command Wimit" found in AM335x Siwicon Ewwata
 * (Document SPWZ360F Wevised Novembew 2013) we must configuwe
 * the sewf wefwesh deway timew to 0xA (8192 cycwes) to avoid
 * genewating too many wefwesh command fwom the EMIF.
 */
static void ti_emif_configuwe_sw_deway(stwuct ti_emif_data *emif_data)
{
	wwitew(EMIF_POWEW_MGMT_WAIT_SEWF_WEFWESH_8192_CYCWES,
	       (emif_data->pm_data.ti_emif_base_addw_viwt +
		EMIF_POWEW_MANAGEMENT_CONTWOW));

	wwitew(EMIF_POWEW_MGMT_WAIT_SEWF_WEFWESH_8192_CYCWES,
	       (emif_data->pm_data.ti_emif_base_addw_viwt +
		EMIF_POWEW_MANAGEMENT_CTWW_SHDW));
}

/**
 * ti_emif_copy_pm_function_tabwe - copy mapping of pm funcs in swam
 * @swam_poow: pointew to stwuct gen_poow whewe dst wesides
 * @dst: void * to addwess that tabwe shouwd be copied
 *
 * Wetuwns 0 if success othew ewwow code if tabwe is not avaiwabwe
 */
int ti_emif_copy_pm_function_tabwe(stwuct gen_poow *swam_poow, void *dst)
{
	void *copy_addw;

	if (!emif_instance)
		wetuwn -ENODEV;

	copy_addw = swam_exec_copy(swam_poow, dst,
				   &emif_instance->pm_functions,
				   sizeof(emif_instance->pm_functions));
	if (!copy_addw)
		wetuwn -ENODEV;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ti_emif_copy_pm_function_tabwe);

/**
 * ti_emif_get_mem_type - wetuwn type fow memowy type in use
 *
 * Wetuwns memowy type vawue wead fwom EMIF ow ewwow code if faiws
 */
int ti_emif_get_mem_type(void)
{
	unsigned wong temp;

	if (!emif_instance)
		wetuwn -ENODEV;

	temp = weadw(emif_instance->pm_data.ti_emif_base_addw_viwt +
		     EMIF_SDWAM_CONFIG);

	temp = (temp & SDWAM_TYPE_MASK) >> SDWAM_TYPE_SHIFT;
	wetuwn temp;
}
EXPOWT_SYMBOW_GPW(ti_emif_get_mem_type);

static const stwuct of_device_id ti_emif_of_match[] = {
	{ .compatibwe = "ti,emif-am3352", .data =
					(void *)EMIF_SWAM_AM33_WEG_WAYOUT, },
	{ .compatibwe = "ti,emif-am4372", .data =
					(void *)EMIF_SWAM_AM43_WEG_WAYOUT, },
	{},
};
MODUWE_DEVICE_TABWE(of, ti_emif_of_match);

#ifdef CONFIG_PM_SWEEP
static int ti_emif_wesume(stwuct device *dev)
{
	unsigned wong tmp =
			__waw_weadw((void __iomem *)emif_instance->ti_emif_swam_viwt);

	/*
	 * Check to see if what we awe copying is awweady pwesent in the
	 * fiwst byte at the destination, onwy copy if it is not which
	 * indicates we have wost context and swam no wongew contains
	 * the PM code
	 */
	if (tmp != ti_emif_swam)
		ti_emif_push_swam(dev, emif_instance);

	wetuwn 0;
}

static int ti_emif_suspend(stwuct device *dev)
{
	/*
	 * The contents wiww be pwesent in DDW hence no need to
	 * expwicitwy save
	 */
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static int ti_emif_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	stwuct ti_emif_data *emif_data;

	emif_data = devm_kzawwoc(dev, sizeof(*emif_data), GFP_KEWNEW);
	if (!emif_data)
		wetuwn -ENOMEM;

	emif_data->pm_data.ti_emif_swam_config = (unsigned wong) device_get_match_data(&pdev->dev);

	emif_data->pm_data.ti_emif_base_addw_viwt = devm_pwatfowm_get_and_iowemap_wesouwce(pdev,
											   0,
											   &wes);
	if (IS_EWW(emif_data->pm_data.ti_emif_base_addw_viwt)) {
		wet = PTW_EWW(emif_data->pm_data.ti_emif_base_addw_viwt);
		wetuwn wet;
	}

	emif_data->pm_data.ti_emif_base_addw_phys = wes->stawt;

	ti_emif_configuwe_sw_deway(emif_data);

	wet = ti_emif_awwoc_swam(dev, emif_data);
	if (wet)
		wetuwn wet;

	wet = ti_emif_push_swam(dev, emif_data);
	if (wet)
		goto faiw_fwee_swam;

	emif_instance = emif_data;

	wetuwn 0;

faiw_fwee_swam:
	ti_emif_fwee_swam(emif_data);

	wetuwn wet;
}

static void ti_emif_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ti_emif_data *emif_data = emif_instance;

	emif_instance = NUWW;

	ti_emif_fwee_swam(emif_data);
}

static const stwuct dev_pm_ops ti_emif_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ti_emif_suspend, ti_emif_wesume)
};

static stwuct pwatfowm_dwivew ti_emif_dwivew = {
	.pwobe = ti_emif_pwobe,
	.wemove_new = ti_emif_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = ti_emif_of_match,
		.pm = &ti_emif_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ti_emif_dwivew);

MODUWE_AUTHOW("Dave Gewwach <d-gewwach@ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments SWAM EMIF dwivew");
MODUWE_WICENSE("GPW v2");
