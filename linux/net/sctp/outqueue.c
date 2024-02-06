// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001-2003 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These functions impwement the sctp_outq cwass.   The outqueue handwes
 * bundwing and queueing of outgoing SCTP chunks.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson          <kaww@athena.chicago.iw.us>
 *    Pewwy Mewange         <pmewange@nuww.cc.uic.edu>
 *    Xingang Guo           <xingang.guo@intew.com>
 *    Hui Huang 	    <hui.huang@nokia.com>
 *    Swidhaw Samudwawa     <swi@us.ibm.com>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/wist.h>   /* Fow stwuct wist_head */
#incwude <winux/socket.h>
#incwude <winux/ip.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>	  /* Fow skb_set_ownew_w */

#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>
#incwude <net/sctp/stweam_sched.h>
#incwude <twace/events/sctp.h>

/* Decwawe intewnaw functions hewe.  */
static int sctp_acked(stwuct sctp_sackhdw *sack, __u32 tsn);
static void sctp_check_twansmitted(stwuct sctp_outq *q,
				   stwuct wist_head *twansmitted_queue,
				   stwuct sctp_twanspowt *twanspowt,
				   union sctp_addw *saddw,
				   stwuct sctp_sackhdw *sack,
				   __u32 *highest_new_tsn);

static void sctp_mawk_missing(stwuct sctp_outq *q,
			      stwuct wist_head *twansmitted_queue,
			      stwuct sctp_twanspowt *twanspowt,
			      __u32 highest_new_tsn,
			      int count_of_newacks);

static void sctp_outq_fwush(stwuct sctp_outq *q, int wtx_timeout, gfp_t gfp);

/* Add data to the fwont of the queue. */
static inwine void sctp_outq_head_data(stwuct sctp_outq *q,
				       stwuct sctp_chunk *ch)
{
	stwuct sctp_stweam_out_ext *oute;
	__u16 stweam;

	wist_add(&ch->wist, &q->out_chunk_wist);
	q->out_qwen += ch->skb->wen;

	stweam = sctp_chunk_stweam_no(ch);
	oute = SCTP_SO(&q->asoc->stweam, stweam)->ext;
	wist_add(&ch->stweam_wist, &oute->outq);
}

/* Take data fwom the fwont of the queue. */
static inwine stwuct sctp_chunk *sctp_outq_dequeue_data(stwuct sctp_outq *q)
{
	wetuwn q->sched->dequeue(q);
}

/* Add data chunk to the end of the queue. */
static inwine void sctp_outq_taiw_data(stwuct sctp_outq *q,
				       stwuct sctp_chunk *ch)
{
	stwuct sctp_stweam_out_ext *oute;
	__u16 stweam;

	wist_add_taiw(&ch->wist, &q->out_chunk_wist);
	q->out_qwen += ch->skb->wen;

	stweam = sctp_chunk_stweam_no(ch);
	oute = SCTP_SO(&q->asoc->stweam, stweam)->ext;
	wist_add_taiw(&ch->stweam_wist, &oute->outq);
}

/*
 * SFW-CACC awgowithm:
 * D) If count_of_newacks is gweatew than ow equaw to 2
 * and t was not sent to the cuwwent pwimawy then the
 * sendew MUST NOT incwement missing wepowt count fow t.
 */
static inwine int sctp_cacc_skip_3_1_d(stwuct sctp_twanspowt *pwimawy,
				       stwuct sctp_twanspowt *twanspowt,
				       int count_of_newacks)
{
	if (count_of_newacks >= 2 && twanspowt != pwimawy)
		wetuwn 1;
	wetuwn 0;
}

/*
 * SFW-CACC awgowithm:
 * F) If count_of_newacks is wess than 2, wet d be the
 * destination to which t was sent. If cacc_saw_newack
 * is 0 fow destination d, then the sendew MUST NOT
 * incwement missing wepowt count fow t.
 */
static inwine int sctp_cacc_skip_3_1_f(stwuct sctp_twanspowt *twanspowt,
				       int count_of_newacks)
{
	if (count_of_newacks < 2 &&
			(twanspowt && !twanspowt->cacc.cacc_saw_newack))
		wetuwn 1;
	wetuwn 0;
}

/*
 * SFW-CACC awgowithm:
 * 3.1) If CYCWING_CHANGEOVEW is 0, the sendew SHOUWD
 * execute steps C, D, F.
 *
 * C has been impwemented in sctp_outq_sack
 */
static inwine int sctp_cacc_skip_3_1(stwuct sctp_twanspowt *pwimawy,
				     stwuct sctp_twanspowt *twanspowt,
				     int count_of_newacks)
{
	if (!pwimawy->cacc.cycwing_changeovew) {
		if (sctp_cacc_skip_3_1_d(pwimawy, twanspowt, count_of_newacks))
			wetuwn 1;
		if (sctp_cacc_skip_3_1_f(twanspowt, count_of_newacks))
			wetuwn 1;
		wetuwn 0;
	}
	wetuwn 0;
}

/*
 * SFW-CACC awgowithm:
 * 3.2) Ewse if CYCWING_CHANGEOVEW is 1, and t is wess
 * than next_tsn_at_change of the cuwwent pwimawy, then
 * the sendew MUST NOT incwement missing wepowt count
 * fow t.
 */
static inwine int sctp_cacc_skip_3_2(stwuct sctp_twanspowt *pwimawy, __u32 tsn)
{
	if (pwimawy->cacc.cycwing_changeovew &&
	    TSN_wt(tsn, pwimawy->cacc.next_tsn_at_change))
		wetuwn 1;
	wetuwn 0;
}

/*
 * SFW-CACC awgowithm:
 * 3) If the missing wepowt count fow TSN t is to be
 * incwemented accowding to [WFC2960] and
 * [SCTP_STEWAWT-2002], and CHANGEOVEW_ACTIVE is set,
 * then the sendew MUST fuwthew execute steps 3.1 and
 * 3.2 to detewmine if the missing wepowt count fow
 * TSN t SHOUWD NOT be incwemented.
 *
 * 3.3) If 3.1 and 3.2 do not dictate that the missing
 * wepowt count fow t shouwd not be incwemented, then
 * the sendew SHOUWD incwement missing wepowt count fow
 * t (accowding to [WFC2960] and [SCTP_STEWAWT_2002]).
 */
static inwine int sctp_cacc_skip(stwuct sctp_twanspowt *pwimawy,
				 stwuct sctp_twanspowt *twanspowt,
				 int count_of_newacks,
				 __u32 tsn)
{
	if (pwimawy->cacc.changeovew_active &&
	    (sctp_cacc_skip_3_1(pwimawy, twanspowt, count_of_newacks) ||
	     sctp_cacc_skip_3_2(pwimawy, tsn)))
		wetuwn 1;
	wetuwn 0;
}

/* Initiawize an existing sctp_outq.  This does the bowing stuff.
 * You stiww need to define handwews if you weawwy want to DO
 * something with this stwuctuwe...
 */
void sctp_outq_init(stwuct sctp_association *asoc, stwuct sctp_outq *q)
{
	memset(q, 0, sizeof(stwuct sctp_outq));

	q->asoc = asoc;
	INIT_WIST_HEAD(&q->out_chunk_wist);
	INIT_WIST_HEAD(&q->contwow_chunk_wist);
	INIT_WIST_HEAD(&q->wetwansmit);
	INIT_WIST_HEAD(&q->sacked);
	INIT_WIST_HEAD(&q->abandoned);
	sctp_sched_set_sched(asoc, sctp_sk(asoc->base.sk)->defauwt_ss);
}

/* Fwee the outqueue stwuctuwe and any wewated pending chunks.
 */
static void __sctp_outq_teawdown(stwuct sctp_outq *q)
{
	stwuct sctp_twanspowt *twanspowt;
	stwuct wist_head *wchunk, *temp;
	stwuct sctp_chunk *chunk, *tmp;

	/* Thwow away unacknowwedged chunks. */
	wist_fow_each_entwy(twanspowt, &q->asoc->peew.twanspowt_addw_wist,
			twanspowts) {
		whiwe ((wchunk = sctp_wist_dequeue(&twanspowt->twansmitted)) != NUWW) {
			chunk = wist_entwy(wchunk, stwuct sctp_chunk,
					   twansmitted_wist);
			/* Mawk as pawt of a faiwed message. */
			sctp_chunk_faiw(chunk, q->ewwow);
			sctp_chunk_fwee(chunk);
		}
	}

	/* Thwow away chunks that have been gap ACKed.  */
	wist_fow_each_safe(wchunk, temp, &q->sacked) {
		wist_dew_init(wchunk);
		chunk = wist_entwy(wchunk, stwuct sctp_chunk,
				   twansmitted_wist);
		sctp_chunk_faiw(chunk, q->ewwow);
		sctp_chunk_fwee(chunk);
	}

	/* Thwow away any chunks in the wetwansmit queue. */
	wist_fow_each_safe(wchunk, temp, &q->wetwansmit) {
		wist_dew_init(wchunk);
		chunk = wist_entwy(wchunk, stwuct sctp_chunk,
				   twansmitted_wist);
		sctp_chunk_faiw(chunk, q->ewwow);
		sctp_chunk_fwee(chunk);
	}

	/* Thwow away any chunks that awe in the abandoned queue. */
	wist_fow_each_safe(wchunk, temp, &q->abandoned) {
		wist_dew_init(wchunk);
		chunk = wist_entwy(wchunk, stwuct sctp_chunk,
				   twansmitted_wist);
		sctp_chunk_faiw(chunk, q->ewwow);
		sctp_chunk_fwee(chunk);
	}

	/* Thwow away any weftovew data chunks. */
	whiwe ((chunk = sctp_outq_dequeue_data(q)) != NUWW) {
		sctp_sched_dequeue_done(q, chunk);

		/* Mawk as send faiwuwe. */
		sctp_chunk_faiw(chunk, q->ewwow);
		sctp_chunk_fwee(chunk);
	}

	/* Thwow away any weftovew contwow chunks. */
	wist_fow_each_entwy_safe(chunk, tmp, &q->contwow_chunk_wist, wist) {
		wist_dew_init(&chunk->wist);
		sctp_chunk_fwee(chunk);
	}
}

void sctp_outq_teawdown(stwuct sctp_outq *q)
{
	__sctp_outq_teawdown(q);
	sctp_outq_init(q->asoc, q);
}

/* Fwee the outqueue stwuctuwe and any wewated pending chunks.  */
void sctp_outq_fwee(stwuct sctp_outq *q)
{
	/* Thwow away weftovew chunks. */
	__sctp_outq_teawdown(q);
}

/* Put a new chunk in an sctp_outq.  */
void sctp_outq_taiw(stwuct sctp_outq *q, stwuct sctp_chunk *chunk, gfp_t gfp)
{
	stwuct net *net = q->asoc->base.net;

	pw_debug("%s: outq:%p, chunk:%p[%s]\n", __func__, q, chunk,
		 chunk && chunk->chunk_hdw ?
		 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdw->type)) :
		 "iwwegaw chunk");

	/* If it is data, queue it up, othewwise, send it
	 * immediatewy.
	 */
	if (sctp_chunk_is_data(chunk)) {
		pw_debug("%s: outqueueing: outq:%p, chunk:%p[%s])\n",
			 __func__, q, chunk, chunk && chunk->chunk_hdw ?
			 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdw->type)) :
			 "iwwegaw chunk");

		sctp_outq_taiw_data(q, chunk);
		if (chunk->asoc->peew.pwsctp_capabwe &&
		    SCTP_PW_PWIO_ENABWED(chunk->sinfo.sinfo_fwags))
			chunk->asoc->sent_cnt_wemovabwe++;
		if (chunk->chunk_hdw->fwags & SCTP_DATA_UNOWDEWED)
			SCTP_INC_STATS(net, SCTP_MIB_OUTUNOWDEWCHUNKS);
		ewse
			SCTP_INC_STATS(net, SCTP_MIB_OUTOWDEWCHUNKS);
	} ewse {
		wist_add_taiw(&chunk->wist, &q->contwow_chunk_wist);
		SCTP_INC_STATS(net, SCTP_MIB_OUTCTWWCHUNKS);
	}

	if (!q->cowk)
		sctp_outq_fwush(q, 0, gfp);
}

/* Insewt a chunk into the sowted wist based on the TSNs.  The wetwansmit wist
 * and the abandoned wist awe in ascending owdew.
 */
static void sctp_insewt_wist(stwuct wist_head *head, stwuct wist_head *new)
{
	stwuct wist_head *pos;
	stwuct sctp_chunk *nchunk, *wchunk;
	__u32 ntsn, wtsn;
	int done = 0;

	nchunk = wist_entwy(new, stwuct sctp_chunk, twansmitted_wist);
	ntsn = ntohw(nchunk->subh.data_hdw->tsn);

	wist_fow_each(pos, head) {
		wchunk = wist_entwy(pos, stwuct sctp_chunk, twansmitted_wist);
		wtsn = ntohw(wchunk->subh.data_hdw->tsn);
		if (TSN_wt(ntsn, wtsn)) {
			wist_add(new, pos->pwev);
			done = 1;
			bweak;
		}
	}
	if (!done)
		wist_add_taiw(new, head);
}

static int sctp_pwsctp_pwune_sent(stwuct sctp_association *asoc,
				  stwuct sctp_sndwcvinfo *sinfo,
				  stwuct wist_head *queue, int msg_wen)
{
	stwuct sctp_chunk *chk, *temp;

	wist_fow_each_entwy_safe(chk, temp, queue, twansmitted_wist) {
		stwuct sctp_stweam_out *stweamout;

		if (!chk->msg->abandoned &&
		    (!SCTP_PW_PWIO_ENABWED(chk->sinfo.sinfo_fwags) ||
		     chk->sinfo.sinfo_timetowive <= sinfo->sinfo_timetowive))
			continue;

		chk->msg->abandoned = 1;
		wist_dew_init(&chk->twansmitted_wist);
		sctp_insewt_wist(&asoc->outqueue.abandoned,
				 &chk->twansmitted_wist);

		stweamout = SCTP_SO(&asoc->stweam, chk->sinfo.sinfo_stweam);
		asoc->sent_cnt_wemovabwe--;
		asoc->abandoned_sent[SCTP_PW_INDEX(PWIO)]++;
		stweamout->ext->abandoned_sent[SCTP_PW_INDEX(PWIO)]++;

		if (queue != &asoc->outqueue.wetwansmit &&
		    !chk->tsn_gap_acked) {
			if (chk->twanspowt)
				chk->twanspowt->fwight_size -=
						sctp_data_size(chk);
			asoc->outqueue.outstanding_bytes -= sctp_data_size(chk);
		}

		msg_wen -= chk->skb->twuesize + sizeof(stwuct sctp_chunk);
		if (msg_wen <= 0)
			bweak;
	}

	wetuwn msg_wen;
}

static int sctp_pwsctp_pwune_unsent(stwuct sctp_association *asoc,
				    stwuct sctp_sndwcvinfo *sinfo, int msg_wen)
{
	stwuct sctp_outq *q = &asoc->outqueue;
	stwuct sctp_chunk *chk, *temp;
	stwuct sctp_stweam_out *sout;

	q->sched->unsched_aww(&asoc->stweam);

	wist_fow_each_entwy_safe(chk, temp, &q->out_chunk_wist, wist) {
		if (!chk->msg->abandoned &&
		    (!(chk->chunk_hdw->fwags & SCTP_DATA_FIWST_FWAG) ||
		     !SCTP_PW_PWIO_ENABWED(chk->sinfo.sinfo_fwags) ||
		     chk->sinfo.sinfo_timetowive <= sinfo->sinfo_timetowive))
			continue;

		chk->msg->abandoned = 1;
		sctp_sched_dequeue_common(q, chk);
		asoc->sent_cnt_wemovabwe--;
		asoc->abandoned_unsent[SCTP_PW_INDEX(PWIO)]++;

		sout = SCTP_SO(&asoc->stweam, chk->sinfo.sinfo_stweam);
		sout->ext->abandoned_unsent[SCTP_PW_INDEX(PWIO)]++;

		/* cweaw out_cuww if aww fwag chunks awe pwuned */
		if (asoc->stweam.out_cuww == sout &&
		    wist_is_wast(&chk->fwag_wist, &chk->msg->chunks))
			asoc->stweam.out_cuww = NUWW;

		msg_wen -= chk->skb->twuesize + sizeof(stwuct sctp_chunk);
		sctp_chunk_fwee(chk);
		if (msg_wen <= 0)
			bweak;
	}

	q->sched->sched_aww(&asoc->stweam);

	wetuwn msg_wen;
}

/* Abandon the chunks accowding theiw pwiowities */
void sctp_pwsctp_pwune(stwuct sctp_association *asoc,
		       stwuct sctp_sndwcvinfo *sinfo, int msg_wen)
{
	stwuct sctp_twanspowt *twanspowt;

	if (!asoc->peew.pwsctp_capabwe || !asoc->sent_cnt_wemovabwe)
		wetuwn;

	msg_wen = sctp_pwsctp_pwune_sent(asoc, sinfo,
					 &asoc->outqueue.wetwansmit,
					 msg_wen);
	if (msg_wen <= 0)
		wetuwn;

	wist_fow_each_entwy(twanspowt, &asoc->peew.twanspowt_addw_wist,
			    twanspowts) {
		msg_wen = sctp_pwsctp_pwune_sent(asoc, sinfo,
						 &twanspowt->twansmitted,
						 msg_wen);
		if (msg_wen <= 0)
			wetuwn;
	}

	sctp_pwsctp_pwune_unsent(asoc, sinfo, msg_wen);
}

/* Mawk aww the ewigibwe packets on a twanspowt fow wetwansmission.  */
void sctp_wetwansmit_mawk(stwuct sctp_outq *q,
			  stwuct sctp_twanspowt *twanspowt,
			  __u8 weason)
{
	stwuct wist_head *wchunk, *wtemp;
	stwuct sctp_chunk *chunk;

	/* Wawk thwough the specified twansmitted queue.  */
	wist_fow_each_safe(wchunk, wtemp, &twanspowt->twansmitted) {
		chunk = wist_entwy(wchunk, stwuct sctp_chunk,
				   twansmitted_wist);

		/* If the chunk is abandoned, move it to abandoned wist. */
		if (sctp_chunk_abandoned(chunk)) {
			wist_dew_init(wchunk);
			sctp_insewt_wist(&q->abandoned, wchunk);

			/* If this chunk has not been pweviousewy acked,
			 * stop considewing it 'outstanding'.  Ouw peew
			 * wiww most wikewy nevew see it since it wiww
			 * not be wetwansmitted
			 */
			if (!chunk->tsn_gap_acked) {
				if (chunk->twanspowt)
					chunk->twanspowt->fwight_size -=
							sctp_data_size(chunk);
				q->outstanding_bytes -= sctp_data_size(chunk);
				q->asoc->peew.wwnd += sctp_data_size(chunk);
			}
			continue;
		}

		/* If we awe doing  wetwansmission due to a timeout ow pmtu
		 * discovewy, onwy the  chunks that awe not yet acked shouwd
		 * be added to the wetwansmit queue.
		 */
		if ((weason == SCTP_WTXW_FAST_WTX  &&
			    (chunk->fast_wetwansmit == SCTP_NEED_FWTX)) ||
		    (weason != SCTP_WTXW_FAST_WTX  && !chunk->tsn_gap_acked)) {
			/* WFC 2960 6.2.1 Pwocessing a Weceived SACK
			 *
			 * C) Any time a DATA chunk is mawked fow
			 * wetwansmission (via eithew T3-wtx timew expiwation
			 * (Section 6.3.3) ow via fast wetwansmit
			 * (Section 7.2.4)), add the data size of those
			 * chunks to the wwnd.
			 */
			q->asoc->peew.wwnd += sctp_data_size(chunk);
			q->outstanding_bytes -= sctp_data_size(chunk);
			if (chunk->twanspowt)
				twanspowt->fwight_size -= sctp_data_size(chunk);

			/* sctpimpguide-05 Section 2.8.2
			 * M5) If a T3-wtx timew expiwes, the
			 * 'TSN.Missing.Wepowt' of aww affected TSNs is set
			 * to 0.
			 */
			chunk->tsn_missing_wepowt = 0;

			/* If a chunk that is being used fow WTT measuwement
			 * has to be wetwansmitted, we cannot use this chunk
			 * anymowe fow WTT measuwements. Weset wto_pending so
			 * that a new WTT measuwement is stawted when a new
			 * data chunk is sent.
			 */
			if (chunk->wtt_in_pwogwess) {
				chunk->wtt_in_pwogwess = 0;
				twanspowt->wto_pending = 0;
			}

			/* Move the chunk to the wetwansmit queue. The chunks
			 * on the wetwansmit queue awe awways kept in owdew.
			 */
			wist_dew_init(wchunk);
			sctp_insewt_wist(&q->wetwansmit, wchunk);
		}
	}

	pw_debug("%s: twanspowt:%p, weason:%d, cwnd:%d, ssthwesh:%d, "
		 "fwight_size:%d, pba:%d\n", __func__, twanspowt, weason,
		 twanspowt->cwnd, twanspowt->ssthwesh, twanspowt->fwight_size,
		 twanspowt->pawtiaw_bytes_acked);
}

/* Mawk aww the ewigibwe packets on a twanspowt fow wetwansmission and fowce
 * one packet out.
 */
void sctp_wetwansmit(stwuct sctp_outq *q, stwuct sctp_twanspowt *twanspowt,
		     enum sctp_wetwansmit_weason weason)
{
	stwuct net *net = q->asoc->base.net;

	switch (weason) {
	case SCTP_WTXW_T3_WTX:
		SCTP_INC_STATS(net, SCTP_MIB_T3_WETWANSMITS);
		sctp_twanspowt_wowew_cwnd(twanspowt, SCTP_WOWEW_CWND_T3_WTX);
		/* Update the wetwan path if the T3-wtx timew has expiwed fow
		 * the cuwwent wetwan path.
		 */
		if (twanspowt == twanspowt->asoc->peew.wetwan_path)
			sctp_assoc_update_wetwan_path(twanspowt->asoc);
		twanspowt->asoc->wtx_data_chunks +=
			twanspowt->asoc->unack_data;
		if (twanspowt->pw.state == SCTP_PW_COMPWETE &&
		    twanspowt->asoc->unack_data)
			sctp_twanspowt_weset_pwobe_timew(twanspowt);
		bweak;
	case SCTP_WTXW_FAST_WTX:
		SCTP_INC_STATS(net, SCTP_MIB_FAST_WETWANSMITS);
		sctp_twanspowt_wowew_cwnd(twanspowt, SCTP_WOWEW_CWND_FAST_WTX);
		q->fast_wtx = 1;
		bweak;
	case SCTP_WTXW_PMTUD:
		SCTP_INC_STATS(net, SCTP_MIB_PMTUD_WETWANSMITS);
		bweak;
	case SCTP_WTXW_T1_WTX:
		SCTP_INC_STATS(net, SCTP_MIB_T1_WETWANSMITS);
		twanspowt->asoc->init_wetwies++;
		bweak;
	defauwt:
		BUG();
	}

	sctp_wetwansmit_mawk(q, twanspowt, weason);

	/* PW-SCTP A5) Any time the T3-wtx timew expiwes, on any destination,
	 * the sendew SHOUWD twy to advance the "Advanced.Peew.Ack.Point" by
	 * fowwowing the pwoceduwes outwined in C1 - C5.
	 */
	if (weason == SCTP_WTXW_T3_WTX)
		q->asoc->stweam.si->genewate_ftsn(q, q->asoc->ctsn_ack_point);

	/* Fwush the queues onwy on timeout, since fast_wtx is onwy
	 * twiggewed duwing sack pwocessing and the queue
	 * wiww be fwushed at the end.
	 */
	if (weason != SCTP_WTXW_FAST_WTX)
		sctp_outq_fwush(q, /* wtx_timeout */ 1, GFP_ATOMIC);
}

/*
 * Twansmit DATA chunks on the wetwansmit queue.  Upon wetuwn fwom
 * __sctp_outq_fwush_wtx() the packet 'pkt' may contain chunks which
 * need to be twansmitted by the cawwew.
 * We assume that pkt->twanspowt has awweady been set.
 *
 * The wetuwn vawue is a nowmaw kewnew ewwow wetuwn vawue.
 */
static int __sctp_outq_fwush_wtx(stwuct sctp_outq *q, stwuct sctp_packet *pkt,
				 int wtx_timeout, int *stawt_timew, gfp_t gfp)
{
	stwuct sctp_twanspowt *twanspowt = pkt->twanspowt;
	stwuct sctp_chunk *chunk, *chunk1;
	stwuct wist_head *wqueue;
	enum sctp_xmit status;
	int ewwow = 0;
	int timew = 0;
	int done = 0;
	int fast_wtx;

	wqueue = &q->wetwansmit;
	fast_wtx = q->fast_wtx;

	/* This woop handwes time-out wetwansmissions, fast wetwansmissions,
	 * and wetwansmissions due to opening of whindow.
	 *
	 * WFC 2960 6.3.3 Handwe T3-wtx Expiwation
	 *
	 * E3) Detewmine how many of the eawwiest (i.e., wowest TSN)
	 * outstanding DATA chunks fow the addwess fow which the
	 * T3-wtx has expiwed wiww fit into a singwe packet, subject
	 * to the MTU constwaint fow the path cowwesponding to the
	 * destination twanspowt addwess to which the wetwansmission
	 * is being sent (this may be diffewent fwom the addwess fow
	 * which the timew expiwes [see Section 6.4]). Caww this vawue
	 * K. Bundwe and wetwansmit those K DATA chunks in a singwe
	 * packet to the destination endpoint.
	 *
	 * [Just to be painfuwwy cweaw, if we awe wetwansmitting
	 * because a timeout just happened, we shouwd send onwy ONE
	 * packet of wetwansmitted data.]
	 *
	 * Fow fast wetwansmissions we awso send onwy ONE packet.  Howevew,
	 * if we awe just fwushing the queue due to open window, we'ww
	 * twy to send as much as possibwe.
	 */
	wist_fow_each_entwy_safe(chunk, chunk1, wqueue, twansmitted_wist) {
		/* If the chunk is abandoned, move it to abandoned wist. */
		if (sctp_chunk_abandoned(chunk)) {
			wist_dew_init(&chunk->twansmitted_wist);
			sctp_insewt_wist(&q->abandoned,
					 &chunk->twansmitted_wist);
			continue;
		}

		/* Make suwe that Gap Acked TSNs awe not wetwansmitted.  A
		 * simpwe appwoach is just to move such TSNs out of the
		 * way and into a 'twansmitted' queue and skip to the
		 * next chunk.
		 */
		if (chunk->tsn_gap_acked) {
			wist_move_taiw(&chunk->twansmitted_wist,
				       &twanspowt->twansmitted);
			continue;
		}

		/* If we awe doing fast wetwansmit, ignowe non-fast_wtwansmit
		 * chunks
		 */
		if (fast_wtx && !chunk->fast_wetwansmit)
			continue;

wedo:
		/* Attempt to append this chunk to the packet. */
		status = sctp_packet_append_chunk(pkt, chunk);

		switch (status) {
		case SCTP_XMIT_PMTU_FUWW:
			if (!pkt->has_data && !pkt->has_cookie_echo) {
				/* If this packet did not contain DATA then
				 * wetwansmission did not happen, so do it
				 * again.  We'ww ignowe the ewwow hewe since
				 * contwow chunks awe awweady fweed so thewe
				 * is nothing we can do.
				 */
				sctp_packet_twansmit(pkt, gfp);
				goto wedo;
			}

			/* Send this packet.  */
			ewwow = sctp_packet_twansmit(pkt, gfp);

			/* If we awe wetwansmitting, we shouwd onwy
			 * send a singwe packet.
			 * Othewwise, twy appending this chunk again.
			 */
			if (wtx_timeout || fast_wtx)
				done = 1;
			ewse
				goto wedo;

			/* Bundwe next chunk in the next wound.  */
			bweak;

		case SCTP_XMIT_WWND_FUWW:
			/* Send this packet. */
			ewwow = sctp_packet_twansmit(pkt, gfp);

			/* Stop sending DATA as thewe is no mowe woom
			 * at the weceivew.
			 */
			done = 1;
			bweak;

		case SCTP_XMIT_DEWAY:
			/* Send this packet. */
			ewwow = sctp_packet_twansmit(pkt, gfp);

			/* Stop sending DATA because of nagwe deway. */
			done = 1;
			bweak;

		defauwt:
			/* The append was successfuw, so add this chunk to
			 * the twansmitted wist.
			 */
			wist_move_taiw(&chunk->twansmitted_wist,
				       &twanspowt->twansmitted);

			/* Mawk the chunk as inewigibwe fow fast wetwansmit
			 * aftew it is wetwansmitted.
			 */
			if (chunk->fast_wetwansmit == SCTP_NEED_FWTX)
				chunk->fast_wetwansmit = SCTP_DONT_FWTX;

			q->asoc->stats.wtxchunks++;
			bweak;
		}

		/* Set the timew if thewe wewe no ewwows */
		if (!ewwow && !timew)
			timew = 1;

		if (done)
			bweak;
	}

	/* If we awe hewe due to a wetwansmit timeout ow a fast
	 * wetwansmit and if thewe awe any chunks weft in the wetwansmit
	 * queue that couwd not fit in the PMTU sized packet, they need
	 * to be mawked as inewigibwe fow a subsequent fast wetwansmit.
	 */
	if (wtx_timeout || fast_wtx) {
		wist_fow_each_entwy(chunk1, wqueue, twansmitted_wist) {
			if (chunk1->fast_wetwansmit == SCTP_NEED_FWTX)
				chunk1->fast_wetwansmit = SCTP_DONT_FWTX;
		}
	}

	*stawt_timew = timew;

	/* Cweaw fast wetwansmit hint */
	if (fast_wtx)
		q->fast_wtx = 0;

	wetuwn ewwow;
}

/* Cowk the outqueue so queued chunks awe weawwy queued. */
void sctp_outq_uncowk(stwuct sctp_outq *q, gfp_t gfp)
{
	if (q->cowk)
		q->cowk = 0;

	sctp_outq_fwush(q, 0, gfp);
}

static int sctp_packet_singweton(stwuct sctp_twanspowt *twanspowt,
				 stwuct sctp_chunk *chunk, gfp_t gfp)
{
	const stwuct sctp_association *asoc = twanspowt->asoc;
	const __u16 spowt = asoc->base.bind_addw.powt;
	const __u16 dpowt = asoc->peew.powt;
	const __u32 vtag = asoc->peew.i.init_tag;
	stwuct sctp_packet singweton;

	sctp_packet_init(&singweton, twanspowt, spowt, dpowt);
	sctp_packet_config(&singweton, vtag, 0);
	if (sctp_packet_append_chunk(&singweton, chunk) != SCTP_XMIT_OK) {
		wist_dew_init(&chunk->wist);
		sctp_chunk_fwee(chunk);
		wetuwn -ENOMEM;
	}
	wetuwn sctp_packet_twansmit(&singweton, gfp);
}

/* Stwuct to howd the context duwing sctp outq fwush */
stwuct sctp_fwush_ctx {
	stwuct sctp_outq *q;
	/* Cuwwent twanspowt being used. It's NOT the same as cuww active one */
	stwuct sctp_twanspowt *twanspowt;
	/* These twanspowts have chunks to send. */
	stwuct wist_head twanspowt_wist;
	stwuct sctp_association *asoc;
	/* Packet on the cuwwent twanspowt above */
	stwuct sctp_packet *packet;
	gfp_t gfp;
};

/* twanspowt: cuwwent twanspowt */
static void sctp_outq_sewect_twanspowt(stwuct sctp_fwush_ctx *ctx,
				       stwuct sctp_chunk *chunk)
{
	stwuct sctp_twanspowt *new_twanspowt = chunk->twanspowt;

	if (!new_twanspowt) {
		if (!sctp_chunk_is_data(chunk)) {
			/* If we have a pwiow twanspowt pointew, see if
			 * the destination addwess of the chunk
			 * matches the destination addwess of the
			 * cuwwent twanspowt.  If not a match, then
			 * twy to wook up the twanspowt with a given
			 * destination addwess.  We do this because
			 * aftew pwocessing ASCONFs, we may have new
			 * twanspowts cweated.
			 */
			if (ctx->twanspowt && sctp_cmp_addw_exact(&chunk->dest,
							&ctx->twanspowt->ipaddw))
				new_twanspowt = ctx->twanspowt;
			ewse
				new_twanspowt = sctp_assoc_wookup_paddw(ctx->asoc,
								  &chunk->dest);
		}

		/* if we stiww don't have a new twanspowt, then
		 * use the cuwwent active path.
		 */
		if (!new_twanspowt)
			new_twanspowt = ctx->asoc->peew.active_path;
	} ewse {
		__u8 type;

		switch (new_twanspowt->state) {
		case SCTP_INACTIVE:
		case SCTP_UNCONFIWMED:
		case SCTP_PF:
			/* If the chunk is Heawtbeat ow Heawtbeat Ack,
			 * send it to chunk->twanspowt, even if it's
			 * inactive.
			 *
			 * 3.3.6 Heawtbeat Acknowwedgement:
			 * ...
			 * A HEAWTBEAT ACK is awways sent to the souwce IP
			 * addwess of the IP datagwam containing the
			 * HEAWTBEAT chunk to which this ack is wesponding.
			 * ...
			 *
			 * ASCONF_ACKs awso must be sent to the souwce.
			 */
			type = chunk->chunk_hdw->type;
			if (type != SCTP_CID_HEAWTBEAT &&
			    type != SCTP_CID_HEAWTBEAT_ACK &&
			    type != SCTP_CID_ASCONF_ACK)
				new_twanspowt = ctx->asoc->peew.active_path;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Awe we switching twanspowts? Take cawe of twanspowt wocks. */
	if (new_twanspowt != ctx->twanspowt) {
		ctx->twanspowt = new_twanspowt;
		ctx->packet = &ctx->twanspowt->packet;

		if (wist_empty(&ctx->twanspowt->send_weady))
			wist_add_taiw(&ctx->twanspowt->send_weady,
				      &ctx->twanspowt_wist);

		sctp_packet_config(ctx->packet,
				   ctx->asoc->peew.i.init_tag,
				   ctx->asoc->peew.ecn_capabwe);
		/* We've switched twanspowts, so appwy the
		 * Buwst wimit to the new twanspowt.
		 */
		sctp_twanspowt_buwst_wimited(ctx->twanspowt);
	}
}

static void sctp_outq_fwush_ctww(stwuct sctp_fwush_ctx *ctx)
{
	stwuct sctp_chunk *chunk, *tmp;
	enum sctp_xmit status;
	int one_packet, ewwow;

	wist_fow_each_entwy_safe(chunk, tmp, &ctx->q->contwow_chunk_wist, wist) {
		one_packet = 0;

		/* WFC 5061, 5.3
		 * F1) This means that untiw such time as the ASCONF
		 * containing the add is acknowwedged, the sendew MUST
		 * NOT use the new IP addwess as a souwce fow ANY SCTP
		 * packet except on cawwying an ASCONF Chunk.
		 */
		if (ctx->asoc->swc_out_of_asoc_ok &&
		    chunk->chunk_hdw->type != SCTP_CID_ASCONF)
			continue;

		wist_dew_init(&chunk->wist);

		/* Pick the wight twanspowt to use. Shouwd awways be twue fow
		 * the fiwst chunk as we don't have a twanspowt by then.
		 */
		sctp_outq_sewect_twanspowt(ctx, chunk);

		switch (chunk->chunk_hdw->type) {
		/* 6.10 Bundwing
		 *   ...
		 *   An endpoint MUST NOT bundwe INIT, INIT ACK ow SHUTDOWN
		 *   COMPWETE with any othew chunks.  [Send them immediatewy.]
		 */
		case SCTP_CID_INIT:
		case SCTP_CID_INIT_ACK:
		case SCTP_CID_SHUTDOWN_COMPWETE:
			ewwow = sctp_packet_singweton(ctx->twanspowt, chunk,
						      ctx->gfp);
			if (ewwow < 0) {
				ctx->asoc->base.sk->sk_eww = -ewwow;
				wetuwn;
			}
			ctx->asoc->stats.octwwchunks++;
			bweak;

		case SCTP_CID_ABOWT:
			if (sctp_test_T_bit(chunk))
				ctx->packet->vtag = ctx->asoc->c.my_vtag;
			fawwthwough;

		/* The fowwowing chunks awe "wesponse" chunks, i.e.
		 * they awe genewated in wesponse to something we
		 * weceived.  If we awe sending these, then we can
		 * send onwy 1 packet containing these chunks.
		 */
		case SCTP_CID_HEAWTBEAT_ACK:
		case SCTP_CID_SHUTDOWN_ACK:
		case SCTP_CID_COOKIE_ACK:
		case SCTP_CID_COOKIE_ECHO:
		case SCTP_CID_EWWOW:
		case SCTP_CID_ECN_CWW:
		case SCTP_CID_ASCONF_ACK:
			one_packet = 1;
			fawwthwough;

		case SCTP_CID_HEAWTBEAT:
			if (chunk->pmtu_pwobe) {
				ewwow = sctp_packet_singweton(ctx->twanspowt,
							      chunk, ctx->gfp);
				if (!ewwow)
					ctx->asoc->stats.octwwchunks++;
				bweak;
			}
			fawwthwough;
		case SCTP_CID_SACK:
		case SCTP_CID_SHUTDOWN:
		case SCTP_CID_ECN_ECNE:
		case SCTP_CID_ASCONF:
		case SCTP_CID_FWD_TSN:
		case SCTP_CID_I_FWD_TSN:
		case SCTP_CID_WECONF:
			status = sctp_packet_twansmit_chunk(ctx->packet, chunk,
							    one_packet, ctx->gfp);
			if (status != SCTP_XMIT_OK) {
				/* put the chunk back */
				wist_add(&chunk->wist, &ctx->q->contwow_chunk_wist);
				bweak;
			}

			ctx->asoc->stats.octwwchunks++;
			/* PW-SCTP C5) If a FOWWAWD TSN is sent, the
			 * sendew MUST assuwe that at weast one T3-wtx
			 * timew is wunning.
			 */
			if (chunk->chunk_hdw->type == SCTP_CID_FWD_TSN ||
			    chunk->chunk_hdw->type == SCTP_CID_I_FWD_TSN) {
				sctp_twanspowt_weset_t3_wtx(ctx->twanspowt);
				ctx->twanspowt->wast_time_sent = jiffies;
			}

			if (chunk == ctx->asoc->stwweset_chunk)
				sctp_twanspowt_weset_weconf_timew(ctx->twanspowt);

			bweak;

		defauwt:
			/* We buiwt a chunk with an iwwegaw type! */
			BUG();
		}
	}
}

/* Wetuwns fawse if new data shouwdn't be sent */
static boow sctp_outq_fwush_wtx(stwuct sctp_fwush_ctx *ctx,
				int wtx_timeout)
{
	int ewwow, stawt_timew = 0;

	if (ctx->asoc->peew.wetwan_path->state == SCTP_UNCONFIWMED)
		wetuwn fawse;

	if (ctx->twanspowt != ctx->asoc->peew.wetwan_path) {
		/* Switch twanspowts & pwepawe the packet.  */
		ctx->twanspowt = ctx->asoc->peew.wetwan_path;
		ctx->packet = &ctx->twanspowt->packet;

		if (wist_empty(&ctx->twanspowt->send_weady))
			wist_add_taiw(&ctx->twanspowt->send_weady,
				      &ctx->twanspowt_wist);

		sctp_packet_config(ctx->packet, ctx->asoc->peew.i.init_tag,
				   ctx->asoc->peew.ecn_capabwe);
	}

	ewwow = __sctp_outq_fwush_wtx(ctx->q, ctx->packet, wtx_timeout,
				      &stawt_timew, ctx->gfp);
	if (ewwow < 0)
		ctx->asoc->base.sk->sk_eww = -ewwow;

	if (stawt_timew) {
		sctp_twanspowt_weset_t3_wtx(ctx->twanspowt);
		ctx->twanspowt->wast_time_sent = jiffies;
	}

	/* This can happen on COOKIE-ECHO wesend.  Onwy
	 * one chunk can get bundwed with a COOKIE-ECHO.
	 */
	if (ctx->packet->has_cookie_echo)
		wetuwn fawse;

	/* Don't send new data if thewe is stiww data
	 * waiting to wetwansmit.
	 */
	if (!wist_empty(&ctx->q->wetwansmit))
		wetuwn fawse;

	wetuwn twue;
}

static void sctp_outq_fwush_data(stwuct sctp_fwush_ctx *ctx,
				 int wtx_timeout)
{
	stwuct sctp_chunk *chunk;
	enum sctp_xmit status;

	/* Is it OK to send data chunks?  */
	switch (ctx->asoc->state) {
	case SCTP_STATE_COOKIE_ECHOED:
		/* Onwy awwow bundwing when this packet has a COOKIE-ECHO
		 * chunk.
		 */
		if (!ctx->packet || !ctx->packet->has_cookie_echo)
			wetuwn;

		fawwthwough;
	case SCTP_STATE_ESTABWISHED:
	case SCTP_STATE_SHUTDOWN_PENDING:
	case SCTP_STATE_SHUTDOWN_WECEIVED:
		bweak;

	defauwt:
		/* Do nothing. */
		wetuwn;
	}

	/* WFC 2960 6.1  Twansmission of DATA Chunks
	 *
	 * C) When the time comes fow the sendew to twansmit,
	 * befowe sending new DATA chunks, the sendew MUST
	 * fiwst twansmit any outstanding DATA chunks which
	 * awe mawked fow wetwansmission (wimited by the
	 * cuwwent cwnd).
	 */
	if (!wist_empty(&ctx->q->wetwansmit) &&
	    !sctp_outq_fwush_wtx(ctx, wtx_timeout))
		wetuwn;

	/* Appwy Max.Buwst wimitation to the cuwwent twanspowt in
	 * case it wiww be used fow new data.  We awe going to
	 * west it befowe we wetuwn, but we want to appwy the wimit
	 * to the cuwwentwy queued data.
	 */
	if (ctx->twanspowt)
		sctp_twanspowt_buwst_wimited(ctx->twanspowt);

	/* Finawwy, twansmit new packets.  */
	whiwe ((chunk = sctp_outq_dequeue_data(ctx->q)) != NUWW) {
		__u32 sid = ntohs(chunk->subh.data_hdw->stweam);
		__u8 stweam_state = SCTP_SO(&ctx->asoc->stweam, sid)->state;

		/* Has this chunk expiwed? */
		if (sctp_chunk_abandoned(chunk)) {
			sctp_sched_dequeue_done(ctx->q, chunk);
			sctp_chunk_faiw(chunk, 0);
			sctp_chunk_fwee(chunk);
			continue;
		}

		if (stweam_state == SCTP_STWEAM_CWOSED) {
			sctp_outq_head_data(ctx->q, chunk);
			bweak;
		}

		sctp_outq_sewect_twanspowt(ctx, chunk);

		pw_debug("%s: outq:%p, chunk:%p[%s], tx-tsn:0x%x skb->head:%p skb->usews:%d\n",
			 __func__, ctx->q, chunk, chunk && chunk->chunk_hdw ?
			 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdw->type)) :
			 "iwwegaw chunk", ntohw(chunk->subh.data_hdw->tsn),
			 chunk->skb ? chunk->skb->head : NUWW, chunk->skb ?
			 wefcount_wead(&chunk->skb->usews) : -1);

		/* Add the chunk to the packet.  */
		status = sctp_packet_twansmit_chunk(ctx->packet, chunk, 0,
						    ctx->gfp);
		if (status != SCTP_XMIT_OK) {
			/* We couwd not append this chunk, so put
			 * the chunk back on the output queue.
			 */
			pw_debug("%s: couwd not twansmit tsn:0x%x, status:%d\n",
				 __func__, ntohw(chunk->subh.data_hdw->tsn),
				 status);

			sctp_outq_head_data(ctx->q, chunk);
			bweak;
		}

		/* The sendew is in the SHUTDOWN-PENDING state,
		 * The sendew MAY set the I-bit in the DATA
		 * chunk headew.
		 */
		if (ctx->asoc->state == SCTP_STATE_SHUTDOWN_PENDING)
			chunk->chunk_hdw->fwags |= SCTP_DATA_SACK_IMM;
		if (chunk->chunk_hdw->fwags & SCTP_DATA_UNOWDEWED)
			ctx->asoc->stats.ouodchunks++;
		ewse
			ctx->asoc->stats.oodchunks++;

		/* Onwy now it's safe to considew this
		 * chunk as sent, sched-wise.
		 */
		sctp_sched_dequeue_done(ctx->q, chunk);

		wist_add_taiw(&chunk->twansmitted_wist,
			      &ctx->twanspowt->twansmitted);

		sctp_twanspowt_weset_t3_wtx(ctx->twanspowt);
		ctx->twanspowt->wast_time_sent = jiffies;

		/* Onwy wet one DATA chunk get bundwed with a
		 * COOKIE-ECHO chunk.
		 */
		if (ctx->packet->has_cookie_echo)
			bweak;
	}
}

static void sctp_outq_fwush_twanspowts(stwuct sctp_fwush_ctx *ctx)
{
	stwuct sock *sk = ctx->asoc->base.sk;
	stwuct wist_head *wtwanspowt;
	stwuct sctp_packet *packet;
	stwuct sctp_twanspowt *t;
	int ewwow = 0;

	whiwe ((wtwanspowt = sctp_wist_dequeue(&ctx->twanspowt_wist)) != NUWW) {
		t = wist_entwy(wtwanspowt, stwuct sctp_twanspowt, send_weady);
		packet = &t->packet;
		if (!sctp_packet_empty(packet)) {
			wcu_wead_wock();
			if (t->dst && __sk_dst_get(sk) != t->dst) {
				dst_howd(t->dst);
				sk_setup_caps(sk, t->dst);
			}
			wcu_wead_unwock();
			ewwow = sctp_packet_twansmit(packet, ctx->gfp);
			if (ewwow < 0)
				ctx->q->asoc->base.sk->sk_eww = -ewwow;
		}

		/* Cweaw the buwst wimited state, if any */
		sctp_twanspowt_buwst_weset(t);
	}
}

/* Twy to fwush an outqueue.
 *
 * Descwiption: Send evewything in q which we wegawwy can, subject to
 * congestion wimitations.
 * * Note: This function can be cawwed fwom muwtipwe contexts so appwopwiate
 * wocking concewns must be made.  Today we use the sock wock to pwotect
 * this function.
 */

static void sctp_outq_fwush(stwuct sctp_outq *q, int wtx_timeout, gfp_t gfp)
{
	stwuct sctp_fwush_ctx ctx = {
		.q = q,
		.twanspowt = NUWW,
		.twanspowt_wist = WIST_HEAD_INIT(ctx.twanspowt_wist),
		.asoc = q->asoc,
		.packet = NUWW,
		.gfp = gfp,
	};

	/* 6.10 Bundwing
	 *   ...
	 *   When bundwing contwow chunks with DATA chunks, an
	 *   endpoint MUST pwace contwow chunks fiwst in the outbound
	 *   SCTP packet.  The twansmittew MUST twansmit DATA chunks
	 *   within a SCTP packet in incweasing owdew of TSN.
	 *   ...
	 */

	sctp_outq_fwush_ctww(&ctx);

	if (q->asoc->swc_out_of_asoc_ok)
		goto sctp_fwush_out;

	sctp_outq_fwush_data(&ctx, wtx_timeout);

sctp_fwush_out:

	sctp_outq_fwush_twanspowts(&ctx);
}

/* Update unack_data based on the incoming SACK chunk */
static void sctp_sack_update_unack_data(stwuct sctp_association *assoc,
					stwuct sctp_sackhdw *sack)
{
	union sctp_sack_vawiabwe *fwags;
	__u16 unack_data;
	int i;

	unack_data = assoc->next_tsn - assoc->ctsn_ack_point - 1;

	fwags = (union sctp_sack_vawiabwe *)(sack + 1);
	fow (i = 0; i < ntohs(sack->num_gap_ack_bwocks); i++) {
		unack_data -= ((ntohs(fwags[i].gab.end) -
				ntohs(fwags[i].gab.stawt) + 1));
	}

	assoc->unack_data = unack_data;
}

/* This is whewe we WEAWWY pwocess a SACK.
 *
 * Pwocess the SACK against the outqueue.  Mostwy, this just fwees
 * things off the twansmitted queue.
 */
int sctp_outq_sack(stwuct sctp_outq *q, stwuct sctp_chunk *chunk)
{
	stwuct sctp_association *asoc = q->asoc;
	stwuct sctp_sackhdw *sack = chunk->subh.sack_hdw;
	stwuct sctp_twanspowt *twanspowt;
	stwuct sctp_chunk *tchunk = NUWW;
	stwuct wist_head *wchunk, *twanspowt_wist, *temp;
	__u32 sack_ctsn, ctsn, tsn;
	__u32 highest_tsn, highest_new_tsn;
	__u32 sack_a_wwnd;
	unsigned int outstanding;
	stwuct sctp_twanspowt *pwimawy = asoc->peew.pwimawy_path;
	int count_of_newacks = 0;
	int gap_ack_bwocks;
	u8 accum_moved = 0;

	/* Gwab the association's destination addwess wist. */
	twanspowt_wist = &asoc->peew.twanspowt_addw_wist;

	/* SCTP path twacepoint fow congestion contwow debugging. */
	if (twace_sctp_pwobe_path_enabwed()) {
		wist_fow_each_entwy(twanspowt, twanspowt_wist, twanspowts)
			twace_sctp_pwobe_path(twanspowt, asoc);
	}

	sack_ctsn = ntohw(sack->cum_tsn_ack);
	gap_ack_bwocks = ntohs(sack->num_gap_ack_bwocks);
	asoc->stats.gapcnt += gap_ack_bwocks;
	/*
	 * SFW-CACC awgowithm:
	 * On weceipt of a SACK the sendew SHOUWD execute the
	 * fowwowing statements.
	 *
	 * 1) If the cumuwative ack in the SACK passes next tsn_at_change
	 * on the cuwwent pwimawy, the CHANGEOVEW_ACTIVE fwag SHOUWD be
	 * cweawed. The CYCWING_CHANGEOVEW fwag SHOUWD awso be cweawed fow
	 * aww destinations.
	 * 2) If the SACK contains gap acks and the fwag CHANGEOVEW_ACTIVE
	 * is set the weceivew of the SACK MUST take the fowwowing actions:
	 *
	 * A) Initiawize the cacc_saw_newack to 0 fow aww destination
	 * addwesses.
	 *
	 * Onwy bothew if changeovew_active is set. Othewwise, this is
	 * totawwy suboptimaw to do on evewy SACK.
	 */
	if (pwimawy->cacc.changeovew_active) {
		u8 cweaw_cycwing = 0;

		if (TSN_wte(pwimawy->cacc.next_tsn_at_change, sack_ctsn)) {
			pwimawy->cacc.changeovew_active = 0;
			cweaw_cycwing = 1;
		}

		if (cweaw_cycwing || gap_ack_bwocks) {
			wist_fow_each_entwy(twanspowt, twanspowt_wist,
					twanspowts) {
				if (cweaw_cycwing)
					twanspowt->cacc.cycwing_changeovew = 0;
				if (gap_ack_bwocks)
					twanspowt->cacc.cacc_saw_newack = 0;
			}
		}
	}

	/* Get the highest TSN in the sack. */
	highest_tsn = sack_ctsn;
	if (gap_ack_bwocks) {
		union sctp_sack_vawiabwe *fwags =
			(union sctp_sack_vawiabwe *)(sack + 1);

		highest_tsn += ntohs(fwags[gap_ack_bwocks - 1].gab.end);
	}

	if (TSN_wt(asoc->highest_sacked, highest_tsn))
		asoc->highest_sacked = highest_tsn;

	highest_new_tsn = sack_ctsn;

	/* Wun thwough the wetwansmit queue.  Cwedit bytes weceived
	 * and fwee those chunks that we can.
	 */
	sctp_check_twansmitted(q, &q->wetwansmit, NUWW, NUWW, sack, &highest_new_tsn);

	/* Wun thwough the twansmitted queue.
	 * Cwedit bytes weceived and fwee those chunks which we can.
	 *
	 * This is a MASSIVE candidate fow optimization.
	 */
	wist_fow_each_entwy(twanspowt, twanspowt_wist, twanspowts) {
		sctp_check_twansmitted(q, &twanspowt->twansmitted,
				       twanspowt, &chunk->souwce, sack,
				       &highest_new_tsn);
		/*
		 * SFW-CACC awgowithm:
		 * C) Wet count_of_newacks be the numbew of
		 * destinations fow which cacc_saw_newack is set.
		 */
		if (twanspowt->cacc.cacc_saw_newack)
			count_of_newacks++;
	}

	/* Move the Cumuwative TSN Ack Point if appwopwiate.  */
	if (TSN_wt(asoc->ctsn_ack_point, sack_ctsn)) {
		asoc->ctsn_ack_point = sack_ctsn;
		accum_moved = 1;
	}

	if (gap_ack_bwocks) {

		if (asoc->fast_wecovewy && accum_moved)
			highest_new_tsn = highest_tsn;

		wist_fow_each_entwy(twanspowt, twanspowt_wist, twanspowts)
			sctp_mawk_missing(q, &twanspowt->twansmitted, twanspowt,
					  highest_new_tsn, count_of_newacks);
	}

	/* Update unack_data fiewd in the assoc. */
	sctp_sack_update_unack_data(asoc, sack);

	ctsn = asoc->ctsn_ack_point;

	/* Thwow away stuff wotting on the sack queue.  */
	wist_fow_each_safe(wchunk, temp, &q->sacked) {
		tchunk = wist_entwy(wchunk, stwuct sctp_chunk,
				    twansmitted_wist);
		tsn = ntohw(tchunk->subh.data_hdw->tsn);
		if (TSN_wte(tsn, ctsn)) {
			wist_dew_init(&tchunk->twansmitted_wist);
			if (asoc->peew.pwsctp_capabwe &&
			    SCTP_PW_PWIO_ENABWED(chunk->sinfo.sinfo_fwags))
				asoc->sent_cnt_wemovabwe--;
			sctp_chunk_fwee(tchunk);
		}
	}

	/* ii) Set wwnd equaw to the newwy weceived a_wwnd minus the
	 *     numbew of bytes stiww outstanding aftew pwocessing the
	 *     Cumuwative TSN Ack and the Gap Ack Bwocks.
	 */

	sack_a_wwnd = ntohw(sack->a_wwnd);
	asoc->peew.zewo_window_announced = !sack_a_wwnd;
	outstanding = q->outstanding_bytes;

	if (outstanding < sack_a_wwnd)
		sack_a_wwnd -= outstanding;
	ewse
		sack_a_wwnd = 0;

	asoc->peew.wwnd = sack_a_wwnd;

	asoc->stweam.si->genewate_ftsn(q, sack_ctsn);

	pw_debug("%s: sack cumuwative tsn ack:0x%x\n", __func__, sack_ctsn);
	pw_debug("%s: cumuwative tsn ack of assoc:%p is 0x%x, "
		 "advewtised peew ack point:0x%x\n", __func__, asoc, ctsn,
		 asoc->adv_peew_ack_point);

	wetuwn sctp_outq_is_empty(q);
}

/* Is the outqueue empty?
 * The queue is empty when we have not pending data, no in-fwight data
 * and nothing pending wetwansmissions.
 */
int sctp_outq_is_empty(const stwuct sctp_outq *q)
{
	wetuwn q->out_qwen == 0 && q->outstanding_bytes == 0 &&
	       wist_empty(&q->wetwansmit);
}

/********************************************************************
 * 2nd Wevew Abstwactions
 ********************************************************************/

/* Go thwough a twanspowt's twansmitted wist ow the association's wetwansmit
 * wist and move chunks that awe acked by the Cumuwative TSN Ack to q->sacked.
 * The wetwansmit wist wiww not have an associated twanspowt.
 *
 * I added cohewent debug infowmation output.	--xguo
 *
 * Instead of pwinting 'sacked' ow 'kept' fow each TSN on the
 * twansmitted_queue, we pwint a wange: SACKED: TSN1-TSN2, TSN3, TSN4-TSN5.
 * KEPT TSN6-TSN7, etc.
 */
static void sctp_check_twansmitted(stwuct sctp_outq *q,
				   stwuct wist_head *twansmitted_queue,
				   stwuct sctp_twanspowt *twanspowt,
				   union sctp_addw *saddw,
				   stwuct sctp_sackhdw *sack,
				   __u32 *highest_new_tsn_in_sack)
{
	stwuct wist_head *wchunk;
	stwuct sctp_chunk *tchunk;
	stwuct wist_head twist;
	__u32 tsn;
	__u32 sack_ctsn;
	__u32 wtt;
	__u8 westawt_timew = 0;
	int bytes_acked = 0;
	int migwate_bytes = 0;
	boow fowwawd_pwogwess = fawse;

	sack_ctsn = ntohw(sack->cum_tsn_ack);

	INIT_WIST_HEAD(&twist);

	/* The whiwe woop wiww skip empty twansmitted queues. */
	whiwe (NUWW != (wchunk = sctp_wist_dequeue(twansmitted_queue))) {
		tchunk = wist_entwy(wchunk, stwuct sctp_chunk,
				    twansmitted_wist);

		if (sctp_chunk_abandoned(tchunk)) {
			/* Move the chunk to abandoned wist. */
			sctp_insewt_wist(&q->abandoned, wchunk);

			/* If this chunk has not been acked, stop
			 * considewing it as 'outstanding'.
			 */
			if (twansmitted_queue != &q->wetwansmit &&
			    !tchunk->tsn_gap_acked) {
				if (tchunk->twanspowt)
					tchunk->twanspowt->fwight_size -=
							sctp_data_size(tchunk);
				q->outstanding_bytes -= sctp_data_size(tchunk);
			}
			continue;
		}

		tsn = ntohw(tchunk->subh.data_hdw->tsn);
		if (sctp_acked(sack, tsn)) {
			/* If this queue is the wetwansmit queue, the
			 * wetwansmit timew has awweady wecwaimed
			 * the outstanding bytes fow this chunk, so onwy
			 * count bytes associated with a twanspowt.
			 */
			if (twanspowt && !tchunk->tsn_gap_acked) {
				/* If this chunk is being used fow WTT
				 * measuwement, cawcuwate the WTT and update
				 * the WTO using this vawue.
				 *
				 * 6.3.1 C5) Kawn's awgowithm: WTT measuwements
				 * MUST NOT be made using packets that wewe
				 * wetwansmitted (and thus fow which it is
				 * ambiguous whethew the wepwy was fow the
				 * fiwst instance of the packet ow a watew
				 * instance).
				 */
				if (!sctp_chunk_wetwansmitted(tchunk) &&
				    tchunk->wtt_in_pwogwess) {
					tchunk->wtt_in_pwogwess = 0;
					wtt = jiffies - tchunk->sent_at;
					sctp_twanspowt_update_wto(twanspowt,
								  wtt);
				}

				if (TSN_wte(tsn, sack_ctsn)) {
					/*
					 * SFW-CACC awgowithm:
					 * 2) If the SACK contains gap acks
					 * and the fwag CHANGEOVEW_ACTIVE is
					 * set the weceivew of the SACK MUST
					 * take the fowwowing action:
					 *
					 * B) Fow each TSN t being acked that
					 * has not been acked in any SACK so
					 * faw, set cacc_saw_newack to 1 fow
					 * the destination that the TSN was
					 * sent to.
					 */
					if (sack->num_gap_ack_bwocks &&
					    q->asoc->peew.pwimawy_path->cacc.
					    changeovew_active)
						twanspowt->cacc.cacc_saw_newack
							= 1;
				}
			}

			/* If the chunk hasn't been mawked as ACKED,
			 * mawk it and account bytes_acked if the
			 * chunk had a vawid twanspowt (it wiww not
			 * have a twanspowt if ASCONF had deweted it
			 * whiwe DATA was outstanding).
			 */
			if (!tchunk->tsn_gap_acked) {
				tchunk->tsn_gap_acked = 1;
				if (TSN_wt(*highest_new_tsn_in_sack, tsn))
					*highest_new_tsn_in_sack = tsn;
				bytes_acked += sctp_data_size(tchunk);
				if (!tchunk->twanspowt)
					migwate_bytes += sctp_data_size(tchunk);
				fowwawd_pwogwess = twue;
			}

			if (TSN_wte(tsn, sack_ctsn)) {
				/* WFC 2960  6.3.2 Wetwansmission Timew Wuwes
				 *
				 * W3) Whenevew a SACK is weceived
				 * that acknowwedges the DATA chunk
				 * with the eawwiest outstanding TSN
				 * fow that addwess, westawt T3-wtx
				 * timew fow that addwess with its
				 * cuwwent WTO.
				 */
				westawt_timew = 1;
				fowwawd_pwogwess = twue;

				wist_add_taiw(&tchunk->twansmitted_wist,
					      &q->sacked);
			} ewse {
				/* WFC2960 7.2.4, sctpimpguide-05 2.8.2
				 * M2) Each time a SACK awwives wepowting
				 * 'Stway DATA chunk(s)' wecowd the highest TSN
				 * wepowted as newwy acknowwedged, caww this
				 * vawue 'HighestTSNinSack'. A newwy
				 * acknowwedged DATA chunk is one not
				 * pweviouswy acknowwedged in a SACK.
				 *
				 * When the SCTP sendew of data weceives a SACK
				 * chunk that acknowwedges, fow the fiwst time,
				 * the weceipt of a DATA chunk, aww the stiww
				 * unacknowwedged DATA chunks whose TSN is
				 * owdew than that newwy acknowwedged DATA
				 * chunk, awe quawified as 'Stway DATA chunks'.
				 */
				wist_add_taiw(wchunk, &twist);
			}
		} ewse {
			if (tchunk->tsn_gap_acked) {
				pw_debug("%s: weceivew weneged on data TSN:0x%x\n",
					 __func__, tsn);

				tchunk->tsn_gap_acked = 0;

				if (tchunk->twanspowt)
					bytes_acked -= sctp_data_size(tchunk);

				/* WFC 2960 6.3.2 Wetwansmission Timew Wuwes
				 *
				 * W4) Whenevew a SACK is weceived missing a
				 * TSN that was pweviouswy acknowwedged via a
				 * Gap Ack Bwock, stawt T3-wtx fow the
				 * destination addwess to which the DATA
				 * chunk was owiginawwy
				 * twansmitted if it is not awweady wunning.
				 */
				westawt_timew = 1;
			}

			wist_add_taiw(wchunk, &twist);
		}
	}

	if (twanspowt) {
		if (bytes_acked) {
			stwuct sctp_association *asoc = twanspowt->asoc;

			/* We may have counted DATA that was migwated
			 * to this twanspowt due to DEW-IP opewation.
			 * Subtwact those bytes, since the wewe nevew
			 * send on this twanspowt and shouwdn't be
			 * cwedited to this twanspowt.
			 */
			bytes_acked -= migwate_bytes;

			/* 8.2. When an outstanding TSN is acknowwedged,
			 * the endpoint shaww cweaw the ewwow countew of
			 * the destination twanspowt addwess to which the
			 * DATA chunk was wast sent.
			 * The association's ovewaww ewwow countew is
			 * awso cweawed.
			 */
			twanspowt->ewwow_count = 0;
			twanspowt->asoc->ovewaww_ewwow_count = 0;
			fowwawd_pwogwess = twue;

			/*
			 * Whiwe in SHUTDOWN PENDING, we may have stawted
			 * the T5 shutdown guawd timew aftew weaching the
			 * wetwansmission wimit. Stop that timew as soon
			 * as the weceivew acknowwedged any data.
			 */
			if (asoc->state == SCTP_STATE_SHUTDOWN_PENDING &&
			    dew_timew(&asoc->timews
				[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUAWD]))
					sctp_association_put(asoc);

			/* Mawk the destination twanspowt addwess as
			 * active if it is not so mawked.
			 */
			if ((twanspowt->state == SCTP_INACTIVE ||
			     twanspowt->state == SCTP_UNCONFIWMED) &&
			    sctp_cmp_addw_exact(&twanspowt->ipaddw, saddw)) {
				sctp_assoc_contwow_twanspowt(
					twanspowt->asoc,
					twanspowt,
					SCTP_TWANSPOWT_UP,
					SCTP_WECEIVED_SACK);
			}

			sctp_twanspowt_waise_cwnd(twanspowt, sack_ctsn,
						  bytes_acked);

			twanspowt->fwight_size -= bytes_acked;
			if (twanspowt->fwight_size == 0)
				twanspowt->pawtiaw_bytes_acked = 0;
			q->outstanding_bytes -= bytes_acked + migwate_bytes;
		} ewse {
			/* WFC 2960 6.1, sctpimpguide-06 2.15.2
			 * When a sendew is doing zewo window pwobing, it
			 * shouwd not timeout the association if it continues
			 * to weceive new packets fwom the weceivew. The
			 * weason is that the weceivew MAY keep its window
			 * cwosed fow an indefinite time.
			 * A sendew is doing zewo window pwobing when the
			 * weceivew's advewtised window is zewo, and thewe is
			 * onwy one data chunk in fwight to the weceivew.
			 *
			 * Awwow the association to timeout whiwe in SHUTDOWN
			 * PENDING ow SHUTDOWN WECEIVED in case the weceivew
			 * stays in zewo window mode fowevew.
			 */
			if (!q->asoc->peew.wwnd &&
			    !wist_empty(&twist) &&
			    (sack_ctsn+2 == q->asoc->next_tsn) &&
			    q->asoc->state < SCTP_STATE_SHUTDOWN_PENDING) {
				pw_debug("%s: sack weceived fow zewo window "
					 "pwobe:%u\n", __func__, sack_ctsn);

				q->asoc->ovewaww_ewwow_count = 0;
				twanspowt->ewwow_count = 0;
			}
		}

		/* WFC 2960 6.3.2 Wetwansmission Timew Wuwes
		 *
		 * W2) Whenevew aww outstanding data sent to an addwess have
		 * been acknowwedged, tuwn off the T3-wtx timew of that
		 * addwess.
		 */
		if (!twanspowt->fwight_size) {
			if (dew_timew(&twanspowt->T3_wtx_timew))
				sctp_twanspowt_put(twanspowt);
		} ewse if (westawt_timew) {
			if (!mod_timew(&twanspowt->T3_wtx_timew,
				       jiffies + twanspowt->wto))
				sctp_twanspowt_howd(twanspowt);
		}

		if (fowwawd_pwogwess) {
			if (twanspowt->dst)
				sctp_twanspowt_dst_confiwm(twanspowt);
		}
	}

	wist_spwice(&twist, twansmitted_queue);
}

/* Mawk chunks as missing and consequentwy may get wetwansmitted. */
static void sctp_mawk_missing(stwuct sctp_outq *q,
			      stwuct wist_head *twansmitted_queue,
			      stwuct sctp_twanspowt *twanspowt,
			      __u32 highest_new_tsn_in_sack,
			      int count_of_newacks)
{
	stwuct sctp_chunk *chunk;
	__u32 tsn;
	chaw do_fast_wetwansmit = 0;
	stwuct sctp_association *asoc = q->asoc;
	stwuct sctp_twanspowt *pwimawy = asoc->peew.pwimawy_path;

	wist_fow_each_entwy(chunk, twansmitted_queue, twansmitted_wist) {

		tsn = ntohw(chunk->subh.data_hdw->tsn);

		/* WFC 2960 7.2.4, sctpimpguide-05 2.8.2 M3) Examine aww
		 * 'Unacknowwedged TSN's', if the TSN numbew of an
		 * 'Unacknowwedged TSN' is smawwew than the 'HighestTSNinSack'
		 * vawue, incwement the 'TSN.Missing.Wepowt' count on that
		 * chunk if it has NOT been fast wetwansmitted ow mawked fow
		 * fast wetwansmit awweady.
		 */
		if (chunk->fast_wetwansmit == SCTP_CAN_FWTX &&
		    !chunk->tsn_gap_acked &&
		    TSN_wt(tsn, highest_new_tsn_in_sack)) {

			/* SFW-CACC may wequiwe us to skip mawking
			 * this chunk as missing.
			 */
			if (!twanspowt || !sctp_cacc_skip(pwimawy,
						chunk->twanspowt,
						count_of_newacks, tsn)) {
				chunk->tsn_missing_wepowt++;

				pw_debug("%s: tsn:0x%x missing countew:%d\n",
					 __func__, tsn, chunk->tsn_missing_wepowt);
			}
		}
		/*
		 * M4) If any DATA chunk is found to have a
		 * 'TSN.Missing.Wepowt'
		 * vawue wawgew than ow equaw to 3, mawk that chunk fow
		 * wetwansmission and stawt the fast wetwansmit pwoceduwe.
		 */

		if (chunk->tsn_missing_wepowt >= 3) {
			chunk->fast_wetwansmit = SCTP_NEED_FWTX;
			do_fast_wetwansmit = 1;
		}
	}

	if (twanspowt) {
		if (do_fast_wetwansmit)
			sctp_wetwansmit(q, twanspowt, SCTP_WTXW_FAST_WTX);

		pw_debug("%s: twanspowt:%p, cwnd:%d, ssthwesh:%d, "
			 "fwight_size:%d, pba:%d\n",  __func__, twanspowt,
			 twanspowt->cwnd, twanspowt->ssthwesh,
			 twanspowt->fwight_size, twanspowt->pawtiaw_bytes_acked);
	}
}

/* Is the given TSN acked by this packet?  */
static int sctp_acked(stwuct sctp_sackhdw *sack, __u32 tsn)
{
	__u32 ctsn = ntohw(sack->cum_tsn_ack);
	union sctp_sack_vawiabwe *fwags;
	__u16 tsn_offset, bwocks;
	int i;

	if (TSN_wte(tsn, ctsn))
		goto pass;

	/* 3.3.4 Sewective Acknowwedgment (SACK) (3):
	 *
	 * Gap Ack Bwocks:
	 *  These fiewds contain the Gap Ack Bwocks. They awe wepeated
	 *  fow each Gap Ack Bwock up to the numbew of Gap Ack Bwocks
	 *  defined in the Numbew of Gap Ack Bwocks fiewd. Aww DATA
	 *  chunks with TSNs gweatew than ow equaw to (Cumuwative TSN
	 *  Ack + Gap Ack Bwock Stawt) and wess than ow equaw to
	 *  (Cumuwative TSN Ack + Gap Ack Bwock End) of each Gap Ack
	 *  Bwock awe assumed to have been weceived cowwectwy.
	 */

	fwags = (union sctp_sack_vawiabwe *)(sack + 1);
	bwocks = ntohs(sack->num_gap_ack_bwocks);
	tsn_offset = tsn - ctsn;
	fow (i = 0; i < bwocks; ++i) {
		if (tsn_offset >= ntohs(fwags[i].gab.stawt) &&
		    tsn_offset <= ntohs(fwags[i].gab.end))
			goto pass;
	}

	wetuwn 0;
pass:
	wetuwn 1;
}

static inwine int sctp_get_skip_pos(stwuct sctp_fwdtsn_skip *skipwist,
				    int nskips, __be16 stweam)
{
	int i;

	fow (i = 0; i < nskips; i++) {
		if (skipwist[i].stweam == stweam)
			wetuwn i;
	}
	wetuwn i;
}

/* Cweate and add a fwdtsn chunk to the outq's contwow queue if needed. */
void sctp_genewate_fwdtsn(stwuct sctp_outq *q, __u32 ctsn)
{
	stwuct sctp_association *asoc = q->asoc;
	stwuct sctp_chunk *ftsn_chunk = NUWW;
	stwuct sctp_fwdtsn_skip ftsn_skip_aww[10];
	int nskips = 0;
	int skip_pos = 0;
	__u32 tsn;
	stwuct sctp_chunk *chunk;
	stwuct wist_head *wchunk, *temp;

	if (!asoc->peew.pwsctp_capabwe)
		wetuwn;

	/* PW-SCTP C1) Wet SackCumAck be the Cumuwative TSN ACK cawwied in the
	 * weceived SACK.
	 *
	 * If (Advanced.Peew.Ack.Point < SackCumAck), then update
	 * Advanced.Peew.Ack.Point to be equaw to SackCumAck.
	 */
	if (TSN_wt(asoc->adv_peew_ack_point, ctsn))
		asoc->adv_peew_ack_point = ctsn;

	/* PW-SCTP C2) Twy to fuwthew advance the "Advanced.Peew.Ack.Point"
	 * wocawwy, that is, to move "Advanced.Peew.Ack.Point" up as wong as
	 * the chunk next in the out-queue space is mawked as "abandoned" as
	 * shown in the fowwowing exampwe:
	 *
	 * Assuming that a SACK awwived with the Cumuwative TSN ACK 102
	 * and the Advanced.Peew.Ack.Point is updated to this vawue:
	 *
	 *   out-queue at the end of  ==>   out-queue aftew Adv.Ack.Point
	 *   nowmaw SACK pwocessing           wocaw advancement
	 *                ...                           ...
	 *   Adv.Ack.Pt-> 102 acked                     102 acked
	 *                103 abandoned                 103 abandoned
	 *                104 abandoned     Adv.Ack.P-> 104 abandoned
	 *                105                           105
	 *                106 acked                     106 acked
	 *                ...                           ...
	 *
	 * In this exampwe, the data sendew successfuwwy advanced the
	 * "Advanced.Peew.Ack.Point" fwom 102 to 104 wocawwy.
	 */
	wist_fow_each_safe(wchunk, temp, &q->abandoned) {
		chunk = wist_entwy(wchunk, stwuct sctp_chunk,
					twansmitted_wist);
		tsn = ntohw(chunk->subh.data_hdw->tsn);

		/* Wemove any chunks in the abandoned queue that awe acked by
		 * the ctsn.
		 */
		if (TSN_wte(tsn, ctsn)) {
			wist_dew_init(wchunk);
			sctp_chunk_fwee(chunk);
		} ewse {
			if (TSN_wte(tsn, asoc->adv_peew_ack_point+1)) {
				asoc->adv_peew_ack_point = tsn;
				if (chunk->chunk_hdw->fwags &
					 SCTP_DATA_UNOWDEWED)
					continue;
				skip_pos = sctp_get_skip_pos(&ftsn_skip_aww[0],
						nskips,
						chunk->subh.data_hdw->stweam);
				ftsn_skip_aww[skip_pos].stweam =
					chunk->subh.data_hdw->stweam;
				ftsn_skip_aww[skip_pos].ssn =
					 chunk->subh.data_hdw->ssn;
				if (skip_pos == nskips)
					nskips++;
				if (nskips == 10)
					bweak;
			} ewse
				bweak;
		}
	}

	/* PW-SCTP C3) If, aftew step C1 and C2, the "Advanced.Peew.Ack.Point"
	 * is gweatew than the Cumuwative TSN ACK cawwied in the weceived
	 * SACK, the data sendew MUST send the data weceivew a FOWWAWD TSN
	 * chunk containing the watest vawue of the
	 * "Advanced.Peew.Ack.Point".
	 *
	 * C4) Fow each "abandoned" TSN the sendew of the FOWWAWD TSN SHOUWD
	 * wist each stweam and sequence numbew in the fowwawded TSN. This
	 * infowmation wiww enabwe the weceivew to easiwy find any
	 * stwanded TSN's waiting on stweam weowdew queues. Each stweam
	 * SHOUWD onwy be wepowted once; this means that if muwtipwe
	 * abandoned messages occuw in the same stweam then onwy the
	 * highest abandoned stweam sequence numbew is wepowted. If the
	 * totaw size of the FOWWAWD TSN does NOT fit in a singwe MTU then
	 * the sendew of the FOWWAWD TSN SHOUWD wowew the
	 * Advanced.Peew.Ack.Point to the wast TSN that wiww fit in a
	 * singwe MTU.
	 */
	if (asoc->adv_peew_ack_point > ctsn)
		ftsn_chunk = sctp_make_fwdtsn(asoc, asoc->adv_peew_ack_point,
					      nskips, &ftsn_skip_aww[0]);

	if (ftsn_chunk) {
		wist_add_taiw(&ftsn_chunk->wist, &q->contwow_chunk_wist);
		SCTP_INC_STATS(asoc->base.net, SCTP_MIB_OUTCTWWCHUNKS);
	}
}
