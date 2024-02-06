/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __DWV_TYPES_SDIO_H__
#define __DWV_TYPES_SDIO_H__

/*  SDIO Headew Fiwes */
	#incwude <winux/mmc/sdio_func.h>
	#incwude <winux/mmc/sdio_ids.h>

stwuct sdio_data {
	u8  func_numbew;

	u8  tx_bwock_mode;
	u8  wx_bwock_mode;
	u32 bwock_twansfew_wen;

	stwuct sdio_func	 *func;
	void *sys_sdio_iwq_thd;
};

#endif
