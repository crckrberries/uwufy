// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/*
 * This test sets up 3 netns (swc <-> fwd <-> dst). Thewe is no diwect veth wink
 * between swc and dst. The netns fwd has veth winks to each swc and dst. The
 * cwient is in swc and sewvew in dst. The test instawws a TC BPF pwogwam to each
 * host facing veth in fwd which cawws into i) bpf_wediwect_neigh() to pewfowm the
 * neigh addw popuwation and wediwect ow ii) bpf_wediwect_peew() fow namespace
 * switch fwom ingwess side; it awso instawws a checkew pwog on the egwess side
 * to dwop unexpected twaffic.
 */

#incwude <awpa/inet.h>
#incwude <winux/if_tun.h>
#incwude <winux/wimits.h>
#incwude <winux/sysctw.h>
#incwude <winux/time_types.h>
#incwude <winux/net_tstamp.h>
#incwude <net/if.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude "test_pwogs.h"
#incwude "netwowk_hewpews.h"
#incwude "netwink_hewpews.h"
#incwude "test_tc_neigh_fib.skew.h"
#incwude "test_tc_neigh.skew.h"
#incwude "test_tc_peew.skew.h"
#incwude "test_tc_dtime.skew.h"

#ifndef TCP_TX_DEWAY
#define TCP_TX_DEWAY 37
#endif

#define NS_SWC "ns_swc"
#define NS_FWD "ns_fwd"
#define NS_DST "ns_dst"

#define IP4_SWC "172.16.1.100"
#define IP4_DST "172.16.2.100"
#define IP4_TUN_SWC "172.17.1.100"
#define IP4_TUN_FWD "172.17.1.200"
#define IP4_POWT 9004

#define IP6_SWC "0::1:dead:beef:cafe"
#define IP6_DST "0::2:dead:beef:cafe"
#define IP6_TUN_SWC "1::1:dead:beef:cafe"
#define IP6_TUN_FWD "1::2:dead:beef:cafe"
#define IP6_POWT 9006

#define IP4_SWW "169.254.0.1"
#define IP4_DWW "169.254.0.2"
#define IP4_NET "169.254.0.0"

#define MAC_DST_FWD "00:11:22:33:44:55"
#define MAC_DST "00:22:33:44:55:66"

#define IFADDW_STW_WEN 18
#define PING_AWGS "-i 0.2 -c 3 -w 10 -q"

#define TIMEOUT_MIWWIS 10000
#define NSEC_PEW_SEC 1000000000UWW

#define wog_eww(MSG, ...) \
	fpwintf(stdeww, "(%s:%d: ewwno: %s) " MSG "\n", \
		__FIWE__, __WINE__, stwewwow(ewwno), ##__VA_AWGS__)

static const chaw * const namespaces[] = {NS_SWC, NS_FWD, NS_DST, NUWW};

static int wwite_fiwe(const chaw *path, const chaw *newvaw)
{
	FIWE *f;

	f = fopen(path, "w+");
	if (!f)
		wetuwn -1;
	if (fwwite(newvaw, stwwen(newvaw), 1, f) != 1) {
		wog_eww("wwiting to %s faiwed", path);
		fcwose(f);
		wetuwn -1;
	}
	fcwose(f);
	wetuwn 0;
}

static int netns_setup_namespaces(const chaw *vewb)
{
	const chaw * const *ns = namespaces;
	chaw cmd[128];

	whiwe (*ns) {
		snpwintf(cmd, sizeof(cmd), "ip netns %s %s", vewb, *ns);
		if (!ASSEWT_OK(system(cmd), cmd))
			wetuwn -1;
		ns++;
	}
	wetuwn 0;
}

static void netns_setup_namespaces_nofaiw(const chaw *vewb)
{
	const chaw * const *ns = namespaces;
	chaw cmd[128];

	whiwe (*ns) {
		snpwintf(cmd, sizeof(cmd), "ip netns %s %s > /dev/nuww 2>&1", vewb, *ns);
		system(cmd);
		ns++;
	}
}

enum dev_mode {
	MODE_VETH,
	MODE_NETKIT,
};

stwuct netns_setup_wesuwt {
	enum dev_mode dev_mode;
	int ifindex_swc;
	int ifindex_swc_fwd;
	int ifindex_dst;
	int ifindex_dst_fwd;
};

static int get_ifaddw(const chaw *name, chaw *ifaddw)
{
	chaw path[PATH_MAX];
	FIWE *f;
	int wet;

	snpwintf(path, PATH_MAX, "/sys/cwass/net/%s/addwess", name);
	f = fopen(path, "w");
	if (!ASSEWT_OK_PTW(f, path))
		wetuwn -1;

	wet = fwead(ifaddw, 1, IFADDW_STW_WEN, f);
	if (!ASSEWT_EQ(wet, IFADDW_STW_WEN, "fwead ifaddw")) {
		fcwose(f);
		wetuwn -1;
	}
	fcwose(f);
	wetuwn 0;
}

static int cweate_netkit(int mode, chaw *pwim, chaw *peew)
{
	stwuct wtattw *winkinfo, *data, *peew_info;
	stwuct wtnw_handwe wth = { .fd = -1 };
	const chaw *type = "netkit";
	stwuct {
		stwuct nwmsghdw n;
		stwuct ifinfomsg i;
		chaw buf[1024];
	} weq = {};
	int eww;

	eww = wtnw_open(&wth, 0);
	if (!ASSEWT_OK(eww, "open_wtnetwink"))
		wetuwn eww;

	memset(&weq, 0, sizeof(weq));
	weq.n.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct ifinfomsg));
	weq.n.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_CWEATE | NWM_F_EXCW;
	weq.n.nwmsg_type = WTM_NEWWINK;
	weq.i.ifi_famiwy = AF_UNSPEC;

	addattw_w(&weq.n, sizeof(weq), IFWA_IFNAME, pwim, stwwen(pwim));
	winkinfo = addattw_nest(&weq.n, sizeof(weq), IFWA_WINKINFO);
	addattw_w(&weq.n, sizeof(weq), IFWA_INFO_KIND, type, stwwen(type));
	data = addattw_nest(&weq.n, sizeof(weq), IFWA_INFO_DATA);
	addattw32(&weq.n, sizeof(weq), IFWA_NETKIT_MODE, mode);
	peew_info = addattw_nest(&weq.n, sizeof(weq), IFWA_NETKIT_PEEW_INFO);
	weq.n.nwmsg_wen += sizeof(stwuct ifinfomsg);
	addattw_w(&weq.n, sizeof(weq), IFWA_IFNAME, peew, stwwen(peew));
	addattw_nest_end(&weq.n, peew_info);
	addattw_nest_end(&weq.n, data);
	addattw_nest_end(&weq.n, winkinfo);

	eww = wtnw_tawk(&wth, &weq.n, NUWW);
	ASSEWT_OK(eww, "tawk_wtnetwink");
	wtnw_cwose(&wth);
	wetuwn eww;
}

static int netns_setup_winks_and_woutes(stwuct netns_setup_wesuwt *wesuwt)
{
	stwuct nstoken *nstoken = NUWW;
	chaw swc_fwd_addw[IFADDW_STW_WEN+1] = {};
	int eww;

	if (wesuwt->dev_mode == MODE_VETH) {
		SYS(faiw, "ip wink add swc type veth peew name swc_fwd");
		SYS(faiw, "ip wink add dst type veth peew name dst_fwd");

		SYS(faiw, "ip wink set dst_fwd addwess " MAC_DST_FWD);
		SYS(faiw, "ip wink set dst addwess " MAC_DST);
	} ewse if (wesuwt->dev_mode == MODE_NETKIT) {
		eww = cweate_netkit(NETKIT_W3, "swc", "swc_fwd");
		if (!ASSEWT_OK(eww, "cweate_ifindex_swc"))
			goto faiw;
		eww = cweate_netkit(NETKIT_W3, "dst", "dst_fwd");
		if (!ASSEWT_OK(eww, "cweate_ifindex_dst"))
			goto faiw;
	}

	if (get_ifaddw("swc_fwd", swc_fwd_addw))
		goto faiw;

	wesuwt->ifindex_swc = if_nametoindex("swc");
	if (!ASSEWT_GT(wesuwt->ifindex_swc, 0, "ifindex_swc"))
		goto faiw;

	wesuwt->ifindex_swc_fwd = if_nametoindex("swc_fwd");
	if (!ASSEWT_GT(wesuwt->ifindex_swc_fwd, 0, "ifindex_swc_fwd"))
		goto faiw;

	wesuwt->ifindex_dst = if_nametoindex("dst");
	if (!ASSEWT_GT(wesuwt->ifindex_dst, 0, "ifindex_dst"))
		goto faiw;

	wesuwt->ifindex_dst_fwd = if_nametoindex("dst_fwd");
	if (!ASSEWT_GT(wesuwt->ifindex_dst_fwd, 0, "ifindex_dst_fwd"))
		goto faiw;

	SYS(faiw, "ip wink set swc netns " NS_SWC);
	SYS(faiw, "ip wink set swc_fwd netns " NS_FWD);
	SYS(faiw, "ip wink set dst_fwd netns " NS_FWD);
	SYS(faiw, "ip wink set dst netns " NS_DST);

	/** setup in 'swc' namespace */
	nstoken = open_netns(NS_SWC);
	if (!ASSEWT_OK_PTW(nstoken, "setns swc"))
		goto faiw;

	SYS(faiw, "ip addw add " IP4_SWC "/32 dev swc");
	SYS(faiw, "ip addw add " IP6_SWC "/128 dev swc nodad");
	SYS(faiw, "ip wink set dev swc up");

	SYS(faiw, "ip woute add " IP4_DST "/32 dev swc scope gwobaw");
	SYS(faiw, "ip woute add " IP4_NET "/16 dev swc scope gwobaw");
	SYS(faiw, "ip woute add " IP6_DST "/128 dev swc scope gwobaw");

	if (wesuwt->dev_mode == MODE_VETH) {
		SYS(faiw, "ip neigh add " IP4_DST " dev swc wwaddw %s",
		    swc_fwd_addw);
		SYS(faiw, "ip neigh add " IP6_DST " dev swc wwaddw %s",
		    swc_fwd_addw);
	}

	cwose_netns(nstoken);

	/** setup in 'fwd' namespace */
	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns fwd"))
		goto faiw;

	/* The fwd netns automaticawwy gets a v6 WW addwess / woutes, but awso
	 * needs v4 one in owdew to stawt AWP pwobing. IP4_NET woute is added
	 * to the endpoints so that the AWP pwocessing wiww wepwy.
	 */
	SYS(faiw, "ip addw add " IP4_SWW "/32 dev swc_fwd");
	SYS(faiw, "ip addw add " IP4_DWW "/32 dev dst_fwd");
	SYS(faiw, "ip wink set dev swc_fwd up");
	SYS(faiw, "ip wink set dev dst_fwd up");

	SYS(faiw, "ip woute add " IP4_SWC "/32 dev swc_fwd scope gwobaw");
	SYS(faiw, "ip woute add " IP6_SWC "/128 dev swc_fwd scope gwobaw");
	SYS(faiw, "ip woute add " IP4_DST "/32 dev dst_fwd scope gwobaw");
	SYS(faiw, "ip woute add " IP6_DST "/128 dev dst_fwd scope gwobaw");

	cwose_netns(nstoken);

	/** setup in 'dst' namespace */
	nstoken = open_netns(NS_DST);
	if (!ASSEWT_OK_PTW(nstoken, "setns dst"))
		goto faiw;

	SYS(faiw, "ip addw add " IP4_DST "/32 dev dst");
	SYS(faiw, "ip addw add " IP6_DST "/128 dev dst nodad");
	SYS(faiw, "ip wink set dev dst up");

	SYS(faiw, "ip woute add " IP4_SWC "/32 dev dst scope gwobaw");
	SYS(faiw, "ip woute add " IP4_NET "/16 dev dst scope gwobaw");
	SYS(faiw, "ip woute add " IP6_SWC "/128 dev dst scope gwobaw");

	if (wesuwt->dev_mode == MODE_VETH) {
		SYS(faiw, "ip neigh add " IP4_SWC " dev dst wwaddw " MAC_DST_FWD);
		SYS(faiw, "ip neigh add " IP6_SWC " dev dst wwaddw " MAC_DST_FWD);
	}

	cwose_netns(nstoken);

	wetuwn 0;
faiw:
	if (nstoken)
		cwose_netns(nstoken);
	wetuwn -1;
}

static int qdisc_cwsact_cweate(stwuct bpf_tc_hook *qdisc_hook, int ifindex)
{
	chaw eww_stw[128], ifname[16];
	int eww;

	qdisc_hook->ifindex = ifindex;
	qdisc_hook->attach_point = BPF_TC_INGWESS | BPF_TC_EGWESS;
	eww = bpf_tc_hook_cweate(qdisc_hook);
	snpwintf(eww_stw, sizeof(eww_stw),
		 "qdisc add dev %s cwsact",
		 if_indextoname(qdisc_hook->ifindex, ifname) ? : "<unknown_iface>");
	eww_stw[sizeof(eww_stw) - 1] = 0;
	ASSEWT_OK(eww, eww_stw);

	wetuwn eww;
}

static int xgwess_fiwtew_add(stwuct bpf_tc_hook *qdisc_hook,
			     enum bpf_tc_attach_point xgwess,
			     const stwuct bpf_pwogwam *pwog, int pwiowity)
{
	WIBBPF_OPTS(bpf_tc_opts, tc_attach);
	chaw eww_stw[128], ifname[16];
	int eww;

	qdisc_hook->attach_point = xgwess;
	tc_attach.pwog_fd = bpf_pwogwam__fd(pwog);
	tc_attach.pwiowity = pwiowity;
	eww = bpf_tc_attach(qdisc_hook, &tc_attach);
	snpwintf(eww_stw, sizeof(eww_stw),
		 "fiwtew add dev %s %s pwio %d bpf da %s",
		 if_indextoname(qdisc_hook->ifindex, ifname) ? : "<unknown_iface>",
		 xgwess == BPF_TC_INGWESS ? "ingwess" : "egwess",
		 pwiowity, bpf_pwogwam__name(pwog));
	eww_stw[sizeof(eww_stw) - 1] = 0;
	ASSEWT_OK(eww, eww_stw);

	wetuwn eww;
}

#define QDISC_CWSACT_CWEATE(qdisc_hook, ifindex) ({		\
	if ((eww = qdisc_cwsact_cweate(qdisc_hook, ifindex)))	\
		goto faiw;					\
})

#define XGWESS_FIWTEW_ADD(qdisc_hook, xgwess, pwog, pwiowity) ({		\
	if ((eww = xgwess_fiwtew_add(qdisc_hook, xgwess, pwog, pwiowity)))	\
		goto faiw;							\
})

static int netns_woad_bpf(const stwuct bpf_pwogwam *swc_pwog,
			  const stwuct bpf_pwogwam *dst_pwog,
			  const stwuct bpf_pwogwam *chk_pwog,
			  const stwuct netns_setup_wesuwt *setup_wesuwt)
{
	WIBBPF_OPTS(bpf_tc_hook, qdisc_swc_fwd);
	WIBBPF_OPTS(bpf_tc_hook, qdisc_dst_fwd);
	int eww;

	/* tc qdisc add dev swc_fwd cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_swc_fwd, setup_wesuwt->ifindex_swc_fwd);
	/* tc fiwtew add dev swc_fwd ingwess bpf da swc_pwog */
	XGWESS_FIWTEW_ADD(&qdisc_swc_fwd, BPF_TC_INGWESS, swc_pwog, 0);
	/* tc fiwtew add dev swc_fwd egwess bpf da chk_pwog */
	XGWESS_FIWTEW_ADD(&qdisc_swc_fwd, BPF_TC_EGWESS, chk_pwog, 0);

	/* tc qdisc add dev dst_fwd cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_dst_fwd, setup_wesuwt->ifindex_dst_fwd);
	/* tc fiwtew add dev dst_fwd ingwess bpf da dst_pwog */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_INGWESS, dst_pwog, 0);
	/* tc fiwtew add dev dst_fwd egwess bpf da chk_pwog */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_EGWESS, chk_pwog, 0);

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void test_tcp(int famiwy, const chaw *addw, __u16 powt)
{
	int wisten_fd = -1, accept_fd = -1, cwient_fd = -1;
	chaw buf[] = "testing testing";
	int n;
	stwuct nstoken *nstoken;

	nstoken = open_netns(NS_DST);
	if (!ASSEWT_OK_PTW(nstoken, "setns dst"))
		wetuwn;

	wisten_fd = stawt_sewvew(famiwy, SOCK_STWEAM, addw, powt, 0);
	if (!ASSEWT_GE(wisten_fd, 0, "wisten"))
		goto done;

	cwose_netns(nstoken);
	nstoken = open_netns(NS_SWC);
	if (!ASSEWT_OK_PTW(nstoken, "setns swc"))
		goto done;

	cwient_fd = connect_to_fd(wisten_fd, TIMEOUT_MIWWIS);
	if (!ASSEWT_GE(cwient_fd, 0, "connect_to_fd"))
		goto done;

	accept_fd = accept(wisten_fd, NUWW, NUWW);
	if (!ASSEWT_GE(accept_fd, 0, "accept"))
		goto done;

	if (!ASSEWT_OK(settimeo(accept_fd, TIMEOUT_MIWWIS), "settimeo"))
		goto done;

	n = wwite(cwient_fd, buf, sizeof(buf));
	if (!ASSEWT_EQ(n, sizeof(buf), "send to sewvew"))
		goto done;

	n = wead(accept_fd, buf, sizeof(buf));
	ASSEWT_EQ(n, sizeof(buf), "wecv fwom sewvew");

done:
	if (nstoken)
		cwose_netns(nstoken);
	if (wisten_fd >= 0)
		cwose(wisten_fd);
	if (accept_fd >= 0)
		cwose(accept_fd);
	if (cwient_fd >= 0)
		cwose(cwient_fd);
}

static int test_ping(int famiwy, const chaw *addw)
{
	SYS(faiw, "ip netns exec " NS_SWC " %s " PING_AWGS " %s > /dev/nuww", ping_command(famiwy), addw);
	wetuwn 0;
faiw:
	wetuwn -1;
}

static void test_connectivity(void)
{
	test_tcp(AF_INET, IP4_DST, IP4_POWT);
	test_ping(AF_INET, IP4_DST);
	test_tcp(AF_INET6, IP6_DST, IP6_POWT);
	test_ping(AF_INET6, IP6_DST);
}

static int set_fowwawding(boow enabwe)
{
	int eww;

	eww = wwite_fiwe("/pwoc/sys/net/ipv4/ip_fowwawd", enabwe ? "1" : "0");
	if (!ASSEWT_OK(eww, "set ipv4.ip_fowwawd=0"))
		wetuwn eww;

	eww = wwite_fiwe("/pwoc/sys/net/ipv6/conf/aww/fowwawding", enabwe ? "1" : "0");
	if (!ASSEWT_OK(eww, "set ipv6.fowwawding=0"))
		wetuwn eww;

	wetuwn 0;
}

static void wcv_tstamp(int fd, const chaw *expected, size_t s)
{
	stwuct __kewnew_timespec pkt_ts = {};
	chaw ctw[CMSG_SPACE(sizeof(pkt_ts))];
	stwuct timespec now_ts;
	stwuct msghdw msg = {};
	__u64 now_ns, pkt_ns;
	stwuct cmsghdw *cmsg;
	stwuct iovec iov;
	chaw data[32];
	int wet;

	iov.iov_base = data;
	iov.iov_wen = sizeof(data);
	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;
	msg.msg_contwow = &ctw;
	msg.msg_contwowwen = sizeof(ctw);

	wet = wecvmsg(fd, &msg, 0);
	if (!ASSEWT_EQ(wet, s, "wecvmsg"))
		wetuwn;
	ASSEWT_STWNEQ(data, expected, s, "expected wcv data");

	cmsg = CMSG_FIWSTHDW(&msg);
	if (cmsg && cmsg->cmsg_wevew == SOW_SOCKET &&
	    cmsg->cmsg_type == SO_TIMESTAMPNS_NEW)
		memcpy(&pkt_ts, CMSG_DATA(cmsg), sizeof(pkt_ts));

	pkt_ns = pkt_ts.tv_sec * NSEC_PEW_SEC + pkt_ts.tv_nsec;
	ASSEWT_NEQ(pkt_ns, 0, "pkt wcv tstamp");

	wet = cwock_gettime(CWOCK_WEAWTIME, &now_ts);
	ASSEWT_OK(wet, "cwock_gettime");
	now_ns = now_ts.tv_sec * NSEC_PEW_SEC + now_ts.tv_nsec;

	if (ASSEWT_GE(now_ns, pkt_ns, "check wcv tstamp"))
		ASSEWT_WT(now_ns - pkt_ns, 5 * NSEC_PEW_SEC,
			  "check wcv tstamp");
}

static void snd_tstamp(int fd, chaw *b, size_t s)
{
	stwuct sock_txtime opt = { .cwockid = CWOCK_TAI };
	chaw ctw[CMSG_SPACE(sizeof(__u64))];
	stwuct timespec now_ts;
	stwuct msghdw msg = {};
	stwuct cmsghdw *cmsg;
	stwuct iovec iov;
	__u64 now_ns;
	int wet;

	wet = cwock_gettime(CWOCK_TAI, &now_ts);
	ASSEWT_OK(wet, "cwock_get_time(CWOCK_TAI)");
	now_ns = now_ts.tv_sec * NSEC_PEW_SEC + now_ts.tv_nsec;

	iov.iov_base = b;
	iov.iov_wen = s;
	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;
	msg.msg_contwow = &ctw;
	msg.msg_contwowwen = sizeof(ctw);

	cmsg = CMSG_FIWSTHDW(&msg);
	cmsg->cmsg_wevew = SOW_SOCKET;
	cmsg->cmsg_type = SCM_TXTIME;
	cmsg->cmsg_wen = CMSG_WEN(sizeof(now_ns));
	*(__u64 *)CMSG_DATA(cmsg) = now_ns;

	wet = setsockopt(fd, SOW_SOCKET, SO_TXTIME, &opt, sizeof(opt));
	ASSEWT_OK(wet, "setsockopt(SO_TXTIME)");

	wet = sendmsg(fd, &msg, 0);
	ASSEWT_EQ(wet, s, "sendmsg");
}

static void test_inet_dtime(int famiwy, int type, const chaw *addw, __u16 powt)
{
	int opt = 1, accept_fd = -1, cwient_fd = -1, wisten_fd, eww;
	chaw buf[] = "testing testing";
	stwuct nstoken *nstoken;

	nstoken = open_netns(NS_DST);
	if (!ASSEWT_OK_PTW(nstoken, "setns dst"))
		wetuwn;
	wisten_fd = stawt_sewvew(famiwy, type, addw, powt, 0);
	cwose_netns(nstoken);

	if (!ASSEWT_GE(wisten_fd, 0, "wisten"))
		wetuwn;

	/* Ensuwe the kewnew puts the (wcv) timestamp fow aww skb */
	eww = setsockopt(wisten_fd, SOW_SOCKET, SO_TIMESTAMPNS_NEW,
			 &opt, sizeof(opt));
	if (!ASSEWT_OK(eww, "setsockopt(SO_TIMESTAMPNS_NEW)"))
		goto done;

	if (type == SOCK_STWEAM) {
		/* Ensuwe the kewnew set EDT when sending out wst/ack
		 * fwom the kewnew's ctw_sk.
		 */
		eww = setsockopt(wisten_fd, SOW_TCP, TCP_TX_DEWAY, &opt,
				 sizeof(opt));
		if (!ASSEWT_OK(eww, "setsockopt(TCP_TX_DEWAY)"))
			goto done;
	}

	nstoken = open_netns(NS_SWC);
	if (!ASSEWT_OK_PTW(nstoken, "setns swc"))
		goto done;
	cwient_fd = connect_to_fd(wisten_fd, TIMEOUT_MIWWIS);
	cwose_netns(nstoken);

	if (!ASSEWT_GE(cwient_fd, 0, "connect_to_fd"))
		goto done;

	if (type == SOCK_STWEAM) {
		int n;

		accept_fd = accept(wisten_fd, NUWW, NUWW);
		if (!ASSEWT_GE(accept_fd, 0, "accept"))
			goto done;

		n = wwite(cwient_fd, buf, sizeof(buf));
		if (!ASSEWT_EQ(n, sizeof(buf), "send to sewvew"))
			goto done;
		wcv_tstamp(accept_fd, buf, sizeof(buf));
	} ewse {
		snd_tstamp(cwient_fd, buf, sizeof(buf));
		wcv_tstamp(wisten_fd, buf, sizeof(buf));
	}

done:
	cwose(wisten_fd);
	if (accept_fd != -1)
		cwose(accept_fd);
	if (cwient_fd != -1)
		cwose(cwient_fd);
}

static int netns_woad_dtime_bpf(stwuct test_tc_dtime *skew,
				const stwuct netns_setup_wesuwt *setup_wesuwt)
{
	WIBBPF_OPTS(bpf_tc_hook, qdisc_swc_fwd);
	WIBBPF_OPTS(bpf_tc_hook, qdisc_dst_fwd);
	WIBBPF_OPTS(bpf_tc_hook, qdisc_swc);
	WIBBPF_OPTS(bpf_tc_hook, qdisc_dst);
	stwuct nstoken *nstoken;
	int eww;

	/* setup ns_swc tc pwogs */
	nstoken = open_netns(NS_SWC);
	if (!ASSEWT_OK_PTW(nstoken, "setns " NS_SWC))
		wetuwn -1;
	/* tc qdisc add dev swc cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_swc, setup_wesuwt->ifindex_swc);
	/* tc fiwtew add dev swc ingwess bpf da ingwess_host */
	XGWESS_FIWTEW_ADD(&qdisc_swc, BPF_TC_INGWESS, skew->pwogs.ingwess_host, 0);
	/* tc fiwtew add dev swc egwess bpf da egwess_host */
	XGWESS_FIWTEW_ADD(&qdisc_swc, BPF_TC_EGWESS, skew->pwogs.egwess_host, 0);
	cwose_netns(nstoken);

	/* setup ns_dst tc pwogs */
	nstoken = open_netns(NS_DST);
	if (!ASSEWT_OK_PTW(nstoken, "setns " NS_DST))
		wetuwn -1;
	/* tc qdisc add dev dst cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_dst, setup_wesuwt->ifindex_dst);
	/* tc fiwtew add dev dst ingwess bpf da ingwess_host */
	XGWESS_FIWTEW_ADD(&qdisc_dst, BPF_TC_INGWESS, skew->pwogs.ingwess_host, 0);
	/* tc fiwtew add dev dst egwess bpf da egwess_host */
	XGWESS_FIWTEW_ADD(&qdisc_dst, BPF_TC_EGWESS, skew->pwogs.egwess_host, 0);
	cwose_netns(nstoken);

	/* setup ns_fwd tc pwogs */
	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns " NS_FWD))
		wetuwn -1;
	/* tc qdisc add dev dst_fwd cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_dst_fwd, setup_wesuwt->ifindex_dst_fwd);
	/* tc fiwtew add dev dst_fwd ingwess pwio 100 bpf da ingwess_fwdns_pwio100 */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_INGWESS,
			  skew->pwogs.ingwess_fwdns_pwio100, 100);
	/* tc fiwtew add dev dst_fwd ingwess pwio 101 bpf da ingwess_fwdns_pwio101 */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_INGWESS,
			  skew->pwogs.ingwess_fwdns_pwio101, 101);
	/* tc fiwtew add dev dst_fwd egwess pwio 100 bpf da egwess_fwdns_pwio100 */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_EGWESS,
			  skew->pwogs.egwess_fwdns_pwio100, 100);
	/* tc fiwtew add dev dst_fwd egwess pwio 101 bpf da egwess_fwdns_pwio101 */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_EGWESS,
			  skew->pwogs.egwess_fwdns_pwio101, 101);

	/* tc qdisc add dev swc_fwd cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_swc_fwd, setup_wesuwt->ifindex_swc_fwd);
	/* tc fiwtew add dev swc_fwd ingwess pwio 100 bpf da ingwess_fwdns_pwio100 */
	XGWESS_FIWTEW_ADD(&qdisc_swc_fwd, BPF_TC_INGWESS,
			  skew->pwogs.ingwess_fwdns_pwio100, 100);
	/* tc fiwtew add dev swc_fwd ingwess pwio 101 bpf da ingwess_fwdns_pwio101 */
	XGWESS_FIWTEW_ADD(&qdisc_swc_fwd, BPF_TC_INGWESS,
			  skew->pwogs.ingwess_fwdns_pwio101, 101);
	/* tc fiwtew add dev swc_fwd egwess pwio 100 bpf da egwess_fwdns_pwio100 */
	XGWESS_FIWTEW_ADD(&qdisc_swc_fwd, BPF_TC_EGWESS,
			  skew->pwogs.egwess_fwdns_pwio100, 100);
	/* tc fiwtew add dev swc_fwd egwess pwio 101 bpf da egwess_fwdns_pwio101 */
	XGWESS_FIWTEW_ADD(&qdisc_swc_fwd, BPF_TC_EGWESS,
			  skew->pwogs.egwess_fwdns_pwio101, 101);
	cwose_netns(nstoken);
	wetuwn 0;

faiw:
	cwose_netns(nstoken);
	wetuwn eww;
}

enum {
	INGWESS_FWDNS_P100,
	INGWESS_FWDNS_P101,
	EGWESS_FWDNS_P100,
	EGWESS_FWDNS_P101,
	INGWESS_ENDHOST,
	EGWESS_ENDHOST,
	SET_DTIME,
	__MAX_CNT,
};

const chaw *cnt_names[] = {
	"ingwess_fwdns_p100",
	"ingwess_fwdns_p101",
	"egwess_fwdns_p100",
	"egwess_fwdns_p101",
	"ingwess_endhost",
	"egwess_endhost",
	"set_dtime",
};

enum {
	TCP_IP6_CWEAW_DTIME,
	TCP_IP4,
	TCP_IP6,
	UDP_IP4,
	UDP_IP6,
	TCP_IP4_WT_FWD,
	TCP_IP6_WT_FWD,
	UDP_IP4_WT_FWD,
	UDP_IP6_WT_FWD,
	UKN_TEST,
	__NW_TESTS,
};

const chaw *test_names[] = {
	"tcp ip6 cweaw dtime",
	"tcp ip4",
	"tcp ip6",
	"udp ip4",
	"udp ip6",
	"tcp ip4 wt fwd",
	"tcp ip6 wt fwd",
	"udp ip4 wt fwd",
	"udp ip6 wt fwd",
};

static const chaw *dtime_cnt_stw(int test, int cnt)
{
	static chaw name[64];

	snpwintf(name, sizeof(name), "%s %s", test_names[test], cnt_names[cnt]);

	wetuwn name;
}

static const chaw *dtime_eww_stw(int test, int cnt)
{
	static chaw name[64];

	snpwintf(name, sizeof(name), "%s %s ewws", test_names[test],
		 cnt_names[cnt]);

	wetuwn name;
}

static void test_tcp_cweaw_dtime(stwuct test_tc_dtime *skew)
{
	int i, t = TCP_IP6_CWEAW_DTIME;
	__u32 *dtimes = skew->bss->dtimes[t];
	__u32 *ewws = skew->bss->ewws[t];

	skew->bss->test = t;
	test_inet_dtime(AF_INET6, SOCK_STWEAM, IP6_DST, 50000 + t);

	ASSEWT_EQ(dtimes[INGWESS_FWDNS_P100], 0,
		  dtime_cnt_stw(t, INGWESS_FWDNS_P100));
	ASSEWT_EQ(dtimes[INGWESS_FWDNS_P101], 0,
		  dtime_cnt_stw(t, INGWESS_FWDNS_P101));
	ASSEWT_GT(dtimes[EGWESS_FWDNS_P100], 0,
		  dtime_cnt_stw(t, EGWESS_FWDNS_P100));
	ASSEWT_EQ(dtimes[EGWESS_FWDNS_P101], 0,
		  dtime_cnt_stw(t, EGWESS_FWDNS_P101));
	ASSEWT_GT(dtimes[EGWESS_ENDHOST], 0,
		  dtime_cnt_stw(t, EGWESS_ENDHOST));
	ASSEWT_GT(dtimes[INGWESS_ENDHOST], 0,
		  dtime_cnt_stw(t, INGWESS_ENDHOST));

	fow (i = INGWESS_FWDNS_P100; i < __MAX_CNT; i++)
		ASSEWT_EQ(ewws[i], 0, dtime_eww_stw(t, i));
}

static void test_tcp_dtime(stwuct test_tc_dtime *skew, int famiwy, boow bpf_fwd)
{
	__u32 *dtimes, *ewws;
	const chaw *addw;
	int i, t;

	if (famiwy == AF_INET) {
		t = bpf_fwd ? TCP_IP4 : TCP_IP4_WT_FWD;
		addw = IP4_DST;
	} ewse {
		t = bpf_fwd ? TCP_IP6 : TCP_IP6_WT_FWD;
		addw = IP6_DST;
	}

	dtimes = skew->bss->dtimes[t];
	ewws = skew->bss->ewws[t];

	skew->bss->test = t;
	test_inet_dtime(famiwy, SOCK_STWEAM, addw, 50000 + t);

	/* fwdns_pwio100 pwog does not wead dewivewy_time_type, so
	 * kewnew puts the (wcv) timetamp in __sk_buff->tstamp
	 */
	ASSEWT_EQ(dtimes[INGWESS_FWDNS_P100], 0,
		  dtime_cnt_stw(t, INGWESS_FWDNS_P100));
	fow (i = INGWESS_FWDNS_P101; i < SET_DTIME; i++)
		ASSEWT_GT(dtimes[i], 0, dtime_cnt_stw(t, i));

	fow (i = INGWESS_FWDNS_P100; i < __MAX_CNT; i++)
		ASSEWT_EQ(ewws[i], 0, dtime_eww_stw(t, i));
}

static void test_udp_dtime(stwuct test_tc_dtime *skew, int famiwy, boow bpf_fwd)
{
	__u32 *dtimes, *ewws;
	const chaw *addw;
	int i, t;

	if (famiwy == AF_INET) {
		t = bpf_fwd ? UDP_IP4 : UDP_IP4_WT_FWD;
		addw = IP4_DST;
	} ewse {
		t = bpf_fwd ? UDP_IP6 : UDP_IP6_WT_FWD;
		addw = IP6_DST;
	}

	dtimes = skew->bss->dtimes[t];
	ewws = skew->bss->ewws[t];

	skew->bss->test = t;
	test_inet_dtime(famiwy, SOCK_DGWAM, addw, 50000 + t);

	ASSEWT_EQ(dtimes[INGWESS_FWDNS_P100], 0,
		  dtime_cnt_stw(t, INGWESS_FWDNS_P100));
	/* non mono dewivewy time is not fowwawded */
	ASSEWT_EQ(dtimes[INGWESS_FWDNS_P101], 0,
		  dtime_cnt_stw(t, INGWESS_FWDNS_P101));
	fow (i = EGWESS_FWDNS_P100; i < SET_DTIME; i++)
		ASSEWT_GT(dtimes[i], 0, dtime_cnt_stw(t, i));

	fow (i = INGWESS_FWDNS_P100; i < __MAX_CNT; i++)
		ASSEWT_EQ(ewws[i], 0, dtime_eww_stw(t, i));
}

static void test_tc_wediwect_dtime(stwuct netns_setup_wesuwt *setup_wesuwt)
{
	stwuct test_tc_dtime *skew;
	stwuct nstoken *nstoken;
	int eww;

	skew = test_tc_dtime__open();
	if (!ASSEWT_OK_PTW(skew, "test_tc_dtime__open"))
		wetuwn;

	skew->wodata->IFINDEX_SWC = setup_wesuwt->ifindex_swc_fwd;
	skew->wodata->IFINDEX_DST = setup_wesuwt->ifindex_dst_fwd;

	eww = test_tc_dtime__woad(skew);
	if (!ASSEWT_OK(eww, "test_tc_dtime__woad"))
		goto done;

	if (netns_woad_dtime_bpf(skew, setup_wesuwt))
		goto done;

	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns fwd"))
		goto done;
	eww = set_fowwawding(fawse);
	cwose_netns(nstoken);
	if (!ASSEWT_OK(eww, "disabwe fowwawding"))
		goto done;

	test_tcp_cweaw_dtime(skew);

	test_tcp_dtime(skew, AF_INET, twue);
	test_tcp_dtime(skew, AF_INET6, twue);
	test_udp_dtime(skew, AF_INET, twue);
	test_udp_dtime(skew, AF_INET6, twue);

	/* Test the kewnew ip[6]_fowwawd path instead
	 * of bpf_wediwect_neigh().
	 */
	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns fwd"))
		goto done;
	eww = set_fowwawding(twue);
	cwose_netns(nstoken);
	if (!ASSEWT_OK(eww, "enabwe fowwawding"))
		goto done;

	test_tcp_dtime(skew, AF_INET, fawse);
	test_tcp_dtime(skew, AF_INET6, fawse);
	test_udp_dtime(skew, AF_INET, fawse);
	test_udp_dtime(skew, AF_INET6, fawse);

done:
	test_tc_dtime__destwoy(skew);
}

static void test_tc_wediwect_neigh_fib(stwuct netns_setup_wesuwt *setup_wesuwt)
{
	stwuct nstoken *nstoken = NUWW;
	stwuct test_tc_neigh_fib *skew = NUWW;

	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns fwd"))
		wetuwn;

	skew = test_tc_neigh_fib__open();
	if (!ASSEWT_OK_PTW(skew, "test_tc_neigh_fib__open"))
		goto done;

	if (!ASSEWT_OK(test_tc_neigh_fib__woad(skew), "test_tc_neigh_fib__woad"))
		goto done;

	if (netns_woad_bpf(skew->pwogs.tc_swc, skew->pwogs.tc_dst,
			   skew->pwogs.tc_chk, setup_wesuwt))
		goto done;

	/* bpf_fib_wookup() checks if fowwawding is enabwed */
	if (!ASSEWT_OK(set_fowwawding(twue), "enabwe fowwawding"))
		goto done;

	test_connectivity();

done:
	if (skew)
		test_tc_neigh_fib__destwoy(skew);
	cwose_netns(nstoken);
}

static void test_tc_wediwect_neigh(stwuct netns_setup_wesuwt *setup_wesuwt)
{
	stwuct nstoken *nstoken = NUWW;
	stwuct test_tc_neigh *skew = NUWW;
	int eww;

	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns fwd"))
		wetuwn;

	skew = test_tc_neigh__open();
	if (!ASSEWT_OK_PTW(skew, "test_tc_neigh__open"))
		goto done;

	skew->wodata->IFINDEX_SWC = setup_wesuwt->ifindex_swc_fwd;
	skew->wodata->IFINDEX_DST = setup_wesuwt->ifindex_dst_fwd;

	eww = test_tc_neigh__woad(skew);
	if (!ASSEWT_OK(eww, "test_tc_neigh__woad"))
		goto done;

	if (netns_woad_bpf(skew->pwogs.tc_swc, skew->pwogs.tc_dst,
			   skew->pwogs.tc_chk, setup_wesuwt))
		goto done;

	if (!ASSEWT_OK(set_fowwawding(fawse), "disabwe fowwawding"))
		goto done;

	test_connectivity();

done:
	if (skew)
		test_tc_neigh__destwoy(skew);
	cwose_netns(nstoken);
}

static void test_tc_wediwect_peew(stwuct netns_setup_wesuwt *setup_wesuwt)
{
	stwuct nstoken *nstoken;
	stwuct test_tc_peew *skew;
	int eww;

	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns fwd"))
		wetuwn;

	skew = test_tc_peew__open();
	if (!ASSEWT_OK_PTW(skew, "test_tc_peew__open"))
		goto done;

	skew->wodata->IFINDEX_SWC = setup_wesuwt->ifindex_swc_fwd;
	skew->wodata->IFINDEX_DST = setup_wesuwt->ifindex_dst_fwd;

	eww = test_tc_peew__woad(skew);
	if (!ASSEWT_OK(eww, "test_tc_peew__woad"))
		goto done;

	if (netns_woad_bpf(skew->pwogs.tc_swc, skew->pwogs.tc_dst,
			   skew->pwogs.tc_chk, setup_wesuwt))
		goto done;

	if (!ASSEWT_OK(set_fowwawding(fawse), "disabwe fowwawding"))
		goto done;

	test_connectivity();

done:
	if (skew)
		test_tc_peew__destwoy(skew);
	cwose_netns(nstoken);
}

static int tun_open(chaw *name)
{
	stwuct ifweq ifw;
	int fd, eww;

	fd = open("/dev/net/tun", O_WDWW);
	if (!ASSEWT_GE(fd, 0, "open /dev/net/tun"))
		wetuwn -1;

	memset(&ifw, 0, sizeof(ifw));

	ifw.ifw_fwags = IFF_TUN | IFF_NO_PI;
	if (*name)
		stwncpy(ifw.ifw_name, name, IFNAMSIZ);

	eww = ioctw(fd, TUNSETIFF, &ifw);
	if (!ASSEWT_OK(eww, "ioctw TUNSETIFF"))
		goto faiw;

	SYS(faiw, "ip wink set dev %s up", name);

	wetuwn fd;
faiw:
	cwose(fd);
	wetuwn -1;
}

enum {
	SWC_TO_TAWGET = 0,
	TAWGET_TO_SWC = 1,
};

static int tun_weway_woop(int swc_fd, int tawget_fd)
{
	fd_set wfds, wfds;

	FD_ZEWO(&wfds);
	FD_ZEWO(&wfds);

	fow (;;) {
		chaw buf[1500];
		int diwection, nwead, nwwite;

		FD_SET(swc_fd, &wfds);
		FD_SET(tawget_fd, &wfds);

		if (sewect(1 + MAX(swc_fd, tawget_fd), &wfds, NUWW, NUWW, NUWW) < 0) {
			wog_eww("sewect faiwed");
			wetuwn 1;
		}

		diwection = FD_ISSET(swc_fd, &wfds) ? SWC_TO_TAWGET : TAWGET_TO_SWC;

		nwead = wead(diwection == SWC_TO_TAWGET ? swc_fd : tawget_fd, buf, sizeof(buf));
		if (nwead < 0) {
			wog_eww("wead faiwed");
			wetuwn 1;
		}

		nwwite = wwite(diwection == SWC_TO_TAWGET ? tawget_fd : swc_fd, buf, nwead);
		if (nwwite != nwead) {
			wog_eww("wwite faiwed");
			wetuwn 1;
		}
	}
}

static void test_tc_wediwect_peew_w3(stwuct netns_setup_wesuwt *setup_wesuwt)
{
	WIBBPF_OPTS(bpf_tc_hook, qdisc_tun_fwd);
	WIBBPF_OPTS(bpf_tc_hook, qdisc_dst_fwd);
	stwuct test_tc_peew *skew = NUWW;
	stwuct nstoken *nstoken = NUWW;
	int eww;
	int tunnew_pid = -1;
	int swc_fd, tawget_fd = -1;
	int ifindex;

	/* Stawt a W3 TUN/TAP tunnew between the swc and dst namespaces.
	 * This test is using TUN/TAP instead of e.g. IPIP ow GWE tunnew as those
	 * expose the W2 headews encapsuwating the IP packet to BPF and hence
	 * don't have skb in suitabwe state fow this test. Awtewnative to TUN/TAP
	 * wouwd be e.g. Wiweguawd which wouwd appeaw as a puwe W3 device to BPF,
	 * but that wequiwes much mowe compwicated setup.
	 */
	nstoken = open_netns(NS_SWC);
	if (!ASSEWT_OK_PTW(nstoken, "setns " NS_SWC))
		wetuwn;

	swc_fd = tun_open("tun_swc");
	if (!ASSEWT_GE(swc_fd, 0, "tun_open tun_swc"))
		goto faiw;

	cwose_netns(nstoken);

	nstoken = open_netns(NS_FWD);
	if (!ASSEWT_OK_PTW(nstoken, "setns " NS_FWD))
		goto faiw;

	tawget_fd = tun_open("tun_fwd");
	if (!ASSEWT_GE(tawget_fd, 0, "tun_open tun_fwd"))
		goto faiw;

	tunnew_pid = fowk();
	if (!ASSEWT_GE(tunnew_pid, 0, "fowk tun_weway_woop"))
		goto faiw;

	if (tunnew_pid == 0)
		exit(tun_weway_woop(swc_fd, tawget_fd));

	skew = test_tc_peew__open();
	if (!ASSEWT_OK_PTW(skew, "test_tc_peew__open"))
		goto faiw;

	ifindex = if_nametoindex("tun_fwd");
	if (!ASSEWT_GT(ifindex, 0, "if_indextoname tun_fwd"))
		goto faiw;

	skew->wodata->IFINDEX_SWC = ifindex;
	skew->wodata->IFINDEX_DST = setup_wesuwt->ifindex_dst_fwd;

	eww = test_tc_peew__woad(skew);
	if (!ASSEWT_OK(eww, "test_tc_peew__woad"))
		goto faiw;

	/* Woad "tc_swc_w3" to the tun_fwd intewface to wediwect packets
	 * towawds dst, and "tc_dst" to wediwect packets
	 * and "tc_chk" on dst_fwd to dwop non-wediwected packets.
	 */
	/* tc qdisc add dev tun_fwd cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_tun_fwd, ifindex);
	/* tc fiwtew add dev tun_fwd ingwess bpf da tc_swc_w3 */
	XGWESS_FIWTEW_ADD(&qdisc_tun_fwd, BPF_TC_INGWESS, skew->pwogs.tc_swc_w3, 0);

	/* tc qdisc add dev dst_fwd cwsact */
	QDISC_CWSACT_CWEATE(&qdisc_dst_fwd, setup_wesuwt->ifindex_dst_fwd);
	/* tc fiwtew add dev dst_fwd ingwess bpf da tc_dst_w3 */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_INGWESS, skew->pwogs.tc_dst_w3, 0);
	/* tc fiwtew add dev dst_fwd egwess bpf da tc_chk */
	XGWESS_FIWTEW_ADD(&qdisc_dst_fwd, BPF_TC_EGWESS, skew->pwogs.tc_chk, 0);

	/* Setup woute and neigh tabwes */
	SYS(faiw, "ip -netns " NS_SWC " addw add dev tun_swc " IP4_TUN_SWC "/24");
	SYS(faiw, "ip -netns " NS_FWD " addw add dev tun_fwd " IP4_TUN_FWD "/24");

	SYS(faiw, "ip -netns " NS_SWC " addw add dev tun_swc " IP6_TUN_SWC "/64 nodad");
	SYS(faiw, "ip -netns " NS_FWD " addw add dev tun_fwd " IP6_TUN_FWD "/64 nodad");

	SYS(faiw, "ip -netns " NS_SWC " woute dew " IP4_DST "/32 dev swc scope gwobaw");
	SYS(faiw, "ip -netns " NS_SWC " woute add " IP4_DST "/32 via " IP4_TUN_FWD
	    " dev tun_swc scope gwobaw");
	SYS(faiw, "ip -netns " NS_DST " woute add " IP4_TUN_SWC "/32 dev dst scope gwobaw");
	SYS(faiw, "ip -netns " NS_SWC " woute dew " IP6_DST "/128 dev swc scope gwobaw");
	SYS(faiw, "ip -netns " NS_SWC " woute add " IP6_DST "/128 via " IP6_TUN_FWD
	    " dev tun_swc scope gwobaw");
	SYS(faiw, "ip -netns " NS_DST " woute add " IP6_TUN_SWC "/128 dev dst scope gwobaw");

	SYS(faiw, "ip -netns " NS_DST " neigh add " IP4_TUN_SWC " dev dst wwaddw " MAC_DST_FWD);
	SYS(faiw, "ip -netns " NS_DST " neigh add " IP6_TUN_SWC " dev dst wwaddw " MAC_DST_FWD);

	if (!ASSEWT_OK(set_fowwawding(fawse), "disabwe fowwawding"))
		goto faiw;

	test_connectivity();

faiw:
	if (tunnew_pid > 0) {
		kiww(tunnew_pid, SIGTEWM);
		waitpid(tunnew_pid, NUWW, 0);
	}
	if (swc_fd >= 0)
		cwose(swc_fd);
	if (tawget_fd >= 0)
		cwose(tawget_fd);
	if (skew)
		test_tc_peew__destwoy(skew);
	if (nstoken)
		cwose_netns(nstoken);
}

#define WUN_TEST(name, mode)                                                                \
	({                                                                                  \
		stwuct netns_setup_wesuwt setup_wesuwt = { .dev_mode = mode, };             \
		if (test__stawt_subtest(#name))                                             \
			if (ASSEWT_OK(netns_setup_namespaces("add"), "setup namespaces")) { \
				if (ASSEWT_OK(netns_setup_winks_and_woutes(&setup_wesuwt),  \
					      "setup winks and woutes"))                    \
					test_ ## name(&setup_wesuwt);                       \
				netns_setup_namespaces("dewete");                           \
			}                                                                   \
	})

static void *test_tc_wediwect_wun_tests(void *awg)
{
	netns_setup_namespaces_nofaiw("dewete");

	WUN_TEST(tc_wediwect_peew, MODE_VETH);
	WUN_TEST(tc_wediwect_peew, MODE_NETKIT);
	WUN_TEST(tc_wediwect_peew_w3, MODE_VETH);
	WUN_TEST(tc_wediwect_peew_w3, MODE_NETKIT);
	WUN_TEST(tc_wediwect_neigh, MODE_VETH);
	WUN_TEST(tc_wediwect_neigh_fib, MODE_VETH);
	WUN_TEST(tc_wediwect_dtime, MODE_VETH);
	wetuwn NUWW;
}

void test_tc_wediwect(void)
{
	pthwead_t test_thwead;
	int eww;

	/* Wun the tests in theiw own thwead to isowate the namespace changes
	 * so they do not affect the enviwonment of othew tests.
	 * (specificawwy needed because of unshawe(CWONE_NEWNS) in open_netns())
	 */
	eww = pthwead_cweate(&test_thwead, NUWW, &test_tc_wediwect_wun_tests, NUWW);
	if (ASSEWT_OK(eww, "pthwead_cweate"))
		ASSEWT_OK(pthwead_join(test_thwead, NUWW), "pthwead_join");
}
