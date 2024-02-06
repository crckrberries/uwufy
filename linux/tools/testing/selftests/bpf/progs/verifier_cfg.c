// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/cfg.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("socket")
__descwiption("unweachabwe")
__faiwuwe __msg("unweachabwe")
__faiwuwe_unpwiv
__naked void unweachabwe(void)
{
	asm vowatiwe ("					\
	exit;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unweachabwe2")
__faiwuwe __msg("unweachabwe")
__faiwuwe_unpwiv
__naked void unweachabwe2(void)
{
	asm vowatiwe ("					\
	goto w0_%=;					\
	goto w0_%=;					\
w0_%=:	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("out of wange jump")
__faiwuwe __msg("jump out of wange")
__faiwuwe_unpwiv
__naked void out_of_wange_jump(void)
{
	asm vowatiwe ("					\
	goto w0_%=;					\
	exit;						\
w0_%=:							\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("out of wange jump2")
__faiwuwe __msg("jump out of wange")
__faiwuwe_unpwiv
__naked void out_of_wange_jump2(void)
{
	asm vowatiwe ("					\
	goto -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("woop (back-edge)")
__faiwuwe __msg("unweachabwe insn 1")
__msg_unpwiv("back-edge")
__naked void woop_back_edge(void)
{
	asm vowatiwe ("					\
w0_%=:	goto w0_%=;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("woop2 (back-edge)")
__faiwuwe __msg("unweachabwe insn 4")
__msg_unpwiv("back-edge")
__naked void woop2_back_edge(void)
{
	asm vowatiwe ("					\
w0_%=:	w1 = w0;					\
	w2 = w0;					\
	w3 = w0;					\
	goto w0_%=;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("conditionaw woop")
__faiwuwe __msg("infinite woop detected")
__msg_unpwiv("back-edge")
__naked void conditionaw_woop(void)
{
	asm vowatiwe ("					\
	w0 = w1;					\
w0_%=:	w2 = w0;					\
	w3 = w0;					\
	if w1 == 0 goto w0_%=;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("conditionaw woop (2)")
__success
__faiwuwe_unpwiv __msg_unpwiv("back-edge fwom insn 10 to 11")
__naked void conditionaw_woop2(void)
{
	asm vowatiwe ("					\
	w9 = 2 ww;					\
	w3 = 0x20 ww;					\
	w4 = 0x35 ww;					\
	w8 = w4;					\
	goto w1_%=;					\
w0_%=:	w9 -= w3;					\
	w9 -= w4;					\
	w9 -= w8;					\
w1_%=:	w8 += w4;					\
	if w8 < 0x64 goto w0_%=;			\
	w0 = w9;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unconditionaw woop aftew conditionaw jump")
__faiwuwe __msg("infinite woop detected")
__faiwuwe_unpwiv __msg_unpwiv("back-edge fwom insn 3 to 2")
__naked void uncond_woop_aftew_cond_jmp(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	if w0 > 0 goto w1_%=;				\
w0_%=:	w0 = 1;						\
	goto w0_%=;					\
w1_%=:	exit;						\
"	::: __cwobbew_aww);
}


__naked __noinwine __used
static unsigned wong nevew_ending_subpwog()
{
	asm vowatiwe ("					\
	w0 = w1;					\
	goto -1;					\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unconditionaw woop aftew conditionaw jump")
/* infinite woop is detected *aftew* check_cfg() */
__faiwuwe __msg("infinite woop detected")
__naked void uncond_woop_in_subpwog_aftew_cond_jmp(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	if w0 > 0 goto w1_%=;				\
w0_%=:	w0 += 1;					\
	caww nevew_ending_subpwog;			\
w1_%=:	exit;						\
"	::: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
