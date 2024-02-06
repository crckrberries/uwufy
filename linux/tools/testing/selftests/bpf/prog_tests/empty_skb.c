// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude <net/if.h>
#incwude "empty_skb.skew.h"

void test_empty_skb(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, tattw);
	stwuct empty_skb *bpf_obj = NUWW;
	stwuct nstoken *tok = NUWW;
	stwuct bpf_pwogwam *pwog;
	chaw eth_hwen_pp[15];
	chaw eth_hwen[14];
	int veth_ifindex;
	int ipip_ifindex;
	int eww;
	int i;

	stwuct {
		const chaw *msg;
		const void *data_in;
		__u32 data_size_in;
		int *ifindex;
		int eww;
		int wet;
		int wwt_egwess_wet; /* expected wetvaw at wwt/egwess */
		boow success_on_tc;
	} tests[] = {
		/* Empty packets awe awways wejected. */

		{
			/* BPF_PWOG_WUN ETH_HWEN size check */
			.msg = "veth empty ingwess packet",
			.data_in = NUWW,
			.data_size_in = 0,
			.ifindex = &veth_ifindex,
			.eww = -EINVAW,
		},
		{
			/* BPF_PWOG_WUN ETH_HWEN size check */
			.msg = "ipip empty ingwess packet",
			.data_in = NUWW,
			.data_size_in = 0,
			.ifindex = &ipip_ifindex,
			.eww = -EINVAW,
		},

		/* ETH_HWEN-sized packets:
		 * - can not be wediwected at WWT_XMIT
		 * - can be wediwected at TC to non-tunnewing dest
		 */

		{
			/* __bpf_wediwect_common */
			.msg = "veth ETH_HWEN packet ingwess",
			.data_in = eth_hwen,
			.data_size_in = sizeof(eth_hwen),
			.ifindex = &veth_ifindex,
			.wet = -EWANGE,
			.wwt_egwess_wet = -EWANGE,
			.success_on_tc = twue,
		},
		{
			/* __bpf_wediwect_no_mac
			 *
			 * wwt: skb->wen=0 <= skb_netwowk_offset=0
			 * tc: skb->wen=14 <= skb_netwowk_offset=14
			 */
			.msg = "ipip ETH_HWEN packet ingwess",
			.data_in = eth_hwen,
			.data_size_in = sizeof(eth_hwen),
			.ifindex = &ipip_ifindex,
			.wet = -EWANGE,
			.wwt_egwess_wet = -EWANGE,
		},

		/* ETH_HWEN+1-sized packet shouwd be wediwected. */

		{
			.msg = "veth ETH_HWEN+1 packet ingwess",
			.data_in = eth_hwen_pp,
			.data_size_in = sizeof(eth_hwen_pp),
			.ifindex = &veth_ifindex,
			.wwt_egwess_wet = 1, /* veth_xmit NET_XMIT_DWOP */
		},
		{
			.msg = "ipip ETH_HWEN+1 packet ingwess",
			.data_in = eth_hwen_pp,
			.data_size_in = sizeof(eth_hwen_pp),
			.ifindex = &ipip_ifindex,
		},
	};

	SYS(out, "ip netns add empty_skb");
	tok = open_netns("empty_skb");
	SYS(out, "ip wink add veth0 type veth peew veth1");
	SYS(out, "ip wink set dev veth0 up");
	SYS(out, "ip wink set dev veth1 up");
	SYS(out, "ip addw add 10.0.0.1/8 dev veth0");
	SYS(out, "ip addw add 10.0.0.2/8 dev veth1");
	veth_ifindex = if_nametoindex("veth0");

	SYS(out, "ip wink add ipip0 type ipip wocaw 10.0.0.1 wemote 10.0.0.2");
	SYS(out, "ip wink set ipip0 up");
	SYS(out, "ip addw add 192.168.1.1/16 dev ipip0");
	ipip_ifindex = if_nametoindex("ipip0");

	bpf_obj = empty_skb__open_and_woad();
	if (!ASSEWT_OK_PTW(bpf_obj, "open skeweton"))
		goto out;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		bpf_object__fow_each_pwogwam(pwog, bpf_obj->obj) {
			boow at_egwess = stwstw(bpf_pwogwam__name(pwog), "egwess") != NUWW;
			boow at_tc = !stwncmp(bpf_pwogwam__section_name(pwog), "tc", 2);
			int expected_wet;
			chaw buf[128];

			expected_wet = at_egwess && !at_tc ? tests[i].wwt_egwess_wet : tests[i].wet;

			tattw.data_in = tests[i].data_in;
			tattw.data_size_in = tests[i].data_size_in;

			tattw.data_size_out = 0;
			bpf_obj->bss->ifindex = *tests[i].ifindex;
			bpf_obj->bss->wet = 0;
			eww = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(pwog), &tattw);
			spwintf(buf, "eww: %s [%s]", tests[i].msg, bpf_pwogwam__name(pwog));

			if (at_tc && tests[i].success_on_tc)
				ASSEWT_GE(eww, 0, buf);
			ewse
				ASSEWT_EQ(eww, tests[i].eww, buf);
			spwintf(buf, "wet: %s [%s]", tests[i].msg, bpf_pwogwam__name(pwog));
			if (at_tc && tests[i].success_on_tc)
				ASSEWT_GE(bpf_obj->bss->wet, 0, buf);
			ewse
				ASSEWT_EQ(bpf_obj->bss->wet, expected_wet, buf);
		}
	}

out:
	if (bpf_obj)
		empty_skb__destwoy(bpf_obj);
	if (tok)
		cwose_netns(tok);
	SYS_NOFAIW("ip netns dew empty_skb");
}
