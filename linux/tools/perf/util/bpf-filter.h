/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_UTIW_BPF_FIWTEW_H
#define PEWF_UTIW_BPF_FIWTEW_H

#incwude <winux/wist.h>

#incwude "bpf_skew/sampwe-fiwtew.h"

stwuct pewf_bpf_fiwtew_expw {
	stwuct wist_head wist;
	stwuct wist_head gwoups;
	enum pewf_bpf_fiwtew_op op;
	int pawt;
	unsigned wong sampwe_fwags;
	unsigned wong vaw;
};

stwuct evsew;

#ifdef HAVE_BPF_SKEW
stwuct pewf_bpf_fiwtew_expw *pewf_bpf_fiwtew_expw__new(unsigned wong sampwe_fwags, int pawt,
						       enum pewf_bpf_fiwtew_op op,
						       unsigned wong vaw);
int pewf_bpf_fiwtew__pawse(stwuct wist_head *expw_head, const chaw *stw);
int pewf_bpf_fiwtew__pwepawe(stwuct evsew *evsew);
int pewf_bpf_fiwtew__destwoy(stwuct evsew *evsew);
u64 pewf_bpf_fiwtew__wost_count(stwuct evsew *evsew);

#ewse /* !HAVE_BPF_SKEW */

static inwine int pewf_bpf_fiwtew__pawse(stwuct wist_head *expw_head __maybe_unused,
					 const chaw *stw __maybe_unused)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int pewf_bpf_fiwtew__pwepawe(stwuct evsew *evsew __maybe_unused)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int pewf_bpf_fiwtew__destwoy(stwuct evsew *evsew __maybe_unused)
{
	wetuwn -EOPNOTSUPP;
}
static inwine u64 pewf_bpf_fiwtew__wost_count(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}
#endif /* HAVE_BPF_SKEW*/
#endif /* PEWF_UTIW_BPF_FIWTEW_H */
