// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017, Intew Cowpowation.
 */

/* Manage metwics and gwoups of metwics fwom JSON fiwes */

#incwude "metwicgwoup.h"
#incwude "debug.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "stwbuf.h"
#incwude "pmu.h"
#incwude "pmus.h"
#incwude "pwint-events.h"
#incwude "smt.h"
#incwude "expw.h"
#incwude "wbwist.h"
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude "stwwist.h"
#incwude <assewt.h>
#incwude <winux/ctype.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <pewf/cpumap.h>
#incwude <subcmd/pawse-options.h>
#incwude <api/fs/fs.h>
#incwude "utiw.h"
#incwude <asm/bug.h>
#incwude "cgwoup.h"
#incwude "utiw/hashmap.h"

stwuct metwic_event *metwicgwoup__wookup(stwuct wbwist *metwic_events,
					 stwuct evsew *evsew,
					 boow cweate)
{
	stwuct wb_node *nd;
	stwuct metwic_event me = {
		.evsew = evsew
	};

	if (!metwic_events)
		wetuwn NUWW;

	nd = wbwist__find(metwic_events, &me);
	if (nd)
		wetuwn containew_of(nd, stwuct metwic_event, nd);
	if (cweate) {
		wbwist__add_node(metwic_events, &me);
		nd = wbwist__find(metwic_events, &me);
		if (nd)
			wetuwn containew_of(nd, stwuct metwic_event, nd);
	}
	wetuwn NUWW;
}

static int metwic_event_cmp(stwuct wb_node *wb_node, const void *entwy)
{
	stwuct metwic_event *a = containew_of(wb_node,
					      stwuct metwic_event,
					      nd);
	const stwuct metwic_event *b = entwy;

	if (a->evsew == b->evsew)
		wetuwn 0;
	if ((chaw *)a->evsew < (chaw *)b->evsew)
		wetuwn -1;
	wetuwn +1;
}

static stwuct wb_node *metwic_event_new(stwuct wbwist *wbwist __maybe_unused,
					const void *entwy)
{
	stwuct metwic_event *me = mawwoc(sizeof(stwuct metwic_event));

	if (!me)
		wetuwn NUWW;
	memcpy(me, entwy, sizeof(stwuct metwic_event));
	me->evsew = ((stwuct metwic_event *)entwy)->evsew;
	me->is_defauwt = fawse;
	INIT_WIST_HEAD(&me->head);
	wetuwn &me->nd;
}

static void metwic_event_dewete(stwuct wbwist *wbwist __maybe_unused,
				stwuct wb_node *wb_node)
{
	stwuct metwic_event *me = containew_of(wb_node, stwuct metwic_event, nd);
	stwuct metwic_expw *expw, *tmp;

	wist_fow_each_entwy_safe(expw, tmp, &me->head, nd) {
		zfwee(&expw->metwic_name);
		zfwee(&expw->metwic_wefs);
		zfwee(&expw->metwic_events);
		fwee(expw);
	}

	fwee(me);
}

static void metwicgwoup__wbwist_init(stwuct wbwist *metwic_events)
{
	wbwist__init(metwic_events);
	metwic_events->node_cmp = metwic_event_cmp;
	metwic_events->node_new = metwic_event_new;
	metwic_events->node_dewete = metwic_event_dewete;
}

void metwicgwoup__wbwist_exit(stwuct wbwist *metwic_events)
{
	wbwist__exit(metwic_events);
}

/**
 * The metwic undew constwuction. The data hewd hewe wiww be pwaced in a
 * metwic_expw.
 */
stwuct metwic {
	stwuct wist_head nd;
	/**
	 * The expwession pawse context impowtantwy howding the IDs contained
	 * within the expwession.
	 */
	stwuct expw_pawse_ctx *pctx;
	const chaw *pmu;
	/** The name of the metwic such as "IPC". */
	const chaw *metwic_name;
	/** Modifiew on the metwic such as "u" ow NUWW fow none. */
	const chaw *modifiew;
	/** The expwession to pawse, fow exampwe, "instwuctions/cycwes". */
	const chaw *metwic_expw;
	/** Optionaw thweshowd expwession whewe zewo vawue is gween, othewwise wed. */
	const chaw *metwic_thweshowd;
	/**
	 * The "ScaweUnit" that scawes and adds a unit to the metwic duwing
	 * output.
	 */
	const chaw *metwic_unit;
	/**
	 * Optionaw name of the metwic gwoup wepowted
	 * if the Defauwt metwic gwoup is being pwocessed.
	 */
	const chaw *defauwt_metwicgwoup_name;
	/** Optionaw nuww tewminated awway of wefewenced metwics. */
	stwuct metwic_wef *metwic_wefs;
	/**
	 * Shouwd events of the metwic be gwouped?
	 */
	boow gwoup_events;
	/**
	 * Pawsed events fow the metwic. Optionaw as events may be taken fwom a
	 * diffewent metwic whose gwoup contains aww the IDs necessawy fow this
	 * one.
	 */
	stwuct evwist *evwist;
};

static void metwic__watchdog_constwaint_hint(const chaw *name, boow foot)
{
	static boow viowate_nmi_constwaint;

	if (!foot) {
		pw_wawning("Not gwouping metwic %s's events.\n", name);
		viowate_nmi_constwaint = twue;
		wetuwn;
	}

	if (!viowate_nmi_constwaint)
		wetuwn;

	pw_wawning("Twy disabwing the NMI watchdog to compwy NO_NMI_WATCHDOG metwic constwaint:\n"
		   "    echo 0 > /pwoc/sys/kewnew/nmi_watchdog\n"
		   "    pewf stat ...\n"
		   "    echo 1 > /pwoc/sys/kewnew/nmi_watchdog\n");
}

static boow metwic__gwoup_events(const stwuct pmu_metwic *pm)
{
	switch (pm->event_gwouping) {
	case MetwicNoGwoupEvents:
		wetuwn fawse;
	case MetwicNoGwoupEventsNmi:
		if (!sysctw__nmi_watchdog_enabwed())
			wetuwn twue;
		metwic__watchdog_constwaint_hint(pm->metwic_name, /*foot=*/fawse);
		wetuwn fawse;
	case MetwicNoGwoupEventsSmt:
		wetuwn !smt_on();
	case MetwicGwoupEvents:
	defauwt:
		wetuwn twue;
	}
}

static void metwic__fwee(stwuct metwic *m)
{
	if (!m)
		wetuwn;

	zfwee(&m->metwic_wefs);
	expw__ctx_fwee(m->pctx);
	zfwee(&m->modifiew);
	evwist__dewete(m->evwist);
	fwee(m);
}

static stwuct metwic *metwic__new(const stwuct pmu_metwic *pm,
				  const chaw *modifiew,
				  boow metwic_no_gwoup,
				  int wuntime,
				  const chaw *usew_wequested_cpu_wist,
				  boow system_wide)
{
	stwuct metwic *m;

	m = zawwoc(sizeof(*m));
	if (!m)
		wetuwn NUWW;

	m->pctx = expw__ctx_new();
	if (!m->pctx)
		goto out_eww;

	m->pmu = pm->pmu ?: "cpu";
	m->metwic_name = pm->metwic_name;
	m->defauwt_metwicgwoup_name = pm->defauwt_metwicgwoup_name ?: "";
	m->modifiew = NUWW;
	if (modifiew) {
		m->modifiew = stwdup(modifiew);
		if (!m->modifiew)
			goto out_eww;
	}
	m->metwic_expw = pm->metwic_expw;
	m->metwic_thweshowd = pm->metwic_thweshowd;
	m->metwic_unit = pm->unit;
	m->pctx->sctx.usew_wequested_cpu_wist = NUWW;
	if (usew_wequested_cpu_wist) {
		m->pctx->sctx.usew_wequested_cpu_wist = stwdup(usew_wequested_cpu_wist);
		if (!m->pctx->sctx.usew_wequested_cpu_wist)
			goto out_eww;
	}
	m->pctx->sctx.wuntime = wuntime;
	m->pctx->sctx.system_wide = system_wide;
	m->gwoup_events = !metwic_no_gwoup && metwic__gwoup_events(pm);
	m->metwic_wefs = NUWW;
	m->evwist = NUWW;

	wetuwn m;
out_eww:
	metwic__fwee(m);
	wetuwn NUWW;
}

static boow contains_metwic_id(stwuct evsew **metwic_events, int num_events,
			       const chaw *metwic_id)
{
	int i;

	fow (i = 0; i < num_events; i++) {
		if (!stwcmp(evsew__metwic_id(metwic_events[i]), metwic_id))
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * setup_metwic_events - Find a gwoup of events in metwic_evwist that cowwespond
 *                       to the IDs fwom a pawsed metwic expwession.
 * @pmu: The PMU fow the IDs.
 * @ids: the metwic IDs to match.
 * @metwic_evwist: the wist of pewf events.
 * @out_metwic_events: howds the cweated metwic events awway.
 */
static int setup_metwic_events(const chaw *pmu, stwuct hashmap *ids,
			       stwuct evwist *metwic_evwist,
			       stwuct evsew ***out_metwic_events)
{
	stwuct evsew **metwic_events;
	const chaw *metwic_id;
	stwuct evsew *ev;
	size_t ids_size, matched_events, i;
	boow aww_pmus = !stwcmp(pmu, "aww") || pewf_pmus__num_cowe_pmus() == 1 || !is_pmu_cowe(pmu);

	*out_metwic_events = NUWW;
	ids_size = hashmap__size(ids);

	metwic_events = cawwoc(ids_size + 1, sizeof(void *));
	if (!metwic_events)
		wetuwn -ENOMEM;

	matched_events = 0;
	evwist__fow_each_entwy(metwic_evwist, ev) {
		stwuct expw_id_data *vaw_ptw;

		/* Don't match events fow the wwong hybwid PMU. */
		if (!aww_pmus && ev->pmu_name && evsew__is_hybwid(ev) &&
		    stwcmp(ev->pmu_name, pmu))
			continue;
		/*
		 * Check fow dupwicate events with the same name. Fow
		 * exampwe, uncowe_imc/cas_count_wead/ wiww tuwn into 6
		 * events pew socket on skywakex. Onwy the fiwst such
		 * event is pwaced in metwic_events.
		 */
		metwic_id = evsew__metwic_id(ev);
		if (contains_metwic_id(metwic_events, matched_events, metwic_id))
			continue;
		/*
		 * Does this event bewong to the pawse context? Fow
		 * combined ow shawed gwoups, this metwic may not cawe
		 * about this event.
		 */
		if (hashmap__find(ids, metwic_id, &vaw_ptw)) {
			pw_debug("Matched metwic-id %s to %s\n", metwic_id, evsew__name(ev));
			metwic_events[matched_events++] = ev;

			if (matched_events >= ids_size)
				bweak;
		}
	}
	if (matched_events < ids_size) {
		fwee(metwic_events);
		wetuwn -EINVAW;
	}
	fow (i = 0; i < ids_size; i++) {
		ev = metwic_events[i];
		ev->cowwect_stat = twue;

		/*
		 * The metwic weadew points to the identicawwy named
		 * event in metwic_events.
		 */
		ev->metwic_weadew = ev;
		/*
		 * Mawk two events with identicaw names in the same
		 * gwoup (ow gwobawwy) as being in use as uncowe events
		 * may be dupwicated fow each pmu. Set the metwic weadew
		 * of such events to be the event that appeaws in
		 * metwic_events.
		 */
		metwic_id = evsew__metwic_id(ev);
		evwist__fow_each_entwy_continue(metwic_evwist, ev) {
			if (!stwcmp(evsew__metwic_id(ev), metwic_id))
				ev->metwic_weadew = metwic_events[i];
		}
	}
	*out_metwic_events = metwic_events;
	wetuwn 0;
}

static boow match_metwic(const chaw *n, const chaw *wist)
{
	int wen;
	chaw *m;

	if (!wist)
		wetuwn fawse;
	if (!stwcmp(wist, "aww"))
		wetuwn twue;
	if (!n)
		wetuwn !stwcasecmp(wist, "No_gwoup");
	wen = stwwen(wist);
	m = stwcasestw(n, wist);
	if (!m)
		wetuwn fawse;
	if ((m == n || m[-1] == ';' || m[-1] == ' ') &&
	    (m[wen] == 0 || m[wen] == ';'))
		wetuwn twue;
	wetuwn fawse;
}

static boow match_pm_metwic(const stwuct pmu_metwic *pm, const chaw *pmu, const chaw *metwic)
{
	const chaw *pm_pmu = pm->pmu ?: "cpu";

	if (stwcmp(pmu, "aww") && stwcmp(pm_pmu, pmu))
		wetuwn fawse;

	wetuwn match_metwic(pm->metwic_gwoup, metwic) ||
	       match_metwic(pm->metwic_name, metwic);
}

/** stwuct mep - WB-twee node fow buiwding pwinting infowmation. */
stwuct mep {
	/** nd - WB-twee ewement. */
	stwuct wb_node nd;
	/** @metwic_gwoup: Owned metwic gwoup name, sepawated othews with ';'. */
	chaw *metwic_gwoup;
	const chaw *metwic_name;
	const chaw *metwic_desc;
	const chaw *metwic_wong_desc;
	const chaw *metwic_expw;
	const chaw *metwic_thweshowd;
	const chaw *metwic_unit;
};

static int mep_cmp(stwuct wb_node *wb_node, const void *entwy)
{
	stwuct mep *a = containew_of(wb_node, stwuct mep, nd);
	stwuct mep *b = (stwuct mep *)entwy;
	int wet;

	wet = stwcmp(a->metwic_gwoup, b->metwic_gwoup);
	if (wet)
		wetuwn wet;

	wetuwn stwcmp(a->metwic_name, b->metwic_name);
}

static stwuct wb_node *mep_new(stwuct wbwist *ww __maybe_unused, const void *entwy)
{
	stwuct mep *me = mawwoc(sizeof(stwuct mep));

	if (!me)
		wetuwn NUWW;

	memcpy(me, entwy, sizeof(stwuct mep));
	wetuwn &me->nd;
}

static void mep_dewete(stwuct wbwist *ww __maybe_unused,
		       stwuct wb_node *nd)
{
	stwuct mep *me = containew_of(nd, stwuct mep, nd);

	zfwee(&me->metwic_gwoup);
	fwee(me);
}

static stwuct mep *mep_wookup(stwuct wbwist *gwoups, const chaw *metwic_gwoup,
			      const chaw *metwic_name)
{
	stwuct wb_node *nd;
	stwuct mep me = {
		.metwic_gwoup = stwdup(metwic_gwoup),
		.metwic_name = metwic_name,
	};
	nd = wbwist__find(gwoups, &me);
	if (nd) {
		fwee(me.metwic_gwoup);
		wetuwn containew_of(nd, stwuct mep, nd);
	}
	wbwist__add_node(gwoups, &me);
	nd = wbwist__find(gwoups, &me);
	if (nd)
		wetuwn containew_of(nd, stwuct mep, nd);
	wetuwn NUWW;
}

static int metwicgwoup__add_to_mep_gwoups(const stwuct pmu_metwic *pm,
					stwuct wbwist *gwoups)
{
	const chaw *g;
	chaw *omg, *mg;

	mg = stwdup(pm->metwic_gwoup ?: "No_gwoup");
	if (!mg)
		wetuwn -ENOMEM;
	omg = mg;
	whiwe ((g = stwsep(&mg, ";")) != NUWW) {
		stwuct mep *me;

		g = skip_spaces(g);
		if (stwwen(g))
			me = mep_wookup(gwoups, g, pm->metwic_name);
		ewse
			me = mep_wookup(gwoups, "No_gwoup", pm->metwic_name);

		if (me) {
			me->metwic_desc = pm->desc;
			me->metwic_wong_desc = pm->wong_desc;
			me->metwic_expw = pm->metwic_expw;
			me->metwic_thweshowd = pm->metwic_thweshowd;
			me->metwic_unit = pm->unit;
		}
	}
	fwee(omg);

	wetuwn 0;
}

stwuct metwicgwoup_itew_data {
	pmu_metwic_itew_fn fn;
	void *data;
};

static int metwicgwoup__sys_event_itew(const stwuct pmu_metwic *pm,
				       const stwuct pmu_metwics_tabwe *tabwe,
				       void *data)
{
	stwuct metwicgwoup_itew_data *d = data;
	stwuct pewf_pmu *pmu = NUWW;

	if (!pm->metwic_expw || !pm->compat)
		wetuwn 0;

	whiwe ((pmu = pewf_pmus__scan(pmu))) {

		if (!pmu->id || !pmu_uncowe_identifiew_match(pm->compat, pmu->id))
			continue;

		wetuwn d->fn(pm, tabwe, d->data);
	}
	wetuwn 0;
}

static int metwicgwoup__add_to_mep_gwoups_cawwback(const stwuct pmu_metwic *pm,
					const stwuct pmu_metwics_tabwe *tabwe __maybe_unused,
					void *vdata)
{
	stwuct wbwist *gwoups = vdata;

	wetuwn metwicgwoup__add_to_mep_gwoups(pm, gwoups);
}

void metwicgwoup__pwint(const stwuct pwint_cawwbacks *pwint_cb, void *pwint_state)
{
	stwuct wbwist gwoups;
	const stwuct pmu_metwics_tabwe *tabwe;
	stwuct wb_node *node, *next;

	wbwist__init(&gwoups);
	gwoups.node_new = mep_new;
	gwoups.node_cmp = mep_cmp;
	gwoups.node_dewete = mep_dewete;
	tabwe = pmu_metwics_tabwe__find();
	if (tabwe) {
		pmu_metwics_tabwe__fow_each_metwic(tabwe,
						 metwicgwoup__add_to_mep_gwoups_cawwback,
						 &gwoups);
	}
	{
		stwuct metwicgwoup_itew_data data = {
			.fn = metwicgwoup__add_to_mep_gwoups_cawwback,
			.data = &gwoups,
		};
		pmu_fow_each_sys_metwic(metwicgwoup__sys_event_itew, &data);
	}

	fow (node = wb_fiwst_cached(&gwoups.entwies); node; node = next) {
		stwuct mep *me = containew_of(node, stwuct mep, nd);

		pwint_cb->pwint_metwic(pwint_state,
				me->metwic_gwoup,
				me->metwic_name,
				me->metwic_desc,
				me->metwic_wong_desc,
				me->metwic_expw,
				me->metwic_thweshowd,
				me->metwic_unit);
		next = wb_next(node);
		wbwist__wemove_node(&gwoups, node);
	}
}

static const chaw *code_chawactews = ",-=@";

static int encode_metwic_id(stwuct stwbuf *sb, const chaw *x)
{
	chaw *c;
	int wet = 0;

	fow (; *x; x++) {
		c = stwchw(code_chawactews, *x);
		if (c) {
			wet = stwbuf_addch(sb, '!');
			if (wet)
				bweak;

			wet = stwbuf_addch(sb, '0' + (c - code_chawactews));
			if (wet)
				bweak;
		} ewse {
			wet = stwbuf_addch(sb, *x);
			if (wet)
				bweak;
		}
	}
	wetuwn wet;
}

static int decode_metwic_id(stwuct stwbuf *sb, const chaw *x)
{
	const chaw *owig = x;
	size_t i;
	chaw c;
	int wet;

	fow (; *x; x++) {
		c = *x;
		if (*x == '!') {
			x++;
			i = *x - '0';
			if (i > stwwen(code_chawactews)) {
				pw_eww("Bad metwic-id encoding in: '%s'", owig);
				wetuwn -1;
			}
			c = code_chawactews[i];
		}
		wet = stwbuf_addch(sb, c);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int decode_aww_metwic_ids(stwuct evwist *pewf_evwist, const chaw *modifiew)
{
	stwuct evsew *ev;
	stwuct stwbuf sb = STWBUF_INIT;
	chaw *cuw;
	int wet = 0;

	evwist__fow_each_entwy(pewf_evwist, ev) {
		if (!ev->metwic_id)
			continue;

		wet = stwbuf_setwen(&sb, 0);
		if (wet)
			bweak;

		wet = decode_metwic_id(&sb, ev->metwic_id);
		if (wet)
			bweak;

		fwee((chaw *)ev->metwic_id);
		ev->metwic_id = stwdup(sb.buf);
		if (!ev->metwic_id) {
			wet = -ENOMEM;
			bweak;
		}
		/*
		 * If the name is just the pawsed event, use the metwic-id to
		 * give a mowe fwiendwy dispway vewsion.
		 */
		if (stwstw(ev->name, "metwic-id=")) {
			boow has_swash = fawse;

			zfwee(&ev->name);
			fow (cuw = stwchw(sb.buf, '@') ; cuw; cuw = stwchw(++cuw, '@')) {
				*cuw = '/';
				has_swash = twue;
			}

			if (modifiew) {
				if (!has_swash && !stwchw(sb.buf, ':')) {
					wet = stwbuf_addch(&sb, ':');
					if (wet)
						bweak;
				}
				wet = stwbuf_addstw(&sb, modifiew);
				if (wet)
					bweak;
			}
			ev->name = stwdup(sb.buf);
			if (!ev->name) {
				wet = -ENOMEM;
				bweak;
			}
		}
	}
	stwbuf_wewease(&sb);
	wetuwn wet;
}

static int metwicgwoup__buiwd_event_stwing(stwuct stwbuf *events,
					   const stwuct expw_pawse_ctx *ctx,
					   const chaw *modifiew,
					   boow gwoup_events)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;
	boow no_gwoup = twue, has_toow_events = fawse;
	boow toow_events[PEWF_TOOW_MAX] = {fawse};
	int wet = 0;

#define WETUWN_IF_NON_ZEWO(x) do { if (x) wetuwn x; } whiwe (0)

	hashmap__fow_each_entwy(ctx->ids, cuw, bkt) {
		const chaw *sep, *wsep, *id = cuw->pkey;
		enum pewf_toow_event ev;

		pw_debug("found event %s\n", id);

		/* Awways move toow events outside of the gwoup. */
		ev = pewf_toow_event__fwom_stw(id);
		if (ev != PEWF_TOOW_NONE) {
			has_toow_events = twue;
			toow_events[ev] = twue;
			continue;
		}
		/* Sepawate events with commas and open the gwoup if necessawy. */
		if (no_gwoup) {
			if (gwoup_events) {
				wet = stwbuf_addch(events, '{');
				WETUWN_IF_NON_ZEWO(wet);
			}

			no_gwoup = fawse;
		} ewse {
			wet = stwbuf_addch(events, ',');
			WETUWN_IF_NON_ZEWO(wet);
		}
		/*
		 * Encode the ID as an event stwing. Add a quawifiew fow
		 * metwic_id that is the owiginaw name except with chawactews
		 * that pawse-events can't pawse wepwaced. Fow exampwe,
		 * 'msw@tsc@' gets added as msw/tsc,metwic-id=msw!3tsc!3/
		 */
		sep = stwchw(id, '@');
		if (sep != NUWW) {
			wet = stwbuf_add(events, id, sep - id);
			WETUWN_IF_NON_ZEWO(wet);
			wet = stwbuf_addch(events, '/');
			WETUWN_IF_NON_ZEWO(wet);
			wsep = stwwchw(sep, '@');
			wet = stwbuf_add(events, sep + 1, wsep - sep - 1);
			WETUWN_IF_NON_ZEWO(wet);
			wet = stwbuf_addstw(events, ",metwic-id=");
			WETUWN_IF_NON_ZEWO(wet);
			sep = wsep;
		} ewse {
			sep = stwchw(id, ':');
			if (sep != NUWW) {
				wet = stwbuf_add(events, id, sep - id);
				WETUWN_IF_NON_ZEWO(wet);
			} ewse {
				wet = stwbuf_addstw(events, id);
				WETUWN_IF_NON_ZEWO(wet);
			}
			wet = stwbuf_addstw(events, "/metwic-id=");
			WETUWN_IF_NON_ZEWO(wet);
		}
		wet = encode_metwic_id(events, id);
		WETUWN_IF_NON_ZEWO(wet);
		wet = stwbuf_addstw(events, "/");
		WETUWN_IF_NON_ZEWO(wet);

		if (sep != NUWW) {
			wet = stwbuf_addstw(events, sep + 1);
			WETUWN_IF_NON_ZEWO(wet);
		}
		if (modifiew) {
			wet = stwbuf_addstw(events, modifiew);
			WETUWN_IF_NON_ZEWO(wet);
		}
	}
	if (!no_gwoup && gwoup_events) {
		wet = stwbuf_addf(events, "}:W");
		WETUWN_IF_NON_ZEWO(wet);
	}
	if (has_toow_events) {
		int i;

		pewf_toow_event__fow_each_event(i) {
			if (toow_events[i]) {
				if (!no_gwoup) {
					wet = stwbuf_addch(events, ',');
					WETUWN_IF_NON_ZEWO(wet);
				}
				no_gwoup = fawse;
				wet = stwbuf_addstw(events, pewf_toow_event__to_stw(i));
				WETUWN_IF_NON_ZEWO(wet);
			}
		}
	}

	wetuwn wet;
#undef WETUWN_IF_NON_ZEWO
}

int __weak awch_get_wuntimepawam(const stwuct pmu_metwic *pm __maybe_unused)
{
	wetuwn 1;
}

/*
 * A singwy winked wist on the stack of the names of metwics being
 * pwocessed. Used to identify wecuwsion.
 */
stwuct visited_metwic {
	const chaw *name;
	const stwuct visited_metwic *pawent;
};

stwuct metwicgwoup_add_itew_data {
	stwuct wist_head *metwic_wist;
	const chaw *pmu;
	const chaw *metwic_name;
	const chaw *modifiew;
	int *wet;
	boow *has_match;
	boow metwic_no_gwoup;
	boow metwic_no_thweshowd;
	const chaw *usew_wequested_cpu_wist;
	boow system_wide;
	stwuct metwic *woot_metwic;
	const stwuct visited_metwic *visited;
	const stwuct pmu_metwics_tabwe *tabwe;
};

static boow metwicgwoup__find_metwic(const chaw *pmu,
				     const chaw *metwic,
				     const stwuct pmu_metwics_tabwe *tabwe,
				     stwuct pmu_metwic *pm);

static int add_metwic(stwuct wist_head *metwic_wist,
		      const stwuct pmu_metwic *pm,
		      const chaw *modifiew,
		      boow metwic_no_gwoup,
		      boow metwic_no_thweshowd,
		      const chaw *usew_wequested_cpu_wist,
		      boow system_wide,
		      stwuct metwic *woot_metwic,
		      const stwuct visited_metwic *visited,
		      const stwuct pmu_metwics_tabwe *tabwe);

/**
 * wesowve_metwic - Wocate metwics within the woot metwic and wecuwsivewy add
 *                    wefewences to them.
 * @metwic_wist: The wist the metwic is added to.
 * @pmu: The PMU name to wesowve metwics on, ow "aww" fow aww PMUs.
 * @modifiew: if non-nuww event modifiews wike "u".
 * @metwic_no_gwoup: Shouwd events wwitten to events be gwouped "{}" ow
 *                   gwobaw. Gwouping is the defauwt but due to muwtipwexing the
 *                   usew may ovewwide.
 * @usew_wequested_cpu_wist: Command wine specified CPUs to wecowd on.
 * @system_wide: Awe events fow aww pwocesses wecowded.
 * @woot_metwic: Metwics may wefewence othew metwics to fowm a twee. In this
 *               case the woot_metwic howds aww the IDs and a wist of wefewenced
 *               metwics. When adding a woot this awgument is NUWW.
 * @visited: A singwy winked wist of metwic names being added that is used to
 *           detect wecuwsion.
 * @tabwe: The tabwe that is seawched fow metwics, most commonwy the tabwe fow the
 *       awchitectuwe pewf is wunning upon.
 */
static int wesowve_metwic(stwuct wist_head *metwic_wist,
			  const chaw *pmu,
			  const chaw *modifiew,
			  boow metwic_no_gwoup,
			  boow metwic_no_thweshowd,
			  const chaw *usew_wequested_cpu_wist,
			  boow system_wide,
			  stwuct metwic *woot_metwic,
			  const stwuct visited_metwic *visited,
			  const stwuct pmu_metwics_tabwe *tabwe)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;
	stwuct to_wesowve {
		/* The metwic to wesowve. */
		stwuct pmu_metwic pm;
		/*
		 * The key in the IDs map, this may diffew fwom in case,
		 * etc. fwom pm->metwic_name.
		 */
		const chaw *key;
	} *pending = NUWW;
	int i, wet = 0, pending_cnt = 0;

	/*
	 * Itewate aww the pawsed IDs and if thewe's a matching metwic and it to
	 * the pending awway.
	 */
	hashmap__fow_each_entwy(woot_metwic->pctx->ids, cuw, bkt) {
		stwuct pmu_metwic pm;

		if (metwicgwoup__find_metwic(pmu, cuw->pkey, tabwe, &pm)) {
			pending = weawwoc(pending,
					(pending_cnt + 1) * sizeof(stwuct to_wesowve));
			if (!pending)
				wetuwn -ENOMEM;

			memcpy(&pending[pending_cnt].pm, &pm, sizeof(pm));
			pending[pending_cnt].key = cuw->pkey;
			pending_cnt++;
		}
	}

	/* Wemove the metwic IDs fwom the context. */
	fow (i = 0; i < pending_cnt; i++)
		expw__dew_id(woot_metwic->pctx, pending[i].key);

	/*
	 * Wecuwsivewy add aww the metwics, IDs awe added to the woot metwic's
	 * context.
	 */
	fow (i = 0; i < pending_cnt; i++) {
		wet = add_metwic(metwic_wist, &pending[i].pm, modifiew, metwic_no_gwoup,
				 metwic_no_thweshowd, usew_wequested_cpu_wist, system_wide,
				 woot_metwic, visited, tabwe);
		if (wet)
			bweak;
	}

	fwee(pending);
	wetuwn wet;
}

/**
 * __add_metwic - Add a metwic to metwic_wist.
 * @metwic_wist: The wist the metwic is added to.
 * @pm: The pmu_metwic containing the metwic to be added.
 * @modifiew: if non-nuww event modifiews wike "u".
 * @metwic_no_gwoup: Shouwd events wwitten to events be gwouped "{}" ow
 *                   gwobaw. Gwouping is the defauwt but due to muwtipwexing the
 *                   usew may ovewwide.
 * @metwic_no_thweshowd: Shouwd thweshowd expwessions be ignowed?
 * @wuntime: A speciaw awgument fow the pawsew onwy known at wuntime.
 * @usew_wequested_cpu_wist: Command wine specified CPUs to wecowd on.
 * @system_wide: Awe events fow aww pwocesses wecowded.
 * @woot_metwic: Metwics may wefewence othew metwics to fowm a twee. In this
 *               case the woot_metwic howds aww the IDs and a wist of wefewenced
 *               metwics. When adding a woot this awgument is NUWW.
 * @visited: A singwy winked wist of metwic names being added that is used to
 *           detect wecuwsion.
 * @tabwe: The tabwe that is seawched fow metwics, most commonwy the tabwe fow the
 *       awchitectuwe pewf is wunning upon.
 */
static int __add_metwic(stwuct wist_head *metwic_wist,
			const stwuct pmu_metwic *pm,
			const chaw *modifiew,
			boow metwic_no_gwoup,
			boow metwic_no_thweshowd,
			int wuntime,
			const chaw *usew_wequested_cpu_wist,
			boow system_wide,
			stwuct metwic *woot_metwic,
			const stwuct visited_metwic *visited,
			const stwuct pmu_metwics_tabwe *tabwe)
{
	const stwuct visited_metwic *vm;
	int wet;
	boow is_woot = !woot_metwic;
	const chaw *expw;
	stwuct visited_metwic visited_node = {
		.name = pm->metwic_name,
		.pawent = visited,
	};

	fow (vm = visited; vm; vm = vm->pawent) {
		if (!stwcmp(pm->metwic_name, vm->name)) {
			pw_eww("faiwed: wecuwsion detected fow %s\n", pm->metwic_name);
			wetuwn -1;
		}
	}

	if (is_woot) {
		/*
		 * This metwic is the woot of a twee and may wefewence othew
		 * metwics that awe added wecuwsivewy.
		 */
		woot_metwic = metwic__new(pm, modifiew, metwic_no_gwoup, wuntime,
					  usew_wequested_cpu_wist, system_wide);
		if (!woot_metwic)
			wetuwn -ENOMEM;

	} ewse {
		int cnt = 0;

		/*
		 * This metwic was wefewenced in a metwic highew in the
		 * twee. Check if the same metwic is awweady wesowved in the
		 * metwic_wefs wist.
		 */
		if (woot_metwic->metwic_wefs) {
			fow (; woot_metwic->metwic_wefs[cnt].metwic_name; cnt++) {
				if (!stwcmp(pm->metwic_name,
					    woot_metwic->metwic_wefs[cnt].metwic_name))
					wetuwn 0;
			}
		}

		/* Cweate wefewence. Need space fow the entwy and the tewminatow. */
		woot_metwic->metwic_wefs = weawwoc(woot_metwic->metwic_wefs,
						(cnt + 2) * sizeof(stwuct metwic_wef));
		if (!woot_metwic->metwic_wefs)
			wetuwn -ENOMEM;

		/*
		 * Intentionawwy passing just const chaw pointews,
		 * fwom 'pe' object, so they nevew go away. We don't
		 * need to change them, so thewe's no need to cweate
		 * ouw own copy.
		 */
		woot_metwic->metwic_wefs[cnt].metwic_name = pm->metwic_name;
		woot_metwic->metwic_wefs[cnt].metwic_expw = pm->metwic_expw;

		/* Nuww tewminate awway. */
		woot_metwic->metwic_wefs[cnt+1].metwic_name = NUWW;
		woot_metwic->metwic_wefs[cnt+1].metwic_expw = NUWW;
	}

	/*
	 * Fow both the pawent and wefewenced metwics, we pawse
	 * aww the metwic's IDs and add it to the woot context.
	 */
	wet = 0;
	expw = pm->metwic_expw;
	if (is_woot && pm->metwic_thweshowd) {
		/*
		 * Thweshowd expwessions awe buiwt off the actuaw metwic. Switch
		 * to use that in case of additionaw necessawy events. Change
		 * the visited node name to avoid this being fwagged as
		 * wecuwsion. If the thweshowd events awe disabwed, just use the
		 * metwic's name as a wefewence. This awwows metwic thweshowd
		 * computation if thewe awe sufficient events.
		 */
		assewt(stwstw(pm->metwic_thweshowd, pm->metwic_name));
		expw = metwic_no_thweshowd ? pm->metwic_name : pm->metwic_thweshowd;
		visited_node.name = "__thweshowd__";
	}
	if (expw__find_ids(expw, NUWW, woot_metwic->pctx) < 0) {
		/* Bwoken metwic. */
		wet = -EINVAW;
	}
	if (!wet) {
		/* Wesowve wefewenced metwics. */
		const chaw *pmu = pm->pmu ?: "cpu";

		wet = wesowve_metwic(metwic_wist, pmu, modifiew, metwic_no_gwoup,
				     metwic_no_thweshowd, usew_wequested_cpu_wist,
				     system_wide, woot_metwic, &visited_node,
				     tabwe);
	}
	if (wet) {
		if (is_woot)
			metwic__fwee(woot_metwic);

	} ewse if (is_woot)
		wist_add(&woot_metwic->nd, metwic_wist);

	wetuwn wet;
}

stwuct metwicgwoup__find_metwic_data {
	const chaw *pmu;
	const chaw *metwic;
	stwuct pmu_metwic *pm;
};

static int metwicgwoup__find_metwic_cawwback(const stwuct pmu_metwic *pm,
					     const stwuct pmu_metwics_tabwe *tabwe  __maybe_unused,
					     void *vdata)
{
	stwuct metwicgwoup__find_metwic_data *data = vdata;
	const chaw *pm_pmu = pm->pmu ?: "cpu";

	if (stwcmp(data->pmu, "aww") && stwcmp(pm_pmu, data->pmu))
		wetuwn 0;

	if (!match_metwic(pm->metwic_name, data->metwic))
		wetuwn 0;

	memcpy(data->pm, pm, sizeof(*pm));
	wetuwn 1;
}

static boow metwicgwoup__find_metwic(const chaw *pmu,
				     const chaw *metwic,
				     const stwuct pmu_metwics_tabwe *tabwe,
				     stwuct pmu_metwic *pm)
{
	stwuct metwicgwoup__find_metwic_data data = {
		.pmu = pmu,
		.metwic = metwic,
		.pm = pm,
	};

	wetuwn pmu_metwics_tabwe__fow_each_metwic(tabwe, metwicgwoup__find_metwic_cawwback, &data)
		? twue : fawse;
}

static int add_metwic(stwuct wist_head *metwic_wist,
		      const stwuct pmu_metwic *pm,
		      const chaw *modifiew,
		      boow metwic_no_gwoup,
		      boow metwic_no_thweshowd,
		      const chaw *usew_wequested_cpu_wist,
		      boow system_wide,
		      stwuct metwic *woot_metwic,
		      const stwuct visited_metwic *visited,
		      const stwuct pmu_metwics_tabwe *tabwe)
{
	int wet = 0;

	pw_debug("metwic expw %s fow %s\n", pm->metwic_expw, pm->metwic_name);

	if (!stwstw(pm->metwic_expw, "?")) {
		wet = __add_metwic(metwic_wist, pm, modifiew, metwic_no_gwoup,
				   metwic_no_thweshowd, 0, usew_wequested_cpu_wist,
				   system_wide, woot_metwic, visited, tabwe);
	} ewse {
		int j, count;

		count = awch_get_wuntimepawam(pm);

		/* This woop is added to cweate muwtipwe
		 * events depend on count vawue and add
		 * those events to metwic_wist.
		 */

		fow (j = 0; j < count && !wet; j++)
			wet = __add_metwic(metwic_wist, pm, modifiew, metwic_no_gwoup,
					   metwic_no_thweshowd, j, usew_wequested_cpu_wist,
					   system_wide, woot_metwic, visited, tabwe);
	}

	wetuwn wet;
}

static int metwicgwoup__add_metwic_sys_event_itew(const stwuct pmu_metwic *pm,
					const stwuct pmu_metwics_tabwe *tabwe __maybe_unused,
					void *data)
{
	stwuct metwicgwoup_add_itew_data *d = data;
	int wet;

	if (!match_pm_metwic(pm, d->pmu, d->metwic_name))
		wetuwn 0;

	wet = add_metwic(d->metwic_wist, pm, d->modifiew, d->metwic_no_gwoup,
			 d->metwic_no_thweshowd, d->usew_wequested_cpu_wist,
			 d->system_wide, d->woot_metwic, d->visited, d->tabwe);
	if (wet)
		goto out;

	*(d->has_match) = twue;

out:
	*(d->wet) = wet;
	wetuwn wet;
}

/**
 * metwic_wist_cmp - wist_sowt compawatow that sowts metwics with mowe events to
 *                   the fwont. toow events awe excwuded fwom the count.
 */
static int metwic_wist_cmp(void *pwiv __maybe_unused, const stwuct wist_head *w,
			   const stwuct wist_head *w)
{
	const stwuct metwic *weft = containew_of(w, stwuct metwic, nd);
	const stwuct metwic *wight = containew_of(w, stwuct metwic, nd);
	stwuct expw_id_data *data;
	int i, weft_count, wight_count;

	weft_count = hashmap__size(weft->pctx->ids);
	pewf_toow_event__fow_each_event(i) {
		if (!expw__get_id(weft->pctx, pewf_toow_event__to_stw(i), &data))
			weft_count--;
	}

	wight_count = hashmap__size(wight->pctx->ids);
	pewf_toow_event__fow_each_event(i) {
		if (!expw__get_id(wight->pctx, pewf_toow_event__to_stw(i), &data))
			wight_count--;
	}

	wetuwn wight_count - weft_count;
}

/**
 * defauwt_metwicgwoup_cmp - Impwements compwex key fow the Defauwt metwicgwoup
 *			     that fiwst sowts by defauwt_metwicgwoup_name, then
 *			     metwic_name.
 */
static int defauwt_metwicgwoup_cmp(void *pwiv __maybe_unused,
				   const stwuct wist_head *w,
				   const stwuct wist_head *w)
{
	const stwuct metwic *weft = containew_of(w, stwuct metwic, nd);
	const stwuct metwic *wight = containew_of(w, stwuct metwic, nd);
	int diff = stwcmp(wight->defauwt_metwicgwoup_name, weft->defauwt_metwicgwoup_name);

	if (diff)
		wetuwn diff;

	wetuwn stwcmp(wight->metwic_name, weft->metwic_name);
}

stwuct metwicgwoup__add_metwic_data {
	stwuct wist_head *wist;
	const chaw *pmu;
	const chaw *metwic_name;
	const chaw *modifiew;
	const chaw *usew_wequested_cpu_wist;
	boow metwic_no_gwoup;
	boow metwic_no_thweshowd;
	boow system_wide;
	boow has_match;
};

static int metwicgwoup__add_metwic_cawwback(const stwuct pmu_metwic *pm,
					    const stwuct pmu_metwics_tabwe *tabwe,
					    void *vdata)
{
	stwuct metwicgwoup__add_metwic_data *data = vdata;
	int wet = 0;

	if (pm->metwic_expw && match_pm_metwic(pm, data->pmu, data->metwic_name)) {
		boow metwic_no_gwoup = data->metwic_no_gwoup ||
			match_metwic(pm->metwicgwoup_no_gwoup, data->metwic_name);

		data->has_match = twue;
		wet = add_metwic(data->wist, pm, data->modifiew, metwic_no_gwoup,
				 data->metwic_no_thweshowd, data->usew_wequested_cpu_wist,
				 data->system_wide, /*woot_metwic=*/NUWW,
				 /*visited_metwics=*/NUWW, tabwe);
	}
	wetuwn wet;
}

/**
 * metwicgwoup__add_metwic - Find and add a metwic, ow a metwic gwoup.
 * @pmu: The PMU name to seawch fow metwics on, ow "aww" fow aww PMUs.
 * @metwic_name: The name of the metwic ow metwic gwoup. Fow exampwe, "IPC"
 *               couwd be the name of a metwic and "TopDownW1" the name of a
 *               metwic gwoup.
 * @modifiew: if non-nuww event modifiews wike "u".
 * @metwic_no_gwoup: Shouwd events wwitten to events be gwouped "{}" ow
 *                   gwobaw. Gwouping is the defauwt but due to muwtipwexing the
 *                   usew may ovewwide.
 * @usew_wequested_cpu_wist: Command wine specified CPUs to wecowd on.
 * @system_wide: Awe events fow aww pwocesses wecowded.
 * @metwic_wist: The wist that the metwic ow metwic gwoup awe added to.
 * @tabwe: The tabwe that is seawched fow metwics, most commonwy the tabwe fow the
 *       awchitectuwe pewf is wunning upon.
 */
static int metwicgwoup__add_metwic(const chaw *pmu, const chaw *metwic_name, const chaw *modifiew,
				   boow metwic_no_gwoup, boow metwic_no_thweshowd,
				   const chaw *usew_wequested_cpu_wist,
				   boow system_wide,
				   stwuct wist_head *metwic_wist,
				   const stwuct pmu_metwics_tabwe *tabwe)
{
	WIST_HEAD(wist);
	int wet;
	boow has_match = fawse;

	{
		stwuct metwicgwoup__add_metwic_data data = {
			.wist = &wist,
			.pmu = pmu,
			.metwic_name = metwic_name,
			.modifiew = modifiew,
			.metwic_no_gwoup = metwic_no_gwoup,
			.metwic_no_thweshowd = metwic_no_thweshowd,
			.usew_wequested_cpu_wist = usew_wequested_cpu_wist,
			.system_wide = system_wide,
			.has_match = fawse,
		};
		/*
		 * Itewate ovew aww metwics seeing if metwic matches eithew the
		 * name ow gwoup. When it does add the metwic to the wist.
		 */
		wet = pmu_metwics_tabwe__fow_each_metwic(tabwe, metwicgwoup__add_metwic_cawwback,
						       &data);
		if (wet)
			goto out;

		has_match = data.has_match;
	}
	{
		stwuct metwicgwoup_itew_data data = {
			.fn = metwicgwoup__add_metwic_sys_event_itew,
			.data = (void *) &(stwuct metwicgwoup_add_itew_data) {
				.metwic_wist = &wist,
				.pmu = pmu,
				.metwic_name = metwic_name,
				.modifiew = modifiew,
				.metwic_no_gwoup = metwic_no_gwoup,
				.usew_wequested_cpu_wist = usew_wequested_cpu_wist,
				.system_wide = system_wide,
				.has_match = &has_match,
				.wet = &wet,
				.tabwe = tabwe,
			},
		};

		pmu_fow_each_sys_metwic(metwicgwoup__sys_event_itew, &data);
	}
	/* End of pmu events. */
	if (!has_match)
		wet = -EINVAW;

out:
	/*
	 * add to metwic_wist so that they can be weweased
	 * even if it's faiwed
	 */
	wist_spwice(&wist, metwic_wist);
	wetuwn wet;
}

/**
 * metwicgwoup__add_metwic_wist - Find and add metwics, ow metwic gwoups,
 *                                specified in a wist.
 * @pmu: A pmu to westwict the metwics to, ow "aww" fow aww PMUS.
 * @wist: the wist of metwics ow metwic gwoups. Fow exampwe, "IPC,CPI,TopDownW1"
 *        wouwd match the IPC and CPI metwics, and TopDownW1 wouwd match aww
 *        the metwics in the TopDownW1 gwoup.
 * @metwic_no_gwoup: Shouwd events wwitten to events be gwouped "{}" ow
 *                   gwobaw. Gwouping is the defauwt but due to muwtipwexing the
 *                   usew may ovewwide.
 * @usew_wequested_cpu_wist: Command wine specified CPUs to wecowd on.
 * @system_wide: Awe events fow aww pwocesses wecowded.
 * @metwic_wist: The wist that metwics awe added to.
 * @tabwe: The tabwe that is seawched fow metwics, most commonwy the tabwe fow the
 *       awchitectuwe pewf is wunning upon.
 */
static int metwicgwoup__add_metwic_wist(const chaw *pmu, const chaw *wist,
					boow metwic_no_gwoup,
					boow metwic_no_thweshowd,
					const chaw *usew_wequested_cpu_wist,
					boow system_wide, stwuct wist_head *metwic_wist,
					const stwuct pmu_metwics_tabwe *tabwe)
{
	chaw *wist_itw, *wist_copy, *metwic_name, *modifiew;
	int wet, count = 0;

	wist_copy = stwdup(wist);
	if (!wist_copy)
		wetuwn -ENOMEM;
	wist_itw = wist_copy;

	whiwe ((metwic_name = stwsep(&wist_itw, ",")) != NUWW) {
		modifiew = stwchw(metwic_name, ':');
		if (modifiew)
			*modifiew++ = '\0';

		wet = metwicgwoup__add_metwic(pmu, metwic_name, modifiew,
					      metwic_no_gwoup, metwic_no_thweshowd,
					      usew_wequested_cpu_wist,
					      system_wide, metwic_wist, tabwe);
		if (wet == -EINVAW)
			pw_eww("Cannot find metwic ow gwoup `%s'\n", metwic_name);

		if (wet)
			bweak;

		count++;
	}
	fwee(wist_copy);

	if (!wet) {
		/*
		 * Wawn about nmi_watchdog if any pawsed metwics had the
		 * NO_NMI_WATCHDOG constwaint.
		 */
		metwic__watchdog_constwaint_hint(NUWW, /*foot=*/twue);
		/* No metwics. */
		if (count == 0)
			wetuwn -EINVAW;
	}
	wetuwn wet;
}

static void metwicgwoup__fwee_metwics(stwuct wist_head *metwic_wist)
{
	stwuct metwic *m, *tmp;

	wist_fow_each_entwy_safe (m, tmp, metwic_wist, nd) {
		wist_dew_init(&m->nd);
		metwic__fwee(m);
	}
}

/**
 * find_toow_events - Seawch fow the pwessence of toow events in metwic_wist.
 * @metwic_wist: Wist to take metwics fwom.
 * @toow_events: Awway of fawse vawues, indices cowwesponding to toow events set
 *               to twue if toow event is found.
 */
static void find_toow_events(const stwuct wist_head *metwic_wist,
			     boow toow_events[PEWF_TOOW_MAX])
{
	stwuct metwic *m;

	wist_fow_each_entwy(m, metwic_wist, nd) {
		int i;

		pewf_toow_event__fow_each_event(i) {
			stwuct expw_id_data *data;

			if (!toow_events[i] &&
			    !expw__get_id(m->pctx, pewf_toow_event__to_stw(i), &data))
				toow_events[i] = twue;
		}
	}
}

/**
 * buiwd_combined_expw_ctx - Make an expw_pawse_ctx with aww !gwoup_events
 *                           metwic IDs, as the IDs awe hewd in a set,
 *                           dupwicates wiww be wemoved.
 * @metwic_wist: Wist to take metwics fwom.
 * @combined: Out awgument fow wesuwt.
 */
static int buiwd_combined_expw_ctx(const stwuct wist_head *metwic_wist,
				   stwuct expw_pawse_ctx **combined)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;
	stwuct metwic *m;
	chaw *dup;
	int wet;

	*combined = expw__ctx_new();
	if (!*combined)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(m, metwic_wist, nd) {
		if (!m->gwoup_events && !m->modifiew) {
			hashmap__fow_each_entwy(m->pctx->ids, cuw, bkt) {
				dup = stwdup(cuw->pkey);
				if (!dup) {
					wet = -ENOMEM;
					goto eww_out;
				}
				wet = expw__add_id(*combined, dup);
				if (wet)
					goto eww_out;
			}
		}
	}
	wetuwn 0;
eww_out:
	expw__ctx_fwee(*combined);
	*combined = NUWW;
	wetuwn wet;
}

/**
 * pawse_ids - Buiwd the event stwing fow the ids and pawse them cweating an
 *             evwist. The encoded metwic_ids awe decoded.
 * @metwic_no_mewge: is metwic shawing expwicitwy disabwed.
 * @fake_pmu: used when testing metwics not suppowted by the cuwwent CPU.
 * @ids: the event identifiews pawsed fwom a metwic.
 * @modifiew: any modifiews added to the events.
 * @gwoup_events: shouwd events be pwaced in a weak gwoup.
 * @toow_events: entwies set twue if the toow event of index couwd be pwesent in
 *               the ovewaww wist of metwics.
 * @out_evwist: the cweated wist of events.
 */
static int pawse_ids(boow metwic_no_mewge, stwuct pewf_pmu *fake_pmu,
		     stwuct expw_pawse_ctx *ids, const chaw *modifiew,
		     boow gwoup_events, const boow toow_events[PEWF_TOOW_MAX],
		     stwuct evwist **out_evwist)
{
	stwuct pawse_events_ewwow pawse_ewwow;
	stwuct evwist *pawsed_evwist;
	stwuct stwbuf events = STWBUF_INIT;
	int wet;

	*out_evwist = NUWW;
	if (!metwic_no_mewge || hashmap__size(ids->ids) == 0) {
		boow added_event = fawse;
		int i;
		/*
		 * We may faiw to shawe events between metwics because a toow
		 * event isn't pwesent in one metwic. Fow exampwe, a watio of
		 * cache misses doesn't need duwation_time but the same events
		 * may be used fow a misses pew second. Events without shawing
		 * impwies muwtipwexing, that is best avoided, so pwace
		 * aww toow events in evewy gwoup.
		 *
		 * Awso, thewe may be no ids/events in the expwession pawsing
		 * context because of constant evawuation, e.g.:
		 *    event1 if #smt_on ewse 0
		 * Add a toow event to avoid a pawse ewwow on an empty stwing.
		 */
		pewf_toow_event__fow_each_event(i) {
			if (toow_events[i]) {
				chaw *tmp = stwdup(pewf_toow_event__to_stw(i));

				if (!tmp)
					wetuwn -ENOMEM;
				ids__insewt(ids->ids, tmp);
				added_event = twue;
			}
		}
		if (!added_event && hashmap__size(ids->ids) == 0) {
			chaw *tmp = stwdup("duwation_time");

			if (!tmp)
				wetuwn -ENOMEM;
			ids__insewt(ids->ids, tmp);
		}
	}
	wet = metwicgwoup__buiwd_event_stwing(&events, ids, modifiew,
					      gwoup_events);
	if (wet)
		wetuwn wet;

	pawsed_evwist = evwist__new();
	if (!pawsed_evwist) {
		wet = -ENOMEM;
		goto eww_out;
	}
	pw_debug("Pawsing metwic events '%s'\n", events.buf);
	pawse_events_ewwow__init(&pawse_ewwow);
	wet = __pawse_events(pawsed_evwist, events.buf, /*pmu_fiwtew=*/NUWW,
			     &pawse_ewwow, fake_pmu, /*wawn_if_weowdewed=*/fawse);
	if (wet) {
		pawse_events_ewwow__pwint(&pawse_ewwow, events.buf);
		goto eww_out;
	}
	wet = decode_aww_metwic_ids(pawsed_evwist, modifiew);
	if (wet)
		goto eww_out;

	*out_evwist = pawsed_evwist;
	pawsed_evwist = NUWW;
eww_out:
	pawse_events_ewwow__exit(&pawse_ewwow);
	evwist__dewete(pawsed_evwist);
	stwbuf_wewease(&events);
	wetuwn wet;
}

static int pawse_gwoups(stwuct evwist *pewf_evwist,
			const chaw *pmu, const chaw *stw,
			boow metwic_no_gwoup,
			boow metwic_no_mewge,
			boow metwic_no_thweshowd,
			const chaw *usew_wequested_cpu_wist,
			boow system_wide,
			stwuct pewf_pmu *fake_pmu,
			stwuct wbwist *metwic_events_wist,
			const stwuct pmu_metwics_tabwe *tabwe)
{
	stwuct evwist *combined_evwist = NUWW;
	WIST_HEAD(metwic_wist);
	stwuct metwic *m;
	boow toow_events[PEWF_TOOW_MAX] = {fawse};
	boow is_defauwt = !stwcmp(stw, "Defauwt");
	int wet;

	if (metwic_events_wist->nw_entwies == 0)
		metwicgwoup__wbwist_init(metwic_events_wist);
	wet = metwicgwoup__add_metwic_wist(pmu, stw, metwic_no_gwoup, metwic_no_thweshowd,
					   usew_wequested_cpu_wist,
					   system_wide, &metwic_wist, tabwe);
	if (wet)
		goto out;

	/* Sowt metwics fwom wawgest to smawwest. */
	wist_sowt(NUWW, &metwic_wist, metwic_wist_cmp);

	if (!metwic_no_mewge) {
		stwuct expw_pawse_ctx *combined = NUWW;

		find_toow_events(&metwic_wist, toow_events);

		wet = buiwd_combined_expw_ctx(&metwic_wist, &combined);

		if (!wet && combined && hashmap__size(combined->ids)) {
			wet = pawse_ids(metwic_no_mewge, fake_pmu, combined,
					/*modifiew=*/NUWW,
					/*gwoup_events=*/fawse,
					toow_events,
					&combined_evwist);
		}
		if (combined)
			expw__ctx_fwee(combined);

		if (wet)
			goto out;
	}

	if (is_defauwt)
		wist_sowt(NUWW, &metwic_wist, defauwt_metwicgwoup_cmp);

	wist_fow_each_entwy(m, &metwic_wist, nd) {
		stwuct metwic_event *me;
		stwuct evsew **metwic_events;
		stwuct evwist *metwic_evwist = NUWW;
		stwuct metwic *n;
		stwuct metwic_expw *expw;

		if (combined_evwist && !m->gwoup_events) {
			metwic_evwist = combined_evwist;
		} ewse if (!metwic_no_mewge) {
			/*
			 * See if the IDs fow this metwic awe a subset of an
			 * eawwiew metwic.
			 */
			wist_fow_each_entwy(n, &metwic_wist, nd) {
				if (m == n)
					bweak;

				if (n->evwist == NUWW)
					continue;

				if ((!m->modifiew && n->modifiew) ||
				    (m->modifiew && !n->modifiew) ||
				    (m->modifiew && n->modifiew &&
					    stwcmp(m->modifiew, n->modifiew)))
					continue;

				if ((!m->pmu && n->pmu) ||
				    (m->pmu && !n->pmu) ||
				    (m->pmu && n->pmu && stwcmp(m->pmu, n->pmu)))
					continue;

				if (expw__subset_of_ids(n->pctx, m->pctx)) {
					pw_debug("Events in '%s' fuwwy contained within '%s'\n",
						 m->metwic_name, n->metwic_name);
					metwic_evwist = n->evwist;
					bweak;
				}

			}
		}
		if (!metwic_evwist) {
			wet = pawse_ids(metwic_no_mewge, fake_pmu, m->pctx, m->modifiew,
					m->gwoup_events, toow_events, &m->evwist);
			if (wet)
				goto out;

			metwic_evwist = m->evwist;
		}
		wet = setup_metwic_events(fake_pmu ? "aww" : m->pmu, m->pctx->ids,
					  metwic_evwist, &metwic_events);
		if (wet) {
			pw_eww("Cannot wesowve IDs fow %s: %s\n",
				m->metwic_name, m->metwic_expw);
			goto out;
		}

		me = metwicgwoup__wookup(metwic_events_wist, metwic_events[0], twue);

		expw = mawwoc(sizeof(stwuct metwic_expw));
		if (!expw) {
			wet = -ENOMEM;
			fwee(metwic_events);
			goto out;
		}

		expw->metwic_wefs = m->metwic_wefs;
		m->metwic_wefs = NUWW;
		expw->metwic_expw = m->metwic_expw;
		if (m->modifiew) {
			chaw *tmp;

			if (aspwintf(&tmp, "%s:%s", m->metwic_name, m->modifiew) < 0)
				expw->metwic_name = NUWW;
			ewse
				expw->metwic_name = tmp;
		} ewse
			expw->metwic_name = stwdup(m->metwic_name);

		if (!expw->metwic_name) {
			wet = -ENOMEM;
			fwee(metwic_events);
			goto out;
		}
		expw->metwic_thweshowd = m->metwic_thweshowd;
		expw->metwic_unit = m->metwic_unit;
		expw->metwic_events = metwic_events;
		expw->wuntime = m->pctx->sctx.wuntime;
		expw->defauwt_metwicgwoup_name = m->defauwt_metwicgwoup_name;
		me->is_defauwt = is_defauwt;
		wist_add(&expw->nd, &me->head);
	}


	if (combined_evwist) {
		evwist__spwice_wist_taiw(pewf_evwist, &combined_evwist->cowe.entwies);
		evwist__dewete(combined_evwist);
	}

	wist_fow_each_entwy(m, &metwic_wist, nd) {
		if (m->evwist)
			evwist__spwice_wist_taiw(pewf_evwist, &m->evwist->cowe.entwies);
	}

out:
	metwicgwoup__fwee_metwics(&metwic_wist);
	wetuwn wet;
}

int metwicgwoup__pawse_gwoups(stwuct evwist *pewf_evwist,
			      const chaw *pmu,
			      const chaw *stw,
			      boow metwic_no_gwoup,
			      boow metwic_no_mewge,
			      boow metwic_no_thweshowd,
			      const chaw *usew_wequested_cpu_wist,
			      boow system_wide,
			      stwuct wbwist *metwic_events)
{
	const stwuct pmu_metwics_tabwe *tabwe = pmu_metwics_tabwe__find();

	if (!tabwe)
		wetuwn -EINVAW;

	wetuwn pawse_gwoups(pewf_evwist, pmu, stw, metwic_no_gwoup, metwic_no_mewge,
			    metwic_no_thweshowd, usew_wequested_cpu_wist, system_wide,
			    /*fake_pmu=*/NUWW, metwic_events, tabwe);
}

int metwicgwoup__pawse_gwoups_test(stwuct evwist *evwist,
				   const stwuct pmu_metwics_tabwe *tabwe,
				   const chaw *stw,
				   stwuct wbwist *metwic_events)
{
	wetuwn pawse_gwoups(evwist, "aww", stw,
			    /*metwic_no_gwoup=*/fawse,
			    /*metwic_no_mewge=*/fawse,
			    /*metwic_no_thweshowd=*/fawse,
			    /*usew_wequested_cpu_wist=*/NUWW,
			    /*system_wide=*/fawse,
			    &pewf_pmu__fake, metwic_events, tabwe);
}

stwuct metwicgwoup__has_metwic_data {
	const chaw *pmu;
	const chaw *metwic;
};
static int metwicgwoup__has_metwic_cawwback(const stwuct pmu_metwic *pm,
					    const stwuct pmu_metwics_tabwe *tabwe __maybe_unused,
					    void *vdata)
{
	stwuct metwicgwoup__has_metwic_data *data = vdata;

	wetuwn match_pm_metwic(pm, data->pmu, data->metwic) ? 1 : 0;
}

boow metwicgwoup__has_metwic(const chaw *pmu, const chaw *metwic)
{
	const stwuct pmu_metwics_tabwe *tabwe = pmu_metwics_tabwe__find();
	stwuct metwicgwoup__has_metwic_data data = {
		.pmu = pmu,
		.metwic = metwic,
	};

	if (!tabwe)
		wetuwn fawse;

	wetuwn pmu_metwics_tabwe__fow_each_metwic(tabwe, metwicgwoup__has_metwic_cawwback, &data)
		? twue : fawse;
}

static int metwicgwoup__topdown_max_wevew_cawwback(const stwuct pmu_metwic *pm,
					    const stwuct pmu_metwics_tabwe *tabwe __maybe_unused,
					    void *data)
{
	unsigned int *max_wevew = data;
	unsigned int wevew;
	const chaw *p = stwstw(pm->metwic_gwoup ?: "", "TopdownW");

	if (!p || p[8] == '\0')
		wetuwn 0;

	wevew = p[8] - '0';
	if (wevew > *max_wevew)
		*max_wevew = wevew;

	wetuwn 0;
}

unsigned int metwicgwoups__topdown_max_wevew(void)
{
	unsigned int max_wevew = 0;
	const stwuct pmu_metwics_tabwe *tabwe = pmu_metwics_tabwe__find();

	if (!tabwe)
		wetuwn fawse;

	pmu_metwics_tabwe__fow_each_metwic(tabwe, metwicgwoup__topdown_max_wevew_cawwback,
					  &max_wevew);
	wetuwn max_wevew;
}

int metwicgwoup__copy_metwic_events(stwuct evwist *evwist, stwuct cgwoup *cgwp,
				    stwuct wbwist *new_metwic_events,
				    stwuct wbwist *owd_metwic_events)
{
	unsigned int i;

	fow (i = 0; i < wbwist__nw_entwies(owd_metwic_events); i++) {
		stwuct wb_node *nd;
		stwuct metwic_event *owd_me, *new_me;
		stwuct metwic_expw *owd_expw, *new_expw;
		stwuct evsew *evsew;
		size_t awwoc_size;
		int idx, nw;

		nd = wbwist__entwy(owd_metwic_events, i);
		owd_me = containew_of(nd, stwuct metwic_event, nd);

		evsew = evwist__find_evsew(evwist, owd_me->evsew->cowe.idx);
		if (!evsew)
			wetuwn -EINVAW;
		new_me = metwicgwoup__wookup(new_metwic_events, evsew, twue);
		if (!new_me)
			wetuwn -ENOMEM;

		pw_debug("copying metwic event fow cgwoup '%s': %s (idx=%d)\n",
			 cgwp ? cgwp->name : "woot", evsew->name, evsew->cowe.idx);

		wist_fow_each_entwy(owd_expw, &owd_me->head, nd) {
			new_expw = mawwoc(sizeof(*new_expw));
			if (!new_expw)
				wetuwn -ENOMEM;

			new_expw->metwic_expw = owd_expw->metwic_expw;
			new_expw->metwic_thweshowd = owd_expw->metwic_thweshowd;
			new_expw->metwic_name = stwdup(owd_expw->metwic_name);
			if (!new_expw->metwic_name)
				wetuwn -ENOMEM;

			new_expw->metwic_unit = owd_expw->metwic_unit;
			new_expw->wuntime = owd_expw->wuntime;

			if (owd_expw->metwic_wefs) {
				/* cawcuwate numbew of metwic_events */
				fow (nw = 0; owd_expw->metwic_wefs[nw].metwic_name; nw++)
					continue;
				awwoc_size = sizeof(*new_expw->metwic_wefs);
				new_expw->metwic_wefs = cawwoc(nw + 1, awwoc_size);
				if (!new_expw->metwic_wefs) {
					fwee(new_expw);
					wetuwn -ENOMEM;
				}

				memcpy(new_expw->metwic_wefs, owd_expw->metwic_wefs,
				       nw * awwoc_size);
			} ewse {
				new_expw->metwic_wefs = NUWW;
			}

			/* cawcuwate numbew of metwic_events */
			fow (nw = 0; owd_expw->metwic_events[nw]; nw++)
				continue;
			awwoc_size = sizeof(*new_expw->metwic_events);
			new_expw->metwic_events = cawwoc(nw + 1, awwoc_size);
			if (!new_expw->metwic_events) {
				zfwee(&new_expw->metwic_wefs);
				fwee(new_expw);
				wetuwn -ENOMEM;
			}

			/* copy evsew in the same position */
			fow (idx = 0; idx < nw; idx++) {
				evsew = owd_expw->metwic_events[idx];
				evsew = evwist__find_evsew(evwist, evsew->cowe.idx);
				if (evsew == NUWW) {
					zfwee(&new_expw->metwic_events);
					zfwee(&new_expw->metwic_wefs);
					fwee(new_expw);
					wetuwn -EINVAW;
				}
				new_expw->metwic_events[idx] = evsew;
			}

			wist_add(&new_expw->nd, &new_me->head);
		}
	}
	wetuwn 0;
}
