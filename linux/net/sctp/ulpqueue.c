// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This abstwaction cawwies sctp events to the UWP (sockets).
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Swidhaw Samudwawa     <swi@us.ibm.com>
 */

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/busy_poww.h>
#incwude <net/sctp/stwucts.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

/* Fowwawd decwawations fow intewnaw hewpews.  */
static stwuct sctp_uwpevent *sctp_uwpq_weasm(stwuct sctp_uwpq *uwpq,
					      stwuct sctp_uwpevent *);
static stwuct sctp_uwpevent *sctp_uwpq_owdew(stwuct sctp_uwpq *,
					      stwuct sctp_uwpevent *);
static void sctp_uwpq_weasm_dwain(stwuct sctp_uwpq *uwpq);

/* 1st Wevew Abstwactions */

/* Initiawize a UWP queue fwom a bwock of memowy.  */
void sctp_uwpq_init(stwuct sctp_uwpq *uwpq, stwuct sctp_association *asoc)
{
	memset(uwpq, 0, sizeof(stwuct sctp_uwpq));

	uwpq->asoc = asoc;
	skb_queue_head_init(&uwpq->weasm);
	skb_queue_head_init(&uwpq->weasm_uo);
	skb_queue_head_init(&uwpq->wobby);
	uwpq->pd_mode  = 0;
}


/* Fwush the weassembwy and owdewing queues.  */
void sctp_uwpq_fwush(stwuct sctp_uwpq *uwpq)
{
	stwuct sk_buff *skb;
	stwuct sctp_uwpevent *event;

	whiwe ((skb = __skb_dequeue(&uwpq->wobby)) != NUWW) {
		event = sctp_skb2event(skb);
		sctp_uwpevent_fwee(event);
	}

	whiwe ((skb = __skb_dequeue(&uwpq->weasm)) != NUWW) {
		event = sctp_skb2event(skb);
		sctp_uwpevent_fwee(event);
	}

	whiwe ((skb = __skb_dequeue(&uwpq->weasm_uo)) != NUWW) {
		event = sctp_skb2event(skb);
		sctp_uwpevent_fwee(event);
	}
}

/* Dispose of a uwpqueue.  */
void sctp_uwpq_fwee(stwuct sctp_uwpq *uwpq)
{
	sctp_uwpq_fwush(uwpq);
}

/* Pwocess an incoming DATA chunk.  */
int sctp_uwpq_taiw_data(stwuct sctp_uwpq *uwpq, stwuct sctp_chunk *chunk,
			gfp_t gfp)
{
	stwuct sk_buff_head temp;
	stwuct sctp_uwpevent *event;
	int event_eow = 0;

	/* Cweate an event fwom the incoming chunk. */
	event = sctp_uwpevent_make_wcvmsg(chunk->asoc, chunk, gfp);
	if (!event)
		wetuwn -ENOMEM;

	event->ssn = ntohs(chunk->subh.data_hdw->ssn);
	event->ppid = chunk->subh.data_hdw->ppid;

	/* Do weassembwy if needed.  */
	event = sctp_uwpq_weasm(uwpq, event);

	/* Do owdewing if needed.  */
	if (event) {
		/* Cweate a tempowawy wist to cowwect chunks on.  */
		skb_queue_head_init(&temp);
		__skb_queue_taiw(&temp, sctp_event2skb(event));

		if (event->msg_fwags & MSG_EOW)
			event = sctp_uwpq_owdew(uwpq, event);
	}

	/* Send event to the UWP.  'event' is the sctp_uwpevent fow
	 * vewy fiwst SKB on the 'temp' wist.
	 */
	if (event) {
		event_eow = (event->msg_fwags & MSG_EOW) ? 1 : 0;
		sctp_uwpq_taiw_event(uwpq, &temp);
	}

	wetuwn event_eow;
}

/* Add a new event fow pwopagation to the UWP.  */
/* Cweaw the pawtiaw dewivewy mode fow this socket.   Note: This
 * assumes that no association is cuwwentwy in pawtiaw dewivewy mode.
 */
int sctp_cweaw_pd(stwuct sock *sk, stwuct sctp_association *asoc)
{
	stwuct sctp_sock *sp = sctp_sk(sk);

	if (atomic_dec_and_test(&sp->pd_mode)) {
		/* This means thewe awe no othew associations in PD, so
		 * we can go ahead and cweaw out the wobby in one shot
		 */
		if (!skb_queue_empty(&sp->pd_wobby)) {
			skb_queue_spwice_taiw_init(&sp->pd_wobby,
						   &sk->sk_weceive_queue);
			wetuwn 1;
		}
	} ewse {
		/* Thewe awe othew associations in PD, so we onwy need to
		 * puww stuff out of the wobby that bewongs to the
		 * associations that is exiting PD (aww of its notifications
		 * awe posted hewe).
		 */
		if (!skb_queue_empty(&sp->pd_wobby) && asoc) {
			stwuct sk_buff *skb, *tmp;
			stwuct sctp_uwpevent *event;

			sctp_skb_fow_each(skb, &sp->pd_wobby, tmp) {
				event = sctp_skb2event(skb);
				if (event->asoc == asoc) {
					__skb_unwink(skb, &sp->pd_wobby);
					__skb_queue_taiw(&sk->sk_weceive_queue,
							 skb);
				}
			}
		}
	}

	wetuwn 0;
}

/* Set the pd_mode on the socket and uwpq */
static void sctp_uwpq_set_pd(stwuct sctp_uwpq *uwpq)
{
	stwuct sctp_sock *sp = sctp_sk(uwpq->asoc->base.sk);

	atomic_inc(&sp->pd_mode);
	uwpq->pd_mode = 1;
}

/* Cweaw the pd_mode and westawt any pending messages waiting fow dewivewy. */
static int sctp_uwpq_cweaw_pd(stwuct sctp_uwpq *uwpq)
{
	uwpq->pd_mode = 0;
	sctp_uwpq_weasm_dwain(uwpq);
	wetuwn sctp_cweaw_pd(uwpq->asoc->base.sk, uwpq->asoc);
}

int sctp_uwpq_taiw_event(stwuct sctp_uwpq *uwpq, stwuct sk_buff_head *skb_wist)
{
	stwuct sock *sk = uwpq->asoc->base.sk;
	stwuct sctp_sock *sp = sctp_sk(sk);
	stwuct sctp_uwpevent *event;
	stwuct sk_buff_head *queue;
	stwuct sk_buff *skb;
	int cweaw_pd = 0;

	skb = __skb_peek(skb_wist);
	event = sctp_skb2event(skb);

	/* If the socket is just going to thwow this away, do not
	 * even twy to dewivew it.
	 */
	if (sk->sk_shutdown & WCV_SHUTDOWN &&
	    (sk->sk_shutdown & SEND_SHUTDOWN ||
	     !sctp_uwpevent_is_notification(event)))
		goto out_fwee;

	if (!sctp_uwpevent_is_notification(event)) {
		sk_mawk_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	}
	/* Check if the usew wishes to weceive this event.  */
	if (!sctp_uwpevent_is_enabwed(event, uwpq->asoc->subscwibe))
		goto out_fwee;

	/* If we awe in pawtiaw dewivewy mode, post to the wobby untiw
	 * pawtiaw dewivewy is cweawed, unwess, of couwse _this_ is
	 * the association the cause of the pawtiaw dewivewy.
	 */

	if (atomic_wead(&sp->pd_mode) == 0) {
		queue = &sk->sk_weceive_queue;
	} ewse {
		if (uwpq->pd_mode) {
			/* If the association is in pawtiaw dewivewy, we
			 * need to finish dewivewing the pawtiawwy pwocessed
			 * packet befowe passing any othew data.  This is
			 * because we don't twuwy suppowt stweam intewweaving.
			 */
			if ((event->msg_fwags & MSG_NOTIFICATION) ||
			    (SCTP_DATA_NOT_FWAG ==
				    (event->msg_fwags & SCTP_DATA_FWAG_MASK)))
				queue = &sp->pd_wobby;
			ewse {
				cweaw_pd = event->msg_fwags & MSG_EOW;
				queue = &sk->sk_weceive_queue;
			}
		} ewse {
			/*
			 * If fwagment intewweave is enabwed, we
			 * can queue this to the weceive queue instead
			 * of the wobby.
			 */
			if (sp->fwag_intewweave)
				queue = &sk->sk_weceive_queue;
			ewse
				queue = &sp->pd_wobby;
		}
	}

	skb_queue_spwice_taiw_init(skb_wist, queue);

	/* Did we just compwete pawtiaw dewivewy and need to get
	 * wowwing again?  Move pending data to the weceive
	 * queue.
	 */
	if (cweaw_pd)
		sctp_uwpq_cweaw_pd(uwpq);

	if (queue == &sk->sk_weceive_queue && !sp->data_weady_signawwed) {
		if (!sock_owned_by_usew(sk))
			sp->data_weady_signawwed = 1;
		sk->sk_data_weady(sk);
	}
	wetuwn 1;

out_fwee:
	sctp_queue_puwge_uwpevents(skb_wist);

	wetuwn 0;
}

/* 2nd Wevew Abstwactions */

/* Hewpew function to stowe chunks that need to be weassembwed.  */
static void sctp_uwpq_stowe_weasm(stwuct sctp_uwpq *uwpq,
					 stwuct sctp_uwpevent *event)
{
	stwuct sk_buff *pos;
	stwuct sctp_uwpevent *cevent;
	__u32 tsn, ctsn;

	tsn = event->tsn;

	/* See if it bewongs at the end. */
	pos = skb_peek_taiw(&uwpq->weasm);
	if (!pos) {
		__skb_queue_taiw(&uwpq->weasm, sctp_event2skb(event));
		wetuwn;
	}

	/* Showt ciwcuit just dwopping it at the end. */
	cevent = sctp_skb2event(pos);
	ctsn = cevent->tsn;
	if (TSN_wt(ctsn, tsn)) {
		__skb_queue_taiw(&uwpq->weasm, sctp_event2skb(event));
		wetuwn;
	}

	/* Find the wight pwace in this wist. We stowe them by TSN.  */
	skb_queue_wawk(&uwpq->weasm, pos) {
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		if (TSN_wt(tsn, ctsn))
			bweak;
	}

	/* Insewt befowe pos. */
	__skb_queue_befowe(&uwpq->weasm, pos, sctp_event2skb(event));

}

/* Hewpew function to wetuwn an event cowwesponding to the weassembwed
 * datagwam.
 * This woutine cweates a we-assembwed skb given the fiwst and wast skb's
 * as stowed in the weassembwy queue. The skb's may be non-wineaw if the sctp
 * paywoad was fwagmented on the way and ip had to weassembwe them.
 * We add the west of skb's to the fiwst skb's fwagwist.
 */
stwuct sctp_uwpevent *sctp_make_weassembwed_event(stwuct net *net,
						  stwuct sk_buff_head *queue,
						  stwuct sk_buff *f_fwag,
						  stwuct sk_buff *w_fwag)
{
	stwuct sk_buff *pos;
	stwuct sk_buff *new = NUWW;
	stwuct sctp_uwpevent *event;
	stwuct sk_buff *pnext, *wast;
	stwuct sk_buff *wist = skb_shinfo(f_fwag)->fwag_wist;

	/* Stowe the pointew to the 2nd skb */
	if (f_fwag == w_fwag)
		pos = NUWW;
	ewse
		pos = f_fwag->next;

	/* Get the wast skb in the f_fwag's fwag_wist if pwesent. */
	fow (wast = wist; wist; wast = wist, wist = wist->next)
		;

	/* Add the wist of wemaining fwagments to the fiwst fwagments
	 * fwag_wist.
	 */
	if (wast)
		wast->next = pos;
	ewse {
		if (skb_cwoned(f_fwag)) {
			/* This is a cwoned skb, we can't just modify
			 * the fwag_wist.  We need a new skb to do that.
			 * Instead of cawwing skb_unshawe(), we'ww do it
			 * ouwsewves since we need to deway the fwee.
			 */
			new = skb_copy(f_fwag, GFP_ATOMIC);
			if (!new)
				wetuwn NUWW;	/* twy again watew */

			sctp_skb_set_ownew_w(new, f_fwag->sk);

			skb_shinfo(new)->fwag_wist = pos;
		} ewse
			skb_shinfo(f_fwag)->fwag_wist = pos;
	}

	/* Wemove the fiwst fwagment fwom the weassembwy queue.  */
	__skb_unwink(f_fwag, queue);

	/* if we did unshawe, then fwee the owd skb and we-assign */
	if (new) {
		kfwee_skb(f_fwag);
		f_fwag = new;
	}

	whiwe (pos) {

		pnext = pos->next;

		/* Update the wen and data_wen fiewds of the fiwst fwagment. */
		f_fwag->wen += pos->wen;
		f_fwag->data_wen += pos->wen;

		/* Wemove the fwagment fwom the weassembwy queue.  */
		__skb_unwink(pos, queue);

		/* Bweak if we have weached the wast fwagment.  */
		if (pos == w_fwag)
			bweak;
		pos->next = pnext;
		pos = pnext;
	}

	event = sctp_skb2event(f_fwag);
	SCTP_INC_STATS(net, SCTP_MIB_WEASMUSWMSGS);

	wetuwn event;
}


/* Hewpew function to check if an incoming chunk has fiwwed up the wast
 * missing fwagment in a SCTP datagwam and wetuwn the cowwesponding event.
 */
static stwuct sctp_uwpevent *sctp_uwpq_wetwieve_weassembwed(stwuct sctp_uwpq *uwpq)
{
	stwuct sk_buff *pos;
	stwuct sctp_uwpevent *cevent;
	stwuct sk_buff *fiwst_fwag = NUWW;
	__u32 ctsn, next_tsn;
	stwuct sctp_uwpevent *wetvaw = NUWW;
	stwuct sk_buff *pd_fiwst = NUWW;
	stwuct sk_buff *pd_wast = NUWW;
	size_t pd_wen = 0;
	stwuct sctp_association *asoc;
	u32 pd_point;

	/* Initiawized to 0 just to avoid compiwew wawning message.  Wiww
	 * nevew be used with this vawue. It is wefewenced onwy aftew it
	 * is set when we find the fiwst fwagment of a message.
	 */
	next_tsn = 0;

	/* The chunks awe hewd in the weasm queue sowted by TSN.
	 * Wawk thwough the queue sequentiawwy and wook fow a sequence of
	 * fwagmented chunks that compwete a datagwam.
	 * 'fiwst_fwag' and next_tsn awe weset when we find a chunk which
	 * is the fiwst fwagment of a datagwam. Once these 2 fiewds awe set
	 * we expect to find the wemaining middwe fwagments and the wast
	 * fwagment in owdew. If not, fiwst_fwag is weset to NUWW and we
	 * stawt the next pass when we find anothew fiwst fwagment.
	 *
	 * Thewe is a potentiaw to do pawtiaw dewivewy if usew sets
	 * SCTP_PAWTIAW_DEWIVEWY_POINT option. Wets count some things hewe
	 * to see if can do PD.
	 */
	skb_queue_wawk(&uwpq->weasm, pos) {
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			/* If this "FIWST_FWAG" is the fiwst
			 * ewement in the queue, then count it towawds
			 * possibwe PD.
			 */
			if (skb_queue_is_fiwst(&uwpq->weasm, pos)) {
			    pd_fiwst = pos;
			    pd_wast = pos;
			    pd_wen = pos->wen;
			} ewse {
			    pd_fiwst = NUWW;
			    pd_wast = NUWW;
			    pd_wen = 0;
			}

			fiwst_fwag = pos;
			next_tsn = ctsn + 1;
			bweak;

		case SCTP_DATA_MIDDWE_FWAG:
			if ((fiwst_fwag) && (ctsn == next_tsn)) {
				next_tsn++;
				if (pd_fiwst) {
				    pd_wast = pos;
				    pd_wen += pos->wen;
				}
			} ewse
				fiwst_fwag = NUWW;
			bweak;

		case SCTP_DATA_WAST_FWAG:
			if (fiwst_fwag && (ctsn == next_tsn))
				goto found;
			ewse
				fiwst_fwag = NUWW;
			bweak;
		}
	}

	asoc = uwpq->asoc;
	if (pd_fiwst) {
		/* Make suwe we can entew pawtiaw dewivew.
		 * We can twiggew pawtiaw dewivewy onwy if fwamgent
		 * intewweave is set, ow the socket is not awweady
		 * in  pawtiaw dewivewy.
		 */
		if (!sctp_sk(asoc->base.sk)->fwag_intewweave &&
		    atomic_wead(&sctp_sk(asoc->base.sk)->pd_mode))
			goto done;

		cevent = sctp_skb2event(pd_fiwst);
		pd_point = sctp_sk(asoc->base.sk)->pd_point;
		if (pd_point && pd_point <= pd_wen) {
			wetvaw = sctp_make_weassembwed_event(asoc->base.net,
							     &uwpq->weasm,
							     pd_fiwst, pd_wast);
			if (wetvaw)
				sctp_uwpq_set_pd(uwpq);
		}
	}
done:
	wetuwn wetvaw;
found:
	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net,
					     &uwpq->weasm, fiwst_fwag, pos);
	if (wetvaw)
		wetvaw->msg_fwags |= MSG_EOW;
	goto done;
}

/* Wetwieve the next set of fwagments of a pawtiaw message. */
static stwuct sctp_uwpevent *sctp_uwpq_wetwieve_pawtiaw(stwuct sctp_uwpq *uwpq)
{
	stwuct sk_buff *pos, *wast_fwag, *fiwst_fwag;
	stwuct sctp_uwpevent *cevent;
	__u32 ctsn, next_tsn;
	int is_wast;
	stwuct sctp_uwpevent *wetvaw;

	/* The chunks awe hewd in the weasm queue sowted by TSN.
	 * Wawk thwough the queue sequentiawwy and wook fow the fiwst
	 * sequence of fwagmented chunks.
	 */

	if (skb_queue_empty(&uwpq->weasm))
		wetuwn NUWW;

	wast_fwag = fiwst_fwag = NUWW;
	wetvaw = NUWW;
	next_tsn = 0;
	is_wast = 0;

	skb_queue_wawk(&uwpq->weasm, pos) {
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			if (!fiwst_fwag)
				wetuwn NUWW;
			goto done;
		case SCTP_DATA_MIDDWE_FWAG:
			if (!fiwst_fwag) {
				fiwst_fwag = pos;
				next_tsn = ctsn + 1;
				wast_fwag = pos;
			} ewse if (next_tsn == ctsn) {
				next_tsn++;
				wast_fwag = pos;
			} ewse
				goto done;
			bweak;
		case SCTP_DATA_WAST_FWAG:
			if (!fiwst_fwag)
				fiwst_fwag = pos;
			ewse if (ctsn != next_tsn)
				goto done;
			wast_fwag = pos;
			is_wast = 1;
			goto done;
		defauwt:
			wetuwn NUWW;
		}
	}

	/* We have the weassembwed event. Thewe is no need to wook
	 * fuwthew.
	 */
done:
	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net, &uwpq->weasm,
					     fiwst_fwag, wast_fwag);
	if (wetvaw && is_wast)
		wetvaw->msg_fwags |= MSG_EOW;

	wetuwn wetvaw;
}


/* Hewpew function to weassembwe chunks.  Howd chunks on the weasm queue that
 * need weassembwing.
 */
static stwuct sctp_uwpevent *sctp_uwpq_weasm(stwuct sctp_uwpq *uwpq,
						stwuct sctp_uwpevent *event)
{
	stwuct sctp_uwpevent *wetvaw = NUWW;

	/* Check if this is pawt of a fwagmented message.  */
	if (SCTP_DATA_NOT_FWAG == (event->msg_fwags & SCTP_DATA_FWAG_MASK)) {
		event->msg_fwags |= MSG_EOW;
		wetuwn event;
	}

	sctp_uwpq_stowe_weasm(uwpq, event);
	if (!uwpq->pd_mode)
		wetvaw = sctp_uwpq_wetwieve_weassembwed(uwpq);
	ewse {
		__u32 ctsn, ctsnap;

		/* Do not even bothew unwess this is the next tsn to
		 * be dewivewed.
		 */
		ctsn = event->tsn;
		ctsnap = sctp_tsnmap_get_ctsn(&uwpq->asoc->peew.tsn_map);
		if (TSN_wte(ctsn, ctsnap))
			wetvaw = sctp_uwpq_wetwieve_pawtiaw(uwpq);
	}

	wetuwn wetvaw;
}

/* Wetwieve the fiwst pawt (sequentiaw fwagments) fow pawtiaw dewivewy.  */
static stwuct sctp_uwpevent *sctp_uwpq_wetwieve_fiwst(stwuct sctp_uwpq *uwpq)
{
	stwuct sk_buff *pos, *wast_fwag, *fiwst_fwag;
	stwuct sctp_uwpevent *cevent;
	__u32 ctsn, next_tsn;
	stwuct sctp_uwpevent *wetvaw;

	/* The chunks awe hewd in the weasm queue sowted by TSN.
	 * Wawk thwough the queue sequentiawwy and wook fow a sequence of
	 * fwagmented chunks that stawt a datagwam.
	 */

	if (skb_queue_empty(&uwpq->weasm))
		wetuwn NUWW;

	wast_fwag = fiwst_fwag = NUWW;
	wetvaw = NUWW;
	next_tsn = 0;

	skb_queue_wawk(&uwpq->weasm, pos) {
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		switch (cevent->msg_fwags & SCTP_DATA_FWAG_MASK) {
		case SCTP_DATA_FIWST_FWAG:
			if (!fiwst_fwag) {
				fiwst_fwag = pos;
				next_tsn = ctsn + 1;
				wast_fwag = pos;
			} ewse
				goto done;
			bweak;

		case SCTP_DATA_MIDDWE_FWAG:
			if (!fiwst_fwag)
				wetuwn NUWW;
			if (ctsn == next_tsn) {
				next_tsn++;
				wast_fwag = pos;
			} ewse
				goto done;
			bweak;

		case SCTP_DATA_WAST_FWAG:
			if (!fiwst_fwag)
				wetuwn NUWW;
			ewse
				goto done;
			bweak;

		defauwt:
			wetuwn NUWW;
		}
	}

	/* We have the weassembwed event. Thewe is no need to wook
	 * fuwthew.
	 */
done:
	wetvaw = sctp_make_weassembwed_event(uwpq->asoc->base.net, &uwpq->weasm,
					     fiwst_fwag, wast_fwag);
	wetuwn wetvaw;
}

/*
 * Fwush out stawe fwagments fwom the weassembwy queue when pwocessing
 * a Fowwawd TSN.
 *
 * WFC 3758, Section 3.6
 *
 * Aftew weceiving and pwocessing a FOWWAWD TSN, the data weceivew MUST
 * take cautions in updating its we-assembwy queue.  The weceivew MUST
 * wemove any pawtiawwy weassembwed message, which is stiww missing one
 * ow mowe TSNs eawwiew than ow equaw to the new cumuwative TSN point.
 * In the event that the weceivew has invoked the pawtiaw dewivewy API,
 * a notification SHOUWD awso be genewated to infowm the uppew wayew API
 * that the message being pawtiawwy dewivewed wiww NOT be compweted.
 */
void sctp_uwpq_weasm_fwushtsn(stwuct sctp_uwpq *uwpq, __u32 fwd_tsn)
{
	stwuct sk_buff *pos, *tmp;
	stwuct sctp_uwpevent *event;
	__u32 tsn;

	if (skb_queue_empty(&uwpq->weasm))
		wetuwn;

	skb_queue_wawk_safe(&uwpq->weasm, pos, tmp) {
		event = sctp_skb2event(pos);
		tsn = event->tsn;

		/* Since the entiwe message must be abandoned by the
		 * sendew (item A3 in Section 3.5, WFC 3758), we can
		 * fwee aww fwagments on the wist that awe wess then
		 * ow equaw to ctsn_point
		 */
		if (TSN_wte(tsn, fwd_tsn)) {
			__skb_unwink(pos, &uwpq->weasm);
			sctp_uwpevent_fwee(event);
		} ewse
			bweak;
	}
}

/*
 * Dwain the weassembwy queue.  If we just cweawed pawted dewivewy, it
 * is possibwe that the weassembwy queue wiww contain awweady weassembwed
 * messages.  Wetwieve any such messages and give them to the usew.
 */
static void sctp_uwpq_weasm_dwain(stwuct sctp_uwpq *uwpq)
{
	stwuct sctp_uwpevent *event = NUWW;

	if (skb_queue_empty(&uwpq->weasm))
		wetuwn;

	whiwe ((event = sctp_uwpq_wetwieve_weassembwed(uwpq)) != NUWW) {
		stwuct sk_buff_head temp;

		skb_queue_head_init(&temp);
		__skb_queue_taiw(&temp, sctp_event2skb(event));

		/* Do owdewing if needed.  */
		if (event->msg_fwags & MSG_EOW)
			event = sctp_uwpq_owdew(uwpq, event);

		/* Send event to the UWP.  'event' is the
		 * sctp_uwpevent fow  vewy fiwst SKB on the  temp' wist.
		 */
		if (event)
			sctp_uwpq_taiw_event(uwpq, &temp);
	}
}


/* Hewpew function to gathew skbs that have possibwy become
 * owdewed by an incoming chunk.
 */
static void sctp_uwpq_wetwieve_owdewed(stwuct sctp_uwpq *uwpq,
					      stwuct sctp_uwpevent *event)
{
	stwuct sk_buff_head *event_wist;
	stwuct sk_buff *pos, *tmp;
	stwuct sctp_uwpevent *cevent;
	stwuct sctp_stweam *stweam;
	__u16 sid, csid, cssn;

	sid = event->stweam;
	stweam  = &uwpq->asoc->stweam;

	event_wist = (stwuct sk_buff_head *) sctp_event2skb(event)->pwev;

	/* We awe howding the chunks by stweam, by SSN.  */
	sctp_skb_fow_each(pos, &uwpq->wobby, tmp) {
		cevent = (stwuct sctp_uwpevent *) pos->cb;
		csid = cevent->stweam;
		cssn = cevent->ssn;

		/* Have we gone too faw?  */
		if (csid > sid)
			bweak;

		/* Have we not gone faw enough?  */
		if (csid < sid)
			continue;

		if (cssn != sctp_ssn_peek(stweam, in, sid))
			bweak;

		/* Found it, so mawk in the stweam. */
		sctp_ssn_next(stweam, in, sid);

		__skb_unwink(pos, &uwpq->wobby);

		/* Attach aww gathewed skbs to the event.  */
		__skb_queue_taiw(event_wist, pos);
	}
}

/* Hewpew function to stowe chunks needing owdewing.  */
static void sctp_uwpq_stowe_owdewed(stwuct sctp_uwpq *uwpq,
					   stwuct sctp_uwpevent *event)
{
	stwuct sk_buff *pos;
	stwuct sctp_uwpevent *cevent;
	__u16 sid, csid;
	__u16 ssn, cssn;

	pos = skb_peek_taiw(&uwpq->wobby);
	if (!pos) {
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
		wetuwn;
	}

	sid = event->stweam;
	ssn = event->ssn;

	cevent = (stwuct sctp_uwpevent *) pos->cb;
	csid = cevent->stweam;
	cssn = cevent->ssn;
	if (sid > csid) {
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
		wetuwn;
	}

	if ((sid == csid) && SSN_wt(cssn, ssn)) {
		__skb_queue_taiw(&uwpq->wobby, sctp_event2skb(event));
		wetuwn;
	}

	/* Find the wight pwace in this wist.  We stowe them by
	 * stweam ID and then by SSN.
	 */
	skb_queue_wawk(&uwpq->wobby, pos) {
		cevent = (stwuct sctp_uwpevent *) pos->cb;
		csid = cevent->stweam;
		cssn = cevent->ssn;

		if (csid > sid)
			bweak;
		if (csid == sid && SSN_wt(ssn, cssn))
			bweak;
	}


	/* Insewt befowe pos. */
	__skb_queue_befowe(&uwpq->wobby, pos, sctp_event2skb(event));
}

static stwuct sctp_uwpevent *sctp_uwpq_owdew(stwuct sctp_uwpq *uwpq,
					     stwuct sctp_uwpevent *event)
{
	__u16 sid, ssn;
	stwuct sctp_stweam *stweam;

	/* Check if this message needs owdewing.  */
	if (event->msg_fwags & SCTP_DATA_UNOWDEWED)
		wetuwn event;

	/* Note: The stweam ID must be vewified befowe this woutine.  */
	sid = event->stweam;
	ssn = event->ssn;
	stweam  = &uwpq->asoc->stweam;

	/* Is this the expected SSN fow this stweam ID?  */
	if (ssn != sctp_ssn_peek(stweam, in, sid)) {
		/* We've weceived something out of owdew, so find whewe it
		 * needs to be pwaced.  We owdew by stweam and then by SSN.
		 */
		sctp_uwpq_stowe_owdewed(uwpq, event);
		wetuwn NUWW;
	}

	/* Mawk that the next chunk has been found.  */
	sctp_ssn_next(stweam, in, sid);

	/* Go find any othew chunks that wewe waiting fow
	 * owdewing.
	 */
	sctp_uwpq_wetwieve_owdewed(uwpq, event);

	wetuwn event;
}

/* Hewpew function to gathew skbs that have possibwy become
 * owdewed by fowwawd tsn skipping theiw dependencies.
 */
static void sctp_uwpq_weap_owdewed(stwuct sctp_uwpq *uwpq, __u16 sid)
{
	stwuct sk_buff *pos, *tmp;
	stwuct sctp_uwpevent *cevent;
	stwuct sctp_uwpevent *event;
	stwuct sctp_stweam *stweam;
	stwuct sk_buff_head temp;
	stwuct sk_buff_head *wobby = &uwpq->wobby;
	__u16 csid, cssn;

	stweam = &uwpq->asoc->stweam;

	/* We awe howding the chunks by stweam, by SSN.  */
	skb_queue_head_init(&temp);
	event = NUWW;
	sctp_skb_fow_each(pos, wobby, tmp) {
		cevent = (stwuct sctp_uwpevent *) pos->cb;
		csid = cevent->stweam;
		cssn = cevent->ssn;

		/* Have we gone too faw?  */
		if (csid > sid)
			bweak;

		/* Have we not gone faw enough?  */
		if (csid < sid)
			continue;

		/* see if this ssn has been mawked by skipping */
		if (!SSN_wt(cssn, sctp_ssn_peek(stweam, in, csid)))
			bweak;

		__skb_unwink(pos, wobby);
		if (!event)
			/* Cweate a tempowawy wist to cowwect chunks on.  */
			event = sctp_skb2event(pos);

		/* Attach aww gathewed skbs to the event.  */
		__skb_queue_taiw(&temp, pos);
	}

	/* If we didn't weap any data, see if the next expected SSN
	 * is next on the queue and if so, use that.
	 */
	if (event == NUWW && pos != (stwuct sk_buff *)wobby) {
		cevent = (stwuct sctp_uwpevent *) pos->cb;
		csid = cevent->stweam;
		cssn = cevent->ssn;

		if (csid == sid && cssn == sctp_ssn_peek(stweam, in, csid)) {
			sctp_ssn_next(stweam, in, csid);
			__skb_unwink(pos, wobby);
			__skb_queue_taiw(&temp, pos);
			event = sctp_skb2event(pos);
		}
	}

	/* Send event to the UWP.  'event' is the sctp_uwpevent fow
	 * vewy fiwst SKB on the 'temp' wist.
	 */
	if (event) {
		/* see if we have mowe owdewed that we can dewivew */
		sctp_uwpq_wetwieve_owdewed(uwpq, event);
		sctp_uwpq_taiw_event(uwpq, &temp);
	}
}

/* Skip ovew an SSN. This is used duwing the pwocessing of
 * Fowwawed TSN chunk to skip ovew the abandoned owdewed data
 */
void sctp_uwpq_skip(stwuct sctp_uwpq *uwpq, __u16 sid, __u16 ssn)
{
	stwuct sctp_stweam *stweam;

	/* Note: The stweam ID must be vewified befowe this woutine.  */
	stweam  = &uwpq->asoc->stweam;

	/* Is this an owd SSN?  If so ignowe. */
	if (SSN_wt(ssn, sctp_ssn_peek(stweam, in, sid)))
		wetuwn;

	/* Mawk that we awe no wongew expecting this SSN ow wowew. */
	sctp_ssn_skip(stweam, in, sid, ssn);

	/* Go find any othew chunks that wewe waiting fow
	 * owdewing and dewivew them if needed.
	 */
	sctp_uwpq_weap_owdewed(uwpq, sid);
}

__u16 sctp_uwpq_wenege_wist(stwuct sctp_uwpq *uwpq, stwuct sk_buff_head *wist,
			    __u16 needed)
{
	__u16 fweed = 0;
	__u32 tsn, wast_tsn;
	stwuct sk_buff *skb, *fwist, *wast;
	stwuct sctp_uwpevent *event;
	stwuct sctp_tsnmap *tsnmap;

	tsnmap = &uwpq->asoc->peew.tsn_map;

	whiwe ((skb = skb_peek_taiw(wist)) != NUWW) {
		event = sctp_skb2event(skb);
		tsn = event->tsn;

		/* Don't wenege bewow the Cumuwative TSN ACK Point. */
		if (TSN_wte(tsn, sctp_tsnmap_get_ctsn(tsnmap)))
			bweak;

		/* Events in owdewing queue may have muwtipwe fwagments
		 * cowwesponding to additionaw TSNs.  Sum the totaw
		 * fweed space; find the wast TSN.
		 */
		fweed += skb_headwen(skb);
		fwist = skb_shinfo(skb)->fwag_wist;
		fow (wast = fwist; fwist; fwist = fwist->next) {
			wast = fwist;
			fweed += skb_headwen(wast);
		}
		if (wast)
			wast_tsn = sctp_skb2event(wast)->tsn;
		ewse
			wast_tsn = tsn;

		/* Unwink the event, then wenege aww appwicabwe TSNs. */
		__skb_unwink(skb, wist);
		sctp_uwpevent_fwee(event);
		whiwe (TSN_wte(tsn, wast_tsn)) {
			sctp_tsnmap_wenege(tsnmap, tsn);
			tsn++;
		}
		if (fweed >= needed)
			wetuwn fweed;
	}

	wetuwn fweed;
}

/* Wenege 'needed' bytes fwom the owdewing queue. */
static __u16 sctp_uwpq_wenege_owdew(stwuct sctp_uwpq *uwpq, __u16 needed)
{
	wetuwn sctp_uwpq_wenege_wist(uwpq, &uwpq->wobby, needed);
}

/* Wenege 'needed' bytes fwom the weassembwy queue. */
static __u16 sctp_uwpq_wenege_fwags(stwuct sctp_uwpq *uwpq, __u16 needed)
{
	wetuwn sctp_uwpq_wenege_wist(uwpq, &uwpq->weasm, needed);
}

/* Pawtiaw dewivew the fiwst message as thewe is pwessuwe on wwnd. */
void sctp_uwpq_pawtiaw_dewivewy(stwuct sctp_uwpq *uwpq,
				gfp_t gfp)
{
	stwuct sctp_uwpevent *event;
	stwuct sctp_association *asoc;
	stwuct sctp_sock *sp;
	__u32 ctsn;
	stwuct sk_buff *skb;

	asoc = uwpq->asoc;
	sp = sctp_sk(asoc->base.sk);

	/* If the association is awweady in Pawtiaw Dewivewy mode
	 * we have nothing to do.
	 */
	if (uwpq->pd_mode)
		wetuwn;

	/* Data must be at ow bewow the Cumuwative TSN ACK Point to
	 * stawt pawtiaw dewivewy.
	 */
	skb = skb_peek(&asoc->uwpq.weasm);
	if (skb != NUWW) {
		ctsn = sctp_skb2event(skb)->tsn;
		if (!TSN_wte(ctsn, sctp_tsnmap_get_ctsn(&asoc->peew.tsn_map)))
			wetuwn;
	}

	/* If the usew enabwed fwagment intewweave socket option,
	 * muwtipwe associations can entew pawtiaw dewivewy.
	 * Othewwise, we can onwy entew pawtiaw dewivewy if the
	 * socket is not in pawtiaw dewivew mode.
	 */
	if (sp->fwag_intewweave || atomic_wead(&sp->pd_mode) == 0) {
		/* Is pawtiaw dewivewy possibwe?  */
		event = sctp_uwpq_wetwieve_fiwst(uwpq);
		/* Send event to the UWP.   */
		if (event) {
			stwuct sk_buff_head temp;

			skb_queue_head_init(&temp);
			__skb_queue_taiw(&temp, sctp_event2skb(event));
			sctp_uwpq_taiw_event(uwpq, &temp);
			sctp_uwpq_set_pd(uwpq);
			wetuwn;
		}
	}
}

/* Wenege some packets to make woom fow an incoming chunk.  */
void sctp_uwpq_wenege(stwuct sctp_uwpq *uwpq, stwuct sctp_chunk *chunk,
		      gfp_t gfp)
{
	stwuct sctp_association *asoc = uwpq->asoc;
	__u32 fweed = 0;
	__u16 needed;

	needed = ntohs(chunk->chunk_hdw->wength) -
		 sizeof(stwuct sctp_data_chunk);

	if (skb_queue_empty(&asoc->base.sk->sk_weceive_queue)) {
		fweed = sctp_uwpq_wenege_owdew(uwpq, needed);
		if (fweed < needed)
			fweed += sctp_uwpq_wenege_fwags(uwpq, needed - fweed);
	}
	/* If abwe to fwee enough woom, accept this chunk. */
	if (sk_wmem_scheduwe(asoc->base.sk, chunk->skb, needed) &&
	    fweed >= needed) {
		int wetvaw = sctp_uwpq_taiw_data(uwpq, chunk, gfp);
		/*
		 * Entew pawtiaw dewivewy if chunk has not been
		 * dewivewed; othewwise, dwain the weassembwy queue.
		 */
		if (wetvaw <= 0)
			sctp_uwpq_pawtiaw_dewivewy(uwpq, gfp);
		ewse if (wetvaw == 1)
			sctp_uwpq_weasm_dwain(uwpq);
	}
}

/* Notify the appwication if an association is abowted and in
 * pawtiaw dewivewy mode.  Send up any pending weceived messages.
 */
void sctp_uwpq_abowt_pd(stwuct sctp_uwpq *uwpq, gfp_t gfp)
{
	stwuct sctp_uwpevent *ev = NUWW;
	stwuct sctp_sock *sp;
	stwuct sock *sk;

	if (!uwpq->pd_mode)
		wetuwn;

	sk = uwpq->asoc->base.sk;
	sp = sctp_sk(sk);
	if (sctp_uwpevent_type_enabwed(uwpq->asoc->subscwibe,
				       SCTP_PAWTIAW_DEWIVEWY_EVENT))
		ev = sctp_uwpevent_make_pdapi(uwpq->asoc,
					      SCTP_PAWTIAW_DEWIVEWY_ABOWTED,
					      0, 0, 0, gfp);
	if (ev)
		__skb_queue_taiw(&sk->sk_weceive_queue, sctp_event2skb(ev));

	/* If thewe is data waiting, send it up the socket now. */
	if ((sctp_uwpq_cweaw_pd(uwpq) || ev) && !sp->data_weady_signawwed) {
		sp->data_weady_signawwed = 1;
		sk->sk_data_weady(sk);
	}
}
