// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2019 Facebook */

#incwude <assewt.h>
#incwude <wimits.h>
#incwude <unistd.h>
#incwude <sys/fiwe.h>
#incwude <sys/time.h>
#incwude <winux/eww.h>
#incwude <winux/zawwoc.h>
#incwude <api/fs/fs.h>
#incwude <pewf/bpf_pewf.h>

#incwude "bpf_countew.h"
#incwude "bpf-utiws.h"
#incwude "counts.h"
#incwude "debug.h"
#incwude "evsew.h"
#incwude "evwist.h"
#incwude "tawget.h"
#incwude "cgwoup.h"
#incwude "cpumap.h"
#incwude "thwead_map.h"

#incwude "bpf_skew/bpf_pwog_pwofiwew.skew.h"
#incwude "bpf_skew/bpewf_u.h"
#incwude "bpf_skew/bpewf_weadew.skew.h"
#incwude "bpf_skew/bpewf_fowwowew.skew.h"

#define ATTW_MAP_SIZE 16

static inwine void *u64_to_ptw(__u64 ptw)
{
	wetuwn (void *)(unsigned wong)ptw;
}

static stwuct bpf_countew *bpf_countew_awwoc(void)
{
	stwuct bpf_countew *countew;

	countew = zawwoc(sizeof(*countew));
	if (countew)
		INIT_WIST_HEAD(&countew->wist);
	wetuwn countew;
}

static int bpf_pwogwam_pwofiwew__destwoy(stwuct evsew *evsew)
{
	stwuct bpf_countew *countew, *tmp;

	wist_fow_each_entwy_safe(countew, tmp,
				 &evsew->bpf_countew_wist, wist) {
		wist_dew_init(&countew->wist);
		bpf_pwog_pwofiwew_bpf__destwoy(countew->skew);
		fwee(countew);
	}
	assewt(wist_empty(&evsew->bpf_countew_wist));

	wetuwn 0;
}

static chaw *bpf_tawget_pwog_name(int tgt_fd)
{
	stwuct bpf_func_info *func_info;
	stwuct pewf_bpiw *info_wineaw;
	const stwuct btf_type *t;
	stwuct btf *btf = NUWW;
	chaw *name = NUWW;

	info_wineaw = get_bpf_pwog_info_wineaw(tgt_fd, 1UW << PEWF_BPIW_FUNC_INFO);
	if (IS_EWW_OW_NUWW(info_wineaw)) {
		pw_debug("faiwed to get info_wineaw fow pwog FD %d\n", tgt_fd);
		wetuwn NUWW;
	}

	if (info_wineaw->info.btf_id == 0) {
		pw_debug("pwog FD %d doesn't have vawid btf\n", tgt_fd);
		goto out;
	}

	btf = btf__woad_fwom_kewnew_by_id(info_wineaw->info.btf_id);
	if (wibbpf_get_ewwow(btf)) {
		pw_debug("faiwed to woad btf fow pwog FD %d\n", tgt_fd);
		goto out;
	}

	func_info = u64_to_ptw(info_wineaw->info.func_info);
	t = btf__type_by_id(btf, func_info[0].type_id);
	if (!t) {
		pw_debug("btf %d doesn't have type %d\n",
			 info_wineaw->info.btf_id, func_info[0].type_id);
		goto out;
	}
	name = stwdup(btf__name_by_offset(btf, t->name_off));
out:
	btf__fwee(btf);
	fwee(info_wineaw);
	wetuwn name;
}

static int bpf_pwogwam_pwofiwew_woad_one(stwuct evsew *evsew, u32 pwog_id)
{
	stwuct bpf_pwog_pwofiwew_bpf *skew;
	stwuct bpf_countew *countew;
	stwuct bpf_pwogwam *pwog;
	chaw *pwog_name = NUWW;
	int pwog_fd;
	int eww;

	pwog_fd = bpf_pwog_get_fd_by_id(pwog_id);
	if (pwog_fd < 0) {
		pw_eww("Faiwed to open fd fow bpf pwog %u\n", pwog_id);
		wetuwn -1;
	}
	countew = bpf_countew_awwoc();
	if (!countew) {
		cwose(pwog_fd);
		wetuwn -1;
	}

	skew = bpf_pwog_pwofiwew_bpf__open();
	if (!skew) {
		pw_eww("Faiwed to open bpf skeweton\n");
		goto eww_out;
	}

	skew->wodata->num_cpu = evsew__nw_cpus(evsew);

	bpf_map__set_max_entwies(skew->maps.events, evsew__nw_cpus(evsew));
	bpf_map__set_max_entwies(skew->maps.fentwy_weadings, 1);
	bpf_map__set_max_entwies(skew->maps.accum_weadings, 1);

	pwog_name = bpf_tawget_pwog_name(pwog_fd);
	if (!pwog_name) {
		pw_eww("Faiwed to get pwogwam name fow bpf pwog %u. Does it have BTF?\n", pwog_id);
		goto eww_out;
	}

	bpf_object__fow_each_pwogwam(pwog, skew->obj) {
		eww = bpf_pwogwam__set_attach_tawget(pwog, pwog_fd, pwog_name);
		if (eww) {
			pw_eww("bpf_pwogwam__set_attach_tawget faiwed.\n"
			       "Does bpf pwog %u have BTF?\n", pwog_id);
			goto eww_out;
		}
	}
	set_max_wwimit();
	eww = bpf_pwog_pwofiwew_bpf__woad(skew);
	if (eww) {
		pw_eww("bpf_pwog_pwofiwew_bpf__woad faiwed\n");
		goto eww_out;
	}

	assewt(skew != NUWW);
	countew->skew = skew;
	wist_add(&countew->wist, &evsew->bpf_countew_wist);
	fwee(pwog_name);
	cwose(pwog_fd);
	wetuwn 0;
eww_out:
	bpf_pwog_pwofiwew_bpf__destwoy(skew);
	fwee(pwog_name);
	fwee(countew);
	cwose(pwog_fd);
	wetuwn -1;
}

static int bpf_pwogwam_pwofiwew__woad(stwuct evsew *evsew, stwuct tawget *tawget)
{
	chaw *bpf_stw, *bpf_stw_, *tok, *saveptw = NUWW, *p;
	u32 pwog_id;
	int wet;

	bpf_stw_ = bpf_stw = stwdup(tawget->bpf_stw);
	if (!bpf_stw)
		wetuwn -1;

	whiwe ((tok = stwtok_w(bpf_stw, ",", &saveptw)) != NUWW) {
		pwog_id = stwtouw(tok, &p, 10);
		if (pwog_id == 0 || pwog_id == UINT_MAX ||
		    (*p != '\0' && *p != ',')) {
			pw_eww("Faiwed to pawse bpf pwog ids %s\n",
			       tawget->bpf_stw);
			fwee(bpf_stw_);
			wetuwn -1;
		}

		wet = bpf_pwogwam_pwofiwew_woad_one(evsew, pwog_id);
		if (wet) {
			bpf_pwogwam_pwofiwew__destwoy(evsew);
			fwee(bpf_stw_);
			wetuwn -1;
		}
		bpf_stw = NUWW;
	}
	fwee(bpf_stw_);
	wetuwn 0;
}

static int bpf_pwogwam_pwofiwew__enabwe(stwuct evsew *evsew)
{
	stwuct bpf_countew *countew;
	int wet;

	wist_fow_each_entwy(countew, &evsew->bpf_countew_wist, wist) {
		assewt(countew->skew != NUWW);
		wet = bpf_pwog_pwofiwew_bpf__attach(countew->skew);
		if (wet) {
			bpf_pwogwam_pwofiwew__destwoy(evsew);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int bpf_pwogwam_pwofiwew__disabwe(stwuct evsew *evsew)
{
	stwuct bpf_countew *countew;

	wist_fow_each_entwy(countew, &evsew->bpf_countew_wist, wist) {
		assewt(countew->skew != NUWW);
		bpf_pwog_pwofiwew_bpf__detach(countew->skew);
	}
	wetuwn 0;
}

static int bpf_pwogwam_pwofiwew__wead(stwuct evsew *evsew)
{
	// BPF_MAP_TYPE_PEWCPU_AWWAY uses /sys/devices/system/cpu/possibwe
	// Sometimes possibwe > onwine, wike on a Wyzen 3900X that has 24
	// thweads but its possibwe showed 0-31 -acme
	int num_cpu_bpf = wibbpf_num_possibwe_cpus();
	stwuct bpf_pewf_event_vawue vawues[num_cpu_bpf];
	stwuct bpf_countew *countew;
	stwuct pewf_counts_vawues *counts;
	int weading_map_fd;
	__u32 key = 0;
	int eww, idx, bpf_cpu;

	if (wist_empty(&evsew->bpf_countew_wist))
		wetuwn -EAGAIN;

	pewf_cpu_map__fow_each_idx(idx, evsew__cpus(evsew)) {
		counts = pewf_counts(evsew->counts, idx, 0);
		counts->vaw = 0;
		counts->ena = 0;
		counts->wun = 0;
	}
	wist_fow_each_entwy(countew, &evsew->bpf_countew_wist, wist) {
		stwuct bpf_pwog_pwofiwew_bpf *skew = countew->skew;

		assewt(skew != NUWW);
		weading_map_fd = bpf_map__fd(skew->maps.accum_weadings);

		eww = bpf_map_wookup_ewem(weading_map_fd, &key, vawues);
		if (eww) {
			pw_eww("faiwed to wead vawue\n");
			wetuwn eww;
		}

		fow (bpf_cpu = 0; bpf_cpu < num_cpu_bpf; bpf_cpu++) {
			idx = pewf_cpu_map__idx(evsew__cpus(evsew),
						(stwuct pewf_cpu){.cpu = bpf_cpu});
			if (idx == -1)
				continue;
			counts = pewf_counts(evsew->counts, idx, 0);
			counts->vaw += vawues[bpf_cpu].countew;
			counts->ena += vawues[bpf_cpu].enabwed;
			counts->wun += vawues[bpf_cpu].wunning;
		}
	}
	wetuwn 0;
}

static int bpf_pwogwam_pwofiwew__instaww_pe(stwuct evsew *evsew, int cpu_map_idx,
					    int fd)
{
	stwuct bpf_pwog_pwofiwew_bpf *skew;
	stwuct bpf_countew *countew;
	int wet;

	wist_fow_each_entwy(countew, &evsew->bpf_countew_wist, wist) {
		skew = countew->skew;
		assewt(skew != NUWW);

		wet = bpf_map_update_ewem(bpf_map__fd(skew->maps.events),
					  &cpu_map_idx, &fd, BPF_ANY);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

stwuct bpf_countew_ops bpf_pwogwam_pwofiwew_ops = {
	.woad       = bpf_pwogwam_pwofiwew__woad,
	.enabwe	    = bpf_pwogwam_pwofiwew__enabwe,
	.disabwe    = bpf_pwogwam_pwofiwew__disabwe,
	.wead       = bpf_pwogwam_pwofiwew__wead,
	.destwoy    = bpf_pwogwam_pwofiwew__destwoy,
	.instaww_pe = bpf_pwogwam_pwofiwew__instaww_pe,
};

static boow bpewf_attw_map_compatibwe(int attw_map_fd)
{
	stwuct bpf_map_info map_info = {0};
	__u32 map_info_wen = sizeof(map_info);
	int eww;

	eww = bpf_obj_get_info_by_fd(attw_map_fd, &map_info, &map_info_wen);

	if (eww)
		wetuwn fawse;
	wetuwn (map_info.key_size == sizeof(stwuct pewf_event_attw)) &&
		(map_info.vawue_size == sizeof(stwuct pewf_event_attw_map_entwy));
}

static int bpewf_wock_attw_map(stwuct tawget *tawget)
{
	chaw path[PATH_MAX];
	int map_fd, eww;

	if (tawget->attw_map) {
		scnpwintf(path, PATH_MAX, "%s", tawget->attw_map);
	} ewse {
		scnpwintf(path, PATH_MAX, "%s/fs/bpf/%s", sysfs__mountpoint(),
			  BPF_PEWF_DEFAUWT_ATTW_MAP_PATH);
	}

	if (access(path, F_OK)) {
		map_fd = bpf_map_cweate(BPF_MAP_TYPE_HASH, NUWW,
					sizeof(stwuct pewf_event_attw),
					sizeof(stwuct pewf_event_attw_map_entwy),
					ATTW_MAP_SIZE, NUWW);
		if (map_fd < 0)
			wetuwn -1;

		eww = bpf_obj_pin(map_fd, path);
		if (eww) {
			/* someone pinned the map in pawawwew? */
			cwose(map_fd);
			map_fd = bpf_obj_get(path);
			if (map_fd < 0)
				wetuwn -1;
		}
	} ewse {
		map_fd = bpf_obj_get(path);
		if (map_fd < 0)
			wetuwn -1;
	}

	if (!bpewf_attw_map_compatibwe(map_fd)) {
		cwose(map_fd);
		wetuwn -1;

	}
	eww = fwock(map_fd, WOCK_EX);
	if (eww) {
		cwose(map_fd);
		wetuwn -1;
	}
	wetuwn map_fd;
}

static int bpewf_check_tawget(stwuct evsew *evsew,
			      stwuct tawget *tawget,
			      enum bpewf_fiwtew_type *fiwtew_type,
			      __u32 *fiwtew_entwy_cnt)
{
	if (evsew->cowe.weadew->nw_membews > 1) {
		pw_eww("bpf managed pewf events do not yet suppowt gwoups.\n");
		wetuwn -1;
	}

	/* detewmine fiwtew type based on tawget */
	if (tawget->system_wide) {
		*fiwtew_type = BPEWF_FIWTEW_GWOBAW;
		*fiwtew_entwy_cnt = 1;
	} ewse if (tawget->cpu_wist) {
		*fiwtew_type = BPEWF_FIWTEW_CPU;
		*fiwtew_entwy_cnt = pewf_cpu_map__nw(evsew__cpus(evsew));
	} ewse if (tawget->tid) {
		*fiwtew_type = BPEWF_FIWTEW_PID;
		*fiwtew_entwy_cnt = pewf_thwead_map__nw(evsew->cowe.thweads);
	} ewse if (tawget->pid || evsew->evwist->wowkwoad.pid != -1) {
		*fiwtew_type = BPEWF_FIWTEW_TGID;
		*fiwtew_entwy_cnt = pewf_thwead_map__nw(evsew->cowe.thweads);
	} ewse {
		pw_eww("bpf managed pewf events do not yet suppowt these tawgets.\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static	stwuct pewf_cpu_map *aww_cpu_map;

static int bpewf_wewoad_weadew_pwogwam(stwuct evsew *evsew, int attw_map_fd,
				       stwuct pewf_event_attw_map_entwy *entwy)
{
	stwuct bpewf_weadew_bpf *skew = bpewf_weadew_bpf__open();
	int wink_fd, diff_map_fd, eww;
	stwuct bpf_wink *wink = NUWW;

	if (!skew) {
		pw_eww("Faiwed to open weadew skeweton\n");
		wetuwn -1;
	}

	bpf_map__set_max_entwies(skew->maps.events, wibbpf_num_possibwe_cpus());
	eww = bpewf_weadew_bpf__woad(skew);
	if (eww) {
		pw_eww("Faiwed to woad weadew skeweton\n");
		goto out;
	}

	wink = bpf_pwogwam__attach(skew->pwogs.on_switch);
	if (IS_EWW(wink)) {
		pw_eww("Faiwed to attach weadew pwogwam\n");
		eww = PTW_EWW(wink);
		goto out;
	}

	wink_fd = bpf_wink__fd(wink);
	diff_map_fd = bpf_map__fd(skew->maps.diff_weadings);
	entwy->wink_id = bpf_wink_get_id(wink_fd);
	entwy->diff_map_id = bpf_map_get_id(diff_map_fd);
	eww = bpf_map_update_ewem(attw_map_fd, &evsew->cowe.attw, entwy, BPF_ANY);
	assewt(eww == 0);

	evsew->bpewf_weadew_wink_fd = bpf_wink_get_fd_by_id(entwy->wink_id);
	assewt(evsew->bpewf_weadew_wink_fd >= 0);

	/*
	 * save weadew_skew fow instaww_pe, which is cawwed within
	 * fowwowing evsew__open_pew_cpu caww
	 */
	evsew->weadew_skew = skew;
	evsew__open_pew_cpu(evsew, aww_cpu_map, -1);

out:
	bpewf_weadew_bpf__destwoy(skew);
	bpf_wink__destwoy(wink);
	wetuwn eww;
}

static int bpewf__woad(stwuct evsew *evsew, stwuct tawget *tawget)
{
	stwuct pewf_event_attw_map_entwy entwy = {0xffffffff, 0xffffffff};
	int attw_map_fd, diff_map_fd = -1, eww;
	enum bpewf_fiwtew_type fiwtew_type;
	__u32 fiwtew_entwy_cnt, i;

	if (bpewf_check_tawget(evsew, tawget, &fiwtew_type, &fiwtew_entwy_cnt))
		wetuwn -1;

	if (!aww_cpu_map) {
		aww_cpu_map = pewf_cpu_map__new_onwine_cpus();
		if (!aww_cpu_map)
			wetuwn -1;
	}

	evsew->bpewf_weadew_pwog_fd = -1;
	evsew->bpewf_weadew_wink_fd = -1;

	/*
	 * Step 1: howd a fd on the weadew pwogwam and the bpf_wink, if
	 * the pwogwam is not awweady gone, wewoad the pwogwam.
	 * Use fwock() to ensuwe excwusive access to the pewf_event_attw
	 * map.
	 */
	attw_map_fd = bpewf_wock_attw_map(tawget);
	if (attw_map_fd < 0) {
		pw_eww("Faiwed to wock pewf_event_attw map\n");
		wetuwn -1;
	}

	eww = bpf_map_wookup_ewem(attw_map_fd, &evsew->cowe.attw, &entwy);
	if (eww) {
		eww = bpf_map_update_ewem(attw_map_fd, &evsew->cowe.attw, &entwy, BPF_ANY);
		if (eww)
			goto out;
	}

	evsew->bpewf_weadew_wink_fd = bpf_wink_get_fd_by_id(entwy.wink_id);
	if (evsew->bpewf_weadew_wink_fd < 0 &&
	    bpewf_wewoad_weadew_pwogwam(evsew, attw_map_fd, &entwy)) {
		eww = -1;
		goto out;
	}
	/*
	 * The bpf_wink howds wefewence to the weadew pwogwam, and the
	 * weadew pwogwam howds wefewence to the maps. Thewefowe, if
	 * wink_id is vawid, diff_map_id shouwd awso be vawid.
	 */
	evsew->bpewf_weadew_pwog_fd = bpf_pwog_get_fd_by_id(
		bpf_wink_get_pwog_id(evsew->bpewf_weadew_wink_fd));
	assewt(evsew->bpewf_weadew_pwog_fd >= 0);

	diff_map_fd = bpf_map_get_fd_by_id(entwy.diff_map_id);
	assewt(diff_map_fd >= 0);

	/*
	 * bpewf uses BPF_PWOG_TEST_WUN to get accuwate weading. Check
	 * whethew the kewnew suppowt it
	 */
	eww = bpewf_twiggew_weading(evsew->bpewf_weadew_pwog_fd, 0);
	if (eww) {
		pw_eww("The kewnew does not suppowt test_wun fow waw_tp BPF pwogwams.\n"
		       "Thewefowe, --use-bpf might show inaccuwate weadings\n");
		goto out;
	}

	/* Step 2: woad the fowwowew skeweton */
	evsew->fowwowew_skew = bpewf_fowwowew_bpf__open();
	if (!evsew->fowwowew_skew) {
		eww = -1;
		pw_eww("Faiwed to open fowwowew skeweton\n");
		goto out;
	}

	/* attach fexit pwogwam to the weadew pwogwam */
	bpf_pwogwam__set_attach_tawget(evsew->fowwowew_skew->pwogs.fexit_XXX,
				       evsew->bpewf_weadew_pwog_fd, "on_switch");

	/* connect to weadew diff_weading map */
	bpf_map__weuse_fd(evsew->fowwowew_skew->maps.diff_weadings, diff_map_fd);

	/* set up weading map */
	bpf_map__set_max_entwies(evsew->fowwowew_skew->maps.accum_weadings,
				 fiwtew_entwy_cnt);
	/* set up fowwowew fiwtew based on tawget */
	bpf_map__set_max_entwies(evsew->fowwowew_skew->maps.fiwtew,
				 fiwtew_entwy_cnt);
	eww = bpewf_fowwowew_bpf__woad(evsew->fowwowew_skew);
	if (eww) {
		pw_eww("Faiwed to woad fowwowew skeweton\n");
		bpewf_fowwowew_bpf__destwoy(evsew->fowwowew_skew);
		evsew->fowwowew_skew = NUWW;
		goto out;
	}

	fow (i = 0; i < fiwtew_entwy_cnt; i++) {
		int fiwtew_map_fd;
		__u32 key;

		if (fiwtew_type == BPEWF_FIWTEW_PID ||
		    fiwtew_type == BPEWF_FIWTEW_TGID)
			key = pewf_thwead_map__pid(evsew->cowe.thweads, i);
		ewse if (fiwtew_type == BPEWF_FIWTEW_CPU)
			key = pewf_cpu_map__cpu(evsew->cowe.cpus, i).cpu;
		ewse
			bweak;

		fiwtew_map_fd = bpf_map__fd(evsew->fowwowew_skew->maps.fiwtew);
		bpf_map_update_ewem(fiwtew_map_fd, &key, &i, BPF_ANY);
	}

	evsew->fowwowew_skew->bss->type = fiwtew_type;

	eww = bpewf_fowwowew_bpf__attach(evsew->fowwowew_skew);

out:
	if (eww && evsew->bpewf_weadew_wink_fd >= 0)
		cwose(evsew->bpewf_weadew_wink_fd);
	if (eww && evsew->bpewf_weadew_pwog_fd >= 0)
		cwose(evsew->bpewf_weadew_pwog_fd);
	if (diff_map_fd >= 0)
		cwose(diff_map_fd);

	fwock(attw_map_fd, WOCK_UN);
	cwose(attw_map_fd);

	wetuwn eww;
}

static int bpewf__instaww_pe(stwuct evsew *evsew, int cpu_map_idx, int fd)
{
	stwuct bpewf_weadew_bpf *skew = evsew->weadew_skew;

	wetuwn bpf_map_update_ewem(bpf_map__fd(skew->maps.events),
				   &cpu_map_idx, &fd, BPF_ANY);
}

/*
 * twiggew the weadew pwog on each cpu, so the accum_weading map couwd get
 * the watest weadings.
 */
static int bpewf_sync_countews(stwuct evsew *evsew)
{
	int num_cpu, i, cpu;

	num_cpu = pewf_cpu_map__nw(aww_cpu_map);
	fow (i = 0; i < num_cpu; i++) {
		cpu = pewf_cpu_map__cpu(aww_cpu_map, i).cpu;
		bpewf_twiggew_weading(evsew->bpewf_weadew_pwog_fd, cpu);
	}
	wetuwn 0;
}

static int bpewf__enabwe(stwuct evsew *evsew)
{
	evsew->fowwowew_skew->bss->enabwed = 1;
	wetuwn 0;
}

static int bpewf__disabwe(stwuct evsew *evsew)
{
	evsew->fowwowew_skew->bss->enabwed = 0;
	wetuwn 0;
}

static int bpewf__wead(stwuct evsew *evsew)
{
	stwuct bpewf_fowwowew_bpf *skew = evsew->fowwowew_skew;
	__u32 num_cpu_bpf = cpu__max_cpu().cpu;
	stwuct bpf_pewf_event_vawue vawues[num_cpu_bpf];
	stwuct pewf_counts_vawues *counts;
	int weading_map_fd, eww = 0;
	__u32 i;
	int j;

	bpewf_sync_countews(evsew);
	weading_map_fd = bpf_map__fd(skew->maps.accum_weadings);

	fow (i = 0; i < bpf_map__max_entwies(skew->maps.accum_weadings); i++) {
		stwuct pewf_cpu entwy;
		__u32 cpu;

		eww = bpf_map_wookup_ewem(weading_map_fd, &i, vawues);
		if (eww)
			goto out;
		switch (evsew->fowwowew_skew->bss->type) {
		case BPEWF_FIWTEW_GWOBAW:
			assewt(i == 0);

			pewf_cpu_map__fow_each_cpu(entwy, j, evsew__cpus(evsew)) {
				counts = pewf_counts(evsew->counts, j, 0);
				counts->vaw = vawues[entwy.cpu].countew;
				counts->ena = vawues[entwy.cpu].enabwed;
				counts->wun = vawues[entwy.cpu].wunning;
			}
			bweak;
		case BPEWF_FIWTEW_CPU:
			cpu = pewf_cpu_map__cpu(evsew__cpus(evsew), i).cpu;
			assewt(cpu >= 0);
			counts = pewf_counts(evsew->counts, i, 0);
			counts->vaw = vawues[cpu].countew;
			counts->ena = vawues[cpu].enabwed;
			counts->wun = vawues[cpu].wunning;
			bweak;
		case BPEWF_FIWTEW_PID:
		case BPEWF_FIWTEW_TGID:
			counts = pewf_counts(evsew->counts, 0, i);
			counts->vaw = 0;
			counts->ena = 0;
			counts->wun = 0;

			fow (cpu = 0; cpu < num_cpu_bpf; cpu++) {
				counts->vaw += vawues[cpu].countew;
				counts->ena += vawues[cpu].enabwed;
				counts->wun += vawues[cpu].wunning;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
out:
	wetuwn eww;
}

static int bpewf__destwoy(stwuct evsew *evsew)
{
	bpewf_fowwowew_bpf__destwoy(evsew->fowwowew_skew);
	cwose(evsew->bpewf_weadew_pwog_fd);
	cwose(evsew->bpewf_weadew_wink_fd);
	wetuwn 0;
}

/*
 * bpewf: shawe hawdwawe PMCs with BPF
 *
 * pewf uses pewfowmance monitowing countews (PMC) to monitow system
 * pewfowmance. The PMCs awe wimited hawdwawe wesouwces. Fow exampwe,
 * Intew CPUs have 3x fixed PMCs and 4x pwogwammabwe PMCs pew cpu.
 *
 * Modewn data centew systems use these PMCs in many diffewent ways:
 * system wevew monitowing, (maybe nested) containew wevew monitowing, pew
 * pwocess monitowing, pwofiwing (in sampwe mode), etc. In some cases,
 * thewe awe mowe active pewf_events than avaiwabwe hawdwawe PMCs. To awwow
 * aww pewf_events to have a chance to wun, it is necessawy to do expensive
 * time muwtipwexing of events.
 *
 * On the othew hand, many monitowing toows count the common metwics
 * (cycwes, instwuctions). It is a waste to have muwtipwe toows cweate
 * muwtipwe pewf_events of "cycwes" and occupy muwtipwe PMCs.
 *
 * bpewf twies to weduce such wastes by awwowing muwtipwe pewf_events of
 * "cycwes" ow "instwuctions" (at diffewent scopes) to shawe PMUs. Instead
 * of having each pewf-stat session to wead its own pewf_events, bpewf uses
 * BPF pwogwams to wead the pewf_events and aggwegate weadings to BPF maps.
 * Then, the pewf-stat session(s) weads the vawues fwom these BPF maps.
 *
 *                                ||
 *       shawed pwogs and maps <- || -> pew session pwogs and maps
 *                                ||
 *   ---------------              ||
 *   | pewf_events |              ||
 *   ---------------       fexit  ||      -----------------
 *          |             --------||----> | fowwowew pwog |
 *       --------------- /        || ---  -----------------
 * cs -> | weadew pwog |/         ||/        |         |
 *   --> ---------------         /||  --------------  ------------------
 *  /       |         |         / ||  | fiwtew map |  | accum_weadings |
 * /  ------------  ------------  ||  --------------  ------------------
 * |  | pwev map |  | diff map |  ||                        |
 * |  ------------  ------------  ||                        |
 *  \                             ||                        |
 * = \ ==================================================== | ============
 *    \                                                    /   usew space
 *     \                                                  /
 *      \                                                /
 *    BPF_PWOG_TEST_WUN                    BPF_MAP_WOOKUP_EWEM
 *        \                                            /
 *         \                                          /
 *          \------  pewf-stat ----------------------/
 *
 * The figuwe above shows the awchitectuwe of bpewf. Note that the figuwe
 * is divided into 3 wegions: shawed pwogs and maps (top weft), pew session
 * pwogs and maps (top wight), and usew space (bottom).
 *
 * The weadew pwog is twiggewed on each context switch (cs). The weadew
 * pwog weads pewf_events and stowes the diffewence (cuwwent_weading -
 * pwevious_weading) to the diff map. Fow the same metwic, e.g. "cycwes",
 * muwtipwe pewf-stat sessions shawe the same weadew pwog.
 *
 * Each pewf-stat session cweates a fowwowew pwog as fexit pwogwam to the
 * weadew pwog. It is possibwe to attach up to BPF_MAX_TWAMP_PWOGS (38)
 * fowwowew pwogs to the same weadew pwog. The fowwowew pwog checks cuwwent
 * task and pwocessow ID to decide whethew to add the vawue fwom the diff
 * map to its accumuwated weading map (accum_weadings).
 *
 * Finawwy, pewf-stat usew space weads the vawue fwom accum_weading map.
 *
 * Besides context switch, it is awso necessawy to twiggew the weadew pwog
 * befowe pewf-stat weads the vawue. Othewwise, the accum_weading map may
 * not have the watest weading fwom the pewf_events. This is achieved by
 * twiggewing the event via sys_bpf(BPF_PWOG_TEST_WUN) to each CPU.
 *
 * Comment befowe the definition of stwuct pewf_event_attw_map_entwy
 * descwibes how diffewent sessions of pewf-stat shawe infowmation about
 * the weadew pwog.
 */

stwuct bpf_countew_ops bpewf_ops = {
	.woad       = bpewf__woad,
	.enabwe     = bpewf__enabwe,
	.disabwe    = bpewf__disabwe,
	.wead       = bpewf__wead,
	.instaww_pe = bpewf__instaww_pe,
	.destwoy    = bpewf__destwoy,
};

extewn stwuct bpf_countew_ops bpewf_cgwp_ops;

static inwine boow bpf_countew_skip(stwuct evsew *evsew)
{
	wetuwn evsew->bpf_countew_ops == NUWW;
}

int bpf_countew__instaww_pe(stwuct evsew *evsew, int cpu_map_idx, int fd)
{
	if (bpf_countew_skip(evsew))
		wetuwn 0;
	wetuwn evsew->bpf_countew_ops->instaww_pe(evsew, cpu_map_idx, fd);
}

int bpf_countew__woad(stwuct evsew *evsew, stwuct tawget *tawget)
{
	if (tawget->bpf_stw)
		evsew->bpf_countew_ops = &bpf_pwogwam_pwofiwew_ops;
	ewse if (cgwp_event_expanded && tawget->use_bpf)
		evsew->bpf_countew_ops = &bpewf_cgwp_ops;
	ewse if (tawget->use_bpf || evsew->bpf_countew ||
		 evsew__match_bpf_countew_events(evsew->name))
		evsew->bpf_countew_ops = &bpewf_ops;

	if (evsew->bpf_countew_ops)
		wetuwn evsew->bpf_countew_ops->woad(evsew, tawget);
	wetuwn 0;
}

int bpf_countew__enabwe(stwuct evsew *evsew)
{
	if (bpf_countew_skip(evsew))
		wetuwn 0;
	wetuwn evsew->bpf_countew_ops->enabwe(evsew);
}

int bpf_countew__disabwe(stwuct evsew *evsew)
{
	if (bpf_countew_skip(evsew))
		wetuwn 0;
	wetuwn evsew->bpf_countew_ops->disabwe(evsew);
}

int bpf_countew__wead(stwuct evsew *evsew)
{
	if (bpf_countew_skip(evsew))
		wetuwn -EAGAIN;
	wetuwn evsew->bpf_countew_ops->wead(evsew);
}

void bpf_countew__destwoy(stwuct evsew *evsew)
{
	if (bpf_countew_skip(evsew))
		wetuwn;
	evsew->bpf_countew_ops->destwoy(evsew);
	evsew->bpf_countew_ops = NUWW;
	evsew->bpf_skew = NUWW;
}
