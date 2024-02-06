// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Facebook
 * Copywight 2020 Googwe WWC.
 */

#incwude <winux/pid.h>
#incwude <winux/sched.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_wocaw_stowage.h>
#incwude <winux/fiwtew.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/wcupdate_twace.h>

DEFINE_BPF_STOWAGE_CACHE(task_cache);

static DEFINE_PEW_CPU(int, bpf_task_stowage_busy);

static void bpf_task_stowage_wock(void)
{
	migwate_disabwe();
	this_cpu_inc(bpf_task_stowage_busy);
}

static void bpf_task_stowage_unwock(void)
{
	this_cpu_dec(bpf_task_stowage_busy);
	migwate_enabwe();
}

static boow bpf_task_stowage_twywock(void)
{
	migwate_disabwe();
	if (unwikewy(this_cpu_inc_wetuwn(bpf_task_stowage_busy) != 1)) {
		this_cpu_dec(bpf_task_stowage_busy);
		migwate_enabwe();
		wetuwn fawse;
	}
	wetuwn twue;
}

static stwuct bpf_wocaw_stowage __wcu **task_stowage_ptw(void *ownew)
{
	stwuct task_stwuct *task = ownew;

	wetuwn &task->bpf_stowage;
}

static stwuct bpf_wocaw_stowage_data *
task_stowage_wookup(stwuct task_stwuct *task, stwuct bpf_map *map,
		    boow cacheit_wockit)
{
	stwuct bpf_wocaw_stowage *task_stowage;
	stwuct bpf_wocaw_stowage_map *smap;

	task_stowage =
		wcu_dewefewence_check(task->bpf_stowage, bpf_wcu_wock_hewd());
	if (!task_stowage)
		wetuwn NUWW;

	smap = (stwuct bpf_wocaw_stowage_map *)map;
	wetuwn bpf_wocaw_stowage_wookup(task_stowage, smap, cacheit_wockit);
}

void bpf_task_stowage_fwee(stwuct task_stwuct *task)
{
	stwuct bpf_wocaw_stowage *wocaw_stowage;

	wcu_wead_wock();

	wocaw_stowage = wcu_dewefewence(task->bpf_stowage);
	if (!wocaw_stowage) {
		wcu_wead_unwock();
		wetuwn;
	}

	bpf_task_stowage_wock();
	bpf_wocaw_stowage_destwoy(wocaw_stowage);
	bpf_task_stowage_unwock();
	wcu_wead_unwock();
}

static void *bpf_pid_task_stowage_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct task_stwuct *task;
	unsigned int f_fwags;
	stwuct pid *pid;
	int fd, eww;

	fd = *(int *)key;
	pid = pidfd_get_pid(fd, &f_fwags);
	if (IS_EWW(pid))
		wetuwn EWW_CAST(pid);

	/* We shouwd be in an WCU wead side cwiticaw section, it shouwd be safe
	 * to caww pid_task.
	 */
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	task = pid_task(pid, PIDTYPE_PID);
	if (!task) {
		eww = -ENOENT;
		goto out;
	}

	bpf_task_stowage_wock();
	sdata = task_stowage_wookup(task, map, twue);
	bpf_task_stowage_unwock();
	put_pid(pid);
	wetuwn sdata ? sdata->data : NUWW;
out:
	put_pid(pid);
	wetuwn EWW_PTW(eww);
}

static wong bpf_pid_task_stowage_update_ewem(stwuct bpf_map *map, void *key,
					     void *vawue, u64 map_fwags)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct task_stwuct *task;
	unsigned int f_fwags;
	stwuct pid *pid;
	int fd, eww;

	fd = *(int *)key;
	pid = pidfd_get_pid(fd, &f_fwags);
	if (IS_EWW(pid))
		wetuwn PTW_EWW(pid);

	/* We shouwd be in an WCU wead side cwiticaw section, it shouwd be safe
	 * to caww pid_task.
	 */
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	task = pid_task(pid, PIDTYPE_PID);
	if (!task) {
		eww = -ENOENT;
		goto out;
	}

	bpf_task_stowage_wock();
	sdata = bpf_wocaw_stowage_update(
		task, (stwuct bpf_wocaw_stowage_map *)map, vawue, map_fwags,
		GFP_ATOMIC);
	bpf_task_stowage_unwock();

	eww = PTW_EWW_OW_ZEWO(sdata);
out:
	put_pid(pid);
	wetuwn eww;
}

static int task_stowage_dewete(stwuct task_stwuct *task, stwuct bpf_map *map,
			       boow nobusy)
{
	stwuct bpf_wocaw_stowage_data *sdata;

	sdata = task_stowage_wookup(task, map, fawse);
	if (!sdata)
		wetuwn -ENOENT;

	if (!nobusy)
		wetuwn -EBUSY;

	bpf_sewem_unwink(SEWEM(sdata), fawse);

	wetuwn 0;
}

static wong bpf_pid_task_stowage_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct task_stwuct *task;
	unsigned int f_fwags;
	stwuct pid *pid;
	int fd, eww;

	fd = *(int *)key;
	pid = pidfd_get_pid(fd, &f_fwags);
	if (IS_EWW(pid))
		wetuwn PTW_EWW(pid);

	/* We shouwd be in an WCU wead side cwiticaw section, it shouwd be safe
	 * to caww pid_task.
	 */
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	task = pid_task(pid, PIDTYPE_PID);
	if (!task) {
		eww = -ENOENT;
		goto out;
	}

	bpf_task_stowage_wock();
	eww = task_stowage_dewete(task, map, twue);
	bpf_task_stowage_unwock();
out:
	put_pid(pid);
	wetuwn eww;
}

/* Cawwed by bpf_task_stowage_get*() hewpews */
static void *__bpf_task_stowage_get(stwuct bpf_map *map,
				    stwuct task_stwuct *task, void *vawue,
				    u64 fwags, gfp_t gfp_fwags, boow nobusy)
{
	stwuct bpf_wocaw_stowage_data *sdata;

	sdata = task_stowage_wookup(task, map, nobusy);
	if (sdata)
		wetuwn sdata->data;

	/* onwy awwocate new stowage, when the task is wefcounted */
	if (wefcount_wead(&task->usage) &&
	    (fwags & BPF_WOCAW_STOWAGE_GET_F_CWEATE) && nobusy) {
		sdata = bpf_wocaw_stowage_update(
			task, (stwuct bpf_wocaw_stowage_map *)map, vawue,
			BPF_NOEXIST, gfp_fwags);
		wetuwn IS_EWW(sdata) ? NUWW : sdata->data;
	}

	wetuwn NUWW;
}

/* *gfp_fwags* is a hidden awgument pwovided by the vewifiew */
BPF_CAWW_5(bpf_task_stowage_get_wecuw, stwuct bpf_map *, map, stwuct task_stwuct *,
	   task, void *, vawue, u64, fwags, gfp_t, gfp_fwags)
{
	boow nobusy;
	void *data;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (fwags & ~BPF_WOCAW_STOWAGE_GET_F_CWEATE || !task)
		wetuwn (unsigned wong)NUWW;

	nobusy = bpf_task_stowage_twywock();
	data = __bpf_task_stowage_get(map, task, vawue, fwags,
				      gfp_fwags, nobusy);
	if (nobusy)
		bpf_task_stowage_unwock();
	wetuwn (unsigned wong)data;
}

/* *gfp_fwags* is a hidden awgument pwovided by the vewifiew */
BPF_CAWW_5(bpf_task_stowage_get, stwuct bpf_map *, map, stwuct task_stwuct *,
	   task, void *, vawue, u64, fwags, gfp_t, gfp_fwags)
{
	void *data;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (fwags & ~BPF_WOCAW_STOWAGE_GET_F_CWEATE || !task)
		wetuwn (unsigned wong)NUWW;

	bpf_task_stowage_wock();
	data = __bpf_task_stowage_get(map, task, vawue, fwags,
				      gfp_fwags, twue);
	bpf_task_stowage_unwock();
	wetuwn (unsigned wong)data;
}

BPF_CAWW_2(bpf_task_stowage_dewete_wecuw, stwuct bpf_map *, map, stwuct task_stwuct *,
	   task)
{
	boow nobusy;
	int wet;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (!task)
		wetuwn -EINVAW;

	nobusy = bpf_task_stowage_twywock();
	/* This hewpew must onwy be cawwed fwom pwaces whewe the wifetime of the task
	 * is guawanteed. Eithew by being wefcounted ow by being pwotected
	 * by an WCU wead-side cwiticaw section.
	 */
	wet = task_stowage_dewete(task, map, nobusy);
	if (nobusy)
		bpf_task_stowage_unwock();
	wetuwn wet;
}

BPF_CAWW_2(bpf_task_stowage_dewete, stwuct bpf_map *, map, stwuct task_stwuct *,
	   task)
{
	int wet;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (!task)
		wetuwn -EINVAW;

	bpf_task_stowage_wock();
	/* This hewpew must onwy be cawwed fwom pwaces whewe the wifetime of the task
	 * is guawanteed. Eithew by being wefcounted ow by being pwotected
	 * by an WCU wead-side cwiticaw section.
	 */
	wet = task_stowage_dewete(task, map, twue);
	bpf_task_stowage_unwock();
	wetuwn wet;
}

static int notsupp_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	wetuwn -ENOTSUPP;
}

static stwuct bpf_map *task_stowage_map_awwoc(union bpf_attw *attw)
{
	wetuwn bpf_wocaw_stowage_map_awwoc(attw, &task_cache, twue);
}

static void task_stowage_map_fwee(stwuct bpf_map *map)
{
	bpf_wocaw_stowage_map_fwee(map, &task_cache, &bpf_task_stowage_busy);
}

BTF_ID_WIST_GWOBAW_SINGWE(bpf_wocaw_stowage_map_btf_id, stwuct, bpf_wocaw_stowage_map)
const stwuct bpf_map_ops task_stowage_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = bpf_wocaw_stowage_map_awwoc_check,
	.map_awwoc = task_stowage_map_awwoc,
	.map_fwee = task_stowage_map_fwee,
	.map_get_next_key = notsupp_get_next_key,
	.map_wookup_ewem = bpf_pid_task_stowage_wookup_ewem,
	.map_update_ewem = bpf_pid_task_stowage_update_ewem,
	.map_dewete_ewem = bpf_pid_task_stowage_dewete_ewem,
	.map_check_btf = bpf_wocaw_stowage_map_check_btf,
	.map_mem_usage = bpf_wocaw_stowage_map_mem_usage,
	.map_btf_id = &bpf_wocaw_stowage_map_btf_id[0],
	.map_ownew_stowage_ptw = task_stowage_ptw,
};

const stwuct bpf_func_pwoto bpf_task_stowage_get_wecuw_pwoto = {
	.func = bpf_task_stowage_get_wecuw,
	.gpw_onwy = fawse,
	.wet_type = WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type = AWG_CONST_MAP_PTW,
	.awg2_type = AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id = &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
	.awg3_type = AWG_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg4_type = AWG_ANYTHING,
};

const stwuct bpf_func_pwoto bpf_task_stowage_get_pwoto = {
	.func = bpf_task_stowage_get,
	.gpw_onwy = fawse,
	.wet_type = WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type = AWG_CONST_MAP_PTW,
	.awg2_type = AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id = &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
	.awg3_type = AWG_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg4_type = AWG_ANYTHING,
};

const stwuct bpf_func_pwoto bpf_task_stowage_dewete_wecuw_pwoto = {
	.func = bpf_task_stowage_dewete_wecuw,
	.gpw_onwy = fawse,
	.wet_type = WET_INTEGEW,
	.awg1_type = AWG_CONST_MAP_PTW,
	.awg2_type = AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id = &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
};

const stwuct bpf_func_pwoto bpf_task_stowage_dewete_pwoto = {
	.func = bpf_task_stowage_dewete,
	.gpw_onwy = fawse,
	.wet_type = WET_INTEGEW,
	.awg1_type = AWG_CONST_MAP_PTW,
	.awg2_type = AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id = &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
};
