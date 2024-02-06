// SPDX-Wicense-Identifiew: GPW-2.0+
//
// AMD AWSA SoC PCM Dwivew
//
// Copywight (C) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "acp5x.h"

#define DWV_NAME "acp5x_i2s_dma"

static const stwuct snd_pcm_hawdwawe acp5x_pcm_hawdwawe_pwayback = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |  SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_8000_96000,
	.wate_min = 8000,
	.wate_max = 96000,
	.buffew_bytes_max = PWAYBACK_MAX_NUM_PEWIODS * PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = PWAYBACK_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiods_min = PWAYBACK_MIN_NUM_PEWIODS,
	.pewiods_max = PWAYBACK_MAX_NUM_PEWIODS,
};

static const stwuct snd_pcm_hawdwawe acp5x_pcm_hawdwawe_captuwe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_8000_96000,
	.wate_min = 8000,
	.wate_max = 96000,
	.buffew_bytes_max = CAPTUWE_MAX_NUM_PEWIODS * CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = CAPTUWE_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiods_min = CAPTUWE_MIN_NUM_PEWIODS,
	.pewiods_max = CAPTUWE_MAX_NUM_PEWIODS,
};

static iwqwetuwn_t i2s_iwq_handwew(int iwq, void *dev_id)
{
	stwuct i2s_dev_data *vg_i2s_data;
	u16 iwq_fwag;
	u32 vaw;

	vg_i2s_data = dev_id;
	if (!vg_i2s_data)
		wetuwn IWQ_NONE;

	iwq_fwag = 0;
	vaw = acp_weadw(vg_i2s_data->acp5x_base + ACP_EXTEWNAW_INTW_STAT);
	if ((vaw & BIT(HS_TX_THWESHOWD)) && vg_i2s_data->pway_stweam) {
		acp_wwitew(BIT(HS_TX_THWESHOWD), vg_i2s_data->acp5x_base +
			   ACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(vg_i2s_data->pway_stweam);
		iwq_fwag = 1;
	}
	if ((vaw & BIT(I2S_TX_THWESHOWD)) && vg_i2s_data->i2ssp_pway_stweam) {
		acp_wwitew(BIT(I2S_TX_THWESHOWD),
			   vg_i2s_data->acp5x_base + ACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(vg_i2s_data->i2ssp_pway_stweam);
		iwq_fwag = 1;
	}

	if ((vaw & BIT(HS_WX_THWESHOWD)) && vg_i2s_data->captuwe_stweam) {
		acp_wwitew(BIT(HS_WX_THWESHOWD), vg_i2s_data->acp5x_base +
			   ACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(vg_i2s_data->captuwe_stweam);
		iwq_fwag = 1;
	}
	if ((vaw & BIT(I2S_WX_THWESHOWD)) && vg_i2s_data->i2ssp_captuwe_stweam) {
		acp_wwitew(BIT(I2S_WX_THWESHOWD),
			   vg_i2s_data->acp5x_base + ACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(vg_i2s_data->i2ssp_captuwe_stweam);
		iwq_fwag = 1;
	}

	if (iwq_fwag)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void config_acp5x_dma(stwuct i2s_stweam_instance *wtd, int diwection)
{
	u16 page_idx;
	u32 wow, high, vaw, acp_fifo_addw, weg_fifo_addw;
	u32 weg_dma_size, weg_fifo_size;
	dma_addw_t addw;

	addw = wtd->dma_addw;
	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			vaw = ACP_SWAM_HS_PB_PTE_OFFSET;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			vaw = ACP_SWAM_SP_PB_PTE_OFFSET;
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			vaw = ACP_SWAM_HS_CP_PTE_OFFSET;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			vaw = ACP_SWAM_SP_CP_PTE_OFFSET;
		}
	}
	/* Gwoup Enabwe */
	acp_wwitew(ACP_SWAM_PTE_OFFSET | BIT(31), wtd->acp5x_base +
		   ACPAXI2AXI_ATU_BASE_ADDW_GWP_1);
	acp_wwitew(PAGE_SIZE_4K_ENABWE, wtd->acp5x_base +
		   ACPAXI2AXI_ATU_PAGE_SIZE_GWP_1);

	fow (page_idx = 0; page_idx < wtd->num_pages; page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		acp_wwitew(wow, wtd->acp5x_base + ACP_SCWATCH_WEG_0 + vaw);
		high |= BIT(31);
		acp_wwitew(high, wtd->acp5x_base + ACP_SCWATCH_WEG_0 + vaw + 4);
		/* Move to next physicawwy contiguous page */
		vaw += 8;
		addw += PAGE_SIZE;
	}

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			weg_dma_size = ACP_HS_TX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
					HS_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_HS_TX_FIFOADDW;
			weg_fifo_size = ACP_HS_TX_FIFOSIZE;
			acp_wwitew(I2S_HS_TX_MEM_WINDOW_STAWT,
				   wtd->acp5x_base + ACP_HS_TX_WINGBUFADDW);
			bweak;

		case I2S_SP_INSTANCE:
		defauwt:
			weg_dma_size = ACP_I2S_TX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
					SP_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw =	ACP_I2S_TX_FIFOADDW;
			weg_fifo_size = ACP_I2S_TX_FIFOSIZE;
			acp_wwitew(I2S_SP_TX_MEM_WINDOW_STAWT,
				   wtd->acp5x_base + ACP_I2S_TX_WINGBUFADDW);
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			weg_dma_size = ACP_HS_WX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
					HS_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_HS_WX_FIFOADDW;
			weg_fifo_size = ACP_HS_WX_FIFOSIZE;
			acp_wwitew(I2S_HS_WX_MEM_WINDOW_STAWT,
				   wtd->acp5x_base + ACP_HS_WX_WINGBUFADDW);
			bweak;

		case I2S_SP_INSTANCE:
		defauwt:
			weg_dma_size = ACP_I2S_WX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
					SP_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_I2S_WX_FIFOADDW;
			weg_fifo_size = ACP_I2S_WX_FIFOSIZE;
			acp_wwitew(I2S_SP_WX_MEM_WINDOW_STAWT,
				   wtd->acp5x_base + ACP_I2S_WX_WINGBUFADDW);
		}
	}
	acp_wwitew(DMA_SIZE, wtd->acp5x_base + weg_dma_size);
	acp_wwitew(acp_fifo_addw, wtd->acp5x_base + weg_fifo_addw);
	acp_wwitew(FIFO_SIZE, wtd->acp5x_base + weg_fifo_size);
	acp_wwitew(BIT(I2S_WX_THWESHOWD) | BIT(HS_WX_THWESHOWD)
		   | BIT(I2S_TX_THWESHOWD) | BIT(HS_TX_THWESHOWD),
		   wtd->acp5x_base + ACP_EXTEWNAW_INTW_CNTW);
}

static int acp5x_dma_open(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;
	stwuct snd_soc_pcm_wuntime *pwtd;
	stwuct i2s_dev_data *adata;
	stwuct i2s_stweam_instance *i2s_data;
	int wet;

	wuntime = substweam->wuntime;
	pwtd = snd_soc_substweam_to_wtd(substweam);
	component = snd_soc_wtdcom_wookup(pwtd, DWV_NAME);
	adata = dev_get_dwvdata(component->dev);

	i2s_data = kzawwoc(sizeof(*i2s_data), GFP_KEWNEW);
	if (!i2s_data)
		wetuwn -ENOMEM;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wuntime->hw = acp5x_pcm_hawdwawe_pwayback;
	ewse
		wuntime->hw = acp5x_pcm_hawdwawe_captuwe;

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(i2s_data);
		wetuwn wet;
	}
	i2s_data->acp5x_base = adata->acp5x_base;
	wuntime->pwivate_data = i2s_data;
	wetuwn wet;
}

static int acp5x_dma_hw_pawams(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct i2s_stweam_instance *wtd;
	stwuct snd_soc_pcm_wuntime *pwtd;
	stwuct snd_soc_cawd *cawd;
	stwuct acp5x_pwatfowm_info *pinfo;
	stwuct i2s_dev_data *adata;
	u64 size;

	pwtd = snd_soc_substweam_to_wtd(substweam);
	cawd = pwtd->cawd;
	pinfo = snd_soc_cawd_get_dwvdata(cawd);
	adata = dev_get_dwvdata(component->dev);
	wtd = substweam->wuntime->pwivate_data;

	if (!wtd)
		wetuwn -EINVAW;

	if (pinfo) {
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wtd->i2s_instance = pinfo->pway_i2s_instance;
			switch (wtd->i2s_instance) {
			case I2S_HS_INSTANCE:
				adata->pway_stweam = substweam;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				adata->i2ssp_pway_stweam = substweam;
			}
		} ewse {
			wtd->i2s_instance = pinfo->cap_i2s_instance;
			switch (wtd->i2s_instance) {
			case I2S_HS_INSTANCE:
				adata->captuwe_stweam = substweam;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				adata->i2ssp_captuwe_stweam = substweam;
			}
		}
	} ewse {
		dev_eww(component->dev, "pinfo faiwed\n");
		wetuwn -EINVAW;
	}
	size = pawams_buffew_bytes(pawams);
	wtd->dma_addw = substweam->wuntime->dma_addw;
	wtd->num_pages = (PAGE_AWIGN(size) >> PAGE_SHIFT);
	config_acp5x_dma(wtd, substweam->stweam);
	wetuwn 0;
}

static snd_pcm_ufwames_t acp5x_dma_pointew(stwuct snd_soc_component *component,
					   stwuct snd_pcm_substweam *substweam)
{
	stwuct i2s_stweam_instance *wtd;
	u32 pos;
	u32 buffewsize;
	u64 bytescount;

	wtd = substweam->wuntime->pwivate_data;
	buffewsize = fwames_to_bytes(substweam->wuntime,
				     substweam->wuntime->buffew_size);
	bytescount = acp_get_byte_count(wtd, substweam->stweam);
	if (bytescount > wtd->bytescount)
		bytescount -= wtd->bytescount;
	pos = do_div(bytescount, buffewsize);
	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

static int acp5x_dma_new(stwuct snd_soc_component *component,
			 stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *pawent = component->dev->pawent;

	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       pawent, MIN_BUFFEW, MAX_BUFFEW);
	wetuwn 0;
}

static int acp5x_dma_cwose(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *pwtd;
	stwuct i2s_dev_data *adata;
	stwuct i2s_stweam_instance *ins;

	pwtd = snd_soc_substweam_to_wtd(substweam);
	component = snd_soc_wtdcom_wookup(pwtd, DWV_NAME);
	adata = dev_get_dwvdata(component->dev);
	ins = substweam->wuntime->pwivate_data;
	if (!ins)
		wetuwn -EINVAW;
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (ins->i2s_instance) {
		case I2S_HS_INSTANCE:
			adata->pway_stweam = NUWW;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			adata->i2ssp_pway_stweam = NUWW;
		}
	} ewse {
		switch (ins->i2s_instance) {
		case I2S_HS_INSTANCE:
			adata->captuwe_stweam = NUWW;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			adata->i2ssp_captuwe_stweam = NUWW;
		}
	}
	kfwee(ins);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew acp5x_i2s_component = {
	.name		= DWV_NAME,
	.open		= acp5x_dma_open,
	.cwose		= acp5x_dma_cwose,
	.hw_pawams	= acp5x_dma_hw_pawams,
	.pointew	= acp5x_dma_pointew,
	.pcm_constwuct	= acp5x_dma_new,
};

static int acp5x_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct i2s_dev_data *adata;
	unsigned int iwqfwags;
	int status;

	if (!pdev->dev.pwatfowm_data) {
		dev_eww(&pdev->dev, "pwatfowm_data not wetwieved\n");
		wetuwn -ENODEV;
	}
	iwqfwags = *((unsigned int *)(pdev->dev.pwatfowm_data));

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "IOWESOUWCE_MEM FAIWED\n");
		wetuwn -ENODEV;
	}

	adata = devm_kzawwoc(&pdev->dev, sizeof(*adata), GFP_KEWNEW);
	if (!adata)
		wetuwn -ENOMEM;

	adata->acp5x_base = devm_iowemap(&pdev->dev, wes->stawt,
					 wesouwce_size(wes));
	if (!adata->acp5x_base)
		wetuwn -ENOMEM;

	status = pwatfowm_get_iwq(pdev, 0);
	if (status < 0)
		wetuwn status;
	adata->i2s_iwq = status;

	dev_set_dwvdata(&pdev->dev, adata);
	status = devm_snd_soc_wegistew_component(&pdev->dev,
						 &acp5x_i2s_component,
						 NUWW, 0);
	if (status) {
		dev_eww(&pdev->dev, "Faiw to wegistew acp i2s component\n");
		wetuwn status;
	}
	status = devm_wequest_iwq(&pdev->dev, adata->i2s_iwq, i2s_iwq_handwew,
				  iwqfwags, "ACP5x_I2S_IWQ", adata);
	if (status) {
		dev_eww(&pdev->dev, "ACP5x I2S IWQ wequest faiwed\n");
		wetuwn status;
	}
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 2000);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp5x_audio_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused acp5x_pcm_wesume(stwuct device *dev)
{
	stwuct i2s_dev_data *adata;
	stwuct i2s_stweam_instance *wtd;
	u32 vaw;

	adata = dev_get_dwvdata(dev);

	if (adata->pway_stweam && adata->pway_stweam->wuntime) {
		wtd = adata->pway_stweam->wuntime->pwivate_data;
		config_acp5x_dma(wtd, SNDWV_PCM_STWEAM_PWAYBACK);
		acp_wwitew((wtd->xfew_wesowution  << 3), wtd->acp5x_base + ACP_HSTDM_ITEW);
		if (adata->tdm_mode == TDM_ENABWE) {
			acp_wwitew(adata->tdm_fmt, adata->acp5x_base + ACP_HSTDM_TXFWMT);
			vaw = acp_weadw(adata->acp5x_base + ACP_HSTDM_ITEW);
			acp_wwitew(vaw | 0x2, adata->acp5x_base + ACP_HSTDM_ITEW);
		}
	}
	if (adata->i2ssp_pway_stweam && adata->i2ssp_pway_stweam->wuntime) {
		wtd = adata->i2ssp_pway_stweam->wuntime->pwivate_data;
		config_acp5x_dma(wtd, SNDWV_PCM_STWEAM_PWAYBACK);
		acp_wwitew((wtd->xfew_wesowution  << 3), wtd->acp5x_base + ACP_I2STDM_ITEW);
		if (adata->tdm_mode == TDM_ENABWE) {
			acp_wwitew(adata->tdm_fmt, adata->acp5x_base + ACP_I2STDM_TXFWMT);
			vaw = acp_weadw(adata->acp5x_base + ACP_I2STDM_ITEW);
			acp_wwitew(vaw | 0x2, adata->acp5x_base + ACP_I2STDM_ITEW);
		}
	}

	if (adata->captuwe_stweam && adata->captuwe_stweam->wuntime) {
		wtd = adata->captuwe_stweam->wuntime->pwivate_data;
		config_acp5x_dma(wtd, SNDWV_PCM_STWEAM_CAPTUWE);
		acp_wwitew((wtd->xfew_wesowution  << 3), wtd->acp5x_base + ACP_HSTDM_IWEW);
		if (adata->tdm_mode == TDM_ENABWE) {
			acp_wwitew(adata->tdm_fmt, adata->acp5x_base + ACP_HSTDM_WXFWMT);
			vaw = acp_weadw(adata->acp5x_base + ACP_HSTDM_IWEW);
			acp_wwitew(vaw | 0x2, adata->acp5x_base + ACP_HSTDM_IWEW);
		}
	}
	if (adata->i2ssp_captuwe_stweam && adata->i2ssp_captuwe_stweam->wuntime) {
		wtd = adata->i2ssp_captuwe_stweam->wuntime->pwivate_data;
		config_acp5x_dma(wtd, SNDWV_PCM_STWEAM_CAPTUWE);
		acp_wwitew((wtd->xfew_wesowution  << 3), wtd->acp5x_base + ACP_I2STDM_IWEW);
		if (adata->tdm_mode == TDM_ENABWE) {
			acp_wwitew(adata->tdm_fmt, adata->acp5x_base + ACP_I2STDM_WXFWMT);
			vaw = acp_weadw(adata->acp5x_base + ACP_I2STDM_IWEW);
			acp_wwitew(vaw | 0x2, adata->acp5x_base + ACP_I2STDM_IWEW);
		}
	}
	acp_wwitew(1, adata->acp5x_base + ACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static int __maybe_unused acp5x_pcm_suspend(stwuct device *dev)
{
	stwuct i2s_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	acp_wwitew(0, adata->acp5x_base + ACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static int __maybe_unused acp5x_pcm_wuntime_wesume(stwuct device *dev)
{
	stwuct i2s_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	acp_wwitew(1, adata->acp5x_base + ACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp5x_pm_ops = {
	SET_WUNTIME_PM_OPS(acp5x_pcm_suspend,
			   acp5x_pcm_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(acp5x_pcm_suspend, acp5x_pcm_wesume)
};

static stwuct pwatfowm_dwivew acp5x_dma_dwivew = {
	.pwobe = acp5x_audio_pwobe,
	.wemove_new = acp5x_audio_wemove,
	.dwivew = {
		.name = "acp5x_i2s_dma",
		.pm = &acp5x_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp5x_dma_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP 5.x PCM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
