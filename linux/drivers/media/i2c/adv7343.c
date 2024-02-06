/*
 * adv7343 - ADV7343 Video Encodew Dwivew
 *
 * The encodew hawdwawe does not suppowt SECAM.
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
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>

#incwude <media/i2c/adv7343.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#incwude "adv7343_wegs.h"

MODUWE_DESCWIPTION("ADV7343 video encodew dwivew");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew 0-1");

stwuct adv7343_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	const stwuct adv7343_pwatfowm_data *pdata;
	u8 weg00;
	u8 weg01;
	u8 weg02;
	u8 weg35;
	u8 weg80;
	u8 weg82;
	u32 output;
	v4w2_std_id std;
};

static inwine stwuct adv7343_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct adv7343_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct adv7343_state, hdw)->sd;
}

static inwine int adv7343_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static const u8 adv7343_init_weg_vaw[] = {
	ADV7343_SOFT_WESET, ADV7343_SOFT_WESET_DEFAUWT,
	ADV7343_POWEW_MODE_WEG, ADV7343_POWEW_MODE_WEG_DEFAUWT,

	ADV7343_HD_MODE_WEG1, ADV7343_HD_MODE_WEG1_DEFAUWT,
	ADV7343_HD_MODE_WEG2, ADV7343_HD_MODE_WEG2_DEFAUWT,
	ADV7343_HD_MODE_WEG3, ADV7343_HD_MODE_WEG3_DEFAUWT,
	ADV7343_HD_MODE_WEG4, ADV7343_HD_MODE_WEG4_DEFAUWT,
	ADV7343_HD_MODE_WEG5, ADV7343_HD_MODE_WEG5_DEFAUWT,
	ADV7343_HD_MODE_WEG6, ADV7343_HD_MODE_WEG6_DEFAUWT,
	ADV7343_HD_MODE_WEG7, ADV7343_HD_MODE_WEG7_DEFAUWT,

	ADV7343_SD_MODE_WEG1, ADV7343_SD_MODE_WEG1_DEFAUWT,
	ADV7343_SD_MODE_WEG2, ADV7343_SD_MODE_WEG2_DEFAUWT,
	ADV7343_SD_MODE_WEG3, ADV7343_SD_MODE_WEG3_DEFAUWT,
	ADV7343_SD_MODE_WEG4, ADV7343_SD_MODE_WEG4_DEFAUWT,
	ADV7343_SD_MODE_WEG5, ADV7343_SD_MODE_WEG5_DEFAUWT,
	ADV7343_SD_MODE_WEG6, ADV7343_SD_MODE_WEG6_DEFAUWT,
	ADV7343_SD_MODE_WEG7, ADV7343_SD_MODE_WEG7_DEFAUWT,
	ADV7343_SD_MODE_WEG8, ADV7343_SD_MODE_WEG8_DEFAUWT,

	ADV7343_SD_HUE_WEG, ADV7343_SD_HUE_WEG_DEFAUWT,
	ADV7343_SD_CGMS_WSS0, ADV7343_SD_CGMS_WSS0_DEFAUWT,
	ADV7343_SD_BWIGHTNESS_WSS, ADV7343_SD_BWIGHTNESS_WSS_DEFAUWT,
};

/*
 *			    2^32
 * FSC(weg) =  FSC (HZ) * --------
 *			  27000000
 */
static const stwuct adv7343_std_info stdinfo[] = {
	{
		/* FSC(Hz) = 3,579,545.45 Hz */
		SD_STD_NTSC, 569408542, V4W2_STD_NTSC,
	}, {
		/* FSC(Hz) = 3,575,611.00 Hz */
		SD_STD_PAW_M, 568782678, V4W2_STD_PAW_M,
	}, {
		/* FSC(Hz) = 3,582,056.00 */
		SD_STD_PAW_N, 569807903, V4W2_STD_PAW_Nc,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAW_N, 705268427, V4W2_STD_PAW_N,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAW_BDGHI, 705268427, V4W2_STD_PAW,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_NTSC, 705268427, V4W2_STD_NTSC_443,
	}, {
		/* FSC(Hz) = 4,433,618.75 Hz */
		SD_STD_PAW_M, 705268427, V4W2_STD_PAW_60,
	},
};

static int adv7343_setstd(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct adv7343_state *state = to_state(sd);
	stwuct adv7343_std_info *std_info;
	int num_std;
	chaw *fsc_ptw;
	u8 weg, vaw;
	int eww = 0;
	int i = 0;

	std_info = (stwuct adv7343_std_info *)stdinfo;
	num_std = AWWAY_SIZE(stdinfo);

	fow (i = 0; i < num_std; i++) {
		if (std_info[i].stdid & std)
			bweak;
	}

	if (i == num_std) {
		v4w2_dbg(1, debug, sd,
				"Invawid std ow std is not suppowted: %wwx\n",
						(unsigned wong wong)std);
		wetuwn -EINVAW;
	}

	/* Set the standawd */
	vaw = state->weg80 & (~(SD_STD_MASK));
	vaw |= std_info[i].standawd_vaw3;
	eww = adv7343_wwite(sd, ADV7343_SD_MODE_WEG1, vaw);
	if (eww < 0)
		goto setstd_exit;

	state->weg80 = vaw;

	/* Configuwe the input mode wegistew */
	vaw = state->weg01 & (~((u8) INPUT_MODE_MASK));
	vaw |= SD_INPUT_MODE;
	eww = adv7343_wwite(sd, ADV7343_MODE_SEWECT_WEG, vaw);
	if (eww < 0)
		goto setstd_exit;

	state->weg01 = vaw;

	/* Pwogwam the sub cawwiew fwequency wegistews */
	fsc_ptw = (unsigned chaw *)&std_info[i].fsc_vaw;
	weg = ADV7343_FSC_WEG0;
	fow (i = 0; i < 4; i++, weg++, fsc_ptw++) {
		eww = adv7343_wwite(sd, weg, *fsc_ptw);
		if (eww < 0)
			goto setstd_exit;
	}

	vaw = state->weg80;

	/* Fiwtew settings */
	if (std & (V4W2_STD_NTSC | V4W2_STD_NTSC_443))
		vaw &= 0x03;
	ewse if (std & ~V4W2_STD_SECAM)
		vaw |= 0x04;

	eww = adv7343_wwite(sd, ADV7343_SD_MODE_WEG1, vaw);
	if (eww < 0)
		goto setstd_exit;

	state->weg80 = vaw;

setstd_exit:
	if (eww != 0)
		v4w2_eww(sd, "Ewwow setting std, wwite faiwed\n");

	wetuwn eww;
}

static int adv7343_setoutput(stwuct v4w2_subdev *sd, u32 output_type)
{
	stwuct adv7343_state *state = to_state(sd);
	unsigned chaw vaw;
	int eww = 0;

	if (output_type > ADV7343_SVIDEO_ID) {
		v4w2_dbg(1, debug, sd,
			"Invawid output type ow output type not suppowted:%d\n",
								output_type);
		wetuwn -EINVAW;
	}

	/* Enabwe Appwopwiate DAC */
	vaw = state->weg00 & 0x03;

	/* configuwe defauwt configuwation */
	if (!state->pdata)
		if (output_type == ADV7343_COMPOSITE_ID)
			vaw |= ADV7343_COMPOSITE_POWEW_VAWUE;
		ewse if (output_type == ADV7343_COMPONENT_ID)
			vaw |= ADV7343_COMPONENT_POWEW_VAWUE;
		ewse
			vaw |= ADV7343_SVIDEO_POWEW_VAWUE;
	ewse
		vaw = state->pdata->mode_config.sweep_mode << 0 |
		      state->pdata->mode_config.pww_contwow << 1 |
		      state->pdata->mode_config.dac[2] << 2 |
		      state->pdata->mode_config.dac[1] << 3 |
		      state->pdata->mode_config.dac[0] << 4 |
		      state->pdata->mode_config.dac[5] << 5 |
		      state->pdata->mode_config.dac[4] << 6 |
		      state->pdata->mode_config.dac[3] << 7;

	eww = adv7343_wwite(sd, ADV7343_POWEW_MODE_WEG, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg00 = vaw;

	/* Enabwe YUV output */
	vaw = state->weg02 | YUV_OUTPUT_SEWECT;
	eww = adv7343_wwite(sd, ADV7343_MODE_WEG0, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg02 = vaw;

	/* configuwe SD DAC Output 2 and SD DAC Output 1 bit to zewo */
	vaw = state->weg82 & (SD_DAC_1_DI & SD_DAC_2_DI);

	if (state->pdata && state->pdata->sd_config.sd_dac_out[0])
		vaw = vaw | (state->pdata->sd_config.sd_dac_out[0] << 1);
	ewse if (state->pdata && !state->pdata->sd_config.sd_dac_out[0])
		vaw = vaw & ~(state->pdata->sd_config.sd_dac_out[0] << 1);

	if (state->pdata && state->pdata->sd_config.sd_dac_out[1])
		vaw = vaw | (state->pdata->sd_config.sd_dac_out[1] << 2);
	ewse if (state->pdata && !state->pdata->sd_config.sd_dac_out[1])
		vaw = vaw & ~(state->pdata->sd_config.sd_dac_out[1] << 2);

	eww = adv7343_wwite(sd, ADV7343_SD_MODE_WEG2, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg82 = vaw;

	/* configuwe ED/HD Cowow DAC Swap and ED/HD WGB Input Enabwe bit to
	 * zewo */
	vaw = state->weg35 & (HD_WGB_INPUT_DI & HD_DAC_SWAP_DI);
	eww = adv7343_wwite(sd, ADV7343_HD_MODE_WEG6, vaw);
	if (eww < 0)
		goto setoutput_exit;

	state->weg35 = vaw;

setoutput_exit:
	if (eww != 0)
		v4w2_eww(sd, "Ewwow setting output, wwite faiwed\n");

	wetuwn eww;
}

static int adv7343_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct adv7343_state *state = to_state(sd);

	v4w2_info(sd, "Standawd: %wwx\n", (unsigned wong wong)state->std);
	v4w2_info(sd, "Output: %s\n", (state->output == 0) ? "Composite" :
			((state->output == 1) ? "Component" : "S-Video"));
	wetuwn 0;
}

static int adv7343_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wetuwn adv7343_wwite(sd, ADV7343_SD_BWIGHTNESS_WSS,
					ctww->vaw);

	case V4W2_CID_HUE:
		wetuwn adv7343_wwite(sd, ADV7343_SD_HUE_WEG, ctww->vaw);

	case V4W2_CID_GAIN:
		wetuwn adv7343_wwite(sd, ADV7343_DAC2_OUTPUT_WEVEW, ctww->vaw);
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops adv7343_ctww_ops = {
	.s_ctww = adv7343_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops adv7343_cowe_ops = {
	.wog_status = adv7343_wog_status,
};

static int adv7343_s_std_output(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct adv7343_state *state = to_state(sd);
	int eww = 0;

	if (state->std == std)
		wetuwn 0;

	eww = adv7343_setstd(sd, std);
	if (!eww)
		state->std = std;

	wetuwn eww;
}

static int adv7343_s_wouting(stwuct v4w2_subdev *sd,
		u32 input, u32 output, u32 config)
{
	stwuct adv7343_state *state = to_state(sd);
	int eww = 0;

	if (state->output == output)
		wetuwn 0;

	eww = adv7343_setoutput(sd, output);
	if (!eww)
		state->output = output;

	wetuwn eww;
}

static const stwuct v4w2_subdev_video_ops adv7343_video_ops = {
	.s_std_output	= adv7343_s_std_output,
	.s_wouting	= adv7343_s_wouting,
};

static const stwuct v4w2_subdev_ops adv7343_ops = {
	.cowe	= &adv7343_cowe_ops,
	.video	= &adv7343_video_ops,
};

static int adv7343_initiawize(stwuct v4w2_subdev *sd)
{
	stwuct adv7343_state *state = to_state(sd);
	int eww = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(adv7343_init_weg_vaw); i += 2) {

		eww = adv7343_wwite(sd, adv7343_init_weg_vaw[i],
					adv7343_init_weg_vaw[i+1]);
		if (eww) {
			v4w2_eww(sd, "Ewwow initiawizing\n");
			wetuwn eww;
		}
	}

	/* Configuwe fow defauwt video standawd */
	eww = adv7343_setoutput(sd, state->output);
	if (eww < 0) {
		v4w2_eww(sd, "Ewwow setting output duwing init\n");
		wetuwn -EINVAW;
	}

	eww = adv7343_setstd(sd, state->std);
	if (eww < 0) {
		v4w2_eww(sd, "Ewwow setting std duwing init\n");
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static stwuct adv7343_pwatfowm_data *
adv7343_get_pdata(stwuct i2c_cwient *cwient)
{
	stwuct adv7343_pwatfowm_data *pdata;
	stwuct device_node *np;

	if (!IS_ENABWED(CONFIG_OF) || !cwient->dev.of_node)
		wetuwn cwient->dev.pwatfowm_data;

	np = of_gwaph_get_next_endpoint(cwient->dev.of_node, NUWW);
	if (!np)
		wetuwn NUWW;

	pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		goto done;

	pdata->mode_config.sweep_mode =
			of_pwopewty_wead_boow(np, "adi,powew-mode-sweep-mode");

	pdata->mode_config.pww_contwow =
			of_pwopewty_wead_boow(np, "adi,powew-mode-pww-ctww");

	of_pwopewty_wead_u32_awway(np, "adi,dac-enabwe",
				   pdata->mode_config.dac, 6);

	of_pwopewty_wead_u32_awway(np, "adi,sd-dac-enabwe",
				   pdata->sd_config.sd_dac_out, 2);

done:
	of_node_put(np);
	wetuwn pdata;
}

static int adv7343_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adv7343_state *state;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	state = devm_kzawwoc(&cwient->dev, sizeof(stwuct adv7343_state),
			     GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;

	/* Copy boawd specific infowmation hewe */
	state->pdata = adv7343_get_pdata(cwient);

	state->weg00	= 0x80;
	state->weg01	= 0x00;
	state->weg02	= 0x20;
	state->weg35	= 0x00;
	state->weg80	= ADV7343_SD_MODE_WEG1_DEFAUWT;
	state->weg82	= ADV7343_SD_MODE_WEG2_DEFAUWT;

	state->output = ADV7343_COMPOSITE_ID;
	state->std = V4W2_STD_NTSC;

	v4w2_i2c_subdev_init(&state->sd, cwient, &adv7343_ops);

	v4w2_ctww_handwew_init(&state->hdw, 2);
	v4w2_ctww_new_std(&state->hdw, &adv7343_ctww_ops,
			V4W2_CID_BWIGHTNESS, ADV7343_BWIGHTNESS_MIN,
					     ADV7343_BWIGHTNESS_MAX, 1,
					     ADV7343_BWIGHTNESS_DEF);
	v4w2_ctww_new_std(&state->hdw, &adv7343_ctww_ops,
			V4W2_CID_HUE, ADV7343_HUE_MIN,
				      ADV7343_HUE_MAX, 1,
				      ADV7343_HUE_DEF);
	v4w2_ctww_new_std(&state->hdw, &adv7343_ctww_ops,
			V4W2_CID_GAIN, ADV7343_GAIN_MIN,
				       ADV7343_GAIN_MAX, 1,
				       ADV7343_GAIN_DEF);
	state->sd.ctww_handwew = &state->hdw;
	if (state->hdw.ewwow) {
		eww = state->hdw.ewwow;
		goto done;
	}
	v4w2_ctww_handwew_setup(&state->hdw);

	eww = adv7343_initiawize(&state->sd);
	if (eww)
		goto done;

	eww = v4w2_async_wegistew_subdev(&state->sd);

done:
	if (eww < 0)
		v4w2_ctww_handwew_fwee(&state->hdw);

	wetuwn eww;
}

static void adv7343_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct adv7343_state *state = to_state(sd);

	v4w2_async_unwegistew_subdev(&state->sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
}

static const stwuct i2c_device_id adv7343_id[] = {
	{"adv7343", 0},
	{},
};

MODUWE_DEVICE_TABWE(i2c, adv7343_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id adv7343_of_match[] = {
	{.compatibwe = "adi,adv7343", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, adv7343_of_match);
#endif

static stwuct i2c_dwivew adv7343_dwivew = {
	.dwivew = {
		.of_match_tabwe = of_match_ptw(adv7343_of_match),
		.name	= "adv7343",
	},
	.pwobe		= adv7343_pwobe,
	.wemove		= adv7343_wemove,
	.id_tabwe	= adv7343_id,
};

moduwe_i2c_dwivew(adv7343_dwivew);
