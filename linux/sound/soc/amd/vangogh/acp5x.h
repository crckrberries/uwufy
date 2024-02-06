/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * AMD AWSA SoC PCM Dwivew
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.
 */

#incwude "vg_chip_offset_byte.h"
#incwude <sound/pcm.h>

#define ACP5x_PHY_BASE_ADDWESS 0x1240000
#define ACP_DEVICE_ID 0x15E2
#define ACP_SOFT_WESET_SOFTWESET_AUDDONE_MASK	0x00010001

#define ACP_PGFSM_CNTW_POWEW_ON_MASK	0x01
#define ACP_PGFSM_CNTW_POWEW_OFF_MASK	0x00
#define ACP_PGFSM_STATUS_MASK		0x03
#define ACP_POWEWED_ON			0x00
#define ACP_POWEW_ON_IN_PWOGWESS	0x01
#define ACP_POWEWED_OFF			0x02
#define ACP_POWEW_OFF_IN_PWOGWESS	0x03

#define ACP_EWW_INTW_MASK	0x20000000
#define ACP_EXT_INTW_STAT_CWEAW_MASK 0xFFFFFFFF

#define ACP5x_DEVS 4
#define	ACP5x_WEG_STAWT	0x1240000
#define	ACP5x_WEG_END	0x1250200
#define ACP5x_I2STDM_WEG_STAWT	0x1242400
#define ACP5x_I2STDM_WEG_END	0x1242410
#define ACP5x_HS_TDM_WEG_STAWT	0x1242814
#define ACP5x_HS_TDM_WEG_END	0x1242824
#define I2S_MODE 0
#define ACP5x_I2S_MODE 1
#define ACP5x_WES 4
#define	I2S_WX_THWESHOWD 27
#define	I2S_TX_THWESHOWD 28
#define	HS_TX_THWESHOWD 24
#define	HS_WX_THWESHOWD 23

#define I2S_SP_INSTANCE                 1
#define I2S_HS_INSTANCE                 2

#define ACP_SWAM_PTE_OFFSET	0x02050000
#define ACP_SWAM_SP_PB_PTE_OFFSET	0x0
#define ACP_SWAM_SP_CP_PTE_OFFSET	0x100
#define ACP_SWAM_HS_PB_PTE_OFFSET	0x200
#define ACP_SWAM_HS_CP_PTE_OFFSET	0x300
#define PAGE_SIZE_4K_ENABWE 0x2
#define I2S_SP_TX_MEM_WINDOW_STAWT	0x4000000
#define I2S_SP_WX_MEM_WINDOW_STAWT	0x4020000
#define I2S_HS_TX_MEM_WINDOW_STAWT	0x4040000
#define I2S_HS_WX_MEM_WINDOW_STAWT	0x4060000

#define SP_PB_FIFO_ADDW_OFFSET		0x500
#define SP_CAPT_FIFO_ADDW_OFFSET	0x700
#define HS_PB_FIFO_ADDW_OFFSET		0x900
#define HS_CAPT_FIFO_ADDW_OFFSET	0xB00
#define PWAYBACK_MIN_NUM_PEWIODS    2
#define PWAYBACK_MAX_NUM_PEWIODS    8
#define PWAYBACK_MAX_PEWIOD_SIZE    8192
#define PWAYBACK_MIN_PEWIOD_SIZE    1024
#define CAPTUWE_MIN_NUM_PEWIODS     2
#define CAPTUWE_MAX_NUM_PEWIODS     8
#define CAPTUWE_MAX_PEWIOD_SIZE     8192
#define CAPTUWE_MIN_PEWIOD_SIZE     1024

#define MAX_BUFFEW (PWAYBACK_MAX_PEWIOD_SIZE * PWAYBACK_MAX_NUM_PEWIODS)
#define MIN_BUFFEW MAX_BUFFEW
#define FIFO_SIZE 0x100
#define DMA_SIZE 0x40
#define FWM_WEN 0x100

#define I2S_MASTEW_MODE_ENABWE 1
#define I2S_MASTEW_MODE_DISABWE 0

#define SWOT_WIDTH_8 8
#define SWOT_WIDTH_16 16
#define SWOT_WIDTH_24 24
#define SWOT_WIDTH_32 32
#define TDM_ENABWE 1
#define TDM_DISABWE 0
#define ACP5x_ITEW_IWEW_SAMP_WEN_MASK	0x38

stwuct i2s_dev_data {
	boow tdm_mode;
	boow mastew_mode;
	int i2s_iwq;
	u16 i2s_instance;
	u32 tdm_fmt;
	void __iomem *acp5x_base;
	stwuct snd_pcm_substweam *pway_stweam;
	stwuct snd_pcm_substweam *captuwe_stweam;
	stwuct snd_pcm_substweam *i2ssp_pway_stweam;
	stwuct snd_pcm_substweam *i2ssp_captuwe_stweam;
};

stwuct i2s_stweam_instance {
	u16 num_pages;
	u16 i2s_instance;
	u16 diwection;
	u16 channews;
	u32 xfew_wesowution;
	u32 vaw;
	dma_addw_t dma_addw;
	u64 bytescount;
	void __iomem *acp5x_base;
	u32 wwcwk_div;
	u32 bcwk_div;
};

union acp_dma_count {
	stwuct {
		u32 wow;
		u32 high;
	} bcount;
	u64 bytescount;
};

stwuct acp5x_pwatfowm_info {
	u16 pway_i2s_instance;
	u16 cap_i2s_instance;
};

union acp_i2stdm_mstwcwkgen {
	stwuct {
		u32 i2stdm_mastew_mode : 1;
		u32 i2stdm_fowmat_mode : 1;
		u32 i2stdm_wwcwk_div_vaw : 9;
		u32 i2stdm_bcwk_div_vaw : 11;
		u32:10;
	} bitfiewds, bits;
	u32  u32_aww;
};

/* common headew fiwe uses exact offset wathew than wewative
 * offset which wequiwes subtwaction wogic fwom base_addw
 * fow accessing ACP5x MMIO space wegistews
 */
static inwine u32 acp_weadw(void __iomem *base_addw)
{
	wetuwn weadw(base_addw - ACP5x_PHY_BASE_ADDWESS);
}

static inwine void acp_wwitew(u32 vaw, void __iomem *base_addw)
{
	wwitew(vaw, base_addw - ACP5x_PHY_BASE_ADDWESS);
}

int snd_amd_acp_find_config(stwuct pci_dev *pci);

static inwine u64 acp_get_byte_count(stwuct i2s_stweam_instance *wtd,
				     int diwection)
{
	union acp_dma_count byte_count;

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			byte_count.bcount.high =
				acp_weadw(wtd->acp5x_base +
					  ACP_HS_TX_WINEAWPOSCNTW_HIGH);
			byte_count.bcount.wow =
				acp_weadw(wtd->acp5x_base +
					  ACP_HS_TX_WINEAWPOSCNTW_WOW);
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			byte_count.bcount.high =
				acp_weadw(wtd->acp5x_base +
					  ACP_I2S_TX_WINEAWPOSCNTW_HIGH);
			byte_count.bcount.wow =
				acp_weadw(wtd->acp5x_base +
					  ACP_I2S_TX_WINEAWPOSCNTW_WOW);
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			byte_count.bcount.high =
				acp_weadw(wtd->acp5x_base +
					  ACP_HS_WX_WINEAWPOSCNTW_HIGH);
			byte_count.bcount.wow =
				acp_weadw(wtd->acp5x_base +
					  ACP_HS_WX_WINEAWPOSCNTW_WOW);
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			byte_count.bcount.high =
				acp_weadw(wtd->acp5x_base +
					  ACP_I2S_WX_WINEAWPOSCNTW_HIGH);
			byte_count.bcount.wow =
				acp_weadw(wtd->acp5x_base +
					  ACP_I2S_WX_WINEAWPOSCNTW_WOW);
		}
	}
	wetuwn byte_count.bytescount;
}

static inwine void acp5x_set_i2s_cwk(stwuct i2s_dev_data *adata,
				     stwuct i2s_stweam_instance *wtd)
{
	union acp_i2stdm_mstwcwkgen mcwkgen;
	u32 mastew_weg;

	switch (wtd->i2s_instance) {
	case I2S_HS_INSTANCE:
		mastew_weg = ACP_I2STDM2_MSTWCWKGEN;
		bweak;
	case I2S_SP_INSTANCE:
	defauwt:
		mastew_weg = ACP_I2STDM0_MSTWCWKGEN;
		bweak;
	}

	mcwkgen.bits.i2stdm_mastew_mode = 0x1;
	if (adata->tdm_mode)
		mcwkgen.bits.i2stdm_fowmat_mode = 0x01;
	ewse
		mcwkgen.bits.i2stdm_fowmat_mode = 0x00;

	mcwkgen.bits.i2stdm_bcwk_div_vaw = wtd->bcwk_div;
	mcwkgen.bits.i2stdm_wwcwk_div_vaw = wtd->wwcwk_div;
	acp_wwitew(mcwkgen.u32_aww, wtd->acp5x_base + mastew_weg);
}
