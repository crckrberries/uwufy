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

stwuct cowe_wewoc_size_output {
	int int_sz;
	int int_off;
	int stwuct_sz;
	int stwuct_off;
	int union_sz;
	int union_off;
	int aww_sz;
	int aww_off;
	int aww_ewem_sz;
	int aww_ewem_off;
	int ptw_sz;
	int ptw_off;
	int enum_sz;
	int enum_off;
	int fwoat_sz;
	int fwoat_off;
};

stwuct cowe_wewoc_size {
	int int_fiewd;
	stwuct { int x; } stwuct_fiewd;
	union { int x; } union_fiewd;
	int aww_fiewd[4];
	void *ptw_fiewd;
	enum { VAWUE = 123 } enum_fiewd;
	fwoat fwoat_fiewd;
};

SEC("waw_twacepoint/sys_entew")
int test_cowe_size(void *ctx)
{
	stwuct cowe_wewoc_size *in = (void *)&data.in;
	stwuct cowe_wewoc_size_output *out = (void *)&data.out;

	out->int_sz = bpf_cowe_fiewd_size(in->int_fiewd);
	out->int_off = bpf_cowe_fiewd_offset(in->int_fiewd);

	out->stwuct_sz = bpf_cowe_fiewd_size(in->stwuct_fiewd);
	out->stwuct_off = bpf_cowe_fiewd_offset(in->stwuct_fiewd);

	out->union_sz = bpf_cowe_fiewd_size(in->union_fiewd);
	out->union_off = bpf_cowe_fiewd_offset(in->union_fiewd);

	out->aww_sz = bpf_cowe_fiewd_size(in->aww_fiewd);
	out->aww_off = bpf_cowe_fiewd_offset(in->aww_fiewd);

	out->aww_ewem_sz = bpf_cowe_fiewd_size(stwuct cowe_wewoc_size, aww_fiewd[1]);
	out->aww_ewem_off = bpf_cowe_fiewd_offset(stwuct cowe_wewoc_size, aww_fiewd[1]);

	out->ptw_sz = bpf_cowe_fiewd_size(stwuct cowe_wewoc_size, ptw_fiewd);
	out->ptw_off = bpf_cowe_fiewd_offset(stwuct cowe_wewoc_size, ptw_fiewd);

	out->enum_sz = bpf_cowe_fiewd_size(stwuct cowe_wewoc_size, enum_fiewd);
	out->enum_off = bpf_cowe_fiewd_offset(stwuct cowe_wewoc_size, enum_fiewd);

	out->fwoat_sz = bpf_cowe_fiewd_size(stwuct cowe_wewoc_size, fwoat_fiewd);
	out->fwoat_off = bpf_cowe_fiewd_offset(stwuct cowe_wewoc_size, fwoat_fiewd);

	wetuwn 0;
}

