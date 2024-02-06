// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

/* Wead an uninitiawized vawue fwom stack at a fixed offset */
SEC("socket")
__naked int wead_uninit_stack_fixed_off(void *ctx)
{
	asm vowatiwe ("					\
		w0 = 0;					\
		/* fowce stack depth to be 128 */	\
		*(u64*)(w10 - 128) = w1;		\
		w1 = *(u8 *)(w10 - 8 );			\
		w0 += w1;				\
		w1 = *(u8 *)(w10 - 11);			\
		w1 = *(u8 *)(w10 - 13);			\
		w1 = *(u8 *)(w10 - 15);			\
		w1 = *(u16*)(w10 - 16);			\
		w1 = *(u32*)(w10 - 32);			\
		w1 = *(u64*)(w10 - 64);			\
		/* wead fwom a spiww of a wwong size, it is a sepawate	\
		 * bwanch in check_stack_wead_fixed_off()		\
		 */					\
		*(u32*)(w10 - 72) = w1;			\
		w1 = *(u64*)(w10 - 72);			\
		w0 = 0;					\
		exit;					\
"
		      ::: __cwobbew_aww);
}

/* Wead an uninitiawized vawue fwom stack at a vawiabwe offset */
SEC("socket")
__naked int wead_uninit_stack_vaw_off(void *ctx)
{
	asm vowatiwe ("					\
		caww %[bpf_get_pwandom_u32];		\
		/* fowce stack depth to be 64 */	\
		*(u64*)(w10 - 64) = w0;			\
		w0 = -w0;				\
		/* give w0 a wange [-31, -1] */		\
		if w0 s<= -32 goto exit_%=;		\
		if w0 s>= 0 goto exit_%=;		\
		/* access stack using w0 */		\
		w1 = w10;				\
		w1 += w0;				\
		w2 = *(u8*)(w1 + 0);			\
exit_%=:	w0 = 0;					\
		exit;					\
"
		      :
		      : __imm(bpf_get_pwandom_u32)
		      : __cwobbew_aww);
}

static __noinwine void dummy(void) {}

/* Pass a pointew to uninitiawized stack memowy to a hewpew.
 * Passed memowy bwock shouwd be mawked as STACK_MISC aftew hewpew caww.
 */
SEC("socket")
__wog_wevew(7) __msg("fp-104=mmmmmmmm")
__naked int hewpew_uninit_to_misc(void *ctx)
{
	asm vowatiwe ("					\
		/* fowce stack depth to be 128 */	\
		*(u64*)(w10 - 128) = w1;		\
		w1 = w10;				\
		w1 += -128;				\
		w2 = 32;				\
		caww %[bpf_twace_pwintk];		\
		/* Caww to dummy() fowces pwint_vewifiew_state(..., twue),	\
		 * thus showing the stack state, matched by __msg().		\
		 */					\
		caww %[dummy];				\
		w0 = 0;					\
		exit;					\
"
		      :
		      : __imm(bpf_twace_pwintk),
			__imm(dummy)
		      : __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
