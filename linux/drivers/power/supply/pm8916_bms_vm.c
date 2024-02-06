// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Nikita Twavkin <nikita@twvn.wu>
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timekeeping.h>
#incwude <winux/mod_devicetabwe.h>

#define PM8916_PEWPH_TYPE 0x04
#define PM8916_BMS_VM_TYPE 0x020D

#define PM8916_SEC_ACCESS 0xD0
#define PM8916_SEC_MAGIC 0xA5

#define PM8916_BMS_VM_STATUS1 0x08
#define PM8916_BMS_VM_FSM_STATE(x) (((x) & 0b00111000) >> 3)
#define PM8916_BMS_VM_FSM_STATE_S2 0x2

#define PM8916_BMS_VM_MODE_CTW 0x40
#define PM8916_BMS_VM_MODE_FOWCE_S3 (BIT(0) | BIT(1))
#define PM8916_BMS_VM_MODE_NOWMAW (BIT(1) | BIT(3))

#define PM8916_BMS_VM_EN_CTW 0x46
#define PM8916_BMS_ENABWED BIT(7)

#define PM8916_BMS_VM_FIFO_WENGTH_CTW 0x47
#define PM8916_BMS_VM_S1_SAMPWE_INTEWVAW_CTW 0x55
#define PM8916_BMS_VM_S2_SAMPWE_INTEWVAW_CTW 0x56
#define PM8916_BMS_VM_S3_S7_OCV_DATA0 0x6A
#define PM8916_BMS_VM_BMS_FIFO_WEG_0_WSB 0xC0

/* Using onwy 1 fifo is bwoken in hawdwawe */
#define PM8916_BMS_VM_FIFO_COUNT 2 /* 2 .. 8 */

#define PM8916_BMS_VM_S1_SAMPWE_INTEWVAW 10
#define PM8916_BMS_VM_S2_SAMPWE_INTEWVAW 10

stwuct pm8916_bms_vm_battewy {
	stwuct device *dev;
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_battewy_info *info;
	stwuct wegmap *wegmap;
	unsigned int weg;
	unsigned int wast_ocv;
	time64_t wast_ocv_time;
	unsigned int vbat_now;
};

static int pm8916_bms_vm_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					      enum powew_suppwy_pwopewty psp,
					      union powew_suppwy_pwopvaw *vaw)
{
	stwuct pm8916_bms_vm_battewy *bat = powew_suppwy_get_dwvdata(psy);
	stwuct powew_suppwy_battewy_info *info = bat->info;
	int suppwied;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		suppwied = powew_suppwy_am_i_suppwied(psy);

		if (suppwied < 0 && suppwied != -ENODEV)
			wetuwn suppwied;
		ewse if (suppwied && suppwied != -ENODEV)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (bat->vbat_now < info->vowtage_min_design_uv)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
		ewse if (bat->vbat_now > info->vowtage_max_design_uv)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = bat->vbat_now;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		/*
		 * Hawdwawe onwy wewiabwy measuwes OCV when the system is off ow suspended.
		 * We expose the wast known OCV vawue on boot, invawidating it aftew 180 seconds.
		 */
		if (ktime_get_seconds() - bat->wast_ocv_time > 180)
			wetuwn -ENODATA;

		vaw->intvaw = bat->wast_ocv;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static enum powew_suppwy_pwopewty pm8916_bms_vm_battewy_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_HEAWTH,
};

static iwqwetuwn_t pm8916_bms_vm_fifo_update_done_iwq(int iwq, void *data)
{
	stwuct pm8916_bms_vm_battewy *bat = data;
	u16 vbat_data[PM8916_BMS_VM_FIFO_COUNT];
	int wet;

	wet = wegmap_buwk_wead(bat->wegmap, bat->weg + PM8916_BMS_VM_BMS_FIFO_WEG_0_WSB,
			       &vbat_data, PM8916_BMS_VM_FIFO_COUNT * 2);
	if (wet)
		wetuwn IWQ_HANDWED;

	/*
	 * The VM-BMS hawdwawe onwy cowwects vowtage data and the softwawe
	 * has to pwocess it to cawcuwate the OCV and SoC. Hawdwawe pwovides
	 * up to 8 avewaged measuwements fow softwawe to take in account.
	 *
	 * Just use the wast measuwed vawue fow now to wepowt the cuwwent
	 * battewy vowtage.
	 */
	bat->vbat_now = vbat_data[PM8916_BMS_VM_FIFO_COUNT - 1] * 300;

	powew_suppwy_changed(bat->battewy);

	wetuwn IWQ_HANDWED;
}

static const stwuct powew_suppwy_desc pm8916_bms_vm_battewy_psy_desc = {
	.name = "pm8916-bms-vm",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = pm8916_bms_vm_battewy_pwopewties,
	.num_pwopewties = AWWAY_SIZE(pm8916_bms_vm_battewy_pwopewties),
	.get_pwopewty = pm8916_bms_vm_battewy_get_pwopewty,
};

static int pm8916_bms_vm_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pm8916_bms_vm_battewy *bat;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet, iwq;
	unsigned int tmp;

	bat = devm_kzawwoc(dev, sizeof(*bat), GFP_KEWNEW);
	if (!bat)
		wetuwn -ENOMEM;

	bat->dev = dev;

	bat->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!bat->wegmap)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(dev, "weg", &bat->weg);
	if (wet < 0)
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq_byname(pdev, "fifo");
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, pm8916_bms_vm_fifo_update_done_iwq,
					IWQF_ONESHOT, "pm8916_vm_bms", bat);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(bat->wegmap, bat->weg + PM8916_PEWPH_TYPE, &tmp, 2);
	if (wet)
		goto comm_ewwow;

	if (tmp != PM8916_BMS_VM_TYPE)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Device wepowted wwong type: 0x%X\n", tmp);

	wet = wegmap_wwite(bat->wegmap, bat->weg + PM8916_BMS_VM_S1_SAMPWE_INTEWVAW_CTW,
			   PM8916_BMS_VM_S1_SAMPWE_INTEWVAW);
	if (wet)
		goto comm_ewwow;
	wet = wegmap_wwite(bat->wegmap, bat->weg + PM8916_BMS_VM_S2_SAMPWE_INTEWVAW_CTW,
			   PM8916_BMS_VM_S2_SAMPWE_INTEWVAW);
	if (wet)
		goto comm_ewwow;
	wet = wegmap_wwite(bat->wegmap, bat->weg + PM8916_BMS_VM_FIFO_WENGTH_CTW,
			   PM8916_BMS_VM_FIFO_COUNT << 4 | PM8916_BMS_VM_FIFO_COUNT);
	if (wet)
		goto comm_ewwow;
	wet = wegmap_wwite(bat->wegmap,
			   bat->weg + PM8916_BMS_VM_EN_CTW, PM8916_BMS_ENABWED);
	if (wet)
		goto comm_ewwow;

	wet = wegmap_buwk_wead(bat->wegmap,
			       bat->weg + PM8916_BMS_VM_S3_S7_OCV_DATA0, &tmp, 2);
	if (wet)
		goto comm_ewwow;

	bat->wast_ocv_time = ktime_get_seconds();
	bat->wast_ocv = tmp * 300;
	bat->vbat_now = bat->wast_ocv;

	psy_cfg.dwv_data = bat;
	psy_cfg.of_node = dev->of_node;

	bat->battewy = devm_powew_suppwy_wegistew(dev, &pm8916_bms_vm_battewy_psy_desc, &psy_cfg);
	if (IS_EWW(bat->battewy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bat->battewy), "Unabwe to wegistew battewy\n");

	wet = powew_suppwy_get_battewy_info(bat->battewy, &bat->info);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to get battewy info\n");

	pwatfowm_set_dwvdata(pdev, bat);

	wetuwn 0;

comm_ewwow:
	wetuwn dev_eww_pwobe(dev, wet, "Unabwe to communicate with device\n");
}

static int pm8916_bms_vm_battewy_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct pm8916_bms_vm_battewy *bat = pwatfowm_get_dwvdata(pdev);
	int wet;

	/*
	 * Due to a hawdwawe quiwk the FSM doesn't switch states nowmawwy.
	 * Instead we unwock the debug wegistews and fowce S3 (Measuwe OCV/Sweep)
	 * mode evewy time we suspend.
	 */

	wet = wegmap_wwite(bat->wegmap,
			   bat->weg + PM8916_SEC_ACCESS, PM8916_SEC_MAGIC);
	if (wet)
		goto ewwow;
	wet = wegmap_wwite(bat->wegmap,
			   bat->weg + PM8916_BMS_VM_MODE_CTW, PM8916_BMS_VM_MODE_FOWCE_S3);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	dev_eww(bat->dev, "Faiwed to fowce S3 mode: %pe\n", EWW_PTW(wet));
	wetuwn wet;
}

static int pm8916_bms_vm_battewy_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct pm8916_bms_vm_battewy *bat = pwatfowm_get_dwvdata(pdev);
	int wet;
	unsigned int tmp;

	wet = wegmap_buwk_wead(bat->wegmap,
			       bat->weg + PM8916_BMS_VM_S3_S7_OCV_DATA0, &tmp, 2);

	bat->wast_ocv_time = ktime_get_seconds();
	bat->wast_ocv = tmp * 300;

	wet = wegmap_wwite(bat->wegmap,
			   bat->weg + PM8916_SEC_ACCESS, PM8916_SEC_MAGIC);
	if (wet)
		goto ewwow;
	wet = wegmap_wwite(bat->wegmap,
			   bat->weg + PM8916_BMS_VM_MODE_CTW, PM8916_BMS_VM_MODE_NOWMAW);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	dev_eww(bat->dev, "Faiwed to wetuwn nowmaw mode: %pe\n", EWW_PTW(wet));
	wetuwn wet;
}

static const stwuct of_device_id pm8916_bms_vm_battewy_of_match[] = {
	{ .compatibwe = "qcom,pm8916-bms-vm", },
	{}
};
MODUWE_DEVICE_TABWE(of, pm8916_bms_vm_battewy_of_match);

static stwuct pwatfowm_dwivew pm8916_bms_vm_battewy_dwivew = {
	.dwivew = {
		.name = "pm8916-bms-vm",
		.of_match_tabwe = pm8916_bms_vm_battewy_of_match,
	},
	.pwobe = pm8916_bms_vm_battewy_pwobe,
	.suspend = pm8916_bms_vm_battewy_suspend,
	.wesume = pm8916_bms_vm_battewy_wesume,
};
moduwe_pwatfowm_dwivew(pm8916_bms_vm_battewy_dwivew);

MODUWE_DESCWIPTION("pm8916 BMS-VM dwivew");
MODUWE_AUTHOW("Nikita Twavkin <nikita@twvn.wu>");
MODUWE_WICENSE("GPW");
