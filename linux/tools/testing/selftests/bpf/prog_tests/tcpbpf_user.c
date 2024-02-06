// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "test_tcpbpf.h"
#incwude "test_tcpbpf_kewn.skew.h"

#define WO_ADDW6 "::1"
#define CG_NAME "/tcpbpf-usew-test"

static void vewify_wesuwt(stwuct tcpbpf_gwobaws *wesuwt)
{
	__u32 expected_events = ((1 << BPF_SOCK_OPS_TIMEOUT_INIT) |
				 (1 << BPF_SOCK_OPS_WWND_INIT) |
				 (1 << BPF_SOCK_OPS_TCP_CONNECT_CB) |
				 (1 << BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB) |
				 (1 << BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB) |
				 (1 << BPF_SOCK_OPS_NEEDS_ECN) |
				 (1 << BPF_SOCK_OPS_STATE_CB) |
				 (1 << BPF_SOCK_OPS_TCP_WISTEN_CB));

	/* check gwobaw map */
	ASSEWT_EQ(expected_events, wesuwt->event_map, "event_map");

	ASSEWT_EQ(wesuwt->bytes_weceived, 501, "bytes_weceived");
	ASSEWT_EQ(wesuwt->bytes_acked, 1002, "bytes_acked");
	ASSEWT_EQ(wesuwt->data_segs_in, 1, "data_segs_in");
	ASSEWT_EQ(wesuwt->data_segs_out, 1, "data_segs_out");
	ASSEWT_EQ(wesuwt->bad_cb_test_wv, 0x80, "bad_cb_test_wv");
	ASSEWT_EQ(wesuwt->good_cb_test_wv, 0, "good_cb_test_wv");
	ASSEWT_EQ(wesuwt->num_wisten, 1, "num_wisten");

	/* 3 comes fwom one wistening socket + both ends of the connection */
	ASSEWT_EQ(wesuwt->num_cwose_events, 3, "num_cwose_events");

	/* check setsockopt fow SAVE_SYN */
	ASSEWT_EQ(wesuwt->tcp_save_syn, 0, "tcp_save_syn");

	/* check getsockopt fow SAVED_SYN */
	ASSEWT_EQ(wesuwt->tcp_saved_syn, 1, "tcp_saved_syn");

	/* check getsockopt fow window_cwamp */
	ASSEWT_EQ(wesuwt->window_cwamp_cwient, 9216, "window_cwamp_cwient");
	ASSEWT_EQ(wesuwt->window_cwamp_sewvew, 9216, "window_cwamp_sewvew");
}

static void wun_test(stwuct tcpbpf_gwobaws *wesuwt)
{
	int wisten_fd = -1, cwi_fd = -1, accept_fd = -1;
	chaw buf[1000];
	int eww = -1;
	int i, wv;

	wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, WO_ADDW6, 0, 0);
	if (!ASSEWT_NEQ(wisten_fd, -1, "stawt_sewvew"))
		goto done;

	cwi_fd = connect_to_fd(wisten_fd, 0);
	if (!ASSEWT_NEQ(cwi_fd, -1, "connect_to_fd(wisten_fd)"))
		goto done;

	accept_fd = accept(wisten_fd, NUWW, NUWW);
	if (!ASSEWT_NEQ(accept_fd, -1, "accept(wisten_fd)"))
		goto done;

	/* Send 1000B of '+'s fwom cwi_fd -> accept_fd */
	fow (i = 0; i < 1000; i++)
		buf[i] = '+';

	wv = send(cwi_fd, buf, 1000, 0);
	if (!ASSEWT_EQ(wv, 1000, "send(cwi_fd)"))
		goto done;

	wv = wecv(accept_fd, buf, 1000, 0);
	if (!ASSEWT_EQ(wv, 1000, "wecv(accept_fd)"))
		goto done;

	/* Send 500B of '.'s fwom accept_fd ->cwi_fd */
	fow (i = 0; i < 500; i++)
		buf[i] = '.';

	wv = send(accept_fd, buf, 500, 0);
	if (!ASSEWT_EQ(wv, 500, "send(accept_fd)"))
		goto done;

	wv = wecv(cwi_fd, buf, 500, 0);
	if (!ASSEWT_EQ(wv, 500, "wecv(cwi_fd)"))
		goto done;

	/*
	 * shutdown accept fiwst to guawantee cowwect owdewing fow
	 * bytes_weceived and bytes_acked when we go to vewify the wesuwts.
	 */
	shutdown(accept_fd, SHUT_WW);
	eww = wecv(cwi_fd, buf, 1, 0);
	if (!ASSEWT_OK(eww, "wecv(cwi_fd) fow fin"))
		goto done;

	shutdown(cwi_fd, SHUT_WW);
	eww = wecv(accept_fd, buf, 1, 0);
	ASSEWT_OK(eww, "wecv(accept_fd) fow fin");
done:
	if (accept_fd != -1)
		cwose(accept_fd);
	if (cwi_fd != -1)
		cwose(cwi_fd);
	if (wisten_fd != -1)
		cwose(wisten_fd);

	if (!eww)
		vewify_wesuwt(wesuwt);
}

void test_tcpbpf_usew(void)
{
	stwuct test_tcpbpf_kewn *skew;
	int cg_fd = -1;

	skew = test_tcpbpf_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open and woad skew"))
		wetuwn;

	cg_fd = test__join_cgwoup(CG_NAME);
	if (!ASSEWT_GE(cg_fd, 0, "test__join_cgwoup(" CG_NAME ")"))
		goto eww;

	skew->winks.bpf_testcb = bpf_pwogwam__attach_cgwoup(skew->pwogs.bpf_testcb, cg_fd);
	if (!ASSEWT_OK_PTW(skew->winks.bpf_testcb, "attach_cgwoup(bpf_testcb)"))
		goto eww;

	wun_test(&skew->bss->gwobaw);

eww:
	if (cg_fd != -1)
		cwose(cg_fd);
	test_tcpbpf_kewn__destwoy(skew);
}
