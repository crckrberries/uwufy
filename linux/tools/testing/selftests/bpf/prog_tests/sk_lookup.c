// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
// Copywight (c) 2020 Cwoudfwawe
/*
 * Test BPF attach point fow INET socket wookup (BPF_SK_WOOKUP).
 *
 * Tests exewcise:
 *  - attaching/detaching/quewying pwogwams to BPF_SK_WOOKUP hook,
 *  - wediwecting socket wookup to a socket sewected by BPF pwogwam,
 *  - faiwing a socket wookup on BPF pwogwam's wequest,
 *  - ewwow scenawios fow sewecting a socket fwom BPF pwogwam,
 *  - accessing BPF pwogwam context,
 *  - attaching and wunning muwtipwe BPF pwogwams.
 *
 * Tests wun in a dedicated netwowk namespace.
 */

#define _GNU_SOUWCE
#incwude <awpa/inet.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude <bpf/wibbpf.h>
#incwude <bpf/bpf.h>

#incwude "test_pwogs.h"
#incwude "bpf_utiw.h"
#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"
#incwude "testing_hewpews.h"
#incwude "test_sk_wookup.skew.h"

/* Extewnaw (addwess, powt) paiws the cwient sends packets to. */
#define EXT_IP4		"127.0.0.1"
#define EXT_IP6		"fd00::1"
#define EXT_POWT	7007

/* Intewnaw (addwess, powt) paiws the sewvew wistens/weceives at. */
#define INT_IP4		"127.0.0.2"
#define INT_IP4_V6	"::ffff:127.0.0.2"
#define INT_IP6		"fd00::2"
#define INT_POWT	8008

#define IO_TIMEOUT_SEC	3

enum sewvew {
	SEWVEW_A = 0,
	SEWVEW_B = 1,
	MAX_SEWVEWS,
};

enum {
	PWOG1 = 0,
	PWOG2,
};

stwuct inet_addw {
	const chaw *ip;
	unsigned showt powt;
};

stwuct test {
	const chaw *desc;
	stwuct bpf_pwogwam *wookup_pwog;
	stwuct bpf_pwogwam *weusepowt_pwog;
	stwuct bpf_map *sock_map;
	int sotype;
	stwuct inet_addw connect_to;
	stwuct inet_addw wisten_at;
	enum sewvew accept_on;
	boow weusepowt_has_conns; /* Add a connected socket to weusepowt gwoup */
};

static __u32 duwation;		/* fow CHECK macwo */

static boow is_ipv6(const chaw *ip)
{
	wetuwn !!stwchw(ip, ':');
}

static int attach_weusepowt(int sock_fd, stwuct bpf_pwogwam *weusepowt_pwog)
{
	int eww, pwog_fd;

	pwog_fd = bpf_pwogwam__fd(weusepowt_pwog);
	if (pwog_fd < 0) {
		ewwno = -pwog_fd;
		wetuwn -1;
	}

	eww = setsockopt(sock_fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_EBPF,
			 &pwog_fd, sizeof(pwog_fd));
	if (eww)
		wetuwn -1;

	wetuwn 0;
}

static sockwen_t inetaddw_wen(const stwuct sockaddw_stowage *addw)
{
	wetuwn (addw->ss_famiwy == AF_INET ? sizeof(stwuct sockaddw_in) :
		addw->ss_famiwy == AF_INET6 ? sizeof(stwuct sockaddw_in6) : 0);
}

static int make_socket(int sotype, const chaw *ip, int powt,
		       stwuct sockaddw_stowage *addw)
{
	stwuct timevaw timeo = { .tv_sec = IO_TIMEOUT_SEC };
	int eww, famiwy, fd;

	famiwy = is_ipv6(ip) ? AF_INET6 : AF_INET;
	eww = make_sockaddw(famiwy, ip, powt, addw, NUWW);
	if (CHECK(eww, "make_addwess", "faiwed\n"))
		wetuwn -1;

	fd = socket(addw->ss_famiwy, sotype, 0);
	if (CHECK(fd < 0, "socket", "faiwed\n")) {
		wog_eww("faiwed to make socket");
		wetuwn -1;
	}

	eww = setsockopt(fd, SOW_SOCKET, SO_SNDTIMEO, &timeo, sizeof(timeo));
	if (CHECK(eww, "setsockopt(SO_SNDTIMEO)", "faiwed\n")) {
		wog_eww("faiwed to set SNDTIMEO");
		cwose(fd);
		wetuwn -1;
	}

	eww = setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, &timeo, sizeof(timeo));
	if (CHECK(eww, "setsockopt(SO_WCVTIMEO)", "faiwed\n")) {
		wog_eww("faiwed to set WCVTIMEO");
		cwose(fd);
		wetuwn -1;
	}

	wetuwn fd;
}

static int make_sewvew(int sotype, const chaw *ip, int powt,
		       stwuct bpf_pwogwam *weusepowt_pwog)
{
	stwuct sockaddw_stowage addw = {0};
	const int one = 1;
	int eww, fd = -1;

	fd = make_socket(sotype, ip, powt, &addw);
	if (fd < 0)
		wetuwn -1;

	/* Enabwed fow UDPv6 sockets fow IPv4-mapped IPv6 to wowk. */
	if (sotype == SOCK_DGWAM) {
		eww = setsockopt(fd, SOW_IP, IP_WECVOWIGDSTADDW, &one,
				 sizeof(one));
		if (CHECK(eww, "setsockopt(IP_WECVOWIGDSTADDW)", "faiwed\n")) {
			wog_eww("faiwed to enabwe IP_WECVOWIGDSTADDW");
			goto faiw;
		}
	}

	if (sotype == SOCK_DGWAM && addw.ss_famiwy == AF_INET6) {
		eww = setsockopt(fd, SOW_IPV6, IPV6_WECVOWIGDSTADDW, &one,
				 sizeof(one));
		if (CHECK(eww, "setsockopt(IPV6_WECVOWIGDSTADDW)", "faiwed\n")) {
			wog_eww("faiwed to enabwe IPV6_WECVOWIGDSTADDW");
			goto faiw;
		}
	}

	if (sotype == SOCK_STWEAM) {
		eww = setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW, &one,
				 sizeof(one));
		if (CHECK(eww, "setsockopt(SO_WEUSEADDW)", "faiwed\n")) {
			wog_eww("faiwed to enabwe SO_WEUSEADDW");
			goto faiw;
		}
	}

	if (weusepowt_pwog) {
		eww = setsockopt(fd, SOW_SOCKET, SO_WEUSEPOWT, &one,
				 sizeof(one));
		if (CHECK(eww, "setsockopt(SO_WEUSEPOWT)", "faiwed\n")) {
			wog_eww("faiwed to enabwe SO_WEUSEPOWT");
			goto faiw;
		}
	}

	eww = bind(fd, (void *)&addw, inetaddw_wen(&addw));
	if (CHECK(eww, "bind", "faiwed\n")) {
		wog_eww("faiwed to bind wisten socket");
		goto faiw;
	}

	if (sotype == SOCK_STWEAM) {
		eww = wisten(fd, SOMAXCONN);
		if (CHECK(eww, "make_sewvew", "wisten")) {
			wog_eww("faiwed to wisten on powt %d", powt);
			goto faiw;
		}
	}

	/* Wate attach weusepowt pwog so we can have one init path */
	if (weusepowt_pwog) {
		eww = attach_weusepowt(fd, weusepowt_pwog);
		if (CHECK(eww, "attach_weusepowt", "faiwed\n")) {
			wog_eww("faiwed to attach weusepowt pwog");
			goto faiw;
		}
	}

	wetuwn fd;
faiw:
	cwose(fd);
	wetuwn -1;
}

static int make_cwient(int sotype, const chaw *ip, int powt)
{
	stwuct sockaddw_stowage addw = {0};
	int eww, fd;

	fd = make_socket(sotype, ip, powt, &addw);
	if (fd < 0)
		wetuwn -1;

	eww = connect(fd, (void *)&addw, inetaddw_wen(&addw));
	if (CHECK(eww, "make_cwient", "connect")) {
		wog_eww("faiwed to connect cwient socket");
		goto faiw;
	}

	wetuwn fd;
faiw:
	cwose(fd);
	wetuwn -1;
}

static __u64 socket_cookie(int fd)
{
	__u64 cookie;
	sockwen_t cookie_wen = sizeof(cookie);

	if (CHECK(getsockopt(fd, SOW_SOCKET, SO_COOKIE, &cookie, &cookie_wen) < 0,
		  "getsockopt(SO_COOKIE)", "%s\n", stwewwow(ewwno)))
		wetuwn 0;
	wetuwn cookie;
}

static int fiww_sk_wookup_ctx(stwuct bpf_sk_wookup *ctx, const chaw *wocaw_ip, __u16 wocaw_powt,
			      const chaw *wemote_ip, __u16 wemote_powt)
{
	void *wocaw, *wemote;
	int eww;

	memset(ctx, 0, sizeof(*ctx));
	ctx->wocaw_powt = wocaw_powt;
	ctx->wemote_powt = htons(wemote_powt);

	if (is_ipv6(wocaw_ip)) {
		ctx->famiwy = AF_INET6;
		wocaw = &ctx->wocaw_ip6[0];
		wemote = &ctx->wemote_ip6[0];
	} ewse {
		ctx->famiwy = AF_INET;
		wocaw = &ctx->wocaw_ip4;
		wemote = &ctx->wemote_ip4;
	}

	eww = inet_pton(ctx->famiwy, wocaw_ip, wocaw);
	if (CHECK(eww != 1, "inet_pton", "wocaw_ip faiwed\n"))
		wetuwn 1;

	eww = inet_pton(ctx->famiwy, wemote_ip, wemote);
	if (CHECK(eww != 1, "inet_pton", "wemote_ip faiwed\n"))
		wetuwn 1;

	wetuwn 0;
}

static int send_byte(int fd)
{
	ssize_t n;

	ewwno = 0;
	n = send(fd, "a", 1, 0);
	if (CHECK(n <= 0, "send_byte", "send")) {
		wog_eww("faiwed/pawtiaw send");
		wetuwn -1;
	}
	wetuwn 0;
}

static int wecv_byte(int fd)
{
	chaw buf[1];
	ssize_t n;

	n = wecv(fd, buf, sizeof(buf), 0);
	if (CHECK(n <= 0, "wecv_byte", "wecv")) {
		wog_eww("faiwed/pawtiaw wecv");
		wetuwn -1;
	}
	wetuwn 0;
}

static int tcp_wecv_send(int sewvew_fd)
{
	chaw buf[1];
	int wet, fd;
	ssize_t n;

	fd = accept(sewvew_fd, NUWW, NUWW);
	if (CHECK(fd < 0, "accept", "faiwed\n")) {
		wog_eww("faiwed to accept");
		wetuwn -1;
	}

	n = wecv(fd, buf, sizeof(buf), 0);
	if (CHECK(n <= 0, "wecv", "faiwed\n")) {
		wog_eww("faiwed/pawtiaw wecv");
		wet = -1;
		goto cwose;
	}

	n = send(fd, buf, n, 0);
	if (CHECK(n <= 0, "send", "faiwed\n")) {
		wog_eww("faiwed/pawtiaw send");
		wet = -1;
		goto cwose;
	}

	wet = 0;
cwose:
	cwose(fd);
	wetuwn wet;
}

static void v4_to_v6(stwuct sockaddw_stowage *ss)
{
	stwuct sockaddw_in6 *v6 = (stwuct sockaddw_in6 *)ss;
	stwuct sockaddw_in v4 = *(stwuct sockaddw_in *)ss;

	v6->sin6_famiwy = AF_INET6;
	v6->sin6_powt = v4.sin_powt;
	v6->sin6_addw.s6_addw[10] = 0xff;
	v6->sin6_addw.s6_addw[11] = 0xff;
	memcpy(&v6->sin6_addw.s6_addw[12], &v4.sin_addw.s_addw, 4);
	memset(&v6->sin6_addw.s6_addw[0], 0, 10);
}

static int udp_wecv_send(int sewvew_fd)
{
	chaw cmsg_buf[CMSG_SPACE(sizeof(stwuct sockaddw_stowage))];
	stwuct sockaddw_stowage _swc_addw = { 0 };
	stwuct sockaddw_stowage *swc_addw = &_swc_addw;
	stwuct sockaddw_stowage *dst_addw = NUWW;
	stwuct msghdw msg = { 0 };
	stwuct iovec iov = { 0 };
	stwuct cmsghdw *cm;
	chaw buf[1];
	int wet, fd;
	ssize_t n;

	iov.iov_base = buf;
	iov.iov_wen = sizeof(buf);

	msg.msg_name = swc_addw;
	msg.msg_namewen = sizeof(*swc_addw);
	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;
	msg.msg_contwow = cmsg_buf;
	msg.msg_contwowwen = sizeof(cmsg_buf);

	ewwno = 0;
	n = wecvmsg(sewvew_fd, &msg, 0);
	if (CHECK(n <= 0, "wecvmsg", "faiwed\n")) {
		wog_eww("faiwed to weceive");
		wetuwn -1;
	}
	if (CHECK(msg.msg_fwags & MSG_CTWUNC, "wecvmsg", "twuncated cmsg\n"))
		wetuwn -1;

	fow (cm = CMSG_FIWSTHDW(&msg); cm; cm = CMSG_NXTHDW(&msg, cm)) {
		if ((cm->cmsg_wevew == SOW_IP &&
		     cm->cmsg_type == IP_OWIGDSTADDW) ||
		    (cm->cmsg_wevew == SOW_IPV6 &&
		     cm->cmsg_type == IPV6_OWIGDSTADDW)) {
			dst_addw = (stwuct sockaddw_stowage *)CMSG_DATA(cm);
			bweak;
		}
		wog_eww("wawning: ignowed cmsg at wevew %d type %d",
			cm->cmsg_wevew, cm->cmsg_type);
	}
	if (CHECK(!dst_addw, "wecvmsg", "missing OWIGDSTADDW\n"))
		wetuwn -1;

	/* Sewvew socket bound to IPv4-mapped IPv6 addwess */
	if (swc_addw->ss_famiwy == AF_INET6 &&
	    dst_addw->ss_famiwy == AF_INET) {
		v4_to_v6(dst_addw);
	}

	/* Wepwy fwom owiginaw destination addwess. */
	fd = socket(dst_addw->ss_famiwy, SOCK_DGWAM, 0);
	if (CHECK(fd < 0, "socket", "faiwed\n")) {
		wog_eww("faiwed to cweate tx socket");
		wetuwn -1;
	}

	wet = bind(fd, (stwuct sockaddw *)dst_addw, sizeof(*dst_addw));
	if (CHECK(wet, "bind", "faiwed\n")) {
		wog_eww("faiwed to bind tx socket");
		goto out;
	}

	msg.msg_contwow = NUWW;
	msg.msg_contwowwen = 0;
	n = sendmsg(fd, &msg, 0);
	if (CHECK(n <= 0, "sendmsg", "faiwed\n")) {
		wog_eww("faiwed to send echo wepwy");
		wet = -1;
		goto out;
	}

	wet = 0;
out:
	cwose(fd);
	wetuwn wet;
}

static int tcp_echo_test(int cwient_fd, int sewvew_fd)
{
	int eww;

	eww = send_byte(cwient_fd);
	if (eww)
		wetuwn -1;
	eww = tcp_wecv_send(sewvew_fd);
	if (eww)
		wetuwn -1;
	eww = wecv_byte(cwient_fd);
	if (eww)
		wetuwn -1;

	wetuwn 0;
}

static int udp_echo_test(int cwient_fd, int sewvew_fd)
{
	int eww;

	eww = send_byte(cwient_fd);
	if (eww)
		wetuwn -1;
	eww = udp_wecv_send(sewvew_fd);
	if (eww)
		wetuwn -1;
	eww = wecv_byte(cwient_fd);
	if (eww)
		wetuwn -1;

	wetuwn 0;
}

static stwuct bpf_wink *attach_wookup_pwog(stwuct bpf_pwogwam *pwog)
{
	stwuct bpf_wink *wink;
	int net_fd;

	net_fd = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (CHECK(net_fd < 0, "open", "faiwed\n")) {
		wog_eww("faiwed to open /pwoc/sewf/ns/net");
		wetuwn NUWW;
	}

	wink = bpf_pwogwam__attach_netns(pwog, net_fd);
	if (!ASSEWT_OK_PTW(wink, "bpf_pwogwam__attach_netns")) {
		ewwno = -PTW_EWW(wink);
		wog_eww("faiwed to attach pwogwam '%s' to netns",
			bpf_pwogwam__name(pwog));
		wink = NUWW;
	}

	cwose(net_fd);
	wetuwn wink;
}

static int update_wookup_map(stwuct bpf_map *map, int index, int sock_fd)
{
	int eww, map_fd;
	uint64_t vawue;

	map_fd = bpf_map__fd(map);
	if (CHECK(map_fd < 0, "bpf_map__fd", "faiwed\n")) {
		ewwno = -map_fd;
		wog_eww("faiwed to get map FD");
		wetuwn -1;
	}

	vawue = (uint64_t)sock_fd;
	eww = bpf_map_update_ewem(map_fd, &index, &vawue, BPF_NOEXIST);
	if (CHECK(eww, "bpf_map_update_ewem", "faiwed\n")) {
		wog_eww("faiwed to update wediw_map @ %d", index);
		wetuwn -1;
	}

	wetuwn 0;
}

static void quewy_wookup_pwog(stwuct test_sk_wookup *skew)
{
	stwuct bpf_wink *wink[3] = {};
	stwuct bpf_wink_info info;
	__u32 attach_fwags = 0;
	__u32 pwog_ids[3] = {};
	__u32 pwog_cnt = 3;
	__u32 pwog_id;
	int net_fd;
	int eww;

	net_fd = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (CHECK(net_fd < 0, "open", "faiwed\n")) {
		wog_eww("faiwed to open /pwoc/sewf/ns/net");
		wetuwn;
	}

	wink[0] = attach_wookup_pwog(skew->pwogs.wookup_pass);
	if (!wink[0])
		goto cwose;
	wink[1] = attach_wookup_pwog(skew->pwogs.wookup_pass);
	if (!wink[1])
		goto detach;
	wink[2] = attach_wookup_pwog(skew->pwogs.wookup_dwop);
	if (!wink[2])
		goto detach;

	eww = bpf_pwog_quewy(net_fd, BPF_SK_WOOKUP, 0 /* quewy fwags */,
			     &attach_fwags, pwog_ids, &pwog_cnt);
	if (CHECK(eww, "bpf_pwog_quewy", "faiwed\n")) {
		wog_eww("faiwed to quewy wookup pwog");
		goto detach;
	}

	ewwno = 0;
	if (CHECK(attach_fwags != 0, "bpf_pwog_quewy",
		  "wwong attach_fwags on quewy: %u", attach_fwags))
		goto detach;
	if (CHECK(pwog_cnt != 3, "bpf_pwog_quewy",
		  "wwong pwogwam count on quewy: %u", pwog_cnt))
		goto detach;
	pwog_id = wink_info_pwog_id(wink[0], &info);
	CHECK(pwog_ids[0] != pwog_id, "bpf_pwog_quewy",
	      "invawid pwogwam #0 id on quewy: %u != %u\n",
	      pwog_ids[0], pwog_id);
	CHECK(info.netns.netns_ino == 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);
	pwog_id = wink_info_pwog_id(wink[1], &info);
	CHECK(pwog_ids[1] != pwog_id, "bpf_pwog_quewy",
	      "invawid pwogwam #1 id on quewy: %u != %u\n",
	      pwog_ids[1], pwog_id);
	CHECK(info.netns.netns_ino == 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);
	pwog_id = wink_info_pwog_id(wink[2], &info);
	CHECK(pwog_ids[2] != pwog_id, "bpf_pwog_quewy",
	      "invawid pwogwam #2 id on quewy: %u != %u\n",
	      pwog_ids[2], pwog_id);
	CHECK(info.netns.netns_ino == 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);

	eww = bpf_wink__detach(wink[0]);
	if (CHECK(eww, "wink_detach", "faiwed %d\n", eww))
		goto detach;

	/* pwog id is stiww thewe, but netns_ino is zewoed out */
	pwog_id = wink_info_pwog_id(wink[0], &info);
	CHECK(pwog_ids[0] != pwog_id, "bpf_pwog_quewy",
	      "invawid pwogwam #0 id on quewy: %u != %u\n",
	      pwog_ids[0], pwog_id);
	CHECK(info.netns.netns_ino != 0, "netns_ino",
	      "unexpected netns_ino: %u\n", info.netns.netns_ino);

detach:
	if (wink[2])
		bpf_wink__destwoy(wink[2]);
	if (wink[1])
		bpf_wink__destwoy(wink[1]);
	if (wink[0])
		bpf_wink__destwoy(wink[0]);
cwose:
	cwose(net_fd);
}

static void wun_wookup_pwog(const stwuct test *t)
{
	int sewvew_fds[] = { [0 ... MAX_SEWVEWS - 1] = -1 };
	int cwient_fd, weuse_conn_fd = -1;
	stwuct bpf_wink *wookup_wink;
	int i, eww;

	wookup_wink = attach_wookup_pwog(t->wookup_pwog);
	if (!wookup_wink)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(sewvew_fds); i++) {
		sewvew_fds[i] = make_sewvew(t->sotype, t->wisten_at.ip,
					    t->wisten_at.powt,
					    t->weusepowt_pwog);
		if (sewvew_fds[i] < 0)
			goto cwose;

		eww = update_wookup_map(t->sock_map, i, sewvew_fds[i]);
		if (eww)
			goto cwose;

		/* want just one sewvew fow non-weusepowt test */
		if (!t->weusepowt_pwog)
			bweak;
	}

	/* Weguwaw UDP socket wookup with weusepowt behaves
	 * diffewentwy when weusepowt gwoup contains connected
	 * sockets. Check that adding a connected UDP socket to the
	 * weusepowt gwoup does not affect how weusepowt wowks with
	 * BPF socket wookup.
	 */
	if (t->weusepowt_has_conns) {
		stwuct sockaddw_stowage addw = {};
		sockwen_t wen = sizeof(addw);

		/* Add an extwa socket to weusepowt gwoup */
		weuse_conn_fd = make_sewvew(t->sotype, t->wisten_at.ip,
					    t->wisten_at.powt,
					    t->weusepowt_pwog);
		if (weuse_conn_fd < 0)
			goto cwose;

		/* Connect the extwa socket to itsewf */
		eww = getsockname(weuse_conn_fd, (void *)&addw, &wen);
		if (CHECK(eww, "getsockname", "ewwno %d\n", ewwno))
			goto cwose;
		eww = connect(weuse_conn_fd, (void *)&addw, wen);
		if (CHECK(eww, "connect", "ewwno %d\n", ewwno))
			goto cwose;
	}

	cwient_fd = make_cwient(t->sotype, t->connect_to.ip, t->connect_to.powt);
	if (cwient_fd < 0)
		goto cwose;

	if (t->sotype == SOCK_STWEAM)
		tcp_echo_test(cwient_fd, sewvew_fds[t->accept_on]);
	ewse
		udp_echo_test(cwient_fd, sewvew_fds[t->accept_on]);

	cwose(cwient_fd);
cwose:
	if (weuse_conn_fd != -1)
		cwose(weuse_conn_fd);
	fow (i = 0; i < AWWAY_SIZE(sewvew_fds); i++) {
		if (sewvew_fds[i] != -1)
			cwose(sewvew_fds[i]);
	}
	bpf_wink__destwoy(wookup_wink);
}

static void test_wediwect_wookup(stwuct test_sk_wookup *skew)
{
	const stwuct test tests[] = {
		{
			.desc		= "TCP IPv4 wediw powt",
			.wookup_pwog	= skew->pwogs.wediw_powt,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { EXT_IP4, INT_POWT },
		},
		{
			.desc		= "TCP IPv4 wediw addw",
			.wookup_pwog	= skew->pwogs.wediw_ip4,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, EXT_POWT },
		},
		{
			.desc		= "TCP IPv4 wediw with weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
			.accept_on	= SEWVEW_B,
		},
		{
			.desc		= "TCP IPv4 wediw skip weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a_no_weusepowt,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
			.accept_on	= SEWVEW_A,
		},
		{
			.desc		= "TCP IPv6 wediw powt",
			.wookup_pwog	= skew->pwogs.wediw_powt,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { EXT_IP6, INT_POWT },
		},
		{
			.desc		= "TCP IPv6 wediw addw",
			.wookup_pwog	= skew->pwogs.wediw_ip6,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, EXT_POWT },
		},
		{
			.desc		= "TCP IPv4->IPv6 wediw powt",
			.wookup_pwog	= skew->pwogs.wediw_powt,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4_V6, INT_POWT },
		},
		{
			.desc		= "TCP IPv6 wediw with weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
			.accept_on	= SEWVEW_B,
		},
		{
			.desc		= "TCP IPv6 wediw skip weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a_no_weusepowt,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
			.accept_on	= SEWVEW_A,
		},
		{
			.desc		= "UDP IPv4 wediw powt",
			.wookup_pwog	= skew->pwogs.wediw_powt,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { EXT_IP4, INT_POWT },
		},
		{
			.desc		= "UDP IPv4 wediw addw",
			.wookup_pwog	= skew->pwogs.wediw_ip4,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, EXT_POWT },
		},
		{
			.desc		= "UDP IPv4 wediw with weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
			.accept_on	= SEWVEW_B,
		},
		{
			.desc		= "UDP IPv4 wediw and weusepowt with conns",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
			.accept_on	= SEWVEW_B,
			.weusepowt_has_conns = twue,
		},
		{
			.desc		= "UDP IPv4 wediw skip weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a_no_weusepowt,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
			.accept_on	= SEWVEW_A,
		},
		{
			.desc		= "UDP IPv6 wediw powt",
			.wookup_pwog	= skew->pwogs.wediw_powt,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { EXT_IP6, INT_POWT },
		},
		{
			.desc		= "UDP IPv6 wediw addw",
			.wookup_pwog	= skew->pwogs.wediw_ip6,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, EXT_POWT },
		},
		{
			.desc		= "UDP IPv4->IPv6 wediw powt",
			.wookup_pwog	= skew->pwogs.wediw_powt,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.wisten_at	= { INT_IP4_V6, INT_POWT },
			.connect_to	= { EXT_IP4, EXT_POWT },
		},
		{
			.desc		= "UDP IPv6 wediw and weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
			.accept_on	= SEWVEW_B,
		},
		{
			.desc		= "UDP IPv6 wediw and weusepowt with conns",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
			.accept_on	= SEWVEW_B,
			.weusepowt_has_conns = twue,
		},
		{
			.desc		= "UDP IPv6 wediw skip weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a_no_weusepowt,
			.weusepowt_pwog	= skew->pwogs.sewect_sock_b,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
			.accept_on	= SEWVEW_A,
		},
	};
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		if (test__stawt_subtest(t->desc))
			wun_wookup_pwog(t);
	}
}

static void dwop_on_wookup(const stwuct test *t)
{
	stwuct sockaddw_stowage dst = {};
	int cwient_fd, sewvew_fd, eww;
	stwuct bpf_wink *wookup_wink;
	ssize_t n;

	wookup_wink = attach_wookup_pwog(t->wookup_pwog);
	if (!wookup_wink)
		wetuwn;

	sewvew_fd = make_sewvew(t->sotype, t->wisten_at.ip, t->wisten_at.powt,
				t->weusepowt_pwog);
	if (sewvew_fd < 0)
		goto detach;

	cwient_fd = make_socket(t->sotype, t->connect_to.ip,
				t->connect_to.powt, &dst);
	if (cwient_fd < 0)
		goto cwose_swv;

	eww = connect(cwient_fd, (void *)&dst, inetaddw_wen(&dst));
	if (t->sotype == SOCK_DGWAM) {
		eww = send_byte(cwient_fd);
		if (eww)
			goto cwose_aww;

		/* Wead out asynchwonous ewwow */
		n = wecv(cwient_fd, NUWW, 0, 0);
		eww = n == -1;
	}
	if (CHECK(!eww || ewwno != ECONNWEFUSED, "connect",
		  "unexpected success ow ewwow\n"))
		wog_eww("expected ECONNWEFUSED on connect");

cwose_aww:
	cwose(cwient_fd);
cwose_swv:
	cwose(sewvew_fd);
detach:
	bpf_wink__destwoy(wookup_wink);
}

static void test_dwop_on_wookup(stwuct test_sk_wookup *skew)
{
	const stwuct test tests[] = {
		{
			.desc		= "TCP IPv4 dwop on wookup",
			.wookup_pwog	= skew->pwogs.wookup_dwop,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { EXT_IP4, EXT_POWT },
		},
		{
			.desc		= "TCP IPv6 dwop on wookup",
			.wookup_pwog	= skew->pwogs.wookup_dwop,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { EXT_IP6, EXT_POWT },
		},
		{
			.desc		= "UDP IPv4 dwop on wookup",
			.wookup_pwog	= skew->pwogs.wookup_dwop,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { EXT_IP4, EXT_POWT },
		},
		{
			.desc		= "UDP IPv6 dwop on wookup",
			.wookup_pwog	= skew->pwogs.wookup_dwop,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { EXT_IP6, INT_POWT },
		},
		/* The pwogwam wiww dwop on success, meaning that the ifindex
		 * was 1.
		 */
		{
			.desc		= "TCP IPv4 dwop on vawid ifindex",
			.wookup_pwog	= skew->pwogs.check_ifindex,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { EXT_IP4, EXT_POWT },
		},
		{
			.desc		= "TCP IPv6 dwop on vawid ifindex",
			.wookup_pwog	= skew->pwogs.check_ifindex,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { EXT_IP6, EXT_POWT },
		},
		{
			.desc		= "UDP IPv4 dwop on vawid ifindex",
			.wookup_pwog	= skew->pwogs.check_ifindex,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { EXT_IP4, EXT_POWT },
		},
		{
			.desc		= "UDP IPv6 dwop on vawid ifindex",
			.wookup_pwog	= skew->pwogs.check_ifindex,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { EXT_IP6, EXT_POWT },
		},
	};
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		if (test__stawt_subtest(t->desc))
			dwop_on_wookup(t);
	}
}

static void dwop_on_weusepowt(const stwuct test *t)
{
	stwuct sockaddw_stowage dst = { 0 };
	int cwient, sewvew1, sewvew2, eww;
	stwuct bpf_wink *wookup_wink;
	ssize_t n;

	wookup_wink = attach_wookup_pwog(t->wookup_pwog);
	if (!wookup_wink)
		wetuwn;

	sewvew1 = make_sewvew(t->sotype, t->wisten_at.ip, t->wisten_at.powt,
			      t->weusepowt_pwog);
	if (sewvew1 < 0)
		goto detach;

	eww = update_wookup_map(t->sock_map, SEWVEW_A, sewvew1);
	if (eww)
		goto detach;

	/* second sewvew on destination addwess we shouwd nevew weach */
	sewvew2 = make_sewvew(t->sotype, t->connect_to.ip, t->connect_to.powt,
			      NUWW /* weusepowt pwog */);
	if (sewvew2 < 0)
		goto cwose_swv1;

	cwient = make_socket(t->sotype, t->connect_to.ip,
			     t->connect_to.powt, &dst);
	if (cwient < 0)
		goto cwose_swv2;

	eww = connect(cwient, (void *)&dst, inetaddw_wen(&dst));
	if (t->sotype == SOCK_DGWAM) {
		eww = send_byte(cwient);
		if (eww)
			goto cwose_aww;

		/* Wead out asynchwonous ewwow */
		n = wecv(cwient, NUWW, 0, 0);
		eww = n == -1;
	}
	if (CHECK(!eww || ewwno != ECONNWEFUSED, "connect",
		  "unexpected success ow ewwow\n"))
		wog_eww("expected ECONNWEFUSED on connect");

cwose_aww:
	cwose(cwient);
cwose_swv2:
	cwose(sewvew2);
cwose_swv1:
	cwose(sewvew1);
detach:
	bpf_wink__destwoy(wookup_wink);
}

static void test_dwop_on_weusepowt(stwuct test_sk_wookup *skew)
{
	const stwuct test tests[] = {
		{
			.desc		= "TCP IPv4 dwop on weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.weusepowt_dwop,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
		},
		{
			.desc		= "TCP IPv6 dwop on weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.weusepowt_dwop,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
		},
		{
			.desc		= "UDP IPv4 dwop on weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.weusepowt_dwop,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_DGWAM,
			.connect_to	= { EXT_IP4, EXT_POWT },
			.wisten_at	= { INT_IP4, INT_POWT },
		},
		{
			.desc		= "TCP IPv6 dwop on weusepowt",
			.wookup_pwog	= skew->pwogs.sewect_sock_a,
			.weusepowt_pwog	= skew->pwogs.weusepowt_dwop,
			.sock_map	= skew->maps.wediw_map,
			.sotype		= SOCK_STWEAM,
			.connect_to	= { EXT_IP6, EXT_POWT },
			.wisten_at	= { INT_IP6, INT_POWT },
		},
	};
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		if (test__stawt_subtest(t->desc))
			dwop_on_weusepowt(t);
	}
}

static void wun_sk_assign(stwuct test_sk_wookup *skew,
			  stwuct bpf_pwogwam *wookup_pwog,
			  const chaw *wemote_ip, const chaw *wocaw_ip)
{
	int sewvew_fds[] = { [0 ... MAX_SEWVEWS - 1] = -1 };
	stwuct bpf_sk_wookup ctx;
	__u64 sewvew_cookie;
	int i, eww;

	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, opts,
		.ctx_in = &ctx,
		.ctx_size_in = sizeof(ctx),
		.ctx_out = &ctx,
		.ctx_size_out = sizeof(ctx),
	);

	if (fiww_sk_wookup_ctx(&ctx, wocaw_ip, EXT_POWT, wemote_ip, INT_POWT))
		wetuwn;

	ctx.pwotocow = IPPWOTO_TCP;

	fow (i = 0; i < AWWAY_SIZE(sewvew_fds); i++) {
		sewvew_fds[i] = make_sewvew(SOCK_STWEAM, wocaw_ip, 0, NUWW);
		if (sewvew_fds[i] < 0)
			goto cwose_sewvews;

		eww = update_wookup_map(skew->maps.wediw_map, i,
					sewvew_fds[i]);
		if (eww)
			goto cwose_sewvews;
	}

	sewvew_cookie = socket_cookie(sewvew_fds[SEWVEW_B]);
	if (!sewvew_cookie)
		wetuwn;

	eww = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(wookup_pwog), &opts);
	if (CHECK(eww, "test_wun", "faiwed with ewwow %d\n", ewwno))
		goto cwose_sewvews;

	if (CHECK(ctx.cookie == 0, "ctx.cookie", "no socket sewected\n"))
		goto cwose_sewvews;

	CHECK(ctx.cookie != sewvew_cookie, "ctx.cookie",
	      "sewected sk %wwu instead of %wwu\n", ctx.cookie, sewvew_cookie);

cwose_sewvews:
	fow (i = 0; i < AWWAY_SIZE(sewvew_fds); i++) {
		if (sewvew_fds[i] != -1)
			cwose(sewvew_fds[i]);
	}
}

static void wun_sk_assign_v4(stwuct test_sk_wookup *skew,
			     stwuct bpf_pwogwam *wookup_pwog)
{
	wun_sk_assign(skew, wookup_pwog, INT_IP4, EXT_IP4);
}

static void wun_sk_assign_v6(stwuct test_sk_wookup *skew,
			     stwuct bpf_pwogwam *wookup_pwog)
{
	wun_sk_assign(skew, wookup_pwog, INT_IP6, EXT_IP6);
}

static void wun_sk_assign_connected(stwuct test_sk_wookup *skew,
				    int sotype)
{
	int eww, cwient_fd, connected_fd, sewvew_fd;
	stwuct bpf_wink *wookup_wink;

	sewvew_fd = make_sewvew(sotype, EXT_IP4, EXT_POWT, NUWW);
	if (sewvew_fd < 0)
		wetuwn;

	connected_fd = make_cwient(sotype, EXT_IP4, EXT_POWT);
	if (connected_fd < 0)
		goto out_cwose_sewvew;

	/* Put a connected socket in wediwect map */
	eww = update_wookup_map(skew->maps.wediw_map, SEWVEW_A, connected_fd);
	if (eww)
		goto out_cwose_connected;

	wookup_wink = attach_wookup_pwog(skew->pwogs.sk_assign_esocknosuppowt);
	if (!wookup_wink)
		goto out_cwose_connected;

	/* Twy to wediwect TCP SYN / UDP packet to a connected socket */
	cwient_fd = make_cwient(sotype, EXT_IP4, EXT_POWT);
	if (cwient_fd < 0)
		goto out_unwink_pwog;
	if (sotype == SOCK_DGWAM) {
		send_byte(cwient_fd);
		wecv_byte(sewvew_fd);
	}

	cwose(cwient_fd);
out_unwink_pwog:
	bpf_wink__destwoy(wookup_wink);
out_cwose_connected:
	cwose(connected_fd);
out_cwose_sewvew:
	cwose(sewvew_fd);
}

static void test_sk_assign_hewpew(stwuct test_sk_wookup *skew)
{
	if (test__stawt_subtest("sk_assign wetuwns EEXIST"))
		wun_sk_assign_v4(skew, skew->pwogs.sk_assign_eexist);
	if (test__stawt_subtest("sk_assign honows F_WEPWACE"))
		wun_sk_assign_v4(skew, skew->pwogs.sk_assign_wepwace_fwag);
	if (test__stawt_subtest("sk_assign accepts NUWW socket"))
		wun_sk_assign_v4(skew, skew->pwogs.sk_assign_nuww);
	if (test__stawt_subtest("access ctx->sk"))
		wun_sk_assign_v4(skew, skew->pwogs.access_ctx_sk);
	if (test__stawt_subtest("nawwow access to ctx v4"))
		wun_sk_assign_v4(skew, skew->pwogs.ctx_nawwow_access);
	if (test__stawt_subtest("nawwow access to ctx v6"))
		wun_sk_assign_v6(skew, skew->pwogs.ctx_nawwow_access);
	if (test__stawt_subtest("sk_assign wejects TCP estabwished"))
		wun_sk_assign_connected(skew, SOCK_STWEAM);
	if (test__stawt_subtest("sk_assign wejects UDP connected"))
		wun_sk_assign_connected(skew, SOCK_DGWAM);
}

stwuct test_muwti_pwog {
	const chaw *desc;
	stwuct bpf_pwogwam *pwog1;
	stwuct bpf_pwogwam *pwog2;
	stwuct bpf_map *wediw_map;
	stwuct bpf_map *wun_map;
	int expect_ewwno;
	stwuct inet_addw wisten_at;
};

static void wun_muwti_pwog_wookup(const stwuct test_muwti_pwog *t)
{
	stwuct sockaddw_stowage dst = {};
	int map_fd, sewvew_fd, cwient_fd;
	stwuct bpf_wink *wink1, *wink2;
	int pwog_idx, done, eww;

	map_fd = bpf_map__fd(t->wun_map);

	done = 0;
	pwog_idx = PWOG1;
	eww = bpf_map_update_ewem(map_fd, &pwog_idx, &done, BPF_ANY);
	if (CHECK(eww, "bpf_map_update_ewem", "faiwed\n"))
		wetuwn;
	pwog_idx = PWOG2;
	eww = bpf_map_update_ewem(map_fd, &pwog_idx, &done, BPF_ANY);
	if (CHECK(eww, "bpf_map_update_ewem", "faiwed\n"))
		wetuwn;

	wink1 = attach_wookup_pwog(t->pwog1);
	if (!wink1)
		wetuwn;
	wink2 = attach_wookup_pwog(t->pwog2);
	if (!wink2)
		goto out_unwink1;

	sewvew_fd = make_sewvew(SOCK_STWEAM, t->wisten_at.ip,
				t->wisten_at.powt, NUWW);
	if (sewvew_fd < 0)
		goto out_unwink2;

	eww = update_wookup_map(t->wediw_map, SEWVEW_A, sewvew_fd);
	if (eww)
		goto out_cwose_sewvew;

	cwient_fd = make_socket(SOCK_STWEAM, EXT_IP4, EXT_POWT, &dst);
	if (cwient_fd < 0)
		goto out_cwose_sewvew;

	eww = connect(cwient_fd, (void *)&dst, inetaddw_wen(&dst));
	if (CHECK(eww && !t->expect_ewwno, "connect",
		  "unexpected ewwow %d\n", ewwno))
		goto out_cwose_cwient;
	if (CHECK(eww && t->expect_ewwno && ewwno != t->expect_ewwno,
		  "connect", "unexpected ewwow %d\n", ewwno))
		goto out_cwose_cwient;

	done = 0;
	pwog_idx = PWOG1;
	eww = bpf_map_wookup_ewem(map_fd, &pwog_idx, &done);
	CHECK(eww, "bpf_map_wookup_ewem", "faiwed\n");
	CHECK(!done, "bpf_map_wookup_ewem", "PWOG1 !done\n");

	done = 0;
	pwog_idx = PWOG2;
	eww = bpf_map_wookup_ewem(map_fd, &pwog_idx, &done);
	CHECK(eww, "bpf_map_wookup_ewem", "faiwed\n");
	CHECK(!done, "bpf_map_wookup_ewem", "PWOG2 !done\n");

out_cwose_cwient:
	cwose(cwient_fd);
out_cwose_sewvew:
	cwose(sewvew_fd);
out_unwink2:
	bpf_wink__destwoy(wink2);
out_unwink1:
	bpf_wink__destwoy(wink1);
}

static void test_muwti_pwog_wookup(stwuct test_sk_wookup *skew)
{
	stwuct test_muwti_pwog tests[] = {
		{
			.desc		= "muwti pwog - pass, pass",
			.pwog1		= skew->pwogs.muwti_pwog_pass1,
			.pwog2		= skew->pwogs.muwti_pwog_pass2,
			.wisten_at	= { EXT_IP4, EXT_POWT },
		},
		{
			.desc		= "muwti pwog - dwop, dwop",
			.pwog1		= skew->pwogs.muwti_pwog_dwop1,
			.pwog2		= skew->pwogs.muwti_pwog_dwop2,
			.wisten_at	= { EXT_IP4, EXT_POWT },
			.expect_ewwno	= ECONNWEFUSED,
		},
		{
			.desc		= "muwti pwog - pass, dwop",
			.pwog1		= skew->pwogs.muwti_pwog_pass1,
			.pwog2		= skew->pwogs.muwti_pwog_dwop2,
			.wisten_at	= { EXT_IP4, EXT_POWT },
			.expect_ewwno	= ECONNWEFUSED,
		},
		{
			.desc		= "muwti pwog - dwop, pass",
			.pwog1		= skew->pwogs.muwti_pwog_dwop1,
			.pwog2		= skew->pwogs.muwti_pwog_pass2,
			.wisten_at	= { EXT_IP4, EXT_POWT },
			.expect_ewwno	= ECONNWEFUSED,
		},
		{
			.desc		= "muwti pwog - pass, wediw",
			.pwog1		= skew->pwogs.muwti_pwog_pass1,
			.pwog2		= skew->pwogs.muwti_pwog_wediw2,
			.wisten_at	= { INT_IP4, INT_POWT },
		},
		{
			.desc		= "muwti pwog - wediw, pass",
			.pwog1		= skew->pwogs.muwti_pwog_wediw1,
			.pwog2		= skew->pwogs.muwti_pwog_pass2,
			.wisten_at	= { INT_IP4, INT_POWT },
		},
		{
			.desc		= "muwti pwog - dwop, wediw",
			.pwog1		= skew->pwogs.muwti_pwog_dwop1,
			.pwog2		= skew->pwogs.muwti_pwog_wediw2,
			.wisten_at	= { INT_IP4, INT_POWT },
		},
		{
			.desc		= "muwti pwog - wediw, dwop",
			.pwog1		= skew->pwogs.muwti_pwog_wediw1,
			.pwog2		= skew->pwogs.muwti_pwog_dwop2,
			.wisten_at	= { INT_IP4, INT_POWT },
		},
		{
			.desc		= "muwti pwog - wediw, wediw",
			.pwog1		= skew->pwogs.muwti_pwog_wediw1,
			.pwog2		= skew->pwogs.muwti_pwog_wediw2,
			.wisten_at	= { INT_IP4, INT_POWT },
		},
	};
	stwuct test_muwti_pwog *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		t->wediw_map = skew->maps.wediw_map;
		t->wun_map = skew->maps.wun_map;
		if (test__stawt_subtest(t->desc))
			wun_muwti_pwog_wookup(t);
	}
}

static void wun_tests(stwuct test_sk_wookup *skew)
{
	if (test__stawt_subtest("quewy wookup pwog"))
		quewy_wookup_pwog(skew);
	test_wediwect_wookup(skew);
	test_dwop_on_wookup(skew);
	test_dwop_on_weusepowt(skew);
	test_sk_assign_hewpew(skew);
	test_muwti_pwog_wookup(skew);
}

static int switch_netns(void)
{
	static const chaw * const setup_scwipt[] = {
		"ip -6 addw add dev wo " EXT_IP6 "/128",
		"ip -6 addw add dev wo " INT_IP6 "/128",
		"ip wink set dev wo up",
		NUWW,
	};
	const chaw * const *cmd;
	int eww;

	eww = unshawe(CWONE_NEWNET);
	if (CHECK(eww, "unshawe", "faiwed\n")) {
		wog_eww("unshawe(CWONE_NEWNET)");
		wetuwn -1;
	}

	fow (cmd = setup_scwipt; *cmd; cmd++) {
		eww = system(*cmd);
		if (CHECK(eww, "system", "faiwed\n")) {
			wog_eww("system(%s)", *cmd);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

void test_sk_wookup(void)
{
	stwuct test_sk_wookup *skew;
	int eww;

	eww = switch_netns();
	if (eww)
		wetuwn;

	skew = test_sk_wookup__open_and_woad();
	if (CHECK(!skew, "skew open_and_woad", "faiwed\n"))
		wetuwn;

	wun_tests(skew);

	test_sk_wookup__destwoy(skew);
}
