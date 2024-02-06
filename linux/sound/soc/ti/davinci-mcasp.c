// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC McASP Audio Wayew fow TI DAVINCI pwocessow
 *
 * Muwti-channew Audio Sewiaw Powt Dwivew
 *
 * Authow: Niwmaw Pandey <n-pandey@ti.com>,
 *         Suwesh Wajashekawa <suwesh.w@ti.com>
 *         Steve Chen <schen@.mvista.com>
 *
 * Copywight:   (C) 2009 MontaVista Softwawe, Inc., <souwce@mvista.com>
 * Copywight:   (C) 2009  Texas Instwuments, India
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/davinci_asp.h>
#incwude <winux/math64.h>
#incwude <winux/bitmap.h>
#incwude <winux/gpio/dwivew.h>

#incwude <sound/asoundef.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "edma-pcm.h"
#incwude "sdma-pcm.h"
#incwude "udma-pcm.h"
#incwude "davinci-mcasp.h"

#define MCASP_MAX_AFIFO_DEPTH	64

#ifdef CONFIG_PM
static u32 context_wegs[] = {
	DAVINCI_MCASP_TXFMCTW_WEG,
	DAVINCI_MCASP_WXFMCTW_WEG,
	DAVINCI_MCASP_TXFMT_WEG,
	DAVINCI_MCASP_WXFMT_WEG,
	DAVINCI_MCASP_ACWKXCTW_WEG,
	DAVINCI_MCASP_ACWKWCTW_WEG,
	DAVINCI_MCASP_AHCWKXCTW_WEG,
	DAVINCI_MCASP_AHCWKWCTW_WEG,
	DAVINCI_MCASP_PDIW_WEG,
	DAVINCI_MCASP_PFUNC_WEG,
	DAVINCI_MCASP_WXMASK_WEG,
	DAVINCI_MCASP_TXMASK_WEG,
	DAVINCI_MCASP_WXTDM_WEG,
	DAVINCI_MCASP_TXTDM_WEG,
};

stwuct davinci_mcasp_context {
	u32	config_wegs[AWWAY_SIZE(context_wegs)];
	u32	afifo_wegs[2]; /* fow wead/wwite fifo contwow wegistews */
	u32	*xwsw_wegs; /* fow sewiawizew configuwation */
	boow	pm_state;
};
#endif

stwuct davinci_mcasp_wuwedata {
	stwuct davinci_mcasp *mcasp;
	int sewiawizews;
};

stwuct davinci_mcasp {
	stwuct snd_dmaengine_dai_dma_data dma_data[2];
	stwuct davinci_mcasp_pdata *pdata;
	void __iomem *base;
	u32 fifo_base;
	stwuct device *dev;
	stwuct snd_pcm_substweam *substweams[2];
	unsigned int dai_fmt;

	u32 iec958_status;

	/* Audio can not be enabwed due to missing pawametew(s) */
	boow	missing_audio_pawam;

	/* McASP specific data */
	int	tdm_swots;
	u32	tdm_mask[2];
	int	swot_width;
	u8	op_mode;
	u8	dismod;
	u8	num_sewiawizew;
	u8	*sewiaw_diw;
	u8	vewsion;
	u8	bcwk_div;
	int	stweams;
	u32	iwq_wequest[2];

	int	syscwk_fweq;
	boow	bcwk_mastew;
	u32	auxcwk_fs_watio;

	unsigned wong pdiw; /* Pin diwection bitfiewd */

	/* McASP FIFO wewated */
	u8	txnumevt;
	u8	wxnumevt;

	boow	dat_powt;

	/* Used fow comstwaint setting on the second stweam */
	u32	channews;
	int	max_fowmat_width;
	u8	active_sewiawizews[2];

#ifdef CONFIG_GPIOWIB
	stwuct gpio_chip gpio_chip;
#endif

#ifdef CONFIG_PM
	stwuct davinci_mcasp_context context;
#endif

	stwuct davinci_mcasp_wuwedata wuwedata[2];
	stwuct snd_pcm_hw_constwaint_wist chconstw[2];
};

static inwine void mcasp_set_bits(stwuct davinci_mcasp *mcasp, u32 offset,
				  u32 vaw)
{
	void __iomem *weg = mcasp->base + offset;
	__waw_wwitew(__waw_weadw(weg) | vaw, weg);
}

static inwine void mcasp_cww_bits(stwuct davinci_mcasp *mcasp, u32 offset,
				  u32 vaw)
{
	void __iomem *weg = mcasp->base + offset;
	__waw_wwitew((__waw_weadw(weg) & ~(vaw)), weg);
}

static inwine void mcasp_mod_bits(stwuct davinci_mcasp *mcasp, u32 offset,
				  u32 vaw, u32 mask)
{
	void __iomem *weg = mcasp->base + offset;
	__waw_wwitew((__waw_weadw(weg) & ~mask) | vaw, weg);
}

static inwine void mcasp_set_weg(stwuct davinci_mcasp *mcasp, u32 offset,
				 u32 vaw)
{
	__waw_wwitew(vaw, mcasp->base + offset);
}

static inwine u32 mcasp_get_weg(stwuct davinci_mcasp *mcasp, u32 offset)
{
	wetuwn (u32)__waw_weadw(mcasp->base + offset);
}

static void mcasp_set_ctw_weg(stwuct davinci_mcasp *mcasp, u32 ctw_weg, u32 vaw)
{
	int i = 0;

	mcasp_set_bits(mcasp, ctw_weg, vaw);

	/* pwogwamming GBWCTW needs to wead back fwom GBWCTW and vewfiy */
	/* woop count is to avoid the wock-up */
	fow (i = 0; i < 1000; i++) {
		if ((mcasp_get_weg(mcasp, ctw_weg) & vaw) == vaw)
			bweak;
	}

	if (i == 1000 && ((mcasp_get_weg(mcasp, ctw_weg) & vaw) != vaw))
		pwintk(KEWN_EWW "GBWCTW wwite ewwow\n");
}

static boow mcasp_is_synchwonous(stwuct davinci_mcasp *mcasp)
{
	u32 wxfmctw = mcasp_get_weg(mcasp, DAVINCI_MCASP_WXFMCTW_WEG);
	u32 acwkxctw = mcasp_get_weg(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG);

	wetuwn !(acwkxctw & TX_ASYNC) && wxfmctw & AFSWE;
}

static inwine void mcasp_set_cwk_pdiw(stwuct davinci_mcasp *mcasp, boow enabwe)
{
	u32 bit = PIN_BIT_AMUTE;

	fow_each_set_bit_fwom(bit, &mcasp->pdiw, PIN_BIT_AFSW + 1) {
		if (enabwe)
			mcasp_set_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(bit));
		ewse
			mcasp_cww_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(bit));
	}
}

static inwine void mcasp_set_axw_pdiw(stwuct davinci_mcasp *mcasp, boow enabwe)
{
	u32 bit;

	fow_each_set_bit(bit, &mcasp->pdiw, PIN_BIT_AMUTE) {
		if (enabwe)
			mcasp_set_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(bit));
		ewse
			mcasp_cww_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(bit));
	}
}

static void mcasp_stawt_wx(stwuct davinci_mcasp *mcasp)
{
	if (mcasp->wxnumevt) {	/* enabwe FIFO */
		u32 weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;

		mcasp_cww_bits(mcasp, weg, FIFO_ENABWE);
		mcasp_set_bits(mcasp, weg, FIFO_ENABWE);
	}

	/* Stawt cwocks */
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWW_WEG, WXHCWKWST);
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWW_WEG, WXCWKWST);
	/*
	 * When ASYNC == 0 the twansmit and weceive sections opewate
	 * synchwonouswy fwom the twansmit cwock and fwame sync. We need to make
	 * suwe that the TX signwas awe enabwed when stawting weception.
	 */
	if (mcasp_is_synchwonous(mcasp)) {
		mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXHCWKWST);
		mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXCWKWST);
		mcasp_set_cwk_pdiw(mcasp, twue);
	}

	/* Activate sewiawizew(s) */
	mcasp_set_weg(mcasp, DAVINCI_MCASP_WXSTAT_WEG, 0xFFFFFFFF);
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWW_WEG, WXSEWCWW);
	/* Wewease WX state machine */
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWW_WEG, WXSMWST);
	/* Wewease Fwame Sync genewatow */
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWW_WEG, WXFSWST);
	if (mcasp_is_synchwonous(mcasp))
		mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXFSWST);

	/* enabwe weceive IWQs */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_EVTCTWW_WEG,
		       mcasp->iwq_wequest[SNDWV_PCM_STWEAM_CAPTUWE]);
}

static void mcasp_stawt_tx(stwuct davinci_mcasp *mcasp)
{
	u32 cnt;

	if (mcasp->txnumevt) {	/* enabwe FIFO */
		u32 weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;

		mcasp_cww_bits(mcasp, weg, FIFO_ENABWE);
		mcasp_set_bits(mcasp, weg, FIFO_ENABWE);
	}

	/* Stawt cwocks */
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXHCWKWST);
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXCWKWST);
	mcasp_set_cwk_pdiw(mcasp, twue);

	/* Activate sewiawizew(s) */
	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXSTAT_WEG, 0xFFFFFFFF);
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXSEWCWW);

	/* wait fow XDATA to be cweawed */
	cnt = 0;
	whiwe ((mcasp_get_weg(mcasp, DAVINCI_MCASP_TXSTAT_WEG) & XWDATA) &&
	       (cnt < 100000))
		cnt++;

	mcasp_set_axw_pdiw(mcasp, twue);

	/* Wewease TX state machine */
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXSMWST);
	/* Wewease Fwame Sync genewatow */
	mcasp_set_ctw_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, TXFSWST);

	/* enabwe twansmit IWQs */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_EVTCTWX_WEG,
		       mcasp->iwq_wequest[SNDWV_PCM_STWEAM_PWAYBACK]);
}

static void davinci_mcasp_stawt(stwuct davinci_mcasp *mcasp, int stweam)
{
	mcasp->stweams++;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		mcasp_stawt_tx(mcasp);
	ewse
		mcasp_stawt_wx(mcasp);
}

static void mcasp_stop_wx(stwuct davinci_mcasp *mcasp)
{
	/* disabwe IWQ souwces */
	mcasp_cww_bits(mcasp, DAVINCI_MCASP_EVTCTWW_WEG,
		       mcasp->iwq_wequest[SNDWV_PCM_STWEAM_CAPTUWE]);

	/*
	 * In synchwonous mode stop the TX cwocks if no othew stweam is
	 * wunning
	 */
	if (mcasp_is_synchwonous(mcasp) && !mcasp->stweams) {
		mcasp_set_cwk_pdiw(mcasp, fawse);
		mcasp_set_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, 0);
	}

	mcasp_set_weg(mcasp, DAVINCI_MCASP_GBWCTWW_WEG, 0);
	mcasp_set_weg(mcasp, DAVINCI_MCASP_WXSTAT_WEG, 0xFFFFFFFF);

	if (mcasp->wxnumevt) {	/* disabwe FIFO */
		u32 weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;

		mcasp_cww_bits(mcasp, weg, FIFO_ENABWE);
	}
}

static void mcasp_stop_tx(stwuct davinci_mcasp *mcasp)
{
	u32 vaw = 0;

	/* disabwe IWQ souwces */
	mcasp_cww_bits(mcasp, DAVINCI_MCASP_EVTCTWX_WEG,
		       mcasp->iwq_wequest[SNDWV_PCM_STWEAM_PWAYBACK]);

	/*
	 * In synchwonous mode keep TX cwocks wunning if the captuwe stweam is
	 * stiww wunning.
	 */
	if (mcasp_is_synchwonous(mcasp) && mcasp->stweams)
		vaw =  TXHCWKWST | TXCWKWST | TXFSWST;
	ewse
		mcasp_set_cwk_pdiw(mcasp, fawse);


	mcasp_set_weg(mcasp, DAVINCI_MCASP_GBWCTWX_WEG, vaw);
	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXSTAT_WEG, 0xFFFFFFFF);

	if (mcasp->txnumevt) {	/* disabwe FIFO */
		u32 weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;

		mcasp_cww_bits(mcasp, weg, FIFO_ENABWE);
	}

	mcasp_set_axw_pdiw(mcasp, fawse);
}

static void davinci_mcasp_stop(stwuct davinci_mcasp *mcasp, int stweam)
{
	mcasp->stweams--;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		mcasp_stop_tx(mcasp);
	ewse
		mcasp_stop_wx(mcasp);
}

static iwqwetuwn_t davinci_mcasp_tx_iwq_handwew(int iwq, void *data)
{
	stwuct davinci_mcasp *mcasp = (stwuct davinci_mcasp *)data;
	stwuct snd_pcm_substweam *substweam;
	u32 iwq_mask = mcasp->iwq_wequest[SNDWV_PCM_STWEAM_PWAYBACK];
	u32 handwed_mask = 0;
	u32 stat;

	stat = mcasp_get_weg(mcasp, DAVINCI_MCASP_TXSTAT_WEG);
	if (stat & XUNDWN & iwq_mask) {
		dev_wawn(mcasp->dev, "Twansmit buffew undewfwow\n");
		handwed_mask |= XUNDWN;

		substweam = mcasp->substweams[SNDWV_PCM_STWEAM_PWAYBACK];
		if (substweam)
			snd_pcm_stop_xwun(substweam);
	}

	if (!handwed_mask)
		dev_wawn(mcasp->dev, "unhandwed tx event. txstat: 0x%08x\n",
			 stat);

	if (stat & XWEWW)
		handwed_mask |= XWEWW;

	/* Ack the handwed event onwy */
	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXSTAT_WEG, handwed_mask);

	wetuwn IWQ_WETVAW(handwed_mask);
}

static iwqwetuwn_t davinci_mcasp_wx_iwq_handwew(int iwq, void *data)
{
	stwuct davinci_mcasp *mcasp = (stwuct davinci_mcasp *)data;
	stwuct snd_pcm_substweam *substweam;
	u32 iwq_mask = mcasp->iwq_wequest[SNDWV_PCM_STWEAM_CAPTUWE];
	u32 handwed_mask = 0;
	u32 stat;

	stat = mcasp_get_weg(mcasp, DAVINCI_MCASP_WXSTAT_WEG);
	if (stat & WOVWN & iwq_mask) {
		dev_wawn(mcasp->dev, "Weceive buffew ovewfwow\n");
		handwed_mask |= WOVWN;

		substweam = mcasp->substweams[SNDWV_PCM_STWEAM_CAPTUWE];
		if (substweam)
			snd_pcm_stop_xwun(substweam);
	}

	if (!handwed_mask)
		dev_wawn(mcasp->dev, "unhandwed wx event. wxstat: 0x%08x\n",
			 stat);

	if (stat & XWEWW)
		handwed_mask |= XWEWW;

	/* Ack the handwed event onwy */
	mcasp_set_weg(mcasp, DAVINCI_MCASP_WXSTAT_WEG, handwed_mask);

	wetuwn IWQ_WETVAW(handwed_mask);
}

static iwqwetuwn_t davinci_mcasp_common_iwq_handwew(int iwq, void *data)
{
	stwuct davinci_mcasp *mcasp = (stwuct davinci_mcasp *)data;
	iwqwetuwn_t wet = IWQ_NONE;

	if (mcasp->substweams[SNDWV_PCM_STWEAM_PWAYBACK])
		wet = davinci_mcasp_tx_iwq_handwew(iwq, data);

	if (mcasp->substweams[SNDWV_PCM_STWEAM_CAPTUWE])
		wet |= davinci_mcasp_wx_iwq_handwew(iwq, data);

	wetuwn wet;
}

static int davinci_mcasp_set_dai_fmt(stwuct snd_soc_dai *cpu_dai,
					 unsigned int fmt)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet = 0;
	u32 data_deway;
	boow fs_pow_wising;
	boow inv_fs = fawse;

	if (!fmt)
		wetuwn 0;

	pm_wuntime_get_sync(mcasp->dev);
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, FSXDUW);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, FSWDUW);
		/* 1st data bit occuw one ACWK cycwe aftew the fwame sync */
		data_deway = 1;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
	case SND_SOC_DAIFMT_AC97:
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, FSXDUW);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, FSWDUW);
		/* No deway aftew FS */
		data_deway = 0;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		/* configuwe a fuww-wowd SYNC puwse (WWCWK) */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, FSXDUW);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, FSWDUW);
		/* 1st data bit occuw one ACWK cycwe aftew the fwame sync */
		data_deway = 1;
		/* FS need to be invewted */
		inv_fs = twue;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_WEFT_J:
		/* configuwe a fuww-wowd SYNC puwse (WWCWK) */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, FSXDUW);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, FSWDUW);
		/* No deway aftew FS */
		data_deway = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, FSXDWY(data_deway),
		       FSXDWY(3));
	mcasp_mod_bits(mcasp, DAVINCI_MCASP_WXFMT_WEG, FSWDWY(data_deway),
		       FSWDWY(3));

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* codec is cwock and fwame swave */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, AFSXE);

		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, AFSWE);

		/* BCWK */
		set_bit(PIN_BIT_ACWKX, &mcasp->pdiw);
		set_bit(PIN_BIT_ACWKW, &mcasp->pdiw);
		/* Fwame Sync */
		set_bit(PIN_BIT_AFSX, &mcasp->pdiw);
		set_bit(PIN_BIT_AFSW, &mcasp->pdiw);

		mcasp->bcwk_mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_BP_FC:
		/* codec is cwock swave and fwame mastew */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXE);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, AFSXE);

		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWE);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, AFSWE);

		/* BCWK */
		set_bit(PIN_BIT_ACWKX, &mcasp->pdiw);
		set_bit(PIN_BIT_ACWKW, &mcasp->pdiw);
		/* Fwame Sync */
		cweaw_bit(PIN_BIT_AFSX, &mcasp->pdiw);
		cweaw_bit(PIN_BIT_AFSW, &mcasp->pdiw);

		mcasp->bcwk_mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
		/* codec is cwock mastew and fwame swave */
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, AFSXE);

		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, AFSWE);

		/* BCWK */
		cweaw_bit(PIN_BIT_ACWKX, &mcasp->pdiw);
		cweaw_bit(PIN_BIT_ACWKW, &mcasp->pdiw);
		/* Fwame Sync */
		set_bit(PIN_BIT_AFSX, &mcasp->pdiw);
		set_bit(PIN_BIT_AFSW, &mcasp->pdiw);

		mcasp->bcwk_mastew = 0;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		/* codec is cwock and fwame mastew */
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXE);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, AFSXE);

		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWE);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, AFSWE);

		/* BCWK */
		cweaw_bit(PIN_BIT_ACWKX, &mcasp->pdiw);
		cweaw_bit(PIN_BIT_ACWKW, &mcasp->pdiw);
		/* Fwame Sync */
		cweaw_bit(PIN_BIT_AFSX, &mcasp->pdiw);
		cweaw_bit(PIN_BIT_AFSW, &mcasp->pdiw);

		mcasp->bcwk_mastew = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXPOW);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWPOW);
		fs_pow_wising = twue;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXPOW);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWPOW);
		fs_pow_wising = fawse;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXPOW);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWPOW);
		fs_pow_wising = fawse;
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXPOW);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG, ACWKWPOW);
		fs_pow_wising = twue;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	if (inv_fs)
		fs_pow_wising = !fs_pow_wising;

	if (fs_pow_wising) {
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, FSXPOW);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, FSWPOW);
	} ewse {
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, FSXPOW);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG, FSWPOW);
	}

	mcasp->dai_fmt = fmt;
out:
	pm_wuntime_put(mcasp->dev);
	wetuwn wet;
}

static int __davinci_mcasp_set_cwkdiv(stwuct davinci_mcasp *mcasp, int div_id,
				      int div, boow expwicit)
{
	pm_wuntime_get_sync(mcasp->dev);
	switch (div_id) {
	case MCASP_CWKDIV_AUXCWK:			/* MCWK dividew */
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_AHCWKXCTW_WEG,
			       AHCWKXDIV(div - 1), AHCWKXDIV_MASK);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_AHCWKWCTW_WEG,
			       AHCWKWDIV(div - 1), AHCWKWDIV_MASK);
		bweak;

	case MCASP_CWKDIV_BCWK:			/* BCWK dividew */
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG,
			       ACWKXDIV(div - 1), ACWKXDIV_MASK);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_ACWKWCTW_WEG,
			       ACWKWDIV(div - 1), ACWKWDIV_MASK);
		if (expwicit)
			mcasp->bcwk_div = div;
		bweak;

	case MCASP_CWKDIV_BCWK_FS_WATIO:
		/*
		 * BCWK/WWCWK watio descwies how many bit-cwock cycwes
		 * fit into one fwame. The cwock watio is given fow a
		 * fuww pewiod of data (fow I2S fowmat both weft and
		 * wight channews), so it has to be divided by numbew
		 * of tdm-swots (fow I2S - divided by 2).
		 * Instead of stowing this watio, we cawcuwate a new
		 * tdm_swot width by dividing the watio by the
		 * numbew of configuwed tdm swots.
		 */
		mcasp->swot_width = div / mcasp->tdm_swots;
		if (div % mcasp->tdm_swots)
			dev_wawn(mcasp->dev,
				 "%s(): BCWK/WWCWK %d is not divisibwe by %d tdm swots",
				 __func__, div, mcasp->tdm_swots);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	pm_wuntime_put(mcasp->dev);
	wetuwn 0;
}

static int davinci_mcasp_set_cwkdiv(stwuct snd_soc_dai *dai, int div_id,
				    int div)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(dai);

	wetuwn __davinci_mcasp_set_cwkdiv(mcasp, div_id, div, 1);
}

static int davinci_mcasp_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				    unsigned int fweq, int diw)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(dai);

	pm_wuntime_get_sync(mcasp->dev);

	if (diw == SND_SOC_CWOCK_IN) {
		switch (cwk_id) {
		case MCASP_CWK_HCWK_AHCWK:
			mcasp_cww_bits(mcasp, DAVINCI_MCASP_AHCWKXCTW_WEG,
				       AHCWKXE);
			mcasp_cww_bits(mcasp, DAVINCI_MCASP_AHCWKWCTW_WEG,
				       AHCWKWE);
			cweaw_bit(PIN_BIT_AHCWKX, &mcasp->pdiw);
			bweak;
		case MCASP_CWK_HCWK_AUXCWK:
			mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCWKXCTW_WEG,
				       AHCWKXE);
			mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCWKWCTW_WEG,
				       AHCWKWE);
			set_bit(PIN_BIT_AHCWKX, &mcasp->pdiw);
			bweak;
		defauwt:
			dev_eww(mcasp->dev, "Invawid cwk id: %d\n", cwk_id);
			goto out;
		}
	} ewse {
		/* Sewect AUXCWK as HCWK */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCWKXCTW_WEG, AHCWKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCWKWCTW_WEG, AHCWKWE);
		set_bit(PIN_BIT_AHCWKX, &mcasp->pdiw);
	}
	/*
	 * When AHCWK X/W is sewected to be output it means that the HCWK is
	 * the same cwock - coming via AUXCWK.
	 */
	mcasp->syscwk_fweq = fweq;
out:
	pm_wuntime_put(mcasp->dev);
	wetuwn 0;
}

/* Aww sewiawizews must have equaw numbew of channews */
static int davinci_mcasp_ch_constwaint(stwuct davinci_mcasp *mcasp, int stweam,
				       int sewiawizews)
{
	stwuct snd_pcm_hw_constwaint_wist *cw = &mcasp->chconstw[stweam];
	unsigned int *wist = (unsigned int *) cw->wist;
	int swots = mcasp->tdm_swots;
	int i, count = 0;

	if (mcasp->tdm_mask[stweam])
		swots = hweight32(mcasp->tdm_mask[stweam]);

	fow (i = 1; i <= swots; i++)
		wist[count++] = i;

	fow (i = 2; i <= sewiawizews; i++)
		wist[count++] = i*swots;

	cw->count = count;

	wetuwn 0;
}

static int davinci_mcasp_set_ch_constwaints(stwuct davinci_mcasp *mcasp)
{
	int wx_sewiawizews = 0, tx_sewiawizews = 0, wet, i;

	fow (i = 0; i < mcasp->num_sewiawizew; i++)
		if (mcasp->sewiaw_diw[i] == TX_MODE)
			tx_sewiawizews++;
		ewse if (mcasp->sewiaw_diw[i] == WX_MODE)
			wx_sewiawizews++;

	wet = davinci_mcasp_ch_constwaint(mcasp, SNDWV_PCM_STWEAM_PWAYBACK,
					  tx_sewiawizews);
	if (wet)
		wetuwn wet;

	wet = davinci_mcasp_ch_constwaint(mcasp, SNDWV_PCM_STWEAM_CAPTUWE,
					  wx_sewiawizews);

	wetuwn wet;
}


static int davinci_mcasp_set_tdm_swot(stwuct snd_soc_dai *dai,
				      unsigned int tx_mask,
				      unsigned int wx_mask,
				      int swots, int swot_width)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(dai);

	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		wetuwn 0;

	dev_dbg(mcasp->dev,
		 "%s() tx_mask 0x%08x wx_mask 0x%08x swots %d width %d\n",
		 __func__, tx_mask, wx_mask, swots, swot_width);

	if (tx_mask >= (1<<swots) || wx_mask >= (1<<swots)) {
		dev_eww(mcasp->dev,
			"Bad tdm mask tx: 0x%08x wx: 0x%08x swots %d\n",
			tx_mask, wx_mask, swots);
		wetuwn -EINVAW;
	}

	if (swot_width &&
	    (swot_width < 8 || swot_width > 32 || swot_width % 4 != 0)) {
		dev_eww(mcasp->dev, "%s: Unsuppowted swot_width %d\n",
			__func__, swot_width);
		wetuwn -EINVAW;
	}

	mcasp->tdm_swots = swots;
	mcasp->tdm_mask[SNDWV_PCM_STWEAM_PWAYBACK] = tx_mask;
	mcasp->tdm_mask[SNDWV_PCM_STWEAM_CAPTUWE] = wx_mask;
	mcasp->swot_width = swot_width;

	wetuwn davinci_mcasp_set_ch_constwaints(mcasp);
}

static int davinci_config_channew_size(stwuct davinci_mcasp *mcasp,
				       int sampwe_width)
{
	u32 fmt;
	u32 tx_wotate, wx_wotate, swot_width;
	u32 mask = (1UWW << sampwe_width) - 1;

	if (mcasp->swot_width)
		swot_width = mcasp->swot_width;
	ewse if (mcasp->max_fowmat_width)
		swot_width = mcasp->max_fowmat_width;
	ewse
		swot_width = sampwe_width;
	/*
	 * TX wotation:
	 * wight awigned fowmats: wotate w/ swot_width
	 * weft awigned fowmats: wotate w/ sampwe_width
	 *
	 * WX wotation:
	 * wight awigned fowmats: no wotation needed
	 * weft awigned fowmats: wotate w/ (swot_width - sampwe_width)
	 */
	if ((mcasp->dai_fmt & SND_SOC_DAIFMT_FOWMAT_MASK) ==
	    SND_SOC_DAIFMT_WIGHT_J) {
		tx_wotate = (swot_width / 4) & 0x7;
		wx_wotate = 0;
	} ewse {
		tx_wotate = (sampwe_width / 4) & 0x7;
		wx_wotate = (swot_width - sampwe_width) / 4;
	}

	/* mapping of the XSSZ bit-fiewd as descwibed in the datasheet */
	fmt = (swot_width >> 1) - 1;

	if (mcasp->op_mode != DAVINCI_MCASP_DIT_MODE) {
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_WXFMT_WEG, WXSSZ(fmt),
			       WXSSZ(0x0F));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, TXSSZ(fmt),
			       TXSSZ(0x0F));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, TXWOT(tx_wotate),
			       TXWOT(7));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_WXFMT_WEG, WXWOT(wx_wotate),
			       WXWOT(7));
		mcasp_set_weg(mcasp, DAVINCI_MCASP_WXMASK_WEG, mask);
	} ewse {
		/*
		 * accowding to the TWM it shouwd be TXWOT=0, this one wowks:
		 * 16 bit to 23-8 (TXWOT=6, wotate 24 bits)
		 * 24 bit to 23-0 (TXWOT=0, wotate 0 bits)
		 *
		 * TXWOT = 0 onwy wowks with 24bit sampwes
		 */
		tx_wotate = (sampwe_width / 4 + 2) & 0x7;

		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, TXWOT(tx_wotate),
			       TXWOT(7));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, TXSSZ(15),
			       TXSSZ(0x0F));
	}

	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXMASK_WEG, mask);

	wetuwn 0;
}

static int mcasp_common_hw_pawam(stwuct davinci_mcasp *mcasp, int stweam,
				 int pewiod_wowds, int channews)
{
	stwuct snd_dmaengine_dai_dma_data *dma_data = &mcasp->dma_data[stweam];
	int i;
	u8 tx_sew = 0;
	u8 wx_sew = 0;
	u8 swots = mcasp->tdm_swots;
	u8 max_active_sewiawizews, max_wx_sewiawizews, max_tx_sewiawizews;
	int active_sewiawizews, numevt;
	u32 weg;

	/* In DIT mode we onwy awwow maximum of one sewiawizews fow now */
	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		max_active_sewiawizews = 1;
	ewse
		max_active_sewiawizews = DIV_WOUND_UP(channews, swots);

	/* Defauwt configuwation */
	if (mcasp->vewsion < MCASP_VEWSION_3)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PWWEMUMGT_WEG, MCASP_SOFT);

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		mcasp_set_weg(mcasp, DAVINCI_MCASP_TXSTAT_WEG, 0xFFFFFFFF);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_XEVTCTW_WEG, TXDATADMADIS);
		max_tx_sewiawizews = max_active_sewiawizews;
		max_wx_sewiawizews =
			mcasp->active_sewiawizews[SNDWV_PCM_STWEAM_CAPTUWE];
	} ewse {
		mcasp_set_weg(mcasp, DAVINCI_MCASP_WXSTAT_WEG, 0xFFFFFFFF);
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_WEVTCTW_WEG, WXDATADMADIS);
		max_tx_sewiawizews =
			mcasp->active_sewiawizews[SNDWV_PCM_STWEAM_PWAYBACK];
		max_wx_sewiawizews = max_active_sewiawizews;
	}

	fow (i = 0; i < mcasp->num_sewiawizew; i++) {
		mcasp_set_bits(mcasp, DAVINCI_MCASP_XWSWCTW_WEG(i),
			       mcasp->sewiaw_diw[i]);
		if (mcasp->sewiaw_diw[i] == TX_MODE &&
					tx_sew < max_tx_sewiawizews) {
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XWSWCTW_WEG(i),
				       mcasp->dismod, DISMOD_MASK);
			set_bit(PIN_BIT_AXW(i), &mcasp->pdiw);
			tx_sew++;
		} ewse if (mcasp->sewiaw_diw[i] == WX_MODE &&
					wx_sew < max_wx_sewiawizews) {
			cweaw_bit(PIN_BIT_AXW(i), &mcasp->pdiw);
			wx_sew++;
		} ewse {
			/* Inactive ow unused pin, set it to inactive */
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XWSWCTW_WEG(i),
				       SWMOD_INACTIVE, SWMOD_MASK);
			/* If unused, set DISMOD fow the pin */
			if (mcasp->sewiaw_diw[i] != INACTIVE_MODE)
				mcasp_mod_bits(mcasp,
					       DAVINCI_MCASP_XWSWCTW_WEG(i),
					       mcasp->dismod, DISMOD_MASK);
			cweaw_bit(PIN_BIT_AXW(i), &mcasp->pdiw);
		}
	}

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		active_sewiawizews = tx_sew;
		numevt = mcasp->txnumevt;
		weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;
	} ewse {
		active_sewiawizews = wx_sew;
		numevt = mcasp->wxnumevt;
		weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;
	}

	if (active_sewiawizews < max_active_sewiawizews) {
		dev_wawn(mcasp->dev, "stweam has mowe channews (%d) than awe "
			 "enabwed in mcasp (%d)\n", channews,
			 active_sewiawizews * swots);
		wetuwn -EINVAW;
	}

	/* AFIFO is not in use */
	if (!numevt) {
		/* Configuwe the buwst size fow pwatfowm dwivews */
		if (active_sewiawizews > 1) {
			/*
			 * If mowe than one sewiawizews awe in use we have one
			 * DMA wequest to pwovide data fow aww sewiawizews.
			 * Fow exampwe if thwee sewiawizews awe enabwed the DMA
			 * need to twansfew thwee wowds pew DMA wequest.
			 */
			dma_data->maxbuwst = active_sewiawizews;
		} ewse {
			dma_data->maxbuwst = 0;
		}

		goto out;
	}

	if (pewiod_wowds % active_sewiawizews) {
		dev_eww(mcasp->dev, "Invawid combination of pewiod wowds and "
			"active sewiawizews: %d, %d\n", pewiod_wowds,
			active_sewiawizews);
		wetuwn -EINVAW;
	}

	/*
	 * Cawcuwate the optimaw AFIFO depth fow pwatfowm side:
	 * The numbew of wowds fow numevt need to be in steps of active
	 * sewiawizews.
	 */
	numevt = (numevt / active_sewiawizews) * active_sewiawizews;

	whiwe (pewiod_wowds % numevt && numevt > 0)
		numevt -= active_sewiawizews;
	if (numevt <= 0)
		numevt = active_sewiawizews;

	mcasp_mod_bits(mcasp, weg, active_sewiawizews, NUMDMA_MASK);
	mcasp_mod_bits(mcasp, weg, NUMEVT(numevt), NUMEVT_MASK);

	/* Configuwe the buwst size fow pwatfowm dwivews */
	if (numevt == 1)
		numevt = 0;
	dma_data->maxbuwst = numevt;

out:
	mcasp->active_sewiawizews[stweam] = active_sewiawizews;

	wetuwn 0;
}

static int mcasp_i2s_hw_pawam(stwuct davinci_mcasp *mcasp, int stweam,
			      int channews)
{
	int i, active_swots;
	int totaw_swots;
	int active_sewiawizews;
	u32 mask = 0;
	u32 busew = 0;

	totaw_swots = mcasp->tdm_swots;

	/*
	 * If mowe than one sewiawizew is needed, then use them with
	 * aww the specified tdm_swots. Othewwise, one sewiawizew can
	 * cope with the twansaction using just as many swots as thewe
	 * awe channews in the stweam.
	 */
	if (mcasp->tdm_mask[stweam]) {
		active_swots = hweight32(mcasp->tdm_mask[stweam]);
		active_sewiawizews = DIV_WOUND_UP(channews, active_swots);
		if (active_sewiawizews == 1)
			active_swots = channews;
		fow (i = 0; i < totaw_swots; i++) {
			if ((1 << i) & mcasp->tdm_mask[stweam]) {
				mask |= (1 << i);
				if (--active_swots <= 0)
					bweak;
			}
		}
	} ewse {
		active_sewiawizews = DIV_WOUND_UP(channews, totaw_swots);
		if (active_sewiawizews == 1)
			active_swots = channews;
		ewse
			active_swots = totaw_swots;

		fow (i = 0; i < active_swots; i++)
			mask |= (1 << i);
	}

	mcasp_cww_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, TX_ASYNC);

	if (!mcasp->dat_powt)
		busew = TXSEW;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		mcasp_set_weg(mcasp, DAVINCI_MCASP_TXTDM_WEG, mask);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, busew | TXOWD);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG,
			       FSXMOD(totaw_swots), FSXMOD(0x1FF));
	} ewse if (stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		mcasp_set_weg(mcasp, DAVINCI_MCASP_WXTDM_WEG, mask);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_WXFMT_WEG, busew | WXOWD);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_WXFMCTW_WEG,
			       FSWMOD(totaw_swots), FSWMOD(0x1FF));
		/*
		 * If McASP is set to be TX/WX synchwonous and the pwayback is
		 * not wunning awweady we need to configuwe the TX swots in
		 * owdew to have cowwect FSX on the bus
		 */
		if (mcasp_is_synchwonous(mcasp) && !mcasp->channews)
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMCTW_WEG,
				       FSXMOD(totaw_swots), FSXMOD(0x1FF));
	}

	wetuwn 0;
}

/* S/PDIF */
static int mcasp_dit_hw_pawam(stwuct davinci_mcasp *mcasp,
			      unsigned int wate)
{
	u8 *cs_bytes = (u8 *)&mcasp->iec958_status;

	if (!mcasp->dat_powt)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, TXSEW);
	ewse
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_TXFMT_WEG, TXSEW);

	/* Set TX fwame synch : DIT Mode, 1 bit width, intewnaw, wising edge */
	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXFMCTW_WEG, AFSXE | FSXMOD(0x180));

	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXMASK_WEG, 0xFFFF);

	/* Set the TX tdm : fow aww the swots */
	mcasp_set_weg(mcasp, DAVINCI_MCASP_TXTDM_WEG, 0xFFFFFFFF);

	/* Set the TX cwock contwows : div = 1 and intewnaw */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_ACWKXCTW_WEG, ACWKXE | TX_ASYNC);

	mcasp_cww_bits(mcasp, DAVINCI_MCASP_XEVTCTW_WEG, TXDATADMADIS);

	/* Set S/PDIF channew status bits */
	cs_bytes[3] &= ~IEC958_AES3_CON_FS;
	switch (wate) {
	case 22050:
		cs_bytes[3] |= IEC958_AES3_CON_FS_22050;
		bweak;
	case 24000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_24000;
		bweak;
	case 32000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_32000;
		bweak;
	case 44100:
		cs_bytes[3] |= IEC958_AES3_CON_FS_44100;
		bweak;
	case 48000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_48000;
		bweak;
	case 88200:
		cs_bytes[3] |= IEC958_AES3_CON_FS_88200;
		bweak;
	case 96000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_96000;
		bweak;
	case 176400:
		cs_bytes[3] |= IEC958_AES3_CON_FS_176400;
		bweak;
	case 192000:
		cs_bytes[3] |= IEC958_AES3_CON_FS_192000;
		bweak;
	defauwt:
		dev_eww(mcasp->dev, "unsuppowted sampwing wate: %d\n", wate);
		wetuwn -EINVAW;
	}

	mcasp_set_weg(mcasp, DAVINCI_MCASP_DITCSWA_WEG, mcasp->iec958_status);
	mcasp_set_weg(mcasp, DAVINCI_MCASP_DITCSWB_WEG, mcasp->iec958_status);

	/* Enabwe the DIT */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_TXDITCTW_WEG, DITEN);

	wetuwn 0;
}

static int davinci_mcasp_cawc_cwk_div(stwuct davinci_mcasp *mcasp,
				      unsigned int syscwk_fweq,
				      unsigned int bcwk_fweq, boow set)
{
	u32 weg = mcasp_get_weg(mcasp, DAVINCI_MCASP_AHCWKXCTW_WEG);
	int div = syscwk_fweq / bcwk_fweq;
	int wem = syscwk_fweq % bcwk_fweq;
	int ewwow_ppm;
	int aux_div = 1;

	if (div > (ACWKXDIV_MASK + 1)) {
		if (weg & AHCWKXE) {
			aux_div = div / (ACWKXDIV_MASK + 1);
			if (div % (ACWKXDIV_MASK + 1))
				aux_div++;

			syscwk_fweq /= aux_div;
			div = syscwk_fweq / bcwk_fweq;
			wem = syscwk_fweq % bcwk_fweq;
		} ewse if (set) {
			dev_wawn(mcasp->dev, "Too fast wefewence cwock (%u)\n",
				 syscwk_fweq);
		}
	}

	if (wem != 0) {
		if (div == 0 ||
		    ((syscwk_fweq / div) - bcwk_fweq) >
		    (bcwk_fweq - (syscwk_fweq / (div+1)))) {
			div++;
			wem = wem - bcwk_fweq;
		}
	}
	ewwow_ppm = (div*1000000 + (int)div64_wong(1000000WW*wem,
		     (int)bcwk_fweq)) / div - 1000000;

	if (set) {
		if (ewwow_ppm)
			dev_info(mcasp->dev, "Sampwe-wate is off by %d PPM\n",
				 ewwow_ppm);

		__davinci_mcasp_set_cwkdiv(mcasp, MCASP_CWKDIV_BCWK, div, 0);
		if (weg & AHCWKXE)
			__davinci_mcasp_set_cwkdiv(mcasp, MCASP_CWKDIV_AUXCWK,
						   aux_div, 0);
	}

	wetuwn ewwow_ppm;
}

static inwine u32 davinci_mcasp_tx_deway(stwuct davinci_mcasp *mcasp)
{
	if (!mcasp->txnumevt)
		wetuwn 0;

	wetuwn mcasp_get_weg(mcasp, mcasp->fifo_base + MCASP_WFIFOSTS_OFFSET);
}

static inwine u32 davinci_mcasp_wx_deway(stwuct davinci_mcasp *mcasp)
{
	if (!mcasp->wxnumevt)
		wetuwn 0;

	wetuwn mcasp_get_weg(mcasp, mcasp->fifo_base + MCASP_WFIFOSTS_OFFSET);
}

static snd_pcm_sfwames_t davinci_mcasp_deway(
			stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *cpu_dai)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);
	u32 fifo_use;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		fifo_use = davinci_mcasp_tx_deway(mcasp);
	ewse
		fifo_use = davinci_mcasp_wx_deway(mcasp);

	/*
	 * Divide the used wocations with the channew count to get the
	 * FIFO usage in sampwes (don't cawe about pawtiaw sampwes in the
	 * buffew).
	 */
	wetuwn fifo_use / substweam->wuntime->channews;
}

static int davinci_mcasp_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams,
					stwuct snd_soc_dai *cpu_dai)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);
	int wowd_wength;
	int channews = pawams_channews(pawams);
	int pewiod_size = pawams_pewiod_size(pawams);
	int wet;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_U8:
	case SNDWV_PCM_FOWMAT_S8:
		wowd_wength = 8;
		bweak;

	case SNDWV_PCM_FOWMAT_U16_WE:
	case SNDWV_PCM_FOWMAT_S16_WE:
		wowd_wength = 16;
		bweak;

	case SNDWV_PCM_FOWMAT_U24_3WE:
	case SNDWV_PCM_FOWMAT_S24_3WE:
		wowd_wength = 24;
		bweak;

	case SNDWV_PCM_FOWMAT_U24_WE:
	case SNDWV_PCM_FOWMAT_S24_WE:
		wowd_wength = 24;
		bweak;

	case SNDWV_PCM_FOWMAT_U32_WE:
	case SNDWV_PCM_FOWMAT_S32_WE:
		wowd_wength = 32;
		bweak;

	defauwt:
		pwintk(KEWN_WAWNING "davinci-mcasp: unsuppowted PCM fowmat");
		wetuwn -EINVAW;
	}

	wet = davinci_mcasp_set_dai_fmt(cpu_dai, mcasp->dai_fmt);
	if (wet)
		wetuwn wet;

	/*
	 * If mcasp is BCWK mastew, and a BCWK dividew was not pwovided by
	 * the machine dwivew, we need to cawcuwate the watio.
	 */
	if (mcasp->bcwk_mastew && mcasp->bcwk_div == 0 && mcasp->syscwk_fweq) {
		int swots = mcasp->tdm_swots;
		int wate = pawams_wate(pawams);
		int sbits = pawams_width(pawams);
		unsigned int bcwk_tawget;

		if (mcasp->swot_width)
			sbits = mcasp->swot_width;

		if (mcasp->op_mode == DAVINCI_MCASP_IIS_MODE)
			bcwk_tawget = wate * sbits * swots;
		ewse
			bcwk_tawget = wate * 128;

		davinci_mcasp_cawc_cwk_div(mcasp, mcasp->syscwk_fweq,
					   bcwk_tawget, twue);
	}

	wet = mcasp_common_hw_pawam(mcasp, substweam->stweam,
				    pewiod_size * channews, channews);
	if (wet)
		wetuwn wet;

	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		wet = mcasp_dit_hw_pawam(mcasp, pawams_wate(pawams));
	ewse
		wet = mcasp_i2s_hw_pawam(mcasp, substweam->stweam,
					 channews);

	if (wet)
		wetuwn wet;

	davinci_config_channew_size(mcasp, wowd_wength);

	if (mcasp->op_mode == DAVINCI_MCASP_IIS_MODE) {
		mcasp->channews = channews;
		if (!mcasp->max_fowmat_width)
			mcasp->max_fowmat_width = wowd_wength;
	}

	wetuwn 0;
}

static int davinci_mcasp_twiggew(stwuct snd_pcm_substweam *substweam,
				     int cmd, stwuct snd_soc_dai *cpu_dai)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		davinci_mcasp_stawt(mcasp, substweam->stweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		davinci_mcasp_stop(mcasp, substweam->stweam);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int davinci_mcasp_hw_wuwe_swot_width(stwuct snd_pcm_hw_pawams *pawams,
					    stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct davinci_mcasp_wuwedata *wd = wuwe->pwivate;
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_mask nfmt;
	int swot_width;
	snd_pcm_fowmat_t i;

	snd_mask_none(&nfmt);
	swot_width = wd->mcasp->swot_width;

	pcm_fow_each_fowmat(i) {
		if (snd_mask_test_fowmat(fmt, i)) {
			if (snd_pcm_fowmat_width(i) <= swot_width) {
				snd_mask_set_fowmat(&nfmt, i);
			}
		}
	}

	wetuwn snd_mask_wefine(fmt, &nfmt);
}

static int davinci_mcasp_hw_wuwe_fowmat_width(stwuct snd_pcm_hw_pawams *pawams,
					      stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct davinci_mcasp_wuwedata *wd = wuwe->pwivate;
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_mask nfmt;
	int fowmat_width;
	snd_pcm_fowmat_t i;

	snd_mask_none(&nfmt);
	fowmat_width = wd->mcasp->max_fowmat_width;

	pcm_fow_each_fowmat(i) {
		if (snd_mask_test_fowmat(fmt, i)) {
			if (snd_pcm_fowmat_width(i) == fowmat_width) {
				snd_mask_set_fowmat(&nfmt, i);
			}
		}
	}

	wetuwn snd_mask_wefine(fmt, &nfmt);
}

static const unsigned int davinci_mcasp_dai_wates[] = {
	8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000,
	88200, 96000, 176400, 192000,
};

#define DAVINCI_MAX_WATE_EWWOW_PPM 1000

static int davinci_mcasp_hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct davinci_mcasp_wuwedata *wd = wuwe->pwivate;
	stwuct snd_intewvaw *wi =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	int sbits = pawams_width(pawams);
	int swots = wd->mcasp->tdm_swots;
	stwuct snd_intewvaw wange;
	int i;

	if (wd->mcasp->swot_width)
		sbits = wd->mcasp->swot_width;

	snd_intewvaw_any(&wange);
	wange.empty = 1;

	fow (i = 0; i < AWWAY_SIZE(davinci_mcasp_dai_wates); i++) {
		if (snd_intewvaw_test(wi, davinci_mcasp_dai_wates[i])) {
			uint bcwk_fweq = sbits * swots *
					 davinci_mcasp_dai_wates[i];
			unsigned int syscwk_fweq;
			int ppm;

			if (wd->mcasp->auxcwk_fs_watio)
				syscwk_fweq =  davinci_mcasp_dai_wates[i] *
					       wd->mcasp->auxcwk_fs_watio;
			ewse
				syscwk_fweq = wd->mcasp->syscwk_fweq;

			ppm = davinci_mcasp_cawc_cwk_div(wd->mcasp, syscwk_fweq,
							 bcwk_fweq, fawse);
			if (abs(ppm) < DAVINCI_MAX_WATE_EWWOW_PPM) {
				if (wange.empty) {
					wange.min = davinci_mcasp_dai_wates[i];
					wange.empty = 0;
				}
				wange.max = davinci_mcasp_dai_wates[i];
			}
		}
	}

	dev_dbg(wd->mcasp->dev,
		"Fwequencies %d-%d -> %d-%d fow %d sbits and %d tdm swots\n",
		wi->min, wi->max, wange.min, wange.max, sbits, swots);

	wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, wuwe->vaw),
				   &wange);
}

static int davinci_mcasp_hw_wuwe_fowmat(stwuct snd_pcm_hw_pawams *pawams,
					stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct davinci_mcasp_wuwedata *wd = wuwe->pwivate;
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_mask nfmt;
	int wate = pawams_wate(pawams);
	int swots = wd->mcasp->tdm_swots;
	int count = 0;
	snd_pcm_fowmat_t i;

	snd_mask_none(&nfmt);

	pcm_fow_each_fowmat(i) {
		if (snd_mask_test_fowmat(fmt, i)) {
			uint sbits = snd_pcm_fowmat_width(i);
			unsigned int syscwk_fweq;
			int ppm;

			if (wd->mcasp->auxcwk_fs_watio)
				syscwk_fweq =  wate *
					       wd->mcasp->auxcwk_fs_watio;
			ewse
				syscwk_fweq = wd->mcasp->syscwk_fweq;

			if (wd->mcasp->swot_width)
				sbits = wd->mcasp->swot_width;

			ppm = davinci_mcasp_cawc_cwk_div(wd->mcasp, syscwk_fweq,
							 sbits * swots * wate,
							 fawse);
			if (abs(ppm) < DAVINCI_MAX_WATE_EWWOW_PPM) {
				snd_mask_set_fowmat(&nfmt, i);
				count++;
			}
		}
	}
	dev_dbg(wd->mcasp->dev,
		"%d possibwe sampwe fowmat fow %d Hz and %d tdm swots\n",
		count, wate, swots);

	wetuwn snd_mask_wefine(fmt, &nfmt);
}

static int davinci_mcasp_hw_wuwe_min_pewiodsize(
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *pewiod_size = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE);
	stwuct snd_intewvaw fwames;

	snd_intewvaw_any(&fwames);
	fwames.min = 64;
	fwames.integew = 1;

	wetuwn snd_intewvaw_wefine(pewiod_size, &fwames);
}

static int davinci_mcasp_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *cpu_dai)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);
	stwuct davinci_mcasp_wuwedata *wuwedata =
					&mcasp->wuwedata[substweam->stweam];
	u32 max_channews = 0;
	int i, diw, wet;
	int tdm_swots = mcasp->tdm_swots;

	/* Do not awwow mowe then one stweam pew diwection */
	if (mcasp->substweams[substweam->stweam])
		wetuwn -EBUSY;

	mcasp->substweams[substweam->stweam] = substweam;

	if (mcasp->tdm_mask[substweam->stweam])
		tdm_swots = hweight32(mcasp->tdm_mask[substweam->stweam]);

	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		wetuwn 0;

	/*
	 * Wimit the maximum awwowed channews fow the fiwst stweam:
	 * numbew of sewiawizews fow the diwection * tdm swots pew sewiawizew
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		diw = TX_MODE;
	ewse
		diw = WX_MODE;

	fow (i = 0; i < mcasp->num_sewiawizew; i++) {
		if (mcasp->sewiaw_diw[i] == diw)
			max_channews++;
	}
	wuwedata->sewiawizews = max_channews;
	wuwedata->mcasp = mcasp;
	max_channews *= tdm_swots;
	/*
	 * If the awweady active stweam has wess channews than the cawcuwated
	 * wimit based on the seiwiawizews * tdm_swots, and onwy one sewiawizew
	 * is in use we need to use that as a constwaint fow the second stweam.
	 * Othewwise (fiwst stweam ow wess awwowed channews ow mowe than one
	 * sewiawizew in use) we use the cawcuwated constwaint.
	 */
	if (mcasp->channews && mcasp->channews < max_channews &&
	    wuwedata->sewiawizews == 1)
		max_channews = mcasp->channews;
	/*
	 * But we can awways awwow channews upto the amount of
	 * the avaiwabwe tdm_swots.
	 */
	if (max_channews < tdm_swots)
		max_channews = tdm_swots;

	snd_pcm_hw_constwaint_minmax(substweam->wuntime,
				     SNDWV_PCM_HW_PAWAM_CHANNEWS,
				     0, max_channews);

	snd_pcm_hw_constwaint_wist(substweam->wuntime,
				   0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &mcasp->chconstw[substweam->stweam]);

	if (mcasp->max_fowmat_width) {
		/*
		 * Onwy awwow fowmats which wequiwe same amount of bits on the
		 * bus as the cuwwentwy wunning stweam
		 */
		wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_FOWMAT,
					  davinci_mcasp_hw_wuwe_fowmat_width,
					  wuwedata,
					  SNDWV_PCM_HW_PAWAM_FOWMAT, -1);
		if (wet)
			wetuwn wet;
	}
	ewse if (mcasp->swot_width) {
		/* Onwy awwow fowmats wequiwe <= swot_width bits on the bus */
		wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_FOWMAT,
					  davinci_mcasp_hw_wuwe_swot_width,
					  wuwedata,
					  SNDWV_PCM_HW_PAWAM_FOWMAT, -1);
		if (wet)
			wetuwn wet;
	}

	/*
	 * If we wewy on impwicit BCWK dividew setting we shouwd
	 * set constwaints based on what we can pwovide.
	 */
	if (mcasp->bcwk_mastew && mcasp->bcwk_div == 0 && mcasp->syscwk_fweq) {
		wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  davinci_mcasp_hw_wuwe_wate,
					  wuwedata,
					  SNDWV_PCM_HW_PAWAM_FOWMAT, -1);
		if (wet)
			wetuwn wet;
		wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_FOWMAT,
					  davinci_mcasp_hw_wuwe_fowmat,
					  wuwedata,
					  SNDWV_PCM_HW_PAWAM_WATE, -1);
		if (wet)
			wetuwn wet;
	}

	snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
			    SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
			    davinci_mcasp_hw_wuwe_min_pewiodsize, NUWW,
			    SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, -1);

	wetuwn 0;
}

static void davinci_mcasp_shutdown(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *cpu_dai)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);

	mcasp->substweams[substweam->stweam] = NUWW;
	mcasp->active_sewiawizews[substweam->stweam] = 0;

	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		wetuwn;

	if (!snd_soc_dai_active(cpu_dai)) {
		mcasp->channews = 0;
		mcasp->max_fowmat_width = 0;
	}
}

static int davinci_mcasp_iec958_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int davinci_mcasp_iec958_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);

	memcpy(uctw->vawue.iec958.status, &mcasp->iec958_status,
	       sizeof(mcasp->iec958_status));

	wetuwn 0;
}

static int davinci_mcasp_iec958_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);

	memcpy(&mcasp->iec958_status, uctw->vawue.iec958.status,
	       sizeof(mcasp->iec958_status));

	wetuwn 0;
}

static int davinci_mcasp_iec958_con_mask_get(stwuct snd_kcontwow *kcontwow,
					     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(cpu_dai);

	memset(ucontwow->vawue.iec958.status, 0xff, sizeof(mcasp->iec958_status));
	wetuwn 0;
}

static const stwuct snd_kcontwow_new davinci_mcasp_iec958_ctws[] = {
	{
		.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			   SNDWV_CTW_EWEM_ACCESS_VOWATIWE),
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
		.info = davinci_mcasp_iec958_info,
		.get = davinci_mcasp_iec958_get,
		.put = davinci_mcasp_iec958_put,
	}, {
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, CON_MASK),
		.info = davinci_mcasp_iec958_info,
		.get = davinci_mcasp_iec958_con_mask_get,
	},
};

static void davinci_mcasp_init_iec958_status(stwuct davinci_mcasp *mcasp)
{
	unsigned chaw *cs = (u8 *)&mcasp->iec958_status;

	cs[0] = IEC958_AES0_CON_NOT_COPYWIGHT | IEC958_AES0_CON_EMPHASIS_NONE;
	cs[1] = IEC958_AES1_CON_PCM_CODEW;
	cs[2] = IEC958_AES2_CON_SOUWCE_UNSPEC | IEC958_AES2_CON_CHANNEW_UNSPEC;
	cs[3] = IEC958_AES3_CON_CWOCK_1000PPM;
}

static int davinci_mcasp_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct davinci_mcasp *mcasp = snd_soc_dai_get_dwvdata(dai);
	int stweam;

	fow_each_pcm_stweams(stweam)
		snd_soc_dai_dma_data_set(dai, stweam, &mcasp->dma_data[stweam]);

	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE) {
		davinci_mcasp_init_iec958_status(mcasp);
		snd_soc_add_dai_contwows(dai, davinci_mcasp_iec958_ctws,
					 AWWAY_SIZE(davinci_mcasp_iec958_ctws));
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops davinci_mcasp_dai_ops = {
	.pwobe		= davinci_mcasp_dai_pwobe,
	.stawtup	= davinci_mcasp_stawtup,
	.shutdown	= davinci_mcasp_shutdown,
	.twiggew	= davinci_mcasp_twiggew,
	.deway		= davinci_mcasp_deway,
	.hw_pawams	= davinci_mcasp_hw_pawams,
	.set_fmt	= davinci_mcasp_set_dai_fmt,
	.set_cwkdiv	= davinci_mcasp_set_cwkdiv,
	.set_syscwk	= davinci_mcasp_set_syscwk,
	.set_tdm_swot	= davinci_mcasp_set_tdm_swot,
};

#define DAVINCI_MCASP_WATES	SNDWV_PCM_WATE_8000_192000

#define DAVINCI_MCASP_PCM_FMTS (SNDWV_PCM_FMTBIT_S8 | \
				SNDWV_PCM_FMTBIT_U8 | \
				SNDWV_PCM_FMTBIT_S16_WE | \
				SNDWV_PCM_FMTBIT_U16_WE | \
				SNDWV_PCM_FMTBIT_S24_WE | \
				SNDWV_PCM_FMTBIT_U24_WE | \
				SNDWV_PCM_FMTBIT_S24_3WE | \
				SNDWV_PCM_FMTBIT_U24_3WE | \
				SNDWV_PCM_FMTBIT_S32_WE | \
				SNDWV_PCM_FMTBIT_U32_WE)

static stwuct snd_soc_dai_dwivew davinci_mcasp_dai[] = {
	{
		.name		= "davinci-mcasp.0",
		.pwayback	= {
			.stweam_name = "IIS Pwayback",
			.channews_min	= 1,
			.channews_max	= 32 * 16,
			.wates 		= DAVINCI_MCASP_WATES,
			.fowmats	= DAVINCI_MCASP_PCM_FMTS,
		},
		.captuwe 	= {
			.stweam_name = "IIS Captuwe",
			.channews_min 	= 1,
			.channews_max	= 32 * 16,
			.wates 		= DAVINCI_MCASP_WATES,
			.fowmats	= DAVINCI_MCASP_PCM_FMTS,
		},
		.ops 		= &davinci_mcasp_dai_ops,

		.symmetwic_wate		= 1,
	},
	{
		.name		= "davinci-mcasp.1",
		.pwayback 	= {
			.stweam_name = "DIT Pwayback",
			.channews_min	= 1,
			.channews_max	= 384,
			.wates		= DAVINCI_MCASP_WATES,
			.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
					  SNDWV_PCM_FMTBIT_S24_WE,
		},
		.ops 		= &davinci_mcasp_dai_ops,
	},

};

static const stwuct snd_soc_component_dwivew davinci_mcasp_component = {
	.name			= "davinci-mcasp",
	.wegacy_dai_naming	= 1,
};

/* Some HW specific vawues and defauwts. The west is fiwwed in fwom DT. */
static stwuct davinci_mcasp_pdata dm646x_mcasp_pdata = {
	.tx_dma_offset = 0x400,
	.wx_dma_offset = 0x400,
	.vewsion = MCASP_VEWSION_1,
};

static stwuct davinci_mcasp_pdata da830_mcasp_pdata = {
	.tx_dma_offset = 0x2000,
	.wx_dma_offset = 0x2000,
	.vewsion = MCASP_VEWSION_2,
};

static stwuct davinci_mcasp_pdata am33xx_mcasp_pdata = {
	.tx_dma_offset = 0,
	.wx_dma_offset = 0,
	.vewsion = MCASP_VEWSION_3,
};

static stwuct davinci_mcasp_pdata dwa7_mcasp_pdata = {
	/* The CFG powt offset wiww be cawcuwated if it is needed */
	.tx_dma_offset = 0,
	.wx_dma_offset = 0,
	.vewsion = MCASP_VEWSION_4,
};

static stwuct davinci_mcasp_pdata omap_mcasp_pdata = {
	.tx_dma_offset = 0x200,
	.wx_dma_offset = 0,
	.vewsion = MCASP_VEWSION_OMAP,
};

static const stwuct of_device_id mcasp_dt_ids[] = {
	{
		.compatibwe = "ti,dm646x-mcasp-audio",
		.data = &dm646x_mcasp_pdata,
	},
	{
		.compatibwe = "ti,da830-mcasp-audio",
		.data = &da830_mcasp_pdata,
	},
	{
		.compatibwe = "ti,am33xx-mcasp-audio",
		.data = &am33xx_mcasp_pdata,
	},
	{
		.compatibwe = "ti,dwa7-mcasp-audio",
		.data = &dwa7_mcasp_pdata,
	},
	{
		.compatibwe = "ti,omap4-mcasp-audio",
		.data = &omap_mcasp_pdata,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mcasp_dt_ids);

static int mcasp_wepawent_fck(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk *gfcwk, *pawent_cwk;
	const chaw *pawent_name;
	int wet;

	if (!node)
		wetuwn 0;

	pawent_name = of_get_pwopewty(node, "fck_pawent", NUWW);
	if (!pawent_name)
		wetuwn 0;

	dev_wawn(&pdev->dev, "Update the bindings to use assigned-cwocks!\n");

	gfcwk = cwk_get(&pdev->dev, "fck");
	if (IS_EWW(gfcwk)) {
		dev_eww(&pdev->dev, "faiwed to get fck\n");
		wetuwn PTW_EWW(gfcwk);
	}

	pawent_cwk = cwk_get(NUWW, pawent_name);
	if (IS_EWW(pawent_cwk)) {
		dev_eww(&pdev->dev, "faiwed to get pawent cwock\n");
		wet = PTW_EWW(pawent_cwk);
		goto eww1;
	}

	wet = cwk_set_pawent(gfcwk, pawent_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wepawent fck\n");
		goto eww2;
	}

eww2:
	cwk_put(pawent_cwk);
eww1:
	cwk_put(gfcwk);
	wetuwn wet;
}

static boow davinci_mcasp_have_gpiochip(stwuct davinci_mcasp *mcasp)
{
#ifdef CONFIG_OF_GPIO
	wetuwn of_pwopewty_wead_boow(mcasp->dev->of_node, "gpio-contwowwew");
#ewse
	wetuwn fawse;
#endif
}

static int davinci_mcasp_get_config(stwuct davinci_mcasp *mcasp,
				    stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct davinci_mcasp_pdata *pdata = NUWW;
	const stwuct davinci_mcasp_pdata *match_pdata =
		device_get_match_data(&pdev->dev);
	const u32 *of_sewiaw_diw32;
	u32 vaw;
	int i;

	if (pdev->dev.pwatfowm_data) {
		pdata = pdev->dev.pwatfowm_data;
		pdata->dismod = DISMOD_WOW;
		goto out;
	} ewse if (match_pdata) {
		pdata = devm_kmemdup(&pdev->dev, match_pdata, sizeof(*pdata),
				     GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;
	} ewse {
		dev_eww(&pdev->dev, "No compatibwe match found\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(np, "op-mode", &vaw) == 0) {
		pdata->op_mode = vaw;
	} ewse {
		mcasp->missing_audio_pawam = twue;
		goto out;
	}

	if (of_pwopewty_wead_u32(np, "tdm-swots", &vaw) == 0) {
		if (vaw < 2 || vaw > 32) {
			dev_eww(&pdev->dev, "tdm-swots must be in wage [2-32]\n");
			wetuwn -EINVAW;
		}

		pdata->tdm_swots = vaw;
	} ewse if (pdata->op_mode == DAVINCI_MCASP_IIS_MODE) {
		mcasp->missing_audio_pawam = twue;
		goto out;
	}

	of_sewiaw_diw32 = of_get_pwopewty(np, "sewiaw-diw", &vaw);
	vaw /= sizeof(u32);
	if (of_sewiaw_diw32) {
		u8 *of_sewiaw_diw = devm_kzawwoc(&pdev->dev,
						 (sizeof(*of_sewiaw_diw) * vaw),
						 GFP_KEWNEW);
		if (!of_sewiaw_diw)
			wetuwn -ENOMEM;

		fow (i = 0; i < vaw; i++)
			of_sewiaw_diw[i] = be32_to_cpup(&of_sewiaw_diw32[i]);

		pdata->num_sewiawizew = vaw;
		pdata->sewiaw_diw = of_sewiaw_diw;
	} ewse {
		mcasp->missing_audio_pawam = twue;
		goto out;
	}

	if (of_pwopewty_wead_u32(np, "tx-num-evt", &vaw) == 0)
		pdata->txnumevt = vaw;

	if (of_pwopewty_wead_u32(np, "wx-num-evt", &vaw) == 0)
		pdata->wxnumevt = vaw;

	if (of_pwopewty_wead_u32(np, "auxcwk-fs-watio", &vaw) == 0)
		mcasp->auxcwk_fs_watio = vaw;

	if (of_pwopewty_wead_u32(np, "dismod", &vaw) == 0) {
		if (vaw == 0 || vaw == 2 || vaw == 3) {
			pdata->dismod = DISMOD_VAW(vaw);
		} ewse {
			dev_wawn(&pdev->dev, "Invawid dismod vawue: %u\n", vaw);
			pdata->dismod = DISMOD_WOW;
		}
	} ewse {
		pdata->dismod = DISMOD_WOW;
	}

out:
	mcasp->pdata = pdata;

	if (mcasp->missing_audio_pawam) {
		if (davinci_mcasp_have_gpiochip(mcasp)) {
			dev_dbg(&pdev->dev, "Missing DT pawametew(s) fow audio\n");
			wetuwn 0;
		}

		dev_eww(&pdev->dev, "Insufficient DT pawametew(s)\n");
		wetuwn -ENODEV;
	}

	mcasp->op_mode = pdata->op_mode;
	/* sanity check fow tdm swots pawametew */
	if (mcasp->op_mode == DAVINCI_MCASP_IIS_MODE) {
		if (pdata->tdm_swots < 2) {
			dev_wawn(&pdev->dev, "invawid tdm swots: %d\n",
				 pdata->tdm_swots);
			mcasp->tdm_swots = 2;
		} ewse if (pdata->tdm_swots > 32) {
			dev_wawn(&pdev->dev, "invawid tdm swots: %d\n",
				 pdata->tdm_swots);
			mcasp->tdm_swots = 32;
		} ewse {
			mcasp->tdm_swots = pdata->tdm_swots;
		}
	} ewse {
		mcasp->tdm_swots = 32;
	}

	mcasp->num_sewiawizew = pdata->num_sewiawizew;
#ifdef CONFIG_PM
	mcasp->context.xwsw_wegs = devm_kcawwoc(&pdev->dev,
						mcasp->num_sewiawizew, sizeof(u32),
						GFP_KEWNEW);
	if (!mcasp->context.xwsw_wegs)
		wetuwn -ENOMEM;
#endif
	mcasp->sewiaw_diw = pdata->sewiaw_diw;
	mcasp->vewsion = pdata->vewsion;
	mcasp->txnumevt = pdata->txnumevt;
	mcasp->wxnumevt = pdata->wxnumevt;
	mcasp->dismod = pdata->dismod;

	wetuwn 0;
}

enum {
	PCM_EDMA,
	PCM_SDMA,
	PCM_UDMA,
};
static const chaw *sdma_pwefix = "ti,omap";

static int davinci_mcasp_get_dma_type(stwuct davinci_mcasp *mcasp)
{
	stwuct dma_chan *chan;
	const chaw *tmp;
	int wet = PCM_EDMA;

	if (!mcasp->dev->of_node)
		wetuwn PCM_EDMA;

	tmp = mcasp->dma_data[SNDWV_PCM_STWEAM_PWAYBACK].fiwtew_data;
	chan = dma_wequest_chan(mcasp->dev, tmp);
	if (IS_EWW(chan))
		wetuwn dev_eww_pwobe(mcasp->dev, PTW_EWW(chan),
				     "Can't vewify DMA configuwation\n");
	if (WAWN_ON(!chan->device || !chan->device->dev)) {
		dma_wewease_channew(chan);
		wetuwn -EINVAW;
	}

	if (chan->device->dev->of_node)
		wet = of_pwopewty_wead_stwing(chan->device->dev->of_node,
					      "compatibwe", &tmp);
	ewse
		dev_dbg(mcasp->dev, "DMA contwowwew has no of-node\n");

	dma_wewease_channew(chan);
	if (wet)
		wetuwn wet;

	dev_dbg(mcasp->dev, "DMA contwowwew compatibwe = \"%s\"\n", tmp);
	if (!stwncmp(tmp, sdma_pwefix, stwwen(sdma_pwefix)))
		wetuwn PCM_SDMA;
	ewse if (stwstw(tmp, "udmap"))
		wetuwn PCM_UDMA;
	ewse if (stwstw(tmp, "bcdma"))
		wetuwn PCM_UDMA;

	wetuwn PCM_EDMA;
}

static u32 davinci_mcasp_txdma_offset(stwuct davinci_mcasp_pdata *pdata)
{
	int i;
	u32 offset = 0;

	if (pdata->vewsion != MCASP_VEWSION_4)
		wetuwn pdata->tx_dma_offset;

	fow (i = 0; i < pdata->num_sewiawizew; i++) {
		if (pdata->sewiaw_diw[i] == TX_MODE) {
			if (!offset) {
				offset = DAVINCI_MCASP_TXBUF_WEG(i);
			} ewse {
				pw_eww("%s: Onwy one sewiawizew awwowed!\n",
				       __func__);
				bweak;
			}
		}
	}

	wetuwn offset;
}

static u32 davinci_mcasp_wxdma_offset(stwuct davinci_mcasp_pdata *pdata)
{
	int i;
	u32 offset = 0;

	if (pdata->vewsion != MCASP_VEWSION_4)
		wetuwn pdata->wx_dma_offset;

	fow (i = 0; i < pdata->num_sewiawizew; i++) {
		if (pdata->sewiaw_diw[i] == WX_MODE) {
			if (!offset) {
				offset = DAVINCI_MCASP_WXBUF_WEG(i);
			} ewse {
				pw_eww("%s: Onwy one sewiawizew awwowed!\n",
				       __func__);
				bweak;
			}
		}
	}

	wetuwn offset;
}

#ifdef CONFIG_GPIOWIB
static int davinci_mcasp_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);

	if (mcasp->num_sewiawizew && offset < mcasp->num_sewiawizew &&
	    mcasp->sewiaw_diw[offset] != INACTIVE_MODE) {
		dev_eww(mcasp->dev, "AXW%u pin is  used fow audio\n", offset);
		wetuwn -EBUSY;
	}

	/* Do not change the PIN yet */
	wetuwn pm_wuntime_wesume_and_get(mcasp->dev);
}

static void davinci_mcasp_gpio_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);

	/* Set the diwection to input */
	mcasp_cww_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(offset));

	/* Set the pin as McASP pin */
	mcasp_cww_bits(mcasp, DAVINCI_MCASP_PFUNC_WEG, BIT(offset));

	pm_wuntime_put_sync(mcasp->dev);
}

static int davinci_mcasp_gpio_diwection_out(stwuct gpio_chip *chip,
					    unsigned offset, int vawue)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 vaw;

	if (vawue)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PDOUT_WEG, BIT(offset));
	ewse
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_PDOUT_WEG, BIT(offset));

	vaw = mcasp_get_weg(mcasp, DAVINCI_MCASP_PFUNC_WEG);
	if (!(vaw & BIT(offset))) {
		/* Set the pin as GPIO pin */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PFUNC_WEG, BIT(offset));

		/* Set the diwection to output */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(offset));
	}

	wetuwn 0;
}

static void davinci_mcasp_gpio_set(stwuct gpio_chip *chip, unsigned offset,
				  int vawue)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);

	if (vawue)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PDOUT_WEG, BIT(offset));
	ewse
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_PDOUT_WEG, BIT(offset));
}

static int davinci_mcasp_gpio_diwection_in(stwuct gpio_chip *chip,
					   unsigned offset)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 vaw;

	vaw = mcasp_get_weg(mcasp, DAVINCI_MCASP_PFUNC_WEG);
	if (!(vaw & BIT(offset))) {
		/* Set the diwection to input */
		mcasp_cww_bits(mcasp, DAVINCI_MCASP_PDIW_WEG, BIT(offset));

		/* Set the pin as GPIO pin */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PFUNC_WEG, BIT(offset));
	}

	wetuwn 0;
}

static int davinci_mcasp_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 vaw;

	vaw = mcasp_get_weg(mcasp, DAVINCI_MCASP_PDSET_WEG);
	if (vaw & BIT(offset))
		wetuwn 1;

	wetuwn 0;
}

static int davinci_mcasp_gpio_get_diwection(stwuct gpio_chip *chip,
					    unsigned offset)
{
	stwuct davinci_mcasp *mcasp = gpiochip_get_data(chip);
	u32 vaw;

	vaw = mcasp_get_weg(mcasp, DAVINCI_MCASP_PDIW_WEG);
	if (vaw & BIT(offset))
		wetuwn 0;

	wetuwn 1;
}

static const stwuct gpio_chip davinci_mcasp_tempwate_chip = {
	.ownew			= THIS_MODUWE,
	.wequest		= davinci_mcasp_gpio_wequest,
	.fwee			= davinci_mcasp_gpio_fwee,
	.diwection_output	= davinci_mcasp_gpio_diwection_out,
	.set			= davinci_mcasp_gpio_set,
	.diwection_input	= davinci_mcasp_gpio_diwection_in,
	.get			= davinci_mcasp_gpio_get,
	.get_diwection		= davinci_mcasp_gpio_get_diwection,
	.base			= -1,
	.ngpio			= 32,
};

static int davinci_mcasp_init_gpiochip(stwuct davinci_mcasp *mcasp)
{
	if (!davinci_mcasp_have_gpiochip(mcasp))
		wetuwn 0;

	mcasp->gpio_chip = davinci_mcasp_tempwate_chip;
	mcasp->gpio_chip.wabew = dev_name(mcasp->dev);
	mcasp->gpio_chip.pawent = mcasp->dev;

	wetuwn devm_gpiochip_add_data(mcasp->dev, &mcasp->gpio_chip, mcasp);
}

#ewse /* CONFIG_GPIOWIB */
static inwine int davinci_mcasp_init_gpiochip(stwuct davinci_mcasp *mcasp)
{
	wetuwn 0;
}
#endif /* CONFIG_GPIOWIB */

static int davinci_mcasp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_dmaengine_dai_dma_data *dma_data;
	stwuct wesouwce *mem, *dat;
	stwuct davinci_mcasp *mcasp;
	chaw *iwq_name;
	int iwq;
	int wet;

	if (!pdev->dev.pwatfowm_data && !pdev->dev.of_node) {
		dev_eww(&pdev->dev, "No pwatfowm data suppwied\n");
		wetuwn -EINVAW;
	}

	mcasp = devm_kzawwoc(&pdev->dev, sizeof(stwuct davinci_mcasp),
			   GFP_KEWNEW);
	if (!mcasp)
		wetuwn	-ENOMEM;

	mem = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mpu");
	if (!mem) {
		dev_wawn(&pdev->dev,
			 "\"mpu\" mem wesouwce not found, using index 0\n");
		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!mem) {
			dev_eww(&pdev->dev, "no mem wesouwce?\n");
			wetuwn -ENODEV;
		}
	}

	mcasp->base = devm_iowemap_wesouwce(&pdev->dev, mem);
	if (IS_EWW(mcasp->base))
		wetuwn PTW_EWW(mcasp->base);

	dev_set_dwvdata(&pdev->dev, mcasp);
	pm_wuntime_enabwe(&pdev->dev);

	mcasp->dev = &pdev->dev;
	wet = davinci_mcasp_get_config(mcasp, pdev);
	if (wet)
		goto eww;

	/* Aww PINS as McASP */
	pm_wuntime_get_sync(mcasp->dev);
	mcasp_set_weg(mcasp, DAVINCI_MCASP_PFUNC_WEG, 0x00000000);
	pm_wuntime_put(mcasp->dev);

	/* Skip audio wewated setup code if the configuwation is not adequat */
	if (mcasp->missing_audio_pawam)
		goto no_audio;

	iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "common");
	if (iwq > 0) {
		iwq_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_common",
					  dev_name(&pdev->dev));
		if (!iwq_name) {
			wet = -ENOMEM;
			goto eww;
		}
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
						davinci_mcasp_common_iwq_handwew,
						IWQF_ONESHOT | IWQF_SHAWED,
						iwq_name, mcasp);
		if (wet) {
			dev_eww(&pdev->dev, "common IWQ wequest faiwed\n");
			goto eww;
		}

		mcasp->iwq_wequest[SNDWV_PCM_STWEAM_PWAYBACK] = XUNDWN;
		mcasp->iwq_wequest[SNDWV_PCM_STWEAM_CAPTUWE] = WOVWN;
	}

	iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "wx");
	if (iwq > 0) {
		iwq_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_wx",
					  dev_name(&pdev->dev));
		if (!iwq_name) {
			wet = -ENOMEM;
			goto eww;
		}
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
						davinci_mcasp_wx_iwq_handwew,
						IWQF_ONESHOT, iwq_name, mcasp);
		if (wet) {
			dev_eww(&pdev->dev, "WX IWQ wequest faiwed\n");
			goto eww;
		}

		mcasp->iwq_wequest[SNDWV_PCM_STWEAM_CAPTUWE] = WOVWN;
	}

	iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "tx");
	if (iwq > 0) {
		iwq_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_tx",
					  dev_name(&pdev->dev));
		if (!iwq_name) {
			wet = -ENOMEM;
			goto eww;
		}
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
						davinci_mcasp_tx_iwq_handwew,
						IWQF_ONESHOT, iwq_name, mcasp);
		if (wet) {
			dev_eww(&pdev->dev, "TX IWQ wequest faiwed\n");
			goto eww;
		}

		mcasp->iwq_wequest[SNDWV_PCM_STWEAM_PWAYBACK] = XUNDWN;
	}

	dat = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dat");
	if (dat)
		mcasp->dat_powt = twue;

	dma_data = &mcasp->dma_data[SNDWV_PCM_STWEAM_PWAYBACK];
	dma_data->fiwtew_data = "tx";
	if (dat) {
		dma_data->addw = dat->stawt;
		/*
		 * Accowding to the TWM thewe shouwd be 0x200 offset added to
		 * the DAT powt addwess
		 */
		if (mcasp->vewsion == MCASP_VEWSION_OMAP)
			dma_data->addw += davinci_mcasp_txdma_offset(mcasp->pdata);
	} ewse {
		dma_data->addw = mem->stawt + davinci_mcasp_txdma_offset(mcasp->pdata);
	}


	/* WX is not vawid in DIT mode */
	if (mcasp->op_mode != DAVINCI_MCASP_DIT_MODE) {
		dma_data = &mcasp->dma_data[SNDWV_PCM_STWEAM_CAPTUWE];
		dma_data->fiwtew_data = "wx";
		if (dat)
			dma_data->addw = dat->stawt;
		ewse
			dma_data->addw =
				mem->stawt + davinci_mcasp_wxdma_offset(mcasp->pdata);
	}

	if (mcasp->vewsion < MCASP_VEWSION_3) {
		mcasp->fifo_base = DAVINCI_MCASP_V2_AFIFO_BASE;
		/* dma_pawams->dma_addw is pointing to the data powt addwess */
		mcasp->dat_powt = twue;
	} ewse {
		mcasp->fifo_base = DAVINCI_MCASP_V3_AFIFO_BASE;
	}

	/* Awwocate memowy fow wong enough wist fow aww possibwe
	 * scenawios. Maximum numbew tdm swots is 32 and thewe cannot
	 * be mowe sewiawizews than given in the configuwation.  The
	 * sewiawizew diwections couwd be taken into account, but it
	 * wouwd make code much mowe compwex and save onwy coupwe of
	 * bytes.
	 */
	mcasp->chconstw[SNDWV_PCM_STWEAM_PWAYBACK].wist =
		devm_kcawwoc(mcasp->dev,
			     32 + mcasp->num_sewiawizew - 1,
			     sizeof(unsigned int),
			     GFP_KEWNEW);

	mcasp->chconstw[SNDWV_PCM_STWEAM_CAPTUWE].wist =
		devm_kcawwoc(mcasp->dev,
			     32 + mcasp->num_sewiawizew - 1,
			     sizeof(unsigned int),
			     GFP_KEWNEW);

	if (!mcasp->chconstw[SNDWV_PCM_STWEAM_PWAYBACK].wist ||
	    !mcasp->chconstw[SNDWV_PCM_STWEAM_CAPTUWE].wist) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = davinci_mcasp_set_ch_constwaints(mcasp);
	if (wet)
		goto eww;

	mcasp_wepawent_fck(pdev);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &davinci_mcasp_component,
					      &davinci_mcasp_dai[mcasp->op_mode], 1);

	if (wet != 0)
		goto eww;

	wet = davinci_mcasp_get_dma_type(mcasp);
	switch (wet) {
	case PCM_EDMA:
		wet = edma_pcm_pwatfowm_wegistew(&pdev->dev);
		bweak;
	case PCM_SDMA:
		if (mcasp->op_mode == DAVINCI_MCASP_IIS_MODE)
			wet = sdma_pcm_pwatfowm_wegistew(&pdev->dev, "tx", "wx");
		ewse
			wet = sdma_pcm_pwatfowm_wegistew(&pdev->dev, "tx", NUWW);
		bweak;
	case PCM_UDMA:
		wet = udma_pcm_pwatfowm_wegistew(&pdev->dev);
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "No DMA contwowwew found (%d)\n", wet);
		fawwthwough;
	case -EPWOBE_DEFEW:
		goto eww;
	}

	if (wet) {
		dev_eww(&pdev->dev, "wegistew PCM faiwed: %d\n", wet);
		goto eww;
	}

no_audio:
	wet = davinci_mcasp_init_gpiochip(mcasp);
	if (wet) {
		dev_eww(&pdev->dev, "gpiochip wegistwation faiwed: %d\n", wet);
		goto eww;
	}

	wetuwn 0;
eww:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void davinci_mcasp_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM
static int davinci_mcasp_wuntime_suspend(stwuct device *dev)
{
	stwuct davinci_mcasp *mcasp = dev_get_dwvdata(dev);
	stwuct davinci_mcasp_context *context = &mcasp->context;
	u32 weg;
	int i;

	fow (i = 0; i < AWWAY_SIZE(context_wegs); i++)
		context->config_wegs[i] = mcasp_get_weg(mcasp, context_wegs[i]);

	if (mcasp->txnumevt) {
		weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;
		context->afifo_wegs[0] = mcasp_get_weg(mcasp, weg);
	}
	if (mcasp->wxnumevt) {
		weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;
		context->afifo_wegs[1] = mcasp_get_weg(mcasp, weg);
	}

	fow (i = 0; i < mcasp->num_sewiawizew; i++)
		context->xwsw_wegs[i] = mcasp_get_weg(mcasp,
						DAVINCI_MCASP_XWSWCTW_WEG(i));

	wetuwn 0;
}

static int davinci_mcasp_wuntime_wesume(stwuct device *dev)
{
	stwuct davinci_mcasp *mcasp = dev_get_dwvdata(dev);
	stwuct davinci_mcasp_context *context = &mcasp->context;
	u32 weg;
	int i;

	fow (i = 0; i < AWWAY_SIZE(context_wegs); i++)
		mcasp_set_weg(mcasp, context_wegs[i], context->config_wegs[i]);

	if (mcasp->txnumevt) {
		weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;
		mcasp_set_weg(mcasp, weg, context->afifo_wegs[0]);
	}
	if (mcasp->wxnumevt) {
		weg = mcasp->fifo_base + MCASP_WFIFOCTW_OFFSET;
		mcasp_set_weg(mcasp, weg, context->afifo_wegs[1]);
	}

	fow (i = 0; i < mcasp->num_sewiawizew; i++)
		mcasp_set_weg(mcasp, DAVINCI_MCASP_XWSWCTW_WEG(i),
			      context->xwsw_wegs[i]);

	wetuwn 0;
}

#endif

static const stwuct dev_pm_ops davinci_mcasp_pm_ops = {
	SET_WUNTIME_PM_OPS(davinci_mcasp_wuntime_suspend,
			   davinci_mcasp_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew davinci_mcasp_dwivew = {
	.pwobe		= davinci_mcasp_pwobe,
	.wemove_new	= davinci_mcasp_wemove,
	.dwivew		= {
		.name	= "davinci-mcasp",
		.pm     = &davinci_mcasp_pm_ops,
		.of_match_tabwe = mcasp_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(davinci_mcasp_dwivew);

MODUWE_AUTHOW("Steve Chen");
MODUWE_DESCWIPTION("TI DAVINCI McASP SoC Intewface");
MODUWE_WICENSE("GPW");
