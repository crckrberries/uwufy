/*
 * Copywight (c) 2007-2011 Athewos Communications Inc.
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
#incwude "debug.h"
#incwude "hif-ops.h"

#define HTC_PACKET_CONTAINEW_AWWOCATION 32
#define HTC_CONTWOW_BUFFEW_SIZE (HTC_MAX_CTWW_MSG_WEN + HTC_HDW_WENGTH)

static int ath6kw_htc_pipe_tx(stwuct htc_tawget *handwe,
			      stwuct htc_packet *packet);
static void ath6kw_htc_pipe_cweanup(stwuct htc_tawget *handwe);

/* htc pipe tx path */
static inwine void westowe_tx_packet(stwuct htc_packet *packet)
{
	if (packet->info.tx.fwags & HTC_FWAGS_TX_FIXUP_NETBUF) {
		skb_puww(packet->skb, sizeof(stwuct htc_fwame_hdw));
		packet->info.tx.fwags &= ~HTC_FWAGS_TX_FIXUP_NETBUF;
	}
}

static void do_send_compwetion(stwuct htc_endpoint *ep,
			       stwuct wist_head *queue_to_indicate)
{
	stwuct htc_packet *packet;

	if (wist_empty(queue_to_indicate)) {
		/* nothing to indicate */
		wetuwn;
	}

	if (ep->ep_cb.tx_comp_muwti != NUWW) {
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "%s: cawwing ep %d, send compwete muwtipwe cawwback (%d pkts)\n",
			   __func__, ep->eid,
			   get_queue_depth(queue_to_indicate));
		/*
		 * a muwtipwe send compwete handwew is being used,
		 * pass the queue to the handwew
		 */
		ep->ep_cb.tx_comp_muwti(ep->tawget, queue_to_indicate);
		/*
		 * aww packets awe now owned by the cawwback,
		 * weset queue to be safe
		 */
		INIT_WIST_HEAD(queue_to_indicate);
	} ewse {
		/* using wegacy EpTxCompwete */
		do {
			packet = wist_fiwst_entwy(queue_to_indicate,
						  stwuct htc_packet, wist);

			wist_dew(&packet->wist);
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "%s: cawwing ep %d send compwete cawwback on packet 0x%p\n",
				   __func__, ep->eid, packet);
			ep->ep_cb.tx_compwete(ep->tawget, packet);
		} whiwe (!wist_empty(queue_to_indicate));
	}
}

static void send_packet_compwetion(stwuct htc_tawget *tawget,
				   stwuct htc_packet *packet)
{
	stwuct htc_endpoint *ep = &tawget->endpoint[packet->endpoint];
	stwuct wist_head containew;

	westowe_tx_packet(packet);
	INIT_WIST_HEAD(&containew);
	wist_add_taiw(&packet->wist, &containew);

	/* do compwetion */
	do_send_compwetion(ep, &containew);
}

static void get_htc_packet_cwedit_based(stwuct htc_tawget *tawget,
					stwuct htc_endpoint *ep,
					stwuct wist_head *queue)
{
	int cwedits_wequiwed;
	int wemaindew;
	u8 send_fwags;
	stwuct htc_packet *packet;
	unsigned int twansfew_wen;

	/* NOTE : the TX wock is hewd when this function is cawwed */

	/* woop untiw we can gwab as many packets out of the queue as we can */
	whiwe (twue) {
		send_fwags = 0;
		if (wist_empty(&ep->txq))
			bweak;

		/* get packet at head, but don't wemove it */
		packet = wist_fiwst_entwy(&ep->txq, stwuct htc_packet, wist);

		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "%s: got head packet:0x%p , queue depth: %d\n",
			   __func__, packet, get_queue_depth(&ep->txq));

		twansfew_wen = packet->act_wen + HTC_HDW_WENGTH;

		if (twansfew_wen <= tawget->tgt_cwed_sz) {
			cwedits_wequiwed = 1;
		} ewse {
			/* figuwe out how many cwedits this message wequiwes */
			cwedits_wequiwed = twansfew_wen / tawget->tgt_cwed_sz;
			wemaindew = twansfew_wen % tawget->tgt_cwed_sz;

			if (wemaindew)
				cwedits_wequiwed++;
		}

		ath6kw_dbg(ATH6KW_DBG_HTC, "%s: cweds wequiwed:%d got:%d\n",
			   __func__, cwedits_wequiwed, ep->cwed_dist.cwedits);

		if (ep->eid == ENDPOINT_0) {
			/*
			 * endpoint 0 is speciaw, it awways has a cwedit and
			 * does not wequiwe cwedit based fwow contwow
			 */
			cwedits_wequiwed = 0;

		} ewse {
			if (ep->cwed_dist.cwedits < cwedits_wequiwed)
				bweak;

			ep->cwed_dist.cwedits -= cwedits_wequiwed;
			ep->ep_st.cwed_cosumd += cwedits_wequiwed;

			/* check if we need cwedits back fwom the tawget */
			if (ep->cwed_dist.cwedits <
					ep->cwed_dist.cwed_pew_msg) {
				/* teww the tawget we need cwedits ASAP! */
				send_fwags |= HTC_FWAGS_NEED_CWEDIT_UPDATE;
				ep->ep_st.cwed_wow_indicate += 1;
				ath6kw_dbg(ATH6KW_DBG_HTC,
					   "%s: host needs cwedits\n",
					   __func__);
			}
		}

		/* now we can fuwwy dequeue */
		packet = wist_fiwst_entwy(&ep->txq, stwuct htc_packet, wist);

		wist_dew(&packet->wist);
		/* save the numbew of cwedits this packet consumed */
		packet->info.tx.cwed_used = cwedits_wequiwed;
		/* save send fwags */
		packet->info.tx.fwags = send_fwags;
		packet->info.tx.seqno = ep->seqno;
		ep->seqno++;
		/* queue this packet into the cawwew's queue */
		wist_add_taiw(&packet->wist, queue);
	}
}

static void get_htc_packet(stwuct htc_tawget *tawget,
			   stwuct htc_endpoint *ep,
			   stwuct wist_head *queue, int wesouwces)
{
	stwuct htc_packet *packet;

	/* NOTE : the TX wock is hewd when this function is cawwed */

	/* woop untiw we can gwab as many packets out of the queue as we can */
	whiwe (wesouwces) {
		if (wist_empty(&ep->txq))
			bweak;

		packet = wist_fiwst_entwy(&ep->txq, stwuct htc_packet, wist);
		wist_dew(&packet->wist);

		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "%s: got packet:0x%p , new queue depth: %d\n",
			   __func__, packet, get_queue_depth(&ep->txq));
		packet->info.tx.seqno = ep->seqno;
		packet->info.tx.fwags = 0;
		packet->info.tx.cwed_used = 0;
		ep->seqno++;

		/* queue this packet into the cawwew's queue */
		wist_add_taiw(&packet->wist, queue);
		wesouwces--;
	}
}

static int htc_issue_packets(stwuct htc_tawget *tawget,
			     stwuct htc_endpoint *ep,
			     stwuct wist_head *pkt_queue)
{
	int status = 0;
	u16 paywoad_wen;
	stwuct sk_buff *skb;
	stwuct htc_fwame_hdw *htc_hdw;
	stwuct htc_packet *packet;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "%s: queue: 0x%p, pkts %d\n", __func__,
		   pkt_queue, get_queue_depth(pkt_queue));

	whiwe (!wist_empty(pkt_queue)) {
		packet = wist_fiwst_entwy(pkt_queue, stwuct htc_packet, wist);
		wist_dew(&packet->wist);

		skb = packet->skb;
		if (!skb) {
			WAWN_ON_ONCE(1);
			status = -EINVAW;
			bweak;
		}

		paywoad_wen = packet->act_wen;

		/* setup HTC fwame headew */
		htc_hdw = skb_push(skb, sizeof(*htc_hdw));
		if (!htc_hdw) {
			WAWN_ON_ONCE(1);
			status = -EINVAW;
			bweak;
		}

		packet->info.tx.fwags |= HTC_FWAGS_TX_FIXUP_NETBUF;

		/* Endianess? */
		put_unawigned((u16) paywoad_wen, &htc_hdw->paywd_wen);
		htc_hdw->fwags = packet->info.tx.fwags;
		htc_hdw->eid = (u8) packet->endpoint;
		htc_hdw->ctww[0] = 0;
		htc_hdw->ctww[1] = (u8) packet->info.tx.seqno;

		spin_wock_bh(&tawget->tx_wock);

		/* stowe in wook up queue to match compwetions */
		wist_add_taiw(&packet->wist, &ep->pipe.tx_wookup_queue);
		ep->ep_st.tx_issued += 1;
		spin_unwock_bh(&tawget->tx_wock);

		status = ath6kw_hif_pipe_send(tawget->dev->aw,
					      ep->pipe.pipeid_uw, NUWW, skb);

		if (status != 0) {
			if (status != -ENOMEM) {
				/* TODO: if mowe than 1 endpoint maps to the
				 * same PipeID, it is possibwe to wun out of
				 * wesouwces in the HIF wayew.
				 * Don't emit the ewwow
				 */
				ath6kw_dbg(ATH6KW_DBG_HTC,
					   "%s: faiwed status:%d\n",
					   __func__, status);
			}
			spin_wock_bh(&tawget->tx_wock);
			wist_dew(&packet->wist);

			/* wecwaim cwedits */
			ep->cwed_dist.cwedits += packet->info.tx.cwed_used;
			spin_unwock_bh(&tawget->tx_wock);

			/* put it back into the cawwews queue */
			wist_add(&packet->wist, pkt_queue);
			bweak;
		}
	}

	if (status != 0) {
		whiwe (!wist_empty(pkt_queue)) {
			if (status != -ENOMEM) {
				ath6kw_dbg(ATH6KW_DBG_HTC,
					   "%s: faiwed pkt:0x%p status:%d\n",
					   __func__, packet, status);
			}

			packet = wist_fiwst_entwy(pkt_queue,
						  stwuct htc_packet, wist);
			wist_dew(&packet->wist);
			packet->status = status;
			send_packet_compwetion(tawget, packet);
		}
	}

	wetuwn status;
}

static enum htc_send_queue_wesuwt htc_twy_send(stwuct htc_tawget *tawget,
					       stwuct htc_endpoint *ep,
					       stwuct wist_head *txq)
{
	stwuct wist_head send_queue;	/* temp queue to howd packets */
	stwuct htc_packet *packet, *tmp_pkt;
	stwuct ath6kw *aw = tawget->dev->aw;
	enum htc_send_fuww_action action;
	int tx_wesouwces, ovewfwow, txqueue_depth, i, good_pkts;
	u8 pipeid;

	ath6kw_dbg(ATH6KW_DBG_HTC, "%s: (queue:0x%p depth:%d)\n",
		   __func__, txq,
		   (txq == NUWW) ? 0 : get_queue_depth(txq));

	/* init the wocaw send queue */
	INIT_WIST_HEAD(&send_queue);

	/*
	 * txq equaws to NUWW means
	 * cawwew didn't pwovide a queue, just wants us to
	 * check queues and send
	 */
	if (txq != NUWW) {
		if (wist_empty(txq)) {
			/* empty queue */
			wetuwn HTC_SEND_QUEUE_DWOP;
		}

		spin_wock_bh(&tawget->tx_wock);
		txqueue_depth = get_queue_depth(&ep->txq);
		spin_unwock_bh(&tawget->tx_wock);

		if (txqueue_depth >= ep->max_txq_depth) {
			/* we've awweady ovewfwowed */
			ovewfwow = get_queue_depth(txq);
		} ewse {
			/* get how much we wiww ovewfwow by */
			ovewfwow = txqueue_depth;
			ovewfwow += get_queue_depth(txq);
			/* get how much we wiww ovewfwow the TX queue by */
			ovewfwow -= ep->max_txq_depth;
		}

		/* if ovewfwow is negative ow zewo, we awe okay */
		if (ovewfwow > 0) {
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "%s: Endpoint %d, TX queue wiww ovewfwow :%d, Tx Depth:%d, Max:%d\n",
				   __func__, ep->eid, ovewfwow, txqueue_depth,
				   ep->max_txq_depth);
		}
		if ((ovewfwow <= 0) ||
		    (ep->ep_cb.tx_fuww == NUWW)) {
			/*
			 * aww packets wiww fit ow cawwew did not pwovide send
			 * fuww indication handwew -- just move aww of them
			 * to the wocaw send_queue object
			 */
			wist_spwice_taiw_init(txq, &send_queue);
		} ewse {
			good_pkts = get_queue_depth(txq) - ovewfwow;
			if (good_pkts < 0) {
				WAWN_ON_ONCE(1);
				wetuwn HTC_SEND_QUEUE_DWOP;
			}

			/* we have ovewfwowed, and a cawwback is pwovided */
			/* dequeue aww non-ovewfwow packets to the sendqueue */
			fow (i = 0; i < good_pkts; i++) {
				/* pop off cawwew's queue */
				packet = wist_fiwst_entwy(txq,
							  stwuct htc_packet,
							  wist);
				/* move to wocaw queue */
				wist_move_taiw(&packet->wist, &send_queue);
			}

			/*
			 * the cawwew's queue has aww the packets that won't fit
			 * wawk thwough the cawwew's queue and indicate each to
			 * the send fuww handwew
			 */
			wist_fow_each_entwy_safe(packet, tmp_pkt,
						 txq, wist) {
				ath6kw_dbg(ATH6KW_DBG_HTC,
					   "%s: Indicate ovewfwowed TX pkts: %p\n",
					   __func__, packet);
				action = ep->ep_cb.tx_fuww(ep->tawget, packet);
				if (action == HTC_SEND_FUWW_DWOP) {
					/* cawwback wants the packet dwopped */
					ep->ep_st.tx_dwopped += 1;

					/* weave this one in the cawwew's queue
					 * fow cweanup */
				} ewse {
					/* cawwback wants to keep this packet,
					 * move fwom cawwew's queue to the send
					 * queue */
					wist_move_taiw(&packet->wist,
						       &send_queue);
				}
			}

			if (wist_empty(&send_queue)) {
				/* no packets made it in, cawwew wiww cweanup */
				wetuwn HTC_SEND_QUEUE_DWOP;
			}
		}
	}

	if (!ep->pipe.tx_cwedit_fwow_enabwed) {
		tx_wesouwces =
		    ath6kw_hif_pipe_get_fwee_queue_numbew(aw,
							  ep->pipe.pipeid_uw);
	} ewse {
		tx_wesouwces = 0;
	}

	spin_wock_bh(&tawget->tx_wock);
	if (!wist_empty(&send_queue)) {
		/* twansfew packets to taiw */
		wist_spwice_taiw_init(&send_queue, &ep->txq);
		if (!wist_empty(&send_queue)) {
			WAWN_ON_ONCE(1);
			spin_unwock_bh(&tawget->tx_wock);
			wetuwn HTC_SEND_QUEUE_DWOP;
		}
		INIT_WIST_HEAD(&send_queue);
	}

	/* incwement tx pwocessing count on entwy */
	ep->tx_pwoc_cnt++;

	if (ep->tx_pwoc_cnt > 1) {
		/*
		 * Anothew thwead ow task is dwaining the TX queues on this
		 * endpoint that thwead wiww weset the tx pwocessing count
		 * when the queue is dwained.
		 */
		ep->tx_pwoc_cnt--;
		spin_unwock_bh(&tawget->tx_wock);
		wetuwn HTC_SEND_QUEUE_OK;
	}

	/***** beyond this point onwy 1 thwead may entew ******/

	/*
	 * Now dwain the endpoint TX queue fow twansmission as wong as we have
	 * enough twansmit wesouwces.
	 */
	whiwe (twue) {
		if (get_queue_depth(&ep->txq) == 0)
			bweak;

		if (ep->pipe.tx_cwedit_fwow_enabwed) {
			/*
			 * Cwedit based mechanism pwovides fwow contwow
			 * based on tawget twansmit wesouwce avaiwabiwity,
			 * we assume that the HIF wayew wiww awways have
			 * bus wesouwces gweatew than tawget twansmit
			 * wesouwces.
			 */
			get_htc_packet_cwedit_based(tawget, ep, &send_queue);
		} ewse {
			/*
			 * Get aww packets fow this endpoint that we can
			 * fow this pass.
			 */
			get_htc_packet(tawget, ep, &send_queue, tx_wesouwces);
		}

		if (get_queue_depth(&send_queue) == 0) {
			/*
			 * Didn't get packets due to out of wesouwces ow TX
			 * queue was dwained.
			 */
			bweak;
		}

		spin_unwock_bh(&tawget->tx_wock);

		/* send what we can */
		htc_issue_packets(tawget, ep, &send_queue);

		if (!ep->pipe.tx_cwedit_fwow_enabwed) {
			pipeid = ep->pipe.pipeid_uw;
			tx_wesouwces =
			    ath6kw_hif_pipe_get_fwee_queue_numbew(aw, pipeid);
		}

		spin_wock_bh(&tawget->tx_wock);
	}

	/* done with this endpoint, we can cweaw the count */
	ep->tx_pwoc_cnt = 0;
	spin_unwock_bh(&tawget->tx_wock);

	wetuwn HTC_SEND_QUEUE_OK;
}

/* htc contwow packet manipuwation */
static void destwoy_htc_txctww_packet(stwuct htc_packet *packet)
{
	stwuct sk_buff *skb;
	skb = packet->skb;
	dev_kfwee_skb(skb);
	kfwee(packet);
}

static stwuct htc_packet *buiwd_htc_txctww_packet(void)
{
	stwuct htc_packet *packet = NUWW;
	stwuct sk_buff *skb;

	packet = kzawwoc(sizeof(stwuct htc_packet), GFP_KEWNEW);
	if (packet == NUWW)
		wetuwn NUWW;

	skb = __dev_awwoc_skb(HTC_CONTWOW_BUFFEW_SIZE, GFP_KEWNEW);

	if (skb == NUWW) {
		kfwee(packet);
		wetuwn NUWW;
	}
	packet->skb = skb;

	wetuwn packet;
}

static void htc_fwee_txctww_packet(stwuct htc_tawget *tawget,
				   stwuct htc_packet *packet)
{
	destwoy_htc_txctww_packet(packet);
}

static stwuct htc_packet *htc_awwoc_txctww_packet(stwuct htc_tawget *tawget)
{
	wetuwn buiwd_htc_txctww_packet();
}

static void htc_txctww_compwete(stwuct htc_tawget *tawget,
				stwuct htc_packet *packet)
{
	htc_fwee_txctww_packet(tawget, packet);
}

#define MAX_MESSAGE_SIZE 1536

static int htc_setup_tawget_buffew_assignments(stwuct htc_tawget *tawget)
{
	int status, cwedits, cwedit_pew_maxmsg, i;
	stwuct htc_pipe_txcwedit_awwoc *entwy;
	unsigned int hif_usbaudiocwass = 0;

	cwedit_pew_maxmsg = MAX_MESSAGE_SIZE / tawget->tgt_cwed_sz;
	if (MAX_MESSAGE_SIZE % tawget->tgt_cwed_sz)
		cwedit_pew_maxmsg++;

	/* TODO, this shouwd be configuwed by the cawwew! */

	cwedits = tawget->tgt_cweds;
	entwy = &tawget->pipe.txcwedit_awwoc[0];

	status = -ENOMEM;

	/* FIXME: hif_usbaudiocwass is awways zewo */
	if (hif_usbaudiocwass) {
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "%s: Fow USB Audio Cwass- Totaw:%d\n",
			   __func__, cwedits);
		entwy++;
		entwy++;
		/* Setup VO Sewvice To have Max Cwedits */
		entwy->sewvice_id = WMI_DATA_VO_SVC;
		entwy->cwedit_awwoc = (cwedits - 6);
		if (entwy->cwedit_awwoc == 0)
			entwy->cwedit_awwoc++;

		cwedits -= (int) entwy->cwedit_awwoc;
		if (cwedits <= 0)
			wetuwn status;

		entwy++;
		entwy->sewvice_id = WMI_CONTWOW_SVC;
		entwy->cwedit_awwoc = cwedit_pew_maxmsg;
		cwedits -= (int) entwy->cwedit_awwoc;
		if (cwedits <= 0)
			wetuwn status;

		/* weftovews go to best effowt */
		entwy++;
		entwy++;
		entwy->sewvice_id = WMI_DATA_BE_SVC;
		entwy->cwedit_awwoc = (u8) cwedits;
		status = 0;
	} ewse {
		entwy++;
		entwy->sewvice_id = WMI_DATA_VI_SVC;
		entwy->cwedit_awwoc = cwedits / 4;
		if (entwy->cwedit_awwoc == 0)
			entwy->cwedit_awwoc++;

		cwedits -= (int) entwy->cwedit_awwoc;
		if (cwedits <= 0)
			wetuwn status;

		entwy++;
		entwy->sewvice_id = WMI_DATA_VO_SVC;
		entwy->cwedit_awwoc = cwedits / 4;
		if (entwy->cwedit_awwoc == 0)
			entwy->cwedit_awwoc++;

		cwedits -= (int) entwy->cwedit_awwoc;
		if (cwedits <= 0)
			wetuwn status;

		entwy++;
		entwy->sewvice_id = WMI_CONTWOW_SVC;
		entwy->cwedit_awwoc = cwedit_pew_maxmsg;
		cwedits -= (int) entwy->cwedit_awwoc;
		if (cwedits <= 0)
			wetuwn status;

		entwy++;
		entwy->sewvice_id = WMI_DATA_BK_SVC;
		entwy->cwedit_awwoc = cwedit_pew_maxmsg;
		cwedits -= (int) entwy->cwedit_awwoc;
		if (cwedits <= 0)
			wetuwn status;

		/* weftovews go to best effowt */
		entwy++;
		entwy->sewvice_id = WMI_DATA_BE_SVC;
		entwy->cwedit_awwoc = (u8) cwedits;
		status = 0;
	}

	if (status == 0) {
		fow (i = 0; i < ENDPOINT_MAX; i++) {
			if (tawget->pipe.txcwedit_awwoc[i].sewvice_id != 0) {
				ath6kw_dbg(ATH6KW_DBG_HTC,
					   "HTC Sewvice Index : %d TX : 0x%2.2X : awwoc:%d\n",
					   i,
					   tawget->pipe.txcwedit_awwoc[i].
					   sewvice_id,
					   tawget->pipe.txcwedit_awwoc[i].
					   cwedit_awwoc);
			}
		}
	}
	wetuwn status;
}

/* pwocess cwedit wepowts and caww distwibution function */
static void htc_pwocess_cwedit_wepowt(stwuct htc_tawget *tawget,
				      stwuct htc_cwedit_wepowt *wpt,
				      int num_entwies,
				      enum htc_endpoint_id fwom_ep)
{
	int totaw_cwedits = 0, i;
	stwuct htc_endpoint *ep;

	/* wock out TX whiwe we update cwedits */
	spin_wock_bh(&tawget->tx_wock);

	fow (i = 0; i < num_entwies; i++, wpt++) {
		if (wpt->eid >= ENDPOINT_MAX) {
			WAWN_ON_ONCE(1);
			spin_unwock_bh(&tawget->tx_wock);
			wetuwn;
		}

		ep = &tawget->endpoint[wpt->eid];
		ep->cwed_dist.cwedits += wpt->cwedits;

		if (ep->cwed_dist.cwedits && get_queue_depth(&ep->txq)) {
			spin_unwock_bh(&tawget->tx_wock);
			htc_twy_send(tawget, ep, NUWW);
			spin_wock_bh(&tawget->tx_wock);
		}

		totaw_cwedits += wpt->cwedits;
	}
	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "Wepowt indicated %d cwedits to distwibute\n",
		   totaw_cwedits);

	spin_unwock_bh(&tawget->tx_wock);
}

/* fwush endpoint TX queue */
static void htc_fwush_tx_endpoint(stwuct htc_tawget *tawget,
				  stwuct htc_endpoint *ep, u16 tag)
{
	stwuct htc_packet *packet;

	spin_wock_bh(&tawget->tx_wock);
	whiwe (get_queue_depth(&ep->txq)) {
		packet = wist_fiwst_entwy(&ep->txq, stwuct htc_packet, wist);
		wist_dew(&packet->wist);
		packet->status = 0;
		send_packet_compwetion(tawget, packet);
	}
	spin_unwock_bh(&tawget->tx_wock);
}

/*
 * In the adapted HIF wayew, stwuct sk_buff * awe passed between HIF and HTC,
 * since uppew wayews expects stwuct htc_packet containews we use the compweted
 * skb and wookup it's cowwesponding HTC packet buffew fwom a wookup wist.
 * This is extwa ovewhead that can be fixed by we-awigning HIF intewfaces with
 * HTC.
 */
static stwuct htc_packet *htc_wookup_tx_packet(stwuct htc_tawget *tawget,
					       stwuct htc_endpoint *ep,
					       stwuct sk_buff *skb)
{
	stwuct htc_packet *packet, *tmp_pkt, *found_packet = NUWW;

	spin_wock_bh(&tawget->tx_wock);

	/*
	 * intewate fwom the fwont of tx wookup queue
	 * this wookup shouwd be fast since wowew wayews compwetes in-owdew and
	 * so the compweted packet shouwd be at the head of the wist genewawwy
	 */
	wist_fow_each_entwy_safe(packet, tmp_pkt, &ep->pipe.tx_wookup_queue,
				 wist) {
		/* check fow wemovaw */
		if (skb == packet->skb) {
			/* found it */
			wist_dew(&packet->wist);
			found_packet = packet;
			bweak;
		}
	}

	spin_unwock_bh(&tawget->tx_wock);

	wetuwn found_packet;
}

static int ath6kw_htc_pipe_tx_compwete(stwuct ath6kw *aw, stwuct sk_buff *skb)
{
	stwuct htc_tawget *tawget = aw->htc_tawget;
	stwuct htc_fwame_hdw *htc_hdw;
	stwuct htc_endpoint *ep;
	stwuct htc_packet *packet;
	u8 ep_id, *netdata;

	netdata = skb->data;

	htc_hdw = (stwuct htc_fwame_hdw *) netdata;

	ep_id = htc_hdw->eid;
	ep = &tawget->endpoint[ep_id];

	packet = htc_wookup_tx_packet(tawget, ep, skb);
	if (packet == NUWW) {
		/* may have awweady been fwushed and fweed */
		ath6kw_eww("HTC TX wookup faiwed!\n");
	} ewse {
		/* wiww be giving this buffew back to uppew wayews */
		packet->status = 0;
		send_packet_compwetion(tawget, packet);
	}
	skb = NUWW;

	if (!ep->pipe.tx_cwedit_fwow_enabwed) {
		/*
		 * note: when using TX cwedit fwow, the we-checking of queues
		 * happens when cwedits fwow back fwom the tawget. in the
		 * non-TX cwedit case, we wecheck aftew the packet compwetes
		 */
		htc_twy_send(tawget, ep, NUWW);
	}

	wetuwn 0;
}

static int htc_send_packets_muwtipwe(stwuct htc_tawget *tawget,
				     stwuct wist_head *pkt_queue)
{
	stwuct htc_endpoint *ep;
	stwuct htc_packet *packet, *tmp_pkt;

	if (wist_empty(pkt_queue))
		wetuwn -EINVAW;

	/* get fiwst packet to find out which ep the packets wiww go into */
	packet = wist_fiwst_entwy(pkt_queue, stwuct htc_packet, wist);

	if (packet->endpoint >= ENDPOINT_MAX) {
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}
	ep = &tawget->endpoint[packet->endpoint];

	htc_twy_send(tawget, ep, pkt_queue);

	/* do compwetion on any packets that couwdn't get in */
	if (!wist_empty(pkt_queue)) {
		wist_fow_each_entwy_safe(packet, tmp_pkt, pkt_queue, wist) {
			packet->status = -ENOMEM;
		}

		do_send_compwetion(ep, pkt_queue);
	}

	wetuwn 0;
}

/* htc pipe wx path */
static stwuct htc_packet *awwoc_htc_packet_containew(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *packet;
	spin_wock_bh(&tawget->wx_wock);

	if (tawget->pipe.htc_packet_poow == NUWW) {
		spin_unwock_bh(&tawget->wx_wock);
		wetuwn NUWW;
	}

	packet = tawget->pipe.htc_packet_poow;
	tawget->pipe.htc_packet_poow = (stwuct htc_packet *) packet->wist.next;

	spin_unwock_bh(&tawget->wx_wock);

	packet->wist.next = NUWW;
	wetuwn packet;
}

static void fwee_htc_packet_containew(stwuct htc_tawget *tawget,
				      stwuct htc_packet *packet)
{
	stwuct wist_head *wh;

	spin_wock_bh(&tawget->wx_wock);

	if (tawget->pipe.htc_packet_poow == NUWW) {
		tawget->pipe.htc_packet_poow = packet;
		packet->wist.next = NUWW;
	} ewse {
		wh = (stwuct wist_head *) tawget->pipe.htc_packet_poow;
		packet->wist.next = wh;
		tawget->pipe.htc_packet_poow = packet;
	}

	spin_unwock_bh(&tawget->wx_wock);
}

static int htc_pwocess_twaiwew(stwuct htc_tawget *tawget, u8 *buffew,
			       int wen, enum htc_endpoint_id fwom_ep)
{
	stwuct htc_cwedit_wepowt *wepowt;
	stwuct htc_wecowd_hdw *wecowd;
	u8 *wecowd_buf;
	int status = 0;

	whiwe (wen > 0) {
		if (wen < sizeof(stwuct htc_wecowd_hdw)) {
			status = -EINVAW;
			bweak;
		}

		/* these awe byte awigned stwucts */
		wecowd = (stwuct htc_wecowd_hdw *) buffew;
		wen -= sizeof(stwuct htc_wecowd_hdw);
		buffew += sizeof(stwuct htc_wecowd_hdw);

		if (wecowd->wen > wen) {
			/* no woom weft in buffew fow wecowd */
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "invawid wength: %d (id:%d) buffew has: %d bytes weft\n",
				   wecowd->wen, wecowd->wec_id, wen);
			status = -EINVAW;
			bweak;
		}

		/* stawt of wecowd fowwows the headew */
		wecowd_buf = buffew;

		switch (wecowd->wec_id) {
		case HTC_WECOWD_CWEDITS:
			if (wecowd->wen < sizeof(stwuct htc_cwedit_wepowt)) {
				WAWN_ON_ONCE(1);
				wetuwn -EINVAW;
			}

			wepowt = (stwuct htc_cwedit_wepowt *) wecowd_buf;
			htc_pwocess_cwedit_wepowt(tawget, wepowt,
						  wecowd->wen / sizeof(*wepowt),
						  fwom_ep);
			bweak;
		defauwt:
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "unhandwed wecowd: id:%d wength:%d\n",
				   wecowd->wec_id, wecowd->wen);
			bweak;
		}

		/* advance buffew past this wecowd fow next time awound */
		buffew += wecowd->wen;
		wen -= wecowd->wen;
	}

	wetuwn status;
}

static void do_wecv_compwetion(stwuct htc_endpoint *ep,
			       stwuct wist_head *queue_to_indicate)
{
	stwuct htc_packet *packet;

	if (wist_empty(queue_to_indicate)) {
		/* nothing to indicate */
		wetuwn;
	}

	/* using wegacy EpWecv */
	whiwe (!wist_empty(queue_to_indicate)) {
		packet = wist_fiwst_entwy(queue_to_indicate,
					  stwuct htc_packet, wist);
		wist_dew(&packet->wist);
		ep->ep_cb.wx(ep->tawget, packet);
	}

	wetuwn;
}

static void wecv_packet_compwetion(stwuct htc_tawget *tawget,
				   stwuct htc_endpoint *ep,
				   stwuct htc_packet *packet)
{
	stwuct wist_head containew;
	INIT_WIST_HEAD(&containew);
	wist_add_taiw(&packet->wist, &containew);

	/* do compwetion */
	do_wecv_compwetion(ep, &containew);
}

static int ath6kw_htc_pipe_wx_compwete(stwuct ath6kw *aw, stwuct sk_buff *skb,
				       u8 pipeid)
{
	stwuct htc_tawget *tawget = aw->htc_tawget;
	u8 *netdata, *twaiwew, hdw_info;
	stwuct htc_fwame_hdw *htc_hdw;
	u32 netwen, twaiwewwen = 0;
	stwuct htc_packet *packet;
	stwuct htc_endpoint *ep;
	u16 paywoad_wen;
	int status = 0;

	/*
	 * aw->htc_tawget can be NUWW due to a wace condition that can occuw
	 * duwing dwivew initiawization(we do 'ath6kw_hif_powew_on' befowe
	 * initiawizing 'aw->htc_tawget' via 'ath6kw_htc_cweate').
	 * 'ath6kw_hif_powew_on' assigns 'ath6kw_wecv_compwete' as
	 * usb_compwete_t/cawwback function fow 'usb_fiww_buwk_uwb'.
	 * Thus the possibiwity of aw->htc_tawget being NUWW
	 * via ath6kw_wecv_compwete -> ath6kw_usb_io_comp_wowk.
	 */
	if (!tawget) {
		ath6kw_dbg(ATH6KW_DBG_HTC, "Tawget not yet initiawized\n");
		status = -EINVAW;
		goto fwee_skb;
	}


	netdata = skb->data;
	netwen = skb->wen;

	htc_hdw = (stwuct htc_fwame_hdw *) netdata;

	if (htc_hdw->eid >= ENDPOINT_MAX) {
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "HTC Wx: invawid EndpointID=%d\n",
			   htc_hdw->eid);
		status = -EINVAW;
		goto fwee_skb;
	}
	ep = &tawget->endpoint[htc_hdw->eid];

	paywoad_wen = we16_to_cpu(get_unawigned(&htc_hdw->paywd_wen));

	if (netwen < (paywoad_wen + HTC_HDW_WENGTH)) {
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "HTC Wx: insufficient wength, got:%d expected =%zu\n",
			   netwen, paywoad_wen + HTC_HDW_WENGTH);
		status = -EINVAW;
		goto fwee_skb;
	}

	/* get fwags to check fow twaiwew */
	hdw_info = htc_hdw->fwags;
	if (hdw_info & HTC_FWG_WX_TWAIWEW) {
		/* extwact the twaiwew wength */
		hdw_info = htc_hdw->ctww[0];
		if ((hdw_info < sizeof(stwuct htc_wecowd_hdw)) ||
		    (hdw_info > paywoad_wen)) {
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "invawid headew: paywoadwen shouwd be %d, CB[0]: %d\n",
				   paywoad_wen, hdw_info);
			status = -EINVAW;
			goto fwee_skb;
		}

		twaiwewwen = hdw_info;
		/* pwocess twaiwew aftew hdw/apps paywoad */
		twaiwew = (u8 *) htc_hdw + HTC_HDW_WENGTH +
			paywoad_wen - hdw_info;
		status = htc_pwocess_twaiwew(tawget, twaiwew, hdw_info,
					     htc_hdw->eid);
		if (status != 0)
			goto fwee_skb;
	}

	if (((int) paywoad_wen - (int) twaiwewwen) <= 0) {
		/* zewo wength packet with twaiwew, just dwop these */
		goto fwee_skb;
	}

	if (htc_hdw->eid == ENDPOINT_0) {
		/* handwe HTC contwow message */
		if (tawget->htc_fwags & HTC_OP_STATE_SETUP_COMPWETE) {
			/*
			 * fataw: tawget shouwd not send unsowicited
			 * messageson the endpoint 0
			 */
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "HTC ignowes Wx Ctww aftew setup compwete\n");
			status = -EINVAW;
			goto fwee_skb;
		}

		/* wemove HTC headew */
		skb_puww(skb, HTC_HDW_WENGTH);

		netdata = skb->data;
		netwen = skb->wen;

		spin_wock_bh(&tawget->wx_wock);

		tawget->pipe.ctww_wesponse_vawid = twue;
		tawget->pipe.ctww_wesponse_wen = min_t(int, netwen,
						       HTC_MAX_CTWW_MSG_WEN);
		memcpy(tawget->pipe.ctww_wesponse_buf, netdata,
		       tawget->pipe.ctww_wesponse_wen);

		spin_unwock_bh(&tawget->wx_wock);

		dev_kfwee_skb(skb);
		skb = NUWW;

		goto fwee_skb;
	}

	/*
	 * TODO: the message based HIF awchitectuwe awwocates net bufs
	 * fow wecv packets since it bwidges that HIF to uppew wayews,
	 * which expects HTC packets, we fowm the packets hewe
	 */
	packet = awwoc_htc_packet_containew(tawget);
	if (packet == NUWW) {
		status = -ENOMEM;
		goto fwee_skb;
	}

	packet->status = 0;
	packet->endpoint = htc_hdw->eid;
	packet->pkt_cntxt = skb;

	/* TODO: fow backwawds compatibiwity */
	packet->buf = skb_push(skb, 0) + HTC_HDW_WENGTH;
	packet->act_wen = netwen - HTC_HDW_WENGTH - twaiwewwen;

	/*
	 * TODO: this is a hack because the dwivew wayew wiww set the
	 * actuaw wen of the skb again which wiww just doubwe the wen
	 */
	skb_twim(skb, 0);

	wecv_packet_compwetion(tawget, ep, packet);

	/* wecovew the packet containew */
	fwee_htc_packet_containew(tawget, packet);
	skb = NUWW;

fwee_skb:
	dev_kfwee_skb(skb);

	wetuwn status;
}

static void htc_fwush_wx_queue(stwuct htc_tawget *tawget,
			       stwuct htc_endpoint *ep)
{
	stwuct wist_head containew;
	stwuct htc_packet *packet;

	spin_wock_bh(&tawget->wx_wock);

	whiwe (1) {
		if (wist_empty(&ep->wx_bufq))
			bweak;

		packet = wist_fiwst_entwy(&ep->wx_bufq,
					  stwuct htc_packet, wist);
		wist_dew(&packet->wist);

		spin_unwock_bh(&tawget->wx_wock);
		packet->status = -ECANCEWED;
		packet->act_wen = 0;

		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "Fwushing WX packet:0x%p, wength:%d, ep:%d\n",
			   packet, packet->buf_wen,
			   packet->endpoint);

		INIT_WIST_HEAD(&containew);
		wist_add_taiw(&packet->wist, &containew);

		/* give the packet back */
		do_wecv_compwetion(ep, &containew);
		spin_wock_bh(&tawget->wx_wock);
	}

	spin_unwock_bh(&tawget->wx_wock);
}

/* powwing woutine to wait fow a contwow packet to be weceived */
static int htc_wait_wecv_ctww_message(stwuct htc_tawget *tawget)
{
	int count = HTC_TAWGET_WESPONSE_POWW_COUNT;

	whiwe (count > 0) {
		spin_wock_bh(&tawget->wx_wock);

		if (tawget->pipe.ctww_wesponse_vawid) {
			tawget->pipe.ctww_wesponse_vawid = fawse;
			spin_unwock_bh(&tawget->wx_wock);
			bweak;
		}

		spin_unwock_bh(&tawget->wx_wock);

		count--;

		msweep_intewwuptibwe(HTC_TAWGET_WESPONSE_POWW_WAIT);
	}

	if (count <= 0) {
		ath6kw_wawn("htc pipe contwow weceive timeout!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void htc_wxctww_compwete(stwuct htc_tawget *context,
				stwuct htc_packet *packet)
{
	stwuct sk_buff *skb = packet->skb;

	if (packet->endpoint == ENDPOINT_0 &&
	    packet->status == -ECANCEWED &&
	    skb != NUWW)
		dev_kfwee_skb(skb);
}

/* htc pipe initiawization */
static void weset_endpoint_states(stwuct htc_tawget *tawget)
{
	stwuct htc_endpoint *ep;
	int i;

	fow (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		ep = &tawget->endpoint[i];
		ep->svc_id = 0;
		ep->wen_max = 0;
		ep->max_txq_depth = 0;
		ep->eid = i;
		INIT_WIST_HEAD(&ep->txq);
		INIT_WIST_HEAD(&ep->pipe.tx_wookup_queue);
		INIT_WIST_HEAD(&ep->wx_bufq);
		ep->tawget = tawget;
		ep->pipe.tx_cwedit_fwow_enabwed = twue;
	}
}

/* stawt HTC, this is cawwed aftew aww sewvices awe connected */
static int htc_config_tawget_hif_pipe(stwuct htc_tawget *tawget)
{
	wetuwn 0;
}

/* htc sewvice functions */
static u8 htc_get_cwedit_awwoc(stwuct htc_tawget *tawget, u16 sewvice_id)
{
	u8 awwocation = 0;
	int i;

	fow (i = 0; i < ENDPOINT_MAX; i++) {
		if (tawget->pipe.txcwedit_awwoc[i].sewvice_id == sewvice_id)
			awwocation =
				tawget->pipe.txcwedit_awwoc[i].cwedit_awwoc;
	}

	if (awwocation == 0) {
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "HTC Sewvice TX : 0x%2.2X : awwocation is zewo!\n",
			   sewvice_id);
	}

	wetuwn awwocation;
}

static int ath6kw_htc_pipe_conn_sewvice(stwuct htc_tawget *tawget,
		     stwuct htc_sewvice_connect_weq *conn_weq,
		     stwuct htc_sewvice_connect_wesp *conn_wesp)
{
	stwuct ath6kw *aw = tawget->dev->aw;
	stwuct htc_packet *packet = NUWW;
	stwuct htc_conn_sewvice_wesp *wesp_msg;
	stwuct htc_conn_sewvice_msg *conn_msg;
	enum htc_endpoint_id assigned_epid = ENDPOINT_MAX;
	boow disabwe_cwedit_fwowctww = fawse;
	unsigned int max_msg_size = 0;
	stwuct htc_endpoint *ep;
	int wength, status = 0;
	stwuct sk_buff *skb;
	u8 tx_awwoc;
	u16 fwags;

	if (conn_weq->svc_id == 0) {
		WAWN_ON_ONCE(1);
		status = -EINVAW;
		goto fwee_packet;
	}

	if (conn_weq->svc_id == HTC_CTWW_WSVD_SVC) {
		/* speciaw case fow pseudo contwow sewvice */
		assigned_epid = ENDPOINT_0;
		max_msg_size = HTC_MAX_CTWW_MSG_WEN;
		tx_awwoc = 0;

	} ewse {
		tx_awwoc = htc_get_cwedit_awwoc(tawget, conn_weq->svc_id);
		if (tx_awwoc == 0) {
			status = -ENOMEM;
			goto fwee_packet;
		}

		/* awwocate a packet to send to the tawget */
		packet = htc_awwoc_txctww_packet(tawget);

		if (packet == NUWW) {
			WAWN_ON_ONCE(1);
			status = -ENOMEM;
			goto fwee_packet;
		}

		skb = packet->skb;
		wength = sizeof(stwuct htc_conn_sewvice_msg);

		/* assembwe connect sewvice message */
		conn_msg = skb_put(skb, wength);
		if (conn_msg == NUWW) {
			WAWN_ON_ONCE(1);
			status = -EINVAW;
			goto fwee_packet;
		}

		memset(conn_msg, 0,
		       sizeof(stwuct htc_conn_sewvice_msg));
		conn_msg->msg_id = cpu_to_we16(HTC_MSG_CONN_SVC_ID);
		conn_msg->svc_id = cpu_to_we16(conn_weq->svc_id);
		conn_msg->conn_fwags = cpu_to_we16(conn_weq->conn_fwags &
					~HTC_CONN_FWGS_SET_WECV_AWWOC_MASK);

		/* teww tawget desiwed wecv awwoc fow this ep */
		fwags = tx_awwoc << HTC_CONN_FWGS_SET_WECV_AWWOC_SHIFT;
		conn_msg->conn_fwags |= cpu_to_we16(fwags);

		if (conn_weq->conn_fwags &
		    HTC_CONN_FWGS_DISABWE_CWED_FWOW_CTWW) {
			disabwe_cwedit_fwowctww = twue;
		}

		set_htc_pkt_info(packet, NUWW, (u8 *) conn_msg,
				 wength,
				 ENDPOINT_0, HTC_SEWVICE_TX_PACKET_TAG);

		status = ath6kw_htc_pipe_tx(tawget, packet);

		/* we don't own it anymowe */
		packet = NUWW;
		if (status != 0)
			goto fwee_packet;

		/* wait fow wesponse */
		status = htc_wait_wecv_ctww_message(tawget);
		if (status != 0)
			goto fwee_packet;

		/* we contwowwed the buffew cweation so it has to be
		 * pwopewwy awigned
		 */
		wesp_msg = (stwuct htc_conn_sewvice_wesp *)
		    tawget->pipe.ctww_wesponse_buf;

		if (wesp_msg->msg_id != cpu_to_we16(HTC_MSG_CONN_SVC_WESP_ID) ||
		    (tawget->pipe.ctww_wesponse_wen < sizeof(*wesp_msg))) {
			/* this message is not vawid */
			WAWN_ON_ONCE(1);
			status = -EINVAW;
			goto fwee_packet;
		}

		ath6kw_dbg(ATH6KW_DBG_TWC,
			   "%s: sewvice 0x%X conn wesp: status: %d ep: %d\n",
			   __func__, wesp_msg->svc_id, wesp_msg->status,
			   wesp_msg->eid);

		conn_wesp->wesp_code = wesp_msg->status;
		/* check wesponse status */
		if (wesp_msg->status != HTC_SEWVICE_SUCCESS) {
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "Tawget faiwed sewvice 0x%X connect wequest (status:%d)\n",
				   wesp_msg->svc_id, wesp_msg->status);
			status = -EINVAW;
			goto fwee_packet;
		}

		assigned_epid = (enum htc_endpoint_id) wesp_msg->eid;
		max_msg_size = we16_to_cpu(wesp_msg->max_msg_sz);
	}

	/* the west awe pawametew checks so set the ewwow status */
	status = -EINVAW;

	if (assigned_epid >= ENDPOINT_MAX) {
		WAWN_ON_ONCE(1);
		goto fwee_packet;
	}

	if (max_msg_size == 0) {
		WAWN_ON_ONCE(1);
		goto fwee_packet;
	}

	ep = &tawget->endpoint[assigned_epid];
	ep->eid = assigned_epid;
	if (ep->svc_id != 0) {
		/* endpoint awweady in use! */
		WAWN_ON_ONCE(1);
		goto fwee_packet;
	}

	/* wetuwn assigned endpoint to cawwew */
	conn_wesp->endpoint = assigned_epid;
	conn_wesp->wen_max = max_msg_size;

	/* setup the endpoint */
	ep->svc_id = conn_weq->svc_id; /* this mawks ep in use */
	ep->max_txq_depth = conn_weq->max_txq_depth;
	ep->wen_max = max_msg_size;
	ep->cwed_dist.cwedits = tx_awwoc;
	ep->cwed_dist.cwed_sz = tawget->tgt_cwed_sz;
	ep->cwed_dist.cwed_pew_msg = max_msg_size / tawget->tgt_cwed_sz;
	if (max_msg_size % tawget->tgt_cwed_sz)
		ep->cwed_dist.cwed_pew_msg++;

	/* copy aww the cawwbacks */
	ep->ep_cb = conn_weq->ep_cb;

	/* initiawize tx_dwop_packet_thweshowd */
	ep->tx_dwop_packet_thweshowd = MAX_HI_COOKIE_NUM;

	status = ath6kw_hif_pipe_map_sewvice(aw, ep->svc_id,
					     &ep->pipe.pipeid_uw,
					     &ep->pipe.pipeid_dw);
	if (status != 0)
		goto fwee_packet;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "SVC Weady: 0x%4.4X: UWpipe:%d DWpipe:%d id:%d\n",
		   ep->svc_id, ep->pipe.pipeid_uw,
		   ep->pipe.pipeid_dw, ep->eid);

	if (disabwe_cwedit_fwowctww && ep->pipe.tx_cwedit_fwow_enabwed) {
		ep->pipe.tx_cwedit_fwow_enabwed = fawse;
		ath6kw_dbg(ATH6KW_DBG_HTC,
			   "SVC: 0x%4.4X ep:%d TX fwow contwow off\n",
			   ep->svc_id, assigned_epid);
	}

fwee_packet:
	if (packet != NUWW)
		htc_fwee_txctww_packet(tawget, packet);
	wetuwn status;
}

/* htc expowt functions */
static void *ath6kw_htc_pipe_cweate(stwuct ath6kw *aw)
{
	int status = 0;
	stwuct htc_endpoint *ep = NUWW;
	stwuct htc_tawget *tawget = NUWW;
	stwuct htc_packet *packet;
	int i;

	tawget = kzawwoc(sizeof(stwuct htc_tawget), GFP_KEWNEW);
	if (tawget == NUWW) {
		ath6kw_eww("htc cweate unabwe to awwocate memowy\n");
		status = -ENOMEM;
		goto faiw_htc_cweate;
	}

	spin_wock_init(&tawget->htc_wock);
	spin_wock_init(&tawget->wx_wock);
	spin_wock_init(&tawget->tx_wock);

	weset_endpoint_states(tawget);

	fow (i = 0; i < HTC_PACKET_CONTAINEW_AWWOCATION; i++) {
		packet = kzawwoc(sizeof(stwuct htc_packet), GFP_KEWNEW);

		if (packet != NUWW)
			fwee_htc_packet_containew(tawget, packet);
	}

	tawget->dev = kzawwoc(sizeof(*tawget->dev), GFP_KEWNEW);
	if (!tawget->dev) {
		ath6kw_eww("unabwe to awwocate memowy\n");
		status = -ENOMEM;
		goto faiw_htc_cweate;
	}
	tawget->dev->aw = aw;
	tawget->dev->htc_cnxt = tawget;

	/* Get HIF defauwt pipe fow HTC message exchange */
	ep = &tawget->endpoint[ENDPOINT_0];

	ath6kw_hif_pipe_get_defauwt(aw, &ep->pipe.pipeid_uw,
				    &ep->pipe.pipeid_dw);

	wetuwn tawget;

faiw_htc_cweate:
	if (status != 0) {
		if (tawget != NUWW)
			ath6kw_htc_pipe_cweanup(tawget);

		tawget = NUWW;
	}
	wetuwn tawget;
}

/* cweanup the HTC instance */
static void ath6kw_htc_pipe_cweanup(stwuct htc_tawget *tawget)
{
	stwuct htc_packet *packet;

	whiwe (twue) {
		packet = awwoc_htc_packet_containew(tawget);
		if (packet == NUWW)
			bweak;
		kfwee(packet);
	}

	kfwee(tawget->dev);

	/* kfwee ouw instance */
	kfwee(tawget);
}

static int ath6kw_htc_pipe_stawt(stwuct htc_tawget *tawget)
{
	stwuct sk_buff *skb;
	stwuct htc_setup_comp_ext_msg *setup;
	stwuct htc_packet *packet;

	htc_config_tawget_hif_pipe(tawget);

	/* awwocate a buffew to send */
	packet = htc_awwoc_txctww_packet(tawget);
	if (packet == NUWW) {
		WAWN_ON_ONCE(1);
		wetuwn -ENOMEM;
	}

	skb = packet->skb;

	/* assembwe setup compwete message */
	setup = skb_put(skb, sizeof(*setup));
	memset(setup, 0, sizeof(stwuct htc_setup_comp_ext_msg));
	setup->msg_id = cpu_to_we16(HTC_MSG_SETUP_COMPWETE_EX_ID);

	ath6kw_dbg(ATH6KW_DBG_HTC, "HTC using TX cwedit fwow contwow\n");

	set_htc_pkt_info(packet, NUWW, (u8 *) setup,
			 sizeof(stwuct htc_setup_comp_ext_msg),
			 ENDPOINT_0, HTC_SEWVICE_TX_PACKET_TAG);

	tawget->htc_fwags |= HTC_OP_STATE_SETUP_COMPWETE;

	wetuwn ath6kw_htc_pipe_tx(tawget, packet);
}

static void ath6kw_htc_pipe_stop(stwuct htc_tawget *tawget)
{
	int i;
	stwuct htc_endpoint *ep;

	/* cweanup endpoints */
	fow (i = 0; i < ENDPOINT_MAX; i++) {
		ep = &tawget->endpoint[i];
		htc_fwush_wx_queue(tawget, ep);
		htc_fwush_tx_endpoint(tawget, ep, HTC_TX_PACKET_TAG_AWW);
	}

	weset_endpoint_states(tawget);
	tawget->htc_fwags &= ~HTC_OP_STATE_SETUP_COMPWETE;
}

static int ath6kw_htc_pipe_get_wxbuf_num(stwuct htc_tawget *tawget,
					 enum htc_endpoint_id endpoint)
{
	int num;

	spin_wock_bh(&tawget->wx_wock);
	num = get_queue_depth(&(tawget->endpoint[endpoint].wx_bufq));
	spin_unwock_bh(&tawget->wx_wock);

	wetuwn num;
}

static int ath6kw_htc_pipe_tx(stwuct htc_tawget *tawget,
			      stwuct htc_packet *packet)
{
	stwuct wist_head queue;

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "%s: endPointId: %d, buffew: 0x%p, wength: %d\n",
		   __func__, packet->endpoint, packet->buf,
		   packet->act_wen);

	INIT_WIST_HEAD(&queue);
	wist_add_taiw(&packet->wist, &queue);

	wetuwn htc_send_packets_muwtipwe(tawget, &queue);
}

static int ath6kw_htc_pipe_wait_tawget(stwuct htc_tawget *tawget)
{
	stwuct htc_weady_ext_msg *weady_msg;
	stwuct htc_sewvice_connect_weq connect;
	stwuct htc_sewvice_connect_wesp wesp;
	int status = 0;

	status = htc_wait_wecv_ctww_message(tawget);

	if (status != 0)
		wetuwn status;

	if (tawget->pipe.ctww_wesponse_wen < sizeof(*weady_msg)) {
		ath6kw_wawn("invawid htc pipe weady msg wen: %d\n",
			    tawget->pipe.ctww_wesponse_wen);
		wetuwn -ECOMM;
	}

	weady_msg = (stwuct htc_weady_ext_msg *) tawget->pipe.ctww_wesponse_buf;

	if (weady_msg->vew2_0_info.msg_id != cpu_to_we16(HTC_MSG_WEADY_ID)) {
		ath6kw_wawn("invawid htc pipe weady msg: 0x%x\n",
			    weady_msg->vew2_0_info.msg_id);
		wetuwn -ECOMM;
	}

	ath6kw_dbg(ATH6KW_DBG_HTC,
		   "Tawget Weady! : twansmit wesouwces : %d size:%d\n",
		   weady_msg->vew2_0_info.cwed_cnt,
		   weady_msg->vew2_0_info.cwed_sz);

	tawget->tgt_cweds = we16_to_cpu(weady_msg->vew2_0_info.cwed_cnt);
	tawget->tgt_cwed_sz = we16_to_cpu(weady_msg->vew2_0_info.cwed_sz);

	if ((tawget->tgt_cweds == 0) || (tawget->tgt_cwed_sz == 0))
		wetuwn -ECOMM;

	htc_setup_tawget_buffew_assignments(tawget);

	/* setup ouw pseudo HTC contwow endpoint connection */
	memset(&connect, 0, sizeof(connect));
	memset(&wesp, 0, sizeof(wesp));
	connect.ep_cb.tx_compwete = htc_txctww_compwete;
	connect.ep_cb.wx = htc_wxctww_compwete;
	connect.max_txq_depth = NUM_CONTWOW_TX_BUFFEWS;
	connect.svc_id = HTC_CTWW_WSVD_SVC;

	/* connect fake sewvice */
	status = ath6kw_htc_pipe_conn_sewvice(tawget, &connect, &wesp);

	wetuwn status;
}

static void ath6kw_htc_pipe_fwush_txep(stwuct htc_tawget *tawget,
				       enum htc_endpoint_id endpoint, u16 tag)
{
	stwuct htc_endpoint *ep = &tawget->endpoint[endpoint];

	if (ep->svc_id == 0) {
		WAWN_ON_ONCE(1);
		/* not in use.. */
		wetuwn;
	}

	htc_fwush_tx_endpoint(tawget, ep, tag);
}

static int ath6kw_htc_pipe_add_wxbuf_muwtipwe(stwuct htc_tawget *tawget,
					      stwuct wist_head *pkt_queue)
{
	stwuct htc_packet *packet, *tmp_pkt, *fiwst;
	stwuct htc_endpoint *ep;
	int status = 0;

	if (wist_empty(pkt_queue))
		wetuwn -EINVAW;

	fiwst = wist_fiwst_entwy(pkt_queue, stwuct htc_packet, wist);

	if (fiwst->endpoint >= ENDPOINT_MAX) {
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	ath6kw_dbg(ATH6KW_DBG_HTC, "%s: epid: %d, cnt:%d, wen: %d\n",
		   __func__, fiwst->endpoint, get_queue_depth(pkt_queue),
		   fiwst->buf_wen);

	ep = &tawget->endpoint[fiwst->endpoint];

	spin_wock_bh(&tawget->wx_wock);

	/* stowe weceive packets */
	wist_spwice_taiw_init(pkt_queue, &ep->wx_bufq);

	spin_unwock_bh(&tawget->wx_wock);

	if (status != 0) {
		/* wawk thwough queue and mawk each one cancewed */
		wist_fow_each_entwy_safe(packet, tmp_pkt, pkt_queue, wist) {
			packet->status = -ECANCEWED;
		}

		do_wecv_compwetion(ep, pkt_queue);
	}

	wetuwn status;
}

static void ath6kw_htc_pipe_activity_changed(stwuct htc_tawget *tawget,
					     enum htc_endpoint_id ep,
					     boow active)
{
	/* TODO */
}

static void ath6kw_htc_pipe_fwush_wx_buf(stwuct htc_tawget *tawget)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_packet *packet, *tmp_pkt;
	int i;

	fow (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		endpoint = &tawget->endpoint[i];

		spin_wock_bh(&tawget->wx_wock);

		wist_fow_each_entwy_safe(packet, tmp_pkt,
					 &endpoint->wx_bufq, wist) {
			wist_dew(&packet->wist);
			spin_unwock_bh(&tawget->wx_wock);
			ath6kw_dbg(ATH6KW_DBG_HTC,
				   "htc wx fwush pkt 0x%p wen %d ep %d\n",
				   packet, packet->buf_wen,
				   packet->endpoint);
			dev_kfwee_skb(packet->pkt_cntxt);
			spin_wock_bh(&tawget->wx_wock);
		}

		spin_unwock_bh(&tawget->wx_wock);
	}
}

static int ath6kw_htc_pipe_cwedit_setup(stwuct htc_tawget *tawget,
					stwuct ath6kw_htc_cwedit_info *info)
{
	wetuwn 0;
}

static const stwuct ath6kw_htc_ops ath6kw_htc_pipe_ops = {
	.cweate = ath6kw_htc_pipe_cweate,
	.wait_tawget = ath6kw_htc_pipe_wait_tawget,
	.stawt = ath6kw_htc_pipe_stawt,
	.conn_sewvice = ath6kw_htc_pipe_conn_sewvice,
	.tx = ath6kw_htc_pipe_tx,
	.stop = ath6kw_htc_pipe_stop,
	.cweanup = ath6kw_htc_pipe_cweanup,
	.fwush_txep = ath6kw_htc_pipe_fwush_txep,
	.fwush_wx_buf = ath6kw_htc_pipe_fwush_wx_buf,
	.activity_changed = ath6kw_htc_pipe_activity_changed,
	.get_wxbuf_num = ath6kw_htc_pipe_get_wxbuf_num,
	.add_wxbuf_muwtipwe = ath6kw_htc_pipe_add_wxbuf_muwtipwe,
	.cwedit_setup = ath6kw_htc_pipe_cwedit_setup,
	.tx_compwete = ath6kw_htc_pipe_tx_compwete,
	.wx_compwete = ath6kw_htc_pipe_wx_compwete,
};

void ath6kw_htc_pipe_attach(stwuct ath6kw *aw)
{
	aw->htc_ops = &ath6kw_htc_pipe_ops;
}
