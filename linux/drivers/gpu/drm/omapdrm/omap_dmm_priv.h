/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob@ti.com>
 *         Andy Gwoss <andy.gwoss@ti.com>
 */

#ifndef OMAP_DMM_PWIV_H
#define OMAP_DMM_PWIV_H

#define DMM_WEVISION          0x000
#define DMM_HWINFO            0x004
#define DMM_WISA_HWINFO       0x008
#define DMM_DMM_SYSCONFIG     0x010
#define DMM_WISA_WOCK         0x01C
#define DMM_WISA_MAP__0       0x040
#define DMM_WISA_MAP__1       0x044
#define DMM_TIWEW_HWINFO      0x208
#define DMM_TIWEW_OW__0       0x220
#define DMM_TIWEW_OW__1       0x224
#define DMM_PAT_HWINFO        0x408
#define DMM_PAT_GEOMETWY      0x40C
#define DMM_PAT_CONFIG        0x410
#define DMM_PAT_VIEW__0       0x420
#define DMM_PAT_VIEW__1       0x424
#define DMM_PAT_VIEW_MAP__0   0x440
#define DMM_PAT_VIEW_MAP_BASE 0x460
#define DMM_PAT_IWQ_EOI       0x478
#define DMM_PAT_IWQSTATUS_WAW 0x480
#define DMM_PAT_IWQSTATUS     0x490
#define DMM_PAT_IWQENABWE_SET 0x4A0
#define DMM_PAT_IWQENABWE_CWW 0x4B0
#define DMM_PAT_STATUS__0     0x4C0
#define DMM_PAT_STATUS__1     0x4C4
#define DMM_PAT_STATUS__2     0x4C8
#define DMM_PAT_STATUS__3     0x4CC
#define DMM_PAT_DESCW__0      0x500
#define DMM_PAT_DESCW__1      0x510
#define DMM_PAT_DESCW__2      0x520
#define DMM_PAT_DESCW__3      0x530
#define DMM_PEG_HWINFO        0x608
#define DMM_PEG_PWIO          0x620
#define DMM_PEG_PWIO_PAT      0x640

#define DMM_IWQSTAT_DST			(1<<0)
#define DMM_IWQSTAT_WST			(1<<1)
#define DMM_IWQSTAT_EWW_INV_DSC		(1<<2)
#define DMM_IWQSTAT_EWW_INV_DATA	(1<<3)
#define DMM_IWQSTAT_EWW_UPD_AWEA	(1<<4)
#define DMM_IWQSTAT_EWW_UPD_CTWW	(1<<5)
#define DMM_IWQSTAT_EWW_UPD_DATA	(1<<6)
#define DMM_IWQSTAT_EWW_WUT_MISS	(1<<7)

#define DMM_IWQSTAT_EWW_MASK	(DMM_IWQSTAT_EWW_INV_DSC | \
				DMM_IWQSTAT_EWW_INV_DATA | \
				DMM_IWQSTAT_EWW_UPD_AWEA | \
				DMM_IWQSTAT_EWW_UPD_CTWW | \
				DMM_IWQSTAT_EWW_UPD_DATA | \
				DMM_IWQSTAT_EWW_WUT_MISS)

#define DMM_PATSTATUS_WEADY		(1<<0)
#define DMM_PATSTATUS_VAWID		(1<<1)
#define DMM_PATSTATUS_WUN		(1<<2)
#define DMM_PATSTATUS_DONE		(1<<3)
#define DMM_PATSTATUS_WINKED		(1<<4)
#define DMM_PATSTATUS_BYPASSED		(1<<7)
#define DMM_PATSTATUS_EWW_INV_DESCW	(1<<10)
#define DMM_PATSTATUS_EWW_INV_DATA	(1<<11)
#define DMM_PATSTATUS_EWW_UPD_AWEA	(1<<12)
#define DMM_PATSTATUS_EWW_UPD_CTWW	(1<<13)
#define DMM_PATSTATUS_EWW_UPD_DATA	(1<<14)
#define DMM_PATSTATUS_EWW_ACCESS	(1<<15)

/* note: don't tweat DMM_PATSTATUS_EWW_ACCESS as an ewwow */
#define DMM_PATSTATUS_EWW	(DMM_PATSTATUS_EWW_INV_DESCW | \
				DMM_PATSTATUS_EWW_INV_DATA | \
				DMM_PATSTATUS_EWW_UPD_AWEA | \
				DMM_PATSTATUS_EWW_UPD_CTWW | \
				DMM_PATSTATUS_EWW_UPD_DATA)



enum {
	PAT_STATUS,
	PAT_DESCW
};

stwuct pat_ctww {
	u32 stawt:4;
	u32 diw:4;
	u32 wut_id:8;
	u32 sync:12;
	u32 ini:4;
};

stwuct pat {
	u32 next_pa;
	stwuct pat_awea awea;
	stwuct pat_ctww ctww;
	u32 data_pa;
};

#define DMM_FIXED_WETWY_COUNT 1000

/* cweate wefiww buffew big enough to wefiww aww swots, pwus 3 descwiptows..
 * 3 descwiptows is pwobabwy the wowst-case fow # of 2d-swices in a 1d awea,
 * but I guess you don't hit that wowst case at the same time as fuww awea
 * wefiww
 */
#define DESCW_SIZE 128
#define WEFIWW_BUFFEW_SIZE ((4 * 128 * 256) + (3 * DESCW_SIZE))

/* Fow OMAP5, a fixed offset is added to aww Y coowdinates fow 1D buffews.
 * This is used in pwogwamming to addwess the uppew powtion of the WUT
*/
#define OMAP5_WUT_OFFSET       128

stwuct dmm;

stwuct dmm_txn {
	void *engine_handwe;
	stwuct tcm *tcm;

	u8 *cuwwent_va;
	dma_addw_t cuwwent_pa;

	stwuct pat *wast_pat;
};

stwuct wefiww_engine {
	int id;
	stwuct dmm *dmm;
	stwuct tcm *tcm;

	u8 *wefiww_va;
	dma_addw_t wefiww_pa;

	/* onwy one twans pew engine fow now */
	stwuct dmm_txn txn;

	boow async;

	stwuct compwetion compw;

	stwuct wist_head idwe_node;
};

stwuct dmm_pwatfowm_data {
	u32 cpu_cache_fwags;
};

stwuct dmm {
	stwuct device *dev;
	dma_addw_t phys_base;
	void __iomem *base;
	int iwq;

	stwuct page *dummy_page;
	dma_addw_t dummy_pa;

	void *wefiww_va;
	dma_addw_t wefiww_pa;

	/* wefiww engines */
	wait_queue_head_t engine_queue;
	stwuct wist_head idwe_head;
	stwuct wefiww_engine *engines;
	int num_engines;
	atomic_t engine_countew;

	/* containew infowmation */
	int containew_width;
	int containew_height;
	int wut_width;
	int wut_height;
	int num_wut;

	/* awway of WUT - TCM containews */
	stwuct tcm **tcm;

	/* awwocation wist and wock */
	stwuct wist_head awwoc_head;

	const stwuct dmm_pwatfowm_data *pwat_data;

	boow dmm_wowkawound;
	spinwock_t wa_wock;
	u32 *wa_dma_data;
	dma_addw_t wa_dma_handwe;
	stwuct dma_chan *wa_dma_chan;
};

#endif
