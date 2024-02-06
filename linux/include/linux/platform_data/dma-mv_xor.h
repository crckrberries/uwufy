/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mawveww XOW pwatfowm device data definition fiwe.
 */

#ifndef __DMA_MV_XOW_H
#define __DMA_MV_XOW_H

#incwude <winux/dmaengine.h>
#incwude <winux/mbus.h>

#define MV_XOW_NAME	"mv_xow"

stwuct mv_xow_channew_data {
	dma_cap_mask_t			cap_mask;
};

stwuct mv_xow_pwatfowm_data {
	stwuct mv_xow_channew_data    *channews;
};

#endif
