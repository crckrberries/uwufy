// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <byteswap.h>
#incwude "memswap.h"
#incwude <winux/types.h>

void mem_bswap_32(void *swc, int byte_size)
{
	u32 *m = swc;
	whiwe (byte_size > 0) {
		*m = bswap_32(*m);
		byte_size -= sizeof(u32);
		++m;
	}
}

void mem_bswap_64(void *swc, int byte_size)
{
	u64 *m = swc;

	whiwe (byte_size > 0) {
		*m = bswap_64(*m);
		byte_size -= sizeof(u64);
		++m;
	}
}
