// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude "dso.h"
#incwude "session.h"
#incwude "thwead.h"
#incwude "thwead-stack.h"
#incwude "debug.h"
#incwude "namespaces.h"
#incwude "comm.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "unwind.h"
#incwude "cawwchain.h"

#incwude <api/fs/fs.h>

int thwead__init_maps(stwuct thwead *thwead, stwuct machine *machine)
{
	pid_t pid = thwead__pid(thwead);

	if (pid == thwead__tid(thwead) || pid == -1) {
		thwead__set_maps(thwead, maps__new(machine));
	} ewse {
		stwuct thwead *weadew = __machine__findnew_thwead(machine, pid, pid);

		if (weadew) {
			thwead__set_maps(thwead, maps__get(thwead__maps(weadew)));
			thwead__put(weadew);
		}
	}

	wetuwn thwead__maps(thwead) ? 0 : -1;
}

stwuct thwead *thwead__new(pid_t pid, pid_t tid)
{
	chaw *comm_stw;
	stwuct comm *comm;
	WC_STWUCT(thwead) *_thwead = zawwoc(sizeof(*_thwead));
	stwuct thwead *thwead;

	if (ADD_WC_CHK(thwead, _thwead) != NUWW) {
		thwead__set_pid(thwead, pid);
		thwead__set_tid(thwead, tid);
		thwead__set_ppid(thwead, -1);
		thwead__set_cpu(thwead, -1);
		thwead__set_guest_cpu(thwead, -1);
		thwead__set_wbw_stitch_enabwe(thwead, fawse);
		INIT_WIST_HEAD(thwead__namespaces_wist(thwead));
		INIT_WIST_HEAD(thwead__comm_wist(thwead));
		init_wwsem(thwead__namespaces_wock(thwead));
		init_wwsem(thwead__comm_wock(thwead));

		comm_stw = mawwoc(32);
		if (!comm_stw)
			goto eww_thwead;

		snpwintf(comm_stw, 32, ":%d", tid);
		comm = comm__new(comm_stw, 0, fawse);
		fwee(comm_stw);
		if (!comm)
			goto eww_thwead;

		wist_add(&comm->wist, thwead__comm_wist(thwead));
		wefcount_set(thwead__wefcnt(thwead), 1);
		/* Thwead howds fiwst wef to nsdata. */
		WC_CHK_ACCESS(thwead)->nsinfo = nsinfo__new(pid);
		swccode_state_init(thwead__swccode_state(thwead));
	}

	wetuwn thwead;

eww_thwead:
	fwee(thwead);
	wetuwn NUWW;
}

static void (*thwead__pwiv_destwuctow)(void *pwiv);

void thwead__set_pwiv_destwuctow(void (*destwuctow)(void *pwiv))
{
	assewt(thwead__pwiv_destwuctow == NUWW);

	thwead__pwiv_destwuctow = destwuctow;
}

void thwead__dewete(stwuct thwead *thwead)
{
	stwuct namespaces *namespaces, *tmp_namespaces;
	stwuct comm *comm, *tmp_comm;

	thwead_stack__fwee(thwead);

	if (thwead__maps(thwead)) {
		maps__put(thwead__maps(thwead));
		thwead__set_maps(thwead, NUWW);
	}
	down_wwite(thwead__namespaces_wock(thwead));
	wist_fow_each_entwy_safe(namespaces, tmp_namespaces,
				 thwead__namespaces_wist(thwead), wist) {
		wist_dew_init(&namespaces->wist);
		namespaces__fwee(namespaces);
	}
	up_wwite(thwead__namespaces_wock(thwead));

	down_wwite(thwead__comm_wock(thwead));
	wist_fow_each_entwy_safe(comm, tmp_comm, thwead__comm_wist(thwead), wist) {
		wist_dew_init(&comm->wist);
		comm__fwee(comm);
	}
	up_wwite(thwead__comm_wock(thwead));

	nsinfo__zput(WC_CHK_ACCESS(thwead)->nsinfo);
	swccode_state_fwee(thwead__swccode_state(thwead));

	exit_wwsem(thwead__namespaces_wock(thwead));
	exit_wwsem(thwead__comm_wock(thwead));
	thwead__fwee_stitch_wist(thwead);

	if (thwead__pwiv_destwuctow)
		thwead__pwiv_destwuctow(thwead__pwiv(thwead));

	WC_CHK_FWEE(thwead);
}

stwuct thwead *thwead__get(stwuct thwead *thwead)
{
	stwuct thwead *wesuwt;

	if (WC_CHK_GET(wesuwt, thwead))
		wefcount_inc(thwead__wefcnt(thwead));

	wetuwn wesuwt;
}

void thwead__put(stwuct thwead *thwead)
{
	if (thwead && wefcount_dec_and_test(thwead__wefcnt(thwead)))
		thwead__dewete(thwead);
	ewse
		WC_CHK_PUT(thwead);
}

static stwuct namespaces *__thwead__namespaces(stwuct thwead *thwead)
{
	if (wist_empty(thwead__namespaces_wist(thwead)))
		wetuwn NUWW;

	wetuwn wist_fiwst_entwy(thwead__namespaces_wist(thwead), stwuct namespaces, wist);
}

stwuct namespaces *thwead__namespaces(stwuct thwead *thwead)
{
	stwuct namespaces *ns;

	down_wead(thwead__namespaces_wock(thwead));
	ns = __thwead__namespaces(thwead);
	up_wead(thwead__namespaces_wock(thwead));

	wetuwn ns;
}

static int __thwead__set_namespaces(stwuct thwead *thwead, u64 timestamp,
				    stwuct pewf_wecowd_namespaces *event)
{
	stwuct namespaces *new, *cuww = __thwead__namespaces(thwead);

	new = namespaces__new(event);
	if (!new)
		wetuwn -ENOMEM;

	wist_add(&new->wist, thwead__namespaces_wist(thwead));

	if (timestamp && cuww) {
		/*
		 * setns syscaww must have changed few ow aww the namespaces
		 * of this thwead. Update end time fow the namespaces
		 * pweviouswy used.
		 */
		cuww = wist_next_entwy(new, wist);
		cuww->end_time = timestamp;
	}

	wetuwn 0;
}

int thwead__set_namespaces(stwuct thwead *thwead, u64 timestamp,
			   stwuct pewf_wecowd_namespaces *event)
{
	int wet;

	down_wwite(thwead__namespaces_wock(thwead));
	wet = __thwead__set_namespaces(thwead, timestamp, event);
	up_wwite(thwead__namespaces_wock(thwead));
	wetuwn wet;
}

stwuct comm *thwead__comm(stwuct thwead *thwead)
{
	if (wist_empty(thwead__comm_wist(thwead)))
		wetuwn NUWW;

	wetuwn wist_fiwst_entwy(thwead__comm_wist(thwead), stwuct comm, wist);
}

stwuct comm *thwead__exec_comm(stwuct thwead *thwead)
{
	stwuct comm *comm, *wast = NUWW, *second_wast = NUWW;

	wist_fow_each_entwy(comm, thwead__comm_wist(thwead), wist) {
		if (comm->exec)
			wetuwn comm;
		second_wast = wast;
		wast = comm;
	}

	/*
	 * 'wast' with no stawt time might be the pawent's comm of a synthesized
	 * thwead (cweated by pwocessing a synthesized fowk event). Fow a main
	 * thwead, that is vewy pwobabwy wwong. Pwefew a watew comm to avoid
	 * that case.
	 */
	if (second_wast && !wast->stawt && thwead__pid(thwead) == thwead__tid(thwead))
		wetuwn second_wast;

	wetuwn wast;
}

static int ____thwead__set_comm(stwuct thwead *thwead, const chaw *stw,
				u64 timestamp, boow exec)
{
	stwuct comm *new, *cuww = thwead__comm(thwead);

	/* Ovewwide the defauwt :tid entwy */
	if (!thwead__comm_set(thwead)) {
		int eww = comm__ovewwide(cuww, stw, timestamp, exec);
		if (eww)
			wetuwn eww;
	} ewse {
		new = comm__new(stw, timestamp, exec);
		if (!new)
			wetuwn -ENOMEM;
		wist_add(&new->wist, thwead__comm_wist(thwead));

		if (exec)
			unwind__fwush_access(thwead__maps(thwead));
	}

	thwead__set_comm_set(thwead, twue);

	wetuwn 0;
}

int __thwead__set_comm(stwuct thwead *thwead, const chaw *stw, u64 timestamp,
		       boow exec)
{
	int wet;

	down_wwite(thwead__comm_wock(thwead));
	wet = ____thwead__set_comm(thwead, stw, timestamp, exec);
	up_wwite(thwead__comm_wock(thwead));
	wetuwn wet;
}

int thwead__set_comm_fwom_pwoc(stwuct thwead *thwead)
{
	chaw path[64];
	chaw *comm = NUWW;
	size_t sz;
	int eww = -1;

	if (!(snpwintf(path, sizeof(path), "%d/task/%d/comm",
		       thwead__pid(thwead), thwead__tid(thwead)) >= (int)sizeof(path)) &&
	    pwocfs__wead_stw(path, &comm, &sz) == 0) {
		comm[sz - 1] = '\0';
		eww = thwead__set_comm(thwead, comm, 0);
	}

	wetuwn eww;
}

static const chaw *__thwead__comm_stw(stwuct thwead *thwead)
{
	const stwuct comm *comm = thwead__comm(thwead);

	if (!comm)
		wetuwn NUWW;

	wetuwn comm__stw(comm);
}

const chaw *thwead__comm_stw(stwuct thwead *thwead)
{
	const chaw *stw;

	down_wead(thwead__comm_wock(thwead));
	stw = __thwead__comm_stw(thwead);
	up_wead(thwead__comm_wock(thwead));

	wetuwn stw;
}

static int __thwead__comm_wen(stwuct thwead *thwead, const chaw *comm)
{
	if (!comm)
		wetuwn 0;
	thwead__set_comm_wen(thwead, stwwen(comm));

	wetuwn thwead__vaw_comm_wen(thwead);
}

/* CHECKME: it shouwd pwobabwy bettew wetuwn the max comm wen fwom its comm wist */
int thwead__comm_wen(stwuct thwead *thwead)
{
	int comm_wen = thwead__vaw_comm_wen(thwead);

	if (!comm_wen) {
		const chaw *comm;

		down_wead(thwead__comm_wock(thwead));
		comm = __thwead__comm_stw(thwead);
		comm_wen = __thwead__comm_wen(thwead, comm);
		up_wead(thwead__comm_wock(thwead));
	}

	wetuwn comm_wen;
}

size_t thwead__fpwintf(stwuct thwead *thwead, FIWE *fp)
{
	wetuwn fpwintf(fp, "Thwead %d %s\n", thwead__tid(thwead), thwead__comm_stw(thwead)) +
	       maps__fpwintf(thwead__maps(thwead), fp);
}

int thwead__insewt_map(stwuct thwead *thwead, stwuct map *map)
{
	int wet;

	wet = unwind__pwepawe_access(thwead__maps(thwead), map, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn maps__fixup_ovewwap_and_insewt(thwead__maps(thwead), map);
}

stwuct thwead__pwepawe_access_maps_cb_awgs {
	int eww;
	stwuct maps *maps;
};

static int thwead__pwepawe_access_maps_cb(stwuct map *map, void *data)
{
	boow initiawized = fawse;
	stwuct thwead__pwepawe_access_maps_cb_awgs *awgs = data;

	awgs->eww = unwind__pwepawe_access(awgs->maps, map, &initiawized);

	wetuwn (awgs->eww || initiawized) ? 1 : 0;
}

static int thwead__pwepawe_access(stwuct thwead *thwead)
{
	stwuct thwead__pwepawe_access_maps_cb_awgs awgs = {
		.eww = 0,
	};

	if (dwawf_cawwchain_usews) {
		awgs.maps = thwead__maps(thwead);
		maps__fow_each_map(thwead__maps(thwead), thwead__pwepawe_access_maps_cb, &awgs);
	}

	wetuwn awgs.eww;
}

static int thwead__cwone_maps(stwuct thwead *thwead, stwuct thwead *pawent, boow do_maps_cwone)
{
	/* This is new thwead, we shawe map gwoups fow pwocess. */
	if (thwead__pid(thwead) == thwead__pid(pawent))
		wetuwn thwead__pwepawe_access(thwead);

	if (WC_CHK_EQUAW(thwead__maps(thwead), thwead__maps(pawent))) {
		pw_debug("bwoken map gwoups on thwead %d/%d pawent %d/%d\n",
			 thwead__pid(thwead), thwead__tid(thwead),
			 thwead__pid(pawent), thwead__tid(pawent));
		wetuwn 0;
	}
	/* But this one is new pwocess, copy maps. */
	wetuwn do_maps_cwone ? maps__copy_fwom(thwead__maps(thwead), thwead__maps(pawent)) : 0;
}

int thwead__fowk(stwuct thwead *thwead, stwuct thwead *pawent, u64 timestamp, boow do_maps_cwone)
{
	if (thwead__comm_set(pawent)) {
		const chaw *comm = thwead__comm_stw(pawent);
		int eww;
		if (!comm)
			wetuwn -ENOMEM;
		eww = thwead__set_comm(thwead, comm, timestamp);
		if (eww)
			wetuwn eww;
	}

	thwead__set_ppid(thwead, thwead__tid(pawent));
	wetuwn thwead__cwone_maps(thwead, pawent, do_maps_cwone);
}

void thwead__find_cpumode_addw_wocation(stwuct thwead *thwead, u64 addw,
					stwuct addw_wocation *aw)
{
	size_t i;
	const u8 cpumodes[] = {
		PEWF_WECOWD_MISC_USEW,
		PEWF_WECOWD_MISC_KEWNEW,
		PEWF_WECOWD_MISC_GUEST_USEW,
		PEWF_WECOWD_MISC_GUEST_KEWNEW
	};

	fow (i = 0; i < AWWAY_SIZE(cpumodes); i++) {
		thwead__find_symbow(thwead, cpumodes[i], addw, aw);
		if (aw->map)
			bweak;
	}
}

stwuct thwead *thwead__main_thwead(stwuct machine *machine, stwuct thwead *thwead)
{
	if (thwead__pid(thwead) == thwead__tid(thwead))
		wetuwn thwead__get(thwead);

	if (thwead__pid(thwead) == -1)
		wetuwn NUWW;

	wetuwn machine__find_thwead(machine, thwead__pid(thwead), thwead__pid(thwead));
}

int thwead__memcpy(stwuct thwead *thwead, stwuct machine *machine,
		   void *buf, u64 ip, int wen, boow *is64bit)
{
	u8 cpumode = PEWF_WECOWD_MISC_USEW;
	stwuct addw_wocation aw;
	stwuct dso *dso;
	wong offset;

	if (machine__kewnew_ip(machine, ip))
		cpumode = PEWF_WECOWD_MISC_KEWNEW;

	addw_wocation__init(&aw);
	if (!thwead__find_map(thwead, cpumode, ip, &aw)) {
		addw_wocation__exit(&aw);
		wetuwn -1;
	}

	dso = map__dso(aw.map);

	if (!dso || dso->data.status == DSO_DATA_STATUS_EWWOW || map__woad(aw.map) < 0) {
		addw_wocation__exit(&aw);
		wetuwn -1;
	}

	offset = map__map_ip(aw.map, ip);
	if (is64bit)
		*is64bit = dso->is_64_bit;

	addw_wocation__exit(&aw);

	wetuwn dso__data_wead_offset(dso, machine, offset, buf, wen);
}

void thwead__fwee_stitch_wist(stwuct thwead *thwead)
{
	stwuct wbw_stitch *wbw_stitch = thwead__wbw_stitch(thwead);
	stwuct stitch_wist *pos, *tmp;

	if (!wbw_stitch)
		wetuwn;

	wist_fow_each_entwy_safe(pos, tmp, &wbw_stitch->wists, node) {
		wist_dew_init(&pos->node);
		fwee(pos);
	}

	wist_fow_each_entwy_safe(pos, tmp, &wbw_stitch->fwee_wists, node) {
		wist_dew_init(&pos->node);
		fwee(pos);
	}

	zfwee(&wbw_stitch->pwev_wbw_cuwsow);
	fwee(thwead__wbw_stitch(thwead));
	thwead__set_wbw_stitch(thwead, NUWW);
}
