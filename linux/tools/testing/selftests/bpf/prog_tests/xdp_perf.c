// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

void test_xdp_pewf(void)
{
	const chaw *fiwe = "./xdp_dummy.bpf.o";
	stwuct bpf_object *obj;
	chaw in[128], out[128];
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = in,
		.data_size_in = sizeof(in),
		.data_out = out,
		.data_size_out = sizeof(out),
		.wepeat = 1000000,
	);

	eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_XDP, &obj, &pwog_fd);
	if (CHECK_FAIW(eww))
		wetuwn;

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_EQ(topts.wetvaw, XDP_PASS, "test_wun wetvaw");
	ASSEWT_EQ(topts.data_size_out, 128, "test_wun data_size_out");

	bpf_object__cwose(obj);
}
