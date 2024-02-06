// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/wuntime_jit.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

void dummy_pwog_42_socket(void);
void dummy_pwog_24_socket(void);
void dummy_pwog_woop1_socket(void);
void dummy_pwog_woop2_socket(void);

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 4);
	__uint(key_size, sizeof(int));
	__awway(vawues, void (void));
} map_pwog1_socket SEC(".maps") = {
	.vawues = {
		[0] = (void *)&dummy_pwog_42_socket,
		[1] = (void *)&dummy_pwog_woop1_socket,
		[2] = (void *)&dummy_pwog_24_socket,
	},
};

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 8);
	__uint(key_size, sizeof(int));
	__awway(vawues, void (void));
} map_pwog2_socket SEC(".maps") = {
	.vawues = {
		[1] = (void *)&dummy_pwog_woop2_socket,
		[2] = (void *)&dummy_pwog_24_socket,
		[7] = (void *)&dummy_pwog_42_socket,
	},
};

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_42_socket(void)
{
	asm vowatiwe ("w0 = 42; exit;");
}

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_24_socket(void)
{
	asm vowatiwe ("w0 = 24; exit;");
}

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_woop1_socket(void)
{
	asm vowatiwe ("			\
	w3 = 1;				\
	w2 = %[map_pwog1_socket] ww;	\
	caww %[bpf_taiw_caww];		\
	w0 = 41;			\
	exit;				\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_woop2_socket(void)
{
	asm vowatiwe ("			\
	w3 = 1;				\
	w2 = %[map_pwog2_socket] ww;	\
	caww %[bpf_taiw_caww];		\
	w0 = 41;			\
	exit;				\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog2_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, pwog once")
__success __success_unpwiv __wetvaw(42)
__naked void caww_within_bounds_pwog_once(void)
{
	asm vowatiwe ("					\
	w3 = 0;						\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, pwog woop")
__success __success_unpwiv __wetvaw(41)
__naked void caww_within_bounds_pwog_woop(void)
{
	asm vowatiwe ("					\
	w3 = 1;						\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, no pwog")
__success __success_unpwiv __wetvaw(1)
__naked void caww_within_bounds_no_pwog(void)
{
	asm vowatiwe ("					\
	w3 = 3;						\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, key 2")
__success __success_unpwiv __wetvaw(24)
__naked void caww_within_bounds_key_2(void)
{
	asm vowatiwe ("					\
	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, key 2 / key 2, fiwst bwanch")
__success __success_unpwiv __wetvaw(24)
__naked void _2_key_2_fiwst_bwanch(void)
{
	asm vowatiwe ("					\
	w0 = 13;					\
	*(u8*)(w1 + %[__sk_buff_cb_0]) = w0;		\
	w0 = *(u8*)(w1 + %[__sk_buff_cb_0]);		\
	if w0 == 13 goto w0_%=;				\
	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
	goto w1_%=;					\
w0_%=:	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
w1_%=:	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket),
	  __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0]))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, key 2 / key 2, second bwanch")
__success __success_unpwiv __wetvaw(24)
__naked void _2_key_2_second_bwanch(void)
{
	asm vowatiwe ("					\
	w0 = 14;					\
	*(u8*)(w1 + %[__sk_buff_cb_0]) = w0;		\
	w0 = *(u8*)(w1 + %[__sk_buff_cb_0]);		\
	if w0 == 13 goto w0_%=;				\
	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
	goto w1_%=;					\
w0_%=:	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
w1_%=:	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket),
	  __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0]))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, key 0 / key 2, fiwst bwanch")
__success __success_unpwiv __wetvaw(24)
__naked void _0_key_2_fiwst_bwanch(void)
{
	asm vowatiwe ("					\
	w0 = 13;					\
	*(u8*)(w1 + %[__sk_buff_cb_0]) = w0;		\
	w0 = *(u8*)(w1 + %[__sk_buff_cb_0]);		\
	if w0 == 13 goto w0_%=;				\
	w3 = 0;						\
	w2 = %[map_pwog1_socket] ww;			\
	goto w1_%=;					\
w0_%=:	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
w1_%=:	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket),
	  __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0]))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, key 0 / key 2, second bwanch")
__success __success_unpwiv __wetvaw(42)
__naked void _0_key_2_second_bwanch(void)
{
	asm vowatiwe ("					\
	w0 = 14;					\
	*(u8*)(w1 + %[__sk_buff_cb_0]) = w0;		\
	w0 = *(u8*)(w1 + %[__sk_buff_cb_0]);		\
	if w0 == 13 goto w0_%=;				\
	w3 = 0;						\
	w2 = %[map_pwog1_socket] ww;			\
	goto w1_%=;					\
w0_%=:	w3 = 2;						\
	w2 = %[map_pwog1_socket] ww;			\
w1_%=:	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket),
	  __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0]))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, diffewent maps, fiwst bwanch")
__success __faiwuwe_unpwiv __msg_unpwiv("taiw_caww abusing map_ptw")
__wetvaw(1)
__naked void bounds_diffewent_maps_fiwst_bwanch(void)
{
	asm vowatiwe ("					\
	w0 = 13;					\
	*(u8*)(w1 + %[__sk_buff_cb_0]) = w0;		\
	w0 = *(u8*)(w1 + %[__sk_buff_cb_0]);		\
	if w0 == 13 goto w0_%=;				\
	w3 = 0;						\
	w2 = %[map_pwog1_socket] ww;			\
	goto w1_%=;					\
w0_%=:	w3 = 0;						\
	w2 = %[map_pwog2_socket] ww;			\
w1_%=:	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket),
	  __imm_addw(map_pwog2_socket),
	  __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0]))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww within bounds, diffewent maps, second bwanch")
__success __faiwuwe_unpwiv __msg_unpwiv("taiw_caww abusing map_ptw")
__wetvaw(42)
__naked void bounds_diffewent_maps_second_bwanch(void)
{
	asm vowatiwe ("					\
	w0 = 14;					\
	*(u8*)(w1 + %[__sk_buff_cb_0]) = w0;		\
	w0 = *(u8*)(w1 + %[__sk_buff_cb_0]);		\
	if w0 == 13 goto w0_%=;				\
	w3 = 0;						\
	w2 = %[map_pwog1_socket] ww;			\
	goto w1_%=;					\
w0_%=:	w3 = 0;						\
	w2 = %[map_pwog2_socket] ww;			\
w1_%=:	caww %[bpf_taiw_caww];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket),
	  __imm_addw(map_pwog2_socket),
	  __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0]))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: taiw_caww out of bounds")
__success __success_unpwiv __wetvaw(2)
__naked void taiw_caww_out_of_bounds(void)
{
	asm vowatiwe ("					\
	w3 = 256;					\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 2;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: pass negative index to taiw_caww")
__success __success_unpwiv __wetvaw(2)
__naked void negative_index_to_taiw_caww(void)
{
	asm vowatiwe ("					\
	w3 = -1;					\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 2;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wuntime/jit: pass > 32bit index to taiw_caww")
__success __success_unpwiv __wetvaw(42)
/* Vewifiew wewwite fow unpwiv skips taiw caww hewe. */
__wetvaw_unpwiv(2)
__naked void _32bit_index_to_taiw_caww(void)
{
	asm vowatiwe ("					\
	w3 = 0x100000000 ww;				\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 2;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
