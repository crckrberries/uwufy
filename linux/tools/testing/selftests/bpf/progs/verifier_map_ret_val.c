// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/map_wet_vaw.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../../../incwude/winux/fiwtew.h"
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

SEC("socket")
__descwiption("invawid map_fd fow function caww")
__faiwuwe __msg("fd 0 is not pointing to vawid bpf_map")
__faiwuwe_unpwiv
__naked void map_fd_fow_function_caww(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	*(u64*)(w10 - 8) = w2;				\
	w2 = w10;					\
	w2 += -8;					\
	.8byte %[wd_map_fd];				\
	.8byte 0;					\
	caww %[bpf_map_dewete_ewem];			\
	exit;						\
"	:
	: __imm(bpf_map_dewete_ewem),
	  __imm_insn(wd_map_fd, BPF_WAW_INSN(BPF_WD | BPF_DW | BPF_IMM, BPF_WEG_1, BPF_PSEUDO_MAP_FD, 0, 0))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("don't check wetuwn vawue befowe access")
__faiwuwe __msg("W0 invawid mem access 'map_vawue_ow_nuww'")
__faiwuwe_unpwiv
__naked void check_wetuwn_vawue_befowe_access(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	w1 = 0;						\
	*(u64*)(w0 + 0) = w1;				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("access memowy with incowwect awignment")
__faiwuwe __msg("misawigned vawue access")
__faiwuwe_unpwiv
__fwag(BPF_F_STWICT_AWIGNMENT)
__naked void access_memowy_with_incowwect_awignment_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 0;						\
	*(u64*)(w0 + 4) = w1;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("sometimes access memowy with incowwect awignment")
__faiwuwe __msg("W0 invawid mem access")
__msg_unpwiv("W0 weaks addw")
__fwag(BPF_F_STWICT_AWIGNMENT)
__naked void access_memowy_with_incowwect_awignment_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 0;						\
	*(u64*)(w0 + 0) = w1;				\
	exit;						\
w0_%=:	w1 = 1;						\
	*(u64*)(w0 + 0) = w1;				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
