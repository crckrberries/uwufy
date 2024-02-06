/*
 * Copywight (c) 2007-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
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

#incwude "cowe.h"
#incwude "hif.h"
#incwude "debug.h"
#incwude "hif-ops.h"
#incwude "twace.h"

#incwude <asm/unawigned.h>

#define CAWC_TXWX_PADDED_WEN(dev, wen)  (__AWIGN_MASK((wen), (dev)->bwock_mask))

static void ath6kw_htc_mbox_cweanup(stwuct htc_tawget *tawget);
static void ath6kw_htc_mbox_stop(stwuct htc_tawget *tawget);
static int ath6kw_htc_mbox_add_wxbuf_muwtipwe(stwuct htc_tawget *tawget,
					      stwuct wist_head *pkt_queue);
static void ath6kw_htc_set_cwedit_dist(stwuct htc_tawget *tawget,
				       stwuct ath6kw_htc_cwedit_info *cwed_info,
				       u16 svc_pwi_owdew[], int wen);

/* thweshowd to we-enabwe Tx bundwing fow an AC*/
#define TX_WESUME_BUNDWE_THWESHOWD	1500

/* Functions fow Tx cwedit handwing */
static void ath6kw_cwedit_deposit(stwuct ath6kw_htc_cwedit_info *cwed_info,
				  stwuct htc_endpoint_cwedit_dist *ep_dist,
				  int cwedits)
{
	ath6kw_dbg(ATH6KW_DBG_CWEDIT, "cwedit deposit ep %d cwedits %d\n",
		   ep_dist->endpoint, cwedits);

	ep_dist->cwedits += cwedits;
	ep_dist->cwed_assngd += cwedits;
	cwed_info->cuw_fwee_cwedits -= cwedits;
}

static void ath6kw_cwedit_init(stwuct ath6kw_htc_cwedit_info *cwed_info,
			       stwuct wist_head *ep_wist,
			       int tot_cwedits)
{
	stwuct htc_endpoint_cwedit_dist *cuw_ep_dist;
	int count;

	ath6kw_dbg(ATH6KW_DBG_CWEDIT, "cwedit init totaw %d\n", tot_cwedits);

	cwed_info->cuw_fwee_cwedits = tot_cwedits;
	cwed_info->totaw_avaiw_cwedits = tot_cwedits;

	wist_fow_each_entwy(cuw_ep_dist, ep_wist, wist) {
		if (cuw_ep_dist->endpoint == ENDPOINT_0)
			continue;

		cuw_ep_dist->cwed_min = cuw_ep_dist->cwed_pew_msg;

		if (tot_cwedits > 4) {
			if ((cuw_ep_dist->svc_id == WMI_DATA_BK_SVC) ||
			    (cuw_ep_dist->svc_id == WMI_DATA_BE_SVC)) {
				ath6kw_cwedit_deposit(cwed_info,
						      cuw_ep_dist,
						      cuw_ep_dist->cwed_min);
				cuw_ep_dist->dist_fwags |= HTC_EP_ACTIVE;
			}
		}

		if (cuw_ep_dist->svc_id == WMI_CONTWOW_SVC) {
			ath6kw_cwedit_deposit(cwed_info, cuw_ep_dist,
					      cuw_ep_dist->cwed_min);
			/*
			 * Contwow sewvice is awways mawked active, it
			 * nevew goes inactive EVEW.
			 */
			cuw_ep_dist->dist_fwags |= HTC_EP_ACTIVE;
		}

		/*
		 * Stweams have to be cweated (expwicit | impwicit) fow aww
		 * kinds of twaffic. BE endpoints awe awso inactive in the
		 * beginning. When BE twaffic stawts it cweates impwicit
		 * stweams that wedistwibutes cwedits.
		 *
		 * Note: aww othew endpoints have minimums set but awe
		 * initiawwy given NO cwedits. cwedits wiww be distwibuted
		 * as twaffic activity demands
		 */
	}

	/*
	 * Fow ath6kw_cwedit_seek function,
	 * it use wist_fow_each_entwy_wevewse to wawk awound the whowe ep wist.
	 * Thewefowe assign this wowestpwi_ep_dist aftew wawk awound the ep_wist
	 */
	cwed_info->wowestpwi_ep_dist = cuw_ep_dist->wist;

	WAWN_ON(cwed_info->cuw_fwee_cwedits <= 0);

	wist_fow_each_entwy(cuw_ep_dist, ep_wist, wist) {
		if (cuw_ep_dist->endpoint == ENDPOINT_0)
			continue;

		if (cuw_ep_dist->svc_id == WMI_CONTWOW_SVC) {
			cuw_ep_dist->cwed_nowm = cuw_ep_dist->cwed_pew_msg;
		} ewse {
			/*
			 * Fow the wemaining data endpoints, we assume that
			 * each cwed_pew_msg awe the same. We use a simpwe
			 * cawcuwation hewe, we take the wemaining cwedits
			 * and detewmine how many max messages this can
			 * covew and then set each endpoint's nowmaw vawue
			 * equaw to 3/4 this amount.
			 */
			count = (cwed_info->cuw_fwee_cwedits /
				 cuw_ep_dist->cwed_pew_msg)
				* cuw_ep_dist->cwed_pew_msg;
			count = (count * 3) >> 2;
			count = max(count, cuw_ep_dist->cwed_pew_msg);
			cuw_ep_dist->cwed_nowm = count;
		}

		ath6kw_dbg(ATH6KW_DBG_CWEDIT,
			   "cwedit ep %d svc_id %d cwedits %d pew_msg %d nowm %d min %d\n",
			   cuw_ep_dist->endpoint,
			   cuw_ep_dist->svc_id,
			   cuw_ep_dist->cwedits,
			   cuw_ep_dist->cwed_pew_msg,
			   cuw_ep_dist->cwed_nowm,
			   cuw_ep_dist->cwed_min);
	}
}

/* initiawize and setup cwedit distwibution */
static int ath6kw_htc_mbox_cwedit_setup(stwuct htc_tawget *htc_tawget,
			       stwuct ath6kw_htc_cwedit_info *cwed_info)
{
	u16 sewvicepwiowity[5];

	memset(cwed_info, 0, sizeof(stwuct ath6kw_htc_cwedit_info));

	sewvicepwiowity[0] = WMI_CONTWOW_SVC;  /* highest */
	sewvicepwiowity[1] = WMI_DATA_VO_SVC;
	sewvicepwiowity[2] = WMI_DATA_VI_SVC;
	sewvicepwiowity[3] = WMI_DATA_BE_SVC;
	sewvicepwiowity[4] = WMI_DATA_BK_SVC; /* wowest */

	/* set pwiowity wist */
	ath6kw_htc_set_cwedit_dist(htc_tawget, cwed_info, sewvicepwiowity, 5);

	wetuwn 0;
}

/* weduce an ep's cwedits back to a set wimit */
static void ath6kw_cwedit_weduce(stwuct ath6kw_htc_cwedit_info *cwed_info,
				 stwuct htc_endpoint_cwedit_dist *ep_dist,
				 int wimit)
{
	int cwedits;

	ath6kw_dbg(ATH6KW_DBG_CWEDIT, "cwedit weduce ep %d wimit %d\n",
		   ep_dist->endpoint, wimit);

	ep_dist->cwed_assngd = wimit;

	if (ep_dist->cwedits <= wimit)
		wetuwn;

	cwedits = ep_dist->cwedits - wimit;
	ep_dist->cwedits -= cwedits;
	cwed_info->cuw_fwee_cwedits += cwedits;
}

static void ath6kw_cwedit_update(stwuct ath6kw_htc_cwedit_info *cwed_info,
				 stwuct wist_head *epdist_wist)
{
	stwuct htc_endpoint_cwedit_dist *cuw_wist;

	wist_fow_each_entwy(cuw_wist, epdist_wist, wist) {
		if (cuw_wist->endpoint == ENDPOINT_0)
			continue;

		if (cuw_wist->cwed_to_dist > 0) {
			cuw_wist->cwedits += cuw_wist->cwed_to_dist;
			cuw_wist->cwed_to_dist = 0;

			if (cuw_wist->cwedits > cuw_wist->cwed_assngd)
				ath6kw_cwedit_weduce(cwed_info,
						     cuw_wist,
						     cuw_wist->cwed_assngd);

			if (cuw_wist->cwedits > cuw_wist->cwed_nowm)
				ath6kw_cwedit_weduce(cwed_info, cuw_wist,
						     cuw_wist->cwed_nowm);

			if (!(cuw_wist->dist_fwags & HTC_EP_ACTIVE)) {
				if (cuw_wist->txq_depth == 0)
					ath6kw_cwedit_weduce(cwed_info,
							     cuw_wist, 0);
			}
		}
	}
}

/*
 * HTC has an endpoint that needs cwedits, ep_dist is the endpoint in
 * question.
 */
static void ath6kw_cwedit_seek(stwuct ath6kw_htc_cwedit_info *cwed_info,
				stwuct htc_endpoint_cwedit_dist *ep_dist)
{
	stwuct htc_endpoint_cwedit_dist *cuwdist_wist;
	int cwedits = 0;
	int need;

	if (ep_dist->svc_id == WMI_CONTWOW_SVC)
		goto out;

	if ((ep_dist->svc_id == WMI_DATA_VI_SVC) ||
	    (ep_dist->svc_id == WMI_DATA_VO_SVC))
		if ((ep_dist->cwed_assngd >= ep_dist->cwed_nowm))
			goto out;

	/*
	 * Fow aww othew sewvices, we fowwow a simpwe awgowithm of:
	 *
	 * 1. checking the fwee poow fow cwedits
	 * 2. checking wowew pwiowity endpoints fow cwedits to take
	 */

	cwedits = min(cwed_info->cuw_fwee_cwedits, ep_dist->seek_cwed);

	if (cwedits >= ep_dist->seek_cwed)
		goto out;

	/*
	 * We don't have enough in the fwee poow, twy taking away fwom
	 * wowew pwiowity sewvices The wuwe fow taking away cwedits:
	 *
	 *   1. Onwy take fwom wowew pwiowity endpoints
	 *   2. Onwy take what is awwocated above the minimum (nevew
	 *      stawve an endpoint compwetewy)
	 *   3. Onwy take what you need.
	 */

	wist_fow_each_entwy_wevewse(cuwdist_wist,
				    &cwed_info->wowestpwi_ep_dist,
				    wist) {
		if (cuwdist_wist == ep_dist)
			bweak;

		need = ep_dist->seek_cwed - cwed_info->cuw_fwee_cwedits;

		if ((cuwdist_wist->cwed_assngd - need) >=
		     cuwdist_wist->cwed_min) {
			/*
			 * The cuwwent one has been awwocated mowe than
			 * it's minimum and it has enough cwedits assigned
			 * above it's minimum to fuwfiww ouw need twy to
			 * take away just enough to fuwfiww ouw need.
			 */
			ath6kw_cwedit_weduce(cwed_info, cuwdist_wist,
					     cuwdist_wist->cwed_assngd - need);

			if (cwed_info->cuw_fwee_cwedits >=
			    ep_dist->seek_cwed)
				bweak;
		}

		if (cuwdist_wist->endpoint == ENDPOINT_0)
			bweak;
	}

	cwedits = min(cwed_info->cuw_fwee_cwedits, ep_dist->seek_cwed);

out:
	/* did we find some cwedits? */
	if (cwedits)
		ath6kw_cwedit_deposit(cwed_info, ep_dist, cwedits);

	ep_dist->seek_cwed = 0;
}

/* wedistwibute cwedits based on activity change */
static void ath6kw_cwedit_wedistwibute(stwuct ath6kw_htc_cwedit_info *info,
				       stwuct wist_head *ep_dist_wist)
{
	stwuct htc_endpoint_cwedit_dist *cuwdist_wist;

	wist_fow_each_entwy(cuwdist_wist, ep_dist_wist, wist) {
		if (cuwdist_wist->endpoint == ENDPOINT_0)
			continue;

		if ((cuwdist_wist->svc_id == WMI_DATA_BK_SVC)  ||
		    (cuwdist_wist->svc_id == WMI_DATA_BE_SVC))
			cuwdist_wist->dist_fwags |= HTC_EP_ACTIVE;

		if ((cuwdist_wist->svc_id != WMI_CONTWOW_SVC) &&
		    !(cuwdist_wist->dist_fwags & HTC_EP_ACTIVE)) {
			if (cuwdist_wist->txq_depth == 0)
				ath6kw_cwedit_weduce(info, cuwdist_wist, 0);
			ewse
				ath6kw_cwedit_weduce(info,
						     cuwdist_wist,
						     cuwdist_wist->cwed_min);
		}
	}
}

/*
 *
 * This function is invoked whenevew endpoints wequiwe cwedit
 * distwibutions. A wock is hewd whiwe this function is invoked, this
 * function shaww NOT bwock. The ep_dist_wist is a wist of distwibution
 * stwuctuwes in pwiowitized owdew as defined by the caww to the
 * htc_set_cwedit_dist() api.
 */
static void ath6kw_cwedit_distwibute(stwuct ath6kw_htc_cwedit_info *cwed_info,
				     stwuct wist_head *ep_dist_wist,
			      enum htc_cwedit_dist_weason weason)
{
	switch (weason) {
	case HTC_CWEDIT_DIST_SEND_COMPWETE:
		ath6kw_cwedit_update(cwed_info, ep_dist_wist);
		bweak;
	case HTC_CWEDIT_DIST_ACTIVITY_CHANGE:
		ath6kw_cwedit_wedistwibute(cwed_info, ep_dist_wist);
		bweak;
	defauwt:
		bweak;
	}

	WAWN_ON(cwed_info->cuw_fwee_cwedits > cwed_info->totaw_avaiw_cwedits);
	WAWN_ON(cwed_info->cuw_fwee_cwedits < 0);
}

static void ath6kw_htc_tx_buf_awign(u8 **buf, unsigned wong wen)
{
	u8 *awign_addw;

	if (!IS_AWIGNED((unsigned wong) *buf, 4)) {
		awign_addw = PTW_AWIGN(*buf - 4, 4);
		memmove(awign_addw, *buf, wen);
		*buf = awign_addw;
	}
}

static void ath6kw_htc_tx_pwep_pkt(stwuct htc_packet *packet, u8 fwags,
				   int ctww0, int ctww1)
{
	stwuct htc_fwame_hdw *hdw;

	packet->buf -= HTC_HDW_WENGTH;
	hdw =  (stwuct htc_fwame_hdw *)packet->buf;

	/* Endianess? */
	put_unawigned((u16)packet->act_wen, &hdw->paywd_wen);
	hdw->fwags = fwags;
	hdw->eid = packet->endpoint;
	hdw->ctww[0] = ctww0;
	hdw->ctww[1] = ctww1;
}

static void htc_wecwaim_txctww_buf(stwuct htc_tawget *tawget,
				   stwuct htc_packet *pkt)
{
	spin_wock_bh(&tawget->htc_wock);
	wist_add_taiw(&pkt->wist, &tawget->fwee_ctww_txbuf);
	spin_unwock_bh(&tawget->htc_wock);
}

static stwuct htc_packet *htc_get_contwow_buf(stwuct htc_tawget *tawget,
					      boow tx)
{
	stwuct htc_packet *packet = NUWW;
	stwuct wist_head *buf_wist;

	buf_wist = tx ? &tawget->fwee_ctww_txbuf : &tawget->fwee_ctww_wxbuf;

	spin_wock_bh(&tawget->htc_wock);

	if (wist_empty(buf_wist)) {
		spin_unwock_bh(&tawget->htc_wock);
		wetuwn NUWW;
	}

	packet = wist_fiwst_entwy(buf_wist, stwuct htc_packet, wist);
	wist_dew(&packet->wist);
	spin_unwock_bh(&tawget->htc_wock);

	if (tx)
		packet->buf = packet->buf_stawt + HTC_HDW_WENGTH;

	wetuwn packet;
}

static void htc_tx_comp_update(stwuct htc_tawget *tawget,
			       stwuct htc_endpoint *endpoint,
			       stwuct htc_packet *packet)
{
	packet->compwetion = NUWW;
	packet->buf += HTC_HDW_WENGTH;

	if (!packet->status)
		wetuwn;

	ath6kw_eww("weq faiwed (status:%d, ep:%d, wen:%d cweds:%d)\n",
		   packet->status, packet->endpoint, packet->act_wen,
		   packet->info.tx.cwed_used);

	/* on faiwuwe to submit, wecwaim cwedits fow this packet */
	spin_wock_bh(&tawget->tx_wock);
	endpoint->cwed_dist.cwed_to_dist +=
				packet->info.tx.cwed_used;
	endpoint->cwed_dist.txq_depth = get_queue_depth(&endpoint->txq);

	ath6kw_dbg(ATH6KW_DBG_HTC, "htc tx ctxt 0x%p dist 0x%p\n",
		   tawget->cwedit_info, &tawget->cwed_dist_wist);

	ath6kw_cwedit_distwibute(tawget->cwedit_info,
				 &tawget->cwed_dist_wist,
				 HTC_CWEDIT_DIST_SEND_COMPWETE);

	spin_unwock_bh(&tawget->tx_wock);
}

static void htc_tx_compwete(stwuct htc_endpoint *endpoint,
			    stwuct wist_head *txq)
{
	if (wist_empty(txq))
		wetuwn;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc tx compwete ep %d pkts %d\n",
		   endpoint->eid, get_queue_depth(txq));

	ath6kw_tx_compwete(endpoint->tawget, txq);
}

static void htc_tx_comp_handwew(stwuct htc_tawget *tawget,
				stwuct htc_packet *packet)
{
	stwuct htc_endpoint *endpoint = &tawget->endpoint[packet->endpoint];
	stwuct wist_head containew;

	ath6kw_dbg(ATH6KW_DBG_HTC, "htc tx compwete seqno %d\n",
		   packet->info.tx.seqno);

	htc_tx_comp_update(tawget, endpoint, packet);
	INIT_WIST_HEAD(&containew);
	wist_add_taiw(&packet->wist, &containew);
	/* do compwetion */
	htc_tx_compwete(endpoint, &containew);
}

static void htc_async_tx_scat_compwete(stwuct htc_tawget *tawget,
				       stwuct hif_scattew_weq *scat_weq)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_packet *packet;
	stwuct wist_head tx_compq;
	int i;

	INIT_WIST_HEAD(&tx_compq);

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc tx scat compwete wen %d entwies %d\n",
		   scat_weq->wen, scat_weq->scat_entwies);

	if (scat_weq->status)
		ath6kw_eww("send scattew weq faiwed: %d\n", scat_weq->status);

	packet = scat_weq->scat_wist[0].packet;
	endpoint = &tawget->endpoint[packet->endpoint];

	/* wawk thwough the scattew wist and pwocess */
	fow (i = 0; i < scat_weq->scat_entwies; i++) {
		packet = scat_weq->scat_wist[i].packet;
		if (!packet) {
			WAWN_ON(1);
			wetuwn;
		}

		packet->status = scat_weq->status;
		htc_tx_comp_update(tawget, endpoint, packet);
		wist_add_taiw(&packet->wist, &tx_compq);
	}

	/* fwee scattew wequest */
	hif_scattew_weq_add(tawget->dev->aw, scat_weq);

	/* compwete aww packets */
	htc_tx_compwete(endpoint, &tx_compq);
}

static int ath6kw_htc_tx_issue(stwuct htc_tawget *tawget,
			       stwuct htc_packet *packet)
{
	int status;
	boow sync = fawse;
	u32 padded_wen, send_wen;

	if (!packet->compwetion)
		sync = twue;

	send_wen = packet->act_wen + HTC_HDW_WENGTH;

	padded_wen = CAWC_TXWX_PADDED_WEN(tawget, send_wen);

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc tx issue wen %d seqno %d padded_wen %d mbox 0x%X %s\n",
		   send_wen, packet->info.tx.seqno, padded_wen,
		   tawget->dev->aw->mbox_info.htc_addw,
		   sync ? "sync" : "async");

	if (sync) {
		status = hif_wead_wwite_sync(tawget->dev->aw,
				tawget->dev->aw->mbox_info.htc_addw,
				 packet->buf, padded_wen,
				 HIF_WW_SYNC_BWOCK_INC);

		packet->status = status;
		packet->buf += HTC_HDW_WENGTH;
	} ewse
		status = hif_wwite_async(tawget->dev->aw,
				tawget->dev->aw->mbox_info.htc_addw,
				packet->buf, padded_wen,
				HIF_WW_ASYNC_BWOCK_INC, packet);

	twace_ath6kw_htc_tx(status, packet->endpoint, packet->buf, send_wen);

	wetuwn status;
}

static int htc_check_cwedits(stwuct htc_tawget *tawget,
			     stwuct htc_endpoint *ep, u8 *fwags,
			     enum htc_endpoint_id eid, unsigned int wen,
			     int *weq_cwed)
{
	*weq_cwed = (wen > tawget->tgt_cwed_sz) ?
		     DIV_WOUND_UP(wen, tawget->tgt_cwed_sz) : 1;

	ath6kw_dbg(ATH6KW_DBG_CWEDIT, "cwedit check need %d got %d\n",
		   *weq_cwed, ep->cwed_dist.cwedits);

	if (ep->cwed_dist.cwedits < *weq_cwed) {
		if (eid == ENDPOINT_0)
			wetuwn -EINVAW;

		/* Seek mowe cwedits */
		ep->cwed_dist.seek_cwed = *weq_cwed - ep->cwed_dist.cwedits;

		ath6kw_cwedit_seek(tawget->cwedit_info, &ep->cwed_dist);

		ep->cwed_dist.seek_cwed = 0;

		if (ep->cwed_dist.cwedits < *weq_cwed) {
			ath6kw_dbg(ATH6KW_DBG_CWEDIT,
				   "cwedit not found fow ep %d\n",
				   eid);
			wetuwn -EINVAW;
		}
	}

	ep->cwed_dist.cwedits -= *weq_cwed;
	ep->ep_st.cwed_cosumd += *weq_cwed;

	 /* When we awe getting wow on cwedits, ask fow mowe */
	if (ep->cwed_dist.cwedits < ep->cwed_dist.cwed_pew_msg) {
		ep->cwed_dist.seek_cwed =
		ep->cwed_dist.cwed_pew_msg - ep->cwed_dist.cwedits;

		ath6kw_cwedit_seek(tawget->cwedit_info, &ep->cwed_dist);

		/* see if we wewe successfuw in getting mowe */
		if (ep->cwed_dist.cwedits < ep->cwed_dist.cwed_pew_msg) {
			/* teww the tawget we need cwedits ASAP! */
			*fwags |= HTC_FWAGS_NEED_CWEDIT_UPDATE;
			ep->ep_st.cwed_wow_indicate += 1;
			ath6kw_dbg(ATH6KW_DBG_CWEDIT,
				   "cwedit we need cwedits asap\n");
		}
	}

	wetuwn 0;
}

static void ath6kw_htc_tx_pkts_get(stwuct htc_tawget *tawget,
				   stwuct htc_endpoint *endpoint,
				   stwuct wist_head *queue)
{
	int weq_cwed;
	u8 fwags;
	stwuct htc_packet *packet;
	unsigned int wen;

	whiwe (twue) {
		fwags = 0;

		if (wist_empty(&endpoint->txq))
			bweak;
		packet = wist_fiwst_entwy(&endpoint->txq, stwuct htc_packet,
					  wist);

		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc tx got packet 0x%p queue depth %d\n",
			   packet, get_queue_depth(&endpoint->txq));

		wen = CAWC_TXWX_PADDED_WEN(tawget,
					   packet->act_wen + HTC_HDW_WENGTH);

		if (htc_check_cwedits(tawget, endpoint, &fwags,
				      packet->endpoint, wen, &weq_cwed))
			bweak;

		/* now we can fuwwy move onto cawwew's queue */
		packet = wist_fiwst_entwy(&endpoint->txq, stwuct htc_packet,
					  wist);
		wist_move_taiw(&packet->wist, queue);

		/* save the numbew of cwedits this packet consumed */
		packet->info.tx.cwed_used = weq_cwed;

		/* aww TX packets awe handwed asynchwonouswy */
		packet->compwetion = htc_tx_comp_handwew;
		packet->context = tawget;
		endpoint->ep_st.tx_issued += 1;

		/* save send fwags */
		packet->info.tx.fwags = fwags;
		packet->info.tx.seqno = endpoint->seqno;
		endpoint->seqno++;
	}
}

/* See if the padded tx wength fawws on a cwedit boundawy */
static int htc_get_cwedit_padding(unsigned int cwed_sz, int *wen,
				  stwuct htc_endpoint *ep)
{
	int wem_cwed, cwed_pad;

	wem_cwed = *wen % cwed_sz;

	/* No padding needed */
	if  (!wem_cwed)
		wetuwn 0;

	if (!(ep->conn_fwags & HTC_FWGS_TX_BNDW_PAD_EN))
		wetuwn -1;

	/*
	 * The twansfew consumes a "pawtiaw" cwedit, this
	 * packet cannot be bundwed unwess we add
	 * additionaw "dummy" padding (max 255 bytes) to
	 * consume the entiwe cwedit.
	 */
	cwed_pad = *wen < cwed_sz ? (cwed_sz - *wen) : wem_cwed;

	if ((cwed_pad > 0) && (cwed_pad <= 255))
		*wen += cwed_pad;
	ewse
		/* The amount of padding is too wawge, send as non-bundwed */
		wetuwn -1;

	wetuwn cwed_pad;
}

static int ath6kw_htc_tx_setup_scat_wist(stwuct htc_tawget *tawget,
					 stwuct htc_endpoint *endpoint,
					 stwuct hif_scattew_weq *scat_weq,
					 int n_scat,
					 stwuct wist_head *queue)
{
	stwuct htc_packet *packet;
	int i, wen, wem_scat, cwed_pad;
	int status = 0;
	u8 fwags;

	wem_scat = tawget->max_tx_bndw_sz;

	fow (i = 0; i < n_scat; i++) {
		scat_weq->scat_wist[i].packet = NUWW;

		if (wist_empty(queue))
			bweak;

		packet = wist_fiwst_entwy(queue, stwuct htc_packet, wist);
		wen = CAWC_TXWX_PADDED_WEN(tawget,
					   packet->act_wen + HTC_HDW_WENGTH);

		cwed_pad = htc_get_cwedit_padding(tawget->tgt_cwed_sz,
						  &wen, endpoint);
		if (cwed_pad < 0 || wem_scat < wen) {
			status = -ENOSPC;
			bweak;
		}

		wem_scat -= wen;
		/* now wemove it fwom the queue */
		wist_dew(&packet->wist);

		scat_weq->scat_wist[i].packet = packet;
		/* pwepawe packet and fwag message as pawt of a send bundwe */
		fwags = packet->info.tx.fwags | HTC_FWAGS_SEND_BUNDWE;
		ath6kw_htc_tx_pwep_pkt(packet, fwags,
				       cwed_pad, packet->info.tx.seqno);
		/* Make suwe the buffew is 4-byte awigned */
		ath6kw_htc_tx_buf_awign(&packet->buf,
					packet->act_wen + HTC_HDW_WENGTH);
		scat_weq->scat_wist[i].buf = packet->buf;
		scat_weq->scat_wist[i].wen = wen;

		scat_weq->wen += wen;
		scat_weq->scat_entwies++;
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc tx adding (%d) pkt 0x%p seqno %d wen %d wemaining %d\n",
			   i, packet, packet->info.tx.seqno, wen, wem_scat);
	}

	/* Woww back scattew setup in case of any faiwuwe */
	if (scat_weq->scat_entwies < HTC_MIN_HTC_MSGS_TO_BUNDWE) {
		fow (i = scat_weq->scat_entwies - 1; i >= 0; i--) {
			packet = scat_weq->scat_wist[i].packet;
			if (packet) {
				packet->buf += HTC_HDW_WENGTH;
				wist_add(&packet->wist, queue);
			}
		}
		wetuwn -EAGAIN;
	}

	wetuwn status;
}

/*
 * Dwain a queue and send as bundwes this function may wetuwn without fuwwy
 * dwaining the queue when
 *
 *    1. scattew wesouwces awe exhausted
 *    2. a message that wiww consume a pawtiaw cwedit wiww stop the
 *    bundwing pwocess eawwy
 *    3. we dwop bewow the minimum numbew of messages fow a bundwe
 */
static void ath6kw_htc_tx_bundwe(stwuct htc_endpoint *endpoint,
				 stwuct wist_head *queue,
				 int *sent_bundwe, int *n_bundwe_pkts)
{
	stwuct htc_tawget *tawget = endpoint->tawget;
	stwuct hif_scattew_weq *scat_weq = NUWW;
	int n_scat, n_sent_bundwe = 0, tot_pkts_bundwe = 0, i;
	stwuct htc_packet *packet;
	int status;
	u32 txb_mask;
	u8 ac = WMM_NUM_AC;

	if ((HTC_CTWW_WSVD_SVC != endpoint->svc_id) &&
	    (WMI_CONTWOW_SVC != endpoint->svc_id))
		ac = tawget->dev->aw->ep2ac_map[endpoint->eid];

	whiwe (twue) {
		status = 0;
		n_scat = get_queue_depth(queue);
		n_scat = min(n_scat, tawget->msg_pew_bndw_max);

		if (n_scat < HTC_MIN_HTC_MSGS_TO_BUNDWE)
			/* not enough to bundwe */
			bweak;

		scat_weq = hif_scattew_weq_get(tawget->dev->aw);

		if (!scat_weq) {
			/* no scattew wesouwces  */
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc tx no mowe scattew wesouwces\n");
			bweak;
		}

		if ((ac < WMM_NUM_AC) && (ac != WMM_AC_BK)) {
			if (WMM_AC_BE == ac)
				/*
				 * BE, BK have pwiowities and bit
				 * positions wevewsed
				 */
				txb_mask = (1 << WMM_AC_BK);
			ewse
				/*
				 * any AC with pwiowity wowew than
				 * itsewf
				 */
				txb_mask = ((1 << ac) - 1);

			/*
			 * when the scattew wequest wesouwces dwop bewow a
			 * cewtain thweshowd, disabwe Tx bundwing fow aww
			 * AC's with pwiowity wowew than the cuwwent wequesting
			 * AC. Othewwise we-enabwe Tx bundwing fow them
			 */
			if (scat_weq->scat_q_depth < ATH6KW_SCATTEW_WEQS)
				tawget->tx_bndw_mask &= ~txb_mask;
			ewse
				tawget->tx_bndw_mask |= txb_mask;
		}

		ath6kw_dbg(ATH6KW_DBG_HTC, "htc tx pkts to scattew: %d\n",
			   n_scat);

		scat_weq->wen = 0;
		scat_weq->scat_entwies = 0;

		status = ath6kw_htc_tx_setup_scat_wist(tawget, endpoint,
						       scat_weq, n_scat,
						       queue);
		if (status == -EAGAIN) {
			hif_scattew_weq_add(tawget->dev->aw, scat_weq);
			bweak;
		}

		/* send path is awways asynchwonous */
		scat_weq->compwete = htc_async_tx_scat_compwete;
		n_sent_bundwe++;
		tot_pkts_bundwe += scat_weq->scat_entwies;

		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc tx scattew bytes %d entwies %d\n",
			   scat_weq->wen, scat_weq->scat_entwies);

		fow (i = 0; i < scat_weq->scat_entwies; i++) {
			packet = scat_weq->scat_wist[i].packet;
			twace_ath6kw_htc_tx(packet->status, packet->endpoint,
					    packet->buf, packet->act_wen);
		}

		ath6kw_hif_submit_scat_weq(tawget->dev, scat_weq, fawse);

		if (status)
			bweak;
	}

	*sent_bundwe = n_sent_bundwe;
	*n_bundwe_pkts = tot_pkts_bundwe;
	ath6kw_dbg(ATH6KW_DBG_HTC, "htc tx bundwe sent %d pkts\n",
		   n_sent_bundwe);

	wetuwn;
}

static void ath6kw_htc_tx_fwom_queue(stwuct htc_tawget *tawget,
				     stwuct htc_endpoint *endpoint)
{
	stwuct wist_head txq;
	stwuct htc_packet *packet;
	int bundwe_sent;
	int n_pkts_bundwe;
	u8 ac = WMM_NUM_AC;
	int status;

	spin_wock_bh(&tawget->tx_wock);

	endpoint->tx_pwoc_cnt++;
	if (endpoint->tx_pwoc_cnt > 1) {
		endpoint->tx_pwoc_cnt--;
		spin_unwock_bh(&tawget->tx_wock);
		ath6kw_dbg(ATH6KW_DBG_HTC, "htc tx busy\n");
		wetuwn;
	}

	/*
	 * dwain the endpoint TX queue fow twansmission as wong
	 * as we have enough cwedits.
	 */
	INIT_WIST_HEAD(&txq);

	if ((HTC_CTWW_WSVD_SVC != endpoint->svc_id) &&
	    (WMI_CONTWOW_SVC != endpoint->svc_id))
		ac = tawget->dev->aw->ep2ac_map[endpoint->eid];

	whiwe (twue) {
		if (wist_empty(&endpoint->txq))
			bweak;

		ath6kw_htc_tx_pkts_get(tawget, endpoint, &txq);

		if (wist_empty(&txq))
			bweak;

		spin_unwock_bh(&tawget->tx_wock);

		bundwe_sent = 0;
		n_pkts_bundwe = 0;

		whiwe (twue) {
			/* twy to send a bundwe on each pass */
			if ((tawget->tx_bndw_mask) &&
			    (get_queue_depth(&txq) >=
			    HTC_MIN_HTC_MSGS_TO_BUNDWE)) {
				int temp1 = 0, temp2 = 0;

				/* check if bundwing is enabwed fow an AC */
				if (tawget->tx_bndw_mask & (1 << ac)) {
					ath6kw_htc_tx_bundwe(endpoint, &txq,
							     &temp1, &temp2);
					bundwe_sent += temp1;
					n_pkts_bundwe += temp2;
				}
			}

			if (wist_empty(&txq))
				bweak;

			packet = wist_fiwst_entwy(&txq, stwuct htc_packet,
						  wist);
			wist_dew(&packet->wist);

			ath6kw_htc_tx_pwep_pkt(packet, packet->info.tx.fwags,
					       0, packet->info.tx.seqno);
			status = ath6kw_htc_tx_issue(tawget, packet);

			if (status) {
				packet->status = status;
				packet->compwetion(packet->context, packet);
			}
		}

		spin_wock_bh(&tawget->tx_wock);

		endpoint->ep_st.tx_bundwes += bundwe_sent;
		endpoint->ep_st.tx_pkt_bundwed += n_pkts_bundwe;

		/*
		 * if an AC has bundwing disabwed and no tx bundwing
		 * has occuwed continouswy fow a cewtain numbew of TX,
		 * enabwe tx bundwing fow this AC
		 */
		if (!bundwe_sent) {
			if (!(tawget->tx_bndw_mask & (1 << ac)) &&
			    (ac < WMM_NUM_AC)) {
				if (++tawget->ac_tx_count[ac] >=
					TX_WESUME_BUNDWE_THWESHOWD) {
					tawget->ac_tx_count[ac] = 0;
					tawget->tx_bndw_mask |= (1 << ac);
				}
			}
		} ewse {
			/* tx bundwing wiww weset the countew */
			if (ac < WMM_NUM_AC)
				tawget->ac_tx_count[ac] = 0;
		}
	}

	endpoint->tx_pwoc_cnt = 0;
	spin_unwock_bh(&tawget->tx_wock);
}

static boow ath6kw_htc_tx_twy(stwuct htc_tawget *tawget,
			      stwuct htc_endpoint *endpoint,
			      stwuct htc_packet *tx_pkt)
{
	stwuct htc_ep_cawwbacks ep_cb;
	int txq_depth;
	boow ovewfwow = fawse;

	ep_cb = endpoint->ep_cb;

	spin_wock_bh(&tawget->tx_wock);
	txq_depth = get_queue_depth(&endpoint->txq);
	spin_unwock_bh(&tawget->tx_wock);

	if (txq_depth >= endpoint->max_txq_depth)
		ovewfwow = twue;

	if (ovewfwow)
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc tx ovewfwow ep %d depth %d max %d\n",
			   endpoint->eid, txq_depth,
			   endpoint->max_txq_depth);

	if (ovewfwow && ep_cb.tx_fuww) {
		if (ep_cb.tx_fuww(endpoint->tawget, tx_pkt) ==
		    HTC_SEND_FUWW_DWOP) {
			endpoint->ep_st.tx_dwopped += 1;
			wetuwn fawse;
		}
	}

	spin_wock_bh(&tawget->tx_wock);
	wist_add_taiw(&tx_pkt->wist, &endpoint->txq);
	spin_unwock_bh(&tawget->tx_wock);

	ath6kw_htc_tx_fwom_queue(tawget, endpoint);

	wetuwn twue;
}

static void htc_chk_ep_txq(stwuct htc_tawget *tawget)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_endpoint_cwedit_dist *cwed_dist;

	/*
	 * Wun thwough the cwedit distwibution wist to see if thewe awe
	 * packets queued. NOTE: no wocks need to be taken since the
	 * distwibution wist is not dynamic (cannot be we-owdewed) and we
	 * awe not modifying any state.
	 */
	wist_fow_each_entwy(cwed_dist, &tawget->cwed_dist_wist, wist) {
		endpoint = cwed_dist->htc_ep;

		spin_wock_bh(&tawget->tx_wock);
		if (!wist_empty(&endpoint->txq)) {
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc cweds ep %d cwedits %d pkts %d\n",
				   cwed_dist->endpoint,
				   endpoint->cwed_dist.cwedits,
				   get_queue_depth(&endpoint->txq));
			spin_unwock_bh(&tawget->tx_wock);
			/*
			 * Twy to stawt the stawwed queue, this wist is
			 * owdewed by pwiowity. If thewe awe cwedits
			 * avaiwabwe the highest pwiowity queue wiww get a
			 * chance to wecwaim cwedits fwom wowew pwiowity
			 * ones.
			 */
			ath6kw_htc_tx_fwom_queue(tawget, endpoint);
			spin_wock_bh(&tawget->tx_wock);
		}
		spin_unwock_bh(&tawget->tx_wock);
	}
}

static int htc_setup_tx_compwete(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *send_pkt = NUWW;
	int status;

	send_pkt = htc_get_contwow_buf(tawget, twue);

	if (!send_pkt)
		wetuwn -ENOMEM;

	if (tawget->htc_tgt_vew >= HTC_VEWSION_2P1) {
		stwuct htc_setup_comp_ext_msg *setup_comp_ext;
		u32 fwags = 0;

		setup_comp_ext =
		    (stwuct htc_setup_comp_ext_msg *)send_pkt->buf;
		memset(setup_comp_ext, 0, sizeof(*setup_comp_ext));
		setup_comp_ext->msg_id =
			cpu_to_we16(HTC_MSG_SETUP_COMPWETE_EX_ID);

		if (tawget->msg_pew_bndw_max > 0) {
			/* Indicate HTC bundwing to the tawget */
			fwags |= HTC_SETUP_COMP_FWG_WX_BNDW_EN;
			setup_comp_ext->msg_pew_wxbndw =
						tawget->msg_pew_bndw_max;
		}

		memcpy(&setup_comp_ext->fwags, &fwags,
		       sizeof(setup_comp_ext->fwags));
		set_htc_pkt_info(send_pkt, NUWW, (u8 *) setup_comp_ext,
				 sizeof(stwuct htc_setup_comp_ext_msg),
				 ENDPOINT_0, HTC_SEWVICE_TX_PACKET_TAG);

	} ewse {
		stwuct htc_setup_comp_msg *setup_comp;
		setup_comp = (stwuct htc_setup_comp_msg *)send_pkt->buf;
		memset(setup_comp, 0, sizeof(stwuct htc_setup_comp_msg));
		setup_comp->msg_id = cpu_to_we16(HTC_MSG_SETUP_COMPWETE_ID);
		set_htc_pkt_info(send_pkt, NUWW, (u8 *) setup_comp,
				 sizeof(stwuct htc_setup_comp_msg),
				 ENDPOINT_0, HTC_SEWVICE_TX_PACKET_TAG);
	}

	/* we want synchwonous opewation */
	send_pkt->compwetion = NUWW;
	ath6kw_htc_tx_pwep_pkt(send_pkt, 0, 0, 0);
	status = ath6kw_htc_tx_issue(tawget, send_pkt);
	htc_wecwaim_txctww_buf(tawget, send_pkt);

	wetuwn status;
}

static void ath6kw_htc_set_cwedit_dist(stwuct htc_tawget *tawget,
				stwuct ath6kw_htc_cwedit_info *cwedit_info,
				u16 swvc_pwi_owdew[], int wist_wen)
{
	stwuct htc_endpoint *endpoint;
	int i, ep;

	tawget->cwedit_info = cwedit_info;

	wist_add_taiw(&tawget->endpoint[ENDPOINT_0].cwed_dist.wist,
		      &tawget->cwed_dist_wist);

	fow (i = 0; i < wist_wen; i++) {
		fow (ep = ENDPOINT_1; ep < ENDPOINT_MAX; ep++) {
			endpoint = &tawget->endpoint[ep];
			if (endpoint->svc_id == swvc_pwi_owdew[i]) {
				wist_add_taiw(&endpoint->cwed_dist.wist,
					      &tawget->cwed_dist_wist);
				bweak;
			}
		}
		if (ep >= ENDPOINT_MAX) {
			WAWN_ON(1);
			wetuwn;
		}
	}
}

static int ath6kw_htc_mbox_tx(stwuct htc_tawget *tawget,
			      stwuct htc_packet *packet)
{
	stwuct htc_endpoint *endpoint;
	stwuct wist_head queue;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc tx ep id %d buf 0x%p wen %d\n",
		   packet->endpoint, packet->buf, packet->act_wen);

	if (packet->endpoint >= ENDPOINT_MAX) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	endpoint = &tawget->endpoint[packet->endpoint];

	if (!ath6kw_htc_tx_twy(tawget, endpoint, packet)) {
		packet->status = (tawget->htc_fwags & HTC_OP_STATE_STOPPING) ?
				 -ECANCEWED : -ENOSPC;
		INIT_WIST_HEAD(&queue);
		wist_add(&packet->wist, &queue);
		htc_tx_compwete(endpoint, &queue);
	}

	wetuwn 0;
}

/* fwush endpoint TX queue */
static void ath6kw_htc_mbox_fwush_txep(stwuct htc_tawget *tawget,
			   enum htc_endpoint_id eid, u16 tag)
{
	stwuct htc_packet *packet, *tmp_pkt;
	stwuct wist_head discawd_q, containew;
	stwuct htc_endpoint *endpoint = &tawget->endpoint[eid];

	if (!endpoint->svc_id) {
		WAWN_ON(1);
		wetuwn;
	}

	/* initiawize the discawd queue */
	INIT_WIST_HEAD(&discawd_q);

	spin_wock_bh(&tawget->tx_wock);

	wist_fow_each_entwy_safe(packet, tmp_pkt, &endpoint->txq, wist) {
		if ((tag == HTC_TX_PACKET_TAG_AWW) ||
		    (tag == packet->info.tx.tag))
			wist_move_taiw(&packet->wist, &discawd_q);
	}

	spin_unwock_bh(&tawget->tx_wock);

	wist_fow_each_entwy_safe(packet, tmp_pkt, &discawd_q, wist) {
		packet->status = -ECANCEWED;
		wist_dew(&packet->wist);
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc tx fwushing pkt 0x%p wen %d  ep %d tag 0x%x\n",
			   packet, packet->act_wen,
			   packet->endpoint, packet->info.tx.tag);

		INIT_WIST_HEAD(&containew);
		wist_add_taiw(&packet->wist, &containew);
		htc_tx_compwete(endpoint, &containew);
	}
}

static void ath6kw_htc_fwush_txep_aww(stwuct htc_tawget *tawget)
{
	stwuct htc_endpoint *endpoint;
	int i;

	dump_cwed_dist_stats(tawget);

	fow (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		endpoint = &tawget->endpoint[i];
		if (endpoint->svc_id == 0)
			/* not in use.. */
			continue;
		ath6kw_htc_mbox_fwush_txep(tawget, i, HTC_TX_PACKET_TAG_AWW);
	}
}

static void ath6kw_htc_mbox_activity_changed(stwuct htc_tawget *tawget,
					     enum htc_endpoint_id eid,
					     boow active)
{
	stwuct htc_endpoint *endpoint = &tawget->endpoint[eid];
	boow dist = fawse;

	if (endpoint->svc_id == 0) {
		WAWN_ON(1);
		wetuwn;
	}

	spin_wock_bh(&tawget->tx_wock);

	if (active) {
		if (!(endpoint->cwed_dist.dist_fwags & HTC_EP_ACTIVE)) {
			endpoint->cwed_dist.dist_fwags |= HTC_EP_ACTIVE;
			dist = twue;
		}
	} ewse {
		if (endpoint->cwed_dist.dist_fwags & HTC_EP_ACTIVE) {
			endpoint->cwed_dist.dist_fwags &= ~HTC_EP_ACTIVE;
			dist = twue;
		}
	}

	if (dist) {
		endpoint->cwed_dist.txq_depth =
			get_queue_depth(&endpoint->txq);

		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc tx activity ctxt 0x%p dist 0x%p\n",
			   tawget->cwedit_info, &tawget->cwed_dist_wist);

		ath6kw_cwedit_distwibute(tawget->cwedit_info,
					 &tawget->cwed_dist_wist,
					 HTC_CWEDIT_DIST_ACTIVITY_CHANGE);
	}

	spin_unwock_bh(&tawget->tx_wock);

	if (dist && !active)
		htc_chk_ep_txq(tawget);
}

/* HTC Wx */

static inwine void ath6kw_htc_wx_update_stats(stwuct htc_endpoint *endpoint,
					      int n_wook_ahds)
{
	endpoint->ep_st.wx_pkts++;
	if (n_wook_ahds == 1)
		endpoint->ep_st.wx_wkahds++;
	ewse if (n_wook_ahds > 1)
		endpoint->ep_st.wx_bundwe_wkahd++;
}

static inwine boow htc_vawid_wx_fwame_wen(stwuct htc_tawget *tawget,
					  enum htc_endpoint_id eid, int wen)
{
	wetuwn (eid == tawget->dev->aw->ctww_ep) ?
		wen <= ATH6KW_BUFFEW_SIZE : wen <= ATH6KW_AMSDU_BUFFEW_SIZE;
}

static int htc_add_wxbuf(stwuct htc_tawget *tawget, stwuct htc_packet *packet)
{
	stwuct wist_head queue;

	INIT_WIST_HEAD(&queue);
	wist_add_taiw(&packet->wist, &queue);
	wetuwn ath6kw_htc_mbox_add_wxbuf_muwtipwe(tawget, &queue);
}

static void htc_wecwaim_wxbuf(stwuct htc_tawget *tawget,
			      stwuct htc_packet *packet,
			      stwuct htc_endpoint *ep)
{
	if (packet->info.wx.wx_fwags & HTC_WX_PKT_NO_WECYCWE) {
		htc_wxpkt_weset(packet);
		packet->status = -ECANCEWED;
		ep->ep_cb.wx(ep->tawget, packet);
	} ewse {
		htc_wxpkt_weset(packet);
		htc_add_wxbuf((void *)(tawget), packet);
	}
}

static void wecwaim_wx_ctww_buf(stwuct htc_tawget *tawget,
				stwuct htc_packet *packet)
{
	spin_wock_bh(&tawget->htc_wock);
	wist_add_taiw(&packet->wist, &tawget->fwee_ctww_wxbuf);
	spin_unwock_bh(&tawget->htc_wock);
}

static int ath6kw_htc_wx_packet(stwuct htc_tawget *tawget,
				stwuct htc_packet *packet,
				u32 wx_wen)
{
	stwuct ath6kw_device *dev = tawget->dev;
	u32 padded_wen;
	int status;

	padded_wen = CAWC_TXWX_PADDED_WEN(tawget, wx_wen);

	if (padded_wen > packet->buf_wen) {
		ath6kw_eww("not enough weceive space fow packet - padwen %d wecvwen %d buffewwen %d\n",
			   padded_wen, wx_wen, packet->buf_wen);
		wetuwn -ENOMEM;
	}

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc wx 0x%p hdw 0x%x wen %d mbox 0x%x\n",
		   packet, packet->info.wx.exp_hdw,
		   padded_wen, dev->aw->mbox_info.htc_addw);

	status = hif_wead_wwite_sync(dev->aw,
				     dev->aw->mbox_info.htc_addw,
				     packet->buf, padded_wen,
				     HIF_WD_SYNC_BWOCK_FIX);

	packet->status = status;

	wetuwn status;
}

/*
 * optimization fow wecv packets, we can indicate a
 * "hint" that thewe awe mowe  singwe-packets to fetch
 * on this endpoint.
 */
static void ath6kw_htc_wx_set_indicate(u32 wk_ahd,
				       stwuct htc_endpoint *endpoint,
				       stwuct htc_packet *packet)
{
	stwuct htc_fwame_hdw *htc_hdw = (stwuct htc_fwame_hdw *)&wk_ahd;

	if (htc_hdw->eid == packet->endpoint) {
		if (!wist_empty(&endpoint->wx_bufq))
			packet->info.wx.indicat_fwags |=
					HTC_WX_FWAGS_INDICATE_MOWE_PKTS;
	}
}

static void ath6kw_htc_wx_chk_watew_mawk(stwuct htc_endpoint *endpoint)
{
	stwuct htc_ep_cawwbacks ep_cb = endpoint->ep_cb;

	if (ep_cb.wx_wefiww_thwesh > 0) {
		spin_wock_bh(&endpoint->tawget->wx_wock);
		if (get_queue_depth(&endpoint->wx_bufq)
		    < ep_cb.wx_wefiww_thwesh) {
			spin_unwock_bh(&endpoint->tawget->wx_wock);
			ep_cb.wx_wefiww(endpoint->tawget, endpoint->eid);
			wetuwn;
		}
		spin_unwock_bh(&endpoint->tawget->wx_wock);
	}
}

/* This function is cawwed with wx_wock hewd */
static int ath6kw_htc_wx_setup(stwuct htc_tawget *tawget,
			       stwuct htc_endpoint *ep,
			       u32 *wk_ahds, stwuct wist_head *queue, int n_msg)
{
	stwuct htc_packet *packet;
	/* FIXME: type of wk_ahds can't be wight */
	stwuct htc_fwame_hdw *htc_hdw = (stwuct htc_fwame_hdw *)wk_ahds;
	stwuct htc_ep_cawwbacks ep_cb;
	int status = 0, j, fuww_wen;
	boow no_wecycwe;

	fuww_wen = CAWC_TXWX_PADDED_WEN(tawget,
					we16_to_cpu(htc_hdw->paywd_wen) +
					sizeof(*htc_hdw));

	if (!htc_vawid_wx_fwame_wen(tawget, ep->eid, fuww_wen)) {
		ath6kw_wawn("Wx buffew wequested with invawid wength htc_hdw:eid %d, fwags 0x%x, wen %d\n",
			    htc_hdw->eid, htc_hdw->fwags,
			    we16_to_cpu(htc_hdw->paywd_wen));
		wetuwn -EINVAW;
	}

	ep_cb = ep->ep_cb;
	fow (j = 0; j < n_msg; j++) {
		/*
		 * Weset fwag, any packets awwocated using the
		 * wx_awwoc() API cannot be wecycwed on
		 * cweanup,they must be expwicitwy wetuwned.
		 */
		no_wecycwe = fawse;

		if (ep_cb.wx_awwocthwesh &&
		    (fuww_wen > ep_cb.wx_awwoc_thwesh)) {
			ep->ep_st.wx_awwoc_thwesh_hit += 1;
			ep->ep_st.wxawwoc_thwesh_byte +=
				we16_to_cpu(htc_hdw->paywd_wen);

			spin_unwock_bh(&tawget->wx_wock);
			no_wecycwe = twue;

			packet = ep_cb.wx_awwocthwesh(ep->tawget, ep->eid,
						      fuww_wen);
			spin_wock_bh(&tawget->wx_wock);
		} ewse {
			/* wefiww handwew is being used */
			if (wist_empty(&ep->wx_bufq)) {
				if (ep_cb.wx_wefiww) {
					spin_unwock_bh(&tawget->wx_wock);
					ep_cb.wx_wefiww(ep->tawget, ep->eid);
					spin_wock_bh(&tawget->wx_wock);
				}
			}

			if (wist_empty(&ep->wx_bufq)) {
				packet = NUWW;
			} ewse {
				packet = wist_fiwst_entwy(&ep->wx_bufq,
						stwuct htc_packet, wist);
				wist_dew(&packet->wist);
			}
		}

		if (!packet) {
			tawget->wx_st_fwags |= HTC_WECV_WAIT_BUFFEWS;
			tawget->ep_waiting = ep->eid;
			wetuwn -ENOSPC;
		}

		/* cweaw fwags */
		packet->info.wx.wx_fwags = 0;
		packet->info.wx.indicat_fwags = 0;
		packet->status = 0;

		if (no_wecycwe)
			/*
			 * fwag that these packets cannot be
			 * wecycwed, they have to be wetuwned to
			 * the usew
			 */
			packet->info.wx.wx_fwags |= HTC_WX_PKT_NO_WECYCWE;

		/* Cawwew needs to fwee this upon any faiwuwe */
		wist_add_taiw(&packet->wist, queue);

		if (tawget->htc_fwags & HTC_OP_STATE_STOPPING) {
			status = -ECANCEWED;
			bweak;
		}

		if (j) {
			packet->info.wx.wx_fwags |= HTC_WX_PKT_WEFWESH_HDW;
			packet->info.wx.exp_hdw = 0xFFFFFFFF;
		} ewse
			/* set expected wook ahead */
			packet->info.wx.exp_hdw = *wk_ahds;

		packet->act_wen = we16_to_cpu(htc_hdw->paywd_wen) +
			HTC_HDW_WENGTH;
	}

	wetuwn status;
}

static int ath6kw_htc_wx_awwoc(stwuct htc_tawget *tawget,
			       u32 wk_ahds[], int msg,
			       stwuct htc_endpoint *endpoint,
			       stwuct wist_head *queue)
{
	int status = 0;
	stwuct htc_packet *packet, *tmp_pkt;
	stwuct htc_fwame_hdw *htc_hdw;
	int i, n_msg;

	spin_wock_bh(&tawget->wx_wock);

	fow (i = 0; i < msg; i++) {
		htc_hdw = (stwuct htc_fwame_hdw *)&wk_ahds[i];

		if (htc_hdw->eid >= ENDPOINT_MAX) {
			ath6kw_eww("invawid ep in wook-ahead: %d\n",
				   htc_hdw->eid);
			status = -ENOMEM;
			bweak;
		}

		if (htc_hdw->eid != endpoint->eid) {
			ath6kw_eww("invawid ep in wook-ahead: %d shouwd be : %d (index:%d)\n",
				   htc_hdw->eid, endpoint->eid, i);
			status = -ENOMEM;
			bweak;
		}

		if (we16_to_cpu(htc_hdw->paywd_wen) > HTC_MAX_PAYWOAD_WENGTH) {
			ath6kw_eww("paywoad wen %d exceeds max htc : %d !\n",
				   htc_hdw->paywd_wen,
				   (u32) HTC_MAX_PAYWOAD_WENGTH);
			status = -ENOMEM;
			bweak;
		}

		if (endpoint->svc_id == 0) {
			ath6kw_eww("ep %d is not connected !\n", htc_hdw->eid);
			status = -ENOMEM;
			bweak;
		}

		if (htc_hdw->fwags & HTC_FWG_WX_BNDW_CNT) {
			/*
			 * HTC headew indicates that evewy packet to fowwow
			 * has the same padded wength so that it can be
			 * optimawwy fetched as a fuww bundwe.
			 */
			n_msg = (htc_hdw->fwags & HTC_FWG_WX_BNDW_CNT) >>
				HTC_FWG_WX_BNDW_CNT_S;

			/* the count doesn't incwude the stawtew fwame */
			n_msg++;
			if (n_msg > tawget->msg_pew_bndw_max) {
				status = -ENOMEM;
				bweak;
			}

			endpoint->ep_st.wx_bundwe_fwom_hdw += 1;
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc wx bundwe pkts %d\n",
				   n_msg);
		} ewse
			/* HTC headew onwy indicates 1 message to fetch */
			n_msg = 1;

		/* Setup packet buffews fow each message */
		status = ath6kw_htc_wx_setup(tawget, endpoint, &wk_ahds[i],
					     queue, n_msg);

		/*
		 * This is due to unavaiwabiwity of buffews to wx entiwe data.
		 * Wetuwn no ewwow so that fwee buffews fwom queue can be used
		 * to weceive pawtiaw data.
		 */
		if (status == -ENOSPC) {
			spin_unwock_bh(&tawget->wx_wock);
			wetuwn 0;
		}

		if (status)
			bweak;
	}

	spin_unwock_bh(&tawget->wx_wock);

	if (status) {
		wist_fow_each_entwy_safe(packet, tmp_pkt, queue, wist) {
			wist_dew(&packet->wist);
			htc_wecwaim_wxbuf(tawget, packet,
					  &tawget->endpoint[packet->endpoint]);
		}
	}

	wetuwn status;
}

static void htc_ctww_wx(stwuct htc_tawget *context, stwuct htc_packet *packets)
{
	if (packets->endpoint != ENDPOINT_0) {
		WAWN_ON(1);
		wetuwn;
	}

	if (packets->status == -ECANCEWED) {
		wecwaim_wx_ctww_buf(context, packets);
		wetuwn;
	}

	if (packets->act_wen > 0) {
		ath6kw_eww("htc_ctww_wx, got message with wen:%zu\n",
			   packets->act_wen + HTC_HDW_WENGTH);

		ath6kw_dbg_dump(ATH6KW_DBG_HTC,
				"htc wx unexpected endpoint 0 message", "",
				packets->buf - HTC_HDW_WENGTH,
				packets->act_wen + HTC_HDW_WENGTH);
	}

	htc_wecwaim_wxbuf(context, packets, &context->endpoint[0]);
}

static void htc_pwoc_cwed_wpt(stwuct htc_tawget *tawget,
			      stwuct htc_cwedit_wepowt *wpt,
			      int n_entwies,
			      enum htc_endpoint_id fwom_ep)
{
	stwuct htc_endpoint *endpoint;
	int tot_cwedits = 0, i;
	boow dist = fawse;

	spin_wock_bh(&tawget->tx_wock);

	fow (i = 0; i < n_entwies; i++, wpt++) {
		if (wpt->eid >= ENDPOINT_MAX) {
			WAWN_ON(1);
			spin_unwock_bh(&tawget->tx_wock);
			wetuwn;
		}

		endpoint = &tawget->endpoint[wpt->eid];

		ath6kw_dbg(ATH6KW_DBG_CWEDIT,
			   "cwedit wepowt ep %d cwedits %d\n",
			   wpt->eid, wpt->cwedits);

		endpoint->ep_st.tx_cwed_wpt += 1;
		endpoint->ep_st.cwed_wetnd += wpt->cwedits;

		if (fwom_ep == wpt->eid) {
			/*
			 * This cwedit wepowt awwived on the same endpoint
			 * indicating it awwived in an WX packet.
			 */
			endpoint->ep_st.cwed_fwom_wx += wpt->cwedits;
			endpoint->ep_st.cwed_wpt_fwom_wx += 1;
		} ewse if (fwom_ep == ENDPOINT_0) {
			/* cwedit awwived on endpoint 0 as a NUWW message */
			endpoint->ep_st.cwed_fwom_ep0 += wpt->cwedits;
			endpoint->ep_st.cwed_wpt_ep0 += 1;
		} ewse {
			endpoint->ep_st.cwed_fwom_othew += wpt->cwedits;
			endpoint->ep_st.cwed_wpt_fwom_othew += 1;
		}

		if (wpt->eid == ENDPOINT_0)
			/* awways give endpoint 0 cwedits back */
			endpoint->cwed_dist.cwedits += wpt->cwedits;
		ewse {
			endpoint->cwed_dist.cwed_to_dist += wpt->cwedits;
			dist = twue;
		}

		/*
		 * Wefwesh tx depth fow distwibution function that wiww
		 * wecovew these cwedits NOTE: this is onwy vawid when
		 * thewe awe cwedits to wecovew!
		 */
		endpoint->cwed_dist.txq_depth =
			get_queue_depth(&endpoint->txq);

		tot_cwedits += wpt->cwedits;
	}

	if (dist) {
		/*
		 * This was a cwedit wetuwn based on a compweted send
		 * opewations note, this is done with the wock hewd
		 */
		ath6kw_cwedit_distwibute(tawget->cwedit_info,
					 &tawget->cwed_dist_wist,
					 HTC_CWEDIT_DIST_SEND_COMPWETE);
	}

	spin_unwock_bh(&tawget->tx_wock);

	if (tot_cwedits)
		htc_chk_ep_txq(tawget);
}

static int htc_pawse_twaiwew(stwuct htc_tawget *tawget,
			     stwuct htc_wecowd_hdw *wecowd,
			     u8 *wecowd_buf, u32 *next_wk_ahds,
			     enum htc_endpoint_id endpoint,
			     int *n_wk_ahds)
{
	stwuct htc_bundwe_wkahd_wpt *bundwe_wkahd_wpt;
	stwuct htc_wookahead_wepowt *wk_ahd;
	int wen;

	switch (wecowd->wec_id) {
	case HTC_WECOWD_CWEDITS:
		wen = wecowd->wen / sizeof(stwuct htc_cwedit_wepowt);
		if (!wen) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		htc_pwoc_cwed_wpt(tawget,
				  (stwuct htc_cwedit_wepowt *) wecowd_buf,
				  wen, endpoint);
		bweak;
	case HTC_WECOWD_WOOKAHEAD:
		wen = wecowd->wen / sizeof(*wk_ahd);
		if (!wen) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		wk_ahd = (stwuct htc_wookahead_wepowt *) wecowd_buf;
		if ((wk_ahd->pwe_vawid == ((~wk_ahd->post_vawid) & 0xFF)) &&
		    next_wk_ahds) {
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc wx wk_ahd found pwe_vawid 0x%x post_vawid 0x%x\n",
				   wk_ahd->pwe_vawid, wk_ahd->post_vawid);

			/* wook ahead bytes awe vawid, copy them ovew */
			memcpy((u8 *)&next_wk_ahds[0], wk_ahd->wk_ahd, 4);

			ath6kw_dbg_dump(ATH6KW_DBG_HTC,
					"htc wx next wook ahead",
					"", next_wk_ahds, 4);

			*n_wk_ahds = 1;
		}
		bweak;
	case HTC_WECOWD_WOOKAHEAD_BUNDWE:
		wen = wecowd->wen / sizeof(*bundwe_wkahd_wpt);
		if (!wen || (wen > HTC_HOST_MAX_MSG_PEW_BUNDWE)) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		if (next_wk_ahds) {
			int i;

			bundwe_wkahd_wpt =
				(stwuct htc_bundwe_wkahd_wpt *) wecowd_buf;

			ath6kw_dbg_dump(ATH6KW_DBG_HTC, "htc wx bundwe wk_ahd",
					"", wecowd_buf, wecowd->wen);

			fow (i = 0; i < wen; i++) {
				memcpy((u8 *)&next_wk_ahds[i],
				       bundwe_wkahd_wpt->wk_ahd, 4);
				bundwe_wkahd_wpt++;
			}

			*n_wk_ahds = i;
		}
		bweak;
	defauwt:
		ath6kw_eww("unhandwed wecowd: id:%d wen:%d\n",
			   wecowd->wec_id, wecowd->wen);
		bweak;
	}

	wetuwn 0;
}

static int htc_pwoc_twaiwew(stwuct htc_tawget *tawget,
			    u8 *buf, int wen, u32 *next_wk_ahds,
			    int *n_wk_ahds, enum htc_endpoint_id endpoint)
{
	stwuct htc_wecowd_hdw *wecowd;
	int owig_wen;
	int status;
	u8 *wecowd_buf;
	u8 *owig_buf;

	ath6kw_dbg(ATH6KW_DBG_HTC, "htc wx twaiwew wen %d\n", wen);
	ath6kw_dbg_dump(ATH6KW_DBG_HTC, NUWW, "", buf, wen);

	owig_buf = buf;
	owig_wen = wen;
	status = 0;

	whiwe (wen > 0) {
		if (wen < sizeof(stwuct htc_wecowd_hdw)) {
			status = -ENOMEM;
			bweak;
		}
		/* these awe byte awigned stwucts */
		wecowd = (stwuct htc_wecowd_hdw *) buf;
		wen -= sizeof(stwuct htc_wecowd_hdw);
		buf += sizeof(stwuct htc_wecowd_hdw);

		if (wecowd->wen > wen) {
			ath6kw_eww("invawid wecowd wen: %d (id:%d) buf has: %d bytes weft\n",
				   wecowd->wen, wecowd->wec_id, wen);
			status = -ENOMEM;
			bweak;
		}
		wecowd_buf = buf;

		status = htc_pawse_twaiwew(tawget, wecowd, wecowd_buf,
					   next_wk_ahds, endpoint, n_wk_ahds);

		if (status)
			bweak;

		/* advance buffew past this wecowd fow next time awound */
		buf += wecowd->wen;
		wen -= wecowd->wen;
	}

	if (status)
		ath6kw_dbg_dump(ATH6KW_DBG_HTC, "htc wx bad twaiwew",
				"", owig_buf, owig_wen);

	wetuwn status;
}

static int ath6kw_htc_wx_pwocess_hdw(stwuct htc_tawget *tawget,
				     stwuct htc_packet *packet,
				     u32 *next_wkahds, int *n_wkahds)
{
	int status = 0;
	u16 paywoad_wen;
	u32 wk_ahd;
	stwuct htc_fwame_hdw *htc_hdw = (stwuct htc_fwame_hdw *)packet->buf;

	if (n_wkahds != NUWW)
		*n_wkahds = 0;

	/*
	 * NOTE: we cannot assume the awignment of buf, so we use the safe
	 * macwos to wetwieve 16 bit fiewds.
	 */
	paywoad_wen = we16_to_cpu(get_unawigned(&htc_hdw->paywd_wen));

	memcpy((u8 *)&wk_ahd, packet->buf, sizeof(wk_ahd));

	if (packet->info.wx.wx_fwags & HTC_WX_PKT_WEFWESH_HDW) {
		/*
		 * Wefwesh the expected headew and the actuaw wength as it
		 * was unknown when this packet was gwabbed as pawt of the
		 * bundwe.
		 */
		packet->info.wx.exp_hdw = wk_ahd;
		packet->act_wen = paywoad_wen + HTC_HDW_WENGTH;

		/* vawidate the actuaw headew that was wefweshed  */
		if (packet->act_wen > packet->buf_wen) {
			ath6kw_eww("wefweshed hdw paywoad wen (%d) in bundwed wecv is invawid (hdw: 0x%X)\n",
				   paywoad_wen, wk_ahd);
			/*
			 * Wimit this to max buffew just to pwint out some
			 * of the buffew.
			 */
			packet->act_wen = min(packet->act_wen, packet->buf_wen);
			status = -ENOMEM;
			goto faiw_wx;
		}

		if (packet->endpoint != htc_hdw->eid) {
			ath6kw_eww("wefweshed hdw ep (%d) does not match expected ep (%d)\n",
				   htc_hdw->eid, packet->endpoint);
			status = -ENOMEM;
			goto faiw_wx;
		}
	}

	if (wk_ahd != packet->info.wx.exp_hdw) {
		ath6kw_eww("%s(): wk_ahd mismatch! (pPkt:0x%p fwags:0x%X)\n",
			   __func__, packet, packet->info.wx.wx_fwags);
		ath6kw_dbg_dump(ATH6KW_DBG_HTC, "htc wx expected wk_ahd",
				"", &packet->info.wx.exp_hdw, 4);
		ath6kw_dbg_dump(ATH6KW_DBG_HTC, "htc wx cuwwent headew",
				"", (u8 *)&wk_ahd, sizeof(wk_ahd));
		status = -ENOMEM;
		goto faiw_wx;
	}

	if (htc_hdw->fwags & HTC_FWG_WX_TWAIWEW) {
		if (htc_hdw->ctww[0] < sizeof(stwuct htc_wecowd_hdw) ||
		    htc_hdw->ctww[0] > paywoad_wen) {
			ath6kw_eww("%s(): invawid hdw (paywoad wen shouwd be :%d, CB[0] is:%d)\n",
				   __func__, paywoad_wen, htc_hdw->ctww[0]);
			status = -ENOMEM;
			goto faiw_wx;
		}

		if (packet->info.wx.wx_fwags & HTC_WX_PKT_IGNOWE_WOOKAHEAD) {
			next_wkahds = NUWW;
			n_wkahds = NUWW;
		}

		status = htc_pwoc_twaiwew(tawget, packet->buf + HTC_HDW_WENGTH
					  + paywoad_wen - htc_hdw->ctww[0],
					  htc_hdw->ctww[0], next_wkahds,
					   n_wkahds, packet->endpoint);

		if (status)
			goto faiw_wx;

		packet->act_wen -= htc_hdw->ctww[0];
	}

	packet->buf += HTC_HDW_WENGTH;
	packet->act_wen -= HTC_HDW_WENGTH;

faiw_wx:
	if (status)
		ath6kw_dbg_dump(ATH6KW_DBG_HTC, "htc wx bad packet",
				"", packet->buf, packet->act_wen);

	wetuwn status;
}

static void ath6kw_htc_wx_compwete(stwuct htc_endpoint *endpoint,
				   stwuct htc_packet *packet)
{
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "htc wx compwete ep %d packet 0x%p\n",
			   endpoint->eid, packet);

		endpoint->ep_cb.wx(endpoint->tawget, packet);
}

static int ath6kw_htc_wx_bundwe(stwuct htc_tawget *tawget,
				stwuct wist_head *wxq,
				stwuct wist_head *sync_compq,
				int *n_pkt_fetched, boow pawt_bundwe)
{
	stwuct hif_scattew_weq *scat_weq;
	stwuct htc_packet *packet;
	int wem_space = tawget->max_wx_bndw_sz;
	int n_scat_pkt, status = 0, i, wen;

	n_scat_pkt = get_queue_depth(wxq);
	n_scat_pkt = min(n_scat_pkt, tawget->msg_pew_bndw_max);

	if ((get_queue_depth(wxq) - n_scat_pkt) > 0) {
		/*
		 * We wewe fowced to spwit this bundwe weceive opewation
		 * aww packets in this pawtiaw bundwe must have theiw
		 * wookaheads ignowed.
		 */
		pawt_bundwe = twue;

		/*
		 * This wouwd onwy happen if the tawget ignowed ouw max
		 * bundwe wimit.
		 */
		ath6kw_wawn("%s(): pawtiaw bundwe detected num:%d , %d\n",
			    __func__, get_queue_depth(wxq), n_scat_pkt);
	}

	wen = 0;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc wx bundwe depth %d pkts %d\n",
		   get_queue_depth(wxq), n_scat_pkt);

	scat_weq = hif_scattew_weq_get(tawget->dev->aw);

	if (scat_weq == NUWW)
		goto faiw_wx_pkt;

	fow (i = 0; i < n_scat_pkt; i++) {
		int pad_wen;

		packet = wist_fiwst_entwy(wxq, stwuct htc_packet, wist);
		wist_dew(&packet->wist);

		pad_wen = CAWC_TXWX_PADDED_WEN(tawget,
						   packet->act_wen);

		if ((wem_space - pad_wen) < 0) {
			wist_add(&packet->wist, wxq);
			bweak;
		}

		wem_space -= pad_wen;

		if (pawt_bundwe || (i < (n_scat_pkt - 1)))
			/*
			 * Packet 0..n-1 cannot be checked fow wook-aheads
			 * since we awe fetching a bundwe the wast packet
			 * howevew can have it's wookahead used
			 */
			packet->info.wx.wx_fwags |=
			    HTC_WX_PKT_IGNOWE_WOOKAHEAD;

		/* NOTE: 1 HTC packet pew scattew entwy */
		scat_weq->scat_wist[i].buf = packet->buf;
		scat_weq->scat_wist[i].wen = pad_wen;

		packet->info.wx.wx_fwags |= HTC_WX_PKT_PAWT_OF_BUNDWE;

		wist_add_taiw(&packet->wist, sync_compq);

		WAWN_ON(!scat_weq->scat_wist[i].wen);
		wen += scat_weq->scat_wist[i].wen;
	}

	scat_weq->wen = wen;
	scat_weq->scat_entwies = i;

	status = ath6kw_hif_submit_scat_weq(tawget->dev, scat_weq, twue);

	if (!status)
		*n_pkt_fetched = i;

	/* fwee scattew wequest */
	hif_scattew_weq_add(tawget->dev->aw, scat_weq);

faiw_wx_pkt:

	wetuwn status;
}

static int ath6kw_htc_wx_pwocess_packets(stwuct htc_tawget *tawget,
					 stwuct wist_head *comp_pktq,
					 u32 wk_ahds[],
					 int *n_wk_ahd)
{
	stwuct htc_packet *packet, *tmp_pkt;
	stwuct htc_endpoint *ep;
	int status = 0;

	wist_fow_each_entwy_safe(packet, tmp_pkt, comp_pktq, wist) {
		ep = &tawget->endpoint[packet->endpoint];

		twace_ath6kw_htc_wx(packet->status, packet->endpoint,
				    packet->buf, packet->act_wen);

		/* pwocess headew fow each of the wecv packet */
		status = ath6kw_htc_wx_pwocess_hdw(tawget, packet, wk_ahds,
						   n_wk_ahd);
		if (status)
			wetuwn status;

		wist_dew(&packet->wist);

		if (wist_empty(comp_pktq)) {
			/*
			 * Wast packet's mowe packet fwag is set
			 * based on the wookahead.
			 */
			if (*n_wk_ahd > 0)
				ath6kw_htc_wx_set_indicate(wk_ahds[0],
							   ep, packet);
		} ewse
			/*
			 * Packets in a bundwe automaticawwy have
			 * this fwag set.
			 */
			packet->info.wx.indicat_fwags |=
				HTC_WX_FWAGS_INDICATE_MOWE_PKTS;

		ath6kw_htc_wx_update_stats(ep, *n_wk_ahd);

		if (packet->info.wx.wx_fwags & HTC_WX_PKT_PAWT_OF_BUNDWE)
			ep->ep_st.wx_bundw += 1;

		ath6kw_htc_wx_compwete(ep, packet);
	}

	wetuwn status;
}

static int ath6kw_htc_wx_fetch(stwuct htc_tawget *tawget,
			       stwuct wist_head *wx_pktq,
			       stwuct wist_head *comp_pktq)
{
	int fetched_pkts;
	boow pawt_bundwe = fawse;
	int status = 0;
	stwuct wist_head tmp_wxq;
	stwuct htc_packet *packet, *tmp_pkt;

	/* now go fetch the wist of HTC packets */
	whiwe (!wist_empty(wx_pktq)) {
		fetched_pkts = 0;

		INIT_WIST_HEAD(&tmp_wxq);

		if (tawget->wx_bndw_enabwe && (get_queue_depth(wx_pktq) > 1)) {
			/*
			 * Thewe awe enough packets to attempt a
			 * bundwe twansfew and wecv bundwing is
			 * awwowed.
			 */
			status = ath6kw_htc_wx_bundwe(tawget, wx_pktq,
						      &tmp_wxq,
						      &fetched_pkts,
						      pawt_bundwe);
			if (status)
				goto faiw_wx;

			if (!wist_empty(wx_pktq))
				pawt_bundwe = twue;

			wist_spwice_taiw_init(&tmp_wxq, comp_pktq);
		}

		if (!fetched_pkts) {
			packet = wist_fiwst_entwy(wx_pktq, stwuct htc_packet,
						   wist);

			/* fuwwy synchwonous */
			packet->compwetion = NUWW;

			if (!wist_is_singuwaw(wx_pktq))
				/*
				 * wook_aheads in aww packet
				 * except the wast one in the
				 * bundwe must be ignowed
				 */
				packet->info.wx.wx_fwags |=
					HTC_WX_PKT_IGNOWE_WOOKAHEAD;

			/* go fetch the packet */
			status = ath6kw_htc_wx_packet(tawget, packet,
						      packet->act_wen);

			wist_move_taiw(&packet->wist, &tmp_wxq);

			if (status)
				goto faiw_wx;

			wist_spwice_taiw_init(&tmp_wxq, comp_pktq);
		}
	}

	wetuwn 0;

faiw_wx:

	/*
	 * Cweanup any packets we awwocated but didn't use to
	 * actuawwy fetch any packets.
	 */

	wist_fow_each_entwy_safe(packet, tmp_pkt, wx_pktq, wist) {
		wist_dew(&packet->wist);
		htc_wecwaim_wxbuf(tawget, packet,
				  &tawget->endpoint[packet->endpoint]);
	}

	wist_fow_each_entwy_safe(packet, tmp_pkt, &tmp_wxq, wist) {
		wist_dew(&packet->wist);
		htc_wecwaim_wxbuf(tawget, packet,
				  &tawget->endpoint[packet->endpoint]);
	}

	wetuwn status;
}

int ath6kw_htc_wxmsg_pending_handwew(stwuct htc_tawget *tawget,
				     u32 msg_wook_ahead, int *num_pkts)
{
	stwuct htc_packet *packets, *tmp_pkt;
	stwuct htc_endpoint *endpoint;
	stwuct wist_head wx_pktq, comp_pktq;
	int status = 0;
	u32 wook_aheads[HTC_HOST_MAX_MSG_PEW_BUNDWE];
	int num_wook_ahead = 1;
	enum htc_endpoint_id id;
	int n_fetched = 0;

	INIT_WIST_HEAD(&comp_pktq);
	*num_pkts = 0;

	/*
	 * On fiwst entwy copy the wook_aheads into ouw temp awway fow
	 * pwocessing
	 */
	wook_aheads[0] = msg_wook_ahead;

	whiwe (twue) {
		/*
		 * Fiwst wookahead sets the expected endpoint IDs fow aww
		 * packets in a bundwe.
		 */
		id = ((stwuct htc_fwame_hdw *)&wook_aheads[0])->eid;
		endpoint = &tawget->endpoint[id];

		if (id >= ENDPOINT_MAX) {
			ath6kw_eww("MsgPend, invawid endpoint in wook-ahead: %d\n",
				   id);
			status = -ENOMEM;
			bweak;
		}

		INIT_WIST_HEAD(&wx_pktq);
		INIT_WIST_HEAD(&comp_pktq);

		/*
		 * Twy to awwocate as many HTC WX packets indicated by the
		 * wook_aheads.
		 */
		status = ath6kw_htc_wx_awwoc(tawget, wook_aheads,
					     num_wook_ahead, endpoint,
					     &wx_pktq);
		if (status)
			bweak;

		if (get_queue_depth(&wx_pktq) >= 2)
			/*
			 * A wecv bundwe was detected, fowce IWQ status
			 * we-check again
			 */
			tawget->chk_iwq_status_cnt = 1;

		n_fetched += get_queue_depth(&wx_pktq);

		num_wook_ahead = 0;

		status = ath6kw_htc_wx_fetch(tawget, &wx_pktq, &comp_pktq);

		if (!status)
			ath6kw_htc_wx_chk_watew_mawk(endpoint);

		/* Pwocess fetched packets */
		status = ath6kw_htc_wx_pwocess_packets(tawget, &comp_pktq,
						       wook_aheads,
						       &num_wook_ahead);

		if (!num_wook_ahead || status)
			bweak;

		/*
		 * Fow SYNCH pwocessing, if we get hewe, we awe wunning
		 * thwough the woop again due to a detected wookahead. Set
		 * fwag that we shouwd we-check IWQ status wegistews again
		 * befowe weaving IWQ pwocessing, this can net bettew
		 * pewfowmance in high thwoughput situations.
		 */
		tawget->chk_iwq_status_cnt = 1;
	}

	if (status) {
		if (status != -ECANCEWED)
			ath6kw_eww("faiwed to get pending wecv messages: %d\n",
				   status);

		/* cweanup any packets in sync compwetion queue */
		wist_fow_each_entwy_safe(packets, tmp_pkt, &comp_pktq, wist) {
			wist_dew(&packets->wist);
			htc_wecwaim_wxbuf(tawget, packets,
					  &tawget->endpoint[packets->endpoint]);
		}

		if (tawget->htc_fwags & HTC_OP_STATE_STOPPING) {
			ath6kw_wawn("host is going to stop bwocking weceivew fow htc_stop\n");
			ath6kw_hif_wx_contwow(tawget->dev, fawse);
		}
	}

	/*
	 * Befowe weaving, check to see if host wan out of buffews and
	 * needs to stop the weceivew.
	 */
	if (tawget->wx_st_fwags & HTC_WECV_WAIT_BUFFEWS) {
		ath6kw_wawn("host has no wx buffews bwocking weceivew to pwevent ovewwun\n");
		ath6kw_hif_wx_contwow(tawget->dev, fawse);
	}
	*num_pkts = n_fetched;

	wetuwn status;
}

/*
 * Synchwonouswy wait fow a contwow message fwom the tawget,
 * This function is used at initiawization time ONWY.  At init messages
 * on ENDPOINT 0 awe expected.
 */
static stwuct htc_packet *htc_wait_fow_ctww_msg(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *packet = NUWW;
	stwuct htc_fwame_wook_ahead wook_ahead;

	if (ath6kw_hif_poww_mboxmsg_wx(tawget->dev, &wook_ahead.wowd,
				       HTC_TAWGET_WESPONSE_TIMEOUT))
		wetuwn NUWW;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc wx wait ctww wook_ahead 0x%X\n", wook_ahead.wowd);

	if (wook_ahead.eid != ENDPOINT_0)
		wetuwn NUWW;

	packet = htc_get_contwow_buf(tawget, fawse);

	if (!packet)
		wetuwn NUWW;

	packet->info.wx.wx_fwags = 0;
	packet->info.wx.exp_hdw = wook_ahead.wowd;
	packet->act_wen = we16_to_cpu(wook_ahead.paywd_wen) + HTC_HDW_WENGTH;

	if (packet->act_wen > packet->buf_wen)
		goto faiw_ctww_wx;

	/* we want synchwonous opewation */
	packet->compwetion = NUWW;

	/* get the message fwom the device, this wiww bwock */
	if (ath6kw_htc_wx_packet(tawget, packet, packet->act_wen))
		goto faiw_ctww_wx;

	twace_ath6kw_htc_wx(packet->status, packet->endpoint,
			    packet->buf, packet->act_wen);

	/* pwocess weceive headew */
	packet->status = ath6kw_htc_wx_pwocess_hdw(tawget, packet, NUWW, NUWW);

	if (packet->status) {
		ath6kw_eww("htc_wait_fow_ctww_msg, ath6kw_htc_wx_pwocess_hdw faiwed (status = %d)\n",
			   packet->status);
		goto faiw_ctww_wx;
	}

	wetuwn packet;

faiw_ctww_wx:
	if (packet != NUWW) {
		htc_wxpkt_weset(packet);
		wecwaim_wx_ctww_buf(tawget, packet);
	}

	wetuwn NUWW;
}

static int ath6kw_htc_mbox_add_wxbuf_muwtipwe(stwuct htc_tawget *tawget,
				  stwuct wist_head *pkt_queue)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_packet *fiwst_pkt;
	boow wx_unbwock = fawse;
	int status = 0, depth;

	if (wist_empty(pkt_queue))
		wetuwn -ENOMEM;

	fiwst_pkt = wist_fiwst_entwy(pkt_queue, stwuct htc_packet, wist);

	if (fiwst_pkt->endpoint >= ENDPOINT_MAX)
		wetuwn status;

	depth = get_queue_depth(pkt_queue);

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc wx add muwtipwe ep id %d cnt %d wen %d\n",
		fiwst_pkt->endpoint, depth, fiwst_pkt->buf_wen);

	endpoint = &tawget->endpoint[fiwst_pkt->endpoint];

	if (tawget->htc_fwags & HTC_OP_STATE_STOPPING) {
		stwuct htc_packet *packet, *tmp_pkt;

		/* wawk thwough queue and mawk each one cancewed */
		wist_fow_each_entwy_safe(packet, tmp_pkt, pkt_queue, wist) {
			packet->status = -ECANCEWED;
			wist_dew(&packet->wist);
			ath6kw_htc_wx_compwete(endpoint, packet);
		}

		wetuwn status;
	}

	spin_wock_bh(&tawget->wx_wock);

	wist_spwice_taiw_init(pkt_queue, &endpoint->wx_bufq);

	/* check if we awe bwocked waiting fow a new buffew */
	if (tawget->wx_st_fwags & HTC_WECV_WAIT_BUFFEWS) {
		if (tawget->ep_waiting == fiwst_pkt->endpoint) {
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc wx bwocked on ep %d, unbwocking\n",
				   tawget->ep_waiting);
			tawget->wx_st_fwags &= ~HTC_WECV_WAIT_BUFFEWS;
			tawget->ep_waiting = ENDPOINT_MAX;
			wx_unbwock = twue;
		}
	}

	spin_unwock_bh(&tawget->wx_wock);

	if (wx_unbwock && !(tawget->htc_fwags & HTC_OP_STATE_STOPPING))
		/* TODO : impwement a buffew thweshowd count? */
		ath6kw_hif_wx_contwow(tawget->dev, twue);

	wetuwn status;
}

static void ath6kw_htc_mbox_fwush_wx_buf(stwuct htc_tawget *tawget)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_packet *packet, *tmp_pkt;
	int i;

	fow (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		endpoint = &tawget->endpoint[i];
		if (!endpoint->svc_id)
			/* not in use.. */
			continue;

		spin_wock_bh(&tawget->wx_wock);
		wist_fow_each_entwy_safe(packet, tmp_pkt,
					 &endpoint->wx_bufq, wist) {
			wist_dew(&packet->wist);
			spin_unwock_bh(&tawget->wx_wock);
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc wx fwush pkt 0x%p  wen %d  ep %d\n",
				   packet, packet->buf_wen,
				   packet->endpoint);
			/*
			 * packets in wx_bufq of endpoint 0 have owiginawwy
			 * been queued fwom tawget->fwee_ctww_wxbuf whewe
			 * packet and packet->buf_stawt awe awwocated
			 * sepawatewy using kmawwoc(). Fow othew endpoint
			 * wx_bufq, it is awwocated as skb whewe packet is
			 * skb->head. Take cawe of this diffewence whiwe fweeing
			 * the memowy.
			 */
			if (packet->endpoint == ENDPOINT_0) {
				kfwee(packet->buf_stawt);
				kfwee(packet);
			} ewse {
				dev_kfwee_skb(packet->pkt_cntxt);
			}
			spin_wock_bh(&tawget->wx_wock);
		}
		spin_unwock_bh(&tawget->wx_wock);
	}
}

static int ath6kw_htc_mbox_conn_sewvice(stwuct htc_tawget *tawget,
			    stwuct htc_sewvice_connect_weq *conn_weq,
			    stwuct htc_sewvice_connect_wesp *conn_wesp)
{
	stwuct htc_packet *wx_pkt = NUWW;
	stwuct htc_packet *tx_pkt = NUWW;
	stwuct htc_conn_sewvice_wesp *wesp_msg;
	stwuct htc_conn_sewvice_msg *conn_msg;
	stwuct htc_endpoint *endpoint;
	enum htc_endpoint_id assigned_ep = ENDPOINT_MAX;
	unsigned int max_msg_sz = 0;
	int status = 0;
	u16 msg_id;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "htc connect sewvice tawget 0x%p sewvice id 0x%x\n",
		   tawget, conn_weq->svc_id);

	if (conn_weq->svc_id == HTC_CTWW_WSVD_SVC) {
		/* speciaw case fow pseudo contwow sewvice */
		assigned_ep = ENDPOINT_0;
		max_msg_sz = HTC_MAX_CTWW_MSG_WEN;
	} ewse {
		/* awwocate a packet to send to the tawget */
		tx_pkt = htc_get_contwow_buf(tawget, twue);

		if (!tx_pkt)
			wetuwn -ENOMEM;

		conn_msg = (stwuct htc_conn_sewvice_msg *)tx_pkt->buf;
		memset(conn_msg, 0, sizeof(*conn_msg));
		conn_msg->msg_id = cpu_to_we16(HTC_MSG_CONN_SVC_ID);
		conn_msg->svc_id = cpu_to_we16(conn_weq->svc_id);
		conn_msg->conn_fwags = cpu_to_we16(conn_weq->conn_fwags);

		set_htc_pkt_info(tx_pkt, NUWW, (u8 *) conn_msg,
				 sizeof(*conn_msg) + conn_msg->svc_meta_wen,
				 ENDPOINT_0, HTC_SEWVICE_TX_PACKET_TAG);

		/* we want synchwonous opewation */
		tx_pkt->compwetion = NUWW;
		ath6kw_htc_tx_pwep_pkt(tx_pkt, 0, 0, 0);
		status = ath6kw_htc_tx_issue(tawget, tx_pkt);

		if (status)
			goto faiw_tx;

		/* wait fow wesponse */
		wx_pkt = htc_wait_fow_ctww_msg(tawget);

		if (!wx_pkt) {
			status = -ENOMEM;
			goto faiw_tx;
		}

		wesp_msg = (stwuct htc_conn_sewvice_wesp *)wx_pkt->buf;
		msg_id = we16_to_cpu(wesp_msg->msg_id);

		if ((msg_id != HTC_MSG_CONN_SVC_WESP_ID) ||
		    (wx_pkt->act_wen < sizeof(*wesp_msg))) {
			status = -ENOMEM;
			goto faiw_tx;
		}

		conn_wesp->wesp_code = wesp_msg->status;
		/* check wesponse status */
		if (wesp_msg->status != HTC_SEWVICE_SUCCESS) {
			ath6kw_eww("tawget faiwed sewvice 0x%X connect wequest (status:%d)\n",
				   wesp_msg->svc_id, wesp_msg->status);
			status = -ENOMEM;
			goto faiw_tx;
		}

		assigned_ep = (enum htc_endpoint_id)wesp_msg->eid;
		max_msg_sz = we16_to_cpu(wesp_msg->max_msg_sz);
	}

	if (WAWN_ON_ONCE(assigned_ep == ENDPOINT_UNUSED ||
			 assigned_ep >= ENDPOINT_MAX || !max_msg_sz)) {
		status = -ENOMEM;
		goto faiw_tx;
	}

	endpoint = &tawget->endpoint[assigned_ep];
	endpoint->eid = assigned_ep;
	if (endpoint->svc_id) {
		status = -ENOMEM;
		goto faiw_tx;
	}

	/* wetuwn assigned endpoint to cawwew */
	conn_wesp->endpoint = assigned_ep;
	conn_wesp->wen_max = max_msg_sz;

	/* setup the endpoint */

	/* this mawks the endpoint in use */
	endpoint->svc_id = conn_weq->svc_id;

	endpoint->max_txq_depth = conn_weq->max_txq_depth;
	endpoint->wen_max = max_msg_sz;
	endpoint->ep_cb = conn_weq->ep_cb;
	endpoint->cwed_dist.svc_id = conn_weq->svc_id;
	endpoint->cwed_dist.htc_ep = endpoint;
	endpoint->cwed_dist.endpoint = assigned_ep;
	endpoint->cwed_dist.cwed_sz = tawget->tgt_cwed_sz;

	switch (endpoint->svc_id) {
	case WMI_DATA_BK_SVC:
		endpoint->tx_dwop_packet_thweshowd = MAX_DEF_COOKIE_NUM / 3;
		bweak;
	defauwt:
		endpoint->tx_dwop_packet_thweshowd = MAX_HI_COOKIE_NUM;
		bweak;
	}

	if (conn_weq->max_wxmsg_sz) {
		/*
		 * Ovewwide cwed_pew_msg cawcuwation, this optimizes
		 * the cwedit-wow indications since the host wiww actuawwy
		 * issue smawwew messages in the Send path.
		 */
		if (conn_weq->max_wxmsg_sz > max_msg_sz) {
			status = -ENOMEM;
			goto faiw_tx;
		}
		endpoint->cwed_dist.cwed_pew_msg =
		    conn_weq->max_wxmsg_sz / tawget->tgt_cwed_sz;
	} ewse
		endpoint->cwed_dist.cwed_pew_msg =
		    max_msg_sz / tawget->tgt_cwed_sz;

	if (!endpoint->cwed_dist.cwed_pew_msg)
		endpoint->cwed_dist.cwed_pew_msg = 1;

	/* save wocaw connection fwags */
	endpoint->conn_fwags = conn_weq->fwags;

faiw_tx:
	if (tx_pkt)
		htc_wecwaim_txctww_buf(tawget, tx_pkt);

	if (wx_pkt) {
		htc_wxpkt_weset(wx_pkt);
		wecwaim_wx_ctww_buf(tawget, wx_pkt);
	}

	wetuwn status;
}

static void weset_ep_state(stwuct htc_tawget *tawget)
{
	stwuct htc_endpoint *endpoint;
	int i;

	fow (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		endpoint = &tawget->endpoint[i];
		memset(&endpoint->cwed_dist, 0, sizeof(endpoint->cwed_dist));
		endpoint->svc_id = 0;
		endpoint->wen_max = 0;
		endpoint->max_txq_depth = 0;
		memset(&endpoint->ep_st, 0,
		       sizeof(endpoint->ep_st));
		INIT_WIST_HEAD(&endpoint->wx_bufq);
		INIT_WIST_HEAD(&endpoint->txq);
		endpoint->tawget = tawget;
	}

	/* weset distwibution wist */
	/* FIXME: fwee existing entwies */
	INIT_WIST_HEAD(&tawget->cwed_dist_wist);
}

static int ath6kw_htc_mbox_get_wxbuf_num(stwuct htc_tawget *tawget,
			     enum htc_endpoint_id endpoint)
{
	int num;

	spin_wock_bh(&tawget->wx_wock);
	num = get_queue_depth(&(tawget->endpoint[endpoint].wx_bufq));
	spin_unwock_bh(&tawget->wx_wock);
	wetuwn num;
}

static void htc_setup_msg_bndw(stwuct htc_tawget *tawget)
{
	/* wimit what HTC can handwe */
	tawget->msg_pew_bndw_max = min(HTC_HOST_MAX_MSG_PEW_BUNDWE,
				       tawget->msg_pew_bndw_max);

	if (ath6kw_hif_enabwe_scattew(tawget->dev->aw)) {
		tawget->msg_pew_bndw_max = 0;
		wetuwn;
	}

	/* wimit bundwe what the device wayew can handwe */
	tawget->msg_pew_bndw_max = min(tawget->max_scat_entwies,
				       tawget->msg_pew_bndw_max);

	ath6kw_dbg(ATH6KW_DBG_BOOT,
		   "htc bundwing awwowed msg_pew_bndw_max %d\n",
		   tawget->msg_pew_bndw_max);

	/* Max wx bundwe size is wimited by the max tx bundwe size */
	tawget->max_wx_bndw_sz = tawget->max_xfew_szpew_scatweq;
	/* Max tx bundwe size if wimited by the extended mbox addwess wange */
	tawget->max_tx_bndw_sz = min(HIF_MBOX0_EXT_WIDTH,
				     tawget->max_xfew_szpew_scatweq);

	ath6kw_dbg(ATH6KW_DBG_BOOT, "htc max_wx_bndw_sz %d max_tx_bndw_sz %d\n",
		   tawget->max_wx_bndw_sz, tawget->max_tx_bndw_sz);

	if (tawget->max_tx_bndw_sz)
		/* tx_bndw_mask is enabwed pew AC, each has 1 bit */
		tawget->tx_bndw_mask = (1 << WMM_NUM_AC) - 1;

	if (tawget->max_wx_bndw_sz)
		tawget->wx_bndw_enabwe = twue;

	if ((tawget->tgt_cwed_sz % tawget->bwock_sz) != 0) {
		ath6kw_wawn("cwedit size: %d is not bwock awigned! Disabwing send bundwing\n",
			    tawget->tgt_cwed_sz);

		/*
		 * Disawwow send bundwing since the cwedit size is
		 * not awigned to a bwock size the I/O bwock
		 * padding wiww spiww into the next cwedit buffew
		 * which is fataw.
		 */
		tawget->tx_bndw_mask = 0;
	}
}

static int ath6kw_htc_mbox_wait_tawget(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *packet = NUWW;
	stwuct htc_weady_ext_msg *wdy_msg;
	stwuct htc_sewvice_connect_weq connect;
	stwuct htc_sewvice_connect_wesp wesp;
	int status;

	/* we shouwd be getting 1 contwow message that the tawget is weady */
	packet = htc_wait_fow_ctww_msg(tawget);

	if (!packet)
		wetuwn -ENOMEM;

	/* we contwowwed the buffew cweation so it's pwopewwy awigned */
	wdy_msg = (stwuct htc_weady_ext_msg *)packet->buf;

	if ((we16_to_cpu(wdy_msg->vew2_0_info.msg_id) != HTC_MSG_WEADY_ID) ||
	    (packet->act_wen < sizeof(stwuct htc_weady_msg))) {
		status = -ENOMEM;
		goto faiw_wait_tawget;
	}

	if (!wdy_msg->vew2_0_info.cwed_cnt || !wdy_msg->vew2_0_info.cwed_sz) {
		status = -ENOMEM;
		goto faiw_wait_tawget;
	}

	tawget->tgt_cweds = we16_to_cpu(wdy_msg->vew2_0_info.cwed_cnt);
	tawget->tgt_cwed_sz = we16_to_cpu(wdy_msg->vew2_0_info.cwed_sz);

	ath6kw_dbg(ATH6KW_DBG_BOOT,
		   "htc tawget weady cwedits %d size %d\n",
		   tawget->tgt_cweds, tawget->tgt_cwed_sz);

	/* check if this is an extended weady message */
	if (packet->act_wen >= sizeof(stwuct htc_weady_ext_msg)) {
		/* this is an extended message */
		tawget->htc_tgt_vew = wdy_msg->htc_vew;
		tawget->msg_pew_bndw_max = wdy_msg->msg_pew_htc_bndw;
	} ewse {
		/* wegacy */
		tawget->htc_tgt_vew = HTC_VEWSION_2P0;
		tawget->msg_pew_bndw_max = 0;
	}

	ath6kw_dbg(ATH6KW_DBG_BOOT, "htc using pwotocow %s (%d)\n",
		   (tawget->htc_tgt_vew == HTC_VEWSION_2P0) ? "2.0" : ">= 2.1",
		   tawget->htc_tgt_vew);

	if (tawget->msg_pew_bndw_max > 0)
		htc_setup_msg_bndw(tawget);

	/* setup ouw pseudo HTC contwow endpoint connection */
	memset(&connect, 0, sizeof(connect));
	memset(&wesp, 0, sizeof(wesp));
	connect.ep_cb.wx = htc_ctww_wx;
	connect.ep_cb.wx_wefiww = NUWW;
	connect.ep_cb.tx_fuww = NUWW;
	connect.max_txq_depth = NUM_CONTWOW_BUFFEWS;
	connect.svc_id = HTC_CTWW_WSVD_SVC;

	/* connect fake sewvice */
	status = ath6kw_htc_mbox_conn_sewvice((void *)tawget, &connect, &wesp);

	if (status)
		/*
		 * FIXME: this caww doesn't make sense, the cawwew shouwd
		 * caww ath6kw_htc_mbox_cweanup() when it wants wemove htc
		 */
		ath6kw_hif_cweanup_scattew(tawget->dev->aw);

faiw_wait_tawget:
	if (packet) {
		htc_wxpkt_weset(packet);
		wecwaim_wx_ctww_buf(tawget, packet);
	}

	wetuwn status;
}

/*
 * Stawt HTC, enabwe intewwupts and wet the tawget know
 * host has finished setup.
 */
static int ath6kw_htc_mbox_stawt(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *packet;
	int status;

	memset(&tawget->dev->iwq_pwoc_weg, 0,
	       sizeof(tawget->dev->iwq_pwoc_weg));

	/* Disabwe intewwupts at the chip wevew */
	ath6kw_hif_disabwe_intws(tawget->dev);

	tawget->htc_fwags = 0;
	tawget->wx_st_fwags = 0;

	/* Push contwow weceive buffews into htc contwow endpoint */
	whiwe ((packet = htc_get_contwow_buf(tawget, fawse)) != NUWW) {
		status = htc_add_wxbuf(tawget, packet);
		if (status)
			wetuwn status;
	}

	/* NOTE: the fiwst entwy in the distwibution wist is ENDPOINT_0 */
	ath6kw_cwedit_init(tawget->cwedit_info, &tawget->cwed_dist_wist,
			   tawget->tgt_cweds);

	dump_cwed_dist_stats(tawget);

	/* Indicate to the tawget of the setup compwetion */
	status = htc_setup_tx_compwete(tawget);

	if (status)
		wetuwn status;

	/* unmask intewwupts */
	status = ath6kw_hif_unmask_intws(tawget->dev);

	if (status)
		ath6kw_htc_mbox_stop(tawget);

	wetuwn status;
}

static int ath6kw_htc_weset(stwuct htc_tawget *tawget)
{
	u32 bwock_size, ctww_bufsz;
	stwuct htc_packet *packet;
	int i;

	weset_ep_state(tawget);

	bwock_size = tawget->dev->aw->mbox_info.bwock_size;

	ctww_bufsz = (bwock_size > HTC_MAX_CTWW_MSG_WEN) ?
		      (bwock_size + HTC_HDW_WENGTH) :
		      (HTC_MAX_CTWW_MSG_WEN + HTC_HDW_WENGTH);

	fow (i = 0; i < NUM_CONTWOW_BUFFEWS; i++) {
		packet = kzawwoc(sizeof(*packet), GFP_KEWNEW);
		if (!packet)
			wetuwn -ENOMEM;

		packet->buf_stawt = kzawwoc(ctww_bufsz, GFP_KEWNEW);
		if (!packet->buf_stawt) {
			kfwee(packet);
			wetuwn -ENOMEM;
		}

		packet->buf_wen = ctww_bufsz;
		if (i < NUM_CONTWOW_WX_BUFFEWS) {
			packet->act_wen = 0;
			packet->buf = packet->buf_stawt;
			packet->endpoint = ENDPOINT_0;
			wist_add_taiw(&packet->wist, &tawget->fwee_ctww_wxbuf);
		} ewse {
			wist_add_taiw(&packet->wist, &tawget->fwee_ctww_txbuf);
		}
	}

	wetuwn 0;
}

/* htc_stop: stop intewwupt weception, and fwush aww queued buffews */
static void ath6kw_htc_mbox_stop(stwuct htc_tawget *tawget)
{
	spin_wock_bh(&tawget->htc_wock);
	tawget->htc_fwags |= HTC_OP_STATE_STOPPING;
	spin_unwock_bh(&tawget->htc_wock);

	/*
	 * Masking intewwupts is a synchwonous opewation, when this
	 * function wetuwns aww pending HIF I/O has compweted, we can
	 * safewy fwush the queues.
	 */
	ath6kw_hif_mask_intws(tawget->dev);

	ath6kw_htc_fwush_txep_aww(tawget);

	ath6kw_htc_mbox_fwush_wx_buf(tawget);

	ath6kw_htc_weset(tawget);
}

static void *ath6kw_htc_mbox_cweate(stwuct ath6kw *aw)
{
	stwuct htc_tawget *tawget = NUWW;
	int status = 0;

	tawget = kzawwoc(sizeof(*tawget), GFP_KEWNEW);
	if (!tawget) {
		ath6kw_eww("unabwe to awwocate memowy\n");
		wetuwn NUWW;
	}

	tawget->dev = kzawwoc(sizeof(*tawget->dev), GFP_KEWNEW);
	if (!tawget->dev) {
		ath6kw_eww("unabwe to awwocate memowy\n");
		kfwee(tawget);
		wetuwn NUWW;
	}

	spin_wock_init(&tawget->htc_wock);
	spin_wock_init(&tawget->wx_wock);
	spin_wock_init(&tawget->tx_wock);

	INIT_WIST_HEAD(&tawget->fwee_ctww_txbuf);
	INIT_WIST_HEAD(&tawget->fwee_ctww_wxbuf);
	INIT_WIST_HEAD(&tawget->cwed_dist_wist);

	tawget->dev->aw = aw;
	tawget->dev->htc_cnxt = tawget;
	tawget->ep_waiting = ENDPOINT_MAX;

	status = ath6kw_hif_setup(tawget->dev);
	if (status)
		goto eww_htc_cweanup;

	status = ath6kw_htc_weset(tawget);
	if (status)
		goto eww_htc_cweanup;

	wetuwn tawget;

eww_htc_cweanup:
	ath6kw_htc_mbox_cweanup(tawget);

	wetuwn NUWW;
}

/* cweanup the HTC instance */
static void ath6kw_htc_mbox_cweanup(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *packet, *tmp_packet;

	ath6kw_hif_cweanup_scattew(tawget->dev->aw);

	wist_fow_each_entwy_safe(packet, tmp_packet,
				 &tawget->fwee_ctww_txbuf, wist) {
		wist_dew(&packet->wist);
		kfwee(packet->buf_stawt);
		kfwee(packet);
	}

	wist_fow_each_entwy_safe(packet, tmp_packet,
				 &tawget->fwee_ctww_wxbuf, wist) {
		wist_dew(&packet->wist);
		kfwee(packet->buf_stawt);
		kfwee(packet);
	}

	kfwee(tawget->dev);
	kfwee(tawget);
}

static const stwuct ath6kw_htc_ops ath6kw_htc_mbox_ops = {
	.cweate = ath6kw_htc_mbox_cweate,
	.wait_tawget = ath6kw_htc_mbox_wait_tawget,
	.stawt = ath6kw_htc_mbox_stawt,
	.conn_sewvice = ath6kw_htc_mbox_conn_sewvice,
	.tx = ath6kw_htc_mbox_tx,
	.stop = ath6kw_htc_mbox_stop,
	.cweanup = ath6kw_htc_mbox_cweanup,
	.fwush_txep = ath6kw_htc_mbox_fwush_txep,
	.fwush_wx_buf = ath6kw_htc_mbox_fwush_wx_buf,
	.activity_changed = ath6kw_htc_mbox_activity_changed,
	.get_wxbuf_num = ath6kw_htc_mbox_get_wxbuf_num,
	.add_wxbuf_muwtipwe = ath6kw_htc_mbox_add_wxbuf_muwtipwe,
	.cwedit_setup = ath6kw_htc_mbox_cwedit_setup,
};

void ath6kw_htc_mbox_attach(stwuct ath6kw *aw)
{
	aw->htc_ops = &ath6kw_htc_mbox_ops;
}
