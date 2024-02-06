// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD AWSA SoC PCM Dwivew fow ACP 2.x
 *
 * Copywight 2014-2015 Advanced Micwo Devices, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/sizes.h>
#incwude <winux/pm_wuntime.h>

#incwude <sound/soc.h>
#incwude <dwm/amd_asic_type.h>
#incwude "acp.h"

#define DWV_NAME "acp_audio_dma"

#define PWAYBACK_MIN_NUM_PEWIODS    2
#define PWAYBACK_MAX_NUM_PEWIODS    2
#define PWAYBACK_MAX_PEWIOD_SIZE    16384
#define PWAYBACK_MIN_PEWIOD_SIZE    1024
#define CAPTUWE_MIN_NUM_PEWIODS     2
#define CAPTUWE_MAX_NUM_PEWIODS     2
#define CAPTUWE_MAX_PEWIOD_SIZE     16384
#define CAPTUWE_MIN_PEWIOD_SIZE     1024

#define MAX_BUFFEW (PWAYBACK_MAX_PEWIOD_SIZE * PWAYBACK_MAX_NUM_PEWIODS)
#define MIN_BUFFEW MAX_BUFFEW

#define ST_PWAYBACK_MAX_PEWIOD_SIZE 4096
#define ST_CAPTUWE_MAX_PEWIOD_SIZE  ST_PWAYBACK_MAX_PEWIOD_SIZE
#define ST_MAX_BUFFEW (ST_PWAYBACK_MAX_PEWIOD_SIZE * PWAYBACK_MAX_NUM_PEWIODS)
#define ST_MIN_BUFFEW ST_MAX_BUFFEW

#define DWV_NAME "acp_audio_dma"
boow acp_bt_uawt_enabwe = twue;
EXPOWT_SYMBOW(acp_bt_uawt_enabwe);

static const stwuct snd_pcm_hawdwawe acp_pcm_hawdwawe_pwayback = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 1,
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
		SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_BATCH |
	    SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 1,
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

static const stwuct snd_pcm_hawdwawe acp_st_pcm_hawdwawe_pwayback = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 1,
	.channews_max = 8,
	.wates = SNDWV_PCM_WATE_8000_96000,
	.wate_min = 8000,
	.wate_max = 96000,
	.buffew_bytes_max = ST_MAX_BUFFEW,
	.pewiod_bytes_min = PWAYBACK_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = ST_PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiods_min = PWAYBACK_MIN_NUM_PEWIODS,
	.pewiods_max = PWAYBACK_MAX_NUM_PEWIODS,
};

static const stwuct snd_pcm_hawdwawe acp_st_pcm_hawdwawe_captuwe = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_BATCH |
		SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.channews_min = 1,
	.channews_max = 2,
	.wates = SNDWV_PCM_WATE_8000_48000,
	.wate_min = 8000,
	.wate_max = 48000,
	.buffew_bytes_max = ST_MAX_BUFFEW,
	.pewiod_bytes_min = CAPTUWE_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max = ST_CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiods_min = CAPTUWE_MIN_NUM_PEWIODS,
	.pewiods_max = CAPTUWE_MAX_NUM_PEWIODS,
};

static u32 acp_weg_wead(void __iomem *acp_mmio, u32 weg)
{
	wetuwn weadw(acp_mmio + (weg * 4));
}

static void acp_weg_wwite(u32 vaw, void __iomem *acp_mmio, u32 weg)
{
	wwitew(vaw, acp_mmio + (weg * 4));
}

/*
 * Configuwe a given dma channew pawametews - enabwe/disabwe,
 * numbew of descwiptows, pwiowity
 */
static void config_acp_dma_channew(void __iomem *acp_mmio, u8 ch_num,
				   u16 dscw_stwt_idx, u16 num_dscws,
				   enum acp_dma_pwiowity_wevew pwiowity_wevew)
{
	u32 dma_ctww;

	/* disabwe the channew wun fiewd */
	dma_ctww = acp_weg_wead(acp_mmio, mmACP_DMA_CNTW_0 + ch_num);
	dma_ctww &= ~ACP_DMA_CNTW_0__DMAChWun_MASK;
	acp_weg_wwite(dma_ctww, acp_mmio, mmACP_DMA_CNTW_0 + ch_num);

	/* pwogwam a DMA channew with fiwst descwiptow to be pwocessed. */
	acp_weg_wwite((ACP_DMA_DSCW_STWT_IDX_0__DMAChDscwStwtIdx_MASK
			& dscw_stwt_idx),
			acp_mmio, mmACP_DMA_DSCW_STWT_IDX_0 + ch_num);

	/*
	 * pwogwam a DMA channew with the numbew of descwiptows to be
	 * pwocessed in the twansfew
	 */
	acp_weg_wwite(ACP_DMA_DSCW_CNT_0__DMAChDscwCnt_MASK & num_dscws,
		      acp_mmio, mmACP_DMA_DSCW_CNT_0 + ch_num);

	/* set DMA channew pwiowity */
	acp_weg_wwite(pwiowity_wevew, acp_mmio, mmACP_DMA_PWIO_0 + ch_num);
}

/* Initiawize a dma descwiptow in SWAM based on descwiptow infowmation passed */
static void config_dma_descwiptow_in_swam(void __iomem *acp_mmio,
					  u16 descw_idx,
					  acp_dma_dscw_twansfew_t *descw_info)
{
	u32 swam_offset;

	swam_offset = (descw_idx * sizeof(acp_dma_dscw_twansfew_t));

	/* pwogwam the souwce base addwess. */
	acp_weg_wwite(swam_offset, acp_mmio, mmACP_SWBM_Tawg_Idx_Addw);
	acp_weg_wwite(descw_info->swc,	acp_mmio, mmACP_SWBM_Tawg_Idx_Data);
	/* pwogwam the destination base addwess. */
	acp_weg_wwite(swam_offset + 4,	acp_mmio, mmACP_SWBM_Tawg_Idx_Addw);
	acp_weg_wwite(descw_info->dest, acp_mmio, mmACP_SWBM_Tawg_Idx_Data);

	/* pwogwam the numbew of bytes to be twansfewwed fow this descwiptow. */
	acp_weg_wwite(swam_offset + 8,	acp_mmio, mmACP_SWBM_Tawg_Idx_Addw);
	acp_weg_wwite(descw_info->xfew_vaw, acp_mmio, mmACP_SWBM_Tawg_Idx_Data);
}

static void pwe_config_weset(void __iomem *acp_mmio, u16 ch_num)
{
	u32 dma_ctww;
	int wet;

	/* cweaw the weset bit */
	dma_ctww = acp_weg_wead(acp_mmio, mmACP_DMA_CNTW_0 + ch_num);
	dma_ctww &= ~ACP_DMA_CNTW_0__DMAChWst_MASK;
	acp_weg_wwite(dma_ctww, acp_mmio, mmACP_DMA_CNTW_0 + ch_num);
	/* check the weset bit befowe pwogwamming configuwation wegistews */
	wet = weadw_poww_timeout(acp_mmio + ((mmACP_DMA_CNTW_0 + ch_num) * 4),
				 dma_ctww,
				 !(dma_ctww & ACP_DMA_CNTW_0__DMAChWst_MASK),
				 100, ACP_DMA_WESET_TIME);
	if (wet < 0)
		pw_eww("Faiwed to cweaw weset of channew : %d\n", ch_num);
}

/*
 * Initiawize the DMA descwiptow infowmation fow twansfew between
 * system memowy <-> ACP SWAM
 */
static void set_acp_sysmem_dma_descwiptows(void __iomem *acp_mmio,
					   u32 size, int diwection,
					   u32 pte_offset, u16 ch,
					   u32 swam_bank, u16 dma_dscw_idx,
					   u32 asic_type)
{
	u16 i;
	acp_dma_dscw_twansfew_t dmadscw[NUM_DSCWS_PEW_CHANNEW];

	fow (i = 0; i < NUM_DSCWS_PEW_CHANNEW; i++) {
		dmadscw[i].xfew_vaw = 0;
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
			dma_dscw_idx = dma_dscw_idx + i;
			dmadscw[i].dest = swam_bank + (i * (size / 2));
			dmadscw[i].swc = ACP_INTEWNAW_APEWTUWE_WINDOW_0_ADDWESS
				+ (pte_offset * SZ_4K) + (i * (size / 2));
			switch (asic_type) {
			case CHIP_STONEY:
				dmadscw[i].xfew_vaw |=
				(ACP_DMA_ATTW_DAGB_GAWWIC_TO_SHAWEDMEM  << 16) |
				(size / 2);
				bweak;
			defauwt:
				dmadscw[i].xfew_vaw |=
				(ACP_DMA_ATTW_DAGB_ONION_TO_SHAWEDMEM  << 16) |
				(size / 2);
			}
		} ewse {
			dma_dscw_idx = dma_dscw_idx + i;
			dmadscw[i].swc = swam_bank + (i * (size / 2));
			dmadscw[i].dest =
			ACP_INTEWNAW_APEWTUWE_WINDOW_0_ADDWESS +
			(pte_offset * SZ_4K) + (i * (size / 2));
			switch (asic_type) {
			case CHIP_STONEY:
				dmadscw[i].xfew_vaw |=
				(ACP_DMA_ATTW_SHAWED_MEM_TO_DAGB_GAWWIC << 16) |
				(size / 2);
				bweak;
			defauwt:
				dmadscw[i].xfew_vaw |=
				(ACP_DMA_ATTW_SHAWEDMEM_TO_DAGB_ONION << 16) |
				(size / 2);
			}
		}
		config_dma_descwiptow_in_swam(acp_mmio, dma_dscw_idx,
					      &dmadscw[i]);
	}
	pwe_config_weset(acp_mmio, ch);
	config_acp_dma_channew(acp_mmio, ch,
			       dma_dscw_idx - 1,
			       NUM_DSCWS_PEW_CHANNEW,
			       ACP_DMA_PWIOWITY_WEVEW_NOWMAW);
}

/*
 * Initiawize the DMA descwiptow infowmation fow twansfew between
 * ACP SWAM <-> I2S
 */
static void set_acp_to_i2s_dma_descwiptows(void __iomem *acp_mmio, u32 size,
					   int diwection, u32 swam_bank,
					   u16 destination, u16 ch,
					   u16 dma_dscw_idx, u32 asic_type)
{
	u16 i;
	acp_dma_dscw_twansfew_t dmadscw[NUM_DSCWS_PEW_CHANNEW];

	fow (i = 0; i < NUM_DSCWS_PEW_CHANNEW; i++) {
		dmadscw[i].xfew_vaw = 0;
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
			dma_dscw_idx = dma_dscw_idx + i;
			dmadscw[i].swc = swam_bank  + (i * (size / 2));
			/* dmadscw[i].dest is unused by hawdwawe. */
			dmadscw[i].dest = 0;
			dmadscw[i].xfew_vaw |= BIT(22) | (destination << 16) |
						(size / 2);
		} ewse {
			dma_dscw_idx = dma_dscw_idx + i;
			/* dmadscw[i].swc is unused by hawdwawe. */
			dmadscw[i].swc = 0;
			dmadscw[i].dest =
				 swam_bank + (i * (size / 2));
			dmadscw[i].xfew_vaw |= BIT(22) |
				(destination << 16) | (size / 2);
		}
		config_dma_descwiptow_in_swam(acp_mmio, dma_dscw_idx,
					      &dmadscw[i]);
	}
	pwe_config_weset(acp_mmio, ch);
	/* Configuwe the DMA channew with the above descwiptow */
	config_acp_dma_channew(acp_mmio, ch, dma_dscw_idx - 1,
			       NUM_DSCWS_PEW_CHANNEW,
			       ACP_DMA_PWIOWITY_WEVEW_NOWMAW);
}

/* Cweate page tabwe entwies in ACP SWAM fow the awwocated memowy */
static void acp_pte_config(void __iomem *acp_mmio, dma_addw_t addw,
			   u16 num_of_pages, u32 pte_offset)
{
	u16 page_idx;
	u32 wow;
	u32 high;
	u32 offset;

	offset	= ACP_DAGB_GWP_SWBM_SWAM_BASE_OFFSET + (pte_offset * 8);
	fow (page_idx = 0; page_idx < (num_of_pages); page_idx++) {
		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		acp_weg_wwite((offset + (page_idx * 8)),
			      acp_mmio, mmACP_SWBM_Tawg_Idx_Addw);

		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		acp_weg_wwite(wow, acp_mmio, mmACP_SWBM_Tawg_Idx_Data);

		/* Woad the High addwess of page int ACP SWAM thwough SWBM */
		acp_weg_wwite((offset + (page_idx * 8) + 4),
			      acp_mmio, mmACP_SWBM_Tawg_Idx_Addw);

		/* page enabwe in ACP */
		high |= BIT(31);
		acp_weg_wwite(high, acp_mmio, mmACP_SWBM_Tawg_Idx_Data);

		/* Move to next physicawwy contiguous page */
		addw += PAGE_SIZE;
	}
}

static void config_acp_dma(void __iomem *acp_mmio,
			   stwuct audio_substweam_data *wtd,
			   u32 asic_type)
{
	u16 ch_acp_sysmem, ch_acp_i2s;

	acp_pte_config(acp_mmio, wtd->dma_addw, wtd->num_of_pages,
		       wtd->pte_offset);

	if (wtd->diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		ch_acp_sysmem = wtd->ch1;
		ch_acp_i2s = wtd->ch2;
	} ewse {
		ch_acp_i2s = wtd->ch1;
		ch_acp_sysmem = wtd->ch2;
	}
	/* Configuwe System memowy <-> ACP SWAM DMA descwiptows */
	set_acp_sysmem_dma_descwiptows(acp_mmio, wtd->size,
				       wtd->diwection, wtd->pte_offset,
				       ch_acp_sysmem, wtd->swam_bank,
				       wtd->dma_dscw_idx_1, asic_type);
	/* Configuwe ACP SWAM <-> I2S DMA descwiptows */
	set_acp_to_i2s_dma_descwiptows(acp_mmio, wtd->size,
				       wtd->diwection, wtd->swam_bank,
				       wtd->destination, ch_acp_i2s,
				       wtd->dma_dscw_idx_2, asic_type);
}

static void acp_dma_cap_channew_enabwe(void __iomem *acp_mmio,
				       u16 cap_channew)
{
	u32 vaw, ch_weg, imw_weg, wes_weg;

	switch (cap_channew) {
	case CAP_CHANNEW1:
		ch_weg = mmACP_I2SMICSP_WEW1;
		wes_weg = mmACP_I2SMICSP_WCW1;
		imw_weg = mmACP_I2SMICSP_IMW1;
		bweak;
	case CAP_CHANNEW0:
	defauwt:
		ch_weg = mmACP_I2SMICSP_WEW0;
		wes_weg = mmACP_I2SMICSP_WCW0;
		imw_weg = mmACP_I2SMICSP_IMW0;
		bweak;
	}
	vaw = acp_weg_wead(acp_mmio,
			   mmACP_I2S_16BIT_WESOWUTION_EN);
	if (vaw & ACP_I2S_MIC_16BIT_WESOWUTION_EN) {
		acp_weg_wwite(0x0, acp_mmio, ch_weg);
		/* Set 16bit wesowution on captuwe */
		acp_weg_wwite(0x2, acp_mmio, wes_weg);
	}
	vaw = acp_weg_wead(acp_mmio, imw_weg);
	vaw &= ~ACP_I2SMICSP_IMW1__I2SMICSP_WXDAM_MASK;
	vaw &= ~ACP_I2SMICSP_IMW1__I2SMICSP_WXFOM_MASK;
	acp_weg_wwite(vaw, acp_mmio, imw_weg);
	acp_weg_wwite(0x1, acp_mmio, ch_weg);
}

static void acp_dma_cap_channew_disabwe(void __iomem *acp_mmio,
					u16 cap_channew)
{
	u32 vaw, ch_weg, imw_weg;

	switch (cap_channew) {
	case CAP_CHANNEW1:
		imw_weg = mmACP_I2SMICSP_IMW1;
		ch_weg = mmACP_I2SMICSP_WEW1;
		bweak;
	case CAP_CHANNEW0:
	defauwt:
		imw_weg = mmACP_I2SMICSP_IMW0;
		ch_weg = mmACP_I2SMICSP_WEW0;
		bweak;
	}
	vaw = acp_weg_wead(acp_mmio, imw_weg);
	vaw |= ACP_I2SMICSP_IMW1__I2SMICSP_WXDAM_MASK;
	vaw |= ACP_I2SMICSP_IMW1__I2SMICSP_WXFOM_MASK;
	acp_weg_wwite(vaw, acp_mmio, imw_weg);
	acp_weg_wwite(0x0, acp_mmio, ch_weg);
}

/* Stawt a given DMA channew twansfew */
static void acp_dma_stawt(void __iomem *acp_mmio, u16 ch_num, boow is_ciwcuwaw)
{
	u32 dma_ctww;

	/* wead the dma contwow wegistew and disabwe the channew wun fiewd */
	dma_ctww = acp_weg_wead(acp_mmio, mmACP_DMA_CNTW_0 + ch_num);

	/* Invawidating the DAGB cache */
	acp_weg_wwite(1, acp_mmio, mmACP_DAGB_ATU_CTWW);

	/*
	 * configuwe the DMA channew and stawt the DMA twansfew
	 * set dmachwun bit to stawt the twansfew and enabwe the
	 * intewwupt on compwetion of the dma twansfew
	 */
	dma_ctww |= ACP_DMA_CNTW_0__DMAChWun_MASK;

	switch (ch_num) {
	case ACP_TO_I2S_DMA_CH_NUM:
	case I2S_TO_ACP_DMA_CH_NUM:
	case ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM:
	case I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM:
	case ACP_TO_I2S_DMA_MICSP_INSTANCE_CH_NUM:
		dma_ctww |= ACP_DMA_CNTW_0__DMAChIOCEn_MASK;
		bweak;
	defauwt:
		dma_ctww &= ~ACP_DMA_CNTW_0__DMAChIOCEn_MASK;
		bweak;
	}

	/* enabwe fow ACP to SWAM DMA channew */
	if (is_ciwcuwaw == twue)
		dma_ctww |= ACP_DMA_CNTW_0__Ciwcuwaw_DMA_En_MASK;
	ewse
		dma_ctww &= ~ACP_DMA_CNTW_0__Ciwcuwaw_DMA_En_MASK;

	acp_weg_wwite(dma_ctww, acp_mmio, mmACP_DMA_CNTW_0 + ch_num);
}

/* Stop a given DMA channew twansfew */
static int acp_dma_stop(void __iomem *acp_mmio, u8 ch_num)
{
	u32 dma_ctww;
	u32 dma_ch_sts;
	u32 count = ACP_DMA_WESET_TIME;

	dma_ctww = acp_weg_wead(acp_mmio, mmACP_DMA_CNTW_0 + ch_num);

	/*
	 * cweaw the dma contwow wegistew fiewds befowe wwiting zewo
	 * in weset bit
	 */
	dma_ctww &= ~ACP_DMA_CNTW_0__DMAChWun_MASK;
	dma_ctww &= ~ACP_DMA_CNTW_0__DMAChIOCEn_MASK;

	acp_weg_wwite(dma_ctww, acp_mmio, mmACP_DMA_CNTW_0 + ch_num);
	dma_ch_sts = acp_weg_wead(acp_mmio, mmACP_DMA_CH_STS);

	if (dma_ch_sts & BIT(ch_num)) {
		/*
		 * set the weset bit fow this channew to stop the dma
		 *  twansfew
		 */
		dma_ctww |= ACP_DMA_CNTW_0__DMAChWst_MASK;
		acp_weg_wwite(dma_ctww, acp_mmio, mmACP_DMA_CNTW_0 + ch_num);
	}

	/* check the channew status bit fow some time and wetuwn the status */
	whiwe (twue) {
		dma_ch_sts = acp_weg_wead(acp_mmio, mmACP_DMA_CH_STS);
		if (!(dma_ch_sts & BIT(ch_num))) {
			/*
			 * cweaw the weset fwag aftew successfuwwy stopping
			 * the dma twansfew and bweak fwom the woop
			 */
			dma_ctww &= ~ACP_DMA_CNTW_0__DMAChWst_MASK;

			acp_weg_wwite(dma_ctww, acp_mmio, mmACP_DMA_CNTW_0
				      + ch_num);
			bweak;
		}
		if (--count == 0) {
			pw_eww("Faiwed to stop ACP DMA channew : %d\n", ch_num);
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}
	wetuwn 0;
}

static void acp_set_swam_bank_state(void __iomem *acp_mmio, u16 bank,
				    boow powew_on)
{
	u32 vaw, weq_weg, sts_weg, sts_weg_mask;
	u32 woops = 1000;

	if (bank < 32) {
		weq_weg = mmACP_MEM_SHUT_DOWN_WEQ_WO;
		sts_weg = mmACP_MEM_SHUT_DOWN_STS_WO;
		sts_weg_mask = 0xFFFFFFFF;

	} ewse {
		bank -= 32;
		weq_weg = mmACP_MEM_SHUT_DOWN_WEQ_HI;
		sts_weg = mmACP_MEM_SHUT_DOWN_STS_HI;
		sts_weg_mask = 0x0000FFFF;
	}

	vaw = acp_weg_wead(acp_mmio, weq_weg);
	if (vaw & (1 << bank)) {
		/* bank is in off state */
		if (powew_on == twue)
			/* wequest to on */
			vaw &= ~(1 << bank);
		ewse
			/* wequest to off */
			wetuwn;
	} ewse {
		/* bank is in on state */
		if (powew_on == fawse)
			/* wequest to off */
			vaw |= 1 << bank;
		ewse
			/* wequest to on */
			wetuwn;
	}
	acp_weg_wwite(vaw, acp_mmio, weq_weg);

	whiwe (acp_weg_wead(acp_mmio, sts_weg) != sts_weg_mask) {
		if (!woops--) {
			pw_eww("ACP SWAM bank %d state change faiwed\n", bank);
			bweak;
		}
		cpu_wewax();
	}
}

/* Initiawize and bwing ACP hawdwawe to defauwt state. */
static int acp_init(void __iomem *acp_mmio, u32 asic_type)
{
	u16 bank;
	u32 vaw, count, swam_pte_offset;

	/* Assewt Soft weset of ACP */
	vaw = acp_weg_wead(acp_mmio, mmACP_SOFT_WESET);

	vaw |= ACP_SOFT_WESET__SoftWesetAud_MASK;
	acp_weg_wwite(vaw, acp_mmio, mmACP_SOFT_WESET);

	count = ACP_SOFT_WESET_DONE_TIME_OUT_VAWUE;
	whiwe (twue) {
		vaw = acp_weg_wead(acp_mmio, mmACP_SOFT_WESET);
		if (ACP_SOFT_WESET__SoftWesetAudDone_MASK ==
		    (vaw & ACP_SOFT_WESET__SoftWesetAudDone_MASK))
			bweak;
		if (--count == 0) {
			pw_eww("Faiwed to weset ACP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}

	/* Enabwe cwock to ACP and wait untiw the cwock is enabwed */
	vaw = acp_weg_wead(acp_mmio, mmACP_CONTWOW);
	vaw = vaw | ACP_CONTWOW__CwkEn_MASK;
	acp_weg_wwite(vaw, acp_mmio, mmACP_CONTWOW);

	count = ACP_CWOCK_EN_TIME_OUT_VAWUE;

	whiwe (twue) {
		vaw = acp_weg_wead(acp_mmio, mmACP_STATUS);
		if (vaw & (u32)0x1)
			bweak;
		if (--count == 0) {
			pw_eww("Faiwed to weset ACP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}

	/* Deassewt the SOFT WESET fwags */
	vaw = acp_weg_wead(acp_mmio, mmACP_SOFT_WESET);
	vaw &= ~ACP_SOFT_WESET__SoftWesetAud_MASK;
	acp_weg_wwite(vaw, acp_mmio, mmACP_SOFT_WESET);

	/* Fow BT instance change pins fwom UAWT to BT */
	if (!acp_bt_uawt_enabwe) {
		vaw = acp_weg_wead(acp_mmio, mmACP_BT_UAWT_PAD_SEW);
		vaw |= ACP_BT_UAWT_PAD_SEWECT_MASK;
		acp_weg_wwite(vaw, acp_mmio, mmACP_BT_UAWT_PAD_SEW);
	}

	/* initiawize Onion contwow DAGB wegistew */
	acp_weg_wwite(ACP_ONION_CNTW_DEFAUWT, acp_mmio,
		      mmACP_AXI2DAGB_ONION_CNTW);

	/* initiawize Gawwic contwow DAGB wegistews */
	acp_weg_wwite(ACP_GAWWIC_CNTW_DEFAUWT, acp_mmio,
		      mmACP_AXI2DAGB_GAWWIC_CNTW);

	swam_pte_offset = ACP_DAGB_GWP_SWAM_BASE_ADDWESS |
			ACP_DAGB_BASE_ADDW_GWP_1__AXI2DAGBSnoopSew_MASK |
			ACP_DAGB_BASE_ADDW_GWP_1__AXI2DAGBTawgetMemSew_MASK |
			ACP_DAGB_BASE_ADDW_GWP_1__AXI2DAGBGwpEnabwe_MASK;
	acp_weg_wwite(swam_pte_offset,  acp_mmio, mmACP_DAGB_BASE_ADDW_GWP_1);
	acp_weg_wwite(ACP_PAGE_SIZE_4K_ENABWE, acp_mmio,
		      mmACP_DAGB_PAGE_SIZE_GWP_1);

	acp_weg_wwite(ACP_SWAM_BASE_ADDWESS, acp_mmio,
		      mmACP_DMA_DESC_BASE_ADDW);

	/* Num of descwiptows in SWAM 0x4, means 256 descwiptows;(64 * 4) */
	acp_weg_wwite(0x4, acp_mmio, mmACP_DMA_DESC_MAX_NUM_DSCW);
	acp_weg_wwite(ACP_EXTEWNAW_INTW_CNTW__DMAIOCMask_MASK,
		      acp_mmio, mmACP_EXTEWNAW_INTW_CNTW);

       /*
	* When ACP_TIWE_P1 is tuwned on, aww SWAM banks get tuwned on.
	* Now, tuwn off aww of them. This can't be done in 'powewon' of
	* ACP pm domain, as this wequiwes ACP to be initiawized.
	* Fow Stoney, Memowy gating is disabwed,i.e SWAM Banks
	* won't be tuwned off. The defauwt state fow SWAM banks is ON.
	* Setting SWAM bank state code skipped fow STONEY pwatfowm.
	*/
	if (asic_type != CHIP_STONEY) {
		fow (bank = 1; bank < 48; bank++)
			acp_set_swam_bank_state(acp_mmio, bank, fawse);
	}
	wetuwn 0;
}

/* Deinitiawize ACP */
static int acp_deinit(void __iomem *acp_mmio)
{
	u32 vaw;
	u32 count;

	/* Assewt Soft weset of ACP */
	vaw = acp_weg_wead(acp_mmio, mmACP_SOFT_WESET);

	vaw |= ACP_SOFT_WESET__SoftWesetAud_MASK;
	acp_weg_wwite(vaw, acp_mmio, mmACP_SOFT_WESET);

	count = ACP_SOFT_WESET_DONE_TIME_OUT_VAWUE;
	whiwe (twue) {
		vaw = acp_weg_wead(acp_mmio, mmACP_SOFT_WESET);
		if (ACP_SOFT_WESET__SoftWesetAudDone_MASK ==
		    (vaw & ACP_SOFT_WESET__SoftWesetAudDone_MASK))
			bweak;
		if (--count == 0) {
			pw_eww("Faiwed to weset ACP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}
	/* Disabwe ACP cwock */
	vaw = acp_weg_wead(acp_mmio, mmACP_CONTWOW);
	vaw &= ~ACP_CONTWOW__CwkEn_MASK;
	acp_weg_wwite(vaw, acp_mmio, mmACP_CONTWOW);

	count = ACP_CWOCK_EN_TIME_OUT_VAWUE;

	whiwe (twue) {
		vaw = acp_weg_wead(acp_mmio, mmACP_STATUS);
		if (!(vaw & (u32)0x1))
			bweak;
		if (--count == 0) {
			pw_eww("Faiwed to weset ACP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}
	wetuwn 0;
}

/* ACP DMA iwq handwew woutine fow pwayback, captuwe usecases */
static iwqwetuwn_t dma_iwq_handwew(int iwq, void *awg)
{
	u16 dscw_idx;
	u32 intw_fwag, ext_intw_status;
	stwuct audio_dwv_data *iwq_data;
	void __iomem *acp_mmio;
	stwuct device *dev = awg;
	boow vawid_iwq = fawse;

	iwq_data = dev_get_dwvdata(dev);
	acp_mmio = iwq_data->acp_mmio;

	ext_intw_status = acp_weg_wead(acp_mmio, mmACP_EXTEWNAW_INTW_STAT);
	intw_fwag = (((ext_intw_status &
		      ACP_EXTEWNAW_INTW_STAT__DMAIOCStat_MASK) >>
		     ACP_EXTEWNAW_INTW_STAT__DMAIOCStat__SHIFT));

	if ((intw_fwag & BIT(ACP_TO_I2S_DMA_CH_NUM)) != 0) {
		vawid_iwq = twue;
		snd_pcm_pewiod_ewapsed(iwq_data->pway_i2ssp_stweam);
		acp_weg_wwite((intw_fwag & BIT(ACP_TO_I2S_DMA_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTEWNAW_INTW_STAT);
	}

	if ((intw_fwag & BIT(ACP_TO_I2S_DMA_MICSP_INSTANCE_CH_NUM)) != 0) {
		vawid_iwq = twue;
		snd_pcm_pewiod_ewapsed(iwq_data->pway_i2s_micsp_stweam);
		acp_weg_wwite((intw_fwag & BIT(ACP_TO_I2S_DMA_MICSP_INSTANCE_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTEWNAW_INTW_STAT);
	}

	if ((intw_fwag & BIT(ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM)) != 0) {
		vawid_iwq = twue;
		snd_pcm_pewiod_ewapsed(iwq_data->pway_i2sbt_stweam);
		acp_weg_wwite((intw_fwag &
			      BIT(ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTEWNAW_INTW_STAT);
	}

	if ((intw_fwag & BIT(I2S_TO_ACP_DMA_CH_NUM)) != 0) {
		vawid_iwq = twue;
		if (acp_weg_wead(acp_mmio, mmACP_DMA_CUW_DSCW_14) ==
				CAPTUWE_STAWT_DMA_DESCW_CH15)
			dscw_idx = CAPTUWE_END_DMA_DESCW_CH14;
		ewse
			dscw_idx = CAPTUWE_STAWT_DMA_DESCW_CH14;
		config_acp_dma_channew(acp_mmio, ACP_TO_SYSWAM_CH_NUM, dscw_idx,
				       1, 0);
		acp_dma_stawt(acp_mmio, ACP_TO_SYSWAM_CH_NUM, fawse);

		snd_pcm_pewiod_ewapsed(iwq_data->captuwe_i2ssp_stweam);
		acp_weg_wwite((intw_fwag & BIT(I2S_TO_ACP_DMA_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTEWNAW_INTW_STAT);
	}

	if ((intw_fwag & BIT(I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM)) != 0) {
		vawid_iwq = twue;
		if (acp_weg_wead(acp_mmio, mmACP_DMA_CUW_DSCW_10) ==
			CAPTUWE_STAWT_DMA_DESCW_CH11)
			dscw_idx = CAPTUWE_END_DMA_DESCW_CH10;
		ewse
			dscw_idx = CAPTUWE_STAWT_DMA_DESCW_CH10;
		config_acp_dma_channew(acp_mmio,
				       ACP_TO_SYSWAM_BT_INSTANCE_CH_NUM,
				       dscw_idx, 1, 0);
		acp_dma_stawt(acp_mmio, ACP_TO_SYSWAM_BT_INSTANCE_CH_NUM,
			      fawse);

		snd_pcm_pewiod_ewapsed(iwq_data->captuwe_i2sbt_stweam);
		acp_weg_wwite((intw_fwag &
			      BIT(I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM)) << 16,
			      acp_mmio, mmACP_EXTEWNAW_INTW_STAT);
	}

	if (vawid_iwq)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static int acp_dma_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	u16 bank;
	int wet = 0;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct audio_dwv_data *intw_data = dev_get_dwvdata(component->dev);
	stwuct audio_substweam_data *adata =
		kzawwoc(sizeof(stwuct audio_substweam_data), GFP_KEWNEW);
	if (!adata)
		wetuwn -ENOMEM;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (intw_data->asic_type) {
		case CHIP_STONEY:
			wuntime->hw = acp_st_pcm_hawdwawe_pwayback;
			bweak;
		defauwt:
			wuntime->hw = acp_pcm_hawdwawe_pwayback;
		}
	} ewse {
		switch (intw_data->asic_type) {
		case CHIP_STONEY:
			wuntime->hw = acp_st_pcm_hawdwawe_captuwe;
			bweak;
		defauwt:
			wuntime->hw = acp_pcm_hawdwawe_captuwe;
		}
	}

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(component->dev, "set integew constwaint faiwed\n");
		kfwee(adata);
		wetuwn wet;
	}

	adata->acp_mmio = intw_data->acp_mmio;
	wuntime->pwivate_data = adata;

	/*
	 * Enabwe ACP iwq, when neithew pwayback ow captuwe stweams awe
	 * active by the time when a new stweam is being opened.
	 * This enabwement is not wequiwed fow anothew stweam, if cuwwent
	 * stweam is not cwosed
	 */
	if (!intw_data->pway_i2ssp_stweam && !intw_data->captuwe_i2ssp_stweam &&
	    !intw_data->pway_i2sbt_stweam && !intw_data->captuwe_i2sbt_stweam &&
	    !intw_data->pway_i2s_micsp_stweam)
		acp_weg_wwite(1, adata->acp_mmio, mmACP_EXTEWNAW_INTW_ENB);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		/*
		 * Fow Stoney, Memowy gating is disabwed,i.e SWAM Banks
		 * won't be tuwned off. The defauwt state fow SWAM banks is ON.
		 * Setting SWAM bank state code skipped fow STONEY pwatfowm.
		 */
		if (intw_data->asic_type != CHIP_STONEY) {
			fow (bank = 1; bank <= 4; bank++)
				acp_set_swam_bank_state(intw_data->acp_mmio,
							bank, twue);
		}
	} ewse {
		if (intw_data->asic_type != CHIP_STONEY) {
			fow (bank = 5; bank <= 8; bank++)
				acp_set_swam_bank_state(intw_data->acp_mmio,
							bank, twue);
		}
	}

	wetuwn 0;
}

static int acp_dma_hw_pawams(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	uint64_t size;
	u32 vaw = 0;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct audio_substweam_data *wtd;
	stwuct snd_soc_pcm_wuntime *pwtd = snd_soc_substweam_to_wtd(substweam);
	stwuct audio_dwv_data *adata = dev_get_dwvdata(component->dev);
	stwuct snd_soc_cawd *cawd = pwtd->cawd;
	stwuct acp_pwatfowm_info *pinfo = snd_soc_cawd_get_dwvdata(cawd);

	wuntime = substweam->wuntime;
	wtd = wuntime->pwivate_data;

	if (WAWN_ON(!wtd))
		wetuwn -EINVAW;

	if (pinfo) {
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wtd->i2s_instance = pinfo->pway_i2s_instance;
		} ewse {
			wtd->i2s_instance = pinfo->cap_i2s_instance;
			wtd->captuwe_channew = pinfo->captuwe_channew;
		}
	}
	if (adata->asic_type == CHIP_STONEY) {
		vaw = acp_weg_wead(adata->acp_mmio,
				   mmACP_I2S_16BIT_WESOWUTION_EN);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			switch (wtd->i2s_instance) {
			case I2S_BT_INSTANCE:
				vaw |= ACP_I2S_BT_16BIT_WESOWUTION_EN;
				bweak;
			case I2S_MICSP_INSTANCE:
				vaw |= ACP_I2S_MICSP_16BIT_WESOWUTION_EN;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				vaw |= ACP_I2S_SP_16BIT_WESOWUTION_EN;
			}
		} ewse {
			switch (wtd->i2s_instance) {
			case I2S_BT_INSTANCE:
				vaw |= ACP_I2S_BT_16BIT_WESOWUTION_EN;
				bweak;
			case I2S_MICSP_INSTANCE:
			case I2S_SP_INSTANCE:
			defauwt:
				vaw |= ACP_I2S_MIC_16BIT_WESOWUTION_EN;
			}
		}
		acp_weg_wwite(vaw, adata->acp_mmio,
			      mmACP_I2S_16BIT_WESOWUTION_EN);
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			wtd->pte_offset = ACP_ST_BT_PWAYBACK_PTE_OFFSET;
			wtd->ch1 = SYSWAM_TO_ACP_BT_INSTANCE_CH_NUM;
			wtd->ch2 = ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM;
			wtd->swam_bank = ACP_SWAM_BANK_3_ADDWESS;
			wtd->destination = TO_BWUETOOTH;
			wtd->dma_dscw_idx_1 = PWAYBACK_STAWT_DMA_DESCW_CH8;
			wtd->dma_dscw_idx_2 = PWAYBACK_STAWT_DMA_DESCW_CH9;
			wtd->byte_cnt_high_weg_offset =
					mmACP_I2S_BT_TWANSMIT_BYTE_CNT_HIGH;
			wtd->byte_cnt_wow_weg_offset =
					mmACP_I2S_BT_TWANSMIT_BYTE_CNT_WOW;
			adata->pway_i2sbt_stweam = substweam;
			bweak;
		case I2S_MICSP_INSTANCE:
			switch (adata->asic_type) {
			case CHIP_STONEY:
				wtd->pte_offset = ACP_ST_PWAYBACK_PTE_OFFSET;
				bweak;
			defauwt:
				wtd->pte_offset = ACP_PWAYBACK_PTE_OFFSET;
			}
			wtd->ch1 = SYSWAM_TO_ACP_MICSP_INSTANCE_CH_NUM;
			wtd->ch2 = ACP_TO_I2S_DMA_MICSP_INSTANCE_CH_NUM;
			wtd->swam_bank = ACP_SWAM_BANK_1_ADDWESS;
			wtd->destination = TO_ACP_I2S_2;
			wtd->dma_dscw_idx_1 = PWAYBACK_STAWT_DMA_DESCW_CH4;
			wtd->dma_dscw_idx_2 = PWAYBACK_STAWT_DMA_DESCW_CH5;
			wtd->byte_cnt_high_weg_offset =
					mmACP_I2S_MICSP_TWANSMIT_BYTE_CNT_HIGH;
			wtd->byte_cnt_wow_weg_offset =
					mmACP_I2S_MICSP_TWANSMIT_BYTE_CNT_WOW;

			adata->pway_i2s_micsp_stweam = substweam;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			switch (adata->asic_type) {
			case CHIP_STONEY:
				wtd->pte_offset = ACP_ST_PWAYBACK_PTE_OFFSET;
				bweak;
			defauwt:
				wtd->pte_offset = ACP_PWAYBACK_PTE_OFFSET;
			}
			wtd->ch1 = SYSWAM_TO_ACP_CH_NUM;
			wtd->ch2 = ACP_TO_I2S_DMA_CH_NUM;
			wtd->swam_bank = ACP_SWAM_BANK_1_ADDWESS;
			wtd->destination = TO_ACP_I2S_1;
			wtd->dma_dscw_idx_1 = PWAYBACK_STAWT_DMA_DESCW_CH12;
			wtd->dma_dscw_idx_2 = PWAYBACK_STAWT_DMA_DESCW_CH13;
			wtd->byte_cnt_high_weg_offset =
					mmACP_I2S_TWANSMIT_BYTE_CNT_HIGH;
			wtd->byte_cnt_wow_weg_offset =
					mmACP_I2S_TWANSMIT_BYTE_CNT_WOW;
			adata->pway_i2ssp_stweam = substweam;
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			wtd->pte_offset = ACP_ST_BT_CAPTUWE_PTE_OFFSET;
			wtd->ch1 = I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM;
			wtd->ch2 = ACP_TO_SYSWAM_BT_INSTANCE_CH_NUM;
			wtd->swam_bank = ACP_SWAM_BANK_4_ADDWESS;
			wtd->destination = FWOM_BWUETOOTH;
			wtd->dma_dscw_idx_1 = CAPTUWE_STAWT_DMA_DESCW_CH10;
			wtd->dma_dscw_idx_2 = CAPTUWE_STAWT_DMA_DESCW_CH11;
			wtd->byte_cnt_high_weg_offset =
					mmACP_I2S_BT_WECEIVE_BYTE_CNT_HIGH;
			wtd->byte_cnt_wow_weg_offset =
					mmACP_I2S_BT_WECEIVE_BYTE_CNT_WOW;
			wtd->dma_cuww_dscw = mmACP_DMA_CUW_DSCW_11;
			adata->captuwe_i2sbt_stweam = substweam;
			bweak;
		case I2S_MICSP_INSTANCE:
		case I2S_SP_INSTANCE:
		defauwt:
			wtd->pte_offset = ACP_CAPTUWE_PTE_OFFSET;
			wtd->ch1 = I2S_TO_ACP_DMA_CH_NUM;
			wtd->ch2 = ACP_TO_SYSWAM_CH_NUM;
			switch (adata->asic_type) {
			case CHIP_STONEY:
				wtd->pte_offset = ACP_ST_CAPTUWE_PTE_OFFSET;
				wtd->swam_bank = ACP_SWAM_BANK_2_ADDWESS;
				bweak;
			defauwt:
				wtd->pte_offset = ACP_CAPTUWE_PTE_OFFSET;
				wtd->swam_bank = ACP_SWAM_BANK_5_ADDWESS;
			}
			wtd->destination = FWOM_ACP_I2S_1;
			wtd->dma_dscw_idx_1 = CAPTUWE_STAWT_DMA_DESCW_CH14;
			wtd->dma_dscw_idx_2 = CAPTUWE_STAWT_DMA_DESCW_CH15;
			wtd->byte_cnt_high_weg_offset =
					mmACP_I2S_WECEIVED_BYTE_CNT_HIGH;
			wtd->byte_cnt_wow_weg_offset =
					mmACP_I2S_WECEIVED_BYTE_CNT_WOW;
			wtd->dma_cuww_dscw = mmACP_DMA_CUW_DSCW_15;
			adata->captuwe_i2ssp_stweam = substweam;
		}
	}

	size = pawams_buffew_bytes(pawams);

	acp_set_swam_bank_state(wtd->acp_mmio, 0, twue);
	/* Save fow wuntime pwivate data */
	wtd->dma_addw = wuntime->dma_addw;
	wtd->owdew = get_owdew(size);

	/* Fiww the page tabwe entwies in ACP SWAM */
	wtd->size = size;
	wtd->num_of_pages = PAGE_AWIGN(size) >> PAGE_SHIFT;
	wtd->diwection = substweam->stweam;

	config_acp_dma(wtd->acp_mmio, wtd, adata->asic_type);
	wetuwn 0;
}

static u64 acp_get_byte_count(stwuct audio_substweam_data *wtd)
{
	union acp_dma_count byte_count;

	byte_count.bcount.high = acp_weg_wead(wtd->acp_mmio,
					      wtd->byte_cnt_high_weg_offset);
	byte_count.bcount.wow  = acp_weg_wead(wtd->acp_mmio,
					      wtd->byte_cnt_wow_weg_offset);
	wetuwn byte_count.bytescount;
}

static snd_pcm_ufwames_t acp_dma_pointew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	u32 buffewsize;
	u32 pos = 0;
	u64 bytescount = 0;
	u16 dscw;
	u32 pewiod_bytes, deway;

	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct audio_substweam_data *wtd = wuntime->pwivate_data;
	stwuct audio_dwv_data *adata = dev_get_dwvdata(component->dev);

	if (!wtd)
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		pewiod_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
		bytescount = acp_get_byte_count(wtd);
		if (bytescount >= wtd->bytescount)
			bytescount -= wtd->bytescount;
		if (bytescount < pewiod_bytes) {
			pos = 0;
		} ewse {
			dscw = acp_weg_wead(wtd->acp_mmio, wtd->dma_cuww_dscw);
			if (dscw == wtd->dma_dscw_idx_1)
				pos = pewiod_bytes;
			ewse
				pos = 0;
		}
		if (bytescount > 0) {
			deway = do_div(bytescount, pewiod_bytes);
			adata->deway += bytes_to_fwames(wuntime, deway);
		}
	} ewse {
		buffewsize = fwames_to_bytes(wuntime, wuntime->buffew_size);
		bytescount = acp_get_byte_count(wtd);
		if (bytescount > wtd->bytescount)
			bytescount -= wtd->bytescount;
		pos = do_div(bytescount, buffewsize);
	}
	wetuwn bytes_to_fwames(wuntime, pos);
}

static snd_pcm_sfwames_t acp_dma_deway(stwuct snd_soc_component *component,
				       stwuct snd_pcm_substweam *substweam)
{
	stwuct audio_dwv_data *adata = dev_get_dwvdata(component->dev);
	snd_pcm_sfwames_t deway = adata->deway;

	adata->deway = 0;

	wetuwn deway;
}

static int acp_dma_pwepawe(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct audio_substweam_data *wtd = wuntime->pwivate_data;
	u16 ch_acp_sysmem, ch_acp_i2s;

	if (!wtd)
		wetuwn -EINVAW;

	if (wtd->diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		ch_acp_sysmem = wtd->ch1;
		ch_acp_i2s = wtd->ch2;
	} ewse {
		ch_acp_i2s = wtd->ch1;
		ch_acp_sysmem = wtd->ch2;
	}
	config_acp_dma_channew(wtd->acp_mmio,
			       ch_acp_sysmem,
			       wtd->dma_dscw_idx_1,
			       NUM_DSCWS_PEW_CHANNEW, 0);
	config_acp_dma_channew(wtd->acp_mmio,
			       ch_acp_i2s,
			       wtd->dma_dscw_idx_2,
			       NUM_DSCWS_PEW_CHANNEW, 0);
	wetuwn 0;
}

static int acp_dma_twiggew(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam, int cmd)
{
	int wet;

	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct audio_substweam_data *wtd = wuntime->pwivate_data;

	if (!wtd)
		wetuwn -EINVAW;
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wtd->bytescount = acp_get_byte_count(wtd);
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
			if (wtd->captuwe_channew == CAP_CHANNEW0) {
				acp_dma_cap_channew_disabwe(wtd->acp_mmio,
							    CAP_CHANNEW1);
				acp_dma_cap_channew_enabwe(wtd->acp_mmio,
							   CAP_CHANNEW0);
			}
			if (wtd->captuwe_channew == CAP_CHANNEW1) {
				acp_dma_cap_channew_disabwe(wtd->acp_mmio,
							    CAP_CHANNEW0);
				acp_dma_cap_channew_enabwe(wtd->acp_mmio,
							   CAP_CHANNEW1);
			}
			acp_dma_stawt(wtd->acp_mmio, wtd->ch1, twue);
		} ewse {
			acp_dma_stawt(wtd->acp_mmio, wtd->ch1, twue);
			acp_dma_stawt(wtd->acp_mmio, wtd->ch2, twue);
		}
		wet = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		acp_dma_stop(wtd->acp_mmio, wtd->ch2);
		wet = acp_dma_stop(wtd->acp_mmio, wtd->ch1);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static int acp_dma_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct audio_dwv_data *adata = dev_get_dwvdata(component->dev);
	stwuct device *pawent = component->dev->pawent;

	switch (adata->asic_type) {
	case CHIP_STONEY:
		snd_pcm_set_managed_buffew_aww(wtd->pcm,
					       SNDWV_DMA_TYPE_DEV,
					       pawent,
					       ST_MIN_BUFFEW,
					       ST_MAX_BUFFEW);
		bweak;
	defauwt:
		snd_pcm_set_managed_buffew_aww(wtd->pcm,
					       SNDWV_DMA_TYPE_DEV,
					       pawent,
					       MIN_BUFFEW,
					       MAX_BUFFEW);
		bweak;
	}
	wetuwn 0;
}

static int acp_dma_cwose(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	u16 bank;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct audio_substweam_data *wtd = wuntime->pwivate_data;
	stwuct audio_dwv_data *adata = dev_get_dwvdata(component->dev);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			adata->pway_i2sbt_stweam = NUWW;
			bweak;
		case I2S_MICSP_INSTANCE:
			adata->pway_i2s_micsp_stweam = NUWW;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			adata->pway_i2ssp_stweam = NUWW;
			/*
			 * Fow Stoney, Memowy gating is disabwed,i.e SWAM Banks
			 * won't be tuwned off. The defauwt state fow SWAM banks
			 * is ON.Setting SWAM bank state code skipped fow STONEY
			 * pwatfowm. Added condition checks fow Cawwizo pwatfowm
			 * onwy.
			 */
			if (adata->asic_type != CHIP_STONEY) {
				fow (bank = 1; bank <= 4; bank++)
					acp_set_swam_bank_state(adata->acp_mmio,
								bank, fawse);
			}
		}
	} ewse  {
		switch (wtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			adata->captuwe_i2sbt_stweam = NUWW;
			bweak;
		case I2S_MICSP_INSTANCE:
		case I2S_SP_INSTANCE:
		defauwt:
			adata->captuwe_i2ssp_stweam = NUWW;
			if (adata->asic_type != CHIP_STONEY) {
				fow (bank = 5; bank <= 8; bank++)
					acp_set_swam_bank_state(adata->acp_mmio,
								bank, fawse);
			}
		}
	}

	/*
	 * Disabwe ACP iwq, when the cuwwent stweam is being cwosed and
	 * anothew stweam is awso not active.
	 */
	if (!adata->pway_i2ssp_stweam && !adata->captuwe_i2ssp_stweam &&
	    !adata->pway_i2sbt_stweam && !adata->captuwe_i2sbt_stweam &&
	    !adata->pway_i2s_micsp_stweam)
		acp_weg_wwite(0, adata->acp_mmio, mmACP_EXTEWNAW_INTW_ENB);
	kfwee(wtd);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew acp_asoc_pwatfowm = {
	.name		= DWV_NAME,
	.open		= acp_dma_open,
	.cwose		= acp_dma_cwose,
	.hw_pawams	= acp_dma_hw_pawams,
	.twiggew	= acp_dma_twiggew,
	.pointew	= acp_dma_pointew,
	.deway		= acp_dma_deway,
	.pwepawe	= acp_dma_pwepawe,
	.pcm_constwuct	= acp_dma_new,
};

static int acp_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	int status, iwq;
	stwuct audio_dwv_data *audio_dwv_data;
	const u32 *pdata = pdev->dev.pwatfowm_data;

	if (!pdata) {
		dev_eww(&pdev->dev, "Missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	audio_dwv_data = devm_kzawwoc(&pdev->dev, sizeof(stwuct audio_dwv_data),
				      GFP_KEWNEW);
	if (!audio_dwv_data)
		wetuwn -ENOMEM;

	audio_dwv_data->acp_mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(audio_dwv_data->acp_mmio))
		wetuwn PTW_EWW(audio_dwv_data->acp_mmio);

	/*
	 * The fowwowing membews gets popuwated in device 'open'
	 * function. Tiww then intewwupts awe disabwed in 'acp_init'
	 * and device doesn't genewate any intewwupts.
	 */

	audio_dwv_data->pway_i2ssp_stweam = NUWW;
	audio_dwv_data->captuwe_i2ssp_stweam = NUWW;
	audio_dwv_data->pway_i2sbt_stweam = NUWW;
	audio_dwv_data->captuwe_i2sbt_stweam = NUWW;
	audio_dwv_data->pway_i2s_micsp_stweam = NUWW;

	audio_dwv_data->asic_type =  *pdata;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENODEV;

	status = devm_wequest_iwq(&pdev->dev, iwq, dma_iwq_handwew,
				  0, "ACP_IWQ", &pdev->dev);
	if (status) {
		dev_eww(&pdev->dev, "ACP IWQ wequest faiwed\n");
		wetuwn status;
	}

	dev_set_dwvdata(&pdev->dev, audio_dwv_data);

	/* Initiawize the ACP */
	status = acp_init(audio_dwv_data->acp_mmio, audio_dwv_data->asic_type);
	if (status) {
		dev_eww(&pdev->dev, "ACP Init faiwed status:%d\n", status);
		wetuwn status;
	}

	status = devm_snd_soc_wegistew_component(&pdev->dev,
						 &acp_asoc_pwatfowm, NUWW, 0);
	if (status != 0) {
		dev_eww(&pdev->dev, "Faiw to wegistew AWSA pwatfowm device\n");
		wetuwn status;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 10000);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn status;
}

static void acp_audio_wemove(stwuct pwatfowm_device *pdev)
{
	int status;
	stwuct audio_dwv_data *adata = dev_get_dwvdata(&pdev->dev);

	status = acp_deinit(adata->acp_mmio);
	if (status)
		dev_eww(&pdev->dev, "ACP Deinit faiwed status:%d\n", status);
	pm_wuntime_disabwe(&pdev->dev);
}

static int acp_pcm_wesume(stwuct device *dev)
{
	u16 bank;
	int status;
	stwuct audio_substweam_data *wtd;
	stwuct audio_dwv_data *adata = dev_get_dwvdata(dev);

	status = acp_init(adata->acp_mmio, adata->asic_type);
	if (status) {
		dev_eww(dev, "ACP Init faiwed status:%d\n", status);
		wetuwn status;
	}

	if (adata->pway_i2ssp_stweam && adata->pway_i2ssp_stweam->wuntime) {
		/*
		 * Fow Stoney, Memowy gating is disabwed,i.e SWAM Banks
		 * won't be tuwned off. The defauwt state fow SWAM banks is ON.
		 * Setting SWAM bank state code skipped fow STONEY pwatfowm.
		 */
		if (adata->asic_type != CHIP_STONEY) {
			fow (bank = 1; bank <= 4; bank++)
				acp_set_swam_bank_state(adata->acp_mmio, bank,
							twue);
		}
		wtd = adata->pway_i2ssp_stweam->wuntime->pwivate_data;
		config_acp_dma(adata->acp_mmio, wtd, adata->asic_type);
	}
	if (adata->captuwe_i2ssp_stweam &&
	    adata->captuwe_i2ssp_stweam->wuntime) {
		if (adata->asic_type != CHIP_STONEY) {
			fow (bank = 5; bank <= 8; bank++)
				acp_set_swam_bank_state(adata->acp_mmio, bank,
							twue);
		}
		wtd =  adata->captuwe_i2ssp_stweam->wuntime->pwivate_data;
		config_acp_dma(adata->acp_mmio, wtd, adata->asic_type);
	}
	if (adata->asic_type != CHIP_CAWWIZO) {
		if (adata->pway_i2s_micsp_stweam &&
		    adata->pway_i2s_micsp_stweam->wuntime) {
			wtd = adata->pway_i2s_micsp_stweam->wuntime->pwivate_data;
			config_acp_dma(adata->acp_mmio, wtd, adata->asic_type);
		}
		if (adata->pway_i2sbt_stweam &&
		    adata->pway_i2sbt_stweam->wuntime) {
			wtd = adata->pway_i2sbt_stweam->wuntime->pwivate_data;
			config_acp_dma(adata->acp_mmio, wtd, adata->asic_type);
		}
		if (adata->captuwe_i2sbt_stweam &&
		    adata->captuwe_i2sbt_stweam->wuntime) {
			wtd = adata->captuwe_i2sbt_stweam->wuntime->pwivate_data;
			config_acp_dma(adata->acp_mmio, wtd, adata->asic_type);
		}
	}
	acp_weg_wwite(1, adata->acp_mmio, mmACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static int acp_pcm_wuntime_suspend(stwuct device *dev)
{
	int status;
	stwuct audio_dwv_data *adata = dev_get_dwvdata(dev);

	status = acp_deinit(adata->acp_mmio);
	if (status)
		dev_eww(dev, "ACP Deinit faiwed status:%d\n", status);
	acp_weg_wwite(0, adata->acp_mmio, mmACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static int acp_pcm_wuntime_wesume(stwuct device *dev)
{
	int status;
	stwuct audio_dwv_data *adata = dev_get_dwvdata(dev);

	status = acp_init(adata->acp_mmio, adata->asic_type);
	if (status) {
		dev_eww(dev, "ACP Init faiwed status:%d\n", status);
		wetuwn status;
	}
	acp_weg_wwite(1, adata->acp_mmio, mmACP_EXTEWNAW_INTW_ENB);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp_pm_ops = {
	.wesume = acp_pcm_wesume,
	.wuntime_suspend = acp_pcm_wuntime_suspend,
	.wuntime_wesume = acp_pcm_wuntime_wesume,
};

static stwuct pwatfowm_dwivew acp_dma_dwivew = {
	.pwobe = acp_audio_pwobe,
	.wemove_new = acp_audio_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.pm = &acp_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp_dma_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_AUTHOW("Mawuthi.Bayyavawapu@amd.com");
MODUWE_DESCWIPTION("AMD ACP PCM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:"DWV_NAME);
