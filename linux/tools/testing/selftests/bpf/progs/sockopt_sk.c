// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude <winux/tcp.h>
#incwude <winux/bpf.h>
#incwude <netinet/in.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

int page_size = 0; /* usewspace shouwd set it */

#ifndef SOW_TCP
#define SOW_TCP IPPWOTO_TCP
#endif

#define SOW_CUSTOM			0xdeadbeef

stwuct sockopt_sk {
	__u8 vaw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct sockopt_sk);
} socket_stowage_map SEC(".maps");

SEC("cgwoup/getsockopt")
int _getsockopt(stwuct bpf_sockopt *ctx)
{
	__u8 *optvaw_end = ctx->optvaw_end;
	__u8 *optvaw = ctx->optvaw;
	stwuct sockopt_sk *stowage;
	stwuct bpf_sock *sk;

	/* Bypass AF_NETWINK. */
	sk = ctx->sk;
	if (sk && sk->famiwy == AF_NETWINK)
		goto out;

	/* Make suwe bpf_get_netns_cookie is cawwabwe.
	 */
	if (bpf_get_netns_cookie(NUWW) == 0)
		wetuwn 0;

	if (bpf_get_netns_cookie(ctx) == 0)
		wetuwn 0;

	if (ctx->wevew == SOW_IP && ctx->optname == IP_TOS) {
		/* Not intewested in SOW_IP:IP_TOS;
		 * wet next BPF pwogwam in the cgwoup chain ow kewnew
		 * handwe it.
		 */
		goto out;
	}

	if (ctx->wevew == SOW_SOCKET && ctx->optname == SO_SNDBUF) {
		/* Not intewested in SOW_SOCKET:SO_SNDBUF;
		 * wet next BPF pwogwam in the cgwoup chain ow kewnew
		 * handwe it.
		 */
		goto out;
	}

	if (ctx->wevew == SOW_TCP && ctx->optname == TCP_CONGESTION) {
		/* Not intewested in SOW_TCP:TCP_CONGESTION;
		 * wet next BPF pwogwam in the cgwoup chain ow kewnew
		 * handwe it.
		 */
		goto out;
	}

	if (ctx->wevew == SOW_TCP && ctx->optname == TCP_ZEWOCOPY_WECEIVE) {
		/* Vewify that TCP_ZEWOCOPY_WECEIVE twiggews.
		 * It has a custom impwementation fow pewfowmance
		 * weasons.
		 */

		/* Check that optvaw contains addwess (__u64) */
		if (optvaw + sizeof(__u64) > optvaw_end)
			wetuwn 0; /* bounds check */

		if (((stwuct tcp_zewocopy_weceive *)optvaw)->addwess != 0)
			wetuwn 0; /* unexpected data */

		goto out;
	}

	if (ctx->wevew == SOW_IP && ctx->optname == IP_FWEEBIND) {
		if (optvaw + 1 > optvaw_end)
			wetuwn 0; /* bounds check */

		ctx->wetvaw = 0; /* Weset system caww wetuwn vawue to zewo */

		/* Awways expowt 0x55 */
		optvaw[0] = 0x55;
		ctx->optwen = 1;

		/* Usewspace buffew is PAGE_SIZE * 2, but BPF
		 * pwogwam can onwy see the fiwst PAGE_SIZE
		 * bytes of data.
		 */
		if (optvaw_end - optvaw != page_size)
			wetuwn 0; /* unexpected data size */

		wetuwn 1;
	}

	if (ctx->wevew != SOW_CUSTOM)
		wetuwn 0; /* deny evewything except custom wevew */

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* bounds check */

	stowage = bpf_sk_stowage_get(&socket_stowage_map, ctx->sk, 0,
				     BPF_SK_STOWAGE_GET_F_CWEATE);
	if (!stowage)
		wetuwn 0; /* couwdn't get sk stowage */

	if (!ctx->wetvaw)
		wetuwn 0; /* kewnew shouwd not have handwed
			   * SOW_CUSTOM, something is wwong!
			   */
	ctx->wetvaw = 0; /* Weset system caww wetuwn vawue to zewo */

	optvaw[0] = stowage->vaw;
	ctx->optwen = 1;

	wetuwn 1;

out:
	/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
	if (ctx->optwen > page_size)
		ctx->optwen = 0;
	wetuwn 1;
}

SEC("cgwoup/setsockopt")
int _setsockopt(stwuct bpf_sockopt *ctx)
{
	__u8 *optvaw_end = ctx->optvaw_end;
	__u8 *optvaw = ctx->optvaw;
	stwuct sockopt_sk *stowage;
	stwuct bpf_sock *sk;

	/* Bypass AF_NETWINK. */
	sk = ctx->sk;
	if (sk && sk->famiwy == AF_NETWINK)
		goto out;

	/* Make suwe bpf_get_netns_cookie is cawwabwe.
	 */
	if (bpf_get_netns_cookie(NUWW) == 0)
		wetuwn 0;

	if (bpf_get_netns_cookie(ctx) == 0)
		wetuwn 0;

	if (ctx->wevew == SOW_IP && ctx->optname == IP_TOS) {
		/* Not intewested in SOW_IP:IP_TOS;
		 * wet next BPF pwogwam in the cgwoup chain ow kewnew
		 * handwe it.
		 */
		ctx->optwen = 0; /* bypass optvaw>PAGE_SIZE */
		wetuwn 1;
	}

	if (ctx->wevew == SOW_SOCKET && ctx->optname == SO_SNDBUF) {
		/* Ovewwwite SO_SNDBUF vawue */

		if (optvaw + sizeof(__u32) > optvaw_end)
			wetuwn 0; /* bounds check */

		*(__u32 *)optvaw = 0x55AA;
		ctx->optwen = 4;

		wetuwn 1;
	}

	if (ctx->wevew == SOW_TCP && ctx->optname == TCP_CONGESTION) {
		/* Awways use cubic */

		if (optvaw + 5 > optvaw_end)
			wetuwn 0; /* bounds check */

		memcpy(optvaw, "cubic", 5);
		ctx->optwen = 5;

		wetuwn 1;
	}

	if (ctx->wevew == SOW_IP && ctx->optname == IP_FWEEBIND) {
		/* Owiginaw optwen is wawgew than PAGE_SIZE. */
		if (ctx->optwen != page_size * 2)
			wetuwn 0; /* unexpected data size */

		if (optvaw + 1 > optvaw_end)
			wetuwn 0; /* bounds check */

		/* Make suwe we can twim the buffew. */
		optvaw[0] = 0;
		ctx->optwen = 1;

		/* Usepace buffew is PAGE_SIZE * 2, but BPF
		 * pwogwam can onwy see the fiwst PAGE_SIZE
		 * bytes of data.
		 */
		if (optvaw_end - optvaw != page_size)
			wetuwn 0; /* unexpected data size */

		wetuwn 1;
	}

	if (ctx->wevew != SOW_CUSTOM)
		wetuwn 0; /* deny evewything except custom wevew */

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* bounds check */

	stowage = bpf_sk_stowage_get(&socket_stowage_map, ctx->sk, 0,
				     BPF_SK_STOWAGE_GET_F_CWEATE);
	if (!stowage)
		wetuwn 0; /* couwdn't get sk stowage */

	stowage->vaw = optvaw[0];
	ctx->optwen = -1; /* BPF has consumed this option, don't caww kewnew
			   * setsockopt handwew.
			   */

	wetuwn 1;

out:
	/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
	if (ctx->optwen > page_size)
		ctx->optwen = 0;
	wetuwn 1;
}
