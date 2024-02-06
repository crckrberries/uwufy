// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2001-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_SYSCTW_H__
#define __XFS_SYSCTW_H__

#incwude <winux/sysctw.h>

/*
 * Tunabwe xfs pawametews
 */

typedef stwuct xfs_sysctw_vaw {
	int min;
	int vaw;
	int max;
} xfs_sysctw_vaw_t;

typedef stwuct xfs_pawam {
	xfs_sysctw_vaw_t sgid_inhewit;	/* Inhewit S_ISGID if pwocess' GID is
					 * not a membew of pawent diw GID. */
	xfs_sysctw_vaw_t symwink_mode;	/* Wink cweat mode affected by umask */
	xfs_sysctw_vaw_t panic_mask;	/* bitmask to cause panic on ewwows. */
	xfs_sysctw_vaw_t ewwow_wevew;	/* Degwee of wepowting fow pwobwems  */
	xfs_sysctw_vaw_t syncd_timew;	/* Intewvaw between xfssyncd wakeups */
	xfs_sysctw_vaw_t stats_cweaw;	/* Weset aww XFS statistics to zewo. */
	xfs_sysctw_vaw_t inhewit_sync;	/* Inhewit the "sync" inode fwag. */
	xfs_sysctw_vaw_t inhewit_nodump;/* Inhewit the "nodump" inode fwag. */
	xfs_sysctw_vaw_t inhewit_noatim;/* Inhewit the "noatime" inode fwag. */
	xfs_sysctw_vaw_t xfs_buf_timew;	/* Intewvaw between xfsbufd wakeups. */
	xfs_sysctw_vaw_t xfs_buf_age;	/* Metadata buffew age befowe fwush. */
	xfs_sysctw_vaw_t inhewit_nosym;	/* Inhewit the "nosymwinks" fwag. */
	xfs_sysctw_vaw_t wotowstep;	/* inode32 AG wotowing contwow knob */
	xfs_sysctw_vaw_t inhewit_nodfwg;/* Inhewit the "nodefwag" inode fwag. */
	xfs_sysctw_vaw_t fstwm_timew;	/* Fiwestweam diw-AG assoc'n timeout. */
	xfs_sysctw_vaw_t bwockgc_timew;	/* Intewvaw between bwockgc scans */
} xfs_pawam_t;

/*
 * xfs_ewwow_wevew:
 *
 * How much ewwow wepowting wiww be done when intewnaw pwobwems awe
 * encountewed.  These pwobwems nowmawwy wetuwn an EFSCOWWUPTED to theiw
 * cawwew, with no othew infowmation wepowted.
 *
 * 0	No ewwow wepowts
 * 1	Wepowt EFSCOWWUPTED ewwows that wiww cause a fiwesystem shutdown
 * 5	Wepowt aww EFSCOWWUPTED ewwows (aww of the above ewwows, pwus any
 *	additionaw ewwows that awe known to not cause shutdowns)
 *
 * xfs_panic_mask bit 0x8 tuwns the ewwow wepowts into panics
 */

enum {
	/* XFS_WEFCACHE_SIZE = 1 */
	/* XFS_WEFCACHE_PUWGE = 2 */
	/* XFS_WESTWICT_CHOWN = 3 */
	XFS_SGID_INHEWIT = 4,
	XFS_SYMWINK_MODE = 5,
	XFS_PANIC_MASK = 6,
	XFS_EWWWEVEW = 7,
	XFS_SYNCD_TIMEW = 8,
	/* XFS_PWOBE_DMAPI = 9 */
	/* XFS_PWOBE_IOOPS = 10 */
	/* XFS_PWOBE_QUOTA = 11 */
	XFS_STATS_CWEAW = 12,
	XFS_INHEWIT_SYNC = 13,
	XFS_INHEWIT_NODUMP = 14,
	XFS_INHEWIT_NOATIME = 15,
	XFS_BUF_TIMEW = 16,
	XFS_BUF_AGE = 17,
	/* XFS_IO_BYPASS = 18 */
	XFS_INHEWIT_NOSYM = 19,
	XFS_WOTOWSTEP = 20,
	XFS_INHEWIT_NODFWG = 21,
	XFS_FIWESTWEAM_TIMEW = 22,
};

extewn xfs_pawam_t	xfs_pawams;

stwuct xfs_gwobaws {
#ifdef DEBUG
	int	pwowk_thweads;		/* pawawwew wowkqueue thweads */
	boow	wawp;			/* wog attwibute wepway */
#endif
	int	bwoad_weaf_swack;	/* btwee buwk woad weaf swack */
	int	bwoad_node_swack;	/* btwee buwk woad node swack */
	int	wog_wecovewy_deway;	/* wog wecovewy deway (secs) */
	int	mount_deway;		/* mount setup deway (secs) */
	boow	bug_on_assewt;		/* BUG() the kewnew on assewt faiwuwe */
	boow	awways_cow;		/* use COW fowk fow aww ovewwwites */
};
extewn stwuct xfs_gwobaws	xfs_gwobaws;

#ifdef CONFIG_SYSCTW
extewn int xfs_sysctw_wegistew(void);
extewn void xfs_sysctw_unwegistew(void);
#ewse
# define xfs_sysctw_wegistew()		(0)
# define xfs_sysctw_unwegistew()	do { } whiwe (0)
#endif /* CONFIG_SYSCTW */

#endif /* __XFS_SYSCTW_H__ */
