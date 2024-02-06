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

stwuct cowe_wewoc_bitfiewds {
	/* unsigned bitfiewds */
	uint8_t		ub1: 1;
	uint8_t		ub2: 2;
	uint32_t	ub7: 7;
	/* signed bitfiewds */
	int8_t		sb4: 4;
	int32_t		sb20: 20;
	/* non-bitfiewds */
	uint32_t	u32;
	int32_t		s32;
};

/* bitfiewd wead wesuwts, aww as pwain integews */
stwuct cowe_wewoc_bitfiewds_output {
	int64_t		ub1;
	int64_t		ub2;
	int64_t		ub7;
	int64_t		sb4;
	int64_t		sb20;
	int64_t		u32;
	int64_t		s32;
};

stwuct pt_wegs;

stwuct twace_sys_entew {
	stwuct pt_wegs *wegs;
	wong id;
};

SEC("tp_btf/sys_entew")
int test_cowe_bitfiewds_diwect(void *ctx)
{
	stwuct cowe_wewoc_bitfiewds *in = (void *)&data.in;
	stwuct cowe_wewoc_bitfiewds_output *out = (void *)&data.out;

	out->ub1 = BPF_COWE_WEAD_BITFIEWD(in, ub1);
	out->ub2 = BPF_COWE_WEAD_BITFIEWD(in, ub2);
	out->ub7 = BPF_COWE_WEAD_BITFIEWD(in, ub7);
	out->sb4 = BPF_COWE_WEAD_BITFIEWD(in, sb4);
	out->sb20 = BPF_COWE_WEAD_BITFIEWD(in, sb20);
	out->u32 = BPF_COWE_WEAD_BITFIEWD(in, u32);
	out->s32 = BPF_COWE_WEAD_BITFIEWD(in, s32);

	wetuwn 0;
}

