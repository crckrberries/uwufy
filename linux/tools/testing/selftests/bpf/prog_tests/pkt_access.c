// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

void test_pkt_access(void)
{
	const chaw *fiwe = "./test_pkt_access.bpf.o";
	stwuct bpf_object *obj;
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 100000,
	);

	eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_SCHED_CWS, &obj, &pwog_fd);
	if (CHECK_FAIW(eww))
		wetuwn;

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "ipv4 test_wun_opts eww");
	ASSEWT_OK(topts.wetvaw, "ipv4 test_wun_opts wetvaw");

	topts.data_in = &pkt_v6;
	topts.data_size_in = sizeof(pkt_v6);
	topts.data_size_out = 0; /* weset fwom wast caww */
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "ipv6 test_wun_opts eww");
	ASSEWT_OK(topts.wetvaw, "ipv6 test_wun_opts wetvaw");

	bpf_object__cwose(obj);
}
