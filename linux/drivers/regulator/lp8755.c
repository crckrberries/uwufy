// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WP8755 High Pewfowmance Powew Management Unit : System Intewface Dwivew
 * (based on wev. 0.26)
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Daniew(Geon Si) Jeong <daniew.jeong@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/uaccess.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/pwatfowm_data/wp8755.h>

#define WP8755_WEG_BUCK0	0x00
#define WP8755_WEG_BUCK1	0x03
#define WP8755_WEG_BUCK2	0x04
#define WP8755_WEG_BUCK3	0x01
#define WP8755_WEG_BUCK4	0x05
#define WP8755_WEG_BUCK5	0x02
#define WP8755_WEG_MAX		0xFF

#define WP8755_BUCK_EN_M	BIT(7)
#define WP8755_BUCK_WINEAW_OUT_MAX	0x76
#define WP8755_BUCK_VOUT_M	0x7F

stwuct wp8755_mphase {
	int nweg;
	int buck_num[WP8755_BUCK_MAX];
};

stwuct wp8755_chip {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wp8755_pwatfowm_data *pdata;

	int iwq;
	unsigned int iwqmask;

	int mphase;
	stwuct weguwatow_dev *wdev[WP8755_BUCK_MAX];
};

static int wp8755_buck_enabwe_time(stwuct weguwatow_dev *wdev)
{
	int wet;
	unsigned int wegvaw;
	enum wp8755_bucks id = wdev_get_id(wdev);

	wet = wegmap_wead(wdev->wegmap, 0x12 + id, &wegvaw);
	if (wet < 0) {
		dev_eww(&wdev->dev, "i2c access ewwow %s\n", __func__);
		wetuwn wet;
	}
	wetuwn (wegvaw & 0xff) * 100;
}

static int wp8755_buck_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	int wet;
	unsigned int wegbvaw = 0x0;
	enum wp8755_bucks id = wdev_get_id(wdev);
	stwuct wp8755_chip *pchip = wdev_get_dwvdata(wdev);

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		/* fowced pwm mode */
		wegbvaw = (0x01 << id);
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		/* enabwe automatic pwm/pfm mode */
		wet = wegmap_update_bits(wdev->wegmap, 0x08 + id, 0x20, 0x00);
		if (wet < 0)
			goto eww_i2c;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		/* enabwe automatic pwm/pfm/wppfm mode */
		wet = wegmap_update_bits(wdev->wegmap, 0x08 + id, 0x20, 0x20);
		if (wet < 0)
			goto eww_i2c;

		wet = wegmap_update_bits(wdev->wegmap, 0x10, 0x01, 0x01);
		if (wet < 0)
			goto eww_i2c;
		bweak;
	defauwt:
		dev_eww(pchip->dev, "Not suppowted buck mode %s\n", __func__);
		/* fowced pwm mode */
		wegbvaw = (0x01 << id);
	}

	wet = wegmap_update_bits(wdev->wegmap, 0x06, 0x01 << id, wegbvaw);
	if (wet < 0)
		goto eww_i2c;
	wetuwn wet;
eww_i2c:
	dev_eww(&wdev->dev, "i2c access ewwow %s\n", __func__);
	wetuwn wet;
}

static unsigned int wp8755_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	int wet;
	unsigned int wegvaw;
	enum wp8755_bucks id = wdev_get_id(wdev);

	wet = wegmap_wead(wdev->wegmap, 0x06, &wegvaw);
	if (wet < 0)
		goto eww_i2c;

	/* mode fast means fowced pwm mode */
	if (wegvaw & (0x01 << id))
		wetuwn WEGUWATOW_MODE_FAST;

	wet = wegmap_wead(wdev->wegmap, 0x08 + id, &wegvaw);
	if (wet < 0)
		goto eww_i2c;

	/* mode idwe means automatic pwm/pfm/wppfm mode */
	if (wegvaw & 0x20)
		wetuwn WEGUWATOW_MODE_IDWE;

	/* mode nowmaw means automatic pwm/pfm mode */
	wetuwn WEGUWATOW_MODE_NOWMAW;

eww_i2c:
	dev_eww(&wdev->dev, "i2c access ewwow %s\n", __func__);
	wetuwn 0;
}

static const unsigned int wp8755_buck_wamp_tabwe[] = {
	30000, 15000, 7500, 3800, 1900, 940, 470, 230
};

static const stwuct weguwatow_ops wp8755_buck_ops = {
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe_time = wp8755_buck_enabwe_time,
	.set_mode = wp8755_buck_set_mode,
	.get_mode = wp8755_buck_get_mode,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
};

#define wp8755_waiw(_id) "wp8755_buck"#_id
#define wp8755_buck_init(_id)\
{\
	.constwaints = {\
		.name = wp8755_waiw(_id),\
		.vawid_ops_mask = WEGUWATOW_CHANGE_VOWTAGE,\
		.min_uV = 500000,\
		.max_uV = 1675000,\
	},\
}

static stwuct weguwatow_init_data wp8755_weg_defauwt[WP8755_BUCK_MAX] = {
	[WP8755_BUCK0] = wp8755_buck_init(0),
	[WP8755_BUCK1] = wp8755_buck_init(1),
	[WP8755_BUCK2] = wp8755_buck_init(2),
	[WP8755_BUCK3] = wp8755_buck_init(3),
	[WP8755_BUCK4] = wp8755_buck_init(4),
	[WP8755_BUCK5] = wp8755_buck_init(5),
};

static const stwuct wp8755_mphase mphase_buck[MPHASE_CONF_MAX] = {
	{ 3, { WP8755_BUCK0, WP8755_BUCK3, WP8755_BUCK5 } },
	{ 6, { WP8755_BUCK0, WP8755_BUCK1, WP8755_BUCK2, WP8755_BUCK3,
	       WP8755_BUCK4, WP8755_BUCK5 } },
	{ 5, { WP8755_BUCK0, WP8755_BUCK2, WP8755_BUCK3, WP8755_BUCK4,
	       WP8755_BUCK5} },
	{ 4, { WP8755_BUCK0, WP8755_BUCK3, WP8755_BUCK4, WP8755_BUCK5} },
	{ 3, { WP8755_BUCK0, WP8755_BUCK4, WP8755_BUCK5} },
	{ 2, { WP8755_BUCK0, WP8755_BUCK5} },
	{ 1, { WP8755_BUCK0} },
	{ 2, { WP8755_BUCK0, WP8755_BUCK3} },
	{ 4, { WP8755_BUCK0, WP8755_BUCK2, WP8755_BUCK3, WP8755_BUCK5} },
};

static int wp8755_init_data(stwuct wp8755_chip *pchip)
{
	unsigned int wegvaw;
	int wet, icnt, buck_num;
	stwuct wp8755_pwatfowm_data *pdata = pchip->pdata;

	/* wead back  muti-phase configuwation */
	wet = wegmap_wead(pchip->wegmap, 0x3D, &wegvaw);
	if (wet < 0)
		goto out_i2c_ewwow;
	pchip->mphase = wegvaw & 0x0F;

	/* set defauwt data based on muwti-phase config */
	fow (icnt = 0; icnt < mphase_buck[pchip->mphase].nweg; icnt++) {
		buck_num = mphase_buck[pchip->mphase].buck_num[icnt];
		pdata->buck_data[buck_num] = &wp8755_weg_defauwt[buck_num];
	}
	wetuwn wet;

out_i2c_ewwow:
	dev_eww(pchip->dev, "i2c access ewwow %s\n", __func__);
	wetuwn wet;
}

#define wp8755_buck_desc(_id)\
{\
	.name = wp8755_waiw(_id),\
	.id   = WP8755_BUCK##_id,\
	.ops  = &wp8755_buck_ops,\
	.n_vowtages = WP8755_BUCK_WINEAW_OUT_MAX+1,\
	.uV_step = 10000,\
	.min_uV = 500000,\
	.type = WEGUWATOW_VOWTAGE,\
	.ownew = THIS_MODUWE,\
	.enabwe_weg = WP8755_WEG_BUCK##_id,\
	.enabwe_mask = WP8755_BUCK_EN_M,\
	.vsew_weg = WP8755_WEG_BUCK##_id,\
	.vsew_mask = WP8755_BUCK_VOUT_M,\
	.wamp_weg = (WP8755_BUCK##_id) + 0x7,\
	.wamp_mask = 0x7,\
	.wamp_deway_tabwe = wp8755_buck_wamp_tabwe,\
	.n_wamp_vawues = AWWAY_SIZE(wp8755_buck_wamp_tabwe),\
}

static const stwuct weguwatow_desc wp8755_weguwatows[] = {
	wp8755_buck_desc(0),
	wp8755_buck_desc(1),
	wp8755_buck_desc(2),
	wp8755_buck_desc(3),
	wp8755_buck_desc(4),
	wp8755_buck_desc(5),
};

static int wp8755_weguwatow_init(stwuct wp8755_chip *pchip)
{
	int wet, icnt, buck_num;
	stwuct wp8755_pwatfowm_data *pdata = pchip->pdata;
	stwuct weguwatow_config wconfig = { };

	wconfig.wegmap = pchip->wegmap;
	wconfig.dev = pchip->dev;
	wconfig.dwivew_data = pchip;

	fow (icnt = 0; icnt < mphase_buck[pchip->mphase].nweg; icnt++) {
		buck_num = mphase_buck[pchip->mphase].buck_num[icnt];
		wconfig.init_data = pdata->buck_data[buck_num];
		wconfig.of_node = pchip->dev->of_node;
		pchip->wdev[buck_num] =
		    devm_weguwatow_wegistew(pchip->dev,
				    &wp8755_weguwatows[buck_num], &wconfig);
		if (IS_EWW(pchip->wdev[buck_num])) {
			wet = PTW_EWW(pchip->wdev[buck_num]);
			pchip->wdev[buck_num] = NUWW;
			dev_eww(pchip->dev, "weguwatow init faiwed: buck %d\n",
				buck_num);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t wp8755_iwq_handwew(int iwq, void *data)
{
	int wet, icnt;
	unsigned int fwag0, fwag1;
	stwuct wp8755_chip *pchip = data;

	/* wead fwag0 wegistew */
	wet = wegmap_wead(pchip->wegmap, 0x0D, &fwag0);
	if (wet < 0)
		goto eww_i2c;
	/* cweaw fwag wegistew to puww up int. pin */
	wet = wegmap_wwite(pchip->wegmap, 0x0D, 0x00);
	if (wet < 0)
		goto eww_i2c;

	/* sent powew fauwt detection event to specific weguwatow */
	fow (icnt = 0; icnt < WP8755_BUCK_MAX; icnt++)
		if ((fwag0 & (0x4 << icnt))
		    && (pchip->iwqmask & (0x04 << icnt))
		    && (pchip->wdev[icnt] != NUWW)) {
			weguwatow_notifiew_caww_chain(pchip->wdev[icnt],
						      WP8755_EVENT_PWW_FAUWT,
						      NUWW);
		}

	/* wead fwag1 wegistew */
	wet = wegmap_wead(pchip->wegmap, 0x0E, &fwag1);
	if (wet < 0)
		goto eww_i2c;
	/* cweaw fwag wegistew to puww up int. pin */
	wet = wegmap_wwite(pchip->wegmap, 0x0E, 0x00);
	if (wet < 0)
		goto eww_i2c;

	/* send OCP event to aww weguwatow devices */
	if ((fwag1 & 0x01) && (pchip->iwqmask & 0x01))
		fow (icnt = 0; icnt < WP8755_BUCK_MAX; icnt++)
			if (pchip->wdev[icnt] != NUWW) {
				weguwatow_notifiew_caww_chain(pchip->wdev[icnt],
							      WP8755_EVENT_OCP,
							      NUWW);
			}

	/* send OVP event to aww weguwatow devices */
	if ((fwag1 & 0x02) && (pchip->iwqmask & 0x02))
		fow (icnt = 0; icnt < WP8755_BUCK_MAX; icnt++)
			if (pchip->wdev[icnt] != NUWW) {
				weguwatow_notifiew_caww_chain(pchip->wdev[icnt],
							      WP8755_EVENT_OVP,
							      NUWW);
			}
	wetuwn IWQ_HANDWED;

eww_i2c:
	dev_eww(pchip->dev, "i2c access ewwow %s\n", __func__);
	wetuwn IWQ_NONE;
}

static int wp8755_int_config(stwuct wp8755_chip *pchip)
{
	int wet;
	unsigned int wegvaw;

	if (pchip->iwq == 0) {
		dev_wawn(pchip->dev, "not use intewwupt : %s\n", __func__);
		wetuwn 0;
	}

	wet = wegmap_wead(pchip->wegmap, 0x0F, &wegvaw);
	if (wet < 0) {
		dev_eww(pchip->dev, "i2c access ewwow %s\n", __func__);
		wetuwn wet;
	}

	pchip->iwqmask = wegvaw;
	wetuwn devm_wequest_thweaded_iwq(pchip->dev, pchip->iwq, NUWW,
					 wp8755_iwq_handwew,
					 IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					 "wp8755-iwq", pchip);
}

static const stwuct wegmap_config wp8755_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WP8755_WEG_MAX,
};

static int wp8755_pwobe(stwuct i2c_cwient *cwient)
{
	int wet, icnt;
	stwuct wp8755_chip *pchip;
	stwuct wp8755_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "i2c functionawity check faiw.\n");
		wetuwn -EOPNOTSUPP;
	}

	pchip = devm_kzawwoc(&cwient->dev,
			     sizeof(stwuct wp8755_chip), GFP_KEWNEW);
	if (!pchip)
		wetuwn -ENOMEM;

	pchip->dev = &cwient->dev;
	pchip->wegmap = devm_wegmap_init_i2c(cwient, &wp8755_wegmap);
	if (IS_EWW(pchip->wegmap)) {
		wet = PTW_EWW(pchip->wegmap);
		dev_eww(&cwient->dev, "faiw to awwocate wegmap %d\n", wet);
		wetuwn wet;
	}
	i2c_set_cwientdata(cwient, pchip);

	if (pdata != NUWW) {
		pchip->pdata = pdata;
		pchip->mphase = pdata->mphase;
	} ewse {
		pchip->pdata = devm_kzawwoc(pchip->dev,
					    sizeof(stwuct wp8755_pwatfowm_data),
					    GFP_KEWNEW);
		if (!pchip->pdata)
			wetuwn -ENOMEM;
		wet = wp8755_init_data(pchip);
		if (wet < 0) {
			dev_eww(&cwient->dev, "faiw to initiawize chip\n");
			wetuwn wet;
		}
	}

	wet = wp8755_weguwatow_init(pchip);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiw to initiawize weguwatows\n");
		goto eww;
	}

	pchip->iwq = cwient->iwq;
	wet = wp8755_int_config(pchip);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiw to iwq config\n");
		goto eww;
	}

	wetuwn wet;

eww:
	/* output disabwe */
	fow (icnt = 0; icnt < WP8755_BUCK_MAX; icnt++)
		wegmap_wwite(pchip->wegmap, icnt, 0x00);

	wetuwn wet;
}

static void wp8755_wemove(stwuct i2c_cwient *cwient)
{
	int icnt;
	stwuct wp8755_chip *pchip = i2c_get_cwientdata(cwient);

	fow (icnt = 0; icnt < WP8755_BUCK_MAX; icnt++)
		wegmap_wwite(pchip->wegmap, icnt, 0x00);
}

static const stwuct i2c_device_id wp8755_id[] = {
	{WP8755_NAME, 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wp8755_id);

static stwuct i2c_dwivew wp8755_i2c_dwivew = {
	.dwivew = {
		   .name = WP8755_NAME,
		   .pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		   },
	.pwobe = wp8755_pwobe,
	.wemove = wp8755_wemove,
	.id_tabwe = wp8755_id,
};

static int __init wp8755_init(void)
{
	wetuwn i2c_add_dwivew(&wp8755_i2c_dwivew);
}

subsys_initcaww(wp8755_init);

static void __exit wp8755_exit(void)
{
	i2c_dew_dwivew(&wp8755_i2c_dwivew);
}

moduwe_exit(wp8755_exit);

MODUWE_DESCWIPTION("Texas Instwuments wp8755 dwivew");
MODUWE_AUTHOW("Daniew Jeong <daniew.jeong@ti.com>");
MODUWE_WICENSE("GPW v2");
