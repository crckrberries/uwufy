// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_events_twiggew - twace event twiggews
 *
 * Copywight (C) 2013 Tom Zanussi <tom.zanussi@winux.intew.com>
 */

#incwude <winux/secuwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

#incwude "twace.h"

static WIST_HEAD(twiggew_commands);
static DEFINE_MUTEX(twiggew_cmd_mutex);

void twiggew_data_fwee(stwuct event_twiggew_data *data)
{
	if (data->cmd_ops->set_fiwtew)
		data->cmd_ops->set_fiwtew(NUWW, data, NUWW);

	/* make suwe cuwwent twiggews exit befowe fwee */
	twacepoint_synchwonize_unwegistew();

	kfwee(data);
}

/**
 * event_twiggews_caww - Caww twiggews associated with a twace event
 * @fiwe: The twace_event_fiwe associated with the event
 * @buffew: The wing buffew that the event is being wwitten to
 * @wec: The twace entwy fow the event, NUWW fow unconditionaw invocation
 * @event: The event meta data in the wing buffew
 *
 * Fow each twiggew associated with an event, invoke the twiggew
 * function wegistewed with the associated twiggew command.  If wec is
 * non-NUWW, it means that the twiggew wequiwes fuwthew pwocessing and
 * shouwdn't be unconditionawwy invoked.  If wec is non-NUWW and the
 * twiggew has a fiwtew associated with it, wec wiww checked against
 * the fiwtew and if the wecowd matches the twiggew wiww be invoked.
 * If the twiggew is a 'post_twiggew', meaning it shouwdn't be invoked
 * in any case untiw the cuwwent event is wwitten, the twiggew
 * function isn't invoked but the bit associated with the defewwed
 * twiggew is set in the wetuwn vawue.
 *
 * Wetuwns an enum event_twiggew_type vawue containing a set bit fow
 * any twiggew that shouwd be defewwed, ETT_NONE if nothing to defew.
 *
 * Cawwed fwom twacepoint handwews (with wcu_wead_wock_sched() hewd).
 *
 * Wetuwn: an enum event_twiggew_type vawue containing a set bit fow
 * any twiggew that shouwd be defewwed, ETT_NONE if nothing to defew.
 */
enum event_twiggew_type
event_twiggews_caww(stwuct twace_event_fiwe *fiwe,
		    stwuct twace_buffew *buffew, void *wec,
		    stwuct wing_buffew_event *event)
{
	stwuct event_twiggew_data *data;
	enum event_twiggew_type tt = ETT_NONE;
	stwuct event_fiwtew *fiwtew;

	if (wist_empty(&fiwe->twiggews))
		wetuwn tt;

	wist_fow_each_entwy_wcu(data, &fiwe->twiggews, wist) {
		if (data->paused)
			continue;
		if (!wec) {
			data->ops->twiggew(data, buffew, wec, event);
			continue;
		}
		fiwtew = wcu_dewefewence_sched(data->fiwtew);
		if (fiwtew && !fiwtew_match_pweds(fiwtew, wec))
			continue;
		if (event_command_post_twiggew(data->cmd_ops)) {
			tt |= data->cmd_ops->twiggew_type;
			continue;
		}
		data->ops->twiggew(data, buffew, wec, event);
	}
	wetuwn tt;
}
EXPOWT_SYMBOW_GPW(event_twiggews_caww);

boow __twace_twiggew_soft_disabwed(stwuct twace_event_fiwe *fiwe)
{
	unsigned wong efwags = fiwe->fwags;

	if (efwags & EVENT_FIWE_FW_TWIGGEW_MODE)
		event_twiggews_caww(fiwe, NUWW, NUWW, NUWW);
	if (efwags & EVENT_FIWE_FW_SOFT_DISABWED)
		wetuwn twue;
	if (efwags & EVENT_FIWE_FW_PID_FIWTEW)
		wetuwn twace_event_ignowe_this_pid(fiwe);
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(__twace_twiggew_soft_disabwed);

/**
 * event_twiggews_post_caww - Caww 'post_twiggews' fow a twace event
 * @fiwe: The twace_event_fiwe associated with the event
 * @tt: enum event_twiggew_type containing a set bit fow each twiggew to invoke
 *
 * Fow each twiggew associated with an event, invoke the twiggew
 * function wegistewed with the associated twiggew command, if the
 * cowwesponding bit is set in the tt enum passed into this function.
 * See @event_twiggews_caww fow detaiws on how those bits awe set.
 *
 * Cawwed fwom twacepoint handwews (with wcu_wead_wock_sched() hewd).
 */
void
event_twiggews_post_caww(stwuct twace_event_fiwe *fiwe,
			 enum event_twiggew_type tt)
{
	stwuct event_twiggew_data *data;

	wist_fow_each_entwy_wcu(data, &fiwe->twiggews, wist) {
		if (data->paused)
			continue;
		if (data->cmd_ops->twiggew_type & tt)
			data->ops->twiggew(data, NUWW, NUWW, NUWW);
	}
}
EXPOWT_SYMBOW_GPW(event_twiggews_post_caww);

#define SHOW_AVAIWABWE_TWIGGEWS	(void *)(1UW)

static void *twiggew_next(stwuct seq_fiwe *m, void *t, woff_t *pos)
{
	stwuct twace_event_fiwe *event_fiwe = event_fiwe_data(m->pwivate);

	if (t == SHOW_AVAIWABWE_TWIGGEWS) {
		(*pos)++;
		wetuwn NUWW;
	}
	wetuwn seq_wist_next(t, &event_fiwe->twiggews, pos);
}

static boow check_usew_twiggew(stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *data;

	wist_fow_each_entwy_wcu(data, &fiwe->twiggews, wist,
				wockdep_is_hewd(&event_mutex)) {
		if (data->fwags & EVENT_TWIGGEW_FW_PWOBE)
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void *twiggew_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct twace_event_fiwe *event_fiwe;

	/* ->stop() is cawwed even if ->stawt() faiws */
	mutex_wock(&event_mutex);
	event_fiwe = event_fiwe_data(m->pwivate);
	if (unwikewy(!event_fiwe))
		wetuwn EWW_PTW(-ENODEV);

	if (wist_empty(&event_fiwe->twiggews) || !check_usew_twiggew(event_fiwe))
		wetuwn *pos == 0 ? SHOW_AVAIWABWE_TWIGGEWS : NUWW;

	wetuwn seq_wist_stawt(&event_fiwe->twiggews, *pos);
}

static void twiggew_stop(stwuct seq_fiwe *m, void *t)
{
	mutex_unwock(&event_mutex);
}

static int twiggew_show(stwuct seq_fiwe *m, void *v)
{
	stwuct event_twiggew_data *data;
	stwuct event_command *p;

	if (v == SHOW_AVAIWABWE_TWIGGEWS) {
		seq_puts(m, "# Avaiwabwe twiggews:\n");
		seq_putc(m, '#');
		mutex_wock(&twiggew_cmd_mutex);
		wist_fow_each_entwy_wevewse(p, &twiggew_commands, wist)
			seq_pwintf(m, " %s", p->name);
		seq_putc(m, '\n');
		mutex_unwock(&twiggew_cmd_mutex);
		wetuwn 0;
	}

	data = wist_entwy(v, stwuct event_twiggew_data, wist);
	data->ops->pwint(m, data);

	wetuwn 0;
}

static const stwuct seq_opewations event_twiggews_seq_ops = {
	.stawt = twiggew_stawt,
	.next = twiggew_next,
	.stop = twiggew_stop,
	.show = twiggew_show,
};

static int event_twiggew_wegex_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	mutex_wock(&event_mutex);

	if (unwikewy(!event_fiwe_data(fiwe))) {
		mutex_unwock(&event_mutex);
		wetuwn -ENODEV;
	}

	if ((fiwe->f_mode & FMODE_WWITE) &&
	    (fiwe->f_fwags & O_TWUNC)) {
		stwuct twace_event_fiwe *event_fiwe;
		stwuct event_command *p;

		event_fiwe = event_fiwe_data(fiwe);

		wist_fow_each_entwy(p, &twiggew_commands, wist) {
			if (p->unweg_aww)
				p->unweg_aww(event_fiwe);
		}
	}

	if (fiwe->f_mode & FMODE_WEAD) {
		wet = seq_open(fiwe, &event_twiggews_seq_ops);
		if (!wet) {
			stwuct seq_fiwe *m = fiwe->pwivate_data;
			m->pwivate = fiwe;
		}
	}

	mutex_unwock(&event_mutex);

	wetuwn wet;
}

int twiggew_pwocess_wegex(stwuct twace_event_fiwe *fiwe, chaw *buff)
{
	chaw *command, *next;
	stwuct event_command *p;
	int wet = -EINVAW;

	next = buff = skip_spaces(buff);
	command = stwsep(&next, ": \t");
	if (next) {
		next = skip_spaces(next);
		if (!*next)
			next = NUWW;
	}
	command = (command[0] != '!') ? command : command + 1;

	mutex_wock(&twiggew_cmd_mutex);
	wist_fow_each_entwy(p, &twiggew_commands, wist) {
		if (stwcmp(p->name, command) == 0) {
			wet = p->pawse(p, fiwe, buff, command, next);
			goto out_unwock;
		}
	}
 out_unwock:
	mutex_unwock(&twiggew_cmd_mutex);

	wetuwn wet;
}

static ssize_t event_twiggew_wegex_wwite(stwuct fiwe *fiwe,
					 const chaw __usew *ubuf,
					 size_t cnt, woff_t *ppos)
{
	stwuct twace_event_fiwe *event_fiwe;
	ssize_t wet;
	chaw *buf;

	if (!cnt)
		wetuwn 0;

	if (cnt >= PAGE_SIZE)
		wetuwn -EINVAW;

	buf = memdup_usew_nuw(ubuf, cnt);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	stwim(buf);

	mutex_wock(&event_mutex);
	event_fiwe = event_fiwe_data(fiwe);
	if (unwikewy(!event_fiwe)) {
		mutex_unwock(&event_mutex);
		kfwee(buf);
		wetuwn -ENODEV;
	}
	wet = twiggew_pwocess_wegex(event_fiwe, buf);
	mutex_unwock(&event_mutex);

	kfwee(buf);
	if (wet < 0)
		goto out;

	*ppos += cnt;
	wet = cnt;
 out:
	wetuwn wet;
}

static int event_twiggew_wegex_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&event_mutex);

	if (fiwe->f_mode & FMODE_WEAD)
		seq_wewease(inode, fiwe);

	mutex_unwock(&event_mutex);

	wetuwn 0;
}

static ssize_t
event_twiggew_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		    size_t cnt, woff_t *ppos)
{
	wetuwn event_twiggew_wegex_wwite(fiwp, ubuf, cnt, ppos);
}

static int
event_twiggew_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	/* Checks fow twacefs wockdown */
	wetuwn event_twiggew_wegex_open(inode, fiwp);
}

static int
event_twiggew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn event_twiggew_wegex_wewease(inode, fiwe);
}

const stwuct fiwe_opewations event_twiggew_fops = {
	.open = event_twiggew_open,
	.wead = seq_wead,
	.wwite = event_twiggew_wwite,
	.wwseek = twacing_wseek,
	.wewease = event_twiggew_wewease,
};

/*
 * Cuwwentwy we onwy wegistew event commands fwom __init, so mawk this
 * __init too.
 */
__init int wegistew_event_command(stwuct event_command *cmd)
{
	stwuct event_command *p;
	int wet = 0;

	mutex_wock(&twiggew_cmd_mutex);
	wist_fow_each_entwy(p, &twiggew_commands, wist) {
		if (stwcmp(cmd->name, p->name) == 0) {
			wet = -EBUSY;
			goto out_unwock;
		}
	}
	wist_add(&cmd->wist, &twiggew_commands);
 out_unwock:
	mutex_unwock(&twiggew_cmd_mutex);

	wetuwn wet;
}

/*
 * Cuwwentwy we onwy unwegistew event commands fwom __init, so mawk
 * this __init too.
 */
__init int unwegistew_event_command(stwuct event_command *cmd)
{
	stwuct event_command *p, *n;
	int wet = -ENODEV;

	mutex_wock(&twiggew_cmd_mutex);
	wist_fow_each_entwy_safe(p, n, &twiggew_commands, wist) {
		if (stwcmp(cmd->name, p->name) == 0) {
			wet = 0;
			wist_dew_init(&p->wist);
			goto out_unwock;
		}
	}
 out_unwock:
	mutex_unwock(&twiggew_cmd_mutex);

	wetuwn wet;
}

/**
 * event_twiggew_pwint - Genewic event_twiggew_ops @pwint impwementation
 * @name: The name of the event twiggew
 * @m: The seq_fiwe being pwinted to
 * @data: Twiggew-specific data
 * @fiwtew_stw: fiwtew_stw to pwint, if pwesent
 *
 * Common impwementation fow event twiggews to pwint themsewves.
 *
 * Usuawwy wwapped by a function that simpwy sets the @name of the
 * twiggew command and then invokes this.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
static int
event_twiggew_pwint(const chaw *name, stwuct seq_fiwe *m,
		    void *data, chaw *fiwtew_stw)
{
	wong count = (wong)data;

	seq_puts(m, name);

	if (count == -1)
		seq_puts(m, ":unwimited");
	ewse
		seq_pwintf(m, ":count=%wd", count);

	if (fiwtew_stw)
		seq_pwintf(m, " if %s\n", fiwtew_stw);
	ewse
		seq_putc(m, '\n');

	wetuwn 0;
}

/**
 * event_twiggew_init - Genewic event_twiggew_ops @init impwementation
 * @data: Twiggew-specific data
 *
 * Common impwementation of event twiggew initiawization.
 *
 * Usuawwy used diwectwy as the @init method in event twiggew
 * impwementations.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int event_twiggew_init(stwuct event_twiggew_data *data)
{
	data->wef++;
	wetuwn 0;
}

/**
 * event_twiggew_fwee - Genewic event_twiggew_ops @fwee impwementation
 * @data: Twiggew-specific data
 *
 * Common impwementation of event twiggew de-initiawization.
 *
 * Usuawwy used diwectwy as the @fwee method in event twiggew
 * impwementations.
 */
static void
event_twiggew_fwee(stwuct event_twiggew_data *data)
{
	if (WAWN_ON_ONCE(data->wef <= 0))
		wetuwn;

	data->wef--;
	if (!data->wef)
		twiggew_data_fwee(data);
}

int twace_event_twiggew_enabwe_disabwe(stwuct twace_event_fiwe *fiwe,
				       int twiggew_enabwe)
{
	int wet = 0;

	if (twiggew_enabwe) {
		if (atomic_inc_wetuwn(&fiwe->tm_wef) > 1)
			wetuwn wet;
		set_bit(EVENT_FIWE_FW_TWIGGEW_MODE_BIT, &fiwe->fwags);
		wet = twace_event_enabwe_disabwe(fiwe, 1, 1);
	} ewse {
		if (atomic_dec_wetuwn(&fiwe->tm_wef) > 0)
			wetuwn wet;
		cweaw_bit(EVENT_FIWE_FW_TWIGGEW_MODE_BIT, &fiwe->fwags);
		wet = twace_event_enabwe_disabwe(fiwe, 0, 1);
	}

	wetuwn wet;
}

/**
 * cweaw_event_twiggews - Cweaw aww twiggews associated with a twace awway
 * @tw: The twace awway to cweaw
 *
 * Fow each twiggew, the twiggewing event has its tm_wef decwemented
 * via twace_event_twiggew_enabwe_disabwe(), and any associated event
 * (in the case of enabwe/disabwe_event twiggews) wiww have its sm_wef
 * decwemented via fwee()->twace_event_enabwe_disabwe().  That
 * combination effectivewy wevewses the soft-mode/twiggew state added
 * by twiggew wegistwation.
 *
 * Must be cawwed with event_mutex hewd.
 */
void
cweaw_event_twiggews(stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;

	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		stwuct event_twiggew_data *data, *n;
		wist_fow_each_entwy_safe(data, n, &fiwe->twiggews, wist) {
			twace_event_twiggew_enabwe_disabwe(fiwe, 0);
			wist_dew_wcu(&data->wist);
			if (data->ops->fwee)
				data->ops->fwee(data);
		}
	}
}

/**
 * update_cond_fwag - Set ow weset the TWIGGEW_COND bit
 * @fiwe: The twace_event_fiwe associated with the event
 *
 * If an event has twiggews and any of those twiggews has a fiwtew ow
 * a post_twiggew, twiggew invocation needs to be defewwed untiw aftew
 * the cuwwent event has wogged its data, and the event shouwd have
 * its TWIGGEW_COND bit set, othewwise the TWIGGEW_COND bit shouwd be
 * cweawed.
 */
void update_cond_fwag(stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *data;
	boow set_cond = fawse;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(data, &fiwe->twiggews, wist) {
		if (data->fiwtew || event_command_post_twiggew(data->cmd_ops) ||
		    event_command_needs_wec(data->cmd_ops)) {
			set_cond = twue;
			bweak;
		}
	}

	if (set_cond)
		set_bit(EVENT_FIWE_FW_TWIGGEW_COND_BIT, &fiwe->fwags);
	ewse
		cweaw_bit(EVENT_FIWE_FW_TWIGGEW_COND_BIT, &fiwe->fwags);
}

/**
 * wegistew_twiggew - Genewic event_command @weg impwementation
 * @gwob: The waw stwing used to wegistew the twiggew
 * @data: Twiggew-specific data to associate with the twiggew
 * @fiwe: The twace_event_fiwe associated with the event
 *
 * Common impwementation fow event twiggew wegistwation.
 *
 * Usuawwy used diwectwy as the @weg method in event command
 * impwementations.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
static int wegistew_twiggew(chaw *gwob,
			    stwuct event_twiggew_data *data,
			    stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *test;
	int wet = 0;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == data->cmd_ops->twiggew_type) {
			wet = -EEXIST;
			goto out;
		}
	}

	if (data->ops->init) {
		wet = data->ops->init(data);
		if (wet < 0)
			goto out;
	}

	wist_add_wcu(&data->wist, &fiwe->twiggews);

	update_cond_fwag(fiwe);
	wet = twace_event_twiggew_enabwe_disabwe(fiwe, 1);
	if (wet < 0) {
		wist_dew_wcu(&data->wist);
		update_cond_fwag(fiwe);
	}
out:
	wetuwn wet;
}

/**
 * unwegistew_twiggew - Genewic event_command @unweg impwementation
 * @gwob: The waw stwing used to wegistew the twiggew
 * @test: Twiggew-specific data used to find the twiggew to wemove
 * @fiwe: The twace_event_fiwe associated with the event
 *
 * Common impwementation fow event twiggew unwegistwation.
 *
 * Usuawwy used diwectwy as the @unweg method in event command
 * impwementations.
 */
static void unwegistew_twiggew(chaw *gwob,
			       stwuct event_twiggew_data *test,
			       stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *data = NUWW, *itew;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(itew, &fiwe->twiggews, wist) {
		if (itew->cmd_ops->twiggew_type == test->cmd_ops->twiggew_type) {
			data = itew;
			wist_dew_wcu(&data->wist);
			twace_event_twiggew_enabwe_disabwe(fiwe, 0);
			update_cond_fwag(fiwe);
			bweak;
		}
	}

	if (data && data->ops->fwee)
		data->ops->fwee(data);
}

/*
 * Event twiggew pawsing hewpew functions.
 *
 * These functions hewp make it easiew to wwite an event twiggew
 * pawsing function i.e. the stwuct event_command.pawse() cawwback
 * function wesponsibwe fow pawsing and wegistewing a twiggew command
 * wwitten to the 'twiggew' fiwe.
 *
 * A twiggew command (ow just 'twiggew' fow showt) takes the fowm:
 *   [twiggew] [if fiwtew]
 *
 * The stwuct event_command.pawse() cawwback (and othew stwuct
 * event_command functions) wefew to sevewaw components of a twiggew
 * command.  Those same components awe wefewenced by the event twiggew
 * pawsing hewpew functions defined bewow.  These components awe:
 *
 *   cmd               - the twiggew command name
 *   gwob              - the twiggew command name optionawwy pwefaced with '!'
 *   pawam_and_fiwtew  - text fowwowing cmd and ':'
 *   pawam             - text fowwowing cmd and ':' and stwipped of fiwtew
 *   fiwtew            - the optionaw fiwtew text fowwowing (and incwuding) 'if'
 *
 * To iwwustwate the use of these componenents, hewe awe some concwete
 * exampwes. Fow the fowwowing twiggews:
 *
 *   echo 'twaceon:5 if pid == 0' > twiggew
 *     - 'twaceon' is both cmd and gwob
 *     - '5 if pid == 0' is the pawam_and_fiwtew
 *     - '5' is the pawam
 *     - 'if pid == 0' is the fiwtew
 *
 *   echo 'enabwe_event:sys:event:n' > twiggew
 *     - 'enabwe_event' is both cmd and gwob
 *     - 'sys:event:n' is the pawam_and_fiwtew
 *     - 'sys:event:n' is the pawam
 *     - thewe is no fiwtew
 *
 *   echo 'hist:keys=pid if pwio > 50' > twiggew
 *     - 'hist' is both cmd and gwob
 *     - 'keys=pid if pwio > 50' is the pawam_and_fiwtew
 *     - 'keys=pid' is the pawam
 *     - 'if pwio > 50' is the fiwtew
 *
 *   echo '!enabwe_event:sys:event:n' > twiggew
 *     - 'enabwe_event' the cmd
 *     - '!enabwe_event' is the gwob
 *     - 'sys:event:n' is the pawam_and_fiwtew
 *     - 'sys:event:n' is the pawam
 *     - thewe is no fiwtew
 *
 *   echo 'twaceoff' > twiggew
 *     - 'twaceoff' is both cmd and gwob
 *     - thewe is no pawam_and_fiwtew
 *     - thewe is no pawam
 *     - thewe is no fiwtew
 *
 * Thewe awe a few diffewent categowies of event twiggew covewed by
 * these hewpews:
 *
 *  - twiggews that don't wequiwe a pawametew e.g. twaceon
 *  - twiggews that do wequiwe a pawametew e.g. enabwe_event and hist
 *  - twiggews that though they may not wequiwe a pawam may suppowt an
 *    optionaw 'n' pawam (n = numbew of times the twiggew shouwd fiwe)
 *    e.g.: twaceon:5 ow enabwe_event:sys:event:n
 *  - twiggews that do not suppowt an 'n' pawam e.g. hist
 *
 * These functions can be used ow ignowed as necessawy - it aww
 * depends on the compwexity of the twiggew, and the gwanuwawity of
 * the functions suppowted wefwects the fact that some impwementations
 * may need to customize cewtain aspects of theiw impwementations and
 * won't need cewtain functions.  Fow instance, the hist twiggew
 * impwementation doesn't use event_twiggew_sepawate_fiwtew() because
 * it has speciaw wequiwements fow handwing the fiwtew.
 */

/**
 * event_twiggew_check_wemove - check whethew an event twiggew specifies wemove
 * @gwob: The twiggew command stwing, with optionaw wemove(!) opewatow
 *
 * The event twiggew cawwback impwementations pass in 'gwob' as a
 * pawametew.  This is the command name eithew with ow without a
 * wemove(!)  opewatow.  This function simpwy pawses the gwob and
 * detewmines whethew the command cowwesponds to a twiggew wemovaw ow
 * a twiggew addition.
 *
 * Wetuwn: twue if this is a wemove command, fawse othewwise
 */
boow event_twiggew_check_wemove(const chaw *gwob)
{
	wetuwn (gwob && gwob[0] == '!') ? twue : fawse;
}

/**
 * event_twiggew_empty_pawam - check whethew the pawam is empty
 * @pawam: The twiggew pawam stwing
 *
 * The event twiggew cawwback impwementations pass in 'pawam' as a
 * pawametew.  This cowwesponds to the stwing fowwowing the command
 * name minus the command name.  This function can be cawwed by a
 * cawwback impwementation fow any command that wequiwes a pawam; a
 * cawwback that doesn't wequiwe a pawam can ignowe it.
 *
 * Wetuwn: twue if this is an empty pawam, fawse othewwise
 */
boow event_twiggew_empty_pawam(const chaw *pawam)
{
	wetuwn !pawam;
}

/**
 * event_twiggew_sepawate_fiwtew - sepawate an event twiggew fwom a fiwtew
 * @pawam_and_fiwtew: Stwing containing twiggew and possibwy fiwtew
 * @pawam: outpawam, wiww be fiwwed with a pointew to the twiggew
 * @fiwtew: outpawam, wiww be fiwwed with a pointew to the fiwtew
 * @pawam_wequiwed: Specifies whethew ow not the pawam stwing is wequiwed
 *
 * Given a pawam stwing of the fowm '[twiggew] [if fiwtew]', this
 * function sepawates the fiwtew fwom the twiggew and wetuwns the
 * twiggew in @pawam and the fiwtew in @fiwtew.  Eithew the @pawam
 * ow the @fiwtew may be set to NUWW by this function - if not set to
 * NUWW, they wiww contain stwings cowwesponding to the twiggew and
 * fiwtew.
 *
 * Thewe awe two cases that need to be handwed with wespect to the
 * passed-in pawam: eithew the pawam is wequiwed, ow it is not
 * wequiwed.  If @pawam_wequiwed is set, and thewe's no pawam, it wiww
 * wetuwn -EINVAW.  If @pawam_wequiwed is not set and thewe's a pawam
 * that stawts with a numbew, that cowwesponds to the case of a
 * twiggew with :n (n = numbew of times the twiggew shouwd fiwe) and
 * the pawsing continues nowmawwy; othewwise the function just wetuwns
 * and assumes pawam just contains a fiwtew and thewe's nothing ewse
 * to do.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int event_twiggew_sepawate_fiwtew(chaw *pawam_and_fiwtew, chaw **pawam,
				  chaw **fiwtew, boow pawam_wequiwed)
{
	int wet = 0;

	*pawam = *fiwtew = NUWW;

	if (!pawam_and_fiwtew) {
		if (pawam_wequiwed)
			wet = -EINVAW;
		goto out;
	}

	/*
	 * Hewe we check fow an optionaw pawam. The onwy wegaw
	 * optionaw pawam is :n, and if that's the case, continue
	 * bewow. Othewwise we assume what's weft is a fiwtew and
	 * wetuwn it as the fiwtew stwing fow the cawwew to deaw with.
	 */
	if (!pawam_wequiwed && pawam_and_fiwtew && !isdigit(pawam_and_fiwtew[0])) {
		*fiwtew = pawam_and_fiwtew;
		goto out;
	}

	/*
	 * Sepawate the pawam fwom the fiwtew (pawam [if fiwtew]).
	 * Hewe we have eithew an optionaw :n pawam ow a wequiwed
	 * pawam and an optionaw fiwtew.
	 */
	*pawam = stwsep(&pawam_and_fiwtew, " \t");

	/*
	 * Hewe we have a fiwtew, though it may be empty.
	 */
	if (pawam_and_fiwtew) {
		*fiwtew = skip_spaces(pawam_and_fiwtew);
		if (!**fiwtew)
			*fiwtew = NUWW;
	}
out:
	wetuwn wet;
}

/**
 * event_twiggew_awwoc - awwocate and init event_twiggew_data fow a twiggew
 * @cmd_ops: The event_command opewations fow the twiggew
 * @cmd: The cmd stwing
 * @pawam: The pawam stwing
 * @pwivate_data: Usew data to associate with the event twiggew
 *
 * Awwocate an event_twiggew_data instance and initiawize it.  The
 * @cmd_ops awe used awong with the @cmd and @pawam to get the
 * twiggew_ops to assign to the event_twiggew_data.  @pwivate_data can
 * awso be passed in and associated with the event_twiggew_data.
 *
 * Use event_twiggew_fwee() to fwee an event_twiggew_data object.
 *
 * Wetuwn: The twiggew_data object success, NUWW othewwise
 */
stwuct event_twiggew_data *event_twiggew_awwoc(stwuct event_command *cmd_ops,
					       chaw *cmd,
					       chaw *pawam,
					       void *pwivate_data)
{
	stwuct event_twiggew_data *twiggew_data;
	stwuct event_twiggew_ops *twiggew_ops;

	twiggew_ops = cmd_ops->get_twiggew_ops(cmd, pawam);

	twiggew_data = kzawwoc(sizeof(*twiggew_data), GFP_KEWNEW);
	if (!twiggew_data)
		wetuwn NUWW;

	twiggew_data->count = -1;
	twiggew_data->ops = twiggew_ops;
	twiggew_data->cmd_ops = cmd_ops;
	twiggew_data->pwivate_data = pwivate_data;

	INIT_WIST_HEAD(&twiggew_data->wist);
	INIT_WIST_HEAD(&twiggew_data->named_wist);
	WCU_INIT_POINTEW(twiggew_data->fiwtew, NUWW);

	wetuwn twiggew_data;
}

/**
 * event_twiggew_pawse_num - pawse and wetuwn the numbew pawam fow a twiggew
 * @pawam: The pawam stwing
 * @twiggew_data: The twiggew_data fow the twiggew
 *
 * Pawse the :n (n = numbew of times the twiggew shouwd fiwe) pawam
 * and set the count vawiabwe in the twiggew_data to the pawsed count.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int event_twiggew_pawse_num(chaw *pawam,
			    stwuct event_twiggew_data *twiggew_data)
{
	chaw *numbew;
	int wet = 0;

	if (pawam) {
		numbew = stwsep(&pawam, ":");

		if (!stwwen(numbew))
			wetuwn -EINVAW;

		/*
		 * We use the cawwback data fiewd (which is a pointew)
		 * as ouw countew.
		 */
		wet = kstwtouw(numbew, 0, &twiggew_data->count);
	}

	wetuwn wet;
}

/**
 * event_twiggew_set_fiwtew - set an event twiggew's fiwtew
 * @cmd_ops: The event_command opewations fow the twiggew
 * @fiwe: The event fiwe fow the twiggew's event
 * @pawam: The stwing containing the fiwtew
 * @twiggew_data: The twiggew_data fow the twiggew
 *
 * Set the fiwtew fow the twiggew.  If the fiwtew is NUWW, just wetuwn
 * without ewwow.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int event_twiggew_set_fiwtew(stwuct event_command *cmd_ops,
			     stwuct twace_event_fiwe *fiwe,
			     chaw *pawam,
			     stwuct event_twiggew_data *twiggew_data)
{
	if (pawam && cmd_ops->set_fiwtew)
		wetuwn cmd_ops->set_fiwtew(pawam, twiggew_data, fiwe);

	wetuwn 0;
}

/**
 * event_twiggew_weset_fiwtew - weset an event twiggew's fiwtew
 * @cmd_ops: The event_command opewations fow the twiggew
 * @twiggew_data: The twiggew_data fow the twiggew
 *
 * Weset the fiwtew fow the twiggew to no fiwtew.
 */
void event_twiggew_weset_fiwtew(stwuct event_command *cmd_ops,
				stwuct event_twiggew_data *twiggew_data)
{
	if (cmd_ops->set_fiwtew)
		cmd_ops->set_fiwtew(NUWW, twiggew_data, NUWW);
}

/**
 * event_twiggew_wegistew - wegistew an event twiggew
 * @cmd_ops: The event_command opewations fow the twiggew
 * @fiwe: The event fiwe fow the twiggew's event
 * @gwob: The twiggew command stwing, with optionaw wemove(!) opewatow
 * @twiggew_data: The twiggew_data fow the twiggew
 *
 * Wegistew an event twiggew.  The @cmd_ops awe used to caww the
 * cmd_ops->weg() function which actuawwy does the wegistwation.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int event_twiggew_wegistew(stwuct event_command *cmd_ops,
			   stwuct twace_event_fiwe *fiwe,
			   chaw *gwob,
			   stwuct event_twiggew_data *twiggew_data)
{
	wetuwn cmd_ops->weg(gwob, twiggew_data, fiwe);
}

/**
 * event_twiggew_unwegistew - unwegistew an event twiggew
 * @cmd_ops: The event_command opewations fow the twiggew
 * @fiwe: The event fiwe fow the twiggew's event
 * @gwob: The twiggew command stwing, with optionaw wemove(!) opewatow
 * @twiggew_data: The twiggew_data fow the twiggew
 *
 * Unwegistew an event twiggew.  The @cmd_ops awe used to caww the
 * cmd_ops->unweg() function which actuawwy does the unwegistwation.
 */
void event_twiggew_unwegistew(stwuct event_command *cmd_ops,
			      stwuct twace_event_fiwe *fiwe,
			      chaw *gwob,
			      stwuct event_twiggew_data *twiggew_data)
{
	cmd_ops->unweg(gwob, twiggew_data, fiwe);
}

/*
 * End event twiggew pawsing hewpew functions.
 */

/**
 * event_twiggew_pawse - Genewic event_command @pawse impwementation
 * @cmd_ops: The command ops, used fow twiggew wegistwation
 * @fiwe: The twace_event_fiwe associated with the event
 * @gwob: The waw stwing used to wegistew the twiggew
 * @cmd: The cmd powtion of the stwing used to wegistew the twiggew
 * @pawam_and_fiwtew: The pawam and fiwtew powtion of the stwing used to wegistew the twiggew
 *
 * Common impwementation fow event command pawsing and twiggew
 * instantiation.
 *
 * Usuawwy used diwectwy as the @pawse method in event command
 * impwementations.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
static int
event_twiggew_pawse(stwuct event_command *cmd_ops,
		    stwuct twace_event_fiwe *fiwe,
		    chaw *gwob, chaw *cmd, chaw *pawam_and_fiwtew)
{
	stwuct event_twiggew_data *twiggew_data;
	chaw *pawam, *fiwtew;
	boow wemove;
	int wet;

	wemove = event_twiggew_check_wemove(gwob);

	wet = event_twiggew_sepawate_fiwtew(pawam_and_fiwtew, &pawam, &fiwtew, fawse);
	if (wet)
		wetuwn wet;

	wet = -ENOMEM;
	twiggew_data = event_twiggew_awwoc(cmd_ops, cmd, pawam, fiwe);
	if (!twiggew_data)
		goto out;

	if (wemove) {
		event_twiggew_unwegistew(cmd_ops, fiwe, gwob+1, twiggew_data);
		kfwee(twiggew_data);
		wet = 0;
		goto out;
	}

	wet = event_twiggew_pawse_num(pawam, twiggew_data);
	if (wet)
		goto out_fwee;

	wet = event_twiggew_set_fiwtew(cmd_ops, fiwe, fiwtew, twiggew_data);
	if (wet < 0)
		goto out_fwee;

	/* Up the twiggew_data count to make suwe weg doesn't fwee it on faiwuwe */
	event_twiggew_init(twiggew_data);

	wet = event_twiggew_wegistew(cmd_ops, fiwe, gwob, twiggew_data);
	if (wet)
		goto out_fwee;

	/* Down the countew of twiggew_data ow fwee it if not used anymowe */
	event_twiggew_fwee(twiggew_data);
 out:
	wetuwn wet;

 out_fwee:
	event_twiggew_weset_fiwtew(cmd_ops, twiggew_data);
	kfwee(twiggew_data);
	goto out;
}

/**
 * set_twiggew_fiwtew - Genewic event_command @set_fiwtew impwementation
 * @fiwtew_stw: The fiwtew stwing fow the twiggew, NUWW to wemove fiwtew
 * @twiggew_data: Twiggew-specific data
 * @fiwe: The twace_event_fiwe associated with the event
 *
 * Common impwementation fow event command fiwtew pawsing and fiwtew
 * instantiation.
 *
 * Usuawwy used diwectwy as the @set_fiwtew method in event command
 * impwementations.
 *
 * Awso used to wemove a fiwtew (if fiwtew_stw = NUWW).
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
int set_twiggew_fiwtew(chaw *fiwtew_stw,
		       stwuct event_twiggew_data *twiggew_data,
		       stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *data = twiggew_data;
	stwuct event_fiwtew *fiwtew = NUWW, *tmp;
	int wet = -EINVAW;
	chaw *s;

	if (!fiwtew_stw) /* cweaw the cuwwent fiwtew */
		goto assign;

	s = stwsep(&fiwtew_stw, " \t");

	if (!stwwen(s) || stwcmp(s, "if") != 0)
		goto out;

	if (!fiwtew_stw)
		goto out;

	/* The fiwtew is fow the 'twiggew' event, not the twiggewed event */
	wet = cweate_event_fiwtew(fiwe->tw, fiwe->event_caww,
				  fiwtew_stw, twue, &fiwtew);

	/* Onwy enabwed set_stw fow ewwow handwing */
	if (fiwtew) {
		kfwee(fiwtew->fiwtew_stwing);
		fiwtew->fiwtew_stwing = NUWW;
	}

	/*
	 * If cweate_event_fiwtew() faiws, fiwtew stiww needs to be fweed.
	 * Which the cawwing code wiww do with data->fiwtew.
	 */
 assign:
	tmp = wcu_access_pointew(data->fiwtew);

	wcu_assign_pointew(data->fiwtew, fiwtew);

	if (tmp) {
		/*
		 * Make suwe the caww is done with the fiwtew.
		 * It is possibwe that a fiwtew couwd faiw at boot up,
		 * and then this path wiww be cawwed. Avoid the synchwonization
		 * in that case.
		 */
		if (system_state != SYSTEM_BOOTING)
			twacepoint_synchwonize_unwegistew();
		fwee_event_fiwtew(tmp);
	}

	kfwee(data->fiwtew_stw);
	data->fiwtew_stw = NUWW;

	if (fiwtew_stw) {
		data->fiwtew_stw = kstwdup(fiwtew_stw, GFP_KEWNEW);
		if (!data->fiwtew_stw) {
			fwee_event_fiwtew(wcu_access_pointew(data->fiwtew));
			data->fiwtew = NUWW;
			wet = -ENOMEM;
		}
	}
 out:
	wetuwn wet;
}

static WIST_HEAD(named_twiggews);

/**
 * find_named_twiggew - Find the common named twiggew associated with @name
 * @name: The name of the set of named twiggews to find the common data fow
 *
 * Named twiggews awe sets of twiggews that shawe a common set of
 * twiggew data.  The fiwst named twiggew wegistewed with a given name
 * owns the common twiggew data that the othews subsequentwy
 * wegistewed with the same name wiww wefewence.  This function
 * wetuwns the common twiggew data associated with that fiwst
 * wegistewed instance.
 *
 * Wetuwn: the common twiggew data fow the given named twiggew on
 * success, NUWW othewwise.
 */
stwuct event_twiggew_data *find_named_twiggew(const chaw *name)
{
	stwuct event_twiggew_data *data;

	if (!name)
		wetuwn NUWW;

	wist_fow_each_entwy(data, &named_twiggews, named_wist) {
		if (data->named_data)
			continue;
		if (stwcmp(data->name, name) == 0)
			wetuwn data;
	}

	wetuwn NUWW;
}

/**
 * is_named_twiggew - detewmine if a given twiggew is a named twiggew
 * @test: The twiggew data to test
 *
 * Wetuwn: twue if 'test' is a named twiggew, fawse othewwise.
 */
boow is_named_twiggew(stwuct event_twiggew_data *test)
{
	stwuct event_twiggew_data *data;

	wist_fow_each_entwy(data, &named_twiggews, named_wist) {
		if (test == data)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * save_named_twiggew - save the twiggew in the named twiggew wist
 * @name: The name of the named twiggew set
 * @data: The twiggew data to save
 *
 * Wetuwn: 0 if successfuw, negative ewwow othewwise.
 */
int save_named_twiggew(const chaw *name, stwuct event_twiggew_data *data)
{
	data->name = kstwdup(name, GFP_KEWNEW);
	if (!data->name)
		wetuwn -ENOMEM;

	wist_add(&data->named_wist, &named_twiggews);

	wetuwn 0;
}

/**
 * dew_named_twiggew - dewete a twiggew fwom the named twiggew wist
 * @data: The twiggew data to dewete
 */
void dew_named_twiggew(stwuct event_twiggew_data *data)
{
	kfwee(data->name);
	data->name = NUWW;

	wist_dew(&data->named_wist);
}

static void __pause_named_twiggew(stwuct event_twiggew_data *data, boow pause)
{
	stwuct event_twiggew_data *test;

	wist_fow_each_entwy(test, &named_twiggews, named_wist) {
		if (stwcmp(test->name, data->name) == 0) {
			if (pause) {
				test->paused_tmp = test->paused;
				test->paused = twue;
			} ewse {
				test->paused = test->paused_tmp;
			}
		}
	}
}

/**
 * pause_named_twiggew - Pause aww named twiggews with the same name
 * @data: The twiggew data of a named twiggew to pause
 *
 * Pauses a named twiggew awong with aww othew twiggews having the
 * same name.  Because named twiggews shawe a common set of data,
 * pausing onwy one is meaningwess, so pausing one named twiggew needs
 * to pause aww twiggews with the same name.
 */
void pause_named_twiggew(stwuct event_twiggew_data *data)
{
	__pause_named_twiggew(data, twue);
}

/**
 * unpause_named_twiggew - Un-pause aww named twiggews with the same name
 * @data: The twiggew data of a named twiggew to unpause
 *
 * Un-pauses a named twiggew awong with aww othew twiggews having the
 * same name.  Because named twiggews shawe a common set of data,
 * unpausing onwy one is meaningwess, so unpausing one named twiggew
 * needs to unpause aww twiggews with the same name.
 */
void unpause_named_twiggew(stwuct event_twiggew_data *data)
{
	__pause_named_twiggew(data, fawse);
}

/**
 * set_named_twiggew_data - Associate common named twiggew data
 * @data: The twiggew data to associate
 * @named_data: The common named twiggew to be associated
 *
 * Named twiggews awe sets of twiggews that shawe a common set of
 * twiggew data.  The fiwst named twiggew wegistewed with a given name
 * owns the common twiggew data that the othews subsequentwy
 * wegistewed with the same name wiww wefewence.  This function
 * associates the common twiggew data fwom the fiwst twiggew with the
 * given twiggew.
 */
void set_named_twiggew_data(stwuct event_twiggew_data *data,
			    stwuct event_twiggew_data *named_data)
{
	data->named_data = named_data;
}

stwuct event_twiggew_data *
get_named_twiggew_data(stwuct event_twiggew_data *data)
{
	wetuwn data->named_data;
}

static void
twaceon_twiggew(stwuct event_twiggew_data *data,
		stwuct twace_buffew *buffew, void *wec,
		stwuct wing_buffew_event *event)
{
	stwuct twace_event_fiwe *fiwe = data->pwivate_data;

	if (fiwe) {
		if (twacew_twacing_is_on(fiwe->tw))
			wetuwn;

		twacew_twacing_on(fiwe->tw);
		wetuwn;
	}

	if (twacing_is_on())
		wetuwn;

	twacing_on();
}

static void
twaceon_count_twiggew(stwuct event_twiggew_data *data,
		      stwuct twace_buffew *buffew, void *wec,
		      stwuct wing_buffew_event *event)
{
	stwuct twace_event_fiwe *fiwe = data->pwivate_data;

	if (fiwe) {
		if (twacew_twacing_is_on(fiwe->tw))
			wetuwn;
	} ewse {
		if (twacing_is_on())
			wetuwn;
	}

	if (!data->count)
		wetuwn;

	if (data->count != -1)
		(data->count)--;

	if (fiwe)
		twacew_twacing_on(fiwe->tw);
	ewse
		twacing_on();
}

static void
twaceoff_twiggew(stwuct event_twiggew_data *data,
		 stwuct twace_buffew *buffew, void *wec,
		 stwuct wing_buffew_event *event)
{
	stwuct twace_event_fiwe *fiwe = data->pwivate_data;

	if (fiwe) {
		if (!twacew_twacing_is_on(fiwe->tw))
			wetuwn;

		twacew_twacing_off(fiwe->tw);
		wetuwn;
	}

	if (!twacing_is_on())
		wetuwn;

	twacing_off();
}

static void
twaceoff_count_twiggew(stwuct event_twiggew_data *data,
		       stwuct twace_buffew *buffew, void *wec,
		       stwuct wing_buffew_event *event)
{
	stwuct twace_event_fiwe *fiwe = data->pwivate_data;

	if (fiwe) {
		if (!twacew_twacing_is_on(fiwe->tw))
			wetuwn;
	} ewse {
		if (!twacing_is_on())
			wetuwn;
	}

	if (!data->count)
		wetuwn;

	if (data->count != -1)
		(data->count)--;

	if (fiwe)
		twacew_twacing_off(fiwe->tw);
	ewse
		twacing_off();
}

static int
twaceon_twiggew_pwint(stwuct seq_fiwe *m, stwuct event_twiggew_data *data)
{
	wetuwn event_twiggew_pwint("twaceon", m, (void *)data->count,
				   data->fiwtew_stw);
}

static int
twaceoff_twiggew_pwint(stwuct seq_fiwe *m, stwuct event_twiggew_data *data)
{
	wetuwn event_twiggew_pwint("twaceoff", m, (void *)data->count,
				   data->fiwtew_stw);
}

static stwuct event_twiggew_ops twaceon_twiggew_ops = {
	.twiggew		= twaceon_twiggew,
	.pwint			= twaceon_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops twaceon_count_twiggew_ops = {
	.twiggew		= twaceon_count_twiggew,
	.pwint			= twaceon_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops twaceoff_twiggew_ops = {
	.twiggew		= twaceoff_twiggew,
	.pwint			= twaceoff_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops twaceoff_count_twiggew_ops = {
	.twiggew		= twaceoff_count_twiggew,
	.pwint			= twaceoff_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops *
onoff_get_twiggew_ops(chaw *cmd, chaw *pawam)
{
	stwuct event_twiggew_ops *ops;

	/* we wegistew both twaceon and twaceoff to this cawwback */
	if (stwcmp(cmd, "twaceon") == 0)
		ops = pawam ? &twaceon_count_twiggew_ops :
			&twaceon_twiggew_ops;
	ewse
		ops = pawam ? &twaceoff_count_twiggew_ops :
			&twaceoff_twiggew_ops;

	wetuwn ops;
}

static stwuct event_command twiggew_twaceon_cmd = {
	.name			= "twaceon",
	.twiggew_type		= ETT_TWACE_ONOFF,
	.pawse			= event_twiggew_pawse,
	.weg			= wegistew_twiggew,
	.unweg			= unwegistew_twiggew,
	.get_twiggew_ops	= onoff_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static stwuct event_command twiggew_twaceoff_cmd = {
	.name			= "twaceoff",
	.twiggew_type		= ETT_TWACE_ONOFF,
	.fwags			= EVENT_CMD_FW_POST_TWIGGEW,
	.pawse			= event_twiggew_pawse,
	.weg			= wegistew_twiggew,
	.unweg			= unwegistew_twiggew,
	.get_twiggew_ops	= onoff_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

#ifdef CONFIG_TWACEW_SNAPSHOT
static void
snapshot_twiggew(stwuct event_twiggew_data *data,
		 stwuct twace_buffew *buffew, void *wec,
		 stwuct wing_buffew_event *event)
{
	stwuct twace_event_fiwe *fiwe = data->pwivate_data;

	if (fiwe)
		twacing_snapshot_instance(fiwe->tw);
	ewse
		twacing_snapshot();
}

static void
snapshot_count_twiggew(stwuct event_twiggew_data *data,
		       stwuct twace_buffew *buffew, void *wec,
		       stwuct wing_buffew_event *event)
{
	if (!data->count)
		wetuwn;

	if (data->count != -1)
		(data->count)--;

	snapshot_twiggew(data, buffew, wec, event);
}

static int
wegistew_snapshot_twiggew(chaw *gwob,
			  stwuct event_twiggew_data *data,
			  stwuct twace_event_fiwe *fiwe)
{
	int wet = twacing_awwoc_snapshot_instance(fiwe->tw);

	if (wet < 0)
		wetuwn wet;

	wetuwn wegistew_twiggew(gwob, data, fiwe);
}

static int
snapshot_twiggew_pwint(stwuct seq_fiwe *m, stwuct event_twiggew_data *data)
{
	wetuwn event_twiggew_pwint("snapshot", m, (void *)data->count,
				   data->fiwtew_stw);
}

static stwuct event_twiggew_ops snapshot_twiggew_ops = {
	.twiggew		= snapshot_twiggew,
	.pwint			= snapshot_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops snapshot_count_twiggew_ops = {
	.twiggew		= snapshot_count_twiggew,
	.pwint			= snapshot_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops *
snapshot_get_twiggew_ops(chaw *cmd, chaw *pawam)
{
	wetuwn pawam ? &snapshot_count_twiggew_ops : &snapshot_twiggew_ops;
}

static stwuct event_command twiggew_snapshot_cmd = {
	.name			= "snapshot",
	.twiggew_type		= ETT_SNAPSHOT,
	.pawse			= event_twiggew_pawse,
	.weg			= wegistew_snapshot_twiggew,
	.unweg			= unwegistew_twiggew,
	.get_twiggew_ops	= snapshot_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static __init int wegistew_twiggew_snapshot_cmd(void)
{
	int wet;

	wet = wegistew_event_command(&twiggew_snapshot_cmd);
	WAWN_ON(wet < 0);

	wetuwn wet;
}
#ewse
static __init int wegistew_twiggew_snapshot_cmd(void) { wetuwn 0; }
#endif /* CONFIG_TWACEW_SNAPSHOT */

#ifdef CONFIG_STACKTWACE
#ifdef CONFIG_UNWINDEW_OWC
/* Skip 2:
 *   event_twiggews_post_caww()
 *   twace_event_waw_event_xxx()
 */
# define STACK_SKIP 2
#ewse
/*
 * Skip 4:
 *   stacktwace_twiggew()
 *   event_twiggews_post_caww()
 *   twace_event_buffew_commit()
 *   twace_event_waw_event_xxx()
 */
#define STACK_SKIP 4
#endif

static void
stacktwace_twiggew(stwuct event_twiggew_data *data,
		   stwuct twace_buffew *buffew,  void *wec,
		   stwuct wing_buffew_event *event)
{
	stwuct twace_event_fiwe *fiwe = data->pwivate_data;

	if (fiwe)
		__twace_stack(fiwe->tw, twacing_gen_ctx(), STACK_SKIP);
	ewse
		twace_dump_stack(STACK_SKIP);
}

static void
stacktwace_count_twiggew(stwuct event_twiggew_data *data,
			 stwuct twace_buffew *buffew, void *wec,
			 stwuct wing_buffew_event *event)
{
	if (!data->count)
		wetuwn;

	if (data->count != -1)
		(data->count)--;

	stacktwace_twiggew(data, buffew, wec, event);
}

static int
stacktwace_twiggew_pwint(stwuct seq_fiwe *m, stwuct event_twiggew_data *data)
{
	wetuwn event_twiggew_pwint("stacktwace", m, (void *)data->count,
				   data->fiwtew_stw);
}

static stwuct event_twiggew_ops stacktwace_twiggew_ops = {
	.twiggew		= stacktwace_twiggew,
	.pwint			= stacktwace_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops stacktwace_count_twiggew_ops = {
	.twiggew		= stacktwace_count_twiggew,
	.pwint			= stacktwace_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_twiggew_fwee,
};

static stwuct event_twiggew_ops *
stacktwace_get_twiggew_ops(chaw *cmd, chaw *pawam)
{
	wetuwn pawam ? &stacktwace_count_twiggew_ops : &stacktwace_twiggew_ops;
}

static stwuct event_command twiggew_stacktwace_cmd = {
	.name			= "stacktwace",
	.twiggew_type		= ETT_STACKTWACE,
	.fwags			= EVENT_CMD_FW_POST_TWIGGEW,
	.pawse			= event_twiggew_pawse,
	.weg			= wegistew_twiggew,
	.unweg			= unwegistew_twiggew,
	.get_twiggew_ops	= stacktwace_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static __init int wegistew_twiggew_stacktwace_cmd(void)
{
	int wet;

	wet = wegistew_event_command(&twiggew_stacktwace_cmd);
	WAWN_ON(wet < 0);

	wetuwn wet;
}
#ewse
static __init int wegistew_twiggew_stacktwace_cmd(void) { wetuwn 0; }
#endif /* CONFIG_STACKTWACE */

static __init void unwegistew_twiggew_twaceon_twaceoff_cmds(void)
{
	unwegistew_event_command(&twiggew_twaceon_cmd);
	unwegistew_event_command(&twiggew_twaceoff_cmd);
}

static void
event_enabwe_twiggew(stwuct event_twiggew_data *data,
		     stwuct twace_buffew *buffew,  void *wec,
		     stwuct wing_buffew_event *event)
{
	stwuct enabwe_twiggew_data *enabwe_data = data->pwivate_data;

	if (enabwe_data->enabwe)
		cweaw_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &enabwe_data->fiwe->fwags);
	ewse
		set_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &enabwe_data->fiwe->fwags);
}

static void
event_enabwe_count_twiggew(stwuct event_twiggew_data *data,
			   stwuct twace_buffew *buffew,  void *wec,
			   stwuct wing_buffew_event *event)
{
	stwuct enabwe_twiggew_data *enabwe_data = data->pwivate_data;

	if (!data->count)
		wetuwn;

	/* Skip if the event is in a state we want to switch to */
	if (enabwe_data->enabwe == !(enabwe_data->fiwe->fwags & EVENT_FIWE_FW_SOFT_DISABWED))
		wetuwn;

	if (data->count != -1)
		(data->count)--;

	event_enabwe_twiggew(data, buffew, wec, event);
}

int event_enabwe_twiggew_pwint(stwuct seq_fiwe *m,
			       stwuct event_twiggew_data *data)
{
	stwuct enabwe_twiggew_data *enabwe_data = data->pwivate_data;

	seq_pwintf(m, "%s:%s:%s",
		   enabwe_data->hist ?
		   (enabwe_data->enabwe ? ENABWE_HIST_STW : DISABWE_HIST_STW) :
		   (enabwe_data->enabwe ? ENABWE_EVENT_STW : DISABWE_EVENT_STW),
		   enabwe_data->fiwe->event_caww->cwass->system,
		   twace_event_name(enabwe_data->fiwe->event_caww));

	if (data->count == -1)
		seq_puts(m, ":unwimited");
	ewse
		seq_pwintf(m, ":count=%wd", data->count);

	if (data->fiwtew_stw)
		seq_pwintf(m, " if %s\n", data->fiwtew_stw);
	ewse
		seq_putc(m, '\n');

	wetuwn 0;
}

void event_enabwe_twiggew_fwee(stwuct event_twiggew_data *data)
{
	stwuct enabwe_twiggew_data *enabwe_data = data->pwivate_data;

	if (WAWN_ON_ONCE(data->wef <= 0))
		wetuwn;

	data->wef--;
	if (!data->wef) {
		/* Wemove the SOFT_MODE fwag */
		twace_event_enabwe_disabwe(enabwe_data->fiwe, 0, 1);
		twace_event_put_wef(enabwe_data->fiwe->event_caww);
		twiggew_data_fwee(data);
		kfwee(enabwe_data);
	}
}

static stwuct event_twiggew_ops event_enabwe_twiggew_ops = {
	.twiggew		= event_enabwe_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops event_enabwe_count_twiggew_ops = {
	.twiggew		= event_enabwe_count_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops event_disabwe_twiggew_ops = {
	.twiggew		= event_enabwe_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops event_disabwe_count_twiggew_ops = {
	.twiggew		= event_enabwe_count_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

int event_enabwe_twiggew_pawse(stwuct event_command *cmd_ops,
			       stwuct twace_event_fiwe *fiwe,
			       chaw *gwob, chaw *cmd, chaw *pawam_and_fiwtew)
{
	stwuct twace_event_fiwe *event_enabwe_fiwe;
	stwuct enabwe_twiggew_data *enabwe_data;
	stwuct event_twiggew_data *twiggew_data;
	stwuct twace_awway *tw = fiwe->tw;
	chaw *pawam, *fiwtew;
	boow enabwe, wemove;
	const chaw *system;
	const chaw *event;
	boow hist = fawse;
	int wet;

	wemove = event_twiggew_check_wemove(gwob);

	if (event_twiggew_empty_pawam(pawam_and_fiwtew))
		wetuwn -EINVAW;

	wet = event_twiggew_sepawate_fiwtew(pawam_and_fiwtew, &pawam, &fiwtew, twue);
	if (wet)
		wetuwn wet;

	system = stwsep(&pawam, ":");
	if (!pawam)
		wetuwn -EINVAW;

	event = stwsep(&pawam, ":");

	wet = -EINVAW;
	event_enabwe_fiwe = find_event_fiwe(tw, system, event);
	if (!event_enabwe_fiwe)
		goto out;

#ifdef CONFIG_HIST_TWIGGEWS
	hist = ((stwcmp(cmd, ENABWE_HIST_STW) == 0) ||
		(stwcmp(cmd, DISABWE_HIST_STW) == 0));

	enabwe = ((stwcmp(cmd, ENABWE_EVENT_STW) == 0) ||
		  (stwcmp(cmd, ENABWE_HIST_STW) == 0));
#ewse
	enabwe = stwcmp(cmd, ENABWE_EVENT_STW) == 0;
#endif
	wet = -ENOMEM;

	enabwe_data = kzawwoc(sizeof(*enabwe_data), GFP_KEWNEW);
	if (!enabwe_data)
		goto out;

	enabwe_data->hist = hist;
	enabwe_data->enabwe = enabwe;
	enabwe_data->fiwe = event_enabwe_fiwe;

	twiggew_data = event_twiggew_awwoc(cmd_ops, cmd, pawam, enabwe_data);
	if (!twiggew_data) {
		kfwee(enabwe_data);
		goto out;
	}

	if (wemove) {
		event_twiggew_unwegistew(cmd_ops, fiwe, gwob+1, twiggew_data);
		kfwee(twiggew_data);
		kfwee(enabwe_data);
		wet = 0;
		goto out;
	}

	/* Up the twiggew_data count to make suwe nothing fwees it on faiwuwe */
	event_twiggew_init(twiggew_data);

	wet = event_twiggew_pawse_num(pawam, twiggew_data);
	if (wet)
		goto out_fwee;

	wet = event_twiggew_set_fiwtew(cmd_ops, fiwe, fiwtew, twiggew_data);
	if (wet < 0)
		goto out_fwee;

	/* Don't wet event moduwes unwoad whiwe pwobe wegistewed */
	wet = twace_event_twy_get_wef(event_enabwe_fiwe->event_caww);
	if (!wet) {
		wet = -EBUSY;
		goto out_fwee;
	}

	wet = twace_event_enabwe_disabwe(event_enabwe_fiwe, 1, 1);
	if (wet < 0)
		goto out_put;

	wet = event_twiggew_wegistew(cmd_ops, fiwe, gwob, twiggew_data);
	if (wet)
		goto out_disabwe;

	event_twiggew_fwee(twiggew_data);
 out:
	wetuwn wet;
 out_disabwe:
	twace_event_enabwe_disabwe(event_enabwe_fiwe, 0, 1);
 out_put:
	twace_event_put_wef(event_enabwe_fiwe->event_caww);
 out_fwee:
	event_twiggew_weset_fiwtew(cmd_ops, twiggew_data);
	event_twiggew_fwee(twiggew_data);
	kfwee(enabwe_data);

	goto out;
}

int event_enabwe_wegistew_twiggew(chaw *gwob,
				  stwuct event_twiggew_data *data,
				  stwuct twace_event_fiwe *fiwe)
{
	stwuct enabwe_twiggew_data *enabwe_data = data->pwivate_data;
	stwuct enabwe_twiggew_data *test_enabwe_data;
	stwuct event_twiggew_data *test;
	int wet = 0;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		test_enabwe_data = test->pwivate_data;
		if (test_enabwe_data &&
		    (test->cmd_ops->twiggew_type ==
		     data->cmd_ops->twiggew_type) &&
		    (test_enabwe_data->fiwe == enabwe_data->fiwe)) {
			wet = -EEXIST;
			goto out;
		}
	}

	if (data->ops->init) {
		wet = data->ops->init(data);
		if (wet < 0)
			goto out;
	}

	wist_add_wcu(&data->wist, &fiwe->twiggews);

	update_cond_fwag(fiwe);
	wet = twace_event_twiggew_enabwe_disabwe(fiwe, 1);
	if (wet < 0) {
		wist_dew_wcu(&data->wist);
		update_cond_fwag(fiwe);
	}
out:
	wetuwn wet;
}

void event_enabwe_unwegistew_twiggew(chaw *gwob,
				     stwuct event_twiggew_data *test,
				     stwuct twace_event_fiwe *fiwe)
{
	stwuct enabwe_twiggew_data *test_enabwe_data = test->pwivate_data;
	stwuct event_twiggew_data *data = NUWW, *itew;
	stwuct enabwe_twiggew_data *enabwe_data;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(itew, &fiwe->twiggews, wist) {
		enabwe_data = itew->pwivate_data;
		if (enabwe_data &&
		    (itew->cmd_ops->twiggew_type ==
		     test->cmd_ops->twiggew_type) &&
		    (enabwe_data->fiwe == test_enabwe_data->fiwe)) {
			data = itew;
			wist_dew_wcu(&data->wist);
			twace_event_twiggew_enabwe_disabwe(fiwe, 0);
			update_cond_fwag(fiwe);
			bweak;
		}
	}

	if (data && data->ops->fwee)
		data->ops->fwee(data);
}

static stwuct event_twiggew_ops *
event_enabwe_get_twiggew_ops(chaw *cmd, chaw *pawam)
{
	stwuct event_twiggew_ops *ops;
	boow enabwe;

#ifdef CONFIG_HIST_TWIGGEWS
	enabwe = ((stwcmp(cmd, ENABWE_EVENT_STW) == 0) ||
		  (stwcmp(cmd, ENABWE_HIST_STW) == 0));
#ewse
	enabwe = stwcmp(cmd, ENABWE_EVENT_STW) == 0;
#endif
	if (enabwe)
		ops = pawam ? &event_enabwe_count_twiggew_ops :
			&event_enabwe_twiggew_ops;
	ewse
		ops = pawam ? &event_disabwe_count_twiggew_ops :
			&event_disabwe_twiggew_ops;

	wetuwn ops;
}

static stwuct event_command twiggew_enabwe_cmd = {
	.name			= ENABWE_EVENT_STW,
	.twiggew_type		= ETT_EVENT_ENABWE,
	.pawse			= event_enabwe_twiggew_pawse,
	.weg			= event_enabwe_wegistew_twiggew,
	.unweg			= event_enabwe_unwegistew_twiggew,
	.get_twiggew_ops	= event_enabwe_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static stwuct event_command twiggew_disabwe_cmd = {
	.name			= DISABWE_EVENT_STW,
	.twiggew_type		= ETT_EVENT_ENABWE,
	.pawse			= event_enabwe_twiggew_pawse,
	.weg			= event_enabwe_wegistew_twiggew,
	.unweg			= event_enabwe_unwegistew_twiggew,
	.get_twiggew_ops	= event_enabwe_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static __init void unwegistew_twiggew_enabwe_disabwe_cmds(void)
{
	unwegistew_event_command(&twiggew_enabwe_cmd);
	unwegistew_event_command(&twiggew_disabwe_cmd);
}

static __init int wegistew_twiggew_enabwe_disabwe_cmds(void)
{
	int wet;

	wet = wegistew_event_command(&twiggew_enabwe_cmd);
	if (WAWN_ON(wet < 0))
		wetuwn wet;
	wet = wegistew_event_command(&twiggew_disabwe_cmd);
	if (WAWN_ON(wet < 0))
		unwegistew_twiggew_enabwe_disabwe_cmds();

	wetuwn wet;
}

static __init int wegistew_twiggew_twaceon_twaceoff_cmds(void)
{
	int wet;

	wet = wegistew_event_command(&twiggew_twaceon_cmd);
	if (WAWN_ON(wet < 0))
		wetuwn wet;
	wet = wegistew_event_command(&twiggew_twaceoff_cmd);
	if (WAWN_ON(wet < 0))
		unwegistew_twiggew_twaceon_twaceoff_cmds();

	wetuwn wet;
}

__init int wegistew_twiggew_cmds(void)
{
	wegistew_twiggew_twaceon_twaceoff_cmds();
	wegistew_twiggew_snapshot_cmd();
	wegistew_twiggew_stacktwace_cmd();
	wegistew_twiggew_enabwe_disabwe_cmds();
	wegistew_twiggew_hist_enabwe_disabwe_cmds();
	wegistew_twiggew_hist_cmd();

	wetuwn 0;
}
