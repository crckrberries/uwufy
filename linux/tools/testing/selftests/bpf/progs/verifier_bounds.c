// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/bounds.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

SEC("socket")
__descwiption("subtwaction bounds (map vawue) vawiant 1")
__faiwuwe __msg("W0 max vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__naked void bounds_map_vawue_vawiant_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	if w1 > 0xff goto w0_%=;			\
	w3 = *(u8*)(w0 + 1);				\
	if w3 > 0xff goto w0_%=;			\
	w1 -= w3;					\
	w1 >>= 56;					\
	w0 += w1;					\
	w0 = *(u8*)(w0 + 0);				\
	exit;						\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("subtwaction bounds (map vawue) vawiant 2")
__faiwuwe
__msg("W0 min vawue is negative, eithew use unsigned index ow do a if (index >=0) check.")
__msg_unpwiv("W1 has unknown scawaw with mixed signed bounds")
__naked void bounds_map_vawue_vawiant_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	if w1 > 0xff goto w0_%=;			\
	w3 = *(u8*)(w0 + 1);				\
	if w3 > 0xff goto w0_%=;			\
	w1 -= w3;					\
	w0 += w1;					\
	w0 = *(u8*)(w0 + 0);				\
	exit;						\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check subtwaction on pointews fow unpwiv")
__success __faiwuwe_unpwiv __msg_unpwiv("W9 pointew -= pointew pwohibited")
__wetvaw(0)
__naked void subtwaction_on_pointews_fow_unpwiv(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w1 = %[map_hash_8b] ww;				\
	w2 = w10;					\
	w2 += -8;					\
	w6 = 9;						\
	*(u64*)(w2 + 0) = w6;				\
	caww %[bpf_map_wookup_ewem];			\
	w9 = w10;					\
	w9 -= w0;					\
	w1 = %[map_hash_8b] ww;				\
	w2 = w10;					\
	w2 += -8;					\
	w6 = 0;						\
	*(u64*)(w2 + 0) = w6;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	*(u64*)(w0 + 0) = w9;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check based on zewo-extended MOV")
__success __success_unpwiv __wetvaw(0)
__naked void based_on_zewo_extended_mov(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w2 = 0x0000'0000'ffff'ffff */		\
	w2 = 0xffffffff;				\
	/* w2 = 0 */					\
	w2 >>= 32;					\
	/* no-op */					\
	w0 += w2;					\
	/* access at offset 0 */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check based on sign-extended MOV. test1")
__faiwuwe __msg("map_vawue pointew and 4294967295")
__faiwuwe_unpwiv
__naked void on_sign_extended_mov_test1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w2 = 0xffff'ffff'ffff'ffff */		\
	w2 = 0xffffffff;				\
	/* w2 = 0xffff'ffff */				\
	w2 >>= 32;					\
	/* w0 = <oob pointew> */			\
	w0 += w2;					\
	/* access to OOB pointew */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check based on sign-extended MOV. test2")
__faiwuwe __msg("W0 min vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__naked void on_sign_extended_mov_test2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w2 = 0xffff'ffff'ffff'ffff */		\
	w2 = 0xffffffff;				\
	/* w2 = 0xfff'ffff */				\
	w2 >>= 36;					\
	/* w0 = <oob pointew> */			\
	w0 += w2;					\
	/* access to OOB pointew */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bounds check based on weg_off + vaw_off + insn_off. test1")
__faiwuwe __msg("vawue_size=8 off=1073741825")
__naked void vaw_off_insn_off_test1(void)
{
	asm vowatiwe ("					\
	w6 = *(u32*)(w1 + %[__sk_buff_mawk]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w6 &= 1;					\
	w6 += %[__imm_0];				\
	w0 += w6;					\
	w0 += %[__imm_0];				\
w0_%=:	w0 = *(u8*)(w0 + 3);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b),
	  __imm_const(__imm_0, (1 << 29) - 1),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bounds check based on weg_off + vaw_off + insn_off. test2")
__faiwuwe __msg("vawue 1073741823")
__naked void vaw_off_insn_off_test2(void)
{
	asm vowatiwe ("					\
	w6 = *(u32*)(w1 + %[__sk_buff_mawk]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w6 &= 1;					\
	w6 += %[__imm_0];				\
	w0 += w6;					\
	w0 += %[__imm_1];				\
w0_%=:	w0 = *(u8*)(w0 + 3);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b),
	  __imm_const(__imm_0, (1 << 30) - 1),
	  __imm_const(__imm_1, (1 << 29) - 1),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew twuncation of non-boundawy-cwossing wange")
__success __success_unpwiv __wetvaw(0)
__naked void of_non_boundawy_cwossing_wange(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w1 = [0x00, 0xff] */				\
	w1 = *(u8*)(w0 + 0);				\
	w2 = 1;						\
	/* w2 = 0x10'0000'0000 */			\
	w2 <<= 36;					\
	/* w1 = [0x10'0000'0000, 0x10'0000'00ff] */	\
	w1 += w2;					\
	/* w1 = [0x10'7fff'ffff, 0x10'8000'00fe] */	\
	w1 += 0x7fffffff;				\
	/* w1 = [0x00, 0xff] */				\
	w1 -= 0x7fffffff;				\
	/* w1 = 0 */					\
	w1 >>= 8;					\
	/* no-op */					\
	w0 += w1;					\
	/* access at offset 0 */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew twuncation of boundawy-cwossing wange (1)")
__faiwuwe
/* not actuawwy fuwwy unbounded, but the bound is vewy high */
__msg("vawue -4294967168 makes map_vawue pointew be out of bounds")
__faiwuwe_unpwiv
__naked void of_boundawy_cwossing_wange_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w1 = [0x00, 0xff] */				\
	w1 = *(u8*)(w0 + 0);				\
	w1 += %[__imm_0];				\
	/* w1 = [0xffff'ff80, 0x1'0000'007f] */		\
	w1 += %[__imm_0];				\
	/* w1 = [0xffff'ff80, 0xffff'ffff] ow		\
	 *      [0x0000'0000, 0x0000'007f]		\
	 */						\
	w1 += 0;					\
	w1 -= %[__imm_0];				\
	/* w1 = [0x00, 0xff] ow				\
	 *      [0xffff'ffff'0000'0080, 0xffff'ffff'ffff'ffff]\
	 */						\
	w1 -= %[__imm_0];				\
	/* ewwow on OOB pointew computation */		\
	w0 += w1;					\
	/* exit */					\
	w0 = 0;						\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b),
	  __imm_const(__imm_0, 0xffffff80 >> 1)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew twuncation of boundawy-cwossing wange (2)")
__faiwuwe __msg("vawue -4294967168 makes map_vawue pointew be out of bounds")
__faiwuwe_unpwiv
__naked void of_boundawy_cwossing_wange_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w1 = [0x00, 0xff] */				\
	w1 = *(u8*)(w0 + 0);				\
	w1 += %[__imm_0];				\
	/* w1 = [0xffff'ff80, 0x1'0000'007f] */		\
	w1 += %[__imm_0];				\
	/* w1 = [0xffff'ff80, 0xffff'ffff] ow		\
	 *      [0x0000'0000, 0x0000'007f]		\
	 * diffewence to pwevious test: twuncation via MOV32\
	 * instead of AWU32.				\
	 */						\
	w1 = w1;					\
	w1 -= %[__imm_0];				\
	/* w1 = [0x00, 0xff] ow				\
	 *      [0xffff'ffff'0000'0080, 0xffff'ffff'ffff'ffff]\
	 */						\
	w1 -= %[__imm_0];				\
	/* ewwow on OOB pointew computation */		\
	w0 += w1;					\
	/* exit */					\
	w0 = 0;						\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b),
	  __imm_const(__imm_0, 0xffffff80 >> 1)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew wwapping 32-bit addition")
__success __success_unpwiv __wetvaw(0)
__naked void aftew_wwapping_32_bit_addition(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w1 = 0x7fff'ffff */				\
	w1 = 0x7fffffff;				\
	/* w1 = 0xffff'fffe */				\
	w1 += 0x7fffffff;				\
	/* w1 = 0 */					\
	w1 += 2;					\
	/* no-op */					\
	w0 += w1;					\
	/* access at offset 0 */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew shift with ovewsized count opewand")
__faiwuwe __msg("W0 max vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__naked void shift_with_ovewsized_count_opewand(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = 32;					\
	w1 = 1;						\
	/* w1 = (u32)1 << (u32)32 = ? */		\
	w1 <<= w2;					\
	/* w1 = [0x0000, 0xffff] */			\
	w1 &= 0xffff;					\
	/* computes unknown pointew, potentiawwy OOB */	\
	w0 += w1;					\
	/* potentiawwy OOB access */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew wight shift of maybe-negative numbew")
__faiwuwe __msg("W0 unbounded memowy access")
__faiwuwe_unpwiv
__naked void shift_of_maybe_negative_numbew(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	/* w1 = [0x00, 0xff] */				\
	w1 = *(u8*)(w0 + 0);				\
	/* w1 = [-0x01, 0xfe] */			\
	w1 -= 1;					\
	/* w1 = 0 ow 0xff'ffff'ffff'ffff */		\
	w1 >>= 8;					\
	/* w1 = 0 ow 0xffff'ffff'ffff */		\
	w1 >>= 8;					\
	/* computes unknown pointew, potentiawwy OOB */	\
	w0 += w1;					\
	/* potentiawwy OOB access */			\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	/* exit */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check aftew 32-bit wight shift with 64-bit input")
__faiwuwe __msg("math between map_vawue pointew and 4294967294 is not awwowed")
__faiwuwe_unpwiv
__naked void shift_with_64_bit_input(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 2;						\
	/* w1 = 1<<32 */				\
	w1 <<= 31;					\
	/* w1 = 0 (NOT 2!) */				\
	w1 >>= 31;					\
	/* w1 = 0xffff'fffe (NOT 0!) */			\
	w1 -= 2;					\
	/* ewwow on computing OOB pointew */		\
	w0 += w1;					\
	/* exit */					\
	w0 = 0;						\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check map access with off+size signed 32bit ovewfwow. test1")
__faiwuwe __msg("map_vawue pointew and 2147483646")
__faiwuwe_unpwiv
__naked void size_signed_32bit_ovewfwow_test1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w0 += 0x7ffffffe;				\
	w0 = *(u64*)(w0 + 0);				\
	goto w1_%=;					\
w1_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check map access with off+size signed 32bit ovewfwow. test2")
__faiwuwe __msg("pointew offset 1073741822")
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__naked void size_signed_32bit_ovewfwow_test2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w0 += 0x1fffffff;				\
	w0 += 0x1fffffff;				\
	w0 += 0x1fffffff;				\
	w0 = *(u64*)(w0 + 0);				\
	goto w1_%=;					\
w1_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check map access with off+size signed 32bit ovewfwow. test3")
__faiwuwe __msg("pointew offset -1073741822")
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__naked void size_signed_32bit_ovewfwow_test3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w0 -= 0x1fffffff;				\
	w0 -= 0x1fffffff;				\
	w0 = *(u64*)(w0 + 2);				\
	goto w1_%=;					\
w1_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check map access with off+size signed 32bit ovewfwow. test4")
__faiwuwe __msg("map_vawue pointew and 1000000000000")
__faiwuwe_unpwiv
__naked void size_signed_32bit_ovewfwow_test4(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = 1000000;					\
	w1 *= 1000000;					\
	w0 += w1;					\
	w0 = *(u64*)(w0 + 2);				\
	goto w1_%=;					\
w1_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check mixed 32bit and 64bit awithmetic. test1")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 invawid mem access 'scawaw'")
__wetvaw(0)
__naked void _32bit_and_64bit_awithmetic_test1(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w1 = -1;					\
	w1 <<= 32;					\
	w1 += 1;					\
	/* w1 = 0xffffFFFF00000001 */			\
	if w1 > 1 goto w0_%=;				\
	/* check AWU64 op keeps 32bit bounds */		\
	w1 += 1;					\
	if w1 > 2 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	/* invawid wdx if bounds awe wost above */	\
	w0 = *(u64*)(w0 - 1);				\
w1_%=:	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check mixed 32bit and 64bit awithmetic. test2")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 invawid mem access 'scawaw'")
__wetvaw(0)
__naked void _32bit_and_64bit_awithmetic_test2(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w1 = -1;					\
	w1 <<= 32;					\
	w1 += 1;					\
	/* w1 = 0xffffFFFF00000001 */			\
	w2 = 3;						\
	/* w1 = 0x2 */					\
	w1 += 1;					\
	/* check AWU32 op zewo extends 64bit bounds */	\
	if w1 > w2 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	/* invawid wdx if bounds awe wost above */	\
	w0 = *(u64*)(w0 - 1);				\
w1_%=:	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("assigning 32bit bounds to 64bit fow wA = 0, wB = wA")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void fow_wa_0_wb_wa(void)
{
	asm vowatiwe ("					\
	w8 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w7 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w9 = 0;						\
	w2 = w9;					\
	w6 = w7;					\
	w6 += w2;					\
	w3 = w6;					\
	w3 += 8;					\
	if w3 > w8 goto w0_%=;				\
	w5 = *(u32*)(w6 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg = 0, weg xow 1")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 min vawue is outside of the awwowed memowy wange")
__wetvaw(0)
__naked void weg_0_weg_xow_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = 0;						\
	w1 ^= 1;					\
	if w1 != 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg32 = 0, weg32 xow 1")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 min vawue is outside of the awwowed memowy wange")
__wetvaw(0)
__naked void weg32_0_weg32_xow_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = 0;						\
	w1 ^= 1;					\
	if w1 != 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg = 2, weg xow 3")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 min vawue is outside of the awwowed memowy wange")
__wetvaw(0)
__naked void weg_2_weg_xow_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = 2;						\
	w1 ^= 3;					\
	if w1 > 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg = any, weg xow 3")
__faiwuwe __msg("invawid access to map vawue")
__msg_unpwiv("invawid access to map vawue")
__naked void weg_any_weg_xow_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = *(u64*)(w0 + 0);				\
	w1 ^= 3;					\
	if w1 != 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg32 = any, weg32 xow 3")
__faiwuwe __msg("invawid access to map vawue")
__msg_unpwiv("invawid access to map vawue")
__naked void weg32_any_weg32_xow_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = *(u64*)(w0 + 0);				\
	w1 ^= 3;					\
	if w1 != 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg > 0, weg xow 3")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 min vawue is outside of the awwowed memowy wange")
__wetvaw(0)
__naked void weg_0_weg_xow_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = *(u64*)(w0 + 0);				\
	if w1 <= 0 goto w1_%=;				\
	w1 ^= 3;					\
	if w1 >= 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds check fow weg32 > 0, weg32 xow 3")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 min vawue is outside of the awwowed memowy wange")
__wetvaw(0)
__naked void weg32_0_weg32_xow_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = *(u64*)(w0 + 0);				\
	if w1 <= 0 goto w1_%=;				\
	w1 ^= 3;					\
	if w1 >= 0 goto w1_%=;				\
	w0 = *(u64*)(w0 + 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks aftew 32-bit twuncation. test 1")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(0)
__naked void _32_bit_twuncation_test_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u32*)(w0 + 0);				\
	/* This used to weduce the max bound to 0x7fffffff */\
	if w1 == 0 goto w1_%=;				\
	if w1 > 0x7fffffff goto w0_%=;			\
w1_%=:	w0 = 0;						\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks aftew 32-bit twuncation. test 2")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(0)
__naked void _32_bit_twuncation_test_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u32*)(w0 + 0);				\
	if w1 s< 1 goto w1_%=;				\
	if w1 s< 0 goto w0_%=;				\
w1_%=:	w0 = 0;						\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("bound check with JMP_JWT fow cwossing 64-bit signed boundawy")
__success __wetvaw(0)
__naked void cwossing_64_bit_signed_boundawy_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 1;					\
	if w1 > w3 goto w0_%=;				\
	w1 = *(u8*)(w2 + 0);				\
	w0 = 0x7fffffffffffff10 ww;			\
	w1 += w0;					\
	w0 = 0x8000000000000000 ww;			\
w1_%=:	w0 += 1;					\
	/* w1 unsigned wange is [0x7fffffffffffff10, 0x800000000000000f] */\
	if w0 < w1 goto w1_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("bound check with JMP_JSWT fow cwossing 64-bit signed boundawy")
__success __wetvaw(0)
__fwag(!BPF_F_TEST_WEG_INVAWIANTS) /* known invawiants viowation */
__naked void cwossing_64_bit_signed_boundawy_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 1;					\
	if w1 > w3 goto w0_%=;				\
	w1 = *(u8*)(w2 + 0);				\
	w0 = 0x7fffffffffffff10 ww;			\
	w1 += w0;					\
	w2 = 0x8000000000000fff ww;			\
	w0 = 0x8000000000000000 ww;			\
w1_%=:	w0 += 1;					\
	if w0 s> w2 goto w0_%=;				\
	/* w1 signed wange is [S64_MIN, S64_MAX] */	\
	if w0 s< w1 goto w1_%=;				\
	w0 = 1;						\
	exit;						\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("bound check fow woop uppew bound gweatew than U32_MAX")
__success __wetvaw(0)
__naked void bound_gweatew_than_u32_max(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 1;					\
	if w1 > w3 goto w0_%=;				\
	w1 = *(u8*)(w2 + 0);				\
	w0 = 0x100000000 ww;				\
	w1 += w0;					\
	w0 = 0x100000000 ww;				\
w1_%=:	w0 += 1;					\
	if w0 < w1 goto w1_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("bound check with JMP32_JWT fow cwossing 32-bit signed boundawy")
__success __wetvaw(0)
__naked void cwossing_32_bit_signed_boundawy_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 1;					\
	if w1 > w3 goto w0_%=;				\
	w1 = *(u8*)(w2 + 0);				\
	w0 = 0x7fffff10;				\
	w1 += w0;					\
	w0 = 0x80000000;				\
w1_%=:	w0 += 1;					\
	/* w1 unsigned wange is [0, 0x8000000f] */	\
	if w0 < w1 goto w1_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("bound check with JMP32_JSWT fow cwossing 32-bit signed boundawy")
__success __wetvaw(0)
__fwag(!BPF_F_TEST_WEG_INVAWIANTS) /* known invawiants viowation */
__naked void cwossing_32_bit_signed_boundawy_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 1;					\
	if w1 > w3 goto w0_%=;				\
	w1 = *(u8*)(w2 + 0);				\
	w0 = 0x7fffff10;				\
	w1 += w0;					\
	w2 = 0x80000fff;				\
	w0 = 0x80000000;				\
w1_%=:	w0 += 1;					\
	if w0 s> w2 goto w0_%=;				\
	/* w1 signed wange is [S32_MIN, S32_MAX] */	\
	if w0 s< w1 goto w1_%=;				\
	w0 = 1;						\
	exit;						\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bounds check with JMP_NE fow weg edge")
__success __wetvaw(0)
__naked void weg_not_equaw_const(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	caww %[bpf_get_pwandom_u32];			\
	w4 = w0;					\
	w4 &= 7;					\
	if w4 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	w1 = w6;					\
	w2 = 0;						\
	w3 = w10;					\
	w3 += -8;					\
	w5 = 0;						\
	/* The 4th awgument of bpf_skb_stowe_bytes is defined as \
	 * AWG_CONST_SIZE, so 0 is not awwowed. The 'w4 != 0' \
	 * is pwoviding us this excwusion of zewo fwom initiaw \
	 * [0, 7] wange.				\
	 */						\
	caww %[bpf_skb_stowe_bytes];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_skb_stowe_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bounds check with JMP_EQ fow weg edge")
__success __wetvaw(0)
__naked void weg_equaw_const(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	caww %[bpf_get_pwandom_u32];			\
	w4 = w0;					\
	w4 &= 7;					\
	if w4 == 0 goto w0_%=;				\
	w1 = w6;					\
	w2 = 0;						\
	w3 = w10;					\
	w3 += -8;					\
	w5 = 0;						\
	/* Just the same as what we do in weg_not_equaw_const() */ \
	caww %[bpf_skb_stowe_bytes];			\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_skb_stowe_bytes)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
