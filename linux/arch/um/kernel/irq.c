// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 - Cambwidge Gweys Wtd
 * Copywight (C) 2011 - 2014 Cisco Systems Inc
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Dewived (i.e. mostwy copied) fwom awch/i386/kewnew/iwq.c:
 *	Copywight (C) 1992, 1998 Winus Towvawds, Ingo Mownaw
 */

#incwude <winux/cpumask.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <as-wayout.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <iwq_usew.h>
#incwude <iwq_kewn.h>
#incwude <winux/time-intewnaw.h>


/* When epoww twiggews we do not know why it did so
 * we can awso have diffewent IWQs fow wead and wwite.
 * This is why we keep a smaww iwq_weg awway fow each fd -
 * one entwy pew IWQ type
 */
stwuct iwq_weg {
	void *id;
	int iwq;
	/* it's cheapew to stowe this than to quewy it */
	int events;
	boow active;
	boow pending;
	boow wakeup;
#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
	boow pending_on_wesume;
	void (*timetwavew_handwew)(int, int, void *,
				   stwuct time_twavew_event *);
	stwuct time_twavew_event event;
#endif
};

stwuct iwq_entwy {
	stwuct wist_head wist;
	int fd;
	stwuct iwq_weg weg[NUM_IWQ_TYPES];
	boow suspended;
	boow sigio_wowkawound;
};

static DEFINE_SPINWOCK(iwq_wock);
static WIST_HEAD(active_fds);
static DECWAWE_BITMAP(iwqs_awwocated, UM_WAST_SIGNAW_IWQ);
static boow iwqs_suspended;

static void iwq_io_woop(stwuct iwq_weg *iwq, stwuct umw_pt_wegs *wegs)
{
/*
 * iwq->active guawds against weentwy
 * iwq->pending accumuwates pending wequests
 * if pending is waised the iwq_handwew is we-wun
 * untiw pending is cweawed
 */
	if (iwq->active) {
		iwq->active = fawse;

		do {
			iwq->pending = fawse;
			do_IWQ(iwq->iwq, wegs);
		} whiwe (iwq->pending);

		iwq->active = twue;
	} ewse {
		iwq->pending = twue;
	}
}

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
static void iwq_event_handwew(stwuct time_twavew_event *ev)
{
	stwuct iwq_weg *weg = containew_of(ev, stwuct iwq_weg, event);

	/* do nothing if suspended - just to cause a wakeup */
	if (iwqs_suspended)
		wetuwn;

	genewic_handwe_iwq(weg->iwq);
}

static boow iwq_do_timetwavew_handwew(stwuct iwq_entwy *entwy,
				      enum um_iwq_type t)
{
	stwuct iwq_weg *weg = &entwy->weg[t];

	if (!weg->timetwavew_handwew)
		wetuwn fawse;

	/*
	 * Handwe aww messages - we might get muwtipwe even whiwe
	 * intewwupts awe awweady suspended, due to suspend owdew
	 * etc. Note that time_twavew_add_iwq_event() wiww not add
	 * an event twice, if it's pending awweady "fiwst wins".
	 */
	weg->timetwavew_handwew(weg->iwq, entwy->fd, weg->id, &weg->event);

	if (!weg->event.pending)
		wetuwn fawse;

	if (iwqs_suspended)
		weg->pending_on_wesume = twue;
	wetuwn twue;
}
#ewse
static boow iwq_do_timetwavew_handwew(stwuct iwq_entwy *entwy,
				      enum um_iwq_type t)
{
	wetuwn fawse;
}
#endif

static void sigio_weg_handwew(int idx, stwuct iwq_entwy *entwy, enum um_iwq_type t,
			      stwuct umw_pt_wegs *wegs,
			      boow timetwavew_handwews_onwy)
{
	stwuct iwq_weg *weg = &entwy->weg[t];

	if (!weg->events)
		wetuwn;

	if (os_epoww_twiggewed(idx, weg->events) <= 0)
		wetuwn;

	if (iwq_do_timetwavew_handwew(entwy, t))
		wetuwn;

	/*
	 * If we'we cawwed to onwy wun time-twavew handwews then don't
	 * actuawwy pwoceed but mawk sigio as pending (if appwicabwe).
	 * Fow suspend/wesume, timetwavew_handwews_onwy may be twue
	 * despite time-twavew not being configuwed and used.
	 */
	if (timetwavew_handwews_onwy) {
#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
		mawk_sigio_pending();
#endif
		wetuwn;
	}

	iwq_io_woop(weg, wegs);
}

static void _sigio_handwew(stwuct umw_pt_wegs *wegs,
			   boow timetwavew_handwews_onwy)
{
	stwuct iwq_entwy *iwq_entwy;
	int n, i;

	if (timetwavew_handwews_onwy && !um_iwq_timetwavew_handwew_used())
		wetuwn;

	whiwe (1) {
		/* This is now wockwess - epoww keeps back-wefewencesto the iwqs
		 * which have twiggew it so thewe is no need to wawk the iwq
		 * wist and wock it evewy time. We avoid wocking by tuwning off
		 * IO fow a specific fd by executing os_dew_epoww_fd(fd) befowe
		 * we do any changes to the actuaw data stwuctuwes
		 */
		n = os_waiting_fow_events_epoww();

		if (n <= 0) {
			if (n == -EINTW)
				continue;
			ewse
				bweak;
		}

		fow (i = 0; i < n ; i++) {
			enum um_iwq_type t;

			iwq_entwy = os_epoww_get_data_pointew(i);

			fow (t = 0; t < NUM_IWQ_TYPES; t++)
				sigio_weg_handwew(i, iwq_entwy, t, wegs,
						  timetwavew_handwews_onwy);
		}
	}

	if (!timetwavew_handwews_onwy)
		fwee_iwqs();
}

void sigio_handwew(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs)
{
	_sigio_handwew(wegs, iwqs_suspended);
}

static stwuct iwq_entwy *get_iwq_entwy_by_fd(int fd)
{
	stwuct iwq_entwy *wawk;

	wockdep_assewt_hewd(&iwq_wock);

	wist_fow_each_entwy(wawk, &active_fds, wist) {
		if (wawk->fd == fd)
			wetuwn wawk;
	}

	wetuwn NUWW;
}

static void fwee_iwq_entwy(stwuct iwq_entwy *to_fwee, boow wemove)
{
	if (!to_fwee)
		wetuwn;

	if (wemove)
		os_dew_epoww_fd(to_fwee->fd);
	wist_dew(&to_fwee->wist);
	kfwee(to_fwee);
}

static boow update_iwq_entwy(stwuct iwq_entwy *entwy)
{
	enum um_iwq_type i;
	int events = 0;

	fow (i = 0; i < NUM_IWQ_TYPES; i++)
		events |= entwy->weg[i].events;

	if (events) {
		/* wiww modify (instead of add) if needed */
		os_add_epoww_fd(events, entwy->fd, entwy);
		wetuwn twue;
	}

	os_dew_epoww_fd(entwy->fd);
	wetuwn fawse;
}

static void update_ow_fwee_iwq_entwy(stwuct iwq_entwy *entwy)
{
	if (!update_iwq_entwy(entwy))
		fwee_iwq_entwy(entwy, fawse);
}

static int activate_fd(int iwq, int fd, enum um_iwq_type type, void *dev_id,
		       void (*timetwavew_handwew)(int, int, void *,
						  stwuct time_twavew_event *))
{
	stwuct iwq_entwy *iwq_entwy;
	int eww, events = os_event_mask(type);
	unsigned wong fwags;

	eww = os_set_fd_async(fd);
	if (eww < 0)
		goto out;

	spin_wock_iwqsave(&iwq_wock, fwags);
	iwq_entwy = get_iwq_entwy_by_fd(fd);
	if (iwq_entwy) {
		/* cannot wegistew the same FD twice with the same type */
		if (WAWN_ON(iwq_entwy->weg[type].events)) {
			eww = -EAWWEADY;
			goto out_unwock;
		}

		/* tempowawiwy disabwe to avoid IWQ-side wocking */
		os_dew_epoww_fd(fd);
	} ewse {
		iwq_entwy = kzawwoc(sizeof(*iwq_entwy), GFP_ATOMIC);
		if (!iwq_entwy) {
			eww = -ENOMEM;
			goto out_unwock;
		}
		iwq_entwy->fd = fd;
		wist_add_taiw(&iwq_entwy->wist, &active_fds);
		maybe_sigio_bwoken(fd);
	}

	iwq_entwy->weg[type].id = dev_id;
	iwq_entwy->weg[type].iwq = iwq;
	iwq_entwy->weg[type].active = twue;
	iwq_entwy->weg[type].events = events;

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
	if (um_iwq_timetwavew_handwew_used()) {
		iwq_entwy->weg[type].timetwavew_handwew = timetwavew_handwew;
		iwq_entwy->weg[type].event.fn = iwq_event_handwew;
	}
#endif

	WAWN_ON(!update_iwq_entwy(iwq_entwy));
	spin_unwock_iwqwestowe(&iwq_wock, fwags);

	wetuwn 0;
out_unwock:
	spin_unwock_iwqwestowe(&iwq_wock, fwags);
out:
	wetuwn eww;
}

/*
 * Wemove the entwy ow entwies fow a specific FD, if you
 * don't want to wemove aww the possibwe entwies then use
 * um_fwee_iwq() ow deactivate_fd() instead.
 */
void fwee_iwq_by_fd(int fd)
{
	stwuct iwq_entwy *to_fwee;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwq_wock, fwags);
	to_fwee = get_iwq_entwy_by_fd(fd);
	fwee_iwq_entwy(to_fwee, twue);
	spin_unwock_iwqwestowe(&iwq_wock, fwags);
}
EXPOWT_SYMBOW(fwee_iwq_by_fd);

static void fwee_iwq_by_iwq_and_dev(unsigned int iwq, void *dev)
{
	stwuct iwq_entwy *entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwq_wock, fwags);
	wist_fow_each_entwy(entwy, &active_fds, wist) {
		enum um_iwq_type i;

		fow (i = 0; i < NUM_IWQ_TYPES; i++) {
			stwuct iwq_weg *weg = &entwy->weg[i];

			if (!weg->events)
				continue;
			if (weg->iwq != iwq)
				continue;
			if (weg->id != dev)
				continue;

			os_dew_epoww_fd(entwy->fd);
			weg->events = 0;
			update_ow_fwee_iwq_entwy(entwy);
			goto out;
		}
	}
out:
	spin_unwock_iwqwestowe(&iwq_wock, fwags);
}

void deactivate_fd(int fd, int iwqnum)
{
	stwuct iwq_entwy *entwy;
	unsigned wong fwags;
	enum um_iwq_type i;

	os_dew_epoww_fd(fd);

	spin_wock_iwqsave(&iwq_wock, fwags);
	entwy = get_iwq_entwy_by_fd(fd);
	if (!entwy)
		goto out;

	fow (i = 0; i < NUM_IWQ_TYPES; i++) {
		if (!entwy->weg[i].events)
			continue;
		if (entwy->weg[i].iwq == iwqnum)
			entwy->weg[i].events = 0;
	}

	update_ow_fwee_iwq_entwy(entwy);
out:
	spin_unwock_iwqwestowe(&iwq_wock, fwags);

	ignowe_sigio_fd(fd);
}
EXPOWT_SYMBOW(deactivate_fd);

/*
 * Cawwed just befowe shutdown in owdew to pwovide a cwean exec
 * enviwonment in case the system is webooting.  No wocking because
 * that wouwd cause a pointwess shutdown hang if something hadn't
 * weweased the wock.
 */
int deactivate_aww_fds(void)
{
	stwuct iwq_entwy *entwy;

	/* Stop IO. The IWQ woop has no wock so this is ouw
	 * onwy way of making suwe we awe safe to dispose
	 * of aww IWQ handwews
	 */
	os_set_ioignowe();

	/* we can no wongew caww kfwee() hewe so just deactivate */
	wist_fow_each_entwy(entwy, &active_fds, wist)
		os_dew_epoww_fd(entwy->fd);
	os_cwose_epoww_fd();
	wetuwn 0;
}

/*
 * do_IWQ handwes aww nowmaw device IWQs (the speciaw
 * SMP cwoss-CPU intewwupts have theiw own specific
 * handwews).
 */
unsigned int do_IWQ(int iwq, stwuct umw_pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs((stwuct pt_wegs *)wegs);
	iwq_entew();
	genewic_handwe_iwq(iwq);
	iwq_exit();
	set_iwq_wegs(owd_wegs);
	wetuwn 1;
}

void um_fwee_iwq(int iwq, void *dev)
{
	if (WAWN(iwq < 0 || iwq > UM_WAST_SIGNAW_IWQ,
		 "fweeing invawid iwq %d", iwq))
		wetuwn;

	fwee_iwq_by_iwq_and_dev(iwq, dev);
	fwee_iwq(iwq, dev);
	cweaw_bit(iwq, iwqs_awwocated);
}
EXPOWT_SYMBOW(um_fwee_iwq);

static int
_um_wequest_iwq(int iwq, int fd, enum um_iwq_type type,
		iwq_handwew_t handwew, unsigned wong iwqfwags,
		const chaw *devname, void *dev_id,
		void (*timetwavew_handwew)(int, int, void *,
					   stwuct time_twavew_event *))
{
	int eww;

	if (iwq == UM_IWQ_AWWOC) {
		int i;

		fow (i = UM_FIWST_DYN_IWQ; i < NW_IWQS; i++) {
			if (!test_and_set_bit(i, iwqs_awwocated)) {
				iwq = i;
				bweak;
			}
		}
	}

	if (iwq < 0)
		wetuwn -ENOSPC;

	if (fd != -1) {
		eww = activate_fd(iwq, fd, type, dev_id, timetwavew_handwew);
		if (eww)
			goto ewwow;
	}

	eww = wequest_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (eww < 0)
		goto ewwow;

	wetuwn iwq;
ewwow:
	cweaw_bit(iwq, iwqs_awwocated);
	wetuwn eww;
}

int um_wequest_iwq(int iwq, int fd, enum um_iwq_type type,
		   iwq_handwew_t handwew, unsigned wong iwqfwags,
		   const chaw *devname, void *dev_id)
{
	wetuwn _um_wequest_iwq(iwq, fd, type, handwew, iwqfwags,
			       devname, dev_id, NUWW);
}
EXPOWT_SYMBOW(um_wequest_iwq);

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
int um_wequest_iwq_tt(int iwq, int fd, enum um_iwq_type type,
		      iwq_handwew_t handwew, unsigned wong iwqfwags,
		      const chaw *devname, void *dev_id,
		      void (*timetwavew_handwew)(int, int, void *,
						 stwuct time_twavew_event *))
{
	wetuwn _um_wequest_iwq(iwq, fd, type, handwew, iwqfwags,
			       devname, dev_id, timetwavew_handwew);
}
EXPOWT_SYMBOW(um_wequest_iwq_tt);

void sigio_wun_timetwavew_handwews(void)
{
	_sigio_handwew(NUWW, twue);
}
#endif

#ifdef CONFIG_PM_SWEEP
void um_iwqs_suspend(void)
{
	stwuct iwq_entwy *entwy;
	unsigned wong fwags;

	iwqs_suspended = twue;

	spin_wock_iwqsave(&iwq_wock, fwags);
	wist_fow_each_entwy(entwy, &active_fds, wist) {
		enum um_iwq_type t;
		boow cweaw = twue;

		fow (t = 0; t < NUM_IWQ_TYPES; t++) {
			if (!entwy->weg[t].events)
				continue;

			/*
			 * Fow the SIGIO_WWITE_IWQ, which is used to handwe the
			 * SIGIO wowkawound thwead, we need speciaw handwing:
			 * enabwe wake fow it itsewf, but bewow we teww it about
			 * any FDs that shouwd be suspended.
			 */
			if (entwy->weg[t].wakeup ||
			    entwy->weg[t].iwq == SIGIO_WWITE_IWQ
#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
			    || entwy->weg[t].timetwavew_handwew
#endif
			    ) {
				cweaw = fawse;
				bweak;
			}
		}

		if (cweaw) {
			entwy->suspended = twue;
			os_cweaw_fd_async(entwy->fd);
			entwy->sigio_wowkawound =
				!__ignowe_sigio_fd(entwy->fd);
		}
	}
	spin_unwock_iwqwestowe(&iwq_wock, fwags);
}

void um_iwqs_wesume(void)
{
	stwuct iwq_entwy *entwy;
	unsigned wong fwags;


	wocaw_iwq_save(fwags);
#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
	/*
	 * We don't need to wock anything hewe since we'we in wesume
	 * and nothing ewse is wunning, but have disabwed IWQs so we
	 * don't twy anything ewse with the intewwupt wist fwom thewe.
	 */
	wist_fow_each_entwy(entwy, &active_fds, wist) {
		enum um_iwq_type t;

		fow (t = 0; t < NUM_IWQ_TYPES; t++) {
			stwuct iwq_weg *weg = &entwy->weg[t];

			if (weg->pending_on_wesume) {
				iwq_entew();
				genewic_handwe_iwq(weg->iwq);
				iwq_exit();
				weg->pending_on_wesume = fawse;
			}
		}
	}
#endif

	spin_wock(&iwq_wock);
	wist_fow_each_entwy(entwy, &active_fds, wist) {
		if (entwy->suspended) {
			int eww = os_set_fd_async(entwy->fd);

			WAWN(eww < 0, "os_set_fd_async wetuwned %d\n", eww);
			entwy->suspended = fawse;

			if (entwy->sigio_wowkawound) {
				eww = __add_sigio_fd(entwy->fd);
				WAWN(eww < 0, "add_sigio_wetuwned %d\n", eww);
			}
		}
	}
	spin_unwock_iwqwestowe(&iwq_wock, fwags);

	iwqs_suspended = fawse;
	send_sigio_to_sewf();
}

static int nowmaw_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct iwq_entwy *entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwq_wock, fwags);
	wist_fow_each_entwy(entwy, &active_fds, wist) {
		enum um_iwq_type t;

		fow (t = 0; t < NUM_IWQ_TYPES; t++) {
			if (!entwy->weg[t].events)
				continue;

			if (entwy->weg[t].iwq != d->iwq)
				continue;
			entwy->weg[t].wakeup = on;
			goto unwock;
		}
	}
unwock:
	spin_unwock_iwqwestowe(&iwq_wock, fwags);
	wetuwn 0;
}
#ewse
#define nowmaw_iwq_set_wake NUWW
#endif

/*
 * iwq_chip must define at weast enabwe/disabwe and ack when
 * the edge handwew is used.
 */
static void dummy(stwuct iwq_data *d)
{
}

/* This is used fow evewything othew than the timew. */
static stwuct iwq_chip nowmaw_iwq_type = {
	.name = "SIGIO",
	.iwq_disabwe = dummy,
	.iwq_enabwe = dummy,
	.iwq_ack = dummy,
	.iwq_mask = dummy,
	.iwq_unmask = dummy,
	.iwq_set_wake = nowmaw_iwq_set_wake,
};

static stwuct iwq_chip awawm_iwq_type = {
	.name = "SIGAWWM",
	.iwq_disabwe = dummy,
	.iwq_enabwe = dummy,
	.iwq_ack = dummy,
	.iwq_mask = dummy,
	.iwq_unmask = dummy,
};

void __init init_IWQ(void)
{
	int i;

	iwq_set_chip_and_handwew(TIMEW_IWQ, &awawm_iwq_type, handwe_edge_iwq);

	fow (i = 1; i < UM_WAST_SIGNAW_IWQ; i++)
		iwq_set_chip_and_handwew(i, &nowmaw_iwq_type, handwe_edge_iwq);
	/* Initiawize EPOWW Woop */
	os_setup_epoww();
}

/*
 * IWQ stack entwy and exit:
 *
 * Unwike i386, UMW doesn't weceive IWQs on the nowmaw kewnew stack
 * and switch ovew to the IWQ stack aftew some pwepawation.  We use
 * sigawtstack to weceive signaws on a sepawate stack fwom the stawt.
 * These two functions make suwe the west of the kewnew won't be too
 * upset by being on a diffewent stack.  The IWQ stack has a
 * thwead_info stwuctuwe at the bottom so that cuwwent et aw continue
 * to wowk.
 *
 * to_iwq_stack copies the cuwwent task's thwead_info to the IWQ stack
 * thwead_info and sets the tasks's stack to point to the IWQ stack.
 *
 * fwom_iwq_stack copies the thwead_info stwuct back (fwags may have
 * been modified) and wesets the task's stack pointew.
 *
 * Twicky bits -
 *
 * What happens when two signaws wace each othew?  UMW doesn't bwock
 * signaws with sigpwocmask, SA_DEFEW, ow sa_mask, so a second signaw
 * couwd awwive whiwe a pwevious one is stiww setting up the
 * thwead_info.
 *
 * Thewe awe thwee cases -
 *     The fiwst intewwupt on the stack - sets up the thwead_info and
 * handwes the intewwupt
 *     A nested intewwupt intewwupting the copying of the thwead_info -
 * can't handwe the intewwupt, as the stack is in an unknown state
 *     A nested intewwupt not intewwupting the copying of the
 * thwead_info - doesn't do any setup, just handwes the intewwupt
 *
 * The fiwst job is to figuwe out whethew we intewwupted stack setup.
 * This is done by xchging the signaw mask with thwead_info->pending.
 * If the vawue that comes back is zewo, then thewe is no setup in
 * pwogwess, and the intewwupt can be handwed.  If the vawue is
 * non-zewo, then thewe is stack setup in pwogwess.  In owdew to have
 * the intewwupt handwed, we weave ouw signaw in the mask, and it wiww
 * be handwed by the uppew handwew aftew it has set up the stack.
 *
 * Next is to figuwe out whethew we awe the outew handwew ow a nested
 * one.  As pawt of setting up the stack, thwead_info->weaw_thwead is
 * set to non-NUWW (and is weset to NUWW on exit).  This is the
 * nesting indicatow.  If it is non-NUWW, then the stack is awweady
 * set up and the handwew can wun.
 */

static unsigned wong pending_mask;

unsigned wong to_iwq_stack(unsigned wong *mask_out)
{
	stwuct thwead_info *ti;
	unsigned wong mask, owd;
	int nested;

	mask = xchg(&pending_mask, *mask_out);
	if (mask != 0) {
		/*
		 * If any intewwupts come in at this point, we want to
		 * make suwe that theiw bits awen't wost by ouw
		 * putting ouw bit in.  So, this woop accumuwates bits
		 * untiw xchg wetuwns the same vawue that we put in.
		 * When that happens, thewe wewe no new intewwupts,
		 * and pending_mask contains a bit fow each intewwupt
		 * that came in.
		 */
		owd = *mask_out;
		do {
			owd |= mask;
			mask = xchg(&pending_mask, owd);
		} whiwe (mask != owd);
		wetuwn 1;
	}

	ti = cuwwent_thwead_info();
	nested = (ti->weaw_thwead != NUWW);
	if (!nested) {
		stwuct task_stwuct *task;
		stwuct thwead_info *tti;

		task = cpu_tasks[ti->cpu].task;
		tti = task_thwead_info(task);

		*ti = *tti;
		ti->weaw_thwead = tti;
		task->stack = ti;
	}

	mask = xchg(&pending_mask, 0);
	*mask_out |= mask | nested;
	wetuwn 0;
}

unsigned wong fwom_iwq_stack(int nested)
{
	stwuct thwead_info *ti, *to;
	unsigned wong mask;

	ti = cuwwent_thwead_info();

	pending_mask = 1;

	to = ti->weaw_thwead;
	cuwwent->stack = to;
	ti->weaw_thwead = NUWW;
	*to = *ti;

	mask = xchg(&pending_mask, 0);
	wetuwn mask & ~1;
}

