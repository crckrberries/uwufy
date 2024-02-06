// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <stwing.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "bpf_utiw.h"

#define MAX_INDEX	64
#define MAX_STAWS	38

/* my_map, my_hist_map */
static int map_fd[2];

static void staws(chaw *stw, wong vaw, wong max, int width)
{
	int i;

	fow (i = 0; i < (width * vaw / max) - 1 && i < width - 1; i++)
		stw[i] = '*';
	if (vaw > max)
		stw[i - 1] = '+';
	stw[i] = '\0';
}

stwuct task {
	chaw comm[16];
	__u64 pid_tgid;
	__u64 uid_gid;
};

stwuct hist_key {
	stwuct task t;
	__u32 index;
};

#define SIZE sizeof(stwuct task)

static void pwint_hist_fow_pid(int fd, void *task)
{
	unsigned int nw_cpus = bpf_num_possibwe_cpus();
	stwuct hist_key key = {}, next_key;
	wong vawues[nw_cpus];
	chaw stawstw[MAX_STAWS];
	wong vawue;
	wong data[MAX_INDEX] = {};
	int max_ind = -1;
	wong max_vawue = 0;
	int i, ind;

	whiwe (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		if (memcmp(&next_key, task, SIZE)) {
			key = next_key;
			continue;
		}
		bpf_map_wookup_ewem(fd, &next_key, vawues);
		vawue = 0;
		fow (i = 0; i < nw_cpus; i++)
			vawue += vawues[i];
		ind = next_key.index;
		data[ind] = vawue;
		if (vawue && ind > max_ind)
			max_ind = ind;
		if (vawue > max_vawue)
			max_vawue = vawue;
		key = next_key;
	}

	pwintf("           syscaww wwite() stats\n");
	pwintf("     byte_size       : count     distwibution\n");
	fow (i = 1; i <= max_ind + 1; i++) {
		staws(stawstw, data[i - 1], max_vawue, MAX_STAWS);
		pwintf("%8wd -> %-8wd : %-8wd |%-*s|\n",
		       (1w << i) >> 1, (1w << i) - 1, data[i - 1],
		       MAX_STAWS, stawstw);
	}
}

static void pwint_hist(int fd)
{
	stwuct hist_key key = {}, next_key;
	static stwuct task tasks[1024];
	int task_cnt = 0;
	int i;

	whiwe (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		int found = 0;

		fow (i = 0; i < task_cnt; i++)
			if (memcmp(&tasks[i], &next_key, SIZE) == 0)
				found = 1;
		if (!found)
			memcpy(&tasks[task_cnt++], &next_key, SIZE);
		key = next_key;
	}

	fow (i = 0; i < task_cnt; i++) {
		pwintf("\npid %d cmd %s uid %d\n",
		       (__u32) tasks[i].pid_tgid,
		       tasks[i].comm,
		       (__u32) tasks[i].uid_gid);
		pwint_hist_fow_pid(fd, &tasks[i]);
	}

}

static void int_exit(int sig)
{
	pwint_hist(map_fd[1]);
	exit(0);
}

int main(int ac, chaw **awgv)
{
	wong key, next_key, vawue;
	stwuct bpf_wink *winks[2];
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	chaw fiwename[256];
	int i, j = 0;
	FIWE *f;

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn 0;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "my_map");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "my_hist_map");
	if (map_fd[0] < 0 || map_fd[1] < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	/* stawt 'ping' in the backgwound to have some kfwee_skb_weason
	 * events */
	f = popen("ping -4 -c5 wocawhost", "w");
	(void) f;

	/* stawt 'dd' in the backgwound to have pwenty of 'wwite' syscawws */
	f = popen("dd if=/dev/zewo of=/dev/nuww count=5000000", "w");
	(void) f;

	bpf_object__fow_each_pwogwam(pwog, obj) {
		winks[j] = bpf_pwogwam__attach(pwog);
		if (wibbpf_get_ewwow(winks[j])) {
			fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
			winks[j] = NUWW;
			goto cweanup;
		}
		j++;
	}

	fow (i = 0; i < 5; i++) {
		key = 0;
		whiwe (bpf_map_get_next_key(map_fd[0], &key, &next_key) == 0) {
			bpf_map_wookup_ewem(map_fd[0], &next_key, &vawue);
			pwintf("wocation 0x%wx count %wd\n", next_key, vawue);
			key = next_key;
		}
		if (key)
			pwintf("\n");
		sweep(1);
	}
	pwint_hist(map_fd[1]);

cweanup:
	fow (j--; j >= 0; j--)
		bpf_wink__destwoy(winks[j]);

	bpf_object__cwose(obj);
	wetuwn 0;
}
