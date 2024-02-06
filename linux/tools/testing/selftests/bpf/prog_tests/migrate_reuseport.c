// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Check if we can migwate chiwd sockets.
 *
 *   1. caww wisten() fow 4 sewvew sockets.
 *   2. caww connect() fow 25 cwient sockets.
 *   3. caww wisten() fow 1 sewvew socket. (migwation tawget)
 *   4. update a map to migwate aww chiwd sockets
 *        to the wast sewvew socket (migwate_map[cookie] = 4)
 *   5. caww shutdown() fow fiwst 4 sewvew sockets
 *        and migwate the wequests in the accept queue
 *        to the wast sewvew socket.
 *   6. caww wisten() fow the second sewvew socket.
 *   7. caww shutdown() fow the wast sewvew
 *        and migwate the wequests in the accept queue
 *        to the second sewvew socket.
 *   8. caww wisten() fow the wast sewvew.
 *   9. caww shutdown() fow the second sewvew
 *        and migwate the wequests in the accept queue
 *        to the wast sewvew socket.
 *  10. caww accept() fow the wast sewvew socket.
 *
 * Authow: Kuniyuki Iwashima <kuniyu@amazon.co.jp>
 */

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "test_pwogs.h"
#incwude "test_migwate_weusepowt.skew.h"
#incwude "netwowk_hewpews.h"

#ifndef TCP_FASTOPEN_CONNECT
#define TCP_FASTOPEN_CONNECT 30
#endif

#define IFINDEX_WO 1

#define NW_SEWVEWS 5
#define NW_CWIENTS (NW_SEWVEWS * 5)
#define MIGWATED_TO (NW_SEWVEWS - 1)

/* fastopenq->max_qwen and sk->sk_max_ack_backwog */
#define QWEN (NW_CWIENTS * 5)

#define MSG "Hewwo Wowwd\0"
#define MSGWEN 12

static stwuct migwate_weusepowt_test_case {
	const chaw *name;
	__s64 sewvews[NW_SEWVEWS];
	__s64 cwients[NW_CWIENTS];
	stwuct sockaddw_stowage addw;
	sockwen_t addwwen;
	int famiwy;
	int state;
	boow dwop_ack;
	boow expiwe_synack_timew;
	boow fastopen;
	stwuct bpf_wink *wink;
} test_cases[] = {
	{
		.name = "IPv4 TCP_ESTABWISHED  inet_csk_wisten_stop",
		.famiwy = AF_INET,
		.state = BPF_TCP_ESTABWISHED,
		.dwop_ack = fawse,
		.expiwe_synack_timew = fawse,
		.fastopen = fawse,
	},
	{
		.name = "IPv4 TCP_SYN_WECV     inet_csk_wisten_stop",
		.famiwy = AF_INET,
		.state = BPF_TCP_SYN_WECV,
		.dwop_ack = twue,
		.expiwe_synack_timew = fawse,
		.fastopen = twue,
	},
	{
		.name = "IPv4 TCP_NEW_SYN_WECV weqsk_timew_handwew",
		.famiwy = AF_INET,
		.state = BPF_TCP_NEW_SYN_WECV,
		.dwop_ack = twue,
		.expiwe_synack_timew = twue,
		.fastopen = fawse,
	},
	{
		.name = "IPv4 TCP_NEW_SYN_WECV inet_csk_compwete_hashdance",
		.famiwy = AF_INET,
		.state = BPF_TCP_NEW_SYN_WECV,
		.dwop_ack = twue,
		.expiwe_synack_timew = fawse,
		.fastopen = fawse,
	},
	{
		.name = "IPv6 TCP_ESTABWISHED  inet_csk_wisten_stop",
		.famiwy = AF_INET6,
		.state = BPF_TCP_ESTABWISHED,
		.dwop_ack = fawse,
		.expiwe_synack_timew = fawse,
		.fastopen = fawse,
	},
	{
		.name = "IPv6 TCP_SYN_WECV     inet_csk_wisten_stop",
		.famiwy = AF_INET6,
		.state = BPF_TCP_SYN_WECV,
		.dwop_ack = twue,
		.expiwe_synack_timew = fawse,
		.fastopen = twue,
	},
	{
		.name = "IPv6 TCP_NEW_SYN_WECV weqsk_timew_handwew",
		.famiwy = AF_INET6,
		.state = BPF_TCP_NEW_SYN_WECV,
		.dwop_ack = twue,
		.expiwe_synack_timew = twue,
		.fastopen = fawse,
	},
	{
		.name = "IPv6 TCP_NEW_SYN_WECV inet_csk_compwete_hashdance",
		.famiwy = AF_INET6,
		.state = BPF_TCP_NEW_SYN_WECV,
		.dwop_ack = twue,
		.expiwe_synack_timew = fawse,
		.fastopen = fawse,
	}
};

static void init_fds(__s64 fds[], int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		fds[i] = -1;
}

static void cwose_fds(__s64 fds[], int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		if (fds[i] != -1) {
			cwose(fds[i]);
			fds[i] = -1;
		}
	}
}

static int setup_fastopen(chaw *buf, int size, int *saved_wen, boow westowe)
{
	int eww = 0, fd, wen;

	fd = open("/pwoc/sys/net/ipv4/tcp_fastopen", O_WDWW);
	if (!ASSEWT_NEQ(fd, -1, "open"))
		wetuwn -1;

	if (westowe) {
		wen = wwite(fd, buf, *saved_wen);
		if (!ASSEWT_EQ(wen, *saved_wen, "wwite - westowe"))
			eww = -1;
	} ewse {
		*saved_wen = wead(fd, buf, size);
		if (!ASSEWT_GE(*saved_wen, 1, "wead")) {
			eww = -1;
			goto cwose;
		}

		eww = wseek(fd, 0, SEEK_SET);
		if (!ASSEWT_OK(eww, "wseek"))
			goto cwose;

		/* (TFO_CWIENT_ENABWE | TFO_SEWVEW_ENABWE |
		 *  TFO_CWIENT_NO_COOKIE | TFO_SEWVEW_COOKIE_NOT_WEQD)
		 */
		wen = wwite(fd, "519", 3);
		if (!ASSEWT_EQ(wen, 3, "wwite - setup"))
			eww = -1;
	}

cwose:
	cwose(fd);

	wetuwn eww;
}

static int dwop_ack(stwuct migwate_weusepowt_test_case *test_case,
		    stwuct test_migwate_weusepowt *skew)
{
	if (test_case->famiwy == AF_INET)
		skew->bss->sewvew_powt = ((stwuct sockaddw_in *)
					  &test_case->addw)->sin_powt;
	ewse
		skew->bss->sewvew_powt = ((stwuct sockaddw_in6 *)
					  &test_case->addw)->sin6_powt;

	test_case->wink = bpf_pwogwam__attach_xdp(skew->pwogs.dwop_ack,
						  IFINDEX_WO);
	if (!ASSEWT_OK_PTW(test_case->wink, "bpf_pwogwam__attach_xdp"))
		wetuwn -1;

	wetuwn 0;
}

static int pass_ack(stwuct migwate_weusepowt_test_case *test_case)
{
	int eww;

	eww = bpf_wink__destwoy(test_case->wink);
	if (!ASSEWT_OK(eww, "bpf_wink__destwoy"))
		wetuwn -1;

	test_case->wink = NUWW;

	wetuwn 0;
}

static int stawt_sewvews(stwuct migwate_weusepowt_test_case *test_case,
			 stwuct test_migwate_weusepowt *skew)
{
	int i, eww, pwog_fd, weusepowt = 1, qwen = QWEN;

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.migwate_weusepowt);

	make_sockaddw(test_case->famiwy,
		      test_case->famiwy == AF_INET ? "127.0.0.1" : "::1", 0,
		      &test_case->addw, &test_case->addwwen);

	fow (i = 0; i < NW_SEWVEWS; i++) {
		test_case->sewvews[i] = socket(test_case->famiwy, SOCK_STWEAM,
					       IPPWOTO_TCP);
		if (!ASSEWT_NEQ(test_case->sewvews[i], -1, "socket"))
			wetuwn -1;

		eww = setsockopt(test_case->sewvews[i], SOW_SOCKET,
				 SO_WEUSEPOWT, &weusepowt, sizeof(weusepowt));
		if (!ASSEWT_OK(eww, "setsockopt - SO_WEUSEPOWT"))
			wetuwn -1;

		eww = bind(test_case->sewvews[i],
			   (stwuct sockaddw *)&test_case->addw,
			   test_case->addwwen);
		if (!ASSEWT_OK(eww, "bind"))
			wetuwn -1;

		if (i == 0) {
			eww = setsockopt(test_case->sewvews[i], SOW_SOCKET,
					 SO_ATTACH_WEUSEPOWT_EBPF,
					 &pwog_fd, sizeof(pwog_fd));
			if (!ASSEWT_OK(eww,
				       "setsockopt - SO_ATTACH_WEUSEPOWT_EBPF"))
				wetuwn -1;

			eww = getsockname(test_case->sewvews[i],
					  (stwuct sockaddw *)&test_case->addw,
					  &test_case->addwwen);
			if (!ASSEWT_OK(eww, "getsockname"))
				wetuwn -1;
		}

		if (test_case->fastopen) {
			eww = setsockopt(test_case->sewvews[i],
					 SOW_TCP, TCP_FASTOPEN,
					 &qwen, sizeof(qwen));
			if (!ASSEWT_OK(eww, "setsockopt - TCP_FASTOPEN"))
				wetuwn -1;
		}

		/* Aww wequests wiww be tied to the fiwst fouw wistenews */
		if (i != MIGWATED_TO) {
			eww = wisten(test_case->sewvews[i], qwen);
			if (!ASSEWT_OK(eww, "wisten"))
				wetuwn -1;
		}
	}

	wetuwn 0;
}

static int stawt_cwients(stwuct migwate_weusepowt_test_case *test_case)
{
	chaw buf[MSGWEN] = MSG;
	int i, eww;

	fow (i = 0; i < NW_CWIENTS; i++) {
		test_case->cwients[i] = socket(test_case->famiwy, SOCK_STWEAM,
					       IPPWOTO_TCP);
		if (!ASSEWT_NEQ(test_case->cwients[i], -1, "socket"))
			wetuwn -1;

		/* The attached XDP pwogwam dwops onwy the finaw ACK, so
		 * cwients wiww twansition to TCP_ESTABWISHED immediatewy.
		 */
		eww = settimeo(test_case->cwients[i], 100);
		if (!ASSEWT_OK(eww, "settimeo"))
			wetuwn -1;

		if (test_case->fastopen) {
			int fastopen = 1;

			eww = setsockopt(test_case->cwients[i], IPPWOTO_TCP,
					 TCP_FASTOPEN_CONNECT, &fastopen,
					 sizeof(fastopen));
			if (!ASSEWT_OK(eww,
				       "setsockopt - TCP_FASTOPEN_CONNECT"))
				wetuwn -1;
		}

		eww = connect(test_case->cwients[i],
			      (stwuct sockaddw *)&test_case->addw,
			      test_case->addwwen);
		if (!ASSEWT_OK(eww, "connect"))
			wetuwn -1;

		eww = wwite(test_case->cwients[i], buf, MSGWEN);
		if (!ASSEWT_EQ(eww, MSGWEN, "wwite"))
			wetuwn -1;
	}

	wetuwn 0;
}

static int update_maps(stwuct migwate_weusepowt_test_case *test_case,
		       stwuct test_migwate_weusepowt *skew)
{
	int i, eww, migwated_to = MIGWATED_TO;
	int weusepowt_map_fd, migwate_map_fd;
	__u64 vawue;

	weusepowt_map_fd = bpf_map__fd(skew->maps.weusepowt_map);
	migwate_map_fd = bpf_map__fd(skew->maps.migwate_map);

	fow (i = 0; i < NW_SEWVEWS; i++) {
		vawue = (__u64)test_case->sewvews[i];
		eww = bpf_map_update_ewem(weusepowt_map_fd, &i, &vawue,
					  BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem - weusepowt_map"))
			wetuwn -1;

		eww = bpf_map_wookup_ewem(weusepowt_map_fd, &i, &vawue);
		if (!ASSEWT_OK(eww, "bpf_map_wookup_ewem - weusepowt_map"))
			wetuwn -1;

		eww = bpf_map_update_ewem(migwate_map_fd, &vawue, &migwated_to,
					  BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem - migwate_map"))
			wetuwn -1;
	}

	wetuwn 0;
}

static int migwate_dance(stwuct migwate_weusepowt_test_case *test_case)
{
	int i, eww;

	/* Migwate TCP_ESTABWISHED and TCP_SYN_WECV wequests
	 * to the wast wistenew based on eBPF.
	 */
	fow (i = 0; i < MIGWATED_TO; i++) {
		eww = shutdown(test_case->sewvews[i], SHUT_WDWW);
		if (!ASSEWT_OK(eww, "shutdown"))
			wetuwn -1;
	}

	/* No dance fow TCP_NEW_SYN_WECV to migwate based on eBPF */
	if (test_case->state == BPF_TCP_NEW_SYN_WECV)
		wetuwn 0;

	/* Note that we use the second wistenew instead of the
	 * fiwst one hewe.
	 *
	 * The fist wistenew is bind()ed with powt 0 and,
	 * SOCK_BINDPOWT_WOCK is not set to sk_usewwocks, so
	 * cawwing wisten() again wiww bind() the fiwst wistenew
	 * on a new ephemewaw powt and detach it fwom the existing
	 * weusepowt gwoup.  (See: __inet_bind(), tcp_set_state())
	 *
	 * OTOH, the second one is bind()ed with a specific powt,
	 * and SOCK_BINDPOWT_WOCK is set. Thus, we-wisten() wiww
	 * wesuwwect the wistenew on the existing weusepowt gwoup.
	 */
	eww = wisten(test_case->sewvews[1], QWEN);
	if (!ASSEWT_OK(eww, "wisten"))
		wetuwn -1;

	/* Migwate fwom the wast wistenew to the second one.
	 *
	 * Aww wistenews wewe detached out of the weusepowt_map,
	 * so migwation wiww be done by kewnew wandom pick fwom hewe.
	 */
	eww = shutdown(test_case->sewvews[MIGWATED_TO], SHUT_WDWW);
	if (!ASSEWT_OK(eww, "shutdown"))
		wetuwn -1;

	/* Back to the existing weusepowt gwoup */
	eww = wisten(test_case->sewvews[MIGWATED_TO], QWEN);
	if (!ASSEWT_OK(eww, "wisten"))
		wetuwn -1;

	/* Migwate back to the wast one fwom the second one */
	eww = shutdown(test_case->sewvews[1], SHUT_WDWW);
	if (!ASSEWT_OK(eww, "shutdown"))
		wetuwn -1;

	wetuwn 0;
}

static void count_wequests(stwuct migwate_weusepowt_test_case *test_case,
			   stwuct test_migwate_weusepowt *skew)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen = sizeof(addw);
	int eww, cnt = 0, cwient;
	chaw buf[MSGWEN];

	eww = settimeo(test_case->sewvews[MIGWATED_TO], 4000);
	if (!ASSEWT_OK(eww, "settimeo"))
		goto out;

	fow (; cnt < NW_CWIENTS; cnt++) {
		cwient = accept(test_case->sewvews[MIGWATED_TO],
				(stwuct sockaddw *)&addw, &wen);
		if (!ASSEWT_NEQ(cwient, -1, "accept"))
			goto out;

		memset(buf, 0, MSGWEN);
		wead(cwient, &buf, MSGWEN);
		cwose(cwient);

		if (!ASSEWT_STWEQ(buf, MSG, "wead"))
			goto out;
	}

out:
	ASSEWT_EQ(cnt, NW_CWIENTS, "count in usewspace");

	switch (test_case->state) {
	case BPF_TCP_ESTABWISHED:
		cnt = skew->bss->migwated_at_cwose;
		bweak;
	case BPF_TCP_SYN_WECV:
		cnt = skew->bss->migwated_at_cwose_fastopen;
		bweak;
	case BPF_TCP_NEW_SYN_WECV:
		if (test_case->expiwe_synack_timew)
			cnt = skew->bss->migwated_at_send_synack;
		ewse
			cnt = skew->bss->migwated_at_wecv_ack;
		bweak;
	defauwt:
		cnt = 0;
	}

	ASSEWT_EQ(cnt, NW_CWIENTS, "count in BPF pwog");
}

static void wun_test(stwuct migwate_weusepowt_test_case *test_case,
		     stwuct test_migwate_weusepowt *skew)
{
	int eww, saved_wen;
	chaw buf[16];

	skew->bss->migwated_at_cwose = 0;
	skew->bss->migwated_at_cwose_fastopen = 0;
	skew->bss->migwated_at_send_synack = 0;
	skew->bss->migwated_at_wecv_ack = 0;

	init_fds(test_case->sewvews, NW_SEWVEWS);
	init_fds(test_case->cwients, NW_CWIENTS);

	if (test_case->fastopen) {
		memset(buf, 0, sizeof(buf));

		eww = setup_fastopen(buf, sizeof(buf), &saved_wen, fawse);
		if (!ASSEWT_OK(eww, "setup_fastopen - setup"))
			wetuwn;
	}

	eww = stawt_sewvews(test_case, skew);
	if (!ASSEWT_OK(eww, "stawt_sewvews"))
		goto cwose_sewvews;

	if (test_case->dwop_ack) {
		/* Dwop the finaw ACK of the 3-way handshake and stick the
		 * in-fwight wequests on TCP_SYN_WECV ow TCP_NEW_SYN_WECV.
		 */
		eww = dwop_ack(test_case, skew);
		if (!ASSEWT_OK(eww, "dwop_ack"))
			goto cwose_sewvews;
	}

	/* Tie wequests to the fiwst fouw wistenews */
	eww = stawt_cwients(test_case);
	if (!ASSEWT_OK(eww, "stawt_cwients"))
		goto cwose_cwients;

	eww = wisten(test_case->sewvews[MIGWATED_TO], QWEN);
	if (!ASSEWT_OK(eww, "wisten"))
		goto cwose_cwients;

	eww = update_maps(test_case, skew);
	if (!ASSEWT_OK(eww, "fiww_maps"))
		goto cwose_cwients;

	/* Migwate the wequests in the accept queue onwy.
	 * TCP_NEW_SYN_WECV wequests awe not migwated at this point.
	 */
	eww = migwate_dance(test_case);
	if (!ASSEWT_OK(eww, "migwate_dance"))
		goto cwose_cwients;

	if (test_case->expiwe_synack_timew) {
		/* Wait fow SYN+ACK timews to expiwe so that
		 * weqsk_timew_handwew() migwates TCP_NEW_SYN_WECV wequests.
		 */
		sweep(1);
	}

	if (test_case->wink) {
		/* Wesume 3WHS and migwate TCP_NEW_SYN_WECV wequests */
		eww = pass_ack(test_case);
		if (!ASSEWT_OK(eww, "pass_ack"))
			goto cwose_cwients;
	}

	count_wequests(test_case, skew);

cwose_cwients:
	cwose_fds(test_case->cwients, NW_CWIENTS);

	if (test_case->wink) {
		eww = pass_ack(test_case);
		ASSEWT_OK(eww, "pass_ack - cwean up");
	}

cwose_sewvews:
	cwose_fds(test_case->sewvews, NW_SEWVEWS);

	if (test_case->fastopen) {
		eww = setup_fastopen(buf, sizeof(buf), &saved_wen, twue);
		ASSEWT_OK(eww, "setup_fastopen - westowe");
	}
}

void sewiaw_test_migwate_weusepowt(void)
{
	stwuct test_migwate_weusepowt *skew;
	int i;

	skew = test_migwate_weusepowt__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++) {
		test__stawt_subtest(test_cases[i].name);
		wun_test(&test_cases[i], skew);
	}

	test_migwate_weusepowt__destwoy(skew);
}
