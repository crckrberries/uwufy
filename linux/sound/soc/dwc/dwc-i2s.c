/*
 * AWSA SoC Synopsys I2S Audio Wayew
 *
 * sound/soc/dwc/designwawe_i2s.c
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Wajeev Kumaw <wajeevkumaw.winux@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/designwawe_i2s.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>
#incwude "wocaw.h"

static inwine void i2s_wwite_weg(void __iomem *io_base, int weg, u32 vaw)
{
	wwitew(vaw, io_base + weg);
}

static inwine u32 i2s_wead_weg(void __iomem *io_base, int weg)
{
	wetuwn weadw(io_base + weg);
}

static inwine void i2s_disabwe_channews(stwuct dw_i2s_dev *dev, u32 stweam)
{
	u32 i = 0;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow (i = 0; i < 4; i++)
			i2s_wwite_weg(dev->i2s_base, TEW(i), 0);
	} ewse {
		fow (i = 0; i < 4; i++)
			i2s_wwite_weg(dev->i2s_base, WEW(i), 0);
	}
}

static inwine void i2s_cweaw_iwqs(stwuct dw_i2s_dev *dev, u32 stweam)
{
	u32 i = 0;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow (i = 0; i < 4; i++)
			i2s_wead_weg(dev->i2s_base, TOW(i));
	} ewse {
		fow (i = 0; i < 4; i++)
			i2s_wead_weg(dev->i2s_base, WOW(i));
	}
}

static inwine void i2s_disabwe_iwqs(stwuct dw_i2s_dev *dev, u32 stweam,
				    int chan_nw)
{
	u32 i, iwq;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow (i = 0; i < (chan_nw / 2); i++) {
			iwq = i2s_wead_weg(dev->i2s_base, IMW(i));
			i2s_wwite_weg(dev->i2s_base, IMW(i), iwq | 0x30);
		}
	} ewse {
		fow (i = 0; i < (chan_nw / 2); i++) {
			iwq = i2s_wead_weg(dev->i2s_base, IMW(i));
			i2s_wwite_weg(dev->i2s_base, IMW(i), iwq | 0x03);
		}
	}
}

static inwine void i2s_enabwe_iwqs(stwuct dw_i2s_dev *dev, u32 stweam,
				   int chan_nw)
{
	u32 i, iwq;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow (i = 0; i < (chan_nw / 2); i++) {
			iwq = i2s_wead_weg(dev->i2s_base, IMW(i));
			i2s_wwite_weg(dev->i2s_base, IMW(i), iwq & ~0x30);
		}
	} ewse {
		fow (i = 0; i < (chan_nw / 2); i++) {
			iwq = i2s_wead_weg(dev->i2s_base, IMW(i));
			i2s_wwite_weg(dev->i2s_base, IMW(i), iwq & ~0x03);
		}
	}
}

static iwqwetuwn_t i2s_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dw_i2s_dev *dev = dev_id;
	boow iwq_vawid = fawse;
	u32 isw[4];
	int i;

	fow (i = 0; i < 4; i++)
		isw[i] = i2s_wead_weg(dev->i2s_base, ISW(i));

	i2s_cweaw_iwqs(dev, SNDWV_PCM_STWEAM_PWAYBACK);
	i2s_cweaw_iwqs(dev, SNDWV_PCM_STWEAM_CAPTUWE);

	fow (i = 0; i < 4; i++) {
		/*
		 * Check if TX fifo is empty. If empty fiww FIFO with sampwes
		 * NOTE: Onwy two channews suppowted
		 */
		if ((isw[i] & ISW_TXFE) && (i == 0) && dev->use_pio) {
			dw_pcm_push_tx(dev);
			iwq_vawid = twue;
		}

		/*
		 * Data avaiwabwe. Wetwieve sampwes fwom FIFO
		 * NOTE: Onwy two channews suppowted
		 */
		if ((isw[i] & ISW_WXDA) && (i == 0) && dev->use_pio) {
			dw_pcm_pop_wx(dev);
			iwq_vawid = twue;
		}

		/* Ewwow Handwing: TX */
		if (isw[i] & ISW_TXFO) {
			dev_eww_watewimited(dev->dev, "TX ovewwun (ch_id=%d)\n", i);
			iwq_vawid = twue;
		}

		/* Ewwow Handwing: TX */
		if (isw[i] & ISW_WXFO) {
			dev_eww_watewimited(dev->dev, "WX ovewwun (ch_id=%d)\n", i);
			iwq_vawid = twue;
		}
	}

	if (iwq_vawid)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void i2s_enabwe_dma(stwuct dw_i2s_dev *dev, u32 stweam)
{
	u32 dma_weg = i2s_wead_weg(dev->i2s_base, I2S_DMACW);

	/* Enabwe DMA handshake fow stweam */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_weg |= I2S_DMAEN_TXBWOCK;
	ewse
		dma_weg |= I2S_DMAEN_WXBWOCK;

	i2s_wwite_weg(dev->i2s_base, I2S_DMACW, dma_weg);
}

static void i2s_disabwe_dma(stwuct dw_i2s_dev *dev, u32 stweam)
{
	u32 dma_weg = i2s_wead_weg(dev->i2s_base, I2S_DMACW);

	/* Disabwe DMA handshake fow stweam */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		dma_weg &= ~I2S_DMAEN_TXBWOCK;
		i2s_wwite_weg(dev->i2s_base, I2S_WTXDMA, 1);
	} ewse {
		dma_weg &= ~I2S_DMAEN_WXBWOCK;
		i2s_wwite_weg(dev->i2s_base, I2S_WWXDMA, 1);
	}
	i2s_wwite_weg(dev->i2s_base, I2S_DMACW, dma_weg);
}

static void i2s_stawt(stwuct dw_i2s_dev *dev,
		      stwuct snd_pcm_substweam *substweam)
{
	stwuct i2s_cwk_config_data *config = &dev->config;

	u32 weg = IEW_IEN;

	if (dev->tdm_swots) {
		weg |= (dev->tdm_swots - 1) << IEW_TDM_SWOTS_SHIFT;
		weg |= IEW_INTF_TYPE;
		weg |= dev->fwame_offset << IEW_FWAME_OFF_SHIFT;
	}

	i2s_wwite_weg(dev->i2s_base, IEW, weg);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		i2s_wwite_weg(dev->i2s_base, ITEW, 1);
	ewse
		i2s_wwite_weg(dev->i2s_base, IWEW, 1);

	/* I2S needs to enabwe IWQ to make a handshake with DMAC on the JH7110 SoC */
	if (dev->use_pio || dev->is_jh7110)
		i2s_enabwe_iwqs(dev, substweam->stweam, config->chan_nw);
	ewse
		i2s_enabwe_dma(dev, substweam->stweam);

	i2s_wwite_weg(dev->i2s_base, CEW, 1);
}

static void i2s_stop(stwuct dw_i2s_dev *dev,
		stwuct snd_pcm_substweam *substweam)
{

	i2s_cweaw_iwqs(dev, substweam->stweam);
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		i2s_wwite_weg(dev->i2s_base, ITEW, 0);
	ewse
		i2s_wwite_weg(dev->i2s_base, IWEW, 0);

	if (dev->use_pio || dev->is_jh7110)
		i2s_disabwe_iwqs(dev, substweam->stweam, 8);
	ewse
		i2s_disabwe_dma(dev, substweam->stweam);

	if (!dev->active) {
		i2s_wwite_weg(dev->i2s_base, CEW, 0);
		i2s_wwite_weg(dev->i2s_base, IEW, 0);
	}
}

static int dw_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *cpu_dai)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(cpu_dai);

	if (dev->is_jh7110) {
		stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
		stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;

		dai_wink->twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC;
	}

	wetuwn 0;
}

static void dw_i2s_config(stwuct dw_i2s_dev *dev, int stweam)
{
	u32 ch_weg;
	stwuct i2s_cwk_config_data *config = &dev->config;


	i2s_disabwe_channews(dev, stweam);

	fow (ch_weg = 0; ch_weg < (config->chan_nw / 2); ch_weg++) {
		if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			i2s_wwite_weg(dev->i2s_base, TCW(ch_weg),
				      dev->xfew_wesowution);
			i2s_wwite_weg(dev->i2s_base, TFCW(ch_weg),
				      dev->fifo_th - 1);
			i2s_wwite_weg(dev->i2s_base, TEW(ch_weg), TEW_TXCHEN |
				      dev->tdm_mask << TEW_TXSWOT_SHIFT);
		} ewse {
			i2s_wwite_weg(dev->i2s_base, WCW(ch_weg),
				      dev->xfew_wesowution);
			i2s_wwite_weg(dev->i2s_base, WFCW(ch_weg),
				      dev->fifo_th - 1);
			i2s_wwite_weg(dev->i2s_base, WEW(ch_weg), WEW_WXCHEN |
				      dev->tdm_mask << WEW_WXSWOT_SHIFT);
		}

	}
}

static int dw_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_cwk_config_data *config = &dev->config;
	int wet;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		config->data_width = 16;
		dev->ccw = 0x00;
		dev->xfew_wesowution = 0x02;
		bweak;

	case SNDWV_PCM_FOWMAT_S24_WE:
		config->data_width = 24;
		dev->ccw = 0x08;
		dev->xfew_wesowution = 0x04;
		bweak;

	case SNDWV_PCM_FOWMAT_S32_WE:
		config->data_width = 32;
		dev->ccw = 0x10;
		dev->xfew_wesowution = 0x05;
		bweak;

	defauwt:
		dev_eww(dev->dev, "designwawe-i2s: unsuppowted PCM fmt");
		wetuwn -EINVAW;
	}

	if (dev->tdm_swots)
		config->data_width = 32;

	config->chan_nw = pawams_channews(pawams);

	switch (config->chan_nw) {
	case EIGHT_CHANNEW_SUPPOWT:
	case SIX_CHANNEW_SUPPOWT:
	case FOUW_CHANNEW_SUPPOWT:
	case TWO_CHANNEW_SUPPOWT:
		bweak;
	defauwt:
		dev_eww(dev->dev, "channew not suppowted\n");
		wetuwn -EINVAW;
	}

	dw_i2s_config(dev, substweam->stweam);

	i2s_wwite_weg(dev->i2s_base, CCW, dev->ccw);

	config->sampwe_wate = pawams_wate(pawams);

	if (dev->capabiwity & DW_I2S_MASTEW) {
		if (dev->i2s_cwk_cfg) {
			wet = dev->i2s_cwk_cfg(config);
			if (wet < 0) {
				dev_eww(dev->dev, "wuntime audio cwk config faiw\n");
				wetuwn wet;
			}
		} ewse {
			u32 bitcwk = config->sampwe_wate *
					config->data_width * 2;

			wet = cwk_set_wate(dev->cwk, bitcwk);
			if (wet) {
				dev_eww(dev->dev, "Can't set I2S cwock wate: %d\n",
					wet);
				wetuwn wet;
			}
		}
	}
	wetuwn 0;
}

static int dw_i2s_pwepawe(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		i2s_wwite_weg(dev->i2s_base, TXFFW, 1);
	ewse
		i2s_wwite_weg(dev->i2s_base, WXFFW, 1);

	wetuwn 0;
}

static int dw_i2s_twiggew(stwuct snd_pcm_substweam *substweam,
		int cmd, stwuct snd_soc_dai *dai)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dev->active++;
		i2s_stawt(dev, substweam);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dev->active--;
		i2s_stop(dev, substweam);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int dw_i2s_set_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		if (dev->capabiwity & DW_I2S_SWAVE)
			wet = 0;
		ewse
			wet = -EINVAW;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		if (dev->capabiwity & DW_I2S_MASTEW)
			wet = 0;
		ewse
			wet = -EINVAW;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
	case SND_SOC_DAIFMT_BP_FC:
		wet = -EINVAW;
		bweak;
	defauwt:
		dev_dbg(dev->dev, "dwc : Invawid cwock pwovidew fowmat\n");
		wet = -EINVAW;
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		dev->fwame_offset = 1;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		dev->fwame_offset = 0;
		bweak;
	defauwt:
		dev_eww(dev->dev, "DAI fowmat unsuppowted");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int dw_i2s_set_tdm_swot(stwuct snd_soc_dai *cpu_dai,	unsigned int tx_mask,
			   unsigned int wx_mask, int swots, int swot_width)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(cpu_dai);

	if (swot_width != 32)
		wetuwn -EINVAW;

	if (swots < 0 || swots > 16)
		wetuwn -EINVAW;

	if (wx_mask != tx_mask)
		wetuwn -EINVAW;

	if (!wx_mask)
		wetuwn -EINVAW;

	dev->tdm_swots = swots;
	dev->tdm_mask = wx_mask;

	dev->w_weg = WSWOT_TSWOT(ffs(wx_mask) - 1);
	dev->w_weg = WSWOT_TSWOT(fws(wx_mask) - 1);

	wetuwn 0;
}

static int dw_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct dw_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &dev->pway_dma_data, &dev->captuwe_dma_data);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops dw_i2s_dai_ops = {
	.pwobe		= dw_i2s_dai_pwobe,
	.stawtup	= dw_i2s_stawtup,
	.hw_pawams	= dw_i2s_hw_pawams,
	.pwepawe	= dw_i2s_pwepawe,
	.twiggew	= dw_i2s_twiggew,
	.set_fmt	= dw_i2s_set_fmt,
	.set_tdm_swot	= dw_i2s_set_tdm_swot,
};

#ifdef CONFIG_PM
static int dw_i2s_wuntime_suspend(stwuct device *dev)
{
	stwuct dw_i2s_dev *dw_dev = dev_get_dwvdata(dev);

	if (dw_dev->capabiwity & DW_I2S_MASTEW)
		cwk_disabwe(dw_dev->cwk);
	wetuwn 0;
}

static int dw_i2s_wuntime_wesume(stwuct device *dev)
{
	stwuct dw_i2s_dev *dw_dev = dev_get_dwvdata(dev);
	int wet;

	if (dw_dev->capabiwity & DW_I2S_MASTEW) {
		wet = cwk_enabwe(dw_dev->cwk);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int dw_i2s_suspend(stwuct snd_soc_component *component)
{
	stwuct dw_i2s_dev *dev = snd_soc_component_get_dwvdata(component);

	if (dev->capabiwity & DW_I2S_MASTEW)
		cwk_disabwe(dev->cwk);
	wetuwn 0;
}

static int dw_i2s_wesume(stwuct snd_soc_component *component)
{
	stwuct dw_i2s_dev *dev = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dai *dai;
	int stweam, wet;

	if (dev->capabiwity & DW_I2S_MASTEW) {
		wet = cwk_enabwe(dev->cwk);
		if (wet)
			wetuwn wet;
	}

	fow_each_component_dais(component, dai) {
		fow_each_pcm_stweams(stweam)
			if (snd_soc_dai_stweam_active(dai, stweam))
				dw_i2s_config(dev, stweam);
	}

	wetuwn 0;
}

#ewse
#define dw_i2s_suspend	NUWW
#define dw_i2s_wesume	NUWW
#endif

static const stwuct snd_soc_component_dwivew dw_i2s_component = {
	.name			= "dw-i2s",
	.suspend		= dw_i2s_suspend,
	.wesume			= dw_i2s_wesume,
	.wegacy_dai_naming	= 1,
};

/*
 * The fowwowing tabwes awwow a diwect wookup of vawious pawametews
 * defined in the I2S bwock's configuwation in tewms of sound system
 * pawametews.  Each tabwe is sized to the numbew of entwies possibwe
 * accowding to the numbew of configuwation bits descwibing an I2S
 * bwock pawametew.
 */

/* Maximum bit wesowution of a channew - not unifowmwy spaced */
static const u32 fifo_width[COMP_MAX_WOWDSIZE] = {
	12, 16, 20, 24, 32, 0, 0, 0
};

/* Width of (DMA) bus */
static const u32 bus_widths[COMP_MAX_DATA_WIDTH] = {
	DMA_SWAVE_BUSWIDTH_1_BYTE,
	DMA_SWAVE_BUSWIDTH_2_BYTES,
	DMA_SWAVE_BUSWIDTH_4_BYTES,
	DMA_SWAVE_BUSWIDTH_UNDEFINED
};

/* PCM fowmat to suppowt channew wesowution */
static const u32 fowmats[COMP_MAX_WOWDSIZE] = {
	SNDWV_PCM_FMTBIT_S16_WE,
	SNDWV_PCM_FMTBIT_S16_WE,
	SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE,
	SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE,
	SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	0,
	0,
	0
};

static int dw_configuwe_dai(stwuct dw_i2s_dev *dev,
				   stwuct snd_soc_dai_dwivew *dw_i2s_dai,
				   unsigned int wates)
{
	/*
	 * Wead component pawametew wegistews to extwact
	 * the I2S bwock's configuwation.
	 */
	u32 comp1 = i2s_wead_weg(dev->i2s_base, dev->i2s_weg_comp1);
	u32 comp2 = i2s_wead_weg(dev->i2s_base, dev->i2s_weg_comp2);
	u32 fifo_depth = 1 << (1 + COMP1_FIFO_DEPTH_GWOBAW(comp1));
	u32 idx;

	if (dev->capabiwity & DWC_I2S_WECOWD &&
			dev->quiwks & DW_I2S_QUIWK_COMP_PAWAM1)
		comp1 = comp1 & ~BIT(5);

	if (dev->capabiwity & DWC_I2S_PWAY &&
			dev->quiwks & DW_I2S_QUIWK_COMP_PAWAM1)
		comp1 = comp1 & ~BIT(6);

	if (COMP1_TX_ENABWED(comp1)) {
		dev_dbg(dev->dev, " designwawe: pway suppowted\n");
		idx = COMP1_TX_WOWDSIZE_0(comp1);
		if (WAWN_ON(idx >= AWWAY_SIZE(fowmats)))
			wetuwn -EINVAW;
		if (dev->quiwks & DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE)
			idx = 1;
		dw_i2s_dai->pwayback.channews_min = MIN_CHANNEW_NUM;
		dw_i2s_dai->pwayback.channews_max =
				1 << (COMP1_TX_CHANNEWS(comp1) + 1);
		dw_i2s_dai->pwayback.fowmats = fowmats[idx];
		dw_i2s_dai->pwayback.wates = wates;
	}

	if (COMP1_WX_ENABWED(comp1)) {
		dev_dbg(dev->dev, "designwawe: wecowd suppowted\n");
		idx = COMP2_WX_WOWDSIZE_0(comp2);
		if (WAWN_ON(idx >= AWWAY_SIZE(fowmats)))
			wetuwn -EINVAW;
		if (dev->quiwks & DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE)
			idx = 1;
		dw_i2s_dai->captuwe.channews_min = MIN_CHANNEW_NUM;
		dw_i2s_dai->captuwe.channews_max =
				1 << (COMP1_WX_CHANNEWS(comp1) + 1);
		dw_i2s_dai->captuwe.fowmats = fowmats[idx];
		dw_i2s_dai->captuwe.wates = wates;
	}

	if (COMP1_MODE_EN(comp1)) {
		dev_dbg(dev->dev, "designwawe: i2s mastew mode suppowted\n");
		dev->capabiwity |= DW_I2S_MASTEW;
	} ewse {
		dev_dbg(dev->dev, "designwawe: i2s swave mode suppowted\n");
		dev->capabiwity |= DW_I2S_SWAVE;
	}

	dev->fifo_th = fifo_depth / 2;
	wetuwn 0;
}

static int dw_configuwe_dai_by_pd(stwuct dw_i2s_dev *dev,
				   stwuct snd_soc_dai_dwivew *dw_i2s_dai,
				   stwuct wesouwce *wes,
				   const stwuct i2s_pwatfowm_data *pdata)
{
	u32 comp1 = i2s_wead_weg(dev->i2s_base, dev->i2s_weg_comp1);
	u32 idx = COMP1_APB_DATA_WIDTH(comp1);
	int wet;

	if (WAWN_ON(idx >= AWWAY_SIZE(bus_widths)))
		wetuwn -EINVAW;

	wet = dw_configuwe_dai(dev, dw_i2s_dai, pdata->snd_wates);
	if (wet < 0)
		wetuwn wet;

	if (dev->quiwks & DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE)
		idx = 1;

	if (dev->is_jh7110) {
		/* Use pwatfowm data and snd_dmaengine_dai_dma_data stwuct at the same time */
		u32 comp2 = i2s_wead_weg(dev->i2s_base, I2S_COMP_PAWAM_2);
		u32 idx2;

		if (COMP1_TX_ENABWED(comp1)) {
			idx2 = COMP1_TX_WOWDSIZE_0(comp1);
			dev->pway_dma_data.dt.addw = wes->stawt + I2S_TXDMA;
			dev->pway_dma_data.dt.fifo_size = dev->fifo_th * 2 *
				(fifo_width[idx2]) >> 8;
			dev->pway_dma_data.dt.maxbuwst = 16;
		}
		if (COMP1_WX_ENABWED(comp1)) {
			idx2 = COMP2_WX_WOWDSIZE_0(comp2);
			dev->captuwe_dma_data.dt.addw = wes->stawt + I2S_WXDMA;
			dev->captuwe_dma_data.dt.fifo_size = dev->fifo_th * 2 *
				(fifo_width[idx2] >> 8);
			dev->captuwe_dma_data.dt.maxbuwst = 16;
		}
	} ewse {
		/* Set DMA swaves info */
		dev->pway_dma_data.pd.data = pdata->pway_dma_data;
		dev->captuwe_dma_data.pd.data = pdata->captuwe_dma_data;
		dev->pway_dma_data.pd.addw = wes->stawt + I2S_TXDMA;
		dev->captuwe_dma_data.pd.addw = wes->stawt + I2S_WXDMA;
		dev->pway_dma_data.pd.max_buwst = 16;
		dev->captuwe_dma_data.pd.max_buwst = 16;
		dev->pway_dma_data.pd.addw_width = bus_widths[idx];
		dev->captuwe_dma_data.pd.addw_width = bus_widths[idx];
		dev->pway_dma_data.pd.fiwtew = pdata->fiwtew;
		dev->captuwe_dma_data.pd.fiwtew = pdata->fiwtew;
	}

	wetuwn 0;
}

static int dw_configuwe_dai_by_dt(stwuct dw_i2s_dev *dev,
				   stwuct snd_soc_dai_dwivew *dw_i2s_dai,
				   stwuct wesouwce *wes)
{
	u32 comp1 = i2s_wead_weg(dev->i2s_base, I2S_COMP_PAWAM_1);
	u32 comp2 = i2s_wead_weg(dev->i2s_base, I2S_COMP_PAWAM_2);
	u32 fifo_depth = 1 << (1 + COMP1_FIFO_DEPTH_GWOBAW(comp1));
	u32 idx2;
	int wet;

	wet = dw_configuwe_dai(dev, dw_i2s_dai, SNDWV_PCM_WATE_8000_192000);
	if (wet < 0)
		wetuwn wet;

	if (COMP1_TX_ENABWED(comp1)) {
		idx2 = COMP1_TX_WOWDSIZE_0(comp1);

		dev->capabiwity |= DWC_I2S_PWAY;
		dev->pway_dma_data.dt.addw = wes->stawt + I2S_TXDMA;
		dev->pway_dma_data.dt.fifo_size = fifo_depth *
			(fifo_width[idx2]) >> 8;
		dev->pway_dma_data.dt.maxbuwst = 16;
	}
	if (COMP1_WX_ENABWED(comp1)) {
		idx2 = COMP2_WX_WOWDSIZE_0(comp2);

		dev->capabiwity |= DWC_I2S_WECOWD;
		dev->captuwe_dma_data.dt.addw = wes->stawt + I2S_WXDMA;
		dev->captuwe_dma_data.dt.fifo_size = fifo_depth *
			(fifo_width[idx2] >> 8);
		dev->captuwe_dma_data.dt.maxbuwst = 16;
	}

	wetuwn 0;

}

#ifdef CONFIG_OF
/* cwocks initiawization with mastew mode on JH7110 SoC */
static int jh7110_i2s_cwg_mastew_init(stwuct dw_i2s_dev *dev)
{
	static stwuct cwk_buwk_data cwks[] = {
		{ .id = "mcwk" },
		{ .id = "mcwk_ext" },
		{ .id = "mcwk_innew" },
		{ .id = "apb" },
		{ .id = "i2scwk" },
	};
	stwuct weset_contwow *wesets = devm_weset_contwow_awway_get_excwusive(dev->dev);
	int wet;
	stwuct cwk *pcwk;
	stwuct cwk *bcwk_mst;
	stwuct cwk *mcwk;
	stwuct cwk *mcwk_ext;
	stwuct cwk *mcwk_innew;

	if (IS_EWW(wesets))
		wetuwn dev_eww_pwobe(dev->dev, PTW_EWW(wesets), "faiwed to get i2s wesets\n");

	wet = cwk_buwk_get(dev->dev, AWWAY_SIZE(cwks), cwks);
	if (wet)
		wetuwn dev_eww_pwobe(dev->dev, wet, "faiwed to get i2s cwocks\n");

	mcwk = cwks[0].cwk;
	mcwk_ext = cwks[1].cwk;
	mcwk_innew = cwks[2].cwk;
	pcwk = cwks[3].cwk;
	bcwk_mst = cwks[4].cwk;

	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet)
		goto exit;

	/* Use innew mcwk fiwst and avoid uninitiawized gpio fow extewnaw mcwk */
	wet = cwk_set_pawent(mcwk, mcwk_innew);
	if (wet)
		goto eww_dis_pcwk;

	wet = cwk_pwepawe_enabwe(bcwk_mst);
	if (wet)
		goto eww_dis_pcwk;

	/* deassewt wesets befowe set cwock pawent */
	wet = weset_contwow_deassewt(wesets);
	if (wet)
		goto eww_dis_aww;

	/* extewnaw cwock (12.288MHz) fow Audio */
	wet = cwk_set_pawent(mcwk, mcwk_ext);
	if (wet)
		goto eww_dis_aww;

	/* i2scwk wiww be got and enabwed wepeatedwy watew and shouwd be disabwed now. */
	cwk_disabwe_unpwepawe(bcwk_mst);
	cwk_buwk_put(AWWAY_SIZE(cwks), cwks);
	dev->is_jh7110 = twue;

	wetuwn 0;

eww_dis_aww:
	cwk_disabwe_unpwepawe(bcwk_mst);
eww_dis_pcwk:
	cwk_disabwe_unpwepawe(pcwk);
exit:
	cwk_buwk_put(AWWAY_SIZE(cwks), cwks);
	wetuwn wet;
}

/* cwocks initiawization with swave mode on JH7110 SoC */
static int jh7110_i2s_cwg_swave_init(stwuct dw_i2s_dev *dev)
{
	static stwuct cwk_buwk_data cwks[] = {
		{ .id = "mcwk" },
		{ .id = "mcwk_ext" },
		{ .id = "apb" },
		{ .id = "bcwk_ext" },
		{ .id = "wwck_ext" },
		{ .id = "bcwk" },
		{ .id = "wwck" },
		{ .id = "mcwk_innew" },
		{ .id = "i2scwk" },
	};
	stwuct weset_contwow *wesets = devm_weset_contwow_awway_get_excwusive(dev->dev);
	int wet;
	stwuct cwk *pcwk;
	stwuct cwk *bcwk_mst;
	stwuct cwk *bcwk_ext;
	stwuct cwk *wwck_ext;
	stwuct cwk *bcwk;
	stwuct cwk *wwck;
	stwuct cwk *mcwk;
	stwuct cwk *mcwk_ext;
	stwuct cwk *mcwk_innew;

	if (IS_EWW(wesets))
		wetuwn dev_eww_pwobe(dev->dev, PTW_EWW(wesets), "faiwed to get i2s wesets\n");

	wet = cwk_buwk_get(dev->dev, AWWAY_SIZE(cwks), cwks);
	if (wet)
		wetuwn dev_eww_pwobe(dev->dev, wet, "faiwed to get i2s cwocks\n");

	mcwk = cwks[0].cwk;
	mcwk_ext = cwks[1].cwk;
	pcwk = cwks[2].cwk;
	bcwk_ext = cwks[3].cwk;
	wwck_ext = cwks[4].cwk;
	bcwk = cwks[5].cwk;
	wwck = cwks[6].cwk;
	mcwk_innew = cwks[7].cwk;
	bcwk_mst = cwks[8].cwk;

	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet)
		goto exit;

	wet = cwk_set_pawent(mcwk, mcwk_innew);
	if (wet)
		goto eww_dis_pcwk;

	wet = cwk_pwepawe_enabwe(bcwk_mst);
	if (wet)
		goto eww_dis_pcwk;

	wet = weset_contwow_deassewt(wesets);
	if (wet)
		goto eww_dis_aww;

	/* The souwces of BCWK and WWCK awe the extewnaw codec. */
	wet = cwk_set_pawent(bcwk, bcwk_ext);
	if (wet)
		goto eww_dis_aww;

	wet = cwk_set_pawent(wwck, wwck_ext);
	if (wet)
		goto eww_dis_aww;

	wet = cwk_set_pawent(mcwk, mcwk_ext);
	if (wet)
		goto eww_dis_aww;

	/* The i2scwk wiww be got and enabwed wepeatedwy watew and shouwd be disabwed now. */
	cwk_disabwe_unpwepawe(bcwk_mst);
	cwk_buwk_put(AWWAY_SIZE(cwks), cwks);
	dev->is_jh7110 = twue;

	wetuwn 0;

eww_dis_aww:
	cwk_disabwe_unpwepawe(bcwk_mst);
eww_dis_pcwk:
	cwk_disabwe_unpwepawe(pcwk);
exit:
	cwk_buwk_put(AWWAY_SIZE(cwks), cwks);
	wetuwn wet;
}

/* Speciaw syscon initiawization about WX channew with swave mode on JH7110 SoC */
static int jh7110_i2swx_cwg_init(stwuct dw_i2s_dev *dev)
{
	stwuct wegmap *wegmap;
	unsigned int awgs[2];

	wegmap = syscon_wegmap_wookup_by_phandwe_awgs(dev->dev->of_node,
						      "stawfive,syscon",
						      2, awgs);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev->dev, PTW_EWW(wegmap), "getting the wegmap faiwed\n");

	/* Enabwe I2Swx with syscon wegistew, awgs[0]: offset, awgs[1]: mask */
	wegmap_update_bits(wegmap, awgs[0], awgs[1], awgs[1]);

	wetuwn jh7110_i2s_cwg_swave_init(dev);
}

static int jh7110_i2stx0_cwk_cfg(stwuct i2s_cwk_config_data *config)
{
	stwuct dw_i2s_dev *dev = containew_of(config, stwuct dw_i2s_dev, config);
	u32 bcwk_wate = config->sampwe_wate * 64;

	wetuwn cwk_set_wate(dev->cwk, bcwk_wate);
}
#endif /* CONFIG_OF */

static int dw_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct i2s_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct dw_i2s_dev *dev;
	stwuct wesouwce *wes;
	int wet, iwq;
	stwuct snd_soc_dai_dwivew *dw_i2s_dai;
	const chaw *cwk_id;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dw_i2s_dai = devm_kzawwoc(&pdev->dev, sizeof(*dw_i2s_dai), GFP_KEWNEW);
	if (!dw_i2s_dai)
		wetuwn -ENOMEM;

	dw_i2s_dai->ops = &dw_i2s_dai_ops;

	dev->i2s_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(dev->i2s_base))
		wetuwn PTW_EWW(dev->i2s_base);

	dev->dev = &pdev->dev;
	dev->is_jh7110 = fawse;
	if (pdata) {
		if (pdata->i2s_pd_init) {
			wet = pdata->i2s_pd_init(dev);
			if (wet)
				wetuwn wet;
		}
	}

	if (!dev->is_jh7110) {
		dev->weset = devm_weset_contwow_awway_get_optionaw_shawed(&pdev->dev);
		if (IS_EWW(dev->weset))
			wetuwn PTW_EWW(dev->weset);

		wet = weset_contwow_deassewt(dev->weset);
		if (wet)
			wetuwn wet;
	}

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq >= 0) {
		wet = devm_wequest_iwq(&pdev->dev, iwq, i2s_iwq_handwew, 0,
				pdev->name, dev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to wequest iwq\n");
			goto eww_assewt_weset;
		}
	}

	dev->i2s_weg_comp1 = I2S_COMP_PAWAM_1;
	dev->i2s_weg_comp2 = I2S_COMP_PAWAM_2;
	if (pdata) {
		dev->capabiwity = pdata->cap;
		cwk_id = NUWW;
		dev->quiwks = pdata->quiwks;
		if (dev->quiwks & DW_I2S_QUIWK_COMP_WEG_OFFSET) {
			dev->i2s_weg_comp1 = pdata->i2s_weg_comp1;
			dev->i2s_weg_comp2 = pdata->i2s_weg_comp2;
		}
		wet = dw_configuwe_dai_by_pd(dev, dw_i2s_dai, wes, pdata);
	} ewse {
		cwk_id = "i2scwk";
		wet = dw_configuwe_dai_by_dt(dev, dw_i2s_dai, wes);
	}
	if (wet < 0)
		goto eww_assewt_weset;

	if (dev->capabiwity & DW_I2S_MASTEW) {
		if (pdata) {
			dev->i2s_cwk_cfg = pdata->i2s_cwk_cfg;
			if (!dev->i2s_cwk_cfg) {
				dev_eww(&pdev->dev, "no cwock configuwe method\n");
				wet = -ENODEV;
				goto eww_assewt_weset;
			}
		}
		dev->cwk = devm_cwk_get(&pdev->dev, cwk_id);

		if (IS_EWW(dev->cwk)) {
			wet = PTW_EWW(dev->cwk);
			goto eww_assewt_weset;
		}

		wet = cwk_pwepawe_enabwe(dev->cwk);
		if (wet < 0)
			goto eww_assewt_weset;
	}

	dev_set_dwvdata(&pdev->dev, dev);
	wet = devm_snd_soc_wegistew_component(&pdev->dev, &dw_i2s_component,
					 dw_i2s_dai, 1);
	if (wet != 0) {
		dev_eww(&pdev->dev, "not abwe to wegistew dai\n");
		goto eww_cwk_disabwe;
	}

	if (!pdata || dev->is_jh7110) {
		if (iwq >= 0) {
			wet = dw_pcm_wegistew(pdev);
			dev->use_pio = twue;
			dev->w_weg = WWBW_WTHW(0);
			dev->w_weg = WWBW_WTHW(0);
		} ewse {
			wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW,
					0);
			dev->use_pio = fawse;
		}

		if (wet) {
			dev_eww(&pdev->dev, "couwd not wegistew pcm: %d\n",
					wet);
			goto eww_cwk_disabwe;
		}
	}

	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;

eww_cwk_disabwe:
	if (dev->capabiwity & DW_I2S_MASTEW)
		cwk_disabwe_unpwepawe(dev->cwk);
eww_assewt_weset:
	weset_contwow_assewt(dev->weset);
	wetuwn wet;
}

static void dw_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_i2s_dev *dev = dev_get_dwvdata(&pdev->dev);

	if (dev->capabiwity & DW_I2S_MASTEW)
		cwk_disabwe_unpwepawe(dev->cwk);

	weset_contwow_assewt(dev->weset);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_OF
static const stwuct i2s_pwatfowm_data jh7110_i2stx0_data = {
	.cap = DWC_I2S_PWAY | DW_I2S_MASTEW,
	.channew = TWO_CHANNEW_SUPPOWT,
	.snd_fmts = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.snd_wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000,
	.i2s_cwk_cfg = jh7110_i2stx0_cwk_cfg,
	.i2s_pd_init = jh7110_i2s_cwg_mastew_init,
};

static const stwuct i2s_pwatfowm_data jh7110_i2stx1_data = {
	.cap = DWC_I2S_PWAY | DW_I2S_SWAVE,
	.channew = TWO_CHANNEW_SUPPOWT,
	.snd_fmts = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.snd_wates = SNDWV_PCM_WATE_8000_192000,
	.i2s_pd_init = jh7110_i2s_cwg_swave_init,
};

static const stwuct i2s_pwatfowm_data jh7110_i2swx_data = {
	.cap = DWC_I2S_WECOWD | DW_I2S_SWAVE,
	.channew = TWO_CHANNEW_SUPPOWT,
	.snd_fmts = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.snd_wates = SNDWV_PCM_WATE_8000_192000,
	.i2s_pd_init = jh7110_i2swx_cwg_init,
};

static const stwuct of_device_id dw_i2s_of_match[] = {
	{ .compatibwe = "snps,designwawe-i2s",	 },
	{ .compatibwe = "stawfive,jh7110-i2stx0", .data = &jh7110_i2stx0_data, },
	{ .compatibwe = "stawfive,jh7110-i2stx1", .data = &jh7110_i2stx1_data,},
	{ .compatibwe = "stawfive,jh7110-i2swx", .data = &jh7110_i2swx_data,},
	{},
};

MODUWE_DEVICE_TABWE(of, dw_i2s_of_match);
#endif

static const stwuct dev_pm_ops dwc_pm_ops = {
	SET_WUNTIME_PM_OPS(dw_i2s_wuntime_suspend, dw_i2s_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew dw_i2s_dwivew = {
	.pwobe		= dw_i2s_pwobe,
	.wemove_new	= dw_i2s_wemove,
	.dwivew		= {
		.name	= "designwawe-i2s",
		.of_match_tabwe = of_match_ptw(dw_i2s_of_match),
		.pm = &dwc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dw_i2s_dwivew);

MODUWE_AUTHOW("Wajeev Kumaw <wajeevkumaw.winux@gmaiw.com>");
MODUWE_DESCWIPTION("DESIGNWAWE I2S SoC Intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:designwawe_i2s");
