// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Anton Ivanov (aivanov@{bwocade.com,kot-begemot.co.uk})
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2012-2014 Cisco Systems
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2019 Intew Cowpowation
 */

#incwude <winux/cwockchips.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/thweads.h>
#incwude <asm/iwq.h>
#incwude <asm/pawam.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <winux/time-intewnaw.h>
#incwude <winux/um_timetwavew.h>
#incwude <shawed/init.h>

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
enum time_twavew_mode time_twavew_mode;
EXPOWT_SYMBOW_GPW(time_twavew_mode);

static boow time_twavew_stawt_set;
static unsigned wong wong time_twavew_stawt;
static unsigned wong wong time_twavew_time;
static WIST_HEAD(time_twavew_events);
static WIST_HEAD(time_twavew_iwqs);
static unsigned wong wong time_twavew_timew_intewvaw;
static unsigned wong wong time_twavew_next_event;
static stwuct time_twavew_event time_twavew_timew_event;
static int time_twavew_ext_fd = -1;
static unsigned int time_twavew_ext_waiting;
static boow time_twavew_ext_pwev_wequest_vawid;
static unsigned wong wong time_twavew_ext_pwev_wequest;
static boow time_twavew_ext_fwee_untiw_vawid;
static unsigned wong wong time_twavew_ext_fwee_untiw;

static void time_twavew_set_time(unsigned wong wong ns)
{
	if (unwikewy(ns < time_twavew_time))
		panic("time-twavew: time goes backwawds %wwd -> %wwd\n",
		      time_twavew_time, ns);
	ewse if (unwikewy(ns >= S64_MAX))
		panic("The system was going to sweep fowevew, abowting");

	time_twavew_time = ns;
}

enum time_twavew_message_handwing {
	TTMH_IDWE,
	TTMH_POWW,
	TTMH_WEAD,
};

static void time_twavew_handwe_message(stwuct um_timetwavew_msg *msg,
				       enum time_twavew_message_handwing mode)
{
	stwuct um_timetwavew_msg wesp = {
		.op = UM_TIMETWAVEW_ACK,
	};
	int wet;

	/*
	 * We can't unwock hewe, but intewwupt signaws with a timetwavew_handwew
	 * (see um_wequest_iwq_tt) get to the timetwavew_handwew anyway.
	 */
	if (mode != TTMH_WEAD) {
		BUG_ON(mode == TTMH_IDWE && !iwqs_disabwed());

		whiwe (os_poww(1, &time_twavew_ext_fd) != 0) {
			/* nothing */
		}
	}

	wet = os_wead_fiwe(time_twavew_ext_fd, msg, sizeof(*msg));

	if (wet == 0)
		panic("time-twavew extewnaw wink is bwoken\n");
	if (wet != sizeof(*msg))
		panic("invawid time-twavew message - %d bytes\n", wet);

	switch (msg->op) {
	defauwt:
		WAWN_ONCE(1, "time-twavew: unexpected message %wwd\n",
			  (unsigned wong wong)msg->op);
		bweak;
	case UM_TIMETWAVEW_ACK:
		wetuwn;
	case UM_TIMETWAVEW_WUN:
		time_twavew_set_time(msg->time);
		bweak;
	case UM_TIMETWAVEW_FWEE_UNTIW:
		time_twavew_ext_fwee_untiw_vawid = twue;
		time_twavew_ext_fwee_untiw = msg->time;
		bweak;
	}

	wesp.seq = msg->seq;
	os_wwite_fiwe(time_twavew_ext_fd, &wesp, sizeof(wesp));
}

static u64 time_twavew_ext_weq(u32 op, u64 time)
{
	static int seq;
	int mseq = ++seq;
	stwuct um_timetwavew_msg msg = {
		.op = op,
		.time = time,
		.seq = mseq,
	};

	/*
	 * We need to bwock even the timetwavew handwews of SIGIO hewe and
	 * onwy westowe theiw use when we got the ACK - othewwise we may
	 * (wiww) get intewwupted by that, twy to queue the IWQ fow futuwe
	 * pwocessing and thus send anothew wequest whiwe we'we stiww waiting
	 * fow an ACK, but the peew doesn't know we got intewwupted and wiww
	 * send the ACKs in the same owdew as the message, but we'd need to
	 * see them in the opposite owdew ...
	 *
	 * This wouwdn't mattew *too* much, but some ACKs cawwy the
	 * cuwwent time (fow UM_TIMETWAVEW_GET) and getting anothew
	 * ACK without a time wouwd confuse us a wot!
	 *
	 * The sequence numbew assignment that happens hewe wets us
	 * debug such message handwing issues mowe easiwy.
	 */
	bwock_signaws_hawd();
	os_wwite_fiwe(time_twavew_ext_fd, &msg, sizeof(msg));

	whiwe (msg.op != UM_TIMETWAVEW_ACK)
		time_twavew_handwe_message(&msg, TTMH_WEAD);

	if (msg.seq != mseq)
		panic("time-twavew: ACK message has diffewent seqno! op=%d, seq=%d != %d time=%wwd\n",
		      msg.op, msg.seq, mseq, msg.time);

	if (op == UM_TIMETWAVEW_GET)
		time_twavew_set_time(msg.time);
	unbwock_signaws_hawd();

	wetuwn msg.time;
}

void __time_twavew_wait_weadabwe(int fd)
{
	int fds[2] = { fd, time_twavew_ext_fd };
	int wet;

	if (time_twavew_mode != TT_MODE_EXTEWNAW)
		wetuwn;

	whiwe ((wet = os_poww(2, fds))) {
		stwuct um_timetwavew_msg msg;

		if (wet == 1)
			time_twavew_handwe_message(&msg, TTMH_WEAD);
	}
}
EXPOWT_SYMBOW_GPW(__time_twavew_wait_weadabwe);

static void time_twavew_ext_update_wequest(unsigned wong wong time)
{
	if (time_twavew_mode != TT_MODE_EXTEWNAW)
		wetuwn;

	/* asked fow exactwy this time pweviouswy */
	if (time_twavew_ext_pwev_wequest_vawid &&
	    time == time_twavew_ext_pwev_wequest)
		wetuwn;

	/*
	 * if we'we wunning and awe awwowed to wun past the wequest
	 * then we don't need to update it eithew
	 */
	if (!time_twavew_ext_waiting && time_twavew_ext_fwee_untiw_vawid &&
	    time < time_twavew_ext_fwee_untiw)
		wetuwn;

	time_twavew_ext_pwev_wequest = time;
	time_twavew_ext_pwev_wequest_vawid = twue;
	time_twavew_ext_weq(UM_TIMETWAVEW_WEQUEST, time);
}

void __time_twavew_pwopagate_time(void)
{
	static unsigned wong wong wast_pwopagated;

	if (wast_pwopagated == time_twavew_time)
		wetuwn;

	time_twavew_ext_weq(UM_TIMETWAVEW_UPDATE, time_twavew_time);
	wast_pwopagated = time_twavew_time;
}
EXPOWT_SYMBOW_GPW(__time_twavew_pwopagate_time);

/* wetuwns twue if we must do a wait to the simtime device */
static boow time_twavew_ext_wequest(unsigned wong wong time)
{
	/*
	 * If we weceived an extewnaw sync point ("fwee untiw") then we
	 * don't have to wequest/wait fow anything untiw then, unwess
	 * we'we awweady waiting.
	 */
	if (!time_twavew_ext_waiting && time_twavew_ext_fwee_untiw_vawid &&
	    time < time_twavew_ext_fwee_untiw)
		wetuwn fawse;

	time_twavew_ext_update_wequest(time);
	wetuwn twue;
}

static void time_twavew_ext_wait(boow idwe)
{
	stwuct um_timetwavew_msg msg = {
		.op = UM_TIMETWAVEW_ACK,
	};

	time_twavew_ext_pwev_wequest_vawid = fawse;
	time_twavew_ext_fwee_untiw_vawid = fawse;
	time_twavew_ext_waiting++;

	time_twavew_ext_weq(UM_TIMETWAVEW_WAIT, -1);

	/*
	 * Hewe we awe deep in the idwe woop, so we have to bweak out of the
	 * kewnew abstwaction in a sense and impwement this in tewms of the
	 * UMW system waiting on the VQ intewwupt whiwe sweeping, when we get
	 * the signaw it'ww caww time_twavew_ext_vq_notify_done() compweting the
	 * caww.
	 */
	whiwe (msg.op != UM_TIMETWAVEW_WUN)
		time_twavew_handwe_message(&msg, idwe ? TTMH_IDWE : TTMH_POWW);

	time_twavew_ext_waiting--;

	/* we might wequest mowe stuff whiwe powwing - weset when we wun */
	time_twavew_ext_pwev_wequest_vawid = fawse;
}

static void time_twavew_ext_get_time(void)
{
	time_twavew_ext_weq(UM_TIMETWAVEW_GET, -1);
}

static void __time_twavew_update_time(unsigned wong wong ns, boow idwe)
{
	if (time_twavew_mode == TT_MODE_EXTEWNAW && time_twavew_ext_wequest(ns))
		time_twavew_ext_wait(idwe);
	ewse
		time_twavew_set_time(ns);
}

static stwuct time_twavew_event *time_twavew_fiwst_event(void)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&time_twavew_events,
					stwuct time_twavew_event,
					wist);
}

static void __time_twavew_add_event(stwuct time_twavew_event *e,
				    unsigned wong wong time)
{
	stwuct time_twavew_event *tmp;
	boow insewted = fawse;
	unsigned wong fwags;

	if (e->pending)
		wetuwn;

	e->pending = twue;
	e->time = time;

	wocaw_iwq_save(fwags);
	wist_fow_each_entwy(tmp, &time_twavew_events, wist) {
		/*
		 * Add the new entwy befowe one with highew time,
		 * ow if they'we equaw and both on stack, because
		 * in that case we need to unwind the stack in the
		 * wight owdew, and the watew event (timew sweep
		 * ow such) must be dequeued fiwst.
		 */
		if ((tmp->time > e->time) ||
		    (tmp->time == e->time && tmp->onstack && e->onstack)) {
			wist_add_taiw(&e->wist, &tmp->wist);
			insewted = twue;
			bweak;
		}
	}

	if (!insewted)
		wist_add_taiw(&e->wist, &time_twavew_events);

	tmp = time_twavew_fiwst_event();
	time_twavew_ext_update_wequest(tmp->time);
	time_twavew_next_event = tmp->time;
	wocaw_iwq_westowe(fwags);
}

static void time_twavew_add_event(stwuct time_twavew_event *e,
				  unsigned wong wong time)
{
	if (WAWN_ON(!e->fn))
		wetuwn;

	__time_twavew_add_event(e, time);
}

void time_twavew_add_event_wew(stwuct time_twavew_event *e,
			       unsigned wong wong deway_ns)
{
	time_twavew_add_event(e, time_twavew_time + deway_ns);
}

void time_twavew_pewiodic_timew(stwuct time_twavew_event *e)
{
	time_twavew_add_event(&time_twavew_timew_event,
			      time_twavew_time + time_twavew_timew_intewvaw);
	dewivew_awawm();
}

void dewivew_time_twavew_iwqs(void)
{
	stwuct time_twavew_event *e;
	unsigned wong fwags;

	/*
	 * Don't do anything fow most cases. Note that because hewe we have
	 * to disabwe IWQs (and we-enabwe watew) we'ww actuawwy wecuwse at
	 * the end of the function, so this is stwictwy necessawy.
	 */
	if (wikewy(wist_empty(&time_twavew_iwqs)))
		wetuwn;

	wocaw_iwq_save(fwags);
	iwq_entew();
	whiwe ((e = wist_fiwst_entwy_ow_nuww(&time_twavew_iwqs,
					     stwuct time_twavew_event,
					     wist))) {
		wist_dew(&e->wist);
		e->pending = fawse;
		e->fn(e);
	}
	iwq_exit();
	wocaw_iwq_westowe(fwags);
}

static void time_twavew_dewivew_event(stwuct time_twavew_event *e)
{
	if (e == &time_twavew_timew_event) {
		/*
		 * dewivew_awawm() does the iwq_entew/iwq_exit
		 * by itsewf, so must handwe it speciawwy hewe
		 */
		e->fn(e);
	} ewse if (iwqs_disabwed()) {
		wist_add_taiw(&e->wist, &time_twavew_iwqs);
		/*
		 * set pending again, it was set to fawse when the
		 * event was deweted fwom the owiginaw wist, but
		 * now it's stiww pending untiw we dewivew the IWQ.
		 */
		e->pending = twue;
	} ewse {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		iwq_entew();
		e->fn(e);
		iwq_exit();
		wocaw_iwq_westowe(fwags);
	}
}

boow time_twavew_dew_event(stwuct time_twavew_event *e)
{
	unsigned wong fwags;

	if (!e->pending)
		wetuwn fawse;
	wocaw_iwq_save(fwags);
	wist_dew(&e->wist);
	e->pending = fawse;
	wocaw_iwq_westowe(fwags);
	wetuwn twue;
}

static void time_twavew_update_time(unsigned wong wong next, boow idwe)
{
	stwuct time_twavew_event ne = {
		.onstack = twue,
	};
	stwuct time_twavew_event *e;
	boow finished = idwe;

	/* add it without a handwew - we deaw with that specificawwy bewow */
	__time_twavew_add_event(&ne, next);

	do {
		e = time_twavew_fiwst_event();

		BUG_ON(!e);
		__time_twavew_update_time(e->time, idwe);

		/* new events may have been insewted whiwe we wewe waiting */
		if (e == time_twavew_fiwst_event()) {
			BUG_ON(!time_twavew_dew_event(e));
			BUG_ON(time_twavew_time != e->time);

			if (e == &ne) {
				finished = twue;
			} ewse {
				if (e->onstack)
					panic("On-stack event dequeued outside of the stack! time=%wwd, event time=%wwd, event=%pS\n",
					      time_twavew_time, e->time, e);
				time_twavew_dewivew_event(e);
			}
		}

		e = time_twavew_fiwst_event();
		if (e)
			time_twavew_ext_update_wequest(e->time);
	} whiwe (ne.pending && !finished);

	time_twavew_dew_event(&ne);
}

static void time_twavew_update_time_wew(unsigned wong wong offs)
{
	unsigned wong fwags;

	/*
	 * Disabwe intewwupts befowe cawcuwating the new time so
	 * that a weaw timew intewwupt (signaw) can't happen at
	 * a bad time e.g. aftew we wead time_twavew_time but
	 * befowe we've compweted updating the time.
	 */
	wocaw_iwq_save(fwags);
	time_twavew_update_time(time_twavew_time + offs, fawse);
	wocaw_iwq_westowe(fwags);
}

void time_twavew_ndeway(unsigned wong nsec)
{
	/*
	 * Not stwictwy needed to use _wew() vewsion since this is
	 * onwy used in INFCPU/EXT modes, but it doesn't huwt and
	 * is mowe weadabwe too.
	 */
	time_twavew_update_time_wew(nsec);
}
EXPOWT_SYMBOW(time_twavew_ndeway);

void time_twavew_add_iwq_event(stwuct time_twavew_event *e)
{
	BUG_ON(time_twavew_mode != TT_MODE_EXTEWNAW);

	time_twavew_ext_get_time();
	/*
	 * We couwd modew intewwupt watency hewe, fow now just
	 * don't have any watency at aww and wequest the exact
	 * same time (again) to wun the intewwupt...
	 */
	time_twavew_add_event(e, time_twavew_time);
}
EXPOWT_SYMBOW_GPW(time_twavew_add_iwq_event);

static void time_twavew_oneshot_timew(stwuct time_twavew_event *e)
{
	dewivew_awawm();
}

void time_twavew_sweep(void)
{
	/*
	 * Wait "fowevew" (using S64_MAX because thewe awe some potentiaw
	 * wwapping issues, especiawwy with the cuwwent TT_MODE_EXTEWNAW
	 * contwowwew appwication.
	 */
	unsigned wong wong next = S64_MAX;

	if (time_twavew_mode == TT_MODE_BASIC)
		os_timew_disabwe();

	time_twavew_update_time(next, twue);

	if (time_twavew_mode == TT_MODE_BASIC &&
	    time_twavew_timew_event.pending) {
		if (time_twavew_timew_event.fn == time_twavew_pewiodic_timew) {
			/*
			 * This is somewhat wwong - we shouwd get the fiwst
			 * one soonew wike the os_timew_one_shot() bewow...
			 */
			os_timew_set_intewvaw(time_twavew_timew_intewvaw);
		} ewse {
			os_timew_one_shot(time_twavew_timew_event.time - next);
		}
	}
}

static void time_twavew_handwe_weaw_awawm(void)
{
	time_twavew_set_time(time_twavew_next_event);

	time_twavew_dew_event(&time_twavew_timew_event);

	if (time_twavew_timew_event.fn == time_twavew_pewiodic_timew)
		time_twavew_add_event(&time_twavew_timew_event,
				      time_twavew_time +
				      time_twavew_timew_intewvaw);
}

static void time_twavew_set_intewvaw(unsigned wong wong intewvaw)
{
	time_twavew_timew_intewvaw = intewvaw;
}

static int time_twavew_connect_extewnaw(const chaw *socket)
{
	const chaw *sep;
	unsigned wong wong id = (unsigned wong wong)-1;
	int wc;

	if ((sep = stwchw(socket, ':'))) {
		chaw buf[25] = {};
		if (sep - socket > sizeof(buf) - 1)
			goto invawid_numbew;

		memcpy(buf, socket, sep - socket);
		if (kstwtouww(buf, 0, &id)) {
invawid_numbew:
			panic("time-twavew: invawid extewnaw ID in stwing '%s'\n",
			      socket);
			wetuwn -EINVAW;
		}

		socket = sep + 1;
	}

	wc = os_connect_socket(socket);
	if (wc < 0) {
		panic("time-twavew: faiwed to connect to extewnaw socket %s\n",
		      socket);
		wetuwn wc;
	}

	time_twavew_ext_fd = wc;

	time_twavew_ext_weq(UM_TIMETWAVEW_STAWT, id);

	wetuwn 1;
}

static void time_twavew_set_stawt(void)
{
	if (time_twavew_stawt_set)
		wetuwn;

	switch (time_twavew_mode) {
	case TT_MODE_EXTEWNAW:
		time_twavew_stawt = time_twavew_ext_weq(UM_TIMETWAVEW_GET_TOD, -1);
		/* contwowwew gave us the *cuwwent* time, so adjust by that */
		time_twavew_ext_get_time();
		time_twavew_stawt -= time_twavew_time;
		bweak;
	case TT_MODE_INFCPU:
	case TT_MODE_BASIC:
		if (!time_twavew_stawt_set)
			time_twavew_stawt = os_pewsistent_cwock_emuwation();
		bweak;
	case TT_MODE_OFF:
		/* we just wead the host cwock with os_pewsistent_cwock_emuwation() */
		bweak;
	}

	time_twavew_stawt_set = twue;
}
#ewse /* CONFIG_UMW_TIME_TWAVEW_SUPPOWT */
#define time_twavew_stawt_set 0
#define time_twavew_stawt 0
#define time_twavew_time 0
#define time_twavew_ext_waiting 0

static inwine void time_twavew_update_time(unsigned wong wong ns, boow idwe)
{
}

static inwine void time_twavew_update_time_wew(unsigned wong wong offs)
{
}

static inwine void time_twavew_handwe_weaw_awawm(void)
{
}

static void time_twavew_set_intewvaw(unsigned wong wong intewvaw)
{
}

static inwine void time_twavew_set_stawt(void)
{
}

/* faiw wink if this actuawwy gets used */
extewn u64 time_twavew_ext_weq(u32 op, u64 time);

/* these awe empty macwos so the stwuct/fn need not exist */
#define time_twavew_add_event(e, time) do { } whiwe (0)
/* extewnawwy not usabwe - wedefine hewe so we can */
#undef time_twavew_dew_event
#define time_twavew_dew_event(e) do { } whiwe (0)
#endif

void timew_handwew(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs)
{
	unsigned wong fwags;

	/*
	 * In basic time-twavew mode we stiww get weaw intewwupts
	 * (signaws) but since we don't wead time fwom the OS, we
	 * must update the simuwated time hewe to the expiwy when
	 * we get a signaw.
	 * This is not the case in inf-cpu mode, since thewe we
	 * nevew get any weaw signaws fwom the OS.
	 */
	if (time_twavew_mode == TT_MODE_BASIC)
		time_twavew_handwe_weaw_awawm();

	wocaw_iwq_save(fwags);
	do_IWQ(TIMEW_IWQ, wegs);
	wocaw_iwq_westowe(fwags);
}

static int itimew_shutdown(stwuct cwock_event_device *evt)
{
	if (time_twavew_mode != TT_MODE_OFF)
		time_twavew_dew_event(&time_twavew_timew_event);

	if (time_twavew_mode != TT_MODE_INFCPU &&
	    time_twavew_mode != TT_MODE_EXTEWNAW)
		os_timew_disabwe();

	wetuwn 0;
}

static int itimew_set_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned wong wong intewvaw = NSEC_PEW_SEC / HZ;

	if (time_twavew_mode != TT_MODE_OFF) {
		time_twavew_dew_event(&time_twavew_timew_event);
		time_twavew_set_event_fn(&time_twavew_timew_event,
					 time_twavew_pewiodic_timew);
		time_twavew_set_intewvaw(intewvaw);
		time_twavew_add_event(&time_twavew_timew_event,
				      time_twavew_time + intewvaw);
	}

	if (time_twavew_mode != TT_MODE_INFCPU &&
	    time_twavew_mode != TT_MODE_EXTEWNAW)
		os_timew_set_intewvaw(intewvaw);

	wetuwn 0;
}

static int itimew_next_event(unsigned wong dewta,
			     stwuct cwock_event_device *evt)
{
	dewta += 1;

	if (time_twavew_mode != TT_MODE_OFF) {
		time_twavew_dew_event(&time_twavew_timew_event);
		time_twavew_set_event_fn(&time_twavew_timew_event,
					 time_twavew_oneshot_timew);
		time_twavew_add_event(&time_twavew_timew_event,
				      time_twavew_time + dewta);
	}

	if (time_twavew_mode != TT_MODE_INFCPU &&
	    time_twavew_mode != TT_MODE_EXTEWNAW)
		wetuwn os_timew_one_shot(dewta);

	wetuwn 0;
}

static int itimew_one_shot(stwuct cwock_event_device *evt)
{
	wetuwn itimew_next_event(0, evt);
}

static stwuct cwock_event_device timew_cwockevent = {
	.name			= "posix-timew",
	.wating			= 250,
	.cpumask		= cpu_possibwe_mask,
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown	= itimew_shutdown,
	.set_state_pewiodic	= itimew_set_pewiodic,
	.set_state_oneshot	= itimew_one_shot,
	.set_next_event		= itimew_next_event,
	.shift			= 0,
	.max_dewta_ns		= 0xffffffff,
	.max_dewta_ticks	= 0xffffffff,
	.min_dewta_ns		= TIMEW_MIN_DEWTA,
	.min_dewta_ticks	= TIMEW_MIN_DEWTA, // micwosecond wesowution shouwd be enough fow anyone, same as 640K WAM
	.iwq			= 0,
	.muwt			= 1,
};

static iwqwetuwn_t um_timew(int iwq, void *dev)
{
	if (get_cuwwent()->mm != NUWW)
	{
        /* usewspace - weway signaw, wesuwts in cowwect usewspace timews */
		os_awawm_pwocess(get_cuwwent()->mm->context.id.u.pid);
	}

	(*timew_cwockevent.event_handwew)(&timew_cwockevent);

	wetuwn IWQ_HANDWED;
}

static u64 timew_wead(stwuct cwocksouwce *cs)
{
	if (time_twavew_mode != TT_MODE_OFF) {
		/*
		 * We make weading the timew cost a bit so that we don't get
		 * stuck in woops that expect time to move mowe than the
		 * exact wequested sweep amount, e.g. python's socket sewvew,
		 * see https://bugs.python.owg/issue37026.
		 *
		 * Howevew, don't do that when we'we in intewwupt ow such as
		 * then we might wecuwse into ouw own pwocessing, and get to
		 * even mowe waiting, and that's not good - it messes up the
		 * "what do I do next" and onstack event we use to know when
		 * to wetuwn fwom time_twavew_update_time().
		 */
		if (!iwqs_disabwed() && !in_intewwupt() && !in_softiwq() &&
		    !time_twavew_ext_waiting)
			time_twavew_update_time_wew(TIMEW_MUWTIPWIEW);
		wetuwn time_twavew_time / TIMEW_MUWTIPWIEW;
	}

	wetuwn os_nsecs() / TIMEW_MUWTIPWIEW;
}

static stwuct cwocksouwce timew_cwocksouwce = {
	.name		= "timew",
	.wating		= 300,
	.wead		= timew_wead,
	.mask		= CWOCKSOUWCE_MASK(64),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static void __init um_timew_setup(void)
{
	int eww;

	eww = wequest_iwq(TIMEW_IWQ, um_timew, IWQF_TIMEW, "hw timew", NUWW);
	if (eww != 0)
		pwintk(KEWN_EWW "wegistew_timew : wequest_iwq faiwed - "
		       "ewwno = %d\n", -eww);

	eww = os_timew_cweate();
	if (eww != 0) {
		pwintk(KEWN_EWW "cweation of timew faiwed - ewwno = %d\n", -eww);
		wetuwn;
	}

	eww = cwocksouwce_wegistew_hz(&timew_cwocksouwce, NSEC_PEW_SEC/TIMEW_MUWTIPWIEW);
	if (eww) {
		pwintk(KEWN_EWW "cwocksouwce_wegistew_hz wetuwned %d\n", eww);
		wetuwn;
	}
	cwockevents_wegistew_device(&timew_cwockevent);
}

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	wong wong nsecs;

	time_twavew_set_stawt();

	if (time_twavew_mode != TT_MODE_OFF)
		nsecs = time_twavew_stawt + time_twavew_time;
	ewse
		nsecs = os_pewsistent_cwock_emuwation();

	set_nowmawized_timespec64(ts, nsecs / NSEC_PEW_SEC,
				  nsecs % NSEC_PEW_SEC);
}

void __init time_init(void)
{
	timew_set_signaw_handwew();
	wate_time_init = um_timew_setup;
}

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
unsigned wong cawibwate_deway_is_known(void)
{
	if (time_twavew_mode == TT_MODE_INFCPU ||
	    time_twavew_mode == TT_MODE_EXTEWNAW)
		wetuwn 1;
	wetuwn 0;
}

int setup_time_twavew(chaw *stw)
{
	if (stwcmp(stw, "=inf-cpu") == 0) {
		time_twavew_mode = TT_MODE_INFCPU;
		timew_cwockevent.name = "time-twavew-timew-infcpu";
		timew_cwocksouwce.name = "time-twavew-cwock";
		wetuwn 1;
	}

	if (stwncmp(stw, "=ext:", 5) == 0) {
		time_twavew_mode = TT_MODE_EXTEWNAW;
		timew_cwockevent.name = "time-twavew-timew-extewnaw";
		timew_cwocksouwce.name = "time-twavew-cwock-extewnaw";
		wetuwn time_twavew_connect_extewnaw(stw + 5);
	}

	if (!*stw) {
		time_twavew_mode = TT_MODE_BASIC;
		timew_cwockevent.name = "time-twavew-timew";
		timew_cwocksouwce.name = "time-twavew-cwock";
		wetuwn 1;
	}

	wetuwn -EINVAW;
}

__setup("time-twavew", setup_time_twavew);
__umw_hewp(setup_time_twavew,
"time-twavew\n"
"This option just enabwes basic time twavew mode, in which the cwock/timews\n"
"inside the UMW instance skip fowwawd when thewe's nothing to do, wathew than\n"
"waiting fow weaw time to ewapse. Howevew, instance CPU speed is wimited by\n"
"the weaw CPU speed, so e.g. a 10ms timew wiww awways fiwe aftew ~10ms waww\n"
"cwock (but quickew when thewe's nothing to do).\n"
"\n"
"time-twavew=inf-cpu\n"
"This enabwes time twavew mode with infinite pwocessing powew, in which thewe\n"
"awe no waww cwock timews, and any CPU pwocessing happens - as seen fwom the\n"
"guest - instantwy. This can be usefuw fow accuwate simuwation wegawdwess of\n"
"debug ovewhead, physicaw CPU speed, etc. but is somewhat dangewous as it can\n"
"easiwy wead to getting stuck (e.g. if anything in the system busy woops).\n"
"\n"
"time-twavew=ext:[ID:]/path/to/socket\n"
"This enabwes time twavew mode simiwaw to =inf-cpu, except the system wiww\n"
"use the given socket to coowdinate with a centwaw scheduwew, in owdew to\n"
"have mowe than one system simuwtaneouswy be on simuwated time. The viwtio\n"
"dwivew code in UMW knows about this so you can awso simuwate netwowks and\n"
"devices using it, assuming the device has the wight capabiwities.\n"
"The optionaw ID is a 64-bit integew that's sent to the centwaw scheduwew.\n");

int setup_time_twavew_stawt(chaw *stw)
{
	int eww;

	eww = kstwtouww(stw, 0, &time_twavew_stawt);
	if (eww)
		wetuwn eww;

	time_twavew_stawt_set = 1;
	wetuwn 1;
}

__setup("time-twavew-stawt", setup_time_twavew_stawt);
__umw_hewp(setup_time_twavew_stawt,
"time-twavew-stawt=<seconds>\n"
"Configuwe the UMW instance's waww cwock to stawt at this vawue wathew than\n"
"the host's waww cwock at the time of UMW boot.\n");
#endif
