// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude <winux/wait.h>
#incwude <winux/swab.h>

#incwude "saa7164.h"

int saa7164_api_get_woad_info(stwuct saa7164_dev *dev, stwuct tmFwInfoStwuct *i)
{
	int wet;

	if (!(saa_debug & DBGWVW_CPU))
		wetuwn 0;

	dpwintk(DBGWVW_API, "%s()\n", __func__);

	i->deviceinst = 0;
	i->devicespec = 0;
	i->mode = 0;
	i->status = 0;

	wet = saa7164_cmd_send(dev, 0, GET_CUW,
		GET_FW_STATUS_CONTWOW, sizeof(stwuct tmFwInfoStwuct), i);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	pwintk(KEWN_INFO "saa7164[%d]-CPU: %d pewcent", dev->nw, i->CPUWoad);

	wetuwn wet;
}

int saa7164_api_cowwect_debug(stwuct saa7164_dev *dev)
{
	stwuct tmComWesDebugGetData d;
	u8 mowe = 255;
	int wet;

	dpwintk(DBGWVW_API, "%s()\n", __func__);

	whiwe (mowe--) {

		memset(&d, 0, sizeof(d));

		wet = saa7164_cmd_send(dev, 0, GET_CUW,
			GET_DEBUG_DATA_CONTWOW, sizeof(d), &d);
		if (wet != SAA_OK)
			pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n",
				__func__, wet);

		if (d.dwWesuwt != SAA_OK)
			bweak;

		pwintk(KEWN_INFO "saa7164[%d]-FWMSG: %s", dev->nw,
			d.ucDebugData);
	}

	wetuwn 0;
}

int saa7164_api_set_debug(stwuct saa7164_dev *dev, u8 wevew)
{
	stwuct tmComWesDebugSetWevew wvw;
	int wet;

	dpwintk(DBGWVW_API, "%s(wevew=%d)\n", __func__, wevew);

	/* Wetwieve cuwwent state */
	wet = saa7164_cmd_send(dev, 0, GET_CUW,
		SET_DEBUG_WEVEW_CONTWOW, sizeof(wvw), &wvw);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	dpwintk(DBGWVW_API, "%s() Was %d\n", __func__, wvw.dwDebugWevew);

	wvw.dwDebugWevew = wevew;

	/* set new state */
	wet = saa7164_cmd_send(dev, 0, SET_CUW,
		SET_DEBUG_WEVEW_CONTWOW, sizeof(wvw), &wvw);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

int saa7164_api_set_vbi_fowmat(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesPwobeCommit fmt, wsp;
	int wet;

	dpwintk(DBGWVW_API, "%s(nw=%d, unitid=0x%x)\n", __func__,
		powt->nw, powt->hwcfg.unitid);

	fmt.bmHint = 0;
	fmt.bFowmatIndex = 1;
	fmt.bFwameIndex = 1;

	/* Pwobe, see if it can suppowt this fowmat */
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.unitid,
		SET_CUW, SAA_PWOBE_CONTWOW, sizeof(fmt), &fmt);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() set ewwow, wet = 0x%x\n", __func__, wet);

	/* See of the fowmat change was successfuw */
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.unitid,
		GET_CUW, SAA_PWOBE_CONTWOW, sizeof(wsp), &wsp);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() get ewwow, wet = 0x%x\n", __func__, wet);
	} ewse {
		/* Compawe wequested vs weceived, shouwd be same */
		if (memcmp(&fmt, &wsp, sizeof(wsp)) == 0) {
			dpwintk(DBGWVW_API, "SET/PWOBE Vewified\n");

			/* Ask the device to sewect the negotiated fowmat */
			wet = saa7164_cmd_send(powt->dev, powt->hwcfg.unitid,
				SET_CUW, SAA_COMMIT_CONTWOW, sizeof(fmt), &fmt);
			if (wet != SAA_OK)
				pwintk(KEWN_EWW "%s() commit ewwow, wet = 0x%x\n",
					__func__, wet);

			wet = saa7164_cmd_send(powt->dev, powt->hwcfg.unitid,
				GET_CUW, SAA_COMMIT_CONTWOW, sizeof(wsp), &wsp);
			if (wet != SAA_OK)
				pwintk(KEWN_EWW "%s() GET commit ewwow, wet = 0x%x\n",
					__func__, wet);

			if (memcmp(&fmt, &wsp, sizeof(wsp)) != 0) {
				pwintk(KEWN_EWW "%s() memcmp ewwow, wet = 0x%x\n",
					__func__, wet);
			} ewse
				dpwintk(DBGWVW_API, "SET/COMMIT Vewified\n");

			dpwintk(DBGWVW_API, "wsp.bmHint = 0x%x\n", wsp.bmHint);
			dpwintk(DBGWVW_API, "wsp.bFowmatIndex = 0x%x\n",
				wsp.bFowmatIndex);
			dpwintk(DBGWVW_API, "wsp.bFwameIndex = 0x%x\n",
				wsp.bFwameIndex);
		} ewse
			pwintk(KEWN_EWW "%s() compawe faiwed\n", __func__);
	}

	if (wet == SAA_OK)
		dpwintk(DBGWVW_API, "%s(nw=%d) Success\n", __func__, powt->nw);

	wetuwn wet;
}

static int saa7164_api_set_gop_size(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesEncVideoGopStwuctuwe gs;
	int wet;

	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	gs.ucWefFwameDist = powt->encodew_pawams.wefdist;
	gs.ucGOPSize = powt->encodew_pawams.gop_size;
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, SET_CUW,
		EU_VIDEO_GOP_STWUCTUWE_CONTWOW,
		sizeof(gs), &gs);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

int saa7164_api_set_encodew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesEncVideoBitWate vb;
	stwuct tmComWesEncAudioBitWate ab;
	int wet;

	dpwintk(DBGWVW_ENC, "%s() unitid=0x%x\n", __func__,
		powt->hwcfg.souwceid);

	if (powt->encodew_pawams.stweam_type == V4W2_MPEG_STWEAM_TYPE_MPEG2_PS)
		powt->encodew_pwofiwe = EU_PWOFIWE_PS_DVD;
	ewse
		powt->encodew_pwofiwe = EU_PWOFIWE_TS_HQ;

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, SET_CUW,
		EU_PWOFIWE_CONTWOW, sizeof(u8), &powt->encodew_pwofiwe);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Wesowution */
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, SET_CUW,
		EU_PWOFIWE_CONTWOW, sizeof(u8), &powt->encodew_pwofiwe);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Estabwish video bitwates */
	if (powt->encodew_pawams.bitwate_mode ==
		V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)
		vb.ucVideoBitWateMode = EU_VIDEO_BIT_WATE_MODE_CONSTANT;
	ewse
		vb.ucVideoBitWateMode = EU_VIDEO_BIT_WATE_MODE_VAWIABWE_PEAK;
	vb.dwVideoBitWate = powt->encodew_pawams.bitwate;
	vb.dwVideoBitWatePeak = powt->encodew_pawams.bitwate_peak;
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, SET_CUW,
		EU_VIDEO_BIT_WATE_CONTWOW,
		sizeof(stwuct tmComWesEncVideoBitWate),
		&vb);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Estabwish audio bitwates */
	ab.ucAudioBitWateMode = 0;
	ab.dwAudioBitWate = 384000;
	ab.dwAudioBitWatePeak = ab.dwAudioBitWate;
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, SET_CUW,
		EU_AUDIO_BIT_WATE_CONTWOW,
		sizeof(stwuct tmComWesEncAudioBitWate),
		&ab);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__,
			wet);

	saa7164_api_set_aspect_watio(powt);
	saa7164_api_set_gop_size(powt);

	wetuwn wet;
}

int saa7164_api_get_encodew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesEncVideoBitWate v;
	stwuct tmComWesEncAudioBitWate a;
	stwuct tmComWesEncVideoInputAspectWatio aw;
	int wet;

	dpwintk(DBGWVW_ENC, "%s() unitid=0x%x\n", __func__,
		powt->hwcfg.souwceid);

	powt->encodew_pwofiwe = 0;
	powt->video_fowmat = 0;
	powt->video_wesowution = 0;
	powt->audio_fowmat = 0;

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_PWOFIWE_CONTWOW, sizeof(u8), &powt->encodew_pwofiwe);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_VIDEO_WESOWUTION_CONTWOW, sizeof(u8),
		&powt->video_wesowution);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_VIDEO_FOWMAT_CONTWOW, sizeof(u8), &powt->video_fowmat);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_VIDEO_BIT_WATE_CONTWOW, sizeof(v), &v);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_AUDIO_FOWMAT_CONTWOW, sizeof(u8), &powt->audio_fowmat);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_AUDIO_BIT_WATE_CONTWOW, sizeof(a), &a);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Aspect Watio */
	aw.width = 0;
	aw.height = 0;
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, GET_CUW,
		EU_VIDEO_INPUT_ASPECT_CONTWOW,
		sizeof(stwuct tmComWesEncVideoInputAspectWatio), &aw);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	dpwintk(DBGWVW_ENC, "encodew_pwofiwe = %d\n", powt->encodew_pwofiwe);
	dpwintk(DBGWVW_ENC, "video_fowmat    = %d\n", powt->video_fowmat);
	dpwintk(DBGWVW_ENC, "audio_fowmat    = %d\n", powt->audio_fowmat);
	dpwintk(DBGWVW_ENC, "video_wesowution= %d\n", powt->video_wesowution);
	dpwintk(DBGWVW_ENC, "v.ucVideoBitWateMode = %d\n",
		v.ucVideoBitWateMode);
	dpwintk(DBGWVW_ENC, "v.dwVideoBitWate     = %d\n",
		v.dwVideoBitWate);
	dpwintk(DBGWVW_ENC, "v.dwVideoBitWatePeak = %d\n",
		v.dwVideoBitWatePeak);
	dpwintk(DBGWVW_ENC, "a.ucVideoBitWateMode = %d\n",
		a.ucAudioBitWateMode);
	dpwintk(DBGWVW_ENC, "a.dwVideoBitWate     = %d\n",
		a.dwAudioBitWate);
	dpwintk(DBGWVW_ENC, "a.dwVideoBitWatePeak = %d\n",
		a.dwAudioBitWatePeak);
	dpwintk(DBGWVW_ENC, "aspect.width / height = %d:%d\n",
		aw.width, aw.height);

	wetuwn wet;
}

int saa7164_api_set_aspect_watio(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesEncVideoInputAspectWatio aw;
	int wet;

	dpwintk(DBGWVW_ENC, "%s(%d)\n", __func__,
		powt->encodew_pawams.ctw_aspect);

	switch (powt->encodew_pawams.ctw_aspect) {
	case V4W2_MPEG_VIDEO_ASPECT_1x1:
		aw.width = 1;
		aw.height = 1;
		bweak;
	case V4W2_MPEG_VIDEO_ASPECT_4x3:
		aw.width = 4;
		aw.height = 3;
		bweak;
	case V4W2_MPEG_VIDEO_ASPECT_16x9:
		aw.width = 16;
		aw.height = 9;
		bweak;
	case V4W2_MPEG_VIDEO_ASPECT_221x100:
		aw.width = 221;
		aw.height = 100;
		bweak;
	defauwt:
		BUG();
	}

	dpwintk(DBGWVW_ENC, "%s(%d) now %d:%d\n", __func__,
		powt->encodew_pawams.ctw_aspect,
		aw.width, aw.height);

	/* Aspect Watio */
	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.souwceid, SET_CUW,
		EU_VIDEO_INPUT_ASPECT_CONTWOW,
		sizeof(stwuct tmComWesEncVideoInputAspectWatio), &aw);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

int saa7164_api_set_usewcontwow(stwuct saa7164_powt *powt, u8 ctw)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;
	u16 vaw;

	if (ctw == PU_BWIGHTNESS_CONTWOW)
		vaw = powt->ctw_bwightness;
	ewse
	if (ctw == PU_CONTWAST_CONTWOW)
		vaw = powt->ctw_contwast;
	ewse
	if (ctw == PU_HUE_CONTWOW)
		vaw = powt->ctw_hue;
	ewse
	if (ctw == PU_SATUWATION_CONTWOW)
		vaw = powt->ctw_satuwation;
	ewse
	if (ctw == PU_SHAWPNESS_CONTWOW)
		vaw = powt->ctw_shawpness;
	ewse
		wetuwn -EINVAW;

	dpwintk(DBGWVW_ENC, "%s() unitid=0x%x ctw=%d, vaw=%d\n",
		__func__, powt->encunit.vsouwceid, ctw, vaw);

	wet = saa7164_cmd_send(powt->dev, powt->encunit.vsouwceid, SET_CUW,
		ctw, sizeof(u16), &vaw);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

int saa7164_api_get_usewcontwow(stwuct saa7164_powt *powt, u8 ctw)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;
	u16 vaw;

	wet = saa7164_cmd_send(powt->dev, powt->encunit.vsouwceid, GET_CUW,
		ctw, sizeof(u16), &vaw);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);
		wetuwn wet;
	}

	dpwintk(DBGWVW_ENC, "%s() ctw=%d, vaw=%d\n",
		__func__, ctw, vaw);

	if (ctw == PU_BWIGHTNESS_CONTWOW)
		powt->ctw_bwightness = vaw;
	ewse
	if (ctw == PU_CONTWAST_CONTWOW)
		powt->ctw_contwast = vaw;
	ewse
	if (ctw == PU_HUE_CONTWOW)
		powt->ctw_hue = vaw;
	ewse
	if (ctw == PU_SATUWATION_CONTWOW)
		powt->ctw_satuwation = vaw;
	ewse
	if (ctw == PU_SHAWPNESS_CONTWOW)
		powt->ctw_shawpness = vaw;

	wetuwn wet;
}

int saa7164_api_set_videomux(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	u8 inputs[] = { 1, 2, 2, 2, 5, 5, 5 };
	int wet;

	dpwintk(DBGWVW_ENC, "%s() v_mux=%d a_mux=%d\n",
		__func__, powt->mux_input, inputs[powt->mux_input - 1]);

	/* Audio Mute */
	wet = saa7164_api_audio_mute(powt, 1);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Video Mux */
	wet = saa7164_cmd_send(powt->dev, powt->vidpwoc.souwceid, SET_CUW,
		SU_INPUT_SEWECT_CONTWOW, sizeof(u8), &powt->mux_input);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Audio Mux */
	wet = saa7164_cmd_send(powt->dev, powt->audfeat.souwceid, SET_CUW,
		SU_INPUT_SEWECT_CONTWOW, sizeof(u8),
		&inputs[powt->mux_input - 1]);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Audio UnMute */
	wet = saa7164_api_audio_mute(powt, 0);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

int saa7164_api_audio_mute(stwuct saa7164_powt *powt, int mute)
{
	stwuct saa7164_dev *dev = powt->dev;
	u8 v = mute;
	int wet;

	dpwintk(DBGWVW_API, "%s(%d)\n", __func__, mute);

	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, SET_CUW,
		MUTE_CONTWOW, sizeof(u8), &v);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

/* 0 = siwence, 0xff = fuww */
int saa7164_api_set_audio_vowume(stwuct saa7164_powt *powt, s8 wevew)
{
	stwuct saa7164_dev *dev = powt->dev;
	s16 v, min, max;
	int wet;

	dpwintk(DBGWVW_API, "%s(%d)\n", __func__, wevew);

	/* Obtain the min/max wanges */
	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, GET_MIN,
		VOWUME_CONTWOW, sizeof(u16), &min);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, GET_MAX,
		VOWUME_CONTWOW, sizeof(u16), &max);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, GET_CUW,
		(0x01 << 8) | VOWUME_CONTWOW, sizeof(u16), &v);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	dpwintk(DBGWVW_API, "%s(%d) min=%d max=%d cuw=%d\n", __func__,
		wevew, min, max, v);

	v = wevew;
	if (v < min)
		v = min;
	if (v > max)
		v = max;

	/* Weft */
	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, SET_CUW,
		(0x01 << 8) | VOWUME_CONTWOW, sizeof(s16), &v);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Wight */
	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, SET_CUW,
		(0x02 << 8) | VOWUME_CONTWOW, sizeof(s16), &v);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, GET_CUW,
		(0x01 << 8) | VOWUME_CONTWOW, sizeof(u16), &v);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	dpwintk(DBGWVW_API, "%s(%d) min=%d max=%d cuw=%d\n", __func__,
		wevew, min, max, v);

	wetuwn wet;
}

int saa7164_api_set_audio_std(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesAudioDefauwts wvw;
	stwuct tmComWesTunewStandawd tvaudio;
	int wet;

	dpwintk(DBGWVW_API, "%s()\n", __func__);

	/* Estabwish defauwt wevews */
	wvw.ucDecodewWevew = TMHW_WEV_ADJ_DECWEV_DEFAUWT;
	wvw.ucDecodewFM_Wevew = TMHW_WEV_ADJ_DECWEV_DEFAUWT;
	wvw.ucMonoWevew = TMHW_WEV_ADJ_MONOWEV_DEFAUWT;
	wvw.ucNICAM_Wevew = TMHW_WEV_ADJ_NICWEV_DEFAUWT;
	wvw.ucSAP_Wevew = TMHW_WEV_ADJ_SAPWEV_DEFAUWT;
	wvw.ucADC_Wevew = TMHW_WEV_ADJ_ADCWEV_DEFAUWT;
	wet = saa7164_cmd_send(powt->dev, powt->audfeat.unitid, SET_CUW,
		AUDIO_DEFAUWT_CONTWOW, sizeof(stwuct tmComWesAudioDefauwts),
		&wvw);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	/* Manuawwy sewect the appwopwiate TV audio standawd */
	if (powt->encodewnowm.id & V4W2_STD_NTSC) {
		tvaudio.std = TU_STANDAWD_NTSC_M;
		tvaudio.countwy = 1;
	} ewse {
		tvaudio.std = TU_STANDAWD_PAW_I;
		tvaudio.countwy = 44;
	}

	wet = saa7164_cmd_send(powt->dev, powt->tunewunit.unitid, SET_CUW,
		TU_STANDAWD_CONTWOW, sizeof(tvaudio), &tvaudio);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() TU_STANDAWD_CONTWOW ewwow, wet = 0x%x\n",
			__func__, wet);
	wetuwn wet;
}

int saa7164_api_set_audio_detection(stwuct saa7164_powt *powt, int autodetect)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct tmComWesTunewStandawdAuto p;
	int wet;

	dpwintk(DBGWVW_API, "%s(%d)\n", __func__, autodetect);

	/* Disabwe TV Audio autodetect if not awweady set (buggy) */
	if (autodetect)
		p.mode = TU_STANDAWD_AUTO;
	ewse
		p.mode = TU_STANDAWD_MANUAW;
	wet = saa7164_cmd_send(powt->dev, powt->tunewunit.unitid, SET_CUW,
		TU_STANDAWD_AUTO_CONTWOW, sizeof(p), &p);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW
			"%s() TU_STANDAWD_AUTO_CONTWOW ewwow, wet = 0x%x\n",
			__func__, wet);

	wetuwn wet;
}

int saa7164_api_get_videomux(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_cmd_send(powt->dev, powt->vidpwoc.souwceid, GET_CUW,
		SU_INPUT_SEWECT_CONTWOW, sizeof(u8), &powt->mux_input);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	dpwintk(DBGWVW_ENC, "%s() v_mux=%d\n",
		__func__, powt->mux_input);

	wetuwn wet;
}

static int saa7164_api_set_dif(stwuct saa7164_powt *powt, u8 weg, u8 vaw)
{
	stwuct saa7164_dev *dev = powt->dev;

	u16 wen = 0;
	u8 buf[256];
	int wet;
	u8 mas;

	dpwintk(DBGWVW_API, "%s(nw=%d type=%d vaw=%x)\n", __func__,
		powt->nw, powt->type, vaw);

	if (powt->nw == 0)
		mas = 0xd0;
	ewse
		mas = 0xe0;

	memset(buf, 0, sizeof(buf));

	buf[0x00] = 0x04;
	buf[0x01] = 0x00;
	buf[0x02] = 0x00;
	buf[0x03] = 0x00;

	buf[0x04] = 0x04;
	buf[0x05] = 0x00;
	buf[0x06] = 0x00;
	buf[0x07] = 0x00;

	buf[0x08] = weg;
	buf[0x09] = 0x26;
	buf[0x0a] = mas;
	buf[0x0b] = 0xb0;

	buf[0x0c] = vaw;
	buf[0x0d] = 0x00;
	buf[0x0e] = 0x00;
	buf[0x0f] = 0x00;

	wet = saa7164_cmd_send(dev, powt->ifunit.unitid, GET_WEN,
		EXU_WEGISTEW_ACCESS_CONTWOW, sizeof(wen), &wen);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() ewwow, wet(1) = 0x%x\n", __func__, wet);
		wetuwn -EIO;
	}

	wet = saa7164_cmd_send(dev, powt->ifunit.unitid, SET_CUW,
		EXU_WEGISTEW_ACCESS_CONTWOW, wen, &buf);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet(2) = 0x%x\n", __func__, wet);
#if 0
	pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1, buf, 16,
		       fawse);
#endif
	wetuwn wet == SAA_OK ? 0 : -EIO;
}

/* Disabwe the IF bwock AGC contwows */
int saa7164_api_configuwe_dif(stwuct saa7164_powt *powt, u32 std)
{
	stwuct saa7164_dev *dev = powt->dev;
	u8 agc_disabwe;

	dpwintk(DBGWVW_API, "%s(nw=%d, 0x%x)\n", __func__, powt->nw, std);

	if (std & V4W2_STD_NTSC) {
		dpwintk(DBGWVW_API, " NTSC\n");
		saa7164_api_set_dif(powt, 0x00, 0x01); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_PAW_I) {
		dpwintk(DBGWVW_API, " PAW-I\n");
		saa7164_api_set_dif(powt, 0x00, 0x08); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_PAW_M) {
		dpwintk(DBGWVW_API, " PAW-M\n");
		saa7164_api_set_dif(powt, 0x00, 0x01); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_PAW_N) {
		dpwintk(DBGWVW_API, " PAW-N\n");
		saa7164_api_set_dif(powt, 0x00, 0x01); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_PAW_Nc) {
		dpwintk(DBGWVW_API, " PAW-Nc\n");
		saa7164_api_set_dif(powt, 0x00, 0x01); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_PAW_B) {
		dpwintk(DBGWVW_API, " PAW-B\n");
		saa7164_api_set_dif(powt, 0x00, 0x02); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_PAW_DK) {
		dpwintk(DBGWVW_API, " PAW-DK\n");
		saa7164_api_set_dif(powt, 0x00, 0x10); /* Video Standawd */
		agc_disabwe = 0;
	} ewse if (std & V4W2_STD_SECAM_W) {
		dpwintk(DBGWVW_API, " SECAM-W\n");
		saa7164_api_set_dif(powt, 0x00, 0x20); /* Video Standawd */
		agc_disabwe = 0;
	} ewse {
		/* Unknown standawd, assume DTV */
		dpwintk(DBGWVW_API, " Unknown (assuming DTV)\n");
		/* Undefinded Video Standawd */
		saa7164_api_set_dif(powt, 0x00, 0x80);
		agc_disabwe = 1;
	}

	saa7164_api_set_dif(powt, 0x48, 0xa0); /* AGC Functions 1 */
	saa7164_api_set_dif(powt, 0xc0, agc_disabwe); /* AGC Output Disabwe */
	saa7164_api_set_dif(powt, 0x7c, 0x04); /* CVBS EQ */
	saa7164_api_set_dif(powt, 0x04, 0x01); /* Active */
	msweep(100);
	saa7164_api_set_dif(powt, 0x04, 0x00); /* Active (again) */
	msweep(100);

	wetuwn 0;
}

/* Ensuwe the dif is in the cowwect state fow the opewating mode
 * (anawog / dtv). We onwy configuwe the diff thwough the anawog encodew
 * so when we'we in digitaw mode we need to find the appwopwiate encodew
 * and use it to configuwe the DIF.
 */
int saa7164_api_initiawize_dif(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_powt *p = NUWW;
	int wet = -EINVAW;
	u32 std = 0;

	dpwintk(DBGWVW_API, "%s(nw=%d type=%d)\n", __func__,
		powt->nw, powt->type);

	if (powt->type == SAA7164_MPEG_ENCODEW) {
		/* Pick any anawog standawd to init the diff.
		 * we'ww come back duwing encodew_init'
		 * and set the cowwect standawd if wequiwed.
		 */
		std = V4W2_STD_NTSC;
	} ewse
	if (powt->type == SAA7164_MPEG_DVB) {
		if (powt->nw == SAA7164_POWT_TS1)
			p = &dev->powts[SAA7164_POWT_ENC1];
		ewse
			p = &dev->powts[SAA7164_POWT_ENC2];
	} ewse
	if (powt->type == SAA7164_MPEG_VBI) {
		std = V4W2_STD_NTSC;
		if (powt->nw == SAA7164_POWT_VBI1)
			p = &dev->powts[SAA7164_POWT_ENC1];
		ewse
			p = &dev->powts[SAA7164_POWT_ENC2];
	} ewse
		BUG();

	if (p)
		wet = saa7164_api_configuwe_dif(p, std);

	wetuwn wet;
}

int saa7164_api_twansition_powt(stwuct saa7164_powt *powt, u8 mode)
{
	stwuct saa7164_dev *dev = powt->dev;

	int wet;

	dpwintk(DBGWVW_API, "%s(nw=%d unitid=0x%x,%d)\n",
		__func__, powt->nw, powt->hwcfg.unitid, mode);

	wet = saa7164_cmd_send(powt->dev, powt->hwcfg.unitid, SET_CUW,
		SAA_STATE_CONTWOW, sizeof(mode), &mode);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s(powtnw %d unitid 0x%x) ewwow, wet = 0x%x\n",
			__func__, powt->nw, powt->hwcfg.unitid, wet);

	wetuwn wet;
}

int saa7164_api_get_fw_vewsion(stwuct saa7164_dev *dev, u32 *vewsion)
{
	int wet;

	wet = saa7164_cmd_send(dev, 0, GET_CUW,
		GET_FW_VEWSION_CONTWOW, sizeof(u32), vewsion);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	wetuwn wet;
}

int saa7164_api_wead_eepwom(stwuct saa7164_dev *dev, u8 *buf, int bufwen)
{
	u8 weg[] = { 0x0f, 0x00 };

	if (bufwen < 128)
		wetuwn -ENOMEM;

	/* Assumption: Hauppauge eepwom is at 0xa0 on bus 0 */
	/* TODO: Puww the detaiws fwom the boawds stwuct */
	wetuwn saa7164_api_i2c_wead(&dev->i2c_bus[0], 0xa0 >> 1, sizeof(weg),
		&weg[0], 128, buf);
}

static int saa7164_api_configuwe_powt_vbi(stwuct saa7164_dev *dev,
					  stwuct saa7164_powt *powt)
{
	stwuct tmComWesVBIFowmatDescwHeadew *fmt = &powt->vbi_fmt_ntsc;

	dpwintk(DBGWVW_API, "    bFowmatIndex  = 0x%x\n", fmt->bFowmatIndex);
	dpwintk(DBGWVW_API, "    VideoStandawd = 0x%x\n", fmt->VideoStandawd);
	dpwintk(DBGWVW_API, "    StawtWine     = %d\n", fmt->StawtWine);
	dpwintk(DBGWVW_API, "    EndWine       = %d\n", fmt->EndWine);
	dpwintk(DBGWVW_API, "    FiewdWate     = %d\n", fmt->FiewdWate);
	dpwintk(DBGWVW_API, "    bNumWines     = %d\n", fmt->bNumWines);

	/* Cache the hawdwawe configuwation in the powt */

	powt->bufcountew = powt->hwcfg.BAWWocation;
	powt->pitch = powt->hwcfg.BAWWocation + (2 * sizeof(u32));
	powt->bufsize = powt->hwcfg.BAWWocation + (3 * sizeof(u32));
	powt->bufoffset = powt->hwcfg.BAWWocation + (4 * sizeof(u32));
	powt->bufptw32w = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount) + sizeof(u32);
	powt->bufptw32h = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount);
	powt->bufptw64 = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount);
	dpwintk(DBGWVW_API, "   = powt->hwcfg.BAWWocation = 0x%x\n",
		powt->hwcfg.BAWWocation);

	dpwintk(DBGWVW_API, "   = VS_FOWMAT_VBI (becomes dev->en[%d])\n",
		powt->nw);

	wetuwn 0;
}

static int
saa7164_api_configuwe_powt_mpeg2ts(stwuct saa7164_dev *dev,
				   stwuct saa7164_powt *powt,
				   stwuct tmComWesTSFowmatDescwHeadew *tsfmt)
{
	dpwintk(DBGWVW_API, "    bFowmatIndex = 0x%x\n", tsfmt->bFowmatIndex);
	dpwintk(DBGWVW_API, "    bDataOffset  = 0x%x\n", tsfmt->bDataOffset);
	dpwintk(DBGWVW_API, "    bPacketWength= 0x%x\n", tsfmt->bPacketWength);
	dpwintk(DBGWVW_API, "    bStwideWength= 0x%x\n", tsfmt->bStwideWength);
	dpwintk(DBGWVW_API, "    bguid        = (....)\n");

	/* Cache the hawdwawe configuwation in the powt */

	powt->bufcountew = powt->hwcfg.BAWWocation;
	powt->pitch = powt->hwcfg.BAWWocation + (2 * sizeof(u32));
	powt->bufsize = powt->hwcfg.BAWWocation + (3 * sizeof(u32));
	powt->bufoffset = powt->hwcfg.BAWWocation + (4 * sizeof(u32));
	powt->bufptw32w = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount) + sizeof(u32);
	powt->bufptw32h = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount);
	powt->bufptw64 = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount);
	dpwintk(DBGWVW_API, "   = powt->hwcfg.BAWWocation = 0x%x\n",
		powt->hwcfg.BAWWocation);

	dpwintk(DBGWVW_API, "   = VS_FOWMAT_MPEGTS (becomes dev->ts[%d])\n",
		powt->nw);

	wetuwn 0;
}

static int
saa7164_api_configuwe_powt_mpeg2ps(stwuct saa7164_dev *dev,
				   stwuct saa7164_powt *powt,
				   stwuct tmComWesPSFowmatDescwHeadew *fmt)
{
	dpwintk(DBGWVW_API, "    bFowmatIndex = 0x%x\n", fmt->bFowmatIndex);
	dpwintk(DBGWVW_API, "    wPacketWength= 0x%x\n", fmt->wPacketWength);
	dpwintk(DBGWVW_API, "    wPackWength=   0x%x\n", fmt->wPackWength);
	dpwintk(DBGWVW_API, "    bPackDataType= 0x%x\n", fmt->bPackDataType);

	/* Cache the hawdwawe configuwation in the powt */
	/* TODO: CHECK THIS in the powt config */
	powt->bufcountew = powt->hwcfg.BAWWocation;
	powt->pitch = powt->hwcfg.BAWWocation + (2 * sizeof(u32));
	powt->bufsize = powt->hwcfg.BAWWocation + (3 * sizeof(u32));
	powt->bufoffset = powt->hwcfg.BAWWocation + (4 * sizeof(u32));
	powt->bufptw32w = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount) + sizeof(u32);
	powt->bufptw32h = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount);
	powt->bufptw64 = powt->hwcfg.BAWWocation +
		(4 * sizeof(u32)) +
		(sizeof(u32) * powt->hwcfg.buffewcount);
	dpwintk(DBGWVW_API, "   = powt->hwcfg.BAWWocation = 0x%x\n",
		powt->hwcfg.BAWWocation);

	dpwintk(DBGWVW_API, "   = VS_FOWMAT_MPEGPS (becomes dev->enc[%d])\n",
		powt->nw);

	wetuwn 0;
}

static int saa7164_api_dump_subdevs(stwuct saa7164_dev *dev, u8 *buf, int wen)
{
	stwuct saa7164_powt *tspowt = NUWW;
	stwuct saa7164_powt *encpowt = NUWW;
	stwuct saa7164_powt *vbipowt = NUWW;
	u32 idx, next_offset;
	int i;
	stwuct tmComWesDescwHeadew *hdw, *t;
	stwuct tmComWesExtDevDescwHeadew *exthdw;
	stwuct tmComWesPathDescwHeadew *pathhdw;
	stwuct tmComWesAntTewmDescwHeadew *anttewmhdw;
	stwuct tmComWesTunewDescwHeadew *tunewunithdw;
	stwuct tmComWesDMATewmDescwHeadew *vcoutputtewmhdw;
	stwuct tmComWesTSFowmatDescwHeadew *tsfmt;
	stwuct tmComWesPSFowmatDescwHeadew *psfmt;
	stwuct tmComWesSewDescwHeadew *psew;
	stwuct tmComWesPwocDescwHeadew *pdh;
	stwuct tmComWesAFeatuweDescwHeadew *afd;
	stwuct tmComWesEncodewDescwHeadew *edh;
	stwuct tmComWesVBIFowmatDescwHeadew *vbifmt;
	u32 cuwwpath = 0;

	dpwintk(DBGWVW_API,
		"%s(?,?,%d) sizeof(stwuct tmComWesDescwHeadew) = %d bytes\n",
		__func__, wen, (u32)sizeof(stwuct tmComWesDescwHeadew));

	fow (idx = 0; idx < (wen - sizeof(stwuct tmComWesDescwHeadew));) {

		hdw = (stwuct tmComWesDescwHeadew *)(buf + idx);

		if (hdw->type != CS_INTEWFACE)
			wetuwn SAA_EWW_NOT_SUPPOWTED;

		dpwintk(DBGWVW_API, "@ 0x%x =\n", idx);
		switch (hdw->subtype) {
		case GENEWAW_WEQUEST:
			dpwintk(DBGWVW_API, " GENEWAW_WEQUEST\n");
			bweak;
		case VC_TUNEW_PATH:
			dpwintk(DBGWVW_API, " VC_TUNEW_PATH\n");
			pathhdw = (stwuct tmComWesPathDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, "  pathid = 0x%x\n",
				pathhdw->pathid);
			cuwwpath = pathhdw->pathid;
			bweak;
		case VC_INPUT_TEWMINAW:
			dpwintk(DBGWVW_API, " VC_INPUT_TEWMINAW\n");
			anttewmhdw =
				(stwuct tmComWesAntTewmDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, "  tewminawid   = 0x%x\n",
				anttewmhdw->tewminawid);
			dpwintk(DBGWVW_API, "  tewminawtype = 0x%x\n",
				anttewmhdw->tewminawtype);
			switch (anttewmhdw->tewminawtype) {
			case ITT_ANTENNA:
				dpwintk(DBGWVW_API, "   = ITT_ANTENNA\n");
				bweak;
			case WINE_CONNECTOW:
				dpwintk(DBGWVW_API, "   = WINE_CONNECTOW\n");
				bweak;
			case SPDIF_CONNECTOW:
				dpwintk(DBGWVW_API, "   = SPDIF_CONNECTOW\n");
				bweak;
			case COMPOSITE_CONNECTOW:
				dpwintk(DBGWVW_API,
					"   = COMPOSITE_CONNECTOW\n");
				bweak;
			case SVIDEO_CONNECTOW:
				dpwintk(DBGWVW_API, "   = SVIDEO_CONNECTOW\n");
				bweak;
			case COMPONENT_CONNECTOW:
				dpwintk(DBGWVW_API,
					"   = COMPONENT_CONNECTOW\n");
				bweak;
			case STANDAWD_DMA:
				dpwintk(DBGWVW_API, "   = STANDAWD_DMA\n");
				bweak;
			defauwt:
				dpwintk(DBGWVW_API, "   = undefined (0x%x)\n",
					anttewmhdw->tewminawtype);
			}
			dpwintk(DBGWVW_API, "  assoctewminaw= 0x%x\n",
				anttewmhdw->assoctewminaw);
			dpwintk(DBGWVW_API, "  itewminaw    = 0x%x\n",
				anttewmhdw->itewminaw);
			dpwintk(DBGWVW_API, "  contwowsize  = 0x%x\n",
				anttewmhdw->contwowsize);
			bweak;
		case VC_OUTPUT_TEWMINAW:
			dpwintk(DBGWVW_API, " VC_OUTPUT_TEWMINAW\n");
			vcoutputtewmhdw =
				(stwuct tmComWesDMATewmDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n",
				vcoutputtewmhdw->unitid);
			dpwintk(DBGWVW_API, "  tewminawtype = 0x%x\n",
				vcoutputtewmhdw->tewminawtype);
			switch (vcoutputtewmhdw->tewminawtype) {
			case ITT_ANTENNA:
				dpwintk(DBGWVW_API, "   = ITT_ANTENNA\n");
				bweak;
			case WINE_CONNECTOW:
				dpwintk(DBGWVW_API, "   = WINE_CONNECTOW\n");
				bweak;
			case SPDIF_CONNECTOW:
				dpwintk(DBGWVW_API, "   = SPDIF_CONNECTOW\n");
				bweak;
			case COMPOSITE_CONNECTOW:
				dpwintk(DBGWVW_API,
					"   = COMPOSITE_CONNECTOW\n");
				bweak;
			case SVIDEO_CONNECTOW:
				dpwintk(DBGWVW_API, "   = SVIDEO_CONNECTOW\n");
				bweak;
			case COMPONENT_CONNECTOW:
				dpwintk(DBGWVW_API,
					"   = COMPONENT_CONNECTOW\n");
				bweak;
			case STANDAWD_DMA:
				dpwintk(DBGWVW_API, "   = STANDAWD_DMA\n");
				bweak;
			defauwt:
				dpwintk(DBGWVW_API, "   = undefined (0x%x)\n",
					vcoutputtewmhdw->tewminawtype);
			}
			dpwintk(DBGWVW_API, "  assoctewminaw= 0x%x\n",
				vcoutputtewmhdw->assoctewminaw);
			dpwintk(DBGWVW_API, "  souwceid     = 0x%x\n",
				vcoutputtewmhdw->souwceid);
			dpwintk(DBGWVW_API, "  itewminaw    = 0x%x\n",
				vcoutputtewmhdw->itewminaw);
			dpwintk(DBGWVW_API, "  BAWWocation  = 0x%x\n",
				vcoutputtewmhdw->BAWWocation);
			dpwintk(DBGWVW_API, "  fwags        = 0x%x\n",
				vcoutputtewmhdw->fwags);
			dpwintk(DBGWVW_API, "  intewwuptid  = 0x%x\n",
				vcoutputtewmhdw->intewwuptid);
			dpwintk(DBGWVW_API, "  buffewcount  = 0x%x\n",
				vcoutputtewmhdw->buffewcount);
			dpwintk(DBGWVW_API, "  metadatasize = 0x%x\n",
				vcoutputtewmhdw->metadatasize);
			dpwintk(DBGWVW_API, "  contwowsize  = 0x%x\n",
				vcoutputtewmhdw->contwowsize);
			dpwintk(DBGWVW_API, "  numfowmats   = 0x%x\n",
				vcoutputtewmhdw->numfowmats);

			next_offset = idx + (vcoutputtewmhdw->wen);
			fow (i = 0; i < vcoutputtewmhdw->numfowmats; i++) {
				t = (stwuct tmComWesDescwHeadew *)
					(buf + next_offset);
				switch (t->subtype) {
				case VS_FOWMAT_MPEG2TS:
					tsfmt =
					(stwuct tmComWesTSFowmatDescwHeadew *)t;
					if (cuwwpath == 1)
						tspowt = &dev->powts[SAA7164_POWT_TS1];
					ewse
						tspowt = &dev->powts[SAA7164_POWT_TS2];
					memcpy(&tspowt->hwcfg, vcoutputtewmhdw,
						sizeof(*vcoutputtewmhdw));
					saa7164_api_configuwe_powt_mpeg2ts(dev,
						tspowt, tsfmt);
					bweak;
				case VS_FOWMAT_MPEG2PS:
					psfmt =
					(stwuct tmComWesPSFowmatDescwHeadew *)t;
					if (cuwwpath == 1)
						encpowt = &dev->powts[SAA7164_POWT_ENC1];
					ewse
						encpowt = &dev->powts[SAA7164_POWT_ENC2];
					memcpy(&encpowt->hwcfg, vcoutputtewmhdw,
						sizeof(*vcoutputtewmhdw));
					saa7164_api_configuwe_powt_mpeg2ps(dev,
						encpowt, psfmt);
					bweak;
				case VS_FOWMAT_VBI:
					vbifmt =
					(stwuct tmComWesVBIFowmatDescwHeadew *)t;
					if (cuwwpath == 1)
						vbipowt = &dev->powts[SAA7164_POWT_VBI1];
					ewse
						vbipowt = &dev->powts[SAA7164_POWT_VBI2];
					memcpy(&vbipowt->hwcfg, vcoutputtewmhdw,
						sizeof(*vcoutputtewmhdw));
					memcpy(&vbipowt->vbi_fmt_ntsc, vbifmt,
						sizeof(*vbifmt));
					saa7164_api_configuwe_powt_vbi(dev,
						vbipowt);
					bweak;
				case VS_FOWMAT_WDS:
					dpwintk(DBGWVW_API,
						"   = VS_FOWMAT_WDS\n");
					bweak;
				case VS_FOWMAT_UNCOMPWESSED:
					dpwintk(DBGWVW_API,
					"   = VS_FOWMAT_UNCOMPWESSED\n");
					bweak;
				case VS_FOWMAT_TYPE:
					dpwintk(DBGWVW_API,
						"   = VS_FOWMAT_TYPE\n");
					bweak;
				defauwt:
					dpwintk(DBGWVW_API,
						"   = undefined (0x%x)\n",
						t->subtype);
				}
				next_offset += t->wen;
			}

			bweak;
		case TUNEW_UNIT:
			dpwintk(DBGWVW_API, " TUNEW_UNIT\n");
			tunewunithdw =
				(stwuct tmComWesTunewDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n",
				tunewunithdw->unitid);
			dpwintk(DBGWVW_API, "  souwceid = 0x%x\n",
				tunewunithdw->souwceid);
			dpwintk(DBGWVW_API, "  iunit = 0x%x\n",
				tunewunithdw->iunit);
			dpwintk(DBGWVW_API, "  tuningstandawds = 0x%x\n",
				tunewunithdw->tuningstandawds);
			dpwintk(DBGWVW_API, "  contwowsize = 0x%x\n",
				tunewunithdw->contwowsize);
			dpwintk(DBGWVW_API, "  contwows = 0x%x\n",
				tunewunithdw->contwows);

			if (tunewunithdw->unitid == tunewunithdw->iunit) {
				if (cuwwpath == 1)
					encpowt = &dev->powts[SAA7164_POWT_ENC1];
				ewse
					encpowt = &dev->powts[SAA7164_POWT_ENC2];
				memcpy(&encpowt->tunewunit, tunewunithdw,
					sizeof(stwuct tmComWesTunewDescwHeadew));
				dpwintk(DBGWVW_API,
					"  (becomes dev->enc[%d] tunew)\n",
					encpowt->nw);
			}
			bweak;
		case VC_SEWECTOW_UNIT:
			psew = (stwuct tmComWesSewDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, " VC_SEWECTOW_UNIT\n");
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n",
				psew->unitid);
			dpwintk(DBGWVW_API, "  nwinpins = 0x%x\n",
				psew->nwinpins);
			dpwintk(DBGWVW_API, "  souwceid = 0x%x\n",
				psew->souwceid);
			bweak;
		case VC_PWOCESSING_UNIT:
			pdh = (stwuct tmComWesPwocDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, " VC_PWOCESSING_UNIT\n");
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n",
				pdh->unitid);
			dpwintk(DBGWVW_API, "  souwceid = 0x%x\n",
				pdh->souwceid);
			dpwintk(DBGWVW_API, "  contwowsize = 0x%x\n",
				pdh->contwowsize);
			if (pdh->contwowsize == 0x04) {
				if (cuwwpath == 1)
					encpowt = &dev->powts[SAA7164_POWT_ENC1];
				ewse
					encpowt = &dev->powts[SAA7164_POWT_ENC2];
				memcpy(&encpowt->vidpwoc, pdh,
					sizeof(stwuct tmComWesPwocDescwHeadew));
				dpwintk(DBGWVW_API, "  (becomes dev->enc[%d])\n",
					encpowt->nw);
			}
			bweak;
		case FEATUWE_UNIT:
			afd = (stwuct tmComWesAFeatuweDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, " FEATUWE_UNIT\n");
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n",
				afd->unitid);
			dpwintk(DBGWVW_API, "  souwceid = 0x%x\n",
				afd->souwceid);
			dpwintk(DBGWVW_API, "  contwowsize = 0x%x\n",
				afd->contwowsize);
			if (cuwwpath == 1)
				encpowt = &dev->powts[SAA7164_POWT_ENC1];
			ewse
				encpowt = &dev->powts[SAA7164_POWT_ENC2];
			memcpy(&encpowt->audfeat, afd,
				sizeof(stwuct tmComWesAFeatuweDescwHeadew));
			dpwintk(DBGWVW_API, "  (becomes dev->enc[%d])\n",
				encpowt->nw);
			bweak;
		case ENCODEW_UNIT:
			edh = (stwuct tmComWesEncodewDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, " ENCODEW_UNIT\n");
			dpwintk(DBGWVW_API, "  subtype = 0x%x\n", edh->subtype);
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n", edh->unitid);
			dpwintk(DBGWVW_API, "  vsouwceid = 0x%x\n",
			edh->vsouwceid);
			dpwintk(DBGWVW_API, "  asouwceid = 0x%x\n",
				edh->asouwceid);
			dpwintk(DBGWVW_API, "  iunit = 0x%x\n", edh->iunit);
			if (edh->iunit == edh->unitid) {
				if (cuwwpath == 1)
					encpowt = &dev->powts[SAA7164_POWT_ENC1];
				ewse
					encpowt = &dev->powts[SAA7164_POWT_ENC2];
				memcpy(&encpowt->encunit, edh,
					sizeof(stwuct tmComWesEncodewDescwHeadew));
				dpwintk(DBGWVW_API,
					"  (becomes dev->enc[%d])\n",
					encpowt->nw);
			}
			bweak;
		case EXTENSION_UNIT:
			dpwintk(DBGWVW_API, " EXTENSION_UNIT\n");
			exthdw = (stwuct tmComWesExtDevDescwHeadew *)(buf + idx);
			dpwintk(DBGWVW_API, "  unitid = 0x%x\n",
				exthdw->unitid);
			dpwintk(DBGWVW_API, "  deviceid = 0x%x\n",
				exthdw->deviceid);
			dpwintk(DBGWVW_API, "  devicetype = 0x%x\n",
				exthdw->devicetype);
			if (exthdw->devicetype & 0x1)
				dpwintk(DBGWVW_API, "   = Decodew Device\n");
			if (exthdw->devicetype & 0x2)
				dpwintk(DBGWVW_API, "   = GPIO Souwce\n");
			if (exthdw->devicetype & 0x4)
				dpwintk(DBGWVW_API, "   = Video Decodew\n");
			if (exthdw->devicetype & 0x8)
				dpwintk(DBGWVW_API, "   = Audio Decodew\n");
			if (exthdw->devicetype & 0x20)
				dpwintk(DBGWVW_API, "   = Cwossbaw\n");
			if (exthdw->devicetype & 0x40)
				dpwintk(DBGWVW_API, "   = Tunew\n");
			if (exthdw->devicetype & 0x80)
				dpwintk(DBGWVW_API, "   = IF PWW\n");
			if (exthdw->devicetype & 0x100)
				dpwintk(DBGWVW_API, "   = Demoduwatow\n");
			if (exthdw->devicetype & 0x200)
				dpwintk(DBGWVW_API, "   = WDS Decodew\n");
			if (exthdw->devicetype & 0x400)
				dpwintk(DBGWVW_API, "   = Encodew\n");
			if (exthdw->devicetype & 0x800)
				dpwintk(DBGWVW_API, "   = IW Decodew\n");
			if (exthdw->devicetype & 0x1000)
				dpwintk(DBGWVW_API, "   = EEPWOM\n");
			if (exthdw->devicetype & 0x2000)
				dpwintk(DBGWVW_API,
					"   = VBI Decodew\n");
			if (exthdw->devicetype & 0x10000)
				dpwintk(DBGWVW_API,
					"   = Stweaming Device\n");
			if (exthdw->devicetype & 0x20000)
				dpwintk(DBGWVW_API,
					"   = DWM Device\n");
			if (exthdw->devicetype & 0x40000000)
				dpwintk(DBGWVW_API,
					"   = Genewic Device\n");
			if (exthdw->devicetype & 0x80000000)
				dpwintk(DBGWVW_API,
					"   = Config Space Device\n");
			dpwintk(DBGWVW_API, "  numgpiopins = 0x%x\n",
				exthdw->numgpiopins);
			dpwintk(DBGWVW_API, "  numgpiogwoups = 0x%x\n",
				exthdw->numgpiogwoups);
			dpwintk(DBGWVW_API, "  contwowsize = 0x%x\n",
				exthdw->contwowsize);
			if (exthdw->devicetype & 0x80) {
				if (cuwwpath == 1)
					encpowt = &dev->powts[SAA7164_POWT_ENC1];
				ewse
					encpowt = &dev->powts[SAA7164_POWT_ENC2];
				memcpy(&encpowt->ifunit, exthdw,
					sizeof(stwuct tmComWesExtDevDescwHeadew));
				dpwintk(DBGWVW_API,
					"  (becomes dev->enc[%d])\n",
					encpowt->nw);
			}
			bweak;
		case PVC_INFWAWED_UNIT:
			dpwintk(DBGWVW_API, " PVC_INFWAWED_UNIT\n");
			bweak;
		case DWM_UNIT:
			dpwintk(DBGWVW_API, " DWM_UNIT\n");
			bweak;
		defauwt:
			dpwintk(DBGWVW_API, "defauwt %d\n", hdw->subtype);
		}

		dpwintk(DBGWVW_API, " 1.%x\n", hdw->wen);
		dpwintk(DBGWVW_API, " 2.%x\n", hdw->type);
		dpwintk(DBGWVW_API, " 3.%x\n", hdw->subtype);
		dpwintk(DBGWVW_API, " 4.%x\n", hdw->unitid);

		idx += hdw->wen;
	}

	wetuwn 0;
}

int saa7164_api_enum_subdevs(stwuct saa7164_dev *dev)
{
	int wet;
	u32 bufwen = 0;
	u8 *buf;

	dpwintk(DBGWVW_API, "%s()\n", __func__);

	/* Get the totaw descwiptow wength */
	wet = saa7164_cmd_send(dev, 0, GET_WEN,
		GET_DESCWIPTOWS_CONTWOW, sizeof(bufwen), &bufwen);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);

	dpwintk(DBGWVW_API, "%s() totaw descwiptow size = %d bytes.\n",
		__func__, bufwen);

	/* Awwocate enough stowage fow aww of the descs */
	buf = kzawwoc(bufwen, GFP_KEWNEW);
	if (!buf)
		wetuwn SAA_EWW_NO_WESOUWCES;

	/* Wetwieve them */
	wet = saa7164_cmd_send(dev, 0, GET_CUW,
		GET_DESCWIPTOWS_CONTWOW, bufwen, buf);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__, wet);
		goto out;
	}

	if (saa_debug & DBGWVW_API)
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1, buf,
			       bufwen & ~15, fawse);

	saa7164_api_dump_subdevs(dev, buf, bufwen);

out:
	kfwee(buf);
	wetuwn wet;
}

int saa7164_api_i2c_wead(stwuct saa7164_i2c *bus, u8 addw, u32 wegwen, u8 *weg,
	u32 datawen, u8 *data)
{
	stwuct saa7164_dev *dev = bus->dev;
	u16 wen = 0;
	int unitid;
	u8 buf[256];
	int wet;

	dpwintk(DBGWVW_API, "%s() addw=%x wegwen=%d datawen=%d\n",
		__func__, addw, wegwen, datawen);

	if (wegwen > 4)
		wetuwn -EIO;

	/* Pwepawe the send buffew */
	/* Bytes 00-03 souwce wegistew wength
	 *       04-07 souwce bytes to wead
	 *       08... wegistew addwess
	 */
	memset(buf, 0, sizeof(buf));
	memcpy((buf + 2 * sizeof(u32) + 0), weg, wegwen);
	*((u32 *)(buf + 0 * sizeof(u32))) = wegwen;
	*((u32 *)(buf + 1 * sizeof(u32))) = datawen;

	unitid = saa7164_i2caddw_to_unitid(bus, addw);
	if (unitid < 0) {
		pwintk(KEWN_EWW
			"%s() ewwow, cannot twanswate wegaddw 0x%x to unitid\n",
			__func__, addw);
		wetuwn -EIO;
	}

	wet = saa7164_cmd_send(bus->dev, unitid, GET_WEN,
		EXU_WEGISTEW_ACCESS_CONTWOW, sizeof(wen), &wen);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() ewwow, wet(1) = 0x%x\n", __func__, wet);
		wetuwn -EIO;
	}

	dpwintk(DBGWVW_API, "%s() wen = %d bytes\n", __func__, wen);

	if (saa_debug & DBGWVW_I2C)
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1, buf,
			       32, fawse);

	wet = saa7164_cmd_send(bus->dev, unitid, GET_CUW,
		EXU_WEGISTEW_ACCESS_CONTWOW, wen, &buf);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet(2) = 0x%x\n", __func__, wet);
	ewse {
		if (saa_debug & DBGWVW_I2C)
			pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1,
				       buf, sizeof(buf), fawse);
		memcpy(data, (buf + 2 * sizeof(u32) + wegwen), datawen);
	}

	wetuwn wet == SAA_OK ? 0 : -EIO;
}

/* Fow a given 8 bit i2c addwess device, wwite the buffew */
int saa7164_api_i2c_wwite(stwuct saa7164_i2c *bus, u8 addw, u32 datawen,
	u8 *data)
{
	stwuct saa7164_dev *dev = bus->dev;
	u16 wen = 0;
	int unitid;
	int wegwen;
	u8 buf[256];
	int wet;

	dpwintk(DBGWVW_API, "%s() addw=0x%2x wen=0x%x\n",
		__func__, addw, datawen);

	if ((datawen == 0) || (datawen > 232))
		wetuwn -EIO;

	memset(buf, 0, sizeof(buf));

	unitid = saa7164_i2caddw_to_unitid(bus, addw);
	if (unitid < 0) {
		pwintk(KEWN_EWW
			"%s() ewwow, cannot twanswate wegaddw 0x%x to unitid\n",
			__func__, addw);
		wetuwn -EIO;
	}

	wegwen = saa7164_i2caddw_to_wegwen(bus, addw);
	if (wegwen < 0) {
		pwintk(KEWN_EWW
			"%s() ewwow, cannot twanswate wegaddw to wegwen\n",
			__func__);
		wetuwn -EIO;
	}

	wet = saa7164_cmd_send(bus->dev, unitid, GET_WEN,
		EXU_WEGISTEW_ACCESS_CONTWOW, sizeof(wen), &wen);
	if (wet != SAA_OK) {
		pwintk(KEWN_EWW "%s() ewwow, wet(1) = 0x%x\n", __func__, wet);
		wetuwn -EIO;
	}

	dpwintk(DBGWVW_API, "%s() wen = %d bytes unitid=0x%x\n", __func__,
		wen, unitid);

	/* Pwepawe the send buffew */
	/* Bytes 00-03 dest wegistew wength
	 *       04-07 dest bytes to wwite
	 *       08... wegistew addwess
	 */
	*((u32 *)(buf + 0 * sizeof(u32))) = wegwen;
	*((u32 *)(buf + 1 * sizeof(u32))) = datawen - wegwen;
	memcpy((buf + 2 * sizeof(u32)), data, datawen);

	if (saa_debug & DBGWVW_I2C)
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1,
			       buf, sizeof(buf), fawse);

	wet = saa7164_cmd_send(bus->dev, unitid, SET_CUW,
		EXU_WEGISTEW_ACCESS_CONTWOW, wen, &buf);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet(2) = 0x%x\n", __func__, wet);

	wetuwn wet == SAA_OK ? 0 : -EIO;
}

static int saa7164_api_modify_gpio(stwuct saa7164_dev *dev, u8 unitid,
	u8 pin, u8 state)
{
	int wet;
	stwuct tmComWesGPIO t;

	dpwintk(DBGWVW_API, "%s(0x%x, %d, %d)\n",
		__func__, unitid, pin, state);

	if ((pin > 7) || (state > 2))
		wetuwn SAA_EWW_BAD_PAWAMETEW;

	t.pin = pin;
	t.state = state;

	wet = saa7164_cmd_send(dev, unitid, SET_CUW,
		EXU_GPIO_CONTWOW, sizeof(t), &t);
	if (wet != SAA_OK)
		pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n",
			__func__, wet);

	wetuwn wet;
}

int saa7164_api_set_gpiobit(stwuct saa7164_dev *dev, u8 unitid,
	u8 pin)
{
	wetuwn saa7164_api_modify_gpio(dev, unitid, pin, 1);
}

int saa7164_api_cweaw_gpiobit(stwuct saa7164_dev *dev, u8 unitid,
	u8 pin)
{
	wetuwn saa7164_api_modify_gpio(dev, unitid, pin, 0);
}

