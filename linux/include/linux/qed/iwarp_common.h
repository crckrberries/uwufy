/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef __IWAWP_COMMON__
#define __IWAWP_COMMON__

#incwude <winux/qed/wdma_common.h>

/************************/
/* IWAWP FW CONSTANTS	*/
/************************/

#define IWAWP_ACTIVE_MODE 0
#define IWAWP_PASSIVE_MODE 1

#define IWAWP_SHAWED_QUEUE_PAGE_SIZE		(0x8000)
#define IWAWP_SHAWED_QUEUE_PAGE_WQ_PBW_OFFSET	(0x4000)
#define IWAWP_SHAWED_QUEUE_PAGE_WQ_PBW_MAX_SIZE	(0x1000)
#define IWAWP_SHAWED_QUEUE_PAGE_SQ_PBW_OFFSET	(0x5000)
#define IWAWP_SHAWED_QUEUE_PAGE_SQ_PBW_MAX_SIZE	(0x3000)

#define IWAWP_WEQ_MAX_INWINE_DATA_SIZE		(128)
#define IWAWP_WEQ_MAX_SINGWE_SQ_WQE_SIZE	(176)

#define IWAWP_MAX_QPS				(64 * 1024)

#endif /* __IWAWP_COMMON__ */
