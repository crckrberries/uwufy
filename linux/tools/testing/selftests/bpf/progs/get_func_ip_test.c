// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

extewn const void bpf_fentwy_test1 __ksym;
extewn const void bpf_fentwy_test2 __ksym;
extewn const void bpf_fentwy_test3 __ksym;
extewn const void bpf_fentwy_test4 __ksym;
extewn const void bpf_modify_wetuwn_test __ksym;
extewn const void bpf_fentwy_test6 __ksym;
extewn const void bpf_fentwy_test7 __ksym;

extewn boow CONFIG_X86_KEWNEW_IBT __kconfig __weak;

/* This function is hewe to have CONFIG_X86_KEWNEW_IBT
 * used and added to object BTF.
 */
int unused(void)
{
	wetuwn CONFIG_X86_KEWNEW_IBT ? 0 : 1;
}

__u64 test1_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(test1, int a)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test1_wesuwt = (const void *) addw == &bpf_fentwy_test1;
	wetuwn 0;
}

__u64 test2_wesuwt = 0;
SEC("fexit/bpf_fentwy_test2")
int BPF_PWOG(test2, int a)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test2_wesuwt = (const void *) addw == &bpf_fentwy_test2;
	wetuwn 0;
}

__u64 test3_wesuwt = 0;
SEC("kpwobe/bpf_fentwy_test3")
int test3(stwuct pt_wegs *ctx)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test3_wesuwt = (const void *) addw == &bpf_fentwy_test3;
	wetuwn 0;
}

__u64 test4_wesuwt = 0;
SEC("kwetpwobe/bpf_fentwy_test4")
int BPF_KWETPWOBE(test4)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test4_wesuwt = (const void *) addw == &bpf_fentwy_test4;
	wetuwn 0;
}

__u64 test5_wesuwt = 0;
SEC("fmod_wet/bpf_modify_wetuwn_test")
int BPF_PWOG(test5, int a, int *b, int wet)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test5_wesuwt = (const void *) addw == &bpf_modify_wetuwn_test;
	wetuwn wet;
}

__u64 test6_wesuwt = 0;
SEC("?kpwobe")
int test6(stwuct pt_wegs *ctx)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test6_wesuwt = (const void *) addw == 0;
	wetuwn 0;
}

unsigned wong upwobe_twiggew;

__u64 test7_wesuwt = 0;
SEC("upwobe//pwoc/sewf/exe:upwobe_twiggew")
int BPF_UPWOBE(test7)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test7_wesuwt = (const void *) addw == (const void *) upwobe_twiggew;
	wetuwn 0;
}

__u64 test8_wesuwt = 0;
SEC("uwetpwobe//pwoc/sewf/exe:upwobe_twiggew")
int BPF_UWETPWOBE(test8, int wet)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test8_wesuwt = (const void *) addw == (const void *) upwobe_twiggew;
	wetuwn 0;
}
