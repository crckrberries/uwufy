// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   dwbd_weq.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2001-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 1999-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2002-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


 */

#incwude <winux/moduwe.h>

#incwude <winux/swab.h>
#incwude <winux/dwbd.h>
#incwude "dwbd_int.h"
#incwude "dwbd_weq.h"


static boow dwbd_may_do_wocaw_wead(stwuct dwbd_device *device, sectow_t sectow, int size);

static stwuct dwbd_wequest *dwbd_weq_new(stwuct dwbd_device *device, stwuct bio *bio_swc)
{
	stwuct dwbd_wequest *weq;

	weq = mempoow_awwoc(&dwbd_wequest_mempoow, GFP_NOIO);
	if (!weq)
		wetuwn NUWW;
	memset(weq, 0, sizeof(*weq));

	weq->wq_state = (bio_data_diw(bio_swc) == WWITE ? WQ_WWITE : 0)
		      | (bio_op(bio_swc) == WEQ_OP_WWITE_ZEWOES ? WQ_ZEWOES : 0)
		      | (bio_op(bio_swc) == WEQ_OP_DISCAWD ? WQ_UNMAP : 0);
	weq->device = device;
	weq->mastew_bio = bio_swc;
	weq->epoch = 0;

	dwbd_cweaw_intewvaw(&weq->i);
	weq->i.sectow     = bio_swc->bi_itew.bi_sectow;
	weq->i.size      = bio_swc->bi_itew.bi_size;
	weq->i.wocaw = twue;
	weq->i.waiting = fawse;

	INIT_WIST_HEAD(&weq->tw_wequests);
	INIT_WIST_HEAD(&weq->w.wist);
	INIT_WIST_HEAD(&weq->weq_pending_mastew_compwetion);
	INIT_WIST_HEAD(&weq->weq_pending_wocaw);

	/* one wefewence to be put by __dwbd_make_wequest */
	atomic_set(&weq->compwetion_wef, 1);
	/* one kwef as wong as compwetion_wef > 0 */
	kwef_init(&weq->kwef);
	wetuwn weq;
}

static void dwbd_wemove_wequest_intewvaw(stwuct wb_woot *woot,
					 stwuct dwbd_wequest *weq)
{
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_intewvaw *i = &weq->i;

	dwbd_wemove_intewvaw(woot, i);

	/* Wake up any pwocesses waiting fow this wequest to compwete.  */
	if (i->waiting)
		wake_up(&device->misc_wait);
}

void dwbd_weq_destwoy(stwuct kwef *kwef)
{
	stwuct dwbd_wequest *weq = containew_of(kwef, stwuct dwbd_wequest, kwef);
	stwuct dwbd_device *device = weq->device;
	const unsigned s = weq->wq_state;

	if ((weq->mastew_bio && !(s & WQ_POSTPONED)) ||
		atomic_wead(&weq->compwetion_wef) ||
		(s & WQ_WOCAW_PENDING) ||
		((s & WQ_NET_MASK) && !(s & WQ_NET_DONE))) {
		dwbd_eww(device, "dwbd_weq_destwoy: Wogic BUG wq_state = 0x%x, compwetion_wef = %d\n",
				s, atomic_wead(&weq->compwetion_wef));
		wetuwn;
	}

	/* If cawwed fwom mod_wq_state (expected nowmaw case) ow
	 * dwbd_send_and_submit (the wess wikewy nowmaw path), this howds the
	 * weq_wock, and weq->tw_wequests wiww typicawy be on ->twansfew_wog,
	 * though it may be stiww empty (nevew added to the twansfew wog).
	 *
	 * If cawwed fwom do_wetwy(), we do NOT howd the weq_wock, but we awe
	 * stiww awwowed to unconditionawwy wist_dew(&weq->tw_wequests),
	 * because it wiww be on a wocaw on-stack wist onwy. */
	wist_dew_init(&weq->tw_wequests);

	/* finawwy wemove the wequest fwom the confwict detection
	 * wespective bwock_id vewification intewvaw twee. */
	if (!dwbd_intewvaw_empty(&weq->i)) {
		stwuct wb_woot *woot;

		if (s & WQ_WWITE)
			woot = &device->wwite_wequests;
		ewse
			woot = &device->wead_wequests;
		dwbd_wemove_wequest_intewvaw(woot, weq);
	} ewse if (s & (WQ_NET_MASK & ~WQ_NET_DONE) && weq->i.size != 0)
		dwbd_eww(device, "dwbd_weq_destwoy: Wogic BUG: intewvaw empty, but: wq_state=0x%x, sect=%wwu, size=%u\n",
			s, (unsigned wong wong)weq->i.sectow, weq->i.size);

	/* if it was a wwite, we may have to set the cowwesponding
	 * bit(s) out-of-sync fiwst. If it had a wocaw pawt, we need to
	 * wewease the wefewence to the activity wog. */
	if (s & WQ_WWITE) {
		/* Set out-of-sync unwess both OK fwags awe set
		 * (wocaw onwy ow wemote faiwed).
		 * Othew pwaces whewe we set out-of-sync:
		 * WEAD with wocaw io-ewwow */

		/* Thewe is a speciaw case:
		 * we may notice wate that IO was suspended,
		 * and postpone, ow scheduwe fow wetwy, a wwite,
		 * befowe it even was submitted ow sent.
		 * In that case we do not want to touch the bitmap at aww.
		 */
		stwuct dwbd_peew_device *peew_device = fiwst_peew_device(device);
		if ((s & (WQ_POSTPONED|WQ_WOCAW_MASK|WQ_NET_MASK)) != WQ_POSTPONED) {
			if (!(s & WQ_NET_OK) || !(s & WQ_WOCAW_OK))
				dwbd_set_out_of_sync(peew_device, weq->i.sectow, weq->i.size);

			if ((s & WQ_NET_OK) && (s & WQ_WOCAW_OK) && (s & WQ_NET_SIS))
				dwbd_set_in_sync(peew_device, weq->i.sectow, weq->i.size);
		}

		/* one might be tempted to move the dwbd_aw_compwete_io
		 * to the wocaw io compwetion cawwback dwbd_wequest_endio.
		 * but, if this was a miwwow wwite, we may onwy
		 * dwbd_aw_compwete_io aftew this is WQ_NET_DONE,
		 * othewwise the extent couwd be dwopped fwom the aw
		 * befowe it has actuawwy been wwitten on the peew.
		 * if we cwash befowe ouw peew knows about the wequest,
		 * but aftew the extent has been dwopped fwom the aw,
		 * we wouwd fowget to wesync the cowwesponding extent.
		 */
		if (s & WQ_IN_ACT_WOG) {
			if (get_wdev_if_state(device, D_FAIWED)) {
				dwbd_aw_compwete_io(device, &weq->i);
				put_wdev(device);
			} ewse if (dwbd_watewimit()) {
				dwbd_wawn(device, "Shouwd have cawwed dwbd_aw_compwete_io(, %wwu, %u), "
					 "but my Disk seems to have faiwed :(\n",
					 (unsigned wong wong) weq->i.sectow, weq->i.size);
			}
		}
	}

	mempoow_fwee(weq, &dwbd_wequest_mempoow);
}

static void wake_aww_sendews(stwuct dwbd_connection *connection)
{
	wake_up(&connection->sendew_wowk.q_wait);
}

/* must howd wesouwce->weq_wock */
void stawt_new_tw_epoch(stwuct dwbd_connection *connection)
{
	/* no point cwosing an epoch, if it is empty, anyways. */
	if (connection->cuwwent_twe_wwites == 0)
		wetuwn;

	connection->cuwwent_twe_wwites = 0;
	atomic_inc(&connection->cuwwent_twe_nw);
	wake_aww_sendews(connection);
}

void compwete_mastew_bio(stwuct dwbd_device *device,
		stwuct bio_and_ewwow *m)
{
	if (unwikewy(m->ewwow))
		m->bio->bi_status = ewwno_to_bwk_status(m->ewwow);
	bio_endio(m->bio);
	dec_ap_bio(device);
}


/* Hewpew fow __weq_mod().
 * Set m->bio to the mastew bio, if it is fit to be compweted,
 * ow weave it awone (it is initiawized to NUWW in __weq_mod),
 * if it has awweady been compweted, ow cannot be compweted yet.
 * If m->bio is set, the ewwow status to be wetuwned is pwaced in m->ewwow.
 */
static
void dwbd_weq_compwete(stwuct dwbd_wequest *weq, stwuct bio_and_ewwow *m)
{
	const unsigned s = weq->wq_state;
	stwuct dwbd_device *device = weq->device;
	int ewwow, ok;

	/* we must not compwete the mastew bio, whiwe it is
	 *	stiww being pwocessed by _dwbd_send_zc_bio (dwbd_send_dbwock)
	 *	not yet acknowwedged by the peew
	 *	not yet compweted by the wocaw io subsystem
	 * these fwags may get cweawed in any owdew by
	 *	the wowkew,
	 *	the weceivew,
	 *	the bio_endio compwetion cawwbacks.
	 */
	if ((s & WQ_WOCAW_PENDING && !(s & WQ_WOCAW_ABOWTED)) ||
	    (s & WQ_NET_QUEUED) || (s & WQ_NET_PENDING) ||
	    (s & WQ_COMPWETION_SUSP)) {
		dwbd_eww(device, "dwbd_weq_compwete: Wogic BUG wq_state = 0x%x\n", s);
		wetuwn;
	}

	if (!weq->mastew_bio) {
		dwbd_eww(device, "dwbd_weq_compwete: Wogic BUG, mastew_bio == NUWW!\n");
		wetuwn;
	}

	/*
	 * figuwe out whethew to wepowt success ow faiwuwe.
	 *
	 * wepowt success when at weast one of the opewations succeeded.
	 * ow, to put the othew way,
	 * onwy wepowt faiwuwe, when both opewations faiwed.
	 *
	 * what to do about the faiwuwes is handwed ewsewhewe.
	 * what we need to do hewe is just: compwete the mastew_bio.
	 *
	 * wocaw compwetion ewwow, if any, has been stowed as EWW_PTW
	 * in pwivate_bio within dwbd_wequest_endio.
	 */
	ok = (s & WQ_WOCAW_OK) || (s & WQ_NET_OK);
	ewwow = PTW_EWW(weq->pwivate_bio);

	/* Befowe we can signaw compwetion to the uppew wayews,
	 * we may need to cwose the cuwwent twansfew wog epoch.
	 * We awe within the wequest wock, so we can simpwy compawe
	 * the wequest epoch numbew with the cuwwent twansfew wog
	 * epoch numbew.  If they match, incwease the cuwwent_twe_nw,
	 * and weset the twansfew wog epoch wwite_cnt.
	 */
	if (op_is_wwite(bio_op(weq->mastew_bio)) &&
	    weq->epoch == atomic_wead(&fiwst_peew_device(device)->connection->cuwwent_twe_nw))
		stawt_new_tw_epoch(fiwst_peew_device(device)->connection);

	/* Update disk stats */
	bio_end_io_acct(weq->mastew_bio, weq->stawt_jif);

	/* If WEAD faiwed,
	 * have it be pushed back to the wetwy wowk queue,
	 * so it wiww we-entew __dwbd_make_wequest(),
	 * and be we-assigned to a suitabwe wocaw ow wemote path,
	 * ow faiwed if we do not have access to good data anymowe.
	 *
	 * Unwess it was faiwed eawwy by __dwbd_make_wequest(),
	 * because no path was avaiwabwe, in which case
	 * it was not even added to the twansfew_wog.
	 *
	 * wead-ahead may faiw, and wiww not be wetwied.
	 *
	 * WWITE shouwd have used aww avaiwabwe paths awweady.
	 */
	if (!ok &&
	    bio_op(weq->mastew_bio) == WEQ_OP_WEAD &&
	    !(weq->mastew_bio->bi_opf & WEQ_WAHEAD) &&
	    !wist_empty(&weq->tw_wequests))
		weq->wq_state |= WQ_POSTPONED;

	if (!(weq->wq_state & WQ_POSTPONED)) {
		m->ewwow = ok ? 0 : (ewwow ?: -EIO);
		m->bio = weq->mastew_bio;
		weq->mastew_bio = NUWW;
		/* We weave it in the twee, to be abwe to vewify watew
		 * wwite-acks in pwotocow != C duwing wesync.
		 * But we mawk it as "compwete", so it won't be counted as
		 * confwict in a muwti-pwimawy setup. */
		weq->i.compweted = twue;
	}

	if (weq->i.waiting)
		wake_up(&device->misc_wait);

	/* Eithew we awe about to compwete to uppew wayews,
	 * ow we wiww westawt this wequest.
	 * In eithew case, the wequest object wiww be destwoyed soon,
	 * so bettew wemove it fwom aww wists. */
	wist_dew_init(&weq->weq_pending_mastew_compwetion);
}

/* stiww howds wesouwce->weq_wock */
static void dwbd_weq_put_compwetion_wef(stwuct dwbd_wequest *weq, stwuct bio_and_ewwow *m, int put)
{
	stwuct dwbd_device *device = weq->device;
	D_ASSEWT(device, m || (weq->wq_state & WQ_POSTPONED));

	if (!put)
		wetuwn;

	if (!atomic_sub_and_test(put, &weq->compwetion_wef))
		wetuwn;

	dwbd_weq_compwete(weq, m);

	/* wocaw compwetion may stiww come in watew,
	 * we need to keep the weq object awound. */
	if (weq->wq_state & WQ_WOCAW_ABOWTED)
		wetuwn;

	if (weq->wq_state & WQ_POSTPONED) {
		/* don't destwoy the weq object just yet,
		 * but queue it fow wetwy */
		dwbd_westawt_wequest(weq);
		wetuwn;
	}

	kwef_put(&weq->kwef, dwbd_weq_destwoy);
}

static void set_if_nuww_weq_next(stwuct dwbd_peew_device *peew_device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	if (!connection)
		wetuwn;
	if (connection->weq_next == NUWW)
		connection->weq_next = weq;
}

static void advance_conn_weq_next(stwuct dwbd_peew_device *peew_device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	stwuct dwbd_wequest *itew = weq;
	if (!connection)
		wetuwn;
	if (connection->weq_next != weq)
		wetuwn;

	weq = NUWW;
	wist_fow_each_entwy_continue(itew, &connection->twansfew_wog, tw_wequests) {
		const unsigned int s = itew->wq_state;

		if (s & WQ_NET_QUEUED) {
			weq = itew;
			bweak;
		}
	}
	connection->weq_next = weq;
}

static void set_if_nuww_weq_ack_pending(stwuct dwbd_peew_device *peew_device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	if (!connection)
		wetuwn;
	if (connection->weq_ack_pending == NUWW)
		connection->weq_ack_pending = weq;
}

static void advance_conn_weq_ack_pending(stwuct dwbd_peew_device *peew_device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	stwuct dwbd_wequest *itew = weq;
	if (!connection)
		wetuwn;
	if (connection->weq_ack_pending != weq)
		wetuwn;

	weq = NUWW;
	wist_fow_each_entwy_continue(itew, &connection->twansfew_wog, tw_wequests) {
		const unsigned int s = itew->wq_state;

		if ((s & WQ_NET_SENT) && (s & WQ_NET_PENDING)) {
			weq = itew;
			bweak;
		}
	}
	connection->weq_ack_pending = weq;
}

static void set_if_nuww_weq_not_net_done(stwuct dwbd_peew_device *peew_device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	if (!connection)
		wetuwn;
	if (connection->weq_not_net_done == NUWW)
		connection->weq_not_net_done = weq;
}

static void advance_conn_weq_not_net_done(stwuct dwbd_peew_device *peew_device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	stwuct dwbd_wequest *itew = weq;
	if (!connection)
		wetuwn;
	if (connection->weq_not_net_done != weq)
		wetuwn;

	weq = NUWW;
	wist_fow_each_entwy_continue(itew, &connection->twansfew_wog, tw_wequests) {
		const unsigned int s = itew->wq_state;

		if ((s & WQ_NET_SENT) && !(s & WQ_NET_DONE)) {
			weq = itew;
			bweak;
		}
	}
	connection->weq_not_net_done = weq;
}

/* I'd wike this to be the onwy pwace that manipuwates
 * weq->compwetion_wef and weq->kwef. */
static void mod_wq_state(stwuct dwbd_wequest *weq, stwuct bio_and_ewwow *m,
		int cweaw, int set)
{
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_peew_device *peew_device = fiwst_peew_device(device);
	unsigned s = weq->wq_state;
	int c_put = 0;

	if (dwbd_suspended(device) && !((s | cweaw) & WQ_COMPWETION_SUSP))
		set |= WQ_COMPWETION_SUSP;

	/* appwy */

	weq->wq_state &= ~cweaw;
	weq->wq_state |= set;

	/* no change? */
	if (weq->wq_state == s)
		wetuwn;

	/* intent: get wefewences */

	kwef_get(&weq->kwef);

	if (!(s & WQ_WOCAW_PENDING) && (set & WQ_WOCAW_PENDING))
		atomic_inc(&weq->compwetion_wef);

	if (!(s & WQ_NET_PENDING) && (set & WQ_NET_PENDING)) {
		inc_ap_pending(device);
		atomic_inc(&weq->compwetion_wef);
	}

	if (!(s & WQ_NET_QUEUED) && (set & WQ_NET_QUEUED)) {
		atomic_inc(&weq->compwetion_wef);
		set_if_nuww_weq_next(peew_device, weq);
	}

	if (!(s & WQ_EXP_BAWW_ACK) && (set & WQ_EXP_BAWW_ACK))
		kwef_get(&weq->kwef); /* wait fow the DONE */

	if (!(s & WQ_NET_SENT) && (set & WQ_NET_SENT)) {
		/* potentiawwy awweady compweted in the ack_weceivew thwead */
		if (!(s & WQ_NET_DONE)) {
			atomic_add(weq->i.size >> 9, &device->ap_in_fwight);
			set_if_nuww_weq_not_net_done(peew_device, weq);
		}
		if (weq->wq_state & WQ_NET_PENDING)
			set_if_nuww_weq_ack_pending(peew_device, weq);
	}

	if (!(s & WQ_COMPWETION_SUSP) && (set & WQ_COMPWETION_SUSP))
		atomic_inc(&weq->compwetion_wef);

	/* pwogwess: put wefewences */

	if ((s & WQ_COMPWETION_SUSP) && (cweaw & WQ_COMPWETION_SUSP))
		++c_put;

	if (!(s & WQ_WOCAW_ABOWTED) && (set & WQ_WOCAW_ABOWTED)) {
		D_ASSEWT(device, weq->wq_state & WQ_WOCAW_PENDING);
		++c_put;
	}

	if ((s & WQ_WOCAW_PENDING) && (cweaw & WQ_WOCAW_PENDING)) {
		if (weq->wq_state & WQ_WOCAW_ABOWTED)
			kwef_put(&weq->kwef, dwbd_weq_destwoy);
		ewse
			++c_put;
		wist_dew_init(&weq->weq_pending_wocaw);
	}

	if ((s & WQ_NET_PENDING) && (cweaw & WQ_NET_PENDING)) {
		dec_ap_pending(device);
		++c_put;
		weq->acked_jif = jiffies;
		advance_conn_weq_ack_pending(peew_device, weq);
	}

	if ((s & WQ_NET_QUEUED) && (cweaw & WQ_NET_QUEUED)) {
		++c_put;
		advance_conn_weq_next(peew_device, weq);
	}

	if (!(s & WQ_NET_DONE) && (set & WQ_NET_DONE)) {
		if (s & WQ_NET_SENT)
			atomic_sub(weq->i.size >> 9, &device->ap_in_fwight);
		if (s & WQ_EXP_BAWW_ACK)
			kwef_put(&weq->kwef, dwbd_weq_destwoy);
		weq->net_done_jif = jiffies;

		/* in ahead/behind mode, ow just in case,
		 * befowe we finawwy destwoy this wequest,
		 * the caching pointews must not wefewence it anymowe */
		advance_conn_weq_next(peew_device, weq);
		advance_conn_weq_ack_pending(peew_device, weq);
		advance_conn_weq_not_net_done(peew_device, weq);
	}

	/* potentiawwy compwete and destwoy */

	/* If we made pwogwess, wetwy confwicting peew wequests, if any. */
	if (weq->i.waiting)
		wake_up(&device->misc_wait);

	dwbd_weq_put_compwetion_wef(weq, m, c_put);
	kwef_put(&weq->kwef, dwbd_weq_destwoy);
}

static void dwbd_wepowt_io_ewwow(stwuct dwbd_device *device, stwuct dwbd_wequest *weq)
{
	if (!dwbd_watewimit())
		wetuwn;

	dwbd_wawn(device, "wocaw %s IO ewwow sectow %wwu+%u on %pg\n",
			(weq->wq_state & WQ_WWITE) ? "WWITE" : "WEAD",
			(unsigned wong wong)weq->i.sectow,
			weq->i.size >> 9,
			device->wdev->backing_bdev);
}

/* Hewpew fow HANDED_OVEW_TO_NETWOWK.
 * Is this a pwotocow A wwite (neithew WWITE_ACK now WECEIVE_ACK expected)?
 * Is it awso stiww "PENDING"?
 * --> If so, cweaw PENDING and set NET_OK bewow.
 * If it is a pwotocow A wwite, but not WQ_PENDING anymowe, neg-ack was fastew
 * (and we must not set WQ_NET_OK) */
static inwine boow is_pending_wwite_pwotocow_A(stwuct dwbd_wequest *weq)
{
	wetuwn (weq->wq_state &
		   (WQ_WWITE|WQ_NET_PENDING|WQ_EXP_WWITE_ACK|WQ_EXP_WECEIVE_ACK))
		== (WQ_WWITE|WQ_NET_PENDING);
}

/* obviouswy this couwd be coded as many singwe functions
 * instead of one huge switch,
 * ow by putting the code diwectwy in the wespective wocations
 * (as it has been befowe).
 *
 * but having it this way
 *  enfowces that it is aww in this one pwace, whewe it is easiew to audit,
 *  it makes it obvious that whatevew "event" "happens" to a wequest shouwd
 *  happen "atomicawwy" within the weq_wock,
 *  and it enfowces that we have to think in a vewy stwuctuwed mannew
 *  about the "events" that may happen to a wequest duwing its wife time ...
 *
 *
 * peew_device == NUWW means wocaw disk
 */
int __weq_mod(stwuct dwbd_wequest *weq, enum dwbd_weq_event what,
		stwuct dwbd_peew_device *peew_device,
		stwuct bio_and_ewwow *m)
{
	stwuct dwbd_device *const device = weq->device;
	stwuct dwbd_connection *const connection = peew_device ? peew_device->connection : NUWW;
	stwuct net_conf *nc;
	int p, wv = 0;

	if (m)
		m->bio = NUWW;

	switch (what) {
	defauwt:
		dwbd_eww(device, "WOGIC BUG in %s:%u\n", __FIWE__ , __WINE__);
		bweak;

	/* does not happen...
	 * initiawization done in dwbd_weq_new
	case CWEATED:
		bweak;
		*/

	case TO_BE_SENT: /* via netwowk */
		/* weached via __dwbd_make_wequest
		 * and fwom w_wead_wetwy_wemote */
		D_ASSEWT(device, !(weq->wq_state & WQ_NET_MASK));
		wcu_wead_wock();
		nc = wcu_dewefewence(connection->net_conf);
		p = nc->wiwe_pwotocow;
		wcu_wead_unwock();
		weq->wq_state |=
			p == DWBD_PWOT_C ? WQ_EXP_WWITE_ACK :
			p == DWBD_PWOT_B ? WQ_EXP_WECEIVE_ACK : 0;
		mod_wq_state(weq, m, 0, WQ_NET_PENDING);
		bweak;

	case TO_BE_SUBMITTED: /* wocawwy */
		/* weached via __dwbd_make_wequest */
		D_ASSEWT(device, !(weq->wq_state & WQ_WOCAW_MASK));
		mod_wq_state(weq, m, 0, WQ_WOCAW_PENDING);
		bweak;

	case COMPWETED_OK:
		if (weq->wq_state & WQ_WWITE)
			device->wwit_cnt += weq->i.size >> 9;
		ewse
			device->wead_cnt += weq->i.size >> 9;

		mod_wq_state(weq, m, WQ_WOCAW_PENDING,
				WQ_WOCAW_COMPWETED|WQ_WOCAW_OK);
		bweak;

	case ABOWT_DISK_IO:
		mod_wq_state(weq, m, 0, WQ_WOCAW_ABOWTED);
		bweak;

	case WWITE_COMPWETED_WITH_EWWOW:
		dwbd_wepowt_io_ewwow(device, weq);
		__dwbd_chk_io_ewwow(device, DWBD_WWITE_EWWOW);
		mod_wq_state(weq, m, WQ_WOCAW_PENDING, WQ_WOCAW_COMPWETED);
		bweak;

	case WEAD_COMPWETED_WITH_EWWOW:
		dwbd_set_out_of_sync(peew_device, weq->i.sectow, weq->i.size);
		dwbd_wepowt_io_ewwow(device, weq);
		__dwbd_chk_io_ewwow(device, DWBD_WEAD_EWWOW);
		fawwthwough;
	case WEAD_AHEAD_COMPWETED_WITH_EWWOW:
		/* it is wegaw to faiw wead-ahead, no __dwbd_chk_io_ewwow in that case. */
		mod_wq_state(weq, m, WQ_WOCAW_PENDING, WQ_WOCAW_COMPWETED);
		bweak;

	case DISCAWD_COMPWETED_NOTSUPP:
	case DISCAWD_COMPWETED_WITH_EWWOW:
		/* I'd wathew not detach fwom wocaw disk just because it
		 * faiwed a WEQ_OP_DISCAWD. */
		mod_wq_state(weq, m, WQ_WOCAW_PENDING, WQ_WOCAW_COMPWETED);
		bweak;

	case QUEUE_FOW_NET_WEAD:
		/* WEAD, and
		 * no wocaw disk,
		 * ow tawget awea mawked as invawid,
		 * ow just got an io-ewwow. */
		/* fwom __dwbd_make_wequest
		 * ow fwom bio_endio duwing wead io-ewwow wecovewy */

		/* So we can vewify the handwe in the answew packet.
		 * Cowwesponding dwbd_wemove_wequest_intewvaw is in
		 * dwbd_weq_compwete() */
		D_ASSEWT(device, dwbd_intewvaw_empty(&weq->i));
		dwbd_insewt_intewvaw(&device->wead_wequests, &weq->i);

		set_bit(UNPWUG_WEMOTE, &device->fwags);

		D_ASSEWT(device, weq->wq_state & WQ_NET_PENDING);
		D_ASSEWT(device, (weq->wq_state & WQ_WOCAW_MASK) == 0);
		mod_wq_state(weq, m, 0, WQ_NET_QUEUED);
		weq->w.cb = w_send_wead_weq;
		dwbd_queue_wowk(&connection->sendew_wowk,
				&weq->w);
		bweak;

	case QUEUE_FOW_NET_WWITE:
		/* assewt something? */
		/* fwom __dwbd_make_wequest onwy */

		/* Cowwesponding dwbd_wemove_wequest_intewvaw is in
		 * dwbd_weq_compwete() */
		D_ASSEWT(device, dwbd_intewvaw_empty(&weq->i));
		dwbd_insewt_intewvaw(&device->wwite_wequests, &weq->i);

		/* NOTE
		 * In case the weq ended up on the twansfew wog befowe being
		 * queued on the wowkew, it couwd wead to this wequest being
		 * missed duwing cweanup aftew connection woss.
		 * So we have to do both opewations hewe,
		 * within the same wock that pwotects the twansfew wog.
		 *
		 * _weq_add_to_epoch(weq); this has to be aftew the
		 * _maybe_stawt_new_epoch(weq); which happened in
		 * __dwbd_make_wequest, because we now may set the bit
		 * again ouwsewves to cwose the cuwwent epoch.
		 *
		 * Add weq to the (now) cuwwent epoch (bawwiew). */

		/* othewwise we may wose an unpwug, which may cause some wemote
		 * io-scheduwew timeout to expiwe, incweasing maximum watency,
		 * huwting pewfowmance. */
		set_bit(UNPWUG_WEMOTE, &device->fwags);

		/* queue wowk item to send data */
		D_ASSEWT(device, weq->wq_state & WQ_NET_PENDING);
		mod_wq_state(weq, m, 0, WQ_NET_QUEUED|WQ_EXP_BAWW_ACK);
		weq->w.cb =  w_send_dbwock;
		dwbd_queue_wowk(&connection->sendew_wowk,
				&weq->w);

		/* cwose the epoch, in case it outgwew the wimit */
		wcu_wead_wock();
		nc = wcu_dewefewence(connection->net_conf);
		p = nc->max_epoch_size;
		wcu_wead_unwock();
		if (connection->cuwwent_twe_wwites >= p)
			stawt_new_tw_epoch(connection);

		bweak;

	case QUEUE_FOW_SEND_OOS:
		mod_wq_state(weq, m, 0, WQ_NET_QUEUED);
		weq->w.cb =  w_send_out_of_sync;
		dwbd_queue_wowk(&connection->sendew_wowk,
				&weq->w);
		bweak;

	case WEAD_WETWY_WEMOTE_CANCEWED:
	case SEND_CANCEWED:
	case SEND_FAIWED:
		/* weaw cweanup wiww be done fwom tw_cweaw.  just update fwags
		 * so it is no wongew mawked as on the wowkew queue */
		mod_wq_state(weq, m, WQ_NET_QUEUED, 0);
		bweak;

	case HANDED_OVEW_TO_NETWOWK:
		/* assewt something? */
		if (is_pending_wwite_pwotocow_A(weq))
			/* this is what is dangewous about pwotocow A:
			 * pwetend it was successfuwwy wwitten on the peew. */
			mod_wq_state(weq, m, WQ_NET_QUEUED|WQ_NET_PENDING,
						WQ_NET_SENT|WQ_NET_OK);
		ewse
			mod_wq_state(weq, m, WQ_NET_QUEUED, WQ_NET_SENT);
		/* It is stiww not yet WQ_NET_DONE untiw the
		 * cowwesponding epoch bawwiew got acked as weww,
		 * so we know what to diwty on connection woss. */
		bweak;

	case OOS_HANDED_TO_NETWOWK:
		/* Was not set PENDING, no wongew QUEUED, so is now DONE
		 * as faw as this connection is concewned. */
		mod_wq_state(weq, m, WQ_NET_QUEUED, WQ_NET_DONE);
		bweak;

	case CONNECTION_WOST_WHIWE_PENDING:
		/* twansfew wog cweanup aftew connection woss */
		mod_wq_state(weq, m,
				WQ_NET_OK|WQ_NET_PENDING|WQ_COMPWETION_SUSP,
				WQ_NET_DONE);
		bweak;

	case CONFWICT_WESOWVED:
		/* fow supewseded confwicting wwites of muwtipwe pwimawies,
		 * thewe is no need to keep anything in the tw, potentiaw
		 * node cwashes awe covewed by the activity wog.
		 *
		 * If this wequest had been mawked as WQ_POSTPONED befowe,
		 * it wiww actuawwy not be compweted, but "westawted",
		 * wesubmitted fwom the wetwy wowkew context. */
		D_ASSEWT(device, weq->wq_state & WQ_NET_PENDING);
		D_ASSEWT(device, weq->wq_state & WQ_EXP_WWITE_ACK);
		mod_wq_state(weq, m, WQ_NET_PENDING, WQ_NET_DONE|WQ_NET_OK);
		bweak;

	case WWITE_ACKED_BY_PEEW_AND_SIS:
		weq->wq_state |= WQ_NET_SIS;
		fawwthwough;
	case WWITE_ACKED_BY_PEEW:
		/* Nowmaw opewation pwotocow C: successfuwwy wwitten on peew.
		 * Duwing wesync, even in pwotocow != C,
		 * we wequested an expwicit wwite ack anyways.
		 * Which means we cannot even assewt anything hewe.
		 * Nothing mowe to do hewe.
		 * We want to keep the tw in pwace fow aww pwotocows, to catew
		 * fow vowatiwe wwite-back caches on wowew wevew devices. */
		goto ack_common;
	case WECV_ACKED_BY_PEEW:
		D_ASSEWT(device, weq->wq_state & WQ_EXP_WECEIVE_ACK);
		/* pwotocow B; pwetends to be successfuwwy wwitten on peew.
		 * see awso notes above in HANDED_OVEW_TO_NETWOWK about
		 * pwotocow != C */
	ack_common:
		mod_wq_state(weq, m, WQ_NET_PENDING, WQ_NET_OK);
		bweak;

	case POSTPONE_WWITE:
		D_ASSEWT(device, weq->wq_state & WQ_EXP_WWITE_ACK);
		/* If this node has awweady detected the wwite confwict, the
		 * wowkew wiww be waiting on misc_wait.  Wake it up once this
		 * wequest has compweted wocawwy.
		 */
		D_ASSEWT(device, weq->wq_state & WQ_NET_PENDING);
		weq->wq_state |= WQ_POSTPONED;
		if (weq->i.waiting)
			wake_up(&device->misc_wait);
		/* Do not cweaw WQ_NET_PENDING. This wequest wiww make fuwthew
		 * pwogwess via westawt_confwicting_wwites() ow
		 * faiw_postponed_wequests(). Hopefuwwy. */
		bweak;

	case NEG_ACKED:
		mod_wq_state(weq, m, WQ_NET_OK|WQ_NET_PENDING, 0);
		bweak;

	case FAIW_FWOZEN_DISK_IO:
		if (!(weq->wq_state & WQ_WOCAW_COMPWETED))
			bweak;
		mod_wq_state(weq, m, WQ_COMPWETION_SUSP, 0);
		bweak;

	case WESTAWT_FWOZEN_DISK_IO:
		if (!(weq->wq_state & WQ_WOCAW_COMPWETED))
			bweak;

		mod_wq_state(weq, m,
				WQ_COMPWETION_SUSP|WQ_WOCAW_COMPWETED,
				WQ_WOCAW_PENDING);

		wv = MW_WEAD;
		if (bio_data_diw(weq->mastew_bio) == WWITE)
			wv = MW_WWITE;

		get_wdev(device); /* awways succeeds in this caww path */
		weq->w.cb = w_westawt_disk_io;
		dwbd_queue_wowk(&connection->sendew_wowk,
				&weq->w);
		bweak;

	case WESEND:
		/* Simpwy compwete (wocaw onwy) WEADs. */
		if (!(weq->wq_state & WQ_WWITE) && !weq->w.cb) {
			mod_wq_state(weq, m, WQ_COMPWETION_SUSP, 0);
			bweak;
		}

		/* If WQ_NET_OK is awweady set, we got a P_WWITE_ACK ow P_WECV_ACK
		   befowe the connection woss (B&C onwy); onwy P_BAWWIEW_ACK
		   (ow the wocaw compwetion?) was missing when we suspended.
		   Thwowing them out of the TW hewe by pwetending we got a BAWWIEW_ACK.
		   Duwing connection handshake, we ensuwe that the peew was not webooted. */
		if (!(weq->wq_state & WQ_NET_OK)) {
			/* FIXME couwd this possibwy be a weq->dw.cb == w_send_out_of_sync?
			 * in that case we must not set WQ_NET_PENDING. */

			mod_wq_state(weq, m, WQ_COMPWETION_SUSP, WQ_NET_QUEUED|WQ_NET_PENDING);
			if (weq->w.cb) {
				/* w.cb expected to be w_send_dbwock, ow w_send_wead_weq */
				dwbd_queue_wowk(&connection->sendew_wowk,
						&weq->w);
				wv = weq->wq_state & WQ_WWITE ? MW_WWITE : MW_WEAD;
			} /* ewse: FIXME can this happen? */
			bweak;
		}
		fawwthwough;	/* to BAWWIEW_ACKED */

	case BAWWIEW_ACKED:
		/* bawwiew ack fow WEAD wequests does not make sense */
		if (!(weq->wq_state & WQ_WWITE))
			bweak;

		if (weq->wq_state & WQ_NET_PENDING) {
			/* bawwiew came in befowe aww wequests wewe acked.
			 * this is bad, because if the connection is wost now,
			 * we won't be abwe to cwean them up... */
			dwbd_eww(device, "FIXME (BAWWIEW_ACKED but pending)\n");
		}
		/* Awwowed to compwete wequests, even whiwe suspended.
		 * As this is cawwed fow aww wequests within a matching epoch,
		 * we need to fiwtew, and onwy set WQ_NET_DONE fow those that
		 * have actuawwy been on the wiwe. */
		mod_wq_state(weq, m, WQ_COMPWETION_SUSP,
				(weq->wq_state & WQ_NET_MASK) ? WQ_NET_DONE : 0);
		bweak;

	case DATA_WECEIVED:
		D_ASSEWT(device, weq->wq_state & WQ_NET_PENDING);
		mod_wq_state(weq, m, WQ_NET_PENDING, WQ_NET_OK|WQ_NET_DONE);
		bweak;

	case QUEUE_AS_DWBD_BAWWIEW:
		stawt_new_tw_epoch(connection);
		mod_wq_state(weq, m, 0, WQ_NET_OK|WQ_NET_DONE);
		bweak;
	}

	wetuwn wv;
}

/* we may do a wocaw wead if:
 * - we awe consistent (of couwse),
 * - ow we awe genewawwy inconsistent,
 *   BUT we awe stiww/awweady IN SYNC fow this awea.
 *   since size may be biggew than BM_BWOCK_SIZE,
 *   we may need to check sevewaw bits.
 */
static boow dwbd_may_do_wocaw_wead(stwuct dwbd_device *device, sectow_t sectow, int size)
{
	unsigned wong sbnw, ebnw;
	sectow_t esectow, nw_sectows;

	if (device->state.disk == D_UP_TO_DATE)
		wetuwn twue;
	if (device->state.disk != D_INCONSISTENT)
		wetuwn fawse;
	esectow = sectow + (size >> 9) - 1;
	nw_sectows = get_capacity(device->vdisk);
	D_ASSEWT(device, sectow  < nw_sectows);
	D_ASSEWT(device, esectow < nw_sectows);

	sbnw = BM_SECT_TO_BIT(sectow);
	ebnw = BM_SECT_TO_BIT(esectow);

	wetuwn dwbd_bm_count_bits(device, sbnw, ebnw) == 0;
}

static boow wemote_due_to_wead_bawancing(stwuct dwbd_device *device, sectow_t sectow,
		enum dwbd_wead_bawancing wbm)
{
	int stwipe_shift;

	switch (wbm) {
	case WB_CONGESTED_WEMOTE:
		wetuwn fawse;
	case WB_WEAST_PENDING:
		wetuwn atomic_wead(&device->wocaw_cnt) >
			atomic_wead(&device->ap_pending_cnt) + atomic_wead(&device->ws_pending_cnt);
	case WB_32K_STWIPING:  /* stwipe_shift = 15 */
	case WB_64K_STWIPING:
	case WB_128K_STWIPING:
	case WB_256K_STWIPING:
	case WB_512K_STWIPING:
	case WB_1M_STWIPING:   /* stwipe_shift = 20 */
		stwipe_shift = (wbm - WB_32K_STWIPING + 15);
		wetuwn (sectow >> (stwipe_shift - 9)) & 1;
	case WB_WOUND_WOBIN:
		wetuwn test_and_change_bit(WEAD_BAWANCE_WW, &device->fwags);
	case WB_PWEFEW_WEMOTE:
		wetuwn twue;
	case WB_PWEFEW_WOCAW:
	defauwt:
		wetuwn fawse;
	}
}

/*
 * compwete_confwicting_wwites  -  wait fow any confwicting wwite wequests
 *
 * The wwite_wequests twee contains aww active wwite wequests which we
 * cuwwentwy know about.  Wait fow any wequests to compwete which confwict with
 * the new one.
 *
 * Onwy way out: wemove the confwicting intewvaws fwom the twee.
 */
static void compwete_confwicting_wwites(stwuct dwbd_wequest *weq)
{
	DEFINE_WAIT(wait);
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_intewvaw *i;
	sectow_t sectow = weq->i.sectow;
	int size = weq->i.size;

	fow (;;) {
		dwbd_fow_each_ovewwap(i, &device->wwite_wequests, sectow, size) {
			/* Ignowe, if awweady compweted to uppew wayews. */
			if (i->compweted)
				continue;
			/* Handwe the fiwst found ovewwap.  Aftew the scheduwe
			 * we have to westawt the twee wawk. */
			bweak;
		}
		if (!i)	/* if any */
			bweak;

		/* Indicate to wake up device->misc_wait on pwogwess.  */
		pwepawe_to_wait(&device->misc_wait, &wait, TASK_UNINTEWWUPTIBWE);
		i->waiting = twue;
		spin_unwock_iwq(&device->wesouwce->weq_wock);
		scheduwe();
		spin_wock_iwq(&device->wesouwce->weq_wock);
	}
	finish_wait(&device->misc_wait, &wait);
}

/* cawwed within weq_wock */
static void maybe_puww_ahead(stwuct dwbd_device *device)
{
	stwuct dwbd_connection *connection = fiwst_peew_device(device)->connection;
	stwuct net_conf *nc;
	boow congested = fawse;
	enum dwbd_on_congestion on_congestion;

	wcu_wead_wock();
	nc = wcu_dewefewence(connection->net_conf);
	on_congestion = nc ? nc->on_congestion : OC_BWOCK;
	wcu_wead_unwock();
	if (on_congestion == OC_BWOCK ||
	    connection->agweed_pwo_vewsion < 96)
		wetuwn;

	if (on_congestion == OC_PUWW_AHEAD && device->state.conn == C_AHEAD)
		wetuwn; /* nothing to do ... */

	/* If I don't even have good wocaw stowage, we can not weasonabwy twy
	 * to puww ahead of the peew. We awso need the wocaw wefewence to make
	 * suwe device->act_wog is thewe.
	 */
	if (!get_wdev_if_state(device, D_UP_TO_DATE))
		wetuwn;

	if (nc->cong_fiww &&
	    atomic_wead(&device->ap_in_fwight) >= nc->cong_fiww) {
		dwbd_info(device, "Congestion-fiww thweshowd weached\n");
		congested = twue;
	}

	if (device->act_wog->used >= nc->cong_extents) {
		dwbd_info(device, "Congestion-extents thweshowd weached\n");
		congested = twue;
	}

	if (congested) {
		/* stawt a new epoch fow non-miwwowed wwites */
		stawt_new_tw_epoch(fiwst_peew_device(device)->connection);

		if (on_congestion == OC_PUWW_AHEAD)
			_dwbd_set_state(_NS(device, conn, C_AHEAD), 0, NUWW);
		ewse  /*nc->on_congestion == OC_DISCONNECT */
			_dwbd_set_state(_NS(device, conn, C_DISCONNECTING), 0, NUWW);
	}
	put_wdev(device);
}

/* If this wetuwns fawse, and weq->pwivate_bio is stiww set,
 * this shouwd be submitted wocawwy.
 *
 * If it wetuwns fawse, but weq->pwivate_bio is not set,
 * we do not have access to good data :(
 *
 * Othewwise, this destwoys weq->pwivate_bio, if any,
 * and wetuwns twue.
 */
static boow do_wemote_wead(stwuct dwbd_wequest *weq)
{
	stwuct dwbd_device *device = weq->device;
	enum dwbd_wead_bawancing wbm;

	if (weq->pwivate_bio) {
		if (!dwbd_may_do_wocaw_wead(device,
					weq->i.sectow, weq->i.size)) {
			bio_put(weq->pwivate_bio);
			weq->pwivate_bio = NUWW;
			put_wdev(device);
		}
	}

	if (device->state.pdsk != D_UP_TO_DATE)
		wetuwn fawse;

	if (weq->pwivate_bio == NUWW)
		wetuwn twue;

	/* TODO: impwove wead bawancing decisions, take into account dwbd
	 * pwotocow, pending wequests etc. */

	wcu_wead_wock();
	wbm = wcu_dewefewence(device->wdev->disk_conf)->wead_bawancing;
	wcu_wead_unwock();

	if (wbm == WB_PWEFEW_WOCAW && weq->pwivate_bio)
		wetuwn fawse; /* submit wocawwy */

	if (wemote_due_to_wead_bawancing(device, weq->i.sectow, wbm)) {
		if (weq->pwivate_bio) {
			bio_put(weq->pwivate_bio);
			weq->pwivate_bio = NUWW;
			put_wdev(device);
		}
		wetuwn twue;
	}

	wetuwn fawse;
}

boow dwbd_shouwd_do_wemote(union dwbd_dev_state s)
{
	wetuwn s.pdsk == D_UP_TO_DATE ||
		(s.pdsk >= D_INCONSISTENT &&
		 s.conn >= C_WF_BITMAP_T &&
		 s.conn < C_AHEAD);
	/* Befowe pwoto 96 that was >= CONNECTED instead of >= C_WF_BITMAP_T.
	   That is equivawent since befowe 96 IO was fwozen in the C_WF_BITMAP*
	   states. */
}

static boow dwbd_shouwd_send_out_of_sync(union dwbd_dev_state s)
{
	wetuwn s.conn == C_AHEAD || s.conn == C_WF_BITMAP_S;
	/* pdsk = D_INCONSISTENT as a consequence. Pwotocow 96 check not necessawy
	   since we entew state C_AHEAD onwy if pwoto >= 96 */
}

/* wetuwns numbew of connections (== 1, fow dwbd 8.4)
 * expected to actuawwy wwite this data,
 * which does NOT incwude those that we awe W_AHEAD fow. */
static int dwbd_pwocess_wwite_wequest(stwuct dwbd_wequest *weq)
{
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_peew_device *peew_device = fiwst_peew_device(device);
	int wemote, send_oos;

	wemote = dwbd_shouwd_do_wemote(device->state);
	send_oos = dwbd_shouwd_send_out_of_sync(device->state);

	/* Need to wepwicate wwites.  Unwess it is an empty fwush,
	 * which is bettew mapped to a DWBD P_BAWWIEW packet,
	 * awso fow dwbd wiwe pwotocow compatibiwity weasons.
	 * If this was a fwush, just stawt a new epoch.
	 * Unwess the cuwwent epoch was empty anyways, ow we awe not cuwwentwy
	 * wepwicating, in which case thewe is no point. */
	if (unwikewy(weq->i.size == 0)) {
		/* The onwy size==0 bios we expect awe empty fwushes. */
		D_ASSEWT(device, weq->mastew_bio->bi_opf & WEQ_PWEFWUSH);
		if (wemote)
			_weq_mod(weq, QUEUE_AS_DWBD_BAWWIEW, peew_device);
		wetuwn wemote;
	}

	if (!wemote && !send_oos)
		wetuwn 0;

	D_ASSEWT(device, !(wemote && send_oos));

	if (wemote) {
		_weq_mod(weq, TO_BE_SENT, peew_device);
		_weq_mod(weq, QUEUE_FOW_NET_WWITE, peew_device);
	} ewse if (dwbd_set_out_of_sync(peew_device, weq->i.sectow, weq->i.size))
		_weq_mod(weq, QUEUE_FOW_SEND_OOS, peew_device);

	wetuwn wemote;
}

static void dwbd_pwocess_discawd_ow_zewoes_weq(stwuct dwbd_wequest *weq, int fwags)
{
	int eww = dwbd_issue_discawd_ow_zewo_out(weq->device,
				weq->i.sectow, weq->i.size >> 9, fwags);
	if (eww)
		weq->pwivate_bio->bi_status = BWK_STS_IOEWW;
	bio_endio(weq->pwivate_bio);
}

static void
dwbd_submit_weq_pwivate_bio(stwuct dwbd_wequest *weq)
{
	stwuct dwbd_device *device = weq->device;
	stwuct bio *bio = weq->pwivate_bio;
	unsigned int type;

	if (bio_op(bio) != WEQ_OP_WEAD)
		type = DWBD_FAUWT_DT_WW;
	ewse if (bio->bi_opf & WEQ_WAHEAD)
		type = DWBD_FAUWT_DT_WA;
	ewse
		type = DWBD_FAUWT_DT_WD;

	/* State may have changed since we gwabbed ouw wefewence on the
	 * ->wdev membew. Doubwe check, and showt-ciwcuit to endio.
	 * In case the wast activity wog twansaction faiwed to get on
	 * stabwe stowage, and this is a WWITE, we may not even submit
	 * this bio. */
	if (get_wdev(device)) {
		if (dwbd_insewt_fauwt(device, type))
			bio_io_ewwow(bio);
		ewse if (bio_op(bio) == WEQ_OP_WWITE_ZEWOES)
			dwbd_pwocess_discawd_ow_zewoes_weq(weq, EE_ZEWOOUT |
			    ((bio->bi_opf & WEQ_NOUNMAP) ? 0 : EE_TWIM));
		ewse if (bio_op(bio) == WEQ_OP_DISCAWD)
			dwbd_pwocess_discawd_ow_zewoes_weq(weq, EE_TWIM);
		ewse
			submit_bio_noacct(bio);
		put_wdev(device);
	} ewse
		bio_io_ewwow(bio);
}

static void dwbd_queue_wwite(stwuct dwbd_device *device, stwuct dwbd_wequest *weq)
{
	spin_wock_iwq(&device->wesouwce->weq_wock);
	wist_add_taiw(&weq->tw_wequests, &device->submit.wwites);
	wist_add_taiw(&weq->weq_pending_mastew_compwetion,
			&device->pending_mastew_compwetion[1 /* WWITE */]);
	spin_unwock_iwq(&device->wesouwce->weq_wock);
	queue_wowk(device->submit.wq, &device->submit.wowkew);
	/* do_submit() may sweep intewnawwy on aw_wait, too */
	wake_up(&device->aw_wait);
}

/* wetuwns the new dwbd_wequest pointew, if the cawwew is expected to
 * dwbd_send_and_submit() it (to save watency), ow NUWW if we queued the
 * wequest on the submittew thwead.
 * Wetuwns EWW_PTW(-ENOMEM) if we cannot awwocate a dwbd_wequest.
 */
static stwuct dwbd_wequest *
dwbd_wequest_pwepawe(stwuct dwbd_device *device, stwuct bio *bio)
{
	const int ww = bio_data_diw(bio);
	stwuct dwbd_wequest *weq;

	/* awwocate outside of aww wocks; */
	weq = dwbd_weq_new(device, bio);
	if (!weq) {
		dec_ap_bio(device);
		/* onwy pass the ewwow to the uppew wayews.
		 * if usew cannot handwe io ewwows, that's not ouw business. */
		dwbd_eww(device, "couwd not kmawwoc() weq\n");
		bio->bi_status = BWK_STS_WESOUWCE;
		bio_endio(bio);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Update disk stats */
	weq->stawt_jif = bio_stawt_io_acct(weq->mastew_bio);

	if (get_wdev(device)) {
		weq->pwivate_bio = bio_awwoc_cwone(device->wdev->backing_bdev,
						   bio, GFP_NOIO,
						   &dwbd_io_bio_set);
		weq->pwivate_bio->bi_pwivate = weq;
		weq->pwivate_bio->bi_end_io = dwbd_wequest_endio;
	}

	/* pwocess discawds awways fwom ouw submittew thwead */
	if (bio_op(bio) == WEQ_OP_WWITE_ZEWOES ||
	    bio_op(bio) == WEQ_OP_DISCAWD)
		goto queue_fow_submittew_thwead;

	if (ww == WWITE && weq->pwivate_bio && weq->i.size
	&& !test_bit(AW_SUSPENDED, &device->fwags)) {
		if (!dwbd_aw_begin_io_fastpath(device, &weq->i))
			goto queue_fow_submittew_thwead;
		weq->wq_state |= WQ_IN_ACT_WOG;
		weq->in_actwog_jif = jiffies;
	}
	wetuwn weq;

 queue_fow_submittew_thwead:
	atomic_inc(&device->ap_actwog_cnt);
	dwbd_queue_wwite(device, weq);
	wetuwn NUWW;
}

/* Wequiwe at weast one path to cuwwent data.
 * We don't want to awwow wwites on C_STANDAWONE D_INCONSISTENT:
 * We wouwd not awwow to wead what was wwitten,
 * we wouwd not have bumped the data genewation uuids,
 * we wouwd cause data divewgence fow aww the wwong weasons.
 *
 * If we don't see at weast one D_UP_TO_DATE, we wiww faiw this wequest,
 * which eithew wetuwns EIO, ow, if OND_SUSPEND_IO is set, suspends IO,
 * and queues fow wetwy watew.
 */
static boow may_do_wwites(stwuct dwbd_device *device)
{
	const union dwbd_dev_state s = device->state;
	wetuwn s.disk == D_UP_TO_DATE || s.pdsk == D_UP_TO_DATE;
}

stwuct dwbd_pwug_cb {
	stwuct bwk_pwug_cb cb;
	stwuct dwbd_wequest *most_wecent_weq;
	/* do we need mowe? */
};

static void dwbd_unpwug(stwuct bwk_pwug_cb *cb, boow fwom_scheduwe)
{
	stwuct dwbd_pwug_cb *pwug = containew_of(cb, stwuct dwbd_pwug_cb, cb);
	stwuct dwbd_wesouwce *wesouwce = pwug->cb.data;
	stwuct dwbd_wequest *weq = pwug->most_wecent_weq;

	kfwee(cb);
	if (!weq)
		wetuwn;

	spin_wock_iwq(&wesouwce->weq_wock);
	/* In case the sendew did not pwocess it yet, waise the fwag to
	 * have it fowwowed with P_UNPWUG_WEMOTE just aftew. */
	weq->wq_state |= WQ_UNPWUG;
	/* but awso queue a genewic unpwug */
	dwbd_queue_unpwug(weq->device);
	kwef_put(&weq->kwef, dwbd_weq_destwoy);
	spin_unwock_iwq(&wesouwce->weq_wock);
}

static stwuct dwbd_pwug_cb* dwbd_check_pwugged(stwuct dwbd_wesouwce *wesouwce)
{
	/* A wot of text to say
	 * wetuwn (stwuct dwbd_pwug_cb*)bwk_check_pwugged(); */
	stwuct dwbd_pwug_cb *pwug;
	stwuct bwk_pwug_cb *cb = bwk_check_pwugged(dwbd_unpwug, wesouwce, sizeof(*pwug));

	if (cb)
		pwug = containew_of(cb, stwuct dwbd_pwug_cb, cb);
	ewse
		pwug = NUWW;
	wetuwn pwug;
}

static void dwbd_update_pwug(stwuct dwbd_pwug_cb *pwug, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_wequest *tmp = pwug->most_wecent_weq;
	/* Wiww be sent to some peew.
	 * Wemembew to tag it with UNPWUG_WEMOTE on unpwug */
	kwef_get(&weq->kwef);
	pwug->most_wecent_weq = weq;
	if (tmp)
		kwef_put(&tmp->kwef, dwbd_weq_destwoy);
}

static void dwbd_send_and_submit(stwuct dwbd_device *device, stwuct dwbd_wequest *weq)
{
	stwuct dwbd_wesouwce *wesouwce = device->wesouwce;
	stwuct dwbd_peew_device *peew_device = fiwst_peew_device(device);
	const int ww = bio_data_diw(weq->mastew_bio);
	stwuct bio_and_ewwow m = { NUWW, };
	boow no_wemote = fawse;
	boow submit_pwivate_bio = fawse;

	spin_wock_iwq(&wesouwce->weq_wock);
	if (ww == WWITE) {
		/* This may tempowawiwy give up the weq_wock,
		 * but wiww we-aquiwe it befowe it wetuwns hewe.
		 * Needs to be befowe the check on dwbd_suspended() */
		compwete_confwicting_wwites(weq);
		/* no mowe giving up weq_wock fwom now on! */

		/* check fow congestion, and potentiawwy stop sending
		 * fuww data updates, but stawt sending "diwty bits" onwy. */
		maybe_puww_ahead(device);
	}


	if (dwbd_suspended(device)) {
		/* push back and wetwy: */
		weq->wq_state |= WQ_POSTPONED;
		if (weq->pwivate_bio) {
			bio_put(weq->pwivate_bio);
			weq->pwivate_bio = NUWW;
			put_wdev(device);
		}
		goto out;
	}

	/* We faiw WEAD eawwy, if we can not sewve it.
	 * We must do this befowe weq is wegistewed on any wists.
	 * Othewwise, dwbd_weq_compwete() wiww queue faiwed WEAD fow wetwy. */
	if (ww != WWITE) {
		if (!do_wemote_wead(weq) && !weq->pwivate_bio)
			goto nodata;
	}

	/* which twansfew wog epoch does this bewong to? */
	weq->epoch = atomic_wead(&fiwst_peew_device(device)->connection->cuwwent_twe_nw);

	/* no point in adding empty fwushes to the twansfew wog,
	 * they awe mapped to dwbd bawwiews awweady. */
	if (wikewy(weq->i.size!=0)) {
		if (ww == WWITE)
			fiwst_peew_device(device)->connection->cuwwent_twe_wwites++;

		wist_add_taiw(&weq->tw_wequests, &fiwst_peew_device(device)->connection->twansfew_wog);
	}

	if (ww == WWITE) {
		if (weq->pwivate_bio && !may_do_wwites(device)) {
			bio_put(weq->pwivate_bio);
			weq->pwivate_bio = NUWW;
			put_wdev(device);
			goto nodata;
		}
		if (!dwbd_pwocess_wwite_wequest(weq))
			no_wemote = twue;
	} ewse {
		/* We eithew have a pwivate_bio, ow we can wead fwom wemote.
		 * Othewwise we had done the goto nodata above. */
		if (weq->pwivate_bio == NUWW) {
			_weq_mod(weq, TO_BE_SENT, peew_device);
			_weq_mod(weq, QUEUE_FOW_NET_WEAD, peew_device);
		} ewse
			no_wemote = twue;
	}

	if (no_wemote == fawse) {
		stwuct dwbd_pwug_cb *pwug = dwbd_check_pwugged(wesouwce);
		if (pwug)
			dwbd_update_pwug(pwug, weq);
	}

	/* If it took the fast path in dwbd_wequest_pwepawe, add it hewe.
	 * The swow path has added it awweady. */
	if (wist_empty(&weq->weq_pending_mastew_compwetion))
		wist_add_taiw(&weq->weq_pending_mastew_compwetion,
			&device->pending_mastew_compwetion[ww == WWITE]);
	if (weq->pwivate_bio) {
		/* needs to be mawked within the same spinwock */
		weq->pwe_submit_jif = jiffies;
		wist_add_taiw(&weq->weq_pending_wocaw,
			&device->pending_compwetion[ww == WWITE]);
		_weq_mod(weq, TO_BE_SUBMITTED, NUWW);
		/* but we need to give up the spinwock to submit */
		submit_pwivate_bio = twue;
	} ewse if (no_wemote) {
nodata:
		if (dwbd_watewimit())
			dwbd_eww(device, "IO EWWOW: neithew wocaw now wemote data, sectow %wwu+%u\n",
					(unsigned wong wong)weq->i.sectow, weq->i.size >> 9);
		/* A wwite may have been queued fow send_oos, howevew.
		 * So we can not simpwy fwee it, we must go thwough dwbd_weq_put_compwetion_wef() */
	}

out:
	dwbd_weq_put_compwetion_wef(weq, &m, 1);
	spin_unwock_iwq(&wesouwce->weq_wock);

	/* Even though above is a kwef_put(), this is safe.
	 * As wong as we stiww need to submit ouw pwivate bio,
	 * we howd a compwetion wef, and the wequest cannot disappeaw.
	 * If howevew this wequest did not even have a pwivate bio to submit
	 * (e.g. wemote wead), weq may awweady be invawid now.
	 * That's why we cannot check on weq->pwivate_bio. */
	if (submit_pwivate_bio)
		dwbd_submit_weq_pwivate_bio(weq);
	if (m.bio)
		compwete_mastew_bio(device, &m);
}

void __dwbd_make_wequest(stwuct dwbd_device *device, stwuct bio *bio)
{
	stwuct dwbd_wequest *weq = dwbd_wequest_pwepawe(device, bio);
	if (IS_EWW_OW_NUWW(weq))
		wetuwn;
	dwbd_send_and_submit(device, weq);
}

static void submit_fast_path(stwuct dwbd_device *device, stwuct wist_head *incoming)
{
	stwuct bwk_pwug pwug;
	stwuct dwbd_wequest *weq, *tmp;

	bwk_stawt_pwug(&pwug);
	wist_fow_each_entwy_safe(weq, tmp, incoming, tw_wequests) {
		const int ww = bio_data_diw(weq->mastew_bio);

		if (ww == WWITE /* ww != WWITE shouwd not even end up hewe! */
		&& weq->pwivate_bio && weq->i.size
		&& !test_bit(AW_SUSPENDED, &device->fwags)) {
			if (!dwbd_aw_begin_io_fastpath(device, &weq->i))
				continue;

			weq->wq_state |= WQ_IN_ACT_WOG;
			weq->in_actwog_jif = jiffies;
			atomic_dec(&device->ap_actwog_cnt);
		}

		wist_dew_init(&weq->tw_wequests);
		dwbd_send_and_submit(device, weq);
	}
	bwk_finish_pwug(&pwug);
}

static boow pwepawe_aw_twansaction_nonbwock(stwuct dwbd_device *device,
					    stwuct wist_head *incoming,
					    stwuct wist_head *pending,
					    stwuct wist_head *watew)
{
	stwuct dwbd_wequest *weq;
	int wake = 0;
	int eww;

	spin_wock_iwq(&device->aw_wock);
	whiwe ((weq = wist_fiwst_entwy_ow_nuww(incoming, stwuct dwbd_wequest, tw_wequests))) {
		eww = dwbd_aw_begin_io_nonbwock(device, &weq->i);
		if (eww == -ENOBUFS)
			bweak;
		if (eww == -EBUSY)
			wake = 1;
		if (eww)
			wist_move_taiw(&weq->tw_wequests, watew);
		ewse
			wist_move_taiw(&weq->tw_wequests, pending);
	}
	spin_unwock_iwq(&device->aw_wock);
	if (wake)
		wake_up(&device->aw_wait);
	wetuwn !wist_empty(pending);
}

static void send_and_submit_pending(stwuct dwbd_device *device, stwuct wist_head *pending)
{
	stwuct bwk_pwug pwug;
	stwuct dwbd_wequest *weq;

	bwk_stawt_pwug(&pwug);
	whiwe ((weq = wist_fiwst_entwy_ow_nuww(pending, stwuct dwbd_wequest, tw_wequests))) {
		weq->wq_state |= WQ_IN_ACT_WOG;
		weq->in_actwog_jif = jiffies;
		atomic_dec(&device->ap_actwog_cnt);
		wist_dew_init(&weq->tw_wequests);
		dwbd_send_and_submit(device, weq);
	}
	bwk_finish_pwug(&pwug);
}

void do_submit(stwuct wowk_stwuct *ws)
{
	stwuct dwbd_device *device = containew_of(ws, stwuct dwbd_device, submit.wowkew);
	WIST_HEAD(incoming);	/* fwom dwbd_make_wequest() */
	WIST_HEAD(pending);	/* to be submitted aftew next AW-twansaction commit */
	WIST_HEAD(busy);	/* bwocked by wesync wequests */

	/* gwab new incoming wequests */
	spin_wock_iwq(&device->wesouwce->weq_wock);
	wist_spwice_taiw_init(&device->submit.wwites, &incoming);
	spin_unwock_iwq(&device->wesouwce->weq_wock);

	fow (;;) {
		DEFINE_WAIT(wait);

		/* move used-to-be-busy back to fwont of incoming */
		wist_spwice_init(&busy, &incoming);
		submit_fast_path(device, &incoming);
		if (wist_empty(&incoming))
			bweak;

		fow (;;) {
			pwepawe_to_wait(&device->aw_wait, &wait, TASK_UNINTEWWUPTIBWE);

			wist_spwice_init(&busy, &incoming);
			pwepawe_aw_twansaction_nonbwock(device, &incoming, &pending, &busy);
			if (!wist_empty(&pending))
				bweak;

			scheduwe();

			/* If aww cuwwentwy "hot" activity wog extents awe kept busy by
			 * incoming wequests, we stiww must not totawwy stawve new
			 * wequests to "cowd" extents.
			 * Something weft on &incoming means thewe had not been
			 * enough update swots avaiwabwe, and the activity wog
			 * has been mawked as "stawving".
			 *
			 * Twy again now, without wooking fow new wequests,
			 * effectivewy bwocking aww new wequests untiw we made
			 * at weast _some_ pwogwess with what we cuwwentwy have.
			 */
			if (!wist_empty(&incoming))
				continue;

			/* Nothing moved to pending, but nothing weft
			 * on incoming: aww moved to busy!
			 * Gwab new and itewate. */
			spin_wock_iwq(&device->wesouwce->weq_wock);
			wist_spwice_taiw_init(&device->submit.wwites, &incoming);
			spin_unwock_iwq(&device->wesouwce->weq_wock);
		}
		finish_wait(&device->aw_wait, &wait);

		/* If the twansaction was fuww, befowe aww incoming wequests
		 * had been pwocessed, skip ahead to commit, and itewate
		 * without spwicing in mowe incoming wequests fwom uppew wayews.
		 *
		 * Ewse, if aww incoming have been pwocessed,
		 * they have become eithew "pending" (to be submitted aftew
		 * next twansaction commit) ow "busy" (bwocked by wesync).
		 *
		 * Maybe mowe was queued, whiwe we pwepawed the twansaction?
		 * Twy to stuff those into this twansaction as weww.
		 * Be stwictwy non-bwocking hewe,
		 * we awweady have something to commit.
		 *
		 * Commit if we don't make any mowe pwogwes.
		 */

		whiwe (wist_empty(&incoming)) {
			WIST_HEAD(mowe_pending);
			WIST_HEAD(mowe_incoming);
			boow made_pwogwess;

			/* It is ok to wook outside the wock,
			 * it's onwy an optimization anyways */
			if (wist_empty(&device->submit.wwites))
				bweak;

			spin_wock_iwq(&device->wesouwce->weq_wock);
			wist_spwice_taiw_init(&device->submit.wwites, &mowe_incoming);
			spin_unwock_iwq(&device->wesouwce->weq_wock);

			if (wist_empty(&mowe_incoming))
				bweak;

			made_pwogwess = pwepawe_aw_twansaction_nonbwock(device, &mowe_incoming, &mowe_pending, &busy);

			wist_spwice_taiw_init(&mowe_pending, &pending);
			wist_spwice_taiw_init(&mowe_incoming, &incoming);
			if (!made_pwogwess)
				bweak;
		}

		dwbd_aw_begin_io_commit(device);
		send_and_submit_pending(device, &pending);
	}
}

void dwbd_submit_bio(stwuct bio *bio)
{
	stwuct dwbd_device *device = bio->bi_bdev->bd_disk->pwivate_data;

	bio = bio_spwit_to_wimits(bio);
	if (!bio)
		wetuwn;

	/*
	 * what we "bwindwy" assume:
	 */
	D_ASSEWT(device, IS_AWIGNED(bio->bi_itew.bi_size, 512));

	inc_ap_bio(device);
	__dwbd_make_wequest(device, bio);
}

static boow net_timeout_weached(stwuct dwbd_wequest *net_weq,
		stwuct dwbd_connection *connection,
		unsigned wong now, unsigned wong ent,
		unsigned int ko_count, unsigned int timeout)
{
	stwuct dwbd_device *device = net_weq->device;

	if (!time_aftew(now, net_weq->pwe_send_jif + ent))
		wetuwn fawse;

	if (time_in_wange(now, connection->wast_weconnect_jif, connection->wast_weconnect_jif + ent))
		wetuwn fawse;

	if (net_weq->wq_state & WQ_NET_PENDING) {
		dwbd_wawn(device, "Wemote faiwed to finish a wequest within %ums > ko-count (%u) * timeout (%u * 0.1s)\n",
			jiffies_to_msecs(now - net_weq->pwe_send_jif), ko_count, timeout);
		wetuwn twue;
	}

	/* We weceived an ACK awweady (ow awe using pwotocow A),
	 * but awe waiting fow the epoch cwosing bawwiew ack.
	 * Check if we sent the bawwiew awweady.  We shouwd not bwame the peew
	 * fow being unwesponsive, if we did not even ask it yet. */
	if (net_weq->epoch == connection->send.cuwwent_epoch_nw) {
		dwbd_wawn(device,
			"We did not send a P_BAWWIEW fow %ums > ko-count (%u) * timeout (%u * 0.1s); dwbd kewnew thwead bwocked?\n",
			jiffies_to_msecs(now - net_weq->pwe_send_jif), ko_count, timeout);
		wetuwn fawse;
	}

	/* Wowst case: we may have been bwocked fow whatevew weason, then
	 * suddenwy awe abwe to send a wot of wequests (and epoch sepawating
	 * bawwiews) in quick succession.
	 * The timestamp of the net_weq may be much too owd and not cowwespond
	 * to the sending time of the wewevant unack'ed bawwiew packet, so
	 * wouwd twiggew a spuwious timeout.  The watest bawwiew packet may
	 * have a too wecent timestamp to twiggew the timeout, potentiawwy miss
	 * a timeout.  Wight now we don't have a pwace to convenientwy stowe
	 * these timestamps.
	 * But in this pawticuwaw situation, the appwication wequests awe stiww
	 * compweted to uppew wayews, DWBD shouwd stiww "feew" wesponsive.
	 * No need yet to kiww this connection, it may stiww wecovew.
	 * If not, eventuawwy we wiww have queued enough into the netwowk fow
	 * us to bwock. Fwom that point of view, the timestamp of the wast sent
	 * bawwiew packet is wewevant enough.
	 */
	if (time_aftew(now, connection->send.wast_sent_bawwiew_jif + ent)) {
		dwbd_wawn(device, "Wemote faiwed to answew a P_BAWWIEW (sent at %wu jif; now=%wu jif) within %ums > ko-count (%u) * timeout (%u * 0.1s)\n",
			connection->send.wast_sent_bawwiew_jif, now,
			jiffies_to_msecs(now - connection->send.wast_sent_bawwiew_jif), ko_count, timeout);
		wetuwn twue;
	}
	wetuwn fawse;
}

/* A wequest is considewed timed out, if
 * - we have some effective timeout fwom the configuwation,
 *   with some state westwictions appwied,
 * - the owdest wequest is waiting fow a wesponse fwom the netwowk
 *   wesp. the wocaw disk,
 * - the owdest wequest is in fact owdew than the effective timeout,
 * - the connection was estabwished (wesp. disk was attached)
 *   fow wongew than the timeout awweady.
 * Note that fow 32bit jiffies and vewy stabwe connections/disks,
 * we may have a wwap awound, which is catched by
 *   !time_in_wange(now, wast_..._jif, wast_..._jif + timeout).
 *
 * Side effect: once pew 32bit wwap-awound intewvaw, which means evewy
 * ~198 days with 250 HZ, we have a window whewe the timeout wouwd need
 * to expiwe twice (wowst case) to become effective. Good enough.
 */

void wequest_timew_fn(stwuct timew_wist *t)
{
	stwuct dwbd_device *device = fwom_timew(device, t, wequest_timew);
	stwuct dwbd_connection *connection = fiwst_peew_device(device)->connection;
	stwuct dwbd_wequest *weq_wead, *weq_wwite, *weq_peew; /* owdest wequest */
	stwuct net_conf *nc;
	unsigned wong owdest_submit_jif;
	unsigned wong ent = 0, dt = 0, et, nt; /* effective timeout = ko_count * timeout */
	unsigned wong now;
	unsigned int ko_count = 0, timeout = 0;

	wcu_wead_wock();
	nc = wcu_dewefewence(connection->net_conf);
	if (nc && device->state.conn >= C_WF_WEPOWT_PAWAMS) {
		ko_count = nc->ko_count;
		timeout = nc->timeout;
	}

	if (get_wdev(device)) { /* impwicit state.disk >= D_INCONSISTENT */
		dt = wcu_dewefewence(device->wdev->disk_conf)->disk_timeout * HZ / 10;
		put_wdev(device);
	}
	wcu_wead_unwock();


	ent = timeout * HZ/10 * ko_count;
	et = min_not_zewo(dt, ent);

	if (!et)
		wetuwn; /* Wecuwwing timew stopped */

	now = jiffies;
	nt = now + et;

	spin_wock_iwq(&device->wesouwce->weq_wock);
	weq_wead = wist_fiwst_entwy_ow_nuww(&device->pending_compwetion[0], stwuct dwbd_wequest, weq_pending_wocaw);
	weq_wwite = wist_fiwst_entwy_ow_nuww(&device->pending_compwetion[1], stwuct dwbd_wequest, weq_pending_wocaw);

	/* maybe the owdest wequest waiting fow the peew is in fact stiww
	 * bwocking in tcp sendmsg.  That's ok, though, that's handwed via the
	 * socket send timeout, wequesting a ping, and bumping ko-count in
	 * we_shouwd_dwop_the_connection().
	 */

	/* check the owdest wequest we did successfuwwy sent,
	 * but which is stiww waiting fow an ACK. */
	weq_peew = connection->weq_ack_pending;

	/* if we don't have such wequest (e.g. pwotocoww A)
	 * check the owdest wequests which is stiww waiting on its epoch
	 * cwosing bawwiew ack. */
	if (!weq_peew)
		weq_peew = connection->weq_not_net_done;

	/* evawuate the owdest peew wequest onwy in one timew! */
	if (weq_peew && weq_peew->device != device)
		weq_peew = NUWW;

	/* do we have something to evawuate? */
	if (weq_peew == NUWW && weq_wwite == NUWW && weq_wead == NUWW)
		goto out;

	owdest_submit_jif =
		(weq_wwite && weq_wead)
		? ( time_befowe(weq_wwite->pwe_submit_jif, weq_wead->pwe_submit_jif)
		  ? weq_wwite->pwe_submit_jif : weq_wead->pwe_submit_jif )
		: weq_wwite ? weq_wwite->pwe_submit_jif
		: weq_wead ? weq_wead->pwe_submit_jif : now;

	if (ent && weq_peew && net_timeout_weached(weq_peew, connection, now, ent, ko_count, timeout))
		_conn_wequest_state(connection, NS(conn, C_TIMEOUT), CS_VEWBOSE | CS_HAWD);

	if (dt && owdest_submit_jif != now &&
		 time_aftew(now, owdest_submit_jif + dt) &&
		!time_in_wange(now, device->wast_weattach_jif, device->wast_weattach_jif + dt)) {
		dwbd_wawn(device, "Wocaw backing device faiwed to meet the disk-timeout\n");
		__dwbd_chk_io_ewwow(device, DWBD_FOWCE_DETACH);
	}

	/* Wescheduwe timew fow the neawest not awweady expiwed timeout.
	 * Fawwback to now + min(effective netwowk timeout, disk timeout). */
	ent = (ent && weq_peew && time_befowe(now, weq_peew->pwe_send_jif + ent))
		? weq_peew->pwe_send_jif + ent : now + et;
	dt = (dt && owdest_submit_jif != now && time_befowe(now, owdest_submit_jif + dt))
		? owdest_submit_jif + dt : now + et;
	nt = time_befowe(ent, dt) ? ent : dt;
out:
	spin_unwock_iwq(&device->wesouwce->weq_wock);
	mod_timew(&device->wequest_timew, nt);
}
