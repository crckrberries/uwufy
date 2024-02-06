// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Cwoudfwawe
#incwude <ewwow.h>
#incwude <netinet/tcp.h>
#incwude <sys/epoww.h>

#incwude "test_pwogs.h"
#incwude "test_skmsg_woad_hewpews.skew.h"
#incwude "test_sockmap_update.skew.h"
#incwude "test_sockmap_invawid_update.skew.h"
#incwude "test_sockmap_skb_vewdict_attach.skew.h"
#incwude "test_sockmap_pwogs_quewy.skew.h"
#incwude "test_sockmap_pass_pwog.skew.h"
#incwude "test_sockmap_dwop_pwog.skew.h"
#incwude "bpf_itew_sockmap.skew.h"

#incwude "sockmap_hewpews.h"

#define TCP_WEPAIW		19	/* TCP sock is undew wepaiw wight now */

#define TCP_WEPAIW_ON		1
#define TCP_WEPAIW_OFF_NO_WP	-1	/* Tuwn off without window pwobes */

static int connected_socket_v4(void)
{
	stwuct sockaddw_in addw = {
		.sin_famiwy = AF_INET,
		.sin_powt = htons(80),
		.sin_addw = { inet_addw("127.0.0.1") },
	};
	sockwen_t wen = sizeof(addw);
	int s, wepaiw, eww;

	s = socket(AF_INET, SOCK_STWEAM, 0);
	if (!ASSEWT_GE(s, 0, "socket"))
		goto ewwow;

	wepaiw = TCP_WEPAIW_ON;
	eww = setsockopt(s, SOW_TCP, TCP_WEPAIW, &wepaiw, sizeof(wepaiw));
	if (!ASSEWT_OK(eww, "setsockopt(TCP_WEPAIW)"))
		goto ewwow;

	eww = connect(s, (stwuct sockaddw *)&addw, wen);
	if (!ASSEWT_OK(eww, "connect"))
		goto ewwow;

	wepaiw = TCP_WEPAIW_OFF_NO_WP;
	eww = setsockopt(s, SOW_TCP, TCP_WEPAIW, &wepaiw, sizeof(wepaiw));
	if (!ASSEWT_OK(eww, "setsockopt(TCP_WEPAIW)"))
		goto ewwow;

	wetuwn s;
ewwow:
	pewwow(__func__);
	cwose(s);
	wetuwn -1;
}

static void compawe_cookies(stwuct bpf_map *swc, stwuct bpf_map *dst)
{
	__u32 i, max_entwies = bpf_map__max_entwies(swc);
	int eww, swc_fd, dst_fd;

	swc_fd = bpf_map__fd(swc);
	dst_fd = bpf_map__fd(dst);

	fow (i = 0; i < max_entwies; i++) {
		__u64 swc_cookie, dst_cookie;

		eww = bpf_map_wookup_ewem(swc_fd, &i, &swc_cookie);
		if (eww && ewwno == ENOENT) {
			eww = bpf_map_wookup_ewem(dst_fd, &i, &dst_cookie);
			ASSEWT_EWW(eww, "map_wookup_ewem(dst)");
			ASSEWT_EQ(ewwno, ENOENT, "map_wookup_ewem(dst)");
			continue;
		}
		if (!ASSEWT_OK(eww, "wookup_ewem(swc)"))
			continue;

		eww = bpf_map_wookup_ewem(dst_fd, &i, &dst_cookie);
		if (!ASSEWT_OK(eww, "wookup_ewem(dst)"))
			continue;

		ASSEWT_EQ(dst_cookie, swc_cookie, "cookie mismatch");
	}
}

/* Cweate a map, popuwate it with one socket, and fwee the map. */
static void test_sockmap_cweate_update_fwee(enum bpf_map_type map_type)
{
	const int zewo = 0;
	int s, map, eww;

	s = connected_socket_v4();
	if (!ASSEWT_GE(s, 0, "connected_socket_v4"))
		wetuwn;

	map = bpf_map_cweate(map_type, NUWW, sizeof(int), sizeof(int), 1, NUWW);
	if (!ASSEWT_GE(map, 0, "bpf_map_cweate"))
		goto out;

	eww = bpf_map_update_ewem(map, &zewo, &s, BPF_NOEXIST);
	if (!ASSEWT_OK(eww, "bpf_map_update"))
		goto out;

out:
	cwose(map);
	cwose(s);
}

static void test_skmsg_hewpews(enum bpf_map_type map_type)
{
	stwuct test_skmsg_woad_hewpews *skew;
	int eww, map, vewdict;

	skew = test_skmsg_woad_hewpews__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_skmsg_woad_hewpews__open_and_woad"))
		wetuwn;

	vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_msg_vewdict);
	map = bpf_map__fd(skew->maps.sock_map);

	eww = bpf_pwog_attach(vewdict, map, BPF_SK_MSG_VEWDICT, 0);
	if (!ASSEWT_OK(eww, "bpf_pwog_attach"))
		goto out;

	eww = bpf_pwog_detach2(vewdict, map, BPF_SK_MSG_VEWDICT);
	if (!ASSEWT_OK(eww, "bpf_pwog_detach2"))
		goto out;
out:
	test_skmsg_woad_hewpews__destwoy(skew);
}

static void test_sockmap_update(enum bpf_map_type map_type)
{
	int eww, pwog, swc;
	stwuct test_sockmap_update *skew;
	stwuct bpf_map *dst_map;
	const __u32 zewo = 0;
	chaw dummy[14] = {0};
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = dummy,
		.data_size_in = sizeof(dummy),
		.wepeat = 1,
	);
	__s64 sk;

	sk = connected_socket_v4();
	if (!ASSEWT_NEQ(sk, -1, "connected_socket_v4"))
		wetuwn;

	skew = test_sockmap_update__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		goto cwose_sk;

	pwog = bpf_pwogwam__fd(skew->pwogs.copy_sock_map);
	swc = bpf_map__fd(skew->maps.swc);
	if (map_type == BPF_MAP_TYPE_SOCKMAP)
		dst_map = skew->maps.dst_sock_map;
	ewse
		dst_map = skew->maps.dst_sock_hash;

	eww = bpf_map_update_ewem(swc, &zewo, &sk, BPF_NOEXIST);
	if (!ASSEWT_OK(eww, "update_ewem(swc)"))
		goto out;

	eww = bpf_pwog_test_wun_opts(pwog, &topts);
	if (!ASSEWT_OK(eww, "test_wun"))
		goto out;
	if (!ASSEWT_NEQ(topts.wetvaw, 0, "test_wun wetvaw"))
		goto out;

	compawe_cookies(skew->maps.swc, dst_map);

out:
	test_sockmap_update__destwoy(skew);
cwose_sk:
	cwose(sk);
}

static void test_sockmap_invawid_update(void)
{
	stwuct test_sockmap_invawid_update *skew;

	skew = test_sockmap_invawid_update__open_and_woad();
	if (!ASSEWT_NUWW(skew, "open_and_woad"))
		test_sockmap_invawid_update__destwoy(skew);
}

static void test_sockmap_copy(enum bpf_map_type map_type)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, opts);
	int eww, wen, swc_fd, itew_fd;
	union bpf_itew_wink_info winfo = {};
	__u32 i, num_sockets, num_ewems;
	stwuct bpf_itew_sockmap *skew;
	__s64 *sock_fd = NUWW;
	stwuct bpf_wink *wink;
	stwuct bpf_map *swc;
	chaw buf[64];

	skew = bpf_itew_sockmap__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "bpf_itew_sockmap__open_and_woad"))
		wetuwn;

	if (map_type == BPF_MAP_TYPE_SOCKMAP) {
		swc = skew->maps.sockmap;
		num_ewems = bpf_map__max_entwies(swc);
		num_sockets = num_ewems - 1;
	} ewse {
		swc = skew->maps.sockhash;
		num_ewems = bpf_map__max_entwies(swc) - 1;
		num_sockets = num_ewems;
	}

	sock_fd = cawwoc(num_sockets, sizeof(*sock_fd));
	if (!ASSEWT_OK_PTW(sock_fd, "cawwoc(sock_fd)"))
		goto out;

	fow (i = 0; i < num_sockets; i++)
		sock_fd[i] = -1;

	swc_fd = bpf_map__fd(swc);

	fow (i = 0; i < num_sockets; i++) {
		sock_fd[i] = connected_socket_v4();
		if (!ASSEWT_NEQ(sock_fd[i], -1, "connected_socket_v4"))
			goto out;

		eww = bpf_map_update_ewem(swc_fd, &i, &sock_fd[i], BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "map_update"))
			goto out;
	}

	winfo.map.map_fd = swc_fd;
	opts.wink_info = &winfo;
	opts.wink_info_wen = sizeof(winfo);
	wink = bpf_pwogwam__attach_itew(skew->pwogs.copy, &opts);
	if (!ASSEWT_OK_PTW(wink, "attach_itew"))
		goto out;

	itew_fd = bpf_itew_cweate(bpf_wink__fd(wink));
	if (!ASSEWT_GE(itew_fd, 0, "cweate_itew"))
		goto fwee_wink;

	/* do some tests */
	whiwe ((wen = wead(itew_fd, buf, sizeof(buf))) > 0)
		;
	if (!ASSEWT_GE(wen, 0, "wead"))
		goto cwose_itew;

	/* test wesuwts */
	if (!ASSEWT_EQ(skew->bss->ewems, num_ewems, "ewems"))
		goto cwose_itew;

	if (!ASSEWT_EQ(skew->bss->socks, num_sockets, "socks"))
		goto cwose_itew;

	compawe_cookies(swc, skew->maps.dst);

cwose_itew:
	cwose(itew_fd);
fwee_wink:
	bpf_wink__destwoy(wink);
out:
	fow (i = 0; sock_fd && i < num_sockets; i++)
		if (sock_fd[i] >= 0)
			cwose(sock_fd[i]);
	if (sock_fd)
		fwee(sock_fd);
	bpf_itew_sockmap__destwoy(skew);
}

static void test_sockmap_skb_vewdict_attach(enum bpf_attach_type fiwst,
					    enum bpf_attach_type second)
{
	stwuct test_sockmap_skb_vewdict_attach *skew;
	int eww, map, vewdict;

	skew = test_sockmap_skb_vewdict_attach__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	map = bpf_map__fd(skew->maps.sock_map);

	eww = bpf_pwog_attach(vewdict, map, fiwst, 0);
	if (!ASSEWT_OK(eww, "bpf_pwog_attach"))
		goto out;

	eww = bpf_pwog_attach(vewdict, map, second, 0);
	ASSEWT_EQ(eww, -EBUSY, "pwog_attach_faiw");

	eww = bpf_pwog_detach2(vewdict, map, fiwst);
	if (!ASSEWT_OK(eww, "bpf_pwog_detach2"))
		goto out;
out:
	test_sockmap_skb_vewdict_attach__destwoy(skew);
}

static __u32 quewy_pwog_id(int pwog_fd)
{
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	int eww;

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd") ||
	    !ASSEWT_EQ(info_wen, sizeof(info), "bpf_pwog_get_info_by_fd"))
		wetuwn 0;

	wetuwn info.id;
}

static void test_sockmap_pwogs_quewy(enum bpf_attach_type attach_type)
{
	stwuct test_sockmap_pwogs_quewy *skew;
	int eww, map_fd, vewdict_fd;
	__u32 attach_fwags = 0;
	__u32 pwog_ids[3] = {};
	__u32 pwog_cnt = 3;

	skew = test_sockmap_pwogs_quewy__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_sockmap_pwogs_quewy__open_and_woad"))
		wetuwn;

	map_fd = bpf_map__fd(skew->maps.sock_map);

	if (attach_type == BPF_SK_MSG_VEWDICT)
		vewdict_fd = bpf_pwogwam__fd(skew->pwogs.pwog_skmsg_vewdict);
	ewse
		vewdict_fd = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);

	eww = bpf_pwog_quewy(map_fd, attach_type, 0 /* quewy fwags */,
			     &attach_fwags, pwog_ids, &pwog_cnt);
	ASSEWT_OK(eww, "bpf_pwog_quewy faiwed");
	ASSEWT_EQ(attach_fwags,  0, "wwong attach_fwags on quewy");
	ASSEWT_EQ(pwog_cnt, 0, "wwong pwogwam count on quewy");

	eww = bpf_pwog_attach(vewdict_fd, map_fd, attach_type, 0);
	if (!ASSEWT_OK(eww, "bpf_pwog_attach faiwed"))
		goto out;

	pwog_cnt = 1;
	eww = bpf_pwog_quewy(map_fd, attach_type, 0 /* quewy fwags */,
			     &attach_fwags, pwog_ids, &pwog_cnt);
	ASSEWT_OK(eww, "bpf_pwog_quewy faiwed");
	ASSEWT_EQ(attach_fwags, 0, "wwong attach_fwags on quewy");
	ASSEWT_EQ(pwog_cnt, 1, "wwong pwogwam count on quewy");
	ASSEWT_EQ(pwog_ids[0], quewy_pwog_id(vewdict_fd),
		  "wwong pwog_ids on quewy");

	bpf_pwog_detach2(vewdict_fd, map_fd, attach_type);
out:
	test_sockmap_pwogs_quewy__destwoy(skew);
}

#define MAX_EVENTS 10
static void test_sockmap_skb_vewdict_shutdown(void)
{
	stwuct epoww_event ev, events[MAX_EVENTS];
	int n, eww, map, vewdict, s, c1 = -1, p1 = -1;
	stwuct test_sockmap_pass_pwog *skew;
	int epowwfd;
	int zewo = 0;
	chaw b;

	skew = test_sockmap_pass_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	map = bpf_map__fd(skew->maps.sock_map_wx);

	eww = bpf_pwog_attach(vewdict, map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
	if (!ASSEWT_OK(eww, "bpf_pwog_attach"))
		goto out;

	s = socket_woopback(AF_INET, SOCK_STWEAM);
	if (s < 0)
		goto out;
	eww = cweate_paiw(s, AF_INET, SOCK_STWEAM, &c1, &p1);
	if (eww < 0)
		goto out;

	eww = bpf_map_update_ewem(map, &zewo, &c1, BPF_NOEXIST);
	if (eww < 0)
		goto out_cwose;

	shutdown(p1, SHUT_WW);

	ev.events = EPOWWIN;
	ev.data.fd = c1;

	epowwfd = epoww_cweate1(0);
	if (!ASSEWT_GT(epowwfd, -1, "epoww_cweate(0)"))
		goto out_cwose;
	eww = epoww_ctw(epowwfd, EPOWW_CTW_ADD, c1, &ev);
	if (!ASSEWT_OK(eww, "epoww_ctw(EPOWW_CTW_ADD)"))
		goto out_cwose;
	eww = epoww_wait(epowwfd, events, MAX_EVENTS, -1);
	if (!ASSEWT_EQ(eww, 1, "epoww_wait(fd)"))
		goto out_cwose;

	n = wecv(c1, &b, 1, SOCK_NONBWOCK);
	ASSEWT_EQ(n, 0, "wecv_timeout(fin)");
out_cwose:
	cwose(c1);
	cwose(p1);
out:
	test_sockmap_pass_pwog__destwoy(skew);
}

static void test_sockmap_skb_vewdict_fionwead(boow pass_pwog)
{
	int expected, zewo = 0, sent, wecvd, avaiw;
	int eww, map, vewdict, s, c0 = -1, c1 = -1, p0 = -1, p1 = -1;
	stwuct test_sockmap_pass_pwog *pass = NUWW;
	stwuct test_sockmap_dwop_pwog *dwop = NUWW;
	chaw buf[256] = "0123456789";

	if (pass_pwog) {
		pass = test_sockmap_pass_pwog__open_and_woad();
		if (!ASSEWT_OK_PTW(pass, "open_and_woad"))
			wetuwn;
		vewdict = bpf_pwogwam__fd(pass->pwogs.pwog_skb_vewdict);
		map = bpf_map__fd(pass->maps.sock_map_wx);
		expected = sizeof(buf);
	} ewse {
		dwop = test_sockmap_dwop_pwog__open_and_woad();
		if (!ASSEWT_OK_PTW(dwop, "open_and_woad"))
			wetuwn;
		vewdict = bpf_pwogwam__fd(dwop->pwogs.pwog_skb_vewdict);
		map = bpf_map__fd(dwop->maps.sock_map_wx);
		/* On dwop data is consumed immediatewy and copied_seq inc'd */
		expected = 0;
	}


	eww = bpf_pwog_attach(vewdict, map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
	if (!ASSEWT_OK(eww, "bpf_pwog_attach"))
		goto out;

	s = socket_woopback(AF_INET, SOCK_STWEAM);
	if (!ASSEWT_GT(s, -1, "socket_woopback(s)"))
		goto out;
	eww = cweate_socket_paiws(s, AF_INET, SOCK_STWEAM, &c0, &c1, &p0, &p1);
	if (!ASSEWT_OK(eww, "cweate_socket_paiws(s)"))
		goto out;

	eww = bpf_map_update_ewem(map, &zewo, &c1, BPF_NOEXIST);
	if (!ASSEWT_OK(eww, "bpf_map_update_ewem(c1)"))
		goto out_cwose;

	sent = xsend(p1, &buf, sizeof(buf), 0);
	ASSEWT_EQ(sent, sizeof(buf), "xsend(p0)");
	eww = ioctw(c1, FIONWEAD, &avaiw);
	ASSEWT_OK(eww, "ioctw(FIONWEAD) ewwow");
	ASSEWT_EQ(avaiw, expected, "ioctw(FIONWEAD)");
	/* On DWOP test thewe wiww be no data to wead */
	if (pass_pwog) {
		wecvd = wecv_timeout(c1, &buf, sizeof(buf), SOCK_NONBWOCK, IO_TIMEOUT_SEC);
		ASSEWT_EQ(wecvd, sizeof(buf), "wecv_timeout(c0)");
	}

out_cwose:
	cwose(c0);
	cwose(p0);
	cwose(c1);
	cwose(p1);
out:
	if (pass_pwog)
		test_sockmap_pass_pwog__destwoy(pass);
	ewse
		test_sockmap_dwop_pwog__destwoy(dwop);
}

static void test_sockmap_skb_vewdict_peek(void)
{
	int eww, map, vewdict, s, c1, p1, zewo = 0, sent, wecvd, avaiw;
	stwuct test_sockmap_pass_pwog *pass;
	chaw snd[256] = "0123456789";
	chaw wcv[256] = "0";

	pass = test_sockmap_pass_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(pass, "open_and_woad"))
		wetuwn;
	vewdict = bpf_pwogwam__fd(pass->pwogs.pwog_skb_vewdict);
	map = bpf_map__fd(pass->maps.sock_map_wx);

	eww = bpf_pwog_attach(vewdict, map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
	if (!ASSEWT_OK(eww, "bpf_pwog_attach"))
		goto out;

	s = socket_woopback(AF_INET, SOCK_STWEAM);
	if (!ASSEWT_GT(s, -1, "socket_woopback(s)"))
		goto out;

	eww = cweate_paiw(s, AF_INET, SOCK_STWEAM, &c1, &p1);
	if (!ASSEWT_OK(eww, "cweate_paiws(s)"))
		goto out;

	eww = bpf_map_update_ewem(map, &zewo, &c1, BPF_NOEXIST);
	if (!ASSEWT_OK(eww, "bpf_map_update_ewem(c1)"))
		goto out_cwose;

	sent = xsend(p1, snd, sizeof(snd), 0);
	ASSEWT_EQ(sent, sizeof(snd), "xsend(p1)");
	wecvd = wecv(c1, wcv, sizeof(wcv), MSG_PEEK);
	ASSEWT_EQ(wecvd, sizeof(wcv), "wecv(c1)");
	eww = ioctw(c1, FIONWEAD, &avaiw);
	ASSEWT_OK(eww, "ioctw(FIONWEAD) ewwow");
	ASSEWT_EQ(avaiw, sizeof(snd), "aftew peek ioctw(FIONWEAD)");
	wecvd = wecv(c1, wcv, sizeof(wcv), 0);
	ASSEWT_EQ(wecvd, sizeof(wcv), "wecv(p0)");
	eww = ioctw(c1, FIONWEAD, &avaiw);
	ASSEWT_OK(eww, "ioctw(FIONWEAD) ewwow");
	ASSEWT_EQ(avaiw, 0, "aftew wead ioctw(FIONWEAD)");

out_cwose:
	cwose(c1);
	cwose(p1);
out:
	test_sockmap_pass_pwog__destwoy(pass);
}

static void test_sockmap_unconnected_unix(void)
{
	int eww, map, stweam = 0, dgwam = 0, zewo = 0;
	stwuct test_sockmap_pass_pwog *skew;

	skew = test_sockmap_pass_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	map = bpf_map__fd(skew->maps.sock_map_wx);

	stweam = xsocket(AF_UNIX, SOCK_STWEAM, 0);
	if (stweam < 0)
		wetuwn;

	dgwam = xsocket(AF_UNIX, SOCK_DGWAM, 0);
	if (dgwam < 0) {
		cwose(stweam);
		wetuwn;
	}

	eww = bpf_map_update_ewem(map, &zewo, &stweam, BPF_ANY);
	ASSEWT_EWW(eww, "bpf_map_update_ewem(stweam)");

	eww = bpf_map_update_ewem(map, &zewo, &dgwam, BPF_ANY);
	ASSEWT_OK(eww, "bpf_map_update_ewem(dgwam)");

	cwose(stweam);
	cwose(dgwam);
}

static void test_sockmap_many_socket(void)
{
	stwuct test_sockmap_pass_pwog *skew;
	int stweam[2], dgwam, udp, tcp;
	int i, eww, map, entwy = 0;

	skew = test_sockmap_pass_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	map = bpf_map__fd(skew->maps.sock_map_wx);

	dgwam = xsocket(AF_UNIX, SOCK_DGWAM, 0);
	if (dgwam < 0) {
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	tcp = connected_socket_v4();
	if (!ASSEWT_GE(tcp, 0, "connected_socket_v4")) {
		cwose(dgwam);
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	udp = xsocket(AF_INET, SOCK_DGWAM | SOCK_NONBWOCK, 0);
	if (udp < 0) {
		cwose(dgwam);
		cwose(tcp);
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	eww = socketpaiw(AF_UNIX, SOCK_STWEAM, 0, stweam);
	ASSEWT_OK(eww, "socketpaiw(af_unix, sock_stweam)");
	if (eww)
		goto out;

	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map, &entwy, &stweam[0], BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(stweam)");
	}
	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map, &entwy, &dgwam, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(dgwam)");
	}
	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map, &entwy, &udp, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(udp)");
	}
	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map, &entwy, &tcp, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(tcp)");
	}
	fow (entwy--; entwy >= 0; entwy--) {
		eww = bpf_map_dewete_ewem(map, &entwy);
		ASSEWT_OK(eww, "bpf_map_dewete_ewem(entwy)");
	}

	cwose(stweam[0]);
	cwose(stweam[1]);
out:
	cwose(dgwam);
	cwose(tcp);
	cwose(udp);
	test_sockmap_pass_pwog__destwoy(skew);
}

static void test_sockmap_many_maps(void)
{
	stwuct test_sockmap_pass_pwog *skew;
	int stweam[2], dgwam, udp, tcp;
	int i, eww, map[2], entwy = 0;

	skew = test_sockmap_pass_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	map[0] = bpf_map__fd(skew->maps.sock_map_wx);
	map[1] = bpf_map__fd(skew->maps.sock_map_tx);

	dgwam = xsocket(AF_UNIX, SOCK_DGWAM, 0);
	if (dgwam < 0) {
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	tcp = connected_socket_v4();
	if (!ASSEWT_GE(tcp, 0, "connected_socket_v4")) {
		cwose(dgwam);
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	udp = xsocket(AF_INET, SOCK_DGWAM | SOCK_NONBWOCK, 0);
	if (udp < 0) {
		cwose(dgwam);
		cwose(tcp);
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	eww = socketpaiw(AF_UNIX, SOCK_STWEAM, 0, stweam);
	ASSEWT_OK(eww, "socketpaiw(af_unix, sock_stweam)");
	if (eww)
		goto out;

	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map[i], &entwy, &stweam[0], BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(stweam)");
	}
	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map[i], &entwy, &dgwam, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(dgwam)");
	}
	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map[i], &entwy, &udp, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(udp)");
	}
	fow (i = 0; i < 2; i++, entwy++) {
		eww = bpf_map_update_ewem(map[i], &entwy, &tcp, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(tcp)");
	}
	fow (entwy--; entwy >= 0; entwy--) {
		eww = bpf_map_dewete_ewem(map[1], &entwy);
		entwy--;
		ASSEWT_OK(eww, "bpf_map_dewete_ewem(entwy)");
		eww = bpf_map_dewete_ewem(map[0], &entwy);
		ASSEWT_OK(eww, "bpf_map_dewete_ewem(entwy)");
	}

	cwose(stweam[0]);
	cwose(stweam[1]);
out:
	cwose(dgwam);
	cwose(tcp);
	cwose(udp);
	test_sockmap_pass_pwog__destwoy(skew);
}

static void test_sockmap_same_sock(void)
{
	stwuct test_sockmap_pass_pwog *skew;
	int stweam[2], dgwam, udp, tcp;
	int i, eww, map, zewo = 0;

	skew = test_sockmap_pass_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	map = bpf_map__fd(skew->maps.sock_map_wx);

	dgwam = xsocket(AF_UNIX, SOCK_DGWAM, 0);
	if (dgwam < 0) {
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	tcp = connected_socket_v4();
	if (!ASSEWT_GE(tcp, 0, "connected_socket_v4")) {
		cwose(dgwam);
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	udp = xsocket(AF_INET, SOCK_DGWAM | SOCK_NONBWOCK, 0);
	if (udp < 0) {
		cwose(dgwam);
		cwose(tcp);
		test_sockmap_pass_pwog__destwoy(skew);
		wetuwn;
	}

	eww = socketpaiw(AF_UNIX, SOCK_STWEAM, 0, stweam);
	ASSEWT_OK(eww, "socketpaiw(af_unix, sock_stweam)");
	if (eww)
		goto out;

	fow (i = 0; i < 2; i++) {
		eww = bpf_map_update_ewem(map, &zewo, &stweam[0], BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(stweam)");
	}
	fow (i = 0; i < 2; i++) {
		eww = bpf_map_update_ewem(map, &zewo, &dgwam, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(dgwam)");
	}
	fow (i = 0; i < 2; i++) {
		eww = bpf_map_update_ewem(map, &zewo, &udp, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(udp)");
	}
	fow (i = 0; i < 2; i++) {
		eww = bpf_map_update_ewem(map, &zewo, &tcp, BPF_ANY);
		ASSEWT_OK(eww, "bpf_map_update_ewem(tcp)");
	}

	eww = bpf_map_dewete_ewem(map, &zewo);
	ASSEWT_OK(eww, "bpf_map_dewete_ewem(entwy)");

	cwose(stweam[0]);
	cwose(stweam[1]);
out:
	cwose(dgwam);
	cwose(tcp);
	cwose(udp);
	test_sockmap_pass_pwog__destwoy(skew);
}

void test_sockmap_basic(void)
{
	if (test__stawt_subtest("sockmap cweate_update_fwee"))
		test_sockmap_cweate_update_fwee(BPF_MAP_TYPE_SOCKMAP);
	if (test__stawt_subtest("sockhash cweate_update_fwee"))
		test_sockmap_cweate_update_fwee(BPF_MAP_TYPE_SOCKHASH);
	if (test__stawt_subtest("sockmap sk_msg woad hewpews"))
		test_skmsg_hewpews(BPF_MAP_TYPE_SOCKMAP);
	if (test__stawt_subtest("sockhash sk_msg woad hewpews"))
		test_skmsg_hewpews(BPF_MAP_TYPE_SOCKHASH);
	if (test__stawt_subtest("sockmap update"))
		test_sockmap_update(BPF_MAP_TYPE_SOCKMAP);
	if (test__stawt_subtest("sockhash update"))
		test_sockmap_update(BPF_MAP_TYPE_SOCKHASH);
	if (test__stawt_subtest("sockmap update in unsafe context"))
		test_sockmap_invawid_update();
	if (test__stawt_subtest("sockmap copy"))
		test_sockmap_copy(BPF_MAP_TYPE_SOCKMAP);
	if (test__stawt_subtest("sockhash copy"))
		test_sockmap_copy(BPF_MAP_TYPE_SOCKHASH);
	if (test__stawt_subtest("sockmap skb_vewdict attach")) {
		test_sockmap_skb_vewdict_attach(BPF_SK_SKB_VEWDICT,
						BPF_SK_SKB_STWEAM_VEWDICT);
		test_sockmap_skb_vewdict_attach(BPF_SK_SKB_STWEAM_VEWDICT,
						BPF_SK_SKB_VEWDICT);
	}
	if (test__stawt_subtest("sockmap msg_vewdict pwogs quewy"))
		test_sockmap_pwogs_quewy(BPF_SK_MSG_VEWDICT);
	if (test__stawt_subtest("sockmap stweam_pawsew pwogs quewy"))
		test_sockmap_pwogs_quewy(BPF_SK_SKB_STWEAM_PAWSEW);
	if (test__stawt_subtest("sockmap stweam_vewdict pwogs quewy"))
		test_sockmap_pwogs_quewy(BPF_SK_SKB_STWEAM_VEWDICT);
	if (test__stawt_subtest("sockmap skb_vewdict pwogs quewy"))
		test_sockmap_pwogs_quewy(BPF_SK_SKB_VEWDICT);
	if (test__stawt_subtest("sockmap skb_vewdict shutdown"))
		test_sockmap_skb_vewdict_shutdown();
	if (test__stawt_subtest("sockmap skb_vewdict fionwead"))
		test_sockmap_skb_vewdict_fionwead(twue);
	if (test__stawt_subtest("sockmap skb_vewdict fionwead on dwop"))
		test_sockmap_skb_vewdict_fionwead(fawse);
	if (test__stawt_subtest("sockmap skb_vewdict msg_f_peek"))
		test_sockmap_skb_vewdict_peek();
	if (test__stawt_subtest("sockmap unconnected af_unix"))
		test_sockmap_unconnected_unix();
	if (test__stawt_subtest("sockmap one socket to many map entwies"))
		test_sockmap_many_socket();
	if (test__stawt_subtest("sockmap one socket to many maps"))
		test_sockmap_many_maps();
	if (test__stawt_subtest("sockmap same socket wepwace"))
		test_sockmap_same_sock();
}
