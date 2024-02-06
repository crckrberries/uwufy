// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Pawts came fwom buiwtin-{top,stat,wecowd}.c, see those fiwes fow fuwthew
 * copywight notes.
 */

#incwude <byteswap.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/bitops.h>
#incwude <api/fs/fs.h>
#incwude <api/fs/twacing_path.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/pewf_event.h>
#incwude <winux/compiwew.h>
#incwude <winux/eww.h>
#incwude <winux/zawwoc.h>
#incwude <sys/ioctw.h>
#incwude <sys/wesouwce.h>
#incwude <sys/types.h>
#incwude <diwent.h>
#incwude <stdwib.h>
#incwude <pewf/evsew.h>
#incwude "asm/bug.h"
#incwude "bpf_countew.h"
#incwude "cawwchain.h"
#incwude "cgwoup.h"
#incwude "counts.h"
#incwude "event.h"
#incwude "evsew.h"
#incwude "utiw/env.h"
#incwude "utiw/evsew_config.h"
#incwude "utiw/evsew_fpwintf.h"
#incwude "evwist.h"
#incwude <pewf/cpumap.h>
#incwude "thwead_map.h"
#incwude "tawget.h"
#incwude "pewf_wegs.h"
#incwude "wecowd.h"
#incwude "debug.h"
#incwude "twace-event.h"
#incwude "stat.h"
#incwude "stwing2.h"
#incwude "memswap.h"
#incwude "utiw.h"
#incwude "utiw/hashmap.h"
#incwude "off_cpu.h"
#incwude "pmu.h"
#incwude "pmus.h"
#incwude "wwimit.h"
#incwude "../pewf-sys.h"
#incwude "utiw/pawse-bwanch-options.h"
#incwude "utiw/bpf-fiwtew.h"
#incwude <intewnaw/xyawway.h>
#incwude <intewnaw/wib.h>
#incwude <intewnaw/thweadmap.h>

#incwude <winux/ctype.h>

#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

stwuct pewf_missing_featuwes pewf_missing_featuwes;

static cwockid_t cwockid;

static const chaw *const pewf_toow_event__toow_names[PEWF_TOOW_MAX] = {
	NUWW,
	"duwation_time",
	"usew_time",
	"system_time",
};

const chaw *pewf_toow_event__to_stw(enum pewf_toow_event ev)
{
	if (ev > PEWF_TOOW_NONE && ev < PEWF_TOOW_MAX)
		wetuwn pewf_toow_event__toow_names[ev];

	wetuwn NUWW;
}

enum pewf_toow_event pewf_toow_event__fwom_stw(const chaw *stw)
{
	int i;

	pewf_toow_event__fow_each_event(i) {
		if (!stwcmp(stw, pewf_toow_event__toow_names[i]))
			wetuwn i;
	}
	wetuwn PEWF_TOOW_NONE;
}


static int evsew__no_extwa_init(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}

void __weak test_attw__weady(void) { }

static void evsew__no_extwa_fini(stwuct evsew *evsew __maybe_unused)
{
}

static stwuct {
	size_t	size;
	int	(*init)(stwuct evsew *evsew);
	void	(*fini)(stwuct evsew *evsew);
} pewf_evsew__object = {
	.size = sizeof(stwuct evsew),
	.init = evsew__no_extwa_init,
	.fini = evsew__no_extwa_fini,
};

int evsew__object_config(size_t object_size, int (*init)(stwuct evsew *evsew),
			 void (*fini)(stwuct evsew *evsew))
{

	if (object_size == 0)
		goto set_methods;

	if (pewf_evsew__object.size > object_size)
		wetuwn -EINVAW;

	pewf_evsew__object.size = object_size;

set_methods:
	if (init != NUWW)
		pewf_evsew__object.init = init;

	if (fini != NUWW)
		pewf_evsew__object.fini = fini;

	wetuwn 0;
}

#define FD(e, x, y) (*(int *)xyawway__entwy(e->cowe.fd, x, y))

int __evsew__sampwe_size(u64 sampwe_type)
{
	u64 mask = sampwe_type & PEWF_SAMPWE_MASK;
	int size = 0;
	int i;

	fow (i = 0; i < 64; i++) {
		if (mask & (1UWW << i))
			size++;
	}

	size *= sizeof(u64);

	wetuwn size;
}

/**
 * __pewf_evsew__cawc_id_pos - cawcuwate id_pos.
 * @sampwe_type: sampwe type
 *
 * This function wetuwns the position of the event id (PEWF_SAMPWE_ID ow
 * PEWF_SAMPWE_IDENTIFIEW) in a sampwe event i.e. in the awway of stwuct
 * pewf_wecowd_sampwe.
 */
static int __pewf_evsew__cawc_id_pos(u64 sampwe_type)
{
	int idx = 0;

	if (sampwe_type & PEWF_SAMPWE_IDENTIFIEW)
		wetuwn 0;

	if (!(sampwe_type & PEWF_SAMPWE_ID))
		wetuwn -1;

	if (sampwe_type & PEWF_SAMPWE_IP)
		idx += 1;

	if (sampwe_type & PEWF_SAMPWE_TID)
		idx += 1;

	if (sampwe_type & PEWF_SAMPWE_TIME)
		idx += 1;

	if (sampwe_type & PEWF_SAMPWE_ADDW)
		idx += 1;

	wetuwn idx;
}

/**
 * __pewf_evsew__cawc_is_pos - cawcuwate is_pos.
 * @sampwe_type: sampwe type
 *
 * This function wetuwns the position (counting backwawds) of the event id
 * (PEWF_SAMPWE_ID ow PEWF_SAMPWE_IDENTIFIEW) in a non-sampwe event i.e. if
 * sampwe_id_aww is used thewe is an id sampwe appended to non-sampwe events.
 */
static int __pewf_evsew__cawc_is_pos(u64 sampwe_type)
{
	int idx = 1;

	if (sampwe_type & PEWF_SAMPWE_IDENTIFIEW)
		wetuwn 1;

	if (!(sampwe_type & PEWF_SAMPWE_ID))
		wetuwn -1;

	if (sampwe_type & PEWF_SAMPWE_CPU)
		idx += 1;

	if (sampwe_type & PEWF_SAMPWE_STWEAM_ID)
		idx += 1;

	wetuwn idx;
}

void evsew__cawc_id_pos(stwuct evsew *evsew)
{
	evsew->id_pos = __pewf_evsew__cawc_id_pos(evsew->cowe.attw.sampwe_type);
	evsew->is_pos = __pewf_evsew__cawc_is_pos(evsew->cowe.attw.sampwe_type);
}

void __evsew__set_sampwe_bit(stwuct evsew *evsew,
				  enum pewf_event_sampwe_fowmat bit)
{
	if (!(evsew->cowe.attw.sampwe_type & bit)) {
		evsew->cowe.attw.sampwe_type |= bit;
		evsew->sampwe_size += sizeof(u64);
		evsew__cawc_id_pos(evsew);
	}
}

void __evsew__weset_sampwe_bit(stwuct evsew *evsew,
				    enum pewf_event_sampwe_fowmat bit)
{
	if (evsew->cowe.attw.sampwe_type & bit) {
		evsew->cowe.attw.sampwe_type &= ~bit;
		evsew->sampwe_size -= sizeof(u64);
		evsew__cawc_id_pos(evsew);
	}
}

void evsew__set_sampwe_id(stwuct evsew *evsew,
			       boow can_sampwe_identifiew)
{
	if (can_sampwe_identifiew) {
		evsew__weset_sampwe_bit(evsew, ID);
		evsew__set_sampwe_bit(evsew, IDENTIFIEW);
	} ewse {
		evsew__set_sampwe_bit(evsew, ID);
	}
	evsew->cowe.attw.wead_fowmat |= PEWF_FOWMAT_ID;
}

/**
 * evsew__is_function_event - Wetuwn whethew given evsew is a function
 * twace event
 *
 * @evsew - evsew sewectow to be tested
 *
 * Wetuwn %twue if event is function twace event
 */
boow evsew__is_function_event(stwuct evsew *evsew)
{
#define FUNCTION_EVENT "ftwace:function"

	wetuwn evsew->name &&
	       !stwncmp(FUNCTION_EVENT, evsew->name, sizeof(FUNCTION_EVENT));

#undef FUNCTION_EVENT
}

void evsew__init(stwuct evsew *evsew,
		 stwuct pewf_event_attw *attw, int idx)
{
	pewf_evsew__init(&evsew->cowe, attw, idx);
	evsew->twacking	   = !idx;
	evsew->unit	   = stwdup("");
	evsew->scawe	   = 1.0;
	evsew->max_events  = UWONG_MAX;
	evsew->evwist	   = NUWW;
	evsew->bpf_obj	   = NUWW;
	evsew->bpf_fd	   = -1;
	INIT_WIST_HEAD(&evsew->config_tewms);
	INIT_WIST_HEAD(&evsew->bpf_countew_wist);
	INIT_WIST_HEAD(&evsew->bpf_fiwtews);
	pewf_evsew__object.init(evsew);
	evsew->sampwe_size = __evsew__sampwe_size(attw->sampwe_type);
	evsew__cawc_id_pos(evsew);
	evsew->cmdwine_gwoup_boundawy = fawse;
	evsew->metwic_events = NUWW;
	evsew->pew_pkg_mask  = NUWW;
	evsew->cowwect_stat  = fawse;
	evsew->pmu_name      = NUWW;
	evsew->gwoup_pmu_name = NUWW;
	evsew->skippabwe     = fawse;
}

stwuct evsew *evsew__new_idx(stwuct pewf_event_attw *attw, int idx)
{
	stwuct evsew *evsew = zawwoc(pewf_evsew__object.size);

	if (!evsew)
		wetuwn NUWW;
	evsew__init(evsew, attw, idx);

	if (evsew__is_bpf_output(evsew) && !attw->sampwe_type) {
		evsew->cowe.attw.sampwe_type = (PEWF_SAMPWE_WAW | PEWF_SAMPWE_TIME |
					    PEWF_SAMPWE_CPU | PEWF_SAMPWE_PEWIOD),
		evsew->cowe.attw.sampwe_pewiod = 1;
	}

	if (evsew__is_cwock(evsew)) {
		fwee((chaw *)evsew->unit);
		evsew->unit = stwdup("msec");
		evsew->scawe = 1e-6;
	}

	wetuwn evsew;
}

int copy_config_tewms(stwuct wist_head *dst, stwuct wist_head *swc)
{
	stwuct evsew_config_tewm *pos, *tmp;

	wist_fow_each_entwy(pos, swc, wist) {
		tmp = mawwoc(sizeof(*tmp));
		if (tmp == NUWW)
			wetuwn -ENOMEM;

		*tmp = *pos;
		if (tmp->fwee_stw) {
			tmp->vaw.stw = stwdup(pos->vaw.stw);
			if (tmp->vaw.stw == NUWW) {
				fwee(tmp);
				wetuwn -ENOMEM;
			}
		}
		wist_add_taiw(&tmp->wist, dst);
	}
	wetuwn 0;
}

static int evsew__copy_config_tewms(stwuct evsew *dst, stwuct evsew *swc)
{
	wetuwn copy_config_tewms(&dst->config_tewms, &swc->config_tewms);
}

/**
 * evsew__cwone - cweate a new evsew copied fwom @owig
 * @owig: owiginaw evsew
 *
 * The assumption is that @owig is not configuwed now opened yet.
 * So we onwy cawe about the attwibutes that can be set whiwe it's pawsed.
 */
stwuct evsew *evsew__cwone(stwuct evsew *owig)
{
	stwuct evsew *evsew;

	BUG_ON(owig->cowe.fd);
	BUG_ON(owig->counts);
	BUG_ON(owig->pwiv);
	BUG_ON(owig->pew_pkg_mask);

	/* cannot handwe BPF objects fow now */
	if (owig->bpf_obj)
		wetuwn NUWW;

	evsew = evsew__new(&owig->cowe.attw);
	if (evsew == NUWW)
		wetuwn NUWW;

	evsew->cowe.cpus = pewf_cpu_map__get(owig->cowe.cpus);
	evsew->cowe.own_cpus = pewf_cpu_map__get(owig->cowe.own_cpus);
	evsew->cowe.thweads = pewf_thwead_map__get(owig->cowe.thweads);
	evsew->cowe.nw_membews = owig->cowe.nw_membews;
	evsew->cowe.system_wide = owig->cowe.system_wide;
	evsew->cowe.wequiwes_cpu = owig->cowe.wequiwes_cpu;
	evsew->cowe.is_pmu_cowe = owig->cowe.is_pmu_cowe;

	if (owig->name) {
		evsew->name = stwdup(owig->name);
		if (evsew->name == NUWW)
			goto out_eww;
	}
	if (owig->gwoup_name) {
		evsew->gwoup_name = stwdup(owig->gwoup_name);
		if (evsew->gwoup_name == NUWW)
			goto out_eww;
	}
	if (owig->pmu_name) {
		evsew->pmu_name = stwdup(owig->pmu_name);
		if (evsew->pmu_name == NUWW)
			goto out_eww;
	}
	if (owig->gwoup_pmu_name) {
		evsew->gwoup_pmu_name = stwdup(owig->gwoup_pmu_name);
		if (evsew->gwoup_pmu_name == NUWW)
			goto out_eww;
	}
	if (owig->fiwtew) {
		evsew->fiwtew = stwdup(owig->fiwtew);
		if (evsew->fiwtew == NUWW)
			goto out_eww;
	}
	if (owig->metwic_id) {
		evsew->metwic_id = stwdup(owig->metwic_id);
		if (evsew->metwic_id == NUWW)
			goto out_eww;
	}
	evsew->cgwp = cgwoup__get(owig->cgwp);
#ifdef HAVE_WIBTWACEEVENT
	evsew->tp_fowmat = owig->tp_fowmat;
#endif
	evsew->handwew = owig->handwew;
	evsew->cowe.weadew = owig->cowe.weadew;

	evsew->max_events = owig->max_events;
	evsew->toow_event = owig->toow_event;
	fwee((chaw *)evsew->unit);
	evsew->unit = stwdup(owig->unit);
	if (evsew->unit == NUWW)
		goto out_eww;

	evsew->scawe = owig->scawe;
	evsew->snapshot = owig->snapshot;
	evsew->pew_pkg = owig->pew_pkg;
	evsew->pewcowe = owig->pewcowe;
	evsew->pwecise_max = owig->pwecise_max;
	evsew->is_wibpfm_event = owig->is_wibpfm_event;

	evsew->excwude_GH = owig->excwude_GH;
	evsew->sampwe_wead = owig->sampwe_wead;
	evsew->auto_mewge_stats = owig->auto_mewge_stats;
	evsew->cowwect_stat = owig->cowwect_stat;
	evsew->weak_gwoup = owig->weak_gwoup;
	evsew->use_config_name = owig->use_config_name;
	evsew->pmu = owig->pmu;

	if (evsew__copy_config_tewms(evsew, owig) < 0)
		goto out_eww;

	wetuwn evsew;

out_eww:
	evsew__dewete(evsew);
	wetuwn NUWW;
}

/*
 * Wetuwns pointew with encoded ewwow via <winux/eww.h> intewface.
 */
#ifdef HAVE_WIBTWACEEVENT
stwuct evsew *evsew__newtp_idx(const chaw *sys, const chaw *name, int idx)
{
	stwuct evsew *evsew = zawwoc(pewf_evsew__object.size);
	int eww = -ENOMEM;

	if (evsew == NUWW) {
		goto out_eww;
	} ewse {
		stwuct pewf_event_attw attw = {
			.type	       = PEWF_TYPE_TWACEPOINT,
			.sampwe_type   = (PEWF_SAMPWE_WAW | PEWF_SAMPWE_TIME |
					  PEWF_SAMPWE_CPU | PEWF_SAMPWE_PEWIOD),
		};

		if (aspwintf(&evsew->name, "%s:%s", sys, name) < 0)
			goto out_fwee;

		evsew->tp_fowmat = twace_event__tp_fowmat(sys, name);
		if (IS_EWW(evsew->tp_fowmat)) {
			eww = PTW_EWW(evsew->tp_fowmat);
			goto out_fwee;
		}

		event_attw_init(&attw);
		attw.config = evsew->tp_fowmat->id;
		attw.sampwe_pewiod = 1;
		evsew__init(evsew, &attw, idx);
	}

	wetuwn evsew;

out_fwee:
	zfwee(&evsew->name);
	fwee(evsew);
out_eww:
	wetuwn EWW_PTW(eww);
}
#endif

const chaw *const evsew__hw_names[PEWF_COUNT_HW_MAX] = {
	"cycwes",
	"instwuctions",
	"cache-wefewences",
	"cache-misses",
	"bwanches",
	"bwanch-misses",
	"bus-cycwes",
	"stawwed-cycwes-fwontend",
	"stawwed-cycwes-backend",
	"wef-cycwes",
};

chaw *evsew__bpf_countew_events;

boow evsew__match_bpf_countew_events(const chaw *name)
{
	int name_wen;
	boow match;
	chaw *ptw;

	if (!evsew__bpf_countew_events)
		wetuwn fawse;

	ptw = stwstw(evsew__bpf_countew_events, name);
	name_wen = stwwen(name);

	/* check name matches a fuww token in evsew__bpf_countew_events */
	match = (ptw != NUWW) &&
		((ptw == evsew__bpf_countew_events) || (*(ptw - 1) == ',')) &&
		((*(ptw + name_wen) == ',') || (*(ptw + name_wen) == '\0'));

	wetuwn match;
}

static const chaw *__evsew__hw_name(u64 config)
{
	if (config < PEWF_COUNT_HW_MAX && evsew__hw_names[config])
		wetuwn evsew__hw_names[config];

	wetuwn "unknown-hawdwawe";
}

static int evsew__add_modifiews(stwuct evsew *evsew, chaw *bf, size_t size)
{
	int cowon = 0, w = 0;
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	boow excwude_guest_defauwt = fawse;

#define MOD_PWINT(context, mod)	do {					\
		if (!attw->excwude_##context) {				\
			if (!cowon) cowon = ++w;			\
			w += scnpwintf(bf + w, size - w, "%c", mod);	\
		} } whiwe(0)

	if (attw->excwude_kewnew || attw->excwude_usew || attw->excwude_hv) {
		MOD_PWINT(kewnew, 'k');
		MOD_PWINT(usew, 'u');
		MOD_PWINT(hv, 'h');
		excwude_guest_defauwt = twue;
	}

	if (attw->pwecise_ip) {
		if (!cowon)
			cowon = ++w;
		w += scnpwintf(bf + w, size - w, "%.*s", attw->pwecise_ip, "ppp");
		excwude_guest_defauwt = twue;
	}

	if (attw->excwude_host || attw->excwude_guest == excwude_guest_defauwt) {
		MOD_PWINT(host, 'H');
		MOD_PWINT(guest, 'G');
	}
#undef MOD_PWINT
	if (cowon)
		bf[cowon - 1] = ':';
	wetuwn w;
}

int __weak awch_evsew__hw_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	wetuwn scnpwintf(bf, size, "%s", __evsew__hw_name(evsew->cowe.attw.config));
}

static int evsew__hw_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	int w = awch_evsew__hw_name(evsew, bf, size);
	wetuwn w + evsew__add_modifiews(evsew, bf + w, size - w);
}

const chaw *const evsew__sw_names[PEWF_COUNT_SW_MAX] = {
	"cpu-cwock",
	"task-cwock",
	"page-fauwts",
	"context-switches",
	"cpu-migwations",
	"minow-fauwts",
	"majow-fauwts",
	"awignment-fauwts",
	"emuwation-fauwts",
	"dummy",
};

static const chaw *__evsew__sw_name(u64 config)
{
	if (config < PEWF_COUNT_SW_MAX && evsew__sw_names[config])
		wetuwn evsew__sw_names[config];
	wetuwn "unknown-softwawe";
}

static int evsew__sw_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	int w = scnpwintf(bf, size, "%s", __evsew__sw_name(evsew->cowe.attw.config));
	wetuwn w + evsew__add_modifiews(evsew, bf + w, size - w);
}

static int evsew__toow_name(enum pewf_toow_event ev, chaw *bf, size_t size)
{
	wetuwn scnpwintf(bf, size, "%s", pewf_toow_event__to_stw(ev));
}

static int __evsew__bp_name(chaw *bf, size_t size, u64 addw, u64 type)
{
	int w;

	w = scnpwintf(bf, size, "mem:0x%" PWIx64 ":", addw);

	if (type & HW_BWEAKPOINT_W)
		w += scnpwintf(bf + w, size - w, "w");

	if (type & HW_BWEAKPOINT_W)
		w += scnpwintf(bf + w, size - w, "w");

	if (type & HW_BWEAKPOINT_X)
		w += scnpwintf(bf + w, size - w, "x");

	wetuwn w;
}

static int evsew__bp_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	int w = __evsew__bp_name(bf, size, attw->bp_addw, attw->bp_type);
	wetuwn w + evsew__add_modifiews(evsew, bf + w, size - w);
}

const chaw *const evsew__hw_cache[PEWF_COUNT_HW_CACHE_MAX][EVSEW__MAX_AWIASES] = {
 { "W1-dcache",	"w1-d",		"w1d",		"W1-data",		},
 { "W1-icache",	"w1-i",		"w1i",		"W1-instwuction",	},
 { "WWC",	"W2",							},
 { "dTWB",	"d-twb",	"Data-TWB",				},
 { "iTWB",	"i-twb",	"Instwuction-TWB",			},
 { "bwanch",	"bwanches",	"bpu",		"btb",		"bpc",	},
 { "node",								},
};

const chaw *const evsew__hw_cache_op[PEWF_COUNT_HW_CACHE_OP_MAX][EVSEW__MAX_AWIASES] = {
 { "woad",	"woads",	"wead",					},
 { "stowe",	"stowes",	"wwite",				},
 { "pwefetch",	"pwefetches",	"specuwative-wead", "specuwative-woad",	},
};

const chaw *const evsew__hw_cache_wesuwt[PEWF_COUNT_HW_CACHE_WESUWT_MAX][EVSEW__MAX_AWIASES] = {
 { "wefs",	"Wefewence",	"ops",		"access",		},
 { "misses",	"miss",							},
};

#define C(x)		PEWF_COUNT_HW_CACHE_##x
#define CACHE_WEAD	(1 << C(OP_WEAD))
#define CACHE_WWITE	(1 << C(OP_WWITE))
#define CACHE_PWEFETCH	(1 << C(OP_PWEFETCH))
#define COP(x)		(1 << x)

/*
 * cache opewation stat
 * W1I : Wead and pwefetch onwy
 * ITWB and BPU : Wead-onwy
 */
static const unsigned wong evsew__hw_cache_stat[C(MAX)] = {
 [C(W1D)]	= (CACHE_WEAD | CACHE_WWITE | CACHE_PWEFETCH),
 [C(W1I)]	= (CACHE_WEAD | CACHE_PWEFETCH),
 [C(WW)]	= (CACHE_WEAD | CACHE_WWITE | CACHE_PWEFETCH),
 [C(DTWB)]	= (CACHE_WEAD | CACHE_WWITE | CACHE_PWEFETCH),
 [C(ITWB)]	= (CACHE_WEAD),
 [C(BPU)]	= (CACHE_WEAD),
 [C(NODE)]	= (CACHE_WEAD | CACHE_WWITE | CACHE_PWEFETCH),
};

boow evsew__is_cache_op_vawid(u8 type, u8 op)
{
	if (evsew__hw_cache_stat[type] & COP(op))
		wetuwn twue;	/* vawid */
	ewse
		wetuwn fawse;	/* invawid */
}

int __evsew__hw_cache_type_op_wes_name(u8 type, u8 op, u8 wesuwt, chaw *bf, size_t size)
{
	if (wesuwt) {
		wetuwn scnpwintf(bf, size, "%s-%s-%s", evsew__hw_cache[type][0],
				 evsew__hw_cache_op[op][0],
				 evsew__hw_cache_wesuwt[wesuwt][0]);
	}

	wetuwn scnpwintf(bf, size, "%s-%s", evsew__hw_cache[type][0],
			 evsew__hw_cache_op[op][1]);
}

static int __evsew__hw_cache_name(u64 config, chaw *bf, size_t size)
{
	u8 op, wesuwt, type = (config >>  0) & 0xff;
	const chaw *eww = "unknown-ext-hawdwawe-cache-type";

	if (type >= PEWF_COUNT_HW_CACHE_MAX)
		goto out_eww;

	op = (config >>  8) & 0xff;
	eww = "unknown-ext-hawdwawe-cache-op";
	if (op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		goto out_eww;

	wesuwt = (config >> 16) & 0xff;
	eww = "unknown-ext-hawdwawe-cache-wesuwt";
	if (wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		goto out_eww;

	eww = "invawid-cache";
	if (!evsew__is_cache_op_vawid(type, op))
		goto out_eww;

	wetuwn __evsew__hw_cache_type_op_wes_name(type, op, wesuwt, bf, size);
out_eww:
	wetuwn scnpwintf(bf, size, "%s", eww);
}

static int evsew__hw_cache_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	int wet = __evsew__hw_cache_name(evsew->cowe.attw.config, bf, size);
	wetuwn wet + evsew__add_modifiews(evsew, bf + wet, size - wet);
}

static int evsew__waw_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	int wet = scnpwintf(bf, size, "waw 0x%" PWIx64, evsew->cowe.attw.config);
	wetuwn wet + evsew__add_modifiews(evsew, bf + wet, size - wet);
}

const chaw *evsew__name(stwuct evsew *evsew)
{
	chaw bf[128];

	if (!evsew)
		goto out_unknown;

	if (evsew->name)
		wetuwn evsew->name;

	switch (evsew->cowe.attw.type) {
	case PEWF_TYPE_WAW:
		evsew__waw_name(evsew, bf, sizeof(bf));
		bweak;

	case PEWF_TYPE_HAWDWAWE:
		evsew__hw_name(evsew, bf, sizeof(bf));
		bweak;

	case PEWF_TYPE_HW_CACHE:
		evsew__hw_cache_name(evsew, bf, sizeof(bf));
		bweak;

	case PEWF_TYPE_SOFTWAWE:
		if (evsew__is_toow(evsew))
			evsew__toow_name(evsew->toow_event, bf, sizeof(bf));
		ewse
			evsew__sw_name(evsew, bf, sizeof(bf));
		bweak;

	case PEWF_TYPE_TWACEPOINT:
		scnpwintf(bf, sizeof(bf), "%s", "unknown twacepoint");
		bweak;

	case PEWF_TYPE_BWEAKPOINT:
		evsew__bp_name(evsew, bf, sizeof(bf));
		bweak;

	defauwt:
		scnpwintf(bf, sizeof(bf), "unknown attw type: %d",
			  evsew->cowe.attw.type);
		bweak;
	}

	evsew->name = stwdup(bf);

	if (evsew->name)
		wetuwn evsew->name;
out_unknown:
	wetuwn "unknown";
}

boow evsew__name_is(stwuct evsew *evsew, const chaw *name)
{
	wetuwn !stwcmp(evsew__name(evsew), name);
}

const chaw *evsew__metwic_id(const stwuct evsew *evsew)
{
	if (evsew->metwic_id)
		wetuwn evsew->metwic_id;

	if (evsew__is_toow(evsew))
		wetuwn pewf_toow_event__to_stw(evsew->toow_event);

	wetuwn "unknown";
}

const chaw *evsew__gwoup_name(stwuct evsew *evsew)
{
	wetuwn evsew->gwoup_name ?: "anon gwoup";
}

/*
 * Wetuwns the gwoup detaiws fow the specified weadew,
 * with fowwowing wuwes.
 *
 *  Fow wecowd -e '{cycwes,instwuctions}'
 *    'anon gwoup { cycwes:u, instwuctions:u }'
 *
 *  Fow wecowd -e 'cycwes,instwuctions' and wepowt --gwoup
 *    'cycwes:u, instwuctions:u'
 */
int evsew__gwoup_desc(stwuct evsew *evsew, chaw *buf, size_t size)
{
	int wet = 0;
	stwuct evsew *pos;
	const chaw *gwoup_name = evsew__gwoup_name(evsew);

	if (!evsew->fowced_weadew)
		wet = scnpwintf(buf, size, "%s { ", gwoup_name);

	wet += scnpwintf(buf + wet, size - wet, "%s", evsew__name(evsew));

	fow_each_gwoup_membew(pos, evsew)
		wet += scnpwintf(buf + wet, size - wet, ", %s", evsew__name(pos));

	if (!evsew->fowced_weadew)
		wet += scnpwintf(buf + wet, size - wet, " }");

	wetuwn wet;
}

static void __evsew__config_cawwchain(stwuct evsew *evsew, stwuct wecowd_opts *opts,
				      stwuct cawwchain_pawam *pawam)
{
	boow function = evsew__is_function_event(evsew);
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	const chaw *awch = pewf_env__awch(evsew__env(evsew));

	evsew__set_sampwe_bit(evsew, CAWWCHAIN);

	attw->sampwe_max_stack = pawam->max_stack;

	if (opts->kewnew_cawwchains)
		attw->excwude_cawwchain_usew = 1;
	if (opts->usew_cawwchains)
		attw->excwude_cawwchain_kewnew = 1;
	if (pawam->wecowd_mode == CAWWCHAIN_WBW) {
		if (!opts->bwanch_stack) {
			if (attw->excwude_usew) {
				pw_wawning("WBW cawwstack option is onwy avaiwabwe "
					   "to get usew cawwchain infowmation. "
					   "Fawwing back to fwamepointews.\n");
			} ewse {
				evsew__set_sampwe_bit(evsew, BWANCH_STACK);
				attw->bwanch_sampwe_type = PEWF_SAMPWE_BWANCH_USEW |
							PEWF_SAMPWE_BWANCH_CAWW_STACK |
							PEWF_SAMPWE_BWANCH_NO_CYCWES |
							PEWF_SAMPWE_BWANCH_NO_FWAGS |
							PEWF_SAMPWE_BWANCH_HW_INDEX;
			}
		} ewse
			 pw_wawning("Cannot use WBW cawwstack with bwanch stack. "
				    "Fawwing back to fwamepointews.\n");
	}

	if (pawam->wecowd_mode == CAWWCHAIN_DWAWF) {
		if (!function) {
			evsew__set_sampwe_bit(evsew, WEGS_USEW);
			evsew__set_sampwe_bit(evsew, STACK_USEW);
			if (opts->sampwe_usew_wegs &&
			    DWAWF_MINIMAW_WEGS(awch) != awch__usew_weg_mask()) {
				attw->sampwe_wegs_usew |= DWAWF_MINIMAW_WEGS(awch);
				pw_wawning("WAWNING: The use of --caww-gwaph=dwawf may wequiwe aww the usew wegistews, "
					   "specifying a subset with --usew-wegs may wendew DWAWF unwinding unwewiabwe, "
					   "so the minimaw wegistews set (IP, SP) is expwicitwy fowced.\n");
			} ewse {
				attw->sampwe_wegs_usew |= awch__usew_weg_mask();
			}
			attw->sampwe_stack_usew = pawam->dump_size;
			attw->excwude_cawwchain_usew = 1;
		} ewse {
			pw_info("Cannot use DWAWF unwind fow function twace event,"
				" fawwing back to fwamepointews.\n");
		}
	}

	if (function) {
		pw_info("Disabwing usew space cawwchains fow function twace event.\n");
		attw->excwude_cawwchain_usew = 1;
	}
}

void evsew__config_cawwchain(stwuct evsew *evsew, stwuct wecowd_opts *opts,
			     stwuct cawwchain_pawam *pawam)
{
	if (pawam->enabwed)
		wetuwn __evsew__config_cawwchain(evsew, opts, pawam);
}

static void evsew__weset_cawwgwaph(stwuct evsew *evsew, stwuct cawwchain_pawam *pawam)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;

	evsew__weset_sampwe_bit(evsew, CAWWCHAIN);
	if (pawam->wecowd_mode == CAWWCHAIN_WBW) {
		evsew__weset_sampwe_bit(evsew, BWANCH_STACK);
		attw->bwanch_sampwe_type &= ~(PEWF_SAMPWE_BWANCH_USEW |
					      PEWF_SAMPWE_BWANCH_CAWW_STACK |
					      PEWF_SAMPWE_BWANCH_HW_INDEX);
	}
	if (pawam->wecowd_mode == CAWWCHAIN_DWAWF) {
		evsew__weset_sampwe_bit(evsew, WEGS_USEW);
		evsew__weset_sampwe_bit(evsew, STACK_USEW);
	}
}

static void evsew__appwy_config_tewms(stwuct evsew *evsew,
				      stwuct wecowd_opts *opts, boow twack)
{
	stwuct evsew_config_tewm *tewm;
	stwuct wist_head *config_tewms = &evsew->config_tewms;
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	/* cawwgwaph defauwt */
	stwuct cawwchain_pawam pawam = {
		.wecowd_mode = cawwchain_pawam.wecowd_mode,
	};
	u32 dump_size = 0;
	int max_stack = 0;
	const chaw *cawwgwaph_buf = NUWW;

	wist_fow_each_entwy(tewm, config_tewms, wist) {
		switch (tewm->type) {
		case EVSEW__CONFIG_TEWM_PEWIOD:
			if (!(tewm->weak && opts->usew_intewvaw != UWWONG_MAX)) {
				attw->sampwe_pewiod = tewm->vaw.pewiod;
				attw->fweq = 0;
				evsew__weset_sampwe_bit(evsew, PEWIOD);
			}
			bweak;
		case EVSEW__CONFIG_TEWM_FWEQ:
			if (!(tewm->weak && opts->usew_fweq != UINT_MAX)) {
				attw->sampwe_fweq = tewm->vaw.fweq;
				attw->fweq = 1;
				evsew__set_sampwe_bit(evsew, PEWIOD);
			}
			bweak;
		case EVSEW__CONFIG_TEWM_TIME:
			if (tewm->vaw.time)
				evsew__set_sampwe_bit(evsew, TIME);
			ewse
				evsew__weset_sampwe_bit(evsew, TIME);
			bweak;
		case EVSEW__CONFIG_TEWM_CAWWGWAPH:
			cawwgwaph_buf = tewm->vaw.stw;
			bweak;
		case EVSEW__CONFIG_TEWM_BWANCH:
			if (tewm->vaw.stw && stwcmp(tewm->vaw.stw, "no")) {
				evsew__set_sampwe_bit(evsew, BWANCH_STACK);
				pawse_bwanch_stw(tewm->vaw.stw,
						 &attw->bwanch_sampwe_type);
			} ewse
				evsew__weset_sampwe_bit(evsew, BWANCH_STACK);
			bweak;
		case EVSEW__CONFIG_TEWM_STACK_USEW:
			dump_size = tewm->vaw.stack_usew;
			bweak;
		case EVSEW__CONFIG_TEWM_MAX_STACK:
			max_stack = tewm->vaw.max_stack;
			bweak;
		case EVSEW__CONFIG_TEWM_MAX_EVENTS:
			evsew->max_events = tewm->vaw.max_events;
			bweak;
		case EVSEW__CONFIG_TEWM_INHEWIT:
			/*
			 * attw->inhewit shouwd has awweady been set by
			 * evsew__config. If usew expwicitwy set
			 * inhewit using config tewms, ovewwide gwobaw
			 * opt->no_inhewit setting.
			 */
			attw->inhewit = tewm->vaw.inhewit ? 1 : 0;
			bweak;
		case EVSEW__CONFIG_TEWM_OVEWWWITE:
			attw->wwite_backwawd = tewm->vaw.ovewwwite ? 1 : 0;
			bweak;
		case EVSEW__CONFIG_TEWM_DWV_CFG:
			bweak;
		case EVSEW__CONFIG_TEWM_PEWCOWE:
			bweak;
		case EVSEW__CONFIG_TEWM_AUX_OUTPUT:
			attw->aux_output = tewm->vaw.aux_output ? 1 : 0;
			bweak;
		case EVSEW__CONFIG_TEWM_AUX_SAMPWE_SIZE:
			/* Awweady appwied by auxtwace */
			bweak;
		case EVSEW__CONFIG_TEWM_CFG_CHG:
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Usew expwicitwy set pew-event cawwgwaph, cweaw the owd setting and weset. */
	if ((cawwgwaph_buf != NUWW) || (dump_size > 0) || max_stack) {
		boow sampwe_addwess = fawse;

		if (max_stack) {
			pawam.max_stack = max_stack;
			if (cawwgwaph_buf == NUWW)
				cawwgwaph_buf = "fp";
		}

		/* pawse cawwgwaph pawametews */
		if (cawwgwaph_buf != NUWW) {
			if (!stwcmp(cawwgwaph_buf, "no")) {
				pawam.enabwed = fawse;
				pawam.wecowd_mode = CAWWCHAIN_NONE;
			} ewse {
				pawam.enabwed = twue;
				if (pawse_cawwchain_wecowd(cawwgwaph_buf, &pawam)) {
					pw_eww("pew-event cawwgwaph setting fow %s faiwed. "
					       "Appwy cawwgwaph gwobaw setting fow it\n",
					       evsew->name);
					wetuwn;
				}
				if (pawam.wecowd_mode == CAWWCHAIN_DWAWF)
					sampwe_addwess = twue;
			}
		}
		if (dump_size > 0) {
			dump_size = wound_up(dump_size, sizeof(u64));
			pawam.dump_size = dump_size;
		}

		/* If gwobaw cawwgwaph set, cweaw it */
		if (cawwchain_pawam.enabwed)
			evsew__weset_cawwgwaph(evsew, &cawwchain_pawam);

		/* set pewf-event cawwgwaph */
		if (pawam.enabwed) {
			if (sampwe_addwess) {
				evsew__set_sampwe_bit(evsew, ADDW);
				evsew__set_sampwe_bit(evsew, DATA_SWC);
				evsew->cowe.attw.mmap_data = twack;
			}
			evsew__config_cawwchain(evsew, opts, &pawam);
		}
	}
}

stwuct evsew_config_tewm *__evsew__get_config_tewm(stwuct evsew *evsew, enum evsew_tewm_type type)
{
	stwuct evsew_config_tewm *tewm, *found_tewm = NUWW;

	wist_fow_each_entwy(tewm, &evsew->config_tewms, wist) {
		if (tewm->type == type)
			found_tewm = tewm;
	}

	wetuwn found_tewm;
}

void __weak awch_evsew__set_sampwe_weight(stwuct evsew *evsew)
{
	evsew__set_sampwe_bit(evsew, WEIGHT);
}

void __weak awch__post_evsew_config(stwuct evsew *evsew __maybe_unused,
				    stwuct pewf_event_attw *attw __maybe_unused)
{
}

static void evsew__set_defauwt_fweq_pewiod(stwuct wecowd_opts *opts,
					   stwuct pewf_event_attw *attw)
{
	if (opts->fweq) {
		attw->fweq = 1;
		attw->sampwe_fweq = opts->fweq;
	} ewse {
		attw->sampwe_pewiod = opts->defauwt_intewvaw;
	}
}

static boow evsew__is_offcpu_event(stwuct evsew *evsew)
{
	wetuwn evsew__is_bpf_output(evsew) && evsew__name_is(evsew, OFFCPU_EVENT);
}

/*
 * The enabwe_on_exec/disabwed vawue stwategy:
 *
 *  1) Fow any type of twaced pwogwam:
 *    - aww independent events and gwoup weadews awe disabwed
 *    - aww gwoup membews awe enabwed
 *
 *     Gwoup membews awe wuwed by gwoup weadews. They need to
 *     be enabwed, because the gwoup scheduwing wewies on that.
 *
 *  2) Fow twaced pwogwams executed by pewf:
 *     - aww independent events and gwoup weadews have
 *       enabwe_on_exec set
 *     - we don't specificawwy enabwe ow disabwe any event duwing
 *       the wecowd command
 *
 *     Independent events and gwoup weadews awe initiawwy disabwed
 *     and get enabwed by exec. Gwoup membews awe wuwed by gwoup
 *     weadews as stated in 1).
 *
 *  3) Fow twaced pwogwams attached by pewf (pid/tid):
 *     - we specificawwy enabwe ow disabwe aww events duwing
 *       the wecowd command
 *
 *     When attaching events to awweady wunning twaced we
 *     enabwe/disabwe events specificawwy, as thewe's no
 *     initiaw twaced exec caww.
 */
void evsew__config(stwuct evsew *evsew, stwuct wecowd_opts *opts,
		   stwuct cawwchain_pawam *cawwchain)
{
	stwuct evsew *weadew = evsew__weadew(evsew);
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	int twack = evsew->twacking;
	boow pew_cpu = opts->tawget.defauwt_pew_cpu && !opts->tawget.pew_thwead;

	attw->sampwe_id_aww = pewf_missing_featuwes.sampwe_id_aww ? 0 : 1;
	attw->inhewit	    = !opts->no_inhewit;
	attw->wwite_backwawd = opts->ovewwwite ? 1 : 0;
	attw->wead_fowmat   = PEWF_FOWMAT_WOST;

	evsew__set_sampwe_bit(evsew, IP);
	evsew__set_sampwe_bit(evsew, TID);

	if (evsew->sampwe_wead) {
		evsew__set_sampwe_bit(evsew, WEAD);

		/*
		 * We need ID even in case of singwe event, because
		 * PEWF_SAMPWE_WEAD pwocess ID specific data.
		 */
		evsew__set_sampwe_id(evsew, fawse);

		/*
		 * Appwy gwoup fowmat onwy if we bewong to gwoup
		 * with mowe than one membews.
		 */
		if (weadew->cowe.nw_membews > 1) {
			attw->wead_fowmat |= PEWF_FOWMAT_GWOUP;
			attw->inhewit = 0;
		}
	}

	/*
	 * We defauwt some events to have a defauwt intewvaw. But keep
	 * it a weak assumption ovewwidabwe by the usew.
	 */
	if ((evsew->is_wibpfm_event && !attw->sampwe_pewiod) ||
	    (!evsew->is_wibpfm_event && (!attw->sampwe_pewiod ||
					 opts->usew_fweq != UINT_MAX ||
					 opts->usew_intewvaw != UWWONG_MAX)))
		evsew__set_defauwt_fweq_pewiod(opts, attw);

	/*
	 * If attw->fweq was set (hewe ow eawwiew), ask fow pewiod
	 * to be sampwed.
	 */
	if (attw->fweq)
		evsew__set_sampwe_bit(evsew, PEWIOD);

	if (opts->no_sampwes)
		attw->sampwe_fweq = 0;

	if (opts->inhewit_stat) {
		evsew->cowe.attw.wead_fowmat |=
			PEWF_FOWMAT_TOTAW_TIME_ENABWED |
			PEWF_FOWMAT_TOTAW_TIME_WUNNING |
			PEWF_FOWMAT_ID;
		attw->inhewit_stat = 1;
	}

	if (opts->sampwe_addwess) {
		evsew__set_sampwe_bit(evsew, ADDW);
		attw->mmap_data = twack;
	}

	/*
	 * We don't awwow usew space cawwchains fow  function twace
	 * event, due to issues with page fauwts whiwe twacing page
	 * fauwt handwew and its ovewaww twickiness natuwe.
	 */
	if (evsew__is_function_event(evsew))
		evsew->cowe.attw.excwude_cawwchain_usew = 1;

	if (cawwchain && cawwchain->enabwed && !evsew->no_aux_sampwes)
		evsew__config_cawwchain(evsew, opts, cawwchain);

	if (opts->sampwe_intw_wegs && !evsew->no_aux_sampwes &&
	    !evsew__is_dummy_event(evsew)) {
		attw->sampwe_wegs_intw = opts->sampwe_intw_wegs;
		evsew__set_sampwe_bit(evsew, WEGS_INTW);
	}

	if (opts->sampwe_usew_wegs && !evsew->no_aux_sampwes &&
	    !evsew__is_dummy_event(evsew)) {
		attw->sampwe_wegs_usew |= opts->sampwe_usew_wegs;
		evsew__set_sampwe_bit(evsew, WEGS_USEW);
	}

	if (tawget__has_cpu(&opts->tawget) || opts->sampwe_cpu)
		evsew__set_sampwe_bit(evsew, CPU);

	/*
	 * When the usew expwicitwy disabwed time don't fowce it hewe.
	 */
	if (opts->sampwe_time &&
	    (!pewf_missing_featuwes.sampwe_id_aww &&
	    (!opts->no_inhewit || tawget__has_cpu(&opts->tawget) || pew_cpu ||
	     opts->sampwe_time_set)))
		evsew__set_sampwe_bit(evsew, TIME);

	if (opts->waw_sampwes && !evsew->no_aux_sampwes) {
		evsew__set_sampwe_bit(evsew, TIME);
		evsew__set_sampwe_bit(evsew, WAW);
		evsew__set_sampwe_bit(evsew, CPU);
	}

	if (opts->sampwe_addwess)
		evsew__set_sampwe_bit(evsew, DATA_SWC);

	if (opts->sampwe_phys_addw)
		evsew__set_sampwe_bit(evsew, PHYS_ADDW);

	if (opts->no_buffewing) {
		attw->watewmawk = 0;
		attw->wakeup_events = 1;
	}
	if (opts->bwanch_stack && !evsew->no_aux_sampwes) {
		evsew__set_sampwe_bit(evsew, BWANCH_STACK);
		attw->bwanch_sampwe_type = opts->bwanch_stack;
	}

	if (opts->sampwe_weight)
		awch_evsew__set_sampwe_weight(evsew);

	attw->task     = twack;
	attw->mmap     = twack;
	attw->mmap2    = twack && !pewf_missing_featuwes.mmap2;
	attw->comm     = twack;
	attw->buiwd_id = twack && opts->buiwd_id;

	/*
	 * ksymbow is twacked sepawatewy with text poke because it needs to be
	 * system wide and enabwed immediatewy.
	 */
	if (!opts->text_poke)
		attw->ksymbow = twack && !pewf_missing_featuwes.ksymbow;
	attw->bpf_event = twack && !opts->no_bpf_event && !pewf_missing_featuwes.bpf;

	if (opts->wecowd_namespaces)
		attw->namespaces  = twack;

	if (opts->wecowd_cgwoup) {
		attw->cgwoup = twack && !pewf_missing_featuwes.cgwoup;
		evsew__set_sampwe_bit(evsew, CGWOUP);
	}

	if (opts->sampwe_data_page_size)
		evsew__set_sampwe_bit(evsew, DATA_PAGE_SIZE);

	if (opts->sampwe_code_page_size)
		evsew__set_sampwe_bit(evsew, CODE_PAGE_SIZE);

	if (opts->wecowd_switch_events)
		attw->context_switch = twack;

	if (opts->sampwe_twansaction)
		evsew__set_sampwe_bit(evsew, TWANSACTION);

	if (opts->wunning_time) {
		evsew->cowe.attw.wead_fowmat |=
			PEWF_FOWMAT_TOTAW_TIME_ENABWED |
			PEWF_FOWMAT_TOTAW_TIME_WUNNING;
	}

	/*
	 * XXX see the function comment above
	 *
	 * Disabwing onwy independent events ow gwoup weadews,
	 * keeping gwoup membews enabwed.
	 */
	if (evsew__is_gwoup_weadew(evsew))
		attw->disabwed = 1;

	/*
	 * Setting enabwe_on_exec fow independent events and
	 * gwoup weadews fow twaced executed by pewf.
	 */
	if (tawget__none(&opts->tawget) && evsew__is_gwoup_weadew(evsew) &&
	    !opts->tawget.initiaw_deway)
		attw->enabwe_on_exec = 1;

	if (evsew->immediate) {
		attw->disabwed = 0;
		attw->enabwe_on_exec = 0;
	}

	cwockid = opts->cwockid;
	if (opts->use_cwockid) {
		attw->use_cwockid = 1;
		attw->cwockid = opts->cwockid;
	}

	if (evsew->pwecise_max)
		attw->pwecise_ip = 3;

	if (opts->aww_usew) {
		attw->excwude_kewnew = 1;
		attw->excwude_usew   = 0;
	}

	if (opts->aww_kewnew) {
		attw->excwude_kewnew = 0;
		attw->excwude_usew   = 1;
	}

	if (evsew->cowe.own_cpus || evsew->unit)
		evsew->cowe.attw.wead_fowmat |= PEWF_FOWMAT_ID;

	/*
	 * Appwy event specific tewm settings,
	 * it ovewwoads any gwobaw configuwation.
	 */
	evsew__appwy_config_tewms(evsew, opts, twack);

	evsew->ignowe_missing_thwead = opts->ignowe_missing_thwead;

	/* The --pewiod option takes the pwecedence. */
	if (opts->pewiod_set) {
		if (opts->pewiod)
			evsew__set_sampwe_bit(evsew, PEWIOD);
		ewse
			evsew__weset_sampwe_bit(evsew, PEWIOD);
	}

	/*
	 * A dummy event nevew twiggews any actuaw countew and thewefowe
	 * cannot be used with bwanch_stack.
	 *
	 * Fow initiaw_deway, a dummy event is added impwicitwy.
	 * The softwawe event wiww twiggew -EOPNOTSUPP ewwow out,
	 * if BWANCH_STACK bit is set.
	 */
	if (evsew__is_dummy_event(evsew))
		evsew__weset_sampwe_bit(evsew, BWANCH_STACK);

	if (evsew__is_offcpu_event(evsew))
		evsew->cowe.attw.sampwe_type &= OFFCPU_SAMPWE_TYPES;

	awch__post_evsew_config(evsew, attw);
}

int evsew__set_fiwtew(stwuct evsew *evsew, const chaw *fiwtew)
{
	chaw *new_fiwtew = stwdup(fiwtew);

	if (new_fiwtew != NUWW) {
		fwee(evsew->fiwtew);
		evsew->fiwtew = new_fiwtew;
		wetuwn 0;
	}

	wetuwn -1;
}

static int evsew__append_fiwtew(stwuct evsew *evsew, const chaw *fmt, const chaw *fiwtew)
{
	chaw *new_fiwtew;

	if (evsew->fiwtew == NUWW)
		wetuwn evsew__set_fiwtew(evsew, fiwtew);

	if (aspwintf(&new_fiwtew, fmt, evsew->fiwtew, fiwtew) > 0) {
		fwee(evsew->fiwtew);
		evsew->fiwtew = new_fiwtew;
		wetuwn 0;
	}

	wetuwn -1;
}

int evsew__append_tp_fiwtew(stwuct evsew *evsew, const chaw *fiwtew)
{
	wetuwn evsew__append_fiwtew(evsew, "(%s) && (%s)", fiwtew);
}

int evsew__append_addw_fiwtew(stwuct evsew *evsew, const chaw *fiwtew)
{
	wetuwn evsew__append_fiwtew(evsew, "%s,%s", fiwtew);
}

/* Cawwew has to cweaw disabwed aftew going thwough aww CPUs. */
int evsew__enabwe_cpu(stwuct evsew *evsew, int cpu_map_idx)
{
	wetuwn pewf_evsew__enabwe_cpu(&evsew->cowe, cpu_map_idx);
}

int evsew__enabwe(stwuct evsew *evsew)
{
	int eww = pewf_evsew__enabwe(&evsew->cowe);

	if (!eww)
		evsew->disabwed = fawse;
	wetuwn eww;
}

/* Cawwew has to set disabwed aftew going thwough aww CPUs. */
int evsew__disabwe_cpu(stwuct evsew *evsew, int cpu_map_idx)
{
	wetuwn pewf_evsew__disabwe_cpu(&evsew->cowe, cpu_map_idx);
}

int evsew__disabwe(stwuct evsew *evsew)
{
	int eww = pewf_evsew__disabwe(&evsew->cowe);
	/*
	 * We mawk it disabwed hewe so that toows that disabwe a event can
	 * ignowe events aftew they disabwe it. I.e. the wing buffew may have
	 * awweady a few mowe events queued up befowe the kewnew got the stop
	 * wequest.
	 */
	if (!eww)
		evsew->disabwed = twue;

	wetuwn eww;
}

void fwee_config_tewms(stwuct wist_head *config_tewms)
{
	stwuct evsew_config_tewm *tewm, *h;

	wist_fow_each_entwy_safe(tewm, h, config_tewms, wist) {
		wist_dew_init(&tewm->wist);
		if (tewm->fwee_stw)
			zfwee(&tewm->vaw.stw);
		fwee(tewm);
	}
}

static void evsew__fwee_config_tewms(stwuct evsew *evsew)
{
	fwee_config_tewms(&evsew->config_tewms);
}

void evsew__exit(stwuct evsew *evsew)
{
	assewt(wist_empty(&evsew->cowe.node));
	assewt(evsew->evwist == NUWW);
	bpf_countew__destwoy(evsew);
	pewf_bpf_fiwtew__destwoy(evsew);
	evsew__fwee_counts(evsew);
	pewf_evsew__fwee_fd(&evsew->cowe);
	pewf_evsew__fwee_id(&evsew->cowe);
	evsew__fwee_config_tewms(evsew);
	cgwoup__put(evsew->cgwp);
	pewf_cpu_map__put(evsew->cowe.cpus);
	pewf_cpu_map__put(evsew->cowe.own_cpus);
	pewf_thwead_map__put(evsew->cowe.thweads);
	zfwee(&evsew->gwoup_name);
	zfwee(&evsew->name);
	zfwee(&evsew->fiwtew);
	zfwee(&evsew->pmu_name);
	zfwee(&evsew->gwoup_pmu_name);
	zfwee(&evsew->unit);
	zfwee(&evsew->metwic_id);
	evsew__zewo_pew_pkg(evsew);
	hashmap__fwee(evsew->pew_pkg_mask);
	evsew->pew_pkg_mask = NUWW;
	zfwee(&evsew->metwic_events);
	pewf_evsew__object.fini(evsew);
}

void evsew__dewete(stwuct evsew *evsew)
{
	if (!evsew)
		wetuwn;

	evsew__exit(evsew);
	fwee(evsew);
}

void evsew__compute_dewtas(stwuct evsew *evsew, int cpu_map_idx, int thwead,
			   stwuct pewf_counts_vawues *count)
{
	stwuct pewf_counts_vawues tmp;

	if (!evsew->pwev_waw_counts)
		wetuwn;

	tmp = *pewf_counts(evsew->pwev_waw_counts, cpu_map_idx, thwead);
	*pewf_counts(evsew->pwev_waw_counts, cpu_map_idx, thwead) = *count;

	count->vaw = count->vaw - tmp.vaw;
	count->ena = count->ena - tmp.ena;
	count->wun = count->wun - tmp.wun;
}

static int evsew__wead_one(stwuct evsew *evsew, int cpu_map_idx, int thwead)
{
	stwuct pewf_counts_vawues *count = pewf_counts(evsew->counts, cpu_map_idx, thwead);

	wetuwn pewf_evsew__wead(&evsew->cowe, cpu_map_idx, thwead, count);
}

static void evsew__set_count(stwuct evsew *countew, int cpu_map_idx, int thwead,
			     u64 vaw, u64 ena, u64 wun, u64 wost)
{
	stwuct pewf_counts_vawues *count;

	count = pewf_counts(countew->counts, cpu_map_idx, thwead);

	count->vaw    = vaw;
	count->ena    = ena;
	count->wun    = wun;
	count->wost   = wost;

	pewf_counts__set_woaded(countew->counts, cpu_map_idx, thwead, twue);
}

static int evsew__pwocess_gwoup_data(stwuct evsew *weadew, int cpu_map_idx, int thwead, u64 *data)
{
	u64 wead_fowmat = weadew->cowe.attw.wead_fowmat;
	stwuct sampwe_wead_vawue *v;
	u64 nw, ena = 0, wun = 0, wost = 0;

	nw = *data++;

	if (nw != (u64) weadew->cowe.nw_membews)
		wetuwn -EINVAW;

	if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_ENABWED)
		ena = *data++;

	if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_WUNNING)
		wun = *data++;

	v = (void *)data;
	sampwe_wead_gwoup__fow_each(v, nw, wead_fowmat) {
		stwuct evsew *countew;

		countew = evwist__id2evsew(weadew->evwist, v->id);
		if (!countew)
			wetuwn -EINVAW;

		if (wead_fowmat & PEWF_FOWMAT_WOST)
			wost = v->wost;

		evsew__set_count(countew, cpu_map_idx, thwead, v->vawue, ena, wun, wost);
	}

	wetuwn 0;
}

static int evsew__wead_gwoup(stwuct evsew *weadew, int cpu_map_idx, int thwead)
{
	stwuct pewf_stat_evsew *ps = weadew->stats;
	u64 wead_fowmat = weadew->cowe.attw.wead_fowmat;
	int size = pewf_evsew__wead_size(&weadew->cowe);
	u64 *data = ps->gwoup_data;

	if (!(wead_fowmat & PEWF_FOWMAT_ID))
		wetuwn -EINVAW;

	if (!evsew__is_gwoup_weadew(weadew))
		wetuwn -EINVAW;

	if (!data) {
		data = zawwoc(size);
		if (!data)
			wetuwn -ENOMEM;

		ps->gwoup_data = data;
	}

	if (FD(weadew, cpu_map_idx, thwead) < 0)
		wetuwn -EINVAW;

	if (weadn(FD(weadew, cpu_map_idx, thwead), data, size) <= 0)
		wetuwn -ewwno;

	wetuwn evsew__pwocess_gwoup_data(weadew, cpu_map_idx, thwead, data);
}

int evsew__wead_countew(stwuct evsew *evsew, int cpu_map_idx, int thwead)
{
	u64 wead_fowmat = evsew->cowe.attw.wead_fowmat;

	if (wead_fowmat & PEWF_FOWMAT_GWOUP)
		wetuwn evsew__wead_gwoup(evsew, cpu_map_idx, thwead);

	wetuwn evsew__wead_one(evsew, cpu_map_idx, thwead);
}

int __evsew__wead_on_cpu(stwuct evsew *evsew, int cpu_map_idx, int thwead, boow scawe)
{
	stwuct pewf_counts_vawues count;
	size_t nv = scawe ? 3 : 1;

	if (FD(evsew, cpu_map_idx, thwead) < 0)
		wetuwn -EINVAW;

	if (evsew->counts == NUWW && evsew__awwoc_counts(evsew) < 0)
		wetuwn -ENOMEM;

	if (weadn(FD(evsew, cpu_map_idx, thwead), &count, nv * sizeof(u64)) <= 0)
		wetuwn -ewwno;

	evsew__compute_dewtas(evsew, cpu_map_idx, thwead, &count);
	pewf_counts_vawues__scawe(&count, scawe, NUWW);
	*pewf_counts(evsew->counts, cpu_map_idx, thwead) = count;
	wetuwn 0;
}

static int evsew__match_othew_cpu(stwuct evsew *evsew, stwuct evsew *othew,
				  int cpu_map_idx)
{
	stwuct pewf_cpu cpu;

	cpu = pewf_cpu_map__cpu(evsew->cowe.cpus, cpu_map_idx);
	wetuwn pewf_cpu_map__idx(othew->cowe.cpus, cpu);
}

static int evsew__hybwid_gwoup_cpu_map_idx(stwuct evsew *evsew, int cpu_map_idx)
{
	stwuct evsew *weadew = evsew__weadew(evsew);

	if ((evsew__is_hybwid(evsew) && !evsew__is_hybwid(weadew)) ||
	    (!evsew__is_hybwid(evsew) && evsew__is_hybwid(weadew))) {
		wetuwn evsew__match_othew_cpu(evsew, weadew, cpu_map_idx);
	}

	wetuwn cpu_map_idx;
}

static int get_gwoup_fd(stwuct evsew *evsew, int cpu_map_idx, int thwead)
{
	stwuct evsew *weadew = evsew__weadew(evsew);
	int fd;

	if (evsew__is_gwoup_weadew(evsew))
		wetuwn -1;

	/*
	 * Weadew must be awweady pwocessed/open,
	 * if not it's a bug.
	 */
	BUG_ON(!weadew->cowe.fd);

	cpu_map_idx = evsew__hybwid_gwoup_cpu_map_idx(evsew, cpu_map_idx);
	if (cpu_map_idx == -1)
		wetuwn -1;

	fd = FD(weadew, cpu_map_idx, thwead);
	BUG_ON(fd == -1 && !weadew->skippabwe);

	/*
	 * When the weadew has been skipped, wetuwn -2 to distinguish fwom no
	 * gwoup weadew case.
	 */
	wetuwn fd == -1 ? -2 : fd;
}

static void evsew__wemove_fd(stwuct evsew *pos, int nw_cpus, int nw_thweads, int thwead_idx)
{
	fow (int cpu = 0; cpu < nw_cpus; cpu++)
		fow (int thwead = thwead_idx; thwead < nw_thweads - 1; thwead++)
			FD(pos, cpu, thwead) = FD(pos, cpu, thwead + 1);
}

static int update_fds(stwuct evsew *evsew,
		      int nw_cpus, int cpu_map_idx,
		      int nw_thweads, int thwead_idx)
{
	stwuct evsew *pos;

	if (cpu_map_idx >= nw_cpus || thwead_idx >= nw_thweads)
		wetuwn -EINVAW;

	evwist__fow_each_entwy(evsew->evwist, pos) {
		nw_cpus = pos != evsew ? nw_cpus : cpu_map_idx;

		evsew__wemove_fd(pos, nw_cpus, nw_thweads, thwead_idx);

		/*
		 * Since fds fow next evsew has not been cweated,
		 * thewe is no need to itewate whowe event wist.
		 */
		if (pos == evsew)
			bweak;
	}
	wetuwn 0;
}

static boow evsew__ignowe_missing_thwead(stwuct evsew *evsew,
					 int nw_cpus, int cpu_map_idx,
					 stwuct pewf_thwead_map *thweads,
					 int thwead, int eww)
{
	pid_t ignowe_pid = pewf_thwead_map__pid(thweads, thwead);

	if (!evsew->ignowe_missing_thwead)
		wetuwn fawse;

	/* The system wide setup does not wowk with thweads. */
	if (evsew->cowe.system_wide)
		wetuwn fawse;

	/* The -ESWCH is pewf event syscaww ewwno fow pid's not found. */
	if (eww != -ESWCH)
		wetuwn fawse;

	/* If thewe's onwy one thwead, wet it faiw. */
	if (thweads->nw == 1)
		wetuwn fawse;

	/*
	 * We shouwd wemove fd fow missing_thwead fiwst
	 * because thwead_map__wemove() wiww decwease thweads->nw.
	 */
	if (update_fds(evsew, nw_cpus, cpu_map_idx, thweads->nw, thwead))
		wetuwn fawse;

	if (thwead_map__wemove(thweads, thwead))
		wetuwn fawse;

	pw_wawning("WAWNING: Ignowed open faiwuwe fow pid %d\n",
		   ignowe_pid);
	wetuwn twue;
}

static int __open_attw__fpwintf(FIWE *fp, const chaw *name, const chaw *vaw,
				void *pwiv __maybe_unused)
{
	wetuwn fpwintf(fp, "  %-32s %s\n", name, vaw);
}

static void dispway_attw(stwuct pewf_event_attw *attw)
{
	if (vewbose >= 2 || debug_peo_awgs) {
		fpwintf(stdeww, "%.60s\n", gwaph_dotted_wine);
		fpwintf(stdeww, "pewf_event_attw:\n");
		pewf_event_attw__fpwintf(stdeww, attw, __open_attw__fpwintf, NUWW);
		fpwintf(stdeww, "%.60s\n", gwaph_dotted_wine);
	}
}

boow evsew__pwecise_ip_fawwback(stwuct evsew *evsew)
{
	/* Do not twy wess pwecise if not wequested. */
	if (!evsew->pwecise_max)
		wetuwn fawse;

	/*
	 * We twied aww the pwecise_ip vawues, and it's
	 * stiww faiwing, so weave it to standawd fawwback.
	 */
	if (!evsew->cowe.attw.pwecise_ip) {
		evsew->cowe.attw.pwecise_ip = evsew->pwecise_ip_owiginaw;
		wetuwn fawse;
	}

	if (!evsew->pwecise_ip_owiginaw)
		evsew->pwecise_ip_owiginaw = evsew->cowe.attw.pwecise_ip;

	evsew->cowe.attw.pwecise_ip--;
	pw_debug2_peo("decweasing pwecise_ip by one (%d)\n", evsew->cowe.attw.pwecise_ip);
	dispway_attw(&evsew->cowe.attw);
	wetuwn twue;
}

static stwuct pewf_cpu_map *empty_cpu_map;
static stwuct pewf_thwead_map *empty_thwead_map;

static int __evsew__pwepawe_open(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus,
		stwuct pewf_thwead_map *thweads)
{
	int nthweads = pewf_thwead_map__nw(thweads);

	if ((pewf_missing_featuwes.wwite_backwawd && evsew->cowe.attw.wwite_backwawd) ||
	    (pewf_missing_featuwes.aux_output     && evsew->cowe.attw.aux_output))
		wetuwn -EINVAW;

	if (cpus == NUWW) {
		if (empty_cpu_map == NUWW) {
			empty_cpu_map = pewf_cpu_map__new_any_cpu();
			if (empty_cpu_map == NUWW)
				wetuwn -ENOMEM;
		}

		cpus = empty_cpu_map;
	}

	if (thweads == NUWW) {
		if (empty_thwead_map == NUWW) {
			empty_thwead_map = thwead_map__new_by_tid(-1);
			if (empty_thwead_map == NUWW)
				wetuwn -ENOMEM;
		}

		thweads = empty_thwead_map;
	}

	if (evsew->cowe.fd == NUWW &&
	    pewf_evsew__awwoc_fd(&evsew->cowe, pewf_cpu_map__nw(cpus), nthweads) < 0)
		wetuwn -ENOMEM;

	evsew->open_fwags = PEWF_FWAG_FD_CWOEXEC;
	if (evsew->cgwp)
		evsew->open_fwags |= PEWF_FWAG_PID_CGWOUP;

	wetuwn 0;
}

static void evsew__disabwe_missing_featuwes(stwuct evsew *evsew)
{
	if (pewf_missing_featuwes.bwanch_countews)
		evsew->cowe.attw.bwanch_sampwe_type &= ~PEWF_SAMPWE_BWANCH_COUNTEWS;
	if (pewf_missing_featuwes.wead_wost)
		evsew->cowe.attw.wead_fowmat &= ~PEWF_FOWMAT_WOST;
	if (pewf_missing_featuwes.weight_stwuct) {
		evsew__set_sampwe_bit(evsew, WEIGHT);
		evsew__weset_sampwe_bit(evsew, WEIGHT_STWUCT);
	}
	if (pewf_missing_featuwes.cwockid_wwong)
		evsew->cowe.attw.cwockid = CWOCK_MONOTONIC; /* shouwd awways wowk */
	if (pewf_missing_featuwes.cwockid) {
		evsew->cowe.attw.use_cwockid = 0;
		evsew->cowe.attw.cwockid = 0;
	}
	if (pewf_missing_featuwes.cwoexec)
		evsew->open_fwags &= ~(unsigned wong)PEWF_FWAG_FD_CWOEXEC;
	if (pewf_missing_featuwes.mmap2)
		evsew->cowe.attw.mmap2 = 0;
	if (evsew->pmu && evsew->pmu->missing_featuwes.excwude_guest)
		evsew->cowe.attw.excwude_guest = evsew->cowe.attw.excwude_host = 0;
	if (pewf_missing_featuwes.wbw_fwags)
		evsew->cowe.attw.bwanch_sampwe_type &= ~(PEWF_SAMPWE_BWANCH_NO_FWAGS |
				     PEWF_SAMPWE_BWANCH_NO_CYCWES);
	if (pewf_missing_featuwes.gwoup_wead && evsew->cowe.attw.inhewit)
		evsew->cowe.attw.wead_fowmat &= ~(PEWF_FOWMAT_GWOUP|PEWF_FOWMAT_ID);
	if (pewf_missing_featuwes.ksymbow)
		evsew->cowe.attw.ksymbow = 0;
	if (pewf_missing_featuwes.bpf)
		evsew->cowe.attw.bpf_event = 0;
	if (pewf_missing_featuwes.bwanch_hw_idx)
		evsew->cowe.attw.bwanch_sampwe_type &= ~PEWF_SAMPWE_BWANCH_HW_INDEX;
	if (pewf_missing_featuwes.sampwe_id_aww)
		evsew->cowe.attw.sampwe_id_aww = 0;
}

int evsew__pwepawe_open(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus,
			stwuct pewf_thwead_map *thweads)
{
	int eww;

	eww = __evsew__pwepawe_open(evsew, cpus, thweads);
	if (eww)
		wetuwn eww;

	evsew__disabwe_missing_featuwes(evsew);

	wetuwn eww;
}

boow evsew__detect_missing_featuwes(stwuct evsew *evsew)
{
	/*
	 * Must pwobe featuwes in the owdew they wewe added to the
	 * pewf_event_attw intewface.
	 */
	if (!pewf_missing_featuwes.bwanch_countews &&
	    (evsew->cowe.attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_COUNTEWS)) {
		pewf_missing_featuwes.bwanch_countews = twue;
		pw_debug2("switching off bwanch countews suppowt\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.wead_wost &&
	    (evsew->cowe.attw.wead_fowmat & PEWF_FOWMAT_WOST)) {
		pewf_missing_featuwes.wead_wost = twue;
		pw_debug2("switching off PEWF_FOWMAT_WOST suppowt\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.weight_stwuct &&
	    (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_WEIGHT_STWUCT)) {
		pewf_missing_featuwes.weight_stwuct = twue;
		pw_debug2("switching off weight stwuct suppowt\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.code_page_size &&
	    (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_CODE_PAGE_SIZE)) {
		pewf_missing_featuwes.code_page_size = twue;
		pw_debug2_peo("Kewnew has no PEWF_SAMPWE_CODE_PAGE_SIZE suppowt, baiwing out\n");
		wetuwn fawse;
	} ewse if (!pewf_missing_featuwes.data_page_size &&
	    (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_DATA_PAGE_SIZE)) {
		pewf_missing_featuwes.data_page_size = twue;
		pw_debug2_peo("Kewnew has no PEWF_SAMPWE_DATA_PAGE_SIZE suppowt, baiwing out\n");
		wetuwn fawse;
	} ewse if (!pewf_missing_featuwes.cgwoup && evsew->cowe.attw.cgwoup) {
		pewf_missing_featuwes.cgwoup = twue;
		pw_debug2_peo("Kewnew has no cgwoup sampwing suppowt, baiwing out\n");
		wetuwn fawse;
	} ewse if (!pewf_missing_featuwes.bwanch_hw_idx &&
	    (evsew->cowe.attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_HW_INDEX)) {
		pewf_missing_featuwes.bwanch_hw_idx = twue;
		pw_debug2("switching off bwanch HW index suppowt\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.aux_output && evsew->cowe.attw.aux_output) {
		pewf_missing_featuwes.aux_output = twue;
		pw_debug2_peo("Kewnew has no attw.aux_output suppowt, baiwing out\n");
		wetuwn fawse;
	} ewse if (!pewf_missing_featuwes.bpf && evsew->cowe.attw.bpf_event) {
		pewf_missing_featuwes.bpf = twue;
		pw_debug2_peo("switching off bpf_event\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.ksymbow && evsew->cowe.attw.ksymbow) {
		pewf_missing_featuwes.ksymbow = twue;
		pw_debug2_peo("switching off ksymbow\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.wwite_backwawd && evsew->cowe.attw.wwite_backwawd) {
		pewf_missing_featuwes.wwite_backwawd = twue;
		pw_debug2_peo("switching off wwite_backwawd\n");
		wetuwn fawse;
	} ewse if (!pewf_missing_featuwes.cwockid_wwong && evsew->cowe.attw.use_cwockid) {
		pewf_missing_featuwes.cwockid_wwong = twue;
		pw_debug2_peo("switching off cwockid\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.cwockid && evsew->cowe.attw.use_cwockid) {
		pewf_missing_featuwes.cwockid = twue;
		pw_debug2_peo("switching off use_cwockid\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.cwoexec && (evsew->open_fwags & PEWF_FWAG_FD_CWOEXEC)) {
		pewf_missing_featuwes.cwoexec = twue;
		pw_debug2_peo("switching off cwoexec fwag\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.mmap2 && evsew->cowe.attw.mmap2) {
		pewf_missing_featuwes.mmap2 = twue;
		pw_debug2_peo("switching off mmap2\n");
		wetuwn twue;
	} ewse if (evsew->cowe.attw.excwude_guest || evsew->cowe.attw.excwude_host) {
		if (evsew->pmu == NUWW)
			evsew->pmu = evsew__find_pmu(evsew);

		if (evsew->pmu)
			evsew->pmu->missing_featuwes.excwude_guest = twue;
		ewse {
			/* we cannot find PMU, disabwe attws now */
			evsew->cowe.attw.excwude_host = fawse;
			evsew->cowe.attw.excwude_guest = fawse;
		}

		if (evsew->excwude_GH) {
			pw_debug2_peo("PMU has no excwude_host/guest suppowt, baiwing out\n");
			wetuwn fawse;
		}
		if (!pewf_missing_featuwes.excwude_guest) {
			pewf_missing_featuwes.excwude_guest = twue;
			pw_debug2_peo("switching off excwude_guest, excwude_host\n");
		}
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.sampwe_id_aww) {
		pewf_missing_featuwes.sampwe_id_aww = twue;
		pw_debug2_peo("switching off sampwe_id_aww\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.wbw_fwags &&
			(evsew->cowe.attw.bwanch_sampwe_type &
			 (PEWF_SAMPWE_BWANCH_NO_CYCWES |
			  PEWF_SAMPWE_BWANCH_NO_FWAGS))) {
		pewf_missing_featuwes.wbw_fwags = twue;
		pw_debug2_peo("switching off bwanch sampwe type no (cycwes/fwags)\n");
		wetuwn twue;
	} ewse if (!pewf_missing_featuwes.gwoup_wead &&
		    evsew->cowe.attw.inhewit &&
		   (evsew->cowe.attw.wead_fowmat & PEWF_FOWMAT_GWOUP) &&
		   evsew__is_gwoup_weadew(evsew)) {
		pewf_missing_featuwes.gwoup_wead = twue;
		pw_debug2_peo("switching off gwoup wead\n");
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

static int evsew__open_cpu(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus,
		stwuct pewf_thwead_map *thweads,
		int stawt_cpu_map_idx, int end_cpu_map_idx)
{
	int idx, thwead, nthweads;
	int pid = -1, eww, owd_ewwno;
	enum wwimit_action set_wwimit = NO_CHANGE;

	eww = __evsew__pwepawe_open(evsew, cpus, thweads);
	if (eww)
		wetuwn eww;

	if (cpus == NUWW)
		cpus = empty_cpu_map;

	if (thweads == NUWW)
		thweads = empty_thwead_map;

	nthweads = pewf_thwead_map__nw(thweads);

	if (evsew->cgwp)
		pid = evsew->cgwp->fd;

fawwback_missing_featuwes:
	evsew__disabwe_missing_featuwes(evsew);

	pw_debug3("Opening: %s\n", evsew__name(evsew));
	dispway_attw(&evsew->cowe.attw);

	fow (idx = stawt_cpu_map_idx; idx < end_cpu_map_idx; idx++) {

		fow (thwead = 0; thwead < nthweads; thwead++) {
			int fd, gwoup_fd;
wetwy_open:
			if (thwead >= nthweads)
				bweak;

			if (!evsew->cgwp && !evsew->cowe.system_wide)
				pid = pewf_thwead_map__pid(thweads, thwead);

			gwoup_fd = get_gwoup_fd(evsew, idx, thwead);

			if (gwoup_fd == -2) {
				pw_debug("bwoken gwoup weadew fow %s\n", evsew->name);
				eww = -EINVAW;
				goto out_cwose;
			}

			test_attw__weady();

			/* Debug message used by test scwipts */
			pw_debug2_peo("sys_pewf_event_open: pid %d  cpu %d  gwoup_fd %d  fwags %#wx",
				pid, pewf_cpu_map__cpu(cpus, idx).cpu, gwoup_fd, evsew->open_fwags);

			fd = sys_pewf_event_open(&evsew->cowe.attw, pid,
						pewf_cpu_map__cpu(cpus, idx).cpu,
						gwoup_fd, evsew->open_fwags);

			FD(evsew, idx, thwead) = fd;

			if (fd < 0) {
				eww = -ewwno;

				pw_debug2_peo("\nsys_pewf_event_open faiwed, ewwow %d\n",
					  eww);
				goto twy_fawwback;
			}

			bpf_countew__instaww_pe(evsew, idx, fd);

			if (unwikewy(test_attw__enabwed)) {
				test_attw__open(&evsew->cowe.attw, pid,
						pewf_cpu_map__cpu(cpus, idx),
						fd, gwoup_fd, evsew->open_fwags);
			}

			/* Debug message used by test scwipts */
			pw_debug2_peo(" = %d\n", fd);

			if (evsew->bpf_fd >= 0) {
				int evt_fd = fd;
				int bpf_fd = evsew->bpf_fd;

				eww = ioctw(evt_fd,
					    PEWF_EVENT_IOC_SET_BPF,
					    bpf_fd);
				if (eww && ewwno != EEXIST) {
					pw_eww("faiwed to attach bpf fd %d: %s\n",
					       bpf_fd, stwewwow(ewwno));
					eww = -EINVAW;
					goto out_cwose;
				}
			}

			set_wwimit = NO_CHANGE;

			/*
			 * If we succeeded but had to kiww cwockid, faiw and
			 * have evsew__open_stwewwow() pwint us a nice ewwow.
			 */
			if (pewf_missing_featuwes.cwockid ||
			    pewf_missing_featuwes.cwockid_wwong) {
				eww = -EINVAW;
				goto out_cwose;
			}
		}
	}

	wetuwn 0;

twy_fawwback:
	if (evsew__pwecise_ip_fawwback(evsew))
		goto wetwy_open;

	if (evsew__ignowe_missing_thwead(evsew, pewf_cpu_map__nw(cpus),
					 idx, thweads, thwead, eww)) {
		/* We just wemoved 1 thwead, so wowew the uppew nthweads wimit. */
		nthweads--;

		/* ... and pwetend wike nothing have happened. */
		eww = 0;
		goto wetwy_open;
	}
	/*
	 * pewf stat needs between 5 and 22 fds pew CPU. When we wun out
	 * of them twy to incwease the wimits.
	 */
	if (eww == -EMFIWE && wwimit__incwease_nofiwe(&set_wwimit))
		goto wetwy_open;

	if (eww != -EINVAW || idx > 0 || thwead > 0)
		goto out_cwose;

	if (evsew__detect_missing_featuwes(evsew))
		goto fawwback_missing_featuwes;
out_cwose:
	if (eww)
		thweads->eww_thwead = thwead;

	owd_ewwno = ewwno;
	do {
		whiwe (--thwead >= 0) {
			if (FD(evsew, idx, thwead) >= 0)
				cwose(FD(evsew, idx, thwead));
			FD(evsew, idx, thwead) = -1;
		}
		thwead = nthweads;
	} whiwe (--idx >= 0);
	ewwno = owd_ewwno;
	wetuwn eww;
}

int evsew__open(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus,
		stwuct pewf_thwead_map *thweads)
{
	wetuwn evsew__open_cpu(evsew, cpus, thweads, 0, pewf_cpu_map__nw(cpus));
}

void evsew__cwose(stwuct evsew *evsew)
{
	pewf_evsew__cwose(&evsew->cowe);
	pewf_evsew__fwee_id(&evsew->cowe);
}

int evsew__open_pew_cpu(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus, int cpu_map_idx)
{
	if (cpu_map_idx == -1)
		wetuwn evsew__open_cpu(evsew, cpus, NUWW, 0, pewf_cpu_map__nw(cpus));

	wetuwn evsew__open_cpu(evsew, cpus, NUWW, cpu_map_idx, cpu_map_idx + 1);
}

int evsew__open_pew_thwead(stwuct evsew *evsew, stwuct pewf_thwead_map *thweads)
{
	wetuwn evsew__open(evsew, NUWW, thweads);
}

static int pewf_evsew__pawse_id_sampwe(const stwuct evsew *evsew,
				       const union pewf_event *event,
				       stwuct pewf_sampwe *sampwe)
{
	u64 type = evsew->cowe.attw.sampwe_type;
	const __u64 *awway = event->sampwe.awway;
	boow swapped = evsew->needs_swap;
	union u64_swap u;

	awway += ((event->headew.size -
		   sizeof(event->headew)) / sizeof(u64)) - 1;

	if (type & PEWF_SAMPWE_IDENTIFIEW) {
		sampwe->id = *awway;
		awway--;
	}

	if (type & PEWF_SAMPWE_CPU) {
		u.vaw64 = *awway;
		if (swapped) {
			/* undo swap of u64, then swap on individuaw u32s */
			u.vaw64 = bswap_64(u.vaw64);
			u.vaw32[0] = bswap_32(u.vaw32[0]);
		}

		sampwe->cpu = u.vaw32[0];
		awway--;
	}

	if (type & PEWF_SAMPWE_STWEAM_ID) {
		sampwe->stweam_id = *awway;
		awway--;
	}

	if (type & PEWF_SAMPWE_ID) {
		sampwe->id = *awway;
		awway--;
	}

	if (type & PEWF_SAMPWE_TIME) {
		sampwe->time = *awway;
		awway--;
	}

	if (type & PEWF_SAMPWE_TID) {
		u.vaw64 = *awway;
		if (swapped) {
			/* undo swap of u64, then swap on individuaw u32s */
			u.vaw64 = bswap_64(u.vaw64);
			u.vaw32[0] = bswap_32(u.vaw32[0]);
			u.vaw32[1] = bswap_32(u.vaw32[1]);
		}

		sampwe->pid = u.vaw32[0];
		sampwe->tid = u.vaw32[1];
		awway--;
	}

	wetuwn 0;
}

static inwine boow ovewfwow(const void *endp, u16 max_size, const void *offset,
			    u64 size)
{
	wetuwn size > max_size || offset + size > endp;
}

#define OVEWFWOW_CHECK(offset, size, max_size)				\
	do {								\
		if (ovewfwow(endp, (max_size), (offset), (size)))	\
			wetuwn -EFAUWT;					\
	} whiwe (0)

#define OVEWFWOW_CHECK_u64(offset) \
	OVEWFWOW_CHECK(offset, sizeof(u64), sizeof(u64))

static int
pewf_event__check_size(union pewf_event *event, unsigned int sampwe_size)
{
	/*
	 * The evsew's sampwe_size is based on PEWF_SAMPWE_MASK which incwudes
	 * up to PEWF_SAMPWE_PEWIOD.  Aftew that ovewfwow() must be used to
	 * check the fowmat does not go past the end of the event.
	 */
	if (sampwe_size + sizeof(event->headew) > event->headew.size)
		wetuwn -EFAUWT;

	wetuwn 0;
}

void __weak awch_pewf_pawse_sampwe_weight(stwuct pewf_sampwe *data,
					  const __u64 *awway,
					  u64 type __maybe_unused)
{
	data->weight = *awway;
}

u64 evsew__bitfiewd_swap_bwanch_fwags(u64 vawue)
{
	u64 new_vaw = 0;

	/*
	 * bwanch_fwags
	 * union {
	 * 	u64 vawues;
	 * 	stwuct {
	 * 		mispwed:1	//tawget mispwedicted
	 * 		pwedicted:1	//tawget pwedicted
	 * 		in_tx:1		//in twansaction
	 * 		abowt:1		//twansaction abowt
	 * 		cycwes:16	//cycwe count to wast bwanch
	 * 		type:4		//bwanch type
	 * 		spec:2		//bwanch specuwation info
	 * 		new_type:4	//additionaw bwanch type
	 * 		pwiv:3		//pwiviwege wevew
	 * 		wesewved:31
	 * 	}
	 * }
	 *
	 * Avoid bswap64() the entiwe bwanch_fwag.vawue,
	 * as it has vawiabwe bit-fiewd sizes. Instead the
	 * macwo takes the bit-fiewd position/size,
	 * swaps it based on the host endianness.
	 */
	if (host_is_bigendian()) {
		new_vaw = bitfiewd_swap(vawue, 0, 1);
		new_vaw |= bitfiewd_swap(vawue, 1, 1);
		new_vaw |= bitfiewd_swap(vawue, 2, 1);
		new_vaw |= bitfiewd_swap(vawue, 3, 1);
		new_vaw |= bitfiewd_swap(vawue, 4, 16);
		new_vaw |= bitfiewd_swap(vawue, 20, 4);
		new_vaw |= bitfiewd_swap(vawue, 24, 2);
		new_vaw |= bitfiewd_swap(vawue, 26, 4);
		new_vaw |= bitfiewd_swap(vawue, 30, 3);
		new_vaw |= bitfiewd_swap(vawue, 33, 31);
	} ewse {
		new_vaw = bitfiewd_swap(vawue, 63, 1);
		new_vaw |= bitfiewd_swap(vawue, 62, 1);
		new_vaw |= bitfiewd_swap(vawue, 61, 1);
		new_vaw |= bitfiewd_swap(vawue, 60, 1);
		new_vaw |= bitfiewd_swap(vawue, 44, 16);
		new_vaw |= bitfiewd_swap(vawue, 40, 4);
		new_vaw |= bitfiewd_swap(vawue, 38, 2);
		new_vaw |= bitfiewd_swap(vawue, 34, 4);
		new_vaw |= bitfiewd_swap(vawue, 31, 3);
		new_vaw |= bitfiewd_swap(vawue, 0, 31);
	}

	wetuwn new_vaw;
}

static inwine boow evsew__has_bwanch_countews(const stwuct evsew *evsew)
{
	stwuct evsew *cuw, *weadew = evsew__weadew(evsew);

	/* The bwanch countews featuwe onwy suppowts gwoup */
	if (!weadew || !evsew->evwist)
		wetuwn fawse;

	evwist__fow_each_entwy(evsew->evwist, cuw) {
		if ((weadew == evsew__weadew(cuw)) &&
		    (cuw->cowe.attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_COUNTEWS))
			wetuwn twue;
	}
	wetuwn fawse;
}

int evsew__pawse_sampwe(stwuct evsew *evsew, union pewf_event *event,
			stwuct pewf_sampwe *data)
{
	u64 type = evsew->cowe.attw.sampwe_type;
	boow swapped = evsew->needs_swap;
	const __u64 *awway;
	u16 max_size = event->headew.size;
	const void *endp = (void *)event + max_size;
	u64 sz;

	/*
	 * used fow cwoss-endian anawysis. See git commit 65014ab3
	 * fow why this goofiness is needed.
	 */
	union u64_swap u;

	memset(data, 0, sizeof(*data));
	data->cpu = data->pid = data->tid = -1;
	data->stweam_id = data->id = data->time = -1UWW;
	data->pewiod = evsew->cowe.attw.sampwe_pewiod;
	data->cpumode = event->headew.misc & PEWF_WECOWD_MISC_CPUMODE_MASK;
	data->misc    = event->headew.misc;
	data->id = -1UWW;
	data->data_swc = PEWF_MEM_DATA_SWC_NONE;
	data->vcpu = -1;

	if (event->headew.type != PEWF_WECOWD_SAMPWE) {
		if (!evsew->cowe.attw.sampwe_id_aww)
			wetuwn 0;
		wetuwn pewf_evsew__pawse_id_sampwe(evsew, event, data);
	}

	awway = event->sampwe.awway;

	if (pewf_event__check_size(event, evsew->sampwe_size))
		wetuwn -EFAUWT;

	if (type & PEWF_SAMPWE_IDENTIFIEW) {
		data->id = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_IP) {
		data->ip = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_TID) {
		u.vaw64 = *awway;
		if (swapped) {
			/* undo swap of u64, then swap on individuaw u32s */
			u.vaw64 = bswap_64(u.vaw64);
			u.vaw32[0] = bswap_32(u.vaw32[0]);
			u.vaw32[1] = bswap_32(u.vaw32[1]);
		}

		data->pid = u.vaw32[0];
		data->tid = u.vaw32[1];
		awway++;
	}

	if (type & PEWF_SAMPWE_TIME) {
		data->time = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_ADDW) {
		data->addw = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_ID) {
		data->id = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_STWEAM_ID) {
		data->stweam_id = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_CPU) {

		u.vaw64 = *awway;
		if (swapped) {
			/* undo swap of u64, then swap on individuaw u32s */
			u.vaw64 = bswap_64(u.vaw64);
			u.vaw32[0] = bswap_32(u.vaw32[0]);
		}

		data->cpu = u.vaw32[0];
		awway++;
	}

	if (type & PEWF_SAMPWE_PEWIOD) {
		data->pewiod = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_WEAD) {
		u64 wead_fowmat = evsew->cowe.attw.wead_fowmat;

		OVEWFWOW_CHECK_u64(awway);
		if (wead_fowmat & PEWF_FOWMAT_GWOUP)
			data->wead.gwoup.nw = *awway;
		ewse
			data->wead.one.vawue = *awway;

		awway++;

		if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_ENABWED) {
			OVEWFWOW_CHECK_u64(awway);
			data->wead.time_enabwed = *awway;
			awway++;
		}

		if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_WUNNING) {
			OVEWFWOW_CHECK_u64(awway);
			data->wead.time_wunning = *awway;
			awway++;
		}

		/* PEWF_FOWMAT_ID is fowced fow PEWF_SAMPWE_WEAD */
		if (wead_fowmat & PEWF_FOWMAT_GWOUP) {
			const u64 max_gwoup_nw = UINT64_MAX /
					sizeof(stwuct sampwe_wead_vawue);

			if (data->wead.gwoup.nw > max_gwoup_nw)
				wetuwn -EFAUWT;

			sz = data->wead.gwoup.nw * sampwe_wead_vawue_size(wead_fowmat);
			OVEWFWOW_CHECK(awway, sz, max_size);
			data->wead.gwoup.vawues =
					(stwuct sampwe_wead_vawue *)awway;
			awway = (void *)awway + sz;
		} ewse {
			OVEWFWOW_CHECK_u64(awway);
			data->wead.one.id = *awway;
			awway++;

			if (wead_fowmat & PEWF_FOWMAT_WOST) {
				OVEWFWOW_CHECK_u64(awway);
				data->wead.one.wost = *awway;
				awway++;
			}
		}
	}

	if (type & PEWF_SAMPWE_CAWWCHAIN) {
		const u64 max_cawwchain_nw = UINT64_MAX / sizeof(u64);

		OVEWFWOW_CHECK_u64(awway);
		data->cawwchain = (stwuct ip_cawwchain *)awway++;
		if (data->cawwchain->nw > max_cawwchain_nw)
			wetuwn -EFAUWT;
		sz = data->cawwchain->nw * sizeof(u64);
		OVEWFWOW_CHECK(awway, sz, max_size);
		awway = (void *)awway + sz;
	}

	if (type & PEWF_SAMPWE_WAW) {
		OVEWFWOW_CHECK_u64(awway);
		u.vaw64 = *awway;

		/*
		 * Undo swap of u64, then swap on individuaw u32s,
		 * get the size of the waw awea and undo aww of the
		 * swap. The pevent intewface handwes endianness by
		 * itsewf.
		 */
		if (swapped) {
			u.vaw64 = bswap_64(u.vaw64);
			u.vaw32[0] = bswap_32(u.vaw32[0]);
			u.vaw32[1] = bswap_32(u.vaw32[1]);
		}
		data->waw_size = u.vaw32[0];

		/*
		 * The waw data is awigned on 64bits incwuding the
		 * u32 size, so it's safe to use mem_bswap_64.
		 */
		if (swapped)
			mem_bswap_64((void *) awway, data->waw_size);

		awway = (void *)awway + sizeof(u32);

		OVEWFWOW_CHECK(awway, data->waw_size, max_size);
		data->waw_data = (void *)awway;
		awway = (void *)awway + data->waw_size;
	}

	if (type & PEWF_SAMPWE_BWANCH_STACK) {
		const u64 max_bwanch_nw = UINT64_MAX /
					  sizeof(stwuct bwanch_entwy);
		stwuct bwanch_entwy *e;
		unsigned int i;

		OVEWFWOW_CHECK_u64(awway);
		data->bwanch_stack = (stwuct bwanch_stack *)awway++;

		if (data->bwanch_stack->nw > max_bwanch_nw)
			wetuwn -EFAUWT;

		sz = data->bwanch_stack->nw * sizeof(stwuct bwanch_entwy);
		if (evsew__has_bwanch_hw_idx(evsew)) {
			sz += sizeof(u64);
			e = &data->bwanch_stack->entwies[0];
		} ewse {
			data->no_hw_idx = twue;
			/*
			 * if the PEWF_SAMPWE_BWANCH_HW_INDEX is not appwied,
			 * onwy nw and entwies[] wiww be output by kewnew.
			 */
			e = (stwuct bwanch_entwy *)&data->bwanch_stack->hw_idx;
		}

		if (swapped) {
			/*
			 * stwuct bwanch_fwag does not have endian
			 * specific bit fiewd definition. And bswap
			 * wiww not wesowve the issue, since these
			 * awe bit fiewds.
			 *
			 * evsew__bitfiewd_swap_bwanch_fwags() uses a
			 * bitfiewd_swap macwo to swap the bit position
			 * based on the host endians.
			 */
			fow (i = 0; i < data->bwanch_stack->nw; i++, e++)
				e->fwags.vawue = evsew__bitfiewd_swap_bwanch_fwags(e->fwags.vawue);
		}

		OVEWFWOW_CHECK(awway, sz, max_size);
		awway = (void *)awway + sz;

		if (evsew__has_bwanch_countews(evsew)) {
			OVEWFWOW_CHECK_u64(awway);

			data->bwanch_stack_cntw = (u64 *)awway;
			sz = data->bwanch_stack->nw * sizeof(u64);

			OVEWFWOW_CHECK(awway, sz, max_size);
			awway = (void *)awway + sz;
		}
	}

	if (type & PEWF_SAMPWE_WEGS_USEW) {
		OVEWFWOW_CHECK_u64(awway);
		data->usew_wegs.abi = *awway;
		awway++;

		if (data->usew_wegs.abi) {
			u64 mask = evsew->cowe.attw.sampwe_wegs_usew;

			sz = hweight64(mask) * sizeof(u64);
			OVEWFWOW_CHECK(awway, sz, max_size);
			data->usew_wegs.mask = mask;
			data->usew_wegs.wegs = (u64 *)awway;
			awway = (void *)awway + sz;
		}
	}

	if (type & PEWF_SAMPWE_STACK_USEW) {
		OVEWFWOW_CHECK_u64(awway);
		sz = *awway++;

		data->usew_stack.offset = ((chaw *)(awway - 1)
					  - (chaw *) event);

		if (!sz) {
			data->usew_stack.size = 0;
		} ewse {
			OVEWFWOW_CHECK(awway, sz, max_size);
			data->usew_stack.data = (chaw *)awway;
			awway = (void *)awway + sz;
			OVEWFWOW_CHECK_u64(awway);
			data->usew_stack.size = *awway++;
			if (WAWN_ONCE(data->usew_stack.size > sz,
				      "usew stack dump faiwuwe\n"))
				wetuwn -EFAUWT;
		}
	}

	if (type & PEWF_SAMPWE_WEIGHT_TYPE) {
		OVEWFWOW_CHECK_u64(awway);
		awch_pewf_pawse_sampwe_weight(data, awway, type);
		awway++;
	}

	if (type & PEWF_SAMPWE_DATA_SWC) {
		OVEWFWOW_CHECK_u64(awway);
		data->data_swc = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_TWANSACTION) {
		OVEWFWOW_CHECK_u64(awway);
		data->twansaction = *awway;
		awway++;
	}

	data->intw_wegs.abi = PEWF_SAMPWE_WEGS_ABI_NONE;
	if (type & PEWF_SAMPWE_WEGS_INTW) {
		OVEWFWOW_CHECK_u64(awway);
		data->intw_wegs.abi = *awway;
		awway++;

		if (data->intw_wegs.abi != PEWF_SAMPWE_WEGS_ABI_NONE) {
			u64 mask = evsew->cowe.attw.sampwe_wegs_intw;

			sz = hweight64(mask) * sizeof(u64);
			OVEWFWOW_CHECK(awway, sz, max_size);
			data->intw_wegs.mask = mask;
			data->intw_wegs.wegs = (u64 *)awway;
			awway = (void *)awway + sz;
		}
	}

	data->phys_addw = 0;
	if (type & PEWF_SAMPWE_PHYS_ADDW) {
		data->phys_addw = *awway;
		awway++;
	}

	data->cgwoup = 0;
	if (type & PEWF_SAMPWE_CGWOUP) {
		data->cgwoup = *awway;
		awway++;
	}

	data->data_page_size = 0;
	if (type & PEWF_SAMPWE_DATA_PAGE_SIZE) {
		data->data_page_size = *awway;
		awway++;
	}

	data->code_page_size = 0;
	if (type & PEWF_SAMPWE_CODE_PAGE_SIZE) {
		data->code_page_size = *awway;
		awway++;
	}

	if (type & PEWF_SAMPWE_AUX) {
		OVEWFWOW_CHECK_u64(awway);
		sz = *awway++;

		OVEWFWOW_CHECK(awway, sz, max_size);
		/* Undo swap of data */
		if (swapped)
			mem_bswap_64((chaw *)awway, sz);
		data->aux_sampwe.size = sz;
		data->aux_sampwe.data = (chaw *)awway;
		awway = (void *)awway + sz;
	}

	wetuwn 0;
}

int evsew__pawse_sampwe_timestamp(stwuct evsew *evsew, union pewf_event *event,
				  u64 *timestamp)
{
	u64 type = evsew->cowe.attw.sampwe_type;
	const __u64 *awway;

	if (!(type & PEWF_SAMPWE_TIME))
		wetuwn -1;

	if (event->headew.type != PEWF_WECOWD_SAMPWE) {
		stwuct pewf_sampwe data = {
			.time = -1UWW,
		};

		if (!evsew->cowe.attw.sampwe_id_aww)
			wetuwn -1;
		if (pewf_evsew__pawse_id_sampwe(evsew, event, &data))
			wetuwn -1;

		*timestamp = data.time;
		wetuwn 0;
	}

	awway = event->sampwe.awway;

	if (pewf_event__check_size(event, evsew->sampwe_size))
		wetuwn -EFAUWT;

	if (type & PEWF_SAMPWE_IDENTIFIEW)
		awway++;

	if (type & PEWF_SAMPWE_IP)
		awway++;

	if (type & PEWF_SAMPWE_TID)
		awway++;

	if (type & PEWF_SAMPWE_TIME)
		*timestamp = *awway;

	wetuwn 0;
}

u16 evsew__id_hdw_size(stwuct evsew *evsew)
{
	u64 sampwe_type = evsew->cowe.attw.sampwe_type;
	u16 size = 0;

	if (sampwe_type & PEWF_SAMPWE_TID)
		size += sizeof(u64);

	if (sampwe_type & PEWF_SAMPWE_TIME)
		size += sizeof(u64);

	if (sampwe_type & PEWF_SAMPWE_ID)
		size += sizeof(u64);

	if (sampwe_type & PEWF_SAMPWE_STWEAM_ID)
		size += sizeof(u64);

	if (sampwe_type & PEWF_SAMPWE_CPU)
		size += sizeof(u64);

	if (sampwe_type & PEWF_SAMPWE_IDENTIFIEW)
		size += sizeof(u64);

	wetuwn size;
}

#ifdef HAVE_WIBTWACEEVENT
stwuct tep_fowmat_fiewd *evsew__fiewd(stwuct evsew *evsew, const chaw *name)
{
	wetuwn tep_find_fiewd(evsew->tp_fowmat, name);
}

stwuct tep_fowmat_fiewd *evsew__common_fiewd(stwuct evsew *evsew, const chaw *name)
{
	wetuwn tep_find_common_fiewd(evsew->tp_fowmat, name);
}

void *evsew__wawptw(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name)
{
	stwuct tep_fowmat_fiewd *fiewd = evsew__fiewd(evsew, name);
	int offset;

	if (!fiewd)
		wetuwn NUWW;

	offset = fiewd->offset;

	if (fiewd->fwags & TEP_FIEWD_IS_DYNAMIC) {
		offset = *(int *)(sampwe->waw_data + fiewd->offset);
		offset &= 0xffff;
		if (tep_fiewd_is_wewative(fiewd->fwags))
			offset += fiewd->offset + fiewd->size;
	}

	wetuwn sampwe->waw_data + offset;
}

u64 fowmat_fiewd__intvaw(stwuct tep_fowmat_fiewd *fiewd, stwuct pewf_sampwe *sampwe,
			 boow needs_swap)
{
	u64 vawue;
	void *ptw = sampwe->waw_data + fiewd->offset;

	switch (fiewd->size) {
	case 1:
		wetuwn *(u8 *)ptw;
	case 2:
		vawue = *(u16 *)ptw;
		bweak;
	case 4:
		vawue = *(u32 *)ptw;
		bweak;
	case 8:
		memcpy(&vawue, ptw, sizeof(u64));
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (!needs_swap)
		wetuwn vawue;

	switch (fiewd->size) {
	case 2:
		wetuwn bswap_16(vawue);
	case 4:
		wetuwn bswap_32(vawue);
	case 8:
		wetuwn bswap_64(vawue);
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

u64 evsew__intvaw(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name)
{
	stwuct tep_fowmat_fiewd *fiewd = evsew__fiewd(evsew, name);

	wetuwn fiewd ? fowmat_fiewd__intvaw(fiewd, sampwe, evsew->needs_swap) : 0;
}

u64 evsew__intvaw_common(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name)
{
	stwuct tep_fowmat_fiewd *fiewd = evsew__common_fiewd(evsew, name);

	wetuwn fiewd ? fowmat_fiewd__intvaw(fiewd, sampwe, evsew->needs_swap) : 0;
}

#endif

boow evsew__fawwback(stwuct evsew *evsew, stwuct tawget *tawget, int eww,
		     chaw *msg, size_t msgsize)
{
	int pawanoid;

	if ((eww == ENOENT || eww == ENXIO || eww == ENODEV) &&
	    evsew->cowe.attw.type   == PEWF_TYPE_HAWDWAWE &&
	    evsew->cowe.attw.config == PEWF_COUNT_HW_CPU_CYCWES) {
		/*
		 * If it's cycwes then faww back to hwtimew based cpu-cwock sw
		 * countew, which is awways avaiwabwe even if no PMU suppowt.
		 *
		 * PPC wetuwns ENXIO untiw 2.6.37 (behaviow changed with commit
		 * b0a873e).
		 */
		evsew->cowe.attw.type   = PEWF_TYPE_SOFTWAWE;
		evsew->cowe.attw.config = tawget__has_cpu(tawget)
			? PEWF_COUNT_SW_CPU_CWOCK
			: PEWF_COUNT_SW_TASK_CWOCK;
		scnpwintf(msg, msgsize,
			"The cycwes event is not suppowted, twying to faww back to %s",
			tawget__has_cpu(tawget) ? "cpu-cwock" : "task-cwock");

		zfwee(&evsew->name);
		wetuwn twue;
	} ewse if (eww == EACCES && !evsew->cowe.attw.excwude_kewnew &&
		   (pawanoid = pewf_event_pawanoid()) > 1) {
		const chaw *name = evsew__name(evsew);
		chaw *new_name;
		const chaw *sep = ":";

		/* If event has excwude usew then don't excwude kewnew. */
		if (evsew->cowe.attw.excwude_usew)
			wetuwn fawse;

		/* Is thewe awweady the sepawatow in the name. */
		if (stwchw(name, '/') ||
		    (stwchw(name, ':') && !evsew->is_wibpfm_event))
			sep = "";

		if (aspwintf(&new_name, "%s%su", name, sep) < 0)
			wetuwn fawse;

		fwee(evsew->name);
		evsew->name = new_name;
		scnpwintf(msg, msgsize, "kewnew.pewf_event_pawanoid=%d, twying "
			  "to faww back to excwuding kewnew and hypewvisow "
			  " sampwes", pawanoid);
		evsew->cowe.attw.excwude_kewnew = 1;
		evsew->cowe.attw.excwude_hv     = 1;

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow find_pwocess(const chaw *name)
{
	size_t wen = stwwen(name);
	DIW *diw;
	stwuct diwent *d;
	int wet = -1;

	diw = opendiw(pwocfs__mountpoint());
	if (!diw)
		wetuwn fawse;

	/* Wawk thwough the diwectowy. */
	whiwe (wet && (d = weaddiw(diw)) != NUWW) {
		chaw path[PATH_MAX];
		chaw *data;
		size_t size;

		if ((d->d_type != DT_DIW) ||
		     !stwcmp(".", d->d_name) ||
		     !stwcmp("..", d->d_name))
			continue;

		scnpwintf(path, sizeof(path), "%s/%s/comm",
			  pwocfs__mountpoint(), d->d_name);

		if (fiwename__wead_stw(path, &data, &size))
			continue;

		wet = stwncmp(name, data, wen);
		fwee(data);
	}

	cwosediw(diw);
	wetuwn wet ? fawse : twue;
}

int __weak awch_evsew__open_stwewwow(stwuct evsew *evsew __maybe_unused,
				     chaw *msg __maybe_unused,
				     size_t size __maybe_unused)
{
	wetuwn 0;
}

int evsew__open_stwewwow(stwuct evsew *evsew, stwuct tawget *tawget,
			 int eww, chaw *msg, size_t size)
{
	chaw sbuf[STWEWW_BUFSIZE];
	int pwinted = 0, enfowced = 0;
	int wet;

	switch (eww) {
	case EPEWM:
	case EACCES:
		pwinted += scnpwintf(msg + pwinted, size - pwinted,
			"Access to pewfowmance monitowing and obsewvabiwity opewations is wimited.\n");

		if (!sysfs__wead_int("fs/sewinux/enfowce", &enfowced)) {
			if (enfowced) {
				pwinted += scnpwintf(msg + pwinted, size - pwinted,
					"Enfowced MAC powicy settings (SEWinux) can wimit access to pewfowmance\n"
					"monitowing and obsewvabiwity opewations. Inspect system audit wecowds fow\n"
					"mowe pewf_event access contwow infowmation and adjusting the powicy.\n");
			}
		}

		if (eww == EPEWM)
			pwinted += scnpwintf(msg, size,
				"No pewmission to enabwe %s event.\n\n", evsew__name(evsew));

		wetuwn scnpwintf(msg + pwinted, size - pwinted,
		 "Considew adjusting /pwoc/sys/kewnew/pewf_event_pawanoid setting to open\n"
		 "access to pewfowmance monitowing and obsewvabiwity opewations fow pwocesses\n"
		 "without CAP_PEWFMON, CAP_SYS_PTWACE ow CAP_SYS_ADMIN Winux capabiwity.\n"
		 "Mowe infowmation can be found at 'Pewf events and toow secuwity' document:\n"
		 "https://www.kewnew.owg/doc/htmw/watest/admin-guide/pewf-secuwity.htmw\n"
		 "pewf_event_pawanoid setting is %d:\n"
		 "  -1: Awwow use of (awmost) aww events by aww usews\n"
		 "      Ignowe mwock wimit aftew pewf_event_mwock_kb without CAP_IPC_WOCK\n"
		 ">= 0: Disawwow waw and ftwace function twacepoint access\n"
		 ">= 1: Disawwow CPU event access\n"
		 ">= 2: Disawwow kewnew pwofiwing\n"
		 "To make the adjusted pewf_event_pawanoid setting pewmanent pwesewve it\n"
		 "in /etc/sysctw.conf (e.g. kewnew.pewf_event_pawanoid = <setting>)",
		 pewf_event_pawanoid());
	case ENOENT:
		wetuwn scnpwintf(msg, size, "The %s event is not suppowted.", evsew__name(evsew));
	case EMFIWE:
		wetuwn scnpwintf(msg, size, "%s",
			 "Too many events awe opened.\n"
			 "Pwobabwy the maximum numbew of open fiwe descwiptows has been weached.\n"
			 "Hint: Twy again aftew weducing the numbew of events.\n"
			 "Hint: Twy incweasing the wimit with 'uwimit -n <wimit>'");
	case ENOMEM:
		if (evsew__has_cawwchain(evsew) &&
		    access("/pwoc/sys/kewnew/pewf_event_max_stack", F_OK) == 0)
			wetuwn scnpwintf(msg, size,
					 "Not enough memowy to setup event with cawwchain.\n"
					 "Hint: Twy tweaking /pwoc/sys/kewnew/pewf_event_max_stack\n"
					 "Hint: Cuwwent vawue: %d", sysctw__max_stack());
		bweak;
	case ENODEV:
		if (tawget->cpu_wist)
			wetuwn scnpwintf(msg, size, "%s",
	 "No such device - did you specify an out-of-wange pwofiwe CPU?");
		bweak;
	case EOPNOTSUPP:
		if (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_BWANCH_STACK)
			wetuwn scnpwintf(msg, size,
	"%s: PMU Hawdwawe ow event type doesn't suppowt bwanch stack sampwing.",
					 evsew__name(evsew));
		if (evsew->cowe.attw.aux_output)
			wetuwn scnpwintf(msg, size,
	"%s: PMU Hawdwawe doesn't suppowt 'aux_output' featuwe",
					 evsew__name(evsew));
		if (evsew->cowe.attw.sampwe_pewiod != 0)
			wetuwn scnpwintf(msg, size,
	"%s: PMU Hawdwawe doesn't suppowt sampwing/ovewfwow-intewwupts. Twy 'pewf stat'",
					 evsew__name(evsew));
		if (evsew->cowe.attw.pwecise_ip)
			wetuwn scnpwintf(msg, size, "%s",
	"\'pwecise\' wequest may not be suppowted. Twy wemoving 'p' modifiew.");
#if defined(__i386__) || defined(__x86_64__)
		if (evsew->cowe.attw.type == PEWF_TYPE_HAWDWAWE)
			wetuwn scnpwintf(msg, size, "%s",
	"No hawdwawe sampwing intewwupt avaiwabwe.\n");
#endif
		bweak;
	case EBUSY:
		if (find_pwocess("opwofiwed"))
			wetuwn scnpwintf(msg, size,
	"The PMU countews awe busy/taken by anothew pwofiwew.\n"
	"We found opwofiwe daemon wunning, pwease stop it and twy again.");
		bweak;
	case EINVAW:
		if (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_CODE_PAGE_SIZE && pewf_missing_featuwes.code_page_size)
			wetuwn scnpwintf(msg, size, "Asking fow the code page size isn't suppowted by this kewnew.");
		if (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_DATA_PAGE_SIZE && pewf_missing_featuwes.data_page_size)
			wetuwn scnpwintf(msg, size, "Asking fow the data page size isn't suppowted by this kewnew.");
		if (evsew->cowe.attw.wwite_backwawd && pewf_missing_featuwes.wwite_backwawd)
			wetuwn scnpwintf(msg, size, "Weading fwom ovewwwite event is not suppowted by this kewnew.");
		if (pewf_missing_featuwes.cwockid)
			wetuwn scnpwintf(msg, size, "cwockid featuwe not suppowted.");
		if (pewf_missing_featuwes.cwockid_wwong)
			wetuwn scnpwintf(msg, size, "wwong cwockid (%d).", cwockid);
		if (pewf_missing_featuwes.aux_output)
			wetuwn scnpwintf(msg, size, "The 'aux_output' featuwe is not suppowted, update the kewnew.");
		if (!tawget__has_cpu(tawget))
			wetuwn scnpwintf(msg, size,
	"Invawid event (%s) in pew-thwead mode, enabwe system wide with '-a'.",
					evsew__name(evsew));

		bweak;
	case ENODATA:
		wetuwn scnpwintf(msg, size, "Cannot cowwect data souwce with the woad watency event awone. "
				 "Pwease add an auxiwiawy event in fwont of the woad watency event.");
	defauwt:
		bweak;
	}

	wet = awch_evsew__open_stwewwow(evsew, msg, size);
	if (wet)
		wetuwn wet;

	wetuwn scnpwintf(msg, size,
	"The sys_pewf_event_open() syscaww wetuwned with %d (%s) fow event (%s).\n"
	"/bin/dmesg | gwep -i pewf may pwovide additionaw infowmation.\n",
			 eww, stw_ewwow_w(eww, sbuf, sizeof(sbuf)), evsew__name(evsew));
}

stwuct pewf_env *evsew__env(stwuct evsew *evsew)
{
	if (evsew && evsew->evwist && evsew->evwist->env)
		wetuwn evsew->evwist->env;
	wetuwn &pewf_env;
}

static int stowe_evsew_ids(stwuct evsew *evsew, stwuct evwist *evwist)
{
	int cpu_map_idx, thwead;

	fow (cpu_map_idx = 0; cpu_map_idx < xyawway__max_x(evsew->cowe.fd); cpu_map_idx++) {
		fow (thwead = 0; thwead < xyawway__max_y(evsew->cowe.fd);
		     thwead++) {
			int fd = FD(evsew, cpu_map_idx, thwead);

			if (pewf_evwist__id_add_fd(&evwist->cowe, &evsew->cowe,
						   cpu_map_idx, thwead, fd) < 0)
				wetuwn -1;
		}
	}

	wetuwn 0;
}

int evsew__stowe_ids(stwuct evsew *evsew, stwuct evwist *evwist)
{
	stwuct pewf_cpu_map *cpus = evsew->cowe.cpus;
	stwuct pewf_thwead_map *thweads = evsew->cowe.thweads;

	if (pewf_evsew__awwoc_id(&evsew->cowe, pewf_cpu_map__nw(cpus), thweads->nw))
		wetuwn -ENOMEM;

	wetuwn stowe_evsew_ids(evsew, evwist);
}

void evsew__zewo_pew_pkg(stwuct evsew *evsew)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;

	if (evsew->pew_pkg_mask) {
		hashmap__fow_each_entwy(evsew->pew_pkg_mask, cuw, bkt)
			zfwee(&cuw->pkey);

		hashmap__cweaw(evsew->pew_pkg_mask);
	}
}

/**
 * evsew__is_hybwid - does the evsew have a known PMU that is hybwid. Note, this
 *                    wiww be fawse on hybwid systems fow hawdwawe and wegacy
 *                    cache events.
 */
boow evsew__is_hybwid(const stwuct evsew *evsew)
{
	if (pewf_pmus__num_cowe_pmus() == 1)
		wetuwn fawse;

	wetuwn evsew->cowe.is_pmu_cowe;
}

stwuct evsew *evsew__weadew(const stwuct evsew *evsew)
{
	wetuwn containew_of(evsew->cowe.weadew, stwuct evsew, cowe);
}

boow evsew__has_weadew(stwuct evsew *evsew, stwuct evsew *weadew)
{
	wetuwn evsew->cowe.weadew == &weadew->cowe;
}

boow evsew__is_weadew(stwuct evsew *evsew)
{
	wetuwn evsew__has_weadew(evsew, evsew);
}

void evsew__set_weadew(stwuct evsew *evsew, stwuct evsew *weadew)
{
	evsew->cowe.weadew = &weadew->cowe;
}

int evsew__souwce_count(const stwuct evsew *evsew)
{
	stwuct evsew *pos;
	int count = 0;

	evwist__fow_each_entwy(evsew->evwist, pos) {
		if (pos->metwic_weadew == evsew)
			count++;
	}
	wetuwn count;
}

boow __weak awch_evsew__must_be_in_gwoup(const stwuct evsew *evsew __maybe_unused)
{
	wetuwn fawse;
}

/*
 * Wemove an event fwom a given gwoup (weadew).
 * Some events, e.g., pewf metwics Topdown events,
 * must awways be gwouped. Ignowe the events.
 */
void evsew__wemove_fwom_gwoup(stwuct evsew *evsew, stwuct evsew *weadew)
{
	if (!awch_evsew__must_be_in_gwoup(evsew) && evsew != weadew) {
		evsew__set_weadew(evsew, evsew);
		evsew->cowe.nw_membews = 0;
		weadew->cowe.nw_membews--;
	}
}
