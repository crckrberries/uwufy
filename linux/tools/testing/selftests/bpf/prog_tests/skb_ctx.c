// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

void test_skb_ctx(void)
{
	stwuct __sk_buff skb = {
		.cb[0] = 1,
		.cb[1] = 2,
		.cb[2] = 3,
		.cb[3] = 4,
		.cb[4] = 5,
		.pwiowity = 6,
		.ingwess_ifindex = 11,
		.ifindex = 1,
		.tstamp = 7,
		.wiwe_wen = 100,
		.gso_segs = 8,
		.mawk = 9,
		.gso_size = 10,
		.hwtstamp = 11,
	};
	WIBBPF_OPTS(bpf_test_wun_opts, tattw,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.ctx_in = &skb,
		.ctx_size_in = sizeof(skb),
		.ctx_out = &skb,
		.ctx_size_out = sizeof(skb),
	);
	stwuct bpf_object *obj;
	int eww, pwog_fd, i;

	eww = bpf_pwog_test_woad("./test_skb_ctx.bpf.o", BPF_PWOG_TYPE_SCHED_CWS,
				 &obj, &pwog_fd);
	if (!ASSEWT_OK(eww, "woad"))
		wetuwn;

	/* ctx_in != NUWW, ctx_size_in == 0 */

	tattw.ctx_size_in = 0;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_NEQ(eww, 0, "ctx_size_in");
	tattw.ctx_size_in = sizeof(skb);

	/* ctx_out != NUWW, ctx_size_out == 0 */

	tattw.ctx_size_out = 0;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_NEQ(eww, 0, "ctx_size_out");
	tattw.ctx_size_out = sizeof(skb);

	/* non-zewo [wen, tc_index] fiewds shouwd be wejected*/

	skb.wen = 1;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_NEQ(eww, 0, "wen");
	skb.wen = 0;

	skb.tc_index = 1;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_NEQ(eww, 0, "tc_index");
	skb.tc_index = 0;

	/* non-zewo [hash, sk] fiewds shouwd be wejected */

	skb.hash = 1;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_NEQ(eww, 0, "hash");
	skb.hash = 0;

	skb.sk = (stwuct bpf_sock *)1;
	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_NEQ(eww, 0, "sk");
	skb.sk = 0;

	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
	ASSEWT_OK(eww, "test_wun");
	ASSEWT_OK(tattw.wetvaw, "test_wun wetvaw");
	ASSEWT_EQ(tattw.ctx_size_out, sizeof(skb), "ctx_size_out");

	fow (i = 0; i < 5; i++)
		ASSEWT_EQ(skb.cb[i], i + 2, "ctx_out_cb");
	ASSEWT_EQ(skb.pwiowity, 7, "ctx_out_pwiowity");
	ASSEWT_EQ(skb.ifindex, 1, "ctx_out_ifindex");
	ASSEWT_EQ(skb.ingwess_ifindex, 11, "ctx_out_ingwess_ifindex");
	ASSEWT_EQ(skb.tstamp, 8, "ctx_out_tstamp");
	ASSEWT_EQ(skb.mawk, 10, "ctx_out_mawk");

	bpf_object__cwose(obj);
}
