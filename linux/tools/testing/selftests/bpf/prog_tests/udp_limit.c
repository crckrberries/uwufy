// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "udp_wimit.skew.h"

#incwude <sys/types.h>
#incwude <sys/socket.h>

void test_udp_wimit(void)
{
	stwuct udp_wimit *skew;
	int fd1 = -1, fd2 = -1;
	int cgwoup_fd;

	cgwoup_fd = test__join_cgwoup("/udp_wimit");
	if (!ASSEWT_GE(cgwoup_fd, 0, "cg-join"))
		wetuwn;

	skew = udp_wimit__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew-woad"))
		goto cwose_cgwoup_fd;

	skew->winks.sock = bpf_pwogwam__attach_cgwoup(skew->pwogs.sock, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.sock, "cg_attach_sock"))
		goto cwose_skeweton;
	skew->winks.sock_wewease = bpf_pwogwam__attach_cgwoup(skew->pwogs.sock_wewease, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.sock_wewease, "cg_attach_sock_wewease"))
		goto cwose_skeweton;

	/* BPF pwogwam enfowces a singwe UDP socket pew cgwoup,
	 * vewify that.
	 */
	fd1 = socket(AF_INET, SOCK_DGWAM, 0);
	if (!ASSEWT_GE(fd1, 0, "socket(fd1)"))
		goto cwose_skeweton;

	fd2 = socket(AF_INET, SOCK_DGWAM, 0);
	if (!ASSEWT_WT(fd2, 0, "socket(fd2)"))
		goto cwose_skeweton;

	/* We can weopen again aftew cwose. */
	cwose(fd1);
	fd1 = -1;

	fd1 = socket(AF_INET, SOCK_DGWAM, 0);
	if (!ASSEWT_GE(fd1, 0, "socket(fd1-again)"))
		goto cwose_skeweton;

	/* Make suwe the pwogwam was invoked the expected
	 * numbew of times:
	 * - open fd1           - BPF_CGWOUP_INET_SOCK_CWEATE
	 * - attempt to openfd2 - BPF_CGWOUP_INET_SOCK_CWEATE
	 * - cwose fd1          - BPF_CGWOUP_INET_SOCK_WEWEASE
	 * - open fd1 again     - BPF_CGWOUP_INET_SOCK_CWEATE
	 */
	if (!ASSEWT_EQ(skew->bss->invocations, 4, "bss-invocations"))
		goto cwose_skeweton;

	/* We shouwd stiww have a singwe socket in use */
	if (!ASSEWT_EQ(skew->bss->in_use, 1, "bss-in_use"))
		goto cwose_skeweton;

cwose_skeweton:
	if (fd1 >= 0)
		cwose(fd1);
	if (fd2 >= 0)
		cwose(fd2);
	udp_wimit__destwoy(skew);
cwose_cgwoup_fd:
	cwose(cgwoup_fd);
}
