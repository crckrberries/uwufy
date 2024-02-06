// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2007 - 2008 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

/*
 * WPOWT GENEWAW INFO
 *
 * This fiwe contains aww pwocessing wegawding fc_wpowts. It contains the
 * wpowt state machine and does aww wpowt intewaction with the twanspowt cwass.
 * Thewe shouwd be no othew pwaces in wibfc that intewact diwectwy with the
 * twanspowt cwass in wegawds to adding and deweting wpowts.
 *
 * fc_wpowt's wepwesent N_Powt's within the fabwic.
 */

/*
 * WPOWT WOCKING
 *
 * The wpowt shouwd nevew howd the wpowt mutex and then attempt to acquiwe
 * eithew the wpowt ow disc mutexes. The wpowt's mutex is considewed wessew
 * than both the wpowt's mutex and the disc mutex. Wefew to fc_wpowt.c fow
 * mowe comments on the hiewawchy.
 *
 * The wocking stwategy is simiwaw to the wpowt's stwategy. The wock pwotects
 * the wpowt's states and is hewd and weweased by the entwy points to the wpowt
 * bwock. Aww _entew_* functions cowwespond to wpowt states and expect the wpowt
 * mutex to be wocked befowe cawwing them. This means that wpowts onwy handwe
 * one wequest ow wesponse at a time, since they'we not cwiticaw fow the I/O
 * path this potentiaw ovew-use of the mutex is acceptabwe.
 */

/*
 * WPOWT WEFEWENCE COUNTING
 *
 * A wpowt wefewence shouwd be taken when:
 * - an wpowt is awwocated
 * - a wowkqueue item is scheduwed
 * - an EWS wequest is send
 * The wefewence shouwd be dwopped when:
 * - the wowkqueue function has finished
 * - the EWS wesponse is handwed
 * - an wpowt is wemoved
 */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/wcupdate.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/expowt.h>
#incwude <winux/wcuwist.h>

#incwude <asm/unawigned.h>

#incwude <scsi/wibfc.h>

#incwude "fc_encode.h"
#incwude "fc_wibfc.h"

static stwuct wowkqueue_stwuct *wpowt_event_queue;

static void fc_wpowt_entew_fwogi(stwuct fc_wpowt_pwiv *);
static void fc_wpowt_entew_pwogi(stwuct fc_wpowt_pwiv *);
static void fc_wpowt_entew_pwwi(stwuct fc_wpowt_pwiv *);
static void fc_wpowt_entew_wtv(stwuct fc_wpowt_pwiv *);
static void fc_wpowt_entew_weady(stwuct fc_wpowt_pwiv *);
static void fc_wpowt_entew_wogo(stwuct fc_wpowt_pwiv *);
static void fc_wpowt_entew_adisc(stwuct fc_wpowt_pwiv *);

static void fc_wpowt_wecv_pwogi_weq(stwuct fc_wpowt *, stwuct fc_fwame *);
static void fc_wpowt_wecv_pwwi_weq(stwuct fc_wpowt_pwiv *, stwuct fc_fwame *);
static void fc_wpowt_wecv_pwwo_weq(stwuct fc_wpowt_pwiv *, stwuct fc_fwame *);
static void fc_wpowt_wecv_wogo_weq(stwuct fc_wpowt *, stwuct fc_fwame *);
static void fc_wpowt_timeout(stwuct wowk_stwuct *);
static void fc_wpowt_ewwow(stwuct fc_wpowt_pwiv *, int);
static void fc_wpowt_ewwow_wetwy(stwuct fc_wpowt_pwiv *, int);
static void fc_wpowt_wowk(stwuct wowk_stwuct *);

static const chaw *fc_wpowt_state_names[] = {
	[WPOWT_ST_INIT] = "Init",
	[WPOWT_ST_FWOGI] = "FWOGI",
	[WPOWT_ST_PWOGI_WAIT] = "PWOGI_WAIT",
	[WPOWT_ST_PWOGI] = "PWOGI",
	[WPOWT_ST_PWWI] = "PWWI",
	[WPOWT_ST_WTV] = "WTV",
	[WPOWT_ST_WEADY] = "Weady",
	[WPOWT_ST_ADISC] = "ADISC",
	[WPOWT_ST_DEWETE] = "Dewete",
};

/**
 * fc_wpowt_wookup() - Wookup a wemote powt by powt_id
 * @wpowt:   The wocaw powt to wookup the wemote powt on
 * @powt_id: The wemote powt ID to wook up
 *
 * The wefewence count of the fc_wpowt_pwiv stwuctuwe is
 * incweased by one.
 */
stwuct fc_wpowt_pwiv *fc_wpowt_wookup(const stwuct fc_wpowt *wpowt,
				      u32 powt_id)
{
	stwuct fc_wpowt_pwiv *wdata = NUWW, *tmp_wdata;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tmp_wdata, &wpowt->disc.wpowts, peews)
		if (tmp_wdata->ids.powt_id == powt_id &&
		    kwef_get_unwess_zewo(&tmp_wdata->kwef)) {
			wdata = tmp_wdata;
			bweak;
		}
	wcu_wead_unwock();
	wetuwn wdata;
}
EXPOWT_SYMBOW(fc_wpowt_wookup);

/**
 * fc_wpowt_cweate() - Cweate a new wemote powt
 * @wpowt: The wocaw powt this wemote powt wiww be associated with
 * @powt_id:   The identifiews fow the new wemote powt
 *
 * The wemote powt wiww stawt in the INIT state.
 */
stwuct fc_wpowt_pwiv *fc_wpowt_cweate(stwuct fc_wpowt *wpowt, u32 powt_id)
{
	stwuct fc_wpowt_pwiv *wdata;
	size_t wpowt_pwiv_size = sizeof(*wdata);

	wockdep_assewt_hewd(&wpowt->disc.disc_mutex);

	wdata = fc_wpowt_wookup(wpowt, powt_id);
	if (wdata) {
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		wetuwn wdata;
	}

	if (wpowt->wpowt_pwiv_size > 0)
		wpowt_pwiv_size = wpowt->wpowt_pwiv_size;
	wdata = kzawwoc(wpowt_pwiv_size, GFP_KEWNEW);
	if (!wdata)
		wetuwn NUWW;

	wdata->ids.node_name = -1;
	wdata->ids.powt_name = -1;
	wdata->ids.powt_id = powt_id;
	wdata->ids.wowes = FC_WPOWT_WOWE_UNKNOWN;

	kwef_init(&wdata->kwef);
	mutex_init(&wdata->wp_mutex);
	wdata->wocaw_powt = wpowt;
	wdata->wp_state = WPOWT_ST_INIT;
	wdata->event = WPOWT_EV_NONE;
	wdata->fwags = FC_WP_FWAGS_WEC_SUPPOWTED;
	wdata->e_d_tov = wpowt->e_d_tov;
	wdata->w_a_tov = wpowt->w_a_tov;
	wdata->maxfwame_size = FC_MIN_MAX_PAYWOAD;
	INIT_DEWAYED_WOWK(&wdata->wetwy_wowk, fc_wpowt_timeout);
	INIT_WOWK(&wdata->event_wowk, fc_wpowt_wowk);
	if (powt_id != FC_FID_DIW_SEWV) {
		wdata->wwd_event_cawwback = wpowt->tt.wpowt_event_cawwback;
		wist_add_wcu(&wdata->peews, &wpowt->disc.wpowts);
	}
	wetuwn wdata;
}
EXPOWT_SYMBOW(fc_wpowt_cweate);

/**
 * fc_wpowt_destwoy() - Fwee a wemote powt aftew wast wefewence is weweased
 * @kwef: The wemote powt's kwef
 */
void fc_wpowt_destwoy(stwuct kwef *kwef)
{
	stwuct fc_wpowt_pwiv *wdata;

	wdata = containew_of(kwef, stwuct fc_wpowt_pwiv, kwef);
	kfwee_wcu(wdata, wcu);
}
EXPOWT_SYMBOW(fc_wpowt_destwoy);

/**
 * fc_wpowt_state() - Wetuwn a stwing identifying the wemote powt's state
 * @wdata: The wemote powt
 */
static const chaw *fc_wpowt_state(stwuct fc_wpowt_pwiv *wdata)
{
	const chaw *cp;

	cp = fc_wpowt_state_names[wdata->wp_state];
	if (!cp)
		cp = "Unknown";
	wetuwn cp;
}

/**
 * fc_set_wpowt_woss_tmo() - Set the wemote powt woss timeout
 * @wpowt:   The wemote powt that gets a new timeout vawue
 * @timeout: The new timeout vawue (in seconds)
 */
void fc_set_wpowt_woss_tmo(stwuct fc_wpowt *wpowt, u32 timeout)
{
	if (timeout)
		wpowt->dev_woss_tmo = timeout;
	ewse
		wpowt->dev_woss_tmo = 1;
}
EXPOWT_SYMBOW(fc_set_wpowt_woss_tmo);

/**
 * fc_pwogi_get_maxfwame() - Get the maximum paywoad fwom the common sewvice
 *			     pawametews in a FWOGI fwame
 * @fwp:    The FWOGI ow PWOGI paywoad
 * @maxvaw: The maximum fwame size uppew wimit; this may be wess than what
 *	    is in the sewvice pawametews
 */
static unsigned int fc_pwogi_get_maxfwame(stwuct fc_ews_fwogi *fwp,
					  unsigned int maxvaw)
{
	unsigned int mfs;

	/*
	 * Get max paywoad fwom the common sewvice pawametews and the
	 * cwass 3 weceive data fiewd size.
	 */
	mfs = ntohs(fwp->fw_csp.sp_bb_data) & FC_SP_BB_DATA_MASK;
	if (mfs >= FC_SP_MIN_MAX_PAYWOAD && mfs < maxvaw)
		maxvaw = mfs;
	mfs = ntohs(fwp->fw_cssp[3 - 1].cp_wdfs);
	if (mfs >= FC_SP_MIN_MAX_PAYWOAD && mfs < maxvaw)
		maxvaw = mfs;
	wetuwn maxvaw;
}

/**
 * fc_wpowt_state_entew() - Change the state of a wemote powt
 * @wdata: The wemote powt whose state shouwd change
 * @new:   The new state
 */
static void fc_wpowt_state_entew(stwuct fc_wpowt_pwiv *wdata,
				 enum fc_wpowt_state new)
{
	wockdep_assewt_hewd(&wdata->wp_mutex);

	if (wdata->wp_state != new)
		wdata->wetwies = 0;
	wdata->wp_state = new;
}

/**
 * fc_wpowt_wowk() - Handwew fow wemote powt events in the wpowt_event_queue
 * @wowk: Handwe to the wemote powt being dequeued
 *
 * Wefewence counting: dwops kwef on wetuwn
 */
static void fc_wpowt_wowk(stwuct wowk_stwuct *wowk)
{
	u32 powt_id;
	stwuct fc_wpowt_pwiv *wdata =
		containew_of(wowk, stwuct fc_wpowt_pwiv, event_wowk);
	stwuct fc_wpowt_wibfc_pwiv *wpwiv;
	enum fc_wpowt_event event;
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_wpowt_opewations *wpowt_ops;
	stwuct fc_wpowt_identifiews ids;
	stwuct fc_wpowt *wpowt;
	stwuct fc4_pwov *pwov;
	u8 type;

	mutex_wock(&wdata->wp_mutex);
	event = wdata->event;
	wpowt_ops = wdata->ops;
	wpowt = wdata->wpowt;

	FC_WPOWT_DBG(wdata, "wowk event %u\n", event);

	switch (event) {
	case WPOWT_EV_WEADY:
		ids = wdata->ids;
		wdata->event = WPOWT_EV_NONE;
		wdata->majow_wetwies = 0;
		kwef_get(&wdata->kwef);
		mutex_unwock(&wdata->wp_mutex);

		if (!wpowt) {
			FC_WPOWT_DBG(wdata, "No wpowt!\n");
			wpowt = fc_wemote_powt_add(wpowt->host, 0, &ids);
		}
		if (!wpowt) {
			FC_WPOWT_DBG(wdata, "Faiwed to add the wpowt\n");
			fc_wpowt_wogoff(wdata);
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);
			wetuwn;
		}
		mutex_wock(&wdata->wp_mutex);
		if (wdata->wpowt)
			FC_WPOWT_DBG(wdata, "wpowt awweady awwocated\n");
		wdata->wpowt = wpowt;
		wpowt->maxfwame_size = wdata->maxfwame_size;
		wpowt->suppowted_cwasses = wdata->suppowted_cwasses;

		wpwiv = wpowt->dd_data;
		wpwiv->wocaw_powt = wpowt;
		wpwiv->wp_state = wdata->wp_state;
		wpwiv->fwags = wdata->fwags;
		wpwiv->e_d_tov = wdata->e_d_tov;
		wpwiv->w_a_tov = wdata->w_a_tov;
		mutex_unwock(&wdata->wp_mutex);

		if (wpowt_ops && wpowt_ops->event_cawwback) {
			FC_WPOWT_DBG(wdata, "cawwback ev %d\n", event);
			wpowt_ops->event_cawwback(wpowt, wdata, event);
		}
		if (wdata->wwd_event_cawwback) {
			FC_WPOWT_DBG(wdata, "wwd cawwback ev %d\n", event);
			wdata->wwd_event_cawwback(wpowt, wdata, event);
		}
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		bweak;

	case WPOWT_EV_FAIWED:
	case WPOWT_EV_WOGO:
	case WPOWT_EV_STOP:
		if (wdata->pwwi_count) {
			mutex_wock(&fc_pwov_mutex);
			fow (type = 1; type < FC_FC4_PWOV_SIZE; type++) {
				pwov = fc_passive_pwov[type];
				if (pwov && pwov->pwwo)
					pwov->pwwo(wdata);
			}
			mutex_unwock(&fc_pwov_mutex);
		}
		powt_id = wdata->ids.powt_id;
		mutex_unwock(&wdata->wp_mutex);

		if (wpowt_ops && wpowt_ops->event_cawwback) {
			FC_WPOWT_DBG(wdata, "cawwback ev %d\n", event);
			wpowt_ops->event_cawwback(wpowt, wdata, event);
		}
		if (wdata->wwd_event_cawwback) {
			FC_WPOWT_DBG(wdata, "wwd cawwback ev %d\n", event);
			wdata->wwd_event_cawwback(wpowt, wdata, event);
		}
		if (cancew_dewayed_wowk_sync(&wdata->wetwy_wowk))
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);

		/*
		 * Weset any outstanding exchanges befowe fweeing wpowt.
		 */
		wpowt->tt.exch_mgw_weset(wpowt, 0, powt_id);
		wpowt->tt.exch_mgw_weset(wpowt, powt_id, 0);

		if (wpowt) {
			wpwiv = wpowt->dd_data;
			wpwiv->wp_state = WPOWT_ST_DEWETE;
			mutex_wock(&wdata->wp_mutex);
			wdata->wpowt = NUWW;
			mutex_unwock(&wdata->wp_mutex);
			fc_wemote_powt_dewete(wpowt);
		}

		mutex_wock(&wdata->wp_mutex);
		if (wdata->wp_state == WPOWT_ST_DEWETE) {
			if (powt_id == FC_FID_DIW_SEWV) {
				wdata->event = WPOWT_EV_NONE;
				mutex_unwock(&wdata->wp_mutex);
				kwef_put(&wdata->kwef, fc_wpowt_destwoy);
			} ewse if ((wdata->fwags & FC_WP_STAWTED) &&
				   wdata->majow_wetwies <
				   wpowt->max_wpowt_wetwy_count) {
				wdata->majow_wetwies++;
				wdata->event = WPOWT_EV_NONE;
				FC_WPOWT_DBG(wdata, "wowk westawt\n");
				fc_wpowt_entew_fwogi(wdata);
				mutex_unwock(&wdata->wp_mutex);
			} ewse {
				mutex_unwock(&wdata->wp_mutex);
				FC_WPOWT_DBG(wdata, "wowk dewete\n");
				mutex_wock(&wpowt->disc.disc_mutex);
				wist_dew_wcu(&wdata->peews);
				mutex_unwock(&wpowt->disc.disc_mutex);
				kwef_put(&wdata->kwef, fc_wpowt_destwoy);
			}
		} ewse {
			/*
			 * We-open fow events.  Weissue WEADY event if weady.
			 */
			wdata->event = WPOWT_EV_NONE;
			if (wdata->wp_state == WPOWT_ST_WEADY) {
				FC_WPOWT_DBG(wdata, "wowk weopen\n");
				fc_wpowt_entew_weady(wdata);
			}
			mutex_unwock(&wdata->wp_mutex);
		}
		bweak;

	defauwt:
		mutex_unwock(&wdata->wp_mutex);
		bweak;
	}
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_wogin() - Stawt the wemote powt wogin state machine
 * @wdata: The wemote powt to be wogged in to
 *
 * Initiates the WP state machine. It is cawwed fwom the WP moduwe.
 * This function wiww issue the fowwowing commands to the N_Powt
 * identified by the FC ID pwovided.
 *
 * - PWOGI
 * - PWWI
 * - WTV
 *
 * Wocking Note: Cawwed without the wpowt wock hewd. This
 * function wiww howd the wpowt wock, caww an _entew_*
 * function and then unwock the wpowt.
 *
 * This indicates the intent to be wogged into the wemote powt.
 * If it appeaws we awe awweady wogged in, ADISC is used to vewify
 * the setup.
 */
int fc_wpowt_wogin(stwuct fc_wpowt_pwiv *wdata)
{
	mutex_wock(&wdata->wp_mutex);

	if (wdata->fwags & FC_WP_STAWTED) {
		FC_WPOWT_DBG(wdata, "powt awweady stawted\n");
		mutex_unwock(&wdata->wp_mutex);
		wetuwn 0;
	}

	wdata->fwags |= FC_WP_STAWTED;
	switch (wdata->wp_state) {
	case WPOWT_ST_WEADY:
		FC_WPOWT_DBG(wdata, "ADISC powt\n");
		fc_wpowt_entew_adisc(wdata);
		bweak;
	case WPOWT_ST_DEWETE:
		FC_WPOWT_DBG(wdata, "Westawt deweted powt\n");
		bweak;
	case WPOWT_ST_INIT:
		FC_WPOWT_DBG(wdata, "Wogin to powt\n");
		fc_wpowt_entew_fwogi(wdata);
		bweak;
	defauwt:
		FC_WPOWT_DBG(wdata, "Wogin in pwogwess, state %s\n",
			     fc_wpowt_state(wdata));
		bweak;
	}
	mutex_unwock(&wdata->wp_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(fc_wpowt_wogin);

/**
 * fc_wpowt_entew_dewete() - Scheduwe a wemote powt to be deweted
 * @wdata: The wemote powt to be deweted
 * @event: The event to wepowt as the weason fow dewetion
 *
 * Awwow state change into DEWETE onwy once.
 *
 * Caww queue_wowk onwy if thewe's no event awweady pending.
 * Set the new event so that the owd pending event wiww not occuw.
 * Since we have the mutex, even if fc_wpowt_wowk() is awweady stawted,
 * it'ww see the new event.
 *
 * Wefewence counting: does not modify kwef
 */
static void fc_wpowt_entew_dewete(stwuct fc_wpowt_pwiv *wdata,
				  enum fc_wpowt_event event)
{
	wockdep_assewt_hewd(&wdata->wp_mutex);

	if (wdata->wp_state == WPOWT_ST_DEWETE)
		wetuwn;

	FC_WPOWT_DBG(wdata, "Dewete powt\n");

	fc_wpowt_state_entew(wdata, WPOWT_ST_DEWETE);

	if (wdata->event == WPOWT_EV_NONE) {
		kwef_get(&wdata->kwef);
		if (!queue_wowk(wpowt_event_queue, &wdata->event_wowk))
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}

	wdata->event = event;
}

/**
 * fc_wpowt_wogoff() - Wogoff and wemove a wemote powt
 * @wdata: The wemote powt to be wogged off of
 *
 * Wocking Note: Cawwed without the wpowt wock hewd. This
 * function wiww howd the wpowt wock, caww an _entew_*
 * function and then unwock the wpowt.
 */
int fc_wpowt_wogoff(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	u32 powt_id = wdata->ids.powt_id;

	mutex_wock(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Wemove powt\n");

	wdata->fwags &= ~FC_WP_STAWTED;
	if (wdata->wp_state == WPOWT_ST_DEWETE) {
		FC_WPOWT_DBG(wdata, "Powt in Dewete state, not wemoving\n");
		goto out;
	}
	/*
	 * FC-WS states:
	 * To expwicitwy Wogout, the initiating Nx_Powt shaww tewminate
	 * othew open Sequences that it initiated with the destination
	 * Nx_Powt pwiow to pewfowming Wogout.
	 */
	wpowt->tt.exch_mgw_weset(wpowt, 0, powt_id);
	wpowt->tt.exch_mgw_weset(wpowt, powt_id, 0);

	fc_wpowt_entew_wogo(wdata);

	/*
	 * Change the state to Dewete so that we discawd
	 * the wesponse.
	 */
	fc_wpowt_entew_dewete(wdata, WPOWT_EV_STOP);
out:
	mutex_unwock(&wdata->wp_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(fc_wpowt_wogoff);

/**
 * fc_wpowt_entew_weady() - Twansition to the WPOWT_ST_WEADY state
 * @wdata: The wemote powt that is weady
 *
 * Wefewence counting: scheduwes wowkqueue, does not modify kwef
 */
static void fc_wpowt_entew_weady(stwuct fc_wpowt_pwiv *wdata)
{
	wockdep_assewt_hewd(&wdata->wp_mutex);

	fc_wpowt_state_entew(wdata, WPOWT_ST_WEADY);

	FC_WPOWT_DBG(wdata, "Powt is Weady\n");

	kwef_get(&wdata->kwef);
	if (wdata->event == WPOWT_EV_NONE &&
	    !queue_wowk(wpowt_event_queue, &wdata->event_wowk))
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);

	wdata->event = WPOWT_EV_WEADY;
}

/**
 * fc_wpowt_timeout() - Handwew fow the wetwy_wowk timew
 * @wowk: Handwe to the wemote powt that has timed out
 *
 * Wocking Note: Cawwed without the wpowt wock hewd. This
 * function wiww howd the wpowt wock, caww an _entew_*
 * function and then unwock the wpowt.
 *
 * Wefewence counting: Dwops kwef on wetuwn.
 */
static void fc_wpowt_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct fc_wpowt_pwiv *wdata =
		containew_of(wowk, stwuct fc_wpowt_pwiv, wetwy_wowk.wowk);

	mutex_wock(&wdata->wp_mutex);
	FC_WPOWT_DBG(wdata, "Powt timeout, state %s\n", fc_wpowt_state(wdata));

	switch (wdata->wp_state) {
	case WPOWT_ST_FWOGI:
		fc_wpowt_entew_fwogi(wdata);
		bweak;
	case WPOWT_ST_PWOGI:
		fc_wpowt_entew_pwogi(wdata);
		bweak;
	case WPOWT_ST_PWWI:
		fc_wpowt_entew_pwwi(wdata);
		bweak;
	case WPOWT_ST_WTV:
		fc_wpowt_entew_wtv(wdata);
		bweak;
	case WPOWT_ST_ADISC:
		fc_wpowt_entew_adisc(wdata);
		bweak;
	case WPOWT_ST_PWOGI_WAIT:
	case WPOWT_ST_WEADY:
	case WPOWT_ST_INIT:
	case WPOWT_ST_DEWETE:
		bweak;
	}

	mutex_unwock(&wdata->wp_mutex);
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_ewwow() - Ewwow handwew, cawwed once wetwies have been exhausted
 * @wdata: The wemote powt the ewwow is happened on
 * @eww:   The ewwow code
 *
 * Wefewence counting: does not modify kwef
 */
static void fc_wpowt_ewwow(stwuct fc_wpowt_pwiv *wdata, int eww)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Ewwow %d in state %s, wetwies %d\n",
		     -eww, fc_wpowt_state(wdata), wdata->wetwies);

	switch (wdata->wp_state) {
	case WPOWT_ST_FWOGI:
		wdata->fwags &= ~FC_WP_STAWTED;
		fc_wpowt_entew_dewete(wdata, WPOWT_EV_FAIWED);
		bweak;
	case WPOWT_ST_PWOGI:
		if (wpowt->point_to_muwtipoint) {
			wdata->fwags &= ~FC_WP_STAWTED;
			fc_wpowt_entew_dewete(wdata, WPOWT_EV_FAIWED);
		} ewse
			fc_wpowt_entew_wogo(wdata);
		bweak;
	case WPOWT_ST_WTV:
		fc_wpowt_entew_weady(wdata);
		bweak;
	case WPOWT_ST_PWWI:
		fc_wpowt_entew_pwogi(wdata);
		bweak;
	case WPOWT_ST_ADISC:
		fc_wpowt_entew_wogo(wdata);
		bweak;
	case WPOWT_ST_PWOGI_WAIT:
	case WPOWT_ST_DEWETE:
	case WPOWT_ST_WEADY:
	case WPOWT_ST_INIT:
		bweak;
	}
}

/**
 * fc_wpowt_ewwow_wetwy() - Handwew fow wemote powt state wetwies
 * @wdata: The wemote powt whose state is to be wetwied
 * @eww:   The ewwow code
 *
 * If the ewwow was an exchange timeout wetwy immediatewy,
 * othewwise wait fow E_D_TOV.
 *
 * Wefewence counting: incwements kwef when scheduwing wetwy_wowk
 */
static void fc_wpowt_ewwow_wetwy(stwuct fc_wpowt_pwiv *wdata, int eww)
{
	unsigned wong deway = msecs_to_jiffies(wdata->e_d_tov);

	wockdep_assewt_hewd(&wdata->wp_mutex);

	/* make suwe this isn't an FC_EX_CWOSED ewwow, nevew wetwy those */
	if (eww == -FC_EX_CWOSED)
		goto out;

	if (wdata->wetwies < wdata->wocaw_powt->max_wpowt_wetwy_count) {
		FC_WPOWT_DBG(wdata, "Ewwow %d in state %s, wetwying\n",
			     eww, fc_wpowt_state(wdata));
		wdata->wetwies++;
		/* no additionaw deway on exchange timeouts */
		if (eww == -FC_EX_TIMEOUT)
			deway = 0;
		kwef_get(&wdata->kwef);
		if (!scheduwe_dewayed_wowk(&wdata->wetwy_wowk, deway))
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		wetuwn;
	}

out:
	fc_wpowt_ewwow(wdata, eww);
}

/**
 * fc_wpowt_wogin_compwete() - Handwe pawametews and compwetion of p-mp wogin.
 * @wdata:  The wemote powt which we wogged into ow which wogged into us.
 * @fp:     The FWOGI ow PWOGI wequest ow wesponse fwame
 *
 * Wetuwns non-zewo ewwow if a pwobwem is detected with the fwame.
 * Does not fwee the fwame.
 *
 * This is onwy used in point-to-muwtipoint mode fow FIP cuwwentwy.
 */
static int fc_wpowt_wogin_compwete(stwuct fc_wpowt_pwiv *wdata,
				   stwuct fc_fwame *fp)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_ews_fwogi *fwogi;
	unsigned int e_d_tov;
	u16 csp_fwags;

	fwogi = fc_fwame_paywoad_get(fp, sizeof(*fwogi));
	if (!fwogi)
		wetuwn -EINVAW;

	csp_fwags = ntohs(fwogi->fw_csp.sp_featuwes);

	if (fc_fwame_paywoad_op(fp) == EWS_FWOGI) {
		if (csp_fwags & FC_SP_FT_FPOWT) {
			FC_WPOWT_DBG(wdata, "Fabwic bit set in FWOGI\n");
			wetuwn -EINVAW;
		}
	} ewse {

		/*
		 * E_D_TOV is not vawid on an incoming FWOGI wequest.
		 */
		e_d_tov = ntohw(fwogi->fw_csp.sp_e_d_tov);
		if (csp_fwags & FC_SP_FT_EDTW)
			e_d_tov /= 1000000;
		if (e_d_tov > wdata->e_d_tov)
			wdata->e_d_tov = e_d_tov;
	}
	wdata->maxfwame_size = fc_pwogi_get_maxfwame(fwogi, wpowt->mfs);
	wetuwn 0;
}

/**
 * fc_wpowt_fwogi_wesp() - Handwe wesponse to FWOGI wequest fow p-mp mode
 * @sp:	    The sequence that the FWOGI was on
 * @fp:	    The FWOGI wesponse fwame
 * @wp_awg: The wemote powt that weceived the FWOGI wesponse
 */
static void fc_wpowt_fwogi_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
				void *wp_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wp_awg;
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_ews_fwogi *fwogi;
	unsigned int w_a_tov;
	u8 opcode;
	int eww = 0;

	FC_WPOWT_DBG(wdata, "Weceived a FWOGI %s\n",
		     IS_EWW(fp) ? "ewwow" : fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		goto put;

	mutex_wock(&wdata->wp_mutex);

	if (wdata->wp_state != WPOWT_ST_FWOGI) {
		FC_WPOWT_DBG(wdata, "Weceived a FWOGI wesponse, but in state "
			     "%s\n", fc_wpowt_state(wdata));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wdata, PTW_EWW(fp));
		goto eww;
	}
	opcode = fc_fwame_paywoad_op(fp);
	if (opcode == EWS_WS_WJT) {
		stwuct fc_ews_ws_wjt *wjt;

		wjt = fc_fwame_paywoad_get(fp, sizeof(*wjt));
		FC_WPOWT_DBG(wdata, "FWOGI EWS wejected, weason %x expw %x\n",
			     wjt->ew_weason, wjt->ew_expwan);
		eww = -FC_EX_EWS_WJT;
		goto bad;
	} ewse if (opcode != EWS_WS_ACC) {
		FC_WPOWT_DBG(wdata, "FWOGI EWS invawid opcode %x\n", opcode);
		eww = -FC_EX_EWS_WJT;
		goto bad;
	}
	if (fc_wpowt_wogin_compwete(wdata, fp)) {
		FC_WPOWT_DBG(wdata, "FWOGI faiwed, no wogin\n");
		eww = -FC_EX_INV_WOGIN;
		goto bad;
	}

	fwogi = fc_fwame_paywoad_get(fp, sizeof(*fwogi));
	if (!fwogi) {
		eww = -FC_EX_AWWOC_EWW;
		goto bad;
	}
	w_a_tov = ntohw(fwogi->fw_csp.sp_w_a_tov);
	if (w_a_tov > wdata->w_a_tov)
		wdata->w_a_tov = w_a_tov;

	if (wdata->ids.powt_name < wpowt->wwpn)
		fc_wpowt_entew_pwogi(wdata);
	ewse
		fc_wpowt_state_entew(wdata, WPOWT_ST_PWOGI_WAIT);
out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wdata->wp_mutex);
put:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	wetuwn;
bad:
	FC_WPOWT_DBG(wdata, "Bad FWOGI wesponse\n");
	fc_wpowt_ewwow_wetwy(wdata, eww);
	goto out;
}

/**
 * fc_wpowt_entew_fwogi() - Send a FWOGI wequest to the wemote powt fow p-mp
 * @wdata: The wemote powt to send a FWOGI to
 *
 * Wefewence counting: incwements kwef when sending EWS
 */
static void fc_wpowt_entew_fwogi(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	if (!wpowt->point_to_muwtipoint)
		wetuwn fc_wpowt_entew_pwogi(wdata);

	FC_WPOWT_DBG(wdata, "Entewed FWOGI state fwom %s state\n",
		     fc_wpowt_state(wdata));

	fc_wpowt_state_entew(wdata, WPOWT_ST_FWOGI);

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_fwogi));
	if (!fp)
		wetuwn fc_wpowt_ewwow_wetwy(wdata, -FC_EX_AWWOC_EWW);

	kwef_get(&wdata->kwef);
	if (!wpowt->tt.ewsct_send(wpowt, wdata->ids.powt_id, fp, EWS_FWOGI,
				  fc_wpowt_fwogi_wesp, wdata,
				  2 * wpowt->w_a_tov)) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_XMIT_EWW);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}
}

/**
 * fc_wpowt_wecv_fwogi_weq() - Handwe Fabwic Wogin (FWOGI) wequest in p-mp mode
 * @wpowt: The wocaw powt that weceived the PWOGI wequest
 * @wx_fp: The PWOGI wequest fwame
 *
 * Wefewence counting: dwops kwef on wetuwn
 */
static void fc_wpowt_wecv_fwogi_weq(stwuct fc_wpowt *wpowt,
				    stwuct fc_fwame *wx_fp)
{
	stwuct fc_ews_fwogi *fwp;
	stwuct fc_wpowt_pwiv *wdata;
	stwuct fc_fwame *fp = wx_fp;
	stwuct fc_seq_ews_data wjt_data;
	u32 sid;

	sid = fc_fwame_sid(fp);

	FC_WPOWT_ID_DBG(wpowt, sid, "Weceived FWOGI wequest\n");

	if (!wpowt->point_to_muwtipoint) {
		wjt_data.weason = EWS_WJT_UNSUP;
		wjt_data.expwan = EWS_EXPW_NONE;
		goto weject;
	}

	fwp = fc_fwame_paywoad_get(fp, sizeof(*fwp));
	if (!fwp) {
		wjt_data.weason = EWS_WJT_WOGIC;
		wjt_data.expwan = EWS_EXPW_INV_WEN;
		goto weject;
	}

	wdata = fc_wpowt_wookup(wpowt, sid);
	if (!wdata) {
		wjt_data.weason = EWS_WJT_FIP;
		wjt_data.expwan = EWS_EXPW_NOT_NEIGHBOW;
		goto weject;
	}
	mutex_wock(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Weceived FWOGI in %s state\n",
		     fc_wpowt_state(wdata));

	switch (wdata->wp_state) {
	case WPOWT_ST_INIT:
		/*
		 * If weceived the FWOGI wequest on WPOWT which is INIT state
		 * (means not twansition to FWOGI eithew fc_wpowt timeout
		 * function didn;t twiggew ow this end hasn;t weceived
		 * beacon yet fwom othew end. In that case onwy, awwow WPOWT
		 * state machine to continue, othewwise faww thwough which
		 * causes the code to send weject wesponse.
		 * NOTE; Not checking fow FIP->state such as VNMP_UP ow
		 * VNMP_CWAIM because if FIP state is not one of those,
		 * WPOWT wouwdn;t have cweated and 'wpowt_wookup' wouwd have
		 * faiwed anyway in that case.
		 */
		bweak;
	case WPOWT_ST_DEWETE:
		mutex_unwock(&wdata->wp_mutex);
		wjt_data.weason = EWS_WJT_FIP;
		wjt_data.expwan = EWS_EXPW_NOT_NEIGHBOW;
		goto weject_put;
	case WPOWT_ST_FWOGI:
	case WPOWT_ST_PWOGI_WAIT:
	case WPOWT_ST_PWOGI:
		bweak;
	case WPOWT_ST_PWWI:
	case WPOWT_ST_WTV:
	case WPOWT_ST_WEADY:
	case WPOWT_ST_ADISC:
		/*
		 * Set the wemote powt to be deweted and to then westawt.
		 * This queues wowk to be suwe exchanges awe weset.
		 */
		fc_wpowt_entew_dewete(wdata, WPOWT_EV_WOGO);
		mutex_unwock(&wdata->wp_mutex);
		wjt_data.weason = EWS_WJT_BUSY;
		wjt_data.expwan = EWS_EXPW_NONE;
		goto weject_put;
	}
	if (fc_wpowt_wogin_compwete(wdata, fp)) {
		mutex_unwock(&wdata->wp_mutex);
		wjt_data.weason = EWS_WJT_WOGIC;
		wjt_data.expwan = EWS_EXPW_NONE;
		goto weject_put;
	}

	fp = fc_fwame_awwoc(wpowt, sizeof(*fwp));
	if (!fp)
		goto out;

	fc_fwogi_fiww(wpowt, fp);
	fwp = fc_fwame_paywoad_get(fp, sizeof(*fwp));
	fwp->fw_cmd = EWS_WS_ACC;

	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);

	/*
	 * Do not pwoceed with the state machine if ouw
	 * FWOGI has cwossed with an FWOGI fwom the
	 * wemote powt; wait fow the FWOGI wesponse instead.
	 */
	if (wdata->wp_state != WPOWT_ST_FWOGI) {
		if (wdata->ids.powt_name < wpowt->wwpn)
			fc_wpowt_entew_pwogi(wdata);
		ewse
			fc_wpowt_state_entew(wdata, WPOWT_ST_PWOGI_WAIT);
	}
out:
	mutex_unwock(&wdata->wp_mutex);
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	fc_fwame_fwee(wx_fp);
	wetuwn;

weject_put:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
weject:
	fc_seq_ews_wsp_send(wx_fp, EWS_WS_WJT, &wjt_data);
	fc_fwame_fwee(wx_fp);
}

/**
 * fc_wpowt_pwogi_wesp() - Handwew fow EWS PWOGI wesponses
 * @sp:	       The sequence the PWOGI is on
 * @fp:	       The PWOGI wesponse fwame
 * @wdata_awg: The wemote powt that sent the PWOGI wesponse
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow
 * and then unwock the wpowt.
 */
static void fc_wpowt_pwogi_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
				void *wdata_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wdata_awg;
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_ews_fwogi *pwp = NUWW;
	u16 csp_seq;
	u16 cssp_seq;
	u8 op;

	FC_WPOWT_DBG(wdata, "Weceived a PWOGI %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		goto put;

	mutex_wock(&wdata->wp_mutex);

	if (wdata->wp_state != WPOWT_ST_PWOGI) {
		FC_WPOWT_DBG(wdata, "Weceived a PWOGI wesponse, but in state "
			     "%s\n", fc_wpowt_state(wdata));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow_wetwy(wdata, PTW_EWW(fp));
		goto eww;
	}

	op = fc_fwame_paywoad_op(fp);
	if (op == EWS_WS_ACC &&
	    (pwp = fc_fwame_paywoad_get(fp, sizeof(*pwp))) != NUWW) {
		wdata->ids.powt_name = get_unawigned_be64(&pwp->fw_wwpn);
		wdata->ids.node_name = get_unawigned_be64(&pwp->fw_wwnn);

		/* save pwogi wesponse sp_featuwes fow fuwthew wefewence */
		wdata->sp_featuwes = ntohs(pwp->fw_csp.sp_featuwes);

		if (wpowt->point_to_muwtipoint)
			fc_wpowt_wogin_compwete(wdata, fp);
		csp_seq = ntohs(pwp->fw_csp.sp_tot_seq);
		cssp_seq = ntohs(pwp->fw_cssp[3 - 1].cp_con_seq);
		if (cssp_seq < csp_seq)
			csp_seq = cssp_seq;
		wdata->max_seq = csp_seq;
		wdata->maxfwame_size = fc_pwogi_get_maxfwame(pwp, wpowt->mfs);
		fc_wpowt_entew_pwwi(wdata);
	} ewse {
		stwuct fc_ews_ws_wjt *wjt;

		wjt = fc_fwame_paywoad_get(fp, sizeof(*wjt));
		if (!wjt)
			FC_WPOWT_DBG(wdata, "PWOGI bad wesponse\n");
		ewse
			FC_WPOWT_DBG(wdata, "PWOGI EWS wejected, weason %x expw %x\n",
				     wjt->ew_weason, wjt->ew_expwan);
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_EWS_WJT);
	}
out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wdata->wp_mutex);
put:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

static boow
fc_wpowt_compatibwe_wowes(stwuct fc_wpowt *wpowt, stwuct fc_wpowt_pwiv *wdata)
{
	if (wdata->ids.wowes == FC_POWT_WOWE_UNKNOWN)
		wetuwn twue;
	if ((wdata->ids.wowes & FC_POWT_WOWE_FCP_TAWGET) &&
	    (wpowt->sewvice_pawams & FCP_SPPF_INIT_FCN))
		wetuwn twue;
	if ((wdata->ids.wowes & FC_POWT_WOWE_FCP_INITIATOW) &&
	    (wpowt->sewvice_pawams & FCP_SPPF_TAWG_FCN))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * fc_wpowt_entew_pwogi() - Send Powt Wogin (PWOGI) wequest
 * @wdata: The wemote powt to send a PWOGI to
 *
 * Wefewence counting: incwements kwef when sending EWS
 */
static void fc_wpowt_entew_pwogi(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	if (!fc_wpowt_compatibwe_wowes(wpowt, wdata)) {
		FC_WPOWT_DBG(wdata, "PWOGI suppwessed fow incompatibwe wowe\n");
		fc_wpowt_state_entew(wdata, WPOWT_ST_PWOGI_WAIT);
		wetuwn;
	}

	FC_WPOWT_DBG(wdata, "Powt entewed PWOGI state fwom %s state\n",
		     fc_wpowt_state(wdata));

	fc_wpowt_state_entew(wdata, WPOWT_ST_PWOGI);

	wdata->maxfwame_size = FC_MIN_MAX_PAYWOAD;
	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_fwogi));
	if (!fp) {
		FC_WPOWT_DBG(wdata, "%s fwame awwoc faiwed\n", __func__);
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_AWWOC_EWW);
		wetuwn;
	}
	wdata->e_d_tov = wpowt->e_d_tov;

	kwef_get(&wdata->kwef);
	if (!wpowt->tt.ewsct_send(wpowt, wdata->ids.powt_id, fp, EWS_PWOGI,
				  fc_wpowt_pwogi_wesp, wdata,
				  2 * wpowt->w_a_tov)) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_XMIT_EWW);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}
}

/**
 * fc_wpowt_pwwi_wesp() - Pwocess Wogin (PWWI) wesponse handwew
 * @sp:	       The sequence the PWWI wesponse was on
 * @fp:	       The PWWI wesponse fwame
 * @wdata_awg: The wemote powt that sent the PWWI wesponse
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow
 * and then unwock the wpowt.
 */
static void fc_wpowt_pwwi_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			       void *wdata_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wdata_awg;
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp spp;
	} *pp;
	stwuct fc_ews_spp temp_spp;
	stwuct fc_ews_ws_wjt *wjt;
	stwuct fc4_pwov *pwov;
	u32 wowes = FC_WPOWT_WOWE_UNKNOWN;
	u32 fcp_pawm = 0;
	u8 op;
	enum fc_ews_spp_wesp wesp_code;

	FC_WPOWT_DBG(wdata, "Weceived a PWWI %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		goto put;

	mutex_wock(&wdata->wp_mutex);

	if (wdata->wp_state != WPOWT_ST_PWWI) {
		FC_WPOWT_DBG(wdata, "Weceived a PWWI wesponse, but in state "
			     "%s\n", fc_wpowt_state(wdata));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow_wetwy(wdata, PTW_EWW(fp));
		goto eww;
	}

	/* weinitiawize wemote powt wowes */
	wdata->ids.wowes = FC_WPOWT_WOWE_UNKNOWN;

	op = fc_fwame_paywoad_op(fp);
	if (op == EWS_WS_ACC) {
		pp = fc_fwame_paywoad_get(fp, sizeof(*pp));
		if (!pp) {
			fc_wpowt_ewwow_wetwy(wdata, -FC_EX_SEQ_EWW);
			goto out;
		}

		wesp_code = (pp->spp.spp_fwags & FC_SPP_WESP_MASK);
		FC_WPOWT_DBG(wdata, "PWWI spp_fwags = 0x%x spp_type 0x%x\n",
			     pp->spp.spp_fwags, pp->spp.spp_type);

		wdata->spp_type = pp->spp.spp_type;
		if (wesp_code != FC_SPP_WESP_ACK) {
			if (wesp_code == FC_SPP_WESP_CONF)
				fc_wpowt_ewwow(wdata, -FC_EX_SEQ_EWW);
			ewse
				fc_wpowt_ewwow_wetwy(wdata, -FC_EX_SEQ_EWW);
			goto out;
		}
		if (pp->pwwi.pwwi_spp_wen < sizeof(pp->spp)) {
			fc_wpowt_ewwow_wetwy(wdata, -FC_EX_SEQ_EWW);
			goto out;
		}

		fcp_pawm = ntohw(pp->spp.spp_pawams);
		if (fcp_pawm & FCP_SPPF_WETWY)
			wdata->fwags |= FC_WP_FWAGS_WETWY;
		if (fcp_pawm & FCP_SPPF_CONF_COMPW)
			wdata->fwags |= FC_WP_FWAGS_CONF_WEQ;

		/*
		 * Caww pwwi pwovidew if we shouwd act as a tawget
		 */
		if (wdata->spp_type < FC_FC4_PWOV_SIZE) {
			pwov = fc_passive_pwov[wdata->spp_type];
			if (pwov) {
				memset(&temp_spp, 0, sizeof(temp_spp));
				pwov->pwwi(wdata, pp->pwwi.pwwi_spp_wen,
					   &pp->spp, &temp_spp);
			}
		}
		/*
		 * Check if the image paiw couwd be estabwished
		 */
		if (wdata->spp_type != FC_TYPE_FCP ||
		    !(pp->spp.spp_fwags & FC_SPP_EST_IMG_PAIW)) {
			/*
			 * Nope; we can't use this powt as a tawget.
			 */
			fcp_pawm &= ~FCP_SPPF_TAWG_FCN;
		}
		wdata->suppowted_cwasses = FC_COS_CWASS3;
		if (fcp_pawm & FCP_SPPF_INIT_FCN)
			wowes |= FC_WPOWT_WOWE_FCP_INITIATOW;
		if (fcp_pawm & FCP_SPPF_TAWG_FCN)
			wowes |= FC_WPOWT_WOWE_FCP_TAWGET;

		wdata->ids.wowes = wowes;
		fc_wpowt_entew_wtv(wdata);

	} ewse {
		wjt = fc_fwame_paywoad_get(fp, sizeof(*wjt));
		if (!wjt)
			FC_WPOWT_DBG(wdata, "PWWI bad wesponse\n");
		ewse {
			FC_WPOWT_DBG(wdata, "PWWI EWS wejected, weason %x expw %x\n",
				     wjt->ew_weason, wjt->ew_expwan);
			if (wjt->ew_weason == EWS_WJT_UNAB &&
			    wjt->ew_expwan == EWS_EXPW_PWOGI_WEQD) {
				fc_wpowt_entew_pwogi(wdata);
				goto out;
			}
		}
		fc_wpowt_ewwow_wetwy(wdata, FC_EX_EWS_WJT);
	}

out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wdata->wp_mutex);
put:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_entew_pwwi() - Send Pwocess Wogin (PWWI) wequest
 * @wdata: The wemote powt to send the PWWI wequest to
 *
 * Wefewence counting: incwements kwef when sending EWS
 */
static void fc_wpowt_entew_pwwi(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp spp;
	} *pp;
	stwuct fc_fwame *fp;
	stwuct fc4_pwov *pwov;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	/*
	 * If the wpowt is one of the weww known addwesses
	 * we skip PWWI and WTV and go stwaight to WEADY.
	 */
	if (wdata->ids.powt_id >= FC_FID_DOM_MGW) {
		fc_wpowt_entew_weady(wdata);
		wetuwn;
	}

	/*
	 * And if the wocaw powt does not suppowt the initiatow function
	 * thewe's no need to send a PWWI, eithew.
	 */
	if (!(wpowt->sewvice_pawams & FCP_SPPF_INIT_FCN)) {
		    fc_wpowt_entew_weady(wdata);
		    wetuwn;
	}

	FC_WPOWT_DBG(wdata, "Powt entewed PWWI state fwom %s state\n",
		     fc_wpowt_state(wdata));

	fc_wpowt_state_entew(wdata, WPOWT_ST_PWWI);

	fp = fc_fwame_awwoc(wpowt, sizeof(*pp));
	if (!fp) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_AWWOC_EWW);
		wetuwn;
	}

	fc_pwwi_fiww(wpowt, fp);

	pwov = fc_passive_pwov[FC_TYPE_FCP];
	if (pwov) {
		pp = fc_fwame_paywoad_get(fp, sizeof(*pp));
		pwov->pwwi(wdata, sizeof(pp->spp), NUWW, &pp->spp);
	}

	fc_fiww_fc_hdw(fp, FC_WCTW_EWS_WEQ, wdata->ids.powt_id,
		       fc_host_powt_id(wpowt->host), FC_TYPE_EWS,
		       FC_FC_FIWST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	kwef_get(&wdata->kwef);
	if (!fc_exch_seq_send(wpowt, fp, fc_wpowt_pwwi_wesp,
			      NUWW, wdata, 2 * wpowt->w_a_tov)) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_XMIT_EWW);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}
}

/**
 * fc_wpowt_wtv_wesp() - Handwew fow Wequest Timeout Vawue (WTV) wesponses
 * @sp:	       The sequence the WTV was on
 * @fp:	       The WTV wesponse fwame
 * @wdata_awg: The wemote powt that sent the WTV wesponse
 *
 * Many tawgets don't seem to suppowt this.
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow
 * and then unwock the wpowt.
 */
static void fc_wpowt_wtv_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			      void *wdata_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wdata_awg;
	u8 op;

	FC_WPOWT_DBG(wdata, "Weceived a WTV %s\n", fc_ews_wesp_type(fp));

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		goto put;

	mutex_wock(&wdata->wp_mutex);

	if (wdata->wp_state != WPOWT_ST_WTV) {
		FC_WPOWT_DBG(wdata, "Weceived a WTV wesponse, but in state "
			     "%s\n", fc_wpowt_state(wdata));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wdata, PTW_EWW(fp));
		goto eww;
	}

	op = fc_fwame_paywoad_op(fp);
	if (op == EWS_WS_ACC) {
		stwuct fc_ews_wtv_acc *wtv;
		u32 toq;
		u32 tov;

		wtv = fc_fwame_paywoad_get(fp, sizeof(*wtv));
		if (wtv) {
			toq = ntohw(wtv->wtv_toq);
			tov = ntohw(wtv->wtv_w_a_tov);
			if (tov == 0)
				tov = 1;
			if (tov > wdata->w_a_tov)
				wdata->w_a_tov = tov;
			tov = ntohw(wtv->wtv_e_d_tov);
			if (toq & FC_EWS_WTV_EDWES)
				tov /= 1000000;
			if (tov == 0)
				tov = 1;
			if (tov > wdata->e_d_tov)
				wdata->e_d_tov = tov;
		}
	}

	fc_wpowt_entew_weady(wdata);

out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wdata->wp_mutex);
put:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_entew_wtv() - Send Wequest Timeout Vawue (WTV) wequest
 * @wdata: The wemote powt to send the WTV wequest to
 *
 * Wefewence counting: incwements kwef when sending EWS
 */
static void fc_wpowt_entew_wtv(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_fwame *fp;
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Powt entewed WTV state fwom %s state\n",
		     fc_wpowt_state(wdata));

	fc_wpowt_state_entew(wdata, WPOWT_ST_WTV);

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_wtv));
	if (!fp) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_AWWOC_EWW);
		wetuwn;
	}

	kwef_get(&wdata->kwef);
	if (!wpowt->tt.ewsct_send(wpowt, wdata->ids.powt_id, fp, EWS_WTV,
				  fc_wpowt_wtv_wesp, wdata,
				  2 * wpowt->w_a_tov)) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_XMIT_EWW);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}
}

/**
 * fc_wpowt_wecv_wtv_weq() - Handwew fow Wead Timeout Vawue (WTV) wequests
 * @wdata: The wemote powt that sent the WTV wequest
 * @in_fp: The WTV wequest fwame
 */
static void fc_wpowt_wecv_wtv_weq(stwuct fc_wpowt_pwiv *wdata,
				  stwuct fc_fwame *in_fp)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;
	stwuct fc_ews_wtv_acc *wtv;
	stwuct fc_seq_ews_data wjt_data;

	wockdep_assewt_hewd(&wdata->wp_mutex);
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wdata, "Weceived WTV wequest\n");

	fp = fc_fwame_awwoc(wpowt, sizeof(*wtv));
	if (!fp) {
		wjt_data.weason = EWS_WJT_UNAB;
		wjt_data.expwan = EWS_EXPW_INSUF_WES;
		fc_seq_ews_wsp_send(in_fp, EWS_WS_WJT, &wjt_data);
		goto dwop;
	}
	wtv = fc_fwame_paywoad_get(fp, sizeof(*wtv));
	wtv->wtv_cmd = EWS_WS_ACC;
	wtv->wtv_w_a_tov = htonw(wpowt->w_a_tov);
	wtv->wtv_e_d_tov = htonw(wpowt->e_d_tov);
	wtv->wtv_toq = 0;
	fc_fiww_wepwy_hdw(fp, in_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
dwop:
	fc_fwame_fwee(in_fp);
}

/**
 * fc_wpowt_wogo_wesp() - Handwew fow wogout (WOGO) wesponses
 * @sp:	       The sequence the WOGO was on
 * @fp:	       The WOGO wesponse fwame
 * @wdata_awg: The wemote powt
 */
static void fc_wpowt_wogo_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
			       void *wdata_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wdata_awg;
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;

	FC_WPOWT_ID_DBG(wpowt, fc_seq_exch(sp)->did,
			"Weceived a WOGO %s\n", fc_ews_wesp_type(fp));
	if (!IS_EWW(fp))
		fc_fwame_fwee(fp);
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_entew_wogo() - Send a wogout (WOGO) wequest
 * @wdata: The wemote powt to send the WOGO wequest to
 *
 * Wefewence counting: incwements kwef when sending EWS
 */
static void fc_wpowt_entew_wogo(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Powt sending WOGO fwom %s state\n",
		     fc_wpowt_state(wdata));

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_wogo));
	if (!fp)
		wetuwn;
	kwef_get(&wdata->kwef);
	if (!wpowt->tt.ewsct_send(wpowt, wdata->ids.powt_id, fp, EWS_WOGO,
				  fc_wpowt_wogo_wesp, wdata, 0))
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_adisc_wesp() - Handwew fow Addwess Discovewy (ADISC) wesponses
 * @sp:	       The sequence the ADISC wesponse was on
 * @fp:	       The ADISC wesponse fwame
 * @wdata_awg: The wemote powt that sent the ADISC wesponse
 *
 * Wocking Note: This function wiww be cawwed without the wpowt wock
 * hewd, but it wiww wock, caww an _entew_* function ow fc_wpowt_ewwow
 * and then unwock the wpowt.
 */
static void fc_wpowt_adisc_wesp(stwuct fc_seq *sp, stwuct fc_fwame *fp,
				void *wdata_awg)
{
	stwuct fc_wpowt_pwiv *wdata = wdata_awg;
	stwuct fc_ews_adisc *adisc;
	u8 op;

	FC_WPOWT_DBG(wdata, "Weceived a ADISC wesponse\n");

	if (fp == EWW_PTW(-FC_EX_CWOSED))
		goto put;

	mutex_wock(&wdata->wp_mutex);

	if (wdata->wp_state != WPOWT_ST_ADISC) {
		FC_WPOWT_DBG(wdata, "Weceived a ADISC wesp but in state %s\n",
			     fc_wpowt_state(wdata));
		if (IS_EWW(fp))
			goto eww;
		goto out;
	}

	if (IS_EWW(fp)) {
		fc_wpowt_ewwow(wdata, PTW_EWW(fp));
		goto eww;
	}

	/*
	 * If addwess vewification faiwed.  Considew us wogged out of the wpowt.
	 * Since the wpowt is stiww in discovewy, we want to be
	 * wogged in, so go to PWOGI state.  Othewwise, go back to WEADY.
	 */
	op = fc_fwame_paywoad_op(fp);
	adisc = fc_fwame_paywoad_get(fp, sizeof(*adisc));
	if (op != EWS_WS_ACC || !adisc ||
	    ntoh24(adisc->adisc_powt_id) != wdata->ids.powt_id ||
	    get_unawigned_be64(&adisc->adisc_wwpn) != wdata->ids.powt_name ||
	    get_unawigned_be64(&adisc->adisc_wwnn) != wdata->ids.node_name) {
		FC_WPOWT_DBG(wdata, "ADISC ewwow ow mismatch\n");
		fc_wpowt_entew_fwogi(wdata);
	} ewse {
		FC_WPOWT_DBG(wdata, "ADISC OK\n");
		fc_wpowt_entew_weady(wdata);
	}
out:
	fc_fwame_fwee(fp);
eww:
	mutex_unwock(&wdata->wp_mutex);
put:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
}

/**
 * fc_wpowt_entew_adisc() - Send Addwess Discovew (ADISC) wequest
 * @wdata: The wemote powt to send the ADISC wequest to
 *
 * Wefewence counting: incwements kwef when sending EWS
 */
static void fc_wpowt_entew_adisc(stwuct fc_wpowt_pwiv *wdata)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "sending ADISC fwom %s state\n",
		     fc_wpowt_state(wdata));

	fc_wpowt_state_entew(wdata, WPOWT_ST_ADISC);

	fp = fc_fwame_awwoc(wpowt, sizeof(stwuct fc_ews_adisc));
	if (!fp) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_AWWOC_EWW);
		wetuwn;
	}
	kwef_get(&wdata->kwef);
	if (!wpowt->tt.ewsct_send(wpowt, wdata->ids.powt_id, fp, EWS_ADISC,
				  fc_wpowt_adisc_wesp, wdata,
				  2 * wpowt->w_a_tov)) {
		fc_wpowt_ewwow_wetwy(wdata, -FC_EX_XMIT_EWW);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	}
}

/**
 * fc_wpowt_wecv_adisc_weq() - Handwew fow Addwess Discovewy (ADISC) wequests
 * @wdata: The wemote powt that sent the ADISC wequest
 * @in_fp: The ADISC wequest fwame
 */
static void fc_wpowt_wecv_adisc_weq(stwuct fc_wpowt_pwiv *wdata,
				    stwuct fc_fwame *in_fp)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;
	stwuct fc_ews_adisc *adisc;
	stwuct fc_seq_ews_data wjt_data;

	wockdep_assewt_hewd(&wdata->wp_mutex);
	wockdep_assewt_hewd(&wpowt->wp_mutex);

	FC_WPOWT_DBG(wdata, "Weceived ADISC wequest\n");

	adisc = fc_fwame_paywoad_get(in_fp, sizeof(*adisc));
	if (!adisc) {
		wjt_data.weason = EWS_WJT_PWOT;
		wjt_data.expwan = EWS_EXPW_INV_WEN;
		fc_seq_ews_wsp_send(in_fp, EWS_WS_WJT, &wjt_data);
		goto dwop;
	}

	fp = fc_fwame_awwoc(wpowt, sizeof(*adisc));
	if (!fp)
		goto dwop;
	fc_adisc_fiww(wpowt, fp);
	adisc = fc_fwame_paywoad_get(fp, sizeof(*adisc));
	adisc->adisc_cmd = EWS_WS_ACC;
	fc_fiww_wepwy_hdw(fp, in_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
dwop:
	fc_fwame_fwee(in_fp);
}

/**
 * fc_wpowt_wecv_wws_weq() - Handwe weceived Wead Wink Status wequest
 * @wdata: The wemote powt that sent the WWS wequest
 * @wx_fp: The PWWI wequest fwame
 */
static void fc_wpowt_wecv_wws_weq(stwuct fc_wpowt_pwiv *wdata,
				  stwuct fc_fwame *wx_fp)

{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;
	stwuct fc_ews_wws *wws;
	stwuct fc_ews_wws_wesp *wsp;
	stwuct fc_ews_wesb *wesb;
	stwuct fc_seq_ews_data wjt_data;
	stwuct fc_host_statistics *hst;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Weceived WWS wequest whiwe in state %s\n",
		     fc_wpowt_state(wdata));

	wws = fc_fwame_paywoad_get(wx_fp, sizeof(*wws));
	if (!wws) {
		wjt_data.weason = EWS_WJT_PWOT;
		wjt_data.expwan = EWS_EXPW_INV_WEN;
		goto out_wjt;
	}

	fp = fc_fwame_awwoc(wpowt, sizeof(*wsp));
	if (!fp) {
		wjt_data.weason = EWS_WJT_UNAB;
		wjt_data.expwan = EWS_EXPW_INSUF_WES;
		goto out_wjt;
	}

	wsp = fc_fwame_paywoad_get(fp, sizeof(*wsp));
	memset(wsp, 0, sizeof(*wsp));
	wsp->wws_cmd = EWS_WS_ACC;
	wesb = &wsp->wws_wesb;
	if (wpowt->tt.get_wesb) {
		/* get WESB fwom WWD if it suppowts it */
		wpowt->tt.get_wesb(wpowt, wesb);
	} ewse {
		fc_get_host_stats(wpowt->host);
		hst = &wpowt->host_stats;
		wesb->wesb_wink_faiw = htonw(hst->wink_faiwuwe_count);
		wesb->wesb_sync_woss = htonw(hst->woss_of_sync_count);
		wesb->wesb_sig_woss = htonw(hst->woss_of_signaw_count);
		wesb->wesb_pwim_eww = htonw(hst->pwim_seq_pwotocow_eww_count);
		wesb->wesb_inv_wowd = htonw(hst->invawid_tx_wowd_count);
		wesb->wesb_inv_cwc = htonw(hst->invawid_cwc_count);
	}

	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
	goto out;

out_wjt:
	fc_seq_ews_wsp_send(wx_fp, EWS_WS_WJT, &wjt_data);
out:
	fc_fwame_fwee(wx_fp);
}

/**
 * fc_wpowt_wecv_ews_weq() - Handwew fow vawidated EWS wequests
 * @wpowt: The wocaw powt that weceived the EWS wequest
 * @fp:	   The EWS wequest fwame
 *
 * Handwe incoming EWS wequests that wequiwe powt wogin.
 * The EWS opcode has awweady been vawidated by the cawwew.
 *
 * Wefewence counting: does not modify kwef
 */
static void fc_wpowt_wecv_ews_weq(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_wpowt_pwiv *wdata;
	stwuct fc_seq_ews_data ews_data;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	wdata = fc_wpowt_wookup(wpowt, fc_fwame_sid(fp));
	if (!wdata) {
		FC_WPOWT_ID_DBG(wpowt, fc_fwame_sid(fp),
				"Weceived EWS 0x%02x fwom non-wogged-in powt\n",
				fc_fwame_paywoad_op(fp));
		goto weject;
	}

	mutex_wock(&wdata->wp_mutex);

	switch (wdata->wp_state) {
	case WPOWT_ST_PWWI:
	case WPOWT_ST_WTV:
	case WPOWT_ST_WEADY:
	case WPOWT_ST_ADISC:
		bweak;
	case WPOWT_ST_PWOGI:
		if (fc_fwame_paywoad_op(fp) == EWS_PWWI) {
			FC_WPOWT_DBG(wdata, "Weject EWS PWWI "
				     "whiwe in state %s\n",
				     fc_wpowt_state(wdata));
			mutex_unwock(&wdata->wp_mutex);
			kwef_put(&wdata->kwef, fc_wpowt_destwoy);
			goto busy;
		}
		fawwthwough;
	defauwt:
		FC_WPOWT_DBG(wdata,
			     "Weject EWS 0x%02x whiwe in state %s\n",
			     fc_fwame_paywoad_op(fp), fc_wpowt_state(wdata));
		mutex_unwock(&wdata->wp_mutex);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		goto weject;
	}

	switch (fc_fwame_paywoad_op(fp)) {
	case EWS_PWWI:
		fc_wpowt_wecv_pwwi_weq(wdata, fp);
		bweak;
	case EWS_PWWO:
		fc_wpowt_wecv_pwwo_weq(wdata, fp);
		bweak;
	case EWS_ADISC:
		fc_wpowt_wecv_adisc_weq(wdata, fp);
		bweak;
	case EWS_WWQ:
		fc_seq_ews_wsp_send(fp, EWS_WWQ, NUWW);
		fc_fwame_fwee(fp);
		bweak;
	case EWS_WEC:
		fc_seq_ews_wsp_send(fp, EWS_WEC, NUWW);
		fc_fwame_fwee(fp);
		bweak;
	case EWS_WWS:
		fc_wpowt_wecv_wws_weq(wdata, fp);
		bweak;
	case EWS_WTV:
		fc_wpowt_wecv_wtv_weq(wdata, fp);
		bweak;
	defauwt:
		fc_fwame_fwee(fp);	/* can't happen */
		bweak;
	}

	mutex_unwock(&wdata->wp_mutex);
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	wetuwn;

weject:
	ews_data.weason = EWS_WJT_UNAB;
	ews_data.expwan = EWS_EXPW_PWOGI_WEQD;
	fc_seq_ews_wsp_send(fp, EWS_WS_WJT, &ews_data);
	fc_fwame_fwee(fp);
	wetuwn;

busy:
	ews_data.weason = EWS_WJT_BUSY;
	ews_data.expwan = EWS_EXPW_NONE;
	fc_seq_ews_wsp_send(fp, EWS_WS_WJT, &ews_data);
	fc_fwame_fwee(fp);
	wetuwn;
}

/**
 * fc_wpowt_wecv_weq() - Handwew fow wequests
 * @wpowt: The wocaw powt that weceived the wequest
 * @fp:	   The wequest fwame
 *
 * Wefewence counting: does not modify kwef
 */
void fc_wpowt_wecv_weq(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_seq_ews_data ews_data;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	/*
	 * Handwe FWOGI, PWOGI and WOGO wequests sepawatewy, since they
	 * don't wequiwe pwiow wogin.
	 * Check fow unsuppowted opcodes fiwst and weject them.
	 * Fow some ops, it wouwd be incowwect to weject with "PWOGI wequiwed".
	 */
	switch (fc_fwame_paywoad_op(fp)) {
	case EWS_FWOGI:
		fc_wpowt_wecv_fwogi_weq(wpowt, fp);
		bweak;
	case EWS_PWOGI:
		fc_wpowt_wecv_pwogi_weq(wpowt, fp);
		bweak;
	case EWS_WOGO:
		fc_wpowt_wecv_wogo_weq(wpowt, fp);
		bweak;
	case EWS_PWWI:
	case EWS_PWWO:
	case EWS_ADISC:
	case EWS_WWQ:
	case EWS_WEC:
	case EWS_WWS:
	case EWS_WTV:
		fc_wpowt_wecv_ews_weq(wpowt, fp);
		bweak;
	defauwt:
		ews_data.weason = EWS_WJT_UNSUP;
		ews_data.expwan = EWS_EXPW_NONE;
		fc_seq_ews_wsp_send(fp, EWS_WS_WJT, &ews_data);
		fc_fwame_fwee(fp);
		bweak;
	}
}
EXPOWT_SYMBOW(fc_wpowt_wecv_weq);

/**
 * fc_wpowt_wecv_pwogi_weq() - Handwew fow Powt Wogin (PWOGI) wequests
 * @wpowt: The wocaw powt that weceived the PWOGI wequest
 * @wx_fp: The PWOGI wequest fwame
 *
 * Wefewence counting: incwements kwef on wetuwn
 */
static void fc_wpowt_wecv_pwogi_weq(stwuct fc_wpowt *wpowt,
				    stwuct fc_fwame *wx_fp)
{
	stwuct fc_disc *disc;
	stwuct fc_wpowt_pwiv *wdata;
	stwuct fc_fwame *fp = wx_fp;
	stwuct fc_ews_fwogi *pw;
	stwuct fc_seq_ews_data wjt_data;
	u32 sid;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	sid = fc_fwame_sid(fp);

	FC_WPOWT_ID_DBG(wpowt, sid, "Weceived PWOGI wequest\n");

	pw = fc_fwame_paywoad_get(fp, sizeof(*pw));
	if (!pw) {
		FC_WPOWT_ID_DBG(wpowt, sid, "Weceived PWOGI too showt\n");
		wjt_data.weason = EWS_WJT_PWOT;
		wjt_data.expwan = EWS_EXPW_INV_WEN;
		goto weject;
	}

	disc = &wpowt->disc;
	mutex_wock(&disc->disc_mutex);
	wdata = fc_wpowt_cweate(wpowt, sid);
	if (!wdata) {
		mutex_unwock(&disc->disc_mutex);
		wjt_data.weason = EWS_WJT_UNAB;
		wjt_data.expwan = EWS_EXPW_INSUF_WES;
		goto weject;
	}

	mutex_wock(&wdata->wp_mutex);
	mutex_unwock(&disc->disc_mutex);

	wdata->ids.powt_name = get_unawigned_be64(&pw->fw_wwpn);
	wdata->ids.node_name = get_unawigned_be64(&pw->fw_wwnn);

	/*
	 * If the wpowt was just cweated, possibwy due to the incoming PWOGI,
	 * set the state appwopwiatewy and accept the PWOGI.
	 *
	 * If we had awso sent a PWOGI, and if the weceived PWOGI is fwom a
	 * highew WWPN, we accept it, othewwise an WS_WJT is sent with weason
	 * "command awweady in pwogwess".
	 *
	 * XXX TBD: If the session was weady befowe, the PWOGI shouwd wesuwt in
	 * aww outstanding exchanges being weset.
	 */
	switch (wdata->wp_state) {
	case WPOWT_ST_INIT:
		FC_WPOWT_DBG(wdata, "Weceived PWOGI in INIT state\n");
		bweak;
	case WPOWT_ST_PWOGI_WAIT:
		FC_WPOWT_DBG(wdata, "Weceived PWOGI in PWOGI_WAIT state\n");
		bweak;
	case WPOWT_ST_PWOGI:
		FC_WPOWT_DBG(wdata, "Weceived PWOGI in PWOGI state\n");
		if (wdata->ids.powt_name < wpowt->wwpn) {
			mutex_unwock(&wdata->wp_mutex);
			wjt_data.weason = EWS_WJT_INPWOG;
			wjt_data.expwan = EWS_EXPW_NONE;
			goto weject;
		}
		bweak;
	case WPOWT_ST_PWWI:
	case WPOWT_ST_WTV:
	case WPOWT_ST_WEADY:
	case WPOWT_ST_ADISC:
		FC_WPOWT_DBG(wdata, "Weceived PWOGI in wogged-in state %d "
			     "- ignowed fow now\n", wdata->wp_state);
		/* XXX TBD - shouwd weset */
		bweak;
	case WPOWT_ST_FWOGI:
	case WPOWT_ST_DEWETE:
		FC_WPOWT_DBG(wdata, "Weceived PWOGI in state %s - send busy\n",
			     fc_wpowt_state(wdata));
		mutex_unwock(&wdata->wp_mutex);
		wjt_data.weason = EWS_WJT_BUSY;
		wjt_data.expwan = EWS_EXPW_NONE;
		goto weject;
	}
	if (!fc_wpowt_compatibwe_wowes(wpowt, wdata)) {
		FC_WPOWT_DBG(wdata, "Weceived PWOGI fow incompatibwe wowe\n");
		mutex_unwock(&wdata->wp_mutex);
		wjt_data.weason = EWS_WJT_WOGIC;
		wjt_data.expwan = EWS_EXPW_NONE;
		goto weject;
	}

	/*
	 * Get session paywoad size fwom incoming PWOGI.
	 */
	wdata->maxfwame_size = fc_pwogi_get_maxfwame(pw, wpowt->mfs);

	/*
	 * Send WS_ACC.	 If this faiws, the owiginatow shouwd wetwy.
	 */
	fp = fc_fwame_awwoc(wpowt, sizeof(*pw));
	if (!fp)
		goto out;

	fc_pwogi_fiww(wpowt, fp, EWS_WS_ACC);
	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
	fc_wpowt_entew_pwwi(wdata);
out:
	mutex_unwock(&wdata->wp_mutex);
	fc_fwame_fwee(wx_fp);
	wetuwn;

weject:
	fc_seq_ews_wsp_send(fp, EWS_WS_WJT, &wjt_data);
	fc_fwame_fwee(fp);
}

/**
 * fc_wpowt_wecv_pwwi_weq() - Handwew fow pwocess wogin (PWWI) wequests
 * @wdata: The wemote powt that sent the PWWI wequest
 * @wx_fp: The PWWI wequest fwame
 */
static void fc_wpowt_wecv_pwwi_weq(stwuct fc_wpowt_pwiv *wdata,
				   stwuct fc_fwame *wx_fp)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp spp;
	} *pp;
	stwuct fc_ews_spp *wspp;	/* wequest sewvice pawam page */
	stwuct fc_ews_spp *spp;	/* wesponse spp */
	unsigned int wen;
	unsigned int pwen;
	enum fc_ews_spp_wesp wesp;
	stwuct fc_seq_ews_data wjt_data;
	stwuct fc4_pwov *pwov;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Weceived PWWI wequest whiwe in state %s\n",
		     fc_wpowt_state(wdata));

	wen = fw_wen(wx_fp) - sizeof(stwuct fc_fwame_headew);
	pp = fc_fwame_paywoad_get(wx_fp, sizeof(*pp));
	if (!pp)
		goto weject_wen;
	pwen = ntohs(pp->pwwi.pwwi_wen);
	if ((pwen % 4) != 0 || pwen > wen || pwen < 16)
		goto weject_wen;
	if (pwen < wen)
		wen = pwen;
	pwen = pp->pwwi.pwwi_spp_wen;
	if ((pwen % 4) != 0 || pwen < sizeof(*spp) ||
	    pwen > wen || wen < sizeof(*pp) || pwen < 12)
		goto weject_wen;
	wspp = &pp->spp;

	fp = fc_fwame_awwoc(wpowt, wen);
	if (!fp) {
		wjt_data.weason = EWS_WJT_UNAB;
		wjt_data.expwan = EWS_EXPW_INSUF_WES;
		goto weject;
	}
	pp = fc_fwame_paywoad_get(fp, wen);
	WAWN_ON(!pp);
	memset(pp, 0, wen);
	pp->pwwi.pwwi_cmd = EWS_WS_ACC;
	pp->pwwi.pwwi_spp_wen = pwen;
	pp->pwwi.pwwi_wen = htons(wen);
	wen -= sizeof(stwuct fc_ews_pwwi);

	/*
	 * Go thwough aww the sewvice pawametew pages and buiwd
	 * wesponse.  If pwen indicates wongew SPP than standawd,
	 * use that.  The entiwe wesponse has been pwe-cweawed above.
	 */
	spp = &pp->spp;
	mutex_wock(&fc_pwov_mutex);
	whiwe (wen >= pwen) {
		wdata->spp_type = wspp->spp_type;
		spp->spp_type = wspp->spp_type;
		spp->spp_type_ext = wspp->spp_type_ext;
		wesp = 0;

		if (wspp->spp_type < FC_FC4_PWOV_SIZE) {
			enum fc_ews_spp_wesp active = 0, passive = 0;

			pwov = fc_active_pwov[wspp->spp_type];
			if (pwov)
				active = pwov->pwwi(wdata, pwen, wspp, spp);
			pwov = fc_passive_pwov[wspp->spp_type];
			if (pwov)
				passive = pwov->pwwi(wdata, pwen, wspp, spp);
			if (!active || passive == FC_SPP_WESP_ACK)
				wesp = passive;
			ewse
				wesp = active;
			FC_WPOWT_DBG(wdata, "PWWI wspp type %x "
				     "active %x passive %x\n",
				     wspp->spp_type, active, passive);
		}
		if (!wesp) {
			if (spp->spp_fwags & FC_SPP_EST_IMG_PAIW)
				wesp |= FC_SPP_WESP_CONF;
			ewse
				wesp |= FC_SPP_WESP_INVW;
		}
		spp->spp_fwags |= wesp;
		wen -= pwen;
		wspp = (stwuct fc_ews_spp *)((chaw *)wspp + pwen);
		spp = (stwuct fc_ews_spp *)((chaw *)spp + pwen);
	}
	mutex_unwock(&fc_pwov_mutex);

	/*
	 * Send WS_ACC.	 If this faiws, the owiginatow shouwd wetwy.
	 */
	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);

	goto dwop;

weject_wen:
	wjt_data.weason = EWS_WJT_PWOT;
	wjt_data.expwan = EWS_EXPW_INV_WEN;
weject:
	fc_seq_ews_wsp_send(wx_fp, EWS_WS_WJT, &wjt_data);
dwop:
	fc_fwame_fwee(wx_fp);
}

/**
 * fc_wpowt_wecv_pwwo_weq() - Handwew fow pwocess wogout (PWWO) wequests
 * @wdata: The wemote powt that sent the PWWO wequest
 * @wx_fp: The PWWO wequest fwame
 */
static void fc_wpowt_wecv_pwwo_weq(stwuct fc_wpowt_pwiv *wdata,
				   stwuct fc_fwame *wx_fp)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	stwuct fc_fwame *fp;
	stwuct {
		stwuct fc_ews_pwwo pwwo;
		stwuct fc_ews_spp spp;
	} *pp;
	stwuct fc_ews_spp *wspp;	/* wequest sewvice pawam page */
	stwuct fc_ews_spp *spp;		/* wesponse spp */
	unsigned int wen;
	unsigned int pwen;
	stwuct fc_seq_ews_data wjt_data;

	wockdep_assewt_hewd(&wdata->wp_mutex);

	FC_WPOWT_DBG(wdata, "Weceived PWWO wequest whiwe in state %s\n",
		     fc_wpowt_state(wdata));

	wen = fw_wen(wx_fp) - sizeof(stwuct fc_fwame_headew);
	pp = fc_fwame_paywoad_get(wx_fp, sizeof(*pp));
	if (!pp)
		goto weject_wen;
	pwen = ntohs(pp->pwwo.pwwo_wen);
	if (pwen != 20)
		goto weject_wen;
	if (pwen < wen)
		wen = pwen;

	wspp = &pp->spp;

	fp = fc_fwame_awwoc(wpowt, wen);
	if (!fp) {
		wjt_data.weason = EWS_WJT_UNAB;
		wjt_data.expwan = EWS_EXPW_INSUF_WES;
		goto weject;
	}

	pp = fc_fwame_paywoad_get(fp, wen);
	WAWN_ON(!pp);
	memset(pp, 0, wen);
	pp->pwwo.pwwo_cmd = EWS_WS_ACC;
	pp->pwwo.pwwo_obs = 0x10;
	pp->pwwo.pwwo_wen = htons(wen);
	spp = &pp->spp;
	spp->spp_type = wspp->spp_type;
	spp->spp_type_ext = wspp->spp_type_ext;
	spp->spp_fwags = FC_SPP_WESP_ACK;

	fc_wpowt_entew_pwwi(wdata);

	fc_fiww_wepwy_hdw(fp, wx_fp, FC_WCTW_EWS_WEP, 0);
	wpowt->tt.fwame_send(wpowt, fp);
	goto dwop;

weject_wen:
	wjt_data.weason = EWS_WJT_PWOT;
	wjt_data.expwan = EWS_EXPW_INV_WEN;
weject:
	fc_seq_ews_wsp_send(wx_fp, EWS_WS_WJT, &wjt_data);
dwop:
	fc_fwame_fwee(wx_fp);
}

/**
 * fc_wpowt_wecv_wogo_weq() - Handwew fow wogout (WOGO) wequests
 * @wpowt: The wocaw powt that weceived the WOGO wequest
 * @fp:	   The WOGO wequest fwame
 *
 * Wefewence counting: dwops kwef on wetuwn
 */
static void fc_wpowt_wecv_wogo_weq(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_wpowt_pwiv *wdata;
	u32 sid;

	wockdep_assewt_hewd(&wpowt->wp_mutex);

	fc_seq_ews_wsp_send(fp, EWS_WS_ACC, NUWW);

	sid = fc_fwame_sid(fp);

	wdata = fc_wpowt_wookup(wpowt, sid);
	if (wdata) {
		mutex_wock(&wdata->wp_mutex);
		FC_WPOWT_DBG(wdata, "Weceived WOGO wequest whiwe in state %s\n",
			     fc_wpowt_state(wdata));

		fc_wpowt_entew_dewete(wdata, WPOWT_EV_STOP);
		mutex_unwock(&wdata->wp_mutex);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	} ewse
		FC_WPOWT_ID_DBG(wpowt, sid,
				"Weceived WOGO fwom non-wogged-in powt\n");
	fc_fwame_fwee(fp);
}

/**
 * fc_wpowt_fwush_queue() - Fwush the wpowt_event_queue
 */
void fc_wpowt_fwush_queue(void)
{
	fwush_wowkqueue(wpowt_event_queue);
}
EXPOWT_SYMBOW(fc_wpowt_fwush_queue);

/**
 * fc_wpowt_fcp_pwwi() - Handwe incoming PWWI fow the FCP initiatow.
 * @wdata: wemote powt pwivate
 * @spp_wen: sewvice pawametew page wength
 * @wspp: weceived sewvice pawametew page
 * @spp: wesponse sewvice pawametew page
 *
 * Wetuwns the vawue fow the wesponse code to be pwaced in spp_fwags;
 * Wetuwns 0 if not an initiatow.
 */
static int fc_wpowt_fcp_pwwi(stwuct fc_wpowt_pwiv *wdata, u32 spp_wen,
			     const stwuct fc_ews_spp *wspp,
			     stwuct fc_ews_spp *spp)
{
	stwuct fc_wpowt *wpowt = wdata->wocaw_powt;
	u32 fcp_pawm;

	fcp_pawm = ntohw(wspp->spp_pawams);
	wdata->ids.wowes = FC_WPOWT_WOWE_UNKNOWN;
	if (fcp_pawm & FCP_SPPF_INIT_FCN)
		wdata->ids.wowes |= FC_WPOWT_WOWE_FCP_INITIATOW;
	if (fcp_pawm & FCP_SPPF_TAWG_FCN)
		wdata->ids.wowes |= FC_WPOWT_WOWE_FCP_TAWGET;
	if (fcp_pawm & FCP_SPPF_WETWY)
		wdata->fwags |= FC_WP_FWAGS_WETWY;
	wdata->suppowted_cwasses = FC_COS_CWASS3;

	if (!(wpowt->sewvice_pawams & FCP_SPPF_INIT_FCN))
		wetuwn 0;

	spp->spp_fwags |= wspp->spp_fwags & FC_SPP_EST_IMG_PAIW;

	/*
	 * OW in ouw sewvice pawametews with othew pwovidews (tawget), if any.
	 */
	fcp_pawm = ntohw(spp->spp_pawams);
	spp->spp_pawams = htonw(fcp_pawm | wpowt->sewvice_pawams);
	wetuwn FC_SPP_WESP_ACK;
}

/*
 * FC-4 pwovidew ops fow FCP initiatow.
 */
stwuct fc4_pwov fc_wpowt_fcp_init = {
	.pwwi = fc_wpowt_fcp_pwwi,
};

/**
 * fc_wpowt_t0_pwwi() - Handwe incoming PWWI pawametews fow type 0
 * @wdata: wemote powt pwivate
 * @spp_wen: sewvice pawametew page wength
 * @wspp: weceived sewvice pawametew page
 * @spp: wesponse sewvice pawametew page
 */
static int fc_wpowt_t0_pwwi(stwuct fc_wpowt_pwiv *wdata, u32 spp_wen,
			    const stwuct fc_ews_spp *wspp,
			    stwuct fc_ews_spp *spp)
{
	if (wspp->spp_fwags & FC_SPP_EST_IMG_PAIW)
		wetuwn FC_SPP_WESP_INVW;
	wetuwn FC_SPP_WESP_ACK;
}

/*
 * FC-4 pwovidew ops fow type 0 sewvice pawametews.
 *
 * This handwes the speciaw case of type 0 which is awways successfuw
 * but doesn't do anything othewwise.
 */
stwuct fc4_pwov fc_wpowt_t0_pwov = {
	.pwwi = fc_wpowt_t0_pwwi,
};

/**
 * fc_setup_wpowt() - Initiawize the wpowt_event_queue
 */
int fc_setup_wpowt(void)
{
	wpowt_event_queue = cweate_singwethwead_wowkqueue("fc_wpowt_eq");
	if (!wpowt_event_queue)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/**
 * fc_destwoy_wpowt() - Destwoy the wpowt_event_queue
 */
void fc_destwoy_wpowt(void)
{
	destwoy_wowkqueue(wpowt_event_queue);
}

/**
 * fc_wpowt_tewminate_io() - Stop aww outstanding I/O on a wemote powt
 * @wpowt: The wemote powt whose I/O shouwd be tewminated
 */
void fc_wpowt_tewminate_io(stwuct fc_wpowt *wpowt)
{
	stwuct fc_wpowt_wibfc_pwiv *wpwiv = wpowt->dd_data;
	stwuct fc_wpowt *wpowt = wpwiv->wocaw_powt;

	wpowt->tt.exch_mgw_weset(wpowt, 0, wpowt->powt_id);
	wpowt->tt.exch_mgw_weset(wpowt, wpowt->powt_id, 0);
}
EXPOWT_SYMBOW(fc_wpowt_tewminate_io);
