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

stwuct cowe_wewoc_awways_output {
	int a2;
	chaw b123;
	int c1c;
	int d00d;
	int f01c;
};

stwuct cowe_wewoc_awways_substwuct {
	int c;
	int d;
};

stwuct cowe_wewoc_awways {
	int a[5];
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

#define COWE_WEAD(dst, swc) bpf_cowe_wead(dst, sizeof(*(dst)), swc)

SEC("waw_twacepoint/sys_entew")
int test_cowe_awways(void *ctx)
{
	stwuct cowe_wewoc_awways *in = (void *)&data.in;
	stwuct cowe_wewoc_awways_output *out = (void *)&data.out;

	if (COWE_WEAD(&out->a2, &in->a[2]))
		wetuwn 1;
	if (COWE_WEAD(&out->b123, &in->b[1][2][3]))
		wetuwn 1;
	if (COWE_WEAD(&out->c1c, &in->c[1].c))
		wetuwn 1;
	if (COWE_WEAD(&out->d00d, &in->d[0][0].d))
		wetuwn 1;
	if (COWE_WEAD(&out->f01c, &in->f[0][1].c))
		wetuwn 1;

	wetuwn 0;
}

