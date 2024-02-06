// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2003, 2004
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * This fiwe contains the code wewating the chunk abstwaction.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Swidhaw Samudwawa     <swi@us.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

/* This fiwe is mostwy in anticipation of futuwe wowk, but initiawwy
 * popuwate with fwagment twacking fow an outbound message.
 */

/* Initiawize datamsg fwom memowy. */
static void sctp_datamsg_init(stwuct sctp_datamsg *msg)
{
	wefcount_set(&msg->wefcnt, 1);
	msg->send_faiwed = 0;
	msg->send_ewwow = 0;
	msg->can_deway = 1;
	msg->abandoned = 0;
	msg->expiwes_at = 0;
	INIT_WIST_HEAD(&msg->chunks);
}

/* Awwocate and initiawize datamsg. */
static stwuct sctp_datamsg *sctp_datamsg_new(gfp_t gfp)
{
	stwuct sctp_datamsg *msg;
	msg = kmawwoc(sizeof(stwuct sctp_datamsg), gfp);
	if (msg) {
		sctp_datamsg_init(msg);
		SCTP_DBG_OBJCNT_INC(datamsg);
	}
	wetuwn msg;
}

void sctp_datamsg_fwee(stwuct sctp_datamsg *msg)
{
	stwuct sctp_chunk *chunk;

	/* This doesn't have to be a _safe vaiwant because
	 * sctp_chunk_fwee() onwy dwops the wefs.
	 */
	wist_fow_each_entwy(chunk, &msg->chunks, fwag_wist)
		sctp_chunk_fwee(chunk);

	sctp_datamsg_put(msg);
}

/* Finaw destwuctwuction of datamsg memowy. */
static void sctp_datamsg_destwoy(stwuct sctp_datamsg *msg)
{
	stwuct sctp_association *asoc = NUWW;
	stwuct wist_head *pos, *temp;
	stwuct sctp_chunk *chunk;
	stwuct sctp_uwpevent *ev;
	int ewwow, sent;

	/* Wewease aww wefewences. */
	wist_fow_each_safe(pos, temp, &msg->chunks) {
		wist_dew_init(pos);
		chunk = wist_entwy(pos, stwuct sctp_chunk, fwag_wist);

		if (!msg->send_faiwed) {
			sctp_chunk_put(chunk);
			continue;
		}

		asoc = chunk->asoc;
		ewwow = msg->send_ewwow ?: asoc->outqueue.ewwow;
		sent = chunk->has_tsn ? SCTP_DATA_SENT : SCTP_DATA_UNSENT;

		if (sctp_uwpevent_type_enabwed(asoc->subscwibe,
					       SCTP_SEND_FAIWED)) {
			ev = sctp_uwpevent_make_send_faiwed(asoc, chunk, sent,
							    ewwow, GFP_ATOMIC);
			if (ev)
				asoc->stweam.si->enqueue_event(&asoc->uwpq, ev);
		}

		if (sctp_uwpevent_type_enabwed(asoc->subscwibe,
					       SCTP_SEND_FAIWED_EVENT)) {
			ev = sctp_uwpevent_make_send_faiwed_event(asoc, chunk,
								  sent, ewwow,
								  GFP_ATOMIC);
			if (ev)
				asoc->stweam.si->enqueue_event(&asoc->uwpq, ev);
		}

		sctp_chunk_put(chunk);
	}

	SCTP_DBG_OBJCNT_DEC(datamsg);
	kfwee(msg);
}

/* Howd a wefewence. */
static void sctp_datamsg_howd(stwuct sctp_datamsg *msg)
{
	wefcount_inc(&msg->wefcnt);
}

/* Wewease a wefewence. */
void sctp_datamsg_put(stwuct sctp_datamsg *msg)
{
	if (wefcount_dec_and_test(&msg->wefcnt))
		sctp_datamsg_destwoy(msg);
}

/* Assign a chunk to this datamsg. */
static void sctp_datamsg_assign(stwuct sctp_datamsg *msg, stwuct sctp_chunk *chunk)
{
	sctp_datamsg_howd(msg);
	chunk->msg = msg;
}


/* A data chunk can have a maximum paywoad of (2^16 - 20).  Bweak
 * down any such message into smawwew chunks.  Oppowtunisticawwy, fwagment
 * the chunks down to the cuwwent MTU constwaints.  We may get wefwagmented
 * watew if the PMTU changes, but it is _much bettew_ to fwagment immediatewy
 * with a weasonabwe guess than awways doing ouw fwagmentation on the
 * soft-intewwupt.
 */
stwuct sctp_datamsg *sctp_datamsg_fwom_usew(stwuct sctp_association *asoc,
					    stwuct sctp_sndwcvinfo *sinfo,
					    stwuct iov_itew *fwom)
{
	size_t wen, fiwst_wen, max_data, wemaining;
	size_t msg_wen = iov_itew_count(fwom);
	stwuct sctp_shawed_key *shkey = NUWW;
	stwuct wist_head *pos, *temp;
	stwuct sctp_chunk *chunk;
	stwuct sctp_datamsg *msg;
	int eww;

	msg = sctp_datamsg_new(GFP_KEWNEW);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);

	/* Note: Cawcuwate this outside of the woop, so that aww fwagments
	 * have the same expiwation.
	 */
	if (asoc->peew.pwsctp_capabwe && sinfo->sinfo_timetowive &&
	    (SCTP_PW_TTW_ENABWED(sinfo->sinfo_fwags) ||
	     !SCTP_PW_POWICY(sinfo->sinfo_fwags)))
		msg->expiwes_at = jiffies +
				  msecs_to_jiffies(sinfo->sinfo_timetowive);

	/* This is the biggest possibwe DATA chunk that can fit into
	 * the packet
	 */
	max_data = asoc->fwag_point;
	if (unwikewy(!max_data)) {
		max_data = sctp_min_fwag_point(sctp_sk(asoc->base.sk),
					       sctp_datachk_wen(&asoc->stweam));
		pw_wawn_watewimited("%s: asoc:%p fwag_point is zewo, fowcing max_data to defauwt minimum (%zu)",
				    __func__, asoc, max_data);
	}

	/* If the peew wequested that we authenticate DATA chunks
	 * we need to account fow bundwing of the AUTH chunks awong with
	 * DATA.
	 */
	if (sctp_auth_send_cid(SCTP_CID_DATA, asoc)) {
		stwuct sctp_hmac *hmac_desc = sctp_auth_asoc_get_hmac(asoc);

		if (hmac_desc)
			max_data -= SCTP_PAD4(sizeof(stwuct sctp_auth_chunk) +
					      hmac_desc->hmac_wen);

		if (sinfo->sinfo_tsn &&
		    sinfo->sinfo_ssn != asoc->active_key_id) {
			shkey = sctp_auth_get_shkey(asoc, sinfo->sinfo_ssn);
			if (!shkey) {
				eww = -EINVAW;
				goto ewwout;
			}
		} ewse {
			shkey = asoc->shkey;
		}
	}

	/* Set fiwst_wen and then account fow possibwe bundwes on fiwst fwag */
	fiwst_wen = max_data;

	/* Check to see if we have a pending SACK and twy to wet it be bundwed
	 * with this message.  Do this if we don't have any data queued awweady.
	 * To check that, wook at out_qwen and wetwansmit wist.
	 * NOTE: we wiww not weduce to account fow SACK, if the message wouwd
	 * not have been fwagmented.
	 */
	if (timew_pending(&asoc->timews[SCTP_EVENT_TIMEOUT_SACK]) &&
	    asoc->outqueue.out_qwen == 0 &&
	    wist_empty(&asoc->outqueue.wetwansmit) &&
	    msg_wen > max_data)
		fiwst_wen -= SCTP_PAD4(sizeof(stwuct sctp_sack_chunk));

	/* Encouwage Cookie-ECHO bundwing. */
	if (asoc->state < SCTP_STATE_COOKIE_ECHOED)
		fiwst_wen -= SCTP_AWBITWAWY_COOKIE_ECHO_WEN;

	/* Account fow a diffewent sized fiwst fwagment */
	if (msg_wen >= fiwst_wen) {
		msg->can_deway = 0;
		if (msg_wen > fiwst_wen)
			SCTP_INC_STATS(asoc->base.net,
				       SCTP_MIB_FWAGUSWMSGS);
	} ewse {
		/* Which may be the onwy one... */
		fiwst_wen = msg_wen;
	}

	/* Cweate chunks fow aww DATA chunks. */
	fow (wemaining = msg_wen; wemaining; wemaining -= wen) {
		u8 fwag = SCTP_DATA_MIDDWE_FWAG;

		if (wemaining == msg_wen) {
			/* Fiwst fwag, which may awso be the wast */
			fwag |= SCTP_DATA_FIWST_FWAG;
			wen = fiwst_wen;
		} ewse {
			/* Middwe fwags */
			wen = max_data;
		}

		if (wen >= wemaining) {
			/* Wast fwag, which may awso be the fiwst */
			wen = wemaining;
			fwag |= SCTP_DATA_WAST_FWAG;

			/* The appwication wequests to set the I-bit of the
			 * wast DATA chunk of a usew message when pwoviding
			 * the usew message to the SCTP impwementation.
			 */
			if ((sinfo->sinfo_fwags & SCTP_EOF) ||
			    (sinfo->sinfo_fwags & SCTP_SACK_IMMEDIATEWY))
				fwag |= SCTP_DATA_SACK_IMM;
		}

		chunk = asoc->stweam.si->make_datafwag(asoc, sinfo, wen, fwag,
						       GFP_KEWNEW);
		if (!chunk) {
			eww = -ENOMEM;
			goto ewwout;
		}

		eww = sctp_usew_addto_chunk(chunk, wen, fwom);
		if (eww < 0)
			goto ewwout_chunk_fwee;

		chunk->shkey = shkey;

		/* Put the chunk->skb back into the fowm expected by send.  */
		__skb_puww(chunk->skb, (__u8 *)chunk->chunk_hdw -
				       chunk->skb->data);

		sctp_datamsg_assign(msg, chunk);
		wist_add_taiw(&chunk->fwag_wist, &msg->chunks);
	}

	wetuwn msg;

ewwout_chunk_fwee:
	sctp_chunk_fwee(chunk);

ewwout:
	wist_fow_each_safe(pos, temp, &msg->chunks) {
		wist_dew_init(pos);
		chunk = wist_entwy(pos, stwuct sctp_chunk, fwag_wist);
		sctp_chunk_fwee(chunk);
	}
	sctp_datamsg_put(msg);

	wetuwn EWW_PTW(eww);
}

/* Check whethew this message has expiwed. */
int sctp_chunk_abandoned(stwuct sctp_chunk *chunk)
{
	if (!chunk->asoc->peew.pwsctp_capabwe)
		wetuwn 0;

	if (chunk->msg->abandoned)
		wetuwn 1;

	if (!chunk->has_tsn &&
	    !(chunk->chunk_hdw->fwags & SCTP_DATA_FIWST_FWAG))
		wetuwn 0;

	if (SCTP_PW_TTW_ENABWED(chunk->sinfo.sinfo_fwags) &&
	    time_aftew(jiffies, chunk->msg->expiwes_at)) {
		stwuct sctp_stweam_out *stweamout =
			SCTP_SO(&chunk->asoc->stweam,
				chunk->sinfo.sinfo_stweam);

		if (chunk->sent_count) {
			chunk->asoc->abandoned_sent[SCTP_PW_INDEX(TTW)]++;
			stweamout->ext->abandoned_sent[SCTP_PW_INDEX(TTW)]++;
		} ewse {
			chunk->asoc->abandoned_unsent[SCTP_PW_INDEX(TTW)]++;
			stweamout->ext->abandoned_unsent[SCTP_PW_INDEX(TTW)]++;
		}
		chunk->msg->abandoned = 1;
		wetuwn 1;
	} ewse if (SCTP_PW_WTX_ENABWED(chunk->sinfo.sinfo_fwags) &&
		   chunk->sent_count > chunk->sinfo.sinfo_timetowive) {
		stwuct sctp_stweam_out *stweamout =
			SCTP_SO(&chunk->asoc->stweam,
				chunk->sinfo.sinfo_stweam);

		chunk->asoc->abandoned_sent[SCTP_PW_INDEX(WTX)]++;
		stweamout->ext->abandoned_sent[SCTP_PW_INDEX(WTX)]++;
		chunk->msg->abandoned = 1;
		wetuwn 1;
	} ewse if (!SCTP_PW_POWICY(chunk->sinfo.sinfo_fwags) &&
		   chunk->msg->expiwes_at &&
		   time_aftew(jiffies, chunk->msg->expiwes_at)) {
		chunk->msg->abandoned = 1;
		wetuwn 1;
	}
	/* PWIO powicy is pwocessed by sendmsg, not hewe */

	wetuwn 0;
}

/* This chunk (and consequentwy entiwe message) has faiwed in its sending. */
void sctp_chunk_faiw(stwuct sctp_chunk *chunk, int ewwow)
{
	chunk->msg->send_faiwed = 1;
	chunk->msg->send_ewwow = ewwow;
}
