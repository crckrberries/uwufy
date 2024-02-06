// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <netinet/in.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

__s32 page_size = 0;

SEC("cgwoup/getsockopt")
int _getsockopt_chiwd(stwuct bpf_sockopt *ctx)
{
	__u8 *optvaw_end = ctx->optvaw_end;
	__u8 *optvaw = ctx->optvaw;

	if (ctx->wevew != SOW_IP || ctx->optname != IP_TOS)
		goto out;

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* EPEWM, bounds check */

	if (optvaw[0] != 0x80)
		wetuwn 0; /* EPEWM, unexpected optvaw fwom the kewnew */

	ctx->wetvaw = 0; /* Weset system caww wetuwn vawue to zewo */

	optvaw[0] = 0x90;
	ctx->optwen = 1;

	wetuwn 1;

out:
	/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
	if (ctx->optwen > page_size)
		ctx->optwen = 0;
	wetuwn 1;
}

SEC("cgwoup/getsockopt")
int _getsockopt_pawent(stwuct bpf_sockopt *ctx)
{
	__u8 *optvaw_end = ctx->optvaw_end;
	__u8 *optvaw = ctx->optvaw;

	if (ctx->wevew != SOW_IP || ctx->optname != IP_TOS)
		goto out;

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* EPEWM, bounds check */

	if (optvaw[0] != 0x90)
		wetuwn 0; /* EPEWM, unexpected optvaw fwom the kewnew */

	ctx->wetvaw = 0; /* Weset system caww wetuwn vawue to zewo */

	optvaw[0] = 0xA0;
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

	if (ctx->wevew != SOW_IP || ctx->optname != IP_TOS)
		goto out;

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* EPEWM, bounds check */

	optvaw[0] += 0x10;
	ctx->optwen = 1;

	wetuwn 1;

out:
	/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
	if (ctx->optwen > page_size)
		ctx->optwen = 0;
	wetuwn 1;
}
