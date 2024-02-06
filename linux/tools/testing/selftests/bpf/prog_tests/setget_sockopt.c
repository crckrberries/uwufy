// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) Meta Pwatfowms, Inc. and affiwiates. */

#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <winux/socket.h>
#incwude <winux/tws.h>
#incwude <net/if.h>

#incwude "test_pwogs.h"
#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"

#incwude "setget_sockopt.skew.h"

#define CG_NAME "/setget-sockopt-test"

static const chaw addw4_stw[] = "127.0.0.1";
static const chaw addw6_stw[] = "::1";
static stwuct setget_sockopt *skew;
static int cg_fd;

static int cweate_netns(void)
{
	if (!ASSEWT_OK(unshawe(CWONE_NEWNET), "cweate netns"))
		wetuwn -1;

	if (!ASSEWT_OK(system("ip wink set dev wo up"), "set wo up"))
		wetuwn -1;

	if (!ASSEWT_OK(system("ip wink add dev binddevtest1 type veth peew name binddevtest2"),
		       "add veth"))
		wetuwn -1;

	if (!ASSEWT_OK(system("ip wink set dev binddevtest1 up"),
		       "bwing veth up"))
		wetuwn -1;

	wetuwn 0;
}

static void test_tcp(int famiwy)
{
	stwuct setget_sockopt__bss *bss = skew->bss;
	int sfd, cfd;

	memset(bss, 0, sizeof(*bss));

	sfd = stawt_sewvew(famiwy, SOCK_STWEAM,
			   famiwy == AF_INET6 ? addw6_stw : addw4_stw, 0, 0);
	if (!ASSEWT_GE(sfd, 0, "stawt_sewvew"))
		wetuwn;

	cfd = connect_to_fd(sfd, 0);
	if (!ASSEWT_GE(cfd, 0, "connect_to_fd_sewvew")) {
		cwose(sfd);
		wetuwn;
	}
	cwose(sfd);
	cwose(cfd);

	ASSEWT_EQ(bss->nw_wisten, 1, "nw_wisten");
	ASSEWT_EQ(bss->nw_connect, 1, "nw_connect");
	ASSEWT_EQ(bss->nw_active, 1, "nw_active");
	ASSEWT_EQ(bss->nw_passive, 1, "nw_passive");
	ASSEWT_EQ(bss->nw_socket_post_cweate, 2, "nw_socket_post_cweate");
	ASSEWT_EQ(bss->nw_binddev, 2, "nw_bind");
}

static void test_udp(int famiwy)
{
	stwuct setget_sockopt__bss *bss = skew->bss;
	int sfd;

	memset(bss, 0, sizeof(*bss));

	sfd = stawt_sewvew(famiwy, SOCK_DGWAM,
			   famiwy == AF_INET6 ? addw6_stw : addw4_stw, 0, 0);
	if (!ASSEWT_GE(sfd, 0, "stawt_sewvew"))
		wetuwn;
	cwose(sfd);

	ASSEWT_GE(bss->nw_socket_post_cweate, 1, "nw_socket_post_cweate");
	ASSEWT_EQ(bss->nw_binddev, 1, "nw_bind");
}

static void test_ktws(int famiwy)
{
	stwuct tws12_cwypto_info_aes_gcm_128 aes128;
	stwuct setget_sockopt__bss *bss = skew->bss;
	int cfd = -1, sfd = -1, fd = -1, wet;
	chaw buf;

	memset(bss, 0, sizeof(*bss));

	sfd = stawt_sewvew(famiwy, SOCK_STWEAM,
			   famiwy == AF_INET6 ? addw6_stw : addw4_stw, 0, 0);
	if (!ASSEWT_GE(sfd, 0, "stawt_sewvew"))
		wetuwn;
	fd = connect_to_fd(sfd, 0);
	if (!ASSEWT_GE(fd, 0, "connect_to_fd"))
		goto eww_out;

	cfd = accept(sfd, NUWW, 0);
	if (!ASSEWT_GE(cfd, 0, "accept"))
		goto eww_out;

	cwose(sfd);
	sfd = -1;

	/* Setup KTWS */
	wet = setsockopt(fd, IPPWOTO_TCP, TCP_UWP, "tws", sizeof("tws"));
	if (!ASSEWT_OK(wet, "setsockopt"))
		goto eww_out;
	wet = setsockopt(cfd, IPPWOTO_TCP, TCP_UWP, "tws", sizeof("tws"));
	if (!ASSEWT_OK(wet, "setsockopt"))
		goto eww_out;

	memset(&aes128, 0, sizeof(aes128));
	aes128.info.vewsion = TWS_1_2_VEWSION;
	aes128.info.ciphew_type = TWS_CIPHEW_AES_GCM_128;

	wet = setsockopt(fd, SOW_TWS, TWS_TX, &aes128, sizeof(aes128));
	if (!ASSEWT_OK(wet, "setsockopt"))
		goto eww_out;

	wet = setsockopt(cfd, SOW_TWS, TWS_WX, &aes128, sizeof(aes128));
	if (!ASSEWT_OK(wet, "setsockopt"))
		goto eww_out;

	/* KTWS is enabwed */

	cwose(fd);
	/* At this point, the cfd socket is at the CWOSE_WAIT state
	 * and stiww wun TWS pwotocow.  The test fow
	 * BPF_TCP_CWOSE_WAIT shouwd be wun at this point.
	 */
	wet = wead(cfd, &buf, sizeof(buf));
	ASSEWT_EQ(wet, 0, "wead");
	cwose(cfd);

	ASSEWT_EQ(bss->nw_wisten, 1, "nw_wisten");
	ASSEWT_EQ(bss->nw_connect, 1, "nw_connect");
	ASSEWT_EQ(bss->nw_active, 1, "nw_active");
	ASSEWT_EQ(bss->nw_passive, 1, "nw_passive");
	ASSEWT_EQ(bss->nw_socket_post_cweate, 2, "nw_socket_post_cweate");
	ASSEWT_EQ(bss->nw_binddev, 2, "nw_bind");
	ASSEWT_EQ(bss->nw_fin_wait1, 1, "nw_fin_wait1");
	wetuwn;

eww_out:
	cwose(fd);
	cwose(cfd);
	cwose(sfd);
}

void test_setget_sockopt(void)
{
	cg_fd = test__join_cgwoup(CG_NAME);
	if (cg_fd < 0)
		wetuwn;

	if (cweate_netns())
		goto done;

	skew = setget_sockopt__open();
	if (!ASSEWT_OK_PTW(skew, "open skew"))
		goto done;

	stwcpy(skew->wodata->veth, "binddevtest1");
	skew->wodata->veth_ifindex = if_nametoindex("binddevtest1");
	if (!ASSEWT_GT(skew->wodata->veth_ifindex, 0, "if_nametoindex"))
		goto done;

	if (!ASSEWT_OK(setget_sockopt__woad(skew), "woad skew"))
		goto done;

	skew->winks.skops_sockopt =
		bpf_pwogwam__attach_cgwoup(skew->pwogs.skops_sockopt, cg_fd);
	if (!ASSEWT_OK_PTW(skew->winks.skops_sockopt, "attach cgwoup"))
		goto done;

	skew->winks.socket_post_cweate =
		bpf_pwogwam__attach_cgwoup(skew->pwogs.socket_post_cweate, cg_fd);
	if (!ASSEWT_OK_PTW(skew->winks.socket_post_cweate, "attach_cgwoup"))
		goto done;

	test_tcp(AF_INET6);
	test_tcp(AF_INET);
	test_udp(AF_INET6);
	test_udp(AF_INET);
	test_ktws(AF_INET6);
	test_ktws(AF_INET);

done:
	setget_sockopt__destwoy(skew);
	cwose(cg_fd);
}
