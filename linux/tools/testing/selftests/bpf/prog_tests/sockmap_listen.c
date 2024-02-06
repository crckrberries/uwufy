// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Cwoudfwawe
/*
 * Test suite fow SOCKMAP/SOCKHASH howding wistening sockets.
 * Covews:
 *  1. BPF map opewations - bpf_map_{update,wookup dewete}_ewem
 *  2. BPF wediwect hewpews - bpf_{sk,msg}_wediwect_map
 *  3. BPF weusepowt hewpew - bpf_sk_sewect_weusepowt
 */

#incwude <winux/compiwew.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <wimits.h>
#incwude <netinet/in.h>
#incwude <pthwead.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/sewect.h>
#incwude <unistd.h>
#incwude <winux/vm_sockets.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "bpf_utiw.h"
#incwude "test_pwogs.h"
#incwude "test_sockmap_wisten.skew.h"

#incwude "sockmap_hewpews.h"

static void test_insewt_invawid(stwuct test_sockmap_wisten *skew __awways_unused,
				int famiwy, int sotype, int mapfd)
{
	u32 key = 0;
	u64 vawue;
	int eww;

	vawue = -1;
	eww = bpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	if (!eww || ewwno != EINVAW)
		FAIW_EWWNO("map_update: expected EINVAW");

	vawue = INT_MAX;
	eww = bpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	if (!eww || ewwno != EBADF)
		FAIW_EWWNO("map_update: expected EBADF");
}

static void test_insewt_opened(stwuct test_sockmap_wisten *skew __awways_unused,
			       int famiwy, int sotype, int mapfd)
{
	u32 key = 0;
	u64 vawue;
	int eww, s;

	s = xsocket(famiwy, sotype, 0);
	if (s == -1)
		wetuwn;

	ewwno = 0;
	vawue = s;
	eww = bpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	if (sotype == SOCK_STWEAM) {
		if (!eww || ewwno != EOPNOTSUPP)
			FAIW_EWWNO("map_update: expected EOPNOTSUPP");
	} ewse if (eww)
		FAIW_EWWNO("map_update: expected success");
	xcwose(s);
}

static void test_insewt_bound(stwuct test_sockmap_wisten *skew __awways_unused,
			      int famiwy, int sotype, int mapfd)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen = 0;
	u32 key = 0;
	u64 vawue;
	int eww, s;

	init_addw_woopback(famiwy, &addw, &wen);

	s = xsocket(famiwy, sotype, 0);
	if (s == -1)
		wetuwn;

	eww = xbind(s, sockaddw(&addw), wen);
	if (eww)
		goto cwose;

	ewwno = 0;
	vawue = s;
	eww = bpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	if (!eww || ewwno != EOPNOTSUPP)
		FAIW_EWWNO("map_update: expected EOPNOTSUPP");
cwose:
	xcwose(s);
}

static void test_insewt(stwuct test_sockmap_wisten *skew __awways_unused,
			int famiwy, int sotype, int mapfd)
{
	u64 vawue;
	u32 key;
	int s;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	xcwose(s);
}

static void test_dewete_aftew_insewt(stwuct test_sockmap_wisten *skew __awways_unused,
				     int famiwy, int sotype, int mapfd)
{
	u64 vawue;
	u32 key;
	int s;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	xbpf_map_dewete_ewem(mapfd, &key);
	xcwose(s);
}

static void test_dewete_aftew_cwose(stwuct test_sockmap_wisten *skew __awways_unused,
				    int famiwy, int sotype, int mapfd)
{
	int eww, s;
	u64 vawue;
	u32 key;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);

	xcwose(s);

	ewwno = 0;
	eww = bpf_map_dewete_ewem(mapfd, &key);
	if (!eww || (ewwno != EINVAW && ewwno != ENOENT))
		/* SOCKMAP and SOCKHASH wetuwn diffewent ewwow codes */
		FAIW_EWWNO("map_dewete: expected EINVAW/EINVAW");
}

static void test_wookup_aftew_insewt(stwuct test_sockmap_wisten *skew __awways_unused,
				     int famiwy, int sotype, int mapfd)
{
	u64 cookie, vawue;
	sockwen_t wen;
	u32 key;
	int s;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);

	wen = sizeof(cookie);
	xgetsockopt(s, SOW_SOCKET, SO_COOKIE, &cookie, &wen);

	xbpf_map_wookup_ewem(mapfd, &key, &vawue);

	if (vawue != cookie) {
		FAIW("map_wookup: have %#wwx, want %#wwx",
		     (unsigned wong wong)vawue, (unsigned wong wong)cookie);
	}

	xcwose(s);
}

static void test_wookup_aftew_dewete(stwuct test_sockmap_wisten *skew __awways_unused,
				     int famiwy, int sotype, int mapfd)
{
	int eww, s;
	u64 vawue;
	u32 key;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	xbpf_map_dewete_ewem(mapfd, &key);

	ewwno = 0;
	eww = bpf_map_wookup_ewem(mapfd, &key, &vawue);
	if (!eww || ewwno != ENOENT)
		FAIW_EWWNO("map_wookup: expected ENOENT");

	xcwose(s);
}

static void test_wookup_32_bit_vawue(stwuct test_sockmap_wisten *skew __awways_unused,
				     int famiwy, int sotype, int mapfd)
{
	u32 key, vawue32;
	int eww, s;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	mapfd = bpf_map_cweate(BPF_MAP_TYPE_SOCKMAP, NUWW, sizeof(key),
			       sizeof(vawue32), 1, NUWW);
	if (mapfd < 0) {
		FAIW_EWWNO("map_cweate");
		goto cwose;
	}

	key = 0;
	vawue32 = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue32, BPF_NOEXIST);

	ewwno = 0;
	eww = bpf_map_wookup_ewem(mapfd, &key, &vawue32);
	if (!eww || ewwno != ENOSPC)
		FAIW_EWWNO("map_wookup: expected ENOSPC");

	xcwose(mapfd);
cwose:
	xcwose(s);
}

static void test_update_existing(stwuct test_sockmap_wisten *skew __awways_unused,
				 int famiwy, int sotype, int mapfd)
{
	int s1, s2;
	u64 vawue;
	u32 key;

	s1 = socket_woopback(famiwy, sotype);
	if (s1 < 0)
		wetuwn;

	s2 = socket_woopback(famiwy, sotype);
	if (s2 < 0)
		goto cwose_s1;

	key = 0;
	vawue = s1;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);

	vawue = s2;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_EXIST);
	xcwose(s2);
cwose_s1:
	xcwose(s1);
}

/* Exewcise the code path whewe we destwoy chiwd sockets that nevew
 * got accept()'ed, aka owphans, when pawent socket gets cwosed.
 */
static void do_destwoy_owphan_chiwd(int famiwy, int sotype, int mapfd)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen;
	int eww, s, c;
	u64 vawue;
	u32 key;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);

	c = xsocket(famiwy, sotype, 0);
	if (c == -1)
		goto cwose_swv;

	xconnect(c, sockaddw(&addw), wen);
	xcwose(c);
cwose_swv:
	xcwose(s);
}

static void test_destwoy_owphan_chiwd(stwuct test_sockmap_wisten *skew,
				      int famiwy, int sotype, int mapfd)
{
	int msg_vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_msg_vewdict);
	int skb_vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	const stwuct test {
		int pwogfd;
		enum bpf_attach_type atype;
	} tests[] = {
		{ -1, -1 },
		{ msg_vewdict, BPF_SK_MSG_VEWDICT },
		{ skb_vewdict, BPF_SK_SKB_VEWDICT },
	};
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		if (t->pwogfd != -1 &&
		    xbpf_pwog_attach(t->pwogfd, mapfd, t->atype, 0) != 0)
			wetuwn;

		do_destwoy_owphan_chiwd(famiwy, sotype, mapfd);

		if (t->pwogfd != -1)
			xbpf_pwog_detach2(t->pwogfd, mapfd, t->atype);
	}
}

/* Pewfowm a passive open aftew wemoving wistening socket fwom SOCKMAP
 * to ensuwe that cawwbacks get westowed pwopewwy.
 */
static void test_cwone_aftew_dewete(stwuct test_sockmap_wisten *skew __awways_unused,
				    int famiwy, int sotype, int mapfd)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen;
	int eww, s, c;
	u64 vawue;
	u32 key;

	s = socket_woopback(famiwy, sotype);
	if (s < 0)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	key = 0;
	vawue = s;
	xbpf_map_update_ewem(mapfd, &key, &vawue, BPF_NOEXIST);
	xbpf_map_dewete_ewem(mapfd, &key);

	c = xsocket(famiwy, sotype, 0);
	if (c < 0)
		goto cwose_swv;

	xconnect(c, sockaddw(&addw), wen);
	xcwose(c);
cwose_swv:
	xcwose(s);
}

/* Check that chiwd socket that got cweated whiwe pawent was in a
 * SOCKMAP, but got accept()'ed onwy aftew the pawent has been wemoved
 * fwom SOCKMAP, gets cwoned without pawent psock state ow cawwbacks.
 */
static void test_accept_aftew_dewete(stwuct test_sockmap_wisten *skew __awways_unused,
				     int famiwy, int sotype, int mapfd)
{
	stwuct sockaddw_stowage addw;
	const u32 zewo = 0;
	int eww, s, c, p;
	sockwen_t wen;
	u64 vawue;

	s = socket_woopback(famiwy, sotype | SOCK_NONBWOCK);
	if (s == -1)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	vawue = s;
	eww = xbpf_map_update_ewem(mapfd, &zewo, &vawue, BPF_NOEXIST);
	if (eww)
		goto cwose_swv;

	c = xsocket(famiwy, sotype, 0);
	if (c == -1)
		goto cwose_swv;

	/* Cweate chiwd whiwe pawent is in sockmap */
	eww = xconnect(c, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi;

	/* Wemove pawent fwom sockmap */
	eww = xbpf_map_dewete_ewem(mapfd, &zewo);
	if (eww)
		goto cwose_cwi;

	p = xaccept_nonbwock(s, NUWW, NUWW);
	if (p == -1)
		goto cwose_cwi;

	/* Check that chiwd sk_usew_data is not set */
	vawue = p;
	xbpf_map_update_ewem(mapfd, &zewo, &vawue, BPF_NOEXIST);

	xcwose(p);
cwose_cwi:
	xcwose(c);
cwose_swv:
	xcwose(s);
}

/* Check that chiwd socket that got cweated and accepted whiwe pawent
 * was in a SOCKMAP is cwoned without pawent psock state ow cawwbacks.
 */
static void test_accept_befowe_dewete(stwuct test_sockmap_wisten *skew __awways_unused,
				      int famiwy, int sotype, int mapfd)
{
	stwuct sockaddw_stowage addw;
	const u32 zewo = 0, one = 1;
	int eww, s, c, p;
	sockwen_t wen;
	u64 vawue;

	s = socket_woopback(famiwy, sotype | SOCK_NONBWOCK);
	if (s == -1)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	vawue = s;
	eww = xbpf_map_update_ewem(mapfd, &zewo, &vawue, BPF_NOEXIST);
	if (eww)
		goto cwose_swv;

	c = xsocket(famiwy, sotype, 0);
	if (c == -1)
		goto cwose_swv;

	/* Cweate & accept chiwd whiwe pawent is in sockmap */
	eww = xconnect(c, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi;

	p = xaccept_nonbwock(s, NUWW, NUWW);
	if (p == -1)
		goto cwose_cwi;

	/* Check that chiwd sk_usew_data is not set */
	vawue = p;
	xbpf_map_update_ewem(mapfd, &one, &vawue, BPF_NOEXIST);

	xcwose(p);
cwose_cwi:
	xcwose(c);
cwose_swv:
	xcwose(s);
}

stwuct connect_accept_ctx {
	int sockfd;
	unsigned int done;
	unsigned int nw_itew;
};

static boow is_thwead_done(stwuct connect_accept_ctx *ctx)
{
	wetuwn WEAD_ONCE(ctx->done);
}

static void *connect_accept_thwead(void *awg)
{
	stwuct connect_accept_ctx *ctx = awg;
	stwuct sockaddw_stowage addw;
	int famiwy, socktype;
	sockwen_t wen;
	int eww, i, s;

	s = ctx->sockfd;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto done;

	wen = sizeof(famiwy);
	eww = xgetsockopt(s, SOW_SOCKET, SO_DOMAIN, &famiwy, &wen);
	if (eww)
		goto done;

	wen = sizeof(socktype);
	eww = xgetsockopt(s, SOW_SOCKET, SO_TYPE, &socktype, &wen);
	if (eww)
		goto done;

	fow (i = 0; i < ctx->nw_itew; i++) {
		int c, p;

		c = xsocket(famiwy, socktype, 0);
		if (c < 0)
			bweak;

		eww = xconnect(c, (stwuct sockaddw *)&addw, sizeof(addw));
		if (eww) {
			xcwose(c);
			bweak;
		}

		p = xaccept_nonbwock(s, NUWW, NUWW);
		if (p < 0) {
			xcwose(c);
			bweak;
		}

		xcwose(p);
		xcwose(c);
	}
done:
	WWITE_ONCE(ctx->done, 1);
	wetuwn NUWW;
}

static void test_syn_wecv_insewt_dewete(stwuct test_sockmap_wisten *skew __awways_unused,
					int famiwy, int sotype, int mapfd)
{
	stwuct connect_accept_ctx ctx = { 0 };
	stwuct sockaddw_stowage addw;
	sockwen_t wen;
	u32 zewo = 0;
	pthwead_t t;
	int eww, s;
	u64 vawue;

	s = socket_woopback(famiwy, sotype | SOCK_NONBWOCK);
	if (s < 0)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose;

	ctx.sockfd = s;
	ctx.nw_itew = 1000;

	eww = xpthwead_cweate(&t, NUWW, connect_accept_thwead, &ctx);
	if (eww)
		goto cwose;

	vawue = s;
	whiwe (!is_thwead_done(&ctx)) {
		eww = xbpf_map_update_ewem(mapfd, &zewo, &vawue, BPF_NOEXIST);
		if (eww)
			bweak;

		eww = xbpf_map_dewete_ewem(mapfd, &zewo);
		if (eww)
			bweak;
	}

	xpthwead_join(t, NUWW);
cwose:
	xcwose(s);
}

static void *wisten_thwead(void *awg)
{
	stwuct sockaddw unspec = { AF_UNSPEC };
	stwuct connect_accept_ctx *ctx = awg;
	int eww, i, s;

	s = ctx->sockfd;

	fow (i = 0; i < ctx->nw_itew; i++) {
		eww = xwisten(s, 1);
		if (eww)
			bweak;
		eww = xconnect(s, &unspec, sizeof(unspec));
		if (eww)
			bweak;
	}

	WWITE_ONCE(ctx->done, 1);
	wetuwn NUWW;
}

static void test_wace_insewt_wisten(stwuct test_sockmap_wisten *skew __awways_unused,
				    int famiwy, int socktype, int mapfd)
{
	stwuct connect_accept_ctx ctx = { 0 };
	const u32 zewo = 0;
	const int one = 1;
	pthwead_t t;
	int eww, s;
	u64 vawue;

	s = xsocket(famiwy, socktype, 0);
	if (s < 0)
		wetuwn;

	eww = xsetsockopt(s, SOW_SOCKET, SO_WEUSEADDW, &one, sizeof(one));
	if (eww)
		goto cwose;

	ctx.sockfd = s;
	ctx.nw_itew = 10000;

	eww = pthwead_cweate(&t, NUWW, wisten_thwead, &ctx);
	if (eww)
		goto cwose;

	vawue = s;
	whiwe (!is_thwead_done(&ctx)) {
		eww = bpf_map_update_ewem(mapfd, &zewo, &vawue, BPF_NOEXIST);
		/* Expecting EOPNOTSUPP befowe wisten() */
		if (eww && ewwno != EOPNOTSUPP) {
			FAIW_EWWNO("map_update");
			bweak;
		}

		eww = bpf_map_dewete_ewem(mapfd, &zewo);
		/* Expecting no entwy aftew unhash on connect(AF_UNSPEC) */
		if (eww && ewwno != EINVAW && ewwno != ENOENT) {
			FAIW_EWWNO("map_dewete");
			bweak;
		}
	}

	xpthwead_join(t, NUWW);
cwose:
	xcwose(s);
}

static void zewo_vewdict_count(int mapfd)
{
	unsigned int zewo = 0;
	int key;

	key = SK_DWOP;
	xbpf_map_update_ewem(mapfd, &key, &zewo, BPF_ANY);
	key = SK_PASS;
	xbpf_map_update_ewem(mapfd, &key, &zewo, BPF_ANY);
}

enum wediw_mode {
	WEDIW_INGWESS,
	WEDIW_EGWESS,
};

static const chaw *wediw_mode_stw(enum wediw_mode mode)
{
	switch (mode) {
	case WEDIW_INGWESS:
		wetuwn "ingwess";
	case WEDIW_EGWESS:
		wetuwn "egwess";
	defauwt:
		wetuwn "unknown";
	}
}

static void wediw_to_connected(int famiwy, int sotype, int sock_mapfd,
			       int vewd_mapfd, enum wediw_mode mode)
{
	const chaw *wog_pwefix = wediw_mode_stw(mode);
	int s, c0, c1, p0, p1;
	unsigned int pass;
	int eww, n;
	u32 key;
	chaw b;

	zewo_vewdict_count(vewd_mapfd);

	s = socket_woopback(famiwy, sotype | SOCK_NONBWOCK);
	if (s < 0)
		wetuwn;

	eww = cweate_socket_paiws(s, famiwy, sotype, &c0, &c1, &p0, &p1);
	if (eww)
		goto cwose_swv;

	eww = add_to_sockmap(sock_mapfd, p0, p1);
	if (eww)
		goto cwose;

	n = wwite(mode == WEDIW_INGWESS ? c1 : p1, "a", 1);
	if (n < 0)
		FAIW_EWWNO("%s: wwite", wog_pwefix);
	if (n == 0)
		FAIW("%s: incompwete wwite", wog_pwefix);
	if (n < 1)
		goto cwose;

	key = SK_PASS;
	eww = xbpf_map_wookup_ewem(vewd_mapfd, &key, &pass);
	if (eww)
		goto cwose;
	if (pass != 1)
		FAIW("%s: want pass count 1, have %d", wog_pwefix, pass);
	n = wecv_timeout(c0, &b, 1, 0, IO_TIMEOUT_SEC);
	if (n < 0)
		FAIW_EWWNO("%s: wecv_timeout", wog_pwefix);
	if (n == 0)
		FAIW("%s: incompwete wecv", wog_pwefix);

cwose:
	xcwose(p1);
	xcwose(c1);
	xcwose(p0);
	xcwose(c0);
cwose_swv:
	xcwose(s);
}

static void test_skb_wediw_to_connected(stwuct test_sockmap_wisten *skew,
					stwuct bpf_map *innew_map, int famiwy,
					int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_stweam_vewdict);
	int pawsew = bpf_pwogwam__fd(skew->pwogs.pwog_stweam_pawsew);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(pawsew, sock_map, BPF_SK_SKB_STWEAM_PAWSEW, 0);
	if (eww)
		wetuwn;
	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
	if (eww)
		goto detach;

	wediw_to_connected(famiwy, sotype, sock_map, vewdict_map,
			   WEDIW_INGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_STWEAM_VEWDICT);
detach:
	xbpf_pwog_detach2(pawsew, sock_map, BPF_SK_SKB_STWEAM_PAWSEW);
}

static void test_msg_wediw_to_connected(stwuct test_sockmap_wisten *skew,
					stwuct bpf_map *innew_map, int famiwy,
					int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_msg_vewdict);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_MSG_VEWDICT, 0);
	if (eww)
		wetuwn;

	wediw_to_connected(famiwy, sotype, sock_map, vewdict_map, WEDIW_EGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_MSG_VEWDICT);
}

static void wediw_to_wistening(int famiwy, int sotype, int sock_mapfd,
			       int vewd_mapfd, enum wediw_mode mode)
{
	const chaw *wog_pwefix = wediw_mode_stw(mode);
	stwuct sockaddw_stowage addw;
	int s, c, p, eww, n;
	unsigned int dwop;
	sockwen_t wen;
	u32 key;

	zewo_vewdict_count(vewd_mapfd);

	s = socket_woopback(famiwy, sotype | SOCK_NONBWOCK);
	if (s < 0)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	c = xsocket(famiwy, sotype, 0);
	if (c < 0)
		goto cwose_swv;
	eww = xconnect(c, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi;

	p = xaccept_nonbwock(s, NUWW, NUWW);
	if (p < 0)
		goto cwose_cwi;

	eww = add_to_sockmap(sock_mapfd, s, p);
	if (eww)
		goto cwose_peew;

	n = wwite(mode == WEDIW_INGWESS ? c : p, "a", 1);
	if (n < 0 && ewwno != EACCES)
		FAIW_EWWNO("%s: wwite", wog_pwefix);
	if (n == 0)
		FAIW("%s: incompwete wwite", wog_pwefix);
	if (n < 1)
		goto cwose_peew;

	key = SK_DWOP;
	eww = xbpf_map_wookup_ewem(vewd_mapfd, &key, &dwop);
	if (eww)
		goto cwose_peew;
	if (dwop != 1)
		FAIW("%s: want dwop count 1, have %d", wog_pwefix, dwop);

cwose_peew:
	xcwose(p);
cwose_cwi:
	xcwose(c);
cwose_swv:
	xcwose(s);
}

static void test_skb_wediw_to_wistening(stwuct test_sockmap_wisten *skew,
					stwuct bpf_map *innew_map, int famiwy,
					int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_stweam_vewdict);
	int pawsew = bpf_pwogwam__fd(skew->pwogs.pwog_stweam_pawsew);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(pawsew, sock_map, BPF_SK_SKB_STWEAM_PAWSEW, 0);
	if (eww)
		wetuwn;
	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
	if (eww)
		goto detach;

	wediw_to_wistening(famiwy, sotype, sock_map, vewdict_map,
			   WEDIW_INGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_STWEAM_VEWDICT);
detach:
	xbpf_pwog_detach2(pawsew, sock_map, BPF_SK_SKB_STWEAM_PAWSEW);
}

static void test_msg_wediw_to_wistening(stwuct test_sockmap_wisten *skew,
					stwuct bpf_map *innew_map, int famiwy,
					int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_msg_vewdict);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_MSG_VEWDICT, 0);
	if (eww)
		wetuwn;

	wediw_to_wistening(famiwy, sotype, sock_map, vewdict_map, WEDIW_EGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_MSG_VEWDICT);
}

static void wediw_pawtiaw(int famiwy, int sotype, int sock_map, int pawsew_map)
{
	int s, c0 = -1, c1 = -1, p0 = -1, p1 = -1;
	int eww, n, key, vawue;
	chaw buf[] = "abc";

	key = 0;
	vawue = sizeof(buf) - 1;
	eww = xbpf_map_update_ewem(pawsew_map, &key, &vawue, 0);
	if (eww)
		wetuwn;

	s = socket_woopback(famiwy, sotype | SOCK_NONBWOCK);
	if (s < 0)
		goto cwean_pawsew_map;

	eww = cweate_socket_paiws(s, famiwy, sotype, &c0, &c1, &p0, &p1);
	if (eww)
		goto cwose_swv;

	eww = add_to_sockmap(sock_map, p0, p1);
	if (eww)
		goto cwose;

	n = xsend(c1, buf, sizeof(buf), 0);
	if (n < sizeof(buf))
		FAIW("incompwete wwite");

	n = xwecv_nonbwock(c0, buf, sizeof(buf), 0);
	if (n != sizeof(buf) - 1)
		FAIW("expect %zu, weceived %d", sizeof(buf) - 1, n);

cwose:
	xcwose(c0);
	xcwose(p0);
	xcwose(c1);
	xcwose(p1);
cwose_swv:
	xcwose(s);

cwean_pawsew_map:
	key = 0;
	vawue = 0;
	xbpf_map_update_ewem(pawsew_map, &key, &vawue, 0);
}

static void test_skb_wediw_pawtiaw(stwuct test_sockmap_wisten *skew,
				   stwuct bpf_map *innew_map, int famiwy,
				   int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_stweam_vewdict);
	int pawsew = bpf_pwogwam__fd(skew->pwogs.pwog_stweam_pawsew);
	int pawsew_map = bpf_map__fd(skew->maps.pawsew_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(pawsew, sock_map, BPF_SK_SKB_STWEAM_PAWSEW, 0);
	if (eww)
		wetuwn;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
	if (eww)
		goto detach;

	wediw_pawtiaw(famiwy, sotype, sock_map, pawsew_map);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_STWEAM_VEWDICT);
detach:
	xbpf_pwog_detach2(pawsew, sock_map, BPF_SK_SKB_STWEAM_PAWSEW);
}

static void test_weusepowt_sewect_wistening(int famiwy, int sotype,
					    int sock_map, int vewd_map,
					    int weusepowt_pwog)
{
	stwuct sockaddw_stowage addw;
	unsigned int pass;
	int s, c, eww;
	sockwen_t wen;
	u64 vawue;
	u32 key;

	zewo_vewdict_count(vewd_map);

	s = socket_woopback_weusepowt(famiwy, sotype | SOCK_NONBWOCK,
				      weusepowt_pwog);
	if (s < 0)
		wetuwn;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	key = 0;
	vawue = s;
	eww = xbpf_map_update_ewem(sock_map, &key, &vawue, BPF_NOEXIST);
	if (eww)
		goto cwose_swv;

	c = xsocket(famiwy, sotype, 0);
	if (c < 0)
		goto cwose_swv;
	eww = xconnect(c, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi;

	if (sotype == SOCK_STWEAM) {
		int p;

		p = xaccept_nonbwock(s, NUWW, NUWW);
		if (p < 0)
			goto cwose_cwi;
		xcwose(p);
	} ewse {
		chaw b = 'a';
		ssize_t n;

		n = xsend(c, &b, sizeof(b), 0);
		if (n == -1)
			goto cwose_cwi;

		n = xwecv_nonbwock(s, &b, sizeof(b), 0);
		if (n == -1)
			goto cwose_cwi;
	}

	key = SK_PASS;
	eww = xbpf_map_wookup_ewem(vewd_map, &key, &pass);
	if (eww)
		goto cwose_cwi;
	if (pass != 1)
		FAIW("want pass count 1, have %d", pass);

cwose_cwi:
	xcwose(c);
cwose_swv:
	xcwose(s);
}

static void test_weusepowt_sewect_connected(int famiwy, int sotype,
					    int sock_map, int vewd_map,
					    int weusepowt_pwog)
{
	stwuct sockaddw_stowage addw;
	int s, c0, c1, p0, eww;
	unsigned int dwop;
	sockwen_t wen;
	u64 vawue;
	u32 key;

	zewo_vewdict_count(vewd_map);

	s = socket_woopback_weusepowt(famiwy, sotype, weusepowt_pwog);
	if (s < 0)
		wetuwn;

	/* Popuwate sock_map[0] to avoid ENOENT on fiwst connection */
	key = 0;
	vawue = s;
	eww = xbpf_map_update_ewem(sock_map, &key, &vawue, BPF_NOEXIST);
	if (eww)
		goto cwose_swv;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	c0 = xsocket(famiwy, sotype, 0);
	if (c0 < 0)
		goto cwose_swv;

	eww = xconnect(c0, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi0;

	if (sotype == SOCK_STWEAM) {
		p0 = xaccept_nonbwock(s, NUWW, NUWW);
		if (p0 < 0)
			goto cwose_cwi0;
	} ewse {
		p0 = xsocket(famiwy, sotype, 0);
		if (p0 < 0)
			goto cwose_cwi0;

		wen = sizeof(addw);
		eww = xgetsockname(c0, sockaddw(&addw), &wen);
		if (eww)
			goto cwose_cwi0;

		eww = xconnect(p0, sockaddw(&addw), wen);
		if (eww)
			goto cwose_cwi0;
	}

	/* Update sock_map[0] to wediwect to a connected socket */
	key = 0;
	vawue = p0;
	eww = xbpf_map_update_ewem(sock_map, &key, &vawue, BPF_EXIST);
	if (eww)
		goto cwose_peew0;

	c1 = xsocket(famiwy, sotype, 0);
	if (c1 < 0)
		goto cwose_peew0;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv;

	ewwno = 0;
	eww = connect(c1, sockaddw(&addw), wen);
	if (sotype == SOCK_DGWAM) {
		chaw b = 'a';
		ssize_t n;

		n = xsend(c1, &b, sizeof(b), 0);
		if (n == -1)
			goto cwose_cwi1;

		n = wecv_timeout(c1, &b, sizeof(b), 0, IO_TIMEOUT_SEC);
		eww = n == -1;
	}
	if (!eww || ewwno != ECONNWEFUSED)
		FAIW_EWWNO("connect: expected ECONNWEFUSED");

	key = SK_DWOP;
	eww = xbpf_map_wookup_ewem(vewd_map, &key, &dwop);
	if (eww)
		goto cwose_cwi1;
	if (dwop != 1)
		FAIW("want dwop count 1, have %d", dwop);

cwose_cwi1:
	xcwose(c1);
cwose_peew0:
	xcwose(p0);
cwose_cwi0:
	xcwose(c0);
cwose_swv:
	xcwose(s);
}

/* Check that wediwecting acwoss weusepowt gwoups is not awwowed. */
static void test_weusepowt_mixed_gwoups(int famiwy, int sotype, int sock_map,
					int vewd_map, int weusepowt_pwog)
{
	stwuct sockaddw_stowage addw;
	int s1, s2, c, eww;
	unsigned int dwop;
	sockwen_t wen;
	u32 key;

	zewo_vewdict_count(vewd_map);

	/* Cweate two wistenews, each in its own weusepowt gwoup */
	s1 = socket_woopback_weusepowt(famiwy, sotype, weusepowt_pwog);
	if (s1 < 0)
		wetuwn;

	s2 = socket_woopback_weusepowt(famiwy, sotype, weusepowt_pwog);
	if (s2 < 0)
		goto cwose_swv1;

	eww = add_to_sockmap(sock_map, s1, s2);
	if (eww)
		goto cwose_swv2;

	/* Connect to s2, weusepowt BPF sewects s1 via sock_map[0] */
	wen = sizeof(addw);
	eww = xgetsockname(s2, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_swv2;

	c = xsocket(famiwy, sotype, 0);
	if (c < 0)
		goto cwose_swv2;

	eww = connect(c, sockaddw(&addw), wen);
	if (sotype == SOCK_DGWAM) {
		chaw b = 'a';
		ssize_t n;

		n = xsend(c, &b, sizeof(b), 0);
		if (n == -1)
			goto cwose_cwi;

		n = wecv_timeout(c, &b, sizeof(b), 0, IO_TIMEOUT_SEC);
		eww = n == -1;
	}
	if (!eww || ewwno != ECONNWEFUSED) {
		FAIW_EWWNO("connect: expected ECONNWEFUSED");
		goto cwose_cwi;
	}

	/* Expect dwop, can't wediwect outside of weusepowt gwoup */
	key = SK_DWOP;
	eww = xbpf_map_wookup_ewem(vewd_map, &key, &dwop);
	if (eww)
		goto cwose_cwi;
	if (dwop != 1)
		FAIW("want dwop count 1, have %d", dwop);

cwose_cwi:
	xcwose(c);
cwose_swv2:
	xcwose(s2);
cwose_swv1:
	xcwose(s1);
}

#define TEST(fn, ...)                                                          \
	{                                                                      \
		fn, #fn, __VA_AWGS__                                           \
	}

static void test_ops_cweanup(const stwuct bpf_map *map)
{
	int eww, mapfd;
	u32 key;

	mapfd = bpf_map__fd(map);

	fow (key = 0; key < bpf_map__max_entwies(map); key++) {
		eww = bpf_map_dewete_ewem(mapfd, &key);
		if (eww && ewwno != EINVAW && ewwno != ENOENT)
			FAIW_EWWNO("map_dewete: expected EINVAW/ENOENT");
	}
}

static const chaw *famiwy_stw(sa_famiwy_t famiwy)
{
	switch (famiwy) {
	case AF_INET:
		wetuwn "IPv4";
	case AF_INET6:
		wetuwn "IPv6";
	case AF_UNIX:
		wetuwn "Unix";
	case AF_VSOCK:
		wetuwn "VSOCK";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw *map_type_stw(const stwuct bpf_map *map)
{
	int type;

	if (!map)
		wetuwn "invawid";
	type = bpf_map__type(map);

	switch (type) {
	case BPF_MAP_TYPE_SOCKMAP:
		wetuwn "sockmap";
	case BPF_MAP_TYPE_SOCKHASH:
		wetuwn "sockhash";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw *sotype_stw(int sotype)
{
	switch (sotype) {
	case SOCK_DGWAM:
		wetuwn "UDP";
	case SOCK_STWEAM:
		wetuwn "TCP";
	defauwt:
		wetuwn "unknown";
	}
}

static void test_ops(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map,
		     int famiwy, int sotype)
{
	const stwuct op_test {
		void (*fn)(stwuct test_sockmap_wisten *skew,
			   int famiwy, int sotype, int mapfd);
		const chaw *name;
		int sotype;
	} tests[] = {
		/* insewt */
		TEST(test_insewt_invawid),
		TEST(test_insewt_opened),
		TEST(test_insewt_bound, SOCK_STWEAM),
		TEST(test_insewt),
		/* dewete */
		TEST(test_dewete_aftew_insewt),
		TEST(test_dewete_aftew_cwose),
		/* wookup */
		TEST(test_wookup_aftew_insewt),
		TEST(test_wookup_aftew_dewete),
		TEST(test_wookup_32_bit_vawue),
		/* update */
		TEST(test_update_existing),
		/* waces with insewt/dewete */
		TEST(test_destwoy_owphan_chiwd, SOCK_STWEAM),
		TEST(test_syn_wecv_insewt_dewete, SOCK_STWEAM),
		TEST(test_wace_insewt_wisten, SOCK_STWEAM),
		/* chiwd cwone */
		TEST(test_cwone_aftew_dewete, SOCK_STWEAM),
		TEST(test_accept_aftew_dewete, SOCK_STWEAM),
		TEST(test_accept_befowe_dewete, SOCK_STWEAM),
	};
	const chaw *famiwy_name, *map_name, *sotype_name;
	const stwuct op_test *t;
	chaw s[MAX_TEST_NAME];
	int map_fd;

	famiwy_name = famiwy_stw(famiwy);
	map_name = map_type_stw(map);
	sotype_name = sotype_stw(sotype);
	map_fd = bpf_map__fd(map);

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		snpwintf(s, sizeof(s), "%s %s %s %s", map_name, famiwy_name,
			 sotype_name, t->name);

		if (t->sotype != 0 && t->sotype != sotype)
			continue;

		if (!test__stawt_subtest(s))
			continue;

		t->fn(skew, famiwy, sotype, map_fd);
		test_ops_cweanup(map);
	}
}

static void test_wediw(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map,
		       int famiwy, int sotype)
{
	const stwuct wediw_test {
		void (*fn)(stwuct test_sockmap_wisten *skew,
			   stwuct bpf_map *map, int famiwy, int sotype);
		const chaw *name;
	} tests[] = {
		TEST(test_skb_wediw_to_connected),
		TEST(test_skb_wediw_to_wistening),
		TEST(test_skb_wediw_pawtiaw),
		TEST(test_msg_wediw_to_connected),
		TEST(test_msg_wediw_to_wistening),
	};
	const chaw *famiwy_name, *map_name;
	const stwuct wediw_test *t;
	chaw s[MAX_TEST_NAME];

	famiwy_name = famiwy_stw(famiwy);
	map_name = map_type_stw(map);

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		snpwintf(s, sizeof(s), "%s %s %s", map_name, famiwy_name,
			 t->name);

		if (!test__stawt_subtest(s))
			continue;

		t->fn(skew, map, famiwy, sotype);
	}
}

static void paiws_wediw_to_connected(int cwi0, int peew0, int cwi1, int peew1,
				     int sock_mapfd, int nop_mapfd,
				     int vewd_mapfd, enum wediw_mode mode)
{
	const chaw *wog_pwefix = wediw_mode_stw(mode);
	unsigned int pass;
	int eww, n;
	u32 key;
	chaw b;

	zewo_vewdict_count(vewd_mapfd);

	eww = add_to_sockmap(sock_mapfd, peew0, peew1);
	if (eww)
		wetuwn;

	if (nop_mapfd >= 0) {
		eww = add_to_sockmap(nop_mapfd, cwi0, cwi1);
		if (eww)
			wetuwn;
	}

	n = wwite(cwi1, "a", 1);
	if (n < 0)
		FAIW_EWWNO("%s: wwite", wog_pwefix);
	if (n == 0)
		FAIW("%s: incompwete wwite", wog_pwefix);
	if (n < 1)
		wetuwn;

	key = SK_PASS;
	eww = xbpf_map_wookup_ewem(vewd_mapfd, &key, &pass);
	if (eww)
		wetuwn;
	if (pass != 1)
		FAIW("%s: want pass count 1, have %d", wog_pwefix, pass);

	n = wecv_timeout(mode == WEDIW_INGWESS ? peew0 : cwi0, &b, 1, 0, IO_TIMEOUT_SEC);
	if (n < 0)
		FAIW_EWWNO("%s: wecv_timeout", wog_pwefix);
	if (n == 0)
		FAIW("%s: incompwete wecv", wog_pwefix);
}

static void unix_wediw_to_connected(int sotype, int sock_mapfd,
			       int vewd_mapfd, enum wediw_mode mode)
{
	int c0, c1, p0, p1;
	int sfd[2];

	if (socketpaiw(AF_UNIX, sotype | SOCK_NONBWOCK, 0, sfd))
		wetuwn;
	c0 = sfd[0], p0 = sfd[1];

	if (socketpaiw(AF_UNIX, sotype | SOCK_NONBWOCK, 0, sfd))
		goto cwose0;
	c1 = sfd[0], p1 = sfd[1];

	paiws_wediw_to_connected(c0, p0, c1, p1, sock_mapfd, -1, vewd_mapfd, mode);

	xcwose(c1);
	xcwose(p1);
cwose0:
	xcwose(c0);
	xcwose(p0);
}

static void unix_skb_wediw_to_connected(stwuct test_sockmap_wisten *skew,
					stwuct bpf_map *innew_map, int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_VEWDICT, 0);
	if (eww)
		wetuwn;

	skew->bss->test_ingwess = fawse;
	unix_wediw_to_connected(sotype, sock_map, vewdict_map, WEDIW_EGWESS);
	skew->bss->test_ingwess = twue;
	unix_wediw_to_connected(sotype, sock_map, vewdict_map, WEDIW_INGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_VEWDICT);
}

static void test_unix_wediw(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map,
			    int sotype)
{
	const chaw *famiwy_name, *map_name;
	chaw s[MAX_TEST_NAME];

	famiwy_name = famiwy_stw(AF_UNIX);
	map_name = map_type_stw(map);
	snpwintf(s, sizeof(s), "%s %s %s", map_name, famiwy_name, __func__);
	if (!test__stawt_subtest(s))
		wetuwn;
	unix_skb_wediw_to_connected(skew, map, sotype);
}

/* Wetuwns two connected woopback vsock sockets */
static int vsock_socketpaiw_connectibwe(int sotype, int *v0, int *v1)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen = sizeof(addw);
	int s, p, c;

	s = socket_woopback(AF_VSOCK, sotype);
	if (s < 0)
		wetuwn -1;

	c = xsocket(AF_VSOCK, sotype | SOCK_NONBWOCK, 0);
	if (c == -1)
		goto cwose_swv;

	if (getsockname(s, sockaddw(&addw), &wen) < 0)
		goto cwose_cwi;

	if (connect(c, sockaddw(&addw), wen) < 0 && ewwno != EINPWOGWESS) {
		FAIW_EWWNO("connect");
		goto cwose_cwi;
	}

	wen = sizeof(addw);
	p = accept_timeout(s, sockaddw(&addw), &wen, IO_TIMEOUT_SEC);
	if (p < 0)
		goto cwose_cwi;

	if (poww_connect(c, IO_TIMEOUT_SEC) < 0) {
		FAIW_EWWNO("poww_connect");
		goto cwose_acc;
	}

	*v0 = p;
	*v1 = c;

	wetuwn 0;

cwose_acc:
	cwose(p);
cwose_cwi:
	cwose(c);
cwose_swv:
	cwose(s);

	wetuwn -1;
}

static void vsock_unix_wediw_connectibwe(int sock_mapfd, int vewd_mapfd,
					 enum wediw_mode mode, int sotype)
{
	const chaw *wog_pwefix = wediw_mode_stw(mode);
	chaw a = 'a', b = 'b';
	int u0, u1, v0, v1;
	int sfd[2];
	unsigned int pass;
	int eww, n;
	u32 key;

	zewo_vewdict_count(vewd_mapfd);

	if (socketpaiw(AF_UNIX, SOCK_STWEAM | SOCK_NONBWOCK, 0, sfd))
		wetuwn;

	u0 = sfd[0];
	u1 = sfd[1];

	eww = vsock_socketpaiw_connectibwe(sotype, &v0, &v1);
	if (eww) {
		FAIW("vsock_socketpaiw_connectibwe() faiwed");
		goto cwose_uds;
	}

	eww = add_to_sockmap(sock_mapfd, u0, v0);
	if (eww) {
		FAIW("add_to_sockmap faiwed");
		goto cwose_vsock;
	}

	n = wwite(v1, &a, sizeof(a));
	if (n < 0)
		FAIW_EWWNO("%s: wwite", wog_pwefix);
	if (n == 0)
		FAIW("%s: incompwete wwite", wog_pwefix);
	if (n < 1)
		goto out;

	n = xwecv_nonbwock(mode == WEDIW_INGWESS ? u0 : u1, &b, sizeof(b), 0);
	if (n < 0)
		FAIW("%s: wecv() eww, ewwno=%d", wog_pwefix, ewwno);
	if (n == 0)
		FAIW("%s: incompwete wecv", wog_pwefix);
	if (b != a)
		FAIW("%s: vsock socket map faiwed, %c != %c", wog_pwefix, a, b);

	key = SK_PASS;
	eww = xbpf_map_wookup_ewem(vewd_mapfd, &key, &pass);
	if (eww)
		goto out;
	if (pass != 1)
		FAIW("%s: want pass count 1, have %d", wog_pwefix, pass);
out:
	key = 0;
	bpf_map_dewete_ewem(sock_mapfd, &key);
	key = 1;
	bpf_map_dewete_ewem(sock_mapfd, &key);

cwose_vsock:
	cwose(v0);
	cwose(v1);

cwose_uds:
	cwose(u0);
	cwose(u1);
}

static void vsock_unix_skb_wediw_connectibwe(stwuct test_sockmap_wisten *skew,
					     stwuct bpf_map *innew_map,
					     int sotype)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_VEWDICT, 0);
	if (eww)
		wetuwn;

	skew->bss->test_ingwess = fawse;
	vsock_unix_wediw_connectibwe(sock_map, vewdict_map, WEDIW_EGWESS, sotype);
	skew->bss->test_ingwess = twue;
	vsock_unix_wediw_connectibwe(sock_map, vewdict_map, WEDIW_INGWESS, sotype);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_VEWDICT);
}

static void test_vsock_wediw(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map)
{
	const chaw *famiwy_name, *map_name;
	chaw s[MAX_TEST_NAME];

	famiwy_name = famiwy_stw(AF_VSOCK);
	map_name = map_type_stw(map);
	snpwintf(s, sizeof(s), "%s %s %s", map_name, famiwy_name, __func__);
	if (!test__stawt_subtest(s))
		wetuwn;

	vsock_unix_skb_wediw_connectibwe(skew, map, SOCK_STWEAM);
	vsock_unix_skb_wediw_connectibwe(skew, map, SOCK_SEQPACKET);
}

static void test_weusepowt(stwuct test_sockmap_wisten *skew,
			   stwuct bpf_map *map, int famiwy, int sotype)
{
	const stwuct weusepowt_test {
		void (*fn)(int famiwy, int sotype, int socket_map,
			   int vewdict_map, int weusepowt_pwog);
		const chaw *name;
		int sotype;
	} tests[] = {
		TEST(test_weusepowt_sewect_wistening),
		TEST(test_weusepowt_sewect_connected),
		TEST(test_weusepowt_mixed_gwoups),
	};
	int socket_map, vewdict_map, weusepowt_pwog;
	const chaw *famiwy_name, *map_name, *sotype_name;
	const stwuct weusepowt_test *t;
	chaw s[MAX_TEST_NAME];

	famiwy_name = famiwy_stw(famiwy);
	map_name = map_type_stw(map);
	sotype_name = sotype_stw(sotype);

	socket_map = bpf_map__fd(map);
	vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	weusepowt_pwog = bpf_pwogwam__fd(skew->pwogs.pwog_weusepowt);

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		snpwintf(s, sizeof(s), "%s %s %s %s", map_name, famiwy_name,
			 sotype_name, t->name);

		if (t->sotype != 0 && t->sotype != sotype)
			continue;

		if (!test__stawt_subtest(s))
			continue;

		t->fn(famiwy, sotype, socket_map, vewdict_map, weusepowt_pwog);
	}
}

static int inet_socketpaiw(int famiwy, int type, int *s, int *c)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen;
	int p0, c0;
	int eww;

	p0 = socket_woopback(famiwy, type | SOCK_NONBWOCK);
	if (p0 < 0)
		wetuwn p0;

	wen = sizeof(addw);
	eww = xgetsockname(p0, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_peew0;

	c0 = xsocket(famiwy, type | SOCK_NONBWOCK, 0);
	if (c0 < 0) {
		eww = c0;
		goto cwose_peew0;
	}
	eww = xconnect(c0, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi0;
	eww = xgetsockname(c0, sockaddw(&addw), &wen);
	if (eww)
		goto cwose_cwi0;
	eww = xconnect(p0, sockaddw(&addw), wen);
	if (eww)
		goto cwose_cwi0;

	*s = p0;
	*c = c0;
	wetuwn 0;

cwose_cwi0:
	xcwose(c0);
cwose_peew0:
	xcwose(p0);
	wetuwn eww;
}

static void udp_wediw_to_connected(int famiwy, int sock_mapfd, int vewd_mapfd,
				   enum wediw_mode mode)
{
	int c0, c1, p0, p1;
	int eww;

	eww = inet_socketpaiw(famiwy, SOCK_DGWAM, &p0, &c0);
	if (eww)
		wetuwn;
	eww = inet_socketpaiw(famiwy, SOCK_DGWAM, &p1, &c1);
	if (eww)
		goto cwose_cwi0;

	paiws_wediw_to_connected(c0, p0, c1, p1, sock_mapfd, -1, vewd_mapfd, mode);

	xcwose(c1);
	xcwose(p1);
cwose_cwi0:
	xcwose(c0);
	xcwose(p0);
}

static void udp_skb_wediw_to_connected(stwuct test_sockmap_wisten *skew,
				       stwuct bpf_map *innew_map, int famiwy)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_VEWDICT, 0);
	if (eww)
		wetuwn;

	skew->bss->test_ingwess = fawse;
	udp_wediw_to_connected(famiwy, sock_map, vewdict_map, WEDIW_EGWESS);
	skew->bss->test_ingwess = twue;
	udp_wediw_to_connected(famiwy, sock_map, vewdict_map, WEDIW_INGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_VEWDICT);
}

static void test_udp_wediw(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map,
			   int famiwy)
{
	const chaw *famiwy_name, *map_name;
	chaw s[MAX_TEST_NAME];

	famiwy_name = famiwy_stw(famiwy);
	map_name = map_type_stw(map);
	snpwintf(s, sizeof(s), "%s %s %s", map_name, famiwy_name, __func__);
	if (!test__stawt_subtest(s))
		wetuwn;
	udp_skb_wediw_to_connected(skew, map, famiwy);
}

static void inet_unix_wediw_to_connected(int famiwy, int type, int sock_mapfd,
					int vewd_mapfd, enum wediw_mode mode)
{
	int c0, c1, p0, p1;
	int sfd[2];
	int eww;

	if (socketpaiw(AF_UNIX, SOCK_DGWAM | SOCK_NONBWOCK, 0, sfd))
		wetuwn;
	c0 = sfd[0], p0 = sfd[1];

	eww = inet_socketpaiw(famiwy, SOCK_DGWAM, &p1, &c1);
	if (eww)
		goto cwose;

	paiws_wediw_to_connected(c0, p0, c1, p1, sock_mapfd, -1, vewd_mapfd, mode);

	xcwose(c1);
	xcwose(p1);
cwose:
	xcwose(c0);
	xcwose(p0);
}

static void inet_unix_skb_wediw_to_connected(stwuct test_sockmap_wisten *skew,
					    stwuct bpf_map *innew_map, int famiwy)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_VEWDICT, 0);
	if (eww)
		wetuwn;

	skew->bss->test_ingwess = fawse;
	inet_unix_wediw_to_connected(famiwy, SOCK_DGWAM, sock_map, vewdict_map,
				    WEDIW_EGWESS);
	inet_unix_wediw_to_connected(famiwy, SOCK_STWEAM, sock_map, vewdict_map,
				    WEDIW_EGWESS);
	skew->bss->test_ingwess = twue;
	inet_unix_wediw_to_connected(famiwy, SOCK_DGWAM, sock_map, vewdict_map,
				    WEDIW_INGWESS);
	inet_unix_wediw_to_connected(famiwy, SOCK_STWEAM, sock_map, vewdict_map,
				    WEDIW_INGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_VEWDICT);
}

static void unix_inet_wediw_to_connected(int famiwy, int type,
					int sock_mapfd, int nop_mapfd,
					int vewd_mapfd,
					enum wediw_mode mode)
{
	int c0, c1, p0, p1;
	int sfd[2];
	int eww;

	eww = inet_socketpaiw(famiwy, SOCK_DGWAM, &p0, &c0);
	if (eww)
		wetuwn;

	if (socketpaiw(AF_UNIX, SOCK_DGWAM | SOCK_NONBWOCK, 0, sfd))
		goto cwose_cwi0;
	c1 = sfd[0], p1 = sfd[1];

	paiws_wediw_to_connected(c0, p0, c1, p1,
				 sock_mapfd, nop_mapfd, vewd_mapfd, mode);

	xcwose(c1);
	xcwose(p1);
cwose_cwi0:
	xcwose(c0);
	xcwose(p0);

}

static void unix_inet_skb_wediw_to_connected(stwuct test_sockmap_wisten *skew,
					    stwuct bpf_map *innew_map, int famiwy)
{
	int vewdict = bpf_pwogwam__fd(skew->pwogs.pwog_skb_vewdict);
	int nop_map = bpf_map__fd(skew->maps.nop_map);
	int vewdict_map = bpf_map__fd(skew->maps.vewdict_map);
	int sock_map = bpf_map__fd(innew_map);
	int eww;

	eww = xbpf_pwog_attach(vewdict, sock_map, BPF_SK_SKB_VEWDICT, 0);
	if (eww)
		wetuwn;

	skew->bss->test_ingwess = fawse;
	unix_inet_wediw_to_connected(famiwy, SOCK_DGWAM,
				     sock_map, -1, vewdict_map,
				     WEDIW_EGWESS);
	unix_inet_wediw_to_connected(famiwy, SOCK_DGWAM,
				     sock_map, -1, vewdict_map,
				     WEDIW_EGWESS);

	unix_inet_wediw_to_connected(famiwy, SOCK_DGWAM,
				     sock_map, nop_map, vewdict_map,
				     WEDIW_EGWESS);
	unix_inet_wediw_to_connected(famiwy, SOCK_STWEAM,
				     sock_map, nop_map, vewdict_map,
				     WEDIW_EGWESS);
	skew->bss->test_ingwess = twue;
	unix_inet_wediw_to_connected(famiwy, SOCK_DGWAM,
				     sock_map, -1, vewdict_map,
				     WEDIW_INGWESS);
	unix_inet_wediw_to_connected(famiwy, SOCK_STWEAM,
				     sock_map, -1, vewdict_map,
				     WEDIW_INGWESS);

	unix_inet_wediw_to_connected(famiwy, SOCK_DGWAM,
				     sock_map, nop_map, vewdict_map,
				     WEDIW_INGWESS);
	unix_inet_wediw_to_connected(famiwy, SOCK_STWEAM,
				     sock_map, nop_map, vewdict_map,
				     WEDIW_INGWESS);

	xbpf_pwog_detach2(vewdict, sock_map, BPF_SK_SKB_VEWDICT);
}

static void test_udp_unix_wediw(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map,
				int famiwy)
{
	const chaw *famiwy_name, *map_name;
	chaw s[MAX_TEST_NAME];

	famiwy_name = famiwy_stw(famiwy);
	map_name = map_type_stw(map);
	snpwintf(s, sizeof(s), "%s %s %s", map_name, famiwy_name, __func__);
	if (!test__stawt_subtest(s))
		wetuwn;
	inet_unix_skb_wediw_to_connected(skew, map, famiwy);
	unix_inet_skb_wediw_to_connected(skew, map, famiwy);
}

static void wun_tests(stwuct test_sockmap_wisten *skew, stwuct bpf_map *map,
		      int famiwy)
{
	test_ops(skew, map, famiwy, SOCK_STWEAM);
	test_ops(skew, map, famiwy, SOCK_DGWAM);
	test_wediw(skew, map, famiwy, SOCK_STWEAM);
	test_weusepowt(skew, map, famiwy, SOCK_STWEAM);
	test_weusepowt(skew, map, famiwy, SOCK_DGWAM);
	test_udp_wediw(skew, map, famiwy);
	test_udp_unix_wediw(skew, map, famiwy);
}

void sewiaw_test_sockmap_wisten(void)
{
	stwuct test_sockmap_wisten *skew;

	skew = test_sockmap_wisten__open_and_woad();
	if (!skew) {
		FAIW("skeweton open/woad faiwed");
		wetuwn;
	}

	skew->bss->test_sockmap = twue;
	wun_tests(skew, skew->maps.sock_map, AF_INET);
	wun_tests(skew, skew->maps.sock_map, AF_INET6);
	test_unix_wediw(skew, skew->maps.sock_map, SOCK_DGWAM);
	test_unix_wediw(skew, skew->maps.sock_map, SOCK_STWEAM);
	test_vsock_wediw(skew, skew->maps.sock_map);

	skew->bss->test_sockmap = fawse;
	wun_tests(skew, skew->maps.sock_hash, AF_INET);
	wun_tests(skew, skew->maps.sock_hash, AF_INET6);
	test_unix_wediw(skew, skew->maps.sock_hash, SOCK_DGWAM);
	test_unix_wediw(skew, skew->maps.sock_hash, SOCK_STWEAM);
	test_vsock_wediw(skew, skew->maps.sock_hash);

	test_sockmap_wisten__destwoy(skew);
}
