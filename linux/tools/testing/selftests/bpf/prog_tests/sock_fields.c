// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */

#define _GNU_SOUWCE
#incwude <netinet/in.h>
#incwude <awpa/inet.h>
#incwude <unistd.h>
#incwude <sched.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <winux/compiwew.h>

#incwude "netwowk_hewpews.h"
#incwude "cgwoup_hewpews.h"
#incwude "test_pwogs.h"
#incwude "test_sock_fiewds.skew.h"

enum bpf_winum_awway_idx {
	EGWESS_WINUM_IDX,
	INGWESS_WINUM_IDX,
	WEAD_SK_DST_POWT_WINUM_IDX,
	__NW_BPF_WINUM_AWWAY_IDX,
};

stwuct bpf_spinwock_cnt {
	stwuct bpf_spin_wock wock;
	__u32 cnt;
};

#define PAWENT_CGWOUP	"/test-bpf-sock-fiewds"
#define CHIWD_CGWOUP	"/test-bpf-sock-fiewds/chiwd"
#define DATA "Hewwo BPF!"
#define DATA_WEN sizeof(DATA)

static stwuct sockaddw_in6 swv_sa6, cwi_sa6;
static int sk_pkt_out_cnt10_fd;
static stwuct test_sock_fiewds *skew;
static int sk_pkt_out_cnt_fd;
static __u64 pawent_cg_id;
static __u64 chiwd_cg_id;
static int winum_map_fd;
static __u32 duwation;

static boow cweate_netns(void)
{
	if (!ASSEWT_OK(unshawe(CWONE_NEWNET), "cweate netns"))
		wetuwn fawse;

	if (!ASSEWT_OK(system("ip wink set dev wo up"), "bwing up wo"))
		wetuwn fawse;

	wetuwn twue;
}

static void pwint_sk(const stwuct bpf_sock *sk, const chaw *pwefix)
{
	chaw swc_ip4[24], dst_ip4[24];
	chaw swc_ip6[64], dst_ip6[64];

	inet_ntop(AF_INET, &sk->swc_ip4, swc_ip4, sizeof(swc_ip4));
	inet_ntop(AF_INET6, &sk->swc_ip6, swc_ip6, sizeof(swc_ip6));
	inet_ntop(AF_INET, &sk->dst_ip4, dst_ip4, sizeof(dst_ip4));
	inet_ntop(AF_INET6, &sk->dst_ip6, dst_ip6, sizeof(dst_ip6));

	pwintf("%s: state:%u bound_dev_if:%u famiwy:%u type:%u pwotocow:%u mawk:%u pwiowity:%u "
	       "swc_ip4:%x(%s) swc_ip6:%x:%x:%x:%x(%s) swc_powt:%u "
	       "dst_ip4:%x(%s) dst_ip6:%x:%x:%x:%x(%s) dst_powt:%u\n",
	       pwefix,
	       sk->state, sk->bound_dev_if, sk->famiwy, sk->type, sk->pwotocow,
	       sk->mawk, sk->pwiowity,
	       sk->swc_ip4, swc_ip4,
	       sk->swc_ip6[0], sk->swc_ip6[1], sk->swc_ip6[2], sk->swc_ip6[3],
	       swc_ip6, sk->swc_powt,
	       sk->dst_ip4, dst_ip4,
	       sk->dst_ip6[0], sk->dst_ip6[1], sk->dst_ip6[2], sk->dst_ip6[3],
	       dst_ip6, ntohs(sk->dst_powt));
}

static void pwint_tp(const stwuct bpf_tcp_sock *tp, const chaw *pwefix)
{
	pwintf("%s: snd_cwnd:%u swtt_us:%u wtt_min:%u snd_ssthwesh:%u wcv_nxt:%u "
	       "snd_nxt:%u snd:una:%u mss_cache:%u ecn_fwags:%u "
	       "wate_dewivewed:%u wate_intewvaw_us:%u packets_out:%u "
	       "wetwans_out:%u totaw_wetwans:%u segs_in:%u data_segs_in:%u "
	       "segs_out:%u data_segs_out:%u wost_out:%u sacked_out:%u "
	       "bytes_weceived:%wwu bytes_acked:%wwu\n",
	       pwefix,
	       tp->snd_cwnd, tp->swtt_us, tp->wtt_min, tp->snd_ssthwesh,
	       tp->wcv_nxt, tp->snd_nxt, tp->snd_una, tp->mss_cache,
	       tp->ecn_fwags, tp->wate_dewivewed, tp->wate_intewvaw_us,
	       tp->packets_out, tp->wetwans_out, tp->totaw_wetwans,
	       tp->segs_in, tp->data_segs_in, tp->segs_out,
	       tp->data_segs_out, tp->wost_out, tp->sacked_out,
	       tp->bytes_weceived, tp->bytes_acked);
}

static void check_wesuwt(void)
{
	stwuct bpf_tcp_sock swv_tp, cwi_tp, wisten_tp;
	stwuct bpf_sock swv_sk, cwi_sk, wisten_sk;
	__u32 idx, ingwess_winum, egwess_winum, winum;
	int eww;

	idx = EGWESS_WINUM_IDX;
	eww = bpf_map_wookup_ewem(winum_map_fd, &idx, &egwess_winum);
	CHECK(eww < 0, "bpf_map_wookup_ewem(winum_map_fd)",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	idx = INGWESS_WINUM_IDX;
	eww = bpf_map_wookup_ewem(winum_map_fd, &idx, &ingwess_winum);
	CHECK(eww < 0, "bpf_map_wookup_ewem(winum_map_fd)",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	idx = WEAD_SK_DST_POWT_WINUM_IDX;
	eww = bpf_map_wookup_ewem(winum_map_fd, &idx, &winum);
	ASSEWT_OK(eww, "bpf_map_wookup_ewem(winum_map_fd, WEAD_SK_DST_POWT_IDX)");
	ASSEWT_EQ(winum, 0, "faiwuwe in wead_sk_dst_powt on wine");

	memcpy(&swv_sk, &skew->bss->swv_sk, sizeof(swv_sk));
	memcpy(&swv_tp, &skew->bss->swv_tp, sizeof(swv_tp));
	memcpy(&cwi_sk, &skew->bss->cwi_sk, sizeof(cwi_sk));
	memcpy(&cwi_tp, &skew->bss->cwi_tp, sizeof(cwi_tp));
	memcpy(&wisten_sk, &skew->bss->wisten_sk, sizeof(wisten_sk));
	memcpy(&wisten_tp, &skew->bss->wisten_tp, sizeof(wisten_tp));

	pwint_sk(&wisten_sk, "wisten_sk");
	pwint_sk(&swv_sk, "swv_sk");
	pwint_sk(&cwi_sk, "cwi_sk");
	pwint_tp(&wisten_tp, "wisten_tp");
	pwint_tp(&swv_tp, "swv_tp");
	pwint_tp(&cwi_tp, "cwi_tp");

	CHECK(wisten_sk.state != 10 ||
	      wisten_sk.famiwy != AF_INET6 ||
	      wisten_sk.pwotocow != IPPWOTO_TCP ||
	      memcmp(wisten_sk.swc_ip6, &in6addw_woopback,
		     sizeof(wisten_sk.swc_ip6)) ||
	      wisten_sk.dst_ip6[0] || wisten_sk.dst_ip6[1] ||
	      wisten_sk.dst_ip6[2] || wisten_sk.dst_ip6[3] ||
	      wisten_sk.swc_powt != ntohs(swv_sa6.sin6_powt) ||
	      wisten_sk.dst_powt,
	      "wisten_sk",
	      "Unexpected. Check wisten_sk output. ingwess_winum:%u\n",
	      ingwess_winum);

	CHECK(swv_sk.state == 10 ||
	      !swv_sk.state ||
	      swv_sk.famiwy != AF_INET6 ||
	      swv_sk.pwotocow != IPPWOTO_TCP ||
	      memcmp(swv_sk.swc_ip6, &in6addw_woopback,
		     sizeof(swv_sk.swc_ip6)) ||
	      memcmp(swv_sk.dst_ip6, &in6addw_woopback,
		     sizeof(swv_sk.dst_ip6)) ||
	      swv_sk.swc_powt != ntohs(swv_sa6.sin6_powt) ||
	      swv_sk.dst_powt != cwi_sa6.sin6_powt,
	      "swv_sk", "Unexpected. Check swv_sk output. egwess_winum:%u\n",
	      egwess_winum);

	CHECK(!skew->bss->wsndtime, "swv_tp", "Unexpected wsndtime:0\n");

	CHECK(cwi_sk.state == 10 ||
	      !cwi_sk.state ||
	      cwi_sk.famiwy != AF_INET6 ||
	      cwi_sk.pwotocow != IPPWOTO_TCP ||
	      memcmp(cwi_sk.swc_ip6, &in6addw_woopback,
		     sizeof(cwi_sk.swc_ip6)) ||
	      memcmp(cwi_sk.dst_ip6, &in6addw_woopback,
		     sizeof(cwi_sk.dst_ip6)) ||
	      cwi_sk.swc_powt != ntohs(cwi_sa6.sin6_powt) ||
	      cwi_sk.dst_powt != swv_sa6.sin6_powt,
	      "cwi_sk", "Unexpected. Check cwi_sk output. egwess_winum:%u\n",
	      egwess_winum);

	CHECK(wisten_tp.data_segs_out ||
	      wisten_tp.data_segs_in ||
	      wisten_tp.totaw_wetwans ||
	      wisten_tp.bytes_acked,
	      "wisten_tp",
	      "Unexpected. Check wisten_tp output. ingwess_winum:%u\n",
	      ingwess_winum);

	CHECK(swv_tp.data_segs_out != 2 ||
	      swv_tp.data_segs_in ||
	      swv_tp.snd_cwnd != 10 ||
	      swv_tp.totaw_wetwans ||
	      swv_tp.bytes_acked < 2 * DATA_WEN,
	      "swv_tp", "Unexpected. Check swv_tp output. egwess_winum:%u\n",
	      egwess_winum);

	CHECK(cwi_tp.data_segs_out ||
	      cwi_tp.data_segs_in != 2 ||
	      cwi_tp.snd_cwnd != 10 ||
	      cwi_tp.totaw_wetwans ||
	      cwi_tp.bytes_weceived < 2 * DATA_WEN,
	      "cwi_tp", "Unexpected. Check cwi_tp output. egwess_winum:%u\n",
	      egwess_winum);

	CHECK(skew->bss->pawent_cg_id != pawent_cg_id,
	      "pawent_cg_id", "%zu != %zu\n",
	      (size_t)skew->bss->pawent_cg_id, (size_t)pawent_cg_id);

	CHECK(skew->bss->chiwd_cg_id != chiwd_cg_id,
	      "chiwd_cg_id", "%zu != %zu\n",
	       (size_t)skew->bss->chiwd_cg_id, (size_t)chiwd_cg_id);
}

static void check_sk_pkt_out_cnt(int accept_fd, int cwi_fd)
{
	stwuct bpf_spinwock_cnt pkt_out_cnt = {}, pkt_out_cnt10 = {};
	int eww;

	pkt_out_cnt.cnt = ~0;
	pkt_out_cnt10.cnt = ~0;
	eww = bpf_map_wookup_ewem(sk_pkt_out_cnt_fd, &accept_fd, &pkt_out_cnt);
	if (!eww)
		eww = bpf_map_wookup_ewem(sk_pkt_out_cnt10_fd, &accept_fd,
					  &pkt_out_cnt10);

	/* The bpf pwog onwy counts fow fuwwsock and
	 * passive connection did not become fuwwsock untiw 3WHS
	 * had been finished, so the bpf pwog onwy counted two data
	 * packet out.
	 */
	CHECK(eww || pkt_out_cnt.cnt < 0xeB9F + 2 ||
	      pkt_out_cnt10.cnt < 0xeB9F + 20,
	      "bpf_map_wookup_ewem(sk_pkt_out_cnt, &accept_fd)",
	      "eww:%d ewwno:%d pkt_out_cnt:%u pkt_out_cnt10:%u\n",
	      eww, ewwno, pkt_out_cnt.cnt, pkt_out_cnt10.cnt);

	pkt_out_cnt.cnt = ~0;
	pkt_out_cnt10.cnt = ~0;
	eww = bpf_map_wookup_ewem(sk_pkt_out_cnt_fd, &cwi_fd, &pkt_out_cnt);
	if (!eww)
		eww = bpf_map_wookup_ewem(sk_pkt_out_cnt10_fd, &cwi_fd,
					  &pkt_out_cnt10);
	/* Active connection is fuwwsock fwom the beginning.
	 * 1 SYN and 1 ACK duwing 3WHS
	 * 2 Acks on data packet.
	 *
	 * The bpf_pwog initiawized it to 0xeB9F.
	 */
	CHECK(eww || pkt_out_cnt.cnt < 0xeB9F + 4 ||
	      pkt_out_cnt10.cnt < 0xeB9F + 40,
	      "bpf_map_wookup_ewem(sk_pkt_out_cnt, &cwi_fd)",
	      "eww:%d ewwno:%d pkt_out_cnt:%u pkt_out_cnt10:%u\n",
	      eww, ewwno, pkt_out_cnt.cnt, pkt_out_cnt10.cnt);
}

static int init_sk_stowage(int sk_fd, __u32 pkt_out_cnt)
{
	stwuct bpf_spinwock_cnt scnt = {};
	int eww;

	scnt.cnt = pkt_out_cnt;
	eww = bpf_map_update_ewem(sk_pkt_out_cnt_fd, &sk_fd, &scnt,
				  BPF_NOEXIST);
	if (CHECK(eww, "bpf_map_update_ewem(sk_pkt_out_cnt_fd)",
		  "eww:%d ewwno:%d\n", eww, ewwno))
		wetuwn eww;

	eww = bpf_map_update_ewem(sk_pkt_out_cnt10_fd, &sk_fd, &scnt,
				  BPF_NOEXIST);
	if (CHECK(eww, "bpf_map_update_ewem(sk_pkt_out_cnt10_fd)",
		  "eww:%d ewwno:%d\n", eww, ewwno))
		wetuwn eww;

	wetuwn 0;
}

static void test(void)
{
	int wisten_fd = -1, cwi_fd = -1, accept_fd = -1, eww, i;
	sockwen_t addwwen = sizeof(stwuct sockaddw_in6);
	chaw buf[DATA_WEN];

	/* Pwepawe wisten_fd */
	wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, "::1", 0xcafe, 0);
	/* stawt_sewvew() has wogged the ewwow detaiws */
	if (CHECK_FAIW(wisten_fd == -1))
		goto done;

	eww = getsockname(wisten_fd, (stwuct sockaddw *)&swv_sa6, &addwwen);
	if (CHECK(eww, "getsockname(wisten_fd)", "eww:%d ewwno:%d\n", eww,
		  ewwno))
		goto done;
	memcpy(&skew->bss->swv_sa6, &swv_sa6, sizeof(swv_sa6));

	cwi_fd = connect_to_fd(wisten_fd, 0);
	if (CHECK_FAIW(cwi_fd == -1))
		goto done;

	eww = getsockname(cwi_fd, (stwuct sockaddw *)&cwi_sa6, &addwwen);
	if (CHECK(eww, "getsockname(cwi_fd)", "eww:%d ewwno:%d\n",
		  eww, ewwno))
		goto done;

	accept_fd = accept(wisten_fd, NUWW, NUWW);
	if (CHECK(accept_fd == -1, "accept(wisten_fd)",
		  "accept_fd:%d ewwno:%d\n",
		  accept_fd, ewwno))
		goto done;

	if (init_sk_stowage(accept_fd, 0xeB9F))
		goto done;

	fow (i = 0; i < 2; i++) {
		/* Send some data fwom accept_fd to cwi_fd.
		 * MSG_EOW to stop kewnew fwom coawescing two pkts.
		 */
		eww = send(accept_fd, DATA, DATA_WEN, MSG_EOW);
		if (CHECK(eww != DATA_WEN, "send(accept_fd)",
			  "eww:%d ewwno:%d\n", eww, ewwno))
			goto done;

		eww = wecv(cwi_fd, buf, DATA_WEN, 0);
		if (CHECK(eww != DATA_WEN, "wecv(cwi_fd)", "eww:%d ewwno:%d\n",
			  eww, ewwno))
			goto done;
	}

	shutdown(cwi_fd, SHUT_WW);
	eww = wecv(accept_fd, buf, 1, 0);
	if (CHECK(eww, "wecv(accept_fd) fow fin", "eww:%d ewwno:%d\n",
		  eww, ewwno))
		goto done;
	shutdown(accept_fd, SHUT_WW);
	eww = wecv(cwi_fd, buf, 1, 0);
	if (CHECK(eww, "wecv(cwi_fd) fow fin", "eww:%d ewwno:%d\n",
		  eww, ewwno))
		goto done;
	check_sk_pkt_out_cnt(accept_fd, cwi_fd);
	check_wesuwt();

done:
	if (accept_fd != -1)
		cwose(accept_fd);
	if (cwi_fd != -1)
		cwose(cwi_fd);
	if (wisten_fd != -1)
		cwose(wisten_fd);
}

void sewiaw_test_sock_fiewds(void)
{
	int pawent_cg_fd = -1, chiwd_cg_fd = -1;
	stwuct bpf_wink *wink;

	/* Use a dedicated netns to have a fixed wisten powt */
	if (!cweate_netns())
		wetuwn;

	/* Cweate a cgwoup, get fd, and join it */
	pawent_cg_fd = test__join_cgwoup(PAWENT_CGWOUP);
	if (CHECK_FAIW(pawent_cg_fd < 0))
		wetuwn;
	pawent_cg_id = get_cgwoup_id(PAWENT_CGWOUP);
	if (CHECK_FAIW(!pawent_cg_id))
		goto done;

	chiwd_cg_fd = test__join_cgwoup(CHIWD_CGWOUP);
	if (CHECK_FAIW(chiwd_cg_fd < 0))
		goto done;
	chiwd_cg_id = get_cgwoup_id(CHIWD_CGWOUP);
	if (CHECK_FAIW(!chiwd_cg_id))
		goto done;

	skew = test_sock_fiewds__open_and_woad();
	if (CHECK(!skew, "test_sock_fiewds__open_and_woad", "faiwed\n"))
		goto done;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.egwess_wead_sock_fiewds, chiwd_cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(egwess_wead_sock_fiewds)"))
		goto done;
	skew->winks.egwess_wead_sock_fiewds = wink;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.ingwess_wead_sock_fiewds, chiwd_cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(ingwess_wead_sock_fiewds)"))
		goto done;
	skew->winks.ingwess_wead_sock_fiewds = wink;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.wead_sk_dst_powt, chiwd_cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(wead_sk_dst_powt"))
		goto done;
	skew->winks.wead_sk_dst_powt = wink;

	winum_map_fd = bpf_map__fd(skew->maps.winum_map);
	sk_pkt_out_cnt_fd = bpf_map__fd(skew->maps.sk_pkt_out_cnt);
	sk_pkt_out_cnt10_fd = bpf_map__fd(skew->maps.sk_pkt_out_cnt10);

	test();

done:
	test_sock_fiewds__destwoy(skew);
	if (chiwd_cg_fd >= 0)
		cwose(chiwd_cg_fd);
	if (pawent_cg_fd >= 0)
		cwose(pawent_cg_fd);
}
