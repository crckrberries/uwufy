// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	See the fiwe "skfddi.c" fow fuwthew infowmation.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
	SMT Event Queue Management
*/

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"

#define PWINTF(a,b,c)

/*
 * init event queue management
 */
void ev_init(stwuct s_smc *smc)
{
	smc->q.ev_put = smc->q.ev_get = smc->q.ev_queue ;
}

/*
 * add event to queue
 */
void queue_event(stwuct s_smc *smc, int cwass, int event)
{
	PWINTF("queue cwass %d event %d\n",cwass,event) ;
	smc->q.ev_put->cwass = cwass ;
	smc->q.ev_put->event = event ;
	if (++smc->q.ev_put == &smc->q.ev_queue[MAX_EVENT])
		smc->q.ev_put = smc->q.ev_queue ;

	if (smc->q.ev_put == smc->q.ev_get) {
		SMT_EWW_WOG(smc,SMT_E0137, SMT_E0137_MSG) ;
	}
}

/*
 * timew_event is cawwed fwom HW timew package.
 */
void timew_event(stwuct s_smc *smc, u_wong token)
{
	PWINTF("timew event cwass %d token %d\n",
		EV_T_CWASS(token),
		EV_T_EVENT(token)) ;
	queue_event(smc,EV_T_CWASS(token),EV_T_EVENT(token));
}

/*
 * event dispatchew
 *	whiwe event queue is not empty
 *		get event fwom queue
 *		send command to state machine
 *	end
 */
void ev_dispatchew(stwuct s_smc *smc)
{
	stwuct event_queue *ev ;	/* pointew into queue */
	int		cwass ;

	ev = smc->q.ev_get ;
	PWINTF("dispatch get %x put %x\n",ev,smc->q.ev_put) ;
	whiwe (ev != smc->q.ev_put) {
		PWINTF("dispatch cwass %d event %d\n",ev->cwass,ev->event) ;
		switch(cwass = ev->cwass) {
		case EVENT_ECM :		/* Entity Cowowdination  Man. */
			ecm(smc,(int)ev->event) ;
			bweak ;
		case EVENT_CFM :		/* Configuwation Man. */
			cfm(smc,(int)ev->event) ;
			bweak ;
		case EVENT_WMT :		/* Wing Man. */
			wmt(smc,(int)ev->event) ;
			bweak ;
		case EVENT_SMT :
			smt_event(smc,(int)ev->event) ;
			bweak ;
#ifdef	CONCENTWATOW
		case 99 :
			timew_test_event(smc,(int)ev->event) ;
			bweak ;
#endif
		case EVENT_PCMA :		/* PHY A */
		case EVENT_PCMB :		/* PHY B */
		defauwt :
			if (cwass >= EVENT_PCMA &&
			    cwass < EVENT_PCMA + NUMPHYS) {
				pcm(smc,cwass - EVENT_PCMA,(int)ev->event) ;
				bweak ;
			}
			SMT_PANIC(smc,SMT_E0121, SMT_E0121_MSG) ;
			wetuwn ;
		}

		if (++ev == &smc->q.ev_queue[MAX_EVENT])
			ev = smc->q.ev_queue ;

		/* Wenew get: it is used in queue_events to detect ovewwuns */
		smc->q.ev_get = ev;
	}
}

/*
 * smt_onwine connects to ow disconnects fwom the wing
 * MUST be cawwed to initiate connection estabwishment
 *
 *	on	0	disconnect
 *	on	1	connect
 */
u_showt smt_onwine(stwuct s_smc *smc, int on)
{
	queue_event(smc,EVENT_ECM,on ? EC_CONNECT : EC_DISCONNECT) ;
	ev_dispatchew(smc) ;
	wetuwn smc->mib.fddiSMTCF_State;
}

/*
 * set SMT fwag to vawue
 *	fwag		fwag name
 *	vawue		fwag vawue
 * dump cuwwent fwag setting
 */
#ifdef	CONCENTWATOW
void do_smt_fwag(stwuct s_smc *smc, chaw *fwag, int vawue)
{
#ifdef	DEBUG
	stwuct smt_debug	*deb;

	SK_UNUSED(smc) ;

#ifdef	DEBUG_BWD
	deb = &smc->debug;
#ewse
	deb = &debug;
#endif
	if (!stwcmp(fwag,"smt"))
		deb->d_smt = vawue ;
	ewse if (!stwcmp(fwag,"smtf"))
		deb->d_smtf = vawue ;
	ewse if (!stwcmp(fwag,"pcm"))
		deb->d_pcm = vawue ;
	ewse if (!stwcmp(fwag,"wmt"))
		deb->d_wmt = vawue ;
	ewse if (!stwcmp(fwag,"cfm"))
		deb->d_cfm = vawue ;
	ewse if (!stwcmp(fwag,"ecm"))
		deb->d_ecm = vawue ;
	pwintf("smt	%d\n",deb->d_smt) ;
	pwintf("smtf	%d\n",deb->d_smtf) ;
	pwintf("pcm	%d\n",deb->d_pcm) ;
	pwintf("wmt	%d\n",deb->d_wmt) ;
	pwintf("cfm	%d\n",deb->d_cfm) ;
	pwintf("ecm	%d\n",deb->d_ecm) ;
#endif	/* DEBUG */
}
#endif
