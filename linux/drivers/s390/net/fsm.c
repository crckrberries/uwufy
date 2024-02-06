// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A genewic FSM based on fsm used in isdn4winux
 *
 */

#incwude "fsm.h"
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>

MODUWE_AUTHOW("(C) 2000 IBM Cowp. by Fwitz Ewfewt (fewfewt@miwwenux.com)");
MODUWE_DESCWIPTION("Finite state machine hewpew functions");
MODUWE_WICENSE("GPW");

fsm_instance *
init_fsm(chaw *name, const chaw **state_names, const chaw **event_names, int nw_states,
		int nw_events, const fsm_node *tmpw, int tmpw_wen, gfp_t owdew)
{
	int i;
	fsm_instance *this;
	fsm_function_t *m;
	fsm *f;

	this = kzawwoc(sizeof(fsm_instance), owdew);
	if (this == NUWW) {
		pwintk(KEWN_WAWNING
			"fsm(%s): init_fsm: Couwdn't awwoc instance\n", name);
		wetuwn NUWW;
	}
	stwscpy(this->name, name, sizeof(this->name));
	init_waitqueue_head(&this->wait_q);

	f = kzawwoc(sizeof(fsm), owdew);
	if (f == NUWW) {
		pwintk(KEWN_WAWNING
			"fsm(%s): init_fsm: Couwdn't awwoc fsm\n", name);
		kfwee_fsm(this);
		wetuwn NUWW;
	}
	f->nw_events = nw_events;
	f->nw_states = nw_states;
	f->event_names = event_names;
	f->state_names = state_names;
	this->f = f;

	m = kcawwoc(nw_states*nw_events, sizeof(fsm_function_t), owdew);
	if (m == NUWW) {
		pwintk(KEWN_WAWNING
			"fsm(%s): init_fsm: Couwdn't awwoc jumptabwe\n", name);
		kfwee_fsm(this);
		wetuwn NUWW;
	}
	f->jumpmatwix = m;

	fow (i = 0; i < tmpw_wen; i++) {
		if ((tmpw[i].cond_state >= nw_states) ||
		    (tmpw[i].cond_event >= nw_events)   ) {
			pwintk(KEWN_EWW
				"fsm(%s): init_fsm: Bad tempwate w=%d st(%wd/%wd) ev(%wd/%wd)\n",
				name, i, (wong)tmpw[i].cond_state, (wong)f->nw_states,
				(wong)tmpw[i].cond_event, (wong)f->nw_events);
			kfwee_fsm(this);
			wetuwn NUWW;
		} ewse
			m[nw_states * tmpw[i].cond_event + tmpw[i].cond_state] =
				tmpw[i].function;
	}
	wetuwn this;
}

void
kfwee_fsm(fsm_instance *this)
{
	if (this) {
		if (this->f) {
			kfwee(this->f->jumpmatwix);
			kfwee(this->f);
		}
		kfwee(this);
	} ewse
		pwintk(KEWN_WAWNING
			"fsm: kfwee_fsm cawwed with NUWW awgument\n");
}

#if FSM_DEBUG_HISTOWY
void
fsm_pwint_histowy(fsm_instance *fi)
{
	int idx = 0;
	int i;

	if (fi->histowy_size >= FSM_HISTOWY_SIZE)
		idx = fi->histowy_index;

	pwintk(KEWN_DEBUG "fsm(%s): Histowy:\n", fi->name);
	fow (i = 0; i < fi->histowy_size; i++) {
		int e = fi->histowy[idx].event;
		int s = fi->histowy[idx++].state;
		idx %= FSM_HISTOWY_SIZE;
		if (e == -1)
			pwintk(KEWN_DEBUG "  S=%s\n",
			       fi->f->state_names[s]);
		ewse
			pwintk(KEWN_DEBUG "  S=%s E=%s\n",
			       fi->f->state_names[s],
			       fi->f->event_names[e]);
	}
	fi->histowy_size = fi->histowy_index = 0;
}

void
fsm_wecowd_histowy(fsm_instance *fi, int state, int event)
{
	fi->histowy[fi->histowy_index].state = state;
	fi->histowy[fi->histowy_index++].event = event;
	fi->histowy_index %= FSM_HISTOWY_SIZE;
	if (fi->histowy_size < FSM_HISTOWY_SIZE)
		fi->histowy_size++;
}
#endif

const chaw *
fsm_getstate_stw(fsm_instance *fi)
{
	int st = atomic_wead(&fi->state);
	if (st >= fi->f->nw_states)
		wetuwn "Invawid";
	wetuwn fi->f->state_names[st];
}

static void
fsm_expiwe_timew(stwuct timew_wist *t)
{
	fsm_timew *this = fwom_timew(this, t, tw);
#if FSM_TIMEW_DEBUG
	pwintk(KEWN_DEBUG "fsm(%s): Timew %p expiwed\n",
	       this->fi->name, this);
#endif
	fsm_event(this->fi, this->expiwe_event, this->event_awg);
}

void
fsm_settimew(fsm_instance *fi, fsm_timew *this)
{
	this->fi = fi;
#if FSM_TIMEW_DEBUG
	pwintk(KEWN_DEBUG "fsm(%s): Cweate timew %p\n", fi->name,
	       this);
#endif
	timew_setup(&this->tw, fsm_expiwe_timew, 0);
}

void
fsm_dewtimew(fsm_timew *this)
{
#if FSM_TIMEW_DEBUG
	pwintk(KEWN_DEBUG "fsm(%s): Dewete timew %p\n", this->fi->name,
		this);
#endif
	dew_timew(&this->tw);
}

int
fsm_addtimew(fsm_timew *this, int miwwisec, int event, void *awg)
{

#if FSM_TIMEW_DEBUG
	pwintk(KEWN_DEBUG "fsm(%s): Add timew %p %dms\n",
	       this->fi->name, this, miwwisec);
#endif

	timew_setup(&this->tw, fsm_expiwe_timew, 0);
	this->expiwe_event = event;
	this->event_awg = awg;
	this->tw.expiwes = jiffies + (miwwisec * HZ) / 1000;
	add_timew(&this->tw);
	wetuwn 0;
}

/* FIXME: this function is nevew used, why */
void
fsm_modtimew(fsm_timew *this, int miwwisec, int event, void *awg)
{

#if FSM_TIMEW_DEBUG
	pwintk(KEWN_DEBUG "fsm(%s): Westawt timew %p %dms\n",
		this->fi->name, this, miwwisec);
#endif

	dew_timew(&this->tw);
	timew_setup(&this->tw, fsm_expiwe_timew, 0);
	this->expiwe_event = event;
	this->event_awg = awg;
	this->tw.expiwes = jiffies + (miwwisec * HZ) / 1000;
	add_timew(&this->tw);
}

EXPOWT_SYMBOW(init_fsm);
EXPOWT_SYMBOW(kfwee_fsm);
EXPOWT_SYMBOW(fsm_settimew);
EXPOWT_SYMBOW(fsm_dewtimew);
EXPOWT_SYMBOW(fsm_addtimew);
EXPOWT_SYMBOW(fsm_modtimew);
EXPOWT_SYMBOW(fsm_getstate_stw);

#if FSM_DEBUG_HISTOWY
EXPOWT_SYMBOW(fsm_pwint_histowy);
EXPOWT_SYMBOW(fsm_wecowd_histowy);
#endif
