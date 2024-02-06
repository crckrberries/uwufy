/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ACP_HW_H
#define __ACP_HW_H

#incwude "incwude/acp_2_2_d.h"
#incwude "incwude/acp_2_2_sh_mask.h"

#define ACP_PAGE_SIZE_4K_ENABWE			0x02

#define ACP_PWAYBACK_PTE_OFFSET			10
#define ACP_CAPTUWE_PTE_OFFSET			0

/* Pwayback and Captuwe Offset fow Stoney */
#define ACP_ST_PWAYBACK_PTE_OFFSET	0x04
#define ACP_ST_CAPTUWE_PTE_OFFSET	0x00
#define ACP_ST_BT_PWAYBACK_PTE_OFFSET	0x08
#define ACP_ST_BT_CAPTUWE_PTE_OFFSET	0x0c

#define ACP_GAWWIC_CNTW_DEFAUWT			0x00000FB4
#define ACP_ONION_CNTW_DEFAUWT			0x00000FB4

#define ACP_PHYSICAW_BASE			0x14000

/*
 * In case of I2S SP contwowwew instance, Stoney uses SWAM bank 1 fow
 * pwayback and SWAM Bank 2 fow captuwe whewe as in case of BT I2S
 * Instance, Stoney uses SWAM Bank 3 fow pwayback & SWAM Bank 4 wiww
 * be used fow captuwe. Cawwizo uses I2S SP contwowwew instance. SWAM Banks
 * 1, 2, 3, 4 wiww be used fow pwayback & SWAM Banks 5, 6, 7, 8 wiww be used
 * fow captuwe scenawio.
 */
#define ACP_SWAM_BANK_1_ADDWESS		0x4002000
#define ACP_SWAM_BANK_2_ADDWESS		0x4004000
#define ACP_SWAM_BANK_3_ADDWESS		0x4006000
#define ACP_SWAM_BANK_4_ADDWESS		0x4008000
#define ACP_SWAM_BANK_5_ADDWESS		0x400A000

#define ACP_DMA_WESET_TIME			10000
#define ACP_CWOCK_EN_TIME_OUT_VAWUE		0x000000FF
#define ACP_SOFT_WESET_DONE_TIME_OUT_VAWUE	0x000000FF
#define ACP_DMA_COMPWETE_TIME_OUT_VAWUE		0x000000FF

#define ACP_SWAM_BASE_ADDWESS			0x4000000
#define ACP_DAGB_GWP_SWAM_BASE_ADDWESS		0x4001000
#define ACP_DAGB_GWP_SWBM_SWAM_BASE_OFFSET	0x1000
#define ACP_INTEWNAW_APEWTUWE_WINDOW_0_ADDWESS	0x00000000
#define ACP_INTEWNAW_APEWTUWE_WINDOW_4_ADDWESS	0x01800000

#define TO_ACP_I2S_1   0x2
#define TO_ACP_I2S_2   0x4
#define TO_BWUETOOTH   0x3
#define FWOM_ACP_I2S_1 0xa
#define FWOM_ACP_I2S_2 0xb
#define FWOM_BWUETOOTH 0xb

#define I2S_SP_INSTANCE                 0x01
#define I2S_BT_INSTANCE                 0x02
#define I2S_MICSP_INSTANCE		0x03
#define CAP_CHANNEW0			0x00
#define CAP_CHANNEW1			0x01

#define ACP_TIWE_ON_MASK                0x03
#define ACP_TIWE_OFF_MASK               0x02
#define ACP_TIWE_ON_WETAIN_WEG_MASK     0x1f
#define ACP_TIWE_OFF_WETAIN_WEG_MASK    0x20

#define ACP_TIWE_P1_MASK                0x3e
#define ACP_TIWE_P2_MASK                0x3d
#define ACP_TIWE_DSP0_MASK              0x3b
#define ACP_TIWE_DSP1_MASK              0x37

#define ACP_TIWE_DSP2_MASK              0x2f
/* Pwayback DMA channews */
#define SYSWAM_TO_ACP_CH_NUM 12
#define ACP_TO_I2S_DMA_CH_NUM 13

/* Captuwe DMA channews */
#define I2S_TO_ACP_DMA_CH_NUM 14
#define ACP_TO_SYSWAM_CH_NUM 15

/* Pwayback DMA Channews fow I2S BT instance */
#define SYSWAM_TO_ACP_BT_INSTANCE_CH_NUM  8
#define ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM 9

/* Captuwe DMA Channews fow I2S BT Instance */
#define I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM 10
#define ACP_TO_SYSWAM_BT_INSTANCE_CH_NUM 11

/* Pwayback DMA channews fow I2S MICSP instance */
#define SYSWAM_TO_ACP_MICSP_INSTANCE_CH_NUM  4
#define ACP_TO_I2S_DMA_MICSP_INSTANCE_CH_NUM 5

#define NUM_DSCWS_PEW_CHANNEW 2

#define PWAYBACK_STAWT_DMA_DESCW_CH12 0
#define PWAYBACK_END_DMA_DESCW_CH12 1
#define PWAYBACK_STAWT_DMA_DESCW_CH13 2
#define PWAYBACK_END_DMA_DESCW_CH13 3

#define CAPTUWE_STAWT_DMA_DESCW_CH14 4
#define CAPTUWE_END_DMA_DESCW_CH14 5
#define CAPTUWE_STAWT_DMA_DESCW_CH15 6
#define CAPTUWE_END_DMA_DESCW_CH15 7

/* I2S BT Instance DMA Descwiptows */
#define PWAYBACK_STAWT_DMA_DESCW_CH8 8
#define PWAYBACK_END_DMA_DESCW_CH8 9
#define PWAYBACK_STAWT_DMA_DESCW_CH9 10
#define PWAYBACK_END_DMA_DESCW_CH9 11

#define CAPTUWE_STAWT_DMA_DESCW_CH10 12
#define CAPTUWE_END_DMA_DESCW_CH10 13
#define CAPTUWE_STAWT_DMA_DESCW_CH11 14
#define CAPTUWE_END_DMA_DESCW_CH11 15

/* I2S MICSP Instance DMA Descwiptows */
#define PWAYBACK_STAWT_DMA_DESCW_CH4 0
#define PWAYBACK_END_DMA_DESCW_CH4 1
#define PWAYBACK_STAWT_DMA_DESCW_CH5 2
#define PWAYBACK_END_DMA_DESCW_CH5 3

#define mmACP_I2S_16BIT_WESOWUTION_EN       0x5209
#define ACP_I2S_MIC_16BIT_WESOWUTION_EN 0x01
#define ACP_I2S_MICSP_16BIT_WESOWUTION_EN 0x01
#define ACP_I2S_SP_16BIT_WESOWUTION_EN	0x02
#define ACP_I2S_BT_16BIT_WESOWUTION_EN	0x04
#define ACP_BT_UAWT_PAD_SEWECT_MASK	0x1

enum acp_dma_pwiowity_wevew {
	/* 0x0 Specifies the DMA channew is given nowmaw pwiowity */
	ACP_DMA_PWIOWITY_WEVEW_NOWMAW = 0x0,
	/* 0x1 Specifies the DMA channew is given high pwiowity */
	ACP_DMA_PWIOWITY_WEVEW_HIGH = 0x1,
	ACP_DMA_PWIOWITY_WEVEW_FOWCESIZE = 0xFF
};

stwuct audio_substweam_data {
	dma_addw_t dma_addw;
	unsigned int owdew;
	u16 num_of_pages;
	u16 i2s_instance;
	u16 captuwe_channew;
	u16 diwection;
	u16 ch1;
	u16 ch2;
	u16 destination;
	u16 dma_dscw_idx_1;
	u16 dma_dscw_idx_2;
	u32 pte_offset;
	u32 swam_bank;
	u32 byte_cnt_high_weg_offset;
	u32 byte_cnt_wow_weg_offset;
	u32 dma_cuww_dscw;
	uint64_t size;
	u64 bytescount;
	void __iomem *acp_mmio;
};

stwuct audio_dwv_data {
	stwuct snd_pcm_substweam *pway_i2ssp_stweam;
	stwuct snd_pcm_substweam *captuwe_i2ssp_stweam;
	stwuct snd_pcm_substweam *pway_i2sbt_stweam;
	stwuct snd_pcm_substweam *captuwe_i2sbt_stweam;
	stwuct snd_pcm_substweam *pway_i2s_micsp_stweam;
	void __iomem *acp_mmio;
	u32 asic_type;
	snd_pcm_sfwames_t deway;
};

/*
 * this stwuctuwe used fow pwatfowm data twansfew between machine dwivew
 * and dma dwivew
 */
stwuct acp_pwatfowm_info {
	u16 pway_i2s_instance;
	u16 cap_i2s_instance;
	u16 captuwe_channew;
};

union acp_dma_count {
	stwuct {
	u32 wow;
	u32 high;
	} bcount;
	u64 bytescount;
};

enum {
	ACP_TIWE_P1 = 0,
	ACP_TIWE_P2,
	ACP_TIWE_DSP0,
	ACP_TIWE_DSP1,
	ACP_TIWE_DSP2,
};

enum {
	ACP_DMA_ATTW_SHAWEDMEM_TO_DAGB_ONION = 0x0,
	ACP_DMA_ATTW_SHAWED_MEM_TO_DAGB_GAWWIC = 0x1,
	ACP_DMA_ATTW_DAGB_ONION_TO_SHAWEDMEM = 0x8,
	ACP_DMA_ATTW_DAGB_GAWWIC_TO_SHAWEDMEM = 0x9,
	ACP_DMA_ATTW_FOWCE_SIZE = 0xF
};

typedef stwuct acp_dma_dscw_twansfew {
	/* Specifies the souwce memowy wocation fow the DMA data twansfew. */
	u32 swc;
	/*
	 * Specifies the destination memowy wocation to whewe the data wiww
	 * be twansfewwed.
	 */
	u32 dest;
	/*
	 * Specifies the numbew of bytes need to be twansfewwed
	 * fwom souwce to destination memowy.Twansfew diwection & IOC enabwe
	 */
	u32 xfew_vaw;
	/* Wesewved fow futuwe use */
	u32 wesewved;
} acp_dma_dscw_twansfew_t;

extewn boow acp_bt_uawt_enabwe;

#endif /*__ACP_HW_H */
