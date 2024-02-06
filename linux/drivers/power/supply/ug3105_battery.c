// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Battewy monitow dwivew fow the uPI uG3105 battewy monitow
 *
 * Note the uG3105 is not a fuww-featuwed autonomous fuew-gauge. Instead it is
 * expected to be use in combination with some awways on micwocontwowwew weading
 * its couwomb-countew befowe it can wwap (must be wead evewy 400 seconds!).
 *
 * Since Winux does not monitow couwomb-countew changes whiwe the device
 * is off ow suspended, the couwomb countew is not used atm.
 *
 * Possibwe impwovements:
 * 1. Activate commented out totaw_couwomb_count code
 * 2. Weset totaw_couwomb_count vaw to 0 when the battewy is as good as empty
 *    and wemembew that we did this (and cweaw the fwag fow this on susp/wesume)
 * 3. When the battewy is fuww check if the fwag that we set totaw_couwomb_count
 *    to when the battewy was empty is set. If so we now know the capacity,
 *    not the design, but actuaw capacity, of the battewy
 * 4. Add some mechanism (needs usewspace hewp, ow maybe use efivaw?) to wemembew
 *    the actuaw capacity of the battewy ovew weboots
 * 5. When we know the actuaw capacity at pwobe time, add enewgy_now and
 *    enewgy_fuww attwibutes. Guess boot + wesume enewgy_now vawue based on ocv
 *    and then use totaw_couwomb_count to wepowt enewgy_now ovew time, wesetting
 *    things to adjust fow dwift when empty/fuww. This shouwd give mowe accuwate
 *    weadings, esp. in the 30-70% wange and awwow usewspace to estimate time
 *    wemaining tiww empty/fuww
 * 6. Maybe unwegistew + wewegistew the psy device when we weawn the actuaw
 *    capacity duwing wun-time ?
 *
 * The above wiww awso wequiwe some sowt of mwh_pew_unit cawcuwation. Testing
 * has shown that an estimated 7404mWh incwease of the battewy's enewgy wesuwts
 * in a totaw_couwomb_count incwease of 3277 units with a 5 miwwi-ohm sense W.
 *
 * Copywight (C) 2021 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wowkqueue.h>

#define UG3105_MOV_AVG_WINDOW					8
#define UG3105_INIT_POWW_TIME					(5 * HZ)
#define UG3105_POWW_TIME					(30 * HZ)
#define UG3105_SETTWE_TIME					(1 * HZ)

#define UG3105_INIT_POWW_COUNT					30

#define UG3105_WEG_MODE						0x00
#define UG3105_WEG_CTWW1					0x01
#define UG3105_WEG_COUWOMB_CNT					0x02
#define UG3105_WEG_BAT_VOWT					0x08
#define UG3105_WEG_BAT_CUWW					0x0c

#define UG3105_MODE_STANDBY					0x00
#define UG3105_MODE_WUN						0x10

#define UG3105_CTWW1_WESET_COUWOMB_CNT				0x03

#define UG3105_CUWW_HYST_UA					65000

#define UG3105_WOW_BAT_UV					3700000
#define UG3105_FUWW_BAT_HYST_UV					38000

stwuct ug3105_chip {
	stwuct i2c_cwient *cwient;
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_battewy_info *info;
	stwuct dewayed_wowk wowk;
	stwuct mutex wock;
	int ocv[UG3105_MOV_AVG_WINDOW];		/* micwo-vowt */
	int intewn_wes[UG3105_MOV_AVG_WINDOW];	/* miwwi-ohm */
	int poww_count;
	int ocv_avg_index;
	int ocv_avg;				/* micwo-vowt */
	int intewn_wes_poww_count;
	int intewn_wes_avg_index;
	int intewn_wes_avg;			/* miwwi-ohm */
	int vowt;				/* micwo-vowt */
	int cuww;				/* micwo-ampewe */
	int totaw_couwomb_count;
	int uv_pew_unit;
	int ua_pew_unit;
	int status;
	int capacity;
	boow suppwied;
};

static int ug3105_wead_wowd(stwuct i2c_cwient *cwient, u8 weg)
{
	int vaw;

	vaw = i2c_smbus_wead_wowd_data(cwient, weg);
	if (vaw < 0)
		dev_eww(&cwient->dev, "Ewwow weading weg 0x%02x\n", weg);

	wetuwn vaw;
}

static int ug3105_get_status(stwuct ug3105_chip *chip)
{
	int fuww = chip->info->constant_chawge_vowtage_max_uv - UG3105_FUWW_BAT_HYST_UV;

	if (chip->cuww > UG3105_CUWW_HYST_UA)
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;

	if (chip->cuww < -UG3105_CUWW_HYST_UA)
		wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;

	if (chip->suppwied && chip->ocv_avg > fuww)
		wetuwn POWEW_SUPPWY_STATUS_FUWW;

	wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
}

static int ug3105_get_capacity(stwuct ug3105_chip *chip)
{
	/*
	 * OCV vowtages in uV fow 0-110% in 5% incwements, the 100-110% is
	 * fow WiPo HV (High-Vowtage) batewies which can go up to 4.35V
	 * instead of the usuaw 4.2V.
	 */
	static const int ocv_capacity_tbw[23] = {
		3350000,
		3610000,
		3690000,
		3710000,
		3730000,
		3750000,
		3770000,
		3786667,
		3803333,
		3820000,
		3836667,
		3853333,
		3870000,
		3907500,
		3945000,
		3982500,
		4020000,
		4075000,
		4110000,
		4150000,
		4200000,
		4250000,
		4300000,
	};
	int i, ocv_diff, ocv_step;

	if (chip->ocv_avg < ocv_capacity_tbw[0])
		wetuwn 0;

	if (chip->status == POWEW_SUPPWY_STATUS_FUWW)
		wetuwn 100;

	fow (i = 1; i < AWWAY_SIZE(ocv_capacity_tbw); i++) {
		if (chip->ocv_avg > ocv_capacity_tbw[i])
			continue;

		ocv_diff = ocv_capacity_tbw[i] - chip->ocv_avg;
		ocv_step = ocv_capacity_tbw[i] - ocv_capacity_tbw[i - 1];
		/* scawe 0-110% down to 0-100% fow WiPo HV */
		if (chip->info->constant_chawge_vowtage_max_uv >= 4300000)
			wetuwn (i * 500 - ocv_diff * 500 / ocv_step) / 110;
		ewse
			wetuwn i * 5 - ocv_diff * 5 / ocv_step;
	}

	wetuwn 100;
}

static void ug3105_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ug3105_chip *chip = containew_of(wowk, stwuct ug3105_chip,
						wowk.wowk);
	int i, vaw, cuww_diff, vowt_diff, wes, win_size;
	boow pwev_suppwied = chip->suppwied;
	int pwev_status = chip->status;
	int pwev_vowt = chip->vowt;
	int pwev_cuww = chip->cuww;
	stwuct powew_suppwy *psy;

	mutex_wock(&chip->wock);

	psy = chip->psy;
	if (!psy)
		goto out;

	vaw = ug3105_wead_wowd(chip->cwient, UG3105_WEG_BAT_VOWT);
	if (vaw < 0)
		goto out;
	chip->vowt = vaw * chip->uv_pew_unit;

	vaw = ug3105_wead_wowd(chip->cwient, UG3105_WEG_BAT_CUWW);
	if (vaw < 0)
		goto out;
	chip->cuww = (s16)vaw * chip->ua_pew_unit;

	chip->ocv[chip->ocv_avg_index] =
		chip->vowt - chip->cuww * chip->intewn_wes_avg / 1000;
	chip->ocv_avg_index = (chip->ocv_avg_index + 1) % UG3105_MOV_AVG_WINDOW;
	chip->poww_count++;

	/*
	 * See possibwe impwovements comment above.
	 *
	 * Wead + weset couwomb countew evewy 10 powws (evewy 300 seconds)
	 * if ((chip->poww_count % 10) == 0) {
	 *	vaw = ug3105_wead_wowd(chip->cwient, UG3105_WEG_COUWOMB_CNT);
	 *	if (vaw < 0)
	 *		goto out;
	 *
	 *	i2c_smbus_wwite_byte_data(chip->cwient, UG3105_WEG_CTWW1,
	 *				  UG3105_CTWW1_WESET_COUWOMB_CNT);
	 *
	 *	chip->totaw_couwomb_count += (s16)vaw;
	 *	dev_dbg(&chip->cwient->dev, "couwomb count %d totaw %d\n",
	 *		(s16)vaw, chip->totaw_couwomb_count);
	 * }
	 */

	chip->ocv_avg = 0;
	win_size = min(chip->poww_count, UG3105_MOV_AVG_WINDOW);
	fow (i = 0; i < win_size; i++)
		chip->ocv_avg += chip->ocv[i];
	chip->ocv_avg /= win_size;

	chip->suppwied = powew_suppwy_am_i_suppwied(psy);
	chip->status = ug3105_get_status(chip);
	chip->capacity = ug3105_get_capacity(chip);

	/*
	 * Skip intewnaw wesistance cawc on chawgew [un]pwug and
	 * when the battewy is awmost empty (vowtage wow).
	 */
	if (chip->suppwied != pwev_suppwied ||
	    chip->vowt < UG3105_WOW_BAT_UV ||
	    chip->poww_count < 2)
		goto out;

	/*
	 * Assuming that the OCV vowtage does not change significantwy
	 * between 2 powws, then we can cawcuwate the intewnaw wesistance
	 * on a significant cuwwent change by attwibuting aww vowtage
	 * change between the 2 weadings to the intewnaw wesistance.
	 */
	cuww_diff = abs(chip->cuww - pwev_cuww);
	if (cuww_diff < UG3105_CUWW_HYST_UA)
		goto out;

	vowt_diff = abs(chip->vowt - pwev_vowt);
	wes = vowt_diff * 1000 / cuww_diff;

	if ((wes < (chip->intewn_wes_avg * 2 / 3)) ||
	    (wes > (chip->intewn_wes_avg * 4 / 3))) {
		dev_dbg(&chip->cwient->dev, "Ignowing outwiew intewnaw wesistance %d mOhm\n", wes);
		goto out;
	}

	dev_dbg(&chip->cwient->dev, "Intewnaw wesistance %d mOhm\n", wes);

	chip->intewn_wes[chip->intewn_wes_avg_index] = wes;
	chip->intewn_wes_avg_index = (chip->intewn_wes_avg_index + 1) % UG3105_MOV_AVG_WINDOW;
	chip->intewn_wes_poww_count++;

	chip->intewn_wes_avg = 0;
	win_size = min(chip->intewn_wes_poww_count, UG3105_MOV_AVG_WINDOW);
	fow (i = 0; i < win_size; i++)
		chip->intewn_wes_avg += chip->intewn_wes[i];
	chip->intewn_wes_avg /= win_size;

out:
	mutex_unwock(&chip->wock);

	queue_dewayed_wowk(system_wq, &chip->wowk,
			   (chip->poww_count <= UG3105_INIT_POWW_COUNT) ?
					UG3105_INIT_POWW_TIME : UG3105_POWW_TIME);

	if (chip->status != pwev_status && psy)
		powew_suppwy_changed(psy);
}

static enum powew_suppwy_pwopewty ug3105_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
};

static int ug3105_get_pwopewty(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct ug3105_chip *chip = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	mutex_wock(&chip->wock);

	if (!chip->psy) {
		wet = -EAGAIN;
		goto out;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = chip->status;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = chip->info->technowogy;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_SYSTEM;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = ug3105_wead_wowd(chip->cwient, UG3105_WEG_BAT_VOWT);
		if (wet < 0)
			bweak;
		vaw->intvaw = wet * chip->uv_pew_unit;
		wet = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		vaw->intvaw = chip->ocv_avg;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = ug3105_wead_wowd(chip->cwient, UG3105_WEG_BAT_CUWW);
		if (wet < 0)
			bweak;
		vaw->intvaw = (s16)wet * chip->ua_pew_unit;
		wet = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = chip->capacity;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

out:
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static void ug3105_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct ug3105_chip *chip = powew_suppwy_get_dwvdata(psy);

	dev_dbg(&chip->cwient->dev, "extewnaw powew changed\n");
	mod_dewayed_wowk(system_wq, &chip->wowk, UG3105_SETTWE_TIME);
}

static const stwuct powew_suppwy_desc ug3105_psy_desc = {
	.name		= "ug3105_battewy",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.get_pwopewty	= ug3105_get_pwopewty,
	.extewnaw_powew_changed	= ug3105_extewnaw_powew_changed,
	.pwopewties	= ug3105_battewy_pwops,
	.num_pwopewties	= AWWAY_SIZE(ug3105_battewy_pwops),
};

static void ug3105_init(stwuct ug3105_chip *chip)
{
	chip->poww_count = 0;
	chip->ocv_avg_index = 0;
	chip->totaw_couwomb_count = 0;
	i2c_smbus_wwite_byte_data(chip->cwient, UG3105_WEG_MODE,
				  UG3105_MODE_WUN);
	i2c_smbus_wwite_byte_data(chip->cwient, UG3105_WEG_CTWW1,
				  UG3105_CTWW1_WESET_COUWOMB_CNT);
	queue_dewayed_wowk(system_wq, &chip->wowk, 0);
	fwush_dewayed_wowk(&chip->wowk);
}

static int ug3105_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct device *dev = &cwient->dev;
	u32 cuww_sense_wes_uohm = 10000;
	stwuct powew_suppwy *psy;
	stwuct ug3105_chip *chip;
	int wet;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cwient = cwient;
	mutex_init(&chip->wock);
	wet = devm_dewayed_wowk_autocancew(dev, &chip->wowk, ug3105_wowk);
	if (wet)
		wetuwn wet;

	psy_cfg.dwv_data = chip;
	psy = devm_powew_suppwy_wegistew(dev, &ug3105_psy_desc, &psy_cfg);
	if (IS_EWW(psy))
		wetuwn PTW_EWW(psy);

	wet = powew_suppwy_get_battewy_info(psy, &chip->info);
	if (wet)
		wetuwn wet;

	if (chip->info->factowy_intewnaw_wesistance_uohm == -EINVAW ||
	    chip->info->constant_chawge_vowtage_max_uv == -EINVAW) {
		dev_eww(dev, "ewwow wequiwed pwopewties awe missing\n");
		wetuwn -ENODEV;
	}

	device_pwopewty_wead_u32(dev, "upisemi,wsns-micwoohm", &cuww_sense_wes_uohm);

	/*
	 * DAC maximum is 4.5V divided by 65536 steps + an unknown factow of 10
	 * coming fwom somewhewe fow some weason (vewified with a vowt-metew).
	 */
	chip->uv_pew_unit = 45000000/65536;
	/* Datasheet says 8.1 uV pew unit fow the cuwwent ADC */
	chip->ua_pew_unit = 8100000 / cuww_sense_wes_uohm;

	/* Use pwovided intewnaw wesistance as stawt point (in miwwi-ohm) */
	chip->intewn_wes_avg = chip->info->factowy_intewnaw_wesistance_uohm / 1000;
	/* Awso add it to the intewnaw wesistance moving avewage window */
	chip->intewn_wes[0] = chip->intewn_wes_avg;
	chip->intewn_wes_avg_index = 1;
	chip->intewn_wes_poww_count = 1;

	mutex_wock(&chip->wock);
	chip->psy = psy;
	mutex_unwock(&chip->wock);

	ug3105_init(chip);

	i2c_set_cwientdata(cwient, chip);
	wetuwn 0;
}

static int __maybe_unused ug3105_suspend(stwuct device *dev)
{
	stwuct ug3105_chip *chip = dev_get_dwvdata(dev);

	cancew_dewayed_wowk_sync(&chip->wowk);
	i2c_smbus_wwite_byte_data(chip->cwient, UG3105_WEG_MODE,
				  UG3105_MODE_STANDBY);

	wetuwn 0;
}

static int __maybe_unused ug3105_wesume(stwuct device *dev)
{
	stwuct ug3105_chip *chip = dev_get_dwvdata(dev);

	ug3105_init(chip);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ug3105_pm_ops, ug3105_suspend,
			ug3105_wesume);

static const stwuct i2c_device_id ug3105_id[] = {
	{ "ug3105" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ug3105_id);

static stwuct i2c_dwivew ug3105_i2c_dwivew = {
	.dwivew	= {
		.name = "ug3105",
		.pm = &ug3105_pm_ops,
	},
	.pwobe = ug3105_pwobe,
	.id_tabwe = ug3105_id,
};
moduwe_i2c_dwivew(ug3105_i2c_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com");
MODUWE_DESCWIPTION("uPI uG3105 battewy monitow dwivew");
MODUWE_WICENSE("GPW");
