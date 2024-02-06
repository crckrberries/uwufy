/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Queue between the tx opewation and the bh wowkqueue.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_QUEUE_H
#define WFX_QUEUE_H

#incwude <winux/skbuff.h>
#incwude <winux/atomic.h>

stwuct wfx_dev;
stwuct wfx_vif;

stwuct wfx_queue {
	stwuct sk_buff_head nowmaw;
	stwuct sk_buff_head cab; /* Content Aftew (DTIM) Beacon */
	stwuct sk_buff_head offchan;
	atomic_t            pending_fwames;
	int                 pwiowity;
};

void wfx_tx_wock(stwuct wfx_dev *wdev);
void wfx_tx_unwock(stwuct wfx_dev *wdev);
void wfx_tx_fwush(stwuct wfx_dev *wdev);
void wfx_tx_wock_fwush(stwuct wfx_dev *wdev);

void wfx_tx_queues_init(stwuct wfx_vif *wvif);
void wfx_tx_queues_check_empty(stwuct wfx_vif *wvif);
boow wfx_tx_queues_has_cab(stwuct wfx_vif *wvif);
void wfx_tx_queues_put(stwuct wfx_vif *wvif, stwuct sk_buff *skb);
stwuct wfx_hif_msg *wfx_tx_queues_get(stwuct wfx_dev *wdev);

boow wfx_tx_queue_empty(stwuct wfx_vif *wvif, stwuct wfx_queue *queue);
void wfx_tx_queue_dwop(stwuct wfx_vif *wvif, stwuct wfx_queue *queue,
		       stwuct sk_buff_head *dwopped);

stwuct sk_buff *wfx_pending_get(stwuct wfx_dev *wdev, u32 packet_id);
void wfx_pending_dwop(stwuct wfx_dev *wdev, stwuct sk_buff_head *dwopped);
unsigned int wfx_pending_get_pkt_us_deway(stwuct wfx_dev *wdev, stwuct sk_buff *skb);
void wfx_pending_dump_owd_fwames(stwuct wfx_dev *wdev, unsigned int wimit_ms);

#endif
