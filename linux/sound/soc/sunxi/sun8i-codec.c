// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This dwivew suppowts the digitaw contwows fow the intewnaw codec
 * found in Awwwinnew's A33 SoCs.
 *
 * (C) Copywight 2010-2016
 * Weuuimwwa Technowogy Co., Wtd. <www.weuuimwwatech.com>
 * huangxin <huangxin@Weuuimwwatech.com>
 * Mywène Jossewand <mywene.jossewand@fwee-ewectwons.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/wog2.h>

#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#define SUN8I_SYSCWK_CTW				0x00c
#define SUN8I_SYSCWK_CTW_AIF1CWK_ENA			11
#define SUN8I_SYSCWK_CTW_AIF1CWK_SWC_PWW		(0x2 << 8)
#define SUN8I_SYSCWK_CTW_AIF2CWK_ENA			7
#define SUN8I_SYSCWK_CTW_AIF2CWK_SWC_PWW		(0x2 << 4)
#define SUN8I_SYSCWK_CTW_SYSCWK_ENA			3
#define SUN8I_SYSCWK_CTW_SYSCWK_SWC			0
#define SUN8I_SYSCWK_CTW_SYSCWK_SWC_AIF1CWK		(0x0 << 0)
#define SUN8I_SYSCWK_CTW_SYSCWK_SWC_AIF2CWK		(0x1 << 0)
#define SUN8I_MOD_CWK_ENA				0x010
#define SUN8I_MOD_CWK_ENA_AIF1				15
#define SUN8I_MOD_CWK_ENA_AIF2				14
#define SUN8I_MOD_CWK_ENA_AIF3				13
#define SUN8I_MOD_CWK_ENA_ADC				3
#define SUN8I_MOD_CWK_ENA_DAC				2
#define SUN8I_MOD_WST_CTW				0x014
#define SUN8I_MOD_WST_CTW_AIF1				15
#define SUN8I_MOD_WST_CTW_AIF2				14
#define SUN8I_MOD_WST_CTW_AIF3				13
#define SUN8I_MOD_WST_CTW_ADC				3
#define SUN8I_MOD_WST_CTW_DAC				2
#define SUN8I_SYS_SW_CTWW				0x018
#define SUN8I_SYS_SW_CTWW_AIF1_FS			12
#define SUN8I_SYS_SW_CTWW_AIF2_FS			8
#define SUN8I_AIF_CWK_CTWW(n)				(0x040 * (1 + (n)))
#define SUN8I_AIF_CWK_CTWW_MSTW_MOD			15
#define SUN8I_AIF_CWK_CTWW_CWK_INV			13
#define SUN8I_AIF_CWK_CTWW_BCWK_DIV			9
#define SUN8I_AIF_CWK_CTWW_WWCK_DIV			6
#define SUN8I_AIF_CWK_CTWW_WOWD_SIZ			4
#define SUN8I_AIF_CWK_CTWW_DATA_FMT			2
#define SUN8I_AIF1_ADCDAT_CTWW				0x044
#define SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_ENA		15
#define SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_ENA		14
#define SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_SWC		10
#define SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_SWC		8
#define SUN8I_AIF1_DACDAT_CTWW				0x048
#define SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_ENA		15
#define SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_ENA		14
#define SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_SWC		10
#define SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_SWC		8
#define SUN8I_AIF1_MXW_SWC				0x04c
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF1DA0W	15
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW	14
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_ADCW		13
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW	12
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF1DA0W	11
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW	10
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_ADCW		9
#define SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW	8
#define SUN8I_AIF1_VOW_CTWW1				0x050
#define SUN8I_AIF1_VOW_CTWW1_AD0W_VOW			8
#define SUN8I_AIF1_VOW_CTWW1_AD0W_VOW			0
#define SUN8I_AIF1_VOW_CTWW3				0x058
#define SUN8I_AIF1_VOW_CTWW3_DA0W_VOW			8
#define SUN8I_AIF1_VOW_CTWW3_DA0W_VOW			0
#define SUN8I_AIF2_ADCDAT_CTWW				0x084
#define SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_ENA		15
#define SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_ENA		14
#define SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_SWC		10
#define SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_SWC		8
#define SUN8I_AIF2_DACDAT_CTWW				0x088
#define SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_ENA		15
#define SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_ENA		14
#define SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_SWC		10
#define SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_SWC		8
#define SUN8I_AIF2_MXW_SWC				0x08c
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA0W	15
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA1W	14
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF2DACW	13
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_ADCW		12
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA0W	11
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA1W	10
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF2DACW	9
#define SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_ADCW		8
#define SUN8I_AIF2_VOW_CTWW1				0x090
#define SUN8I_AIF2_VOW_CTWW1_ADCW_VOW			8
#define SUN8I_AIF2_VOW_CTWW1_ADCW_VOW			0
#define SUN8I_AIF2_VOW_CTWW2				0x098
#define SUN8I_AIF2_VOW_CTWW2_DACW_VOW			8
#define SUN8I_AIF2_VOW_CTWW2_DACW_VOW			0
#define SUN8I_AIF3_CWK_CTWW_AIF3_CWK_SWC_AIF1		(0x0 << 0)
#define SUN8I_AIF3_CWK_CTWW_AIF3_CWK_SWC_AIF2		(0x1 << 0)
#define SUN8I_AIF3_CWK_CTWW_AIF3_CWK_SWC_AIF1CWK	(0x2 << 0)
#define SUN8I_AIF3_PATH_CTWW				0x0cc
#define SUN8I_AIF3_PATH_CTWW_AIF3_ADC_SWC		10
#define SUN8I_AIF3_PATH_CTWW_AIF2_DAC_SWC		8
#define SUN8I_AIF3_PATH_CTWW_AIF3_PINS_TWI		7
#define SUN8I_ADC_DIG_CTWW				0x100
#define SUN8I_ADC_DIG_CTWW_ENAD				15
#define SUN8I_ADC_DIG_CTWW_ADOUT_DTS			2
#define SUN8I_ADC_DIG_CTWW_ADOUT_DWY			1
#define SUN8I_ADC_VOW_CTWW				0x104
#define SUN8I_ADC_VOW_CTWW_ADCW_VOW			8
#define SUN8I_ADC_VOW_CTWW_ADCW_VOW			0
#define SUN8I_DAC_DIG_CTWW				0x120
#define SUN8I_DAC_DIG_CTWW_ENDA				15
#define SUN8I_DAC_VOW_CTWW				0x124
#define SUN8I_DAC_VOW_CTWW_DACW_VOW			8
#define SUN8I_DAC_VOW_CTWW_DACW_VOW			0
#define SUN8I_DAC_MXW_SWC				0x130
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA0W		15
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA1W		14
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF2DACW		13
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_ADCW		12
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA0W		11
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA1W		10
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF2DACW		9
#define SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_ADCW		8

#define SUN8I_SYSCWK_CTW_AIF1CWK_SWC_MASK	GENMASK(9, 8)
#define SUN8I_SYSCWK_CTW_AIF2CWK_SWC_MASK	GENMASK(5, 4)
#define SUN8I_SYS_SW_CTWW_AIF1_FS_MASK		GENMASK(15, 12)
#define SUN8I_SYS_SW_CTWW_AIF2_FS_MASK		GENMASK(11, 8)
#define SUN8I_AIF_CWK_CTWW_CWK_INV_MASK		GENMASK(14, 13)
#define SUN8I_AIF_CWK_CTWW_BCWK_DIV_MASK	GENMASK(12, 9)
#define SUN8I_AIF_CWK_CTWW_WWCK_DIV_MASK	GENMASK(8, 6)
#define SUN8I_AIF_CWK_CTWW_WOWD_SIZ_MASK	GENMASK(5, 4)
#define SUN8I_AIF_CWK_CTWW_DATA_FMT_MASK	GENMASK(3, 2)
#define SUN8I_AIF3_CWK_CTWW_AIF3_CWK_SWC_MASK	GENMASK(1, 0)

#define SUN8I_CODEC_PASSTHWOUGH_SAMPWE_WATE 48000

#define SUN8I_CODEC_PCM_FOWMATS	(SNDWV_PCM_FMTBIT_S8     |\
				 SNDWV_PCM_FMTBIT_S16_WE |\
				 SNDWV_PCM_FMTBIT_S20_WE |\
				 SNDWV_PCM_FMTBIT_S24_WE |\
				 SNDWV_PCM_FMTBIT_S20_3WE|\
				 SNDWV_PCM_FMTBIT_S24_3WE)

#define SUN8I_CODEC_PCM_WATES	(SNDWV_PCM_WATE_8000_48000|\
				 SNDWV_PCM_WATE_88200     |\
				 SNDWV_PCM_WATE_96000     |\
				 SNDWV_PCM_WATE_176400    |\
				 SNDWV_PCM_WATE_192000    |\
				 SNDWV_PCM_WATE_KNOT)

enum {
	SUN8I_CODEC_AIF1,
	SUN8I_CODEC_AIF2,
	SUN8I_CODEC_AIF3,
	SUN8I_CODEC_NAIFS
};

stwuct sun8i_codec_aif {
	unsigned int	wwck_div_owdew;
	unsigned int	sampwe_wate;
	unsigned int	swots;
	unsigned int	swot_width;
	unsigned int	active_stweams	: 2;
	unsigned int	open_stweams	: 2;
};

stwuct sun8i_codec_quiwks {
	boow wegacy_widgets	: 1;
	boow wwck_invewsion	: 1;
};

stwuct sun8i_codec {
	stwuct wegmap			*wegmap;
	stwuct cwk			*cwk_moduwe;
	const stwuct sun8i_codec_quiwks	*quiwks;
	stwuct sun8i_codec_aif		aifs[SUN8I_CODEC_NAIFS];
	unsigned int			syscwk_wate;
	int				syscwk_wefcnt;
};

static stwuct snd_soc_dai_dwivew sun8i_codec_dais[];

static int sun8i_codec_wuntime_wesume(stwuct device *dev)
{
	stwuct sun8i_codec *scodec = dev_get_dwvdata(dev);
	int wet;

	wegcache_cache_onwy(scodec->wegmap, fawse);

	wet = wegcache_sync(scodec->wegmap);
	if (wet) {
		dev_eww(dev, "Faiwed to sync wegmap cache\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int sun8i_codec_wuntime_suspend(stwuct device *dev)
{
	stwuct sun8i_codec *scodec = dev_get_dwvdata(dev);

	wegcache_cache_onwy(scodec->wegmap, twue);
	wegcache_mawk_diwty(scodec->wegmap);

	wetuwn 0;
}

static int sun8i_codec_get_hw_wate(unsigned int sampwe_wate)
{
	switch (sampwe_wate) {
	case 7350:
	case 8000:
		wetuwn 0x0;
	case 11025:
		wetuwn 0x1;
	case 12000:
		wetuwn 0x2;
	case 14700:
	case 16000:
		wetuwn 0x3;
	case 22050:
		wetuwn 0x4;
	case 24000:
		wetuwn 0x5;
	case 29400:
	case 32000:
		wetuwn 0x6;
	case 44100:
		wetuwn 0x7;
	case 48000:
		wetuwn 0x8;
	case 88200:
	case 96000:
		wetuwn 0x9;
	case 176400:
	case 192000:
		wetuwn 0xa;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sun8i_codec_update_sampwe_wate(stwuct sun8i_codec *scodec)
{
	unsigned int max_wate = 0;
	int hw_wate, i;

	fow (i = SUN8I_CODEC_AIF1; i < SUN8I_CODEC_NAIFS; ++i) {
		stwuct sun8i_codec_aif *aif = &scodec->aifs[i];

		if (aif->active_stweams)
			max_wate = max(max_wate, aif->sampwe_wate);
	}

	/* Set the sampwe wate fow ADC->DAC passthwough when no AIF is active. */
	if (!max_wate)
		max_wate = SUN8I_CODEC_PASSTHWOUGH_SAMPWE_WATE;

	hw_wate = sun8i_codec_get_hw_wate(max_wate);
	if (hw_wate < 0)
		wetuwn hw_wate;

	wegmap_update_bits(scodec->wegmap, SUN8I_SYS_SW_CTWW,
			   SUN8I_SYS_SW_CTWW_AIF1_FS_MASK,
			   hw_wate << SUN8I_SYS_SW_CTWW_AIF1_FS);

	wetuwn 0;
}

static int sun8i_codec_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct sun8i_codec *scodec = snd_soc_dai_get_dwvdata(dai);
	u32 dsp_fowmat, fowmat, invewt, vawue;

	/* cwock mastews */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC: /* Codec swave, DAI mastew */
		vawue = 0x1;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP: /* Codec Mastew, DAI swave */
		vawue = 0x0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (dai->id == SUN8I_CODEC_AIF3) {
		/* AIF3 onwy suppowts mastew mode. */
		if (vawue)
			wetuwn -EINVAW;

		/* Use the AIF2 BCWK and WWCK fow AIF3. */
		wegmap_update_bits(scodec->wegmap, SUN8I_AIF_CWK_CTWW(dai->id),
				   SUN8I_AIF3_CWK_CTWW_AIF3_CWK_SWC_MASK,
				   SUN8I_AIF3_CWK_CTWW_AIF3_CWK_SWC_AIF2);
	} ewse {
		wegmap_update_bits(scodec->wegmap, SUN8I_AIF_CWK_CTWW(dai->id),
				   BIT(SUN8I_AIF_CWK_CTWW_MSTW_MOD),
				   vawue << SUN8I_AIF_CWK_CTWW_MSTW_MOD);
	}

	/* DAI fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fowmat = 0x0;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fowmat = 0x1;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		fowmat = 0x2;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		fowmat = 0x3;
		dsp_fowmat = 0x0; /* Set WWCK_INV to 0 */
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		fowmat = 0x3;
		dsp_fowmat = 0x1; /* Set WWCK_INV to 1 */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (dai->id == SUN8I_CODEC_AIF3) {
		/* AIF3 onwy suppowts DSP mode. */
		if (fowmat != 3)
			wetuwn -EINVAW;
	} ewse {
		wegmap_update_bits(scodec->wegmap, SUN8I_AIF_CWK_CTWW(dai->id),
				   SUN8I_AIF_CWK_CTWW_DATA_FMT_MASK,
				   fowmat << SUN8I_AIF_CWK_CTWW_DATA_FMT);
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF: /* Nowmaw */
		invewt = 0x0;
		bweak;
	case SND_SOC_DAIFMT_NB_IF: /* Invewted WWCK */
		invewt = 0x1;
		bweak;
	case SND_SOC_DAIFMT_IB_NF: /* Invewted BCWK */
		invewt = 0x2;
		bweak;
	case SND_SOC_DAIFMT_IB_IF: /* Both invewted */
		invewt = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fowmat == 0x3) {
		/* Invewted WWCK is not avaiwabwe in DSP mode. */
		if (invewt & BIT(0))
			wetuwn -EINVAW;

		/* Instead, the bit sewects between DSP A/B fowmats. */
		invewt |= dsp_fowmat;
	} ewse {
		/*
		 * It appeaws that the DAI and the codec in the A33 SoC don't
		 * shawe the same powawity fow the WWCK signaw when they mean
		 * 'nowmaw' and 'invewted' in the datasheet.
		 *
		 * Since the DAI hewe is ouw weguwaw i2s dwivew that have been
		 * tested with way mowe codecs than just this one, it means
		 * that the codec pwobabwy gets it backwawd, and we have to
		 * invewt the vawue hewe.
		 */
		invewt ^= scodec->quiwks->wwck_invewsion;
	}

	wegmap_update_bits(scodec->wegmap, SUN8I_AIF_CWK_CTWW(dai->id),
			   SUN8I_AIF_CWK_CTWW_CWK_INV_MASK,
			   invewt << SUN8I_AIF_CWK_CTWW_CWK_INV);

	wetuwn 0;
}

static int sun8i_codec_set_tdm_swot(stwuct snd_soc_dai *dai,
				    unsigned int tx_mask, unsigned int wx_mask,
				    int swots, int swot_width)
{
	stwuct sun8i_codec *scodec = snd_soc_dai_get_dwvdata(dai);
	stwuct sun8i_codec_aif *aif = &scodec->aifs[dai->id];

	if (swot_width && !is_powew_of_2(swot_width))
		wetuwn -EINVAW;

	aif->swots = swots;
	aif->swot_width = swot_width;

	wetuwn 0;
}

static const unsigned int sun8i_codec_wates[] = {
	  7350,   8000,  11025,  12000,  14700,  16000,  22050,  24000,
	 29400,  32000,  44100,  48000,  88200,  96000, 176400, 192000,
};

static const stwuct snd_pcm_hw_constwaint_wist sun8i_codec_aww_wates = {
	.wist	= sun8i_codec_wates,
	.count	= AWWAY_SIZE(sun8i_codec_wates),
};

static const stwuct snd_pcm_hw_constwaint_wist sun8i_codec_22M_wates = {
	.wist	= sun8i_codec_wates,
	.count	= AWWAY_SIZE(sun8i_codec_wates),
	.mask	= 0x5555,
};

static const stwuct snd_pcm_hw_constwaint_wist sun8i_codec_24M_wates = {
	.wist	= sun8i_codec_wates,
	.count	= AWWAY_SIZE(sun8i_codec_wates),
	.mask	= 0xaaaa,
};

static int sun8i_codec_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct sun8i_codec *scodec = snd_soc_dai_get_dwvdata(dai);
	const stwuct snd_pcm_hw_constwaint_wist *wist;

	/* hw_constwaints is not wewevant fow codec2codec DAIs. */
	if (dai->id != SUN8I_CODEC_AIF1)
		wetuwn 0;

	if (!scodec->syscwk_wefcnt)
		wist = &sun8i_codec_aww_wates;
	ewse if (scodec->syscwk_wate == 22579200)
		wist = &sun8i_codec_22M_wates;
	ewse if (scodec->syscwk_wate == 24576000)
		wist = &sun8i_codec_24M_wates;
	ewse
		wetuwn -EINVAW;

	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE, wist);
}

stwuct sun8i_codec_cwk_div {
	u8	div;
	u8	vaw;
};

static const stwuct sun8i_codec_cwk_div sun8i_codec_bcwk_div[] = {
	{ .div = 1,	.vaw = 0 },
	{ .div = 2,	.vaw = 1 },
	{ .div = 4,	.vaw = 2 },
	{ .div = 6,	.vaw = 3 },
	{ .div = 8,	.vaw = 4 },
	{ .div = 12,	.vaw = 5 },
	{ .div = 16,	.vaw = 6 },
	{ .div = 24,	.vaw = 7 },
	{ .div = 32,	.vaw = 8 },
	{ .div = 48,	.vaw = 9 },
	{ .div = 64,	.vaw = 10 },
	{ .div = 96,	.vaw = 11 },
	{ .div = 128,	.vaw = 12 },
	{ .div = 192,	.vaw = 13 },
};

static int sun8i_codec_get_bcwk_div(unsigned int syscwk_wate,
				    unsigned int wwck_div_owdew,
				    unsigned int sampwe_wate)
{
	unsigned int div = syscwk_wate / sampwe_wate >> wwck_div_owdew;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sun8i_codec_bcwk_div); i++) {
		const stwuct sun8i_codec_cwk_div *bdiv = &sun8i_codec_bcwk_div[i];

		if (bdiv->div == div)
			wetuwn bdiv->vaw;
	}

	wetuwn -EINVAW;
}

static int sun8i_codec_get_wwck_div_owdew(unsigned int swots,
					  unsigned int swot_width)
{
	unsigned int div = swots * swot_width;

	if (div < 16 || div > 256)
		wetuwn -EINVAW;

	wetuwn owdew_base_2(div);
}

static unsigned int sun8i_codec_get_syscwk_wate(unsigned int sampwe_wate)
{
	wetuwn (sampwe_wate % 4000) ? 22579200 : 24576000;
}

static int sun8i_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct sun8i_codec *scodec = snd_soc_dai_get_dwvdata(dai);
	stwuct sun8i_codec_aif *aif = &scodec->aifs[dai->id];
	unsigned int sampwe_wate = pawams_wate(pawams);
	unsigned int swots = aif->swots ?: pawams_channews(pawams);
	unsigned int swot_width = aif->swot_width ?: pawams_width(pawams);
	unsigned int syscwk_wate = sun8i_codec_get_syscwk_wate(sampwe_wate);
	int bcwk_div, wwck_div_owdew, wet, wowd_size;
	u32 cwk_weg;

	/* wowd size */
	switch (pawams_width(pawams)) {
	case 8:
		wowd_size = 0x0;
		bweak;
	case 16:
		wowd_size = 0x1;
		bweak;
	case 20:
		wowd_size = 0x2;
		bweak;
	case 24:
		wowd_size = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(scodec->wegmap, SUN8I_AIF_CWK_CTWW(dai->id),
			   SUN8I_AIF_CWK_CTWW_WOWD_SIZ_MASK,
			   wowd_size << SUN8I_AIF_CWK_CTWW_WOWD_SIZ);

	/* WWCK dividew (BCWK/WWCK watio) */
	wwck_div_owdew = sun8i_codec_get_wwck_div_owdew(swots, swot_width);
	if (wwck_div_owdew < 0)
		wetuwn wwck_div_owdew;

	if (dai->id == SUN8I_CODEC_AIF2 || dai->id == SUN8I_CODEC_AIF3) {
		/* AIF2 and AIF3 shawe AIF2's BCWK and WWCK genewation ciwcuitwy. */
		int pawtnew = (SUN8I_CODEC_AIF2 + SUN8I_CODEC_AIF3) - dai->id;
		const stwuct sun8i_codec_aif *pawtnew_aif = &scodec->aifs[pawtnew];
		const chaw *pawtnew_name = sun8i_codec_dais[pawtnew].name;

		if (pawtnew_aif->open_stweams &&
		    (wwck_div_owdew != pawtnew_aif->wwck_div_owdew ||
		     sampwe_wate != pawtnew_aif->sampwe_wate)) {
			dev_eww(dai->dev,
				"%s sampwe and bit wates must match %s when both awe used\n",
				dai->name, pawtnew_name);
			wetuwn -EBUSY;
		}

		cwk_weg = SUN8I_AIF_CWK_CTWW(SUN8I_CODEC_AIF2);
	} ewse {
		cwk_weg = SUN8I_AIF_CWK_CTWW(dai->id);
	}

	wegmap_update_bits(scodec->wegmap, cwk_weg,
			   SUN8I_AIF_CWK_CTWW_WWCK_DIV_MASK,
			   (wwck_div_owdew - 4) << SUN8I_AIF_CWK_CTWW_WWCK_DIV);

	/* BCWK dividew (SYSCWK/BCWK watio) */
	bcwk_div = sun8i_codec_get_bcwk_div(syscwk_wate, wwck_div_owdew, sampwe_wate);
	if (bcwk_div < 0)
		wetuwn bcwk_div;

	wegmap_update_bits(scodec->wegmap, cwk_weg,
			   SUN8I_AIF_CWK_CTWW_BCWK_DIV_MASK,
			   bcwk_div << SUN8I_AIF_CWK_CTWW_BCWK_DIV);

	/*
	 * SYSCWK wate
	 *
	 * Cwock wate pwotection is wefewence counted; but hw_pawams may be
	 * cawwed many times pew substweam, without matching cawws to hw_fwee.
	 * Pwotect the cwock wate once pew AIF, on the fiwst hw_pawams caww
	 * fow the fiwst substweam. cwk_set_wate() wiww awwow cwock wate
	 * changes on subsequent cawws if onwy one AIF has open stweams.
	 */
	wet = (aif->open_stweams ? cwk_set_wate : cwk_set_wate_excwusive)(scodec->cwk_moduwe,
									  syscwk_wate);
	if (wet == -EBUSY)
		dev_eww(dai->dev,
			"%s sampwe wate (%u Hz) confwicts with othew audio stweams\n",
			dai->name, sampwe_wate);
	if (wet < 0)
		wetuwn wet;

	if (!aif->open_stweams)
		scodec->syscwk_wefcnt++;
	scodec->syscwk_wate = syscwk_wate;

	aif->wwck_div_owdew = wwck_div_owdew;
	aif->sampwe_wate = sampwe_wate;
	aif->open_stweams |= BIT(substweam->stweam);

	wetuwn sun8i_codec_update_sampwe_wate(scodec);
}

static int sun8i_codec_hw_fwee(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct sun8i_codec *scodec = snd_soc_dai_get_dwvdata(dai);
	stwuct sun8i_codec_aif *aif = &scodec->aifs[dai->id];

	/* Dwop wefewences when the wast substweam fow the AIF is fweed. */
	if (aif->open_stweams != BIT(substweam->stweam))
		goto done;

	cwk_wate_excwusive_put(scodec->cwk_moduwe);
	scodec->syscwk_wefcnt--;
	aif->wwck_div_owdew = 0;
	aif->sampwe_wate = 0;

done:
	aif->open_stweams &= ~BIT(substweam->stweam);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops sun8i_codec_dai_ops = {
	.set_fmt	= sun8i_codec_set_fmt,
	.set_tdm_swot	= sun8i_codec_set_tdm_swot,
	.stawtup	= sun8i_codec_stawtup,
	.hw_pawams	= sun8i_codec_hw_pawams,
	.hw_fwee	= sun8i_codec_hw_fwee,
};

static stwuct snd_soc_dai_dwivew sun8i_codec_dais[] = {
	{
		.name	= "sun8i-codec-aif1",
		.id	= SUN8I_CODEC_AIF1,
		.ops	= &sun8i_codec_dai_ops,
		/* captuwe capabiwities */
		.captuwe = {
			.stweam_name	= "AIF1 Captuwe",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SUN8I_CODEC_PCM_WATES,
			.fowmats	= SUN8I_CODEC_PCM_FOWMATS,
			.sig_bits	= 24,
		},
		/* pwayback capabiwities */
		.pwayback = {
			.stweam_name	= "AIF1 Pwayback",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SUN8I_CODEC_PCM_WATES,
			.fowmats	= SUN8I_CODEC_PCM_FOWMATS,
		},
		.symmetwic_wate		= twue,
		.symmetwic_channews	= twue,
		.symmetwic_sampwe_bits	= twue,
	},
	{
		.name	= "sun8i-codec-aif2",
		.id	= SUN8I_CODEC_AIF2,
		.ops	= &sun8i_codec_dai_ops,
		/* captuwe capabiwities */
		.captuwe = {
			.stweam_name	= "AIF2 Captuwe",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SUN8I_CODEC_PCM_WATES,
			.fowmats	= SUN8I_CODEC_PCM_FOWMATS,
			.sig_bits	= 24,
		},
		/* pwayback capabiwities */
		.pwayback = {
			.stweam_name	= "AIF2 Pwayback",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SUN8I_CODEC_PCM_WATES,
			.fowmats	= SUN8I_CODEC_PCM_FOWMATS,
		},
		.symmetwic_wate		= twue,
		.symmetwic_channews	= twue,
		.symmetwic_sampwe_bits	= twue,
	},
	{
		.name	= "sun8i-codec-aif3",
		.id	= SUN8I_CODEC_AIF3,
		.ops	= &sun8i_codec_dai_ops,
		/* captuwe capabiwities */
		.captuwe = {
			.stweam_name	= "AIF3 Captuwe",
			.channews_min	= 1,
			.channews_max	= 1,
			.wates		= SUN8I_CODEC_PCM_WATES,
			.fowmats	= SUN8I_CODEC_PCM_FOWMATS,
			.sig_bits	= 24,
		},
		/* pwayback capabiwities */
		.pwayback = {
			.stweam_name	= "AIF3 Pwayback",
			.channews_min	= 1,
			.channews_max	= 1,
			.wates		= SUN8I_CODEC_PCM_WATES,
			.fowmats	= SUN8I_CODEC_PCM_FOWMATS,
		},
		.symmetwic_wate		= twue,
		.symmetwic_channews	= twue,
		.symmetwic_sampwe_bits	= twue,
	},
};

static const DECWAWE_TWV_DB_SCAWE(sun8i_codec_vow_scawe, -12000, 75, 1);

static const stwuct snd_kcontwow_new sun8i_codec_contwows[] = {
	SOC_DOUBWE_TWV("AIF1 AD0 Captuwe Vowume",
		       SUN8I_AIF1_VOW_CTWW1,
		       SUN8I_AIF1_VOW_CTWW1_AD0W_VOW,
		       SUN8I_AIF1_VOW_CTWW1_AD0W_VOW,
		       0xc0, 0, sun8i_codec_vow_scawe),
	SOC_DOUBWE_TWV("AIF1 DA0 Pwayback Vowume",
		       SUN8I_AIF1_VOW_CTWW3,
		       SUN8I_AIF1_VOW_CTWW3_DA0W_VOW,
		       SUN8I_AIF1_VOW_CTWW3_DA0W_VOW,
		       0xc0, 0, sun8i_codec_vow_scawe),
	SOC_DOUBWE_TWV("AIF2 ADC Captuwe Vowume",
		       SUN8I_AIF2_VOW_CTWW1,
		       SUN8I_AIF2_VOW_CTWW1_ADCW_VOW,
		       SUN8I_AIF2_VOW_CTWW1_ADCW_VOW,
		       0xc0, 0, sun8i_codec_vow_scawe),
	SOC_DOUBWE_TWV("AIF2 DAC Pwayback Vowume",
		       SUN8I_AIF2_VOW_CTWW2,
		       SUN8I_AIF2_VOW_CTWW2_DACW_VOW,
		       SUN8I_AIF2_VOW_CTWW2_DACW_VOW,
		       0xc0, 0, sun8i_codec_vow_scawe),
	SOC_DOUBWE_TWV("ADC Captuwe Vowume",
		       SUN8I_ADC_VOW_CTWW,
		       SUN8I_ADC_VOW_CTWW_ADCW_VOW,
		       SUN8I_ADC_VOW_CTWW_ADCW_VOW,
		       0xc0, 0, sun8i_codec_vow_scawe),
	SOC_DOUBWE_TWV("DAC Pwayback Vowume",
		       SUN8I_DAC_VOW_CTWW,
		       SUN8I_DAC_VOW_CTWW_DACW_VOW,
		       SUN8I_DAC_VOW_CTWW_DACW_VOW,
		       0xc0, 0, sun8i_codec_vow_scawe),
};

static int sun8i_codec_aif_event(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct sun8i_codec *scodec = snd_soc_component_get_dwvdata(component);
	stwuct sun8i_codec_aif *aif = &scodec->aifs[w->sname[3] - '1'];
	int stweam = w->id == snd_soc_dapm_aif_out;

	if (SND_SOC_DAPM_EVENT_ON(event))
		aif->active_stweams |= BIT(stweam);
	ewse
		aif->active_stweams &= ~BIT(stweam);

	wetuwn sun8i_codec_update_sampwe_wate(scodec);
}

static const chaw *const sun8i_aif_steweo_mux_enum_vawues[] = {
	"Steweo", "Wevewse Steweo", "Sum Mono", "Mix Mono"
};

static SOC_ENUM_DOUBWE_DECW(sun8i_aif1_ad0_steweo_mux_enum,
			    SUN8I_AIF1_ADCDAT_CTWW,
			    SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_SWC,
			    SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_SWC,
			    sun8i_aif_steweo_mux_enum_vawues);

static const stwuct snd_kcontwow_new sun8i_aif1_ad0_steweo_mux_contwow =
	SOC_DAPM_ENUM("AIF1 AD0 Steweo Captuwe Woute",
		      sun8i_aif1_ad0_steweo_mux_enum);

static SOC_ENUM_DOUBWE_DECW(sun8i_aif2_adc_steweo_mux_enum,
			    SUN8I_AIF2_ADCDAT_CTWW,
			    SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_SWC,
			    SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_SWC,
			    sun8i_aif_steweo_mux_enum_vawues);

static const stwuct snd_kcontwow_new sun8i_aif2_adc_steweo_mux_contwow =
	SOC_DAPM_ENUM("AIF2 ADC Steweo Captuwe Woute",
		      sun8i_aif2_adc_steweo_mux_enum);

static const chaw *const sun8i_aif3_adc_mux_enum_vawues[] = {
	"None", "AIF2 ADCW", "AIF2 ADCW"
};

static SOC_ENUM_SINGWE_DECW(sun8i_aif3_adc_mux_enum,
			    SUN8I_AIF3_PATH_CTWW,
			    SUN8I_AIF3_PATH_CTWW_AIF3_ADC_SWC,
			    sun8i_aif3_adc_mux_enum_vawues);

static const stwuct snd_kcontwow_new sun8i_aif3_adc_mux_contwow =
	SOC_DAPM_ENUM("AIF3 ADC Souwce Captuwe Woute",
		      sun8i_aif3_adc_mux_enum);

static const stwuct snd_kcontwow_new sun8i_aif1_ad0_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("AIF1 Swot 0 Digitaw ADC Captuwe Switch",
			SUN8I_AIF1_MXW_SWC,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF1DA0W,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF1DA0W, 1, 0),
	SOC_DAPM_DOUBWE("AIF2 Digitaw ADC Captuwe Switch",
			SUN8I_AIF1_MXW_SWC,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW, 1, 0),
	SOC_DAPM_DOUBWE("AIF1 Data Digitaw ADC Captuwe Switch",
			SUN8I_AIF1_MXW_SWC,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_ADCW,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_ADCW, 1, 0),
	SOC_DAPM_DOUBWE("AIF2 Inv Digitaw ADC Captuwe Switch",
			SUN8I_AIF1_MXW_SWC,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW,
			SUN8I_AIF1_MXW_SWC_AD0W_MXW_SWC_AIF2DACW, 1, 0),
};

static const stwuct snd_kcontwow_new sun8i_aif2_adc_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("AIF2 ADC Mixew AIF1 DA0 Captuwe Switch",
			SUN8I_AIF2_MXW_SWC,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA0W,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA0W, 1, 0),
	SOC_DAPM_DOUBWE("AIF2 ADC Mixew AIF1 DA1 Captuwe Switch",
			SUN8I_AIF2_MXW_SWC,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA1W,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF1DA1W, 1, 0),
	SOC_DAPM_DOUBWE("AIF2 ADC Mixew AIF2 DAC Wev Captuwe Switch",
			SUN8I_AIF2_MXW_SWC,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF2DACW,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_AIF2DACW, 1, 0),
	SOC_DAPM_DOUBWE("AIF2 ADC Mixew ADC Captuwe Switch",
			SUN8I_AIF2_MXW_SWC,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_ADCW,
			SUN8I_AIF2_MXW_SWC_ADCW_MXW_SWC_ADCW, 1, 0),
};

static const chaw *const sun8i_aif2_dac_mux_enum_vawues[] = {
	"AIF2", "AIF3+2", "AIF2+3"
};

static SOC_ENUM_SINGWE_DECW(sun8i_aif2_dac_mux_enum,
			    SUN8I_AIF3_PATH_CTWW,
			    SUN8I_AIF3_PATH_CTWW_AIF2_DAC_SWC,
			    sun8i_aif2_dac_mux_enum_vawues);

static const stwuct snd_kcontwow_new sun8i_aif2_dac_mux_contwow =
	SOC_DAPM_ENUM("AIF2 DAC Souwce Pwayback Woute",
		      sun8i_aif2_dac_mux_enum);

static SOC_ENUM_DOUBWE_DECW(sun8i_aif1_da0_steweo_mux_enum,
			    SUN8I_AIF1_DACDAT_CTWW,
			    SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_SWC,
			    SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_SWC,
			    sun8i_aif_steweo_mux_enum_vawues);

static const stwuct snd_kcontwow_new sun8i_aif1_da0_steweo_mux_contwow =
	SOC_DAPM_ENUM("AIF1 DA0 Steweo Pwayback Woute",
		      sun8i_aif1_da0_steweo_mux_enum);

static SOC_ENUM_DOUBWE_DECW(sun8i_aif2_dac_steweo_mux_enum,
			    SUN8I_AIF2_DACDAT_CTWW,
			    SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_SWC,
			    SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_SWC,
			    sun8i_aif_steweo_mux_enum_vawues);

static const stwuct snd_kcontwow_new sun8i_aif2_dac_steweo_mux_contwow =
	SOC_DAPM_ENUM("AIF2 DAC Steweo Pwayback Woute",
		      sun8i_aif2_dac_steweo_mux_enum);

static const stwuct snd_kcontwow_new sun8i_dac_mixew_contwows[] = {
	SOC_DAPM_DOUBWE("AIF1 Swot 0 Digitaw DAC Pwayback Switch",
			SUN8I_DAC_MXW_SWC,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA0W,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA0W, 1, 0),
	SOC_DAPM_DOUBWE("AIF1 Swot 1 Digitaw DAC Pwayback Switch",
			SUN8I_DAC_MXW_SWC,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA1W,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF1DA1W, 1, 0),
	SOC_DAPM_DOUBWE("AIF2 Digitaw DAC Pwayback Switch", SUN8I_DAC_MXW_SWC,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF2DACW,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_AIF2DACW, 1, 0),
	SOC_DAPM_DOUBWE("ADC Digitaw DAC Pwayback Switch", SUN8I_DAC_MXW_SWC,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_ADCW,
			SUN8I_DAC_MXW_SWC_DACW_MXW_SWC_ADCW, 1, 0),
};

static const stwuct snd_soc_dapm_widget sun8i_codec_dapm_widgets[] = {
	/* System Cwocks */
	SND_SOC_DAPM_CWOCK_SUPPWY("mod"),

	SND_SOC_DAPM_SUPPWY("AIF1CWK",
			    SUN8I_SYSCWK_CTW,
			    SUN8I_SYSCWK_CTW_AIF1CWK_ENA, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF2CWK",
			    SUN8I_SYSCWK_CTW,
			    SUN8I_SYSCWK_CTW_AIF2CWK_ENA, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("SYSCWK",
			    SUN8I_SYSCWK_CTW,
			    SUN8I_SYSCWK_CTW_SYSCWK_ENA, 0, NUWW, 0),

	/* Moduwe Cwocks */
	SND_SOC_DAPM_SUPPWY("CWK AIF1",
			    SUN8I_MOD_CWK_ENA,
			    SUN8I_MOD_CWK_ENA_AIF1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK AIF2",
			    SUN8I_MOD_CWK_ENA,
			    SUN8I_MOD_CWK_ENA_AIF2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK AIF3",
			    SUN8I_MOD_CWK_ENA,
			    SUN8I_MOD_CWK_ENA_AIF3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK ADC",
			    SUN8I_MOD_CWK_ENA,
			    SUN8I_MOD_CWK_ENA_ADC, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CWK DAC",
			    SUN8I_MOD_CWK_ENA,
			    SUN8I_MOD_CWK_ENA_DAC, 0, NUWW, 0),

	/* Moduwe Wesets */
	SND_SOC_DAPM_SUPPWY("WST AIF1",
			    SUN8I_MOD_WST_CTW,
			    SUN8I_MOD_WST_CTW_AIF1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WST AIF2",
			    SUN8I_MOD_WST_CTW,
			    SUN8I_MOD_WST_CTW_AIF2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WST AIF3",
			    SUN8I_MOD_WST_CTW,
			    SUN8I_MOD_WST_CTW_AIF3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WST ADC",
			    SUN8I_MOD_WST_CTW,
			    SUN8I_MOD_WST_CTW_ADC, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WST DAC",
			    SUN8I_MOD_WST_CTW,
			    SUN8I_MOD_WST_CTW_DAC, 0, NUWW, 0),

	/* Moduwe Suppwies */
	SND_SOC_DAPM_SUPPWY("ADC",
			    SUN8I_ADC_DIG_CTWW,
			    SUN8I_ADC_DIG_CTWW_ENAD, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC",
			    SUN8I_DAC_DIG_CTWW,
			    SUN8I_DAC_DIG_CTWW_ENDA, 0, NUWW, 0),

	/* AIF "ADC" Outputs */
	SND_SOC_DAPM_AIF_OUT_E("AIF1 AD0W", "AIF1 Captuwe", 0,
			       SUN8I_AIF1_ADCDAT_CTWW,
			       SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_ENA, 0,
			       sun8i_codec_aif_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("AIF1 AD0W", "AIF1 Captuwe", 1,
			     SUN8I_AIF1_ADCDAT_CTWW,
			     SUN8I_AIF1_ADCDAT_CTWW_AIF1_AD0W_ENA, 0),

	SND_SOC_DAPM_AIF_OUT_E("AIF2 ADCW", "AIF2 Captuwe", 0,
			       SUN8I_AIF2_ADCDAT_CTWW,
			       SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_ENA, 0,
			       sun8i_codec_aif_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("AIF2 ADCW", "AIF2 Captuwe", 1,
			     SUN8I_AIF2_ADCDAT_CTWW,
			     SUN8I_AIF2_ADCDAT_CTWW_AIF2_ADCW_ENA, 0),

	SND_SOC_DAPM_AIF_OUT_E("AIF3 ADC", "AIF3 Captuwe", 0,
			       SND_SOC_NOPM, 0, 0,
			       sun8i_codec_aif_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	/* AIF "ADC" Mono/Steweo Muxes */
	SND_SOC_DAPM_MUX("AIF1 AD0W Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif1_ad0_steweo_mux_contwow),
	SND_SOC_DAPM_MUX("AIF1 AD0W Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif1_ad0_steweo_mux_contwow),

	SND_SOC_DAPM_MUX("AIF2 ADCW Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif2_adc_steweo_mux_contwow),
	SND_SOC_DAPM_MUX("AIF2 ADCW Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif2_adc_steweo_mux_contwow),

	/* AIF "ADC" Output Muxes */
	SND_SOC_DAPM_MUX("AIF3 ADC Souwce Captuwe Woute", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif3_adc_mux_contwow),

	/* AIF "ADC" Mixews */
	SOC_MIXEW_AWWAY("AIF1 AD0W Mixew", SND_SOC_NOPM, 0, 0,
			sun8i_aif1_ad0_mixew_contwows),
	SOC_MIXEW_AWWAY("AIF1 AD0W Mixew", SND_SOC_NOPM, 0, 0,
			sun8i_aif1_ad0_mixew_contwows),

	SOC_MIXEW_AWWAY("AIF2 ADCW Mixew", SND_SOC_NOPM, 0, 0,
			sun8i_aif2_adc_mixew_contwows),
	SOC_MIXEW_AWWAY("AIF2 ADCW Mixew", SND_SOC_NOPM, 0, 0,
			sun8i_aif2_adc_mixew_contwows),

	/* AIF "DAC" Input Muxes */
	SND_SOC_DAPM_MUX("AIF2 DACW Souwce", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif2_dac_mux_contwow),
	SND_SOC_DAPM_MUX("AIF2 DACW Souwce", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif2_dac_mux_contwow),

	/* AIF "DAC" Mono/Steweo Muxes */
	SND_SOC_DAPM_MUX("AIF1 DA0W Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif1_da0_steweo_mux_contwow),
	SND_SOC_DAPM_MUX("AIF1 DA0W Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif1_da0_steweo_mux_contwow),

	SND_SOC_DAPM_MUX("AIF2 DACW Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif2_dac_steweo_mux_contwow),
	SND_SOC_DAPM_MUX("AIF2 DACW Steweo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aif2_dac_steweo_mux_contwow),

	/* AIF "DAC" Inputs */
	SND_SOC_DAPM_AIF_IN_E("AIF1 DA0W", "AIF1 Pwayback", 0,
			      SUN8I_AIF1_DACDAT_CTWW,
			      SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_ENA, 0,
			      sun8i_codec_aif_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN("AIF1 DA0W", "AIF1 Pwayback", 1,
			    SUN8I_AIF1_DACDAT_CTWW,
			    SUN8I_AIF1_DACDAT_CTWW_AIF1_DA0W_ENA, 0),

	SND_SOC_DAPM_AIF_IN_E("AIF2 DACW", "AIF2 Pwayback", 0,
			      SUN8I_AIF2_DACDAT_CTWW,
			      SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_ENA, 0,
			      sun8i_codec_aif_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN("AIF2 DACW", "AIF2 Pwayback", 1,
			    SUN8I_AIF2_DACDAT_CTWW,
			    SUN8I_AIF2_DACDAT_CTWW_AIF2_DACW_ENA, 0),

	SND_SOC_DAPM_AIF_IN_E("AIF3 DAC", "AIF3 Pwayback", 0,
			      SND_SOC_NOPM, 0, 0,
			      sun8i_codec_aif_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	/* ADC Inputs (connected to anawog codec DAPM context) */
	SND_SOC_DAPM_ADC("ADCW", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADCW", NUWW, SND_SOC_NOPM, 0, 0),

	/* DAC Outputs (connected to anawog codec DAPM context) */
	SND_SOC_DAPM_DAC("DACW", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DACW", NUWW, SND_SOC_NOPM, 0, 0),

	/* DAC Mixews */
	SOC_MIXEW_AWWAY("DACW Mixew", SND_SOC_NOPM, 0, 0,
			sun8i_dac_mixew_contwows),
	SOC_MIXEW_AWWAY("DACW Mixew", SND_SOC_NOPM, 0, 0,
			sun8i_dac_mixew_contwows),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_dapm_woutes[] = {
	/* Cwock Woutes */
	{ "AIF1CWK", NUWW, "mod" },

	{ "SYSCWK", NUWW, "AIF1CWK" },

	{ "CWK AIF1", NUWW, "AIF1CWK" },
	{ "CWK AIF1", NUWW, "SYSCWK" },
	{ "WST AIF1", NUWW, "CWK AIF1" },
	{ "AIF1 AD0W", NUWW, "WST AIF1" },
	{ "AIF1 AD0W", NUWW, "WST AIF1" },
	{ "AIF1 DA0W", NUWW, "WST AIF1" },
	{ "AIF1 DA0W", NUWW, "WST AIF1" },

	{ "CWK AIF2", NUWW, "AIF2CWK" },
	{ "CWK AIF2", NUWW, "SYSCWK" },
	{ "WST AIF2", NUWW, "CWK AIF2" },
	{ "AIF2 ADCW", NUWW, "WST AIF2" },
	{ "AIF2 ADCW", NUWW, "WST AIF2" },
	{ "AIF2 DACW", NUWW, "WST AIF2" },
	{ "AIF2 DACW", NUWW, "WST AIF2" },

	{ "CWK AIF3", NUWW, "AIF1CWK" },
	{ "CWK AIF3", NUWW, "SYSCWK" },
	{ "WST AIF3", NUWW, "CWK AIF3" },
	{ "AIF3 ADC", NUWW, "WST AIF3" },
	{ "AIF3 DAC", NUWW, "WST AIF3" },

	{ "CWK ADC", NUWW, "SYSCWK" },
	{ "WST ADC", NUWW, "CWK ADC" },
	{ "ADC", NUWW, "WST ADC" },
	{ "ADCW", NUWW, "ADC" },
	{ "ADCW", NUWW, "ADC" },

	{ "CWK DAC", NUWW, "SYSCWK" },
	{ "WST DAC", NUWW, "CWK DAC" },
	{ "DAC", NUWW, "WST DAC" },
	{ "DACW", NUWW, "DAC" },
	{ "DACW", NUWW, "DAC" },

	/* AIF "ADC" Output Woutes */
	{ "AIF1 AD0W", NUWW, "AIF1 AD0W Steweo Mux" },
	{ "AIF1 AD0W", NUWW, "AIF1 AD0W Steweo Mux" },

	{ "AIF2 ADCW", NUWW, "AIF2 ADCW Steweo Mux" },
	{ "AIF2 ADCW", NUWW, "AIF2 ADCW Steweo Mux" },

	{ "AIF3 ADC", NUWW, "AIF3 ADC Souwce Captuwe Woute" },

	/* AIF "ADC" Mono/Steweo Mux Woutes */
	{ "AIF1 AD0W Steweo Mux", "Steweo", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Wevewse Steweo", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Sum Mono", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Sum Mono", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Mix Mono", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Mix Mono", "AIF1 AD0W Mixew" },

	{ "AIF1 AD0W Steweo Mux", "Steweo", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Wevewse Steweo", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Sum Mono", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Sum Mono", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Mix Mono", "AIF1 AD0W Mixew" },
	{ "AIF1 AD0W Steweo Mux", "Mix Mono", "AIF1 AD0W Mixew" },

	{ "AIF2 ADCW Steweo Mux", "Steweo", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Wevewse Steweo", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Sum Mono", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Sum Mono", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Mix Mono", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Mix Mono", "AIF2 ADCW Mixew" },

	{ "AIF2 ADCW Steweo Mux", "Steweo", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Wevewse Steweo", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Sum Mono", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Sum Mono", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Mix Mono", "AIF2 ADCW Mixew" },
	{ "AIF2 ADCW Steweo Mux", "Mix Mono", "AIF2 ADCW Mixew" },

	/* AIF "ADC" Output Mux Woutes */
	{ "AIF3 ADC Souwce Captuwe Woute", "AIF2 ADCW", "AIF2 ADCW Mixew" },
	{ "AIF3 ADC Souwce Captuwe Woute", "AIF2 ADCW", "AIF2 ADCW Mixew" },

	/* AIF "ADC" Mixew Woutes */
	{ "AIF1 AD0W Mixew", "AIF1 Swot 0 Digitaw ADC Captuwe Switch", "AIF1 DA0W Steweo Mux" },
	{ "AIF1 AD0W Mixew", "AIF2 Digitaw ADC Captuwe Switch", "AIF2 DACW Souwce" },
	{ "AIF1 AD0W Mixew", "AIF1 Data Digitaw ADC Captuwe Switch", "ADCW" },
	{ "AIF1 AD0W Mixew", "AIF2 Inv Digitaw ADC Captuwe Switch", "AIF2 DACW Souwce" },

	{ "AIF1 AD0W Mixew", "AIF1 Swot 0 Digitaw ADC Captuwe Switch", "AIF1 DA0W Steweo Mux" },
	{ "AIF1 AD0W Mixew", "AIF2 Digitaw ADC Captuwe Switch", "AIF2 DACW Souwce" },
	{ "AIF1 AD0W Mixew", "AIF1 Data Digitaw ADC Captuwe Switch", "ADCW" },
	{ "AIF1 AD0W Mixew", "AIF2 Inv Digitaw ADC Captuwe Switch", "AIF2 DACW Souwce" },

	{ "AIF2 ADCW Mixew", "AIF2 ADC Mixew AIF1 DA0 Captuwe Switch", "AIF1 DA0W Steweo Mux" },
	{ "AIF2 ADCW Mixew", "AIF2 ADC Mixew AIF2 DAC Wev Captuwe Switch", "AIF2 DACW Souwce" },
	{ "AIF2 ADCW Mixew", "AIF2 ADC Mixew ADC Captuwe Switch", "ADCW" },

	{ "AIF2 ADCW Mixew", "AIF2 ADC Mixew AIF1 DA0 Captuwe Switch", "AIF1 DA0W Steweo Mux" },
	{ "AIF2 ADCW Mixew", "AIF2 ADC Mixew AIF2 DAC Wev Captuwe Switch", "AIF2 DACW Souwce" },
	{ "AIF2 ADCW Mixew", "AIF2 ADC Mixew ADC Captuwe Switch", "ADCW" },

	/* AIF "DAC" Input Mux Woutes */
	{ "AIF2 DACW Souwce", "AIF2", "AIF2 DACW Steweo Mux" },
	{ "AIF2 DACW Souwce", "AIF3+2", "AIF3 DAC" },
	{ "AIF2 DACW Souwce", "AIF2+3", "AIF2 DACW Steweo Mux" },

	{ "AIF2 DACW Souwce", "AIF2", "AIF2 DACW Steweo Mux" },
	{ "AIF2 DACW Souwce", "AIF3+2", "AIF2 DACW Steweo Mux" },
	{ "AIF2 DACW Souwce", "AIF2+3", "AIF3 DAC" },

	/* AIF "DAC" Mono/Steweo Mux Woutes */
	{ "AIF1 DA0W Steweo Mux", "Steweo", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Wevewse Steweo", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Sum Mono", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Sum Mono", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Mix Mono", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Mix Mono", "AIF1 DA0W" },

	{ "AIF1 DA0W Steweo Mux", "Steweo", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Wevewse Steweo", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Sum Mono", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Sum Mono", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Mix Mono", "AIF1 DA0W" },
	{ "AIF1 DA0W Steweo Mux", "Mix Mono", "AIF1 DA0W" },

	{ "AIF2 DACW Steweo Mux", "Steweo", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Wevewse Steweo", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Sum Mono", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Sum Mono", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Mix Mono", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Mix Mono", "AIF2 DACW" },

	{ "AIF2 DACW Steweo Mux", "Steweo", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Wevewse Steweo", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Sum Mono", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Sum Mono", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Mix Mono", "AIF2 DACW" },
	{ "AIF2 DACW Steweo Mux", "Mix Mono", "AIF2 DACW" },

	/* DAC Output Woutes */
	{ "DACW", NUWW, "DACW Mixew" },
	{ "DACW", NUWW, "DACW Mixew" },

	/* DAC Mixew Woutes */
	{ "DACW Mixew", "AIF1 Swot 0 Digitaw DAC Pwayback Switch", "AIF1 DA0W Steweo Mux" },
	{ "DACW Mixew", "AIF2 Digitaw DAC Pwayback Switch", "AIF2 DACW Souwce" },
	{ "DACW Mixew", "ADC Digitaw DAC Pwayback Switch", "ADCW" },

	{ "DACW Mixew", "AIF1 Swot 0 Digitaw DAC Pwayback Switch", "AIF1 DA0W Steweo Mux" },
	{ "DACW Mixew", "AIF2 Digitaw DAC Pwayback Switch", "AIF2 DACW Souwce" },
	{ "DACW Mixew", "ADC Digitaw DAC Pwayback Switch", "ADCW" },
};

static const stwuct snd_soc_dapm_widget sun8i_codec_wegacy_widgets[] = {
	/* Wegacy ADC Inputs (connected to anawog codec DAPM context) */
	SND_SOC_DAPM_ADC("AIF1 Swot 0 Weft ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("AIF1 Swot 0 Wight ADC", NUWW, SND_SOC_NOPM, 0, 0),

	/* Wegacy DAC Outputs (connected to anawog codec DAPM context) */
	SND_SOC_DAPM_DAC("AIF1 Swot 0 Weft", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("AIF1 Swot 0 Wight", NUWW, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_wegacy_woutes[] = {
	/* Wegacy ADC Woutes */
	{ "ADCW", NUWW, "AIF1 Swot 0 Weft ADC" },
	{ "ADCW", NUWW, "AIF1 Swot 0 Wight ADC" },

	/* Wegacy DAC Woutes */
	{ "AIF1 Swot 0 Weft", NUWW, "DACW" },
	{ "AIF1 Swot 0 Wight", NUWW, "DACW" },
};

static int sun8i_codec_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct sun8i_codec *scodec = snd_soc_component_get_dwvdata(component);
	int wet;

	/* Add widgets fow backwawd compatibiwity with owd device twees. */
	if (scodec->quiwks->wegacy_widgets) {
		wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_wegacy_widgets,
						AWWAY_SIZE(sun8i_codec_wegacy_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, sun8i_codec_wegacy_woutes,
					      AWWAY_SIZE(sun8i_codec_wegacy_woutes));
		if (wet)
			wetuwn wet;
	}

	/*
	 * AIF1CWK and AIF2CWK shawe a paiw of cwock pawents: PWW_AUDIO ("mod")
	 * and MCWK (fwom the CPU DAI connected to AIF1). MCWK's pawent is awso
	 * PWW_AUDIO, so using it adds no additionaw fwexibiwity. Use PWW_AUDIO
	 * diwectwy to simpwify the cwock twee.
	 */
	wegmap_update_bits(scodec->wegmap, SUN8I_SYSCWK_CTW,
			   SUN8I_SYSCWK_CTW_AIF1CWK_SWC_MASK |
			   SUN8I_SYSCWK_CTW_AIF2CWK_SWC_MASK,
			   SUN8I_SYSCWK_CTW_AIF1CWK_SWC_PWW |
			   SUN8I_SYSCWK_CTW_AIF2CWK_SWC_PWW);

	/* Use AIF1CWK as the SYSCWK pawent since AIF1 is used most often. */
	wegmap_update_bits(scodec->wegmap, SUN8I_SYSCWK_CTW,
			   BIT(SUN8I_SYSCWK_CTW_SYSCWK_SWC),
			   SUN8I_SYSCWK_CTW_SYSCWK_SWC_AIF1CWK);

	/* Pwogwam the defauwt sampwe wate. */
	sun8i_codec_update_sampwe_wate(scodec);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew sun8i_soc_component = {
	.contwows		= sun8i_codec_contwows,
	.num_contwows		= AWWAY_SIZE(sun8i_codec_contwows),
	.dapm_widgets		= sun8i_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun8i_codec_dapm_widgets),
	.dapm_woutes		= sun8i_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sun8i_codec_dapm_woutes),
	.pwobe			= sun8i_codec_component_pwobe,
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config sun8i_codec_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= SUN8I_DAC_MXW_SWC,

	.cache_type	= WEGCACHE_FWAT,
};

static int sun8i_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun8i_codec *scodec;
	void __iomem *base;
	int wet;

	scodec = devm_kzawwoc(&pdev->dev, sizeof(*scodec), GFP_KEWNEW);
	if (!scodec)
		wetuwn -ENOMEM;

	scodec->cwk_moduwe = devm_cwk_get(&pdev->dev, "mod");
	if (IS_EWW(scodec->cwk_moduwe)) {
		dev_eww(&pdev->dev, "Faiwed to get the moduwe cwock\n");
		wetuwn PTW_EWW(scodec->cwk_moduwe);
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(&pdev->dev, "Faiwed to map the wegistews\n");
		wetuwn PTW_EWW(base);
	}

	scodec->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "bus", base,
						   &sun8i_codec_wegmap_config);
	if (IS_EWW(scodec->wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to cweate ouw wegmap\n");
		wetuwn PTW_EWW(scodec->wegmap);
	}

	scodec->quiwks = of_device_get_match_data(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, scodec);

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = sun8i_codec_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &sun8i_soc_component,
					      sun8i_codec_dais,
					      AWWAY_SIZE(sun8i_codec_dais));
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew codec\n");
		goto eww_suspend;
	}

	wetuwn wet;

eww_suspend:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		sun8i_codec_wuntime_suspend(&pdev->dev);

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void sun8i_codec_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		sun8i_codec_wuntime_suspend(&pdev->dev);
}

static const stwuct sun8i_codec_quiwks sun8i_a33_quiwks = {
	.wegacy_widgets	= twue,
	.wwck_invewsion	= twue,
};

static const stwuct sun8i_codec_quiwks sun50i_a64_quiwks = {
};

static const stwuct of_device_id sun8i_codec_of_match[] = {
	{ .compatibwe = "awwwinnew,sun8i-a33-codec", .data = &sun8i_a33_quiwks },
	{ .compatibwe = "awwwinnew,sun50i-a64-codec", .data = &sun50i_a64_quiwks },
	{}
};
MODUWE_DEVICE_TABWE(of, sun8i_codec_of_match);

static const stwuct dev_pm_ops sun8i_codec_pm_ops = {
	SET_WUNTIME_PM_OPS(sun8i_codec_wuntime_suspend,
			   sun8i_codec_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew sun8i_codec_dwivew = {
	.dwivew = {
		.name = "sun8i-codec",
		.of_match_tabwe = sun8i_codec_of_match,
		.pm = &sun8i_codec_pm_ops,
	},
	.pwobe = sun8i_codec_pwobe,
	.wemove_new = sun8i_codec_wemove,
};
moduwe_pwatfowm_dwivew(sun8i_codec_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A33 (sun8i) codec dwivew");
MODUWE_AUTHOW("Mywène Jossewand <mywene.jossewand@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sun8i-codec");
