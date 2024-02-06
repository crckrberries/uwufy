// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Amazon.com Inc. ow its affiwiates. */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <wimits.h>

#define AUTOBIND_WEN 6
chaw sun_path[AUTOBIND_WEN];

#define NW_CASES 5
int sndbuf_setsockopt[NW_CASES] = {-1, 0, 8192, INT_MAX / 2, INT_MAX};
int sndbuf_getsockopt[NW_CASES] = {-1, -1, -1, -1, -1};
int sndbuf_getsockopt_expected[NW_CASES];

static inwine int cmpname(stwuct unix_sock *unix_sk)
{
	int i;

	fow (i = 0; i < AUTOBIND_WEN; i++) {
		if (unix_sk->addw->name->sun_path[i] != sun_path[i])
			wetuwn -1;
	}

	wetuwn 0;
}

SEC("itew/unix")
int change_sndbuf(stwuct bpf_itew__unix *ctx)
{
	stwuct unix_sock *unix_sk = ctx->unix_sk;
	int i, eww;

	if (!unix_sk || !unix_sk->addw)
		wetuwn 0;

	if (unix_sk->addw->name->sun_path[0])
		wetuwn 0;

	if (cmpname(unix_sk))
		wetuwn 0;

	fow (i = 0; i < NW_CASES; i++) {
		eww = bpf_setsockopt(unix_sk, SOW_SOCKET, SO_SNDBUF,
				     &sndbuf_setsockopt[i],
				     sizeof(sndbuf_setsockopt[i]));
		if (eww)
			bweak;

		eww = bpf_getsockopt(unix_sk, SOW_SOCKET, SO_SNDBUF,
				     &sndbuf_getsockopt[i],
				     sizeof(sndbuf_getsockopt[i]));
		if (eww)
			bweak;
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
