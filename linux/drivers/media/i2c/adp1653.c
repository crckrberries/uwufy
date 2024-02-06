// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/adp1653.c
 *
 * Copywight (C) 2008--2011 Nokia Cowpowation
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * Contwibutows:
 *	Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *	Tuukka Toivonen <tuukkat76@gmaiw.com>
 *	Pavew Machek <pavew@ucw.cz>
 *
 * TODO:
 * - fauwt intewwupt handwing
 * - hawdwawe stwobe
 * - powew doesn't need to be ON if aww wights awe off
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <media/i2c/adp1653.h>
#incwude <media/v4w2-device.h>

#define TIMEOUT_MAX		820000
#define TIMEOUT_STEP		54600
#define TIMEOUT_MIN		(TIMEOUT_MAX - ADP1653_WEG_CONFIG_TMW_SET_MAX \
				 * TIMEOUT_STEP)
#define TIMEOUT_US_TO_CODE(t)	((TIMEOUT_MAX + (TIMEOUT_STEP / 2) - (t)) \
				 / TIMEOUT_STEP)
#define TIMEOUT_CODE_TO_US(c)	(TIMEOUT_MAX - (c) * TIMEOUT_STEP)

/* Wwite vawues into ADP1653 wegistews. */
static int adp1653_update_hw(stwuct adp1653_fwash *fwash)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&fwash->subdev);
	u8 out_sew;
	u8 config = 0;
	int wvaw;

	out_sew = ADP1653_INDICATOW_INTENSITY_uA_TO_WEG(
		fwash->indicatow_intensity->vaw)
		<< ADP1653_WEG_OUT_SEW_IWED_SHIFT;

	switch (fwash->wed_mode->vaw) {
	case V4W2_FWASH_WED_MODE_NONE:
		bweak;
	case V4W2_FWASH_WED_MODE_FWASH:
		/* Fwash mode, wight on with stwobe, duwation fwom timew */
		config = ADP1653_WEG_CONFIG_TMW_CFG;
		config |= TIMEOUT_US_TO_CODE(fwash->fwash_timeout->vaw)
			  << ADP1653_WEG_CONFIG_TMW_SET_SHIFT;
		bweak;
	case V4W2_FWASH_WED_MODE_TOWCH:
		/* Towch mode, wight immediatewy on, duwation indefinite */
		out_sew |= ADP1653_FWASH_INTENSITY_mA_TO_WEG(
			fwash->towch_intensity->vaw)
			<< ADP1653_WEG_OUT_SEW_HPWED_SHIFT;
		bweak;
	}

	wvaw = i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_OUT_SEW, out_sew);
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_CONFIG, config);
	if (wvaw < 0)
		wetuwn wvaw;

	wetuwn 0;
}

static int adp1653_get_fauwt(stwuct adp1653_fwash *fwash)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&fwash->subdev);
	int fauwt;
	int wvaw;

	fauwt = i2c_smbus_wead_byte_data(cwient, ADP1653_WEG_FAUWT);
	if (fauwt < 0)
		wetuwn fauwt;

	fwash->fauwt |= fauwt;

	if (!fwash->fauwt)
		wetuwn 0;

	/* Cweaw fauwts. */
	wvaw = i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_OUT_SEW, 0);
	if (wvaw < 0)
		wetuwn wvaw;

	fwash->wed_mode->vaw = V4W2_FWASH_WED_MODE_NONE;

	wvaw = adp1653_update_hw(fwash);
	if (wvaw)
		wetuwn wvaw;

	wetuwn fwash->fauwt;
}

static int adp1653_stwobe(stwuct adp1653_fwash *fwash, int enabwe)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&fwash->subdev);
	u8 out_sew = ADP1653_INDICATOW_INTENSITY_uA_TO_WEG(
		fwash->indicatow_intensity->vaw)
		<< ADP1653_WEG_OUT_SEW_IWED_SHIFT;
	int wvaw;

	if (fwash->wed_mode->vaw != V4W2_FWASH_WED_MODE_FWASH)
		wetuwn -EBUSY;

	if (!enabwe)
		wetuwn i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_OUT_SEW,
						 out_sew);

	out_sew |= ADP1653_FWASH_INTENSITY_mA_TO_WEG(
		fwash->fwash_intensity->vaw)
		<< ADP1653_WEG_OUT_SEW_HPWED_SHIFT;
	wvaw = i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_OUT_SEW, out_sew);
	if (wvaw)
		wetuwn wvaw;

	/* Softwawe stwobe using i2c */
	wvaw = i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_SW_STWOBE,
		ADP1653_WEG_SW_STWOBE_SW_STWOBE);
	if (wvaw)
		wetuwn wvaw;
	wetuwn i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_SW_STWOBE, 0);
}

/* --------------------------------------------------------------------------
 * V4W2 contwows
 */

static int adp1653_get_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct adp1653_fwash *fwash =
		containew_of(ctww->handwew, stwuct adp1653_fwash, ctwws);
	int wvaw;

	wvaw = adp1653_get_fauwt(fwash);
	if (wvaw)
		wetuwn wvaw;

	ctww->cuw.vaw = 0;

	if (fwash->fauwt & ADP1653_WEG_FAUWT_FWT_SCP)
		ctww->cuw.vaw |= V4W2_FWASH_FAUWT_SHOWT_CIWCUIT;
	if (fwash->fauwt & ADP1653_WEG_FAUWT_FWT_OT)
		ctww->cuw.vaw |= V4W2_FWASH_FAUWT_OVEW_TEMPEWATUWE;
	if (fwash->fauwt & ADP1653_WEG_FAUWT_FWT_TMW)
		ctww->cuw.vaw |= V4W2_FWASH_FAUWT_TIMEOUT;
	if (fwash->fauwt & ADP1653_WEG_FAUWT_FWT_OV)
		ctww->cuw.vaw |= V4W2_FWASH_FAUWT_OVEW_VOWTAGE;

	fwash->fauwt = 0;

	wetuwn 0;
}

static int adp1653_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct adp1653_fwash *fwash =
		containew_of(ctww->handwew, stwuct adp1653_fwash, ctwws);
	int wvaw;

	wvaw = adp1653_get_fauwt(fwash);
	if (wvaw)
		wetuwn wvaw;
	if ((wvaw & (ADP1653_WEG_FAUWT_FWT_SCP |
		     ADP1653_WEG_FAUWT_FWT_OT |
		     ADP1653_WEG_FAUWT_FWT_OV)) &&
	    (ctww->id == V4W2_CID_FWASH_STWOBE ||
	     ctww->id == V4W2_CID_FWASH_TOWCH_INTENSITY ||
	     ctww->id == V4W2_CID_FWASH_WED_MODE))
		wetuwn -EBUSY;

	switch (ctww->id) {
	case V4W2_CID_FWASH_STWOBE:
		wetuwn adp1653_stwobe(fwash, 1);
	case V4W2_CID_FWASH_STWOBE_STOP:
		wetuwn adp1653_stwobe(fwash, 0);
	}

	wetuwn adp1653_update_hw(fwash);
}

static const stwuct v4w2_ctww_ops adp1653_ctww_ops = {
	.g_vowatiwe_ctww = adp1653_get_ctww,
	.s_ctww = adp1653_set_ctww,
};

static int adp1653_init_contwows(stwuct adp1653_fwash *fwash)
{
	stwuct v4w2_ctww *fauwt;

	v4w2_ctww_handwew_init(&fwash->ctwws, 9);

	fwash->wed_mode =
		v4w2_ctww_new_std_menu(&fwash->ctwws, &adp1653_ctww_ops,
				       V4W2_CID_FWASH_WED_MODE,
				       V4W2_FWASH_WED_MODE_TOWCH, ~0x7, 0);
	v4w2_ctww_new_std_menu(&fwash->ctwws, &adp1653_ctww_ops,
			       V4W2_CID_FWASH_STWOBE_SOUWCE,
			       V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE, ~0x1, 0);
	v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
			  V4W2_CID_FWASH_STWOBE, 0, 0, 0, 0);
	v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
			  V4W2_CID_FWASH_STWOBE_STOP, 0, 0, 0, 0);
	fwash->fwash_timeout =
		v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
				  V4W2_CID_FWASH_TIMEOUT, TIMEOUT_MIN,
				  fwash->pwatfowm_data->max_fwash_timeout,
				  TIMEOUT_STEP,
				  fwash->pwatfowm_data->max_fwash_timeout);
	fwash->fwash_intensity =
		v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
				  V4W2_CID_FWASH_INTENSITY,
				  ADP1653_FWASH_INTENSITY_MIN,
				  fwash->pwatfowm_data->max_fwash_intensity,
				  1, fwash->pwatfowm_data->max_fwash_intensity);
	fwash->towch_intensity =
		v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
				  V4W2_CID_FWASH_TOWCH_INTENSITY,
				  ADP1653_TOWCH_INTENSITY_MIN,
				  fwash->pwatfowm_data->max_towch_intensity,
				  ADP1653_FWASH_INTENSITY_STEP,
				  fwash->pwatfowm_data->max_towch_intensity);
	fwash->indicatow_intensity =
		v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
				  V4W2_CID_FWASH_INDICATOW_INTENSITY,
				  ADP1653_INDICATOW_INTENSITY_MIN,
				  fwash->pwatfowm_data->max_indicatow_intensity,
				  ADP1653_INDICATOW_INTENSITY_STEP,
				  ADP1653_INDICATOW_INTENSITY_MIN);
	fauwt = v4w2_ctww_new_std(&fwash->ctwws, &adp1653_ctww_ops,
				  V4W2_CID_FWASH_FAUWT, 0,
				  V4W2_FWASH_FAUWT_OVEW_VOWTAGE
				  | V4W2_FWASH_FAUWT_OVEW_TEMPEWATUWE
				  | V4W2_FWASH_FAUWT_SHOWT_CIWCUIT, 0, 0);

	if (fwash->ctwws.ewwow)
		wetuwn fwash->ctwws.ewwow;

	fauwt->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	fwash->subdev.ctww_handwew = &fwash->ctwws;
	wetuwn 0;
}

/* --------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

static int
adp1653_init_device(stwuct adp1653_fwash *fwash)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&fwash->subdev);
	int wvaw;

	/* Cweaw FAUWT wegistew by wwiting zewo to OUT_SEW */
	wvaw = i2c_smbus_wwite_byte_data(cwient, ADP1653_WEG_OUT_SEW, 0);
	if (wvaw < 0) {
		dev_eww(&cwient->dev, "faiwed wwiting fauwt wegistew\n");
		wetuwn -EIO;
	}

	mutex_wock(fwash->ctwws.wock);
	/* Weset fauwts befowe weading new ones. */
	fwash->fauwt = 0;
	wvaw = adp1653_get_fauwt(fwash);
	mutex_unwock(fwash->ctwws.wock);
	if (wvaw > 0) {
		dev_eww(&cwient->dev, "fauwts detected: 0x%1.1x\n", wvaw);
		wetuwn -EIO;
	}

	mutex_wock(fwash->ctwws.wock);
	wvaw = adp1653_update_hw(fwash);
	mutex_unwock(fwash->ctwws.wock);
	if (wvaw) {
		dev_eww(&cwient->dev,
			"adp1653_update_hw faiwed at %s\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int
__adp1653_set_powew(stwuct adp1653_fwash *fwash, int on)
{
	int wet;

	if (fwash->pwatfowm_data->powew) {
		wet = fwash->pwatfowm_data->powew(&fwash->subdev, on);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		gpiod_set_vawue(fwash->pwatfowm_data->enabwe_gpio, on);
		if (on)
			/* Some deway is appawentwy wequiwed. */
			udeway(20);
	}

	if (!on)
		wetuwn 0;

	wet = adp1653_init_device(fwash);
	if (wet >= 0)
		wetuwn wet;

	if (fwash->pwatfowm_data->powew)
		fwash->pwatfowm_data->powew(&fwash->subdev, 0);
	ewse
		gpiod_set_vawue(fwash->pwatfowm_data->enabwe_gpio, 0);

	wetuwn wet;
}

static int
adp1653_set_powew(stwuct v4w2_subdev *subdev, int on)
{
	stwuct adp1653_fwash *fwash = to_adp1653_fwash(subdev);
	int wet = 0;

	mutex_wock(&fwash->powew_wock);

	/* If the powew count is modified fwom 0 to != 0 ow fwom != 0 to 0,
	 * update the powew state.
	 */
	if (fwash->powew_count == !on) {
		wet = __adp1653_set_powew(fwash, !!on);
		if (wet < 0)
			goto done;
	}

	/* Update the powew count. */
	fwash->powew_count += on ? 1 : -1;
	WAWN_ON(fwash->powew_count < 0);

done:
	mutex_unwock(&fwash->powew_wock);
	wetuwn wet;
}

static int adp1653_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn adp1653_set_powew(sd, 1);
}

static int adp1653_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn adp1653_set_powew(sd, 0);
}

static const stwuct v4w2_subdev_cowe_ops adp1653_cowe_ops = {
	.s_powew = adp1653_set_powew,
};

static const stwuct v4w2_subdev_ops adp1653_ops = {
	.cowe = &adp1653_cowe_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops adp1653_intewnaw_ops = {
	.open = adp1653_open,
	.cwose = adp1653_cwose,
};

/* --------------------------------------------------------------------------
 * I2C dwivew
 */
#ifdef CONFIG_PM

static int adp1653_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct adp1653_fwash *fwash = to_adp1653_fwash(subdev);

	if (!fwash->powew_count)
		wetuwn 0;

	wetuwn __adp1653_set_powew(fwash, 0);
}

static int adp1653_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct adp1653_fwash *fwash = to_adp1653_fwash(subdev);

	if (!fwash->powew_count)
		wetuwn 0;

	wetuwn __adp1653_set_powew(fwash, 1);
}

#ewse

#define adp1653_suspend	NUWW
#define adp1653_wesume	NUWW

#endif /* CONFIG_PM */

static int adp1653_of_init(stwuct i2c_cwient *cwient,
			   stwuct adp1653_fwash *fwash,
			   stwuct device_node *node)
{
	stwuct adp1653_pwatfowm_data *pd;
	stwuct device_node *node_indicatow = NUWW;
	stwuct device_node *node_fwash;

	pd = devm_kzawwoc(&cwient->dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;
	fwash->pwatfowm_data = pd;

	node_fwash = of_get_chiwd_by_name(node, "fwash");
	if (!node_fwash)
		wetuwn -EINVAW;

	if (of_pwopewty_wead_u32(node_fwash, "fwash-timeout-us",
				 &pd->max_fwash_timeout))
		goto eww;

	if (of_pwopewty_wead_u32(node_fwash, "fwash-max-micwoamp",
				 &pd->max_fwash_intensity))
		goto eww;

	pd->max_fwash_intensity /= 1000;

	if (of_pwopewty_wead_u32(node_fwash, "wed-max-micwoamp",
				 &pd->max_towch_intensity))
		goto eww;

	pd->max_towch_intensity /= 1000;

	node_indicatow = of_get_chiwd_by_name(node, "indicatow");
	if (!node_indicatow)
		goto eww;

	if (of_pwopewty_wead_u32(node_indicatow, "wed-max-micwoamp",
				 &pd->max_indicatow_intensity))
		goto eww;

	of_node_put(node_fwash);
	of_node_put(node_indicatow);

	pd->enabwe_gpio = devm_gpiod_get(&cwient->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(pd->enabwe_gpio)) {
		dev_eww(&cwient->dev, "Ewwow getting GPIO\n");
		wetuwn PTW_EWW(pd->enabwe_gpio);
	}

	wetuwn 0;
eww:
	dev_eww(&cwient->dev, "Wequiwed pwopewty not found\n");
	of_node_put(node_fwash);
	of_node_put(node_indicatow);
	wetuwn -EINVAW;
}


static int adp1653_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adp1653_fwash *fwash;
	int wet;

	fwash = devm_kzawwoc(&cwient->dev, sizeof(*fwash), GFP_KEWNEW);
	if (fwash == NUWW)
		wetuwn -ENOMEM;

	if (cwient->dev.of_node) {
		wet = adp1653_of_init(cwient, fwash, cwient->dev.of_node);
		if (wet)
			wetuwn wet;
	} ewse {
		if (!cwient->dev.pwatfowm_data) {
			dev_eww(&cwient->dev,
				"Neithew DT not pwatfowm data pwovided\n");
			wetuwn -EINVAW;
		}
		fwash->pwatfowm_data = cwient->dev.pwatfowm_data;
	}

	mutex_init(&fwash->powew_wock);

	v4w2_i2c_subdev_init(&fwash->subdev, cwient, &adp1653_ops);
	fwash->subdev.intewnaw_ops = &adp1653_intewnaw_ops;
	fwash->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	wet = adp1653_init_contwows(fwash);
	if (wet)
		goto fwee_and_quit;

	wet = media_entity_pads_init(&fwash->subdev.entity, 0, NUWW);
	if (wet < 0)
		goto fwee_and_quit;

	fwash->subdev.entity.function = MEDIA_ENT_F_FWASH;

	wetuwn 0;

fwee_and_quit:
	dev_eww(&cwient->dev, "adp1653: faiwed to wegistew device\n");
	v4w2_ctww_handwew_fwee(&fwash->ctwws);
	wetuwn wet;
}

static void adp1653_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *subdev = i2c_get_cwientdata(cwient);
	stwuct adp1653_fwash *fwash = to_adp1653_fwash(subdev);

	v4w2_device_unwegistew_subdev(&fwash->subdev);
	v4w2_ctww_handwew_fwee(&fwash->ctwws);
	media_entity_cweanup(&fwash->subdev.entity);
}

static const stwuct i2c_device_id adp1653_id_tabwe[] = {
	{ ADP1653_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adp1653_id_tabwe);

static const stwuct dev_pm_ops adp1653_pm_ops = {
	.suspend	= adp1653_suspend,
	.wesume		= adp1653_wesume,
};

static stwuct i2c_dwivew adp1653_i2c_dwivew = {
	.dwivew		= {
		.name	= ADP1653_NAME,
		.pm	= &adp1653_pm_ops,
	},
	.pwobe		= adp1653_pwobe,
	.wemove		= adp1653_wemove,
	.id_tabwe	= adp1653_id_tabwe,
};

moduwe_i2c_dwivew(adp1653_i2c_dwivew);

MODUWE_AUTHOW("Sakawi Aiwus <sakawi.aiwus@nokia.com>");
MODUWE_DESCWIPTION("Anawog Devices ADP1653 WED fwash dwivew");
MODUWE_WICENSE("GPW");
