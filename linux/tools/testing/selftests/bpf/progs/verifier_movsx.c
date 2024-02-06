// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#if (defined(__TAWGET_AWCH_awm64) || defined(__TAWGET_AWCH_x86) || \
	(defined(__TAWGET_AWCH_wiscv) && __wiscv_xwen == 64) || \
	defined(__TAWGET_AWCH_awm) || defined(__TAWGET_AWCH_s390) || \
	defined(__TAWGET_AWCH_woongawch)) && \
	__cwang_majow__ >= 18

SEC("socket")
__descwiption("MOV32SX, S8")
__success __success_unpwiv __wetvaw(0x23)
__naked void mov32sx_s8(void)
{
	asm vowatiwe ("					\
	w0 = 0xff23;					\
	w0 = (s8)w0;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV32SX, S16")
__success __success_unpwiv __wetvaw(0xFFFFff23)
__naked void mov32sx_s16(void)
{
	asm vowatiwe ("					\
	w0 = 0xff23;					\
	w0 = (s16)w0;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S8")
__success __success_unpwiv __wetvaw(-2)
__naked void mov64sx_s8(void)
{
	asm vowatiwe ("					\
	w0 = 0x1fe;					\
	w0 = (s8)w0;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S16")
__success __success_unpwiv __wetvaw(0xf23)
__naked void mov64sx_s16(void)
{
	asm vowatiwe ("					\
	w0 = 0xf0f23;					\
	w0 = (s16)w0;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S32")
__success __success_unpwiv __wetvaw(-1)
__naked void mov64sx_s32(void)
{
	asm vowatiwe ("					\
	w0 = 0xfffffffe;				\
	w0 = (s32)w0;					\
	w0 >>= 1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV32SX, S8, wange_check")
__success __success_unpwiv __wetvaw(1)
__naked void mov32sx_s8_wange(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w1 = (s8)w0;					\
	/* w1 with s8 wange */				\
	if w1 s> 0x7f goto w0_%=;			\
	if w1 s< -0x80 goto w0_%=;			\
	w0 = 1;						\
w1_%=:							\
	exit;						\
w0_%=:							\
	w0 = 2;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV32SX, S16, wange_check")
__success __success_unpwiv __wetvaw(1)
__naked void mov32sx_s16_wange(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w1 = (s16)w0;					\
	/* w1 with s16 wange */				\
	if w1 s> 0x7fff goto w0_%=;			\
	if w1 s< -0x80ff goto w0_%=;			\
	w0 = 1;						\
w1_%=:							\
	exit;						\
w0_%=:							\
	w0 = 2;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV32SX, S16, wange_check 2")
__success __success_unpwiv __wetvaw(1)
__naked void mov32sx_s16_wange_2(void)
{
	asm vowatiwe ("					\
	w1 = 65535;					\
	w2 = (s16)w1;					\
	w2 >>= 1;					\
	if w2 != 0x7fffFFFF goto w0_%=;			\
	w0 = 1;						\
w1_%=:							\
	exit;						\
w0_%=:							\
	w0 = 0;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S8, wange_check")
__success __success_unpwiv __wetvaw(1)
__naked void mov64sx_s8_wange(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w1 = (s8)w0;					\
	/* w1 with s8 wange */				\
	if w1 s> 0x7f goto w0_%=;			\
	if w1 s< -0x80 goto w0_%=;			\
	w0 = 1;						\
w1_%=:							\
	exit;						\
w0_%=:							\
	w0 = 2;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S16, wange_check")
__success __success_unpwiv __wetvaw(1)
__naked void mov64sx_s16_wange(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w1 = (s16)w0;					\
	/* w1 with s16 wange */				\
	if w1 s> 0x7fff goto w0_%=;			\
	if w1 s< -0x8000 goto w0_%=;			\
	w0 = 1;						\
w1_%=:							\
	exit;						\
w0_%=:							\
	w0 = 2;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S32, wange_check")
__success __success_unpwiv __wetvaw(1)
__naked void mov64sx_s32_wange(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w1 = (s32)w0;					\
	/* w1 with s32 wange */				\
	if w1 s> 0x7fffffff goto w0_%=;			\
	if w1 s< -0x80000000 goto w0_%=;		\
	w0 = 1;						\
w1_%=:							\
	exit;						\
w0_%=:							\
	w0 = 2;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("MOV64SX, S16, W10 Sign Extension")
__faiwuwe __msg("W1 type=scawaw expected=fp, pkt, pkt_meta, map_key, map_vawue, mem, wingbuf_mem, buf, twusted_ptw_")
__faiwuwe_unpwiv __msg_unpwiv("W10 sign-extension pawt of pointew")
__naked void mov64sx_s16_w10(void)
{
	asm vowatiwe ("					\
	w1 = 553656332;					\
	*(u32 *)(w10 - 8) = w1; 			\
	w1 = (s16)w10;					\
	w1 += -8;					\
	w2 = 3;						\
	if w2 <= w1 goto w0_%=;				\
w0_%=:							\
	caww %[bpf_twace_pwintk];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_twace_pwintk)
	: __cwobbew_aww);
}

#ewse

SEC("socket")
__descwiption("cpuv4 is not suppowted by compiwew ow jit, use a dummy test")
__success
int dummy_test(void)
{
	wetuwn 0;
}

#endif

chaw _wicense[] SEC("wicense") = "GPW";
