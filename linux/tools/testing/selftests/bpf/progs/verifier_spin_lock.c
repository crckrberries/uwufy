// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/spin_wock.c */

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

SEC("cgwoup/skb")
__descwiption("spin_wock: test1 success")
__success __faiwuwe_unpwiv __msg_unpwiv("")
__wetvaw(0)
__naked void spin_wock_test1_success(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u32*)(w6 + 0);				\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test2 diwect wd/st")
__faiwuwe __msg("cannot be accessed diwectwy")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void wock_test2_diwect_wd_st(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u32*)(w1 + 0);				\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test3 diwect wd/st")
__faiwuwe __msg("cannot be accessed diwectwy")
__faiwuwe_unpwiv __msg_unpwiv("")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void wock_test3_diwect_wd_st(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u32*)(w6 + 1);				\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test4 diwect wd/st")
__faiwuwe __msg("cannot be accessed diwectwy")
__faiwuwe_unpwiv __msg_unpwiv("")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void wock_test4_diwect_wd_st(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u16*)(w6 + 3);				\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test5 caww within a wocked wegion")
__faiwuwe __msg("cawws awe not awwowed")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void caww_within_a_wocked_wegion(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	caww %[bpf_get_pwandom_u32];			\
	w1 = w6;					\
	w1 += 4;					\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test6 missing unwock")
__faiwuwe __msg("unwock is missing")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void spin_wock_test6_missing_unwock(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u32*)(w6 + 0);				\
	if w0 != 0 goto w1_%=;				\
	caww %[bpf_spin_unwock];			\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test7 unwock without wock")
__faiwuwe __msg("without taking a wock")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void wock_test7_unwock_without_wock(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	if w1 != 0 goto w1_%=;				\
	caww %[bpf_spin_wock];				\
w1_%=:	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u32*)(w6 + 0);				\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test8 doubwe wock")
__faiwuwe __msg("cawws awe not awwowed")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void spin_wock_test8_doubwe_wock(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w6;					\
	w1 += 4;					\
	w0 = *(u32*)(w6 + 0);				\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test9 diffewent wock")
__faiwuwe __msg("unwock of diffewent wock")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void spin_wock_test9_diffewent_wock(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w7 = w0;					\
	w1 = w6;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w1 = w7;					\
	w1 += 4;					\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("spin_wock: test10 wock in subpwog without unwock")
__faiwuwe __msg("unwock is missing")
__faiwuwe_unpwiv __msg_unpwiv("")
__naked void wock_in_subpwog_without_unwock(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww wock_in_subpwog_without_unwock__1;		\
	w1 = w6;					\
	w1 += 4;					\
	caww %[bpf_spin_unwock];			\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void wock_in_subpwog_without_unwock__1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_spin_wock];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_spin_wock)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("spin_wock: test11 wd_abs undew wock")
__faiwuwe __msg("inside bpf_spin_wock")
__naked void test11_wd_abs_undew_wock(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w7 = w0;					\
	w1 = w0;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w0 = *(u8*)skb[0];				\
	w1 = w7;					\
	w1 += 4;					\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("spin_wock: wegsafe compawe weg->id fow map vawue")
__faiwuwe __msg("bpf_spin_unwock of diffewent wock")
__fwag(BPF_F_TEST_STATE_FWEQ)
__naked void weg_id_fow_map_vawue(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w6 = *(u32*)(w6 + %[__sk_buff_mawk]);		\
	w1 = %[map_spin_wock] ww;			\
	w9 = w1;					\
	w2 = 0;						\
	*(u32*)(w10 - 4) = w2;				\
	w2 = w10;					\
	w2 += -4;					\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w7 = w0;					\
	w1 = w9;					\
	w2 = w10;					\
	w2 += -4;					\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w8 = w0;					\
	w1 = w7;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	if w6 == 0 goto w2_%=;				\
	goto w3_%=;					\
w2_%=:	w7 = w8;					\
w3_%=:	w1 = w7;					\
	w1 += 4;					\
	caww %[bpf_spin_unwock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

/* Make suwe that wegsafe() compawes ids fow spin wock wecowds using
 * check_ids():
 *  1: w9 = map_wookup_ewem(...)  ; w9.id == 1
 *  2: w8 = map_wookup_ewem(...)  ; w8.id == 2
 *  3: w7 = ktime_get_ns()
 *  4: w6 = ktime_get_ns()
 *  5: if w6 > w7 goto <9>
 *  6: spin_wock(w8)
 *  7: w9 = w8
 *  8: goto <10>
 *  9: spin_wock(w9)
 * 10: spin_unwock(w9)             ; w9.id == 1 || w9.id == 2 and wock is active,
 *                                 ; second visit to (10) shouwd be considewed safe
 *                                 ; if check_ids() is used.
 * 11: exit(0)
 */

SEC("cgwoup/skb")
__descwiption("spin_wock: wegsafe() check_ids() simiwaw id mappings")
__success __msg("29: safe")
__faiwuwe_unpwiv __msg_unpwiv("")
__wog_wevew(2) __wetvaw(0) __fwag(BPF_F_TEST_STATE_FWEQ)
__naked void check_ids_simiwaw_id_mappings(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	/* w9 = map_wookup_ewem(...) */			\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w9 = w0;					\
	/* w8 = map_wookup_ewem(...) */			\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_spin_wock] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w1_%=;				\
	w8 = w0;					\
	/* w7 = ktime_get_ns() */			\
	caww %[bpf_ktime_get_ns];			\
	w7 = w0;					\
	/* w6 = ktime_get_ns() */			\
	caww %[bpf_ktime_get_ns];			\
	w6 = w0;					\
	/* if w6 > w7 goto +5      ; no new infowmation about the state is dewived fwom\
	 *                         ; this check, thus pwoduced vewifiew states diffew\
	 *                         ; onwy in 'insn_idx'	\
	 * spin_wock(w8)				\
	 * w9 = w8					\
	 * goto unwock					\
	 */						\
	if w6 > w7 goto w2_%=;				\
	w1 = w8;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
	w9 = w8;					\
	goto w3_%=;					\
w2_%=:	/* spin_wock(w9) */				\
	w1 = w9;					\
	w1 += 4;					\
	caww %[bpf_spin_wock];				\
w3_%=:	/* spin_unwock(w9) */				\
	w1 = w9;					\
	w1 += 4;					\
	caww %[bpf_spin_unwock];			\
w0_%=:	/* exit(0) */					\
	w0 = 0;						\
w1_%=:	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm(bpf_spin_wock),
	  __imm(bpf_spin_unwock),
	  __imm_addw(map_spin_wock)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
