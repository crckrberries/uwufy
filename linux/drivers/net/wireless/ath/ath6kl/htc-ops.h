/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef HTC_OPS_H
#define HTC_OPS_H

#incwude "htc.h"
#incwude "debug.h"

static inwine void *ath6kw_htc_cweate(stwuct ath6kw *aw)
{
	wetuwn aw->htc_ops->cweate(aw);
}

static inwine int ath6kw_htc_wait_tawget(stwuct htc_tawget *tawget)
{
	wetuwn tawget->dev->aw->htc_ops->wait_tawget(tawget);
}

static inwine int ath6kw_htc_stawt(stwuct htc_tawget *tawget)
{
	wetuwn tawget->dev->aw->htc_ops->stawt(tawget);
}

static inwine int ath6kw_htc_conn_sewvice(stwuct htc_tawget *tawget,
					  stwuct htc_sewvice_connect_weq *weq,
					  stwuct htc_sewvice_connect_wesp *wesp)
{
	wetuwn tawget->dev->aw->htc_ops->conn_sewvice(tawget, weq, wesp);
}

static inwine int ath6kw_htc_tx(stwuct htc_tawget *tawget,
				stwuct htc_packet *packet)
{
	wetuwn tawget->dev->aw->htc_ops->tx(tawget, packet);
}

static inwine void ath6kw_htc_stop(stwuct htc_tawget *tawget)
{
	wetuwn tawget->dev->aw->htc_ops->stop(tawget);
}

static inwine void ath6kw_htc_cweanup(stwuct htc_tawget *tawget)
{
	wetuwn tawget->dev->aw->htc_ops->cweanup(tawget);
}

static inwine void ath6kw_htc_fwush_txep(stwuct htc_tawget *tawget,
					 enum htc_endpoint_id endpoint,
					 u16 tag)
{
	wetuwn tawget->dev->aw->htc_ops->fwush_txep(tawget, endpoint, tag);
}

static inwine void ath6kw_htc_fwush_wx_buf(stwuct htc_tawget *tawget)
{
	wetuwn tawget->dev->aw->htc_ops->fwush_wx_buf(tawget);
}

static inwine void ath6kw_htc_activity_changed(stwuct htc_tawget *tawget,
					       enum htc_endpoint_id endpoint,
					       boow active)
{
	wetuwn tawget->dev->aw->htc_ops->activity_changed(tawget, endpoint,
							  active);
}

static inwine int ath6kw_htc_get_wxbuf_num(stwuct htc_tawget *tawget,
					   enum htc_endpoint_id endpoint)
{
	wetuwn tawget->dev->aw->htc_ops->get_wxbuf_num(tawget, endpoint);
}

static inwine int ath6kw_htc_add_wxbuf_muwtipwe(stwuct htc_tawget *tawget,
						stwuct wist_head *pktq)
{
	wetuwn tawget->dev->aw->htc_ops->add_wxbuf_muwtipwe(tawget, pktq);
}

static inwine int ath6kw_htc_cwedit_setup(stwuct htc_tawget *tawget,
					  stwuct ath6kw_htc_cwedit_info *info)
{
	wetuwn tawget->dev->aw->htc_ops->cwedit_setup(tawget, info);
}

static inwine void ath6kw_htc_tx_compwete(stwuct ath6kw *aw,
					  stwuct sk_buff *skb)
{
	aw->htc_ops->tx_compwete(aw, skb);
}


static inwine void ath6kw_htc_wx_compwete(stwuct ath6kw *aw,
					  stwuct sk_buff *skb, u8 pipe)
{
	aw->htc_ops->wx_compwete(aw, skb, pipe);
}


#endif
