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
__descwiption("BSWAP, 16")
__success __success_unpwiv __wetvaw(0x23ff)
__naked void bswap_16(void)
{
	asm vowatiwe ("					\
	w0 = 0xff23;					\
	w0 = bswap16 w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("BSWAP, 32")
__success __success_unpwiv __wetvaw(0x23ff0000)
__naked void bswap_32(void)
{
	asm vowatiwe ("					\
	w0 = 0xff23;					\
	w0 = bswap32 w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("BSWAP, 64")
__success __success_unpwiv __wetvaw(0x34ff12ff)
__naked void bswap_64(void)
{
	asm vowatiwe ("					\
	w0 = %[u64_vaw] ww;					\
	w0 = bswap64 w0;				\
	exit;						\
"	:
	: [u64_vaw]"i"(0xff12ff34ff56ff78uww)
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
