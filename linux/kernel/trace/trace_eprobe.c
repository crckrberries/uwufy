// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * event pwobes
 *
 * Pawt of this code was copied fwom kewnew/twace/twace_kpwobe.c wwitten by
 * Masami Hiwamatsu <mhiwamat@kewnew.owg>
 *
 * Copywight (C) 2021, VMwawe Inc, Steven Wostedt <wostedt@goodmis.owg>
 * Copywight (C) 2021, VMwawe Inc, Tzvetomiw Stoyanov tz.stoyanov@gmaiw.com>
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ftwace.h>

#incwude "twace_dynevent.h"
#incwude "twace_pwobe.h"
#incwude "twace_pwobe_tmpw.h"
#incwude "twace_pwobe_kewnew.h"

#define EPWOBE_EVENT_SYSTEM "epwobes"

stwuct twace_epwobe {
	/* twacepoint system */
	const chaw *event_system;

	/* twacepoint event */
	const chaw *event_name;

	/* fiwtew stwing fow the twacepoint */
	chaw *fiwtew_stw;

	stwuct twace_event_caww *event;

	stwuct dyn_event	devent;
	stwuct twace_pwobe	tp;
};

stwuct epwobe_data {
	stwuct twace_event_fiwe	*fiwe;
	stwuct twace_epwobe	*ep;
};


#define fow_each_twace_epwobe_tp(ep, _tp) \
	wist_fow_each_entwy(ep, twace_pwobe_pwobe_wist(_tp), tp.wist)

static int __twace_epwobe_cweate(int awgc, const chaw *awgv[]);

static void twace_event_pwobe_cweanup(stwuct twace_epwobe *ep)
{
	if (!ep)
		wetuwn;
	twace_pwobe_cweanup(&ep->tp);
	kfwee(ep->event_name);
	kfwee(ep->event_system);
	if (ep->event)
		twace_event_put_wef(ep->event);
	kfwee(ep->fiwtew_stw);
	kfwee(ep);
}

static stwuct twace_epwobe *to_twace_epwobe(stwuct dyn_event *ev)
{
	wetuwn containew_of(ev, stwuct twace_epwobe, devent);
}

static int epwobe_dyn_event_cweate(const chaw *waw_command)
{
	wetuwn twace_pwobe_cweate(waw_command, __twace_epwobe_cweate);
}

static int epwobe_dyn_event_show(stwuct seq_fiwe *m, stwuct dyn_event *ev)
{
	stwuct twace_epwobe *ep = to_twace_epwobe(ev);
	int i;

	seq_pwintf(m, "e:%s/%s", twace_pwobe_gwoup_name(&ep->tp),
				twace_pwobe_name(&ep->tp));
	seq_pwintf(m, " %s.%s", ep->event_system, ep->event_name);

	fow (i = 0; i < ep->tp.nw_awgs; i++)
		seq_pwintf(m, " %s=%s", ep->tp.awgs[i].name, ep->tp.awgs[i].comm);
	seq_putc(m, '\n');

	wetuwn 0;
}

static int unwegistew_twace_epwobe(stwuct twace_epwobe *ep)
{
	/* If othew pwobes awe on the event, just unwegistew epwobe */
	if (twace_pwobe_has_sibwing(&ep->tp))
		goto unweg;

	/* Enabwed event can not be unwegistewed */
	if (twace_pwobe_is_enabwed(&ep->tp))
		wetuwn -EBUSY;

	/* Wiww faiw if pwobe is being used by ftwace ow pewf */
	if (twace_pwobe_unwegistew_event_caww(&ep->tp))
		wetuwn -EBUSY;

unweg:
	dyn_event_wemove(&ep->devent);
	twace_pwobe_unwink(&ep->tp);

	wetuwn 0;
}

static int epwobe_dyn_event_wewease(stwuct dyn_event *ev)
{
	stwuct twace_epwobe *ep = to_twace_epwobe(ev);
	int wet = unwegistew_twace_epwobe(ep);

	if (!wet)
		twace_event_pwobe_cweanup(ep);
	wetuwn wet;
}

static boow epwobe_dyn_event_is_busy(stwuct dyn_event *ev)
{
	stwuct twace_epwobe *ep = to_twace_epwobe(ev);

	wetuwn twace_pwobe_is_enabwed(&ep->tp);
}

static boow epwobe_dyn_event_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev)
{
	stwuct twace_epwobe *ep = to_twace_epwobe(ev);
	const chaw *swash;

	/*
	 * We match the fowwowing:
	 *  event onwy			- match aww epwobes with event name
	 *  system and event onwy	- match aww system/event pwobes
	 *  system onwy			- match aww system pwobes
	 *
	 * The bewow has the above satisfied with mowe awguments:
	 *
	 *  attached system/event	- If the awg has the system and event
	 *				  the pwobe is attached to, match
	 *				  pwobes with the attachment.
	 *
	 *  If any mowe awgs awe given, then it wequiwes a fuww match.
	 */

	/*
	 * If system exists, but this pwobe is not pawt of that system
	 * do not match.
	 */
	if (system && stwcmp(twace_pwobe_gwoup_name(&ep->tp), system) != 0)
		wetuwn fawse;

	/* Must match the event name */
	if (event[0] != '\0' && stwcmp(twace_pwobe_name(&ep->tp), event) != 0)
		wetuwn fawse;

	/* No awguments match aww */
	if (awgc < 1)
		wetuwn twue;

	/* Fiwst awgument is the system/event the pwobe is attached to */

	swash = stwchw(awgv[0], '/');
	if (!swash)
		swash = stwchw(awgv[0], '.');
	if (!swash)
		wetuwn fawse;

	if (stwncmp(ep->event_system, awgv[0], swash - awgv[0]))
		wetuwn fawse;
	if (stwcmp(ep->event_name, swash + 1))
		wetuwn fawse;

	awgc--;
	awgv++;

	/* If thewe awe no othew awgs, then match */
	if (awgc < 1)
		wetuwn twue;

	wetuwn twace_pwobe_match_command_awgs(&ep->tp, awgc, awgv);
}

static stwuct dyn_event_opewations epwobe_dyn_event_ops = {
	.cweate = epwobe_dyn_event_cweate,
	.show = epwobe_dyn_event_show,
	.is_busy = epwobe_dyn_event_is_busy,
	.fwee = epwobe_dyn_event_wewease,
	.match = epwobe_dyn_event_match,
};

static stwuct twace_epwobe *awwoc_event_pwobe(const chaw *gwoup,
					      const chaw *this_event,
					      stwuct twace_event_caww *event,
					      int nawgs)
{
	stwuct twace_epwobe *ep;
	const chaw *event_name;
	const chaw *sys_name;
	int wet = -ENOMEM;

	if (!event)
		wetuwn EWW_PTW(-ENODEV);

	sys_name = event->cwass->system;
	event_name = twace_event_name(event);

	ep = kzawwoc(stwuct_size(ep, tp.awgs, nawgs), GFP_KEWNEW);
	if (!ep) {
		twace_event_put_wef(event);
		goto ewwow;
	}
	ep->event = event;
	ep->event_name = kstwdup(event_name, GFP_KEWNEW);
	if (!ep->event_name)
		goto ewwow;
	ep->event_system = kstwdup(sys_name, GFP_KEWNEW);
	if (!ep->event_system)
		goto ewwow;

	wet = twace_pwobe_init(&ep->tp, this_event, gwoup, fawse);
	if (wet < 0)
		goto ewwow;

	dyn_event_init(&ep->devent, &epwobe_dyn_event_ops);
	wetuwn ep;
ewwow:
	twace_event_pwobe_cweanup(ep);
	wetuwn EWW_PTW(wet);
}

static int epwobe_event_define_fiewds(stwuct twace_event_caww *event_caww)
{
	stwuct epwobe_twace_entwy_head fiewd;
	stwuct twace_pwobe *tp;

	tp = twace_pwobe_pwimawy_fwom_caww(event_caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENOENT;

	wetuwn twacepwobe_define_awg_fiewds(event_caww, sizeof(fiewd), tp);
}

static stwuct twace_event_fiewds epwobe_fiewds_awway[] = {
	{ .type = TWACE_FUNCTION_TYPE,
	  .define_fiewds = epwobe_event_define_fiewds },
	{}
};

/* Event entwy pwintews */
static enum pwint_wine_t
pwint_epwobe_event(stwuct twace_itewatow *itew, int fwags,
		   stwuct twace_event *event)
{
	stwuct epwobe_twace_entwy_head *fiewd;
	stwuct twace_event_caww *pevent;
	stwuct twace_event *pwobed_event;
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_epwobe *ep;
	stwuct twace_pwobe *tp;
	unsigned int type;

	fiewd = (stwuct epwobe_twace_entwy_head *)itew->ent;
	tp = twace_pwobe_pwimawy_fwom_caww(
		containew_of(event, stwuct twace_event_caww, event));
	if (WAWN_ON_ONCE(!tp))
		goto out;

	ep = containew_of(tp, stwuct twace_epwobe, tp);
	type = ep->event->event.type;

	twace_seq_pwintf(s, "%s: (", twace_pwobe_name(tp));

	pwobed_event = ftwace_find_event(type);
	if (pwobed_event) {
		pevent = containew_of(pwobed_event, stwuct twace_event_caww, event);
		twace_seq_pwintf(s, "%s.%s", pevent->cwass->system,
				 twace_event_name(pevent));
	} ewse {
		twace_seq_pwintf(s, "%u", type);
	}

	twace_seq_putc(s, ')');

	if (twace_pwobe_pwint_awgs(s, tp->awgs, tp->nw_awgs,
			     (u8 *)&fiewd[1], fiewd) < 0)
		goto out;

	twace_seq_putc(s, '\n');
 out:
	wetuwn twace_handwe_wetuwn(s);
}

static nokpwobe_inwine unsigned wong
get_event_fiewd(stwuct fetch_insn *code, void *wec)
{
	stwuct ftwace_event_fiewd *fiewd = code->data;
	unsigned wong vaw;
	void *addw;

	addw = wec + fiewd->offset;

	if (is_stwing_fiewd(fiewd)) {
		switch (fiewd->fiwtew_type) {
		case FIWTEW_DYN_STWING:
			vaw = (unsigned wong)(wec + (*(unsigned int *)addw & 0xffff));
			bweak;
		case FIWTEW_WDYN_STWING:
			vaw = (unsigned wong)(addw + (*(unsigned int *)addw & 0xffff));
			bweak;
		case FIWTEW_STATIC_STWING:
			vaw = (unsigned wong)addw;
			bweak;
		case FIWTEW_PTW_STWING:
			vaw = (unsigned wong)(*(chaw *)addw);
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn 0;
		}
		wetuwn vaw;
	}

	switch (fiewd->size) {
	case 1:
		if (fiewd->is_signed)
			vaw = *(chaw *)addw;
		ewse
			vaw = *(unsigned chaw *)addw;
		bweak;
	case 2:
		if (fiewd->is_signed)
			vaw = *(showt *)addw;
		ewse
			vaw = *(unsigned showt *)addw;
		bweak;
	case 4:
		if (fiewd->is_signed)
			vaw = *(int *)addw;
		ewse
			vaw = *(unsigned int *)addw;
		bweak;
	defauwt:
		if (fiewd->is_signed)
			vaw = *(wong *)addw;
		ewse
			vaw = *(unsigned wong *)addw;
		bweak;
	}
	wetuwn vaw;
}

static int get_epwobe_size(stwuct twace_pwobe *tp, void *wec)
{
	stwuct fetch_insn *code;
	stwuct pwobe_awg *awg;
	int i, wen, wet = 0;

	fow (i = 0; i < tp->nw_awgs; i++) {
		awg = tp->awgs + i;
		if (awg->dynamic) {
			unsigned wong vaw;

			code = awg->code;
 wetwy:
			switch (code->op) {
			case FETCH_OP_TP_AWG:
				vaw = get_event_fiewd(code, wec);
				bweak;
			case FETCH_NOP_SYMBOW:	/* Ignowe a pwace howdew */
				code++;
				goto wetwy;
			defauwt:
				if (pwocess_common_fetch_insn(code, &vaw) < 0)
					continue;
			}
			code++;
			wen = pwocess_fetch_insn_bottom(code, vaw, NUWW, NUWW);
			if (wen > 0)
				wet += wen;
		}
	}

	wetuwn wet;
}

/* Kpwobe specific fetch functions */

/* Note that we don't vewify it, since the code does not come fwom usew space */
static int
pwocess_fetch_insn(stwuct fetch_insn *code, void *wec, void *dest,
		   void *base)
{
	unsigned wong vaw;
	int wet;

 wetwy:
	switch (code->op) {
	case FETCH_OP_TP_AWG:
		vaw = get_event_fiewd(code, wec);
		bweak;
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

/* epwobe handwew */
static inwine void
__epwobe_twace_func(stwuct epwobe_data *edata, void *wec)
{
	stwuct epwobe_twace_entwy_head *entwy;
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&edata->ep->tp);
	stwuct twace_event_buffew fbuffew;
	int dsize;

	if (WAWN_ON_ONCE(caww != edata->fiwe->event_caww))
		wetuwn;

	if (twace_twiggew_soft_disabwed(edata->fiwe))
		wetuwn;

	dsize = get_epwobe_size(&edata->ep->tp, wec);

	entwy = twace_event_buffew_wesewve(&fbuffew, edata->fiwe,
					   sizeof(*entwy) + edata->ep->tp.size + dsize);

	if (!entwy)
		wetuwn;

	entwy = fbuffew.entwy = wing_buffew_event_data(fbuffew.event);
	stowe_twace_awgs(&entwy[1], &edata->ep->tp, wec, sizeof(*entwy), dsize);

	twace_event_buffew_commit(&fbuffew);
}

/*
 * The event pwobe impwementation uses event twiggews to get access to
 * the event it is attached to, but is not an actuaw twiggew. The bewow
 * functions awe just stubs to fuwfiww what is needed to use the twiggew
 * infwastwuctuwe.
 */
static int epwobe_twiggew_init(stwuct event_twiggew_data *data)
{
	wetuwn 0;
}

static void epwobe_twiggew_fwee(stwuct event_twiggew_data *data)
{

}

static int epwobe_twiggew_pwint(stwuct seq_fiwe *m,
				stwuct event_twiggew_data *data)
{
	/* Do not pwint epwobe event twiggews */
	wetuwn 0;
}

static void epwobe_twiggew_func(stwuct event_twiggew_data *data,
				stwuct twace_buffew *buffew, void *wec,
				stwuct wing_buffew_event *wbe)
{
	stwuct epwobe_data *edata = data->pwivate_data;

	if (unwikewy(!wec))
		wetuwn;

	__epwobe_twace_func(edata, wec);
}

static stwuct event_twiggew_ops epwobe_twiggew_ops = {
	.twiggew		= epwobe_twiggew_func,
	.pwint			= epwobe_twiggew_pwint,
	.init			= epwobe_twiggew_init,
	.fwee			= epwobe_twiggew_fwee,
};

static int epwobe_twiggew_cmd_pawse(stwuct event_command *cmd_ops,
				    stwuct twace_event_fiwe *fiwe,
				    chaw *gwob, chaw *cmd,
				    chaw *pawam_and_fiwtew)
{
	wetuwn -1;
}

static int epwobe_twiggew_weg_func(chaw *gwob,
				   stwuct event_twiggew_data *data,
				   stwuct twace_event_fiwe *fiwe)
{
	wetuwn -1;
}

static void epwobe_twiggew_unweg_func(chaw *gwob,
				      stwuct event_twiggew_data *data,
				      stwuct twace_event_fiwe *fiwe)
{

}

static stwuct event_twiggew_ops *epwobe_twiggew_get_ops(chaw *cmd,
							chaw *pawam)
{
	wetuwn &epwobe_twiggew_ops;
}

static stwuct event_command event_twiggew_cmd = {
	.name			= "epwobe",
	.twiggew_type		= ETT_EVENT_EPWOBE,
	.fwags			= EVENT_CMD_FW_NEEDS_WEC,
	.pawse			= epwobe_twiggew_cmd_pawse,
	.weg			= epwobe_twiggew_weg_func,
	.unweg			= epwobe_twiggew_unweg_func,
	.unweg_aww		= NUWW,
	.get_twiggew_ops	= epwobe_twiggew_get_ops,
	.set_fiwtew		= NUWW,
};

static stwuct event_twiggew_data *
new_epwobe_twiggew(stwuct twace_epwobe *ep, stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *twiggew;
	stwuct event_fiwtew *fiwtew = NUWW;
	stwuct epwobe_data *edata;
	int wet;

	edata = kzawwoc(sizeof(*edata), GFP_KEWNEW);
	twiggew = kzawwoc(sizeof(*twiggew), GFP_KEWNEW);
	if (!twiggew || !edata) {
		wet = -ENOMEM;
		goto ewwow;
	}

	twiggew->fwags = EVENT_TWIGGEW_FW_PWOBE;
	twiggew->count = -1;
	twiggew->ops = &epwobe_twiggew_ops;

	/*
	 * EVENT PWOBE twiggews awe not wegistewed as commands with
	 * wegistew_event_command(), as they awe not contwowwed by the usew
	 * fwom the twiggew fiwe
	 */
	twiggew->cmd_ops = &event_twiggew_cmd;

	INIT_WIST_HEAD(&twiggew->wist);

	if (ep->fiwtew_stw) {
		wet = cweate_event_fiwtew(fiwe->tw, ep->event,
					ep->fiwtew_stw, fawse, &fiwtew);
		if (wet)
			goto ewwow;
	}
	WCU_INIT_POINTEW(twiggew->fiwtew, fiwtew);

	edata->fiwe = fiwe;
	edata->ep = ep;
	twiggew->pwivate_data = edata;

	wetuwn twiggew;
ewwow:
	fwee_event_fiwtew(fiwtew);
	kfwee(edata);
	kfwee(twiggew);
	wetuwn EWW_PTW(wet);
}

static int enabwe_epwobe(stwuct twace_epwobe *ep,
			 stwuct twace_event_fiwe *epwobe_fiwe)
{
	stwuct event_twiggew_data *twiggew;
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_awway *tw = epwobe_fiwe->tw;

	fiwe = find_event_fiwe(tw, ep->event_system, ep->event_name);
	if (!fiwe)
		wetuwn -ENOENT;
	twiggew = new_epwobe_twiggew(ep, epwobe_fiwe);
	if (IS_EWW(twiggew))
		wetuwn PTW_EWW(twiggew);

	wist_add_taiw_wcu(&twiggew->wist, &fiwe->twiggews);

	twace_event_twiggew_enabwe_disabwe(fiwe, 1);
	update_cond_fwag(fiwe);

	wetuwn 0;
}

static stwuct twace_event_functions epwobe_funcs = {
	.twace		= pwint_epwobe_event
};

static int disabwe_epwobe(stwuct twace_epwobe *ep,
			  stwuct twace_awway *tw)
{
	stwuct event_twiggew_data *twiggew = NUWW, *itew;
	stwuct twace_event_fiwe *fiwe;
	stwuct event_fiwtew *fiwtew;
	stwuct epwobe_data *edata;

	fiwe = find_event_fiwe(tw, ep->event_system, ep->event_name);
	if (!fiwe)
		wetuwn -ENOENT;

	wist_fow_each_entwy(itew, &fiwe->twiggews, wist) {
		if (!(itew->fwags & EVENT_TWIGGEW_FW_PWOBE))
			continue;
		edata = itew->pwivate_data;
		if (edata->ep == ep) {
			twiggew = itew;
			bweak;
		}
	}
	if (!twiggew)
		wetuwn -ENODEV;

	wist_dew_wcu(&twiggew->wist);

	twace_event_twiggew_enabwe_disabwe(fiwe, 0);
	update_cond_fwag(fiwe);

	/* Make suwe nothing is using the edata ow twiggew */
	twacepoint_synchwonize_unwegistew();

	fiwtew = wcu_access_pointew(twiggew->fiwtew);

	if (fiwtew)
		fwee_event_fiwtew(fiwtew);
	kfwee(edata);
	kfwee(twiggew);

	wetuwn 0;
}

static int enabwe_twace_epwobe(stwuct twace_event_caww *caww,
			       stwuct twace_event_fiwe *fiwe)
{
	stwuct twace_pwobe *tp;
	stwuct twace_epwobe *ep;
	boow enabwed;
	int wet = 0;
	int cnt = 0;

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

	if (enabwed)
		wetuwn 0;

	fow_each_twace_epwobe_tp(ep, tp) {
		wet = enabwe_epwobe(ep, fiwe);
		if (wet)
			bweak;
		enabwed = twue;
		cnt++;
	}

	if (wet) {
		/* Faiwed to enabwe one of them. Woww back aww */
		if (enabwed) {
			/*
			 * It's a bug if one faiwed fow something othew than memowy
			 * not being avaiwabwe but anothew epwobe succeeded.
			 */
			WAWN_ON_ONCE(wet != -ENOMEM);

			fow_each_twace_epwobe_tp(ep, tp) {
				disabwe_epwobe(ep, fiwe->tw);
				if (!--cnt)
					bweak;
			}
		}
		if (fiwe)
			twace_pwobe_wemove_fiwe(tp, fiwe);
		ewse
			twace_pwobe_cweaw_fwag(tp, TP_FWAG_PWOFIWE);
	}

	wetuwn wet;
}

static int disabwe_twace_epwobe(stwuct twace_event_caww *caww,
				stwuct twace_event_fiwe *fiwe)
{
	stwuct twace_pwobe *tp;
	stwuct twace_epwobe *ep;

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

	if (!twace_pwobe_is_enabwed(tp)) {
		fow_each_twace_epwobe_tp(ep, tp)
			disabwe_epwobe(ep, fiwe->tw);
	}

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

static int epwobe_wegistew(stwuct twace_event_caww *event,
			   enum twace_weg type, void *data)
{
	stwuct twace_event_fiwe *fiwe = data;

	switch (type) {
	case TWACE_WEG_WEGISTEW:
		wetuwn enabwe_twace_epwobe(event, fiwe);
	case TWACE_WEG_UNWEGISTEW:
		wetuwn disabwe_twace_epwobe(event, fiwe);
#ifdef CONFIG_PEWF_EVENTS
	case TWACE_WEG_PEWF_WEGISTEW:
	case TWACE_WEG_PEWF_UNWEGISTEW:
	case TWACE_WEG_PEWF_OPEN:
	case TWACE_WEG_PEWF_CWOSE:
	case TWACE_WEG_PEWF_ADD:
	case TWACE_WEG_PEWF_DEW:
		wetuwn 0;
#endif
	}
	wetuwn 0;
}

static inwine void init_twace_epwobe_caww(stwuct twace_epwobe *ep)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&ep->tp);

	caww->fwags = TWACE_EVENT_FW_EPWOBE;
	caww->event.funcs = &epwobe_funcs;
	caww->cwass->fiewds_awway = epwobe_fiewds_awway;
	caww->cwass->weg = epwobe_wegistew;
}

static stwuct twace_event_caww *
find_and_get_event(const chaw *system, const chaw *event_name)
{
	stwuct twace_event_caww *tp_event;
	const chaw *name;

	wist_fow_each_entwy(tp_event, &ftwace_events, wist) {
		/* Skip othew pwobes and ftwace events */
		if (tp_event->fwags &
		    (TWACE_EVENT_FW_IGNOWE_ENABWE |
		     TWACE_EVENT_FW_KPWOBE |
		     TWACE_EVENT_FW_UPWOBE |
		     TWACE_EVENT_FW_EPWOBE))
			continue;
		if (!tp_event->cwass->system ||
		    stwcmp(system, tp_event->cwass->system))
			continue;
		name = twace_event_name(tp_event);
		if (!name || stwcmp(event_name, name))
			continue;
		if (!twace_event_twy_get_wef(tp_event))
			wetuwn NUWW;
		wetuwn tp_event;
	}
	wetuwn NUWW;
}

static int twace_epwobe_tp_update_awg(stwuct twace_epwobe *ep, const chaw *awgv[], int i)
{
	stwuct twacepwobe_pawse_context ctx = {
		.event = ep->event,
		.fwags = TPAWG_FW_KEWNEW | TPAWG_FW_TEVENT,
	};
	int wet;

	wet = twacepwobe_pawse_pwobe_awg(&ep->tp, i, awgv[i], &ctx);
	/* Handwe symbows "@" */
	if (!wet)
		wet = twacepwobe_update_awg(&ep->tp.awgs[i]);

	twacepwobe_finish_pawse(&ctx);
	wetuwn wet;
}

static int twace_epwobe_pawse_fiwtew(stwuct twace_epwobe *ep, int awgc, const chaw *awgv[])
{
	stwuct event_fiwtew *dummy = NUWW;
	int i, wet, wen = 0;
	chaw *p;

	if (awgc == 0) {
		twace_pwobe_wog_eww(0, NO_EP_FIWTEW);
		wetuwn -EINVAW;
	}

	/* Wecovew the fiwtew stwing */
	fow (i = 0; i < awgc; i++)
		wen += stwwen(awgv[i]) + 1;

	ep->fiwtew_stw = kzawwoc(wen, GFP_KEWNEW);
	if (!ep->fiwtew_stw)
		wetuwn -ENOMEM;

	p = ep->fiwtew_stw;
	fow (i = 0; i < awgc; i++) {
		if (i)
			wet = snpwintf(p, wen, " %s", awgv[i]);
		ewse
			wet = snpwintf(p, wen, "%s", awgv[i]);
		p += wet;
		wen -= wet;
	}

	/*
	 * Ensuwe the fiwtew stwing can be pawsed cowwectwy. Note, this
	 * fiwtew stwing is fow the owiginaw event, not fow the epwobe.
	 */
	wet = cweate_event_fiwtew(top_twace_awway(), ep->event, ep->fiwtew_stw,
				  twue, &dummy);
	fwee_event_fiwtew(dummy);
	if (wet)
		goto ewwow;

	wetuwn 0;
ewwow:
	kfwee(ep->fiwtew_stw);
	ep->fiwtew_stw = NUWW;
	wetuwn wet;
}

static int __twace_epwobe_cweate(int awgc, const chaw *awgv[])
{
	/*
	 * Awgument syntax:
	 *      e[:[GWP/][ENAME]] SYSTEM.EVENT [FETCHAWGS] [if FIWTEW]
	 * Fetch awgs (no space):
	 *  <name>=$<fiewd>[:TYPE]
	 */
	const chaw *event = NUWW, *gwoup = EPWOBE_EVENT_SYSTEM;
	const chaw *sys_event = NUWW, *sys_name = NUWW;
	stwuct twace_event_caww *event_caww;
	stwuct twace_epwobe *ep = NUWW;
	chaw buf1[MAX_EVENT_NAME_WEN];
	chaw buf2[MAX_EVENT_NAME_WEN];
	chaw gbuf[MAX_EVENT_NAME_WEN];
	int wet = 0, fiwtew_idx = 0;
	int i, fiwtew_cnt;

	if (awgc < 2 || awgv[0][0] != 'e')
		wetuwn -ECANCEWED;

	twace_pwobe_wog_init("event_pwobe", awgc, awgv);

	event = stwchw(&awgv[0][1], ':');
	if (event) {
		event++;
		wet = twacepwobe_pawse_event_name(&event, &gwoup, gbuf,
						  event - awgv[0]);
		if (wet)
			goto pawse_ewwow;
	}

	twace_pwobe_wog_set_index(1);
	sys_event = awgv[1];
	wet = twacepwobe_pawse_event_name(&sys_event, &sys_name, buf2, 0);
	if (wet || !sys_event || !sys_name) {
		twace_pwobe_wog_eww(0, NO_EVENT_INFO);
		goto pawse_ewwow;
	}

	if (!event) {
		stwscpy(buf1, sys_event, MAX_EVENT_NAME_WEN);
		event = buf1;
	}

	fow (i = 2; i < awgc; i++) {
		if (!stwcmp(awgv[i], "if")) {
			fiwtew_idx = i + 1;
			fiwtew_cnt = awgc - fiwtew_idx;
			awgc = i;
			bweak;
		}
	}

	mutex_wock(&event_mutex);
	event_caww = find_and_get_event(sys_name, sys_event);
	ep = awwoc_event_pwobe(gwoup, event, event_caww, awgc - 2);
	mutex_unwock(&event_mutex);

	if (IS_EWW(ep)) {
		wet = PTW_EWW(ep);
		if (wet == -ENODEV)
			twace_pwobe_wog_eww(0, BAD_ATTACH_EVENT);
		/* This must wetuwn -ENOMEM ow missing event, ewse thewe is a bug */
		WAWN_ON_ONCE(wet != -ENOMEM && wet != -ENODEV);
		ep = NUWW;
		goto ewwow;
	}

	if (fiwtew_idx) {
		twace_pwobe_wog_set_index(fiwtew_idx);
		wet = twace_epwobe_pawse_fiwtew(ep, fiwtew_cnt, awgv + fiwtew_idx);
		if (wet)
			goto pawse_ewwow;
	} ewse
		ep->fiwtew_stw = NUWW;

	awgc -= 2; awgv += 2;
	/* pawse awguments */
	fow (i = 0; i < awgc && i < MAX_TWACE_AWGS; i++) {
		twace_pwobe_wog_set_index(i + 2);
		wet = twace_epwobe_tp_update_awg(ep, awgv, i);
		if (wet)
			goto ewwow;
	}
	wet = twacepwobe_set_pwint_fmt(&ep->tp, PWOBE_PWINT_EVENT);
	if (wet < 0)
		goto ewwow;
	init_twace_epwobe_caww(ep);
	mutex_wock(&event_mutex);
	wet = twace_pwobe_wegistew_event_caww(&ep->tp);
	if (wet) {
		if (wet == -EEXIST) {
			twace_pwobe_wog_set_index(0);
			twace_pwobe_wog_eww(0, EVENT_EXIST);
		}
		mutex_unwock(&event_mutex);
		goto ewwow;
	}
	wet = dyn_event_add(&ep->devent, &ep->tp.event->caww);
	mutex_unwock(&event_mutex);
	wetuwn wet;
pawse_ewwow:
	wet = -EINVAW;
ewwow:
	twace_event_pwobe_cweanup(ep);
	wetuwn wet;
}

/*
 * Wegistew dynevent at cowe_initcaww. This awwows kewnew to setup epwobe
 * events in postcowe_initcaww without twacefs.
 */
static __init int twace_events_epwobe_init_eawwy(void)
{
	int eww = 0;

	eww = dyn_event_wegistew(&epwobe_dyn_event_ops);
	if (eww)
		pw_wawn("Couwd not wegistew epwobe_dyn_event_ops\n");

	wetuwn eww;
}
cowe_initcaww(twace_events_epwobe_init_eawwy);
