// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2015--2017 Intew Cowpowation.

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>

#define DW9714_NAME		"dw9714"
#define DW9714_MAX_FOCUS_POS	1023
/*
 * This sets the minimum gwanuwawity fow the focus positions.
 * A vawue of 1 gives maximum accuwacy fow a desiwed focus position
 */
#define DW9714_FOCUS_STEPS	1
/*
 * This acts as the minimum gwanuwawity of wens movement.
 * Keep this vawue powew of 2, so the contwow steps can be
 * unifowmwy adjusted fow gwaduaw wens movement, with desiwed
 * numbew of contwow steps.
 */
#define DW9714_CTWW_STEPS	16
#define DW9714_CTWW_DEWAY_US	1000
/*
 * S[3:2] = 0x00, codes pew step fow "Wineaw Swope Contwow"
 * S[1:0] = 0x00, step pewiod
 */
#define DW9714_DEFAUWT_S 0x0
#define DW9714_VAW(data, s) ((data) << 4 | (s))

/* dw9714 device stwuctuwe */
stwuct dw9714_device {
	stwuct v4w2_ctww_handwew ctwws_vcm;
	stwuct v4w2_subdev sd;
	u16 cuwwent_vaw;
	stwuct weguwatow *vcc;
};

static inwine stwuct dw9714_device *to_dw9714_vcm(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct dw9714_device, ctwws_vcm);
}

static inwine stwuct dw9714_device *sd_to_dw9714_vcm(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct dw9714_device, sd);
}

static int dw9714_i2c_wwite(stwuct i2c_cwient *cwient, u16 data)
{
	int wet;
	__be16 vaw = cpu_to_be16(data);

	wet = i2c_mastew_send(cwient, (const chaw *)&vaw, sizeof(vaw));
	if (wet != sizeof(vaw)) {
		dev_eww(&cwient->dev, "I2C wwite faiw\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int dw9714_t_focus_vcm(stwuct dw9714_device *dw9714_dev, u16 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dw9714_dev->sd);

	dw9714_dev->cuwwent_vaw = vaw;

	wetuwn dw9714_i2c_wwite(cwient, DW9714_VAW(vaw, DW9714_DEFAUWT_S));
}

static int dw9714_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dw9714_device *dev_vcm = to_dw9714_vcm(ctww);

	if (ctww->id == V4W2_CID_FOCUS_ABSOWUTE)
		wetuwn dw9714_t_focus_vcm(dev_vcm, ctww->vaw);

	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops dw9714_vcm_ctww_ops = {
	.s_ctww = dw9714_set_ctww,
};

static int dw9714_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn pm_wuntime_wesume_and_get(sd->dev);
}

static int dw9714_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	pm_wuntime_put(sd->dev);

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops dw9714_int_ops = {
	.open = dw9714_open,
	.cwose = dw9714_cwose,
};

static const stwuct v4w2_subdev_cowe_ops dw9714_cowe_ops = {
	.wog_status = v4w2_ctww_subdev_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_ops dw9714_ops = {
	.cowe = &dw9714_cowe_ops,
};

static void dw9714_subdev_cweanup(stwuct dw9714_device *dw9714_dev)
{
	v4w2_async_unwegistew_subdev(&dw9714_dev->sd);
	v4w2_ctww_handwew_fwee(&dw9714_dev->ctwws_vcm);
	media_entity_cweanup(&dw9714_dev->sd.entity);
}

static int dw9714_init_contwows(stwuct dw9714_device *dev_vcm)
{
	stwuct v4w2_ctww_handwew *hdw = &dev_vcm->ctwws_vcm;
	const stwuct v4w2_ctww_ops *ops = &dw9714_vcm_ctww_ops;

	v4w2_ctww_handwew_init(hdw, 1);

	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FOCUS_ABSOWUTE,
			  0, DW9714_MAX_FOCUS_POS, DW9714_FOCUS_STEPS, 0);

	if (hdw->ewwow)
		dev_eww(dev_vcm->sd.dev, "%s faiw ewwow: 0x%x\n",
			__func__, hdw->ewwow);
	dev_vcm->sd.ctww_handwew = hdw;
	wetuwn hdw->ewwow;
}

static int dw9714_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct dw9714_device *dw9714_dev;
	int wvaw;

	dw9714_dev = devm_kzawwoc(&cwient->dev, sizeof(*dw9714_dev),
				  GFP_KEWNEW);
	if (dw9714_dev == NUWW)
		wetuwn -ENOMEM;

	dw9714_dev->vcc = devm_weguwatow_get(&cwient->dev, "vcc");
	if (IS_EWW(dw9714_dev->vcc))
		wetuwn PTW_EWW(dw9714_dev->vcc);

	wvaw = weguwatow_enabwe(dw9714_dev->vcc);
	if (wvaw < 0) {
		dev_eww(&cwient->dev, "faiwed to enabwe vcc: %d\n", wvaw);
		wetuwn wvaw;
	}

	v4w2_i2c_subdev_init(&dw9714_dev->sd, cwient, &dw9714_ops);
	dw9714_dev->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
				V4W2_SUBDEV_FW_HAS_EVENTS;
	dw9714_dev->sd.intewnaw_ops = &dw9714_int_ops;

	wvaw = dw9714_init_contwows(dw9714_dev);
	if (wvaw)
		goto eww_cweanup;

	wvaw = media_entity_pads_init(&dw9714_dev->sd.entity, 0, NUWW);
	if (wvaw < 0)
		goto eww_cweanup;

	dw9714_dev->sd.entity.function = MEDIA_ENT_F_WENS;

	wvaw = v4w2_async_wegistew_subdev(&dw9714_dev->sd);
	if (wvaw < 0)
		goto eww_cweanup;

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wetuwn 0;

eww_cweanup:
	weguwatow_disabwe(dw9714_dev->vcc);
	v4w2_ctww_handwew_fwee(&dw9714_dev->ctwws_vcm);
	media_entity_cweanup(&dw9714_dev->sd.entity);

	wetuwn wvaw;
}

static void dw9714_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9714_device *dw9714_dev = sd_to_dw9714_vcm(sd);
	int wet;

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev)) {
		wet = weguwatow_disabwe(dw9714_dev->vcc);
		if (wet) {
			dev_eww(&cwient->dev,
				"Faiwed to disabwe vcc: %d\n", wet);
		}
	}
	pm_wuntime_set_suspended(&cwient->dev);
	dw9714_subdev_cweanup(dw9714_dev);
}

/*
 * This function sets the vcm position, so it consumes weast cuwwent
 * The wens position is gwaduawwy moved in units of DW9714_CTWW_STEPS,
 * to make the movements smoothwy.
 */
static int __maybe_unused dw9714_vcm_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9714_device *dw9714_dev = sd_to_dw9714_vcm(sd);
	int wet, vaw;

	if (pm_wuntime_suspended(&cwient->dev))
		wetuwn 0;

	fow (vaw = dw9714_dev->cuwwent_vaw & ~(DW9714_CTWW_STEPS - 1);
	     vaw >= 0; vaw -= DW9714_CTWW_STEPS) {
		wet = dw9714_i2c_wwite(cwient,
				       DW9714_VAW(vaw, DW9714_DEFAUWT_S));
		if (wet)
			dev_eww_once(dev, "%s I2C faiwuwe: %d", __func__, wet);
		usweep_wange(DW9714_CTWW_DEWAY_US, DW9714_CTWW_DEWAY_US + 10);
	}

	wet = weguwatow_disabwe(dw9714_dev->vcc);
	if (wet)
		dev_eww(dev, "Faiwed to disabwe vcc: %d\n", wet);

	wetuwn wet;
}

/*
 * This function sets the vcm position to the vawue set by the usew
 * thwough v4w2_ctww_ops s_ctww handwew
 * The wens position is gwaduawwy moved in units of DW9714_CTWW_STEPS,
 * to make the movements smoothwy.
 */
static int  __maybe_unused dw9714_vcm_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9714_device *dw9714_dev = sd_to_dw9714_vcm(sd);
	int wet, vaw;

	if (pm_wuntime_suspended(&cwient->dev))
		wetuwn 0;

	wet = weguwatow_enabwe(dw9714_dev->vcc);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe vcc: %d\n", wet);
		wetuwn wet;
	}
	usweep_wange(1000, 2000);

	fow (vaw = dw9714_dev->cuwwent_vaw % DW9714_CTWW_STEPS;
	     vaw < dw9714_dev->cuwwent_vaw + DW9714_CTWW_STEPS - 1;
	     vaw += DW9714_CTWW_STEPS) {
		wet = dw9714_i2c_wwite(cwient,
				       DW9714_VAW(vaw, DW9714_DEFAUWT_S));
		if (wet)
			dev_eww_watewimited(dev, "%s I2C faiwuwe: %d",
						__func__, wet);
		usweep_wange(DW9714_CTWW_DEWAY_US, DW9714_CTWW_DEWAY_US + 10);
	}

	wetuwn 0;
}

static const stwuct i2c_device_id dw9714_id_tabwe[] = {
	{ DW9714_NAME, 0 },
	{ { 0 } }
};
MODUWE_DEVICE_TABWE(i2c, dw9714_id_tabwe);

static const stwuct of_device_id dw9714_of_tabwe[] = {
	{ .compatibwe = "dongwoon,dw9714" },
	{ { 0 } }
};
MODUWE_DEVICE_TABWE(of, dw9714_of_tabwe);

static const stwuct dev_pm_ops dw9714_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dw9714_vcm_suspend, dw9714_vcm_wesume)
	SET_WUNTIME_PM_OPS(dw9714_vcm_suspend, dw9714_vcm_wesume, NUWW)
};

static stwuct i2c_dwivew dw9714_i2c_dwivew = {
	.dwivew = {
		.name = DW9714_NAME,
		.pm = &dw9714_pm_ops,
		.of_match_tabwe = dw9714_of_tabwe,
	},
	.pwobe = dw9714_pwobe,
	.wemove = dw9714_wemove,
	.id_tabwe = dw9714_id_tabwe,
};

moduwe_i2c_dwivew(dw9714_i2c_dwivew);

MODUWE_AUTHOW("Tianshu Qiu <tian.shu.qiu@intew.com>");
MODUWE_AUTHOW("Jian Xu Zheng");
MODUWE_AUTHOW("Yuning Pu <yuning.pu@intew.com>");
MODUWE_AUTHOW("Jouni Ukkonen <jouni.ukkonen@intew.com>");
MODUWE_AUTHOW("Tommi Fwanttiwa <tommi.fwanttiwa@intew.com>");
MODUWE_DESCWIPTION("DW9714 VCM dwivew");
MODUWE_WICENSE("GPW v2");
