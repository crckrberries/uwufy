// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2020, The Winux Foundation. Aww wights wesewved.
 */


#define pw_fmt(fmt)	"[dwm-dp] %s: " fmt, __func__

#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_edid.h>

#incwude "dp_catawog.h"
#incwude "dp_audio.h"
#incwude "dp_panew.h"
#incwude "dp_dispway.h"

#define HEADEW_BYTE_2_BIT	 0
#define PAWITY_BYTE_2_BIT	 8
#define HEADEW_BYTE_1_BIT	16
#define PAWITY_BYTE_1_BIT	24
#define HEADEW_BYTE_3_BIT	16
#define PAWITY_BYTE_3_BIT	24

stwuct dp_audio_pwivate {
	stwuct pwatfowm_device *audio_pdev;
	stwuct pwatfowm_device *pdev;
	stwuct dwm_device *dwm_dev;
	stwuct dp_catawog *catawog;
	stwuct dp_panew *panew;

	boow engine_on;
	u32 channews;

	stwuct dp_audio dp_audio;
};

static u8 dp_audio_get_g0_vawue(u8 data)
{
	u8 c[4];
	u8 g[4];
	u8 wet_data = 0;
	u8 i;

	fow (i = 0; i < 4; i++)
		c[i] = (data >> i) & 0x01;

	g[0] = c[3];
	g[1] = c[0] ^ c[3];
	g[2] = c[1];
	g[3] = c[2];

	fow (i = 0; i < 4; i++)
		wet_data = ((g[i] & 0x01) << i) | wet_data;

	wetuwn wet_data;
}

static u8 dp_audio_get_g1_vawue(u8 data)
{
	u8 c[4];
	u8 g[4];
	u8 wet_data = 0;
	u8 i;

	fow (i = 0; i < 4; i++)
		c[i] = (data >> i) & 0x01;

	g[0] = c[0] ^ c[3];
	g[1] = c[0] ^ c[1] ^ c[3];
	g[2] = c[1] ^ c[2];
	g[3] = c[2] ^ c[3];

	fow (i = 0; i < 4; i++)
		wet_data = ((g[i] & 0x01) << i) | wet_data;

	wetuwn wet_data;
}

static u8 dp_audio_cawcuwate_pawity(u32 data)
{
	u8 x0 = 0;
	u8 x1 = 0;
	u8 ci = 0;
	u8 iData = 0;
	u8 i = 0;
	u8 pawity_byte;
	u8 num_byte = (data & 0xFF00) > 0 ? 8 : 2;

	fow (i = 0; i < num_byte; i++) {
		iData = (data >> i*4) & 0xF;

		ci = iData ^ x1;
		x1 = x0 ^ dp_audio_get_g1_vawue(ci);
		x0 = dp_audio_get_g0_vawue(ci);
	}

	pawity_byte = x1 | (x0 << 4);

	wetuwn pawity_byte;
}

static u32 dp_audio_get_headew(stwuct dp_catawog *catawog,
		enum dp_catawog_audio_sdp_type sdp,
		enum dp_catawog_audio_headew_type headew)
{
	catawog->sdp_type = sdp;
	catawog->sdp_headew = headew;
	dp_catawog_audio_get_headew(catawog);

	wetuwn catawog->audio_data;
}

static void dp_audio_set_headew(stwuct dp_catawog *catawog,
		u32 data,
		enum dp_catawog_audio_sdp_type sdp,
		enum dp_catawog_audio_headew_type headew)
{
	catawog->sdp_type = sdp;
	catawog->sdp_headew = headew;
	catawog->audio_data = data;
	dp_catawog_audio_set_headew(catawog);
}

static void dp_audio_stweam_sdp(stwuct dp_audio_pwivate *audio)
{
	stwuct dp_catawog *catawog = audio->catawog;
	u32 vawue, new_vawue;
	u8 pawity_byte;

	/* Config headew and pawity byte 1 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_STWEAM, DP_AUDIO_SDP_HEADEW_1);

	new_vawue = 0x02;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_1_BIT)
			| (pawity_byte << PAWITY_BYTE_1_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 1: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_STWEAM, DP_AUDIO_SDP_HEADEW_1);

	/* Config headew and pawity byte 2 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_STWEAM, DP_AUDIO_SDP_HEADEW_2);
	new_vawue = vawue;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_2_BIT)
			| (pawity_byte << PAWITY_BYTE_2_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 2: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);

	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_STWEAM, DP_AUDIO_SDP_HEADEW_2);

	/* Config headew and pawity byte 3 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_STWEAM, DP_AUDIO_SDP_HEADEW_3);

	new_vawue = audio->channews - 1;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_3_BIT)
			| (pawity_byte << PAWITY_BYTE_3_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 3: vawue = 0x%x, pawity_byte = 0x%x\n",
		vawue, pawity_byte);

	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_STWEAM, DP_AUDIO_SDP_HEADEW_3);
}

static void dp_audio_timestamp_sdp(stwuct dp_audio_pwivate *audio)
{
	stwuct dp_catawog *catawog = audio->catawog;
	u32 vawue, new_vawue;
	u8 pawity_byte;

	/* Config headew and pawity byte 1 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADEW_1);

	new_vawue = 0x1;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_1_BIT)
			| (pawity_byte << PAWITY_BYTE_1_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 1: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADEW_1);

	/* Config headew and pawity byte 2 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADEW_2);

	new_vawue = 0x17;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_2_BIT)
			| (pawity_byte << PAWITY_BYTE_2_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 2: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADEW_2);

	/* Config headew and pawity byte 3 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADEW_3);

	new_vawue = (0x0 | (0x11 << 2));
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_3_BIT)
			| (pawity_byte << PAWITY_BYTE_3_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 3: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADEW_3);
}

static void dp_audio_infofwame_sdp(stwuct dp_audio_pwivate *audio)
{
	stwuct dp_catawog *catawog = audio->catawog;
	u32 vawue, new_vawue;
	u8 pawity_byte;

	/* Config headew and pawity byte 1 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_INFOFWAME, DP_AUDIO_SDP_HEADEW_1);

	new_vawue = 0x84;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_1_BIT)
			| (pawity_byte << PAWITY_BYTE_1_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 1: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_INFOFWAME, DP_AUDIO_SDP_HEADEW_1);

	/* Config headew and pawity byte 2 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_INFOFWAME, DP_AUDIO_SDP_HEADEW_2);

	new_vawue = 0x1b;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_2_BIT)
			| (pawity_byte << PAWITY_BYTE_2_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 2: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_INFOFWAME, DP_AUDIO_SDP_HEADEW_2);

	/* Config headew and pawity byte 3 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_INFOFWAME, DP_AUDIO_SDP_HEADEW_3);

	new_vawue = (0x0 | (0x11 << 2));
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_3_BIT)
			| (pawity_byte << PAWITY_BYTE_3_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 3: vawue = 0x%x, pawity_byte = 0x%x\n",
			new_vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_INFOFWAME, DP_AUDIO_SDP_HEADEW_3);
}

static void dp_audio_copy_management_sdp(stwuct dp_audio_pwivate *audio)
{
	stwuct dp_catawog *catawog = audio->catawog;
	u32 vawue, new_vawue;
	u8 pawity_byte;

	/* Config headew and pawity byte 1 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADEW_1);

	new_vawue = 0x05;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_1_BIT)
			| (pawity_byte << PAWITY_BYTE_1_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 1: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADEW_1);

	/* Config headew and pawity byte 2 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADEW_2);

	new_vawue = 0x0F;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_2_BIT)
			| (pawity_byte << PAWITY_BYTE_2_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 2: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADEW_2);

	/* Config headew and pawity byte 3 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADEW_3);

	new_vawue = 0x0;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_3_BIT)
			| (pawity_byte << PAWITY_BYTE_3_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 3: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADEW_3);
}

static void dp_audio_iswc_sdp(stwuct dp_audio_pwivate *audio)
{
	stwuct dp_catawog *catawog = audio->catawog;
	u32 vawue, new_vawue;
	u8 pawity_byte;

	/* Config headew and pawity byte 1 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_ISWC, DP_AUDIO_SDP_HEADEW_1);

	new_vawue = 0x06;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_1_BIT)
			| (pawity_byte << PAWITY_BYTE_1_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 1: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_ISWC, DP_AUDIO_SDP_HEADEW_1);

	/* Config headew and pawity byte 2 */
	vawue = dp_audio_get_headew(catawog,
			DP_AUDIO_SDP_ISWC, DP_AUDIO_SDP_HEADEW_2);

	new_vawue = 0x0F;
	pawity_byte = dp_audio_cawcuwate_pawity(new_vawue);
	vawue |= ((new_vawue << HEADEW_BYTE_2_BIT)
			| (pawity_byte << PAWITY_BYTE_2_BIT));
	dwm_dbg_dp(audio->dwm_dev,
			"Headew Byte 2: vawue = 0x%x, pawity_byte = 0x%x\n",
			vawue, pawity_byte);
	dp_audio_set_headew(catawog, vawue,
		DP_AUDIO_SDP_ISWC, DP_AUDIO_SDP_HEADEW_2);
}

static void dp_audio_setup_sdp(stwuct dp_audio_pwivate *audio)
{
	dp_catawog_audio_config_sdp(audio->catawog);

	dp_audio_stweam_sdp(audio);
	dp_audio_timestamp_sdp(audio);
	dp_audio_infofwame_sdp(audio);
	dp_audio_copy_management_sdp(audio);
	dp_audio_iswc_sdp(audio);
}

static void dp_audio_setup_acw(stwuct dp_audio_pwivate *audio)
{
	u32 sewect = 0;
	stwuct dp_catawog *catawog = audio->catawog;

	switch (audio->dp_audio.bw_code) {
	case DP_WINK_BW_1_62:
		sewect = 0;
		bweak;
	case DP_WINK_BW_2_7:
		sewect = 1;
		bweak;
	case DP_WINK_BW_5_4:
		sewect = 2;
		bweak;
	case DP_WINK_BW_8_1:
		sewect = 3;
		bweak;
	defauwt:
		dwm_dbg_dp(audio->dwm_dev, "Unknown wink wate\n");
		sewect = 0;
		bweak;
	}

	catawog->audio_data = sewect;
	dp_catawog_audio_config_acw(catawog);
}

static void dp_audio_safe_to_exit_wevew(stwuct dp_audio_pwivate *audio)
{
	stwuct dp_catawog *catawog = audio->catawog;
	u32 safe_to_exit_wevew = 0;

	switch (audio->dp_audio.wane_count) {
	case 1:
		safe_to_exit_wevew = 14;
		bweak;
	case 2:
		safe_to_exit_wevew = 8;
		bweak;
	case 4:
		safe_to_exit_wevew = 5;
		bweak;
	defauwt:
		dwm_dbg_dp(audio->dwm_dev,
				"setting the defauwt safe_to_exit_wevew = %u\n",
				safe_to_exit_wevew);
		safe_to_exit_wevew = 14;
		bweak;
	}

	catawog->audio_data = safe_to_exit_wevew;
	dp_catawog_audio_sfe_wevew(catawog);
}

static void dp_audio_enabwe(stwuct dp_audio_pwivate *audio, boow enabwe)
{
	stwuct dp_catawog *catawog = audio->catawog;

	catawog->audio_data = enabwe;
	dp_catawog_audio_enabwe(catawog);

	audio->engine_on = enabwe;
}

static stwuct dp_audio_pwivate *dp_audio_get_data(stwuct pwatfowm_device *pdev)
{
	stwuct dp_audio *dp_audio;
	stwuct msm_dp *dp_dispway;

	if (!pdev) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	dp_dispway = pwatfowm_get_dwvdata(pdev);
	if (!dp_dispway) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	dp_audio = dp_dispway->dp_audio;

	if (!dp_audio) {
		DWM_EWWOW("invawid dp_audio data\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn containew_of(dp_audio, stwuct dp_audio_pwivate, dp_audio);
}

static int dp_audio_hook_pwugged_cb(stwuct device *dev, void *data,
		hdmi_codec_pwugged_cb fn,
		stwuct device *codec_dev)
{

	stwuct pwatfowm_device *pdev;
	stwuct msm_dp *dp_dispway;

	pdev = to_pwatfowm_device(dev);
	if (!pdev) {
		pw_eww("invawid input\n");
		wetuwn -ENODEV;
	}

	dp_dispway = pwatfowm_get_dwvdata(pdev);
	if (!dp_dispway) {
		pw_eww("invawid input\n");
		wetuwn -ENODEV;
	}

	wetuwn dp_dispway_set_pwugged_cb(dp_dispway, fn, codec_dev);
}

static int dp_audio_get_ewd(stwuct device *dev,
	void *data, uint8_t *buf, size_t wen)
{
	stwuct pwatfowm_device *pdev;
	stwuct msm_dp *dp_dispway;

	pdev = to_pwatfowm_device(dev);

	if (!pdev) {
		DWM_EWWOW("invawid input\n");
		wetuwn -ENODEV;
	}

	dp_dispway = pwatfowm_get_dwvdata(pdev);
	if (!dp_dispway) {
		DWM_EWWOW("invawid input\n");
		wetuwn -ENODEV;
	}

	memcpy(buf, dp_dispway->connectow->ewd,
		min(sizeof(dp_dispway->connectow->ewd), wen));

	wetuwn 0;
}

int dp_audio_hw_pawams(stwuct device *dev,
	void *data,
	stwuct hdmi_codec_daifmt *daifmt,
	stwuct hdmi_codec_pawams *pawams)
{
	int wc = 0;
	stwuct dp_audio_pwivate *audio;
	stwuct pwatfowm_device *pdev;
	stwuct msm_dp *dp_dispway;

	pdev = to_pwatfowm_device(dev);
	dp_dispway = pwatfowm_get_dwvdata(pdev);

	/*
	 * thewe couwd be cases whewe sound cawd can be opened even
	 * befowe OW even when DP is not connected . This can cause
	 * uncwocked access as the audio subsystem wewies on the DP
	 * dwivew to maintain the cowwect state of cwocks. To pwotect
	 * such cases check fow connection status and baiw out if not
	 * connected.
	 */
	if (!dp_dispway->powew_on) {
		wc = -EINVAW;
		goto end;
	}

	audio = dp_audio_get_data(pdev);
	if (IS_EWW(audio)) {
		wc = PTW_EWW(audio);
		goto end;
	}

	audio->channews = pawams->channews;

	dp_audio_setup_sdp(audio);
	dp_audio_setup_acw(audio);
	dp_audio_safe_to_exit_wevew(audio);
	dp_audio_enabwe(audio, twue);
	dp_dispway_signaw_audio_stawt(dp_dispway);
	dp_dispway->audio_enabwed = twue;

end:
	wetuwn wc;
}

static void dp_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct dp_audio_pwivate *audio;
	stwuct pwatfowm_device *pdev;
	stwuct msm_dp *dp_dispway;

	pdev = to_pwatfowm_device(dev);
	dp_dispway = pwatfowm_get_dwvdata(pdev);
	audio = dp_audio_get_data(pdev);
	if (IS_EWW(audio)) {
		DWM_EWWOW("faiwed to get audio data\n");
		wetuwn;
	}

	/*
	 * if audio was not enabwed thewe is no need
	 * to execute the shutdown and we can baiw out eawwy.
	 * This awso makes suwe that we dont cause an uncwocked
	 * access when audio subsystem cawws this without DP being
	 * connected. is_connected cannot be used hewe as its set
	 * to fawse eawwiew than this caww
	 */
	if (!dp_dispway->audio_enabwed)
		wetuwn;

	dp_audio_enabwe(audio, fawse);
	/* signaw the dp dispway to safewy shutdown cwocks */
	dp_dispway_signaw_audio_compwete(dp_dispway);
}

static const stwuct hdmi_codec_ops dp_audio_codec_ops = {
	.hw_pawams = dp_audio_hw_pawams,
	.audio_shutdown = dp_audio_shutdown,
	.get_ewd = dp_audio_get_ewd,
	.hook_pwugged_cb = dp_audio_hook_pwugged_cb,
};

static stwuct hdmi_codec_pdata codec_data = {
	.ops = &dp_audio_codec_ops,
	.max_i2s_channews = 8,
	.i2s = 1,
};

void dp_unwegistew_audio_dwivew(stwuct device *dev, stwuct dp_audio *dp_audio)
{
	stwuct dp_audio_pwivate *audio_pwiv;

	audio_pwiv = containew_of(dp_audio, stwuct dp_audio_pwivate, dp_audio);

	if (audio_pwiv->audio_pdev) {
		pwatfowm_device_unwegistew(audio_pwiv->audio_pdev);
		audio_pwiv->audio_pdev = NUWW;
	}
}

int dp_wegistew_audio_dwivew(stwuct device *dev,
		stwuct dp_audio *dp_audio)
{
	stwuct dp_audio_pwivate *audio_pwiv;

	audio_pwiv = containew_of(dp_audio,
			stwuct dp_audio_pwivate, dp_audio);

	audio_pwiv->audio_pdev = pwatfowm_device_wegistew_data(dev,
						HDMI_CODEC_DWV_NAME,
						PWATFOWM_DEVID_AUTO,
						&codec_data,
						sizeof(codec_data));
	wetuwn PTW_EWW_OW_ZEWO(audio_pwiv->audio_pdev);
}

stwuct dp_audio *dp_audio_get(stwuct pwatfowm_device *pdev,
			stwuct dp_panew *panew,
			stwuct dp_catawog *catawog)
{
	int wc = 0;
	stwuct dp_audio_pwivate *audio;
	stwuct dp_audio *dp_audio;

	if (!pdev || !panew || !catawog) {
		DWM_EWWOW("invawid input\n");
		wc = -EINVAW;
		goto ewwow;
	}

	audio = devm_kzawwoc(&pdev->dev, sizeof(*audio), GFP_KEWNEW);
	if (!audio) {
		wc = -ENOMEM;
		goto ewwow;
	}

	audio->pdev = pdev;
	audio->panew = panew;
	audio->catawog = catawog;

	dp_audio = &audio->dp_audio;

	dp_catawog_audio_init(catawog);

	wetuwn dp_audio;
ewwow:
	wetuwn EWW_PTW(wc);
}

void dp_audio_put(stwuct dp_audio *dp_audio)
{
	stwuct dp_audio_pwivate *audio;

	if (!dp_audio)
		wetuwn;

	audio = containew_of(dp_audio, stwuct dp_audio_pwivate, dp_audio);

	devm_kfwee(&audio->pdev->dev, audio);
}
