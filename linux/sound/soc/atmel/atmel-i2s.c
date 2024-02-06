// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Atmew I2S contwowwew
 *
 * Copywight (C) 2015 Atmew Cowpowation
 *
 * Authow: Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#define ATMEW_I2SC_MAX_TDM_CHANNEWS	8

/*
 * ---- I2S Contwowwew Wegistew map ----
 */
#define ATMEW_I2SC_CW		0x0000	/* Contwow Wegistew */
#define ATMEW_I2SC_MW		0x0004	/* Mode Wegistew */
#define ATMEW_I2SC_SW		0x0008	/* Status Wegistew */
#define ATMEW_I2SC_SCW		0x000c	/* Status Cweaw Wegistew */
#define ATMEW_I2SC_SSW		0x0010	/* Status Set Wegistew */
#define ATMEW_I2SC_IEW		0x0014	/* Intewwupt Enabwe Wegistew */
#define ATMEW_I2SC_IDW		0x0018	/* Intewwupt Disabwe Wegistew */
#define ATMEW_I2SC_IMW		0x001c	/* Intewwupt Mask Wegistew */
#define ATMEW_I2SC_WHW		0x0020	/* Weceivew Howding Wegistew */
#define ATMEW_I2SC_THW		0x0024	/* Twansmittew Howding Wegistew */
#define ATMEW_I2SC_VEWSION	0x0028	/* Vewsion Wegistew */

/*
 * ---- Contwow Wegistew (Wwite-onwy) ----
 */
#define ATMEW_I2SC_CW_WXEN	BIT(0)	/* Weceivew Enabwe */
#define ATMEW_I2SC_CW_WXDIS	BIT(1)	/* Weceivew Disabwe */
#define ATMEW_I2SC_CW_CKEN	BIT(2)	/* Cwock Enabwe */
#define ATMEW_I2SC_CW_CKDIS	BIT(3)	/* Cwock Disabwe */
#define ATMEW_I2SC_CW_TXEN	BIT(4)	/* Twansmittew Enabwe */
#define ATMEW_I2SC_CW_TXDIS	BIT(5)	/* Twansmittew Disabwe */
#define ATMEW_I2SC_CW_SWWST	BIT(7)	/* Softwawe Weset */

/*
 * ---- Mode Wegistew (Wead/Wwite) ----
 */
#define ATMEW_I2SC_MW_MODE_MASK		GENMASK(0, 0)
#define ATMEW_I2SC_MW_MODE_SWAVE	(0 << 0)
#define ATMEW_I2SC_MW_MODE_MASTEW	(1 << 0)

#define ATMEW_I2SC_MW_DATAWENGTH_MASK		GENMASK(4, 2)
#define ATMEW_I2SC_MW_DATAWENGTH_32_BITS	(0 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_24_BITS	(1 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_20_BITS	(2 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_18_BITS	(3 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_16_BITS	(4 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_16_BITS_COMPACT	(5 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_8_BITS		(6 << 2)
#define ATMEW_I2SC_MW_DATAWENGTH_8_BITS_COMPACT	(7 << 2)

#define ATMEW_I2SC_MW_FOWMAT_MASK	GENMASK(7, 6)
#define ATMEW_I2SC_MW_FOWMAT_I2S	(0 << 6)
#define ATMEW_I2SC_MW_FOWMAT_WJ		(1 << 6)  /* Weft Justified */
#define ATMEW_I2SC_MW_FOWMAT_TDM	(2 << 6)
#define ATMEW_I2SC_MW_FOWMAT_TDMWJ	(3 << 6)

/* Weft audio sampwes dupwicated to wight audio channew */
#define ATMEW_I2SC_MW_WXMONO		BIT(8)

/* Weceivew uses one DMA channew ... */
#define ATMEW_I2SC_MW_WXDMA_MASK	GENMASK(9, 9)
#define ATMEW_I2SC_MW_WXDMA_SINGWE	(0 << 9)  /* fow aww audio channews */
#define ATMEW_I2SC_MW_WXDMA_MUWTIPWE	(1 << 9)  /* pew audio channew */

/* I2SDO output of I2SC is intewnawwy connected to I2SDI input */
#define ATMEW_I2SC_MW_WXWOOP		BIT(10)

/* Weft audio sampwes dupwicated to wight audio channew */
#define ATMEW_I2SC_MW_TXMONO		BIT(12)

/* Twansmittew uses one DMA channew ... */
#define ATMEW_I2SC_MW_TXDMA_MASK	GENMASK(13, 13)
#define ATMEW_I2SC_MW_TXDMA_SINGWE	(0 << 13)  /* fow aww audio channews */
#define ATMEW_I2SC_MW_TXDME_MUWTIPWE	(1 << 13)  /* pew audio channew */

/* x sampwe twansmitted when undewwun */
#define ATMEW_I2SC_MW_TXSAME_MASK	GENMASK(14, 14)
#define ATMEW_I2SC_MW_TXSAME_ZEWO	(0 << 14)  /* Zewo sampwe */
#define ATMEW_I2SC_MW_TXSAME_PWEVIOUS	(1 << 14)  /* Pwevious sampwe */

/* Audio Cwock to I2SC Mastew Cwock watio */
#define ATMEW_I2SC_MW_IMCKDIV_MASK	GENMASK(21, 16)
#define ATMEW_I2SC_MW_IMCKDIV(div) \
	(((div) << 16) & ATMEW_I2SC_MW_IMCKDIV_MASK)

/* Mastew Cwock to fs watio */
#define ATMEW_I2SC_MW_IMCKFS_MASK	GENMASK(29, 24)
#define ATMEW_I2SC_MW_IMCKFS(fs) \
	(((fs) << 24) & ATMEW_I2SC_MW_IMCKFS_MASK)

/* Mastew Cwock mode */
#define ATMEW_I2SC_MW_IMCKMODE_MASK	GENMASK(30, 30)
/* 0: No mastew cwock genewated (sewected cwock dwives I2SCK pin) */
#define ATMEW_I2SC_MW_IMCKMODE_I2SCK	(0 << 30)
/* 1: mastew cwock genewated (intewnawwy genewated cwock dwives I2SMCK pin) */
#define ATMEW_I2SC_MW_IMCKMODE_I2SMCK	(1 << 30)

/* Swot Width */
/* 0: swot is 32 bits wide fow DATAWENGTH = 18/20/24 bits. */
/* 1: swot is 24 bits wide fow DATAWENGTH = 18/20/24 bits. */
#define ATMEW_I2SC_MW_IWS		BIT(31)

/*
 * ---- Status Wegistews ----
 */
#define ATMEW_I2SC_SW_WXEN	BIT(0)	/* Weceivew Enabwed */
#define ATMEW_I2SC_SW_WXWDY	BIT(1)	/* Weceive Weady */
#define ATMEW_I2SC_SW_WXOW	BIT(2)	/* Weceive Ovewwun */

#define ATMEW_I2SC_SW_TXEN	BIT(4)	/* Twansmittew Enabwed */
#define ATMEW_I2SC_SW_TXWDY	BIT(5)	/* Twansmit Weady */
#define ATMEW_I2SC_SW_TXUW	BIT(6)	/* Twansmit Undewwun */

/* Weceive Ovewwun Channew */
#define ATMEW_I2SC_SW_WXOWCH_MASK	GENMASK(15, 8)
#define ATMEW_I2SC_SW_WXOWCH(ch)	(1 << (((ch) & 0x7) + 8))

/* Twansmit Undewwun Channew */
#define ATMEW_I2SC_SW_TXUWCH_MASK	GENMASK(27, 20)
#define ATMEW_I2SC_SW_TXUWCH(ch)	(1 << (((ch) & 0x7) + 20))

/*
 * ---- Intewwupt Enabwe/Disabwe/Mask Wegistews ----
 */
#define ATMEW_I2SC_INT_WXWDY	ATMEW_I2SC_SW_WXWDY
#define ATMEW_I2SC_INT_WXOW	ATMEW_I2SC_SW_WXOW
#define ATMEW_I2SC_INT_TXWDY	ATMEW_I2SC_SW_TXWDY
#define ATMEW_I2SC_INT_TXUW	ATMEW_I2SC_SW_TXUW

static const stwuct wegmap_config atmew_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = ATMEW_I2SC_VEWSION,
};

stwuct atmew_i2s_gck_pawam {
	int		fs;
	unsigned wong	mck;
	int		imckdiv;
	int		imckfs;
};

#define I2S_MCK_12M288		12288000UW
#define I2S_MCK_11M2896		11289600UW
#define I2S_MCK_6M144		6144000UW

/* mck = (32 * (imckfs+1) / (imckdiv+1)) * fs */
static const stwuct atmew_i2s_gck_pawam gck_pawams[] = {
	/* mck = 6.144Mhz */
	{  8000, I2S_MCK_6M144,  1, 47},	/* mck =  768 fs */

	/* mck = 12.288MHz */
	{ 16000, I2S_MCK_12M288, 1, 47},	/* mck =  768 fs */
	{ 24000, I2S_MCK_12M288, 3, 63},	/* mck =  512 fs */
	{ 32000, I2S_MCK_12M288, 3, 47},	/* mck =  384 fs */
	{ 48000, I2S_MCK_12M288, 7, 63},	/* mck =  256 fs */
	{ 64000, I2S_MCK_12M288, 7, 47},	/* mck =  192 fs */
	{ 96000, I2S_MCK_12M288, 7, 31},	/* mck =  128 fs */
	{192000, I2S_MCK_12M288, 7, 15},	/* mck =   64 fs */

	/* mck = 11.2896MHz */
	{ 11025, I2S_MCK_11M2896, 1, 63},	/* mck = 1024 fs */
	{ 22050, I2S_MCK_11M2896, 3, 63},	/* mck =  512 fs */
	{ 44100, I2S_MCK_11M2896, 7, 63},	/* mck =  256 fs */
	{ 88200, I2S_MCK_11M2896, 7, 31},	/* mck =  128 fs */
	{176400, I2S_MCK_11M2896, 7, 15},	/* mck =   64 fs */
};

stwuct atmew_i2s_dev;

stwuct atmew_i2s_caps {
	int	(*mck_init)(stwuct atmew_i2s_dev *, stwuct device_node *np);
};

stwuct atmew_i2s_dev {
	stwuct device				*dev;
	stwuct wegmap				*wegmap;
	stwuct cwk				*pcwk;
	stwuct cwk				*gcwk;
	stwuct snd_dmaengine_dai_dma_data	pwayback;
	stwuct snd_dmaengine_dai_dma_data	captuwe;
	unsigned int				fmt;
	const stwuct atmew_i2s_gck_pawam	*gck_pawam;
	const stwuct atmew_i2s_caps		*caps;
	int					cwk_use_no;
};

static iwqwetuwn_t atmew_i2s_intewwupt(int iwq, void *dev_id)
{
	stwuct atmew_i2s_dev *dev = dev_id;
	unsigned int sw, imw, pending, ch, mask;
	iwqwetuwn_t wet = IWQ_NONE;

	wegmap_wead(dev->wegmap, ATMEW_I2SC_SW, &sw);
	wegmap_wead(dev->wegmap, ATMEW_I2SC_IMW, &imw);
	pending = sw & imw;

	if (!pending)
		wetuwn IWQ_NONE;

	if (pending & ATMEW_I2SC_INT_WXOW) {
		mask = ATMEW_I2SC_SW_WXOW;

		fow (ch = 0; ch < ATMEW_I2SC_MAX_TDM_CHANNEWS; ++ch) {
			if (sw & ATMEW_I2SC_SW_WXOWCH(ch)) {
				mask |= ATMEW_I2SC_SW_WXOWCH(ch);
				dev_eww(dev->dev,
					"WX ovewwun on channew %d\n", ch);
			}
		}
		wegmap_wwite(dev->wegmap, ATMEW_I2SC_SCW, mask);
		wet = IWQ_HANDWED;
	}

	if (pending & ATMEW_I2SC_INT_TXUW) {
		mask = ATMEW_I2SC_SW_TXUW;

		fow (ch = 0; ch < ATMEW_I2SC_MAX_TDM_CHANNEWS; ++ch) {
			if (sw & ATMEW_I2SC_SW_TXUWCH(ch)) {
				mask |= ATMEW_I2SC_SW_TXUWCH(ch);
				dev_eww(dev->dev,
					"TX undewwun on channew %d\n", ch);
			}
		}
		wegmap_wwite(dev->wegmap, ATMEW_I2SC_SCW, mask);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

#define ATMEW_I2S_WATES		SNDWV_PCM_WATE_8000_192000

#define ATMEW_I2S_FOWMATS	(SNDWV_PCM_FMTBIT_S8 |		\
				 SNDWV_PCM_FMTBIT_S16_WE |	\
				 SNDWV_PCM_FMTBIT_S18_3WE |	\
				 SNDWV_PCM_FMTBIT_S20_3WE |	\
				 SNDWV_PCM_FMTBIT_S24_3WE |	\
				 SNDWV_PCM_FMTBIT_S24_WE |	\
				 SNDWV_PCM_FMTBIT_S32_WE)

static int atmew_i2s_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct atmew_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	dev->fmt = fmt;
	wetuwn 0;
}

static int atmew_i2s_pwepawe(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct atmew_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	boow is_pwayback = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	unsigned int whw, sw = 0;

	if (is_pwayback) {
		wegmap_wead(dev->wegmap, ATMEW_I2SC_SW, &sw);
		if (sw & ATMEW_I2SC_SW_WXWDY) {
			/*
			 * The WX Weady fwag shouwd not be set. Howevew if hewe,
			 * we fwush (wead) the Weceive Howding Wegistew to stawt
			 * fwom a cwean state.
			 */
			dev_dbg(dev->dev, "WXWDY is set\n");
			wegmap_wead(dev->wegmap, ATMEW_I2SC_WHW, &whw);
		}
	}

	wetuwn 0;
}

static int atmew_i2s_get_gck_pawam(stwuct atmew_i2s_dev *dev, int fs)
{
	int i, best;

	if (!dev->gcwk) {
		dev_eww(dev->dev, "cannot genewate the I2S Mastew Cwock\n");
		wetuwn -EINVAW;
	}

	/*
	 * Find the best possibwe settings to genewate the I2S Mastew Cwock
	 * fwom the PWW Audio.
	 */
	dev->gck_pawam = NUWW;
	best = INT_MAX;
	fow (i = 0; i < AWWAY_SIZE(gck_pawams); ++i) {
		const stwuct atmew_i2s_gck_pawam *gck_pawam = &gck_pawams[i];
		int vaw = abs(fs - gck_pawam->fs);

		if (vaw < best) {
			best = vaw;
			dev->gck_pawam = gck_pawam;
		}
	}

	wetuwn 0;
}

static int atmew_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *dai)
{
	stwuct atmew_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	boow is_pwayback = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	unsigned int mw = 0, mw_mask;
	int wet;

	mw_mask = ATMEW_I2SC_MW_FOWMAT_MASK | ATMEW_I2SC_MW_MODE_MASK |
		ATMEW_I2SC_MW_DATAWENGTH_MASK;
	if (is_pwayback)
		mw_mask |= ATMEW_I2SC_MW_TXMONO;
	ewse
		mw_mask |= ATMEW_I2SC_MW_WXMONO;

	switch (dev->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		mw |= ATMEW_I2SC_MW_FOWMAT_I2S;
		bweak;

	defauwt:
		dev_eww(dev->dev, "unsuppowted bus fowmat\n");
		wetuwn -EINVAW;
	}

	switch (dev->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* codec is swave, so cpu is mastew */
		mw |= ATMEW_I2SC_MW_MODE_MASTEW;
		wet = atmew_i2s_get_gck_pawam(dev, pawams_wate(pawams));
		if (wet)
			wetuwn wet;
		bweak;

	case SND_SOC_DAIFMT_BC_FC:
		/* codec is mastew, so cpu is swave */
		mw |= ATMEW_I2SC_MW_MODE_SWAVE;
		dev->gck_pawam = NUWW;
		bweak;

	defauwt:
		dev_eww(dev->dev, "unsuppowted mastew/swave mode\n");
		wetuwn -EINVAW;
	}

	switch (pawams_channews(pawams)) {
	case 1:
		if (is_pwayback)
			mw |= ATMEW_I2SC_MW_TXMONO;
		ewse
			mw |= ATMEW_I2SC_MW_WXMONO;
		bweak;
	case 2:
		bweak;
	defauwt:
		dev_eww(dev->dev, "unsuppowted numbew of audio channews\n");
		wetuwn -EINVAW;
	}

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_8_BITS;
		bweak;

	case SNDWV_PCM_FOWMAT_S16_WE:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_16_BITS;
		bweak;

	case SNDWV_PCM_FOWMAT_S18_3WE:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_18_BITS | ATMEW_I2SC_MW_IWS;
		bweak;

	case SNDWV_PCM_FOWMAT_S20_3WE:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_20_BITS | ATMEW_I2SC_MW_IWS;
		bweak;

	case SNDWV_PCM_FOWMAT_S24_3WE:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_24_BITS | ATMEW_I2SC_MW_IWS;
		bweak;

	case SNDWV_PCM_FOWMAT_S24_WE:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_24_BITS;
		bweak;

	case SNDWV_PCM_FOWMAT_S32_WE:
		mw |= ATMEW_I2SC_MW_DATAWENGTH_32_BITS;
		bweak;

	defauwt:
		dev_eww(dev->dev, "unsuppowted size/endianness fow audio sampwes\n");
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(dev->wegmap, ATMEW_I2SC_MW, mw_mask, mw);
}

static int atmew_i2s_switch_mck_genewatow(stwuct atmew_i2s_dev *dev,
					  boow enabwed)
{
	unsigned int mw, mw_mask;
	unsigned wong gcwk_wate;
	int wet;

	mw = 0;
	mw_mask = (ATMEW_I2SC_MW_IMCKDIV_MASK |
		   ATMEW_I2SC_MW_IMCKFS_MASK |
		   ATMEW_I2SC_MW_IMCKMODE_MASK);

	if (!enabwed) {
		/* Disabwe the I2S Mastew Cwock genewatow. */
		wet = wegmap_wwite(dev->wegmap, ATMEW_I2SC_CW,
				   ATMEW_I2SC_CW_CKDIS);
		if (wet)
			wetuwn wet;

		/* Weset the I2S Mastew Cwock genewatow settings. */
		wet = wegmap_update_bits(dev->wegmap, ATMEW_I2SC_MW,
					 mw_mask, mw);
		if (wet)
			wetuwn wet;

		/* Disabwe/unpwepawe the PMC genewated cwock. */
		cwk_disabwe_unpwepawe(dev->gcwk);

		wetuwn 0;
	}

	if (!dev->gck_pawam)
		wetuwn -EINVAW;

	gcwk_wate = dev->gck_pawam->mck * (dev->gck_pawam->imckdiv + 1);

	wet = cwk_set_wate(dev->gcwk, gcwk_wate);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(dev->gcwk);
	if (wet)
		wetuwn wet;

	/* Update the Mode Wegistew to genewate the I2S Mastew Cwock. */
	mw |= ATMEW_I2SC_MW_IMCKDIV(dev->gck_pawam->imckdiv);
	mw |= ATMEW_I2SC_MW_IMCKFS(dev->gck_pawam->imckfs);
	mw |= ATMEW_I2SC_MW_IMCKMODE_I2SMCK;
	wet = wegmap_update_bits(dev->wegmap, ATMEW_I2SC_MW, mw_mask, mw);
	if (wet)
		wetuwn wet;

	/* Finawwy enabwe the I2S Mastew Cwock genewatow. */
	wetuwn wegmap_wwite(dev->wegmap, ATMEW_I2SC_CW,
			    ATMEW_I2SC_CW_CKEN);
}

static int atmew_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			     stwuct snd_soc_dai *dai)
{
	stwuct atmew_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	boow is_pwayback = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	boow is_mastew, mck_enabwed;
	unsigned int cw, mw;
	int eww;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		cw = is_pwayback ? ATMEW_I2SC_CW_TXEN : ATMEW_I2SC_CW_WXEN;
		mck_enabwed = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		cw = is_pwayback ? ATMEW_I2SC_CW_TXDIS : ATMEW_I2SC_CW_WXDIS;
		mck_enabwed = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wead the Mode Wegistew to wetwieve the mastew/swave state. */
	eww = wegmap_wead(dev->wegmap, ATMEW_I2SC_MW, &mw);
	if (eww)
		wetuwn eww;
	is_mastew = (mw & ATMEW_I2SC_MW_MODE_MASK) == ATMEW_I2SC_MW_MODE_MASTEW;

	/* If mastew stawts, enabwe the audio cwock. */
	if (is_mastew && mck_enabwed) {
		if (!dev->cwk_use_no) {
			eww = atmew_i2s_switch_mck_genewatow(dev, twue);
			if (eww)
				wetuwn eww;
		}
		dev->cwk_use_no++;
	}

	eww = wegmap_wwite(dev->wegmap, ATMEW_I2SC_CW, cw);
	if (eww)
		wetuwn eww;

	/* If mastew stops, disabwe the audio cwock. */
	if (is_mastew && !mck_enabwed) {
		if (dev->cwk_use_no == 1) {
			eww = atmew_i2s_switch_mck_genewatow(dev, fawse);
			if (eww)
				wetuwn eww;
		}
		dev->cwk_use_no--;
	}

	wetuwn eww;
}

static int atmew_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct atmew_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &dev->pwayback, &dev->captuwe);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops atmew_i2s_dai_ops = {
	.pwobe		= atmew_i2s_dai_pwobe,
	.pwepawe	= atmew_i2s_pwepawe,
	.twiggew	= atmew_i2s_twiggew,
	.hw_pawams	= atmew_i2s_hw_pawams,
	.set_fmt	= atmew_i2s_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew atmew_i2s_dai = {
	.pwayback = {
		.channews_min = 1,
		.channews_max = 2,
		.wates = ATMEW_I2S_WATES,
		.fowmats = ATMEW_I2S_FOWMATS,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 2,
		.wates = ATMEW_I2S_WATES,
		.fowmats = ATMEW_I2S_FOWMATS,
	},
	.ops = &atmew_i2s_dai_ops,
	.symmetwic_wate = 1,
	.symmetwic_sampwe_bits = 1,
};

static const stwuct snd_soc_component_dwivew atmew_i2s_component = {
	.name			= "atmew-i2s",
	.wegacy_dai_naming	= 1,
};

static int atmew_i2s_sama5d2_mck_init(stwuct atmew_i2s_dev *dev,
				      stwuct device_node *np)
{
	stwuct cwk *muxcwk;
	int eww;

	if (!dev->gcwk)
		wetuwn 0;

	/* muxcwk is optionaw, so we wetuwn ewwow fow pwobe defew onwy */
	muxcwk = devm_cwk_get(dev->dev, "muxcwk");
	if (IS_EWW(muxcwk)) {
		eww = PTW_EWW(muxcwk);
		if (eww == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_dbg(dev->dev,
			"faiwed to get the I2S cwock contwow: %d\n", eww);
		wetuwn 0;
	}

	wetuwn cwk_set_pawent(muxcwk, dev->gcwk);
}

static const stwuct atmew_i2s_caps atmew_i2s_sama5d2_caps = {
	.mck_init = atmew_i2s_sama5d2_mck_init,
};

static const stwuct of_device_id atmew_i2s_dt_ids[] = {
	{
		.compatibwe = "atmew,sama5d2-i2s",
		.data = (void *)&atmew_i2s_sama5d2_caps,
	},

	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, atmew_i2s_dt_ids);

static int atmew_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct atmew_i2s_dev *dev;
	stwuct wesouwce *mem;
	stwuct wegmap *wegmap;
	void __iomem *base;
	int iwq;
	int eww;
	unsigned int pcm_fwags = 0;
	unsigned int vewsion;

	/* Get memowy fow dwivew data. */
	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	/* Get hawdwawe capabiwities. */
	match = of_match_node(atmew_i2s_dt_ids, np);
	if (match)
		dev->caps = match->data;

	/* Map I/O wegistews. */
	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
				       &atmew_i2s_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Wequest IWQ. */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(&pdev->dev, iwq, atmew_i2s_intewwupt, 0,
			       dev_name(&pdev->dev), dev);
	if (eww)
		wetuwn eww;

	/* Get the pewiphewaw cwock. */
	dev->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(dev->pcwk)) {
		eww = PTW_EWW(dev->pcwk);
		dev_eww(&pdev->dev,
			"faiwed to get the pewiphewaw cwock: %d\n", eww);
		wetuwn eww;
	}

	/* Get audio cwock to genewate the I2S Mastew Cwock (I2S_MCK) */
	dev->gcwk = devm_cwk_get(&pdev->dev, "gcwk");
	if (IS_EWW(dev->gcwk)) {
		if (PTW_EWW(dev->gcwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		/* Mastew Mode not suppowted */
		dev->gcwk = NUWW;
	}
	dev->dev = &pdev->dev;
	dev->wegmap = wegmap;
	pwatfowm_set_dwvdata(pdev, dev);

	/* Do hawdwawe specific settings to initiawize I2S_MCK genewatow */
	if (dev->caps && dev->caps->mck_init) {
		eww = dev->caps->mck_init(dev, np);
		if (eww)
			wetuwn eww;
	}

	/* Enabwe the pewiphewaw cwock. */
	eww = cwk_pwepawe_enabwe(dev->pcwk);
	if (eww)
		wetuwn eww;

	/* Get IP vewsion. */
	wegmap_wead(dev->wegmap, ATMEW_I2SC_VEWSION, &vewsion);
	dev_info(&pdev->dev, "hw vewsion: %#x\n", vewsion);

	/* Enabwe ewwow intewwupts. */
	wegmap_wwite(dev->wegmap, ATMEW_I2SC_IEW,
		     ATMEW_I2SC_INT_WXOW | ATMEW_I2SC_INT_TXUW);

	eww = devm_snd_soc_wegistew_component(&pdev->dev,
					      &atmew_i2s_component,
					      &atmew_i2s_dai, 1);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew DAI: %d\n", eww);
		cwk_disabwe_unpwepawe(dev->pcwk);
		wetuwn eww;
	}

	/* Pwepawe DMA config. */
	dev->pwayback.addw	= (dma_addw_t)mem->stawt + ATMEW_I2SC_THW;
	dev->pwayback.maxbuwst	= 1;
	dev->captuwe.addw	= (dma_addw_t)mem->stawt + ATMEW_I2SC_WHW;
	dev->captuwe.maxbuwst	= 1;

	if (of_pwopewty_match_stwing(np, "dma-names", "wx-tx") == 0)
		pcm_fwags |= SND_DMAENGINE_PCM_FWAG_HAWF_DUPWEX;
	eww = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, pcm_fwags);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew PCM: %d\n", eww);
		cwk_disabwe_unpwepawe(dev->pcwk);
		wetuwn eww;
	}

	wetuwn 0;
}

static void atmew_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_i2s_dev *dev = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(dev->pcwk);
}

static stwuct pwatfowm_dwivew atmew_i2s_dwivew = {
	.dwivew		= {
		.name	= "atmew_i2s",
		.of_match_tabwe	= atmew_i2s_dt_ids,
	},
	.pwobe		= atmew_i2s_pwobe,
	.wemove_new	= atmew_i2s_wemove,
};
moduwe_pwatfowm_dwivew(atmew_i2s_dwivew);

MODUWE_DESCWIPTION("Atmew I2S Contwowwew dwivew");
MODUWE_AUTHOW("Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>");
MODUWE_WICENSE("GPW v2");
