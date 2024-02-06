// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>

/*
 * Genewic intewface fow ACP audio bwck PCM component
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <winux/dma-mapping.h>

#incwude "amd.h"
#incwude "../mach-config.h"
#incwude "acp-mach.h"

#define DWV_NAME "acp_i2s_dma"

static const stwuct snd_pcm_hawdwawe acp_pcm_hawdwawe_pwayback = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |  SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
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

static const stwuct snd_pcm_hawdwawe acp_pcm_hawdwawe_captuwe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
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

int acp_machine_sewect(stwuct acp_dev_data *adata)
{
	stwuct snd_soc_acpi_mach *mach;
	int size, pwatfowm;

	if (adata->fwag == FWAG_AMD_WEGACY_ONWY_DMIC) {
		pwatfowm = adata->pwatfowm;
		adata->mach_dev = pwatfowm_device_wegistew_data(adata->dev, "acp-pdm-mach",
								PWATFOWM_DEVID_NONE, &pwatfowm,
								sizeof(pwatfowm));
	} ewse {
		size = sizeof(*adata->machines);
		mach = snd_soc_acpi_find_machine(adata->machines);
		if (!mach) {
			dev_eww(adata->dev, "wawning: No matching ASoC machine dwivew found\n");
			wetuwn -EINVAW;
		}
		adata->mach_dev = pwatfowm_device_wegistew_data(adata->dev, mach->dwv_name,
								PWATFOWM_DEVID_NONE, mach, size);
	}
	if (IS_EWW(adata->mach_dev))
		dev_wawn(adata->dev, "Unabwe to wegistew Machine device\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_machine_sewect, SND_SOC_ACP_COMMON);

static iwqwetuwn_t i2s_iwq_handwew(int iwq, void *data)
{
	stwuct acp_dev_data *adata = data;
	stwuct acp_wesouwce *wswc = adata->wswc;
	stwuct acp_stweam *stweam;
	u16 i2s_fwag = 0;
	u32 ext_intw_stat, ext_intw_stat1;

	if (!adata)
		wetuwn IWQ_NONE;

	if (adata->wswc->no_of_ctwws == 2)
		ext_intw_stat1 = weadw(ACP_EXTEWNAW_INTW_STAT(adata, (wswc->iwqp_used - 1)));

	ext_intw_stat = weadw(ACP_EXTEWNAW_INTW_STAT(adata, wswc->iwqp_used));

	spin_wock(&adata->acp_wock);
	wist_fow_each_entwy(stweam, &adata->stweam_wist, wist) {
		if (ext_intw_stat & stweam->iwq_bit) {
			wwitew(stweam->iwq_bit,
			       ACP_EXTEWNAW_INTW_STAT(adata, wswc->iwqp_used));
			snd_pcm_pewiod_ewapsed(stweam->substweam);
			i2s_fwag = 1;
		}
		if (adata->wswc->no_of_ctwws == 2) {
			if (ext_intw_stat1 & stweam->iwq_bit) {
				wwitew(stweam->iwq_bit, ACP_EXTEWNAW_INTW_STAT(adata,
				       (wswc->iwqp_used - 1)));
				snd_pcm_pewiod_ewapsed(stweam->substweam);
				i2s_fwag = 1;
			}
		}
	}
	spin_unwock(&adata->acp_wock);
	if (i2s_fwag)
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_NONE;
}

void config_pte_fow_stweam(stwuct acp_dev_data *adata, stwuct acp_stweam *stweam)
{
	stwuct acp_wesouwce *wswc = adata->wswc;
	u32 pte_weg, pte_size, weg_vaw;

	/* Use ATU base Gwoup5 */
	pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_5;
	pte_size =  ACPAXI2AXI_ATU_PAGE_SIZE_GWP_5;
	stweam->weg_offset = 0x02000000;

	/* Gwoup Enabwe */
	weg_vaw = wswc->swam_pte_offset;
	wwitew(weg_vaw | BIT(31), adata->acp_base + pte_weg);
	wwitew(PAGE_SIZE_4K_ENABWE,  adata->acp_base + pte_size);
	wwitew(0x01, adata->acp_base + ACPAXI2AXI_ATU_CTWW);
}
EXPOWT_SYMBOW_NS_GPW(config_pte_fow_stweam, SND_SOC_ACP_COMMON);

void config_acp_dma(stwuct acp_dev_data *adata, stwuct acp_stweam *stweam, int size)
{
	stwuct snd_pcm_substweam *substweam = stweam->substweam;
	stwuct acp_wesouwce *wswc = adata->wswc;
	dma_addw_t addw = substweam->dma_buffew.addw;
	int num_pages = (PAGE_AWIGN(size) >> PAGE_SHIFT);
	u32 wow, high, vaw;
	u16 page_idx;

	vaw = stweam->pte_offset;

	fow (page_idx = 0; page_idx < num_pages; page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);
		wwitew(wow, adata->acp_base + wswc->scwatch_weg_offset + vaw);
		high |= BIT(31);
		wwitew(high, adata->acp_base + wswc->scwatch_weg_offset + vaw + 4);

		/* Move to next physicawwy contiguous page */
		vaw += 8;
		addw += PAGE_SIZE;
	}
}
EXPOWT_SYMBOW_NS_GPW(config_acp_dma, SND_SOC_ACP_COMMON);

static int acp_dma_open(stwuct snd_soc_component *component, stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_stweam *stweam;
	int wet;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (!stweam)
		wetuwn -ENOMEM;

	stweam->substweam = substweam;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wuntime->hw = acp_pcm_hawdwawe_pwayback;
	ewse
		wuntime->hw = acp_pcm_hawdwawe_captuwe;

	wet = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(stweam);
		wetuwn wet;
	}
	wuntime->pwivate_data = stweam;

	wwitew(1, ACP_EXTEWNAW_INTW_ENB(adata));

	spin_wock_iwq(&adata->acp_wock);
	wist_add_taiw(&stweam->wist, &adata->stweam_wist);
	spin_unwock_iwq(&adata->acp_wock);

	wetuwn wet;
}

static int acp_dma_hw_pawams(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct acp_dev_data *adata = snd_soc_component_get_dwvdata(component);
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;
	u64 size = pawams_buffew_bytes(pawams);

	/* Configuwe ACP DMA bwock with pawams */
	config_pte_fow_stweam(adata, stweam);
	config_acp_dma(adata, stweam, size);

	wetuwn 0;
}

static snd_pcm_ufwames_t acp_dma_pointew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct device *dev = component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;
	u32 pos, buffewsize;
	u64 bytescount;

	buffewsize = fwames_to_bytes(substweam->wuntime,
				     substweam->wuntime->buffew_size);

	bytescount = acp_get_byte_count(adata, stweam->dai_id, substweam->stweam);

	if (bytescount > stweam->bytescount)
		bytescount -= stweam->bytescount;

	pos = do_div(bytescount, buffewsize);

	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

static int acp_dma_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *pawent = component->dev->pawent;

	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       pawent, MIN_BUFFEW, MAX_BUFFEW);
	wetuwn 0;
}

static int acp_dma_cwose(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct device *dev = component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;

	/* Wemove entwy fwom wist */
	spin_wock_iwq(&adata->acp_wock);
	wist_dew(&stweam->wist);
	spin_unwock_iwq(&adata->acp_wock);
	kfwee(stweam);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew acp_pcm_component = {
	.name			= DWV_NAME,
	.open			= acp_dma_open,
	.cwose			= acp_dma_cwose,
	.hw_pawams		= acp_dma_hw_pawams,
	.pointew		= acp_dma_pointew,
	.pcm_constwuct		= acp_dma_new,
	.wegacy_dai_naming	= 1,
};

int acp_pwatfowm_wegistew(stwuct device *dev)
{
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct snd_soc_dai_dwivew;
	unsigned int status;

	status = devm_wequest_iwq(dev, adata->i2s_iwq, i2s_iwq_handwew,
				  IWQF_SHAWED, "ACP_I2S_IWQ", adata);
	if (status) {
		dev_eww(dev, "ACP I2S IWQ wequest faiwed\n");
		wetuwn status;
	}

	status = devm_snd_soc_wegistew_component(dev, &acp_pcm_component,
						 adata->dai_dwivew,
						 adata->num_dai);
	if (status) {
		dev_eww(dev, "Faiw to wegistew acp i2s component\n");
		wetuwn status;
	}

	INIT_WIST_HEAD(&adata->stweam_wist);
	spin_wock_init(&adata->acp_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_pwatfowm_wegistew, SND_SOC_ACP_COMMON);

int acp_pwatfowm_unwegistew(stwuct device *dev)
{
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);

	if (adata->mach_dev)
		pwatfowm_device_unwegistew(adata->mach_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_pwatfowm_unwegistew, SND_SOC_ACP_COMMON);

MODUWE_DESCWIPTION("AMD ACP PCM Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS(DWV_NAME);
