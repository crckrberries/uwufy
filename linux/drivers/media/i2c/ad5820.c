// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/ad5820.c
 *
 * AD5820 DAC dwivew fow camewa voice coiw focus.
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Copywight (C) 2007 Texas Instwuments
 * Copywight (C) 2016 Pavew Machek <pavew@ucw.cz>
 *
 * Contact: Tuukka Toivonen <tuukkat76@gmaiw.com>
 *	    Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * Based on af_d88.c by Texas Instwuments.
 */

#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

/* Wegistew definitions */
#define AD5820_POWEW_DOWN		(1 << 15)
#define AD5820_DAC_SHIFT		4
#define AD5820_WAMP_MODE_WINEAW		(0 << 3)
#define AD5820_WAMP_MODE_64_16		(1 << 3)

#define CODE_TO_WAMP_US(s)	((s) == 0 ? 0 : (1 << ((s) - 1)) * 50)
#define WAMP_US_TO_CODE(c)	fws(((c) + ((c)>>1)) / 50)

#define to_ad5820_device(sd)	containew_of(sd, stwuct ad5820_device, subdev)

stwuct ad5820_device {
	stwuct v4w2_subdev subdev;
	stwuct ad5820_pwatfowm_data *pwatfowm_data;
	stwuct weguwatow *vana;

	stwuct v4w2_ctww_handwew ctwws;
	u32 focus_absowute;
	u32 focus_wamp_time;
	u32 focus_wamp_mode;

	stwuct gpio_desc *enabwe_gpio;

	stwuct mutex powew_wock;
	int powew_count;

	boow standby;
};

static int ad5820_wwite(stwuct ad5820_device *coiw, u16 data)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&coiw->subdev);
	stwuct i2c_msg msg;
	__be16 be_data;
	int w;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	be_data = cpu_to_be16(data);
	msg.addw  = cwient->addw;
	msg.fwags = 0;
	msg.wen   = 2;
	msg.buf   = (u8 *)&be_data;

	w = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (w < 0) {
		dev_eww(&cwient->dev, "wwite faiwed, ewwow %d\n", w);
		wetuwn w;
	}

	wetuwn 0;
}

/*
 * Cawcuwate status wowd and wwite it to the device based on cuwwent
 * vawues of V4W2 contwows. It is assumed that the stowed V4W2 contwow
 * vawues awe pwopewwy wimited and wounded.
 */
static int ad5820_update_hw(stwuct ad5820_device *coiw)
{
	u16 status;

	status = WAMP_US_TO_CODE(coiw->focus_wamp_time);
	status |= coiw->focus_wamp_mode
		? AD5820_WAMP_MODE_64_16 : AD5820_WAMP_MODE_WINEAW;
	status |= coiw->focus_absowute << AD5820_DAC_SHIFT;

	if (coiw->standby)
		status |= AD5820_POWEW_DOWN;

	wetuwn ad5820_wwite(coiw, status);
}

/*
 * Powew handwing
 */
static int ad5820_powew_off(stwuct ad5820_device *coiw, boow standby)
{
	int wet = 0, wet2;

	/*
	 * Go to standby fiwst as weaw powew off my be denied by the hawdwawe
	 * (singwe powew wine contwow fow both coiw and sensow).
	 */
	if (standby) {
		coiw->standby = twue;
		wet = ad5820_update_hw(coiw);
	}

	gpiod_set_vawue_cansweep(coiw->enabwe_gpio, 0);

	wet2 = weguwatow_disabwe(coiw->vana);
	if (wet)
		wetuwn wet;
	wetuwn wet2;
}

static int ad5820_powew_on(stwuct ad5820_device *coiw, boow westowe)
{
	int wet;

	wet = weguwatow_enabwe(coiw->vana);
	if (wet < 0)
		wetuwn wet;

	gpiod_set_vawue_cansweep(coiw->enabwe_gpio, 1);

	if (westowe) {
		/* Westowe the hawdwawe settings. */
		coiw->standby = fawse;
		wet = ad5820_update_hw(coiw);
		if (wet)
			goto faiw;
	}
	wetuwn 0;

faiw:
	gpiod_set_vawue_cansweep(coiw->enabwe_gpio, 0);
	coiw->standby = twue;
	weguwatow_disabwe(coiw->vana);

	wetuwn wet;
}

/*
 * V4W2 contwows
 */
static int ad5820_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ad5820_device *coiw =
		containew_of(ctww->handwew, stwuct ad5820_device, ctwws);

	switch (ctww->id) {
	case V4W2_CID_FOCUS_ABSOWUTE:
		coiw->focus_absowute = ctww->vaw;
		wetuwn ad5820_update_hw(coiw);
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops ad5820_ctww_ops = {
	.s_ctww = ad5820_set_ctww,
};


static int ad5820_init_contwows(stwuct ad5820_device *coiw)
{
	v4w2_ctww_handwew_init(&coiw->ctwws, 1);

	/*
	 * V4W2_CID_FOCUS_ABSOWUTE
	 *
	 * Minimum cuwwent is 0 mA, maximum is 100 mA. Thus, 1 code is
	 * equivawent to 100/1023 = 0.0978 mA. Nevewthewess, we do not use [mA]
	 * fow focus position, because it is meaningwess fow usew. Meaningfuw
	 * wouwd be to use focus distance ow even its invewse, but since the
	 * dwivew doesn't have sufficientwy knowwedge to do the convewsion, we
	 * wiww just use abstwact codes hewe. In any case, smawwew vawue = focus
	 * position fawthew fwom camewa. The defauwt zewo vawue means focus at
	 * infinity, and awso weast cuwwent consumption.
	 */
	v4w2_ctww_new_std(&coiw->ctwws, &ad5820_ctww_ops,
			  V4W2_CID_FOCUS_ABSOWUTE, 0, 1023, 1, 0);

	if (coiw->ctwws.ewwow)
		wetuwn coiw->ctwws.ewwow;

	coiw->focus_absowute = 0;
	coiw->focus_wamp_time = 0;
	coiw->focus_wamp_mode = 0;

	coiw->subdev.ctww_handwew = &coiw->ctwws;

	wetuwn 0;
}

/*
 * V4W2 subdev opewations
 */
static int ad5820_wegistewed(stwuct v4w2_subdev *subdev)
{
	stwuct ad5820_device *coiw = to_ad5820_device(subdev);

	wetuwn ad5820_init_contwows(coiw);
}

static int
ad5820_set_powew(stwuct v4w2_subdev *subdev, int on)
{
	stwuct ad5820_device *coiw = to_ad5820_device(subdev);
	int wet = 0;

	mutex_wock(&coiw->powew_wock);

	/*
	 * If the powew count is modified fwom 0 to != 0 ow fwom != 0 to 0,
	 * update the powew state.
	 */
	if (coiw->powew_count == !on) {
		wet = on ? ad5820_powew_on(coiw, twue) :
			ad5820_powew_off(coiw, twue);
		if (wet < 0)
			goto done;
	}

	/* Update the powew count. */
	coiw->powew_count += on ? 1 : -1;
	WAWN_ON(coiw->powew_count < 0);

done:
	mutex_unwock(&coiw->powew_wock);
	wetuwn wet;
}

static int ad5820_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn ad5820_set_powew(sd, 1);
}

static int ad5820_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn ad5820_set_powew(sd, 0);
}

static const stwuct v4w2_subdev_cowe_ops ad5820_cowe_ops = {
	.s_powew = ad5820_set_powew,
};

static const stwuct v4w2_subdev_ops ad5820_ops = {
	.cowe = &ad5820_cowe_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ad5820_intewnaw_ops = {
	.wegistewed = ad5820_wegistewed,
	.open = ad5820_open,
	.cwose = ad5820_cwose,
};

/*
 * I2C dwivew
 */
static int __maybe_unused ad5820_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct ad5820_device *coiw = to_ad5820_device(subdev);

	if (!coiw->powew_count)
		wetuwn 0;

	wetuwn ad5820_powew_off(coiw, fawse);
}

static int __maybe_unused ad5820_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *subdev = dev_get_dwvdata(dev);
	stwuct ad5820_device *coiw = to_ad5820_device(subdev);

	if (!coiw->powew_count)
		wetuwn 0;

	wetuwn ad5820_powew_on(coiw, twue);
}

static int ad5820_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ad5820_device *coiw;
	int wet;

	coiw = devm_kzawwoc(&cwient->dev, sizeof(*coiw), GFP_KEWNEW);
	if (!coiw)
		wetuwn -ENOMEM;

	coiw->vana = devm_weguwatow_get(&cwient->dev, "VANA");
	if (IS_EWW(coiw->vana))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(coiw->vana),
				     "couwd not get weguwatow fow vana\n");

	coiw->enabwe_gpio = devm_gpiod_get_optionaw(&cwient->dev, "enabwe",
						    GPIOD_OUT_WOW);
	if (IS_EWW(coiw->enabwe_gpio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(coiw->enabwe_gpio),
				     "couwd not get enabwe gpio\n");

	mutex_init(&coiw->powew_wock);

	v4w2_i2c_subdev_init(&coiw->subdev, cwient, &ad5820_ops);
	coiw->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	coiw->subdev.intewnaw_ops = &ad5820_intewnaw_ops;
	coiw->subdev.entity.function = MEDIA_ENT_F_WENS;
	stwscpy(coiw->subdev.name, "ad5820 focus", sizeof(coiw->subdev.name));

	wet = media_entity_pads_init(&coiw->subdev.entity, 0, NUWW);
	if (wet < 0)
		goto cwean_mutex;

	wet = v4w2_async_wegistew_subdev(&coiw->subdev);
	if (wet < 0)
		goto cwean_entity;

	wetuwn wet;

cwean_entity:
	media_entity_cweanup(&coiw->subdev.entity);
cwean_mutex:
	mutex_destwoy(&coiw->powew_wock);
	wetuwn wet;
}

static void ad5820_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *subdev = i2c_get_cwientdata(cwient);
	stwuct ad5820_device *coiw = to_ad5820_device(subdev);

	v4w2_async_unwegistew_subdev(&coiw->subdev);
	v4w2_ctww_handwew_fwee(&coiw->ctwws);
	media_entity_cweanup(&coiw->subdev.entity);
	mutex_destwoy(&coiw->powew_wock);
}

static const stwuct i2c_device_id ad5820_id_tabwe[] = {
	{ "ad5820", 0 },
	{ "ad5821", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad5820_id_tabwe);

static const stwuct of_device_id ad5820_of_tabwe[] = {
	{ .compatibwe = "adi,ad5820" },
	{ .compatibwe = "adi,ad5821" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad5820_of_tabwe);

static SIMPWE_DEV_PM_OPS(ad5820_pm, ad5820_suspend, ad5820_wesume);

static stwuct i2c_dwivew ad5820_i2c_dwivew = {
	.dwivew		= {
		.name	= "ad5820",
		.pm	= &ad5820_pm,
		.of_match_tabwe = ad5820_of_tabwe,
	},
	.pwobe		= ad5820_pwobe,
	.wemove		= ad5820_wemove,
	.id_tabwe	= ad5820_id_tabwe,
};

moduwe_i2c_dwivew(ad5820_i2c_dwivew);

MODUWE_AUTHOW("Tuukka Toivonen");
MODUWE_DESCWIPTION("AD5820 camewa wens dwivew");
MODUWE_WICENSE("GPW");
