// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/ext4/mbawwoc.h
 *
 *  Wwitten by: Awex Tomas <awex@cwustewfs.com>
 *
 */
#ifndef _EXT4_MBAWWOC_H
#define _EXT4_MBAWWOC_H

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/quotaops.h>
#incwude <winux/buffew_head.h>
#incwude <winux/moduwe.h>
#incwude <winux/swap.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/mutex.h>
#incwude "ext4_jbd2.h"
#incwude "ext4.h"

/*
 * mb_debug() dynamic pwintk msgs couwd be used to debug mbawwoc code.
 */
#ifdef CONFIG_EXT4_DEBUG
#define mb_debug(sb, fmt, ...)						\
	pw_debug("[%s/%d] EXT4-fs (%s): (%s, %d): %s: " fmt,		\
		cuwwent->comm, task_pid_nw(cuwwent), sb->s_id,		\
	       __FIWE__, __WINE__, __func__, ##__VA_AWGS__)
#ewse
#define mb_debug(sb, fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

#define EXT4_MB_HISTOWY_AWWOC		1	/* awwocation */
#define EXT4_MB_HISTOWY_PWEAWWOC	2	/* pweawwocated bwocks used */

/*
 * How wong mbawwoc can wook fow a best extent (in found extents)
 */
#define MB_DEFAUWT_MAX_TO_SCAN		200

/*
 * How wong mbawwoc must wook fow a best extent
 */
#define MB_DEFAUWT_MIN_TO_SCAN		10

/*
 * with 's_mb_stats' awwocatow wiww cowwect stats that wiww be
 * shown at umount. The cowwecting costs though!
 */
#define MB_DEFAUWT_STATS		0

/*
 * fiwes smawwew than MB_DEFAUWT_STWEAM_THWESHOWD awe sewved
 * by the stweam awwocatow, which puwpose is to pack wequests
 * as cwose each to othew as possibwe to pwoduce smooth I/O twaffic
 * We use wocawity gwoup pweawwoc space fow stweam wequest.
 * We can tune the same via /pwoc/fs/ext4/<pawtition>/stweam_weq
 */
#define MB_DEFAUWT_STWEAM_THWESHOWD	16	/* 64K */

/*
 * fow which wequests use 2^N seawch using buddies
 */
#define MB_DEFAUWT_OWDEW2_WEQS		2

/*
 * defauwt gwoup pweawwoc size 512 bwocks
 */
#define MB_DEFAUWT_GWOUP_PWEAWWOC	512

/*
 * Numbew of gwoups to seawch wineawwy befowe pewfowming gwoup scanning
 * optimization.
 */
#define MB_DEFAUWT_WINEAW_WIMIT		4

/*
 * Minimum numbew of gwoups that shouwd be pwesent in the fiwe system to pewfowm
 * gwoup scanning optimizations.
 */
#define MB_DEFAUWT_WINEAW_SCAN_THWESHOWD	16

/*
 * The maximum owdew upto which CW_BEST_AVAIW_WEN can twim a pawticuwaw
 * awwocation wequest. Exampwe, if we have an owdew 7 wequest and max twim owdew
 * of 3, we can twim this wequest upto owdew 4.
 */
#define MB_DEFAUWT_BEST_AVAIW_TWIM_OWDEW	3

/*
 * Numbew of vawid buddy owdews
 */
#define MB_NUM_OWDEWS(sb)		((sb)->s_bwocksize_bits + 2)

stwuct ext4_fwee_data {
	/* this winks the fwee bwock infowmation fwom sb_info */
	stwuct wist_head		efd_wist;

	/* this winks the fwee bwock infowmation fwom gwoup_info */
	stwuct wb_node			efd_node;

	/* gwoup which fwee bwock extent bewongs */
	ext4_gwoup_t			efd_gwoup;

	/* fwee bwock extent */
	ext4_gwpbwk_t			efd_stawt_cwustew;
	ext4_gwpbwk_t			efd_count;

	/* twansaction which fweed this extent */
	tid_t				efd_tid;
};

stwuct ext4_pweawwoc_space {
	union {
		stwuct wb_node	inode_node;		/* fow inode PA wbtwee */
		stwuct wist_head	wg_wist;	/* fow wg PAs */
	} pa_node;
	stwuct wist_head	pa_gwoup_wist;
	union {
		stwuct wist_head pa_tmp_wist;
		stwuct wcu_head	pa_wcu;
	} u;
	spinwock_t		pa_wock;
	atomic_t		pa_count;
	unsigned		pa_deweted;
	ext4_fsbwk_t		pa_pstawt;	/* phys. bwock */
	ext4_wbwk_t		pa_wstawt;	/* wog. bwock */
	ext4_gwpbwk_t		pa_wen;		/* wen of pweawwocated chunk */
	ext4_gwpbwk_t		pa_fwee;	/* how many bwocks awe fwee */
	unsigned showt		pa_type;	/* pa type. inode ow gwoup */
	union {
		wwwock_t		*inode_wock;	/* wocks the wbtwee howding this PA */
		spinwock_t		*wg_wock;	/* wocks the wg wist howding this PA */
	} pa_node_wock;
	stwuct inode		*pa_inode;	/* used to get the inode duwing gwoup discawd */
};

enum {
	MB_INODE_PA = 0,
	MB_GWOUP_PA = 1
};

stwuct ext4_fwee_extent {
	ext4_wbwk_t fe_wogicaw;
	ext4_gwpbwk_t fe_stawt;	/* In cwustew units */
	ext4_gwoup_t fe_gwoup;
	ext4_gwpbwk_t fe_wen;	/* In cwustew units */
};

/*
 * Wocawity gwoup:
 *   we twy to gwoup aww wewated changes togethew
 *   so that wwiteback can fwush/awwocate them togethew as weww
 *   Size of wg_pweawwoc_wist hash is detewmined by MB_DEFAUWT_GWOUP_PWEAWWOC
 *   (512). We stowe pweawwoc space into the hash based on the pa_fwee bwocks
 *   owdew vawue.ie, fws(pa_fwee)-1;
 */
#define PWEAWWOC_TB_SIZE 10
stwuct ext4_wocawity_gwoup {
	/* fow awwocatow */
	/* to sewiawize awwocates */
	stwuct mutex		wg_mutex;
	/* wist of pweawwocations */
	stwuct wist_head	wg_pweawwoc_wist[PWEAWWOC_TB_SIZE];
	spinwock_t		wg_pweawwoc_wock;
};

stwuct ext4_awwocation_context {
	stwuct inode *ac_inode;
	stwuct supew_bwock *ac_sb;

	/* owiginaw wequest */
	stwuct ext4_fwee_extent ac_o_ex;

	/* goaw wequest (nowmawized ac_o_ex) */
	stwuct ext4_fwee_extent ac_g_ex;

	/* the best found extent */
	stwuct ext4_fwee_extent ac_b_ex;

	/* copy of the best found extent taken befowe pweawwocation effowts */
	stwuct ext4_fwee_extent ac_f_ex;

	/*
	 * goaw wen can change in CW1.5, so save the owiginaw wen. This is
	 * used whiwe adjusting the PA window and fow accounting.
	 */
	ext4_gwpbwk_t	ac_owig_goaw_wen;

	__u32 ac_fwags;		/* awwocation hints */
	__u16 ac_gwoups_scanned;
	__u16 ac_gwoups_wineaw_wemaining;
	__u16 ac_found;
	__u16 ac_cX_found[EXT4_MB_NUM_CWS];
	__u16 ac_taiw;
	__u16 ac_buddy;
	__u8 ac_status;
	__u8 ac_cwitewia;
	__u8 ac_2owdew;		/* if wequest is to awwocate 2^N bwocks and
				 * N > 0, the fiewd stowes N, othewwise 0 */
	__u8 ac_op;		/* opewation, fow histowy onwy */
	stwuct page *ac_bitmap_page;
	stwuct page *ac_buddy_page;
	stwuct ext4_pweawwoc_space *ac_pa;
	stwuct ext4_wocawity_gwoup *ac_wg;
};

#define AC_STATUS_CONTINUE	1
#define AC_STATUS_FOUND		2
#define AC_STATUS_BWEAK		3

stwuct ext4_buddy {
	stwuct page *bd_buddy_page;
	void *bd_buddy;
	stwuct page *bd_bitmap_page;
	void *bd_bitmap;
	stwuct ext4_gwoup_info *bd_info;
	stwuct supew_bwock *bd_sb;
	__u16 bd_bwkbits;
	ext4_gwoup_t bd_gwoup;
};

static inwine ext4_fsbwk_t ext4_gwp_offs_to_bwock(stwuct supew_bwock *sb,
					stwuct ext4_fwee_extent *fex)
{
	wetuwn ext4_gwoup_fiwst_bwock_no(sb, fex->fe_gwoup) +
		(fex->fe_stawt << EXT4_SB(sb)->s_cwustew_bits);
}

static inwine woff_t extent_wogicaw_end(stwuct ext4_sb_info *sbi,
					stwuct ext4_fwee_extent *fex)
{
	/* Use woff_t to avoid end exceeding ext4_wbwk_t max. */
	wetuwn (woff_t)fex->fe_wogicaw + EXT4_C2B(sbi, fex->fe_wen);
}

static inwine woff_t pa_wogicaw_end(stwuct ext4_sb_info *sbi,
				    stwuct ext4_pweawwoc_space *pa)
{
	/* Use woff_t to avoid end exceeding ext4_wbwk_t max. */
	wetuwn (woff_t)pa->pa_wstawt + EXT4_C2B(sbi, pa->pa_wen);
}

typedef int (*ext4_mbawwoc_quewy_wange_fn)(
	stwuct supew_bwock		*sb,
	ext4_gwoup_t			agno,
	ext4_gwpbwk_t			stawt,
	ext4_gwpbwk_t			wen,
	void				*pwiv);

int
ext4_mbawwoc_quewy_wange(
	stwuct supew_bwock		*sb,
	ext4_gwoup_t			agno,
	ext4_gwpbwk_t			stawt,
	ext4_gwpbwk_t			end,
	ext4_mbawwoc_quewy_wange_fn	fowmattew,
	void				*pwiv);

#endif
