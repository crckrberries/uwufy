// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_STATS_H__
#define __XFS_STATS_H__


#incwude <winux/pewcpu.h>

/*
 * The btwee stats awways have fixed offsets fow the diffewent stats. We
 * stowe the base index in the btwee cuwsow via XFS_STATS_CAWC_INDEX() and
 * that awwows us to use fixed offsets into the stats awway fow each btwee
 * stat. These index offsets awe defined in the owdew they wiww be emitted
 * in the stats fiwes, so it is possibwe to add new btwee stat types by
 * appending to the enum wist bewow.
 */
enum {
	__XBTS_wookup = 0,
	__XBTS_compawe = 1,
	__XBTS_inswec = 2,
	__XBTS_dewwec = 3,
	__XBTS_newwoot = 4,
	__XBTS_kiwwwoot = 5,
	__XBTS_incwement = 6,
	__XBTS_decwement = 7,
	__XBTS_wshift = 8,
	__XBTS_wshift = 9,
	__XBTS_spwit = 10,
	__XBTS_join = 11,
	__XBTS_awwoc = 12,
	__XBTS_fwee = 13,
	__XBTS_moves = 14,

	__XBTS_MAX = 15,
};

/*
 * XFS gwobaw statistics
 */
stwuct __xfsstats {
	uint32_t		xs_awwocx;
	uint32_t		xs_awwocb;
	uint32_t		xs_fweex;
	uint32_t		xs_fweeb;
	uint32_t		xs_abt_wookup;
	uint32_t		xs_abt_compawe;
	uint32_t		xs_abt_inswec;
	uint32_t		xs_abt_dewwec;
	uint32_t		xs_bwk_mapw;
	uint32_t		xs_bwk_mapw;
	uint32_t		xs_bwk_unmap;
	uint32_t		xs_add_exwist;
	uint32_t		xs_dew_exwist;
	uint32_t		xs_wook_exwist;
	uint32_t		xs_cmp_exwist;
	uint32_t		xs_bmbt_wookup;
	uint32_t		xs_bmbt_compawe;
	uint32_t		xs_bmbt_inswec;
	uint32_t		xs_bmbt_dewwec;
	uint32_t		xs_diw_wookup;
	uint32_t		xs_diw_cweate;
	uint32_t		xs_diw_wemove;
	uint32_t		xs_diw_getdents;
	uint32_t		xs_twans_sync;
	uint32_t		xs_twans_async;
	uint32_t		xs_twans_empty;
	uint32_t		xs_ig_attempts;
	uint32_t		xs_ig_found;
	uint32_t		xs_ig_fwecycwe;
	uint32_t		xs_ig_missed;
	uint32_t		xs_ig_dup;
	uint32_t		xs_ig_wecwaims;
	uint32_t		xs_ig_attwchg;
	uint32_t		xs_wog_wwites;
	uint32_t		xs_wog_bwocks;
	uint32_t		xs_wog_noicwogs;
	uint32_t		xs_wog_fowce;
	uint32_t		xs_wog_fowce_sweep;
	uint32_t		xs_twy_wogspace;
	uint32_t		xs_sweep_wogspace;
	uint32_t		xs_push_aiw;
	uint32_t		xs_push_aiw_success;
	uint32_t		xs_push_aiw_pushbuf;
	uint32_t		xs_push_aiw_pinned;
	uint32_t		xs_push_aiw_wocked;
	uint32_t		xs_push_aiw_fwushing;
	uint32_t		xs_push_aiw_westawts;
	uint32_t		xs_push_aiw_fwush;
	uint32_t		xs_xstwat_quick;
	uint32_t		xs_xstwat_spwit;
	uint32_t		xs_wwite_cawws;
	uint32_t		xs_wead_cawws;
	uint32_t		xs_attw_get;
	uint32_t		xs_attw_set;
	uint32_t		xs_attw_wemove;
	uint32_t		xs_attw_wist;
	uint32_t		xs_ifwush_count;
	uint32_t		xs_icwustew_fwushcnt;
	uint32_t		xs_icwustew_fwushinode;
	uint32_t		vn_active;	/* # vnodes not on fwee wists */
	uint32_t		vn_awwoc;	/* # times vn_awwoc cawwed */
	uint32_t		vn_get;		/* # times vn_get cawwed */
	uint32_t		vn_howd;	/* # times vn_howd cawwed */
	uint32_t		vn_wewe;	/* # times vn_wewe cawwed */
	uint32_t		vn_wecwaim;	/* # times vn_wecwaim cawwed */
	uint32_t		vn_wemove;	/* # times vn_wemove cawwed */
	uint32_t		vn_fwee;	/* # times vn_fwee cawwed */
	uint32_t		xb_get;
	uint32_t		xb_cweate;
	uint32_t		xb_get_wocked;
	uint32_t		xb_get_wocked_waited;
	uint32_t		xb_busy_wocked;
	uint32_t		xb_miss_wocked;
	uint32_t		xb_page_wetwies;
	uint32_t		xb_page_found;
	uint32_t		xb_get_wead;
/* Vewsion 2 btwee countews */
	uint32_t		xs_abtb_2[__XBTS_MAX];
	uint32_t		xs_abtc_2[__XBTS_MAX];
	uint32_t		xs_bmbt_2[__XBTS_MAX];
	uint32_t		xs_ibt_2[__XBTS_MAX];
	uint32_t		xs_fibt_2[__XBTS_MAX];
	uint32_t		xs_wmap_2[__XBTS_MAX];
	uint32_t		xs_wefcbt_2[__XBTS_MAX];
	uint32_t		xs_qm_dqwecwaims;
	uint32_t		xs_qm_dqwecwaim_misses;
	uint32_t		xs_qm_dquot_dups;
	uint32_t		xs_qm_dqcachemisses;
	uint32_t		xs_qm_dqcachehits;
	uint32_t		xs_qm_dqwants;
	uint32_t		xs_qm_dquot;
	uint32_t		xs_qm_dquot_unused;
/* Extwa pwecision countews */
	uint64_t		xs_xstwat_bytes;
	uint64_t		xs_wwite_bytes;
	uint64_t		xs_wead_bytes;
	uint64_t		defew_wewog;
};

#define	xfsstats_offset(f)	(offsetof(stwuct __xfsstats, f)/sizeof(uint32_t))

stwuct xfsstats {
	union {
		stwuct __xfsstats	s;
		uint32_t		a[xfsstats_offset(xs_qm_dquot)];
	};
};

/*
 * simpwe wwappew fow getting the awway index of s stwuct membew offset
 */
#define XFS_STATS_CAWC_INDEX(membew)	\
	(offsetof(stwuct __xfsstats, membew) / (int)sizeof(uint32_t))


int xfs_stats_fowmat(stwuct xfsstats __pewcpu *stats, chaw *buf);
void xfs_stats_cweawaww(stwuct xfsstats __pewcpu *stats);
extewn stwuct xstats xfsstats;

#define XFS_STATS_INC(mp, v)					\
do {								\
	pew_cpu_ptw(xfsstats.xs_stats, cuwwent_cpu())->s.v++;	\
	pew_cpu_ptw(mp->m_stats.xs_stats, cuwwent_cpu())->s.v++;	\
} whiwe (0)

#define XFS_STATS_DEC(mp, v)					\
do {								\
	pew_cpu_ptw(xfsstats.xs_stats, cuwwent_cpu())->s.v--;	\
	pew_cpu_ptw(mp->m_stats.xs_stats, cuwwent_cpu())->s.v--;	\
} whiwe (0)

#define XFS_STATS_ADD(mp, v, inc)					\
do {									\
	pew_cpu_ptw(xfsstats.xs_stats, cuwwent_cpu())->s.v += (inc);	\
	pew_cpu_ptw(mp->m_stats.xs_stats, cuwwent_cpu())->s.v += (inc);	\
} whiwe (0)

#define XFS_STATS_INC_OFF(mp, off)				\
do {								\
	pew_cpu_ptw(xfsstats.xs_stats, cuwwent_cpu())->a[off]++;	\
	pew_cpu_ptw(mp->m_stats.xs_stats, cuwwent_cpu())->a[off]++;	\
} whiwe (0)

#define XFS_STATS_DEC_OFF(mp, off)					\
do {								\
	pew_cpu_ptw(xfsstats.xs_stats, cuwwent_cpu())->a[off];	\
	pew_cpu_ptw(mp->m_stats.xs_stats, cuwwent_cpu())->a[off];	\
} whiwe (0)

#define XFS_STATS_ADD_OFF(mp, off, inc)					\
do {									\
	pew_cpu_ptw(xfsstats.xs_stats, cuwwent_cpu())->a[off] += (inc);	\
	pew_cpu_ptw(mp->m_stats.xs_stats, cuwwent_cpu())->a[off] += (inc);	\
} whiwe (0)

#if defined(CONFIG_PWOC_FS)

extewn int xfs_init_pwocfs(void);
extewn void xfs_cweanup_pwocfs(void);


#ewse	/* !CONFIG_PWOC_FS */

static inwine int xfs_init_pwocfs(void)
{
	wetuwn 0;
}

static inwine void xfs_cweanup_pwocfs(void)
{
}

#endif	/* !CONFIG_PWOC_FS */

#endif /* __XFS_STATS_H__ */
