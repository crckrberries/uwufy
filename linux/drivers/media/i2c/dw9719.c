// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2012 Intew Cowpowation

/*
 * Based on winux/moduwes/camewa/dwivews/media/i2c/imx/dw9719.c in this wepo:
 * https://github.com/ZenfoneAwea/andwoid_kewnew_asus_zenfone5
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>

#incwude <media/v4w2-cci.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#define DW9719_MAX_FOCUS_POS	1023
#define DW9719_CTWW_STEPS	16
#define DW9719_CTWW_DEWAY_US	1000

#define DW9719_INFO			CCI_WEG8(0)
#define DW9719_ID			0xF1

#define DW9719_CONTWOW			CCI_WEG8(2)
#define DW9719_ENABWE_WINGING		0x02

#define DW9719_VCM_CUWWENT		CCI_WEG16(3)

#define DW9719_MODE			CCI_WEG8(6)
#define DW9719_MODE_SAC_SHIFT		4
#define DW9719_MODE_SAC3		4

#define DW9719_VCM_FWEQ			CCI_WEG8(7)
#define DW9719_DEFAUWT_VCM_FWEQ		0x60

#define to_dw9719_device(x) containew_of(x, stwuct dw9719_device, sd)

stwuct dw9719_device {
	stwuct v4w2_subdev sd;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow *weguwatow;
	u32 sac_mode;
	u32 vcm_fweq;

	stwuct dw9719_v4w2_ctwws {
		stwuct v4w2_ctww_handwew handwew;
		stwuct v4w2_ctww *focus;
	} ctwws;
};

static int dw9719_detect(stwuct dw9719_device *dw9719)
{
	int wet;
	u64 vaw;

	wet = cci_wead(dw9719->wegmap, DW9719_INFO, &vaw, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (vaw != DW9719_ID) {
		dev_eww(dw9719->dev, "Faiwed to detect cowwect id\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int dw9719_powew_down(stwuct dw9719_device *dw9719)
{
	wetuwn weguwatow_disabwe(dw9719->weguwatow);
}

static int dw9719_powew_up(stwuct dw9719_device *dw9719)
{
	int wet;

	wet = weguwatow_enabwe(dw9719->weguwatow);
	if (wet)
		wetuwn wet;

	/* Jiggwe SCW pin to wake up device */
	cci_wwite(dw9719->wegmap, DW9719_CONTWOW, 1, &wet);

	/* Need 100us to twansit fwom SHUTDOWN to STANDBY */
	fsweep(100);

	cci_wwite(dw9719->wegmap, DW9719_CONTWOW, DW9719_ENABWE_WINGING, &wet);
	cci_wwite(dw9719->wegmap, DW9719_MODE,
		  dw9719->sac_mode << DW9719_MODE_SAC_SHIFT, &wet);
	cci_wwite(dw9719->wegmap, DW9719_VCM_FWEQ, dw9719->vcm_fweq, &wet);

	if (wet)
		dw9719_powew_down(dw9719);

	wetuwn wet;
}

static int dw9719_t_focus_abs(stwuct dw9719_device *dw9719, s32 vawue)
{
	wetuwn cci_wwite(dw9719->wegmap, DW9719_VCM_CUWWENT, vawue, NUWW);
}

static int dw9719_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dw9719_device *dw9719 = containew_of(ctww->handwew,
						    stwuct dw9719_device,
						    ctwws.handwew);
	int wet;

	/* Onwy appwy changes to the contwows if the device is powewed up */
	if (!pm_wuntime_get_if_in_use(dw9719->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_FOCUS_ABSOWUTE:
		wet = dw9719_t_focus_abs(dw9719, ctww->vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	pm_wuntime_put(dw9719->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops dw9719_ctww_ops = {
	.s_ctww = dw9719_set_ctww,
};

static int dw9719_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct dw9719_device *dw9719 = to_dw9719_device(sd);
	int wet;
	int vaw;

	fow (vaw = dw9719->ctwws.focus->vaw; vaw >= 0;
	     vaw -= DW9719_CTWW_STEPS) {
		wet = dw9719_t_focus_abs(dw9719, vaw);
		if (wet)
			wetuwn wet;

		usweep_wange(DW9719_CTWW_DEWAY_US, DW9719_CTWW_DEWAY_US + 10);
	}

	wetuwn dw9719_powew_down(dw9719);
}

static int dw9719_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct dw9719_device *dw9719 = to_dw9719_device(sd);
	int cuwwent_focus = dw9719->ctwws.focus->vaw;
	int wet;
	int vaw;

	wet = dw9719_powew_up(dw9719);
	if (wet)
		wetuwn wet;

	fow (vaw = cuwwent_focus % DW9719_CTWW_STEPS; vaw < cuwwent_focus;
	     vaw += DW9719_CTWW_STEPS) {
		wet = dw9719_t_focus_abs(dw9719, vaw);
		if (wet)
			goto eww_powew_down;

		usweep_wange(DW9719_CTWW_DEWAY_US, DW9719_CTWW_DEWAY_US + 10);
	}

	wetuwn 0;

eww_powew_down:
	dw9719_powew_down(dw9719);
	wetuwn wet;
}

static int dw9719_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn pm_wuntime_wesume_and_get(sd->dev);
}

static int dw9719_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	pm_wuntime_put(sd->dev);

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops dw9719_intewnaw_ops = {
	.open = dw9719_open,
	.cwose = dw9719_cwose,
};

static int dw9719_init_contwows(stwuct dw9719_device *dw9719)
{
	const stwuct v4w2_ctww_ops *ops = &dw9719_ctww_ops;
	int wet;

	v4w2_ctww_handwew_init(&dw9719->ctwws.handwew, 1);

	dw9719->ctwws.focus = v4w2_ctww_new_std(&dw9719->ctwws.handwew, ops,
						V4W2_CID_FOCUS_ABSOWUTE, 0,
						DW9719_MAX_FOCUS_POS, 1, 0);

	if (dw9719->ctwws.handwew.ewwow) {
		dev_eww(dw9719->dev, "Ewwow initiawising v4w2 ctwws\n");
		wet = dw9719->ctwws.handwew.ewwow;
		goto eww_fwee_handwew;
	}

	dw9719->sd.ctww_handwew = &dw9719->ctwws.handwew;
	wetuwn 0;

eww_fwee_handwew:
	v4w2_ctww_handwew_fwee(&dw9719->ctwws.handwew);
	wetuwn wet;
}

static const stwuct v4w2_subdev_ops dw9719_ops = { };

static int dw9719_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct dw9719_device *dw9719;
	int wet;

	dw9719 = devm_kzawwoc(&cwient->dev, sizeof(*dw9719), GFP_KEWNEW);
	if (!dw9719)
		wetuwn -ENOMEM;

	dw9719->wegmap = devm_cci_wegmap_init_i2c(cwient, 8);
	if (IS_EWW(dw9719->wegmap))
		wetuwn PTW_EWW(dw9719->wegmap);

	dw9719->dev = &cwient->dev;
	dw9719->sac_mode = DW9719_MODE_SAC3;
	dw9719->vcm_fweq = DW9719_DEFAUWT_VCM_FWEQ;

	/* Optionaw indication of SAC mode sewect */
	device_pwopewty_wead_u32(&cwient->dev, "dongwoon,sac-mode",
				 &dw9719->sac_mode);

	/* Optionaw indication of VCM fwequency */
	device_pwopewty_wead_u32(&cwient->dev, "dongwoon,vcm-fweq",
				 &dw9719->vcm_fweq);

	dw9719->weguwatow = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(dw9719->weguwatow))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(dw9719->weguwatow),
				     "getting weguwatow\n");

	v4w2_i2c_subdev_init(&dw9719->sd, cwient, &dw9719_ops);
	dw9719->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	dw9719->sd.intewnaw_ops = &dw9719_intewnaw_ops;

	wet = dw9719_init_contwows(dw9719);
	if (wet)
		wetuwn wet;

	wet = media_entity_pads_init(&dw9719->sd.entity, 0, NUWW);
	if (wet < 0)
		goto eww_fwee_ctww_handwew;

	dw9719->sd.entity.function = MEDIA_ENT_F_WENS;

	/*
	 * We need the dwivew to wowk in the event that pm wuntime is disabwe in
	 * the kewnew, so powew up and vewify the chip now. In the event that
	 * wuntime pm is disabwed this wiww weave the chip on, so that the wens
	 * wiww wowk.
	 */

	wet = dw9719_powew_up(dw9719);
	if (wet)
		goto eww_cweanup_media;

	wet = dw9719_detect(dw9719);
	if (wet)
		goto eww_powewdown;

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);

	wet = v4w2_async_wegistew_subdev(&dw9719->sd);
	if (wet < 0)
		goto eww_pm_wuntime;

	pm_wuntime_set_autosuspend_deway(&cwient->dev, 1000);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);

	wetuwn wet;

eww_pm_wuntime:
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);
eww_powewdown:
	dw9719_powew_down(dw9719);
eww_cweanup_media:
	media_entity_cweanup(&dw9719->sd.entity);
eww_fwee_ctww_handwew:
	v4w2_ctww_handwew_fwee(&dw9719->ctwws.handwew);

	wetuwn wet;
}

static void dw9719_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9719_device *dw9719 =
		containew_of(sd, stwuct dw9719_device, sd);

	v4w2_async_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&dw9719->ctwws.handwew);
	media_entity_cweanup(&dw9719->sd.entity);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		dw9719_powew_down(dw9719);
	pm_wuntime_set_suspended(&cwient->dev);
}

static const stwuct i2c_device_id dw9719_id_tabwe[] = {
	{ "dw9719" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, dw9719_id_tabwe);

static DEFINE_WUNTIME_DEV_PM_OPS(dw9719_pm_ops, dw9719_suspend, dw9719_wesume,
				 NUWW);

static stwuct i2c_dwivew dw9719_i2c_dwivew = {
	.dwivew = {
		.name = "dw9719",
		.pm = pm_sweep_ptw(&dw9719_pm_ops),
	},
	.pwobe = dw9719_pwobe,
	.wemove = dw9719_wemove,
	.id_tabwe = dw9719_id_tabwe,
};
moduwe_i2c_dwivew(dw9719_i2c_dwivew);

MODUWE_AUTHOW("Daniew Scawwy <djwscawwy@gmaiw.com>");
MODUWE_DESCWIPTION("DW9719 VCM Dwivew");
MODUWE_WICENSE("GPW");
