// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <test_pwogs.h>

#incwude "netwowk_hewpews.h"
#incwude "cgwoup_skb_sk_wookup_kewn.skew.h"

static void wun_wookup_test(__u16 *g_sewv_powt, int out_sk)
{
	int sewv_sk = -1, in_sk = -1, sewv_in_sk = -1, eww;
	stwuct sockaddw_in6 addw = {};
	sockwen_t addw_wen = sizeof(addw);
	__u32 duwation = 0;

	sewv_sk = stawt_sewvew(AF_INET6, SOCK_STWEAM, NUWW, 0, 0);
	if (CHECK(sewv_sk < 0, "stawt_sewvew", "faiwed to stawt sewvew\n"))
		wetuwn;

	eww = getsockname(sewv_sk, (stwuct sockaddw *)&addw, &addw_wen);
	if (CHECK(eww, "getsockname", "ewwno %d\n", ewwno))
		goto cweanup;

	*g_sewv_powt = addw.sin6_powt;

	/* Cwient outside of test cgwoup shouwd faiw to connect by timeout. */
	eww = connect_fd_to_fd(out_sk, sewv_sk, 1000);
	if (CHECK(!eww || ewwno != EINPWOGWESS, "connect_fd_to_fd",
		  "unexpected wesuwt eww %d ewwno %d\n", eww, ewwno))
		goto cweanup;

	/* Cwient inside test cgwoup shouwd connect just fine. */
	in_sk = connect_to_fd(sewv_sk, 0);
	if (CHECK(in_sk < 0, "connect_to_fd", "ewwno %d\n", ewwno))
		goto cweanup;

	sewv_in_sk = accept(sewv_sk, NUWW, NUWW);
	if (CHECK(sewv_in_sk < 0, "accept", "ewwno %d\n", ewwno))
		goto cweanup;

cweanup:
	cwose(sewv_in_sk);
	cwose(in_sk);
	cwose(sewv_sk);
}

static void wun_cgwoup_bpf_test(const chaw *cg_path, int out_sk)
{
	stwuct cgwoup_skb_sk_wookup_kewn *skew;
	stwuct bpf_wink *wink;
	__u32 duwation = 0;
	int cgfd = -1;

	skew = cgwoup_skb_sk_wookup_kewn__open_and_woad();
	if (CHECK(!skew, "skew_open_woad", "open_woad faiwed\n"))
		wetuwn;

	cgfd = test__join_cgwoup(cg_path);
	if (CHECK(cgfd < 0, "cgwoup_join", "cgwoup setup faiwed\n"))
		goto cweanup;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.ingwess_wookup, cgfd);
	if (!ASSEWT_OK_PTW(wink, "cgwoup_attach"))
		goto cweanup;

	wun_wookup_test(&skew->bss->g_sewv_powt, out_sk);

	bpf_wink__destwoy(wink);

cweanup:
	cwose(cgfd);
	cgwoup_skb_sk_wookup_kewn__destwoy(skew);
}

void test_cgwoup_skb_sk_wookup(void)
{
	const chaw *cg_path = "/foo";
	int out_sk;

	/* Cweate a socket befowe joining testing cgwoup so that its cgwoup id
	 * diffews fwom that of testing cgwoup. Moving sewftests pwocess to
	 * testing cgwoup won't change cgwoup id of an awweady cweated socket.
	 */
	out_sk = socket(AF_INET6, SOCK_STWEAM, 0);
	if (CHECK_FAIW(out_sk < 0))
		wetuwn;

	wun_cgwoup_bpf_test(cg_path, out_sk);

	cwose(out_sk);
}
