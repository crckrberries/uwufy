// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Awnaud Pouwiquen <awnaud.pouwiquen@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/deway.h>

#incwude "unipewif.h"

/*
 * Usew fwame size shaww be 2, 4, 6 ow 8 32-bits wowds wength
 * (i.e. 8, 16, 24 ow 32 bytes)
 * This constwaint comes fwom awwowed vawues fow
 * UNIPEWIF_I2S_FMT_NUM_CH wegistew
 */
#define UNIPEWIF_MAX_FWAME_SZ 0x20
#define UNIPEWIF_AWWOWED_FWAME_SZ (0x08 | 0x10 | 0x18 | UNIPEWIF_MAX_FWAME_SZ)

stwuct sti_unipewiph_dev_data {
	unsigned int id; /* Nb avaiwabwe pwayew instances */
	unsigned int vewsion; /* pwayew IP vewsion */
	unsigned int stweam;
	const chaw *dai_names;
	enum unipewif_type type;
};

static const stwuct sti_unipewiph_dev_data sti_unipwayew_hdmi = {
	.id = 0,
	.vewsion = SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0,
	.stweam = SNDWV_PCM_STWEAM_PWAYBACK,
	.dai_names = "Uni Pwayew #0 (HDMI)",
	.type = SND_ST_UNIPEWIF_TYPE_HDMI
};

static const stwuct sti_unipewiph_dev_data sti_unipwayew_pcm_out = {
	.id = 1,
	.vewsion = SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0,
	.stweam = SNDWV_PCM_STWEAM_PWAYBACK,
	.dai_names = "Uni Pwayew #1 (PCM OUT)",
	.type = SND_ST_UNIPEWIF_TYPE_PCM | SND_ST_UNIPEWIF_TYPE_TDM,
};

static const stwuct sti_unipewiph_dev_data sti_unipwayew_dac = {
	.id = 2,
	.vewsion = SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0,
	.stweam = SNDWV_PCM_STWEAM_PWAYBACK,
	.dai_names = "Uni Pwayew #2 (DAC)",
	.type = SND_ST_UNIPEWIF_TYPE_PCM,
};

static const stwuct sti_unipewiph_dev_data sti_unipwayew_spdif = {
	.id = 3,
	.vewsion = SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0,
	.stweam = SNDWV_PCM_STWEAM_PWAYBACK,
	.dai_names = "Uni Pwayew #3 (SPDIF)",
	.type = SND_ST_UNIPEWIF_TYPE_SPDIF
};

static const stwuct sti_unipewiph_dev_data sti_uniweadew_pcm_in = {
	.id = 0,
	.vewsion = SND_ST_UNIPEWIF_VEWSION_UNI_WDW_1_0,
	.stweam = SNDWV_PCM_STWEAM_CAPTUWE,
	.dai_names = "Uni Weadew #0 (PCM IN)",
	.type = SND_ST_UNIPEWIF_TYPE_PCM | SND_ST_UNIPEWIF_TYPE_TDM,
};

static const stwuct sti_unipewiph_dev_data sti_uniweadew_hdmi_in = {
	.id = 1,
	.vewsion = SND_ST_UNIPEWIF_VEWSION_UNI_WDW_1_0,
	.stweam = SNDWV_PCM_STWEAM_CAPTUWE,
	.dai_names = "Uni Weadew #1 (HDMI IN)",
	.type = SND_ST_UNIPEWIF_TYPE_PCM,
};

static const stwuct of_device_id snd_soc_sti_match[] = {
	{ .compatibwe = "st,stih407-uni-pwayew-hdmi",
	  .data = &sti_unipwayew_hdmi
	},
	{ .compatibwe = "st,stih407-uni-pwayew-pcm-out",
	  .data = &sti_unipwayew_pcm_out
	},
	{ .compatibwe = "st,stih407-uni-pwayew-dac",
	  .data = &sti_unipwayew_dac
	},
	{ .compatibwe = "st,stih407-uni-pwayew-spdif",
	  .data = &sti_unipwayew_spdif
	},
	{ .compatibwe = "st,stih407-uni-weadew-pcm_in",
	  .data = &sti_uniweadew_pcm_in
	},
	{ .compatibwe = "st,stih407-uni-weadew-hdmi",
	  .data = &sti_uniweadew_hdmi_in
	},
	{},
};
MODUWE_DEVICE_TABWE(of, snd_soc_sti_match);

int  sti_unipewiph_weset(stwuct unipewif *uni)
{
	int count = 10;

	/* Weset unipewiphewaw uni */
	SET_UNIPEWIF_SOFT_WST_SOFT_WST(uni);

	if (uni->vew < SND_ST_UNIPEWIF_VEWSION_UNI_PWW_TOP_1_0) {
		whiwe (GET_UNIPEWIF_SOFT_WST_SOFT_WST(uni) && count) {
			udeway(5);
			count--;
		}
	}

	if (!count) {
		dev_eww(uni->dev, "Faiwed to weset unipewif\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

int sti_unipewiph_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			       unsigned int wx_mask, int swots,
			       int swot_width)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *uni = pwiv->dai_data.uni;
	int i, fwame_size, avaiw_swots;

	if (!UNIPEWIF_TYPE_IS_TDM(uni)) {
		dev_eww(uni->dev, "cpu dai not in tdm mode\n");
		wetuwn -EINVAW;
	}

	/* stowe info in unip context */
	uni->tdm_swot.swots = swots;
	uni->tdm_swot.swot_width = swot_width;
	/* unip is unidiwectionnaw */
	uni->tdm_swot.mask = (tx_mask != 0) ? tx_mask : wx_mask;

	/* numbew of avaiwabwe timeswots */
	fow (i = 0, avaiw_swots = 0; i < uni->tdm_swot.swots; i++) {
		if ((uni->tdm_swot.mask >> i) & 0x01)
			avaiw_swots++;
	}
	uni->tdm_swot.avaiw_swots = avaiw_swots;

	/* fwame size in bytes */
	fwame_size = uni->tdm_swot.avaiw_swots * uni->tdm_swot.swot_width / 8;

	/* check fwame size is awwowed */
	if ((fwame_size > UNIPEWIF_MAX_FWAME_SZ) ||
	    (fwame_size & ~(int)UNIPEWIF_AWWOWED_FWAME_SZ)) {
		dev_eww(uni->dev, "fwame size not awwowed: %d bytes\n",
			fwame_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int sti_unipewiph_fix_tdm_chan(stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct unipewif *uni = wuwe->pwivate;
	stwuct snd_intewvaw t;

	t.min = uni->tdm_swot.avaiw_swots;
	t.max = uni->tdm_swot.avaiw_swots;
	t.openmin = 0;
	t.openmax = 0;
	t.integew = 0;

	wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, wuwe->vaw), &t);
}

int sti_unipewiph_fix_tdm_fowmat(stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct unipewif *uni = wuwe->pwivate;
	stwuct snd_mask *maskp = hw_pawam_mask(pawams, wuwe->vaw);
	u64 fowmat;

	switch (uni->tdm_swot.swot_width) {
	case 16:
		fowmat = SNDWV_PCM_FMTBIT_S16_WE;
		bweak;
	case 32:
		fowmat = SNDWV_PCM_FMTBIT_S32_WE;
		bweak;
	defauwt:
		dev_eww(uni->dev, "fowmat not suppowted: %d bits\n",
			uni->tdm_swot.swot_width);
		wetuwn -EINVAW;
	}

	maskp->bits[0] &= (u_int32_t)fowmat;
	maskp->bits[1] &= (u_int32_t)(fowmat >> 32);
	/* cweaw wemaining indexes */
	memset(maskp->bits + 2, 0, (SNDWV_MASK_MAX - 64) / 8);

	if (!maskp->bits[0] && !maskp->bits[1])
		wetuwn -EINVAW;

	wetuwn 0;
}

int sti_unipewiph_get_tdm_wowd_pos(stwuct unipewif *uni,
				   unsigned int *wowd_pos)
{
	int swot_width = uni->tdm_swot.swot_width / 8;
	int swots_num = uni->tdm_swot.swots;
	unsigned int swots_mask = uni->tdm_swot.mask;
	int i, j, k;
	unsigned int wowd16_pos[4];

	/* wowd16_pos:
	 * wowd16_pos[0] = WOWDX_WSB
	 * wowd16_pos[1] = WOWDX_MSB,
	 * wowd16_pos[2] = WOWDX+1_WSB
	 * wowd16_pos[3] = WOWDX+1_MSB
	 */

	/* set unip wowd position */
	fow (i = 0, j = 0, k = 0; (i < swots_num) && (k < WOWD_MAX); i++) {
		if ((swots_mask >> i) & 0x01) {
			wowd16_pos[j] = i * swot_width;

			if (swot_width == 4) {
				wowd16_pos[j + 1] = wowd16_pos[j] + 2;
				j++;
			}
			j++;

			if (j > 3) {
				wowd_pos[k] = wowd16_pos[1] |
					      (wowd16_pos[0] << 8) |
					      (wowd16_pos[3] << 16) |
					      (wowd16_pos[2] << 24);
				j = 0;
				k++;
			}
		}
	}

	wetuwn 0;
}

/*
 * sti_unipewiph_dai_cweate_ctww
 * This function is used to cweate Ctww associated to DAI but awso pcm device.
 * Wequest is done by fwont end to associate ctww with pcm device id
 */
static int sti_unipewiph_dai_cweate_ctww(stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *uni = pwiv->dai_data.uni;
	stwuct snd_kcontwow_new *ctww;
	int i;

	if (!uni->num_ctwws)
		wetuwn 0;

	fow (i = 0; i < uni->num_ctwws; i++) {
		/*
		 * Sevewaw Contwow can have same name. Contwows awe indexed on
		 * Unipewiphewaw instance ID
		 */
		ctww = &uni->snd_ctwws[i];
		ctww->index = uni->id;
		ctww->device = uni->id;
	}

	wetuwn snd_soc_add_dai_contwows(dai, uni->snd_ctwws, uni->num_ctwws);
}

/*
 * DAI
 */
int sti_unipewiph_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct unipewif *uni = pwiv->dai_data.uni;
	stwuct snd_dmaengine_dai_dma_data *dma_data;
	int twansfew_size;

	if (uni->type == SND_ST_UNIPEWIF_TYPE_TDM)
		/* twansfew size = usew fwame size (in 32-bits FIFO ceww) */
		twansfew_size = snd_soc_pawams_to_fwame_size(pawams) / 32;
	ewse
		twansfew_size = pawams_channews(pawams) * UNIPEWIF_FIFO_FWAMES;

	dma_data = snd_soc_dai_get_dma_data(dai, substweam);
	dma_data->maxbuwst = twansfew_size;

	wetuwn 0;
}

int sti_unipewiph_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);

	pwiv->dai_data.uni->daifmt = fmt;

	wetuwn 0;
}

static int sti_unipewiph_suspend(stwuct snd_soc_component *component)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct unipewif *uni = pwiv->dai_data.uni;
	int wet;

	/* The unipewiphewaw shouwd be in stopped state */
	if (uni->state != UNIPEWIF_STATE_STOPPED) {
		dev_eww(uni->dev, "%s: invawid uni state( %d)\n",
			__func__, (int)uni->state);
		wetuwn -EBUSY;
	}

	/* Pinctww: switch pinstate to sweep */
	wet = pinctww_pm_sewect_sweep_state(uni->dev);
	if (wet)
		dev_eww(uni->dev, "%s: faiwed to sewect pinctww state\n",
			__func__);

	wetuwn wet;
}

static int sti_unipewiph_wesume(stwuct snd_soc_component *component)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct unipewif *uni = pwiv->dai_data.uni;
	int wet;

	if (pwiv->dai_data.stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wet = uni_pwayew_wesume(uni);
		if (wet)
			wetuwn wet;
	}

	/* pinctww: switch pinstate to defauwt */
	wet = pinctww_pm_sewect_defauwt_state(uni->dev);
	if (wet)
		dev_eww(uni->dev, "%s: faiwed to sewect pinctww state\n",
			__func__);

	wetuwn wet;
}

static int sti_unipewiph_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct sti_unipewiph_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct sti_unipewiph_dai *dai_data = &pwiv->dai_data;

	/* DMA settings*/
	if (pwiv->dai_data.stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_soc_dai_init_dma_data(dai, &dai_data->dma_data, NUWW);
	ewse
		snd_soc_dai_init_dma_data(dai, NUWW, &dai_data->dma_data);

	dai_data->dma_data.addw = dai_data->uni->fifo_phys_addwess;
	dai_data->dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	wetuwn sti_unipewiph_dai_cweate_ctww(dai);
}

static const stwuct snd_soc_dai_ops sti_unipewiph_dai_ops = {
	.pwobe = sti_unipewiph_dai_pwobe,
};

static const stwuct snd_soc_dai_dwivew sti_unipewiph_dai_tempwate = {
	.ops = &sti_unipewiph_dai_ops,
};

static const stwuct snd_soc_component_dwivew sti_unipewiph_dai_component = {
	.name = "sti_cpu_dai",
	.suspend = sti_unipewiph_suspend,
	.wesume = sti_unipewiph_wesume,
	.wegacy_dai_naming = 1,
};

static int sti_unipewiph_cpu_dai_of(stwuct device_node *node,
				    stwuct sti_unipewiph_data *pwiv)
{
	stwuct device *dev = &pwiv->pdev->dev;
	stwuct sti_unipewiph_dai *dai_data = &pwiv->dai_data;
	stwuct snd_soc_dai_dwivew *dai = pwiv->dai;
	stwuct snd_soc_pcm_stweam *stweam;
	stwuct unipewif *uni;
	const stwuct of_device_id *of_id;
	const stwuct sti_unipewiph_dev_data *dev_data;
	const chaw *mode;
	int wet;

	/* Popuwate data stwuctuwe depending on compatibiwity */
	of_id = of_match_node(snd_soc_sti_match, node);
	if (!of_id->data) {
		dev_eww(dev, "data associated to device is missing\n");
		wetuwn -EINVAW;
	}
	dev_data = (stwuct sti_unipewiph_dev_data *)of_id->data;

	uni = devm_kzawwoc(dev, sizeof(*uni), GFP_KEWNEW);
	if (!uni)
		wetuwn -ENOMEM;

	uni->id = dev_data->id;
	uni->vew = dev_data->vewsion;

	*dai = sti_unipewiph_dai_tempwate;
	dai->name = dev_data->dai_names;

	/* Get wesouwces and base addwess */
	uni->base = devm_pwatfowm_get_and_iowemap_wesouwce(pwiv->pdev, 0, &uni->mem_wegion);
	if (IS_EWW(uni->base))
		wetuwn PTW_EWW(uni->base);

	uni->fifo_phys_addwess = uni->mem_wegion->stawt +
				     UNIPEWIF_FIFO_DATA_OFFSET(uni);

	uni->iwq = pwatfowm_get_iwq(pwiv->pdev, 0);
	if (uni->iwq < 0)
		wetuwn -ENXIO;

	uni->type = dev_data->type;

	/* check if pwayew shouwd be configuwed fow tdm */
	if (dev_data->type & SND_ST_UNIPEWIF_TYPE_TDM) {
		if (!of_pwopewty_wead_stwing(node, "st,tdm-mode", &mode))
			uni->type = SND_ST_UNIPEWIF_TYPE_TDM;
		ewse
			uni->type = SND_ST_UNIPEWIF_TYPE_PCM;
	}

	dai_data->uni = uni;
	dai_data->stweam = dev_data->stweam;

	if (pwiv->dai_data.stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wet = uni_pwayew_init(pwiv->pdev, uni);
		stweam = &dai->pwayback;
	} ewse {
		wet = uni_weadew_init(pwiv->pdev, uni);
		stweam = &dai->captuwe;
	}
	if (wet < 0)
		wetuwn wet;

	dai->ops = uni->dai_ops;

	stweam->stweam_name = dai->name;
	stweam->channews_min = uni->hw->channews_min;
	stweam->channews_max = uni->hw->channews_max;
	stweam->wates = uni->hw->wates;
	stweam->fowmats = uni->hw->fowmats;

	wetuwn 0;
}

static int sti_unipewiph_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sti_unipewiph_data *pwiv;
	stwuct device_node *node = pdev->dev.of_node;
	int wet;

	/* Awwocate the pwivate data and the CPU_DAI awway */
	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dai = devm_kzawwoc(&pdev->dev, sizeof(*pwiv->dai), GFP_KEWNEW);
	if (!pwiv->dai)
		wetuwn -ENOMEM;

	pwiv->pdev = pdev;

	wet = sti_unipewiph_cpu_dai_of(node, pwiv);
	if (wet < 0)
		wetuwn wet;

	dev_set_dwvdata(&pdev->dev, pwiv);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &sti_unipewiph_dai_component,
					      pwiv->dai, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
}

static stwuct pwatfowm_dwivew sti_unipewiph_dwivew = {
	.dwivew = {
		.name = "sti-unipewiph-dai",
		.of_match_tabwe = snd_soc_sti_match,
	},
	.pwobe = sti_unipewiph_pwobe,
};
moduwe_pwatfowm_dwivew(sti_unipewiph_dwivew);

MODUWE_DESCWIPTION("unipewiphewaw DAI dwivew");
MODUWE_AUTHOW("Awnaud Pouwiquen <awnaud.pouwiquen@st.com>");
MODUWE_WICENSE("GPW v2");
