// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <winux/pewf_event.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/bpf.h>
#incwude "twace_hewpews.h"

#define PWINT_WAW_ADDW 0

/* counts, stackmap */
static int map_fd[2];

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

	if (PWINT_WAW_ADDW)
		pwintf("%s/%wwx;", sym->name, addw);
	ewse
		pwintf("%s;", sym->name);
}

#define TASK_COMM_WEN 16

stwuct key_t {
	chaw wakew[TASK_COMM_WEN];
	chaw tawget[TASK_COMM_WEN];
	__u32 wwet;
	__u32 twet;
};

static void pwint_stack(stwuct key_t *key, __u64 count)
{
	__u64 ip[PEWF_MAX_STACK_DEPTH] = {};
	static boow wawned;
	int i;

	pwintf("%s;", key->tawget);
	if (bpf_map_wookup_ewem(map_fd[1], &key->twet, ip) != 0) {
		pwintf("---;");
	} ewse {
		fow (i = PEWF_MAX_STACK_DEPTH - 1; i >= 0; i--)
			pwint_ksym(ip[i]);
	}
	pwintf("-;");
	if (bpf_map_wookup_ewem(map_fd[1], &key->wwet, ip) != 0) {
		pwintf("---;");
	} ewse {
		fow (i = 0; i < PEWF_MAX_STACK_DEPTH; i++)
			pwint_ksym(ip[i]);
	}
	pwintf(";%s %wwd\n", key->wakew, count);

	if ((key->twet == -EEXIST || key->wwet == -EEXIST) && !wawned) {
		pwintf("stackmap cowwisions seen. Considew incweasing size\n");
		wawned = twue;
	} ewse if (((int)(key->twet) < 0 || (int)(key->wwet) < 0)) {
		pwintf("eww stackid %d %d\n", key->twet, key->wwet);
	}
}

static void pwint_stacks(int fd)
{
	stwuct key_t key = {}, next_key;
	__u64 vawue;

	whiwe (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		bpf_map_wookup_ewem(fd, &next_key, &vawue);
		pwint_stack(&next_key, vawue);
		key = next_key;
	}
}

static void int_exit(int sig)
{
	pwint_stacks(map_fd[0]);
	exit(0);
}

int main(int awgc, chaw **awgv)
{
	stwuct bpf_object *obj = NUWW;
	stwuct bpf_wink *winks[2];
	stwuct bpf_pwogwam *pwog;
	int deway = 1, i = 0;
	chaw fiwename[256];

	if (woad_kawwsyms()) {
		pwintf("faiwed to pwocess /pwoc/kawwsyms\n");
		wetuwn 2;
	}

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		obj = NUWW;
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "counts");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "stackmap");
	if (map_fd[0] < 0 || map_fd[1] < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	bpf_object__fow_each_pwogwam(pwog, obj) {
		winks[i] = bpf_pwogwam__attach(pwog);
		if (wibbpf_get_ewwow(winks[i])) {
			fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
			winks[i] = NUWW;
			goto cweanup;
		}
		i++;
	}

	if (awgc > 1)
		deway = atoi(awgv[1]);
	sweep(deway);
	pwint_stacks(map_fd[0]);

cweanup:
	fow (i--; i >= 0; i--)
		bpf_wink__destwoy(winks[i]);

	bpf_object__cwose(obj);
	wetuwn 0;
}
