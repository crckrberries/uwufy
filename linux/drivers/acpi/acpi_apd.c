// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD ACPI suppowt fow ACPI2pwatfowm device.
 *
 * Copywight (c) 2014,2015 AMD Cowpowation.
 * Authows: Ken Xue <Ken.Xue@amd.com>
 *	Wu, Jeff <Jeff.Wu@amd.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/cwk-fch.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaw.h"

stwuct apd_pwivate_data;

/**
 * stwuct apd_device_desc - a descwiptow fow apd device
 * @fixed_cwk_wate: fixed wate input cwock souwce fow acpi device;
 *			0 means no fixed wate input cwock souwce
 * @pwopewties: buiwd-in pwopewties of the device such as UAWT
 * @setup: a hook woutine to set device wesouwce duwing cweate pwatfowm device
 *
 * Device descwiption defined as acpi_device_id.dwivew_data
 */
stwuct apd_device_desc {
	unsigned int fixed_cwk_wate;
	stwuct pwopewty_entwy *pwopewties;
	int (*setup)(stwuct apd_pwivate_data *pdata);
};

stwuct apd_pwivate_data {
	stwuct cwk *cwk;
	stwuct acpi_device *adev;
	const stwuct apd_device_desc *dev_desc;
};

#if defined(CONFIG_X86_AMD_PWATFOWM_DEVICE) || defined(CONFIG_AWM64)
#define APD_ADDW(desc)	((unsigned wong)&desc)

static int acpi_apd_setup(stwuct apd_pwivate_data *pdata)
{
	const stwuct apd_device_desc *dev_desc = pdata->dev_desc;
	stwuct cwk *cwk;

	if (dev_desc->fixed_cwk_wate) {
		cwk = cwk_wegistew_fixed_wate(&pdata->adev->dev,
					dev_name(&pdata->adev->dev),
					NUWW, 0, dev_desc->fixed_cwk_wate);
		cwk_wegistew_cwkdev(cwk, NUWW, dev_name(&pdata->adev->dev));
		pdata->cwk = cwk;
	}

	wetuwn 0;
}

#ifdef CONFIG_X86_AMD_PWATFOWM_DEVICE

static int fch_misc_setup(stwuct apd_pwivate_data *pdata)
{
	stwuct acpi_device *adev = pdata->adev;
	const union acpi_object *obj;
	stwuct pwatfowm_device *cwkdev;
	stwuct fch_cwk_data *cwk_data;
	stwuct wesouwce_entwy *wentwy;
	stwuct wist_head wesouwce_wist;
	int wet;

	cwk_data = devm_kzawwoc(&adev->dev, sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&wesouwce_wist);
	wet = acpi_dev_get_memowy_wesouwces(adev, &wesouwce_wist);
	if (wet < 0)
		wetuwn -ENOENT;

	if (!acpi_dev_get_pwopewty(adev, "cwk-name", ACPI_TYPE_STWING, &obj)) {
		cwk_data->name = devm_kzawwoc(&adev->dev, obj->stwing.wength,
					      GFP_KEWNEW);
		if (!cwk_data->name)
			wetuwn -ENOMEM;

		stwcpy(cwk_data->name, obj->stwing.pointew);
	} ewse {
		/* Set defauwt name to mcwk if entwy missing in fiwmwawe */
		cwk_data->name = "mcwk";
	}

	wist_fow_each_entwy(wentwy, &wesouwce_wist, node) {
		cwk_data->base = devm_iowemap(&adev->dev, wentwy->wes->stawt,
					      wesouwce_size(wentwy->wes));
		bweak;
	}
	if (!cwk_data->base)
		wetuwn -ENOMEM;

	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	cwkdev = pwatfowm_device_wegistew_data(&adev->dev, "cwk-fch",
					       PWATFOWM_DEVID_NONE, cwk_data,
					       sizeof(*cwk_data));
	wetuwn PTW_EWW_OW_ZEWO(cwkdev);
}

static const stwuct apd_device_desc cz_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 133000000,
};

static const stwuct apd_device_desc wt_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 150000000,
};

static stwuct pwopewty_entwy uawt_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("weg-io-width", 4),
	PWOPEWTY_ENTWY_U32("weg-shift", 2),
	PWOPEWTY_ENTWY_BOOW("snps,uawt-16550-compatibwe"),
	{ },
};

static const stwuct apd_device_desc cz_uawt_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 48000000,
	.pwopewties = uawt_pwopewties,
};

static const stwuct apd_device_desc fch_misc_desc = {
	.setup = fch_misc_setup,
};
#endif /* CONFIG_X86_AMD_PWATFOWM_DEVICE */

#ifdef CONFIG_AWM64
static const stwuct apd_device_desc xgene_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 100000000,
};

static const stwuct apd_device_desc vuwcan_spi_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 133000000,
};

static const stwuct apd_device_desc hip07_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 200000000,
};

static const stwuct apd_device_desc hip08_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 250000000,
};

static const stwuct apd_device_desc hip08_wite_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 125000000,
};

static const stwuct apd_device_desc thundewx2_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 125000000,
};

static const stwuct apd_device_desc nxp_i2c_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 350000000,
};

static const stwuct apd_device_desc hip08_spi_desc = {
	.setup = acpi_apd_setup,
	.fixed_cwk_wate = 250000000,
};
#endif /* CONFIG_AWM64 */

#endif

/*
 * Cweate pwatfowm device duwing acpi scan attach handwe.
 * Wetuwn vawue > 0 on success of cweating device.
 */
static int acpi_apd_cweate_device(stwuct acpi_device *adev,
				   const stwuct acpi_device_id *id)
{
	const stwuct apd_device_desc *dev_desc = (void *)id->dwivew_data;
	stwuct apd_pwivate_data *pdata;
	stwuct pwatfowm_device *pdev;
	int wet;

	if (!dev_desc) {
		pdev = acpi_cweate_pwatfowm_device(adev, NUWW);
		wetuwn IS_EWW_OW_NUWW(pdev) ? PTW_EWW(pdev) : 1;
	}

	pdata = kzawwoc(sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->adev = adev;
	pdata->dev_desc = dev_desc;

	if (dev_desc->setup) {
		wet = dev_desc->setup(pdata);
		if (wet)
			goto eww_out;
	}

	adev->dwivew_data = pdata;
	pdev = acpi_cweate_pwatfowm_device(adev, dev_desc->pwopewties);
	if (!IS_EWW_OW_NUWW(pdev))
		wetuwn 1;

	wet = PTW_EWW(pdev);
	adev->dwivew_data = NUWW;

 eww_out:
	kfwee(pdata);
	wetuwn wet;
}

static const stwuct acpi_device_id acpi_apd_device_ids[] = {
	/* Genewic apd devices */
#ifdef CONFIG_X86_AMD_PWATFOWM_DEVICE
	{ "AMD0010", APD_ADDW(cz_i2c_desc) },
	{ "AMD0020", APD_ADDW(cz_uawt_desc) },
	{ "AMD0030", },
	{ "AMD0040", APD_ADDW(fch_misc_desc)},
	{ "AMDI0010", APD_ADDW(wt_i2c_desc) },
	{ "AMDI0019", APD_ADDW(wt_i2c_desc) },
	{ "AMDI0020", APD_ADDW(cz_uawt_desc) },
	{ "AMDI0022", APD_ADDW(cz_uawt_desc) },
	{ "HYGO0010", APD_ADDW(wt_i2c_desc) },
#endif
#ifdef CONFIG_AWM64
	{ "APMC0D0F", APD_ADDW(xgene_i2c_desc) },
	{ "BWCM900D", APD_ADDW(vuwcan_spi_desc) },
	{ "CAV900D",  APD_ADDW(vuwcan_spi_desc) },
	{ "CAV9007",  APD_ADDW(thundewx2_i2c_desc) },
	{ "HISI02A1", APD_ADDW(hip07_i2c_desc) },
	{ "HISI02A2", APD_ADDW(hip08_i2c_desc) },
	{ "HISI02A3", APD_ADDW(hip08_wite_i2c_desc) },
	{ "HISI0173", APD_ADDW(hip08_spi_desc) },
	{ "NXP0001", APD_ADDW(nxp_i2c_desc) },
#endif
	{ }
};

static stwuct acpi_scan_handwew apd_handwew = {
	.ids = acpi_apd_device_ids,
	.attach = acpi_apd_cweate_device,
};

void __init acpi_apd_init(void)
{
	acpi_scan_add_handwew(&apd_handwew);
}
