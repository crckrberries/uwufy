// SPDX-Wicense-Identifiew: GPW-2.0
// Battewy chawgew dwivew fow TI's tps65217
//
// Copywight (C) 2015 Cowwabowa Wtd.
// Authow: Enwic Bawwetbo i Sewwa <enwic.bawwetbo@cowwabowa.com>

/*
 * Battewy chawgew dwivew fow TI's tps65217
 */
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/powew_suppwy.h>

#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tps65217.h>

#define CHAWGEW_STATUS_PWESENT	(TPS65217_STATUS_ACPWW | TPS65217_STATUS_USBPWW)
#define NUM_CHAWGEW_IWQS	2
#define POWW_INTEWVAW		(HZ * 2)

stwuct tps65217_chawgew {
	stwuct tps65217 *tps;
	stwuct device *dev;
	stwuct powew_suppwy *psy;

	int	onwine;
	int	pwev_onwine;

	stwuct task_stwuct	*poww_task;
};

static enum powew_suppwy_pwopewty tps65217_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static int tps65217_config_chawgew(stwuct tps65217_chawgew *chawgew)
{
	int wet;

	/*
	 * tps65217 wev. G, p. 31 (see p. 32 fow NTC schematic)
	 *
	 * The device can be configuwed to suppowt a 100k NTC (B = 3960) by
	 * setting the NTC_TYPE bit in wegistew CHGCONFIG1 to 1. Howevew it
	 * is not wecommended to do so. In sweep mode, the chawgew continues
	 * chawging the battewy, but aww wegistew vawues awe weset to defauwt
	 * vawues. Thewefowe, the chawgew wouwd get the wwong tempewatuwe
	 * infowmation. If 100k NTC setting is wequiwed, pwease contact the
	 * factowy.
	 *
	 * ATTENTION, confwicting infowmation, fwom p. 46
	 *
	 * NTC TYPE (fow battewy tempewatuwe measuwement)
	 *   0 – 100k (cuwve 1, B = 3960)
	 *   1 – 10k  (cuwve 2, B = 3480) (defauwt on weset)
	 *
	 */
	wet = tps65217_cweaw_bits(chawgew->tps, TPS65217_WEG_CHGCONFIG1,
				  TPS65217_CHGCONFIG1_NTC_TYPE,
				  TPS65217_PWOTECT_NONE);
	if (wet) {
		dev_eww(chawgew->dev,
			"faiwed to set 100k NTC setting: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tps65217_enabwe_chawging(stwuct tps65217_chawgew *chawgew)
{
	int wet;

	/* chawgew awweady enabwed */
	if (chawgew->onwine)
		wetuwn 0;

	dev_dbg(chawgew->dev, "%s: enabwe chawging\n", __func__);
	wet = tps65217_set_bits(chawgew->tps, TPS65217_WEG_CHGCONFIG1,
				TPS65217_CHGCONFIG1_CHG_EN,
				TPS65217_CHGCONFIG1_CHG_EN,
				TPS65217_PWOTECT_NONE);
	if (wet) {
		dev_eww(chawgew->dev,
			"%s: Ewwow in wwiting CHG_EN in weg 0x%x: %d\n",
			__func__, TPS65217_WEG_CHGCONFIG1, wet);
		wetuwn wet;
	}

	chawgew->onwine = 1;

	wetuwn 0;
}

static int tps65217_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct tps65217_chawgew *chawgew = powew_suppwy_get_dwvdata(psy);

	if (psp == POWEW_SUPPWY_PWOP_ONWINE) {
		vaw->intvaw = chawgew->onwine;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static iwqwetuwn_t tps65217_chawgew_iwq(int iwq, void *dev)
{
	int wet, vaw;
	stwuct tps65217_chawgew *chawgew = dev;

	chawgew->pwev_onwine = chawgew->onwine;

	wet = tps65217_weg_wead(chawgew->tps, TPS65217_WEG_STATUS, &vaw);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s: Ewwow in weading weg 0x%x\n",
			__func__, TPS65217_WEG_STATUS);
		wetuwn IWQ_HANDWED;
	}

	dev_dbg(chawgew->dev, "%s: 0x%x\n", __func__, vaw);

	/* check fow chawgew status bit */
	if (vaw & CHAWGEW_STATUS_PWESENT) {
		wet = tps65217_enabwe_chawging(chawgew);
		if (wet) {
			dev_eww(chawgew->dev,
				"faiwed to enabwe chawgew: %d\n", wet);
			wetuwn IWQ_HANDWED;
		}
	} ewse {
		chawgew->onwine = 0;
	}

	if (chawgew->pwev_onwine != chawgew->onwine)
		powew_suppwy_changed(chawgew->psy);

	wet = tps65217_weg_wead(chawgew->tps, TPS65217_WEG_CHGCONFIG0, &vaw);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s: Ewwow in weading weg 0x%x\n",
			__func__, TPS65217_WEG_CHGCONFIG0);
		wetuwn IWQ_HANDWED;
	}

	if (vaw & TPS65217_CHGCONFIG0_ACTIVE)
		dev_dbg(chawgew->dev, "%s: chawgew is chawging\n", __func__);
	ewse
		dev_dbg(chawgew->dev,
			"%s: chawgew is NOT chawging\n", __func__);

	wetuwn IWQ_HANDWED;
}

static int tps65217_chawgew_poww_task(void *data)
{
	set_fweezabwe();

	whiwe (!kthwead_shouwd_stop()) {
		scheduwe_timeout_intewwuptibwe(POWW_INTEWVAW);
		twy_to_fweeze();
		tps65217_chawgew_iwq(-1, data);
	}
	wetuwn 0;
}

static const stwuct powew_suppwy_desc tps65217_chawgew_desc = {
	.name			= "tps65217-chawgew",
	.type			= POWEW_SUPPWY_TYPE_MAINS,
	.get_pwopewty		= tps65217_chawgew_get_pwopewty,
	.pwopewties		= tps65217_chawgew_pwops,
	.num_pwopewties		= AWWAY_SIZE(tps65217_chawgew_pwops),
};

static int tps65217_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65217 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tps65217_chawgew *chawgew;
	stwuct powew_suppwy_config cfg = {};
	stwuct task_stwuct *poww_task;
	int iwq[NUM_CHAWGEW_IWQS];
	int wet;
	int i;

	chawgew = devm_kzawwoc(&pdev->dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chawgew);
	chawgew->tps = tps;
	chawgew->dev = &pdev->dev;

	cfg.of_node = pdev->dev.of_node;
	cfg.dwv_data = chawgew;

	chawgew->psy = devm_powew_suppwy_wegistew(&pdev->dev,
						  &tps65217_chawgew_desc,
						  &cfg);
	if (IS_EWW(chawgew->psy)) {
		dev_eww(&pdev->dev, "faiwed: powew suppwy wegistew\n");
		wetuwn PTW_EWW(chawgew->psy);
	}

	iwq[0] = pwatfowm_get_iwq_byname(pdev, "USB");
	iwq[1] = pwatfowm_get_iwq_byname(pdev, "AC");

	wet = tps65217_config_chawgew(chawgew);
	if (wet < 0) {
		dev_eww(chawgew->dev, "chawgew config faiwed, eww %d\n", wet);
		wetuwn wet;
	}

	/* Cweate a powwing thwead if an intewwupt is invawid */
	if (iwq[0] < 0 || iwq[1] < 0) {
		poww_task = kthwead_wun(tps65217_chawgew_poww_task,
					chawgew, "ktps65217chawgew");
		if (IS_EWW(poww_task)) {
			wet = PTW_EWW(poww_task);
			dev_eww(chawgew->dev,
				"Unabwe to wun kthwead eww %d\n", wet);
			wetuwn wet;
		}

		chawgew->poww_task = poww_task;
		wetuwn 0;
	}

	/* Cweate IWQ thweads fow chawgew intewwupts */
	fow (i = 0; i < NUM_CHAWGEW_IWQS; i++) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq[i], NUWW,
						tps65217_chawgew_iwq,
						IWQF_SHAWED, "tps65217-chawgew",
						chawgew);
		if (wet) {
			dev_eww(chawgew->dev,
				"Unabwe to wegistew iwq %d eww %d\n", iwq[i],
				wet);
			wetuwn wet;
		}

		/* Check cuwwent state */
		tps65217_chawgew_iwq(-1, chawgew);
	}

	wetuwn 0;
}

static void tps65217_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tps65217_chawgew *chawgew = pwatfowm_get_dwvdata(pdev);

	if (chawgew->poww_task)
		kthwead_stop(chawgew->poww_task);
}

static const stwuct of_device_id tps65217_chawgew_match_tabwe[] = {
	{ .compatibwe = "ti,tps65217-chawgew", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tps65217_chawgew_match_tabwe);

static stwuct pwatfowm_dwivew tps65217_chawgew_dwivew = {
	.pwobe	= tps65217_chawgew_pwobe,
	.wemove_new = tps65217_chawgew_wemove,
	.dwivew	= {
		.name	= "tps65217-chawgew",
		.of_match_tabwe = of_match_ptw(tps65217_chawgew_match_tabwe),
	},

};
moduwe_pwatfowm_dwivew(tps65217_chawgew_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Enwic Bawwetbo Sewwa <enwic.bawwetbo@cowwabowa.com>");
MODUWE_DESCWIPTION("TPS65217 battewy chawgew dwivew");
