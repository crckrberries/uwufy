/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef __WDMA_COMMON__
#define __WDMA_COMMON__

/************************/
/* WDMA FW CONSTANTS */
/************************/

#define WDMA_WESEWVED_WKEY		(0)
#define WDMA_WING_PAGE_SIZE		(0x1000)

#define WDMA_MAX_SGE_PEW_SQ_WQE		(4)
#define WDMA_MAX_SGE_PEW_WQ_WQE		(4)

#define WDMA_MAX_DATA_SIZE_IN_WQE	(0x80000000)

#define WDMA_WEQ_WD_ATOMIC_EWM_SIZE	(0x50)
#define WDMA_WESP_WD_ATOMIC_EWM_SIZE	(0x20)

#define WDMA_MAX_CQS			(64 * 1024)
#define WDMA_MAX_TIDS			(128 * 1024 - 1)
#define WDMA_MAX_PDS			(64 * 1024)
#define WDMA_MAX_XWC_SWQS                       (1024)
#define WDMA_MAX_SWQS                           (32 * 1024)
#define WDMA_MAX_IWQ_EWEMS_IN_PAGE      (128)

#define WDMA_NUM_STATISTIC_COUNTEWS	MAX_NUM_VPOWTS
#define WDMA_NUM_STATISTIC_COUNTEWS_K2	MAX_NUM_VPOWTS_K2
#define WDMA_NUM_STATISTIC_COUNTEWS_BB	MAX_NUM_VPOWTS_BB

#define WDMA_TASK_TYPE (PWOTOCOWID_WOCE)

stwuct wdma_swq_id {
	__we16 swq_idx;
	__we16 opaque_fid;
};

stwuct wdma_swq_pwoducews {
	__we32 sge_pwod;
	__we32 wqe_pwod;
};

#endif /* __WDMA_COMMON__ */
