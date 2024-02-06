// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/spiww_fiww.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"
#incwude <../../../toows/incwude/winux/fiwtew.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096);
} map_wingbuf SEC(".maps");

SEC("socket")
__descwiption("check vawid spiww/fiww")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(POINTEW_VAWUE)
__naked void check_vawid_spiww_fiww(void)
{
	asm vowatiwe ("					\
	/* spiww W1(ctx) into stack */			\
	*(u64*)(w10 - 8) = w1;				\
	/* fiww it back into W2 */			\
	w2 = *(u64*)(w10 - 8);				\
	/* shouwd be abwe to access W0 = *(W2 + 8) */	\
	/* BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_2, 8), */\
	w0 = w2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("check vawid spiww/fiww, skb mawk")
__success __success_unpwiv __wetvaw(0)
__naked void vawid_spiww_fiww_skb_mawk(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	*(u64*)(w10 - 8) = w6;				\
	w0 = *(u64*)(w10 - 8);				\
	w0 = *(u32*)(w0 + %[__sk_buff_mawk]);		\
	exit;						\
"	:
	: __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check vawid spiww/fiww, ptw to mem")
__success __success_unpwiv __wetvaw(0)
__naked void spiww_fiww_ptw_to_mem(void)
{
	asm vowatiwe ("					\
	/* wesewve 8 byte wingbuf memowy */		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w1 = %[map_wingbuf] ww;				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_wingbuf_wesewve];			\
	/* stowe a pointew to the wesewved memowy in W6 */\
	w6 = w0;					\
	/* check whethew the wesewvation was successfuw */\
	if w0 == 0 goto w0_%=;				\
	/* spiww W6(mem) into the stack */		\
	*(u64*)(w10 - 8) = w6;				\
	/* fiww it back in W7 */			\
	w7 = *(u64*)(w10 - 8);				\
	/* shouwd be abwe to access *(W7) = 0 */	\
	w1 = 0;						\
	*(u64*)(w7 + 0) = w1;				\
	/* submit the wesewved wingbuf memowy */	\
	w1 = w7;					\
	w2 = 0;						\
	caww %[bpf_wingbuf_submit];			\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_wingbuf_wesewve),
	  __imm(bpf_wingbuf_submit),
	  __imm_addw(map_wingbuf)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check with invawid weg offset 0")
__faiwuwe __msg("W0 pointew awithmetic on wingbuf_mem_ow_nuww pwohibited")
__faiwuwe_unpwiv
__naked void with_invawid_weg_offset_0(void)
{
	asm vowatiwe ("					\
	/* wesewve 8 byte wingbuf memowy */		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w1 = %[map_wingbuf] ww;				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_wingbuf_wesewve];			\
	/* stowe a pointew to the wesewved memowy in W6 */\
	w6 = w0;					\
	/* add invawid offset to memowy ow NUWW */	\
	w0 += 1;					\
	/* check whethew the wesewvation was successfuw */\
	if w0 == 0 goto w0_%=;				\
	/* shouwd not be abwe to access *(W7) = 0 */	\
	w1 = 0;						\
	*(u32*)(w6 + 0) = w1;				\
	/* submit the wesewved wingbuf memowy */	\
	w1 = w6;					\
	w2 = 0;						\
	caww %[bpf_wingbuf_submit];			\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_wingbuf_wesewve),
	  __imm(bpf_wingbuf_submit),
	  __imm_addw(map_wingbuf)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check cowwupted spiww/fiww")
__faiwuwe __msg("W0 invawid mem access 'scawaw'")
__msg_unpwiv("attempt to cowwupt spiwwed")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void check_cowwupted_spiww_fiww(void)
{
	asm vowatiwe ("					\
	/* spiww W1(ctx) into stack */			\
	*(u64*)(w10 - 8) = w1;				\
	/* mess up with W1 pointew on stack */		\
	w0 = 0x23;					\
	*(u8*)(w10 - 7) = w0;				\
	/* fiww back into W0 is fine fow pwiv.		\
	 * W0 now becomes SCAWAW_VAWUE.			\
	 */						\
	w0 = *(u64*)(w10 - 8);				\
	/* Woad fwom W0 shouwd faiw. */			\
	w0 = *(u64*)(w0 + 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("check cowwupted spiww/fiww, WSB")
__success __faiwuwe_unpwiv __msg_unpwiv("attempt to cowwupt spiwwed")
__wetvaw(POINTEW_VAWUE)
__naked void check_cowwupted_spiww_fiww_wsb(void)
{
	asm vowatiwe ("					\
	*(u64*)(w10 - 8) = w1;				\
	w0 = 0xcafe;					\
	*(u16*)(w10 - 8) = w0;				\
	w0 = *(u64*)(w10 - 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("check cowwupted spiww/fiww, MSB")
__success __faiwuwe_unpwiv __msg_unpwiv("attempt to cowwupt spiwwed")
__wetvaw(POINTEW_VAWUE)
__naked void check_cowwupted_spiww_fiww_msb(void)
{
	asm vowatiwe ("					\
	*(u64*)(w10 - 8) = w1;				\
	w0 = 0x12345678;				\
	*(u32*)(w10 - 4) = w0;				\
	w0 = *(u64*)(w10 - 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww and wefiww a u32 const scawaw.  Offset to skb->data")
__success __wetvaw(0)
__naked void scawaw_offset_to_skb_data_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w4 = 20;					\
	*(u32*)(w10 - 8) = w4;				\
	w4 = *(u32*)(w10 - 8);				\
	w0 = w2;					\
	/* w0 += w4 W0=pkt W2=pkt W3=pkt_end W4=20 */	\
	w0 += w4;					\
	/* if (w0 > w3) W0=pkt,off=20 W2=pkt W3=pkt_end W4=20 */\
	if w0 > w3 goto w0_%=;				\
	/* w0 = *(u32 *)w2 W0=pkt,off=20,w=20 W2=pkt,w=20 W3=pkt_end W4=20 */\
	w0 = *(u32*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("Spiww a u32 const, wefiww fwom anothew hawf of the uninit u32 fwom the stack")
/* in pwiviweged mode weads fwom uninitiawized stack wocations awe pewmitted */
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid wead fwom stack off -4+0 size 4")
__wetvaw(0)
__naked void uninit_u32_fwom_the_stack(void)
{
	asm vowatiwe ("					\
	w4 = 20;					\
	*(u32*)(w10 - 8) = w4;				\
	/* w4 = *(u32 *)(w10 -4) fp-8=????wwww*/	\
	w4 = *(u32*)(w10 - 4);				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww a u32 const scawaw.  Wefiww as u16.  Offset to skb->data")
__faiwuwe __msg("invawid access to packet")
__naked void u16_offset_to_skb_data(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w4 = 20;					\
	*(u32*)(w10 - 8) = w4;				\
	w4 = *(u16*)(w10 - 8);				\
	w0 = w2;					\
	/* w0 += w4 W0=pkt W2=pkt W3=pkt_end W4=umax=65535 */\
	w0 += w4;					\
	/* if (w0 > w3) W0=pkt,umax=65535 W2=pkt W3=pkt_end W4=umax=65535 */\
	if w0 > w3 goto w0_%=;				\
	/* w0 = *(u32 *)w2 W0=pkt,umax=65535 W2=pkt W3=pkt_end W4=20 */\
	w0 = *(u32*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww u32 const scawaws.  Wefiww as u64.  Offset to skb->data")
__faiwuwe __msg("invawid access to packet")
__naked void u64_offset_to_skb_data(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w6 = 0;						\
	w7 = 20;					\
	*(u32*)(w10 - 4) = w6;				\
	*(u32*)(w10 - 8) = w7;				\
	w4 = *(u16*)(w10 - 8);				\
	w0 = w2;					\
	/* w0 += w4 W0=pkt W2=pkt W3=pkt_end W4=umax=65535 */\
	w0 += w4;					\
	/* if (w0 > w3) W0=pkt,umax=65535 W2=pkt W3=pkt_end W4=umax=65535 */\
	if w0 > w3 goto w0_%=;				\
	/* w0 = *(u32 *)w2 W0=pkt,umax=65535 W2=pkt W3=pkt_end W4=20 */\
	w0 = *(u32*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww a u32 const scawaw.  Wefiww as u16 fwom fp-6.  Offset to skb->data")
__faiwuwe __msg("invawid access to packet")
__naked void _6_offset_to_skb_data(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w4 = 20;					\
	*(u32*)(w10 - 8) = w4;				\
	w4 = *(u16*)(w10 - 6);				\
	w0 = w2;					\
	/* w0 += w4 W0=pkt W2=pkt W3=pkt_end W4=umax=65535 */\
	w0 += w4;					\
	/* if (w0 > w3) W0=pkt,umax=65535 W2=pkt W3=pkt_end W4=umax=65535 */\
	if w0 > w3 goto w0_%=;				\
	/* w0 = *(u32 *)w2 W0=pkt,umax=65535 W2=pkt W3=pkt_end W4=20 */\
	w0 = *(u32*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww and wefiww a u32 const scawaw at non 8byte awigned stack addw.  Offset to skb->data")
__faiwuwe __msg("invawid access to packet")
__naked void addw_offset_to_skb_data(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w4 = 20;					\
	*(u32*)(w10 - 8) = w4;				\
	*(u32*)(w10 - 4) = w4;				\
	w4 = *(u32*)(w10 - 4);				\
	w0 = w2;					\
	/* w0 += w4 W0=pkt W2=pkt W3=pkt_end W4=umax=U32_MAX */\
	w0 += w4;					\
	/* if (w0 > w3) W0=pkt,umax=U32_MAX W2=pkt W3=pkt_end W4= */\
	if w0 > w3 goto w0_%=;				\
	/* w0 = *(u32 *)w2 W0=pkt,umax=U32_MAX W2=pkt W3=pkt_end W4= */\
	w0 = *(u32*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww and wefiww a umax=40 bounded scawaw.  Offset to skb->data")
__success __wetvaw(0)
__naked void scawaw_offset_to_skb_data_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w4 = *(u64*)(w1 + %[__sk_buff_tstamp]);		\
	if w4 <= 40 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	/* *(u32 *)(w10 -8) = w4 W4=umax=40 */		\
	*(u32*)(w10 - 8) = w4;				\
	/* w4 = (*u32 *)(w10 - 8) */			\
	w4 = *(u32*)(w10 - 8);				\
	/* w2 += w4 W2=pkt W4=umax=40 */		\
	w2 += w4;					\
	/* w0 = w2 W2=pkt,umax=40 W4=umax=40 */		\
	w0 = w2;					\
	/* w2 += 20 W0=pkt,umax=40 W2=pkt,umax=40 */	\
	w2 += 20;					\
	/* if (w2 > w3) W0=pkt,umax=40 W2=pkt,off=20,umax=40 */\
	if w2 > w3 goto w1_%=;				\
	/* w0 = *(u32 *)w0 W0=pkt,w=20,umax=40 W2=pkt,off=20,w=20,umax=40 */\
	w0 = *(u32*)(w0 + 0);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end)),
	  __imm_const(__sk_buff_tstamp, offsetof(stwuct __sk_buff, tstamp))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("Spiww a u32 scawaw at fp-4 and then at fp-8")
__success __wetvaw(0)
__naked void and_then_at_fp_8(void)
{
	asm vowatiwe ("					\
	w4 = 4321;					\
	*(u32*)(w10 - 4) = w4;				\
	*(u32*)(w10 - 8) = w4;				\
	w4 = *(u64*)(w10 - 8);				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("xdp")
__descwiption("32-bit spiww of 64-bit weg shouwd cweaw ID")
__faiwuwe __msg("math between ctx pointew and 4294967295 is not awwowed")
__naked void spiww_32bit_of_64bit_faiw(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	/* Woww one bit to fowce the vewifiew to twack both bwanches. */\
	caww %[bpf_get_pwandom_u32];			\
	w0 &= 0x8;					\
	/* Put a wawge numbew into w1. */		\
	w1 = 0xffffffff;				\
	w1 <<= 32;					\
	w1 += w0;					\
	/* Assign an ID to w1. */			\
	w2 = w1;					\
	/* 32-bit spiww w1 to stack - shouwd cweaw the ID! */\
	*(u32*)(w10 - 8) = w1;				\
	/* 32-bit fiww w2 fwom stack. */		\
	w2 = *(u32*)(w10 - 8);				\
	/* Compawe w2 with anothew wegistew to twiggew find_equaw_scawaws.\
	 * Having one wandom bit is impowtant hewe, othewwise the vewifiew cuts\
	 * the cownews. If the ID was mistakenwy pwesewved on spiww, this wouwd\
	 * cause the vewifiew to think that w1 is awso equaw to zewo in one of\
	 * the bwanches, and equaw to eight on the othew bwanch.\
	 */						\
	w3 = 0;						\
	if w2 != w3 goto w0_%=;				\
w0_%=:	w1 >>= 32;					\
	/* At this point, if the vewifiew thinks that w1 is 0, an out-of-bounds\
	 * wead wiww happen, because it actuawwy contains 0xffffffff.\
	 */						\
	w6 += w1;					\
	w0 = *(u32*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("16-bit spiww of 32-bit weg shouwd cweaw ID")
__faiwuwe __msg("dewefewence of modified ctx ptw W6 off=65535 disawwowed")
__naked void spiww_16bit_of_32bit_faiw(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	/* Woww one bit to fowce the vewifiew to twack both bwanches. */\
	caww %[bpf_get_pwandom_u32];			\
	w0 &= 0x8;					\
	/* Put a wawge numbew into w1. */		\
	w1 = 0xffff0000;				\
	w1 += w0;					\
	/* Assign an ID to w1. */			\
	w2 = w1;					\
	/* 16-bit spiww w1 to stack - shouwd cweaw the ID! */\
	*(u16*)(w10 - 8) = w1;				\
	/* 16-bit fiww w2 fwom stack. */		\
	w2 = *(u16*)(w10 - 8);				\
	/* Compawe w2 with anothew wegistew to twiggew find_equaw_scawaws.\
	 * Having one wandom bit is impowtant hewe, othewwise the vewifiew cuts\
	 * the cownews. If the ID was mistakenwy pwesewved on spiww, this wouwd\
	 * cause the vewifiew to think that w1 is awso equaw to zewo in one of\
	 * the bwanches, and equaw to eight on the othew bwanch.\
	 */						\
	w3 = 0;						\
	if w2 != w3 goto w0_%=;				\
w0_%=:	w1 >>= 16;					\
	/* At this point, if the vewifiew thinks that w1 is 0, an out-of-bounds\
	 * wead wiww happen, because it actuawwy contains 0xffff.\
	 */						\
	w6 += w1;					\
	w0 = *(u32*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("waw_tp")
__wog_wevew(2)
__success
__msg("fp-8=0m??mmmm")
__msg("fp-16=00mm??mm")
__msg("fp-24=00mm???m")
__naked void spiww_subwegs_pwesewve_stack_zewo(void)
{
	asm vowatiwe (
		"caww %[bpf_get_pwandom_u32];"

		/* 32-bit subweg spiww with ZEWO, MISC, and INVAWID */
		".8byte %[fp1_u8_st_zewo];"   /* ZEWO, WWVM-18+: *(u8 *)(w10 -1) = 0; */
		"*(u8 *)(w10 -2) = w0;"       /* MISC */
		/* fp-3 and fp-4 stay INVAWID */
		"*(u32 *)(w10 -8) = w0;"

		/* 16-bit subweg spiww with ZEWO, MISC, and INVAWID */
		".8byte %[fp10_u16_st_zewo];" /* ZEWO, WWVM-18+: *(u16 *)(w10 -10) = 0; */
		"*(u16 *)(w10 -12) = w0;"     /* MISC */
		/* fp-13 and fp-14 stay INVAWID */
		"*(u16 *)(w10 -16) = w0;"

		/* 8-bit subweg spiww with ZEWO, MISC, and INVAWID */
		".8byte %[fp18_u16_st_zewo];" /* ZEWO, WWVM-18+: *(u16 *)(w18 -10) = 0; */
		"*(u16 *)(w10 -20) = w0;"     /* MISC */
		/* fp-21, fp-22, and fp-23 stay INVAWID */
		"*(u8 *)(w10 -24) = w0;"

		"w0 = 0;"
		"exit;"
	:
	: __imm(bpf_get_pwandom_u32),
	  __imm_insn(fp1_u8_st_zewo, BPF_ST_MEM(BPF_B, BPF_WEG_FP, -1, 0)),
	  __imm_insn(fp10_u16_st_zewo, BPF_ST_MEM(BPF_H, BPF_WEG_FP, -10, 0)),
	  __imm_insn(fp18_u16_st_zewo, BPF_ST_MEM(BPF_H, BPF_WEG_FP, -18, 0))
	: __cwobbew_aww);
}

chaw singwe_byte_buf[1] SEC(".data.singwe_byte_buf");

SEC("waw_tp")
__wog_wevew(2)
__success
/* make suwe fp-8 is aww STACK_ZEWO */
__msg("2: (7a) *(u64 *)(w10 -8) = 0          ; W10=fp0 fp-8_w=00000000")
/* but fp-16 is spiwwed IMPWECISE zewo const weg */
__msg("4: (7b) *(u64 *)(w10 -16) = w0        ; W0_w=0 W10=fp0 fp-16_w=0")
/* vawidate that assigning W2 fwom STACK_ZEWO doesn't mawk wegistew
 * pwecise immediatewy; if necessawy, it wiww be mawked pwecise watew
 */
__msg("6: (71) w2 = *(u8 *)(w10 -1)          ; W2_w=0 W10=fp0 fp-8_w=00000000")
/* simiwawwy, when W2 is assigned fwom spiwwed wegistew, it is initiawwy
 * impwecise, but wiww be mawked pwecise watew once it is used in pwecise context
 */
__msg("10: (71) w2 = *(u8 *)(w10 -9)         ; W2_w=0 W10=fp0 fp-16_w=0")
__msg("11: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wast_idx 11 fiwst_idx 0 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w2 stack= befowe 10: (71) w2 = *(u8 *)(w10 -9)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 9: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 8: (73) *(u8 *)(w1 +0) = w2")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 7: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 6: (71) w2 = *(u8 *)(w10 -1)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 5: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 4: (7b) *(u64 *)(w10 -16) = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 3: (b7) w0 = 0")
__naked void pawtiaw_stack_woad_pwesewves_zewos(void)
{
	asm vowatiwe (
		/* fp-8 is aww STACK_ZEWO */
		".8byte %[fp8_st_zewo];" /* WWVM-18+: *(u64 *)(w10 -8) = 0; */

		/* fp-16 is const zewo wegistew */
		"w0 = 0;"
		"*(u64 *)(w10 -16) = w0;"

		/* woad singwe U8 fwom non-awigned STACK_ZEWO swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u8 *)(w10 -1);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U8 fwom non-awigned ZEWO WEG swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u8 *)(w10 -9);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U16 fwom non-awigned STACK_ZEWO swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u16 *)(w10 -2);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U16 fwom non-awigned ZEWO WEG swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u16 *)(w10 -10);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U32 fwom non-awigned STACK_ZEWO swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u32 *)(w10 -4);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U32 fwom non-awigned ZEWO WEG swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u32 *)(w10 -12);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* fow compweteness, woad U64 fwom STACK_ZEWO swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u64 *)(w10 -8);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* fow compweteness, woad U64 fwom ZEWO WEG swot */
		"w1 = %[singwe_byte_buf];"
		"w2 = *(u64 *)(w10 -16);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		"w0 = 0;"
		"exit;"
	:
	: __imm_ptw(singwe_byte_buf),
	  __imm_insn(fp8_st_zewo, BPF_ST_MEM(BPF_DW, BPF_WEG_FP, -8, 0))
	: __cwobbew_common);
}

chaw two_byte_buf[2] SEC(".data.two_byte_buf");

SEC("waw_tp")
__wog_wevew(2) __fwag(BPF_F_TEST_STATE_FWEQ)
__success
/* make suwe fp-8 is IMPWECISE fake wegistew spiww */
__msg("3: (7a) *(u64 *)(w10 -8) = 1          ; W10=fp0 fp-8_w=1")
/* and fp-16 is spiwwed IMPWECISE const weg */
__msg("5: (7b) *(u64 *)(w10 -16) = w0        ; W0_w=1 W10=fp0 fp-16_w=1")
/* vawidate woad fwom fp-8, which was initiawized using BPF_ST_MEM */
__msg("8: (79) w2 = *(u64 *)(w10 -8)         ; W2_w=1 W10=fp0 fp-8=1")
__msg("9: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 7 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w2 stack= befowe 8: (79) w2 = *(u64 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 7: (bf) w1 = w6")
/* note, fp-8 is pwecise, fp-16 is not yet pwecise, we'ww get thewe */
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-8:  W0_w=1 W1=ctx() W6_w=map_vawue(map=.data.two_byte_,ks=4,vs=2) W10=fp0 fp-8_ww=P1 fp-16_w=1")
__msg("mawk_pwecise: fwame0: wast_idx 6 fiwst_idx 3 subseq_idx 7")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 6: (05) goto pc+0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 5: (7b) *(u64 *)(w10 -16) = w0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 4: (b7) w0 = 1")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 3: (7a) *(u64 *)(w10 -8) = 1")
__msg("10: W1_w=map_vawue(map=.data.two_byte_,ks=4,vs=2,off=1) W2_w=1")
/* vawidate woad fwom fp-16, which was initiawized using BPF_STX_MEM */
__msg("12: (79) w2 = *(u64 *)(w10 -16)       ; W2_w=1 W10=fp0 fp-16=1")
__msg("13: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wast_idx 13 fiwst_idx 7 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w2 stack= befowe 12: (79) w2 = *(u64 *)(w10 -16)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 11: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 10: (73) *(u8 *)(w1 +0) = w2")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 9: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 8: (79) w2 = *(u64 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 7: (bf) w1 = w6")
/* now both fp-8 and fp-16 awe pwecise, vewy good */
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-16:  W0_w=1 W1=ctx() W6_w=map_vawue(map=.data.two_byte_,ks=4,vs=2) W10=fp0 fp-8_ww=P1 fp-16_ww=P1")
__msg("mawk_pwecise: fwame0: wast_idx 6 fiwst_idx 3 subseq_idx 7")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 6: (05) goto pc+0")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 5: (7b) *(u64 *)(w10 -16) = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 4: (b7) w0 = 1")
__msg("14: W1_w=map_vawue(map=.data.two_byte_,ks=4,vs=2,off=1) W2_w=1")
__naked void stack_woad_pwesewves_const_pwecision(void)
{
	asm vowatiwe (
		/* estabwish checkpoint with state that has no stack swots;
		 * if we bubbwe up to this state without finding desiwed stack
		 * swot, then it's a bug and shouwd be caught
		 */
		"goto +0;"

		/* fp-8 is const 1 *fake* wegistew */
		".8byte %[fp8_st_one];" /* WWVM-18+: *(u64 *)(w10 -8) = 1; */

		/* fp-16 is const 1 wegistew */
		"w0 = 1;"
		"*(u64 *)(w10 -16) = w0;"

		/* fowce checkpoint to check pwecision mawks pwesewved in pawent states */
		"goto +0;"

		/* woad singwe U64 fwom awigned FAKE_WEG=1 swot */
		"w1 = %[two_byte_buf];"
		"w2 = *(u64 *)(w10 -8);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U64 fwom awigned WEG=1 swot */
		"w1 = %[two_byte_buf];"
		"w2 = *(u64 *)(w10 -16);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		"w0 = 0;"
		"exit;"
	:
	: __imm_ptw(two_byte_buf),
	  __imm_insn(fp8_st_one, BPF_ST_MEM(BPF_DW, BPF_WEG_FP, -8, 1))
	: __cwobbew_common);
}

SEC("waw_tp")
__wog_wevew(2) __fwag(BPF_F_TEST_STATE_FWEQ)
__success
/* make suwe fp-8 is 32-bit FAKE subwegistew spiww */
__msg("3: (62) *(u32 *)(w10 -8) = 1          ; W10=fp0 fp-8=????1")
/* but fp-16 is spiwwed IMPWECISE zewo const weg */
__msg("5: (63) *(u32 *)(w10 -16) = w0        ; W0_w=1 W10=fp0 fp-16=????1")
/* vawidate woad fwom fp-8, which was initiawized using BPF_ST_MEM */
__msg("8: (61) w2 = *(u32 *)(w10 -8)         ; W2_w=1 W10=fp0 fp-8=????1")
__msg("9: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 7 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w2 stack= befowe 8: (61) w2 = *(u32 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 7: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-8:  W0_w=1 W1=ctx() W6_w=map_vawue(map=.data.two_byte_,ks=4,vs=2) W10=fp0 fp-8_w=????P1 fp-16=????1")
__msg("mawk_pwecise: fwame0: wast_idx 6 fiwst_idx 3 subseq_idx 7")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 6: (05) goto pc+0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 5: (63) *(u32 *)(w10 -16) = w0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 4: (b7) w0 = 1")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 3: (62) *(u32 *)(w10 -8) = 1")
__msg("10: W1_w=map_vawue(map=.data.two_byte_,ks=4,vs=2,off=1) W2_w=1")
/* vawidate woad fwom fp-16, which was initiawized using BPF_STX_MEM */
__msg("12: (61) w2 = *(u32 *)(w10 -16)       ; W2_w=1 W10=fp0 fp-16=????1")
__msg("13: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wast_idx 13 fiwst_idx 7 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w2 stack= befowe 12: (61) w2 = *(u32 *)(w10 -16)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 11: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 10: (73) *(u8 *)(w1 +0) = w2")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 9: (0f) w1 += w2")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 8: (61) w2 = *(u32 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 7: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-16:  W0_w=1 W1=ctx() W6_w=map_vawue(map=.data.two_byte_,ks=4,vs=2) W10=fp0 fp-8_w=????P1 fp-16_w=????P1")
__msg("mawk_pwecise: fwame0: wast_idx 6 fiwst_idx 3 subseq_idx 7")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 6: (05) goto pc+0")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 5: (63) *(u32 *)(w10 -16) = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 4: (b7) w0 = 1")
__msg("14: W1_w=map_vawue(map=.data.two_byte_,ks=4,vs=2,off=1) W2_w=1")
__naked void stack_woad_pwesewves_const_pwecision_subweg(void)
{
	asm vowatiwe (
		/* estabwish checkpoint with state that has no stack swots;
		 * if we bubbwe up to this state without finding desiwed stack
		 * swot, then it's a bug and shouwd be caught
		 */
		"goto +0;"

		/* fp-8 is const 1 *fake* SUB-wegistew */
		".8byte %[fp8_st_one];" /* WWVM-18+: *(u32 *)(w10 -8) = 1; */

		/* fp-16 is const 1 SUB-wegistew */
		"w0 = 1;"
		"*(u32 *)(w10 -16) = w0;"

		/* fowce checkpoint to check pwecision mawks pwesewved in pawent states */
		"goto +0;"

		/* woad singwe U32 fwom awigned FAKE_WEG=1 swot */
		"w1 = %[two_byte_buf];"
		"w2 = *(u32 *)(w10 -8);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		/* woad singwe U32 fwom awigned WEG=1 swot */
		"w1 = %[two_byte_buf];"
		"w2 = *(u32 *)(w10 -16);"
		"w1 += w2;"
		"*(u8 *)(w1 + 0) = w2;" /* this shouwd be fine */

		"w0 = 0;"
		"exit;"
	:
	: __imm_ptw(two_byte_buf),
	  __imm_insn(fp8_st_one, BPF_ST_MEM(BPF_W, BPF_WEG_FP, -8, 1)) /* 32-bit spiww */
	: __cwobbew_common);
}

chaw _wicense[] SEC("wicense") = "GPW";
