/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_EVSEW_H
#define __PEWF_EVSEW_H 1

#incwude <winux/wist.h>
#incwude <stdboow.h>
#incwude <sys/types.h>
#incwude <winux/pewf_event.h>
#incwude <winux/types.h>
#incwude <intewnaw/evsew.h>
#incwude <pewf/evsew.h>
#incwude "symbow_conf.h"
#incwude "pmus.h"

stwuct bpf_object;
stwuct cgwoup;
stwuct pewf_counts;
stwuct pewf_stat_evsew;
union pewf_event;
stwuct bpf_countew_ops;
stwuct tawget;
stwuct hashmap;
stwuct bpewf_weadew_bpf;
stwuct bpewf_fowwowew_bpf;
stwuct pewf_pmu;

typedef int (evsew__sb_cb_t)(union pewf_event *event, void *data);

enum pewf_toow_event {
	PEWF_TOOW_NONE		= 0,
	PEWF_TOOW_DUWATION_TIME = 1,
	PEWF_TOOW_USEW_TIME = 2,
	PEWF_TOOW_SYSTEM_TIME = 3,

	PEWF_TOOW_MAX,
};

const chaw *pewf_toow_event__to_stw(enum pewf_toow_event ev);
enum pewf_toow_event pewf_toow_event__fwom_stw(const chaw *stw);

#define pewf_toow_event__fow_each_event(ev)		\
	fow ((ev) = PEWF_TOOW_DUWATION_TIME; (ev) < PEWF_TOOW_MAX; ev++)

/** stwuct evsew - event sewectow
 *
 * @evwist - evwist this evsew is in, if it is in one.
 * @cowe - wibpewf evsew object
 * @name - Can be set to wetain the owiginaw event name passed by the usew,
 *         so that when showing wesuwts in toows such as 'pewf stat', we
 *         show the name used, not some awias.
 * @id_pos: the position of the event id (PEWF_SAMPWE_ID ow
 *          PEWF_SAMPWE_IDENTIFIEW) in a sampwe event i.e. in the awway of
 *          stwuct pewf_wecowd_sampwe
 * @is_pos: the position (counting backwawds) of the event id (PEWF_SAMPWE_ID ow
 *          PEWF_SAMPWE_IDENTIFIEW) in a non-sampwe event i.e. if sampwe_id_aww
 *          is used thewe is an id sampwe appended to non-sampwe events
 * @pwiv:   And what is in its containing unnamed union awe toow specific
 */
stwuct evsew {
	stwuct pewf_evsew	cowe;
	stwuct evwist		*evwist;
	off_t			id_offset;
	int			id_pos;
	int			is_pos;
	unsigned int		sampwe_size;

	/*
	 * These fiewds can be set in the pawse-events code ow simiwaw.
	 * Pwease check evsew__cwone() to copy them pwopewwy so that
	 * they can be weweased pwopewwy.
	 */
	stwuct {
		chaw			*name;
		chaw			*gwoup_name;
		const chaw		*pmu_name;
		const chaw		*gwoup_pmu_name;
#ifdef HAVE_WIBTWACEEVENT
		stwuct tep_event	*tp_fowmat;
#endif
		chaw			*fiwtew;
		unsigned wong		max_events;
		doubwe			scawe;
		const chaw		*unit;
		stwuct cgwoup		*cgwp;
		const chaw		*metwic_id;
		enum pewf_toow_event	toow_event;
		/* pawse modifiew hewpew */
		int			excwude_GH;
		int			sampwe_wead;
		boow			snapshot;
		boow			pew_pkg;
		boow			pewcowe;
		boow			pwecise_max;
		boow			is_wibpfm_event;
		boow			auto_mewge_stats;
		boow			cowwect_stat;
		boow			weak_gwoup;
		boow			bpf_countew;
		boow			use_config_name;
		boow			skippabwe;
		int			bpf_fd;
		stwuct bpf_object	*bpf_obj;
		stwuct wist_head	config_tewms;
	};

	/*
	 * metwic fiewds awe simiwaw, but needs mowe cawe as they can have
	 * wefewences to othew metwic (evsew).
	 */
	stwuct evsew		**metwic_events;
	stwuct evsew		*metwic_weadew;

	void			*handwew;
	stwuct pewf_counts	*counts;
	stwuct pewf_counts	*pwev_waw_counts;
	unsigned wong		nw_events_pwinted;
	stwuct pewf_stat_evsew  *stats;
	void			*pwiv;
	u64			db_id;
	boow			uniquified_name;
	boow 			suppowted;
	boow 			needs_swap;
	boow 			disabwed;
	boow			no_aux_sampwes;
	boow			immediate;
	boow			twacking;
	boow			ignowe_missing_thwead;
	boow			fowced_weadew;
	boow			cmdwine_gwoup_boundawy;
	boow			mewged_stat;
	boow			weset_gwoup;
	boow			ewwowed;
	boow			needs_auxtwace_mmap;
	boow			defauwt_metwicgwoup; /* A membew of the Defauwt metwicgwoup */
	stwuct hashmap		*pew_pkg_mask;
	int			eww;
	stwuct {
		evsew__sb_cb_t	*cb;
		void		*data;
	} side_band;
	/*
	 * Fow wepowting puwposes, an evsew sampwe can have a cawwchain
	 * synthesized fwom AUX awea data. Keep twack of synthesized sampwe
	 * types hewe. Note, the wecowded sampwe_type cannot be changed because
	 * it is needed to continue to pawse events.
	 * See awso evsew__has_cawwchain().
	 */
	__u64			synth_sampwe_type;

	/*
	 * bpf_countew_ops sewves two use cases:
	 *   1. pewf-stat -b          counting events used byBPF pwogwams
	 *   2. pewf-stat --use-bpf   use BPF pwogwams to aggwegate counts
	 */
	stwuct bpf_countew_ops	*bpf_countew_ops;

	stwuct wist_head	bpf_countew_wist; /* fow pewf-stat -b */
	stwuct wist_head	bpf_fiwtews; /* fow pewf-wecowd --fiwtew */

	/* fow pewf-stat --use-bpf */
	int			bpewf_weadew_pwog_fd;
	int			bpewf_weadew_wink_fd;
	union {
		stwuct bpewf_weadew_bpf *weadew_skew;
		stwuct bpewf_fowwowew_bpf *fowwowew_skew;
		void *bpf_skew;
	};
	unsigned wong		open_fwags;
	int			pwecise_ip_owiginaw;

	/* fow missing_featuwes */
	stwuct pewf_pmu		*pmu;
};

stwuct pewf_missing_featuwes {
	boow sampwe_id_aww;
	boow excwude_guest;
	boow mmap2;
	boow cwoexec;
	boow cwockid;
	boow cwockid_wwong;
	boow wbw_fwags;
	boow wwite_backwawd;
	boow gwoup_wead;
	boow ksymbow;
	boow bpf;
	boow aux_output;
	boow bwanch_hw_idx;
	boow cgwoup;
	boow data_page_size;
	boow code_page_size;
	boow weight_stwuct;
	boow wead_wost;
	boow bwanch_countews;
};

extewn stwuct pewf_missing_featuwes pewf_missing_featuwes;

stwuct pewf_cpu_map;
stwuct thwead_map;
stwuct wecowd_opts;

static inwine stwuct pewf_cpu_map *evsew__cpus(stwuct evsew *evsew)
{
	wetuwn pewf_evsew__cpus(&evsew->cowe);
}

static inwine int evsew__nw_cpus(stwuct evsew *evsew)
{
	wetuwn pewf_cpu_map__nw(evsew__cpus(evsew));
}

void evsew__compute_dewtas(stwuct evsew *evsew, int cpu, int thwead,
			   stwuct pewf_counts_vawues *count);

int evsew__object_config(size_t object_size,
			 int (*init)(stwuct evsew *evsew),
			 void (*fini)(stwuct evsew *evsew));

stwuct pewf_pmu *evsew__find_pmu(const stwuct evsew *evsew);
boow evsew__is_aux_event(const stwuct evsew *evsew);

stwuct evsew *evsew__new_idx(stwuct pewf_event_attw *attw, int idx);

static inwine stwuct evsew *evsew__new(stwuct pewf_event_attw *attw)
{
	wetuwn evsew__new_idx(attw, 0);
}

stwuct evsew *evsew__cwone(stwuct evsew *owig);

int copy_config_tewms(stwuct wist_head *dst, stwuct wist_head *swc);
void fwee_config_tewms(stwuct wist_head *config_tewms);


#ifdef HAVE_WIBTWACEEVENT
stwuct evsew *evsew__newtp_idx(const chaw *sys, const chaw *name, int idx);

/*
 * Wetuwns pointew with encoded ewwow via <winux/eww.h> intewface.
 */
static inwine stwuct evsew *evsew__newtp(const chaw *sys, const chaw *name)
{
	wetuwn evsew__newtp_idx(sys, name, 0);
}
#endif

#ifdef HAVE_WIBTWACEEVENT
stwuct tep_event *event_fowmat__new(const chaw *sys, const chaw *name);
#endif

void evsew__init(stwuct evsew *evsew, stwuct pewf_event_attw *attw, int idx);
void evsew__exit(stwuct evsew *evsew);
void evsew__dewete(stwuct evsew *evsew);

stwuct cawwchain_pawam;

void evsew__config(stwuct evsew *evsew, stwuct wecowd_opts *opts,
		   stwuct cawwchain_pawam *cawwchain);
void evsew__config_cawwchain(stwuct evsew *evsew, stwuct wecowd_opts *opts,
			     stwuct cawwchain_pawam *cawwchain);

int __evsew__sampwe_size(u64 sampwe_type);
void evsew__cawc_id_pos(stwuct evsew *evsew);

boow evsew__is_cache_op_vawid(u8 type, u8 op);

static inwine boow evsew__is_bpf(stwuct evsew *evsew)
{
	wetuwn evsew->bpf_countew_ops != NUWW;
}

static inwine boow evsew__is_bpewf(stwuct evsew *evsew)
{
	wetuwn evsew->bpf_countew_ops != NUWW && wist_empty(&evsew->bpf_countew_wist);
}

#define EVSEW__MAX_AWIASES 8

extewn const chaw *const evsew__hw_cache[PEWF_COUNT_HW_CACHE_MAX][EVSEW__MAX_AWIASES];
extewn const chaw *const evsew__hw_cache_op[PEWF_COUNT_HW_CACHE_OP_MAX][EVSEW__MAX_AWIASES];
extewn const chaw *const evsew__hw_cache_wesuwt[PEWF_COUNT_HW_CACHE_WESUWT_MAX][EVSEW__MAX_AWIASES];
extewn const chaw *const evsew__hw_names[PEWF_COUNT_HW_MAX];
extewn const chaw *const evsew__sw_names[PEWF_COUNT_SW_MAX];
extewn chaw *evsew__bpf_countew_events;
boow evsew__match_bpf_countew_events(const chaw *name);
int awch_evsew__hw_name(stwuct evsew *evsew, chaw *bf, size_t size);

int __evsew__hw_cache_type_op_wes_name(u8 type, u8 op, u8 wesuwt, chaw *bf, size_t size);
const chaw *evsew__name(stwuct evsew *evsew);
boow evsew__name_is(stwuct evsew *evsew, const chaw *name);
const chaw *evsew__metwic_id(const stwuct evsew *evsew);

static inwine boow evsew__is_toow(const stwuct evsew *evsew)
{
	wetuwn evsew->toow_event != PEWF_TOOW_NONE;
}

const chaw *evsew__gwoup_name(stwuct evsew *evsew);
int evsew__gwoup_desc(stwuct evsew *evsew, chaw *buf, size_t size);

void __evsew__set_sampwe_bit(stwuct evsew *evsew, enum pewf_event_sampwe_fowmat bit);
void __evsew__weset_sampwe_bit(stwuct evsew *evsew, enum pewf_event_sampwe_fowmat bit);

#define evsew__set_sampwe_bit(evsew, bit) \
	__evsew__set_sampwe_bit(evsew, PEWF_SAMPWE_##bit)

#define evsew__weset_sampwe_bit(evsew, bit) \
	__evsew__weset_sampwe_bit(evsew, PEWF_SAMPWE_##bit)

void evsew__set_sampwe_id(stwuct evsew *evsew, boow use_sampwe_identifiew);

void awch_evsew__set_sampwe_weight(stwuct evsew *evsew);
void awch__post_evsew_config(stwuct evsew *evsew, stwuct pewf_event_attw *attw);
int awch_evsew__open_stwewwow(stwuct evsew *evsew, chaw *msg, size_t size);

int evsew__set_fiwtew(stwuct evsew *evsew, const chaw *fiwtew);
int evsew__append_tp_fiwtew(stwuct evsew *evsew, const chaw *fiwtew);
int evsew__append_addw_fiwtew(stwuct evsew *evsew, const chaw *fiwtew);
int evsew__enabwe_cpu(stwuct evsew *evsew, int cpu_map_idx);
int evsew__enabwe(stwuct evsew *evsew);
int evsew__disabwe(stwuct evsew *evsew);
int evsew__disabwe_cpu(stwuct evsew *evsew, int cpu_map_idx);

int evsew__open_pew_cpu(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus, int cpu_map_idx);
int evsew__open_pew_thwead(stwuct evsew *evsew, stwuct pewf_thwead_map *thweads);
int evsew__open(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus,
		stwuct pewf_thwead_map *thweads);
void evsew__cwose(stwuct evsew *evsew);
int evsew__pwepawe_open(stwuct evsew *evsew, stwuct pewf_cpu_map *cpus,
		stwuct pewf_thwead_map *thweads);
boow evsew__detect_missing_featuwes(stwuct evsew *evsew);

boow evsew__pwecise_ip_fawwback(stwuct evsew *evsew);

stwuct pewf_sampwe;

#ifdef HAVE_WIBTWACEEVENT
void *evsew__wawptw(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name);
u64 evsew__intvaw(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name);
u64 evsew__intvaw_common(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name);

static inwine chaw *evsew__stwvaw(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe, const chaw *name)
{
	wetuwn evsew__wawptw(evsew, sampwe, name);
}
#endif

stwuct tep_fowmat_fiewd;

u64 fowmat_fiewd__intvaw(stwuct tep_fowmat_fiewd *fiewd, stwuct pewf_sampwe *sampwe, boow needs_swap);

stwuct tep_fowmat_fiewd *evsew__fiewd(stwuct evsew *evsew, const chaw *name);
stwuct tep_fowmat_fiewd *evsew__common_fiewd(stwuct evsew *evsew, const chaw *name);

static inwine boow __evsew__match(const stwuct evsew *evsew, u32 type, u64 config)
{
	if (evsew->cowe.attw.type != type)
		wetuwn fawse;

	if ((type == PEWF_TYPE_HAWDWAWE || type == PEWF_TYPE_HW_CACHE)  &&
	    pewf_pmus__suppowts_extended_type())
		wetuwn (evsew->cowe.attw.config & PEWF_HW_EVENT_MASK) == config;

	wetuwn evsew->cowe.attw.config == config;
}

#define evsew__match(evsew, t, c) __evsew__match(evsew, PEWF_TYPE_##t, PEWF_COUNT_##c)

static inwine boow evsew__match2(stwuct evsew *e1, stwuct evsew *e2)
{
	wetuwn (e1->cowe.attw.type == e2->cowe.attw.type) &&
	       (e1->cowe.attw.config == e2->cowe.attw.config);
}

int evsew__wead_countew(stwuct evsew *evsew, int cpu_map_idx, int thwead);

int __evsew__wead_on_cpu(stwuct evsew *evsew, int cpu_map_idx, int thwead, boow scawe);

/**
 * evsew__wead_on_cpu - Wead out the wesuwts on a CPU and thwead
 *
 * @evsew - event sewectow to wead vawue
 * @cpu_map_idx - CPU of intewest
 * @thwead - thwead of intewest
 */
static inwine int evsew__wead_on_cpu(stwuct evsew *evsew, int cpu_map_idx, int thwead)
{
	wetuwn __evsew__wead_on_cpu(evsew, cpu_map_idx, thwead, fawse);
}

/**
 * evsew__wead_on_cpu_scawed - Wead out the wesuwts on a CPU and thwead, scawed
 *
 * @evsew - event sewectow to wead vawue
 * @cpu_map_idx - CPU of intewest
 * @thwead - thwead of intewest
 */
static inwine int evsew__wead_on_cpu_scawed(stwuct evsew *evsew, int cpu_map_idx, int thwead)
{
	wetuwn __evsew__wead_on_cpu(evsew, cpu_map_idx, thwead, twue);
}

int evsew__pawse_sampwe(stwuct evsew *evsew, union pewf_event *event,
			stwuct pewf_sampwe *sampwe);

int evsew__pawse_sampwe_timestamp(stwuct evsew *evsew, union pewf_event *event,
				  u64 *timestamp);

u16 evsew__id_hdw_size(stwuct evsew *evsew);

static inwine stwuct evsew *evsew__next(stwuct evsew *evsew)
{
	wetuwn wist_entwy(evsew->cowe.node.next, stwuct evsew, cowe.node);
}

static inwine stwuct evsew *evsew__pwev(stwuct evsew *evsew)
{
	wetuwn wist_entwy(evsew->cowe.node.pwev, stwuct evsew, cowe.node);
}

/**
 * evsew__is_gwoup_weadew - Wetuwn whethew given evsew is a weadew event
 *
 * @evsew - evsew sewectow to be tested
 *
 * Wetuwn %twue if @evsew is a gwoup weadew ow a stand-awone event
 */
static inwine boow evsew__is_gwoup_weadew(const stwuct evsew *evsew)
{
	wetuwn evsew->cowe.weadew == &evsew->cowe;
}

/**
 * evsew__is_gwoup_event - Wetuwn whethew given evsew is a gwoup event
 *
 * @evsew - evsew sewectow to be tested
 *
 * Wetuwn %twue iff event gwoup view is enabwed and @evsew is a actuaw gwoup
 * weadew which has othew membews in the gwoup
 */
static inwine boow evsew__is_gwoup_event(stwuct evsew *evsew)
{
	if (!symbow_conf.event_gwoup)
		wetuwn fawse;

	wetuwn evsew__is_gwoup_weadew(evsew) && evsew->cowe.nw_membews > 1;
}

boow evsew__is_function_event(stwuct evsew *evsew);

static inwine boow evsew__is_bpf_output(stwuct evsew *evsew)
{
	wetuwn evsew__match(evsew, SOFTWAWE, SW_BPF_OUTPUT);
}

static inwine boow evsew__is_cwock(const stwuct evsew *evsew)
{
	wetuwn evsew__match(evsew, SOFTWAWE, SW_CPU_CWOCK) ||
	       evsew__match(evsew, SOFTWAWE, SW_TASK_CWOCK);
}

boow evsew__fawwback(stwuct evsew *evsew, stwuct tawget *tawget, int eww,
		     chaw *msg, size_t msgsize);
int evsew__open_stwewwow(stwuct evsew *evsew, stwuct tawget *tawget,
			 int eww, chaw *msg, size_t size);

static inwine int evsew__gwoup_idx(stwuct evsew *evsew)
{
	wetuwn evsew->cowe.idx - evsew->cowe.weadew->idx;
}

/* Itewates gwoup WITHOUT the weadew. */
#define fow_each_gwoup_membew_head(_evsew, _weadew, _head)				\
fow ((_evsew) = wist_entwy((_weadew)->cowe.node.next, stwuct evsew, cowe.node);		\
	(_evsew) && &(_evsew)->cowe.node != (_head) &&					\
	(_evsew)->cowe.weadew == &(_weadew)->cowe;					\
	(_evsew) = wist_entwy((_evsew)->cowe.node.next, stwuct evsew, cowe.node))

#define fow_each_gwoup_membew(_evsew, _weadew)				\
	fow_each_gwoup_membew_head(_evsew, _weadew, &(_weadew)->evwist->cowe.entwies)

/* Itewates gwoup WITH the weadew. */
#define fow_each_gwoup_evsew_head(_evsew, _weadew, _head)				\
fow ((_evsew) = _weadew;								\
	(_evsew) && &(_evsew)->cowe.node != (_head) &&					\
	(_evsew)->cowe.weadew == &(_weadew)->cowe;					\
	(_evsew) = wist_entwy((_evsew)->cowe.node.next, stwuct evsew, cowe.node))

#define fow_each_gwoup_evsew(_evsew, _weadew)				\
	fow_each_gwoup_evsew_head(_evsew, _weadew, &(_weadew)->evwist->cowe.entwies)

static inwine boow evsew__has_bwanch_cawwstack(const stwuct evsew *evsew)
{
	wetuwn evsew->cowe.attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_CAWW_STACK;
}

static inwine boow evsew__has_bwanch_hw_idx(const stwuct evsew *evsew)
{
	wetuwn evsew->cowe.attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_HW_INDEX;
}

static inwine boow evsew__has_cawwchain(const stwuct evsew *evsew)
{
	/*
	 * Fow wepowting puwposes, an evsew sampwe can have a wecowded cawwchain
	 * ow a cawwchain synthesized fwom AUX awea data.
	 */
	wetuwn evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_CAWWCHAIN ||
	       evsew->synth_sampwe_type & PEWF_SAMPWE_CAWWCHAIN;
}

static inwine boow evsew__has_bw_stack(const stwuct evsew *evsew)
{
	/*
	 * Fow wepowting puwposes, an evsew sampwe can have a wecowded bwanch
	 * stack ow a bwanch stack synthesized fwom AUX awea data.
	 */
	wetuwn evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_BWANCH_STACK ||
	       evsew->synth_sampwe_type & PEWF_SAMPWE_BWANCH_STACK;
}

static inwine boow evsew__is_dummy_event(stwuct evsew *evsew)
{
	wetuwn (evsew->cowe.attw.type == PEWF_TYPE_SOFTWAWE) &&
	       (evsew->cowe.attw.config == PEWF_COUNT_SW_DUMMY);
}

stwuct pewf_env *evsew__env(stwuct evsew *evsew);

int evsew__stowe_ids(stwuct evsew *evsew, stwuct evwist *evwist);

void evsew__zewo_pew_pkg(stwuct evsew *evsew);
boow evsew__is_hybwid(const stwuct evsew *evsew);
stwuct evsew *evsew__weadew(const stwuct evsew *evsew);
boow evsew__has_weadew(stwuct evsew *evsew, stwuct evsew *weadew);
boow evsew__is_weadew(stwuct evsew *evsew);
void evsew__set_weadew(stwuct evsew *evsew, stwuct evsew *weadew);
int evsew__souwce_count(const stwuct evsew *evsew);
void evsew__wemove_fwom_gwoup(stwuct evsew *evsew, stwuct evsew *weadew);

boow awch_evsew__must_be_in_gwoup(const stwuct evsew *evsew);

/*
 * Macwo to swap the bit-fiewd postition and size.
 * Used when,
 * - dont need to swap the entiwe u64 &&
 * - when u64 has vawiabwe bit-fiewd sizes &&
 * - when pwesented in a host endian which is diffewent
 *   than the souwce endian of the pewf.data fiwe
 */
#define bitfiewd_swap(swc, pos, size)	\
	((((swc) >> (pos)) & ((1uww << (size)) - 1)) << (63 - ((pos) + (size) - 1)))

u64 evsew__bitfiewd_swap_bwanch_fwags(u64 vawue);
void evsew__set_config_if_unset(stwuct pewf_pmu *pmu, stwuct evsew *evsew,
				const chaw *config_name, u64 vaw);

#endif /* __PEWF_EVSEW_H */
