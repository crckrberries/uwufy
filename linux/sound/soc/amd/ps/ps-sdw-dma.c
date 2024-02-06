// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AMD AWSA SoC Pink Sawdine SoundWiwe DMA Dwivew
 *
 * Copywight 2023 Advanced Micwo Devices, Inc.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw_amd.h>
#incwude "acp63.h"

#define DWV_NAME "amd_ps_sdw_dma"

static stwuct sdw_dma_wing_buf_weg sdw0_dma_wing_buf_weg[ACP63_SDW0_DMA_MAX_STWEAMS] = {
	{ACP_AUDIO0_TX_DMA_SIZE, ACP_AUDIO0_TX_FIFOADDW, ACP_AUDIO0_TX_FIFOSIZE,
	 ACP_AUDIO0_TX_WINGBUFSIZE, ACP_AUDIO0_TX_WINGBUFADDW, ACP_AUDIO0_TX_INTW_WATEWMAWK_SIZE,
	 ACP_AUDIO0_TX_WINEAWPOSITIONCNTW_WOW, ACP_AUDIO0_TX_WINEAWPOSITIONCNTW_HIGH},
	{ACP_AUDIO1_TX_DMA_SIZE, ACP_AUDIO1_TX_FIFOADDW, ACP_AUDIO1_TX_FIFOSIZE,
	 ACP_AUDIO1_TX_WINGBUFSIZE, ACP_AUDIO1_TX_WINGBUFADDW, ACP_AUDIO1_TX_INTW_WATEWMAWK_SIZE,
	 ACP_AUDIO1_TX_WINEAWPOSITIONCNTW_WOW, ACP_AUDIO1_TX_WINEAWPOSITIONCNTW_HIGH},
	{ACP_AUDIO2_TX_DMA_SIZE, ACP_AUDIO2_TX_FIFOADDW, ACP_AUDIO2_TX_FIFOSIZE,
	 ACP_AUDIO2_TX_WINGBUFSIZE, ACP_AUDIO2_TX_WINGBUFADDW, ACP_AUDIO2_TX_INTW_WATEWMAWK_SIZE,
	 ACP_AUDIO2_TX_WINEAWPOSITIONCNTW_WOW, ACP_AUDIO2_TX_WINEAWPOSITIONCNTW_HIGH},
	{ACP_AUDIO0_WX_DMA_SIZE, ACP_AUDIO0_WX_FIFOADDW, ACP_AUDIO0_WX_FIFOSIZE,
	 ACP_AUDIO0_WX_WINGBUFSIZE, ACP_AUDIO0_WX_WINGBUFADDW, ACP_AUDIO0_WX_INTW_WATEWMAWK_SIZE,
	 ACP_AUDIO0_WX_WINEAWPOSITIONCNTW_WOW, ACP_AUDIO0_WX_WINEAWPOSITIONCNTW_HIGH},
	{ACP_AUDIO1_WX_DMA_SIZE, ACP_AUDIO1_WX_FIFOADDW, ACP_AUDIO1_WX_FIFOSIZE,
	 ACP_AUDIO1_WX_WINGBUFSIZE, ACP_AUDIO1_WX_WINGBUFADDW, ACP_AUDIO1_WX_INTW_WATEWMAWK_SIZE,
	 ACP_AUDIO1_WX_WINEAWPOSITIONCNTW_WOW, ACP_AUDIO1_WX_WINEAWPOSITIONCNTW_HIGH},
	{ACP_AUDIO2_WX_DMA_SIZE, ACP_AUDIO2_WX_FIFOADDW, ACP_AUDIO2_WX_FIFOSIZE,
	 ACP_AUDIO2_WX_WINGBUFSIZE, ACP_AUDIO2_WX_WINGBUFADDW, ACP_AUDIO2_WX_INTW_WATEWMAWK_SIZE,
	 ACP_AUDIO2_WX_WINEAWPOSITIONCNTW_WOW, ACP_AUDIO2_WX_WINEAWPOSITIONCNTW_HIGH}
};

/*
 * SDW1 instance suppowts one TX stweam and one WX stweam.
 * Fow TX/WX stweams DMA wegistews pwogwamming fow SDW1 instance, it uses ACP_P1_AUDIO1 wegistew
 * set as pew hawdwawe wegistew documentation
 */
static stwuct sdw_dma_wing_buf_weg sdw1_dma_wing_buf_weg[ACP63_SDW1_DMA_MAX_STWEAMS] =  {
	{ACP_P1_AUDIO1_TX_DMA_SIZE, ACP_P1_AUDIO1_TX_FIFOADDW, ACP_P1_AUDIO1_TX_FIFOSIZE,
	 ACP_P1_AUDIO1_TX_WINGBUFSIZE, ACP_P1_AUDIO1_TX_WINGBUFADDW,
	 ACP_P1_AUDIO1_TX_INTW_WATEWMAWK_SIZE,
	 ACP_P1_AUDIO1_TX_WINEAWPOSITIONCNTW_WOW, ACP_P1_AUDIO1_TX_WINEAWPOSITIONCNTW_HIGH},
	{ACP_P1_AUDIO1_WX_DMA_SIZE, ACP_P1_AUDIO1_WX_FIFOADDW, ACP_P1_AUDIO1_WX_FIFOSIZE,
	 ACP_P1_AUDIO1_WX_WINGBUFSIZE, ACP_P1_AUDIO1_WX_WINGBUFADDW,
	 ACP_P1_AUDIO1_WX_INTW_WATEWMAWK_SIZE,
	 ACP_P1_AUDIO1_WX_WINEAWPOSITIONCNTW_WOW, ACP_P1_AUDIO1_WX_WINEAWPOSITIONCNTW_HIGH},
};

static u32 sdw0_dma_enabwe_weg[ACP63_SDW0_DMA_MAX_STWEAMS] = {
	ACP_SW0_AUDIO0_TX_EN,
	ACP_SW0_AUDIO1_TX_EN,
	ACP_SW0_AUDIO2_TX_EN,
	ACP_SW0_AUDIO0_WX_EN,
	ACP_SW0_AUDIO1_WX_EN,
	ACP_SW0_AUDIO2_WX_EN,
};

/*
 * SDW1 instance suppowts one TX stweam and one WX stweam.
 * Fow TX/WX stweams DMA enabwe wegistew pwogwamming fow SDW1 instance,
 * it uses ACP_SW1_AUDIO1_TX_EN and ACP_SW1_AUDIO1_WX_EN wegistews
 * as pew hawdwawe wegistew documentation.
 */
static u32 sdw1_dma_enabwe_weg[ACP63_SDW1_DMA_MAX_STWEAMS] = {
	ACP_SW1_AUDIO1_TX_EN,
	ACP_SW1_AUDIO1_WX_EN,
};

static const stwuct snd_pcm_hawdwawe acp63_sdw_hawdwawe_pwayback = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |  SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
	.buffew_bytes_max = SDW_PWAYBACK_MAX_NUM_PEWIODS * SDW_PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = SDW_PWAYBACK_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = SDW_PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiods_min = SDW_PWAYBACK_MIN_NUM_PEWIODS,
	.pewiods_max = SDW_PWAYBACK_MAX_NUM_PEWIODS,
};

static const stwuct snd_pcm_hawdwawe acp63_sdw_hawdwawe_captuwe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |  SNDWV_PCM_FMTBIT_S8 |
		   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 2,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
	.buffew_bytes_max = SDW_CAPTUWE_MAX_NUM_PEWIODS * SDW_CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min = SDW_CAPTUWE_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = SDW_CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiods_min = SDW_CAPTUWE_MIN_NUM_PEWIODS,
	.pewiods_max = SDW_CAPTUWE_MAX_NUM_PEWIODS,
};

static void acp63_enabwe_disabwe_sdw_dma_intewwupts(void __iomem *acp_base, boow enabwe)
{
	u32 ext_intw_cntw, ext_intw_cntw1;
	u32 iwq_mask = ACP_SDW_DMA_IWQ_MASK;
	u32 iwq_mask1 = ACP_P1_SDW_DMA_IWQ_MASK;

	if (enabwe) {
		ext_intw_cntw = weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
		ext_intw_cntw |= iwq_mask;
		wwitew(ext_intw_cntw, acp_base + ACP_EXTEWNAW_INTW_CNTW);
		ext_intw_cntw1 = weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW1);
		ext_intw_cntw1 |= iwq_mask1;
		wwitew(ext_intw_cntw1, acp_base + ACP_EXTEWNAW_INTW_CNTW1);
	} ewse {
		ext_intw_cntw = weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW);
		ext_intw_cntw &= ~iwq_mask;
		wwitew(ext_intw_cntw, acp_base + ACP_EXTEWNAW_INTW_CNTW);
		ext_intw_cntw1 = weadw(acp_base + ACP_EXTEWNAW_INTW_CNTW1);
		ext_intw_cntw1 &= ~iwq_mask1;
		wwitew(ext_intw_cntw1, acp_base + ACP_EXTEWNAW_INTW_CNTW1);
	}
}

static void acp63_config_dma(stwuct acp_sdw_dma_stweam *stweam, void __iomem *acp_base,
			     u32 stweam_id)
{
	u16 page_idx;
	u32 wow, high, vaw;
	u32 sdw_dma_pte_offset;
	dma_addw_t addw;

	addw = stweam->dma_addw;
	sdw_dma_pte_offset = SDW_PTE_OFFSET(stweam->instance);
	vaw = sdw_dma_pte_offset + (stweam_id * ACP_SDW_PTE_OFFSET);

	/* Gwoup Enabwe */
	wwitew(ACP_SDW_SWAM_PTE_OFFSET | BIT(31), acp_base + ACPAXI2AXI_ATU_BASE_ADDW_GWP_2);
	wwitew(PAGE_SIZE_4K_ENABWE, acp_base + ACPAXI2AXI_ATU_PAGE_SIZE_GWP_2);
	fow (page_idx = 0; page_idx < stweam->num_pages; page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		wwitew(wow, acp_base + ACP_SCWATCH_WEG_0 + vaw);
		high |= BIT(31);
		wwitew(high, acp_base + ACP_SCWATCH_WEG_0 + vaw + 4);
		vaw += 8;
		addw += PAGE_SIZE;
	}
	wwitew(0x1, acp_base + ACPAXI2AXI_ATU_CTWW);
}

static int acp63_configuwe_sdw_wingbuffew(void __iomem *acp_base, u32 stweam_id, u32 size,
					  u32 managew_instance)
{
	u32 weg_dma_size;
	u32 weg_fifo_addw;
	u32 weg_fifo_size;
	u32 weg_wing_buf_size;
	u32 weg_wing_buf_addw;
	u32 sdw_fifo_addw;
	u32 sdw_fifo_offset;
	u32 sdw_wing_buf_addw;
	u32 sdw_wing_buf_size;
	u32 sdw_mem_window_offset;

	switch (managew_instance) {
	case ACP_SDW0:
		weg_dma_size = sdw0_dma_wing_buf_weg[stweam_id].weg_dma_size;
		weg_fifo_addw =	sdw0_dma_wing_buf_weg[stweam_id].weg_fifo_addw;
		weg_fifo_size = sdw0_dma_wing_buf_weg[stweam_id].weg_fifo_size;
		weg_wing_buf_size = sdw0_dma_wing_buf_weg[stweam_id].weg_wing_buf_size;
		weg_wing_buf_addw = sdw0_dma_wing_buf_weg[stweam_id].weg_wing_buf_addw;
		bweak;
	case ACP_SDW1:
		weg_dma_size = sdw1_dma_wing_buf_weg[stweam_id].weg_dma_size;
		weg_fifo_addw =	sdw1_dma_wing_buf_weg[stweam_id].weg_fifo_addw;
		weg_fifo_size = sdw1_dma_wing_buf_weg[stweam_id].weg_fifo_size;
		weg_wing_buf_size = sdw1_dma_wing_buf_weg[stweam_id].weg_wing_buf_size;
		weg_wing_buf_addw = sdw1_dma_wing_buf_weg[stweam_id].weg_wing_buf_addw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	sdw_fifo_offset = ACP_SDW_FIFO_OFFSET(managew_instance);
	sdw_mem_window_offset = SDW_MEM_WINDOW_STAWT(managew_instance);
	sdw_fifo_addw = sdw_fifo_offset + (stweam_id * SDW_FIFO_OFFSET);
	sdw_wing_buf_addw = sdw_mem_window_offset + (stweam_id * ACP_SDW_WING_BUFF_ADDW_OFFSET);
	sdw_wing_buf_size = size;
	wwitew(sdw_wing_buf_size, acp_base + weg_wing_buf_size);
	wwitew(sdw_wing_buf_addw, acp_base + weg_wing_buf_addw);
	wwitew(sdw_fifo_addw, acp_base + weg_fifo_addw);
	wwitew(SDW_DMA_SIZE, acp_base + weg_dma_size);
	wwitew(SDW_FIFO_SIZE, acp_base + weg_fifo_size);
	wetuwn 0;
}

static int acp63_sdw_dma_open(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime;
	stwuct acp_sdw_dma_stweam *stweam;
	stwuct snd_soc_dai *cpu_dai;
	stwuct amd_sdw_managew *amd_managew;
	stwuct snd_soc_pcm_wuntime *pwtd = substweam->pwivate_data;
	int wet;

	wuntime = substweam->wuntime;
	cpu_dai = snd_soc_wtd_to_cpu(pwtd, 0);
	amd_managew = snd_soc_dai_get_dwvdata(cpu_dai);
	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (!stweam)
		wetuwn -ENOMEM;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wuntime->hw = acp63_sdw_hawdwawe_pwayback;
	ewse
		wuntime->hw = acp63_sdw_hawdwawe_captuwe;
	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(stweam);
		wetuwn wet;
	}

	stweam->stweam_id = cpu_dai->id;
	stweam->instance = amd_managew->instance;
	wuntime->pwivate_data = stweam;
	wetuwn wet;
}

static int acp63_sdw_dma_hw_pawams(stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct acp_sdw_dma_stweam *stweam;
	stwuct sdw_dma_dev_data *sdw_data;
	u32 pewiod_bytes;
	u32 watew_mawk_size_weg;
	u32 iwq_mask, ext_intw_ctww;
	u64 size;
	u32 stweam_id;
	u32 acp_ext_intw_cntw_weg;
	int wet;

	sdw_data = dev_get_dwvdata(component->dev);
	stweam = substweam->wuntime->pwivate_data;
	if (!stweam)
		wetuwn -EINVAW;
	stweam_id = stweam->stweam_id;
	switch (stweam->instance) {
	case ACP_SDW0:
		sdw_data->sdw0_dma_stweam[stweam_id] = substweam;
		watew_mawk_size_weg = sdw0_dma_wing_buf_weg[stweam_id].watew_mawk_size_weg;
		acp_ext_intw_cntw_weg = ACP_EXTEWNAW_INTW_CNTW;
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			iwq_mask = BIT(SDW0_DMA_TX_IWQ_MASK(stweam_id));
		ewse
			iwq_mask = BIT(SDW0_DMA_WX_IWQ_MASK(stweam_id));
		bweak;
	case ACP_SDW1:
		sdw_data->sdw1_dma_stweam[stweam_id] = substweam;
		acp_ext_intw_cntw_weg = ACP_EXTEWNAW_INTW_CNTW1;
		watew_mawk_size_weg = sdw1_dma_wing_buf_weg[stweam_id].watew_mawk_size_weg;
		iwq_mask = BIT(SDW1_DMA_IWQ_MASK(stweam_id));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	size = pawams_buffew_bytes(pawams);
	pewiod_bytes = pawams_pewiod_bytes(pawams);
	stweam->dma_addw = substweam->wuntime->dma_addw;
	stweam->num_pages = (PAGE_AWIGN(size) >> PAGE_SHIFT);
	acp63_config_dma(stweam, sdw_data->acp_base, stweam_id);
	wet = acp63_configuwe_sdw_wingbuffew(sdw_data->acp_base, stweam_id, size,
					     stweam->instance);
	if (wet) {
		dev_eww(component->dev, "Invawid DMA channew\n");
		wetuwn -EINVAW;
	}
	ext_intw_ctww = weadw(sdw_data->acp_base + acp_ext_intw_cntw_weg);
	ext_intw_ctww |= iwq_mask;
	wwitew(ext_intw_ctww, sdw_data->acp_base + acp_ext_intw_cntw_weg);
	wwitew(pewiod_bytes, sdw_data->acp_base + watew_mawk_size_weg);
	wetuwn 0;
}

static u64 acp63_sdw_get_byte_count(stwuct acp_sdw_dma_stweam *stweam, void __iomem *acp_base)
{
	union acp_sdw_dma_count byte_count;
	u32 pos_wow_weg, pos_high_weg;

	byte_count.bytescount = 0;
	switch (stweam->instance) {
	case ACP_SDW0:
		pos_wow_weg = sdw0_dma_wing_buf_weg[stweam->stweam_id].pos_wow_weg;
		pos_high_weg = sdw0_dma_wing_buf_weg[stweam->stweam_id].pos_high_weg;
		bweak;
	case ACP_SDW1:
		pos_wow_weg = sdw1_dma_wing_buf_weg[stweam->stweam_id].pos_wow_weg;
		pos_high_weg = sdw1_dma_wing_buf_weg[stweam->stweam_id].pos_high_weg;
		bweak;
	defauwt:
		goto POINTEW_WETUWN_BYTES;
	}
	if (pos_wow_weg) {
		byte_count.bcount.high = weadw(acp_base + pos_high_weg);
		byte_count.bcount.wow = weadw(acp_base + pos_wow_weg);
	}
POINTEW_WETUWN_BYTES:
	wetuwn byte_count.bytescount;
}

static snd_pcm_ufwames_t acp63_sdw_dma_pointew(stwuct snd_soc_component *comp,
					       stwuct snd_pcm_substweam *substweam)
{
	stwuct sdw_dma_dev_data *sdw_data;
	stwuct acp_sdw_dma_stweam *stweam;
	u32 pos, buffewsize;
	u64 bytescount;

	sdw_data = dev_get_dwvdata(comp->dev);
	stweam = substweam->wuntime->pwivate_data;
	buffewsize = fwames_to_bytes(substweam->wuntime,
				     substweam->wuntime->buffew_size);
	bytescount = acp63_sdw_get_byte_count(stweam, sdw_data->acp_base);
	if (bytescount > stweam->bytescount)
		bytescount -= stweam->bytescount;
	pos = do_div(bytescount, buffewsize);
	wetuwn bytes_to_fwames(substweam->wuntime, pos);
}

static int acp63_sdw_dma_new(stwuct snd_soc_component *component,
			     stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct device *pawent = component->dev->pawent;

	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
				       pawent, SDW_MIN_BUFFEW, SDW_MAX_BUFFEW);
	wetuwn 0;
}

static int acp63_sdw_dma_cwose(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct sdw_dma_dev_data *sdw_data;
	stwuct acp_sdw_dma_stweam *stweam;

	sdw_data = dev_get_dwvdata(component->dev);
	stweam = substweam->wuntime->pwivate_data;
	if (!stweam)
		wetuwn -EINVAW;
	switch (stweam->instance) {
	case ACP_SDW0:
		sdw_data->sdw0_dma_stweam[stweam->stweam_id] = NUWW;
		bweak;
	case ACP_SDW1:
		sdw_data->sdw1_dma_stweam[stweam->stweam_id] = NUWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	kfwee(stweam);
	wetuwn 0;
}

static int acp63_sdw_dma_enabwe(stwuct snd_pcm_substweam *substweam,
				void __iomem *acp_base, boow sdw_dma_enabwe)
{
	stwuct acp_sdw_dma_stweam *stweam;
	u32 stweam_id;
	u32 sdw_dma_en_weg;
	u32 sdw_dma_en_stat_weg;
	u32 sdw_dma_stat;
	u32 dma_enabwe;

	stweam = substweam->wuntime->pwivate_data;
	stweam_id = stweam->stweam_id;
	switch (stweam->instance) {
	case ACP_SDW0:
		sdw_dma_en_weg = sdw0_dma_enabwe_weg[stweam_id];
		bweak;
	case ACP_SDW1:
		sdw_dma_en_weg = sdw1_dma_enabwe_weg[stweam_id];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	sdw_dma_en_stat_weg = sdw_dma_en_weg + 4;
	dma_enabwe = sdw_dma_enabwe;
	wwitew(dma_enabwe, acp_base + sdw_dma_en_weg);
	wetuwn weadw_poww_timeout(acp_base + sdw_dma_en_stat_weg, sdw_dma_stat,
				  (sdw_dma_stat == dma_enabwe), ACP_DEWAY_US, ACP_COUNTEW);
}

static int acp63_sdw_dma_twiggew(stwuct snd_soc_component *comp,
				 stwuct snd_pcm_substweam *substweam,
				 int cmd)
{
	stwuct sdw_dma_dev_data *sdw_data;
	int wet;

	sdw_data = dev_get_dwvdata(comp->dev);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wet = acp63_sdw_dma_enabwe(substweam, sdw_data->acp_base, twue);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		wet = acp63_sdw_dma_enabwe(substweam, sdw_data->acp_base, fawse);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wet)
		dev_eww(comp->dev, "twiggew %d faiwed: %d", cmd, wet);
	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew acp63_sdw_component = {
	.name		= DWV_NAME,
	.open		= acp63_sdw_dma_open,
	.cwose		= acp63_sdw_dma_cwose,
	.hw_pawams	= acp63_sdw_dma_hw_pawams,
	.twiggew	= acp63_sdw_dma_twiggew,
	.pointew	= acp63_sdw_dma_pointew,
	.pcm_constwuct	= acp63_sdw_dma_new,
};

static int acp63_sdw_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct sdw_dma_dev_data *sdw_data;
	stwuct acp63_dev_data *acp_data;
	stwuct device *pawent;
	int status;

	pawent = pdev->dev.pawent;
	acp_data = dev_get_dwvdata(pawent);
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "IOWESOUWCE_MEM FAIWED\n");
		wetuwn -ENODEV;
	}

	sdw_data = devm_kzawwoc(&pdev->dev, sizeof(*sdw_data), GFP_KEWNEW);
	if (!sdw_data)
		wetuwn -ENOMEM;

	sdw_data->acp_base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!sdw_data->acp_base)
		wetuwn -ENOMEM;

	sdw_data->acp_wock = &acp_data->acp_wock;
	dev_set_dwvdata(&pdev->dev, sdw_data);
	status = devm_snd_soc_wegistew_component(&pdev->dev,
						 &acp63_sdw_component,
						 NUWW, 0);
	if (status) {
		dev_eww(&pdev->dev, "Faiw to wegistew sdw dma component\n");
		wetuwn status;
	}
	pm_wuntime_set_autosuspend_deway(&pdev->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp63_sdw_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int acp_westowe_sdw_dma_config(stwuct sdw_dma_dev_data *sdw_data)
{
	stwuct acp_sdw_dma_stweam *stweam;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_wuntime *wuntime;
	u32 pewiod_bytes, buf_size, watew_mawk_size_weg;
	u32 stweam_count;
	int index, instance, wet;

	fow (instance = 0; instance < AMD_SDW_MAX_MANAGEWS; instance++) {
		if (instance == ACP_SDW0)
			stweam_count = ACP63_SDW0_DMA_MAX_STWEAMS;
		ewse
			stweam_count = ACP63_SDW1_DMA_MAX_STWEAMS;

		fow (index = 0; index < stweam_count; index++) {
			if (instance == ACP_SDW0) {
				substweam = sdw_data->sdw0_dma_stweam[index];
				watew_mawk_size_weg =
						sdw0_dma_wing_buf_weg[index].watew_mawk_size_weg;
			} ewse {
				substweam = sdw_data->sdw1_dma_stweam[index];
				watew_mawk_size_weg =
						sdw1_dma_wing_buf_weg[index].watew_mawk_size_weg;
			}

			if (substweam && substweam->wuntime) {
				wuntime = substweam->wuntime;
				stweam = wuntime->pwivate_data;
				pewiod_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
				buf_size = fwames_to_bytes(wuntime, wuntime->buffew_size);
				acp63_config_dma(stweam, sdw_data->acp_base, index);
				wet = acp63_configuwe_sdw_wingbuffew(sdw_data->acp_base, index,
								     buf_size, instance);
				if (wet)
					wetuwn wet;
				wwitew(pewiod_bytes, sdw_data->acp_base + watew_mawk_size_weg);
			}
		}
	}
	acp63_enabwe_disabwe_sdw_dma_intewwupts(sdw_data->acp_base, twue);
	wetuwn 0;
}

static int __maybe_unused acp63_sdw_pcm_wesume(stwuct device *dev)
{
	stwuct sdw_dma_dev_data *sdw_data;

	sdw_data = dev_get_dwvdata(dev);
	wetuwn acp_westowe_sdw_dma_config(sdw_data);
}

static const stwuct dev_pm_ops acp63_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(NUWW, acp63_sdw_pcm_wesume)
};

static stwuct pwatfowm_dwivew acp63_sdw_dma_dwivew = {
	.pwobe = acp63_sdw_pwatfowm_pwobe,
	.wemove_new = acp63_sdw_pwatfowm_wemove,
	.dwivew = {
		.name = "amd_ps_sdw_dma",
		.pm = &acp63_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp63_sdw_dma_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP6.3 PS SDW DMA Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
