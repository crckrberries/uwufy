// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <non_const> == <const>, 1")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 3 goto w0_%=;				\
	w2 = 2;						\
	if w0 == w2 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <non_const> == <const>, 2")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_2(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 > 3 goto w0_%=;				\
	w2 = 4;						\
	if w0 == w2 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <non_const> != <const>, 1")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_3(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 3 goto w0_%=;				\
	w2 = 2;						\
	if w0 != w2 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <non_const> != <const>, 2")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_4(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 > 3 goto w0_%=;				\
	w2 = 4;						\
	if w0 != w2 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <non_const> == <const>, 1")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_5(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 4 goto w0_%=;				\
	w2 = 3;						\
	if w0 == w2 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <non_const> == <const>, 2")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_6(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 > 4 goto w0_%=;				\
	w2 = 5;						\
	if w0 == w2 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <non_const> != <const>, 1")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_7(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 3 goto w0_%=;				\
	w2 = 2;						\
	if w0 != w2 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <non_const> != <const>, 2")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_8(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 > 3 goto w0_%=;				\
	w2 = 4;						\
	if w0 != w2 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> > <non_const>, 1")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_9(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	w2 = 0;						\
	if w2 > w0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> > <non_const>, 2")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_10(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 > w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> >= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_11(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 4 goto w0_%=;				\
	w2 = 3;						\
	if w2 >= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> < <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_12(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 > 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 < w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> <= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_13(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 >= 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 <= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> == <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_14(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 3 goto w0_%=;				\
	w2 = 2;						\
	if w2 == w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> s> <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_15(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s< 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 s> w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> s>= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_16(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s< 4 goto w0_%=;				\
	w2 = 3;						\
	if w2 s>= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> s< <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_17(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s> 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 s< w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> s<= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_18(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s> 4 goto w0_%=;				\
	w2 = 5;						\
	if w2 s<= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp64, <const> != <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_19(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 3 goto w0_%=;				\
	w2 = 2;						\
	if w2 != w0 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> > <non_const>, 1")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_20(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	w2 = 0;						\
	if w2 > w0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> > <non_const>, 2")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_21(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 > w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> >= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_22(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 4 goto w0_%=;				\
	w2 = 3;						\
	if w2 >= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> < <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_23(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 > 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 < w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> <= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_24(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 >= 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 <= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> == <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_25(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 4 goto w0_%=;				\
	w2 = 3;						\
	if w2 == w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> s> <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_26(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s< 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 s> w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> s>= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_27(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s< 4 goto w0_%=;				\
	w2 = 3;						\
	if w2 s>= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> s< <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_28(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s> 4 goto w0_%=;				\
	w2 = 5;						\
	if w2 s< w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> s<= <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_29(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 s>= 4 goto w0_%=;				\
	w2 = 4;						\
	if w2 s<= w0 goto w1_%=;				\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check deducing bounds fwom non-const, jmp32, <const> != <non_const>")
__success __wetvaw(0)
__naked void deducing_bounds_fwom_non_const_30(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	if w0 < 3 goto w0_%=;				\
	w2 = 2;						\
	if w2 != w0 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:							\
	w0 = 0;						\
	exit;						\
w1_%=:							\
	w0 -= w1;					\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
