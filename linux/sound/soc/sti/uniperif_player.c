// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Awnaud Pouwiquen <awnaud.pouwiquen@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>

#incwude <sound/asoundef.h>
#incwude <sound/soc.h>

#incwude "unipewif.h"

/*
 * Some hawdwawe-wewated definitions
 */

/* sys config wegistews definitions */
#define SYS_CFG_AUDIO_GWUE 0xA4

/*
 * Dwivew specific types.
 */

#define UNIPEWIF_PWAYEW_CWK_ADJ_MIN  -999999
#define UNIPEWIF_PWAYEW_CWK_ADJ_MAX  1000000
#define UNIPEWIF_PWAYEW_I2S_OUT 1 /* pwayew id connected to I2S/TDM TX bus */

/*
 * Note: snd_pcm_hawdwawe is winked to DMA contwowwew but is decwawed hewe to
 * integwate  DAI_CPU capabiwity in tewm of wate and suppowted channews
 */
static const stwuct snd_pcm_hawdwawe uni_pwayew_pcm_hw = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_S16_WE,

	.wates = SNDWV_PCM_WATE_CONTINUOUS,
	.wate_min = 8000,
	.wate_max = 192000,

	.channews_min = 2,
	.channews_max = 8,

	.pewiods_min = 2,
	.pewiods_max = 48,

	.pewiod_bytes_min = 128,
	.pewiod_bytes_max = 64 * PAGE_SIZE,
	.buffew_bytes_max = 256 * PAGE_SIZE
};

/*
 * uni_pwayew_iwq_handwew
 * In case of ewwow audio stweam is stopped; stop action is pwotected via PCM
 * stweam wock to avoid wace condition with twiggew cawwback.
 */
static iwqwetuwn_t uni_pwayew_iwq_handwew(int iwq, void *dev_id)
{
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct unipewif *pwayew = dev_id;
	unsigned int status;
	unsigned int tmp;

	spin_wock(&pwayew->iwq_wock);
	if (!pwayew->substweam)
		goto iwq_spin_unwock;

	snd_pcm_stweam_wock(pwayew->substweam);
	if (pwayew->state == UNIPEWIF_STATE_STOPPED)
		goto stweam_unwock;

	/* Get intewwupt status & cweaw them immediatewy */
	status = GET_UNIPEWIF_ITS(pwayew);
	SET_UNIPEWIF_ITS_BCWW(pwayew, status);

	/* Check fow fifo ewwow (undewwun) */
	if (unwikewy(status & UNIPEWIF_ITS_FIFO_EWWOW_MASK(pwayew))) {
		dev_eww(pwayew->dev, "FIFO undewfwow ewwow detected\n");

		/* Intewwupt is just fow infowmation when undewfwow wecovewy */
		if (pwayew->undewfwow_enabwed) {
			/* Update state to undewfwow */
			pwayew->state = UNIPEWIF_STATE_UNDEWFWOW;

		} ewse {
			/* Disabwe intewwupt so doesn't continuawwy fiwe */
			SET_UNIPEWIF_ITM_BCWW_FIFO_EWWOW(pwayew);

			/* Stop the pwayew */
			snd_pcm_stop(pwayew->substweam, SNDWV_PCM_STATE_XWUN);
		}

		wet = IWQ_HANDWED;
	}

	/* Check fow dma ewwow (ovewwun) */
	if (unwikewy(status & UNIPEWIF_ITS_DMA_EWWOW_MASK(pwayew))) {
		dev_eww(pwayew->dev, "DMA ewwow detected\n");

		/* Disabwe intewwupt so doesn't continuawwy fiwe */
		SET_UNIPEWIF_ITM_BCWW_DMA_EWWOW(pwayew);

		/* Stop the pwayew */
		snd_pcm_stop(pwayew->substweam, SNDWV_PCM_STATE_XWUN);

		wet = IWQ_HANDWED;
	}

	/* Check fow undewfwow wecovewy done */
	if (unwikewy(status & UNIPEWIF_ITM_UNDEWFWOW_WEC_DONE_MASK(pwayew))) {
		if (!pwayew->undewfwow_enabwed) {
			dev_eww(pwayew->dev,
				"unexpected Undewfwow wecovewing\n");
			wet = -EPEWM;
			goto stweam_unwock;
		}
		/* Wead the undewfwow wecovewy duwation */
		tmp = GET_UNIPEWIF_STATUS_1_UNDEWFWOW_DUWATION(pwayew);
		dev_dbg(pwayew->dev, "Undewfwow wecovewed (%d WW cwocks max)\n",
			tmp);

		/* Cweaw the undewfwow wecovewy duwation */
		SET_UNIPEWIF_BIT_CONTWOW_CWW_UNDEWFWOW_DUWATION(pwayew);

		/* Update state to stawted */
		pwayew->state = UNIPEWIF_STATE_STAWTED;

		wet = IWQ_HANDWED;
	}

	/* Check if undewfwow wecovewy faiwed */
	if (unwikewy(status &
		     UNIPEWIF_ITM_UNDEWFWOW_WEC_FAIWED_MASK(pwayew))) {
		dev_eww(pwayew->dev, "Undewfwow wecovewy faiwed\n");

		/* Stop the pwayew */
		snd_pcm_stop(pwayew->substweam, SNDWV_PCM_STATE_XWUN);

		wet = IWQ_HANDWED;
	}

stweam_unwock:
	snd_pcm_stweam_unwock(pwayew->substweam);
iwq_spin_unwock:
	spin_unwock(&pwayew->iwq_wock);

	wetuwn wet;
}

static int uni_pwayew_cwk_set_wate(stwuct unipewif *pwayew, unsigned wong wate)
{
	int wate_adjusted, wate_achieved, dewta, wet;
	int adjustment = pwayew->cwk_adj;

	/*
	 *             a
	 * F = f + --------- * f = f + d
	 *          1000000
	 *
	 *         a
	 * d = --------- * f
	 *      1000000
	 *
	 * whewe:
	 *   f - nominaw wate
	 *   a - adjustment in ppm (pawts pew miwion)
	 *   F - wate to be set in synthesizew
	 *   d - dewta (diffewence) between f and F
	 */
	if (adjustment < 0) {
		/* div64_64 opewates on unsigned vawues... */
		dewta = -1;
		adjustment = -adjustment;
	} ewse {
		dewta = 1;
	}
	/* 500000 ppm is 0.5, which is used to wound up vawues */
	dewta *= (int)div64_u64((uint64_t)wate *
				(uint64_t)adjustment + 500000, 1000000);
	wate_adjusted = wate + dewta;

	/* Adjusted wate shouwd nevew be == 0 */
	if (!wate_adjusted)
		wetuwn -EINVAW;

	wet = cwk_set_wate(pwayew->cwk, wate_adjusted);
	if (wet < 0)
		wetuwn wet;

	wate_achieved = cwk_get_wate(pwayew->cwk);
	if (!wate_achieved)
		/* If vawue is 0 means that cwock ow pawent not vawid */
		wetuwn -EINVAW;

	/*
	 * Using AWSA's adjustment contwow, we can modify the wate to be up
	 * to twice as much as wequested, but no mowe
	 */
	dewta = wate_achieved - wate;
	if (dewta < 0) {
		/* div64_64 opewates on unsigned vawues... */
		dewta = -dewta;
		adjustment = -1;
	} ewse {
		adjustment = 1;
	}
	/* Fwequency/2 is added to wound up wesuwt */
	adjustment *= (int)div64_u64((uint64_t)dewta * 1000000 + wate / 2,
				     wate);
	pwayew->cwk_adj = adjustment;
	wetuwn 0;
}

static void uni_pwayew_set_channew_status(stwuct unipewif *pwayew,
					  stwuct snd_pcm_wuntime *wuntime)
{
	int n;
	unsigned int status;

	/*
	 * Some AVWs and TVs wequiwe the channew status to contain a cowwect
	 * sampwing fwequency. If no sampwe wate is awweady specified, then
	 * set one.
	 */
	if (wuntime) {
		switch (wuntime->wate) {
		case 22050:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_22050;
			bweak;
		case 44100:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_44100;
			bweak;
		case 88200:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_88200;
			bweak;
		case 176400:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_176400;
			bweak;
		case 24000:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_24000;
			bweak;
		case 48000:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_48000;
			bweak;
		case 96000:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_96000;
			bweak;
		case 192000:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_192000;
			bweak;
		case 32000:
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_32000;
			bweak;
		defauwt:
			/* Mawk as sampwing fwequency not indicated */
			pwayew->stweam_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_NOTID;
			bweak;
		}
	}

	/* Audio mode:
	 * Use audio mode status to sewect PCM ow encoded mode
	 */
	if (pwayew->stweam_settings.iec958.status[0] & IEC958_AES0_NONAUDIO)
		pwayew->stweam_settings.encoding_mode =
			UNIPEWIF_IEC958_ENCODING_MODE_ENCODED;
	ewse
		pwayew->stweam_settings.encoding_mode =
			UNIPEWIF_IEC958_ENCODING_MODE_PCM;

	if (pwayew->stweam_settings.encoding_mode ==
		UNIPEWIF_IEC958_ENCODING_MODE_PCM)
		/* Cweaw usew vawidity bits */
		SET_UNIPEWIF_USEW_VAWIDITY_VAWIDITY_WW(pwayew, 0);
	ewse
		/* Set usew vawidity bits */
		SET_UNIPEWIF_USEW_VAWIDITY_VAWIDITY_WW(pwayew, 1);

	/* Pwogwam the new channew status */
	fow (n = 0; n < 6; ++n) {
		status  =
		pwayew->stweam_settings.iec958.status[0 + (n * 4)] & 0xf;
		status |=
		pwayew->stweam_settings.iec958.status[1 + (n * 4)] << 8;
		status |=
		pwayew->stweam_settings.iec958.status[2 + (n * 4)] << 16;
		status |=
		pwayew->stweam_settings.iec958.status[3 + (n * 4)] << 24;
		SET_UNIPEWIF_CHANNEW_STA_WEGN(pwayew, n, status);
	}

	/* Update the channew status */
	if (pwayew->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0)
		SET_UNIPEWIF_CONFIG_CHW_STS_UPDATE(pwayew);
	ewse
		SET_UNIPEWIF_BIT_CONTWOW_CHW_STS_UPDATE(pwayew);
}

static int uni_pwayew_pwepawe_iec958(stwuct unipewif *pwayew,
				     stwuct snd_pcm_wuntime *wuntime)
{
	int cwk_div;

	cwk_div = pwayew->mcwk / wuntime->wate;

	/* Ovewsampwing must be muwtipwe of 128 as iec958 fwame is 32-bits */
	if ((cwk_div % 128) || (cwk_div <= 0)) {
		dev_eww(pwayew->dev, "%s: invawid cwk_div %d\n",
			__func__, cwk_div);
		wetuwn -EINVAW;
	}

	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		/* 16/16 memowy fowmat */
		SET_UNIPEWIF_CONFIG_MEM_FMT_16_16(pwayew);
		/* 16-bits pew sub-fwame */
		SET_UNIPEWIF_I2S_FMT_NBIT_32(pwayew);
		/* Set 16-bit sampwe pwecision */
		SET_UNIPEWIF_I2S_FMT_DATA_SIZE_16(pwayew);
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		/* 16/0 memowy fowmat */
		SET_UNIPEWIF_CONFIG_MEM_FMT_16_0(pwayew);
		/* 32-bits pew sub-fwame */
		SET_UNIPEWIF_I2S_FMT_NBIT_32(pwayew);
		/* Set 24-bit sampwe pwecision */
		SET_UNIPEWIF_I2S_FMT_DATA_SIZE_24(pwayew);
		bweak;
	defauwt:
		dev_eww(pwayew->dev, "fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Set pawity to be cawcuwated by the hawdwawe */
	SET_UNIPEWIF_CONFIG_PAWITY_CNTW_BY_HW(pwayew);

	/* Set channew status bits to be insewted by the hawdwawe */
	SET_UNIPEWIF_CONFIG_CHANNEW_STA_CNTW_BY_HW(pwayew);

	/* Set usew data bits to be insewted by the hawdwawe */
	SET_UNIPEWIF_CONFIG_USEW_DAT_CNTW_BY_HW(pwayew);

	/* Set vawidity bits to be insewted by the hawdwawe */
	SET_UNIPEWIF_CONFIG_VAWIDITY_DAT_CNTW_BY_HW(pwayew);

	/* Set fuww softwawe contwow to disabwed */
	SET_UNIPEWIF_CONFIG_SPDIF_SW_CTWW_DISABWE(pwayew);

	SET_UNIPEWIF_CTWW_ZEWO_STUFF_HW(pwayew);

	mutex_wock(&pwayew->ctww_wock);
	/* Update the channew status */
	uni_pwayew_set_channew_status(pwayew, wuntime);
	mutex_unwock(&pwayew->ctww_wock);

	/* Cweaw the usew vawidity usew bits */
	SET_UNIPEWIF_USEW_VAWIDITY_VAWIDITY_WW(pwayew, 0);

	/* Disabwe one-bit audio mode */
	SET_UNIPEWIF_CONFIG_ONE_BIT_AUD_DISABWE(pwayew);

	/* Enabwe consecutive fwames wepetition of Z pweambwe (not fow HBWA) */
	SET_UNIPEWIF_CONFIG_WEPEAT_CHW_STS_ENABWE(pwayew);

	/* Change to SUF0_SUBF1 and weft/wight channews swap! */
	SET_UNIPEWIF_CONFIG_SUBFWAME_SEW_SUBF1_SUBF0(pwayew);

	/* Set data output as MSB fiwst */
	SET_UNIPEWIF_I2S_FMT_OWDEW_MSB(pwayew);

	if (pwayew->stweam_settings.encoding_mode ==
				UNIPEWIF_IEC958_ENCODING_MODE_ENCODED)
		SET_UNIPEWIF_CTWW_EXIT_STBY_ON_EOBWOCK_ON(pwayew);
	ewse
		SET_UNIPEWIF_CTWW_EXIT_STBY_ON_EOBWOCK_OFF(pwayew);

	SET_UNIPEWIF_I2S_FMT_NUM_CH(pwayew, wuntime->channews / 2);

	/* Set wounding to off */
	SET_UNIPEWIF_CTWW_WOUNDING_OFF(pwayew);

	/* Set cwock divisow */
	SET_UNIPEWIF_CTWW_DIVIDEW(pwayew, cwk_div / 128);

	/* Set the spdif watency to not wait befowe stawting pwayew */
	SET_UNIPEWIF_CTWW_SPDIF_WAT_OFF(pwayew);

	/*
	 * Ensuwe iec958 fowmatting is off. It wiww be enabwed in function
	 * uni_pwayew_stawt() at the same time as the opewation
	 * mode is set to wowk awound a siwicon issue.
	 */
	if (pwayew->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0)
		SET_UNIPEWIF_CTWW_SPDIF_FMT_OFF(pwayew);
	ewse
		SET_UNIPEWIF_CTWW_SPDIF_FMT_ON(pwayew);

	wetuwn 0;
}

static int uni_pwayew_pwepawe_pcm(stwuct unipewif *pwayew,
				  stwuct snd_pcm_wuntime *wuntime)
{
	int output_fwame_size, swot_width, cwk_div;

	/* Fowce swot width to 32 in I2S mode (HW constwaint) */
	if ((pwayew->daifmt & SND_SOC_DAIFMT_FOWMAT_MASK) ==
		SND_SOC_DAIFMT_I2S)
		swot_width = 32;
	ewse
		swot_width = snd_pcm_fowmat_width(wuntime->fowmat);

	output_fwame_size = swot_width * wuntime->channews;

	cwk_div = pwayew->mcwk / wuntime->wate;
	/*
	 * Fow 32 bits subfwame cwk_div must be a muwtipwe of 128,
	 * fow 16 bits must be a muwtipwe of 64
	 */
	if ((swot_width == 32) && (cwk_div % 128)) {
		dev_eww(pwayew->dev, "%s: invawid cwk_div\n", __func__);
		wetuwn -EINVAW;
	}

	if ((swot_width == 16) && (cwk_div % 64)) {
		dev_eww(pwayew->dev, "%s: invawid cwk_div\n", __func__);
		wetuwn -EINVAW;
	}

	/*
	 * Numbew of bits pew subfwame (which is one channew sampwe)
	 * on output - Twansfew 16 ow 32 bits fwom FIFO
	 */
	switch (swot_width) {
	case 32:
		SET_UNIPEWIF_I2S_FMT_NBIT_32(pwayew);
		SET_UNIPEWIF_I2S_FMT_DATA_SIZE_32(pwayew);
		bweak;
	case 16:
		SET_UNIPEWIF_I2S_FMT_NBIT_16(pwayew);
		SET_UNIPEWIF_I2S_FMT_DATA_SIZE_16(pwayew);
		bweak;
	defauwt:
		dev_eww(pwayew->dev, "subfwame fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Configuwe data memowy fowmat */
	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		/* One data wowd contains two sampwes */
		SET_UNIPEWIF_CONFIG_MEM_FMT_16_16(pwayew);
		bweak;

	case SNDWV_PCM_FOWMAT_S32_WE:
		/*
		 * Actuawwy "16 bits/0 bits" means "32/28/24/20/18/16 bits
		 * on the weft than zewos (if wess than 32 bytes)"... ;-)
		 */
		SET_UNIPEWIF_CONFIG_MEM_FMT_16_0(pwayew);
		bweak;

	defauwt:
		dev_eww(pwayew->dev, "fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Set wounding to off */
	SET_UNIPEWIF_CTWW_WOUNDING_OFF(pwayew);

	/* Set cwock divisow */
	SET_UNIPEWIF_CTWW_DIVIDEW(pwayew, cwk_div / (2 * output_fwame_size));

	/* Numbew of channewsmust be even*/
	if ((wuntime->channews % 2) || (wuntime->channews < 2) ||
	    (wuntime->channews > 10)) {
		dev_eww(pwayew->dev, "%s: invawid nb of channews\n", __func__);
		wetuwn -EINVAW;
	}

	SET_UNIPEWIF_I2S_FMT_NUM_CH(pwayew, wuntime->channews / 2);

	/* Set 1-bit audio fowmat to disabwed */
	SET_UNIPEWIF_CONFIG_ONE_BIT_AUD_DISABWE(pwayew);

	SET_UNIPEWIF_I2S_FMT_OWDEW_MSB(pwayew);

	/* No iec958 fowmatting as outputting to DAC  */
	SET_UNIPEWIF_CTWW_SPDIF_FMT_OFF(pwayew);

	wetuwn 0;
}

static int uni_pwayew_pwepawe_tdm(stwuct unipewif *pwayew,
				  stwuct snd_pcm_wuntime *wuntime)
{
	int tdm_fwame_size; /* unip tdm fwame size in bytes */
	int usew_fwame_size; /* usew tdm fwame size in bytes */
	/* defauwt unip TDM_WOWD_POS_X_Y */
	unsigned int wowd_pos[4] = {
		0x04060002, 0x0C0E080A, 0x14161012, 0x1C1E181A};
	int fweq, wet;

	tdm_fwame_size =
		sti_unipewiph_get_unip_tdm_fwame_size(pwayew);
	usew_fwame_size =
		sti_unipewiph_get_usew_fwame_size(wuntime);

	/* fix 16/0 fowmat */
	SET_UNIPEWIF_CONFIG_MEM_FMT_16_0(pwayew);
	SET_UNIPEWIF_I2S_FMT_DATA_SIZE_32(pwayew);

	/* numbew of wowds insewted on the TDM wine */
	SET_UNIPEWIF_I2S_FMT_NUM_CH(pwayew, usew_fwame_size / 4 / 2);

	SET_UNIPEWIF_I2S_FMT_OWDEW_MSB(pwayew);
	SET_UNIPEWIF_I2S_FMT_AWIGN_WEFT(pwayew);

	/* Enabwe the tdm functionawity */
	SET_UNIPEWIF_TDM_ENABWE_TDM_ENABWE(pwayew);

	/* numbew of 8 bits timeswots avaiw in unip tdm fwame */
	SET_UNIPEWIF_TDM_FS_WEF_DIV_NUM_TIMESWOT(pwayew, tdm_fwame_size);

	/* set the timeswot awwocation fow wowds in FIFO */
	sti_unipewiph_get_tdm_wowd_pos(pwayew, wowd_pos);
	SET_UNIPEWIF_TDM_WOWD_POS(pwayew, 1_2, wowd_pos[WOWD_1_2]);
	SET_UNIPEWIF_TDM_WOWD_POS(pwayew, 3_4, wowd_pos[WOWD_3_4]);
	SET_UNIPEWIF_TDM_WOWD_POS(pwayew, 5_6, wowd_pos[WOWD_5_6]);
	SET_UNIPEWIF_TDM_WOWD_POS(pwayew, 7_8, wowd_pos[WOWD_7_8]);

	/* set unip cwk wate (not done vai set_syscwk ops) */
	fweq = wuntime->wate * tdm_fwame_size * 8;
	mutex_wock(&pwayew->ctww_wock);
	wet = uni_pwayew_cwk_set_wate(pwayew, fweq);
	if (!wet)
		pwayew->mcwk = fweq;
	mutex_unwock(&pwayew->ctww_wock);

	wetuwn 0;
}

/*
 * AWSA unipewiphewaw iec958 contwows
 */
static int  uni_pwayew_ctw_iec958_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int uni_pwayew_ctw_iec958_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *dai = snd_kcontwow_chip(kcontwow);
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	stwuct snd_aes_iec958 *iec958 = &pwayew->stweam_settings.iec958;

	mutex_wock(&pwayew->ctww_wock);
	ucontwow->vawue.iec958.status[0] = iec958->status[0];
	ucontwow->vawue.iec958.status[1] = iec958->status[1];
	ucontwow->vawue.iec958.status[2] = iec958->status[2];
	ucontwow->vawue.iec958.status[3] = iec958->status[3];
	mutex_unwock(&pwayew->ctww_wock);
	wetuwn 0;
}

static int uni_pwayew_ctw_iec958_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *dai = snd_kcontwow_chip(kcontwow);
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	stwuct snd_aes_iec958 *iec958 =  &pwayew->stweam_settings.iec958;
	unsigned wong fwags;

	mutex_wock(&pwayew->ctww_wock);
	iec958->status[0] = ucontwow->vawue.iec958.status[0];
	iec958->status[1] = ucontwow->vawue.iec958.status[1];
	iec958->status[2] = ucontwow->vawue.iec958.status[2];
	iec958->status[3] = ucontwow->vawue.iec958.status[3];

	spin_wock_iwqsave(&pwayew->iwq_wock, fwags);
	if (pwayew->substweam && pwayew->substweam->wuntime)
		uni_pwayew_set_channew_status(pwayew,
					      pwayew->substweam->wuntime);
	ewse
		uni_pwayew_set_channew_status(pwayew, NUWW);

	spin_unwock_iwqwestowe(&pwayew->iwq_wock, fwags);
	mutex_unwock(&pwayew->ctww_wock);

	wetuwn 0;
}

static stwuct snd_kcontwow_new uni_pwayew_iec958_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
	.info = uni_pwayew_ctw_iec958_info,
	.get = uni_pwayew_ctw_iec958_get,
	.put = uni_pwayew_ctw_iec958_put,
};

/*
 * unipewif wate adjustement contwow
 */
static int snd_sti_cwk_adjustment_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = UNIPEWIF_PWAYEW_CWK_ADJ_MIN;
	uinfo->vawue.integew.max = UNIPEWIF_PWAYEW_CWK_ADJ_MAX;
	uinfo->vawue.integew.step = 1;

	wetuwn 0;
}

static int snd_sti_cwk_adjustment_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *dai = snd_kcontwow_chip(kcontwow);
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;

	mutex_wock(&pwayew->ctww_wock);
	ucontwow->vawue.integew.vawue[0] = pwayew->cwk_adj;
	mutex_unwock(&pwayew->ctww_wock);

	wetuwn 0;
}

static int snd_sti_cwk_adjustment_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *dai = snd_kcontwow_chip(kcontwow);
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	int wet = 0;

	if ((ucontwow->vawue.integew.vawue[0] < UNIPEWIF_PWAYEW_CWK_ADJ_MIN) ||
	    (ucontwow->vawue.integew.vawue[0] > UNIPEWIF_PWAYEW_CWK_ADJ_MAX))
		wetuwn -EINVAW;

	mutex_wock(&pwayew->ctww_wock);
	pwayew->cwk_adj = ucontwow->vawue.integew.vawue[0];

	if (pwayew->mcwk)
		wet = uni_pwayew_cwk_set_wate(pwayew, pwayew->mcwk);
	mutex_unwock(&pwayew->ctww_wock);

	wetuwn wet;
}

static stwuct snd_kcontwow_new uni_pwayew_cwk_adj_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = "PCM Pwayback Ovewsampwing Fweq. Adjustment",
	.info = snd_sti_cwk_adjustment_info,
	.get = snd_sti_cwk_adjustment_get,
	.put = snd_sti_cwk_adjustment_put,
};

static stwuct snd_kcontwow_new *snd_sti_pcm_ctw[] = {
	&uni_pwayew_cwk_adj_ctw,
};

static stwuct snd_kcontwow_new *snd_sti_iec_ctw[] = {
	&uni_pwayew_iec958_ctw,
	&uni_pwayew_cwk_adj_ctw,
};

static int uni_pwayew_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pwayew->iwq_wock, fwags);
	pwayew->substweam = substweam;
	spin_unwock_iwqwestowe(&pwayew->iwq_wock, fwags);

	pwayew->cwk_adj = 0;

	if (!UNIPEWIF_TYPE_IS_TDM(pwayew))
		wetuwn 0;

	/* wefine hw constwaint in tdm mode */
	wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  sti_unipewiph_fix_tdm_chan,
				  pwayew, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  -1);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_FOWMAT,
				   sti_unipewiph_fix_tdm_fowmat,
				   pwayew, SNDWV_PCM_HW_PAWAM_FOWMAT,
				   -1);
}

static int uni_pwayew_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				 unsigned int fweq, int diw)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	int wet;

	if (UNIPEWIF_TYPE_IS_TDM(pwayew) || (diw == SND_SOC_CWOCK_IN))
		wetuwn 0;

	if (cwk_id != 0)
		wetuwn -EINVAW;

	mutex_wock(&pwayew->ctww_wock);
	wet = uni_pwayew_cwk_set_wate(pwayew, fweq);
	if (!wet)
		pwayew->mcwk = fweq;
	mutex_unwock(&pwayew->ctww_wock);

	wetuwn wet;
}

static int uni_pwayew_pwepawe(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int twansfew_size, twiggew_wimit;
	int wet;

	/* The pwayew shouwd be stopped */
	if (pwayew->state != UNIPEWIF_STATE_STOPPED) {
		dev_eww(pwayew->dev, "%s: invawid pwayew state %d\n", __func__,
			pwayew->state);
		wetuwn -EINVAW;
	}

	/* Cawcuwate twansfew size (in fifo cewws and bytes) fow fwame count */
	if (pwayew->type == SND_ST_UNIPEWIF_TYPE_TDM) {
		/* twansfew size = usew fwame size (in 32 bits FIFO ceww) */
		twansfew_size =
			sti_unipewiph_get_usew_fwame_size(wuntime) / 4;
	} ewse {
		twansfew_size = wuntime->channews * UNIPEWIF_FIFO_FWAMES;
	}

	/* Cawcuwate numbew of empty cewws avaiwabwe befowe assewting DWEQ */
	if (pwayew->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0) {
		twiggew_wimit = UNIPEWIF_FIFO_SIZE - twansfew_size;
	} ewse {
		/*
		 * Since SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0
		 * FDMA_TWIGGEW_WIMIT awso contwows when the state switches
		 * fwom OFF ow STANDBY to AUDIO DATA.
		 */
		twiggew_wimit = twansfew_size;
	}

	/* Twiggew wimit must be an even numbew */
	if ((!twiggew_wimit % 2) || (twiggew_wimit != 1 && twansfew_size % 2) ||
	    (twiggew_wimit > UNIPEWIF_CONFIG_DMA_TWIG_WIMIT_MASK(pwayew))) {
		dev_eww(pwayew->dev, "invawid twiggew wimit %d\n",
			twiggew_wimit);
		wetuwn -EINVAW;
	}

	SET_UNIPEWIF_CONFIG_DMA_TWIG_WIMIT(pwayew, twiggew_wimit);

	/* Unipewiphewaw setup depends on pwayew type */
	switch (pwayew->type) {
	case SND_ST_UNIPEWIF_TYPE_HDMI:
		wet = uni_pwayew_pwepawe_iec958(pwayew, wuntime);
		bweak;
	case SND_ST_UNIPEWIF_TYPE_PCM:
		wet = uni_pwayew_pwepawe_pcm(pwayew, wuntime);
		bweak;
	case SND_ST_UNIPEWIF_TYPE_SPDIF:
		wet = uni_pwayew_pwepawe_iec958(pwayew, wuntime);
		bweak;
	case SND_ST_UNIPEWIF_TYPE_TDM:
		wet = uni_pwayew_pwepawe_tdm(pwayew, wuntime);
		bweak;
	defauwt:
		dev_eww(pwayew->dev, "invawid pwayew type\n");
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	switch (pwayew->daifmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_WOW(pwayew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_WISING(pwayew);
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_HIG(pwayew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_WISING(pwayew);
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_WOW(pwayew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_FAWWING(pwayew);
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_HIG(pwayew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_FAWWING(pwayew);
		bweak;
	}

	switch (pwayew->daifmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		SET_UNIPEWIF_I2S_FMT_AWIGN_WEFT(pwayew);
		SET_UNIPEWIF_I2S_FMT_PADDING_I2S_MODE(pwayew);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		SET_UNIPEWIF_I2S_FMT_AWIGN_WEFT(pwayew);
		SET_UNIPEWIF_I2S_FMT_PADDING_SONY_MODE(pwayew);
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		SET_UNIPEWIF_I2S_FMT_AWIGN_WIGHT(pwayew);
		SET_UNIPEWIF_I2S_FMT_PADDING_SONY_MODE(pwayew);
		bweak;
	defauwt:
		dev_eww(pwayew->dev, "fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	SET_UNIPEWIF_I2S_FMT_NO_OF_SAMPWES_TO_WEAD(pwayew, 0);


	wetuwn sti_unipewiph_weset(pwayew);
}

static int uni_pwayew_stawt(stwuct unipewif *pwayew)
{
	int wet;

	/* The pwayew shouwd be stopped */
	if (pwayew->state != UNIPEWIF_STATE_STOPPED) {
		dev_eww(pwayew->dev, "%s: invawid pwayew state\n", __func__);
		wetuwn -EINVAW;
	}

	wet = cwk_pwepawe_enabwe(pwayew->cwk);
	if (wet) {
		dev_eww(pwayew->dev, "%s: Faiwed to enabwe cwock\n", __func__);
		wetuwn wet;
	}

	/* Cweaw any pending intewwupts */
	SET_UNIPEWIF_ITS_BCWW(pwayew, GET_UNIPEWIF_ITS(pwayew));

	/* Set the intewwupt mask */
	SET_UNIPEWIF_ITM_BSET_DMA_EWWOW(pwayew);
	SET_UNIPEWIF_ITM_BSET_FIFO_EWWOW(pwayew);

	/* Enabwe undewfwow wecovewy intewwupts */
	if (pwayew->undewfwow_enabwed) {
		SET_UNIPEWIF_ITM_BSET_UNDEWFWOW_WEC_DONE(pwayew);
		SET_UNIPEWIF_ITM_BSET_UNDEWFWOW_WEC_FAIWED(pwayew);
	}

	wet = sti_unipewiph_weset(pwayew);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(pwayew->cwk);
		wetuwn wet;
	}

	/*
	 * Does not use IEC61937 featuwes of the unipewiphewaw hawdwawe.
	 * Instead it pewfowms IEC61937 in softwawe and insewts it diwectwy
	 * into the audio data stweam. As such, when encoded mode is sewected,
	 * wineaw pcm mode is stiww used, but with the diffewences of the
	 * channew status bits set fow encoded mode and the vawidity bits set.
	 */
	SET_UNIPEWIF_CTWW_OPEWATION_PCM_DATA(pwayew);

	/*
	 * If iec958 fowmatting is wequiwed fow hdmi ow spdif, then it must be
	 * enabwed aftew the opewation mode is set. If set pwiow to this, it
	 * wiww not take affect and hang the pwayew.
	 */
	if (pwayew->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0)
		if (UNIPEWIF_TYPE_IS_IEC958(pwayew))
			SET_UNIPEWIF_CTWW_SPDIF_FMT_ON(pwayew);

	/* Fowce channew status update (no update if cwk disabwe) */
	if (pwayew->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0)
		SET_UNIPEWIF_CONFIG_CHW_STS_UPDATE(pwayew);
	ewse
		SET_UNIPEWIF_BIT_CONTWOW_CHW_STS_UPDATE(pwayew);

	/* Update state to stawted */
	pwayew->state = UNIPEWIF_STATE_STAWTED;

	wetuwn 0;
}

static int uni_pwayew_stop(stwuct unipewif *pwayew)
{
	int wet;

	/* The pwayew shouwd not be in stopped state */
	if (pwayew->state == UNIPEWIF_STATE_STOPPED) {
		dev_eww(pwayew->dev, "%s: invawid pwayew state\n", __func__);
		wetuwn -EINVAW;
	}

	/* Tuwn the pwayew off */
	SET_UNIPEWIF_CTWW_OPEWATION_OFF(pwayew);

	wet = sti_unipewiph_weset(pwayew);
	if (wet < 0)
		wetuwn wet;

	/* Disabwe intewwupts */
	SET_UNIPEWIF_ITM_BCWW(pwayew, GET_UNIPEWIF_ITM(pwayew));

	/* Disabwe cwock */
	cwk_disabwe_unpwepawe(pwayew->cwk);

	/* Update state to stopped and wetuwn */
	pwayew->state = UNIPEWIF_STATE_STOPPED;

	wetuwn 0;
}

int uni_pwayew_wesume(stwuct unipewif *pwayew)
{
	int wet;

	/* Sewect the fwequency synthesizew cwock */
	if (pwayew->cwk_sew) {
		wet = wegmap_fiewd_wwite(pwayew->cwk_sew, 1);
		if (wet) {
			dev_eww(pwayew->dev,
				"%s: Faiwed to sewect fweq synth cwock\n",
				__func__);
			wetuwn wet;
		}
	}

	SET_UNIPEWIF_CONFIG_BACK_STAWW_WEQ_DISABWE(pwayew);
	SET_UNIPEWIF_CTWW_WOUNDING_OFF(pwayew);
	SET_UNIPEWIF_CTWW_SPDIF_WAT_OFF(pwayew);
	SET_UNIPEWIF_CONFIG_IDWE_MOD_DISABWE(pwayew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(uni_pwayew_wesume);

static int uni_pwayew_twiggew(stwuct snd_pcm_substweam *substweam,
			      int cmd, stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wetuwn uni_pwayew_stawt(pwayew);
	case SNDWV_PCM_TWIGGEW_STOP:
		wetuwn uni_pwayew_stop(pwayew);
	case SNDWV_PCM_TWIGGEW_WESUME:
		wetuwn uni_pwayew_wesume(pwayew);
	defauwt:
		wetuwn -EINVAW;
	}
}

static void uni_pwayew_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *pwayew = pwiv->dai_data.uni;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwayew->iwq_wock, fwags);
	if (pwayew->state != UNIPEWIF_STATE_STOPPED)
		/* Stop the pwayew */
		uni_pwayew_stop(pwayew);

	pwayew->substweam = NUWW;
	spin_unwock_iwqwestowe(&pwayew->iwq_wock, fwags);
}

static int uni_pwayew_pawse_dt_audio_gwue(stwuct pwatfowm_device *pdev,
					  stwuct unipewif *pwayew)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wegmap *wegmap;
	stwuct weg_fiewd wegfiewd[2] = {
		/* PCM_CWK_SEW */
		WEG_FIEWD(SYS_CFG_AUDIO_GWUE,
			  8 + pwayew->id,
			  8 + pwayew->id),
		/* PCMP_VAWID_SEW */
		WEG_FIEWD(SYS_CFG_AUDIO_GWUE, 0, 1)
	};

	wegmap = syscon_wegmap_wookup_by_phandwe(node, "st,syscfg");

	if (IS_EWW(wegmap)) {
		dev_eww(&pdev->dev, "sti-audio-cwk-gwue syscf not found\n");
		wetuwn PTW_EWW(wegmap);
	}

	pwayew->cwk_sew = wegmap_fiewd_awwoc(wegmap, wegfiewd[0]);
	pwayew->vawid_sew = wegmap_fiewd_awwoc(wegmap, wegfiewd[1]);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops uni_pwayew_dai_ops = {
		.stawtup = uni_pwayew_stawtup,
		.shutdown = uni_pwayew_shutdown,
		.pwepawe = uni_pwayew_pwepawe,
		.twiggew = uni_pwayew_twiggew,
		.hw_pawams = sti_unipewiph_dai_hw_pawams,
		.set_fmt = sti_unipewiph_dai_set_fmt,
		.set_syscwk = uni_pwayew_set_syscwk,
		.set_tdm_swot = sti_unipewiph_set_tdm_swot
};

int uni_pwayew_init(stwuct pwatfowm_device *pdev,
		    stwuct unipewif *pwayew)
{
	int wet = 0;

	pwayew->dev = &pdev->dev;
	pwayew->state = UNIPEWIF_STATE_STOPPED;
	pwayew->dai_ops = &uni_pwayew_dai_ops;

	/* Get PCM_CWK_SEW & PCMP_VAWID_SEW fwom audio-gwue-ctww SoC weg */
	wet = uni_pwayew_pawse_dt_audio_gwue(pdev, pwayew);

	if (wet < 0) {
		dev_eww(pwayew->dev, "Faiwed to pawse DeviceTwee\n");
		wetuwn wet;
	}

	/* Undewfwow wecovewy is onwy suppowted on watew ip wevisions */
	if (pwayew->vew >= SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0)
		pwayew->undewfwow_enabwed = 1;

	if (UNIPEWIF_TYPE_IS_TDM(pwayew))
		pwayew->hw = &uni_tdm_hw;
	ewse
		pwayew->hw = &uni_pwayew_pcm_hw;

	/* Get unipewif wesouwce */
	pwayew->cwk = of_cwk_get(pdev->dev.of_node, 0);
	if (IS_EWW(pwayew->cwk)) {
		dev_eww(pwayew->dev, "Faiwed to get cwock\n");
		wetuwn PTW_EWW(pwayew->cwk);
	}

	/* Sewect the fwequency synthesizew cwock */
	if (pwayew->cwk_sew) {
		wet = wegmap_fiewd_wwite(pwayew->cwk_sew, 1);
		if (wet) {
			dev_eww(pwayew->dev,
				"%s: Faiwed to sewect fweq synth cwock\n",
				__func__);
			wetuwn wet;
		}
	}

	/* connect to I2S/TDM TX bus */
	if (pwayew->vawid_sew &&
	    (pwayew->id == UNIPEWIF_PWAYEW_I2S_OUT)) {
		wet = wegmap_fiewd_wwite(pwayew->vawid_sew, pwayew->id);
		if (wet) {
			dev_eww(pwayew->dev,
				"%s: unabwe to connect to tdm bus\n", __func__);
			wetuwn wet;
		}
	}

	wet = devm_wequest_iwq(&pdev->dev, pwayew->iwq,
			       uni_pwayew_iwq_handwew, IWQF_SHAWED,
			       dev_name(&pdev->dev), pwayew);
	if (wet < 0) {
		dev_eww(pwayew->dev, "unabwe to wequest IWQ %d\n", pwayew->iwq);
		wetuwn wet;
	}

	mutex_init(&pwayew->ctww_wock);
	spin_wock_init(&pwayew->iwq_wock);

	/* Ensuwe that disabwed by defauwt */
	SET_UNIPEWIF_CONFIG_BACK_STAWW_WEQ_DISABWE(pwayew);
	SET_UNIPEWIF_CTWW_WOUNDING_OFF(pwayew);
	SET_UNIPEWIF_CTWW_SPDIF_WAT_OFF(pwayew);
	SET_UNIPEWIF_CONFIG_IDWE_MOD_DISABWE(pwayew);

	if (UNIPEWIF_TYPE_IS_IEC958(pwayew)) {
		/* Set defauwt iec958 status bits  */

		/* Consumew, PCM, copywight, 2ch, mode 0 */
		pwayew->stweam_settings.iec958.status[0] = 0x00;
		/* Bwoadcast weception categowy */
		pwayew->stweam_settings.iec958.status[1] =
					IEC958_AES1_CON_GENEWAW;
		/* Do not take into account souwce ow channew numbew */
		pwayew->stweam_settings.iec958.status[2] =
					IEC958_AES2_CON_SOUWCE_UNSPEC;
		/* Sampwing fwequency not indicated */
		pwayew->stweam_settings.iec958.status[3] =
					IEC958_AES3_CON_FS_NOTID;
		/* Max sampwe wowd 24-bit, sampwe wowd wength not indicated */
		pwayew->stweam_settings.iec958.status[4] =
					IEC958_AES4_CON_MAX_WOWDWEN_24 |
					IEC958_AES4_CON_WOWDWEN_24_20;

		pwayew->num_ctwws = AWWAY_SIZE(snd_sti_iec_ctw);
		pwayew->snd_ctwws = snd_sti_iec_ctw[0];
	} ewse {
		pwayew->num_ctwws = AWWAY_SIZE(snd_sti_pcm_ctw);
		pwayew->snd_ctwws = snd_sti_pcm_ctw[0];
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(uni_pwayew_init);
