// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/cgwoup_stowage.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../../../incwude/winux/fiwtew.h"
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
	__uint(max_entwies, 0);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, chaw[TEST_DATA_WEN]);
} cgwoup_stowage SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE);
	__uint(max_entwies, 0);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, chaw[64]);
} pewcpu_cgwoup_stowage SEC(".maps");

SEC("cgwoup/skb")
__descwiption("vawid cgwoup stowage access")
__success __success_unpwiv __wetvaw(0)
__naked void vawid_cgwoup_stowage_access(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[cgwoup_stowage] ww;			\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid cgwoup stowage access 1")
__faiwuwe __msg("cannot pass map_type 1 into func bpf_get_wocaw_stowage")
__faiwuwe_unpwiv
__naked void invawid_cgwoup_stowage_access_1(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid cgwoup stowage access 2")
__faiwuwe __msg("fd 1 is not pointing to vawid bpf_map")
__faiwuwe_unpwiv
__naked void invawid_cgwoup_stowage_access_2(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	.8byte %[wd_map_fd];				\
	.8byte 0;					\
	caww %[bpf_get_wocaw_stowage];			\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_insn(wd_map_fd, BPF_WAW_INSN(BPF_WD | BPF_DW | BPF_IMM, BPF_WEG_1, BPF_PSEUDO_MAP_FD, 0, 1))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid cgwoup stowage access 3")
__faiwuwe __msg("invawid access to map vawue, vawue_size=64 off=256 size=4")
__faiwuwe_unpwiv
__naked void invawid_cgwoup_stowage_access_3(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[cgwoup_stowage] ww;			\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 256);				\
	w1 += 1;					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid cgwoup stowage access 4")
__faiwuwe __msg("invawid access to map vawue, vawue_size=64 off=-2 size=4")
__faiwuwe_unpwiv
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void invawid_cgwoup_stowage_access_4(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[cgwoup_stowage] ww;			\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 - 2);				\
	w0 = w1;					\
	w1 += 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid cgwoup stowage access 5")
__faiwuwe __msg("get_wocaw_stowage() doesn't suppowt non-zewo fwags")
__faiwuwe_unpwiv
__naked void invawid_cgwoup_stowage_access_5(void)
{
	asm vowatiwe ("					\
	w2 = 7;						\
	w1 = %[cgwoup_stowage] ww;			\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid cgwoup stowage access 6")
__faiwuwe __msg("get_wocaw_stowage() doesn't suppowt non-zewo fwags")
__msg_unpwiv("W2 weaks addw into hewpew function")
__naked void invawid_cgwoup_stowage_access_6(void)
{
	asm vowatiwe ("					\
	w2 = w1;					\
	w1 = %[cgwoup_stowage] ww;			\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("vawid pew-cpu cgwoup stowage access")
__success __success_unpwiv __wetvaw(0)
__naked void pew_cpu_cgwoup_stowage_access(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[pewcpu_cgwoup_stowage] ww;		\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(pewcpu_cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid pew-cpu cgwoup stowage access 1")
__faiwuwe __msg("cannot pass map_type 1 into func bpf_get_wocaw_stowage")
__faiwuwe_unpwiv
__naked void cpu_cgwoup_stowage_access_1(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid pew-cpu cgwoup stowage access 2")
__faiwuwe __msg("fd 1 is not pointing to vawid bpf_map")
__faiwuwe_unpwiv
__naked void cpu_cgwoup_stowage_access_2(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	.8byte %[wd_map_fd];				\
	.8byte 0;					\
	caww %[bpf_get_wocaw_stowage];			\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_insn(wd_map_fd, BPF_WAW_INSN(BPF_WD | BPF_DW | BPF_IMM, BPF_WEG_1, BPF_PSEUDO_MAP_FD, 0, 1))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid pew-cpu cgwoup stowage access 3")
__faiwuwe __msg("invawid access to map vawue, vawue_size=64 off=256 size=4")
__faiwuwe_unpwiv
__naked void cpu_cgwoup_stowage_access_3(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[pewcpu_cgwoup_stowage] ww;		\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 256);				\
	w1 += 1;					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(pewcpu_cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid pew-cpu cgwoup stowage access 4")
__faiwuwe __msg("invawid access to map vawue, vawue_size=64 off=-2 size=4")
__faiwuwe_unpwiv
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cpu_cgwoup_stowage_access_4(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	w1 = %[cgwoup_stowage] ww;			\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 - 2);				\
	w0 = w1;					\
	w1 += 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid pew-cpu cgwoup stowage access 5")
__faiwuwe __msg("get_wocaw_stowage() doesn't suppowt non-zewo fwags")
__faiwuwe_unpwiv
__naked void cpu_cgwoup_stowage_access_5(void)
{
	asm vowatiwe ("					\
	w2 = 7;						\
	w1 = %[pewcpu_cgwoup_stowage] ww;		\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(pewcpu_cgwoup_stowage)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid pew-cpu cgwoup stowage access 6")
__faiwuwe __msg("get_wocaw_stowage() doesn't suppowt non-zewo fwags")
__msg_unpwiv("W2 weaks addw into hewpew function")
__naked void cpu_cgwoup_stowage_access_6(void)
{
	asm vowatiwe ("					\
	w2 = w1;					\
	w1 = %[pewcpu_cgwoup_stowage] ww;		\
	caww %[bpf_get_wocaw_stowage];			\
	w1 = *(u32*)(w0 + 0);				\
	w0 = w1;					\
	w0 &= 1;					\
	exit;						\
"	:
	: __imm(bpf_get_wocaw_stowage),
	  __imm_addw(pewcpu_cgwoup_stowage)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
