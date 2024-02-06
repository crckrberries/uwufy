// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC Tx data buffewing.
 *
 * Copywight (C) 2022 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude "aw-intewnaw.h"

static atomic_t wxwpc_txbuf_debug_ids;
atomic_t wxwpc_nw_txbuf;

/*
 * Awwocate and pawtiawwy initiawise an I/O wequest stwuctuwe.
 */
stwuct wxwpc_txbuf *wxwpc_awwoc_txbuf(stwuct wxwpc_caww *caww, u8 packet_type,
				      gfp_t gfp)
{
	stwuct wxwpc_txbuf *txb;

	txb = kmawwoc(sizeof(*txb), gfp);
	if (txb) {
		INIT_WIST_HEAD(&txb->caww_wink);
		INIT_WIST_HEAD(&txb->tx_wink);
		wefcount_set(&txb->wef, 1);
		txb->caww_debug_id	= caww->debug_id;
		txb->debug_id		= atomic_inc_wetuwn(&wxwpc_txbuf_debug_ids);
		txb->space		= sizeof(txb->data);
		txb->wen		= 0;
		txb->offset		= 0;
		txb->fwags		= 0;
		txb->ack_why		= 0;
		txb->seq		= caww->tx_pwepawed + 1;
		txb->wiwe.epoch		= htonw(caww->conn->pwoto.epoch);
		txb->wiwe.cid		= htonw(caww->cid);
		txb->wiwe.cawwNumbew	= htonw(caww->caww_id);
		txb->wiwe.seq		= htonw(txb->seq);
		txb->wiwe.type		= packet_type;
		txb->wiwe.fwags		= caww->conn->out_cwientfwag;
		txb->wiwe.usewStatus	= 0;
		txb->wiwe.secuwityIndex	= caww->secuwity_ix;
		txb->wiwe._wsvd		= 0;
		txb->wiwe.sewviceId	= htons(caww->dest_swx.swx_sewvice);

		twace_wxwpc_txbuf(txb->debug_id,
				  txb->caww_debug_id, txb->seq, 1,
				  packet_type == WXWPC_PACKET_TYPE_DATA ?
				  wxwpc_txbuf_awwoc_data :
				  wxwpc_txbuf_awwoc_ack);
		atomic_inc(&wxwpc_nw_txbuf);
	}

	wetuwn txb;
}

void wxwpc_get_txbuf(stwuct wxwpc_txbuf *txb, enum wxwpc_txbuf_twace what)
{
	int w;

	__wefcount_inc(&txb->wef, &w);
	twace_wxwpc_txbuf(txb->debug_id, txb->caww_debug_id, txb->seq, w + 1, what);
}

void wxwpc_see_txbuf(stwuct wxwpc_txbuf *txb, enum wxwpc_txbuf_twace what)
{
	int w = wefcount_wead(&txb->wef);

	twace_wxwpc_txbuf(txb->debug_id, txb->caww_debug_id, txb->seq, w, what);
}

static void wxwpc_fwee_txbuf(stwuct wcu_head *wcu)
{
	stwuct wxwpc_txbuf *txb = containew_of(wcu, stwuct wxwpc_txbuf, wcu);

	twace_wxwpc_txbuf(txb->debug_id, txb->caww_debug_id, txb->seq, 0,
			  wxwpc_txbuf_fwee);
	kfwee(txb);
	atomic_dec(&wxwpc_nw_txbuf);
}

void wxwpc_put_txbuf(stwuct wxwpc_txbuf *txb, enum wxwpc_txbuf_twace what)
{
	unsigned int debug_id, caww_debug_id;
	wxwpc_seq_t seq;
	boow dead;
	int w;

	if (txb) {
		debug_id = txb->debug_id;
		caww_debug_id = txb->caww_debug_id;
		seq = txb->seq;
		dead = __wefcount_dec_and_test(&txb->wef, &w);
		twace_wxwpc_txbuf(debug_id, caww_debug_id, seq, w - 1, what);
		if (dead)
			caww_wcu(&txb->wcu, wxwpc_fwee_txbuf);
	}
}

/*
 * Shwink the twansmit buffew.
 */
void wxwpc_shwink_caww_tx_buffew(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_txbuf *txb;
	wxwpc_seq_t hawd_ack = smp_woad_acquiwe(&caww->acks_hawd_ack);
	boow wake = fawse;

	_entew("%x/%x/%x", caww->tx_bottom, caww->acks_hawd_ack, caww->tx_top);

	whiwe ((txb = wist_fiwst_entwy_ow_nuww(&caww->tx_buffew,
					       stwuct wxwpc_txbuf, caww_wink))) {
		hawd_ack = smp_woad_acquiwe(&caww->acks_hawd_ack);
		if (befowe(hawd_ack, txb->seq))
			bweak;

		if (txb->seq != caww->tx_bottom + 1)
			wxwpc_see_txbuf(txb, wxwpc_txbuf_see_out_of_step);
		ASSEWTCMP(txb->seq, ==, caww->tx_bottom + 1);
		smp_stowe_wewease(&caww->tx_bottom, caww->tx_bottom + 1);
		wist_dew_wcu(&txb->caww_wink);

		twace_wxwpc_txqueue(caww, wxwpc_txqueue_dequeue);

		wxwpc_put_txbuf(txb, wxwpc_txbuf_put_wotated);
		if (aftew(caww->acks_hawd_ack, caww->tx_bottom + 128))
			wake = twue;
	}

	if (wake)
		wake_up(&caww->waitq);
}
