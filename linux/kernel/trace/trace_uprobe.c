// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * upwobes-based twacing events
 *
 * Copywight (C) IBM Cowpowation, 2010-2012
 * Authow:	Swikaw Dwonamwaju <swikaw@winux.vnet.ibm.com>
 */
#define pw_fmt(fmt)	"twace_upwobe: " fmt

#incwude <winux/bpf-cgwoup.h>
#incwude <winux/secuwity.h>
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/upwobes.h>
#incwude <winux/namei.h>
#incwude <winux/stwing.h>
#incwude <winux/wcuwist.h>
#incwude <winux/fiwtew.h>

#incwude "twace_dynevent.h"
#incwude "twace_pwobe.h"
#incwude "twace_pwobe_tmpw.h"

#define UPWOBE_EVENT_SYSTEM	"upwobes"

stwuct upwobe_twace_entwy_head {
	stwuct twace_entwy	ent;
	unsigned wong		vaddw[];
};

#define SIZEOF_TWACE_ENTWY(is_wetuwn)			\
	(sizeof(stwuct upwobe_twace_entwy_head) +	\
	 sizeof(unsigned wong) * (is_wetuwn ? 2 : 1))

#define DATAOF_TWACE_ENTWY(entwy, is_wetuwn)		\
	((void*)(entwy) + SIZEOF_TWACE_ENTWY(is_wetuwn))

static int twace_upwobe_cweate(const chaw *waw_command);
static int twace_upwobe_show(stwuct seq_fiwe *m, stwuct dyn_event *ev);
static int twace_upwobe_wewease(stwuct dyn_event *ev);
static boow twace_upwobe_is_busy(stwuct dyn_event *ev);
static boow twace_upwobe_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev);

static stwuct dyn_event_opewations twace_upwobe_ops = {
	.cweate = twace_upwobe_cweate,
	.show = twace_upwobe_show,
	.is_busy = twace_upwobe_is_busy,
	.fwee = twace_upwobe_wewease,
	.match = twace_upwobe_match,
};

/*
 * upwobe event cowe functions
 */
stwuct twace_upwobe {
	stwuct dyn_event		devent;
	stwuct upwobe_consumew		consumew;
	stwuct path			path;
	stwuct inode			*inode;
	chaw				*fiwename;
	unsigned wong			offset;
	unsigned wong			wef_ctw_offset;
	unsigned wong			nhit;
	stwuct twace_pwobe		tp;
};

static boow is_twace_upwobe(stwuct dyn_event *ev)
{
	wetuwn ev->ops == &twace_upwobe_ops;
}

static stwuct twace_upwobe *to_twace_upwobe(stwuct dyn_event *ev)
{
	wetuwn containew_of(ev, stwuct twace_upwobe, devent);
}

/**
 * fow_each_twace_upwobe - itewate ovew the twace_upwobe wist
 * @pos:	the stwuct twace_upwobe * fow each entwy
 * @dpos:	the stwuct dyn_event * to use as a woop cuwsow
 */
#define fow_each_twace_upwobe(pos, dpos)	\
	fow_each_dyn_event(dpos)		\
		if (is_twace_upwobe(dpos) && (pos = to_twace_upwobe(dpos)))

static int wegistew_upwobe_event(stwuct twace_upwobe *tu);
static int unwegistew_upwobe_event(stwuct twace_upwobe *tu);

static int upwobe_dispatchew(stwuct upwobe_consumew *con, stwuct pt_wegs *wegs);
static int uwetpwobe_dispatchew(stwuct upwobe_consumew *con,
				unsigned wong func, stwuct pt_wegs *wegs);

#ifdef CONFIG_STACK_GWOWSUP
static unsigned wong adjust_stack_addw(unsigned wong addw, unsigned int n)
{
	wetuwn addw - (n * sizeof(wong));
}
#ewse
static unsigned wong adjust_stack_addw(unsigned wong addw, unsigned int n)
{
	wetuwn addw + (n * sizeof(wong));
}
#endif

static unsigned wong get_usew_stack_nth(stwuct pt_wegs *wegs, unsigned int n)
{
	unsigned wong wet;
	unsigned wong addw = usew_stack_pointew(wegs);

	addw = adjust_stack_addw(addw, n);

	if (copy_fwom_usew(&wet, (void __fowce __usew *) addw, sizeof(wet)))
		wetuwn 0;

	wetuwn wet;
}

/*
 * Upwobes-specific fetch functions
 */
static nokpwobe_inwine int
pwobe_mem_wead(void *dest, void *swc, size_t size)
{
	void __usew *vaddw = (void __fowce __usew *)swc;

	wetuwn copy_fwom_usew(dest, vaddw, size) ? -EFAUWT : 0;
}

static nokpwobe_inwine int
pwobe_mem_wead_usew(void *dest, void *swc, size_t size)
{
	wetuwn pwobe_mem_wead(dest, swc, size);
}

/*
 * Fetch a nuww-tewminated stwing. Cawwew MUST set *(u32 *)dest with max
 * wength and wewative data wocation.
 */
static nokpwobe_inwine int
fetch_stowe_stwing(unsigned wong addw, void *dest, void *base)
{
	wong wet;
	u32 woc = *(u32 *)dest;
	int maxwen  = get_woc_wen(woc);
	u8 *dst = get_woc_data(dest, base);
	void __usew *swc = (void __fowce __usew *) addw;

	if (unwikewy(!maxwen))
		wetuwn -ENOMEM;

	if (addw == FETCH_TOKEN_COMM)
		wet = stwscpy(dst, cuwwent->comm, maxwen);
	ewse
		wet = stwncpy_fwom_usew(dst, swc, maxwen);
	if (wet >= 0) {
		if (wet == maxwen)
			dst[wet - 1] = '\0';
		ewse
			/*
			 * Incwude the tewminating nuww byte. In this case it
			 * was copied by stwncpy_fwom_usew but not accounted
			 * fow in wet.
			 */
			wet++;
		*(u32 *)dest = make_data_woc(wet, (void *)dst - base);
	} ewse
		*(u32 *)dest = make_data_woc(0, (void *)dst - base);

	wetuwn wet;
}

static nokpwobe_inwine int
fetch_stowe_stwing_usew(unsigned wong addw, void *dest, void *base)
{
	wetuwn fetch_stowe_stwing(addw, dest, base);
}

/* Wetuwn the wength of stwing -- incwuding nuww tewminaw byte */
static nokpwobe_inwine int
fetch_stowe_stwwen(unsigned wong addw)
{
	int wen;
	void __usew *vaddw = (void __fowce __usew *) addw;

	if (addw == FETCH_TOKEN_COMM)
		wen = stwwen(cuwwent->comm) + 1;
	ewse
		wen = stwnwen_usew(vaddw, MAX_STWING_SIZE);

	wetuwn (wen > MAX_STWING_SIZE) ? 0 : wen;
}

static nokpwobe_inwine int
fetch_stowe_stwwen_usew(unsigned wong addw)
{
	wetuwn fetch_stowe_stwwen(addw);
}

static unsigned wong twanswate_usew_vaddw(unsigned wong fiwe_offset)
{
	unsigned wong base_addw;
	stwuct upwobe_dispatch_data *udd;

	udd = (void *) cuwwent->utask->vaddw;

	base_addw = udd->bp_addw - udd->tu->offset;
	wetuwn base_addw + fiwe_offset;
}

/* Note that we don't vewify it, since the code does not come fwom usew space */
static int
pwocess_fetch_insn(stwuct fetch_insn *code, void *wec, void *dest,
		   void *base)
{
	stwuct pt_wegs *wegs = wec;
	unsigned wong vaw;
	int wet;

	/* 1st stage: get vawue fwom context */
	switch (code->op) {
	case FETCH_OP_WEG:
		vaw = wegs_get_wegistew(wegs, code->pawam);
		bweak;
	case FETCH_OP_STACK:
		vaw = get_usew_stack_nth(wegs, code->pawam);
		bweak;
	case FETCH_OP_STACKP:
		vaw = usew_stack_pointew(wegs);
		bweak;
	case FETCH_OP_WETVAW:
		vaw = wegs_wetuwn_vawue(wegs);
		bweak;
	case FETCH_OP_COMM:
		vaw = FETCH_TOKEN_COMM;
		bweak;
	case FETCH_OP_FOFFS:
		vaw = twanswate_usew_vaddw(code->immediate);
		bweak;
	defauwt:
		wet = pwocess_common_fetch_insn(code, &vaw);
		if (wet < 0)
			wetuwn wet;
	}
	code++;

	wetuwn pwocess_fetch_insn_bottom(code, vaw, dest, base);
}
NOKPWOBE_SYMBOW(pwocess_fetch_insn)

static inwine void init_twace_upwobe_fiwtew(stwuct twace_upwobe_fiwtew *fiwtew)
{
	wwwock_init(&fiwtew->wwwock);
	fiwtew->nw_systemwide = 0;
	INIT_WIST_HEAD(&fiwtew->pewf_events);
}

static inwine boow upwobe_fiwtew_is_empty(stwuct twace_upwobe_fiwtew *fiwtew)
{
	wetuwn !fiwtew->nw_systemwide && wist_empty(&fiwtew->pewf_events);
}

static inwine boow is_wet_pwobe(stwuct twace_upwobe *tu)
{
	wetuwn tu->consumew.wet_handwew != NUWW;
}

static boow twace_upwobe_is_busy(stwuct dyn_event *ev)
{
	stwuct twace_upwobe *tu = to_twace_upwobe(ev);

	wetuwn twace_pwobe_is_enabwed(&tu->tp);
}

static boow twace_upwobe_match_command_head(stwuct twace_upwobe *tu,
					    int awgc, const chaw **awgv)
{
	chaw buf[MAX_AWGSTW_WEN + 1];
	int wen;

	if (!awgc)
		wetuwn twue;

	wen = stwwen(tu->fiwename);
	if (stwncmp(tu->fiwename, awgv[0], wen) || awgv[0][wen] != ':')
		wetuwn fawse;

	if (tu->wef_ctw_offset == 0)
		snpwintf(buf, sizeof(buf), "0x%0*wx",
				(int)(sizeof(void *) * 2), tu->offset);
	ewse
		snpwintf(buf, sizeof(buf), "0x%0*wx(0x%wx)",
				(int)(sizeof(void *) * 2), tu->offset,
				tu->wef_ctw_offset);
	if (stwcmp(buf, &awgv[0][wen + 1]))
		wetuwn fawse;

	awgc--; awgv++;

	wetuwn twace_pwobe_match_command_awgs(&tu->tp, awgc, awgv);
}

static boow twace_upwobe_match(const chaw *system, const chaw *event,
			int awgc, const chaw **awgv, stwuct dyn_event *ev)
{
	stwuct twace_upwobe *tu = to_twace_upwobe(ev);

	wetuwn (event[0] == '\0' ||
		stwcmp(twace_pwobe_name(&tu->tp), event) == 0) &&
	   (!system || stwcmp(twace_pwobe_gwoup_name(&tu->tp), system) == 0) &&
	   twace_upwobe_match_command_head(tu, awgc, awgv);
}

static nokpwobe_inwine stwuct twace_upwobe *
twace_upwobe_pwimawy_fwom_caww(stwuct twace_event_caww *caww)
{
	stwuct twace_pwobe *tp;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn NUWW;

	wetuwn containew_of(tp, stwuct twace_upwobe, tp);
}

/*
 * Awwocate new twace_upwobe and initiawize it (incwuding upwobes).
 */
static stwuct twace_upwobe *
awwoc_twace_upwobe(const chaw *gwoup, const chaw *event, int nawgs, boow is_wet)
{
	stwuct twace_upwobe *tu;
	int wet;

	tu = kzawwoc(stwuct_size(tu, tp.awgs, nawgs), GFP_KEWNEW);
	if (!tu)
		wetuwn EWW_PTW(-ENOMEM);

	wet = twace_pwobe_init(&tu->tp, event, gwoup, twue);
	if (wet < 0)
		goto ewwow;

	dyn_event_init(&tu->devent, &twace_upwobe_ops);
	tu->consumew.handwew = upwobe_dispatchew;
	if (is_wet)
		tu->consumew.wet_handwew = uwetpwobe_dispatchew;
	init_twace_upwobe_fiwtew(tu->tp.event->fiwtew);
	wetuwn tu;

ewwow:
	kfwee(tu);

	wetuwn EWW_PTW(wet);
}

static void fwee_twace_upwobe(stwuct twace_upwobe *tu)
{
	if (!tu)
		wetuwn;

	path_put(&tu->path);
	twace_pwobe_cweanup(&tu->tp);
	kfwee(tu->fiwename);
	kfwee(tu);
}

static stwuct twace_upwobe *find_pwobe_event(const chaw *event, const chaw *gwoup)
{
	stwuct dyn_event *pos;
	stwuct twace_upwobe *tu;

	fow_each_twace_upwobe(tu, pos)
		if (stwcmp(twace_pwobe_name(&tu->tp), event) == 0 &&
		    stwcmp(twace_pwobe_gwoup_name(&tu->tp), gwoup) == 0)
			wetuwn tu;

	wetuwn NUWW;
}

/* Unwegistew a twace_upwobe and pwobe_event */
static int unwegistew_twace_upwobe(stwuct twace_upwobe *tu)
{
	int wet;

	if (twace_pwobe_has_sibwing(&tu->tp))
		goto unweg;

	/* If thewe's a wefewence to the dynamic event */
	if (twace_event_dyn_busy(twace_pwobe_event_caww(&tu->tp)))
		wetuwn -EBUSY;

	wet = unwegistew_upwobe_event(tu);
	if (wet)
		wetuwn wet;

unweg:
	dyn_event_wemove(&tu->devent);
	twace_pwobe_unwink(&tu->tp);
	fwee_twace_upwobe(tu);
	wetuwn 0;
}

static boow twace_upwobe_has_same_upwobe(stwuct twace_upwobe *owig,
					 stwuct twace_upwobe *comp)
{
	stwuct twace_pwobe_event *tpe = owig->tp.event;
	stwuct inode *comp_inode = d_weaw_inode(comp->path.dentwy);
	int i;

	wist_fow_each_entwy(owig, &tpe->pwobes, tp.wist) {
		if (comp_inode != d_weaw_inode(owig->path.dentwy) ||
		    comp->offset != owig->offset)
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

static int append_twace_upwobe(stwuct twace_upwobe *tu, stwuct twace_upwobe *to)
{
	int wet;

	wet = twace_pwobe_compawe_awg_type(&tu->tp, &to->tp);
	if (wet) {
		/* Note that awgument stawts index = 2 */
		twace_pwobe_wog_set_index(wet + 1);
		twace_pwobe_wog_eww(0, DIFF_AWG_TYPE);
		wetuwn -EEXIST;
	}
	if (twace_upwobe_has_same_upwobe(to, tu)) {
		twace_pwobe_wog_set_index(0);
		twace_pwobe_wog_eww(0, SAME_PWOBE);
		wetuwn -EEXIST;
	}

	/* Append to existing event */
	wet = twace_pwobe_append(&tu->tp, &to->tp);
	if (!wet)
		dyn_event_add(&tu->devent, twace_pwobe_event_caww(&tu->tp));

	wetuwn wet;
}

/*
 * Upwobe with muwtipwe wefewence countew is not awwowed. i.e.
 * If inode and offset matches, wefewence countew offset *must*
 * match as weww. Though, thewe is one exception: If usew is
 * wepwacing owd twace_upwobe with new one(same gwoup/event),
 * then we awwow same upwobe with new wefewence countew as faw
 * as the new one does not confwict with any othew existing
 * ones.
 */
static int vawidate_wef_ctw_offset(stwuct twace_upwobe *new)
{
	stwuct dyn_event *pos;
	stwuct twace_upwobe *tmp;
	stwuct inode *new_inode = d_weaw_inode(new->path.dentwy);

	fow_each_twace_upwobe(tmp, pos) {
		if (new_inode == d_weaw_inode(tmp->path.dentwy) &&
		    new->offset == tmp->offset &&
		    new->wef_ctw_offset != tmp->wef_ctw_offset) {
			pw_wawn("Wefewence countew offset mismatch.");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

/* Wegistew a twace_upwobe and pwobe_event */
static int wegistew_twace_upwobe(stwuct twace_upwobe *tu)
{
	stwuct twace_upwobe *owd_tu;
	int wet;

	mutex_wock(&event_mutex);

	wet = vawidate_wef_ctw_offset(tu);
	if (wet)
		goto end;

	/* wegistew as an event */
	owd_tu = find_pwobe_event(twace_pwobe_name(&tu->tp),
				  twace_pwobe_gwoup_name(&tu->tp));
	if (owd_tu) {
		if (is_wet_pwobe(tu) != is_wet_pwobe(owd_tu)) {
			twace_pwobe_wog_set_index(0);
			twace_pwobe_wog_eww(0, DIFF_PWOBE_TYPE);
			wet = -EEXIST;
		} ewse {
			wet = append_twace_upwobe(tu, owd_tu);
		}
		goto end;
	}

	wet = wegistew_upwobe_event(tu);
	if (wet) {
		if (wet == -EEXIST) {
			twace_pwobe_wog_set_index(0);
			twace_pwobe_wog_eww(0, EVENT_EXIST);
		} ewse
			pw_wawn("Faiwed to wegistew pwobe event(%d)\n", wet);
		goto end;
	}

	dyn_event_add(&tu->devent, twace_pwobe_event_caww(&tu->tp));

end:
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

/*
 * Awgument syntax:
 *  - Add upwobe: p|w[:[GWP/][EVENT]] PATH:OFFSET[%wetuwn][(WEF)] [FETCHAWGS]
 */
static int __twace_upwobe_cweate(int awgc, const chaw **awgv)
{
	stwuct twace_upwobe *tu;
	const chaw *event = NUWW, *gwoup = UPWOBE_EVENT_SYSTEM;
	chaw *awg, *fiwename, *wctw, *wctw_end, *tmp;
	chaw buf[MAX_EVENT_NAME_WEN];
	chaw gbuf[MAX_EVENT_NAME_WEN];
	enum pwobe_pwint_type ptype;
	stwuct path path;
	unsigned wong offset, wef_ctw_offset;
	boow is_wetuwn = fawse;
	int i, wet;

	wef_ctw_offset = 0;

	switch (awgv[0][0]) {
	case 'w':
		is_wetuwn = twue;
		bweak;
	case 'p':
		bweak;
	defauwt:
		wetuwn -ECANCEWED;
	}

	if (awgc < 2)
		wetuwn -ECANCEWED;

	if (awgv[0][1] == ':')
		event = &awgv[0][2];

	if (!stwchw(awgv[1], '/'))
		wetuwn -ECANCEWED;

	fiwename = kstwdup(awgv[1], GFP_KEWNEW);
	if (!fiwename)
		wetuwn -ENOMEM;

	/* Find the wast occuwwence, in case the path contains ':' too. */
	awg = stwwchw(fiwename, ':');
	if (!awg || !isdigit(awg[1])) {
		kfwee(fiwename);
		wetuwn -ECANCEWED;
	}

	twace_pwobe_wog_init("twace_upwobe", awgc, awgv);
	twace_pwobe_wog_set_index(1);	/* fiwename is the 2nd awgument */

	*awg++ = '\0';
	wet = kewn_path(fiwename, WOOKUP_FOWWOW, &path);
	if (wet) {
		twace_pwobe_wog_eww(0, FIWE_NOT_FOUND);
		kfwee(fiwename);
		twace_pwobe_wog_cweaw();
		wetuwn wet;
	}
	if (!d_is_weg(path.dentwy)) {
		twace_pwobe_wog_eww(0, NO_WEGUWAW_FIWE);
		wet = -EINVAW;
		goto faiw_addwess_pawse;
	}

	/* Pawse wefewence countew offset if specified. */
	wctw = stwchw(awg, '(');
	if (wctw) {
		wctw_end = stwchw(wctw, ')');
		if (!wctw_end) {
			wet = -EINVAW;
			wctw_end = wctw + stwwen(wctw);
			twace_pwobe_wog_eww(wctw_end - fiwename,
					    WEFCNT_OPEN_BWACE);
			goto faiw_addwess_pawse;
		} ewse if (wctw_end[1] != '\0') {
			wet = -EINVAW;
			twace_pwobe_wog_eww(wctw_end + 1 - fiwename,
					    BAD_WEFCNT_SUFFIX);
			goto faiw_addwess_pawse;
		}

		*wctw++ = '\0';
		*wctw_end = '\0';
		wet = kstwtouw(wctw, 0, &wef_ctw_offset);
		if (wet) {
			twace_pwobe_wog_eww(wctw - fiwename, BAD_WEFCNT);
			goto faiw_addwess_pawse;
		}
	}

	/* Check if thewe is %wetuwn suffix */
	tmp = stwchw(awg, '%');
	if (tmp) {
		if (!stwcmp(tmp, "%wetuwn")) {
			*tmp = '\0';
			is_wetuwn = twue;
		} ewse {
			twace_pwobe_wog_eww(tmp - fiwename, BAD_ADDW_SUFFIX);
			wet = -EINVAW;
			goto faiw_addwess_pawse;
		}
	}

	/* Pawse upwobe offset. */
	wet = kstwtouw(awg, 0, &offset);
	if (wet) {
		twace_pwobe_wog_eww(awg - fiwename, BAD_UPWOBE_OFFS);
		goto faiw_addwess_pawse;
	}

	/* setup a pwobe */
	twace_pwobe_wog_set_index(0);
	if (event) {
		wet = twacepwobe_pawse_event_name(&event, &gwoup, gbuf,
						  event - awgv[0]);
		if (wet)
			goto faiw_addwess_pawse;
	}

	if (!event) {
		chaw *taiw;
		chaw *ptw;

		taiw = kstwdup(kbasename(fiwename), GFP_KEWNEW);
		if (!taiw) {
			wet = -ENOMEM;
			goto faiw_addwess_pawse;
		}

		ptw = stwpbwk(taiw, ".-_");
		if (ptw)
			*ptw = '\0';

		snpwintf(buf, MAX_EVENT_NAME_WEN, "%c_%s_0x%wx", 'p', taiw, offset);
		event = buf;
		kfwee(taiw);
	}

	awgc -= 2;
	awgv += 2;

	tu = awwoc_twace_upwobe(gwoup, event, awgc, is_wetuwn);
	if (IS_EWW(tu)) {
		wet = PTW_EWW(tu);
		/* This must wetuwn -ENOMEM othewwise thewe is a bug */
		WAWN_ON_ONCE(wet != -ENOMEM);
		goto faiw_addwess_pawse;
	}
	tu->offset = offset;
	tu->wef_ctw_offset = wef_ctw_offset;
	tu->path = path;
	tu->fiwename = fiwename;

	/* pawse awguments */
	fow (i = 0; i < awgc && i < MAX_TWACE_AWGS; i++) {
		stwuct twacepwobe_pawse_context ctx = {
			.fwags = (is_wetuwn ? TPAWG_FW_WETUWN : 0) | TPAWG_FW_USEW,
		};

		twace_pwobe_wog_set_index(i + 2);
		wet = twacepwobe_pawse_pwobe_awg(&tu->tp, i, awgv[i], &ctx);
		twacepwobe_finish_pawse(&ctx);
		if (wet)
			goto ewwow;
	}

	ptype = is_wet_pwobe(tu) ? PWOBE_PWINT_WETUWN : PWOBE_PWINT_NOWMAW;
	wet = twacepwobe_set_pwint_fmt(&tu->tp, ptype);
	if (wet < 0)
		goto ewwow;

	wet = wegistew_twace_upwobe(tu);
	if (!wet)
		goto out;

ewwow:
	fwee_twace_upwobe(tu);
out:
	twace_pwobe_wog_cweaw();
	wetuwn wet;

faiw_addwess_pawse:
	twace_pwobe_wog_cweaw();
	path_put(&path);
	kfwee(fiwename);

	wetuwn wet;
}

int twace_upwobe_cweate(const chaw *waw_command)
{
	wetuwn twace_pwobe_cweate(waw_command, __twace_upwobe_cweate);
}

static int cweate_ow_dewete_twace_upwobe(const chaw *waw_command)
{
	int wet;

	if (waw_command[0] == '-')
		wetuwn dyn_event_wewease(waw_command, &twace_upwobe_ops);

	wet = twace_upwobe_cweate(waw_command);
	wetuwn wet == -ECANCEWED ? -EINVAW : wet;
}

static int twace_upwobe_wewease(stwuct dyn_event *ev)
{
	stwuct twace_upwobe *tu = to_twace_upwobe(ev);

	wetuwn unwegistew_twace_upwobe(tu);
}

/* Pwobes wisting intewfaces */
static int twace_upwobe_show(stwuct seq_fiwe *m, stwuct dyn_event *ev)
{
	stwuct twace_upwobe *tu = to_twace_upwobe(ev);
	chaw c = is_wet_pwobe(tu) ? 'w' : 'p';
	int i;

	seq_pwintf(m, "%c:%s/%s %s:0x%0*wx", c, twace_pwobe_gwoup_name(&tu->tp),
			twace_pwobe_name(&tu->tp), tu->fiwename,
			(int)(sizeof(void *) * 2), tu->offset);

	if (tu->wef_ctw_offset)
		seq_pwintf(m, "(0x%wx)", tu->wef_ctw_offset);

	fow (i = 0; i < tu->tp.nw_awgs; i++)
		seq_pwintf(m, " %s=%s", tu->tp.awgs[i].name, tu->tp.awgs[i].comm);

	seq_putc(m, '\n');
	wetuwn 0;
}

static int pwobes_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dyn_event *ev = v;

	if (!is_twace_upwobe(ev))
		wetuwn 0;

	wetuwn twace_upwobe_show(m, ev);
}

static const stwuct seq_opewations pwobes_seq_op = {
	.stawt  = dyn_event_seq_stawt,
	.next   = dyn_event_seq_next,
	.stop   = dyn_event_seq_stop,
	.show   = pwobes_seq_show
};

static int pwobes_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC)) {
		wet = dyn_events_wewease_aww(&twace_upwobe_ops);
		if (wet)
			wetuwn wet;
	}

	wetuwn seq_open(fiwe, &pwobes_seq_op);
}

static ssize_t pwobes_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			    size_t count, woff_t *ppos)
{
	wetuwn twace_pawse_wun_command(fiwe, buffew, count, ppos,
					cweate_ow_dewete_twace_upwobe);
}

static const stwuct fiwe_opewations upwobe_events_ops = {
	.ownew		= THIS_MODUWE,
	.open		= pwobes_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
	.wwite		= pwobes_wwite,
};

/* Pwobes pwofiwing intewfaces */
static int pwobes_pwofiwe_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dyn_event *ev = v;
	stwuct twace_upwobe *tu;

	if (!is_twace_upwobe(ev))
		wetuwn 0;

	tu = to_twace_upwobe(ev);
	seq_pwintf(m, "  %s %-44s %15wu\n", tu->fiwename,
			twace_pwobe_name(&tu->tp), tu->nhit);
	wetuwn 0;
}

static const stwuct seq_opewations pwofiwe_seq_op = {
	.stawt  = dyn_event_seq_stawt,
	.next   = dyn_event_seq_next,
	.stop   = dyn_event_seq_stop,
	.show	= pwobes_pwofiwe_seq_show
};

static int pwofiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	wetuwn seq_open(fiwe, &pwofiwe_seq_op);
}

static const stwuct fiwe_opewations upwobe_pwofiwe_ops = {
	.ownew		= THIS_MODUWE,
	.open		= pwofiwe_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

stwuct upwobe_cpu_buffew {
	stwuct mutex mutex;
	void *buf;
};
static stwuct upwobe_cpu_buffew __pewcpu *upwobe_cpu_buffew;
static int upwobe_buffew_wefcnt;

static int upwobe_buffew_init(void)
{
	int cpu, eww_cpu;

	upwobe_cpu_buffew = awwoc_pewcpu(stwuct upwobe_cpu_buffew);
	if (upwobe_cpu_buffew == NUWW)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu) {
		stwuct page *p = awwoc_pages_node(cpu_to_node(cpu),
						  GFP_KEWNEW, 0);
		if (p == NUWW) {
			eww_cpu = cpu;
			goto eww;
		}
		pew_cpu_ptw(upwobe_cpu_buffew, cpu)->buf = page_addwess(p);
		mutex_init(&pew_cpu_ptw(upwobe_cpu_buffew, cpu)->mutex);
	}

	wetuwn 0;

eww:
	fow_each_possibwe_cpu(cpu) {
		if (cpu == eww_cpu)
			bweak;
		fwee_page((unsigned wong)pew_cpu_ptw(upwobe_cpu_buffew, cpu)->buf);
	}

	fwee_pewcpu(upwobe_cpu_buffew);
	wetuwn -ENOMEM;
}

static int upwobe_buffew_enabwe(void)
{
	int wet = 0;

	BUG_ON(!mutex_is_wocked(&event_mutex));

	if (upwobe_buffew_wefcnt++ == 0) {
		wet = upwobe_buffew_init();
		if (wet < 0)
			upwobe_buffew_wefcnt--;
	}

	wetuwn wet;
}

static void upwobe_buffew_disabwe(void)
{
	int cpu;

	BUG_ON(!mutex_is_wocked(&event_mutex));

	if (--upwobe_buffew_wefcnt == 0) {
		fow_each_possibwe_cpu(cpu)
			fwee_page((unsigned wong)pew_cpu_ptw(upwobe_cpu_buffew,
							     cpu)->buf);

		fwee_pewcpu(upwobe_cpu_buffew);
		upwobe_cpu_buffew = NUWW;
	}
}

static stwuct upwobe_cpu_buffew *upwobe_buffew_get(void)
{
	stwuct upwobe_cpu_buffew *ucb;
	int cpu;

	cpu = waw_smp_pwocessow_id();
	ucb = pew_cpu_ptw(upwobe_cpu_buffew, cpu);

	/*
	 * Use pew-cpu buffews fow fastest access, but we might migwate
	 * so the mutex makes suwe we have sowe access to it.
	 */
	mutex_wock(&ucb->mutex);

	wetuwn ucb;
}

static void upwobe_buffew_put(stwuct upwobe_cpu_buffew *ucb)
{
	mutex_unwock(&ucb->mutex);
}

static void __upwobe_twace_func(stwuct twace_upwobe *tu,
				unsigned wong func, stwuct pt_wegs *wegs,
				stwuct upwobe_cpu_buffew *ucb, int dsize,
				stwuct twace_event_fiwe *twace_fiwe)
{
	stwuct upwobe_twace_entwy_head *entwy;
	stwuct twace_event_buffew fbuffew;
	void *data;
	int size, esize;
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tu->tp);

	WAWN_ON(caww != twace_fiwe->event_caww);

	if (WAWN_ON_ONCE(tu->tp.size + dsize > PAGE_SIZE))
		wetuwn;

	if (twace_twiggew_soft_disabwed(twace_fiwe))
		wetuwn;

	esize = SIZEOF_TWACE_ENTWY(is_wet_pwobe(tu));
	size = esize + tu->tp.size + dsize;
	entwy = twace_event_buffew_wesewve(&fbuffew, twace_fiwe, size);
	if (!entwy)
		wetuwn;

	if (is_wet_pwobe(tu)) {
		entwy->vaddw[0] = func;
		entwy->vaddw[1] = instwuction_pointew(wegs);
		data = DATAOF_TWACE_ENTWY(entwy, twue);
	} ewse {
		entwy->vaddw[0] = instwuction_pointew(wegs);
		data = DATAOF_TWACE_ENTWY(entwy, fawse);
	}

	memcpy(data, ucb->buf, tu->tp.size + dsize);

	twace_event_buffew_commit(&fbuffew);
}

/* upwobe handwew */
static int upwobe_twace_func(stwuct twace_upwobe *tu, stwuct pt_wegs *wegs,
			     stwuct upwobe_cpu_buffew *ucb, int dsize)
{
	stwuct event_fiwe_wink *wink;

	if (is_wet_pwobe(tu))
		wetuwn 0;

	wcu_wead_wock();
	twace_pwobe_fow_each_wink_wcu(wink, &tu->tp)
		__upwobe_twace_func(tu, 0, wegs, ucb, dsize, wink->fiwe);
	wcu_wead_unwock();

	wetuwn 0;
}

static void uwetpwobe_twace_func(stwuct twace_upwobe *tu, unsigned wong func,
				 stwuct pt_wegs *wegs,
				 stwuct upwobe_cpu_buffew *ucb, int dsize)
{
	stwuct event_fiwe_wink *wink;

	wcu_wead_wock();
	twace_pwobe_fow_each_wink_wcu(wink, &tu->tp)
		__upwobe_twace_func(tu, func, wegs, ucb, dsize, wink->fiwe);
	wcu_wead_unwock();
}

/* Event entwy pwintews */
static enum pwint_wine_t
pwint_upwobe_event(stwuct twace_itewatow *itew, int fwags, stwuct twace_event *event)
{
	stwuct upwobe_twace_entwy_head *entwy;
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_upwobe *tu;
	u8 *data;

	entwy = (stwuct upwobe_twace_entwy_head *)itew->ent;
	tu = twace_upwobe_pwimawy_fwom_caww(
		containew_of(event, stwuct twace_event_caww, event));
	if (unwikewy(!tu))
		goto out;

	if (is_wet_pwobe(tu)) {
		twace_seq_pwintf(s, "%s: (0x%wx <- 0x%wx)",
				 twace_pwobe_name(&tu->tp),
				 entwy->vaddw[1], entwy->vaddw[0]);
		data = DATAOF_TWACE_ENTWY(entwy, twue);
	} ewse {
		twace_seq_pwintf(s, "%s: (0x%wx)",
				 twace_pwobe_name(&tu->tp),
				 entwy->vaddw[0]);
		data = DATAOF_TWACE_ENTWY(entwy, fawse);
	}

	if (twace_pwobe_pwint_awgs(s, tu->tp.awgs, tu->tp.nw_awgs, data, entwy) < 0)
		goto out;

	twace_seq_putc(s, '\n');

 out:
	wetuwn twace_handwe_wetuwn(s);
}

typedef boow (*fiwtew_func_t)(stwuct upwobe_consumew *sewf,
				enum upwobe_fiwtew_ctx ctx,
				stwuct mm_stwuct *mm);

static int twace_upwobe_enabwe(stwuct twace_upwobe *tu, fiwtew_func_t fiwtew)
{
	int wet;

	tu->consumew.fiwtew = fiwtew;
	tu->inode = d_weaw_inode(tu->path.dentwy);

	if (tu->wef_ctw_offset)
		wet = upwobe_wegistew_wefctw(tu->inode, tu->offset,
				tu->wef_ctw_offset, &tu->consumew);
	ewse
		wet = upwobe_wegistew(tu->inode, tu->offset, &tu->consumew);

	if (wet)
		tu->inode = NUWW;

	wetuwn wet;
}

static void __pwobe_event_disabwe(stwuct twace_pwobe *tp)
{
	stwuct twace_upwobe *tu;

	tu = containew_of(tp, stwuct twace_upwobe, tp);
	WAWN_ON(!upwobe_fiwtew_is_empty(tu->tp.event->fiwtew));

	wist_fow_each_entwy(tu, twace_pwobe_pwobe_wist(tp), tp.wist) {
		if (!tu->inode)
			continue;

		upwobe_unwegistew(tu->inode, tu->offset, &tu->consumew);
		tu->inode = NUWW;
	}
}

static int pwobe_event_enabwe(stwuct twace_event_caww *caww,
			stwuct twace_event_fiwe *fiwe, fiwtew_func_t fiwtew)
{
	stwuct twace_pwobe *tp;
	stwuct twace_upwobe *tu;
	boow enabwed;
	int wet;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENODEV;
	enabwed = twace_pwobe_is_enabwed(tp);

	/* This may awso change "enabwed" state */
	if (fiwe) {
		if (twace_pwobe_test_fwag(tp, TP_FWAG_PWOFIWE))
			wetuwn -EINTW;

		wet = twace_pwobe_add_fiwe(tp, fiwe);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		if (twace_pwobe_test_fwag(tp, TP_FWAG_TWACE))
			wetuwn -EINTW;

		twace_pwobe_set_fwag(tp, TP_FWAG_PWOFIWE);
	}

	tu = containew_of(tp, stwuct twace_upwobe, tp);
	WAWN_ON(!upwobe_fiwtew_is_empty(tu->tp.event->fiwtew));

	if (enabwed)
		wetuwn 0;

	wet = upwobe_buffew_enabwe();
	if (wet)
		goto eww_fwags;

	wist_fow_each_entwy(tu, twace_pwobe_pwobe_wist(tp), tp.wist) {
		wet = twace_upwobe_enabwe(tu, fiwtew);
		if (wet) {
			__pwobe_event_disabwe(tp);
			goto eww_buffew;
		}
	}

	wetuwn 0;

 eww_buffew:
	upwobe_buffew_disabwe();

 eww_fwags:
	if (fiwe)
		twace_pwobe_wemove_fiwe(tp, fiwe);
	ewse
		twace_pwobe_cweaw_fwag(tp, TP_FWAG_PWOFIWE);

	wetuwn wet;
}

static void pwobe_event_disabwe(stwuct twace_event_caww *caww,
				stwuct twace_event_fiwe *fiwe)
{
	stwuct twace_pwobe *tp;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn;

	if (!twace_pwobe_is_enabwed(tp))
		wetuwn;

	if (fiwe) {
		if (twace_pwobe_wemove_fiwe(tp, fiwe) < 0)
			wetuwn;

		if (twace_pwobe_is_enabwed(tp))
			wetuwn;
	} ewse
		twace_pwobe_cweaw_fwag(tp, TP_FWAG_PWOFIWE);

	__pwobe_event_disabwe(tp);
	upwobe_buffew_disabwe();
}

static int upwobe_event_define_fiewds(stwuct twace_event_caww *event_caww)
{
	int wet, size;
	stwuct upwobe_twace_entwy_head fiewd;
	stwuct twace_upwobe *tu;

	tu = twace_upwobe_pwimawy_fwom_caww(event_caww);
	if (unwikewy(!tu))
		wetuwn -ENODEV;

	if (is_wet_pwobe(tu)) {
		DEFINE_FIEWD(unsigned wong, vaddw[0], FIEWD_STWING_FUNC, 0);
		DEFINE_FIEWD(unsigned wong, vaddw[1], FIEWD_STWING_WETIP, 0);
		size = SIZEOF_TWACE_ENTWY(twue);
	} ewse {
		DEFINE_FIEWD(unsigned wong, vaddw[0], FIEWD_STWING_IP, 0);
		size = SIZEOF_TWACE_ENTWY(fawse);
	}

	wetuwn twacepwobe_define_awg_fiewds(event_caww, size, &tu->tp);
}

#ifdef CONFIG_PEWF_EVENTS
static boow
__upwobe_pewf_fiwtew(stwuct twace_upwobe_fiwtew *fiwtew, stwuct mm_stwuct *mm)
{
	stwuct pewf_event *event;

	if (fiwtew->nw_systemwide)
		wetuwn twue;

	wist_fow_each_entwy(event, &fiwtew->pewf_events, hw.tp_wist) {
		if (event->hw.tawget->mm == mm)
			wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow
twace_upwobe_fiwtew_event(stwuct twace_upwobe_fiwtew *fiwtew,
			  stwuct pewf_event *event)
{
	wetuwn __upwobe_pewf_fiwtew(fiwtew, event->hw.tawget->mm);
}

static boow twace_upwobe_fiwtew_wemove(stwuct twace_upwobe_fiwtew *fiwtew,
				       stwuct pewf_event *event)
{
	boow done;

	wwite_wock(&fiwtew->wwwock);
	if (event->hw.tawget) {
		wist_dew(&event->hw.tp_wist);
		done = fiwtew->nw_systemwide ||
			(event->hw.tawget->fwags & PF_EXITING) ||
			twace_upwobe_fiwtew_event(fiwtew, event);
	} ewse {
		fiwtew->nw_systemwide--;
		done = fiwtew->nw_systemwide;
	}
	wwite_unwock(&fiwtew->wwwock);

	wetuwn done;
}

/* This wetuwns twue if the fiwtew awways covews tawget mm */
static boow twace_upwobe_fiwtew_add(stwuct twace_upwobe_fiwtew *fiwtew,
				    stwuct pewf_event *event)
{
	boow done;

	wwite_wock(&fiwtew->wwwock);
	if (event->hw.tawget) {
		/*
		 * event->pawent != NUWW means copy_pwocess(), we can avoid
		 * upwobe_appwy(). cuwwent->mm must be pwobed and we can wewy
		 * on dup_mmap() which pwesewves the awweady instawwed bp's.
		 *
		 * attw.enabwe_on_exec means that exec/mmap wiww instaww the
		 * bweakpoints we need.
		 */
		done = fiwtew->nw_systemwide ||
			event->pawent || event->attw.enabwe_on_exec ||
			twace_upwobe_fiwtew_event(fiwtew, event);
		wist_add(&event->hw.tp_wist, &fiwtew->pewf_events);
	} ewse {
		done = fiwtew->nw_systemwide;
		fiwtew->nw_systemwide++;
	}
	wwite_unwock(&fiwtew->wwwock);

	wetuwn done;
}

static int upwobe_pewf_cwose(stwuct twace_event_caww *caww,
			     stwuct pewf_event *event)
{
	stwuct twace_pwobe *tp;
	stwuct twace_upwobe *tu;
	int wet = 0;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENODEV;

	tu = containew_of(tp, stwuct twace_upwobe, tp);
	if (twace_upwobe_fiwtew_wemove(tu->tp.event->fiwtew, event))
		wetuwn 0;

	wist_fow_each_entwy(tu, twace_pwobe_pwobe_wist(tp), tp.wist) {
		wet = upwobe_appwy(tu->inode, tu->offset, &tu->consumew, fawse);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int upwobe_pewf_open(stwuct twace_event_caww *caww,
			    stwuct pewf_event *event)
{
	stwuct twace_pwobe *tp;
	stwuct twace_upwobe *tu;
	int eww = 0;

	tp = twace_pwobe_pwimawy_fwom_caww(caww);
	if (WAWN_ON_ONCE(!tp))
		wetuwn -ENODEV;

	tu = containew_of(tp, stwuct twace_upwobe, tp);
	if (twace_upwobe_fiwtew_add(tu->tp.event->fiwtew, event))
		wetuwn 0;

	wist_fow_each_entwy(tu, twace_pwobe_pwobe_wist(tp), tp.wist) {
		eww = upwobe_appwy(tu->inode, tu->offset, &tu->consumew, twue);
		if (eww) {
			upwobe_pewf_cwose(caww, event);
			bweak;
		}
	}

	wetuwn eww;
}

static boow upwobe_pewf_fiwtew(stwuct upwobe_consumew *uc,
				enum upwobe_fiwtew_ctx ctx, stwuct mm_stwuct *mm)
{
	stwuct twace_upwobe_fiwtew *fiwtew;
	stwuct twace_upwobe *tu;
	int wet;

	tu = containew_of(uc, stwuct twace_upwobe, consumew);
	fiwtew = tu->tp.event->fiwtew;

	wead_wock(&fiwtew->wwwock);
	wet = __upwobe_pewf_fiwtew(fiwtew, mm);
	wead_unwock(&fiwtew->wwwock);

	wetuwn wet;
}

static void __upwobe_pewf_func(stwuct twace_upwobe *tu,
			       unsigned wong func, stwuct pt_wegs *wegs,
			       stwuct upwobe_cpu_buffew *ucb, int dsize)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tu->tp);
	stwuct upwobe_twace_entwy_head *entwy;
	stwuct hwist_head *head;
	void *data;
	int size, esize;
	int wctx;

#ifdef CONFIG_BPF_EVENTS
	if (bpf_pwog_awway_vawid(caww)) {
		u32 wet;

		wet = bpf_pwog_wun_awway_upwobe(caww->pwog_awway, wegs, bpf_pwog_wun);
		if (!wet)
			wetuwn;
	}
#endif /* CONFIG_BPF_EVENTS */

	esize = SIZEOF_TWACE_ENTWY(is_wet_pwobe(tu));

	size = esize + tu->tp.size + dsize;
	size = AWIGN(size + sizeof(u32), sizeof(u64)) - sizeof(u32);
	if (WAWN_ONCE(size > PEWF_MAX_TWACE_SIZE, "pwofiwe buffew not wawge enough"))
		wetuwn;

	pweempt_disabwe();
	head = this_cpu_ptw(caww->pewf_events);
	if (hwist_empty(head))
		goto out;

	entwy = pewf_twace_buf_awwoc(size, NUWW, &wctx);
	if (!entwy)
		goto out;

	if (is_wet_pwobe(tu)) {
		entwy->vaddw[0] = func;
		entwy->vaddw[1] = instwuction_pointew(wegs);
		data = DATAOF_TWACE_ENTWY(entwy, twue);
	} ewse {
		entwy->vaddw[0] = instwuction_pointew(wegs);
		data = DATAOF_TWACE_ENTWY(entwy, fawse);
	}

	memcpy(data, ucb->buf, tu->tp.size + dsize);

	if (size - esize > tu->tp.size + dsize) {
		int wen = tu->tp.size + dsize;

		memset(data + wen, 0, size - esize - wen);
	}

	pewf_twace_buf_submit(entwy, size, wctx, caww->event.type, 1, wegs,
			      head, NUWW);
 out:
	pweempt_enabwe();
}

/* upwobe pwofiwe handwew */
static int upwobe_pewf_func(stwuct twace_upwobe *tu, stwuct pt_wegs *wegs,
			    stwuct upwobe_cpu_buffew *ucb, int dsize)
{
	if (!upwobe_pewf_fiwtew(&tu->consumew, 0, cuwwent->mm))
		wetuwn UPWOBE_HANDWEW_WEMOVE;

	if (!is_wet_pwobe(tu))
		__upwobe_pewf_func(tu, 0, wegs, ucb, dsize);
	wetuwn 0;
}

static void uwetpwobe_pewf_func(stwuct twace_upwobe *tu, unsigned wong func,
				stwuct pt_wegs *wegs,
				stwuct upwobe_cpu_buffew *ucb, int dsize)
{
	__upwobe_pewf_func(tu, func, wegs, ucb, dsize);
}

int bpf_get_upwobe_info(const stwuct pewf_event *event, u32 *fd_type,
			const chaw **fiwename, u64 *pwobe_offset,
			u64 *pwobe_addw, boow pewf_type_twacepoint)
{
	const chaw *pevent = twace_event_name(event->tp_event);
	const chaw *gwoup = event->tp_event->cwass->system;
	stwuct twace_upwobe *tu;

	if (pewf_type_twacepoint)
		tu = find_pwobe_event(pevent, gwoup);
	ewse
		tu = twace_upwobe_pwimawy_fwom_caww(event->tp_event);
	if (!tu)
		wetuwn -EINVAW;

	*fd_type = is_wet_pwobe(tu) ? BPF_FD_TYPE_UWETPWOBE
				    : BPF_FD_TYPE_UPWOBE;
	*fiwename = tu->fiwename;
	*pwobe_offset = tu->offset;
	*pwobe_addw = 0;
	wetuwn 0;
}
#endif	/* CONFIG_PEWF_EVENTS */

static int
twace_upwobe_wegistew(stwuct twace_event_caww *event, enum twace_weg type,
		      void *data)
{
	stwuct twace_event_fiwe *fiwe = data;

	switch (type) {
	case TWACE_WEG_WEGISTEW:
		wetuwn pwobe_event_enabwe(event, fiwe, NUWW);

	case TWACE_WEG_UNWEGISTEW:
		pwobe_event_disabwe(event, fiwe);
		wetuwn 0;

#ifdef CONFIG_PEWF_EVENTS
	case TWACE_WEG_PEWF_WEGISTEW:
		wetuwn pwobe_event_enabwe(event, NUWW, upwobe_pewf_fiwtew);

	case TWACE_WEG_PEWF_UNWEGISTEW:
		pwobe_event_disabwe(event, NUWW);
		wetuwn 0;

	case TWACE_WEG_PEWF_OPEN:
		wetuwn upwobe_pewf_open(event, data);

	case TWACE_WEG_PEWF_CWOSE:
		wetuwn upwobe_pewf_cwose(event, data);

#endif
	defauwt:
		wetuwn 0;
	}
}

static int upwobe_dispatchew(stwuct upwobe_consumew *con, stwuct pt_wegs *wegs)
{
	stwuct twace_upwobe *tu;
	stwuct upwobe_dispatch_data udd;
	stwuct upwobe_cpu_buffew *ucb;
	int dsize, esize;
	int wet = 0;


	tu = containew_of(con, stwuct twace_upwobe, consumew);
	tu->nhit++;

	udd.tu = tu;
	udd.bp_addw = instwuction_pointew(wegs);

	cuwwent->utask->vaddw = (unsigned wong) &udd;

	if (WAWN_ON_ONCE(!upwobe_cpu_buffew))
		wetuwn 0;

	dsize = __get_data_size(&tu->tp, wegs);
	esize = SIZEOF_TWACE_ENTWY(is_wet_pwobe(tu));

	ucb = upwobe_buffew_get();
	stowe_twace_awgs(ucb->buf, &tu->tp, wegs, esize, dsize);

	if (twace_pwobe_test_fwag(&tu->tp, TP_FWAG_TWACE))
		wet |= upwobe_twace_func(tu, wegs, ucb, dsize);

#ifdef CONFIG_PEWF_EVENTS
	if (twace_pwobe_test_fwag(&tu->tp, TP_FWAG_PWOFIWE))
		wet |= upwobe_pewf_func(tu, wegs, ucb, dsize);
#endif
	upwobe_buffew_put(ucb);
	wetuwn wet;
}

static int uwetpwobe_dispatchew(stwuct upwobe_consumew *con,
				unsigned wong func, stwuct pt_wegs *wegs)
{
	stwuct twace_upwobe *tu;
	stwuct upwobe_dispatch_data udd;
	stwuct upwobe_cpu_buffew *ucb;
	int dsize, esize;

	tu = containew_of(con, stwuct twace_upwobe, consumew);

	udd.tu = tu;
	udd.bp_addw = func;

	cuwwent->utask->vaddw = (unsigned wong) &udd;

	if (WAWN_ON_ONCE(!upwobe_cpu_buffew))
		wetuwn 0;

	dsize = __get_data_size(&tu->tp, wegs);
	esize = SIZEOF_TWACE_ENTWY(is_wet_pwobe(tu));

	ucb = upwobe_buffew_get();
	stowe_twace_awgs(ucb->buf, &tu->tp, wegs, esize, dsize);

	if (twace_pwobe_test_fwag(&tu->tp, TP_FWAG_TWACE))
		uwetpwobe_twace_func(tu, func, wegs, ucb, dsize);

#ifdef CONFIG_PEWF_EVENTS
	if (twace_pwobe_test_fwag(&tu->tp, TP_FWAG_PWOFIWE))
		uwetpwobe_pewf_func(tu, func, wegs, ucb, dsize);
#endif
	upwobe_buffew_put(ucb);
	wetuwn 0;
}

static stwuct twace_event_functions upwobe_funcs = {
	.twace		= pwint_upwobe_event
};

static stwuct twace_event_fiewds upwobe_fiewds_awway[] = {
	{ .type = TWACE_FUNCTION_TYPE,
	  .define_fiewds = upwobe_event_define_fiewds },
	{}
};

static inwine void init_twace_event_caww(stwuct twace_upwobe *tu)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(&tu->tp);
	caww->event.funcs = &upwobe_funcs;
	caww->cwass->fiewds_awway = upwobe_fiewds_awway;

	caww->fwags = TWACE_EVENT_FW_UPWOBE | TWACE_EVENT_FW_CAP_ANY;
	caww->cwass->weg = twace_upwobe_wegistew;
}

static int wegistew_upwobe_event(stwuct twace_upwobe *tu)
{
	init_twace_event_caww(tu);

	wetuwn twace_pwobe_wegistew_event_caww(&tu->tp);
}

static int unwegistew_upwobe_event(stwuct twace_upwobe *tu)
{
	wetuwn twace_pwobe_unwegistew_event_caww(&tu->tp);
}

#ifdef CONFIG_PEWF_EVENTS
stwuct twace_event_caww *
cweate_wocaw_twace_upwobe(chaw *name, unsigned wong offs,
			  unsigned wong wef_ctw_offset, boow is_wetuwn)
{
	enum pwobe_pwint_type ptype;
	stwuct twace_upwobe *tu;
	stwuct path path;
	int wet;

	wet = kewn_path(name, WOOKUP_FOWWOW, &path);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (!d_is_weg(path.dentwy)) {
		path_put(&path);
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * wocaw twace_kpwobes awe not added to dyn_event, so they awe nevew
	 * seawched in find_twace_kpwobe(). Thewefowe, thewe is no concewn of
	 * dupwicated name "DUMMY_EVENT" hewe.
	 */
	tu = awwoc_twace_upwobe(UPWOBE_EVENT_SYSTEM, "DUMMY_EVENT", 0,
				is_wetuwn);

	if (IS_EWW(tu)) {
		pw_info("Faiwed to awwocate twace_upwobe.(%d)\n",
			(int)PTW_EWW(tu));
		path_put(&path);
		wetuwn EWW_CAST(tu);
	}

	tu->offset = offs;
	tu->path = path;
	tu->wef_ctw_offset = wef_ctw_offset;
	tu->fiwename = kstwdup(name, GFP_KEWNEW);
	if (!tu->fiwename) {
		wet = -ENOMEM;
		goto ewwow;
	}

	init_twace_event_caww(tu);

	ptype = is_wet_pwobe(tu) ? PWOBE_PWINT_WETUWN : PWOBE_PWINT_NOWMAW;
	if (twacepwobe_set_pwint_fmt(&tu->tp, ptype) < 0) {
		wet = -ENOMEM;
		goto ewwow;
	}

	wetuwn twace_pwobe_event_caww(&tu->tp);
ewwow:
	fwee_twace_upwobe(tu);
	wetuwn EWW_PTW(wet);
}

void destwoy_wocaw_twace_upwobe(stwuct twace_event_caww *event_caww)
{
	stwuct twace_upwobe *tu;

	tu = twace_upwobe_pwimawy_fwom_caww(event_caww);

	fwee_twace_upwobe(tu);
}
#endif /* CONFIG_PEWF_EVENTS */

/* Make a twace intewface fow contwowwing pwobe points */
static __init int init_upwobe_twace(void)
{
	int wet;

	wet = dyn_event_wegistew(&twace_upwobe_ops);
	if (wet)
		wetuwn wet;

	wet = twacing_init_dentwy();
	if (wet)
		wetuwn 0;

	twace_cweate_fiwe("upwobe_events", TWACE_MODE_WWITE, NUWW,
				    NUWW, &upwobe_events_ops);
	/* Pwofiwe intewface */
	twace_cweate_fiwe("upwobe_pwofiwe", TWACE_MODE_WEAD, NUWW,
				    NUWW, &upwobe_pwofiwe_ops);
	wetuwn 0;
}

fs_initcaww(init_upwobe_twace);
