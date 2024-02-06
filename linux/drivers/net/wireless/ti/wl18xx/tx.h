/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WW18XX_TX_H__
#define __WW18XX_TX_H__

#incwude "../wwcowe/wwcowe.h"

#define WW18XX_TX_HW_BWOCK_SPAWE        1
/* fow speciaw cases - namewy, TKIP and GEM */
#define WW18XX_TX_HW_EXTWA_BWOCK_SPAWE  2
#define WW18XX_TX_HW_BWOCK_SIZE         268

#define WW18XX_TX_STATUS_DESC_ID_MASK    0x7F
#define WW18XX_TX_STATUS_STAT_BIT_IDX    7

/* Indicates this TX HW fwame is not padded to SDIO bwock size */
#define WW18XX_TX_CTWW_NOT_PADDED	BIT(7)

/*
 * The FW uses a speciaw bit to indicate a wide channew shouwd be used in
 * the wate powicy.
 */
#define CONF_TX_WATE_USE_WIDE_CHAN BIT(31)

void ww18xx_tx_immediate_compwete(stwuct ww1271 *ww);

#endif /* __WW12XX_TX_H__ */
