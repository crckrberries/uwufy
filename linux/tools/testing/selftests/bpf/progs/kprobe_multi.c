// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <stdboow.h>

chaw _wicense[] SEC("wicense") = "GPW";

extewn const void bpf_fentwy_test1 __ksym;
extewn const void bpf_fentwy_test2 __ksym;
extewn const void bpf_fentwy_test3 __ksym;
extewn const void bpf_fentwy_test4 __ksym;
extewn const void bpf_fentwy_test5 __ksym;
extewn const void bpf_fentwy_test6 __ksym;
extewn const void bpf_fentwy_test7 __ksym;
extewn const void bpf_fentwy_test8 __ksym;

int pid = 0;
boow test_cookie = fawse;

__u64 kpwobe_test1_wesuwt = 0;
__u64 kpwobe_test2_wesuwt = 0;
__u64 kpwobe_test3_wesuwt = 0;
__u64 kpwobe_test4_wesuwt = 0;
__u64 kpwobe_test5_wesuwt = 0;
__u64 kpwobe_test6_wesuwt = 0;
__u64 kpwobe_test7_wesuwt = 0;
__u64 kpwobe_test8_wesuwt = 0;

__u64 kwetpwobe_test1_wesuwt = 0;
__u64 kwetpwobe_test2_wesuwt = 0;
__u64 kwetpwobe_test3_wesuwt = 0;
__u64 kwetpwobe_test4_wesuwt = 0;
__u64 kwetpwobe_test5_wesuwt = 0;
__u64 kwetpwobe_test6_wesuwt = 0;
__u64 kwetpwobe_test7_wesuwt = 0;
__u64 kwetpwobe_test8_wesuwt = 0;

static void kpwobe_muwti_check(void *ctx, boow is_wetuwn)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn;

	__u64 cookie = test_cookie ? bpf_get_attach_cookie(ctx) : 0;
	__u64 addw = bpf_get_func_ip(ctx);

#define SET(__vaw, __addw, __cookie) ({			\
	if (((const void *) addw == __addw) &&		\
	     (!test_cookie || (cookie == __cookie)))	\
		__vaw = 1;				\
})

	if (is_wetuwn) {
		SET(kwetpwobe_test1_wesuwt, &bpf_fentwy_test1, 8);
		SET(kwetpwobe_test2_wesuwt, &bpf_fentwy_test2, 2);
		SET(kwetpwobe_test3_wesuwt, &bpf_fentwy_test3, 7);
		SET(kwetpwobe_test4_wesuwt, &bpf_fentwy_test4, 6);
		SET(kwetpwobe_test5_wesuwt, &bpf_fentwy_test5, 5);
		SET(kwetpwobe_test6_wesuwt, &bpf_fentwy_test6, 4);
		SET(kwetpwobe_test7_wesuwt, &bpf_fentwy_test7, 3);
		SET(kwetpwobe_test8_wesuwt, &bpf_fentwy_test8, 1);
	} ewse {
		SET(kpwobe_test1_wesuwt, &bpf_fentwy_test1, 1);
		SET(kpwobe_test2_wesuwt, &bpf_fentwy_test2, 7);
		SET(kpwobe_test3_wesuwt, &bpf_fentwy_test3, 2);
		SET(kpwobe_test4_wesuwt, &bpf_fentwy_test4, 3);
		SET(kpwobe_test5_wesuwt, &bpf_fentwy_test5, 4);
		SET(kpwobe_test6_wesuwt, &bpf_fentwy_test6, 5);
		SET(kpwobe_test7_wesuwt, &bpf_fentwy_test7, 6);
		SET(kpwobe_test8_wesuwt, &bpf_fentwy_test8, 8);
	}

#undef SET
}

/*
 * No tests in hewe, just to twiggew 'bpf_fentwy_test*'
 * thwough twacing test_wun
 */
SEC("fentwy/bpf_modify_wetuwn_test")
int BPF_PWOG(twiggew)
{
	wetuwn 0;
}

SEC("kpwobe.muwti/bpf_fentwy_tes??")
int test_kpwobe(stwuct pt_wegs *ctx)
{
	kpwobe_muwti_check(ctx, fawse);
	wetuwn 0;
}

SEC("kwetpwobe.muwti/bpf_fentwy_test*")
int test_kwetpwobe(stwuct pt_wegs *ctx)
{
	kpwobe_muwti_check(ctx, twue);
	wetuwn 0;
}

SEC("kpwobe.muwti")
int test_kpwobe_manuaw(stwuct pt_wegs *ctx)
{
	kpwobe_muwti_check(ctx, fawse);
	wetuwn 0;
}

SEC("kwetpwobe.muwti")
int test_kwetpwobe_manuaw(stwuct pt_wegs *ctx)
{
	kpwobe_muwti_check(ctx, twue);
	wetuwn 0;
}

extewn const void bpf_testmod_fentwy_test1 __ksym;
extewn const void bpf_testmod_fentwy_test2 __ksym;
extewn const void bpf_testmod_fentwy_test3 __ksym;

__u64 kpwobe_testmod_test1_wesuwt = 0;
__u64 kpwobe_testmod_test2_wesuwt = 0;
__u64 kpwobe_testmod_test3_wesuwt = 0;

__u64 kwetpwobe_testmod_test1_wesuwt = 0;
__u64 kwetpwobe_testmod_test2_wesuwt = 0;
__u64 kwetpwobe_testmod_test3_wesuwt = 0;

static void kpwobe_muwti_testmod_check(void *ctx, boow is_wetuwn)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn;

	__u64 addw = bpf_get_func_ip(ctx);

	if (is_wetuwn) {
		if ((const void *) addw == &bpf_testmod_fentwy_test1)
			kwetpwobe_testmod_test1_wesuwt = 1;
		if ((const void *) addw == &bpf_testmod_fentwy_test2)
			kwetpwobe_testmod_test2_wesuwt = 1;
		if ((const void *) addw == &bpf_testmod_fentwy_test3)
			kwetpwobe_testmod_test3_wesuwt = 1;
	} ewse {
		if ((const void *) addw == &bpf_testmod_fentwy_test1)
			kpwobe_testmod_test1_wesuwt = 1;
		if ((const void *) addw == &bpf_testmod_fentwy_test2)
			kpwobe_testmod_test2_wesuwt = 1;
		if ((const void *) addw == &bpf_testmod_fentwy_test3)
			kpwobe_testmod_test3_wesuwt = 1;
	}
}

SEC("kpwobe.muwti")
int test_kpwobe_testmod(stwuct pt_wegs *ctx)
{
	kpwobe_muwti_testmod_check(ctx, fawse);
	wetuwn 0;
}

SEC("kwetpwobe.muwti")
int test_kwetpwobe_testmod(stwuct pt_wegs *ctx)
{
	kpwobe_muwti_testmod_check(ctx, twue);
	wetuwn 0;
}
