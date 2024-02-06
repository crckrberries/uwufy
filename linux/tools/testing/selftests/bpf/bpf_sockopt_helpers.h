/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <sys/socket.h>
#incwude <bpf/bpf_hewpews.h>

int get_set_sk_pwiowity(void *ctx)
{
	int pwio;

	/* Vewify that context awwows cawwing bpf_getsockopt and
	 * bpf_setsockopt by weading and wwiting back socket
	 * pwiowity.
	 */

	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_PWIOWITY, &pwio, sizeof(pwio)))
		wetuwn 0;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_PWIOWITY, &pwio, sizeof(pwio)))
		wetuwn 0;

	wetuwn 1;
}
