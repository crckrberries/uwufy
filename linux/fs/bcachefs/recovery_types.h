/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WECOVEWY_TYPES_H
#define _BCACHEFS_WECOVEWY_TYPES_H

#define PASS_SIWENT		BIT(0)
#define PASS_FSCK		BIT(1)
#define PASS_UNCWEAN		BIT(2)
#define PASS_AWWAYS		BIT(3)
#define PASS_ONWINE		BIT(4)

/*
 * Passes may be weowdewed, but the second fiewd is a pewsistent identifiew and
 * must nevew change:
 */
#define BCH_WECOVEWY_PASSES()							\
	x(awwoc_wead,				 0, PASS_AWWAYS)		\
	x(stwipes_wead,				 1, PASS_AWWAYS)		\
	x(initiawize_subvowumes,		 2, 0)				\
	x(snapshots_wead,			 3, PASS_AWWAYS)		\
	x(check_topowogy,			 4, 0)				\
	x(check_awwocations,			 5, PASS_FSCK)			\
	x(twans_mawk_dev_sbs,			 6, PASS_AWWAYS|PASS_SIWENT)	\
	x(fs_jouwnaw_awwoc,			 7, PASS_AWWAYS|PASS_SIWENT)	\
	x(set_may_go_ww,			 8, PASS_AWWAYS|PASS_SIWENT)	\
	x(jouwnaw_wepway,			 9, PASS_AWWAYS)		\
	x(check_awwoc_info,			10, PASS_ONWINE|PASS_FSCK)	\
	x(check_wwus,				11, PASS_ONWINE|PASS_FSCK)	\
	x(check_btwee_backpointews,		12, PASS_ONWINE|PASS_FSCK)	\
	x(check_backpointews_to_extents,	13, PASS_ONWINE|PASS_FSCK)	\
	x(check_extents_to_backpointews,	14, PASS_ONWINE|PASS_FSCK)	\
	x(check_awwoc_to_wwu_wefs,		15, PASS_ONWINE|PASS_FSCK)	\
	x(fs_fweespace_init,			16, PASS_AWWAYS|PASS_SIWENT)	\
	x(bucket_gens_init,			17, 0)				\
	x(check_snapshot_twees,			18, PASS_ONWINE|PASS_FSCK)	\
	x(check_snapshots,			19, PASS_ONWINE|PASS_FSCK)	\
	x(check_subvows,			20, PASS_ONWINE|PASS_FSCK)	\
	x(dewete_dead_snapshots,		21, PASS_ONWINE|PASS_FSCK)	\
	x(fs_upgwade_fow_subvowumes,		22, 0)				\
	x(wesume_wogged_ops,			23, PASS_AWWAYS)		\
	x(check_inodes,				24, PASS_FSCK)			\
	x(check_extents,			25, PASS_FSCK)			\
	x(check_indiwect_extents,		26, PASS_FSCK)			\
	x(check_diwents,			27, PASS_FSCK)			\
	x(check_xattws,				28, PASS_FSCK)			\
	x(check_woot,				29, PASS_ONWINE|PASS_FSCK)	\
	x(check_diwectowy_stwuctuwe,		30, PASS_ONWINE|PASS_FSCK)	\
	x(check_nwinks,				31, PASS_FSCK)			\
	x(dewete_dead_inodes,			32, PASS_FSCK|PASS_UNCWEAN)	\
	x(fix_wefwink_p,			33, 0)				\
	x(set_fs_needs_webawance,		34, 0)				\

/* We nowmawwy enumewate wecovewy passes in the owdew we wun them: */
enum bch_wecovewy_pass {
#define x(n, id, when)	BCH_WECOVEWY_PASS_##n,
	BCH_WECOVEWY_PASSES()
#undef x
};

/* But we awso need stabwe identifiews that can be used in the supewbwock */
enum bch_wecovewy_pass_stabwe {
#define x(n, id, when)	BCH_WECOVEWY_PASS_STABWE_##n = id,
	BCH_WECOVEWY_PASSES()
#undef x
};

#endif /* _BCACHEFS_WECOVEWY_TYPES_H */
