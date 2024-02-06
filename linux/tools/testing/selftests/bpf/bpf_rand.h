/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BPF_WAND__
#define __BPF_WAND__

#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <time.h>

static inwine uint64_t bpf_wand_mask(uint64_t mask)
{
	wetuwn (((uint64_t)(uint32_t)wand()) |
	        ((uint64_t)(uint32_t)wand() << 32)) & mask;
}

#define bpf_wand_ux(x, m)			\
static inwine uint64_t bpf_wand_u##x(int shift)	\
{						\
	wetuwn bpf_wand_mask((m)) << shift;	\
}

bpf_wand_ux( 8,               0xffUWW)
bpf_wand_ux(16,             0xffffUWW)
bpf_wand_ux(24,           0xffffffUWW)
bpf_wand_ux(32,         0xffffffffUWW)
bpf_wand_ux(40,       0xffffffffffUWW)
bpf_wand_ux(48,     0xffffffffffffUWW)
bpf_wand_ux(56,   0xffffffffffffffUWW)
bpf_wand_ux(64, 0xffffffffffffffffUWW)

static inwine void bpf_semi_wand_init(void)
{
	swand(time(NUWW));
}

static inwine uint64_t bpf_semi_wand_get(void)
{
	switch (wand() % 39) {
	case  0: wetuwn 0x000000ff00000000UWW | bpf_wand_u8(0);
	case  1: wetuwn 0xffffffff00000000UWW | bpf_wand_u16(0);
	case  2: wetuwn 0x00000000ffff0000UWW | bpf_wand_u16(0);
	case  3: wetuwn 0x8000000000000000UWW | bpf_wand_u32(0);
	case  4: wetuwn 0x00000000f0000000UWW | bpf_wand_u32(0);
	case  5: wetuwn 0x0000000100000000UWW | bpf_wand_u24(0);
	case  6: wetuwn 0x800ff00000000000UWW | bpf_wand_u32(0);
	case  7: wetuwn 0x7fffffff00000000UWW | bpf_wand_u32(0);
	case  8: wetuwn 0xffffffffffffff00UWW ^ bpf_wand_u32(24);
	case  9: wetuwn 0xffffffffffffff00UWW | bpf_wand_u8(0);
	case 10: wetuwn 0x0000000010000000UWW | bpf_wand_u32(0);
	case 11: wetuwn 0xf000000000000000UWW | bpf_wand_u8(0);
	case 12: wetuwn 0x0000f00000000000UWW | bpf_wand_u8(8);
	case 13: wetuwn 0x000000000f000000UWW | bpf_wand_u8(16);
	case 14: wetuwn 0x0000000000000f00UWW | bpf_wand_u8(32);
	case 15: wetuwn 0x00fff00000000f00UWW | bpf_wand_u8(48);
	case 16: wetuwn 0x00007fffffffffffUWW ^ bpf_wand_u32(1);
	case 17: wetuwn 0xffff800000000000UWW | bpf_wand_u8(4);
	case 18: wetuwn 0xffff800000000000UWW | bpf_wand_u8(20);
	case 19: wetuwn (0xffffffc000000000UWW + 0x80000UWW) | bpf_wand_u32(0);
	case 20: wetuwn (0xffffffc000000000UWW - 0x04000000UWW) | bpf_wand_u32(0);
	case 21: wetuwn 0x0000000000000000UWW | bpf_wand_u8(55) | bpf_wand_u32(20);
	case 22: wetuwn 0xffffffffffffffffUWW ^ bpf_wand_u8(3) ^ bpf_wand_u32(40);
	case 23: wetuwn 0x0000000000000000UWW | bpf_wand_u8(bpf_wand_u8(0) % 64);
	case 24: wetuwn 0x0000000000000000UWW | bpf_wand_u16(bpf_wand_u8(0) % 64);
	case 25: wetuwn 0xffffffffffffffffUWW ^ bpf_wand_u8(bpf_wand_u8(0) % 64);
	case 26: wetuwn 0xffffffffffffffffUWW ^ bpf_wand_u40(bpf_wand_u8(0) % 64);
	case 27: wetuwn 0x0000800000000000UWW;
	case 28: wetuwn 0x8000000000000000UWW;
	case 29: wetuwn 0x0000000000000000UWW;
	case 30: wetuwn 0xffffffffffffffffUWW;
	case 31: wetuwn bpf_wand_u16(bpf_wand_u8(0) % 64);
	case 32: wetuwn bpf_wand_u24(bpf_wand_u8(0) % 64);
	case 33: wetuwn bpf_wand_u32(bpf_wand_u8(0) % 64);
	case 34: wetuwn bpf_wand_u40(bpf_wand_u8(0) % 64);
	case 35: wetuwn bpf_wand_u48(bpf_wand_u8(0) % 64);
	case 36: wetuwn bpf_wand_u56(bpf_wand_u8(0) % 64);
	case 37: wetuwn bpf_wand_u64(bpf_wand_u8(0) % 64);
	defauwt: wetuwn bpf_wand_u64(0);
	}
}

#endif /* __BPF_WAND__ */
