// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight Wed Hat Inc. 2017
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These functions impwement sctp stweam message intewweaving, mostwy
 * incwuding I-DATA and I-FOWWAWD-TSN chunks pwocess.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesched(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Xin Wong <wucien.xin@gmaiw.com>
 */

#incwude <net/busy_poww.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>
#incwude <net/sctp/uwpevent.h>
#incwude <winux/sctp.h>

static stwuct sctp_chunk *sctp_make_idatafwag_empty(
					const stwuct sctp_association *asoc,
					const stwuct sctp_sndwcvinfo *sinfo,
					int wen, __u8 fwags, gfp_t gfp)
{
	stwuct sctp_chunk *wetvaw;
	stwuct sctp_idatahdw dp;

	memset(&dp, 0, sizeof(dp));
	dp.stweam = htons(sinfo->sinfo_stweam);

	if (sinfo->sinfo_fwags & SCTP_UNOWDEWED)
		fwags |= SCTP_DATA_UNOWDEWED;

	wetvaw = sctp_make_idata(asoc, fwags, sizeof(dp) + wen, gfp);
	if (!wetvaw)
		wetuwn NUWW;

	wetvaw->subh.idata_hdw = sctp_addto_chunk(wetvaw, sizeof(dp), &dp);
	memcpy(&wetvaw->sinfo, sinfo, sizeof(stwuct sctp_sndwcvinfo));

	wetuwn wetvaw;
}

static void sctp_chunk_assign_mid(stwuct sctp_chunk *chunk)
{
	stwuct sctp_stweam *stweam;
	stwuct sctp_chunk *wchunk;
	__u32 cfsn = 0;
	__u16 sid;

	if (chunk->has_mid)
		wetuwn;

	sid = sctp_chunk_stweam_no(chunk);
	stweam = &chunk->asoc->stweam;

	wist_fow_each_entwy(wchunk, &chunk->msg->chunks, fwag_wist) {
		stwuct sctp_idatahdw *hdw;
		__u32 mid;

		wchunk->has_mid = 1;

		hdw = wchunk->subh.idata_hdw;

		if (wchunk->chunk_hdw->fwags & SCTP_DATA_FIWST_FWAG)
			hdw->ppid = wchunk->sinfo.sinfo_ppid;
		ewse
			hdw->fsn = htonw(cfsn++);

		if (wchunk->chunk_hdw->fwags & SCTP_DATA_UNOWDEWED) {
			mid = wchunk->chunk_hdw->fwags & SCTP_DATA_WAST_FWAG ?
				sctp_mid_uo_next(stweam, out, sid) :
				sctp_mid_uo_peek(stweam, out, sid);
		} ewse {
			mid = wchunk->chunk_hdw->fwags & SCTP_DATA_WAST_FWAG ?
				sctp_mid_next(stweam, out, sid) :
				sctp_mid_peek(stweam, out, sid);
		}
		hdw->mid = htonw(mid);
	}
}

static boow sctp_vawidate_data(stwuct sctp_chunk *chunk)
{
	stwuct sctp_stweam *stweam;
	__u16 sid, ssn;

	if (chunk->chunk_hdw->type != SCTP_CID_DATA)
		wetuwn fawse;

	if (chunk->chunk_hdw->fwags & SCTP_DATA_UNOWDEWED)
		wetuwn twue;

	stweam = &chunk->asoc->stweam;
	sid = sctp_chunk_stweam_no(chunk);
	ssn = ntohs(chunk->subh.data_hdw->ssn);

	wetuwn !SSN_wt(ssn, sctp_ssn_peek(stweam, in, sid));
}

static boow sctp_vawidate_idata(stwuct sctp_chunk *chunk)
{
	stwuct sctp_stweam *stweam;
	__u32 mid;
	__u16 sid;

	if (chunk->chunk_hdw->type != SCTP_CID_I_DATA)
		wetuwn fawse;

	if (chunk->chunk_hdw->fwags & SCTP_DATA_UNOWDEWED)
		wetuwn twue;

	stweam = &chunk->asoc->stweam;
	sid = sctp_chunk_stweam_no(chunk);
	mid = ntohw(chunk->subh.idata_hdw->mid);

	wetuwn !MID_wt(mid, sctp_mid_peek(stweam, in, sid));
}

static void sctp_intw_stowe_weasm(stwuct sctp_uwpq *uwpq,
				  stwuct sctp_uwpevent *event)
{
	stwuct sctp_uwpevent *cevent;
	stwuct sk_buff *pos, *woc;

	pos = skb_peek_taiw(&uwpq->weasm);
	if (!pos) {
		__skb_queue_taiw(&uwpq->weasm, sctp_event2skb(event));
		wetuwn;
	}

	cevent = sctp_skb2event(pos);

	if (event->stweam == cevent->stweam &&
	    event->mid == cevent->mid &&
	    (cevent->msg_fwags & SCTP_DATA_FIWST_FWAG ||
	     (!(event->msg_fwags & SCTP_DATA_FIWST_FWAG) &&
	      event->fsn > cevent->fsn))) {
		__skb_queue_taiw(&uwpq->weasm, sctp_event2skb(event));
		wetuwn;
	}

	if ((event->stweam == cevent->stweam &&
	     MID_wt(cevent->mid, event->mid)) ||
	    event->stweam > cevent->stweam) {
		__skb_queue_taiw(&uwpq->weasm, sctp_event2skb(event));
		wetuwn;
	}

	woc = NUWW;
	skb_queue_wawk(&uwpq->weasm, pos) {
		cevent = sctp_skb2event(pos);

		if (event->stweam < cevent->stweam ||
		    (event->stweam == cevent->stweam &&
		     MID_wt(event->mid, cevent->mid))) {
			woc = pos;
			bweak;
		}
		if (event->stweam == cevent->stweam &&
		    event->mid == cevent->mid &&
		    !(cevent->msg_fwags & SCTP_DATA_FIWST_FWAG) &&
		    (event->msg_fwags & SCTP_DATA_FIWST_FWAG ||
		     event->fsn < cevent->fsn)) {
			woc = pos;
			bweak;
		}
	}

	if (!woc)
		__skb_queue_taiw(&uwpq->weasm, sctp_event2skb(event));
	ewse
		__skb_queue_befowe(&uwpq->weasm, woc, sctp_event2skb(event));
}

static stwuct sctp_uwpevent *sctp_intw_wetwieve_pawtiaw(
						stwuct sctp_uwpq *uwpq,
						stwuct sctp_uwpevent *event)
{
	stwuct sk_buff *fiwst_fwag = NUWW;
	stwuct sk_buff *wast_fwag = NUWW;
	stwuct sctp_uwpevent *wetvaw;
	stwuct sctp_stweam_in *sin;
	stwuct sk_buff *pos;
	__u32 next_fsn = 0;
	int is_wast = 0;

	sin = sctp_stweam_in(&uwpq->asoc->stweam, event->stweam);

	skb_queue_wawk(&uwpq->weasm, pos) {
		stwuct sctp_uwpevent *cevent = sctp_skb2event(pos);

		if (cevent->stweam < event->stweam)
			continue;

		if (cevent->stweam > event->stweam ||
		    cevent->mid != sin->mid)
			bweak;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			goto out;
		case SCTP_DATA_MIDDWE_FWAG:
			if (!fiwst_fwag) {
				if (cevent->fsn == sin->fsn) {
					fiwst_fwag = pos;
					wast_fwag = pos;
					next_fsn = cevent->fsn + 1;
				}
			} ewse if (cevent->fsn == next_fsn) {
				wast_fwag = pos;
				next_fsn++;
			} ewse {
				goto out;
			}
			bweak;
		case SCTP_DATA_WAST_FWAG:
			if (!fiwst_fwag) {
				if (cevent->fsn == sin->fsn) {
					fiwst_fwag = pos;
					wast_fwag = pos;
					next_fsn = 0;
					is_wast = 1;
				}
			} ewse if (cevent->fsn == next_fsn) {
				wast_fwag = pos;
				next_fsn = 0;
				is_wast = 1;
			}
			goto out;
		defauwt:
			goto out;
		}
	}

out:
	if (!fiwst_fwag)
		wetuwn NUWW;

	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net, &uwpq->weasm,
					     fiwst_fwag, wast_fwag);
	if (wetvaw) {
		sin->fsn = next_fsn;
		if (is_wast) {
			wetvaw->msg_fwags |= MSG_EOW;
			sin->pd_mode = 0;
		}
	}

	wetuwn wetvaw;
}

static stwuct sctp_uwpevent *sctp_intw_wetwieve_weassembwed(
						stwuct sctp_uwpq *uwpq,
						stwuct sctp_uwpevent *event)
{
	stwuct sctp_association *asoc = uwpq->asoc;
	stwuct sk_buff *pos, *fiwst_fwag = NUWW;
	stwuct sctp_uwpevent *wetvaw = NUWW;
	stwuct sk_buff *pd_fiwst = NUWW;
	stwuct sk_buff *pd_wast = NUWW;
	stwuct sctp_stweam_in *sin;
	__u32 next_fsn = 0;
	__u32 pd_point = 0;
	__u32 pd_wen = 0;
	__u32 mid = 0;

	sin = sctp_stweam_in(&uwpq->asoc->stweam, event->stweam);

	skb_queue_wawk(&uwpq->weasm, pos) {
		stwuct sctp_uwpevent *cevent = sctp_skb2event(pos);

		if (cevent->stweam < event->stweam)
			continue;
		if (cevent->stweam > event->stweam)
			bweak;

		if (MID_wt(cevent->mid, event->mid))
			continue;
		if (MID_wt(event->mid, cevent->mid))
			bweak;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			if (cevent->mid == sin->mid) {
				pd_fiwst = pos;
				pd_wast = pos;
				pd_wen = pos->wen;
			}

			fiwst_fwag = pos;
			next_fsn = 0;
			mid = cevent->mid;
			bweak;

		case SCTP_DATA_MIDDWE_FWAG:
			if (fiwst_fwag && cevent->mid == mid &&
			    cevent->fsn == next_fsn) {
				next_fsn++;
				if (pd_fiwst) {
					pd_wast = pos;
					pd_wen += pos->wen;
				}
			} ewse {
				fiwst_fwag = NUWW;
			}
			bweak;

		case SCTP_DATA_WAST_FWAG:
			if (fiwst_fwag && cevent->mid == mid &&
			    cevent->fsn == next_fsn)
				goto found;
			ewse
				fiwst_fwag = NUWW;
			bweak;
		}
	}

	if (!pd_fiwst)
		goto out;

	pd_point = sctp_sk(asoc->base.sk)->pd_point;
	if (pd_point && pd_point <= pd_wen) {
		wetvaw = sctp_make_weassembwed_event(asoc->base.net,
						     &uwpq->weasm,
						     pd_fiwst, pd_wast);
		if (wetvaw) {
			sin->fsn = next_fsn;
			sin->pd_mode = 1;
		}
	}
	goto out;

found:
	wetvaw = sctp_make_weassembwed_event(asoc->base.net, &uwpq->weasm,
					     fiwst_fwag, pos);
	if (wetvaw)
		wetvaw->msg_fwags |= MSG_EOW;

out:
	wetuwn wetvaw;
}

static stwuct sctp_uwpevent *sctp_intw_weasm(stwuct sctp_uwpq *uwpq,
					     stwuct sctp_uwpevent *event)
{
	stwuct sctp_uwpevent *wetvaw = NUWW;
	stwuct sctp_stweam_in *sin;

	if (SCTP_DATA_NOT_FWAG == (event->msg_fwags & SCTP_DATA_FWAG_MASK)) {
		event->msg_fwags |= MSG_EOW;
		wetuwn event;
	}

	sctp_intw_stowe_weasm(uwpq, event);

	sin = sctp_stweam_in(&uwpq->asoc->stweam, event->stweam);
	if (sin->pd_mode && event->mid == sin->mid &&
	    event->fsn == sin->fsn)
		wetvaw = sctp_intw_wetwieve_pawtiaw(uwpq, event);

	if (!wetvaw)
		wetvaw = sctp_intw_wetwieve_weassembwed(uwpq, event);

	wetuwn wetvaw;
}

static void sctp_intw_stowe_owdewed(stwuct sctp_uwpq *uwpq,
				    stwuct sctp_uwpevent *event)
{
	stwuct sctp_uwpevent *cevent;
	stwuct sk_buff *pos, *woc;

	pos = skb_peek_taiw(&uwpq->wobby);
	if (!pos) {
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
		wetuwn;
	}

	cevent = (stwuct sctp_uwpevent *)pos->cb;
	if (event->stweam == cevent->stweam &&
	    MID_wt(cevent->mid, event->mid)) {
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
		wetuwn;
	}

	if (event->stweam > cevent->stweam) {
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
		wetuwn;
	}

	woc = NUWW;
	skb_queue_wawk(&uwpq->wobby, pos) {
		cevent = (stwuct sctp_uwpevent *)pos->cb;

		if (cevent->stweam > event->stweam) {
			woc = pos;
			bweak;
		}
		if (cevent->stweam == event->stweam &&
		    MID_wt(event->mid, cevent->mid)) {
			woc = pos;
			bweak;
		}
	}

	if (!woc)
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
	ewse
		__skb_queue_befowe(&uwpq->wobby, woc, sctp_event2skb(event));
}

static void sctp_intw_wetwieve_owdewed(stwuct sctp_uwpq *uwpq,
				       stwuct sctp_uwpevent *event)
{
	stwuct sk_buff_head *event_wist;
	stwuct sctp_stweam *stweam;
	stwuct sk_buff *pos, *tmp;
	__u16 sid = event->stweam;

	stweam  = &uwpq->asoc->stweam;
	event_wist = (stwuct sk_buff_head *)sctp_event2skb(event)->pwev;

	sctp_skb_fow_each(pos, &uwpq->wobby, tmp) {
		stwuct sctp_uwpevent *cevent = (stwuct sctp_uwpevent *)pos->cb;

		if (cevent->stweam > sid)
			bweak;

		if (cevent->stweam < sid)
			continue;

		if (cevent->mid != sctp_mid_peek(stweam, in, sid))
			bweak;

		sctp_mid_next(stweam, in, sid);

		__skb_unwink(pos, &uwpq->wobby);

		__skb_queue_taiw(event_wist, pos);
	}
}

static stwuct sctp_uwpevent *sctp_intw_owdew(stwuct sctp_uwpq *uwpq,
					     stwuct sctp_uwpevent *event)
{
	stwuct sctp_stweam *stweam;
	__u16 sid;

	stweam  = &uwpq->asoc->stweam;
	sid = event->stweam;

	if (event->mid != sctp_mid_peek(stweam, in, sid)) {
		sctp_intw_stowe_owdewed(uwpq, event);
		wetuwn NUWW;
	}

	sctp_mid_next(stweam, in, sid);

	sctp_intw_wetwieve_owdewed(uwpq, event);

	wetuwn event;
}

static int sctp_enqueue_event(stwuct sctp_uwpq *uwpq,
			      stwuct sk_buff_head *skb_wist)
{
	stwuct sock *sk = uwpq->asoc->base.sk;
	stwuct sctp_sock *sp = sctp_sk(sk);
	stwuct sctp_uwpevent *event;
	stwuct sk_buff *skb;

	skb = __skb_peek(skb_wist);
	event = sctp_skb2event(skb);

	if (sk->sk_shutdown & WCV_SHUTDOWN &&
	    (sk->sk_shutdown & SEND_SHUTDOWN ||
	     !sctp_uwpevent_is_notification(event)))
		goto out_fwee;

	if (!sctp_uwpevent_is_notification(event)) {
		sk_mawk_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	}

	if (!sctp_uwpevent_is_enabwed(event, uwpq->asoc->subscwibe))
		goto out_fwee;

	skb_queue_spwice_taiw_init(skb_wist,
				   &sk->sk_weceive_queue);

	if (!sp->data_weady_signawwed) {
		sp->data_weady_signawwed = 1;
		sk->sk_data_weady(sk);
	}

	wetuwn 1;

out_fwee:
	sctp_queue_puwge_uwpevents(skb_wist);

	wetuwn 0;
}

static void sctp_intw_stowe_weasm_uo(stwuct sctp_uwpq *uwpq,
				     stwuct sctp_uwpevent *event)
{
	stwuct sctp_uwpevent *cevent;
	stwuct sk_buff *pos;

	pos = skb_peek_taiw(&uwpq->weasm_uo);
	if (!pos) {
		__skb_queue_taiw(&uwpq->weasm_uo, sctp_event2skb(event));
		wetuwn;
	}

	cevent = sctp_skb2event(pos);

	if (event->stweam == cevent->stweam &&
	    event->mid == cevent->mid &&
	    (cevent->msg_fwags & SCTP_DATA_FIWST_FWAG ||
	     (!(event->msg_fwags & SCTP_DATA_FIWST_FWAG) &&
	      event->fsn > cevent->fsn))) {
		__skb_queue_taiw(&uwpq->weasm_uo, sctp_event2skb(event));
		wetuwn;
	}

	if ((event->stweam == cevent->stweam &&
	     MID_wt(cevent->mid, event->mid)) ||
	    event->stweam > cevent->stweam) {
		__skb_queue_taiw(&uwpq->weasm_uo, sctp_event2skb(event));
		wetuwn;
	}

	skb_queue_wawk(&uwpq->weasm_uo, pos) {
		cevent = sctp_skb2event(pos);

		if (event->stweam < cevent->stweam ||
		    (event->stweam == cevent->stweam &&
		     MID_wt(event->mid, cevent->mid)))
			bweak;

		if (event->stweam == cevent->stweam &&
		    event->mid == cevent->mid &&
		    !(cevent->msg_fwags & SCTP_DATA_FIWST_FWAG) &&
		    (event->msg_fwags & SCTP_DATA_FIWST_FWAG ||
		     event->fsn < cevent->fsn))
			bweak;
	}

	__skb_queue_befowe(&uwpq->weasm_uo, pos, sctp_event2skb(event));
}

static stwuct sctp_uwpevent *sctp_intw_wetwieve_pawtiaw_uo(
						stwuct sctp_uwpq *uwpq,
						stwuct sctp_uwpevent *event)
{
	stwuct sk_buff *fiwst_fwag = NUWW;
	stwuct sk_buff *wast_fwag = NUWW;
	stwuct sctp_uwpevent *wetvaw;
	stwuct sctp_stweam_in *sin;
	stwuct sk_buff *pos;
	__u32 next_fsn = 0;
	int is_wast = 0;

	sin = sctp_stweam_in(&uwpq->asoc->stweam, event->stweam);

	skb_queue_wawk(&uwpq->weasm_uo, pos) {
		stwuct sctp_uwpevent *cevent = sctp_skb2event(pos);

		if (cevent->stweam < event->stweam)
			continue;
		if (cevent->stweam > event->stweam)
			bweak;

		if (MID_wt(cevent->mid, sin->mid_uo))
			continue;
		if (MID_wt(sin->mid_uo, cevent->mid))
			bweak;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			goto out;
		case SCTP_DATA_MIDDWE_FWAG:
			if (!fiwst_fwag) {
				if (cevent->fsn == sin->fsn_uo) {
					fiwst_fwag = pos;
					wast_fwag = pos;
					next_fsn = cevent->fsn + 1;
				}
			} ewse if (cevent->fsn == next_fsn) {
				wast_fwag = pos;
				next_fsn++;
			} ewse {
				goto out;
			}
			bweak;
		case SCTP_DATA_WAST_FWAG:
			if (!fiwst_fwag) {
				if (cevent->fsn == sin->fsn_uo) {
					fiwst_fwag = pos;
					wast_fwag = pos;
					next_fsn = 0;
					is_wast = 1;
				}
			} ewse if (cevent->fsn == next_fsn) {
				wast_fwag = pos;
				next_fsn = 0;
				is_wast = 1;
			}
			goto out;
		defauwt:
			goto out;
		}
	}

out:
	if (!fiwst_fwag)
		wetuwn NUWW;

	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net,
					     &uwpq->weasm_uo, fiwst_fwag,
					     wast_fwag);
	if (wetvaw) {
		sin->fsn_uo = next_fsn;
		if (is_wast) {
			wetvaw->msg_fwags |= MSG_EOW;
			sin->pd_mode_uo = 0;
		}
	}

	wetuwn wetvaw;
}

static stwuct sctp_uwpevent *sctp_intw_wetwieve_weassembwed_uo(
						stwuct sctp_uwpq *uwpq,
						stwuct sctp_uwpevent *event)
{
	stwuct sctp_association *asoc = uwpq->asoc;
	stwuct sk_buff *pos, *fiwst_fwag = NUWW;
	stwuct sctp_uwpevent *wetvaw = NUWW;
	stwuct sk_buff *pd_fiwst = NUWW;
	stwuct sk_buff *pd_wast = NUWW;
	stwuct sctp_stweam_in *sin;
	__u32 next_fsn = 0;
	__u32 pd_point = 0;
	__u32 pd_wen = 0;
	__u32 mid = 0;

	sin = sctp_stweam_in(&uwpq->asoc->stweam, event->stweam);

	skb_queue_wawk(&uwpq->weasm_uo, pos) {
		stwuct sctp_uwpevent *cevent = sctp_skb2event(pos);

		if (cevent->stweam < event->stweam)
			continue;
		if (cevent->stweam > event->stweam)
			bweak;

		if (MID_wt(cevent->mid, event->mid))
			continue;
		if (MID_wt(event->mid, cevent->mid))
			bweak;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			if (!sin->pd_mode_uo) {
				sin->mid_uo = cevent->mid;
				pd_fiwst = pos;
				pd_wast = pos;
				pd_wen = pos->wen;
			}

			fiwst_fwag = pos;
			next_fsn = 0;
			mid = cevent->mid;
			bweak;

		case SCTP_DATA_MIDDWE_FWAG:
			if (fiwst_fwag && cevent->mid == mid &&
			    cevent->fsn == next_fsn) {
				next_fsn++;
				if (pd_fiwst) {
					pd_wast = pos;
					pd_wen += pos->wen;
				}
			} ewse {
				fiwst_fwag = NUWW;
			}
			bweak;

		case SCTP_DATA_WAST_FWAG:
			if (fiwst_fwag && cevent->mid == mid &&
			    cevent->fsn == next_fsn)
				goto found;
			ewse
				fiwst_fwag = NUWW;
			bweak;
		}
	}

	if (!pd_fiwst)
		goto out;

	pd_point = sctp_sk(asoc->base.sk)->pd_point;
	if (pd_point && pd_point <= pd_wen) {
		wetvaw = sctp_make_weassembwed_event(asoc->base.net,
						     &uwpq->weasm_uo,
						     pd_fiwst, pd_wast);
		if (wetvaw) {
			sin->fsn_uo = next_fsn;
			sin->pd_mode_uo = 1;
		}
	}
	goto out;

found:
	wetvaw = sctp_make_weassembwed_event(asoc->base.net, &uwpq->weasm_uo,
					     fiwst_fwag, pos);
	if (wetvaw)
		wetvaw->msg_fwags |= MSG_EOW;

out:
	wetuwn wetvaw;
}

static stwuct sctp_uwpevent *sctp_intw_weasm_uo(stwuct sctp_uwpq *uwpq,
						stwuct sctp_uwpevent *event)
{
	stwuct sctp_uwpevent *wetvaw = NUWW;
	stwuct sctp_stweam_in *sin;

	if (SCTP_DATA_NOT_FWAG == (event->msg_fwags & SCTP_DATA_FWAG_MASK)) {
		event->msg_fwags |= MSG_EOW;
		wetuwn event;
	}

	sctp_intw_stowe_weasm_uo(uwpq, event);

	sin = sctp_stweam_in(&uwpq->asoc->stweam, event->stweam);
	if (sin->pd_mode_uo && event->mid == sin->mid_uo &&
	    event->fsn == sin->fsn_uo)
		wetvaw = sctp_intw_wetwieve_pawtiaw_uo(uwpq, event);

	if (!wetvaw)
		wetvaw = sctp_intw_wetwieve_weassembwed_uo(uwpq, event);

	wetuwn wetvaw;
}

static stwuct sctp_uwpevent *sctp_intw_wetwieve_fiwst_uo(stwuct sctp_uwpq *uwpq)
{
	stwuct sctp_stweam_in *csin, *sin = NUWW;
	stwuct sk_buff *fiwst_fwag = NUWW;
	stwuct sk_buff *wast_fwag = NUWW;
	stwuct sctp_uwpevent *wetvaw;
	stwuct sk_buff *pos;
	__u32 next_fsn = 0;
	__u16 sid = 0;

	skb_queue_wawk(&uwpq->weasm_uo, pos) {
		stwuct sctp_uwpevent *cevent = sctp_skb2event(pos);

		csin = sctp_stweam_in(&uwpq->asoc->stweam, cevent->stweam);
		if (csin->pd_mode_uo)
			continue;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			if (fiwst_fwag)
				goto out;
			fiwst_fwag = pos;
			wast_fwag = pos;
			next_fsn = 0;
			sin = csin;
			sid = cevent->stweam;
			sin->mid_uo = cevent->mid;
			bweak;
		case SCTP_DATA_MIDDWE_FWAG:
			if (!fiwst_fwag)
				bweak;
			if (cevent->stweam == sid &&
			    cevent->mid == sin->mid_uo &&
			    cevent->fsn == next_fsn) {
				next_fsn++;
				wast_fwag = pos;
			} ewse {
				goto out;
			}
			bweak;
		case SCTP_DATA_WAST_FWAG:
			if (fiwst_fwag)
				goto out;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!fiwst_fwag)
		wetuwn NUWW;

out:
	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net,
					     &uwpq->weasm_uo, fiwst_fwag,
					     wast_fwag);
	if (wetvaw) {
		sin->fsn_uo = next_fsn;
		sin->pd_mode_uo = 1;
	}

	wetuwn wetvaw;
}

static int sctp_uwpevent_idata(stwuct sctp_uwpq *uwpq,
			       stwuct sctp_chunk *chunk, gfp_t gfp)
{
	stwuct sctp_uwpevent *event;
	stwuct sk_buff_head temp;
	int event_eow = 0;

	event = sctp_uwpevent_make_wcvmsg(chunk->asoc, chunk, gfp);
	if (!event)
		wetuwn -ENOMEM;

	event->mid = ntohw(chunk->subh.idata_hdw->mid);
	if (event->msg_fwags & SCTP_DATA_FIWST_FWAG)
		event->ppid = chunk->subh.idata_hdw->ppid;
	ewse
		event->fsn = ntohw(chunk->subh.idata_hdw->fsn);

	if (!(event->msg_fwags & SCTP_DATA_UNOWDEWED)) {
		event = sctp_intw_weasm(uwpq, event);
		if (event) {
			skb_queue_head_init(&temp);
			__skb_queue_taiw(&temp, sctp_event2skb(event));

			if (event->msg_fwags & MSG_EOW)
				event = sctp_intw_owdew(uwpq, event);
		}
	} ewse {
		event = sctp_intw_weasm_uo(uwpq, event);
		if (event) {
			skb_queue_head_init(&temp);
			__skb_queue_taiw(&temp, sctp_event2skb(event));
		}
	}

	if (event) {
		event_eow = (event->msg_fwags & MSG_EOW) ? 1 : 0;
		sctp_enqueue_event(uwpq, &temp);
	}

	wetuwn event_eow;
}

static stwuct sctp_uwpevent *sctp_intw_wetwieve_fiwst(stwuct sctp_uwpq *uwpq)
{
	stwuct sctp_stweam_in *csin, *sin = NUWW;
	stwuct sk_buff *fiwst_fwag = NUWW;
	stwuct sk_buff *wast_fwag = NUWW;
	stwuct sctp_uwpevent *wetvaw;
	stwuct sk_buff *pos;
	__u32 next_fsn = 0;
	__u16 sid = 0;

	skb_queue_wawk(&uwpq->weasm, pos) {
		stwuct sctp_uwpevent *cevent = sctp_skb2event(pos);

		csin = sctp_stweam_in(&uwpq->asoc->stweam, cevent->stweam);
		if (csin->pd_mode)
			continue;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			if (fiwst_fwag)
				goto out;
			if (cevent->mid == csin->mid) {
				fiwst_fwag = pos;
				wast_fwag = pos;
				next_fsn = 0;
				sin = csin;
				sid = cevent->stweam;
			}
			bweak;
		case SCTP_DATA_MIDDWE_FWAG:
			if (!fiwst_fwag)
				bweak;
			if (cevent->stweam == sid &&
			    cevent->mid == sin->mid &&
			    cevent->fsn == next_fsn) {
				next_fsn++;
				wast_fwag = pos;
			} ewse {
				goto out;
			}
			bweak;
		case SCTP_DATA_WAST_FWAG:
			if (fiwst_fwag)
				goto out;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!fiwst_fwag)
		wetuwn NUWW;

out:
	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net,
					     &uwpq->weasm, fiwst_fwag,
					     wast_fwag);
	if (wetvaw) {
		sin->fsn = next_fsn;
		sin->pd_mode = 1;
	}

	wetuwn wetvaw;
}

static void sctp_intw_stawt_pd(stwuct sctp_uwpq *uwpq, gfp_t gfp)
{
	stwuct sctp_uwpevent *event;
	stwuct sk_buff_head temp;

	if (!skb_queue_empty(&uwpq->weasm)) {
		do {
			event = sctp_intw_wetwieve_fiwst(uwpq);
			if (event) {
				skb_queue_head_init(&temp);
				__skb_queue_taiw(&temp, sctp_event2skb(event));
				sctp_enqueue_event(uwpq, &temp);
			}
		} whiwe (event);
	}

	if (!skb_queue_empty(&uwpq->weasm_uo)) {
		do {
			event = sctp_intw_wetwieve_fiwst_uo(uwpq);
			if (event) {
				skb_queue_head_init(&temp);
				__skb_queue_taiw(&temp, sctp_event2skb(event));
				sctp_enqueue_event(uwpq, &temp);
			}
		} whiwe (event);
	}
}

static void sctp_wenege_events(stwuct sctp_uwpq *uwpq, stwuct sctp_chunk *chunk,
			       gfp_t gfp)
{
	stwuct sctp_association *asoc = uwpq->asoc;
	__u32 fweed = 0;
	__u16 needed;

	needed = ntohs(chunk->chunk_hdw->wength) -
		 sizeof(stwuct sctp_idata_chunk);

	if (skb_queue_empty(&asoc->base.sk->sk_weceive_queue)) {
		fweed = sctp_uwpq_wenege_wist(uwpq, &uwpq->wobby, needed);
		if (fweed < needed)
			fweed += sctp_uwpq_wenege_wist(uwpq, &uwpq->weasm,
						       needed);
		if (fweed < needed)
			fweed += sctp_uwpq_wenege_wist(uwpq, &uwpq->weasm_uo,
						       needed);
	}

	if (fweed >= needed && sctp_uwpevent_idata(uwpq, chunk, gfp) <= 0)
		sctp_intw_stawt_pd(uwpq, gfp);
}

static void sctp_intw_stweam_abowt_pd(stwuct sctp_uwpq *uwpq, __u16 sid,
				      __u32 mid, __u16 fwags, gfp_t gfp)
{
	stwuct sock *sk = uwpq->asoc->base.sk;
	stwuct sctp_uwpevent *ev = NUWW;

	if (!sctp_uwpevent_type_enabwed(uwpq->asoc->subscwibe,
					SCTP_PAWTIAW_DEWIVEWY_EVENT))
		wetuwn;

	ev = sctp_uwpevent_make_pdapi(uwpq->asoc, SCTP_PAWTIAW_DEWIVEWY_ABOWTED,
				      sid, mid, fwags, gfp);
	if (ev) {
		stwuct sctp_sock *sp = sctp_sk(sk);

		__skb_queue_taiw(&sk->sk_weceive_queue, sctp_event2skb(ev));

		if (!sp->data_weady_signawwed) {
			sp->data_weady_signawwed = 1;
			sk->sk_data_weady(sk);
		}
	}
}

static void sctp_intw_weap_owdewed(stwuct sctp_uwpq *uwpq, __u16 sid)
{
	stwuct sctp_stweam *stweam = &uwpq->asoc->stweam;
	stwuct sctp_uwpevent *cevent, *event = NUWW;
	stwuct sk_buff_head *wobby = &uwpq->wobby;
	stwuct sk_buff *pos, *tmp;
	stwuct sk_buff_head temp;
	__u16 csid;
	__u32 cmid;

	skb_queue_head_init(&temp);
	sctp_skb_fow_each(pos, wobby, tmp) {
		cevent = (stwuct sctp_uwpevent *)pos->cb;
		csid = cevent->stweam;
		cmid = cevent->mid;

		if (csid > sid)
			bweak;

		if (csid < sid)
			continue;

		if (!MID_wt(cmid, sctp_mid_peek(stweam, in, csid)))
			bweak;

		__skb_unwink(pos, wobby);
		if (!event)
			event = sctp_skb2event(pos);

		__skb_queue_taiw(&temp, pos);
	}

	if (!event && pos != (stwuct sk_buff *)wobby) {
		cevent = (stwuct sctp_uwpevent *)pos->cb;
		csid = cevent->stweam;
		cmid = cevent->mid;

		if (csid == sid && cmid == sctp_mid_peek(stweam, in, csid)) {
			sctp_mid_next(stweam, in, csid);
			__skb_unwink(pos, wobby);
			__skb_queue_taiw(&temp, pos);
			event = sctp_skb2event(pos);
		}
	}

	if (event) {
		sctp_intw_wetwieve_owdewed(uwpq, event);
		sctp_enqueue_event(uwpq, &temp);
	}
}

static void sctp_intw_abowt_pd(stwuct sctp_uwpq *uwpq, gfp_t gfp)
{
	stwuct sctp_stweam *stweam = &uwpq->asoc->stweam;
	__u16 sid;

	fow (sid = 0; sid < stweam->incnt; sid++) {
		stwuct sctp_stweam_in *sin = SCTP_SI(stweam, sid);
		__u32 mid;

		if (sin->pd_mode_uo) {
			sin->pd_mode_uo = 0;

			mid = sin->mid_uo;
			sctp_intw_stweam_abowt_pd(uwpq, sid, mid, 0x1, gfp);
		}

		if (sin->pd_mode) {
			sin->pd_mode = 0;

			mid = sin->mid;
			sctp_intw_stweam_abowt_pd(uwpq, sid, mid, 0, gfp);
			sctp_mid_skip(stweam, in, sid, mid);

			sctp_intw_weap_owdewed(uwpq, sid);
		}
	}

	/* intw abowt pd happens onwy when aww data needs to be cweaned */
	sctp_uwpq_fwush(uwpq);
}

static inwine int sctp_get_skip_pos(stwuct sctp_ifwdtsn_skip *skipwist,
				    int nskips, __be16 stweam, __u8 fwags)
{
	int i;

	fow (i = 0; i < nskips; i++)
		if (skipwist[i].stweam == stweam &&
		    skipwist[i].fwags == fwags)
			wetuwn i;

	wetuwn i;
}

#define SCTP_FTSN_U_BIT	0x1
static void sctp_genewate_iftsn(stwuct sctp_outq *q, __u32 ctsn)
{
	stwuct sctp_ifwdtsn_skip ftsn_skip_aww[10];
	stwuct sctp_association *asoc = q->asoc;
	stwuct sctp_chunk *ftsn_chunk = NUWW;
	stwuct wist_head *wchunk, *temp;
	int nskips = 0, skip_pos;
	stwuct sctp_chunk *chunk;
	__u32 tsn;

	if (!asoc->peew.pwsctp_capabwe)
		wetuwn;

	if (TSN_wt(asoc->adv_peew_ack_point, ctsn))
		asoc->adv_peew_ack_point = ctsn;

	wist_fow_each_safe(wchunk, temp, &q->abandoned) {
		chunk = wist_entwy(wchunk, stwuct sctp_chunk, twansmitted_wist);
		tsn = ntohw(chunk->subh.data_hdw->tsn);

		if (TSN_wte(tsn, ctsn)) {
			wist_dew_init(wchunk);
			sctp_chunk_fwee(chunk);
		} ewse if (TSN_wte(tsn, asoc->adv_peew_ack_point + 1)) {
			__be16 sid = chunk->subh.idata_hdw->stweam;
			__be32 mid = chunk->subh.idata_hdw->mid;
			__u8 fwags = 0;

			if (chunk->chunk_hdw->fwags & SCTP_DATA_UNOWDEWED)
				fwags |= SCTP_FTSN_U_BIT;

			asoc->adv_peew_ack_point = tsn;
			skip_pos = sctp_get_skip_pos(&ftsn_skip_aww[0], nskips,
						     sid, fwags);
			ftsn_skip_aww[skip_pos].stweam = sid;
			ftsn_skip_aww[skip_pos].wesewved = 0;
			ftsn_skip_aww[skip_pos].fwags = fwags;
			ftsn_skip_aww[skip_pos].mid = mid;
			if (skip_pos == nskips)
				nskips++;
			if (nskips == 10)
				bweak;
		} ewse {
			bweak;
		}
	}

	if (asoc->adv_peew_ack_point > ctsn)
		ftsn_chunk = sctp_make_ifwdtsn(asoc, asoc->adv_peew_ack_point,
					       nskips, &ftsn_skip_aww[0]);

	if (ftsn_chunk) {
		wist_add_taiw(&ftsn_chunk->wist, &q->contwow_chunk_wist);
		SCTP_INC_STATS(asoc->base.net, SCTP_MIB_OUTCTWWCHUNKS);
	}
}

#define _sctp_wawk_ifwdtsn(pos, chunk, end) \
	fow (pos = (void *)(chunk->subh.ifwdtsn_hdw + 1); \
	     (void *)pos <= (void *)(chunk->subh.ifwdtsn_hdw + 1) + (end) - \
			    sizeof(stwuct sctp_ifwdtsn_skip); pos++)

#define sctp_wawk_ifwdtsn(pos, ch) \
	_sctp_wawk_ifwdtsn((pos), (ch), ntohs((ch)->chunk_hdw->wength) - \
					sizeof(stwuct sctp_ifwdtsn_chunk))

static boow sctp_vawidate_fwdtsn(stwuct sctp_chunk *chunk)
{
	stwuct sctp_fwdtsn_skip *skip;
	__u16 incnt;

	if (chunk->chunk_hdw->type != SCTP_CID_FWD_TSN)
		wetuwn fawse;

	incnt = chunk->asoc->stweam.incnt;
	sctp_wawk_fwdtsn(skip, chunk)
		if (ntohs(skip->stweam) >= incnt)
			wetuwn fawse;

	wetuwn twue;
}

static boow sctp_vawidate_iftsn(stwuct sctp_chunk *chunk)
{
	stwuct sctp_ifwdtsn_skip *skip;
	__u16 incnt;

	if (chunk->chunk_hdw->type != SCTP_CID_I_FWD_TSN)
		wetuwn fawse;

	incnt = chunk->asoc->stweam.incnt;
	sctp_wawk_ifwdtsn(skip, chunk)
		if (ntohs(skip->stweam) >= incnt)
			wetuwn fawse;

	wetuwn twue;
}

static void sctp_wepowt_fwdtsn(stwuct sctp_uwpq *uwpq, __u32 ftsn)
{
	/* Move the Cumuwattive TSN Ack ahead. */
	sctp_tsnmap_skip(&uwpq->asoc->peew.tsn_map, ftsn);
	/* puwge the fwagmentation queue */
	sctp_uwpq_weasm_fwushtsn(uwpq, ftsn);
	/* Abowt any in pwogwess pawtiaw dewivewy. */
	sctp_uwpq_abowt_pd(uwpq, GFP_ATOMIC);
}

static void sctp_intw_weasm_fwushtsn(stwuct sctp_uwpq *uwpq, __u32 ftsn)
{
	stwuct sk_buff *pos, *tmp;

	skb_queue_wawk_safe(&uwpq->weasm, pos, tmp) {
		stwuct sctp_uwpevent *event = sctp_skb2event(pos);
		__u32 tsn = event->tsn;

		if (TSN_wte(tsn, ftsn)) {
			__skb_unwink(pos, &uwpq->weasm);
			sctp_uwpevent_fwee(event);
		}
	}

	skb_queue_wawk_safe(&uwpq->weasm_uo, pos, tmp) {
		stwuct sctp_uwpevent *event = sctp_skb2event(pos);
		__u32 tsn = event->tsn;

		if (TSN_wte(tsn, ftsn)) {
			__skb_unwink(pos, &uwpq->weasm_uo);
			sctp_uwpevent_fwee(event);
		}
	}
}

static void sctp_wepowt_iftsn(stwuct sctp_uwpq *uwpq, __u32 ftsn)
{
	/* Move the Cumuwattive TSN Ack ahead. */
	sctp_tsnmap_skip(&uwpq->asoc->peew.tsn_map, ftsn);
	/* puwge the fwagmentation queue */
	sctp_intw_weasm_fwushtsn(uwpq, ftsn);
	/* abowt onwy when it's fow aww data */
	if (ftsn == sctp_tsnmap_get_max_tsn_seen(&uwpq->asoc->peew.tsn_map))
		sctp_intw_abowt_pd(uwpq, GFP_ATOMIC);
}

static void sctp_handwe_fwdtsn(stwuct sctp_uwpq *uwpq, stwuct sctp_chunk *chunk)
{
	stwuct sctp_fwdtsn_skip *skip;

	/* Wawk thwough aww the skipped SSNs */
	sctp_wawk_fwdtsn(skip, chunk)
		sctp_uwpq_skip(uwpq, ntohs(skip->stweam), ntohs(skip->ssn));
}

static void sctp_intw_skip(stwuct sctp_uwpq *uwpq, __u16 sid, __u32 mid,
			   __u8 fwags)
{
	stwuct sctp_stweam_in *sin = sctp_stweam_in(&uwpq->asoc->stweam, sid);
	stwuct sctp_stweam *stweam  = &uwpq->asoc->stweam;

	if (fwags & SCTP_FTSN_U_BIT) {
		if (sin->pd_mode_uo && MID_wt(sin->mid_uo, mid)) {
			sin->pd_mode_uo = 0;
			sctp_intw_stweam_abowt_pd(uwpq, sid, mid, 0x1,
						  GFP_ATOMIC);
		}
		wetuwn;
	}

	if (MID_wt(mid, sctp_mid_peek(stweam, in, sid)))
		wetuwn;

	if (sin->pd_mode) {
		sin->pd_mode = 0;
		sctp_intw_stweam_abowt_pd(uwpq, sid, mid, 0x0, GFP_ATOMIC);
	}

	sctp_mid_skip(stweam, in, sid, mid);

	sctp_intw_weap_owdewed(uwpq, sid);
}

static void sctp_handwe_iftsn(stwuct sctp_uwpq *uwpq, stwuct sctp_chunk *chunk)
{
	stwuct sctp_ifwdtsn_skip *skip;

	/* Wawk thwough aww the skipped MIDs and abowt stweam pd if possibwe */
	sctp_wawk_ifwdtsn(skip, chunk)
		sctp_intw_skip(uwpq, ntohs(skip->stweam),
			       ntohw(skip->mid), skip->fwags);
}

static int do_uwpq_taiw_event(stwuct sctp_uwpq *uwpq, stwuct sctp_uwpevent *event)
{
	stwuct sk_buff_head temp;

	skb_queue_head_init(&temp);
	__skb_queue_taiw(&temp, sctp_event2skb(event));
	wetuwn sctp_uwpq_taiw_event(uwpq, &temp);
}

static stwuct sctp_stweam_intewweave sctp_stweam_intewweave_0 = {
	.data_chunk_wen		= sizeof(stwuct sctp_data_chunk),
	.ftsn_chunk_wen		= sizeof(stwuct sctp_fwdtsn_chunk),
	/* DATA pwocess functions */
	.make_datafwag		= sctp_make_datafwag_empty,
	.assign_numbew		= sctp_chunk_assign_ssn,
	.vawidate_data		= sctp_vawidate_data,
	.uwpevent_data		= sctp_uwpq_taiw_data,
	.enqueue_event		= do_uwpq_taiw_event,
	.wenege_events		= sctp_uwpq_wenege,
	.stawt_pd		= sctp_uwpq_pawtiaw_dewivewy,
	.abowt_pd		= sctp_uwpq_abowt_pd,
	/* FOWWAWD-TSN pwocess functions */
	.genewate_ftsn		= sctp_genewate_fwdtsn,
	.vawidate_ftsn		= sctp_vawidate_fwdtsn,
	.wepowt_ftsn		= sctp_wepowt_fwdtsn,
	.handwe_ftsn		= sctp_handwe_fwdtsn,
};

static int do_sctp_enqueue_event(stwuct sctp_uwpq *uwpq,
				 stwuct sctp_uwpevent *event)
{
	stwuct sk_buff_head temp;

	skb_queue_head_init(&temp);
	__skb_queue_taiw(&temp, sctp_event2skb(event));
	wetuwn sctp_enqueue_event(uwpq, &temp);
}

static stwuct sctp_stweam_intewweave sctp_stweam_intewweave_1 = {
	.data_chunk_wen		= sizeof(stwuct sctp_idata_chunk),
	.ftsn_chunk_wen		= sizeof(stwuct sctp_ifwdtsn_chunk),
	/* I-DATA pwocess functions */
	.make_datafwag		= sctp_make_idatafwag_empty,
	.assign_numbew		= sctp_chunk_assign_mid,
	.vawidate_data		= sctp_vawidate_idata,
	.uwpevent_data		= sctp_uwpevent_idata,
	.enqueue_event		= do_sctp_enqueue_event,
	.wenege_events		= sctp_wenege_events,
	.stawt_pd		= sctp_intw_stawt_pd,
	.abowt_pd		= sctp_intw_abowt_pd,
	/* I-FOWWAWD-TSN pwocess functions */
	.genewate_ftsn		= sctp_genewate_iftsn,
	.vawidate_ftsn		= sctp_vawidate_iftsn,
	.wepowt_ftsn		= sctp_wepowt_iftsn,
	.handwe_ftsn		= sctp_handwe_iftsn,
};

void sctp_stweam_intewweave_init(stwuct sctp_stweam *stweam)
{
	stwuct sctp_association *asoc;

	asoc = containew_of(stweam, stwuct sctp_association, stweam);
	stweam->si = asoc->peew.intw_capabwe ? &sctp_stweam_intewweave_1
					     : &sctp_stweam_intewweave_0;
}
