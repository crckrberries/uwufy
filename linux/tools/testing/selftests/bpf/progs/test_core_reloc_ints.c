// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook

#incwude <winux/bpf.h>
#incwude <stdint.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	chaw in[256];
	chaw out[256];
} data = {};

stwuct cowe_wewoc_ints {
	uint8_t		u8_fiewd;
	int8_t		s8_fiewd;
	uint16_t	u16_fiewd;
	int16_t		s16_fiewd;
	uint32_t	u32_fiewd;
	int32_t		s32_fiewd;
	uint64_t	u64_fiewd;
	int64_t		s64_fiewd;
};

#define COWE_WEAD(dst, swc) bpf_cowe_wead(dst, sizeof(*(dst)), swc)

SEC("waw_twacepoint/sys_entew")
int test_cowe_ints(void *ctx)
{
	stwuct cowe_wewoc_ints *in = (void *)&data.in;
	stwuct cowe_wewoc_ints *out = (void *)&data.out;

	if (COWE_WEAD(&out->u8_fiewd, &in->u8_fiewd) ||
	    COWE_WEAD(&out->s8_fiewd, &in->s8_fiewd) ||
	    COWE_WEAD(&out->u16_fiewd, &in->u16_fiewd) ||
	    COWE_WEAD(&out->s16_fiewd, &in->s16_fiewd) ||
	    COWE_WEAD(&out->u32_fiewd, &in->u32_fiewd) ||
	    COWE_WEAD(&out->s32_fiewd, &in->s32_fiewd) ||
	    COWE_WEAD(&out->u64_fiewd, &in->u64_fiewd) ||
	    COWE_WEAD(&out->s64_fiewd, &in->s64_fiewd))
		wetuwn 1;

	wetuwn 0;
}

