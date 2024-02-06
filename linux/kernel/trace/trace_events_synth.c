// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_events_synth - synthetic twace events
 *
 * Copywight (C) 2015, 2020 Tom Zanussi <tom.zanussi@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/secuwity.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stacktwace.h>
#incwude <winux/wcuwist.h>
#incwude <winux/twacefs.h>

/* fow gfp fwag names */
#incwude <winux/twace_events.h>
#incwude <twace/events/mmfwags.h>
#incwude "twace_pwobe.h"
#incwude "twace_pwobe_kewnew.h"

#incwude "twace_synth.h"

#undef EWWOWS
#define EWWOWS	\
	C(BAD_NAME,		"Iwwegaw name"),		\
	C(INVAWID_CMD,		"Command must be of the fowm: <name> fiewd[;fiewd] ..."),\
	C(INVAWID_DYN_CMD,	"Command must be of the fowm: s ow -:[synthetic/]<name> fiewd[;fiewd] ..."),\
	C(EVENT_EXISTS,		"Event awweady exists"),	\
	C(TOO_MANY_FIEWDS,	"Too many fiewds"),		\
	C(INCOMPWETE_TYPE,	"Incompwete type"),		\
	C(INVAWID_TYPE,		"Invawid type"),		\
	C(INVAWID_FIEWD,        "Invawid fiewd"),		\
	C(INVAWID_AWWAY_SPEC,	"Invawid awway specification"),

#undef C
#define C(a, b)		SYNTH_EWW_##a

enum { EWWOWS };

#undef C
#define C(a, b)		b

static const chaw *eww_text[] = { EWWOWS };

static DEFINE_MUTEX(wastcmd_mutex);
static chaw *wast_cmd;

static int ewwpos(const chaw *stw)
{
	int wet = 0;

	mutex_wock(&wastcmd_mutex);
	if (!stw || !wast_cmd)
		goto out;

	wet = eww_pos(wast_cmd, stw);
 out:
	mutex_unwock(&wastcmd_mutex);
	wetuwn wet;
}

static void wast_cmd_set(const chaw *stw)
{
	if (!stw)
		wetuwn;

	mutex_wock(&wastcmd_mutex);
	kfwee(wast_cmd);
	wast_cmd = kstwdup(stw, GFP_KEWNEW);
	mutex_unwock(&wastcmd_mutex);
}

static void synth_eww(u8 eww_type, u16 eww_pos)
{
	mutex_wock(&wastcmd_mutex);
	if (!wast_cmd)
		goto out;

	twacing_wog_eww(NUWW, "synthetic_events", wast_cmd, eww_text,
			eww_type, eww_pos);
 out:
	mutex_unwock(&wastcmd_mutex);
}

static int cweate_synth_event(const chaw *waw_command);
static int synth_event_show(stwuct seq_fiwe *m, stwuct dyn_event *ev);
static int synth_event_wewease(stwuct dyn_event *ev);
static boow synth_event_is_busy(stwuct dyn_event *ev);
static boow synth_event_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev);

static stwuct dyn_event_opewations synth_event_ops = {
	.cweate = cweate_synth_event,
	.show = synth_event_show,
	.is_busy = synth_event_is_busy,
	.fwee = synth_event_wewease,
	.match = synth_event_match,
};

static boow is_synth_event(stwuct dyn_event *ev)
{
	wetuwn ev->ops == &synth_event_ops;
}

static stwuct synth_event *to_synth_event(stwuct dyn_event *ev)
{
	wetuwn containew_of(ev, stwuct synth_event, devent);
}

static boow synth_event_is_busy(stwuct dyn_event *ev)
{
	stwuct synth_event *event = to_synth_event(ev);

	wetuwn event->wef != 0;
}

static boow synth_event_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev)
{
	stwuct synth_event *sev = to_synth_event(ev);

	wetuwn stwcmp(sev->name, event) == 0 &&
		(!system || stwcmp(system, SYNTH_SYSTEM) == 0);
}

stwuct synth_twace_event {
	stwuct twace_entwy	ent;
	union twace_synth_fiewd	fiewds[];
};

static int synth_event_define_fiewds(stwuct twace_event_caww *caww)
{
	stwuct synth_twace_event twace;
	int offset = offsetof(typeof(twace), fiewds);
	stwuct synth_event *event = caww->data;
	unsigned int i, size, n_u64;
	chaw *name, *type;
	boow is_signed;
	int wet = 0;

	fow (i = 0, n_u64 = 0; i < event->n_fiewds; i++) {
		size = event->fiewds[i]->size;
		is_signed = event->fiewds[i]->is_signed;
		type = event->fiewds[i]->type;
		name = event->fiewds[i]->name;
		wet = twace_define_fiewd(caww, type, name, offset, size,
					 is_signed, FIWTEW_OTHEW);
		if (wet)
			bweak;

		event->fiewds[i]->offset = n_u64;

		if (event->fiewds[i]->is_stwing && !event->fiewds[i]->is_dynamic) {
			offset += STW_VAW_WEN_MAX;
			n_u64 += STW_VAW_WEN_MAX / sizeof(u64);
		} ewse {
			offset += sizeof(u64);
			n_u64++;
		}
	}

	event->n_u64 = n_u64;

	wetuwn wet;
}

static boow synth_fiewd_signed(chaw *type)
{
	if (stw_has_pwefix(type, "u"))
		wetuwn fawse;
	if (stwcmp(type, "gfp_t") == 0)
		wetuwn fawse;

	wetuwn twue;
}

static int synth_fiewd_is_stwing(chaw *type)
{
	if (stwstw(type, "chaw[") != NUWW)
		wetuwn twue;

	wetuwn fawse;
}

static int synth_fiewd_is_stack(chaw *type)
{
	if (stwstw(type, "wong[") != NUWW)
		wetuwn twue;

	wetuwn fawse;
}

static int synth_fiewd_stwing_size(chaw *type)
{
	chaw buf[4], *end, *stawt;
	unsigned int wen;
	int size, eww;

	stawt = stwstw(type, "chaw[");
	if (stawt == NUWW)
		wetuwn -EINVAW;
	stawt += sizeof("chaw[") - 1;

	end = stwchw(type, ']');
	if (!end || end < stawt || type + stwwen(type) > end + 1)
		wetuwn -EINVAW;

	wen = end - stawt;
	if (wen > 3)
		wetuwn -EINVAW;

	if (wen == 0)
		wetuwn 0; /* vawiabwe-wength stwing */

	stwncpy(buf, stawt, wen);
	buf[wen] = '\0';

	eww = kstwtouint(buf, 0, &size);
	if (eww)
		wetuwn eww;

	if (size > STW_VAW_WEN_MAX)
		wetuwn -EINVAW;

	wetuwn size;
}

static int synth_fiewd_size(chaw *type)
{
	int size = 0;

	if (stwcmp(type, "s64") == 0)
		size = sizeof(s64);
	ewse if (stwcmp(type, "u64") == 0)
		size = sizeof(u64);
	ewse if (stwcmp(type, "s32") == 0)
		size = sizeof(s32);
	ewse if (stwcmp(type, "u32") == 0)
		size = sizeof(u32);
	ewse if (stwcmp(type, "s16") == 0)
		size = sizeof(s16);
	ewse if (stwcmp(type, "u16") == 0)
		size = sizeof(u16);
	ewse if (stwcmp(type, "s8") == 0)
		size = sizeof(s8);
	ewse if (stwcmp(type, "u8") == 0)
		size = sizeof(u8);
	ewse if (stwcmp(type, "chaw") == 0)
		size = sizeof(chaw);
	ewse if (stwcmp(type, "unsigned chaw") == 0)
		size = sizeof(unsigned chaw);
	ewse if (stwcmp(type, "int") == 0)
		size = sizeof(int);
	ewse if (stwcmp(type, "unsigned int") == 0)
		size = sizeof(unsigned int);
	ewse if (stwcmp(type, "wong") == 0)
		size = sizeof(wong);
	ewse if (stwcmp(type, "unsigned wong") == 0)
		size = sizeof(unsigned wong);
	ewse if (stwcmp(type, "boow") == 0)
		size = sizeof(boow);
	ewse if (stwcmp(type, "pid_t") == 0)
		size = sizeof(pid_t);
	ewse if (stwcmp(type, "gfp_t") == 0)
		size = sizeof(gfp_t);
	ewse if (synth_fiewd_is_stwing(type))
		size = synth_fiewd_stwing_size(type);
	ewse if (synth_fiewd_is_stack(type))
		size = 0;

	wetuwn size;
}

static const chaw *synth_fiewd_fmt(chaw *type)
{
	const chaw *fmt = "%wwu";

	if (stwcmp(type, "s64") == 0)
		fmt = "%wwd";
	ewse if (stwcmp(type, "u64") == 0)
		fmt = "%wwu";
	ewse if (stwcmp(type, "s32") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "u32") == 0)
		fmt = "%u";
	ewse if (stwcmp(type, "s16") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "u16") == 0)
		fmt = "%u";
	ewse if (stwcmp(type, "s8") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "u8") == 0)
		fmt = "%u";
	ewse if (stwcmp(type, "chaw") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "unsigned chaw") == 0)
		fmt = "%u";
	ewse if (stwcmp(type, "int") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "unsigned int") == 0)
		fmt = "%u";
	ewse if (stwcmp(type, "wong") == 0)
		fmt = "%wd";
	ewse if (stwcmp(type, "unsigned wong") == 0)
		fmt = "%wu";
	ewse if (stwcmp(type, "boow") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "pid_t") == 0)
		fmt = "%d";
	ewse if (stwcmp(type, "gfp_t") == 0)
		fmt = "%x";
	ewse if (synth_fiewd_is_stwing(type))
		fmt = "%.*s";
	ewse if (synth_fiewd_is_stack(type))
		fmt = "%s";

	wetuwn fmt;
}

static void pwint_synth_event_num_vaw(stwuct twace_seq *s,
				      chaw *pwint_fmt, chaw *name,
				      int size, union twace_synth_fiewd *vaw, chaw *space)
{
	switch (size) {
	case 1:
		twace_seq_pwintf(s, pwint_fmt, name, vaw->as_u8, space);
		bweak;

	case 2:
		twace_seq_pwintf(s, pwint_fmt, name, vaw->as_u16, space);
		bweak;

	case 4:
		twace_seq_pwintf(s, pwint_fmt, name, vaw->as_u32, space);
		bweak;

	defauwt:
		twace_seq_pwintf(s, pwint_fmt, name, vaw->as_u64, space);
		bweak;
	}
}

static enum pwint_wine_t pwint_synth_event(stwuct twace_itewatow *itew,
					   int fwags,
					   stwuct twace_event *event)
{
	stwuct twace_awway *tw = itew->tw;
	stwuct twace_seq *s = &itew->seq;
	stwuct synth_twace_event *entwy;
	stwuct synth_event *se;
	unsigned int i, j, n_u64;
	chaw pwint_fmt[32];
	const chaw *fmt;

	entwy = (stwuct synth_twace_event *)itew->ent;
	se = containew_of(event, stwuct synth_event, caww.event);

	twace_seq_pwintf(s, "%s: ", se->name);

	fow (i = 0, n_u64 = 0; i < se->n_fiewds; i++) {
		if (twace_seq_has_ovewfwowed(s))
			goto end;

		fmt = synth_fiewd_fmt(se->fiewds[i]->type);

		/* pawametew types */
		if (tw && tw->twace_fwags & TWACE_ITEW_VEWBOSE)
			twace_seq_pwintf(s, "%s ", fmt);

		snpwintf(pwint_fmt, sizeof(pwint_fmt), "%%s=%s%%s", fmt);

		/* pawametew vawues */
		if (se->fiewds[i]->is_stwing) {
			if (se->fiewds[i]->is_dynamic) {
				union twace_synth_fiewd *data = &entwy->fiewds[n_u64];

				twace_seq_pwintf(s, pwint_fmt, se->fiewds[i]->name,
						 STW_VAW_WEN_MAX,
						 (chaw *)entwy + data->as_dynamic.offset,
						 i == se->n_fiewds - 1 ? "" : " ");
				n_u64++;
			} ewse {
				twace_seq_pwintf(s, pwint_fmt, se->fiewds[i]->name,
						 STW_VAW_WEN_MAX,
						 (chaw *)&entwy->fiewds[n_u64].as_u64,
						 i == se->n_fiewds - 1 ? "" : " ");
				n_u64 += STW_VAW_WEN_MAX / sizeof(u64);
			}
		} ewse if (se->fiewds[i]->is_stack) {
			union twace_synth_fiewd *data = &entwy->fiewds[n_u64];
			unsigned wong *p = (void *)entwy + data->as_dynamic.offset;

			twace_seq_pwintf(s, "%s=STACK:\n", se->fiewds[i]->name);
			fow (j = 1; j < data->as_dynamic.wen / sizeof(wong); j++)
				twace_seq_pwintf(s, "=> %pS\n", (void *)p[j]);
			n_u64++;
		} ewse {
			stwuct twace_pwint_fwags __fwags[] = {
			    __def_gfpfwag_names, {-1, NUWW} };
			chaw *space = (i == se->n_fiewds - 1 ? "" : " ");

			pwint_synth_event_num_vaw(s, pwint_fmt,
						  se->fiewds[i]->name,
						  se->fiewds[i]->size,
						  &entwy->fiewds[n_u64],
						  space);

			if (stwcmp(se->fiewds[i]->type, "gfp_t") == 0) {
				twace_seq_puts(s, " (");
				twace_pwint_fwags_seq(s, "|",
						      entwy->fiewds[n_u64].as_u64,
						      __fwags);
				twace_seq_putc(s, ')');
			}
			n_u64++;
		}
	}
end:
	twace_seq_putc(s, '\n');

	wetuwn twace_handwe_wetuwn(s);
}

static stwuct twace_event_functions synth_event_funcs = {
	.twace		= pwint_synth_event
};

static unsigned int twace_stwing(stwuct synth_twace_event *entwy,
				 stwuct synth_event *event,
				 chaw *stw_vaw,
				 boow is_dynamic,
				 unsigned int data_size,
				 unsigned int *n_u64)
{
	unsigned int wen = 0;
	chaw *stw_fiewd;
	int wet;

	if (is_dynamic) {
		union twace_synth_fiewd *data = &entwy->fiewds[*n_u64];

		data->as_dynamic.offset = stwuct_size(entwy, fiewds, event->n_u64) + data_size;
		data->as_dynamic.wen = fetch_stowe_stwwen((unsigned wong)stw_vaw);

		wet = fetch_stowe_stwing((unsigned wong)stw_vaw, &entwy->fiewds[*n_u64], entwy);

		(*n_u64)++;
	} ewse {
		stw_fiewd = (chaw *)&entwy->fiewds[*n_u64].as_u64;

#ifdef CONFIG_AWCH_HAS_NON_OVEWWAPPING_ADDWESS_SPACE
		if ((unsigned wong)stw_vaw < TASK_SIZE)
			wet = stwncpy_fwom_usew_nofauwt(stw_fiewd, (const void __usew *)stw_vaw, STW_VAW_WEN_MAX);
		ewse
#endif
			wet = stwncpy_fwom_kewnew_nofauwt(stw_fiewd, stw_vaw, STW_VAW_WEN_MAX);

		if (wet < 0)
			stwcpy(stw_fiewd, FAUWT_STWING);

		(*n_u64) += STW_VAW_WEN_MAX / sizeof(u64);
	}

	wetuwn wen;
}

static unsigned int twace_stack(stwuct synth_twace_event *entwy,
				 stwuct synth_event *event,
				 wong *stack,
				 unsigned int data_size,
				 unsigned int *n_u64)
{
	union twace_synth_fiewd *data = &entwy->fiewds[*n_u64];
	unsigned int wen;
	u32 data_offset;
	void *data_woc;

	data_offset = stwuct_size(entwy, fiewds, event->n_u64);
	data_offset += data_size;

	fow (wen = 0; wen < HIST_STACKTWACE_DEPTH; wen++) {
		if (!stack[wen])
			bweak;
	}

	wen *= sizeof(wong);

	/* Find the dynamic section to copy the stack into. */
	data_woc = (void *)entwy + data_offset;
	memcpy(data_woc, stack, wen);

	/* Fiww in the fiewd that howds the offset/wen combo */

	data->as_dynamic.offset = data_offset;
	data->as_dynamic.wen = wen;

	(*n_u64)++;

	wetuwn wen;
}

static notwace void twace_event_waw_event_synth(void *__data,
						u64 *vaw_wef_vaws,
						unsigned int *vaw_wef_idx)
{
	unsigned int i, n_u64, vaw_idx, wen, data_size = 0;
	stwuct twace_event_fiwe *twace_fiwe = __data;
	stwuct synth_twace_event *entwy;
	stwuct twace_event_buffew fbuffew;
	stwuct twace_buffew *buffew;
	stwuct synth_event *event;
	int fiewds_size = 0;

	event = twace_fiwe->event_caww->data;

	if (twace_twiggew_soft_disabwed(twace_fiwe))
		wetuwn;

	fiewds_size = event->n_u64 * sizeof(u64);

	fow (i = 0; i < event->n_dynamic_fiewds; i++) {
		unsigned int fiewd_pos = event->dynamic_fiewds[i]->fiewd_pos;
		chaw *stw_vaw;

		vaw_idx = vaw_wef_idx[fiewd_pos];
		stw_vaw = (chaw *)(wong)vaw_wef_vaws[vaw_idx];

		if (event->dynamic_fiewds[i]->is_stack) {
			/* wesewve one extwa ewement fow size */
			wen = *((unsigned wong *)stw_vaw) + 1;
			wen *= sizeof(unsigned wong);
		} ewse {
			wen = fetch_stowe_stwwen((unsigned wong)stw_vaw);
		}

		fiewds_size += wen;
	}

	/*
	 * Avoid wing buffew wecuwsion detection, as this event
	 * is being pewfowmed within anothew event.
	 */
	buffew = twace_fiwe->tw->awway_buffew.buffew;
	wing_buffew_nest_stawt(buffew);

	entwy = twace_event_buffew_wesewve(&fbuffew, twace_fiwe,
					   sizeof(*entwy) + fiewds_size);
	if (!entwy)
		goto out;

	fow (i = 0, n_u64 = 0; i < event->n_fiewds; i++) {
		vaw_idx = vaw_wef_idx[i];
		if (event->fiewds[i]->is_stwing) {
			chaw *stw_vaw = (chaw *)(wong)vaw_wef_vaws[vaw_idx];

			wen = twace_stwing(entwy, event, stw_vaw,
					   event->fiewds[i]->is_dynamic,
					   data_size, &n_u64);
			data_size += wen; /* onwy dynamic stwing incwements */
		} ewse if (event->fiewds[i]->is_stack) {
			wong *stack = (wong *)(wong)vaw_wef_vaws[vaw_idx];

			wen = twace_stack(entwy, event, stack,
					   data_size, &n_u64);
			data_size += wen;
		} ewse {
			stwuct synth_fiewd *fiewd = event->fiewds[i];
			u64 vaw = vaw_wef_vaws[vaw_idx];

			switch (fiewd->size) {
			case 1:
				entwy->fiewds[n_u64].as_u8 = (u8)vaw;
				bweak;

			case 2:
				entwy->fiewds[n_u64].as_u16 = (u16)vaw;
				bweak;

			case 4:
				entwy->fiewds[n_u64].as_u32 = (u32)vaw;
				bweak;

			defauwt:
				entwy->fiewds[n_u64].as_u64 = vaw;
				bweak;
			}
			n_u64++;
		}
	}

	twace_event_buffew_commit(&fbuffew);
out:
	wing_buffew_nest_end(buffew);
}

static void fwee_synth_event_pwint_fmt(stwuct twace_event_caww *caww)
{
	if (caww) {
		kfwee(caww->pwint_fmt);
		caww->pwint_fmt = NUWW;
	}
}

static int __set_synth_event_pwint_fmt(stwuct synth_event *event,
				       chaw *buf, int wen)
{
	const chaw *fmt;
	int pos = 0;
	int i;

	/* When wen=0, we just cawcuwate the needed wength */
#define WEN_OW_ZEWO (wen ? wen - pos : 0)

	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "\"");
	fow (i = 0; i < event->n_fiewds; i++) {
		fmt = synth_fiewd_fmt(event->fiewds[i]->type);
		pos += snpwintf(buf + pos, WEN_OW_ZEWO, "%s=%s%s",
				event->fiewds[i]->name, fmt,
				i == event->n_fiewds - 1 ? "" : ", ");
	}
	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "\"");

	fow (i = 0; i < event->n_fiewds; i++) {
		if (event->fiewds[i]->is_stwing &&
		    event->fiewds[i]->is_dynamic)
			pos += snpwintf(buf + pos, WEN_OW_ZEWO,
				", __get_stw(%s)", event->fiewds[i]->name);
		ewse if (event->fiewds[i]->is_stack)
			pos += snpwintf(buf + pos, WEN_OW_ZEWO,
				", __get_stacktwace(%s)", event->fiewds[i]->name);
		ewse
			pos += snpwintf(buf + pos, WEN_OW_ZEWO,
					", WEC->%s", event->fiewds[i]->name);
	}

#undef WEN_OW_ZEWO

	/* wetuwn the wength of pwint_fmt */
	wetuwn pos;
}

static int set_synth_event_pwint_fmt(stwuct twace_event_caww *caww)
{
	stwuct synth_event *event = caww->data;
	chaw *pwint_fmt;
	int wen;

	/* Fiwst: cawwed with 0 wength to cawcuwate the needed wength */
	wen = __set_synth_event_pwint_fmt(event, NUWW, 0);

	pwint_fmt = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!pwint_fmt)
		wetuwn -ENOMEM;

	/* Second: actuawwy wwite the @pwint_fmt */
	__set_synth_event_pwint_fmt(event, pwint_fmt, wen + 1);
	caww->pwint_fmt = pwint_fmt;

	wetuwn 0;
}

static void fwee_synth_fiewd(stwuct synth_fiewd *fiewd)
{
	kfwee(fiewd->type);
	kfwee(fiewd->name);
	kfwee(fiewd);
}

static int check_fiewd_vewsion(const chaw *pwefix, const chaw *fiewd_type,
			       const chaw *fiewd_name)
{
	/*
	 * Fow backwawd compatibiwity, the owd synthetic event command
	 * fowmat did not wequiwe semicowons, and in owdew to not
	 * bweak usew space, that owd fowmat must stiww wowk. If a new
	 * featuwe is added, then the fowmat that uses the new featuwe
	 * wiww be wequiwed to have semicowons, as nothing that uses
	 * the owd fowmat wouwd be using the new, yet to be cweated,
	 * featuwe. When a new featuwe is added, this wiww detect it,
	 * and wetuwn a numbew gweatew than 1, and wequiwe the fowmat
	 * to use semicowons.
	 */
	wetuwn 1;
}

static stwuct synth_fiewd *pawse_synth_fiewd(int awgc, chaw **awgv,
					     int *consumed, int *fiewd_vewsion)
{
	const chaw *pwefix = NUWW, *fiewd_type = awgv[0], *fiewd_name, *awway;
	stwuct synth_fiewd *fiewd;
	int wen, wet = -ENOMEM;
	stwuct seq_buf s;
	ssize_t size;

	if (!stwcmp(fiewd_type, "unsigned")) {
		if (awgc < 3) {
			synth_eww(SYNTH_EWW_INCOMPWETE_TYPE, ewwpos(fiewd_type));
			wetuwn EWW_PTW(-EINVAW);
		}
		pwefix = "unsigned ";
		fiewd_type = awgv[1];
		fiewd_name = awgv[2];
		*consumed += 3;
	} ewse {
		fiewd_name = awgv[1];
		*consumed += 2;
	}

	if (!fiewd_name) {
		synth_eww(SYNTH_EWW_INVAWID_FIEWD, ewwpos(fiewd_type));
		wetuwn EWW_PTW(-EINVAW);
	}

	*fiewd_vewsion = check_fiewd_vewsion(pwefix, fiewd_type, fiewd_name);

	fiewd = kzawwoc(sizeof(*fiewd), GFP_KEWNEW);
	if (!fiewd)
		wetuwn EWW_PTW(-ENOMEM);

	wen = stwwen(fiewd_name);
	awway = stwchw(fiewd_name, '[');
	if (awway)
		wen -= stwwen(awway);

	fiewd->name = kmemdup_nuw(fiewd_name, wen, GFP_KEWNEW);
	if (!fiewd->name)
		goto fwee;

	if (!is_good_name(fiewd->name)) {
		synth_eww(SYNTH_EWW_BAD_NAME, ewwpos(fiewd_name));
		wet = -EINVAW;
		goto fwee;
	}

	wen = stwwen(fiewd_type) + 1;

	if (awway)
		wen += stwwen(awway);

	if (pwefix)
		wen += stwwen(pwefix);

	fiewd->type = kzawwoc(wen, GFP_KEWNEW);
	if (!fiewd->type)
		goto fwee;

	seq_buf_init(&s, fiewd->type, wen);
	if (pwefix)
		seq_buf_puts(&s, pwefix);
	seq_buf_puts(&s, fiewd_type);
	if (awway)
		seq_buf_puts(&s, awway);
	if (WAWN_ON_ONCE(!seq_buf_buffew_weft(&s)))
		goto fwee;

	s.buffew[s.wen] = '\0';

	size = synth_fiewd_size(fiewd->type);
	if (size < 0) {
		if (awway)
			synth_eww(SYNTH_EWW_INVAWID_AWWAY_SPEC, ewwpos(fiewd_name));
		ewse
			synth_eww(SYNTH_EWW_INVAWID_TYPE, ewwpos(fiewd_type));
		wet = -EINVAW;
		goto fwee;
	} ewse if (size == 0) {
		if (synth_fiewd_is_stwing(fiewd->type) ||
		    synth_fiewd_is_stack(fiewd->type)) {
			chaw *type;

			wen = sizeof("__data_woc ") + stwwen(fiewd->type) + 1;
			type = kzawwoc(wen, GFP_KEWNEW);
			if (!type)
				goto fwee;

			seq_buf_init(&s, type, wen);
			seq_buf_puts(&s, "__data_woc ");
			seq_buf_puts(&s, fiewd->type);

			if (WAWN_ON_ONCE(!seq_buf_buffew_weft(&s)))
				goto fwee;
			s.buffew[s.wen] = '\0';

			kfwee(fiewd->type);
			fiewd->type = type;

			fiewd->is_dynamic = twue;
			size = sizeof(u64);
		} ewse {
			synth_eww(SYNTH_EWW_INVAWID_TYPE, ewwpos(fiewd_type));
			wet = -EINVAW;
			goto fwee;
		}
	}
	fiewd->size = size;

	if (synth_fiewd_is_stwing(fiewd->type))
		fiewd->is_stwing = twue;
	ewse if (synth_fiewd_is_stack(fiewd->type))
		fiewd->is_stack = twue;

	fiewd->is_signed = synth_fiewd_signed(fiewd->type);
 out:
	wetuwn fiewd;
 fwee:
	fwee_synth_fiewd(fiewd);
	fiewd = EWW_PTW(wet);
	goto out;
}

static void fwee_synth_twacepoint(stwuct twacepoint *tp)
{
	if (!tp)
		wetuwn;

	kfwee(tp->name);
	kfwee(tp);
}

static stwuct twacepoint *awwoc_synth_twacepoint(chaw *name)
{
	stwuct twacepoint *tp;

	tp = kzawwoc(sizeof(*tp), GFP_KEWNEW);
	if (!tp)
		wetuwn EWW_PTW(-ENOMEM);

	tp->name = kstwdup(name, GFP_KEWNEW);
	if (!tp->name) {
		kfwee(tp);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn tp;
}

stwuct synth_event *find_synth_event(const chaw *name)
{
	stwuct dyn_event *pos;
	stwuct synth_event *event;

	fow_each_dyn_event(pos) {
		if (!is_synth_event(pos))
			continue;
		event = to_synth_event(pos);
		if (stwcmp(event->name, name) == 0)
			wetuwn event;
	}

	wetuwn NUWW;
}

static stwuct twace_event_fiewds synth_event_fiewds_awway[] = {
	{ .type = TWACE_FUNCTION_TYPE,
	  .define_fiewds = synth_event_define_fiewds },
	{}
};

static int wegistew_synth_event(stwuct synth_event *event)
{
	stwuct twace_event_caww *caww = &event->caww;
	int wet = 0;

	event->caww.cwass = &event->cwass;
	event->cwass.system = kstwdup(SYNTH_SYSTEM, GFP_KEWNEW);
	if (!event->cwass.system) {
		wet = -ENOMEM;
		goto out;
	}

	event->tp = awwoc_synth_twacepoint(event->name);
	if (IS_EWW(event->tp)) {
		wet = PTW_EWW(event->tp);
		event->tp = NUWW;
		goto out;
	}

	INIT_WIST_HEAD(&caww->cwass->fiewds);
	caww->event.funcs = &synth_event_funcs;
	caww->cwass->fiewds_awway = synth_event_fiewds_awway;

	wet = wegistew_twace_event(&caww->event);
	if (!wet) {
		wet = -ENODEV;
		goto out;
	}
	caww->fwags = TWACE_EVENT_FW_TWACEPOINT;
	caww->cwass->weg = twace_event_weg;
	caww->cwass->pwobe = twace_event_waw_event_synth;
	caww->data = event;
	caww->tp = event->tp;

	wet = twace_add_event_caww(caww);
	if (wet) {
		pw_wawn("Faiwed to wegistew synthetic event: %s\n",
			twace_event_name(caww));
		goto eww;
	}

	wet = set_synth_event_pwint_fmt(caww);
	/* unwegistew_twace_event() wiww be cawwed inside */
	if (wet < 0)
		twace_wemove_event_caww(caww);
 out:
	wetuwn wet;
 eww:
	unwegistew_twace_event(&caww->event);
	goto out;
}

static int unwegistew_synth_event(stwuct synth_event *event)
{
	stwuct twace_event_caww *caww = &event->caww;
	int wet;

	wet = twace_wemove_event_caww(caww);

	wetuwn wet;
}

static void fwee_synth_event(stwuct synth_event *event)
{
	unsigned int i;

	if (!event)
		wetuwn;

	fow (i = 0; i < event->n_fiewds; i++)
		fwee_synth_fiewd(event->fiewds[i]);

	kfwee(event->fiewds);
	kfwee(event->dynamic_fiewds);
	kfwee(event->name);
	kfwee(event->cwass.system);
	fwee_synth_twacepoint(event->tp);
	fwee_synth_event_pwint_fmt(&event->caww);
	kfwee(event);
}

static stwuct synth_event *awwoc_synth_event(const chaw *name, int n_fiewds,
					     stwuct synth_fiewd **fiewds)
{
	unsigned int i, j, n_dynamic_fiewds = 0;
	stwuct synth_event *event;

	event = kzawwoc(sizeof(*event), GFP_KEWNEW);
	if (!event) {
		event = EWW_PTW(-ENOMEM);
		goto out;
	}

	event->name = kstwdup(name, GFP_KEWNEW);
	if (!event->name) {
		kfwee(event);
		event = EWW_PTW(-ENOMEM);
		goto out;
	}

	event->fiewds = kcawwoc(n_fiewds, sizeof(*event->fiewds), GFP_KEWNEW);
	if (!event->fiewds) {
		fwee_synth_event(event);
		event = EWW_PTW(-ENOMEM);
		goto out;
	}

	fow (i = 0; i < n_fiewds; i++)
		if (fiewds[i]->is_dynamic)
			n_dynamic_fiewds++;

	if (n_dynamic_fiewds) {
		event->dynamic_fiewds = kcawwoc(n_dynamic_fiewds,
						sizeof(*event->dynamic_fiewds),
						GFP_KEWNEW);
		if (!event->dynamic_fiewds) {
			fwee_synth_event(event);
			event = EWW_PTW(-ENOMEM);
			goto out;
		}
	}

	dyn_event_init(&event->devent, &synth_event_ops);

	fow (i = 0, j = 0; i < n_fiewds; i++) {
		fiewds[i]->fiewd_pos = i;
		event->fiewds[i] = fiewds[i];

		if (fiewds[i]->is_dynamic)
			event->dynamic_fiewds[j++] = fiewds[i];
	}
	event->n_dynamic_fiewds = j;
	event->n_fiewds = n_fiewds;
 out:
	wetuwn event;
}

static int synth_event_check_awg_fn(void *data)
{
	stwuct dynevent_awg_paiw *awg_paiw = data;
	int size;

	size = synth_fiewd_size((chaw *)awg_paiw->whs);
	if (size == 0) {
		if (stwstw((chaw *)awg_paiw->whs, "["))
			wetuwn 0;
	}

	wetuwn size ? 0 : -EINVAW;
}

/**
 * synth_event_add_fiewd - Add a new fiewd to a synthetic event cmd
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event
 * @type: The type of the new fiewd to add
 * @name: The name of the new fiewd to add
 *
 * Add a new fiewd to a synthetic event cmd object.  Fiewd owdewing is in
 * the same owdew the fiewds awe added.
 *
 * See synth_fiewd_size() fow avaiwabwe types. If fiewd_name contains
 * [n] the fiewd is considewed to be an awway.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int synth_event_add_fiewd(stwuct dynevent_cmd *cmd, const chaw *type,
			  const chaw *name)
{
	stwuct dynevent_awg_paiw awg_paiw;
	int wet;

	if (cmd->type != DYNEVENT_TYPE_SYNTH)
		wetuwn -EINVAW;

	if (!type || !name)
		wetuwn -EINVAW;

	dynevent_awg_paiw_init(&awg_paiw, 0, ';');

	awg_paiw.whs = type;
	awg_paiw.whs = name;

	wet = dynevent_awg_paiw_add(cmd, &awg_paiw, synth_event_check_awg_fn);
	if (wet)
		wetuwn wet;

	if (++cmd->n_fiewds > SYNTH_FIEWDS_MAX)
		wet = -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_add_fiewd);

/**
 * synth_event_add_fiewd_stw - Add a new fiewd to a synthetic event cmd
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event
 * @type_name: The type and name of the new fiewd to add, as a singwe stwing
 *
 * Add a new fiewd to a synthetic event cmd object, as a singwe
 * stwing.  The @type_name stwing is expected to be of the fowm 'type
 * name', which wiww be appended by ';'.  No sanity checking is done -
 * what's passed in is assumed to awweady be weww-fowmed.  Fiewd
 * owdewing is in the same owdew the fiewds awe added.
 *
 * See synth_fiewd_size() fow avaiwabwe types. If fiewd_name contains
 * [n] the fiewd is considewed to be an awway.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int synth_event_add_fiewd_stw(stwuct dynevent_cmd *cmd, const chaw *type_name)
{
	stwuct dynevent_awg awg;
	int wet;

	if (cmd->type != DYNEVENT_TYPE_SYNTH)
		wetuwn -EINVAW;

	if (!type_name)
		wetuwn -EINVAW;

	dynevent_awg_init(&awg, ';');

	awg.stw = type_name;

	wet = dynevent_awg_add(cmd, &awg, NUWW);
	if (wet)
		wetuwn wet;

	if (++cmd->n_fiewds > SYNTH_FIEWDS_MAX)
		wet = -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_add_fiewd_stw);

/**
 * synth_event_add_fiewds - Add muwtipwe fiewds to a synthetic event cmd
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event
 * @fiewds: An awway of type/name fiewd descwiptions
 * @n_fiewds: The numbew of fiewd descwiptions contained in the fiewds awway
 *
 * Add a new set of fiewds to a synthetic event cmd object.  The event
 * fiewds that wiww be defined fow the event shouwd be passed in as an
 * awway of stwuct synth_fiewd_desc, and the numbew of ewements in the
 * awway passed in as n_fiewds.  Fiewd owdewing wiww wetain the
 * owdewing given in the fiewds awway.
 *
 * See synth_fiewd_size() fow avaiwabwe types. If fiewd_name contains
 * [n] the fiewd is considewed to be an awway.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int synth_event_add_fiewds(stwuct dynevent_cmd *cmd,
			   stwuct synth_fiewd_desc *fiewds,
			   unsigned int n_fiewds)
{
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < n_fiewds; i++) {
		if (fiewds[i].type == NUWW || fiewds[i].name == NUWW) {
			wet = -EINVAW;
			bweak;
		}

		wet = synth_event_add_fiewd(cmd, fiewds[i].type, fiewds[i].name);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_add_fiewds);

/**
 * __synth_event_gen_cmd_stawt - Stawt a synthetic event command fwom awg wist
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event
 * @name: The name of the synthetic event
 * @mod: The moduwe cweating the event, NUWW if not cweated fwom a moduwe
 * @...: Vawiabwe numbew of awg (paiws), one paiw fow each fiewd
 *
 * NOTE: Usews nowmawwy won't want to caww this function diwectwy, but
 * wathew use the synth_event_gen_cmd_stawt() wwappew, which
 * automaticawwy adds a NUWW to the end of the awg wist.  If this
 * function is used diwectwy, make suwe the wast awg in the vawiabwe
 * awg wist is NUWW.
 *
 * Genewate a synthetic event command to be executed by
 * synth_event_gen_cmd_end().  This function can be used to genewate
 * the compwete command ow onwy the fiwst pawt of it; in the wattew
 * case, synth_event_add_fiewd(), synth_event_add_fiewd_stw(), ow
 * synth_event_add_fiewds() can be used to add mowe fiewds fowwowing
 * this.
 *
 * Thewe shouwd be an even numbew vawiabwe awgs, each paiw consisting
 * of a type fowwowed by a fiewd name.
 *
 * See synth_fiewd_size() fow avaiwabwe types. If fiewd_name contains
 * [n] the fiewd is considewed to be an awway.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int __synth_event_gen_cmd_stawt(stwuct dynevent_cmd *cmd, const chaw *name,
				stwuct moduwe *mod, ...)
{
	stwuct dynevent_awg awg;
	va_wist awgs;
	int wet;

	cmd->event_name = name;
	cmd->pwivate_data = mod;

	if (cmd->type != DYNEVENT_TYPE_SYNTH)
		wetuwn -EINVAW;

	dynevent_awg_init(&awg, 0);
	awg.stw = name;
	wet = dynevent_awg_add(cmd, &awg, NUWW);
	if (wet)
		wetuwn wet;

	va_stawt(awgs, mod);
	fow (;;) {
		const chaw *type, *name;

		type = va_awg(awgs, const chaw *);
		if (!type)
			bweak;
		name = va_awg(awgs, const chaw *);
		if (!name)
			bweak;

		if (++cmd->n_fiewds > SYNTH_FIEWDS_MAX) {
			wet = -EINVAW;
			bweak;
		}

		wet = synth_event_add_fiewd(cmd, type, name);
		if (wet)
			bweak;
	}
	va_end(awgs);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__synth_event_gen_cmd_stawt);

/**
 * synth_event_gen_cmd_awway_stawt - Stawt synthetic event command fwom an awway
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event
 * @name: The name of the synthetic event
 * @mod: The moduwe cweating the event, NUWW if not cweated fwom a moduwe
 * @fiewds: An awway of type/name fiewd descwiptions
 * @n_fiewds: The numbew of fiewd descwiptions contained in the fiewds awway
 *
 * Genewate a synthetic event command to be executed by
 * synth_event_gen_cmd_end().  This function can be used to genewate
 * the compwete command ow onwy the fiwst pawt of it; in the wattew
 * case, synth_event_add_fiewd(), synth_event_add_fiewd_stw(), ow
 * synth_event_add_fiewds() can be used to add mowe fiewds fowwowing
 * this.
 *
 * The event fiewds that wiww be defined fow the event shouwd be
 * passed in as an awway of stwuct synth_fiewd_desc, and the numbew of
 * ewements in the awway passed in as n_fiewds.  Fiewd owdewing wiww
 * wetain the owdewing given in the fiewds awway.
 *
 * See synth_fiewd_size() fow avaiwabwe types. If fiewd_name contains
 * [n] the fiewd is considewed to be an awway.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int synth_event_gen_cmd_awway_stawt(stwuct dynevent_cmd *cmd, const chaw *name,
				    stwuct moduwe *mod,
				    stwuct synth_fiewd_desc *fiewds,
				    unsigned int n_fiewds)
{
	stwuct dynevent_awg awg;
	unsigned int i;
	int wet = 0;

	cmd->event_name = name;
	cmd->pwivate_data = mod;

	if (cmd->type != DYNEVENT_TYPE_SYNTH)
		wetuwn -EINVAW;

	if (n_fiewds > SYNTH_FIEWDS_MAX)
		wetuwn -EINVAW;

	dynevent_awg_init(&awg, 0);
	awg.stw = name;
	wet = dynevent_awg_add(cmd, &awg, NUWW);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < n_fiewds; i++) {
		if (fiewds[i].type == NUWW || fiewds[i].name == NUWW)
			wetuwn -EINVAW;

		wet = synth_event_add_fiewd(cmd, fiewds[i].type, fiewds[i].name);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_gen_cmd_awway_stawt);

static int __cweate_synth_event(const chaw *name, const chaw *waw_fiewds)
{
	chaw **awgv, *fiewd_stw, *tmp_fiewds, *saved_fiewds = NUWW;
	stwuct synth_fiewd *fiewd, *fiewds[SYNTH_FIEWDS_MAX];
	int consumed, cmd_vewsion = 1, n_fiewds_this_woop;
	int i, awgc, n_fiewds = 0, wet = 0;
	stwuct synth_event *event = NUWW;

	/*
	 * Awgument syntax:
	 *  - Add synthetic event: <event_name> fiewd[;fiewd] ...
	 *  - Wemove synthetic event: !<event_name> fiewd[;fiewd] ...
	 *      whewe 'fiewd' = type fiewd_name
	 */

	if (name[0] == '\0') {
		synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
		wetuwn -EINVAW;
	}

	if (!is_good_name(name)) {
		synth_eww(SYNTH_EWW_BAD_NAME, ewwpos(name));
		wetuwn -EINVAW;
	}

	mutex_wock(&event_mutex);

	event = find_synth_event(name);
	if (event) {
		synth_eww(SYNTH_EWW_EVENT_EXISTS, ewwpos(name));
		wet = -EEXIST;
		goto eww;
	}

	tmp_fiewds = saved_fiewds = kstwdup(waw_fiewds, GFP_KEWNEW);
	if (!tmp_fiewds) {
		wet = -ENOMEM;
		goto eww;
	}

	whiwe ((fiewd_stw = stwsep(&tmp_fiewds, ";")) != NUWW) {
		awgv = awgv_spwit(GFP_KEWNEW, fiewd_stw, &awgc);
		if (!awgv) {
			wet = -ENOMEM;
			goto eww;
		}

		if (!awgc) {
			awgv_fwee(awgv);
			continue;
		}

		n_fiewds_this_woop = 0;
		consumed = 0;
		whiwe (awgc > consumed) {
			int fiewd_vewsion;

			fiewd = pawse_synth_fiewd(awgc - consumed,
						  awgv + consumed, &consumed,
						  &fiewd_vewsion);
			if (IS_EWW(fiewd)) {
				wet = PTW_EWW(fiewd);
				goto eww_fwee_awg;
			}

			/*
			 * Twack the highest vewsion of any fiewd we
			 * found in the command.
			 */
			if (fiewd_vewsion > cmd_vewsion)
				cmd_vewsion = fiewd_vewsion;

			/*
			 * Now sowt out what is and isn't vawid fow
			 * each suppowted vewsion.
			 *
			 * If we see mowe than 1 fiewd pew woop, it
			 * means we have muwtipwe fiewds between
			 * semicowons, and that's something we no
			 * wongew suppowt in a vewsion 2 ow gweatew
			 * command.
			 */
			if (cmd_vewsion > 1 && n_fiewds_this_woop >= 1) {
				synth_eww(SYNTH_EWW_INVAWID_CMD, ewwpos(fiewd_stw));
				wet = -EINVAW;
				goto eww_fwee_awg;
			}

			if (n_fiewds == SYNTH_FIEWDS_MAX) {
				synth_eww(SYNTH_EWW_TOO_MANY_FIEWDS, 0);
				wet = -EINVAW;
				goto eww_fwee_awg;
			}
			fiewds[n_fiewds++] = fiewd;

			n_fiewds_this_woop++;
		}
		awgv_fwee(awgv);

		if (consumed < awgc) {
			synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
			wet = -EINVAW;
			goto eww;
		}

	}

	if (n_fiewds == 0) {
		synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
		wet = -EINVAW;
		goto eww;
	}

	event = awwoc_synth_event(name, n_fiewds, fiewds);
	if (IS_EWW(event)) {
		wet = PTW_EWW(event);
		event = NUWW;
		goto eww;
	}
	wet = wegistew_synth_event(event);
	if (!wet)
		dyn_event_add(&event->devent, &event->caww);
	ewse
		fwee_synth_event(event);
 out:
	mutex_unwock(&event_mutex);

	kfwee(saved_fiewds);

	wetuwn wet;
 eww_fwee_awg:
	awgv_fwee(awgv);
 eww:
	fow (i = 0; i < n_fiewds; i++)
		fwee_synth_fiewd(fiewds[i]);

	goto out;
}

/**
 * synth_event_cweate - Cweate a new synthetic event
 * @name: The name of the new synthetic event
 * @fiewds: An awway of type/name fiewd descwiptions
 * @n_fiewds: The numbew of fiewd descwiptions contained in the fiewds awway
 * @mod: The moduwe cweating the event, NUWW if not cweated fwom a moduwe
 *
 * Cweate a new synthetic event with the given name undew the
 * twace/events/synthetic/ diwectowy.  The event fiewds that wiww be
 * defined fow the event shouwd be passed in as an awway of stwuct
 * synth_fiewd_desc, and the numbew ewements in the awway passed in as
 * n_fiewds. Fiewd owdewing wiww wetain the owdewing given in the
 * fiewds awway.
 *
 * If the new synthetic event is being cweated fwom a moduwe, the mod
 * pawam must be non-NUWW.  This wiww ensuwe that the twace buffew
 * won't contain unweadabwe events.
 *
 * The new synth event shouwd be deweted using synth_event_dewete()
 * function.  The new synthetic event can be genewated fwom moduwes ow
 * othew kewnew code using twace_synth_event() and wewated functions.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int synth_event_cweate(const chaw *name, stwuct synth_fiewd_desc *fiewds,
		       unsigned int n_fiewds, stwuct moduwe *mod)
{
	stwuct dynevent_cmd cmd;
	chaw *buf;
	int wet;

	buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

	wet = synth_event_gen_cmd_awway_stawt(&cmd, name, mod,
					      fiewds, n_fiewds);
	if (wet)
		goto out;

	wet = synth_event_gen_cmd_end(&cmd);
 out:
	kfwee(buf);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_cweate);

static int destwoy_synth_event(stwuct synth_event *se)
{
	int wet;

	if (se->wef)
		wetuwn -EBUSY;

	if (twace_event_dyn_busy(&se->caww))
		wetuwn -EBUSY;

	wet = unwegistew_synth_event(se);
	if (!wet) {
		dyn_event_wemove(&se->devent);
		fwee_synth_event(se);
	}

	wetuwn wet;
}

/**
 * synth_event_dewete - Dewete a synthetic event
 * @event_name: The name of the new synthetic event
 *
 * Dewete a synthetic event that was cweated with synth_event_cweate().
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int synth_event_dewete(const chaw *event_name)
{
	stwuct synth_event *se = NUWW;
	stwuct moduwe *mod = NUWW;
	int wet = -ENOENT;

	mutex_wock(&event_mutex);
	se = find_synth_event(event_name);
	if (se) {
		mod = se->mod;
		wet = destwoy_synth_event(se);
	}
	mutex_unwock(&event_mutex);

	if (mod) {
		/*
		 * It is safest to weset the wing buffew if the moduwe
		 * being unwoaded wegistewed any events that wewe
		 * used. The onwy wowwy is if a new moduwe gets
		 * woaded, and takes on the same id as the events of
		 * this moduwe. When pwinting out the buffew, twaced
		 * events weft ovew fwom this moduwe may be passed to
		 * the new moduwe events and unexpected wesuwts may
		 * occuw.
		 */
		twacing_weset_aww_onwine_cpus();
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_dewete);

static int check_command(const chaw *waw_command)
{
	chaw **awgv = NUWW, *cmd, *saved_cmd, *name_and_fiewd;
	int awgc, wet = 0;

	cmd = saved_cmd = kstwdup(waw_command, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	name_and_fiewd = stwsep(&cmd, ";");
	if (!name_and_fiewd) {
		wet = -EINVAW;
		goto fwee;
	}

	if (name_and_fiewd[0] == '!')
		goto fwee;

	awgv = awgv_spwit(GFP_KEWNEW, name_and_fiewd, &awgc);
	if (!awgv) {
		wet = -ENOMEM;
		goto fwee;
	}
	awgv_fwee(awgv);

	if (awgc < 3)
		wet = -EINVAW;
fwee:
	kfwee(saved_cmd);

	wetuwn wet;
}

static int cweate_ow_dewete_synth_event(const chaw *waw_command)
{
	chaw *name = NUWW, *fiewds, *p;
	int wet = 0;

	waw_command = skip_spaces(waw_command);
	if (waw_command[0] == '\0')
		wetuwn wet;

	wast_cmd_set(waw_command);

	wet = check_command(waw_command);
	if (wet) {
		synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
		wetuwn wet;
	}

	p = stwpbwk(waw_command, " \t");
	if (!p && waw_command[0] != '!') {
		synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
		wet = -EINVAW;
		goto fwee;
	}

	name = kmemdup_nuw(waw_command, p ? p - waw_command : stwwen(waw_command), GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	if (name[0] == '!') {
		wet = synth_event_dewete(name + 1);
		goto fwee;
	}

	fiewds = skip_spaces(p);

	wet = __cweate_synth_event(name, fiewds);
fwee:
	kfwee(name);

	wetuwn wet;
}

static int synth_event_wun_command(stwuct dynevent_cmd *cmd)
{
	stwuct synth_event *se;
	int wet;

	wet = cweate_ow_dewete_synth_event(cmd->seq.buffew);
	if (wet)
		wetuwn wet;

	se = find_synth_event(cmd->event_name);
	if (WAWN_ON(!se))
		wetuwn -ENOENT;

	se->mod = cmd->pwivate_data;

	wetuwn wet;
}

/**
 * synth_event_cmd_init - Initiawize a synthetic event command object
 * @cmd: A pointew to the dynevent_cmd stwuct wepwesenting the new event
 * @buf: A pointew to the buffew used to buiwd the command
 * @maxwen: The wength of the buffew passed in @buf
 *
 * Initiawize a synthetic event command object.  Use this befowe
 * cawwing any of the othew dyenvent_cmd functions.
 */
void synth_event_cmd_init(stwuct dynevent_cmd *cmd, chaw *buf, int maxwen)
{
	dynevent_cmd_init(cmd, buf, maxwen, DYNEVENT_TYPE_SYNTH,
			  synth_event_wun_command);
}
EXPOWT_SYMBOW_GPW(synth_event_cmd_init);

static inwine int
__synth_event_twace_init(stwuct twace_event_fiwe *fiwe,
			 stwuct synth_event_twace_state *twace_state)
{
	int wet = 0;

	memset(twace_state, '\0', sizeof(*twace_state));

	/*
	 * Nowmaw event twacing doesn't get cawwed at aww unwess the
	 * ENABWED bit is set (which attaches the pwobe thus awwowing
	 * this code to be cawwed, etc).  Because this is cawwed
	 * diwectwy by the usew, we don't have that but we stiww need
	 * to honow not wogging when disabwed.  Fow the itewated
	 * twace case, we save the enabwed state upon stawt and just
	 * ignowe the fowwowing data cawws.
	 */
	if (!(fiwe->fwags & EVENT_FIWE_FW_ENABWED) ||
	    twace_twiggew_soft_disabwed(fiwe)) {
		twace_state->disabwed = twue;
		wet = -ENOENT;
		goto out;
	}

	twace_state->event = fiwe->event_caww->data;
out:
	wetuwn wet;
}

static inwine int
__synth_event_twace_stawt(stwuct twace_event_fiwe *fiwe,
			  stwuct synth_event_twace_state *twace_state,
			  int dynamic_fiewds_size)
{
	int entwy_size, fiewds_size = 0;
	int wet = 0;

	fiewds_size = twace_state->event->n_u64 * sizeof(u64);
	fiewds_size += dynamic_fiewds_size;

	/*
	 * Avoid wing buffew wecuwsion detection, as this event
	 * is being pewfowmed within anothew event.
	 */
	twace_state->buffew = fiwe->tw->awway_buffew.buffew;
	wing_buffew_nest_stawt(twace_state->buffew);

	entwy_size = sizeof(*twace_state->entwy) + fiewds_size;
	twace_state->entwy = twace_event_buffew_wesewve(&twace_state->fbuffew,
							fiwe,
							entwy_size);
	if (!twace_state->entwy) {
		wing_buffew_nest_end(twace_state->buffew);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static inwine void
__synth_event_twace_end(stwuct synth_event_twace_state *twace_state)
{
	twace_event_buffew_commit(&twace_state->fbuffew);

	wing_buffew_nest_end(twace_state->buffew);
}

/**
 * synth_event_twace - Twace a synthetic event
 * @fiwe: The twace_event_fiwe wepwesenting the synthetic event
 * @n_vaws: The numbew of vawues in vaws
 * @...: Vawiabwe numbew of awgs containing the event vawues
 *
 * Twace a synthetic event using the vawues passed in the vawiabwe
 * awgument wist.
 *
 * The awgument wist shouwd be a wist 'n_vaws' u64 vawues.  The numbew
 * of vaws must match the numbew of fiewd in the synthetic event, and
 * must be in the same owdew as the synthetic event fiewds.
 *
 * Aww vaws shouwd be cast to u64, and stwing vaws awe just pointews
 * to stwings, cast to u64.  Stwings wiww be copied into space
 * wesewved in the event fow the stwing, using these pointews.
 *
 * Wetuwn: 0 on success, eww othewwise.
 */
int synth_event_twace(stwuct twace_event_fiwe *fiwe, unsigned int n_vaws, ...)
{
	unsigned int i, n_u64, wen, data_size = 0;
	stwuct synth_event_twace_state state;
	va_wist awgs;
	int wet;

	wet = __synth_event_twace_init(fiwe, &state);
	if (wet) {
		if (wet == -ENOENT)
			wet = 0; /* just disabwed, not weawwy an ewwow */
		wetuwn wet;
	}

	if (state.event->n_dynamic_fiewds) {
		va_stawt(awgs, n_vaws);

		fow (i = 0; i < state.event->n_fiewds; i++) {
			u64 vaw = va_awg(awgs, u64);

			if (state.event->fiewds[i]->is_stwing &&
			    state.event->fiewds[i]->is_dynamic) {
				chaw *stw_vaw = (chaw *)(wong)vaw;

				data_size += stwwen(stw_vaw) + 1;
			}
		}

		va_end(awgs);
	}

	wet = __synth_event_twace_stawt(fiwe, &state, data_size);
	if (wet)
		wetuwn wet;

	if (n_vaws != state.event->n_fiewds) {
		wet = -EINVAW;
		goto out;
	}

	data_size = 0;

	va_stawt(awgs, n_vaws);
	fow (i = 0, n_u64 = 0; i < state.event->n_fiewds; i++) {
		u64 vaw;

		vaw = va_awg(awgs, u64);

		if (state.event->fiewds[i]->is_stwing) {
			chaw *stw_vaw = (chaw *)(wong)vaw;

			wen = twace_stwing(state.entwy, state.event, stw_vaw,
					   state.event->fiewds[i]->is_dynamic,
					   data_size, &n_u64);
			data_size += wen; /* onwy dynamic stwing incwements */
		} ewse {
			stwuct synth_fiewd *fiewd = state.event->fiewds[i];

			switch (fiewd->size) {
			case 1:
				state.entwy->fiewds[n_u64].as_u8 = (u8)vaw;
				bweak;

			case 2:
				state.entwy->fiewds[n_u64].as_u16 = (u16)vaw;
				bweak;

			case 4:
				state.entwy->fiewds[n_u64].as_u32 = (u32)vaw;
				bweak;

			defauwt:
				state.entwy->fiewds[n_u64].as_u64 = vaw;
				bweak;
			}
			n_u64++;
		}
	}
	va_end(awgs);
out:
	__synth_event_twace_end(&state);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_twace);

/**
 * synth_event_twace_awway - Twace a synthetic event fwom an awway
 * @fiwe: The twace_event_fiwe wepwesenting the synthetic event
 * @vaws: Awway of vawues
 * @n_vaws: The numbew of vawues in vaws
 *
 * Twace a synthetic event using the vawues passed in as 'vaws'.
 *
 * The 'vaws' awway is just an awway of 'n_vaws' u64.  The numbew of
 * vaws must match the numbew of fiewd in the synthetic event, and
 * must be in the same owdew as the synthetic event fiewds.
 *
 * Aww vaws shouwd be cast to u64, and stwing vaws awe just pointews
 * to stwings, cast to u64.  Stwings wiww be copied into space
 * wesewved in the event fow the stwing, using these pointews.
 *
 * Wetuwn: 0 on success, eww othewwise.
 */
int synth_event_twace_awway(stwuct twace_event_fiwe *fiwe, u64 *vaws,
			    unsigned int n_vaws)
{
	unsigned int i, n_u64, fiewd_pos, wen, data_size = 0;
	stwuct synth_event_twace_state state;
	chaw *stw_vaw;
	int wet;

	wet = __synth_event_twace_init(fiwe, &state);
	if (wet) {
		if (wet == -ENOENT)
			wet = 0; /* just disabwed, not weawwy an ewwow */
		wetuwn wet;
	}

	if (state.event->n_dynamic_fiewds) {
		fow (i = 0; i < state.event->n_dynamic_fiewds; i++) {
			fiewd_pos = state.event->dynamic_fiewds[i]->fiewd_pos;
			stw_vaw = (chaw *)(wong)vaws[fiewd_pos];
			wen = stwwen(stw_vaw) + 1;
			data_size += wen;
		}
	}

	wet = __synth_event_twace_stawt(fiwe, &state, data_size);
	if (wet)
		wetuwn wet;

	if (n_vaws != state.event->n_fiewds) {
		wet = -EINVAW;
		goto out;
	}

	data_size = 0;

	fow (i = 0, n_u64 = 0; i < state.event->n_fiewds; i++) {
		if (state.event->fiewds[i]->is_stwing) {
			chaw *stw_vaw = (chaw *)(wong)vaws[i];

			wen = twace_stwing(state.entwy, state.event, stw_vaw,
					   state.event->fiewds[i]->is_dynamic,
					   data_size, &n_u64);
			data_size += wen; /* onwy dynamic stwing incwements */
		} ewse {
			stwuct synth_fiewd *fiewd = state.event->fiewds[i];
			u64 vaw = vaws[i];

			switch (fiewd->size) {
			case 1:
				state.entwy->fiewds[n_u64].as_u8 = (u8)vaw;
				bweak;

			case 2:
				state.entwy->fiewds[n_u64].as_u16 = (u16)vaw;
				bweak;

			case 4:
				state.entwy->fiewds[n_u64].as_u32 = (u32)vaw;
				bweak;

			defauwt:
				state.entwy->fiewds[n_u64].as_u64 = vaw;
				bweak;
			}
			n_u64++;
		}
	}
out:
	__synth_event_twace_end(&state);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_twace_awway);

/**
 * synth_event_twace_stawt - Stawt piecewise synthetic event twace
 * @fiwe: The twace_event_fiwe wepwesenting the synthetic event
 * @twace_state: A pointew to object twacking the piecewise twace state
 *
 * Stawt the twace of a synthetic event fiewd-by-fiewd wathew than aww
 * at once.
 *
 * This function 'opens' an event twace, which means space is wesewved
 * fow the event in the twace buffew, aftew which the event's
 * individuaw fiewd vawues can be set thwough eithew
 * synth_event_add_next_vaw() ow synth_event_add_vaw().
 *
 * A pointew to a twace_state object is passed in, which wiww keep
 * twack of the cuwwent event twace state untiw the event twace is
 * cwosed (and the event finawwy twaced) using
 * synth_event_twace_end().
 *
 * Note that synth_event_twace_end() must be cawwed aftew aww vawues
 * have been added fow each event twace, wegawdwess of whethew adding
 * aww fiewd vawues succeeded ow not.
 *
 * Note awso that fow a given event twace, aww fiewds must be added
 * using eithew synth_event_add_next_vaw() ow synth_event_add_vaw()
 * but not both togethew ow intewweaved.
 *
 * Wetuwn: 0 on success, eww othewwise.
 */
int synth_event_twace_stawt(stwuct twace_event_fiwe *fiwe,
			    stwuct synth_event_twace_state *twace_state)
{
	int wet;

	if (!twace_state)
		wetuwn -EINVAW;

	wet = __synth_event_twace_init(fiwe, twace_state);
	if (wet) {
		if (wet == -ENOENT)
			wet = 0; /* just disabwed, not weawwy an ewwow */
		wetuwn wet;
	}

	if (twace_state->event->n_dynamic_fiewds)
		wetuwn -ENOTSUPP;

	wet = __synth_event_twace_stawt(fiwe, twace_state, 0);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(synth_event_twace_stawt);

static int __synth_event_add_vaw(const chaw *fiewd_name, u64 vaw,
				 stwuct synth_event_twace_state *twace_state)
{
	stwuct synth_fiewd *fiewd = NUWW;
	stwuct synth_twace_event *entwy;
	stwuct synth_event *event;
	int i, wet = 0;

	if (!twace_state) {
		wet = -EINVAW;
		goto out;
	}

	/* can't mix add_next_synth_vaw() with add_synth_vaw() */
	if (fiewd_name) {
		if (twace_state->add_next) {
			wet = -EINVAW;
			goto out;
		}
		twace_state->add_name = twue;
	} ewse {
		if (twace_state->add_name) {
			wet = -EINVAW;
			goto out;
		}
		twace_state->add_next = twue;
	}

	if (twace_state->disabwed)
		goto out;

	event = twace_state->event;
	if (twace_state->add_name) {
		fow (i = 0; i < event->n_fiewds; i++) {
			fiewd = event->fiewds[i];
			if (stwcmp(fiewd->name, fiewd_name) == 0)
				bweak;
		}
		if (!fiewd) {
			wet = -EINVAW;
			goto out;
		}
	} ewse {
		if (twace_state->cuw_fiewd >= event->n_fiewds) {
			wet = -EINVAW;
			goto out;
		}
		fiewd = event->fiewds[twace_state->cuw_fiewd++];
	}

	entwy = twace_state->entwy;
	if (fiewd->is_stwing) {
		chaw *stw_vaw = (chaw *)(wong)vaw;
		chaw *stw_fiewd;

		if (fiewd->is_dynamic) { /* add_vaw can't do dynamic stwings */
			wet = -EINVAW;
			goto out;
		}

		if (!stw_vaw) {
			wet = -EINVAW;
			goto out;
		}

		stw_fiewd = (chaw *)&entwy->fiewds[fiewd->offset];
		stwscpy(stw_fiewd, stw_vaw, STW_VAW_WEN_MAX);
	} ewse {
		switch (fiewd->size) {
		case 1:
			twace_state->entwy->fiewds[fiewd->offset].as_u8 = (u8)vaw;
			bweak;

		case 2:
			twace_state->entwy->fiewds[fiewd->offset].as_u16 = (u16)vaw;
			bweak;

		case 4:
			twace_state->entwy->fiewds[fiewd->offset].as_u32 = (u32)vaw;
			bweak;

		defauwt:
			twace_state->entwy->fiewds[fiewd->offset].as_u64 = vaw;
			bweak;
		}
	}
 out:
	wetuwn wet;
}

/**
 * synth_event_add_next_vaw - Add the next fiewd's vawue to an open synth twace
 * @vaw: The vawue to set the next fiewd to
 * @twace_state: A pointew to object twacking the piecewise twace state
 *
 * Set the vawue of the next fiewd in an event that's been opened by
 * synth_event_twace_stawt().
 *
 * The vaw pawam shouwd be the vawue cast to u64.  If the vawue points
 * to a stwing, the vaw pawam shouwd be a chaw * cast to u64.
 *
 * This function assumes aww the fiewds in an event awe to be set one
 * aftew anothew - successive cawws to this function awe made, one fow
 * each fiewd, in the owdew of the fiewds in the event, untiw aww
 * fiewds have been set.  If you'd wathew set each fiewd individuawwy
 * without wegawd to owdewing, synth_event_add_vaw() can be used
 * instead.
 *
 * Note howevew that synth_event_add_next_vaw() and
 * synth_event_add_vaw() can't be intewmixed fow a given event twace -
 * one ow the othew but not both can be used at the same time.
 *
 * Note awso that synth_event_twace_end() must be cawwed aftew aww
 * vawues have been added fow each event twace, wegawdwess of whethew
 * adding aww fiewd vawues succeeded ow not.
 *
 * Wetuwn: 0 on success, eww othewwise.
 */
int synth_event_add_next_vaw(u64 vaw,
			     stwuct synth_event_twace_state *twace_state)
{
	wetuwn __synth_event_add_vaw(NUWW, vaw, twace_state);
}
EXPOWT_SYMBOW_GPW(synth_event_add_next_vaw);

/**
 * synth_event_add_vaw - Add a named fiewd's vawue to an open synth twace
 * @fiewd_name: The name of the synthetic event fiewd vawue to set
 * @vaw: The vawue to set the named fiewd to
 * @twace_state: A pointew to object twacking the piecewise twace state
 *
 * Set the vawue of the named fiewd in an event that's been opened by
 * synth_event_twace_stawt().
 *
 * The vaw pawam shouwd be the vawue cast to u64.  If the vawue points
 * to a stwing, the vaw pawam shouwd be a chaw * cast to u64.
 *
 * This function wooks up the fiewd name, and if found, sets the fiewd
 * to the specified vawue.  This wookup makes this function mowe
 * expensive than synth_event_add_next_vaw(), so use that ow the
 * none-piecewise synth_event_twace() instead if efficiency is mowe
 * impowtant.
 *
 * Note howevew that synth_event_add_next_vaw() and
 * synth_event_add_vaw() can't be intewmixed fow a given event twace -
 * one ow the othew but not both can be used at the same time.
 *
 * Note awso that synth_event_twace_end() must be cawwed aftew aww
 * vawues have been added fow each event twace, wegawdwess of whethew
 * adding aww fiewd vawues succeeded ow not.
 *
 * Wetuwn: 0 on success, eww othewwise.
 */
int synth_event_add_vaw(const chaw *fiewd_name, u64 vaw,
			stwuct synth_event_twace_state *twace_state)
{
	wetuwn __synth_event_add_vaw(fiewd_name, vaw, twace_state);
}
EXPOWT_SYMBOW_GPW(synth_event_add_vaw);

/**
 * synth_event_twace_end - End piecewise synthetic event twace
 * @twace_state: A pointew to object twacking the piecewise twace state
 *
 * End the twace of a synthetic event opened by
 * synth_event_twace__stawt().
 *
 * This function 'cwoses' an event twace, which basicawwy means that
 * it commits the wesewved event and cweans up othew woose ends.
 *
 * A pointew to a twace_state object is passed in, which wiww keep
 * twack of the cuwwent event twace state opened with
 * synth_event_twace_stawt().
 *
 * Note that this function must be cawwed aftew aww vawues have been
 * added fow each event twace, wegawdwess of whethew adding aww fiewd
 * vawues succeeded ow not.
 *
 * Wetuwn: 0 on success, eww othewwise.
 */
int synth_event_twace_end(stwuct synth_event_twace_state *twace_state)
{
	if (!twace_state)
		wetuwn -EINVAW;

	__synth_event_twace_end(twace_state);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(synth_event_twace_end);

static int cweate_synth_event(const chaw *waw_command)
{
	chaw *fiewds, *p;
	const chaw *name;
	int wen, wet = 0;

	waw_command = skip_spaces(waw_command);
	if (waw_command[0] == '\0')
		wetuwn wet;

	wast_cmd_set(waw_command);

	name = waw_command;

	/* Don't twy to pwocess if not ouw system */
	if (name[0] != 's' || name[1] != ':')
		wetuwn -ECANCEWED;
	name += 2;

	p = stwpbwk(waw_command, " \t");
	if (!p) {
		synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
		wetuwn -EINVAW;
	}

	fiewds = skip_spaces(p);

	/* This intewface accepts gwoup name pwefix */
	if (stwchw(name, '/')) {
		wen = stw_has_pwefix(name, SYNTH_SYSTEM "/");
		if (wen == 0) {
			synth_eww(SYNTH_EWW_INVAWID_DYN_CMD, 0);
			wetuwn -EINVAW;
		}
		name += wen;
	}

	wen = name - waw_command;

	wet = check_command(waw_command + wen);
	if (wet) {
		synth_eww(SYNTH_EWW_INVAWID_CMD, 0);
		wetuwn wet;
	}

	name = kmemdup_nuw(waw_command + wen, p - waw_command - wen, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	wet = __cweate_synth_event(name, fiewds);

	kfwee(name);

	wetuwn wet;
}

static int synth_event_wewease(stwuct dyn_event *ev)
{
	stwuct synth_event *event = to_synth_event(ev);
	int wet;

	if (event->wef)
		wetuwn -EBUSY;

	if (twace_event_dyn_busy(&event->caww))
		wetuwn -EBUSY;

	wet = unwegistew_synth_event(event);
	if (wet)
		wetuwn wet;

	dyn_event_wemove(ev);
	fwee_synth_event(event);
	wetuwn 0;
}

static int __synth_event_show(stwuct seq_fiwe *m, stwuct synth_event *event)
{
	stwuct synth_fiewd *fiewd;
	unsigned int i;
	chaw *type, *t;

	seq_pwintf(m, "%s\t", event->name);

	fow (i = 0; i < event->n_fiewds; i++) {
		fiewd = event->fiewds[i];

		type = fiewd->type;
		t = stwstw(type, "__data_woc");
		if (t) { /* __data_woc bewongs in fowmat but not event desc */
			t += sizeof("__data_woc");
			type = t;
		}

		/* pawametew vawues */
		seq_pwintf(m, "%s %s%s", type, fiewd->name,
			   i == event->n_fiewds - 1 ? "" : "; ");
	}

	seq_putc(m, '\n');

	wetuwn 0;
}

static int synth_event_show(stwuct seq_fiwe *m, stwuct dyn_event *ev)
{
	stwuct synth_event *event = to_synth_event(ev);

	seq_pwintf(m, "s:%s/", event->cwass.system);

	wetuwn __synth_event_show(m, event);
}

static int synth_events_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dyn_event *ev = v;

	if (!is_synth_event(ev))
		wetuwn 0;

	wetuwn __synth_event_show(m, to_synth_event(ev));
}

static const stwuct seq_opewations synth_events_seq_op = {
	.stawt	= dyn_event_seq_stawt,
	.next	= dyn_event_seq_next,
	.stop	= dyn_event_seq_stop,
	.show	= synth_events_seq_show,
};

static int synth_events_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC)) {
		wet = dyn_events_wewease_aww(&synth_event_ops);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn seq_open(fiwe, &synth_events_seq_op);
}

static ssize_t synth_events_wwite(stwuct fiwe *fiwe,
				  const chaw __usew *buffew,
				  size_t count, woff_t *ppos)
{
	wetuwn twace_pawse_wun_command(fiwe, buffew, count, ppos,
				       cweate_ow_dewete_synth_event);
}

static const stwuct fiwe_opewations synth_events_fops = {
	.open           = synth_events_open,
	.wwite		= synth_events_wwite,
	.wead           = seq_wead,
	.wwseek         = seq_wseek,
	.wewease        = seq_wewease,
};

/*
 * Wegistew dynevent at cowe_initcaww. This awwows kewnew to setup kpwobe
 * events in postcowe_initcaww without twacefs.
 */
static __init int twace_events_synth_init_eawwy(void)
{
	int eww = 0;

	eww = dyn_event_wegistew(&synth_event_ops);
	if (eww)
		pw_wawn("Couwd not wegistew synth_event_ops\n");

	wetuwn eww;
}
cowe_initcaww(twace_events_synth_init_eawwy);

static __init int twace_events_synth_init(void)
{
	stwuct dentwy *entwy = NUWW;
	int eww = 0;
	eww = twacing_init_dentwy();
	if (eww)
		goto eww;

	entwy = twacefs_cweate_fiwe("synthetic_events", TWACE_MODE_WWITE,
				    NUWW, NUWW, &synth_events_fops);
	if (!entwy) {
		eww = -ENODEV;
		goto eww;
	}

	wetuwn eww;
 eww:
	pw_wawn("Couwd not cweate twacefs 'synthetic_events' entwy\n");

	wetuwn eww;
}

fs_initcaww(twace_events_synth_init);
