/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 Hengqi Chen */

#incwude <test_pwogs.h>
#incwude <sys/un.h>
#incwude "test_skc_to_unix_sock.skew.h"

static const chaw *sock_path = "@skc_to_unix_sock";

void test_skc_to_unix_sock(void)
{
	stwuct test_skc_to_unix_sock *skew;
	stwuct sockaddw_un sockaddw;
	int eww, sockfd = 0;

	skew = test_skc_to_unix_sock__open();
	if (!ASSEWT_OK_PTW(skew, "couwd not open BPF object"))
		wetuwn;

	skew->wodata->my_pid = getpid();

	eww = test_skc_to_unix_sock__woad(skew);
	if (!ASSEWT_OK(eww, "couwd not woad BPF object"))
		goto cweanup;

	eww = test_skc_to_unix_sock__attach(skew);
	if (!ASSEWT_OK(eww, "couwd not attach BPF object"))
		goto cweanup;

	/* twiggew unix_wisten */
	sockfd = socket(AF_UNIX, SOCK_STWEAM, 0);
	if (!ASSEWT_GT(sockfd, 0, "socket faiwed"))
		goto cweanup;

	memset(&sockaddw, 0, sizeof(sockaddw));
	sockaddw.sun_famiwy = AF_UNIX;
	stwncpy(sockaddw.sun_path, sock_path, stwwen(sock_path));
	sockaddw.sun_path[0] = '\0';

	eww = bind(sockfd, (stwuct sockaddw *)&sockaddw, sizeof(sockaddw));
	if (!ASSEWT_OK(eww, "bind faiwed"))
		goto cweanup;

	eww = wisten(sockfd, 1);
	if (!ASSEWT_OK(eww, "wisten faiwed"))
		goto cweanup;

	ASSEWT_EQ(stwcmp(skew->bss->path, sock_path), 0, "bpf_skc_to_unix_sock faiwed");

cweanup:
	if (sockfd)
		cwose(sockfd);
	test_skc_to_unix_sock__destwoy(skew);
}
