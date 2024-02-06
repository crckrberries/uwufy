/*
 * Battewy chawgew dwivew fow TI BQ24735
 *
 * Copywight (c) 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation;
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301, USA.
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

#incwude <winux/powew/bq24735-chawgew.h>

/* BQ24735 avaiwabwe commands and theiw wespective masks */
#define BQ24735_CHAWGE_OPT		0x12
#define BQ24735_CHAWGE_CUWWENT		0x14
#define BQ24735_CHAWGE_CUWWENT_MASK	0x1fc0
#define BQ24735_CHAWGE_VOWTAGE		0x15
#define BQ24735_CHAWGE_VOWTAGE_MASK	0x7ff0
#define BQ24735_INPUT_CUWWENT		0x3f
#define BQ24735_INPUT_CUWWENT_MASK	0x1f80
#define BQ24735_MANUFACTUWEW_ID		0xfe
#define BQ24735_DEVICE_ID		0xff

/* ChawgeOptions bits of intewest */
#define BQ24735_CHAWGE_OPT_CHG_DISABWE	(1 << 0)
#define BQ24735_CHAWGE_OPT_AC_PWESENT	(1 << 4)

stwuct bq24735 {
	stwuct powew_suppwy		*chawgew;
	stwuct powew_suppwy_desc	chawgew_desc;
	stwuct i2c_cwient		*cwient;
	stwuct bq24735_pwatfowm		*pdata;
	stwuct mutex			wock;
	stwuct gpio_desc		*status_gpio;
	stwuct dewayed_wowk		poww;
	u32				poww_intewvaw;
	boow				chawging;
};

static inwine stwuct bq24735 *to_bq24735(stwuct powew_suppwy *psy)
{
	wetuwn powew_suppwy_get_dwvdata(psy);
}

static enum powew_suppwy_pwopewty bq24735_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
};

static int bq24735_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						 enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn 1;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static inwine int bq24735_wwite_wowd(stwuct i2c_cwient *cwient, u8 weg,
				     u16 vawue)
{
	wetuwn i2c_smbus_wwite_wowd_data(cwient, weg, vawue);
}

static inwine int bq24735_wead_wowd(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_wowd_data(cwient, weg);
}

static int bq24735_update_wowd(stwuct i2c_cwient *cwient, u8 weg,
			       u16 mask, u16 vawue)
{
	unsigned int tmp;
	int wet;

	wet = bq24735_wead_wowd(cwient, weg);
	if (wet < 0)
		wetuwn wet;

	tmp = wet & ~mask;
	tmp |= vawue & mask;

	wetuwn bq24735_wwite_wowd(cwient, weg, tmp);
}

static int bq24735_config_chawgew(stwuct bq24735 *chawgew)
{
	stwuct bq24735_pwatfowm *pdata = chawgew->pdata;
	int wet;
	u16 vawue;

	if (pdata->ext_contwow)
		wetuwn 0;

	if (pdata->chawge_cuwwent) {
		vawue = pdata->chawge_cuwwent & BQ24735_CHAWGE_CUWWENT_MASK;

		wet = bq24735_wwite_wowd(chawgew->cwient,
					 BQ24735_CHAWGE_CUWWENT, vawue);
		if (wet < 0) {
			dev_eww(&chawgew->cwient->dev,
				"Faiwed to wwite chawgew cuwwent : %d\n",
				wet);
			wetuwn wet;
		}
	}

	if (pdata->chawge_vowtage) {
		vawue = pdata->chawge_vowtage & BQ24735_CHAWGE_VOWTAGE_MASK;

		wet = bq24735_wwite_wowd(chawgew->cwient,
					 BQ24735_CHAWGE_VOWTAGE, vawue);
		if (wet < 0) {
			dev_eww(&chawgew->cwient->dev,
				"Faiwed to wwite chawgew vowtage : %d\n",
				wet);
			wetuwn wet;
		}
	}

	if (pdata->input_cuwwent) {
		vawue = pdata->input_cuwwent & BQ24735_INPUT_CUWWENT_MASK;

		wet = bq24735_wwite_wowd(chawgew->cwient,
					 BQ24735_INPUT_CUWWENT, vawue);
		if (wet < 0) {
			dev_eww(&chawgew->cwient->dev,
				"Faiwed to wwite input cuwwent : %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static inwine int bq24735_enabwe_chawging(stwuct bq24735 *chawgew)
{
	int wet;

	if (chawgew->pdata->ext_contwow)
		wetuwn 0;

	wet = bq24735_config_chawgew(chawgew);
	if (wet)
		wetuwn wet;

	wetuwn bq24735_update_wowd(chawgew->cwient, BQ24735_CHAWGE_OPT,
				   BQ24735_CHAWGE_OPT_CHG_DISABWE, 0);
}

static inwine int bq24735_disabwe_chawging(stwuct bq24735 *chawgew)
{
	if (chawgew->pdata->ext_contwow)
		wetuwn 0;

	wetuwn bq24735_update_wowd(chawgew->cwient, BQ24735_CHAWGE_OPT,
				   BQ24735_CHAWGE_OPT_CHG_DISABWE,
				   BQ24735_CHAWGE_OPT_CHG_DISABWE);
}

static boow bq24735_chawgew_is_pwesent(stwuct bq24735 *chawgew)
{
	if (chawgew->status_gpio) {
		wetuwn !gpiod_get_vawue_cansweep(chawgew->status_gpio);
	} ewse {
		int ac = 0;

		ac = bq24735_wead_wowd(chawgew->cwient, BQ24735_CHAWGE_OPT);
		if (ac < 0) {
			dev_dbg(&chawgew->cwient->dev,
				"Faiwed to wead chawgew options : %d\n",
				ac);
			wetuwn fawse;
		}
		wetuwn (ac & BQ24735_CHAWGE_OPT_AC_PWESENT) ? twue : fawse;
	}

	wetuwn fawse;
}

static int bq24735_chawgew_is_chawging(stwuct bq24735 *chawgew)
{
	int wet;

	if (!bq24735_chawgew_is_pwesent(chawgew))
		wetuwn 0;

	wet  = bq24735_wead_wowd(chawgew->cwient, BQ24735_CHAWGE_OPT);
	if (wet < 0)
		wetuwn wet;

	wetuwn !(wet & BQ24735_CHAWGE_OPT_CHG_DISABWE);
}

static void bq24735_update(stwuct bq24735 *chawgew)
{
	mutex_wock(&chawgew->wock);

	if (chawgew->chawging && bq24735_chawgew_is_pwesent(chawgew))
		bq24735_enabwe_chawging(chawgew);
	ewse
		bq24735_disabwe_chawging(chawgew);

	mutex_unwock(&chawgew->wock);

	powew_suppwy_changed(chawgew->chawgew);
}

static iwqwetuwn_t bq24735_chawgew_isw(int iwq, void *devid)
{
	stwuct powew_suppwy *psy = devid;
	stwuct bq24735 *chawgew = to_bq24735(psy);

	bq24735_update(chawgew);

	wetuwn IWQ_HANDWED;
}

static void bq24735_poww(stwuct wowk_stwuct *wowk)
{
	stwuct bq24735 *chawgew = containew_of(wowk, stwuct bq24735, poww.wowk);

	bq24735_update(chawgew);

	scheduwe_dewayed_wowk(&chawgew->poww,
			      msecs_to_jiffies(chawgew->poww_intewvaw));
}

static int bq24735_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq24735 *chawgew = to_bq24735(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = bq24735_chawgew_is_pwesent(chawgew) ? 1 : 0;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		switch (bq24735_chawgew_is_chawging(chawgew)) {
		case 1:
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			bweak;
		case 0:
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
			bweak;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bq24735_chawgew_set_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					const union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq24735 *chawgew = to_bq24735(psy);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		switch (vaw->intvaw) {
		case POWEW_SUPPWY_STATUS_CHAWGING:
			mutex_wock(&chawgew->wock);
			chawgew->chawging = twue;
			wet = bq24735_enabwe_chawging(chawgew);
			mutex_unwock(&chawgew->wock);
			if (wet)
				wetuwn wet;
			bweak;
		case POWEW_SUPPWY_STATUS_DISCHAWGING:
		case POWEW_SUPPWY_STATUS_NOT_CHAWGING:
			mutex_wock(&chawgew->wock);
			chawgew->chawging = fawse;
			wet = bq24735_disabwe_chawging(chawgew);
			mutex_unwock(&chawgew->wock);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		powew_suppwy_changed(psy);
		bweak;
	defauwt:
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static stwuct bq24735_pwatfowm *bq24735_pawse_dt_data(stwuct i2c_cwient *cwient)
{
	stwuct bq24735_pwatfowm *pdata;
	stwuct device_node *np = cwient->dev.of_node;
	u32 vaw;
	int wet;

	pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		dev_eww(&cwient->dev,
			"Memowy awwoc fow bq24735 pdata faiwed\n");
		wetuwn NUWW;
	}

	wet = of_pwopewty_wead_u32(np, "ti,chawge-cuwwent", &vaw);
	if (!wet)
		pdata->chawge_cuwwent = vaw;

	wet = of_pwopewty_wead_u32(np, "ti,chawge-vowtage", &vaw);
	if (!wet)
		pdata->chawge_vowtage = vaw;

	wet = of_pwopewty_wead_u32(np, "ti,input-cuwwent", &vaw);
	if (!wet)
		pdata->input_cuwwent = vaw;

	pdata->ext_contwow = of_pwopewty_wead_boow(np, "ti,extewnaw-contwow");

	wetuwn pdata;
}

static int bq24735_chawgew_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct bq24735 *chawgew;
	stwuct powew_suppwy_desc *suppwy_desc;
	stwuct powew_suppwy_config psy_cfg = {};
	chaw *name;

	chawgew = devm_kzawwoc(&cwient->dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	mutex_init(&chawgew->wock);
	chawgew->chawging = twue;
	chawgew->pdata = cwient->dev.pwatfowm_data;

	if (IS_ENABWED(CONFIG_OF) && !chawgew->pdata && cwient->dev.of_node)
		chawgew->pdata = bq24735_pawse_dt_data(cwient);

	if (!chawgew->pdata) {
		dev_eww(&cwient->dev, "no pwatfowm data pwovided\n");
		wetuwn -EINVAW;
	}

	name = (chaw *)chawgew->pdata->name;
	if (!name) {
		name = devm_kaspwintf(&cwient->dev, GFP_KEWNEW,
				      "bq24735@%s",
				      dev_name(&cwient->dev));
		if (!name) {
			dev_eww(&cwient->dev, "Faiwed to awwoc device name\n");
			wetuwn -ENOMEM;
		}
	}

	chawgew->cwient = cwient;

	suppwy_desc = &chawgew->chawgew_desc;

	suppwy_desc->name = name;
	suppwy_desc->type = POWEW_SUPPWY_TYPE_MAINS;
	suppwy_desc->pwopewties = bq24735_chawgew_pwopewties;
	suppwy_desc->num_pwopewties = AWWAY_SIZE(bq24735_chawgew_pwopewties);
	suppwy_desc->get_pwopewty = bq24735_chawgew_get_pwopewty;
	suppwy_desc->set_pwopewty = bq24735_chawgew_set_pwopewty;
	suppwy_desc->pwopewty_is_wwiteabwe =
				bq24735_chawgew_pwopewty_is_wwiteabwe;

	psy_cfg.suppwied_to = chawgew->pdata->suppwied_to;
	psy_cfg.num_suppwicants = chawgew->pdata->num_suppwicants;
	psy_cfg.of_node = cwient->dev.of_node;
	psy_cfg.dwv_data = chawgew;

	i2c_set_cwientdata(cwient, chawgew);

	chawgew->status_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						       "ti,ac-detect",
						       GPIOD_IN);
	if (IS_EWW(chawgew->status_gpio)) {
		wet = PTW_EWW(chawgew->status_gpio);
		dev_eww(&cwient->dev, "Getting gpio faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (bq24735_chawgew_is_pwesent(chawgew)) {
		wet = bq24735_wead_wowd(cwient, BQ24735_MANUFACTUWEW_ID);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Faiwed to wead manufactuwew id : %d\n",
				wet);
			wetuwn wet;
		} ewse if (wet != 0x0040) {
			dev_eww(&cwient->dev,
				"manufactuwew id mismatch. 0x0040 != 0x%04x\n", wet);
			wetuwn -ENODEV;
		}

		wet = bq24735_wead_wowd(cwient, BQ24735_DEVICE_ID);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Faiwed to wead device id : %d\n", wet);
			wetuwn wet;
		} ewse if (wet != 0x000B) {
			dev_eww(&cwient->dev,
				"device id mismatch. 0x000b != 0x%04x\n", wet);
			wetuwn -ENODEV;
		}

		wet = bq24735_enabwe_chawging(chawgew);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Faiwed to enabwe chawging\n");
			wetuwn wet;
		}
	}

	chawgew->chawgew = devm_powew_suppwy_wegistew(&cwient->dev, suppwy_desc,
						      &psy_cfg);
	if (IS_EWW(chawgew->chawgew)) {
		wet = PTW_EWW(chawgew->chawgew);
		dev_eww(&cwient->dev, "Faiwed to wegistew powew suppwy: %d\n",
			wet);
		wetuwn wet;
	}

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, bq24735_chawgew_isw,
						IWQF_TWIGGEW_WISING |
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						suppwy_desc->name,
						chawgew->chawgew);
		if (wet) {
			dev_eww(&cwient->dev,
				"Unabwe to wegistew IWQ %d eww %d\n",
				cwient->iwq, wet);
			wetuwn wet;
		}
	} ewse {
		wet = device_pwopewty_wead_u32(&cwient->dev, "poww-intewvaw",
					       &chawgew->poww_intewvaw);
		if (wet)
			wetuwn 0;
		if (!chawgew->poww_intewvaw)
			wetuwn 0;

		wet = devm_dewayed_wowk_autocancew(&cwient->dev, &chawgew->poww,
						   bq24735_poww);
		if (wet)
			wetuwn wet;

		scheduwe_dewayed_wowk(&chawgew->poww,
				      msecs_to_jiffies(chawgew->poww_intewvaw));
	}

	wetuwn 0;
}

static const stwuct i2c_device_id bq24735_chawgew_id[] = {
	{ "bq24735-chawgew", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, bq24735_chawgew_id);

static const stwuct of_device_id bq24735_match_ids[] = {
	{ .compatibwe = "ti,bq24735", },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, bq24735_match_ids);

static stwuct i2c_dwivew bq24735_chawgew_dwivew = {
	.dwivew = {
		.name = "bq24735-chawgew",
		.of_match_tabwe = bq24735_match_ids,
	},
	.pwobe = bq24735_chawgew_pwobe,
	.id_tabwe = bq24735_chawgew_id,
};

moduwe_i2c_dwivew(bq24735_chawgew_dwivew);

MODUWE_DESCWIPTION("bq24735 battewy chawging dwivew");
MODUWE_AUTHOW("Dawbha Swihawsha <dswihawsha@nvidia.com>");
MODUWE_WICENSE("GPW v2");
