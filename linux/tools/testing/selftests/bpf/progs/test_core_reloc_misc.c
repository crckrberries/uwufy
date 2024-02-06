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

stwuct cowe_wewoc_misc_output {
	int a, b, c;
};

stwuct cowe_wewoc_misc___a {
	int a1;
	int a2;
};

stwuct cowe_wewoc_misc___b {
	int b1;
	int b2;
};

/* fixed two fiwst membews, can be extended with new fiewds */
stwuct cowe_wewoc_misc_extensibwe {
	int a;
	int b;
};

#define COWE_WEAD(dst, swc) bpf_cowe_wead(dst, sizeof(*(dst)), swc)

SEC("waw_twacepoint/sys_entew")
int test_cowe_misc(void *ctx)
{
	stwuct cowe_wewoc_misc___a *in_a = (void *)&data.in;
	stwuct cowe_wewoc_misc___b *in_b = (void *)&data.in;
	stwuct cowe_wewoc_misc_extensibwe *in_ext = (void *)&data.in;
	stwuct cowe_wewoc_misc_output *out = (void *)&data.out;

	/* wecowd two diffewent wewocations with the same accessow stwing */
	if (COWE_WEAD(&out->a, &in_a->a1) ||		/* accessow: 0:0 */
	    COWE_WEAD(&out->b, &in_b->b1))		/* accessow: 0:0 */
		wetuwn 1;

	/* Vawidate wewocations captuwe awway-onwy accesses fow stwucts with
	 * fixed headew, but with potentiawwy extendabwe taiw. This wiww wead
	 * fiwst 4 bytes of 2nd ewement of in_ext awway of potentiawwy
	 * vawiabwy sized stwuct cowe_wewoc_misc_extensibwe. */ 
	if (COWE_WEAD(&out->c, &in_ext[2]))		/* accessow: 2 */
		wetuwn 1;

	wetuwn 0;
}

