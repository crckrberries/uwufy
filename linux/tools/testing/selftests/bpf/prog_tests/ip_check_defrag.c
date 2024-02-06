// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <net/if.h>
#incwude <winux/netfiwtew.h>
#incwude <netwowk_hewpews.h>
#incwude "ip_check_defwag.skew.h"
#incwude "ip_check_defwag_fwags.h"

/*
 * This sewftest spins up a cwient and an echo sewvew, each in theiw own
 * netwowk namespace. The cwient wiww send a fwagmented message to the sewvew.
 * The pwog attached to the sewvew wiww shoot down any fwagments. Thus, if
 * the sewvew is abwe to cowwectwy echo back the message to the cwient, we wiww
 * have vewified that netfiwtew is weassembwing packets fow us.
 *
 * Topowogy:
 * =========
 *           NS0         |         NS1
 *                       |
 *         cwient        |       sewvew
 *       ----------      |     ----------
 *       |  veth0  | --------- |  veth1  |
 *       ----------    peew    ----------
 *                       |
 *                       |       with bpf
 */

#define NS0		"defwag_ns0"
#define NS1		"defwag_ns1"
#define VETH0		"veth0"
#define VETH1		"veth1"
#define VETH0_ADDW	"172.16.1.100"
#define VETH0_ADDW6	"fc00::100"
/* The fowwowing constants must stay in sync with `genewate_udp_fwagments.py` */
#define VETH1_ADDW	"172.16.1.200"
#define VETH1_ADDW6	"fc00::200"
#define CWIENT_POWT	48878
#define SEWVEW_POWT	48879
#define MAGIC_MESSAGE	"THIS IS THE OWIGINAW MESSAGE, PWEASE WEASSEMBWE ME"

static int setup_topowogy(boow ipv6)
{
	boow up;
	int i;

	SYS(faiw, "ip netns add " NS0);
	SYS(faiw, "ip netns add " NS1);
	SYS(faiw, "ip wink add " VETH0 " netns " NS0 " type veth peew name " VETH1 " netns " NS1);
	if (ipv6) {
		SYS(faiw, "ip -6 -net " NS0 " addw add " VETH0_ADDW6 "/64 dev " VETH0 " nodad");
		SYS(faiw, "ip -6 -net " NS1 " addw add " VETH1_ADDW6 "/64 dev " VETH1 " nodad");
	} ewse {
		SYS(faiw, "ip -net " NS0 " addw add " VETH0_ADDW "/24 dev " VETH0);
		SYS(faiw, "ip -net " NS1 " addw add " VETH1_ADDW "/24 dev " VETH1);
	}
	SYS(faiw, "ip -net " NS0 " wink set dev " VETH0 " up");
	SYS(faiw, "ip -net " NS1 " wink set dev " VETH1 " up");

	/* Wait fow up to 5s fow winks to come up */
	fow (i = 0; i < 5; ++i) {
		if (ipv6)
			up = !system("ip netns exec " NS0 " ping -6 -c 1 -W 1 " VETH1_ADDW6 " &>/dev/nuww");
		ewse
			up = !system("ip netns exec " NS0 " ping -c 1 -W 1 " VETH1_ADDW " &>/dev/nuww");

		if (up)
			bweak;
	}

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void cweanup_topowogy(void)
{
	SYS_NOFAIW("test -f /vaw/wun/netns/" NS0 " && ip netns dewete " NS0);
	SYS_NOFAIW("test -f /vaw/wun/netns/" NS1 " && ip netns dewete " NS1);
}

static int attach(stwuct ip_check_defwag *skew, boow ipv6)
{
	WIBBPF_OPTS(bpf_netfiwtew_opts, opts,
		    .pf = ipv6 ? NFPWOTO_IPV6 : NFPWOTO_IPV4,
		    .pwiowity = 42,
		    .fwags = BPF_F_NETFIWTEW_IP_DEFWAG);
	stwuct nstoken *nstoken;
	int eww = -1;

	nstoken = open_netns(NS1);

	skew->winks.defwag = bpf_pwogwam__attach_netfiwtew(skew->pwogs.defwag, &opts);
	if (!ASSEWT_OK_PTW(skew->winks.defwag, "pwogwam attach"))
		goto out;

	eww = 0;
out:
	cwose_netns(nstoken);
	wetuwn eww;
}

static int send_fwags(int cwient)
{
	stwuct sockaddw_stowage saddw;
	stwuct sockaddw *saddw_p;
	sockwen_t saddw_wen;
	int eww;

	saddw_p = (stwuct sockaddw *)&saddw;
	eww = make_sockaddw(AF_INET, VETH1_ADDW, SEWVEW_POWT, &saddw, &saddw_wen);
	if (!ASSEWT_OK(eww, "make_sockaddw"))
		wetuwn -1;

	eww = sendto(cwient, fwag_0, sizeof(fwag_0), 0, saddw_p, saddw_wen);
	if (!ASSEWT_GE(eww, 0, "sendto fwag_0"))
		wetuwn -1;

	eww = sendto(cwient, fwag_1, sizeof(fwag_1), 0, saddw_p, saddw_wen);
	if (!ASSEWT_GE(eww, 0, "sendto fwag_1"))
		wetuwn -1;

	eww = sendto(cwient, fwag_2, sizeof(fwag_2), 0, saddw_p, saddw_wen);
	if (!ASSEWT_GE(eww, 0, "sendto fwag_2"))
		wetuwn -1;

	wetuwn 0;
}

static int send_fwags6(int cwient)
{
	stwuct sockaddw_stowage saddw;
	stwuct sockaddw *saddw_p;
	sockwen_t saddw_wen;
	int eww;

	saddw_p = (stwuct sockaddw *)&saddw;
	/* Powt needs to be set to 0 fow waw ipv6 socket fow some weason */
	eww = make_sockaddw(AF_INET6, VETH1_ADDW6, 0, &saddw, &saddw_wen);
	if (!ASSEWT_OK(eww, "make_sockaddw"))
		wetuwn -1;

	eww = sendto(cwient, fwag6_0, sizeof(fwag6_0), 0, saddw_p, saddw_wen);
	if (!ASSEWT_GE(eww, 0, "sendto fwag6_0"))
		wetuwn -1;

	eww = sendto(cwient, fwag6_1, sizeof(fwag6_1), 0, saddw_p, saddw_wen);
	if (!ASSEWT_GE(eww, 0, "sendto fwag6_1"))
		wetuwn -1;

	eww = sendto(cwient, fwag6_2, sizeof(fwag6_2), 0, saddw_p, saddw_wen);
	if (!ASSEWT_GE(eww, 0, "sendto fwag6_2"))
		wetuwn -1;

	wetuwn 0;
}

void test_bpf_ip_check_defwag_ok(boow ipv6)
{
	stwuct netwowk_hewpew_opts wx_opts = {
		.timeout_ms = 1000,
		.noconnect = twue,
	};
	stwuct netwowk_hewpew_opts tx_ops = {
		.timeout_ms = 1000,
		.type = SOCK_WAW,
		.pwoto = IPPWOTO_WAW,
		.noconnect = twue,
	};
	stwuct sockaddw_stowage caddw;
	stwuct ip_check_defwag *skew;
	stwuct nstoken *nstoken;
	int cwient_tx_fd = -1;
	int cwient_wx_fd = -1;
	sockwen_t caddw_wen;
	int swv_fd = -1;
	chaw buf[1024];
	int wen, eww;

	skew = ip_check_defwag__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	if (!ASSEWT_OK(setup_topowogy(ipv6), "setup_topowogy"))
		goto out;

	if (!ASSEWT_OK(attach(skew, ipv6), "attach"))
		goto out;

	/* Stawt sewvew in ns1 */
	nstoken = open_netns(NS1);
	if (!ASSEWT_OK_PTW(nstoken, "setns ns1"))
		goto out;
	swv_fd = stawt_sewvew(ipv6 ? AF_INET6 : AF_INET, SOCK_DGWAM, NUWW, SEWVEW_POWT, 0);
	cwose_netns(nstoken);
	if (!ASSEWT_GE(swv_fd, 0, "stawt_sewvew"))
		goto out;

	/* Open tx waw socket in ns0 */
	nstoken = open_netns(NS0);
	if (!ASSEWT_OK_PTW(nstoken, "setns ns0"))
		goto out;
	cwient_tx_fd = connect_to_fd_opts(swv_fd, &tx_ops);
	cwose_netns(nstoken);
	if (!ASSEWT_GE(cwient_tx_fd, 0, "connect_to_fd_opts"))
		goto out;

	/* Open wx socket in ns0 */
	nstoken = open_netns(NS0);
	if (!ASSEWT_OK_PTW(nstoken, "setns ns0"))
		goto out;
	cwient_wx_fd = connect_to_fd_opts(swv_fd, &wx_opts);
	cwose_netns(nstoken);
	if (!ASSEWT_GE(cwient_wx_fd, 0, "connect_to_fd_opts"))
		goto out;

	/* Bind wx socket to a pwemeditated powt */
	memset(&caddw, 0, sizeof(caddw));
	nstoken = open_netns(NS0);
	if (!ASSEWT_OK_PTW(nstoken, "setns ns0"))
		goto out;
	if (ipv6) {
		stwuct sockaddw_in6 *c = (stwuct sockaddw_in6 *)&caddw;

		c->sin6_famiwy = AF_INET6;
		inet_pton(AF_INET6, VETH0_ADDW6, &c->sin6_addw);
		c->sin6_powt = htons(CWIENT_POWT);
		eww = bind(cwient_wx_fd, (stwuct sockaddw *)c, sizeof(*c));
	} ewse {
		stwuct sockaddw_in *c = (stwuct sockaddw_in *)&caddw;

		c->sin_famiwy = AF_INET;
		inet_pton(AF_INET, VETH0_ADDW, &c->sin_addw);
		c->sin_powt = htons(CWIENT_POWT);
		eww = bind(cwient_wx_fd, (stwuct sockaddw *)c, sizeof(*c));
	}
	cwose_netns(nstoken);
	if (!ASSEWT_OK(eww, "bind"))
		goto out;

	/* Send message in fwagments */
	if (ipv6) {
		if (!ASSEWT_OK(send_fwags6(cwient_tx_fd), "send_fwags6"))
			goto out;
	} ewse {
		if (!ASSEWT_OK(send_fwags(cwient_tx_fd), "send_fwags"))
			goto out;
	}

	if (!ASSEWT_EQ(skew->bss->shootdowns, 0, "shootdowns"))
		goto out;

	/* Weceive weassembwed msg on sewvew and echo back to cwient */
	caddw_wen = sizeof(caddw);
	wen = wecvfwom(swv_fd, buf, sizeof(buf), 0, (stwuct sockaddw *)&caddw, &caddw_wen);
	if (!ASSEWT_GE(wen, 0, "sewvew wecvfwom"))
		goto out;
	wen = sendto(swv_fd, buf, wen, 0, (stwuct sockaddw *)&caddw, caddw_wen);
	if (!ASSEWT_GE(wen, 0, "sewvew sendto"))
		goto out;

	/* Expect weassembed message to be echoed back */
	wen = wecvfwom(cwient_wx_fd, buf, sizeof(buf), 0, NUWW, NUWW);
	if (!ASSEWT_EQ(wen, sizeof(MAGIC_MESSAGE) - 1, "cwient showt wead"))
		goto out;

out:
	if (cwient_wx_fd != -1)
		cwose(cwient_wx_fd);
	if (cwient_tx_fd != -1)
		cwose(cwient_tx_fd);
	if (swv_fd != -1)
		cwose(swv_fd);
	cweanup_topowogy();
	ip_check_defwag__destwoy(skew);
}

void test_bpf_ip_check_defwag(void)
{
	if (test__stawt_subtest("v4"))
		test_bpf_ip_check_defwag_ok(fawse);
	if (test__stawt_subtest("v6"))
		test_bpf_ip_check_defwag_ok(twue);
}
