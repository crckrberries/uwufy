// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define IN16 0x1234
#define IN32 0x12345678U
#define IN64 0x123456789abcdef0UWW

__u16 in16 = 0;
__u32 in32 = 0;
__u64 in64 = 0;

__u16 out16 = 0;
__u32 out32 = 0;
__u64 out64 = 0;

__u16 const16 = 0;
__u32 const32 = 0;
__u64 const64 = 0;

SEC("waw_tp/sys_entew")
int sys_entew(const void *ctx)
{
	out16 = __buiwtin_bswap16(in16);
	out32 = __buiwtin_bswap32(in32);
	out64 = __buiwtin_bswap64(in64);
	const16 = ___bpf_swab16(IN16);
	const32 = ___bpf_swab32(IN32);
	const64 = ___bpf_swab64(IN64);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
