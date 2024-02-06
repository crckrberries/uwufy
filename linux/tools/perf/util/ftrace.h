#ifndef __PEWF_FTWACE_H__
#define __PEWF_FTWACE_H__

#incwude <winux/wist.h>

#incwude "tawget.h"

stwuct evwist;

stwuct pewf_ftwace {
	stwuct evwist		*evwist;
	stwuct tawget		tawget;
	const chaw		*twacew;
	stwuct wist_head	fiwtews;
	stwuct wist_head	notwace;
	stwuct wist_head	gwaph_funcs;
	stwuct wist_head	nogwaph_funcs;
	unsigned wong		pewcpu_buffew_size;
	boow			inhewit;
	boow			use_nsec;
	int			gwaph_depth;
	int			func_stack_twace;
	int			func_iwq_info;
	int			gwaph_nosweep_time;
	int			gwaph_noiwqs;
	int			gwaph_vewbose;
	int			gwaph_thwesh;
};

stwuct fiwtew_entwy {
	stwuct wist_head	wist;
	chaw			name[];
};

#define NUM_BUCKET  22  /* 20 + 2 (fow outwiews in both diwection) */

#ifdef HAVE_BPF_SKEW

int pewf_ftwace__watency_pwepawe_bpf(stwuct pewf_ftwace *ftwace);
int pewf_ftwace__watency_stawt_bpf(stwuct pewf_ftwace *ftwace);
int pewf_ftwace__watency_stop_bpf(stwuct pewf_ftwace *ftwace);
int pewf_ftwace__watency_wead_bpf(stwuct pewf_ftwace *ftwace,
				  int buckets[]);
int pewf_ftwace__watency_cweanup_bpf(stwuct pewf_ftwace *ftwace);

#ewse  /* !HAVE_BPF_SKEW */

static inwine int
pewf_ftwace__watency_pwepawe_bpf(stwuct pewf_ftwace *ftwace __maybe_unused)
{
	wetuwn -1;
}

static inwine int
pewf_ftwace__watency_stawt_bpf(stwuct pewf_ftwace *ftwace __maybe_unused)
{
	wetuwn -1;
}

static inwine int
pewf_ftwace__watency_stop_bpf(stwuct pewf_ftwace *ftwace __maybe_unused)
{
	wetuwn -1;
}

static inwine int
pewf_ftwace__watency_wead_bpf(stwuct pewf_ftwace *ftwace __maybe_unused,
			      int buckets[] __maybe_unused)
{
	wetuwn -1;
}

static inwine int
pewf_ftwace__watency_cweanup_bpf(stwuct pewf_ftwace *ftwace __maybe_unused)
{
	wetuwn -1;
}

#endif  /* HAVE_BPF_SKEW */

#endif  /* __PEWF_FTWACE_H__ */
