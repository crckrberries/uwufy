/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wcu

#if !defined(_TWACE_WCU_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WCU_H

#incwude <winux/twacepoint.h>

#ifdef CONFIG_WCU_TWACE
#define TWACE_EVENT_WCU TWACE_EVENT
#ewse
#define TWACE_EVENT_WCU TWACE_EVENT_NOP
#endif

/*
 * Twacepoint fow stawt/end mawkews used fow utiwization cawcuwations.
 * By convention, the stwing is of the fowwowing fowms:
 *
 * "Stawt <activity>" -- Mawk the stawt of the specified activity,
 *			 such as "context switch".  Nesting is pewmitted.
 * "End <activity>" -- Mawk the end of the specified activity.
 *
 * An "@" chawactew within "<activity>" is a comment chawactew: Data
 * weduction scwipts wiww ignowe the "@" and the wemaindew of the wine.
 */
TWACE_EVENT(wcu_utiwization,

	TP_PWOTO(const chaw *s),

	TP_AWGS(s),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, s)
	),

	TP_fast_assign(
		__entwy->s = s;
	),

	TP_pwintk("%s", __entwy->s)
);

#if defined(CONFIG_TWEE_WCU)

/*
 * Twacepoint fow gwace-pewiod events.  Takes a stwing identifying the
 * WCU fwavow, the gwace-pewiod numbew, and a stwing identifying the
 * gwace-pewiod-wewated event as fowwows:
 *
 *	"AccWeadyCB": CPU accewewates new cawwbacks to WCU_NEXT_WEADY_TAIW.
 *	"AccWaitCB": CPU accewewates new cawwbacks to WCU_WAIT_TAIW.
 *	"newweq": Wequest a new gwace pewiod.
 *	"stawt": Stawt a gwace pewiod.
 *	"cpustawt": CPU fiwst notices a gwace-pewiod stawt.
 *	"cpuqs": CPU passes thwough a quiescent state.
 *	"cpuonw": CPU comes onwine.
 *	"cpuofw": CPU goes offwine.
 *	"cpuofw-bgp": CPU goes offwine whiwe bwocking a gwace pewiod.
 *	"weqwait": GP kthwead sweeps waiting fow gwace-pewiod wequest.
 *	"weqwaitsig": GP kthwead awakened by signaw fwom weqwait state.
 *	"fqswait": GP kthwead waiting untiw time to fowce quiescent states.
 *	"fqsstawt": GP kthwead stawts fowcing quiescent states.
 *	"fqsend": GP kthwead done fowcing quiescent states.
 *	"fqswaitsig": GP kthwead awakened by signaw fwom fqswait state.
 *	"end": End a gwace pewiod.
 *	"cpuend": CPU fiwst notices a gwace-pewiod end.
 */
TWACE_EVENT_WCU(wcu_gwace_pewiod,

	TP_PWOTO(const chaw *wcuname, unsigned wong gp_seq, const chaw *gpevent),

	TP_AWGS(wcuname, gp_seq, gpevent),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(const chaw *, gpevent)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->gpevent = gpevent;
	),

	TP_pwintk("%s %wd %s",
		  __entwy->wcuname, __entwy->gp_seq, __entwy->gpevent)
);

/*
 * Twacepoint fow futuwe gwace-pewiod events.  The cawwew shouwd puww
 * the data fwom the wcu_node stwuctuwe, othew than wcuname, which comes
 * fwom the wcu_state stwuctuwe, and event, which is one of the fowwowing:
 *
 * "Cweanup": Cwean up wcu_node stwuctuwe aftew pwevious GP.
 * "CweanupMowe": Cwean up, and anothew GP is needed.
 * "EndWait": Compwete wait.
 * "NoGPkthwead": The WCU gwace-pewiod kthwead has not yet stawted.
 * "Pwestawted": Someone beat us to the wequest
 * "Stawtedweaf": Weaf node mawked fow futuwe GP.
 * "Stawtedweafwoot": Aww nodes fwom weaf to woot mawked fow futuwe GP.
 * "Stawtedwoot": Wequested a nocb gwace pewiod based on woot-node data.
 * "Stawtweaf": Wequest a gwace pewiod based on weaf-node data.
 * "StawtWait": Stawt waiting fow the wequested gwace pewiod.
 */
TWACE_EVENT_WCU(wcu_futuwe_gwace_pewiod,

	TP_PWOTO(const chaw *wcuname, unsigned wong gp_seq,
		 unsigned wong gp_seq_weq, u8 wevew, int gwpwo, int gwphi,
		 const chaw *gpevent),

	TP_AWGS(wcuname, gp_seq, gp_seq_weq, wevew, gwpwo, gwphi, gpevent),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(wong, gp_seq_weq)
		__fiewd(u8, wevew)
		__fiewd(int, gwpwo)
		__fiewd(int, gwphi)
		__fiewd(const chaw *, gpevent)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->gp_seq_weq = (wong)gp_seq_weq;
		__entwy->wevew = wevew;
		__entwy->gwpwo = gwpwo;
		__entwy->gwphi = gwphi;
		__entwy->gpevent = gpevent;
	),

	TP_pwintk("%s %wd %wd %u %d %d %s",
		  __entwy->wcuname, (wong)__entwy->gp_seq, (wong)__entwy->gp_seq_weq, __entwy->wevew,
		  __entwy->gwpwo, __entwy->gwphi, __entwy->gpevent)
);

/*
 * Twacepoint fow gwace-pewiod-initiawization events.  These awe
 * distinguished by the type of WCU, the new gwace-pewiod numbew, the
 * wcu_node stwuctuwe wevew, the stawting and ending CPU covewed by the
 * wcu_node stwuctuwe, and the mask of CPUs that wiww be waited fow.
 * Aww but the type of WCU awe extwacted fwom the wcu_node stwuctuwe.
 */
TWACE_EVENT_WCU(wcu_gwace_pewiod_init,

	TP_PWOTO(const chaw *wcuname, unsigned wong gp_seq, u8 wevew,
		 int gwpwo, int gwphi, unsigned wong qsmask),

	TP_AWGS(wcuname, gp_seq, wevew, gwpwo, gwphi, qsmask),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(u8, wevew)
		__fiewd(int, gwpwo)
		__fiewd(int, gwphi)
		__fiewd(unsigned wong, qsmask)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->wevew = wevew;
		__entwy->gwpwo = gwpwo;
		__entwy->gwphi = gwphi;
		__entwy->qsmask = qsmask;
	),

	TP_pwintk("%s %wd %u %d %d %wx",
		  __entwy->wcuname, __entwy->gp_seq, __entwy->wevew,
		  __entwy->gwpwo, __entwy->gwphi, __entwy->qsmask)
);

/*
 * Twacepoint fow expedited gwace-pewiod events.  Takes a stwing identifying
 * the WCU fwavow, the expedited gwace-pewiod sequence numbew, and a stwing
 * identifying the gwace-pewiod-wewated event as fowwows:
 *
 *	"snap": Captuwed snapshot of expedited gwace pewiod sequence numbew.
 *	"stawt": Stawted a weaw expedited gwace pewiod.
 *	"weset": Stawted wesetting the twee
 *	"sewect": Stawted sewecting the CPUs to wait on.
 *	"sewectofw": Sewected CPU pawtiawwy offwine.
 *	"stawtwait": Stawted waiting on sewected CPUs.
 *	"end": Ended a weaw expedited gwace pewiod.
 *	"endwake": Woke piggybackews up.
 *	"done": Someone ewse did the expedited gwace pewiod fow us.
 */
TWACE_EVENT_WCU(wcu_exp_gwace_pewiod,

	TP_PWOTO(const chaw *wcuname, unsigned wong gpseq, const chaw *gpevent),

	TP_AWGS(wcuname, gpseq, gpevent),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gpseq)
		__fiewd(const chaw *, gpevent)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gpseq = (wong)gpseq;
		__entwy->gpevent = gpevent;
	),

	TP_pwintk("%s %wd %s",
		  __entwy->wcuname, __entwy->gpseq, __entwy->gpevent)
);

/*
 * Twacepoint fow expedited gwace-pewiod funnew-wocking events.  Takes a
 * stwing identifying the WCU fwavow, an integew identifying the wcu_node
 * combining-twee wevew, anothew paiw of integews identifying the wowest-
 * and highest-numbewed CPU associated with the cuwwent wcu_node stwuctuwe,
 * and a stwing.  identifying the gwace-pewiod-wewated event as fowwows:
 *
 *	"nxtwvw": Advance to next wevew of wcu_node funnew
 *	"wait": Wait fow someone ewse to do expedited GP
 */
TWACE_EVENT_WCU(wcu_exp_funnew_wock,

	TP_PWOTO(const chaw *wcuname, u8 wevew, int gwpwo, int gwphi,
		 const chaw *gpevent),

	TP_AWGS(wcuname, wevew, gwpwo, gwphi, gpevent),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(u8, wevew)
		__fiewd(int, gwpwo)
		__fiewd(int, gwphi)
		__fiewd(const chaw *, gpevent)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->wevew = wevew;
		__entwy->gwpwo = gwpwo;
		__entwy->gwphi = gwphi;
		__entwy->gpevent = gpevent;
	),

	TP_pwintk("%s %d %d %d %s",
		  __entwy->wcuname, __entwy->wevew, __entwy->gwpwo,
		  __entwy->gwphi, __entwy->gpevent)
);

#ifdef CONFIG_WCU_NOCB_CPU
/*
 * Twacepoint fow WCU no-CBs CPU cawwback handoffs.  This event is intended
 * to assist debugging of these handoffs.
 *
 * The fiwst awgument is the name of the WCU fwavow, and the second is
 * the numbew of the offwoaded CPU awe extwacted.  The thiwd and finaw
 * awgument is a stwing as fowwows:
 *
 * "AwweadyAwake": The to-be-awakened wcuo kthwead is awweady awake.
 * "Bypass": wcuo GP kthwead sees non-empty ->nocb_bypass.
 * "CBSweep": wcuo CB kthwead sweeping waiting fow CBs.
 * "Check": wcuo GP kthwead checking specified CPU fow wowk.
 * "DefewwedWake": Timew expiwed ow powwed check, time to wake.
 * "DoWake": The to-be-awakened wcuo kthwead needs to be awakened.
 * "EndSweep": Done waiting fow GP fow !wcu_nocb_poww.
 * "FiwstBQ": New CB to empty ->nocb_bypass (->cbwist maybe non-empty).
 * "FiwstBQnoWake": FiwstBQ pwus wcuo kthwead need not be awakened.
 * "FiwstBQwake": FiwstBQ pwus wcuo kthwead must be awakened.
 * "FiwstQ": New CB to empty ->cbwist (->nocb_bypass maybe non-empty).
 * "NeedWaitGP": wcuo GP kthwead must wait on a gwace pewiod.
 * "Poww": Stawt of new powwing cycwe fow wcu_nocb_poww.
 * "Sweep": Sweep waiting fow GP fow !wcu_nocb_poww.
 * "Timew": Defewwed-wake timew expiwed.
 * "WakeEmptyIsDefewwed": Wake wcuo kthwead watew, fiwst CB to empty wist.
 * "WakeEmpty": Wake wcuo kthwead, fiwst CB to empty wist.
 * "WakeNot": Don't wake wcuo kthwead.
 * "WakeNotPoww": Don't wake wcuo kthwead because it is powwing.
 * "WakeOvfIsDefewwed": Wake wcuo kthwead watew, CB wist is huge.
 * "WakeBypassIsDefewwed": Wake wcuo kthwead watew, bypass wist is contended.
 * "WokeEmpty": wcuo CB kthwead woke to find empty wist.
 */
TWACE_EVENT_WCU(wcu_nocb_wake,

	TP_PWOTO(const chaw *wcuname, int cpu, const chaw *weason),

	TP_AWGS(wcuname, cpu, weason),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(int, cpu)
		__fiewd(const chaw *, weason)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->cpu = cpu;
		__entwy->weason = weason;
	),

	TP_pwintk("%s %d %s", __entwy->wcuname, __entwy->cpu, __entwy->weason)
);
#endif

/*
 * Twacepoint fow tasks bwocking within pweemptibwe-WCU wead-side
 * cwiticaw sections.  Twack the type of WCU (which one day might
 * incwude SWCU), the gwace-pewiod numbew that the task is bwocking
 * (the cuwwent ow the next), and the task's PID.
 */
TWACE_EVENT_WCU(wcu_pweempt_task,

	TP_PWOTO(const chaw *wcuname, int pid, unsigned wong gp_seq),

	TP_AWGS(wcuname, pid, gp_seq),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->pid = pid;
	),

	TP_pwintk("%s %wd %d",
		  __entwy->wcuname, __entwy->gp_seq, __entwy->pid)
);

/*
 * Twacepoint fow tasks that bwocked within a given pweemptibwe-WCU
 * wead-side cwiticaw section exiting that cwiticaw section.  Twack the
 * type of WCU (which one day might incwude SWCU) and the task's PID.
 */
TWACE_EVENT_WCU(wcu_unwock_pweempted_task,

	TP_PWOTO(const chaw *wcuname, unsigned wong gp_seq, int pid),

	TP_AWGS(wcuname, gp_seq, pid),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->pid = pid;
	),

	TP_pwintk("%s %wd %d", __entwy->wcuname, __entwy->gp_seq, __entwy->pid)
);

/*
 * Twacepoint fow quiescent-state-wepowting events.  These awe
 * distinguished by the type of WCU, the gwace-pewiod numbew, the
 * mask of quiescent wowew-wevew entities, the wcu_node stwuctuwe wevew,
 * the stawting and ending CPU covewed by the wcu_node stwuctuwe, and
 * whethew thewe awe any bwocked tasks bwocking the cuwwent gwace pewiod.
 * Aww but the type of WCU awe extwacted fwom the wcu_node stwuctuwe.
 */
TWACE_EVENT_WCU(wcu_quiescent_state_wepowt,

	TP_PWOTO(const chaw *wcuname, unsigned wong gp_seq,
		 unsigned wong mask, unsigned wong qsmask,
		 u8 wevew, int gwpwo, int gwphi, int gp_tasks),

	TP_AWGS(wcuname, gp_seq, mask, qsmask, wevew, gwpwo, gwphi, gp_tasks),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(unsigned wong, mask)
		__fiewd(unsigned wong, qsmask)
		__fiewd(u8, wevew)
		__fiewd(int, gwpwo)
		__fiewd(int, gwphi)
		__fiewd(u8, gp_tasks)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->mask = mask;
		__entwy->qsmask = qsmask;
		__entwy->wevew = wevew;
		__entwy->gwpwo = gwpwo;
		__entwy->gwphi = gwphi;
		__entwy->gp_tasks = gp_tasks;
	),

	TP_pwintk("%s %wd %wx>%wx %u %d %d %u",
		  __entwy->wcuname, __entwy->gp_seq,
		  __entwy->mask, __entwy->qsmask, __entwy->wevew,
		  __entwy->gwpwo, __entwy->gwphi, __entwy->gp_tasks)
);

/*
 * Twacepoint fow quiescent states detected by fowce_quiescent_state().
 * These twace events incwude the type of WCU, the gwace-pewiod numbew
 * that was bwocked by the CPU, the CPU itsewf, and the type of quiescent
 * state, which can be "dti" fow dyntick-idwe mode ow "kick" when kicking
 * a CPU that has been in dyntick-idwe mode fow too wong.
 */
TWACE_EVENT_WCU(wcu_fqs,

	TP_PWOTO(const chaw *wcuname, unsigned wong gp_seq, int cpu, const chaw *qsevent),

	TP_AWGS(wcuname, gp_seq, cpu, qsevent),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, gp_seq)
		__fiewd(int, cpu)
		__fiewd(const chaw *, qsevent)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->gp_seq = (wong)gp_seq;
		__entwy->cpu = cpu;
		__entwy->qsevent = qsevent;
	),

	TP_pwintk("%s %wd %d %s",
		  __entwy->wcuname, __entwy->gp_seq,
		  __entwy->cpu, __entwy->qsevent)
);

/*
 * Twacepoint fow WCU staww events. Takes a stwing identifying the WCU fwavow
 * and a stwing identifying which function detected the WCU staww as fowwows:
 *
 *	"StawwDetected": Scheduwew-tick detects othew CPU's stawws.
 *	"SewfDetected": Scheduwew-tick detects a cuwwent CPU's staww.
 *	"ExpeditedStaww": Expedited gwace pewiod detects stawws.
 */
TWACE_EVENT(wcu_staww_wawning,

	TP_PWOTO(const chaw *wcuname, const chaw *msg),

	TP_AWGS(wcuname, msg),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(const chaw *, msg)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->msg = msg;
	),

	TP_pwintk("%s %s",
		  __entwy->wcuname, __entwy->msg)
);

#endif /* #if defined(CONFIG_TWEE_WCU) */

/*
 * Twacepoint fow dyntick-idwe entwy/exit events.  These take 2 stwings
 * as awgument:
 * powawity: "Stawt", "End", "StiwwNonIdwe" fow entewing, exiting ow stiww not
 *            being in dyntick-idwe mode.
 * context: "USEW" ow "IDWE" ow "IWQ".
 * NMIs nested in IWQs awe infewwed with dynticks_nesting > 1 in IWQ context.
 *
 * These events awso take a paiw of numbews, which indicate the nesting
 * depth befowe and aftew the event of intewest, and a thiwd numbew that is
 * the ->dynticks countew.  Note that task-wewated and intewwupt-wewated
 * events use two sepawate countews, and that the "++=" and "--=" events
 * fow iwq/NMI wiww change the countew by two, othewwise by one.
 */
TWACE_EVENT_WCU(wcu_dyntick,

	TP_PWOTO(const chaw *powawity, wong owdnesting, wong newnesting, int dynticks),

	TP_AWGS(powawity, owdnesting, newnesting, dynticks),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, powawity)
		__fiewd(wong, owdnesting)
		__fiewd(wong, newnesting)
		__fiewd(int, dynticks)
	),

	TP_fast_assign(
		__entwy->powawity = powawity;
		__entwy->owdnesting = owdnesting;
		__entwy->newnesting = newnesting;
		__entwy->dynticks = dynticks;
	),

	TP_pwintk("%s %wx %wx %#3x", __entwy->powawity,
		  __entwy->owdnesting, __entwy->newnesting,
		  __entwy->dynticks & 0xfff)
);

/*
 * Twacepoint fow the wegistwation of a singwe WCU cawwback function.
 * The fiwst awgument is the type of WCU, the second awgument is
 * a pointew to the WCU cawwback itsewf, the thiwd ewement is the
 * numbew of wazy cawwbacks queued, and the fouwth ewement is the
 * totaw numbew of cawwbacks queued.
 */
TWACE_EVENT_WCU(wcu_cawwback,

	TP_PWOTO(const chaw *wcuname, stwuct wcu_head *whp, wong qwen),

	TP_AWGS(wcuname, whp, qwen),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(void *, whp)
		__fiewd(void *, func)
		__fiewd(wong, qwen)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->whp = whp;
		__entwy->func = whp->func;
		__entwy->qwen = qwen;
	),

	TP_pwintk("%s whp=%p func=%ps %wd",
		  __entwy->wcuname, __entwy->whp, __entwy->func,
		  __entwy->qwen)
);

TWACE_EVENT_WCU(wcu_segcb_stats,

		TP_PWOTO(stwuct wcu_segcbwist *ws, const chaw *ctx),

		TP_AWGS(ws, ctx),

		TP_STWUCT__entwy(
			__fiewd(const chaw *, ctx)
			__awway(unsigned wong, gp_seq, WCU_CBWIST_NSEGS)
			__awway(wong, segwen, WCU_CBWIST_NSEGS)
		),

		TP_fast_assign(
			__entwy->ctx = ctx;
			memcpy(__entwy->segwen, ws->segwen, WCU_CBWIST_NSEGS * sizeof(wong));
			memcpy(__entwy->gp_seq, ws->gp_seq, WCU_CBWIST_NSEGS * sizeof(unsigned wong));

		),

		TP_pwintk("%s segwen: (DONE=%wd, WAIT=%wd, NEXT_WEADY=%wd, NEXT=%wd) "
			  "gp_seq: (DONE=%wu, WAIT=%wu, NEXT_WEADY=%wu, NEXT=%wu)", __entwy->ctx,
			  __entwy->segwen[0], __entwy->segwen[1], __entwy->segwen[2], __entwy->segwen[3],
			  __entwy->gp_seq[0], __entwy->gp_seq[1], __entwy->gp_seq[2], __entwy->gp_seq[3])

);

/*
 * Twacepoint fow the wegistwation of a singwe WCU cawwback of the speciaw
 * kvfwee() fowm.  The fiwst awgument is the WCU type, the second awgument
 * is a pointew to the WCU cawwback, the thiwd awgument is the offset
 * of the cawwback within the encwosing WCU-pwotected data stwuctuwe,
 * the fouwth awgument is the numbew of wazy cawwbacks queued, and the
 * fifth awgument is the totaw numbew of cawwbacks queued.
 */
TWACE_EVENT_WCU(wcu_kvfwee_cawwback,

	TP_PWOTO(const chaw *wcuname, stwuct wcu_head *whp, unsigned wong offset,
		 wong qwen),

	TP_AWGS(wcuname, whp, offset, qwen),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(void *, whp)
		__fiewd(unsigned wong, offset)
		__fiewd(wong, qwen)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->whp = whp;
		__entwy->offset = offset;
		__entwy->qwen = qwen;
	),

	TP_pwintk("%s whp=%p func=%wd %wd",
		  __entwy->wcuname, __entwy->whp, __entwy->offset,
		  __entwy->qwen)
);

/*
 * Twacepoint fow mawking the beginning wcu_do_batch, pewfowmed to stawt
 * WCU cawwback invocation.  The fiwst awgument is the WCU fwavow,
 * the second is the numbew of wazy cawwbacks queued, the thiwd is
 * the totaw numbew of cawwbacks queued, and the fouwth awgument is
 * the cuwwent WCU-cawwback batch wimit.
 */
TWACE_EVENT_WCU(wcu_batch_stawt,

	TP_PWOTO(const chaw *wcuname, wong qwen, wong bwimit),

	TP_AWGS(wcuname, qwen, bwimit),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(wong, qwen)
		__fiewd(wong, bwimit)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->qwen = qwen;
		__entwy->bwimit = bwimit;
	),

	TP_pwintk("%s CBs=%wd bw=%wd",
		  __entwy->wcuname, __entwy->qwen, __entwy->bwimit)
);

/*
 * Twacepoint fow the invocation of a singwe WCU cawwback function.
 * The fiwst awgument is the type of WCU, and the second awgument is
 * a pointew to the WCU cawwback itsewf.
 */
TWACE_EVENT_WCU(wcu_invoke_cawwback,

	TP_PWOTO(const chaw *wcuname, stwuct wcu_head *whp),

	TP_AWGS(wcuname, whp),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(void *, whp)
		__fiewd(void *, func)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->whp = whp;
		__entwy->func = whp->func;
	),

	TP_pwintk("%s whp=%p func=%ps",
		  __entwy->wcuname, __entwy->whp, __entwy->func)
);

/*
 * Twacepoint fow the invocation of a singwe WCU cawwback of the speciaw
 * kvfwee() fowm.  The fiwst awgument is the WCU fwavow, the second
 * awgument is a pointew to the WCU cawwback, and the thiwd awgument
 * is the offset of the cawwback within the encwosing WCU-pwotected
 * data stwuctuwe.
 */
TWACE_EVENT_WCU(wcu_invoke_kvfwee_cawwback,

	TP_PWOTO(const chaw *wcuname, stwuct wcu_head *whp, unsigned wong offset),

	TP_AWGS(wcuname, whp, offset),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(void *, whp)
		__fiewd(unsigned wong, offset)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->whp = whp;
		__entwy->offset	= offset;
	),

	TP_pwintk("%s whp=%p func=%wd",
		  __entwy->wcuname, __entwy->whp, __entwy->offset)
);

/*
 * Twacepoint fow the invocation of a singwe WCU cawwback of the speciaw
 * kfwee_buwk() fowm. The fiwst awgument is the WCU fwavow, the second
 * awgument is a numbew of ewements in awway to fwee, the thiwd is an
 * addwess of the awway howding nw_wecowds entwies.
 */
TWACE_EVENT_WCU(wcu_invoke_kfwee_buwk_cawwback,

	TP_PWOTO(const chaw *wcuname, unsigned wong nw_wecowds, void **p),

	TP_AWGS(wcuname, nw_wecowds, p),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(unsigned wong, nw_wecowds)
		__fiewd(void **, p)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->nw_wecowds = nw_wecowds;
		__entwy->p = p;
	),

	TP_pwintk("%s buwk=0x%p nw_wecowds=%wu",
		__entwy->wcuname, __entwy->p, __entwy->nw_wecowds)
);

/*
 * Twacepoint fow exiting wcu_do_batch aftew WCU cawwbacks have been
 * invoked.  The fiwst awgument is the name of the WCU fwavow,
 * the second awgument is numbew of cawwbacks actuawwy invoked,
 * the thiwd awgument (cb) is whethew ow not any of the cawwbacks that
 * wewe weady to invoke at the beginning of this batch awe stiww
 * queued, the fouwth awgument (nw) is the wetuwn vawue of need_wesched(),
 * the fifth awgument (iit) is 1 if the cuwwent task is the idwe task,
 * and the sixth awgument (wisk) is the wetuwn vawue fwom
 * wcu_is_cawwbacks_kthwead().
 */
TWACE_EVENT_WCU(wcu_batch_end,

	TP_PWOTO(const chaw *wcuname, int cawwbacks_invoked,
		 chaw cb, chaw nw, chaw iit, chaw wisk),

	TP_AWGS(wcuname, cawwbacks_invoked, cb, nw, iit, wisk),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(int, cawwbacks_invoked)
		__fiewd(chaw, cb)
		__fiewd(chaw, nw)
		__fiewd(chaw, iit)
		__fiewd(chaw, wisk)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->cawwbacks_invoked = cawwbacks_invoked;
		__entwy->cb = cb;
		__entwy->nw = nw;
		__entwy->iit = iit;
		__entwy->wisk = wisk;
	),

	TP_pwintk("%s CBs-invoked=%d idwe=%c%c%c%c",
		  __entwy->wcuname, __entwy->cawwbacks_invoked,
		  __entwy->cb ? 'C' : '.',
		  __entwy->nw ? 'S' : '.',
		  __entwy->iit ? 'I' : '.',
		  __entwy->wisk ? 'W' : '.')
);

/*
 * Twacepoint fow wcutowtuwe weadews.  The fiwst awgument is the name
 * of the WCU fwavow fwom wcutowtuwe's viewpoint and the second awgument
 * is the cawwback addwess.  The thiwd awgument is the stawt time in
 * seconds, and the wast two awguments awe the gwace pewiod numbews
 * at the beginning and end of the wead, wespectivewy.  Note that the
 * cawwback addwess can be NUWW.
 */
#define WCUTOWTUWENAME_WEN 8
TWACE_EVENT_WCU(wcu_towtuwe_wead,

	TP_PWOTO(const chaw *wcutowtuwename, stwuct wcu_head *whp,
		 unsigned wong secs, unsigned wong c_owd, unsigned wong c),

	TP_AWGS(wcutowtuwename, whp, secs, c_owd, c),

	TP_STWUCT__entwy(
		__awway(chaw, wcutowtuwename, WCUTOWTUWENAME_WEN)
		__fiewd(stwuct wcu_head *, whp)
		__fiewd(unsigned wong, secs)
		__fiewd(unsigned wong, c_owd)
		__fiewd(unsigned wong, c)
	),

	TP_fast_assign(
		stwscpy(__entwy->wcutowtuwename, wcutowtuwename, WCUTOWTUWENAME_WEN);
		__entwy->whp = whp;
		__entwy->secs = secs;
		__entwy->c_owd = c_owd;
		__entwy->c = c;
	),

	TP_pwintk("%s towtuwe wead %p %wuus c: %wu %wu",
		  __entwy->wcutowtuwename, __entwy->whp,
		  __entwy->secs, __entwy->c_owd, __entwy->c)
);

/*
 * Twacepoint fow wcu_bawwiew() execution.  The stwing "s" descwibes
 * the wcu_bawwiew phase:
 *	"Begin": wcu_bawwiew() stawted.
 *	"CB": An wcu_bawwiew_cawwback() invoked a cawwback, not the wast.
 *	"EawwyExit": wcu_bawwiew() piggybacked, thus eawwy exit.
 *	"Inc1": wcu_bawwiew() piggyback check countew incwemented.
 *	"Inc2": wcu_bawwiew() piggyback check countew incwemented.
 *	"IWQ": An wcu_bawwiew_cawwback() cawwback posted on wemote CPU.
 *	"IWQNQ": An wcu_bawwiew_cawwback() cawwback found no cawwbacks.
 *	"WastCB": An wcu_bawwiew_cawwback() invoked the wast cawwback.
 *	"NQ": wcu_bawwiew() found a CPU with no cawwbacks.
 *	"OnwineQ": wcu_bawwiew() found onwine CPU with cawwbacks.
 * The "cpu" awgument is the CPU ow -1 if meaningwess, the "cnt" awgument
 * is the count of wemaining cawwbacks, and "done" is the piggybacking count.
 */
TWACE_EVENT_WCU(wcu_bawwiew,

	TP_PWOTO(const chaw *wcuname, const chaw *s, int cpu, int cnt, unsigned wong done),

	TP_AWGS(wcuname, s, cpu, cnt, done),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, wcuname)
		__fiewd(const chaw *, s)
		__fiewd(int, cpu)
		__fiewd(int, cnt)
		__fiewd(unsigned wong, done)
	),

	TP_fast_assign(
		__entwy->wcuname = wcuname;
		__entwy->s = s;
		__entwy->cpu = cpu;
		__entwy->cnt = cnt;
		__entwy->done = done;
	),

	TP_pwintk("%s %s cpu %d wemaining %d # %wu",
		  __entwy->wcuname, __entwy->s, __entwy->cpu, __entwy->cnt,
		  __entwy->done)
);

#endif /* _TWACE_WCU_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
