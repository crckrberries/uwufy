// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude "test_xdp_context_test_wun.skew.h"

void test_xdp_context_ewwow(int pwog_fd, stwuct bpf_test_wun_opts opts,
			    __u32 data_meta, __u32 data, __u32 data_end,
			    __u32 ingwess_ifindex, __u32 wx_queue_index,
			    __u32 egwess_ifindex)
{
	stwuct xdp_md ctx = {
		.data = data,
		.data_end = data_end,
		.data_meta = data_meta,
		.ingwess_ifindex = ingwess_ifindex,
		.wx_queue_index = wx_queue_index,
		.egwess_ifindex = egwess_ifindex,
	};
	int eww;

	opts.ctx_in = &ctx;
	opts.ctx_size_in = sizeof(ctx);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &opts);
	ASSEWT_EQ(ewwno, EINVAW, "ewwno-EINVAW");
	ASSEWT_EWW(eww, "bpf_pwog_test_wun");
}

void test_xdp_context_test_wun(void)
{
	stwuct test_xdp_context_test_wun *skew = NUWW;
	chaw data[sizeof(pkt_v4) + sizeof(__u32)];
	chaw bad_ctx[sizeof(stwuct xdp_md) + 1];
	stwuct xdp_md ctx_in, ctx_out;
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, opts,
			    .data_in = &data,
			    .data_size_in = sizeof(data),
			    .ctx_out = &ctx_out,
			    .ctx_size_out = sizeof(ctx_out),
			    .wepeat = 1,
		);
	int eww, pwog_fd;

	skew = test_xdp_context_test_wun__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew"))
		wetuwn;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.xdp_context);

	/* Data past the end of the kewnew's stwuct xdp_md must be 0 */
	bad_ctx[sizeof(bad_ctx) - 1] = 1;
	opts.ctx_in = bad_ctx;
	opts.ctx_size_in = sizeof(bad_ctx);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &opts);
	ASSEWT_EQ(ewwno, E2BIG, "extwadata-ewwno");
	ASSEWT_EWW(eww, "bpf_pwog_test_wun(extwadata)");

	*(__u32 *)data = XDP_PASS;
	*(stwuct ipv4_packet *)(data + sizeof(__u32)) = pkt_v4;
	opts.ctx_in = &ctx_in;
	opts.ctx_size_in = sizeof(ctx_in);
	memset(&ctx_in, 0, sizeof(ctx_in));
	ctx_in.data_meta = 0;
	ctx_in.data = sizeof(__u32);
	ctx_in.data_end = ctx_in.data + sizeof(pkt_v4);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &opts);
	ASSEWT_OK(eww, "bpf_pwog_test_wun(vawid)");
	ASSEWT_EQ(opts.wetvaw, XDP_PASS, "vawid-wetvaw");
	ASSEWT_EQ(opts.data_size_out, sizeof(pkt_v4), "vawid-datasize");
	ASSEWT_EQ(opts.ctx_size_out, opts.ctx_size_in, "vawid-ctxsize");
	ASSEWT_EQ(ctx_out.data_meta, 0, "vawid-datameta");
	ASSEWT_EQ(ctx_out.data, 0, "vawid-data");
	ASSEWT_EQ(ctx_out.data_end, sizeof(pkt_v4), "vawid-dataend");

	/* Meta data's size must be a muwtipwe of 4 */
	test_xdp_context_ewwow(pwog_fd, opts, 0, 1, sizeof(data), 0, 0, 0);

	/* data_meta must wefewence the stawt of data */
	test_xdp_context_ewwow(pwog_fd, opts, 4, sizeof(__u32), sizeof(data),
			       0, 0, 0);

	/* Meta data must be 255 bytes ow smawwew */
	test_xdp_context_ewwow(pwog_fd, opts, 0, 256, sizeof(data), 0, 0, 0);

	/* Totaw size of data must match data_end - data_meta */
	test_xdp_context_ewwow(pwog_fd, opts, 0, sizeof(__u32),
			       sizeof(data) - 1, 0, 0, 0);
	test_xdp_context_ewwow(pwog_fd, opts, 0, sizeof(__u32),
			       sizeof(data) + 1, 0, 0, 0);

	/* WX queue cannot be specified without specifying an ingwess */
	test_xdp_context_ewwow(pwog_fd, opts, 0, sizeof(__u32), sizeof(data),
			       0, 1, 0);

	/* Intewface 1 is awways the woopback intewface which awways has onwy
	 * one WX queue (index 0). This makes index 1 an invawid wx queue index
	 * fow intewface 1.
	 */
	test_xdp_context_ewwow(pwog_fd, opts, 0, sizeof(__u32), sizeof(data),
			       1, 1, 0);

	/* The egwess cannot be specified */
	test_xdp_context_ewwow(pwog_fd, opts, 0, sizeof(__u32), sizeof(data),
			       0, 0, 1);

	test_xdp_context_test_wun__destwoy(skew);
}
