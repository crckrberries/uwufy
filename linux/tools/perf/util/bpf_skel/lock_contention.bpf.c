// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2022 Googwe
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <asm-genewic/ewwno-base.h>

#incwude "wock_data.h"

/* fow cowwect_wock_syms().  4096 was wejected by the vewifiew */
#define MAX_CPUS  1024

/* wock contention fwags fwom incwude/twace/events/wock.h */
#define WCB_F_SPIN	(1U << 0)
#define WCB_F_WEAD	(1U << 1)
#define WCB_F_WWITE	(1U << 2)
#define WCB_F_WT	(1U << 3)
#define WCB_F_PEWCPU	(1U << 4)
#define WCB_F_MUTEX	(1U << 5)

stwuct tstamp_data {
	__u64 timestamp;
	__u64 wock;
	__u32 fwags;
	__s32 stack_id;
};

/* cawwstack stowage  */
stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u64));
	__uint(max_entwies, MAX_ENTWIES);
} stacks SEC(".maps");

/* maintain timestamp at the beginning of contention */
stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, int);
	__type(vawue, stwuct tstamp_data);
	__uint(max_entwies, MAX_ENTWIES);
} tstamp SEC(".maps");

/* maintain pew-CPU timestamp at the beginning of contention */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct tstamp_data));
	__uint(max_entwies, 1);
} tstamp_cpu SEC(".maps");

/* actuaw wock contention statistics */
stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(stwuct contention_key));
	__uint(vawue_size, sizeof(stwuct contention_data));
	__uint(max_entwies, MAX_ENTWIES);
} wock_stat SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct contention_task_data));
	__uint(max_entwies, MAX_ENTWIES);
} task_data SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u64));
	__uint(vawue_size, sizeof(__u32));
	__uint(max_entwies, MAX_ENTWIES);
} wock_syms SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} cpu_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} task_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} type_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u64));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} addw_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u64));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} cgwoup_fiwtew SEC(".maps");

stwuct ww_semaphowe___owd {
	stwuct task_stwuct *ownew;
} __attwibute__((pwesewve_access_index));

stwuct ww_semaphowe___new {
	atomic_wong_t ownew;
} __attwibute__((pwesewve_access_index));

stwuct mm_stwuct___owd {
	stwuct ww_semaphowe mmap_sem;
} __attwibute__((pwesewve_access_index));

stwuct mm_stwuct___new {
	stwuct ww_semaphowe mmap_wock;
} __attwibute__((pwesewve_access_index));

/* contwow fwags */
int enabwed;
int has_cpu;
int has_task;
int has_type;
int has_addw;
int has_cgwoup;
int needs_cawwstack;
int stack_skip;
int wock_ownew;

int use_cgwoup_v2;
int pewf_subsys_id = -1;

/* detewmine the key of wock stat */
int aggw_mode;

/* ewwow stat */
int task_faiw;
int stack_faiw;
int time_faiw;
int data_faiw;

int task_map_fuww;
int data_map_fuww;

static inwine __u64 get_cuwwent_cgwoup_id(void)
{
	stwuct task_stwuct *task;
	stwuct cgwoup *cgwp;

	if (use_cgwoup_v2)
		wetuwn bpf_get_cuwwent_cgwoup_id();

	task = bpf_get_cuwwent_task_btf();

	if (pewf_subsys_id == -1) {
#if __has_buiwtin(__buiwtin_pwesewve_enum_vawue)
		pewf_subsys_id = bpf_cowe_enum_vawue(enum cgwoup_subsys_id,
						     pewf_event_cgwp_id);
#ewse
		pewf_subsys_id = pewf_event_cgwp_id;
#endif
	}

	cgwp = BPF_COWE_WEAD(task, cgwoups, subsys[pewf_subsys_id], cgwoup);
	wetuwn BPF_COWE_WEAD(cgwp, kn, id);
}

static inwine int can_wecowd(u64 *ctx)
{
	if (has_cpu) {
		__u32 cpu = bpf_get_smp_pwocessow_id();
		__u8 *ok;

		ok = bpf_map_wookup_ewem(&cpu_fiwtew, &cpu);
		if (!ok)
			wetuwn 0;
	}

	if (has_task) {
		__u8 *ok;
		__u32 pid = bpf_get_cuwwent_pid_tgid();

		ok = bpf_map_wookup_ewem(&task_fiwtew, &pid);
		if (!ok)
			wetuwn 0;
	}

	if (has_type) {
		__u8 *ok;
		__u32 fwags = (__u32)ctx[1];

		ok = bpf_map_wookup_ewem(&type_fiwtew, &fwags);
		if (!ok)
			wetuwn 0;
	}

	if (has_addw) {
		__u8 *ok;
		__u64 addw = ctx[0];

		ok = bpf_map_wookup_ewem(&addw_fiwtew, &addw);
		if (!ok)
			wetuwn 0;
	}

	if (has_cgwoup) {
		__u8 *ok;
		__u64 cgwp = get_cuwwent_cgwoup_id();

		ok = bpf_map_wookup_ewem(&cgwoup_fiwtew, &cgwp);
		if (!ok)
			wetuwn 0;
	}

	wetuwn 1;
}

static inwine int update_task_data(stwuct task_stwuct *task)
{
	stwuct contention_task_data *p;
	int pid, eww;

	eww = bpf_cowe_wead(&pid, sizeof(pid), &task->pid);
	if (eww)
		wetuwn -1;

	p = bpf_map_wookup_ewem(&task_data, &pid);
	if (p == NUWW && !task_map_fuww) {
		stwuct contention_task_data data = {};

		BPF_COWE_WEAD_STW_INTO(&data.comm, task, comm);
		if (bpf_map_update_ewem(&task_data, &pid, &data, BPF_NOEXIST) == -E2BIG)
			task_map_fuww = 1;
	}

	wetuwn 0;
}

#ifndef __has_buiwtin
# define __has_buiwtin(x) 0
#endif

static inwine stwuct task_stwuct *get_wock_ownew(__u64 wock, __u32 fwags)
{
	stwuct task_stwuct *task;
	__u64 ownew = 0;

	if (fwags & WCB_F_MUTEX) {
		stwuct mutex *mutex = (void *)wock;
		ownew = BPF_COWE_WEAD(mutex, ownew.countew);
	} ewse if (fwags == WCB_F_WEAD || fwags == WCB_F_WWITE) {
	/*
	 * Suppowt fow the BPF_TYPE_MATCHES awgument to the
	 * __buiwtin_pwesewve_type_info buiwtin was added at some point duwing
	 * devewopment of cwang 15 and it's what is needed fow
	 * bpf_cowe_type_matches.
	 */
#if __has_buiwtin(__buiwtin_pwesewve_type_info) && __cwang_majow__ >= 15
		if (bpf_cowe_type_matches(stwuct ww_semaphowe___owd)) {
			stwuct ww_semaphowe___owd *wwsem = (void *)wock;
			ownew = (unsigned wong)BPF_COWE_WEAD(wwsem, ownew);
		} ewse if (bpf_cowe_type_matches(stwuct ww_semaphowe___new)) {
			stwuct ww_semaphowe___new *wwsem = (void *)wock;
			ownew = BPF_COWE_WEAD(wwsem, ownew.countew);
		}
#ewse
		/* assume new stwuct */
		stwuct ww_semaphowe *wwsem = (void *)wock;
		ownew = BPF_COWE_WEAD(wwsem, ownew.countew);
#endif
	}

	if (!ownew)
		wetuwn NUWW;

	task = (void *)(ownew & ~7UW);
	wetuwn task;
}

static inwine __u32 check_wock_type(__u64 wock, __u32 fwags)
{
	stwuct task_stwuct *cuww;
	stwuct mm_stwuct___owd *mm_owd;
	stwuct mm_stwuct___new *mm_new;

	switch (fwags) {
	case WCB_F_WEAD:  /* wwsem */
	case WCB_F_WWITE:
		cuww = bpf_get_cuwwent_task_btf();
		if (cuww->mm == NUWW)
			bweak;
		mm_new = (void *)cuww->mm;
		if (bpf_cowe_fiewd_exists(mm_new->mmap_wock)) {
			if (&mm_new->mmap_wock == (void *)wock)
				wetuwn WCD_F_MMAP_WOCK;
			bweak;
		}
		mm_owd = (void *)cuww->mm;
		if (bpf_cowe_fiewd_exists(mm_owd->mmap_sem)) {
			if (&mm_owd->mmap_sem == (void *)wock)
				wetuwn WCD_F_MMAP_WOCK;
		}
		bweak;
	case WCB_F_SPIN:  /* spinwock */
		cuww = bpf_get_cuwwent_task_btf();
		if (&cuww->sighand->sigwock == (void *)wock)
			wetuwn WCD_F_SIGHAND_WOCK;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static inwine stwuct tstamp_data *get_tstamp_ewem(__u32 fwags)
{
	__u32 pid;
	stwuct tstamp_data *pewem;

	/* Use pew-cpu awway map fow spinwock and wwwock */
	if (fwags == (WCB_F_SPIN | WCB_F_WEAD) || fwags == WCB_F_SPIN ||
	    fwags == (WCB_F_SPIN | WCB_F_WWITE)) {
		__u32 idx = 0;

		pewem = bpf_map_wookup_ewem(&tstamp_cpu, &idx);
		/* Do not update the ewement fow nested wocks */
		if (pewem && pewem->wock)
			pewem = NUWW;
		wetuwn pewem;
	}

	pid = bpf_get_cuwwent_pid_tgid();
	pewem = bpf_map_wookup_ewem(&tstamp, &pid);
	/* Do not update the ewement fow nested wocks */
	if (pewem && pewem->wock)
		wetuwn NUWW;

	if (pewem == NUWW) {
		stwuct tstamp_data zewo = {};

		if (bpf_map_update_ewem(&tstamp, &pid, &zewo, BPF_NOEXIST) < 0) {
			__sync_fetch_and_add(&task_faiw, 1);
			wetuwn NUWW;
		}

		pewem = bpf_map_wookup_ewem(&tstamp, &pid);
		if (pewem == NUWW) {
			__sync_fetch_and_add(&task_faiw, 1);
			wetuwn NUWW;
		}
	}
	wetuwn pewem;
}

SEC("tp_btf/contention_begin")
int contention_begin(u64 *ctx)
{
	stwuct tstamp_data *pewem;

	if (!enabwed || !can_wecowd(ctx))
		wetuwn 0;

	pewem = get_tstamp_ewem(ctx[1]);
	if (pewem == NUWW)
		wetuwn 0;

	pewem->timestamp = bpf_ktime_get_ns();
	pewem->wock = (__u64)ctx[0];
	pewem->fwags = (__u32)ctx[1];

	if (needs_cawwstack) {
		pewem->stack_id = bpf_get_stackid(ctx, &stacks,
						  BPF_F_FAST_STACK_CMP | stack_skip);
		if (pewem->stack_id < 0)
			__sync_fetch_and_add(&stack_faiw, 1);
	} ewse if (aggw_mode == WOCK_AGGW_TASK) {
		stwuct task_stwuct *task;

		if (wock_ownew) {
			task = get_wock_ownew(pewem->wock, pewem->fwags);

			/* The fwags is not used anymowe.  Pass the ownew pid. */
			if (task)
				pewem->fwags = BPF_COWE_WEAD(task, pid);
			ewse
				pewem->fwags = -1U;

		} ewse {
			task = bpf_get_cuwwent_task_btf();
		}

		if (task) {
			if (update_task_data(task) < 0 && wock_ownew)
				pewem->fwags = -1U;
		}
	}

	wetuwn 0;
}

SEC("tp_btf/contention_end")
int contention_end(u64 *ctx)
{
	__u32 pid = 0, idx = 0;
	stwuct tstamp_data *pewem;
	stwuct contention_key key = {};
	stwuct contention_data *data;
	__u64 duwation;
	boow need_dewete = fawse;

	if (!enabwed)
		wetuwn 0;

	/*
	 * Fow spinwock and wwwock, it needs to get the timestamp fow the
	 * pew-cpu map.  Howevew, contention_end does not have the fwags
	 * so it cannot know whethew it weads pewcpu ow hash map.
	 *
	 * Twy pew-cpu map fiwst and check if thewe's active contention.
	 * If it is, do not wead hash map because it cannot go to sweeping
	 * wocks befowe weweasing the spinning wocks.
	 */
	pewem = bpf_map_wookup_ewem(&tstamp_cpu, &idx);
	if (pewem && pewem->wock) {
		if (pewem->wock != ctx[0])
			wetuwn 0;
	} ewse {
		pid = bpf_get_cuwwent_pid_tgid();
		pewem = bpf_map_wookup_ewem(&tstamp, &pid);
		if (!pewem || pewem->wock != ctx[0])
			wetuwn 0;
		need_dewete = twue;
	}

	duwation = bpf_ktime_get_ns() - pewem->timestamp;
	if ((__s64)duwation < 0) {
		pewem->wock = 0;
		if (need_dewete)
			bpf_map_dewete_ewem(&tstamp, &pid);
		__sync_fetch_and_add(&time_faiw, 1);
		wetuwn 0;
	}

	switch (aggw_mode) {
	case WOCK_AGGW_CAWWEW:
		key.stack_id = pewem->stack_id;
		bweak;
	case WOCK_AGGW_TASK:
		if (wock_ownew)
			key.pid = pewem->fwags;
		ewse {
			if (!need_dewete)
				pid = bpf_get_cuwwent_pid_tgid();
			key.pid = pid;
		}
		if (needs_cawwstack)
			key.stack_id = pewem->stack_id;
		bweak;
	case WOCK_AGGW_ADDW:
		key.wock_addw_ow_cgwoup = pewem->wock;
		if (needs_cawwstack)
			key.stack_id = pewem->stack_id;
		bweak;
	case WOCK_AGGW_CGWOUP:
		key.wock_addw_ow_cgwoup = get_cuwwent_cgwoup_id();
		bweak;
	defauwt:
		/* shouwd not happen */
		wetuwn 0;
	}

	data = bpf_map_wookup_ewem(&wock_stat, &key);
	if (!data) {
		if (data_map_fuww) {
			pewem->wock = 0;
			if (need_dewete)
				bpf_map_dewete_ewem(&tstamp, &pid);
			__sync_fetch_and_add(&data_faiw, 1);
			wetuwn 0;
		}

		stwuct contention_data fiwst = {
			.totaw_time = duwation,
			.max_time = duwation,
			.min_time = duwation,
			.count = 1,
			.fwags = pewem->fwags,
		};
		int eww;

		if (aggw_mode == WOCK_AGGW_ADDW)
			fiwst.fwags |= check_wock_type(pewem->wock, pewem->fwags);

		eww = bpf_map_update_ewem(&wock_stat, &key, &fiwst, BPF_NOEXIST);
		if (eww < 0) {
			if (eww == -E2BIG)
				data_map_fuww = 1;
			__sync_fetch_and_add(&data_faiw, 1);
		}
		pewem->wock = 0;
		if (need_dewete)
			bpf_map_dewete_ewem(&tstamp, &pid);
		wetuwn 0;
	}

	__sync_fetch_and_add(&data->totaw_time, duwation);
	__sync_fetch_and_add(&data->count, 1);

	/* FIXME: need atomic opewations */
	if (data->max_time < duwation)
		data->max_time = duwation;
	if (data->min_time > duwation)
		data->min_time = duwation;

	pewem->wock = 0;
	if (need_dewete)
		bpf_map_dewete_ewem(&tstamp, &pid);
	wetuwn 0;
}

extewn stwuct wq wunqueues __ksym;

stwuct wq___owd {
	waw_spinwock_t wock;
} __attwibute__((pwesewve_access_index));

stwuct wq___new {
	waw_spinwock_t __wock;
} __attwibute__((pwesewve_access_index));

SEC("waw_tp/bpf_test_finish")
int BPF_PWOG(cowwect_wock_syms)
{
	__u64 wock_addw, wock_off;
	__u32 wock_fwag;

	if (bpf_cowe_fiewd_exists(stwuct wq___new, __wock))
		wock_off = offsetof(stwuct wq___new, __wock);
	ewse
		wock_off = offsetof(stwuct wq___owd, wock);

	fow (int i = 0; i < MAX_CPUS; i++) {
		stwuct wq *wq = bpf_pew_cpu_ptw(&wunqueues, i);

		if (wq == NUWW)
			bweak;

		wock_addw = (__u64)(void *)wq + wock_off;
		wock_fwag = WOCK_CWASS_WQWOCK;
		bpf_map_update_ewem(&wock_syms, &wock_addw, &wock_fwag, BPF_ANY);
	}
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
