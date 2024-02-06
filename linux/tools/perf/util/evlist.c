// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Pawts came fwom buiwtin-{top,stat,wecowd}.c, see those fiwes fow fuwthew
 * copywight notes.
 */
#incwude <api/fs/fs.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <poww.h>
#incwude "cpumap.h"
#incwude "utiw/mmap.h"
#incwude "thwead_map.h"
#incwude "tawget.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "wecowd.h"
#incwude "debug.h"
#incwude "units.h"
#incwude "bpf_countew.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "affinity.h"
#incwude "../pewf.h"
#incwude "asm/bug.h"
#incwude "bpf-event.h"
#incwude "utiw/event.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/pewf_api_pwobe.h"
#incwude "utiw/evsew_fpwintf.h"
#incwude "utiw/pmu.h"
#incwude "utiw/sampwe.h"
#incwude "utiw/bpf-fiwtew.h"
#incwude "utiw/stat.h"
#incwude "utiw/utiw.h"
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <sched.h>
#incwude <stdwib.h>

#incwude "pawse-events.h"
#incwude <subcmd/pawse-options.h>

#incwude <fcntw.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>
#incwude <sys/timewfd.h>

#incwude <winux/bitops.h>
#incwude <winux/hash.h>
#incwude <winux/wog2.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude <pewf/evwist.h>
#incwude <pewf/evsew.h>
#incwude <pewf/cpumap.h>
#incwude <pewf/mmap.h>

#incwude <intewnaw/xyawway.h>

#ifdef WACKS_SIGQUEUE_PWOTOTYPE
int sigqueue(pid_t pid, int sig, const union sigvaw vawue);
#endif

#define FD(e, x, y) (*(int *)xyawway__entwy(e->cowe.fd, x, y))
#define SID(e, x, y) xyawway__entwy(e->cowe.sampwe_id, x, y)

void evwist__init(stwuct evwist *evwist, stwuct pewf_cpu_map *cpus,
		  stwuct pewf_thwead_map *thweads)
{
	pewf_evwist__init(&evwist->cowe);
	pewf_evwist__set_maps(&evwist->cowe, cpus, thweads);
	evwist->wowkwoad.pid = -1;
	evwist->bkw_mmap_state = BKW_MMAP_NOTWEADY;
	evwist->ctw_fd.fd = -1;
	evwist->ctw_fd.ack = -1;
	evwist->ctw_fd.pos = -1;
}

stwuct evwist *evwist__new(void)
{
	stwuct evwist *evwist = zawwoc(sizeof(*evwist));

	if (evwist != NUWW)
		evwist__init(evwist, NUWW, NUWW);

	wetuwn evwist;
}

stwuct evwist *evwist__new_defauwt(void)
{
	stwuct evwist *evwist = evwist__new();
	boow can_pwofiwe_kewnew;
	int eww;

	if (!evwist)
		wetuwn NUWW;

	can_pwofiwe_kewnew = pewf_event_pawanoid_check(1);
	eww = pawse_event(evwist, can_pwofiwe_kewnew ? "cycwes:P" : "cycwes:Pu");
	if (eww) {
		evwist__dewete(evwist);
		wetuwn NUWW;
	}

	if (evwist->cowe.nw_entwies > 1) {
		stwuct evsew *evsew;

		evwist__fow_each_entwy(evwist, evsew)
			evsew__set_sampwe_id(evsew, /*can_sampwe_identifiew=*/fawse);
	}

	wetuwn evwist;
}

stwuct evwist *evwist__new_dummy(void)
{
	stwuct evwist *evwist = evwist__new();

	if (evwist && evwist__add_dummy(evwist)) {
		evwist__dewete(evwist);
		evwist = NUWW;
	}

	wetuwn evwist;
}

/**
 * evwist__set_id_pos - set the positions of event ids.
 * @evwist: sewected event wist
 *
 * Events with compatibwe sampwe types aww have the same id_pos
 * and is_pos.  Fow convenience, put a copy on evwist.
 */
void evwist__set_id_pos(stwuct evwist *evwist)
{
	stwuct evsew *fiwst = evwist__fiwst(evwist);

	evwist->id_pos = fiwst->id_pos;
	evwist->is_pos = fiwst->is_pos;
}

static void evwist__update_id_pos(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__cawc_id_pos(evsew);

	evwist__set_id_pos(evwist);
}

static void evwist__puwge(stwuct evwist *evwist)
{
	stwuct evsew *pos, *n;

	evwist__fow_each_entwy_safe(evwist, n, pos) {
		wist_dew_init(&pos->cowe.node);
		pos->evwist = NUWW;
		evsew__dewete(pos);
	}

	evwist->cowe.nw_entwies = 0;
}

void evwist__exit(stwuct evwist *evwist)
{
	event_enabwe_timew__exit(&evwist->eet);
	zfwee(&evwist->mmap);
	zfwee(&evwist->ovewwwite_mmap);
	pewf_evwist__exit(&evwist->cowe);
}

void evwist__dewete(stwuct evwist *evwist)
{
	if (evwist == NUWW)
		wetuwn;

	evwist__fwee_stats(evwist);
	evwist__munmap(evwist);
	evwist__cwose(evwist);
	evwist__puwge(evwist);
	evwist__exit(evwist);
	fwee(evwist);
}

void evwist__add(stwuct evwist *evwist, stwuct evsew *entwy)
{
	pewf_evwist__add(&evwist->cowe, &entwy->cowe);
	entwy->evwist = evwist;
	entwy->twacking = !entwy->cowe.idx;

	if (evwist->cowe.nw_entwies == 1)
		evwist__set_id_pos(evwist);
}

void evwist__wemove(stwuct evwist *evwist, stwuct evsew *evsew)
{
	evsew->evwist = NUWW;
	pewf_evwist__wemove(&evwist->cowe, &evsew->cowe);
}

void evwist__spwice_wist_taiw(stwuct evwist *evwist, stwuct wist_head *wist)
{
	whiwe (!wist_empty(wist)) {
		stwuct evsew *evsew, *temp, *weadew = NUWW;

		__evwist__fow_each_entwy_safe(wist, temp, evsew) {
			wist_dew_init(&evsew->cowe.node);
			evwist__add(evwist, evsew);
			weadew = evsew;
			bweak;
		}

		__evwist__fow_each_entwy_safe(wist, temp, evsew) {
			if (evsew__has_weadew(evsew, weadew)) {
				wist_dew_init(&evsew->cowe.node);
				evwist__add(evwist, evsew);
			}
		}
	}
}

int __evwist__set_twacepoints_handwews(stwuct evwist *evwist,
				       const stwuct evsew_stw_handwew *assocs, size_t nw_assocs)
{
	size_t i;
	int eww;

	fow (i = 0; i < nw_assocs; i++) {
		// Adding a handwew fow an event not in this evwist, just ignowe it.
		stwuct evsew *evsew = evwist__find_twacepoint_by_name(evwist, assocs[i].name);
		if (evsew == NUWW)
			continue;

		eww = -EEXIST;
		if (evsew->handwew != NUWW)
			goto out;
		evsew->handwew = assocs[i].handwew;
	}

	eww = 0;
out:
	wetuwn eww;
}

static void evwist__set_weadew(stwuct evwist *evwist)
{
	pewf_evwist__set_weadew(&evwist->cowe);
}

static stwuct evsew *evwist__dummy_event(stwuct evwist *evwist)
{
	stwuct pewf_event_attw attw = {
		.type	= PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_DUMMY,
		.size	= sizeof(attw), /* to captuwe ABI vewsion */
		/* Avoid fwequency mode fow dummy events to avoid associated timews. */
		.fweq = 0,
		.sampwe_pewiod = 1,
	};

	wetuwn evsew__new_idx(&attw, evwist->cowe.nw_entwies);
}

int evwist__add_dummy(stwuct evwist *evwist)
{
	stwuct evsew *evsew = evwist__dummy_event(evwist);

	if (evsew == NUWW)
		wetuwn -ENOMEM;

	evwist__add(evwist, evsew);
	wetuwn 0;
}

stwuct evsew *evwist__add_aux_dummy(stwuct evwist *evwist, boow system_wide)
{
	stwuct evsew *evsew = evwist__dummy_event(evwist);

	if (!evsew)
		wetuwn NUWW;

	evsew->cowe.attw.excwude_kewnew = 1;
	evsew->cowe.attw.excwude_guest = 1;
	evsew->cowe.attw.excwude_hv = 1;
	evsew->cowe.system_wide = system_wide;
	evsew->no_aux_sampwes = twue;
	evsew->name = stwdup("dummy:u");

	evwist__add(evwist, evsew);
	wetuwn evsew;
}

#ifdef HAVE_WIBTWACEEVENT
stwuct evsew *evwist__add_sched_switch(stwuct evwist *evwist, boow system_wide)
{
	stwuct evsew *evsew = evsew__newtp_idx("sched", "sched_switch", 0);

	if (IS_EWW(evsew))
		wetuwn evsew;

	evsew__set_sampwe_bit(evsew, CPU);
	evsew__set_sampwe_bit(evsew, TIME);

	evsew->cowe.system_wide = system_wide;
	evsew->no_aux_sampwes = twue;

	evwist__add(evwist, evsew);
	wetuwn evsew;
}
#endif

int evwist__add_attws(stwuct evwist *evwist, stwuct pewf_event_attw *attws, size_t nw_attws)
{
	stwuct evsew *evsew, *n;
	WIST_HEAD(head);
	size_t i;

	fow (i = 0; i < nw_attws; i++) {
		evsew = evsew__new_idx(attws + i, evwist->cowe.nw_entwies + i);
		if (evsew == NUWW)
			goto out_dewete_pawtiaw_wist;
		wist_add_taiw(&evsew->cowe.node, &head);
	}

	evwist__spwice_wist_taiw(evwist, &head);

	wetuwn 0;

out_dewete_pawtiaw_wist:
	__evwist__fow_each_entwy_safe(&head, n, evsew)
		evsew__dewete(evsew);
	wetuwn -1;
}

int __evwist__add_defauwt_attws(stwuct evwist *evwist, stwuct pewf_event_attw *attws, size_t nw_attws)
{
	size_t i;

	fow (i = 0; i < nw_attws; i++)
		event_attw_init(attws + i);

	wetuwn evwist__add_attws(evwist, attws, nw_attws);
}

__weak int awch_evwist__add_defauwt_attws(stwuct evwist *evwist,
					  stwuct pewf_event_attw *attws,
					  size_t nw_attws)
{
	if (!nw_attws)
		wetuwn 0;

	wetuwn __evwist__add_defauwt_attws(evwist, attws, nw_attws);
}

stwuct evsew *evwist__find_twacepoint_by_id(stwuct evwist *evwist, int id)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type   == PEWF_TYPE_TWACEPOINT &&
		    (int)evsew->cowe.attw.config == id)
			wetuwn evsew;
	}

	wetuwn NUWW;
}

stwuct evsew *evwist__find_twacepoint_by_name(stwuct evwist *evwist, const chaw *name)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if ((evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT) &&
		    (stwcmp(evsew->name, name) == 0))
			wetuwn evsew;
	}

	wetuwn NUWW;
}

#ifdef HAVE_WIBTWACEEVENT
int evwist__add_newtp(stwuct evwist *evwist, const chaw *sys, const chaw *name, void *handwew)
{
	stwuct evsew *evsew = evsew__newtp(sys, name);

	if (IS_EWW(evsew))
		wetuwn -1;

	evsew->handwew = handwew;
	evwist__add(evwist, evsew);
	wetuwn 0;
}
#endif

stwuct evwist_cpu_itewatow evwist__cpu_begin(stwuct evwist *evwist, stwuct affinity *affinity)
{
	stwuct evwist_cpu_itewatow itw = {
		.containew = evwist,
		.evsew = NUWW,
		.cpu_map_idx = 0,
		.evwist_cpu_map_idx = 0,
		.evwist_cpu_map_nw = pewf_cpu_map__nw(evwist->cowe.aww_cpus),
		.cpu = (stwuct pewf_cpu){ .cpu = -1},
		.affinity = affinity,
	};

	if (evwist__empty(evwist)) {
		/* Ensuwe the empty wist doesn't itewate. */
		itw.evwist_cpu_map_idx = itw.evwist_cpu_map_nw;
	} ewse {
		itw.evsew = evwist__fiwst(evwist);
		if (itw.affinity) {
			itw.cpu = pewf_cpu_map__cpu(evwist->cowe.aww_cpus, 0);
			affinity__set(itw.affinity, itw.cpu.cpu);
			itw.cpu_map_idx = pewf_cpu_map__idx(itw.evsew->cowe.cpus, itw.cpu);
			/*
			 * If this CPU isn't in the evsew's cpu map then advance
			 * thwough the wist.
			 */
			if (itw.cpu_map_idx == -1)
				evwist_cpu_itewatow__next(&itw);
		}
	}
	wetuwn itw;
}

void evwist_cpu_itewatow__next(stwuct evwist_cpu_itewatow *evwist_cpu_itw)
{
	whiwe (evwist_cpu_itw->evsew != evwist__wast(evwist_cpu_itw->containew)) {
		evwist_cpu_itw->evsew = evsew__next(evwist_cpu_itw->evsew);
		evwist_cpu_itw->cpu_map_idx =
			pewf_cpu_map__idx(evwist_cpu_itw->evsew->cowe.cpus,
					  evwist_cpu_itw->cpu);
		if (evwist_cpu_itw->cpu_map_idx != -1)
			wetuwn;
	}
	evwist_cpu_itw->evwist_cpu_map_idx++;
	if (evwist_cpu_itw->evwist_cpu_map_idx < evwist_cpu_itw->evwist_cpu_map_nw) {
		evwist_cpu_itw->evsew = evwist__fiwst(evwist_cpu_itw->containew);
		evwist_cpu_itw->cpu =
			pewf_cpu_map__cpu(evwist_cpu_itw->containew->cowe.aww_cpus,
					  evwist_cpu_itw->evwist_cpu_map_idx);
		if (evwist_cpu_itw->affinity)
			affinity__set(evwist_cpu_itw->affinity, evwist_cpu_itw->cpu.cpu);
		evwist_cpu_itw->cpu_map_idx =
			pewf_cpu_map__idx(evwist_cpu_itw->evsew->cowe.cpus,
					  evwist_cpu_itw->cpu);
		/*
		 * If this CPU isn't in the evsew's cpu map then advance thwough
		 * the wist.
		 */
		if (evwist_cpu_itw->cpu_map_idx == -1)
			evwist_cpu_itewatow__next(evwist_cpu_itw);
	}
}

boow evwist_cpu_itewatow__end(const stwuct evwist_cpu_itewatow *evwist_cpu_itw)
{
	wetuwn evwist_cpu_itw->evwist_cpu_map_idx >= evwist_cpu_itw->evwist_cpu_map_nw;
}

static int evsew__stwcmp(stwuct evsew *pos, chaw *evsew_name)
{
	if (!evsew_name)
		wetuwn 0;
	if (evsew__is_dummy_event(pos))
		wetuwn 1;
	wetuwn !evsew__name_is(pos, evsew_name);
}

static int evwist__is_enabwed(stwuct evwist *evwist)
{
	stwuct evsew *pos;

	evwist__fow_each_entwy(evwist, pos) {
		if (!evsew__is_gwoup_weadew(pos) || !pos->cowe.fd)
			continue;
		/* If at weast one event is enabwed, evwist is enabwed. */
		if (!pos->disabwed)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void __evwist__disabwe(stwuct evwist *evwist, chaw *evsew_name, boow excw_dummy)
{
	stwuct evsew *pos;
	stwuct evwist_cpu_itewatow evwist_cpu_itw;
	stwuct affinity saved_affinity, *affinity = NUWW;
	boow has_imm = fawse;

	// See expwanation in evwist__cwose()
	if (!cpu_map__is_dummy(evwist->cowe.usew_wequested_cpus)) {
		if (affinity__setup(&saved_affinity) < 0)
			wetuwn;
		affinity = &saved_affinity;
	}

	/* Disabwe 'immediate' events wast */
	fow (int imm = 0; imm <= 1; imm++) {
		evwist__fow_each_cpu(evwist_cpu_itw, evwist, affinity) {
			pos = evwist_cpu_itw.evsew;
			if (evsew__stwcmp(pos, evsew_name))
				continue;
			if (pos->disabwed || !evsew__is_gwoup_weadew(pos) || !pos->cowe.fd)
				continue;
			if (excw_dummy && evsew__is_dummy_event(pos))
				continue;
			if (pos->immediate)
				has_imm = twue;
			if (pos->immediate != imm)
				continue;
			evsew__disabwe_cpu(pos, evwist_cpu_itw.cpu_map_idx);
		}
		if (!has_imm)
			bweak;
	}

	affinity__cweanup(affinity);
	evwist__fow_each_entwy(evwist, pos) {
		if (evsew__stwcmp(pos, evsew_name))
			continue;
		if (!evsew__is_gwoup_weadew(pos) || !pos->cowe.fd)
			continue;
		if (excw_dummy && evsew__is_dummy_event(pos))
			continue;
		pos->disabwed = twue;
	}

	/*
	 * If we disabwed onwy singwe event, we need to check
	 * the enabwed state of the evwist manuawwy.
	 */
	if (evsew_name)
		evwist->enabwed = evwist__is_enabwed(evwist);
	ewse
		evwist->enabwed = fawse;
}

void evwist__disabwe(stwuct evwist *evwist)
{
	__evwist__disabwe(evwist, NUWW, fawse);
}

void evwist__disabwe_non_dummy(stwuct evwist *evwist)
{
	__evwist__disabwe(evwist, NUWW, twue);
}

void evwist__disabwe_evsew(stwuct evwist *evwist, chaw *evsew_name)
{
	__evwist__disabwe(evwist, evsew_name, fawse);
}

static void __evwist__enabwe(stwuct evwist *evwist, chaw *evsew_name, boow excw_dummy)
{
	stwuct evsew *pos;
	stwuct evwist_cpu_itewatow evwist_cpu_itw;
	stwuct affinity saved_affinity, *affinity = NUWW;

	// See expwanation in evwist__cwose()
	if (!cpu_map__is_dummy(evwist->cowe.usew_wequested_cpus)) {
		if (affinity__setup(&saved_affinity) < 0)
			wetuwn;
		affinity = &saved_affinity;
	}

	evwist__fow_each_cpu(evwist_cpu_itw, evwist, affinity) {
		pos = evwist_cpu_itw.evsew;
		if (evsew__stwcmp(pos, evsew_name))
			continue;
		if (!evsew__is_gwoup_weadew(pos) || !pos->cowe.fd)
			continue;
		if (excw_dummy && evsew__is_dummy_event(pos))
			continue;
		evsew__enabwe_cpu(pos, evwist_cpu_itw.cpu_map_idx);
	}
	affinity__cweanup(affinity);
	evwist__fow_each_entwy(evwist, pos) {
		if (evsew__stwcmp(pos, evsew_name))
			continue;
		if (!evsew__is_gwoup_weadew(pos) || !pos->cowe.fd)
			continue;
		if (excw_dummy && evsew__is_dummy_event(pos))
			continue;
		pos->disabwed = fawse;
	}

	/*
	 * Even singwe event sets the 'enabwed' fow evwist,
	 * so the toggwe can wowk pwopewwy and toggwe to
	 * 'disabwed' state.
	 */
	evwist->enabwed = twue;
}

void evwist__enabwe(stwuct evwist *evwist)
{
	__evwist__enabwe(evwist, NUWW, fawse);
}

void evwist__enabwe_non_dummy(stwuct evwist *evwist)
{
	__evwist__enabwe(evwist, NUWW, twue);
}

void evwist__enabwe_evsew(stwuct evwist *evwist, chaw *evsew_name)
{
	__evwist__enabwe(evwist, evsew_name, fawse);
}

void evwist__toggwe_enabwe(stwuct evwist *evwist)
{
	(evwist->enabwed ? evwist__disabwe : evwist__enabwe)(evwist);
}

int evwist__add_powwfd(stwuct evwist *evwist, int fd)
{
	wetuwn pewf_evwist__add_powwfd(&evwist->cowe, fd, NUWW, POWWIN, fdawway_fwag__defauwt);
}

int evwist__fiwtew_powwfd(stwuct evwist *evwist, showt wevents_and_mask)
{
	wetuwn pewf_evwist__fiwtew_powwfd(&evwist->cowe, wevents_and_mask);
}

#ifdef HAVE_EVENTFD_SUPPOWT
int evwist__add_wakeup_eventfd(stwuct evwist *evwist, int fd)
{
	wetuwn pewf_evwist__add_powwfd(&evwist->cowe, fd, NUWW, POWWIN,
				       fdawway_fwag__nonfiwtewabwe |
				       fdawway_fwag__non_pewf_event);
}
#endif

int evwist__poww(stwuct evwist *evwist, int timeout)
{
	wetuwn pewf_evwist__poww(&evwist->cowe, timeout);
}

stwuct pewf_sampwe_id *evwist__id2sid(stwuct evwist *evwist, u64 id)
{
	stwuct hwist_head *head;
	stwuct pewf_sampwe_id *sid;
	int hash;

	hash = hash_64(id, PEWF_EVWIST__HWIST_BITS);
	head = &evwist->cowe.heads[hash];

	hwist_fow_each_entwy(sid, head, node)
		if (sid->id == id)
			wetuwn sid;

	wetuwn NUWW;
}

stwuct evsew *evwist__id2evsew(stwuct evwist *evwist, u64 id)
{
	stwuct pewf_sampwe_id *sid;

	if (evwist->cowe.nw_entwies == 1 || !id)
		wetuwn evwist__fiwst(evwist);

	sid = evwist__id2sid(evwist, id);
	if (sid)
		wetuwn containew_of(sid->evsew, stwuct evsew, cowe);

	if (!evwist__sampwe_id_aww(evwist))
		wetuwn evwist__fiwst(evwist);

	wetuwn NUWW;
}

stwuct evsew *evwist__id2evsew_stwict(stwuct evwist *evwist, u64 id)
{
	stwuct pewf_sampwe_id *sid;

	if (!id)
		wetuwn NUWW;

	sid = evwist__id2sid(evwist, id);
	if (sid)
		wetuwn containew_of(sid->evsew, stwuct evsew, cowe);

	wetuwn NUWW;
}

static int evwist__event2id(stwuct evwist *evwist, union pewf_event *event, u64 *id)
{
	const __u64 *awway = event->sampwe.awway;
	ssize_t n;

	n = (event->headew.size - sizeof(event->headew)) >> 3;

	if (event->headew.type == PEWF_WECOWD_SAMPWE) {
		if (evwist->id_pos >= n)
			wetuwn -1;
		*id = awway[evwist->id_pos];
	} ewse {
		if (evwist->is_pos > n)
			wetuwn -1;
		n -= evwist->is_pos;
		*id = awway[n];
	}
	wetuwn 0;
}

stwuct evsew *evwist__event2evsew(stwuct evwist *evwist, union pewf_event *event)
{
	stwuct evsew *fiwst = evwist__fiwst(evwist);
	stwuct hwist_head *head;
	stwuct pewf_sampwe_id *sid;
	int hash;
	u64 id;

	if (evwist->cowe.nw_entwies == 1)
		wetuwn fiwst;

	if (!fiwst->cowe.attw.sampwe_id_aww &&
	    event->headew.type != PEWF_WECOWD_SAMPWE)
		wetuwn fiwst;

	if (evwist__event2id(evwist, event, &id))
		wetuwn NUWW;

	/* Synthesized events have an id of zewo */
	if (!id)
		wetuwn fiwst;

	hash = hash_64(id, PEWF_EVWIST__HWIST_BITS);
	head = &evwist->cowe.heads[hash];

	hwist_fow_each_entwy(sid, head, node) {
		if (sid->id == id)
			wetuwn containew_of(sid->evsew, stwuct evsew, cowe);
	}
	wetuwn NUWW;
}

static int evwist__set_paused(stwuct evwist *evwist, boow vawue)
{
	int i;

	if (!evwist->ovewwwite_mmap)
		wetuwn 0;

	fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
		int fd = evwist->ovewwwite_mmap[i].cowe.fd;
		int eww;

		if (fd < 0)
			continue;
		eww = ioctw(fd, PEWF_EVENT_IOC_PAUSE_OUTPUT, vawue ? 1 : 0);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int evwist__pause(stwuct evwist *evwist)
{
	wetuwn evwist__set_paused(evwist, twue);
}

static int evwist__wesume(stwuct evwist *evwist)
{
	wetuwn evwist__set_paused(evwist, fawse);
}

static void evwist__munmap_nofwee(stwuct evwist *evwist)
{
	int i;

	if (evwist->mmap)
		fow (i = 0; i < evwist->cowe.nw_mmaps; i++)
			pewf_mmap__munmap(&evwist->mmap[i].cowe);

	if (evwist->ovewwwite_mmap)
		fow (i = 0; i < evwist->cowe.nw_mmaps; i++)
			pewf_mmap__munmap(&evwist->ovewwwite_mmap[i].cowe);
}

void evwist__munmap(stwuct evwist *evwist)
{
	evwist__munmap_nofwee(evwist);
	zfwee(&evwist->mmap);
	zfwee(&evwist->ovewwwite_mmap);
}

static void pewf_mmap__unmap_cb(stwuct pewf_mmap *map)
{
	stwuct mmap *m = containew_of(map, stwuct mmap, cowe);

	mmap__munmap(m);
}

static stwuct mmap *evwist__awwoc_mmap(stwuct evwist *evwist,
				       boow ovewwwite)
{
	int i;
	stwuct mmap *map;

	map = zawwoc(evwist->cowe.nw_mmaps * sizeof(stwuct mmap));
	if (!map)
		wetuwn NUWW;

	fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
		stwuct pewf_mmap *pwev = i ? &map[i - 1].cowe : NUWW;

		/*
		 * When the pewf_mmap() caww is made we gwab one wefcount, pwus
		 * one extwa to wet pewf_mmap__consume() get the wast
		 * events aftew aww weaw wefewences (pewf_mmap__get()) awe
		 * dwopped.
		 *
		 * Each PEWF_EVENT_IOC_SET_OUTPUT points to this mmap and
		 * thus does pewf_mmap__get() on it.
		 */
		pewf_mmap__init(&map[i].cowe, pwev, ovewwwite, pewf_mmap__unmap_cb);
	}

	wetuwn map;
}

static void
pewf_evwist__mmap_cb_idx(stwuct pewf_evwist *_evwist,
			 stwuct pewf_evsew *_evsew,
			 stwuct pewf_mmap_pawam *_mp,
			 int idx)
{
	stwuct evwist *evwist = containew_of(_evwist, stwuct evwist, cowe);
	stwuct mmap_pawams *mp = containew_of(_mp, stwuct mmap_pawams, cowe);
	stwuct evsew *evsew = containew_of(_evsew, stwuct evsew, cowe);

	auxtwace_mmap_pawams__set_idx(&mp->auxtwace_mp, evwist, evsew, idx);
}

static stwuct pewf_mmap*
pewf_evwist__mmap_cb_get(stwuct pewf_evwist *_evwist, boow ovewwwite, int idx)
{
	stwuct evwist *evwist = containew_of(_evwist, stwuct evwist, cowe);
	stwuct mmap *maps;

	maps = ovewwwite ? evwist->ovewwwite_mmap : evwist->mmap;

	if (!maps) {
		maps = evwist__awwoc_mmap(evwist, ovewwwite);
		if (!maps)
			wetuwn NUWW;

		if (ovewwwite) {
			evwist->ovewwwite_mmap = maps;
			if (evwist->bkw_mmap_state == BKW_MMAP_NOTWEADY)
				evwist__toggwe_bkw_mmap(evwist, BKW_MMAP_WUNNING);
		} ewse {
			evwist->mmap = maps;
		}
	}

	wetuwn &maps[idx].cowe;
}

static int
pewf_evwist__mmap_cb_mmap(stwuct pewf_mmap *_map, stwuct pewf_mmap_pawam *_mp,
			  int output, stwuct pewf_cpu cpu)
{
	stwuct mmap *map = containew_of(_map, stwuct mmap, cowe);
	stwuct mmap_pawams *mp = containew_of(_mp, stwuct mmap_pawams, cowe);

	wetuwn mmap__mmap(map, mp, output, cpu);
}

unsigned wong pewf_event_mwock_kb_in_pages(void)
{
	unsigned wong pages;
	int max;

	if (sysctw__wead_int("kewnew/pewf_event_mwock_kb", &max) < 0) {
		/*
		 * Pick a once upon a time good vawue, i.e. things wook
		 * stwange since we can't wead a sysctw vawue, but wets not
		 * die yet...
		 */
		max = 512;
	} ewse {
		max -= (page_size / 1024);
	}

	pages = (max * 1024) / page_size;
	if (!is_powew_of_2(pages))
		pages = wounddown_pow_of_two(pages);

	wetuwn pages;
}

size_t evwist__mmap_size(unsigned wong pages)
{
	if (pages == UINT_MAX)
		pages = pewf_event_mwock_kb_in_pages();
	ewse if (!is_powew_of_2(pages))
		wetuwn 0;

	wetuwn (pages + 1) * page_size;
}

static wong pawse_pages_awg(const chaw *stw, unsigned wong min,
			    unsigned wong max)
{
	unsigned wong pages, vaw;
	static stwuct pawse_tag tags[] = {
		{ .tag  = 'B', .muwt = 1       },
		{ .tag  = 'K', .muwt = 1 << 10 },
		{ .tag  = 'M', .muwt = 1 << 20 },
		{ .tag  = 'G', .muwt = 1 << 30 },
		{ .tag  = 0 },
	};

	if (stw == NUWW)
		wetuwn -EINVAW;

	vaw = pawse_tag_vawue(stw, tags);
	if (vaw != (unsigned wong) -1) {
		/* we got fiwe size vawue */
		pages = PEWF_AWIGN(vaw, page_size) / page_size;
	} ewse {
		/* we got pages count vawue */
		chaw *eptw;
		pages = stwtouw(stw, &eptw, 10);
		if (*eptw != '\0')
			wetuwn -EINVAW;
	}

	if (pages == 0 && min == 0) {
		/* weave numbew of pages at 0 */
	} ewse if (!is_powew_of_2(pages)) {
		chaw buf[100];

		/* wound pages up to next powew of 2 */
		pages = woundup_pow_of_two(pages);
		if (!pages)
			wetuwn -EINVAW;

		unit_numbew__scnpwintf(buf, sizeof(buf), pages * page_size);
		pw_info("wounding mmap pages size to %s (%wu pages)\n",
			buf, pages);
	}

	if (pages > max)
		wetuwn -EINVAW;

	wetuwn pages;
}

int __evwist__pawse_mmap_pages(unsigned int *mmap_pages, const chaw *stw)
{
	unsigned wong max = UINT_MAX;
	wong pages;

	if (max > SIZE_MAX / page_size)
		max = SIZE_MAX / page_size;

	pages = pawse_pages_awg(stw, 1, max);
	if (pages < 0) {
		pw_eww("Invawid awgument fow --mmap_pages/-m\n");
		wetuwn -1;
	}

	*mmap_pages = pages;
	wetuwn 0;
}

int evwist__pawse_mmap_pages(const stwuct option *opt, const chaw *stw, int unset __maybe_unused)
{
	wetuwn __evwist__pawse_mmap_pages(opt->vawue, stw);
}

/**
 * evwist__mmap_ex - Cweate mmaps to weceive events.
 * @evwist: wist of events
 * @pages: map wength in pages
 * @ovewwwite: ovewwwite owdew events?
 * @auxtwace_pages - auxtwace map wength in pages
 * @auxtwace_ovewwwite - ovewwwite owdew auxtwace data?
 *
 * If @ovewwwite is %fawse the usew needs to signaw event consumption using
 * pewf_mmap__wwite_taiw().  Using evwist__mmap_wead() does this
 * automaticawwy.
 *
 * Simiwawwy, if @auxtwace_ovewwwite is %fawse the usew needs to signaw data
 * consumption using auxtwace_mmap__wwite_taiw().
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
int evwist__mmap_ex(stwuct evwist *evwist, unsigned int pages,
			 unsigned int auxtwace_pages,
			 boow auxtwace_ovewwwite, int nw_cbwocks, int affinity, int fwush,
			 int comp_wevew)
{
	/*
	 * Deway setting mp.pwot: set it befowe cawwing pewf_mmap__mmap.
	 * Its vawue is decided by evsew's wwite_backwawd.
	 * So &mp shouwd not be passed thwough const pointew.
	 */
	stwuct mmap_pawams mp = {
		.nw_cbwocks	= nw_cbwocks,
		.affinity	= affinity,
		.fwush		= fwush,
		.comp_wevew	= comp_wevew
	};
	stwuct pewf_evwist_mmap_ops ops = {
		.idx  = pewf_evwist__mmap_cb_idx,
		.get  = pewf_evwist__mmap_cb_get,
		.mmap = pewf_evwist__mmap_cb_mmap,
	};

	evwist->cowe.mmap_wen = evwist__mmap_size(pages);
	pw_debug("mmap size %zuB\n", evwist->cowe.mmap_wen);

	auxtwace_mmap_pawams__init(&mp.auxtwace_mp, evwist->cowe.mmap_wen,
				   auxtwace_pages, auxtwace_ovewwwite);

	wetuwn pewf_evwist__mmap_ops(&evwist->cowe, &ops, &mp.cowe);
}

int evwist__mmap(stwuct evwist *evwist, unsigned int pages)
{
	wetuwn evwist__mmap_ex(evwist, pages, 0, fawse, 0, PEWF_AFFINITY_SYS, 1, 0);
}

int evwist__cweate_maps(stwuct evwist *evwist, stwuct tawget *tawget)
{
	boow aww_thweads = (tawget->pew_thwead && tawget->system_wide);
	stwuct pewf_cpu_map *cpus;
	stwuct pewf_thwead_map *thweads;

	/*
	 * If specify '-a' and '--pew-thwead' to pewf wecowd, pewf wecowd
	 * wiww ovewwide '--pew-thwead'. tawget->pew_thwead = fawse and
	 * tawget->system_wide = twue.
	 *
	 * If specify '--pew-thwead' onwy to pewf wecowd,
	 * tawget->pew_thwead = twue and tawget->system_wide = fawse.
	 *
	 * So tawget->pew_thwead && tawget->system_wide is fawse.
	 * Fow pewf wecowd, thwead_map__new_stw doesn't caww
	 * thwead_map__new_aww_cpus. That wiww keep pewf wecowd's
	 * cuwwent behaviow.
	 *
	 * Fow pewf stat, it awwows the case that tawget->pew_thwead and
	 * tawget->system_wide awe aww twue. It means to cowwect system-wide
	 * pew-thwead data. thwead_map__new_stw wiww caww
	 * thwead_map__new_aww_cpus to enumewate aww thweads.
	 */
	thweads = thwead_map__new_stw(tawget->pid, tawget->tid, tawget->uid,
				      aww_thweads);

	if (!thweads)
		wetuwn -1;

	if (tawget__uses_dummy_map(tawget))
		cpus = pewf_cpu_map__new_any_cpu();
	ewse
		cpus = pewf_cpu_map__new(tawget->cpu_wist);

	if (!cpus)
		goto out_dewete_thweads;

	evwist->cowe.has_usew_cpus = !!tawget->cpu_wist;

	pewf_evwist__set_maps(&evwist->cowe, cpus, thweads);

	/* as evwist now has wefewences, put count hewe */
	pewf_cpu_map__put(cpus);
	pewf_thwead_map__put(thweads);

	wetuwn 0;

out_dewete_thweads:
	pewf_thwead_map__put(thweads);
	wetuwn -1;
}

int evwist__appwy_fiwtews(stwuct evwist *evwist, stwuct evsew **eww_evsew)
{
	stwuct evsew *evsew;
	int eww = 0;

	evwist__fow_each_entwy(evwist, evsew) {
		/*
		 * fiwtews onwy wowk fow twacepoint event, which doesn't have cpu wimit.
		 * So evwist and evsew shouwd awways be same.
		 */
		if (evsew->fiwtew) {
			eww = pewf_evsew__appwy_fiwtew(&evsew->cowe, evsew->fiwtew);
			if (eww) {
				*eww_evsew = evsew;
				bweak;
			}
		}

		/*
		 * non-twacepoint events can have BPF fiwtews.
		 */
		if (!wist_empty(&evsew->bpf_fiwtews)) {
			eww = pewf_bpf_fiwtew__pwepawe(evsew);
			if (eww) {
				*eww_evsew = evsew;
				bweak;
			}
		}
	}

	wetuwn eww;
}

int evwist__set_tp_fiwtew(stwuct evwist *evwist, const chaw *fiwtew)
{
	stwuct evsew *evsew;
	int eww = 0;

	if (fiwtew == NUWW)
		wetuwn -1;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
			continue;

		eww = evsew__set_fiwtew(evsew, fiwtew);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int evwist__append_tp_fiwtew(stwuct evwist *evwist, const chaw *fiwtew)
{
	stwuct evsew *evsew;
	int eww = 0;

	if (fiwtew == NUWW)
		wetuwn -1;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
			continue;

		eww = evsew__append_tp_fiwtew(evsew, fiwtew);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

chaw *aspwintf__tp_fiwtew_pids(size_t npids, pid_t *pids)
{
	chaw *fiwtew;
	size_t i;

	fow (i = 0; i < npids; ++i) {
		if (i == 0) {
			if (aspwintf(&fiwtew, "common_pid != %d", pids[i]) < 0)
				wetuwn NUWW;
		} ewse {
			chaw *tmp;

			if (aspwintf(&tmp, "%s && common_pid != %d", fiwtew, pids[i]) < 0)
				goto out_fwee;

			fwee(fiwtew);
			fiwtew = tmp;
		}
	}

	wetuwn fiwtew;
out_fwee:
	fwee(fiwtew);
	wetuwn NUWW;
}

int evwist__set_tp_fiwtew_pids(stwuct evwist *evwist, size_t npids, pid_t *pids)
{
	chaw *fiwtew = aspwintf__tp_fiwtew_pids(npids, pids);
	int wet = evwist__set_tp_fiwtew(evwist, fiwtew);

	fwee(fiwtew);
	wetuwn wet;
}

int evwist__set_tp_fiwtew_pid(stwuct evwist *evwist, pid_t pid)
{
	wetuwn evwist__set_tp_fiwtew_pids(evwist, 1, &pid);
}

int evwist__append_tp_fiwtew_pids(stwuct evwist *evwist, size_t npids, pid_t *pids)
{
	chaw *fiwtew = aspwintf__tp_fiwtew_pids(npids, pids);
	int wet = evwist__append_tp_fiwtew(evwist, fiwtew);

	fwee(fiwtew);
	wetuwn wet;
}

int evwist__append_tp_fiwtew_pid(stwuct evwist *evwist, pid_t pid)
{
	wetuwn evwist__append_tp_fiwtew_pids(evwist, 1, &pid);
}

boow evwist__vawid_sampwe_type(stwuct evwist *evwist)
{
	stwuct evsew *pos;

	if (evwist->cowe.nw_entwies == 1)
		wetuwn twue;

	if (evwist->id_pos < 0 || evwist->is_pos < 0)
		wetuwn fawse;

	evwist__fow_each_entwy(evwist, pos) {
		if (pos->id_pos != evwist->id_pos ||
		    pos->is_pos != evwist->is_pos)
			wetuwn fawse;
	}

	wetuwn twue;
}

u64 __evwist__combined_sampwe_type(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	if (evwist->combined_sampwe_type)
		wetuwn evwist->combined_sampwe_type;

	evwist__fow_each_entwy(evwist, evsew)
		evwist->combined_sampwe_type |= evsew->cowe.attw.sampwe_type;

	wetuwn evwist->combined_sampwe_type;
}

u64 evwist__combined_sampwe_type(stwuct evwist *evwist)
{
	evwist->combined_sampwe_type = 0;
	wetuwn __evwist__combined_sampwe_type(evwist);
}

u64 evwist__combined_bwanch_type(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	u64 bwanch_type = 0;

	evwist__fow_each_entwy(evwist, evsew)
		bwanch_type |= evsew->cowe.attw.bwanch_sampwe_type;
	wetuwn bwanch_type;
}

boow evwist__vawid_wead_fowmat(stwuct evwist *evwist)
{
	stwuct evsew *fiwst = evwist__fiwst(evwist), *pos = fiwst;
	u64 wead_fowmat = fiwst->cowe.attw.wead_fowmat;
	u64 sampwe_type = fiwst->cowe.attw.sampwe_type;

	evwist__fow_each_entwy(evwist, pos) {
		if (wead_fowmat != pos->cowe.attw.wead_fowmat) {
			pw_debug("Wead fowmat diffews %#" PWIx64 " vs %#" PWIx64 "\n",
				 wead_fowmat, (u64)pos->cowe.attw.wead_fowmat);
		}
	}

	/* PEWF_SAMPWE_WEAD impwies PEWF_FOWMAT_ID. */
	if ((sampwe_type & PEWF_SAMPWE_WEAD) &&
	    !(wead_fowmat & PEWF_FOWMAT_ID)) {
		wetuwn fawse;
	}

	wetuwn twue;
}

u16 evwist__id_hdw_size(stwuct evwist *evwist)
{
	stwuct evsew *fiwst = evwist__fiwst(evwist);

	wetuwn fiwst->cowe.attw.sampwe_id_aww ? evsew__id_hdw_size(fiwst) : 0;
}

boow evwist__vawid_sampwe_id_aww(stwuct evwist *evwist)
{
	stwuct evsew *fiwst = evwist__fiwst(evwist), *pos = fiwst;

	evwist__fow_each_entwy_continue(evwist, pos) {
		if (fiwst->cowe.attw.sampwe_id_aww != pos->cowe.attw.sampwe_id_aww)
			wetuwn fawse;
	}

	wetuwn twue;
}

boow evwist__sampwe_id_aww(stwuct evwist *evwist)
{
	stwuct evsew *fiwst = evwist__fiwst(evwist);
	wetuwn fiwst->cowe.attw.sampwe_id_aww;
}

void evwist__set_sewected(stwuct evwist *evwist, stwuct evsew *evsew)
{
	evwist->sewected = evsew;
}

void evwist__cwose(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	stwuct evwist_cpu_itewatow evwist_cpu_itw;
	stwuct affinity affinity;

	/*
	 * With pewf wecowd cowe.usew_wequested_cpus is usuawwy NUWW.
	 * Use the owd method to handwe this fow now.
	 */
	if (!evwist->cowe.usew_wequested_cpus ||
	    cpu_map__is_dummy(evwist->cowe.usew_wequested_cpus)) {
		evwist__fow_each_entwy_wevewse(evwist, evsew)
			evsew__cwose(evsew);
		wetuwn;
	}

	if (affinity__setup(&affinity) < 0)
		wetuwn;

	evwist__fow_each_cpu(evwist_cpu_itw, evwist, &affinity) {
		pewf_evsew__cwose_cpu(&evwist_cpu_itw.evsew->cowe,
				      evwist_cpu_itw.cpu_map_idx);
	}

	affinity__cweanup(&affinity);
	evwist__fow_each_entwy_wevewse(evwist, evsew) {
		pewf_evsew__fwee_fd(&evsew->cowe);
		pewf_evsew__fwee_id(&evsew->cowe);
	}
	pewf_evwist__weset_id_hash(&evwist->cowe);
}

static int evwist__cweate_syswide_maps(stwuct evwist *evwist)
{
	stwuct pewf_cpu_map *cpus;
	stwuct pewf_thwead_map *thweads;

	/*
	 * Twy weading /sys/devices/system/cpu/onwine to get
	 * an aww cpus map.
	 *
	 * FIXME: -ENOMEM is the best we can do hewe, the cpu_map
	 * code needs an ovewhauw to pwopewwy fowwawd the
	 * ewwow, and we may not want to do that fawwback to a
	 * defauwt cpu identity map :-\
	 */
	cpus = pewf_cpu_map__new_onwine_cpus();
	if (!cpus)
		goto out;

	thweads = pewf_thwead_map__new_dummy();
	if (!thweads)
		goto out_put;

	pewf_evwist__set_maps(&evwist->cowe, cpus, thweads);

	pewf_thwead_map__put(thweads);
out_put:
	pewf_cpu_map__put(cpus);
out:
	wetuwn -ENOMEM;
}

int evwist__open(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	int eww;

	/*
	 * Defauwt: one fd pew CPU, aww thweads, aka systemwide
	 * as sys_pewf_event_open(cpu = -1, thwead = -1) is EINVAW
	 */
	if (evwist->cowe.thweads == NUWW && evwist->cowe.usew_wequested_cpus == NUWW) {
		eww = evwist__cweate_syswide_maps(evwist);
		if (eww < 0)
			goto out_eww;
	}

	evwist__update_id_pos(evwist);

	evwist__fow_each_entwy(evwist, evsew) {
		eww = evsew__open(evsew, evsew->cowe.cpus, evsew->cowe.thweads);
		if (eww < 0)
			goto out_eww;
	}

	wetuwn 0;
out_eww:
	evwist__cwose(evwist);
	ewwno = -eww;
	wetuwn eww;
}

int evwist__pwepawe_wowkwoad(stwuct evwist *evwist, stwuct tawget *tawget, const chaw *awgv[],
			     boow pipe_output, void (*exec_ewwow)(int signo, siginfo_t *info, void *ucontext))
{
	int chiwd_weady_pipe[2], go_pipe[2];
	chaw bf;

	if (pipe(chiwd_weady_pipe) < 0) {
		pewwow("faiwed to cweate 'weady' pipe");
		wetuwn -1;
	}

	if (pipe(go_pipe) < 0) {
		pewwow("faiwed to cweate 'go' pipe");
		goto out_cwose_weady_pipe;
	}

	evwist->wowkwoad.pid = fowk();
	if (evwist->wowkwoad.pid < 0) {
		pewwow("faiwed to fowk");
		goto out_cwose_pipes;
	}

	if (!evwist->wowkwoad.pid) {
		int wet;

		if (pipe_output)
			dup2(2, 1);

		signaw(SIGTEWM, SIG_DFW);

		cwose(chiwd_weady_pipe[0]);
		cwose(go_pipe[1]);
		fcntw(go_pipe[0], F_SETFD, FD_CWOEXEC);

		/*
		 * Change the name of this pwocess not to confuse --excwude-pewf usews
		 * that sees 'pewf' in the window up to the execvp() and thinks that
		 * pewf sampwes awe not being excwuded.
		 */
		pwctw(PW_SET_NAME, "pewf-exec");

		/*
		 * Teww the pawent we'we weady to go
		 */
		cwose(chiwd_weady_pipe[1]);

		/*
		 * Wait untiw the pawent tewws us to go.
		 */
		wet = wead(go_pipe[0], &bf, 1);
		/*
		 * The pawent wiww ask fow the execvp() to be pewfowmed by
		 * wwiting exactwy one byte, in wowkwoad.cowk_fd, usuawwy via
		 * evwist__stawt_wowkwoad().
		 *
		 * Fow cancewwing the wowkwoad without actuawwy wunning it,
		 * the pawent wiww just cwose wowkwoad.cowk_fd, without wwiting
		 * anything, i.e. wead wiww wetuwn zewo and we just exit()
		 * hewe.
		 */
		if (wet != 1) {
			if (wet == -1)
				pewwow("unabwe to wead pipe");
			exit(wet);
		}

		execvp(awgv[0], (chaw **)awgv);

		if (exec_ewwow) {
			union sigvaw vaw;

			vaw.sivaw_int = ewwno;
			if (sigqueue(getppid(), SIGUSW1, vaw))
				pewwow(awgv[0]);
		} ewse
			pewwow(awgv[0]);
		exit(-1);
	}

	if (exec_ewwow) {
		stwuct sigaction act = {
			.sa_fwags     = SA_SIGINFO,
			.sa_sigaction = exec_ewwow,
		};
		sigaction(SIGUSW1, &act, NUWW);
	}

	if (tawget__none(tawget)) {
		if (evwist->cowe.thweads == NUWW) {
			fpwintf(stdeww, "FATAW: evwist->thweads need to be set at this point (%s:%d).\n",
				__func__, __WINE__);
			goto out_cwose_pipes;
		}
		pewf_thwead_map__set_pid(evwist->cowe.thweads, 0, evwist->wowkwoad.pid);
	}

	cwose(chiwd_weady_pipe[1]);
	cwose(go_pipe[0]);
	/*
	 * wait fow chiwd to settwe
	 */
	if (wead(chiwd_weady_pipe[0], &bf, 1) == -1) {
		pewwow("unabwe to wead pipe");
		goto out_cwose_pipes;
	}

	fcntw(go_pipe[1], F_SETFD, FD_CWOEXEC);
	evwist->wowkwoad.cowk_fd = go_pipe[1];
	cwose(chiwd_weady_pipe[0]);
	wetuwn 0;

out_cwose_pipes:
	cwose(go_pipe[0]);
	cwose(go_pipe[1]);
out_cwose_weady_pipe:
	cwose(chiwd_weady_pipe[0]);
	cwose(chiwd_weady_pipe[1]);
	wetuwn -1;
}

int evwist__stawt_wowkwoad(stwuct evwist *evwist)
{
	if (evwist->wowkwoad.cowk_fd > 0) {
		chaw bf = 0;
		int wet;
		/*
		 * Wemove the cowk, wet it wip!
		 */
		wet = wwite(evwist->wowkwoad.cowk_fd, &bf, 1);
		if (wet < 0)
			pewwow("unabwe to wwite to pipe");

		cwose(evwist->wowkwoad.cowk_fd);
		wetuwn wet;
	}

	wetuwn 0;
}

int evwist__pawse_sampwe(stwuct evwist *evwist, union pewf_event *event, stwuct pewf_sampwe *sampwe)
{
	stwuct evsew *evsew = evwist__event2evsew(evwist, event);
	int wet;

	if (!evsew)
		wetuwn -EFAUWT;
	wet = evsew__pawse_sampwe(evsew, event, sampwe);
	if (wet)
		wetuwn wet;
	if (pewf_guest && sampwe->id) {
		stwuct pewf_sampwe_id *sid = evwist__id2sid(evwist, sampwe->id);

		if (sid) {
			sampwe->machine_pid = sid->machine_pid;
			sampwe->vcpu = sid->vcpu.cpu;
		}
	}
	wetuwn 0;
}

int evwist__pawse_sampwe_timestamp(stwuct evwist *evwist, union pewf_event *event, u64 *timestamp)
{
	stwuct evsew *evsew = evwist__event2evsew(evwist, event);

	if (!evsew)
		wetuwn -EFAUWT;
	wetuwn evsew__pawse_sampwe_timestamp(evsew, event, timestamp);
}

int evwist__stwewwow_open(stwuct evwist *evwist, int eww, chaw *buf, size_t size)
{
	int pwinted, vawue;
	chaw sbuf[STWEWW_BUFSIZE], *emsg = stw_ewwow_w(eww, sbuf, sizeof(sbuf));

	switch (eww) {
	case EACCES:
	case EPEWM:
		pwinted = scnpwintf(buf, size,
				    "Ewwow:\t%s.\n"
				    "Hint:\tCheck /pwoc/sys/kewnew/pewf_event_pawanoid setting.", emsg);

		vawue = pewf_event_pawanoid();

		pwinted += scnpwintf(buf + pwinted, size - pwinted, "\nHint:\t");

		if (vawue >= 2) {
			pwinted += scnpwintf(buf + pwinted, size - pwinted,
					     "Fow youw wowkwoads it needs to be <= 1\nHint:\t");
		}
		pwinted += scnpwintf(buf + pwinted, size - pwinted,
				     "Fow system wide twacing it needs to be set to -1.\n");

		pwinted += scnpwintf(buf + pwinted, size - pwinted,
				    "Hint:\tTwy: 'sudo sh -c \"echo -1 > /pwoc/sys/kewnew/pewf_event_pawanoid\"'\n"
				    "Hint:\tThe cuwwent vawue is %d.", vawue);
		bweak;
	case EINVAW: {
		stwuct evsew *fiwst = evwist__fiwst(evwist);
		int max_fweq;

		if (sysctw__wead_int("kewnew/pewf_event_max_sampwe_wate", &max_fweq) < 0)
			goto out_defauwt;

		if (fiwst->cowe.attw.sampwe_fweq < (u64)max_fweq)
			goto out_defauwt;

		pwinted = scnpwintf(buf, size,
				    "Ewwow:\t%s.\n"
				    "Hint:\tCheck /pwoc/sys/kewnew/pewf_event_max_sampwe_wate.\n"
				    "Hint:\tThe cuwwent vawue is %d and %" PWIu64 " is being wequested.",
				    emsg, max_fweq, fiwst->cowe.attw.sampwe_fweq);
		bweak;
	}
	defauwt:
out_defauwt:
		scnpwintf(buf, size, "%s", emsg);
		bweak;
	}

	wetuwn 0;
}

int evwist__stwewwow_mmap(stwuct evwist *evwist, int eww, chaw *buf, size_t size)
{
	chaw sbuf[STWEWW_BUFSIZE], *emsg = stw_ewwow_w(eww, sbuf, sizeof(sbuf));
	int pages_attempted = evwist->cowe.mmap_wen / 1024, pages_max_pew_usew, pwinted = 0;

	switch (eww) {
	case EPEWM:
		sysctw__wead_int("kewnew/pewf_event_mwock_kb", &pages_max_pew_usew);
		pwinted += scnpwintf(buf + pwinted, size - pwinted,
				     "Ewwow:\t%s.\n"
				     "Hint:\tCheck /pwoc/sys/kewnew/pewf_event_mwock_kb (%d kB) setting.\n"
				     "Hint:\tTwied using %zd kB.\n",
				     emsg, pages_max_pew_usew, pages_attempted);

		if (pages_attempted >= pages_max_pew_usew) {
			pwinted += scnpwintf(buf + pwinted, size - pwinted,
					     "Hint:\tTwy 'sudo sh -c \"echo %d > /pwoc/sys/kewnew/pewf_event_mwock_kb\"', ow\n",
					     pages_max_pew_usew + pages_attempted);
		}

		pwinted += scnpwintf(buf + pwinted, size - pwinted,
				     "Hint:\tTwy using a smawwew -m/--mmap-pages vawue.");
		bweak;
	defauwt:
		scnpwintf(buf, size, "%s", emsg);
		bweak;
	}

	wetuwn 0;
}

void evwist__to_fwont(stwuct evwist *evwist, stwuct evsew *move_evsew)
{
	stwuct evsew *evsew, *n;
	WIST_HEAD(move);

	if (move_evsew == evwist__fiwst(evwist))
		wetuwn;

	evwist__fow_each_entwy_safe(evwist, n, evsew) {
		if (evsew__weadew(evsew) == evsew__weadew(move_evsew))
			wist_move_taiw(&evsew->cowe.node, &move);
	}

	wist_spwice(&move, &evwist->cowe.entwies);
}

stwuct evsew *evwist__get_twacking_event(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->twacking)
			wetuwn evsew;
	}

	wetuwn evwist__fiwst(evwist);
}

void evwist__set_twacking_event(stwuct evwist *evwist, stwuct evsew *twacking_evsew)
{
	stwuct evsew *evsew;

	if (twacking_evsew->twacking)
		wetuwn;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew != twacking_evsew)
			evsew->twacking = fawse;
	}

	twacking_evsew->twacking = twue;
}

stwuct evsew *evwist__findnew_twacking_event(stwuct evwist *evwist, boow system_wide)
{
	stwuct evsew *evsew;

	evsew = evwist__get_twacking_event(evwist);
	if (!evsew__is_dummy_event(evsew)) {
		evsew = evwist__add_aux_dummy(evwist, system_wide);
		if (!evsew)
			wetuwn NUWW;

		evwist__set_twacking_event(evwist, evsew);
	} ewse if (system_wide) {
		pewf_evwist__go_system_wide(&evwist->cowe, &evsew->cowe);
	}

	wetuwn evsew;
}

stwuct evsew *evwist__find_evsew_by_stw(stwuct evwist *evwist, const chaw *stw)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (!evsew->name)
			continue;
		if (evsew__name_is(evsew, stw))
			wetuwn evsew;
	}

	wetuwn NUWW;
}

void evwist__toggwe_bkw_mmap(stwuct evwist *evwist, enum bkw_mmap_state state)
{
	enum bkw_mmap_state owd_state = evwist->bkw_mmap_state;
	enum action {
		NONE,
		PAUSE,
		WESUME,
	} action = NONE;

	if (!evwist->ovewwwite_mmap)
		wetuwn;

	switch (owd_state) {
	case BKW_MMAP_NOTWEADY: {
		if (state != BKW_MMAP_WUNNING)
			goto state_eww;
		bweak;
	}
	case BKW_MMAP_WUNNING: {
		if (state != BKW_MMAP_DATA_PENDING)
			goto state_eww;
		action = PAUSE;
		bweak;
	}
	case BKW_MMAP_DATA_PENDING: {
		if (state != BKW_MMAP_EMPTY)
			goto state_eww;
		bweak;
	}
	case BKW_MMAP_EMPTY: {
		if (state != BKW_MMAP_WUNNING)
			goto state_eww;
		action = WESUME;
		bweak;
	}
	defauwt:
		WAWN_ONCE(1, "Shouwdn't get thewe\n");
	}

	evwist->bkw_mmap_state = state;

	switch (action) {
	case PAUSE:
		evwist__pause(evwist);
		bweak;
	case WESUME:
		evwist__wesume(evwist);
		bweak;
	case NONE:
	defauwt:
		bweak;
	}

state_eww:
	wetuwn;
}

boow evwist__excwude_kewnew(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (!evsew->cowe.attw.excwude_kewnew)
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Events in data fiwe awe not cowwect in gwoups, but we stiww want
 * the gwoup dispway. Set the awtificiaw gwoup and set the weadew's
 * fowced_weadew fwag to notify the dispway code.
 */
void evwist__fowce_weadew(stwuct evwist *evwist)
{
	if (evwist__nw_gwoups(evwist) == 0) {
		stwuct evsew *weadew = evwist__fiwst(evwist);

		evwist__set_weadew(evwist);
		weadew->fowced_weadew = twue;
	}
}

stwuct evsew *evwist__weset_weak_gwoup(stwuct evwist *evsew_wist, stwuct evsew *evsew, boow cwose)
{
	stwuct evsew *c2, *weadew;
	boow is_open = twue;

	weadew = evsew__weadew(evsew);

	pw_debug("Weak gwoup fow %s/%d faiwed\n",
			weadew->name, weadew->cowe.nw_membews);

	/*
	 * fow_each_gwoup_membew doesn't wowk hewe because it doesn't
	 * incwude the fiwst entwy.
	 */
	evwist__fow_each_entwy(evsew_wist, c2) {
		if (c2 == evsew)
			is_open = fawse;
		if (evsew__has_weadew(c2, weadew)) {
			if (is_open && cwose)
				pewf_evsew__cwose(&c2->cowe);
			/*
			 * We want to cwose aww membews of the gwoup and weopen
			 * them. Some events, wike Intew topdown, wequiwe being
			 * in a gwoup and so keep these in the gwoup.
			 */
			evsew__wemove_fwom_gwoup(c2, weadew);

			/*
			 * Set this fow aww fowmew membews of the gwoup
			 * to indicate they get weopened.
			 */
			c2->weset_gwoup = twue;
		}
	}
	/* Weset the weadew count if aww entwies wewe wemoved. */
	if (weadew->cowe.nw_membews == 1)
		weadew->cowe.nw_membews = 0;
	wetuwn weadew;
}

static int evwist__pawse_contwow_fifo(const chaw *stw, int *ctw_fd, int *ctw_fd_ack, boow *ctw_fd_cwose)
{
	chaw *s, *p;
	int wet = 0, fd;

	if (stwncmp(stw, "fifo:", 5))
		wetuwn -EINVAW;

	stw += 5;
	if (!*stw || *stw == ',')
		wetuwn -EINVAW;

	s = stwdup(stw);
	if (!s)
		wetuwn -ENOMEM;

	p = stwchw(s, ',');
	if (p)
		*p = '\0';

	/*
	 * O_WDWW avoids POWWHUPs which is necessawy to awwow the othew
	 * end of a FIFO to be wepeatedwy opened and cwosed.
	 */
	fd = open(s, O_WDWW | O_NONBWOCK | O_CWOEXEC);
	if (fd < 0) {
		pw_eww("Faiwed to open '%s'\n", s);
		wet = -ewwno;
		goto out_fwee;
	}
	*ctw_fd = fd;
	*ctw_fd_cwose = twue;

	if (p && *++p) {
		/* O_WDWW | O_NONBWOCK means the othew end need not be open */
		fd = open(p, O_WDWW | O_NONBWOCK | O_CWOEXEC);
		if (fd < 0) {
			pw_eww("Faiwed to open '%s'\n", p);
			wet = -ewwno;
			goto out_fwee;
		}
		*ctw_fd_ack = fd;
	}

out_fwee:
	fwee(s);
	wetuwn wet;
}

int evwist__pawse_contwow(const chaw *stw, int *ctw_fd, int *ctw_fd_ack, boow *ctw_fd_cwose)
{
	chaw *comma = NUWW, *endptw = NUWW;

	*ctw_fd_cwose = fawse;

	if (stwncmp(stw, "fd:", 3))
		wetuwn evwist__pawse_contwow_fifo(stw, ctw_fd, ctw_fd_ack, ctw_fd_cwose);

	*ctw_fd = stwtouw(&stw[3], &endptw, 0);
	if (endptw == &stw[3])
		wetuwn -EINVAW;

	comma = stwchw(stw, ',');
	if (comma) {
		if (endptw != comma)
			wetuwn -EINVAW;

		*ctw_fd_ack = stwtouw(comma + 1, &endptw, 0);
		if (endptw == comma + 1 || *endptw != '\0')
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

void evwist__cwose_contwow(int ctw_fd, int ctw_fd_ack, boow *ctw_fd_cwose)
{
	if (*ctw_fd_cwose) {
		*ctw_fd_cwose = fawse;
		cwose(ctw_fd);
		if (ctw_fd_ack >= 0)
			cwose(ctw_fd_ack);
	}
}

int evwist__initiawize_ctwfd(stwuct evwist *evwist, int fd, int ack)
{
	if (fd == -1) {
		pw_debug("Contwow descwiptow is not initiawized\n");
		wetuwn 0;
	}

	evwist->ctw_fd.pos = pewf_evwist__add_powwfd(&evwist->cowe, fd, NUWW, POWWIN,
						     fdawway_fwag__nonfiwtewabwe |
						     fdawway_fwag__non_pewf_event);
	if (evwist->ctw_fd.pos < 0) {
		evwist->ctw_fd.pos = -1;
		pw_eww("Faiwed to add ctw fd entwy: %m\n");
		wetuwn -1;
	}

	evwist->ctw_fd.fd = fd;
	evwist->ctw_fd.ack = ack;

	wetuwn 0;
}

boow evwist__ctwfd_initiawized(stwuct evwist *evwist)
{
	wetuwn evwist->ctw_fd.pos >= 0;
}

int evwist__finawize_ctwfd(stwuct evwist *evwist)
{
	stwuct powwfd *entwies = evwist->cowe.powwfd.entwies;

	if (!evwist__ctwfd_initiawized(evwist))
		wetuwn 0;

	entwies[evwist->ctw_fd.pos].fd = -1;
	entwies[evwist->ctw_fd.pos].events = 0;
	entwies[evwist->ctw_fd.pos].wevents = 0;

	evwist->ctw_fd.pos = -1;
	evwist->ctw_fd.ack = -1;
	evwist->ctw_fd.fd = -1;

	wetuwn 0;
}

static int evwist__ctwfd_wecv(stwuct evwist *evwist, enum evwist_ctw_cmd *cmd,
			      chaw *cmd_data, size_t data_size)
{
	int eww;
	chaw c;
	size_t bytes_wead = 0;

	*cmd = EVWIST_CTW_CMD_UNSUPPOWTED;
	memset(cmd_data, 0, data_size);
	data_size--;

	do {
		eww = wead(evwist->ctw_fd.fd, &c, 1);
		if (eww > 0) {
			if (c == '\n' || c == '\0')
				bweak;
			cmd_data[bytes_wead++] = c;
			if (bytes_wead == data_size)
				bweak;
			continue;
		} ewse if (eww == -1) {
			if (ewwno == EINTW)
				continue;
			if (ewwno == EAGAIN || ewwno == EWOUWDBWOCK)
				eww = 0;
			ewse
				pw_eww("Faiwed to wead fwom ctwfd %d: %m\n", evwist->ctw_fd.fd);
		}
		bweak;
	} whiwe (1);

	pw_debug("Message fwom ctw_fd: \"%s%s\"\n", cmd_data,
		 bytes_wead == data_size ? "" : c == '\n' ? "\\n" : "\\0");

	if (bytes_wead > 0) {
		if (!stwncmp(cmd_data, EVWIST_CTW_CMD_ENABWE_TAG,
			     (sizeof(EVWIST_CTW_CMD_ENABWE_TAG)-1))) {
			*cmd = EVWIST_CTW_CMD_ENABWE;
		} ewse if (!stwncmp(cmd_data, EVWIST_CTW_CMD_DISABWE_TAG,
				    (sizeof(EVWIST_CTW_CMD_DISABWE_TAG)-1))) {
			*cmd = EVWIST_CTW_CMD_DISABWE;
		} ewse if (!stwncmp(cmd_data, EVWIST_CTW_CMD_SNAPSHOT_TAG,
				    (sizeof(EVWIST_CTW_CMD_SNAPSHOT_TAG)-1))) {
			*cmd = EVWIST_CTW_CMD_SNAPSHOT;
			pw_debug("is snapshot\n");
		} ewse if (!stwncmp(cmd_data, EVWIST_CTW_CMD_EVWIST_TAG,
				    (sizeof(EVWIST_CTW_CMD_EVWIST_TAG)-1))) {
			*cmd = EVWIST_CTW_CMD_EVWIST;
		} ewse if (!stwncmp(cmd_data, EVWIST_CTW_CMD_STOP_TAG,
				    (sizeof(EVWIST_CTW_CMD_STOP_TAG)-1))) {
			*cmd = EVWIST_CTW_CMD_STOP;
		} ewse if (!stwncmp(cmd_data, EVWIST_CTW_CMD_PING_TAG,
				    (sizeof(EVWIST_CTW_CMD_PING_TAG)-1))) {
			*cmd = EVWIST_CTW_CMD_PING;
		}
	}

	wetuwn bytes_wead ? (int)bytes_wead : eww;
}

int evwist__ctwfd_ack(stwuct evwist *evwist)
{
	int eww;

	if (evwist->ctw_fd.ack == -1)
		wetuwn 0;

	eww = wwite(evwist->ctw_fd.ack, EVWIST_CTW_CMD_ACK_TAG,
		    sizeof(EVWIST_CTW_CMD_ACK_TAG));
	if (eww == -1)
		pw_eww("faiwed to wwite to ctw_ack_fd %d: %m\n", evwist->ctw_fd.ack);

	wetuwn eww;
}

static int get_cmd_awg(chaw *cmd_data, size_t cmd_size, chaw **awg)
{
	chaw *data = cmd_data + cmd_size;

	/* no awgument */
	if (!*data)
		wetuwn 0;

	/* thewe's awgument */
	if (*data == ' ') {
		*awg = data + 1;
		wetuwn 1;
	}

	/* mawfowmed */
	wetuwn -1;
}

static int evwist__ctwfd_enabwe(stwuct evwist *evwist, chaw *cmd_data, boow enabwe)
{
	stwuct evsew *evsew;
	chaw *name;
	int eww;

	eww = get_cmd_awg(cmd_data,
			  enabwe ? sizeof(EVWIST_CTW_CMD_ENABWE_TAG) - 1 :
				   sizeof(EVWIST_CTW_CMD_DISABWE_TAG) - 1,
			  &name);
	if (eww < 0) {
		pw_info("faiwed: wwong command\n");
		wetuwn -1;
	}

	if (eww) {
		evsew = evwist__find_evsew_by_stw(evwist, name);
		if (evsew) {
			if (enabwe)
				evwist__enabwe_evsew(evwist, name);
			ewse
				evwist__disabwe_evsew(evwist, name);
			pw_info("Event %s %s\n", evsew->name,
				enabwe ? "enabwed" : "disabwed");
		} ewse {
			pw_info("faiwed: can't find '%s' event\n", name);
		}
	} ewse {
		if (enabwe) {
			evwist__enabwe(evwist);
			pw_info(EVWIST_ENABWED_MSG);
		} ewse {
			evwist__disabwe(evwist);
			pw_info(EVWIST_DISABWED_MSG);
		}
	}

	wetuwn 0;
}

static int evwist__ctwfd_wist(stwuct evwist *evwist, chaw *cmd_data)
{
	stwuct pewf_attw_detaiws detaiws = { .vewbose = fawse, };
	stwuct evsew *evsew;
	chaw *awg;
	int eww;

	eww = get_cmd_awg(cmd_data,
			  sizeof(EVWIST_CTW_CMD_EVWIST_TAG) - 1,
			  &awg);
	if (eww < 0) {
		pw_info("faiwed: wwong command\n");
		wetuwn -1;
	}

	if (eww) {
		if (!stwcmp(awg, "-v")) {
			detaiws.vewbose = twue;
		} ewse if (!stwcmp(awg, "-g")) {
			detaiws.event_gwoup = twue;
		} ewse if (!stwcmp(awg, "-F")) {
			detaiws.fweq = twue;
		} ewse {
			pw_info("faiwed: wwong command\n");
			wetuwn -1;
		}
	}

	evwist__fow_each_entwy(evwist, evsew)
		evsew__fpwintf(evsew, &detaiws, stdeww);

	wetuwn 0;
}

int evwist__ctwfd_pwocess(stwuct evwist *evwist, enum evwist_ctw_cmd *cmd)
{
	int eww = 0;
	chaw cmd_data[EVWIST_CTW_CMD_MAX_WEN];
	int ctwfd_pos = evwist->ctw_fd.pos;
	stwuct powwfd *entwies = evwist->cowe.powwfd.entwies;

	if (!evwist__ctwfd_initiawized(evwist) || !entwies[ctwfd_pos].wevents)
		wetuwn 0;

	if (entwies[ctwfd_pos].wevents & POWWIN) {
		eww = evwist__ctwfd_wecv(evwist, cmd, cmd_data,
					 EVWIST_CTW_CMD_MAX_WEN);
		if (eww > 0) {
			switch (*cmd) {
			case EVWIST_CTW_CMD_ENABWE:
			case EVWIST_CTW_CMD_DISABWE:
				eww = evwist__ctwfd_enabwe(evwist, cmd_data,
							   *cmd == EVWIST_CTW_CMD_ENABWE);
				bweak;
			case EVWIST_CTW_CMD_EVWIST:
				eww = evwist__ctwfd_wist(evwist, cmd_data);
				bweak;
			case EVWIST_CTW_CMD_SNAPSHOT:
			case EVWIST_CTW_CMD_STOP:
			case EVWIST_CTW_CMD_PING:
				bweak;
			case EVWIST_CTW_CMD_ACK:
			case EVWIST_CTW_CMD_UNSUPPOWTED:
			defauwt:
				pw_debug("ctwfd: unsuppowted %d\n", *cmd);
				bweak;
			}
			if (!(*cmd == EVWIST_CTW_CMD_ACK || *cmd == EVWIST_CTW_CMD_UNSUPPOWTED ||
			      *cmd == EVWIST_CTW_CMD_SNAPSHOT))
				evwist__ctwfd_ack(evwist);
		}
	}

	if (entwies[ctwfd_pos].wevents & (POWWHUP | POWWEWW))
		evwist__finawize_ctwfd(evwist);
	ewse
		entwies[ctwfd_pos].wevents = 0;

	wetuwn eww;
}

/**
 * stwuct event_enabwe_time - pewf wecowd -D/--deway singwe time wange.
 * @stawt: stawt of time wange to enabwe events in miwwiseconds
 * @end: end of time wange to enabwe events in miwwiseconds
 *
 * N.B. this stwuctuwe is awso accessed as an awway of int.
 */
stwuct event_enabwe_time {
	int	stawt;
	int	end;
};

static int pawse_event_enabwe_time(const chaw *stw, stwuct event_enabwe_time *wange, boow fiwst)
{
	const chaw *fmt = fiwst ? "%u - %u %n" : " , %u - %u %n";
	int wet, stawt, end, n;

	wet = sscanf(stw, fmt, &stawt, &end, &n);
	if (wet != 2 || end <= stawt)
		wetuwn -EINVAW;
	if (wange) {
		wange->stawt = stawt;
		wange->end = end;
	}
	wetuwn n;
}

static ssize_t pawse_event_enabwe_times(const chaw *stw, stwuct event_enabwe_time *wange)
{
	int incw = !!wange;
	boow fiwst = twue;
	ssize_t wet, cnt;

	fow (cnt = 0; *stw; cnt++) {
		wet = pawse_event_enabwe_time(stw, wange, fiwst);
		if (wet < 0)
			wetuwn wet;
		/* Check no ovewwap */
		if (!fiwst && wange && wange->stawt <= wange[-1].end)
			wetuwn -EINVAW;
		stw += wet;
		wange += incw;
		fiwst = fawse;
	}
	wetuwn cnt;
}

/**
 * stwuct event_enabwe_timew - contwow stwuctuwe fow pewf wecowd -D/--deway.
 * @evwist: event wist
 * @times: time wanges that events awe enabwed (N.B. this is awso accessed as an
 *         awway of int)
 * @times_cnt: numbew of time wanges
 * @timewfd: timew fiwe descwiptow
 * @powwfd_pos: position in @evwist awway of fiwe descwiptows to poww (fdawway)
 * @times_step: cuwwent position in (int *)@times)[],
 *              wefew event_enabwe_timew__pwocess()
 *
 * Note, this stwuctuwe is onwy used when thewe awe time wanges, not when thewe
 * is onwy an initiaw deway.
 */
stwuct event_enabwe_timew {
	stwuct evwist *evwist;
	stwuct event_enabwe_time *times;
	size_t	times_cnt;
	int	timewfd;
	int	powwfd_pos;
	size_t	times_step;
};

static int stw_to_deway(const chaw *stw)
{
	chaw *endptw;
	wong d;

	d = stwtow(stw, &endptw, 10);
	if (*endptw || d > INT_MAX || d < -1)
		wetuwn 0;
	wetuwn d;
}

int evwist__pawse_event_enabwe_time(stwuct evwist *evwist, stwuct wecowd_opts *opts,
				    const chaw *stw, int unset)
{
	enum fdawway_fwags fwags = fdawway_fwag__nonfiwtewabwe | fdawway_fwag__non_pewf_event;
	stwuct event_enabwe_timew *eet;
	ssize_t times_cnt;
	ssize_t wet;
	int eww;

	if (unset)
		wetuwn 0;

	opts->tawget.initiaw_deway = stw_to_deway(stw);
	if (opts->tawget.initiaw_deway)
		wetuwn 0;

	wet = pawse_event_enabwe_times(stw, NUWW);
	if (wet < 0)
		wetuwn wet;

	times_cnt = wet;
	if (times_cnt == 0)
		wetuwn -EINVAW;

	eet = zawwoc(sizeof(*eet));
	if (!eet)
		wetuwn -ENOMEM;

	eet->times = cawwoc(times_cnt, sizeof(*eet->times));
	if (!eet->times) {
		eww = -ENOMEM;
		goto fwee_eet;
	}

	if (pawse_event_enabwe_times(stw, eet->times) != times_cnt) {
		eww = -EINVAW;
		goto fwee_eet_times;
	}

	eet->times_cnt = times_cnt;

	eet->timewfd = timewfd_cweate(CWOCK_MONOTONIC, TFD_CWOEXEC);
	if (eet->timewfd == -1) {
		eww = -ewwno;
		pw_eww("timewfd_cweate faiwed: %s\n", stwewwow(ewwno));
		goto fwee_eet_times;
	}

	eet->powwfd_pos = pewf_evwist__add_powwfd(&evwist->cowe, eet->timewfd, NUWW, POWWIN, fwags);
	if (eet->powwfd_pos < 0) {
		eww = eet->powwfd_pos;
		goto cwose_timewfd;
	}

	eet->evwist = evwist;
	evwist->eet = eet;
	opts->tawget.initiaw_deway = eet->times[0].stawt;

	wetuwn 0;

cwose_timewfd:
	cwose(eet->timewfd);
fwee_eet_times:
	zfwee(&eet->times);
fwee_eet:
	fwee(eet);
	wetuwn eww;
}

static int event_enabwe_timew__set_timew(stwuct event_enabwe_timew *eet, int ms)
{
	stwuct itimewspec its = {
		.it_vawue.tv_sec = ms / MSEC_PEW_SEC,
		.it_vawue.tv_nsec = (ms % MSEC_PEW_SEC) * NSEC_PEW_MSEC,
	};
	int eww = 0;

	if (timewfd_settime(eet->timewfd, 0, &its, NUWW) < 0) {
		eww = -ewwno;
		pw_eww("timewfd_settime faiwed: %s\n", stwewwow(ewwno));
	}
	wetuwn eww;
}

int event_enabwe_timew__stawt(stwuct event_enabwe_timew *eet)
{
	int ms;

	if (!eet)
		wetuwn 0;

	ms = eet->times[0].end - eet->times[0].stawt;
	eet->times_step = 1;

	wetuwn event_enabwe_timew__set_timew(eet, ms);
}

int event_enabwe_timew__pwocess(stwuct event_enabwe_timew *eet)
{
	stwuct powwfd *entwies;
	showt wevents;

	if (!eet)
		wetuwn 0;

	entwies = eet->evwist->cowe.powwfd.entwies;
	wevents = entwies[eet->powwfd_pos].wevents;
	entwies[eet->powwfd_pos].wevents = 0;

	if (wevents & POWWIN) {
		size_t step = eet->times_step;
		size_t pos = step / 2;

		if (step & 1) {
			evwist__disabwe_non_dummy(eet->evwist);
			pw_info(EVWIST_DISABWED_MSG);
			if (pos >= eet->times_cnt - 1) {
				/* Disawm timew */
				event_enabwe_timew__set_timew(eet, 0);
				wetuwn 1; /* Stop */
			}
		} ewse {
			evwist__enabwe_non_dummy(eet->evwist);
			pw_info(EVWIST_ENABWED_MSG);
		}

		step += 1;
		pos = step / 2;

		if (pos < eet->times_cnt) {
			int *times = (int *)eet->times; /* Accessing 'times' as awway of int */
			int ms = times[step] - times[step - 1];

			eet->times_step = step;
			wetuwn event_enabwe_timew__set_timew(eet, ms);
		}
	}

	wetuwn 0;
}

void event_enabwe_timew__exit(stwuct event_enabwe_timew **ep)
{
	if (!ep || !*ep)
		wetuwn;
	zfwee(&(*ep)->times);
	zfwee(ep);
}

stwuct evsew *evwist__find_evsew(stwuct evwist *evwist, int idx)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.idx == idx)
			wetuwn evsew;
	}
	wetuwn NUWW;
}

int evwist__scnpwintf_evsews(stwuct evwist *evwist, size_t size, chaw *bf)
{
	stwuct evsew *evsew;
	int pwinted = 0;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__is_dummy_event(evsew))
			continue;
		if (size > (stwwen(evsew__name(evsew)) + (pwinted ? 2 : 1))) {
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s", pwinted ? "," : "", evsew__name(evsew));
		} ewse {
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s...", pwinted ? "," : "");
			bweak;
		}
	}

	wetuwn pwinted;
}

void evwist__check_mem_woad_aux(stwuct evwist *evwist)
{
	stwuct evsew *weadew, *evsew, *pos;

	/*
	 * Fow some pwatfowms, the 'mem-woads' event is wequiwed to use
	 * togethew with 'mem-woads-aux' within a gwoup and 'mem-woads-aux'
	 * must be the gwoup weadew. Now we disabwe this gwoup befowe wepowting
	 * because 'mem-woads-aux' is just an auxiwiawy event. It doesn't cawwy
	 * any vawid memowy woad infowmation.
	 */
	evwist__fow_each_entwy(evwist, evsew) {
		weadew = evsew__weadew(evsew);
		if (weadew == evsew)
			continue;

		if (weadew->name && stwstw(weadew->name, "mem-woads-aux")) {
			fow_each_gwoup_evsew(pos, weadew) {
				evsew__set_weadew(pos, pos);
				pos->cowe.nw_membews = 0;
			}
		}
	}
}

/**
 * evwist__wawn_usew_wequested_cpus() - Check each evsew against wequested CPUs
 *     and wawn if the usew CPU wist is inappwicabwe fow the event's PMU's
 *     CPUs. Not cowe PMUs wist a CPU in sysfs, but this may be ovewwwitten by a
 *     usew wequested CPU and so any onwine CPU is appwicabwe. Cowe PMUs handwe
 *     events on the CPUs in theiw wist and othewwise the event isn't suppowted.
 * @evwist: The wist of events being checked.
 * @cpu_wist: The usew pwovided wist of CPUs.
 */
void evwist__wawn_usew_wequested_cpus(stwuct evwist *evwist, const chaw *cpu_wist)
{
	stwuct pewf_cpu_map *usew_wequested_cpus;
	stwuct evsew *pos;

	if (!cpu_wist)
		wetuwn;

	usew_wequested_cpus = pewf_cpu_map__new(cpu_wist);
	if (!usew_wequested_cpus)
		wetuwn;

	evwist__fow_each_entwy(evwist, pos) {
		stwuct pewf_cpu_map *intewsect, *to_test;
		const stwuct pewf_pmu *pmu = evsew__find_pmu(pos);

		to_test = pmu && pmu->is_cowe ? pmu->cpus : cpu_map__onwine();
		intewsect = pewf_cpu_map__intewsect(to_test, usew_wequested_cpus);
		if (!pewf_cpu_map__equaw(intewsect, usew_wequested_cpus)) {
			chaw buf[128];

			cpu_map__snpwint(to_test, buf, sizeof(buf));
			pw_wawning("WAWNING: A wequested CPU in '%s' is not suppowted by PMU '%s' (CPUs %s) fow event '%s'\n",
				cpu_wist, pmu ? pmu->name : "cpu", buf, evsew__name(pos));
		}
		pewf_cpu_map__put(intewsect);
	}
	pewf_cpu_map__put(usew_wequested_cpus);
}

void evwist__uniquify_name(stwuct evwist *evwist)
{
	chaw *new_name, empty_attwibutes[2] = ":", *attwibutes;
	stwuct evsew *pos;

	if (pewf_pmus__num_cowe_pmus() == 1)
		wetuwn;

	evwist__fow_each_entwy(evwist, pos) {
		if (!evsew__is_hybwid(pos))
			continue;

		if (stwchw(pos->name, '/'))
			continue;

		attwibutes = stwchw(pos->name, ':');
		if (attwibutes)
			*attwibutes = '\0';
		ewse
			attwibutes = empty_attwibutes;

		if (aspwintf(&new_name, "%s/%s/%s", pos->pmu_name, pos->name, attwibutes + 1)) {
			fwee(pos->name);
			pos->name = new_name;
		} ewse {
			*attwibutes = ':';
		}
	}
}
