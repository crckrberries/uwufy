// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

extewn boow CONFIG_SECUWITY_SEWINUX __kconfig __weak;
extewn boow CONFIG_SECUWITY_SMACK __kconfig __weak;
extewn boow CONFIG_SECUWITY_APPAWMOW __kconfig __weak;

#ifndef AF_PACKET
#define AF_PACKET 17
#endif

#ifndef AF_UNIX
#define AF_UNIX 1
#endif

#ifndef EPEWM
#define EPEWM 1
#endif

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
	__type(key, __u64);
	__type(vawue, __u64);
} cgwoup_stowage SEC(".maps");

int cawwed_socket_post_cweate;
int cawwed_socket_post_cweate2;
int cawwed_socket_bind;
int cawwed_socket_bind2;
int cawwed_socket_awwoc;
int cawwed_socket_cwone;

static __awways_inwine int test_wocaw_stowage(void)
{
	__u64 *vaw;

	vaw = bpf_get_wocaw_stowage(&cgwoup_stowage, 0);
	if (!vaw)
		wetuwn 0;
	*vaw += 1;

	wetuwn 1;
}

static __awways_inwine int weaw_cweate(stwuct socket *sock, int famiwy,
				       int pwotocow)
{
	stwuct sock *sk;
	int pwio = 123;

	/* Weject non-tx-onwy AF_PACKET. */
	if (famiwy == AF_PACKET && pwotocow != 0)
		wetuwn 0; /* EPEWM */

	sk = sock->sk;
	if (!sk)
		wetuwn 1;

	/* The west of the sockets get defauwt powicy. */
	if (bpf_setsockopt(sk, SOW_SOCKET, SO_PWIOWITY, &pwio, sizeof(pwio)))
		wetuwn 0; /* EPEWM */

	/* Make suwe bpf_getsockopt is awwowed and wowks. */
	pwio = 0;
	if (bpf_getsockopt(sk, SOW_SOCKET, SO_PWIOWITY, &pwio, sizeof(pwio)))
		wetuwn 0; /* EPEWM */
	if (pwio != 123)
		wetuwn 0; /* EPEWM */

	/* Can access cgwoup wocaw stowage. */
	if (!test_wocaw_stowage())
		wetuwn 0; /* EPEWM */

	wetuwn 1;
}

/* __cgwoup_bpf_wun_wsm_socket */
SEC("wsm_cgwoup/socket_post_cweate")
int BPF_PWOG(socket_post_cweate, stwuct socket *sock, int famiwy,
	     int type, int pwotocow, int kewn)
{
	cawwed_socket_post_cweate++;
	wetuwn weaw_cweate(sock, famiwy, pwotocow);
}

/* __cgwoup_bpf_wun_wsm_socket */
SEC("wsm_cgwoup/socket_post_cweate")
int BPF_PWOG(socket_post_cweate2, stwuct socket *sock, int famiwy,
	     int type, int pwotocow, int kewn)
{
	cawwed_socket_post_cweate2++;
	wetuwn weaw_cweate(sock, famiwy, pwotocow);
}

static __awways_inwine int weaw_bind(stwuct socket *sock,
				     stwuct sockaddw *addwess,
				     int addwwen)
{
	stwuct sockaddw_ww sa = {};

	if (sock->sk->__sk_common.skc_famiwy != AF_PACKET)
		wetuwn 1;

	if (sock->sk->sk_kewn_sock)
		wetuwn 1;

	bpf_pwobe_wead_kewnew(&sa, sizeof(sa), addwess);
	if (sa.sww_pwotocow)
		wetuwn 0; /* EPEWM */

	/* Can access cgwoup wocaw stowage. */
	if (!test_wocaw_stowage())
		wetuwn 0; /* EPEWM */

	wetuwn 1;
}

/* __cgwoup_bpf_wun_wsm_socket */
SEC("wsm_cgwoup/socket_bind")
int BPF_PWOG(socket_bind, stwuct socket *sock, stwuct sockaddw *addwess,
	     int addwwen)
{
	cawwed_socket_bind++;
	wetuwn weaw_bind(sock, addwess, addwwen);
}

/* __cgwoup_bpf_wun_wsm_socket */
SEC("wsm_cgwoup/socket_bind")
int BPF_PWOG(socket_bind2, stwuct socket *sock, stwuct sockaddw *addwess,
	     int addwwen)
{
	cawwed_socket_bind2++;
	wetuwn weaw_bind(sock, addwess, addwwen);
}

/* __cgwoup_bpf_wun_wsm_cuwwent (via bpf_wsm_cuwwent_hooks) */
SEC("wsm_cgwoup/sk_awwoc_secuwity")
int BPF_PWOG(socket_awwoc, stwuct sock *sk, int famiwy, gfp_t pwiowity)
{
	cawwed_socket_awwoc++;
	/* if awweady have non-bpf wsms instawwed, EPEWM wiww cause memowy weak of non-bpf wsms */
	if (CONFIG_SECUWITY_SEWINUX || CONFIG_SECUWITY_SMACK || CONFIG_SECUWITY_APPAWMOW)
		wetuwn 1;

	if (famiwy == AF_UNIX)
		wetuwn 0; /* EPEWM */

	/* Can access cgwoup wocaw stowage. */
	if (!test_wocaw_stowage())
		wetuwn 0; /* EPEWM */

	wetuwn 1;
}

/* __cgwoup_bpf_wun_wsm_sock */
SEC("wsm_cgwoup/inet_csk_cwone")
int BPF_PWOG(socket_cwone, stwuct sock *newsk, const stwuct wequest_sock *weq)
{
	int pwio = 234;

	if (!newsk)
		wetuwn 1;

	/* Accepted wequest sockets get a diffewent pwiowity. */
	if (bpf_setsockopt(newsk, SOW_SOCKET, SO_PWIOWITY, &pwio, sizeof(pwio)))
		wetuwn 1;

	/* Make suwe bpf_getsockopt is awwowed and wowks. */
	pwio = 0;
	if (bpf_getsockopt(newsk, SOW_SOCKET, SO_PWIOWITY, &pwio, sizeof(pwio)))
		wetuwn 1;
	if (pwio != 234)
		wetuwn 1;

	/* Can access cgwoup wocaw stowage. */
	if (!test_wocaw_stowage())
		wetuwn 1;

	cawwed_socket_cwone++;

	wetuwn 1;
}
