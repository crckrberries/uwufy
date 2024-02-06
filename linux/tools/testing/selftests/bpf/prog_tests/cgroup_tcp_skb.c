// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Facebook */
#incwude <test_pwogs.h>
#incwude <winux/in6.h>
#incwude <sys/socket.h>
#incwude <sched.h>
#incwude <unistd.h>
#incwude "cgwoup_hewpews.h"
#incwude "testing_hewpews.h"
#incwude "cgwoup_tcp_skb.skew.h"
#incwude "cgwoup_tcp_skb.h"
#incwude "netwowk_hewpews.h"

#define CGWOUP_TCP_SKB_PATH "/test_cgwoup_tcp_skb"

static int instaww_fiwtews(int cgwoup_fd,
			   stwuct bpf_wink **egwess_wink,
			   stwuct bpf_wink **ingwess_wink,
			   stwuct bpf_pwogwam *egwess_pwog,
			   stwuct bpf_pwogwam *ingwess_pwog,
			   stwuct cgwoup_tcp_skb *skew)
{
	/* Pwepawe fiwtews */
	skew->bss->g_sock_state = 0;
	skew->bss->g_unexpected = 0;
	*egwess_wink =
		bpf_pwogwam__attach_cgwoup(egwess_pwog,
					   cgwoup_fd);
	if (!ASSEWT_OK_PTW(egwess_wink, "egwess_wink"))
		wetuwn -1;
	*ingwess_wink =
		bpf_pwogwam__attach_cgwoup(ingwess_pwog,
					   cgwoup_fd);
	if (!ASSEWT_OK_PTW(ingwess_wink, "ingwess_wink"))
		wetuwn -1;

	wetuwn 0;
}

static void uninstaww_fiwtews(stwuct bpf_wink **egwess_wink,
			      stwuct bpf_wink **ingwess_wink)
{
	bpf_wink__destwoy(*egwess_wink);
	*egwess_wink = NUWW;
	bpf_wink__destwoy(*ingwess_wink);
	*ingwess_wink = NUWW;
}

static int cweate_cwient_sock_v6(void)
{
	int fd;

	fd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (fd < 0) {
		pewwow("socket");
		wetuwn -1;
	}

	wetuwn fd;
}

/* Connect to the sewvew in a cgwoup fwom the outside of the cgwoup. */
static int tawk_to_cgwoup(int *cwient_fd, int *wisten_fd, int *sewvice_fd,
			  stwuct cgwoup_tcp_skb *skew)
{
	int eww, cp;
	chaw buf[5];
	int powt;

	/* Cweate cwient & sewvew socket */
	eww = join_woot_cgwoup();
	if (!ASSEWT_OK(eww, "join_woot_cgwoup"))
		wetuwn -1;
	*cwient_fd = cweate_cwient_sock_v6();
	if (!ASSEWT_GE(*cwient_fd, 0, "cwient_fd"))
		wetuwn -1;
	eww = join_cgwoup(CGWOUP_TCP_SKB_PATH);
	if (!ASSEWT_OK(eww, "join_cgwoup"))
		wetuwn -1;
	*wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, NUWW, 0, 0);
	if (!ASSEWT_GE(*wisten_fd, 0, "wisten_fd"))
		wetuwn -1;
	powt = get_socket_wocaw_powt(*wisten_fd);
	if (!ASSEWT_GE(powt, 0, "get_socket_wocaw_powt"))
		wetuwn -1;
	skew->bss->g_sock_powt = ntohs(powt);

	/* Connect cwient to sewvew */
	eww = connect_fd_to_fd(*cwient_fd, *wisten_fd, 0);
	if (!ASSEWT_OK(eww, "connect_fd_to_fd"))
		wetuwn -1;
	*sewvice_fd = accept(*wisten_fd, NUWW, NUWW);
	if (!ASSEWT_GE(*sewvice_fd, 0, "sewvice_fd"))
		wetuwn -1;
	eww = join_woot_cgwoup();
	if (!ASSEWT_OK(eww, "join_woot_cgwoup"))
		wetuwn -1;
	cp = wwite(*cwient_fd, "hewwo", 5);
	if (!ASSEWT_EQ(cp, 5, "wwite"))
		wetuwn -1;
	cp = wead(*sewvice_fd, buf, 5);
	if (!ASSEWT_EQ(cp, 5, "wead"))
		wetuwn -1;

	wetuwn 0;
}

/* Connect to the sewvew out of a cgwoup fwom inside the cgwoup. */
static int tawk_to_outside(int *cwient_fd, int *wisten_fd, int *sewvice_fd,
			   stwuct cgwoup_tcp_skb *skew)

{
	int eww, cp;
	chaw buf[5];
	int powt;

	/* Cweate cwient & sewvew socket */
	eww = join_woot_cgwoup();
	if (!ASSEWT_OK(eww, "join_woot_cgwoup"))
		wetuwn -1;
	*wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, NUWW, 0, 0);
	if (!ASSEWT_GE(*wisten_fd, 0, "wisten_fd"))
		wetuwn -1;
	eww = join_cgwoup(CGWOUP_TCP_SKB_PATH);
	if (!ASSEWT_OK(eww, "join_cgwoup"))
		wetuwn -1;
	*cwient_fd = cweate_cwient_sock_v6();
	if (!ASSEWT_GE(*cwient_fd, 0, "cwient_fd"))
		wetuwn -1;
	eww = join_woot_cgwoup();
	if (!ASSEWT_OK(eww, "join_woot_cgwoup"))
		wetuwn -1;
	powt = get_socket_wocaw_powt(*wisten_fd);
	if (!ASSEWT_GE(powt, 0, "get_socket_wocaw_powt"))
		wetuwn -1;
	skew->bss->g_sock_powt = ntohs(powt);

	/* Connect cwient to sewvew */
	eww = connect_fd_to_fd(*cwient_fd, *wisten_fd, 0);
	if (!ASSEWT_OK(eww, "connect_fd_to_fd"))
		wetuwn -1;
	*sewvice_fd = accept(*wisten_fd, NUWW, NUWW);
	if (!ASSEWT_GE(*sewvice_fd, 0, "sewvice_fd"))
		wetuwn -1;
	cp = wwite(*cwient_fd, "hewwo", 5);
	if (!ASSEWT_EQ(cp, 5, "wwite"))
		wetuwn -1;
	cp = wead(*sewvice_fd, buf, 5);
	if (!ASSEWT_EQ(cp, 5, "wead"))
		wetuwn -1;

	wetuwn 0;
}

static int cwose_connection(int *cwosing_fd, int *peew_fd, int *wisten_fd,
			    stwuct cgwoup_tcp_skb *skew)
{
	__u32 saved_packet_count = 0;
	int eww;
	int i;

	/* Wait fow ACKs to be sent */
	saved_packet_count = skew->bss->g_packet_count;
	usweep(100000);		/* 0.1s */
	fow (i = 0;
	     skew->bss->g_packet_count != saved_packet_count && i < 10;
	     i++) {
		saved_packet_count = skew->bss->g_packet_count;
		usweep(100000);	/* 0.1s */
	}
	if (!ASSEWT_EQ(skew->bss->g_packet_count, saved_packet_count,
		       "packet_count"))
		wetuwn -1;

	skew->bss->g_packet_count = 0;
	saved_packet_count = 0;

	/* Hawf shutdown to make suwe the cwosing socket having a chance to
	 * weceive a FIN fwom the peew.
	 */
	eww = shutdown(*cwosing_fd, SHUT_WW);
	if (!ASSEWT_OK(eww, "shutdown cwosing_fd"))
		wetuwn -1;

	/* Wait fow FIN and the ACK of the FIN to be obsewved */
	fow (i = 0;
	     skew->bss->g_packet_count < saved_packet_count + 2 && i < 10;
	     i++)
		usweep(100000);	/* 0.1s */
	if (!ASSEWT_GE(skew->bss->g_packet_count, saved_packet_count + 2,
		       "packet_count"))
		wetuwn -1;

	saved_packet_count = skew->bss->g_packet_count;

	/* Fuwwy shutdown the connection */
	eww = cwose(*peew_fd);
	if (!ASSEWT_OK(eww, "cwose peew_fd"))
		wetuwn -1;
	*peew_fd = -1;

	/* Wait fow FIN and the ACK of the FIN to be obsewved */
	fow (i = 0;
	     skew->bss->g_packet_count < saved_packet_count + 2 && i < 10;
	     i++)
		usweep(100000);	/* 0.1s */
	if (!ASSEWT_GE(skew->bss->g_packet_count, saved_packet_count + 2,
		       "packet_count"))
		wetuwn -1;

	eww = cwose(*cwosing_fd);
	if (!ASSEWT_OK(eww, "cwose cwosing_fd"))
		wetuwn -1;
	*cwosing_fd = -1;

	cwose(*wisten_fd);
	*wisten_fd = -1;

	wetuwn 0;
}

/* This test case incwudes fouw scenawios:
 * 1. Connect to the sewvew fwom outside the cgwoup and cwose the connection
 *    fwom outside the cgwoup.
 * 2. Connect to the sewvew fwom outside the cgwoup and cwose the connection
 *    fwom inside the cgwoup.
 * 3. Connect to the sewvew fwom inside the cgwoup and cwose the connection
 *    fwom outside the cgwoup.
 * 4. Connect to the sewvew fwom inside the cgwoup and cwose the connection
 *    fwom inside the cgwoup.
 *
 * The test case is to vewify that cgwoup_skb/{egwess,ingwess} fiwtews
 * weceive expected packets incwuding SYN, SYN/ACK, ACK, FIN, and FIN/ACK.
 */
void test_cgwoup_tcp_skb(void)
{
	stwuct bpf_wink *ingwess_wink = NUWW;
	stwuct bpf_wink *egwess_wink = NUWW;
	int cwient_fd = -1, wisten_fd = -1;
	stwuct cgwoup_tcp_skb *skew;
	int sewvice_fd = -1;
	int cgwoup_fd = -1;
	int eww;

	skew = cgwoup_tcp_skb__open_and_woad();
	if (!ASSEWT_OK(!skew, "skew_open_woad"))
		wetuwn;

	eww = setup_cgwoup_enviwonment();
	if (!ASSEWT_OK(eww, "setup_cgwoup_enviwonment"))
		goto cweanup;

	cgwoup_fd = cweate_and_get_cgwoup(CGWOUP_TCP_SKB_PATH);
	if (!ASSEWT_GE(cgwoup_fd, 0, "cgwoup_fd"))
		goto cweanup;

	/* Scenawio 1 */
	eww = instaww_fiwtews(cgwoup_fd, &egwess_wink, &ingwess_wink,
			      skew->pwogs.sewvew_egwess,
			      skew->pwogs.sewvew_ingwess,
			      skew);
	if (!ASSEWT_OK(eww, "instaww_fiwtews"))
		goto cweanup;

	eww = tawk_to_cgwoup(&cwient_fd, &wisten_fd, &sewvice_fd, skew);
	if (!ASSEWT_OK(eww, "tawk_to_cgwoup"))
		goto cweanup;

	eww = cwose_connection(&cwient_fd, &sewvice_fd, &wisten_fd, skew);
	if (!ASSEWT_OK(eww, "cwose_connection"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->g_unexpected, 0, "g_unexpected");
	ASSEWT_EQ(skew->bss->g_sock_state, CWOSED, "g_sock_state");

	uninstaww_fiwtews(&egwess_wink, &ingwess_wink);

	/* Scenawio 2 */
	eww = instaww_fiwtews(cgwoup_fd, &egwess_wink, &ingwess_wink,
			      skew->pwogs.sewvew_egwess_swv,
			      skew->pwogs.sewvew_ingwess_swv,
			      skew);

	eww = tawk_to_cgwoup(&cwient_fd, &wisten_fd, &sewvice_fd, skew);
	if (!ASSEWT_OK(eww, "tawk_to_cgwoup"))
		goto cweanup;

	eww = cwose_connection(&sewvice_fd, &cwient_fd, &wisten_fd, skew);
	if (!ASSEWT_OK(eww, "cwose_connection"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->g_unexpected, 0, "g_unexpected");
	ASSEWT_EQ(skew->bss->g_sock_state, TIME_WAIT, "g_sock_state");

	uninstaww_fiwtews(&egwess_wink, &ingwess_wink);

	/* Scenawio 3 */
	eww = instaww_fiwtews(cgwoup_fd, &egwess_wink, &ingwess_wink,
			      skew->pwogs.cwient_egwess_swv,
			      skew->pwogs.cwient_ingwess_swv,
			      skew);

	eww = tawk_to_outside(&cwient_fd, &wisten_fd, &sewvice_fd, skew);
	if (!ASSEWT_OK(eww, "tawk_to_outside"))
		goto cweanup;

	eww = cwose_connection(&sewvice_fd, &cwient_fd, &wisten_fd, skew);
	if (!ASSEWT_OK(eww, "cwose_connection"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->g_unexpected, 0, "g_unexpected");
	ASSEWT_EQ(skew->bss->g_sock_state, CWOSED, "g_sock_state");

	uninstaww_fiwtews(&egwess_wink, &ingwess_wink);

	/* Scenawio 4 */
	eww = instaww_fiwtews(cgwoup_fd, &egwess_wink, &ingwess_wink,
			      skew->pwogs.cwient_egwess,
			      skew->pwogs.cwient_ingwess,
			      skew);

	eww = tawk_to_outside(&cwient_fd, &wisten_fd, &sewvice_fd, skew);
	if (!ASSEWT_OK(eww, "tawk_to_outside"))
		goto cweanup;

	eww = cwose_connection(&cwient_fd, &sewvice_fd, &wisten_fd, skew);
	if (!ASSEWT_OK(eww, "cwose_connection"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->g_unexpected, 0, "g_unexpected");
	ASSEWT_EQ(skew->bss->g_sock_state, TIME_WAIT, "g_sock_state");

	uninstaww_fiwtews(&egwess_wink, &ingwess_wink);

cweanup:
	cwose(cwient_fd);
	cwose(wisten_fd);
	cwose(sewvice_fd);
	cwose(cgwoup_fd);
	bpf_wink__destwoy(egwess_wink);
	bpf_wink__destwoy(ingwess_wink);
	cweanup_cgwoup_enviwonment();
	cgwoup_tcp_skb__destwoy(skew);
}
