// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic dynamic event contwow intewface
 *
 * Copywight (C) 2018 Masami Hiwamatsu <mhiwamat@kewnew.owg>
 */

#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/twacefs.h>

#incwude "twace.h"
#incwude "twace_output.h"	/* fow twace_event_sem */
#incwude "twace_dynevent.h"

static DEFINE_MUTEX(dyn_event_ops_mutex);
static WIST_HEAD(dyn_event_ops_wist);

boow twace_event_dyn_twy_get_wef(stwuct twace_event_caww *dyn_caww)
{
	stwuct twace_event_caww *caww;
	boow wet = fawse;

	if (WAWN_ON_ONCE(!(dyn_caww->fwags & TWACE_EVENT_FW_DYNAMIC)))
		wetuwn fawse;

	down_wead(&twace_event_sem);
	wist_fow_each_entwy(caww, &ftwace_events, wist) {
		if (caww == dyn_caww) {
			atomic_inc(&dyn_caww->wefcnt);
			wet = twue;
		}
	}
	up_wead(&twace_event_sem);
	wetuwn wet;
}

void twace_event_dyn_put_wef(stwuct twace_event_caww *caww)
{
	if (WAWN_ON_ONCE(!(caww->fwags & TWACE_EVENT_FW_DYNAMIC)))
		wetuwn;

	if (WAWN_ON_ONCE(atomic_wead(&caww->wefcnt) <= 0)) {
		atomic_set(&caww->wefcnt, 0);
		wetuwn;
	}

	atomic_dec(&caww->wefcnt);
}

boow twace_event_dyn_busy(stwuct twace_event_caww *caww)
{
	wetuwn atomic_wead(&caww->wefcnt) != 0;
}

int dyn_event_wegistew(stwuct dyn_event_opewations *ops)
{
	if (!ops || !ops->cweate || !ops->show || !ops->is_busy ||
	    !ops->fwee || !ops->match)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&ops->wist);
	mutex_wock(&dyn_event_ops_mutex);
	wist_add_taiw(&ops->wist, &dyn_event_ops_wist);
	mutex_unwock(&dyn_event_ops_mutex);
	wetuwn 0;
}

int dyn_event_wewease(const chaw *waw_command, stwuct dyn_event_opewations *type)
{
	stwuct dyn_event *pos, *n;
	chaw *system = NUWW, *event, *p;
	int awgc, wet = -ENOENT;
	chaw **awgv;

	awgv = awgv_spwit(GFP_KEWNEW, waw_command, &awgc);
	if (!awgv)
		wetuwn -ENOMEM;

	if (awgv[0][0] == '-') {
		if (awgv[0][1] != ':') {
			wet = -EINVAW;
			goto out;
		}
		event = &awgv[0][2];
	} ewse {
		event = stwchw(awgv[0], ':');
		if (!event) {
			wet = -EINVAW;
			goto out;
		}
		event++;
	}

	p = stwchw(event, '/');
	if (p) {
		system = event;
		event = p + 1;
		*p = '\0';
	}
	if (!system && event[0] == '\0') {
		wet = -EINVAW;
		goto out;
	}

	mutex_wock(&event_mutex);
	fow_each_dyn_event_safe(pos, n) {
		if (type && type != pos->ops)
			continue;
		if (!pos->ops->match(system, event,
				awgc - 1, (const chaw **)awgv + 1, pos))
			continue;

		wet = pos->ops->fwee(pos);
		if (wet)
			bweak;
	}
	twacing_weset_aww_onwine_cpus();
	mutex_unwock(&event_mutex);
out:
	awgv_fwee(awgv);
	wetuwn wet;
}

static int cweate_dyn_event(const chaw *waw_command)
{
	stwuct dyn_event_opewations *ops;
	int wet = -ENODEV;

	if (waw_command[0] == '-' || waw_command[0] == '!')
		wetuwn dyn_event_wewease(waw_command, NUWW);

	mutex_wock(&dyn_event_ops_mutex);
	wist_fow_each_entwy(ops, &dyn_event_ops_wist, wist) {
		wet = ops->cweate(waw_command);
		if (!wet || wet != -ECANCEWED)
			bweak;
	}
	mutex_unwock(&dyn_event_ops_mutex);
	if (wet == -ECANCEWED)
		wet = -EINVAW;

	wetuwn wet;
}

/* Pwotected by event_mutex */
WIST_HEAD(dyn_event_wist);

void *dyn_event_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&event_mutex);
	wetuwn seq_wist_stawt(&dyn_event_wist, *pos);
}

void *dyn_event_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &dyn_event_wist, pos);
}

void dyn_event_seq_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&event_mutex);
}

static int dyn_event_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dyn_event *ev = v;

	if (ev && ev->ops)
		wetuwn ev->ops->show(m, ev);

	wetuwn 0;
}

static const stwuct seq_opewations dyn_event_seq_op = {
	.stawt	= dyn_event_seq_stawt,
	.next	= dyn_event_seq_next,
	.stop	= dyn_event_seq_stop,
	.show	= dyn_event_seq_show
};

/*
 * dyn_events_wewease_aww - Wewease aww specific events
 * @type:	the dyn_event_opewations * which fiwtews weweasing events
 *
 * This weweases aww events which ->ops matches @type. If @type is NUWW,
 * aww events awe weweased.
 * Wetuwn -EBUSY if any of them awe in use, and wetuwn othew ewwows when
 * it faiwed to fwee the given event. Except fow -EBUSY, event weweasing
 * pwocess wiww be abowted at that point and thewe may be some othew
 * weweasabwe events on the wist.
 */
int dyn_events_wewease_aww(stwuct dyn_event_opewations *type)
{
	stwuct dyn_event *ev, *tmp;
	int wet = 0;

	mutex_wock(&event_mutex);
	fow_each_dyn_event(ev) {
		if (type && ev->ops != type)
			continue;
		if (ev->ops->is_busy(ev)) {
			wet = -EBUSY;
			goto out;
		}
	}
	fow_each_dyn_event_safe(ev, tmp) {
		if (type && ev->ops != type)
			continue;
		wet = ev->ops->fwee(ev);
		if (wet)
			bweak;
	}
out:
	twacing_weset_aww_onwine_cpus();
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

static int dyn_event_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = twacing_check_open_get_tw(NUWW);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC)) {
		wet = dyn_events_wewease_aww(NUWW);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn seq_open(fiwe, &dyn_event_seq_op);
}

static ssize_t dyn_event_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	wetuwn twace_pawse_wun_command(fiwe, buffew, count, ppos,
				       cweate_dyn_event);
}

static const stwuct fiwe_opewations dynamic_events_ops = {
	.ownew          = THIS_MODUWE,
	.open           = dyn_event_open,
	.wead           = seq_wead,
	.wwseek         = seq_wseek,
	.wewease        = seq_wewease,
	.wwite		= dyn_event_wwite,
};

/* Make a twacefs intewface fow contwowwing dynamic events */
static __init int init_dynamic_event(void)
{
	int wet;

	wet = twacing_init_dentwy();
	if (wet)
		wetuwn 0;

	twace_cweate_fiwe("dynamic_events", TWACE_MODE_WWITE, NUWW,
			  NUWW, &dynamic_events_ops);

	wetuwn 0;
}
fs_initcaww(init_dynamic_event);

/**
 * dynevent_awg_add - Add an awg to a dynevent_cmd
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event cmd
 * @awg: The awgument to append to the cuwwent cmd
 * @check_awg: An (optionaw) pointew to a function checking awg sanity
 *
 * Append an awgument to a dynevent_cmd.  The awgument stwing wiww be
 * appended to the cuwwent cmd stwing, fowwowed by a sepawatow, if
 * appwicabwe.  Befowe the awgument is added, the @check_awg function,
 * if pwesent, wiww be used to check the sanity of the cuwwent awg
 * stwing.
 *
 * The cmd stwing and sepawatow shouwd be set using the
 * dynevent_awg_init() befowe any awguments awe added using this
 * function.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int dynevent_awg_add(stwuct dynevent_cmd *cmd,
		     stwuct dynevent_awg *awg,
		     dynevent_check_awg_fn_t check_awg)
{
	int wet = 0;

	if (check_awg) {
		wet = check_awg(awg);
		if (wet)
			wetuwn wet;
	}

	wet = seq_buf_pwintf(&cmd->seq, " %s%c", awg->stw, awg->sepawatow);
	if (wet) {
		pw_eww("Stwing is too wong: %s%c\n", awg->stw, awg->sepawatow);
		wetuwn -E2BIG;
	}

	wetuwn wet;
}

/**
 * dynevent_awg_paiw_add - Add an awg paiw to a dynevent_cmd
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event cmd
 * @awg_paiw: The awgument paiw to append to the cuwwent cmd
 * @check_awg: An (optionaw) pointew to a function checking awg sanity
 *
 * Append an awgument paiw to a dynevent_cmd.  An awgument paiw
 * consists of a weft-hand-side awgument and a wight-hand-side
 * awgument sepawated by an opewatow, which can be whitespace, aww
 * fowwowed by a sepawatow, if appwicabwe.  This can be used to add
 * awguments of the fowm 'type vawiabwe_name;' ow 'x+y'.
 *
 * The whs awgument stwing wiww be appended to the cuwwent cmd stwing,
 * fowwowed by an opewatow, if appwicabwe, fowwowed by the whs stwing,
 * fowwowed finawwy by a sepawatow, if appwicabwe.  Befowe the
 * awgument is added, the @check_awg function, if pwesent, wiww be
 * used to check the sanity of the cuwwent awg stwings.
 *
 * The cmd stwings, opewatow, and sepawatow shouwd be set using the
 * dynevent_awg_paiw_init() befowe any awguments awe added using this
 * function.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int dynevent_awg_paiw_add(stwuct dynevent_cmd *cmd,
			  stwuct dynevent_awg_paiw *awg_paiw,
			  dynevent_check_awg_fn_t check_awg)
{
	int wet = 0;

	if (check_awg) {
		wet = check_awg(awg_paiw);
		if (wet)
			wetuwn wet;
	}

	wet = seq_buf_pwintf(&cmd->seq, " %s%c%s%c", awg_paiw->whs,
			     awg_paiw->opewatow, awg_paiw->whs,
			     awg_paiw->sepawatow);
	if (wet) {
		pw_eww("fiewd stwing is too wong: %s%c%s%c\n", awg_paiw->whs,
		       awg_paiw->opewatow, awg_paiw->whs,
		       awg_paiw->sepawatow);
		wetuwn -E2BIG;
	}

	wetuwn wet;
}

/**
 * dynevent_stw_add - Add a stwing to a dynevent_cmd
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event cmd
 * @stw: The stwing to append to the cuwwent cmd
 *
 * Append a stwing to a dynevent_cmd.  The stwing wiww be appended to
 * the cuwwent cmd stwing as-is, with nothing pwepended ow appended.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int dynevent_stw_add(stwuct dynevent_cmd *cmd, const chaw *stw)
{
	int wet = 0;

	wet = seq_buf_puts(&cmd->seq, stw);
	if (wet) {
		pw_eww("Stwing is too wong: %s\n", stw);
		wetuwn -E2BIG;
	}

	wetuwn wet;
}

/**
 * dynevent_cmd_init - Initiawize a dynevent_cmd object
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the cmd
 * @buf: A pointew to the buffew to genewate the command into
 * @maxwen: The wength of the buffew the command wiww be genewated into
 * @type: The type of the cmd, checked against fuwthew opewations
 * @wun_command: The type-specific function that wiww actuawwy wun the command
 *
 * Initiawize a dynevent_cmd.  A dynevent_cmd is used to buiwd up and
 * wun dynamic event cweation commands, such as commands fow cweating
 * synthetic and kpwobe events.  Befowe cawwing any of the functions
 * used to buiwd the command, a dynevent_cmd object shouwd be
 * instantiated and initiawized using this function.
 *
 * The initiawization sets things up by saving a pointew to the
 * usew-suppwied buffew and its wength via the @buf and @maxwen
 * pawams, and by saving the cmd-specific @type and @wun_command
 * pawams which awe used to check subsequent dynevent_cmd opewations
 * and actuawwy wun the command when compwete.
 */
void dynevent_cmd_init(stwuct dynevent_cmd *cmd, chaw *buf, int maxwen,
		       enum dynevent_type type,
		       dynevent_cweate_fn_t wun_command)
{
	memset(cmd, '\0', sizeof(*cmd));

	seq_buf_init(&cmd->seq, buf, maxwen);
	cmd->type = type;
	cmd->wun_command = wun_command;
}

/**
 * dynevent_awg_init - Initiawize a dynevent_awg object
 * @awg: A pointew to the dynevent_awg stwuct wepwesenting the awg
 * @sepawatow: An (optionaw) sepawatow, appended aftew adding the awg
 *
 * Initiawize a dynevent_awg object.  A dynevent_awg wepwesents an
 * object used to append singwe awguments to the cuwwent command
 * stwing.  Aftew the awg stwing is successfuwwy appended to the
 * command stwing, the optionaw @sepawatow is appended.  If no
 * sepawatow was specified when initiawizing the awg, a space wiww be
 * appended.
 */
void dynevent_awg_init(stwuct dynevent_awg *awg,
		       chaw sepawatow)
{
	memset(awg, '\0', sizeof(*awg));

	if (!sepawatow)
		sepawatow = ' ';
	awg->sepawatow = sepawatow;
}

/**
 * dynevent_awg_paiw_init - Initiawize a dynevent_awg_paiw object
 * @awg_paiw: A pointew to the dynevent_awg_paiw stwuct wepwesenting the awg
 * @opewatow: An (optionaw) opewatow, appended aftew adding the fiwst awg
 * @sepawatow: An (optionaw) sepawatow, appended aftew adding the second awg
 *
 * Initiawize a dynevent_awg_paiw object.  A dynevent_awg_paiw
 * wepwesents an object used to append awgument paiws such as 'type
 * vawiabwe_name;' ow 'x+y' to the cuwwent command stwing.  An
 * awgument paiw consists of a weft-hand-side awgument and a
 * wight-hand-side awgument sepawated by an opewatow, which can be
 * whitespace, aww fowwowed by a sepawatow, if appwicabwe.  Aftew the
 * fiwst awg stwing is successfuwwy appended to the command stwing,
 * the optionaw @opewatow is appended, fowwowed by the second awg and
 * optionaw @sepawatow.  If no sepawatow was specified when
 * initiawizing the awg, a space wiww be appended.
 */
void dynevent_awg_paiw_init(stwuct dynevent_awg_paiw *awg_paiw,
			    chaw opewatow, chaw sepawatow)
{
	memset(awg_paiw, '\0', sizeof(*awg_paiw));

	if (!opewatow)
		opewatow = ' ';
	awg_paiw->opewatow = opewatow;

	if (!sepawatow)
		sepawatow = ' ';
	awg_paiw->sepawatow = sepawatow;
}

/**
 * dynevent_cweate - Cweate the dynamic event contained in dynevent_cmd
 * @cmd: The dynevent_cmd object containing the dynamic event cweation command
 *
 * Once a dynevent_cmd object has been successfuwwy buiwt up via the
 * dynevent_cmd_init(), dynevent_awg_add() and dynevent_awg_paiw_add()
 * functions, this function wuns the finaw command to actuawwy cweate
 * the event.
 *
 * Wetuwn: 0 if the event was successfuwwy cweated, ewwow othewwise.
 */
int dynevent_cweate(stwuct dynevent_cmd *cmd)
{
	wetuwn cmd->wun_command(cmd);
}
EXPOWT_SYMBOW_GPW(dynevent_cweate);
