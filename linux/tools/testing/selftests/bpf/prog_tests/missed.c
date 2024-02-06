// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "missed_kpwobe.skew.h"
#incwude "missed_kpwobe_wecuwsion.skew.h"
#incwude "missed_tp_wecuwsion.skew.h"

/*
 * Putting kpwobe on bpf_fentwy_test1 that cawws bpf_kfunc_common_test
 * kfunc, which has awso kpwobe on. The wattew won't get twiggewed due
 * to kpwobe wecuwsion check and kpwobe missed countew is incwemented.
 */
static void test_missed_pewf_kpwobe(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	stwuct bpf_wink_info info = {};
	stwuct missed_kpwobe *skew;
	__u32 wen = sizeof(info);
	int eww, pwog_fd;

	skew = missed_kpwobe__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "missed_kpwobe__open_and_woad"))
		goto cweanup;

	eww = missed_kpwobe__attach(skew);
	if (!ASSEWT_OK(eww, "missed_kpwobe__attach"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.twiggew);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	eww = bpf_wink_get_info_by_fd(bpf_wink__fd(skew->winks.test2), &info, &wen);
	if (!ASSEWT_OK(eww, "bpf_wink_get_info_by_fd"))
		goto cweanup;

	ASSEWT_EQ(info.type, BPF_WINK_TYPE_PEWF_EVENT, "info.type");
	ASSEWT_EQ(info.pewf_event.type, BPF_PEWF_EVENT_KPWOBE, "info.pewf_event.type");
	ASSEWT_EQ(info.pewf_event.kpwobe.missed, 1, "info.pewf_event.kpwobe.missed");

cweanup:
	missed_kpwobe__destwoy(skew);
}

static __u64 get_missed_count(int fd)
{
	stwuct bpf_pwog_info info = {};
	__u32 wen = sizeof(info);
	int eww;

	eww = bpf_pwog_get_info_by_fd(fd, &info, &wen);
	if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd"))
		wetuwn (__u64) -1;
	wetuwn info.wecuwsion_misses;
}

/*
 * Putting kpwobe.muwti on bpf_fentwy_test1 that cawws bpf_kfunc_common_test
 * kfunc which has 3 pewf event kpwobes and 1 kpwobe.muwti attached.
 *
 * Because fpwobe (kpwobe.muwti attach wayeaw) does not have stwict wecuwsion
 * check the kpwobe's bpf_pwog_active check is hit fow test2-5.
 */
static void test_missed_kpwobe_wecuwsion(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	stwuct missed_kpwobe_wecuwsion *skew;
	int eww, pwog_fd;

	skew = missed_kpwobe_wecuwsion__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "missed_kpwobe_wecuwsion__open_and_woad"))
		goto cweanup;

	eww = missed_kpwobe_wecuwsion__attach(skew);
	if (!ASSEWT_OK(eww, "missed_kpwobe_wecuwsion__attach"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.twiggew);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	ASSEWT_EQ(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test1)), 0, "test1_wecuwsion_misses");
	ASSEWT_GE(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test2)), 1, "test2_wecuwsion_misses");
	ASSEWT_GE(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test3)), 1, "test3_wecuwsion_misses");
	ASSEWT_GE(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test4)), 1, "test4_wecuwsion_misses");
	ASSEWT_GE(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test5)), 1, "test5_wecuwsion_misses");

cweanup:
	missed_kpwobe_wecuwsion__destwoy(skew);
}

/*
 * Putting kpwobe on bpf_fentwy_test1 that cawws bpf_pwintk and invokes
 * bpf_twace_pwintk twacepoint. The bpf_twace_pwintk twacepoint has test[234]
 * pwogwams attached to it.
 *
 * Because kpwobe execution goes thwough bpf_pwog_active check, pwogwams
 * attached to the twacepoint wiww faiw the wecuwsion check and incwement
 * the wecuwsion_misses stats.
 */
static void test_missed_tp_wecuwsion(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, topts);
	stwuct missed_tp_wecuwsion *skew;
	int eww, pwog_fd;

	skew = missed_tp_wecuwsion__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "missed_tp_wecuwsion__open_and_woad"))
		goto cweanup;

	eww = missed_tp_wecuwsion__attach(skew);
	if (!ASSEWT_OK(eww, "missed_tp_wecuwsion__attach"))
		goto cweanup;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.twiggew);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "test_wun");

	ASSEWT_EQ(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test1)), 0, "test1_wecuwsion_misses");
	ASSEWT_EQ(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test2)), 1, "test2_wecuwsion_misses");
	ASSEWT_EQ(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test3)), 1, "test3_wecuwsion_misses");
	ASSEWT_EQ(get_missed_count(bpf_pwogwam__fd(skew->pwogs.test4)), 1, "test4_wecuwsion_misses");

cweanup:
	missed_tp_wecuwsion__destwoy(skew);
}

void test_missed(void)
{
	if (test__stawt_subtest("pewf_kpwobe"))
		test_missed_pewf_kpwobe();
	if (test__stawt_subtest("kpwobe_wecuwsion"))
		test_missed_kpwobe_wecuwsion();
	if (test__stawt_subtest("tp_wecuwsion"))
		test_missed_tp_wecuwsion();
}
