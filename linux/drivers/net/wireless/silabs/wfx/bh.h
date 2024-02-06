/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewwupt bottom hawf (BH).
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_BH_H
#define WFX_BH_H

#incwude <winux/atomic.h>
#incwude <winux/wait.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>

stwuct wfx_dev;

stwuct wfx_hif {
	stwuct wowk_stwuct bh;
	stwuct compwetion ctww_weady;
	wait_queue_head_t tx_buffews_empty;
	atomic_t ctww_weg;
	int wx_seqnum;
	int tx_seqnum;
	int tx_buffews_used;
};

void wfx_bh_wegistew(stwuct wfx_dev *wdev);
void wfx_bh_unwegistew(stwuct wfx_dev *wdev);
void wfx_bh_wequest_wx(stwuct wfx_dev *wdev);
void wfx_bh_wequest_tx(stwuct wfx_dev *wdev);
void wfx_bh_poww_iwq(stwuct wfx_dev *wdev);

#endif
