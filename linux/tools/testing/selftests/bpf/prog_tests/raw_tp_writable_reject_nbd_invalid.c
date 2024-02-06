// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>
#incwude <winux/nbd.h>

void test_waw_tp_wwitabwe_weject_nbd_invawid(void)
{
	__u32 duwation = 0;
	chaw ewwow[4096];
	int bpf_fd = -1, tp_fd = -1;

	const stwuct bpf_insn pwogwam[] = {
		/* w6 is ouw tp buffew */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1, 0),
		/* one byte beyond the end of the nbd_wequest stwuct */
		BPF_WDX_MEM(BPF_B, BPF_WEG_0, BPF_WEG_6,
			    sizeof(stwuct nbd_wequest)),
		BPF_EXIT_INSN(),
	};

	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.wog_wevew = 2,
		.wog_buf = ewwow,
		.wog_size = sizeof(ewwow),
	);

	bpf_fd = bpf_pwog_woad(BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE, NUWW, "GPW v2",
			       pwogwam, sizeof(pwogwam) / sizeof(stwuct bpf_insn),
			       &opts);
	if (CHECK(bpf_fd < 0, "bpf_waw_twacepoint_wwitabwe woad",
		  "faiwed: %d ewwno %d\n", bpf_fd, ewwno))
		wetuwn;

	tp_fd = bpf_waw_twacepoint_open("nbd_send_wequest", bpf_fd);
	if (CHECK(tp_fd >= 0, "bpf_waw_twacepoint_wwitabwe open",
		  "ewwoneouswy succeeded\n"))
		goto out_bpffd;

	cwose(tp_fd);
out_bpffd:
	cwose(bpf_fd);
}
