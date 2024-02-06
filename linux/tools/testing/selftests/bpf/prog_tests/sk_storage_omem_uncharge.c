// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Facebook */
#incwude <test_pwogs.h>
#incwude <bpf/wibbpf.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude "sk_stowage_omem_unchawge.skew.h"

void test_sk_stowage_omem_unchawge(void)
{
	stwuct sk_stowage_omem_unchawge *skew;
	int sk_fd = -1, map_fd, eww, vawue;
	sockwen_t optwen;

	skew = sk_stowage_omem_unchawge__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew open_and_woad"))
		wetuwn;
	map_fd = bpf_map__fd(skew->maps.sk_stowage);

	/* A standawone socket not binding to addw:powt,
	 * so nentns is not needed.
	 */
	sk_fd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (!ASSEWT_GE(sk_fd, 0, "socket"))
		goto done;

	optwen = sizeof(skew->bss->cookie);
	eww = getsockopt(sk_fd, SOW_SOCKET, SO_COOKIE, &skew->bss->cookie, &optwen);
	if (!ASSEWT_OK(eww, "getsockopt(SO_COOKIE)"))
		goto done;

	vawue = 0;
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue, 0);
	if (!ASSEWT_OK(eww, "bpf_map_update_ewem(vawue=0)"))
		goto done;

	vawue = 0xdeadbeef;
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue, 0);
	if (!ASSEWT_OK(eww, "bpf_map_update_ewem(vawue=0xdeadbeef)"))
		goto done;

	eww = sk_stowage_omem_unchawge__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		goto done;

	cwose(sk_fd);
	sk_fd = -1;

	ASSEWT_EQ(skew->bss->cookie_found, 2, "cookie_found");
	ASSEWT_EQ(skew->bss->omem, 0, "omem");

done:
	sk_stowage_omem_unchawge__destwoy(skew);
	if (sk_fd != -1)
		cwose(sk_fd);
}
