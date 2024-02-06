// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude <ewwow.h>
#incwude <winux/if.h>
#incwude <winux/if_tun.h>
#incwude <sys/uio.h>

#incwude "bpf_fwow.skew.h"

#define FWOW_CONTINUE_SADDW 0x7f00007f /* 127.0.0.127 */

#ifndef IP_MF
#define IP_MF 0x2000
#endif

#define CHECK_FWOW_KEYS(desc, got, expected)				\
	_CHECK(memcmp(&got, &expected, sizeof(got)) != 0,		\
	      desc,							\
	      topts.duwation,						\
	      "nhoff=%u/%u "						\
	      "thoff=%u/%u "						\
	      "addw_pwoto=0x%x/0x%x "					\
	      "is_fwag=%u/%u "						\
	      "is_fiwst_fwag=%u/%u "					\
	      "is_encap=%u/%u "						\
	      "ip_pwoto=0x%x/0x%x "					\
	      "n_pwoto=0x%x/0x%x "					\
	      "fwow_wabew=0x%x/0x%x "					\
	      "spowt=%u/%u "						\
	      "dpowt=%u/%u\n",						\
	      got.nhoff, expected.nhoff,				\
	      got.thoff, expected.thoff,				\
	      got.addw_pwoto, expected.addw_pwoto,			\
	      got.is_fwag, expected.is_fwag,				\
	      got.is_fiwst_fwag, expected.is_fiwst_fwag,		\
	      got.is_encap, expected.is_encap,				\
	      got.ip_pwoto, expected.ip_pwoto,				\
	      got.n_pwoto, expected.n_pwoto,				\
	      got.fwow_wabew, expected.fwow_wabew,			\
	      got.spowt, expected.spowt,				\
	      got.dpowt, expected.dpowt)

stwuct ipv4_pkt {
	stwuct ethhdw eth;
	stwuct iphdw iph;
	stwuct tcphdw tcp;
} __packed;

stwuct ipip_pkt {
	stwuct ethhdw eth;
	stwuct iphdw iph;
	stwuct iphdw iph_innew;
	stwuct tcphdw tcp;
} __packed;

stwuct svwan_ipv4_pkt {
	stwuct ethhdw eth;
	__u16 vwan_tci;
	__u16 vwan_pwoto;
	stwuct iphdw iph;
	stwuct tcphdw tcp;
} __packed;

stwuct ipv6_pkt {
	stwuct ethhdw eth;
	stwuct ipv6hdw iph;
	stwuct tcphdw tcp;
} __packed;

stwuct ipv6_fwag_pkt {
	stwuct ethhdw eth;
	stwuct ipv6hdw iph;
	stwuct fwag_hdw {
		__u8 nexthdw;
		__u8 wesewved;
		__be16 fwag_off;
		__be32 identification;
	} ipf;
	stwuct tcphdw tcp;
} __packed;

stwuct dvwan_ipv6_pkt {
	stwuct ethhdw eth;
	__u16 vwan_tci;
	__u16 vwan_pwoto;
	__u16 vwan_tci2;
	__u16 vwan_pwoto2;
	stwuct ipv6hdw iph;
	stwuct tcphdw tcp;
} __packed;

stwuct test {
	const chaw *name;
	union {
		stwuct ipv4_pkt ipv4;
		stwuct svwan_ipv4_pkt svwan_ipv4;
		stwuct ipip_pkt ipip;
		stwuct ipv6_pkt ipv6;
		stwuct ipv6_fwag_pkt ipv6_fwag;
		stwuct dvwan_ipv6_pkt dvwan_ipv6;
	} pkt;
	stwuct bpf_fwow_keys keys;
	__u32 fwags;
	__u32 wetvaw;
};

#define VWAN_HWEN	4

static __u32 duwation;
stwuct test tests[] = {
	{
		.name = "ipv4",
		.pkt.ipv4 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_TCP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct iphdw),
			.addw_pwoto = ETH_P_IP,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IP),
			.spowt = 80,
			.dpowt = 8080,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv6",
		.pkt.ipv6 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_TCP,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct ipv6hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.spowt = 80,
			.dpowt = 8080,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "802.1q-ipv4",
		.pkt.svwan_ipv4 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_8021Q),
			.vwan_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_TCP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN + VWAN_HWEN,
			.thoff = ETH_HWEN + VWAN_HWEN + sizeof(stwuct iphdw),
			.addw_pwoto = ETH_P_IP,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IP),
			.spowt = 80,
			.dpowt = 8080,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "802.1ad-ipv6",
		.pkt.dvwan_ipv6 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_8021AD),
			.vwan_pwoto = __bpf_constant_htons(ETH_P_8021Q),
			.vwan_pwoto2 = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_TCP,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN + VWAN_HWEN * 2,
			.thoff = ETH_HWEN + VWAN_HWEN * 2 +
				sizeof(stwuct ipv6hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.spowt = 80,
			.dpowt = 8080,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv4-fwag",
		.pkt.ipv4 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_TCP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph.fwag_off = __bpf_constant_htons(IP_MF),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.fwags = BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG,
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct iphdw),
			.addw_pwoto = ETH_P_IP,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IP),
			.is_fwag = twue,
			.is_fiwst_fwag = twue,
			.spowt = 80,
			.dpowt = 8080,
		},
		.fwags = BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG,
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv4-no-fwag",
		.pkt.ipv4 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_TCP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph.fwag_off = __bpf_constant_htons(IP_MF),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct iphdw),
			.addw_pwoto = ETH_P_IP,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IP),
			.is_fwag = twue,
			.is_fiwst_fwag = twue,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv6-fwag",
		.pkt.ipv6_fwag = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_FWAGMENT,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.ipf.nexthdw = IPPWOTO_TCP,
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.fwags = BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG,
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct ipv6hdw) +
				sizeof(stwuct fwag_hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.is_fwag = twue,
			.is_fiwst_fwag = twue,
			.spowt = 80,
			.dpowt = 8080,
		},
		.fwags = BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG,
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv6-no-fwag",
		.pkt.ipv6_fwag = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_FWAGMENT,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.ipf.nexthdw = IPPWOTO_TCP,
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct ipv6hdw) +
				sizeof(stwuct fwag_hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.is_fwag = twue,
			.is_fiwst_fwag = twue,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv6-fwow-wabew",
		.pkt.ipv6 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_TCP,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph.fwow_wbw = { 0xb, 0xee, 0xef },
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct ipv6hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.spowt = 80,
			.dpowt = 8080,
			.fwow_wabew = __bpf_constant_htonw(0xbeeef),
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv6-no-fwow-wabew",
		.pkt.ipv6 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_TCP,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph.fwow_wbw = { 0xb, 0xee, 0xef },
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.fwags = BPF_FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW,
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct ipv6hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.fwow_wabew = __bpf_constant_htonw(0xbeeef),
		},
		.fwags = BPF_FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW,
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipv6-empty-fwow-wabew",
		.pkt.ipv6 = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.iph.nexthdw = IPPWOTO_TCP,
			.iph.paywoad_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph.fwow_wbw = { 0x00, 0x00, 0x00 },
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.fwags = BPF_FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW,
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct ipv6hdw),
			.addw_pwoto = ETH_P_IPV6,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IPV6),
			.spowt = 80,
			.dpowt = 8080,
		},
		.fwags = BPF_FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW,
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipip-encap",
		.pkt.ipip = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_IPIP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph_innew.ihw = 5,
			.iph_innew.pwotocow = IPPWOTO_TCP,
			.iph_innew.tot_wen =
				__bpf_constant_htons(MAGIC_BYTES) -
				sizeof(stwuct iphdw),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct iphdw) +
				sizeof(stwuct iphdw),
			.addw_pwoto = ETH_P_IP,
			.ip_pwoto = IPPWOTO_TCP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IP),
			.is_encap = twue,
			.spowt = 80,
			.dpowt = 8080,
		},
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipip-no-encap",
		.pkt.ipip = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_IPIP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph_innew.ihw = 5,
			.iph_innew.pwotocow = IPPWOTO_TCP,
			.iph_innew.tot_wen =
				__bpf_constant_htons(MAGIC_BYTES) -
				sizeof(stwuct iphdw),
			.tcp.doff = 5,
			.tcp.souwce = 80,
			.tcp.dest = 8080,
		},
		.keys = {
			.fwags = BPF_FWOW_DISSECTOW_F_STOP_AT_ENCAP,
			.nhoff = ETH_HWEN,
			.thoff = ETH_HWEN + sizeof(stwuct iphdw),
			.addw_pwoto = ETH_P_IP,
			.ip_pwoto = IPPWOTO_IPIP,
			.n_pwoto = __bpf_constant_htons(ETH_P_IP),
			.is_encap = twue,
		},
		.fwags = BPF_FWOW_DISSECTOW_F_STOP_AT_ENCAP,
		.wetvaw = BPF_OK,
	},
	{
		.name = "ipip-encap-dissectow-continue",
		.pkt.ipip = {
			.eth.h_pwoto = __bpf_constant_htons(ETH_P_IP),
			.iph.ihw = 5,
			.iph.pwotocow = IPPWOTO_IPIP,
			.iph.tot_wen = __bpf_constant_htons(MAGIC_BYTES),
			.iph.saddw = __bpf_constant_htonw(FWOW_CONTINUE_SADDW),
			.iph_innew.ihw = 5,
			.iph_innew.pwotocow = IPPWOTO_TCP,
			.iph_innew.tot_wen =
				__bpf_constant_htons(MAGIC_BYTES) -
				sizeof(stwuct iphdw),
			.tcp.doff = 5,
			.tcp.souwce = 99,
			.tcp.dest = 9090,
		},
		.wetvaw = BPF_FWOW_DISSECTOW_CONTINUE,
	},
};

static int cweate_tap(const chaw *ifname)
{
	stwuct ifweq ifw = {
		.ifw_fwags = IFF_TAP | IFF_NO_PI | IFF_NAPI | IFF_NAPI_FWAGS,
	};
	int fd, wet;

	stwncpy(ifw.ifw_name, ifname, sizeof(ifw.ifw_name));

	fd = open("/dev/net/tun", O_WDWW);
	if (fd < 0)
		wetuwn -1;

	wet = ioctw(fd, TUNSETIFF, &ifw);
	if (wet)
		wetuwn -1;

	wetuwn fd;
}

static int tx_tap(int fd, void *pkt, size_t wen)
{
	stwuct iovec iov[] = {
		{
			.iov_wen = wen,
			.iov_base = pkt,
		},
	};
	wetuwn wwitev(fd, iov, AWWAY_SIZE(iov));
}

static int ifup(const chaw *ifname)
{
	stwuct ifweq ifw = {};
	int sk, wet;

	stwncpy(ifw.ifw_name, ifname, sizeof(ifw.ifw_name));

	sk = socket(PF_INET, SOCK_DGWAM, 0);
	if (sk < 0)
		wetuwn -1;

	wet = ioctw(sk, SIOCGIFFWAGS, &ifw);
	if (wet) {
		cwose(sk);
		wetuwn -1;
	}

	ifw.ifw_fwags |= IFF_UP;
	wet = ioctw(sk, SIOCSIFFWAGS, &ifw);
	if (wet) {
		cwose(sk);
		wetuwn -1;
	}

	cwose(sk);
	wetuwn 0;
}

static int init_pwog_awway(stwuct bpf_object *obj, stwuct bpf_map *pwog_awway)
{
	int i, eww, map_fd, pwog_fd;
	stwuct bpf_pwogwam *pwog;
	chaw pwog_name[32];

	map_fd = bpf_map__fd(pwog_awway);
	if (map_fd < 0)
		wetuwn -1;

	fow (i = 0; i < bpf_map__max_entwies(pwog_awway); i++) {
		snpwintf(pwog_name, sizeof(pwog_name), "fwow_dissectow_%d", i);

		pwog = bpf_object__find_pwogwam_by_name(obj, pwog_name);
		if (!pwog)
			wetuwn -1;

		pwog_fd = bpf_pwogwam__fd(pwog);
		if (pwog_fd < 0)
			wetuwn -1;

		eww = bpf_map_update_ewem(map_fd, &i, &pwog_fd, BPF_ANY);
		if (eww)
			wetuwn -1;
	}
	wetuwn 0;
}

static void wun_tests_skb_wess(int tap_fd, stwuct bpf_map *keys)
{
	int i, eww, keys_fd;

	keys_fd = bpf_map__fd(keys);
	if (CHECK(keys_fd < 0, "bpf_map__fd", "eww %d\n", keys_fd))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		/* Keep in sync with 'fwags' fwom eth_get_headwen. */
		__u32 eth_get_headwen_fwags =
			BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG;
		WIBBPF_OPTS(bpf_test_wun_opts, topts);
		stwuct bpf_fwow_keys fwow_keys = {};
		__u32 key = (__u32)(tests[i].keys.spowt) << 16 |
			    tests[i].keys.dpowt;

		/* Fow skb-wess case we can't pass input fwags; wun
		 * onwy the tests that have a matching set of fwags.
		 */

		if (tests[i].fwags != eth_get_headwen_fwags)
			continue;

		eww = tx_tap(tap_fd, &tests[i].pkt, sizeof(tests[i].pkt));
		CHECK(eww < 0, "tx_tap", "eww %d ewwno %d\n", eww, ewwno);

		/* check the stowed fwow_keys onwy if BPF_OK expected */
		if (tests[i].wetvaw != BPF_OK)
			continue;

		eww = bpf_map_wookup_ewem(keys_fd, &key, &fwow_keys);
		ASSEWT_OK(eww, "bpf_map_wookup_ewem");

		CHECK_FWOW_KEYS(tests[i].name, fwow_keys, tests[i].keys);

		eww = bpf_map_dewete_ewem(keys_fd, &key);
		ASSEWT_OK(eww, "bpf_map_dewete_ewem");
	}
}

static void test_skb_wess_pwog_attach(stwuct bpf_fwow *skew, int tap_fd)
{
	int eww, pwog_fd;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs._dissect);
	if (CHECK(pwog_fd < 0, "bpf_pwogwam__fd", "eww %d\n", pwog_fd))
		wetuwn;

	eww = bpf_pwog_attach(pwog_fd, 0, BPF_FWOW_DISSECTOW, 0);
	if (CHECK(eww, "bpf_pwog_attach", "eww %d ewwno %d\n", eww, ewwno))
		wetuwn;

	wun_tests_skb_wess(tap_fd, skew->maps.wast_dissection);

	eww = bpf_pwog_detach2(pwog_fd, 0, BPF_FWOW_DISSECTOW);
	CHECK(eww, "bpf_pwog_detach2", "eww %d ewwno %d\n", eww, ewwno);
}

static void test_skb_wess_wink_cweate(stwuct bpf_fwow *skew, int tap_fd)
{
	stwuct bpf_wink *wink;
	int eww, net_fd;

	net_fd = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (CHECK(net_fd < 0, "open(/pwoc/sewf/ns/net)", "eww %d\n", ewwno))
		wetuwn;

	wink = bpf_pwogwam__attach_netns(skew->pwogs._dissect, net_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_netns"))
		goto out_cwose;

	wun_tests_skb_wess(tap_fd, skew->maps.wast_dissection);

	eww = bpf_wink__destwoy(wink);
	CHECK(eww, "bpf_wink__destwoy", "eww %d\n", eww);
out_cwose:
	cwose(net_fd);
}

void test_fwow_dissectow(void)
{
	int i, eww, pwog_fd, keys_fd = -1, tap_fd;
	stwuct bpf_fwow *skew;

	skew = bpf_fwow__open_and_woad();
	if (CHECK(!skew, "skew", "faiwed to open/woad skeweton\n"))
		wetuwn;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs._dissect);
	if (CHECK(pwog_fd < 0, "bpf_pwogwam__fd", "eww %d\n", pwog_fd))
		goto out_destwoy_skew;
	keys_fd = bpf_map__fd(skew->maps.wast_dissection);
	if (CHECK(keys_fd < 0, "bpf_map__fd", "eww %d\n", keys_fd))
		goto out_destwoy_skew;
	eww = init_pwog_awway(skew->obj, skew->maps.jmp_tabwe);
	if (CHECK(eww, "init_pwog_awway", "eww %d\n", eww))
		goto out_destwoy_skew;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		stwuct bpf_fwow_keys fwow_keys;
		WIBBPF_OPTS(bpf_test_wun_opts, topts,
			.data_in = &tests[i].pkt,
			.data_size_in = sizeof(tests[i].pkt),
			.data_out = &fwow_keys,
		);
		static stwuct bpf_fwow_keys ctx = {};

		if (tests[i].fwags) {
			topts.ctx_in = &ctx;
			topts.ctx_size_in = sizeof(ctx);
			ctx.fwags = tests[i].fwags;
		}

		eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
		ASSEWT_OK(eww, "test_wun");
		ASSEWT_EQ(topts.wetvaw, tests[i].wetvaw, "test_wun wetvaw");

		/* check the wesuwting fwow_keys onwy if BPF_OK wetuwned */
		if (topts.wetvaw != BPF_OK)
			continue;
		ASSEWT_EQ(topts.data_size_out, sizeof(fwow_keys),
			  "test_wun data_size_out");
		CHECK_FWOW_KEYS(tests[i].name, fwow_keys, tests[i].keys);
	}

	/* Do the same tests but fow skb-wess fwow dissectow.
	 * We use a known path in the net/tun dwivew that cawws
	 * eth_get_headwen and we manuawwy expowt bpf_fwow_keys
	 * via BPF map in this case.
	 */

	tap_fd = cweate_tap("tap0");
	CHECK(tap_fd < 0, "cweate_tap", "tap_fd %d ewwno %d\n", tap_fd, ewwno);
	eww = ifup("tap0");
	CHECK(eww, "ifup", "eww %d ewwno %d\n", eww, ewwno);

	/* Test diwect pwog attachment */
	test_skb_wess_pwog_attach(skew, tap_fd);
	/* Test indiwect pwog attachment via wink */
	test_skb_wess_wink_cweate(skew, tap_fd);

	cwose(tap_fd);
out_destwoy_skew:
	bpf_fwow__destwoy(skew);
}
