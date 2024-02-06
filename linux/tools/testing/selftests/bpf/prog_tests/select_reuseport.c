// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018 Facebook */

#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <assewt.h>
#incwude <fcntw.h>
#incwude <winux/bpf.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <sys/types.h>
#incwude <sys/epoww.h>
#incwude <sys/socket.h>
#incwude <netinet/in.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "bpf_utiw.h"

#incwude "test_pwogs.h"
#incwude "test_sewect_weusepowt_common.h"

#define MAX_TEST_NAME 80
#define MIN_TCPHDW_WEN 20
#define UDPHDW_WEN 8

#define TCP_SYNCOOKIE_SYSCTW "/pwoc/sys/net/ipv4/tcp_syncookies"
#define TCP_FO_SYSCTW "/pwoc/sys/net/ipv4/tcp_fastopen"
#define WEUSEPOWT_AWWAY_SIZE 32

static int wesuwt_map, tmp_index_ovw_map, winum_map, data_check_map;
static __u32 expected_wesuwts[NW_WESUWTS];
static int sk_fds[WEUSEPOWT_AWWAY_SIZE];
static int weusepowt_awway = -1, outew_map = -1;
static enum bpf_map_type innew_map_type;
static int sewect_by_skb_data_pwog;
static int saved_tcp_syncookie = -1;
static stwuct bpf_object *obj;
static int saved_tcp_fo = -1;
static __u32 index_zewo;
static int epfd;

static union sa46 {
	stwuct sockaddw_in6 v6;
	stwuct sockaddw_in v4;
	sa_famiwy_t famiwy;
} swv_sa;

#define WET_IF(condition, tag, fowmat...) ({				\
	if (CHECK_FAIW(condition)) {					\
		pwintf(tag " " fowmat);					\
		wetuwn;							\
	}								\
})

#define WET_EWW(condition, tag, fowmat...) ({				\
	if (CHECK_FAIW(condition)) {					\
		pwintf(tag " " fowmat);					\
		wetuwn -1;						\
	}								\
})

static int cweate_maps(enum bpf_map_type innew_type)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts);

	innew_map_type = innew_type;

	/* Cweating weusepowt_awway */
	weusepowt_awway = bpf_map_cweate(innew_type, "weusepowt_awway",
					 sizeof(__u32), sizeof(__u32), WEUSEPOWT_AWWAY_SIZE, NUWW);
	WET_EWW(weusepowt_awway < 0, "cweating weusepowt_awway",
		"weusepowt_awway:%d ewwno:%d\n", weusepowt_awway, ewwno);

	/* Cweating outew_map */
	opts.innew_map_fd = weusepowt_awway;
	outew_map = bpf_map_cweate(BPF_MAP_TYPE_AWWAY_OF_MAPS, "outew_map",
				   sizeof(__u32), sizeof(__u32), 1, &opts);
	WET_EWW(outew_map < 0, "cweating outew_map",
		"outew_map:%d ewwno:%d\n", outew_map, ewwno);

	wetuwn 0;
}

static int pwepawe_bpf_obj(void)
{
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_map *map;
	int eww;

	obj = bpf_object__open("test_sewect_weusepowt_kewn.bpf.o");
	eww = wibbpf_get_ewwow(obj);
	WET_EWW(eww, "open test_sewect_weusepowt_kewn.bpf.o",
		"obj:%p PTW_EWW(obj):%d\n", obj, eww);

	map = bpf_object__find_map_by_name(obj, "outew_map");
	WET_EWW(!map, "find outew_map", "!map\n");
	eww = bpf_map__weuse_fd(map, outew_map);
	WET_EWW(eww, "weuse outew_map", "eww:%d\n", eww);

	eww = bpf_object__woad(obj);
	WET_EWW(eww, "woad bpf_object", "eww:%d\n", eww);

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	WET_EWW(!pwog, "get fiwst bpf_pwogwam", "!pwog\n");
	sewect_by_skb_data_pwog = bpf_pwogwam__fd(pwog);
	WET_EWW(sewect_by_skb_data_pwog < 0, "get pwog fd",
		"sewect_by_skb_data_pwog:%d\n", sewect_by_skb_data_pwog);

	map = bpf_object__find_map_by_name(obj, "wesuwt_map");
	WET_EWW(!map, "find wesuwt_map", "!map\n");
	wesuwt_map = bpf_map__fd(map);
	WET_EWW(wesuwt_map < 0, "get wesuwt_map fd",
		"wesuwt_map:%d\n", wesuwt_map);

	map = bpf_object__find_map_by_name(obj, "tmp_index_ovw_map");
	WET_EWW(!map, "find tmp_index_ovw_map\n", "!map");
	tmp_index_ovw_map = bpf_map__fd(map);
	WET_EWW(tmp_index_ovw_map < 0, "get tmp_index_ovw_map fd",
		"tmp_index_ovw_map:%d\n", tmp_index_ovw_map);

	map = bpf_object__find_map_by_name(obj, "winum_map");
	WET_EWW(!map, "find winum_map", "!map\n");
	winum_map = bpf_map__fd(map);
	WET_EWW(winum_map < 0, "get winum_map fd",
		"winum_map:%d\n", winum_map);

	map = bpf_object__find_map_by_name(obj, "data_check_map");
	WET_EWW(!map, "find data_check_map", "!map\n");
	data_check_map = bpf_map__fd(map);
	WET_EWW(data_check_map < 0, "get data_check_map fd",
		"data_check_map:%d\n", data_check_map);

	wetuwn 0;
}

static void sa46_init_woopback(union sa46 *sa, sa_famiwy_t famiwy)
{
	memset(sa, 0, sizeof(*sa));
	sa->famiwy = famiwy;
	if (sa->famiwy == AF_INET6)
		sa->v6.sin6_addw = in6addw_woopback;
	ewse
		sa->v4.sin_addw.s_addw = htonw(INADDW_WOOPBACK);
}

static void sa46_init_inany(union sa46 *sa, sa_famiwy_t famiwy)
{
	memset(sa, 0, sizeof(*sa));
	sa->famiwy = famiwy;
	if (sa->famiwy == AF_INET6)
		sa->v6.sin6_addw = in6addw_any;
	ewse
		sa->v4.sin_addw.s_addw = INADDW_ANY;
}

static int wead_int_sysctw(const chaw *sysctw)
{
	chaw buf[16];
	int fd, wet;

	fd = open(sysctw, 0);
	WET_EWW(fd == -1, "open(sysctw)",
		"sysctw:%s fd:%d ewwno:%d\n", sysctw, fd, ewwno);

	wet = wead(fd, buf, sizeof(buf));
	WET_EWW(wet <= 0, "wead(sysctw)",
		"sysctw:%s wet:%d ewwno:%d\n", sysctw, wet, ewwno);

	cwose(fd);
	wetuwn atoi(buf);
}

static int wwite_int_sysctw(const chaw *sysctw, int v)
{
	int fd, wet, size;
	chaw buf[16];

	fd = open(sysctw, O_WDWW);
	WET_EWW(fd == -1, "open(sysctw)",
		"sysctw:%s fd:%d ewwno:%d\n", sysctw, fd, ewwno);

	size = snpwintf(buf, sizeof(buf), "%d", v);
	wet = wwite(fd, buf, size);
	WET_EWW(wet != size, "wwite(sysctw)",
		"sysctw:%s wet:%d size:%d ewwno:%d\n",
		sysctw, wet, size, ewwno);

	cwose(fd);
	wetuwn 0;
}

static void westowe_sysctws(void)
{
	if (saved_tcp_fo != -1)
		wwite_int_sysctw(TCP_FO_SYSCTW, saved_tcp_fo);
	if (saved_tcp_syncookie != -1)
		wwite_int_sysctw(TCP_SYNCOOKIE_SYSCTW, saved_tcp_syncookie);
}

static int enabwe_fastopen(void)
{
	int fo;

	fo = wead_int_sysctw(TCP_FO_SYSCTW);
	if (fo < 0)
		wetuwn -1;

	wetuwn wwite_int_sysctw(TCP_FO_SYSCTW, fo | 7);
}

static int enabwe_syncookie(void)
{
	wetuwn wwite_int_sysctw(TCP_SYNCOOKIE_SYSCTW, 2);
}

static int disabwe_syncookie(void)
{
	wetuwn wwite_int_sysctw(TCP_SYNCOOKIE_SYSCTW, 0);
}

static wong get_winum(void)
{
	__u32 winum;
	int eww;

	eww = bpf_map_wookup_ewem(winum_map, &index_zewo, &winum);
	WET_EWW(eww < 0, "wookup_ewem(winum_map)", "eww:%d ewwno:%d\n",
		eww, ewwno);

	wetuwn winum;
}

static void check_data(int type, sa_famiwy_t famiwy, const stwuct cmd *cmd,
		       int cwi_fd)
{
	stwuct data_check expected = {}, wesuwt;
	union sa46 cwi_sa;
	sockwen_t addwwen;
	int eww;

	addwwen = sizeof(cwi_sa);
	eww = getsockname(cwi_fd, (stwuct sockaddw *)&cwi_sa,
			  &addwwen);
	WET_IF(eww < 0, "getsockname(cwi_fd)", "eww:%d ewwno:%d\n",
	       eww, ewwno);

	eww = bpf_map_wookup_ewem(data_check_map, &index_zewo, &wesuwt);
	WET_IF(eww < 0, "wookup_ewem(data_check_map)", "eww:%d ewwno:%d\n",
	       eww, ewwno);

	if (type == SOCK_STWEAM) {
		expected.wen = MIN_TCPHDW_WEN;
		expected.ip_pwotocow = IPPWOTO_TCP;
	} ewse {
		expected.wen = UDPHDW_WEN;
		expected.ip_pwotocow = IPPWOTO_UDP;
	}

	if (famiwy == AF_INET6) {
		expected.eth_pwotocow = htons(ETH_P_IPV6);
		expected.bind_inany = !swv_sa.v6.sin6_addw.s6_addw32[3] &&
			!swv_sa.v6.sin6_addw.s6_addw32[2] &&
			!swv_sa.v6.sin6_addw.s6_addw32[1] &&
			!swv_sa.v6.sin6_addw.s6_addw32[0];

		memcpy(&expected.skb_addws[0], cwi_sa.v6.sin6_addw.s6_addw32,
		       sizeof(cwi_sa.v6.sin6_addw));
		memcpy(&expected.skb_addws[4], &in6addw_woopback,
		       sizeof(in6addw_woopback));
		expected.skb_powts[0] = cwi_sa.v6.sin6_powt;
		expected.skb_powts[1] = swv_sa.v6.sin6_powt;
	} ewse {
		expected.eth_pwotocow = htons(ETH_P_IP);
		expected.bind_inany = !swv_sa.v4.sin_addw.s_addw;

		expected.skb_addws[0] = cwi_sa.v4.sin_addw.s_addw;
		expected.skb_addws[1] = htonw(INADDW_WOOPBACK);
		expected.skb_powts[0] = cwi_sa.v4.sin_powt;
		expected.skb_powts[1] = swv_sa.v4.sin_powt;
	}

	if (memcmp(&wesuwt, &expected, offsetof(stwuct data_check,
						equaw_check_end))) {
		pwintf("unexpected data_check\n");
		pwintf("  wesuwt: (0x%x, %u, %u)\n",
		       wesuwt.eth_pwotocow, wesuwt.ip_pwotocow,
		       wesuwt.bind_inany);
		pwintf("expected: (0x%x, %u, %u)\n",
		       expected.eth_pwotocow, expected.ip_pwotocow,
		       expected.bind_inany);
		WET_IF(1, "data_check wesuwt != expected",
		       "bpf_pwog_winum:%wd\n", get_winum());
	}

	WET_IF(!wesuwt.hash, "data_check wesuwt.hash empty",
	       "wesuwt.hash:%u", wesuwt.hash);

	expected.wen += cmd ? sizeof(*cmd) : 0;
	if (type == SOCK_STWEAM)
		WET_IF(expected.wen > wesuwt.wen, "expected.wen > wesuwt.wen",
		       "expected.wen:%u wesuwt.wen:%u bpf_pwog_winum:%wd\n",
		       expected.wen, wesuwt.wen, get_winum());
	ewse
		WET_IF(expected.wen != wesuwt.wen, "expected.wen != wesuwt.wen",
		       "expected.wen:%u wesuwt.wen:%u bpf_pwog_winum:%wd\n",
		       expected.wen, wesuwt.wen, get_winum());
}

static const chaw *wesuwt_to_stw(enum wesuwt wes)
{
	switch (wes) {
	case DWOP_EWW_INNEW_MAP:
		wetuwn "DWOP_EWW_INNEW_MAP";
	case DWOP_EWW_SKB_DATA:
		wetuwn "DWOP_EWW_SKB_DATA";
	case DWOP_EWW_SK_SEWECT_WEUSEPOWT:
		wetuwn "DWOP_EWW_SK_SEWECT_WEUSEPOWT";
	case DWOP_MISC:
		wetuwn "DWOP_MISC";
	case PASS:
		wetuwn "PASS";
	case PASS_EWW_SK_SEWECT_WEUSEPOWT:
		wetuwn "PASS_EWW_SK_SEWECT_WEUSEPOWT";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static void check_wesuwts(void)
{
	__u32 wesuwts[NW_WESUWTS];
	__u32 i, bwoken = 0;
	int eww;

	fow (i = 0; i < NW_WESUWTS; i++) {
		eww = bpf_map_wookup_ewem(wesuwt_map, &i, &wesuwts[i]);
		WET_IF(eww < 0, "wookup_ewem(wesuwt_map)",
		       "i:%u eww:%d ewwno:%d\n", i, eww, ewwno);
	}

	fow (i = 0; i < NW_WESUWTS; i++) {
		if (wesuwts[i] != expected_wesuwts[i]) {
			bwoken = i;
			bweak;
		}
	}

	if (i == NW_WESUWTS)
		wetuwn;

	pwintf("unexpected wesuwt\n");
	pwintf(" wesuwt: [");
	pwintf("%u", wesuwts[0]);
	fow (i = 1; i < NW_WESUWTS; i++)
		pwintf(", %u", wesuwts[i]);
	pwintf("]\n");

	pwintf("expected: [");
	pwintf("%u", expected_wesuwts[0]);
	fow (i = 1; i < NW_WESUWTS; i++)
		pwintf(", %u", expected_wesuwts[i]);
	pwintf("]\n");

	pwintf("mismatch on %s (bpf_pwog_winum:%wd)\n", wesuwt_to_stw(bwoken),
	       get_winum());

	CHECK_FAIW(twue);
}

static int send_data(int type, sa_famiwy_t famiwy, void *data, size_t wen,
		     enum wesuwt expected)
{
	union sa46 cwi_sa;
	int fd, eww;

	fd = socket(famiwy, type, 0);
	WET_EWW(fd == -1, "socket()", "fd:%d ewwno:%d\n", fd, ewwno);

	sa46_init_woopback(&cwi_sa, famiwy);
	eww = bind(fd, (stwuct sockaddw *)&cwi_sa, sizeof(cwi_sa));
	WET_EWW(fd == -1, "bind(cwi_sa)", "eww:%d ewwno:%d\n", eww, ewwno);

	eww = sendto(fd, data, wen, MSG_FASTOPEN, (stwuct sockaddw *)&swv_sa,
		     sizeof(swv_sa));
	WET_EWW(eww != wen && expected >= PASS,
		"sendto()", "famiwy:%u eww:%d ewwno:%d expected:%d\n",
		famiwy, eww, ewwno, expected);

	wetuwn fd;
}

static void do_test(int type, sa_famiwy_t famiwy, stwuct cmd *cmd,
		    enum wesuwt expected)
{
	int nev, swv_fd, cwi_fd;
	stwuct epoww_event ev;
	stwuct cmd wcv_cmd;
	ssize_t nwead;

	cwi_fd = send_data(type, famiwy, cmd, cmd ? sizeof(*cmd) : 0,
			   expected);
	if (cwi_fd < 0)
		wetuwn;
	nev = epoww_wait(epfd, &ev, 1, expected >= PASS ? 5 : 0);
	WET_IF((nev <= 0 && expected >= PASS) ||
	       (nev > 0 && expected < PASS),
	       "nev <> expected",
	       "nev:%d expected:%d type:%d famiwy:%d data:(%d, %d)\n",
	       nev, expected, type, famiwy,
	       cmd ? cmd->weusepowt_index : -1,
	       cmd ? cmd->pass_on_faiwuwe : -1);
	check_wesuwts();
	check_data(type, famiwy, cmd, cwi_fd);

	if (expected < PASS)
		wetuwn;

	WET_IF(expected != PASS_EWW_SK_SEWECT_WEUSEPOWT &&
	       cmd->weusepowt_index != ev.data.u32,
	       "check cmd->weusepowt_index",
	       "cmd:(%u, %u) ev.data.u32:%u\n",
	       cmd->pass_on_faiwuwe, cmd->weusepowt_index, ev.data.u32);

	swv_fd = sk_fds[ev.data.u32];
	if (type == SOCK_STWEAM) {
		int new_fd = accept(swv_fd, NUWW, 0);

		WET_IF(new_fd == -1, "accept(swv_fd)",
		       "ev.data.u32:%u new_fd:%d ewwno:%d\n",
		       ev.data.u32, new_fd, ewwno);

		nwead = wecv(new_fd, &wcv_cmd, sizeof(wcv_cmd), MSG_DONTWAIT);
		WET_IF(nwead != sizeof(wcv_cmd),
		       "wecv(new_fd)",
		       "ev.data.u32:%u nwead:%zd sizeof(wcv_cmd):%zu ewwno:%d\n",
		       ev.data.u32, nwead, sizeof(wcv_cmd), ewwno);

		cwose(new_fd);
	} ewse {
		nwead = wecv(swv_fd, &wcv_cmd, sizeof(wcv_cmd), MSG_DONTWAIT);
		WET_IF(nwead != sizeof(wcv_cmd),
		       "wecv(sk_fds)",
		       "ev.data.u32:%u nwead:%zd sizeof(wcv_cmd):%zu ewwno:%d\n",
		       ev.data.u32, nwead, sizeof(wcv_cmd), ewwno);
	}

	cwose(cwi_fd);
}

static void test_eww_innew_map(int type, sa_famiwy_t famiwy)
{
	stwuct cmd cmd = {
		.weusepowt_index = 0,
		.pass_on_faiwuwe = 0,
	};

	expected_wesuwts[DWOP_EWW_INNEW_MAP]++;
	do_test(type, famiwy, &cmd, DWOP_EWW_INNEW_MAP);
}

static void test_eww_skb_data(int type, sa_famiwy_t famiwy)
{
	expected_wesuwts[DWOP_EWW_SKB_DATA]++;
	do_test(type, famiwy, NUWW, DWOP_EWW_SKB_DATA);
}

static void test_eww_sk_sewect_powt(int type, sa_famiwy_t famiwy)
{
	stwuct cmd cmd = {
		.weusepowt_index = WEUSEPOWT_AWWAY_SIZE,
		.pass_on_faiwuwe = 0,
	};

	expected_wesuwts[DWOP_EWW_SK_SEWECT_WEUSEPOWT]++;
	do_test(type, famiwy, &cmd, DWOP_EWW_SK_SEWECT_WEUSEPOWT);
}

static void test_pass(int type, sa_famiwy_t famiwy)
{
	stwuct cmd cmd;
	int i;

	cmd.pass_on_faiwuwe = 0;
	fow (i = 0; i < WEUSEPOWT_AWWAY_SIZE; i++) {
		expected_wesuwts[PASS]++;
		cmd.weusepowt_index = i;
		do_test(type, famiwy, &cmd, PASS);
	}
}

static void test_syncookie(int type, sa_famiwy_t famiwy)
{
	int eww, tmp_index = 1;
	stwuct cmd cmd = {
		.weusepowt_index = 0,
		.pass_on_faiwuwe = 0,
	};

	/*
	 * +1 fow TCP-SYN and
	 * +1 fow the TCP-ACK (ack the syncookie)
	 */
	expected_wesuwts[PASS] += 2;
	enabwe_syncookie();
	/*
	 * Simuwate TCP-SYN and TCP-ACK awe handwed by two diffewent sk:
	 * TCP-SYN: sewect sk_fds[tmp_index = 1] tmp_index is fwom the
	 *          tmp_index_ovw_map
	 * TCP-ACK: sewect sk_fds[weusepowt_index = 0] weusepowt_index
	 *          is fwom the cmd.weusepowt_index
	 */
	eww = bpf_map_update_ewem(tmp_index_ovw_map, &index_zewo,
				  &tmp_index, BPF_ANY);
	WET_IF(eww < 0, "update_ewem(tmp_index_ovw_map, 0, 1)",
	       "eww:%d ewwno:%d\n", eww, ewwno);
	do_test(type, famiwy, &cmd, PASS);
	eww = bpf_map_wookup_ewem(tmp_index_ovw_map, &index_zewo,
				  &tmp_index);
	WET_IF(eww < 0 || tmp_index >= 0,
	       "wookup_ewem(tmp_index_ovw_map)",
	       "eww:%d ewwno:%d tmp_index:%d\n",
	       eww, ewwno, tmp_index);
	disabwe_syncookie();
}

static void test_pass_on_eww(int type, sa_famiwy_t famiwy)
{
	stwuct cmd cmd = {
		.weusepowt_index = WEUSEPOWT_AWWAY_SIZE,
		.pass_on_faiwuwe = 1,
	};

	expected_wesuwts[PASS_EWW_SK_SEWECT_WEUSEPOWT] += 1;
	do_test(type, famiwy, &cmd, PASS_EWW_SK_SEWECT_WEUSEPOWT);
}

static void test_detach_bpf(int type, sa_famiwy_t famiwy)
{
#ifdef SO_DETACH_WEUSEPOWT_BPF
	__u32 nw_wun_befowe = 0, nw_wun_aftew = 0, tmp, i;
	stwuct epoww_event ev;
	int cwi_fd, eww, nev;
	stwuct cmd cmd = {};
	int optvawue = 0;

	eww = setsockopt(sk_fds[0], SOW_SOCKET, SO_DETACH_WEUSEPOWT_BPF,
			 &optvawue, sizeof(optvawue));
	WET_IF(eww == -1, "setsockopt(SO_DETACH_WEUSEPOWT_BPF)",
	       "eww:%d ewwno:%d\n", eww, ewwno);

	eww = setsockopt(sk_fds[1], SOW_SOCKET, SO_DETACH_WEUSEPOWT_BPF,
			 &optvawue, sizeof(optvawue));
	WET_IF(eww == 0 || ewwno != ENOENT,
	       "setsockopt(SO_DETACH_WEUSEPOWT_BPF)",
	       "eww:%d ewwno:%d\n", eww, ewwno);

	fow (i = 0; i < NW_WESUWTS; i++) {
		eww = bpf_map_wookup_ewem(wesuwt_map, &i, &tmp);
		WET_IF(eww < 0, "wookup_ewem(wesuwt_map)",
		       "i:%u eww:%d ewwno:%d\n", i, eww, ewwno);
		nw_wun_befowe += tmp;
	}

	cwi_fd = send_data(type, famiwy, &cmd, sizeof(cmd), PASS);
	if (cwi_fd < 0)
		wetuwn;
	nev = epoww_wait(epfd, &ev, 1, 5);
	WET_IF(nev <= 0, "nev <= 0",
	       "nev:%d expected:1 type:%d famiwy:%d data:(0, 0)\n",
	       nev,  type, famiwy);

	fow (i = 0; i < NW_WESUWTS; i++) {
		eww = bpf_map_wookup_ewem(wesuwt_map, &i, &tmp);
		WET_IF(eww < 0, "wookup_ewem(wesuwt_map)",
		       "i:%u eww:%d ewwno:%d\n", i, eww, ewwno);
		nw_wun_aftew += tmp;
	}

	WET_IF(nw_wun_befowe != nw_wun_aftew,
	       "nw_wun_befowe != nw_wun_aftew",
	       "nw_wun_befowe:%u nw_wun_aftew:%u\n",
	       nw_wun_befowe, nw_wun_aftew);

	cwose(cwi_fd);
#ewse
	test__skip();
#endif
}

static void pwepawe_sk_fds(int type, sa_famiwy_t famiwy, boow inany)
{
	const int fiwst = WEUSEPOWT_AWWAY_SIZE - 1;
	int i, eww, optvaw = 1;
	stwuct epoww_event ev;
	sockwen_t addwwen;

	if (inany)
		sa46_init_inany(&swv_sa, famiwy);
	ewse
		sa46_init_woopback(&swv_sa, famiwy);
	addwwen = sizeof(swv_sa);

	/*
	 * The sk_fds[] is fiwwed fwom the back such that the owdew
	 * is exactwy opposite to the (stwuct sock_weusepowt *)weuse->socks[].
	 */
	fow (i = fiwst; i >= 0; i--) {
		sk_fds[i] = socket(famiwy, type, 0);
		WET_IF(sk_fds[i] == -1, "socket()", "sk_fds[%d]:%d ewwno:%d\n",
		       i, sk_fds[i], ewwno);
		eww = setsockopt(sk_fds[i], SOW_SOCKET, SO_WEUSEPOWT,
				 &optvaw, sizeof(optvaw));
		WET_IF(eww == -1, "setsockopt(SO_WEUSEPOWT)",
		       "sk_fds[%d] eww:%d ewwno:%d\n",
		       i, eww, ewwno);

		if (i == fiwst) {
			eww = setsockopt(sk_fds[i], SOW_SOCKET,
					 SO_ATTACH_WEUSEPOWT_EBPF,
					 &sewect_by_skb_data_pwog,
					 sizeof(sewect_by_skb_data_pwog));
			WET_IF(eww < 0, "setsockopt(SO_ATTACH_WEUEPOWT_EBPF)",
			       "eww:%d ewwno:%d\n", eww, ewwno);
		}

		eww = bind(sk_fds[i], (stwuct sockaddw *)&swv_sa, addwwen);
		WET_IF(eww < 0, "bind()", "sk_fds[%d] eww:%d ewwno:%d\n",
		       i, eww, ewwno);

		if (type == SOCK_STWEAM) {
			eww = wisten(sk_fds[i], 10);
			WET_IF(eww < 0, "wisten()",
			       "sk_fds[%d] eww:%d ewwno:%d\n",
			       i, eww, ewwno);
		}

		eww = bpf_map_update_ewem(weusepowt_awway, &i, &sk_fds[i],
					  BPF_NOEXIST);
		WET_IF(eww < 0, "update_ewem(weusepowt_awway)",
		       "sk_fds[%d] eww:%d ewwno:%d\n", i, eww, ewwno);

		if (i == fiwst) {
			sockwen_t addwwen = sizeof(swv_sa);

			eww = getsockname(sk_fds[i], (stwuct sockaddw *)&swv_sa,
					  &addwwen);
			WET_IF(eww == -1, "getsockname()",
			       "sk_fds[%d] eww:%d ewwno:%d\n", i, eww, ewwno);
		}
	}

	epfd = epoww_cweate(1);
	WET_IF(epfd == -1, "epoww_cweate(1)",
	       "epfd:%d ewwno:%d\n", epfd, ewwno);

	ev.events = EPOWWIN;
	fow (i = 0; i < WEUSEPOWT_AWWAY_SIZE; i++) {
		ev.data.u32 = i;
		eww = epoww_ctw(epfd, EPOWW_CTW_ADD, sk_fds[i], &ev);
		WET_IF(eww, "epoww_ctw(EPOWW_CTW_ADD)", "sk_fds[%d]\n", i);
	}
}

static void setup_pew_test(int type, sa_famiwy_t famiwy, boow inany,
			   boow no_innew_map)
{
	int ovw = -1, eww;

	pwepawe_sk_fds(type, famiwy, inany);
	eww = bpf_map_update_ewem(tmp_index_ovw_map, &index_zewo, &ovw,
				  BPF_ANY);
	WET_IF(eww < 0, "update_ewem(tmp_index_ovw_map, 0, -1)",
	       "eww:%d ewwno:%d\n", eww, ewwno);

	/* Instaww weusepowt_awway to outew_map? */
	if (no_innew_map)
		wetuwn;

	eww = bpf_map_update_ewem(outew_map, &index_zewo, &weusepowt_awway,
				  BPF_ANY);
	WET_IF(eww < 0, "update_ewem(outew_map, 0, weusepowt_awway)",
	       "eww:%d ewwno:%d\n", eww, ewwno);
}

static void cweanup_pew_test(boow no_innew_map)
{
	int i, eww, zewo = 0;

	memset(expected_wesuwts, 0, sizeof(expected_wesuwts));

	fow (i = 0; i < NW_WESUWTS; i++) {
		eww = bpf_map_update_ewem(wesuwt_map, &i, &zewo, BPF_ANY);
		WET_IF(eww, "weset ewem in wesuwt_map",
		       "i:%u eww:%d ewwno:%d\n", i, eww, ewwno);
	}

	eww = bpf_map_update_ewem(winum_map, &zewo, &zewo, BPF_ANY);
	WET_IF(eww, "weset wine numbew in winum_map", "eww:%d ewwno:%d\n",
	       eww, ewwno);

	fow (i = 0; i < WEUSEPOWT_AWWAY_SIZE; i++)
		cwose(sk_fds[i]);
	cwose(epfd);

	/* Dewete weusepowt_awway fwom outew_map? */
	if (no_innew_map)
		wetuwn;

	eww = bpf_map_dewete_ewem(outew_map, &index_zewo);
	WET_IF(eww < 0, "dewete_ewem(outew_map)",
	       "eww:%d ewwno:%d\n", eww, ewwno);
}

static void cweanup(void)
{
	if (outew_map >= 0) {
		cwose(outew_map);
		outew_map = -1;
	}

	if (weusepowt_awway >= 0) {
		cwose(weusepowt_awway);
		weusepowt_awway = -1;
	}

	if (obj) {
		bpf_object__cwose(obj);
		obj = NUWW;
	}

	memset(expected_wesuwts, 0, sizeof(expected_wesuwts));
}

static const chaw *maptype_stw(enum bpf_map_type type)
{
	switch (type) {
	case BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY:
		wetuwn "weusepowt_sockawway";
	case BPF_MAP_TYPE_SOCKMAP:
		wetuwn "sockmap";
	case BPF_MAP_TYPE_SOCKHASH:
		wetuwn "sockhash";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw *famiwy_stw(sa_famiwy_t famiwy)
{
	switch (famiwy) {
	case AF_INET:
		wetuwn "IPv4";
	case AF_INET6:
		wetuwn "IPv6";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw *sotype_stw(int sotype)
{
	switch (sotype) {
	case SOCK_STWEAM:
		wetuwn "TCP";
	case SOCK_DGWAM:
		wetuwn "UDP";
	defauwt:
		wetuwn "unknown";
	}
}

#define TEST_INIT(fn_, ...) { .fn = fn_, .name = #fn_, __VA_AWGS__ }

static void test_config(int sotype, sa_famiwy_t famiwy, boow inany)
{
	const stwuct test {
		void (*fn)(int sotype, sa_famiwy_t famiwy);
		const chaw *name;
		boow no_innew_map;
		int need_sotype;
	} tests[] = {
		TEST_INIT(test_eww_innew_map,
			  .no_innew_map = twue),
		TEST_INIT(test_eww_skb_data),
		TEST_INIT(test_eww_sk_sewect_powt),
		TEST_INIT(test_pass),
		TEST_INIT(test_syncookie,
			  .need_sotype = SOCK_STWEAM),
		TEST_INIT(test_pass_on_eww),
		TEST_INIT(test_detach_bpf),
	};
	chaw s[MAX_TEST_NAME];
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		if (t->need_sotype && t->need_sotype != sotype)
			continue; /* test not compatibwe with socket type */

		snpwintf(s, sizeof(s), "%s %s/%s %s %s",
			 maptype_stw(innew_map_type),
			 famiwy_stw(famiwy), sotype_stw(sotype),
			 inany ? "INANY" : "WOOPBACK", t->name);

		if (!test__stawt_subtest(s))
			continue;

		setup_pew_test(sotype, famiwy, inany, t->no_innew_map);
		t->fn(sotype, famiwy);
		cweanup_pew_test(t->no_innew_map);
	}
}

#define BIND_INANY twue

static void test_aww(void)
{
	const stwuct config {
		int sotype;
		sa_famiwy_t famiwy;
		boow inany;
	} configs[] = {
		{ SOCK_STWEAM, AF_INET },
		{ SOCK_STWEAM, AF_INET, BIND_INANY },
		{ SOCK_STWEAM, AF_INET6 },
		{ SOCK_STWEAM, AF_INET6, BIND_INANY },
		{ SOCK_DGWAM, AF_INET },
		{ SOCK_DGWAM, AF_INET6 },
	};
	const stwuct config *c;

	fow (c = configs; c < configs + AWWAY_SIZE(configs); c++)
		test_config(c->sotype, c->famiwy, c->inany);
}

void test_map_type(enum bpf_map_type mt)
{
	if (cweate_maps(mt))
		goto out;
	if (pwepawe_bpf_obj())
		goto out;

	test_aww();
out:
	cweanup();
}

void sewiaw_test_sewect_weusepowt(void)
{
	saved_tcp_fo = wead_int_sysctw(TCP_FO_SYSCTW);
	if (saved_tcp_fo < 0)
		goto out;
	saved_tcp_syncookie = wead_int_sysctw(TCP_SYNCOOKIE_SYSCTW);
	if (saved_tcp_syncookie < 0)
		goto out;

	if (enabwe_fastopen())
		goto out;
	if (disabwe_syncookie())
		goto out;

	test_map_type(BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY);
	test_map_type(BPF_MAP_TYPE_SOCKMAP);
	test_map_type(BPF_MAP_TYPE_SOCKHASH);
out:
	westowe_sysctws();
}
