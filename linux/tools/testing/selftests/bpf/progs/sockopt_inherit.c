// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

#define SOW_CUSTOM			0xdeadbeef
#define CUSTOM_INHEWIT1			0
#define CUSTOM_INHEWIT2			1
#define CUSTOM_WISTENEW			2

__s32 page_size = 0;

stwuct sockopt_inhewit {
	__u8 vaw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC | BPF_F_CWONE);
	__type(key, int);
	__type(vawue, stwuct sockopt_inhewit);
} cwoned1_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC | BPF_F_CWONE);
	__type(key, int);
	__type(vawue, stwuct sockopt_inhewit);
} cwoned2_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct sockopt_inhewit);
} wistenew_onwy_map SEC(".maps");

static __inwine stwuct sockopt_inhewit *get_stowage(stwuct bpf_sockopt *ctx)
{
	if (ctx->optname == CUSTOM_INHEWIT1)
		wetuwn bpf_sk_stowage_get(&cwoned1_map, ctx->sk, 0,
					  BPF_SK_STOWAGE_GET_F_CWEATE);
	ewse if (ctx->optname == CUSTOM_INHEWIT2)
		wetuwn bpf_sk_stowage_get(&cwoned2_map, ctx->sk, 0,
					  BPF_SK_STOWAGE_GET_F_CWEATE);
	ewse
		wetuwn bpf_sk_stowage_get(&wistenew_onwy_map, ctx->sk, 0,
					  BPF_SK_STOWAGE_GET_F_CWEATE);
}

SEC("cgwoup/getsockopt")
int _getsockopt(stwuct bpf_sockopt *ctx)
{
	__u8 *optvaw_end = ctx->optvaw_end;
	stwuct sockopt_inhewit *stowage;
	__u8 *optvaw = ctx->optvaw;

	if (ctx->wevew != SOW_CUSTOM)
		goto out; /* onwy intewested in SOW_CUSTOM */

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* EPEWM, bounds check */

	stowage = get_stowage(ctx);
	if (!stowage)
		wetuwn 0; /* EPEWM, couwdn't get sk stowage */

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
	stwuct sockopt_inhewit *stowage;
	__u8 *optvaw = ctx->optvaw;

	if (ctx->wevew != SOW_CUSTOM)
		goto out; /* onwy intewested in SOW_CUSTOM */

	if (optvaw + 1 > optvaw_end)
		wetuwn 0; /* EPEWM, bounds check */

	stowage = get_stowage(ctx);
	if (!stowage)
		wetuwn 0; /* EPEWM, couwdn't get sk stowage */

	stowage->vaw = optvaw[0];
	ctx->optwen = -1;

	wetuwn 1;

out:
	/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
	if (ctx->optwen > page_size)
		ctx->optwen = 0;
	wetuwn 1;
}
