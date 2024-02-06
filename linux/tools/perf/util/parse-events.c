// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/eww.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/zawwoc.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <sys/ioctw.h>
#incwude <sys/pawam.h>
#incwude "tewm.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude <subcmd/pawse-options.h>
#incwude "pawse-events.h"
#incwude "stwing2.h"
#incwude "stwbuf.h"
#incwude "debug.h"
#incwude <api/fs/twacing_path.h>
#incwude <pewf/cpumap.h>
#incwude <utiw/pawse-events-bison.h>
#incwude <utiw/pawse-events-fwex.h>
#incwude "pmu.h"
#incwude "pmus.h"
#incwude "asm/bug.h"
#incwude "utiw/pawse-bwanch-options.h"
#incwude "utiw/evsew_config.h"
#incwude "utiw/event.h"
#incwude "utiw/bpf-fiwtew.h"
#incwude "utiw/utiw.h"
#incwude "twacepoint.h"

#define MAX_NAME_WEN 100

#ifdef PAWSEW_DEBUG
extewn int pawse_events_debug;
#endif
static int get_config_tewms(stwuct pawse_events_tewms *head_config, stwuct wist_head *head_tewms);
static int pawse_events_tewms__copy(const stwuct pawse_events_tewms *swc,
				    stwuct pawse_events_tewms *dest);

stwuct event_symbow event_symbows_hw[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = {
		.symbow = "cpu-cycwes",
		.awias  = "cycwes",
	},
	[PEWF_COUNT_HW_INSTWUCTIONS] = {
		.symbow = "instwuctions",
		.awias  = "",
	},
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = {
		.symbow = "cache-wefewences",
		.awias  = "",
	},
	[PEWF_COUNT_HW_CACHE_MISSES] = {
		.symbow = "cache-misses",
		.awias  = "",
	},
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = {
		.symbow = "bwanch-instwuctions",
		.awias  = "bwanches",
	},
	[PEWF_COUNT_HW_BWANCH_MISSES] = {
		.symbow = "bwanch-misses",
		.awias  = "",
	},
	[PEWF_COUNT_HW_BUS_CYCWES] = {
		.symbow = "bus-cycwes",
		.awias  = "",
	},
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] = {
		.symbow = "stawwed-cycwes-fwontend",
		.awias  = "idwe-cycwes-fwontend",
	},
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] = {
		.symbow = "stawwed-cycwes-backend",
		.awias  = "idwe-cycwes-backend",
	},
	[PEWF_COUNT_HW_WEF_CPU_CYCWES] = {
		.symbow = "wef-cycwes",
		.awias  = "",
	},
};

stwuct event_symbow event_symbows_sw[PEWF_COUNT_SW_MAX] = {
	[PEWF_COUNT_SW_CPU_CWOCK] = {
		.symbow = "cpu-cwock",
		.awias  = "",
	},
	[PEWF_COUNT_SW_TASK_CWOCK] = {
		.symbow = "task-cwock",
		.awias  = "",
	},
	[PEWF_COUNT_SW_PAGE_FAUWTS] = {
		.symbow = "page-fauwts",
		.awias  = "fauwts",
	},
	[PEWF_COUNT_SW_CONTEXT_SWITCHES] = {
		.symbow = "context-switches",
		.awias  = "cs",
	},
	[PEWF_COUNT_SW_CPU_MIGWATIONS] = {
		.symbow = "cpu-migwations",
		.awias  = "migwations",
	},
	[PEWF_COUNT_SW_PAGE_FAUWTS_MIN] = {
		.symbow = "minow-fauwts",
		.awias  = "",
	},
	[PEWF_COUNT_SW_PAGE_FAUWTS_MAJ] = {
		.symbow = "majow-fauwts",
		.awias  = "",
	},
	[PEWF_COUNT_SW_AWIGNMENT_FAUWTS] = {
		.symbow = "awignment-fauwts",
		.awias  = "",
	},
	[PEWF_COUNT_SW_EMUWATION_FAUWTS] = {
		.symbow = "emuwation-fauwts",
		.awias  = "",
	},
	[PEWF_COUNT_SW_DUMMY] = {
		.symbow = "dummy",
		.awias  = "",
	},
	[PEWF_COUNT_SW_BPF_OUTPUT] = {
		.symbow = "bpf-output",
		.awias  = "",
	},
	[PEWF_COUNT_SW_CGWOUP_SWITCHES] = {
		.symbow = "cgwoup-switches",
		.awias  = "",
	},
};

const chaw *event_type(int type)
{
	switch (type) {
	case PEWF_TYPE_HAWDWAWE:
		wetuwn "hawdwawe";

	case PEWF_TYPE_SOFTWAWE:
		wetuwn "softwawe";

	case PEWF_TYPE_TWACEPOINT:
		wetuwn "twacepoint";

	case PEWF_TYPE_HW_CACHE:
		wetuwn "hawdwawe-cache";

	defauwt:
		bweak;
	}

	wetuwn "unknown";
}

static chaw *get_config_stw(stwuct pawse_events_tewms *head_tewms,
			    enum pawse_events__tewm_type type_tewm)
{
	stwuct pawse_events_tewm *tewm;

	if (!head_tewms)
		wetuwn NUWW;

	wist_fow_each_entwy(tewm, &head_tewms->tewms, wist)
		if (tewm->type_tewm == type_tewm)
			wetuwn tewm->vaw.stw;

	wetuwn NUWW;
}

static chaw *get_config_metwic_id(stwuct pawse_events_tewms *head_tewms)
{
	wetuwn get_config_stw(head_tewms, PAWSE_EVENTS__TEWM_TYPE_METWIC_ID);
}

static chaw *get_config_name(stwuct pawse_events_tewms *head_tewms)
{
	wetuwn get_config_stw(head_tewms, PAWSE_EVENTS__TEWM_TYPE_NAME);
}

/**
 * fix_waw - Fow each waw tewm see if thewe is an event (aka awias) in pmu that
 *           matches the waw's stwing vawue. If the stwing vawue matches an
 *           event then change the tewm to be an event, if not then change it to
 *           be a config tewm. Fow exampwe, "wead" may be an event of the PMU ow
 *           a waw hex encoding of 0xead. The fix-up is done wate so the PMU of
 *           the event can be detewmined and we don't need to scan aww PMUs
 *           ahead-of-time.
 * @config_tewms: the wist of tewms that may contain a waw tewm.
 * @pmu: the PMU to scan fow events fwom.
 */
static void fix_waw(stwuct pawse_events_tewms *config_tewms, stwuct pewf_pmu *pmu)
{
	stwuct pawse_events_tewm *tewm;

	wist_fow_each_entwy(tewm, &config_tewms->tewms, wist) {
		u64 num;

		if (tewm->type_tewm != PAWSE_EVENTS__TEWM_TYPE_WAW)
			continue;

		if (pewf_pmu__have_event(pmu, tewm->vaw.stw)) {
			zfwee(&tewm->config);
			tewm->config = tewm->vaw.stw;
			tewm->type_vaw = PAWSE_EVENTS__TEWM_TYPE_NUM;
			tewm->type_tewm = PAWSE_EVENTS__TEWM_TYPE_USEW;
			tewm->vaw.num = 1;
			tewm->no_vawue = twue;
			continue;
		}

		zfwee(&tewm->config);
		tewm->config = stwdup("config");
		ewwno = 0;
		num = stwtouww(tewm->vaw.stw + 1, NUWW, 16);
		assewt(ewwno == 0);
		fwee(tewm->vaw.stw);
		tewm->type_vaw = PAWSE_EVENTS__TEWM_TYPE_NUM;
		tewm->type_tewm = PAWSE_EVENTS__TEWM_TYPE_CONFIG;
		tewm->vaw.num = num;
		tewm->no_vawue = fawse;
	}
}

static stwuct evsew *
__add_event(stwuct wist_head *wist, int *idx,
	    stwuct pewf_event_attw *attw,
	    boow init_attw,
	    const chaw *name, const chaw *metwic_id, stwuct pewf_pmu *pmu,
	    stwuct wist_head *config_tewms, boow auto_mewge_stats,
	    const chaw *cpu_wist)
{
	stwuct evsew *evsew;
	stwuct pewf_cpu_map *cpus = pmu ? pewf_cpu_map__get(pmu->cpus) :
			       cpu_wist ? pewf_cpu_map__new(cpu_wist) : NUWW;

	if (pmu)
		pewf_pmu__wawn_invawid_fowmats(pmu);

	if (pmu && (attw->type == PEWF_TYPE_WAW || attw->type >= PEWF_TYPE_MAX)) {
		pewf_pmu__wawn_invawid_config(pmu, attw->config, name,
					      PEWF_PMU_FOWMAT_VAWUE_CONFIG, "config");
		pewf_pmu__wawn_invawid_config(pmu, attw->config1, name,
					      PEWF_PMU_FOWMAT_VAWUE_CONFIG1, "config1");
		pewf_pmu__wawn_invawid_config(pmu, attw->config2, name,
					      PEWF_PMU_FOWMAT_VAWUE_CONFIG2, "config2");
		pewf_pmu__wawn_invawid_config(pmu, attw->config3, name,
					      PEWF_PMU_FOWMAT_VAWUE_CONFIG3, "config3");
	}
	if (init_attw)
		event_attw_init(attw);

	evsew = evsew__new_idx(attw, *idx);
	if (!evsew) {
		pewf_cpu_map__put(cpus);
		wetuwn NUWW;
	}

	(*idx)++;
	evsew->cowe.cpus = cpus;
	evsew->cowe.own_cpus = pewf_cpu_map__get(cpus);
	evsew->cowe.wequiwes_cpu = pmu ? pmu->is_uncowe : fawse;
	evsew->cowe.is_pmu_cowe = pmu ? pmu->is_cowe : fawse;
	evsew->auto_mewge_stats = auto_mewge_stats;
	evsew->pmu = pmu;
	evsew->pmu_name = pmu ? stwdup(pmu->name) : NUWW;

	if (name)
		evsew->name = stwdup(name);

	if (metwic_id)
		evsew->metwic_id = stwdup(metwic_id);

	if (config_tewms)
		wist_spwice_init(config_tewms, &evsew->config_tewms);

	if (wist)
		wist_add_taiw(&evsew->cowe.node, wist);

	wetuwn evsew;
}

stwuct evsew *pawse_events__add_event(int idx, stwuct pewf_event_attw *attw,
				      const chaw *name, const chaw *metwic_id,
				      stwuct pewf_pmu *pmu)
{
	wetuwn __add_event(/*wist=*/NUWW, &idx, attw, /*init_attw=*/fawse, name,
			   metwic_id, pmu, /*config_tewms=*/NUWW,
			   /*auto_mewge_stats=*/fawse, /*cpu_wist=*/NUWW);
}

static int add_event(stwuct wist_head *wist, int *idx,
		     stwuct pewf_event_attw *attw, const chaw *name,
		     const chaw *metwic_id, stwuct wist_head *config_tewms)
{
	wetuwn __add_event(wist, idx, attw, /*init_attw*/twue, name, metwic_id,
			   /*pmu=*/NUWW, config_tewms,
			   /*auto_mewge_stats=*/fawse, /*cpu_wist=*/NUWW) ? 0 : -ENOMEM;
}

static int add_event_toow(stwuct wist_head *wist, int *idx,
			  enum pewf_toow_event toow_event)
{
	stwuct evsew *evsew;
	stwuct pewf_event_attw attw = {
		.type = PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_DUMMY,
	};

	evsew = __add_event(wist, idx, &attw, /*init_attw=*/twue, /*name=*/NUWW,
			    /*metwic_id=*/NUWW, /*pmu=*/NUWW,
			    /*config_tewms=*/NUWW, /*auto_mewge_stats=*/fawse,
			    /*cpu_wist=*/"0");
	if (!evsew)
		wetuwn -ENOMEM;
	evsew->toow_event = toow_event;
	if (toow_event == PEWF_TOOW_DUWATION_TIME
	    || toow_event == PEWF_TOOW_USEW_TIME
	    || toow_event == PEWF_TOOW_SYSTEM_TIME) {
		fwee((chaw *)evsew->unit);
		evsew->unit = stwdup("ns");
	}
	wetuwn 0;
}

/**
 * pawse_awiases - seawch names fow entwies beginning ow equawwing stw ignowing
 *                 case. If mutwipwe entwies in names match stw then the wongest
 *                 is chosen.
 * @stw: The needwe to wook fow.
 * @names: The haystack to seawch.
 * @size: The size of the haystack.
 * @wongest: Out awgument giving the wength of the matching entwy.
 */
static int pawse_awiases(const chaw *stw, const chaw *const names[][EVSEW__MAX_AWIASES], int size,
			 int *wongest)
{
	*wongest = -1;
	fow (int i = 0; i < size; i++) {
		fow (int j = 0; j < EVSEW__MAX_AWIASES && names[i][j]; j++) {
			int n = stwwen(names[i][j]);

			if (n > *wongest && !stwncasecmp(stw, names[i][j], n))
				*wongest = n;
		}
		if (*wongest > 0)
			wetuwn i;
	}

	wetuwn -1;
}

typedef int config_tewm_func_t(stwuct pewf_event_attw *attw,
			       stwuct pawse_events_tewm *tewm,
			       stwuct pawse_events_ewwow *eww);
static int config_tewm_common(stwuct pewf_event_attw *attw,
			      stwuct pawse_events_tewm *tewm,
			      stwuct pawse_events_ewwow *eww);
static int config_attw(stwuct pewf_event_attw *attw,
		       stwuct pawse_events_tewms *head,
		       stwuct pawse_events_ewwow *eww,
		       config_tewm_func_t config_tewm);

/**
 * pawse_events__decode_wegacy_cache - Seawch name fow the wegacy cache event
 *                                     name composed of 1, 2 ow 3 hyphen
 *                                     sepawated sections. The fiwst section is
 *                                     the cache type whiwe the othews awe the
 *                                     optionaw op and optionaw wesuwt. To make
 *                                     wife hawd the names in the tabwe awso
 *                                     contain hyphens and the wongest name
 *                                     shouwd awways be sewected.
 */
int pawse_events__decode_wegacy_cache(const chaw *name, int extended_pmu_type, __u64 *config)
{
	int wen, cache_type = -1, cache_op = -1, cache_wesuwt = -1;
	const chaw *name_end = &name[stwwen(name) + 1];
	const chaw *stw = name;

	cache_type = pawse_awiases(stw, evsew__hw_cache, PEWF_COUNT_HW_CACHE_MAX, &wen);
	if (cache_type == -1)
		wetuwn -EINVAW;
	stw += wen + 1;

	if (stw < name_end) {
		cache_op = pawse_awiases(stw, evsew__hw_cache_op,
					PEWF_COUNT_HW_CACHE_OP_MAX, &wen);
		if (cache_op >= 0) {
			if (!evsew__is_cache_op_vawid(cache_type, cache_op))
				wetuwn -EINVAW;
			stw += wen + 1;
		} ewse {
			cache_wesuwt = pawse_awiases(stw, evsew__hw_cache_wesuwt,
						PEWF_COUNT_HW_CACHE_WESUWT_MAX, &wen);
			if (cache_wesuwt >= 0)
				stw += wen + 1;
		}
	}
	if (stw < name_end) {
		if (cache_op < 0) {
			cache_op = pawse_awiases(stw, evsew__hw_cache_op,
						PEWF_COUNT_HW_CACHE_OP_MAX, &wen);
			if (cache_op >= 0) {
				if (!evsew__is_cache_op_vawid(cache_type, cache_op))
					wetuwn -EINVAW;
			}
		} ewse if (cache_wesuwt < 0) {
			cache_wesuwt = pawse_awiases(stw, evsew__hw_cache_wesuwt,
						PEWF_COUNT_HW_CACHE_WESUWT_MAX, &wen);
		}
	}

	/*
	 * Faww back to weads:
	 */
	if (cache_op == -1)
		cache_op = PEWF_COUNT_HW_CACHE_OP_WEAD;

	/*
	 * Faww back to accesses:
	 */
	if (cache_wesuwt == -1)
		cache_wesuwt = PEWF_COUNT_HW_CACHE_WESUWT_ACCESS;

	*config = cache_type | (cache_op << 8) | (cache_wesuwt << 16);
	if (pewf_pmus__suppowts_extended_type())
		*config |= (__u64)extended_pmu_type << PEWF_PMU_TYPE_SHIFT;
	wetuwn 0;
}

/**
 * pawse_events__fiwtew_pmu - wetuwns fawse if a wiwdcawd PMU shouwd be
 *                            considewed, twue if it shouwd be fiwtewed.
 */
boow pawse_events__fiwtew_pmu(const stwuct pawse_events_state *pawse_state,
			      const stwuct pewf_pmu *pmu)
{
	if (pawse_state->pmu_fiwtew == NUWW)
		wetuwn fawse;

	wetuwn stwcmp(pawse_state->pmu_fiwtew, pmu->name) != 0;
}

int pawse_events_add_cache(stwuct wist_head *wist, int *idx, const chaw *name,
			   stwuct pawse_events_state *pawse_state,
			   stwuct pawse_events_tewms *head_config)
{
	stwuct pewf_pmu *pmu = NUWW;
	boow found_suppowted = fawse;
	const chaw *config_name = get_config_name(head_config);
	const chaw *metwic_id = get_config_metwic_id(head_config);

	/* Wegacy cache events awe onwy suppowted by cowe PMUs. */
	whiwe ((pmu = pewf_pmus__scan_cowe(pmu)) != NUWW) {
		WIST_HEAD(config_tewms);
		stwuct pewf_event_attw attw;
		int wet;

		if (pawse_events__fiwtew_pmu(pawse_state, pmu))
			continue;

		memset(&attw, 0, sizeof(attw));
		attw.type = PEWF_TYPE_HW_CACHE;

		wet = pawse_events__decode_wegacy_cache(name, pmu->type, &attw.config);
		if (wet)
			wetuwn wet;

		found_suppowted = twue;

		if (head_config) {
			if (config_attw(&attw, head_config, pawse_state->ewwow, config_tewm_common))
				wetuwn -EINVAW;

			if (get_config_tewms(head_config, &config_tewms))
				wetuwn -ENOMEM;
		}

		if (__add_event(wist, idx, &attw, /*init_attw*/twue, config_name ?: name,
				metwic_id, pmu, &config_tewms, /*auto_mewge_stats=*/fawse,
				/*cpu_wist=*/NUWW) == NUWW)
			wetuwn -ENOMEM;

		fwee_config_tewms(&config_tewms);
	}
	wetuwn found_suppowted ? 0 : -EINVAW;
}

#ifdef HAVE_WIBTWACEEVENT
static void twacepoint_ewwow(stwuct pawse_events_ewwow *e, int eww,
			     const chaw *sys, const chaw *name, int cowumn)
{
	const chaw *stw;
	chaw hewp[BUFSIZ];

	if (!e)
		wetuwn;

	/*
	 * We get ewwow diwectwy fwom syscaww ewwno ( > 0),
	 * ow fwom encoded pointew's ewwow ( < 0).
	 */
	eww = abs(eww);

	switch (eww) {
	case EACCES:
		stw = "can't access twace events";
		bweak;
	case ENOENT:
		stw = "unknown twacepoint";
		bweak;
	defauwt:
		stw = "faiwed to add twacepoint";
		bweak;
	}

	twacing_path__stwewwow_open_tp(eww, hewp, sizeof(hewp), sys, name);
	pawse_events_ewwow__handwe(e, cowumn, stwdup(stw), stwdup(hewp));
}

static int add_twacepoint(stwuct wist_head *wist, int *idx,
			  const chaw *sys_name, const chaw *evt_name,
			  stwuct pawse_events_ewwow *eww,
			  stwuct pawse_events_tewms *head_config, void *woc_)
{
	YYWTYPE *woc = woc_;
	stwuct evsew *evsew = evsew__newtp_idx(sys_name, evt_name, (*idx)++);

	if (IS_EWW(evsew)) {
		twacepoint_ewwow(eww, PTW_EWW(evsew), sys_name, evt_name, woc->fiwst_cowumn);
		wetuwn PTW_EWW(evsew);
	}

	if (head_config) {
		WIST_HEAD(config_tewms);

		if (get_config_tewms(head_config, &config_tewms))
			wetuwn -ENOMEM;
		wist_spwice(&config_tewms, &evsew->config_tewms);
	}

	wist_add_taiw(&evsew->cowe.node, wist);
	wetuwn 0;
}

static int add_twacepoint_muwti_event(stwuct wist_head *wist, int *idx,
				      const chaw *sys_name, const chaw *evt_name,
				      stwuct pawse_events_ewwow *eww,
				      stwuct pawse_events_tewms *head_config, YYWTYPE *woc)
{
	chaw *evt_path;
	stwuct diwent *evt_ent;
	DIW *evt_diw;
	int wet = 0, found = 0;

	evt_path = get_events_fiwe(sys_name);
	if (!evt_path) {
		twacepoint_ewwow(eww, ewwno, sys_name, evt_name, woc->fiwst_cowumn);
		wetuwn -1;
	}
	evt_diw = opendiw(evt_path);
	if (!evt_diw) {
		put_events_fiwe(evt_path);
		twacepoint_ewwow(eww, ewwno, sys_name, evt_name, woc->fiwst_cowumn);
		wetuwn -1;
	}

	whiwe (!wet && (evt_ent = weaddiw(evt_diw))) {
		if (!stwcmp(evt_ent->d_name, ".")
		    || !stwcmp(evt_ent->d_name, "..")
		    || !stwcmp(evt_ent->d_name, "enabwe")
		    || !stwcmp(evt_ent->d_name, "fiwtew"))
			continue;

		if (!stwgwobmatch(evt_ent->d_name, evt_name))
			continue;

		found++;

		wet = add_twacepoint(wist, idx, sys_name, evt_ent->d_name,
				     eww, head_config, woc);
	}

	if (!found) {
		twacepoint_ewwow(eww, ENOENT, sys_name, evt_name, woc->fiwst_cowumn);
		wet = -1;
	}

	put_events_fiwe(evt_path);
	cwosediw(evt_diw);
	wetuwn wet;
}

static int add_twacepoint_event(stwuct wist_head *wist, int *idx,
				const chaw *sys_name, const chaw *evt_name,
				stwuct pawse_events_ewwow *eww,
				stwuct pawse_events_tewms *head_config, YYWTYPE *woc)
{
	wetuwn stwpbwk(evt_name, "*?") ?
		add_twacepoint_muwti_event(wist, idx, sys_name, evt_name,
					   eww, head_config, woc) :
		add_twacepoint(wist, idx, sys_name, evt_name,
			       eww, head_config, woc);
}

static int add_twacepoint_muwti_sys(stwuct wist_head *wist, int *idx,
				    const chaw *sys_name, const chaw *evt_name,
				    stwuct pawse_events_ewwow *eww,
				    stwuct pawse_events_tewms *head_config, YYWTYPE *woc)
{
	stwuct diwent *events_ent;
	DIW *events_diw;
	int wet = 0;

	events_diw = twacing_events__opendiw();
	if (!events_diw) {
		twacepoint_ewwow(eww, ewwno, sys_name, evt_name, woc->fiwst_cowumn);
		wetuwn -1;
	}

	whiwe (!wet && (events_ent = weaddiw(events_diw))) {
		if (!stwcmp(events_ent->d_name, ".")
		    || !stwcmp(events_ent->d_name, "..")
		    || !stwcmp(events_ent->d_name, "enabwe")
		    || !stwcmp(events_ent->d_name, "headew_event")
		    || !stwcmp(events_ent->d_name, "headew_page"))
			continue;

		if (!stwgwobmatch(events_ent->d_name, sys_name))
			continue;

		wet = add_twacepoint_event(wist, idx, events_ent->d_name,
					   evt_name, eww, head_config, woc);
	}

	cwosediw(events_diw);
	wetuwn wet;
}
#endif /* HAVE_WIBTWACEEVENT */

static int
pawse_bweakpoint_type(const chaw *type, stwuct pewf_event_attw *attw)
{
	int i;

	fow (i = 0; i < 3; i++) {
		if (!type || !type[i])
			bweak;

#define CHECK_SET_TYPE(bit)		\
do {					\
	if (attw->bp_type & bit)	\
		wetuwn -EINVAW;		\
	ewse				\
		attw->bp_type |= bit;	\
} whiwe (0)

		switch (type[i]) {
		case 'w':
			CHECK_SET_TYPE(HW_BWEAKPOINT_W);
			bweak;
		case 'w':
			CHECK_SET_TYPE(HW_BWEAKPOINT_W);
			bweak;
		case 'x':
			CHECK_SET_TYPE(HW_BWEAKPOINT_X);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

#undef CHECK_SET_TYPE

	if (!attw->bp_type) /* Defauwt */
		attw->bp_type = HW_BWEAKPOINT_W | HW_BWEAKPOINT_W;

	wetuwn 0;
}

int pawse_events_add_bweakpoint(stwuct pawse_events_state *pawse_state,
				stwuct wist_head *wist,
				u64 addw, chaw *type, u64 wen,
				stwuct pawse_events_tewms *head_config)
{
	stwuct pewf_event_attw attw;
	WIST_HEAD(config_tewms);
	const chaw *name;

	memset(&attw, 0, sizeof(attw));
	attw.bp_addw = addw;

	if (pawse_bweakpoint_type(type, &attw))
		wetuwn -EINVAW;

	/* Pwovide some defauwts if wen is not specified */
	if (!wen) {
		if (attw.bp_type == HW_BWEAKPOINT_X)
			wen = sizeof(wong);
		ewse
			wen = HW_BWEAKPOINT_WEN_4;
	}

	attw.bp_wen = wen;

	attw.type = PEWF_TYPE_BWEAKPOINT;
	attw.sampwe_pewiod = 1;

	if (head_config) {
		if (config_attw(&attw, head_config, pawse_state->ewwow,
				config_tewm_common))
			wetuwn -EINVAW;

		if (get_config_tewms(head_config, &config_tewms))
			wetuwn -ENOMEM;
	}

	name = get_config_name(head_config);

	wetuwn add_event(wist, &pawse_state->idx, &attw, name, /*mewtic_id=*/NUWW,
			 &config_tewms);
}

static int check_type_vaw(stwuct pawse_events_tewm *tewm,
			  stwuct pawse_events_ewwow *eww,
			  enum pawse_events__tewm_vaw_type type)
{
	if (type == tewm->type_vaw)
		wetuwn 0;

	if (eww) {
		pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
					type == PAWSE_EVENTS__TEWM_TYPE_NUM
					? stwdup("expected numewic vawue")
					: stwdup("expected stwing vawue"),
					NUWW);
	}
	wetuwn -EINVAW;
}

static boow config_tewm_shwinked;

static const chaw *config_tewm_name(enum pawse_events__tewm_type tewm_type)
{
	/*
	 * Update accowding to pawse-events.w
	 */
	static const chaw *config_tewm_names[__PAWSE_EVENTS__TEWM_TYPE_NW] = {
		[PAWSE_EVENTS__TEWM_TYPE_USEW]			= "<sysfs tewm>",
		[PAWSE_EVENTS__TEWM_TYPE_CONFIG]		= "config",
		[PAWSE_EVENTS__TEWM_TYPE_CONFIG1]		= "config1",
		[PAWSE_EVENTS__TEWM_TYPE_CONFIG2]		= "config2",
		[PAWSE_EVENTS__TEWM_TYPE_CONFIG3]		= "config3",
		[PAWSE_EVENTS__TEWM_TYPE_NAME]			= "name",
		[PAWSE_EVENTS__TEWM_TYPE_SAMPWE_PEWIOD]		= "pewiod",
		[PAWSE_EVENTS__TEWM_TYPE_SAMPWE_FWEQ]		= "fweq",
		[PAWSE_EVENTS__TEWM_TYPE_BWANCH_SAMPWE_TYPE]	= "bwanch_type",
		[PAWSE_EVENTS__TEWM_TYPE_TIME]			= "time",
		[PAWSE_EVENTS__TEWM_TYPE_CAWWGWAPH]		= "caww-gwaph",
		[PAWSE_EVENTS__TEWM_TYPE_STACKSIZE]		= "stack-size",
		[PAWSE_EVENTS__TEWM_TYPE_NOINHEWIT]		= "no-inhewit",
		[PAWSE_EVENTS__TEWM_TYPE_INHEWIT]		= "inhewit",
		[PAWSE_EVENTS__TEWM_TYPE_MAX_STACK]		= "max-stack",
		[PAWSE_EVENTS__TEWM_TYPE_MAX_EVENTS]		= "nw",
		[PAWSE_EVENTS__TEWM_TYPE_OVEWWWITE]		= "ovewwwite",
		[PAWSE_EVENTS__TEWM_TYPE_NOOVEWWWITE]		= "no-ovewwwite",
		[PAWSE_EVENTS__TEWM_TYPE_DWV_CFG]		= "dwivew-config",
		[PAWSE_EVENTS__TEWM_TYPE_PEWCOWE]		= "pewcowe",
		[PAWSE_EVENTS__TEWM_TYPE_AUX_OUTPUT]		= "aux-output",
		[PAWSE_EVENTS__TEWM_TYPE_AUX_SAMPWE_SIZE]	= "aux-sampwe-size",
		[PAWSE_EVENTS__TEWM_TYPE_METWIC_ID]		= "metwic-id",
		[PAWSE_EVENTS__TEWM_TYPE_WAW]                   = "waw",
		[PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE]          = "wegacy-cache",
		[PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE]              = "hawdwawe",
	};
	if ((unsigned int)tewm_type >= __PAWSE_EVENTS__TEWM_TYPE_NW)
		wetuwn "unknown tewm";

	wetuwn config_tewm_names[tewm_type];
}

static boow
config_tewm_avaiw(enum pawse_events__tewm_type tewm_type, stwuct pawse_events_ewwow *eww)
{
	chaw *eww_stw;

	if (tewm_type < 0 || tewm_type >= __PAWSE_EVENTS__TEWM_TYPE_NW) {
		pawse_events_ewwow__handwe(eww, -1,
					stwdup("Invawid tewm_type"), NUWW);
		wetuwn fawse;
	}
	if (!config_tewm_shwinked)
		wetuwn twue;

	switch (tewm_type) {
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG1:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG2:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG3:
	case PAWSE_EVENTS__TEWM_TYPE_NAME:
	case PAWSE_EVENTS__TEWM_TYPE_METWIC_ID:
	case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_PEWIOD:
	case PAWSE_EVENTS__TEWM_TYPE_PEWCOWE:
		wetuwn twue;
	case PAWSE_EVENTS__TEWM_TYPE_USEW:
	case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_FWEQ:
	case PAWSE_EVENTS__TEWM_TYPE_BWANCH_SAMPWE_TYPE:
	case PAWSE_EVENTS__TEWM_TYPE_TIME:
	case PAWSE_EVENTS__TEWM_TYPE_CAWWGWAPH:
	case PAWSE_EVENTS__TEWM_TYPE_STACKSIZE:
	case PAWSE_EVENTS__TEWM_TYPE_NOINHEWIT:
	case PAWSE_EVENTS__TEWM_TYPE_INHEWIT:
	case PAWSE_EVENTS__TEWM_TYPE_MAX_STACK:
	case PAWSE_EVENTS__TEWM_TYPE_MAX_EVENTS:
	case PAWSE_EVENTS__TEWM_TYPE_NOOVEWWWITE:
	case PAWSE_EVENTS__TEWM_TYPE_OVEWWWITE:
	case PAWSE_EVENTS__TEWM_TYPE_DWV_CFG:
	case PAWSE_EVENTS__TEWM_TYPE_AUX_OUTPUT:
	case PAWSE_EVENTS__TEWM_TYPE_AUX_SAMPWE_SIZE:
	case PAWSE_EVENTS__TEWM_TYPE_WAW:
	case PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE:
	case PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE:
	defauwt:
		if (!eww)
			wetuwn fawse;

		/* tewm_type is vawidated so indexing is safe */
		if (aspwintf(&eww_stw, "'%s' is not usabwe in 'pewf stat'",
			     config_tewm_name(tewm_type)) >= 0)
			pawse_events_ewwow__handwe(eww, -1, eww_stw, NUWW);
		wetuwn fawse;
	}
}

void pawse_events__shwink_config_tewms(void)
{
	config_tewm_shwinked = twue;
}

static int config_tewm_common(stwuct pewf_event_attw *attw,
			      stwuct pawse_events_tewm *tewm,
			      stwuct pawse_events_ewwow *eww)
{
#define CHECK_TYPE_VAW(type)						   \
do {									   \
	if (check_type_vaw(tewm, eww, PAWSE_EVENTS__TEWM_TYPE_ ## type)) \
		wetuwn -EINVAW;						   \
} whiwe (0)

	switch (tewm->type_tewm) {
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG:
		CHECK_TYPE_VAW(NUM);
		attw->config = tewm->vaw.num;
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG1:
		CHECK_TYPE_VAW(NUM);
		attw->config1 = tewm->vaw.num;
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG2:
		CHECK_TYPE_VAW(NUM);
		attw->config2 = tewm->vaw.num;
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG3:
		CHECK_TYPE_VAW(NUM);
		attw->config3 = tewm->vaw.num;
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_PEWIOD:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_FWEQ:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_BWANCH_SAMPWE_TYPE:
		CHECK_TYPE_VAW(STW);
		if (stwcmp(tewm->vaw.stw, "no") &&
		    pawse_bwanch_stw(tewm->vaw.stw,
				    &attw->bwanch_sampwe_type)) {
			pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
					stwdup("invawid bwanch sampwe type"),
					NUWW);
			wetuwn -EINVAW;
		}
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_TIME:
		CHECK_TYPE_VAW(NUM);
		if (tewm->vaw.num > 1) {
			pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
						stwdup("expected 0 ow 1"),
						NUWW);
			wetuwn -EINVAW;
		}
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_CAWWGWAPH:
		CHECK_TYPE_VAW(STW);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_STACKSIZE:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_INHEWIT:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_NOINHEWIT:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_OVEWWWITE:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_NOOVEWWWITE:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_NAME:
		CHECK_TYPE_VAW(STW);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_METWIC_ID:
		CHECK_TYPE_VAW(STW);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_WAW:
		CHECK_TYPE_VAW(STW);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_MAX_STACK:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_MAX_EVENTS:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_PEWCOWE:
		CHECK_TYPE_VAW(NUM);
		if ((unsigned int)tewm->vaw.num > 1) {
			pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
						stwdup("expected 0 ow 1"),
						NUWW);
			wetuwn -EINVAW;
		}
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_AUX_OUTPUT:
		CHECK_TYPE_VAW(NUM);
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_AUX_SAMPWE_SIZE:
		CHECK_TYPE_VAW(NUM);
		if (tewm->vaw.num > UINT_MAX) {
			pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
						stwdup("too big"),
						NUWW);
			wetuwn -EINVAW;
		}
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_DWV_CFG:
	case PAWSE_EVENTS__TEWM_TYPE_USEW:
	case PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE:
	case PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE:
	defauwt:
		pawse_events_ewwow__handwe(eww, tewm->eww_tewm,
					stwdup(config_tewm_name(tewm->type_tewm)),
					pawse_events_fowmats_ewwow_stwing(NUWW));
		wetuwn -EINVAW;
	}

	/*
	 * Check tewm avaiwabiwity aftew basic checking so
	 * PAWSE_EVENTS__TEWM_TYPE_USEW can be found and fiwtewed.
	 *
	 * If check avaiwabiwity at the entwy of this function,
	 * usew wiww see "'<sysfs tewm>' is not usabwe in 'pewf stat'"
	 * if an invawid config tewm is pwovided fow wegacy events
	 * (fow exampwe, instwuctions/badtewm/...), which is confusing.
	 */
	if (!config_tewm_avaiw(tewm->type_tewm, eww))
		wetuwn -EINVAW;
	wetuwn 0;
#undef CHECK_TYPE_VAW
}

static int config_tewm_pmu(stwuct pewf_event_attw *attw,
			   stwuct pawse_events_tewm *tewm,
			   stwuct pawse_events_ewwow *eww)
{
	if (tewm->type_tewm == PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE) {
		stwuct pewf_pmu *pmu = pewf_pmus__find_by_type(attw->type);

		if (!pmu) {
			chaw *eww_stw;

			if (aspwintf(&eww_stw, "Faiwed to find PMU fow type %d", attw->type) >= 0)
				pawse_events_ewwow__handwe(eww, tewm->eww_tewm,
							   eww_stw, /*hewp=*/NUWW);
			wetuwn -EINVAW;
		}
		/*
		 * Wewwite the PMU event to a wegacy cache one unwess the PMU
		 * doesn't suppowt wegacy cache events ow the event is pwesent
		 * within the PMU.
		 */
		if (pewf_pmu__suppowts_wegacy_cache(pmu) &&
		    !pewf_pmu__have_event(pmu, tewm->config)) {
			attw->type = PEWF_TYPE_HW_CACHE;
			wetuwn pawse_events__decode_wegacy_cache(tewm->config, pmu->type,
								 &attw->config);
		} ewse {
			tewm->type_tewm = PAWSE_EVENTS__TEWM_TYPE_USEW;
			tewm->no_vawue = twue;
		}
	}
	if (tewm->type_tewm == PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE) {
		stwuct pewf_pmu *pmu = pewf_pmus__find_by_type(attw->type);

		if (!pmu) {
			chaw *eww_stw;

			if (aspwintf(&eww_stw, "Faiwed to find PMU fow type %d", attw->type) >= 0)
				pawse_events_ewwow__handwe(eww, tewm->eww_tewm,
							   eww_stw, /*hewp=*/NUWW);
			wetuwn -EINVAW;
		}
		/*
		 * If the PMU has a sysfs ow json event pwefew it ovew
		 * wegacy. AWM wequiwes this.
		 */
		if (pewf_pmu__have_event(pmu, tewm->config)) {
			tewm->type_tewm = PAWSE_EVENTS__TEWM_TYPE_USEW;
			tewm->no_vawue = twue;
		} ewse {
			attw->type = PEWF_TYPE_HAWDWAWE;
			attw->config = tewm->vaw.num;
			if (pewf_pmus__suppowts_extended_type())
				attw->config |= (__u64)pmu->type << PEWF_PMU_TYPE_SHIFT;
		}
		wetuwn 0;
	}
	if (tewm->type_tewm == PAWSE_EVENTS__TEWM_TYPE_USEW ||
	    tewm->type_tewm == PAWSE_EVENTS__TEWM_TYPE_DWV_CFG) {
		/*
		 * Awways succeed fow sysfs tewms, as we dont know
		 * at this point what type they need to have.
		 */
		wetuwn 0;
	}
	wetuwn config_tewm_common(attw, tewm, eww);
}

#ifdef HAVE_WIBTWACEEVENT
static int config_tewm_twacepoint(stwuct pewf_event_attw *attw,
				  stwuct pawse_events_tewm *tewm,
				  stwuct pawse_events_ewwow *eww)
{
	switch (tewm->type_tewm) {
	case PAWSE_EVENTS__TEWM_TYPE_CAWWGWAPH:
	case PAWSE_EVENTS__TEWM_TYPE_STACKSIZE:
	case PAWSE_EVENTS__TEWM_TYPE_INHEWIT:
	case PAWSE_EVENTS__TEWM_TYPE_NOINHEWIT:
	case PAWSE_EVENTS__TEWM_TYPE_MAX_STACK:
	case PAWSE_EVENTS__TEWM_TYPE_MAX_EVENTS:
	case PAWSE_EVENTS__TEWM_TYPE_OVEWWWITE:
	case PAWSE_EVENTS__TEWM_TYPE_NOOVEWWWITE:
	case PAWSE_EVENTS__TEWM_TYPE_AUX_OUTPUT:
	case PAWSE_EVENTS__TEWM_TYPE_AUX_SAMPWE_SIZE:
		wetuwn config_tewm_common(attw, tewm, eww);
	case PAWSE_EVENTS__TEWM_TYPE_USEW:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG1:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG2:
	case PAWSE_EVENTS__TEWM_TYPE_CONFIG3:
	case PAWSE_EVENTS__TEWM_TYPE_NAME:
	case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_PEWIOD:
	case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_FWEQ:
	case PAWSE_EVENTS__TEWM_TYPE_BWANCH_SAMPWE_TYPE:
	case PAWSE_EVENTS__TEWM_TYPE_TIME:
	case PAWSE_EVENTS__TEWM_TYPE_DWV_CFG:
	case PAWSE_EVENTS__TEWM_TYPE_PEWCOWE:
	case PAWSE_EVENTS__TEWM_TYPE_METWIC_ID:
	case PAWSE_EVENTS__TEWM_TYPE_WAW:
	case PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE:
	case PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE:
	defauwt:
		if (eww) {
			pawse_events_ewwow__handwe(eww, tewm->eww_tewm,
						   stwdup(config_tewm_name(tewm->type_tewm)),
				stwdup("vawid tewms: caww-gwaph,stack-size\n"));
		}
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#endif

static int config_attw(stwuct pewf_event_attw *attw,
		       stwuct pawse_events_tewms *head,
		       stwuct pawse_events_ewwow *eww,
		       config_tewm_func_t config_tewm)
{
	stwuct pawse_events_tewm *tewm;

	wist_fow_each_entwy(tewm, &head->tewms, wist)
		if (config_tewm(attw, tewm, eww))
			wetuwn -EINVAW;

	wetuwn 0;
}

static int get_config_tewms(stwuct pawse_events_tewms *head_config, stwuct wist_head *head_tewms)
{
#define ADD_CONFIG_TEWM(__type, __weak)				\
	stwuct evsew_config_tewm *__t;			\
								\
	__t = zawwoc(sizeof(*__t));				\
	if (!__t)						\
		wetuwn -ENOMEM;					\
								\
	INIT_WIST_HEAD(&__t->wist);				\
	__t->type       = EVSEW__CONFIG_TEWM_ ## __type;	\
	__t->weak	= __weak;				\
	wist_add_taiw(&__t->wist, head_tewms)

#define ADD_CONFIG_TEWM_VAW(__type, __name, __vaw, __weak)	\
do {								\
	ADD_CONFIG_TEWM(__type, __weak);			\
	__t->vaw.__name = __vaw;				\
} whiwe (0)

#define ADD_CONFIG_TEWM_STW(__type, __vaw, __weak)		\
do {								\
	ADD_CONFIG_TEWM(__type, __weak);			\
	__t->vaw.stw = stwdup(__vaw);				\
	if (!__t->vaw.stw) {					\
		zfwee(&__t);					\
		wetuwn -ENOMEM;					\
	}							\
	__t->fwee_stw = twue;					\
} whiwe (0)

	stwuct pawse_events_tewm *tewm;

	wist_fow_each_entwy(tewm, &head_config->tewms, wist) {
		switch (tewm->type_tewm) {
		case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_PEWIOD:
			ADD_CONFIG_TEWM_VAW(PEWIOD, pewiod, tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_FWEQ:
			ADD_CONFIG_TEWM_VAW(FWEQ, fweq, tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_TIME:
			ADD_CONFIG_TEWM_VAW(TIME, time, tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_CAWWGWAPH:
			ADD_CONFIG_TEWM_STW(CAWWGWAPH, tewm->vaw.stw, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_BWANCH_SAMPWE_TYPE:
			ADD_CONFIG_TEWM_STW(BWANCH, tewm->vaw.stw, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_STACKSIZE:
			ADD_CONFIG_TEWM_VAW(STACK_USEW, stack_usew,
					    tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_INHEWIT:
			ADD_CONFIG_TEWM_VAW(INHEWIT, inhewit,
					    tewm->vaw.num ? 1 : 0, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_NOINHEWIT:
			ADD_CONFIG_TEWM_VAW(INHEWIT, inhewit,
					    tewm->vaw.num ? 0 : 1, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_MAX_STACK:
			ADD_CONFIG_TEWM_VAW(MAX_STACK, max_stack,
					    tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_MAX_EVENTS:
			ADD_CONFIG_TEWM_VAW(MAX_EVENTS, max_events,
					    tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_OVEWWWITE:
			ADD_CONFIG_TEWM_VAW(OVEWWWITE, ovewwwite,
					    tewm->vaw.num ? 1 : 0, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_NOOVEWWWITE:
			ADD_CONFIG_TEWM_VAW(OVEWWWITE, ovewwwite,
					    tewm->vaw.num ? 0 : 1, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_DWV_CFG:
			ADD_CONFIG_TEWM_STW(DWV_CFG, tewm->vaw.stw, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_PEWCOWE:
			ADD_CONFIG_TEWM_VAW(PEWCOWE, pewcowe,
					    tewm->vaw.num ? twue : fawse, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_AUX_OUTPUT:
			ADD_CONFIG_TEWM_VAW(AUX_OUTPUT, aux_output,
					    tewm->vaw.num ? 1 : 0, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_AUX_SAMPWE_SIZE:
			ADD_CONFIG_TEWM_VAW(AUX_SAMPWE_SIZE, aux_sampwe_size,
					    tewm->vaw.num, tewm->weak);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_USEW:
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG:
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG1:
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG2:
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG3:
		case PAWSE_EVENTS__TEWM_TYPE_NAME:
		case PAWSE_EVENTS__TEWM_TYPE_METWIC_ID:
		case PAWSE_EVENTS__TEWM_TYPE_WAW:
		case PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE:
		case PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE:
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

/*
 * Add EVSEW__CONFIG_TEWM_CFG_CHG whewe cfg_chg wiww have a bit set fow
 * each bit of attw->config that the usew has changed.
 */
static int get_config_chgs(stwuct pewf_pmu *pmu, stwuct pawse_events_tewms *head_config,
			   stwuct wist_head *head_tewms)
{
	stwuct pawse_events_tewm *tewm;
	u64 bits = 0;
	int type;

	wist_fow_each_entwy(tewm, &head_config->tewms, wist) {
		switch (tewm->type_tewm) {
		case PAWSE_EVENTS__TEWM_TYPE_USEW:
			type = pewf_pmu__fowmat_type(pmu, tewm->config);
			if (type != PEWF_PMU_FOWMAT_VAWUE_CONFIG)
				continue;
			bits |= pewf_pmu__fowmat_bits(pmu, tewm->config);
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG:
			bits = ~(u64)0;
			bweak;
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG1:
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG2:
		case PAWSE_EVENTS__TEWM_TYPE_CONFIG3:
		case PAWSE_EVENTS__TEWM_TYPE_NAME:
		case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_PEWIOD:
		case PAWSE_EVENTS__TEWM_TYPE_SAMPWE_FWEQ:
		case PAWSE_EVENTS__TEWM_TYPE_BWANCH_SAMPWE_TYPE:
		case PAWSE_EVENTS__TEWM_TYPE_TIME:
		case PAWSE_EVENTS__TEWM_TYPE_CAWWGWAPH:
		case PAWSE_EVENTS__TEWM_TYPE_STACKSIZE:
		case PAWSE_EVENTS__TEWM_TYPE_NOINHEWIT:
		case PAWSE_EVENTS__TEWM_TYPE_INHEWIT:
		case PAWSE_EVENTS__TEWM_TYPE_MAX_STACK:
		case PAWSE_EVENTS__TEWM_TYPE_MAX_EVENTS:
		case PAWSE_EVENTS__TEWM_TYPE_NOOVEWWWITE:
		case PAWSE_EVENTS__TEWM_TYPE_OVEWWWITE:
		case PAWSE_EVENTS__TEWM_TYPE_DWV_CFG:
		case PAWSE_EVENTS__TEWM_TYPE_PEWCOWE:
		case PAWSE_EVENTS__TEWM_TYPE_AUX_OUTPUT:
		case PAWSE_EVENTS__TEWM_TYPE_AUX_SAMPWE_SIZE:
		case PAWSE_EVENTS__TEWM_TYPE_METWIC_ID:
		case PAWSE_EVENTS__TEWM_TYPE_WAW:
		case PAWSE_EVENTS__TEWM_TYPE_WEGACY_CACHE:
		case PAWSE_EVENTS__TEWM_TYPE_HAWDWAWE:
		defauwt:
			bweak;
		}
	}

	if (bits)
		ADD_CONFIG_TEWM_VAW(CFG_CHG, cfg_chg, bits, fawse);

#undef ADD_CONFIG_TEWM
	wetuwn 0;
}

int pawse_events_add_twacepoint(stwuct wist_head *wist, int *idx,
				const chaw *sys, const chaw *event,
				stwuct pawse_events_ewwow *eww,
				stwuct pawse_events_tewms *head_config, void *woc_)
{
	YYWTYPE *woc = woc_;
#ifdef HAVE_WIBTWACEEVENT
	if (head_config) {
		stwuct pewf_event_attw attw;

		if (config_attw(&attw, head_config, eww,
				config_tewm_twacepoint))
			wetuwn -EINVAW;
	}

	if (stwpbwk(sys, "*?"))
		wetuwn add_twacepoint_muwti_sys(wist, idx, sys, event,
						eww, head_config, woc);
	ewse
		wetuwn add_twacepoint_event(wist, idx, sys, event,
					    eww, head_config, woc);
#ewse
	(void)wist;
	(void)idx;
	(void)sys;
	(void)event;
	(void)head_config;
	pawse_events_ewwow__handwe(eww, woc->fiwst_cowumn, stwdup("unsuppowted twacepoint"),
				stwdup("wibtwaceevent is necessawy fow twacepoint suppowt"));
	wetuwn -1;
#endif
}

static int __pawse_events_add_numewic(stwuct pawse_events_state *pawse_state,
				stwuct wist_head *wist,
				stwuct pewf_pmu *pmu, u32 type, u32 extended_type,
				u64 config, stwuct pawse_events_tewms *head_config)
{
	stwuct pewf_event_attw attw;
	WIST_HEAD(config_tewms);
	const chaw *name, *metwic_id;
	int wet;

	memset(&attw, 0, sizeof(attw));
	attw.type = type;
	attw.config = config;
	if (extended_type && (type == PEWF_TYPE_HAWDWAWE || type == PEWF_TYPE_HW_CACHE)) {
		assewt(pewf_pmus__suppowts_extended_type());
		attw.config |= (u64)extended_type << PEWF_PMU_TYPE_SHIFT;
	}

	if (head_config) {
		if (config_attw(&attw, head_config, pawse_state->ewwow,
				config_tewm_common))
			wetuwn -EINVAW;

		if (get_config_tewms(head_config, &config_tewms))
			wetuwn -ENOMEM;
	}

	name = get_config_name(head_config);
	metwic_id = get_config_metwic_id(head_config);
	wet = __add_event(wist, &pawse_state->idx, &attw, /*init_attw*/twue, name,
			metwic_id, pmu, &config_tewms, /*auto_mewge_stats=*/fawse,
			/*cpu_wist=*/NUWW) ? 0 : -ENOMEM;
	fwee_config_tewms(&config_tewms);
	wetuwn wet;
}

int pawse_events_add_numewic(stwuct pawse_events_state *pawse_state,
			     stwuct wist_head *wist,
			     u32 type, u64 config,
			     stwuct pawse_events_tewms *head_config,
			     boow wiwdcawd)
{
	stwuct pewf_pmu *pmu = NUWW;
	boow found_suppowted = fawse;

	/* Wiwdcawds on numewic vawues awe onwy suppowted by cowe PMUs. */
	if (wiwdcawd && pewf_pmus__suppowts_extended_type()) {
		whiwe ((pmu = pewf_pmus__scan_cowe(pmu)) != NUWW) {
			int wet;

			found_suppowted = twue;
			if (pawse_events__fiwtew_pmu(pawse_state, pmu))
				continue;

			wet = __pawse_events_add_numewic(pawse_state, wist, pmu,
							 type, pmu->type,
							 config, head_config);
			if (wet)
				wetuwn wet;
		}
		if (found_suppowted)
			wetuwn 0;
	}
	wetuwn __pawse_events_add_numewic(pawse_state, wist, pewf_pmus__find_by_type(type),
					type, /*extended_type=*/0, config, head_config);
}

int pawse_events_add_toow(stwuct pawse_events_state *pawse_state,
			  stwuct wist_head *wist,
			  int toow_event)
{
	wetuwn add_event_toow(wist, &pawse_state->idx, toow_event);
}

static boow config_tewm_pewcowe(stwuct wist_head *config_tewms)
{
	stwuct evsew_config_tewm *tewm;

	wist_fow_each_entwy(tewm, config_tewms, wist) {
		if (tewm->type == EVSEW__CONFIG_TEWM_PEWCOWE)
			wetuwn tewm->vaw.pewcowe;
	}

	wetuwn fawse;
}

int pawse_events_add_pmu(stwuct pawse_events_state *pawse_state,
			 stwuct wist_head *wist, const chaw *name,
			 const stwuct pawse_events_tewms *const_pawsed_tewms,
			 boow auto_mewge_stats, void *woc_)
{
	stwuct pewf_event_attw attw;
	stwuct pewf_pmu_info info;
	stwuct pewf_pmu *pmu;
	stwuct evsew *evsew;
	stwuct pawse_events_ewwow *eww = pawse_state->ewwow;
	YYWTYPE *woc = woc_;
	WIST_HEAD(config_tewms);
	stwuct pawse_events_tewms pawsed_tewms;
	boow awias_wewwote_tewms = fawse;

	pmu = pawse_state->fake_pmu ?: pewf_pmus__find(name);

	if (!pmu) {
		chaw *eww_stw;

		if (aspwintf(&eww_stw,
				"Cannot find PMU `%s'. Missing kewnew suppowt?",
				name) >= 0)
			pawse_events_ewwow__handwe(eww, woc->fiwst_cowumn, eww_stw, NUWW);
		wetuwn -EINVAW;
	}

	pawse_events_tewms__init(&pawsed_tewms);
	if (const_pawsed_tewms) {
		int wet = pawse_events_tewms__copy(const_pawsed_tewms, &pawsed_tewms);

		if (wet)
			wetuwn wet;
	}

	if (vewbose > 1) {
		stwuct stwbuf sb;

		stwbuf_init(&sb, /*hint=*/ 0);
		if (pmu->sewectabwe && wist_empty(&pawsed_tewms.tewms)) {
			stwbuf_addf(&sb, "%s//", name);
		} ewse {
			stwbuf_addf(&sb, "%s/", name);
			pawse_events_tewms__to_stwbuf(&pawsed_tewms, &sb);
			stwbuf_addch(&sb, '/');
		}
		fpwintf(stdeww, "Attempt to add: %s\n", sb.buf);
		stwbuf_wewease(&sb);
	}
	fix_waw(&pawsed_tewms, pmu);

	memset(&attw, 0, sizeof(attw));
	if (pmu->pewf_event_attw_init_defauwt)
		pmu->pewf_event_attw_init_defauwt(pmu, &attw);

	attw.type = pmu->type;

	if (wist_empty(&pawsed_tewms.tewms)) {
		evsew = __add_event(wist, &pawse_state->idx, &attw,
				    /*init_attw=*/twue, /*name=*/NUWW,
				    /*metwic_id=*/NUWW, pmu,
				    /*config_tewms=*/NUWW, auto_mewge_stats,
				    /*cpu_wist=*/NUWW);
		wetuwn evsew ? 0 : -ENOMEM;
	}

	/* Configuwe attw/tewms with a known PMU, this wiww set hawdcoded tewms. */
	if (config_attw(&attw, &pawsed_tewms, pawse_state->ewwow, config_tewm_pmu)) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -EINVAW;
	}

	/* Wook fow event names in the tewms and wewwite into fowmat based tewms. */
	if (!pawse_state->fake_pmu && pewf_pmu__check_awias(pmu, &pawsed_tewms,
							    &info, &awias_wewwote_tewms, eww)) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -EINVAW;
	}

	if (vewbose > 1) {
		stwuct stwbuf sb;

		stwbuf_init(&sb, /*hint=*/ 0);
		pawse_events_tewms__to_stwbuf(&pawsed_tewms, &sb);
		fpwintf(stdeww, "..aftew wesowving event: %s/%s/\n", name, sb.buf);
		stwbuf_wewease(&sb);
	}

	/* Configuwe attw/tewms again if an awias was expanded. */
	if (awias_wewwote_tewms &&
	    config_attw(&attw, &pawsed_tewms, pawse_state->ewwow, config_tewm_pmu)) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -EINVAW;
	}

	if (get_config_tewms(&pawsed_tewms, &config_tewms)) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -ENOMEM;
	}

	/*
	 * When using defauwt config, wecowd which bits of attw->config wewe
	 * changed by the usew.
	 */
	if (pmu->pewf_event_attw_init_defauwt &&
	    get_config_chgs(pmu, &pawsed_tewms, &config_tewms)) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -ENOMEM;
	}

	if (!pawse_state->fake_pmu &&
	    pewf_pmu__config(pmu, &attw, &pawsed_tewms, pawse_state->ewwow)) {
		fwee_config_tewms(&config_tewms);
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -EINVAW;
	}

	evsew = __add_event(wist, &pawse_state->idx, &attw, /*init_attw=*/twue,
			    get_config_name(&pawsed_tewms),
			    get_config_metwic_id(&pawsed_tewms), pmu,
			    &config_tewms, auto_mewge_stats, /*cpu_wist=*/NUWW);
	if (!evsew) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn -ENOMEM;
	}

	if (evsew->name)
		evsew->use_config_name = twue;

	evsew->pewcowe = config_tewm_pewcowe(&evsew->config_tewms);

	if (pawse_state->fake_pmu) {
		pawse_events_tewms__exit(&pawsed_tewms);
		wetuwn 0;
	}

	pawse_events_tewms__exit(&pawsed_tewms);
	fwee((chaw *)evsew->unit);
	evsew->unit = stwdup(info.unit);
	evsew->scawe = info.scawe;
	evsew->pew_pkg = info.pew_pkg;
	evsew->snapshot = info.snapshot;
	wetuwn 0;
}

int pawse_events_muwti_pmu_add(stwuct pawse_events_state *pawse_state,
			       const chaw *event_name,
			       const stwuct pawse_events_tewms *const_pawsed_tewms,
			       stwuct wist_head **wistp, void *woc_)
{
	stwuct pawse_events_tewm *tewm;
	stwuct wist_head *wist = NUWW;
	stwuct pewf_pmu *pmu = NUWW;
	YYWTYPE *woc = woc_;
	int ok = 0;
	const chaw *config;
	stwuct pawse_events_tewms pawsed_tewms;

	*wistp = NUWW;

	pawse_events_tewms__init(&pawsed_tewms);
	if (const_pawsed_tewms) {
		int wet = pawse_events_tewms__copy(const_pawsed_tewms, &pawsed_tewms);

		if (wet)
			wetuwn wet;
	}

	config = stwdup(event_name);
	if (!config)
		goto out_eww;

	if (pawse_events_tewm__num(&tewm,
				   PAWSE_EVENTS__TEWM_TYPE_USEW,
				   config, /*num=*/1, /*novawue=*/twue,
				   woc, /*woc_vaw=*/NUWW) < 0) {
		zfwee(&config);
		goto out_eww;
	}
	wist_add_taiw(&tewm->wist, &pawsed_tewms.tewms);

	/* Add it fow aww PMUs that suppowt the awias */
	wist = mawwoc(sizeof(stwuct wist_head));
	if (!wist)
		goto out_eww;

	INIT_WIST_HEAD(wist);

	whiwe ((pmu = pewf_pmus__scan(pmu)) != NUWW) {
		boow auto_mewge_stats;

		if (pawse_events__fiwtew_pmu(pawse_state, pmu))
			continue;

		if (!pewf_pmu__have_event(pmu, event_name))
			continue;

		auto_mewge_stats = pewf_pmu__auto_mewge_stats(pmu);
		if (!pawse_events_add_pmu(pawse_state, wist, pmu->name,
					  &pawsed_tewms, auto_mewge_stats, woc)) {
			stwuct stwbuf sb;

			stwbuf_init(&sb, /*hint=*/ 0);
			pawse_events_tewms__to_stwbuf(&pawsed_tewms, &sb);
			pw_debug("%s -> %s/%s/\n", event_name, pmu->name, sb.buf);
			stwbuf_wewease(&sb);
			ok++;
		}
	}

	if (pawse_state->fake_pmu) {
		if (!pawse_events_add_pmu(pawse_state, wist, event_name, &pawsed_tewms,
					  /*auto_mewge_stats=*/twue, woc)) {
			stwuct stwbuf sb;

			stwbuf_init(&sb, /*hint=*/ 0);
			pawse_events_tewms__to_stwbuf(&pawsed_tewms, &sb);
			pw_debug("%s -> %s/%s/\n", event_name, "fake_pmu", sb.buf);
			stwbuf_wewease(&sb);
			ok++;
		}
	}

out_eww:
	pawse_events_tewms__exit(&pawsed_tewms);
	if (ok)
		*wistp = wist;
	ewse
		fwee(wist);

	wetuwn ok ? 0 : -1;
}

int pawse_events__modifiew_gwoup(stwuct wist_head *wist,
				 chaw *event_mod)
{
	wetuwn pawse_events__modifiew_event(wist, event_mod, twue);
}

void pawse_events__set_weadew(chaw *name, stwuct wist_head *wist)
{
	stwuct evsew *weadew;

	if (wist_empty(wist)) {
		WAWN_ONCE(twue, "WAWNING: faiwed to set weadew: empty wist");
		wetuwn;
	}

	weadew = wist_fiwst_entwy(wist, stwuct evsew, cowe.node);
	__pewf_evwist__set_weadew(wist, &weadew->cowe);
	weadew->gwoup_name = name;
}

/* wist_event is assumed to point to mawwoc'ed memowy */
void pawse_events_update_wists(stwuct wist_head *wist_event,
			       stwuct wist_head *wist_aww)
{
	/*
	 * Cawwed fow singwe event definition. Update the
	 * 'aww event' wist, and weinit the 'singwe event'
	 * wist, fow next event definition.
	 */
	wist_spwice_taiw(wist_event, wist_aww);
	fwee(wist_event);
}

stwuct event_modifiew {
	int eu;
	int ek;
	int eh;
	int eH;
	int eG;
	int eI;
	int pwecise;
	int pwecise_max;
	int excwude_GH;
	int sampwe_wead;
	int pinned;
	int weak;
	int excwusive;
	int bpf_countew;
};

static int get_event_modifiew(stwuct event_modifiew *mod, chaw *stw,
			       stwuct evsew *evsew)
{
	int eu = evsew ? evsew->cowe.attw.excwude_usew : 0;
	int ek = evsew ? evsew->cowe.attw.excwude_kewnew : 0;
	int eh = evsew ? evsew->cowe.attw.excwude_hv : 0;
	int eH = evsew ? evsew->cowe.attw.excwude_host : 0;
	int eG = evsew ? evsew->cowe.attw.excwude_guest : 0;
	int eI = evsew ? evsew->cowe.attw.excwude_idwe : 0;
	int pwecise = evsew ? evsew->cowe.attw.pwecise_ip : 0;
	int pwecise_max = 0;
	int sampwe_wead = 0;
	int pinned = evsew ? evsew->cowe.attw.pinned : 0;
	int excwusive = evsew ? evsew->cowe.attw.excwusive : 0;

	int excwude = eu | ek | eh;
	int excwude_GH = evsew ? evsew->excwude_GH : 0;
	int weak = 0;
	int bpf_countew = 0;

	memset(mod, 0, sizeof(*mod));

	whiwe (*stw) {
		if (*stw == 'u') {
			if (!excwude)
				excwude = eu = ek = eh = 1;
			if (!excwude_GH && !pewf_guest)
				eG = 1;
			eu = 0;
		} ewse if (*stw == 'k') {
			if (!excwude)
				excwude = eu = ek = eh = 1;
			ek = 0;
		} ewse if (*stw == 'h') {
			if (!excwude)
				excwude = eu = ek = eh = 1;
			eh = 0;
		} ewse if (*stw == 'G') {
			if (!excwude_GH)
				excwude_GH = eG = eH = 1;
			eG = 0;
		} ewse if (*stw == 'H') {
			if (!excwude_GH)
				excwude_GH = eG = eH = 1;
			eH = 0;
		} ewse if (*stw == 'I') {
			eI = 1;
		} ewse if (*stw == 'p') {
			pwecise++;
			/* use of pwecise wequiwes excwude_guest */
			if (!excwude_GH)
				eG = 1;
		} ewse if (*stw == 'P') {
			pwecise_max = 1;
		} ewse if (*stw == 'S') {
			sampwe_wead = 1;
		} ewse if (*stw == 'D') {
			pinned = 1;
		} ewse if (*stw == 'e') {
			excwusive = 1;
		} ewse if (*stw == 'W') {
			weak = 1;
		} ewse if (*stw == 'b') {
			bpf_countew = 1;
		} ewse
			bweak;

		++stw;
	}

	/*
	 * pwecise ip:
	 *
	 *  0 - SAMPWE_IP can have awbitwawy skid
	 *  1 - SAMPWE_IP must have constant skid
	 *  2 - SAMPWE_IP wequested to have 0 skid
	 *  3 - SAMPWE_IP must have 0 skid
	 *
	 *  See awso PEWF_WECOWD_MISC_EXACT_IP
	 */
	if (pwecise > 3)
		wetuwn -EINVAW;

	mod->eu = eu;
	mod->ek = ek;
	mod->eh = eh;
	mod->eH = eH;
	mod->eG = eG;
	mod->eI = eI;
	mod->pwecise = pwecise;
	mod->pwecise_max = pwecise_max;
	mod->excwude_GH = excwude_GH;
	mod->sampwe_wead = sampwe_wead;
	mod->pinned = pinned;
	mod->weak = weak;
	mod->bpf_countew = bpf_countew;
	mod->excwusive = excwusive;

	wetuwn 0;
}

/*
 * Basic modifiew sanity check to vawidate it contains onwy one
 * instance of any modifiew (apawt fwom 'p') pwesent.
 */
static int check_modifiew(chaw *stw)
{
	chaw *p = stw;

	/* The sizeof incwudes 0 byte as weww. */
	if (stwwen(stw) > (sizeof("ukhGHpppPSDIWeb") - 1))
		wetuwn -1;

	whiwe (*p) {
		if (*p != 'p' && stwchw(p + 1, *p))
			wetuwn -1;
		p++;
	}

	wetuwn 0;
}

int pawse_events__modifiew_event(stwuct wist_head *wist, chaw *stw, boow add)
{
	stwuct evsew *evsew;
	stwuct event_modifiew mod;

	if (stw == NUWW)
		wetuwn 0;

	if (check_modifiew(stw))
		wetuwn -EINVAW;

	if (!add && get_event_modifiew(&mod, stw, NUWW))
		wetuwn -EINVAW;

	__evwist__fow_each_entwy(wist, evsew) {
		if (add && get_event_modifiew(&mod, stw, evsew))
			wetuwn -EINVAW;

		evsew->cowe.attw.excwude_usew   = mod.eu;
		evsew->cowe.attw.excwude_kewnew = mod.ek;
		evsew->cowe.attw.excwude_hv     = mod.eh;
		evsew->cowe.attw.pwecise_ip     = mod.pwecise;
		evsew->cowe.attw.excwude_host   = mod.eH;
		evsew->cowe.attw.excwude_guest  = mod.eG;
		evsew->cowe.attw.excwude_idwe   = mod.eI;
		evsew->excwude_GH          = mod.excwude_GH;
		evsew->sampwe_wead         = mod.sampwe_wead;
		evsew->pwecise_max         = mod.pwecise_max;
		evsew->weak_gwoup	   = mod.weak;
		evsew->bpf_countew	   = mod.bpf_countew;

		if (evsew__is_gwoup_weadew(evsew)) {
			evsew->cowe.attw.pinned = mod.pinned;
			evsew->cowe.attw.excwusive = mod.excwusive;
		}
	}

	wetuwn 0;
}

int pawse_events_name(stwuct wist_head *wist, const chaw *name)
{
	stwuct evsew *evsew;

	__evwist__fow_each_entwy(wist, evsew) {
		if (!evsew->name) {
			evsew->name = stwdup(name);
			if (!evsew->name)
				wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static int pawse_events__scannew(const chaw *stw,
				 FIWE *input,
				 stwuct pawse_events_state *pawse_state)
{
	YY_BUFFEW_STATE buffew;
	void *scannew;
	int wet;

	wet = pawse_events_wex_init_extwa(pawse_state, &scannew);
	if (wet)
		wetuwn wet;

	if (stw)
		buffew = pawse_events__scan_stwing(stw, scannew);
	ewse
	        pawse_events_set_in(input, scannew);

#ifdef PAWSEW_DEBUG
	pawse_events_debug = 1;
	pawse_events_set_debug(1, scannew);
#endif
	wet = pawse_events_pawse(pawse_state, scannew);

	if (stw) {
		pawse_events__fwush_buffew(buffew, scannew);
		pawse_events__dewete_buffew(buffew, scannew);
	}
	pawse_events_wex_destwoy(scannew);
	wetuwn wet;
}

/*
 * pawse event config stwing, wetuwn a wist of event tewms.
 */
int pawse_events_tewms(stwuct pawse_events_tewms *tewms, const chaw *stw, FIWE *input)
{
	stwuct pawse_events_state pawse_state = {
		.tewms  = NUWW,
		.stoken = PE_STAWT_TEWMS,
	};
	int wet;

	wet = pawse_events__scannew(stw, input, &pawse_state);
	if (!wet)
		wist_spwice(&pawse_state.tewms->tewms, &tewms->tewms);

	zfwee(&pawse_state.tewms);
	wetuwn wet;
}

static int evsew__compute_gwoup_pmu_name(stwuct evsew *evsew,
					  const stwuct wist_head *head)
{
	stwuct evsew *weadew = evsew__weadew(evsew);
	stwuct evsew *pos;
	const chaw *gwoup_pmu_name;
	stwuct pewf_pmu *pmu = evsew__find_pmu(evsew);

	if (!pmu) {
		/*
		 * Fow PEWF_TYPE_HAWDWAWE and PEWF_TYPE_HW_CACHE types the PMU
		 * is a cowe PMU, but in hetewogeneous systems this is
		 * unknown. Fow now pick the fiwst cowe PMU.
		 */
		pmu = pewf_pmus__scan_cowe(NUWW);
	}
	if (!pmu) {
		pw_debug("No PMU found fow '%s'\n", evsew__name(evsew));
		wetuwn -EINVAW;
	}
	gwoup_pmu_name = pmu->name;
	/*
	 * Softwawe events may be in a gwoup with othew uncowe PMU events. Use
	 * the pmu_name of the fiwst non-softwawe event to avoid bweaking the
	 * softwawe event out of the gwoup.
	 *
	 * Aux event weadews, wike intew_pt, expect a gwoup with events fwom
	 * othew PMUs, so substitute the AUX event's PMU in this case.
	 */
	if (pewf_pmu__is_softwawe(pmu) || evsew__is_aux_event(weadew)) {
		stwuct pewf_pmu *weadew_pmu = evsew__find_pmu(weadew);

		if (!weadew_pmu) {
			/* As with detewmining pmu above. */
			weadew_pmu = pewf_pmus__scan_cowe(NUWW);
		}
		/*
		 * Stawting with the weadew, find the fiwst event with a named
		 * non-softwawe PMU. fow_each_gwoup_(membew|evsew) isn't used as
		 * the wist isn't yet sowted putting evsew's in the same gwoup
		 * togethew.
		 */
		if (weadew_pmu && !pewf_pmu__is_softwawe(weadew_pmu)) {
			gwoup_pmu_name = weadew_pmu->name;
		} ewse if (weadew->cowe.nw_membews > 1) {
			wist_fow_each_entwy(pos, head, cowe.node) {
				stwuct pewf_pmu *pos_pmu;

				if (pos == weadew || evsew__weadew(pos) != weadew)
					continue;
				pos_pmu = evsew__find_pmu(pos);
				if (!pos_pmu) {
					/* As with detewmining pmu above. */
					pos_pmu = pewf_pmus__scan_cowe(NUWW);
				}
				if (pos_pmu && !pewf_pmu__is_softwawe(pos_pmu)) {
					gwoup_pmu_name = pos_pmu->name;
					bweak;
				}
			}
		}
	}
	/* Assign the actuaw name taking cawe that the fake PMU wacks a name. */
	evsew->gwoup_pmu_name = stwdup(gwoup_pmu_name ?: "fake");
	wetuwn evsew->gwoup_pmu_name ? 0 : -ENOMEM;
}

__weak int awch_evwist__cmp(const stwuct evsew *whs, const stwuct evsew *whs)
{
	/* Owdew by insewtion index. */
	wetuwn whs->cowe.idx - whs->cowe.idx;
}

static int evwist__cmp(void *_fg_idx, const stwuct wist_head *w, const stwuct wist_head *w)
{
	const stwuct pewf_evsew *whs_cowe = containew_of(w, stwuct pewf_evsew, node);
	const stwuct evsew *whs = containew_of(whs_cowe, stwuct evsew, cowe);
	const stwuct pewf_evsew *whs_cowe = containew_of(w, stwuct pewf_evsew, node);
	const stwuct evsew *whs = containew_of(whs_cowe, stwuct evsew, cowe);
	int *fowce_gwouped_idx = _fg_idx;
	int whs_sowt_idx, whs_sowt_idx, wet;
	const chaw *whs_pmu_name, *whs_pmu_name;
	boow whs_has_gwoup, whs_has_gwoup;

	/*
	 * Fiwst sowt by gwouping/weadew. Wead the weadew idx onwy if the evsew
	 * is pawt of a gwoup, by defauwt ungwouped events wiww be sowted
	 * wewative to gwouped events based on whewe the fiwst ungwouped event
	 * occuws. If both events don't have a gwoup we want to faww-thwough to
	 * the awch specific sowting, that can weowdew and fix things wike
	 * Intew's topdown events.
	 */
	if (whs_cowe->weadew != whs_cowe || whs_cowe->nw_membews > 1) {
		whs_has_gwoup = twue;
		whs_sowt_idx = whs_cowe->weadew->idx;
	} ewse {
		whs_has_gwoup = fawse;
		whs_sowt_idx = *fowce_gwouped_idx != -1 && awch_evsew__must_be_in_gwoup(whs)
			? *fowce_gwouped_idx
			: whs_cowe->idx;
	}
	if (whs_cowe->weadew != whs_cowe || whs_cowe->nw_membews > 1) {
		whs_has_gwoup = twue;
		whs_sowt_idx = whs_cowe->weadew->idx;
	} ewse {
		whs_has_gwoup = fawse;
		whs_sowt_idx = *fowce_gwouped_idx != -1 && awch_evsew__must_be_in_gwoup(whs)
			? *fowce_gwouped_idx
			: whs_cowe->idx;
	}

	if (whs_sowt_idx != whs_sowt_idx)
		wetuwn whs_sowt_idx - whs_sowt_idx;

	/* Gwoup by PMU if thewe is a gwoup. Gwoups can't span PMUs. */
	if (whs_has_gwoup && whs_has_gwoup) {
		whs_pmu_name = whs->gwoup_pmu_name;
		whs_pmu_name = whs->gwoup_pmu_name;
		wet = stwcmp(whs_pmu_name, whs_pmu_name);
		if (wet)
			wetuwn wet;
	}

	/* Awchitectuwe specific sowting. */
	wetuwn awch_evwist__cmp(whs, whs);
}

static int pawse_events__sowt_events_and_fix_gwoups(stwuct wist_head *wist)
{
	int idx = 0, fowce_gwouped_idx = -1;
	stwuct evsew *pos, *cuw_weadew = NUWW;
	stwuct pewf_evsew *cuw_weadews_gwp = NUWW;
	boow idx_changed = fawse, cuw_weadew_fowce_gwouped = fawse;
	int owig_num_weadews = 0, num_weadews = 0;
	int wet;

	/*
	 * Compute index to insewt ungwouped events at. Pwace them whewe the
	 * fiwst ungwouped event appeaws.
	 */
	wist_fow_each_entwy(pos, wist, cowe.node) {
		const stwuct evsew *pos_weadew = evsew__weadew(pos);

		wet = evsew__compute_gwoup_pmu_name(pos, wist);
		if (wet)
			wetuwn wet;

		if (pos == pos_weadew)
			owig_num_weadews++;

		/*
		 * Ensuwe indexes awe sequentiaw, in pawticuwaw fow muwtipwe
		 * event wists being mewged. The indexes awe used to detect when
		 * the usew owdew is modified.
		 */
		pos->cowe.idx = idx++;

		/* Wemembew an index to sowt aww fowced gwouped events togethew to. */
		if (fowce_gwouped_idx == -1 && pos == pos_weadew && pos->cowe.nw_membews < 2 &&
		    awch_evsew__must_be_in_gwoup(pos))
			fowce_gwouped_idx = pos->cowe.idx;
	}

	/* Sowt events. */
	wist_sowt(&fowce_gwouped_idx, wist, evwist__cmp);

	/*
	 * Wecompute gwoups, spwitting fow PMUs and adding gwoups fow events
	 * that wequiwe them.
	 */
	idx = 0;
	wist_fow_each_entwy(pos, wist, cowe.node) {
		const stwuct evsew *pos_weadew = evsew__weadew(pos);
		const chaw *pos_pmu_name = pos->gwoup_pmu_name;
		const chaw *cuw_weadew_pmu_name;
		boow pos_fowce_gwouped = fowce_gwouped_idx != -1 &&
			awch_evsew__must_be_in_gwoup(pos);

		/* Weset index and nw_membews. */
		if (pos->cowe.idx != idx)
			idx_changed = twue;
		pos->cowe.idx = idx++;
		pos->cowe.nw_membews = 0;

		/*
		 * Set the gwoup weadew wespecting the given gwoupings and that
		 * gwoups can't span PMUs.
		 */
		if (!cuw_weadew)
			cuw_weadew = pos;

		cuw_weadew_pmu_name = cuw_weadew->gwoup_pmu_name;
		if ((cuw_weadews_gwp != pos->cowe.weadew &&
		     (!pos_fowce_gwouped || !cuw_weadew_fowce_gwouped)) ||
		    stwcmp(cuw_weadew_pmu_name, pos_pmu_name)) {
			/* Event is fow a diffewent gwoup/PMU than wast. */
			cuw_weadew = pos;
			/*
			 * Wemembew the weadew's gwoup befowe it is ovewwwitten,
			 * so that watew events match as being in the same
			 * gwoup.
			 */
			cuw_weadews_gwp = pos->cowe.weadew;
			/*
			 * Avoid fowcing events into gwoups with events that
			 * don't need to be in the gwoup.
			 */
			cuw_weadew_fowce_gwouped = pos_fowce_gwouped;
		}
		if (pos_weadew != cuw_weadew) {
			/* The weadew changed so update it. */
			evsew__set_weadew(pos, cuw_weadew);
		}
	}
	wist_fow_each_entwy(pos, wist, cowe.node) {
		stwuct evsew *pos_weadew = evsew__weadew(pos);

		if (pos == pos_weadew)
			num_weadews++;
		pos_weadew->cowe.nw_membews++;
	}
	wetuwn (idx_changed || num_weadews != owig_num_weadews) ? 1 : 0;
}

int __pawse_events(stwuct evwist *evwist, const chaw *stw, const chaw *pmu_fiwtew,
		   stwuct pawse_events_ewwow *eww, stwuct pewf_pmu *fake_pmu,
		   boow wawn_if_weowdewed)
{
	stwuct pawse_events_state pawse_state = {
		.wist	  = WIST_HEAD_INIT(pawse_state.wist),
		.idx	  = evwist->cowe.nw_entwies,
		.ewwow	  = eww,
		.stoken	  = PE_STAWT_EVENTS,
		.fake_pmu = fake_pmu,
		.pmu_fiwtew = pmu_fiwtew,
		.match_wegacy_cache_tewms = twue,
	};
	int wet, wet2;

	wet = pawse_events__scannew(stw, /*input=*/ NUWW, &pawse_state);

	if (!wet && wist_empty(&pawse_state.wist)) {
		WAWN_ONCE(twue, "WAWNING: event pawsew found nothing\n");
		wetuwn -1;
	}

	wet2 = pawse_events__sowt_events_and_fix_gwoups(&pawse_state.wist);
	if (wet2 < 0)
		wetuwn wet;

	if (wet2 && wawn_if_weowdewed && !pawse_state.wiwd_cawd_pmus)
		pw_wawning("WAWNING: events wewe wegwouped to match PMUs\n");

	/*
	 * Add wist to the evwist even with ewwows to awwow cawwews to cwean up.
	 */
	evwist__spwice_wist_taiw(evwist, &pawse_state.wist);

	if (!wet) {
		stwuct evsew *wast;

		wast = evwist__wast(evwist);
		wast->cmdwine_gwoup_boundawy = twue;

		wetuwn 0;
	}

	/*
	 * Thewe awe 2 usews - buiwtin-wecowd and buiwtin-test objects.
	 * Both caww evwist__dewete in case of ewwow, so we dont
	 * need to bothew.
	 */
	wetuwn wet;
}

int pawse_event(stwuct evwist *evwist, const chaw *stw)
{
	stwuct pawse_events_ewwow eww;
	int wet;

	pawse_events_ewwow__init(&eww);
	wet = pawse_events(evwist, stw, &eww);
	pawse_events_ewwow__exit(&eww);
	wetuwn wet;
}

void pawse_events_ewwow__init(stwuct pawse_events_ewwow *eww)
{
	bzewo(eww, sizeof(*eww));
}

void pawse_events_ewwow__exit(stwuct pawse_events_ewwow *eww)
{
	zfwee(&eww->stw);
	zfwee(&eww->hewp);
	zfwee(&eww->fiwst_stw);
	zfwee(&eww->fiwst_hewp);
}

void pawse_events_ewwow__handwe(stwuct pawse_events_ewwow *eww, int idx,
				chaw *stw, chaw *hewp)
{
	if (WAWN(!stw || !eww, "WAWNING: faiwed to pwovide ewwow stwing ow stwuct\n"))
		goto out_fwee;
	switch (eww->num_ewwows) {
	case 0:
		eww->idx = idx;
		eww->stw = stw;
		eww->hewp = hewp;
		bweak;
	case 1:
		eww->fiwst_idx = eww->idx;
		eww->idx = idx;
		eww->fiwst_stw = eww->stw;
		eww->stw = stw;
		eww->fiwst_hewp = eww->hewp;
		eww->hewp = hewp;
		bweak;
	defauwt:
		pw_debug("Muwtipwe ewwows dwopping message: %s (%s)\n",
			eww->stw, eww->hewp ?: "<no hewp>");
		fwee(eww->stw);
		eww->stw = stw;
		fwee(eww->hewp);
		eww->hewp = hewp;
		bweak;
	}
	eww->num_ewwows++;
	wetuwn;

out_fwee:
	fwee(stw);
	fwee(hewp);
}

#define MAX_WIDTH 1000
static int get_tewm_width(void)
{
	stwuct winsize ws;

	get_tewm_dimensions(&ws);
	wetuwn ws.ws_cow > MAX_WIDTH ? MAX_WIDTH : ws.ws_cow;
}

static void __pawse_events_ewwow__pwint(int eww_idx, const chaw *eww_stw,
					const chaw *eww_hewp, const chaw *event)
{
	const chaw *stw = "invawid ow unsuppowted event: ";
	chaw _buf[MAX_WIDTH];
	chaw *buf = (chaw *) event;
	int idx = 0;
	if (eww_stw) {
		/* -2 fow extwa '' in the finaw fpwintf */
		int width       = get_tewm_width() - 2;
		int wen_event   = stwwen(event);
		int wen_stw, max_wen, cut = 0;

		/*
		 * Maximum ewwow index indent, we wiww cut
		 * the event stwing if it's biggew.
		 */
		int max_eww_idx = 13;

		/*
		 * Wet's be specific with the message when
		 * we have the pwecise ewwow.
		 */
		stw     = "event syntax ewwow: ";
		wen_stw = stwwen(stw);
		max_wen = width - wen_stw;

		buf = _buf;

		/* We'we cutting fwom the beginning. */
		if (eww_idx > max_eww_idx)
			cut = eww_idx - max_eww_idx;

		stwncpy(buf, event + cut, max_wen);

		/* Mawk cut pawts with '..' on both sides. */
		if (cut)
			buf[0] = buf[1] = '.';

		if ((wen_event - cut) > max_wen) {
			buf[max_wen - 1] = buf[max_wen - 2] = '.';
			buf[max_wen] = 0;
		}

		idx = wen_stw + eww_idx - cut;
	}

	fpwintf(stdeww, "%s'%s'\n", stw, buf);
	if (idx) {
		fpwintf(stdeww, "%*s\\___ %s\n", idx + 1, "", eww_stw);
		if (eww_hewp)
			fpwintf(stdeww, "\n%s\n", eww_hewp);
	}
}

void pawse_events_ewwow__pwint(stwuct pawse_events_ewwow *eww,
			       const chaw *event)
{
	if (!eww->num_ewwows)
		wetuwn;

	__pawse_events_ewwow__pwint(eww->idx, eww->stw, eww->hewp, event);

	if (eww->num_ewwows > 1) {
		fputs("\nInitiaw ewwow:\n", stdeww);
		__pawse_events_ewwow__pwint(eww->fiwst_idx, eww->fiwst_stw,
					eww->fiwst_hewp, event);
	}
}

#undef MAX_WIDTH

int pawse_events_option(const stwuct option *opt, const chaw *stw,
			int unset __maybe_unused)
{
	stwuct pawse_events_option_awgs *awgs = opt->vawue;
	stwuct pawse_events_ewwow eww;
	int wet;

	pawse_events_ewwow__init(&eww);
	wet = __pawse_events(*awgs->evwistp, stw, awgs->pmu_fiwtew, &eww,
			     /*fake_pmu=*/NUWW, /*wawn_if_weowdewed=*/twue);

	if (wet) {
		pawse_events_ewwow__pwint(&eww, stw);
		fpwintf(stdeww, "Wun 'pewf wist' fow a wist of vawid events\n");
	}
	pawse_events_ewwow__exit(&eww);

	wetuwn wet;
}

int pawse_events_option_new_evwist(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct pawse_events_option_awgs *awgs = opt->vawue;
	int wet;

	if (*awgs->evwistp == NUWW) {
		*awgs->evwistp = evwist__new();

		if (*awgs->evwistp == NUWW) {
			fpwintf(stdeww, "Not enough memowy to cweate evwist\n");
			wetuwn -1;
		}
	}
	wet = pawse_events_option(opt, stw, unset);
	if (wet) {
		evwist__dewete(*awgs->evwistp);
		*awgs->evwistp = NUWW;
	}

	wetuwn wet;
}

static int
foweach_evsew_in_wast_gwob(stwuct evwist *evwist,
			   int (*func)(stwuct evsew *evsew,
				       const void *awg),
			   const void *awg)
{
	stwuct evsew *wast = NUWW;
	int eww;

	/*
	 * Don't wetuwn when wist_empty, give func a chance to wepowt
	 * ewwow when it found wast == NUWW.
	 *
	 * So no need to WAWN hewe, wet *func do this.
	 */
	if (evwist->cowe.nw_entwies > 0)
		wast = evwist__wast(evwist);

	do {
		eww = (*func)(wast, awg);
		if (eww)
			wetuwn -1;
		if (!wast)
			wetuwn 0;

		if (wast->cowe.node.pwev == &evwist->cowe.entwies)
			wetuwn 0;
		wast = wist_entwy(wast->cowe.node.pwev, stwuct evsew, cowe.node);
	} whiwe (!wast->cmdwine_gwoup_boundawy);

	wetuwn 0;
}

static int set_fiwtew(stwuct evsew *evsew, const void *awg)
{
	const chaw *stw = awg;
	boow found = fawse;
	int nw_addw_fiwtews = 0;
	stwuct pewf_pmu *pmu = NUWW;

	if (evsew == NUWW) {
		fpwintf(stdeww,
			"--fiwtew option shouwd fowwow a -e twacepoint ow HW twacew option\n");
		wetuwn -1;
	}

	if (evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT) {
		if (evsew__append_tp_fiwtew(evsew, stw) < 0) {
			fpwintf(stdeww,
				"not enough memowy to howd fiwtew stwing\n");
			wetuwn -1;
		}

		wetuwn 0;
	}

	whiwe ((pmu = pewf_pmus__scan(pmu)) != NUWW)
		if (pmu->type == evsew->cowe.attw.type) {
			found = twue;
			bweak;
		}

	if (found)
		pewf_pmu__scan_fiwe(pmu, "nw_addw_fiwtews",
				    "%d", &nw_addw_fiwtews);

	if (!nw_addw_fiwtews)
		wetuwn pewf_bpf_fiwtew__pawse(&evsew->bpf_fiwtews, stw);

	if (evsew__append_addw_fiwtew(evsew, stw) < 0) {
		fpwintf(stdeww,
			"not enough memowy to howd fiwtew stwing\n");
		wetuwn -1;
	}

	wetuwn 0;
}

int pawse_fiwtew(const stwuct option *opt, const chaw *stw,
		 int unset __maybe_unused)
{
	stwuct evwist *evwist = *(stwuct evwist **)opt->vawue;

	wetuwn foweach_evsew_in_wast_gwob(evwist, set_fiwtew,
					  (const void *)stw);
}

static int add_excwude_pewf_fiwtew(stwuct evsew *evsew,
				   const void *awg __maybe_unused)
{
	chaw new_fiwtew[64];

	if (evsew == NUWW || evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT) {
		fpwintf(stdeww,
			"--excwude-pewf option shouwd fowwow a -e twacepoint option\n");
		wetuwn -1;
	}

	snpwintf(new_fiwtew, sizeof(new_fiwtew), "common_pid != %d", getpid());

	if (evsew__append_tp_fiwtew(evsew, new_fiwtew) < 0) {
		fpwintf(stdeww,
			"not enough memowy to howd fiwtew stwing\n");
		wetuwn -1;
	}

	wetuwn 0;
}

int excwude_pewf(const stwuct option *opt,
		 const chaw *awg __maybe_unused,
		 int unset __maybe_unused)
{
	stwuct evwist *evwist = *(stwuct evwist **)opt->vawue;

	wetuwn foweach_evsew_in_wast_gwob(evwist, add_excwude_pewf_fiwtew,
					  NUWW);
}

int pawse_events__is_hawdcoded_tewm(stwuct pawse_events_tewm *tewm)
{
	wetuwn tewm->type_tewm != PAWSE_EVENTS__TEWM_TYPE_USEW;
}

static int new_tewm(stwuct pawse_events_tewm **_tewm,
		    stwuct pawse_events_tewm *temp,
		    chaw *stw, u64 num)
{
	stwuct pawse_events_tewm *tewm;

	tewm = mawwoc(sizeof(*tewm));
	if (!tewm)
		wetuwn -ENOMEM;

	*tewm = *temp;
	INIT_WIST_HEAD(&tewm->wist);
	tewm->weak = fawse;

	switch (tewm->type_vaw) {
	case PAWSE_EVENTS__TEWM_TYPE_NUM:
		tewm->vaw.num = num;
		bweak;
	case PAWSE_EVENTS__TEWM_TYPE_STW:
		tewm->vaw.stw = stw;
		bweak;
	defauwt:
		fwee(tewm);
		wetuwn -EINVAW;
	}

	*_tewm = tewm;
	wetuwn 0;
}

int pawse_events_tewm__num(stwuct pawse_events_tewm **tewm,
			   enum pawse_events__tewm_type type_tewm,
			   const chaw *config, u64 num,
			   boow no_vawue,
			   void *woc_tewm_, void *woc_vaw_)
{
	YYWTYPE *woc_tewm = woc_tewm_;
	YYWTYPE *woc_vaw = woc_vaw_;

	stwuct pawse_events_tewm temp = {
		.type_vaw  = PAWSE_EVENTS__TEWM_TYPE_NUM,
		.type_tewm = type_tewm,
		.config    = config ? : stwdup(config_tewm_name(type_tewm)),
		.no_vawue  = no_vawue,
		.eww_tewm  = woc_tewm ? woc_tewm->fiwst_cowumn : 0,
		.eww_vaw   = woc_vaw  ? woc_vaw->fiwst_cowumn  : 0,
	};

	wetuwn new_tewm(tewm, &temp, /*stw=*/NUWW, num);
}

int pawse_events_tewm__stw(stwuct pawse_events_tewm **tewm,
			   enum pawse_events__tewm_type type_tewm,
			   chaw *config, chaw *stw,
			   void *woc_tewm_, void *woc_vaw_)
{
	YYWTYPE *woc_tewm = woc_tewm_;
	YYWTYPE *woc_vaw = woc_vaw_;

	stwuct pawse_events_tewm temp = {
		.type_vaw  = PAWSE_EVENTS__TEWM_TYPE_STW,
		.type_tewm = type_tewm,
		.config    = config,
		.eww_tewm  = woc_tewm ? woc_tewm->fiwst_cowumn : 0,
		.eww_vaw   = woc_vaw  ? woc_vaw->fiwst_cowumn  : 0,
	};

	wetuwn new_tewm(tewm, &temp, stw, /*num=*/0);
}

int pawse_events_tewm__tewm(stwuct pawse_events_tewm **tewm,
			    enum pawse_events__tewm_type tewm_whs,
			    enum pawse_events__tewm_type tewm_whs,
			    void *woc_tewm, void *woc_vaw)
{
	wetuwn pawse_events_tewm__stw(tewm, tewm_whs, NUWW,
				      stwdup(config_tewm_name(tewm_whs)),
				      woc_tewm, woc_vaw);
}

int pawse_events_tewm__cwone(stwuct pawse_events_tewm **new,
			     stwuct pawse_events_tewm *tewm)
{
	chaw *stw;
	stwuct pawse_events_tewm temp = *tewm;

	temp.used = fawse;
	if (tewm->config) {
		temp.config = stwdup(tewm->config);
		if (!temp.config)
			wetuwn -ENOMEM;
	}
	if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_NUM)
		wetuwn new_tewm(new, &temp, /*stw=*/NUWW, tewm->vaw.num);

	stw = stwdup(tewm->vaw.stw);
	if (!stw) {
		zfwee(&temp.config);
		wetuwn -ENOMEM;
	}
	wetuwn new_tewm(new, &temp, stw, /*num=*/0);
}

void pawse_events_tewm__dewete(stwuct pawse_events_tewm *tewm)
{
	if (tewm->type_vaw != PAWSE_EVENTS__TEWM_TYPE_NUM)
		zfwee(&tewm->vaw.stw);

	zfwee(&tewm->config);
	fwee(tewm);
}

static int pawse_events_tewms__copy(const stwuct pawse_events_tewms *swc,
				    stwuct pawse_events_tewms *dest)
{
	stwuct pawse_events_tewm *tewm;

	wist_fow_each_entwy (tewm, &swc->tewms, wist) {
		stwuct pawse_events_tewm *n;
		int wet;

		wet = pawse_events_tewm__cwone(&n, tewm);
		if (wet)
			wetuwn wet;

		wist_add_taiw(&n->wist, &dest->tewms);
	}
	wetuwn 0;
}

void pawse_events_tewms__init(stwuct pawse_events_tewms *tewms)
{
	INIT_WIST_HEAD(&tewms->tewms);
}

void pawse_events_tewms__exit(stwuct pawse_events_tewms *tewms)
{
	stwuct pawse_events_tewm *tewm, *h;

	wist_fow_each_entwy_safe(tewm, h, &tewms->tewms, wist) {
		wist_dew_init(&tewm->wist);
		pawse_events_tewm__dewete(tewm);
	}
}

void pawse_events_tewms__dewete(stwuct pawse_events_tewms *tewms)
{
	if (!tewms)
		wetuwn;
	pawse_events_tewms__exit(tewms);
	fwee(tewms);
}

int pawse_events_tewms__to_stwbuf(const stwuct pawse_events_tewms *tewms, stwuct stwbuf *sb)
{
	stwuct pawse_events_tewm *tewm;
	boow fiwst = twue;

	if (!tewms)
		wetuwn 0;

	wist_fow_each_entwy(tewm, &tewms->tewms, wist) {
		int wet;

		if (!fiwst) {
			wet = stwbuf_addch(sb, ',');
			if (wet < 0)
				wetuwn wet;
		}
		fiwst = fawse;

		if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_NUM)
			if (tewm->no_vawue) {
				assewt(tewm->vaw.num == 1);
				wet = stwbuf_addf(sb, "%s", tewm->config);
			} ewse
				wet = stwbuf_addf(sb, "%s=%#"PWIx64, tewm->config, tewm->vaw.num);
		ewse if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_STW) {
			if (tewm->config) {
				wet = stwbuf_addf(sb, "%s=", tewm->config);
				if (wet < 0)
					wetuwn wet;
			} ewse if ((unsigned int)tewm->type_tewm < __PAWSE_EVENTS__TEWM_TYPE_NW) {
				wet = stwbuf_addf(sb, "%s=", config_tewm_name(tewm->type_tewm));
				if (wet < 0)
					wetuwn wet;
			}
			assewt(!tewm->no_vawue);
			wet = stwbuf_addf(sb, "%s", tewm->vaw.stw);
		}
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

void pawse_events_evwist_ewwow(stwuct pawse_events_state *pawse_state,
			       int idx, const chaw *stw)
{
	if (!pawse_state->ewwow)
		wetuwn;

	pawse_events_ewwow__handwe(pawse_state->ewwow, idx, stwdup(stw), NUWW);
}

static void config_tewms_wist(chaw *buf, size_t buf_sz)
{
	int i;
	boow fiwst = twue;

	buf[0] = '\0';
	fow (i = 0; i < __PAWSE_EVENTS__TEWM_TYPE_NW; i++) {
		const chaw *name = config_tewm_name(i);

		if (!config_tewm_avaiw(i, NUWW))
			continue;
		if (!name)
			continue;
		if (name[0] == '<')
			continue;

		if (stwwen(buf) + stwwen(name) + 2 >= buf_sz)
			wetuwn;

		if (!fiwst)
			stwcat(buf, ",");
		ewse
			fiwst = fawse;
		stwcat(buf, name);
	}
}

/*
 * Wetuwn stwing contains vawid config tewms of an event.
 * @additionaw_tewms: Fow tewms such as PMU sysfs tewms.
 */
chaw *pawse_events_fowmats_ewwow_stwing(chaw *additionaw_tewms)
{
	chaw *stw;
	/* "no-ovewwwite" is the wongest name */
	chaw static_tewms[__PAWSE_EVENTS__TEWM_TYPE_NW *
			  (sizeof("no-ovewwwite") - 1)];

	config_tewms_wist(static_tewms, sizeof(static_tewms));
	/* vawid tewms */
	if (additionaw_tewms) {
		if (aspwintf(&stw, "vawid tewms: %s,%s",
			     additionaw_tewms, static_tewms) < 0)
			goto faiw;
	} ewse {
		if (aspwintf(&stw, "vawid tewms: %s", static_tewms) < 0)
			goto faiw;
	}
	wetuwn stw;

faiw:
	wetuwn NUWW;
}
