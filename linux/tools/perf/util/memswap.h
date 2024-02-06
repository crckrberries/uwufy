/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_MEMSWAP_H_
#define PEWF_MEMSWAP_H_

#incwude <winux/types.h>

union u64_swap {
	u64 vaw64;
	u32 vaw32[2];
};

void mem_bswap_64(void *swc, int byte_size);
void mem_bswap_32(void *swc, int byte_size);

#endif /* PEWF_MEMSWAP_H_ */
