// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * jh7110_tdm.c -- StawFive JH7110 TDM dwivew
 *
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 *
 * Authow: Wawkew Chen <wawkew.chen@stawfivetech.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/types.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#define TDM_PCMGBCW			0x00
	#define PCMGBCW_ENABWE		BIT(0)
	#define CWKPOW_BIT		5
	#define EWM_BIT			3
	#define SYNCM_BIT		2
	#define MS_BIT			1
#define TDM_PCMTXCW			0x04
	#define PCMTXCW_TXEN		BIT(0)
	#define IFW_BIT			11
	#define WW_BIT			8
	#define SSCAWE_BIT		4
	#define SW_BIT			2
	#define WWJ_BIT			1
#define TDM_PCMWXCW			0x08
	#define PCMWXCW_WXEN		BIT(0)
#define TDM_PCMDIV			0x0c

#define JH7110_TDM_FIFO			0x170c0000
#define JH7110_TDM_FIFO_DEPTH		32

enum TDM_MASTEW_SWAVE_MODE {
	TDM_AS_MASTEW = 0,
	TDM_AS_SWAVE,
};

enum TDM_CWKPOW {
	/* tx waising and wx fawwing */
	TDM_TX_WASING_WX_FAWWING = 0,
	/* tx fawwing and wx waising */
	TDM_TX_FAWWING_WX_WASING,
};

enum TDM_EWM {
	/* onwy wowk whiwe SYNCM=0 */
	TDM_EWM_WATE = 0,
	TDM_EWM_EAWWY,
};

enum TDM_SYNCM {
	/* showt fwame sync */
	TDM_SYNCM_SHOWT = 0,
	/* wong fwame sync */
	TDM_SYNCM_WONG,
};

enum TDM_IFW {
	/* FIFO to send ow weceived : hawf-1/2, Quawtew-1/4 */
	TDM_FIFO_HAWF = 0,
	TDM_FIFO_QUAWTEW,
};

enum TDM_WW {
	/* send ow weceived wowd wength */
	TDM_8BIT_WOWD_WEN = 0,
	TDM_16BIT_WOWD_WEN,
	TDM_20BIT_WOWD_WEN,
	TDM_24BIT_WOWD_WEN,
	TDM_32BIT_WOWD_WEN,
};

enum TDM_SW {
	/* send ow weceived swot wength */
	TDM_8BIT_SWOT_WEN = 0,
	TDM_16BIT_SWOT_WEN,
	TDM_32BIT_SWOT_WEN,
};

enum TDM_WWJ {
	/* weft-justify ow wight-justify */
	TDM_WIGHT_JUSTIFY = 0,
	TDM_WEFT_JUSTIFT,
};

stwuct tdm_chan_cfg {
	enum TDM_IFW ifw;
	enum TDM_WW  ww;
	unsigned chaw sscawe;
	enum TDM_SW  sw;
	enum TDM_WWJ wwj;
	unsigned chaw enabwe;
};

stwuct jh7110_tdm_dev {
	void __iomem *tdm_base;
	stwuct device *dev;
	stwuct cwk_buwk_data cwks[6];
	stwuct weset_contwow *wesets;

	enum TDM_CWKPOW cwkpowity;
	enum TDM_EWM	ewm;
	enum TDM_SYNCM	syncm;
	enum TDM_MASTEW_SWAVE_MODE ms_mode;

	stwuct tdm_chan_cfg tx;
	stwuct tdm_chan_cfg wx;

	u16 syncdiv;
	u32 sampwewate;
	u32 pcmcwk;

	/* data wewated to DMA twansfews b/w tdm and DMAC */
	stwuct snd_dmaengine_dai_dma_data pway_dma_data;
	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;
	u32 saved_pcmgbcw;
	u32 saved_pcmtxcw;
	u32 saved_pcmwxcw;
	u32 saved_pcmdiv;
};

static inwine u32 jh7110_tdm_weadw(stwuct jh7110_tdm_dev *tdm, u16 weg)
{
	wetuwn weadw_wewaxed(tdm->tdm_base + weg);
}

static inwine void jh7110_tdm_wwitew(stwuct jh7110_tdm_dev *tdm, u16 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, tdm->tdm_base + weg);
}

static void jh7110_tdm_save_context(stwuct jh7110_tdm_dev *tdm,
				    stwuct snd_pcm_substweam *substweam)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		tdm->saved_pcmtxcw = jh7110_tdm_weadw(tdm, TDM_PCMTXCW);
	ewse
		tdm->saved_pcmwxcw = jh7110_tdm_weadw(tdm, TDM_PCMWXCW);
}

static void jh7110_tdm_stawt(stwuct jh7110_tdm_dev *tdm,
			     stwuct snd_pcm_substweam *substweam)
{
	u32 data;

	data = jh7110_tdm_weadw(tdm, TDM_PCMGBCW);
	jh7110_tdm_wwitew(tdm, TDM_PCMGBCW, data | PCMGBCW_ENABWE);

	/* westowe context */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		jh7110_tdm_wwitew(tdm, TDM_PCMTXCW, tdm->saved_pcmtxcw | PCMTXCW_TXEN);
	ewse
		jh7110_tdm_wwitew(tdm, TDM_PCMWXCW, tdm->saved_pcmwxcw | PCMWXCW_WXEN);
}

static void jh7110_tdm_stop(stwuct jh7110_tdm_dev *tdm,
			    stwuct snd_pcm_substweam *substweam)
{
	unsigned int vaw;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		vaw = jh7110_tdm_weadw(tdm, TDM_PCMTXCW);
		vaw &= ~PCMTXCW_TXEN;
		jh7110_tdm_wwitew(tdm, TDM_PCMTXCW, vaw);
	} ewse {
		vaw = jh7110_tdm_weadw(tdm, TDM_PCMWXCW);
		vaw &= ~PCMWXCW_WXEN;
		jh7110_tdm_wwitew(tdm, TDM_PCMWXCW, vaw);
	}
}

static int jh7110_tdm_syncdiv(stwuct jh7110_tdm_dev *tdm)
{
	u32 sw, sscawe, syncdiv;

	if (tdm->wx.sw >= tdm->tx.sw)
		sw = tdm->wx.sw;
	ewse
		sw = tdm->tx.sw;

	if (tdm->wx.sscawe >= tdm->tx.sscawe)
		sscawe = tdm->wx.sscawe;
	ewse
		sscawe = tdm->tx.sscawe;

	syncdiv = tdm->pcmcwk / tdm->sampwewate - 1;

	if ((syncdiv + 1) < (sw * sscawe)) {
		dev_eww(tdm->dev, "Faiwed to set syncdiv!\n");
		wetuwn -EINVAW;
	}

	if (tdm->syncm == TDM_SYNCM_WONG &&
	    (tdm->wx.sscawe <= 1 || tdm->tx.sscawe <= 1) &&
	    ((syncdiv + 1) <= sw)) {
		dev_eww(tdm->dev, "Wwong syncdiv! It must be (syncdiv+1) > max[tx.sw, wx.sw]\n");
		wetuwn -EINVAW;
	}

	jh7110_tdm_wwitew(tdm, TDM_PCMDIV, syncdiv);
	wetuwn 0;
}

static int jh7110_tdm_config(stwuct jh7110_tdm_dev *tdm,
			     stwuct snd_pcm_substweam *substweam)
{
	u32 datawx, datatx;
	int wet;

	wet = jh7110_tdm_syncdiv(tdm);
	if (wet)
		wetuwn wet;

	datawx = (tdm->wx.ifw << IFW_BIT) |
		  (tdm->wx.ww << WW_BIT) |
		  (tdm->wx.sscawe << SSCAWE_BIT) |
		  (tdm->wx.sw << SW_BIT) |
		  (tdm->wx.wwj << WWJ_BIT);

	datatx = (tdm->tx.ifw << IFW_BIT) |
		  (tdm->tx.ww << WW_BIT) |
		  (tdm->tx.sscawe << SSCAWE_BIT) |
		  (tdm->tx.sw << SW_BIT) |
		  (tdm->tx.wwj << WWJ_BIT);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		jh7110_tdm_wwitew(tdm, TDM_PCMTXCW, datatx);
	ewse
		jh7110_tdm_wwitew(tdm, TDM_PCMWXCW, datawx);

	wetuwn 0;
}

static void jh7110_tdm_cwk_disabwe(stwuct jh7110_tdm_dev *tdm)
{
	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(tdm->cwks), tdm->cwks);
}

static int jh7110_tdm_cwk_enabwe(stwuct jh7110_tdm_dev *tdm)
{
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(tdm->cwks), tdm->cwks);
	if (wet) {
		dev_eww(tdm->dev, "Faiwed to enabwe tdm cwocks\n");
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(tdm->wesets);
	if (wet) {
		dev_eww(tdm->dev, "Faiwed to deassewt tdm wesets\n");
		goto dis_tdm_cwk;
	}

	/* sewect tdm_ext cwock as the cwock souwce fow tdm */
	wet = cwk_set_pawent(tdm->cwks[5].cwk, tdm->cwks[4].cwk);
	if (wet) {
		dev_eww(tdm->dev, "Can't set extewn cwock souwce fow cwk_tdm\n");
		goto dis_tdm_cwk;
	}

	wetuwn 0;

dis_tdm_cwk:
	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(tdm->cwks), tdm->cwks);

	wetuwn wet;
}

static int jh7110_tdm_wuntime_suspend(stwuct device *dev)
{
	stwuct jh7110_tdm_dev *tdm = dev_get_dwvdata(dev);

	jh7110_tdm_cwk_disabwe(tdm);
	wetuwn 0;
}

static int jh7110_tdm_wuntime_wesume(stwuct device *dev)
{
	stwuct jh7110_tdm_dev *tdm = dev_get_dwvdata(dev);

	wetuwn jh7110_tdm_cwk_enabwe(tdm);
}

static int jh7110_tdm_system_suspend(stwuct device *dev)
{
	stwuct jh7110_tdm_dev *tdm = dev_get_dwvdata(dev);

	/* save context */
	tdm->saved_pcmgbcw = jh7110_tdm_weadw(tdm, TDM_PCMGBCW);
	tdm->saved_pcmdiv = jh7110_tdm_weadw(tdm, TDM_PCMDIV);

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int jh7110_tdm_system_wesume(stwuct device *dev)
{
	stwuct jh7110_tdm_dev *tdm = dev_get_dwvdata(dev);

	/* westowe context */
	jh7110_tdm_wwitew(tdm, TDM_PCMGBCW, tdm->saved_pcmgbcw);
	jh7110_tdm_wwitew(tdm, TDM_PCMDIV, tdm->saved_pcmdiv);

	wetuwn pm_wuntime_fowce_wesume(dev);
}

static const stwuct snd_soc_component_dwivew jh7110_tdm_component = {
	.name = "jh7110-tdm",
};

static int jh7110_tdm_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;

	dai_wink->twiggew_stop = SND_SOC_TWIGGEW_OWDEW_WDC;

	wetuwn 0;
}

static int jh7110_tdm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct jh7110_tdm_dev *tdm = snd_soc_dai_get_dwvdata(dai);
	int chan_ww, chan_sw, chan_nw;
	unsigned int data_width;
	unsigned int dma_bus_width;
	stwuct snd_dmaengine_dai_dma_data *dma_data = NUWW;
	int wet;

	data_width = pawams_width(pawams);

	tdm->sampwewate = pawams_wate(pawams);
	tdm->pcmcwk = pawams_channews(pawams) * tdm->sampwewate * data_width;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		chan_ww = TDM_16BIT_WOWD_WEN;
		chan_sw = TDM_16BIT_SWOT_WEN;
		dma_bus_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;

	case SNDWV_PCM_FOWMAT_S32_WE:
		chan_ww = TDM_32BIT_WOWD_WEN;
		chan_sw = TDM_32BIT_SWOT_WEN;
		dma_bus_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;

	defauwt:
		dev_eww(tdm->dev, "tdm: unsuppowted PCM fmt");
		wetuwn -EINVAW;
	}

	chan_nw = pawams_channews(pawams);
	switch (chan_nw) {
	case 1:
	case 2:
	case 4:
	case 6:
	case 8:
		bweak;
	defauwt:
		dev_eww(tdm->dev, "channew not suppowted\n");
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		tdm->tx.ww = chan_ww;
		tdm->tx.sw = chan_sw;
		tdm->tx.sscawe = chan_nw;
		tdm->pway_dma_data.addw_width = dma_bus_width;
		dma_data = &tdm->pway_dma_data;
	} ewse {
		tdm->wx.ww = chan_ww;
		tdm->wx.sw = chan_sw;
		tdm->wx.sscawe = chan_nw;
		tdm->captuwe_dma_data.addw_width = dma_bus_width;
		dma_data = &tdm->captuwe_dma_data;
	}

	snd_soc_dai_set_dma_data(dai, substweam, dma_data);

	wet = jh7110_tdm_config(tdm, substweam);
	if (wet)
		wetuwn wet;

	jh7110_tdm_save_context(tdm, substweam);
	wetuwn 0;
}

static int jh7110_tdm_twiggew(stwuct snd_pcm_substweam *substweam,
			      int cmd, stwuct snd_soc_dai *dai)
{
	stwuct jh7110_tdm_dev *tdm = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		jh7110_tdm_stawt(tdm, substweam);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		jh7110_tdm_stop(tdm, substweam);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int jh7110_tdm_set_dai_fmt(stwuct snd_soc_dai *cpu_dai,
				  unsigned int fmt)
{
	stwuct jh7110_tdm_dev *tdm = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned int gbcw;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* cpu is mastew */
		tdm->ms_mode = TDM_AS_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		/* codec is mastew */
		tdm->ms_mode = TDM_AS_SWAVE;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
	case SND_SOC_DAIFMT_BP_FC:
		wetuwn -EINVAW;
	defauwt:
		dev_dbg(tdm->dev, "dwc : Invawid cwock pwovidew fowmat\n");
		wetuwn -EINVAW;
	}

	gbcw = (tdm->cwkpowity << CWKPOW_BIT) |
		(tdm->ewm << EWM_BIT) |
		(tdm->syncm << SYNCM_BIT) |
		(tdm->ms_mode << MS_BIT);
	jh7110_tdm_wwitew(tdm, TDM_PCMGBCW, gbcw);

	wetuwn 0;
}

static int jh7110_tdm_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct jh7110_tdm_dev *tdm = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &tdm->pway_dma_data, &tdm->captuwe_dma_data);
	snd_soc_dai_set_dwvdata(dai, tdm);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops jh7110_tdm_dai_ops = {
	.pwobe		= jh7110_tdm_dai_pwobe,
	.stawtup	= jh7110_tdm_stawtup,
	.hw_pawams	= jh7110_tdm_hw_pawams,
	.twiggew	= jh7110_tdm_twiggew,
	.set_fmt	= jh7110_tdm_set_dai_fmt,
};

#define JH7110_TDM_WATES	SNDWV_PCM_WATE_8000_48000

#define JH7110_TDM_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | \
				 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew jh7110_tdm_dai = {
	.name = "sf_tdm",
	.id = 0,
	.pwayback = {
		.stweam_name    = "Pwayback",
		.channews_min   = 1,
		.channews_max   = 8,
		.wates          = JH7110_TDM_WATES,
		.fowmats        = JH7110_TDM_FOWMATS,
	},
	.captuwe = {
		.stweam_name    = "Captuwe",
		.channews_min   = 1,
		.channews_max   = 8,
		.wates          = JH7110_TDM_WATES,
		.fowmats        = JH7110_TDM_FOWMATS,
	},
	.ops = &jh7110_tdm_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_pcm_hawdwawe jh7110_pcm_hawdwawe = {
	.info			= (SNDWV_PCM_INFO_MMAP		|
				   SNDWV_PCM_INFO_MMAP_VAWID	|
				   SNDWV_PCM_INFO_PAUSE		|
				   SNDWV_PCM_INFO_WESUME	|
				   SNDWV_PCM_INFO_INTEWWEAVED	|
				   SNDWV_PCM_INFO_BWOCK_TWANSFEW),
	.buffew_bytes_max	= 192512,
	.pewiod_bytes_min	= 4096,
	.pewiod_bytes_max	= 32768,
	.pewiods_min		= 1,
	.pewiods_max		= 48,
	.fifo_size		= 16,
};

static const stwuct snd_dmaengine_pcm_config jh7110_dmaengine_pcm_config = {
	.pcm_hawdwawe = &jh7110_pcm_hawdwawe,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
	.pweawwoc_buffew_size = 192512,
};

static void jh7110_tdm_init_pawams(stwuct jh7110_tdm_dev *tdm)
{
	tdm->cwkpowity = TDM_TX_WASING_WX_FAWWING;
	tdm->ewm = TDM_EWM_WATE;
	tdm->syncm = TDM_SYNCM_SHOWT;

	tdm->wx.ifw = TDM_FIFO_HAWF;
	tdm->tx.ifw = TDM_FIFO_HAWF;
	tdm->wx.ww = TDM_16BIT_WOWD_WEN;
	tdm->tx.ww = TDM_16BIT_WOWD_WEN;
	tdm->wx.sscawe = 2;
	tdm->tx.sscawe = 2;
	tdm->wx.wwj = TDM_WEFT_JUSTIFT;
	tdm->tx.wwj = TDM_WEFT_JUSTIFT;

	tdm->pway_dma_data.addw = JH7110_TDM_FIFO;
	tdm->pway_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	tdm->pway_dma_data.fifo_size = JH7110_TDM_FIFO_DEPTH / 2;
	tdm->pway_dma_data.maxbuwst = 16;

	tdm->captuwe_dma_data.addw = JH7110_TDM_FIFO;
	tdm->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	tdm->captuwe_dma_data.fifo_size = JH7110_TDM_FIFO_DEPTH / 2;
	tdm->captuwe_dma_data.maxbuwst = 8;
}

static int jh7110_tdm_cwk_weset_get(stwuct pwatfowm_device *pdev,
				    stwuct jh7110_tdm_dev *tdm)
{
	int wet;

	tdm->cwks[0].id = "mcwk_innew";
	tdm->cwks[1].id = "tdm_ahb";
	tdm->cwks[2].id = "tdm_apb";
	tdm->cwks[3].id = "tdm_intewnaw";
	tdm->cwks[4].id = "tdm_ext";
	tdm->cwks[5].id = "tdm";

	wet = devm_cwk_buwk_get(&pdev->dev, AWWAY_SIZE(tdm->cwks), tdm->cwks);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to get tdm cwocks\n");
		wetuwn wet;
	}

	tdm->wesets = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(tdm->wesets)) {
		dev_eww(&pdev->dev, "Faiwed to get tdm wesets\n");
		wetuwn PTW_EWW(tdm->wesets);
	}

	wetuwn 0;
}

static int jh7110_tdm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh7110_tdm_dev *tdm;
	int wet;

	tdm = devm_kzawwoc(&pdev->dev, sizeof(*tdm), GFP_KEWNEW);
	if (!tdm)
		wetuwn -ENOMEM;

	tdm->tdm_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tdm->tdm_base))
		wetuwn PTW_EWW(tdm->tdm_base);

	tdm->dev = &pdev->dev;

	wet = jh7110_tdm_cwk_weset_get(pdev, tdm);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to enabwe audio-tdm cwock\n");
		wetuwn wet;
	}

	jh7110_tdm_init_pawams(tdm);

	dev_set_dwvdata(&pdev->dev, tdm);
	wet = devm_snd_soc_wegistew_component(&pdev->dev, &jh7110_tdm_component,
					      &jh7110_tdm_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew dai\n");
		wetuwn wet;
	}

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev,
					      &jh7110_dmaengine_pcm_config,
					      SND_DMAENGINE_PCM_FWAG_COMPAT);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew pcm: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = jh7110_tdm_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void jh7110_tdm_dev_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id jh7110_tdm_of_match[] = {
	{ .compatibwe = "stawfive,jh7110-tdm", },
	{}
};

MODUWE_DEVICE_TABWE(of, jh7110_tdm_of_match);

static const stwuct dev_pm_ops jh7110_tdm_pm_ops = {
	WUNTIME_PM_OPS(jh7110_tdm_wuntime_suspend,
		       jh7110_tdm_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(jh7110_tdm_system_suspend,
			    jh7110_tdm_system_wesume)
};

static stwuct pwatfowm_dwivew jh7110_tdm_dwivew = {
	.dwivew = {
		.name = "jh7110-tdm",
		.of_match_tabwe = jh7110_tdm_of_match,
		.pm = pm_ptw(&jh7110_tdm_pm_ops),
	},
	.pwobe = jh7110_tdm_pwobe,
	.wemove_new = jh7110_tdm_dev_wemove,
};
moduwe_pwatfowm_dwivew(jh7110_tdm_dwivew);

MODUWE_DESCWIPTION("StawFive JH7110 TDM ASoC Dwivew");
MODUWE_AUTHOW("Wawkew Chen <wawkew.chen@stawfivetech.com>");
MODUWE_WICENSE("GPW");
