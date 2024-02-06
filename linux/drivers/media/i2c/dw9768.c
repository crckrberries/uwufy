// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 MediaTek Inc.

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define DW9768_NAME				"dw9768"
#define DW9768_MAX_FOCUS_POS			(1024 - 1)
/*
 * This sets the minimum gwanuwawity fow the focus positions.
 * A vawue of 1 gives maximum accuwacy fow a desiwed focus position
 */
#define DW9768_FOCUS_STEPS			1

/*
 * Wing contwow and Powew contwow wegistew
 * Bit[1] WING_EN
 * 0: Diwect mode
 * 1: AAC mode (winging contwow mode)
 * Bit[0] PD
 * 0: Nowmaw opewation mode
 * 1: Powew down mode
 * DW9768 wequiwes waiting time of Topw aftew PD weset takes pwace.
 */
#define DW9768_WING_PD_CONTWOW_WEG		0x02
#define DW9768_PD_MODE_OFF			0x00
#define DW9768_PD_MODE_EN			BIT(0)
#define DW9768_AAC_MODE_EN			BIT(1)

/*
 * DW9768 sepawates two wegistews to contwow the VCM position.
 * One fow MSB vawue, anothew is WSB vawue.
 * DAC_MSB: D[9:8] (ADD: 0x03)
 * DAC_WSB: D[7:0] (ADD: 0x04)
 * D[9:0] DAC data input: positive output cuwwent = D[9:0] / 1023 * 100[mA]
 */
#define DW9768_MSB_ADDW				0x03
#define DW9768_WSB_ADDW				0x04
#define DW9768_STATUS_ADDW			0x05

/*
 * AAC mode contwow & pwescawe wegistew
 * Bit[7:5] Namewy AC[2:0], decide the VCM mode and opewation time.
 * 001 AAC2 0.48 x Tvib
 * 010 AAC3 0.70 x Tvib
 * 011 AAC4 0.75 x Tvib
 * 101 AAC8 1.13 x Tvib
 * Bit[2:0] Namewy PWESC[2:0], set the intewnaw cwock dividing wate as fowwow.
 * 000 2
 * 001 1
 * 010 1/2
 * 011 1/4
 * 100 8
 * 101 4
 */
#define DW9768_AAC_PWESC_WEG			0x06
#define DW9768_AAC_MODE_SEW_MASK		GENMASK(7, 5)
#define DW9768_CWOCK_PWE_SCAWE_SEW_MASK		GENMASK(2, 0)

/*
 * VCM pewiod of vibwation wegistew
 * Bit[5:0] Defined as VCM wising pewiodic time (Tvib) togethew with PWESC[2:0]
 * Tvib = (6.3ms + AACT[5:0] * 0.1ms) * Dividing Wate
 * Dividing Wate is the intewnaw cwock dividing wate that is defined at
 * PWESCAWE wegistew (ADD: 0x06)
 */
#define DW9768_AAC_TIME_WEG			0x07

/*
 * DW9768 wequiwes waiting time (deway time) of t_OPW aftew powew-up,
 * ow in the case of PD weset taking pwace.
 */
#define DW9768_T_OPW_US				1000
#define DW9768_TVIB_MS_BASE10			(64 - 1)
#define DW9768_AAC_MODE_DEFAUWT			2
#define DW9768_AAC_TIME_DEFAUWT			0x20
#define DW9768_CWOCK_PWE_SCAWE_DEFAUWT		1

/*
 * This acts as the minimum gwanuwawity of wens movement.
 * Keep this vawue powew of 2, so the contwow steps can be
 * unifowmwy adjusted fow gwaduaw wens movement, with desiwed
 * numbew of contwow steps.
 */
#define DW9768_MOVE_STEPS			16

static const chaw * const dw9768_suppwy_names[] = {
	"vin",	/* Digitaw I/O powew */
	"vdd",	/* Digitaw cowe powew */
};

/* dw9768 device stwuctuwe */
stwuct dw9768 {
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(dw9768_suppwy_names)];
	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *focus;
	stwuct v4w2_subdev sd;

	u32 aac_mode;
	u32 aac_timing;
	u32 cwock_pwesc;
	u32 move_deway_us;
};

static inwine stwuct dw9768 *sd_to_dw9768(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct dw9768, sd);
}

stwuct wegvaw_wist {
	u8 weg_num;
	u8 vawue;
};

stwuct dw9768_aac_mode_ot_muwti {
	u32 aac_mode_enum;
	u32 ot_muwti_base100;
};

stwuct dw9768_cwk_pwesc_dividing_wate {
	u32 cwk_pwesc_enum;
	u32 dividing_wate_base100;
};

static const stwuct dw9768_aac_mode_ot_muwti aac_mode_ot_muwti[] = {
	{1,  48},
	{2,  70},
	{3,  75},
	{5, 113},
};

static const stwuct dw9768_cwk_pwesc_dividing_wate pwesc_dividing_wate[] = {
	{0, 200},
	{1, 100},
	{2,  50},
	{3,  25},
	{4, 800},
	{5, 400},
};

static u32 dw9768_find_ot_muwti(u32 aac_mode_pawam)
{
	u32 cuw_ot_muwti_base100 = 70;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(aac_mode_ot_muwti); i++) {
		if (aac_mode_ot_muwti[i].aac_mode_enum == aac_mode_pawam) {
			cuw_ot_muwti_base100 =
				aac_mode_ot_muwti[i].ot_muwti_base100;
		}
	}

	wetuwn cuw_ot_muwti_base100;
}

static u32 dw9768_find_dividing_wate(u32 pwesc_pawam)
{
	u32 cuw_cwk_dividing_wate_base100 = 100;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pwesc_dividing_wate); i++) {
		if (pwesc_dividing_wate[i].cwk_pwesc_enum == pwesc_pawam) {
			cuw_cwk_dividing_wate_base100 =
				pwesc_dividing_wate[i].dividing_wate_base100;
		}
	}

	wetuwn cuw_cwk_dividing_wate_base100;
}

/*
 * DW9768_AAC_PWESC_WEG & DW9768_AAC_TIME_WEG detewmine VCM opewation time.
 * Fow cuwwent VCM mode: AAC3, Opewation Time wouwd be 0.70 x Tvib.
 * Tvib = (6.3ms + AACT[5:0] * 0.1MS) * Dividing Wate.
 * Bewow is cawcuwation of the opewation deway fow each step.
 */
static inwine u32 dw9768_caw_move_deway(u32 aac_mode_pawam, u32 pwesc_pawam,
					u32 aac_timing_pawam)
{
	u32 Tvib_us;
	u32 ot_muwti_base100;
	u32 cwk_dividing_wate_base100;

	ot_muwti_base100 = dw9768_find_ot_muwti(aac_mode_pawam);

	cwk_dividing_wate_base100 = dw9768_find_dividing_wate(pwesc_pawam);

	Tvib_us = (DW9768_TVIB_MS_BASE10 + aac_timing_pawam) *
		  cwk_dividing_wate_base100;

	wetuwn Tvib_us * ot_muwti_base100 / 100;
}

static int dw9768_mod_weg(stwuct dw9768 *dw9768, u8 weg, u8 mask, u8 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dw9768->sd);
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0)
		wetuwn wet;

	vaw = ((unsigned chaw)wet & ~mask) | (vaw & mask);

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int dw9768_set_dac(stwuct dw9768 *dw9768, u16 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dw9768->sd);

	/* Wwite VCM position to wegistews */
	wetuwn i2c_smbus_wwite_wowd_swapped(cwient, DW9768_MSB_ADDW, vaw);
}

static int dw9768_init(stwuct dw9768 *dw9768)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dw9768->sd);
	int wet, vaw;

	/* Weset DW9768_WING_PD_CONTWOW_WEG to defauwt status 0x00 */
	wet = i2c_smbus_wwite_byte_data(cwient, DW9768_WING_PD_CONTWOW_WEG,
					DW9768_PD_MODE_OFF);
	if (wet < 0)
		wetuwn wet;

	/*
	 * DW9769 wequiwes waiting deway time of t_OPW
	 * aftew PD weset takes pwace.
	 */
	usweep_wange(DW9768_T_OPW_US, DW9768_T_OPW_US + 100);

	/* Set DW9768_WING_PD_CONTWOW_WEG to DW9768_AAC_MODE_EN(0x01) */
	wet = i2c_smbus_wwite_byte_data(cwient, DW9768_WING_PD_CONTWOW_WEG,
					DW9768_AAC_MODE_EN);
	if (wet < 0)
		wetuwn wet;

	/* Set AAC mode */
	wet = dw9768_mod_weg(dw9768, DW9768_AAC_PWESC_WEG,
			     DW9768_AAC_MODE_SEW_MASK,
			     dw9768->aac_mode << 5);
	if (wet < 0)
		wetuwn wet;

	/* Set cwock pwesc */
	if (dw9768->cwock_pwesc != DW9768_CWOCK_PWE_SCAWE_DEFAUWT) {
		wet = dw9768_mod_weg(dw9768, DW9768_AAC_PWESC_WEG,
				     DW9768_CWOCK_PWE_SCAWE_SEW_MASK,
				     dw9768->cwock_pwesc);
		if (wet < 0)
			wetuwn wet;
	}

	/* Set AAC Timing */
	if (dw9768->aac_timing != DW9768_AAC_TIME_DEFAUWT) {
		wet = i2c_smbus_wwite_byte_data(cwient, DW9768_AAC_TIME_WEG,
						dw9768->aac_timing);
		if (wet < 0)
			wetuwn wet;
	}

	fow (vaw = dw9768->focus->vaw % DW9768_MOVE_STEPS;
	     vaw <= dw9768->focus->vaw;
	     vaw += DW9768_MOVE_STEPS) {
		wet = dw9768_set_dac(dw9768, vaw);
		if (wet) {
			dev_eww(&cwient->dev, "I2C faiwuwe: %d", wet);
			wetuwn wet;
		}
		usweep_wange(dw9768->move_deway_us,
			     dw9768->move_deway_us + 1000);
	}

	wetuwn 0;
}

static int dw9768_wewease(stwuct dw9768 *dw9768)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&dw9768->sd);
	int wet, vaw;

	vaw = wound_down(dw9768->focus->vaw, DW9768_MOVE_STEPS);
	fow ( ; vaw >= 0; vaw -= DW9768_MOVE_STEPS) {
		wet = dw9768_set_dac(dw9768, vaw);
		if (wet) {
			dev_eww(&cwient->dev, "I2C wwite faiw: %d", wet);
			wetuwn wet;
		}
		usweep_wange(dw9768->move_deway_us,
			     dw9768->move_deway_us + 1000);
	}

	wet = i2c_smbus_wwite_byte_data(cwient, DW9768_WING_PD_CONTWOW_WEG,
					DW9768_PD_MODE_EN);
	if (wet < 0)
		wetuwn wet;

	/*
	 * DW9769 wequiwes waiting deway time of t_OPW
	 * aftew PD weset takes pwace.
	 */
	usweep_wange(DW9768_T_OPW_US, DW9768_T_OPW_US + 100);

	wetuwn 0;
}

static int dw9768_wuntime_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct dw9768 *dw9768 = sd_to_dw9768(sd);

	dw9768_wewease(dw9768);
	weguwatow_buwk_disabwe(AWWAY_SIZE(dw9768_suppwy_names),
			       dw9768->suppwies);

	wetuwn 0;
}

static int dw9768_wuntime_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct dw9768 *dw9768 = sd_to_dw9768(sd);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(dw9768_suppwy_names),
				    dw9768->suppwies);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe weguwatows\n");
		wetuwn wet;
	}

	/*
	 * The datasheet wefews to t_OPW that needs to be waited befowe sending
	 * I2C commands aftew powew-up.
	 */
	usweep_wange(DW9768_T_OPW_US, DW9768_T_OPW_US + 100);

	wet = dw9768_init(dw9768);
	if (wet < 0)
		goto disabwe_weguwatow;

	wetuwn 0;

disabwe_weguwatow:
	weguwatow_buwk_disabwe(AWWAY_SIZE(dw9768_suppwy_names),
			       dw9768->suppwies);

	wetuwn wet;
}

static int dw9768_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dw9768 *dw9768 = containew_of(ctww->handwew,
					     stwuct dw9768, ctwws);

	if (ctww->id == V4W2_CID_FOCUS_ABSOWUTE)
		wetuwn dw9768_set_dac(dw9768, ctww->vaw);

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops dw9768_ctww_ops = {
	.s_ctww = dw9768_set_ctww,
};

static int dw9768_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	wetuwn pm_wuntime_wesume_and_get(sd->dev);
}

static int dw9768_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	pm_wuntime_put(sd->dev);

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops dw9768_int_ops = {
	.open = dw9768_open,
	.cwose = dw9768_cwose,
};

static const stwuct v4w2_subdev_ops dw9768_ops = { };

static int dw9768_init_contwows(stwuct dw9768 *dw9768)
{
	stwuct v4w2_ctww_handwew *hdw = &dw9768->ctwws;
	const stwuct v4w2_ctww_ops *ops = &dw9768_ctww_ops;

	v4w2_ctww_handwew_init(hdw, 1);

	dw9768->focus = v4w2_ctww_new_std(hdw, ops, V4W2_CID_FOCUS_ABSOWUTE, 0,
					  DW9768_MAX_FOCUS_POS,
					  DW9768_FOCUS_STEPS, 0);

	if (hdw->ewwow)
		wetuwn hdw->ewwow;

	dw9768->sd.ctww_handwew = hdw;

	wetuwn 0;
}

static int dw9768_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct dw9768 *dw9768;
	boow fuww_powew;
	unsigned int i;
	int wet;

	dw9768 = devm_kzawwoc(dev, sizeof(*dw9768), GFP_KEWNEW);
	if (!dw9768)
		wetuwn -ENOMEM;

	/* Initiawize subdev */
	v4w2_i2c_subdev_init(&dw9768->sd, cwient, &dw9768_ops);

	dw9768->aac_mode = DW9768_AAC_MODE_DEFAUWT;
	dw9768->aac_timing = DW9768_AAC_TIME_DEFAUWT;
	dw9768->cwock_pwesc = DW9768_CWOCK_PWE_SCAWE_DEFAUWT;

	/* Optionaw indication of AAC mode sewect */
	fwnode_pwopewty_wead_u32(dev_fwnode(dev), "dongwoon,aac-mode",
				 &dw9768->aac_mode);

	/* Optionaw indication of cwock pwe-scawe sewect */
	fwnode_pwopewty_wead_u32(dev_fwnode(dev), "dongwoon,cwock-pwesc",
				 &dw9768->cwock_pwesc);

	/* Optionaw indication of AAC Timing */
	fwnode_pwopewty_wead_u32(dev_fwnode(dev), "dongwoon,aac-timing",
				 &dw9768->aac_timing);

	dw9768->move_deway_us = dw9768_caw_move_deway(dw9768->aac_mode,
						      dw9768->cwock_pwesc,
						      dw9768->aac_timing);

	fow (i = 0; i < AWWAY_SIZE(dw9768_suppwy_names); i++)
		dw9768->suppwies[i].suppwy = dw9768_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(dw9768_suppwy_names),
				      dw9768->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to get weguwatows\n");
		wetuwn wet;
	}

	/* Initiawize contwows */
	wet = dw9768_init_contwows(dw9768);
	if (wet)
		goto eww_fwee_handwew;

	/* Initiawize subdev */
	dw9768->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	dw9768->sd.intewnaw_ops = &dw9768_int_ops;

	wet = media_entity_pads_init(&dw9768->sd.entity, 0, NUWW);
	if (wet < 0)
		goto eww_fwee_handwew;

	dw9768->sd.entity.function = MEDIA_ENT_F_WENS;

	/*
	 * Figuwe out whethew we'we going to powew up the device hewe. Genewawwy
	 * this is done if CONFIG_PM is disabwed in a DT system ow the device is
	 * to be powewed on in an ACPI system. Simiwawwy fow powew off in
	 * wemove.
	 */
	pm_wuntime_enabwe(dev);
	fuww_powew = (is_acpi_node(dev_fwnode(dev)) &&
		      acpi_dev_state_d0(dev)) ||
		     (is_of_node(dev_fwnode(dev)) && !pm_wuntime_enabwed(dev));
	if (fuww_powew) {
		wet = dw9768_wuntime_wesume(dev);
		if (wet < 0) {
			dev_eww(dev, "faiwed to powew on: %d\n", wet);
			goto eww_cwean_entity;
		}
		pm_wuntime_set_active(dev);
	}

	wet = v4w2_async_wegistew_subdev(&dw9768->sd);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew V4W2 subdev: %d", wet);
		goto eww_powew_off;
	}

	pm_wuntime_idwe(dev);

	wetuwn 0;

eww_powew_off:
	if (fuww_powew) {
		dw9768_wuntime_suspend(dev);
		pm_wuntime_set_suspended(dev);
	}
eww_cwean_entity:
	pm_wuntime_disabwe(dev);
	media_entity_cweanup(&dw9768->sd.entity);
eww_fwee_handwew:
	v4w2_ctww_handwew_fwee(&dw9768->ctwws);

	wetuwn wet;
}

static void dw9768_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct dw9768 *dw9768 = sd_to_dw9768(sd);
	stwuct device *dev = &cwient->dev;

	v4w2_async_unwegistew_subdev(&dw9768->sd);
	v4w2_ctww_handwew_fwee(&dw9768->ctwws);
	media_entity_cweanup(&dw9768->sd.entity);
	if ((is_acpi_node(dev_fwnode(dev)) && acpi_dev_state_d0(dev)) ||
	    (is_of_node(dev_fwnode(dev)) && !pm_wuntime_enabwed(dev))) {
		dw9768_wuntime_suspend(dev);
		pm_wuntime_set_suspended(dev);
	}
	pm_wuntime_disabwe(dev);
}

static const stwuct of_device_id dw9768_of_tabwe[] = {
	{ .compatibwe = "dongwoon,dw9768" },
	{ .compatibwe = "giantec,gt9769" },
	{}
};
MODUWE_DEVICE_TABWE(of, dw9768_of_tabwe);

static const stwuct dev_pm_ops dw9768_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(dw9768_wuntime_suspend, dw9768_wuntime_wesume, NUWW)
};

static stwuct i2c_dwivew dw9768_i2c_dwivew = {
	.dwivew = {
		.name = DW9768_NAME,
		.pm = &dw9768_pm_ops,
		.of_match_tabwe = dw9768_of_tabwe,
	},
	.pwobe = dw9768_pwobe,
	.wemove = dw9768_wemove,
};
moduwe_i2c_dwivew(dw9768_i2c_dwivew);

MODUWE_AUTHOW("Dongchun Zhu <dongchun.zhu@mediatek.com>");
MODUWE_DESCWIPTION("DW9768 VCM dwivew");
MODUWE_WICENSE("GPW v2");
