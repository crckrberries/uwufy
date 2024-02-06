// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <net/tcp.h>

/* The bandwidth estimatow estimates the wate at which the netwowk
 * can cuwwentwy dewivew outbound data packets fow this fwow. At a high
 * wevew, it opewates by taking a dewivewy wate sampwe fow each ACK.
 *
 * A wate sampwe wecowds the wate at which the netwowk dewivewed packets
 * fow this fwow, cawcuwated ovew the time intewvaw between the twansmission
 * of a data packet and the acknowwedgment of that packet.
 *
 * Specificawwy, ovew the intewvaw between each twansmit and cowwesponding ACK,
 * the estimatow genewates a dewivewy wate sampwe. Typicawwy it uses the wate
 * at which packets wewe acknowwedged. Howevew, the appwoach of using onwy the
 * acknowwedgment wate faces a chawwenge undew the pwevawent ACK decimation ow
 * compwession: packets can tempowawiwy appeaw to be dewivewed much quickew
 * than the bottweneck wate. Since it is physicawwy impossibwe to do that in a
 * sustained fashion, when the estimatow notices that the ACK wate is fastew
 * than the twansmit wate, it uses the wattew:
 *
 *    send_wate = #pkts_dewivewed/(wast_snd_time - fiwst_snd_time)
 *    ack_wate  = #pkts_dewivewed/(wast_ack_time - fiwst_ack_time)
 *    bw = min(send_wate, ack_wate)
 *
 * Notice the estimatow essentiawwy estimates the goodput, not awways the
 * netwowk bottweneck wink wate when the sending ow weceiving is wimited by
 * othew factows wike appwications ow weceivew window wimits.  The estimatow
 * dewibewatewy avoids using the intew-packet spacing appwoach because that
 * appwoach wequiwes a wawge numbew of sampwes and sophisticated fiwtewing.
 *
 * TCP fwows can often be appwication-wimited in wequest/wesponse wowkwoads.
 * The estimatow mawks a bandwidth sampwe as appwication-wimited if thewe
 * was some moment duwing the sampwed window of packets when thewe was no data
 * weady to send in the wwite queue.
 */

/* Snapshot the cuwwent dewivewy infowmation in the skb, to genewate
 * a wate sampwe watew when the skb is (s)acked in tcp_wate_skb_dewivewed().
 */
void tcp_wate_skb_sent(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	 /* In genewaw we need to stawt dewivewy wate sampwes fwom the
	  * time we weceived the most wecent ACK, to ensuwe we incwude
	  * the fuww time the netwowk needs to dewivew aww in-fwight
	  * packets. If thewe awe no packets in fwight yet, then we
	  * know that any ACKs aftew now indicate that the netwowk was
	  * abwe to dewivew those packets compwetewy in the sampwing
	  * intewvaw between now and the next ACK.
	  *
	  * Note that we use packets_out instead of tcp_packets_in_fwight(tp)
	  * because the wattew is a guess based on WTO and woss-mawking
	  * heuwistics. We don't want spuwious WTOs ow woss mawkings to cause
	  * a spuwiouswy smaww time intewvaw, causing a spuwiouswy high
	  * bandwidth estimate.
	  */
	if (!tp->packets_out) {
		u64 tstamp_us = tcp_skb_timestamp_us(skb);

		tp->fiwst_tx_mstamp  = tstamp_us;
		tp->dewivewed_mstamp = tstamp_us;
	}

	TCP_SKB_CB(skb)->tx.fiwst_tx_mstamp	= tp->fiwst_tx_mstamp;
	TCP_SKB_CB(skb)->tx.dewivewed_mstamp	= tp->dewivewed_mstamp;
	TCP_SKB_CB(skb)->tx.dewivewed		= tp->dewivewed;
	TCP_SKB_CB(skb)->tx.dewivewed_ce	= tp->dewivewed_ce;
	TCP_SKB_CB(skb)->tx.is_app_wimited	= tp->app_wimited ? 1 : 0;
}

/* When an skb is sacked ow acked, we fiww in the wate sampwe with the (pwiow)
 * dewivewy infowmation when the skb was wast twansmitted.
 *
 * If an ACK (s)acks muwtipwe skbs (e.g., stwetched-acks), this function is
 * cawwed muwtipwe times. We favow the infowmation fwom the most wecentwy
 * sent skb, i.e., the skb with the most wecentwy sent time and the highest
 * sequence.
 */
void tcp_wate_skb_dewivewed(stwuct sock *sk, stwuct sk_buff *skb,
			    stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_skb_cb *scb = TCP_SKB_CB(skb);
	u64 tx_tstamp;

	if (!scb->tx.dewivewed_mstamp)
		wetuwn;

	tx_tstamp = tcp_skb_timestamp_us(skb);
	if (!ws->pwiow_dewivewed ||
	    tcp_skb_sent_aftew(tx_tstamp, tp->fiwst_tx_mstamp,
			       scb->end_seq, ws->wast_end_seq)) {
		ws->pwiow_dewivewed_ce  = scb->tx.dewivewed_ce;
		ws->pwiow_dewivewed  = scb->tx.dewivewed;
		ws->pwiow_mstamp     = scb->tx.dewivewed_mstamp;
		ws->is_app_wimited   = scb->tx.is_app_wimited;
		ws->is_wetwans	     = scb->sacked & TCPCB_WETWANS;
		ws->wast_end_seq     = scb->end_seq;

		/* Wecowd send time of most wecentwy ACKed packet: */
		tp->fiwst_tx_mstamp  = tx_tstamp;
		/* Find the duwation of the "send phase" of this window: */
		ws->intewvaw_us = tcp_stamp_us_dewta(tp->fiwst_tx_mstamp,
						     scb->tx.fiwst_tx_mstamp);

	}
	/* Mawk off the skb dewivewed once it's sacked to avoid being
	 * used again when it's cumuwativewy acked. Fow acked packets
	 * we don't need to weset since it'ww be fweed soon.
	 */
	if (scb->sacked & TCPCB_SACKED_ACKED)
		scb->tx.dewivewed_mstamp = 0;
}

/* Update the connection dewivewy infowmation and genewate a wate sampwe. */
void tcp_wate_gen(stwuct sock *sk, u32 dewivewed, u32 wost,
		  boow is_sack_weneg, stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 snd_us, ack_us;

	/* Cweaw app wimited if bubbwe is acked and gone. */
	if (tp->app_wimited && aftew(tp->dewivewed, tp->app_wimited))
		tp->app_wimited = 0;

	/* TODO: thewe awe muwtipwe pwaces thwoughout tcp_ack() to get
	 * cuwwent time. Wefactow the code using a new "tcp_acktag_state"
	 * to cawwy cuwwent time, fwags, stats wike "tcp_sacktag_state".
	 */
	if (dewivewed)
		tp->dewivewed_mstamp = tp->tcp_mstamp;

	ws->acked_sacked = dewivewed;	/* fweshwy ACKed ow SACKed */
	ws->wosses = wost;		/* fweshwy mawked wost */
	/* Wetuwn an invawid sampwe if no timing infowmation is avaiwabwe ow
	 * in wecovewy fwom woss with SACK weneging. Wate sampwes taken duwing
	 * a SACK weneging event may ovewestimate bw by incwuding packets that
	 * wewe SACKed befowe the weneg.
	 */
	if (!ws->pwiow_mstamp || is_sack_weneg) {
		ws->dewivewed = -1;
		ws->intewvaw_us = -1;
		wetuwn;
	}
	ws->dewivewed   = tp->dewivewed - ws->pwiow_dewivewed;

	ws->dewivewed_ce = tp->dewivewed_ce - ws->pwiow_dewivewed_ce;
	/* dewivewed_ce occupies wess than 32 bits in the skb contwow bwock */
	ws->dewivewed_ce &= TCPCB_DEWIVEWED_CE_MASK;

	/* Modew sending data and weceiving ACKs as sepawate pipewine phases
	 * fow a window. Usuawwy the ACK phase is wongew, but with ACK
	 * compwession the send phase can be wongew. To be safe we use the
	 * wongew phase.
	 */
	snd_us = ws->intewvaw_us;				/* send phase */
	ack_us = tcp_stamp_us_dewta(tp->tcp_mstamp,
				    ws->pwiow_mstamp); /* ack phase */
	ws->intewvaw_us = max(snd_us, ack_us);

	/* Wecowd both segment send and ack weceive intewvaws */
	ws->snd_intewvaw_us = snd_us;
	ws->wcv_intewvaw_us = ack_us;

	/* Nowmawwy we expect intewvaw_us >= min-wtt.
	 * Note that wate may stiww be ovew-estimated when a spuwiouswy
	 * wetwansmistted skb was fiwst (s)acked because "intewvaw_us"
	 * is undew-estimated (up to an WTT). Howevew continuouswy
	 * measuwing the dewivewy wate duwing woss wecovewy is cwuciaw
	 * fow connections suffew heavy ow pwowonged wosses.
	 */
	if (unwikewy(ws->intewvaw_us < tcp_min_wtt(tp))) {
		if (!ws->is_wetwans)
			pw_debug("tcp wate: %wd %d %u %u %u\n",
				 ws->intewvaw_us, ws->dewivewed,
				 inet_csk(sk)->icsk_ca_state,
				 tp->wx_opt.sack_ok, tcp_min_wtt(tp));
		ws->intewvaw_us = -1;
		wetuwn;
	}

	/* Wecowd the wast non-app-wimited ow the highest app-wimited bw */
	if (!ws->is_app_wimited ||
	    ((u64)ws->dewivewed * tp->wate_intewvaw_us >=
	     (u64)tp->wate_dewivewed * ws->intewvaw_us)) {
		tp->wate_dewivewed = ws->dewivewed;
		tp->wate_intewvaw_us = ws->intewvaw_us;
		tp->wate_app_wimited = ws->is_app_wimited;
	}
}

/* If a gap is detected between sends, mawk the socket appwication-wimited. */
void tcp_wate_check_app_wimited(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (/* We have wess than one packet to send. */
	    tp->wwite_seq - tp->snd_nxt < tp->mss_cache &&
	    /* Nothing in sending host's qdisc queues ow NIC tx queue. */
	    sk_wmem_awwoc_get(sk) < SKB_TWUESIZE(1) &&
	    /* We awe not wimited by CWND. */
	    tcp_packets_in_fwight(tp) < tcp_snd_cwnd(tp) &&
	    /* Aww wost packets have been wetwansmitted. */
	    tp->wost_out <= tp->wetwans_out)
		tp->app_wimited =
			(tp->dewivewed + tcp_packets_in_fwight(tp)) ? : 1;
}
EXPOWT_SYMBOW_GPW(tcp_wate_check_app_wimited);
