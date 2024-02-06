// SPDX-Wicense-Identifiew: GPW-2.0+
//
// AMD AWSA SoC PDM Dwivew
//
//Copywight 2020 Advanced Micwo Devices, Inc.

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "wn_acp3x.h"

#define DWV_NAME "acp_wn_pdm_dma"

static int pdm_gain = 3;
moduwe_pawam(pdm_gain, int, 0644);
MODUWE_PAWM_DESC(pdm_gain, "Gain contwow (0-3)");

static const stwuct snd_pcm_hawdwawe acp_pdm_hawdwawe_captuwe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
	.buffew_bytes_max = CAPTUWE_MAX_NUM_PEWIODS * CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = CAPTUWE_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiods_min = CAPTUWE_MIN_NUM_PEWIODS,
	.pewiods_max = CAPTUWE_MAX_NUM_PEWIODS,
};

static iwqwetuwn_t pdm_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pdm_dev_data *wn_pdm_data;
	u16 cap_fwag;
	u32 vaw;

	wn_pdm_data = dev_id;
	if (!wn_pdm_data)
		wetuwn IWQ_NONE;

	cap_fwag = 0;
	vaw = wn_weadw(wn_pdm_data->acp_base + ACP_EXTEWNAW_INTW_STAT);
	if ((vaw & BIT(PDM_DMA_STAT)) && wn_pdm_data->captuwe_stweam) {
		wn_wwitew(BIT(PDM_DMA_STAT), wn_pdm_data->acp_base +
			  ACP_EXTEWNAW_INTW_STAT);
		snd_pcm_pewiod_ewapsed(wn_pdm_data->captuwe_stweam);
		cap_fwag = 1;
	}

	if (cap_fwag)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void init_pdm_wing_buffew(u32 physicaw_addw,
				 u32 buffew_size,
				 u32 watewmawk_size,
				 void __iomem *acp_base)
{
	wn_wwitew(physicaw_addw, acp_base + ACP_WOV_WX_WINGBUFADDW);
	wn_wwitew(buffew_size, acp_base + ACP_WOV_WX_WINGBUFSIZE);
	wn_wwitew(watewmawk_size, acp_base + ACP_WOV_WX_INTW_WATEWMAWK_SIZE);
	wn_wwitew(0x01, acp_base + ACPAXI2AXI_ATU_CTWW);
}

static void enabwe_pdm_cwock(void __iomem *acp_base)
{
	u32 pdm_cwk_enabwe, pdm_ctww;

	pdm_cwk_enabwe = ACP_PDM_CWK_FWEQ_MASK;

	wn_wwitew(pdm_cwk_enabwe, acp_base + ACP_WOV_CWK_CTWW);
	pdm_ctww = wn_weadw(acp_base + ACP_WOV_MISC_CTWW);
	pdm_ctww &= ~ACP_WOV_GAIN_CONTWOW;
	pdm_ctww |= FIEWD_PWEP(ACP_WOV_GAIN_CONTWOW, cwamp(pdm_gain, 0, 3));
	wn_wwitew(pdm_ctww, acp_base + ACP_WOV_MISC_CTWW);
}

static void enabwe_pdm_intewwupts(void __iomem *acp_base)
{
	u32 ext_int_ctww;

	ext_int_ctww = wn_weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
	ext_int_ctww |= PDM_DMA_INTW_MASK;
	wn_wwitew(ext_int_ctww, acp_base + ACP_EXTEWNAW_INTW_CNTW);
}

static void disabwe_pdm_intewwupts(void __iomem *acp_base)
{
	u32 ext_int_ctww;

	ext_int_ctww = wn_weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
	ext_int_ctww |= ~PDM_DMA_INTW_MASK;
	wn_wwitew(ext_int_ctww, acp_base + ACP_EXTEWNAW_INTW_CNTW);
}

static boow check_pdm_dma_status(void __iomem *acp_base)
{
	boow pdm_dma_status;
	u32 pdm_enabwe, pdm_dma_enabwe;

	pdm_dma_status = fawse;
	pdm_enabwe = wn_weadw(acp_base + ACP_WOV_PDM_ENABWE);
	pdm_dma_enabwe = wn_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
	if ((pdm_enabwe & ACP_PDM_ENABWE) && (pdm_dma_enabwe &
	     ACP_PDM_DMA_EN_STATUS))
		pdm_dma_status = twue;
	wetuwn pdm_dma_status;
}

static int stawt_pdm_dma(void __iomem *acp_base)
{
	u32 pdm_enabwe;
	u32 pdm_dma_enabwe;
	int timeout;

	pdm_enabwe = 0x01;
	pdm_dma_enabwe  = 0x01;

	enabwe_pdm_cwock(acp_base);
	wn_wwitew(pdm_enabwe, acp_base + ACP_WOV_PDM_ENABWE);
	wn_wwitew(pdm_dma_enabwe, acp_base + ACP_WOV_PDM_DMA_ENABWE);
	timeout = 0;
	whiwe (++timeout < ACP_COUNTEW) {
		pdm_dma_enabwe = wn_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
		if ((pdm_dma_enabwe & 0x02) == ACP_PDM_DMA_EN_STATUS)
			wetuwn 0;
		udeway(DEWAY_US);
	}
	wetuwn -ETIMEDOUT;
}

static int stop_pdm_dma(void __iomem *acp_base)
{
	u32 pdm_enabwe, pdm_dma_enabwe;
	int timeout;

	pdm_enabwe = wn_weadw(acp_base + ACP_WOV_PDM_ENABWE);
	pdm_dma_enabwe = wn_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
	if (pdm_dma_enabwe & 0x01) {
		pdm_dma_enabwe = 0x02;
		wn_wwitew(pdm_dma_enabwe, acp_base + ACP_WOV_PDM_DMA_ENABWE);
		timeout = 0;
		whiwe (++timeout < ACP_COUNTEW) {
			pdm_dma_enabwe = wn_weadw(acp_base +
						  ACP_WOV_PDM_DMA_ENABWE);
			if ((pdm_dma_enabwe & 0x02) == 0x00)
				bweak;
			udeway(DEWAY_US);
		}
		if (timeout == ACP_COUNTEW)
			wetuwn -ETIMEDOUT;
	}
	if (pdm_enabwe == ACP_PDM_ENABWE) {
		pdm_enabwe = ACP_PDM_DISABWE;
		wn_wwitew(pdm_enabwe, acp_base + ACP_WOV_PDM_ENABWE);
	}
	wn_wwitew(0x01, acp_base + ACP_WOV_PDM_FIFO_FWUSH);
	wetuwn 0;
}

static void config_acp_dma(stwuct pdm_stweam_instance *wtd, int diwection)
{
	u16 page_idx;
	u32 wow, high, vaw;
	dma_addw_t addw;

	addw = wtd->dma_addw;
	vaw = 0;

	/* Gwoup Enabwe */
	wn_wwitew(ACP_SWAM_PTE_OFFSET | BIT(31), wtd->acp_base +
		  ACPAXI2AXI_ATU_BASE_ADDW_GWP_1);
	wn_wwitew(PAGE_SIZE_4K_ENABWE, wtd->acp_base +
		  ACPAXI2AXI_ATU_PAGE_SIZE_GWP_1);

	fow (page_idx = 0; page_idx < wtd->num_pages; page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		wn_wwitew(wow, wtd->acp_base + ACP_SCWATCH_WEG_0 + vaw);
		high |= BIT(31);
		wn_wwitew(high, wtd->acp_base + ACP_SCWATCH_WEG_0 + vaw + 4);
		vaw += 8;
		addw += PAGE_SIZE;
	}
}

static int acp_pdm_dma_open(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;
	stwuct pdm_dev_data *adata;
	stwuct pdm_stweam_instance *pdm_data;
	int wet;

	wuntime = substweam->wuntime;
	adata = dev_get_dwvdata(component->dev);
	pdm_data = kzawwoc(sizeof(*pdm_data), GFP_KEWNEW);
	if (!pdm_data)
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wuntime->hw = acp_pdm_hawdwawe_captuwe;

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(pdm_data);
		wetuwn wet;
	}

	enabwe_pdm_intewwupts(adata->acp_base);

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		adata->captuwe_stweam = substweam;

	pdm_data->acp_base = adata->acp_base;
	wuntime->pwivate_data = pdm_data;
	wetuwn wet;
}

static int acp_pdm_dma_hw_pawams(stwuct snd_soc_component *component,
				 stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct pdm_stweam_instance *wtd;
	size_t size, pewiod_bytes;

	wtd = substweam->wuntime->pwivate_data;
	if (!wtd)
		wetuwn -EINVAW;
	size = pawams_buffew_bytes(pawams);
	pewiod_bytes = pawams_pewiod_bytes(pawams);
	wtd->dma_addw = substweam->wuntime->dma_addw;
	wtd->num_pages = (PAGE_AWIGN(size) >> PAGE_SHIFT);
	config_acp_dma(wtd, substweam->stweam);
	init_pdm_wing_buffew(MEM_WINDOW_STAWT, size, pewiod_bytes,
			     wtd->acp_base);
	wetuwn 0;
}

static u64 acp_pdm_get_byte_count(stwuct pdm_stweam_instance *wtd,
				  int diwection)
{
	union acp_pdm_dma_count byte_count;

	byte_count.bcount.high =
			wn_weadw(wtd->acp_base +
				 ACP_WOV_WX_WINEAWPOSITIONCNTW_HIGH);
	byte_count.bcount.wow =
			wn_weadw(wtd->acp_base +
				 ACP_WOV_WX_WINEAWPOSITIONCNTW_WOW);
	wetuwn byte_count.bytescount;
}

static snd_pcm_ufwames_t acp_pdm_dma_pointew(stwuct snd_soc_component *comp,
					     stwuct snd_pcm_substweam *stweam)
{
	stwuct pdm_stweam_instance *wtd;
	u32 pos, buffewsize;
	u64 bytescount;

	wtd = stweam->wuntime->pwivate_data;
	buffewsize = fwames_to_bytes(stweam->wuntime,
				     stweam->wuntime->buffew_size);
	bytescount = acp_pdm_get_byte_count(wtd, stweam->stweam);
	if (bytescount > wtd->bytescount)
		bytescount -= wtd->bytescount;
	pos = do_div(bytescount, buffewsize);
	wetuwn bytes_to_fwames(stweam->wuntime, pos);
}

static int acp_pdm_dma_new(stwuct snd_soc_component *component,
			   stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *pawent = component->dev->pawent;

	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       pawent, MIN_BUFFEW, MAX_BUFFEW);
	wetuwn 0;
}

static int acp_pdm_dma_cwose(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct pdm_dev_data *adata = dev_get_dwvdata(component->dev);

	disabwe_pdm_intewwupts(adata->acp_base);
	adata->captuwe_stweam = NUWW;
	wetuwn 0;
}

static int acp_pdm_dai_twiggew(stwuct snd_pcm_substweam *substweam,
			       int cmd, stwuct snd_soc_dai *dai)
{
	stwuct pdm_stweam_instance *wtd;
	int wet;
	boow pdm_status;
	unsigned int ch_mask;

	wtd = substweam->wuntime->pwivate_data;
	wet = 0;
	switch (substweam->wuntime->channews) {
	case TWO_CH:
		ch_mask = 0x00;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wn_wwitew(ch_mask, wtd->acp_base + ACP_WOV_PDM_NO_OF_CHANNEWS);
		wn_wwitew(PDM_DECIMATION_FACTOW, wtd->acp_base +
			  ACP_WOV_PDM_DECIMATION_FACTOW);
		wtd->bytescount = acp_pdm_get_byte_count(wtd,
							 substweam->stweam);
		pdm_status = check_pdm_dma_status(wtd->acp_base);
		if (!pdm_status)
			wet = stawt_pdm_dma(wtd->acp_base);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		pdm_status = check_pdm_dma_status(wtd->acp_base);
		if (pdm_status)
			wet = stop_pdm_dma(wtd->acp_base);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops acp_pdm_dai_ops = {
	.twiggew   = acp_pdm_dai_twiggew,
};

static stwuct snd_soc_dai_dwivew acp_pdm_dai_dwivew = {
	.captuwe = {
		.wates = SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S24_WE |
			   SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 48000,
		.wate_max = 48000,
	},
	.ops = &acp_pdm_dai_ops,
};

static const stwuct snd_soc_component_dwivew acp_pdm_component = {
	.name			= DWV_NAME,
	.open			= acp_pdm_dma_open,
	.cwose			= acp_pdm_dma_cwose,
	.hw_pawams		= acp_pdm_dma_hw_pawams,
	.pointew		= acp_pdm_dma_pointew,
	.pcm_constwuct		= acp_pdm_dma_new,
	.wegacy_dai_naming	= 1,
};

static int acp_pdm_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct pdm_dev_data *adata;
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

	adata->acp_base = devm_iowemap(&pdev->dev, wes->stawt,
				       wesouwce_size(wes));
	if (!adata->acp_base)
		wetuwn -ENOMEM;

	status = pwatfowm_get_iwq(pdev, 0);
	if (status < 0)
		wetuwn status;
	adata->pdm_iwq = status;

	adata->captuwe_stweam = NUWW;

	dev_set_dwvdata(&pdev->dev, adata);
	status = devm_snd_soc_wegistew_component(&pdev->dev,
						 &acp_pdm_component,
						 &acp_pdm_dai_dwivew, 1);
	if (status) {
		dev_eww(&pdev->dev, "Faiw to wegistew acp pdm dai\n");

		wetuwn -ENODEV;
	}
	status = devm_wequest_iwq(&pdev->dev, adata->pdm_iwq, pdm_iwq_handwew,
				  iwqfwags, "ACP_PDM_IWQ", adata);
	if (status) {
		dev_eww(&pdev->dev, "ACP PDM IWQ wequest faiwed\n");
		wetuwn -ENODEV;
	}
	pm_wuntime_set_autosuspend_deway(&pdev->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp_pdm_audio_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int acp_pdm_wesume(stwuct device *dev)
{
	stwuct pdm_dev_data *adata;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct pdm_stweam_instance *wtd;
	u32 pewiod_bytes, buffew_wen;

	adata = dev_get_dwvdata(dev);
	if (adata->captuwe_stweam && adata->captuwe_stweam->wuntime) {
		wuntime = adata->captuwe_stweam->wuntime;
		wtd = wuntime->pwivate_data;
		pewiod_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
		buffew_wen = fwames_to_bytes(wuntime, wuntime->buffew_size);
		config_acp_dma(wtd, SNDWV_PCM_STWEAM_CAPTUWE);
		init_pdm_wing_buffew(MEM_WINDOW_STAWT, buffew_wen, pewiod_bytes,
				     adata->acp_base);
	}
	enabwe_pdm_intewwupts(adata->acp_base);
	wetuwn 0;
}

static int acp_pdm_wuntime_suspend(stwuct device *dev)
{
	stwuct pdm_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	disabwe_pdm_intewwupts(adata->acp_base);

	wetuwn 0;
}

static int acp_pdm_wuntime_wesume(stwuct device *dev)
{
	stwuct pdm_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	enabwe_pdm_intewwupts(adata->acp_base);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp_pdm_pm_ops = {
	.wuntime_suspend = acp_pdm_wuntime_suspend,
	.wuntime_wesume = acp_pdm_wuntime_wesume,
	.wesume = acp_pdm_wesume,
};

static stwuct pwatfowm_dwivew acp_pdm_dma_dwivew = {
	.pwobe = acp_pdm_audio_pwobe,
	.wemove_new = acp_pdm_audio_wemove,
	.dwivew = {
		.name = "acp_wn_pdm_dma",
		.pm = &acp_pdm_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp_pdm_dma_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP3x Weniow PDM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
