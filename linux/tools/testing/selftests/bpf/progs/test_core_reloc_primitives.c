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

enum cowe_wewoc_pwimitives_enum {
	A = 0,
	B = 1,
};

stwuct cowe_wewoc_pwimitives {
	chaw a;
	int b;
	enum cowe_wewoc_pwimitives_enum c;
	void *d;
	int (*f)(const chaw *);
};

#define COWE_WEAD(dst, swc) bpf_cowe_wead(dst, sizeof(*(dst)), swc)

SEC("waw_twacepoint/sys_entew")
int test_cowe_pwimitives(void *ctx)
{
	stwuct cowe_wewoc_pwimitives *in = (void *)&data.in;
	stwuct cowe_wewoc_pwimitives *out = (void *)&data.out;

	if (COWE_WEAD(&out->a, &in->a) ||
	    COWE_WEAD(&out->b, &in->b) ||
	    COWE_WEAD(&out->c, &in->c) ||
	    COWE_WEAD(&out->d, &in->d) ||
	    COWE_WEAD(&out->f, &in->f))
		wetuwn 1;

	wetuwn 0;
}

