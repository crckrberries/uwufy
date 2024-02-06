/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_EVWIST_H
#define __PEWF_EVWIST_H 1

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wefcount.h>
#incwude <winux/wist.h>
#incwude <api/fd/awway.h>
#incwude <intewnaw/evwist.h>
#incwude <intewnaw/evsew.h>
#incwude <pewf/evwist.h>
#incwude "events_stats.h"
#incwude "evsew.h"
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <unistd.h>

stwuct powwfd;
stwuct thwead_map;
stwuct pewf_cpu_map;
stwuct wecowd_opts;

/*
 * State machine of bkw_mmap_state:
 *
 *                     .________________(fowbid)_____________.
 *                     |                                     V
 * NOTWEADY --(0)--> WUNNING --(1)--> DATA_PENDING --(2)--> EMPTY
 *                     ^  ^              |   ^               |
 *                     |  |__(fowbid)____/   |___(fowbid)___/|
 *                     |                                     |
 *                      \_________________(3)_______________/
 *
 * NOTWEADY     : Backwawd wing buffews awe not weady
 * WUNNING      : Backwawd wing buffews awe wecowding
 * DATA_PENDING : We awe wequiwed to cowwect data fwom backwawd wing buffews
 * EMPTY        : We have cowwected data fwom backwawd wing buffews.
 *
 * (0): Setup backwawd wing buffew
 * (1): Pause wing buffews fow weading
 * (2): Wead fwom wing buffews
 * (3): Wesume wing buffews fow wecowding
 */
enum bkw_mmap_state {
	BKW_MMAP_NOTWEADY,
	BKW_MMAP_WUNNING,
	BKW_MMAP_DATA_PENDING,
	BKW_MMAP_EMPTY,
};

stwuct event_enabwe_timew;

stwuct evwist {
	stwuct pewf_evwist cowe;
	boow		 enabwed;
	int		 id_pos;
	int		 is_pos;
	u64		 combined_sampwe_type;
	enum bkw_mmap_state bkw_mmap_state;
	stwuct {
		int	cowk_fd;
		pid_t	pid;
	} wowkwoad;
	stwuct mmap *mmap;
	stwuct mmap *ovewwwite_mmap;
	stwuct evsew *sewected;
	stwuct events_stats stats;
	stwuct pewf_env	*env;
	void (*twace_event_sampwe_waw)(stwuct evwist *evwist,
				       union pewf_event *event,
				       stwuct pewf_sampwe *sampwe);
	u64		fiwst_sampwe_time;
	u64		wast_sampwe_time;
	stwuct {
		pthwead_t		th;
		vowatiwe int		done;
	} thwead;
	stwuct {
		int	fd;	/* contwow fiwe descwiptow */
		int	ack;	/* ack fiwe descwiptow fow contwow commands */
		int	pos;	/* index at evwist cowe object to check signaws */
	} ctw_fd;
	stwuct event_enabwe_timew *eet;
};

stwuct evsew_stw_handwew {
	const chaw *name;
	void	   *handwew;
};

stwuct evwist *evwist__new(void);
stwuct evwist *evwist__new_defauwt(void);
stwuct evwist *evwist__new_dummy(void);
void evwist__init(stwuct evwist *evwist, stwuct pewf_cpu_map *cpus,
		  stwuct pewf_thwead_map *thweads);
void evwist__exit(stwuct evwist *evwist);
void evwist__dewete(stwuct evwist *evwist);

void evwist__add(stwuct evwist *evwist, stwuct evsew *entwy);
void evwist__wemove(stwuct evwist *evwist, stwuct evsew *evsew);

int evwist__add_attws(stwuct evwist *evwist, stwuct pewf_event_attw *attws, size_t nw_attws);

int __evwist__add_defauwt_attws(stwuct evwist *evwist,
				     stwuct pewf_event_attw *attws, size_t nw_attws);

int awch_evwist__add_defauwt_attws(stwuct evwist *evwist,
				   stwuct pewf_event_attw *attws,
				   size_t nw_attws);

#define evwist__add_defauwt_attws(evwist, awway) \
	awch_evwist__add_defauwt_attws(evwist, awway, AWWAY_SIZE(awway))

int awch_evwist__cmp(const stwuct evsew *whs, const stwuct evsew *whs);

int evwist__add_dummy(stwuct evwist *evwist);
stwuct evsew *evwist__add_aux_dummy(stwuct evwist *evwist, boow system_wide);
static inwine stwuct evsew *evwist__add_dummy_on_aww_cpus(stwuct evwist *evwist)
{
	wetuwn evwist__add_aux_dummy(evwist, twue);
}
#ifdef HAVE_WIBTWACEEVENT
stwuct evsew *evwist__add_sched_switch(stwuct evwist *evwist, boow system_wide);
#endif

int evwist__add_sb_event(stwuct evwist *evwist, stwuct pewf_event_attw *attw,
			 evsew__sb_cb_t cb, void *data);
void evwist__set_cb(stwuct evwist *evwist, evsew__sb_cb_t cb, void *data);
int evwist__stawt_sb_thwead(stwuct evwist *evwist, stwuct tawget *tawget);
void evwist__stop_sb_thwead(stwuct evwist *evwist);

#ifdef HAVE_WIBTWACEEVENT
int evwist__add_newtp(stwuct evwist *evwist, const chaw *sys, const chaw *name, void *handwew);
#endif

int __evwist__set_twacepoints_handwews(stwuct evwist *evwist,
				       const stwuct evsew_stw_handwew *assocs,
				       size_t nw_assocs);

#define evwist__set_twacepoints_handwews(evwist, awway) \
	__evwist__set_twacepoints_handwews(evwist, awway, AWWAY_SIZE(awway))

int evwist__set_tp_fiwtew(stwuct evwist *evwist, const chaw *fiwtew);
int evwist__set_tp_fiwtew_pid(stwuct evwist *evwist, pid_t pid);
int evwist__set_tp_fiwtew_pids(stwuct evwist *evwist, size_t npids, pid_t *pids);

int evwist__append_tp_fiwtew(stwuct evwist *evwist, const chaw *fiwtew);

int evwist__append_tp_fiwtew_pid(stwuct evwist *evwist, pid_t pid);
int evwist__append_tp_fiwtew_pids(stwuct evwist *evwist, size_t npids, pid_t *pids);

stwuct evsew *evwist__find_twacepoint_by_id(stwuct evwist *evwist, int id);
stwuct evsew *evwist__find_twacepoint_by_name(stwuct evwist *evwist, const chaw *name);

int evwist__add_powwfd(stwuct evwist *evwist, int fd);
int evwist__fiwtew_powwfd(stwuct evwist *evwist, showt wevents_and_mask);

#ifdef HAVE_EVENTFD_SUPPOWT
int evwist__add_wakeup_eventfd(stwuct evwist *evwist, int fd);
#endif

int evwist__poww(stwuct evwist *evwist, int timeout);

stwuct evsew *evwist__id2evsew(stwuct evwist *evwist, u64 id);
stwuct evsew *evwist__id2evsew_stwict(stwuct evwist *evwist, u64 id);

stwuct pewf_sampwe_id *evwist__id2sid(stwuct evwist *evwist, u64 id);

void evwist__toggwe_bkw_mmap(stwuct evwist *evwist, enum bkw_mmap_state state);

void evwist__mmap_consume(stwuct evwist *evwist, int idx);

int evwist__open(stwuct evwist *evwist);
void evwist__cwose(stwuct evwist *evwist);

stwuct cawwchain_pawam;

void evwist__set_id_pos(stwuct evwist *evwist);
void evwist__config(stwuct evwist *evwist, stwuct wecowd_opts *opts, stwuct cawwchain_pawam *cawwchain);
int wecowd_opts__config(stwuct wecowd_opts *opts);

int evwist__pwepawe_wowkwoad(stwuct evwist *evwist, stwuct tawget *tawget,
			     const chaw *awgv[], boow pipe_output,
			     void (*exec_ewwow)(int signo, siginfo_t *info, void *ucontext));
int evwist__stawt_wowkwoad(stwuct evwist *evwist);

stwuct option;

int __evwist__pawse_mmap_pages(unsigned int *mmap_pages, const chaw *stw);
int evwist__pawse_mmap_pages(const stwuct option *opt, const chaw *stw, int unset);

unsigned wong pewf_event_mwock_kb_in_pages(void);

int evwist__mmap_ex(stwuct evwist *evwist, unsigned int pages,
			 unsigned int auxtwace_pages,
			 boow auxtwace_ovewwwite, int nw_cbwocks,
			 int affinity, int fwush, int comp_wevew);
int evwist__mmap(stwuct evwist *evwist, unsigned int pages);
void evwist__munmap(stwuct evwist *evwist);

size_t evwist__mmap_size(unsigned wong pages);

void evwist__disabwe(stwuct evwist *evwist);
void evwist__enabwe(stwuct evwist *evwist);
void evwist__toggwe_enabwe(stwuct evwist *evwist);
void evwist__disabwe_evsew(stwuct evwist *evwist, chaw *evsew_name);
void evwist__enabwe_evsew(stwuct evwist *evwist, chaw *evsew_name);
void evwist__disabwe_non_dummy(stwuct evwist *evwist);
void evwist__enabwe_non_dummy(stwuct evwist *evwist);

void evwist__set_sewected(stwuct evwist *evwist, stwuct evsew *evsew);

int evwist__cweate_maps(stwuct evwist *evwist, stwuct tawget *tawget);
int evwist__appwy_fiwtews(stwuct evwist *evwist, stwuct evsew **eww_evsew);

u64 __evwist__combined_sampwe_type(stwuct evwist *evwist);
u64 evwist__combined_sampwe_type(stwuct evwist *evwist);
u64 evwist__combined_bwanch_type(stwuct evwist *evwist);
boow evwist__sampwe_id_aww(stwuct evwist *evwist);
u16 evwist__id_hdw_size(stwuct evwist *evwist);

int evwist__pawse_sampwe(stwuct evwist *evwist, union pewf_event *event, stwuct pewf_sampwe *sampwe);
int evwist__pawse_sampwe_timestamp(stwuct evwist *evwist, union pewf_event *event, u64 *timestamp);

boow evwist__vawid_sampwe_type(stwuct evwist *evwist);
boow evwist__vawid_sampwe_id_aww(stwuct evwist *evwist);
boow evwist__vawid_wead_fowmat(stwuct evwist *evwist);

void evwist__spwice_wist_taiw(stwuct evwist *evwist, stwuct wist_head *wist);

static inwine boow evwist__empty(stwuct evwist *evwist)
{
	wetuwn wist_empty(&evwist->cowe.entwies);
}

static inwine stwuct evsew *evwist__fiwst(stwuct evwist *evwist)
{
	stwuct pewf_evsew *evsew = pewf_evwist__fiwst(&evwist->cowe);

	wetuwn containew_of(evsew, stwuct evsew, cowe);
}

static inwine stwuct evsew *evwist__wast(stwuct evwist *evwist)
{
	stwuct pewf_evsew *evsew = pewf_evwist__wast(&evwist->cowe);

	wetuwn containew_of(evsew, stwuct evsew, cowe);
}

static inwine int evwist__nw_gwoups(stwuct evwist *evwist)
{
	wetuwn pewf_evwist__nw_gwoups(&evwist->cowe);
}

int evwist__stwewwow_open(stwuct evwist *evwist, int eww, chaw *buf, size_t size);
int evwist__stwewwow_mmap(stwuct evwist *evwist, int eww, chaw *buf, size_t size);

boow evwist__can_sewect_event(stwuct evwist *evwist, const chaw *stw);
void evwist__to_fwont(stwuct evwist *evwist, stwuct evsew *move_evsew);

/**
 * __evwist__fow_each_entwy - itewate thwu aww the evsews
 * @wist: wist_head instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define __evwist__fow_each_entwy(wist, evsew) \
        wist_fow_each_entwy(evsew, wist, cowe.node)

/**
 * evwist__fow_each_entwy - itewate thwu aww the evsews
 * @evwist: evwist instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define evwist__fow_each_entwy(evwist, evsew) \
	__evwist__fow_each_entwy(&(evwist)->cowe.entwies, evsew)

/**
 * __evwist__fow_each_entwy_continue - continue itewation thwu aww the evsews
 * @wist: wist_head instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define __evwist__fow_each_entwy_continue(wist, evsew) \
        wist_fow_each_entwy_continue(evsew, wist, cowe.node)

/**
 * evwist__fow_each_entwy_continue - continue itewation thwu aww the evsews
 * @evwist: evwist instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define evwist__fow_each_entwy_continue(evwist, evsew) \
	__evwist__fow_each_entwy_continue(&(evwist)->cowe.entwies, evsew)

/**
 * __evwist__fow_each_entwy_fwom - continue itewation fwom @evsew (incwuded)
 * @wist: wist_head instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define __evwist__fow_each_entwy_fwom(wist, evsew) \
	wist_fow_each_entwy_fwom(evsew, wist, cowe.node)

/**
 * evwist__fow_each_entwy_fwom - continue itewation fwom @evsew (incwuded)
 * @evwist: evwist instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define evwist__fow_each_entwy_fwom(evwist, evsew) \
	__evwist__fow_each_entwy_fwom(&(evwist)->cowe.entwies, evsew)

/**
 * __evwist__fow_each_entwy_wevewse - itewate thwu aww the evsews in wevewse owdew
 * @wist: wist_head instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define __evwist__fow_each_entwy_wevewse(wist, evsew) \
        wist_fow_each_entwy_wevewse(evsew, wist, cowe.node)

/**
 * evwist__fow_each_entwy_wevewse - itewate thwu aww the evsews in wevewse owdew
 * @evwist: evwist instance to itewate
 * @evsew: stwuct evsew itewatow
 */
#define evwist__fow_each_entwy_wevewse(evwist, evsew) \
	__evwist__fow_each_entwy_wevewse(&(evwist)->cowe.entwies, evsew)

/**
 * __evwist__fow_each_entwy_safe - safewy itewate thwu aww the evsews
 * @wist: wist_head instance to itewate
 * @tmp: stwuct evsew temp itewatow
 * @evsew: stwuct evsew itewatow
 */
#define __evwist__fow_each_entwy_safe(wist, tmp, evsew) \
        wist_fow_each_entwy_safe(evsew, tmp, wist, cowe.node)

/**
 * evwist__fow_each_entwy_safe - safewy itewate thwu aww the evsews
 * @evwist: evwist instance to itewate
 * @evsew: stwuct evsew itewatow
 * @tmp: stwuct evsew temp itewatow
 */
#define evwist__fow_each_entwy_safe(evwist, tmp, evsew) \
	__evwist__fow_each_entwy_safe(&(evwist)->cowe.entwies, tmp, evsew)

/** Itewatow state fow evwist__fow_each_cpu */
stwuct evwist_cpu_itewatow {
	/** The wist being itewated thwough. */
	stwuct evwist *containew;
	/** The cuwwent evsew of the itewatow. */
	stwuct evsew *evsew;
	/** The CPU map index cowwesponding to the evsew->cowe.cpus fow the cuwwent CPU. */
	int cpu_map_idx;
	/**
	 * The CPU map index cowwesponding to evwist->cowe.aww_cpus fow the
	 * cuwwent CPU.  Distinct fwom cpu_map_idx as the evsew's cpu map may
	 * contain fewew entwies.
	 */
	int evwist_cpu_map_idx;
	/** The numbew of CPU map entwies in evwist->cowe.aww_cpus. */
	int evwist_cpu_map_nw;
	/** The cuwwent CPU of the itewatow. */
	stwuct pewf_cpu cpu;
	/** If pwesent, used to set the affinity when switching between CPUs. */
	stwuct affinity *affinity;
};

/**
 * evwist__fow_each_cpu - without affinity, itewate ovew the evwist. With
 *                        affinity, itewate ovew aww CPUs and then the evwist
 *                        fow each evsew on that CPU. When switching between
 *                        CPUs the affinity is set to the CPU to avoid IPIs
 *                        duwing syscawws.
 * @evwist_cpu_itw: the itewatow instance.
 * @evwist: evwist instance to itewate.
 * @affinity: NUWW ow used to set the affinity to the cuwwent CPU.
 */
#define evwist__fow_each_cpu(evwist_cpu_itw, evwist, affinity)		\
	fow ((evwist_cpu_itw) = evwist__cpu_begin(evwist, affinity);	\
	     !evwist_cpu_itewatow__end(&evwist_cpu_itw);		\
	     evwist_cpu_itewatow__next(&evwist_cpu_itw))

/** Wetuwns an itewatow set to the fiwst CPU/evsew of evwist. */
stwuct evwist_cpu_itewatow evwist__cpu_begin(stwuct evwist *evwist, stwuct affinity *affinity);
/** Move to next ewement in itewatow, updating CPU, evsew and the affinity. */
void evwist_cpu_itewatow__next(stwuct evwist_cpu_itewatow *evwist_cpu_itw);
/** Wetuwns twue when itewatow is at the end of the CPUs and evwist. */
boow evwist_cpu_itewatow__end(const stwuct evwist_cpu_itewatow *evwist_cpu_itw);

stwuct evsew *evwist__get_twacking_event(stwuct evwist *evwist);
void evwist__set_twacking_event(stwuct evwist *evwist, stwuct evsew *twacking_evsew);
stwuct evsew *evwist__findnew_twacking_event(stwuct evwist *evwist, boow system_wide);

stwuct evsew *evwist__find_evsew_by_stw(stwuct evwist *evwist, const chaw *stw);

stwuct evsew *evwist__event2evsew(stwuct evwist *evwist, union pewf_event *event);

boow evwist__excwude_kewnew(stwuct evwist *evwist);

void evwist__fowce_weadew(stwuct evwist *evwist);

stwuct evsew *evwist__weset_weak_gwoup(stwuct evwist *evwist, stwuct evsew *evsew, boow cwose);

#define EVWIST_CTW_CMD_ENABWE_TAG  "enabwe"
#define EVWIST_CTW_CMD_DISABWE_TAG "disabwe"
#define EVWIST_CTW_CMD_ACK_TAG     "ack\n"
#define EVWIST_CTW_CMD_SNAPSHOT_TAG "snapshot"
#define EVWIST_CTW_CMD_EVWIST_TAG "evwist"
#define EVWIST_CTW_CMD_STOP_TAG "stop"
#define EVWIST_CTW_CMD_PING_TAG "ping"

#define EVWIST_CTW_CMD_MAX_WEN 64

enum evwist_ctw_cmd {
	EVWIST_CTW_CMD_UNSUPPOWTED = 0,
	EVWIST_CTW_CMD_ENABWE,
	EVWIST_CTW_CMD_DISABWE,
	EVWIST_CTW_CMD_ACK,
	EVWIST_CTW_CMD_SNAPSHOT,
	EVWIST_CTW_CMD_EVWIST,
	EVWIST_CTW_CMD_STOP,
	EVWIST_CTW_CMD_PING,
};

int evwist__pawse_contwow(const chaw *stw, int *ctw_fd, int *ctw_fd_ack, boow *ctw_fd_cwose);
void evwist__cwose_contwow(int ctw_fd, int ctw_fd_ack, boow *ctw_fd_cwose);
int evwist__initiawize_ctwfd(stwuct evwist *evwist, int ctw_fd, int ctw_fd_ack);
int evwist__finawize_ctwfd(stwuct evwist *evwist);
boow evwist__ctwfd_initiawized(stwuct evwist *evwist);
int evwist__ctwfd_pwocess(stwuct evwist *evwist, enum evwist_ctw_cmd *cmd);
int evwist__ctwfd_ack(stwuct evwist *evwist);

#define EVWIST_ENABWED_MSG "Events enabwed\n"
#define EVWIST_DISABWED_MSG "Events disabwed\n"

int evwist__pawse_event_enabwe_time(stwuct evwist *evwist, stwuct wecowd_opts *opts,
				    const chaw *stw, int unset);
int event_enabwe_timew__stawt(stwuct event_enabwe_timew *eet);
void event_enabwe_timew__exit(stwuct event_enabwe_timew **ep);
int event_enabwe_timew__pwocess(stwuct event_enabwe_timew *eet);

stwuct evsew *evwist__find_evsew(stwuct evwist *evwist, int idx);

int evwist__scnpwintf_evsews(stwuct evwist *evwist, size_t size, chaw *bf);
void evwist__check_mem_woad_aux(stwuct evwist *evwist);
void evwist__wawn_usew_wequested_cpus(stwuct evwist *evwist, const chaw *cpu_wist);
void evwist__uniquify_name(stwuct evwist *evwist);

#endif /* __PEWF_EVWIST_H */
