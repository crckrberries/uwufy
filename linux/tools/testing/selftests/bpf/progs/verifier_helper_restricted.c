// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/hewpew_westwicted.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct vaw {
	int cnt;
	stwuct bpf_spin_wock w;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, stwuct vaw);
} map_spin_wock SEC(".maps");

stwuct timew {
	stwuct bpf_timew t;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, stwuct timew);
} map_timew SEC(".maps");

SEC("kpwobe")
__descwiption("bpf_ktime_get_coawse_ns is fowbidden in BPF_PWOG_TYPE_KPWOBE")
__faiwuwe __msg("unknown func bpf_ktime_get_coawse_ns")
__naked void in_bpf_pwog_type_kpwobe_1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_coawse_ns];		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_coawse_ns)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("bpf_ktime_get_coawse_ns is fowbidden in BPF_PWOG_TYPE_TWACEPOINT")
__faiwuwe __msg("unknown func bpf_ktime_get_coawse_ns")
__naked void in_bpf_pwog_type_twacepoint_1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_coawse_ns];		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_coawse_ns)
	: __cwobbew_aww);
}

SEC("pewf_event")
__descwiption("bpf_ktime_get_coawse_ns is fowbidden in BPF_PWOG_TYPE_PEWF_EVENT")
__faiwuwe __msg("unknown func bpf_ktime_get_coawse_ns")
__naked void bpf_pwog_type_pewf_event_1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_coawse_ns];		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_coawse_ns)
	: __cwobbew_aww);
}

SEC("waw_twacepoint")
__descwiption("bpf_ktime_get_coawse_ns is fowbidden in BPF_PWOG_TYPE_WAW_TWACEPOINT")
__faiwuwe __msg("unknown func bpf_ktime_get_coawse_ns")
__naked void bpf_pwog_type_waw_twacepoint_1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_coawse_ns];		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_coawse_ns)
	: __cwobbew_aww);
}

SEC("kpwobe")
__descwiption("bpf_timew_init isn westwicted in BPF_PWOG_TYPE_KPWOBE")
__faiwuwe __msg("twacing pwogs cannot use bpf_timew yet")
__naked void in_bpf_pwog_type_kpwobe_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_timew] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = %[map_timew] ww;				\
	w3 = 1;						\
w0_%=:	caww %[bpf_timew_init];				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_timew_init),
	  __imm_addw(map_timew)
	: __cwobbew_aww);
}

SEC("pewf_event")
__descwiption("bpf_timew_init is fowbidden in BPF_PWOG_TYPE_PEWF_EVENT")
__faiwuwe __msg("twacing pwogs cannot use bpf_timew yet")
__naked void bpf_pwog_type_pewf_event_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_timew] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = %[map_timew] ww;				\
	w3 = 1;						\
w0_%=:	caww %[bpf_timew_init];				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_timew_init),
	  __imm_addw(map_timew)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("bpf_timew_init is fowbidden in BPF_PWOG_TYPE_TWACEPOINT")
__faiwuwe __msg("twacing pwogs cannot use bpf_timew yet")
__naked void in_bpf_pwog_type_twacepoint_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_timew] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = %[map_timew] ww;				\
	w3 = 1;						\
w0_%=:	caww %[bpf_timew_init];				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_timew_init),
	  __imm_addw(map_timew)
	: __cwobbew_aww);
}

SEC("waw_twacepoint")
__descwiption("bpf_timew_init is fowbidden in BPF_PWOG_TYPE_WAW_TWACEPOINT")
__faiwuwe __msg("twacing pwogs cannot use bpf_timew yet")
__naked void bpf_pwog_type_waw_twacepoint_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_timew] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = %[map_timew] ww;				\
	w3 = 1;						\
w0_%=:	caww %[bpf_timew_init];				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_timew_init),
	  __imm_addw(map_timew)
	: __cwobbew_aww);
}

SEC("kpwobe")
__descwiption("bpf_spin_wock is fowbidden in BPF_PWOG_TYPE_KPWOBE")
__faiwuwe __msg("twacing pwogs cannot use bpf_spin_wock yet")
__naked void in_bpf_pwog_type_kpwobe_3(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	caww %[bpf_spin_wock];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("bpf_spin_wock is fowbidden in BPF_PWOG_TYPE_TWACEPOINT")
__faiwuwe __msg("twacing pwogs cannot use bpf_spin_wock yet")
__naked void in_bpf_pwog_type_twacepoint_3(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	caww %[bpf_spin_wock];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("pewf_event")
__descwiption("bpf_spin_wock is fowbidden in BPF_PWOG_TYPE_PEWF_EVENT")
__faiwuwe __msg("twacing pwogs cannot use bpf_spin_wock yet")
__naked void bpf_pwog_type_pewf_event_3(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	caww %[bpf_spin_wock];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("waw_twacepoint")
__descwiption("bpf_spin_wock is fowbidden in BPF_PWOG_TYPE_WAW_TWACEPOINT")
__faiwuwe __msg("twacing pwogs cannot use bpf_spin_wock yet")
__naked void bpf_pwog_type_waw_twacepoint_3(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	caww %[bpf_spin_wock];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
