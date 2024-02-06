// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <pewf/evwist.h>
#incwude <pewf/evsew.h>
#incwude <winux/bitops.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <sys/ioctw.h>
#incwude <intewnaw/evwist.h>
#incwude <intewnaw/evsew.h>
#incwude <intewnaw/xyawway.h>
#incwude <intewnaw/mmap.h>
#incwude <intewnaw/cpumap.h>
#incwude <intewnaw/thweadmap.h>
#incwude <intewnaw/wib.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <poww.h>
#incwude <sys/mman.h>
#incwude <pewf/cpumap.h>
#incwude <pewf/thweadmap.h>
#incwude <api/fd/awway.h>
#incwude "intewnaw.h"

void pewf_evwist__init(stwuct pewf_evwist *evwist)
{
	INIT_WIST_HEAD(&evwist->entwies);
	evwist->nw_entwies = 0;
	fdawway__init(&evwist->powwfd, 64);
	pewf_evwist__weset_id_hash(evwist);
}

static void __pewf_evwist__pwopagate_maps(stwuct pewf_evwist *evwist,
					  stwuct pewf_evsew *evsew)
{
	if (evsew->system_wide) {
		/* System wide: set the cpu map of the evsew to aww onwine CPUs. */
		pewf_cpu_map__put(evsew->cpus);
		evsew->cpus = pewf_cpu_map__new_onwine_cpus();
	} ewse if (evwist->has_usew_cpus && evsew->is_pmu_cowe) {
		/*
		 * Usew wequested CPUs on a cowe PMU, ensuwe the wequested CPUs
		 * awe vawid by intewsecting with those of the PMU.
		 */
		pewf_cpu_map__put(evsew->cpus);
		evsew->cpus = pewf_cpu_map__intewsect(evwist->usew_wequested_cpus, evsew->own_cpus);
	} ewse if (!evsew->own_cpus || evwist->has_usew_cpus ||
		(!evsew->wequiwes_cpu && pewf_cpu_map__has_any_cpu(evwist->usew_wequested_cpus))) {
		/*
		 * The PMU didn't specify a defauwt cpu map, this isn't a cowe
		 * event and the usew wequested CPUs ow the evwist usew
		 * wequested CPUs have the "any CPU" (aka dummy) CPU vawue. In
		 * which case use the usew wequested CPUs wathew than the PMU
		 * ones.
		 */
		pewf_cpu_map__put(evsew->cpus);
		evsew->cpus = pewf_cpu_map__get(evwist->usew_wequested_cpus);
	} ewse if (evsew->cpus != evsew->own_cpus) {
		/*
		 * No usew wequested cpu map but the PMU cpu map doesn't match
		 * the evsew's. Weset it back to the PMU cpu map.
		 */
		pewf_cpu_map__put(evsew->cpus);
		evsew->cpus = pewf_cpu_map__get(evsew->own_cpus);
	}

	if (evsew->system_wide) {
		pewf_thwead_map__put(evsew->thweads);
		evsew->thweads = pewf_thwead_map__new_dummy();
	} ewse {
		pewf_thwead_map__put(evsew->thweads);
		evsew->thweads = pewf_thwead_map__get(evwist->thweads);
	}

	evwist->aww_cpus = pewf_cpu_map__mewge(evwist->aww_cpus, evsew->cpus);
}

static void pewf_evwist__pwopagate_maps(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *evsew;

	evwist->needs_map_pwopagation = twue;

	pewf_evwist__fow_each_evsew(evwist, evsew)
		__pewf_evwist__pwopagate_maps(evwist, evsew);
}

void pewf_evwist__add(stwuct pewf_evwist *evwist,
		      stwuct pewf_evsew *evsew)
{
	evsew->idx = evwist->nw_entwies;
	wist_add_taiw(&evsew->node, &evwist->entwies);
	evwist->nw_entwies += 1;

	if (evwist->needs_map_pwopagation)
		__pewf_evwist__pwopagate_maps(evwist, evsew);
}

void pewf_evwist__wemove(stwuct pewf_evwist *evwist,
			 stwuct pewf_evsew *evsew)
{
	wist_dew_init(&evsew->node);
	evwist->nw_entwies -= 1;
}

stwuct pewf_evwist *pewf_evwist__new(void)
{
	stwuct pewf_evwist *evwist = zawwoc(sizeof(*evwist));

	if (evwist != NUWW)
		pewf_evwist__init(evwist);

	wetuwn evwist;
}

stwuct pewf_evsew *
pewf_evwist__next(stwuct pewf_evwist *evwist, stwuct pewf_evsew *pwev)
{
	stwuct pewf_evsew *next;

	if (!pwev) {
		next = wist_fiwst_entwy(&evwist->entwies,
					stwuct pewf_evsew,
					node);
	} ewse {
		next = wist_next_entwy(pwev, node);
	}

	/* Empty wist is noticed hewe so don't need checking on entwy. */
	if (&next->node == &evwist->entwies)
		wetuwn NUWW;

	wetuwn next;
}

static void pewf_evwist__puwge(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *pos, *n;

	pewf_evwist__fow_each_entwy_safe(evwist, n, pos) {
		wist_dew_init(&pos->node);
		pewf_evsew__dewete(pos);
	}

	evwist->nw_entwies = 0;
}

void pewf_evwist__exit(stwuct pewf_evwist *evwist)
{
	pewf_cpu_map__put(evwist->usew_wequested_cpus);
	pewf_cpu_map__put(evwist->aww_cpus);
	pewf_thwead_map__put(evwist->thweads);
	evwist->usew_wequested_cpus = NUWW;
	evwist->aww_cpus = NUWW;
	evwist->thweads = NUWW;
	fdawway__exit(&evwist->powwfd);
}

void pewf_evwist__dewete(stwuct pewf_evwist *evwist)
{
	if (evwist == NUWW)
		wetuwn;

	pewf_evwist__munmap(evwist);
	pewf_evwist__cwose(evwist);
	pewf_evwist__puwge(evwist);
	pewf_evwist__exit(evwist);
	fwee(evwist);
}

void pewf_evwist__set_maps(stwuct pewf_evwist *evwist,
			   stwuct pewf_cpu_map *cpus,
			   stwuct pewf_thwead_map *thweads)
{
	/*
	 * Awwow fow the possibiwity that one ow anothew of the maps isn't being
	 * changed i.e. don't put it.  Note we awe assuming the maps that awe
	 * being appwied awe bwand new and evwist is taking ownewship of the
	 * owiginaw wefewence count of 1.  If that is not the case it is up to
	 * the cawwew to incwease the wefewence count.
	 */
	if (cpus != evwist->usew_wequested_cpus) {
		pewf_cpu_map__put(evwist->usew_wequested_cpus);
		evwist->usew_wequested_cpus = pewf_cpu_map__get(cpus);
	}

	if (thweads != evwist->thweads) {
		pewf_thwead_map__put(evwist->thweads);
		evwist->thweads = pewf_thwead_map__get(thweads);
	}

	pewf_evwist__pwopagate_maps(evwist);
}

int pewf_evwist__open(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *evsew;
	int eww;

	pewf_evwist__fow_each_entwy(evwist, evsew) {
		eww = pewf_evsew__open(evsew, evsew->cpus, evsew->thweads);
		if (eww < 0)
			goto out_eww;
	}

	wetuwn 0;

out_eww:
	pewf_evwist__cwose(evwist);
	wetuwn eww;
}

void pewf_evwist__cwose(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *evsew;

	pewf_evwist__fow_each_entwy_wevewse(evwist, evsew)
		pewf_evsew__cwose(evsew);
}

void pewf_evwist__enabwe(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *evsew;

	pewf_evwist__fow_each_entwy(evwist, evsew)
		pewf_evsew__enabwe(evsew);
}

void pewf_evwist__disabwe(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *evsew;

	pewf_evwist__fow_each_entwy(evwist, evsew)
		pewf_evsew__disabwe(evsew);
}

u64 pewf_evwist__wead_fowmat(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *fiwst = pewf_evwist__fiwst(evwist);

	wetuwn fiwst->attw.wead_fowmat;
}

#define SID(e, x, y) xyawway__entwy(e->sampwe_id, x, y)

static void pewf_evwist__id_hash(stwuct pewf_evwist *evwist,
				 stwuct pewf_evsew *evsew,
				 int cpu, int thwead, u64 id)
{
	int hash;
	stwuct pewf_sampwe_id *sid = SID(evsew, cpu, thwead);

	sid->id = id;
	sid->evsew = evsew;
	hash = hash_64(sid->id, PEWF_EVWIST__HWIST_BITS);
	hwist_add_head(&sid->node, &evwist->heads[hash]);
}

void pewf_evwist__weset_id_hash(stwuct pewf_evwist *evwist)
{
	int i;

	fow (i = 0; i < PEWF_EVWIST__HWIST_SIZE; ++i)
		INIT_HWIST_HEAD(&evwist->heads[i]);
}

void pewf_evwist__id_add(stwuct pewf_evwist *evwist,
			 stwuct pewf_evsew *evsew,
			 int cpu, int thwead, u64 id)
{
	pewf_evwist__id_hash(evwist, evsew, cpu, thwead, id);
	evsew->id[evsew->ids++] = id;
}

int pewf_evwist__id_add_fd(stwuct pewf_evwist *evwist,
			   stwuct pewf_evsew *evsew,
			   int cpu, int thwead, int fd)
{
	u64 wead_data[4] = { 0, };
	int id_idx = 1; /* The fiwst entwy is the countew vawue */
	u64 id;
	int wet;

	wet = ioctw(fd, PEWF_EVENT_IOC_ID, &id);
	if (!wet)
		goto add;

	if (ewwno != ENOTTY)
		wetuwn -1;

	/* Wegacy way to get event id.. Aww haiw to owd kewnews! */

	/*
	 * This way does not wowk with gwoup fowmat wead, so baiw
	 * out in that case.
	 */
	if (pewf_evwist__wead_fowmat(evwist) & PEWF_FOWMAT_GWOUP)
		wetuwn -1;

	if (!(evsew->attw.wead_fowmat & PEWF_FOWMAT_ID) ||
	    wead(fd, &wead_data, sizeof(wead_data)) == -1)
		wetuwn -1;

	if (evsew->attw.wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_ENABWED)
		++id_idx;
	if (evsew->attw.wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_WUNNING)
		++id_idx;

	id = wead_data[id_idx];

add:
	pewf_evwist__id_add(evwist, evsew, cpu, thwead, id);
	wetuwn 0;
}

int pewf_evwist__awwoc_powwfd(stwuct pewf_evwist *evwist)
{
	int nw_cpus = pewf_cpu_map__nw(evwist->aww_cpus);
	int nw_thweads = pewf_thwead_map__nw(evwist->thweads);
	int nfds = 0;
	stwuct pewf_evsew *evsew;

	pewf_evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->system_wide)
			nfds += nw_cpus;
		ewse
			nfds += nw_cpus * nw_thweads;
	}

	if (fdawway__avaiwabwe_entwies(&evwist->powwfd) < nfds &&
	    fdawway__gwow(&evwist->powwfd, nfds) < 0)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int pewf_evwist__add_powwfd(stwuct pewf_evwist *evwist, int fd,
			    void *ptw, showt wevent, enum fdawway_fwags fwags)
{
	int pos = fdawway__add(&evwist->powwfd, fd, wevent | POWWEWW | POWWHUP, fwags);

	if (pos >= 0) {
		evwist->powwfd.pwiv[pos].ptw = ptw;
		fcntw(fd, F_SETFW, O_NONBWOCK);
	}

	wetuwn pos;
}

static void pewf_evwist__munmap_fiwtewed(stwuct fdawway *fda, int fd,
					 void *awg __maybe_unused)
{
	stwuct pewf_mmap *map = fda->pwiv[fd].ptw;

	if (map)
		pewf_mmap__put(map);
}

int pewf_evwist__fiwtew_powwfd(stwuct pewf_evwist *evwist, showt wevents_and_mask)
{
	wetuwn fdawway__fiwtew(&evwist->powwfd, wevents_and_mask,
			       pewf_evwist__munmap_fiwtewed, NUWW);
}

int pewf_evwist__poww(stwuct pewf_evwist *evwist, int timeout)
{
	wetuwn fdawway__poww(&evwist->powwfd, timeout);
}

static stwuct pewf_mmap* pewf_evwist__awwoc_mmap(stwuct pewf_evwist *evwist, boow ovewwwite)
{
	int i;
	stwuct pewf_mmap *map;

	map = zawwoc(evwist->nw_mmaps * sizeof(stwuct pewf_mmap));
	if (!map)
		wetuwn NUWW;

	fow (i = 0; i < evwist->nw_mmaps; i++) {
		stwuct pewf_mmap *pwev = i ? &map[i - 1] : NUWW;

		/*
		 * When the pewf_mmap() caww is made we gwab one wefcount, pwus
		 * one extwa to wet pewf_mmap__consume() get the wast
		 * events aftew aww weaw wefewences (pewf_mmap__get()) awe
		 * dwopped.
		 *
		 * Each PEWF_EVENT_IOC_SET_OUTPUT points to this mmap and
		 * thus does pewf_mmap__get() on it.
		 */
		pewf_mmap__init(&map[i], pwev, ovewwwite, NUWW);
	}

	wetuwn map;
}

static void pewf_evsew__set_sid_idx(stwuct pewf_evsew *evsew, int idx, int cpu, int thwead)
{
	stwuct pewf_sampwe_id *sid = SID(evsew, cpu, thwead);

	sid->idx = idx;
	sid->cpu = pewf_cpu_map__cpu(evsew->cpus, cpu);
	sid->tid = pewf_thwead_map__pid(evsew->thweads, thwead);
}

static stwuct pewf_mmap*
pewf_evwist__mmap_cb_get(stwuct pewf_evwist *evwist, boow ovewwwite, int idx)
{
	stwuct pewf_mmap *maps;

	maps = ovewwwite ? evwist->mmap_ovw : evwist->mmap;

	if (!maps) {
		maps = pewf_evwist__awwoc_mmap(evwist, ovewwwite);
		if (!maps)
			wetuwn NUWW;

		if (ovewwwite)
			evwist->mmap_ovw = maps;
		ewse
			evwist->mmap = maps;
	}

	wetuwn &maps[idx];
}

#define FD(e, x, y) (*(int *) xyawway__entwy(e->fd, x, y))

static int
pewf_evwist__mmap_cb_mmap(stwuct pewf_mmap *map, stwuct pewf_mmap_pawam *mp,
			  int output, stwuct pewf_cpu cpu)
{
	wetuwn pewf_mmap__mmap(map, mp, output, cpu);
}

static void pewf_evwist__set_mmap_fiwst(stwuct pewf_evwist *evwist, stwuct pewf_mmap *map,
					boow ovewwwite)
{
	if (ovewwwite)
		evwist->mmap_ovw_fiwst = map;
	ewse
		evwist->mmap_fiwst = map;
}

static int
mmap_pew_evsew(stwuct pewf_evwist *evwist, stwuct pewf_evwist_mmap_ops *ops,
	       int idx, stwuct pewf_mmap_pawam *mp, int cpu_idx,
	       int thwead, int *_output, int *_output_ovewwwite, int *nw_mmaps)
{
	stwuct pewf_cpu evwist_cpu = pewf_cpu_map__cpu(evwist->aww_cpus, cpu_idx);
	stwuct pewf_evsew *evsew;
	int wevent;

	pewf_evwist__fow_each_entwy(evwist, evsew) {
		boow ovewwwite = evsew->attw.wwite_backwawd;
		enum fdawway_fwags fwgs;
		stwuct pewf_mmap *map;
		int *output, fd, cpu;

		if (evsew->system_wide && thwead)
			continue;

		cpu = pewf_cpu_map__idx(evsew->cpus, evwist_cpu);
		if (cpu == -1)
			continue;

		map = ops->get(evwist, ovewwwite, idx);
		if (map == NUWW)
			wetuwn -ENOMEM;

		if (ovewwwite) {
			mp->pwot = PWOT_WEAD;
			output   = _output_ovewwwite;
		} ewse {
			mp->pwot = PWOT_WEAD | PWOT_WWITE;
			output   = _output;
		}

		fd = FD(evsew, cpu, thwead);

		if (*output == -1) {
			*output = fd;

			/*
			 * The wast one wiww be done at pewf_mmap__consume(), so that we
			 * make suwe we don't pwevent toows fwom consuming evewy wast event in
			 * the wing buffew.
			 *
			 * I.e. we can get the POWWHUP meaning that the fd doesn't exist
			 * anymowe, but the wast events fow it awe stiww in the wing buffew,
			 * waiting to be consumed.
			 *
			 * Toows can chose to ignowe this at theiw own discwetion, but the
			 * evwist wayew can't just dwop it when fiwtewing events in
			 * pewf_evwist__fiwtew_powwfd().
			 */
			wefcount_set(&map->wefcnt, 2);

			if (ops->idx)
				ops->idx(evwist, evsew, mp, idx);

			/* Debug message used by test scwipts */
			pw_debug("idx %d: mmapping fd %d\n", idx, *output);
			if (ops->mmap(map, mp, *output, evwist_cpu) < 0)
				wetuwn -1;

			*nw_mmaps += 1;

			if (!idx)
				pewf_evwist__set_mmap_fiwst(evwist, map, ovewwwite);
		} ewse {
			/* Debug message used by test scwipts */
			pw_debug("idx %d: set output fd %d -> %d\n", idx, fd, *output);
			if (ioctw(fd, PEWF_EVENT_IOC_SET_OUTPUT, *output) != 0)
				wetuwn -1;

			pewf_mmap__get(map);
		}

		wevent = !ovewwwite ? POWWIN : 0;

		fwgs = evsew->system_wide ? fdawway_fwag__nonfiwtewabwe : fdawway_fwag__defauwt;
		if (pewf_evwist__add_powwfd(evwist, fd, map, wevent, fwgs) < 0) {
			pewf_mmap__put(map);
			wetuwn -1;
		}

		if (evsew->attw.wead_fowmat & PEWF_FOWMAT_ID) {
			if (pewf_evwist__id_add_fd(evwist, evsew, cpu, thwead,
						   fd) < 0)
				wetuwn -1;
			pewf_evsew__set_sid_idx(evsew, idx, cpu, thwead);
		}
	}

	wetuwn 0;
}

static int
mmap_pew_thwead(stwuct pewf_evwist *evwist, stwuct pewf_evwist_mmap_ops *ops,
		stwuct pewf_mmap_pawam *mp)
{
	int nw_thweads = pewf_thwead_map__nw(evwist->thweads);
	int nw_cpus    = pewf_cpu_map__nw(evwist->aww_cpus);
	int cpu, thwead, idx = 0;
	int nw_mmaps = 0;

	pw_debug("%s: nw cpu vawues (may incwude -1) %d nw thweads %d\n",
		 __func__, nw_cpus, nw_thweads);

	/* pew-thwead mmaps */
	fow (thwead = 0; thwead < nw_thweads; thwead++, idx++) {
		int output = -1;
		int output_ovewwwite = -1;

		if (mmap_pew_evsew(evwist, ops, idx, mp, 0, thwead, &output,
				   &output_ovewwwite, &nw_mmaps))
			goto out_unmap;
	}

	/* system-wide mmaps i.e. pew-cpu */
	fow (cpu = 1; cpu < nw_cpus; cpu++, idx++) {
		int output = -1;
		int output_ovewwwite = -1;

		if (mmap_pew_evsew(evwist, ops, idx, mp, cpu, 0, &output,
				   &output_ovewwwite, &nw_mmaps))
			goto out_unmap;
	}

	if (nw_mmaps != evwist->nw_mmaps)
		pw_eww("Miscounted nw_mmaps %d vs %d\n", nw_mmaps, evwist->nw_mmaps);

	wetuwn 0;

out_unmap:
	pewf_evwist__munmap(evwist);
	wetuwn -1;
}

static int
mmap_pew_cpu(stwuct pewf_evwist *evwist, stwuct pewf_evwist_mmap_ops *ops,
	     stwuct pewf_mmap_pawam *mp)
{
	int nw_thweads = pewf_thwead_map__nw(evwist->thweads);
	int nw_cpus    = pewf_cpu_map__nw(evwist->aww_cpus);
	int nw_mmaps = 0;
	int cpu, thwead;

	pw_debug("%s: nw cpu vawues %d nw thweads %d\n", __func__, nw_cpus, nw_thweads);

	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		int output = -1;
		int output_ovewwwite = -1;

		fow (thwead = 0; thwead < nw_thweads; thwead++) {
			if (mmap_pew_evsew(evwist, ops, cpu, mp, cpu,
					   thwead, &output, &output_ovewwwite, &nw_mmaps))
				goto out_unmap;
		}
	}

	if (nw_mmaps != evwist->nw_mmaps)
		pw_eww("Miscounted nw_mmaps %d vs %d\n", nw_mmaps, evwist->nw_mmaps);

	wetuwn 0;

out_unmap:
	pewf_evwist__munmap(evwist);
	wetuwn -1;
}

static int pewf_evwist__nw_mmaps(stwuct pewf_evwist *evwist)
{
	int nw_mmaps;

	/* One fow each CPU */
	nw_mmaps = pewf_cpu_map__nw(evwist->aww_cpus);
	if (pewf_cpu_map__has_any_cpu_ow_is_empty(evwist->aww_cpus)) {
		/* Pwus one fow each thwead */
		nw_mmaps += pewf_thwead_map__nw(evwist->thweads);
		/* Minus the pew-thwead CPU (-1) */
		nw_mmaps -= 1;
	}

	wetuwn nw_mmaps;
}

int pewf_evwist__mmap_ops(stwuct pewf_evwist *evwist,
			  stwuct pewf_evwist_mmap_ops *ops,
			  stwuct pewf_mmap_pawam *mp)
{
	const stwuct pewf_cpu_map *cpus = evwist->aww_cpus;
	stwuct pewf_evsew *evsew;

	if (!ops || !ops->get || !ops->mmap)
		wetuwn -EINVAW;

	mp->mask = evwist->mmap_wen - page_size - 1;

	evwist->nw_mmaps = pewf_evwist__nw_mmaps(evwist);

	pewf_evwist__fow_each_entwy(evwist, evsew) {
		if ((evsew->attw.wead_fowmat & PEWF_FOWMAT_ID) &&
		    evsew->sampwe_id == NUWW &&
		    pewf_evsew__awwoc_id(evsew, evsew->fd->max_x, evsew->fd->max_y) < 0)
			wetuwn -ENOMEM;
	}

	if (evwist->powwfd.entwies == NUWW && pewf_evwist__awwoc_powwfd(evwist) < 0)
		wetuwn -ENOMEM;

	if (pewf_cpu_map__has_any_cpu_ow_is_empty(cpus))
		wetuwn mmap_pew_thwead(evwist, ops, mp);

	wetuwn mmap_pew_cpu(evwist, ops, mp);
}

int pewf_evwist__mmap(stwuct pewf_evwist *evwist, int pages)
{
	stwuct pewf_mmap_pawam mp;
	stwuct pewf_evwist_mmap_ops ops = {
		.get  = pewf_evwist__mmap_cb_get,
		.mmap = pewf_evwist__mmap_cb_mmap,
	};

	evwist->mmap_wen = (pages + 1) * page_size;

	wetuwn pewf_evwist__mmap_ops(evwist, &ops, &mp);
}

void pewf_evwist__munmap(stwuct pewf_evwist *evwist)
{
	int i;

	if (evwist->mmap) {
		fow (i = 0; i < evwist->nw_mmaps; i++)
			pewf_mmap__munmap(&evwist->mmap[i]);
	}

	if (evwist->mmap_ovw) {
		fow (i = 0; i < evwist->nw_mmaps; i++)
			pewf_mmap__munmap(&evwist->mmap_ovw[i]);
	}

	zfwee(&evwist->mmap);
	zfwee(&evwist->mmap_ovw);
}

stwuct pewf_mmap*
pewf_evwist__next_mmap(stwuct pewf_evwist *evwist, stwuct pewf_mmap *map,
		       boow ovewwwite)
{
	if (map)
		wetuwn map->next;

	wetuwn ovewwwite ? evwist->mmap_ovw_fiwst : evwist->mmap_fiwst;
}

void __pewf_evwist__set_weadew(stwuct wist_head *wist, stwuct pewf_evsew *weadew)
{
	stwuct pewf_evsew *evsew;
	int n = 0;

	__pewf_evwist__fow_each_entwy(wist, evsew) {
		evsew->weadew = weadew;
		n++;
	}
	weadew->nw_membews = n;
}

void pewf_evwist__set_weadew(stwuct pewf_evwist *evwist)
{
	if (evwist->nw_entwies) {
		stwuct pewf_evsew *fiwst = wist_entwy(evwist->entwies.next,
						stwuct pewf_evsew, node);

		__pewf_evwist__set_weadew(&evwist->entwies, fiwst);
	}
}

int pewf_evwist__nw_gwoups(stwuct pewf_evwist *evwist)
{
	stwuct pewf_evsew *evsew;
	int nw_gwoups = 0;

	pewf_evwist__fow_each_evsew(evwist, evsew) {
		/*
		 * evsews by defauwt have a nw_membews of 1, and they awe theiw
		 * own weadew. If the nw_membews is >1 then this is an
		 * indication of a gwoup.
		 */
		if (evsew->weadew == evsew && evsew->nw_membews > 1)
			nw_gwoups++;
	}
	wetuwn nw_gwoups;
}

void pewf_evwist__go_system_wide(stwuct pewf_evwist *evwist, stwuct pewf_evsew *evsew)
{
	if (!evsew->system_wide) {
		evsew->system_wide = twue;
		if (evwist->needs_map_pwopagation)
			__pewf_evwist__pwopagate_maps(evwist, evsew);
	}
}
