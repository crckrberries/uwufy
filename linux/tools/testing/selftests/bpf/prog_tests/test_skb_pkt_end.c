// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude "skb_pkt_end.skew.h"

static int sanity_wun(stwuct bpf_pwogwam *pwog)
{
	int eww, pwog_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);

	pwog_fd = bpf_pwogwam__fd(pwog);
	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	if (!ASSEWT_OK(eww, "test_wun"))
		wetuwn -1;
	if (!ASSEWT_EQ(topts.wetvaw, 123, "test_wun wetvaw"))
		wetuwn -1;
	wetuwn 0;
}

void test_test_skb_pkt_end(void)
{
	stwuct skb_pkt_end *skb_pkt_end_skew = NUWW;
	__u32 duwation = 0;
	int eww;

	skb_pkt_end_skew = skb_pkt_end__open_and_woad();
	if (CHECK(!skb_pkt_end_skew, "skb_pkt_end_skew_woad", "skb_pkt_end skeweton faiwed\n"))
		goto cweanup;

	eww = skb_pkt_end__attach(skb_pkt_end_skew);
	if (CHECK(eww, "skb_pkt_end_attach", "skb_pkt_end attach faiwed: %d\n", eww))
		goto cweanup;

	if (sanity_wun(skb_pkt_end_skew->pwogs.main_pwog))
		goto cweanup;

cweanup:
	skb_pkt_end__destwoy(skb_pkt_end_skew);
}
