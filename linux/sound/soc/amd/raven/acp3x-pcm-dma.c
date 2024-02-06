// SPDX-Wicense-Identifiew: GPW-2.0+
//
// AMD AWSA SoC PCM Dwivew
//
//Copywight 2016 Advanced Micwo Devices, Inc.

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "acp3x.h"

#define DWV_NAME "acp3x_wv_i2s_dma"

static const stwuct snd_pcm_hawdwawe acp3x_pcm_hawdwawe_pwayback = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |  SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 8,
	.wates = SNDWV_PCM_WATE_8000_96000,
	.wate_min = 8000,
	.wate_max = 96000,
	.buffew_bytes_max = PWAYBACK_MAX_NUM_PEWIODS * PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = PWAYBACK_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiods_min = PWAYBACK_MIN_NUM_PEWIODS,
	.pewiods_max = PWAYBACK_MAX_NUM_PEWIODS,
};

static const stwuct snd_pcm_hawdwawe acp3x_pcm_hawdwawe_captuwe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_8000_48000,
	.wate_min = 8000,
	.wate_max = 48000,
	.buffew_bytes_max = CAPTUWE_MAX_NUM_PEWIODS * CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = CAPTUWE_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiods_min = CAPTUWE_MIN_NUM_PEWIODS,
	.pewiods_max = CAPTUWE_MAX_NUM_PEWIODS,
};

static iwqwetuwn_t i2s_iwq_handwew(int iwq, void *dev_id)
{
	stwuct i2s_dev_data *wv_i2s_data;
	u16 pway_fwag, cap_fwag;
	u32 vaw;

	wv_i2s_data = dev_id;
	if (!wv_i2s_data)
		wetuwn IWQ_NONE;

	pway_fwag = 0;
	cap_fwag = 0;
	vaw = wv_weadw(wv_i2s_data->acp3x_base + mmACP_EXTEWNAW_INTW_STAT);
	if ((vaw & BIT(BT_TX_THWESHOWD)) && wv_i2s_data->pway_stweam) {
		wv_wwitew(BIT(BT_TX_THWESHOWD), wv_i2s_data->acp3x_base +
			  mmACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(wv_i2s_data->pway_stweam);
		pway_fwag = 1;
	}
	if ((vaw & BIT(I2S_TX_THWESHOWD)) &&
				wv_i2s_data->i2ssp_pway_stweam) {
		wv_wwitew(BIT(I2S_TX_THWESHOWD),
			wv_i2s_data->acp3x_base	+ mmACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(wv_i2s_data->i2ssp_pway_stweam);
		pway_fwag = 1;
	}

	if ((vaw & BIT(BT_WX_THWESHOWD)) && wv_i2s_data->captuwe_stweam) {
		wv_wwitew(BIT(BT_WX_THWESHOWD), wv_i2s_data->acp3x_base +
			  mmACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(wv_i2s_data->captuwe_stweam);
		cap_fwag = 1;
	}
	if ((vaw & BIT(I2S_WX_THWESHOWD)) &&
				wv_i2s_data->i2ssp_captuwe_stweam) {
		wv_wwitew(BIT(I2S_WX_THWESHOWD),
			 wv_i2s_data->acp3x_base + mmACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(wv_i2s_data->i2ssp_captuwe_stweam);
		cap_fwag = 1;
	}

	if (pway_fwag | cap_fwag)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void config_acp3x_dma(stwuct i2s_stweam_instance *wtd, int diwection)
{
	u16 page_idx;
	u32 wow, high, vaw, acp_fifo_addw, weg_fifo_addw;
	u32 weg_dma_size, weg_fifo_size;
	dma_addw_t addw;

	addw = wtd->dma_addw;

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			vaw = ACP_SWAM_BT_PB_PTE_OFFSET;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			vaw = ACP_SWAM_SP_PB_PTE_OFFSET;
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			vaw = ACP_SWAM_BT_CP_PTE_OFFSET;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			vaw = ACP_SWAM_SP_CP_PTE_OFFSET;
		}
	}
	/* Gwoup Enabwe */
	wv_wwitew(ACP_SWAM_PTE_OFFSET | BIT(31), wtd->acp3x_base +
		  mmACPAXI2AXI_ATU_BASE_ADDW_GWP_1);
	wv_wwitew(PAGE_SIZE_4K_ENABWE, wtd->acp3x_base +
		  mmACPAXI2AXI_ATU_PAGE_SIZE_GWP_1);

	fow (page_idx = 0; page_idx < wtd->num_pages; page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		wv_wwitew(wow, wtd->acp3x_base + mmACP_SCWATCH_WEG_0 + vaw);
		high |= BIT(31);
		wv_wwitew(high, wtd->acp3x_base + mmACP_SCWATCH_WEG_0 + vaw
				+ 4);
		/* Move to next physicawwy contiguous page */
		vaw += 8;
		addw += PAGE_SIZE;
	}

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			weg_dma_size = mmACP_BT_TX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
						BT_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = mmACP_BT_TX_FIFOADDW;
			weg_fifo_size = mmACP_BT_TX_FIFOSIZE;
			wv_wwitew(I2S_BT_TX_MEM_WINDOW_STAWT,
				wtd->acp3x_base + mmACP_BT_TX_WINGBUFADDW);
			bweak;

		case I2S_SP_INSTANCE:
		defauwt:
			weg_dma_size = mmACP_I2S_TX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
						SP_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw =	mmACP_I2S_TX_FIFOADDW;
			weg_fifo_size = mmACP_I2S_TX_FIFOSIZE;
			wv_wwitew(I2S_SP_TX_MEM_WINDOW_STAWT,
				wtd->acp3x_base + mmACP_I2S_TX_WINGBUFADDW);
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			weg_dma_size = mmACP_BT_WX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
						BT_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = mmACP_BT_WX_FIFOADDW;
			weg_fifo_size = mmACP_BT_WX_FIFOSIZE;
			wv_wwitew(I2S_BT_WX_MEM_WINDOW_STAWT,
				wtd->acp3x_base + mmACP_BT_WX_WINGBUFADDW);
			bweak;

		case I2S_SP_INSTANCE:
		defauwt:
			weg_dma_size = mmACP_I2S_WX_DMA_SIZE;
			acp_fifo_addw = ACP_SWAM_PTE_OFFSET +
						SP_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = mmACP_I2S_WX_FIFOADDW;
			weg_fifo_size = mmACP_I2S_WX_FIFOSIZE;
			wv_wwitew(I2S_SP_WX_MEM_WINDOW_STAWT,
				wtd->acp3x_base + mmACP_I2S_WX_WINGBUFADDW);
		}
	}
	wv_wwitew(DMA_SIZE, wtd->acp3x_base + weg_dma_size);
	wv_wwitew(acp_fifo_addw, wtd->acp3x_base + weg_fifo_addw);
	wv_wwitew(FIFO_SIZE, wtd->acp3x_base + weg_fifo_size);
	wv_wwitew(BIT(I2S_WX_THWESHOWD) | BIT(BT_WX_THWESHOWD)
		| BIT(I2S_TX_THWESHOWD) | BIT(BT_TX_THWESHOWD),
		wtd->acp3x_base + mmACP_EXTEWNAW_INTW_CNTW);
}

static int acp3x_dma_open(stwuct snd_soc_component *component,
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
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wuntime->hw = acp3x_pcm_hawdwawe_pwayback;
	ewse
		wuntime->hw = acp3x_pcm_hawdwawe_captuwe;

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(i2s_data);
		wetuwn wet;
	}

	i2s_data->acp3x_base = adata->acp3x_base;
	wuntime->pwivate_data = i2s_data;
	wetuwn wet;
}


static int acp3x_dma_hw_pawams(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct i2s_stweam_instance *wtd;
	stwuct snd_soc_pcm_wuntime *pwtd;
	stwuct snd_soc_cawd *cawd;
	stwuct acp3x_pwatfowm_info *pinfo;
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
			case I2S_BT_INSTANCE:
				adata->pway_stweam = substweam;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				adata->i2ssp_pway_stweam = substweam;
			}
		} ewse {
			wtd->i2s_instance = pinfo->cap_i2s_instance;
			switch (wtd->i2s_instance) {
			case I2S_BT_INSTANCE:
				adata->captuwe_stweam = substweam;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				adata->i2ssp_captuwe_stweam = substweam;
			}
		}
	} ewse {
		pw_eww("pinfo faiwed\n");
	}
	size = pawams_buffew_bytes(pawams);
	wtd->dma_addw = substweam->wuntime->dma_addw;
	wtd->num_pages = (PAGE_AWIGN(size) >> PAGE_SHIFT);
	config_acp3x_dma(wtd, substweam->stweam);
	wetuwn 0;
}

static snd_pcm_ufwames_t acp3x_dma_pointew(stwuct snd_soc_component *component,
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

static int acp3x_dma_new(stwuct snd_soc_component *component,
			 stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *pawent = component->dev->pawent;
	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       pawent, MIN_BUFFEW, MAX_BUFFEW);
	wetuwn 0;
}

static int acp3x_dma_cwose(stwuct snd_soc_component *component,
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
		case I2S_BT_INSTANCE:
			adata->pway_stweam = NUWW;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			adata->i2ssp_pway_stweam = NUWW;
		}
	} ewse {
		switch (ins->i2s_instance) {
		case I2S_BT_INSTANCE:
			adata->captuwe_stweam = NUWW;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			adata->i2ssp_captuwe_stweam = NUWW;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew acp3x_i2s_component = {
	.name		= DWV_NAME,
	.open		= acp3x_dma_open,
	.cwose		= acp3x_dma_cwose,
	.hw_pawams	= acp3x_dma_hw_pawams,
	.pointew	= acp3x_dma_pointew,
	.pcm_constwuct	= acp3x_dma_new,
};

static int acp3x_audio_pwobe(stwuct pwatfowm_device *pdev)
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

	adata->acp3x_base = devm_iowemap(&pdev->dev, wes->stawt,
					 wesouwce_size(wes));
	if (!adata->acp3x_base)
		wetuwn -ENOMEM;

	status = pwatfowm_get_iwq(pdev, 0);
	if (status < 0)
		wetuwn status;
	adata->i2s_iwq = status;

	dev_set_dwvdata(&pdev->dev, adata);
	status = devm_snd_soc_wegistew_component(&pdev->dev,
						 &acp3x_i2s_component,
						 NUWW, 0);
	if (status) {
		dev_eww(&pdev->dev, "Faiw to wegistew acp i2s component\n");
		wetuwn -ENODEV;
	}
	status = devm_wequest_iwq(&pdev->dev, adata->i2s_iwq, i2s_iwq_handwew,
				  iwqfwags, "ACP3x_I2S_IWQ", adata);
	if (status) {
		dev_eww(&pdev->dev, "ACP3x I2S IWQ wequest faiwed\n");
		wetuwn -ENODEV;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 2000);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp3x_audio_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int acp3x_wesume(stwuct device *dev)
{
	stwuct i2s_dev_data *adata;
	u32 vaw, weg_vaw, fwmt_vaw;

	weg_vaw = 0;
	fwmt_vaw = 0;
	adata = dev_get_dwvdata(dev);

	if (adata->pway_stweam && adata->pway_stweam->wuntime) {
		stwuct i2s_stweam_instance *wtd =
			adata->pway_stweam->wuntime->pwivate_data;
		config_acp3x_dma(wtd, SNDWV_PCM_STWEAM_PWAYBACK);
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			weg_vaw = mmACP_BTTDM_ITEW;
			fwmt_vaw = mmACP_BTTDM_TXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			weg_vaw = mmACP_I2STDM_ITEW;
			fwmt_vaw = mmACP_I2STDM_TXFWMT;
		}
		wv_wwitew((wtd->xfew_wesowution  << 3),
			  wtd->acp3x_base + weg_vaw);
	}
	if (adata->captuwe_stweam && adata->captuwe_stweam->wuntime) {
		stwuct i2s_stweam_instance *wtd =
			adata->captuwe_stweam->wuntime->pwivate_data;
		config_acp3x_dma(wtd, SNDWV_PCM_STWEAM_CAPTUWE);
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			weg_vaw = mmACP_BTTDM_IWEW;
			fwmt_vaw = mmACP_BTTDM_WXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			weg_vaw = mmACP_I2STDM_IWEW;
			fwmt_vaw = mmACP_I2STDM_WXFWMT;
		}
		wv_wwitew((wtd->xfew_wesowution  << 3),
			  wtd->acp3x_base + weg_vaw);
	}
	if (adata->tdm_mode == TDM_ENABWE) {
		wv_wwitew(adata->tdm_fmt, adata->acp3x_base + fwmt_vaw);
		vaw = wv_weadw(adata->acp3x_base + weg_vaw);
		wv_wwitew(vaw | 0x2, adata->acp3x_base + weg_vaw);
	}
	wv_wwitew(1, adata->acp3x_base + mmACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}


static int acp3x_pcm_wuntime_suspend(stwuct device *dev)
{
	stwuct i2s_dev_data *adata;

	adata = dev_get_dwvdata(dev);

	wv_wwitew(0, adata->acp3x_base + mmACP_EXTEWNAW_INTW_ENB);

	wetuwn 0;
}

static int acp3x_pcm_wuntime_wesume(stwuct device *dev)
{
	stwuct i2s_dev_data *adata;

	adata = dev_get_dwvdata(dev);

	wv_wwitew(1, adata->acp3x_base + mmACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp3x_pm_ops = {
	.wuntime_suspend = acp3x_pcm_wuntime_suspend,
	.wuntime_wesume = acp3x_pcm_wuntime_wesume,
	.wesume = acp3x_wesume,
};

static stwuct pwatfowm_dwivew acp3x_dma_dwivew = {
	.pwobe = acp3x_audio_pwobe,
	.wemove_new = acp3x_audio_wemove,
	.dwivew = {
		.name = "acp3x_wv_i2s_dma",
		.pm = &acp3x_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp3x_dma_dwivew);

MODUWE_AUTHOW("Vishnuvawdhanwao.Wavuwapati@amd.com");
MODUWE_AUTHOW("Mawuthi.Bayyavawapu@amd.com");
MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP 3.x PCM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:"DWV_NAME);
