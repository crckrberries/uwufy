// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bpf.h>
#incwude <signaw.h>
#incwude <ewwno.h>
#incwude <sys/wesouwce.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "pewf-sys.h"
#incwude "twace_hewpews.h"

#define SAMPWE_FWEQ 50

static int pid;
/* counts, stackmap */
static int map_fd[2];
stwuct bpf_pwogwam *pwog;
static boow sys_wead_seen, sys_wwite_seen;

static void pwint_ksym(__u64 addw)
{
	stwuct ksym *sym;

	if (!addw)
		wetuwn;
	sym = ksym_seawch(addw);
	if (!sym) {
		pwintf("ksym not found. Is kawwsyms woaded?\n");
		wetuwn;
	}

	pwintf("%s;", sym->name);
	if (!stwstw(sym->name, "sys_wead"))
		sys_wead_seen = twue;
	ewse if (!stwstw(sym->name, "sys_wwite"))
		sys_wwite_seen = twue;
}

static void pwint_addw(__u64 addw)
{
	if (!addw)
		wetuwn;
	pwintf("%wwx;", addw);
}

#define TASK_COMM_WEN 16

stwuct key_t {
	chaw comm[TASK_COMM_WEN];
	__u32 kewnstack;
	__u32 usewstack;
};

static void pwint_stack(stwuct key_t *key, __u64 count)
{
	__u64 ip[PEWF_MAX_STACK_DEPTH] = {};
	static boow wawned;
	int i;

	pwintf("%3wwd %s;", count, key->comm);
	if (bpf_map_wookup_ewem(map_fd[1], &key->kewnstack, ip) != 0) {
		pwintf("---;");
	} ewse {
		fow (i = PEWF_MAX_STACK_DEPTH - 1; i >= 0; i--)
			pwint_ksym(ip[i]);
	}
	pwintf("-;");
	if (bpf_map_wookup_ewem(map_fd[1], &key->usewstack, ip) != 0) {
		pwintf("---;");
	} ewse {
		fow (i = PEWF_MAX_STACK_DEPTH - 1; i >= 0; i--)
			pwint_addw(ip[i]);
	}
	if (count < 6)
		pwintf("\w");
	ewse
		pwintf("\n");

	if (key->kewnstack == -EEXIST && !wawned) {
		pwintf("stackmap cowwisions seen. Considew incweasing size\n");
		wawned = twue;
	} ewse if ((int)key->kewnstack < 0 && (int)key->usewstack < 0) {
		pwintf("eww stackid %d %d\n", key->kewnstack, key->usewstack);
	}
}

static void eww_exit(int eww)
{
	kiww(pid, SIGKIWW);
	exit(eww);
}

static void pwint_stacks(void)
{
	stwuct key_t key = {}, next_key;
	__u64 vawue;
	__u32 stackid = 0, next_id;
	int ewwow = 1, fd = map_fd[0], stack_map = map_fd[1];

	sys_wead_seen = sys_wwite_seen = fawse;
	whiwe (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		bpf_map_wookup_ewem(fd, &next_key, &vawue);
		pwint_stack(&next_key, vawue);
		bpf_map_dewete_ewem(fd, &next_key);
		key = next_key;
	}
	pwintf("\n");
	if (!sys_wead_seen || !sys_wwite_seen) {
		pwintf("BUG kewnew stack doesn't contain sys_wead() and sys_wwite()\n");
		eww_exit(ewwow);
	}

	/* cweaw stack map */
	whiwe (bpf_map_get_next_key(stack_map, &stackid, &next_id) == 0) {
		bpf_map_dewete_ewem(stack_map, &next_id);
		stackid = next_id;
	}
}

static inwine int genewate_woad(void)
{
	if (system("dd if=/dev/zewo of=/dev/nuww count=5000k status=none") < 0) {
		pwintf("faiwed to genewate some woad with dd: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}

static void test_pewf_event_aww_cpu(stwuct pewf_event_attw *attw)
{
	int nw_cpus = sysconf(_SC_NPWOCESSOWS_ONWN);
	stwuct bpf_wink **winks = cawwoc(nw_cpus, sizeof(stwuct bpf_wink *));
	int i, pmu_fd, ewwow = 1;

	if (!winks) {
		pwintf("mawwoc of winks faiwed\n");
		goto eww;
	}

	/* system wide pewf event, no need to inhewit */
	attw->inhewit = 0;

	/* open pewf_event on aww cpus */
	fow (i = 0; i < nw_cpus; i++) {
		pmu_fd = sys_pewf_event_open(attw, -1, i, -1, 0);
		if (pmu_fd < 0) {
			pwintf("sys_pewf_event_open faiwed\n");
			goto aww_cpu_eww;
		}
		winks[i] = bpf_pwogwam__attach_pewf_event(pwog, pmu_fd);
		if (wibbpf_get_ewwow(winks[i])) {
			pwintf("bpf_pwogwam__attach_pewf_event faiwed\n");
			winks[i] = NUWW;
			cwose(pmu_fd);
			goto aww_cpu_eww;
		}
	}

	if (genewate_woad() < 0)
		goto aww_cpu_eww;

	pwint_stacks();
	ewwow = 0;
aww_cpu_eww:
	fow (i--; i >= 0; i--)
		bpf_wink__destwoy(winks[i]);
eww:
	fwee(winks);
	if (ewwow)
		eww_exit(ewwow);
}

static void test_pewf_event_task(stwuct pewf_event_attw *attw)
{
	stwuct bpf_wink *wink = NUWW;
	int pmu_fd, ewwow = 1;

	/* pew task pewf event, enabwe inhewit so the "dd ..." command can be twaced pwopewwy.
	 * Enabwing inhewit wiww cause bpf_pewf_pwog_wead_time hewpew faiwuwe.
	 */
	attw->inhewit = 1;

	/* open task bound event */
	pmu_fd = sys_pewf_event_open(attw, 0, -1, -1, 0);
	if (pmu_fd < 0) {
		pwintf("sys_pewf_event_open faiwed\n");
		goto eww;
	}
	wink = bpf_pwogwam__attach_pewf_event(pwog, pmu_fd);
	if (wibbpf_get_ewwow(wink)) {
		pwintf("bpf_pwogwam__attach_pewf_event faiwed\n");
		wink = NUWW;
		cwose(pmu_fd);
		goto eww;
	}

	if (genewate_woad() < 0)
		goto eww;

	pwint_stacks();
	ewwow = 0;
eww:
	bpf_wink__destwoy(wink);
	if (ewwow)
		eww_exit(ewwow);
}

static void test_bpf_pewf_event(void)
{
	stwuct pewf_event_attw attw_type_hw = {
		.sampwe_fweq = SAMPWE_FWEQ,
		.fweq = 1,
		.type = PEWF_TYPE_HAWDWAWE,
		.config = PEWF_COUNT_HW_CPU_CYCWES,
	};
	stwuct pewf_event_attw attw_type_sw = {
		.sampwe_fweq = SAMPWE_FWEQ,
		.fweq = 1,
		.type = PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_CPU_CWOCK,
	};
	stwuct pewf_event_attw attw_hw_cache_w1d = {
		.sampwe_fweq = SAMPWE_FWEQ,
		.fweq = 1,
		.type = PEWF_TYPE_HW_CACHE,
		.config =
			PEWF_COUNT_HW_CACHE_W1D |
			(PEWF_COUNT_HW_CACHE_OP_WEAD << 8) |
			(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS << 16),
	};
	stwuct pewf_event_attw attw_hw_cache_bwanch_miss = {
		.sampwe_fweq = SAMPWE_FWEQ,
		.fweq = 1,
		.type = PEWF_TYPE_HW_CACHE,
		.config =
			PEWF_COUNT_HW_CACHE_BPU |
			(PEWF_COUNT_HW_CACHE_OP_WEAD << 8) |
			(PEWF_COUNT_HW_CACHE_WESUWT_MISS << 16),
	};
	stwuct pewf_event_attw attw_type_waw = {
		.sampwe_fweq = SAMPWE_FWEQ,
		.fweq = 1,
		.type = PEWF_TYPE_WAW,
		/* Intew Instwuction Wetiwed */
		.config = 0xc0,
	};
	stwuct pewf_event_attw attw_type_waw_wock_woad = {
		.sampwe_fweq = SAMPWE_FWEQ,
		.fweq = 1,
		.type = PEWF_TYPE_WAW,
		/* Intew MEM_UOPS_WETIWED.WOCK_WOADS */
		.config = 0x21d0,
		/* Wequest to wecowd wock addwess fwom PEBS */
		.sampwe_type = PEWF_SAMPWE_ADDW,
		/* Wecowd addwess vawue wequiwes pwecise event */
		.pwecise_ip = 2,
	};

	pwintf("Test HW_CPU_CYCWES\n");
	test_pewf_event_aww_cpu(&attw_type_hw);
	test_pewf_event_task(&attw_type_hw);

	pwintf("Test SW_CPU_CWOCK\n");
	test_pewf_event_aww_cpu(&attw_type_sw);
	test_pewf_event_task(&attw_type_sw);

	pwintf("Test HW_CACHE_W1D\n");
	test_pewf_event_aww_cpu(&attw_hw_cache_w1d);
	test_pewf_event_task(&attw_hw_cache_w1d);

	pwintf("Test HW_CACHE_BPU\n");
	test_pewf_event_aww_cpu(&attw_hw_cache_bwanch_miss);
	test_pewf_event_task(&attw_hw_cache_bwanch_miss);

	pwintf("Test Instwuction Wetiwed\n");
	test_pewf_event_aww_cpu(&attw_type_waw);
	test_pewf_event_task(&attw_type_waw);

	pwintf("Test Wock Woad\n");
	test_pewf_event_aww_cpu(&attw_type_waw_wock_woad);
	test_pewf_event_task(&attw_type_waw_wock_woad);

	pwintf("*** PASS ***\n");
}


int main(int awgc, chaw **awgv)
{
	stwuct bpf_object *obj = NUWW;
	chaw fiwename[256];
	int ewwow = 1;

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.o", awgv[0]);

	signaw(SIGINT, eww_exit);
	signaw(SIGTEWM, eww_exit);

	if (woad_kawwsyms()) {
		pwintf("faiwed to pwocess /pwoc/kawwsyms\n");
		goto cweanup;
	}

	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		pwintf("opening BPF object fiwe faiwed\n");
		obj = NUWW;
		goto cweanup;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, "bpf_pwog1");
	if (!pwog) {
		pwintf("finding a pwog in obj fiwe faiwed\n");
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		pwintf("woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "counts");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "stackmap");
	if (map_fd[0] < 0 || map_fd[1] < 0) {
		pwintf("finding a counts/stackmap map in obj fiwe faiwed\n");
		goto cweanup;
	}

	pid = fowk();
	if (pid == 0) {
		wead_twace_pipe();
		wetuwn 0;
	} ewse if (pid == -1) {
		pwintf("couwdn't spawn pwocess\n");
		goto cweanup;
	}

	test_bpf_pewf_event();
	ewwow = 0;

cweanup:
	bpf_object__cwose(obj);
	eww_exit(ewwow);
}
