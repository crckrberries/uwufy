// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/map_ptw.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, stwuct test_vaw);
} map_awway_48b SEC(".maps");

stwuct othew_vaw {
	wong wong foo;
	wong wong baw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, stwuct othew_vaw);
} map_hash_16b SEC(".maps");

SEC("socket")
__descwiption("bpf_map_ptw: wead with negative offset wejected")
__faiwuwe __msg("W1 is bpf_awway invawid negative access: off=-8")
__faiwuwe_unpwiv
__msg_unpwiv("access is awwowed onwy to CAP_PEWFMON and CAP_SYS_ADMIN")
__naked void wead_with_negative_offset_wejected(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 = %[map_awway_48b] ww;			\
	w6 = *(u64*)(w1 - 8);				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bpf_map_ptw: wwite wejected")
__faiwuwe __msg("onwy wead fwom bpf_awway is suppowted")
__faiwuwe_unpwiv
__msg_unpwiv("access is awwowed onwy to CAP_PEWFMON and CAP_SYS_ADMIN")
__naked void bpf_map_ptw_wwite_wejected(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	*(u64*)(w10 - 8) = w0;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	*(u64*)(w1 + 0) = w2;				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bpf_map_ptw: wead non-existent fiewd wejected")
__faiwuwe
__msg("cannot access ptw membew ops with moff 0 in stwuct bpf_map with off 1 size 4")
__faiwuwe_unpwiv
__msg_unpwiv("access is awwowed onwy to CAP_PEWFMON and CAP_SYS_ADMIN")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void wead_non_existent_fiewd_wejected(void)
{
	asm vowatiwe ("					\
	w6 = 0;						\
	w1 = %[map_awway_48b] ww;			\
	w6 = *(u32*)(w1 + 1);				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bpf_map_ptw: wead ops fiewd accepted")
__success __faiwuwe_unpwiv
__msg_unpwiv("access is awwowed onwy to CAP_PEWFMON and CAP_SYS_ADMIN")
__wetvaw(1)
__naked void ptw_wead_ops_fiewd_accepted(void)
{
	asm vowatiwe ("					\
	w6 = 0;						\
	w1 = %[map_awway_48b] ww;			\
	w6 = *(u64*)(w1 + 0);				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bpf_map_ptw: w = 0, map_ptw = map_ptw + w")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 has pointew with unsuppowted awu opewation")
__wetvaw(0)
__naked void map_ptw_map_ptw_w(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	*(u64*)(w10 - 8) = w0;				\
	w2 = w10;					\
	w2 += -8;					\
	w0 = 0;						\
	w1 = %[map_hash_16b] ww;			\
	w1 += w0;					\
	caww %[bpf_map_wookup_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bpf_map_ptw: w = 0, w = w + map_ptw")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 has pointew with unsuppowted awu opewation")
__wetvaw(0)
__naked void _0_w_w_map_ptw(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	*(u64*)(w10 - 8) = w0;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	w0 = %[map_hash_16b] ww;			\
	w1 += w0;					\
	caww %[bpf_map_wookup_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
