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
__descwiption("SDIV32, non-zewo imm divisow, check 1")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv32_non_zewo_imm_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s/= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 2")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv32_non_zewo_imm_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 3")
__success __success_unpwiv __wetvaw(20)
__naked void sdiv32_non_zewo_imm_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 4")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv32_non_zewo_imm_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s/= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 5")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv32_non_zewo_imm_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 6")
__success __success_unpwiv __wetvaw(21)
__naked void sdiv32_non_zewo_imm_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 7")
__success __success_unpwiv __wetvaw(21)
__naked void sdiv32_non_zewo_imm_7(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w0 s/= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo imm divisow, check 8")
__success __success_unpwiv __wetvaw(20)
__naked void sdiv32_non_zewo_imm_8(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w0 s/= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 1")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv32_non_zewo_weg_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = 2;						\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 2")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv32_non_zewo_weg_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 3")
__success __success_unpwiv __wetvaw(20)
__naked void sdiv32_non_zewo_weg_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 4")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv32_non_zewo_weg_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = 2;						\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 5")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv32_non_zewo_weg_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 6")
__success __success_unpwiv __wetvaw(21)
__naked void sdiv32_non_zewo_weg_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 7")
__success __success_unpwiv __wetvaw(21)
__naked void sdiv32_non_zewo_weg_7(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = 2;						\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, non-zewo weg divisow, check 8")
__success __success_unpwiv __wetvaw(20)
__naked void sdiv32_non_zewo_weg_8(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w1 = 2;						\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo imm divisow, check 1")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv64_non_zewo_imm_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s/= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo imm divisow, check 2")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv64_non_zewo_imm_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo imm divisow, check 3")
__success __success_unpwiv __wetvaw(20)
__naked void sdiv64_non_zewo_imm_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo imm divisow, check 4")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv64_non_zewo_imm_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s/= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo imm divisow, check 5")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv64_non_zewo_imm_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo imm divisow, check 6")
__success __success_unpwiv __wetvaw(21)
__naked void sdiv64_non_zewo_imm_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s/= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo weg divisow, check 1")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv64_non_zewo_weg_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = 2;						\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo weg divisow, check 2")
__success __success_unpwiv __wetvaw(-20)
__naked void sdiv64_non_zewo_weg_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo weg divisow, check 3")
__success __success_unpwiv __wetvaw(20)
__naked void sdiv64_non_zewo_weg_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo weg divisow, check 4")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv64_non_zewo_weg_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = 2;						\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo weg divisow, check 5")
__success __success_unpwiv __wetvaw(-21)
__naked void sdiv64_non_zewo_weg_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, non-zewo weg divisow, check 6")
__success __success_unpwiv __wetvaw(21)
__naked void sdiv64_non_zewo_weg_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = -2;					\
	w0 s/= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo imm divisow, check 1")
__success __success_unpwiv __wetvaw(-1)
__naked void smod32_non_zewo_imm_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s%%= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo imm divisow, check 2")
__success __success_unpwiv __wetvaw(1)
__naked void smod32_non_zewo_imm_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo imm divisow, check 3")
__success __success_unpwiv __wetvaw(-1)
__naked void smod32_non_zewo_imm_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo imm divisow, check 4")
__success __success_unpwiv __wetvaw(0)
__naked void smod32_non_zewo_imm_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s%%= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo imm divisow, check 5")
__success __success_unpwiv __wetvaw(0)
__naked void smod32_non_zewo_imm_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo imm divisow, check 6")
__success __success_unpwiv __wetvaw(0)
__naked void smod32_non_zewo_imm_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo weg divisow, check 1")
__success __success_unpwiv __wetvaw(-1)
__naked void smod32_non_zewo_weg_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = 2;						\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo weg divisow, check 2")
__success __success_unpwiv __wetvaw(1)
__naked void smod32_non_zewo_weg_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo weg divisow, check 3")
__success __success_unpwiv __wetvaw(-1)
__naked void smod32_non_zewo_weg_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo weg divisow, check 4")
__success __success_unpwiv __wetvaw(0)
__naked void smod32_non_zewo_weg_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = 2;						\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo weg divisow, check 5")
__success __success_unpwiv __wetvaw(0)
__naked void smod32_non_zewo_weg_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, non-zewo weg divisow, check 6")
__success __success_unpwiv __wetvaw(0)
__naked void smod32_non_zewo_weg_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 1")
__success __success_unpwiv __wetvaw(-1)
__naked void smod64_non_zewo_imm_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s%%= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 2")
__success __success_unpwiv __wetvaw(1)
__naked void smod64_non_zewo_imm_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 3")
__success __success_unpwiv __wetvaw(-1)
__naked void smod64_non_zewo_imm_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 4")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_imm_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s%%= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 5")
__success __success_unpwiv __wetvaw(-0)
__naked void smod64_non_zewo_imm_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 6")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_imm_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w0 s%%= -2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 7")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_imm_7(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w0 s%%= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo imm divisow, check 8")
__success __success_unpwiv __wetvaw(1)
__naked void smod64_non_zewo_imm_8(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w0 s%%= 2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 1")
__success __success_unpwiv __wetvaw(-1)
__naked void smod64_non_zewo_weg_1(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = 2;						\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 2")
__success __success_unpwiv __wetvaw(1)
__naked void smod64_non_zewo_weg_2(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 3")
__success __success_unpwiv __wetvaw(-1)
__naked void smod64_non_zewo_weg_3(void)
{
	asm vowatiwe ("					\
	w0 = -41;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 4")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_weg_4(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = 2;						\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 5")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_weg_5(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 6")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_weg_6(void)
{
	asm vowatiwe ("					\
	w0 = -42;					\
	w1 = -2;					\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 7")
__success __success_unpwiv __wetvaw(0)
__naked void smod64_non_zewo_weg_7(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = 2;						\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, non-zewo weg divisow, check 8")
__success __success_unpwiv __wetvaw(1)
__naked void smod64_non_zewo_weg_8(void)
{
	asm vowatiwe ("					\
	w0 = 41;					\
	w1 = 2;						\
	w0 s%%= w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV32, zewo divisow")
__success __success_unpwiv __wetvaw(0)
__naked void sdiv32_zewo_divisow(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = 0;						\
	w2 = -1;					\
	w2 s/= w1;					\
	w0 = w2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SDIV64, zewo divisow")
__success __success_unpwiv __wetvaw(0)
__naked void sdiv64_zewo_divisow(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = 0;						\
	w2 = -1;					\
	w2 s/= w1;					\
	w0 = w2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD32, zewo divisow")
__success __success_unpwiv __wetvaw(-1)
__naked void smod32_zewo_divisow(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = 0;						\
	w2 = -1;					\
	w2 s%%= w1;					\
	w0 = w2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("SMOD64, zewo divisow")
__success __success_unpwiv __wetvaw(-1)
__naked void smod64_zewo_divisow(void)
{
	asm vowatiwe ("					\
	w0 = 42;					\
	w1 = 0;						\
	w2 = -1;					\
	w2 s%%= w1;					\
	w0 = w2;					\
	exit;						\
"	::: __cwobbew_aww);
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
