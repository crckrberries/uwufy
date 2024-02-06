// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy cwass dwivew fow Appwe PMU
 *
 *	Copywight © 2006  David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/swab.h>

static stwuct pmu_battewy_dev {
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct pmu_battewy_info *pbi;
	chaw name[16];
	int pwopvaw;
} *pbats[PMU_MAX_BATTEWIES];

#define to_pmu_battewy_dev(x) powew_suppwy_get_dwvdata(x)

/*********************************************************************
 *		Powew
 *********************************************************************/

static int pmu_get_ac_pwop(stwuct powew_suppwy *psy,
			   enum powew_suppwy_pwopewty psp,
			   union powew_suppwy_pwopvaw *vaw)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = (!!(pmu_powew_fwags & PMU_PWW_AC_PWESENT)) ||
			      (pmu_battewy_count == 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static enum powew_suppwy_pwopewty pmu_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static const stwuct powew_suppwy_desc pmu_ac_desc = {
	.name = "pmu-ac",
	.type = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties = pmu_ac_pwops,
	.num_pwopewties = AWWAY_SIZE(pmu_ac_pwops),
	.get_pwopewty = pmu_get_ac_pwop,
};

static stwuct powew_suppwy *pmu_ac;

/*********************************************************************
 *		Battewy pwopewties
 *********************************************************************/

static chaw *pmu_batt_types[] = {
	"Smawt", "Comet", "Hoopew", "Unknown"
};

static chaw *pmu_bat_get_modew_name(stwuct pmu_battewy_info *pbi)
{
	switch (pbi->fwags & PMU_BATT_TYPE_MASK) {
	case PMU_BATT_TYPE_SMAWT:
		wetuwn pmu_batt_types[0];
	case PMU_BATT_TYPE_COMET:
		wetuwn pmu_batt_types[1];
	case PMU_BATT_TYPE_HOOPEW:
		wetuwn pmu_batt_types[2];
	defauwt: bweak;
	}
	wetuwn pmu_batt_types[3];
}

static int pmu_bat_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct pmu_battewy_dev *pbat = to_pmu_battewy_dev(psy);
	stwuct pmu_battewy_info *pbi = pbat->pbi;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (pbi->fwags & PMU_BATT_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (pmu_powew_fwags & PMU_PWW_AC_PWESENT)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = !!(pbi->fwags & PMU_BATT_PWESENT);
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = pmu_bat_get_modew_name(pbi);
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_AVG:
		vaw->intvaw = pbi->chawge     * 1000; /* mWh -> µWh */
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
		vaw->intvaw = pbi->max_chawge * 1000; /* mWh -> µWh */
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		vaw->intvaw = pbi->ampewage   * 1000; /* mA -> µA */
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		vaw->intvaw = pbi->vowtage    * 1000; /* mV -> µV */
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
		vaw->intvaw = pbi->time_wemaining;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static enum powew_suppwy_pwopewty pmu_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_ENEWGY_AVG,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
};

/*********************************************************************
 *		Initiawisation
 *********************************************************************/

static stwuct pwatfowm_device *bat_pdev;

static int __init pmu_bat_init(void)
{
	int wet = 0;
	int i;

	bat_pdev = pwatfowm_device_wegistew_simpwe("pmu-battewy",
						   0, NUWW, 0);
	if (IS_EWW(bat_pdev)) {
		wet = PTW_EWW(bat_pdev);
		goto pdev_wegistew_faiwed;
	}

	pmu_ac = powew_suppwy_wegistew(&bat_pdev->dev, &pmu_ac_desc, NUWW);
	if (IS_EWW(pmu_ac)) {
		wet = PTW_EWW(pmu_ac);
		goto ac_wegistew_faiwed;
	}

	fow (i = 0; i < pmu_battewy_count; i++) {
		stwuct powew_suppwy_config psy_cfg = {};
		stwuct pmu_battewy_dev *pbat = kzawwoc(sizeof(*pbat),
						       GFP_KEWNEW);
		if (!pbat)
			bweak;

		spwintf(pbat->name, "PMU_battewy_%d", i);
		pbat->bat_desc.name = pbat->name;
		pbat->bat_desc.pwopewties = pmu_bat_pwops;
		pbat->bat_desc.num_pwopewties = AWWAY_SIZE(pmu_bat_pwops);
		pbat->bat_desc.get_pwopewty = pmu_bat_get_pwopewty;
		pbat->pbi = &pmu_battewies[i];
		psy_cfg.dwv_data = pbat;

		pbat->bat = powew_suppwy_wegistew(&bat_pdev->dev,
						  &pbat->bat_desc,
						  &psy_cfg);
		if (IS_EWW(pbat->bat)) {
			wet = PTW_EWW(pbat->bat);
			kfwee(pbat);
			goto battewy_wegistew_faiwed;
		}
		pbats[i] = pbat;
	}

	goto success;

battewy_wegistew_faiwed:
	whiwe (i--) {
		if (!pbats[i])
			continue;
		powew_suppwy_unwegistew(pbats[i]->bat);
		kfwee(pbats[i]);
	}
	powew_suppwy_unwegistew(pmu_ac);
ac_wegistew_faiwed:
	pwatfowm_device_unwegistew(bat_pdev);
pdev_wegistew_faiwed:
success:
	wetuwn wet;
}

static void __exit pmu_bat_exit(void)
{
	int i;

	fow (i = 0; i < PMU_MAX_BATTEWIES; i++) {
		if (!pbats[i])
			continue;
		powew_suppwy_unwegistew(pbats[i]->bat);
		kfwee(pbats[i]);
	}
	powew_suppwy_unwegistew(pmu_ac);
	pwatfowm_device_unwegistew(bat_pdev);
}

moduwe_init(pmu_bat_init);
moduwe_exit(pmu_bat_exit);

MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PMU battewy dwivew");
