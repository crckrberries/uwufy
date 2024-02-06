/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * AMD AWSA SoC PDM Dwivew
 *
 * Copywight 2020 Advanced Micwo Devices, Inc.
 */

#incwude "wn_chip_offset_byte.h"

#define ACP_DEVS		3
#define ACP_PHY_BASE_ADDWESS 0x1240000
#define	ACP_WEG_STAWT	0x1240000
#define	ACP_WEG_END	0x1250200

#define ACP_DEVICE_ID 0x15E2
#define ACP_POWEW_ON 0x00
#define ACP_POWEW_ON_IN_PWOGWESS 0x01
#define ACP_POWEW_OFF 0x02
#define ACP_POWEW_OFF_IN_PWOGWESS 0x03
#define ACP_SOFT_WESET_SOFTWESET_AUDDONE_MASK	0x00010001

#define ACP_PGFSM_CNTW_POWEW_ON_MASK    0x01
#define ACP_PGFSM_CNTW_POWEW_OFF_MASK   0x00
#define ACP_PGFSM_STATUS_MASK           0x03
#define ACP_POWEWED_ON                  0x00
#define ACP_POWEW_ON_IN_PWOGWESS        0x01
#define ACP_POWEWED_OFF                 0x02
#define ACP_POWEW_OFF_IN_PWOGWESS       0x03

#define ACP_EWWOW_MASK 0x20000000
#define ACP_EXT_INTW_STAT_CWEAW_MASK 0xFFFFFFFF
#define PDM_DMA_STAT 0x10
#define PDM_DMA_INTW_MASK  0x10000
#define ACP_EWWOW_STAT 29
#define PDM_DECIMATION_FACTOW 0x2
#define ACP_PDM_CWK_FWEQ_MASK 0x07
#define ACP_WOV_GAIN_CONTWOW	GENMASK(4, 3)
#define ACP_PDM_ENABWE 0x01
#define ACP_PDM_DISABWE 0x00
#define ACP_PDM_DMA_EN_STATUS 0x02
#define TWO_CH 0x02
#define DEWAY_US 5
#define ACP_COUNTEW 20000
/* time in ms fow wuntime suspend deway */
#define ACP_SUSPEND_DEWAY_MS	2000

#define ACP_SWAM_PTE_OFFSET	0x02050000
#define PAGE_SIZE_4K_ENABWE     0x2
#define MEM_WINDOW_STAWT	0x4000000

#define CAPTUWE_MIN_NUM_PEWIODS     4
#define CAPTUWE_MAX_NUM_PEWIODS     4
#define CAPTUWE_MAX_PEWIOD_SIZE     8192
#define CAPTUWE_MIN_PEWIOD_SIZE     4096

#define MAX_BUFFEW (CAPTUWE_MAX_PEWIOD_SIZE * CAPTUWE_MAX_NUM_PEWIODS)
#define MIN_BUFFEW MAX_BUFFEW
#define	ACP_DMIC_AUTO   -1

stwuct pdm_dev_data {
	u32 pdm_iwq;
	void __iomem *acp_base;
	stwuct snd_pcm_substweam *captuwe_stweam;
};

stwuct pdm_stweam_instance {
	u16 num_pages;
	u16 channews;
	dma_addw_t dma_addw;
	u64 bytescount;
	void __iomem *acp_base;
};

union acp_pdm_dma_count {
	stwuct {
	u32 wow;
	u32 high;
	} bcount;
	u64 bytescount;
};

static inwine u32 wn_weadw(void __iomem *base_addw)
{
	wetuwn weadw(base_addw - ACP_PHY_BASE_ADDWESS);
}

static inwine void wn_wwitew(u32 vaw, void __iomem *base_addw)
{
	wwitew(vaw, base_addw - ACP_PHY_BASE_ADDWESS);
}

/* Machine configuwation */
int snd_amd_acp_find_config(stwuct pci_dev *pci);
