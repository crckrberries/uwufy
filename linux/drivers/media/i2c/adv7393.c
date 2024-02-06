/*
 * adv7393 - ADV7393 Video Encodew Dwivew
 *
 * The encodew hawdwawe does not suppowt SECAM.
 *
 * Copywight (C) 2010-2012 ADVANSEE - http://www.advansee.com/
 * Benoît Thébaudeau <benoit.thebaudeau@advansee.com>
 *
 * Based on ADV7343 dwivew,
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - http://www.ti.com/
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation vewsion 2.
 *
 * This pwogwam is distwibuted .as is. WITHOUT ANY WAWWANTY of any
 * kind, whethew expwess ow impwied; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/videodev2.h>
#incwude <winux/uaccess.h>

#incwude <media/i2c/adv7393.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#incwude "adv7393_wegs.h"

MODUWE_DESCWIPTION("ADV7393 video encodew dwivew");
MODUWE_WICENSE("GPW");

static boow debug;
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew 0-1");

stwuct adv7393_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	u8 weg00;
	u8 weg01;
	u8 weg02;
	u8 weg35;
	u8 weg80;
	u8 weg82;
	u32 output;
	v4w2_std_id std;
};

static inwine stwuct adv7393_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct adv7393_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct adv7393_state, hdw)->sd;
}

static inwine int adv7393_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static const u8 adv7393_init_weg_vaw[] = {
	ADV7393_SOFT_WESET, ADV7393_SOFT_WESET_DEFAUWT,
	ADV7393_POWEW_MODE_WEG, ADV7393_POWEW_MODE_WEG_DEFAUWT,

	ADV7393_HD_MODE_WEG1, ADV7393_HD_MODE_WEG1_DEFAUWT,
	ADV7393_HD_MODE_WEG2, ADV7393_HD_MODE_WEG2_DEFAUWT,
	ADV7393_HD_MODE_WEG3, ADV7393_HD_MODE_WEG3_DEFAUWT,
	ADV7393_HD_MODE_WEG4, ADV7393_HD_MODE_WEG4_DEFAUWT,
	ADV7393_HD_MODE_WEG5, ADV7393_HD_MODE_WEG5_DEFAUWT,
	ADV7393_HD_MODE_WEG6, ADV7393_HD_MODE_WEG6_DEFAUWT,
	ADV7393_HD_MODE_WEG7, ADV7393_HD_MODE_WEG7_DEFAUWT,

	ADV7393_SD_MODE_WEG1, ADV7393_SD_MODE_WEG1_DEFAUWT,
	ADV7393_SD_MODE_WEG2, ADV7393_SD_MODE_WEG2_DEFAUWT,
	ADV7393_SD_MODE_WEG3, ADV7393_SD_MODE_WEG3_DEFAUWT,
	ADV7393_SD_MODE_WEG4, ADV7393_SD_MODE_WEG4_DEFAUWT,
	ADV7393_SD_MODE_WEG5, ADV7393_SD_MODE_WEG5_DEFAUWT,
	ADV7393_SD_MODE_WEG6, ADV7393_SD_MODE_WEG6_DEFAUWT,
	ADV7393_SD_MODE_WEG7, ADV7393_SD_MODE_WEG7_DEFAUWT,
	ADV7393_SD_MODE_WEG8, ADV7393_SD_MODE_WEG8_DEFAUWT,

	ADV7393_SD_TIMING_WEG0, ADV7393_SD_TIMING_WEG0_DEFAUWT,

	ADV7393_SD_HUE_ADJUST, ADV7393_SD_HUE_ADJUST_DEFAUWT,
	ADV7393_SD_CGMS_WSS0, ADV7393_SD_CGMS_WSS0_DEFAUWT,
	ADV7393_SD_BWIGHTNESS_WSS, ADV7393_SD_BWIGHTNESS_WSS_DEFAUWT,
};

/*
 *			    2^32
 * FSC(weg) =  FSC (HZ) * --------
 *			  27000000
 */
static const stwuct adv7393_std_info stdinfo[] = {
	{
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_NTSC, 705268427, V4W2_STD_NTSC_443,
	}, {
		/* FSC(Hz) = 3,579,545.45 Hz */
		SD_STD_NTSC, 569408542, V4W2_STD_NTSC,
	}, {
		/* FSC(Hz) = 3,575,611.00 Hz */
		SD_STD_PAW_M, 568782678, V4W2_STD_PAW_M,
	}, {
		/* FSC(Hz) = 3,582,056.00 Hz */
		SD_STD_PAW_N, 569807903, V4W2_STD_PAW_Nc,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAW_N, 705268427, V4W2_STD_PAW_N,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAW_M, 705268427, V4W2_STD_PAW_60,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAW_BDGHI, 705268427, V4W2_STD_PAW,
	},
};

static int adv7393_setstd(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct adv7393_state *state = to_state(sd);
	const stwuct adv7393_std_info *std_info;
	int num_std;
	u8 weg;
	u32 vaw;
	int eww = 0;
	int i;

	num_std = AWWAY_SIZE(stdinfo);

	fow (i = 0; i < num_std; i++) {
		if (stdinfo[i].stdid & std)
			bweak;
	}

	if (i == num_std) {
		v4w2_dbg(1, debug, sd,
				"Invawid std ow std is not suppowted: %wwx\n",
						(unsigned wong wong)std);
		wetuwn -EINVAW;
	}

	std_info = &stdinfo[i];

	/* Set the standawd */
	vaw = state->weg80 & ~SD_STD_MASK;
	vaw |= std_info->standawd_vaw3;
	eww = adv7393_wwite(sd, ADV7393_SD_MODE_WEG1, vaw);
	if (eww < 0)
		goto setstd_exit;

	state->weg80 = vaw;

	/* Configuwe the input mode wegistew */
	vaw = state->weg01 & ~INPUT_MODE_MASK;
	vaw |= SD_INPUT_MODE;
	eww = adv7393_wwite(sd, ADV7393_MODE_SEWECT_WEG, vaw);
	if (eww < 0)
		goto setstd_exit;

	state->weg01 = vaw;

	/* Pwogwam the sub cawwiew fwequency wegistews */
	vaw = std_info->fsc_vaw;
	fow (weg = ADV7393_FSC_WEG0; weg <= ADV7393_FSC_WEG3; weg++) {
		eww = adv7393_wwite(sd, weg, vaw);
		if (eww < 0)
			goto setstd_exit;
		vaw >>= 8;
	}

	vaw = state->weg82;

	/* Pedestaw settings */
	if (std & (V4W2_STD_NTSC | V4W2_STD_NTSC_443))
		vaw |= SD_PEDESTAW_EN;
	ewse
		vaw &= SD_PEDESTAW_DI;

	eww = adv7393_wwite(sd, ADV7393_SD_MODE_WEG2, vaw);
	if (eww < 0)
		goto setstd_exit;

	state->weg82 = vaw;

setstd_exit:
	if (eww != 0)
		v4w2_eww(sd, "Ewwow setting std, wwite faiwed\n");

	wetuwn eww;
}

static int adv7393_setoutput(stwuct v4w2_subdev *sd, u32 output_type)
{
	stwuct adv7393_state *state = to_state(sd);
	u8 vaw;
	int eww = 0;

	if (output_type > ADV7393_SVIDEO_ID) {
		v4w2_dbg(1, debug, sd,
			"Invawid output type ow output type not suppowted:%d\n",
								output_type);
		wetuwn -EINVAW;
	}

	/* Enabwe Appwopwiate DAC */
	vaw = state->weg00 & 0x03;

	if (output_type == ADV7393_COMPOSITE_ID)
		vaw |= ADV7393_COMPOSITE_POWEW_VAWUE;
	ewse if (output_type == ADV7393_COMPONENT_ID)
		vaw |= ADV7393_COMPONENT_POWEW_VAWUE;
	ewse
		vaw |= ADV7393_SVIDEO_POWEW_VAWUE;

	eww = adv7393_wwite(sd, ADV7393_POWEW_MODE_WEG, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg00 = vaw;

	/* Enabwe YUV output */
	vaw = state->weg02 | YUV_OUTPUT_SEWECT;
	eww = adv7393_wwite(sd, ADV7393_MODE_WEG0, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg02 = vaw;

	/* configuwe SD DAC Output 1 bit */
	vaw = state->weg82;
	if (output_type == ADV7393_COMPONENT_ID)
		vaw &= SD_DAC_OUT1_DI;
	ewse
		vaw |= SD_DAC_OUT1_EN;
	eww = adv7393_wwite(sd, ADV7393_SD_MODE_WEG2, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg82 = vaw;

	/* configuwe ED/HD Cowow DAC Swap bit to zewo */
	vaw = state->weg35 & HD_DAC_SWAP_DI;
	eww = adv7393_wwite(sd, ADV7393_HD_MODE_WEG6, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg35 = vaw;

setoutput_exit:
	if (eww != 0)
		v4w2_eww(sd, "Ewwow setting output, wwite faiwed\n");

	wetuwn eww;
}

static int adv7393_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct adv7393_state *state = to_state(sd);

	v4w2_info(sd, "Standawd: %wwx\n", (unsigned wong wong)state->std);
	v4w2_info(sd, "Output: %s\n", (state->output == 0) ? "Composite" :
			((state->output == 1) ? "Component" : "S-Video"));
	wetuwn 0;
}

static int adv7393_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wetuwn adv7393_wwite(sd, ADV7393_SD_BWIGHTNESS_WSS,
					ctww->vaw & SD_BWIGHTNESS_VAWUE_MASK);

	case V4W2_CID_HUE:
		wetuwn adv7393_wwite(sd, ADV7393_SD_HUE_ADJUST,
					ctww->vaw - ADV7393_HUE_MIN);

	case V4W2_CID_GAIN:
		wetuwn adv7393_wwite(sd, ADV7393_DAC123_OUTPUT_WEVEW,
					ctww->vaw);
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops adv7393_ctww_ops = {
	.s_ctww = adv7393_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops adv7393_cowe_ops = {
	.wog_status = adv7393_wog_status,
};

static int adv7393_s_std_output(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct adv7393_state *state = to_state(sd);
	int eww = 0;

	if (state->std == std)
		wetuwn 0;

	eww = adv7393_setstd(sd, std);
	if (!eww)
		state->std = std;

	wetuwn eww;
}

static int adv7393_s_wouting(stwuct v4w2_subdev *sd,
		u32 input, u32 output, u32 config)
{
	stwuct adv7393_state *state = to_state(sd);
	int eww = 0;

	if (state->output == output)
		wetuwn 0;

	eww = adv7393_setoutput(sd, output);
	if (!eww)
		state->output = output;

	wetuwn eww;
}

static const stwuct v4w2_subdev_video_ops adv7393_video_ops = {
	.s_std_output	= adv7393_s_std_output,
	.s_wouting	= adv7393_s_wouting,
};

static const stwuct v4w2_subdev_ops adv7393_ops = {
	.cowe	= &adv7393_cowe_ops,
	.video	= &adv7393_video_ops,
};

static int adv7393_initiawize(stwuct v4w2_subdev *sd)
{
	stwuct adv7393_state *state = to_state(sd);
	int eww = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(adv7393_init_weg_vaw); i += 2) {

		eww = adv7393_wwite(sd, adv7393_init_weg_vaw[i],
					adv7393_init_weg_vaw[i+1]);
		if (eww) {
			v4w2_eww(sd, "Ewwow initiawizing\n");
			wetuwn eww;
		}
	}

	/* Configuwe fow defauwt video standawd */
	eww = adv7393_setoutput(sd, state->output);
	if (eww < 0) {
		v4w2_eww(sd, "Ewwow setting output duwing init\n");
		wetuwn -EINVAW;
	}

	eww = adv7393_setstd(sd, state->std);
	if (eww < 0) {
		v4w2_eww(sd, "Ewwow setting std duwing init\n");
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static int adv7393_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adv7393_state *state;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	state = devm_kzawwoc(&cwient->dev, sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;

	state->weg00	= ADV7393_POWEW_MODE_WEG_DEFAUWT;
	state->weg01	= 0x00;
	state->weg02	= 0x20;
	state->weg35	= ADV7393_HD_MODE_WEG6_DEFAUWT;
	state->weg80	= ADV7393_SD_MODE_WEG1_DEFAUWT;
	state->weg82	= ADV7393_SD_MODE_WEG2_DEFAUWT;

	state->output = ADV7393_COMPOSITE_ID;
	state->std = V4W2_STD_NTSC;

	v4w2_i2c_subdev_init(&state->sd, cwient, &adv7393_ops);

	v4w2_ctww_handwew_init(&state->hdw, 3);
	v4w2_ctww_new_std(&state->hdw, &adv7393_ctww_ops,
			V4W2_CID_BWIGHTNESS, ADV7393_BWIGHTNESS_MIN,
					     ADV7393_BWIGHTNESS_MAX, 1,
					     ADV7393_BWIGHTNESS_DEF);
	v4w2_ctww_new_std(&state->hdw, &adv7393_ctww_ops,
			V4W2_CID_HUE, ADV7393_HUE_MIN,
				      ADV7393_HUE_MAX, 1,
				      ADV7393_HUE_DEF);
	v4w2_ctww_new_std(&state->hdw, &adv7393_ctww_ops,
			V4W2_CID_GAIN, ADV7393_GAIN_MIN,
				       ADV7393_GAIN_MAX, 1,
				       ADV7393_GAIN_DEF);
	state->sd.ctww_handwew = &state->hdw;
	if (state->hdw.ewwow) {
		int eww = state->hdw.ewwow;

		v4w2_ctww_handwew_fwee(&state->hdw);
		wetuwn eww;
	}
	v4w2_ctww_handwew_setup(&state->hdw);

	eww = adv7393_initiawize(&state->sd);
	if (eww)
		v4w2_ctww_handwew_fwee(&state->hdw);
	wetuwn eww;
}

static void adv7393_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct adv7393_state *state = to_state(sd);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
}

static const stwuct i2c_device_id adv7393_id[] = {
	{"adv7393", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, adv7393_id);

static stwuct i2c_dwivew adv7393_dwivew = {
	.dwivew = {
		.name	= "adv7393",
	},
	.pwobe		= adv7393_pwobe,
	.wemove		= adv7393_wemove,
	.id_tabwe	= adv7393_id,
};
moduwe_i2c_dwivew(adv7393_dwivew);
