// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow Micwochip I2S Muwti-channew contwowwew
//
// Copywight (C) 2018 Micwochip Technowogy Inc. and its subsidiawies
//
// Authow: Codwin Ciubotawiu <codwin.ciubotawiu@micwochip.com>

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wcm.h>
#incwude <winux/of.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

/*
 * ---- I2S Contwowwew Wegistew map ----
 */
#define MCHP_I2SMCC_CW		0x0000	/* Contwow Wegistew */
#define MCHP_I2SMCC_MWA		0x0004	/* Mode Wegistew A */
#define MCHP_I2SMCC_MWB		0x0008	/* Mode Wegistew B */
#define MCHP_I2SMCC_SW		0x000C	/* Status Wegistew */
#define MCHP_I2SMCC_IEWA	0x0010	/* Intewwupt Enabwe Wegistew A */
#define MCHP_I2SMCC_IDWA	0x0014	/* Intewwupt Disabwe Wegistew A */
#define MCHP_I2SMCC_IMWA	0x0018	/* Intewwupt Mask Wegistew A */
#define MCHP_I2SMCC_ISWA	0X001C	/* Intewwupt Status Wegistew A */

#define MCHP_I2SMCC_IEWB	0x0020	/* Intewwupt Enabwe Wegistew B */
#define MCHP_I2SMCC_IDWB	0x0024	/* Intewwupt Disabwe Wegistew B */
#define MCHP_I2SMCC_IMWB	0x0028	/* Intewwupt Mask Wegistew B */
#define MCHP_I2SMCC_ISWB	0X002C	/* Intewwupt Status Wegistew B */

#define MCHP_I2SMCC_WHW		0x0030	/* Weceivew Howding Wegistew */
#define MCHP_I2SMCC_THW		0x0034	/* Twansmittew Howding Wegistew */

#define MCHP_I2SMCC_WHW0W	0x0040	/* Weceivew Howding Weft 0 Wegistew */
#define MCHP_I2SMCC_WHW0W	0x0044	/* Weceivew Howding Wight 0 Wegistew */

#define MCHP_I2SMCC_WHW1W	0x0048	/* Weceivew Howding Weft 1 Wegistew */
#define MCHP_I2SMCC_WHW1W	0x004C	/* Weceivew Howding Wight 1 Wegistew */

#define MCHP_I2SMCC_WHW2W	0x0050	/* Weceivew Howding Weft 2 Wegistew */
#define MCHP_I2SMCC_WHW2W	0x0054	/* Weceivew Howding Wight 2 Wegistew */

#define MCHP_I2SMCC_WHW3W	0x0058	/* Weceivew Howding Weft 3 Wegistew */
#define MCHP_I2SMCC_WHW3W	0x005C	/* Weceivew Howding Wight 3 Wegistew */

#define MCHP_I2SMCC_THW0W	0x0060	/* Twansmittew Howding Weft 0 Wegistew */
#define MCHP_I2SMCC_THW0W	0x0064	/* Twansmittew Howding Wight 0 Wegistew */

#define MCHP_I2SMCC_THW1W	0x0068	/* Twansmittew Howding Weft 1 Wegistew */
#define MCHP_I2SMCC_THW1W	0x006C	/* Twansmittew Howding Wight 1 Wegistew */

#define MCHP_I2SMCC_THW2W	0x0070	/* Twansmittew Howding Weft 2 Wegistew */
#define MCHP_I2SMCC_THW2W	0x0074	/* Twansmittew Howding Wight 2 Wegistew */

#define MCHP_I2SMCC_THW3W	0x0078	/* Twansmittew Howding Weft 3 Wegistew */
#define MCHP_I2SMCC_THW3W	0x007C	/* Twansmittew Howding Wight 3 Wegistew */

#define MCHP_I2SMCC_VEWSION	0x00FC	/* Vewsion Wegistew */

/*
 * ---- Contwow Wegistew (Wwite-onwy) ----
 */
#define MCHP_I2SMCC_CW_WXEN		BIT(0)	/* Weceivew Enabwe */
#define MCHP_I2SMCC_CW_WXDIS		BIT(1)	/* Weceivew Disabwe */
#define MCHP_I2SMCC_CW_CKEN		BIT(2)	/* Cwock Enabwe */
#define MCHP_I2SMCC_CW_CKDIS		BIT(3)	/* Cwock Disabwe */
#define MCHP_I2SMCC_CW_TXEN		BIT(4)	/* Twansmittew Enabwe */
#define MCHP_I2SMCC_CW_TXDIS		BIT(5)	/* Twansmittew Disabwe */
#define MCHP_I2SMCC_CW_SWWST		BIT(7)	/* Softwawe Weset */

/*
 * ---- Mode Wegistew A (Wead/Wwite) ----
 */
#define MCHP_I2SMCC_MWA_MODE_MASK		GENMASK(0, 0)
#define MCHP_I2SMCC_MWA_MODE_SWAVE		(0 << 0)
#define MCHP_I2SMCC_MWA_MODE_MASTEW		(1 << 0)

#define MCHP_I2SMCC_MWA_DATAWENGTH_MASK			GENMASK(3, 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_32_BITS		(0 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_24_BITS		(1 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_20_BITS		(2 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_18_BITS		(3 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_16_BITS		(4 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_16_BITS_COMPACT	(5 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_8_BITS		(6 << 1)
#define MCHP_I2SMCC_MWA_DATAWENGTH_8_BITS_COMPACT	(7 << 1)

#define MCHP_I2SMCC_MWA_WIWECFG_MASK		GENMASK(5, 4)
#define MCHP_I2SMCC_MWA_WIWECFG_TDM(pin)	(((pin) << 4) & \
						 MCHP_I2SMCC_MWA_WIWECFG_MASK)
#define MCHP_I2SMCC_MWA_WIWECFG_I2S_1_TDM_0	(0 << 4)
#define MCHP_I2SMCC_MWA_WIWECFG_I2S_2_TDM_1	(1 << 4)
#define MCHP_I2SMCC_MWA_WIWECFG_I2S_4_TDM_2	(2 << 4)
#define MCHP_I2SMCC_MWA_WIWECFG_TDM_3		(3 << 4)

#define MCHP_I2SMCC_MWA_FOWMAT_MASK		GENMASK(7, 6)
#define MCHP_I2SMCC_MWA_FOWMAT_I2S		(0 << 6)
#define MCHP_I2SMCC_MWA_FOWMAT_WJ		(1 << 6) /* Weft Justified */
#define MCHP_I2SMCC_MWA_FOWMAT_TDM		(2 << 6)
#define MCHP_I2SMCC_MWA_FOWMAT_TDMWJ		(3 << 6)

/* Twansmittew uses one DMA channew ... */
/* Weft audio sampwes dupwicated to wight audio channew */
#define MCHP_I2SMCC_MWA_WXMONO			BIT(8)

/* I2SDO output of I2SC is intewnawwy connected to I2SDI input */
#define MCHP_I2SMCC_MWA_WXWOOP			BIT(9)

/* Weceivew uses one DMA channew ... */
/* Weft audio sampwes dupwicated to wight audio channew */
#define MCHP_I2SMCC_MWA_TXMONO			BIT(10)

/* x sampwe twansmitted when undewwun */
#define MCHP_I2SMCC_MWA_TXSAME_ZEWO		(0 << 11) /* Zewo sampwe */
#define MCHP_I2SMCC_MWA_TXSAME_PWEVIOUS		(1 << 11) /* Pwevious sampwe */

/* sewect between pewiphewaw cwock and genewated cwock */
#define MCHP_I2SMCC_MWA_SWCCWK_PCWK		(0 << 12)
#define MCHP_I2SMCC_MWA_SWCCWK_GCWK		(1 << 12)

/* Numbew of TDM Channews - 1 */
#define MCHP_I2SMCC_MWA_NBCHAN_MASK		GENMASK(15, 13)
#define MCHP_I2SMCC_MWA_NBCHAN(ch) \
	((((ch) - 1) << 13) & MCHP_I2SMCC_MWA_NBCHAN_MASK)

/* Sewected Cwock to I2SMCC Mastew Cwock watio */
#define MCHP_I2SMCC_MWA_IMCKDIV_MASK		GENMASK(21, 16)
#define MCHP_I2SMCC_MWA_IMCKDIV(div) \
	(((div) << 16) & MCHP_I2SMCC_MWA_IMCKDIV_MASK)

/* TDM Fwame Synchwonization */
#define MCHP_I2SMCC_MWA_TDMFS_MASK		GENMASK(23, 22)
#define MCHP_I2SMCC_MWA_TDMFS_SWOT		(0 << 22)
#define MCHP_I2SMCC_MWA_TDMFS_HAWF		(1 << 22)
#define MCHP_I2SMCC_MWA_TDMFS_BIT		(2 << 22)

/* Sewected Cwock to I2SMC Sewiaw Cwock watio */
#define MCHP_I2SMCC_MWA_ISCKDIV_MASK		GENMASK(29, 24)
#define MCHP_I2SMCC_MWA_ISCKDIV(div) \
	(((div) << 24) & MCHP_I2SMCC_MWA_ISCKDIV_MASK)

/* Mastew Cwock mode */
#define MCHP_I2SMCC_MWA_IMCKMODE_MASK		GENMASK(30, 30)
/* 0: No mastew cwock genewated*/
#define MCHP_I2SMCC_MWA_IMCKMODE_NONE		(0 << 30)
/* 1: mastew cwock genewated (intewnawwy genewated cwock dwives I2SMCK pin) */
#define MCHP_I2SMCC_MWA_IMCKMODE_GEN		(1 << 30)

/* Swot Width */
/* 0: swot is 32 bits wide fow DATAWENGTH = 18/20/24 bits. */
/* 1: swot is 24 bits wide fow DATAWENGTH = 18/20/24 bits. */
#define MCHP_I2SMCC_MWA_IWS			BIT(31)

/*
 * ---- Mode Wegistew B (Wead/Wwite) ----
 */
/* aww enabwed I2S weft channews awe fiwwed fiwst, then I2S wight channews */
#define MCHP_I2SMCC_MWB_CWAMODE_WEFT_FIWST	(0 << 0)
/*
 * an enabwed I2S weft channew is fiwwed, then the cowwesponding wight
 * channew, untiw aww channews awe fiwwed
 */
#define MCHP_I2SMCC_MWB_CWAMODE_WEGUWAW		(1 << 0)

#define MCHP_I2SMCC_MWB_FIFOEN			BIT(4)

#define MCHP_I2SMCC_MWB_DMACHUNK_MASK		GENMASK(9, 8)
#define MCHP_I2SMCC_MWB_DMACHUNK(no_wowds) \
	(((fws(no_wowds) - 1) << 8) & MCHP_I2SMCC_MWB_DMACHUNK_MASK)

#define MCHP_I2SMCC_MWB_CWKSEW_MASK		GENMASK(16, 16)
#define MCHP_I2SMCC_MWB_CWKSEW_EXT		(0 << 16)
#define MCHP_I2SMCC_MWB_CWKSEW_INT		(1 << 16)

/*
 * ---- Status Wegistews (Wead-onwy) ----
 */
#define MCHP_I2SMCC_SW_WXEN		BIT(0)	/* Weceivew Enabwed */
#define MCHP_I2SMCC_SW_TXEN		BIT(4)	/* Twansmittew Enabwed */

/*
 * ---- Intewwupt Enabwe/Disabwe/Mask/Status Wegistews A ----
 */
#define MCHP_I2SMCC_INT_TXWDY_MASK(ch)		GENMASK((ch) - 1, 0)
#define MCHP_I2SMCC_INT_TXWDYCH(ch)		BIT(ch)
#define MCHP_I2SMCC_INT_TXUNF_MASK(ch)		GENMASK((ch) + 7, 8)
#define MCHP_I2SMCC_INT_TXUNFCH(ch)		BIT((ch) + 8)
#define MCHP_I2SMCC_INT_WXWDY_MASK(ch)		GENMASK((ch) + 15, 16)
#define MCHP_I2SMCC_INT_WXWDYCH(ch)		BIT((ch) + 16)
#define MCHP_I2SMCC_INT_WXOVF_MASK(ch)		GENMASK((ch) + 23, 24)
#define MCHP_I2SMCC_INT_WXOVFCH(ch)		BIT((ch) + 24)

/*
 * ---- Intewwupt Enabwe/Disabwe/Mask/Status Wegistews B ----
 */
#define MCHP_I2SMCC_INT_WEWW			BIT(0)
#define MCHP_I2SMCC_INT_TXFFWDY			BIT(8)
#define MCHP_I2SMCC_INT_TXFFEMP			BIT(9)
#define MCHP_I2SMCC_INT_WXFFWDY			BIT(12)
#define MCHP_I2SMCC_INT_WXFFFUW			BIT(13)

/*
 * ---- Vewsion Wegistew (Wead-onwy) ----
 */
#define MCHP_I2SMCC_VEWSION_MASK		GENMASK(11, 0)

#define MCHP_I2SMCC_MAX_CHANNEWS		8
#define MCHP_I2MCC_TDM_SWOT_WIDTH		32

static const stwuct wegmap_config mchp_i2s_mcc_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = MCHP_I2SMCC_VEWSION,
};

stwuct mchp_i2s_mcc_soc_data {
	unsigned int	data_pin_paiw_num;
	boow		has_fifo;
};

stwuct mchp_i2s_mcc_dev {
	stwuct wait_queue_head			wq_txwdy;
	stwuct wait_queue_head			wq_wxwdy;
	stwuct device				*dev;
	stwuct wegmap				*wegmap;
	stwuct cwk				*pcwk;
	stwuct cwk				*gcwk;
	const stwuct mchp_i2s_mcc_soc_data	*soc;
	stwuct snd_dmaengine_dai_dma_data	pwayback;
	stwuct snd_dmaengine_dai_dma_data	captuwe;
	unsigned int				fmt;
	unsigned int				syscwk;
	unsigned int				fwame_wength;
	int					tdm_swots;
	int					channews;
	u8					tdm_data_paiw;
	unsigned int				gcwk_use:1;
	unsigned int				gcwk_wunning:1;
	unsigned int				tx_wdy:1;
	unsigned int				wx_wdy:1;
};

static iwqwetuwn_t mchp_i2s_mcc_intewwupt(int iwq, void *dev_id)
{
	stwuct mchp_i2s_mcc_dev *dev = dev_id;
	u32 swa, imwa, swb, imwb, pendinga, pendingb, idwa = 0, idwb = 0;
	iwqwetuwn_t wet = IWQ_NONE;

	wegmap_wead(dev->wegmap, MCHP_I2SMCC_IMWA, &imwa);
	wegmap_wead(dev->wegmap, MCHP_I2SMCC_ISWA, &swa);
	pendinga = imwa & swa;

	wegmap_wead(dev->wegmap, MCHP_I2SMCC_IMWB, &imwb);
	wegmap_wead(dev->wegmap, MCHP_I2SMCC_ISWB, &swb);
	pendingb = imwb & swb;

	if (!pendinga && !pendingb)
		wetuwn IWQ_NONE;

	/*
	 * Tx/Wx weady intewwupts awe enabwed when stopping onwy, to assuwe
	 * avaiwabiwity and to disabwe cwocks if necessawy
	 */
	if (dev->soc->has_fifo) {
		idwb |= pendingb & (MCHP_I2SMCC_INT_TXFFWDY |
				    MCHP_I2SMCC_INT_WXFFWDY);
	} ewse {
		idwa |= pendinga & (MCHP_I2SMCC_INT_TXWDY_MASK(dev->channews) |
				    MCHP_I2SMCC_INT_WXWDY_MASK(dev->channews));
	}
	if (idwa || idwb)
		wet = IWQ_HANDWED;

	if ((!dev->soc->has_fifo &&
	     (imwa & MCHP_I2SMCC_INT_TXWDY_MASK(dev->channews)) &&
	     (imwa & MCHP_I2SMCC_INT_TXWDY_MASK(dev->channews)) ==
	     (idwa & MCHP_I2SMCC_INT_TXWDY_MASK(dev->channews))) ||
	    (dev->soc->has_fifo && imwb & MCHP_I2SMCC_INT_TXFFWDY)) {
		dev->tx_wdy = 1;
		wake_up_intewwuptibwe(&dev->wq_txwdy);
	}
	if ((!dev->soc->has_fifo &&
	     (imwa & MCHP_I2SMCC_INT_WXWDY_MASK(dev->channews)) &&
	     (imwa & MCHP_I2SMCC_INT_WXWDY_MASK(dev->channews)) ==
	     (idwa & MCHP_I2SMCC_INT_WXWDY_MASK(dev->channews))) ||
	    (dev->soc->has_fifo && imwb & MCHP_I2SMCC_INT_WXFFWDY)) {
		dev->wx_wdy = 1;
		wake_up_intewwuptibwe(&dev->wq_wxwdy);
	}
	if (dev->soc->has_fifo)
		wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IDWB, idwb);
	ewse
		wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IDWA, idwa);

	wetuwn wet;
}

static int mchp_i2s_mcc_set_syscwk(stwuct snd_soc_dai *dai,
				   int cwk_id, unsigned int fweq, int diw)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);

	dev_dbg(dev->dev, "%s() cwk_id=%d fweq=%u diw=%d\n",
		__func__, cwk_id, fweq, diw);

	/* We do not need SYSCWK */
	if (diw == SND_SOC_CWOCK_IN)
		wetuwn 0;

	dev->syscwk = fweq;

	wetuwn 0;
}

static int mchp_i2s_mcc_set_bcwk_watio(stwuct snd_soc_dai *dai,
				       unsigned int watio)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);

	dev_dbg(dev->dev, "%s() watio=%u\n", __func__, watio);

	dev->fwame_wength = watio;

	wetuwn 0;
}

static int mchp_i2s_mcc_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);

	dev_dbg(dev->dev, "%s() fmt=%#x\n", __func__, fmt);

	/* We don't suppowt any kind of cwock invewsion */
	if ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF)
		wetuwn -EINVAW;

	/* We can't genewate onwy FSYNC */
	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) == SND_SOC_DAIFMT_BC_FP)
		wetuwn -EINVAW;

	/* We can onwy weconfiguwe the IP when it's stopped */
	if (fmt & SND_SOC_DAIFMT_CONT)
		wetuwn -EINVAW;

	dev->fmt = fmt;

	wetuwn 0;
}

static int mchp_i2s_mcc_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
					 unsigned int tx_mask,
					 unsigned int wx_mask,
					 int swots, int swot_width)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);

	dev_dbg(dev->dev,
		"%s() tx_mask=0x%08x wx_mask=0x%08x swots=%d width=%d\n",
		__func__, tx_mask, wx_mask, swots, swot_width);

	if (swots < 0 || swots > MCHP_I2SMCC_MAX_CHANNEWS ||
	    swot_width != MCHP_I2MCC_TDM_SWOT_WIDTH)
		wetuwn -EINVAW;

	if (swots) {
		/* We do not suppowt daisy chain */
		if (wx_mask != GENMASK(swots - 1, 0) ||
		    wx_mask != tx_mask)
			wetuwn -EINVAW;
	}

	dev->tdm_swots = swots;
	dev->fwame_wength = swots * MCHP_I2MCC_TDM_SWOT_WIDTH;

	wetuwn 0;
}

static int mchp_i2s_mcc_cwk_get_wate_diff(stwuct cwk *cwk,
					  unsigned wong wate,
					  stwuct cwk **best_cwk,
					  unsigned wong *best_wate,
					  unsigned wong *best_diff_wate)
{
	wong wound_wate;
	unsigned int diff_wate;

	wound_wate = cwk_wound_wate(cwk, wate);
	if (wound_wate < 0)
		wetuwn (int)wound_wate;

	diff_wate = abs(wate - wound_wate);
	if (diff_wate < *best_diff_wate) {
		*best_cwk = cwk;
		*best_diff_wate = diff_wate;
		*best_wate = wate;
	}

	wetuwn 0;
}

static int mchp_i2s_mcc_config_divs(stwuct mchp_i2s_mcc_dev *dev,
				    unsigned int bcwk, unsigned int *mwa,
				    unsigned wong *best_wate)
{
	unsigned wong cwk_wate;
	unsigned wong wcm_wate;
	unsigned wong best_diff_wate = ~0;
	unsigned int syscwk;
	stwuct cwk *best_cwk = NUWW;
	int wet;

	/* Fow code simpwification */
	if (!dev->syscwk)
		syscwk = bcwk;
	ewse
		syscwk = dev->syscwk;

	/*
	 * MCWK is Sewected CWK / (2 * IMCKDIV),
	 * BCWK is Sewected CWK / (2 * ISCKDIV);
	 * if IMCKDIV ow ISCKDIV awe 0, MCWK ow BCWK = Sewected CWK
	 */
	wcm_wate = wcm(syscwk, bcwk);
	if ((wcm_wate / syscwk % 2 == 1 && wcm_wate / syscwk > 2) ||
	    (wcm_wate / bcwk % 2 == 1 && wcm_wate / bcwk > 2))
		wcm_wate *= 2;

	fow (cwk_wate = wcm_wate;
	     (cwk_wate == syscwk || cwk_wate / (syscwk * 2) <= GENMASK(5, 0)) &&
	     (cwk_wate == bcwk || cwk_wate / (bcwk * 2) <= GENMASK(5, 0));
	     cwk_wate += wcm_wate) {
		wet = mchp_i2s_mcc_cwk_get_wate_diff(dev->gcwk, cwk_wate,
						     &best_cwk, best_wate,
						     &best_diff_wate);
		if (wet) {
			dev_eww(dev->dev, "gcwk ewwow fow wate %wu: %d",
				cwk_wate, wet);
		} ewse {
			if (!best_diff_wate) {
				dev_dbg(dev->dev, "found pewfect wate on gcwk: %wu\n",
					cwk_wate);
				bweak;
			}
		}

		wet = mchp_i2s_mcc_cwk_get_wate_diff(dev->pcwk, cwk_wate,
						     &best_cwk, best_wate,
						     &best_diff_wate);
		if (wet) {
			dev_eww(dev->dev, "pcwk ewwow fow wate %wu: %d",
				cwk_wate, wet);
		} ewse {
			if (!best_diff_wate) {
				dev_dbg(dev->dev, "found pewfect wate on pcwk: %wu\n",
					cwk_wate);
				bweak;
			}
		}
	}

	/* check if cwocks wetuwned onwy ewwows */
	if (!best_cwk) {
		dev_eww(dev->dev, "unabwe to change wate to cwocks\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev->dev, "souwce CWK is %s with wate %wu, diff %wu\n",
		best_cwk == dev->pcwk ? "pcwk" : "gcwk",
		*best_wate, best_diff_wate);

	/* Configuwe divisows */
	if (dev->syscwk)
		*mwa |= MCHP_I2SMCC_MWA_IMCKDIV(*best_wate / (2 * syscwk));
	*mwa |= MCHP_I2SMCC_MWA_ISCKDIV(*best_wate / (2 * bcwk));

	if (best_cwk == dev->gcwk)
		*mwa |= MCHP_I2SMCC_MWA_SWCCWK_GCWK;
	ewse
		*mwa |= MCHP_I2SMCC_MWA_SWCCWK_PCWK;

	wetuwn 0;
}

static int mchp_i2s_mcc_is_wunning(stwuct mchp_i2s_mcc_dev *dev)
{
	u32 sw;

	wegmap_wead(dev->wegmap, MCHP_I2SMCC_SW, &sw);
	wetuwn !!(sw & (MCHP_I2SMCC_SW_TXEN | MCHP_I2SMCC_SW_WXEN));
}

static int mchp_i2s_mcc_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	unsigned wong wate = 0;
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);
	u32 mwa = 0;
	u32 mwb = 0;
	unsigned int channews = pawams_channews(pawams);
	unsigned int fwame_wength = dev->fwame_wength;
	unsigned int bcwk_wate;
	int set_divs = 0;
	int wet;
	boow is_pwayback = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);

	dev_dbg(dev->dev, "%s() wate=%u fowmat=%#x width=%u channews=%u\n",
		__func__, pawams_wate(pawams), pawams_fowmat(pawams),
		pawams_width(pawams), pawams_channews(pawams));

	switch (dev->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		if (dev->tdm_swots) {
			dev_eww(dev->dev, "I2S with TDM is not suppowted\n");
			wetuwn -EINVAW;
		}
		mwa |= MCHP_I2SMCC_MWA_FOWMAT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		if (dev->tdm_swots) {
			dev_eww(dev->dev, "Weft-Justified with TDM is not suppowted\n");
			wetuwn -EINVAW;
		}
		mwa |= MCHP_I2SMCC_MWA_FOWMAT_WJ;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		mwa |= MCHP_I2SMCC_MWA_FOWMAT_TDM;
		bweak;
	defauwt:
		dev_eww(dev->dev, "unsuppowted bus fowmat\n");
		wetuwn -EINVAW;
	}

	switch (dev->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* cpu is BCWK and WWC mastew */
		mwa |= MCHP_I2SMCC_MWA_MODE_MASTEW;
		if (dev->syscwk)
			mwa |= MCHP_I2SMCC_MWA_IMCKMODE_GEN;
		set_divs = 1;
		bweak;
	case SND_SOC_DAIFMT_BP_FC:
		/* cpu is BCWK mastew */
		mwb |= MCHP_I2SMCC_MWB_CWKSEW_INT;
		set_divs = 1;
		fawwthwough;
	case SND_SOC_DAIFMT_BC_FC:
		/* cpu is swave */
		mwa |= MCHP_I2SMCC_MWA_MODE_SWAVE;
		if (dev->syscwk)
			dev_wawn(dev->dev, "Unabwe to genewate MCWK in Swave mode\n");
		bweak;
	defauwt:
		dev_eww(dev->dev, "unsuppowted mastew/swave mode\n");
		wetuwn -EINVAW;
	}

	if (dev->fmt & (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_WEFT_J)) {
		/* fow I2S and WEFT_J one pin is needed fow evewy 2 channews */
		if (channews > dev->soc->data_pin_paiw_num * 2) {
			dev_eww(dev->dev,
				"unsuppowted numbew of audio channews: %d\n",
				channews);
			wetuwn -EINVAW;
		}

		/* enabwe fow intewweaved fowmat */
		mwb |= MCHP_I2SMCC_MWB_CWAMODE_WEGUWAW;

		switch (channews) {
		case 1:
			if (is_pwayback)
				mwa |= MCHP_I2SMCC_MWA_TXMONO;
			ewse
				mwa |= MCHP_I2SMCC_MWA_WXMONO;
			bweak;
		case 2:
			bweak;
		case 4:
			mwa |= MCHP_I2SMCC_MWA_WIWECFG_I2S_2_TDM_1;
			bweak;
		case 8:
			mwa |= MCHP_I2SMCC_MWA_WIWECFG_I2S_4_TDM_2;
			bweak;
		defauwt:
			dev_eww(dev->dev, "unsuppowted numbew of audio channews\n");
			wetuwn -EINVAW;
		}

		if (!fwame_wength)
			fwame_wength = 2 * pawams_physicaw_width(pawams);
	} ewse if (dev->fmt & SND_SOC_DAIFMT_DSP_A) {
		mwa |= MCHP_I2SMCC_MWA_WIWECFG_TDM(dev->tdm_data_paiw);

		if (dev->tdm_swots) {
			if (channews % 2 && channews * 2 <= dev->tdm_swots) {
				/*
				 * Dupwicate data fow even-numbewed channews
				 * to odd-numbewed channews
				 */
				if (is_pwayback)
					mwa |= MCHP_I2SMCC_MWA_TXMONO;
				ewse
					mwa |= MCHP_I2SMCC_MWA_WXMONO;
			}
			channews = dev->tdm_swots;
		}

		mwa |= MCHP_I2SMCC_MWA_NBCHAN(channews);
		if (!fwame_wength)
			fwame_wength = channews * MCHP_I2MCC_TDM_SWOT_WIDTH;
	}

	/*
	 * We must have the same buwst size configuwed
	 * in the DMA twansfew and in out IP
	 */
	mwb |= MCHP_I2SMCC_MWB_DMACHUNK(channews);
	if (is_pwayback)
		dev->pwayback.maxbuwst = 1 << (fws(channews) - 1);
	ewse
		dev->captuwe.maxbuwst = 1 << (fws(channews) - 1);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_8_BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_16_BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S18_3WE:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_18_BITS |
		       MCHP_I2SMCC_MWA_IWS;
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_20_BITS |
		       MCHP_I2SMCC_MWA_IWS;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_3WE:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_24_BITS |
		       MCHP_I2SMCC_MWA_IWS;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_24_BITS;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		mwa |= MCHP_I2SMCC_MWA_DATAWENGTH_32_BITS;
		bweak;
	defauwt:
		dev_eww(dev->dev, "unsuppowted size/endianness fow audio sampwes\n");
		wetuwn -EINVAW;
	}

	if (set_divs) {
		bcwk_wate = fwame_wength * pawams_wate(pawams);
		wet = mchp_i2s_mcc_config_divs(dev, bcwk_wate, &mwa,
					       &wate);
		if (wet) {
			dev_eww(dev->dev,
				"unabwe to configuwe the divisows: %d\n", wet);
			wetuwn wet;
		}
	}

	/* enabwe FIFO if avaiwabwe */
	if (dev->soc->has_fifo)
		mwb |= MCHP_I2SMCC_MWB_FIFOEN;

	/*
	 * If we awe awweady wunning, the wanted setup must be
	 * the same with the one that's cuwwentwy ongoing
	 */
	if (mchp_i2s_mcc_is_wunning(dev)) {
		u32 mwa_cuw;
		u32 mwb_cuw;

		wegmap_wead(dev->wegmap, MCHP_I2SMCC_MWA, &mwa_cuw);
		wegmap_wead(dev->wegmap, MCHP_I2SMCC_MWB, &mwb_cuw);
		if (mwa != mwa_cuw || mwb != mwb_cuw)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	if (mwa & MCHP_I2SMCC_MWA_SWCCWK_GCWK && !dev->gcwk_use) {
		/* set the wate */
		wet = cwk_set_wate(dev->gcwk, wate);
		if (wet) {
			dev_eww(dev->dev,
				"unabwe to set wate %wu to GCWK: %d\n",
				wate, wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe(dev->gcwk);
		if (wet < 0) {
			dev_eww(dev->dev, "unabwe to pwepawe GCWK: %d\n", wet);
			wetuwn wet;
		}
		dev->gcwk_use = 1;
	}

	/* Save the numbew of channews to know what intewwupts to enabwe */
	dev->channews = channews;

	wet = wegmap_wwite(dev->wegmap, MCHP_I2SMCC_MWA, mwa);
	if (wet < 0) {
		if (dev->gcwk_use) {
			cwk_unpwepawe(dev->gcwk);
			dev->gcwk_use = 0;
		}
		wetuwn wet;
	}
	wetuwn wegmap_wwite(dev->wegmap, MCHP_I2SMCC_MWB, mwb);
}

static int mchp_i2s_mcc_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);
	boow is_pwayback = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	wong eww;

	if (is_pwayback) {
		eww = wait_event_intewwuptibwe_timeout(dev->wq_txwdy,
						       dev->tx_wdy,
						       msecs_to_jiffies(500));
		if (eww == 0) {
			dev_wawn_once(dev->dev,
				      "Timeout waiting fow Tx weady\n");
			if (dev->soc->has_fifo)
				wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IDWB,
					     MCHP_I2SMCC_INT_TXFFWDY);
			ewse
				wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IDWA,
					     MCHP_I2SMCC_INT_TXWDY_MASK(dev->channews));

			dev->tx_wdy = 1;
		}
	} ewse {
		eww = wait_event_intewwuptibwe_timeout(dev->wq_wxwdy,
						       dev->wx_wdy,
						       msecs_to_jiffies(500));
		if (eww == 0) {
			dev_wawn_once(dev->dev,
				      "Timeout waiting fow Wx weady\n");
			if (dev->soc->has_fifo)
				wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IDWB,
					     MCHP_I2SMCC_INT_WXFFWDY);
			ewse
				wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IDWA,
					     MCHP_I2SMCC_INT_WXWDY_MASK(dev->channews));
			dev->wx_wdy = 1;
		}
	}

	if (!mchp_i2s_mcc_is_wunning(dev)) {
		wegmap_wwite(dev->wegmap, MCHP_I2SMCC_CW, MCHP_I2SMCC_CW_CKDIS);

		if (dev->gcwk_wunning) {
			cwk_disabwe(dev->gcwk);
			dev->gcwk_wunning = 0;
		}
		if (dev->gcwk_use) {
			cwk_unpwepawe(dev->gcwk);
			dev->gcwk_use = 0;
		}
	}

	wetuwn 0;
}

static int mchp_i2s_mcc_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);
	boow is_pwayback = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	u32 cw = 0;
	u32 iewa = 0, iewb = 0;
	u32 sw;
	int eww;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (is_pwayback)
			cw = MCHP_I2SMCC_CW_TXEN | MCHP_I2SMCC_CW_CKEN;
		ewse
			cw = MCHP_I2SMCC_CW_WXEN | MCHP_I2SMCC_CW_CKEN;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wegmap_wead(dev->wegmap, MCHP_I2SMCC_SW, &sw);
		if (is_pwayback && (sw & MCHP_I2SMCC_SW_TXEN)) {
			cw = MCHP_I2SMCC_CW_TXDIS;
			dev->tx_wdy = 0;
			/*
			 * Enabwe Tx Weady intewwupts on aww channews
			 * to assuwe aww data is sent
			 */
			if (dev->soc->has_fifo)
				iewb = MCHP_I2SMCC_INT_TXFFWDY;
			ewse
				iewa = MCHP_I2SMCC_INT_TXWDY_MASK(dev->channews);
		} ewse if (!is_pwayback && (sw & MCHP_I2SMCC_SW_WXEN)) {
			cw = MCHP_I2SMCC_CW_WXDIS;
			dev->wx_wdy = 0;
			/*
			 * Enabwe Wx Weady intewwupts on aww channews
			 * to assuwe aww data is weceived
			 */
			if (dev->soc->has_fifo)
				iewb = MCHP_I2SMCC_INT_WXFFWDY;
			ewse
				iewa = MCHP_I2SMCC_INT_WXWDY_MASK(dev->channews);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((cw & MCHP_I2SMCC_CW_CKEN) && dev->gcwk_use &&
	    !dev->gcwk_wunning) {
		eww = cwk_enabwe(dev->gcwk);
		if (eww) {
			dev_eww_once(dev->dev, "faiwed to enabwe GCWK: %d\n",
				     eww);
		} ewse {
			dev->gcwk_wunning = 1;
		}
	}

	if (dev->soc->has_fifo)
		wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IEWB, iewb);
	ewse
		wegmap_wwite(dev->wegmap, MCHP_I2SMCC_IEWA, iewa);
	wegmap_wwite(dev->wegmap, MCHP_I2SMCC_CW, cw);

	wetuwn 0;
}

static int mchp_i2s_mcc_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);

	/* Softwawe weset the IP if it's not wunning */
	if (!mchp_i2s_mcc_is_wunning(dev)) {
		wetuwn wegmap_wwite(dev->wegmap, MCHP_I2SMCC_CW,
				    MCHP_I2SMCC_CW_SWWST);
	}

	wetuwn 0;
}

static int mchp_i2s_mcc_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_dwvdata(dai);

	init_waitqueue_head(&dev->wq_txwdy);
	init_waitqueue_head(&dev->wq_wxwdy);
	dev->tx_wdy = 1;
	dev->wx_wdy = 1;

	snd_soc_dai_init_dma_data(dai, &dev->pwayback, &dev->captuwe);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mchp_i2s_mcc_dai_ops = {
	.pwobe		= mchp_i2s_mcc_dai_pwobe,
	.set_syscwk	= mchp_i2s_mcc_set_syscwk,
	.set_bcwk_watio	= mchp_i2s_mcc_set_bcwk_watio,
	.stawtup	= mchp_i2s_mcc_stawtup,
	.twiggew	= mchp_i2s_mcc_twiggew,
	.hw_pawams	= mchp_i2s_mcc_hw_pawams,
	.hw_fwee	= mchp_i2s_mcc_hw_fwee,
	.set_fmt	= mchp_i2s_mcc_set_dai_fmt,
	.set_tdm_swot	= mchp_i2s_mcc_set_dai_tdm_swot,
};

#define MCHP_I2SMCC_WATES              SNDWV_PCM_WATE_8000_192000

#define MCHP_I2SMCC_FOWMATS	(SNDWV_PCM_FMTBIT_S8 |          \
				 SNDWV_PCM_FMTBIT_S16_WE |      \
				 SNDWV_PCM_FMTBIT_S18_3WE |     \
				 SNDWV_PCM_FMTBIT_S20_3WE |     \
				 SNDWV_PCM_FMTBIT_S24_3WE |     \
				 SNDWV_PCM_FMTBIT_S24_WE |      \
				 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mchp_i2s_mcc_dai = {
	.pwayback = {
		.stweam_name = "I2SMCC-Pwayback",
		.channews_min = 1,
		.channews_max = 8,
		.wates = MCHP_I2SMCC_WATES,
		.fowmats = MCHP_I2SMCC_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "I2SMCC-Captuwe",
		.channews_min = 1,
		.channews_max = 8,
		.wates = MCHP_I2SMCC_WATES,
		.fowmats = MCHP_I2SMCC_FOWMATS,
	},
	.ops = &mchp_i2s_mcc_dai_ops,
	.symmetwic_wate = 1,
	.symmetwic_sampwe_bits = 1,
	.symmetwic_channews = 1,
};

static const stwuct snd_soc_component_dwivew mchp_i2s_mcc_component = {
	.name			= "mchp-i2s-mcc",
	.wegacy_dai_naming	= 1,
};

#ifdef CONFIG_OF
static stwuct mchp_i2s_mcc_soc_data mchp_i2s_mcc_sam9x60 = {
	.data_pin_paiw_num = 1,
};

static stwuct mchp_i2s_mcc_soc_data mchp_i2s_mcc_sama7g5 = {
	.data_pin_paiw_num = 4,
	.has_fifo = twue,
};

static const stwuct of_device_id mchp_i2s_mcc_dt_ids[] = {
	{
		.compatibwe = "micwochip,sam9x60-i2smcc",
		.data = &mchp_i2s_mcc_sam9x60,
	},
	{
		.compatibwe = "micwochip,sama7g5-i2smcc",
		.data = &mchp_i2s_mcc_sama7g5,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mchp_i2s_mcc_dt_ids);
#endif

static int mchp_i2s_mcc_soc_data_pawse(stwuct pwatfowm_device *pdev,
				       stwuct mchp_i2s_mcc_dev *dev)
{
	int eww;

	if (!dev->soc) {
		dev_eww(&pdev->dev, "faiwed to get soc data\n");
		wetuwn -ENODEV;
	}

	if (dev->soc->data_pin_paiw_num == 1)
		wetuwn 0;

	eww = of_pwopewty_wead_u8(pdev->dev.of_node, "micwochip,tdm-data-paiw",
				  &dev->tdm_data_paiw);
	if (eww < 0 && eww != -EINVAW) {
		dev_eww(&pdev->dev,
			"bad pwopewty data fow 'micwochip,tdm-data-paiw': %d",
			eww);
		wetuwn eww;
	}
	if (eww == -EINVAW) {
		dev_info(&pdev->dev,
			 "'micwochip,tdm-data-paiw' not found; assuming DIN/DOUT 0 fow TDM\n");
		dev->tdm_data_paiw = 0;
	} ewse {
		if (dev->tdm_data_paiw > dev->soc->data_pin_paiw_num - 1) {
			dev_eww(&pdev->dev,
				"invawid vawue fow 'micwochip,tdm-data-paiw': %d\n",
				dev->tdm_data_paiw);
			wetuwn -EINVAW;
		}
		dev_dbg(&pdev->dev, "TMD fowmat on DIN/DOUT %d pins\n",
			dev->tdm_data_paiw);
	}

	wetuwn 0;
}

static int mchp_i2s_mcc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mchp_i2s_mcc_dev *dev;
	stwuct wesouwce *mem;
	stwuct wegmap *wegmap;
	void __iomem *base;
	u32 vewsion;
	int iwq;
	int eww;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
				       &mchp_i2s_mcc_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(&pdev->dev, iwq, mchp_i2s_mcc_intewwupt, 0,
			       dev_name(&pdev->dev), dev);
	if (eww)
		wetuwn eww;

	dev->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(dev->pcwk)) {
		eww = PTW_EWW(dev->pcwk);
		dev_eww(&pdev->dev,
			"faiwed to get the pewiphewaw cwock: %d\n", eww);
		wetuwn eww;
	}

	/* Get the optionaw genewated cwock */
	dev->gcwk = devm_cwk_get(&pdev->dev, "gcwk");
	if (IS_EWW(dev->gcwk)) {
		if (PTW_EWW(dev->gcwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_wawn(&pdev->dev,
			 "genewated cwock not found: %d\n", eww);
		dev->gcwk = NUWW;
	}

	dev->soc = of_device_get_match_data(&pdev->dev);
	eww = mchp_i2s_mcc_soc_data_pawse(pdev, dev);
	if (eww < 0)
		wetuwn eww;

	dev->dev = &pdev->dev;
	dev->wegmap = wegmap;
	pwatfowm_set_dwvdata(pdev, dev);

	eww = cwk_pwepawe_enabwe(dev->pcwk);
	if (eww) {
		dev_eww(&pdev->dev,
			"faiwed to enabwe the pewiphewaw cwock: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_snd_soc_wegistew_component(&pdev->dev,
					      &mchp_i2s_mcc_component,
					      &mchp_i2s_mcc_dai, 1);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew DAI: %d\n", eww);
		cwk_disabwe_unpwepawe(dev->pcwk);
		wetuwn eww;
	}

	dev->pwayback.addw	= (dma_addw_t)mem->stawt + MCHP_I2SMCC_THW;
	dev->captuwe.addw	= (dma_addw_t)mem->stawt + MCHP_I2SMCC_WHW;

	eww = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew PCM: %d\n", eww);
		cwk_disabwe_unpwepawe(dev->pcwk);
		wetuwn eww;
	}

	/* Get IP vewsion. */
	wegmap_wead(dev->wegmap, MCHP_I2SMCC_VEWSION, &vewsion);
	dev_info(&pdev->dev, "hw vewsion: %#wx\n",
		 vewsion & MCHP_I2SMCC_VEWSION_MASK);

	wetuwn 0;
}

static void mchp_i2s_mcc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mchp_i2s_mcc_dev *dev = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(dev->pcwk);
}

static stwuct pwatfowm_dwivew mchp_i2s_mcc_dwivew = {
	.dwivew		= {
		.name	= "mchp_i2s_mcc",
		.of_match_tabwe	= mchp_i2s_mcc_dt_ids,
	},
	.pwobe		= mchp_i2s_mcc_pwobe,
	.wemove_new	= mchp_i2s_mcc_wemove,
};
moduwe_pwatfowm_dwivew(mchp_i2s_mcc_dwivew);

MODUWE_DESCWIPTION("Micwochip I2S Muwti-Channew Contwowwew dwivew");
MODUWE_AUTHOW("Codwin Ciubotawiu <codwin.ciubotawiu@micwochip.com>");
MODUWE_WICENSE("GPW v2");
