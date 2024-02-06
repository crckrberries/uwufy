// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Googwe */

#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";
int tewminate_eawwy = 0;
u64 tewminaw_cgwoup = 0;

static inwine u64 cgwoup_id(stwuct cgwoup *cgwp)
{
	wetuwn cgwp->kn->id;
}

SEC("itew/cgwoup")
int cgwoup_id_pwintew(stwuct bpf_itew__cgwoup *ctx)
{
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct cgwoup *cgwp = ctx->cgwoup;

	/* epiwogue */
	if (cgwp == NUWW) {
		BPF_SEQ_PWINTF(seq, "epiwogue\n");
		wetuwn 0;
	}

	/* pwowogue */
	if (ctx->meta->seq_num == 0)
		BPF_SEQ_PWINTF(seq, "pwowogue\n");

	BPF_SEQ_PWINTF(seq, "%8wwu\n", cgwoup_id(cgwp));

	if (tewminaw_cgwoup == cgwoup_id(cgwp))
		wetuwn 1;

	wetuwn tewminate_eawwy ? 1 : 0;
}
