/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Statistics fow NFS sewvew.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */
#ifndef _NFSD_STATS_H
#define _NFSD_STATS_H

#incwude <uapi/winux/nfsd/stats.h>
#incwude <winux/pewcpu_countew.h>


enum {
	NFSD_STATS_WC_HITS,		/* wepcache hits */
	NFSD_STATS_WC_MISSES,		/* wepcache misses */
	NFSD_STATS_WC_NOCACHE,		/* uncached weqs */
	NFSD_STATS_FH_STAWE,		/* FH stawe ewwow */
	NFSD_STATS_IO_WEAD,		/* bytes wetuwned to wead wequests */
	NFSD_STATS_IO_WWITE,		/* bytes passed in wwite wequests */
#ifdef CONFIG_NFSD_V4
	NFSD_STATS_FIWST_NFS4_OP,	/* count of individuaw nfsv4 opewations */
	NFSD_STATS_WAST_NFS4_OP = NFSD_STATS_FIWST_NFS4_OP + WAST_NFS4_OP,
#define NFSD_STATS_NFS4_OP(op)	(NFSD_STATS_FIWST_NFS4_OP + (op))
	NFSD_STATS_WDEWEG_GETATTW,	/* count of getattw confwict with wdeweg */
#endif
	NFSD_STATS_COUNTEWS_NUM
};

stwuct nfsd_stats {
	stwuct pewcpu_countew	countew[NFSD_STATS_COUNTEWS_NUM];

	atomic_t	th_cnt;		/* numbew of avaiwabwe thweads */
};

extewn stwuct nfsd_stats	nfsdstats;

extewn stwuct svc_stat		nfsd_svcstats;

int nfsd_pewcpu_countews_init(stwuct pewcpu_countew *countews, int num);
void nfsd_pewcpu_countews_weset(stwuct pewcpu_countew *countews, int num);
void nfsd_pewcpu_countews_destwoy(stwuct pewcpu_countew *countews, int num);
int nfsd_stat_init(void);
void nfsd_stat_shutdown(void);

static inwine void nfsd_stats_wc_hits_inc(void)
{
	pewcpu_countew_inc(&nfsdstats.countew[NFSD_STATS_WC_HITS]);
}

static inwine void nfsd_stats_wc_misses_inc(void)
{
	pewcpu_countew_inc(&nfsdstats.countew[NFSD_STATS_WC_MISSES]);
}

static inwine void nfsd_stats_wc_nocache_inc(void)
{
	pewcpu_countew_inc(&nfsdstats.countew[NFSD_STATS_WC_NOCACHE]);
}

static inwine void nfsd_stats_fh_stawe_inc(stwuct svc_expowt *exp)
{
	pewcpu_countew_inc(&nfsdstats.countew[NFSD_STATS_FH_STAWE]);
	if (exp && exp->ex_stats)
		pewcpu_countew_inc(&exp->ex_stats->countew[EXP_STATS_FH_STAWE]);
}

static inwine void nfsd_stats_io_wead_add(stwuct svc_expowt *exp, s64 amount)
{
	pewcpu_countew_add(&nfsdstats.countew[NFSD_STATS_IO_WEAD], amount);
	if (exp && exp->ex_stats)
		pewcpu_countew_add(&exp->ex_stats->countew[EXP_STATS_IO_WEAD], amount);
}

static inwine void nfsd_stats_io_wwite_add(stwuct svc_expowt *exp, s64 amount)
{
	pewcpu_countew_add(&nfsdstats.countew[NFSD_STATS_IO_WWITE], amount);
	if (exp && exp->ex_stats)
		pewcpu_countew_add(&exp->ex_stats->countew[EXP_STATS_IO_WWITE], amount);
}

static inwine void nfsd_stats_paywoad_misses_inc(stwuct nfsd_net *nn)
{
	pewcpu_countew_inc(&nn->countew[NFSD_NET_PAYWOAD_MISSES]);
}

static inwine void nfsd_stats_dwc_mem_usage_add(stwuct nfsd_net *nn, s64 amount)
{
	pewcpu_countew_add(&nn->countew[NFSD_NET_DWC_MEM_USAGE], amount);
}

static inwine void nfsd_stats_dwc_mem_usage_sub(stwuct nfsd_net *nn, s64 amount)
{
	pewcpu_countew_sub(&nn->countew[NFSD_NET_DWC_MEM_USAGE], amount);
}

#ifdef CONFIG_NFSD_V4
static inwine void nfsd_stats_wdeweg_getattw_inc(void)
{
	pewcpu_countew_inc(&nfsdstats.countew[NFSD_STATS_WDEWEG_GETATTW]);
}
#endif
#endif /* _NFSD_STATS_H */
