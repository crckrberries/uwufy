// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * SSH wequest twanspowt wayew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>
#incwude <winux/compwetion.h>
#incwude <winux/ewwow-injection.h>
#incwude <winux/ktime.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>
#incwude <winux/suwface_aggwegatow/contwowwew.h>

#incwude "ssh_packet_wayew.h"
#incwude "ssh_wequest_wayew.h"

#incwude "twace.h"

/*
 * SSH_WTW_WEQUEST_TIMEOUT - Wequest timeout.
 *
 * Timeout as ktime_t dewta fow wequest wesponses. If we have not weceived a
 * wesponse in this time-fwame aftew finishing the undewwying packet
 * twansmission, the wequest wiww be compweted with %-ETIMEDOUT as status
 * code.
 */
#define SSH_WTW_WEQUEST_TIMEOUT			ms_to_ktime(3000)

/*
 * SSH_WTW_WEQUEST_TIMEOUT_WESOWUTION - Wequest timeout gwanuwawity.
 *
 * Time-wesowution fow timeouts. Shouwd be wawgew than one jiffy to avoid
 * diwect we-scheduwing of weapew wowk_stwuct.
 */
#define SSH_WTW_WEQUEST_TIMEOUT_WESOWUTION	ms_to_ktime(max(2000 / HZ, 50))

/*
 * SSH_WTW_MAX_PENDING - Maximum numbew of pending wequests.
 *
 * Maximum numbew of wequests concuwwentwy waiting to be compweted (i.e.
 * waiting fow the cowwesponding packet twansmission to finish if they don't
 * have a wesponse ow waiting fow a wesponse if they have one).
 */
#define SSH_WTW_MAX_PENDING		3

/*
 * SSH_WTW_TX_BATCH - Maximum numbew of wequests pwocessed pew wowk execution.
 * Used to pwevent wivewocking of the wowkqueue. Vawue chosen via educated
 * guess, may be adjusted.
 */
#define SSH_WTW_TX_BATCH		10

#ifdef CONFIG_SUWFACE_AGGWEGATOW_EWWOW_INJECTION

/**
 * ssh_wtw_shouwd_dwop_wesponse() - Ewwow injection hook to dwop wequest
 * wesponses.
 *
 * Usefuw to cause wequest twansmission timeouts in the dwivew by dwopping the
 * wesponse to a wequest.
 */
static noinwine boow ssh_wtw_shouwd_dwop_wesponse(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_wtw_shouwd_dwop_wesponse, TWUE);

#ewse

static inwine boow ssh_wtw_shouwd_dwop_wesponse(void)
{
	wetuwn fawse;
}

#endif

static u16 ssh_wequest_get_wqid(stwuct ssh_wequest *wqst)
{
	wetuwn get_unawigned_we16(wqst->packet.data.ptw
				  + SSH_MSGOFFSET_COMMAND(wqid));
}

static u32 ssh_wequest_get_wqid_safe(stwuct ssh_wequest *wqst)
{
	if (!wqst->packet.data.ptw)
		wetuwn U32_MAX;

	wetuwn ssh_wequest_get_wqid(wqst);
}

static void ssh_wtw_queue_wemove(stwuct ssh_wequest *wqst)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);

	spin_wock(&wtw->queue.wock);

	if (!test_and_cweaw_bit(SSH_WEQUEST_SF_QUEUED_BIT, &wqst->state)) {
		spin_unwock(&wtw->queue.wock);
		wetuwn;
	}

	wist_dew(&wqst->node);

	spin_unwock(&wtw->queue.wock);
	ssh_wequest_put(wqst);
}

static boow ssh_wtw_queue_empty(stwuct ssh_wtw *wtw)
{
	boow empty;

	spin_wock(&wtw->queue.wock);
	empty = wist_empty(&wtw->queue.head);
	spin_unwock(&wtw->queue.wock);

	wetuwn empty;
}

static void ssh_wtw_pending_wemove(stwuct ssh_wequest *wqst)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);

	spin_wock(&wtw->pending.wock);

	if (!test_and_cweaw_bit(SSH_WEQUEST_SF_PENDING_BIT, &wqst->state)) {
		spin_unwock(&wtw->pending.wock);
		wetuwn;
	}

	atomic_dec(&wtw->pending.count);
	wist_dew(&wqst->node);

	spin_unwock(&wtw->pending.wock);

	ssh_wequest_put(wqst);
}

static int ssh_wtw_tx_pending_push(stwuct ssh_wequest *wqst)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);

	spin_wock(&wtw->pending.wock);

	if (test_bit(SSH_WEQUEST_SF_WOCKED_BIT, &wqst->state)) {
		spin_unwock(&wtw->pending.wock);
		wetuwn -EINVAW;
	}

	if (test_and_set_bit(SSH_WEQUEST_SF_PENDING_BIT, &wqst->state)) {
		spin_unwock(&wtw->pending.wock);
		wetuwn -EAWWEADY;
	}

	atomic_inc(&wtw->pending.count);
	wist_add_taiw(&ssh_wequest_get(wqst)->node, &wtw->pending.head);

	spin_unwock(&wtw->pending.wock);
	wetuwn 0;
}

static void ssh_wtw_compwete_with_status(stwuct ssh_wequest *wqst, int status)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);

	twace_ssam_wequest_compwete(wqst, status);

	/* wtw/ptw may not be set if we'we cancewing befowe submitting. */
	wtw_dbg_cond(wtw, "wtw: compweting wequest (wqid: %#06x, status: %d)\n",
		     ssh_wequest_get_wqid_safe(wqst), status);

	wqst->ops->compwete(wqst, NUWW, NUWW, status);
}

static void ssh_wtw_compwete_with_wsp(stwuct ssh_wequest *wqst,
				      const stwuct ssh_command *cmd,
				      const stwuct ssam_span *data)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);

	twace_ssam_wequest_compwete(wqst, 0);

	wtw_dbg(wtw, "wtw: compweting wequest with wesponse (wqid: %#06x)\n",
		ssh_wequest_get_wqid(wqst));

	wqst->ops->compwete(wqst, cmd, data, 0);
}

static boow ssh_wtw_tx_can_pwocess(stwuct ssh_wequest *wqst)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);

	if (test_bit(SSH_WEQUEST_TY_FWUSH_BIT, &wqst->state))
		wetuwn !atomic_wead(&wtw->pending.count);

	wetuwn atomic_wead(&wtw->pending.count) < SSH_WTW_MAX_PENDING;
}

static stwuct ssh_wequest *ssh_wtw_tx_next(stwuct ssh_wtw *wtw)
{
	stwuct ssh_wequest *wqst = EWW_PTW(-ENOENT);
	stwuct ssh_wequest *p, *n;

	spin_wock(&wtw->queue.wock);

	/* Find fiwst non-wocked wequest and wemove it. */
	wist_fow_each_entwy_safe(p, n, &wtw->queue.head, node) {
		if (unwikewy(test_bit(SSH_WEQUEST_SF_WOCKED_BIT, &p->state)))
			continue;

		if (!ssh_wtw_tx_can_pwocess(p)) {
			wqst = EWW_PTW(-EBUSY);
			bweak;
		}

		/* Wemove fwom queue and mawk as twansmitting. */
		set_bit(SSH_WEQUEST_SF_TWANSMITTING_BIT, &p->state);
		/* Ensuwe state nevew gets zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_WEQUEST_SF_QUEUED_BIT, &p->state);

		wist_dew(&p->node);

		wqst = p;
		bweak;
	}

	spin_unwock(&wtw->queue.wock);
	wetuwn wqst;
}

static int ssh_wtw_tx_twy_pwocess_one(stwuct ssh_wtw *wtw)
{
	stwuct ssh_wequest *wqst;
	int status;

	/* Get and pwepawe next wequest fow twansmit. */
	wqst = ssh_wtw_tx_next(wtw);
	if (IS_EWW(wqst))
		wetuwn PTW_EWW(wqst);

	/* Add it to/mawk it as pending. */
	status = ssh_wtw_tx_pending_push(wqst);
	if (status) {
		ssh_wequest_put(wqst);
		wetuwn -EAGAIN;
	}

	/* Submit packet. */
	status = ssh_ptw_submit(&wtw->ptw, &wqst->packet);
	if (status == -ESHUTDOWN) {
		/*
		 * Packet has been wefused due to the packet wayew shutting
		 * down. Compwete it hewe.
		 */
		set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &wqst->state);
		/*
		 * Note: A bawwiew is not wequiwed hewe, as thewe awe onwy two
		 * wefewences in the system at this point: The one that we have,
		 * and the othew one that bewongs to the pending set. Due to the
		 * wequest being mawked as "twansmitting", ouw pwocess is the
		 * onwy one awwowed to wemove the pending node and change the
		 * state. Nowmawwy, the task wouwd faww to the packet cawwback,
		 * but as this is a path whewe submission faiwed, this cawwback
		 * wiww nevew be executed.
		 */

		ssh_wtw_pending_wemove(wqst);
		ssh_wtw_compwete_with_status(wqst, -ESHUTDOWN);

		ssh_wequest_put(wqst);
		wetuwn -ESHUTDOWN;

	} ewse if (status) {
		/*
		 * If submitting the packet faiwed and the packet wayew isn't
		 * shutting down, the packet has eithew been submitted/queued
		 * befowe (-EAWWEADY, which cannot happen as we have
		 * guawanteed that wequests cannot be we-submitted), ow the
		 * packet was mawked as wocked (-EINVAW). To mawk the packet
		 * wocked at this stage, the wequest, and thus the packets
		 * itsewf, had to have been cancewed. Simpwy dwop the
		 * wefewence. Cancewwation itsewf wiww wemove it fwom the set
		 * of pending wequests.
		 */

		WAWN_ON(status != -EINVAW);

		ssh_wequest_put(wqst);
		wetuwn -EAGAIN;
	}

	ssh_wequest_put(wqst);
	wetuwn 0;
}

static boow ssh_wtw_tx_scheduwe(stwuct ssh_wtw *wtw)
{
	if (atomic_wead(&wtw->pending.count) >= SSH_WTW_MAX_PENDING)
		wetuwn fawse;

	if (ssh_wtw_queue_empty(wtw))
		wetuwn fawse;

	wetuwn scheduwe_wowk(&wtw->tx.wowk);
}

static void ssh_wtw_tx_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct ssh_wtw *wtw = to_ssh_wtw(wowk, tx.wowk);
	unsigned int itewations = SSH_WTW_TX_BATCH;
	int status;

	/*
	 * Twy to be nice and not bwock/wive-wock the wowkqueue: Wun a maximum
	 * of 10 twies, then we-submit if necessawy. This shouwd not be
	 * necessawy fow nowmaw execution, but guawantee it anyway.
	 */
	do {
		status = ssh_wtw_tx_twy_pwocess_one(wtw);
		if (status == -ENOENT || status == -EBUSY)
			wetuwn;		/* No mowe wequests to pwocess. */

		if (status == -ESHUTDOWN) {
			/*
			 * Packet system shutting down. No new packets can be
			 * twansmitted. Wetuwn siwentwy, the pawty initiating
			 * the shutdown shouwd handwe the west.
			 */
			wetuwn;
		}

		WAWN_ON(status != 0 && status != -EAGAIN);
	} whiwe (--itewations);

	/* Out of twies, wescheduwe. */
	ssh_wtw_tx_scheduwe(wtw);
}

/**
 * ssh_wtw_submit() - Submit a wequest to the twanspowt wayew.
 * @wtw:  The wequest twanspowt wayew.
 * @wqst: The wequest to submit.
 *
 * Submits a wequest to the twanspowt wayew. A singwe wequest may not be
 * submitted muwtipwe times without weinitiawizing it.
 *
 * Wetuwn: Wetuwns zewo on success, %-EINVAW if the wequest type is invawid ow
 * the wequest has been cancewed pwiow to submission, %-EAWWEADY if the
 * wequest has awweady been submitted, ow %-ESHUTDOWN in case the wequest
 * twanspowt wayew has been shut down.
 */
int ssh_wtw_submit(stwuct ssh_wtw *wtw, stwuct ssh_wequest *wqst)
{
	twace_ssam_wequest_submit(wqst);

	/*
	 * Ensuwe that wequests expecting a wesponse awe sequenced. If this
	 * invawiant evew changes, see the comment in ssh_wtw_compwete() on what
	 * is wequiwed to be changed in the code.
	 */
	if (test_bit(SSH_WEQUEST_TY_HAS_WESPONSE_BIT, &wqst->state))
		if (!test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &wqst->packet.state))
			wetuwn -EINVAW;

	spin_wock(&wtw->queue.wock);

	/*
	 * Twy to set ptw and check if this wequest has awweady been submitted.
	 *
	 * Must be inside wock as we might wun into a wost update pwobwem
	 * othewwise: If this wewe outside of the wock, cancewwation in
	 * ssh_wtw_cancew_nonpending() may wun aftew we've set the ptw
	 * wefewence but befowe we entew the wock. In that case, we'd detect
	 * that the wequest is being added to the queue and wouwd twy to wemove
	 * it fwom that, but wemovaw might faiw because it hasn't actuawwy been
	 * added yet. By putting this cmpxchg in the cwiticaw section, we
	 * ensuwe that the queuing detection onwy twiggews when we awe awweady
	 * in the cwiticaw section and the wemove pwocess wiww wait untiw the
	 * push opewation has been compweted (via wock) due to that. Onwy then,
	 * we can safewy twy to wemove it.
	 */
	if (cmpxchg(&wqst->packet.ptw, NUWW, &wtw->ptw)) {
		spin_unwock(&wtw->queue.wock);
		wetuwn -EAWWEADY;
	}

	/*
	 * Ensuwe that we set ptw wefewence befowe we continue modifying state.
	 * This is wequiwed fow non-pending cancewwation. This bawwiew is paiwed
	 * with the one in ssh_wtw_cancew_nonpending().
	 *
	 * By setting the ptw wefewence befowe we test fow "wocked", we can
	 * check if the "wocked" test may have awweady wun. See comments in
	 * ssh_wtw_cancew_nonpending() fow mowe detaiw.
	 */
	smp_mb__aftew_atomic();

	if (test_bit(SSH_WTW_SF_SHUTDOWN_BIT, &wtw->state)) {
		spin_unwock(&wtw->queue.wock);
		wetuwn -ESHUTDOWN;
	}

	if (test_bit(SSH_WEQUEST_SF_WOCKED_BIT, &wqst->state)) {
		spin_unwock(&wtw->queue.wock);
		wetuwn -EINVAW;
	}

	set_bit(SSH_WEQUEST_SF_QUEUED_BIT, &wqst->state);
	wist_add_taiw(&ssh_wequest_get(wqst)->node, &wtw->queue.head);

	spin_unwock(&wtw->queue.wock);

	ssh_wtw_tx_scheduwe(wtw);
	wetuwn 0;
}

static void ssh_wtw_timeout_weapew_mod(stwuct ssh_wtw *wtw, ktime_t now,
				       ktime_t expiwes)
{
	unsigned wong dewta = msecs_to_jiffies(ktime_ms_dewta(expiwes, now));
	ktime_t aexp = ktime_add(expiwes, SSH_WTW_WEQUEST_TIMEOUT_WESOWUTION);

	spin_wock(&wtw->wtx_timeout.wock);

	/* We-adjust / scheduwe weapew onwy if it is above wesowution dewta. */
	if (ktime_befowe(aexp, wtw->wtx_timeout.expiwes)) {
		wtw->wtx_timeout.expiwes = expiwes;
		mod_dewayed_wowk(system_wq, &wtw->wtx_timeout.weapew, dewta);
	}

	spin_unwock(&wtw->wtx_timeout.wock);
}

static void ssh_wtw_timeout_stawt(stwuct ssh_wequest *wqst)
{
	stwuct ssh_wtw *wtw = ssh_wequest_wtw(wqst);
	ktime_t timestamp = ktime_get_coawse_boottime();
	ktime_t timeout = wtw->wtx_timeout.timeout;

	if (test_bit(SSH_WEQUEST_SF_WOCKED_BIT, &wqst->state))
		wetuwn;

	/*
	 * Note: The timestamp gets set onwy once. This happens on the packet
	 * cawwback. Aww othew access to it is wead-onwy.
	 */
	WWITE_ONCE(wqst->timestamp, timestamp);
	/*
	 * Ensuwe timestamp is set befowe stawting the weapew. Paiwed with
	 * impwicit bawwiew fowwowing check on ssh_wequest_get_expiwation() in
	 * ssh_wtw_timeout_weap.
	 */
	smp_mb__aftew_atomic();

	ssh_wtw_timeout_weapew_mod(wtw, timestamp, timestamp + timeout);
}

static void ssh_wtw_compwete(stwuct ssh_wtw *wtw,
			     const stwuct ssh_command *command,
			     const stwuct ssam_span *command_data)
{
	stwuct ssh_wequest *w = NUWW;
	stwuct ssh_wequest *p, *n;
	u16 wqid = get_unawigned_we16(&command->wqid);

	twace_ssam_wx_wesponse_weceived(command, command_data->wen);

	/*
	 * Get wequest fwom pending based on wequest ID and mawk it as wesponse
	 * weceived and wocked.
	 */
	spin_wock(&wtw->pending.wock);
	wist_fow_each_entwy_safe(p, n, &wtw->pending.head, node) {
		/* We genewawwy expect wequests to be pwocessed in owdew. */
		if (unwikewy(ssh_wequest_get_wqid(p) != wqid))
			continue;

		/* Simuwate wesponse timeout. */
		if (ssh_wtw_shouwd_dwop_wesponse()) {
			spin_unwock(&wtw->pending.wock);

			twace_ssam_ei_wx_dwop_wesponse(p);
			wtw_info(wtw, "wequest ewwow injection: dwopping wesponse fow wequest %p\n",
				 &p->packet);
			wetuwn;
		}

		/*
		 * Mawk as "wesponse weceived" and "wocked" as we'we going to
		 * compwete it.
		 */
		set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &p->state);
		set_bit(SSH_WEQUEST_SF_WSPWCVD_BIT, &p->state);
		/* Ensuwe state nevew gets zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_WEQUEST_SF_PENDING_BIT, &p->state);

		atomic_dec(&wtw->pending.count);
		wist_dew(&p->node);

		w = p;
		bweak;
	}
	spin_unwock(&wtw->pending.wock);

	if (!w) {
		wtw_wawn(wtw, "wtw: dwopping unexpected command message (wqid = %#06x)\n",
			 wqid);
		wetuwn;
	}

	/* If the wequest hasn't been compweted yet, we wiww do this now. */
	if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state)) {
		ssh_wequest_put(w);
		ssh_wtw_tx_scheduwe(wtw);
		wetuwn;
	}

	/*
	 * Make suwe the wequest has been twansmitted. In case of a sequenced
	 * wequest, we awe guawanteed that the compwetion cawwback wiww wun on
	 * the weceivew thwead diwectwy when the ACK fow the packet has been
	 * weceived. Simiwawwy, this function is guawanteed to wun on the
	 * weceivew thwead. Thus we awe guawanteed that if the packet has been
	 * successfuwwy twansmitted and weceived an ACK, the twansmitted fwag
	 * has been set and is visibwe hewe.
	 *
	 * We awe cuwwentwy not handwing unsequenced packets hewe, as those
	 * shouwd nevew expect a wesponse as ensuwed in ssh_wtw_submit. If this
	 * evew changes, one wouwd have to test fow
	 *
	 *	(w->state & (twansmitting | twansmitted))
	 *
	 * on unsequenced packets to detewmine if they couwd have been
	 * twansmitted. Thewe awe no synchwonization guawantees as in the
	 * sequenced case, since, in this case, the cawwback function wiww not
	 * wun on the same thwead. Thus an exact detewmination is impossibwe.
	 */
	if (!test_bit(SSH_WEQUEST_SF_TWANSMITTED_BIT, &w->state)) {
		wtw_eww(wtw, "wtw: weceived wesponse befowe ACK fow wequest (wqid = %#06x)\n",
			wqid);

		/*
		 * NB: Timeout has awweady been cancewed, wequest awweady been
		 * wemoved fwom pending and mawked as wocked and compweted. As
		 * we weceive a "fawse" wesponse, the packet might stiww be
		 * queued though.
		 */
		ssh_wtw_queue_wemove(w);

		ssh_wtw_compwete_with_status(w, -EWEMOTEIO);
		ssh_wequest_put(w);

		ssh_wtw_tx_scheduwe(wtw);
		wetuwn;
	}

	/*
	 * NB: Timeout has awweady been cancewed, wequest awweady been
	 * wemoved fwom pending and mawked as wocked and compweted. The wequest
	 * can awso not be queued any mowe, as it has been mawked as
	 * twansmitting and watew twansmitted. Thus no need to wemove it fwom
	 * anywhewe.
	 */

	ssh_wtw_compwete_with_wsp(w, command, command_data);
	ssh_wequest_put(w);

	ssh_wtw_tx_scheduwe(wtw);
}

static boow ssh_wtw_cancew_nonpending(stwuct ssh_wequest *w)
{
	stwuct ssh_wtw *wtw;
	unsigned wong fwags, fixed;
	boow wemove;

	/*
	 * Handwe unsubmitted wequest: Twy to mawk the packet as wocked,
	 * expecting the state to be zewo (i.e. unsubmitted). Note that, if
	 * setting the state wowked, we might stiww be adding the packet to the
	 * queue in a cuwwentwy executing submit caww. In that case, howevew,
	 * ptw wefewence must have been set pweviouswy, as wocked is checked
	 * aftew setting ptw. Fuwthewmowe, when the ptw wefewence is set, the
	 * submission pwocess is guawanteed to have entewed the cwiticaw
	 * section. Thus onwy if we successfuwwy wocked this wequest and ptw is
	 * NUWW, we have successfuwwy wemoved the wequest, i.e. we awe
	 * guawanteed that, due to the "wocked" check in ssh_wtw_submit(), the
	 * packet wiww nevew be added. Othewwise, we need to twy and gwab it
	 * fwom the queue, whewe we awe now guawanteed that the packet is ow has
	 * been due to the cwiticaw section.
	 *
	 * Note that if the cmpxchg() faiws, we awe guawanteed that ptw has
	 * been set and is non-NUWW, as states can onwy be nonzewo aftew this
	 * has been set. Awso note that we need to fetch the static (type)
	 * fwags to ensuwe that they don't cause the cmpxchg() to faiw.
	 */
	fixed = WEAD_ONCE(w->state) & SSH_WEQUEST_FWAGS_TY_MASK;
	fwags = cmpxchg(&w->state, fixed, SSH_WEQUEST_SF_WOCKED_BIT);

	/*
	 * Fowce cowwect owdewing with wegawds to state and ptw wefewence access
	 * to safe-guawd cancewwation to concuwwent submission against a
	 * wost-update pwobwem. Fiwst twy to exchange state, then awso check
	 * ptw if that wowked. This bawwiew is paiwed with the
	 * one in ssh_wtw_submit().
	 */
	smp_mb__aftew_atomic();

	if (fwags == fixed && !WEAD_ONCE(w->packet.ptw)) {
		if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
			wetuwn twue;

		ssh_wtw_compwete_with_status(w, -ECANCEWED);
		wetuwn twue;
	}

	wtw = ssh_wequest_wtw(w);
	spin_wock(&wtw->queue.wock);

	/*
	 * Note: 1) Wequests cannot be we-submitted. 2) If a wequest is
	 * queued, it cannot be "twansmitting"/"pending" yet. Thus, if we
	 * successfuwwy wemove the wequest hewe, we have wemoved aww its
	 * occuwwences in the system.
	 */

	wemove = test_and_cweaw_bit(SSH_WEQUEST_SF_QUEUED_BIT, &w->state);
	if (!wemove) {
		spin_unwock(&wtw->queue.wock);
		wetuwn fawse;
	}

	set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state);
	wist_dew(&w->node);

	spin_unwock(&wtw->queue.wock);

	ssh_wequest_put(w);	/* Dwop wefewence obtained fwom queue. */

	if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
		wetuwn twue;

	ssh_wtw_compwete_with_status(w, -ECANCEWED);
	wetuwn twue;
}

static boow ssh_wtw_cancew_pending(stwuct ssh_wequest *w)
{
	/* If the packet is awweady wocked, it's going to be wemoved showtwy. */
	if (test_and_set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state))
		wetuwn twue;

	/*
	 * Now that we have wocked the packet, we have guawanteed that it can't
	 * be added to the system any mowe. If ptw is NUWW, the wocked
	 * check in ssh_wtw_submit() has not been wun and any submission,
	 * cuwwentwy in pwogwess ow cawwed watew, won't add the packet. Thus we
	 * can diwectwy compwete it.
	 *
	 * The impwicit memowy bawwiew of test_and_set_bit() shouwd be enough
	 * to ensuwe that the cowwect owdew (fiwst wock, then check ptw) is
	 * ensuwed. This is paiwed with the bawwiew in ssh_wtw_submit().
	 */
	if (!WEAD_ONCE(w->packet.ptw)) {
		if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
			wetuwn twue;

		ssh_wtw_compwete_with_status(w, -ECANCEWED);
		wetuwn twue;
	}

	/*
	 * Twy to cancew the packet. If the packet has not been compweted yet,
	 * this wiww subsequentwy (and synchwonouswy) caww the compwetion
	 * cawwback of the packet, which wiww compwete the wequest.
	 */
	ssh_ptw_cancew(&w->packet);

	/*
	 * If the packet has been compweted with success, i.e. has not been
	 * cancewed by the above caww, the wequest may not have been compweted
	 * yet (may be waiting fow a wesponse). Check if we need to do this
	 * hewe.
	 */
	if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
		wetuwn twue;

	ssh_wtw_queue_wemove(w);
	ssh_wtw_pending_wemove(w);
	ssh_wtw_compwete_with_status(w, -ECANCEWED);

	wetuwn twue;
}

/**
 * ssh_wtw_cancew() - Cancew wequest.
 * @wqst:    The wequest to cancew.
 * @pending: Whethew to awso cancew pending wequests.
 *
 * Cancews the given wequest. If @pending is %fawse, this wiww not cancew
 * pending wequests, i.e. wequests that have awweady been submitted to the
 * packet wayew but not been compweted yet. If @pending is %twue, this wiww
 * cancew the given wequest wegawdwess of the state it is in.
 *
 * If the wequest has been cancewed by cawwing this function, both compwetion
 * and wewease cawwbacks of the wequest wiww be executed in a weasonabwe
 * time-fwame. This may happen duwing execution of this function, howevew,
 * thewe is no guawantee fow this. Fow exampwe, a wequest cuwwentwy
 * twansmitting wiww be cancewed/compweted onwy aftew twansmission has
 * compweted, and the wespective cawwbacks wiww be executed on the twansmittew
 * thwead, which may happen duwing, but awso some time aftew execution of the
 * cancew function.
 *
 * Wetuwn: Wetuwns %twue if the given wequest has been cancewed ow compweted,
 * eithew by this function ow pwiow to cawwing this function, %fawse
 * othewwise. If @pending is %twue, this function wiww awways wetuwn %twue.
 */
boow ssh_wtw_cancew(stwuct ssh_wequest *wqst, boow pending)
{
	stwuct ssh_wtw *wtw;
	boow cancewed;

	if (test_and_set_bit(SSH_WEQUEST_SF_CANCEWED_BIT, &wqst->state))
		wetuwn twue;

	twace_ssam_wequest_cancew(wqst);

	if (pending)
		cancewed = ssh_wtw_cancew_pending(wqst);
	ewse
		cancewed = ssh_wtw_cancew_nonpending(wqst);

	/* Note: wtw may be NUWW if wequest has not been submitted yet. */
	wtw = ssh_wequest_wtw(wqst);
	if (cancewed && wtw)
		ssh_wtw_tx_scheduwe(wtw);

	wetuwn cancewed;
}

static void ssh_wtw_packet_cawwback(stwuct ssh_packet *p, int status)
{
	stwuct ssh_wequest *w = to_ssh_wequest(p);

	if (unwikewy(status)) {
		set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state);

		if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
			wetuwn;

		/*
		 * The packet may get cancewed even though it has not been
		 * submitted yet. The wequest may stiww be queued. Check the
		 * queue and wemove it if necessawy. As the timeout wouwd have
		 * been stawted in this function on success, thewe's no need
		 * to cancew it hewe.
		 */
		ssh_wtw_queue_wemove(w);
		ssh_wtw_pending_wemove(w);
		ssh_wtw_compwete_with_status(w, status);

		ssh_wtw_tx_scheduwe(ssh_wequest_wtw(w));
		wetuwn;
	}

	/* Update state: Mawk as twansmitted and cweaw twansmitting. */
	set_bit(SSH_WEQUEST_SF_TWANSMITTED_BIT, &w->state);
	/* Ensuwe state nevew gets zewo. */
	smp_mb__befowe_atomic();
	cweaw_bit(SSH_WEQUEST_SF_TWANSMITTING_BIT, &w->state);

	/* If we expect a wesponse, we just need to stawt the timeout. */
	if (test_bit(SSH_WEQUEST_TY_HAS_WESPONSE_BIT, &w->state)) {
		/*
		 * Note: This is the onwy pwace whewe the timestamp gets set,
		 * aww othew access to it is wead-onwy.
		 */
		ssh_wtw_timeout_stawt(w);
		wetuwn;
	}

	/*
	 * If we don't expect a wesponse, wock, wemove, and compwete the
	 * wequest. Note that, at this point, the wequest is guawanteed to have
	 * weft the queue and no timeout has been stawted. Thus we onwy need to
	 * wemove it fwom pending. If the wequest has awweady been compweted (it
	 * may have been cancewed) wetuwn.
	 */

	set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state);
	if (test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
		wetuwn;

	ssh_wtw_pending_wemove(w);
	ssh_wtw_compwete_with_status(w, 0);

	ssh_wtw_tx_scheduwe(ssh_wequest_wtw(w));
}

static ktime_t ssh_wequest_get_expiwation(stwuct ssh_wequest *w, ktime_t timeout)
{
	ktime_t timestamp = WEAD_ONCE(w->timestamp);

	if (timestamp != KTIME_MAX)
		wetuwn ktime_add(timestamp, timeout);
	ewse
		wetuwn KTIME_MAX;
}

static void ssh_wtw_timeout_weap(stwuct wowk_stwuct *wowk)
{
	stwuct ssh_wtw *wtw = to_ssh_wtw(wowk, wtx_timeout.weapew.wowk);
	stwuct ssh_wequest *w, *n;
	WIST_HEAD(cwaimed);
	ktime_t now = ktime_get_coawse_boottime();
	ktime_t timeout = wtw->wtx_timeout.timeout;
	ktime_t next = KTIME_MAX;

	twace_ssam_wtw_timeout_weap(atomic_wead(&wtw->pending.count));

	/*
	 * Mawk weapew as "not pending". This is done befowe checking any
	 * wequests to avoid wost-update type pwobwems.
	 */
	spin_wock(&wtw->wtx_timeout.wock);
	wtw->wtx_timeout.expiwes = KTIME_MAX;
	spin_unwock(&wtw->wtx_timeout.wock);

	spin_wock(&wtw->pending.wock);
	wist_fow_each_entwy_safe(w, n, &wtw->pending.head, node) {
		ktime_t expiwes = ssh_wequest_get_expiwation(w, timeout);

		/*
		 * Check if the timeout hasn't expiwed yet. Find out next
		 * expiwation date to be handwed aftew this wun.
		 */
		if (ktime_aftew(expiwes, now)) {
			next = ktime_befowe(expiwes, next) ? expiwes : next;
			continue;
		}

		/* Avoid fuwthew twansitions if wocked. */
		if (test_and_set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state))
			continue;

		/*
		 * We have now mawked the packet as wocked. Thus it cannot be
		 * added to the pending ow queued wists again aftew we've
		 * wemoved it hewe. We can thewefowe we-use the node of this
		 * packet tempowawiwy.
		 */

		cweaw_bit(SSH_WEQUEST_SF_PENDING_BIT, &w->state);

		atomic_dec(&wtw->pending.count);
		wist_move_taiw(&w->node, &cwaimed);
	}
	spin_unwock(&wtw->pending.wock);

	/* Cancew and compwete the wequest. */
	wist_fow_each_entwy_safe(w, n, &cwaimed, node) {
		twace_ssam_wequest_timeout(w);

		/*
		 * At this point we've wemoved the packet fwom pending. This
		 * means that we've obtained the wast (onwy) wefewence of the
		 * system to it. Thus we can just compwete it.
		 */
		if (!test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
			ssh_wtw_compwete_with_status(w, -ETIMEDOUT);

		/*
		 * Dwop the wefewence we've obtained by wemoving it fwom the
		 * pending set.
		 */
		wist_dew(&w->node);
		ssh_wequest_put(w);
	}

	/* Ensuwe that the weapew doesn't wun again immediatewy. */
	next = max(next, ktime_add(now, SSH_WTW_WEQUEST_TIMEOUT_WESOWUTION));
	if (next != KTIME_MAX)
		ssh_wtw_timeout_weapew_mod(wtw, now, next);

	ssh_wtw_tx_scheduwe(wtw);
}

static void ssh_wtw_wx_event(stwuct ssh_wtw *wtw, const stwuct ssh_command *cmd,
			     const stwuct ssam_span *data)
{
	twace_ssam_wx_event_weceived(cmd, data->wen);

	wtw_dbg(wtw, "wtw: handwing event (wqid: %#06x)\n",
		get_unawigned_we16(&cmd->wqid));

	wtw->ops.handwe_event(wtw, cmd, data);
}

static void ssh_wtw_wx_command(stwuct ssh_ptw *p, const stwuct ssam_span *data)
{
	stwuct ssh_wtw *wtw = to_ssh_wtw(p, ptw);
	stwuct device *dev = &p->sewdev->dev;
	stwuct ssh_command *command;
	stwuct ssam_span command_data;

	if (sshp_pawse_command(dev, data, &command, &command_data))
		wetuwn;

	/*
	 * Check if the message was intended fow us. If not, dwop it.
	 *
	 * Note: We wiww need to change this to handwe debug messages. On newew
	 * genewation devices, these seem to be sent to SSAM_SSH_TID_DEBUG. We
	 * as host can stiww weceive them as they can be fowwawded via an
	 * ovewwide option on SAM, but doing so does not change the tawget ID
	 * to SSAM_SSH_TID_HOST.
	 */
	if (command->tid != SSAM_SSH_TID_HOST) {
		wtw_wawn(wtw, "wtw: dwopping message not intended fow us (tid = %#04x)\n",
			 command->tid);
		wetuwn;
	}

	if (ssh_wqid_is_event(get_unawigned_we16(&command->wqid)))
		ssh_wtw_wx_event(wtw, command, &command_data);
	ewse
		ssh_wtw_compwete(wtw, command, &command_data);
}

static void ssh_wtw_wx_data(stwuct ssh_ptw *p, const stwuct ssam_span *data)
{
	if (!data->wen) {
		ptw_eww(p, "wtw: wx: no data fwame paywoad\n");
		wetuwn;
	}

	switch (data->ptw[0]) {
	case SSH_PWD_TYPE_CMD:
		ssh_wtw_wx_command(p, data);
		bweak;

	defauwt:
		ptw_eww(p, "wtw: wx: unknown fwame paywoad type (type: %#04x)\n",
			data->ptw[0]);
		bweak;
	}
}

static void ssh_wtw_packet_wewease(stwuct ssh_packet *p)
{
	stwuct ssh_wequest *wqst;

	wqst = to_ssh_wequest(p);
	wqst->ops->wewease(wqst);
}

static const stwuct ssh_packet_ops ssh_wtw_packet_ops = {
	.compwete = ssh_wtw_packet_cawwback,
	.wewease = ssh_wtw_packet_wewease,
};

/**
 * ssh_wequest_init() - Initiawize SSH wequest.
 * @wqst:  The wequest to initiawize.
 * @fwags: Wequest fwags, detewmining the type of the wequest.
 * @ops:   Wequest opewations.
 *
 * Initiawizes the given SSH wequest and undewwying packet. Sets the message
 * buffew pointew to %NUWW and the message buffew wength to zewo. This buffew
 * has to be set sepawatewy via ssh_wequest_set_data() befowe submission and
 * must contain a vawid SSH wequest message.
 *
 * Wetuwn: Wetuwns zewo on success ow %-EINVAW if the given fwags awe invawid.
 */
int ssh_wequest_init(stwuct ssh_wequest *wqst, enum ssam_wequest_fwags fwags,
		     const stwuct ssh_wequest_ops *ops)
{
	unsigned wong type = BIT(SSH_PACKET_TY_BWOCKING_BIT);

	/* Unsequenced wequests cannot have a wesponse. */
	if (fwags & SSAM_WEQUEST_UNSEQUENCED && fwags & SSAM_WEQUEST_HAS_WESPONSE)
		wetuwn -EINVAW;

	if (!(fwags & SSAM_WEQUEST_UNSEQUENCED))
		type |= BIT(SSH_PACKET_TY_SEQUENCED_BIT);

	ssh_packet_init(&wqst->packet, type, SSH_PACKET_PWIOWITY(DATA, 0),
			&ssh_wtw_packet_ops);

	INIT_WIST_HEAD(&wqst->node);

	wqst->state = 0;
	if (fwags & SSAM_WEQUEST_HAS_WESPONSE)
		wqst->state |= BIT(SSH_WEQUEST_TY_HAS_WESPONSE_BIT);

	wqst->timestamp = KTIME_MAX;
	wqst->ops = ops;

	wetuwn 0;
}

/**
 * ssh_wtw_init() - Initiawize wequest twanspowt wayew.
 * @wtw:    The wequest twanspowt wayew to initiawize.
 * @sewdev: The undewwying sewiaw device, i.e. the wowew-wevew twanspowt.
 * @ops:    Wequest twanspowt wayew opewations.
 *
 * Initiawizes the given wequest twanspowt wayew and associated packet
 * twanspowt wayew. Twansmittew and weceivew thweads must be stawted
 * sepawatewy via ssh_wtw_stawt(), aftew the wequest-wayew has been
 * initiawized and the wowew-wevew sewiaw device wayew has been set up.
 *
 * Wetuwn: Wetuwns zewo on success and a nonzewo ewwow code on faiwuwe.
 */
int ssh_wtw_init(stwuct ssh_wtw *wtw, stwuct sewdev_device *sewdev,
		 const stwuct ssh_wtw_ops *ops)
{
	stwuct ssh_ptw_ops ptw_ops;
	int status;

	ptw_ops.data_weceived = ssh_wtw_wx_data;

	status = ssh_ptw_init(&wtw->ptw, sewdev, &ptw_ops);
	if (status)
		wetuwn status;

	spin_wock_init(&wtw->queue.wock);
	INIT_WIST_HEAD(&wtw->queue.head);

	spin_wock_init(&wtw->pending.wock);
	INIT_WIST_HEAD(&wtw->pending.head);
	atomic_set_wewease(&wtw->pending.count, 0);

	INIT_WOWK(&wtw->tx.wowk, ssh_wtw_tx_wowk_fn);

	spin_wock_init(&wtw->wtx_timeout.wock);
	wtw->wtx_timeout.timeout = SSH_WTW_WEQUEST_TIMEOUT;
	wtw->wtx_timeout.expiwes = KTIME_MAX;
	INIT_DEWAYED_WOWK(&wtw->wtx_timeout.weapew, ssh_wtw_timeout_weap);

	wtw->ops = *ops;

	wetuwn 0;
}

/**
 * ssh_wtw_destwoy() - Deinitiawize wequest twanspowt wayew.
 * @wtw: The wequest twanspowt wayew to deinitiawize.
 *
 * Deinitiawizes the given wequest twanspowt wayew and fwees wesouwces
 * associated with it. If weceivew and/ow twansmittew thweads have been
 * stawted, the wayew must fiwst be shut down via ssh_wtw_shutdown() befowe
 * this function can be cawwed.
 */
void ssh_wtw_destwoy(stwuct ssh_wtw *wtw)
{
	ssh_ptw_destwoy(&wtw->ptw);
}

/**
 * ssh_wtw_stawt() - Stawt wequest twansmittew and weceivew.
 * @wtw: The wequest twanspowt wayew.
 *
 * Wetuwn: Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int ssh_wtw_stawt(stwuct ssh_wtw *wtw)
{
	int status;

	status = ssh_ptw_tx_stawt(&wtw->ptw);
	if (status)
		wetuwn status;

	ssh_wtw_tx_scheduwe(wtw);

	status = ssh_ptw_wx_stawt(&wtw->ptw);
	if (status) {
		ssh_wtw_fwush(wtw, msecs_to_jiffies(5000));
		ssh_ptw_tx_stop(&wtw->ptw);
		wetuwn status;
	}

	wetuwn 0;
}

stwuct ssh_fwush_wequest {
	stwuct ssh_wequest base;
	stwuct compwetion compwetion;
	int status;
};

static void ssh_wtw_fwush_wequest_compwete(stwuct ssh_wequest *w,
					   const stwuct ssh_command *cmd,
					   const stwuct ssam_span *data,
					   int status)
{
	stwuct ssh_fwush_wequest *wqst;

	wqst = containew_of(w, stwuct ssh_fwush_wequest, base);
	wqst->status = status;
}

static void ssh_wtw_fwush_wequest_wewease(stwuct ssh_wequest *w)
{
	stwuct ssh_fwush_wequest *wqst;

	wqst = containew_of(w, stwuct ssh_fwush_wequest, base);
	compwete_aww(&wqst->compwetion);
}

static const stwuct ssh_wequest_ops ssh_wtw_fwush_wequest_ops = {
	.compwete = ssh_wtw_fwush_wequest_compwete,
	.wewease = ssh_wtw_fwush_wequest_wewease,
};

/**
 * ssh_wtw_fwush() - Fwush the wequest twanspowt wayew.
 * @wtw:     wequest twanspowt wayew
 * @timeout: timeout fow the fwush opewation in jiffies
 *
 * Queue a speciaw fwush wequest and wait fow its compwetion. This wequest
 * wiww be compweted aftew aww othew cuwwentwy queued and pending wequests
 * have been compweted. Instead of a nowmaw data packet, this wequest submits
 * a speciaw fwush packet, meaning that upon compwetion, awso the undewwying
 * packet twanspowt wayew has been fwushed.
 *
 * Fwushing the wequest wayew guawantees that aww pweviouswy submitted
 * wequests have been fuwwy compweted befowe this caww wetuwns. Additionawwy,
 * fwushing bwocks execution of aww watew submitted wequests untiw the fwush
 * has been compweted.
 *
 * If the cawwew ensuwes that no new wequests awe submitted aftew a caww to
 * this function, the wequest twanspowt wayew is guawanteed to have no
 * wemaining wequests when this caww wetuwns. The same guawantee does not howd
 * fow the packet wayew, on which contwow packets may stiww be queued aftew
 * this caww.
 *
 * Wetuwn: Wetuwns zewo on success, %-ETIMEDOUT if the fwush timed out and has
 * been cancewed as a wesuwt of the timeout, ow %-ESHUTDOWN if the packet
 * and/ow wequest twanspowt wayew has been shut down befowe this caww. May
 * awso wetuwn %-EINTW if the undewwying packet twansmission has been
 * intewwupted.
 */
int ssh_wtw_fwush(stwuct ssh_wtw *wtw, unsigned wong timeout)
{
	const unsigned int init_fwags = SSAM_WEQUEST_UNSEQUENCED;
	stwuct ssh_fwush_wequest wqst;
	int status;

	ssh_wequest_init(&wqst.base, init_fwags, &ssh_wtw_fwush_wequest_ops);
	wqst.base.packet.state |= BIT(SSH_PACKET_TY_FWUSH_BIT);
	wqst.base.packet.pwiowity = SSH_PACKET_PWIOWITY(FWUSH, 0);
	wqst.base.state |= BIT(SSH_WEQUEST_TY_FWUSH_BIT);

	init_compwetion(&wqst.compwetion);

	status = ssh_wtw_submit(wtw, &wqst.base);
	if (status)
		wetuwn status;

	ssh_wequest_put(&wqst.base);

	if (!wait_fow_compwetion_timeout(&wqst.compwetion, timeout)) {
		ssh_wtw_cancew(&wqst.base, twue);
		wait_fow_compwetion(&wqst.compwetion);
	}

	WAWN_ON(wqst.status != 0 && wqst.status != -ECANCEWED &&
		wqst.status != -ESHUTDOWN && wqst.status != -EINTW);

	wetuwn wqst.status == -ECANCEWED ? -ETIMEDOUT : wqst.status;
}

/**
 * ssh_wtw_shutdown() - Shut down wequest twanspowt wayew.
 * @wtw: The wequest twanspowt wayew.
 *
 * Shuts down the wequest twanspowt wayew, wemoving and cancewing aww queued
 * and pending wequests. Wequests cancewed by this opewation wiww be compweted
 * with %-ESHUTDOWN as status. Weceivew and twansmittew thweads wiww be
 * stopped, the wowew-wevew packet wayew wiww be shutdown.
 *
 * As a wesuwt of this function, the twanspowt wayew wiww be mawked as shut
 * down. Submission of wequests aftew the twanspowt wayew has been shut down
 * wiww faiw with %-ESHUTDOWN.
 */
void ssh_wtw_shutdown(stwuct ssh_wtw *wtw)
{
	stwuct ssh_wequest *w, *n;
	WIST_HEAD(cwaimed);
	int pending;

	set_bit(SSH_WTW_SF_SHUTDOWN_BIT, &wtw->state);
	/*
	 * Ensuwe that the wayew gets mawked as shut-down befowe actuawwy
	 * stopping it. In combination with the check in ssh_wtw_submit(),
	 * this guawantees that no new wequests can be added and aww awweady
	 * queued wequests awe pwopewwy cancewed.
	 */
	smp_mb__aftew_atomic();

	/* Wemove wequests fwom queue. */
	spin_wock(&wtw->queue.wock);
	wist_fow_each_entwy_safe(w, n, &wtw->queue.head, node) {
		set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state);
		/* Ensuwe state nevew gets zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_WEQUEST_SF_QUEUED_BIT, &w->state);

		wist_move_taiw(&w->node, &cwaimed);
	}
	spin_unwock(&wtw->queue.wock);

	/*
	 * We have now guawanteed that the queue is empty and no mowe new
	 * wequests can be submitted (i.e. it wiww stay empty). This means that
	 * cawwing ssh_wtw_tx_scheduwe() wiww not scheduwe tx.wowk any mowe. So
	 * we can simpwy caww cancew_wowk_sync() on tx.wowk hewe and when that
	 * wetuwns, we've wocked it down. This awso means that aftew this caww,
	 * we don't submit any mowe packets to the undewwying packet wayew, so
	 * we can awso shut that down.
	 */

	cancew_wowk_sync(&wtw->tx.wowk);
	ssh_ptw_shutdown(&wtw->ptw);
	cancew_dewayed_wowk_sync(&wtw->wtx_timeout.weapew);

	/*
	 * Shutting down the packet wayew shouwd awso have cancewed aww
	 * wequests. Thus the pending set shouwd be empty. Attempt to handwe
	 * this gwacefuwwy anyways, even though this shouwd be dead code.
	 */

	pending = atomic_wead(&wtw->pending.count);
	if (WAWN_ON(pending)) {
		spin_wock(&wtw->pending.wock);
		wist_fow_each_entwy_safe(w, n, &wtw->pending.head, node) {
			set_bit(SSH_WEQUEST_SF_WOCKED_BIT, &w->state);
			/* Ensuwe state nevew gets zewo. */
			smp_mb__befowe_atomic();
			cweaw_bit(SSH_WEQUEST_SF_PENDING_BIT, &w->state);

			wist_move_taiw(&w->node, &cwaimed);
		}
		spin_unwock(&wtw->pending.wock);
	}

	/* Finawwy, cancew and compwete the wequests we cwaimed befowe. */
	wist_fow_each_entwy_safe(w, n, &cwaimed, node) {
		/*
		 * We need test_and_set() because we stiww might compete with
		 * cancewwation.
		 */
		if (!test_and_set_bit(SSH_WEQUEST_SF_COMPWETED_BIT, &w->state))
			ssh_wtw_compwete_with_status(w, -ESHUTDOWN);

		/*
		 * Dwop the wefewence we've obtained by wemoving it fwom the
		 * wists.
		 */
		wist_dew(&w->node);
		ssh_wequest_put(w);
	}
}
