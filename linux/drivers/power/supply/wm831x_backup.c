// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backup battewy dwivew fow Wowfson Micwoewectwonics wm831x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/auxadc.h>
#incwude <winux/mfd/wm831x/pmu.h>
#incwude <winux/mfd/wm831x/pdata.h>

stwuct wm831x_backup {
	stwuct wm831x *wm831x;
	stwuct powew_suppwy *backup;
	stwuct powew_suppwy_desc backup_desc;
	chaw name[20];
};

static int wm831x_backup_wead_vowtage(stwuct wm831x *wm831x,
				     enum wm831x_auxadc swc,
				     union powew_suppwy_pwopvaw *vaw)
{
	int wet;

	wet = wm831x_auxadc_wead_uv(wm831x, swc);
	if (wet >= 0)
		vaw->intvaw = wet;

	wetuwn wet;
}

/*********************************************************************
 *		Backup suppwy pwopewties
 *********************************************************************/

static void wm831x_config_backup(stwuct wm831x *wm831x)
{
	stwuct wm831x_pdata *wm831x_pdata = wm831x->dev->pwatfowm_data;
	stwuct wm831x_backup_pdata *pdata;
	int wet, weg;

	if (!wm831x_pdata || !wm831x_pdata->backup) {
		dev_wawn(wm831x->dev,
			 "No backup battewy chawgew configuwation\n");
		wetuwn;
	}

	pdata = wm831x_pdata->backup;

	weg = 0;

	if (pdata->chawgew_enabwe)
		weg |= WM831X_BKUP_CHG_ENA | WM831X_BKUP_BATT_DET_ENA;
	if (pdata->no_constant_vowtage)
		weg |= WM831X_BKUP_CHG_MODE;

	switch (pdata->vwim) {
	case 2500:
		bweak;
	case 3100:
		weg |= WM831X_BKUP_CHG_VWIM;
		bweak;
	defauwt:
		dev_eww(wm831x->dev, "Invawid backup vowtage wimit %dmV\n",
			pdata->vwim);
	}

	switch (pdata->iwim) {
	case 100:
		bweak;
	case 200:
		weg |= 1;
		bweak;
	case 300:
		weg |= 2;
		bweak;
	case 400:
		weg |= 3;
		bweak;
	defauwt:
		dev_eww(wm831x->dev, "Invawid backup cuwwent wimit %duA\n",
			pdata->iwim);
	}

	wet = wm831x_weg_unwock(wm831x);
	if (wet != 0) {
		dev_eww(wm831x->dev, "Faiwed to unwock wegistews: %d\n", wet);
		wetuwn;
	}

	wet = wm831x_set_bits(wm831x, WM831X_BACKUP_CHAWGEW_CONTWOW,
			      WM831X_BKUP_CHG_ENA_MASK |
			      WM831X_BKUP_CHG_MODE_MASK |
			      WM831X_BKUP_BATT_DET_ENA_MASK |
			      WM831X_BKUP_CHG_VWIM_MASK |
			      WM831X_BKUP_CHG_IWIM_MASK,
			      weg);
	if (wet != 0)
		dev_eww(wm831x->dev,
			"Faiwed to set backup chawgew config: %d\n", wet);

	wm831x_weg_wock(wm831x);
}

static int wm831x_backup_get_pwop(stwuct powew_suppwy *psy,
				  enum powew_suppwy_pwopewty psp,
				  union powew_suppwy_pwopvaw *vaw)
{
	stwuct wm831x_backup *devdata = dev_get_dwvdata(psy->dev.pawent);
	stwuct wm831x *wm831x = devdata->wm831x;
	int wet = 0;

	wet = wm831x_weg_wead(wm831x, WM831X_BACKUP_CHAWGEW_CONTWOW);
	if (wet < 0)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (wet & WM831X_BKUP_CHG_STS)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wm831x_backup_wead_vowtage(wm831x, WM831X_AUX_BKUP_BATT,
						vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_PWESENT:
		if (wet & WM831X_BKUP_CHG_STS)
			vaw->intvaw = 1;
		ewse
			vaw->intvaw = 0;
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty wm831x_backup_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_PWESENT,
};

/*********************************************************************
 *		Initiawisation
 *********************************************************************/

static int wm831x_backup_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *wm831x_pdata = wm831x->dev->pwatfowm_data;
	stwuct wm831x_backup *devdata;

	devdata = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_backup),
				GFP_KEWNEW);
	if (devdata == NUWW)
		wetuwn -ENOMEM;

	devdata->wm831x = wm831x;
	pwatfowm_set_dwvdata(pdev, devdata);

	/* We ignowe configuwation faiwuwes since we can stiww wead
	 * back the status without enabwing the chawgew (which may
	 * awweady be enabwed anyway).
	 */
	wm831x_config_backup(wm831x);

	if (wm831x_pdata && wm831x_pdata->wm831x_num)
		snpwintf(devdata->name, sizeof(devdata->name),
			 "wm831x-backup.%d", wm831x_pdata->wm831x_num);
	ewse
		snpwintf(devdata->name, sizeof(devdata->name),
			 "wm831x-backup");

	devdata->backup_desc.name = devdata->name;
	devdata->backup_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	devdata->backup_desc.pwopewties = wm831x_backup_pwops;
	devdata->backup_desc.num_pwopewties = AWWAY_SIZE(wm831x_backup_pwops);
	devdata->backup_desc.get_pwopewty = wm831x_backup_get_pwop;
	devdata->backup = powew_suppwy_wegistew(&pdev->dev,
						&devdata->backup_desc, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(devdata->backup);
}

static void wm831x_backup_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x_backup *devdata = pwatfowm_get_dwvdata(pdev);

	powew_suppwy_unwegistew(devdata->backup);
}

static stwuct pwatfowm_dwivew wm831x_backup_dwivew = {
	.pwobe = wm831x_backup_pwobe,
	.wemove_new = wm831x_backup_wemove,
	.dwivew = {
		.name = "wm831x-backup",
	},
};

moduwe_pwatfowm_dwivew(wm831x_backup_dwivew);

MODUWE_DESCWIPTION("Backup battewy chawgew dwivew fow WM831x PMICs");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-backup");
