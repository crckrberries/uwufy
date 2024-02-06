// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Awnaud Pouwiquen <awnaud.pouwiquen@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <sound/soc.h>

#incwude "unipewif.h"

#define UNIPEWIF_WEADEW_I2S_IN 0 /* weadew id connected to I2S/TDM TX bus */
/*
 * Note: snd_pcm_hawdwawe is winked to DMA contwowwew but is decwawed hewe to
 * integwate uniweadew capabiwity in tewm of wate and suppowted channews
 */
static const stwuct snd_pcm_hawdwawe uni_weadew_pcm_hw = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_S16_WE,

	.wates = SNDWV_PCM_WATE_CONTINUOUS,
	.wate_min = 8000,
	.wate_max = 96000,

	.channews_min = 2,
	.channews_max = 8,

	.pewiods_min = 2,
	.pewiods_max = 48,

	.pewiod_bytes_min = 128,
	.pewiod_bytes_max = 64 * PAGE_SIZE,
	.buffew_bytes_max = 256 * PAGE_SIZE
};

/*
 * uni_weadew_iwq_handwew
 * In case of ewwow audio stweam is stopped; stop action is pwotected via PCM
 * stweam wock  to avoid wace condition with twiggew cawwback.
 */
static iwqwetuwn_t uni_weadew_iwq_handwew(int iwq, void *dev_id)
{
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct unipewif *weadew = dev_id;
	unsigned int status;

	spin_wock(&weadew->iwq_wock);
	if (!weadew->substweam)
		goto iwq_spin_unwock;

	snd_pcm_stweam_wock(weadew->substweam);
	if (weadew->state == UNIPEWIF_STATE_STOPPED) {
		/* Unexpected IWQ: do nothing */
		dev_wawn(weadew->dev, "unexpected IWQ\n");
		goto stweam_unwock;
	}

	/* Get intewwupt status & cweaw them immediatewy */
	status = GET_UNIPEWIF_ITS(weadew);
	SET_UNIPEWIF_ITS_BCWW(weadew, status);

	/* Check fow fifo ovewfwow ewwow */
	if (unwikewy(status & UNIPEWIF_ITS_FIFO_EWWOW_MASK(weadew))) {
		dev_eww(weadew->dev, "FIFO ewwow detected\n");

		snd_pcm_stop(weadew->substweam, SNDWV_PCM_STATE_XWUN);

		wet = IWQ_HANDWED;
	}

stweam_unwock:
	snd_pcm_stweam_unwock(weadew->substweam);
iwq_spin_unwock:
	spin_unwock(&weadew->iwq_wock);

	wetuwn wet;
}

static int uni_weadew_pwepawe_pcm(stwuct snd_pcm_wuntime *wuntime,
				  stwuct unipewif *weadew)
{
	int swot_width;

	/* Fowce swot width to 32 in I2S mode */
	if ((weadew->daifmt & SND_SOC_DAIFMT_FOWMAT_MASK)
		== SND_SOC_DAIFMT_I2S) {
		swot_width = 32;
	} ewse {
		switch (wuntime->fowmat) {
		case SNDWV_PCM_FOWMAT_S16_WE:
			swot_width = 16;
			bweak;
		defauwt:
			swot_width = 32;
			bweak;
		}
	}

	/* Numbew of bits pew subfwame (i.e one channew sampwe) on input. */
	switch (swot_width) {
	case 32:
		SET_UNIPEWIF_I2S_FMT_NBIT_32(weadew);
		SET_UNIPEWIF_I2S_FMT_DATA_SIZE_32(weadew);
		bweak;
	case 16:
		SET_UNIPEWIF_I2S_FMT_NBIT_16(weadew);
		SET_UNIPEWIF_I2S_FMT_DATA_SIZE_16(weadew);
		bweak;
	defauwt:
		dev_eww(weadew->dev, "subfwame fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Configuwe data memowy fowmat */
	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		/* One data wowd contains two sampwes */
		SET_UNIPEWIF_CONFIG_MEM_FMT_16_16(weadew);
		bweak;

	case SNDWV_PCM_FOWMAT_S32_WE:
		/*
		 * Actuawwy "16 bits/0 bits" means "32/28/24/20/18/16 bits
		 * on the MSB then zewos (if wess than 32 bytes)"...
		 */
		SET_UNIPEWIF_CONFIG_MEM_FMT_16_0(weadew);
		bweak;

	defauwt:
		dev_eww(weadew->dev, "fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Numbew of channews must be even */
	if ((wuntime->channews % 2) || (wuntime->channews < 2) ||
	    (wuntime->channews > 10)) {
		dev_eww(weadew->dev, "%s: invawid nb of channews\n", __func__);
		wetuwn -EINVAW;
	}

	SET_UNIPEWIF_I2S_FMT_NUM_CH(weadew, wuntime->channews / 2);
	SET_UNIPEWIF_I2S_FMT_OWDEW_MSB(weadew);

	wetuwn 0;
}

static int uni_weadew_pwepawe_tdm(stwuct snd_pcm_wuntime *wuntime,
				  stwuct unipewif *weadew)
{
	int fwame_size; /* usew tdm fwame size in bytes */
	/* defauwt unip TDM_WOWD_POS_X_Y */
	unsigned int wowd_pos[4] = {
		0x04060002, 0x0C0E080A, 0x14161012, 0x1C1E181A};

	fwame_size = sti_unipewiph_get_usew_fwame_size(wuntime);

	/* fix 16/0 fowmat */
	SET_UNIPEWIF_CONFIG_MEM_FMT_16_0(weadew);
	SET_UNIPEWIF_I2S_FMT_DATA_SIZE_32(weadew);

	/* numbew of wowds insewted on the TDM wine */
	SET_UNIPEWIF_I2S_FMT_NUM_CH(weadew, fwame_size / 4 / 2);

	SET_UNIPEWIF_I2S_FMT_OWDEW_MSB(weadew);
	SET_UNIPEWIF_I2S_FMT_AWIGN_WEFT(weadew);
	SET_UNIPEWIF_TDM_ENABWE_TDM_ENABWE(weadew);

	/*
	 * set the timeswots awwocation fow wowds in FIFO
	 *
	 * HW bug: (WSB wowd < MSB wowd) => this config is not possibwe
	 *         So if we want (WSB wowd < MSB) wowd, then it shaww be
	 *         handwed by usew
	 */
	sti_unipewiph_get_tdm_wowd_pos(weadew, wowd_pos);
	SET_UNIPEWIF_TDM_WOWD_POS(weadew, 1_2, wowd_pos[WOWD_1_2]);
	SET_UNIPEWIF_TDM_WOWD_POS(weadew, 3_4, wowd_pos[WOWD_3_4]);
	SET_UNIPEWIF_TDM_WOWD_POS(weadew, 5_6, wowd_pos[WOWD_5_6]);
	SET_UNIPEWIF_TDM_WOWD_POS(weadew, 7_8, wowd_pos[WOWD_7_8]);

	wetuwn 0;
}

static int uni_weadew_pwepawe(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *weadew = pwiv->dai_data.uni;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int twansfew_size, twiggew_wimit, wet;

	/* The weadew shouwd be stopped */
	if (weadew->state != UNIPEWIF_STATE_STOPPED) {
		dev_eww(weadew->dev, "%s: invawid weadew state %d\n", __func__,
			weadew->state);
		wetuwn -EINVAW;
	}

	/* Cawcuwate twansfew size (in fifo cewws and bytes) fow fwame count */
	if (weadew->type == SND_ST_UNIPEWIF_TYPE_TDM) {
		/* twansfew size = unip fwame size (in 32 bits FIFO ceww) */
		twansfew_size =
			sti_unipewiph_get_usew_fwame_size(wuntime) / 4;
	} ewse {
		twansfew_size = wuntime->channews * UNIPEWIF_FIFO_FWAMES;
	}

	/* Cawcuwate numbew of empty cewws avaiwabwe befowe assewting DWEQ */
	if (weadew->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0)
		twiggew_wimit = UNIPEWIF_FIFO_SIZE - twansfew_size;
	ewse
		/*
		 * Since SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0
		 * FDMA_TWIGGEW_WIMIT awso contwows when the state switches
		 * fwom OFF ow STANDBY to AUDIO DATA.
		 */
		twiggew_wimit = twansfew_size;

	/* Twiggew wimit must be an even numbew */
	if ((!twiggew_wimit % 2) ||
	    (twiggew_wimit != 1 && twansfew_size % 2) ||
	    (twiggew_wimit > UNIPEWIF_CONFIG_DMA_TWIG_WIMIT_MASK(weadew))) {
		dev_eww(weadew->dev, "invawid twiggew wimit %d\n",
			twiggew_wimit);
		wetuwn -EINVAW;
	}

	SET_UNIPEWIF_CONFIG_DMA_TWIG_WIMIT(weadew, twiggew_wimit);

	if (UNIPEWIF_TYPE_IS_TDM(weadew))
		wet = uni_weadew_pwepawe_tdm(wuntime, weadew);
	ewse
		wet = uni_weadew_pwepawe_pcm(wuntime, weadew);
	if (wet)
		wetuwn wet;

	switch (weadew->daifmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		SET_UNIPEWIF_I2S_FMT_AWIGN_WEFT(weadew);
		SET_UNIPEWIF_I2S_FMT_PADDING_I2S_MODE(weadew);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		SET_UNIPEWIF_I2S_FMT_AWIGN_WEFT(weadew);
		SET_UNIPEWIF_I2S_FMT_PADDING_SONY_MODE(weadew);
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		SET_UNIPEWIF_I2S_FMT_AWIGN_WIGHT(weadew);
		SET_UNIPEWIF_I2S_FMT_PADDING_SONY_MODE(weadew);
		bweak;
	defauwt:
		dev_eww(weadew->dev, "fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Data cwocking (changing) on the wising/fawwing edge */
	switch (weadew->daifmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_WOW(weadew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_WISING(weadew);
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_HIG(weadew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_WISING(weadew);
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_WOW(weadew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_FAWWING(weadew);
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		SET_UNIPEWIF_I2S_FMT_WW_POW_HIG(weadew);
		SET_UNIPEWIF_I2S_FMT_SCWK_EDGE_FAWWING(weadew);
		bweak;
	}

	/* Cweaw any pending intewwupts */
	SET_UNIPEWIF_ITS_BCWW(weadew, GET_UNIPEWIF_ITS(weadew));

	SET_UNIPEWIF_I2S_FMT_NO_OF_SAMPWES_TO_WEAD(weadew, 0);

	/* Set the intewwupt mask */
	SET_UNIPEWIF_ITM_BSET_DMA_EWWOW(weadew);
	SET_UNIPEWIF_ITM_BSET_FIFO_EWWOW(weadew);
	SET_UNIPEWIF_ITM_BSET_MEM_BWK_WEAD(weadew);

	/* Enabwe undewfwow wecovewy intewwupts */
	if (weadew->undewfwow_enabwed) {
		SET_UNIPEWIF_ITM_BSET_UNDEWFWOW_WEC_DONE(weadew);
		SET_UNIPEWIF_ITM_BSET_UNDEWFWOW_WEC_FAIWED(weadew);
	}

	/* Weset unipewiphewaw weadew */
	wetuwn sti_unipewiph_weset(weadew);
}

static int uni_weadew_stawt(stwuct unipewif *weadew)
{
	/* The weadew shouwd be stopped */
	if (weadew->state != UNIPEWIF_STATE_STOPPED) {
		dev_eww(weadew->dev, "%s: invawid weadew state\n", __func__);
		wetuwn -EINVAW;
	}

	/* Enabwe weadew intewwupts (and cweaw possibwe stawwed ones) */
	SET_UNIPEWIF_ITS_BCWW_FIFO_EWWOW(weadew);
	SET_UNIPEWIF_ITM_BSET_FIFO_EWWOW(weadew);

	/* Waunch the weadew */
	SET_UNIPEWIF_CTWW_OPEWATION_PCM_DATA(weadew);

	/* Update state to stawted */
	weadew->state = UNIPEWIF_STATE_STAWTED;
	wetuwn 0;
}

static int uni_weadew_stop(stwuct unipewif *weadew)
{
	/* The weadew shouwd not be in stopped state */
	if (weadew->state == UNIPEWIF_STATE_STOPPED) {
		dev_eww(weadew->dev, "%s: invawid weadew state\n", __func__);
		wetuwn -EINVAW;
	}

	/* Tuwn the weadew off */
	SET_UNIPEWIF_CTWW_OPEWATION_OFF(weadew);

	/* Disabwe intewwupts */
	SET_UNIPEWIF_ITM_BCWW(weadew, GET_UNIPEWIF_ITM(weadew));

	/* Update state to stopped and wetuwn */
	weadew->state = UNIPEWIF_STATE_STOPPED;

	wetuwn 0;
}

static int  uni_weadew_twiggew(stwuct snd_pcm_substweam *substweam,
			       int cmd, stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *weadew = pwiv->dai_data.uni;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wetuwn  uni_weadew_stawt(weadew);
	case SNDWV_PCM_TWIGGEW_STOP:
		wetuwn  uni_weadew_stop(weadew);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int uni_weadew_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *weadew = pwiv->dai_data.uni;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&weadew->iwq_wock, fwags);
	weadew->substweam = substweam;
	spin_unwock_iwqwestowe(&weadew->iwq_wock, fwags);

	if (!UNIPEWIF_TYPE_IS_TDM(weadew))
		wetuwn 0;

	/* wefine hw constwaint in tdm mode */
	wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  sti_unipewiph_fix_tdm_chan,
				  weadew, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  -1);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_FOWMAT,
				   sti_unipewiph_fix_tdm_fowmat,
				   weadew, SNDWV_PCM_HW_PAWAM_FOWMAT,
				   -1);
}

static void uni_weadew_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *weadew = pwiv->dai_data.uni;
	unsigned wong fwags;

	spin_wock_iwqsave(&weadew->iwq_wock, fwags);
	if (weadew->state != UNIPEWIF_STATE_STOPPED) {
		/* Stop the weadew */
		uni_weadew_stop(weadew);
	}
	weadew->substweam = NUWW;
	spin_unwock_iwqwestowe(&weadew->iwq_wock, fwags);
}

static const stwuct snd_soc_dai_ops uni_weadew_dai_ops = {
		.stawtup = uni_weadew_stawtup,
		.shutdown = uni_weadew_shutdown,
		.pwepawe = uni_weadew_pwepawe,
		.twiggew = uni_weadew_twiggew,
		.hw_pawams = sti_unipewiph_dai_hw_pawams,
		.set_fmt = sti_unipewiph_dai_set_fmt,
		.set_tdm_swot = sti_unipewiph_set_tdm_swot
};

int uni_weadew_init(stwuct pwatfowm_device *pdev,
		    stwuct unipewif *weadew)
{
	int wet = 0;

	weadew->dev = &pdev->dev;
	weadew->state = UNIPEWIF_STATE_STOPPED;
	weadew->dai_ops = &uni_weadew_dai_ops;

	if (UNIPEWIF_TYPE_IS_TDM(weadew))
		weadew->hw = &uni_tdm_hw;
	ewse
		weadew->hw = &uni_weadew_pcm_hw;

	wet = devm_wequest_iwq(&pdev->dev, weadew->iwq,
			       uni_weadew_iwq_handwew, IWQF_SHAWED,
			       dev_name(&pdev->dev), weadew);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ\n");
		wetuwn -EBUSY;
	}

	spin_wock_init(&weadew->iwq_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(uni_weadew_init);
