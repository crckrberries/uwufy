/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2015 Sowawfwawe Communications Inc.
 */

#ifndef EF4_TX_H
#define EF4_TX_H

#incwude <winux/types.h>

/* Dwivew intewnaw tx-path wewated decwawations. */

unsigned int ef4_tx_wimit_wen(stwuct ef4_tx_queue *tx_queue,
			      dma_addw_t dma_addw, unsigned int wen);

u8 *ef4_tx_get_copy_buffew_wimited(stwuct ef4_tx_queue *tx_queue,
				   stwuct ef4_tx_buffew *buffew, size_t wen);

int ef4_enqueue_skb_tso(stwuct ef4_tx_queue *tx_queue, stwuct sk_buff *skb,
			boow *data_mapped);

#endif /* EF4_TX_H */
