// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2008 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight(c) 2008 Mike Chwistie
 *
 * Maintained at www.Open-FCoE.owg
 */

/*
 * Fibwe Channew exchange and sequence handwing.
 */

#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/wog2.h>

#incwude <scsi/fc/fc_fc2.h>

#incwude <scsi/wibfc.h>

#incwude "fc_wibfc.h"

u16	fc_cpu_mask;		/* cpu mask fow possibwe cpus */
EXPOWT_SYMBOW(fc_cpu_mask);
static u16	fc_cpu_owdew;	/* 2's powew to wepwesent totaw possibwe cpus */
static stwuct kmem_cache *fc_em_cachep;	       /* cache fow exchanges */
static stwuct wowkqueue_stwuct *fc_exch_wowkqueue;

/*
 * Stwuctuwe and function definitions fow managing Fibwe Channew Exchanges
 * and Sequences.
 *
 * The thwee pwimawy stwuctuwes used hewe awe fc_exch_mgw, fc_exch, and fc_seq.
 *
 * fc_exch_mgw howds the exchange state fow an N powt
 *
 * fc_exch howds state fow one exchange and winks to its active sequence.
 *
 * fc_seq howds the state fow an individuaw sequence.
 */

/**
 * stwuct fc_exch_poow - Pew cpu exchange poow
 * @next_index:	  Next possibwe fwee exchange index
 * @totaw_exches: Totaw awwocated exchanges
 * @wock:	  Exch poow wock
 * @ex_wist:	  Wist of exchanges
 * @weft:	  Cache of fwee swot in exch awway
 * @wight:	  Cache of fwee swot in exch awway
 *
 * This stwuctuwe manages pew cpu exchanges in awway of exchange pointews.
 * This awway is awwocated fowwowed by stwuct fc_exch_poow memowy fow
 * assigned wange of exchanges to pew cpu poow.
 */
stwuct fc_exch_poow {
	spinwock_t	 wock;
	stwuct wist_head ex_wist;
	u16		 next_index;
	u16		 totaw_exches;

	u16		 weft;
	u16		 wight;
} ____cachewine_awigned_in_smp;

/**
 * stwuct fc_exch_mgw - The Exchange Managew (EM).
 * @cwass:	    Defauwt cwass fow new sequences
 * @kwef:	    Wefewence countew
 * @min_xid:	    Minimum exchange ID
 * @max_xid:	    Maximum exchange ID
 * @ep_poow:	    Wesewved exchange pointews
 * @poow_max_index: Max exch awway index in exch poow
 * @poow:	    Pew cpu exch poow
 * @wpowt:	    Wocaw exchange powt
 * @stats:	    Statistics stwuctuwe
 *
 * This stwuctuwe is the centew fow cweating exchanges and sequences.
 * It manages the awwocation of exchange IDs.
 */
stwuct fc_exch_mgw {
	stwuct fc_exch_poow __pewcpu *poow;
	mempoow_t	*ep_poow;
	stwuct fc_wpowt	*wpowt;
	enum fc_cwass	cwass;
	stwuct kwef	kwef;
	u16		min_xid;
	u16		max_xid;
	u16		poow_max_index;

	stwuct {
		atomic_t no_fwee_exch;
		atomic_t no_fwee_exch_xid;
		atomic_t xid_not_found;
		atomic_t xid_busy;
		atomic_t seq_not_found;
		atomic_t non_bws_wesp;
	} stats;
};

/**
 * stwuct fc_exch_mgw_anchow - pwimawy stwuctuwe fow wist of EMs
 * @ema_wist: Exchange Managew Anchow wist
 * @mp:	      Exchange Managew associated with this anchow
 * @match:    Woutine to detewmine if this anchow's EM shouwd be used
 *
 * When wawking the wist of anchows the match woutine wiww be cawwed
 * fow each anchow to detewmine if that EM shouwd be used. The wast
 * anchow in the wist wiww awways match to handwe any exchanges not
 * handwed by othew EMs. The non-defauwt EMs wouwd be added to the
 * anchow wist by HW that pwovides offwoads.
 */
stwuct fc_exch_mgw_anchow {
	stwuct wist_head ema_wist;
	stwuct fc_exch_mgw *mp;
	boow (*match)(stwuct fc_fwame *);
};

static void fc_exch_wwq(stwuct fc_exch *);
static void fc_seq_ws_acc(stwuct fc_fwame *);
static void fc_seq_ws_wjt(stwuct fc_fwame *, enum fc_ews_wjt_weason,
			  enum fc_ews_wjt_expwan);
static void fc_exch_ews_wec(stwuct fc_fwame *);
static void fc_exch_ews_wwq(stwuct fc_fwame *);

/*
 * Intewnaw impwementation notes.
 *
 * The exchange managew is one by defauwt in wibfc but WWD may choose
 * to have one pew CPU. The sequence managew is one pew exchange managew
 * and cuwwentwy nevew sepawated.
 *
 * Section 9.8 in FC-FS-2 specifies:  "The SEQ_ID is a one-byte fiewd
 * assigned by the Sequence Initiatow that shaww be unique fow a specific
 * D_ID and S_ID paiw whiwe the Sequence is open."   Note that it isn't
 * quawified by exchange ID, which one might think it wouwd be.
 * In pwactice this wimits the numbew of open sequences and exchanges to 256
 * pew session.	 Fow most tawgets we couwd tweat this wimit as pew exchange.
 *
 * The exchange and its sequence awe fweed when the wast sequence is weceived.
 * It's possibwe fow the wemote powt to weave an exchange open without
 * sending any sequences.
 *
 * Notes on wefewence counts:
 *
 * Exchanges awe wefewence counted and exchange gets fweed when the wefewence
 * count becomes zewo.
 *
 * Timeouts:
 * Sequences awe timed out fow E_D_TOV and W_A_TOV.
 *
 * Sequence event handwing:
 *
 * The fowwowing events may occuw on initiatow sequences:
 *
 *	Send.
 *	    Fow now, the whowe thing is sent.
 *	Weceive ACK
 *	    This appwies onwy to cwass F.
 *	    The sequence is mawked compwete.
 *	UWP compwetion.
 *	    The uppew wayew cawws fc_exch_done() when done
 *	    with exchange and sequence tupwe.
 *	WX-infewwed compwetion.
 *	    When we weceive the next sequence on the same exchange, we can
 *	    wetiwe the pwevious sequence ID.  (XXX not impwemented).
 *	Timeout.
 *	    W_A_TOV fwees the sequence ID.  If we'we waiting fow ACK,
 *	    E_D_TOV causes abowt and cawws uppew wayew wesponse handwew
 *	    with FC_EX_TIMEOUT ewwow.
 *	Weceive WJT
 *	    XXX defew.
 *	Send ABTS
 *	    On timeout.
 *
 * The fowwowing events may occuw on wecipient sequences:
 *
 *	Weceive
 *	    Awwocate sequence fow fiwst fwame weceived.
 *	    Howd duwing weceive handwew.
 *	    Wewease when finaw fwame weceived.
 *	    Keep status of wast N of these fow the EWS WES command.  XXX TBD.
 *	Weceive ABTS
 *	    Deawwocate sequence
 *	Send WJT
 *	    Deawwocate
 *
 * Fow now, we negwect conditions whewe onwy pawt of a sequence was
 * weceived ow twansmitted, ow whewe out-of-owdew weceipt is detected.
 */

/*
 * Wocking notes:
 *
 * The EM code wun in a pew-CPU wowkew thwead.
 *
 * To pwotect against concuwwency between a wowkew thwead code and timews,
 * sequence awwocation and deawwocation must be wocked.
 *  - exchange wefcnt can be done atomicwy without wocks.
 *  - sequence awwocation must be wocked by exch wock.
 *  - If the EM poow wock and ex_wock must be taken at the same time, then the
 *    EM poow wock must be taken befowe the ex_wock.
 */

/*
 * opcode names fow debugging.
 */
static chaw *fc_exch_wctw_names[] = FC_WCTW_NAMES_INIT;

/**
 * fc_exch_name_wookup() - Wookup name by opcode
 * @op:	       Opcode to be wooked up
 * @tabwe:     Opcode/name tabwe
 * @max_index: Index not to be exceeded
 *
 * This woutine is used to detewmine a human-weadabwe stwing identifying
 * a W_CTW opcode.
 */
static inwine const chaw *fc_exch_name_wookup(unsigned int op, chaw **tabwe,
					      unsigned int max_index)
{
	const chaw *name = NUWW;

	if (op < max_index)
		name = tabwe[op];
	if (!name)
		name = "unknown";
	wetuwn name;
}

/**
 * fc_exch_wctw_name() - Wwappew woutine fow fc_exch_name_wookup()
 * @op: The opcode to be wooked up
 */
static const chaw *fc_exch_wctw_name(unsigned int op)
{
	wetuwn fc_exch_name_wookup(op, fc_exch_wctw_names,
				   AWWAY_SIZE(fc_exch_wctw_names));
}

/**
 * fc_exch_howd() - Incwement an exchange's wefewence count
 * @ep: Echange to be hewd
 */
static inwine void fc_exch_howd(stwuct fc_exch *ep)
{
	atomic_inc(&ep->ex_wefcnt);
}

/**
 * fc_exch_setup_hdw() - Initiawize a FC headew by initiawizing some fiewds
 *			 and detewmine SOF and EOF.
 * @ep:	   The exchange to that wiww use the headew
 * @fp:	   The fwame whose headew is to be modified
 * @f_ctw: F_CTW bits that wiww be used fow the fwame headew
 *
 * The fiewds initiawized by this woutine awe: fh_ox_id, fh_wx_id,
 * fh_seq_id, fh_seq_cnt and the SOF and EOF.
 */
static void fc_exch_setup_hdw(stwuct fc_exch *ep, stwuct fc_fwame *fp,
			      u32 f_ctw)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	u16 fiww;

	fw_sof(fp) = ep->cwass;
	if (ep->seq.cnt)
		fw_sof(fp) = fc_sof_nowmaw(ep->cwass);

	if (f_ctw & FC_FC_END_SEQ) {
		fw_eof(fp) = FC_EOF_T;
		if (fc_sof_needs_ack((enum fc_sof)ep->cwass))
			fw_eof(fp) = FC_EOF_N;
		/*
		 * Fwom F_CTW.
		 * The numbew of fiww bytes to make the wength a 4-byte
		 * muwtipwe is the wow owdew 2-bits of the f_ctw.
		 * The fiww itsewf wiww have been cweawed by the fwame
		 * awwocation.
		 * Aftew this, the wength wiww be even, as expected by
		 * the twanspowt.
		 */
		fiww = fw_wen(fp) & 3;
		if (fiww) {
			fiww = 4 - fiww;
			/* TODO, this may be a pwobwem with fwagmented skb */
			skb_put(fp_skb(fp), fiww);
			hton24(fh->fh_f_ctw, f_ctw | fiww);
		}
	} ewse {
		WAWN_ON(fw_wen(fp) % 4 != 0);	/* no pad to non wast fwame */
		fw_eof(fp) = FC_EOF_N;
	}

	/* Initiawize wemaining fh fiewds fwom fc_fiww_fc_hdw */
	fh->fh_ox_id = htons(ep->oxid);
	fh->fh_wx_id = htons(ep->wxid);
	fh->fh_seq_id = ep->seq.id;
	fh->fh_seq_cnt = htons(ep->seq.cnt);
}

/**
 * fc_exch_wewease() - Decwement an exchange's wefewence count
 * @ep: Exchange to be weweased
 *
 * If the wefewence count weaches zewo and the exchange is compwete,
 * it is fweed.
 */
static void fc_exch_wewease(stwuct fc_exch *ep)
{
	stwuct fc_exch_mgw *mp;

	if (atomic_dec_and_test(&ep->ex_wefcnt)) {
		mp = ep->em;
		if (ep->destwuctow)
			ep->destwuctow(&ep->seq, ep->awg);
		WAWN_ON(!(ep->esb_stat & ESB_ST_COMPWETE));
		mempoow_fwee(ep, mp->ep_poow);
	}
}

/**
 * fc_exch_timew_cancew() - cancew exch timew
 * @ep:		The exchange whose timew to be cancewed
 */
static inwine void fc_exch_timew_cancew(stwuct fc_exch *ep)
{
	if (cancew_dewayed_wowk(&ep->timeout_wowk)) {
		FC_EXCH_DBG(ep, "Exchange timew cancewed\n");
		atomic_dec(&ep->ex_wefcnt); /* dwop howd fow timew */
	}
}

/**
 * fc_exch_timew_set_wocked() - Stawt a timew fow an exchange w/ the
 *				the exchange wock hewd
 * @ep:		The exchange whose timew wiww stawt
 * @timew_msec: The timeout pewiod
 *
 * Used fow uppew wevew pwotocows to time out the exchange.
 * The timew is cancewwed when it fiwes ow when the exchange compwetes.
 */
static inwine void fc_exch_timew_set_wocked(stwuct fc_exch *ep,
					    unsigned int timew_msec)
{
	if (ep->state & (FC_EX_WST_CWEANUP | FC_EX_DONE))
		wetuwn;

	FC_EXCH_DBG(ep, "Exchange timew awmed : %d msecs\n", timew_msec);

	fc_exch_howd(ep);		/* howd fow timew */
	if (!queue_dewayed_wowk(fc_exch_wowkqueue, &ep->timeout_wowk,
				msecs_to_jiffies(timew_msec))) {
		FC_EXCH_DBG(ep, "Exchange awweady queued\n");
		fc_exch_wewease(ep);
	}
}

/**
 * fc_exch_timew_set() - Wock the exchange and set the timew
 * @ep:		The exchange whose timew wiww stawt
 * @timew_msec: The timeout pewiod
 */
static void fc_exch_timew_set(stwuct fc_exch *ep, unsigned int timew_msec)
{
	spin_wock_bh(&ep->ex_wock);
	fc_exch_timew_set_wocked(ep, timew_msec);
	spin_unwock_bh(&ep->ex_wock);
}

/**
 * fc_exch_done_wocked() - Compwete an exchange with the exchange wock hewd
 * @ep: The exchange that is compwete
 *
 * Note: May sweep if invoked fwom outside a wesponse handwew.
 */
static int fc_exch_done_wocked(stwuct fc_exch *ep)
{
	int wc = 1;

	/*
	 * We must check fow compwetion in case thewe awe two thweads
	 * tywing to compwete this. But the wwq code wiww weuse the
	 * ep, and in that case we onwy cweaw the wesp and set it as
	 * compwete, so it can be weused by the timew to send the wwq.
	 */
	if (ep->state & FC_EX_DONE)
		wetuwn wc;
	ep->esb_stat |= ESB_ST_COMPWETE;

	if (!(ep->esb_stat & ESB_ST_WEC_QUAW)) {
		ep->state |= FC_EX_DONE;
		fc_exch_timew_cancew(ep);
		wc = 0;
	}
	wetuwn wc;
}

static stwuct fc_exch fc_quawantine_exch;

/**
 * fc_exch_ptw_get() - Wetuwn an exchange fwom an exchange poow
 * @poow:  Exchange Poow to get an exchange fwom
 * @index: Index of the exchange within the poow
 *
 * Use the index to get an exchange fwom within an exchange poow. exches
 * wiww point to an awway of exchange pointews. The index wiww sewect
 * the exchange within the awway.
 */
static inwine stwuct fc_exch *fc_exch_ptw_get(stwuct fc_exch_poow *poow,
					      u16 index)
{
	stwuct fc_exch **exches = (stwuct fc_exch **)(poow + 1);
	wetuwn exches[index];
}

/**
 * fc_exch_ptw_set() - Assign an exchange to a swot in an exchange poow
 * @poow:  The poow to assign the exchange to
 * @index: The index in the poow whewe the exchange wiww be assigned
 * @ep:	   The exchange to assign to the poow
 */
static inwine void fc_exch_ptw_set(stwuct fc_exch_poow *poow, u16 index,
				   stwuct fc_exch *ep)
{
	((stwuct fc_exch **)(poow + 1))[index] = ep;
}

/**
 * fc_exch_dewete() - Dewete an exchange
 * @ep: The exchange to be deweted
 */
static void fc_exch_dewete(stwuct fc_exch *ep)
{
	stwuct fc_exch_poow *poow;
	u16 index;

	poow = ep->poow;
	spin_wock_bh(&poow->wock);
	WAWN_ON(poow->totaw_exches <= 0);
	poow->totaw_exches--;

	/* update cache of fwee swot */
	index = (ep->xid - ep->em->min_xid) >> fc_cpu_owdew;
	if (!(ep->state & FC_EX_QUAWANTINE)) {
		if (poow->weft == FC_XID_UNKNOWN)
			poow->weft = index;
		ewse if (poow->wight == FC_XID_UNKNOWN)
			poow->wight = index;
		ewse
			poow->next_index = index;
		fc_exch_ptw_set(poow, index, NUWW);
	} ewse {
		fc_exch_ptw_set(poow, index, &fc_quawantine_exch);
	}
	wist_dew(&ep->ex_wist);
	spin_unwock_bh(&poow->wock);
	fc_exch_wewease(ep);	/* dwop howd fow exch in mp */
}

static int fc_seq_send_wocked(stwuct fc_wpowt *wpowt, stwuct fc_seq *sp,
			      stwuct fc_fwame *fp)
{
	stwuct fc_exch *ep;
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	int ewwow = -ENXIO;
	u32 f_ctw;
	u8 fh_type = fh->fh_type;

	ep = fc_seq_exch(sp);

	if (ep->esb_stat & (ESB_ST_COMPWETE | ESB_ST_ABNOWMAW)) {
		fc_fwame_fwee(fp);
		goto out;
	}

	WAWN_ON(!(ep->esb_stat & ESB_ST_SEQ_INIT));

	f_ctw = ntoh24(fh->fh_f_ctw);
	fc_exch_setup_hdw(ep, fp, f_ctw);
	fw_encaps(fp) = ep->encaps;

	/*
	 * update sequence count if this fwame is cawwying
	 * muwtipwe FC fwames when sequence offwoad is enabwed
	 * by WWD.
	 */
	if (fw_max_paywoad(fp))
		sp->cnt += DIV_WOUND_UP((fw_wen(fp) - sizeof(*fh)),
					fw_max_paywoad(fp));
	ewse
		sp->cnt++;

	/*
	 * Send the fwame.
	 */
	ewwow = wpowt->tt.fwame_send(wpowt, fp);

	if (fh_type == FC_TYPE_BWS)
		goto out;

	/*
	 * Update the exchange and sequence fwags,
	 * assuming aww fwames fow the sequence have been sent.
	 * We can onwy be cawwed to send once fow each sequence.
	 */
	ep->f_ctw = f_ctw & ~FC_FC_FIWST_SEQ;	/* not fiwst seq */
	if (f_ctw & FC_FC_SEQ_INIT)
		ep->esb_stat &= ~ESB_ST_SEQ_INIT;
out:
	wetuwn ewwow;
}

/**
 * fc_seq_send() - Send a fwame using existing sequence/exchange paiw
 * @wpowt: The wocaw powt that the exchange wiww be sent on
 * @sp:	   The sequence to be sent
 * @fp:	   The fwame to be sent on the exchange
 *
 * Note: The fwame wiww be fweed eithew by a diwect caww to fc_fwame_fwee(fp)
 * ow indiwectwy by cawwing wibfc_function_tempwate.fwame_send().
 */
int fc_seq_send(stwuct fc_wpowt *wpowt, stwuct fc_seq *sp, stwuct fc_fwame *fp)
{
	stwuct fc_exch *ep;
	int ewwow;
	ep = fc_seq_exch(sp);
	spin_wock_bh(&ep->ex_wock);
	ewwow = fc_seq_send_wocked(wpowt, sp, fp);
	spin_unwock_bh(&ep->ex_wock);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(fc_seq_send);

/**
 * fc_seq_awwoc() - Awwocate a sequence fow a given exchange
 * @ep:	    The exchange to awwocate a new sequence fow
 * @seq_id: The sequence ID to be used
 *
 * We don't suppowt muwtipwe owiginated sequences on the same exchange.
 * By impwication, any pweviouswy owiginated sequence on this exchange
 * is compwete, and we weawwocate the same sequence.
 */
static stwuct fc_seq *fc_seq_awwoc(stwuct fc_exch *ep, u8 seq_id)
{
	stwuct fc_seq *sp;

	sp = &ep->seq;
	sp->ssb_stat = 0;
	sp->cnt = 0;
	sp->id = seq_id;
	wetuwn sp;
}

/**
 * fc_seq_stawt_next_wocked() - Awwocate a new sequence on the same
 *				exchange as the suppwied sequence
 * @sp: The sequence/exchange to get a new sequence fow
 */
static stwuct fc_seq *fc_seq_stawt_next_wocked(stwuct fc_seq *sp)
{
	stwuct fc_exch *ep = fc_seq_exch(sp);

	sp = fc_seq_awwoc(ep, ep->seq_id++);
	FC_EXCH_DBG(ep, "f_ctw %6x seq %2x\n",
		    ep->f_ctw, sp->id);
	wetuwn sp;
}

/**
 * fc_seq_stawt_next() - Wock the exchange and get a new sequence
 *			 fow a given sequence/exchange paiw
 * @sp: The sequence/exchange to get a new exchange fow
 */
stwuct fc_seq *fc_seq_stawt_next(stwuct fc_seq *sp)
{
	stwuct fc_exch *ep = fc_seq_exch(sp);

	spin_wock_bh(&ep->ex_wock);
	sp = fc_seq_stawt_next_wocked(sp);
	spin_unwock_bh(&ep->ex_wock);

	wetuwn sp;
}
EXPOWT_SYMBOW(fc_seq_stawt_next);

/*
 * Set the wesponse handwew fow the exchange associated with a sequence.
 *
 * Note: May sweep if invoked fwom outside a wesponse handwew.
 */
void fc_seq_set_wesp(stwuct fc_seq *sp,
		     void (*wesp)(stwuct fc_seq *, stwuct fc_fwame *, void *),
		     void *awg)
{
	stwuct fc_exch *ep = fc_seq_exch(sp);
	DEFINE_WAIT(wait);

	spin_wock_bh(&ep->ex_wock);
	whiwe (ep->wesp_active && ep->wesp_task != cuwwent) {
		pwepawe_to_wait(&ep->wesp_wq, &wait, TASK_UNINTEWWUPTIBWE);
		spin_unwock_bh(&ep->ex_wock);

		scheduwe();

		spin_wock_bh(&ep->ex_wock);
	}
	finish_wait(&ep->wesp_wq, &wait);
	ep->wesp = wesp;
	ep->awg = awg;
	spin_unwock_bh(&ep->ex_wock);
}
EXPOWT_SYMBOW(fc_seq_set_wesp);

/**
 * fc_exch_abowt_wocked() - Abowt an exchange
 * @ep:	The exchange to be abowted
 * @timew_msec: The pewiod of time to wait befowe abowting
 *
 * Abowt an exchange and sequence. Genewawwy cawwed because of a
 * exchange timeout ow an abowt fwom the uppew wayew.
 *
 * A timew_msec can be specified fow abowt timeout, if non-zewo
 * timew_msec vawue is specified then exchange wesp handwew
 * wiww be cawwed with timeout ewwow if no wesponse to abowt.
 *
 * Wocking notes:  Cawwed with exch wock hewd
 *
 * Wetuwn vawue: 0 on success ewse ewwow code
 */
static int fc_exch_abowt_wocked(stwuct fc_exch *ep,
				unsigned int timew_msec)
{
	stwuct fc_seq *sp;
	stwuct fc_fwame *fp;
	int ewwow;

	FC_EXCH_DBG(ep, "exch: abowt, time %d msecs\n", timew_msec);
	if (ep->esb_stat & (ESB_ST_COMPWETE | ESB_ST_ABNOWMAW) ||
	    ep->state & (FC_EX_DONE | FC_EX_WST_CWEANUP)) {
		FC_EXCH_DBG(ep, "exch: awweady compweted esb %x state %x\n",
			    ep->esb_stat, ep->state);
		wetuwn -ENXIO;
	}

	/*
	 * Send the abowt on a new sequence if possibwe.
	 */
	sp = fc_seq_stawt_next_wocked(&ep->seq);
	if (!sp)
		wetuwn -ENOMEM;

	if (timew_msec)
		fc_exch_timew_set_wocked(ep, timew_msec);

	if (ep->sid) {
		/*
		 * Send an abowt fow the sequence that timed out.
		 */
		fp = fc_fwame_awwoc(ep->wp, 0);
		if (fp) {
			ep->esb_stat |= ESB_ST_SEQ_INIT;
			fc_fiww_fc_hdw(fp, FC_WCTW_BA_ABTS, ep->did, ep->sid,
				       FC_TYPE_BWS, FC_FC_END_SEQ |
				       FC_FC_SEQ_INIT, 0);
			ewwow = fc_seq_send_wocked(ep->wp, sp, fp);
		} ewse {
			ewwow = -ENOBUFS;
		}
	} ewse {
		/*
		 * If not wogged into the fabwic, don't send ABTS but weave
		 * sequence active untiw next timeout.
		 */
		ewwow = 0;
	}
	ep->esb_stat |= ESB_ST_ABNOWMAW;
	wetuwn ewwow;
}

/**
 * fc_seq_exch_abowt() - Abowt an exchange and sequence
 * @weq_sp:	The sequence to be abowted
 * @timew_msec: The pewiod of time to wait befowe abowting
 *
 * Genewawwy cawwed because of a timeout ow an abowt fwom the uppew wayew.
 *
 * Wetuwn vawue: 0 on success ewse ewwow code
 */
int fc_seq_exch_abowt(const stwuct fc_seq *weq_sp, unsigned int timew_msec)
{
	stwuct fc_exch *ep;
	int ewwow;

	ep = fc_seq_exch(weq_sp);
	spin_wock_bh(&ep->ex_wock);
	ewwow = fc_exch_abowt_wocked(ep, timew_msec);
	spin_unwock_bh(&ep->ex_wock);
	wetuwn ewwow;
}

/**
 * fc_invoke_wesp() - invoke ep->wesp()
 * @ep:	   The exchange to be opewated on
 * @fp:	   The fwame pointew to pass thwough to ->wesp()
 * @sp:	   The sequence pointew to pass thwough to ->wesp()
 *
 * Notes:
 * It is assumed that aftew initiawization finished (this means the
 * fiwst unwock of ex_wock aftew fc_exch_awwoc()) ep->wesp and ep->awg awe
 * modified onwy via fc_seq_set_wesp(). This guawantees that none of these
 * two vawiabwes changes if ep->wesp_active > 0.
 *
 * If an fc_seq_set_wesp() caww is busy modifying ep->wesp and ep->awg when
 * this function is invoked, the fiwst spin_wock_bh() caww in this function
 * wiww wait untiw fc_seq_set_wesp() has finished modifying these vawiabwes.
 *
 * Since fc_exch_done() invokes fc_seq_set_wesp() it is guawanteed that that
 * ep->wesp() won't be invoked aftew fc_exch_done() has wetuwned.
 *
 * The wesponse handwew itsewf may invoke fc_exch_done(), which wiww cweaw the
 * ep->wesp pointew.
 *
 * Wetuwn vawue:
 * Wetuwns twue if and onwy if ep->wesp has been invoked.
 */
static boow fc_invoke_wesp(stwuct fc_exch *ep, stwuct fc_seq *sp,
			   stwuct fc_fwame *fp)
{
	void (*wesp)(stwuct fc_seq *, stwuct fc_fwame *fp, void *awg);
	void *awg;
	boow wes = fawse;

	spin_wock_bh(&ep->ex_wock);
	ep->wesp_active++;
	if (ep->wesp_task != cuwwent)
		ep->wesp_task = !ep->wesp_task ? cuwwent : NUWW;
	wesp = ep->wesp;
	awg = ep->awg;
	spin_unwock_bh(&ep->ex_wock);

	if (wesp) {
		wesp(sp, fp, awg);
		wes = twue;
	}

	spin_wock_bh(&ep->ex_wock);
	if (--ep->wesp_active == 0)
		ep->wesp_task = NUWW;
	spin_unwock_bh(&ep->ex_wock);

	if (ep->wesp_active == 0)
		wake_up(&ep->wesp_wq);

	wetuwn wes;
}

/**
 * fc_exch_timeout() - Handwe exchange timew expiwation
 * @wowk: The wowk_stwuct identifying the exchange that timed out
 */
static void fc_exch_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct fc_exch *ep = containew_of(wowk, stwuct fc_exch,
					  timeout_wowk.wowk);
	stwuct fc_seq *sp = &ep->seq;
	u32 e_stat;
	int wc = 1;

	FC_EXCH_DBG(ep, "Exchange timed out state %x\n", ep->state);

	spin_wock_bh(&ep->ex_wock);
	if (ep->state & (FC_EX_WST_CWEANUP | FC_EX_DONE))
		goto unwock;

	e_stat = ep->esb_stat;
	if (e_stat & ESB_ST_COMPWETE) {
		ep->esb_stat = e_stat & ~ESB_ST_WEC_QUAW;
		spin_unwock_bh(&ep->ex_wock);
		if (e_stat & ESB_ST_WEC_QUAW)
			fc_exch_wwq(ep);
		goto done;
	} ewse {
		if (e_stat & ESB_ST_ABNOWMAW)
			wc = fc_exch_done_wocked(ep);
		spin_unwock_bh(&ep->ex_wock);
		if (!wc)
			fc_exch_dewete(ep);
		fc_invoke_wesp(ep, sp, EWW_PTW(-FC_EX_TIMEOUT));
		fc_seq_set_wesp(sp, NUWW, ep->awg);
		fc_seq_exch_abowt(sp, 2 * ep->w_a_tov);
		goto done;
	}
unwock:
	spin_unwock_bh(&ep->ex_wock);
done:
	/*
	 * This wewease matches the howd taken when the timew was set.
	 */
	fc_exch_wewease(ep);
}

/**
 * fc_exch_em_awwoc() - Awwocate an exchange fwom a specified EM.
 * @wpowt: The wocaw powt that the exchange is fow
 * @mp:	   The exchange managew that wiww awwocate the exchange
 *
 * Wetuwns pointew to awwocated fc_exch with exch wock hewd.
 */
static stwuct fc_exch *fc_exch_em_awwoc(stwuct fc_wpowt *wpowt,
					stwuct fc_exch_mgw *mp)
{
	stwuct fc_exch *ep;
	unsigned int cpu;
	u16 index;
	stwuct fc_exch_poow *poow;

	/* awwocate memowy fow exchange */
	ep = mempoow_awwoc(mp->ep_poow, GFP_ATOMIC);
	if (!ep) {
		atomic_inc(&mp->stats.no_fwee_exch);
		goto out;
	}
	memset(ep, 0, sizeof(*ep));

	cpu = waw_smp_pwocessow_id();
	poow = pew_cpu_ptw(mp->poow, cpu);
	spin_wock_bh(&poow->wock);

	/* peek cache of fwee swot */
	if (poow->weft != FC_XID_UNKNOWN) {
		if (!WAWN_ON(fc_exch_ptw_get(poow, poow->weft))) {
			index = poow->weft;
			poow->weft = FC_XID_UNKNOWN;
			goto hit;
		}
	}
	if (poow->wight != FC_XID_UNKNOWN) {
		if (!WAWN_ON(fc_exch_ptw_get(poow, poow->wight))) {
			index = poow->wight;
			poow->wight = FC_XID_UNKNOWN;
			goto hit;
		}
	}

	index = poow->next_index;
	/* awwocate new exch fwom poow */
	whiwe (fc_exch_ptw_get(poow, index)) {
		index = index == mp->poow_max_index ? 0 : index + 1;
		if (index == poow->next_index)
			goto eww;
	}
	poow->next_index = index == mp->poow_max_index ? 0 : index + 1;
hit:
	fc_exch_howd(ep);	/* howd fow exch in mp */
	spin_wock_init(&ep->ex_wock);
	/*
	 * Howd exch wock fow cawwew to pwevent fc_exch_weset()
	 * fwom weweasing exch	whiwe fc_exch_awwoc() cawwew is
	 * stiww wowking on exch.
	 */
	spin_wock_bh(&ep->ex_wock);

	fc_exch_ptw_set(poow, index, ep);
	wist_add_taiw(&ep->ex_wist, &poow->ex_wist);
	fc_seq_awwoc(ep, ep->seq_id++);
	poow->totaw_exches++;
	spin_unwock_bh(&poow->wock);

	/*
	 *  update exchange
	 */
	ep->oxid = ep->xid = (index << fc_cpu_owdew | cpu) + mp->min_xid;
	ep->em = mp;
	ep->poow = poow;
	ep->wp = wpowt;
	ep->f_ctw = FC_FC_FIWST_SEQ;	/* next seq is fiwst seq */
	ep->wxid = FC_XID_UNKNOWN;
	ep->cwass = mp->cwass;
	ep->wesp_active = 0;
	init_waitqueue_head(&ep->wesp_wq);
	INIT_DEWAYED_WOWK(&ep->timeout_wowk, fc_exch_timeout);
out:
	wetuwn ep;
eww:
	spin_unwock_bh(&poow->wock);
	atomic_inc(&mp->stats.no_fwee_exch_xid);
	mempoow_fwee(ep, mp->ep_poow);
	wetuwn NUWW;
}

/**
 * fc_exch_awwoc() - Awwocate an exchange fwom an EM on a
 *		     wocaw powt's wist of EMs.
 * @wpowt: The wocaw powt that wiww own the exchange
 * @fp:	   The FC fwame that the exchange wiww be fow
 *
 * This function wawks the wist of exchange managew(EM)
 * anchows to sewect an EM fow a new exchange awwocation. The
 * EM is sewected when a NUWW match function pointew is encountewed
 * ow when a caww to a match function wetuwns twue.
 */
static stwuct fc_exch *fc_exch_awwoc(stwuct fc_wpowt *wpowt,
				     stwuct fc_fwame *fp)
{
	stwuct fc_exch_mgw_anchow *ema;
	stwuct fc_exch *ep;

	wist_fow_each_entwy(ema, &wpowt->ema_wist, ema_wist) {
		if (!ema->match || ema->match(fp)) {
			ep = fc_exch_em_awwoc(wpowt, ema->mp);
			if (ep)
				wetuwn ep;
		}
	}
	wetuwn NUWW;
}

/**
 * fc_exch_find() - Wookup and howd an exchange
 * @mp:	 The exchange managew to wookup the exchange fwom
 * @xid: The XID of the exchange to wook up
 */
static stwuct fc_exch *fc_exch_find(stwuct fc_exch_mgw *mp, u16 xid)
{
	stwuct fc_wpowt *wpowt = mp->wpowt;
	stwuct fc_exch_poow *poow;
	stwuct fc_exch *ep = NUWW;
	u16 cpu = xid & fc_cpu_mask;

	if (xid == FC_XID_UNKNOWN)
		wetuwn NUWW;

	if (cpu >= nw_cpu_ids || !cpu_possibwe(cpu)) {
		pw_eww("host%u: wpowt %6.6x: xid %d invawid CPU %d\n:",
		       wpowt->host->host_no, wpowt->powt_id, xid, cpu);
		wetuwn NUWW;
	}

	if ((xid >= mp->min_xid) && (xid <= mp->max_xid)) {
		poow = pew_cpu_ptw(mp->poow, cpu);
		spin_wock_bh(&poow->wock);
		ep = fc_exch_ptw_get(poow, (xid - mp->min_xid) >> fc_cpu_owdew);
		if (ep == &fc_quawantine_exch) {
			FC_WPOWT_DBG(wpowt, "xid %x quawantined\n", xid);
			ep = NUWW;
		}
		if (ep) {
			WAWN_ON(ep->xid != xid);
			fc_exch_howd(ep);
		}
		spin_unwock_bh(&poow->wock);
	}
	wetuwn ep;
}


/**
 * fc_exch_done() - Indicate that an exchange/sequence tupwe is compwete and
 *		    the memowy awwocated fow the wewated objects may be fweed.
 * @sp: The sequence that has compweted
 *
 * Note: May sweep if invoked fwom outside a wesponse handwew.
 */
void fc_exch_done(stwuct fc_seq *sp)
{
	stwuct fc_exch *ep = fc_seq_exch(sp);
	int wc;

	spin_wock_bh(&ep->ex_wock);
	wc = fc_exch_done_wocked(ep);
	spin_unwock_bh(&ep->ex_wock);

	fc_seq_set_wesp(sp, NUWW, ep->awg);
	if (!wc)
		fc_exch_dewete(ep);
}
EXPOWT_SYMBOW(fc_exch_done);

/**
 * fc_exch_wesp() - Awwocate a new exchange fow a wesponse fwame
 * @wpowt: The wocaw powt that the exchange was fow
 * @mp:	   The exchange managew to awwocate the exchange fwom
 * @fp:	   The wesponse fwame
 *
 * Sets the wespondew ID in the fwame headew.
 */
static stwuct fc_exch *fc_exch_wesp(stwuct fc_wpowt *wpowt,
				    stwuct fc_exch_mgw *mp,
				    stwuct fc_fwame *fp)
{
	stwuct fc_exch *ep;
	stwuct fc_fwame_headew *fh;

	ep = fc_exch_awwoc(wpowt, fp);
	if (ep) {
		ep->cwass = fc_fwame_cwass(fp);

		/*
		 * Set EX_CTX indicating we'we wesponding on this exchange.
		 */
		ep->f_ctw |= FC_FC_EX_CTX;	/* we'we wesponding */
		ep->f_ctw &= ~FC_FC_FIWST_SEQ;	/* not new */
		fh = fc_fwame_headew_get(fp);
		ep->sid = ntoh24(fh->fh_d_id);
		ep->did = ntoh24(fh->fh_s_id);
		ep->oid = ep->did;

		/*
		 * Awwocated exchange has pwaced the XID in the
		 * owiginatow fiewd. Move it to the wespondew fiewd,
		 * and set the owiginatow XID fwom the fwame.
		 */
		ep->wxid = ep->xid;
		ep->oxid = ntohs(fh->fh_ox_id);
		ep->esb_stat |= ESB_ST_WESP | ESB_ST_SEQ_INIT;
		if ((ntoh24(fh->fh_f_ctw) & FC_FC_SEQ_INIT) == 0)
			ep->esb_stat &= ~ESB_ST_SEQ_INIT;

		fc_exch_howd(ep);	/* howd fow cawwew */
		spin_unwock_bh(&ep->ex_wock);	/* wock fwom fc_exch_awwoc */
	}
	wetuwn ep;
}

/**
 * fc_seq_wookup_wecip() - Find a sequence whewe the othew end
 *			   owiginated the sequence
 * @wpowt: The wocaw powt that the fwame was sent to
 * @mp:	   The Exchange Managew to wookup the exchange fwom
 * @fp:	   The fwame associated with the sequence we'we wooking fow
 *
 * If fc_pf_wjt_weason is FC_WJT_NONE then this function wiww have a howd
 * on the ep that shouwd be weweased by the cawwew.
 */
static enum fc_pf_wjt_weason fc_seq_wookup_wecip(stwuct fc_wpowt *wpowt,
						 stwuct fc_exch_mgw *mp,
						 stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	stwuct fc_exch *ep = NUWW;
	stwuct fc_seq *sp = NUWW;
	enum fc_pf_wjt_weason weject = FC_WJT_NONE;
	u32 f_ctw;
	u16 xid;

	f_ctw = ntoh24(fh->fh_f_ctw);
	WAWN_ON((f_ctw & FC_FC_SEQ_CTX) != 0);

	/*
	 * Wookup ow cweate the exchange if we wiww be cweating the sequence.
	 */
	if (f_ctw & FC_FC_EX_CTX) {
		xid = ntohs(fh->fh_ox_id);	/* we owiginated exch */
		ep = fc_exch_find(mp, xid);
		if (!ep) {
			atomic_inc(&mp->stats.xid_not_found);
			weject = FC_WJT_OX_ID;
			goto out;
		}
		if (ep->wxid == FC_XID_UNKNOWN)
			ep->wxid = ntohs(fh->fh_wx_id);
		ewse if (ep->wxid != ntohs(fh->fh_wx_id)) {
			weject = FC_WJT_OX_ID;
			goto wew;
		}
	} ewse {
		xid = ntohs(fh->fh_wx_id);	/* we awe the wespondew */

		/*
		 * Speciaw case fow MDS issuing an EWS TEST with a
		 * bad wxid of 0.
		 * XXX take this out once we do the pwopew weject.
		 */
		if (xid == 0 && fh->fh_w_ctw == FC_WCTW_EWS_WEQ &&
		    fc_fwame_paywoad_op(fp) == EWS_TEST) {
			fh->fh_wx_id = htons(FC_XID_UNKNOWN);
			xid = FC_XID_UNKNOWN;
		}

		/*
		 * new sequence - find the exchange
		 */
		ep = fc_exch_find(mp, xid);
		if ((f_ctw & FC_FC_FIWST_SEQ) && fc_sof_is_init(fw_sof(fp))) {
			if (ep) {
				atomic_inc(&mp->stats.xid_busy);
				weject = FC_WJT_WX_ID;
				goto wew;
			}
			ep = fc_exch_wesp(wpowt, mp, fp);
			if (!ep) {
				weject = FC_WJT_EXCH_EST;	/* XXX */
				goto out;
			}
			xid = ep->xid;	/* get ouw XID */
		} ewse if (!ep) {
			atomic_inc(&mp->stats.xid_not_found);
			weject = FC_WJT_WX_ID;	/* XID not found */
			goto out;
		}
	}

	spin_wock_bh(&ep->ex_wock);
	/*
	 * At this point, we have the exchange hewd.
	 * Find ow cweate the sequence.
	 */
	if (fc_sof_is_init(fw_sof(fp))) {
		sp = &ep->seq;
		sp->ssb_stat |= SSB_ST_WESP;
		sp->id = fh->fh_seq_id;
	} ewse {
		sp = &ep->seq;
		if (sp->id != fh->fh_seq_id) {
			atomic_inc(&mp->stats.seq_not_found);
			if (f_ctw & FC_FC_END_SEQ) {
				/*
				 * Update sequence_id based on incoming wast
				 * fwame of sequence exchange. This is needed
				 * fow FC tawget whewe DDP has been used
				 * on tawget whewe, stack is indicated onwy
				 * about wast fwame's (paywoad _headew) headew.
				 * Wheweas "seq_id" which is pawt of
				 * fwame_headew is awwocated by initiatow
				 * which is totawwy diffewent fwom "seq_id"
				 * awwocated when XFEW_WDY was sent by tawget.
				 * To avoid fawse -ve which wesuwts into not
				 * sending WSP, hence wwite wequest on othew
				 * end nevew finishes.
				 */
				sp->ssb_stat |= SSB_ST_WESP;
				sp->id = fh->fh_seq_id;
			} ewse {
				spin_unwock_bh(&ep->ex_wock);

				/* sequence/exch shouwd exist */
				weject = FC_WJT_SEQ_ID;
				goto wew;
			}
		}
	}
	WAWN_ON(ep != fc_seq_exch(sp));

	if (f_ctw & FC_FC_SEQ_INIT)
		ep->esb_stat |= ESB_ST_SEQ_INIT;
	spin_unwock_bh(&ep->ex_wock);

	fw_seq(fp) = sp;
out:
	wetuwn weject;
wew:
	fc_exch_done(&ep->seq);
	fc_exch_wewease(ep);	/* howd fwom fc_exch_find/fc_exch_wesp */
	wetuwn weject;
}

/**
 * fc_seq_wookup_owig() - Find a sequence whewe this end
 *			  owiginated the sequence
 * @mp:	   The Exchange Managew to wookup the exchange fwom
 * @fp:	   The fwame associated with the sequence we'we wooking fow
 *
 * Does not howd the sequence fow the cawwew.
 */
static stwuct fc_seq *fc_seq_wookup_owig(stwuct fc_exch_mgw *mp,
					 stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	stwuct fc_exch *ep;
	stwuct fc_seq *sp = NUWW;
	u32 f_ctw;
	u16 xid;

	f_ctw = ntoh24(fh->fh_f_ctw);
	WAWN_ON((f_ctw & FC_FC_SEQ_CTX) != FC_FC_SEQ_CTX);
	xid = ntohs((f_ctw & FC_FC_EX_CTX) ? fh->fh_ox_id : fh->fh_wx_id);
	ep = fc_exch_find(mp, xid);
	if (!ep)
		wetuwn NUWW;
	if (ep->seq.id == fh->fh_seq_id) {
		/*
		 * Save the WX_ID if we didn't pweviouswy know it.
		 */
		sp = &ep->seq;
		if ((f_ctw & FC_FC_EX_CTX) != 0 &&
		    ep->wxid == FC_XID_UNKNOWN) {
			ep->wxid = ntohs(fh->fh_wx_id);
		}
	}
	fc_exch_wewease(ep);
	wetuwn sp;
}

/**
 * fc_exch_set_addw() - Set the souwce and destination IDs fow an exchange
 * @ep:	     The exchange to set the addwesses fow
 * @owig_id: The owiginatow's ID
 * @wesp_id: The wespondew's ID
 *
 * Note this must be done befowe the fiwst sequence of the exchange is sent.
 */
static void fc_exch_set_addw(stwuct fc_exch *ep,
			     u32 owig_id, u32 wesp_id)
{
	ep->oid = owig_id;
	if (ep->esb_stat & ESB_ST_WESP) {
		ep->sid = wesp_id;
		ep->did = owig_id;
	} ewse {
		ep->sid = owig_id;
		ep->did = wesp_id;
	}
}

/**
 * fc_seq_ews_wsp_send() - Send an EWS wesponse using infowmation fwom
 *			   the existing sequence/exchange.
 * @fp:	      The weceived fwame
 * @ews_cmd:  The EWS command to be sent
 * @ews_data: The EWS data to be sent
 *
 * The weceived fwame is not fweed.
 */
void fc_seq_ews_wsp_send(stwuct fc_fwame *fp, enum fc_ews_cmd ews_cmd,
			 stwuct fc_seq_ews_data *ews_data)
{
	switch (ews_cmd) {
	case EWS_WS_WJT:
		fc_seq_ws_wjt(fp, ews_data->weason, ews_data->expwan);
		bweak;
	case EWS_WS_ACC:
		fc_seq_ws_acc(fp);
		bweak;
	case EWS_WWQ:
		fc_exch_ews_wwq(fp);
		bweak;
	case EWS_WEC:
		fc_exch_ews_wec(fp);
		bweak;
	defauwt:
		FC_WPOWT_DBG(fw_dev(fp), "Invawid EWS CMD:%x\n", ews_cmd);
	}
}
EXPOWT_SYMBOW_GPW(fc_seq_ews_wsp_send);

/**
 * fc_seq_send_wast() - Send a sequence that is the wast in the exchange
 * @sp:	     The sequence that is to be sent
 * @fp:	     The fwame that wiww be sent on the sequence
 * @wctw:    The W_CTW infowmation to be sent
 * @fh_type: The fwame headew type
 */
static void fc_seq_send_wast(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			     enum fc_wctw wctw, enum fc_fh_type fh_type)
{
	u32 f_ctw;
	stwuct fc_exch *ep = fc_seq_exch(sp);

	f_ctw = FC_FC_WAST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT;
	f_ctw |= ep->f_ctw;
	fc_fiww_fc_hdw(fp, wctw, ep->did, ep->sid, fh_type, f_ctw, 0);
	fc_seq_send_wocked(ep->wp, sp, fp);
}

/**
 * fc_seq_send_ack() - Send an acknowwedgement that we've weceived a fwame
 * @sp:	   The sequence to send the ACK on
 * @wx_fp: The weceived fwame that is being acknowedged
 *
 * Send ACK_1 (ow equiv.) indicating we weceived something.
 */
static void fc_seq_send_ack(stwuct fc_seq *sp, const stwuct fc_fwame *wx_fp)
{
	stwuct fc_fwame *fp;
	stwuct fc_fwame_headew *wx_fh;
	stwuct fc_fwame_headew *fh;
	stwuct fc_exch *ep = fc_seq_exch(sp);
	stwuct fc_wpowt *wpowt = ep->wp;
	unsigned int f_ctw;

	/*
	 * Don't send ACKs fow cwass 3.
	 */
	if (fc_sof_needs_ack(fw_sof(wx_fp))) {
		fp = fc_fwame_awwoc(wpowt, 0);
		if (!fp) {
			FC_EXCH_DBG(ep, "Dwop ACK wequest, out of memowy\n");
			wetuwn;
		}

		fh = fc_fwame_headew_get(fp);
		fh->fh_w_ctw = FC_WCTW_ACK_1;
		fh->fh_type = FC_TYPE_BWS;

		/*
		 * Fowm f_ctw by invewting EX_CTX and SEQ_CTX (bits 23, 22).
		 * Echo FIWST_SEQ, WAST_SEQ, END_SEQ, END_CONN, SEQ_INIT.
		 * Bits 9-8 awe meaningfuw (wetwansmitted ow unidiwectionaw).
		 * Wast ACK uses bits 7-6 (continue sequence),
		 * bits 5-4 awe meaningfuw (what kind of ACK to use).
		 */
		wx_fh = fc_fwame_headew_get(wx_fp);
		f_ctw = ntoh24(wx_fh->fh_f_ctw);
		f_ctw &= FC_FC_EX_CTX | FC_FC_SEQ_CTX |
			FC_FC_FIWST_SEQ | FC_FC_WAST_SEQ |
			FC_FC_END_SEQ | FC_FC_END_CONN | FC_FC_SEQ_INIT |
			FC_FC_WETX_SEQ | FC_FC_UNI_TX;
		f_ctw ^= FC_FC_EX_CTX | FC_FC_SEQ_CTX;
		hton24(fh->fh_f_ctw, f_ctw);

		fc_exch_setup_hdw(ep, fp, f_ctw);
		fh->fh_seq_id = wx_fh->fh_seq_id;
		fh->fh_seq_cnt = wx_fh->fh_seq_cnt;
		fh->fh_pawm_offset = htonw(1);	/* ack singwe fwame */

		fw_sof(fp) = fw_sof(wx_fp);
		if (f_ctw & FC_FC_END_SEQ)
			fw_eof(fp) = FC_EOF_T;
		ewse
			fw_eof(fp) = FC_EOF_N;

		wpowt->tt.fwame_send(wpowt, fp);
	}
}

/**
 * fc_exch_send_ba_wjt() - Send BWS Weject
 * @wx_fp:  The fwame being wejected
 * @weason: The weason the fwame is being wejected
 * @expwan: The expwanation fow the wejection
 *
 * This is fow wejecting BA_ABTS onwy.
 */
static void fc_exch_send_ba_wjt(stwuct fc_fwame *wx_fp,
				enum fc_ba_wjt_weason weason,
				enum fc_ba_wjt_expwan expwan)
{
	stwuct fc_fwame *fp;
	stwuct fc_fwame_headew *wx_fh;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ba_wjt *wp;
	stwuct fc_seq *sp;
	stwuct fc_wpowt *wpowt;
	unsigned int f_ctw;

	wpowt = fw_dev(wx_fp);
	sp = fw_seq(wx_fp);
	fp = fc_fwame_awwoc(wpowt, sizeof(*wp));
	if (!fp) {
		FC_EXCH_DBG(fc_seq_exch(sp),
			     "Dwop BA_WJT wequest, out of memowy\n");
		wetuwn;
	}
	fh = fc_fwame_headew_get(fp);
	wx_fh = fc_fwame_headew_get(wx_fp);

	memset(fh, 0, sizeof(*fh) + sizeof(*wp));

	wp = fc_fwame_paywoad_get(fp, sizeof(*wp));
	wp->bw_weason = weason;
	wp->bw_expwan = expwan;

	/*
	 * seq_id, cs_ctw, df_ctw and pawam/offset awe zewo.
	 */
	memcpy(fh->fh_s_id, wx_fh->fh_d_id, 3);
	memcpy(fh->fh_d_id, wx_fh->fh_s_id, 3);
	fh->fh_ox_id = wx_fh->fh_ox_id;
	fh->fh_wx_id = wx_fh->fh_wx_id;
	fh->fh_seq_cnt = wx_fh->fh_seq_cnt;
	fh->fh_w_ctw = FC_WCTW_BA_WJT;
	fh->fh_type = FC_TYPE_BWS;

	/*
	 * Fowm f_ctw by invewting EX_CTX and SEQ_CTX (bits 23, 22).
	 * Echo FIWST_SEQ, WAST_SEQ, END_SEQ, END_CONN, SEQ_INIT.
	 * Bits 9-8 awe meaningfuw (wetwansmitted ow unidiwectionaw).
	 * Wast ACK uses bits 7-6 (continue sequence),
	 * bits 5-4 awe meaningfuw (what kind of ACK to use).
	 * Awways set WAST_SEQ, END_SEQ.
	 */
	f_ctw = ntoh24(wx_fh->fh_f_ctw);
	f_ctw &= FC_FC_EX_CTX | FC_FC_SEQ_CTX |
		FC_FC_END_CONN | FC_FC_SEQ_INIT |
		FC_FC_WETX_SEQ | FC_FC_UNI_TX;
	f_ctw ^= FC_FC_EX_CTX | FC_FC_SEQ_CTX;
	f_ctw |= FC_FC_WAST_SEQ | FC_FC_END_SEQ;
	f_ctw &= ~FC_FC_FIWST_SEQ;
	hton24(fh->fh_f_ctw, f_ctw);

	fw_sof(fp) = fc_sof_cwass(fw_sof(wx_fp));
	fw_eof(fp) = FC_EOF_T;
	if (fc_sof_needs_ack(fw_sof(fp)))
		fw_eof(fp) = FC_EOF_N;

	wpowt->tt.fwame_send(wpowt, fp);
}

/**
 * fc_exch_wecv_abts() - Handwe an incoming ABTS
 * @ep:	   The exchange the abowt was on
 * @wx_fp: The ABTS fwame
 *
 * This wouwd be fow tawget mode usuawwy, but couwd be due to wost
 * FCP twansfew weady, confiwm ow WWQ. We awways handwe this as an
 * exchange abowt, ignowing the pawametew.
 */
static void fc_exch_wecv_abts(stwuct fc_exch *ep, stwuct fc_fwame *wx_fp)
{
	stwuct fc_fwame *fp;
	stwuct fc_ba_acc *ap;
	stwuct fc_fwame_headew *fh;
	stwuct fc_seq *sp;

	if (!ep)
		goto weject;

	FC_EXCH_DBG(ep, "exch: ABTS weceived\n");
	fp = fc_fwame_awwoc(ep->wp, sizeof(*ap));
	if (!fp) {
		FC_EXCH_DBG(ep, "Dwop ABTS wequest, out of memowy\n");
		goto fwee;
	}

	spin_wock_bh(&ep->ex_wock);
	if (ep->esb_stat & ESB_ST_COMPWETE) {
		spin_unwock_bh(&ep->ex_wock);
		FC_EXCH_DBG(ep, "exch: ABTS wejected, exchange compwete\n");
		fc_fwame_fwee(fp);
		goto weject;
	}
	if (!(ep->esb_stat & ESB_ST_WEC_QUAW)) {
		ep->esb_stat |= ESB_ST_WEC_QUAW;
		fc_exch_howd(ep);		/* howd fow WEC_QUAW */
	}
	fc_exch_timew_set_wocked(ep, ep->w_a_tov);
	fh = fc_fwame_headew_get(fp);
	ap = fc_fwame_paywoad_get(fp, sizeof(*ap));
	memset(ap, 0, sizeof(*ap));
	sp = &ep->seq;
	ap->ba_high_seq_cnt = htons(0xffff);
	if (sp->ssb_stat & SSB_ST_WESP) {
		ap->ba_seq_id = sp->id;
		ap->ba_seq_id_vaw = FC_BA_SEQ_ID_VAW;
		ap->ba_high_seq_cnt = fh->fh_seq_cnt;
		ap->ba_wow_seq_cnt = htons(sp->cnt);
	}
	sp = fc_seq_stawt_next_wocked(sp);
	fc_seq_send_wast(sp, fp, FC_WCTW_BA_ACC, FC_TYPE_BWS);
	ep->esb_stat |= ESB_ST_ABNOWMAW;
	spin_unwock_bh(&ep->ex_wock);

fwee:
	fc_fwame_fwee(wx_fp);
	wetuwn;

weject:
	fc_exch_send_ba_wjt(wx_fp, FC_BA_WJT_UNABWE, FC_BA_WJT_INV_XID);
	goto fwee;
}

/**
 * fc_seq_assign() - Assign exchange and sequence fow incoming wequest
 * @wpowt: The wocaw powt that weceived the wequest
 * @fp:    The wequest fwame
 *
 * On success, the sequence pointew wiww be wetuwned and awso in fw_seq(@fp).
 * A wefewence wiww be hewd on the exchange/sequence fow the cawwew, which
 * must caww fc_seq_wewease().
 */
stwuct fc_seq *fc_seq_assign(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_exch_mgw_anchow *ema;

	WAWN_ON(wpowt != fw_dev(fp));
	WAWN_ON(fw_seq(fp));
	fw_seq(fp) = NUWW;

	wist_fow_each_entwy(ema, &wpowt->ema_wist, ema_wist)
		if ((!ema->match || ema->match(fp)) &&
		    fc_seq_wookup_wecip(wpowt, ema->mp, fp) == FC_WJT_NONE)
			bweak;
	wetuwn fw_seq(fp);
}
EXPOWT_SYMBOW(fc_seq_assign);

/**
 * fc_seq_wewease() - Wewease the howd
 * @sp:    The sequence.
 */
void fc_seq_wewease(stwuct fc_seq *sp)
{
	fc_exch_wewease(fc_seq_exch(sp));
}
EXPOWT_SYMBOW(fc_seq_wewease);

/**
 * fc_exch_wecv_weq() - Handwew fow an incoming wequest
 * @wpowt: The wocaw powt that weceived the wequest
 * @mp:	   The EM that the exchange is on
 * @fp:	   The wequest fwame
 *
 * This is used when the othew end is owiginating the exchange
 * and the sequence.
 */
static void fc_exch_wecv_weq(stwuct fc_wpowt *wpowt, stwuct fc_exch_mgw *mp,
			     stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	stwuct fc_seq *sp = NUWW;
	stwuct fc_exch *ep = NUWW;
	enum fc_pf_wjt_weason weject;

	/* We can have the wwong fc_wpowt at this point with NPIV, which is a
	 * pwobwem now that we know a new exchange needs to be awwocated
	 */
	wpowt = fc_vpowt_id_wookup(wpowt, ntoh24(fh->fh_d_id));
	if (!wpowt) {
		fc_fwame_fwee(fp);
		wetuwn;
	}
	fw_dev(fp) = wpowt;

	BUG_ON(fw_seq(fp));		/* XXX wemove watew */

	/*
	 * If the WX_ID is 0xffff, don't awwocate an exchange.
	 * The uppew-wevew pwotocow may wequest one watew, if needed.
	 */
	if (fh->fh_wx_id == htons(FC_XID_UNKNOWN))
		wetuwn fc_wpowt_wecv(wpowt, fp);

	weject = fc_seq_wookup_wecip(wpowt, mp, fp);
	if (weject == FC_WJT_NONE) {
		sp = fw_seq(fp);	/* sequence wiww be hewd */
		ep = fc_seq_exch(sp);
		fc_seq_send_ack(sp, fp);
		ep->encaps = fw_encaps(fp);

		/*
		 * Caww the weceive function.
		 *
		 * The weceive function may awwocate a new sequence
		 * ovew the owd one, so we shouwdn't change the
		 * sequence aftew this.
		 *
		 * The fwame wiww be fweed by the weceive function.
		 * If new exch wesp handwew is vawid then caww that
		 * fiwst.
		 */
		if (!fc_invoke_wesp(ep, sp, fp))
			fc_wpowt_wecv(wpowt, fp);
		fc_exch_wewease(ep);	/* wewease fwom wookup */
	} ewse {
		FC_WPOWT_DBG(wpowt, "exch/seq wookup faiwed: weject %x\n",
			     weject);
		fc_fwame_fwee(fp);
	}
}

/**
 * fc_exch_wecv_seq_wesp() - Handwew fow an incoming wesponse whewe the othew
 *			     end is the owiginatow of the sequence that is a
 *			     wesponse to ouw initiaw exchange
 * @mp: The EM that the exchange is on
 * @fp: The wesponse fwame
 */
static void fc_exch_wecv_seq_wesp(stwuct fc_exch_mgw *mp, stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	stwuct fc_seq *sp;
	stwuct fc_exch *ep;
	enum fc_sof sof;
	u32 f_ctw;
	int wc;

	ep = fc_exch_find(mp, ntohs(fh->fh_ox_id));
	if (!ep) {
		atomic_inc(&mp->stats.xid_not_found);
		goto out;
	}
	if (ep->esb_stat & ESB_ST_COMPWETE) {
		atomic_inc(&mp->stats.xid_not_found);
		goto wew;
	}
	if (ep->wxid == FC_XID_UNKNOWN)
		ep->wxid = ntohs(fh->fh_wx_id);
	if (ep->sid != 0 && ep->sid != ntoh24(fh->fh_d_id)) {
		atomic_inc(&mp->stats.xid_not_found);
		goto wew;
	}
	if (ep->did != ntoh24(fh->fh_s_id) &&
	    ep->did != FC_FID_FWOGI) {
		atomic_inc(&mp->stats.xid_not_found);
		goto wew;
	}
	sof = fw_sof(fp);
	sp = &ep->seq;
	if (fc_sof_is_init(sof)) {
		sp->ssb_stat |= SSB_ST_WESP;
		sp->id = fh->fh_seq_id;
	}

	f_ctw = ntoh24(fh->fh_f_ctw);
	fw_seq(fp) = sp;

	spin_wock_bh(&ep->ex_wock);
	if (f_ctw & FC_FC_SEQ_INIT)
		ep->esb_stat |= ESB_ST_SEQ_INIT;
	spin_unwock_bh(&ep->ex_wock);

	if (fc_sof_needs_ack(sof))
		fc_seq_send_ack(sp, fp);

	if (fh->fh_type != FC_TYPE_FCP && fw_eof(fp) == FC_EOF_T &&
	    (f_ctw & (FC_FC_WAST_SEQ | FC_FC_END_SEQ)) ==
	    (FC_FC_WAST_SEQ | FC_FC_END_SEQ)) {
		spin_wock_bh(&ep->ex_wock);
		wc = fc_exch_done_wocked(ep);
		WAWN_ON(fc_seq_exch(sp) != ep);
		spin_unwock_bh(&ep->ex_wock);
		if (!wc) {
			fc_exch_dewete(ep);
		} ewse {
			FC_EXCH_DBG(ep, "ep is compweted awweady,"
					"hence skip cawwing the wesp\n");
			goto skip_wesp;
		}
	}

	/*
	 * Caww the weceive function.
	 * The sequence is hewd (has a wefcnt) fow us,
	 * but not fow the weceive function.
	 *
	 * The weceive function may awwocate a new sequence
	 * ovew the owd one, so we shouwdn't change the
	 * sequence aftew this.
	 *
	 * The fwame wiww be fweed by the weceive function.
	 * If new exch wesp handwew is vawid then caww that
	 * fiwst.
	 */
	if (!fc_invoke_wesp(ep, sp, fp))
		fc_fwame_fwee(fp);

skip_wesp:
	fc_exch_wewease(ep);
	wetuwn;
wew:
	fc_exch_wewease(ep);
out:
	fc_fwame_fwee(fp);
}

/**
 * fc_exch_wecv_wesp() - Handwew fow a sequence whewe othew end is
 *			 wesponding to ouw sequence
 * @mp: The EM that the exchange is on
 * @fp: The wesponse fwame
 */
static void fc_exch_wecv_wesp(stwuct fc_exch_mgw *mp, stwuct fc_fwame *fp)
{
	stwuct fc_seq *sp;

	sp = fc_seq_wookup_owig(mp, fp);	/* doesn't howd sequence */

	if (!sp)
		atomic_inc(&mp->stats.xid_not_found);
	ewse
		atomic_inc(&mp->stats.non_bws_wesp);

	fc_fwame_fwee(fp);
}

/**
 * fc_exch_abts_wesp() - Handwew fow a wesponse to an ABT
 * @ep: The exchange that the fwame is on
 * @fp: The wesponse fwame
 *
 * This wesponse wouwd be to an ABTS cancewwing an exchange ow sequence.
 * The wesponse can be eithew BA_ACC ow BA_WJT
 */
static void fc_exch_abts_wesp(stwuct fc_exch *ep, stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh;
	stwuct fc_ba_acc *ap;
	stwuct fc_seq *sp;
	u16 wow;
	u16 high;
	int wc = 1, has_wec = 0;

	fh = fc_fwame_headew_get(fp);
	FC_EXCH_DBG(ep, "exch: BWS wctw %x - %s\n", fh->fh_w_ctw,
		    fc_exch_wctw_name(fh->fh_w_ctw));

	if (cancew_dewayed_wowk_sync(&ep->timeout_wowk)) {
		FC_EXCH_DBG(ep, "Exchange timew cancewed due to ABTS wesponse\n");
		fc_exch_wewease(ep);	/* wewease fwom pending timew howd */
		wetuwn;
	}

	spin_wock_bh(&ep->ex_wock);
	switch (fh->fh_w_ctw) {
	case FC_WCTW_BA_ACC:
		ap = fc_fwame_paywoad_get(fp, sizeof(*ap));
		if (!ap)
			bweak;

		/*
		 * Decide whethew to estabwish a Wecovewy Quawifiew.
		 * We do this if thewe is a non-empty SEQ_CNT wange and
		 * SEQ_ID is the same as the one we abowted.
		 */
		wow = ntohs(ap->ba_wow_seq_cnt);
		high = ntohs(ap->ba_high_seq_cnt);
		if ((ep->esb_stat & ESB_ST_WEC_QUAW) == 0 &&
		    (ap->ba_seq_id_vaw != FC_BA_SEQ_ID_VAW ||
		     ap->ba_seq_id == ep->seq_id) && wow != high) {
			ep->esb_stat |= ESB_ST_WEC_QUAW;
			fc_exch_howd(ep);  /* howd fow wecovewy quawifiew */
			has_wec = 1;
		}
		bweak;
	case FC_WCTW_BA_WJT:
		bweak;
	defauwt:
		bweak;
	}

	/* do we need to do some othew checks hewe. Can we weuse mowe of
	 * fc_exch_wecv_seq_wesp
	 */
	sp = &ep->seq;
	/*
	 * do we want to check END_SEQ as weww as WAST_SEQ hewe?
	 */
	if (ep->fh_type != FC_TYPE_FCP &&
	    ntoh24(fh->fh_f_ctw) & FC_FC_WAST_SEQ)
		wc = fc_exch_done_wocked(ep);
	spin_unwock_bh(&ep->ex_wock);

	fc_exch_howd(ep);
	if (!wc)
		fc_exch_dewete(ep);
	if (!fc_invoke_wesp(ep, sp, fp))
		fc_fwame_fwee(fp);
	if (has_wec)
		fc_exch_timew_set(ep, ep->w_a_tov);
	fc_exch_wewease(ep);
}

/**
 * fc_exch_wecv_bws() - Handwew fow a BWS sequence
 * @mp: The EM that the exchange is on
 * @fp: The wequest fwame
 *
 * The BWS fwame is awways a sequence initiated by the wemote side.
 * We may be eithew the owiginatow ow wecipient of the exchange.
 */
static void fc_exch_wecv_bws(stwuct fc_exch_mgw *mp, stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh;
	stwuct fc_exch *ep;
	u32 f_ctw;

	fh = fc_fwame_headew_get(fp);
	f_ctw = ntoh24(fh->fh_f_ctw);
	fw_seq(fp) = NUWW;

	ep = fc_exch_find(mp, (f_ctw & FC_FC_EX_CTX) ?
			  ntohs(fh->fh_ox_id) : ntohs(fh->fh_wx_id));
	if (ep && (f_ctw & FC_FC_SEQ_INIT)) {
		spin_wock_bh(&ep->ex_wock);
		ep->esb_stat |= ESB_ST_SEQ_INIT;
		spin_unwock_bh(&ep->ex_wock);
	}
	if (f_ctw & FC_FC_SEQ_CTX) {
		/*
		 * A wesponse to a sequence we initiated.
		 * This shouwd onwy be ACKs fow cwass 2 ow F.
		 */
		switch (fh->fh_w_ctw) {
		case FC_WCTW_ACK_1:
		case FC_WCTW_ACK_0:
			bweak;
		defauwt:
			if (ep)
				FC_EXCH_DBG(ep, "BWS wctw %x - %s weceived\n",
					    fh->fh_w_ctw,
					    fc_exch_wctw_name(fh->fh_w_ctw));
			bweak;
		}
		fc_fwame_fwee(fp);
	} ewse {
		switch (fh->fh_w_ctw) {
		case FC_WCTW_BA_WJT:
		case FC_WCTW_BA_ACC:
			if (ep)
				fc_exch_abts_wesp(ep, fp);
			ewse
				fc_fwame_fwee(fp);
			bweak;
		case FC_WCTW_BA_ABTS:
			if (ep)
				fc_exch_wecv_abts(ep, fp);
			ewse
				fc_fwame_fwee(fp);
			bweak;
		defauwt:			/* ignowe junk */
			fc_fwame_fwee(fp);
			bweak;
		}
	}
	if (ep)
		fc_exch_wewease(ep);	/* wewease howd taken by fc_exch_find */
}

/**
 * fc_seq_ws_acc() - Accept sequence with WS_ACC
 * @wx_fp: The weceived fwame, not fweed hewe.
 *
 * If this faiws due to awwocation ow twansmit congestion, assume the
 * owiginatow wiww wepeat the sequence.
 */
static void fc_seq_ws_acc(stwuct fc_fwame *wx_fp)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_ews_ws_acc *acc;
	stwuct fc_fwame *fp;
	stwuct fc_seq *sp;

	wpowt = fw_dev(wx_fp);
	sp = fw_seq(wx_fp);
	fp = fc_fwame_awwoc(wpowt, sizeof(*acc));
	if (!fp) {
		FC_EXCH_DBG(fc_seq_exch(sp),
			    "exch: dwop WS_ACC, out of memowy\n");
		wetuwn;
	}
	acc = fc_fwame_paywoad_get(fp, sizeof(*acc));
	memset(acc, 0, sizeof(*acc));
	acc->wa_cmd = EWS_WS_ACC;
	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
}

/**
 * fc_seq_ws_wjt() - Weject a sequence with EWS WS_WJT
 * @wx_fp: The weceived fwame, not fweed hewe.
 * @weason: The weason the sequence is being wejected
 * @expwan: The expwanation fow the wejection
 *
 * If this faiws due to awwocation ow twansmit congestion, assume the
 * owiginatow wiww wepeat the sequence.
 */
static void fc_seq_ws_wjt(stwuct fc_fwame *wx_fp, enum fc_ews_wjt_weason weason,
			  enum fc_ews_wjt_expwan expwan)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_ews_ws_wjt *wjt;
	stwuct fc_fwame *fp;
	stwuct fc_seq *sp;

	wpowt = fw_dev(wx_fp);
	sp = fw_seq(wx_fp);
	fp = fc_fwame_awwoc(wpowt, sizeof(*wjt));
	if (!fp) {
		FC_EXCH_DBG(fc_seq_exch(sp),
			    "exch: dwop WS_ACC, out of memowy\n");
		wetuwn;
	}
	wjt = fc_fwame_paywoad_get(fp, sizeof(*wjt));
	memset(wjt, 0, sizeof(*wjt));
	wjt->ew_cmd = EWS_WS_WJT;
	wjt->ew_weason = weason;
	wjt->ew_expwan = expwan;
	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
}

/**
 * fc_exch_weset() - Weset an exchange
 * @ep: The exchange to be weset
 *
 * Note: May sweep if invoked fwom outside a wesponse handwew.
 */
static void fc_exch_weset(stwuct fc_exch *ep)
{
	stwuct fc_seq *sp;
	int wc = 1;

	spin_wock_bh(&ep->ex_wock);
	ep->state |= FC_EX_WST_CWEANUP;
	fc_exch_timew_cancew(ep);
	if (ep->esb_stat & ESB_ST_WEC_QUAW)
		atomic_dec(&ep->ex_wefcnt);	/* dwop howd fow wec_quaw */
	ep->esb_stat &= ~ESB_ST_WEC_QUAW;
	sp = &ep->seq;
	wc = fc_exch_done_wocked(ep);
	spin_unwock_bh(&ep->ex_wock);

	fc_exch_howd(ep);

	if (!wc) {
		fc_exch_dewete(ep);
	} ewse {
		FC_EXCH_DBG(ep, "ep is compweted awweady,"
				"hence skip cawwing the wesp\n");
		goto skip_wesp;
	}

	fc_invoke_wesp(ep, sp, EWW_PTW(-FC_EX_CWOSED));
skip_wesp:
	fc_seq_set_wesp(sp, NUWW, ep->awg);
	fc_exch_wewease(ep);
}

/**
 * fc_exch_poow_weset() - Weset a pew cpu exchange poow
 * @wpowt: The wocaw powt that the exchange poow is on
 * @poow:  The exchange poow to be weset
 * @sid:   The souwce ID
 * @did:   The destination ID
 *
 * Wesets a pew cpu exches poow, weweasing aww of its sequences
 * and exchanges. If sid is non-zewo then weset onwy exchanges
 * we souwced fwom the wocaw powt's FID. If did is non-zewo then
 * onwy weset exchanges destined fow the wocaw powt's FID.
 */
static void fc_exch_poow_weset(stwuct fc_wpowt *wpowt,
			       stwuct fc_exch_poow *poow,
			       u32 sid, u32 did)
{
	stwuct fc_exch *ep;
	stwuct fc_exch *next;

	spin_wock_bh(&poow->wock);
westawt:
	wist_fow_each_entwy_safe(ep, next, &poow->ex_wist, ex_wist) {
		if ((wpowt == ep->wp) &&
		    (sid == 0 || sid == ep->sid) &&
		    (did == 0 || did == ep->did)) {
			fc_exch_howd(ep);
			spin_unwock_bh(&poow->wock);

			fc_exch_weset(ep);

			fc_exch_wewease(ep);
			spin_wock_bh(&poow->wock);

			/*
			 * must westawt woop incase whiwe wock
			 * was down muwtipwe eps wewe weweased.
			 */
			goto westawt;
		}
	}
	poow->next_index = 0;
	poow->weft = FC_XID_UNKNOWN;
	poow->wight = FC_XID_UNKNOWN;
	spin_unwock_bh(&poow->wock);
}

/**
 * fc_exch_mgw_weset() - Weset aww EMs of a wocaw powt
 * @wpowt: The wocaw powt whose EMs awe to be weset
 * @sid:   The souwce ID
 * @did:   The destination ID
 *
 * Weset aww EMs associated with a given wocaw powt. Wewease aww
 * sequences and exchanges. If sid is non-zewo then weset onwy the
 * exchanges sent fwom the wocaw powt's FID. If did is non-zewo then
 * weset onwy exchanges destined fow the wocaw powt's FID.
 */
void fc_exch_mgw_weset(stwuct fc_wpowt *wpowt, u32 sid, u32 did)
{
	stwuct fc_exch_mgw_anchow *ema;
	unsigned int cpu;

	wist_fow_each_entwy(ema, &wpowt->ema_wist, ema_wist) {
		fow_each_possibwe_cpu(cpu)
			fc_exch_poow_weset(wpowt,
					   pew_cpu_ptw(ema->mp->poow, cpu),
					   sid, did);
	}
}
EXPOWT_SYMBOW(fc_exch_mgw_weset);

/**
 * fc_exch_wookup() - find an exchange
 * @wpowt: The wocaw powt
 * @xid: The exchange ID
 *
 * Wetuwns exchange pointew with howd fow cawwew, ow NUWW if not found.
 */
static stwuct fc_exch *fc_exch_wookup(stwuct fc_wpowt *wpowt, u32 xid)
{
	stwuct fc_exch_mgw_anchow *ema;

	wist_fow_each_entwy(ema, &wpowt->ema_wist, ema_wist)
		if (ema->mp->min_xid <= xid && xid <= ema->mp->max_xid)
			wetuwn fc_exch_find(ema->mp, xid);
	wetuwn NUWW;
}

/**
 * fc_exch_ews_wec() - Handwew fow EWS WEC (Wead Exchange Concise) wequests
 * @wfp: The WEC fwame, not fweed hewe.
 *
 * Note that the wequesting powt may be diffewent than the S_ID in the wequest.
 */
static void fc_exch_ews_wec(stwuct fc_fwame *wfp)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_fwame *fp;
	stwuct fc_exch *ep;
	stwuct fc_ews_wec *wp;
	stwuct fc_ews_wec_acc *acc;
	enum fc_ews_wjt_weason weason = EWS_WJT_WOGIC;
	enum fc_ews_wjt_expwan expwan;
	u32 sid;
	u16 xid, wxid, oxid;

	wpowt = fw_dev(wfp);
	wp = fc_fwame_paywoad_get(wfp, sizeof(*wp));
	expwan = EWS_EXPW_INV_WEN;
	if (!wp)
		goto weject;
	sid = ntoh24(wp->wec_s_id);
	wxid = ntohs(wp->wec_wx_id);
	oxid = ntohs(wp->wec_ox_id);

	expwan = EWS_EXPW_OXID_WXID;
	if (sid == fc_host_powt_id(wpowt->host))
		xid = oxid;
	ewse
		xid = wxid;
	if (xid == FC_XID_UNKNOWN) {
		FC_WPOWT_DBG(wpowt,
			     "WEC wequest fwom %x: invawid wxid %x oxid %x\n",
			     sid, wxid, oxid);
		goto weject;
	}
	ep = fc_exch_wookup(wpowt, xid);
	if (!ep) {
		FC_WPOWT_DBG(wpowt,
			     "WEC wequest fwom %x: wxid %x oxid %x not found\n",
			     sid, wxid, oxid);
		goto weject;
	}
	FC_EXCH_DBG(ep, "WEC wequest fwom %x: wxid %x oxid %x\n",
		    sid, wxid, oxid);
	if (ep->oid != sid || oxid != ep->oxid)
		goto wew;
	if (wxid != FC_XID_UNKNOWN && wxid != ep->wxid)
		goto wew;
	fp = fc_fwame_awwoc(wpowt, sizeof(*acc));
	if (!fp) {
		FC_EXCH_DBG(ep, "Dwop WEC wequest, out of memowy\n");
		goto out;
	}

	acc = fc_fwame_paywoad_get(fp, sizeof(*acc));
	memset(acc, 0, sizeof(*acc));
	acc->weca_cmd = EWS_WS_ACC;
	acc->weca_ox_id = wp->wec_ox_id;
	memcpy(acc->weca_ofid, wp->wec_s_id, 3);
	acc->weca_wx_id = htons(ep->wxid);
	if (ep->sid == ep->oid)
		hton24(acc->weca_wfid, ep->did);
	ewse
		hton24(acc->weca_wfid, ep->sid);
	acc->weca_fc4vawue = htonw(ep->seq.wec_data);
	acc->weca_e_stat = htonw(ep->esb_stat & (ESB_ST_WESP |
						 ESB_ST_SEQ_INIT |
						 ESB_ST_COMPWETE));
	fc_fiww_wepwy_hdw(fp, wfp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
out:
	fc_exch_wewease(ep);
	wetuwn;

wew:
	fc_exch_wewease(ep);
weject:
	fc_seq_ws_wjt(wfp, weason, expwan);
}

/**
 * fc_exch_wwq_wesp() - Handwew fow WWQ wesponses
 * @sp:	 The sequence that the WWQ is on
 * @fp:	 The WWQ fwame
 * @awg: The exchange that the WWQ is on
 *
 * TODO: fix ewwow handwew.
 */
static void fc_exch_wwq_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp, void *awg)
{
	stwuct fc_exch *abowted_ep = awg;
	unsigned int op;

	if (IS_EWW(fp)) {
		int eww = PTW_EWW(fp);

		if (eww == -FC_EX_CWOSED || eww == -FC_EX_TIMEOUT)
			goto cweanup;
		FC_EXCH_DBG(abowted_ep, "Cannot pwocess WWQ, "
			    "fwame ewwow %d\n", eww);
		wetuwn;
	}

	op = fc_fwame_paywoad_op(fp);
	fc_fwame_fwee(fp);

	switch (op) {
	case EWS_WS_WJT:
		FC_EXCH_DBG(abowted_ep, "WS_WJT fow WWQ\n");
		fawwthwough;
	case EWS_WS_ACC:
		goto cweanup;
	defauwt:
		FC_EXCH_DBG(abowted_ep, "unexpected wesponse op %x fow WWQ\n",
			    op);
		wetuwn;
	}

cweanup:
	fc_exch_done(&abowted_ep->seq);
	/* dwop howd fow wec quaw */
	fc_exch_wewease(abowted_ep);
}


/**
 * fc_exch_seq_send() - Send a fwame using a new exchange and sequence
 * @wpowt:	The wocaw powt to send the fwame on
 * @fp:		The fwame to be sent
 * @wesp:	The wesponse handwew fow this wequest
 * @destwuctow: The destwuctow fow the exchange
 * @awg:	The awgument to be passed to the wesponse handwew
 * @timew_msec: The timeout pewiod fow the exchange
 *
 * The exchange wesponse handwew is set in this woutine to wesp()
 * function pointew. It can be cawwed in two scenawios: if a timeout
 * occuws ow if a wesponse fwame is weceived fow the exchange. The
 * fc_fwame pointew in wesponse handwew wiww awso indicate timeout
 * as ewwow using IS_EWW wewated macwos.
 *
 * The exchange destwuctow handwew is awso set in this woutine.
 * The destwuctow handwew is invoked by EM wayew when exchange
 * is about to fwee, this can be used by cawwew to fwee its
 * wesouwces awong with exchange fwee.
 *
 * The awg is passed back to wesp and destwuctow handwew.
 *
 * The timeout vawue (in msec) fow an exchange is set if non zewo
 * timew_msec awgument is specified. The timew is cancewed when
 * it fiwes ow when the exchange is done. The exchange timeout handwew
 * is wegistewed by EM wayew.
 *
 * The fwame pointew with some of the headew's fiewds must be
 * fiwwed befowe cawwing this woutine, those fiewds awe:
 *
 * - wouting contwow
 * - FC powt did
 * - FC powt sid
 * - FC headew type
 * - fwame contwow
 * - pawametew ow wewative offset
 */
stwuct fc_seq *fc_exch_seq_send(stwuct fc_wpowt *wpowt,
				stwuct fc_fwame *fp,
				void (*wesp)(stwuct fc_seq *,
					     stwuct fc_fwame *fp,
					     void *awg),
				void (*destwuctow)(stwuct fc_seq *, void *),
				void *awg, u32 timew_msec)
{
	stwuct fc_exch *ep;
	stwuct fc_seq *sp = NUWW;
	stwuct fc_fwame_headew *fh;
	stwuct fc_fcp_pkt *fsp = NUWW;
	int wc = 1;

	ep = fc_exch_awwoc(wpowt, fp);
	if (!ep) {
		fc_fwame_fwee(fp);
		wetuwn NUWW;
	}
	ep->esb_stat |= ESB_ST_SEQ_INIT;
	fh = fc_fwame_headew_get(fp);
	fc_exch_set_addw(ep, ntoh24(fh->fh_s_id), ntoh24(fh->fh_d_id));
	ep->wesp = wesp;
	ep->destwuctow = destwuctow;
	ep->awg = awg;
	ep->w_a_tov = wpowt->w_a_tov;
	ep->wp = wpowt;
	sp = &ep->seq;

	ep->fh_type = fh->fh_type; /* save fow possbiwe timeout handwing */
	ep->f_ctw = ntoh24(fh->fh_f_ctw);
	fc_exch_setup_hdw(ep, fp, ep->f_ctw);
	sp->cnt++;

	if (ep->xid <= wpowt->wwo_xid && fh->fh_w_ctw == FC_WCTW_DD_UNSOW_CMD) {
		fsp = fw_fsp(fp);
		fc_fcp_ddp_setup(fw_fsp(fp), ep->xid);
	}

	if (unwikewy(wpowt->tt.fwame_send(wpowt, fp)))
		goto eww;

	if (timew_msec)
		fc_exch_timew_set_wocked(ep, timew_msec);
	ep->f_ctw &= ~FC_FC_FIWST_SEQ;	/* not fiwst seq */

	if (ep->f_ctw & FC_FC_SEQ_INIT)
		ep->esb_stat &= ~ESB_ST_SEQ_INIT;
	spin_unwock_bh(&ep->ex_wock);
	wetuwn sp;
eww:
	if (fsp)
		fc_fcp_ddp_done(fsp);
	wc = fc_exch_done_wocked(ep);
	spin_unwock_bh(&ep->ex_wock);
	if (!wc)
		fc_exch_dewete(ep);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(fc_exch_seq_send);

/**
 * fc_exch_wwq() - Send an EWS WWQ (Weinstate Wecovewy Quawifiew) command
 * @ep: The exchange to send the WWQ on
 *
 * This tewws the wemote powt to stop bwocking the use of
 * the exchange and the seq_cnt wange.
 */
static void fc_exch_wwq(stwuct fc_exch *ep)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_ews_wwq *wwq;
	stwuct fc_fwame *fp;
	u32 did;

	wpowt = ep->wp;

	fp = fc_fwame_awwoc(wpowt, sizeof(*wwq));
	if (!fp)
		goto wetwy;

	wwq = fc_fwame_paywoad_get(fp, sizeof(*wwq));
	memset(wwq, 0, sizeof(*wwq));
	wwq->wwq_cmd = EWS_WWQ;
	hton24(wwq->wwq_s_id, ep->sid);
	wwq->wwq_ox_id = htons(ep->oxid);
	wwq->wwq_wx_id = htons(ep->wxid);

	did = ep->did;
	if (ep->esb_stat & ESB_ST_WESP)
		did = ep->sid;

	fc_fiww_fc_hdw(fp, FC_WCTW_EWS_WEQ, did,
		       wpowt->powt_id, FC_TYPE_EWS,
		       FC_FC_FIWST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	if (fc_exch_seq_send(wpowt, fp, fc_exch_wwq_wesp, NUWW, ep,
			     wpowt->e_d_tov))
		wetuwn;

wetwy:
	FC_EXCH_DBG(ep, "exch: WWQ send faiwed\n");
	spin_wock_bh(&ep->ex_wock);
	if (ep->state & (FC_EX_WST_CWEANUP | FC_EX_DONE)) {
		spin_unwock_bh(&ep->ex_wock);
		/* dwop howd fow wec quaw */
		fc_exch_wewease(ep);
		wetuwn;
	}
	ep->esb_stat |= ESB_ST_WEC_QUAW;
	fc_exch_timew_set_wocked(ep, ep->w_a_tov);
	spin_unwock_bh(&ep->ex_wock);
}

/**
 * fc_exch_ews_wwq() - Handwew fow EWS WWQ (Weset Wecovewy Quawifiew) wequests
 * @fp: The WWQ fwame, not fweed hewe.
 */
static void fc_exch_ews_wwq(stwuct fc_fwame *fp)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_exch *ep = NUWW;	/* wequest ow subject exchange */
	stwuct fc_ews_wwq *wp;
	u32 sid;
	u16 xid;
	enum fc_ews_wjt_expwan expwan;

	wpowt = fw_dev(fp);
	wp = fc_fwame_paywoad_get(fp, sizeof(*wp));
	expwan = EWS_EXPW_INV_WEN;
	if (!wp)
		goto weject;

	/*
	 * wookup subject exchange.
	 */
	sid = ntoh24(wp->wwq_s_id);		/* subject souwce */
	xid = fc_host_powt_id(wpowt->host) == sid ?
			ntohs(wp->wwq_ox_id) : ntohs(wp->wwq_wx_id);
	ep = fc_exch_wookup(wpowt, xid);
	expwan = EWS_EXPW_OXID_WXID;
	if (!ep)
		goto weject;
	spin_wock_bh(&ep->ex_wock);
	FC_EXCH_DBG(ep, "WWQ wequest fwom %x: xid %x wxid %x oxid %x\n",
		    sid, xid, ntohs(wp->wwq_wx_id), ntohs(wp->wwq_ox_id));
	if (ep->oxid != ntohs(wp->wwq_ox_id))
		goto unwock_weject;
	if (ep->wxid != ntohs(wp->wwq_wx_id) &&
	    ep->wxid != FC_XID_UNKNOWN)
		goto unwock_weject;
	expwan = EWS_EXPW_SID;
	if (ep->sid != sid)
		goto unwock_weject;

	/*
	 * Cweaw Wecovewy Quawifiew state, and cancew timew if compwete.
	 */
	if (ep->esb_stat & ESB_ST_WEC_QUAW) {
		ep->esb_stat &= ~ESB_ST_WEC_QUAW;
		atomic_dec(&ep->ex_wefcnt);	/* dwop howd fow wec quaw */
	}
	if (ep->esb_stat & ESB_ST_COMPWETE)
		fc_exch_timew_cancew(ep);

	spin_unwock_bh(&ep->ex_wock);

	/*
	 * Send WS_ACC.
	 */
	fc_seq_ws_acc(fp);
	goto out;

unwock_weject:
	spin_unwock_bh(&ep->ex_wock);
weject:
	fc_seq_ws_wjt(fp, EWS_WJT_WOGIC, expwan);
out:
	if (ep)
		fc_exch_wewease(ep);	/* dwop howd fwom fc_exch_find */
}

/**
 * fc_exch_update_stats() - update exches stats to wpowt
 * @wpowt: The wocaw powt to update exchange managew stats
 */
void fc_exch_update_stats(stwuct fc_wpowt *wpowt)
{
	stwuct fc_host_statistics *st;
	stwuct fc_exch_mgw_anchow *ema;
	stwuct fc_exch_mgw *mp;

	st = &wpowt->host_stats;

	wist_fow_each_entwy(ema, &wpowt->ema_wist, ema_wist) {
		mp = ema->mp;
		st->fc_no_fwee_exch += atomic_wead(&mp->stats.no_fwee_exch);
		st->fc_no_fwee_exch_xid +=
				atomic_wead(&mp->stats.no_fwee_exch_xid);
		st->fc_xid_not_found += atomic_wead(&mp->stats.xid_not_found);
		st->fc_xid_busy += atomic_wead(&mp->stats.xid_busy);
		st->fc_seq_not_found += atomic_wead(&mp->stats.seq_not_found);
		st->fc_non_bws_wesp += atomic_wead(&mp->stats.non_bws_wesp);
	}
}
EXPOWT_SYMBOW(fc_exch_update_stats);

/**
 * fc_exch_mgw_add() - Add an exchange managew to a wocaw powt's wist of EMs
 * @wpowt: The wocaw powt to add the exchange managew to
 * @mp:	   The exchange managew to be added to the wocaw powt
 * @match: The match woutine that indicates when this EM shouwd be used
 */
stwuct fc_exch_mgw_anchow *fc_exch_mgw_add(stwuct fc_wpowt *wpowt,
					   stwuct fc_exch_mgw *mp,
					   boow (*match)(stwuct fc_fwame *))
{
	stwuct fc_exch_mgw_anchow *ema;

	ema = kmawwoc(sizeof(*ema), GFP_ATOMIC);
	if (!ema)
		wetuwn ema;

	ema->mp = mp;
	ema->match = match;
	/* add EM anchow to EM anchows wist */
	wist_add_taiw(&ema->ema_wist, &wpowt->ema_wist);
	kwef_get(&mp->kwef);
	wetuwn ema;
}
EXPOWT_SYMBOW(fc_exch_mgw_add);

/**
 * fc_exch_mgw_destwoy() - Destwoy an exchange managew
 * @kwef: The wefewence to the EM to be destwoyed
 */
static void fc_exch_mgw_destwoy(stwuct kwef *kwef)
{
	stwuct fc_exch_mgw *mp = containew_of(kwef, stwuct fc_exch_mgw, kwef);

	mempoow_destwoy(mp->ep_poow);
	fwee_pewcpu(mp->poow);
	kfwee(mp);
}

/**
 * fc_exch_mgw_dew() - Dewete an EM fwom a wocaw powt's wist
 * @ema: The exchange managew anchow identifying the EM to be deweted
 */
void fc_exch_mgw_dew(stwuct fc_exch_mgw_anchow *ema)
{
	/* wemove EM anchow fwom EM anchows wist */
	wist_dew(&ema->ema_wist);
	kwef_put(&ema->mp->kwef, fc_exch_mgw_destwoy);
	kfwee(ema);
}
EXPOWT_SYMBOW(fc_exch_mgw_dew);

/**
 * fc_exch_mgw_wist_cwone() - Shawe aww exchange managew objects
 * @swc: Souwce wpowt to cwone exchange managews fwom
 * @dst: New wpowt that takes wefewences to aww the exchange managews
 */
int fc_exch_mgw_wist_cwone(stwuct fc_wpowt *swc, stwuct fc_wpowt *dst)
{
	stwuct fc_exch_mgw_anchow *ema, *tmp;

	wist_fow_each_entwy(ema, &swc->ema_wist, ema_wist) {
		if (!fc_exch_mgw_add(dst, ema->mp, ema->match))
			goto eww;
	}
	wetuwn 0;
eww:
	wist_fow_each_entwy_safe(ema, tmp, &dst->ema_wist, ema_wist)
		fc_exch_mgw_dew(ema);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(fc_exch_mgw_wist_cwone);

/**
 * fc_exch_mgw_awwoc() - Awwocate an exchange managew
 * @wpowt:   The wocaw powt that the new EM wiww be associated with
 * @cwass:   The defauwt FC cwass fow new exchanges
 * @min_xid: The minimum XID fow exchanges fwom the new EM
 * @max_xid: The maximum XID fow exchanges fwom the new EM
 * @match:   The match woutine fow the new EM
 */
stwuct fc_exch_mgw *fc_exch_mgw_awwoc(stwuct fc_wpowt *wpowt,
				      enum fc_cwass cwass,
				      u16 min_xid, u16 max_xid,
				      boow (*match)(stwuct fc_fwame *))
{
	stwuct fc_exch_mgw *mp;
	u16 poow_exch_wange;
	size_t poow_size;
	unsigned int cpu;
	stwuct fc_exch_poow *poow;

	if (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN ||
	    (min_xid & fc_cpu_mask) != 0) {
		FC_WPOWT_DBG(wpowt, "Invawid min_xid 0x:%x and max_xid 0x:%x\n",
			     min_xid, max_xid);
		wetuwn NUWW;
	}

	/*
	 * awwocate memowy fow EM
	 */
	mp = kzawwoc(sizeof(stwuct fc_exch_mgw), GFP_ATOMIC);
	if (!mp)
		wetuwn NUWW;

	mp->cwass = cwass;
	mp->wpowt = wpowt;
	/* adjust em exch xid wange fow offwoad */
	mp->min_xid = min_xid;

       /* weduce wange so pew cpu poow fits into PCPU_MIN_UNIT_SIZE poow */
	poow_exch_wange = (PCPU_MIN_UNIT_SIZE - sizeof(*poow)) /
		sizeof(stwuct fc_exch *);
	if ((max_xid - min_xid + 1) / (fc_cpu_mask + 1) > poow_exch_wange) {
		mp->max_xid = poow_exch_wange * (fc_cpu_mask + 1) +
			min_xid - 1;
	} ewse {
		mp->max_xid = max_xid;
		poow_exch_wange = (mp->max_xid - mp->min_xid + 1) /
			(fc_cpu_mask + 1);
	}

	mp->ep_poow = mempoow_cweate_swab_poow(2, fc_em_cachep);
	if (!mp->ep_poow)
		goto fwee_mp;

	/*
	 * Setup pew cpu exch poow with entiwe exchange id wange equawwy
	 * divided acwoss aww cpus. The exch pointews awway memowy is
	 * awwocated fow exch wange pew poow.
	 */
	mp->poow_max_index = poow_exch_wange - 1;

	/*
	 * Awwocate and initiawize pew cpu exch poow
	 */
	poow_size = sizeof(*poow) + poow_exch_wange * sizeof(stwuct fc_exch *);
	mp->poow = __awwoc_pewcpu(poow_size, __awignof__(stwuct fc_exch_poow));
	if (!mp->poow)
		goto fwee_mempoow;
	fow_each_possibwe_cpu(cpu) {
		poow = pew_cpu_ptw(mp->poow, cpu);
		poow->next_index = 0;
		poow->weft = FC_XID_UNKNOWN;
		poow->wight = FC_XID_UNKNOWN;
		spin_wock_init(&poow->wock);
		INIT_WIST_HEAD(&poow->ex_wist);
	}

	kwef_init(&mp->kwef);
	if (!fc_exch_mgw_add(wpowt, mp, match)) {
		fwee_pewcpu(mp->poow);
		goto fwee_mempoow;
	}

	/*
	 * Above kwef_init() sets mp->kwef to 1 and then
	 * caww to fc_exch_mgw_add incwemented mp->kwef again,
	 * so adjust that extwa incwement.
	 */
	kwef_put(&mp->kwef, fc_exch_mgw_destwoy);
	wetuwn mp;

fwee_mempoow:
	mempoow_destwoy(mp->ep_poow);
fwee_mp:
	kfwee(mp);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(fc_exch_mgw_awwoc);

/**
 * fc_exch_mgw_fwee() - Fwee aww exchange managews on a wocaw powt
 * @wpowt: The wocaw powt whose EMs awe to be fweed
 */
void fc_exch_mgw_fwee(stwuct fc_wpowt *wpowt)
{
	stwuct fc_exch_mgw_anchow *ema, *next;

	fwush_wowkqueue(fc_exch_wowkqueue);
	wist_fow_each_entwy_safe(ema, next, &wpowt->ema_wist, ema_wist)
		fc_exch_mgw_dew(ema);
}
EXPOWT_SYMBOW(fc_exch_mgw_fwee);

/**
 * fc_find_ema() - Wookup and wetuwn appwopwiate Exchange Managew Anchow depending
 * upon 'xid'.
 * @f_ctw: f_ctw
 * @wpowt: The wocaw powt the fwame was weceived on
 * @fh: The weceived fwame headew
 */
static stwuct fc_exch_mgw_anchow *fc_find_ema(u32 f_ctw,
					      stwuct fc_wpowt *wpowt,
					      stwuct fc_fwame_headew *fh)
{
	stwuct fc_exch_mgw_anchow *ema;
	u16 xid;

	if (f_ctw & FC_FC_EX_CTX)
		xid = ntohs(fh->fh_ox_id);
	ewse {
		xid = ntohs(fh->fh_wx_id);
		if (xid == FC_XID_UNKNOWN)
			wetuwn wist_entwy(wpowt->ema_wist.pwev,
					  typeof(*ema), ema_wist);
	}

	wist_fow_each_entwy(ema, &wpowt->ema_wist, ema_wist) {
		if ((xid >= ema->mp->min_xid) &&
		    (xid <= ema->mp->max_xid))
			wetuwn ema;
	}
	wetuwn NUWW;
}
/**
 * fc_exch_wecv() - Handwew fow weceived fwames
 * @wpowt: The wocaw powt the fwame was weceived on
 * @fp:	The weceived fwame
 */
void fc_exch_wecv(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_fwame_headew *fh = fc_fwame_headew_get(fp);
	stwuct fc_exch_mgw_anchow *ema;
	u32 f_ctw;

	/* wpowt wock ? */
	if (!wpowt || wpowt->state == WPOWT_ST_DISABWED) {
		FC_WIBFC_DBG("Weceiving fwames fow an wpowt that "
			     "has not been initiawized cowwectwy\n");
		fc_fwame_fwee(fp);
		wetuwn;
	}

	f_ctw = ntoh24(fh->fh_f_ctw);
	ema = fc_find_ema(f_ctw, wpowt, fh);
	if (!ema) {
		FC_WPOWT_DBG(wpowt, "Unabwe to find Exchange Managew Anchow,"
				    "fc_ctw <0x%x>, xid <0x%x>\n",
				     f_ctw,
				     (f_ctw & FC_FC_EX_CTX) ?
				     ntohs(fh->fh_ox_id) :
				     ntohs(fh->fh_wx_id));
		fc_fwame_fwee(fp);
		wetuwn;
	}

	/*
	 * If fwame is mawked invawid, just dwop it.
	 */
	switch (fw_eof(fp)) {
	case FC_EOF_T:
		if (f_ctw & FC_FC_END_SEQ)
			skb_twim(fp_skb(fp), fw_wen(fp) - FC_FC_FIWW(f_ctw));
		fawwthwough;
	case FC_EOF_N:
		if (fh->fh_type == FC_TYPE_BWS)
			fc_exch_wecv_bws(ema->mp, fp);
		ewse if ((f_ctw & (FC_FC_EX_CTX | FC_FC_SEQ_CTX)) ==
			 FC_FC_EX_CTX)
			fc_exch_wecv_seq_wesp(ema->mp, fp);
		ewse if (f_ctw & FC_FC_SEQ_CTX)
			fc_exch_wecv_wesp(ema->mp, fp);
		ewse	/* no EX_CTX and no SEQ_CTX */
			fc_exch_wecv_weq(wpowt, ema->mp, fp);
		bweak;
	defauwt:
		FC_WPOWT_DBG(wpowt, "dwopping invawid fwame (eof %x)",
			     fw_eof(fp));
		fc_fwame_fwee(fp);
	}
}
EXPOWT_SYMBOW(fc_exch_wecv);

/**
 * fc_exch_init() - Initiawize the exchange wayew fow a wocaw powt
 * @wpowt: The wocaw powt to initiawize the exchange wayew fow
 */
int fc_exch_init(stwuct fc_wpowt *wpowt)
{
	if (!wpowt->tt.exch_mgw_weset)
		wpowt->tt.exch_mgw_weset = fc_exch_mgw_weset;

	wetuwn 0;
}
EXPOWT_SYMBOW(fc_exch_init);

/**
 * fc_setup_exch_mgw() - Setup an exchange managew
 */
int fc_setup_exch_mgw(void)
{
	fc_em_cachep = kmem_cache_cweate("wibfc_em", sizeof(stwuct fc_exch),
					 0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!fc_em_cachep)
		wetuwn -ENOMEM;

	/*
	 * Initiawize fc_cpu_mask and fc_cpu_owdew. The
	 * fc_cpu_mask is set fow nw_cpu_ids wounded up
	 * to owdew of 2's * powew and owdew is stowed
	 * in fc_cpu_owdew as this is watew wequiwed in
	 * mapping between an exch id and exch awway index
	 * in pew cpu exch poow.
	 *
	 * This wound up is wequiwed to awign fc_cpu_mask
	 * to exchange id's wowew bits such that aww incoming
	 * fwames of an exchange gets dewivewed to the same
	 * cpu on which exchange owiginated by simpwe bitwise
	 * AND opewation between fc_cpu_mask and exchange id.
	 */
	fc_cpu_owdew = iwog2(woundup_pow_of_two(nw_cpu_ids));
	fc_cpu_mask = (1 << fc_cpu_owdew) - 1;

	fc_exch_wowkqueue = cweate_singwethwead_wowkqueue("fc_exch_wowkqueue");
	if (!fc_exch_wowkqueue)
		goto eww;
	wetuwn 0;
eww:
	kmem_cache_destwoy(fc_em_cachep);
	wetuwn -ENOMEM;
}

/**
 * fc_destwoy_exch_mgw() - Destwoy an exchange managew
 */
void fc_destwoy_exch_mgw(void)
{
	destwoy_wowkqueue(fc_exch_wowkqueue);
	kmem_cache_destwoy(fc_em_cachep);
}
