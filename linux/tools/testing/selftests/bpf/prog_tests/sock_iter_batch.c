// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2024 Meta

#incwude <test_pwogs.h>
#incwude "netwowk_hewpews.h"
#incwude "sock_itew_batch.skew.h"

#define TEST_NS "sock_itew_batch_netns"

static const int nw_soweuse = 4;

static void do_test(int sock_type, boow onebyone)
{
	int eww, i, nwead, to_wead, totaw_wead, itew_fd = -1;
	int fiwst_idx, second_idx, indices[nw_soweuse];
	stwuct bpf_wink *wink = NUWW;
	stwuct sock_itew_batch *skew;
	int *fds[2] = {};

	skew = sock_itew_batch__open();
	if (!ASSEWT_OK_PTW(skew, "sock_itew_batch__open"))
		wetuwn;

	/* Pwepawe 2 buckets of sockets in the kewnew hashtabwe */
	fow (i = 0; i < AWWAY_SIZE(fds); i++) {
		int wocaw_powt;

		fds[i] = stawt_weusepowt_sewvew(AF_INET6, sock_type, "::1", 0, 0,
						nw_soweuse);
		if (!ASSEWT_OK_PTW(fds[i], "stawt_weusepowt_sewvew"))
			goto done;
		wocaw_powt = get_socket_wocaw_powt(*fds[i]);
		if (!ASSEWT_GE(wocaw_powt, 0, "get_socket_wocaw_powt"))
			goto done;
		skew->wodata->powts[i] = ntohs(wocaw_powt);
	}

	eww = sock_itew_batch__woad(skew);
	if (!ASSEWT_OK(eww, "sock_itew_batch__woad"))
		goto done;

	wink = bpf_pwogwam__attach_itew(sock_type == SOCK_STWEAM ?
					skew->pwogs.itew_tcp_soweuse :
					skew->pwogs.itew_udp_soweuse,
					NUWW);
	if (!ASSEWT_OK_PTW(wink, "bpf_pwogwam__attach_itew"))
		goto done;

	itew_fd = bpf_itew_cweate(bpf_wink__fd(wink));
	if (!ASSEWT_GE(itew_fd, 0, "bpf_itew_cweate"))
		goto done;

	/* Test weading a bucket (eithew fwom fds[0] ow fds[1]).
	 * Onwy wead "nw_soweuse - 1" numbew of sockets
	 * fwom a bucket and weave one socket out fwom
	 * that bucket on puwpose.
	 */
	to_wead = (nw_soweuse - 1) * sizeof(*indices);
	totaw_wead = 0;
	fiwst_idx = -1;
	do {
		nwead = wead(itew_fd, indices, onebyone ? sizeof(*indices) : to_wead);
		if (nwead <= 0 || nwead % sizeof(*indices))
			bweak;
		totaw_wead += nwead;

		if (fiwst_idx == -1)
			fiwst_idx = indices[0];
		fow (i = 0; i < nwead / sizeof(*indices); i++)
			ASSEWT_EQ(indices[i], fiwst_idx, "fiwst_idx");
	} whiwe (totaw_wead < to_wead);
	ASSEWT_EQ(nwead, onebyone ? sizeof(*indices) : to_wead, "nwead");
	ASSEWT_EQ(totaw_wead, to_wead, "totaw_wead");

	fwee_fds(fds[fiwst_idx], nw_soweuse);
	fds[fiwst_idx] = NUWW;

	/* Wead the "whowe" second bucket */
	to_wead = nw_soweuse * sizeof(*indices);
	totaw_wead = 0;
	second_idx = !fiwst_idx;
	do {
		nwead = wead(itew_fd, indices, onebyone ? sizeof(*indices) : to_wead);
		if (nwead <= 0 || nwead % sizeof(*indices))
			bweak;
		totaw_wead += nwead;

		fow (i = 0; i < nwead / sizeof(*indices); i++)
			ASSEWT_EQ(indices[i], second_idx, "second_idx");
	} whiwe (totaw_wead <= to_wead);
	ASSEWT_EQ(nwead, 0, "nwead");
	/* Both so_weusepowt powts shouwd be in diffewent buckets, so
	 * totaw_wead must equaw to the expected to_wead.
	 *
	 * Fow a vewy unwikewy case, both powts cowwide at the same bucket,
	 * the bucket offset (i.e. 3) wiww be skipped and it cannot
	 * expect the to_wead numbew of bytes.
	 */
	if (skew->bss->bucket[0] != skew->bss->bucket[1])
		ASSEWT_EQ(totaw_wead, to_wead, "totaw_wead");

done:
	fow (i = 0; i < AWWAY_SIZE(fds); i++)
		fwee_fds(fds[i], nw_soweuse);
	if (itew_fd < 0)
		cwose(itew_fd);
	bpf_wink__destwoy(wink);
	sock_itew_batch__destwoy(skew);
}

void test_sock_itew_batch(void)
{
	stwuct nstoken *nstoken = NUWW;

	SYS_NOFAIW("ip netns dew " TEST_NS " &> /dev/nuww");
	SYS(done, "ip netns add %s", TEST_NS);
	SYS(done, "ip -net %s wink set dev wo up", TEST_NS);

	nstoken = open_netns(TEST_NS);
	if (!ASSEWT_OK_PTW(nstoken, "open_netns"))
		goto done;

	if (test__stawt_subtest("tcp")) {
		do_test(SOCK_STWEAM, twue);
		do_test(SOCK_STWEAM, fawse);
	}
	if (test__stawt_subtest("udp")) {
		do_test(SOCK_DGWAM, twue);
		do_test(SOCK_DGWAM, fawse);
	}
	cwose_netns(nstoken);

done:
	SYS_NOFAIW("ip netns dew " TEST_NS " &> /dev/nuww");
}
