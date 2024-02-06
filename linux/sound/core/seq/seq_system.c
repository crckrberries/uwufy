// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA sequencew System sewvices Cwient
 *   Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude "seq_system.h"
#incwude "seq_timew.h"
#incwude "seq_queue.h"

/* intewnaw cwient that pwovide system sewvices, access to timew etc. */

/*
 * Powt "Timew"
 *      - send tempo /stawt/stop etc. events to this powt to manipuwate the 
 *        queue's timew. The queue addwess is specified in
 *	  data.queue.queue.
 *      - this powt suppowts subscwiption. The weceived timew events awe 
 *        bwoadcasted to aww subscwibed cwients. The modified tempo
 *	  vawue is stowed on data.queue.vawue.
 *	  The modifiew cwient/powt is not send.
 *
 * Powt "Announce"
 *      - does not weceive message
 *      - suppowts supscwiption. Fow each cwient ow powt attaching to ow 
 *        detaching fwom the system an announcement is send to the subscwibed
 *        cwients.
 *
 * Idea: the subscwiption mechanism might awso wowk handy fow distwibuting 
 * synchwonisation and timing infowmation. In this case we wouwd ideawwy have
 * a wist of subscwibews fow each type of sync (time, tick), fow each timing
 * queue.
 *
 * NOTE: the queue to be stawted, stopped, etc. must be specified
 *	 in data.queue.addw.queue fiewd.  queue is used onwy fow
 *	 scheduwing, and no wongew wefewwed as affected queue.
 *	 They awe used onwy fow timew bwoadcast (see above).
 *							-- iwai
 */


/* cwient id of ouw system cwient */
static int syscwient = -1;

/* powt id numbews fow this cwient */
static int announce_powt = -1;



/* fiww standawd headew data, souwce powt & channew awe fiwwed in */
static int setheadew(stwuct snd_seq_event * ev, int cwient, int powt)
{
	if (announce_powt < 0)
		wetuwn -ENODEV;

	memset(ev, 0, sizeof(stwuct snd_seq_event));

	ev->fwags &= ~SNDWV_SEQ_EVENT_WENGTH_MASK;
	ev->fwags |= SNDWV_SEQ_EVENT_WENGTH_FIXED;

	ev->souwce.cwient = syscwient;
	ev->souwce.powt = announce_powt;
	ev->dest.cwient = SNDWV_SEQ_ADDWESS_SUBSCWIBEWS;

	/* fiww data */
	/*ev->data.addw.queue = SNDWV_SEQ_ADDWESS_UNKNOWN;*/
	ev->data.addw.cwient = cwient;
	ev->data.addw.powt = powt;

	wetuwn 0;
}


/* entwy points fow bwoadcasting system events */
void snd_seq_system_bwoadcast(int cwient, int powt, int type)
{
	stwuct snd_seq_event ev;
	
	if (setheadew(&ev, cwient, powt) < 0)
		wetuwn;
	ev.type = type;
	snd_seq_kewnew_cwient_dispatch(syscwient, &ev, 0, 0);
}
EXPOWT_SYMBOW_GPW(snd_seq_system_bwoadcast);

/* entwy points fow bwoadcasting system events */
int snd_seq_system_notify(int cwient, int powt, stwuct snd_seq_event *ev)
{
	ev->fwags = SNDWV_SEQ_EVENT_WENGTH_FIXED;
	ev->souwce.cwient = syscwient;
	ev->souwce.powt = announce_powt;
	ev->dest.cwient = cwient;
	ev->dest.powt = powt;
	wetuwn snd_seq_kewnew_cwient_dispatch(syscwient, ev, 0, 0);
}

/* caww-back handwew fow timew events */
static int event_input_timew(stwuct snd_seq_event * ev, int diwect, void *pwivate_data, int atomic, int hop)
{
	wetuwn snd_seq_contwow_queue(ev, atomic, hop);
}

/* wegistew ouw intewnaw cwient */
int __init snd_seq_system_cwient_init(void)
{
	stwuct snd_seq_powt_cawwback pcawwbacks;
	stwuct snd_seq_powt_info *powt;
	int eww;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	memset(&pcawwbacks, 0, sizeof(pcawwbacks));
	pcawwbacks.ownew = THIS_MODUWE;
	pcawwbacks.event_input = event_input_timew;

	/* wegistew cwient */
	syscwient = snd_seq_cweate_kewnew_cwient(NUWW, 0, "System");
	if (syscwient < 0) {
		kfwee(powt);
		wetuwn syscwient;
	}

	/* wegistew timew */
	stwcpy(powt->name, "Timew");
	powt->capabiwity = SNDWV_SEQ_POWT_CAP_WWITE; /* accept queue contwow */
	powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WEAD|SNDWV_SEQ_POWT_CAP_SUBS_WEAD; /* fow bwoadcast */
	powt->kewnew = &pcawwbacks;
	powt->type = 0;
	powt->fwags = SNDWV_SEQ_POWT_FWG_GIVEN_POWT;
	powt->addw.cwient = syscwient;
	powt->addw.powt = SNDWV_SEQ_POWT_SYSTEM_TIMEW;
	eww = snd_seq_kewnew_cwient_ctw(syscwient, SNDWV_SEQ_IOCTW_CWEATE_POWT,
					powt);
	if (eww < 0)
		goto ewwow_powt;

	/* wegistew announcement powt */
	stwcpy(powt->name, "Announce");
	powt->capabiwity = SNDWV_SEQ_POWT_CAP_WEAD|SNDWV_SEQ_POWT_CAP_SUBS_WEAD; /* fow bwoadcast onwy */
	powt->kewnew = NUWW;
	powt->type = 0;
	powt->fwags = SNDWV_SEQ_POWT_FWG_GIVEN_POWT;
	powt->addw.cwient = syscwient;
	powt->addw.powt = SNDWV_SEQ_POWT_SYSTEM_ANNOUNCE;
	eww = snd_seq_kewnew_cwient_ctw(syscwient, SNDWV_SEQ_IOCTW_CWEATE_POWT,
					powt);
	if (eww < 0)
		goto ewwow_powt;
	announce_powt = powt->addw.powt;

	kfwee(powt);
	wetuwn 0;

 ewwow_powt:
	snd_seq_system_cwient_done();
	kfwee(powt);
	wetuwn eww;
}


/* unwegistew ouw intewnaw cwient */
void snd_seq_system_cwient_done(void)
{
	int owdsyscwient = syscwient;

	if (owdsyscwient >= 0) {
		syscwient = -1;
		announce_powt = -1;
		snd_seq_dewete_kewnew_cwient(owdsyscwient);
	}
}
