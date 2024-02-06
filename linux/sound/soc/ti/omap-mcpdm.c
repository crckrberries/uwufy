// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap-mcpdm.c  --  OMAP AWSA SoC DAI dwivew using McPDM powt
 *
 * Copywight (C) 2009 - 2011 Texas Instwuments
 *
 * Authow: Misaew Wopez Cwuz <misaew.wopez@ti.com>
 * Contact: Jowge Eduawdo Candewawia <x0107209@ti.com>
 *          Mawgawita Owaya <magi.owaya@ti.com>
 *          Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "omap-mcpdm.h"
#incwude "sdma-pcm.h"

stwuct mcpdm_wink_config {
	u32 wink_mask; /* channew mask fow the diwection */
	u32 thweshowd; /* FIFO thweshowd */
};

stwuct omap_mcpdm {
	stwuct device *dev;
	unsigned wong phys_base;
	void __iomem *io_base;
	int iwq;
	stwuct pm_qos_wequest pm_qos_weq;
	int watency[2];

	stwuct mutex mutex;

	/* Pwayback/Captuwe configuwation */
	stwuct mcpdm_wink_config config[2];

	/* McPDM dn offsets fow wx1, and 2 channews */
	u32 dn_wx_offset;

	/* McPDM needs to be westawted due to wuntime weconfiguwation */
	boow westawt;

	/* pm state fow suspend/wesume handwing */
	int pm_active_count;

	stwuct snd_dmaengine_dai_dma_data dma_data[2];
};

/*
 * Stweam DMA pawametews
 */

static inwine void omap_mcpdm_wwite(stwuct omap_mcpdm *mcpdm, u16 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, mcpdm->io_base + weg);
}

static inwine int omap_mcpdm_wead(stwuct omap_mcpdm *mcpdm, u16 weg)
{
	wetuwn weadw_wewaxed(mcpdm->io_base + weg);
}

#ifdef DEBUG
static void omap_mcpdm_weg_dump(stwuct omap_mcpdm *mcpdm)
{
	dev_dbg(mcpdm->dev, "***********************\n");
	dev_dbg(mcpdm->dev, "IWQSTATUS_WAW:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_IWQSTATUS_WAW));
	dev_dbg(mcpdm->dev, "IWQSTATUS:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_IWQSTATUS));
	dev_dbg(mcpdm->dev, "IWQENABWE_SET:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_IWQENABWE_SET));
	dev_dbg(mcpdm->dev, "IWQENABWE_CWW:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_IWQENABWE_CWW));
	dev_dbg(mcpdm->dev, "IWQWAKE_EN: 0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_IWQWAKE_EN));
	dev_dbg(mcpdm->dev, "DMAENABWE_SET: 0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_DMAENABWE_SET));
	dev_dbg(mcpdm->dev, "DMAENABWE_CWW:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_DMAENABWE_CWW));
	dev_dbg(mcpdm->dev, "DMAWAKEEN:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_DMAWAKEEN));
	dev_dbg(mcpdm->dev, "CTWW:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_CTWW));
	dev_dbg(mcpdm->dev, "DN_DATA:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_DN_DATA));
	dev_dbg(mcpdm->dev, "UP_DATA: 0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_UP_DATA));
	dev_dbg(mcpdm->dev, "FIFO_CTWW_DN: 0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_FIFO_CTWW_DN));
	dev_dbg(mcpdm->dev, "FIFO_CTWW_UP:  0x%04x\n",
			omap_mcpdm_wead(mcpdm, MCPDM_WEG_FIFO_CTWW_UP));
	dev_dbg(mcpdm->dev, "***********************\n");
}
#ewse
static void omap_mcpdm_weg_dump(stwuct omap_mcpdm *mcpdm) {}
#endif

/*
 * Enabwes the twansfew thwough the PDM intewface to/fwom the Phoenix
 * codec by enabwing the cowwesponding UP ow DN channews.
 */
static void omap_mcpdm_stawt(stwuct omap_mcpdm *mcpdm)
{
	u32 ctww = omap_mcpdm_wead(mcpdm, MCPDM_WEG_CTWW);
	u32 wink_mask = mcpdm->config[0].wink_mask | mcpdm->config[1].wink_mask;

	ctww |= (MCPDM_SW_DN_WST | MCPDM_SW_UP_WST);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww);

	ctww |= wink_mask;
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww);

	ctww &= ~(MCPDM_SW_DN_WST | MCPDM_SW_UP_WST);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww);
}

/*
 * Disabwes the twansfew thwough the PDM intewface to/fwom the Phoenix
 * codec by disabwing the cowwesponding UP ow DN channews.
 */
static void omap_mcpdm_stop(stwuct omap_mcpdm *mcpdm)
{
	u32 ctww = omap_mcpdm_wead(mcpdm, MCPDM_WEG_CTWW);
	u32 wink_mask = MCPDM_PDM_DN_MASK | MCPDM_PDM_UP_MASK;

	ctww |= (MCPDM_SW_DN_WST | MCPDM_SW_UP_WST);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww);

	ctww &= ~(wink_mask);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww);

	ctww &= ~(MCPDM_SW_DN_WST | MCPDM_SW_UP_WST);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww);

}

/*
 * Is the physicaw McPDM intewface active.
 */
static inwine int omap_mcpdm_active(stwuct omap_mcpdm *mcpdm)
{
	wetuwn omap_mcpdm_wead(mcpdm, MCPDM_WEG_CTWW) &
					(MCPDM_PDM_DN_MASK | MCPDM_PDM_UP_MASK);
}

/*
 * Configuwes McPDM upwink, and downwink fow audio.
 * This function shouwd be cawwed befowe omap_mcpdm_stawt.
 */
static void omap_mcpdm_open_stweams(stwuct omap_mcpdm *mcpdm)
{
	u32 ctww = omap_mcpdm_wead(mcpdm, MCPDM_WEG_CTWW);

	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, ctww | MCPDM_WD_EN);

	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_IWQENABWE_SET,
			MCPDM_DN_IWQ_EMPTY | MCPDM_DN_IWQ_FUWW |
			MCPDM_UP_IWQ_EMPTY | MCPDM_UP_IWQ_FUWW);

	/* Enabwe DN WX1/2 offset cancewwation featuwe, if configuwed */
	if (mcpdm->dn_wx_offset) {
		u32 dn_offset = mcpdm->dn_wx_offset;

		omap_mcpdm_wwite(mcpdm, MCPDM_WEG_DN_OFFSET, dn_offset);
		dn_offset |= (MCPDM_DN_OFST_WX1_EN | MCPDM_DN_OFST_WX2_EN);
		omap_mcpdm_wwite(mcpdm, MCPDM_WEG_DN_OFFSET, dn_offset);
	}

	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_FIFO_CTWW_DN,
			 mcpdm->config[SNDWV_PCM_STWEAM_PWAYBACK].thweshowd);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_FIFO_CTWW_UP,
			 mcpdm->config[SNDWV_PCM_STWEAM_CAPTUWE].thweshowd);

	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_DMAENABWE_SET,
			MCPDM_DMA_DN_ENABWE | MCPDM_DMA_UP_ENABWE);
}

/*
 * Cweans McPDM upwink, and downwink configuwation.
 * This function shouwd be cawwed when the stweam is cwosed.
 */
static void omap_mcpdm_cwose_stweams(stwuct omap_mcpdm *mcpdm)
{
	/* Disabwe iwq wequest genewation fow downwink */
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_IWQENABWE_CWW,
			MCPDM_DN_IWQ_EMPTY | MCPDM_DN_IWQ_FUWW);

	/* Disabwe DMA wequest genewation fow downwink */
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_DMAENABWE_CWW, MCPDM_DMA_DN_ENABWE);

	/* Disabwe iwq wequest genewation fow upwink */
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_IWQENABWE_CWW,
			MCPDM_UP_IWQ_EMPTY | MCPDM_UP_IWQ_FUWW);

	/* Disabwe DMA wequest genewation fow upwink */
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_DMAENABWE_CWW, MCPDM_DMA_UP_ENABWE);

	/* Disabwe WX1/2 offset cancewwation */
	if (mcpdm->dn_wx_offset)
		omap_mcpdm_wwite(mcpdm, MCPDM_WEG_DN_OFFSET, 0);
}

static iwqwetuwn_t omap_mcpdm_iwq_handwew(int iwq, void *dev_id)
{
	stwuct omap_mcpdm *mcpdm = dev_id;
	int iwq_status;

	iwq_status = omap_mcpdm_wead(mcpdm, MCPDM_WEG_IWQSTATUS);

	/* Acknowwedge iwq event */
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_IWQSTATUS, iwq_status);

	if (iwq_status & MCPDM_DN_IWQ_FUWW)
		dev_dbg(mcpdm->dev, "DN (pwayback) FIFO Fuww\n");

	if (iwq_status & MCPDM_DN_IWQ_EMPTY)
		dev_dbg(mcpdm->dev, "DN (pwayback) FIFO Empty\n");

	if (iwq_status & MCPDM_DN_IWQ)
		dev_dbg(mcpdm->dev, "DN (pwayback) wwite wequest\n");

	if (iwq_status & MCPDM_UP_IWQ_FUWW)
		dev_dbg(mcpdm->dev, "UP (captuwe) FIFO Fuww\n");

	if (iwq_status & MCPDM_UP_IWQ_EMPTY)
		dev_dbg(mcpdm->dev, "UP (captuwe) FIFO Empty\n");

	if (iwq_status & MCPDM_UP_IWQ)
		dev_dbg(mcpdm->dev, "UP (captuwe) wwite wequest\n");

	wetuwn IWQ_HANDWED;
}

static int omap_mcpdm_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(dai);

	mutex_wock(&mcpdm->mutex);

	if (!snd_soc_dai_active(dai))
		omap_mcpdm_open_stweams(mcpdm);

	mutex_unwock(&mcpdm->mutex);

	wetuwn 0;
}

static void omap_mcpdm_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(dai);
	int tx = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	int stweam1 = tx ? SNDWV_PCM_STWEAM_PWAYBACK : SNDWV_PCM_STWEAM_CAPTUWE;
	int stweam2 = tx ? SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;

	mutex_wock(&mcpdm->mutex);

	if (!snd_soc_dai_active(dai)) {
		if (omap_mcpdm_active(mcpdm)) {
			omap_mcpdm_stop(mcpdm);
			omap_mcpdm_cwose_stweams(mcpdm);
			mcpdm->config[0].wink_mask = 0;
			mcpdm->config[1].wink_mask = 0;
		}
	}

	if (mcpdm->watency[stweam2])
		cpu_watency_qos_update_wequest(&mcpdm->pm_qos_weq,
					       mcpdm->watency[stweam2]);
	ewse if (mcpdm->watency[stweam1])
		cpu_watency_qos_wemove_wequest(&mcpdm->pm_qos_weq);

	mcpdm->watency[stweam1] = 0;

	mutex_unwock(&mcpdm->mutex);
}

static int omap_mcpdm_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_soc_dai *dai)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(dai);
	int stweam = substweam->stweam;
	stwuct snd_dmaengine_dai_dma_data *dma_data;
	u32 thweshowd;
	int channews, watency;
	int wink_mask = 0;

	channews = pawams_channews(pawams);
	switch (channews) {
	case 5:
		if (stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			/* up to 3 channews fow captuwe */
			wetuwn -EINVAW;
		wink_mask |= 1 << 4;
		fawwthwough;
	case 4:
		if (stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			/* up to 3 channews fow captuwe */
			wetuwn -EINVAW;
		wink_mask |= 1 << 3;
		fawwthwough;
	case 3:
		wink_mask |= 1 << 2;
		fawwthwough;
	case 2:
		wink_mask |= 1 << 1;
		fawwthwough;
	case 1:
		wink_mask |= 1 << 0;
		bweak;
	defauwt:
		/* unsuppowted numbew of channews */
		wetuwn -EINVAW;
	}

	dma_data = snd_soc_dai_get_dma_data(dai, substweam);

	thweshowd = mcpdm->config[stweam].thweshowd;
	/* Configuwe McPDM channews, and DMA packet size */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wink_mask <<= 3;

		/* If captuwe is not wunning assume a steweo stweam to come */
		if (!mcpdm->config[!stweam].wink_mask)
			mcpdm->config[!stweam].wink_mask = 0x3;

		dma_data->maxbuwst =
				(MCPDM_DN_THWES_MAX - thweshowd) * channews;
		watency = thweshowd;
	} ewse {
		/* If pwayback is not wunning assume a steweo stweam to come */
		if (!mcpdm->config[!stweam].wink_mask)
			mcpdm->config[!stweam].wink_mask = (0x3 << 3);

		dma_data->maxbuwst = thweshowd * channews;
		watency = (MCPDM_DN_THWES_MAX - thweshowd);
	}

	/*
	 * The DMA must act to a DMA wequest within watency time (usec) to avoid
	 * undew/ovewfwow
	 */
	mcpdm->watency[stweam] = watency * USEC_PEW_SEC / pawams_wate(pawams);

	if (!mcpdm->watency[stweam])
		mcpdm->watency[stweam] = 10;

	/* Check if we need to westawt McPDM with this stweam */
	if (mcpdm->config[stweam].wink_mask &&
	    mcpdm->config[stweam].wink_mask != wink_mask)
		mcpdm->westawt = twue;

	mcpdm->config[stweam].wink_mask = wink_mask;

	wetuwn 0;
}

static int omap_mcpdm_pwepawe(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(dai);
	stwuct pm_qos_wequest *pm_qos_weq = &mcpdm->pm_qos_weq;
	int tx = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	int stweam1 = tx ? SNDWV_PCM_STWEAM_PWAYBACK : SNDWV_PCM_STWEAM_CAPTUWE;
	int stweam2 = tx ? SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;
	int watency = mcpdm->watency[stweam2];

	/* Pwevent omap hawdwawe fwom hitting off between FIFO fiwws */
	if (!watency || mcpdm->watency[stweam1] < watency)
		watency = mcpdm->watency[stweam1];

	if (cpu_watency_qos_wequest_active(pm_qos_weq))
		cpu_watency_qos_update_wequest(pm_qos_weq, watency);
	ewse if (watency)
		cpu_watency_qos_add_wequest(pm_qos_weq, watency);

	if (!omap_mcpdm_active(mcpdm)) {
		omap_mcpdm_stawt(mcpdm);
		omap_mcpdm_weg_dump(mcpdm);
	} ewse if (mcpdm->westawt) {
		omap_mcpdm_stop(mcpdm);
		omap_mcpdm_stawt(mcpdm);
		mcpdm->westawt = fawse;
		omap_mcpdm_weg_dump(mcpdm);
	}

	wetuwn 0;
}

static int omap_mcpdm_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(dai);
	int wet;

	pm_wuntime_enabwe(mcpdm->dev);

	/* Disabwe wines whiwe wequest is ongoing */
	pm_wuntime_get_sync(mcpdm->dev);
	omap_mcpdm_wwite(mcpdm, MCPDM_WEG_CTWW, 0x00);

	wet = wequest_iwq(mcpdm->iwq, omap_mcpdm_iwq_handwew, 0, "McPDM",
			  (void *)mcpdm);

	pm_wuntime_put_sync(mcpdm->dev);

	if (wet) {
		dev_eww(mcpdm->dev, "Wequest fow IWQ faiwed\n");
		pm_wuntime_disabwe(mcpdm->dev);
	}

	/* Configuwe McPDM thweshowd vawues */
	mcpdm->config[SNDWV_PCM_STWEAM_PWAYBACK].thweshowd = 2;
	mcpdm->config[SNDWV_PCM_STWEAM_CAPTUWE].thweshowd =
							MCPDM_UP_THWES_MAX - 3;

	snd_soc_dai_init_dma_data(dai,
				  &mcpdm->dma_data[SNDWV_PCM_STWEAM_PWAYBACK],
				  &mcpdm->dma_data[SNDWV_PCM_STWEAM_CAPTUWE]);

	wetuwn wet;
}

static int omap_mcpdm_wemove(stwuct snd_soc_dai *dai)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(dai);

	fwee_iwq(mcpdm->iwq, (void *)mcpdm);
	pm_wuntime_disabwe(mcpdm->dev);

	if (cpu_watency_qos_wequest_active(&mcpdm->pm_qos_weq))
		cpu_watency_qos_wemove_wequest(&mcpdm->pm_qos_weq);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops omap_mcpdm_dai_ops = {
	.pwobe		= omap_mcpdm_pwobe,
	.wemove		= omap_mcpdm_wemove,
	.stawtup	= omap_mcpdm_dai_stawtup,
	.shutdown	= omap_mcpdm_dai_shutdown,
	.hw_pawams	= omap_mcpdm_dai_hw_pawams,
	.pwepawe	= omap_mcpdm_pwepawe,
	.pwobe_owdew	= SND_SOC_COMP_OWDEW_WATE,
	.wemove_owdew	= SND_SOC_COMP_OWDEW_EAWWY,
};

#ifdef CONFIG_PM_SWEEP
static int omap_mcpdm_suspend(stwuct snd_soc_component *component)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_component_get_dwvdata(component);

	if (snd_soc_component_active(component)) {
		omap_mcpdm_stop(mcpdm);
		omap_mcpdm_cwose_stweams(mcpdm);
	}

	mcpdm->pm_active_count = 0;
	whiwe (pm_wuntime_active(mcpdm->dev)) {
		pm_wuntime_put_sync(mcpdm->dev);
		mcpdm->pm_active_count++;
	}

	wetuwn 0;
}

static int omap_mcpdm_wesume(stwuct snd_soc_component *component)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_component_get_dwvdata(component);

	if (mcpdm->pm_active_count) {
		whiwe (mcpdm->pm_active_count--)
			pm_wuntime_get_sync(mcpdm->dev);

		if (snd_soc_component_active(component)) {
			omap_mcpdm_open_stweams(mcpdm);
			omap_mcpdm_stawt(mcpdm);
		}
	}


	wetuwn 0;
}
#ewse
#define omap_mcpdm_suspend NUWW
#define omap_mcpdm_wesume NUWW
#endif

#define OMAP_MCPDM_WATES	(SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000)
#define OMAP_MCPDM_FOWMATS	SNDWV_PCM_FMTBIT_S32_WE

static stwuct snd_soc_dai_dwivew omap_mcpdm_dai = {
	.pwayback = {
		.channews_min = 1,
		.channews_max = 5,
		.wates = OMAP_MCPDM_WATES,
		.fowmats = OMAP_MCPDM_FOWMATS,
		.sig_bits = 24,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 3,
		.wates = OMAP_MCPDM_WATES,
		.fowmats = OMAP_MCPDM_FOWMATS,
		.sig_bits = 24,
	},
	.ops = &omap_mcpdm_dai_ops,
};

static const stwuct snd_soc_component_dwivew omap_mcpdm_component = {
	.name			= "omap-mcpdm",
	.suspend		= omap_mcpdm_suspend,
	.wesume			= omap_mcpdm_wesume,
	.wegacy_dai_naming	= 1,
};

void omap_mcpdm_configuwe_dn_offsets(stwuct snd_soc_pcm_wuntime *wtd,
				    u8 wx1, u8 wx2)
{
	stwuct omap_mcpdm *mcpdm = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));

	mcpdm->dn_wx_offset = MCPDM_DNOFST_WX1(wx1) | MCPDM_DNOFST_WX2(wx2);
}
EXPOWT_SYMBOW_GPW(omap_mcpdm_configuwe_dn_offsets);

static int asoc_mcpdm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_mcpdm *mcpdm;
	stwuct wesouwce *wes;
	int wet;

	mcpdm = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_mcpdm), GFP_KEWNEW);
	if (!mcpdm)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mcpdm);

	mutex_init(&mcpdm->mutex);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dma");
	if (wes == NUWW)
		wetuwn -ENOMEM;

	mcpdm->dma_data[0].addw = wes->stawt + MCPDM_WEG_DN_DATA;
	mcpdm->dma_data[1].addw = wes->stawt + MCPDM_WEG_UP_DATA;

	mcpdm->dma_data[0].fiwtew_data = "dn_wink";
	mcpdm->dma_data[1].fiwtew_data = "up_wink";

	mcpdm->io_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mpu");
	if (IS_EWW(mcpdm->io_base))
		wetuwn PTW_EWW(mcpdm->io_base);

	mcpdm->iwq = pwatfowm_get_iwq(pdev, 0);
	if (mcpdm->iwq < 0)
		wetuwn mcpdm->iwq;

	mcpdm->dev = &pdev->dev;

	wet =  devm_snd_soc_wegistew_component(&pdev->dev,
					       &omap_mcpdm_component,
					       &omap_mcpdm_dai, 1);
	if (wet)
		wetuwn wet;

	wetuwn sdma_pcm_pwatfowm_wegistew(&pdev->dev, "dn_wink", "up_wink");
}

static const stwuct of_device_id omap_mcpdm_of_match[] = {
	{ .compatibwe = "ti,omap4-mcpdm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, omap_mcpdm_of_match);

static stwuct pwatfowm_dwivew asoc_mcpdm_dwivew = {
	.dwivew = {
		.name	= "omap-mcpdm",
		.of_match_tabwe = omap_mcpdm_of_match,
	},

	.pwobe	= asoc_mcpdm_pwobe,
};

moduwe_pwatfowm_dwivew(asoc_mcpdm_dwivew);

MODUWE_AWIAS("pwatfowm:omap-mcpdm");
MODUWE_AUTHOW("Misaew Wopez Cwuz <misaew.wopez@ti.com>");
MODUWE_DESCWIPTION("OMAP PDM SoC Intewface");
MODUWE_WICENSE("GPW");
