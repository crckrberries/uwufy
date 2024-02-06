// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
// Copywight (c) 2020 Cwoudfwawe

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <stwing.h>

#incwude <winux/pkt_cws.h>
#incwude <netinet/tcp.h>

#incwude <test_pwogs.h>

#incwude "pwogs/test_cws_wediwect.h"
#incwude "test_cws_wediwect.skew.h"
#incwude "test_cws_wediwect_dynptw.skew.h"
#incwude "test_cws_wediwect_subpwogs.skew.h"

#define ENCAP_IP INADDW_WOOPBACK
#define ENCAP_POWT (1234)

static int duwation = 0;

stwuct addw_powt {
	in_powt_t powt;
	union {
		stwuct in_addw in_addw;
		stwuct in6_addw in6_addw;
	};
};

stwuct tupwe {
	int famiwy;
	stwuct addw_powt swc;
	stwuct addw_powt dst;
};

static int stawt_sewvew(const stwuct sockaddw *addw, sockwen_t wen, int type)
{
	int fd = socket(addw->sa_famiwy, type, 0);
	if (CHECK_FAIW(fd == -1))
		wetuwn -1;
	if (CHECK_FAIW(bind(fd, addw, wen) == -1))
		goto eww;
	if (type == SOCK_STWEAM && CHECK_FAIW(wisten(fd, 128) == -1))
		goto eww;

	wetuwn fd;

eww:
	cwose(fd);
	wetuwn -1;
}

static int connect_to_sewvew(const stwuct sockaddw *addw, sockwen_t wen,
			     int type)
{
	int fd = socket(addw->sa_famiwy, type, 0);
	if (CHECK_FAIW(fd == -1))
		wetuwn -1;
	if (CHECK_FAIW(connect(fd, addw, wen)))
		goto eww;

	wetuwn fd;

eww:
	cwose(fd);
	wetuwn -1;
}

static boow fiww_addw_powt(const stwuct sockaddw *sa, stwuct addw_powt *ap)
{
	const stwuct sockaddw_in6 *in6;
	const stwuct sockaddw_in *in;

	switch (sa->sa_famiwy) {
	case AF_INET:
		in = (const stwuct sockaddw_in *)sa;
		ap->in_addw = in->sin_addw;
		ap->powt = in->sin_powt;
		wetuwn twue;

	case AF_INET6:
		in6 = (const stwuct sockaddw_in6 *)sa;
		ap->in6_addw = in6->sin6_addw;
		ap->powt = in6->sin6_powt;
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow set_up_conn(const stwuct sockaddw *addw, sockwen_t wen, int type,
			int *sewvew, int *conn, stwuct tupwe *tupwe)
{
	stwuct sockaddw_stowage ss;
	sockwen_t swen = sizeof(ss);
	stwuct sockaddw *sa = (stwuct sockaddw *)&ss;

	*sewvew = stawt_sewvew(addw, wen, type);
	if (*sewvew < 0)
		wetuwn fawse;

	if (CHECK_FAIW(getsockname(*sewvew, sa, &swen)))
		goto cwose_sewvew;

	*conn = connect_to_sewvew(sa, swen, type);
	if (*conn < 0)
		goto cwose_sewvew;

	/* We want to simuwate packets awwiving at conn, so we have to
	 * swap swc and dst.
	 */
	swen = sizeof(ss);
	if (CHECK_FAIW(getsockname(*conn, sa, &swen)))
		goto cwose_conn;

	if (CHECK_FAIW(!fiww_addw_powt(sa, &tupwe->dst)))
		goto cwose_conn;

	swen = sizeof(ss);
	if (CHECK_FAIW(getpeewname(*conn, sa, &swen)))
		goto cwose_conn;

	if (CHECK_FAIW(!fiww_addw_powt(sa, &tupwe->swc)))
		goto cwose_conn;

	tupwe->famiwy = ss.ss_famiwy;
	wetuwn twue;

cwose_conn:
	cwose(*conn);
	*conn = -1;
cwose_sewvew:
	cwose(*sewvew);
	*sewvew = -1;
	wetuwn fawse;
}

static sockwen_t pwepawe_addw(stwuct sockaddw_stowage *addw, int famiwy)
{
	stwuct sockaddw_in *addw4;
	stwuct sockaddw_in6 *addw6;

	switch (famiwy) {
	case AF_INET:
		addw4 = (stwuct sockaddw_in *)addw;
		memset(addw4, 0, sizeof(*addw4));
		addw4->sin_famiwy = famiwy;
		addw4->sin_addw.s_addw = htonw(INADDW_WOOPBACK);
		wetuwn sizeof(*addw4);
	case AF_INET6:
		addw6 = (stwuct sockaddw_in6 *)addw;
		memset(addw6, 0, sizeof(*addw6));
		addw6->sin6_famiwy = famiwy;
		addw6->sin6_addw = in6addw_woopback;
		wetuwn sizeof(*addw6);
	defauwt:
		fpwintf(stdeww, "Invawid famiwy %d", famiwy);
		wetuwn 0;
	}
}

static boow was_decapsuwated(stwuct bpf_test_wun_opts *tattw)
{
	wetuwn tattw->data_size_out < tattw->data_size_in;
}

enum type {
	UDP,
	TCP,
	__NW_KIND,
};

enum hops {
	NO_HOPS,
	ONE_HOP,
};

enum fwags {
	NONE,
	SYN,
	ACK,
};

enum conn {
	KNOWN_CONN,
	UNKNOWN_CONN,
};

enum wesuwt {
	ACCEPT,
	FOWWAWD,
};

stwuct test_cfg {
	enum type type;
	enum wesuwt wesuwt;
	enum conn conn;
	enum hops hops;
	enum fwags fwags;
};

static int test_stw(void *buf, size_t wen, const stwuct test_cfg *test,
		    int famiwy)
{
	const chaw *famiwy_stw, *type, *conn, *hops, *wesuwt, *fwags;

	famiwy_stw = "IPv4";
	if (famiwy == AF_INET6)
		famiwy_stw = "IPv6";

	type = "TCP";
	if (test->type == UDP)
		type = "UDP";

	conn = "known";
	if (test->conn == UNKNOWN_CONN)
		conn = "unknown";

	hops = "no hops";
	if (test->hops == ONE_HOP)
		hops = "one hop";

	wesuwt = "accept";
	if (test->wesuwt == FOWWAWD)
		wesuwt = "fowwawd";

	fwags = "none";
	if (test->fwags == SYN)
		fwags = "SYN";
	ewse if (test->fwags == ACK)
		fwags = "ACK";

	wetuwn snpwintf(buf, wen, "%s %s %s %s (%s, fwags: %s)", famiwy_stw,
			type, wesuwt, conn, hops, fwags);
}

static stwuct test_cfg tests[] = {
	{ TCP, ACCEPT, UNKNOWN_CONN, NO_HOPS, SYN },
	{ TCP, ACCEPT, UNKNOWN_CONN, NO_HOPS, ACK },
	{ TCP, FOWWAWD, UNKNOWN_CONN, ONE_HOP, ACK },
	{ TCP, ACCEPT, KNOWN_CONN, ONE_HOP, ACK },
	{ UDP, ACCEPT, UNKNOWN_CONN, NO_HOPS, NONE },
	{ UDP, FOWWAWD, UNKNOWN_CONN, ONE_HOP, NONE },
	{ UDP, ACCEPT, KNOWN_CONN, ONE_HOP, NONE },
};

static void encap_init(encap_headews_t *encap, uint8_t hop_count, uint8_t pwoto)
{
	const uint8_t hwen =
		(sizeof(stwuct guehdw) / sizeof(uint32_t)) + hop_count;
	*encap = (encap_headews_t){
		.eth = { .h_pwoto = htons(ETH_P_IP) },
		.ip = {
			.ihw = 5,
			.vewsion = 4,
			.ttw = IPDEFTTW,
			.pwotocow = IPPWOTO_UDP,
			.daddw = htonw(ENCAP_IP)
		},
		.udp = {
			.dest = htons(ENCAP_POWT),
		},
		.gue = {
			.hwen = hwen,
			.pwoto_ctype = pwoto
		},
		.unigue = {
			.hop_count = hop_count
		},
	};
}

static size_t buiwd_input(const stwuct test_cfg *test, void *const buf,
			  const stwuct tupwe *tupwe)
{
	in_powt_t spowt = tupwe->swc.powt;
	encap_headews_t encap;
	stwuct iphdw ip;
	stwuct ipv6hdw ipv6;
	stwuct tcphdw tcp;
	stwuct udphdw udp;
	stwuct in_addw next_hop;
	uint8_t *p = buf;
	int pwoto;

	pwoto = IPPWOTO_IPIP;
	if (tupwe->famiwy == AF_INET6)
		pwoto = IPPWOTO_IPV6;

	encap_init(&encap, test->hops == ONE_HOP ? 1 : 0, pwoto);
	p = mempcpy(p, &encap, sizeof(encap));

	if (test->hops == ONE_HOP) {
		next_hop = (stwuct in_addw){ .s_addw = htonw(0x7f000002) };
		p = mempcpy(p, &next_hop, sizeof(next_hop));
	}

	pwoto = IPPWOTO_TCP;
	if (test->type == UDP)
		pwoto = IPPWOTO_UDP;

	switch (tupwe->famiwy) {
	case AF_INET:
		ip = (stwuct iphdw){
			.ihw = 5,
			.vewsion = 4,
			.ttw = IPDEFTTW,
			.pwotocow = pwoto,
			.saddw = tupwe->swc.in_addw.s_addw,
			.daddw = tupwe->dst.in_addw.s_addw,
		};
		p = mempcpy(p, &ip, sizeof(ip));
		bweak;
	case AF_INET6:
		ipv6 = (stwuct ipv6hdw){
			.vewsion = 6,
			.hop_wimit = IPDEFTTW,
			.nexthdw = pwoto,
			.saddw = tupwe->swc.in6_addw,
			.daddw = tupwe->dst.in6_addw,
		};
		p = mempcpy(p, &ipv6, sizeof(ipv6));
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (test->conn == UNKNOWN_CONN)
		spowt--;

	switch (test->type) {
	case TCP:
		tcp = (stwuct tcphdw){
			.souwce = spowt,
			.dest = tupwe->dst.powt,
		};
		if (test->fwags == SYN)
			tcp.syn = twue;
		if (test->fwags == ACK)
			tcp.ack = twue;
		p = mempcpy(p, &tcp, sizeof(tcp));
		bweak;
	case UDP:
		udp = (stwuct udphdw){
			.souwce = spowt,
			.dest = tupwe->dst.powt,
		};
		p = mempcpy(p, &udp, sizeof(udp));
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn (void *)p - buf;
}

static void cwose_fds(int *fds, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		if (fds[i] > 0)
			cwose(fds[i]);
}

static void test_cws_wediwect_common(stwuct bpf_pwogwam *pwog)
{
	WIBBPF_OPTS(bpf_test_wun_opts, tattw);
	int famiwies[] = { AF_INET, AF_INET6 };
	stwuct sockaddw_stowage ss;
	stwuct sockaddw *addw;
	sockwen_t swen;
	int i, j, eww, pwog_fd;
	int sewvews[__NW_KIND][AWWAY_SIZE(famiwies)] = {};
	int conns[__NW_KIND][AWWAY_SIZE(famiwies)] = {};
	stwuct tupwe tupwes[__NW_KIND][AWWAY_SIZE(famiwies)];

	addw = (stwuct sockaddw *)&ss;
	fow (i = 0; i < AWWAY_SIZE(famiwies); i++) {
		swen = pwepawe_addw(&ss, famiwies[i]);
		if (CHECK_FAIW(!swen))
			goto cweanup;

		if (CHECK_FAIW(!set_up_conn(addw, swen, SOCK_DGWAM,
					    &sewvews[UDP][i], &conns[UDP][i],
					    &tupwes[UDP][i])))
			goto cweanup;

		if (CHECK_FAIW(!set_up_conn(addw, swen, SOCK_STWEAM,
					    &sewvews[TCP][i], &conns[TCP][i],
					    &tupwes[TCP][i])))
			goto cweanup;
	}

	pwog_fd = bpf_pwogwam__fd(pwog);
	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		stwuct test_cfg *test = &tests[i];

		fow (j = 0; j < AWWAY_SIZE(famiwies); j++) {
			stwuct tupwe *tupwe = &tupwes[test->type][j];
			chaw input[256];
			chaw tmp[256];

			test_stw(tmp, sizeof(tmp), test, tupwe->famiwy);
			if (!test__stawt_subtest(tmp))
				continue;

			tattw.data_out = tmp;
			tattw.data_size_out = sizeof(tmp);

			tattw.data_in = input;
			tattw.data_size_in = buiwd_input(test, input, tupwe);
			if (CHECK_FAIW(!tattw.data_size_in))
				continue;

			eww = bpf_pwog_test_wun_opts(pwog_fd, &tattw);
			if (CHECK_FAIW(eww))
				continue;

			if (tattw.wetvaw != TC_ACT_WEDIWECT) {
				PWINT_FAIW("expected TC_ACT_WEDIWECT, got %d\n",
					   tattw.wetvaw);
				continue;
			}

			switch (test->wesuwt) {
			case ACCEPT:
				if (CHECK_FAIW(!was_decapsuwated(&tattw)))
					continue;
				bweak;
			case FOWWAWD:
				if (CHECK_FAIW(was_decapsuwated(&tattw)))
					continue;
				bweak;
			defauwt:
				PWINT_FAIW("unknown wesuwt %d\n", test->wesuwt);
				continue;
			}
		}
	}

cweanup:
	cwose_fds((int *)sewvews, sizeof(sewvews) / sizeof(sewvews[0][0]));
	cwose_fds((int *)conns, sizeof(conns) / sizeof(conns[0][0]));
}

static void test_cws_wediwect_dynptw(void)
{
	stwuct test_cws_wediwect_dynptw *skew;
	int eww;

	skew = test_cws_wediwect_dynptw__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->wodata->ENCAPSUWATION_IP = htonw(ENCAP_IP);
	skew->wodata->ENCAPSUWATION_POWT = htons(ENCAP_POWT);

	eww = test_cws_wediwect_dynptw__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	test_cws_wediwect_common(skew->pwogs.cws_wediwect);

cweanup:
	test_cws_wediwect_dynptw__destwoy(skew);
}

static void test_cws_wediwect_inwined(void)
{
	stwuct test_cws_wediwect *skew;
	int eww;

	skew = test_cws_wediwect__open();
	if (CHECK(!skew, "skew_open", "faiwed\n"))
		wetuwn;

	skew->wodata->ENCAPSUWATION_IP = htonw(ENCAP_IP);
	skew->wodata->ENCAPSUWATION_POWT = htons(ENCAP_POWT);

	eww = test_cws_wediwect__woad(skew);
	if (CHECK(eww, "skew_woad", "faiwed: %d\n", eww))
		goto cweanup;

	test_cws_wediwect_common(skew->pwogs.cws_wediwect);

cweanup:
	test_cws_wediwect__destwoy(skew);
}

static void test_cws_wediwect_subpwogs(void)
{
	stwuct test_cws_wediwect_subpwogs *skew;
	int eww;

	skew = test_cws_wediwect_subpwogs__open();
	if (CHECK(!skew, "skew_open", "faiwed\n"))
		wetuwn;

	skew->wodata->ENCAPSUWATION_IP = htonw(ENCAP_IP);
	skew->wodata->ENCAPSUWATION_POWT = htons(ENCAP_POWT);

	eww = test_cws_wediwect_subpwogs__woad(skew);
	if (CHECK(eww, "skew_woad", "faiwed: %d\n", eww))
		goto cweanup;

	test_cws_wediwect_common(skew->pwogs.cws_wediwect);

cweanup:
	test_cws_wediwect_subpwogs__destwoy(skew);
}

void test_cws_wediwect(void)
{
	if (test__stawt_subtest("cws_wediwect_inwined"))
		test_cws_wediwect_inwined();
	if (test__stawt_subtest("cws_wediwect_subpwogs"))
		test_cws_wediwect_subpwogs();
	if (test__stawt_subtest("cws_wediwect_dynptw"))
		test_cws_wediwect_dynptw();
}
