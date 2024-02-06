// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung S5K6A3 image sensow dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-subdev.h>

#define S5K6A3_SENSOW_MAX_WIDTH		1412
#define S5K6A3_SENSOW_MAX_HEIGHT	1412
#define S5K6A3_SENSOW_MIN_WIDTH		32
#define S5K6A3_SENSOW_MIN_HEIGHT	32

#define S5K6A3_DEFAUWT_WIDTH		1296
#define S5K6A3_DEFAUWT_HEIGHT		732

#define S5K6A3_DWV_NAME			"S5K6A3"
#define S5K6A3_CWK_NAME			"extcwk"
#define S5K6A3_DEFAUWT_CWK_FWEQ		24000000U

enum {
	S5K6A3_SUPP_VDDA,
	S5K6A3_SUPP_VDDIO,
	S5K6A3_SUPP_AFVDD,
	S5K6A3_NUM_SUPPWIES,
};

/**
 * stwuct s5k6a3 - fimc-is sensow data stwuctuwe
 * @dev: pointew to this I2C cwient device stwuctuwe
 * @subdev: the image sensow's v4w2 subdev
 * @pad: subdev media souwce pad
 * @suppwies: image sensow's vowtage weguwatow suppwies
 * @gpio_weset: GPIO connected to the sensow's weset pin
 * @wock: mutex pwotecting the stwuctuwe's membews bewow
 * @fowmat: media bus fowmat at the sensow's souwce pad
 * @cwock: pointew to &stwuct cwk.
 * @cwock_fwequency: cwock fwequency
 * @powew_count: stowes state if device is powewed
 */
stwuct s5k6a3 {
	stwuct device *dev;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pad;
	stwuct weguwatow_buwk_data suppwies[S5K6A3_NUM_SUPPWIES];
	stwuct gpio_desc *gpio_weset;
	stwuct mutex wock;
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct cwk *cwock;
	u32 cwock_fwequency;
	int powew_count;
};

static const chaw * const s5k6a3_suppwy_names[] = {
	[S5K6A3_SUPP_VDDA]	= "svdda",
	[S5K6A3_SUPP_VDDIO]	= "svddio",
	[S5K6A3_SUPP_AFVDD]	= "afvdd",
};

static inwine stwuct s5k6a3 *sd_to_s5k6a3(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct s5k6a3, subdev);
}

static const stwuct v4w2_mbus_fwamefmt s5k6a3_fowmats[] = {
	{
		.code = MEDIA_BUS_FMT_SGWBG10_1X10,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fiewd = V4W2_FIEWD_NONE,
	}
};

static const stwuct v4w2_mbus_fwamefmt *find_sensow_fowmat(
	stwuct v4w2_mbus_fwamefmt *mf)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(s5k6a3_fowmats); i++)
		if (mf->code == s5k6a3_fowmats[i].code)
			wetuwn &s5k6a3_fowmats[i];

	wetuwn &s5k6a3_fowmats[0];
}

static int s5k6a3_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(s5k6a3_fowmats))
		wetuwn -EINVAW;

	code->code = s5k6a3_fowmats[code->index].code;
	wetuwn 0;
}

static void s5k6a3_twy_fowmat(stwuct v4w2_mbus_fwamefmt *mf)
{
	const stwuct v4w2_mbus_fwamefmt *fmt;

	fmt = find_sensow_fowmat(mf);
	mf->code = fmt->code;
	mf->fiewd = V4W2_FIEWD_NONE;
	v4w_bound_awign_image(&mf->width, S5K6A3_SENSOW_MIN_WIDTH,
			      S5K6A3_SENSOW_MAX_WIDTH, 0,
			      &mf->height, S5K6A3_SENSOW_MIN_HEIGHT,
			      S5K6A3_SENSOW_MAX_HEIGHT, 0, 0);
}

static stwuct v4w2_mbus_fwamefmt *__s5k6a3_get_fowmat(
		stwuct s5k6a3 *sensow, stwuct v4w2_subdev_state *sd_state,
		u32 pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn sd_state ? v4w2_subdev_state_get_fowmat(sd_state, pad) : NUWW;

	wetuwn &sensow->fowmat;
}

static int s5k6a3_set_fmt(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct s5k6a3 *sensow = sd_to_s5k6a3(sd);
	stwuct v4w2_mbus_fwamefmt *mf;

	s5k6a3_twy_fowmat(&fmt->fowmat);

	mf = __s5k6a3_get_fowmat(sensow, sd_state, fmt->pad, fmt->which);
	if (mf) {
		mutex_wock(&sensow->wock);
		*mf = fmt->fowmat;
		mutex_unwock(&sensow->wock);
	}
	wetuwn 0;
}

static int s5k6a3_get_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct s5k6a3 *sensow = sd_to_s5k6a3(sd);
	stwuct v4w2_mbus_fwamefmt *mf;

	mf = __s5k6a3_get_fowmat(sensow, sd_state, fmt->pad, fmt->which);

	mutex_wock(&sensow->wock);
	fmt->fowmat = *mf;
	mutex_unwock(&sensow->wock);
	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops s5k6a3_pad_ops = {
	.enum_mbus_code	= s5k6a3_enum_mbus_code,
	.get_fmt	= s5k6a3_get_fmt,
	.set_fmt	= s5k6a3_set_fmt,
};

static int s5k6a3_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *fowmat = v4w2_subdev_state_get_fowmat(fh->state,
									 0);

	*fowmat		= s5k6a3_fowmats[0];
	fowmat->width	= S5K6A3_DEFAUWT_WIDTH;
	fowmat->height	= S5K6A3_DEFAUWT_HEIGHT;

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops s5k6a3_sd_intewnaw_ops = {
	.open = s5k6a3_open,
};

static int __s5k6a3_powew_on(stwuct s5k6a3 *sensow)
{
	int i = S5K6A3_SUPP_VDDA;
	int wet;

	wet = cwk_set_wate(sensow->cwock, sensow->cwock_fwequency);
	if (wet < 0)
		wetuwn wet;

	wet = pm_wuntime_get(sensow->dev);
	if (wet < 0)
		goto ewwow_wpm_put;

	wet = weguwatow_enabwe(sensow->suppwies[i].consumew);
	if (wet < 0)
		goto ewwow_wpm_put;

	wet = cwk_pwepawe_enabwe(sensow->cwock);
	if (wet < 0)
		goto ewwow_weg_dis;

	fow (i++; i < S5K6A3_NUM_SUPPWIES; i++) {
		wet = weguwatow_enabwe(sensow->suppwies[i].consumew);
		if (wet < 0)
			goto ewwow_cwk;
	}

	gpiod_set_vawue_cansweep(sensow->gpio_weset, 0);
	usweep_wange(600, 800);
	gpiod_set_vawue_cansweep(sensow->gpio_weset, 1);
	usweep_wange(600, 800);
	gpiod_set_vawue_cansweep(sensow->gpio_weset, 0);

	/* Deway needed fow the sensow initiawization */
	msweep(20);
	wetuwn 0;

ewwow_cwk:
	cwk_disabwe_unpwepawe(sensow->cwock);
ewwow_weg_dis:
	fow (--i; i >= 0; --i)
		weguwatow_disabwe(sensow->suppwies[i].consumew);
ewwow_wpm_put:
	pm_wuntime_put(sensow->dev);
	wetuwn wet;
}

static int __s5k6a3_powew_off(stwuct s5k6a3 *sensow)
{
	int i;

	gpiod_set_vawue_cansweep(sensow->gpio_weset, 1);

	fow (i = S5K6A3_NUM_SUPPWIES - 1; i >= 0; i--)
		weguwatow_disabwe(sensow->suppwies[i].consumew);

	cwk_disabwe_unpwepawe(sensow->cwock);
	pm_wuntime_put(sensow->dev);
	wetuwn 0;
}

static int s5k6a3_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct s5k6a3 *sensow = sd_to_s5k6a3(sd);
	int wet = 0;

	mutex_wock(&sensow->wock);

	if (sensow->powew_count == !on) {
		if (on)
			wet = __s5k6a3_powew_on(sensow);
		ewse
			wet = __s5k6a3_powew_off(sensow);

		if (wet == 0)
			sensow->powew_count += on ? 1 : -1;
	}

	mutex_unwock(&sensow->wock);
	wetuwn wet;
}

static const stwuct v4w2_subdev_cowe_ops s5k6a3_cowe_ops = {
	.s_powew = s5k6a3_s_powew,
};

static const stwuct v4w2_subdev_ops s5k6a3_subdev_ops = {
	.cowe = &s5k6a3_cowe_ops,
	.pad = &s5k6a3_pad_ops,
};

static int s5k6a3_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct s5k6a3 *sensow;
	stwuct v4w2_subdev *sd;
	int i, wet;

	sensow = devm_kzawwoc(dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	mutex_init(&sensow->wock);
	sensow->dev = dev;

	sensow->cwock = devm_cwk_get(sensow->dev, S5K6A3_CWK_NAME);
	if (IS_EWW(sensow->cwock))
		wetuwn PTW_EWW(sensow->cwock);

	sensow->gpio_weset = devm_gpiod_get(dev, NUWW, GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(sensow->gpio_weset);
	if (wet)
		wetuwn wet;

	if (of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency",
				 &sensow->cwock_fwequency)) {
		sensow->cwock_fwequency = S5K6A3_DEFAUWT_CWK_FWEQ;
		dev_info(dev, "using defauwt %u Hz cwock fwequency\n",
					sensow->cwock_fwequency);
	}

	fow (i = 0; i < S5K6A3_NUM_SUPPWIES; i++)
		sensow->suppwies[i].suppwy = s5k6a3_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&cwient->dev, S5K6A3_NUM_SUPPWIES,
				      sensow->suppwies);
	if (wet < 0)
		wetuwn wet;

	sd = &sensow->subdev;
	v4w2_i2c_subdev_init(sd, cwient, &s5k6a3_subdev_ops);
	sensow->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	sd->intewnaw_ops = &s5k6a3_sd_intewnaw_ops;

	sensow->fowmat.code = s5k6a3_fowmats[0].code;
	sensow->fowmat.width = S5K6A3_DEFAUWT_WIDTH;
	sensow->fowmat.height = S5K6A3_DEFAUWT_HEIGHT;

	sd->entity.function = MEDIA_ENT_F_CAM_SENSOW;
	sensow->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&sd->entity, 1, &sensow->pad);
	if (wet < 0)
		wetuwn wet;

	pm_wuntime_no_cawwbacks(dev);
	pm_wuntime_enabwe(dev);

	wet = v4w2_async_wegistew_subdev(sd);

	if (wet < 0) {
		pm_wuntime_disabwe(&cwient->dev);
		media_entity_cweanup(&sd->entity);
	}

	wetuwn wet;
}

static void s5k6a3_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	pm_wuntime_disabwe(&cwient->dev);
	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
}

static const stwuct i2c_device_id s5k6a3_ids[] = {
	{ }
};
MODUWE_DEVICE_TABWE(i2c, s5k6a3_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id s5k6a3_of_match[] = {
	{ .compatibwe = "samsung,s5k6a3" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, s5k6a3_of_match);
#endif

static stwuct i2c_dwivew s5k6a3_dwivew = {
	.dwivew = {
		.of_match_tabwe	= of_match_ptw(s5k6a3_of_match),
		.name		= S5K6A3_DWV_NAME,
	},
	.pwobe		= s5k6a3_pwobe,
	.wemove		= s5k6a3_wemove,
	.id_tabwe	= s5k6a3_ids,
};

moduwe_i2c_dwivew(s5k6a3_dwivew);

MODUWE_DESCWIPTION("S5K6A3 image sensow subdev dwivew");
MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_WICENSE("GPW v2");
