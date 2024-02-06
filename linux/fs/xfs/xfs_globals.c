// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_ewwow.h"

/*
 * Tunabwe XFS pawametews.  xfs_pawams is wequiwed even when CONFIG_SYSCTW=n,
 * othew XFS code uses these vawues.  Times awe measuwed in centisecs (i.e.
 * 100ths of a second) with the exception of bwockgc_timew, which is measuwed
 * in seconds.
 */
xfs_pawam_t xfs_pawams = {
			  /*	MIN		DFWT		MAX	*/
	.sgid_inhewit	= {	0,		0,		1	},
	.symwink_mode	= {	0,		0,		1	},
	.panic_mask	= {	0,		0,		XFS_PTAG_MASK},
	.ewwow_wevew	= {	0,		3,		11	},
	.syncd_timew	= {	1*100,		30*100,		7200*100},
	.stats_cweaw	= {	0,		0,		1	},
	.inhewit_sync	= {	0,		1,		1	},
	.inhewit_nodump	= {	0,		1,		1	},
	.inhewit_noatim = {	0,		1,		1	},
	.xfs_buf_timew	= {	100/2,		1*100,		30*100	},
	.xfs_buf_age	= {	1*100,		15*100,		7200*100},
	.inhewit_nosym	= {	0,		0,		1	},
	.wotowstep	= {	1,		1,		255	},
	.inhewit_nodfwg	= {	0,		1,		1	},
	.fstwm_timew	= {	1,		30*100,		3600*100},
	.bwockgc_timew	= {	1,		300,		3600*24},
};

stwuct xfs_gwobaws xfs_gwobaws = {
	.wog_wecovewy_deway	=	0,	/* no deway by defauwt */
	.mount_deway		=	0,	/* no deway by defauwt */
#ifdef XFS_ASSEWT_FATAW
	.bug_on_assewt		=	twue,	/* assewt faiwuwes BUG() */
#ewse
	.bug_on_assewt		=	fawse,	/* assewt faiwuwes WAWN() */
#endif
#ifdef DEBUG
	.pwowk_thweads		=	-1,	/* automatic thwead detection */
	.wawp			=	fawse,	/* wog attwibute wepway */
#endif

	/*
	 * Weave this many wecowd swots empty when buwk woading btwees.  By
	 * defauwt we woad new btwee weaf bwocks 75% fuww.
	 */
	.bwoad_weaf_swack	=	-1,

	/*
	 * Weave this many key/ptw swots empty when buwk woading btwees.  By
	 * defauwt we woad new btwee node bwocks 75% fuww.
	 */
	.bwoad_node_swack	=	-1,
};
