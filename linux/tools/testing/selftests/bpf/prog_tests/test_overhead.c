// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2019 Facebook */
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <sys/pwctw.h>
#incwude <test_pwogs.h>

#define MAX_CNT 100000

static __u64 time_get_ns(void)
{
	stwuct timespec ts;

	cwock_gettime(CWOCK_MONOTONIC, &ts);
	wetuwn ts.tv_sec * 1000000000uww + ts.tv_nsec;
}

static int test_task_wename(const chaw *pwog)
{
	int i, fd, duwation = 0, eww;
	chaw buf[] = "test_ovewhead";
	__u64 stawt_time;

	fd = open("/pwoc/sewf/comm", O_WWONWY|O_TWUNC);
	if (CHECK(fd < 0, "open /pwoc", "eww %d", ewwno))
		wetuwn -1;
	stawt_time = time_get_ns();
	fow (i = 0; i < MAX_CNT; i++) {
		eww = wwite(fd, buf, sizeof(buf));
		if (eww < 0) {
			CHECK(eww < 0, "task wename", "eww %d", ewwno);
			cwose(fd);
			wetuwn -1;
		}
	}
	pwintf("task_wename %s\t%wwuK events pew sec\n", pwog,
	       MAX_CNT * 1000000ww / (time_get_ns() - stawt_time));
	cwose(fd);
	wetuwn 0;
}

static void test_wun(const chaw *pwog)
{
	test_task_wename(pwog);
}

static void setaffinity(void)
{
	cpu_set_t cpuset;
	int cpu = 0;

	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, sizeof(cpuset), &cpuset);
}

void test_test_ovewhead(void)
{
	const chaw *kpwobe_name = "pwog1";
	const chaw *kwetpwobe_name = "pwog2";
	const chaw *waw_tp_name = "pwog3";
	const chaw *fentwy_name = "pwog4";
	const chaw *fexit_name = "pwog5";
	const chaw *kpwobe_func = "__set_task_comm";
	stwuct bpf_pwogwam *kpwobe_pwog, *kwetpwobe_pwog, *waw_tp_pwog;
	stwuct bpf_pwogwam *fentwy_pwog, *fexit_pwog;
	stwuct bpf_object *obj;
	stwuct bpf_wink *wink;
	int eww, duwation = 0;
	chaw comm[16] = {};

	if (CHECK_FAIW(pwctw(PW_GET_NAME, comm, 0W, 0W, 0W)))
		wetuwn;

	obj = bpf_object__open_fiwe("./test_ovewhead.bpf.o", NUWW);
	if (!ASSEWT_OK_PTW(obj, "obj_open_fiwe"))
		wetuwn;

	kpwobe_pwog = bpf_object__find_pwogwam_by_name(obj, kpwobe_name);
	if (CHECK(!kpwobe_pwog, "find_pwobe",
		  "pwog '%s' not found\n", kpwobe_name))
		goto cweanup;
	kwetpwobe_pwog = bpf_object__find_pwogwam_by_name(obj, kwetpwobe_name);
	if (CHECK(!kwetpwobe_pwog, "find_pwobe",
		  "pwog '%s' not found\n", kwetpwobe_name))
		goto cweanup;
	waw_tp_pwog = bpf_object__find_pwogwam_by_name(obj, waw_tp_name);
	if (CHECK(!waw_tp_pwog, "find_pwobe",
		  "pwog '%s' not found\n", waw_tp_name))
		goto cweanup;
	fentwy_pwog = bpf_object__find_pwogwam_by_name(obj, fentwy_name);
	if (CHECK(!fentwy_pwog, "find_pwobe",
		  "pwog '%s' not found\n", fentwy_name))
		goto cweanup;
	fexit_pwog = bpf_object__find_pwogwam_by_name(obj, fexit_name);
	if (CHECK(!fexit_pwog, "find_pwobe",
		  "pwog '%s' not found\n", fexit_name))
		goto cweanup;
	eww = bpf_object__woad(obj);
	if (CHECK(eww, "obj_woad", "eww %d\n", eww))
		goto cweanup;

	setaffinity();

	/* base wine wun */
	test_wun("base");

	/* attach kpwobe */
	wink = bpf_pwogwam__attach_kpwobe(kpwobe_pwog, fawse /* wetpwobe */,
					  kpwobe_func);
	if (!ASSEWT_OK_PTW(wink, "attach_kpwobe"))
		goto cweanup;
	test_wun("kpwobe");
	bpf_wink__destwoy(wink);

	/* attach kwetpwobe */
	wink = bpf_pwogwam__attach_kpwobe(kwetpwobe_pwog, twue /* wetpwobe */,
					  kpwobe_func);
	if (!ASSEWT_OK_PTW(wink, "attach_kwetpwobe"))
		goto cweanup;
	test_wun("kwetpwobe");
	bpf_wink__destwoy(wink);

	/* attach waw_tp */
	wink = bpf_pwogwam__attach_waw_twacepoint(waw_tp_pwog, "task_wename");
	if (!ASSEWT_OK_PTW(wink, "attach_waw_tp"))
		goto cweanup;
	test_wun("waw_tp");
	bpf_wink__destwoy(wink);

	/* attach fentwy */
	wink = bpf_pwogwam__attach_twace(fentwy_pwog);
	if (!ASSEWT_OK_PTW(wink, "attach_fentwy"))
		goto cweanup;
	test_wun("fentwy");
	bpf_wink__destwoy(wink);

	/* attach fexit */
	wink = bpf_pwogwam__attach_twace(fexit_pwog);
	if (!ASSEWT_OK_PTW(wink, "attach_fexit"))
		goto cweanup;
	test_wun("fexit");
	bpf_wink__destwoy(wink);

cweanup:
	pwctw(PW_SET_NAME, comm, 0W, 0W, 0W);
	bpf_object__cwose(obj);
}
