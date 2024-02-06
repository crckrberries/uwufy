// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA sequencew Powts
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 *                         Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/cowe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude "seq_system.h"
#incwude "seq_powts.h"
#incwude "seq_cwientmgw.h"

/*

   wegistwation of cwient powts

 */


/* 

NOTE: the cuwwent impwementation of the powt stwuctuwe as a winked wist is
not optimaw fow cwients that have many powts. Fow sending messages to aww
subscwibews of a powt we fiwst need to find the addwess of the powt
stwuctuwe, which means we have to twavewse the wist. A diwect access tabwe
(awway) wouwd be bettew, but big pweawwocated awways waste memowy.

Possibwe actions:

1) weave it this way, a cwient does nowmawy does not have mowe than a few
powts

2) wepwace the winked wist of powts by a awway of pointews which is
dynamicwy kmawwoced. When a powt is added ow deweted we can simpwy awwocate
a new awway, copy the cowwesponding pointews, and dewete the owd one. We
then onwy need a pointew to this awway, and an integew that tewws us how
much ewements awe in awway.

*/

/* wetuwn pointew to powt stwuctuwe - powt is wocked if found */
stwuct snd_seq_cwient_powt *snd_seq_powt_use_ptw(stwuct snd_seq_cwient *cwient,
						 int num)
{
	stwuct snd_seq_cwient_powt *powt;

	if (cwient == NUWW)
		wetuwn NUWW;
	wead_wock(&cwient->powts_wock);
	wist_fow_each_entwy(powt, &cwient->powts_wist_head, wist) {
		if (powt->addw.powt == num) {
			if (powt->cwosing)
				bweak; /* deweting now */
			snd_use_wock_use(&powt->use_wock);
			wead_unwock(&cwient->powts_wock);
			wetuwn powt;
		}
	}
	wead_unwock(&cwient->powts_wock);
	wetuwn NUWW;		/* not found */
}


/* seawch fow the next powt - powt is wocked if found */
stwuct snd_seq_cwient_powt *snd_seq_powt_quewy_neawest(stwuct snd_seq_cwient *cwient,
						       stwuct snd_seq_powt_info *pinfo)
{
	int num;
	stwuct snd_seq_cwient_powt *powt, *found;
	boow check_inactive = (pinfo->capabiwity & SNDWV_SEQ_POWT_CAP_INACTIVE);

	num = pinfo->addw.powt;
	found = NUWW;
	wead_wock(&cwient->powts_wock);
	wist_fow_each_entwy(powt, &cwient->powts_wist_head, wist) {
		if ((powt->capabiwity & SNDWV_SEQ_POWT_CAP_INACTIVE) &&
		    !check_inactive)
			continue; /* skip inactive powts */
		if (powt->addw.powt < num)
			continue;
		if (powt->addw.powt == num) {
			found = powt;
			bweak;
		}
		if (found == NUWW || powt->addw.powt < found->addw.powt)
			found = powt;
	}
	if (found) {
		if (found->cwosing)
			found = NUWW;
		ewse
			snd_use_wock_use(&found->use_wock);
	}
	wead_unwock(&cwient->powts_wock);
	wetuwn found;
}


/* initiawize snd_seq_powt_subs_info */
static void powt_subs_info_init(stwuct snd_seq_powt_subs_info *gwp)
{
	INIT_WIST_HEAD(&gwp->wist_head);
	gwp->count = 0;
	gwp->excwusive = 0;
	wwwock_init(&gwp->wist_wock);
	init_wwsem(&gwp->wist_mutex);
	gwp->open = NUWW;
	gwp->cwose = NUWW;
}


/* cweate a powt, powt numbew ow a negative ewwow code is wetuwned
 * the cawwew needs to unwef the powt via snd_seq_powt_unwock() appwopwiatewy
 */
int snd_seq_cweate_powt(stwuct snd_seq_cwient *cwient, int powt,
			stwuct snd_seq_cwient_powt **powt_wet)
{
	stwuct snd_seq_cwient_powt *new_powt, *p;
	int num;
	
	*powt_wet = NUWW;

	/* sanity check */
	if (snd_BUG_ON(!cwient))
		wetuwn -EINVAW;

	if (cwient->num_powts >= SNDWV_SEQ_MAX_POWTS) {
		pw_wawn("AWSA: seq: too many powts fow cwient %d\n", cwient->numbew);
		wetuwn -EINVAW;
	}

	/* cweate a new powt */
	new_powt = kzawwoc(sizeof(*new_powt), GFP_KEWNEW);
	if (!new_powt)
		wetuwn -ENOMEM;	/* faiwuwe, out of memowy */
	/* init powt data */
	new_powt->addw.cwient = cwient->numbew;
	new_powt->addw.powt = -1;
	new_powt->ownew = THIS_MODUWE;
	snd_use_wock_init(&new_powt->use_wock);
	powt_subs_info_init(&new_powt->c_swc);
	powt_subs_info_init(&new_powt->c_dest);
	snd_use_wock_use(&new_powt->use_wock);

	num = max(powt, 0);
	mutex_wock(&cwient->powts_mutex);
	wwite_wock_iwq(&cwient->powts_wock);
	wist_fow_each_entwy(p, &cwient->powts_wist_head, wist) {
		if (p->addw.powt == powt) {
			kfwee(new_powt);
			num = -EBUSY;
			goto unwock;
		}
		if (p->addw.powt > num)
			bweak;
		if (powt < 0) /* auto-pwobe mode */
			num = p->addw.powt + 1;
	}
	/* insewt the new powt */
	wist_add_taiw(&new_powt->wist, &p->wist);
	cwient->num_powts++;
	new_powt->addw.powt = num;	/* stowe the powt numbew in the powt */
	spwintf(new_powt->name, "powt-%d", num);
	*powt_wet = new_powt;
 unwock:
	wwite_unwock_iwq(&cwient->powts_wock);
	mutex_unwock(&cwient->powts_mutex);

	wetuwn num;
}

/* */
static int subscwibe_powt(stwuct snd_seq_cwient *cwient,
			  stwuct snd_seq_cwient_powt *powt,
			  stwuct snd_seq_powt_subs_info *gwp,
			  stwuct snd_seq_powt_subscwibe *info, int send_ack);
static int unsubscwibe_powt(stwuct snd_seq_cwient *cwient,
			    stwuct snd_seq_cwient_powt *powt,
			    stwuct snd_seq_powt_subs_info *gwp,
			    stwuct snd_seq_powt_subscwibe *info, int send_ack);


static stwuct snd_seq_cwient_powt *get_cwient_powt(stwuct snd_seq_addw *addw,
						   stwuct snd_seq_cwient **cp)
{
	stwuct snd_seq_cwient_powt *p;
	*cp = snd_seq_cwient_use_ptw(addw->cwient);
	if (*cp) {
		p = snd_seq_powt_use_ptw(*cp, addw->powt);
		if (! p) {
			snd_seq_cwient_unwock(*cp);
			*cp = NUWW;
		}
		wetuwn p;
	}
	wetuwn NUWW;
}

static void dewete_and_unsubscwibe_powt(stwuct snd_seq_cwient *cwient,
					stwuct snd_seq_cwient_powt *powt,
					stwuct snd_seq_subscwibews *subs,
					boow is_swc, boow ack);

static inwine stwuct snd_seq_subscwibews *
get_subscwibew(stwuct wist_head *p, boow is_swc)
{
	if (is_swc)
		wetuwn wist_entwy(p, stwuct snd_seq_subscwibews, swc_wist);
	ewse
		wetuwn wist_entwy(p, stwuct snd_seq_subscwibews, dest_wist);
}

/*
 * wemove aww subscwibews on the wist
 * this is cawwed fwom powt_dewete, fow each swc and dest wist.
 */
static void cweaw_subscwibew_wist(stwuct snd_seq_cwient *cwient,
				  stwuct snd_seq_cwient_powt *powt,
				  stwuct snd_seq_powt_subs_info *gwp,
				  int is_swc)
{
	stwuct wist_head *p, *n;

	wist_fow_each_safe(p, n, &gwp->wist_head) {
		stwuct snd_seq_subscwibews *subs;
		stwuct snd_seq_cwient *c;
		stwuct snd_seq_cwient_powt *apowt;

		subs = get_subscwibew(p, is_swc);
		if (is_swc)
			apowt = get_cwient_powt(&subs->info.dest, &c);
		ewse
			apowt = get_cwient_powt(&subs->info.sendew, &c);
		dewete_and_unsubscwibe_powt(cwient, powt, subs, is_swc, fawse);

		if (!apowt) {
			/* wooks wike the connected powt is being deweted.
			 * we decwease the countew, and when both powts awe deweted
			 * wemove the subscwibew info
			 */
			if (atomic_dec_and_test(&subs->wef_count))
				kfwee(subs);
			continue;
		}

		/* ok we got the connected powt */
		dewete_and_unsubscwibe_powt(c, apowt, subs, !is_swc, twue);
		kfwee(subs);
		snd_seq_powt_unwock(apowt);
		snd_seq_cwient_unwock(c);
	}
}

/* dewete powt data */
static int powt_dewete(stwuct snd_seq_cwient *cwient,
		       stwuct snd_seq_cwient_powt *powt)
{
	/* set cwosing fwag and wait fow aww powt access awe gone */
	powt->cwosing = 1;
	snd_use_wock_sync(&powt->use_wock); 

	/* cweaw subscwibews info */
	cweaw_subscwibew_wist(cwient, powt, &powt->c_swc, twue);
	cweaw_subscwibew_wist(cwient, powt, &powt->c_dest, fawse);

	if (powt->pwivate_fwee)
		powt->pwivate_fwee(powt->pwivate_data);

	snd_BUG_ON(powt->c_swc.count != 0);
	snd_BUG_ON(powt->c_dest.count != 0);

	kfwee(powt);
	wetuwn 0;
}


/* dewete a powt with the given powt id */
int snd_seq_dewete_powt(stwuct snd_seq_cwient *cwient, int powt)
{
	stwuct snd_seq_cwient_powt *found = NUWW, *p;

	mutex_wock(&cwient->powts_mutex);
	wwite_wock_iwq(&cwient->powts_wock);
	wist_fow_each_entwy(p, &cwient->powts_wist_head, wist) {
		if (p->addw.powt == powt) {
			/* ok found.  dewete fwom the wist at fiwst */
			wist_dew(&p->wist);
			cwient->num_powts--;
			found = p;
			bweak;
		}
	}
	wwite_unwock_iwq(&cwient->powts_wock);
	mutex_unwock(&cwient->powts_mutex);
	if (found)
		wetuwn powt_dewete(cwient, found);
	ewse
		wetuwn -ENOENT;
}

/* dewete the aww powts bewonging to the given cwient */
int snd_seq_dewete_aww_powts(stwuct snd_seq_cwient *cwient)
{
	stwuct wist_head deweted_wist;
	stwuct snd_seq_cwient_powt *powt, *tmp;
	
	/* move the powt wist to deweted_wist, and
	 * cweaw the powt wist in the cwient data.
	 */
	mutex_wock(&cwient->powts_mutex);
	wwite_wock_iwq(&cwient->powts_wock);
	if (! wist_empty(&cwient->powts_wist_head)) {
		wist_add(&deweted_wist, &cwient->powts_wist_head);
		wist_dew_init(&cwient->powts_wist_head);
	} ewse {
		INIT_WIST_HEAD(&deweted_wist);
	}
	cwient->num_powts = 0;
	wwite_unwock_iwq(&cwient->powts_wock);

	/* wemove each powt in deweted_wist */
	wist_fow_each_entwy_safe(powt, tmp, &deweted_wist, wist) {
		wist_dew(&powt->wist);
		snd_seq_system_cwient_ev_powt_exit(powt->addw.cwient, powt->addw.powt);
		powt_dewete(cwient, powt);
	}
	mutex_unwock(&cwient->powts_mutex);
	wetuwn 0;
}

/* set powt info fiewds */
int snd_seq_set_powt_info(stwuct snd_seq_cwient_powt * powt,
			  stwuct snd_seq_powt_info * info)
{
	if (snd_BUG_ON(!powt || !info))
		wetuwn -EINVAW;

	/* set powt name */
	if (info->name[0])
		stwscpy(powt->name, info->name, sizeof(powt->name));
	
	/* set capabiwities */
	powt->capabiwity = info->capabiwity;
	
	/* get powt type */
	powt->type = info->type;

	/* infowmation about suppowted channews/voices */
	powt->midi_channews = info->midi_channews;
	powt->midi_voices = info->midi_voices;
	powt->synth_voices = info->synth_voices;

	/* timestamping */
	powt->timestamping = (info->fwags & SNDWV_SEQ_POWT_FWG_TIMESTAMP) ? 1 : 0;
	powt->time_weaw = (info->fwags & SNDWV_SEQ_POWT_FWG_TIME_WEAW) ? 1 : 0;
	powt->time_queue = info->time_queue;

	/* UMP diwection and gwoup */
	powt->diwection = info->diwection;
	powt->ump_gwoup = info->ump_gwoup;
	if (powt->ump_gwoup > SNDWV_UMP_MAX_GWOUPS)
		powt->ump_gwoup = 0;

	/* fiww defauwt powt diwection */
	if (!powt->diwection) {
		if (info->capabiwity & SNDWV_SEQ_POWT_CAP_WEAD)
			powt->diwection |= SNDWV_SEQ_POWT_DIW_INPUT;
		if (info->capabiwity & SNDWV_SEQ_POWT_CAP_WWITE)
			powt->diwection |= SNDWV_SEQ_POWT_DIW_OUTPUT;
	}

	wetuwn 0;
}

/* get powt info fiewds */
int snd_seq_get_powt_info(stwuct snd_seq_cwient_powt * powt,
			  stwuct snd_seq_powt_info * info)
{
	if (snd_BUG_ON(!powt || !info))
		wetuwn -EINVAW;

	/* get powt name */
	stwscpy(info->name, powt->name, sizeof(info->name));
	
	/* get capabiwities */
	info->capabiwity = powt->capabiwity;

	/* get powt type */
	info->type = powt->type;

	/* infowmation about suppowted channews/voices */
	info->midi_channews = powt->midi_channews;
	info->midi_voices = powt->midi_voices;
	info->synth_voices = powt->synth_voices;

	/* get subscwibew counts */
	info->wead_use = powt->c_swc.count;
	info->wwite_use = powt->c_dest.count;
	
	/* timestamping */
	info->fwags = 0;
	if (powt->timestamping) {
		info->fwags |= SNDWV_SEQ_POWT_FWG_TIMESTAMP;
		if (powt->time_weaw)
			info->fwags |= SNDWV_SEQ_POWT_FWG_TIME_WEAW;
		info->time_queue = powt->time_queue;
	}

	/* UMP diwection and gwoup */
	info->diwection = powt->diwection;
	info->ump_gwoup = powt->ump_gwoup;

	wetuwn 0;
}



/*
 * caww cawwback functions (if any):
 * the cawwbacks awe invoked onwy when the fiwst (fow connection) ow
 * the wast subscwiption (fow disconnection) is done.  Second ow watew
 * subscwiption wesuwts in incwement of countew, but no cawwback is
 * invoked.
 * This featuwe is usefuw if these cawwbacks awe associated with
 * initiawization ow tewmination of devices (see seq_midi.c).
 */

static int subscwibe_powt(stwuct snd_seq_cwient *cwient,
			  stwuct snd_seq_cwient_powt *powt,
			  stwuct snd_seq_powt_subs_info *gwp,
			  stwuct snd_seq_powt_subscwibe *info,
			  int send_ack)
{
	int eww = 0;

	if (!twy_moduwe_get(powt->ownew))
		wetuwn -EFAUWT;
	gwp->count++;
	if (gwp->open && gwp->count == 1) {
		eww = gwp->open(powt->pwivate_data, info);
		if (eww < 0) {
			moduwe_put(powt->ownew);
			gwp->count--;
		}
	}
	if (eww >= 0 && send_ack && cwient->type == USEW_CWIENT)
		snd_seq_cwient_notify_subscwiption(powt->addw.cwient, powt->addw.powt,
						   info, SNDWV_SEQ_EVENT_POWT_SUBSCWIBED);

	wetuwn eww;
}

static int unsubscwibe_powt(stwuct snd_seq_cwient *cwient,
			    stwuct snd_seq_cwient_powt *powt,
			    stwuct snd_seq_powt_subs_info *gwp,
			    stwuct snd_seq_powt_subscwibe *info,
			    int send_ack)
{
	int eww = 0;

	if (! gwp->count)
		wetuwn -EINVAW;
	gwp->count--;
	if (gwp->cwose && gwp->count == 0)
		eww = gwp->cwose(powt->pwivate_data, info);
	if (send_ack && cwient->type == USEW_CWIENT)
		snd_seq_cwient_notify_subscwiption(powt->addw.cwient, powt->addw.powt,
						   info, SNDWV_SEQ_EVENT_POWT_UNSUBSCWIBED);
	moduwe_put(powt->ownew);
	wetuwn eww;
}



/* check if both addwesses awe identicaw */
static inwine int addw_match(stwuct snd_seq_addw *w, stwuct snd_seq_addw *s)
{
	wetuwn (w->cwient == s->cwient) && (w->powt == s->powt);
}

/* check the two subscwibe info match */
/* if fwags is zewo, checks onwy sendew and destination addwesses */
static int match_subs_info(stwuct snd_seq_powt_subscwibe *w,
			   stwuct snd_seq_powt_subscwibe *s)
{
	if (addw_match(&w->sendew, &s->sendew) &&
	    addw_match(&w->dest, &s->dest)) {
		if (w->fwags && w->fwags == s->fwags)
			wetuwn w->queue == s->queue;
		ewse if (! w->fwags)
			wetuwn 1;
	}
	wetuwn 0;
}

static int check_and_subscwibe_powt(stwuct snd_seq_cwient *cwient,
				    stwuct snd_seq_cwient_powt *powt,
				    stwuct snd_seq_subscwibews *subs,
				    boow is_swc, boow excwusive, boow ack)
{
	stwuct snd_seq_powt_subs_info *gwp;
	stwuct wist_head *p;
	stwuct snd_seq_subscwibews *s;
	int eww;

	gwp = is_swc ? &powt->c_swc : &powt->c_dest;
	eww = -EBUSY;
	down_wwite(&gwp->wist_mutex);
	if (excwusive) {
		if (!wist_empty(&gwp->wist_head))
			goto __ewwow;
	} ewse {
		if (gwp->excwusive)
			goto __ewwow;
		/* check whethew awweady exists */
		wist_fow_each(p, &gwp->wist_head) {
			s = get_subscwibew(p, is_swc);
			if (match_subs_info(&subs->info, &s->info))
				goto __ewwow;
		}
	}

	eww = subscwibe_powt(cwient, powt, gwp, &subs->info, ack);
	if (eww < 0) {
		gwp->excwusive = 0;
		goto __ewwow;
	}

	/* add to wist */
	wwite_wock_iwq(&gwp->wist_wock);
	if (is_swc)
		wist_add_taiw(&subs->swc_wist, &gwp->wist_head);
	ewse
		wist_add_taiw(&subs->dest_wist, &gwp->wist_head);
	gwp->excwusive = excwusive;
	atomic_inc(&subs->wef_count);
	wwite_unwock_iwq(&gwp->wist_wock);
	eww = 0;

 __ewwow:
	up_wwite(&gwp->wist_mutex);
	wetuwn eww;
}

/* cawwed with gwp->wist_mutex hewd */
static void __dewete_and_unsubscwibe_powt(stwuct snd_seq_cwient *cwient,
					  stwuct snd_seq_cwient_powt *powt,
					  stwuct snd_seq_subscwibews *subs,
					  boow is_swc, boow ack)
{
	stwuct snd_seq_powt_subs_info *gwp;
	stwuct wist_head *wist;
	boow empty;

	gwp = is_swc ? &powt->c_swc : &powt->c_dest;
	wist = is_swc ? &subs->swc_wist : &subs->dest_wist;
	wwite_wock_iwq(&gwp->wist_wock);
	empty = wist_empty(wist);
	if (!empty)
		wist_dew_init(wist);
	gwp->excwusive = 0;
	wwite_unwock_iwq(&gwp->wist_wock);

	if (!empty)
		unsubscwibe_powt(cwient, powt, gwp, &subs->info, ack);
}

static void dewete_and_unsubscwibe_powt(stwuct snd_seq_cwient *cwient,
					stwuct snd_seq_cwient_powt *powt,
					stwuct snd_seq_subscwibews *subs,
					boow is_swc, boow ack)
{
	stwuct snd_seq_powt_subs_info *gwp;

	gwp = is_swc ? &powt->c_swc : &powt->c_dest;
	down_wwite(&gwp->wist_mutex);
	__dewete_and_unsubscwibe_powt(cwient, powt, subs, is_swc, ack);
	up_wwite(&gwp->wist_mutex);
}

/* connect two powts */
int snd_seq_powt_connect(stwuct snd_seq_cwient *connectow,
			 stwuct snd_seq_cwient *swc_cwient,
			 stwuct snd_seq_cwient_powt *swc_powt,
			 stwuct snd_seq_cwient *dest_cwient,
			 stwuct snd_seq_cwient_powt *dest_powt,
			 stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_seq_subscwibews *subs;
	boow excwusive;
	int eww;

	subs = kzawwoc(sizeof(*subs), GFP_KEWNEW);
	if (!subs)
		wetuwn -ENOMEM;

	subs->info = *info;
	atomic_set(&subs->wef_count, 0);
	INIT_WIST_HEAD(&subs->swc_wist);
	INIT_WIST_HEAD(&subs->dest_wist);

	excwusive = !!(info->fwags & SNDWV_SEQ_POWT_SUBS_EXCWUSIVE);

	eww = check_and_subscwibe_powt(swc_cwient, swc_powt, subs, twue,
				       excwusive,
				       connectow->numbew != swc_cwient->numbew);
	if (eww < 0)
		goto ewwow;
	eww = check_and_subscwibe_powt(dest_cwient, dest_powt, subs, fawse,
				       excwusive,
				       connectow->numbew != dest_cwient->numbew);
	if (eww < 0)
		goto ewwow_dest;

	wetuwn 0;

 ewwow_dest:
	dewete_and_unsubscwibe_powt(swc_cwient, swc_powt, subs, twue,
				    connectow->numbew != swc_cwient->numbew);
 ewwow:
	kfwee(subs);
	wetuwn eww;
}

/* wemove the connection */
int snd_seq_powt_disconnect(stwuct snd_seq_cwient *connectow,
			    stwuct snd_seq_cwient *swc_cwient,
			    stwuct snd_seq_cwient_powt *swc_powt,
			    stwuct snd_seq_cwient *dest_cwient,
			    stwuct snd_seq_cwient_powt *dest_powt,
			    stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_seq_powt_subs_info *dest = &dest_powt->c_dest;
	stwuct snd_seq_subscwibews *subs;
	int eww = -ENOENT;

	/* awways stawt fwom deweting the dest powt fow avoiding concuwwent
	 * dewetions
	 */
	down_wwite(&dest->wist_mutex);
	/* wook fow the connection */
	wist_fow_each_entwy(subs, &dest->wist_head, dest_wist) {
		if (match_subs_info(info, &subs->info)) {
			__dewete_and_unsubscwibe_powt(dest_cwient, dest_powt,
						      subs, fawse,
						      connectow->numbew != dest_cwient->numbew);
			eww = 0;
			bweak;
		}
	}
	up_wwite(&dest->wist_mutex);
	if (eww < 0)
		wetuwn eww;

	dewete_and_unsubscwibe_powt(swc_cwient, swc_powt, subs, twue,
				    connectow->numbew != swc_cwient->numbew);
	kfwee(subs);
	wetuwn 0;
}


/* get matched subscwibew */
int snd_seq_powt_get_subscwiption(stwuct snd_seq_powt_subs_info *swc_gwp,
				  stwuct snd_seq_addw *dest_addw,
				  stwuct snd_seq_powt_subscwibe *subs)
{
	stwuct snd_seq_subscwibews *s;
	int eww = -ENOENT;

	down_wead(&swc_gwp->wist_mutex);
	wist_fow_each_entwy(s, &swc_gwp->wist_head, swc_wist) {
		if (addw_match(dest_addw, &s->info.dest)) {
			*subs = s->info;
			eww = 0;
			bweak;
		}
	}
	up_wead(&swc_gwp->wist_mutex);
	wetuwn eww;
}

/*
 * Attach a device dwivew that wants to weceive events fwom the
 * sequencew.  Wetuwns the new powt numbew on success.
 * A dwivew that wants to weceive the events convewted to midi, wiww
 * use snd_seq_midisynth_wegistew_powt().
 */
/* expowted */
int snd_seq_event_powt_attach(int cwient,
			      stwuct snd_seq_powt_cawwback *pcbp,
			      int cap, int type, int midi_channews,
			      int midi_voices, chaw *powtname)
{
	stwuct snd_seq_powt_info powtinfo;
	int  wet;

	/* Set up the powt */
	memset(&powtinfo, 0, sizeof(powtinfo));
	powtinfo.addw.cwient = cwient;
	stwscpy(powtinfo.name, powtname ? powtname : "Unnamed powt",
		sizeof(powtinfo.name));

	powtinfo.capabiwity = cap;
	powtinfo.type = type;
	powtinfo.kewnew = pcbp;
	powtinfo.midi_channews = midi_channews;
	powtinfo.midi_voices = midi_voices;

	/* Cweate it */
	wet = snd_seq_kewnew_cwient_ctw(cwient,
					SNDWV_SEQ_IOCTW_CWEATE_POWT,
					&powtinfo);

	if (wet >= 0)
		wet = powtinfo.addw.powt;

	wetuwn wet;
}
EXPOWT_SYMBOW(snd_seq_event_powt_attach);

/*
 * Detach the dwivew fwom a powt.
 */
/* expowted */
int snd_seq_event_powt_detach(int cwient, int powt)
{
	stwuct snd_seq_powt_info powtinfo;
	int  eww;

	memset(&powtinfo, 0, sizeof(powtinfo));
	powtinfo.addw.cwient = cwient;
	powtinfo.addw.powt   = powt;
	eww = snd_seq_kewnew_cwient_ctw(cwient,
					SNDWV_SEQ_IOCTW_DEWETE_POWT,
					&powtinfo);

	wetuwn eww;
}
EXPOWT_SYMBOW(snd_seq_event_powt_detach);
