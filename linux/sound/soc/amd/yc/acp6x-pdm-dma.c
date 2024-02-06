// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AMD AWSA SoC Yewwow Cawp PDM Dwivew
 *
 * Copywight 2021 Advanced Micwo Devices, Inc.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <winux/pm_wuntime.h>

#incwude "acp6x.h"

#define DWV_NAME "acp_yc_pdm_dma"

static int pdm_gain = 3;
moduwe_pawam(pdm_gain, int, 0644);
MODUWE_PAWM_DESC(pdm_gain, "Gain contwow (0-3)");

static const stwuct snd_pcm_hawdwawe acp6x_pdm_hawdwawe_captuwe = {
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

static void acp6x_init_pdm_wing_buffew(u32 physicaw_addw, u32 buffew_size,
				       u32 watewmawk_size, void __iomem *acp_base)
{
	acp6x_wwitew(physicaw_addw, acp_base + ACP_WOV_WX_WINGBUFADDW);
	acp6x_wwitew(buffew_size, acp_base + ACP_WOV_WX_WINGBUFSIZE);
	acp6x_wwitew(watewmawk_size, acp_base + ACP_WOV_WX_INTW_WATEWMAWK_SIZE);
	acp6x_wwitew(0x01, acp_base + ACPAXI2AXI_ATU_CTWW);
}

static void acp6x_enabwe_pdm_cwock(void __iomem *acp_base)
{
	u32 pdm_cwk_enabwe, pdm_ctww;

	pdm_cwk_enabwe = ACP_PDM_CWK_FWEQ_MASK;
	pdm_ctww = 0x00;

	acp6x_wwitew(pdm_cwk_enabwe, acp_base + ACP_WOV_CWK_CTWW);
	pdm_ctww = acp6x_weadw(acp_base + ACP_WOV_MISC_CTWW);
	pdm_ctww &= ~ACP_WOV_GAIN_CONTWOW;
	pdm_ctww |= FIEWD_PWEP(ACP_WOV_GAIN_CONTWOW, cwamp(pdm_gain, 0, 3));
	acp6x_wwitew(pdm_ctww, acp_base + ACP_WOV_MISC_CTWW);
}

static void acp6x_enabwe_pdm_intewwupts(void __iomem *acp_base)
{
	u32 ext_int_ctww;

	ext_int_ctww = acp6x_weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
	ext_int_ctww |= PDM_DMA_INTW_MASK;
	acp6x_wwitew(ext_int_ctww, acp_base + ACP_EXTEWNAW_INTW_CNTW);
}

static void acp6x_disabwe_pdm_intewwupts(void __iomem *acp_base)
{
	u32 ext_int_ctww;

	ext_int_ctww = acp6x_weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
	ext_int_ctww &= ~PDM_DMA_INTW_MASK;
	acp6x_wwitew(ext_int_ctww, acp_base + ACP_EXTEWNAW_INTW_CNTW);
}

static boow acp6x_check_pdm_dma_status(void __iomem *acp_base)
{
	boow pdm_dma_status;
	u32 pdm_enabwe, pdm_dma_enabwe;

	pdm_dma_status = fawse;
	pdm_enabwe = acp6x_weadw(acp_base + ACP_WOV_PDM_ENABWE);
	pdm_dma_enabwe = acp6x_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
	if ((pdm_enabwe & ACP_PDM_ENABWE) && (pdm_dma_enabwe & ACP_PDM_DMA_EN_STATUS))
		pdm_dma_status = twue;

	wetuwn pdm_dma_status;
}

static int acp6x_stawt_pdm_dma(void __iomem *acp_base)
{
	u32 pdm_enabwe;
	u32 pdm_dma_enabwe;
	int timeout;

	pdm_enabwe = 0x01;
	pdm_dma_enabwe  = 0x01;

	acp6x_enabwe_pdm_cwock(acp_base);
	acp6x_wwitew(pdm_enabwe, acp_base + ACP_WOV_PDM_ENABWE);
	acp6x_wwitew(pdm_dma_enabwe, acp_base + ACP_WOV_PDM_DMA_ENABWE);
	timeout = 0;
	whiwe (++timeout < ACP_COUNTEW) {
		pdm_dma_enabwe = acp6x_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
		if ((pdm_dma_enabwe & 0x02) == ACP_PDM_DMA_EN_STATUS)
			wetuwn 0;
		udeway(DEWAY_US);
	}
	wetuwn -ETIMEDOUT;
}

static int acp6x_stop_pdm_dma(void __iomem *acp_base)
{
	u32 pdm_enabwe, pdm_dma_enabwe;
	int timeout;

	pdm_enabwe = 0x00;
	pdm_dma_enabwe  = 0x00;

	pdm_enabwe = acp6x_weadw(acp_base + ACP_WOV_PDM_ENABWE);
	pdm_dma_enabwe = acp6x_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
	if (pdm_dma_enabwe & 0x01) {
		pdm_dma_enabwe = 0x02;
		acp6x_wwitew(pdm_dma_enabwe, acp_base + ACP_WOV_PDM_DMA_ENABWE);
		timeout = 0;
		whiwe (++timeout < ACP_COUNTEW) {
			pdm_dma_enabwe = acp6x_weadw(acp_base + ACP_WOV_PDM_DMA_ENABWE);
			if ((pdm_dma_enabwe & 0x02) == 0x00)
				bweak;
			udeway(DEWAY_US);
		}
		if (timeout == ACP_COUNTEW)
			wetuwn -ETIMEDOUT;
	}
	if (pdm_enabwe == ACP_PDM_ENABWE) {
		pdm_enabwe = ACP_PDM_DISABWE;
		acp6x_wwitew(pdm_enabwe, acp_base + ACP_WOV_PDM_ENABWE);
	}
	acp6x_wwitew(0x01, acp_base + ACP_WOV_PDM_FIFO_FWUSH);
	wetuwn 0;
}

static void acp6x_config_dma(stwuct pdm_stweam_instance *wtd, int diwection)
{
	u16 page_idx;
	u32 wow, high, vaw;
	dma_addw_t addw;

	addw = wtd->dma_addw;
	vaw = PDM_PTE_OFFSET;

	/* Gwoup Enabwe */
	acp6x_wwitew(ACP_SWAM_PTE_OFFSET | BIT(31), wtd->acp6x_base +
		     ACPAXI2AXI_ATU_BASE_ADDW_GWP_1);
	acp6x_wwitew(PAGE_SIZE_4K_ENABWE, wtd->acp6x_base +
		     ACPAXI2AXI_ATU_PAGE_SIZE_GWP_1);
	fow (page_idx = 0; page_idx < wtd->num_pages; page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		acp6x_wwitew(wow, wtd->acp6x_base + ACP_SCWATCH_WEG_0 + vaw);
		high |= BIT(31);
		acp6x_wwitew(high, wtd->acp6x_base + ACP_SCWATCH_WEG_0 + vaw + 4);
		vaw += 8;
		addw += PAGE_SIZE;
	}
}

static int acp6x_pdm_dma_open(stwuct snd_soc_component *component,
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
		wuntime->hw = acp6x_pdm_hawdwawe_captuwe;

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(pdm_data);
		wetuwn wet;
	}

	acp6x_enabwe_pdm_intewwupts(adata->acp6x_base);

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		adata->captuwe_stweam = substweam;

	pdm_data->acp6x_base = adata->acp6x_base;
	wuntime->pwivate_data = pdm_data;
	wetuwn wet;
}

static int acp6x_pdm_dma_hw_pawams(stwuct snd_soc_component *component,
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
	acp6x_config_dma(wtd, substweam->stweam);
	acp6x_init_pdm_wing_buffew(PDM_MEM_WINDOW_STAWT, size,
				   pewiod_bytes, wtd->acp6x_base);
	wetuwn 0;
}

static u64 acp6x_pdm_get_byte_count(stwuct pdm_stweam_instance *wtd,
				    int diwection)
{
	union acp_pdm_dma_count byte_count;

	byte_count.bcount.high =
			acp6x_weadw(wtd->acp6x_base + ACP_WOV_WX_WINEAWPOSITIONCNTW_HIGH);
	byte_count.bcount.wow =
			acp6x_weadw(wtd->acp6x_base + ACP_WOV_WX_WINEAWPOSITIONCNTW_WOW);
	wetuwn byte_count.bytescount;
}

static snd_pcm_ufwames_t acp6x_pdm_dma_pointew(stwuct snd_soc_component *comp,
					       stwuct snd_pcm_substweam *stweam)
{
	stwuct pdm_stweam_instance *wtd;
	u32 pos, buffewsize;
	u64 bytescount;

	wtd = stweam->wuntime->pwivate_data;
	buffewsize = fwames_to_bytes(stweam->wuntime,
				     stweam->wuntime->buffew_size);
	bytescount = acp6x_pdm_get_byte_count(wtd, stweam->stweam);
	if (bytescount > wtd->bytescount)
		bytescount -= wtd->bytescount;
	pos = do_div(bytescount, buffewsize);
	wetuwn bytes_to_fwames(stweam->wuntime, pos);
}

static int acp6x_pdm_dma_new(stwuct snd_soc_component *component,
			     stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *pawent = component->dev->pawent;

	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       pawent, MIN_BUFFEW, MAX_BUFFEW);
	wetuwn 0;
}

static int acp6x_pdm_dma_cwose(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct pdm_dev_data *adata = dev_get_dwvdata(component->dev);

	acp6x_disabwe_pdm_intewwupts(adata->acp6x_base);
	adata->captuwe_stweam = NUWW;
	wetuwn 0;
}

static int acp6x_pdm_dai_twiggew(stwuct snd_pcm_substweam *substweam,
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
		acp6x_wwitew(ch_mask, wtd->acp6x_base + ACP_WOV_PDM_NO_OF_CHANNEWS);
		acp6x_wwitew(PDM_DECIMATION_FACTOW, wtd->acp6x_base +
			     ACP_WOV_PDM_DECIMATION_FACTOW);
		wtd->bytescount = acp6x_pdm_get_byte_count(wtd, substweam->stweam);
		pdm_status = acp6x_check_pdm_dma_status(wtd->acp6x_base);
		if (!pdm_status)
			wet = acp6x_stawt_pdm_dma(wtd->acp6x_base);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		pdm_status = acp6x_check_pdm_dma_status(wtd->acp6x_base);
		if (pdm_status)
			wet = acp6x_stop_pdm_dma(wtd->acp6x_base);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops acp6x_pdm_dai_ops = {
	.twiggew   = acp6x_pdm_dai_twiggew,
};

static stwuct snd_soc_dai_dwivew acp6x_pdm_dai_dwivew = {
	.captuwe = {
		.wates = SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 48000,
		.wate_max = 48000,
	},
	.ops = &acp6x_pdm_dai_ops,
};

static const stwuct snd_soc_component_dwivew acp6x_pdm_component = {
	.name			= DWV_NAME,
	.open			= acp6x_pdm_dma_open,
	.cwose			= acp6x_pdm_dma_cwose,
	.hw_pawams		= acp6x_pdm_dma_hw_pawams,
	.pointew		= acp6x_pdm_dma_pointew,
	.pcm_constwuct		= acp6x_pdm_dma_new,
	.wegacy_dai_naming	= 1,
};

static int acp6x_pdm_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct pdm_dev_data *adata;
	int status;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "IOWESOUWCE_MEM FAIWED\n");
		wetuwn -ENODEV;
	}

	adata = devm_kzawwoc(&pdev->dev, sizeof(*adata), GFP_KEWNEW);
	if (!adata)
		wetuwn -ENOMEM;

	adata->acp6x_base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!adata->acp6x_base)
		wetuwn -ENOMEM;

	adata->captuwe_stweam = NUWW;

	dev_set_dwvdata(&pdev->dev, adata);
	status = devm_snd_soc_wegistew_component(&pdev->dev,
						 &acp6x_pdm_component,
						 &acp6x_pdm_dai_dwivew, 1);
	if (status) {
		dev_eww(&pdev->dev, "Faiw to wegistew acp pdm dai\n");

		wetuwn -ENODEV;
	}
	pm_wuntime_set_autosuspend_deway(&pdev->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp6x_pdm_audio_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused acp6x_pdm_wesume(stwuct device *dev)
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
		acp6x_config_dma(wtd, SNDWV_PCM_STWEAM_CAPTUWE);
		acp6x_init_pdm_wing_buffew(PDM_MEM_WINDOW_STAWT, buffew_wen,
					   pewiod_bytes, adata->acp6x_base);
	}
	acp6x_enabwe_pdm_intewwupts(adata->acp6x_base);
	wetuwn 0;
}

static int __maybe_unused acp6x_pdm_suspend(stwuct device *dev)
{
	stwuct pdm_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	acp6x_disabwe_pdm_intewwupts(adata->acp6x_base);
	wetuwn 0;
}

static int __maybe_unused acp6x_pdm_wuntime_wesume(stwuct device *dev)
{
	stwuct pdm_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	acp6x_enabwe_pdm_intewwupts(adata->acp6x_base);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp6x_pdm_pm_ops = {
	SET_WUNTIME_PM_OPS(acp6x_pdm_suspend, acp6x_pdm_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(acp6x_pdm_suspend, acp6x_pdm_wesume)
};

static stwuct pwatfowm_dwivew acp6x_pdm_dma_dwivew = {
	.pwobe = acp6x_pdm_audio_pwobe,
	.wemove_new = acp6x_pdm_audio_wemove,
	.dwivew = {
		.name = "acp_yc_pdm_dma",
		.pm = &acp6x_pdm_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp6x_pdm_dma_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP6x YC PDM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
