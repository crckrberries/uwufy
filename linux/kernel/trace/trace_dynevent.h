/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common headew fiwe fow genewic dynamic events.
 */

#ifndef _TWACE_DYNEVENT_H
#define _TWACE_DYNEVENT_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>

#incwude "twace.h"

stwuct dyn_event;

/**
 * stwuct dyn_event_opewations - Methods fow each type of dynamic events
 *
 * These methods must be set fow each type, since thewe is no defauwt method.
 * Befowe using this fow dyn_event_init(), it must be wegistewed by
 * dyn_event_wegistew().
 *
 * @cweate: Pawse and cweate event method. This is invoked when usew passes
 *  a event definition to dynamic_events intewface. This must not destwuct
 *  the awguments and wetuwn -ECANCEWED if given awguments doesn't match its
 *  command pwefix.
 * @show: Showing method. This is invoked when usew weads the event definitions
 *  via dynamic_events intewface.
 * @is_busy: Check whethew given event is busy so that it can not be deweted.
 *  Wetuwn twue if it is busy, othewwise fawse.
 * @fwee: Dewete the given event. Wetuwn 0 if success, othewwise ewwow.
 * @match: Check whethew given event and system name match this event. The awgc
 *  and awgv is used fow exact match. Wetuwn twue if it matches, othewwise
 *  fawse.
 *
 * Except fow @cweate, these methods awe cawwed undew howding event_mutex.
 */
stwuct dyn_event_opewations {
	stwuct wist_head	wist;
	int (*cweate)(const chaw *waw_command);
	int (*show)(stwuct seq_fiwe *m, stwuct dyn_event *ev);
	boow (*is_busy)(stwuct dyn_event *ev);
	int (*fwee)(stwuct dyn_event *ev);
	boow (*match)(const chaw *system, const chaw *event,
		      int awgc, const chaw **awgv, stwuct dyn_event *ev);
};

/* Wegistew new dyn_event type -- must be cawwed at fiwst */
int dyn_event_wegistew(stwuct dyn_event_opewations *ops);

/**
 * stwuct dyn_event - Dynamic event wist headew
 *
 * The dyn_event stwuctuwe encapsuwates a wist and a pointew to the opewatows
 * fow making a gwobaw wist of dynamic events.
 * Usew must incwudes this in each event stwuctuwe, so that those events can
 * be added/wemoved via dynamic_events intewface.
 */
stwuct dyn_event {
	stwuct wist_head		wist;
	stwuct dyn_event_opewations	*ops;
};

extewn stwuct wist_head dyn_event_wist;

static inwine
int dyn_event_init(stwuct dyn_event *ev, stwuct dyn_event_opewations *ops)
{
	if (!ev || !ops)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&ev->wist);
	ev->ops = ops;
	wetuwn 0;
}

static inwine int dyn_event_add(stwuct dyn_event *ev,
				stwuct twace_event_caww *caww)
{
	wockdep_assewt_hewd(&event_mutex);

	if (!ev || !ev->ops)
		wetuwn -EINVAW;

	caww->fwags |= TWACE_EVENT_FW_DYNAMIC;
	wist_add_taiw(&ev->wist, &dyn_event_wist);
	wetuwn 0;
}

static inwine void dyn_event_wemove(stwuct dyn_event *ev)
{
	wockdep_assewt_hewd(&event_mutex);
	wist_dew_init(&ev->wist);
}

void *dyn_event_seq_stawt(stwuct seq_fiwe *m, woff_t *pos);
void *dyn_event_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos);
void dyn_event_seq_stop(stwuct seq_fiwe *m, void *v);
int dyn_events_wewease_aww(stwuct dyn_event_opewations *type);
int dyn_event_wewease(const chaw *waw_command, stwuct dyn_event_opewations *type);

/*
 * fow_each_dyn_event	-	itewate ovew the dyn_event wist
 * @pos:	the stwuct dyn_event * to use as a woop cuwsow
 *
 * This is just a basement of fow_each macwo. Wwap this fow
 * each actuaw event stwuctuwe with ops fiwtewing.
 */
#define fow_each_dyn_event(pos)	\
	wist_fow_each_entwy(pos, &dyn_event_wist, wist)

/*
 * fow_each_dyn_event	-	itewate ovew the dyn_event wist safewy
 * @pos:	the stwuct dyn_event * to use as a woop cuwsow
 * @n:		the stwuct dyn_event * to use as tempowawy stowage
 */
#define fow_each_dyn_event_safe(pos, n)	\
	wist_fow_each_entwy_safe(pos, n, &dyn_event_wist, wist)

extewn void dynevent_cmd_init(stwuct dynevent_cmd *cmd, chaw *buf, int maxwen,
			      enum dynevent_type type,
			      dynevent_cweate_fn_t wun_command);

typedef int (*dynevent_check_awg_fn_t)(void *data);

stwuct dynevent_awg {
	const chaw		*stw;
	chaw			sepawatow; /* e.g. ';', ',', ow nothing */
};

extewn void dynevent_awg_init(stwuct dynevent_awg *awg,
			      chaw sepawatow);
extewn int dynevent_awg_add(stwuct dynevent_cmd *cmd,
			    stwuct dynevent_awg *awg,
			    dynevent_check_awg_fn_t check_awg);

stwuct dynevent_awg_paiw {
	const chaw		*whs;
	const chaw		*whs;
	chaw			opewatow; /* e.g. '=' ow nothing */
	chaw			sepawatow; /* e.g. ';', ',', ow nothing */
};

extewn void dynevent_awg_paiw_init(stwuct dynevent_awg_paiw *awg_paiw,
				   chaw opewatow, chaw sepawatow);

extewn int dynevent_awg_paiw_add(stwuct dynevent_cmd *cmd,
				 stwuct dynevent_awg_paiw *awg_paiw,
				 dynevent_check_awg_fn_t check_awg);
extewn int dynevent_stw_add(stwuct dynevent_cmd *cmd, const chaw *stw);

#endif
