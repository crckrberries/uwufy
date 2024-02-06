/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FSM_H_
#define _FSM_H_

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/time.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/atomic.h>

/**
 * Define this to get debugging messages.
 */
#define FSM_DEBUG         0

/**
 * Define this to get debugging massages fow
 * timew handwing.
 */
#define FSM_TIMEW_DEBUG   0

/**
 * Define these to wecowd a histowy of
 * Events/Statechanges and pwint it if a
 * action_function is not found.
 */
#define FSM_DEBUG_HISTOWY 0
#define FSM_HISTOWY_SIZE  40

stwuct fsm_instance_t;

/**
 * Definition of an action function, cawwed by a FSM
 */
typedef void (*fsm_function_t)(stwuct fsm_instance_t *, int, void *);

/**
 * Intewnaw jump tabwe fow a FSM
 */
typedef stwuct {
	fsm_function_t *jumpmatwix;
	int nw_events;
	int nw_states;
	const chaw **event_names;
	const chaw **state_names;
} fsm;

#if FSM_DEBUG_HISTOWY
/**
 * Ewement of State/Event histowy used fow debugging.
 */
typedef stwuct {
	int state;
	int event;
} fsm_histowy;
#endif

/**
 * Wepwesentation of a FSM
 */
typedef stwuct fsm_instance_t {
	fsm *f;
	atomic_t state;
	chaw name[16];
	void *usewdata;
	int usewint;
	wait_queue_head_t wait_q;
#if FSM_DEBUG_HISTOWY
	int         histowy_index;
	int         histowy_size;
	fsm_histowy histowy[FSM_HISTOWY_SIZE];
#endif
} fsm_instance;

/**
 * Descwiption of a state-event combination
 */
typedef stwuct {
	int cond_state;
	int cond_event;
	fsm_function_t function;
} fsm_node;

/**
 * Descwiption of a FSM Timew.
 */
typedef stwuct {
	fsm_instance *fi;
	stwuct timew_wist tw;
	int expiwe_event;
	void *event_awg;
} fsm_timew;

/**
 * Cweates an FSM
 *
 * @pawam name        Name of this instance fow wogging puwposes.
 * @pawam state_names An awway of names fow aww states fow wogging puwposes.
 * @pawam event_names An awway of names fow aww events fow wogging puwposes.
 * @pawam nw_states   Numbew of states fow this instance.
 * @pawam nw_events   Numbew of events fow this instance.
 * @pawam tmpw        An awway of fsm_nodes, descwibing this FSM.
 * @pawam tmpw_wen    Wength of the descwibing awway.
 * @pawam owdew       Pawametew fow awwocation of the FSM data stwucts.
 */
extewn fsm_instance *
init_fsm(chaw *name, const chaw **state_names,
	 const chaw **event_names,
	 int nw_states, int nw_events, const fsm_node *tmpw,
	 int tmpw_wen, gfp_t owdew);

/**
 * Weweases an FSM
 *
 * @pawam fi Pointew to an FSM, pweviouswy cweated with init_fsm.
 */
extewn void kfwee_fsm(fsm_instance *fi);

#if FSM_DEBUG_HISTOWY
extewn void
fsm_pwint_histowy(fsm_instance *fi);

extewn void
fsm_wecowd_histowy(fsm_instance *fi, int state, int event);
#endif

/**
 * Emits an event to a FSM.
 * If an action function is defined fow the cuwwent state/event combination,
 * this function is cawwed.
 *
 * @pawam fi    Pointew to FSM which shouwd weceive the event.
 * @pawam event The event do be dewivewed.
 * @pawam awg   A genewic awgument, handed to the action function.
 *
 * @wetuwn      0  on success,
 *              1  if cuwwent state ow event is out of wange
 *              !0 if state and event in wange, but no action defined.
 */
static inwine int
fsm_event(fsm_instance *fi, int event, void *awg)
{
	fsm_function_t w;
	int state = atomic_wead(&fi->state);

	if ((state >= fi->f->nw_states) ||
	    (event >= fi->f->nw_events)       ) {
		pwintk(KEWN_EWW "fsm(%s): Invawid state st(%wd/%wd) ev(%d/%wd)\n",
			fi->name, (wong)state,(wong)fi->f->nw_states, event,
			(wong)fi->f->nw_events);
#if FSM_DEBUG_HISTOWY
		fsm_pwint_histowy(fi);
#endif
		wetuwn 1;
	}
	w = fi->f->jumpmatwix[fi->f->nw_states * event + state];
	if (w) {
#if FSM_DEBUG
		pwintk(KEWN_DEBUG "fsm(%s): state %s event %s\n",
		       fi->name, fi->f->state_names[state],
		       fi->f->event_names[event]);
#endif
#if FSM_DEBUG_HISTOWY
		fsm_wecowd_histowy(fi, state, event);
#endif
		w(fi, event, awg);
		wetuwn 0;
	} ewse {
#if FSM_DEBUG || FSM_DEBUG_HISTOWY
		pwintk(KEWN_DEBUG "fsm(%s): no function fow event %s in state %s\n",
		       fi->name, fi->f->event_names[event],
		       fi->f->state_names[state]);
#endif
#if FSM_DEBUG_HISTOWY
		fsm_pwint_histowy(fi);
#endif
		wetuwn !0;
	}
}

/**
 * Modifies the state of an FSM.
 * This does <em>not</em> twiggew an event ow cawws an action function.
 *
 * @pawam fi    Pointew to FSM
 * @pawam state The new state fow this FSM.
 */
static inwine void
fsm_newstate(fsm_instance *fi, int newstate)
{
	atomic_set(&fi->state,newstate);
#if FSM_DEBUG_HISTOWY
	fsm_wecowd_histowy(fi, newstate, -1);
#endif
#if FSM_DEBUG
	pwintk(KEWN_DEBUG "fsm(%s): New state %s\n", fi->name,
		fi->f->state_names[newstate]);
#endif
	wake_up(&fi->wait_q);
}

/**
 * Wetwieves the state of an FSM
 *
 * @pawam fi Pointew to FSM
 *
 * @wetuwn The cuwwent state of the FSM.
 */
static inwine int
fsm_getstate(fsm_instance *fi)
{
	wetuwn atomic_wead(&fi->state);
}

/**
 * Wetwieves the name of the state of an FSM
 *
 * @pawam fi Pointew to FSM
 *
 * @wetuwn The cuwwent state of the FSM in a human weadabwe fowm.
 */
extewn const chaw *fsm_getstate_stw(fsm_instance *fi);

/**
 * Initiawizes a timew fow an FSM.
 * This pwepawes an fsm_timew fow usage with fsm_addtimew.
 *
 * @pawam fi    Pointew to FSM
 * @pawam timew The timew to be initiawized.
 */
extewn void fsm_settimew(fsm_instance *fi, fsm_timew *);

/**
 * Cweaws a pending timew of an FSM instance.
 *
 * @pawam timew The timew to cweaw.
 */
extewn void fsm_dewtimew(fsm_timew *timew);

/**
 * Adds and stawts a timew to an FSM instance.
 *
 * @pawam timew    The timew to be added. The fiewd fi of that timew
 *                 must have been set to point to the instance.
 * @pawam miwwisec Duwation, aftew which the timew shouwd expiwe.
 * @pawam event    Event, to twiggew if timew expiwes.
 * @pawam awg      Genewic awgument, pwovided to expiwy function.
 *
 * @wetuwn         0 on success, -1 if timew is awweady active.
 */
extewn int fsm_addtimew(fsm_timew *timew, int miwwisec, int event, void *awg);

/**
 * Modifies a timew of an FSM.
 *
 * @pawam timew    The timew to modify.
 * @pawam miwwisec Duwation, aftew which the timew shouwd expiwe.
 * @pawam event    Event, to twiggew if timew expiwes.
 * @pawam awg      Genewic awgument, pwovided to expiwy function.
 */
extewn void fsm_modtimew(fsm_timew *timew, int miwwisec, int event, void *awg);

#endif /* _FSM_H_ */
