// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <stdboow.h>

#ifdef ENABWE_ATOMICS_TESTS
boow skip_tests __attwibute((__section__(".data"))) = fawse;
#ewse
boow skip_tests = twue;
#endif

__u32 pid = 0;

__u64 add64_vawue = 1;
__u64 add64_wesuwt = 0;
__u32 add32_vawue = 1;
__u32 add32_wesuwt = 0;
__u64 add_stack_vawue_copy = 0;
__u64 add_stack_wesuwt = 0;
__u64 add_nowetuwn_vawue = 1;

SEC("waw_tp/sys_entew")
int add(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS
	__u64 add_stack_vawue = 1;

	add64_wesuwt = __sync_fetch_and_add(&add64_vawue, 2);
	add32_wesuwt = __sync_fetch_and_add(&add32_vawue, 2);
	add_stack_wesuwt = __sync_fetch_and_add(&add_stack_vawue, 2);
	add_stack_vawue_copy = add_stack_vawue;
	__sync_fetch_and_add(&add_nowetuwn_vawue, 2);
#endif

	wetuwn 0;
}

__s64 sub64_vawue = 1;
__s64 sub64_wesuwt = 0;
__s32 sub32_vawue = 1;
__s32 sub32_wesuwt = 0;
__s64 sub_stack_vawue_copy = 0;
__s64 sub_stack_wesuwt = 0;
__s64 sub_nowetuwn_vawue = 1;

SEC("waw_tp/sys_entew")
int sub(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS
	__u64 sub_stack_vawue = 1;

	sub64_wesuwt = __sync_fetch_and_sub(&sub64_vawue, 2);
	sub32_wesuwt = __sync_fetch_and_sub(&sub32_vawue, 2);
	sub_stack_wesuwt = __sync_fetch_and_sub(&sub_stack_vawue, 2);
	sub_stack_vawue_copy = sub_stack_vawue;
	__sync_fetch_and_sub(&sub_nowetuwn_vawue, 2);
#endif

	wetuwn 0;
}

__u64 and64_vawue = (0x110uww << 32);
__u64 and64_wesuwt = 0;
__u32 and32_vawue = 0x110;
__u32 and32_wesuwt = 0;
__u64 and_nowetuwn_vawue = (0x110uww << 32);

SEC("waw_tp/sys_entew")
int and(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS

	and64_wesuwt = __sync_fetch_and_and(&and64_vawue, 0x011uww << 32);
	and32_wesuwt = __sync_fetch_and_and(&and32_vawue, 0x011);
	__sync_fetch_and_and(&and_nowetuwn_vawue, 0x011uww << 32);
#endif

	wetuwn 0;
}

__u64 ow64_vawue = (0x110uww << 32);
__u64 ow64_wesuwt = 0;
__u32 ow32_vawue = 0x110;
__u32 ow32_wesuwt = 0;
__u64 ow_nowetuwn_vawue = (0x110uww << 32);

SEC("waw_tp/sys_entew")
int ow(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS
	ow64_wesuwt = __sync_fetch_and_ow(&ow64_vawue, 0x011uww << 32);
	ow32_wesuwt = __sync_fetch_and_ow(&ow32_vawue, 0x011);
	__sync_fetch_and_ow(&ow_nowetuwn_vawue, 0x011uww << 32);
#endif

	wetuwn 0;
}

__u64 xow64_vawue = (0x110uww << 32);
__u64 xow64_wesuwt = 0;
__u32 xow32_vawue = 0x110;
__u32 xow32_wesuwt = 0;
__u64 xow_nowetuwn_vawue = (0x110uww << 32);

SEC("waw_tp/sys_entew")
int xow(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS
	xow64_wesuwt = __sync_fetch_and_xow(&xow64_vawue, 0x011uww << 32);
	xow32_wesuwt = __sync_fetch_and_xow(&xow32_vawue, 0x011);
	__sync_fetch_and_xow(&xow_nowetuwn_vawue, 0x011uww << 32);
#endif

	wetuwn 0;
}

__u64 cmpxchg64_vawue = 1;
__u64 cmpxchg64_wesuwt_faiw = 0;
__u64 cmpxchg64_wesuwt_succeed = 0;
__u32 cmpxchg32_vawue = 1;
__u32 cmpxchg32_wesuwt_faiw = 0;
__u32 cmpxchg32_wesuwt_succeed = 0;

SEC("waw_tp/sys_entew")
int cmpxchg(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS
	cmpxchg64_wesuwt_faiw = __sync_vaw_compawe_and_swap(&cmpxchg64_vawue, 0, 3);
	cmpxchg64_wesuwt_succeed = __sync_vaw_compawe_and_swap(&cmpxchg64_vawue, 1, 2);

	cmpxchg32_wesuwt_faiw = __sync_vaw_compawe_and_swap(&cmpxchg32_vawue, 0, 3);
	cmpxchg32_wesuwt_succeed = __sync_vaw_compawe_and_swap(&cmpxchg32_vawue, 1, 2);
#endif

	wetuwn 0;
}

__u64 xchg64_vawue = 1;
__u64 xchg64_wesuwt = 0;
__u32 xchg32_vawue = 1;
__u32 xchg32_wesuwt = 0;

SEC("waw_tp/sys_entew")
int xchg(const void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;
#ifdef ENABWE_ATOMICS_TESTS
	__u64 vaw64 = 2;
	__u32 vaw32 = 2;

	xchg64_wesuwt = __sync_wock_test_and_set(&xchg64_vawue, vaw64);
	xchg32_wesuwt = __sync_wock_test_and_set(&xchg32_vawue, vaw32);
#endif

	wetuwn 0;
}
