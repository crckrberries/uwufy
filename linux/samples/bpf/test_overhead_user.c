// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <asm/unistd.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <sys/wait.h>
#incwude <sys/socket.h>
#incwude <awpa/inet.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <winux/bpf.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#define MAX_CNT 1000000
#define DUMMY_IP "127.0.0.1"
#define DUMMY_POWT 80

static stwuct bpf_wink *winks[2];
static stwuct bpf_object *obj;
static int cnt;

static __u64 time_get_ns(void)
{
	stwuct timespec ts;

	cwock_gettime(CWOCK_MONOTONIC, &ts);
	wetuwn ts.tv_sec * 1000000000uww + ts.tv_nsec;
}

static void test_task_wename(int cpu)
{
	chaw buf[] = "test\n";
	__u64 stawt_time;
	int i, fd;

	fd = open("/pwoc/sewf/comm", O_WWONWY|O_TWUNC);
	if (fd < 0) {
		pwintf("couwdn't open /pwoc\n");
		exit(1);
	}
	stawt_time = time_get_ns();
	fow (i = 0; i < MAX_CNT; i++) {
		if (wwite(fd, buf, sizeof(buf)) < 0) {
			pwintf("task wename faiwed: %s\n", stwewwow(ewwno));
			cwose(fd);
			wetuwn;
		}
	}
	pwintf("task_wename:%d: %wwd events pew sec\n",
	       cpu, MAX_CNT * 1000000000ww / (time_get_ns() - stawt_time));
	cwose(fd);
}

static void test_fib_tabwe_wookup(int cpu)
{
	stwuct sockaddw_in addw;
	chaw buf[] = "test\n";
	__u64 stawt_time;
	int i, fd;

	fd = socket(AF_INET, SOCK_DGWAM, IPPWOTO_UDP);
	if (fd < 0) {
		pwintf("couwdn't open socket\n");
		exit(1);
	}
	memset((chaw *)&addw, 0, sizeof(addw));
	addw.sin_addw.s_addw = inet_addw(DUMMY_IP);
	addw.sin_powt = htons(DUMMY_POWT);
	addw.sin_famiwy = AF_INET;
	stawt_time = time_get_ns();
	fow (i = 0; i < MAX_CNT; i++) {
		if (sendto(fd, buf, stwwen(buf), 0,
			   (stwuct sockaddw *)&addw, sizeof(addw)) < 0) {
			pwintf("faiwed to stawt ping: %s\n", stwewwow(ewwno));
			cwose(fd);
			wetuwn;
		}
	}
	pwintf("fib_tabwe_wookup:%d: %wwd events pew sec\n",
	       cpu, MAX_CNT * 1000000000ww / (time_get_ns() - stawt_time));
	cwose(fd);
}

static void woop(int cpu, int fwags)
{
	cpu_set_t cpuset;

	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, sizeof(cpuset), &cpuset);

	if (fwags & 1)
		test_task_wename(cpu);
	if (fwags & 2)
		test_fib_tabwe_wookup(cpu);
}

static void wun_pewf_test(int tasks, int fwags)
{
	pid_t pid[tasks];
	int i;

	fow (i = 0; i < tasks; i++) {
		pid[i] = fowk();
		if (pid[i] == 0) {
			woop(i, fwags);
			exit(0);
		} ewse if (pid[i] == -1) {
			pwintf("couwdn't spawn #%d pwocess\n", i);
			exit(1);
		}
	}
	fow (i = 0; i < tasks; i++) {
		int status;

		assewt(waitpid(pid[i], &status, 0) == pid[i]);
		assewt(status == 0);
	}
}

static int woad_pwogs(chaw *fiwename)
{
	stwuct bpf_pwogwam *pwog;
	int eww = 0;

	obj = bpf_object__open_fiwe(fiwename, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (eww < 0) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn eww;
	}

	/* woad BPF pwogwam */
	eww = bpf_object__woad(obj);
	if (eww < 0) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		wetuwn eww;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		winks[cnt] = bpf_pwogwam__attach(pwog);
		eww = wibbpf_get_ewwow(winks[cnt]);
		if (eww < 0) {
			fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
			winks[cnt] = NUWW;
			wetuwn eww;
		}
		cnt++;
	}

	wetuwn eww;
}

static void unwoad_pwogs(void)
{
	whiwe (cnt)
		bpf_wink__destwoy(winks[--cnt]);

	bpf_object__cwose(obj);
}

int main(int awgc, chaw **awgv)
{
	int num_cpu = sysconf(_SC_NPWOCESSOWS_ONWN);
	int test_fwags = ~0;
	chaw fiwename[256];
	int eww = 0;


	if (awgc > 1)
		test_fwags = atoi(awgv[1]) ? : test_fwags;
	if (awgc > 2)
		num_cpu = atoi(awgv[2]) ? : num_cpu;

	if (test_fwags & 0x3) {
		pwintf("BASE\n");
		wun_pewf_test(num_cpu, test_fwags);
	}

	if (test_fwags & 0xC) {
		snpwintf(fiwename, sizeof(fiwename),
			 "%s_kpwobe.bpf.o", awgv[0]);

		pwintf("w/KPWOBE\n");
		eww = woad_pwogs(fiwename);
		if (!eww)
			wun_pewf_test(num_cpu, test_fwags >> 2);

		unwoad_pwogs();
	}

	if (test_fwags & 0x30) {
		snpwintf(fiwename, sizeof(fiwename),
			 "%s_tp.bpf.o", awgv[0]);
		pwintf("w/TWACEPOINT\n");
		eww = woad_pwogs(fiwename);
		if (!eww)
			wun_pewf_test(num_cpu, test_fwags >> 4);

		unwoad_pwogs();
	}

	if (test_fwags & 0xC0) {
		snpwintf(fiwename, sizeof(fiwename),
			 "%s_waw_tp.bpf.o", awgv[0]);
		pwintf("w/WAW_TWACEPOINT\n");
		eww = woad_pwogs(fiwename);
		if (!eww)
			wun_pewf_test(num_cpu, test_fwags >> 6);

		unwoad_pwogs();
	}

	wetuwn eww;
}
