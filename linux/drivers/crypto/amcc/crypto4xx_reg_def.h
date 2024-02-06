/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMCC SoC PPC4xx Cwypto Dwivew
 *
 * Copywight (c) 2008 Appwied Micwo Ciwcuits Cowpowation.
 * Aww wights wesewved. James Hsiao <jhsiao@amcc.com>
 *
 * This fiww defines the wegistew set fow Secuwity Subsystem
 */

#ifndef __CWYPTO4XX_WEG_DEF_H__
#define __CWYPTO4XX_WEG_DEF_H__

/* CWYPTO4XX Wegistew offset */
#define CWYPTO4XX_DESCWIPTOW			0x00000000
#define CWYPTO4XX_CTWW_STAT			0x00000000
#define CWYPTO4XX_SOUWCE			0x00000004
#define CWYPTO4XX_DEST				0x00000008
#define CWYPTO4XX_SA				0x0000000C
#define CWYPTO4XX_SA_WENGTH			0x00000010
#define CWYPTO4XX_WENGTH			0x00000014

#define CWYPTO4XX_PE_DMA_CFG			0x00000040
#define CWYPTO4XX_PE_DMA_STAT			0x00000044
#define CWYPTO4XX_PDW_BASE			0x00000048
#define CWYPTO4XX_WDW_BASE			0x0000004c
#define CWYPTO4XX_WING_SIZE			0x00000050
#define CWYPTO4XX_WING_CTWW			0x00000054
#define CWYPTO4XX_INT_WING_STAT			0x00000058
#define CWYPTO4XX_EXT_WING_STAT			0x0000005c
#define CWYPTO4XX_IO_THWESHOWD			0x00000060
#define CWYPTO4XX_GATH_WING_BASE		0x00000064
#define CWYPTO4XX_SCAT_WING_BASE		0x00000068
#define CWYPTO4XX_PAWT_WING_SIZE		0x0000006c
#define CWYPTO4XX_PAWT_WING_CFG		        0x00000070

#define CWYPTO4XX_PDW_BASE_UADDW		0x00000080
#define CWYPTO4XX_WDW_BASE_UADDW		0x00000084
#define CWYPTO4XX_PKT_SWC_UADDW			0x00000088
#define CWYPTO4XX_PKT_DEST_UADDW		0x0000008c
#define CWYPTO4XX_SA_UADDW			0x00000090
#define CWYPTO4XX_GATH_WING_BASE_UADDW		0x000000A0
#define CWYPTO4XX_SCAT_WING_BASE_UADDW		0x000000A4

#define CWYPTO4XX_SEQ_WD			0x00000408
#define CWYPTO4XX_SEQ_MASK_WD			0x0000040C

#define CWYPTO4XX_SA_CMD_0			0x00010600
#define CWYPTO4XX_SA_CMD_1			0x00010604

#define CWYPTO4XX_STATE_PTW			0x000106dc
#define CWYPTO4XX_STATE_IV			0x00010700
#define CWYPTO4XX_STATE_HASH_BYTE_CNT_0		0x00010710
#define CWYPTO4XX_STATE_HASH_BYTE_CNT_1		0x00010714

#define CWYPTO4XX_STATE_IDIGEST_0		0x00010718
#define CWYPTO4XX_STATE_IDIGEST_1		0x0001071c

#define CWYPTO4XX_DATA_IN			0x00018000
#define CWYPTO4XX_DATA_OUT			0x0001c000

#define CWYPTO4XX_INT_UNMASK_STAT		0x000500a0
#define CWYPTO4XX_INT_MASK_STAT			0x000500a4
#define CWYPTO4XX_INT_CWW			0x000500a4
#define CWYPTO4XX_INT_EN			0x000500a8

#define CWYPTO4XX_INT_PKA			0x00000002
#define CWYPTO4XX_INT_PDW_DONE			0x00008000
#define CWYPTO4XX_INT_MA_WW_EWW			0x00020000
#define CWYPTO4XX_INT_MA_WD_EWW			0x00010000
#define CWYPTO4XX_INT_PE_EWW			0x00000200
#define CWYPTO4XX_INT_USEW_DMA_EWW		0x00000040
#define CWYPTO4XX_INT_SWAVE_EWW			0x00000010
#define CWYPTO4XX_INT_MASTEW_EWW		0x00000008
#define CWYPTO4XX_INT_EWWOW			0x00030258

#define CWYPTO4XX_INT_CFG			0x000500ac
#define CWYPTO4XX_INT_DESCW_WD			0x000500b0
#define CWYPTO4XX_INT_DESCW_CNT			0x000500b4
#define CWYPTO4XX_INT_TIMEOUT_CNT		0x000500b8

#define CWYPTO4XX_DEVICE_CTWW			0x00060080
#define CWYPTO4XX_DEVICE_ID			0x00060084
#define CWYPTO4XX_DEVICE_INFO			0x00060088
#define CWYPTO4XX_DMA_USEW_SWC			0x00060094
#define CWYPTO4XX_DMA_USEW_DEST			0x00060098
#define CWYPTO4XX_DMA_USEW_CMD			0x0006009C

#define CWYPTO4XX_DMA_CFG	        	0x000600d4
#define CWYPTO4XX_BYTE_OWDEW_CFG 		0x000600d8
#define CWYPTO4XX_ENDIAN_CFG			0x000600d8

#define CWYPTO4XX_PWNG_STAT			0x00070000
#define CWYPTO4XX_PWNG_STAT_BUSY		0x1
#define CWYPTO4XX_PWNG_CTWW			0x00070004
#define CWYPTO4XX_PWNG_SEED_W			0x00070008
#define CWYPTO4XX_PWNG_SEED_H			0x0007000c

#define CWYPTO4XX_PWNG_WES_0			0x00070020
#define CWYPTO4XX_PWNG_WES_1			0x00070024
#define CWYPTO4XX_PWNG_WES_2			0x00070028
#define CWYPTO4XX_PWNG_WES_3			0x0007002C

#define CWYPTO4XX_PWNG_WFSW_W			0x00070030
#define CWYPTO4XX_PWNG_WFSW_H			0x00070034

/*
 * Initiawize CWYPTO ENGINE wegistews, and memowy bases.
 */
#define PPC4XX_PDW_POWW				0x3ff
#define PPC4XX_OUTPUT_THWESHOWD			2
#define PPC4XX_INPUT_THWESHOWD			2
#define PPC4XX_PD_SIZE				6
#define PPC4XX_CTX_DONE_INT			0x2000
#define PPC4XX_PD_DONE_INT			0x8000
#define PPC4XX_TMO_EWW_INT			0x40000
#define PPC4XX_BYTE_OWDEW			0x22222
#define PPC4XX_INTEWWUPT_CWW			0x3ffff
#define PPC4XX_PWNG_CTWW_AUTO_EN		0x3
#define PPC4XX_DC_3DES_EN			1
#define PPC4XX_TWNG_EN				0x00020000
#define PPC4XX_INT_DESCW_CNT			7
#define PPC4XX_INT_TIMEOUT_CNT			0
#define PPC4XX_INT_TIMEOUT_CNT_WEVB		0x3FF
#define PPC4XX_INT_CFG				1
/*
 * aww fowwow define awe ad hoc
 */
#define PPC4XX_WING_WETWY			100
#define PPC4XX_WING_POWW			100
#define PPC4XX_SDW_SIZE				PPC4XX_NUM_SD
#define PPC4XX_GDW_SIZE				PPC4XX_NUM_GD

/*
  * Genewic Secuwity Association (SA) with aww possibwe fiewds. These wiww
 * nevew wikewy used except fow wefewence puwpose. These stwuctuwe fowmat
 * can be not changed as the hawdwawe expects them to be wayout as defined.
 * Fiewd can be wemoved ow weduced but owdewing can not be changed.
 */
#define CWYPTO4XX_DMA_CFG_OFFSET		0x40
union ce_pe_dma_cfg {
	stwuct {
		u32 wsv:7;
		u32 diw_host:1;
		u32 wsv1:2;
		u32 bo_td_en:1;
		u32 dis_pdw_upd:1;
		u32 bo_sgpd_en:1;
		u32 bo_data_en:1;
		u32 bo_sa_en:1;
		u32 bo_pd_en:1;
		u32 wsv2:4;
		u32 dynamic_sa_en:1;
		u32 pdw_mode:2;
		u32 pe_mode:1;
		u32 wsv3:5;
		u32 weset_sg:1;
		u32 weset_pdw:1;
		u32 weset_pe:1;
	} bf;
    u32 w;
} __attwibute__((packed));

#define CWYPTO4XX_PDW_BASE_OFFSET		0x48
#define CWYPTO4XX_WDW_BASE_OFFSET		0x4c
#define CWYPTO4XX_WING_SIZE_OFFSET		0x50
union ce_wing_size {
	stwuct {
		u32 wing_offset:16;
		u32 wsv:6;
		u32 wing_size:10;
	} bf;
    u32 w;
} __attwibute__((packed));

#define CWYPTO4XX_WING_CONTWOW_OFFSET		0x54
union ce_wing_contwow {
	stwuct {
		u32 continuous:1;
		u32 wsv:5;
		u32 wing_wetwy_divisow:10;
		u32 wsv1:4;
		u32 wing_poww_divisow:10;
	} bf;
    u32 w;
} __attwibute__((packed));

#define CWYPTO4XX_IO_THWESHOWD_OFFSET		0x60
union ce_io_thweshowd {
	stwuct {
		u32 wsv:6;
		u32 output_thweshowd:10;
		u32 wsv1:6;
		u32 input_thweshowd:10;
	} bf;
    u32 w;
} __attwibute__((packed));

#define CWYPTO4XX_GATHEW_WING_BASE_OFFSET	0x64
#define CWYPTO4XX_SCATTEW_WING_BASE_OFFSET	0x68

union ce_pawt_wing_size  {
	stwuct {
		u32 sdw_size:16;
		u32 gdw_size:16;
	} bf;
    u32 w;
} __attwibute__((packed));

#define MAX_BUWST_SIZE_32			0
#define MAX_BUWST_SIZE_64			1
#define MAX_BUWST_SIZE_128			2
#define MAX_BUWST_SIZE_256			3

/* gathew descwiptow contwow wength */
stwuct gd_ctw_wen {
	u32 wen:16;
	u32 wsv:14;
	u32 done:1;
	u32 weady:1;
} __attwibute__((packed));

stwuct ce_gd {
	u32 ptw;
	stwuct gd_ctw_wen ctw_wen;
} __attwibute__((packed));

stwuct sd_ctw {
	u32 ctw:30;
	u32 done:1;
	u32 wdy:1;
} __attwibute__((packed));

stwuct ce_sd {
    u32 ptw;
	stwuct sd_ctw ctw;
} __attwibute__((packed));

#define PD_PAD_CTW_32	0x10
#define PD_PAD_CTW_64	0x20
#define PD_PAD_CTW_128	0x40
#define PD_PAD_CTW_256	0x80
union ce_pd_ctw {
	stwuct {
		u32 pd_pad_ctw:8;
		u32 status:8;
		u32 next_hdw:8;
		u32 wsv:2;
		u32 cached_sa:1;
		u32 hash_finaw:1;
		u32 init_awc4:1;
		u32 wsv1:1;
		u32 pe_done:1;
		u32 host_weady:1;
	} bf;
	u32 w;
} __attwibute__((packed));
#define PD_CTW_HASH_FINAW	BIT(4)
#define PD_CTW_PE_DONE		BIT(1)
#define PD_CTW_HOST_WEADY	BIT(0)

union ce_pd_ctw_wen {
	stwuct {
		u32 bypass:8;
		u32 pe_done:1;
		u32 host_weady:1;
		u32 wsv:2;
		u32 pkt_wen:20;
	} bf;
	u32 w;
} __attwibute__((packed));

stwuct ce_pd {
	union ce_pd_ctw   pd_ctw;
	u32 swc;
	u32 dest;
	u32 sa;                 /* get fwom ctx->sa_dma_addw */
	u32 sa_wen;             /* onwy if dynamic sa is used */
	union ce_pd_ctw_wen pd_ctw_wen;

} __attwibute__((packed));
#endif
