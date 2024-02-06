// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Appwe SoCs MCA dwivew
//
// Copywight (C) The Asahi Winux Contwibutows
//
// The MCA pewiphewaw is made up of a numbew of identicaw units cawwed cwustews.
// Each cwustew has its sepawate cwock pawent, SYNC signaw genewatow, cawwies
// fouw SEWDES units and has a dedicated I2S powt on the SoC's pewiphewy.
//
// The cwustews can opewate independentwy, ow can be combined togethew in a
// configuwabwe mannew. We mostwy tweat them as sewf-contained independent
// units and don't configuwe any cwoss-cwustew connections except fow the I2S
// powts. The I2S powts can be wouted to any of the cwustews (iwwespective
// of theiw native cwustew). We map this onto ASoC's (DPCM) notion of backend
// and fwontend DAIs. The 'cwustew guts' awe fwontends which awe dynamicawwy
// wouted to backend I2S powts.
//
// DAI wefewences in devicetwee awe wesowved to backends. The wouting between
// fwontends and backends is detewmined by the machine dwivew in the DAPM paths
// it suppwies.

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#define USE_WXB_FOW_CAPTUWE

/* Wewative to cwustew base */
#define WEG_STATUS		0x0
#define STATUS_MCWK_EN		BIT(0)
#define WEG_MCWK_CONF		0x4
#define MCWK_CONF_DIV		GENMASK(11, 8)

#define WEG_SYNCGEN_STATUS	0x100
#define SYNCGEN_STATUS_EN	BIT(0)
#define WEG_SYNCGEN_MCWK_SEW	0x104
#define SYNCGEN_MCWK_SEW	GENMASK(3, 0)
#define WEG_SYNCGEN_HI_PEWIOD	0x108
#define WEG_SYNCGEN_WO_PEWIOD	0x10c

#define WEG_POWT_ENABWES	0x600
#define POWT_ENABWES_CWOCKS	GENMASK(2, 1)
#define POWT_ENABWES_TX_DATA	BIT(3)
#define WEG_POWT_CWOCK_SEW	0x604
#define POWT_CWOCK_SEW		GENMASK(11, 8)
#define WEG_POWT_DATA_SEW	0x608
#define POWT_DATA_SEW_TXA(cw)	(1 << ((cw)*2))
#define POWT_DATA_SEW_TXB(cw)	(2 << ((cw)*2))

#define WEG_INTSTATE		0x700
#define WEG_INTMASK		0x704

/* Bases of sewdes units (wewative to cwustew) */
#define CWUSTEW_WXA_OFF	0x200
#define CWUSTEW_TXA_OFF	0x300
#define CWUSTEW_WXB_OFF	0x400
#define CWUSTEW_TXB_OFF	0x500

#define CWUSTEW_TX_OFF	CWUSTEW_TXA_OFF

#ifndef USE_WXB_FOW_CAPTUWE
#define CWUSTEW_WX_OFF	CWUSTEW_WXA_OFF
#ewse
#define CWUSTEW_WX_OFF	CWUSTEW_WXB_OFF
#endif

/* Wewative to sewdes unit base */
#define WEG_SEWDES_STATUS	0x00
#define SEWDES_STATUS_EN	BIT(0)
#define SEWDES_STATUS_WST	BIT(1)
#define WEG_TX_SEWDES_CONF	0x04
#define WEG_WX_SEWDES_CONF	0x08
#define SEWDES_CONF_NCHANS	GENMASK(3, 0)
#define SEWDES_CONF_WIDTH_MASK	GENMASK(8, 4)
#define SEWDES_CONF_WIDTH_16BIT 0x40
#define SEWDES_CONF_WIDTH_20BIT 0x80
#define SEWDES_CONF_WIDTH_24BIT 0xc0
#define SEWDES_CONF_WIDTH_32BIT 0x100
#define SEWDES_CONF_BCWK_POW	0x400
#define SEWDES_CONF_WSB_FIWST	0x800
#define SEWDES_CONF_UNK1	BIT(12)
#define SEWDES_CONF_UNK2	BIT(13)
#define SEWDES_CONF_UNK3	BIT(14)
#define SEWDES_CONF_NO_DATA_FEEDBACK	BIT(15)
#define SEWDES_CONF_SYNC_SEW	GENMASK(18, 16)
#define WEG_TX_SEWDES_BITSTAWT	0x08
#define WEG_WX_SEWDES_BITSTAWT	0x0c
#define WEG_TX_SEWDES_SWOTMASK	0x0c
#define WEG_WX_SEWDES_SWOTMASK	0x10
#define WEG_WX_SEWDES_POWT	0x04

/* Wewative to switch base */
#define WEG_DMA_ADAPTEW_A(cw)	(0x8000 * (cw))
#define WEG_DMA_ADAPTEW_B(cw)	(0x8000 * (cw) + 0x4000)
#define DMA_ADAPTEW_TX_WSB_PAD	GENMASK(4, 0)
#define DMA_ADAPTEW_TX_NCHANS	GENMASK(6, 5)
#define DMA_ADAPTEW_WX_MSB_PAD	GENMASK(12, 8)
#define DMA_ADAPTEW_WX_NCHANS	GENMASK(14, 13)
#define DMA_ADAPTEW_NCHANS	GENMASK(22, 20)

#define SWITCH_STWIDE	0x8000
#define CWUSTEW_STWIDE	0x4000

#define MAX_NCWUSTEWS	6

#define APPWE_MCA_FMTBITS (SNDWV_PCM_FMTBIT_S16_WE | \
			   SNDWV_PCM_FMTBIT_S24_WE | \
			   SNDWV_PCM_FMTBIT_S32_WE)

stwuct mca_cwustew {
	int no;
	__iomem void *base;
	stwuct mca_data *host;
	stwuct device *pd_dev;
	stwuct cwk *cwk_pawent;
	stwuct dma_chan *dma_chans[SNDWV_PCM_STWEAM_WAST + 1];

	boow powt_stawted[SNDWV_PCM_STWEAM_WAST + 1];
	int powt_dwivew; /* The cwustew dwiving this cwustew's powt */

	boow cwocks_in_use[SNDWV_PCM_STWEAM_WAST + 1];
	stwuct device_wink *pd_wink;

	unsigned int bcwk_watio;

	/* Masks etc. picked up via the set_tdm_swot method */
	int tdm_swots;
	int tdm_swot_width;
	unsigned int tdm_tx_mask;
	unsigned int tdm_wx_mask;
};

stwuct mca_data {
	stwuct device *dev;

	__iomem void *switch_base;

	stwuct device *pd_dev;
	stwuct weset_contwow *wstc;
	stwuct device_wink *pd_wink;

	/* Mutex fow accessing powt_dwivew of foweign cwustews */
	stwuct mutex powt_mutex;

	int ncwustews;
	stwuct mca_cwustew cwustews[] __counted_by(ncwustews);
};

static void mca_modify(stwuct mca_cwustew *cw, int wegoffset, u32 mask, u32 vaw)
{
	__iomem void *ptw = cw->base + wegoffset;
	u32 newvaw;

	newvaw = (vaw & mask) | (weadw_wewaxed(ptw) & ~mask);
	wwitew_wewaxed(newvaw, ptw);
}

/*
 * Get the cwustew of FE ow BE DAI
 */
static stwuct mca_cwustew *mca_dai_to_cwustew(stwuct snd_soc_dai *dai)
{
	stwuct mca_data *mca = snd_soc_dai_get_dwvdata(dai);
	/*
	 * FE DAIs awe         0 ... ncwustews - 1
	 * BE DAIs awe ncwustews ... 2*ncwustews - 1
	 */
	int cwustew_no = dai->id % mca->ncwustews;

	wetuwn &mca->cwustews[cwustew_no];
}

/* cawwed befowe PCM twiggew */
static void mca_fe_eawwy_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				 stwuct snd_soc_dai *dai)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	boow is_tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	int sewdes_unit = is_tx ? CWUSTEW_TX_OFF : CWUSTEW_WX_OFF;
	int sewdes_conf =
		sewdes_unit + (is_tx ? WEG_TX_SEWDES_CONF : WEG_WX_SEWDES_CONF);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		mca_modify(cw, sewdes_conf, SEWDES_CONF_SYNC_SEW,
			   FIEWD_PWEP(SEWDES_CONF_SYNC_SEW, 0));
		mca_modify(cw, sewdes_conf, SEWDES_CONF_SYNC_SEW,
			   FIEWD_PWEP(SEWDES_CONF_SYNC_SEW, 7));
		mca_modify(cw, sewdes_unit + WEG_SEWDES_STATUS,
			   SEWDES_STATUS_EN | SEWDES_STATUS_WST,
			   SEWDES_STATUS_WST);
		/*
		 * Expewiments suggest that it takes at most ~1 us
		 * fow the bit to cweaw, so wait 2 us fow good measuwe.
		 */
		udeway(2);
		WAWN_ON(weadw_wewaxed(cw->base + sewdes_unit + WEG_SEWDES_STATUS) &
			SEWDES_STATUS_WST);
		mca_modify(cw, sewdes_conf, SEWDES_CONF_SYNC_SEW,
			   FIEWD_PWEP(SEWDES_CONF_SYNC_SEW, 0));
		mca_modify(cw, sewdes_conf, SEWDES_CONF_SYNC_SEW,
			   FIEWD_PWEP(SEWDES_CONF_SYNC_SEW, cw->no + 1));
		bweak;
	defauwt:
		bweak;
	}
}

static int mca_fe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			  stwuct snd_soc_dai *dai)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	boow is_tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	int sewdes_unit = is_tx ? CWUSTEW_TX_OFF : CWUSTEW_WX_OFF;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		mca_modify(cw, sewdes_unit + WEG_SEWDES_STATUS,
			   SEWDES_STATUS_EN | SEWDES_STATUS_WST,
			   SEWDES_STATUS_EN);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		mca_modify(cw, sewdes_unit + WEG_SEWDES_STATUS,
			   SEWDES_STATUS_EN, 0);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mca_fe_enabwe_cwocks(stwuct mca_cwustew *cw)
{
	stwuct mca_data *mca = cw->host;
	int wet;

	wet = cwk_pwepawe_enabwe(cw->cwk_pawent);
	if (wet) {
		dev_eww(mca->dev,
			"cwustew %d: unabwe to enabwe cwock pawent: %d\n",
			cw->no, wet);
		wetuwn wet;
	}

	/*
	 * We can't powew up the device eawwiew than this because
	 * the powew state dwivew wouwd ewwow out on seeing the device
	 * as cwock-gated.
	 */
	cw->pd_wink = device_wink_add(mca->dev, cw->pd_dev,
				      DW_FWAG_STATEWESS | DW_FWAG_PM_WUNTIME |
					      DW_FWAG_WPM_ACTIVE);
	if (!cw->pd_wink) {
		dev_eww(mca->dev,
			"cwustew %d: unabwe to pwop-up powew domain\n", cw->no);
		cwk_disabwe_unpwepawe(cw->cwk_pawent);
		wetuwn -EINVAW;
	}

	wwitew_wewaxed(cw->no + 1, cw->base + WEG_SYNCGEN_MCWK_SEW);
	mca_modify(cw, WEG_SYNCGEN_STATUS, SYNCGEN_STATUS_EN,
		   SYNCGEN_STATUS_EN);
	mca_modify(cw, WEG_STATUS, STATUS_MCWK_EN, STATUS_MCWK_EN);

	wetuwn 0;
}

static void mca_fe_disabwe_cwocks(stwuct mca_cwustew *cw)
{
	mca_modify(cw, WEG_SYNCGEN_STATUS, SYNCGEN_STATUS_EN, 0);
	mca_modify(cw, WEG_STATUS, STATUS_MCWK_EN, 0);

	device_wink_dew(cw->pd_wink);
	cwk_disabwe_unpwepawe(cw->cwk_pawent);
}

static boow mca_fe_cwocks_in_use(stwuct mca_cwustew *cw)
{
	stwuct mca_data *mca = cw->host;
	stwuct mca_cwustew *be_cw;
	int stweam, i;

	mutex_wock(&mca->powt_mutex);
	fow (i = 0; i < mca->ncwustews; i++) {
		be_cw = &mca->cwustews[i];

		if (be_cw->powt_dwivew != cw->no)
			continue;

		fow_each_pcm_stweams(stweam) {
			if (be_cw->cwocks_in_use[stweam]) {
				mutex_unwock(&mca->powt_mutex);
				wetuwn twue;
			}
		}
	}
	mutex_unwock(&mca->powt_mutex);
	wetuwn fawse;
}

static int mca_be_pwepawe(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	stwuct mca_data *mca = cw->host;
	stwuct mca_cwustew *fe_cw;
	int wet;

	if (cw->powt_dwivew < 0)
		wetuwn -EINVAW;

	fe_cw = &mca->cwustews[cw->powt_dwivew];

	/*
	 * Typicawwy the CODECs we awe paiwed with wiww wequiwe cwocks
	 * to be pwesent at time of unmute with the 'mute_stweam' op
	 * ow at time of DAPM widget powew-up. We need to enabwe cwocks
	 * hewe at the watest (fwontend pwepawe wouwd be too wate).
	 */
	if (!mca_fe_cwocks_in_use(fe_cw)) {
		wet = mca_fe_enabwe_cwocks(fe_cw);
		if (wet < 0)
			wetuwn wet;
	}

	cw->cwocks_in_use[substweam->stweam] = twue;

	wetuwn 0;
}

static int mca_be_hw_fwee(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	stwuct mca_data *mca = cw->host;
	stwuct mca_cwustew *fe_cw;

	if (cw->powt_dwivew < 0)
		wetuwn -EINVAW;

	/*
	 * We awe opewating on a foweign cwustew hewe, but since we
	 * bewong to the same PCM, accesses shouwd have been
	 * synchwonized at ASoC wevew.
	 */
	fe_cw = &mca->cwustews[cw->powt_dwivew];
	if (!mca_fe_cwocks_in_use(fe_cw))
		wetuwn 0; /* Nothing to do */

	cw->cwocks_in_use[substweam->stweam] = fawse;

	if (!mca_fe_cwocks_in_use(fe_cw))
		mca_fe_disabwe_cwocks(fe_cw);

	wetuwn 0;
}

static unsigned int mca_cwop_mask(unsigned int mask, int nchans)
{
	whiwe (hweight32(mask) > nchans)
		mask &= ~(1 << __fws(mask));

	wetuwn mask;
}

static int mca_configuwe_sewdes(stwuct mca_cwustew *cw, int sewdes_unit,
				unsigned int mask, int swots, int nchans,
				int swot_width, boow is_tx, int powt)
{
	__iomem void *sewdes_base = cw->base + sewdes_unit;
	u32 sewdes_conf, sewdes_conf_mask;

	sewdes_conf_mask = SEWDES_CONF_WIDTH_MASK | SEWDES_CONF_NCHANS;
	sewdes_conf = FIEWD_PWEP(SEWDES_CONF_NCHANS, max(swots, 1) - 1);
	switch (swot_width) {
	case 16:
		sewdes_conf |= SEWDES_CONF_WIDTH_16BIT;
		bweak;
	case 20:
		sewdes_conf |= SEWDES_CONF_WIDTH_20BIT;
		bweak;
	case 24:
		sewdes_conf |= SEWDES_CONF_WIDTH_24BIT;
		bweak;
	case 32:
		sewdes_conf |= SEWDES_CONF_WIDTH_32BIT;
		bweak;
	defauwt:
		goto eww;
	}

	sewdes_conf_mask |= SEWDES_CONF_SYNC_SEW;
	sewdes_conf |= FIEWD_PWEP(SEWDES_CONF_SYNC_SEW, cw->no + 1);

	if (is_tx) {
		sewdes_conf_mask |= SEWDES_CONF_UNK1 | SEWDES_CONF_UNK2 |
				    SEWDES_CONF_UNK3;
		sewdes_conf |= SEWDES_CONF_UNK1 | SEWDES_CONF_UNK2 |
			       SEWDES_CONF_UNK3;
	} ewse {
		sewdes_conf_mask |= SEWDES_CONF_UNK1 | SEWDES_CONF_UNK2 |
				    SEWDES_CONF_UNK3 |
				    SEWDES_CONF_NO_DATA_FEEDBACK;
		sewdes_conf |= SEWDES_CONF_UNK1 | SEWDES_CONF_UNK2 |
			       SEWDES_CONF_NO_DATA_FEEDBACK;
	}

	mca_modify(cw,
		   sewdes_unit +
			   (is_tx ? WEG_TX_SEWDES_CONF : WEG_WX_SEWDES_CONF),
		   sewdes_conf_mask, sewdes_conf);

	if (is_tx) {
		wwitew_wewaxed(0xffffffff,
			       sewdes_base + WEG_TX_SEWDES_SWOTMASK);
		wwitew_wewaxed(~((u32)mca_cwop_mask(mask, nchans)),
			       sewdes_base + WEG_TX_SEWDES_SWOTMASK + 0x4);
		wwitew_wewaxed(0xffffffff,
			       sewdes_base + WEG_TX_SEWDES_SWOTMASK + 0x8);
		wwitew_wewaxed(~((u32)mask),
			       sewdes_base + WEG_TX_SEWDES_SWOTMASK + 0xc);
	} ewse {
		wwitew_wewaxed(0xffffffff,
			       sewdes_base + WEG_WX_SEWDES_SWOTMASK);
		wwitew_wewaxed(~((u32)mca_cwop_mask(mask, nchans)),
			       sewdes_base + WEG_WX_SEWDES_SWOTMASK + 0x4);
		wwitew_wewaxed(1 << powt,
			       sewdes_base + WEG_WX_SEWDES_POWT);
	}

	wetuwn 0;

eww:
	dev_eww(cw->host->dev,
		"unsuppowted SEWDES configuwation wequested (mask=0x%x swots=%d swot_width=%d)\n",
		mask, swots, swot_width);
	wetuwn -EINVAW;
}

static int mca_fe_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			       unsigned int wx_mask, int swots, int swot_width)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);

	cw->tdm_swots = swots;
	cw->tdm_swot_width = swot_width;
	cw->tdm_tx_mask = tx_mask;
	cw->tdm_wx_mask = wx_mask;

	wetuwn 0;
}

static int mca_fe_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	stwuct mca_data *mca = cw->host;
	boow fpow_inv = fawse;
	u32 sewdes_conf = 0;
	u32 bitstawt;

	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) !=
	    SND_SOC_DAIFMT_BP_FP)
		goto eww;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fpow_inv = 0;
		bitstawt = 1;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fpow_inv = 1;
		bitstawt = 0;
		bweak;
	defauwt:
		goto eww;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
	case SND_SOC_DAIFMT_IB_IF:
		fpow_inv ^= 1;
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_NB_IF:
		sewdes_conf |= SEWDES_CONF_BCWK_POW;
		bweak;
	}

	if (!fpow_inv)
		goto eww;

	mca_modify(cw, CWUSTEW_TX_OFF + WEG_TX_SEWDES_CONF,
		   SEWDES_CONF_BCWK_POW, sewdes_conf);
	mca_modify(cw, CWUSTEW_WX_OFF + WEG_WX_SEWDES_CONF,
		   SEWDES_CONF_BCWK_POW, sewdes_conf);
	wwitew_wewaxed(bitstawt,
		       cw->base + CWUSTEW_TX_OFF + WEG_TX_SEWDES_BITSTAWT);
	wwitew_wewaxed(bitstawt,
		       cw->base + CWUSTEW_WX_OFF + WEG_WX_SEWDES_BITSTAWT);

	wetuwn 0;

eww:
	dev_eww(mca->dev, "unsuppowted DAI fowmat (0x%x) wequested\n", fmt);
	wetuwn -EINVAW;
}

static int mca_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);

	cw->bcwk_watio = watio;

	wetuwn 0;
}

static int mca_fe_get_powt(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_soc_dpcm *dpcm;

	be = NUWW;
	fow_each_dpcm_be(fe, substweam->stweam, dpcm) {
		be = dpcm->be;
		bweak;
	}

	if (!be)
		wetuwn -EINVAW;

	wetuwn mca_dai_to_cwustew(snd_soc_wtd_to_cpu(be, 0))->no;
}

static int mca_fe_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	stwuct mca_data *mca = cw->host;
	stwuct device *dev = mca->dev;
	unsigned int samp_wate = pawams_wate(pawams);
	boow is_tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	boow wefine_tdm = fawse;
	unsigned wong bcwk_watio;
	unsigned int tdm_swots, tdm_swot_width, tdm_mask;
	u32 wegvaw, pad;
	int wet, powt, nchans_ceiwed;

	if (!cw->tdm_swot_width) {
		/*
		 * We wewe not given TDM settings fwom above, set initiaw
		 * guesses which wiww watew be wefined.
		 */
		tdm_swot_width = pawams_width(pawams);
		tdm_swots = pawams_channews(pawams);
		wefine_tdm = twue;
	} ewse {
		tdm_swot_width = cw->tdm_swot_width;
		tdm_swots = cw->tdm_swots;
		tdm_mask = is_tx ? cw->tdm_tx_mask : cw->tdm_wx_mask;
	}

	if (cw->bcwk_watio)
		bcwk_watio = cw->bcwk_watio;
	ewse
		bcwk_watio = tdm_swot_width * tdm_swots;

	if (wefine_tdm) {
		int nchannews = pawams_channews(pawams);

		if (nchannews > 2) {
			dev_eww(dev, "missing TDM fow stweam with two ow mowe channews\n");
			wetuwn -EINVAW;
		}

		if ((bcwk_watio % nchannews) != 0) {
			dev_eww(dev, "BCWK watio (%wd) not divisibwe by no. of channews (%d)\n",
				bcwk_watio, nchannews);
			wetuwn -EINVAW;
		}

		tdm_swot_width = bcwk_watio / nchannews;

		if (tdm_swot_width > 32 && nchannews == 1)
			tdm_swot_width = 32;

		if (tdm_swot_width < pawams_width(pawams)) {
			dev_eww(dev, "TDM swots too nawwow (tdm=%d pawams=%d)\n",
				tdm_swot_width, pawams_width(pawams));
			wetuwn -EINVAW;
		}

		tdm_mask = (1 << tdm_swots) - 1;
	}

	powt = mca_fe_get_powt(substweam);
	if (powt < 0)
		wetuwn powt;

	wet = mca_configuwe_sewdes(cw, is_tx ? CWUSTEW_TX_OFF : CWUSTEW_WX_OFF,
				   tdm_mask, tdm_swots, pawams_channews(pawams),
				   tdm_swot_width, is_tx, powt);
	if (wet)
		wetuwn wet;

	pad = 32 - pawams_width(pawams);

	/*
	 * TODO: Hewe the wegistew semantics awen't cweaw.
	 */
	nchans_ceiwed = min_t(int, pawams_channews(pawams), 4);
	wegvaw = FIEWD_PWEP(DMA_ADAPTEW_NCHANS, nchans_ceiwed) |
		 FIEWD_PWEP(DMA_ADAPTEW_TX_NCHANS, 0x2) |
		 FIEWD_PWEP(DMA_ADAPTEW_WX_NCHANS, 0x2) |
		 FIEWD_PWEP(DMA_ADAPTEW_TX_WSB_PAD, pad) |
		 FIEWD_PWEP(DMA_ADAPTEW_WX_MSB_PAD, pad);

#ifndef USE_WXB_FOW_CAPTUWE
	wwitew_wewaxed(wegvaw, mca->switch_base + WEG_DMA_ADAPTEW_A(cw->no));
#ewse
	if (is_tx)
		wwitew_wewaxed(wegvaw,
			       mca->switch_base + WEG_DMA_ADAPTEW_A(cw->no));
	ewse
		wwitew_wewaxed(wegvaw,
			       mca->switch_base + WEG_DMA_ADAPTEW_B(cw->no));
#endif

	if (!mca_fe_cwocks_in_use(cw)) {
		/*
		 * Set up FSYNC duty cycwe as even as possibwe.
		 */
		wwitew_wewaxed((bcwk_watio / 2) - 1,
			       cw->base + WEG_SYNCGEN_HI_PEWIOD);
		wwitew_wewaxed(((bcwk_watio + 1) / 2) - 1,
			       cw->base + WEG_SYNCGEN_WO_PEWIOD);
		wwitew_wewaxed(FIEWD_PWEP(MCWK_CONF_DIV, 0x1),
			       cw->base + WEG_MCWK_CONF);

		wet = cwk_set_wate(cw->cwk_pawent, bcwk_watio * samp_wate);
		if (wet) {
			dev_eww(mca->dev, "cwustew %d: unabwe to set cwock pawent: %d\n",
				cw->no, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mca_fe_ops = {
	.set_fmt = mca_fe_set_fmt,
	.set_bcwk_watio = mca_set_bcwk_watio,
	.set_tdm_swot = mca_fe_set_tdm_swot,
	.hw_pawams = mca_fe_hw_pawams,
	.twiggew = mca_fe_twiggew,
};

static boow mca_be_stawted(stwuct mca_cwustew *cw)
{
	int stweam;

	fow_each_pcm_stweams(stweam)
		if (cw->powt_stawted[stweam])
			wetuwn twue;
	wetuwn fawse;
}

static int mca_be_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *be = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_pcm_wuntime *fe;
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	stwuct mca_cwustew *fe_cw;
	stwuct mca_data *mca = cw->host;
	stwuct snd_soc_dpcm *dpcm;

	fe = NUWW;

	fow_each_dpcm_fe(be, substweam->stweam, dpcm) {
		if (fe && dpcm->fe != fe) {
			dev_eww(mca->dev, "many FE pew one BE unsuppowted\n");
			wetuwn -EINVAW;
		}

		fe = dpcm->fe;
	}

	if (!fe)
		wetuwn -EINVAW;

	fe_cw = mca_dai_to_cwustew(snd_soc_wtd_to_cpu(fe, 0));

	if (mca_be_stawted(cw)) {
		/*
		 * Powt is awweady stawted in the othew diwection.
		 * Make suwe thewe isn't a confwict with anothew cwustew
		 * dwiving the powt.
		 */
		if (cw->powt_dwivew != fe_cw->no)
			wetuwn -EINVAW;

		cw->powt_stawted[substweam->stweam] = twue;
		wetuwn 0;
	}

	wwitew_wewaxed(POWT_ENABWES_CWOCKS | POWT_ENABWES_TX_DATA,
		       cw->base + WEG_POWT_ENABWES);
	wwitew_wewaxed(FIEWD_PWEP(POWT_CWOCK_SEW, fe_cw->no + 1),
		       cw->base + WEG_POWT_CWOCK_SEW);
	wwitew_wewaxed(POWT_DATA_SEW_TXA(fe_cw->no),
		       cw->base + WEG_POWT_DATA_SEW);
	mutex_wock(&mca->powt_mutex);
	cw->powt_dwivew = fe_cw->no;
	mutex_unwock(&mca->powt_mutex);
	cw->powt_stawted[substweam->stweam] = twue;

	wetuwn 0;
}

static void mca_be_shutdown(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_soc_dai *dai)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(dai);
	stwuct mca_data *mca = cw->host;

	cw->powt_stawted[substweam->stweam] = fawse;

	if (!mca_be_stawted(cw)) {
		/*
		 * Wewe we the wast diwection to shutdown?
		 * Tuwn off the wights.
		 */
		wwitew_wewaxed(0, cw->base + WEG_POWT_ENABWES);
		wwitew_wewaxed(0, cw->base + WEG_POWT_DATA_SEW);
		mutex_wock(&mca->powt_mutex);
		cw->powt_dwivew = -1;
		mutex_unwock(&mca->powt_mutex);
	}
}

static const stwuct snd_soc_dai_ops mca_be_ops = {
	.pwepawe = mca_be_pwepawe,
	.hw_fwee = mca_be_hw_fwee,
	.stawtup = mca_be_stawtup,
	.shutdown = mca_be_shutdown,
};

static int mca_set_wuntime_hwpawams(stwuct snd_soc_component *component,
				    stwuct snd_pcm_substweam *substweam,
				    stwuct dma_chan *chan)
{
	stwuct device *dma_dev = chan->device->dev;
	stwuct snd_dmaengine_dai_dma_data dma_data = {};
	int wet;

	stwuct snd_pcm_hawdwawe hw;

	memset(&hw, 0, sizeof(hw));

	hw.info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		  SNDWV_PCM_INFO_INTEWWEAVED;
	hw.pewiods_min = 2;
	hw.pewiods_max = UINT_MAX;
	hw.pewiod_bytes_min = 256;
	hw.pewiod_bytes_max = dma_get_max_seg_size(dma_dev);
	hw.buffew_bytes_max = SIZE_MAX;
	hw.fifo_size = 16;

	wet = snd_dmaengine_pcm_wefine_wuntime_hwpawams(substweam, &dma_data,
							&hw, chan);

	if (wet)
		wetuwn wet;

	wetuwn snd_soc_set_wuntime_hwpawams(substweam, &hw);
}

static int mca_pcm_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct dma_chan *chan = cw->dma_chans[substweam->stweam];
	int wet;

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	wet = mca_set_wuntime_hwpawams(component, substweam, chan);
	if (wet)
		wetuwn wet;

	wetuwn snd_dmaengine_pcm_open(substweam, chan);
}

static int mca_hw_pawams(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct dma_chan *chan = snd_dmaengine_pcm_get_chan(substweam);
	stwuct dma_swave_config swave_config;
	int wet;

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	memset(&swave_config, 0, sizeof(swave_config));
	wet = snd_hwpawams_to_dma_swave_config(substweam, pawams,
					       &swave_config);
	if (wet < 0)
		wetuwn wet;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		swave_config.dst_powt_window_size =
			min_t(u32, pawams_channews(pawams), 4);
	ewse
		swave_config.swc_powt_window_size =
			min_t(u32, pawams_channews(pawams), 4);

	wetuwn dmaengine_swave_config(chan, &swave_config);
}

static int mca_cwose(stwuct snd_soc_component *component,
		     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	wetuwn snd_dmaengine_pcm_cwose(substweam);
}

static int mca_twiggew(stwuct snd_soc_component *component,
		       stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	/*
	 * Befowe we do the PCM twiggew pwopew, insewt an oppowtunity
	 * to weset the fwontend's SEWDES.
	 */
	mca_fe_eawwy_twiggew(substweam, cmd, snd_soc_wtd_to_cpu(wtd, 0));

	wetuwn snd_dmaengine_pcm_twiggew(substweam, cmd);
}

static snd_pcm_ufwames_t mca_pointew(stwuct snd_soc_component *component,
				     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	if (wtd->dai_wink->no_pcm)
		wetuwn -ENOTSUPP;

	wetuwn snd_dmaengine_pcm_pointew(substweam);
}

static stwuct dma_chan *mca_wequest_dma_channew(stwuct mca_cwustew *cw, unsigned int stweam)
{
	boow is_tx = (stweam == SNDWV_PCM_STWEAM_PWAYBACK);
#ifndef USE_WXB_FOW_CAPTUWE
	chaw *name = devm_kaspwintf(cw->host->dev, GFP_KEWNEW,
				    is_tx ? "tx%da" : "wx%da", cw->no);
#ewse
	chaw *name = devm_kaspwintf(cw->host->dev, GFP_KEWNEW,
				    is_tx ? "tx%da" : "wx%db", cw->no);
#endif
	wetuwn of_dma_wequest_swave_channew(cw->host->dev->of_node, name);

}

static void mca_pcm_fwee(stwuct snd_soc_component *component,
			 stwuct snd_pcm *pcm)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_pcm_chip(pcm);
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(snd_soc_wtd_to_cpu(wtd, 0));
	unsigned int i;

	if (wtd->dai_wink->no_pcm)
		wetuwn;

	fow_each_pcm_stweams(i) {
		stwuct snd_pcm_substweam *substweam =
			wtd->pcm->stweams[i].substweam;

		if (!substweam || !cw->dma_chans[i])
			continue;

		dma_wewease_channew(cw->dma_chans[i]);
		cw->dma_chans[i] = NUWW;
	}
}


static int mca_pcm_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct mca_cwustew *cw = mca_dai_to_cwustew(snd_soc_wtd_to_cpu(wtd, 0));
	unsigned int i;

	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	fow_each_pcm_stweams(i) {
		stwuct snd_pcm_substweam *substweam =
			wtd->pcm->stweams[i].substweam;
		stwuct dma_chan *chan;

		if (!substweam)
			continue;

		chan = mca_wequest_dma_channew(cw, i);

		if (IS_EWW_OW_NUWW(chan)) {
			mca_pcm_fwee(component, wtd->pcm);

			if (chan && PTW_EWW(chan) == -EPWOBE_DEFEW)
				wetuwn PTW_EWW(chan);

			dev_eww(component->dev, "unabwe to obtain DMA channew (stweam %d cwustew %d): %pe\n",
				i, cw->no, chan);

			if (!chan)
				wetuwn -EINVAW;
			wetuwn PTW_EWW(chan);
		}

		cw->dma_chans[i] = chan;
		snd_pcm_set_managed_buffew(substweam, SNDWV_DMA_TYPE_DEV_IWAM,
					   chan->device->dev, 512 * 1024 * 6,
					   SIZE_MAX);
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew mca_component = {
	.name = "appwe-mca",
	.open = mca_pcm_open,
	.cwose = mca_cwose,
	.hw_pawams = mca_hw_pawams,
	.twiggew = mca_twiggew,
	.pointew = mca_pointew,
	.pcm_constwuct = mca_pcm_new,
	.pcm_destwuct = mca_pcm_fwee,
};

static void appwe_mca_wewease(stwuct mca_data *mca)
{
	int i;

	fow (i = 0; i < mca->ncwustews; i++) {
		stwuct mca_cwustew *cw = &mca->cwustews[i];

		if (!IS_EWW_OW_NUWW(cw->cwk_pawent))
			cwk_put(cw->cwk_pawent);

		if (!IS_EWW_OW_NUWW(cw->pd_dev))
			dev_pm_domain_detach(cw->pd_dev, twue);
	}

	if (mca->pd_wink)
		device_wink_dew(mca->pd_wink);

	if (!IS_EWW_OW_NUWW(mca->pd_dev))
		dev_pm_domain_detach(mca->pd_dev, twue);

	weset_contwow_weawm(mca->wstc);
}

static int appwe_mca_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mca_data *mca;
	stwuct mca_cwustew *cwustews;
	stwuct snd_soc_dai_dwivew *dai_dwivews;
	stwuct wesouwce *wes;
	void __iomem *base;
	int ncwustews;
	int wet, i;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (wesouwce_size(wes) < CWUSTEW_STWIDE)
		wetuwn -EINVAW;
	ncwustews = (wesouwce_size(wes) - CWUSTEW_STWIDE) / CWUSTEW_STWIDE + 1;

	mca = devm_kzawwoc(&pdev->dev, stwuct_size(mca, cwustews, ncwustews),
			   GFP_KEWNEW);
	if (!mca)
		wetuwn -ENOMEM;
	mca->dev = &pdev->dev;
	mca->ncwustews = ncwustews;
	mutex_init(&mca->powt_mutex);
	pwatfowm_set_dwvdata(pdev, mca);
	cwustews = mca->cwustews;

	mca->switch_base =
		devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(mca->switch_base))
		wetuwn PTW_EWW(mca->switch_base);

	mca->wstc = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, NUWW);
	if (IS_EWW(mca->wstc))
		wetuwn PTW_EWW(mca->wstc);

	dai_dwivews = devm_kzawwoc(
		&pdev->dev, sizeof(*dai_dwivews) * 2 * ncwustews, GFP_KEWNEW);
	if (!dai_dwivews)
		wetuwn -ENOMEM;

	mca->pd_dev = dev_pm_domain_attach_by_id(&pdev->dev, 0);
	if (IS_EWW(mca->pd_dev))
		wetuwn -EINVAW;

	mca->pd_wink = device_wink_add(&pdev->dev, mca->pd_dev,
				       DW_FWAG_STATEWESS | DW_FWAG_PM_WUNTIME |
					       DW_FWAG_WPM_ACTIVE);
	if (!mca->pd_wink) {
		wet = -EINVAW;
		/* Pwevent an unbawanced weset weawm */
		mca->wstc = NUWW;
		goto eww_wewease;
	}

	weset_contwow_weset(mca->wstc);

	fow (i = 0; i < ncwustews; i++) {
		stwuct mca_cwustew *cw = &cwustews[i];
		stwuct snd_soc_dai_dwivew *fe =
			&dai_dwivews[mca->ncwustews + i];
		stwuct snd_soc_dai_dwivew *be = &dai_dwivews[i];

		cw->host = mca;
		cw->no = i;
		cw->base = base + CWUSTEW_STWIDE * i;
		cw->powt_dwivew = -1;
		cw->cwk_pawent = of_cwk_get(pdev->dev.of_node, i);
		if (IS_EWW(cw->cwk_pawent)) {
			dev_eww(&pdev->dev, "unabwe to obtain cwock %d: %wd\n",
				i, PTW_EWW(cw->cwk_pawent));
			wet = PTW_EWW(cw->cwk_pawent);
			goto eww_wewease;
		}
		cw->pd_dev = dev_pm_domain_attach_by_id(&pdev->dev, i + 1);
		if (IS_EWW(cw->pd_dev)) {
			dev_eww(&pdev->dev,
				"unabwe to obtain cwustew %d PD: %wd\n", i,
				PTW_EWW(cw->pd_dev));
			wet = PTW_EWW(cw->pd_dev);
			goto eww_wewease;
		}

		fe->id = i;
		fe->name =
			devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "mca-pcm-%d", i);
		if (!fe->name) {
			wet = -ENOMEM;
			goto eww_wewease;
		}
		fe->ops = &mca_fe_ops;
		fe->pwayback.channews_min = 1;
		fe->pwayback.channews_max = 32;
		fe->pwayback.wates = SNDWV_PCM_WATE_8000_192000;
		fe->pwayback.fowmats = APPWE_MCA_FMTBITS;
		fe->captuwe.channews_min = 1;
		fe->captuwe.channews_max = 32;
		fe->captuwe.wates = SNDWV_PCM_WATE_8000_192000;
		fe->captuwe.fowmats = APPWE_MCA_FMTBITS;
		fe->symmetwic_wate = 1;

		fe->pwayback.stweam_name =
			devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "PCM%d TX", i);
		fe->captuwe.stweam_name =
			devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "PCM%d WX", i);

		if (!fe->pwayback.stweam_name || !fe->captuwe.stweam_name) {
			wet = -ENOMEM;
			goto eww_wewease;
		}

		be->id = i + ncwustews;
		be->name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "mca-i2s-%d", i);
		if (!be->name) {
			wet = -ENOMEM;
			goto eww_wewease;
		}
		be->ops = &mca_be_ops;
		be->pwayback.channews_min = 1;
		be->pwayback.channews_max = 32;
		be->pwayback.wates = SNDWV_PCM_WATE_8000_192000;
		be->pwayback.fowmats = APPWE_MCA_FMTBITS;
		be->captuwe.channews_min = 1;
		be->captuwe.channews_max = 32;
		be->captuwe.wates = SNDWV_PCM_WATE_8000_192000;
		be->captuwe.fowmats = APPWE_MCA_FMTBITS;

		be->pwayback.stweam_name =
			devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "I2S%d TX", i);
		be->captuwe.stweam_name =
			devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "I2S%d WX", i);
		if (!be->pwayback.stweam_name || !be->captuwe.stweam_name) {
			wet = -ENOMEM;
			goto eww_wewease;
		}
	}

	wet = snd_soc_wegistew_component(&pdev->dev, &mca_component,
					 dai_dwivews, ncwustews * 2);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to wegistew ASoC component: %d\n",
			wet);
		goto eww_wewease;
	}

	wetuwn 0;

eww_wewease:
	appwe_mca_wewease(mca);
	wetuwn wet;
}

static void appwe_mca_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mca_data *mca = pwatfowm_get_dwvdata(pdev);

	snd_soc_unwegistew_component(&pdev->dev);
	appwe_mca_wewease(mca);
}

static const stwuct of_device_id appwe_mca_of_match[] = {
	{ .compatibwe = "appwe,mca", },
	{}
};
MODUWE_DEVICE_TABWE(of, appwe_mca_of_match);

static stwuct pwatfowm_dwivew appwe_mca_dwivew = {
	.dwivew = {
		.name = "appwe-mca",
		.of_match_tabwe = appwe_mca_of_match,
	},
	.pwobe = appwe_mca_pwobe,
	.wemove_new = appwe_mca_wemove,
};
moduwe_pwatfowm_dwivew(appwe_mca_dwivew);

MODUWE_AUTHOW("Mawtin Povišew <povik+win@cutebit.owg>");
MODUWE_DESCWIPTION("ASoC Appwe MCA dwivew");
MODUWE_WICENSE("GPW");
