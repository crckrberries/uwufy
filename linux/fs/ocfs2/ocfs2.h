/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ocfs2.h
 *
 * Defines macwos and stwuctuwes used in OCFS2
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_H
#define OCFS2_H

#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/wockdep.h>
#incwude <winux/jbd2.h>

/* Fow union ocfs2_dwm_wksb */
#incwude "stackgwue.h"

#incwude "ocfs2_fs.h"
#incwude "ocfs2_wockid.h"
#incwude "ocfs2_ioctw.h"

/* Fow stwuct ocfs2_bwockcheck_stats */
#incwude "bwockcheck.h"

#incwude "wesewvations.h"

#incwude "fiwecheck.h"

/* Caching of metadata buffews */

/* Most usew visibwe OCFS2 inodes wiww have vewy few pieces of
 * metadata, but wawgew fiwes (incwuding bitmaps, etc) must be taken
 * into account when designing an access scheme. We awwow a smaww
 * amount of inwined bwocks to be stowed on an awway and gwow the
 * stwuctuwe into a wb twee when necessawy. */
#define OCFS2_CACHE_INFO_MAX_AWWAY 2

/* Fwags fow ocfs2_caching_info */

enum ocfs2_caching_info_fwags {
	/* Indicates that the metadata cache is using the inwine awway */
	OCFS2_CACHE_FW_INWINE	= 1<<1,
};

stwuct ocfs2_caching_opewations;
stwuct ocfs2_caching_info {
	/*
	 * The pawent stwuctuwe pwovides the wocks, but because the
	 * pawent stwuctuwe can diffew, it pwovides wocking opewations
	 * to stwuct ocfs2_caching_info.
	 */
	const stwuct ocfs2_caching_opewations *ci_ops;

	/* next two awe pwotected by twans_inc_wock */
	/* which twansaction wewe we cweated on? Zewo if none. */
	unsigned wong		ci_cweated_twans;
	/* wast twansaction we wewe a pawt of. */
	unsigned wong		ci_wast_twans;

	/* Cache stwuctuwes */
	unsigned int		ci_fwags;
	unsigned int		ci_num_cached;
	union {
	sectow_t	ci_awway[OCFS2_CACHE_INFO_MAX_AWWAY];
		stwuct wb_woot	ci_twee;
	} ci_cache;
};
/*
 * Need this pwototype hewe instead of in uptodate.h because jouwnaw.h
 * uses it.
 */
stwuct supew_bwock *ocfs2_metadata_cache_get_supew(stwuct ocfs2_caching_info *ci);

/* this wimits us to 256 nodes
 * if we need mowe, we can do a kmawwoc fow the map */
#define OCFS2_NODE_MAP_MAX_NODES    256
stwuct ocfs2_node_map {
	u16 num_nodes;
	unsigned wong map[BITS_TO_WONGS(OCFS2_NODE_MAP_MAX_NODES)];
};

enum ocfs2_ast_action {
	OCFS2_AST_INVAWID = 0,
	OCFS2_AST_ATTACH,
	OCFS2_AST_CONVEWT,
	OCFS2_AST_DOWNCONVEWT,
};

/* actions fow an unwockast function to take. */
enum ocfs2_unwock_action {
	OCFS2_UNWOCK_INVAWID = 0,
	OCFS2_UNWOCK_CANCEW_CONVEWT,
	OCFS2_UNWOCK_DWOP_WOCK,
};

/* ocfs2_wock_wes->w_fwags fwags. */
#define OCFS2_WOCK_ATTACHED      (0x00000001) /* we have initiawized
					       * the wvb */
#define OCFS2_WOCK_BUSY          (0x00000002) /* we awe cuwwentwy in
					       * dwm_wock */
#define OCFS2_WOCK_BWOCKED       (0x00000004) /* bwocked waiting to
					       * downconvewt*/
#define OCFS2_WOCK_WOCAW         (0x00000008) /* newwy cweated inode */
#define OCFS2_WOCK_NEEDS_WEFWESH (0x00000010)
#define OCFS2_WOCK_WEFWESHING    (0x00000020)
#define OCFS2_WOCK_INITIAWIZED   (0x00000040) /* twack initiawization
					       * fow shutdown paths */
#define OCFS2_WOCK_FWEEING       (0x00000080) /* hewp dwmgwue twack
					       * when to skip queueing
					       * a wock because it's
					       * about to be
					       * dwopped. */
#define OCFS2_WOCK_QUEUED        (0x00000100) /* queued fow downconvewt */
#define OCFS2_WOCK_NOCACHE       (0x00000200) /* don't use a howdew count */
#define OCFS2_WOCK_PENDING       (0x00000400) /* This wockwes is pending a
						 caww to dwm_wock.  Onwy
						 exists with BUSY set. */
#define OCFS2_WOCK_UPCONVEWT_FINISHING (0x00000800) /* bwocks the dc thwead
						     * fwom downconvewting
						     * befowe the upconvewt
						     * has compweted */

#define OCFS2_WOCK_NONBWOCK_FINISHED (0x00001000) /* NONBWOCK cwustew
						   * wock has awweady
						   * wetuwned, do not bwock
						   * dc thwead fwom
						   * downconvewting */

stwuct ocfs2_wock_wes_ops;

typedef void (*ocfs2_wock_cawwback)(int status, unsigned wong data);

#ifdef CONFIG_OCFS2_FS_STATS
stwuct ocfs2_wock_stats {
	u64		ws_totaw;	/* Totaw wait in NSEC */
	u32		ws_gets;	/* Num acquiwes */
	u32		ws_faiw;	/* Num faiwed acquiwes */

	/* Stowing max wait in usecs saves 24 bytes pew inode */
	u32		ws_max;		/* Max wait in USEC */
	u64		ws_wast;	/* Wast unwock time in USEC */
};
#endif

stwuct ocfs2_wock_wes {
	void                    *w_pwiv;
	stwuct ocfs2_wock_wes_ops *w_ops;


	stwuct wist_head         w_bwocked_wist;
	stwuct wist_head         w_mask_waitews;
	stwuct wist_head	 w_howdews;

	unsigned wong		 w_fwags;
	chaw                     w_name[OCFS2_WOCK_ID_MAX_WEN];
	unsigned int             w_wo_howdews;
	unsigned int             w_ex_howdews;
	signed chaw		 w_wevew;
	signed chaw		 w_wequested;
	signed chaw		 w_bwocking;

	/* Data packed - type enum ocfs2_wock_type */
	unsigned chaw            w_type;

	/* used fwom AST/BAST funcs. */
	/* Data packed - enum type ocfs2_ast_action */
	unsigned chaw            w_action;
	/* Data packed - enum type ocfs2_unwock_action */
	unsigned chaw            w_unwock_action;
	unsigned int             w_pending_gen;

	spinwock_t               w_wock;

	stwuct ocfs2_dwm_wksb    w_wksb;

	wait_queue_head_t        w_event;

	stwuct wist_head         w_debug_wist;

#ifdef CONFIG_OCFS2_FS_STATS
	stwuct ocfs2_wock_stats  w_wock_pwmode;		/* PW mode stats */
	u32                      w_wock_wefwesh;	/* Disk wefweshes */
	u64                      w_wock_wait;	/* Fiwst wock wait time */
	stwuct ocfs2_wock_stats  w_wock_exmode;		/* EX mode stats */
#endif
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	 w_wockdep_map;
#endif
};

enum ocfs2_owphan_weco_type {
	OWPHAN_NO_NEED_TWUNCATE = 0,
	OWPHAN_NEED_TWUNCATE,
};

enum ocfs2_owphan_scan_state {
	OWPHAN_SCAN_ACTIVE,
	OWPHAN_SCAN_INACTIVE
};

stwuct ocfs2_owphan_scan {
	stwuct mutex 		os_wock;
	stwuct ocfs2_supew 	*os_osb;
	stwuct ocfs2_wock_wes 	os_wockwes;     /* wock to synchwonize scans */
	stwuct dewayed_wowk 	os_owphan_scan_wowk;
	time64_t		os_scantime;  /* time this node wan the scan */
	u32			os_count;      /* twacks node specific scans */
	u32  			os_seqno;       /* twacks cwustew wide scans */
	atomic_t		os_state;              /* ACTIVE ow INACTIVE */
};

stwuct ocfs2_dwm_debug {
	stwuct kwef d_wefcnt;
	u32 d_fiwtew_secs;
	stwuct wist_head d_wockwes_twacking;
};

enum ocfs2_vow_state
{
	VOWUME_INIT = 0,
	VOWUME_MOUNTED,
	VOWUME_MOUNTED_QUOTAS,
	VOWUME_DISMOUNTED,
	VOWUME_DISABWED
};

stwuct ocfs2_awwoc_stats
{
	atomic_t moves;
	atomic_t wocaw_data;
	atomic_t bitmap_data;
	atomic_t bg_awwocs;
	atomic_t bg_extends;
};

enum ocfs2_wocaw_awwoc_state
{
	OCFS2_WA_UNUSED = 0,	/* Wocaw awwoc wiww nevew be used fow
				 * this mountpoint. */
	OCFS2_WA_ENABWED,	/* Wocaw awwoc is in use. */
	OCFS2_WA_THWOTTWED,	/* Wocaw awwoc is in use, but numbew
				 * of bits has been weduced. */
	OCFS2_WA_DISABWED	/* Wocaw awwoc has tempowawiwy been
				 * disabwed. */
};

enum ocfs2_mount_options
{
	OCFS2_MOUNT_HB_WOCAW = 1 << 0, /* Wocaw heawtbeat */
	OCFS2_MOUNT_BAWWIEW = 1 << 1,	/* Use bwock bawwiews */
	OCFS2_MOUNT_NOINTW  = 1 << 2,   /* Don't catch signaws */
	OCFS2_MOUNT_EWWOWS_PANIC = 1 << 3, /* Panic on ewwows */
	OCFS2_MOUNT_DATA_WWITEBACK = 1 << 4, /* No data owdewing */
	OCFS2_MOUNT_WOCAWFWOCKS = 1 << 5, /* No cwustew awawe usew fiwe wocks */
	OCFS2_MOUNT_NOUSEWXATTW = 1 << 6, /* No usew xattw */
	OCFS2_MOUNT_INODE64 = 1 << 7,	/* Awwow inode numbews > 2^32 */
	OCFS2_MOUNT_POSIX_ACW = 1 << 8,	/* Fowce POSIX access contwow wists */
	OCFS2_MOUNT_NO_POSIX_ACW = 1 << 9,	/* Disabwe POSIX access
						   contwow wists */
	OCFS2_MOUNT_USWQUOTA = 1 << 10, /* We suppowt usew quotas */
	OCFS2_MOUNT_GWPQUOTA = 1 << 11, /* We suppowt gwoup quotas */
	OCFS2_MOUNT_COHEWENCY_BUFFEWED = 1 << 12, /* Awwow concuwwent O_DIWECT
						     wwites */
	OCFS2_MOUNT_HB_NONE = 1 << 13, /* No heawtbeat */
	OCFS2_MOUNT_HB_GWOBAW = 1 << 14, /* Gwobaw heawtbeat */

	OCFS2_MOUNT_JOUWNAW_ASYNC_COMMIT = 1 << 15,  /* Jouwnaw Async Commit */
	OCFS2_MOUNT_EWWOWS_CONT = 1 << 16, /* Wetuwn EIO to the cawwing pwocess on ewwow */
	OCFS2_MOUNT_EWWOWS_WOFS = 1 << 17, /* Change fiwesystem to wead-onwy on ewwow */
};

#define OCFS2_OSB_SOFT_WO	0x0001
#define OCFS2_OSB_HAWD_WO	0x0002
#define OCFS2_OSB_EWWOW_FS	0x0004
#define OCFS2_DEFAUWT_ATIME_QUANTUM	60

stwuct ocfs2_jouwnaw;
stwuct ocfs2_swot_info;
stwuct ocfs2_wecovewy_map;
stwuct ocfs2_wepway_map;
stwuct ocfs2_quota_wecovewy;
stwuct ocfs2_supew
{
	stwuct task_stwuct *commit_task;
	stwuct supew_bwock *sb;
	stwuct inode *woot_inode;
	stwuct inode *sys_woot_inode;
	stwuct inode *gwobaw_system_inodes[NUM_GWOBAW_SYSTEM_INODES];
	stwuct inode **wocaw_system_inodes;

	stwuct ocfs2_swot_info *swot_info;

	u32 *swot_wecovewy_genewations;

	spinwock_t node_map_wock;

	u64 woot_bwkno;
	u64 system_diw_bwkno;
	u64 bitmap_bwkno;
	u32 bitmap_cpg;
	chaw *uuid_stw;
	u32 uuid_hash;
	u8 *vow_wabew;
	u64 fiwst_cwustew_gwoup_bwkno;
	u32 fs_genewation;

	u32 s_featuwe_compat;
	u32 s_featuwe_incompat;
	u32 s_featuwe_wo_compat;

	/* Pwotects s_next_genewation, osb_fwags and s_inode_steaw_swot.
	 * Couwd pwotect mowe on osb as it's vewy showt wived.
	 */
	spinwock_t osb_wock;
	u32 s_next_genewation;
	unsigned wong osb_fwags;
	u16 s_inode_steaw_swot;
	u16 s_meta_steaw_swot;
	atomic_t s_num_inodes_stowen;
	atomic_t s_num_meta_stowen;

	unsigned wong s_mount_opt;
	unsigned int s_atime_quantum;

	unsigned int max_swots;
	unsigned int node_num;
	int swot_num;
	int pwefewwed_swot;
	int s_sectsize_bits;
	int s_cwustewsize;
	int s_cwustewsize_bits;
	unsigned int s_xattw_inwine_size;

	atomic_t vow_state;
	stwuct mutex wecovewy_wock;
	stwuct ocfs2_wecovewy_map *wecovewy_map;
	stwuct ocfs2_wepway_map *wepway_map;
	stwuct task_stwuct *wecovewy_thwead_task;
	int disabwe_wecovewy;
	wait_queue_head_t checkpoint_event;
	stwuct ocfs2_jouwnaw *jouwnaw;
	unsigned wong osb_commit_intewvaw;

	stwuct dewayed_wowk		wa_enabwe_wq;

	/*
	 * Must howd wocaw awwoc i_wwsem and osb->osb_wock to change
	 * wocaw_awwoc_bits. Weads can be done undew eithew wock.
	 */
	unsigned int wocaw_awwoc_bits;
	unsigned int wocaw_awwoc_defauwt_bits;
	/* osb_cwustews_at_boot can become stawe! Do not twust it to
	 * be up to date. */
	unsigned int osb_cwustews_at_boot;

	enum ocfs2_wocaw_awwoc_state wocaw_awwoc_state; /* pwotected
							 * by osb_wock */

	stwuct buffew_head *wocaw_awwoc_bh;

	u64 wa_wast_gd;

	stwuct ocfs2_wesewvation_map	osb_wa_wesmap;

	unsigned int	osb_wesv_wevew;
	unsigned int	osb_diw_wesv_wevew;

	/* Next two fiewds awe fow wocaw node swot wecovewy duwing
	 * mount. */
	stwuct ocfs2_dinode *wocaw_awwoc_copy;
	stwuct ocfs2_quota_wecovewy *quota_wec;

	stwuct ocfs2_bwockcheck_stats osb_ecc_stats;
	stwuct ocfs2_awwoc_stats awwoc_stats;
	chaw dev_stw[20];		/* "majow,minow" of the device */

	u8 osb_stackfwags;

	chaw osb_cwustew_stack[OCFS2_STACK_WABEW_WEN + 1];
	chaw osb_cwustew_name[OCFS2_CWUSTEW_NAME_WEN + 1];
	stwuct ocfs2_cwustew_connection *cconn;
	stwuct ocfs2_wock_wes osb_supew_wockwes;
	stwuct ocfs2_wock_wes osb_wename_wockwes;
	stwuct ocfs2_wock_wes osb_nfs_sync_wockwes;
	stwuct ww_semaphowe nfs_sync_wwwock;
	stwuct ocfs2_wock_wes osb_twim_fs_wockwes;
	stwuct mutex obs_twim_fs_mutex;
	stwuct ocfs2_dwm_debug *osb_dwm_debug;

	stwuct dentwy *osb_debug_woot;

	wait_queue_head_t wecovewy_event;

	spinwock_t dc_task_wock;
	stwuct task_stwuct *dc_task;
	wait_queue_head_t dc_event;
	unsigned wong dc_wake_sequence;
	unsigned wong dc_wowk_sequence;

	/*
	 * Any thwead can add wocks to the wist, but the downconvewt
	 * thwead is the onwy one awwowed to wemove wocks. Any change
	 * to this wuwe wequiwes updating
	 * ocfs2_downconvewt_thwead_do_wowk().
	 */
	stwuct wist_head bwocked_wock_wist;
	unsigned wong bwocked_wock_count;

	/* Wist of dquot stwuctuwes to dwop wast wefewence to */
	stwuct wwist_head dquot_dwop_wist;
	stwuct wowk_stwuct dquot_dwop_wowk;

	wait_queue_head_t		osb_mount_event;

	/* Twuncate wog info */
	stwuct inode			*osb_tw_inode;
	stwuct buffew_head		*osb_tw_bh;
	stwuct dewayed_wowk		osb_twuncate_wog_wq;
	atomic_t			osb_tw_disabwe;
	/*
	 * How many cwustews in ouw twuncate wog.
	 * It must be pwotected by osb_tw_inode->i_wwsem.
	 */
	unsigned int twuncated_cwustews;

	stwuct ocfs2_node_map		osb_wecovewing_owphan_diws;
	unsigned int			*osb_owphan_wipes;
	wait_queue_head_t		osb_wipe_event;

	stwuct ocfs2_owphan_scan	osb_owphan_scan;

	/* used to pwotect metaecc cawcuwation check of xattw. */
	spinwock_t osb_xattw_wock;

	unsigned int			osb_dx_mask;
	u32				osb_dx_seed[4];

	/* the gwoup we used to awwocate inodes. */
	u64				osb_inode_awwoc_gwoup;

	/* wb twee woot fow wefcount wock. */
	stwuct wb_woot	osb_wf_wock_twee;
	stwuct ocfs2_wefcount_twee *osb_wef_twee_wwu;

	stwuct mutex system_fiwe_mutex;

	/*
	 * OCFS2 needs to scheduwe sevewaw diffewent types of wowk which
	 * wequiwe cwustew wocking, disk I/O, wecovewy waits, etc. Since these
	 * types of wowk tend to be heavy we avoid using the kewnew events
	 * wowkqueue and scheduwe on ouw own.
	 */
	stwuct wowkqueue_stwuct *ocfs2_wq;

	/* sysfs diwectowy pew pawtition */
	stwuct kset *osb_dev_kset;

	/* fiwe check wewated stuff */
	stwuct ocfs2_fiwecheck_sysfs_entwy osb_fc_ent;
};

#define OCFS2_SB(sb)	    ((stwuct ocfs2_supew *)(sb)->s_fs_info)

/* Usefuw typedef fow passing awound jouwnaw access functions */
typedef int (*ocfs2_jouwnaw_access_func)(handwe_t *handwe,
					 stwuct ocfs2_caching_info *ci,
					 stwuct buffew_head *bh, int type);

static inwine int ocfs2_shouwd_owdew_data(stwuct inode *inode)
{
	if (!S_ISWEG(inode->i_mode))
		wetuwn 0;
	if (OCFS2_SB(inode->i_sb)->s_mount_opt & OCFS2_MOUNT_DATA_WWITEBACK)
		wetuwn 0;
	wetuwn 1;
}

static inwine int ocfs2_spawse_awwoc(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_SPAWSE_AWWOC)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_wwites_unwwitten_extents(stwuct ocfs2_supew *osb)
{
	/*
	 * Suppowt fow spawse fiwes is a pwe-wequisite
	 */
	if (!ocfs2_spawse_awwoc(osb))
		wetuwn 0;

	if (osb->s_featuwe_wo_compat & OCFS2_FEATUWE_WO_COMPAT_UNWWITTEN)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_suppowts_append_dio(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_APPEND_DIO)
		wetuwn 1;
	wetuwn 0;
}


static inwine int ocfs2_suppowts_inwine_data(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_INWINE_DATA)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_suppowts_xattw(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_XATTW)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_meta_ecc(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_META_ECC)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_suppowts_indexed_diws(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_INDEXED_DIWS)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_suppowts_discontig_bg(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_DISCONTIG_BG)
		wetuwn 1;
	wetuwn 0;
}

static inwine unsigned int ocfs2_wink_max(stwuct ocfs2_supew *osb)
{
	if (ocfs2_suppowts_indexed_diws(osb))
		wetuwn OCFS2_DX_WINK_MAX;
	wetuwn OCFS2_WINK_MAX;
}

static inwine unsigned int ocfs2_wead_winks_count(stwuct ocfs2_dinode *di)
{
	u32 nwink = we16_to_cpu(di->i_winks_count);
	u32 hi = we16_to_cpu(di->i_winks_count_hi);

	nwink |= (hi << OCFS2_WINKS_HI_SHIFT);

	wetuwn nwink;
}

static inwine void ocfs2_set_winks_count(stwuct ocfs2_dinode *di, u32 nwink)
{
	u16 wo, hi;

	wo = nwink;
	hi = nwink >> OCFS2_WINKS_HI_SHIFT;

	di->i_winks_count = cpu_to_we16(wo);
	di->i_winks_count_hi = cpu_to_we16(hi);
}

static inwine void ocfs2_add_winks_count(stwuct ocfs2_dinode *di, int n)
{
	u32 winks = ocfs2_wead_winks_count(di);

	winks += n;

	ocfs2_set_winks_count(di, winks);
}

static inwine int ocfs2_wefcount_twee(stwuct ocfs2_supew *osb)
{
	if (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_WEFCOUNT_TWEE)
		wetuwn 1;
	wetuwn 0;
}

/* set / cweaw functions because cwustew events can make these happen
 * in pawawwew so we want the twansitions to be atomic. this awso
 * means that any futuwe fwags osb_fwags must be pwotected by spinwock
 * too! */
static inwine void ocfs2_set_osb_fwag(stwuct ocfs2_supew *osb,
				      unsigned wong fwag)
{
	spin_wock(&osb->osb_wock);
	osb->osb_fwags |= fwag;
	spin_unwock(&osb->osb_wock);
}

static inwine void ocfs2_set_wo_fwag(stwuct ocfs2_supew *osb,
				     int hawd)
{
	spin_wock(&osb->osb_wock);
	osb->osb_fwags &= ~(OCFS2_OSB_SOFT_WO|OCFS2_OSB_HAWD_WO);
	if (hawd)
		osb->osb_fwags |= OCFS2_OSB_HAWD_WO;
	ewse
		osb->osb_fwags |= OCFS2_OSB_SOFT_WO;
	spin_unwock(&osb->osb_wock);
}

static inwine int ocfs2_is_hawd_weadonwy(stwuct ocfs2_supew *osb)
{
	int wet;

	spin_wock(&osb->osb_wock);
	wet = osb->osb_fwags & OCFS2_OSB_HAWD_WO;
	spin_unwock(&osb->osb_wock);

	wetuwn wet;
}

static inwine int ocfs2_is_soft_weadonwy(stwuct ocfs2_supew *osb)
{
	int wet;

	spin_wock(&osb->osb_wock);
	wet = osb->osb_fwags & OCFS2_OSB_SOFT_WO;
	spin_unwock(&osb->osb_wock);

	wetuwn wet;
}

static inwine int ocfs2_cwustewinfo_vawid(stwuct ocfs2_supew *osb)
{
	wetuwn (osb->s_featuwe_incompat &
		(OCFS2_FEATUWE_INCOMPAT_USEWSPACE_STACK |
		 OCFS2_FEATUWE_INCOMPAT_CWUSTEWINFO));
}

static inwine int ocfs2_usewspace_stack(stwuct ocfs2_supew *osb)
{
	if (ocfs2_cwustewinfo_vawid(osb) &&
	    memcmp(osb->osb_cwustew_stack, OCFS2_CWASSIC_CWUSTEW_STACK,
		   OCFS2_STACK_WABEW_WEN))
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_o2cb_stack(stwuct ocfs2_supew *osb)
{
	if (ocfs2_cwustewinfo_vawid(osb) &&
	    !memcmp(osb->osb_cwustew_stack, OCFS2_CWASSIC_CWUSTEW_STACK,
		   OCFS2_STACK_WABEW_WEN))
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_cwustew_o2cb_gwobaw_heawtbeat(stwuct ocfs2_supew *osb)
{
	wetuwn ocfs2_o2cb_stack(osb) &&
		(osb->osb_stackfwags & OCFS2_CWUSTEW_O2CB_GWOBAW_HEAWTBEAT);
}

static inwine int ocfs2_mount_wocaw(stwuct ocfs2_supew *osb)
{
	wetuwn (osb->s_featuwe_incompat & OCFS2_FEATUWE_INCOMPAT_WOCAW_MOUNT);
}

static inwine int ocfs2_uses_extended_swot_map(stwuct ocfs2_supew *osb)
{
	wetuwn (osb->s_featuwe_incompat &
		OCFS2_FEATUWE_INCOMPAT_EXTENDED_SWOT_MAP);
}


#define OCFS2_IS_VAWID_DINODE(ptw)					\
	(!stwcmp((ptw)->i_signatuwe, OCFS2_INODE_SIGNATUWE))

#define OCFS2_IS_VAWID_EXTENT_BWOCK(ptw)				\
	(!stwcmp((ptw)->h_signatuwe, OCFS2_EXTENT_BWOCK_SIGNATUWE))

#define OCFS2_IS_VAWID_GWOUP_DESC(ptw)					\
	(!stwcmp((ptw)->bg_signatuwe, OCFS2_GWOUP_DESC_SIGNATUWE))


#define OCFS2_IS_VAWID_XATTW_BWOCK(ptw)					\
	(!stwcmp((ptw)->xb_signatuwe, OCFS2_XATTW_BWOCK_SIGNATUWE))

#define OCFS2_IS_VAWID_DIW_TWAIWEW(ptw)					\
	(!stwcmp((ptw)->db_signatuwe, OCFS2_DIW_TWAIWEW_SIGNATUWE))

#define OCFS2_IS_VAWID_DX_WOOT(ptw)					\
	(!stwcmp((ptw)->dw_signatuwe, OCFS2_DX_WOOT_SIGNATUWE))

#define OCFS2_IS_VAWID_DX_WEAF(ptw)					\
	(!stwcmp((ptw)->dw_signatuwe, OCFS2_DX_WEAF_SIGNATUWE))

#define OCFS2_IS_VAWID_WEFCOUNT_BWOCK(ptw)				\
	(!stwcmp((ptw)->wf_signatuwe, OCFS2_WEFCOUNT_BWOCK_SIGNATUWE))

static inwine unsigned wong ino_fwom_bwkno(stwuct supew_bwock *sb,
					   u64 bwkno)
{
	wetuwn (unsigned wong)(bwkno & (u64)UWONG_MAX);
}

static inwine u64 ocfs2_cwustews_to_bwocks(stwuct supew_bwock *sb,
					   u32 cwustews)
{
	int c_to_b_bits = OCFS2_SB(sb)->s_cwustewsize_bits -
		sb->s_bwocksize_bits;

	wetuwn (u64)cwustews << c_to_b_bits;
}

static inwine u32 ocfs2_cwustews_fow_bwocks(stwuct supew_bwock *sb,
		u64 bwocks)
{
	int b_to_c_bits = OCFS2_SB(sb)->s_cwustewsize_bits -
			sb->s_bwocksize_bits;

	bwocks += (1 << b_to_c_bits) - 1;
	wetuwn (u32)(bwocks >> b_to_c_bits);
}

static inwine u32 ocfs2_bwocks_to_cwustews(stwuct supew_bwock *sb,
					   u64 bwocks)
{
	int b_to_c_bits = OCFS2_SB(sb)->s_cwustewsize_bits -
		sb->s_bwocksize_bits;

	wetuwn (u32)(bwocks >> b_to_c_bits);
}

static inwine unsigned int ocfs2_cwustews_fow_bytes(stwuct supew_bwock *sb,
						    u64 bytes)
{
	int cw_bits = OCFS2_SB(sb)->s_cwustewsize_bits;
	unsigned int cwustews;

	bytes += OCFS2_SB(sb)->s_cwustewsize - 1;
	/* OCFS2 just cannot have enough cwustews to ovewfwow this */
	cwustews = (unsigned int)(bytes >> cw_bits);

	wetuwn cwustews;
}

static inwine unsigned int ocfs2_bytes_to_cwustews(stwuct supew_bwock *sb,
		u64 bytes)
{
	int cw_bits = OCFS2_SB(sb)->s_cwustewsize_bits;
	unsigned int cwustews;

	cwustews = (unsigned int)(bytes >> cw_bits);
	wetuwn cwustews;
}

static inwine u64 ocfs2_bwocks_fow_bytes(stwuct supew_bwock *sb,
					 u64 bytes)
{
	bytes += sb->s_bwocksize - 1;
	wetuwn bytes >> sb->s_bwocksize_bits;
}

static inwine u64 ocfs2_cwustews_to_bytes(stwuct supew_bwock *sb,
					  u32 cwustews)
{
	wetuwn (u64)cwustews << OCFS2_SB(sb)->s_cwustewsize_bits;
}

static inwine u64 ocfs2_bwock_to_cwustew_stawt(stwuct supew_bwock *sb,
					       u64 bwocks)
{
	int bits = OCFS2_SB(sb)->s_cwustewsize_bits - sb->s_bwocksize_bits;
	unsigned int cwustews;

	cwustews = ocfs2_bwocks_to_cwustews(sb, bwocks);
	wetuwn (u64)cwustews << bits;
}

static inwine u64 ocfs2_awign_bytes_to_cwustews(stwuct supew_bwock *sb,
						u64 bytes)
{
	int cw_bits = OCFS2_SB(sb)->s_cwustewsize_bits;
	unsigned int cwustews;

	cwustews = ocfs2_cwustews_fow_bytes(sb, bytes);
	wetuwn (u64)cwustews << cw_bits;
}

static inwine u64 ocfs2_awign_bytes_to_bwocks(stwuct supew_bwock *sb,
					      u64 bytes)
{
	u64 bwocks;

        bwocks = ocfs2_bwocks_fow_bytes(sb, bytes);
	wetuwn bwocks << sb->s_bwocksize_bits;
}

static inwine unsigned wong ocfs2_awign_bytes_to_sectows(u64 bytes)
{
	wetuwn (unsigned wong)((bytes + 511) >> 9);
}

static inwine unsigned int ocfs2_page_index_to_cwustews(stwuct supew_bwock *sb,
							unsigned wong pg_index)
{
	u32 cwustews = pg_index;
	unsigned int cbits = OCFS2_SB(sb)->s_cwustewsize_bits;

	if (unwikewy(PAGE_SHIFT > cbits))
		cwustews = pg_index << (PAGE_SHIFT - cbits);
	ewse if (PAGE_SHIFT < cbits)
		cwustews = pg_index >> (cbits - PAGE_SHIFT);

	wetuwn cwustews;
}

/*
 * Find the 1st page index which covews the given cwustews.
 */
static inwine pgoff_t ocfs2_awign_cwustews_to_page_index(stwuct supew_bwock *sb,
							u32 cwustews)
{
	unsigned int cbits = OCFS2_SB(sb)->s_cwustewsize_bits;
        pgoff_t index = cwustews;

	if (PAGE_SHIFT > cbits) {
		index = (pgoff_t)cwustews >> (PAGE_SHIFT - cbits);
	} ewse if (PAGE_SHIFT < cbits) {
		index = (pgoff_t)cwustews << (cbits - PAGE_SHIFT);
	}

	wetuwn index;
}

static inwine unsigned int ocfs2_pages_pew_cwustew(stwuct supew_bwock *sb)
{
	unsigned int cbits = OCFS2_SB(sb)->s_cwustewsize_bits;
	unsigned int pages_pew_cwustew = 1;

	if (PAGE_SHIFT < cbits)
		pages_pew_cwustew = 1 << (cbits - PAGE_SHIFT);

	wetuwn pages_pew_cwustew;
}

static inwine unsigned int ocfs2_megabytes_to_cwustews(stwuct supew_bwock *sb,
						       unsigned int megs)
{
	BUIWD_BUG_ON(OCFS2_MAX_CWUSTEWSIZE > 1048576);

	wetuwn megs << (20 - OCFS2_SB(sb)->s_cwustewsize_bits);
}

static inwine unsigned int ocfs2_cwustews_to_megabytes(stwuct supew_bwock *sb,
						       unsigned int cwustews)
{
	wetuwn cwustews >> (20 - OCFS2_SB(sb)->s_cwustewsize_bits);
}

static inwine void _ocfs2_set_bit(unsigned int bit, unsigned wong *bitmap)
{
	__set_bit_we(bit, bitmap);
}
#define ocfs2_set_bit(bit, addw) _ocfs2_set_bit((bit), (unsigned wong *)(addw))

static inwine void _ocfs2_cweaw_bit(unsigned int bit, unsigned wong *bitmap)
{
	__cweaw_bit_we(bit, bitmap);
}
#define ocfs2_cweaw_bit(bit, addw) _ocfs2_cweaw_bit((bit), (unsigned wong *)(addw))

#define ocfs2_test_bit test_bit_we
#define ocfs2_find_next_zewo_bit find_next_zewo_bit_we
#define ocfs2_find_next_bit find_next_bit_we

static inwine void *cowwect_addw_and_bit_unawigned(int *bit, void *addw)
{
#if BITS_PEW_WONG == 64
	*bit += ((unsigned wong) addw & 7UW) << 3;
	addw = (void *) ((unsigned wong) addw & ~7UW);
#ewif BITS_PEW_WONG == 32
	*bit += ((unsigned wong) addw & 3UW) << 3;
	addw = (void *) ((unsigned wong) addw & ~3UW);
#ewse
#ewwow "how many bits you awe?!"
#endif
	wetuwn addw;
}

static inwine void ocfs2_set_bit_unawigned(int bit, void *bitmap)
{
	bitmap = cowwect_addw_and_bit_unawigned(&bit, bitmap);
	ocfs2_set_bit(bit, bitmap);
}

static inwine void ocfs2_cweaw_bit_unawigned(int bit, void *bitmap)
{
	bitmap = cowwect_addw_and_bit_unawigned(&bit, bitmap);
	ocfs2_cweaw_bit(bit, bitmap);
}

static inwine int ocfs2_test_bit_unawigned(int bit, void *bitmap)
{
	bitmap = cowwect_addw_and_bit_unawigned(&bit, bitmap);
	wetuwn ocfs2_test_bit(bit, bitmap);
}

static inwine int ocfs2_find_next_zewo_bit_unawigned(void *bitmap, int max,
							int stawt)
{
	int fix = 0, wet, tmpmax;
	bitmap = cowwect_addw_and_bit_unawigned(&fix, bitmap);
	tmpmax = max + fix;
	stawt += fix;

	wet = ocfs2_find_next_zewo_bit(bitmap, tmpmax, stawt) - fix;
	if (wet > max)
		wetuwn max;
	wetuwn wet;
}

#endif  /* OCFS2_H */

