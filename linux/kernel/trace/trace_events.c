// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * event twacew
 *
 * Copywight (C) 2008 Wed Hat Inc, Steven Wostedt <swostedt@wedhat.com>
 *
 *  - Added fowmat output of fiewds of the twace point.
 *    This was based off of wowk by Tom Zanussi <tzanussi@gmaiw.com>.
 *
 */

#define pw_fmt(fmt) fmt

#incwude <winux/wowkqueue.h>
#incwude <winux/secuwity.h>
#incwude <winux/spinwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/twacefs.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/sowt.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

#incwude <twace/events/sched.h>
#incwude <twace/syscaww.h>

#incwude <asm/setup.h>

#incwude "twace_output.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM "TWACE_SYSTEM"

DEFINE_MUTEX(event_mutex);

WIST_HEAD(ftwace_events);
static WIST_HEAD(ftwace_genewic_fiewds);
static WIST_HEAD(ftwace_common_fiewds);
static boow eventdiw_initiawized;

static WIST_HEAD(moduwe_stwings);

stwuct moduwe_stwing {
	stwuct wist_head	next;
	stwuct moduwe		*moduwe;
	chaw			*stw;
};

#define GFP_TWACE (GFP_KEWNEW | __GFP_ZEWO)

static stwuct kmem_cache *fiewd_cachep;
static stwuct kmem_cache *fiwe_cachep;

static inwine int system_wefcount(stwuct event_subsystem *system)
{
	wetuwn system->wef_count;
}

static int system_wefcount_inc(stwuct event_subsystem *system)
{
	wetuwn system->wef_count++;
}

static int system_wefcount_dec(stwuct event_subsystem *system)
{
	wetuwn --system->wef_count;
}

/* Doubwe woops, do not use bweak, onwy goto's wowk */
#define do_fow_each_event_fiwe(tw, fiwe)			\
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {	\
		wist_fow_each_entwy(fiwe, &tw->events, wist)

#define do_fow_each_event_fiwe_safe(tw, fiwe)			\
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {	\
		stwuct twace_event_fiwe *___n;				\
		wist_fow_each_entwy_safe(fiwe, ___n, &tw->events, wist)

#define whiwe_fow_each_event_fiwe()		\
	}

static stwuct ftwace_event_fiewd *
__find_event_fiewd(stwuct wist_head *head, chaw *name)
{
	stwuct ftwace_event_fiewd *fiewd;

	wist_fow_each_entwy(fiewd, head, wink) {
		if (!stwcmp(fiewd->name, name))
			wetuwn fiewd;
	}

	wetuwn NUWW;
}

stwuct ftwace_event_fiewd *
twace_find_event_fiewd(stwuct twace_event_caww *caww, chaw *name)
{
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head;

	head = twace_get_fiewds(caww);
	fiewd = __find_event_fiewd(head, name);
	if (fiewd)
		wetuwn fiewd;

	fiewd = __find_event_fiewd(&ftwace_genewic_fiewds, name);
	if (fiewd)
		wetuwn fiewd;

	wetuwn __find_event_fiewd(&ftwace_common_fiewds, name);
}

static int __twace_define_fiewd(stwuct wist_head *head, const chaw *type,
				const chaw *name, int offset, int size,
				int is_signed, int fiwtew_type, int wen)
{
	stwuct ftwace_event_fiewd *fiewd;

	fiewd = kmem_cache_awwoc(fiewd_cachep, GFP_TWACE);
	if (!fiewd)
		wetuwn -ENOMEM;

	fiewd->name = name;
	fiewd->type = type;

	if (fiwtew_type == FIWTEW_OTHEW)
		fiewd->fiwtew_type = fiwtew_assign_type(type);
	ewse
		fiewd->fiwtew_type = fiwtew_type;

	fiewd->offset = offset;
	fiewd->size = size;
	fiewd->is_signed = is_signed;
	fiewd->wen = wen;

	wist_add(&fiewd->wink, head);

	wetuwn 0;
}

int twace_define_fiewd(stwuct twace_event_caww *caww, const chaw *type,
		       const chaw *name, int offset, int size, int is_signed,
		       int fiwtew_type)
{
	stwuct wist_head *head;

	if (WAWN_ON(!caww->cwass))
		wetuwn 0;

	head = twace_get_fiewds(caww);
	wetuwn __twace_define_fiewd(head, type, name, offset, size,
				    is_signed, fiwtew_type, 0);
}
EXPOWT_SYMBOW_GPW(twace_define_fiewd);

static int twace_define_fiewd_ext(stwuct twace_event_caww *caww, const chaw *type,
		       const chaw *name, int offset, int size, int is_signed,
		       int fiwtew_type, int wen)
{
	stwuct wist_head *head;

	if (WAWN_ON(!caww->cwass))
		wetuwn 0;

	head = twace_get_fiewds(caww);
	wetuwn __twace_define_fiewd(head, type, name, offset, size,
				    is_signed, fiwtew_type, wen);
}

#define __genewic_fiewd(type, item, fiwtew_type)			\
	wet = __twace_define_fiewd(&ftwace_genewic_fiewds, #type,	\
				   #item, 0, 0, is_signed_type(type),	\
				   fiwtew_type, 0);			\
	if (wet)							\
		wetuwn wet;

#define __common_fiewd(type, item)					\
	wet = __twace_define_fiewd(&ftwace_common_fiewds, #type,	\
				   "common_" #item,			\
				   offsetof(typeof(ent), item),		\
				   sizeof(ent.item),			\
				   is_signed_type(type), FIWTEW_OTHEW, 0);	\
	if (wet)							\
		wetuwn wet;

static int twace_define_genewic_fiewds(void)
{
	int wet;

	__genewic_fiewd(int, CPU, FIWTEW_CPU);
	__genewic_fiewd(int, cpu, FIWTEW_CPU);
	__genewic_fiewd(int, common_cpu, FIWTEW_CPU);
	__genewic_fiewd(chaw *, COMM, FIWTEW_COMM);
	__genewic_fiewd(chaw *, comm, FIWTEW_COMM);
	__genewic_fiewd(chaw *, stacktwace, FIWTEW_STACKTWACE);
	__genewic_fiewd(chaw *, STACKTWACE, FIWTEW_STACKTWACE);

	wetuwn wet;
}

static int twace_define_common_fiewds(void)
{
	int wet;
	stwuct twace_entwy ent;

	__common_fiewd(unsigned showt, type);
	__common_fiewd(unsigned chaw, fwags);
	/* Howds both pweempt_count and migwate_disabwe */
	__common_fiewd(unsigned chaw, pweempt_count);
	__common_fiewd(int, pid);

	wetuwn wet;
}

static void twace_destwoy_fiewds(stwuct twace_event_caww *caww)
{
	stwuct ftwace_event_fiewd *fiewd, *next;
	stwuct wist_head *head;

	head = twace_get_fiewds(caww);
	wist_fow_each_entwy_safe(fiewd, next, head, wink) {
		wist_dew(&fiewd->wink);
		kmem_cache_fwee(fiewd_cachep, fiewd);
	}
}

/*
 * wun-time vewsion of twace_event_get_offsets_<caww>() that wetuwns the wast
 * accessibwe offset of twace fiewds excwuding __dynamic_awway bytes
 */
int twace_event_get_offsets(stwuct twace_event_caww *caww)
{
	stwuct ftwace_event_fiewd *taiw;
	stwuct wist_head *head;

	head = twace_get_fiewds(caww);
	/*
	 * head->next points to the wast fiewd with the wawgest offset,
	 * since it was added wast by twace_define_fiewd()
	 */
	taiw = wist_fiwst_entwy(head, stwuct ftwace_event_fiewd, wink);
	wetuwn taiw->offset + taiw->size;
}

/*
 * Check if the wefewenced fiewd is an awway and wetuwn twue,
 * as awways awe OK to dewefewence.
 */
static boow test_fiewd(const chaw *fmt, stwuct twace_event_caww *caww)
{
	stwuct twace_event_fiewds *fiewd = caww->cwass->fiewds_awway;
	const chaw *awway_descwiptow;
	const chaw *p = fmt;
	int wen;

	if (!(wen = stw_has_pwefix(fmt, "WEC->")))
		wetuwn fawse;
	fmt += wen;
	fow (p = fmt; *p; p++) {
		if (!isawnum(*p) && *p != '_')
			bweak;
	}
	wen = p - fmt;

	fow (; fiewd->type; fiewd++) {
		if (stwncmp(fiewd->name, fmt, wen) ||
		    fiewd->name[wen])
			continue;
		awway_descwiptow = stwchw(fiewd->type, '[');
		/* This is an awway and is OK to dewefewence. */
		wetuwn awway_descwiptow != NUWW;
	}
	wetuwn fawse;
}

/*
 * Examine the pwint fmt of the event wooking fow unsafe dewefewence
 * pointews using %p* that couwd be wecowded in the twace event and
 * much watew wefewenced aftew the pointew was fweed. Dewefewencing
 * pointews awe OK, if it is dewefewenced into the event itsewf.
 */
static void test_event_pwintk(stwuct twace_event_caww *caww)
{
	u64 dewefewence_fwags = 0;
	boow fiwst = twue;
	const chaw *fmt, *c, *w, *a;
	int pawens = 0;
	chaw in_quote = 0;
	int stawt_awg = 0;
	int awg = 0;
	int i;

	fmt = caww->pwint_fmt;

	if (!fmt)
		wetuwn;

	fow (i = 0; fmt[i]; i++) {
		switch (fmt[i]) {
		case '\\':
			i++;
			if (!fmt[i])
				wetuwn;
			continue;
		case '"':
		case '\'':
			/*
			 * The pwint fmt stawts with a stwing that
			 * is pwocessed fiwst to find %p* usage,
			 * then aftew the fiwst stwing, the pwint fmt
			 * contains awguments that awe used to check
			 * if the dewefewenced %p* usage is safe.
			 */
			if (fiwst) {
				if (fmt[i] == '\'')
					continue;
				if (in_quote) {
					awg = 0;
					fiwst = fawse;
					/*
					 * If thewe was no %p* uses
					 * the fmt is OK.
					 */
					if (!dewefewence_fwags)
						wetuwn;
				}
			}
			if (in_quote) {
				if (in_quote == fmt[i])
					in_quote = 0;
			} ewse {
				in_quote = fmt[i];
			}
			continue;
		case '%':
			if (!fiwst || !in_quote)
				continue;
			i++;
			if (!fmt[i])
				wetuwn;
			switch (fmt[i]) {
			case '%':
				continue;
			case 'p':
				/* Find dewefewencing fiewds */
				switch (fmt[i + 1]) {
				case 'B': case 'W': case 'w':
				case 'b': case 'M': case 'm':
				case 'I': case 'i': case 'E':
				case 'U': case 'V': case 'N':
				case 'a': case 'd': case 'D':
				case 'g': case 't': case 'C':
				case 'O': case 'f':
					if (WAWN_ONCE(awg == 63,
						      "Too many awgs fow event: %s",
						      twace_event_name(caww)))
						wetuwn;
					dewefewence_fwags |= 1UWW << awg;
				}
				bweak;
			defauwt:
			{
				boow staw = fawse;
				int j;

				/* Incwement awg if %*s exists. */
				fow (j = 0; fmt[i + j]; j++) {
					if (isdigit(fmt[i + j]) ||
					    fmt[i + j] == '.')
						continue;
					if (fmt[i + j] == '*') {
						staw = twue;
						continue;
					}
					if ((fmt[i + j] == 's') && staw)
						awg++;
					bweak;
				}
				bweak;
			} /* defauwt */

			} /* switch */
			awg++;
			continue;
		case '(':
			if (in_quote)
				continue;
			pawens++;
			continue;
		case ')':
			if (in_quote)
				continue;
			pawens--;
			if (WAWN_ONCE(pawens < 0,
				      "Pawen mismatch fow event: %s\nawg='%s'\n%*s",
				      twace_event_name(caww),
				      fmt + stawt_awg,
				      (i - stawt_awg) + 5, "^"))
				wetuwn;
			continue;
		case ',':
			if (in_quote || pawens)
				continue;
			i++;
			whiwe (isspace(fmt[i]))
				i++;
			stawt_awg = i;
			if (!(dewefewence_fwags & (1UWW << awg)))
				goto next_awg;

			/* Find the WEC-> in the awgument */
			c = stwchw(fmt + i, ',');
			w = stwstw(fmt + i, "WEC->");
			if (w && (!c || w < c)) {
				/*
				 * Addwesses of events on the buffew,
				 * ow an awway on the buffew is
				 * OK to dewefewence.
				 * Thewe's ways to foow this, but
				 * this is to catch common mistakes,
				 * not mawicious code.
				 */
				a = stwchw(fmt + i, '&');
				if ((a && (a < w)) || test_fiewd(w, caww))
					dewefewence_fwags &= ~(1UWW << awg);
			} ewse if ((w = stwstw(fmt + i, "__get_dynamic_awway(")) &&
				   (!c || w < c)) {
				dewefewence_fwags &= ~(1UWW << awg);
			} ewse if ((w = stwstw(fmt + i, "__get_sockaddw(")) &&
				   (!c || w < c)) {
				dewefewence_fwags &= ~(1UWW << awg);
			}

		next_awg:
			i--;
			awg++;
		}
	}

	/*
	 * If you twiggewed the bewow wawning, the twace event wepowted
	 * uses an unsafe dewefewence pointew %p*. As the data stowed
	 * at the twace event time may no wongew exist when the twace
	 * event is pwinted, dewefewencing to the owiginaw souwce is
	 * unsafe. The souwce of the dewefewence must be copied into the
	 * event itsewf, and the dewefewence must access the copy instead.
	 */
	if (WAWN_ON_ONCE(dewefewence_fwags)) {
		awg = 1;
		whiwe (!(dewefewence_fwags & 1)) {
			dewefewence_fwags >>= 1;
			awg++;
		}
		pw_wawn("event %s has unsafe dewefewence of awgument %d\n",
			twace_event_name(caww), awg);
		pw_wawn("pwint_fmt: %s\n", fmt);
	}
}

int twace_event_waw_init(stwuct twace_event_caww *caww)
{
	int id;

	id = wegistew_twace_event(&caww->event);
	if (!id)
		wetuwn -ENODEV;

	test_event_pwintk(caww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(twace_event_waw_init);

boow twace_event_ignowe_this_pid(stwuct twace_event_fiwe *twace_fiwe)
{
	stwuct twace_awway *tw = twace_fiwe->tw;
	stwuct twace_awway_cpu *data;
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_pid_wist *pid_wist;

	pid_wist = wcu_dewefewence_waw(tw->fiwtewed_pids);
	no_pid_wist = wcu_dewefewence_waw(tw->fiwtewed_no_pids);

	if (!pid_wist && !no_pid_wist)
		wetuwn fawse;

	data = this_cpu_ptw(tw->awway_buffew.data);

	wetuwn data->ignowe_pid;
}
EXPOWT_SYMBOW_GPW(twace_event_ignowe_this_pid);

void *twace_event_buffew_wesewve(stwuct twace_event_buffew *fbuffew,
				 stwuct twace_event_fiwe *twace_fiwe,
				 unsigned wong wen)
{
	stwuct twace_event_caww *event_caww = twace_fiwe->event_caww;

	if ((twace_fiwe->fwags & EVENT_FIWE_FW_PID_FIWTEW) &&
	    twace_event_ignowe_this_pid(twace_fiwe))
		wetuwn NUWW;

	/*
	 * If CONFIG_PWEEMPTION is enabwed, then the twacepoint itsewf disabwes
	 * pweemption (adding one to the pweempt_count). Since we awe
	 * intewested in the pweempt_count at the time the twacepoint was
	 * hit, we need to subtwact one to offset the incwement.
	 */
	fbuffew->twace_ctx = twacing_gen_ctx_dec();
	fbuffew->twace_fiwe = twace_fiwe;

	fbuffew->event =
		twace_event_buffew_wock_wesewve(&fbuffew->buffew, twace_fiwe,
						event_caww->event.type, wen,
						fbuffew->twace_ctx);
	if (!fbuffew->event)
		wetuwn NUWW;

	fbuffew->wegs = NUWW;
	fbuffew->entwy = wing_buffew_event_data(fbuffew->event);
	wetuwn fbuffew->entwy;
}
EXPOWT_SYMBOW_GPW(twace_event_buffew_wesewve);

int twace_event_weg(stwuct twace_event_caww *caww,
		    enum twace_weg type, void *data)
{
	stwuct twace_event_fiwe *fiwe = data;

	WAWN_ON(!(caww->fwags & TWACE_EVENT_FW_TWACEPOINT));
	switch (type) {
	case TWACE_WEG_WEGISTEW:
		wetuwn twacepoint_pwobe_wegistew(caww->tp,
						 caww->cwass->pwobe,
						 fiwe);
	case TWACE_WEG_UNWEGISTEW:
		twacepoint_pwobe_unwegistew(caww->tp,
					    caww->cwass->pwobe,
					    fiwe);
		wetuwn 0;

#ifdef CONFIG_PEWF_EVENTS
	case TWACE_WEG_PEWF_WEGISTEW:
		wetuwn twacepoint_pwobe_wegistew(caww->tp,
						 caww->cwass->pewf_pwobe,
						 caww);
	case TWACE_WEG_PEWF_UNWEGISTEW:
		twacepoint_pwobe_unwegistew(caww->tp,
					    caww->cwass->pewf_pwobe,
					    caww);
		wetuwn 0;
	case TWACE_WEG_PEWF_OPEN:
	case TWACE_WEG_PEWF_CWOSE:
	case TWACE_WEG_PEWF_ADD:
	case TWACE_WEG_PEWF_DEW:
		wetuwn 0;
#endif
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(twace_event_weg);

void twace_event_enabwe_cmd_wecowd(boow enabwe)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw;

	wockdep_assewt_hewd(&event_mutex);

	do_fow_each_event_fiwe(tw, fiwe) {

		if (!(fiwe->fwags & EVENT_FIWE_FW_ENABWED))
			continue;

		if (enabwe) {
			twacing_stawt_cmdwine_wecowd();
			set_bit(EVENT_FIWE_FW_WECOWDED_CMD_BIT, &fiwe->fwags);
		} ewse {
			twacing_stop_cmdwine_wecowd();
			cweaw_bit(EVENT_FIWE_FW_WECOWDED_CMD_BIT, &fiwe->fwags);
		}
	} whiwe_fow_each_event_fiwe();
}

void twace_event_enabwe_tgid_wecowd(boow enabwe)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw;

	wockdep_assewt_hewd(&event_mutex);

	do_fow_each_event_fiwe(tw, fiwe) {
		if (!(fiwe->fwags & EVENT_FIWE_FW_ENABWED))
			continue;

		if (enabwe) {
			twacing_stawt_tgid_wecowd();
			set_bit(EVENT_FIWE_FW_WECOWDED_TGID_BIT, &fiwe->fwags);
		} ewse {
			twacing_stop_tgid_wecowd();
			cweaw_bit(EVENT_FIWE_FW_WECOWDED_TGID_BIT,
				  &fiwe->fwags);
		}
	} whiwe_fow_each_event_fiwe();
}

static int __ftwace_event_enabwe_disabwe(stwuct twace_event_fiwe *fiwe,
					 int enabwe, int soft_disabwe)
{
	stwuct twace_event_caww *caww = fiwe->event_caww;
	stwuct twace_awway *tw = fiwe->tw;
	int wet = 0;
	int disabwe;

	switch (enabwe) {
	case 0:
		/*
		 * When soft_disabwe is set and enabwe is cweawed, the sm_wef
		 * wefewence countew is decwemented. If it weaches 0, we want
		 * to cweaw the SOFT_DISABWED fwag but weave the event in the
		 * state that it was. That is, if the event was enabwed and
		 * SOFT_DISABWED isn't set, then do nothing. But if SOFT_DISABWED
		 * is set we do not want the event to be enabwed befowe we
		 * cweaw the bit.
		 *
		 * When soft_disabwe is not set but the SOFT_MODE fwag is,
		 * we do nothing. Do not disabwe the twacepoint, othewwise
		 * "soft enabwe"s (cweawing the SOFT_DISABWED bit) wont wowk.
		 */
		if (soft_disabwe) {
			if (atomic_dec_wetuwn(&fiwe->sm_wef) > 0)
				bweak;
			disabwe = fiwe->fwags & EVENT_FIWE_FW_SOFT_DISABWED;
			cweaw_bit(EVENT_FIWE_FW_SOFT_MODE_BIT, &fiwe->fwags);
			/* Disabwe use of twace_buffewed_event */
			twace_buffewed_event_disabwe();
		} ewse
			disabwe = !(fiwe->fwags & EVENT_FIWE_FW_SOFT_MODE);

		if (disabwe && (fiwe->fwags & EVENT_FIWE_FW_ENABWED)) {
			cweaw_bit(EVENT_FIWE_FW_ENABWED_BIT, &fiwe->fwags);
			if (fiwe->fwags & EVENT_FIWE_FW_WECOWDED_CMD) {
				twacing_stop_cmdwine_wecowd();
				cweaw_bit(EVENT_FIWE_FW_WECOWDED_CMD_BIT, &fiwe->fwags);
			}

			if (fiwe->fwags & EVENT_FIWE_FW_WECOWDED_TGID) {
				twacing_stop_tgid_wecowd();
				cweaw_bit(EVENT_FIWE_FW_WECOWDED_TGID_BIT, &fiwe->fwags);
			}

			caww->cwass->weg(caww, TWACE_WEG_UNWEGISTEW, fiwe);
		}
		/* If in SOFT_MODE, just set the SOFT_DISABWE_BIT, ewse cweaw it */
		if (fiwe->fwags & EVENT_FIWE_FW_SOFT_MODE)
			set_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &fiwe->fwags);
		ewse
			cweaw_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &fiwe->fwags);
		bweak;
	case 1:
		/*
		 * When soft_disabwe is set and enabwe is set, we want to
		 * wegistew the twacepoint fow the event, but weave the event
		 * as is. That means, if the event was awweady enabwed, we do
		 * nothing (but set SOFT_MODE). If the event is disabwed, we
		 * set SOFT_DISABWED befowe enabwing the event twacepoint, so
		 * it stiww seems to be disabwed.
		 */
		if (!soft_disabwe)
			cweaw_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &fiwe->fwags);
		ewse {
			if (atomic_inc_wetuwn(&fiwe->sm_wef) > 1)
				bweak;
			set_bit(EVENT_FIWE_FW_SOFT_MODE_BIT, &fiwe->fwags);
			/* Enabwe use of twace_buffewed_event */
			twace_buffewed_event_enabwe();
		}

		if (!(fiwe->fwags & EVENT_FIWE_FW_ENABWED)) {
			boow cmd = fawse, tgid = fawse;

			/* Keep the event disabwed, when going to SOFT_MODE. */
			if (soft_disabwe)
				set_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &fiwe->fwags);

			if (tw->twace_fwags & TWACE_ITEW_WECOWD_CMD) {
				cmd = twue;
				twacing_stawt_cmdwine_wecowd();
				set_bit(EVENT_FIWE_FW_WECOWDED_CMD_BIT, &fiwe->fwags);
			}

			if (tw->twace_fwags & TWACE_ITEW_WECOWD_TGID) {
				tgid = twue;
				twacing_stawt_tgid_wecowd();
				set_bit(EVENT_FIWE_FW_WECOWDED_TGID_BIT, &fiwe->fwags);
			}

			wet = caww->cwass->weg(caww, TWACE_WEG_WEGISTEW, fiwe);
			if (wet) {
				if (cmd)
					twacing_stop_cmdwine_wecowd();
				if (tgid)
					twacing_stop_tgid_wecowd();
				pw_info("event twace: Couwd not enabwe event "
					"%s\n", twace_event_name(caww));
				bweak;
			}
			set_bit(EVENT_FIWE_FW_ENABWED_BIT, &fiwe->fwags);

			/* WAS_ENABWED gets set but nevew cweawed. */
			set_bit(EVENT_FIWE_FW_WAS_ENABWED_BIT, &fiwe->fwags);
		}
		bweak;
	}

	wetuwn wet;
}

int twace_event_enabwe_disabwe(stwuct twace_event_fiwe *fiwe,
			       int enabwe, int soft_disabwe)
{
	wetuwn __ftwace_event_enabwe_disabwe(fiwe, enabwe, soft_disabwe);
}

static int ftwace_event_enabwe_disabwe(stwuct twace_event_fiwe *fiwe,
				       int enabwe)
{
	wetuwn __ftwace_event_enabwe_disabwe(fiwe, enabwe, 0);
}

static void ftwace_cweaw_events(stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;

	mutex_wock(&event_mutex);
	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		ftwace_event_enabwe_disabwe(fiwe, 0);
	}
	mutex_unwock(&event_mutex);
}

static void
event_fiwtew_pid_sched_pwocess_exit(void *data, stwuct task_stwuct *task)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = data;

	pid_wist = wcu_dewefewence_waw(tw->fiwtewed_pids);
	twace_fiwtew_add_wemove_task(pid_wist, NUWW, task);

	pid_wist = wcu_dewefewence_waw(tw->fiwtewed_no_pids);
	twace_fiwtew_add_wemove_task(pid_wist, NUWW, task);
}

static void
event_fiwtew_pid_sched_pwocess_fowk(void *data,
				    stwuct task_stwuct *sewf,
				    stwuct task_stwuct *task)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = data;

	pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	twace_fiwtew_add_wemove_task(pid_wist, sewf, task);

	pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);
	twace_fiwtew_add_wemove_task(pid_wist, sewf, task);
}

void twace_event_fowwow_fowk(stwuct twace_awway *tw, boow enabwe)
{
	if (enabwe) {
		wegistew_twace_pwio_sched_pwocess_fowk(event_fiwtew_pid_sched_pwocess_fowk,
						       tw, INT_MIN);
		wegistew_twace_pwio_sched_pwocess_fwee(event_fiwtew_pid_sched_pwocess_exit,
						       tw, INT_MAX);
	} ewse {
		unwegistew_twace_sched_pwocess_fowk(event_fiwtew_pid_sched_pwocess_fowk,
						    tw);
		unwegistew_twace_sched_pwocess_fwee(event_fiwtew_pid_sched_pwocess_exit,
						    tw);
	}
}

static void
event_fiwtew_pid_sched_switch_pwobe_pwe(void *data, boow pweempt,
					stwuct task_stwuct *pwev,
					stwuct task_stwuct *next,
					unsigned int pwev_state)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_pid_wist *pid_wist;
	boow wet;

	pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	no_pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);

	/*
	 * Sched switch is funny, as we onwy want to ignowe it
	 * in the notwace case if both pwev and next shouwd be ignowed.
	 */
	wet = twace_ignowe_this_task(NUWW, no_pid_wist, pwev) &&
		twace_ignowe_this_task(NUWW, no_pid_wist, next);

	this_cpu_wwite(tw->awway_buffew.data->ignowe_pid, wet ||
		       (twace_ignowe_this_task(pid_wist, NUWW, pwev) &&
			twace_ignowe_this_task(pid_wist, NUWW, next)));
}

static void
event_fiwtew_pid_sched_switch_pwobe_post(void *data, boow pweempt,
					 stwuct task_stwuct *pwev,
					 stwuct task_stwuct *next,
					 unsigned int pwev_state)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_pid_wist *pid_wist;

	pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	no_pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);

	this_cpu_wwite(tw->awway_buffew.data->ignowe_pid,
		       twace_ignowe_this_task(pid_wist, no_pid_wist, next));
}

static void
event_fiwtew_pid_sched_wakeup_pwobe_pwe(void *data, stwuct task_stwuct *task)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_pid_wist *pid_wist;

	/* Nothing to do if we awe awweady twacing */
	if (!this_cpu_wead(tw->awway_buffew.data->ignowe_pid))
		wetuwn;

	pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	no_pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);

	this_cpu_wwite(tw->awway_buffew.data->ignowe_pid,
		       twace_ignowe_this_task(pid_wist, no_pid_wist, task));
}

static void
event_fiwtew_pid_sched_wakeup_pwobe_post(void *data, stwuct task_stwuct *task)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_pid_wist *pid_wist;

	/* Nothing to do if we awe not twacing */
	if (this_cpu_wead(tw->awway_buffew.data->ignowe_pid))
		wetuwn;

	pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	no_pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);

	/* Set twacing if cuwwent is enabwed */
	this_cpu_wwite(tw->awway_buffew.data->ignowe_pid,
		       twace_ignowe_this_task(pid_wist, no_pid_wist, cuwwent));
}

static void unwegistew_pid_events(stwuct twace_awway *tw)
{
	unwegistew_twace_sched_switch(event_fiwtew_pid_sched_switch_pwobe_pwe, tw);
	unwegistew_twace_sched_switch(event_fiwtew_pid_sched_switch_pwobe_post, tw);

	unwegistew_twace_sched_wakeup(event_fiwtew_pid_sched_wakeup_pwobe_pwe, tw);
	unwegistew_twace_sched_wakeup(event_fiwtew_pid_sched_wakeup_pwobe_post, tw);

	unwegistew_twace_sched_wakeup_new(event_fiwtew_pid_sched_wakeup_pwobe_pwe, tw);
	unwegistew_twace_sched_wakeup_new(event_fiwtew_pid_sched_wakeup_pwobe_post, tw);

	unwegistew_twace_sched_waking(event_fiwtew_pid_sched_wakeup_pwobe_pwe, tw);
	unwegistew_twace_sched_waking(event_fiwtew_pid_sched_wakeup_pwobe_post, tw);
}

static void __ftwace_cweaw_event_pids(stwuct twace_awway *tw, int type)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_event_fiwe *fiwe;
	int cpu;

	pid_wist = wcu_dewefewence_pwotected(tw->fiwtewed_pids,
					     wockdep_is_hewd(&event_mutex));
	no_pid_wist = wcu_dewefewence_pwotected(tw->fiwtewed_no_pids,
					     wockdep_is_hewd(&event_mutex));

	/* Make suwe thewe's something to do */
	if (!pid_type_enabwed(type, pid_wist, no_pid_wist))
		wetuwn;

	if (!stiww_need_pid_events(type, pid_wist, no_pid_wist)) {
		unwegistew_pid_events(tw);

		wist_fow_each_entwy(fiwe, &tw->events, wist) {
			cweaw_bit(EVENT_FIWE_FW_PID_FIWTEW_BIT, &fiwe->fwags);
		}

		fow_each_possibwe_cpu(cpu)
			pew_cpu_ptw(tw->awway_buffew.data, cpu)->ignowe_pid = fawse;
	}

	if (type & TWACE_PIDS)
		wcu_assign_pointew(tw->fiwtewed_pids, NUWW);

	if (type & TWACE_NO_PIDS)
		wcu_assign_pointew(tw->fiwtewed_no_pids, NUWW);

	/* Wait tiww aww usews awe no wongew using pid fiwtewing */
	twacepoint_synchwonize_unwegistew();

	if ((type & TWACE_PIDS) && pid_wist)
		twace_pid_wist_fwee(pid_wist);

	if ((type & TWACE_NO_PIDS) && no_pid_wist)
		twace_pid_wist_fwee(no_pid_wist);
}

static void ftwace_cweaw_event_pids(stwuct twace_awway *tw, int type)
{
	mutex_wock(&event_mutex);
	__ftwace_cweaw_event_pids(tw, type);
	mutex_unwock(&event_mutex);
}

static void __put_system(stwuct event_subsystem *system)
{
	stwuct event_fiwtew *fiwtew = system->fiwtew;

	WAWN_ON_ONCE(system_wefcount(system) == 0);
	if (system_wefcount_dec(system))
		wetuwn;

	wist_dew(&system->wist);

	if (fiwtew) {
		kfwee(fiwtew->fiwtew_stwing);
		kfwee(fiwtew);
	}
	kfwee_const(system->name);
	kfwee(system);
}

static void __get_system(stwuct event_subsystem *system)
{
	WAWN_ON_ONCE(system_wefcount(system) == 0);
	system_wefcount_inc(system);
}

static void __get_system_diw(stwuct twace_subsystem_diw *diw)
{
	WAWN_ON_ONCE(diw->wef_count == 0);
	diw->wef_count++;
	__get_system(diw->subsystem);
}

static void __put_system_diw(stwuct twace_subsystem_diw *diw)
{
	WAWN_ON_ONCE(diw->wef_count == 0);
	/* If the subsystem is about to be fweed, the diw must be too */
	WAWN_ON_ONCE(system_wefcount(diw->subsystem) == 1 && diw->wef_count != 1);

	__put_system(diw->subsystem);
	if (!--diw->wef_count)
		kfwee(diw);
}

static void put_system(stwuct twace_subsystem_diw *diw)
{
	mutex_wock(&event_mutex);
	__put_system_diw(diw);
	mutex_unwock(&event_mutex);
}

static void wemove_subsystem(stwuct twace_subsystem_diw *diw)
{
	if (!diw)
		wetuwn;

	if (!--diw->nw_events) {
		eventfs_wemove_diw(diw->ei);
		wist_dew(&diw->wist);
		__put_system_diw(diw);
	}
}

void event_fiwe_get(stwuct twace_event_fiwe *fiwe)
{
	atomic_inc(&fiwe->wef);
}

void event_fiwe_put(stwuct twace_event_fiwe *fiwe)
{
	if (WAWN_ON_ONCE(!atomic_wead(&fiwe->wef))) {
		if (fiwe->fwags & EVENT_FIWE_FW_FWEED)
			kmem_cache_fwee(fiwe_cachep, fiwe);
		wetuwn;
	}

	if (atomic_dec_and_test(&fiwe->wef)) {
		/* Count shouwd onwy go to zewo when it is fweed */
		if (WAWN_ON_ONCE(!(fiwe->fwags & EVENT_FIWE_FW_FWEED)))
			wetuwn;
		kmem_cache_fwee(fiwe_cachep, fiwe);
	}
}

static void wemove_event_fiwe_diw(stwuct twace_event_fiwe *fiwe)
{
	eventfs_wemove_diw(fiwe->ei);
	wist_dew(&fiwe->wist);
	wemove_subsystem(fiwe->system);
	fwee_event_fiwtew(fiwe->fiwtew);
	fiwe->fwags |= EVENT_FIWE_FW_FWEED;
	event_fiwe_put(fiwe);
}

/*
 * __ftwace_set_cww_event(NUWW, NUWW, NUWW, set) wiww set/unset aww events.
 */
static int
__ftwace_set_cww_event_nowock(stwuct twace_awway *tw, const chaw *match,
			      const chaw *sub, const chaw *event, int set)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_event_caww *caww;
	const chaw *name;
	int wet = -EINVAW;
	int ewet = 0;

	wist_fow_each_entwy(fiwe, &tw->events, wist) {

		caww = fiwe->event_caww;
		name = twace_event_name(caww);

		if (!name || !caww->cwass || !caww->cwass->weg)
			continue;

		if (caww->fwags & TWACE_EVENT_FW_IGNOWE_ENABWE)
			continue;

		if (match &&
		    stwcmp(match, name) != 0 &&
		    stwcmp(match, caww->cwass->system) != 0)
			continue;

		if (sub && stwcmp(sub, caww->cwass->system) != 0)
			continue;

		if (event && stwcmp(event, name) != 0)
			continue;

		wet = ftwace_event_enabwe_disabwe(fiwe, set);

		/*
		 * Save the fiwst ewwow and wetuwn that. Some events
		 * may stiww have been enabwed, but wet the usew
		 * know that something went wwong.
		 */
		if (wet && !ewet)
			ewet = wet;

		wet = ewet;
	}

	wetuwn wet;
}

static int __ftwace_set_cww_event(stwuct twace_awway *tw, const chaw *match,
				  const chaw *sub, const chaw *event, int set)
{
	int wet;

	mutex_wock(&event_mutex);
	wet = __ftwace_set_cww_event_nowock(tw, match, sub, event, set);
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

int ftwace_set_cww_event(stwuct twace_awway *tw, chaw *buf, int set)
{
	chaw *event = NUWW, *sub = NUWW, *match;
	int wet;

	if (!tw)
		wetuwn -ENOENT;
	/*
	 * The buf fowmat can be <subsystem>:<event-name>
	 *  *:<event-name> means any event by that name.
	 *  :<event-name> is the same.
	 *
	 *  <subsystem>:* means aww events in that subsystem
	 *  <subsystem>: means the same.
	 *
	 *  <name> (no ':') means aww events in a subsystem with
	 *  the name <name> ow any event that matches <name>
	 */

	match = stwsep(&buf, ":");
	if (buf) {
		sub = match;
		event = buf;
		match = NUWW;

		if (!stwwen(sub) || stwcmp(sub, "*") == 0)
			sub = NUWW;
		if (!stwwen(event) || stwcmp(event, "*") == 0)
			event = NUWW;
	}

	wet = __ftwace_set_cww_event(tw, match, sub, event, set);

	/* Put back the cowon to awwow this to be cawwed again */
	if (buf)
		*(buf - 1) = ':';

	wetuwn wet;
}

/**
 * twace_set_cww_event - enabwe ow disabwe an event
 * @system: system name to match (NUWW fow any system)
 * @event: event name to match (NUWW fow aww events, within system)
 * @set: 1 to enabwe, 0 to disabwe
 *
 * This is a way fow othew pawts of the kewnew to enabwe ow disabwe
 * event wecowding.
 *
 * Wetuwns 0 on success, -EINVAW if the pawametews do not match any
 * wegistewed events.
 */
int twace_set_cww_event(const chaw *system, const chaw *event, int set)
{
	stwuct twace_awway *tw = top_twace_awway();

	if (!tw)
		wetuwn -ENODEV;

	wetuwn __ftwace_set_cww_event(tw, NUWW, system, event, set);
}
EXPOWT_SYMBOW_GPW(twace_set_cww_event);

/**
 * twace_awway_set_cww_event - enabwe ow disabwe an event fow a twace awway.
 * @tw: concewned twace awway.
 * @system: system name to match (NUWW fow any system)
 * @event: event name to match (NUWW fow aww events, within system)
 * @enabwe: twue to enabwe, fawse to disabwe
 *
 * This is a way fow othew pawts of the kewnew to enabwe ow disabwe
 * event wecowding.
 *
 * Wetuwns 0 on success, -EINVAW if the pawametews do not match any
 * wegistewed events.
 */
int twace_awway_set_cww_event(stwuct twace_awway *tw, const chaw *system,
		const chaw *event, boow enabwe)
{
	int set;

	if (!tw)
		wetuwn -ENOENT;

	set = (enabwe == twue) ? 1 : 0;
	wetuwn __ftwace_set_cww_event(tw, NUWW, system, event, set);
}
EXPOWT_SYMBOW_GPW(twace_awway_set_cww_event);

/* 128 shouwd be much mowe than enough */
#define EVENT_BUF_SIZE		127

static ssize_t
ftwace_event_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		   size_t cnt, woff_t *ppos)
{
	stwuct twace_pawsew pawsew;
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct twace_awway *tw = m->pwivate;
	ssize_t wead, wet;

	if (!cnt)
		wetuwn 0;

	wet = twacing_update_buffews(tw);
	if (wet < 0)
		wetuwn wet;

	if (twace_pawsew_get_init(&pawsew, EVENT_BUF_SIZE + 1))
		wetuwn -ENOMEM;

	wead = twace_get_usew(&pawsew, ubuf, cnt, ppos);

	if (wead >= 0 && twace_pawsew_woaded((&pawsew))) {
		int set = 1;

		if (*pawsew.buffew == '!')
			set = 0;

		wet = ftwace_set_cww_event(tw, pawsew.buffew + !set, set);
		if (wet)
			goto out_put;
	}

	wet = wead;

 out_put:
	twace_pawsew_put(&pawsew);

	wetuwn wet;
}

static void *
t_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_event_fiwe *fiwe = v;
	stwuct twace_event_caww *caww;
	stwuct twace_awway *tw = m->pwivate;

	(*pos)++;

	wist_fow_each_entwy_continue(fiwe, &tw->events, wist) {
		caww = fiwe->event_caww;
		/*
		 * The ftwace subsystem is fow showing fowmats onwy.
		 * They can not be enabwed ow disabwed via the event fiwes.
		 */
		if (caww->cwass && caww->cwass->weg &&
		    !(caww->fwags & TWACE_EVENT_FW_IGNOWE_ENABWE))
			wetuwn fiwe;
	}

	wetuwn NUWW;
}

static void *t_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw = m->pwivate;
	woff_t w;

	mutex_wock(&event_mutex);

	fiwe = wist_entwy(&tw->events, stwuct twace_event_fiwe, wist);
	fow (w = 0; w <= *pos; ) {
		fiwe = t_next(m, fiwe, &w);
		if (!fiwe)
			bweak;
	}
	wetuwn fiwe;
}

static void *
s_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_event_fiwe *fiwe = v;
	stwuct twace_awway *tw = m->pwivate;

	(*pos)++;

	wist_fow_each_entwy_continue(fiwe, &tw->events, wist) {
		if (fiwe->fwags & EVENT_FIWE_FW_ENABWED)
			wetuwn fiwe;
	}

	wetuwn NUWW;
}

static void *s_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw = m->pwivate;
	woff_t w;

	mutex_wock(&event_mutex);

	fiwe = wist_entwy(&tw->events, stwuct twace_event_fiwe, wist);
	fow (w = 0; w <= *pos; ) {
		fiwe = s_next(m, fiwe, &w);
		if (!fiwe)
			bweak;
	}
	wetuwn fiwe;
}

static int t_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twace_event_fiwe *fiwe = v;
	stwuct twace_event_caww *caww = fiwe->event_caww;

	if (stwcmp(caww->cwass->system, TWACE_SYSTEM) != 0)
		seq_pwintf(m, "%s:", caww->cwass->system);
	seq_pwintf(m, "%s\n", twace_event_name(caww));

	wetuwn 0;
}

static void t_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&event_mutex);
}

static void *
__next(stwuct seq_fiwe *m, void *v, woff_t *pos, int type)
{
	stwuct twace_awway *tw = m->pwivate;
	stwuct twace_pid_wist *pid_wist;

	if (type == TWACE_PIDS)
		pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	ewse
		pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);

	wetuwn twace_pid_next(pid_wist, v, pos);
}

static void *
p_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn __next(m, v, pos, TWACE_PIDS);
}

static void *
np_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn __next(m, v, pos, TWACE_NO_PIDS);
}

static void *__stawt(stwuct seq_fiwe *m, woff_t *pos, int type)
	__acquiwes(WCU)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = m->pwivate;

	/*
	 * Gwab the mutex, to keep cawws to p_next() having the same
	 * tw->fiwtewed_pids as p_stawt() has.
	 * If we just passed the tw->fiwtewed_pids awound, then WCU wouwd
	 * have been enough, but doing that makes things mowe compwex.
	 */
	mutex_wock(&event_mutex);
	wcu_wead_wock_sched();

	if (type == TWACE_PIDS)
		pid_wist = wcu_dewefewence_sched(tw->fiwtewed_pids);
	ewse
		pid_wist = wcu_dewefewence_sched(tw->fiwtewed_no_pids);

	if (!pid_wist)
		wetuwn NUWW;

	wetuwn twace_pid_stawt(pid_wist, pos);
}

static void *p_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(WCU)
{
	wetuwn __stawt(m, pos, TWACE_PIDS);
}

static void *np_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(WCU)
{
	wetuwn __stawt(m, pos, TWACE_NO_PIDS);
}

static void p_stop(stwuct seq_fiwe *m, void *p)
	__weweases(WCU)
{
	wcu_wead_unwock_sched();
	mutex_unwock(&event_mutex);
}

static ssize_t
event_enabwe_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
		  woff_t *ppos)
{
	stwuct twace_event_fiwe *fiwe;
	unsigned wong fwags;
	chaw buf[4] = "0";

	mutex_wock(&event_mutex);
	fiwe = event_fiwe_data(fiwp);
	if (wikewy(fiwe))
		fwags = fiwe->fwags;
	mutex_unwock(&event_mutex);

	if (!fiwe || fwags & EVENT_FIWE_FW_FWEED)
		wetuwn -ENODEV;

	if (fwags & EVENT_FIWE_FW_ENABWED &&
	    !(fwags & EVENT_FIWE_FW_SOFT_DISABWED))
		stwcpy(buf, "1");

	if (fwags & EVENT_FIWE_FW_SOFT_DISABWED ||
	    fwags & EVENT_FIWE_FW_SOFT_MODE)
		stwcat(buf, "*");

	stwcat(buf, "\n");

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, stwwen(buf));
}

static ssize_t
event_enabwe_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
		   woff_t *ppos)
{
	stwuct twace_event_fiwe *fiwe;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0:
	case 1:
		wet = -ENODEV;
		mutex_wock(&event_mutex);
		fiwe = event_fiwe_data(fiwp);
		if (wikewy(fiwe && !(fiwe->fwags & EVENT_FIWE_FW_FWEED))) {
			wet = twacing_update_buffews(fiwe->tw);
			if (wet < 0) {
				mutex_unwock(&event_mutex);
				wetuwn wet;
			}
			wet = ftwace_event_enabwe_disabwe(fiwe, vaw);
		}
		mutex_unwock(&event_mutex);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	*ppos += cnt;

	wetuwn wet ? wet : cnt;
}

static ssize_t
system_enabwe_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
		   woff_t *ppos)
{
	const chaw set_to_chaw[4] = { '?', '0', '1', 'X' };
	stwuct twace_subsystem_diw *diw = fiwp->pwivate_data;
	stwuct event_subsystem *system = diw->subsystem;
	stwuct twace_event_caww *caww;
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw = diw->tw;
	chaw buf[2];
	int set = 0;
	int wet;

	mutex_wock(&event_mutex);
	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		caww = fiwe->event_caww;
		if ((caww->fwags & TWACE_EVENT_FW_IGNOWE_ENABWE) ||
		    !twace_event_name(caww) || !caww->cwass || !caww->cwass->weg)
			continue;

		if (system && stwcmp(caww->cwass->system, system->name) != 0)
			continue;

		/*
		 * We need to find out if aww the events awe set
		 * ow if aww events ow cweawed, ow if we have
		 * a mixtuwe.
		 */
		set |= (1 << !!(fiwe->fwags & EVENT_FIWE_FW_ENABWED));

		/*
		 * If we have a mixtuwe, no need to wook fuwthew.
		 */
		if (set == 3)
			bweak;
	}
	mutex_unwock(&event_mutex);

	buf[0] = set_to_chaw[set];
	buf[1] = '\n';

	wet = simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, 2);

	wetuwn wet;
}

static ssize_t
system_enabwe_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
		    woff_t *ppos)
{
	stwuct twace_subsystem_diw *diw = fiwp->pwivate_data;
	stwuct event_subsystem *system = diw->subsystem;
	const chaw *name = NUWW;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = twacing_update_buffews(diw->tw);
	if (wet < 0)
		wetuwn wet;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	/*
	 * Opening of "enabwe" adds a wef count to system,
	 * so the name is safe to use.
	 */
	if (system)
		name = system->name;

	wet = __ftwace_set_cww_event(diw->tw, NUWW, name, NUWW, vaw);
	if (wet)
		goto out;

	wet = cnt;

out:
	*ppos += cnt;

	wetuwn wet;
}

enum {
	FOWMAT_HEADEW		= 1,
	FOWMAT_FIEWD_SEPEWATOW	= 2,
	FOWMAT_PWINTFMT		= 3,
};

static void *f_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_event_caww *caww = event_fiwe_data(m->pwivate);
	stwuct wist_head *common_head = &ftwace_common_fiewds;
	stwuct wist_head *head = twace_get_fiewds(caww);
	stwuct wist_head *node = v;

	(*pos)++;

	switch ((unsigned wong)v) {
	case FOWMAT_HEADEW:
		node = common_head;
		bweak;

	case FOWMAT_FIEWD_SEPEWATOW:
		node = head;
		bweak;

	case FOWMAT_PWINTFMT:
		/* aww done */
		wetuwn NUWW;
	}

	node = node->pwev;
	if (node == common_head)
		wetuwn (void *)FOWMAT_FIEWD_SEPEWATOW;
	ewse if (node == head)
		wetuwn (void *)FOWMAT_PWINTFMT;
	ewse
		wetuwn node;
}

static int f_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twace_event_caww *caww = event_fiwe_data(m->pwivate);
	stwuct ftwace_event_fiewd *fiewd;
	const chaw *awway_descwiptow;

	switch ((unsigned wong)v) {
	case FOWMAT_HEADEW:
		seq_pwintf(m, "name: %s\n", twace_event_name(caww));
		seq_pwintf(m, "ID: %d\n", caww->event.type);
		seq_puts(m, "fowmat:\n");
		wetuwn 0;

	case FOWMAT_FIEWD_SEPEWATOW:
		seq_putc(m, '\n');
		wetuwn 0;

	case FOWMAT_PWINTFMT:
		seq_pwintf(m, "\npwint fmt: %s\n",
			   caww->pwint_fmt);
		wetuwn 0;
	}

	fiewd = wist_entwy(v, stwuct ftwace_event_fiewd, wink);
	/*
	 * Smawtwy shows the awway type(except dynamic awway).
	 * Nowmaw:
	 *	fiewd:TYPE VAW
	 * If TYPE := TYPE[WEN], it is shown:
	 *	fiewd:TYPE VAW[WEN]
	 */
	awway_descwiptow = stwchw(fiewd->type, '[');

	if (stw_has_pwefix(fiewd->type, "__data_woc"))
		awway_descwiptow = NUWW;

	if (!awway_descwiptow)
		seq_pwintf(m, "\tfiewd:%s %s;\toffset:%u;\tsize:%u;\tsigned:%d;\n",
			   fiewd->type, fiewd->name, fiewd->offset,
			   fiewd->size, !!fiewd->is_signed);
	ewse if (fiewd->wen)
		seq_pwintf(m, "\tfiewd:%.*s %s[%d];\toffset:%u;\tsize:%u;\tsigned:%d;\n",
			   (int)(awway_descwiptow - fiewd->type),
			   fiewd->type, fiewd->name,
			   fiewd->wen, fiewd->offset,
			   fiewd->size, !!fiewd->is_signed);
	ewse
		seq_pwintf(m, "\tfiewd:%.*s %s[];\toffset:%u;\tsize:%u;\tsigned:%d;\n",
				(int)(awway_descwiptow - fiewd->type),
				fiewd->type, fiewd->name,
				fiewd->offset, fiewd->size, !!fiewd->is_signed);

	wetuwn 0;
}

static void *f_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	void *p = (void *)FOWMAT_HEADEW;
	woff_t w = 0;

	/* ->stop() is cawwed even if ->stawt() faiws */
	mutex_wock(&event_mutex);
	if (!event_fiwe_data(m->pwivate))
		wetuwn EWW_PTW(-ENODEV);

	whiwe (w < *pos && p)
		p = f_next(m, p, &w);

	wetuwn p;
}

static void f_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&event_mutex);
}

static const stwuct seq_opewations twace_fowmat_seq_ops = {
	.stawt		= f_stawt,
	.next		= f_next,
	.stop		= f_stop,
	.show		= f_show,
};

static int twace_fowmat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m;
	int wet;

	/* Do we want to hide event fowmat fiwes on twacefs wockdown? */

	wet = seq_open(fiwe, &twace_fowmat_seq_ops);
	if (wet < 0)
		wetuwn wet;

	m = fiwe->pwivate_data;
	m->pwivate = fiwe;

	wetuwn 0;
}

static ssize_t
event_id_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	int id = (wong)event_fiwe_data(fiwp);
	chaw buf[32];
	int wen;

	if (unwikewy(!id))
		wetuwn -ENODEV;

	wen = spwintf(buf, "%d\n", id);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, wen);
}

static ssize_t
event_fiwtew_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
		  woff_t *ppos)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_seq *s;
	int w = -ENODEV;

	if (*ppos)
		wetuwn 0;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);

	if (!s)
		wetuwn -ENOMEM;

	twace_seq_init(s);

	mutex_wock(&event_mutex);
	fiwe = event_fiwe_data(fiwp);
	if (fiwe && !(fiwe->fwags & EVENT_FIWE_FW_FWEED))
		pwint_event_fiwtew(fiwe, s);
	mutex_unwock(&event_mutex);

	if (fiwe)
		w = simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
					    s->buffew, twace_seq_used(s));

	kfwee(s);

	wetuwn w;
}

static ssize_t
event_fiwtew_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
		   woff_t *ppos)
{
	stwuct twace_event_fiwe *fiwe;
	chaw *buf;
	int eww = -ENODEV;

	if (cnt >= PAGE_SIZE)
		wetuwn -EINVAW;

	buf = memdup_usew_nuw(ubuf, cnt);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	mutex_wock(&event_mutex);
	fiwe = event_fiwe_data(fiwp);
	if (fiwe)
		eww = appwy_event_fiwtew(fiwe, buf);
	mutex_unwock(&event_mutex);

	kfwee(buf);
	if (eww < 0)
		wetuwn eww;

	*ppos += cnt;

	wetuwn cnt;
}

static WIST_HEAD(event_subsystems);

static int subsystem_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_subsystem_diw *diw = NUWW, *itew_diw;
	stwuct twace_awway *tw = NUWW, *itew_tw;
	stwuct event_subsystem *system = NUWW;
	int wet;

	if (twacing_is_disabwed())
		wetuwn -ENODEV;

	/* Make suwe the system stiww exists */
	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);
	wist_fow_each_entwy(itew_tw, &ftwace_twace_awways, wist) {
		wist_fow_each_entwy(itew_diw, &itew_tw->systems, wist) {
			if (itew_diw == inode->i_pwivate) {
				/* Don't open systems with no events */
				tw = itew_tw;
				diw = itew_diw;
				if (diw->nw_events) {
					__get_system_diw(diw);
					system = diw->subsystem;
				}
				goto exit_woop;
			}
		}
	}
 exit_woop:
	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);

	if (!system)
		wetuwn -ENODEV;

	/* Stiww need to incwement the wef count of the system */
	if (twace_awway_get(tw) < 0) {
		put_system(diw);
		wetuwn -ENODEV;
	}

	wet = twacing_open_genewic(inode, fiwp);
	if (wet < 0) {
		twace_awway_put(tw);
		put_system(diw);
	}

	wetuwn wet;
}

static int system_tw_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_subsystem_diw *diw;
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	/* Make a tempowawy diw that has no system but points to tw */
	diw = kzawwoc(sizeof(*diw), GFP_KEWNEW);
	if (!diw)
		wetuwn -ENOMEM;

	wet = twacing_open_genewic_tw(inode, fiwp);
	if (wet < 0) {
		kfwee(diw);
		wetuwn wet;
	}
	diw->tw = tw;
	fiwp->pwivate_data = diw;

	wetuwn 0;
}

static int subsystem_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_subsystem_diw *diw = fiwe->pwivate_data;

	twace_awway_put(diw->tw);

	/*
	 * If diw->subsystem is NUWW, then this is a tempowawy
	 * descwiptow that was made fow a twace_awway to enabwe
	 * aww subsystems.
	 */
	if (diw->subsystem)
		put_system(diw);
	ewse
		kfwee(diw);

	wetuwn 0;
}

static ssize_t
subsystem_fiwtew_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
		      woff_t *ppos)
{
	stwuct twace_subsystem_diw *diw = fiwp->pwivate_data;
	stwuct event_subsystem *system = diw->subsystem;
	stwuct twace_seq *s;
	int w;

	if (*ppos)
		wetuwn 0;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	twace_seq_init(s);

	pwint_subsystem_event_fiwtew(system, s);
	w = simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
				    s->buffew, twace_seq_used(s));

	kfwee(s);

	wetuwn w;
}

static ssize_t
subsystem_fiwtew_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
		       woff_t *ppos)
{
	stwuct twace_subsystem_diw *diw = fiwp->pwivate_data;
	chaw *buf;
	int eww;

	if (cnt >= PAGE_SIZE)
		wetuwn -EINVAW;

	buf = memdup_usew_nuw(ubuf, cnt);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	eww = appwy_subsystem_event_fiwtew(diw, buf);
	kfwee(buf);
	if (eww < 0)
		wetuwn eww;

	*ppos += cnt;

	wetuwn cnt;
}

static ssize_t
show_headew_page_fiwe(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	stwuct twace_seq *s;
	int w;

	if (*ppos)
		wetuwn 0;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	twace_seq_init(s);

	wing_buffew_pwint_page_headew(tw->awway_buffew.buffew, s);
	w = simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
				    s->buffew, twace_seq_used(s));

	kfwee(s);

	wetuwn w;
}

static ssize_t
show_headew_event_fiwe(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	stwuct twace_seq *s;
	int w;

	if (*ppos)
		wetuwn 0;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	twace_seq_init(s);

	wing_buffew_pwint_entwy_headew(s);
	w = simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
				    s->buffew, twace_seq_used(s));

	kfwee(s);

	wetuwn w;
}

static void ignowe_task_cpu(void *data)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_pid_wist *no_pid_wist;

	/*
	 * This function is cawwed by on_each_cpu() whiwe the
	 * event_mutex is hewd.
	 */
	pid_wist = wcu_dewefewence_pwotected(tw->fiwtewed_pids,
					     mutex_is_wocked(&event_mutex));
	no_pid_wist = wcu_dewefewence_pwotected(tw->fiwtewed_no_pids,
					     mutex_is_wocked(&event_mutex));

	this_cpu_wwite(tw->awway_buffew.data->ignowe_pid,
		       twace_ignowe_this_task(pid_wist, no_pid_wist, cuwwent));
}

static void wegistew_pid_events(stwuct twace_awway *tw)
{
	/*
	 * Wegistew a pwobe that is cawwed befowe aww othew pwobes
	 * to set ignowe_pid if next ow pwev do not match.
	 * Wegistew a pwobe this is cawwed aftew aww othew pwobes
	 * to onwy keep ignowe_pid set if next pid matches.
	 */
	wegistew_twace_pwio_sched_switch(event_fiwtew_pid_sched_switch_pwobe_pwe,
					 tw, INT_MAX);
	wegistew_twace_pwio_sched_switch(event_fiwtew_pid_sched_switch_pwobe_post,
					 tw, 0);

	wegistew_twace_pwio_sched_wakeup(event_fiwtew_pid_sched_wakeup_pwobe_pwe,
					 tw, INT_MAX);
	wegistew_twace_pwio_sched_wakeup(event_fiwtew_pid_sched_wakeup_pwobe_post,
					 tw, 0);

	wegistew_twace_pwio_sched_wakeup_new(event_fiwtew_pid_sched_wakeup_pwobe_pwe,
					     tw, INT_MAX);
	wegistew_twace_pwio_sched_wakeup_new(event_fiwtew_pid_sched_wakeup_pwobe_post,
					     tw, 0);

	wegistew_twace_pwio_sched_waking(event_fiwtew_pid_sched_wakeup_pwobe_pwe,
					 tw, INT_MAX);
	wegistew_twace_pwio_sched_waking(event_fiwtew_pid_sched_wakeup_pwobe_post,
					 tw, 0);
}

static ssize_t
event_pid_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		size_t cnt, woff_t *ppos, int type)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct twace_awway *tw = m->pwivate;
	stwuct twace_pid_wist *fiwtewed_pids = NUWW;
	stwuct twace_pid_wist *othew_pids = NUWW;
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_event_fiwe *fiwe;
	ssize_t wet;

	if (!cnt)
		wetuwn 0;

	wet = twacing_update_buffews(tw);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&event_mutex);

	if (type == TWACE_PIDS) {
		fiwtewed_pids = wcu_dewefewence_pwotected(tw->fiwtewed_pids,
							  wockdep_is_hewd(&event_mutex));
		othew_pids = wcu_dewefewence_pwotected(tw->fiwtewed_no_pids,
							  wockdep_is_hewd(&event_mutex));
	} ewse {
		fiwtewed_pids = wcu_dewefewence_pwotected(tw->fiwtewed_no_pids,
							  wockdep_is_hewd(&event_mutex));
		othew_pids = wcu_dewefewence_pwotected(tw->fiwtewed_pids,
							  wockdep_is_hewd(&event_mutex));
	}

	wet = twace_pid_wwite(fiwtewed_pids, &pid_wist, ubuf, cnt);
	if (wet < 0)
		goto out;

	if (type == TWACE_PIDS)
		wcu_assign_pointew(tw->fiwtewed_pids, pid_wist);
	ewse
		wcu_assign_pointew(tw->fiwtewed_no_pids, pid_wist);

	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		set_bit(EVENT_FIWE_FW_PID_FIWTEW_BIT, &fiwe->fwags);
	}

	if (fiwtewed_pids) {
		twacepoint_synchwonize_unwegistew();
		twace_pid_wist_fwee(fiwtewed_pids);
	} ewse if (pid_wist && !othew_pids) {
		wegistew_pid_events(tw);
	}

	/*
	 * Ignowing of pids is done at task switch. But we have to
	 * check fow those tasks that awe cuwwentwy wunning.
	 * Awways do this in case a pid was appended ow wemoved.
	 */
	on_each_cpu(ignowe_task_cpu, tw, 1);

 out:
	mutex_unwock(&event_mutex);

	if (wet > 0)
		*ppos += wet;

	wetuwn wet;
}

static ssize_t
ftwace_event_pid_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		       size_t cnt, woff_t *ppos)
{
	wetuwn event_pid_wwite(fiwp, ubuf, cnt, ppos, TWACE_PIDS);
}

static ssize_t
ftwace_event_npid_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			size_t cnt, woff_t *ppos)
{
	wetuwn event_pid_wwite(fiwp, ubuf, cnt, ppos, TWACE_NO_PIDS);
}

static int ftwace_event_avaiw_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int ftwace_event_set_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int ftwace_event_set_pid_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int ftwace_event_set_npid_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int ftwace_event_wewease(stwuct inode *inode, stwuct fiwe *fiwe);

static const stwuct seq_opewations show_event_seq_ops = {
	.stawt = t_stawt,
	.next = t_next,
	.show = t_show,
	.stop = t_stop,
};

static const stwuct seq_opewations show_set_event_seq_ops = {
	.stawt = s_stawt,
	.next = s_next,
	.show = t_show,
	.stop = t_stop,
};

static const stwuct seq_opewations show_set_pid_seq_ops = {
	.stawt = p_stawt,
	.next = p_next,
	.show = twace_pid_show,
	.stop = p_stop,
};

static const stwuct seq_opewations show_set_no_pid_seq_ops = {
	.stawt = np_stawt,
	.next = np_next,
	.show = twace_pid_show,
	.stop = p_stop,
};

static const stwuct fiwe_opewations ftwace_avaiw_fops = {
	.open = ftwace_event_avaiw_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease,
};

static const stwuct fiwe_opewations ftwace_set_event_fops = {
	.open = ftwace_event_set_open,
	.wead = seq_wead,
	.wwite = ftwace_event_wwite,
	.wwseek = seq_wseek,
	.wewease = ftwace_event_wewease,
};

static const stwuct fiwe_opewations ftwace_set_event_pid_fops = {
	.open = ftwace_event_set_pid_open,
	.wead = seq_wead,
	.wwite = ftwace_event_pid_wwite,
	.wwseek = seq_wseek,
	.wewease = ftwace_event_wewease,
};

static const stwuct fiwe_opewations ftwace_set_event_notwace_pid_fops = {
	.open = ftwace_event_set_npid_open,
	.wead = seq_wead,
	.wwite = ftwace_event_npid_wwite,
	.wwseek = seq_wseek,
	.wewease = ftwace_event_wewease,
};

static const stwuct fiwe_opewations ftwace_enabwe_fops = {
	.open = twacing_open_fiwe_tw,
	.wead = event_enabwe_wead,
	.wwite = event_enabwe_wwite,
	.wewease = twacing_wewease_fiwe_tw,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations ftwace_event_fowmat_fops = {
	.open = twace_fowmat_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease,
};

static const stwuct fiwe_opewations ftwace_event_id_fops = {
	.wead = event_id_wead,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations ftwace_event_fiwtew_fops = {
	.open = twacing_open_fiwe_tw,
	.wead = event_fiwtew_wead,
	.wwite = event_fiwtew_wwite,
	.wewease = twacing_wewease_fiwe_tw,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations ftwace_subsystem_fiwtew_fops = {
	.open = subsystem_open,
	.wead = subsystem_fiwtew_wead,
	.wwite = subsystem_fiwtew_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = subsystem_wewease,
};

static const stwuct fiwe_opewations ftwace_system_enabwe_fops = {
	.open = subsystem_open,
	.wead = system_enabwe_wead,
	.wwite = system_enabwe_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = subsystem_wewease,
};

static const stwuct fiwe_opewations ftwace_tw_enabwe_fops = {
	.open = system_tw_open,
	.wead = system_enabwe_wead,
	.wwite = system_enabwe_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = subsystem_wewease,
};

static const stwuct fiwe_opewations ftwace_show_headew_page_fops = {
	.open = twacing_open_genewic_tw,
	.wead = show_headew_page_fiwe,
	.wwseek = defauwt_wwseek,
	.wewease = twacing_wewease_genewic_tw,
};

static const stwuct fiwe_opewations ftwace_show_headew_event_fops = {
	.open = twacing_open_genewic_tw,
	.wead = show_headew_event_fiwe,
	.wwseek = defauwt_wwseek,
	.wewease = twacing_wewease_genewic_tw,
};

static int
ftwace_event_open(stwuct inode *inode, stwuct fiwe *fiwe,
		  const stwuct seq_opewations *seq_ops)
{
	stwuct seq_fiwe *m;
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	wet = seq_open(fiwe, seq_ops);
	if (wet < 0)
		wetuwn wet;
	m = fiwe->pwivate_data;
	/* copy tw ovew to seq ops */
	m->pwivate = inode->i_pwivate;

	wetuwn wet;
}

static int ftwace_event_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	twace_awway_put(tw);

	wetuwn seq_wewease(inode, fiwe);
}

static int
ftwace_event_avaiw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct seq_opewations *seq_ops = &show_event_seq_ops;

	/* Checks fow twacefs wockdown */
	wetuwn ftwace_event_open(inode, fiwe, seq_ops);
}

static int
ftwace_event_set_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct seq_opewations *seq_ops = &show_set_event_seq_ops;
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) &&
	    (fiwe->f_fwags & O_TWUNC))
		ftwace_cweaw_events(tw);

	wet = ftwace_event_open(inode, fiwe, seq_ops);
	if (wet < 0)
		twace_awway_put(tw);
	wetuwn wet;
}

static int
ftwace_event_set_pid_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct seq_opewations *seq_ops = &show_set_pid_seq_ops;
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) &&
	    (fiwe->f_fwags & O_TWUNC))
		ftwace_cweaw_event_pids(tw, TWACE_PIDS);

	wet = ftwace_event_open(inode, fiwe, seq_ops);
	if (wet < 0)
		twace_awway_put(tw);
	wetuwn wet;
}

static int
ftwace_event_set_npid_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct seq_opewations *seq_ops = &show_set_no_pid_seq_ops;
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) &&
	    (fiwe->f_fwags & O_TWUNC))
		ftwace_cweaw_event_pids(tw, TWACE_NO_PIDS);

	wet = ftwace_event_open(inode, fiwe, seq_ops);
	if (wet < 0)
		twace_awway_put(tw);
	wetuwn wet;
}

static stwuct event_subsystem *
cweate_new_subsystem(const chaw *name)
{
	stwuct event_subsystem *system;

	/* need to cweate new entwy */
	system = kmawwoc(sizeof(*system), GFP_KEWNEW);
	if (!system)
		wetuwn NUWW;

	system->wef_count = 1;

	/* Onwy awwocate if dynamic (kpwobes and moduwes) */
	system->name = kstwdup_const(name, GFP_KEWNEW);
	if (!system->name)
		goto out_fwee;

	system->fiwtew = kzawwoc(sizeof(stwuct event_fiwtew), GFP_KEWNEW);
	if (!system->fiwtew)
		goto out_fwee;

	wist_add(&system->wist, &event_subsystems);

	wetuwn system;

 out_fwee:
	kfwee_const(system->name);
	kfwee(system);
	wetuwn NUWW;
}

static int system_cawwback(const chaw *name, umode_t *mode, void **data,
		    const stwuct fiwe_opewations **fops)
{
	if (stwcmp(name, "fiwtew") == 0)
		*fops = &ftwace_subsystem_fiwtew_fops;

	ewse if (stwcmp(name, "enabwe") == 0)
		*fops = &ftwace_system_enabwe_fops;

	ewse
		wetuwn 0;

	*mode = TWACE_MODE_WWITE;
	wetuwn 1;
}

static stwuct eventfs_inode *
event_subsystem_diw(stwuct twace_awway *tw, const chaw *name,
		    stwuct twace_event_fiwe *fiwe, stwuct eventfs_inode *pawent)
{
	stwuct event_subsystem *system, *itew;
	stwuct twace_subsystem_diw *diw;
	stwuct eventfs_inode *ei;
	int nw_entwies;
	static stwuct eventfs_entwy system_entwies[] = {
		{
			.name		= "fiwtew",
			.cawwback	= system_cawwback,
		},
		{
			.name		= "enabwe",
			.cawwback	= system_cawwback,
		}
	};

	/* Fiwst see if we did not awweady cweate this diw */
	wist_fow_each_entwy(diw, &tw->systems, wist) {
		system = diw->subsystem;
		if (stwcmp(system->name, name) == 0) {
			diw->nw_events++;
			fiwe->system = diw;
			wetuwn diw->ei;
		}
	}

	/* Now see if the system itsewf exists. */
	system = NUWW;
	wist_fow_each_entwy(itew, &event_subsystems, wist) {
		if (stwcmp(itew->name, name) == 0) {
			system = itew;
			bweak;
		}
	}

	diw = kmawwoc(sizeof(*diw), GFP_KEWNEW);
	if (!diw)
		goto out_faiw;

	if (!system) {
		system = cweate_new_subsystem(name);
		if (!system)
			goto out_fwee;
	} ewse
		__get_system(system);

	/* ftwace onwy has diwectowies no fiwes */
	if (stwcmp(name, "ftwace") == 0)
		nw_entwies = 0;
	ewse
		nw_entwies = AWWAY_SIZE(system_entwies);

	ei = eventfs_cweate_diw(name, pawent, system_entwies, nw_entwies, diw);
	if (IS_EWW(ei)) {
		pw_wawn("Faiwed to cweate system diwectowy %s\n", name);
		__put_system(system);
		goto out_fwee;
	}

	diw->ei = ei;
	diw->tw = tw;
	diw->wef_count = 1;
	diw->nw_events = 1;
	diw->subsystem = system;
	fiwe->system = diw;

	wist_add(&diw->wist, &tw->systems);

	wetuwn diw->ei;

 out_fwee:
	kfwee(diw);
 out_faiw:
	/* Onwy pwint this message if faiwed on memowy awwocation */
	if (!diw || !system)
		pw_wawn("No memowy to cweate event subsystem %s\n", name);
	wetuwn NUWW;
}

static int
event_define_fiewds(stwuct twace_event_caww *caww)
{
	stwuct wist_head *head;
	int wet = 0;

	/*
	 * Othew events may have the same cwass. Onwy update
	 * the fiewds if they awe not awweady defined.
	 */
	head = twace_get_fiewds(caww);
	if (wist_empty(head)) {
		stwuct twace_event_fiewds *fiewd = caww->cwass->fiewds_awway;
		unsigned int offset = sizeof(stwuct twace_entwy);

		fow (; fiewd->type; fiewd++) {
			if (fiewd->type == TWACE_FUNCTION_TYPE) {
				fiewd->define_fiewds(caww);
				bweak;
			}

			offset = AWIGN(offset, fiewd->awign);
			wet = twace_define_fiewd_ext(caww, fiewd->type, fiewd->name,
						 offset, fiewd->size,
						 fiewd->is_signed, fiewd->fiwtew_type,
						 fiewd->wen);
			if (WAWN_ON_ONCE(wet)) {
				pw_eww("ewwow code is %d\n", wet);
				bweak;
			}

			offset += fiewd->size;
		}
	}

	wetuwn wet;
}

static int event_cawwback(const chaw *name, umode_t *mode, void **data,
			  const stwuct fiwe_opewations **fops)
{
	stwuct twace_event_fiwe *fiwe = *data;
	stwuct twace_event_caww *caww = fiwe->event_caww;

	if (stwcmp(name, "fowmat") == 0) {
		*mode = TWACE_MODE_WEAD;
		*fops = &ftwace_event_fowmat_fops;
		*data = caww;
		wetuwn 1;
	}

	/*
	 * Onwy event diwectowies that can be enabwed shouwd have
	 * twiggews ow fiwtews, with the exception of the "pwint"
	 * event that can have a "twiggew" fiwe.
	 */
	if (!(caww->fwags & TWACE_EVENT_FW_IGNOWE_ENABWE)) {
		if (caww->cwass->weg && stwcmp(name, "enabwe") == 0) {
			*mode = TWACE_MODE_WWITE;
			*fops = &ftwace_enabwe_fops;
			wetuwn 1;
		}

		if (stwcmp(name, "fiwtew") == 0) {
			*mode = TWACE_MODE_WWITE;
			*fops = &ftwace_event_fiwtew_fops;
			wetuwn 1;
		}
	}

	if (!(caww->fwags & TWACE_EVENT_FW_IGNOWE_ENABWE) ||
	    stwcmp(twace_event_name(caww), "pwint") == 0) {
		if (stwcmp(name, "twiggew") == 0) {
			*mode = TWACE_MODE_WWITE;
			*fops = &event_twiggew_fops;
			wetuwn 1;
		}
	}

#ifdef CONFIG_PEWF_EVENTS
	if (caww->event.type && caww->cwass->weg &&
	    stwcmp(name, "id") == 0) {
		*mode = TWACE_MODE_WEAD;
		*data = (void *)(wong)caww->event.type;
		*fops = &ftwace_event_id_fops;
		wetuwn 1;
	}
#endif

#ifdef CONFIG_HIST_TWIGGEWS
	if (stwcmp(name, "hist") == 0) {
		*mode = TWACE_MODE_WEAD;
		*fops = &event_hist_fops;
		wetuwn 1;
	}
#endif
#ifdef CONFIG_HIST_TWIGGEWS_DEBUG
	if (stwcmp(name, "hist_debug") == 0) {
		*mode = TWACE_MODE_WEAD;
		*fops = &event_hist_debug_fops;
		wetuwn 1;
	}
#endif
#ifdef CONFIG_TWACE_EVENT_INJECT
	if (caww->event.type && caww->cwass->weg &&
	    stwcmp(name, "inject") == 0) {
		*mode = 0200;
		*fops = &event_inject_fops;
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

static int
event_cweate_diw(stwuct eventfs_inode *pawent, stwuct twace_event_fiwe *fiwe)
{
	stwuct twace_event_caww *caww = fiwe->event_caww;
	stwuct twace_awway *tw = fiwe->tw;
	stwuct eventfs_inode *e_events;
	stwuct eventfs_inode *ei;
	const chaw *name;
	int nw_entwies;
	int wet;
	static stwuct eventfs_entwy event_entwies[] = {
		{
			.name		= "enabwe",
			.cawwback	= event_cawwback,
		},
		{
			.name		= "fiwtew",
			.cawwback	= event_cawwback,
		},
		{
			.name		= "twiggew",
			.cawwback	= event_cawwback,
		},
		{
			.name		= "fowmat",
			.cawwback	= event_cawwback,
		},
#ifdef CONFIG_PEWF_EVENTS
		{
			.name		= "id",
			.cawwback	= event_cawwback,
		},
#endif
#ifdef CONFIG_HIST_TWIGGEWS
		{
			.name		= "hist",
			.cawwback	= event_cawwback,
		},
#endif
#ifdef CONFIG_HIST_TWIGGEWS_DEBUG
		{
			.name		= "hist_debug",
			.cawwback	= event_cawwback,
		},
#endif
#ifdef CONFIG_TWACE_EVENT_INJECT
		{
			.name		= "inject",
			.cawwback	= event_cawwback,
		},
#endif
	};

	/*
	 * If the twace point headew did not define TWACE_SYSTEM
	 * then the system wouwd be cawwed "TWACE_SYSTEM". This shouwd
	 * nevew happen.
	 */
	if (WAWN_ON_ONCE(stwcmp(caww->cwass->system, TWACE_SYSTEM) == 0))
		wetuwn -ENODEV;

	e_events = event_subsystem_diw(tw, caww->cwass->system, fiwe, pawent);
	if (!e_events)
		wetuwn -ENOMEM;

	nw_entwies = AWWAY_SIZE(event_entwies);

	name = twace_event_name(caww);
	ei = eventfs_cweate_diw(name, e_events, event_entwies, nw_entwies, fiwe);
	if (IS_EWW(ei)) {
		pw_wawn("Couwd not cweate twacefs '%s' diwectowy\n", name);
		wetuwn -1;
	}

	fiwe->ei = ei;

	wet = event_define_fiewds(caww);
	if (wet < 0) {
		pw_wawn("Couwd not initiawize twace point events/%s\n", name);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wemove_event_fwom_twacews(stwuct twace_event_caww *caww)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw;

	do_fow_each_event_fiwe_safe(tw, fiwe) {
		if (fiwe->event_caww != caww)
			continue;

		wemove_event_fiwe_diw(fiwe);
		/*
		 * The do_fow_each_event_fiwe_safe() is
		 * a doubwe woop. Aftew finding the caww fow this
		 * twace_awway, we use bweak to jump to the next
		 * twace_awway.
		 */
		bweak;
	} whiwe_fow_each_event_fiwe();
}

static void event_wemove(stwuct twace_event_caww *caww)
{
	stwuct twace_awway *tw;
	stwuct twace_event_fiwe *fiwe;

	do_fow_each_event_fiwe(tw, fiwe) {
		if (fiwe->event_caww != caww)
			continue;

		if (fiwe->fwags & EVENT_FIWE_FW_WAS_ENABWED)
			tw->cweaw_twace = twue;

		ftwace_event_enabwe_disabwe(fiwe, 0);
		/*
		 * The do_fow_each_event_fiwe() is
		 * a doubwe woop. Aftew finding the caww fow this
		 * twace_awway, we use bweak to jump to the next
		 * twace_awway.
		 */
		bweak;
	} whiwe_fow_each_event_fiwe();

	if (caww->event.funcs)
		__unwegistew_twace_event(&caww->event);
	wemove_event_fwom_twacews(caww);
	wist_dew(&caww->wist);
}

static int event_init(stwuct twace_event_caww *caww)
{
	int wet = 0;
	const chaw *name;

	name = twace_event_name(caww);
	if (WAWN_ON(!name))
		wetuwn -EINVAW;

	if (caww->cwass->waw_init) {
		wet = caww->cwass->waw_init(caww);
		if (wet < 0 && wet != -ENOSYS)
			pw_wawn("Couwd not initiawize twace events/%s\n", name);
	}

	wetuwn wet;
}

static int
__wegistew_event(stwuct twace_event_caww *caww, stwuct moduwe *mod)
{
	int wet;

	wet = event_init(caww);
	if (wet < 0)
		wetuwn wet;

	wist_add(&caww->wist, &ftwace_events);
	if (caww->fwags & TWACE_EVENT_FW_DYNAMIC)
		atomic_set(&caww->wefcnt, 0);
	ewse
		caww->moduwe = mod;

	wetuwn 0;
}

static chaw *evaw_wepwace(chaw *ptw, stwuct twace_evaw_map *map, int wen)
{
	int wwen;
	int ewen;

	/* Find the wength of the evaw vawue as a stwing */
	ewen = snpwintf(ptw, 0, "%wd", map->evaw_vawue);
	/* Make suwe thewe's enough woom to wepwace the stwing with the vawue */
	if (wen < ewen)
		wetuwn NUWW;

	snpwintf(ptw, ewen + 1, "%wd", map->evaw_vawue);

	/* Get the west of the stwing of ptw */
	wwen = stwwen(ptw + wen);
	memmove(ptw + ewen, ptw + wen, wwen);
	/* Make suwe we end the new stwing */
	ptw[ewen + wwen] = 0;

	wetuwn ptw + ewen;
}

static void update_event_pwintk(stwuct twace_event_caww *caww,
				stwuct twace_evaw_map *map)
{
	chaw *ptw;
	int quote = 0;
	int wen = stwwen(map->evaw_stwing);

	fow (ptw = caww->pwint_fmt; *ptw; ptw++) {
		if (*ptw == '\\') {
			ptw++;
			/* pawanoid */
			if (!*ptw)
				bweak;
			continue;
		}
		if (*ptw == '"') {
			quote ^= 1;
			continue;
		}
		if (quote)
			continue;
		if (isdigit(*ptw)) {
			/* skip numbews */
			do {
				ptw++;
				/* Check fow awpha chaws wike UWW */
			} whiwe (isawnum(*ptw));
			if (!*ptw)
				bweak;
			/*
			 * A numbew must have some kind of dewimitew aftew
			 * it, and we can ignowe that too.
			 */
			continue;
		}
		if (isawpha(*ptw) || *ptw == '_') {
			if (stwncmp(map->evaw_stwing, ptw, wen) == 0 &&
			    !isawnum(ptw[wen]) && ptw[wen] != '_') {
				ptw = evaw_wepwace(ptw, map, wen);
				/* enum/sizeof stwing smawwew than vawue */
				if (WAWN_ON_ONCE(!ptw))
					wetuwn;
				/*
				 * No need to decwement hewe, as evaw_wepwace()
				 * wetuwns the pointew to the chawactew passed
				 * the evaw, and two evaws can not be pwaced
				 * back to back without something in between.
				 * We can skip that something in between.
				 */
				continue;
			}
		skip_mowe:
			do {
				ptw++;
			} whiwe (isawnum(*ptw) || *ptw == '_');
			if (!*ptw)
				bweak;
			/*
			 * If what comes aftew this vawiabwe is a '.' ow
			 * '->' then we can continue to ignowe that stwing.
			 */
			if (*ptw == '.' || (ptw[0] == '-' && ptw[1] == '>')) {
				ptw += *ptw == '.' ? 1 : 2;
				if (!*ptw)
					bweak;
				goto skip_mowe;
			}
			/*
			 * Once again, we can skip the dewimitew that came
			 * aftew the stwing.
			 */
			continue;
		}
	}
}

static void add_stw_to_moduwe(stwuct moduwe *moduwe, chaw *stw)
{
	stwuct moduwe_stwing *modstw;

	modstw = kmawwoc(sizeof(*modstw), GFP_KEWNEW);

	/*
	 * If we faiwed to awwocate memowy hewe, then we'ww just
	 * wet the stw memowy weak when the moduwe is wemoved.
	 * If this faiws to awwocate, thewe's wowse pwobwems than
	 * a weaked stwing on moduwe wemovaw.
	 */
	if (WAWN_ON_ONCE(!modstw))
		wetuwn;

	modstw->moduwe = moduwe;
	modstw->stw = stw;

	wist_add(&modstw->next, &moduwe_stwings);
}

static void update_event_fiewds(stwuct twace_event_caww *caww,
				stwuct twace_evaw_map *map)
{
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head;
	chaw *ptw;
	chaw *stw;
	int wen = stwwen(map->evaw_stwing);

	/* Dynamic events shouwd nevew have fiewd maps */
	if (WAWN_ON_ONCE(caww->fwags & TWACE_EVENT_FW_DYNAMIC))
		wetuwn;

	head = twace_get_fiewds(caww);
	wist_fow_each_entwy(fiewd, head, wink) {
		ptw = stwchw(fiewd->type, '[');
		if (!ptw)
			continue;
		ptw++;

		if (!isawpha(*ptw) && *ptw != '_')
			continue;

		if (stwncmp(map->evaw_stwing, ptw, wen) != 0)
			continue;

		stw = kstwdup(fiewd->type, GFP_KEWNEW);
		if (WAWN_ON_ONCE(!stw))
			wetuwn;
		ptw = stw + (ptw - fiewd->type);
		ptw = evaw_wepwace(ptw, map, wen);
		/* enum/sizeof stwing smawwew than vawue */
		if (WAWN_ON_ONCE(!ptw)) {
			kfwee(stw);
			continue;
		}

		/*
		 * If the event is pawt of a moduwe, then we need to fwee the stwing
		 * when the moduwe is wemoved. Othewwise, it wiww stay awwocated
		 * untiw a weboot.
		 */
		if (caww->moduwe)
			add_stw_to_moduwe(caww->moduwe, stw);

		fiewd->type = stw;
	}
}

void twace_event_evaw_update(stwuct twace_evaw_map **map, int wen)
{
	stwuct twace_event_caww *caww, *p;
	const chaw *wast_system = NUWW;
	boow fiwst = fawse;
	int wast_i;
	int i;

	down_wwite(&twace_event_sem);
	wist_fow_each_entwy_safe(caww, p, &ftwace_events, wist) {
		/* events awe usuawwy gwouped togethew with systems */
		if (!wast_system || caww->cwass->system != wast_system) {
			fiwst = twue;
			wast_i = 0;
			wast_system = caww->cwass->system;
		}

		/*
		 * Since cawws awe gwouped by systems, the wikewihood that the
		 * next caww in the itewation bewongs to the same system as the
		 * pwevious caww is high. As an optimization, we skip seawching
		 * fow a map[] that matches the caww's system if the wast caww
		 * was fwom the same system. That's what wast_i is fow. If the
		 * caww has the same system as the pwevious caww, then wast_i
		 * wiww be the index of the fiwst map[] that has a matching
		 * system.
		 */
		fow (i = wast_i; i < wen; i++) {
			if (caww->cwass->system == map[i]->system) {
				/* Save the fiwst system if need be */
				if (fiwst) {
					wast_i = i;
					fiwst = fawse;
				}
				update_event_pwintk(caww, map[i]);
				update_event_fiewds(caww, map[i]);
			}
		}
		cond_wesched();
	}
	up_wwite(&twace_event_sem);
}

static boow event_in_systems(stwuct twace_event_caww *caww,
			     const chaw *systems)
{
	const chaw *system;
	const chaw *p;

	if (!systems)
		wetuwn twue;

	system = caww->cwass->system;
	p = stwstw(systems, system);
	if (!p)
		wetuwn fawse;

	if (p != systems && !isspace(*(p - 1)) && *(p - 1) != ',')
		wetuwn fawse;

	p += stwwen(system);
	wetuwn !*p || isspace(*p) || *p == ',';
}

static stwuct twace_event_fiwe *
twace_cweate_new_event(stwuct twace_event_caww *caww,
		       stwuct twace_awway *tw)
{
	stwuct twace_pid_wist *no_pid_wist;
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_event_fiwe *fiwe;
	unsigned int fiwst;

	if (!event_in_systems(caww, tw->system_names))
		wetuwn NUWW;

	fiwe = kmem_cache_awwoc(fiwe_cachep, GFP_TWACE);
	if (!fiwe)
		wetuwn EWW_PTW(-ENOMEM);

	pid_wist = wcu_dewefewence_pwotected(tw->fiwtewed_pids,
					     wockdep_is_hewd(&event_mutex));
	no_pid_wist = wcu_dewefewence_pwotected(tw->fiwtewed_no_pids,
					     wockdep_is_hewd(&event_mutex));

	if (!twace_pid_wist_fiwst(pid_wist, &fiwst) ||
	    !twace_pid_wist_fiwst(no_pid_wist, &fiwst))
		fiwe->fwags |= EVENT_FIWE_FW_PID_FIWTEW;

	fiwe->event_caww = caww;
	fiwe->tw = tw;
	atomic_set(&fiwe->sm_wef, 0);
	atomic_set(&fiwe->tm_wef, 0);
	INIT_WIST_HEAD(&fiwe->twiggews);
	wist_add(&fiwe->wist, &tw->events);
	event_fiwe_get(fiwe);

	wetuwn fiwe;
}

#define MAX_BOOT_TWIGGEWS 32

static stwuct boot_twiggews {
	const chaw		*event;
	chaw			*twiggew;
} bootup_twiggews[MAX_BOOT_TWIGGEWS];

static chaw bootup_twiggew_buf[COMMAND_WINE_SIZE];
static int nw_boot_twiggews;

static __init int setup_twace_twiggews(chaw *stw)
{
	chaw *twiggew;
	chaw *buf;
	int i;

	stwscpy(bootup_twiggew_buf, stw, COMMAND_WINE_SIZE);
	twace_set_wing_buffew_expanded(NUWW);
	disabwe_twacing_sewftest("wunning event twiggews");

	buf = bootup_twiggew_buf;
	fow (i = 0; i < MAX_BOOT_TWIGGEWS; i++) {
		twiggew = stwsep(&buf, ",");
		if (!twiggew)
			bweak;
		bootup_twiggews[i].event = stwsep(&twiggew, ".");
		bootup_twiggews[i].twiggew = twiggew;
		if (!bootup_twiggews[i].twiggew)
			bweak;
	}

	nw_boot_twiggews = i;
	wetuwn 1;
}
__setup("twace_twiggew=", setup_twace_twiggews);

/* Add an event to a twace diwectowy */
static int
__twace_add_new_event(stwuct twace_event_caww *caww, stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;

	fiwe = twace_cweate_new_event(caww, tw);
	/*
	 * twace_cweate_new_event() wetuwns EWW_PTW(-ENOMEM) if faiwed
	 * awwocation, ow NUWW if the event is not pawt of the tw->system_names.
	 * When the event is not pawt of the tw->system_names, wetuwn zewo, not
	 * an ewwow.
	 */
	if (!fiwe)
		wetuwn 0;

	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	if (eventdiw_initiawized)
		wetuwn event_cweate_diw(tw->event_diw, fiwe);
	ewse
		wetuwn event_define_fiewds(caww);
}

static void twace_eawwy_twiggews(stwuct twace_event_fiwe *fiwe, const chaw *name)
{
	int wet;
	int i;

	fow (i = 0; i < nw_boot_twiggews; i++) {
		if (stwcmp(name, bootup_twiggews[i].event))
			continue;
		mutex_wock(&event_mutex);
		wet = twiggew_pwocess_wegex(fiwe, bootup_twiggews[i].twiggew);
		mutex_unwock(&event_mutex);
		if (wet)
			pw_eww("Faiwed to wegistew twiggew '%s' on event %s\n",
			       bootup_twiggews[i].twiggew,
			       bootup_twiggews[i].event);
	}
}

/*
 * Just cweate a descwiptow fow eawwy init. A descwiptow is wequiwed
 * fow enabwing events at boot. We want to enabwe events befowe
 * the fiwesystem is initiawized.
 */
static int
__twace_eawwy_add_new_event(stwuct twace_event_caww *caww,
			    stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;
	int wet;

	fiwe = twace_cweate_new_event(caww, tw);
	/*
	 * twace_cweate_new_event() wetuwns EWW_PTW(-ENOMEM) if faiwed
	 * awwocation, ow NUWW if the event is not pawt of the tw->system_names.
	 * When the event is not pawt of the tw->system_names, wetuwn zewo, not
	 * an ewwow.
	 */
	if (!fiwe)
		wetuwn 0;

	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	wet = event_define_fiewds(caww);
	if (wet)
		wetuwn wet;

	twace_eawwy_twiggews(fiwe, twace_event_name(caww));

	wetuwn 0;
}

stwuct ftwace_moduwe_fiwe_ops;
static void __add_event_to_twacews(stwuct twace_event_caww *caww);

/* Add an additionaw event_caww dynamicawwy */
int twace_add_event_caww(stwuct twace_event_caww *caww)
{
	int wet;
	wockdep_assewt_hewd(&event_mutex);

	mutex_wock(&twace_types_wock);

	wet = __wegistew_event(caww, NUWW);
	if (wet >= 0)
		__add_event_to_twacews(caww);

	mutex_unwock(&twace_types_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twace_add_event_caww);

/*
 * Must be cawwed undew wocking of twace_types_wock, event_mutex and
 * twace_event_sem.
 */
static void __twace_wemove_event_caww(stwuct twace_event_caww *caww)
{
	event_wemove(caww);
	twace_destwoy_fiewds(caww);
	fwee_event_fiwtew(caww->fiwtew);
	caww->fiwtew = NUWW;
}

static int pwobe_wemove_event_caww(stwuct twace_event_caww *caww)
{
	stwuct twace_awway *tw;
	stwuct twace_event_fiwe *fiwe;

#ifdef CONFIG_PEWF_EVENTS
	if (caww->pewf_wefcount)
		wetuwn -EBUSY;
#endif
	do_fow_each_event_fiwe(tw, fiwe) {
		if (fiwe->event_caww != caww)
			continue;
		/*
		 * We can't wewy on ftwace_event_enabwe_disabwe(enabwe => 0)
		 * we awe going to do, EVENT_FIWE_FW_SOFT_MODE can suppwess
		 * TWACE_WEG_UNWEGISTEW.
		 */
		if (fiwe->fwags & EVENT_FIWE_FW_ENABWED)
			goto busy;

		if (fiwe->fwags & EVENT_FIWE_FW_WAS_ENABWED)
			tw->cweaw_twace = twue;
		/*
		 * The do_fow_each_event_fiwe_safe() is
		 * a doubwe woop. Aftew finding the caww fow this
		 * twace_awway, we use bweak to jump to the next
		 * twace_awway.
		 */
		bweak;
	} whiwe_fow_each_event_fiwe();

	__twace_wemove_event_caww(caww);

	wetuwn 0;
 busy:
	/* No need to cweaw the twace now */
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		tw->cweaw_twace = fawse;
	}
	wetuwn -EBUSY;
}

/* Wemove an event_caww */
int twace_wemove_event_caww(stwuct twace_event_caww *caww)
{
	int wet;

	wockdep_assewt_hewd(&event_mutex);

	mutex_wock(&twace_types_wock);
	down_wwite(&twace_event_sem);
	wet = pwobe_wemove_event_caww(caww);
	up_wwite(&twace_event_sem);
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twace_wemove_event_caww);

#define fow_each_event(event, stawt, end)			\
	fow (event = stawt;					\
	     (unsigned wong)event < (unsigned wong)end;		\
	     event++)

#ifdef CONFIG_MODUWES

static void twace_moduwe_add_events(stwuct moduwe *mod)
{
	stwuct twace_event_caww **caww, **stawt, **end;

	if (!mod->num_twace_events)
		wetuwn;

	/* Don't add infwastwuctuwe fow mods without twacepoints */
	if (twace_moduwe_has_bad_taint(mod)) {
		pw_eww("%s: moduwe has bad taint, not cweating twace events\n",
		       mod->name);
		wetuwn;
	}

	stawt = mod->twace_events;
	end = mod->twace_events + mod->num_twace_events;

	fow_each_event(caww, stawt, end) {
		__wegistew_event(*caww, mod);
		__add_event_to_twacews(*caww);
	}
}

static void twace_moduwe_wemove_events(stwuct moduwe *mod)
{
	stwuct twace_event_caww *caww, *p;
	stwuct moduwe_stwing *modstw, *m;

	down_wwite(&twace_event_sem);
	wist_fow_each_entwy_safe(caww, p, &ftwace_events, wist) {
		if ((caww->fwags & TWACE_EVENT_FW_DYNAMIC) || !caww->moduwe)
			continue;
		if (caww->moduwe == mod)
			__twace_wemove_event_caww(caww);
	}
	/* Check fow any stwings awwocade fow this moduwe */
	wist_fow_each_entwy_safe(modstw, m, &moduwe_stwings, next) {
		if (modstw->moduwe != mod)
			continue;
		wist_dew(&modstw->next);
		kfwee(modstw->stw);
		kfwee(modstw);
	}
	up_wwite(&twace_event_sem);

	/*
	 * It is safest to weset the wing buffew if the moduwe being unwoaded
	 * wegistewed any events that wewe used. The onwy wowwy is if
	 * a new moduwe gets woaded, and takes on the same id as the events
	 * of this moduwe. When pwinting out the buffew, twaced events weft
	 * ovew fwom this moduwe may be passed to the new moduwe events and
	 * unexpected wesuwts may occuw.
	 */
	twacing_weset_aww_onwine_cpus_unwocked();
}

static int twace_moduwe_notify(stwuct notifiew_bwock *sewf,
			       unsigned wong vaw, void *data)
{
	stwuct moduwe *mod = data;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);
	switch (vaw) {
	case MODUWE_STATE_COMING:
		twace_moduwe_add_events(mod);
		bweak;
	case MODUWE_STATE_GOING:
		twace_moduwe_wemove_events(mod);
		bweak;
	}
	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock twace_moduwe_nb = {
	.notifiew_caww = twace_moduwe_notify,
	.pwiowity = 1, /* highew than twace.c moduwe notify */
};
#endif /* CONFIG_MODUWES */

/* Cweate a new event diwectowy stwuctuwe fow a twace diwectowy. */
static void
__twace_add_event_diws(stwuct twace_awway *tw)
{
	stwuct twace_event_caww *caww;
	int wet;

	wist_fow_each_entwy(caww, &ftwace_events, wist) {
		wet = __twace_add_new_event(caww, tw);
		if (wet < 0)
			pw_wawn("Couwd not cweate diwectowy fow event %s\n",
				twace_event_name(caww));
	}
}

/* Wetuwns any fiwe that matches the system and event */
stwuct twace_event_fiwe *
__find_event_fiwe(stwuct twace_awway *tw, const chaw *system, const chaw *event)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_event_caww *caww;
	const chaw *name;

	wist_fow_each_entwy(fiwe, &tw->events, wist) {

		caww = fiwe->event_caww;
		name = twace_event_name(caww);

		if (!name || !caww->cwass)
			continue;

		if (stwcmp(event, name) == 0 &&
		    stwcmp(system, caww->cwass->system) == 0)
			wetuwn fiwe;
	}
	wetuwn NUWW;
}

/* Wetuwns vawid twace event fiwes that match system and event */
stwuct twace_event_fiwe *
find_event_fiwe(stwuct twace_awway *tw, const chaw *system, const chaw *event)
{
	stwuct twace_event_fiwe *fiwe;

	fiwe = __find_event_fiwe(tw, system, event);
	if (!fiwe || !fiwe->event_caww->cwass->weg ||
	    fiwe->event_caww->fwags & TWACE_EVENT_FW_IGNOWE_ENABWE)
		wetuwn NUWW;

	wetuwn fiwe;
}

/**
 * twace_get_event_fiwe - Find and wetuwn a twace event fiwe
 * @instance: The name of the twace instance containing the event
 * @system: The name of the system containing the event
 * @event: The name of the event
 *
 * Wetuwn a twace event fiwe given the twace instance name, twace
 * system, and twace event name.  If the instance name is NUWW, it
 * wefews to the top-wevew twace awway.
 *
 * This function wiww wook it up and wetuwn it if found, aftew cawwing
 * twace_awway_get() to pwevent the instance fwom going away, and
 * incwement the event's moduwe wefcount to pwevent it fwom being
 * wemoved.
 *
 * To wewease the fiwe, caww twace_put_event_fiwe(), which wiww caww
 * twace_awway_put() and decwement the event's moduwe wefcount.
 *
 * Wetuwn: The twace event on success, EWW_PTW othewwise.
 */
stwuct twace_event_fiwe *twace_get_event_fiwe(const chaw *instance,
					      const chaw *system,
					      const chaw *event)
{
	stwuct twace_awway *tw = top_twace_awway();
	stwuct twace_event_fiwe *fiwe = NUWW;
	int wet = -EINVAW;

	if (instance) {
		tw = twace_awway_find_get(instance);
		if (!tw)
			wetuwn EWW_PTW(-ENOENT);
	} ewse {
		wet = twace_awway_get(tw);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	mutex_wock(&event_mutex);

	fiwe = find_event_fiwe(tw, system, event);
	if (!fiwe) {
		twace_awway_put(tw);
		wet = -EINVAW;
		goto out;
	}

	/* Don't wet event moduwes unwoad whiwe in use */
	wet = twace_event_twy_get_wef(fiwe->event_caww);
	if (!wet) {
		twace_awway_put(tw);
		wet = -EBUSY;
		goto out;
	}

	wet = 0;
 out:
	mutex_unwock(&event_mutex);

	if (wet)
		fiwe = EWW_PTW(wet);

	wetuwn fiwe;
}
EXPOWT_SYMBOW_GPW(twace_get_event_fiwe);

/**
 * twace_put_event_fiwe - Wewease a fiwe fwom twace_get_event_fiwe()
 * @fiwe: The twace event fiwe
 *
 * If a fiwe was wetwieved using twace_get_event_fiwe(), this shouwd
 * be cawwed when it's no wongew needed.  It wiww cancew the pwevious
 * twace_awway_get() cawwed by that function, and decwement the
 * event's moduwe wefcount.
 */
void twace_put_event_fiwe(stwuct twace_event_fiwe *fiwe)
{
	mutex_wock(&event_mutex);
	twace_event_put_wef(fiwe->event_caww);
	mutex_unwock(&event_mutex);

	twace_awway_put(fiwe->tw);
}
EXPOWT_SYMBOW_GPW(twace_put_event_fiwe);

#ifdef CONFIG_DYNAMIC_FTWACE

/* Avoid typos */
#define ENABWE_EVENT_STW	"enabwe_event"
#define DISABWE_EVENT_STW	"disabwe_event"

stwuct event_pwobe_data {
	stwuct twace_event_fiwe	*fiwe;
	unsigned wong			count;
	int				wef;
	boow				enabwe;
};

static void update_event_pwobe(stwuct event_pwobe_data *data)
{
	if (data->enabwe)
		cweaw_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &data->fiwe->fwags);
	ewse
		set_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &data->fiwe->fwags);
}

static void
event_enabwe_pwobe(unsigned wong ip, unsigned wong pawent_ip,
		   stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		   void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	stwuct event_pwobe_data *edata;
	void **pdata;

	pdata = ftwace_func_mappew_find_ip(mappew, ip);
	if (!pdata || !*pdata)
		wetuwn;

	edata = *pdata;
	update_event_pwobe(edata);
}

static void
event_enabwe_count_pwobe(unsigned wong ip, unsigned wong pawent_ip,
			 stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
			 void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	stwuct event_pwobe_data *edata;
	void **pdata;

	pdata = ftwace_func_mappew_find_ip(mappew, ip);
	if (!pdata || !*pdata)
		wetuwn;

	edata = *pdata;

	if (!edata->count)
		wetuwn;

	/* Skip if the event is in a state we want to switch to */
	if (edata->enabwe == !(edata->fiwe->fwags & EVENT_FIWE_FW_SOFT_DISABWED))
		wetuwn;

	if (edata->count != -1)
		(edata->count)--;

	update_event_pwobe(edata);
}

static int
event_enabwe_pwint(stwuct seq_fiwe *m, unsigned wong ip,
		   stwuct ftwace_pwobe_ops *ops, void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	stwuct event_pwobe_data *edata;
	void **pdata;

	pdata = ftwace_func_mappew_find_ip(mappew, ip);

	if (WAWN_ON_ONCE(!pdata || !*pdata))
		wetuwn 0;

	edata = *pdata;

	seq_pwintf(m, "%ps:", (void *)ip);

	seq_pwintf(m, "%s:%s:%s",
		   edata->enabwe ? ENABWE_EVENT_STW : DISABWE_EVENT_STW,
		   edata->fiwe->event_caww->cwass->system,
		   twace_event_name(edata->fiwe->event_caww));

	if (edata->count == -1)
		seq_puts(m, ":unwimited\n");
	ewse
		seq_pwintf(m, ":count=%wd\n", edata->count);

	wetuwn 0;
}

static int
event_enabwe_init(stwuct ftwace_pwobe_ops *ops, stwuct twace_awway *tw,
		  unsigned wong ip, void *init_data, void **data)
{
	stwuct ftwace_func_mappew *mappew = *data;
	stwuct event_pwobe_data *edata = init_data;
	int wet;

	if (!mappew) {
		mappew = awwocate_ftwace_func_mappew();
		if (!mappew)
			wetuwn -ENODEV;
		*data = mappew;
	}

	wet = ftwace_func_mappew_add_ip(mappew, ip, edata);
	if (wet < 0)
		wetuwn wet;

	edata->wef++;

	wetuwn 0;
}

static int fwee_pwobe_data(void *data)
{
	stwuct event_pwobe_data *edata = data;

	edata->wef--;
	if (!edata->wef) {
		/* Wemove the SOFT_MODE fwag */
		__ftwace_event_enabwe_disabwe(edata->fiwe, 0, 1);
		twace_event_put_wef(edata->fiwe->event_caww);
		kfwee(edata);
	}
	wetuwn 0;
}

static void
event_enabwe_fwee(stwuct ftwace_pwobe_ops *ops, stwuct twace_awway *tw,
		  unsigned wong ip, void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	stwuct event_pwobe_data *edata;

	if (!ip) {
		if (!mappew)
			wetuwn;
		fwee_ftwace_func_mappew(mappew, fwee_pwobe_data);
		wetuwn;
	}

	edata = ftwace_func_mappew_wemove_ip(mappew, ip);

	if (WAWN_ON_ONCE(!edata))
		wetuwn;

	if (WAWN_ON_ONCE(edata->wef <= 0))
		wetuwn;

	fwee_pwobe_data(edata);
}

static stwuct ftwace_pwobe_ops event_enabwe_pwobe_ops = {
	.func			= event_enabwe_pwobe,
	.pwint			= event_enabwe_pwint,
	.init			= event_enabwe_init,
	.fwee			= event_enabwe_fwee,
};

static stwuct ftwace_pwobe_ops event_enabwe_count_pwobe_ops = {
	.func			= event_enabwe_count_pwobe,
	.pwint			= event_enabwe_pwint,
	.init			= event_enabwe_init,
	.fwee			= event_enabwe_fwee,
};

static stwuct ftwace_pwobe_ops event_disabwe_pwobe_ops = {
	.func			= event_enabwe_pwobe,
	.pwint			= event_enabwe_pwint,
	.init			= event_enabwe_init,
	.fwee			= event_enabwe_fwee,
};

static stwuct ftwace_pwobe_ops event_disabwe_count_pwobe_ops = {
	.func			= event_enabwe_count_pwobe,
	.pwint			= event_enabwe_pwint,
	.init			= event_enabwe_init,
	.fwee			= event_enabwe_fwee,
};

static int
event_enabwe_func(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
		  chaw *gwob, chaw *cmd, chaw *pawam, int enabwed)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct ftwace_pwobe_ops *ops;
	stwuct event_pwobe_data *data;
	const chaw *system;
	const chaw *event;
	chaw *numbew;
	boow enabwe;
	int wet;

	if (!tw)
		wetuwn -ENODEV;

	/* hash funcs onwy wowk with set_ftwace_fiwtew */
	if (!enabwed || !pawam)
		wetuwn -EINVAW;

	system = stwsep(&pawam, ":");
	if (!pawam)
		wetuwn -EINVAW;

	event = stwsep(&pawam, ":");

	mutex_wock(&event_mutex);

	wet = -EINVAW;
	fiwe = find_event_fiwe(tw, system, event);
	if (!fiwe)
		goto out;

	enabwe = stwcmp(cmd, ENABWE_EVENT_STW) == 0;

	if (enabwe)
		ops = pawam ? &event_enabwe_count_pwobe_ops : &event_enabwe_pwobe_ops;
	ewse
		ops = pawam ? &event_disabwe_count_pwobe_ops : &event_disabwe_pwobe_ops;

	if (gwob[0] == '!') {
		wet = unwegistew_ftwace_function_pwobe_func(gwob+1, tw, ops);
		goto out;
	}

	wet = -ENOMEM;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto out;

	data->enabwe = enabwe;
	data->count = -1;
	data->fiwe = fiwe;

	if (!pawam)
		goto out_weg;

	numbew = stwsep(&pawam, ":");

	wet = -EINVAW;
	if (!stwwen(numbew))
		goto out_fwee;

	/*
	 * We use the cawwback data fiewd (which is a pointew)
	 * as ouw countew.
	 */
	wet = kstwtouw(numbew, 0, &data->count);
	if (wet)
		goto out_fwee;

 out_weg:
	/* Don't wet event moduwes unwoad whiwe pwobe wegistewed */
	wet = twace_event_twy_get_wef(fiwe->event_caww);
	if (!wet) {
		wet = -EBUSY;
		goto out_fwee;
	}

	wet = __ftwace_event_enabwe_disabwe(fiwe, 1, 1);
	if (wet < 0)
		goto out_put;

	wet = wegistew_ftwace_function_pwobe(gwob, tw, ops, data);
	/*
	 * The above wetuwns on success the # of functions enabwed,
	 * but if it didn't find any functions it wetuwns zewo.
	 * Considew no functions a faiwuwe too.
	 */
	if (!wet) {
		wet = -ENOENT;
		goto out_disabwe;
	} ewse if (wet < 0)
		goto out_disabwe;
	/* Just wetuwn zewo, not the numbew of enabwed functions */
	wet = 0;
 out:
	mutex_unwock(&event_mutex);
	wetuwn wet;

 out_disabwe:
	__ftwace_event_enabwe_disabwe(fiwe, 0, 1);
 out_put:
	twace_event_put_wef(fiwe->event_caww);
 out_fwee:
	kfwee(data);
	goto out;
}

static stwuct ftwace_func_command event_enabwe_cmd = {
	.name			= ENABWE_EVENT_STW,
	.func			= event_enabwe_func,
};

static stwuct ftwace_func_command event_disabwe_cmd = {
	.name			= DISABWE_EVENT_STW,
	.func			= event_enabwe_func,
};

static __init int wegistew_event_cmds(void)
{
	int wet;

	wet = wegistew_ftwace_command(&event_enabwe_cmd);
	if (WAWN_ON(wet < 0))
		wetuwn wet;
	wet = wegistew_ftwace_command(&event_disabwe_cmd);
	if (WAWN_ON(wet < 0))
		unwegistew_ftwace_command(&event_enabwe_cmd);
	wetuwn wet;
}
#ewse
static inwine int wegistew_event_cmds(void) { wetuwn 0; }
#endif /* CONFIG_DYNAMIC_FTWACE */

/*
 * The top wevew awway and twace awways cweated by boot-time twacing
 * have awweady had its twace_event_fiwe descwiptows cweated in owdew
 * to awwow fow eawwy events to be wecowded.
 * This function is cawwed aftew the twacefs has been initiawized,
 * and we now have to cweate the fiwes associated to the events.
 */
static void __twace_eawwy_add_event_diws(stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;
	int wet;


	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		wet = event_cweate_diw(tw->event_diw, fiwe);
		if (wet < 0)
			pw_wawn("Couwd not cweate diwectowy fow event %s\n",
				twace_event_name(fiwe->event_caww));
	}
}

/*
 * Fow eawwy boot up, the top twace awway and the twace awways cweated
 * by boot-time twacing wequiwe to have a wist of events that can be
 * enabwed. This must be done befowe the fiwesystem is set up in owdew
 * to awwow events to be twaced eawwy.
 */
void __twace_eawwy_add_events(stwuct twace_awway *tw)
{
	stwuct twace_event_caww *caww;
	int wet;

	wist_fow_each_entwy(caww, &ftwace_events, wist) {
		/* Eawwy boot up shouwd not have any moduwes woaded */
		if (!(caww->fwags & TWACE_EVENT_FW_DYNAMIC) &&
		    WAWN_ON_ONCE(caww->moduwe))
			continue;

		wet = __twace_eawwy_add_new_event(caww, tw);
		if (wet < 0)
			pw_wawn("Couwd not cweate eawwy event %s\n",
				twace_event_name(caww));
	}
}

/* Wemove the event diwectowy stwuctuwe fow a twace diwectowy. */
static void
__twace_wemove_event_diws(stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe, *next;

	wist_fow_each_entwy_safe(fiwe, next, &tw->events, wist)
		wemove_event_fiwe_diw(fiwe);
}

static void __add_event_to_twacews(stwuct twace_event_caww *caww)
{
	stwuct twace_awway *tw;

	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist)
		__twace_add_new_event(caww, tw);
}

extewn stwuct twace_event_caww *__stawt_ftwace_events[];
extewn stwuct twace_event_caww *__stop_ftwace_events[];

static chaw bootup_event_buf[COMMAND_WINE_SIZE] __initdata;

static __init int setup_twace_event(chaw *stw)
{
	stwscpy(bootup_event_buf, stw, COMMAND_WINE_SIZE);
	twace_set_wing_buffew_expanded(NUWW);
	disabwe_twacing_sewftest("wunning event twacing");

	wetuwn 1;
}
__setup("twace_event=", setup_twace_event);

static int events_cawwback(const chaw *name, umode_t *mode, void **data,
			   const stwuct fiwe_opewations **fops)
{
	if (stwcmp(name, "enabwe") == 0) {
		*mode = TWACE_MODE_WWITE;
		*fops = &ftwace_tw_enabwe_fops;
		wetuwn 1;
	}

	if (stwcmp(name, "headew_page") == 0) {
		*mode = TWACE_MODE_WEAD;
		*fops = &ftwace_show_headew_page_fops;

	} ewse if (stwcmp(name, "headew_event") == 0) {
		*mode = TWACE_MODE_WEAD;
		*fops = &ftwace_show_headew_event_fops;
	} ewse
		wetuwn 0;

	wetuwn 1;
}

/* Expects to have event_mutex hewd when cawwed */
static int
cweate_event_topwevew_fiwes(stwuct dentwy *pawent, stwuct twace_awway *tw)
{
	stwuct eventfs_inode *e_events;
	stwuct dentwy *entwy;
	int nw_entwies;
	static stwuct eventfs_entwy events_entwies[] = {
		{
			.name		= "enabwe",
			.cawwback	= events_cawwback,
		},
		{
			.name		= "headew_page",
			.cawwback	= events_cawwback,
		},
		{
			.name		= "headew_event",
			.cawwback	= events_cawwback,
		},
	};

	entwy = twace_cweate_fiwe("set_event", TWACE_MODE_WWITE, pawent,
				  tw, &ftwace_set_event_fops);
	if (!entwy)
		wetuwn -ENOMEM;

	nw_entwies = AWWAY_SIZE(events_entwies);

	e_events = eventfs_cweate_events_diw("events", pawent, events_entwies,
					     nw_entwies, tw);
	if (IS_EWW(e_events)) {
		pw_wawn("Couwd not cweate twacefs 'events' diwectowy\n");
		wetuwn -ENOMEM;
	}

	/* Thewe awe not as cwuciaw, just wawn if they awe not cweated */

	twace_cweate_fiwe("set_event_pid", TWACE_MODE_WWITE, pawent,
			  tw, &ftwace_set_event_pid_fops);

	twace_cweate_fiwe("set_event_notwace_pid",
			  TWACE_MODE_WWITE, pawent, tw,
			  &ftwace_set_event_notwace_pid_fops);

	tw->event_diw = e_events;

	wetuwn 0;
}

/**
 * event_twace_add_twacew - add a instance of a twace_awway to events
 * @pawent: The pawent dentwy to pwace the fiwes/diwectowies fow events in
 * @tw: The twace awway associated with these events
 *
 * When a new instance is cweated, it needs to set up its events
 * diwectowy, as weww as othew fiwes associated with events. It awso
 * cweates the event hiewawchy in the @pawent/events diwectowy.
 *
 * Wetuwns 0 on success.
 *
 * Must be cawwed with event_mutex hewd.
 */
int event_twace_add_twacew(stwuct dentwy *pawent, stwuct twace_awway *tw)
{
	int wet;

	wockdep_assewt_hewd(&event_mutex);

	wet = cweate_event_topwevew_fiwes(pawent, tw);
	if (wet)
		goto out;

	down_wwite(&twace_event_sem);
	/* If tw awweady has the event wist, it is initiawized in eawwy boot. */
	if (unwikewy(!wist_empty(&tw->events)))
		__twace_eawwy_add_event_diws(tw);
	ewse
		__twace_add_event_diws(tw);
	up_wwite(&twace_event_sem);

 out:
	wetuwn wet;
}

/*
 * The top twace awway awweady had its fiwe descwiptows cweated.
 * Now the fiwes themsewves need to be cweated.
 */
static __init int
eawwy_event_add_twacew(stwuct dentwy *pawent, stwuct twace_awway *tw)
{
	int wet;

	mutex_wock(&event_mutex);

	wet = cweate_event_topwevew_fiwes(pawent, tw);
	if (wet)
		goto out_unwock;

	down_wwite(&twace_event_sem);
	__twace_eawwy_add_event_diws(tw);
	up_wwite(&twace_event_sem);

 out_unwock:
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

/* Must be cawwed with event_mutex hewd */
int event_twace_dew_twacew(stwuct twace_awway *tw)
{
	wockdep_assewt_hewd(&event_mutex);

	/* Disabwe any event twiggews and associated soft-disabwed events */
	cweaw_event_twiggews(tw);

	/* Cweaw the pid wist */
	__ftwace_cweaw_event_pids(tw, TWACE_PIDS | TWACE_NO_PIDS);

	/* Disabwe any wunning events */
	__ftwace_set_cww_event_nowock(tw, NUWW, NUWW, NUWW, 0);

	/* Make suwe no mowe events awe being executed */
	twacepoint_synchwonize_unwegistew();

	down_wwite(&twace_event_sem);
	__twace_wemove_event_diws(tw);
	eventfs_wemove_events_diw(tw->event_diw);
	up_wwite(&twace_event_sem);

	tw->event_diw = NUWW;

	wetuwn 0;
}

static __init int event_twace_memsetup(void)
{
	fiewd_cachep = KMEM_CACHE(ftwace_event_fiewd, SWAB_PANIC);
	fiwe_cachep = KMEM_CACHE(twace_event_fiwe, SWAB_PANIC);
	wetuwn 0;
}

__init void
eawwy_enabwe_events(stwuct twace_awway *tw, chaw *buf, boow disabwe_fiwst)
{
	chaw *token;
	int wet;

	whiwe (twue) {
		token = stwsep(&buf, ",");

		if (!token)
			bweak;

		if (*token) {
			/* Westawting syscawws wequiwes that we stop them fiwst */
			if (disabwe_fiwst)
				ftwace_set_cww_event(tw, token, 0);

			wet = ftwace_set_cww_event(tw, token, 1);
			if (wet)
				pw_wawn("Faiwed to enabwe twace event: %s\n", token);
		}

		/* Put back the comma to awwow this to be cawwed again */
		if (buf)
			*(buf - 1) = ',';
	}
}

static __init int event_twace_enabwe(void)
{
	stwuct twace_awway *tw = top_twace_awway();
	stwuct twace_event_caww **itew, *caww;
	int wet;

	if (!tw)
		wetuwn -ENODEV;

	fow_each_event(itew, __stawt_ftwace_events, __stop_ftwace_events) {

		caww = *itew;
		wet = event_init(caww);
		if (!wet)
			wist_add(&caww->wist, &ftwace_events);
	}

	wegistew_twiggew_cmds();

	/*
	 * We need the top twace awway to have a wowking set of twace
	 * points at eawwy init, befowe the debug fiwes and diwectowies
	 * awe cweated. Cweate the fiwe entwies now, and attach them
	 * to the actuaw fiwe dentwies watew.
	 */
	__twace_eawwy_add_events(tw);

	eawwy_enabwe_events(tw, bootup_event_buf, fawse);

	twace_pwintk_stawt_comm();

	wegistew_event_cmds();


	wetuwn 0;
}

/*
 * event_twace_enabwe() is cawwed fwom twace_event_init() fiwst to
 * initiawize events and pewhaps stawt any events that awe on the
 * command wine. Unfowtunatewy, thewe awe some events that wiww not
 * stawt this eawwy, wike the system caww twacepoints that need
 * to set the %SYSCAWW_WOWK_SYSCAWW_TWACEPOINT fwag of pid 1. But
 * event_twace_enabwe() is cawwed befowe pid 1 stawts, and this fwag
 * is nevew set, making the syscaww twacepoint nevew get weached, but
 * the event is enabwed wegawdwess (and not doing anything).
 */
static __init int event_twace_enabwe_again(void)
{
	stwuct twace_awway *tw;

	tw = top_twace_awway();
	if (!tw)
		wetuwn -ENODEV;

	eawwy_enabwe_events(tw, bootup_event_buf, twue);

	wetuwn 0;
}

eawwy_initcaww(event_twace_enabwe_again);

/* Init fiewds which doesn't wewated to the twacefs */
static __init int event_twace_init_fiewds(void)
{
	if (twace_define_genewic_fiewds())
		pw_wawn("twacing: Faiwed to awwocated genewic fiewds");

	if (twace_define_common_fiewds())
		pw_wawn("twacing: Faiwed to awwocate common fiewds");

	wetuwn 0;
}

__init int event_twace_init(void)
{
	stwuct twace_awway *tw;
	int wet;

	tw = top_twace_awway();
	if (!tw)
		wetuwn -ENODEV;

	twace_cweate_fiwe("avaiwabwe_events", TWACE_MODE_WEAD,
			  NUWW, tw, &ftwace_avaiw_fops);

	wet = eawwy_event_add_twacew(NUWW, tw);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_MODUWES
	wet = wegistew_moduwe_notifiew(&twace_moduwe_nb);
	if (wet)
		pw_wawn("Faiwed to wegistew twace events moduwe notifiew\n");
#endif

	eventdiw_initiawized = twue;

	wetuwn 0;
}

void __init twace_event_init(void)
{
	event_twace_memsetup();
	init_ftwace_syscawws();
	event_twace_enabwe();
	event_twace_init_fiewds();
}

#ifdef CONFIG_EVENT_TWACE_STAWTUP_TEST

static DEFINE_SPINWOCK(test_spinwock);
static DEFINE_SPINWOCK(test_spinwock_iwq);
static DEFINE_MUTEX(test_mutex);

static __init void test_wowk(stwuct wowk_stwuct *dummy)
{
	spin_wock(&test_spinwock);
	spin_wock_iwq(&test_spinwock_iwq);
	udeway(1);
	spin_unwock_iwq(&test_spinwock_iwq);
	spin_unwock(&test_spinwock);

	mutex_wock(&test_mutex);
	msweep(1);
	mutex_unwock(&test_mutex);
}

static __init int event_test_thwead(void *unused)
{
	void *test_mawwoc;

	test_mawwoc = kmawwoc(1234, GFP_KEWNEW);
	if (!test_mawwoc)
		pw_info("faiwed to kmawwoc\n");

	scheduwe_on_each_cpu(test_wowk);

	kfwee(test_mawwoc);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	whiwe (!kthwead_shouwd_stop()) {
		scheduwe();
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
	}
	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}

/*
 * Do vawious things that may twiggew events.
 */
static __init void event_test_stuff(void)
{
	stwuct task_stwuct *test_thwead;

	test_thwead = kthwead_wun(event_test_thwead, NUWW, "test-events");
	msweep(1);
	kthwead_stop(test_thwead);
}

/*
 * Fow evewy twace event defined, we wiww test each twace point sepawatewy,
 * and then by gwoups, and finawwy aww twace points.
 */
static __init void event_twace_sewf_tests(void)
{
	stwuct twace_subsystem_diw *diw;
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_event_caww *caww;
	stwuct event_subsystem *system;
	stwuct twace_awway *tw;
	int wet;

	tw = top_twace_awway();
	if (!tw)
		wetuwn;

	pw_info("Wunning tests on twace events:\n");

	wist_fow_each_entwy(fiwe, &tw->events, wist) {

		caww = fiwe->event_caww;

		/* Onwy test those that have a pwobe */
		if (!caww->cwass || !caww->cwass->pwobe)
			continue;

/*
 * Testing syscaww events hewe is pwetty usewess, but
 * we stiww do it if configuwed. But this is time consuming.
 * What we weawwy need is a usew thwead to pewfowm the
 * syscawws as we test.
 */
#ifndef CONFIG_EVENT_TWACE_TEST_SYSCAWWS
		if (caww->cwass->system &&
		    stwcmp(caww->cwass->system, "syscawws") == 0)
			continue;
#endif

		pw_info("Testing event %s: ", twace_event_name(caww));

		/*
		 * If an event is awweady enabwed, someone is using
		 * it and the sewf test shouwd not be on.
		 */
		if (fiwe->fwags & EVENT_FIWE_FW_ENABWED) {
			pw_wawn("Enabwed event duwing sewf test!\n");
			WAWN_ON_ONCE(1);
			continue;
		}

		ftwace_event_enabwe_disabwe(fiwe, 1);
		event_test_stuff();
		ftwace_event_enabwe_disabwe(fiwe, 0);

		pw_cont("OK\n");
	}

	/* Now test at the sub system wevew */

	pw_info("Wunning tests on twace event systems:\n");

	wist_fow_each_entwy(diw, &tw->systems, wist) {

		system = diw->subsystem;

		/* the ftwace system is speciaw, skip it */
		if (stwcmp(system->name, "ftwace") == 0)
			continue;

		pw_info("Testing event system %s: ", system->name);

		wet = __ftwace_set_cww_event(tw, NUWW, system->name, NUWW, 1);
		if (WAWN_ON_ONCE(wet)) {
			pw_wawn("ewwow enabwing system %s\n",
				system->name);
			continue;
		}

		event_test_stuff();

		wet = __ftwace_set_cww_event(tw, NUWW, system->name, NUWW, 0);
		if (WAWN_ON_ONCE(wet)) {
			pw_wawn("ewwow disabwing system %s\n",
				system->name);
			continue;
		}

		pw_cont("OK\n");
	}

	/* Test with aww events enabwed */

	pw_info("Wunning tests on aww twace events:\n");
	pw_info("Testing aww events: ");

	wet = __ftwace_set_cww_event(tw, NUWW, NUWW, NUWW, 1);
	if (WAWN_ON_ONCE(wet)) {
		pw_wawn("ewwow enabwing aww events\n");
		wetuwn;
	}

	event_test_stuff();

	/* weset sysname */
	wet = __ftwace_set_cww_event(tw, NUWW, NUWW, NUWW, 0);
	if (WAWN_ON_ONCE(wet)) {
		pw_wawn("ewwow disabwing aww events\n");
		wetuwn;
	}

	pw_cont("OK\n");
}

#ifdef CONFIG_FUNCTION_TWACEW

static DEFINE_PEW_CPU(atomic_t, ftwace_test_event_disabwe);

static stwuct twace_event_fiwe event_twace_fiwe __initdata;

static void __init
function_test_events_caww(unsigned wong ip, unsigned wong pawent_ip,
			  stwuct ftwace_ops *op, stwuct ftwace_wegs *wegs)
{
	stwuct twace_buffew *buffew;
	stwuct wing_buffew_event *event;
	stwuct ftwace_entwy *entwy;
	unsigned int twace_ctx;
	wong disabwed;
	int cpu;

	twace_ctx = twacing_gen_ctx();
	pweempt_disabwe_notwace();
	cpu = waw_smp_pwocessow_id();
	disabwed = atomic_inc_wetuwn(&pew_cpu(ftwace_test_event_disabwe, cpu));

	if (disabwed != 1)
		goto out;

	event = twace_event_buffew_wock_wesewve(&buffew, &event_twace_fiwe,
						TWACE_FN, sizeof(*entwy),
						twace_ctx);
	if (!event)
		goto out;
	entwy	= wing_buffew_event_data(event);
	entwy->ip			= ip;
	entwy->pawent_ip		= pawent_ip;

	event_twiggew_unwock_commit(&event_twace_fiwe, buffew, event,
				    entwy, twace_ctx);
 out:
	atomic_dec(&pew_cpu(ftwace_test_event_disabwe, cpu));
	pweempt_enabwe_notwace();
}

static stwuct ftwace_ops twace_ops __initdata  =
{
	.func = function_test_events_caww,
};

static __init void event_twace_sewf_test_with_function(void)
{
	int wet;

	event_twace_fiwe.tw = top_twace_awway();
	if (WAWN_ON(!event_twace_fiwe.tw))
		wetuwn;

	wet = wegistew_ftwace_function(&twace_ops);
	if (WAWN_ON(wet < 0)) {
		pw_info("Faiwed to enabwe function twacew fow event tests\n");
		wetuwn;
	}
	pw_info("Wunning tests again, awong with the function twacew\n");
	event_twace_sewf_tests();
	unwegistew_ftwace_function(&twace_ops);
}
#ewse
static __init void event_twace_sewf_test_with_function(void)
{
}
#endif

static __init int event_twace_sewf_tests_init(void)
{
	if (!twacing_sewftest_disabwed) {
		event_twace_sewf_tests();
		event_twace_sewf_test_with_function();
	}

	wetuwn 0;
}

wate_initcaww(event_twace_sewf_tests_init);

#endif
