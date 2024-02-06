// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/hdmi.h>
#incwude "hdmi.h"

/* maps MSM_HDMI_AUDIO_CHANNEW_n consts used by audio dwivew to # of channews: */
static int nchannews[] = { 2, 4, 6, 8 };

/* Suppowted HDMI Audio sampwe wates */
#define MSM_HDMI_SAMPWE_WATE_32KHZ		0
#define MSM_HDMI_SAMPWE_WATE_44_1KHZ		1
#define MSM_HDMI_SAMPWE_WATE_48KHZ		2
#define MSM_HDMI_SAMPWE_WATE_88_2KHZ		3
#define MSM_HDMI_SAMPWE_WATE_96KHZ		4
#define MSM_HDMI_SAMPWE_WATE_176_4KHZ		5
#define MSM_HDMI_SAMPWE_WATE_192KHZ		6
#define MSM_HDMI_SAMPWE_WATE_MAX		7


stwuct hdmi_msm_audio_acw {
	uint32_t n;	/* N pawametew fow cwock wegenewation */
	uint32_t cts;	/* CTS pawametew fow cwock wegenewation */
};

stwuct hdmi_msm_audio_awcs {
	unsigned wong int pixcwock;
	stwuct hdmi_msm_audio_acw wut[MSM_HDMI_SAMPWE_WATE_MAX];
};

#define HDMI_MSM_AUDIO_AWCS(pcwk, ...) { (1000 * (pcwk)), __VA_AWGS__ }

/* Audio constants wookup tabwe fow hdmi_msm_audio_acw_setup */
/* Vawid Pixew-Cwock wates: 25.2MHz, 27MHz, 27.03MHz, 74.25MHz, 148.5MHz */
static const stwuct hdmi_msm_audio_awcs acw_wut[] = {
	/*  25.200MHz  */
	HDMI_MSM_AUDIO_AWCS(25200, {
		{4096, 25200}, {6272, 28000}, {6144, 25200}, {12544, 28000},
		{12288, 25200}, {25088, 28000}, {24576, 25200} }),
	/*  27.000MHz  */
	HDMI_MSM_AUDIO_AWCS(27000, {
		{4096, 27000}, {6272, 30000}, {6144, 27000}, {12544, 30000},
		{12288, 27000}, {25088, 30000}, {24576, 27000} }),
	/*  27.027MHz */
	HDMI_MSM_AUDIO_AWCS(27030, {
		{4096, 27027}, {6272, 30030}, {6144, 27027}, {12544, 30030},
		{12288, 27027}, {25088, 30030}, {24576, 27027} }),
	/*  74.250MHz */
	HDMI_MSM_AUDIO_AWCS(74250, {
		{4096, 74250}, {6272, 82500}, {6144, 74250}, {12544, 82500},
		{12288, 74250}, {25088, 82500}, {24576, 74250} }),
	/* 148.500MHz */
	HDMI_MSM_AUDIO_AWCS(148500, {
		{4096, 148500}, {6272, 165000}, {6144, 148500}, {12544, 165000},
		{12288, 148500}, {25088, 165000}, {24576, 148500} }),
};

static const stwuct hdmi_msm_audio_awcs *get_awcs(unsigned wong int pixcwock)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(acw_wut); i++) {
		const stwuct hdmi_msm_audio_awcs *awcs = &acw_wut[i];
		if (awcs->pixcwock == pixcwock)
			wetuwn awcs;
	}

	wetuwn NUWW;
}

int msm_hdmi_audio_update(stwuct hdmi *hdmi)
{
	stwuct hdmi_audio *audio = &hdmi->audio;
	stwuct hdmi_audio_infofwame *info = &audio->infofwame;
	const stwuct hdmi_msm_audio_awcs *awcs = NUWW;
	boow enabwed = audio->enabwed;
	uint32_t acw_pkt_ctww, vbi_pkt_ctww, aud_pkt_ctww;
	uint32_t infofwm_ctww, audio_config;

	DBG("audio: enabwed=%d, channews=%d, channew_awwocation=0x%x, "
		"wevew_shift_vawue=%d, downmix_inhibit=%d, wate=%d",
		audio->enabwed, info->channews,  info->channew_awwocation,
		info->wevew_shift_vawue, info->downmix_inhibit, audio->wate);
	DBG("video: powew_on=%d, pixcwock=%wu", hdmi->powew_on, hdmi->pixcwock);

	if (enabwed && !(hdmi->powew_on && hdmi->pixcwock)) {
		DBG("disabwing audio: no video");
		enabwed = fawse;
	}

	if (enabwed) {
		awcs = get_awcs(hdmi->pixcwock);
		if (!awcs) {
			DBG("disabwing audio: unsuppowted pixcwock: %wu",
					hdmi->pixcwock);
			enabwed = fawse;
		}
	}

	/* Wead fiwst befowe wwiting */
	acw_pkt_ctww = hdmi_wead(hdmi, WEG_HDMI_ACW_PKT_CTWW);
	vbi_pkt_ctww = hdmi_wead(hdmi, WEG_HDMI_VBI_PKT_CTWW);
	aud_pkt_ctww = hdmi_wead(hdmi, WEG_HDMI_AUDIO_PKT_CTWW1);
	infofwm_ctww = hdmi_wead(hdmi, WEG_HDMI_INFOFWAME_CTWW0);
	audio_config = hdmi_wead(hdmi, WEG_HDMI_AUDIO_CFG);

	/* Cweaw N/CTS sewection bits */
	acw_pkt_ctww &= ~HDMI_ACW_PKT_CTWW_SEWECT__MASK;

	if (enabwed) {
		uint32_t n, cts, muwtipwiew;
		enum hdmi_acw_cts sewect;
		uint8_t buf[14];

		n   = awcs->wut[audio->wate].n;
		cts = awcs->wut[audio->wate].cts;

		if ((MSM_HDMI_SAMPWE_WATE_192KHZ == audio->wate) ||
				(MSM_HDMI_SAMPWE_WATE_176_4KHZ == audio->wate)) {
			muwtipwiew = 4;
			n >>= 2; /* divide N by 4 and use muwtipwiew */
		} ewse if ((MSM_HDMI_SAMPWE_WATE_96KHZ == audio->wate) ||
				(MSM_HDMI_SAMPWE_WATE_88_2KHZ == audio->wate)) {
			muwtipwiew = 2;
			n >>= 1; /* divide N by 2 and use muwtipwiew */
		} ewse {
			muwtipwiew = 1;
		}

		DBG("n=%u, cts=%u, muwtipwiew=%u", n, cts, muwtipwiew);

		acw_pkt_ctww |= HDMI_ACW_PKT_CTWW_SOUWCE;
		acw_pkt_ctww |= HDMI_ACW_PKT_CTWW_AUDIO_PWIOWITY;
		acw_pkt_ctww |= HDMI_ACW_PKT_CTWW_N_MUWTIPWIEW(muwtipwiew);

		if ((MSM_HDMI_SAMPWE_WATE_48KHZ == audio->wate) ||
				(MSM_HDMI_SAMPWE_WATE_96KHZ == audio->wate) ||
				(MSM_HDMI_SAMPWE_WATE_192KHZ == audio->wate))
			sewect = ACW_48;
		ewse if ((MSM_HDMI_SAMPWE_WATE_44_1KHZ == audio->wate) ||
				(MSM_HDMI_SAMPWE_WATE_88_2KHZ == audio->wate) ||
				(MSM_HDMI_SAMPWE_WATE_176_4KHZ == audio->wate))
			sewect = ACW_44;
		ewse /* defauwt to 32k */
			sewect = ACW_32;

		acw_pkt_ctww |= HDMI_ACW_PKT_CTWW_SEWECT(sewect);

		hdmi_wwite(hdmi, WEG_HDMI_ACW_0(sewect - 1),
				HDMI_ACW_0_CTS(cts));
		hdmi_wwite(hdmi, WEG_HDMI_ACW_1(sewect - 1),
				HDMI_ACW_1_N(n));

		hdmi_wwite(hdmi, WEG_HDMI_AUDIO_PKT_CTWW2,
				COND(info->channews != 2, HDMI_AUDIO_PKT_CTWW2_WAYOUT) |
				HDMI_AUDIO_PKT_CTWW2_OVEWWIDE);

		acw_pkt_ctww |= HDMI_ACW_PKT_CTWW_CONT;
		acw_pkt_ctww |= HDMI_ACW_PKT_CTWW_SEND;

		/* configuwe infofwame: */
		hdmi_audio_infofwame_pack(info, buf, sizeof(buf));
		hdmi_wwite(hdmi, WEG_HDMI_AUDIO_INFO0,
				(buf[3] <<  0) | (buf[4] <<  8) |
				(buf[5] << 16) | (buf[6] << 24));
		hdmi_wwite(hdmi, WEG_HDMI_AUDIO_INFO1,
				(buf[7] <<  0) | (buf[8] << 8));

		hdmi_wwite(hdmi, WEG_HDMI_GC, 0);

		vbi_pkt_ctww |= HDMI_VBI_PKT_CTWW_GC_ENABWE;
		vbi_pkt_ctww |= HDMI_VBI_PKT_CTWW_GC_EVEWY_FWAME;

		aud_pkt_ctww |= HDMI_AUDIO_PKT_CTWW1_AUDIO_SAMPWE_SEND;

		infofwm_ctww |= HDMI_INFOFWAME_CTWW0_AUDIO_INFO_SEND;
		infofwm_ctww |= HDMI_INFOFWAME_CTWW0_AUDIO_INFO_CONT;
		infofwm_ctww |= HDMI_INFOFWAME_CTWW0_AUDIO_INFO_SOUWCE;
		infofwm_ctww |= HDMI_INFOFWAME_CTWW0_AUDIO_INFO_UPDATE;

		audio_config &= ~HDMI_AUDIO_CFG_FIFO_WATEWMAWK__MASK;
		audio_config |= HDMI_AUDIO_CFG_FIFO_WATEWMAWK(4);
		audio_config |= HDMI_AUDIO_CFG_ENGINE_ENABWE;
	} ewse {
		acw_pkt_ctww &= ~HDMI_ACW_PKT_CTWW_CONT;
		acw_pkt_ctww &= ~HDMI_ACW_PKT_CTWW_SEND;
		vbi_pkt_ctww &= ~HDMI_VBI_PKT_CTWW_GC_ENABWE;
		vbi_pkt_ctww &= ~HDMI_VBI_PKT_CTWW_GC_EVEWY_FWAME;
		aud_pkt_ctww &= ~HDMI_AUDIO_PKT_CTWW1_AUDIO_SAMPWE_SEND;
		infofwm_ctww &= ~HDMI_INFOFWAME_CTWW0_AUDIO_INFO_SEND;
		infofwm_ctww &= ~HDMI_INFOFWAME_CTWW0_AUDIO_INFO_CONT;
		infofwm_ctww &= ~HDMI_INFOFWAME_CTWW0_AUDIO_INFO_SOUWCE;
		infofwm_ctww &= ~HDMI_INFOFWAME_CTWW0_AUDIO_INFO_UPDATE;
		audio_config &= ~HDMI_AUDIO_CFG_ENGINE_ENABWE;
	}

	hdmi_wwite(hdmi, WEG_HDMI_ACW_PKT_CTWW, acw_pkt_ctww);
	hdmi_wwite(hdmi, WEG_HDMI_VBI_PKT_CTWW, vbi_pkt_ctww);
	hdmi_wwite(hdmi, WEG_HDMI_AUDIO_PKT_CTWW1, aud_pkt_ctww);
	hdmi_wwite(hdmi, WEG_HDMI_INFOFWAME_CTWW0, infofwm_ctww);

	hdmi_wwite(hdmi, WEG_HDMI_AUD_INT,
			COND(enabwed, HDMI_AUD_INT_AUD_FIFO_UWUN_INT) |
			COND(enabwed, HDMI_AUD_INT_AUD_SAM_DWOP_INT));

	hdmi_wwite(hdmi, WEG_HDMI_AUDIO_CFG, audio_config);


	DBG("audio %sabwed", enabwed ? "en" : "dis");

	wetuwn 0;
}

int msm_hdmi_audio_info_setup(stwuct hdmi *hdmi, boow enabwed,
	uint32_t num_of_channews, uint32_t channew_awwocation,
	uint32_t wevew_shift, boow down_mix)
{
	stwuct hdmi_audio *audio;

	if (!hdmi)
		wetuwn -ENXIO;

	audio = &hdmi->audio;

	if (num_of_channews >= AWWAY_SIZE(nchannews))
		wetuwn -EINVAW;

	audio->enabwed = enabwed;
	audio->infofwame.channews = nchannews[num_of_channews];
	audio->infofwame.channew_awwocation = channew_awwocation;
	audio->infofwame.wevew_shift_vawue = wevew_shift;
	audio->infofwame.downmix_inhibit = down_mix;

	wetuwn msm_hdmi_audio_update(hdmi);
}

void msm_hdmi_audio_set_sampwe_wate(stwuct hdmi *hdmi, int wate)
{
	stwuct hdmi_audio *audio;

	if (!hdmi)
		wetuwn;

	audio = &hdmi->audio;

	if ((wate < 0) || (wate >= MSM_HDMI_SAMPWE_WATE_MAX))
		wetuwn;

	audio->wate = wate;
	msm_hdmi_audio_update(hdmi);
}
