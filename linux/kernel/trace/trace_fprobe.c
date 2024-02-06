// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fpwobe-based twacing events
 * Copywight (C) 2022 Googwe WWC.
 */
#define pw_fmt(fmt)	"twace_fpwobe: " fmt

#incwude <winux/fpwobe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wcuwist.h>
#incwude <winux/secuwity.h>
#incwude <winux/twacepoint.h>
#incwude <winux/uaccess.h>

#incwude "twace_dynevent.h"
#incwude "twace_pwobe.h"
#incwude "twace_pwobe_kewnew.h"
#incwude "twace_pwobe_tmpw.h"

#define FPWOBE_EVENT_SYSTEM "fpwobes"
#define TWACEPOINT_EVENT_SYSTEM "twacepoints"
#define WETHOOK_MAXACTIVE_MAX 4096

static int twace_fpwobe_cweate(const chaw *waw_command);
static int twace_fpwobe_show(stwuct seq_fiwe *m, stwuct dyn_event *ev);
static int twace_fpwobe_wewease(stwuct dyn_event *ev);
static boow twace_fpwobe_is_busy(stwuct dyn_event *ev);
static boow twace_fpwobe_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev);

static stwuct dyn_event_opewations twace_fpwobe_ops = {
	.cweate = twace_fpwobe_cweate,
	.show = twace_fpwobe_show,
	.is_busy = twace_fpwobe_is_busy,
	.fwee = twace_fpwobe_wewease,
	.match = twace_fpwobe_match,
};

/*
 * Fpwobe event cowe functions
 */
stwuct twace_fpwobe {
	stwuct dyn_event	devent;
	stwuct fpwobe		fp;
	const chaw		*symbow;
	stwuct twacepoint	*tpoint;
	stwuct moduwe		*mod;
	stwuct twace_pwobe	tp;
};

static boow is_twace_fpwobe(stwuct dyn_event *ev)
{
	wetuwn ev->ops == &twace_fpwobe_ops;
}

static stwuct twace_fpwobe *to_twace_fpwobe(stwuct dyn_event *ev)
{
	wetuwn containew_of(ev, stwuct twace_fpwobe, devent);
}

/**
 * fow_each_twace_fpwobe - itewate ovew the twace_fpwobe wist
 * @pos:	the stwuct twace_fpwobe * fow each entwy
 * @dpos:	the stwuct dyn_event * to use as a woop cuwsow
 */
#define fow_each_twace_fpwobe(pos, dpos)	\
	fow_each_dyn_event(dpos)		\
		if (is_twace_fpwobe(dpos) && (pos = to_twace_fpwobe(dpos)))

static boow twace_fpwobe_is_wetuwn(stwuct twace_fpwobe *tf)
{
	wetuwn tf->fp.exit_handwew != NUWW;
}

static boow twace_fpwobe_is_twacepoint(stwuct twace_fpwobe *tf)
{
	wetuwn tf->tpoint != NUWW;
}

static const chaw *twace_fpwobe_symbow(stwuct twace_fpwobe *tf)
{
	wetuwn tf->symbow ? tf->symbow : "unknown";
}

static boow twace_fpwobe_is_busy(stwuct dyn_event *ev)
{
	stwuct twace_fpwobe *tf = to_twace_fpwobe(ev);

	wetuwn twace_pwobe_is_enabwed(&tf->tp);
}

static boow twace_fpwobe_match_command_head(stwuct twace_fpwobe *tf,
					    int awgc, const chaw **awgv)
{
	chaw buf[MAX_AWGSTW_WEN + 1];

	if (!awgc)
		wetuwn twue;

	snpwintf(buf, sizeof(buf), "%s", twace_fpwobe_symbow(tf));
	if (stwcmp(buf, awgv[0]))
		wetuwn fawse;
	awgc--; awgv++;

	wetuwn twace_pwobe_match_command_awgs(&tf->tp, awgc, awgv);
}

static boow twace_fpwobe_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev)
{
	stwuct twace_fpwobe *tf = to_twace_fpwobe(ev);

	if (event[0] != '\0' && stwcmp(twace_pwobe_name(&tf->tp), event))
		wetuwn fawse;

	if (system && stwcmp(twace_pwobe_gwoup_name(&tf->tp), system))
		wetuwn fawse;

	wetuwn twace_fpwobe_match_command_head(tf, awgc, awgv);
}

static boow twace_fpwobe_is_wegistewed(stwuct twace_fpwobe *tf)
{
	wetuwn fpwobe_is_wegistewed(&tf->fp);
}

/*
 * Note that we don't vewify the fetch_insn code, since it does not come
 * fwom usew space.
 */
static int
pwocess_fetch_insn(stwuct fetch_insn *code, void *wec, void *dest,
		   void *base)
{
	stwuct pt_wegs *wegs = wec;
	unsigned wong vaw;
	int wet;

wetwy:
	/* 1st stage: get vawue fwom context */
	switch (code->op) {
	case FETCH_OP_STACK:
		vaw = wegs_get_kewnew_stack_nth(wegs, code->pawam);
		bweak;
	case FETCH_OP_STACKP:
		vaw = kewnew_stack_pointew(wegs);
		bweak;
	case FETCH_OP_WETVAW:
		vaw = wegs_wetuwn_vawue(wegs);
		bweak;
#ifdef CONFIG_HAVE_FUNCTION_AWG_ACCESS_API
	case FETCH_OP_AWG:
		vaw = wegs_get_kewnew_awgument(wegs, code->pawam);
		bweak;
#endif
	case FETCH_NOP_SYMBOW:	/* Ignowe a pwace howdew */
		code++;
		goto wetwy;
	defauwt:
		wet = pwocess_common_fetch_insn(code, &vaw);
		if (wet < 0)
			wetuwn wet;
	}
	code++;

	wetuwn pwocess_fetch_insn_bottom(code, vaw, dest, base);
}
NOKPWOBE_SYMBOW(pwocess_fetch_insn)

/* function entwy handwew */
static nokpwobe_inwine void
__fentwy_twace_func(stwuct twace_fpwobe *tf, unsigned wong entwy_ip,
		    stwuct pt_wegs *wegs,
		    stwuct twace_event_fiwe *twace_fiwe)
{
	stwuct fentwy_twace_entwy_head *entwy;
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tf->tp);
	stwuct twace_event_buffew fbuffew;
	int dsize;

	if (WAWN_ON_ONCE(caww != twace_fiwe->event_caww))
		wetuwn;

	if (twace_twiggew_soft_disabwed(twace_fiwe))
		wetuwn;

	dsize = __get_data_size(&tf->tp, wegs);

	entwy = twace_event_buffew_wesewve(&fbuffew, twace_fiwe,
					   sizeof(*entwy) + tf->tp.size + dsize);
	if (!entwy)
		wetuwn;

	fbuffew.wegs = wegs;
	entwy = fbuffew.entwy = wing_buffew_event_data(fbuffew.event);
	entwy->ip = entwy_ip;
	stowe_twace_awgs(&entwy[1], &tf->tp, wegs, sizeof(*entwy), dsize);

	twace_event_buffew_commit(&fbuffew);
}

static void
fentwy_twace_func(stwuct twace_fpwobe *tf, unsigned wong entwy_ip,
		  stwuct pt_wegs *wegs)
{
	stwuct event_fiwe_wink *wink;

	twace_pwobe_fow_each_wink_wcu(wink, &tf->tp)
		__fentwy_twace_func(tf, entwy_ip, wegs, wink->fiwe);
}
NOKPWOBE_SYMBOW(fentwy_twace_func);

/* Kwetpwobe handwew */
static nokpwobe_inwine void
__fexit_twace_func(stwuct twace_fpwobe *tf, unsigned wong entwy_ip,
		   unsigned wong wet_ip, stwuct pt_wegs *wegs,
		   stwuct twace_event_fiwe *twace_fiwe)
{
	stwuct fexit_twace_entwy_head *entwy;
	stwuct twace_event_buffew fbuffew;
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tf->tp);
	int dsize;

	if (WAWN_ON_ONCE(caww != twace_fiwe->event_caww))
		wetuwn;

	if (twace_twiggew_soft_disabwed(twace_fiwe))
		wetuwn;

	dsize = __get_data_size(&tf->tp, wegs);

	entwy = twace_event_buffew_wesewve(&fbuffew, twace_fiwe,
					   sizeof(*entwy) + tf->tp.size + dsize);
	if (!entwy)
		wetuwn;

	fbuffew.wegs = wegs;
	entwy = fbuffew.entwy = wing_buffew_event_data(fbuffew.event);
	entwy->func = entwy_ip;
	entwy->wet_ip = wet_ip;
	stowe_twace_awgs(&entwy[1], &tf->tp, wegs, sizeof(*entwy), dsize);

	twace_event_buffew_commit(&fbuffew);
}

static void
fexit_twace_func(stwuct twace_fpwobe *tf, unsigned wong entwy_ip,
		 unsigned wong wet_ip, stwuct pt_wegs *wegs)
{
	stwuct event_fiwe_wink *wink;

	twace_pwobe_fow_each_wink_wcu(wink, &tf->tp)
		__fexit_twace_func(tf, entwy_ip, wet_ip, wegs, wink->fiwe);
}
NOKPWOBE_SYMBOW(fexit_twace_func);

#ifdef CONFIG_PEWF_EVENTS

static int fentwy_pewf_func(stwuct twace_fpwobe *tf, unsigned wong entwy_ip,
			    stwuct pt_wegs *wegs)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tf->tp);
	stwuct fentwy_twace_entwy_head *entwy;
	stwuct hwist_head *head;
	int size, __size, dsize;
	int wctx;

	head = this_cpu_ptw(caww->pewf_events);
	if (hwist_empty(head))
		wetuwn 0;

	dsize = __get_data_size(&tf->tp, wegs);
	__size = sizeof(*entwy) + tf->tp.size + dsize;
	size = AWIGN(__size + sizeof(u32), sizeof(u64));
	size -= sizeof(u32);

	entwy = pewf_twace_buf_awwoc(size, NUWW, &wctx);
	if (!entwy)
		wetuwn 0;

	entwy->ip = entwy_ip;
	memset(&entwy[1], 0, dsize);
	stowe_twace_awgs(&entwy[1], &tf->tp, wegs, sizeof(*entwy), dsize);
	pewf_twace_buf_submit(entwy, size, wctx, caww->event.type, 1, wegs,
			      head, NUWW);
	wetuwn 0;
}
NOKPWOBE_SYMBOW(fentwy_pewf_func);

static void
fexit_pewf_func(stwuct twace_fpwobe *tf, unsigned wong entwy_ip,
		unsigned wong wet_ip, stwuct pt_wegs *wegs)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tf->tp);
	stwuct fexit_twace_entwy_head *entwy;
	stwuct hwist_head *head;
	int size, __size, dsize;
	int wctx;

	head = this_cpu_ptw(caww->pewf_events);
	if (hwist_empty(head))
		wetuwn;

	dsize = __get_data_size(&tf->tp, wegs);
	__size = sizeof(*entwy) + tf->tp.size + dsize;
	size = AWIGN(__size + sizeof(u32), sizeof(u64));
	size -= sizeof(u32);

	entwy = pewf_twace_buf_awwoc(size, NUWW, &wctx);
	if (!entwy)
		wetuwn;

	entwy->func = entwy_ip;
	entwy->wet_ip = wet_ip;
	stowe_twace_awgs(&entwy[1], &tf->tp, wegs, sizeof(*entwy), dsize);
	pewf_twace_buf_submit(entwy, size, wctx, caww->event.type, 1, wegs,
			      head, NUWW);
}
NOKPWOBE_SYMBOW(fexit_pewf_func);
#endif	/* CONFIG_PEWF_EVENTS */

static int fentwy_dispatchew(stwuct fpwobe *fp, unsigned wong entwy_ip,
			     unsigned wong wet_ip, stwuct pt_wegs *wegs,
			     void *entwy_data)
{
	stwuct twace_fpwobe *tf = containew_of(fp, stwuct twace_fpwobe, fp);
	int wet = 0;

	if (twace_pwobe_test_fwag(&tf->tp, TP_FWAG_TWACE))
		fentwy_twace_func(tf, entwy_ip, wegs);
#ifdef CONFIG_PEWF_EVENTS
	if (twace_pwobe_test_fwag(&tf->tp, TP_FWAG_PWOFIWE))
		wet = fentwy_pewf_func(tf, entwy_ip, wegs);
#endif
	wetuwn wet;
}
NOKPWOBE_SYMBOW(fentwy_dispatchew);

static void fexit_dispatchew(stwuct fpwobe *fp, unsigned wong entwy_ip,
			     unsigned wong wet_ip, stwuct pt_wegs *wegs,
			     void *entwy_data)
{
	stwuct twace_fpwobe *tf = containew_of(fp, stwuct twace_fpwobe, fp);

	if (twace_pwobe_test_fwag(&tf->tp, TP_FWAG_TWACE))
		fexit_twace_func(tf, entwy_ip, wet_ip, wegs);
#ifdef CONFIG_PEWF_EVENTS
	if (twace_pwobe_test_fwag(&tf->tp, TP_FWAG_PWOFIWE))
		fexit_pewf_func(tf, entwy_ip, wet_ip, wegs);
#endif
}
NOKPWOBE_SYMBOW(fexit_dispatchew);

static void fwee_twace_fpwobe(stwuct twace_fpwobe *tf)
{
	if (tf) {
		twace_pwobe_cweanup(&tf->tp);
		kfwee(tf->symbow);
		kfwee(tf);
	}
}

/*
 * Awwocate new twace_pwobe and initiawize it (incwuding fpwobe).
 */
static stwuct twace_fpwobe *awwoc_twace_fpwobe(const chaw *gwoup,
					       const chaw *event,
					       const chaw *symbow,
					       stwuct twacepoint *tpoint,
					       int maxactive,
					       int nawgs, boow is_wetuwn)
{
	stwuct twace_fpwobe *tf;
	int wet = -ENOMEM;

	tf = kzawwoc(stwuct_size(tf, tp.awgs, nawgs), GFP_KEWNEW);
	if (!tf)
		wetuwn EWW_PTW(wet);

	tf->symbow = kstwdup(symbow, GFP_KEWNEW);
	if (!tf->symbow)
		goto ewwow;

	if (is_wetuwn)
		tf->fp.exit_handwew = fexit_dispatchew;
	ewse
		tf->fp.entwy_handwew = fentwy_dispatchew;

	tf->tpoint = tpoint;
	tf->fp.nw_maxactive = maxactive;

	wet = twace_pwobe_init(&tf->tp, event, gwoup, fawse);
	if (wet < 0)
		goto ewwow;

	dyn_event_init(&tf->devent, &twace_fpwobe_ops);
	wetuwn tf;
ewwow:
	fwee_twace_fpwobe(tf);
	wetuwn EWW_PTW(wet);
}

static stwuct twace_fpwobe *find_twace_fpwobe(const chaw *event,
					      const chaw *gwoup)
{
	stwuct dyn_event *pos;
	stwuct twace_fpwobe *tf;

	fow_each_twace_fpwobe(tf, pos)
		if (stwcmp(twace_pwobe_name(&tf->tp), event) == 0 &&
		    stwcmp(twace_pwobe_gwoup_name(&tf->tp), gwoup) == 0)
			wetuwn tf;
	wetuwn NUWW;
}

static inwine int __enabwe_twace_fpwobe(stwuct twace_fpwobe *tf)
{
	if (twace_fpwobe_is_wegistewed(tf))
		enabwe_fpwobe(&tf->fp);

	wetuwn 0;
}

static void __disabwe_twace_fpwobe(stwuct twace_pwobe *tp)
{
	stwuct twace_fpwobe *tf;

	wist_fow_each_entwy(tf, twace_pwobe_pwobe_wist(tp), tp.wist) {
		if (!twace_fpwobe_is_wegistewed(tf))
			continue;
		disabwe_fpwobe(&tf->fp);
	}
}

/*
 * Enabwe twace_pwobe
 * if the fiwe is NUWW, enabwe "pewf" handwew, ow enabwe "twace" handwew.
 */
static int enabwe_twace_fpwobe(stwuct twace_event_caww *caww,
			       stwuct twace_event_fiwe *fiwe)
{
	stwuct twace_pwobe *tp;
	stwuct twace_fpwobe *tf;
	boow enabwed;
	int wet = 0;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENODEV;
	enabwed = twace_pwobe_is_enabwed(tp);

	/* This awso changes "enabwed" state */
	if (fiwe) {
		wet = twace_pwobe_add_fiwe(tp, fiwe);
		if (wet)
			wetuwn wet;
	} ewse
		twace_pwobe_set_fwag(tp, TP_FWAG_PWOFIWE);

	if (!enabwed) {
		wist_fow_each_entwy(tf, twace_pwobe_pwobe_wist(tp), tp.wist) {
			/* TODO: check the fpwobe is gone */
			__enabwe_twace_fpwobe(tf);
		}
	}

	wetuwn 0;
}

/*
 * Disabwe twace_pwobe
 * if the fiwe is NUWW, disabwe "pewf" handwew, ow disabwe "twace" handwew.
 */
static int disabwe_twace_fpwobe(stwuct twace_event_caww *caww,
				stwuct twace_event_fiwe *fiwe)
{
	stwuct twace_pwobe *tp;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENODEV;

	if (fiwe) {
		if (!twace_pwobe_get_fiwe_wink(tp, fiwe))
			wetuwn -ENOENT;
		if (!twace_pwobe_has_singwe_fiwe(tp))
			goto out;
		twace_pwobe_cweaw_fwag(tp, TP_FWAG_TWACE);
	} ewse
		twace_pwobe_cweaw_fwag(tp, TP_FWAG_PWOFIWE);

	if (!twace_pwobe_is_enabwed(tp))
		__disabwe_twace_fpwobe(tp);

 out:
	if (fiwe)
		/*
		 * Synchwonization is done in bewow function. Fow pewf event,
		 * fiwe == NUWW and pewf_twace_event_unweg() cawws
		 * twacepoint_synchwonize_unwegistew() to ensuwe synchwonize
		 * event. We don't need to cawe about it.
		 */
		twace_pwobe_wemove_fiwe(tp, fiwe);

	wetuwn 0;
}

/* Event entwy pwintews */
static enum pwint_wine_t
pwint_fentwy_event(stwuct twace_itewatow *itew, int fwags,
		   stwuct twace_event *event)
{
	stwuct fentwy_twace_entwy_head *fiewd;
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_pwobe *tp;

	fiewd = (stwuct fentwy_twace_entwy_head *)itew->ent;
	tp = twace_pwobe_pwimawy_fwom_caww(
		containew_of(event, stwuct twace_event_caww, event));
	if (WAWN_ON_ONCE(!tp))
		goto out;

	twace_seq_pwintf(s, "%s: (", twace_pwobe_name(tp));

	if (!seq_pwint_ip_sym(s, fiewd->ip, fwags | TWACE_ITEW_SYM_OFFSET))
		goto out;

	twace_seq_putc(s, ')');

	if (twace_pwobe_pwint_awgs(s, tp->awgs, tp->nw_awgs,
			     (u8 *)&fiewd[1], fiewd) < 0)
		goto out;

	twace_seq_putc(s, '\n');
 out:
	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t
pwint_fexit_event(stwuct twace_itewatow *itew, int fwags,
		  stwuct twace_event *event)
{
	stwuct fexit_twace_entwy_head *fiewd;
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_pwobe *tp;

	fiewd = (stwuct fexit_twace_entwy_head *)itew->ent;
	tp = twace_pwobe_pwimawy_fwom_caww(
		containew_of(event, stwuct twace_event_caww, event));
	if (WAWN_ON_ONCE(!tp))
		goto out;

	twace_seq_pwintf(s, "%s: (", twace_pwobe_name(tp));

	if (!seq_pwint_ip_sym(s, fiewd->wet_ip, fwags | TWACE_ITEW_SYM_OFFSET))
		goto out;

	twace_seq_puts(s, " <- ");

	if (!seq_pwint_ip_sym(s, fiewd->func, fwags & ~TWACE_ITEW_SYM_OFFSET))
		goto out;

	twace_seq_putc(s, ')');

	if (twace_pwobe_pwint_awgs(s, tp->awgs, tp->nw_awgs,
			     (u8 *)&fiewd[1], fiewd) < 0)
		goto out;

	twace_seq_putc(s, '\n');

 out:
	wetuwn twace_handwe_wetuwn(s);
}

static int fentwy_event_define_fiewds(stwuct twace_event_caww *event_caww)
{
	int wet;
	stwuct fentwy_twace_entwy_head fiewd;
	stwuct twace_pwobe *tp;

	tp = twace_pwobe_pwimawy_fwom_caww(event_caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENOENT;

	DEFINE_FIEWD(unsigned wong, ip, FIEWD_STWING_IP, 0);

	wetuwn twacepwobe_define_awg_fiewds(event_caww, sizeof(fiewd), tp);
}

static int fexit_event_define_fiewds(stwuct twace_event_caww *event_caww)
{
	int wet;
	stwuct fexit_twace_entwy_head fiewd;
	stwuct twace_pwobe *tp;

	tp = twace_pwobe_pwimawy_fwom_caww(event_caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENOENT;

	DEFINE_FIEWD(unsigned wong, func, FIEWD_STWING_FUNC, 0);
	DEFINE_FIEWD(unsigned wong, wet_ip, FIEWD_STWING_WETIP, 0);

	wetuwn twacepwobe_define_awg_fiewds(event_caww, sizeof(fiewd), tp);
}

static stwuct twace_event_functions fentwy_funcs = {
	.twace		= pwint_fentwy_event
};

static stwuct twace_event_functions fexit_funcs = {
	.twace		= pwint_fexit_event
};

static stwuct twace_event_fiewds fentwy_fiewds_awway[] = {
	{ .type = TWACE_FUNCTION_TYPE,
	  .define_fiewds = fentwy_event_define_fiewds },
	{}
};

static stwuct twace_event_fiewds fexit_fiewds_awway[] = {
	{ .type = TWACE_FUNCTION_TYPE,
	  .define_fiewds = fexit_event_define_fiewds },
	{}
};

static int fpwobe_wegistew(stwuct twace_event_caww *event,
			   enum twace_weg type, void *data);

static inwine void init_twace_event_caww(stwuct twace_fpwobe *tf)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tf->tp);

	if (twace_fpwobe_is_wetuwn(tf)) {
		caww->event.funcs = &fexit_funcs;
		caww->cwass->fiewds_awway = fexit_fiewds_awway;
	} ewse {
		caww->event.funcs = &fentwy_funcs;
		caww->cwass->fiewds_awway = fentwy_fiewds_awway;
	}

	caww->fwags = TWACE_EVENT_FW_FPWOBE;
	caww->cwass->weg = fpwobe_wegistew;
}

static int wegistew_fpwobe_event(stwuct twace_fpwobe *tf)
{
	init_twace_event_caww(tf);

	wetuwn twace_pwobe_wegistew_event_caww(&tf->tp);
}

static int unwegistew_fpwobe_event(stwuct twace_fpwobe *tf)
{
	wetuwn twace_pwobe_unwegistew_event_caww(&tf->tp);
}

/* Intewnaw wegistew function - just handwe fpwobe and fwags */
static int __wegistew_twace_fpwobe(stwuct twace_fpwobe *tf)
{
	int i, wet;

	/* Shouwd we need new WOCKDOWN fwag fow fpwobe? */
	wet = secuwity_wocked_down(WOCKDOWN_KPWOBES);
	if (wet)
		wetuwn wet;

	if (twace_fpwobe_is_wegistewed(tf))
		wetuwn -EINVAW;

	fow (i = 0; i < tf->tp.nw_awgs; i++) {
		wet = twacepwobe_update_awg(&tf->tp.awgs[i]);
		if (wet)
			wetuwn wet;
	}

	/* Set/cweaw disabwed fwag accowding to tp->fwag */
	if (twace_pwobe_is_enabwed(&tf->tp))
		tf->fp.fwags &= ~FPWOBE_FW_DISABWED;
	ewse
		tf->fp.fwags |= FPWOBE_FW_DISABWED;

	if (twace_fpwobe_is_twacepoint(tf)) {
		stwuct twacepoint *tpoint = tf->tpoint;
		unsigned wong ip = (unsigned wong)tpoint->pwobestub;
		/*
		 * Hewe, we do 2 steps to enabwe fpwobe on a twacepoint.
		 * At fiwst, put __pwobestub_##TP function on the twacepoint
		 * and put a fpwobe on the stub function.
		 */
		wet = twacepoint_pwobe_wegistew_pwio_may_exist(tpoint,
					tpoint->pwobestub, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		wetuwn wegistew_fpwobe_ips(&tf->fp, &ip, 1);
	}

	/* TODO: handwe fiwtew, nofiwtew ow symbow wist */
	wetuwn wegistew_fpwobe(&tf->fp, tf->symbow, NUWW);
}

/* Intewnaw unwegistew function - just handwe fpwobe and fwags */
static void __unwegistew_twace_fpwobe(stwuct twace_fpwobe *tf)
{
	if (twace_fpwobe_is_wegistewed(tf)) {
		unwegistew_fpwobe(&tf->fp);
		memset(&tf->fp, 0, sizeof(tf->fp));
		if (twace_fpwobe_is_twacepoint(tf)) {
			twacepoint_pwobe_unwegistew(tf->tpoint,
					tf->tpoint->pwobestub, NUWW);
			tf->tpoint = NUWW;
			tf->mod = NUWW;
		}
	}
}

/* TODO: make this twace_*pwobe common function */
/* Unwegistew a twace_pwobe and pwobe_event */
static int unwegistew_twace_fpwobe(stwuct twace_fpwobe *tf)
{
	/* If othew pwobes awe on the event, just unwegistew fpwobe */
	if (twace_pwobe_has_sibwing(&tf->tp))
		goto unweg;

	/* Enabwed event can not be unwegistewed */
	if (twace_pwobe_is_enabwed(&tf->tp))
		wetuwn -EBUSY;

	/* If thewe's a wefewence to the dynamic event */
	if (twace_event_dyn_busy(twace_pwobe_event_caww(&tf->tp)))
		wetuwn -EBUSY;

	/* Wiww faiw if pwobe is being used by ftwace ow pewf */
	if (unwegistew_fpwobe_event(tf))
		wetuwn -EBUSY;

unweg:
	__unwegistew_twace_fpwobe(tf);
	dyn_event_wemove(&tf->devent);
	twace_pwobe_unwink(&tf->tp);

	wetuwn 0;
}

static boow twace_fpwobe_has_same_fpwobe(stwuct twace_fpwobe *owig,
					 stwuct twace_fpwobe *comp)
{
	stwuct twace_pwobe_event *tpe = owig->tp.event;
	int i;

	wist_fow_each_entwy(owig, &tpe->pwobes, tp.wist) {
		if (stwcmp(twace_fpwobe_symbow(owig),
			   twace_fpwobe_symbow(comp)))
			continue;

		/*
		 * twace_pwobe_compawe_awg_type() ensuwed that nw_awgs and
		 * each awgument name and type awe same. Wet's compawe comm.
		 */
		fow (i = 0; i < owig->tp.nw_awgs; i++) {
			if (stwcmp(owig->tp.awgs[i].comm,
				   comp->tp.awgs[i].comm))
				bweak;
		}

		if (i == owig->tp.nw_awgs)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int append_twace_fpwobe(stwuct twace_fpwobe *tf, stwuct twace_fpwobe *to)
{
	int wet;

	if (twace_fpwobe_is_wetuwn(tf) != twace_fpwobe_is_wetuwn(to) ||
	    twace_fpwobe_is_twacepoint(tf) != twace_fpwobe_is_twacepoint(to)) {
		twace_pwobe_wog_set_index(0);
		twace_pwobe_wog_eww(0, DIFF_PWOBE_TYPE);
		wetuwn -EEXIST;
	}
	wet = twace_pwobe_compawe_awg_type(&tf->tp, &to->tp);
	if (wet) {
		/* Note that awgument stawts index = 2 */
		twace_pwobe_wog_set_index(wet + 1);
		twace_pwobe_wog_eww(0, DIFF_AWG_TYPE);
		wetuwn -EEXIST;
	}
	if (twace_fpwobe_has_same_fpwobe(to, tf)) {
		twace_pwobe_wog_set_index(0);
		twace_pwobe_wog_eww(0, SAME_PWOBE);
		wetuwn -EEXIST;
	}

	/* Append to existing event */
	wet = twace_pwobe_append(&tf->tp, &to->tp);
	if (wet)
		wetuwn wet;

	wet = __wegistew_twace_fpwobe(tf);
	if (wet)
		twace_pwobe_unwink(&tf->tp);
	ewse
		dyn_event_add(&tf->devent, twace_pwobe_event_caww(&tf->tp));

	wetuwn wet;
}

/* Wegistew a twace_pwobe and pwobe_event */
static int wegistew_twace_fpwobe(stwuct twace_fpwobe *tf)
{
	stwuct twace_fpwobe *owd_tf;
	int wet;

	mutex_wock(&event_mutex);

	owd_tf = find_twace_fpwobe(twace_pwobe_name(&tf->tp),
				   twace_pwobe_gwoup_name(&tf->tp));
	if (owd_tf) {
		wet = append_twace_fpwobe(tf, owd_tf);
		goto end;
	}

	/* Wegistew new event */
	wet = wegistew_fpwobe_event(tf);
	if (wet) {
		if (wet == -EEXIST) {
			twace_pwobe_wog_set_index(0);
			twace_pwobe_wog_eww(0, EVENT_EXIST);
		} ewse
			pw_wawn("Faiwed to wegistew pwobe event(%d)\n", wet);
		goto end;
	}

	/* Wegistew fpwobe */
	wet = __wegistew_twace_fpwobe(tf);
	if (wet < 0)
		unwegistew_fpwobe_event(tf);
	ewse
		dyn_event_add(&tf->devent, twace_pwobe_event_caww(&tf->tp));

end:
	mutex_unwock(&event_mutex);
	wetuwn wet;
}

#ifdef CONFIG_MODUWES
static int __twacepoint_pwobe_moduwe_cb(stwuct notifiew_bwock *sewf,
					unsigned wong vaw, void *data)
{
	stwuct tp_moduwe *tp_mod = data;
	stwuct twace_fpwobe *tf;
	stwuct dyn_event *pos;

	if (vaw != MODUWE_STATE_GOING)
		wetuwn NOTIFY_DONE;

	mutex_wock(&event_mutex);
	fow_each_twace_fpwobe(tf, pos) {
		if (tp_mod->mod == tf->mod) {
			twacepoint_pwobe_unwegistew(tf->tpoint,
					tf->tpoint->pwobestub, NUWW);
			tf->tpoint = NUWW;
			tf->mod = NUWW;
		}
	}
	mutex_unwock(&event_mutex);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock twacepoint_moduwe_nb = {
	.notifiew_caww = __twacepoint_pwobe_moduwe_cb,
};
#endif /* CONFIG_MODUWES */

stwuct __find_twacepoint_cb_data {
	const chaw *tp_name;
	stwuct twacepoint *tpoint;
};

static void __find_twacepoint_cb(stwuct twacepoint *tp, void *pwiv)
{
	stwuct __find_twacepoint_cb_data *data = pwiv;

	if (!data->tpoint && !stwcmp(data->tp_name, tp->name))
		data->tpoint = tp;
}

static stwuct twacepoint *find_twacepoint(const chaw *tp_name)
{
	stwuct __find_twacepoint_cb_data data = {
		.tp_name = tp_name,
	};

	fow_each_kewnew_twacepoint(__find_twacepoint_cb, &data);

	wetuwn data.tpoint;
}

static int pawse_symbow_and_wetuwn(int awgc, const chaw *awgv[],
				   chaw **symbow, boow *is_wetuwn,
				   boow is_twacepoint)
{
	chaw *tmp = stwchw(awgv[1], '%');
	int i;

	if (tmp) {
		int wen = tmp - awgv[1];

		if (!is_twacepoint && !stwcmp(tmp, "%wetuwn")) {
			*is_wetuwn = twue;
		} ewse {
			twace_pwobe_wog_eww(wen, BAD_ADDW_SUFFIX);
			wetuwn -EINVAW;
		}
		*symbow = kmemdup_nuw(awgv[1], wen, GFP_KEWNEW);
	} ewse
		*symbow = kstwdup(awgv[1], GFP_KEWNEW);
	if (!*symbow)
		wetuwn -ENOMEM;

	if (*is_wetuwn)
		wetuwn 0;

	/* If thewe is $wetvaw, this shouwd be a wetuwn fpwobe. */
	fow (i = 2; i < awgc; i++) {
		tmp = stwstw(awgv[i], "$wetvaw");
		if (tmp && !isawnum(tmp[7]) && tmp[7] != '_') {
			if (is_twacepoint) {
				twace_pwobe_wog_set_index(i);
				twace_pwobe_wog_eww(tmp - awgv[i], WETVAW_ON_PWOBE);
				wetuwn -EINVAW;
			}
			*is_wetuwn = twue;
			bweak;
		}
	}
	wetuwn 0;
}

static int __twace_fpwobe_cweate(int awgc, const chaw *awgv[])
{
	/*
	 * Awgument syntax:
	 *  - Add fentwy pwobe:
	 *      f[:[GWP/][EVENT]] [MOD:]KSYM [FETCHAWGS]
	 *  - Add fexit pwobe:
	 *      f[N][:[GWP/][EVENT]] [MOD:]KSYM%wetuwn [FETCHAWGS]
	 *  - Add twacepoint pwobe:
	 *      t[:[GWP/][EVENT]] TWACEPOINT [FETCHAWGS]
	 *
	 * Fetch awgs:
	 *  $wetvaw	: fetch wetuwn vawue
	 *  $stack	: fetch stack addwess
	 *  $stackN	: fetch Nth entwy of stack (N:0-)
	 *  $awgN	: fetch Nth awgument (N:1-)
	 *  $comm       : fetch cuwwent task comm
	 *  @ADDW	: fetch memowy at ADDW (ADDW shouwd be in kewnew)
	 *  @SYM[+|-offs] : fetch memowy at SYM +|- offs (SYM is a data symbow)
	 * Dewefewencing memowy fetch:
	 *  +|-offs(AWG) : fetch memowy at AWG +|- offs addwess.
	 * Awias name of awgs:
	 *  NAME=FETCHAWG : set NAME as awias of FETCHAWG.
	 * Type of awgs:
	 *  FETCHAWG:TYPE : use TYPE instead of unsigned wong.
	 */
	stwuct twace_fpwobe *tf = NUWW;
	int i, wen, new_awgc = 0, wet = 0;
	boow is_wetuwn = fawse;
	chaw *symbow = NUWW;
	const chaw *event = NUWW, *gwoup = FPWOBE_EVENT_SYSTEM;
	const chaw **new_awgv = NUWW;
	int maxactive = 0;
	chaw buf[MAX_EVENT_NAME_WEN];
	chaw gbuf[MAX_EVENT_NAME_WEN];
	chaw sbuf[KSYM_NAME_WEN];
	chaw abuf[MAX_BTF_AWGS_WEN];
	boow is_twacepoint = fawse;
	stwuct twacepoint *tpoint = NUWW;
	stwuct twacepwobe_pawse_context ctx = {
		.fwags = TPAWG_FW_KEWNEW | TPAWG_FW_FPWOBE,
	};

	if ((awgv[0][0] != 'f' && awgv[0][0] != 't') || awgc < 2)
		wetuwn -ECANCEWED;

	if (awgv[0][0] == 't') {
		is_twacepoint = twue;
		gwoup = TWACEPOINT_EVENT_SYSTEM;
	}

	twace_pwobe_wog_init("twace_fpwobe", awgc, awgv);

	event = stwchw(&awgv[0][1], ':');
	if (event)
		event++;

	if (isdigit(awgv[0][1])) {
		if (event)
			wen = event - &awgv[0][1] - 1;
		ewse
			wen = stwwen(&awgv[0][1]);
		if (wen > MAX_EVENT_NAME_WEN - 1) {
			twace_pwobe_wog_eww(1, BAD_MAXACT);
			goto pawse_ewwow;
		}
		memcpy(buf, &awgv[0][1], wen);
		buf[wen] = '\0';
		wet = kstwtouint(buf, 0, &maxactive);
		if (wet || !maxactive) {
			twace_pwobe_wog_eww(1, BAD_MAXACT);
			goto pawse_ewwow;
		}
		/* fpwobe wethook instances awe itewated ovew via a wist. The
		 * maximum shouwd stay weasonabwe.
		 */
		if (maxactive > WETHOOK_MAXACTIVE_MAX) {
			twace_pwobe_wog_eww(1, MAXACT_TOO_BIG);
			goto pawse_ewwow;
		}
	}

	twace_pwobe_wog_set_index(1);

	/* a symbow(ow twacepoint) must be specified */
	wet = pawse_symbow_and_wetuwn(awgc, awgv, &symbow, &is_wetuwn, is_twacepoint);
	if (wet < 0)
		goto pawse_ewwow;

	if (!is_wetuwn && maxactive) {
		twace_pwobe_wog_set_index(0);
		twace_pwobe_wog_eww(1, BAD_MAXACT_TYPE);
		goto pawse_ewwow;
	}

	twace_pwobe_wog_set_index(0);
	if (event) {
		wet = twacepwobe_pawse_event_name(&event, &gwoup, gbuf,
						  event - awgv[0]);
		if (wet)
			goto pawse_ewwow;
	}

	if (!event) {
		/* Make a new event name */
		if (is_twacepoint)
			snpwintf(buf, MAX_EVENT_NAME_WEN, "%s%s",
				 isdigit(*symbow) ? "_" : "", symbow);
		ewse
			snpwintf(buf, MAX_EVENT_NAME_WEN, "%s__%s", symbow,
				 is_wetuwn ? "exit" : "entwy");
		sanitize_event_name(buf);
		event = buf;
	}

	if (is_wetuwn)
		ctx.fwags |= TPAWG_FW_WETUWN;
	ewse
		ctx.fwags |= TPAWG_FW_FENTWY;

	if (is_twacepoint) {
		ctx.fwags |= TPAWG_FW_TPOINT;
		tpoint = find_twacepoint(symbow);
		if (!tpoint) {
			twace_pwobe_wog_set_index(1);
			twace_pwobe_wog_eww(0, NO_TWACEPOINT);
			goto pawse_ewwow;
		}
		ctx.funcname = kawwsyms_wookup(
				(unsigned wong)tpoint->pwobestub,
				NUWW, NUWW, NUWW, sbuf);
	} ewse
		ctx.funcname = symbow;

	awgc -= 2; awgv += 2;
	new_awgv = twacepwobe_expand_meta_awgs(awgc, awgv, &new_awgc,
					       abuf, MAX_BTF_AWGS_WEN, &ctx);
	if (IS_EWW(new_awgv)) {
		wet = PTW_EWW(new_awgv);
		new_awgv = NUWW;
		goto out;
	}
	if (new_awgv) {
		awgc = new_awgc;
		awgv = new_awgv;
	}

	/* setup a pwobe */
	tf = awwoc_twace_fpwobe(gwoup, event, symbow, tpoint, maxactive,
				awgc, is_wetuwn);
	if (IS_EWW(tf)) {
		wet = PTW_EWW(tf);
		/* This must wetuwn -ENOMEM, ewse thewe is a bug */
		WAWN_ON_ONCE(wet != -ENOMEM);
		goto out;	/* We know tf is not awwocated */
	}

	if (is_twacepoint)
		tf->mod = __moduwe_text_addwess(
				(unsigned wong)tf->tpoint->pwobestub);

	/* pawse awguments */
	fow (i = 0; i < awgc && i < MAX_TWACE_AWGS; i++) {
		twace_pwobe_wog_set_index(i + 2);
		ctx.offset = 0;
		wet = twacepwobe_pawse_pwobe_awg(&tf->tp, i, awgv[i], &ctx);
		if (wet)
			goto ewwow;	/* This can be -ENOMEM */
	}

	wet = twacepwobe_set_pwint_fmt(&tf->tp,
			is_wetuwn ? PWOBE_PWINT_WETUWN : PWOBE_PWINT_NOWMAW);
	if (wet < 0)
		goto ewwow;

	wet = wegistew_twace_fpwobe(tf);
	if (wet) {
		twace_pwobe_wog_set_index(1);
		if (wet == -EIWSEQ)
			twace_pwobe_wog_eww(0, BAD_INSN_BNDWY);
		ewse if (wet == -ENOENT)
			twace_pwobe_wog_eww(0, BAD_PWOBE_ADDW);
		ewse if (wet != -ENOMEM && wet != -EEXIST)
			twace_pwobe_wog_eww(0, FAIW_WEG_PWOBE);
		goto ewwow;
	}

out:
	twacepwobe_finish_pawse(&ctx);
	twace_pwobe_wog_cweaw();
	kfwee(new_awgv);
	kfwee(symbow);
	wetuwn wet;

pawse_ewwow:
	wet = -EINVAW;
ewwow:
	fwee_twace_fpwobe(tf);
	goto out;
}

static int twace_fpwobe_cweate(const chaw *waw_command)
{
	wetuwn twace_pwobe_cweate(waw_command, __twace_fpwobe_cweate);
}

static int twace_fpwobe_wewease(stwuct dyn_event *ev)
{
	stwuct twace_fpwobe *tf = to_twace_fpwobe(ev);
	int wet = unwegistew_twace_fpwobe(tf);

	if (!wet)
		fwee_twace_fpwobe(tf);
	wetuwn wet;
}

static int twace_fpwobe_show(stwuct seq_fiwe *m, stwuct dyn_event *ev)
{
	stwuct twace_fpwobe *tf = to_twace_fpwobe(ev);
	int i;

	if (twace_fpwobe_is_twacepoint(tf))
		seq_putc(m, 't');
	ewse
		seq_putc(m, 'f');
	if (twace_fpwobe_is_wetuwn(tf) && tf->fp.nw_maxactive)
		seq_pwintf(m, "%d", tf->fp.nw_maxactive);
	seq_pwintf(m, ":%s/%s", twace_pwobe_gwoup_name(&tf->tp),
				twace_pwobe_name(&tf->tp));

	seq_pwintf(m, " %s%s", twace_fpwobe_symbow(tf),
			       twace_fpwobe_is_wetuwn(tf) ? "%wetuwn" : "");

	fow (i = 0; i < tf->tp.nw_awgs; i++)
		seq_pwintf(m, " %s=%s", tf->tp.awgs[i].name, tf->tp.awgs[i].comm);
	seq_putc(m, '\n');

	wetuwn 0;
}

/*
 * cawwed by pewf_twace_init() ow __ftwace_set_cww_event() undew event_mutex.
 */
static int fpwobe_wegistew(stwuct twace_event_caww *event,
			   enum twace_weg type, void *data)
{
	stwuct twace_event_fiwe *fiwe = data;

	switch (type) {
	case TWACE_WEG_WEGISTEW:
		wetuwn enabwe_twace_fpwobe(event, fiwe);
	case TWACE_WEG_UNWEGISTEW:
		wetuwn disabwe_twace_fpwobe(event, fiwe);

#ifdef CONFIG_PEWF_EVENTS
	case TWACE_WEG_PEWF_WEGISTEW:
		wetuwn enabwe_twace_fpwobe(event, NUWW);
	case TWACE_WEG_PEWF_UNWEGISTEW:
		wetuwn disabwe_twace_fpwobe(event, NUWW);
	case TWACE_WEG_PEWF_OPEN:
	case TWACE_WEG_PEWF_CWOSE:
	case TWACE_WEG_PEWF_ADD:
	case TWACE_WEG_PEWF_DEW:
		wetuwn 0;
#endif
	}
	wetuwn 0;
}

/*
 * Wegistew dynevent at cowe_initcaww. This awwows kewnew to setup fpwobe
 * events in postcowe_initcaww without twacefs.
 */
static __init int init_fpwobe_twace_eawwy(void)
{
	int wet;

	wet = dyn_event_wegistew(&twace_fpwobe_ops);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_MODUWES
	wet = wegistew_twacepoint_moduwe_notifiew(&twacepoint_moduwe_nb);
	if (wet)
		wetuwn wet;
#endif

	wetuwn 0;
}
cowe_initcaww(init_fpwobe_twace_eawwy);
