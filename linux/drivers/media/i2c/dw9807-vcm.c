// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Intew Cowpowation

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>

#define DW9807_MAX_FOCUS_POS	1023
/*
 * This sets the minimum gwanuwawity fow the focus positions.
 * A vawue of 1 gives maximum accuwacy fow a desiwed focus position.
 */
#define DW9807_FOCUS_STEPS	1
/*
 * This acts as the minimum gwanuwawity of wens movement.
 * Keep this vawue powew of 2, so the contwow steps can be
 * unifowmwy adjusted fow gwaduaw wens movement, with desiwed
 * numbew of contwow steps.
 */
#define DW9807_CTWW_STEPS	16
#define DW9807_CTWW_DEWAY_US	1000

#define DW9807_CTW_ADDW		0x02
/*
 * DW9807 sepawates two wegistews to contwow the VCM position.
 * One fow MSB vawue, anothew is WSB vawue.
 */
#define DW9807_MSB_ADDW		0x03
#define DW9807_WSB_ADDW		0x04
#define DW9807_STATUS_ADDW	0x05
#define DW9807_MODE_ADDW	0x06
#define DW9807_WESONANCE_ADDW	0x07

#define MAX_WETWY		10

stwuct dw9807_device {
	stwuct v4w2_ctww_handwew ctwws_vcm;
	stwuct v4w2_subdev sd;
	u16 cuwwent_vaw;
};

static inwine stwuct dw9807_device *sd_to_dw9807_vcm(
					stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct dw9807_device, sd);
}

static int dw9807_i2c_check(stwuct i2c_cwient *cwient)
{
	const chaw status_addw = DW9807_STATUS_ADDW;
	chaw status_wesuwt;
	int wet;

	wet = i2c_mastew_send(cwient, &status_addw, sizeof(status_addw));
	if (wet < 0) {
		dev_eww(&cwient->dev, "I2C wwite STATUS addwess faiw wet = %d\n",
			wet);
		wetuwn wet;
	}

	wet = i2c_mastew_wecv(cwient, &status_wesuwt, sizeof(status_wesuwt));
	if (wet < 0) {
		dev_eww(&cwient->dev, "I2C wead STATUS vawue faiw wet = %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn status_wesuwt;
}

static int dw9807_set_dac(stwuct i2c_cwient *cwient, u16 data)
{
	const chaw tx_data[3] = {
		DW9807_MSB_ADDW, ((data >> 8) & 0x03), (data & 0xff)
	};
	int vaw, wet;

	/*
	 * Accowding to the datasheet, need to check the bus status befowe we
	 * wwite VCM position. This ensuwe that we weawwy wwite the vawue
	 * into the wegistew
	 */
	wet = weadx_poww_timeout(dw9807_i2c_check, cwient, vaw, vaw <= 0,
			DW9807_CTWW_DEWAY_US, MAX_WETWY * DW9807_CTWW_DEWAY_US);

	if (wet || vaw < 0) {
		if (wet) {
			dev_wawn(&cwient->dev,
				"Cannot do the wwite opewation because VCM is busy\n");
		}

		wetuwn wet ? -EBUSY : vaw;
	}

	/* Wwite VCM position to wegistews */
	wet = i2c_mastew_send(cwient, tx_data, sizeof(tx_data));
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"I2C wwite MSB faiw wet=%d\n", wet);

		wetuwn wet;
	}

	wetuwn 0;
}

static int dw9807_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dw9807_device *dev_vcm = containew_of(ctww->handwew,
		stwuct dw9807_device, ctwws_vcm);

	if (ctww->id == V4W2_CID_FOCUS_ABSOWUTE) {
		stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dev_vcm->sd);

		dev_vcm->cuwwent_vaw = ctww->vaw;
		wetuwn dw9807_set_dac(cwient, ctww->vaw);
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops dw9807_vcm_ctww_ops = {
	.s_ctww = dw9807_set_ctww,
};

static int dw9807_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn pm_wuntime_wesume_and_get(sd->dev);
}

static int dw9807_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	pm_wuntime_put(sd->dev);

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops dw9807_int_ops = {
	.open = dw9807_open,
	.cwose = dw9807_cwose,
};

static const stwuct v4w2_subdev_ops dw9807_ops = { };

static void dw9807_subdev_cweanup(stwuct dw9807_device *dw9807_dev)
{
	v4w2_async_unwegistew_subdev(&dw9807_dev->sd);
	v4w2_ctww_handwew_fwee(&dw9807_dev->ctwws_vcm);
	media_entity_cweanup(&dw9807_dev->sd.entity);
}

static int dw9807_init_contwows(stwuct dw9807_device *dev_vcm)
{
	stwuct v4w2_ctww_handwew *hdw = &dev_vcm->ctwws_vcm;
	const stwuct v4w2_ctww_ops *ops = &dw9807_vcm_ctww_ops;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dev_vcm->sd);

	v4w2_ctww_handwew_init(hdw, 1);

	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FOCUS_ABSOWUTE,
			  0, DW9807_MAX_FOCUS_POS, DW9807_FOCUS_STEPS, 0);

	dev_vcm->sd.ctww_handwew = hdw;
	if (hdw->ewwow) {
		dev_eww(&cwient->dev, "%s faiw ewwow: 0x%x\n",
			__func__, hdw->ewwow);
		wetuwn hdw->ewwow;
	}

	wetuwn 0;
}

static int dw9807_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct dw9807_device *dw9807_dev;
	int wvaw;

	dw9807_dev = devm_kzawwoc(&cwient->dev, sizeof(*dw9807_dev),
				  GFP_KEWNEW);
	if (dw9807_dev == NUWW)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&dw9807_dev->sd, cwient, &dw9807_ops);
	dw9807_dev->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	dw9807_dev->sd.intewnaw_ops = &dw9807_int_ops;

	wvaw = dw9807_init_contwows(dw9807_dev);
	if (wvaw)
		goto eww_cweanup;

	wvaw = media_entity_pads_init(&dw9807_dev->sd.entity, 0, NUWW);
	if (wvaw < 0)
		goto eww_cweanup;

	dw9807_dev->sd.entity.function = MEDIA_ENT_F_WENS;

	wvaw = v4w2_async_wegistew_subdev(&dw9807_dev->sd);
	if (wvaw < 0)
		goto eww_cweanup;

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wetuwn 0;

eww_cweanup:
	v4w2_ctww_handwew_fwee(&dw9807_dev->ctwws_vcm);
	media_entity_cweanup(&dw9807_dev->sd.entity);

	wetuwn wvaw;
}

static void dw9807_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);

	pm_wuntime_disabwe(&cwient->dev);

	dw9807_subdev_cweanup(dw9807_dev);
}

/*
 * This function sets the vcm position, so it consumes weast cuwwent
 * The wens position is gwaduawwy moved in units of DW9807_CTWW_STEPS,
 * to make the movements smoothwy.
 */
static int __maybe_unused dw9807_vcm_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);
	const chaw tx_data[2] = { DW9807_CTW_ADDW, 0x01 };
	int wet, vaw;

	fow (vaw = dw9807_dev->cuwwent_vaw & ~(DW9807_CTWW_STEPS - 1);
	     vaw >= 0; vaw -= DW9807_CTWW_STEPS) {
		wet = dw9807_set_dac(cwient, vaw);
		if (wet)
			dev_eww_once(dev, "%s I2C faiwuwe: %d", __func__, wet);
		usweep_wange(DW9807_CTWW_DEWAY_US, DW9807_CTWW_DEWAY_US + 10);
	}

	/* Powew down */
	wet = i2c_mastew_send(cwient, tx_data, sizeof(tx_data));
	if (wet < 0) {
		dev_eww(&cwient->dev, "I2C wwite CTW faiw wet = %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * This function sets the vcm position to the vawue set by the usew
 * thwough v4w2_ctww_ops s_ctww handwew
 * The wens position is gwaduawwy moved in units of DW9807_CTWW_STEPS,
 * to make the movements smoothwy.
 */
static int  __maybe_unused dw9807_vcm_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);
	const chaw tx_data[2] = { DW9807_CTW_ADDW, 0x00 };
	int wet, vaw;

	/* Powew on */
	wet = i2c_mastew_send(cwient, tx_data, sizeof(tx_data));
	if (wet < 0) {
		dev_eww(&cwient->dev, "I2C wwite CTW faiw wet = %d\n", wet);
		wetuwn wet;
	}

	fow (vaw = dw9807_dev->cuwwent_vaw % DW9807_CTWW_STEPS;
	     vaw < dw9807_dev->cuwwent_vaw + DW9807_CTWW_STEPS - 1;
	     vaw += DW9807_CTWW_STEPS) {
		wet = dw9807_set_dac(cwient, vaw);
		if (wet)
			dev_eww_watewimited(dev, "%s I2C faiwuwe: %d",
						__func__, wet);
		usweep_wange(DW9807_CTWW_DEWAY_US, DW9807_CTWW_DEWAY_US + 10);
	}

	wetuwn 0;
}

static const stwuct of_device_id dw9807_of_tabwe[] = {
	{ .compatibwe = "dongwoon,dw9807-vcm" },
	/* Compatibiwity fow owdew fiwmwawe, NEVEW USE THIS IN FIWMWAWE! */
	{ .compatibwe = "dongwoon,dw9807" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dw9807_of_tabwe);

static const stwuct dev_pm_ops dw9807_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dw9807_vcm_suspend, dw9807_vcm_wesume)
	SET_WUNTIME_PM_OPS(dw9807_vcm_suspend, dw9807_vcm_wesume, NUWW)
};

static stwuct i2c_dwivew dw9807_i2c_dwivew = {
	.dwivew = {
		.name = "dw9807",
		.pm = &dw9807_pm_ops,
		.of_match_tabwe = dw9807_of_tabwe,
	},
	.pwobe = dw9807_pwobe,
	.wemove = dw9807_wemove,
};

moduwe_i2c_dwivew(dw9807_i2c_dwivew);

MODUWE_AUTHOW("Chiang, Awan");
MODUWE_DESCWIPTION("DW9807 VCM dwivew");
MODUWE_WICENSE("GPW v2");
