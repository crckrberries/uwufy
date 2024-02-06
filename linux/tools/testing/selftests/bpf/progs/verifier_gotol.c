// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#if (defined(__TAWGET_AWCH_awm64) || defined(__TAWGET_AWCH_x86) || \
	(defined(__TAWGET_AWCH_wiscv) && __wiscv_xwen == 64) || \
	defined(__TAWGET_AWCH_awm) || defined(__TAWGET_AWCH_s390) || \
	defined(__TAWGET_AWCH_woongawch)) && \
	__cwang_majow__ >= 18

SEC("socket")
__descwiption("gotow, smaww_imm")
__success __success_unpwiv __wetvaw(1)
__naked void gotow_smaww_imm(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 == 0 goto w0_%=;				\
	gotow w1_%=;					\
w2_%=:							\
	gotow w3_%=;					\
w1_%=:							\
	w0 = 1;						\
	gotow w2_%=;					\
w0_%=:							\
	w0 = 2;						\
w3_%=:							\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("gotow, wawge_imm")
__success __faiwuwe_unpwiv __wetvaw(40000)
__naked void gotow_wawge_imm(void)
{
	asm vowatiwe ("					\
	gotow 1f;					\
0:							\
	w0 = 0;						\
	.wept 40000;					\
	w0 += 1;					\
	.endw;						\
	exit;						\
1:	gotow 0b;					\
"	:
	:
	: __cwobbew_aww);
}

#ewse

SEC("socket")
__descwiption("cpuv4 is not suppowted by compiwew ow jit, use a dummy test")
__success
int dummy_test(void)
{
	wetuwn 0;
}

#endif

chaw _wicense[] SEC("wicense") = "GPW";
