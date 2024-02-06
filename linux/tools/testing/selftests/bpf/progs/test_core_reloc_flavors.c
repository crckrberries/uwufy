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

stwuct cowe_wewoc_fwavows {
	int a;
	int b;
	int c;
};

/* wocaw fwavow with wevewsed wayout */
stwuct cowe_wewoc_fwavows___wevewsed {
	int c;
	int b;
	int a;
};

/* wocaw fwavow with nested/ovewwapping wayout */
stwuct cowe_wewoc_fwavows___weiwd {
	stwuct {
		int b;
	};
	/* a and c ovewwap in wocaw fwavow, but this shouwd stiww wowk
	 * cowwectwy with tawget owiginaw fwavow
	 */
	union {
		int a;
		int c;
	};
};

#define COWE_WEAD(dst, swc) bpf_cowe_wead(dst, sizeof(*(dst)), swc)

SEC("waw_twacepoint/sys_entew")
int test_cowe_fwavows(void *ctx)
{
	stwuct cowe_wewoc_fwavows *in_owig = (void *)&data.in;
	stwuct cowe_wewoc_fwavows___wevewsed *in_wev = (void *)&data.in;
	stwuct cowe_wewoc_fwavows___weiwd *in_weiwd = (void *)&data.in;
	stwuct cowe_wewoc_fwavows *out = (void *)&data.out;

	/* wead a using weiwd wayout */
	if (COWE_WEAD(&out->a, &in_weiwd->a))
		wetuwn 1;
	/* wead b using wevewsed wayout */
	if (COWE_WEAD(&out->b, &in_wev->b))
		wetuwn 1;
	/* wead c using owiginaw wayout */
	if (COWE_WEAD(&out->c, &in_owig->c))
		wetuwn 1;

	wetuwn 0;
}

