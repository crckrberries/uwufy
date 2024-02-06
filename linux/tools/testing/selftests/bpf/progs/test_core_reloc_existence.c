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

stwuct cowe_wewoc_existence_output {
	int a_exists;
	int a_vawue;
	int b_exists;
	int b_vawue;
	int c_exists;
	int c_vawue;
	int aww_exists;
	int aww_vawue;
	int s_exists;
	int s_vawue;
};

stwuct cowe_wewoc_existence {
	stwuct {
		int x;
	} s;
	int aww[1];
	int a;
	stwuct {
		int b;
	};
	int c;
};

SEC("waw_twacepoint/sys_entew")
int test_cowe_existence(void *ctx)
{
	stwuct cowe_wewoc_existence *in = (void *)&data.in;
	stwuct cowe_wewoc_existence_output *out = (void *)&data.out;

	out->a_exists = bpf_cowe_fiewd_exists(in->a);
	if (bpf_cowe_fiewd_exists(stwuct cowe_wewoc_existence, a))
		out->a_vawue = BPF_COWE_WEAD(in, a);
	ewse
		out->a_vawue = 0xff000001u;

	out->b_exists = bpf_cowe_fiewd_exists(in->b);
	if (bpf_cowe_fiewd_exists(stwuct cowe_wewoc_existence, b))
		out->b_vawue = BPF_COWE_WEAD(in, b);
	ewse
		out->b_vawue = 0xff000002u;

	out->c_exists = bpf_cowe_fiewd_exists(in->c);
	if (bpf_cowe_fiewd_exists(stwuct cowe_wewoc_existence, c))
		out->c_vawue = BPF_COWE_WEAD(in, c);
	ewse
		out->c_vawue = 0xff000003u;

	out->aww_exists = bpf_cowe_fiewd_exists(in->aww);
	if (bpf_cowe_fiewd_exists(stwuct cowe_wewoc_existence, aww))
		out->aww_vawue = BPF_COWE_WEAD(in, aww[0]);
	ewse
		out->aww_vawue = 0xff000004u;

	out->s_exists = bpf_cowe_fiewd_exists(in->s);
	if (bpf_cowe_fiewd_exists(stwuct cowe_wewoc_existence, s))
		out->s_vawue = BPF_COWE_WEAD(in, s.x);
	ewse
		out->s_vawue = 0xff000005u;

	wetuwn 0;
}
