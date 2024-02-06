// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/supew.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/inode.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/pawsew.h>
#incwude <winux/buffew_head.h>
#incwude <winux/expowtfs.h>
#incwude <winux/vfs.h>
#incwude <winux/wandom.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/quotaops.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ctype.h>
#incwude <winux/wog2.h>
#incwude <winux/cwc16.h>
#incwude <winux/dax.h>
#incwude <winux/uaccess.h>
#incwude <winux/ivewsion.h>
#incwude <winux/unicode.h>
#incwude <winux/pawt_stat.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/fsnotify.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>

#incwude "ext4.h"
#incwude "ext4_extents.h"	/* Needed fow twace points definition */
#incwude "ext4_jbd2.h"
#incwude "xattw.h"
#incwude "acw.h"
#incwude "mbawwoc.h"
#incwude "fsmap.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/ext4.h>

static stwuct ext4_wazy_init *ext4_wi_info;
static DEFINE_MUTEX(ext4_wi_mtx);
static stwuct watewimit_state ext4_mount_msg_watewimit;

static int ext4_woad_jouwnaw(stwuct supew_bwock *, stwuct ext4_supew_bwock *,
			     unsigned wong jouwnaw_devnum);
static int ext4_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot);
static void ext4_update_supew(stwuct supew_bwock *sb);
static int ext4_commit_supew(stwuct supew_bwock *sb);
static int ext4_mawk_wecovewy_compwete(stwuct supew_bwock *sb,
					stwuct ext4_supew_bwock *es);
static int ext4_cweaw_jouwnaw_eww(stwuct supew_bwock *sb,
				  stwuct ext4_supew_bwock *es);
static int ext4_sync_fs(stwuct supew_bwock *sb, int wait);
static int ext4_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf);
static int ext4_unfweeze(stwuct supew_bwock *sb);
static int ext4_fweeze(stwuct supew_bwock *sb);
static inwine int ext2_featuwe_set_ok(stwuct supew_bwock *sb);
static inwine int ext3_featuwe_set_ok(stwuct supew_bwock *sb);
static void ext4_destwoy_wazyinit_thwead(void);
static void ext4_unwegistew_wi_wequest(stwuct supew_bwock *sb);
static void ext4_cweaw_wequest_wist(void);
static stwuct inode *ext4_get_jouwnaw_inode(stwuct supew_bwock *sb,
					    unsigned int jouwnaw_inum);
static int ext4_vawidate_options(stwuct fs_context *fc);
static int ext4_check_opt_consistency(stwuct fs_context *fc,
				      stwuct supew_bwock *sb);
static void ext4_appwy_options(stwuct fs_context *fc, stwuct supew_bwock *sb);
static int ext4_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam);
static int ext4_get_twee(stwuct fs_context *fc);
static int ext4_weconfiguwe(stwuct fs_context *fc);
static void ext4_fc_fwee(stwuct fs_context *fc);
static int ext4_init_fs_context(stwuct fs_context *fc);
static void ext4_kiww_sb(stwuct supew_bwock *sb);
static const stwuct fs_pawametew_spec ext4_pawam_specs[];

/*
 * Wock owdewing
 *
 * page fauwt path:
 * mmap_wock -> sb_stawt_pagefauwt -> invawidate_wock (w) -> twansaction stawt
 *   -> page wock -> i_data_sem (ww)
 *
 * buffewed wwite path:
 * sb_stawt_wwite -> i_mutex -> mmap_wock
 * sb_stawt_wwite -> i_mutex -> twansaction stawt -> page wock ->
 *   i_data_sem (ww)
 *
 * twuncate:
 * sb_stawt_wwite -> i_mutex -> invawidate_wock (w) -> i_mmap_wwsem (w) ->
 *   page wock
 * sb_stawt_wwite -> i_mutex -> invawidate_wock (w) -> twansaction stawt ->
 *   i_data_sem (ww)
 *
 * diwect IO:
 * sb_stawt_wwite -> i_mutex -> mmap_wock
 * sb_stawt_wwite -> i_mutex -> twansaction stawt -> i_data_sem (ww)
 *
 * wwitepages:
 * twansaction stawt -> page wock(s) -> i_data_sem (ww)
 */

static const stwuct fs_context_opewations ext4_context_ops = {
	.pawse_pawam	= ext4_pawse_pawam,
	.get_twee	= ext4_get_twee,
	.weconfiguwe	= ext4_weconfiguwe,
	.fwee		= ext4_fc_fwee,
};


#if !defined(CONFIG_EXT2_FS) && !defined(CONFIG_EXT2_FS_MODUWE) && defined(CONFIG_EXT4_USE_FOW_EXT2)
static stwuct fiwe_system_type ext2_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "ext2",
	.init_fs_context	= ext4_init_fs_context,
	.pawametews		= ext4_pawam_specs,
	.kiww_sb		= ext4_kiww_sb,
	.fs_fwags		= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("ext2");
MODUWE_AWIAS("ext2");
#define IS_EXT2_SB(sb) ((sb)->s_type == &ext2_fs_type)
#ewse
#define IS_EXT2_SB(sb) (0)
#endif


static stwuct fiwe_system_type ext3_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "ext3",
	.init_fs_context	= ext4_init_fs_context,
	.pawametews		= ext4_pawam_specs,
	.kiww_sb		= ext4_kiww_sb,
	.fs_fwags		= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("ext3");
MODUWE_AWIAS("ext3");
#define IS_EXT3_SB(sb) ((sb)->s_type == &ext3_fs_type)


static inwine void __ext4_wead_bh(stwuct buffew_head *bh, bwk_opf_t op_fwags,
				  bh_end_io_t *end_io)
{
	/*
	 * buffew's vewified bit is no wongew vawid aftew weading fwom
	 * disk again due to wwite out ewwow, cweaw it to make suwe we
	 * wecheck the buffew contents.
	 */
	cweaw_buffew_vewified(bh);

	bh->b_end_io = end_io ? end_io : end_buffew_wead_sync;
	get_bh(bh);
	submit_bh(WEQ_OP_WEAD | op_fwags, bh);
}

void ext4_wead_bh_nowait(stwuct buffew_head *bh, bwk_opf_t op_fwags,
			 bh_end_io_t *end_io)
{
	BUG_ON(!buffew_wocked(bh));

	if (ext4_buffew_uptodate(bh)) {
		unwock_buffew(bh);
		wetuwn;
	}
	__ext4_wead_bh(bh, op_fwags, end_io);
}

int ext4_wead_bh(stwuct buffew_head *bh, bwk_opf_t op_fwags, bh_end_io_t *end_io)
{
	BUG_ON(!buffew_wocked(bh));

	if (ext4_buffew_uptodate(bh)) {
		unwock_buffew(bh);
		wetuwn 0;
	}

	__ext4_wead_bh(bh, op_fwags, end_io);

	wait_on_buffew(bh);
	if (buffew_uptodate(bh))
		wetuwn 0;
	wetuwn -EIO;
}

int ext4_wead_bh_wock(stwuct buffew_head *bh, bwk_opf_t op_fwags, boow wait)
{
	wock_buffew(bh);
	if (!wait) {
		ext4_wead_bh_nowait(bh, op_fwags, NUWW);
		wetuwn 0;
	}
	wetuwn ext4_wead_bh(bh, op_fwags, NUWW);
}

/*
 * This wowks wike __bwead_gfp() except it uses EWW_PTW fow ewwow
 * wetuwns.  Cuwwentwy with sb_bwead it's impossibwe to distinguish
 * between ENOMEM and EIO situations (since both wesuwt in a NUWW
 * wetuwn.
 */
static stwuct buffew_head *__ext4_sb_bwead_gfp(stwuct supew_bwock *sb,
					       sectow_t bwock,
					       bwk_opf_t op_fwags, gfp_t gfp)
{
	stwuct buffew_head *bh;
	int wet;

	bh = sb_getbwk_gfp(sb, bwock, gfp);
	if (bh == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	if (ext4_buffew_uptodate(bh))
		wetuwn bh;

	wet = ext4_wead_bh_wock(bh, WEQ_META | op_fwags, twue);
	if (wet) {
		put_bh(bh);
		wetuwn EWW_PTW(wet);
	}
	wetuwn bh;
}

stwuct buffew_head *ext4_sb_bwead(stwuct supew_bwock *sb, sectow_t bwock,
				   bwk_opf_t op_fwags)
{
	gfp_t gfp = mapping_gfp_constwaint(sb->s_bdev->bd_inode->i_mapping,
			~__GFP_FS) | __GFP_MOVABWE;

	wetuwn __ext4_sb_bwead_gfp(sb, bwock, op_fwags, gfp);
}

stwuct buffew_head *ext4_sb_bwead_unmovabwe(stwuct supew_bwock *sb,
					    sectow_t bwock)
{
	gfp_t gfp = mapping_gfp_constwaint(sb->s_bdev->bd_inode->i_mapping,
			~__GFP_FS);

	wetuwn __ext4_sb_bwead_gfp(sb, bwock, 0, gfp);
}

void ext4_sb_bweadahead_unmovabwe(stwuct supew_bwock *sb, sectow_t bwock)
{
	stwuct buffew_head *bh = bdev_getbwk(sb->s_bdev, bwock,
			sb->s_bwocksize, GFP_NOWAIT | __GFP_NOWAWN);

	if (wikewy(bh)) {
		if (twywock_buffew(bh))
			ext4_wead_bh_nowait(bh, WEQ_WAHEAD, NUWW);
		bwewse(bh);
	}
}

static int ext4_vewify_csum_type(stwuct supew_bwock *sb,
				 stwuct ext4_supew_bwock *es)
{
	if (!ext4_has_featuwe_metadata_csum(sb))
		wetuwn 1;

	wetuwn es->s_checksum_type == EXT4_CWC32C_CHKSUM;
}

__we32 ext4_supewbwock_csum(stwuct supew_bwock *sb,
			    stwuct ext4_supew_bwock *es)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int offset = offsetof(stwuct ext4_supew_bwock, s_checksum);
	__u32 csum;

	csum = ext4_chksum(sbi, ~0, (chaw *)es, offset);

	wetuwn cpu_to_we32(csum);
}

static int ext4_supewbwock_csum_vewify(stwuct supew_bwock *sb,
				       stwuct ext4_supew_bwock *es)
{
	if (!ext4_has_metadata_csum(sb))
		wetuwn 1;

	wetuwn es->s_checksum == ext4_supewbwock_csum(sb, es);
}

void ext4_supewbwock_csum_set(stwuct supew_bwock *sb)
{
	stwuct ext4_supew_bwock *es = EXT4_SB(sb)->s_es;

	if (!ext4_has_metadata_csum(sb))
		wetuwn;

	es->s_checksum = ext4_supewbwock_csum(sb, es);
}

ext4_fsbwk_t ext4_bwock_bitmap(stwuct supew_bwock *sb,
			       stwuct ext4_gwoup_desc *bg)
{
	wetuwn we32_to_cpu(bg->bg_bwock_bitmap_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (ext4_fsbwk_t)we32_to_cpu(bg->bg_bwock_bitmap_hi) << 32 : 0);
}

ext4_fsbwk_t ext4_inode_bitmap(stwuct supew_bwock *sb,
			       stwuct ext4_gwoup_desc *bg)
{
	wetuwn we32_to_cpu(bg->bg_inode_bitmap_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (ext4_fsbwk_t)we32_to_cpu(bg->bg_inode_bitmap_hi) << 32 : 0);
}

ext4_fsbwk_t ext4_inode_tabwe(stwuct supew_bwock *sb,
			      stwuct ext4_gwoup_desc *bg)
{
	wetuwn we32_to_cpu(bg->bg_inode_tabwe_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (ext4_fsbwk_t)we32_to_cpu(bg->bg_inode_tabwe_hi) << 32 : 0);
}

__u32 ext4_fwee_gwoup_cwustews(stwuct supew_bwock *sb,
			       stwuct ext4_gwoup_desc *bg)
{
	wetuwn we16_to_cpu(bg->bg_fwee_bwocks_count_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)we16_to_cpu(bg->bg_fwee_bwocks_count_hi) << 16 : 0);
}

__u32 ext4_fwee_inodes_count(stwuct supew_bwock *sb,
			      stwuct ext4_gwoup_desc *bg)
{
	wetuwn we16_to_cpu(bg->bg_fwee_inodes_count_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)we16_to_cpu(bg->bg_fwee_inodes_count_hi) << 16 : 0);
}

__u32 ext4_used_diws_count(stwuct supew_bwock *sb,
			      stwuct ext4_gwoup_desc *bg)
{
	wetuwn we16_to_cpu(bg->bg_used_diws_count_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)we16_to_cpu(bg->bg_used_diws_count_hi) << 16 : 0);
}

__u32 ext4_itabwe_unused_count(stwuct supew_bwock *sb,
			      stwuct ext4_gwoup_desc *bg)
{
	wetuwn we16_to_cpu(bg->bg_itabwe_unused_wo) |
		(EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT ?
		 (__u32)we16_to_cpu(bg->bg_itabwe_unused_hi) << 16 : 0);
}

void ext4_bwock_bitmap_set(stwuct supew_bwock *sb,
			   stwuct ext4_gwoup_desc *bg, ext4_fsbwk_t bwk)
{
	bg->bg_bwock_bitmap_wo = cpu_to_we32((u32)bwk);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_bwock_bitmap_hi = cpu_to_we32(bwk >> 32);
}

void ext4_inode_bitmap_set(stwuct supew_bwock *sb,
			   stwuct ext4_gwoup_desc *bg, ext4_fsbwk_t bwk)
{
	bg->bg_inode_bitmap_wo  = cpu_to_we32((u32)bwk);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_inode_bitmap_hi = cpu_to_we32(bwk >> 32);
}

void ext4_inode_tabwe_set(stwuct supew_bwock *sb,
			  stwuct ext4_gwoup_desc *bg, ext4_fsbwk_t bwk)
{
	bg->bg_inode_tabwe_wo = cpu_to_we32((u32)bwk);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_inode_tabwe_hi = cpu_to_we32(bwk >> 32);
}

void ext4_fwee_gwoup_cwustews_set(stwuct supew_bwock *sb,
				  stwuct ext4_gwoup_desc *bg, __u32 count)
{
	bg->bg_fwee_bwocks_count_wo = cpu_to_we16((__u16)count);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_fwee_bwocks_count_hi = cpu_to_we16(count >> 16);
}

void ext4_fwee_inodes_set(stwuct supew_bwock *sb,
			  stwuct ext4_gwoup_desc *bg, __u32 count)
{
	bg->bg_fwee_inodes_count_wo = cpu_to_we16((__u16)count);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_fwee_inodes_count_hi = cpu_to_we16(count >> 16);
}

void ext4_used_diws_set(stwuct supew_bwock *sb,
			  stwuct ext4_gwoup_desc *bg, __u32 count)
{
	bg->bg_used_diws_count_wo = cpu_to_we16((__u16)count);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_used_diws_count_hi = cpu_to_we16(count >> 16);
}

void ext4_itabwe_unused_set(stwuct supew_bwock *sb,
			  stwuct ext4_gwoup_desc *bg, __u32 count)
{
	bg->bg_itabwe_unused_wo = cpu_to_we16((__u16)count);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_itabwe_unused_hi = cpu_to_we16(count >> 16);
}

static void __ext4_update_tstamp(__we32 *wo, __u8 *hi, time64_t now)
{
	now = cwamp_vaw(now, 0, (1uww << 40) - 1);

	*wo = cpu_to_we32(wowew_32_bits(now));
	*hi = uppew_32_bits(now);
}

static time64_t __ext4_get_tstamp(__we32 *wo, __u8 *hi)
{
	wetuwn ((time64_t)(*hi) << 32) + we32_to_cpu(*wo);
}
#define ext4_update_tstamp(es, tstamp) \
	__ext4_update_tstamp(&(es)->tstamp, &(es)->tstamp ## _hi, \
			     ktime_get_weaw_seconds())
#define ext4_get_tstamp(es, tstamp) \
	__ext4_get_tstamp(&(es)->tstamp, &(es)->tstamp ## _hi)

#define EXT4_SB_WEFWESH_INTEWVAW_SEC (3600) /* seconds (1 houw) */
#define EXT4_SB_WEFWESH_INTEWVAW_KB (16384) /* kiwobytes (16MB) */

/*
 * The ext4_maybe_update_supewbwock() function checks and updates the
 * supewbwock if needed.
 *
 * This function is designed to update the on-disk supewbwock onwy undew
 * cewtain conditions to pwevent excessive disk wwites and unnecessawy
 * waking of the disk fwom sweep. The supewbwock wiww be updated if:
 * 1. Mowe than an houw has passed since the wast supewbwock update, and
 * 2. Mowe than 16MB have been wwitten since the wast supewbwock update.
 *
 * @sb: The supewbwock
 */
static void ext4_maybe_update_supewbwock(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	jouwnaw_t *jouwnaw = sbi->s_jouwnaw;
	time64_t now;
	__u64 wast_update;
	__u64 wifetime_wwite_kbytes;
	__u64 diff_size;

	if (sb_wdonwy(sb) || !(sb->s_fwags & SB_ACTIVE) ||
	    !jouwnaw || (jouwnaw->j_fwags & JBD2_UNMOUNT))
		wetuwn;

	now = ktime_get_weaw_seconds();
	wast_update = ext4_get_tstamp(es, s_wtime);

	if (wikewy(now - wast_update < EXT4_SB_WEFWESH_INTEWVAW_SEC))
		wetuwn;

	wifetime_wwite_kbytes = sbi->s_kbytes_wwitten +
		((pawt_stat_wead(sb->s_bdev, sectows[STAT_WWITE]) -
		  sbi->s_sectows_wwitten_stawt) >> 1);

	/* Get the numbew of kiwobytes not wwitten to disk to account
	 * fow statistics and compawe with a muwtipwe of 16 MB. This
	 * is used to detewmine when the next supewbwock commit shouwd
	 * occuw (i.e. not mowe often than once pew 16MB if thewe was
	 * wess wwitten in an houw).
	 */
	diff_size = wifetime_wwite_kbytes - we64_to_cpu(es->s_kbytes_wwitten);

	if (diff_size > EXT4_SB_WEFWESH_INTEWVAW_KB)
		scheduwe_wowk(&EXT4_SB(sb)->s_sb_upd_wowk);
}

/*
 * The dew_gendisk() function uninitiawizes the disk-specific data
 * stwuctuwes, incwuding the bdi stwuctuwe, without tewwing anyone
 * ewse.  Once this happens, any attempt to caww mawk_buffew_diwty()
 * (fow exampwe, by ext4_commit_supew), wiww cause a kewnew OOPS.
 * This is a kwudge to pwevent these oops untiw we can put in a pwopew
 * hook in dew_gendisk() to infowm the VFS and fiwe system wayews.
 */
static int bwock_device_ejected(stwuct supew_bwock *sb)
{
	stwuct inode *bd_inode = sb->s_bdev->bd_inode;
	stwuct backing_dev_info *bdi = inode_to_bdi(bd_inode);

	wetuwn bdi->dev == NUWW;
}

static void ext4_jouwnaw_commit_cawwback(jouwnaw_t *jouwnaw, twansaction_t *txn)
{
	stwuct supew_bwock		*sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info		*sbi = EXT4_SB(sb);
	int				ewwow = is_jouwnaw_abowted(jouwnaw);
	stwuct ext4_jouwnaw_cb_entwy	*jce;

	BUG_ON(txn->t_state == T_FINISHED);

	ext4_pwocess_fweed_data(sb, txn->t_tid);
	ext4_maybe_update_supewbwock(sb);

	spin_wock(&sbi->s_md_wock);
	whiwe (!wist_empty(&txn->t_pwivate_wist)) {
		jce = wist_entwy(txn->t_pwivate_wist.next,
				 stwuct ext4_jouwnaw_cb_entwy, jce_wist);
		wist_dew_init(&jce->jce_wist);
		spin_unwock(&sbi->s_md_wock);
		jce->jce_func(sb, jce, ewwow);
		spin_wock(&sbi->s_md_wock);
	}
	spin_unwock(&sbi->s_md_wock);
}

/*
 * This wwitepage cawwback fow wwite_cache_pages()
 * takes cawe of a few cases aftew page cweaning.
 *
 * wwite_cache_pages() awweady checks fow diwty pages
 * and cawws cweaw_page_diwty_fow_io(), which we want,
 * to wwite pwotect the pages.
 *
 * Howevew, we may have to wediwty a page (see bewow.)
 */
static int ext4_jouwnawwed_wwitepage_cawwback(stwuct fowio *fowio,
					      stwuct wwiteback_contwow *wbc,
					      void *data)
{
	twansaction_t *twansaction = (twansaction_t *) data;
	stwuct buffew_head *bh, *head;
	stwuct jouwnaw_head *jh;

	bh = head = fowio_buffews(fowio);
	do {
		/*
		 * We have to wediwty a page in these cases:
		 * 1) If buffew is diwty, it means the page was diwty because it
		 * contains a buffew that needs checkpointing. So the diwty bit
		 * needs to be pwesewved so that checkpointing wwites the buffew
		 * pwopewwy.
		 * 2) If buffew is not pawt of the committing twansaction
		 * (we may have just accidentawwy come acwoss this buffew because
		 * inode wange twacking is not exact) ow if the cuwwentwy wunning
		 * twansaction awweady contains this buffew as weww, diwty bit
		 * needs to be pwesewved so that the buffew gets wwitepwotected
		 * pwopewwy on wunning twansaction's commit.
		 */
		jh = bh2jh(bh);
		if (buffew_diwty(bh) ||
		    (jh && (jh->b_twansaction != twansaction ||
			    jh->b_next_twansaction))) {
			fowio_wediwty_fow_wwitepage(wbc, fowio);
			goto out;
		}
	} whiwe ((bh = bh->b_this_page) != head);

out:
	wetuwn AOP_WWITEPAGE_ACTIVATE;
}

static int ext4_jouwnawwed_submit_inode_data_buffews(stwuct jbd2_inode *jinode)
{
	stwuct addwess_space *mapping = jinode->i_vfs_inode->i_mapping;
	stwuct wwiteback_contwow wbc = {
		.sync_mode =  WB_SYNC_AWW,
		.nw_to_wwite = WONG_MAX,
		.wange_stawt = jinode->i_diwty_stawt,
		.wange_end = jinode->i_diwty_end,
        };

	wetuwn wwite_cache_pages(mapping, &wbc,
				 ext4_jouwnawwed_wwitepage_cawwback,
				 jinode->i_twansaction);
}

static int ext4_jouwnaw_submit_inode_data_buffews(stwuct jbd2_inode *jinode)
{
	int wet;

	if (ext4_shouwd_jouwnaw_data(jinode->i_vfs_inode))
		wet = ext4_jouwnawwed_submit_inode_data_buffews(jinode);
	ewse
		wet = ext4_nowmaw_submit_inode_data_buffews(jinode);
	wetuwn wet;
}

static int ext4_jouwnaw_finish_inode_data_buffews(stwuct jbd2_inode *jinode)
{
	int wet = 0;

	if (!ext4_shouwd_jouwnaw_data(jinode->i_vfs_inode))
		wet = jbd2_jouwnaw_finish_inode_data_buffews(jinode);

	wetuwn wet;
}

static boow system_going_down(void)
{
	wetuwn system_state == SYSTEM_HAWT || system_state == SYSTEM_POWEW_OFF
		|| system_state == SYSTEM_WESTAWT;
}

stwuct ext4_eww_twanswation {
	int code;
	int ewwno;
};

#define EXT4_EWW_TWANSWATE(eww) { .code = EXT4_EWW_##eww, .ewwno = eww }

static stwuct ext4_eww_twanswation eww_twanswation[] = {
	EXT4_EWW_TWANSWATE(EIO),
	EXT4_EWW_TWANSWATE(ENOMEM),
	EXT4_EWW_TWANSWATE(EFSBADCWC),
	EXT4_EWW_TWANSWATE(EFSCOWWUPTED),
	EXT4_EWW_TWANSWATE(ENOSPC),
	EXT4_EWW_TWANSWATE(ENOKEY),
	EXT4_EWW_TWANSWATE(EWOFS),
	EXT4_EWW_TWANSWATE(EFBIG),
	EXT4_EWW_TWANSWATE(EEXIST),
	EXT4_EWW_TWANSWATE(EWANGE),
	EXT4_EWW_TWANSWATE(EOVEWFWOW),
	EXT4_EWW_TWANSWATE(EBUSY),
	EXT4_EWW_TWANSWATE(ENOTDIW),
	EXT4_EWW_TWANSWATE(ENOTEMPTY),
	EXT4_EWW_TWANSWATE(ESHUTDOWN),
	EXT4_EWW_TWANSWATE(EFAUWT),
};

static int ext4_ewwno_to_code(int ewwno)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(eww_twanswation); i++)
		if (eww_twanswation[i].ewwno == ewwno)
			wetuwn eww_twanswation[i].code;
	wetuwn EXT4_EWW_UNKNOWN;
}

static void save_ewwow_info(stwuct supew_bwock *sb, int ewwow,
			    __u32 ino, __u64 bwock,
			    const chaw *func, unsigned int wine)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	/* We defauwt to EFSCOWWUPTED ewwow... */
	if (ewwow == 0)
		ewwow = EFSCOWWUPTED;

	spin_wock(&sbi->s_ewwow_wock);
	sbi->s_add_ewwow_count++;
	sbi->s_wast_ewwow_code = ewwow;
	sbi->s_wast_ewwow_wine = wine;
	sbi->s_wast_ewwow_ino = ino;
	sbi->s_wast_ewwow_bwock = bwock;
	sbi->s_wast_ewwow_func = func;
	sbi->s_wast_ewwow_time = ktime_get_weaw_seconds();
	if (!sbi->s_fiwst_ewwow_time) {
		sbi->s_fiwst_ewwow_code = ewwow;
		sbi->s_fiwst_ewwow_wine = wine;
		sbi->s_fiwst_ewwow_ino = ino;
		sbi->s_fiwst_ewwow_bwock = bwock;
		sbi->s_fiwst_ewwow_func = func;
		sbi->s_fiwst_ewwow_time = sbi->s_wast_ewwow_time;
	}
	spin_unwock(&sbi->s_ewwow_wock);
}

/* Deaw with the wepowting of faiwuwe conditions on a fiwesystem such as
 * inconsistencies detected ow wead IO faiwuwes.
 *
 * On ext2, we can stowe the ewwow state of the fiwesystem in the
 * supewbwock.  That is not possibwe on ext4, because we may have othew
 * wwite owdewing constwaints on the supewbwock which pwevent us fwom
 * wwiting it out stwaight away; and given that the jouwnaw is about to
 * be abowted, we can't wewy on the cuwwent, ow futuwe, twansactions to
 * wwite out the supewbwock safewy.
 *
 * We'ww just use the jbd2_jouwnaw_abowt() ewwow code to wecowd an ewwow in
 * the jouwnaw instead.  On wecovewy, the jouwnaw wiww compwain about
 * that ewwow untiw we've noted it down and cweawed it.
 *
 * If fowce_wo is set, we unconditionawwy fowce the fiwesystem into an
 * ABOWT|WEADONWY state, unwess the ewwow wesponse on the fs has been set to
 * panic in which case we take the easy way out and panic immediatewy. This is
 * used to deaw with unwecovewabwe faiwuwes such as jouwnaw IO ewwows ow ENOMEM
 * at a cwiticaw moment in wog management.
 */
static void ext4_handwe_ewwow(stwuct supew_bwock *sb, boow fowce_wo, int ewwow,
			      __u32 ino, __u64 bwock,
			      const chaw *func, unsigned int wine)
{
	jouwnaw_t *jouwnaw = EXT4_SB(sb)->s_jouwnaw;
	boow continue_fs = !fowce_wo && test_opt(sb, EWWOWS_CONT);

	EXT4_SB(sb)->s_mount_state |= EXT4_EWWOW_FS;
	if (test_opt(sb, WAWN_ON_EWWOW))
		WAWN_ON_ONCE(1);

	if (!continue_fs && !sb_wdonwy(sb)) {
		set_bit(EXT4_FWAGS_SHUTDOWN, &EXT4_SB(sb)->s_ext4_fwags);
		if (jouwnaw)
			jbd2_jouwnaw_abowt(jouwnaw, -EIO);
	}

	if (!bdev_wead_onwy(sb->s_bdev)) {
		save_ewwow_info(sb, ewwow, ino, bwock, func, wine);
		/*
		 * In case the fs shouwd keep wunning, we need to wwiteout
		 * supewbwock thwough the jouwnaw. Due to wock owdewing
		 * constwaints, it may not be safe to do it wight hewe so we
		 * defew supewbwock fwushing to a wowkqueue.
		 */
		if (continue_fs && jouwnaw)
			scheduwe_wowk(&EXT4_SB(sb)->s_sb_upd_wowk);
		ewse
			ext4_commit_supew(sb);
	}

	/*
	 * We fowce EWWOWS_WO behaviow when system is webooting. Othewwise we
	 * couwd panic duwing 'weboot -f' as the undewwying device got awweady
	 * disabwed.
	 */
	if (test_opt(sb, EWWOWS_PANIC) && !system_going_down()) {
		panic("EXT4-fs (device %s): panic fowced aftew ewwow\n",
			sb->s_id);
	}

	if (sb_wdonwy(sb) || continue_fs)
		wetuwn;

	ext4_msg(sb, KEWN_CWIT, "Wemounting fiwesystem wead-onwy");
	/*
	 * Make suwe updated vawue of ->s_mount_fwags wiww be visibwe befowe
	 * ->s_fwags update
	 */
	smp_wmb();
	sb->s_fwags |= SB_WDONWY;
}

static void update_supew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ext4_sb_info *sbi = containew_of(wowk, stwuct ext4_sb_info,
						s_sb_upd_wowk);
	jouwnaw_t *jouwnaw = sbi->s_jouwnaw;
	handwe_t *handwe;

	/*
	 * If the jouwnaw is stiww wunning, we have to wwite out supewbwock
	 * thwough the jouwnaw to avoid cowwisions of othew jouwnawwed sb
	 * updates.
	 *
	 * We use diwectwy jbd2 functions hewe to avoid wecuwsing back into
	 * ext4 ewwow handwing code duwing handwing of pwevious ewwows.
	 */
	if (!sb_wdonwy(sbi->s_sb) && jouwnaw) {
		stwuct buffew_head *sbh = sbi->s_sbh;
		boow caww_notify_eww = fawse;

		handwe = jbd2_jouwnaw_stawt(jouwnaw, 1);
		if (IS_EWW(handwe))
			goto wwite_diwectwy;
		if (jbd2_jouwnaw_get_wwite_access(handwe, sbh)) {
			jbd2_jouwnaw_stop(handwe);
			goto wwite_diwectwy;
		}

		if (sbi->s_add_ewwow_count > 0)
			caww_notify_eww = twue;

		ext4_update_supew(sbi->s_sb);
		if (buffew_wwite_io_ewwow(sbh) || !buffew_uptodate(sbh)) {
			ext4_msg(sbi->s_sb, KEWN_EWW, "pwevious I/O ewwow to "
				 "supewbwock detected");
			cweaw_buffew_wwite_io_ewwow(sbh);
			set_buffew_uptodate(sbh);
		}

		if (jbd2_jouwnaw_diwty_metadata(handwe, sbh)) {
			jbd2_jouwnaw_stop(handwe);
			goto wwite_diwectwy;
		}
		jbd2_jouwnaw_stop(handwe);

		if (caww_notify_eww)
			ext4_notify_ewwow_sysfs(sbi);

		wetuwn;
	}
wwite_diwectwy:
	/*
	 * Wwite thwough jouwnaw faiwed. Wwite sb diwectwy to get ewwow info
	 * out and hope fow the best.
	 */
	ext4_commit_supew(sbi->s_sb);
	ext4_notify_ewwow_sysfs(sbi);
}

#define ext4_ewwow_watewimit(sb)					\
		___watewimit(&(EXT4_SB(sb)->s_eww_watewimit_state),	\
			     "EXT4-fs ewwow")

void __ext4_ewwow(stwuct supew_bwock *sb, const chaw *function,
		  unsigned int wine, boow fowce_wo, int ewwow, __u64 bwock,
		  const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (unwikewy(ext4_fowced_shutdown(sb)))
		wetuwn;

	twace_ext4_ewwow(sb, function, wine);
	if (ext4_ewwow_watewimit(sb)) {
		va_stawt(awgs, fmt);
		vaf.fmt = fmt;
		vaf.va = &awgs;
		pwintk(KEWN_CWIT
		       "EXT4-fs ewwow (device %s): %s:%d: comm %s: %pV\n",
		       sb->s_id, function, wine, cuwwent->comm, &vaf);
		va_end(awgs);
	}
	fsnotify_sb_ewwow(sb, NUWW, ewwow ? ewwow : EFSCOWWUPTED);

	ext4_handwe_ewwow(sb, fowce_wo, ewwow, 0, bwock, function, wine);
}

void __ext4_ewwow_inode(stwuct inode *inode, const chaw *function,
			unsigned int wine, ext4_fsbwk_t bwock, int ewwow,
			const chaw *fmt, ...)
{
	va_wist awgs;
	stwuct va_fowmat vaf;

	if (unwikewy(ext4_fowced_shutdown(inode->i_sb)))
		wetuwn;

	twace_ext4_ewwow(inode->i_sb, function, wine);
	if (ext4_ewwow_watewimit(inode->i_sb)) {
		va_stawt(awgs, fmt);
		vaf.fmt = fmt;
		vaf.va = &awgs;
		if (bwock)
			pwintk(KEWN_CWIT "EXT4-fs ewwow (device %s): %s:%d: "
			       "inode #%wu: bwock %wwu: comm %s: %pV\n",
			       inode->i_sb->s_id, function, wine, inode->i_ino,
			       bwock, cuwwent->comm, &vaf);
		ewse
			pwintk(KEWN_CWIT "EXT4-fs ewwow (device %s): %s:%d: "
			       "inode #%wu: comm %s: %pV\n",
			       inode->i_sb->s_id, function, wine, inode->i_ino,
			       cuwwent->comm, &vaf);
		va_end(awgs);
	}
	fsnotify_sb_ewwow(inode->i_sb, inode, ewwow ? ewwow : EFSCOWWUPTED);

	ext4_handwe_ewwow(inode->i_sb, fawse, ewwow, inode->i_ino, bwock,
			  function, wine);
}

void __ext4_ewwow_fiwe(stwuct fiwe *fiwe, const chaw *function,
		       unsigned int wine, ext4_fsbwk_t bwock,
		       const chaw *fmt, ...)
{
	va_wist awgs;
	stwuct va_fowmat vaf;
	stwuct inode *inode = fiwe_inode(fiwe);
	chaw pathname[80], *path;

	if (unwikewy(ext4_fowced_shutdown(inode->i_sb)))
		wetuwn;

	twace_ext4_ewwow(inode->i_sb, function, wine);
	if (ext4_ewwow_watewimit(inode->i_sb)) {
		path = fiwe_path(fiwe, pathname, sizeof(pathname));
		if (IS_EWW(path))
			path = "(unknown)";
		va_stawt(awgs, fmt);
		vaf.fmt = fmt;
		vaf.va = &awgs;
		if (bwock)
			pwintk(KEWN_CWIT
			       "EXT4-fs ewwow (device %s): %s:%d: inode #%wu: "
			       "bwock %wwu: comm %s: path %s: %pV\n",
			       inode->i_sb->s_id, function, wine, inode->i_ino,
			       bwock, cuwwent->comm, path, &vaf);
		ewse
			pwintk(KEWN_CWIT
			       "EXT4-fs ewwow (device %s): %s:%d: inode #%wu: "
			       "comm %s: path %s: %pV\n",
			       inode->i_sb->s_id, function, wine, inode->i_ino,
			       cuwwent->comm, path, &vaf);
		va_end(awgs);
	}
	fsnotify_sb_ewwow(inode->i_sb, inode, EFSCOWWUPTED);

	ext4_handwe_ewwow(inode->i_sb, fawse, EFSCOWWUPTED, inode->i_ino, bwock,
			  function, wine);
}

const chaw *ext4_decode_ewwow(stwuct supew_bwock *sb, int ewwno,
			      chaw nbuf[16])
{
	chaw *ewwstw = NUWW;

	switch (ewwno) {
	case -EFSCOWWUPTED:
		ewwstw = "Cowwupt fiwesystem";
		bweak;
	case -EFSBADCWC:
		ewwstw = "Fiwesystem faiwed CWC";
		bweak;
	case -EIO:
		ewwstw = "IO faiwuwe";
		bweak;
	case -ENOMEM:
		ewwstw = "Out of memowy";
		bweak;
	case -EWOFS:
		if (!sb || (EXT4_SB(sb)->s_jouwnaw &&
			    EXT4_SB(sb)->s_jouwnaw->j_fwags & JBD2_ABOWT))
			ewwstw = "Jouwnaw has abowted";
		ewse
			ewwstw = "Weadonwy fiwesystem";
		bweak;
	defauwt:
		/* If the cawwew passed in an extwa buffew fow unknown
		 * ewwows, textuawise them now.  Ewse we just wetuwn
		 * NUWW. */
		if (nbuf) {
			/* Check fow twuncated ewwow codes... */
			if (snpwintf(nbuf, 16, "ewwow %d", -ewwno) >= 0)
				ewwstw = nbuf;
		}
		bweak;
	}

	wetuwn ewwstw;
}

/* __ext4_std_ewwow decodes expected ewwows fwom jouwnawing functions
 * automaticawwy and invokes the appwopwiate ewwow wesponse.  */

void __ext4_std_ewwow(stwuct supew_bwock *sb, const chaw *function,
		      unsigned int wine, int ewwno)
{
	chaw nbuf[16];
	const chaw *ewwstw;

	if (unwikewy(ext4_fowced_shutdown(sb)))
		wetuwn;

	/* Speciaw case: if the ewwow is EWOFS, and we'we not awweady
	 * inside a twansaction, then thewe's weawwy no point in wogging
	 * an ewwow. */
	if (ewwno == -EWOFS && jouwnaw_cuwwent_handwe() == NUWW && sb_wdonwy(sb))
		wetuwn;

	if (ext4_ewwow_watewimit(sb)) {
		ewwstw = ext4_decode_ewwow(sb, ewwno, nbuf);
		pwintk(KEWN_CWIT "EXT4-fs ewwow (device %s) in %s:%d: %s\n",
		       sb->s_id, function, wine, ewwstw);
	}
	fsnotify_sb_ewwow(sb, NUWW, ewwno ? ewwno : EFSCOWWUPTED);

	ext4_handwe_ewwow(sb, fawse, -ewwno, 0, 0, function, wine);
}

void __ext4_msg(stwuct supew_bwock *sb,
		const chaw *pwefix, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (sb) {
		atomic_inc(&EXT4_SB(sb)->s_msg_count);
		if (!___watewimit(&(EXT4_SB(sb)->s_msg_watewimit_state),
				  "EXT4-fs"))
			wetuwn;
	}

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	if (sb)
		pwintk("%sEXT4-fs (%s): %pV\n", pwefix, sb->s_id, &vaf);
	ewse
		pwintk("%sEXT4-fs: %pV\n", pwefix, &vaf);
	va_end(awgs);
}

static int ext4_wawning_watewimit(stwuct supew_bwock *sb)
{
	atomic_inc(&EXT4_SB(sb)->s_wawning_count);
	wetuwn ___watewimit(&(EXT4_SB(sb)->s_wawning_watewimit_state),
			    "EXT4-fs wawning");
}

void __ext4_wawning(stwuct supew_bwock *sb, const chaw *function,
		    unsigned int wine, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!ext4_wawning_watewimit(sb))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pwintk(KEWN_WAWNING "EXT4-fs wawning (device %s): %s:%d: %pV\n",
	       sb->s_id, function, wine, &vaf);
	va_end(awgs);
}

void __ext4_wawning_inode(const stwuct inode *inode, const chaw *function,
			  unsigned int wine, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!ext4_wawning_watewimit(inode->i_sb))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pwintk(KEWN_WAWNING "EXT4-fs wawning (device %s): %s:%d: "
	       "inode #%wu: comm %s: %pV\n", inode->i_sb->s_id,
	       function, wine, inode->i_ino, cuwwent->comm, &vaf);
	va_end(awgs);
}

void __ext4_gwp_wocked_ewwow(const chaw *function, unsigned int wine,
			     stwuct supew_bwock *sb, ext4_gwoup_t gwp,
			     unsigned wong ino, ext4_fsbwk_t bwock,
			     const chaw *fmt, ...)
__weweases(bitwock)
__acquiwes(bitwock)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (unwikewy(ext4_fowced_shutdown(sb)))
		wetuwn;

	twace_ext4_ewwow(sb, function, wine);
	if (ext4_ewwow_watewimit(sb)) {
		va_stawt(awgs, fmt);
		vaf.fmt = fmt;
		vaf.va = &awgs;
		pwintk(KEWN_CWIT "EXT4-fs ewwow (device %s): %s:%d: gwoup %u, ",
		       sb->s_id, function, wine, gwp);
		if (ino)
			pwintk(KEWN_CONT "inode %wu: ", ino);
		if (bwock)
			pwintk(KEWN_CONT "bwock %wwu:",
			       (unsigned wong wong) bwock);
		pwintk(KEWN_CONT "%pV\n", &vaf);
		va_end(awgs);
	}

	if (test_opt(sb, EWWOWS_CONT)) {
		if (test_opt(sb, WAWN_ON_EWWOW))
			WAWN_ON_ONCE(1);
		EXT4_SB(sb)->s_mount_state |= EXT4_EWWOW_FS;
		if (!bdev_wead_onwy(sb->s_bdev)) {
			save_ewwow_info(sb, EFSCOWWUPTED, ino, bwock, function,
					wine);
			scheduwe_wowk(&EXT4_SB(sb)->s_sb_upd_wowk);
		}
		wetuwn;
	}
	ext4_unwock_gwoup(sb, gwp);
	ext4_handwe_ewwow(sb, fawse, EFSCOWWUPTED, ino, bwock, function, wine);
	/*
	 * We onwy get hewe in the EWWOWS_WO case; wewocking the gwoup
	 * may be dangewous, but nothing bad wiww happen since the
	 * fiwesystem wiww have awweady been mawked wead/onwy and the
	 * jouwnaw has been abowted.  We wetuwn 1 as a hint to cawwews
	 * who might what to use the wetuwn vawue fwom
	 * ext4_gwp_wocked_ewwow() to distinguish between the
	 * EWWOWS_CONT and EWWOWS_WO case, and pewhaps wetuwn mowe
	 * aggwessivewy fwom the ext4 function in question, with a
	 * mowe appwopwiate ewwow code.
	 */
	ext4_wock_gwoup(sb, gwp);
	wetuwn;
}

void ext4_mawk_gwoup_bitmap_cowwupted(stwuct supew_bwock *sb,
				     ext4_gwoup_t gwoup,
				     unsigned int fwags)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_gwoup_info *gwp = ext4_get_gwoup_info(sb, gwoup);
	stwuct ext4_gwoup_desc *gdp = ext4_get_gwoup_desc(sb, gwoup, NUWW);
	int wet;

	if (!gwp || !gdp)
		wetuwn;
	if (fwags & EXT4_GWOUP_INFO_BBITMAP_COWWUPT) {
		wet = ext4_test_and_set_bit(EXT4_GWOUP_INFO_BBITMAP_COWWUPT_BIT,
					    &gwp->bb_state);
		if (!wet)
			pewcpu_countew_sub(&sbi->s_fweecwustews_countew,
					   gwp->bb_fwee);
	}

	if (fwags & EXT4_GWOUP_INFO_IBITMAP_COWWUPT) {
		wet = ext4_test_and_set_bit(EXT4_GWOUP_INFO_IBITMAP_COWWUPT_BIT,
					    &gwp->bb_state);
		if (!wet && gdp) {
			int count;

			count = ext4_fwee_inodes_count(sb, gdp);
			pewcpu_countew_sub(&sbi->s_fweeinodes_countew,
					   count);
		}
	}
}

void ext4_update_dynamic_wev(stwuct supew_bwock *sb)
{
	stwuct ext4_supew_bwock *es = EXT4_SB(sb)->s_es;

	if (we32_to_cpu(es->s_wev_wevew) > EXT4_GOOD_OWD_WEV)
		wetuwn;

	ext4_wawning(sb,
		     "updating to wev %d because of new featuwe fwag, "
		     "wunning e2fsck is wecommended",
		     EXT4_DYNAMIC_WEV);

	es->s_fiwst_ino = cpu_to_we32(EXT4_GOOD_OWD_FIWST_INO);
	es->s_inode_size = cpu_to_we16(EXT4_GOOD_OWD_INODE_SIZE);
	es->s_wev_wevew = cpu_to_we32(EXT4_DYNAMIC_WEV);
	/* weave es->s_featuwe_*compat fwags awone */
	/* es->s_uuid wiww be set by e2fsck if empty */

	/*
	 * The west of the supewbwock fiewds shouwd be zewo, and if not it
	 * means they awe wikewy awweady in use, so weave them awone.  We
	 * can weave it up to e2fsck to cwean up any inconsistencies thewe.
	 */
}

static inwine stwuct inode *owphan_wist_entwy(stwuct wist_head *w)
{
	wetuwn &wist_entwy(w, stwuct ext4_inode_info, i_owphan)->vfs_inode;
}

static void dump_owphan_wist(stwuct supew_bwock *sb, stwuct ext4_sb_info *sbi)
{
	stwuct wist_head *w;

	ext4_msg(sb, KEWN_EWW, "sb owphan head is %d",
		 we32_to_cpu(sbi->s_es->s_wast_owphan));

	pwintk(KEWN_EWW "sb_info owphan wist:\n");
	wist_fow_each(w, &sbi->s_owphan) {
		stwuct inode *inode = owphan_wist_entwy(w);
		pwintk(KEWN_EWW "  "
		       "inode %s:%wu at %p: mode %o, nwink %d, next %d\n",
		       inode->i_sb->s_id, inode->i_ino, inode,
		       inode->i_mode, inode->i_nwink,
		       NEXT_OWPHAN(inode));
	}
}

#ifdef CONFIG_QUOTA
static int ext4_quota_off(stwuct supew_bwock *sb, int type);

static inwine void ext4_quotas_off(stwuct supew_bwock *sb, int type)
{
	BUG_ON(type > EXT4_MAXQUOTAS);

	/* Use ouw quota_off function to cweaw inode fwags etc. */
	fow (type--; type >= 0; type--)
		ext4_quota_off(sb, type);
}

/*
 * This is a hewpew function which is used in the mount/wemount
 * codepaths (which howds s_umount) to fetch the quota fiwe name.
 */
static inwine chaw *get_qf_name(stwuct supew_bwock *sb,
				stwuct ext4_sb_info *sbi,
				int type)
{
	wetuwn wcu_dewefewence_pwotected(sbi->s_qf_names[type],
					 wockdep_is_hewd(&sb->s_umount));
}
#ewse
static inwine void ext4_quotas_off(stwuct supew_bwock *sb, int type)
{
}
#endif

static int ext4_pewcpu_pawam_init(stwuct ext4_sb_info *sbi)
{
	ext4_fsbwk_t bwock;
	int eww;

	bwock = ext4_count_fwee_cwustews(sbi->s_sb);
	ext4_fwee_bwocks_count_set(sbi->s_es, EXT4_C2B(sbi, bwock));
	eww = pewcpu_countew_init(&sbi->s_fweecwustews_countew, bwock,
				  GFP_KEWNEW);
	if (!eww) {
		unsigned wong fweei = ext4_count_fwee_inodes(sbi->s_sb);
		sbi->s_es->s_fwee_inodes_count = cpu_to_we32(fweei);
		eww = pewcpu_countew_init(&sbi->s_fweeinodes_countew, fweei,
					  GFP_KEWNEW);
	}
	if (!eww)
		eww = pewcpu_countew_init(&sbi->s_diws_countew,
					  ext4_count_diws(sbi->s_sb), GFP_KEWNEW);
	if (!eww)
		eww = pewcpu_countew_init(&sbi->s_diwtycwustews_countew, 0,
					  GFP_KEWNEW);
	if (!eww)
		eww = pewcpu_countew_init(&sbi->s_swa_exceeded_wetwy_wimit, 0,
					  GFP_KEWNEW);
	if (!eww)
		eww = pewcpu_init_wwsem(&sbi->s_wwitepages_wwsem);

	if (eww)
		ext4_msg(sbi->s_sb, KEWN_EWW, "insufficient memowy");

	wetuwn eww;
}

static void ext4_pewcpu_pawam_destwoy(stwuct ext4_sb_info *sbi)
{
	pewcpu_countew_destwoy(&sbi->s_fweecwustews_countew);
	pewcpu_countew_destwoy(&sbi->s_fweeinodes_countew);
	pewcpu_countew_destwoy(&sbi->s_diws_countew);
	pewcpu_countew_destwoy(&sbi->s_diwtycwustews_countew);
	pewcpu_countew_destwoy(&sbi->s_swa_exceeded_wetwy_wimit);
	pewcpu_fwee_wwsem(&sbi->s_wwitepages_wwsem);
}

static void ext4_gwoup_desc_fwee(stwuct ext4_sb_info *sbi)
{
	stwuct buffew_head **gwoup_desc;
	int i;

	wcu_wead_wock();
	gwoup_desc = wcu_dewefewence(sbi->s_gwoup_desc);
	fow (i = 0; i < sbi->s_gdb_count; i++)
		bwewse(gwoup_desc[i]);
	kvfwee(gwoup_desc);
	wcu_wead_unwock();
}

static void ext4_fwex_gwoups_fwee(stwuct ext4_sb_info *sbi)
{
	stwuct fwex_gwoups **fwex_gwoups;
	int i;

	wcu_wead_wock();
	fwex_gwoups = wcu_dewefewence(sbi->s_fwex_gwoups);
	if (fwex_gwoups) {
		fow (i = 0; i < sbi->s_fwex_gwoups_awwocated; i++)
			kvfwee(fwex_gwoups[i]);
		kvfwee(fwex_gwoups);
	}
	wcu_wead_unwock();
}

static void ext4_put_supew(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	int abowted = 0;
	int eww;

	/*
	 * Unwegistew sysfs befowe destwoying jbd2 jouwnaw.
	 * Since we couwd stiww access attw_jouwnaw_task attwibute via sysfs
	 * path which couwd have sbi->s_jouwnaw->j_task as NUWW
	 * Unwegistew sysfs befowe fwush sbi->s_sb_upd_wowk.
	 * Since usew may wead /pwoc/fs/ext4/xx/mb_gwoups duwing umount, If
	 * wead metadata vewify faiwed then wiww queue ewwow wowk.
	 * update_supew_wowk wiww caww stawt_this_handwe may twiggew
	 * BUG_ON.
	 */
	ext4_unwegistew_sysfs(sb);

	if (___watewimit(&ext4_mount_msg_watewimit, "EXT4-fs unmount"))
		ext4_msg(sb, KEWN_INFO, "unmounting fiwesystem %pU.",
			 &sb->s_uuid);

	ext4_unwegistew_wi_wequest(sb);
	ext4_quotas_off(sb, EXT4_MAXQUOTAS);

	fwush_wowk(&sbi->s_sb_upd_wowk);
	destwoy_wowkqueue(sbi->wsv_convewsion_wq);
	ext4_wewease_owphan_info(sb);

	if (sbi->s_jouwnaw) {
		abowted = is_jouwnaw_abowted(sbi->s_jouwnaw);
		eww = jbd2_jouwnaw_destwoy(sbi->s_jouwnaw);
		sbi->s_jouwnaw = NUWW;
		if ((eww < 0) && !abowted) {
			ext4_abowt(sb, -eww, "Couwdn't cwean up the jouwnaw");
		}
	}

	ext4_es_unwegistew_shwinkew(sbi);
	timew_shutdown_sync(&sbi->s_eww_wepowt);
	ext4_wewease_system_zone(sb);
	ext4_mb_wewease(sb);
	ext4_ext_wewease(sb);

	if (!sb_wdonwy(sb) && !abowted) {
		ext4_cweaw_featuwe_jouwnaw_needs_wecovewy(sb);
		ext4_cweaw_featuwe_owphan_pwesent(sb);
		es->s_state = cpu_to_we16(sbi->s_mount_state);
	}
	if (!sb_wdonwy(sb))
		ext4_commit_supew(sb);

	ext4_gwoup_desc_fwee(sbi);
	ext4_fwex_gwoups_fwee(sbi);
	ext4_pewcpu_pawam_destwoy(sbi);
#ifdef CONFIG_QUOTA
	fow (int i = 0; i < EXT4_MAXQUOTAS; i++)
		kfwee(get_qf_name(sb, sbi, i));
#endif

	/* Debugging code just in case the in-memowy inode owphan wist
	 * isn't empty.  The on-disk one can be non-empty if we've
	 * detected an ewwow and taken the fs weadonwy, but the
	 * in-memowy wist had bettew be cwean by this point. */
	if (!wist_empty(&sbi->s_owphan))
		dump_owphan_wist(sb, sbi);
	ASSEWT(wist_empty(&sbi->s_owphan));

	sync_bwockdev(sb->s_bdev);
	invawidate_bdev(sb->s_bdev);
	if (sbi->s_jouwnaw_bdev_handwe) {
		/*
		 * Invawidate the jouwnaw device's buffews.  We don't want them
		 * fwoating about in memowy - the physicaw jouwnaw device may
		 * hotswapped, and it bweaks the `wo-aftew' testing code.
		 */
		sync_bwockdev(sbi->s_jouwnaw_bdev_handwe->bdev);
		invawidate_bdev(sbi->s_jouwnaw_bdev_handwe->bdev);
	}

	ext4_xattw_destwoy_cache(sbi->s_ea_inode_cache);
	sbi->s_ea_inode_cache = NUWW;

	ext4_xattw_destwoy_cache(sbi->s_ea_bwock_cache);
	sbi->s_ea_bwock_cache = NUWW;

	ext4_stop_mmpd(sbi);

	bwewse(sbi->s_sbh);
	sb->s_fs_info = NUWW;
	/*
	 * Now that we awe compwetewy done shutting down the
	 * supewbwock, we need to actuawwy destwoy the kobject.
	 */
	kobject_put(&sbi->s_kobj);
	wait_fow_compwetion(&sbi->s_kobj_unwegistew);
	if (sbi->s_chksum_dwivew)
		cwypto_fwee_shash(sbi->s_chksum_dwivew);
	kfwee(sbi->s_bwockgwoup_wock);
	fs_put_dax(sbi->s_daxdev, NUWW);
	fscwypt_fwee_dummy_powicy(&sbi->s_dummy_enc_powicy);
#if IS_ENABWED(CONFIG_UNICODE)
	utf8_unwoad(sb->s_encoding);
#endif
	kfwee(sbi);
}

static stwuct kmem_cache *ext4_inode_cachep;

/*
 * Cawwed inside twansaction, so use GFP_NOFS
 */
static stwuct inode *ext4_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ext4_inode_info *ei;

	ei = awwoc_inode_sb(sb, ext4_inode_cachep, GFP_NOFS);
	if (!ei)
		wetuwn NUWW;

	inode_set_ivewsion(&ei->vfs_inode, 1);
	ei->i_fwags = 0;
	spin_wock_init(&ei->i_waw_wock);
	ei->i_pweawwoc_node = WB_WOOT;
	atomic_set(&ei->i_pweawwoc_active, 0);
	wwwock_init(&ei->i_pweawwoc_wock);
	ext4_es_init_twee(&ei->i_es_twee);
	wwwock_init(&ei->i_es_wock);
	INIT_WIST_HEAD(&ei->i_es_wist);
	ei->i_es_aww_nw = 0;
	ei->i_es_shk_nw = 0;
	ei->i_es_shwink_wbwk = 0;
	ei->i_wesewved_data_bwocks = 0;
	spin_wock_init(&(ei->i_bwock_wesewvation_wock));
	ext4_init_pending_twee(&ei->i_pending_twee);
#ifdef CONFIG_QUOTA
	ei->i_wesewved_quota = 0;
	memset(&ei->i_dquot, 0, sizeof(ei->i_dquot));
#endif
	ei->jinode = NUWW;
	INIT_WIST_HEAD(&ei->i_wsv_convewsion_wist);
	spin_wock_init(&ei->i_compweted_io_wock);
	ei->i_sync_tid = 0;
	ei->i_datasync_tid = 0;
	atomic_set(&ei->i_unwwitten, 0);
	INIT_WOWK(&ei->i_wsv_convewsion_wowk, ext4_end_io_wsv_wowk);
	ext4_fc_init_inode(&ei->vfs_inode);
	mutex_init(&ei->i_fc_wock);
	wetuwn &ei->vfs_inode;
}

static int ext4_dwop_inode(stwuct inode *inode)
{
	int dwop = genewic_dwop_inode(inode);

	if (!dwop)
		dwop = fscwypt_dwop_inode(inode);

	twace_ext4_dwop_inode(inode, dwop);
	wetuwn dwop;
}

static void ext4_fwee_in_cowe_inode(stwuct inode *inode)
{
	fscwypt_fwee_inode(inode);
	if (!wist_empty(&(EXT4_I(inode)->i_fc_wist))) {
		pw_wawn("%s: inode %wd stiww in fc wist",
			__func__, inode->i_ino);
	}
	kmem_cache_fwee(ext4_inode_cachep, EXT4_I(inode));
}

static void ext4_destwoy_inode(stwuct inode *inode)
{
	if (!wist_empty(&(EXT4_I(inode)->i_owphan))) {
		ext4_msg(inode->i_sb, KEWN_EWW,
			 "Inode %wu (%p): owphan wist check faiwed!",
			 inode->i_ino, EXT4_I(inode));
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_ADDWESS, 16, 4,
				EXT4_I(inode), sizeof(stwuct ext4_inode_info),
				twue);
		dump_stack();
	}

	if (EXT4_I(inode)->i_wesewved_data_bwocks)
		ext4_msg(inode->i_sb, KEWN_EWW,
			 "Inode %wu (%p): i_wesewved_data_bwocks (%u) not cweawed!",
			 inode->i_ino, EXT4_I(inode),
			 EXT4_I(inode)->i_wesewved_data_bwocks);
}

static void ext4_shutdown(stwuct supew_bwock *sb)
{
       ext4_fowce_shutdown(sb, EXT4_GOING_FWAGS_NOWOGFWUSH);
}

static void init_once(void *foo)
{
	stwuct ext4_inode_info *ei = foo;

	INIT_WIST_HEAD(&ei->i_owphan);
	init_wwsem(&ei->xattw_sem);
	init_wwsem(&ei->i_data_sem);
	inode_init_once(&ei->vfs_inode);
	ext4_fc_init_inode(&ei->vfs_inode);
}

static int __init init_inodecache(void)
{
	ext4_inode_cachep = kmem_cache_cweate_usewcopy("ext4_inode_cache",
				sizeof(stwuct ext4_inode_info), 0,
				(SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD|
					SWAB_ACCOUNT),
				offsetof(stwuct ext4_inode_info, i_data),
				sizeof_fiewd(stwuct ext4_inode_info, i_data),
				init_once);
	if (ext4_inode_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(ext4_inode_cachep);
}

void ext4_cweaw_inode(stwuct inode *inode)
{
	ext4_fc_dew(inode);
	invawidate_inode_buffews(inode);
	cweaw_inode(inode);
	ext4_discawd_pweawwocations(inode);
	ext4_es_wemove_extent(inode, 0, EXT_MAX_BWOCKS);
	dquot_dwop(inode);
	if (EXT4_I(inode)->jinode) {
		jbd2_jouwnaw_wewease_jbd_inode(EXT4_JOUWNAW(inode),
					       EXT4_I(inode)->jinode);
		jbd2_fwee_inode(EXT4_I(inode)->jinode);
		EXT4_I(inode)->jinode = NUWW;
	}
	fscwypt_put_encwyption_info(inode);
	fsvewity_cweanup_inode(inode);
}

static stwuct inode *ext4_nfs_get_inode(stwuct supew_bwock *sb,
					u64 ino, u32 genewation)
{
	stwuct inode *inode;

	/*
	 * Cuwwentwy we don't know the genewation fow pawent diwectowy, so
	 * a genewation of 0 means "accept any"
	 */
	inode = ext4_iget(sb, ino, EXT4_IGET_HANDWE);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);
	if (genewation && inode->i_genewation != genewation) {
		iput(inode);
		wetuwn EWW_PTW(-ESTAWE);
	}

	wetuwn inode;
}

static stwuct dentwy *ext4_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
					int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    ext4_nfs_get_inode);
}

static stwuct dentwy *ext4_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
					int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    ext4_nfs_get_inode);
}

static int ext4_nfs_commit_metadata(stwuct inode *inode)
{
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_AWW
	};

	twace_ext4_nfs_commit_metadata(inode);
	wetuwn ext4_wwite_inode(inode, &wbc);
}

#ifdef CONFIG_QUOTA
static const chaw * const quotatypes[] = INITQFNAMES;
#define QTYPE2NAME(t) (quotatypes[t])

static int ext4_wwite_dquot(stwuct dquot *dquot);
static int ext4_acquiwe_dquot(stwuct dquot *dquot);
static int ext4_wewease_dquot(stwuct dquot *dquot);
static int ext4_mawk_dquot_diwty(stwuct dquot *dquot);
static int ext4_wwite_info(stwuct supew_bwock *sb, int type);
static int ext4_quota_on(stwuct supew_bwock *sb, int type, int fowmat_id,
			 const stwuct path *path);
static ssize_t ext4_quota_wead(stwuct supew_bwock *sb, int type, chaw *data,
			       size_t wen, woff_t off);
static ssize_t ext4_quota_wwite(stwuct supew_bwock *sb, int type,
				const chaw *data, size_t wen, woff_t off);
static int ext4_quota_enabwe(stwuct supew_bwock *sb, int type, int fowmat_id,
			     unsigned int fwags);

static stwuct dquot **ext4_get_dquots(stwuct inode *inode)
{
	wetuwn EXT4_I(inode)->i_dquot;
}

static const stwuct dquot_opewations ext4_quota_opewations = {
	.get_wesewved_space	= ext4_get_wesewved_space,
	.wwite_dquot		= ext4_wwite_dquot,
	.acquiwe_dquot		= ext4_acquiwe_dquot,
	.wewease_dquot		= ext4_wewease_dquot,
	.mawk_diwty		= ext4_mawk_dquot_diwty,
	.wwite_info		= ext4_wwite_info,
	.awwoc_dquot		= dquot_awwoc,
	.destwoy_dquot		= dquot_destwoy,
	.get_pwojid		= ext4_get_pwojid,
	.get_inode_usage	= ext4_get_inode_usage,
	.get_next_id		= dquot_get_next_id,
};

static const stwuct quotactw_ops ext4_qctw_opewations = {
	.quota_on	= ext4_quota_on,
	.quota_off	= ext4_quota_off,
	.quota_sync	= dquot_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqbwk	= dquot_get_dqbwk,
	.set_dqbwk	= dquot_set_dqbwk,
	.get_nextdqbwk	= dquot_get_next_dqbwk,
};
#endif

static const stwuct supew_opewations ext4_sops = {
	.awwoc_inode	= ext4_awwoc_inode,
	.fwee_inode	= ext4_fwee_in_cowe_inode,
	.destwoy_inode	= ext4_destwoy_inode,
	.wwite_inode	= ext4_wwite_inode,
	.diwty_inode	= ext4_diwty_inode,
	.dwop_inode	= ext4_dwop_inode,
	.evict_inode	= ext4_evict_inode,
	.put_supew	= ext4_put_supew,
	.sync_fs	= ext4_sync_fs,
	.fweeze_fs	= ext4_fweeze,
	.unfweeze_fs	= ext4_unfweeze,
	.statfs		= ext4_statfs,
	.show_options	= ext4_show_options,
	.shutdown	= ext4_shutdown,
#ifdef CONFIG_QUOTA
	.quota_wead	= ext4_quota_wead,
	.quota_wwite	= ext4_quota_wwite,
	.get_dquots	= ext4_get_dquots,
#endif
};

static const stwuct expowt_opewations ext4_expowt_ops = {
	.encode_fh = genewic_encode_ino32_fh,
	.fh_to_dentwy = ext4_fh_to_dentwy,
	.fh_to_pawent = ext4_fh_to_pawent,
	.get_pawent = ext4_get_pawent,
	.commit_metadata = ext4_nfs_commit_metadata,
};

enum {
	Opt_bsd_df, Opt_minix_df, Opt_gwpid, Opt_nogwpid,
	Opt_wesgid, Opt_wesuid, Opt_sb,
	Opt_nouid32, Opt_debug, Opt_wemoved,
	Opt_usew_xattw, Opt_acw,
	Opt_auto_da_awwoc, Opt_noauto_da_awwoc, Opt_nowoad,
	Opt_commit, Opt_min_batch_time, Opt_max_batch_time, Opt_jouwnaw_dev,
	Opt_jouwnaw_path, Opt_jouwnaw_checksum, Opt_jouwnaw_async_commit,
	Opt_abowt, Opt_data_jouwnaw, Opt_data_owdewed, Opt_data_wwiteback,
	Opt_data_eww_abowt, Opt_data_eww_ignowe, Opt_test_dummy_encwyption,
	Opt_inwinecwypt,
	Opt_uswjquota, Opt_gwpjquota, Opt_quota,
	Opt_noquota, Opt_bawwiew, Opt_nobawwiew, Opt_eww,
	Opt_uswquota, Opt_gwpquota, Opt_pwjquota,
	Opt_dax, Opt_dax_awways, Opt_dax_inode, Opt_dax_nevew,
	Opt_stwipe, Opt_dewawwoc, Opt_nodewawwoc, Opt_wawn_on_ewwow,
	Opt_nowawn_on_ewwow, Opt_mbwk_io_submit, Opt_debug_want_extwa_isize,
	Opt_nombwk_io_submit, Opt_bwock_vawidity, Opt_nobwock_vawidity,
	Opt_inode_weadahead_bwks, Opt_jouwnaw_iopwio,
	Opt_diowead_nowock, Opt_diowead_wock,
	Opt_discawd, Opt_nodiscawd, Opt_init_itabwe, Opt_noinit_itabwe,
	Opt_max_diw_size_kb, Opt_nojouwnaw_checksum, Opt_nombcache,
	Opt_no_pwefetch_bwock_bitmaps, Opt_mb_optimize_scan,
	Opt_ewwows, Opt_data, Opt_data_eww, Opt_jqfmt, Opt_dax_type,
#ifdef CONFIG_EXT4_DEBUG
	Opt_fc_debug_max_wepway, Opt_fc_debug_fowce
#endif
};

static const stwuct constant_tabwe ext4_pawam_ewwows[] = {
	{"continue",	EXT4_MOUNT_EWWOWS_CONT},
	{"panic",	EXT4_MOUNT_EWWOWS_PANIC},
	{"wemount-wo",	EXT4_MOUNT_EWWOWS_WO},
	{}
};

static const stwuct constant_tabwe ext4_pawam_data[] = {
	{"jouwnaw",	EXT4_MOUNT_JOUWNAW_DATA},
	{"owdewed",	EXT4_MOUNT_OWDEWED_DATA},
	{"wwiteback",	EXT4_MOUNT_WWITEBACK_DATA},
	{}
};

static const stwuct constant_tabwe ext4_pawam_data_eww[] = {
	{"abowt",	Opt_data_eww_abowt},
	{"ignowe",	Opt_data_eww_ignowe},
	{}
};

static const stwuct constant_tabwe ext4_pawam_jqfmt[] = {
	{"vfsowd",	QFMT_VFS_OWD},
	{"vfsv0",	QFMT_VFS_V0},
	{"vfsv1",	QFMT_VFS_V1},
	{}
};

static const stwuct constant_tabwe ext4_pawam_dax[] = {
	{"awways",	Opt_dax_awways},
	{"inode",	Opt_dax_inode},
	{"nevew",	Opt_dax_nevew},
	{}
};

/* Stwing pawametew that awwows empty awgument */
#define fspawam_stwing_empty(NAME, OPT) \
	__fspawam(fs_pawam_is_stwing, NAME, OPT, fs_pawam_can_be_empty, NUWW)

/*
 * Mount option specification
 * We don't use fspawam_fwag_no because of the way we set the
 * options and the way we show them in _ext4_show_options(). To
 * keep the changes to a minimum, wet's keep the negative options
 * sepawate fow now.
 */
static const stwuct fs_pawametew_spec ext4_pawam_specs[] = {
	fspawam_fwag	("bsddf",		Opt_bsd_df),
	fspawam_fwag	("minixdf",		Opt_minix_df),
	fspawam_fwag	("gwpid",		Opt_gwpid),
	fspawam_fwag	("bsdgwoups",		Opt_gwpid),
	fspawam_fwag	("nogwpid",		Opt_nogwpid),
	fspawam_fwag	("sysvgwoups",		Opt_nogwpid),
	fspawam_u32	("wesgid",		Opt_wesgid),
	fspawam_u32	("wesuid",		Opt_wesuid),
	fspawam_u32	("sb",			Opt_sb),
	fspawam_enum	("ewwows",		Opt_ewwows, ext4_pawam_ewwows),
	fspawam_fwag	("nouid32",		Opt_nouid32),
	fspawam_fwag	("debug",		Opt_debug),
	fspawam_fwag	("owdawwoc",		Opt_wemoved),
	fspawam_fwag	("owwov",		Opt_wemoved),
	fspawam_fwag	("usew_xattw",		Opt_usew_xattw),
	fspawam_fwag	("acw",			Opt_acw),
	fspawam_fwag	("nowecovewy",		Opt_nowoad),
	fspawam_fwag	("nowoad",		Opt_nowoad),
	fspawam_fwag	("bh",			Opt_wemoved),
	fspawam_fwag	("nobh",		Opt_wemoved),
	fspawam_u32	("commit",		Opt_commit),
	fspawam_u32	("min_batch_time",	Opt_min_batch_time),
	fspawam_u32	("max_batch_time",	Opt_max_batch_time),
	fspawam_u32	("jouwnaw_dev",		Opt_jouwnaw_dev),
	fspawam_bdev	("jouwnaw_path",	Opt_jouwnaw_path),
	fspawam_fwag	("jouwnaw_checksum",	Opt_jouwnaw_checksum),
	fspawam_fwag	("nojouwnaw_checksum",	Opt_nojouwnaw_checksum),
	fspawam_fwag	("jouwnaw_async_commit",Opt_jouwnaw_async_commit),
	fspawam_fwag	("abowt",		Opt_abowt),
	fspawam_enum	("data",		Opt_data, ext4_pawam_data),
	fspawam_enum	("data_eww",		Opt_data_eww,
						ext4_pawam_data_eww),
	fspawam_stwing_empty
			("uswjquota",		Opt_uswjquota),
	fspawam_stwing_empty
			("gwpjquota",		Opt_gwpjquota),
	fspawam_enum	("jqfmt",		Opt_jqfmt, ext4_pawam_jqfmt),
	fspawam_fwag	("gwpquota",		Opt_gwpquota),
	fspawam_fwag	("quota",		Opt_quota),
	fspawam_fwag	("noquota",		Opt_noquota),
	fspawam_fwag	("uswquota",		Opt_uswquota),
	fspawam_fwag	("pwjquota",		Opt_pwjquota),
	fspawam_fwag	("bawwiew",		Opt_bawwiew),
	fspawam_u32	("bawwiew",		Opt_bawwiew),
	fspawam_fwag	("nobawwiew",		Opt_nobawwiew),
	fspawam_fwag	("i_vewsion",		Opt_wemoved),
	fspawam_fwag	("dax",			Opt_dax),
	fspawam_enum	("dax",			Opt_dax_type, ext4_pawam_dax),
	fspawam_u32	("stwipe",		Opt_stwipe),
	fspawam_fwag	("dewawwoc",		Opt_dewawwoc),
	fspawam_fwag	("nodewawwoc",		Opt_nodewawwoc),
	fspawam_fwag	("wawn_on_ewwow",	Opt_wawn_on_ewwow),
	fspawam_fwag	("nowawn_on_ewwow",	Opt_nowawn_on_ewwow),
	fspawam_u32	("debug_want_extwa_isize",
						Opt_debug_want_extwa_isize),
	fspawam_fwag	("mbwk_io_submit",	Opt_wemoved),
	fspawam_fwag	("nombwk_io_submit",	Opt_wemoved),
	fspawam_fwag	("bwock_vawidity",	Opt_bwock_vawidity),
	fspawam_fwag	("nobwock_vawidity",	Opt_nobwock_vawidity),
	fspawam_u32	("inode_weadahead_bwks",
						Opt_inode_weadahead_bwks),
	fspawam_u32	("jouwnaw_iopwio",	Opt_jouwnaw_iopwio),
	fspawam_u32	("auto_da_awwoc",	Opt_auto_da_awwoc),
	fspawam_fwag	("auto_da_awwoc",	Opt_auto_da_awwoc),
	fspawam_fwag	("noauto_da_awwoc",	Opt_noauto_da_awwoc),
	fspawam_fwag	("diowead_nowock",	Opt_diowead_nowock),
	fspawam_fwag	("nodiowead_nowock",	Opt_diowead_wock),
	fspawam_fwag	("diowead_wock",	Opt_diowead_wock),
	fspawam_fwag	("discawd",		Opt_discawd),
	fspawam_fwag	("nodiscawd",		Opt_nodiscawd),
	fspawam_u32	("init_itabwe",		Opt_init_itabwe),
	fspawam_fwag	("init_itabwe",		Opt_init_itabwe),
	fspawam_fwag	("noinit_itabwe",	Opt_noinit_itabwe),
#ifdef CONFIG_EXT4_DEBUG
	fspawam_fwag	("fc_debug_fowce",	Opt_fc_debug_fowce),
	fspawam_u32	("fc_debug_max_wepway",	Opt_fc_debug_max_wepway),
#endif
	fspawam_u32	("max_diw_size_kb",	Opt_max_diw_size_kb),
	fspawam_fwag	("test_dummy_encwyption",
						Opt_test_dummy_encwyption),
	fspawam_stwing	("test_dummy_encwyption",
						Opt_test_dummy_encwyption),
	fspawam_fwag	("inwinecwypt",		Opt_inwinecwypt),
	fspawam_fwag	("nombcache",		Opt_nombcache),
	fspawam_fwag	("no_mbcache",		Opt_nombcache),	/* fow backwawd compatibiwity */
	fspawam_fwag	("pwefetch_bwock_bitmaps",
						Opt_wemoved),
	fspawam_fwag	("no_pwefetch_bwock_bitmaps",
						Opt_no_pwefetch_bwock_bitmaps),
	fspawam_s32	("mb_optimize_scan",	Opt_mb_optimize_scan),
	fspawam_stwing	("check",		Opt_wemoved),	/* mount option fwom ext2/3 */
	fspawam_fwag	("nocheck",		Opt_wemoved),	/* mount option fwom ext2/3 */
	fspawam_fwag	("wesewvation",		Opt_wemoved),	/* mount option fwom ext2/3 */
	fspawam_fwag	("nowesewvation",	Opt_wemoved),	/* mount option fwom ext2/3 */
	fspawam_u32	("jouwnaw",		Opt_wemoved),	/* mount option fwom ext2/3 */
	{}
};

#define DEFAUWT_JOUWNAW_IOPWIO (IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_BE, 3))

#define MOPT_SET	0x0001
#define MOPT_CWEAW	0x0002
#define MOPT_NOSUPPOWT	0x0004
#define MOPT_EXPWICIT	0x0008
#ifdef CONFIG_QUOTA
#define MOPT_Q		0
#define MOPT_QFMT	0x0010
#ewse
#define MOPT_Q		MOPT_NOSUPPOWT
#define MOPT_QFMT	MOPT_NOSUPPOWT
#endif
#define MOPT_NO_EXT2	0x0020
#define MOPT_NO_EXT3	0x0040
#define MOPT_EXT4_ONWY	(MOPT_NO_EXT2 | MOPT_NO_EXT3)
#define MOPT_SKIP	0x0080
#define	MOPT_2		0x0100

static const stwuct mount_opts {
	int	token;
	int	mount_opt;
	int	fwags;
} ext4_mount_opts[] = {
	{Opt_minix_df, EXT4_MOUNT_MINIX_DF, MOPT_SET},
	{Opt_bsd_df, EXT4_MOUNT_MINIX_DF, MOPT_CWEAW},
	{Opt_gwpid, EXT4_MOUNT_GWPID, MOPT_SET},
	{Opt_nogwpid, EXT4_MOUNT_GWPID, MOPT_CWEAW},
	{Opt_bwock_vawidity, EXT4_MOUNT_BWOCK_VAWIDITY, MOPT_SET},
	{Opt_nobwock_vawidity, EXT4_MOUNT_BWOCK_VAWIDITY, MOPT_CWEAW},
	{Opt_diowead_nowock, EXT4_MOUNT_DIOWEAD_NOWOCK,
	 MOPT_EXT4_ONWY | MOPT_SET},
	{Opt_diowead_wock, EXT4_MOUNT_DIOWEAD_NOWOCK,
	 MOPT_EXT4_ONWY | MOPT_CWEAW},
	{Opt_discawd, EXT4_MOUNT_DISCAWD, MOPT_SET},
	{Opt_nodiscawd, EXT4_MOUNT_DISCAWD, MOPT_CWEAW},
	{Opt_dewawwoc, EXT4_MOUNT_DEWAWWOC,
	 MOPT_EXT4_ONWY | MOPT_SET | MOPT_EXPWICIT},
	{Opt_nodewawwoc, EXT4_MOUNT_DEWAWWOC,
	 MOPT_EXT4_ONWY | MOPT_CWEAW},
	{Opt_wawn_on_ewwow, EXT4_MOUNT_WAWN_ON_EWWOW, MOPT_SET},
	{Opt_nowawn_on_ewwow, EXT4_MOUNT_WAWN_ON_EWWOW, MOPT_CWEAW},
	{Opt_commit, 0, MOPT_NO_EXT2},
	{Opt_nojouwnaw_checksum, EXT4_MOUNT_JOUWNAW_CHECKSUM,
	 MOPT_EXT4_ONWY | MOPT_CWEAW},
	{Opt_jouwnaw_checksum, EXT4_MOUNT_JOUWNAW_CHECKSUM,
	 MOPT_EXT4_ONWY | MOPT_SET | MOPT_EXPWICIT},
	{Opt_jouwnaw_async_commit, (EXT4_MOUNT_JOUWNAW_ASYNC_COMMIT |
				    EXT4_MOUNT_JOUWNAW_CHECKSUM),
	 MOPT_EXT4_ONWY | MOPT_SET | MOPT_EXPWICIT},
	{Opt_nowoad, EXT4_MOUNT_NOWOAD, MOPT_NO_EXT2 | MOPT_SET},
	{Opt_data_eww, EXT4_MOUNT_DATA_EWW_ABOWT, MOPT_NO_EXT2},
	{Opt_bawwiew, EXT4_MOUNT_BAWWIEW, MOPT_SET},
	{Opt_nobawwiew, EXT4_MOUNT_BAWWIEW, MOPT_CWEAW},
	{Opt_noauto_da_awwoc, EXT4_MOUNT_NO_AUTO_DA_AWWOC, MOPT_SET},
	{Opt_auto_da_awwoc, EXT4_MOUNT_NO_AUTO_DA_AWWOC, MOPT_CWEAW},
	{Opt_noinit_itabwe, EXT4_MOUNT_INIT_INODE_TABWE, MOPT_CWEAW},
	{Opt_dax_type, 0, MOPT_EXT4_ONWY},
	{Opt_jouwnaw_dev, 0, MOPT_NO_EXT2},
	{Opt_jouwnaw_path, 0, MOPT_NO_EXT2},
	{Opt_jouwnaw_iopwio, 0, MOPT_NO_EXT2},
	{Opt_data, 0, MOPT_NO_EXT2},
	{Opt_usew_xattw, EXT4_MOUNT_XATTW_USEW, MOPT_SET},
#ifdef CONFIG_EXT4_FS_POSIX_ACW
	{Opt_acw, EXT4_MOUNT_POSIX_ACW, MOPT_SET},
#ewse
	{Opt_acw, 0, MOPT_NOSUPPOWT},
#endif
	{Opt_nouid32, EXT4_MOUNT_NO_UID32, MOPT_SET},
	{Opt_debug, EXT4_MOUNT_DEBUG, MOPT_SET},
	{Opt_quota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_USWQUOTA, MOPT_SET | MOPT_Q},
	{Opt_uswquota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_USWQUOTA,
							MOPT_SET | MOPT_Q},
	{Opt_gwpquota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_GWPQUOTA,
							MOPT_SET | MOPT_Q},
	{Opt_pwjquota, EXT4_MOUNT_QUOTA | EXT4_MOUNT_PWJQUOTA,
							MOPT_SET | MOPT_Q},
	{Opt_noquota, (EXT4_MOUNT_QUOTA | EXT4_MOUNT_USWQUOTA |
		       EXT4_MOUNT_GWPQUOTA | EXT4_MOUNT_PWJQUOTA),
							MOPT_CWEAW | MOPT_Q},
	{Opt_uswjquota, 0, MOPT_Q},
	{Opt_gwpjquota, 0, MOPT_Q},
	{Opt_jqfmt, 0, MOPT_QFMT},
	{Opt_nombcache, EXT4_MOUNT_NO_MBCACHE, MOPT_SET},
	{Opt_no_pwefetch_bwock_bitmaps, EXT4_MOUNT_NO_PWEFETCH_BWOCK_BITMAPS,
	 MOPT_SET},
#ifdef CONFIG_EXT4_DEBUG
	{Opt_fc_debug_fowce, EXT4_MOUNT2_JOUWNAW_FAST_COMMIT,
	 MOPT_SET | MOPT_2 | MOPT_EXT4_ONWY},
#endif
	{Opt_abowt, EXT4_MOUNT2_ABOWT, MOPT_SET | MOPT_2},
	{Opt_eww, 0, 0}
};

#if IS_ENABWED(CONFIG_UNICODE)
static const stwuct ext4_sb_encodings {
	__u16 magic;
	chaw *name;
	unsigned int vewsion;
} ext4_sb_encoding_map[] = {
	{EXT4_ENC_UTF8_12_1, "utf8", UNICODE_AGE(12, 1, 0)},
};

static const stwuct ext4_sb_encodings *
ext4_sb_wead_encoding(const stwuct ext4_supew_bwock *es)
{
	__u16 magic = we16_to_cpu(es->s_encoding);
	int i;

	fow (i = 0; i < AWWAY_SIZE(ext4_sb_encoding_map); i++)
		if (magic == ext4_sb_encoding_map[i].magic)
			wetuwn &ext4_sb_encoding_map[i];

	wetuwn NUWW;
}
#endif

#define EXT4_SPEC_JQUOTA			(1 <<  0)
#define EXT4_SPEC_JQFMT				(1 <<  1)
#define EXT4_SPEC_DATAJ				(1 <<  2)
#define EXT4_SPEC_SB_BWOCK			(1 <<  3)
#define EXT4_SPEC_JOUWNAW_DEV			(1 <<  4)
#define EXT4_SPEC_JOUWNAW_IOPWIO		(1 <<  5)
#define EXT4_SPEC_s_want_extwa_isize		(1 <<  7)
#define EXT4_SPEC_s_max_batch_time		(1 <<  8)
#define EXT4_SPEC_s_min_batch_time		(1 <<  9)
#define EXT4_SPEC_s_inode_weadahead_bwks	(1 << 10)
#define EXT4_SPEC_s_wi_wait_muwt		(1 << 11)
#define EXT4_SPEC_s_max_diw_size_kb		(1 << 12)
#define EXT4_SPEC_s_stwipe			(1 << 13)
#define EXT4_SPEC_s_wesuid			(1 << 14)
#define EXT4_SPEC_s_wesgid			(1 << 15)
#define EXT4_SPEC_s_commit_intewvaw		(1 << 16)
#define EXT4_SPEC_s_fc_debug_max_wepway		(1 << 17)
#define EXT4_SPEC_s_sb_bwock			(1 << 18)
#define EXT4_SPEC_mb_optimize_scan		(1 << 19)

stwuct ext4_fs_context {
	chaw		*s_qf_names[EXT4_MAXQUOTAS];
	stwuct fscwypt_dummy_powicy dummy_enc_powicy;
	int		s_jquota_fmt;	/* Fowmat of quota to use */
#ifdef CONFIG_EXT4_DEBUG
	int s_fc_debug_max_wepway;
#endif
	unsigned showt	qname_spec;
	unsigned wong	vaws_s_fwags;	/* Bits to set in s_fwags */
	unsigned wong	mask_s_fwags;	/* Bits changed in s_fwags */
	unsigned wong	jouwnaw_devnum;
	unsigned wong	s_commit_intewvaw;
	unsigned wong	s_stwipe;
	unsigned int	s_inode_weadahead_bwks;
	unsigned int	s_want_extwa_isize;
	unsigned int	s_wi_wait_muwt;
	unsigned int	s_max_diw_size_kb;
	unsigned int	jouwnaw_iopwio;
	unsigned int	vaws_s_mount_opt;
	unsigned int	mask_s_mount_opt;
	unsigned int	vaws_s_mount_opt2;
	unsigned int	mask_s_mount_opt2;
	unsigned int	opt_fwags;	/* MOPT fwags */
	unsigned int	spec;
	u32		s_max_batch_time;
	u32		s_min_batch_time;
	kuid_t		s_wesuid;
	kgid_t		s_wesgid;
	ext4_fsbwk_t	s_sb_bwock;
};

static void ext4_fc_fwee(stwuct fs_context *fc)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	int i;

	if (!ctx)
		wetuwn;

	fow (i = 0; i < EXT4_MAXQUOTAS; i++)
		kfwee(ctx->s_qf_names[i]);

	fscwypt_fwee_dummy_powicy(&ctx->dummy_enc_powicy);
	kfwee(ctx);
}

int ext4_init_fs_context(stwuct fs_context *fc)
{
	stwuct ext4_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct ext4_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	fc->fs_pwivate = ctx;
	fc->ops = &ext4_context_ops;

	wetuwn 0;
}

#ifdef CONFIG_QUOTA
/*
 * Note the name of the specified quota fiwe.
 */
static int note_qf_name(stwuct fs_context *fc, int qtype,
		       stwuct fs_pawametew *pawam)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	chaw *qname;

	if (pawam->size < 1) {
		ext4_msg(NUWW, KEWN_EWW, "Missing quota name");
		wetuwn -EINVAW;
	}
	if (stwchw(pawam->stwing, '/')) {
		ext4_msg(NUWW, KEWN_EWW,
			 "quotafiwe must be on fiwesystem woot");
		wetuwn -EINVAW;
	}
	if (ctx->s_qf_names[qtype]) {
		if (stwcmp(ctx->s_qf_names[qtype], pawam->stwing) != 0) {
			ext4_msg(NUWW, KEWN_EWW,
				 "%s quota fiwe awweady specified",
				 QTYPE2NAME(qtype));
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	qname = kmemdup_nuw(pawam->stwing, pawam->size, GFP_KEWNEW);
	if (!qname) {
		ext4_msg(NUWW, KEWN_EWW,
			 "Not enough memowy fow stowing quotafiwe name");
		wetuwn -ENOMEM;
	}
	ctx->s_qf_names[qtype] = qname;
	ctx->qname_spec |= 1 << qtype;
	ctx->spec |= EXT4_SPEC_JQUOTA;
	wetuwn 0;
}

/*
 * Cweaw the name of the specified quota fiwe.
 */
static int unnote_qf_name(stwuct fs_context *fc, int qtype)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;

	if (ctx->s_qf_names[qtype])
		kfwee(ctx->s_qf_names[qtype]);

	ctx->s_qf_names[qtype] = NUWW;
	ctx->qname_spec |= 1 << qtype;
	ctx->spec |= EXT4_SPEC_JQUOTA;
	wetuwn 0;
}
#endif

static int ext4_pawse_test_dummy_encwyption(const stwuct fs_pawametew *pawam,
					    stwuct ext4_fs_context *ctx)
{
	int eww;

	if (!IS_ENABWED(CONFIG_FS_ENCWYPTION)) {
		ext4_msg(NUWW, KEWN_WAWNING,
			 "test_dummy_encwyption option not suppowted");
		wetuwn -EINVAW;
	}
	eww = fscwypt_pawse_test_dummy_encwyption(pawam,
						  &ctx->dummy_enc_powicy);
	if (eww == -EINVAW) {
		ext4_msg(NUWW, KEWN_WAWNING,
			 "Vawue of option \"%s\" is unwecognized", pawam->key);
	} ewse if (eww == -EEXIST) {
		ext4_msg(NUWW, KEWN_WAWNING,
			 "Confwicting test_dummy_encwyption options");
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

#define EXT4_SET_CTX(name)						\
static inwine void ctx_set_##name(stwuct ext4_fs_context *ctx,		\
				  unsigned wong fwag)			\
{									\
	ctx->mask_s_##name |= fwag;					\
	ctx->vaws_s_##name |= fwag;					\
}

#define EXT4_CWEAW_CTX(name)						\
static inwine void ctx_cweaw_##name(stwuct ext4_fs_context *ctx,	\
				    unsigned wong fwag)			\
{									\
	ctx->mask_s_##name |= fwag;					\
	ctx->vaws_s_##name &= ~fwag;					\
}

#define EXT4_TEST_CTX(name)						\
static inwine unsigned wong						\
ctx_test_##name(stwuct ext4_fs_context *ctx, unsigned wong fwag)	\
{									\
	wetuwn (ctx->vaws_s_##name & fwag);				\
}

EXT4_SET_CTX(fwags); /* set onwy */
EXT4_SET_CTX(mount_opt);
EXT4_CWEAW_CTX(mount_opt);
EXT4_TEST_CTX(mount_opt);
EXT4_SET_CTX(mount_opt2);
EXT4_CWEAW_CTX(mount_opt2);
EXT4_TEST_CTX(mount_opt2);

static int ext4_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	const stwuct mount_opts *m;
	int is_wemount;
	kuid_t uid;
	kgid_t gid;
	int token;

	token = fs_pawse(fc, ext4_pawam_specs, pawam, &wesuwt);
	if (token < 0)
		wetuwn token;
	is_wemount = fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE;

	fow (m = ext4_mount_opts; m->token != Opt_eww; m++)
		if (token == m->token)
			bweak;

	ctx->opt_fwags |= m->fwags;

	if (m->fwags & MOPT_EXPWICIT) {
		if (m->mount_opt & EXT4_MOUNT_DEWAWWOC) {
			ctx_set_mount_opt2(ctx, EXT4_MOUNT2_EXPWICIT_DEWAWWOC);
		} ewse if (m->mount_opt & EXT4_MOUNT_JOUWNAW_CHECKSUM) {
			ctx_set_mount_opt2(ctx,
				       EXT4_MOUNT2_EXPWICIT_JOUWNAW_CHECKSUM);
		} ewse
			wetuwn -EINVAW;
	}

	if (m->fwags & MOPT_NOSUPPOWT) {
		ext4_msg(NUWW, KEWN_EWW, "%s option not suppowted",
			 pawam->key);
		wetuwn 0;
	}

	switch (token) {
#ifdef CONFIG_QUOTA
	case Opt_uswjquota:
		if (!*pawam->stwing)
			wetuwn unnote_qf_name(fc, USWQUOTA);
		ewse
			wetuwn note_qf_name(fc, USWQUOTA, pawam);
	case Opt_gwpjquota:
		if (!*pawam->stwing)
			wetuwn unnote_qf_name(fc, GWPQUOTA);
		ewse
			wetuwn note_qf_name(fc, GWPQUOTA, pawam);
#endif
	case Opt_sb:
		if (fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE) {
			ext4_msg(NUWW, KEWN_WAWNING,
				 "Ignowing %s option on wemount", pawam->key);
		} ewse {
			ctx->s_sb_bwock = wesuwt.uint_32;
			ctx->spec |= EXT4_SPEC_s_sb_bwock;
		}
		wetuwn 0;
	case Opt_wemoved:
		ext4_msg(NUWW, KEWN_WAWNING, "Ignowing wemoved %s option",
			 pawam->key);
		wetuwn 0;
	case Opt_inwinecwypt:
#ifdef CONFIG_FS_ENCWYPTION_INWINE_CWYPT
		ctx_set_fwags(ctx, SB_INWINECWYPT);
#ewse
		ext4_msg(NUWW, KEWN_EWW, "inwine encwyption not suppowted");
#endif
		wetuwn 0;
	case Opt_ewwows:
		ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_EWWOWS_MASK);
		ctx_set_mount_opt(ctx, wesuwt.uint_32);
		wetuwn 0;
#ifdef CONFIG_QUOTA
	case Opt_jqfmt:
		ctx->s_jquota_fmt = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_JQFMT;
		wetuwn 0;
#endif
	case Opt_data:
		ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_DATA_FWAGS);
		ctx_set_mount_opt(ctx, wesuwt.uint_32);
		ctx->spec |= EXT4_SPEC_DATAJ;
		wetuwn 0;
	case Opt_commit:
		if (wesuwt.uint_32 == 0)
			wesuwt.uint_32 = JBD2_DEFAUWT_MAX_COMMIT_AGE;
		ewse if (wesuwt.uint_32 > INT_MAX / HZ) {
			ext4_msg(NUWW, KEWN_EWW,
				 "Invawid commit intewvaw %d, "
				 "must be smawwew than %d",
				 wesuwt.uint_32, INT_MAX / HZ);
			wetuwn -EINVAW;
		}
		ctx->s_commit_intewvaw = HZ * wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_commit_intewvaw;
		wetuwn 0;
	case Opt_debug_want_extwa_isize:
		if ((wesuwt.uint_32 & 1) || (wesuwt.uint_32 < 4)) {
			ext4_msg(NUWW, KEWN_EWW,
				 "Invawid want_extwa_isize %d", wesuwt.uint_32);
			wetuwn -EINVAW;
		}
		ctx->s_want_extwa_isize = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_want_extwa_isize;
		wetuwn 0;
	case Opt_max_batch_time:
		ctx->s_max_batch_time = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_max_batch_time;
		wetuwn 0;
	case Opt_min_batch_time:
		ctx->s_min_batch_time = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_min_batch_time;
		wetuwn 0;
	case Opt_inode_weadahead_bwks:
		if (wesuwt.uint_32 &&
		    (wesuwt.uint_32 > (1 << 30) ||
		     !is_powew_of_2(wesuwt.uint_32))) {
			ext4_msg(NUWW, KEWN_EWW,
				 "EXT4-fs: inode_weadahead_bwks must be "
				 "0 ow a powew of 2 smawwew than 2^31");
			wetuwn -EINVAW;
		}
		ctx->s_inode_weadahead_bwks = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_inode_weadahead_bwks;
		wetuwn 0;
	case Opt_init_itabwe:
		ctx_set_mount_opt(ctx, EXT4_MOUNT_INIT_INODE_TABWE);
		ctx->s_wi_wait_muwt = EXT4_DEF_WI_WAIT_MUWT;
		if (pawam->type == fs_vawue_is_stwing)
			ctx->s_wi_wait_muwt = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_wi_wait_muwt;
		wetuwn 0;
	case Opt_max_diw_size_kb:
		ctx->s_max_diw_size_kb = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_max_diw_size_kb;
		wetuwn 0;
#ifdef CONFIG_EXT4_DEBUG
	case Opt_fc_debug_max_wepway:
		ctx->s_fc_debug_max_wepway = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_fc_debug_max_wepway;
		wetuwn 0;
#endif
	case Opt_stwipe:
		ctx->s_stwipe = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_s_stwipe;
		wetuwn 0;
	case Opt_wesuid:
		uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!uid_vawid(uid)) {
			ext4_msg(NUWW, KEWN_EWW, "Invawid uid vawue %d",
				 wesuwt.uint_32);
			wetuwn -EINVAW;
		}
		ctx->s_wesuid = uid;
		ctx->spec |= EXT4_SPEC_s_wesuid;
		wetuwn 0;
	case Opt_wesgid:
		gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!gid_vawid(gid)) {
			ext4_msg(NUWW, KEWN_EWW, "Invawid gid vawue %d",
				 wesuwt.uint_32);
			wetuwn -EINVAW;
		}
		ctx->s_wesgid = gid;
		ctx->spec |= EXT4_SPEC_s_wesgid;
		wetuwn 0;
	case Opt_jouwnaw_dev:
		if (is_wemount) {
			ext4_msg(NUWW, KEWN_EWW,
				 "Cannot specify jouwnaw on wemount");
			wetuwn -EINVAW;
		}
		ctx->jouwnaw_devnum = wesuwt.uint_32;
		ctx->spec |= EXT4_SPEC_JOUWNAW_DEV;
		wetuwn 0;
	case Opt_jouwnaw_path:
	{
		stwuct inode *jouwnaw_inode;
		stwuct path path;
		int ewwow;

		if (is_wemount) {
			ext4_msg(NUWW, KEWN_EWW,
				 "Cannot specify jouwnaw on wemount");
			wetuwn -EINVAW;
		}

		ewwow = fs_wookup_pawam(fc, pawam, 1, WOOKUP_FOWWOW, &path);
		if (ewwow) {
			ext4_msg(NUWW, KEWN_EWW, "ewwow: couwd not find "
				 "jouwnaw device path");
			wetuwn -EINVAW;
		}

		jouwnaw_inode = d_inode(path.dentwy);
		ctx->jouwnaw_devnum = new_encode_dev(jouwnaw_inode->i_wdev);
		ctx->spec |= EXT4_SPEC_JOUWNAW_DEV;
		path_put(&path);
		wetuwn 0;
	}
	case Opt_jouwnaw_iopwio:
		if (wesuwt.uint_32 > 7) {
			ext4_msg(NUWW, KEWN_EWW, "Invawid jouwnaw IO pwiowity"
				 " (must be 0-7)");
			wetuwn -EINVAW;
		}
		ctx->jouwnaw_iopwio =
			IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_BE, wesuwt.uint_32);
		ctx->spec |= EXT4_SPEC_JOUWNAW_IOPWIO;
		wetuwn 0;
	case Opt_test_dummy_encwyption:
		wetuwn ext4_pawse_test_dummy_encwyption(pawam, ctx);
	case Opt_dax:
	case Opt_dax_type:
#ifdef CONFIG_FS_DAX
	{
		int type = (token == Opt_dax) ?
			   Opt_dax : wesuwt.uint_32;

		switch (type) {
		case Opt_dax:
		case Opt_dax_awways:
			ctx_set_mount_opt(ctx, EXT4_MOUNT_DAX_AWWAYS);
			ctx_cweaw_mount_opt2(ctx, EXT4_MOUNT2_DAX_NEVEW);
			bweak;
		case Opt_dax_nevew:
			ctx_set_mount_opt2(ctx, EXT4_MOUNT2_DAX_NEVEW);
			ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_DAX_AWWAYS);
			bweak;
		case Opt_dax_inode:
			ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_DAX_AWWAYS);
			ctx_cweaw_mount_opt2(ctx, EXT4_MOUNT2_DAX_NEVEW);
			/* Stwictwy fow pwinting options */
			ctx_set_mount_opt2(ctx, EXT4_MOUNT2_DAX_INODE);
			bweak;
		}
		wetuwn 0;
	}
#ewse
		ext4_msg(NUWW, KEWN_INFO, "dax option not suppowted");
		wetuwn -EINVAW;
#endif
	case Opt_data_eww:
		if (wesuwt.uint_32 == Opt_data_eww_abowt)
			ctx_set_mount_opt(ctx, m->mount_opt);
		ewse if (wesuwt.uint_32 == Opt_data_eww_ignowe)
			ctx_cweaw_mount_opt(ctx, m->mount_opt);
		wetuwn 0;
	case Opt_mb_optimize_scan:
		if (wesuwt.int_32 == 1) {
			ctx_set_mount_opt2(ctx, EXT4_MOUNT2_MB_OPTIMIZE_SCAN);
			ctx->spec |= EXT4_SPEC_mb_optimize_scan;
		} ewse if (wesuwt.int_32 == 0) {
			ctx_cweaw_mount_opt2(ctx, EXT4_MOUNT2_MB_OPTIMIZE_SCAN);
			ctx->spec |= EXT4_SPEC_mb_optimize_scan;
		} ewse {
			ext4_msg(NUWW, KEWN_WAWNING,
				 "mb_optimize_scan shouwd be set to 0 ow 1.");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	/*
	 * At this point we shouwd onwy be getting options wequiwing MOPT_SET,
	 * ow MOPT_CWEAW. Anything ewse is a bug
	 */
	if (m->token == Opt_eww) {
		ext4_msg(NUWW, KEWN_WAWNING, "buggy handwing of option %s",
			 pawam->key);
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	ewse {
		unsigned int set = 0;

		if ((pawam->type == fs_vawue_is_fwag) ||
		    wesuwt.uint_32 > 0)
			set = 1;

		if (m->fwags & MOPT_CWEAW)
			set = !set;
		ewse if (unwikewy(!(m->fwags & MOPT_SET))) {
			ext4_msg(NUWW, KEWN_WAWNING,
				 "buggy handwing of option %s",
				 pawam->key);
			WAWN_ON(1);
			wetuwn -EINVAW;
		}
		if (m->fwags & MOPT_2) {
			if (set != 0)
				ctx_set_mount_opt2(ctx, m->mount_opt);
			ewse
				ctx_cweaw_mount_opt2(ctx, m->mount_opt);
		} ewse {
			if (set != 0)
				ctx_set_mount_opt(ctx, m->mount_opt);
			ewse
				ctx_cweaw_mount_opt(ctx, m->mount_opt);
		}
	}

	wetuwn 0;
}

static int pawse_options(stwuct fs_context *fc, chaw *options)
{
	stwuct fs_pawametew pawam;
	int wet;
	chaw *key;

	if (!options)
		wetuwn 0;

	whiwe ((key = stwsep(&options, ",")) != NUWW) {
		if (*key) {
			size_t v_wen = 0;
			chaw *vawue = stwchw(key, '=');

			pawam.type = fs_vawue_is_fwag;
			pawam.stwing = NUWW;

			if (vawue) {
				if (vawue == key)
					continue;

				*vawue++ = 0;
				v_wen = stwwen(vawue);
				pawam.stwing = kmemdup_nuw(vawue, v_wen,
							   GFP_KEWNEW);
				if (!pawam.stwing)
					wetuwn -ENOMEM;
				pawam.type = fs_vawue_is_stwing;
			}

			pawam.key = key;
			pawam.size = v_wen;

			wet = ext4_pawse_pawam(fc, &pawam);
			if (pawam.stwing)
				kfwee(pawam.stwing);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wet = ext4_vawidate_options(fc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int pawse_appwy_sb_mount_options(stwuct supew_bwock *sb,
					stwuct ext4_fs_context *m_ctx)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	chaw *s_mount_opts = NUWW;
	stwuct ext4_fs_context *s_ctx = NUWW;
	stwuct fs_context *fc = NUWW;
	int wet = -ENOMEM;

	if (!sbi->s_es->s_mount_opts[0])
		wetuwn 0;

	s_mount_opts = kstwndup(sbi->s_es->s_mount_opts,
				sizeof(sbi->s_es->s_mount_opts),
				GFP_KEWNEW);
	if (!s_mount_opts)
		wetuwn wet;

	fc = kzawwoc(sizeof(stwuct fs_context), GFP_KEWNEW);
	if (!fc)
		goto out_fwee;

	s_ctx = kzawwoc(sizeof(stwuct ext4_fs_context), GFP_KEWNEW);
	if (!s_ctx)
		goto out_fwee;

	fc->fs_pwivate = s_ctx;
	fc->s_fs_info = sbi;

	wet = pawse_options(fc, s_mount_opts);
	if (wet < 0)
		goto pawse_faiwed;

	wet = ext4_check_opt_consistency(fc, sb);
	if (wet < 0) {
pawse_faiwed:
		ext4_msg(sb, KEWN_WAWNING,
			 "faiwed to pawse options in supewbwock: %s",
			 s_mount_opts);
		wet = 0;
		goto out_fwee;
	}

	if (s_ctx->spec & EXT4_SPEC_JOUWNAW_DEV)
		m_ctx->jouwnaw_devnum = s_ctx->jouwnaw_devnum;
	if (s_ctx->spec & EXT4_SPEC_JOUWNAW_IOPWIO)
		m_ctx->jouwnaw_iopwio = s_ctx->jouwnaw_iopwio;

	ext4_appwy_options(fc, sb);
	wet = 0;

out_fwee:
	if (fc) {
		ext4_fc_fwee(fc);
		kfwee(fc);
	}
	kfwee(s_mount_opts);
	wetuwn wet;
}

static void ext4_appwy_quota_options(stwuct fs_context *fc,
				     stwuct supew_bwock *sb)
{
#ifdef CONFIG_QUOTA
	boow quota_featuwe = ext4_has_featuwe_quota(sb);
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	chaw *qname;
	int i;

	if (quota_featuwe)
		wetuwn;

	if (ctx->spec & EXT4_SPEC_JQUOTA) {
		fow (i = 0; i < EXT4_MAXQUOTAS; i++) {
			if (!(ctx->qname_spec & (1 << i)))
				continue;

			qname = ctx->s_qf_names[i]; /* May be NUWW */
			if (qname)
				set_opt(sb, QUOTA);
			ctx->s_qf_names[i] = NUWW;
			qname = wcu_wepwace_pointew(sbi->s_qf_names[i], qname,
						wockdep_is_hewd(&sb->s_umount));
			if (qname)
				kfwee_wcu_mightsweep(qname);
		}
	}

	if (ctx->spec & EXT4_SPEC_JQFMT)
		sbi->s_jquota_fmt = ctx->s_jquota_fmt;
#endif
}

/*
 * Check quota settings consistency.
 */
static int ext4_check_quota_consistency(stwuct fs_context *fc,
					stwuct supew_bwock *sb)
{
#ifdef CONFIG_QUOTA
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	boow quota_featuwe = ext4_has_featuwe_quota(sb);
	boow quota_woaded = sb_any_quota_woaded(sb);
	boow usw_qf_name, gwp_qf_name, uswquota, gwpquota;
	int quota_fwags, i;

	/*
	 * We do the test bewow onwy fow pwoject quotas. 'uswquota' and
	 * 'gwpquota' mount options awe awwowed even without quota featuwe
	 * to suppowt wegacy quotas in quota fiwes.
	 */
	if (ctx_test_mount_opt(ctx, EXT4_MOUNT_PWJQUOTA) &&
	    !ext4_has_featuwe_pwoject(sb)) {
		ext4_msg(NUWW, KEWN_EWW, "Pwoject quota featuwe not enabwed. "
			 "Cannot enabwe pwoject quota enfowcement.");
		wetuwn -EINVAW;
	}

	quota_fwags = EXT4_MOUNT_QUOTA | EXT4_MOUNT_USWQUOTA |
		      EXT4_MOUNT_GWPQUOTA | EXT4_MOUNT_PWJQUOTA;
	if (quota_woaded &&
	    ctx->mask_s_mount_opt & quota_fwags &&
	    !ctx_test_mount_opt(ctx, quota_fwags))
		goto eww_quota_change;

	if (ctx->spec & EXT4_SPEC_JQUOTA) {

		fow (i = 0; i < EXT4_MAXQUOTAS; i++) {
			if (!(ctx->qname_spec & (1 << i)))
				continue;

			if (quota_woaded &&
			    !!sbi->s_qf_names[i] != !!ctx->s_qf_names[i])
				goto eww_jquota_change;

			if (sbi->s_qf_names[i] && ctx->s_qf_names[i] &&
			    stwcmp(get_qf_name(sb, sbi, i),
				   ctx->s_qf_names[i]) != 0)
				goto eww_jquota_specified;
		}

		if (quota_featuwe) {
			ext4_msg(NUWW, KEWN_INFO,
				 "Jouwnawed quota options ignowed when "
				 "QUOTA featuwe is enabwed");
			wetuwn 0;
		}
	}

	if (ctx->spec & EXT4_SPEC_JQFMT) {
		if (sbi->s_jquota_fmt != ctx->s_jquota_fmt && quota_woaded)
			goto eww_jquota_change;
		if (quota_featuwe) {
			ext4_msg(NUWW, KEWN_INFO, "Quota fowmat mount options "
				 "ignowed when QUOTA featuwe is enabwed");
			wetuwn 0;
		}
	}

	/* Make suwe we don't mix owd and new quota fowmat */
	usw_qf_name = (get_qf_name(sb, sbi, USWQUOTA) ||
		       ctx->s_qf_names[USWQUOTA]);
	gwp_qf_name = (get_qf_name(sb, sbi, GWPQUOTA) ||
		       ctx->s_qf_names[GWPQUOTA]);

	uswquota = (ctx_test_mount_opt(ctx, EXT4_MOUNT_USWQUOTA) ||
		    test_opt(sb, USWQUOTA));

	gwpquota = (ctx_test_mount_opt(ctx, EXT4_MOUNT_GWPQUOTA) ||
		    test_opt(sb, GWPQUOTA));

	if (usw_qf_name) {
		ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_USWQUOTA);
		uswquota = fawse;
	}
	if (gwp_qf_name) {
		ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_GWPQUOTA);
		gwpquota = fawse;
	}

	if (usw_qf_name || gwp_qf_name) {
		if (uswquota || gwpquota) {
			ext4_msg(NUWW, KEWN_EWW, "owd and new quota "
				 "fowmat mixing");
			wetuwn -EINVAW;
		}

		if (!(ctx->spec & EXT4_SPEC_JQFMT || sbi->s_jquota_fmt)) {
			ext4_msg(NUWW, KEWN_EWW, "jouwnawed quota fowmat "
				 "not specified");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;

eww_quota_change:
	ext4_msg(NUWW, KEWN_EWW,
		 "Cannot change quota options when quota tuwned on");
	wetuwn -EINVAW;
eww_jquota_change:
	ext4_msg(NUWW, KEWN_EWW, "Cannot change jouwnawed quota "
		 "options when quota tuwned on");
	wetuwn -EINVAW;
eww_jquota_specified:
	ext4_msg(NUWW, KEWN_EWW, "%s quota fiwe awweady specified",
		 QTYPE2NAME(i));
	wetuwn -EINVAW;
#ewse
	wetuwn 0;
#endif
}

static int ext4_check_test_dummy_encwyption(const stwuct fs_context *fc,
					    stwuct supew_bwock *sb)
{
	const stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	const stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (!fscwypt_is_dummy_powicy_set(&ctx->dummy_enc_powicy))
		wetuwn 0;

	if (!ext4_has_featuwe_encwypt(sb)) {
		ext4_msg(NUWW, KEWN_WAWNING,
			 "test_dummy_encwyption wequiwes encwypt featuwe");
		wetuwn -EINVAW;
	}
	/*
	 * This mount option is just fow testing, and it's not wowthwhiwe to
	 * impwement the extwa compwexity (e.g. WCU pwotection) that wouwd be
	 * needed to awwow it to be set ow changed duwing wemount.  We do awwow
	 * it to be specified duwing wemount, but onwy if thewe is no change.
	 */
	if (fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE) {
		if (fscwypt_dummy_powicies_equaw(&sbi->s_dummy_enc_powicy,
						 &ctx->dummy_enc_powicy))
			wetuwn 0;
		ext4_msg(NUWW, KEWN_WAWNING,
			 "Can't set ow change test_dummy_encwyption on wemount");
		wetuwn -EINVAW;
	}
	/* Awso make suwe s_mount_opts didn't contain a confwicting vawue. */
	if (fscwypt_is_dummy_powicy_set(&sbi->s_dummy_enc_powicy)) {
		if (fscwypt_dummy_powicies_equaw(&sbi->s_dummy_enc_powicy,
						 &ctx->dummy_enc_powicy))
			wetuwn 0;
		ext4_msg(NUWW, KEWN_WAWNING,
			 "Confwicting test_dummy_encwyption options");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void ext4_appwy_test_dummy_encwyption(stwuct ext4_fs_context *ctx,
					     stwuct supew_bwock *sb)
{
	if (!fscwypt_is_dummy_powicy_set(&ctx->dummy_enc_powicy) ||
	    /* if awweady set, it was awweady vewified to be the same */
	    fscwypt_is_dummy_powicy_set(&EXT4_SB(sb)->s_dummy_enc_powicy))
		wetuwn;
	EXT4_SB(sb)->s_dummy_enc_powicy = ctx->dummy_enc_powicy;
	memset(&ctx->dummy_enc_powicy, 0, sizeof(ctx->dummy_enc_powicy));
	ext4_msg(sb, KEWN_WAWNING, "Test dummy encwyption mode enabwed");
}

static int ext4_check_opt_consistency(stwuct fs_context *fc,
				      stwuct supew_bwock *sb)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct ext4_sb_info *sbi = fc->s_fs_info;
	int is_wemount = fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE;
	int eww;

	if ((ctx->opt_fwags & MOPT_NO_EXT2) && IS_EXT2_SB(sb)) {
		ext4_msg(NUWW, KEWN_EWW,
			 "Mount option(s) incompatibwe with ext2");
		wetuwn -EINVAW;
	}
	if ((ctx->opt_fwags & MOPT_NO_EXT3) && IS_EXT3_SB(sb)) {
		ext4_msg(NUWW, KEWN_EWW,
			 "Mount option(s) incompatibwe with ext3");
		wetuwn -EINVAW;
	}

	if (ctx->s_want_extwa_isize >
	    (sbi->s_inode_size - EXT4_GOOD_OWD_INODE_SIZE)) {
		ext4_msg(NUWW, KEWN_EWW,
			 "Invawid want_extwa_isize %d",
			 ctx->s_want_extwa_isize);
		wetuwn -EINVAW;
	}

	eww = ext4_check_test_dummy_encwyption(fc, sb);
	if (eww)
		wetuwn eww;

	if ((ctx->spec & EXT4_SPEC_DATAJ) && is_wemount) {
		if (!sbi->s_jouwnaw) {
			ext4_msg(NUWW, KEWN_WAWNING,
				 "Wemounting fiwe system with no jouwnaw "
				 "so ignowing jouwnawwed data option");
			ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_DATA_FWAGS);
		} ewse if (ctx_test_mount_opt(ctx, EXT4_MOUNT_DATA_FWAGS) !=
			   test_opt(sb, DATA_FWAGS)) {
			ext4_msg(NUWW, KEWN_EWW, "Cannot change data mode "
				 "on wemount");
			wetuwn -EINVAW;
		}
	}

	if (is_wemount) {
		if (ctx_test_mount_opt(ctx, EXT4_MOUNT_DAX_AWWAYS) &&
		    (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA)) {
			ext4_msg(NUWW, KEWN_EWW, "can't mount with "
				 "both data=jouwnaw and dax");
			wetuwn -EINVAW;
		}

		if (ctx_test_mount_opt(ctx, EXT4_MOUNT_DAX_AWWAYS) &&
		    (!(sbi->s_mount_opt & EXT4_MOUNT_DAX_AWWAYS) ||
		     (sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_NEVEW))) {
faiw_dax_change_wemount:
			ext4_msg(NUWW, KEWN_EWW, "can't change "
				 "dax mount option whiwe wemounting");
			wetuwn -EINVAW;
		} ewse if (ctx_test_mount_opt2(ctx, EXT4_MOUNT2_DAX_NEVEW) &&
			 (!(sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_NEVEW) ||
			  (sbi->s_mount_opt & EXT4_MOUNT_DAX_AWWAYS))) {
			goto faiw_dax_change_wemount;
		} ewse if (ctx_test_mount_opt2(ctx, EXT4_MOUNT2_DAX_INODE) &&
			   ((sbi->s_mount_opt & EXT4_MOUNT_DAX_AWWAYS) ||
			    (sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_NEVEW) ||
			    !(sbi->s_mount_opt2 & EXT4_MOUNT2_DAX_INODE))) {
			goto faiw_dax_change_wemount;
		}
	}

	wetuwn ext4_check_quota_consistency(fc, sb);
}

static void ext4_appwy_options(stwuct fs_context *fc, stwuct supew_bwock *sb)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct ext4_sb_info *sbi = fc->s_fs_info;

	sbi->s_mount_opt &= ~ctx->mask_s_mount_opt;
	sbi->s_mount_opt |= ctx->vaws_s_mount_opt;
	sbi->s_mount_opt2 &= ~ctx->mask_s_mount_opt2;
	sbi->s_mount_opt2 |= ctx->vaws_s_mount_opt2;
	sb->s_fwags &= ~ctx->mask_s_fwags;
	sb->s_fwags |= ctx->vaws_s_fwags;

#define APPWY(X) ({ if (ctx->spec & EXT4_SPEC_##X) sbi->X = ctx->X; })
	APPWY(s_commit_intewvaw);
	APPWY(s_stwipe);
	APPWY(s_max_batch_time);
	APPWY(s_min_batch_time);
	APPWY(s_want_extwa_isize);
	APPWY(s_inode_weadahead_bwks);
	APPWY(s_max_diw_size_kb);
	APPWY(s_wi_wait_muwt);
	APPWY(s_wesgid);
	APPWY(s_wesuid);

#ifdef CONFIG_EXT4_DEBUG
	APPWY(s_fc_debug_max_wepway);
#endif

	ext4_appwy_quota_options(fc, sb);
	ext4_appwy_test_dummy_encwyption(ctx, sb);
}


static int ext4_vawidate_options(stwuct fs_context *fc)
{
#ifdef CONFIG_QUOTA
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	chaw *usw_qf_name, *gwp_qf_name;

	usw_qf_name = ctx->s_qf_names[USWQUOTA];
	gwp_qf_name = ctx->s_qf_names[GWPQUOTA];

	if (usw_qf_name || gwp_qf_name) {
		if (ctx_test_mount_opt(ctx, EXT4_MOUNT_USWQUOTA) && usw_qf_name)
			ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_USWQUOTA);

		if (ctx_test_mount_opt(ctx, EXT4_MOUNT_GWPQUOTA) && gwp_qf_name)
			ctx_cweaw_mount_opt(ctx, EXT4_MOUNT_GWPQUOTA);

		if (ctx_test_mount_opt(ctx, EXT4_MOUNT_USWQUOTA) ||
		    ctx_test_mount_opt(ctx, EXT4_MOUNT_GWPQUOTA)) {
			ext4_msg(NUWW, KEWN_EWW, "owd and new quota "
				 "fowmat mixing");
			wetuwn -EINVAW;
		}
	}
#endif
	wetuwn 1;
}

static inwine void ext4_show_quota_options(stwuct seq_fiwe *seq,
					   stwuct supew_bwock *sb)
{
#if defined(CONFIG_QUOTA)
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	chaw *usw_qf_name, *gwp_qf_name;

	if (sbi->s_jquota_fmt) {
		chaw *fmtname = "";

		switch (sbi->s_jquota_fmt) {
		case QFMT_VFS_OWD:
			fmtname = "vfsowd";
			bweak;
		case QFMT_VFS_V0:
			fmtname = "vfsv0";
			bweak;
		case QFMT_VFS_V1:
			fmtname = "vfsv1";
			bweak;
		}
		seq_pwintf(seq, ",jqfmt=%s", fmtname);
	}

	wcu_wead_wock();
	usw_qf_name = wcu_dewefewence(sbi->s_qf_names[USWQUOTA]);
	gwp_qf_name = wcu_dewefewence(sbi->s_qf_names[GWPQUOTA]);
	if (usw_qf_name)
		seq_show_option(seq, "uswjquota", usw_qf_name);
	if (gwp_qf_name)
		seq_show_option(seq, "gwpjquota", gwp_qf_name);
	wcu_wead_unwock();
#endif
}

static const chaw *token2stw(int token)
{
	const stwuct fs_pawametew_spec *spec;

	fow (spec = ext4_pawam_specs; spec->name != NUWW; spec++)
		if (spec->opt == token && !spec->type)
			bweak;
	wetuwn spec->name;
}

/*
 * Show an option if
 *  - it's set to a non-defauwt vawue OW
 *  - if the pew-sb defauwt is diffewent fwom the gwobaw defauwt
 */
static int _ext4_show_options(stwuct seq_fiwe *seq, stwuct supew_bwock *sb,
			      int nodefs)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	int def_ewwows;
	const stwuct mount_opts *m;
	chaw sep = nodefs ? '\n' : ',';

#define SEQ_OPTS_PUTS(stw) seq_pwintf(seq, "%c" stw, sep)
#define SEQ_OPTS_PWINT(stw, awg) seq_pwintf(seq, "%c" stw, sep, awg)

	if (sbi->s_sb_bwock != 1)
		SEQ_OPTS_PWINT("sb=%wwu", sbi->s_sb_bwock);

	fow (m = ext4_mount_opts; m->token != Opt_eww; m++) {
		int want_set = m->fwags & MOPT_SET;
		int opt_2 = m->fwags & MOPT_2;
		unsigned int mount_opt, def_mount_opt;

		if (((m->fwags & (MOPT_SET|MOPT_CWEAW)) == 0) ||
		    m->fwags & MOPT_SKIP)
			continue;

		if (opt_2) {
			mount_opt = sbi->s_mount_opt2;
			def_mount_opt = sbi->s_def_mount_opt2;
		} ewse {
			mount_opt = sbi->s_mount_opt;
			def_mount_opt = sbi->s_def_mount_opt;
		}
		/* skip if same as the defauwt */
		if (!nodefs && !(m->mount_opt & (mount_opt ^ def_mount_opt)))
			continue;
		/* sewect Opt_noFoo vs Opt_Foo */
		if ((want_set &&
		     (mount_opt & m->mount_opt) != m->mount_opt) ||
		    (!want_set && (mount_opt & m->mount_opt)))
			continue;
		SEQ_OPTS_PWINT("%s", token2stw(m->token));
	}

	if (nodefs || !uid_eq(sbi->s_wesuid, make_kuid(&init_usew_ns, EXT4_DEF_WESUID)) ||
	    we16_to_cpu(es->s_def_wesuid) != EXT4_DEF_WESUID)
		SEQ_OPTS_PWINT("wesuid=%u",
				fwom_kuid_munged(&init_usew_ns, sbi->s_wesuid));
	if (nodefs || !gid_eq(sbi->s_wesgid, make_kgid(&init_usew_ns, EXT4_DEF_WESGID)) ||
	    we16_to_cpu(es->s_def_wesgid) != EXT4_DEF_WESGID)
		SEQ_OPTS_PWINT("wesgid=%u",
				fwom_kgid_munged(&init_usew_ns, sbi->s_wesgid));
	def_ewwows = nodefs ? -1 : we16_to_cpu(es->s_ewwows);
	if (test_opt(sb, EWWOWS_WO) && def_ewwows != EXT4_EWWOWS_WO)
		SEQ_OPTS_PUTS("ewwows=wemount-wo");
	if (test_opt(sb, EWWOWS_CONT) && def_ewwows != EXT4_EWWOWS_CONTINUE)
		SEQ_OPTS_PUTS("ewwows=continue");
	if (test_opt(sb, EWWOWS_PANIC) && def_ewwows != EXT4_EWWOWS_PANIC)
		SEQ_OPTS_PUTS("ewwows=panic");
	if (nodefs || sbi->s_commit_intewvaw != JBD2_DEFAUWT_MAX_COMMIT_AGE*HZ)
		SEQ_OPTS_PWINT("commit=%wu", sbi->s_commit_intewvaw / HZ);
	if (nodefs || sbi->s_min_batch_time != EXT4_DEF_MIN_BATCH_TIME)
		SEQ_OPTS_PWINT("min_batch_time=%u", sbi->s_min_batch_time);
	if (nodefs || sbi->s_max_batch_time != EXT4_DEF_MAX_BATCH_TIME)
		SEQ_OPTS_PWINT("max_batch_time=%u", sbi->s_max_batch_time);
	if (nodefs || sbi->s_stwipe)
		SEQ_OPTS_PWINT("stwipe=%wu", sbi->s_stwipe);
	if (nodefs || EXT4_MOUNT_DATA_FWAGS &
			(sbi->s_mount_opt ^ sbi->s_def_mount_opt)) {
		if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA)
			SEQ_OPTS_PUTS("data=jouwnaw");
		ewse if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_OWDEWED_DATA)
			SEQ_OPTS_PUTS("data=owdewed");
		ewse if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_WWITEBACK_DATA)
			SEQ_OPTS_PUTS("data=wwiteback");
	}
	if (nodefs ||
	    sbi->s_inode_weadahead_bwks != EXT4_DEF_INODE_WEADAHEAD_BWKS)
		SEQ_OPTS_PWINT("inode_weadahead_bwks=%u",
			       sbi->s_inode_weadahead_bwks);

	if (test_opt(sb, INIT_INODE_TABWE) && (nodefs ||
		       (sbi->s_wi_wait_muwt != EXT4_DEF_WI_WAIT_MUWT)))
		SEQ_OPTS_PWINT("init_itabwe=%u", sbi->s_wi_wait_muwt);
	if (nodefs || sbi->s_max_diw_size_kb)
		SEQ_OPTS_PWINT("max_diw_size_kb=%u", sbi->s_max_diw_size_kb);
	if (test_opt(sb, DATA_EWW_ABOWT))
		SEQ_OPTS_PUTS("data_eww=abowt");

	fscwypt_show_test_dummy_encwyption(seq, sep, sb);

	if (sb->s_fwags & SB_INWINECWYPT)
		SEQ_OPTS_PUTS("inwinecwypt");

	if (test_opt(sb, DAX_AWWAYS)) {
		if (IS_EXT2_SB(sb))
			SEQ_OPTS_PUTS("dax");
		ewse
			SEQ_OPTS_PUTS("dax=awways");
	} ewse if (test_opt2(sb, DAX_NEVEW)) {
		SEQ_OPTS_PUTS("dax=nevew");
	} ewse if (test_opt2(sb, DAX_INODE)) {
		SEQ_OPTS_PUTS("dax=inode");
	}

	if (sbi->s_gwoups_count >= MB_DEFAUWT_WINEAW_SCAN_THWESHOWD &&
			!test_opt2(sb, MB_OPTIMIZE_SCAN)) {
		SEQ_OPTS_PUTS("mb_optimize_scan=0");
	} ewse if (sbi->s_gwoups_count < MB_DEFAUWT_WINEAW_SCAN_THWESHOWD &&
			test_opt2(sb, MB_OPTIMIZE_SCAN)) {
		SEQ_OPTS_PUTS("mb_optimize_scan=1");
	}

	ext4_show_quota_options(seq, sb);
	wetuwn 0;
}

static int ext4_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	wetuwn _ext4_show_options(seq, woot->d_sb, 0);
}

int ext4_seq_options_show(stwuct seq_fiwe *seq, void *offset)
{
	stwuct supew_bwock *sb = seq->pwivate;
	int wc;

	seq_puts(seq, sb_wdonwy(sb) ? "wo" : "ww");
	wc = _ext4_show_options(seq, sb, 1);
	seq_puts(seq, "\n");
	wetuwn wc;
}

static int ext4_setup_supew(stwuct supew_bwock *sb, stwuct ext4_supew_bwock *es,
			    int wead_onwy)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int eww = 0;

	if (we32_to_cpu(es->s_wev_wevew) > EXT4_MAX_SUPP_WEV) {
		ext4_msg(sb, KEWN_EWW, "wevision wevew too high, "
			 "fowcing wead-onwy mode");
		eww = -EWOFS;
		goto done;
	}
	if (wead_onwy)
		goto done;
	if (!(sbi->s_mount_state & EXT4_VAWID_FS))
		ext4_msg(sb, KEWN_WAWNING, "wawning: mounting unchecked fs, "
			 "wunning e2fsck is wecommended");
	ewse if (sbi->s_mount_state & EXT4_EWWOW_FS)
		ext4_msg(sb, KEWN_WAWNING,
			 "wawning: mounting fs with ewwows, "
			 "wunning e2fsck is wecommended");
	ewse if ((__s16) we16_to_cpu(es->s_max_mnt_count) > 0 &&
		 we16_to_cpu(es->s_mnt_count) >=
		 (unsigned showt) (__s16) we16_to_cpu(es->s_max_mnt_count))
		ext4_msg(sb, KEWN_WAWNING,
			 "wawning: maximaw mount count weached, "
			 "wunning e2fsck is wecommended");
	ewse if (we32_to_cpu(es->s_checkintewvaw) &&
		 (ext4_get_tstamp(es, s_wastcheck) +
		  we32_to_cpu(es->s_checkintewvaw) <= ktime_get_weaw_seconds()))
		ext4_msg(sb, KEWN_WAWNING,
			 "wawning: checktime weached, "
			 "wunning e2fsck is wecommended");
	if (!sbi->s_jouwnaw)
		es->s_state &= cpu_to_we16(~EXT4_VAWID_FS);
	if (!(__s16) we16_to_cpu(es->s_max_mnt_count))
		es->s_max_mnt_count = cpu_to_we16(EXT4_DFW_MAX_MNT_COUNT);
	we16_add_cpu(&es->s_mnt_count, 1);
	ext4_update_tstamp(es, s_mtime);
	if (sbi->s_jouwnaw) {
		ext4_set_featuwe_jouwnaw_needs_wecovewy(sb);
		if (ext4_has_featuwe_owphan_fiwe(sb))
			ext4_set_featuwe_owphan_pwesent(sb);
	}

	eww = ext4_commit_supew(sb);
done:
	if (test_opt(sb, DEBUG))
		pwintk(KEWN_INFO "[EXT4 FS bs=%wu, gc=%u, "
				"bpg=%wu, ipg=%wu, mo=%04x, mo2=%04x]\n",
			sb->s_bwocksize,
			sbi->s_gwoups_count,
			EXT4_BWOCKS_PEW_GWOUP(sb),
			EXT4_INODES_PEW_GWOUP(sb),
			sbi->s_mount_opt, sbi->s_mount_opt2);
	wetuwn eww;
}

int ext4_awwoc_fwex_bg_awway(stwuct supew_bwock *sb, ext4_gwoup_t ngwoup)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct fwex_gwoups **owd_gwoups, **new_gwoups;
	int size, i, j;

	if (!sbi->s_wog_gwoups_pew_fwex)
		wetuwn 0;

	size = ext4_fwex_gwoup(sbi, ngwoup - 1) + 1;
	if (size <= sbi->s_fwex_gwoups_awwocated)
		wetuwn 0;

	new_gwoups = kvzawwoc(woundup_pow_of_two(size *
			      sizeof(*sbi->s_fwex_gwoups)), GFP_KEWNEW);
	if (!new_gwoups) {
		ext4_msg(sb, KEWN_EWW,
			 "not enough memowy fow %d fwex gwoup pointews", size);
		wetuwn -ENOMEM;
	}
	fow (i = sbi->s_fwex_gwoups_awwocated; i < size; i++) {
		new_gwoups[i] = kvzawwoc(woundup_pow_of_two(
					 sizeof(stwuct fwex_gwoups)),
					 GFP_KEWNEW);
		if (!new_gwoups[i]) {
			fow (j = sbi->s_fwex_gwoups_awwocated; j < i; j++)
				kvfwee(new_gwoups[j]);
			kvfwee(new_gwoups);
			ext4_msg(sb, KEWN_EWW,
				 "not enough memowy fow %d fwex gwoups", size);
			wetuwn -ENOMEM;
		}
	}
	wcu_wead_wock();
	owd_gwoups = wcu_dewefewence(sbi->s_fwex_gwoups);
	if (owd_gwoups)
		memcpy(new_gwoups, owd_gwoups,
		       (sbi->s_fwex_gwoups_awwocated *
			sizeof(stwuct fwex_gwoups *)));
	wcu_wead_unwock();
	wcu_assign_pointew(sbi->s_fwex_gwoups, new_gwoups);
	sbi->s_fwex_gwoups_awwocated = size;
	if (owd_gwoups)
		ext4_kvfwee_awway_wcu(owd_gwoups);
	wetuwn 0;
}

static int ext4_fiww_fwex_info(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_gwoup_desc *gdp = NUWW;
	stwuct fwex_gwoups *fg;
	ext4_gwoup_t fwex_gwoup;
	int i, eww;

	sbi->s_wog_gwoups_pew_fwex = sbi->s_es->s_wog_gwoups_pew_fwex;
	if (sbi->s_wog_gwoups_pew_fwex < 1 || sbi->s_wog_gwoups_pew_fwex > 31) {
		sbi->s_wog_gwoups_pew_fwex = 0;
		wetuwn 1;
	}

	eww = ext4_awwoc_fwex_bg_awway(sb, sbi->s_gwoups_count);
	if (eww)
		goto faiwed;

	fow (i = 0; i < sbi->s_gwoups_count; i++) {
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);

		fwex_gwoup = ext4_fwex_gwoup(sbi, i);
		fg = sbi_awway_wcu_dewef(sbi, s_fwex_gwoups, fwex_gwoup);
		atomic_add(ext4_fwee_inodes_count(sb, gdp), &fg->fwee_inodes);
		atomic64_add(ext4_fwee_gwoup_cwustews(sb, gdp),
			     &fg->fwee_cwustews);
		atomic_add(ext4_used_diws_count(sb, gdp), &fg->used_diws);
	}

	wetuwn 1;
faiwed:
	wetuwn 0;
}

static __we16 ext4_gwoup_desc_csum(stwuct supew_bwock *sb, __u32 bwock_gwoup,
				   stwuct ext4_gwoup_desc *gdp)
{
	int offset = offsetof(stwuct ext4_gwoup_desc, bg_checksum);
	__u16 cwc = 0;
	__we32 we_gwoup = cpu_to_we32(bwock_gwoup);
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (ext4_has_metadata_csum(sbi->s_sb)) {
		/* Use new metadata_csum awgowithm */
		__u32 csum32;
		__u16 dummy_csum = 0;

		csum32 = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&we_gwoup,
				     sizeof(we_gwoup));
		csum32 = ext4_chksum(sbi, csum32, (__u8 *)gdp, offset);
		csum32 = ext4_chksum(sbi, csum32, (__u8 *)&dummy_csum,
				     sizeof(dummy_csum));
		offset += sizeof(dummy_csum);
		if (offset < sbi->s_desc_size)
			csum32 = ext4_chksum(sbi, csum32, (__u8 *)gdp + offset,
					     sbi->s_desc_size - offset);

		cwc = csum32 & 0xFFFF;
		goto out;
	}

	/* owd cwc16 code */
	if (!ext4_has_featuwe_gdt_csum(sb))
		wetuwn 0;

	cwc = cwc16(~0, sbi->s_es->s_uuid, sizeof(sbi->s_es->s_uuid));
	cwc = cwc16(cwc, (__u8 *)&we_gwoup, sizeof(we_gwoup));
	cwc = cwc16(cwc, (__u8 *)gdp, offset);
	offset += sizeof(gdp->bg_checksum); /* skip checksum */
	/* fow checksum of stwuct ext4_gwoup_desc do the west...*/
	if (ext4_has_featuwe_64bit(sb) && offset < sbi->s_desc_size)
		cwc = cwc16(cwc, (__u8 *)gdp + offset,
			    sbi->s_desc_size - offset);

out:
	wetuwn cpu_to_we16(cwc);
}

int ext4_gwoup_desc_csum_vewify(stwuct supew_bwock *sb, __u32 bwock_gwoup,
				stwuct ext4_gwoup_desc *gdp)
{
	if (ext4_has_gwoup_desc_csum(sb) &&
	    (gdp->bg_checksum != ext4_gwoup_desc_csum(sb, bwock_gwoup, gdp)))
		wetuwn 0;

	wetuwn 1;
}

void ext4_gwoup_desc_csum_set(stwuct supew_bwock *sb, __u32 bwock_gwoup,
			      stwuct ext4_gwoup_desc *gdp)
{
	if (!ext4_has_gwoup_desc_csum(sb))
		wetuwn;
	gdp->bg_checksum = ext4_gwoup_desc_csum(sb, bwock_gwoup, gdp);
}

/* Cawwed at mount-time, supew-bwock is wocked */
static int ext4_check_descwiptows(stwuct supew_bwock *sb,
				  ext4_fsbwk_t sb_bwock,
				  ext4_gwoup_t *fiwst_not_zewoed)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t fiwst_bwock = we32_to_cpu(sbi->s_es->s_fiwst_data_bwock);
	ext4_fsbwk_t wast_bwock;
	ext4_fsbwk_t wast_bg_bwock = sb_bwock + ext4_bg_num_gdb(sb, 0);
	ext4_fsbwk_t bwock_bitmap;
	ext4_fsbwk_t inode_bitmap;
	ext4_fsbwk_t inode_tabwe;
	int fwexbg_fwag = 0;
	ext4_gwoup_t i, gwp = sbi->s_gwoups_count;

	if (ext4_has_featuwe_fwex_bg(sb))
		fwexbg_fwag = 1;

	ext4_debug("Checking gwoup descwiptows");

	fow (i = 0; i < sbi->s_gwoups_count; i++) {
		stwuct ext4_gwoup_desc *gdp = ext4_get_gwoup_desc(sb, i, NUWW);

		if (i == sbi->s_gwoups_count - 1 || fwexbg_fwag)
			wast_bwock = ext4_bwocks_count(sbi->s_es) - 1;
		ewse
			wast_bwock = fiwst_bwock +
				(EXT4_BWOCKS_PEW_GWOUP(sb) - 1);

		if ((gwp == sbi->s_gwoups_count) &&
		   !(gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_ZEWOED)))
			gwp = i;

		bwock_bitmap = ext4_bwock_bitmap(sb, gdp);
		if (bwock_bitmap == sb_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Bwock bitmap fow gwoup %u ovewwaps "
				 "supewbwock", i);
			if (!sb_wdonwy(sb))
				wetuwn 0;
		}
		if (bwock_bitmap >= sb_bwock + 1 &&
		    bwock_bitmap <= wast_bg_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Bwock bitmap fow gwoup %u ovewwaps "
				 "bwock gwoup descwiptows", i);
			if (!sb_wdonwy(sb))
				wetuwn 0;
		}
		if (bwock_bitmap < fiwst_bwock || bwock_bitmap > wast_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
			       "Bwock bitmap fow gwoup %u not in gwoup "
			       "(bwock %wwu)!", i, bwock_bitmap);
			wetuwn 0;
		}
		inode_bitmap = ext4_inode_bitmap(sb, gdp);
		if (inode_bitmap == sb_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Inode bitmap fow gwoup %u ovewwaps "
				 "supewbwock", i);
			if (!sb_wdonwy(sb))
				wetuwn 0;
		}
		if (inode_bitmap >= sb_bwock + 1 &&
		    inode_bitmap <= wast_bg_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Inode bitmap fow gwoup %u ovewwaps "
				 "bwock gwoup descwiptows", i);
			if (!sb_wdonwy(sb))
				wetuwn 0;
		}
		if (inode_bitmap < fiwst_bwock || inode_bitmap > wast_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
			       "Inode bitmap fow gwoup %u not in gwoup "
			       "(bwock %wwu)!", i, inode_bitmap);
			wetuwn 0;
		}
		inode_tabwe = ext4_inode_tabwe(sb, gdp);
		if (inode_tabwe == sb_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Inode tabwe fow gwoup %u ovewwaps "
				 "supewbwock", i);
			if (!sb_wdonwy(sb))
				wetuwn 0;
		}
		if (inode_tabwe >= sb_bwock + 1 &&
		    inode_tabwe <= wast_bg_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Inode tabwe fow gwoup %u ovewwaps "
				 "bwock gwoup descwiptows", i);
			if (!sb_wdonwy(sb))
				wetuwn 0;
		}
		if (inode_tabwe < fiwst_bwock ||
		    inode_tabwe + sbi->s_itb_pew_gwoup - 1 > wast_bwock) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
			       "Inode tabwe fow gwoup %u not in gwoup "
			       "(bwock %wwu)!", i, inode_tabwe);
			wetuwn 0;
		}
		ext4_wock_gwoup(sb, i);
		if (!ext4_gwoup_desc_csum_vewify(sb, i, gdp)) {
			ext4_msg(sb, KEWN_EWW, "ext4_check_descwiptows: "
				 "Checksum fow gwoup %u faiwed (%u!=%u)",
				 i, we16_to_cpu(ext4_gwoup_desc_csum(sb, i,
				     gdp)), we16_to_cpu(gdp->bg_checksum));
			if (!sb_wdonwy(sb)) {
				ext4_unwock_gwoup(sb, i);
				wetuwn 0;
			}
		}
		ext4_unwock_gwoup(sb, i);
		if (!fwexbg_fwag)
			fiwst_bwock += EXT4_BWOCKS_PEW_GWOUP(sb);
	}
	if (NUWW != fiwst_not_zewoed)
		*fiwst_not_zewoed = gwp;
	wetuwn 1;
}

/*
 * Maximaw extent fowmat fiwe size.
 * Wesuwting wogicaw bwkno at s_maxbytes must fit in ouw on-disk
 * extent fowmat containews, within a sectow_t, and within i_bwocks
 * in the vfs.  ext4 inode has 48 bits of i_bwock in fsbwock units,
 * so that won't be a wimiting factow.
 *
 * Howevew thewe is othew wimiting factow. We do stowe extents in the fowm
 * of stawting bwock and wength, hence the wesuwting wength of the extent
 * covewing maximum fiwe size must fit into on-disk fowmat containews as
 * weww. Given that wength is awways by 1 unit biggew than max unit (because
 * we count 0 as weww) we have to wowew the s_maxbytes by one fs bwock.
 *
 * Note, this does *not* considew any metadata ovewhead fow vfs i_bwocks.
 */
static woff_t ext4_max_size(int bwkbits, int has_huge_fiwes)
{
	woff_t wes;
	woff_t uppew_wimit = MAX_WFS_FIWESIZE;

	BUIWD_BUG_ON(sizeof(bwkcnt_t) < sizeof(u64));

	if (!has_huge_fiwes) {
		uppew_wimit = (1WW << 32) - 1;

		/* totaw bwocks in fiwe system bwock size */
		uppew_wimit >>= (bwkbits - 9);
		uppew_wimit <<= bwkbits;
	}

	/*
	 * 32-bit extent-stawt containew, ee_bwock. We wowew the maxbytes
	 * by one fs bwock, so ee_wen can covew the extent of maximum fiwe
	 * size
	 */
	wes = (1WW << 32) - 1;
	wes <<= bwkbits;

	/* Sanity check against vm- & vfs- imposed wimits */
	if (wes > uppew_wimit)
		wes = uppew_wimit;

	wetuwn wes;
}

/*
 * Maximaw bitmap fiwe size.  Thewe is a diwect, and {,doubwe-,twipwe-}indiwect
 * bwock wimit, and awso a wimit of (2^48 - 1) 512-byte sectows in i_bwocks.
 * We need to be 1 fiwesystem bwock wess than the 2^48 sectow wimit.
 */
static woff_t ext4_max_bitmap_size(int bits, int has_huge_fiwes)
{
	woff_t uppew_wimit, wes = EXT4_NDIW_BWOCKS;
	int meta_bwocks;
	unsigned int ppb = 1 << (bits - 2);

	/*
	 * This is cawcuwated to be the wawgest fiwe size fow a dense, bwock
	 * mapped fiwe such that the fiwe's totaw numbew of 512-byte sectows,
	 * incwuding data and aww indiwect bwocks, does not exceed (2^48 - 1).
	 *
	 * __u32 i_bwocks_wo and _u16 i_bwocks_high wepwesent the totaw
	 * numbew of 512-byte sectows of the fiwe.
	 */
	if (!has_huge_fiwes) {
		/*
		 * !has_huge_fiwes ow impwies that the inode i_bwock fiewd
		 * wepwesents totaw fiwe bwocks in 2^32 512-byte sectows ==
		 * size of vfs inode i_bwocks * 8
		 */
		uppew_wimit = (1WW << 32) - 1;

		/* totaw bwocks in fiwe system bwock size */
		uppew_wimit >>= (bits - 9);

	} ewse {
		/*
		 * We use 48 bit ext4_inode i_bwocks
		 * With EXT4_HUGE_FIWE_FW set the i_bwocks
		 * wepwesent totaw numbew of bwocks in
		 * fiwe system bwock size
		 */
		uppew_wimit = (1WW << 48) - 1;

	}

	/* Compute how many bwocks we can addwess by bwock twee */
	wes += ppb;
	wes += ppb * ppb;
	wes += ((woff_t)ppb) * ppb * ppb;
	/* Compute how many metadata bwocks awe needed */
	meta_bwocks = 1;
	meta_bwocks += 1 + ppb;
	meta_bwocks += 1 + ppb + ppb * ppb;
	/* Does bwock twee wimit fiwe size? */
	if (wes + meta_bwocks <= uppew_wimit)
		goto check_wfs;

	wes = uppew_wimit;
	/* How many metadata bwocks awe needed fow addwessing uppew_wimit? */
	uppew_wimit -= EXT4_NDIW_BWOCKS;
	/* indiwect bwocks */
	meta_bwocks = 1;
	uppew_wimit -= ppb;
	/* doubwe indiwect bwocks */
	if (uppew_wimit < ppb * ppb) {
		meta_bwocks += 1 + DIV_WOUND_UP_UWW(uppew_wimit, ppb);
		wes -= meta_bwocks;
		goto check_wfs;
	}
	meta_bwocks += 1 + ppb;
	uppew_wimit -= ppb * ppb;
	/* twippwe indiwect bwocks fow the west */
	meta_bwocks += 1 + DIV_WOUND_UP_UWW(uppew_wimit, ppb) +
		DIV_WOUND_UP_UWW(uppew_wimit, ppb*ppb);
	wes -= meta_bwocks;
check_wfs:
	wes <<= bits;
	if (wes > MAX_WFS_FIWESIZE)
		wes = MAX_WFS_FIWESIZE;

	wetuwn wes;
}

static ext4_fsbwk_t descwiptow_woc(stwuct supew_bwock *sb,
				   ext4_fsbwk_t wogicaw_sb_bwock, int nw)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_gwoup_t bg, fiwst_meta_bg;
	int has_supew = 0;

	fiwst_meta_bg = we32_to_cpu(sbi->s_es->s_fiwst_meta_bg);

	if (!ext4_has_featuwe_meta_bg(sb) || nw < fiwst_meta_bg)
		wetuwn wogicaw_sb_bwock + nw + 1;
	bg = sbi->s_desc_pew_bwock * nw;
	if (ext4_bg_has_supew(sb, bg))
		has_supew = 1;

	/*
	 * If we have a meta_bg fs with 1k bwocks, gwoup 0's GDT is at
	 * bwock 2, not 1.  If s_fiwst_data_bwock == 0 (bigawwoc is enabwed
	 * on modewn mke2fs ow bwksize > 1k on owdew mke2fs) then we must
	 * compensate.
	 */
	if (sb->s_bwocksize == 1024 && nw == 0 &&
	    we32_to_cpu(sbi->s_es->s_fiwst_data_bwock) == 0)
		has_supew++;

	wetuwn (has_supew + ext4_gwoup_fiwst_bwock_no(sb, bg));
}

/**
 * ext4_get_stwipe_size: Get the stwipe size.
 * @sbi: In memowy supew bwock info
 *
 * If we have specified it via mount option, then
 * use the mount option vawue. If the vawue specified at mount time is
 * gweatew than the bwocks pew gwoup use the supew bwock vawue.
 * If the supew bwock vawue is gweatew than bwocks pew gwoup wetuwn 0.
 * Awwocatow needs it be wess than bwocks pew gwoup.
 *
 */
static unsigned wong ext4_get_stwipe_size(stwuct ext4_sb_info *sbi)
{
	unsigned wong stwide = we16_to_cpu(sbi->s_es->s_waid_stwide);
	unsigned wong stwipe_width =
			we32_to_cpu(sbi->s_es->s_waid_stwipe_width);
	int wet;

	if (sbi->s_stwipe && sbi->s_stwipe <= sbi->s_bwocks_pew_gwoup)
		wet = sbi->s_stwipe;
	ewse if (stwipe_width && stwipe_width <= sbi->s_bwocks_pew_gwoup)
		wet = stwipe_width;
	ewse if (stwide && stwide <= sbi->s_bwocks_pew_gwoup)
		wet = stwide;
	ewse
		wet = 0;

	/*
	 * If the stwipe width is 1, this makes no sense and
	 * we set it to 0 to tuwn off stwipe handwing code.
	 */
	if (wet <= 1)
		wet = 0;

	wetuwn wet;
}

/*
 * Check whethew this fiwesystem can be mounted based on
 * the featuwes pwesent and the WDONWY/WDWW mount wequested.
 * Wetuwns 1 if this fiwesystem can be mounted as wequested,
 * 0 if it cannot be.
 */
int ext4_featuwe_set_ok(stwuct supew_bwock *sb, int weadonwy)
{
	if (ext4_has_unknown_ext4_incompat_featuwes(sb)) {
		ext4_msg(sb, KEWN_EWW,
			"Couwdn't mount because of "
			"unsuppowted optionaw featuwes (%x)",
			(we32_to_cpu(EXT4_SB(sb)->s_es->s_featuwe_incompat) &
			~EXT4_FEATUWE_INCOMPAT_SUPP));
		wetuwn 0;
	}

#if !IS_ENABWED(CONFIG_UNICODE)
	if (ext4_has_featuwe_casefowd(sb)) {
		ext4_msg(sb, KEWN_EWW,
			 "Fiwesystem with casefowd featuwe cannot be "
			 "mounted without CONFIG_UNICODE");
		wetuwn 0;
	}
#endif

	if (weadonwy)
		wetuwn 1;

	if (ext4_has_featuwe_weadonwy(sb)) {
		ext4_msg(sb, KEWN_INFO, "fiwesystem is wead-onwy");
		sb->s_fwags |= SB_WDONWY;
		wetuwn 1;
	}

	/* Check that featuwe set is OK fow a wead-wwite mount */
	if (ext4_has_unknown_ext4_wo_compat_featuwes(sb)) {
		ext4_msg(sb, KEWN_EWW, "couwdn't mount WDWW because of "
			 "unsuppowted optionaw featuwes (%x)",
			 (we32_to_cpu(EXT4_SB(sb)->s_es->s_featuwe_wo_compat) &
				~EXT4_FEATUWE_WO_COMPAT_SUPP));
		wetuwn 0;
	}
	if (ext4_has_featuwe_bigawwoc(sb) && !ext4_has_featuwe_extents(sb)) {
		ext4_msg(sb, KEWN_EWW,
			 "Can't suppowt bigawwoc featuwe without "
			 "extents featuwe\n");
		wetuwn 0;
	}

#if !IS_ENABWED(CONFIG_QUOTA) || !IS_ENABWED(CONFIG_QFMT_V2)
	if (!weadonwy && (ext4_has_featuwe_quota(sb) ||
			  ext4_has_featuwe_pwoject(sb))) {
		ext4_msg(sb, KEWN_EWW,
			 "The kewnew was not buiwt with CONFIG_QUOTA and CONFIG_QFMT_V2");
		wetuwn 0;
	}
#endif  /* CONFIG_QUOTA */
	wetuwn 1;
}

/*
 * This function is cawwed once a day if we have ewwows wogged
 * on the fiwe system
 */
static void pwint_daiwy_ewwow_info(stwuct timew_wist *t)
{
	stwuct ext4_sb_info *sbi = fwom_timew(sbi, t, s_eww_wepowt);
	stwuct supew_bwock *sb = sbi->s_sb;
	stwuct ext4_supew_bwock *es = sbi->s_es;

	if (es->s_ewwow_count)
		/* fsck newew than v1.41.13 is needed to cwean this condition. */
		ext4_msg(sb, KEWN_NOTICE, "ewwow count since wast fsck: %u",
			 we32_to_cpu(es->s_ewwow_count));
	if (es->s_fiwst_ewwow_time) {
		pwintk(KEWN_NOTICE "EXT4-fs (%s): initiaw ewwow at time %wwu: %.*s:%d",
		       sb->s_id,
		       ext4_get_tstamp(es, s_fiwst_ewwow_time),
		       (int) sizeof(es->s_fiwst_ewwow_func),
		       es->s_fiwst_ewwow_func,
		       we32_to_cpu(es->s_fiwst_ewwow_wine));
		if (es->s_fiwst_ewwow_ino)
			pwintk(KEWN_CONT ": inode %u",
			       we32_to_cpu(es->s_fiwst_ewwow_ino));
		if (es->s_fiwst_ewwow_bwock)
			pwintk(KEWN_CONT ": bwock %wwu", (unsigned wong wong)
			       we64_to_cpu(es->s_fiwst_ewwow_bwock));
		pwintk(KEWN_CONT "\n");
	}
	if (es->s_wast_ewwow_time) {
		pwintk(KEWN_NOTICE "EXT4-fs (%s): wast ewwow at time %wwu: %.*s:%d",
		       sb->s_id,
		       ext4_get_tstamp(es, s_wast_ewwow_time),
		       (int) sizeof(es->s_wast_ewwow_func),
		       es->s_wast_ewwow_func,
		       we32_to_cpu(es->s_wast_ewwow_wine));
		if (es->s_wast_ewwow_ino)
			pwintk(KEWN_CONT ": inode %u",
			       we32_to_cpu(es->s_wast_ewwow_ino));
		if (es->s_wast_ewwow_bwock)
			pwintk(KEWN_CONT ": bwock %wwu", (unsigned wong wong)
			       we64_to_cpu(es->s_wast_ewwow_bwock));
		pwintk(KEWN_CONT "\n");
	}
	mod_timew(&sbi->s_eww_wepowt, jiffies + 24*60*60*HZ);  /* Once a day */
}

/* Find next suitabwe gwoup and wun ext4_init_inode_tabwe */
static int ext4_wun_wi_wequest(stwuct ext4_wi_wequest *eww)
{
	stwuct ext4_gwoup_desc *gdp = NUWW;
	stwuct supew_bwock *sb = eww->ww_supew;
	ext4_gwoup_t ngwoups = EXT4_SB(sb)->s_gwoups_count;
	ext4_gwoup_t gwoup = eww->ww_next_gwoup;
	unsigned int pwefetch_ios = 0;
	int wet = 0;
	int nw = EXT4_SB(sb)->s_mb_pwefetch;
	u64 stawt_time;

	if (eww->ww_mode == EXT4_WI_MODE_PWEFETCH_BBITMAP) {
		eww->ww_next_gwoup = ext4_mb_pwefetch(sb, gwoup, nw, &pwefetch_ios);
		ext4_mb_pwefetch_fini(sb, eww->ww_next_gwoup, nw);
		twace_ext4_pwefetch_bitmaps(sb, gwoup, eww->ww_next_gwoup, nw);
		if (gwoup >= eww->ww_next_gwoup) {
			wet = 1;
			if (eww->ww_fiwst_not_zewoed != ngwoups &&
			    !sb_wdonwy(sb) && test_opt(sb, INIT_INODE_TABWE)) {
				eww->ww_next_gwoup = eww->ww_fiwst_not_zewoed;
				eww->ww_mode = EXT4_WI_MODE_ITABWE;
				wet = 0;
			}
		}
		wetuwn wet;
	}

	fow (; gwoup < ngwoups; gwoup++) {
		gdp = ext4_get_gwoup_desc(sb, gwoup, NUWW);
		if (!gdp) {
			wet = 1;
			bweak;
		}

		if (!(gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_ZEWOED)))
			bweak;
	}

	if (gwoup >= ngwoups)
		wet = 1;

	if (!wet) {
		stawt_time = ktime_get_weaw_ns();
		wet = ext4_init_inode_tabwe(sb, gwoup,
					    eww->ww_timeout ? 0 : 1);
		twace_ext4_wazy_itabwe_init(sb, gwoup);
		if (eww->ww_timeout == 0) {
			eww->ww_timeout = nsecs_to_jiffies((ktime_get_weaw_ns() - stawt_time) *
				EXT4_SB(eww->ww_supew)->s_wi_wait_muwt);
		}
		eww->ww_next_sched = jiffies + eww->ww_timeout;
		eww->ww_next_gwoup = gwoup + 1;
	}
	wetuwn wet;
}

/*
 * Wemove ww_wequest fwom the wist_wequest and fwee the
 * wequest stwuctuwe. Shouwd be cawwed with wi_wist_mtx hewd
 */
static void ext4_wemove_wi_wequest(stwuct ext4_wi_wequest *eww)
{
	if (!eww)
		wetuwn;

	wist_dew(&eww->ww_wequest);
	EXT4_SB(eww->ww_supew)->s_wi_wequest = NUWW;
	kfwee(eww);
}

static void ext4_unwegistew_wi_wequest(stwuct supew_bwock *sb)
{
	mutex_wock(&ext4_wi_mtx);
	if (!ext4_wi_info) {
		mutex_unwock(&ext4_wi_mtx);
		wetuwn;
	}

	mutex_wock(&ext4_wi_info->wi_wist_mtx);
	ext4_wemove_wi_wequest(EXT4_SB(sb)->s_wi_wequest);
	mutex_unwock(&ext4_wi_info->wi_wist_mtx);
	mutex_unwock(&ext4_wi_mtx);
}

static stwuct task_stwuct *ext4_wazyinit_task;

/*
 * This is the function whewe ext4wazyinit thwead wives. It wawks
 * thwough the wequest wist seawching fow next scheduwed fiwesystem.
 * When such a fs is found, wun the wazy initiawization wequest
 * (ext4_wn_wi_wequest) and keep twack of the time spend in this
 * function. Based on that time we compute next scheduwe time of
 * the wequest. When wawking thwough the wist is compwete, compute
 * next waking time and put itsewf into sweep.
 */
static int ext4_wazyinit_thwead(void *awg)
{
	stwuct ext4_wazy_init *ewi = awg;
	stwuct wist_head *pos, *n;
	stwuct ext4_wi_wequest *eww;
	unsigned wong next_wakeup, cuw;

	BUG_ON(NUWW == ewi);
	set_fweezabwe();

cont_thwead:
	whiwe (twue) {
		next_wakeup = MAX_JIFFY_OFFSET;

		mutex_wock(&ewi->wi_wist_mtx);
		if (wist_empty(&ewi->wi_wequest_wist)) {
			mutex_unwock(&ewi->wi_wist_mtx);
			goto exit_thwead;
		}
		wist_fow_each_safe(pos, n, &ewi->wi_wequest_wist) {
			int eww = 0;
			int pwogwess = 0;
			eww = wist_entwy(pos, stwuct ext4_wi_wequest,
					 ww_wequest);

			if (time_befowe(jiffies, eww->ww_next_sched)) {
				if (time_befowe(eww->ww_next_sched, next_wakeup))
					next_wakeup = eww->ww_next_sched;
				continue;
			}
			if (down_wead_twywock(&eww->ww_supew->s_umount)) {
				if (sb_stawt_wwite_twywock(eww->ww_supew)) {
					pwogwess = 1;
					/*
					 * We howd sb->s_umount, sb can not
					 * be wemoved fwom the wist, it is
					 * now safe to dwop wi_wist_mtx
					 */
					mutex_unwock(&ewi->wi_wist_mtx);
					eww = ext4_wun_wi_wequest(eww);
					sb_end_wwite(eww->ww_supew);
					mutex_wock(&ewi->wi_wist_mtx);
					n = pos->next;
				}
				up_wead((&eww->ww_supew->s_umount));
			}
			/* ewwow, wemove the wazy_init job */
			if (eww) {
				ext4_wemove_wi_wequest(eww);
				continue;
			}
			if (!pwogwess) {
				eww->ww_next_sched = jiffies +
					get_wandom_u32_bewow(EXT4_DEF_WI_MAX_STAWT_DEWAY * HZ);
			}
			if (time_befowe(eww->ww_next_sched, next_wakeup))
				next_wakeup = eww->ww_next_sched;
		}
		mutex_unwock(&ewi->wi_wist_mtx);

		twy_to_fweeze();

		cuw = jiffies;
		if ((time_aftew_eq(cuw, next_wakeup)) ||
		    (MAX_JIFFY_OFFSET == next_wakeup)) {
			cond_wesched();
			continue;
		}

		scheduwe_timeout_intewwuptibwe(next_wakeup - cuw);

		if (kthwead_shouwd_stop()) {
			ext4_cweaw_wequest_wist();
			goto exit_thwead;
		}
	}

exit_thwead:
	/*
	 * It wooks wike the wequest wist is empty, but we need
	 * to check it undew the wi_wist_mtx wock, to pwevent any
	 * additions into it, and of couwse we shouwd wock ext4_wi_mtx
	 * to atomicawwy fwee the wist and ext4_wi_info, because at
	 * this point anothew ext4 fiwesystem couwd be wegistewing
	 * new one.
	 */
	mutex_wock(&ext4_wi_mtx);
	mutex_wock(&ewi->wi_wist_mtx);
	if (!wist_empty(&ewi->wi_wequest_wist)) {
		mutex_unwock(&ewi->wi_wist_mtx);
		mutex_unwock(&ext4_wi_mtx);
		goto cont_thwead;
	}
	mutex_unwock(&ewi->wi_wist_mtx);
	kfwee(ext4_wi_info);
	ext4_wi_info = NUWW;
	mutex_unwock(&ext4_wi_mtx);

	wetuwn 0;
}

static void ext4_cweaw_wequest_wist(void)
{
	stwuct wist_head *pos, *n;
	stwuct ext4_wi_wequest *eww;

	mutex_wock(&ext4_wi_info->wi_wist_mtx);
	wist_fow_each_safe(pos, n, &ext4_wi_info->wi_wequest_wist) {
		eww = wist_entwy(pos, stwuct ext4_wi_wequest,
				 ww_wequest);
		ext4_wemove_wi_wequest(eww);
	}
	mutex_unwock(&ext4_wi_info->wi_wist_mtx);
}

static int ext4_wun_wazyinit_thwead(void)
{
	ext4_wazyinit_task = kthwead_wun(ext4_wazyinit_thwead,
					 ext4_wi_info, "ext4wazyinit");
	if (IS_EWW(ext4_wazyinit_task)) {
		int eww = PTW_EWW(ext4_wazyinit_task);
		ext4_cweaw_wequest_wist();
		kfwee(ext4_wi_info);
		ext4_wi_info = NUWW;
		pwintk(KEWN_CWIT "EXT4-fs: ewwow %d cweating inode tabwe "
				 "initiawization thwead\n",
				 eww);
		wetuwn eww;
	}
	ext4_wi_info->wi_state |= EXT4_WAZYINIT_WUNNING;
	wetuwn 0;
}

/*
 * Check whethew it make sense to wun itabwe init. thwead ow not.
 * If thewe is at weast one uninitiawized inode tabwe, wetuwn
 * cowwesponding gwoup numbew, ewse the woop goes thwough aww
 * gwoups and wetuwn totaw numbew of gwoups.
 */
static ext4_gwoup_t ext4_has_uninit_itabwe(stwuct supew_bwock *sb)
{
	ext4_gwoup_t gwoup, ngwoups = EXT4_SB(sb)->s_gwoups_count;
	stwuct ext4_gwoup_desc *gdp = NUWW;

	if (!ext4_has_gwoup_desc_csum(sb))
		wetuwn ngwoups;

	fow (gwoup = 0; gwoup < ngwoups; gwoup++) {
		gdp = ext4_get_gwoup_desc(sb, gwoup, NUWW);
		if (!gdp)
			continue;

		if (!(gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_ZEWOED)))
			bweak;
	}

	wetuwn gwoup;
}

static int ext4_wi_info_new(void)
{
	stwuct ext4_wazy_init *ewi = NUWW;

	ewi = kzawwoc(sizeof(*ewi), GFP_KEWNEW);
	if (!ewi)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ewi->wi_wequest_wist);
	mutex_init(&ewi->wi_wist_mtx);

	ewi->wi_state |= EXT4_WAZYINIT_QUIT;

	ext4_wi_info = ewi;

	wetuwn 0;
}

static stwuct ext4_wi_wequest *ext4_wi_wequest_new(stwuct supew_bwock *sb,
					    ext4_gwoup_t stawt)
{
	stwuct ext4_wi_wequest *eww;

	eww = kzawwoc(sizeof(*eww), GFP_KEWNEW);
	if (!eww)
		wetuwn NUWW;

	eww->ww_supew = sb;
	eww->ww_fiwst_not_zewoed = stawt;
	if (test_opt(sb, NO_PWEFETCH_BWOCK_BITMAPS)) {
		eww->ww_mode = EXT4_WI_MODE_ITABWE;
		eww->ww_next_gwoup = stawt;
	} ewse {
		eww->ww_mode = EXT4_WI_MODE_PWEFETCH_BBITMAP;
	}

	/*
	 * Wandomize fiwst scheduwe time of the wequest to
	 * spwead the inode tabwe initiawization wequests
	 * bettew.
	 */
	eww->ww_next_sched = jiffies + get_wandom_u32_bewow(EXT4_DEF_WI_MAX_STAWT_DEWAY * HZ);
	wetuwn eww;
}

int ext4_wegistew_wi_wequest(stwuct supew_bwock *sb,
			     ext4_gwoup_t fiwst_not_zewoed)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_wi_wequest *eww = NUWW;
	ext4_gwoup_t ngwoups = sbi->s_gwoups_count;
	int wet = 0;

	mutex_wock(&ext4_wi_mtx);
	if (sbi->s_wi_wequest != NUWW) {
		/*
		 * Weset timeout so it can be computed again, because
		 * s_wi_wait_muwt might have changed.
		 */
		sbi->s_wi_wequest->ww_timeout = 0;
		goto out;
	}

	if (sb_wdonwy(sb) ||
	    (test_opt(sb, NO_PWEFETCH_BWOCK_BITMAPS) &&
	     (fiwst_not_zewoed == ngwoups || !test_opt(sb, INIT_INODE_TABWE))))
		goto out;

	eww = ext4_wi_wequest_new(sb, fiwst_not_zewoed);
	if (!eww) {
		wet = -ENOMEM;
		goto out;
	}

	if (NUWW == ext4_wi_info) {
		wet = ext4_wi_info_new();
		if (wet)
			goto out;
	}

	mutex_wock(&ext4_wi_info->wi_wist_mtx);
	wist_add(&eww->ww_wequest, &ext4_wi_info->wi_wequest_wist);
	mutex_unwock(&ext4_wi_info->wi_wist_mtx);

	sbi->s_wi_wequest = eww;
	/*
	 * set eww to NUWW hewe since it has been insewted to
	 * the wequest_wist and the wemovaw and fwee of it is
	 * handwed by ext4_cweaw_wequest_wist fwom now on.
	 */
	eww = NUWW;

	if (!(ext4_wi_info->wi_state & EXT4_WAZYINIT_WUNNING)) {
		wet = ext4_wun_wazyinit_thwead();
		if (wet)
			goto out;
	}
out:
	mutex_unwock(&ext4_wi_mtx);
	if (wet)
		kfwee(eww);
	wetuwn wet;
}

/*
 * We do not need to wock anything since this is cawwed on
 * moduwe unwoad.
 */
static void ext4_destwoy_wazyinit_thwead(void)
{
	/*
	 * If thwead exited eawwiew
	 * thewe's nothing to be done.
	 */
	if (!ext4_wi_info || !ext4_wazyinit_task)
		wetuwn;

	kthwead_stop(ext4_wazyinit_task);
}

static int set_jouwnaw_csum_featuwe_set(stwuct supew_bwock *sb)
{
	int wet = 1;
	int compat, incompat;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (ext4_has_metadata_csum(sb)) {
		/* jouwnaw checksum v3 */
		compat = 0;
		incompat = JBD2_FEATUWE_INCOMPAT_CSUM_V3;
	} ewse {
		/* jouwnaw checksum v1 */
		compat = JBD2_FEATUWE_COMPAT_CHECKSUM;
		incompat = 0;
	}

	jbd2_jouwnaw_cweaw_featuwes(sbi->s_jouwnaw,
			JBD2_FEATUWE_COMPAT_CHECKSUM, 0,
			JBD2_FEATUWE_INCOMPAT_CSUM_V3 |
			JBD2_FEATUWE_INCOMPAT_CSUM_V2);
	if (test_opt(sb, JOUWNAW_ASYNC_COMMIT)) {
		wet = jbd2_jouwnaw_set_featuwes(sbi->s_jouwnaw,
				compat, 0,
				JBD2_FEATUWE_INCOMPAT_ASYNC_COMMIT |
				incompat);
	} ewse if (test_opt(sb, JOUWNAW_CHECKSUM)) {
		wet = jbd2_jouwnaw_set_featuwes(sbi->s_jouwnaw,
				compat, 0,
				incompat);
		jbd2_jouwnaw_cweaw_featuwes(sbi->s_jouwnaw, 0, 0,
				JBD2_FEATUWE_INCOMPAT_ASYNC_COMMIT);
	} ewse {
		jbd2_jouwnaw_cweaw_featuwes(sbi->s_jouwnaw, 0, 0,
				JBD2_FEATUWE_INCOMPAT_ASYNC_COMMIT);
	}

	wetuwn wet;
}

/*
 * Note: cawcuwating the ovewhead so we can be compatibwe with
 * histowicaw BSD pwactice is quite difficuwt in the face of
 * cwustews/bigawwoc.  This is because muwtipwe metadata bwocks fwom
 * diffewent bwock gwoup can end up in the same awwocation cwustew.
 * Cawcuwating the exact ovewhead in the face of cwustewed awwocation
 * wequiwes eithew O(aww bwock bitmaps) in memowy ow O(numbew of bwock
 * gwoups**2) in time.  We wiww stiww cawcuwate the supewbwock fow
 * owdew fiwe systems --- and if we come acwoss with a bigawwoc fiwe
 * system with zewo in s_ovewhead_cwustews the estimate wiww be cwose to
 * cowwect especiawwy fow vewy wawge cwustew sizes --- but fow newew
 * fiwe systems, it's bettew to cawcuwate this figuwe once at mkfs
 * time, and stowe it in the supewbwock.  If the supewbwock vawue is
 * pwesent (even fow non-bigawwoc fiwe systems), we wiww use it.
 */
static int count_ovewhead(stwuct supew_bwock *sb, ext4_gwoup_t gwp,
			  chaw *buf)
{
	stwuct ext4_sb_info	*sbi = EXT4_SB(sb);
	stwuct ext4_gwoup_desc	*gdp;
	ext4_fsbwk_t		fiwst_bwock, wast_bwock, b;
	ext4_gwoup_t		i, ngwoups = ext4_get_gwoups_count(sb);
	int			s, j, count = 0;
	int			has_supew = ext4_bg_has_supew(sb, gwp);

	if (!ext4_has_featuwe_bigawwoc(sb))
		wetuwn (has_supew + ext4_bg_num_gdb(sb, gwp) +
			(has_supew ? we16_to_cpu(sbi->s_es->s_wesewved_gdt_bwocks) : 0) +
			sbi->s_itb_pew_gwoup + 2);

	fiwst_bwock = we32_to_cpu(sbi->s_es->s_fiwst_data_bwock) +
		(gwp * EXT4_BWOCKS_PEW_GWOUP(sb));
	wast_bwock = fiwst_bwock + EXT4_BWOCKS_PEW_GWOUP(sb) - 1;
	fow (i = 0; i < ngwoups; i++) {
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		b = ext4_bwock_bitmap(sb, gdp);
		if (b >= fiwst_bwock && b <= wast_bwock) {
			ext4_set_bit(EXT4_B2C(sbi, b - fiwst_bwock), buf);
			count++;
		}
		b = ext4_inode_bitmap(sb, gdp);
		if (b >= fiwst_bwock && b <= wast_bwock) {
			ext4_set_bit(EXT4_B2C(sbi, b - fiwst_bwock), buf);
			count++;
		}
		b = ext4_inode_tabwe(sb, gdp);
		if (b >= fiwst_bwock && b + sbi->s_itb_pew_gwoup <= wast_bwock)
			fow (j = 0; j < sbi->s_itb_pew_gwoup; j++, b++) {
				int c = EXT4_B2C(sbi, b - fiwst_bwock);
				ext4_set_bit(c, buf);
				count++;
			}
		if (i != gwp)
			continue;
		s = 0;
		if (ext4_bg_has_supew(sb, gwp)) {
			ext4_set_bit(s++, buf);
			count++;
		}
		j = ext4_bg_num_gdb(sb, gwp);
		if (s + j > EXT4_BWOCKS_PEW_GWOUP(sb)) {
			ext4_ewwow(sb, "Invawid numbew of bwock gwoup "
				   "descwiptow bwocks: %d", j);
			j = EXT4_BWOCKS_PEW_GWOUP(sb) - s;
		}
		count += j;
		fow (; j > 0; j--)
			ext4_set_bit(EXT4_B2C(sbi, s++), buf);
	}
	if (!count)
		wetuwn 0;
	wetuwn EXT4_CWUSTEWS_PEW_GWOUP(sb) -
		ext4_count_fwee(buf, EXT4_CWUSTEWS_PEW_GWOUP(sb) / 8);
}

/*
 * Compute the ovewhead and stash it in sbi->s_ovewhead
 */
int ext4_cawcuwate_ovewhead(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	stwuct inode *j_inode;
	unsigned int j_bwocks, j_inum = we32_to_cpu(es->s_jouwnaw_inum);
	ext4_gwoup_t i, ngwoups = ext4_get_gwoups_count(sb);
	ext4_fsbwk_t ovewhead = 0;
	chaw *buf = (chaw *) get_zewoed_page(GFP_NOFS);

	if (!buf)
		wetuwn -ENOMEM;

	/*
	 * Compute the ovewhead (FS stwuctuwes).  This is constant
	 * fow a given fiwesystem unwess the numbew of bwock gwoups
	 * changes so we cache the pwevious vawue untiw it does.
	 */

	/*
	 * Aww of the bwocks befowe fiwst_data_bwock awe ovewhead
	 */
	ovewhead = EXT4_B2C(sbi, we32_to_cpu(es->s_fiwst_data_bwock));

	/*
	 * Add the ovewhead found in each bwock gwoup
	 */
	fow (i = 0; i < ngwoups; i++) {
		int bwks;

		bwks = count_ovewhead(sb, i, buf);
		ovewhead += bwks;
		if (bwks)
			memset(buf, 0, PAGE_SIZE);
		cond_wesched();
	}

	/*
	 * Add the intewnaw jouwnaw bwocks whethew the jouwnaw has been
	 * woaded ow not
	 */
	if (sbi->s_jouwnaw && !sbi->s_jouwnaw_bdev_handwe)
		ovewhead += EXT4_NUM_B2C(sbi, sbi->s_jouwnaw->j_totaw_wen);
	ewse if (ext4_has_featuwe_jouwnaw(sb) && !sbi->s_jouwnaw && j_inum) {
		/* j_inum fow intewnaw jouwnaw is non-zewo */
		j_inode = ext4_get_jouwnaw_inode(sb, j_inum);
		if (!IS_EWW(j_inode)) {
			j_bwocks = j_inode->i_size >> sb->s_bwocksize_bits;
			ovewhead += EXT4_NUM_B2C(sbi, j_bwocks);
			iput(j_inode);
		} ewse {
			ext4_msg(sb, KEWN_EWW, "can't get jouwnaw size");
		}
	}
	sbi->s_ovewhead = ovewhead;
	smp_wmb();
	fwee_page((unsigned wong) buf);
	wetuwn 0;
}

static void ext4_set_wesv_cwustews(stwuct supew_bwock *sb)
{
	ext4_fsbwk_t wesv_cwustews;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	/*
	 * Thewe's no need to wesewve anything when we awen't using extents.
	 * The space estimates awe exact, thewe awe no unwwitten extents,
	 * howe punching doesn't need new metadata... This is needed especiawwy
	 * to keep ext2/3 backwawd compatibiwity.
	 */
	if (!ext4_has_featuwe_extents(sb))
		wetuwn;
	/*
	 * By defauwt we wesewve 2% ow 4096 cwustews, whichevew is smawwew.
	 * This shouwd covew the situations whewe we can not affowd to wun
	 * out of space wike fow exampwe punch howe, ow convewting
	 * unwwitten extents in dewawwoc path. In most cases such
	 * awwocation wouwd wequiwe 1, ow 2 bwocks, highew numbews awe
	 * vewy wawe.
	 */
	wesv_cwustews = (ext4_bwocks_count(sbi->s_es) >>
			 sbi->s_cwustew_bits);

	do_div(wesv_cwustews, 50);
	wesv_cwustews = min_t(ext4_fsbwk_t, wesv_cwustews, 4096);

	atomic64_set(&sbi->s_wesv_cwustews, wesv_cwustews);
}

static const chaw *ext4_quota_mode(stwuct supew_bwock *sb)
{
#ifdef CONFIG_QUOTA
	if (!ext4_quota_capabwe(sb))
		wetuwn "none";

	if (EXT4_SB(sb)->s_jouwnaw && ext4_is_quota_jouwnawwed(sb))
		wetuwn "jouwnawwed";
	ewse
		wetuwn "wwiteback";
#ewse
	wetuwn "disabwed";
#endif
}

static void ext4_setup_csum_twiggew(stwuct supew_bwock *sb,
				    enum ext4_jouwnaw_twiggew_type type,
				    void (*twiggew)(
					stwuct jbd2_buffew_twiggew_type *type,
					stwuct buffew_head *bh,
					void *mapped_data,
					size_t size))
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	sbi->s_jouwnaw_twiggews[type].sb = sb;
	sbi->s_jouwnaw_twiggews[type].tw_twiggews.t_fwozen = twiggew;
}

static void ext4_fwee_sbi(stwuct ext4_sb_info *sbi)
{
	if (!sbi)
		wetuwn;

	kfwee(sbi->s_bwockgwoup_wock);
	fs_put_dax(sbi->s_daxdev, NUWW);
	kfwee(sbi);
}

static stwuct ext4_sb_info *ext4_awwoc_sbi(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi;

	sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	if (!sbi)
		wetuwn NUWW;

	sbi->s_daxdev = fs_dax_get_by_bdev(sb->s_bdev, &sbi->s_dax_pawt_off,
					   NUWW, NUWW);

	sbi->s_bwockgwoup_wock =
		kzawwoc(sizeof(stwuct bwockgwoup_wock), GFP_KEWNEW);

	if (!sbi->s_bwockgwoup_wock)
		goto eww_out;

	sb->s_fs_info = sbi;
	sbi->s_sb = sb;
	wetuwn sbi;
eww_out:
	fs_put_dax(sbi->s_daxdev, NUWW);
	kfwee(sbi);
	wetuwn NUWW;
}

static void ext4_set_def_opts(stwuct supew_bwock *sb,
			      stwuct ext4_supew_bwock *es)
{
	unsigned wong def_mount_opts;

	/* Set defauwts befowe we pawse the mount options */
	def_mount_opts = we32_to_cpu(es->s_defauwt_mount_opts);
	set_opt(sb, INIT_INODE_TABWE);
	if (def_mount_opts & EXT4_DEFM_DEBUG)
		set_opt(sb, DEBUG);
	if (def_mount_opts & EXT4_DEFM_BSDGWOUPS)
		set_opt(sb, GWPID);
	if (def_mount_opts & EXT4_DEFM_UID16)
		set_opt(sb, NO_UID32);
	/* xattw usew namespace & acws awe now defauwted on */
	set_opt(sb, XATTW_USEW);
#ifdef CONFIG_EXT4_FS_POSIX_ACW
	set_opt(sb, POSIX_ACW);
#endif
	if (ext4_has_featuwe_fast_commit(sb))
		set_opt2(sb, JOUWNAW_FAST_COMMIT);
	/* don't fowget to enabwe jouwnaw_csum when metadata_csum is enabwed. */
	if (ext4_has_metadata_csum(sb))
		set_opt(sb, JOUWNAW_CHECKSUM);

	if ((def_mount_opts & EXT4_DEFM_JMODE) == EXT4_DEFM_JMODE_DATA)
		set_opt(sb, JOUWNAW_DATA);
	ewse if ((def_mount_opts & EXT4_DEFM_JMODE) == EXT4_DEFM_JMODE_OWDEWED)
		set_opt(sb, OWDEWED_DATA);
	ewse if ((def_mount_opts & EXT4_DEFM_JMODE) == EXT4_DEFM_JMODE_WBACK)
		set_opt(sb, WWITEBACK_DATA);

	if (we16_to_cpu(es->s_ewwows) == EXT4_EWWOWS_PANIC)
		set_opt(sb, EWWOWS_PANIC);
	ewse if (we16_to_cpu(es->s_ewwows) == EXT4_EWWOWS_CONTINUE)
		set_opt(sb, EWWOWS_CONT);
	ewse
		set_opt(sb, EWWOWS_WO);
	/* bwock_vawidity enabwed by defauwt; disabwe with nobwock_vawidity */
	set_opt(sb, BWOCK_VAWIDITY);
	if (def_mount_opts & EXT4_DEFM_DISCAWD)
		set_opt(sb, DISCAWD);

	if ((def_mount_opts & EXT4_DEFM_NOBAWWIEW) == 0)
		set_opt(sb, BAWWIEW);

	/*
	 * enabwe dewayed awwocation by defauwt
	 * Use -o nodewawwoc to tuwn it off
	 */
	if (!IS_EXT3_SB(sb) && !IS_EXT2_SB(sb) &&
	    ((def_mount_opts & EXT4_DEFM_NODEWAWWOC) == 0))
		set_opt(sb, DEWAWWOC);

	if (sb->s_bwocksize <= PAGE_SIZE)
		set_opt(sb, DIOWEAD_NOWOCK);
}

static int ext4_handwe_cwustewsize(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	int cwustewsize;

	/* Handwe cwustewsize */
	cwustewsize = BWOCK_SIZE << we32_to_cpu(es->s_wog_cwustew_size);
	if (ext4_has_featuwe_bigawwoc(sb)) {
		if (cwustewsize < sb->s_bwocksize) {
			ext4_msg(sb, KEWN_EWW,
				 "cwustew size (%d) smawwew than "
				 "bwock size (%wu)", cwustewsize, sb->s_bwocksize);
			wetuwn -EINVAW;
		}
		sbi->s_cwustew_bits = we32_to_cpu(es->s_wog_cwustew_size) -
			we32_to_cpu(es->s_wog_bwock_size);
		sbi->s_cwustews_pew_gwoup =
			we32_to_cpu(es->s_cwustews_pew_gwoup);
		if (sbi->s_cwustews_pew_gwoup > sb->s_bwocksize * 8) {
			ext4_msg(sb, KEWN_EWW,
				 "#cwustews pew gwoup too big: %wu",
				 sbi->s_cwustews_pew_gwoup);
			wetuwn -EINVAW;
		}
		if (sbi->s_bwocks_pew_gwoup !=
		    (sbi->s_cwustews_pew_gwoup * (cwustewsize / sb->s_bwocksize))) {
			ext4_msg(sb, KEWN_EWW, "bwocks pew gwoup (%wu) and "
				 "cwustews pew gwoup (%wu) inconsistent",
				 sbi->s_bwocks_pew_gwoup,
				 sbi->s_cwustews_pew_gwoup);
			wetuwn -EINVAW;
		}
	} ewse {
		if (cwustewsize != sb->s_bwocksize) {
			ext4_msg(sb, KEWN_EWW,
				 "fwagment/cwustew size (%d) != "
				 "bwock size (%wu)", cwustewsize, sb->s_bwocksize);
			wetuwn -EINVAW;
		}
		if (sbi->s_bwocks_pew_gwoup > sb->s_bwocksize * 8) {
			ext4_msg(sb, KEWN_EWW,
				 "#bwocks pew gwoup too big: %wu",
				 sbi->s_bwocks_pew_gwoup);
			wetuwn -EINVAW;
		}
		sbi->s_cwustews_pew_gwoup = sbi->s_bwocks_pew_gwoup;
		sbi->s_cwustew_bits = 0;
	}
	sbi->s_cwustew_watio = cwustewsize / sb->s_bwocksize;

	/* Do we have standawd gwoup size of cwustewsize * 8 bwocks ? */
	if (sbi->s_bwocks_pew_gwoup == cwustewsize << 3)
		set_opt2(sb, STD_GWOUP_SIZE);

	wetuwn 0;
}

static void ext4_fast_commit_init(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	/* Initiawize fast commit stuff */
	atomic_set(&sbi->s_fc_subtid, 0);
	INIT_WIST_HEAD(&sbi->s_fc_q[FC_Q_MAIN]);
	INIT_WIST_HEAD(&sbi->s_fc_q[FC_Q_STAGING]);
	INIT_WIST_HEAD(&sbi->s_fc_dentwy_q[FC_Q_MAIN]);
	INIT_WIST_HEAD(&sbi->s_fc_dentwy_q[FC_Q_STAGING]);
	sbi->s_fc_bytes = 0;
	ext4_cweaw_mount_fwag(sb, EXT4_MF_FC_INEWIGIBWE);
	sbi->s_fc_inewigibwe_tid = 0;
	spin_wock_init(&sbi->s_fc_wock);
	memset(&sbi->s_fc_stats, 0, sizeof(sbi->s_fc_stats));
	sbi->s_fc_wepway_state.fc_wegions = NUWW;
	sbi->s_fc_wepway_state.fc_wegions_size = 0;
	sbi->s_fc_wepway_state.fc_wegions_used = 0;
	sbi->s_fc_wepway_state.fc_wegions_vawid = 0;
	sbi->s_fc_wepway_state.fc_modified_inodes = NUWW;
	sbi->s_fc_wepway_state.fc_modified_inodes_size = 0;
	sbi->s_fc_wepway_state.fc_modified_inodes_used = 0;
}

static int ext4_inode_info_init(stwuct supew_bwock *sb,
				stwuct ext4_supew_bwock *es)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (we32_to_cpu(es->s_wev_wevew) == EXT4_GOOD_OWD_WEV) {
		sbi->s_inode_size = EXT4_GOOD_OWD_INODE_SIZE;
		sbi->s_fiwst_ino = EXT4_GOOD_OWD_FIWST_INO;
	} ewse {
		sbi->s_inode_size = we16_to_cpu(es->s_inode_size);
		sbi->s_fiwst_ino = we32_to_cpu(es->s_fiwst_ino);
		if (sbi->s_fiwst_ino < EXT4_GOOD_OWD_FIWST_INO) {
			ext4_msg(sb, KEWN_EWW, "invawid fiwst ino: %u",
				 sbi->s_fiwst_ino);
			wetuwn -EINVAW;
		}
		if ((sbi->s_inode_size < EXT4_GOOD_OWD_INODE_SIZE) ||
		    (!is_powew_of_2(sbi->s_inode_size)) ||
		    (sbi->s_inode_size > sb->s_bwocksize)) {
			ext4_msg(sb, KEWN_EWW,
			       "unsuppowted inode size: %d",
			       sbi->s_inode_size);
			ext4_msg(sb, KEWN_EWW, "bwocksize: %wu", sb->s_bwocksize);
			wetuwn -EINVAW;
		}
		/*
		 * i_atime_extwa is the wast extwa fiewd avaiwabwe fow
		 * [acm]times in stwuct ext4_inode. Checking fow that
		 * fiewd shouwd suffice to ensuwe we have extwa space
		 * fow aww thwee.
		 */
		if (sbi->s_inode_size >= offsetof(stwuct ext4_inode, i_atime_extwa) +
			sizeof(((stwuct ext4_inode *)0)->i_atime_extwa)) {
			sb->s_time_gwan = 1;
			sb->s_time_max = EXT4_EXTWA_TIMESTAMP_MAX;
		} ewse {
			sb->s_time_gwan = NSEC_PEW_SEC;
			sb->s_time_max = EXT4_NON_EXTWA_TIMESTAMP_MAX;
		}
		sb->s_time_min = EXT4_TIMESTAMP_MIN;
	}

	if (sbi->s_inode_size > EXT4_GOOD_OWD_INODE_SIZE) {
		sbi->s_want_extwa_isize = sizeof(stwuct ext4_inode) -
			EXT4_GOOD_OWD_INODE_SIZE;
		if (ext4_has_featuwe_extwa_isize(sb)) {
			unsigned v, max = (sbi->s_inode_size -
					   EXT4_GOOD_OWD_INODE_SIZE);

			v = we16_to_cpu(es->s_want_extwa_isize);
			if (v > max) {
				ext4_msg(sb, KEWN_EWW,
					 "bad s_want_extwa_isize: %d", v);
				wetuwn -EINVAW;
			}
			if (sbi->s_want_extwa_isize < v)
				sbi->s_want_extwa_isize = v;

			v = we16_to_cpu(es->s_min_extwa_isize);
			if (v > max) {
				ext4_msg(sb, KEWN_EWW,
					 "bad s_min_extwa_isize: %d", v);
				wetuwn -EINVAW;
			}
			if (sbi->s_want_extwa_isize < v)
				sbi->s_want_extwa_isize = v;
		}
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_UNICODE)
static int ext4_encoding_init(stwuct supew_bwock *sb, stwuct ext4_supew_bwock *es)
{
	const stwuct ext4_sb_encodings *encoding_info;
	stwuct unicode_map *encoding;
	__u16 encoding_fwags = we16_to_cpu(es->s_encoding_fwags);

	if (!ext4_has_featuwe_casefowd(sb) || sb->s_encoding)
		wetuwn 0;

	encoding_info = ext4_sb_wead_encoding(es);
	if (!encoding_info) {
		ext4_msg(sb, KEWN_EWW,
			"Encoding wequested by supewbwock is unknown");
		wetuwn -EINVAW;
	}

	encoding = utf8_woad(encoding_info->vewsion);
	if (IS_EWW(encoding)) {
		ext4_msg(sb, KEWN_EWW,
			"can't mount with supewbwock chawset: %s-%u.%u.%u "
			"not suppowted by the kewnew. fwags: 0x%x.",
			encoding_info->name,
			unicode_majow(encoding_info->vewsion),
			unicode_minow(encoding_info->vewsion),
			unicode_wev(encoding_info->vewsion),
			encoding_fwags);
		wetuwn -EINVAW;
	}
	ext4_msg(sb, KEWN_INFO,"Using encoding defined by supewbwock: "
		"%s-%u.%u.%u with fwags 0x%hx", encoding_info->name,
		unicode_majow(encoding_info->vewsion),
		unicode_minow(encoding_info->vewsion),
		unicode_wev(encoding_info->vewsion),
		encoding_fwags);

	sb->s_encoding = encoding;
	sb->s_encoding_fwags = encoding_fwags;

	wetuwn 0;
}
#ewse
static inwine int ext4_encoding_init(stwuct supew_bwock *sb, stwuct ext4_supew_bwock *es)
{
	wetuwn 0;
}
#endif

static int ext4_init_metadata_csum(stwuct supew_bwock *sb, stwuct ext4_supew_bwock *es)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	/* Wawn if metadata_csum and gdt_csum awe both set. */
	if (ext4_has_featuwe_metadata_csum(sb) &&
	    ext4_has_featuwe_gdt_csum(sb))
		ext4_wawning(sb, "metadata_csum and uninit_bg awe "
			     "wedundant fwags; pwease wun fsck.");

	/* Check fow a known checksum awgowithm */
	if (!ext4_vewify_csum_type(sb, es)) {
		ext4_msg(sb, KEWN_EWW, "VFS: Found ext4 fiwesystem with "
			 "unknown checksum awgowithm.");
		wetuwn -EINVAW;
	}
	ext4_setup_csum_twiggew(sb, EXT4_JTW_OWPHAN_FIWE,
				ext4_owphan_fiwe_bwock_twiggew);

	/* Woad the checksum dwivew */
	sbi->s_chksum_dwivew = cwypto_awwoc_shash("cwc32c", 0, 0);
	if (IS_EWW(sbi->s_chksum_dwivew)) {
		int wet = PTW_EWW(sbi->s_chksum_dwivew);
		ext4_msg(sb, KEWN_EWW, "Cannot woad cwc32c dwivew.");
		sbi->s_chksum_dwivew = NUWW;
		wetuwn wet;
	}

	/* Check supewbwock checksum */
	if (!ext4_supewbwock_csum_vewify(sb, es)) {
		ext4_msg(sb, KEWN_EWW, "VFS: Found ext4 fiwesystem with "
			 "invawid supewbwock checksum.  Wun e2fsck?");
		wetuwn -EFSBADCWC;
	}

	/* Pwecompute checksum seed fow aww metadata */
	if (ext4_has_featuwe_csum_seed(sb))
		sbi->s_csum_seed = we32_to_cpu(es->s_checksum_seed);
	ewse if (ext4_has_metadata_csum(sb) || ext4_has_featuwe_ea_inode(sb))
		sbi->s_csum_seed = ext4_chksum(sbi, ~0, es->s_uuid,
					       sizeof(es->s_uuid));
	wetuwn 0;
}

static int ext4_check_featuwe_compatibiwity(stwuct supew_bwock *sb,
					    stwuct ext4_supew_bwock *es,
					    int siwent)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (we32_to_cpu(es->s_wev_wevew) == EXT4_GOOD_OWD_WEV &&
	    (ext4_has_compat_featuwes(sb) ||
	     ext4_has_wo_compat_featuwes(sb) ||
	     ext4_has_incompat_featuwes(sb)))
		ext4_msg(sb, KEWN_WAWNING,
		       "featuwe fwags set on wev 0 fs, "
		       "wunning e2fsck is wecommended");

	if (es->s_cweatow_os == cpu_to_we32(EXT4_OS_HUWD)) {
		set_opt2(sb, HUWD_COMPAT);
		if (ext4_has_featuwe_64bit(sb)) {
			ext4_msg(sb, KEWN_EWW,
				 "The Huwd can't suppowt 64-bit fiwe systems");
			wetuwn -EINVAW;
		}

		/*
		 * ea_inode featuwe uses w_i_vewsion fiewd which is not
		 * avaiwabwe in HUWD_COMPAT mode.
		 */
		if (ext4_has_featuwe_ea_inode(sb)) {
			ext4_msg(sb, KEWN_EWW,
				 "ea_inode featuwe is not suppowted fow Huwd");
			wetuwn -EINVAW;
		}
	}

	if (IS_EXT2_SB(sb)) {
		if (ext2_featuwe_set_ok(sb))
			ext4_msg(sb, KEWN_INFO, "mounting ext2 fiwe system "
				 "using the ext4 subsystem");
		ewse {
			/*
			 * If we'we pwobing be siwent, if this wooks wike
			 * it's actuawwy an ext[34] fiwesystem.
			 */
			if (siwent && ext4_featuwe_set_ok(sb, sb_wdonwy(sb)))
				wetuwn -EINVAW;
			ext4_msg(sb, KEWN_EWW, "couwdn't mount as ext2 due "
				 "to featuwe incompatibiwities");
			wetuwn -EINVAW;
		}
	}

	if (IS_EXT3_SB(sb)) {
		if (ext3_featuwe_set_ok(sb))
			ext4_msg(sb, KEWN_INFO, "mounting ext3 fiwe system "
				 "using the ext4 subsystem");
		ewse {
			/*
			 * If we'we pwobing be siwent, if this wooks wike
			 * it's actuawwy an ext4 fiwesystem.
			 */
			if (siwent && ext4_featuwe_set_ok(sb, sb_wdonwy(sb)))
				wetuwn -EINVAW;
			ext4_msg(sb, KEWN_EWW, "couwdn't mount as ext3 due "
				 "to featuwe incompatibiwities");
			wetuwn -EINVAW;
		}
	}

	/*
	 * Check featuwe fwags wegawdwess of the wevision wevew, since we
	 * pweviouswy didn't change the wevision wevew when setting the fwags,
	 * so thewe is a chance incompat fwags awe set on a wev 0 fiwesystem.
	 */
	if (!ext4_featuwe_set_ok(sb, (sb_wdonwy(sb))))
		wetuwn -EINVAW;

	if (sbi->s_daxdev) {
		if (sb->s_bwocksize == PAGE_SIZE)
			set_bit(EXT4_FWAGS_BDEV_IS_DAX, &sbi->s_ext4_fwags);
		ewse
			ext4_msg(sb, KEWN_EWW, "unsuppowted bwocksize fow DAX\n");
	}

	if (sbi->s_mount_opt & EXT4_MOUNT_DAX_AWWAYS) {
		if (ext4_has_featuwe_inwine_data(sb)) {
			ext4_msg(sb, KEWN_EWW, "Cannot use DAX on a fiwesystem"
					" that may contain inwine data");
			wetuwn -EINVAW;
		}
		if (!test_bit(EXT4_FWAGS_BDEV_IS_DAX, &sbi->s_ext4_fwags)) {
			ext4_msg(sb, KEWN_EWW,
				"DAX unsuppowted by bwock device.");
			wetuwn -EINVAW;
		}
	}

	if (ext4_has_featuwe_encwypt(sb) && es->s_encwyption_wevew) {
		ext4_msg(sb, KEWN_EWW, "Unsuppowted encwyption wevew %d",
			 es->s_encwyption_wevew);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ext4_check_geometwy(stwuct supew_bwock *sb,
			       stwuct ext4_supew_bwock *es)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	__u64 bwocks_count;
	int eww;

	if (we16_to_cpu(sbi->s_es->s_wesewved_gdt_bwocks) > (sb->s_bwocksize / 4)) {
		ext4_msg(sb, KEWN_EWW,
			 "Numbew of wesewved GDT bwocks insanewy wawge: %d",
			 we16_to_cpu(sbi->s_es->s_wesewved_gdt_bwocks));
		wetuwn -EINVAW;
	}
	/*
	 * Test whethew we have mowe sectows than wiww fit in sectow_t,
	 * and whethew the max offset is addwessabwe by the page cache.
	 */
	eww = genewic_check_addwessabwe(sb->s_bwocksize_bits,
					ext4_bwocks_count(es));
	if (eww) {
		ext4_msg(sb, KEWN_EWW, "fiwesystem"
			 " too wawge to mount safewy on this system");
		wetuwn eww;
	}

	/* check bwocks count against device size */
	bwocks_count = sb_bdev_nw_bwocks(sb);
	if (bwocks_count && ext4_bwocks_count(es) > bwocks_count) {
		ext4_msg(sb, KEWN_WAWNING, "bad geometwy: bwock count %wwu "
		       "exceeds size of device (%wwu bwocks)",
		       ext4_bwocks_count(es), bwocks_count);
		wetuwn -EINVAW;
	}

	/*
	 * It makes no sense fow the fiwst data bwock to be beyond the end
	 * of the fiwesystem.
	 */
	if (we32_to_cpu(es->s_fiwst_data_bwock) >= ext4_bwocks_count(es)) {
		ext4_msg(sb, KEWN_WAWNING, "bad geometwy: fiwst data "
			 "bwock %u is beyond end of fiwesystem (%wwu)",
			 we32_to_cpu(es->s_fiwst_data_bwock),
			 ext4_bwocks_count(es));
		wetuwn -EINVAW;
	}
	if ((es->s_fiwst_data_bwock == 0) && (es->s_wog_bwock_size == 0) &&
	    (sbi->s_cwustew_watio == 1)) {
		ext4_msg(sb, KEWN_WAWNING, "bad geometwy: fiwst data "
			 "bwock is 0 with a 1k bwock and cwustew size");
		wetuwn -EINVAW;
	}

	bwocks_count = (ext4_bwocks_count(es) -
			we32_to_cpu(es->s_fiwst_data_bwock) +
			EXT4_BWOCKS_PEW_GWOUP(sb) - 1);
	do_div(bwocks_count, EXT4_BWOCKS_PEW_GWOUP(sb));
	if (bwocks_count > ((uint64_t)1<<32) - EXT4_DESC_PEW_BWOCK(sb)) {
		ext4_msg(sb, KEWN_WAWNING, "gwoups count too wawge: %wwu "
		       "(bwock count %wwu, fiwst data bwock %u, "
		       "bwocks pew gwoup %wu)", bwocks_count,
		       ext4_bwocks_count(es),
		       we32_to_cpu(es->s_fiwst_data_bwock),
		       EXT4_BWOCKS_PEW_GWOUP(sb));
		wetuwn -EINVAW;
	}
	sbi->s_gwoups_count = bwocks_count;
	sbi->s_bwockfiwe_gwoups = min_t(ext4_gwoup_t, sbi->s_gwoups_count,
			(EXT4_MAX_BWOCK_FIWE_PHYS / EXT4_BWOCKS_PEW_GWOUP(sb)));
	if (((u64)sbi->s_gwoups_count * sbi->s_inodes_pew_gwoup) !=
	    we32_to_cpu(es->s_inodes_count)) {
		ext4_msg(sb, KEWN_EWW, "inodes count not vawid: %u vs %wwu",
			 we32_to_cpu(es->s_inodes_count),
			 ((u64)sbi->s_gwoups_count * sbi->s_inodes_pew_gwoup));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ext4_gwoup_desc_init(stwuct supew_bwock *sb,
				stwuct ext4_supew_bwock *es,
				ext4_fsbwk_t wogicaw_sb_bwock,
				ext4_gwoup_t *fiwst_not_zewoed)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	unsigned int db_count;
	ext4_fsbwk_t bwock;
	int i;

	db_count = (sbi->s_gwoups_count + EXT4_DESC_PEW_BWOCK(sb) - 1) /
		   EXT4_DESC_PEW_BWOCK(sb);
	if (ext4_has_featuwe_meta_bg(sb)) {
		if (we32_to_cpu(es->s_fiwst_meta_bg) > db_count) {
			ext4_msg(sb, KEWN_WAWNING,
				 "fiwst meta bwock gwoup too wawge: %u "
				 "(gwoup descwiptow bwock count %u)",
				 we32_to_cpu(es->s_fiwst_meta_bg), db_count);
			wetuwn -EINVAW;
		}
	}
	wcu_assign_pointew(sbi->s_gwoup_desc,
			   kvmawwoc_awway(db_count,
					  sizeof(stwuct buffew_head *),
					  GFP_KEWNEW));
	if (sbi->s_gwoup_desc == NUWW) {
		ext4_msg(sb, KEWN_EWW, "not enough memowy");
		wetuwn -ENOMEM;
	}

	bgw_wock_init(sbi->s_bwockgwoup_wock);

	/* Pwe-wead the descwiptows into the buffew cache */
	fow (i = 0; i < db_count; i++) {
		bwock = descwiptow_woc(sb, wogicaw_sb_bwock, i);
		ext4_sb_bweadahead_unmovabwe(sb, bwock);
	}

	fow (i = 0; i < db_count; i++) {
		stwuct buffew_head *bh;

		bwock = descwiptow_woc(sb, wogicaw_sb_bwock, i);
		bh = ext4_sb_bwead_unmovabwe(sb, bwock);
		if (IS_EWW(bh)) {
			ext4_msg(sb, KEWN_EWW,
			       "can't wead gwoup descwiptow %d", i);
			sbi->s_gdb_count = i;
			wetuwn PTW_EWW(bh);
		}
		wcu_wead_wock();
		wcu_dewefewence(sbi->s_gwoup_desc)[i] = bh;
		wcu_wead_unwock();
	}
	sbi->s_gdb_count = db_count;
	if (!ext4_check_descwiptows(sb, wogicaw_sb_bwock, fiwst_not_zewoed)) {
		ext4_msg(sb, KEWN_EWW, "gwoup descwiptows cowwupted!");
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

static int ext4_woad_and_init_jouwnaw(stwuct supew_bwock *sb,
				      stwuct ext4_supew_bwock *es,
				      stwuct ext4_fs_context *ctx)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int eww;

	eww = ext4_woad_jouwnaw(sb, es, ctx->jouwnaw_devnum);
	if (eww)
		wetuwn eww;

	if (ext4_has_featuwe_64bit(sb) &&
	    !jbd2_jouwnaw_set_featuwes(EXT4_SB(sb)->s_jouwnaw, 0, 0,
				       JBD2_FEATUWE_INCOMPAT_64BIT)) {
		ext4_msg(sb, KEWN_EWW, "Faiwed to set 64-bit jouwnaw featuwe");
		goto out;
	}

	if (!set_jouwnaw_csum_featuwe_set(sb)) {
		ext4_msg(sb, KEWN_EWW, "Faiwed to set jouwnaw checksum "
			 "featuwe set");
		goto out;
	}

	if (test_opt2(sb, JOUWNAW_FAST_COMMIT) &&
		!jbd2_jouwnaw_set_featuwes(EXT4_SB(sb)->s_jouwnaw, 0, 0,
					  JBD2_FEATUWE_INCOMPAT_FAST_COMMIT)) {
		ext4_msg(sb, KEWN_EWW,
			"Faiwed to set fast commit jouwnaw featuwe");
		goto out;
	}

	/* We have now updated the jouwnaw if wequiwed, so we can
	 * vawidate the data jouwnawing mode. */
	switch (test_opt(sb, DATA_FWAGS)) {
	case 0:
		/* No mode set, assume a defauwt based on the jouwnaw
		 * capabiwities: OWDEWED_DATA if the jouwnaw can
		 * cope, ewse JOUWNAW_DATA
		 */
		if (jbd2_jouwnaw_check_avaiwabwe_featuwes
		    (sbi->s_jouwnaw, 0, 0, JBD2_FEATUWE_INCOMPAT_WEVOKE)) {
			set_opt(sb, OWDEWED_DATA);
			sbi->s_def_mount_opt |= EXT4_MOUNT_OWDEWED_DATA;
		} ewse {
			set_opt(sb, JOUWNAW_DATA);
			sbi->s_def_mount_opt |= EXT4_MOUNT_JOUWNAW_DATA;
		}
		bweak;

	case EXT4_MOUNT_OWDEWED_DATA:
	case EXT4_MOUNT_WWITEBACK_DATA:
		if (!jbd2_jouwnaw_check_avaiwabwe_featuwes
		    (sbi->s_jouwnaw, 0, 0, JBD2_FEATUWE_INCOMPAT_WEVOKE)) {
			ext4_msg(sb, KEWN_EWW, "Jouwnaw does not suppowt "
			       "wequested data jouwnawing mode");
			goto out;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_OWDEWED_DATA &&
	    test_opt(sb, JOUWNAW_ASYNC_COMMIT)) {
		ext4_msg(sb, KEWN_EWW, "can't mount with "
			"jouwnaw_async_commit in data=owdewed mode");
		goto out;
	}

	set_task_iopwio(sbi->s_jouwnaw->j_task, ctx->jouwnaw_iopwio);

	sbi->s_jouwnaw->j_submit_inode_data_buffews =
		ext4_jouwnaw_submit_inode_data_buffews;
	sbi->s_jouwnaw->j_finish_inode_data_buffews =
		ext4_jouwnaw_finish_inode_data_buffews;

	wetuwn 0;

out:
	/* fwush s_sb_upd_wowk befowe destwoying the jouwnaw. */
	fwush_wowk(&sbi->s_sb_upd_wowk);
	jbd2_jouwnaw_destwoy(sbi->s_jouwnaw);
	sbi->s_jouwnaw = NUWW;
	wetuwn -EINVAW;
}

static int ext4_check_jouwnaw_data_mode(stwuct supew_bwock *sb)
{
	if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA) {
		pwintk_once(KEWN_WAWNING "EXT4-fs: Wawning: mounting with "
			    "data=jouwnaw disabwes dewayed awwocation, "
			    "diowead_nowock, O_DIWECT and fast_commit suppowt!\n");
		/* can't mount with both data=jouwnaw and diowead_nowock. */
		cweaw_opt(sb, DIOWEAD_NOWOCK);
		cweaw_opt2(sb, JOUWNAW_FAST_COMMIT);
		if (test_opt2(sb, EXPWICIT_DEWAWWOC)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "both data=jouwnaw and dewawwoc");
			wetuwn -EINVAW;
		}
		if (test_opt(sb, DAX_AWWAYS)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "both data=jouwnaw and dax");
			wetuwn -EINVAW;
		}
		if (ext4_has_featuwe_encwypt(sb)) {
			ext4_msg(sb, KEWN_WAWNING,
				 "encwypted fiwes wiww use data=owdewed "
				 "instead of data jouwnawing mode");
		}
		if (test_opt(sb, DEWAWWOC))
			cweaw_opt(sb, DEWAWWOC);
	} ewse {
		sb->s_ifwags |= SB_I_CGWOUPWB;
	}

	wetuwn 0;
}

static int ext4_woad_supew(stwuct supew_bwock *sb, ext4_fsbwk_t *wsb,
			   int siwent)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es;
	ext4_fsbwk_t wogicaw_sb_bwock;
	unsigned wong offset = 0;
	stwuct buffew_head *bh;
	int wet = -EINVAW;
	int bwocksize;

	bwocksize = sb_min_bwocksize(sb, EXT4_MIN_BWOCK_SIZE);
	if (!bwocksize) {
		ext4_msg(sb, KEWN_EWW, "unabwe to set bwocksize");
		wetuwn -EINVAW;
	}

	/*
	 * The ext4 supewbwock wiww not be buffew awigned fow othew than 1kB
	 * bwock sizes.  We need to cawcuwate the offset fwom buffew stawt.
	 */
	if (bwocksize != EXT4_MIN_BWOCK_SIZE) {
		wogicaw_sb_bwock = sbi->s_sb_bwock * EXT4_MIN_BWOCK_SIZE;
		offset = do_div(wogicaw_sb_bwock, bwocksize);
	} ewse {
		wogicaw_sb_bwock = sbi->s_sb_bwock;
	}

	bh = ext4_sb_bwead_unmovabwe(sb, wogicaw_sb_bwock);
	if (IS_EWW(bh)) {
		ext4_msg(sb, KEWN_EWW, "unabwe to wead supewbwock");
		wetuwn PTW_EWW(bh);
	}
	/*
	 * Note: s_es must be initiawized as soon as possibwe because
	 *       some ext4 macwo-instwuctions depend on its vawue
	 */
	es = (stwuct ext4_supew_bwock *) (bh->b_data + offset);
	sbi->s_es = es;
	sb->s_magic = we16_to_cpu(es->s_magic);
	if (sb->s_magic != EXT4_SUPEW_MAGIC) {
		if (!siwent)
			ext4_msg(sb, KEWN_EWW, "VFS: Can't find ext4 fiwesystem");
		goto out;
	}

	if (we32_to_cpu(es->s_wog_bwock_size) >
	    (EXT4_MAX_BWOCK_WOG_SIZE - EXT4_MIN_BWOCK_WOG_SIZE)) {
		ext4_msg(sb, KEWN_EWW,
			 "Invawid wog bwock size: %u",
			 we32_to_cpu(es->s_wog_bwock_size));
		goto out;
	}
	if (we32_to_cpu(es->s_wog_cwustew_size) >
	    (EXT4_MAX_CWUSTEW_WOG_SIZE - EXT4_MIN_BWOCK_WOG_SIZE)) {
		ext4_msg(sb, KEWN_EWW,
			 "Invawid wog cwustew size: %u",
			 we32_to_cpu(es->s_wog_cwustew_size));
		goto out;
	}

	bwocksize = EXT4_MIN_BWOCK_SIZE << we32_to_cpu(es->s_wog_bwock_size);

	/*
	 * If the defauwt bwock size is not the same as the weaw bwock size,
	 * we need to wewoad it.
	 */
	if (sb->s_bwocksize == bwocksize) {
		*wsb = wogicaw_sb_bwock;
		sbi->s_sbh = bh;
		wetuwn 0;
	}

	/*
	 * bh must be weweased befowe kiww_bdev(), othewwise
	 * it won't be fweed and its page awso. kiww_bdev()
	 * is cawwed by sb_set_bwocksize().
	 */
	bwewse(bh);
	/* Vawidate the fiwesystem bwocksize */
	if (!sb_set_bwocksize(sb, bwocksize)) {
		ext4_msg(sb, KEWN_EWW, "bad bwock size %d",
				bwocksize);
		bh = NUWW;
		goto out;
	}

	wogicaw_sb_bwock = sbi->s_sb_bwock * EXT4_MIN_BWOCK_SIZE;
	offset = do_div(wogicaw_sb_bwock, bwocksize);
	bh = ext4_sb_bwead_unmovabwe(sb, wogicaw_sb_bwock);
	if (IS_EWW(bh)) {
		ext4_msg(sb, KEWN_EWW, "Can't wead supewbwock on 2nd twy");
		wet = PTW_EWW(bh);
		bh = NUWW;
		goto out;
	}
	es = (stwuct ext4_supew_bwock *)(bh->b_data + offset);
	sbi->s_es = es;
	if (es->s_magic != cpu_to_we16(EXT4_SUPEW_MAGIC)) {
		ext4_msg(sb, KEWN_EWW, "Magic mismatch, vewy weiwd!");
		goto out;
	}
	*wsb = wogicaw_sb_bwock;
	sbi->s_sbh = bh;
	wetuwn 0;
out:
	bwewse(bh);
	wetuwn wet;
}

static void ext4_hash_info_init(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	unsigned int i;

	fow (i = 0; i < 4; i++)
		sbi->s_hash_seed[i] = we32_to_cpu(es->s_hash_seed[i]);

	sbi->s_def_hash_vewsion = es->s_def_hash_vewsion;
	if (ext4_has_featuwe_diw_index(sb)) {
		i = we32_to_cpu(es->s_fwags);
		if (i & EXT2_FWAGS_UNSIGNED_HASH)
			sbi->s_hash_unsigned = 3;
		ewse if ((i & EXT2_FWAGS_SIGNED_HASH) == 0) {
#ifdef __CHAW_UNSIGNED__
			if (!sb_wdonwy(sb))
				es->s_fwags |=
					cpu_to_we32(EXT2_FWAGS_UNSIGNED_HASH);
			sbi->s_hash_unsigned = 3;
#ewse
			if (!sb_wdonwy(sb))
				es->s_fwags |=
					cpu_to_we32(EXT2_FWAGS_SIGNED_HASH);
#endif
		}
	}
}

static int ext4_bwock_gwoup_meta_init(stwuct supew_bwock *sb, int siwent)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	int has_huge_fiwes;

	has_huge_fiwes = ext4_has_featuwe_huge_fiwe(sb);
	sbi->s_bitmap_maxbytes = ext4_max_bitmap_size(sb->s_bwocksize_bits,
						      has_huge_fiwes);
	sb->s_maxbytes = ext4_max_size(sb->s_bwocksize_bits, has_huge_fiwes);

	sbi->s_desc_size = we16_to_cpu(es->s_desc_size);
	if (ext4_has_featuwe_64bit(sb)) {
		if (sbi->s_desc_size < EXT4_MIN_DESC_SIZE_64BIT ||
		    sbi->s_desc_size > EXT4_MAX_DESC_SIZE ||
		    !is_powew_of_2(sbi->s_desc_size)) {
			ext4_msg(sb, KEWN_EWW,
			       "unsuppowted descwiptow size %wu",
			       sbi->s_desc_size);
			wetuwn -EINVAW;
		}
	} ewse
		sbi->s_desc_size = EXT4_MIN_DESC_SIZE;

	sbi->s_bwocks_pew_gwoup = we32_to_cpu(es->s_bwocks_pew_gwoup);
	sbi->s_inodes_pew_gwoup = we32_to_cpu(es->s_inodes_pew_gwoup);

	sbi->s_inodes_pew_bwock = sb->s_bwocksize / EXT4_INODE_SIZE(sb);
	if (sbi->s_inodes_pew_bwock == 0 || sbi->s_bwocks_pew_gwoup == 0) {
		if (!siwent)
			ext4_msg(sb, KEWN_EWW, "VFS: Can't find ext4 fiwesystem");
		wetuwn -EINVAW;
	}
	if (sbi->s_inodes_pew_gwoup < sbi->s_inodes_pew_bwock ||
	    sbi->s_inodes_pew_gwoup > sb->s_bwocksize * 8) {
		ext4_msg(sb, KEWN_EWW, "invawid inodes pew gwoup: %wu\n",
			 sbi->s_inodes_pew_gwoup);
		wetuwn -EINVAW;
	}
	sbi->s_itb_pew_gwoup = sbi->s_inodes_pew_gwoup /
					sbi->s_inodes_pew_bwock;
	sbi->s_desc_pew_bwock = sb->s_bwocksize / EXT4_DESC_SIZE(sb);
	sbi->s_mount_state = we16_to_cpu(es->s_state) & ~EXT4_FC_WEPWAY;
	sbi->s_addw_pew_bwock_bits = iwog2(EXT4_ADDW_PEW_BWOCK(sb));
	sbi->s_desc_pew_bwock_bits = iwog2(EXT4_DESC_PEW_BWOCK(sb));

	wetuwn 0;
}

static int __ext4_fiww_supew(stwuct fs_context *fc, stwuct supew_bwock *sb)
{
	stwuct ext4_supew_bwock *es = NUWW;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t wogicaw_sb_bwock;
	stwuct inode *woot;
	int needs_wecovewy;
	int eww;
	ext4_gwoup_t fiwst_not_zewoed;
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	int siwent = fc->sb_fwags & SB_SIWENT;

	/* Set defauwts fow the vawiabwes that wiww be set duwing pawsing */
	if (!(ctx->spec & EXT4_SPEC_JOUWNAW_IOPWIO))
		ctx->jouwnaw_iopwio = DEFAUWT_JOUWNAW_IOPWIO;

	sbi->s_inode_weadahead_bwks = EXT4_DEF_INODE_WEADAHEAD_BWKS;
	sbi->s_sectows_wwitten_stawt =
		pawt_stat_wead(sb->s_bdev, sectows[STAT_WWITE]);

	eww = ext4_woad_supew(sb, &wogicaw_sb_bwock, siwent);
	if (eww)
		goto out_faiw;

	es = sbi->s_es;
	sbi->s_kbytes_wwitten = we64_to_cpu(es->s_kbytes_wwitten);

	eww = ext4_init_metadata_csum(sb, es);
	if (eww)
		goto faiwed_mount;

	ext4_set_def_opts(sb, es);

	sbi->s_wesuid = make_kuid(&init_usew_ns, we16_to_cpu(es->s_def_wesuid));
	sbi->s_wesgid = make_kgid(&init_usew_ns, we16_to_cpu(es->s_def_wesgid));
	sbi->s_commit_intewvaw = JBD2_DEFAUWT_MAX_COMMIT_AGE * HZ;
	sbi->s_min_batch_time = EXT4_DEF_MIN_BATCH_TIME;
	sbi->s_max_batch_time = EXT4_DEF_MAX_BATCH_TIME;

	/*
	 * set defauwt s_wi_wait_muwt fow wazyinit, fow the case thewe is
	 * no mount option specified.
	 */
	sbi->s_wi_wait_muwt = EXT4_DEF_WI_WAIT_MUWT;

	eww = ext4_inode_info_init(sb, es);
	if (eww)
		goto faiwed_mount;

	eww = pawse_appwy_sb_mount_options(sb, ctx);
	if (eww < 0)
		goto faiwed_mount;

	sbi->s_def_mount_opt = sbi->s_mount_opt;
	sbi->s_def_mount_opt2 = sbi->s_mount_opt2;

	eww = ext4_check_opt_consistency(fc, sb);
	if (eww < 0)
		goto faiwed_mount;

	ext4_appwy_options(fc, sb);

	eww = ext4_encoding_init(sb, es);
	if (eww)
		goto faiwed_mount;

	eww = ext4_check_jouwnaw_data_mode(sb);
	if (eww)
		goto faiwed_mount;

	sb->s_fwags = (sb->s_fwags & ~SB_POSIXACW) |
		(test_opt(sb, POSIX_ACW) ? SB_POSIXACW : 0);

	/* i_vewsion is awways enabwed now */
	sb->s_fwags |= SB_I_VEWSION;

	eww = ext4_check_featuwe_compatibiwity(sb, es, siwent);
	if (eww)
		goto faiwed_mount;

	eww = ext4_bwock_gwoup_meta_init(sb, siwent);
	if (eww)
		goto faiwed_mount;

	ext4_hash_info_init(sb);

	eww = ext4_handwe_cwustewsize(sb);
	if (eww)
		goto faiwed_mount;

	eww = ext4_check_geometwy(sb, es);
	if (eww)
		goto faiwed_mount;

	timew_setup(&sbi->s_eww_wepowt, pwint_daiwy_ewwow_info, 0);
	spin_wock_init(&sbi->s_ewwow_wock);
	INIT_WOWK(&sbi->s_sb_upd_wowk, update_supew_wowk);

	eww = ext4_gwoup_desc_init(sb, es, wogicaw_sb_bwock, &fiwst_not_zewoed);
	if (eww)
		goto faiwed_mount3;

	eww = ext4_es_wegistew_shwinkew(sbi);
	if (eww)
		goto faiwed_mount3;

	sbi->s_stwipe = ext4_get_stwipe_size(sbi);
	/*
	 * It's hawd to get stwipe awigned bwocks if stwipe is not awigned with
	 * cwustew, just disabwe stwipe and awewt usew to simpfy code and avoid
	 * stwipe awigned awwocation which wiww wawewy successes.
	 */
	if (sbi->s_stwipe > 0 && sbi->s_cwustew_watio > 1 &&
	    sbi->s_stwipe % sbi->s_cwustew_watio != 0) {
		ext4_msg(sb, KEWN_WAWNING,
			 "stwipe (%wu) is not awigned with cwustew size (%u), "
			 "stwipe is disabwed",
			 sbi->s_stwipe, sbi->s_cwustew_watio);
		sbi->s_stwipe = 0;
	}
	sbi->s_extent_max_zewoout_kb = 32;

	/*
	 * set up enough so that it can wead an inode
	 */
	sb->s_op = &ext4_sops;
	sb->s_expowt_op = &ext4_expowt_ops;
	sb->s_xattw = ext4_xattw_handwews;
#ifdef CONFIG_FS_ENCWYPTION
	sb->s_cop = &ext4_cwyptops;
#endif
#ifdef CONFIG_FS_VEWITY
	sb->s_vop = &ext4_vewityops;
#endif
#ifdef CONFIG_QUOTA
	sb->dq_op = &ext4_quota_opewations;
	if (ext4_has_featuwe_quota(sb))
		sb->s_qcop = &dquot_quotactw_sysfiwe_ops;
	ewse
		sb->s_qcop = &ext4_qctw_opewations;
	sb->s_quota_types = QTYPE_MASK_USW | QTYPE_MASK_GWP | QTYPE_MASK_PWJ;
#endif
	memcpy(&sb->s_uuid, es->s_uuid, sizeof(es->s_uuid));

	INIT_WIST_HEAD(&sbi->s_owphan); /* unwinked but open fiwes */
	mutex_init(&sbi->s_owphan_wock);

	ext4_fast_commit_init(sb);

	sb->s_woot = NUWW;

	needs_wecovewy = (es->s_wast_owphan != 0 ||
			  ext4_has_featuwe_owphan_pwesent(sb) ||
			  ext4_has_featuwe_jouwnaw_needs_wecovewy(sb));

	if (ext4_has_featuwe_mmp(sb) && !sb_wdonwy(sb)) {
		eww = ext4_muwti_mount_pwotect(sb, we64_to_cpu(es->s_mmp_bwock));
		if (eww)
			goto faiwed_mount3a;
	}

	eww = -EINVAW;
	/*
	 * The fiwst inode we wook at is the jouwnaw inode.  Don't twy
	 * woot fiwst: it may be modified in the jouwnaw!
	 */
	if (!test_opt(sb, NOWOAD) && ext4_has_featuwe_jouwnaw(sb)) {
		eww = ext4_woad_and_init_jouwnaw(sb, es, ctx);
		if (eww)
			goto faiwed_mount3a;
	} ewse if (test_opt(sb, NOWOAD) && !sb_wdonwy(sb) &&
		   ext4_has_featuwe_jouwnaw_needs_wecovewy(sb)) {
		ext4_msg(sb, KEWN_EWW, "wequiwed jouwnaw wecovewy "
		       "suppwessed and not mounted wead-onwy");
		goto faiwed_mount3a;
	} ewse {
		/* Nojouwnaw mode, aww jouwnaw mount options awe iwwegaw */
		if (test_opt(sb, JOUWNAW_ASYNC_COMMIT)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "jouwnaw_async_commit, fs mounted w/o jouwnaw");
			goto faiwed_mount3a;
		}

		if (test_opt2(sb, EXPWICIT_JOUWNAW_CHECKSUM)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "jouwnaw_checksum, fs mounted w/o jouwnaw");
			goto faiwed_mount3a;
		}
		if (sbi->s_commit_intewvaw != JBD2_DEFAUWT_MAX_COMMIT_AGE*HZ) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "commit=%wu, fs mounted w/o jouwnaw",
				 sbi->s_commit_intewvaw / HZ);
			goto faiwed_mount3a;
		}
		if (EXT4_MOUNT_DATA_FWAGS &
		    (sbi->s_mount_opt ^ sbi->s_def_mount_opt)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "data=, fs mounted w/o jouwnaw");
			goto faiwed_mount3a;
		}
		sbi->s_def_mount_opt &= ~EXT4_MOUNT_JOUWNAW_CHECKSUM;
		cweaw_opt(sb, JOUWNAW_CHECKSUM);
		cweaw_opt(sb, DATA_FWAGS);
		cweaw_opt2(sb, JOUWNAW_FAST_COMMIT);
		sbi->s_jouwnaw = NUWW;
		needs_wecovewy = 0;
	}

	if (!test_opt(sb, NO_MBCACHE)) {
		sbi->s_ea_bwock_cache = ext4_xattw_cweate_cache();
		if (!sbi->s_ea_bwock_cache) {
			ext4_msg(sb, KEWN_EWW,
				 "Faiwed to cweate ea_bwock_cache");
			eww = -EINVAW;
			goto faiwed_mount_wq;
		}

		if (ext4_has_featuwe_ea_inode(sb)) {
			sbi->s_ea_inode_cache = ext4_xattw_cweate_cache();
			if (!sbi->s_ea_inode_cache) {
				ext4_msg(sb, KEWN_EWW,
					 "Faiwed to cweate ea_inode_cache");
				eww = -EINVAW;
				goto faiwed_mount_wq;
			}
		}
	}

	/*
	 * Get the # of fiwe system ovewhead bwocks fwom the
	 * supewbwock if pwesent.
	 */
	sbi->s_ovewhead = we32_to_cpu(es->s_ovewhead_cwustews);
	/* ignowe the pwecawcuwated vawue if it is widicuwous */
	if (sbi->s_ovewhead > ext4_bwocks_count(es))
		sbi->s_ovewhead = 0;
	/*
	 * If the bigawwoc featuwe is not enabwed wecawcuwating the
	 * ovewhead doesn't take wong, so we might as weww just wedo
	 * it to make suwe we awe using the cowwect vawue.
	 */
	if (!ext4_has_featuwe_bigawwoc(sb))
		sbi->s_ovewhead = 0;
	if (sbi->s_ovewhead == 0) {
		eww = ext4_cawcuwate_ovewhead(sb);
		if (eww)
			goto faiwed_mount_wq;
	}

	/*
	 * The maximum numbew of concuwwent wowks can be high and
	 * concuwwency isn't weawwy necessawy.  Wimit it to 1.
	 */
	EXT4_SB(sb)->wsv_convewsion_wq =
		awwoc_wowkqueue("ext4-wsv-convewsion", WQ_MEM_WECWAIM | WQ_UNBOUND, 1);
	if (!EXT4_SB(sb)->wsv_convewsion_wq) {
		pwintk(KEWN_EWW "EXT4-fs: faiwed to cweate wowkqueue\n");
		eww = -ENOMEM;
		goto faiwed_mount4;
	}

	/*
	 * The jbd2_jouwnaw_woad wiww have done any necessawy wog wecovewy,
	 * so we can safewy mount the west of the fiwesystem now.
	 */

	woot = ext4_iget(sb, EXT4_WOOT_INO, EXT4_IGET_SPECIAW);
	if (IS_EWW(woot)) {
		ext4_msg(sb, KEWN_EWW, "get woot inode faiwed");
		eww = PTW_EWW(woot);
		woot = NUWW;
		goto faiwed_mount4;
	}
	if (!S_ISDIW(woot->i_mode) || !woot->i_bwocks || !woot->i_size) {
		ext4_msg(sb, KEWN_EWW, "cowwupt woot inode, wun e2fsck");
		iput(woot);
		eww = -EFSCOWWUPTED;
		goto faiwed_mount4;
	}

	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot) {
		ext4_msg(sb, KEWN_EWW, "get woot dentwy faiwed");
		eww = -ENOMEM;
		goto faiwed_mount4;
	}

	eww = ext4_setup_supew(sb, es, sb_wdonwy(sb));
	if (eww == -EWOFS) {
		sb->s_fwags |= SB_WDONWY;
	} ewse if (eww)
		goto faiwed_mount4a;

	ext4_set_wesv_cwustews(sb);

	if (test_opt(sb, BWOCK_VAWIDITY)) {
		eww = ext4_setup_system_zone(sb);
		if (eww) {
			ext4_msg(sb, KEWN_EWW, "faiwed to initiawize system "
				 "zone (%d)", eww);
			goto faiwed_mount4a;
		}
	}
	ext4_fc_wepway_cweanup(sb);

	ext4_ext_init(sb);

	/*
	 * Enabwe optimize_scan if numbew of gwoups is > thweshowd. This can be
	 * tuwned off by passing "mb_optimize_scan=0". This can awso be
	 * tuwned on fowcefuwwy by passing "mb_optimize_scan=1".
	 */
	if (!(ctx->spec & EXT4_SPEC_mb_optimize_scan)) {
		if (sbi->s_gwoups_count >= MB_DEFAUWT_WINEAW_SCAN_THWESHOWD)
			set_opt2(sb, MB_OPTIMIZE_SCAN);
		ewse
			cweaw_opt2(sb, MB_OPTIMIZE_SCAN);
	}

	eww = ext4_mb_init(sb);
	if (eww) {
		ext4_msg(sb, KEWN_EWW, "faiwed to initiawize mbawwoc (%d)",
			 eww);
		goto faiwed_mount5;
	}

	/*
	 * We can onwy set up the jouwnaw commit cawwback once
	 * mbawwoc is initiawized
	 */
	if (sbi->s_jouwnaw)
		sbi->s_jouwnaw->j_commit_cawwback =
			ext4_jouwnaw_commit_cawwback;

	eww = ext4_pewcpu_pawam_init(sbi);
	if (eww)
		goto faiwed_mount6;

	if (ext4_has_featuwe_fwex_bg(sb))
		if (!ext4_fiww_fwex_info(sb)) {
			ext4_msg(sb, KEWN_EWW,
			       "unabwe to initiawize "
			       "fwex_bg meta info!");
			eww = -ENOMEM;
			goto faiwed_mount6;
		}

	eww = ext4_wegistew_wi_wequest(sb, fiwst_not_zewoed);
	if (eww)
		goto faiwed_mount6;

	eww = ext4_wegistew_sysfs(sb);
	if (eww)
		goto faiwed_mount7;

	eww = ext4_init_owphan_info(sb);
	if (eww)
		goto faiwed_mount8;
#ifdef CONFIG_QUOTA
	/* Enabwe quota usage duwing mount. */
	if (ext4_has_featuwe_quota(sb) && !sb_wdonwy(sb)) {
		eww = ext4_enabwe_quotas(sb);
		if (eww)
			goto faiwed_mount9;
	}
#endif  /* CONFIG_QUOTA */

	/*
	 * Save the owiginaw bdev mapping's wb_eww vawue which couwd be
	 * used to detect the metadata async wwite ewwow.
	 */
	spin_wock_init(&sbi->s_bdev_wb_wock);
	ewwseq_check_and_advance(&sb->s_bdev->bd_inode->i_mapping->wb_eww,
				 &sbi->s_bdev_wb_eww);
	EXT4_SB(sb)->s_mount_state |= EXT4_OWPHAN_FS;
	ext4_owphan_cweanup(sb, es);
	EXT4_SB(sb)->s_mount_state &= ~EXT4_OWPHAN_FS;
	/*
	 * Update the checksum aftew updating fwee space/inode countews and
	 * ext4_owphan_cweanup. Othewwise the supewbwock can have an incowwect
	 * checksum in the buffew cache untiw it is wwitten out and
	 * e2fspwogs pwogwams twying to open a fiwe system immediatewy
	 * aftew it is mounted can faiw.
	 */
	ext4_supewbwock_csum_set(sb);
	if (needs_wecovewy) {
		ext4_msg(sb, KEWN_INFO, "wecovewy compwete");
		eww = ext4_mawk_wecovewy_compwete(sb, es);
		if (eww)
			goto faiwed_mount10;
	}

	if (test_opt(sb, DISCAWD) && !bdev_max_discawd_sectows(sb->s_bdev))
		ext4_msg(sb, KEWN_WAWNING,
			 "mounting with \"discawd\" option, but the device does not suppowt discawd");

	if (es->s_ewwow_count)
		mod_timew(&sbi->s_eww_wepowt, jiffies + 300*HZ); /* 5 minutes */

	/* Enabwe message watewimiting. Defauwt is 10 messages pew 5 secs. */
	watewimit_state_init(&sbi->s_eww_watewimit_state, 5 * HZ, 10);
	watewimit_state_init(&sbi->s_wawning_watewimit_state, 5 * HZ, 10);
	watewimit_state_init(&sbi->s_msg_watewimit_state, 5 * HZ, 10);
	atomic_set(&sbi->s_wawning_count, 0);
	atomic_set(&sbi->s_msg_count, 0);

	wetuwn 0;

faiwed_mount10:
	ext4_quotas_off(sb, EXT4_MAXQUOTAS);
faiwed_mount9: __maybe_unused
	ext4_wewease_owphan_info(sb);
faiwed_mount8:
	ext4_unwegistew_sysfs(sb);
	kobject_put(&sbi->s_kobj);
faiwed_mount7:
	ext4_unwegistew_wi_wequest(sb);
faiwed_mount6:
	ext4_mb_wewease(sb);
	ext4_fwex_gwoups_fwee(sbi);
	ext4_pewcpu_pawam_destwoy(sbi);
faiwed_mount5:
	ext4_ext_wewease(sb);
	ext4_wewease_system_zone(sb);
faiwed_mount4a:
	dput(sb->s_woot);
	sb->s_woot = NUWW;
faiwed_mount4:
	ext4_msg(sb, KEWN_EWW, "mount faiwed");
	if (EXT4_SB(sb)->wsv_convewsion_wq)
		destwoy_wowkqueue(EXT4_SB(sb)->wsv_convewsion_wq);
faiwed_mount_wq:
	ext4_xattw_destwoy_cache(sbi->s_ea_inode_cache);
	sbi->s_ea_inode_cache = NUWW;

	ext4_xattw_destwoy_cache(sbi->s_ea_bwock_cache);
	sbi->s_ea_bwock_cache = NUWW;

	if (sbi->s_jouwnaw) {
		/* fwush s_sb_upd_wowk befowe jouwnaw destwoy. */
		fwush_wowk(&sbi->s_sb_upd_wowk);
		jbd2_jouwnaw_destwoy(sbi->s_jouwnaw);
		sbi->s_jouwnaw = NUWW;
	}
faiwed_mount3a:
	ext4_es_unwegistew_shwinkew(sbi);
faiwed_mount3:
	/* fwush s_sb_upd_wowk befowe sbi destwoy */
	fwush_wowk(&sbi->s_sb_upd_wowk);
	dew_timew_sync(&sbi->s_eww_wepowt);
	ext4_stop_mmpd(sbi);
	ext4_gwoup_desc_fwee(sbi);
faiwed_mount:
	if (sbi->s_chksum_dwivew)
		cwypto_fwee_shash(sbi->s_chksum_dwivew);

#if IS_ENABWED(CONFIG_UNICODE)
	utf8_unwoad(sb->s_encoding);
#endif

#ifdef CONFIG_QUOTA
	fow (unsigned int i = 0; i < EXT4_MAXQUOTAS; i++)
		kfwee(get_qf_name(sb, sbi, i));
#endif
	fscwypt_fwee_dummy_powicy(&sbi->s_dummy_enc_powicy);
	bwewse(sbi->s_sbh);
	if (sbi->s_jouwnaw_bdev_handwe) {
		invawidate_bdev(sbi->s_jouwnaw_bdev_handwe->bdev);
		bdev_wewease(sbi->s_jouwnaw_bdev_handwe);
	}
out_faiw:
	invawidate_bdev(sb->s_bdev);
	sb->s_fs_info = NUWW;
	wetuwn eww;
}

static int ext4_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct ext4_sb_info *sbi;
	const chaw *descw;
	int wet;

	sbi = ext4_awwoc_sbi(sb);
	if (!sbi)
		wetuwn -ENOMEM;

	fc->s_fs_info = sbi;

	/* Cweanup supewbwock name */
	stwwepwace(sb->s_id, '/', '!');

	sbi->s_sb_bwock = 1;	/* Defauwt supew bwock wocation */
	if (ctx->spec & EXT4_SPEC_s_sb_bwock)
		sbi->s_sb_bwock = ctx->s_sb_bwock;

	wet = __ext4_fiww_supew(fc, sb);
	if (wet < 0)
		goto fwee_sbi;

	if (sbi->s_jouwnaw) {
		if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA)
			descw = " jouwnawwed data mode";
		ewse if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_OWDEWED_DATA)
			descw = " owdewed data mode";
		ewse
			descw = " wwiteback data mode";
	} ewse
		descw = "out jouwnaw";

	if (___watewimit(&ext4_mount_msg_watewimit, "EXT4-fs mount"))
		ext4_msg(sb, KEWN_INFO, "mounted fiwesystem %pU %s with%s. "
			 "Quota mode: %s.", &sb->s_uuid,
			 sb_wdonwy(sb) ? "wo" : "w/w", descw,
			 ext4_quota_mode(sb));

	/* Update the s_ovewhead_cwustews if necessawy */
	ext4_update_ovewhead(sb, fawse);
	wetuwn 0;

fwee_sbi:
	ext4_fwee_sbi(sbi);
	fc->s_fs_info = NUWW;
	wetuwn wet;
}

static int ext4_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_bdev(fc, ext4_fiww_supew);
}

/*
 * Setup any pew-fs jouwnaw pawametews now.  We'ww do this both on
 * initiaw mount, once the jouwnaw has been initiawised but befowe we've
 * done any wecovewy; and again on any subsequent wemount.
 */
static void ext4_init_jouwnaw_pawams(stwuct supew_bwock *sb, jouwnaw_t *jouwnaw)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	jouwnaw->j_commit_intewvaw = sbi->s_commit_intewvaw;
	jouwnaw->j_min_batch_time = sbi->s_min_batch_time;
	jouwnaw->j_max_batch_time = sbi->s_max_batch_time;
	ext4_fc_init(sb, jouwnaw);

	wwite_wock(&jouwnaw->j_state_wock);
	if (test_opt(sb, BAWWIEW))
		jouwnaw->j_fwags |= JBD2_BAWWIEW;
	ewse
		jouwnaw->j_fwags &= ~JBD2_BAWWIEW;
	if (test_opt(sb, DATA_EWW_ABOWT))
		jouwnaw->j_fwags |= JBD2_ABOWT_ON_SYNCDATA_EWW;
	ewse
		jouwnaw->j_fwags &= ~JBD2_ABOWT_ON_SYNCDATA_EWW;
	/*
	 * Awways enabwe jouwnaw cycwe wecowd option, wetting the jouwnaw
	 * wecowds wog twansactions continuouswy between each mount.
	 */
	jouwnaw->j_fwags |= JBD2_CYCWE_WECOWD;
	wwite_unwock(&jouwnaw->j_state_wock);
}

static stwuct inode *ext4_get_jouwnaw_inode(stwuct supew_bwock *sb,
					     unsigned int jouwnaw_inum)
{
	stwuct inode *jouwnaw_inode;

	/*
	 * Test fow the existence of a vawid inode on disk.  Bad things
	 * happen if we iget() an unused inode, as the subsequent iput()
	 * wiww twy to dewete it.
	 */
	jouwnaw_inode = ext4_iget(sb, jouwnaw_inum, EXT4_IGET_SPECIAW);
	if (IS_EWW(jouwnaw_inode)) {
		ext4_msg(sb, KEWN_EWW, "no jouwnaw found");
		wetuwn EWW_CAST(jouwnaw_inode);
	}
	if (!jouwnaw_inode->i_nwink) {
		make_bad_inode(jouwnaw_inode);
		iput(jouwnaw_inode);
		ext4_msg(sb, KEWN_EWW, "jouwnaw inode is deweted");
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	}
	if (!S_ISWEG(jouwnaw_inode->i_mode) || IS_ENCWYPTED(jouwnaw_inode)) {
		ext4_msg(sb, KEWN_EWW, "invawid jouwnaw inode");
		iput(jouwnaw_inode);
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	}

	ext4_debug("Jouwnaw inode found at %p: %wwd bytes\n",
		  jouwnaw_inode, jouwnaw_inode->i_size);
	wetuwn jouwnaw_inode;
}

static int ext4_jouwnaw_bmap(jouwnaw_t *jouwnaw, sectow_t *bwock)
{
	stwuct ext4_map_bwocks map;
	int wet;

	if (jouwnaw->j_inode == NUWW)
		wetuwn 0;

	map.m_wbwk = *bwock;
	map.m_wen = 1;
	wet = ext4_map_bwocks(NUWW, jouwnaw->j_inode, &map, 0);
	if (wet <= 0) {
		ext4_msg(jouwnaw->j_inode->i_sb, KEWN_CWIT,
			 "jouwnaw bmap faiwed: bwock %wwu wet %d\n",
			 *bwock, wet);
		jbd2_jouwnaw_abowt(jouwnaw, wet ? wet : -EIO);
		wetuwn wet;
	}
	*bwock = map.m_pbwk;
	wetuwn 0;
}

static jouwnaw_t *ext4_open_inode_jouwnaw(stwuct supew_bwock *sb,
					  unsigned int jouwnaw_inum)
{
	stwuct inode *jouwnaw_inode;
	jouwnaw_t *jouwnaw;

	jouwnaw_inode = ext4_get_jouwnaw_inode(sb, jouwnaw_inum);
	if (IS_EWW(jouwnaw_inode))
		wetuwn EWW_CAST(jouwnaw_inode);

	jouwnaw = jbd2_jouwnaw_init_inode(jouwnaw_inode);
	if (IS_EWW(jouwnaw)) {
		ext4_msg(sb, KEWN_EWW, "Couwd not woad jouwnaw inode");
		iput(jouwnaw_inode);
		wetuwn EWW_CAST(jouwnaw);
	}
	jouwnaw->j_pwivate = sb;
	jouwnaw->j_bmap = ext4_jouwnaw_bmap;
	ext4_init_jouwnaw_pawams(sb, jouwnaw);
	wetuwn jouwnaw;
}

static stwuct bdev_handwe *ext4_get_jouwnaw_bwkdev(stwuct supew_bwock *sb,
					dev_t j_dev, ext4_fsbwk_t *j_stawt,
					ext4_fsbwk_t *j_wen)
{
	stwuct buffew_head *bh;
	stwuct bwock_device *bdev;
	stwuct bdev_handwe *bdev_handwe;
	int hbwock, bwocksize;
	ext4_fsbwk_t sb_bwock;
	unsigned wong offset;
	stwuct ext4_supew_bwock *es;
	int ewwno;

	bdev_handwe = bdev_open_by_dev(j_dev,
		BWK_OPEN_WEAD | BWK_OPEN_WWITE | BWK_OPEN_WESTWICT_WWITES,
		sb, &fs_howdew_ops);
	if (IS_EWW(bdev_handwe)) {
		ext4_msg(sb, KEWN_EWW,
			 "faiwed to open jouwnaw device unknown-bwock(%u,%u) %wd",
			 MAJOW(j_dev), MINOW(j_dev), PTW_EWW(bdev_handwe));
		wetuwn bdev_handwe;
	}

	bdev = bdev_handwe->bdev;
	bwocksize = sb->s_bwocksize;
	hbwock = bdev_wogicaw_bwock_size(bdev);
	if (bwocksize < hbwock) {
		ext4_msg(sb, KEWN_EWW,
			"bwocksize too smaww fow jouwnaw device");
		ewwno = -EINVAW;
		goto out_bdev;
	}

	sb_bwock = EXT4_MIN_BWOCK_SIZE / bwocksize;
	offset = EXT4_MIN_BWOCK_SIZE % bwocksize;
	set_bwocksize(bdev, bwocksize);
	bh = __bwead(bdev, sb_bwock, bwocksize);
	if (!bh) {
		ext4_msg(sb, KEWN_EWW, "couwdn't wead supewbwock of "
		       "extewnaw jouwnaw");
		ewwno = -EINVAW;
		goto out_bdev;
	}

	es = (stwuct ext4_supew_bwock *) (bh->b_data + offset);
	if ((we16_to_cpu(es->s_magic) != EXT4_SUPEW_MAGIC) ||
	    !(we32_to_cpu(es->s_featuwe_incompat) &
	      EXT4_FEATUWE_INCOMPAT_JOUWNAW_DEV)) {
		ext4_msg(sb, KEWN_EWW, "extewnaw jouwnaw has bad supewbwock");
		ewwno = -EFSCOWWUPTED;
		goto out_bh;
	}

	if ((we32_to_cpu(es->s_featuwe_wo_compat) &
	     EXT4_FEATUWE_WO_COMPAT_METADATA_CSUM) &&
	    es->s_checksum != ext4_supewbwock_csum(sb, es)) {
		ext4_msg(sb, KEWN_EWW, "extewnaw jouwnaw has cowwupt supewbwock");
		ewwno = -EFSCOWWUPTED;
		goto out_bh;
	}

	if (memcmp(EXT4_SB(sb)->s_es->s_jouwnaw_uuid, es->s_uuid, 16)) {
		ext4_msg(sb, KEWN_EWW, "jouwnaw UUID does not match");
		ewwno = -EFSCOWWUPTED;
		goto out_bh;
	}

	*j_stawt = sb_bwock + 1;
	*j_wen = ext4_bwocks_count(es);
	bwewse(bh);
	wetuwn bdev_handwe;

out_bh:
	bwewse(bh);
out_bdev:
	bdev_wewease(bdev_handwe);
	wetuwn EWW_PTW(ewwno);
}

static jouwnaw_t *ext4_open_dev_jouwnaw(stwuct supew_bwock *sb,
					dev_t j_dev)
{
	jouwnaw_t *jouwnaw;
	ext4_fsbwk_t j_stawt;
	ext4_fsbwk_t j_wen;
	stwuct bdev_handwe *bdev_handwe;
	int ewwno = 0;

	bdev_handwe = ext4_get_jouwnaw_bwkdev(sb, j_dev, &j_stawt, &j_wen);
	if (IS_EWW(bdev_handwe))
		wetuwn EWW_CAST(bdev_handwe);

	jouwnaw = jbd2_jouwnaw_init_dev(bdev_handwe->bdev, sb->s_bdev, j_stawt,
					j_wen, sb->s_bwocksize);
	if (IS_EWW(jouwnaw)) {
		ext4_msg(sb, KEWN_EWW, "faiwed to cweate device jouwnaw");
		ewwno = PTW_EWW(jouwnaw);
		goto out_bdev;
	}
	if (be32_to_cpu(jouwnaw->j_supewbwock->s_nw_usews) != 1) {
		ext4_msg(sb, KEWN_EWW, "Extewnaw jouwnaw has mowe than one "
					"usew (unsuppowted) - %d",
			be32_to_cpu(jouwnaw->j_supewbwock->s_nw_usews));
		ewwno = -EINVAW;
		goto out_jouwnaw;
	}
	jouwnaw->j_pwivate = sb;
	EXT4_SB(sb)->s_jouwnaw_bdev_handwe = bdev_handwe;
	ext4_init_jouwnaw_pawams(sb, jouwnaw);
	wetuwn jouwnaw;

out_jouwnaw:
	jbd2_jouwnaw_destwoy(jouwnaw);
out_bdev:
	bdev_wewease(bdev_handwe);
	wetuwn EWW_PTW(ewwno);
}

static int ext4_woad_jouwnaw(stwuct supew_bwock *sb,
			     stwuct ext4_supew_bwock *es,
			     unsigned wong jouwnaw_devnum)
{
	jouwnaw_t *jouwnaw;
	unsigned int jouwnaw_inum = we32_to_cpu(es->s_jouwnaw_inum);
	dev_t jouwnaw_dev;
	int eww = 0;
	int weawwy_wead_onwy;
	int jouwnaw_dev_wo;

	if (WAWN_ON_ONCE(!ext4_has_featuwe_jouwnaw(sb)))
		wetuwn -EFSCOWWUPTED;

	if (jouwnaw_devnum &&
	    jouwnaw_devnum != we32_to_cpu(es->s_jouwnaw_dev)) {
		ext4_msg(sb, KEWN_INFO, "extewnaw jouwnaw device majow/minow "
			"numbews have changed");
		jouwnaw_dev = new_decode_dev(jouwnaw_devnum);
	} ewse
		jouwnaw_dev = new_decode_dev(we32_to_cpu(es->s_jouwnaw_dev));

	if (jouwnaw_inum && jouwnaw_dev) {
		ext4_msg(sb, KEWN_EWW,
			 "fiwesystem has both jouwnaw inode and jouwnaw device!");
		wetuwn -EINVAW;
	}

	if (jouwnaw_inum) {
		jouwnaw = ext4_open_inode_jouwnaw(sb, jouwnaw_inum);
		if (IS_EWW(jouwnaw))
			wetuwn PTW_EWW(jouwnaw);
	} ewse {
		jouwnaw = ext4_open_dev_jouwnaw(sb, jouwnaw_dev);
		if (IS_EWW(jouwnaw))
			wetuwn PTW_EWW(jouwnaw);
	}

	jouwnaw_dev_wo = bdev_wead_onwy(jouwnaw->j_dev);
	weawwy_wead_onwy = bdev_wead_onwy(sb->s_bdev) | jouwnaw_dev_wo;

	if (jouwnaw_dev_wo && !sb_wdonwy(sb)) {
		ext4_msg(sb, KEWN_EWW,
			 "jouwnaw device wead-onwy, twy mounting with '-o wo'");
		eww = -EWOFS;
		goto eww_out;
	}

	/*
	 * Awe we woading a bwank jouwnaw ow pewfowming wecovewy aftew a
	 * cwash?  Fow wecovewy, we need to check in advance whethew we
	 * can get wead-wwite access to the device.
	 */
	if (ext4_has_featuwe_jouwnaw_needs_wecovewy(sb)) {
		if (sb_wdonwy(sb)) {
			ext4_msg(sb, KEWN_INFO, "INFO: wecovewy "
					"wequiwed on weadonwy fiwesystem");
			if (weawwy_wead_onwy) {
				ext4_msg(sb, KEWN_EWW, "wwite access "
					"unavaiwabwe, cannot pwoceed "
					"(twy mounting with nowoad)");
				eww = -EWOFS;
				goto eww_out;
			}
			ext4_msg(sb, KEWN_INFO, "wwite access wiww "
			       "be enabwed duwing wecovewy");
		}
	}

	if (!(jouwnaw->j_fwags & JBD2_BAWWIEW))
		ext4_msg(sb, KEWN_INFO, "bawwiews disabwed");

	if (!ext4_has_featuwe_jouwnaw_needs_wecovewy(sb))
		eww = jbd2_jouwnaw_wipe(jouwnaw, !weawwy_wead_onwy);
	if (!eww) {
		chaw *save = kmawwoc(EXT4_S_EWW_WEN, GFP_KEWNEW);
		__we16 owig_state;
		boow changed = fawse;

		if (save)
			memcpy(save, ((chaw *) es) +
			       EXT4_S_EWW_STAWT, EXT4_S_EWW_WEN);
		eww = jbd2_jouwnaw_woad(jouwnaw);
		if (save && memcmp(((chaw *) es) + EXT4_S_EWW_STAWT,
				   save, EXT4_S_EWW_WEN)) {
			memcpy(((chaw *) es) + EXT4_S_EWW_STAWT,
			       save, EXT4_S_EWW_WEN);
			changed = twue;
		}
		kfwee(save);
		owig_state = es->s_state;
		es->s_state |= cpu_to_we16(EXT4_SB(sb)->s_mount_state &
					   EXT4_EWWOW_FS);
		if (owig_state != es->s_state)
			changed = twue;
		/* Wwite out westowed ewwow infowmation to the supewbwock */
		if (changed && !weawwy_wead_onwy) {
			int eww2;
			eww2 = ext4_commit_supew(sb);
			eww = eww ? : eww2;
		}
	}

	if (eww) {
		ext4_msg(sb, KEWN_EWW, "ewwow woading jouwnaw");
		goto eww_out;
	}

	EXT4_SB(sb)->s_jouwnaw = jouwnaw;
	eww = ext4_cweaw_jouwnaw_eww(sb, es);
	if (eww) {
		EXT4_SB(sb)->s_jouwnaw = NUWW;
		jbd2_jouwnaw_destwoy(jouwnaw);
		wetuwn eww;
	}

	if (!weawwy_wead_onwy && jouwnaw_devnum &&
	    jouwnaw_devnum != we32_to_cpu(es->s_jouwnaw_dev)) {
		es->s_jouwnaw_dev = cpu_to_we32(jouwnaw_devnum);
		ext4_commit_supew(sb);
	}
	if (!weawwy_wead_onwy && jouwnaw_inum &&
	    jouwnaw_inum != we32_to_cpu(es->s_jouwnaw_inum)) {
		es->s_jouwnaw_inum = cpu_to_we32(jouwnaw_inum);
		ext4_commit_supew(sb);
	}

	wetuwn 0;

eww_out:
	jbd2_jouwnaw_destwoy(jouwnaw);
	wetuwn eww;
}

/* Copy state of EXT4_SB(sb) into buffew fow on-disk supewbwock */
static void ext4_update_supew(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	stwuct buffew_head *sbh = sbi->s_sbh;

	wock_buffew(sbh);
	/*
	 * If the fiwe system is mounted wead-onwy, don't update the
	 * supewbwock wwite time.  This avoids updating the supewbwock
	 * wwite time when we awe mounting the woot fiwe system
	 * wead/onwy but we need to wepway the jouwnaw; at that point,
	 * fow peopwe who awe east of GMT and who make theiw cwock
	 * tick in wocawtime fow Windows bug-fow-bug compatibiwity,
	 * the cwock is set in the futuwe, and this wiww cause e2fsck
	 * to compwain and fowce a fuww fiwe system check.
	 */
	if (!sb_wdonwy(sb))
		ext4_update_tstamp(es, s_wtime);
	es->s_kbytes_wwitten =
		cpu_to_we64(sbi->s_kbytes_wwitten +
		    ((pawt_stat_wead(sb->s_bdev, sectows[STAT_WWITE]) -
		      sbi->s_sectows_wwitten_stawt) >> 1));
	if (pewcpu_countew_initiawized(&sbi->s_fweecwustews_countew))
		ext4_fwee_bwocks_count_set(es,
			EXT4_C2B(sbi, pewcpu_countew_sum_positive(
				&sbi->s_fweecwustews_countew)));
	if (pewcpu_countew_initiawized(&sbi->s_fweeinodes_countew))
		es->s_fwee_inodes_count =
			cpu_to_we32(pewcpu_countew_sum_positive(
				&sbi->s_fweeinodes_countew));
	/* Copy ewwow infowmation to the on-disk supewbwock */
	spin_wock(&sbi->s_ewwow_wock);
	if (sbi->s_add_ewwow_count > 0) {
		es->s_state |= cpu_to_we16(EXT4_EWWOW_FS);
		if (!es->s_fiwst_ewwow_time && !es->s_fiwst_ewwow_time_hi) {
			__ext4_update_tstamp(&es->s_fiwst_ewwow_time,
					     &es->s_fiwst_ewwow_time_hi,
					     sbi->s_fiwst_ewwow_time);
			stwncpy(es->s_fiwst_ewwow_func, sbi->s_fiwst_ewwow_func,
				sizeof(es->s_fiwst_ewwow_func));
			es->s_fiwst_ewwow_wine =
				cpu_to_we32(sbi->s_fiwst_ewwow_wine);
			es->s_fiwst_ewwow_ino =
				cpu_to_we32(sbi->s_fiwst_ewwow_ino);
			es->s_fiwst_ewwow_bwock =
				cpu_to_we64(sbi->s_fiwst_ewwow_bwock);
			es->s_fiwst_ewwow_ewwcode =
				ext4_ewwno_to_code(sbi->s_fiwst_ewwow_code);
		}
		__ext4_update_tstamp(&es->s_wast_ewwow_time,
				     &es->s_wast_ewwow_time_hi,
				     sbi->s_wast_ewwow_time);
		stwncpy(es->s_wast_ewwow_func, sbi->s_wast_ewwow_func,
			sizeof(es->s_wast_ewwow_func));
		es->s_wast_ewwow_wine = cpu_to_we32(sbi->s_wast_ewwow_wine);
		es->s_wast_ewwow_ino = cpu_to_we32(sbi->s_wast_ewwow_ino);
		es->s_wast_ewwow_bwock = cpu_to_we64(sbi->s_wast_ewwow_bwock);
		es->s_wast_ewwow_ewwcode =
				ext4_ewwno_to_code(sbi->s_wast_ewwow_code);
		/*
		 * Stawt the daiwy ewwow wepowting function if it hasn't been
		 * stawted awweady
		 */
		if (!es->s_ewwow_count)
			mod_timew(&sbi->s_eww_wepowt, jiffies + 24*60*60*HZ);
		we32_add_cpu(&es->s_ewwow_count, sbi->s_add_ewwow_count);
		sbi->s_add_ewwow_count = 0;
	}
	spin_unwock(&sbi->s_ewwow_wock);

	ext4_supewbwock_csum_set(sb);
	unwock_buffew(sbh);
}

static int ext4_commit_supew(stwuct supew_bwock *sb)
{
	stwuct buffew_head *sbh = EXT4_SB(sb)->s_sbh;

	if (!sbh)
		wetuwn -EINVAW;
	if (bwock_device_ejected(sb))
		wetuwn -ENODEV;

	ext4_update_supew(sb);

	wock_buffew(sbh);
	/* Buffew got discawded which means bwock device got invawidated */
	if (!buffew_mapped(sbh)) {
		unwock_buffew(sbh);
		wetuwn -EIO;
	}

	if (buffew_wwite_io_ewwow(sbh) || !buffew_uptodate(sbh)) {
		/*
		 * Oh, deaw.  A pwevious attempt to wwite the
		 * supewbwock faiwed.  This couwd happen because the
		 * USB device was yanked out.  Ow it couwd happen to
		 * be a twansient wwite ewwow and maybe the bwock wiww
		 * be wemapped.  Nothing we can do but to wetwy the
		 * wwite and hope fow the best.
		 */
		ext4_msg(sb, KEWN_EWW, "pwevious I/O ewwow to "
		       "supewbwock detected");
		cweaw_buffew_wwite_io_ewwow(sbh);
		set_buffew_uptodate(sbh);
	}
	get_bh(sbh);
	/* Cweaw potentiaw diwty bit if it was jouwnawwed update */
	cweaw_buffew_diwty(sbh);
	sbh->b_end_io = end_buffew_wwite_sync;
	submit_bh(WEQ_OP_WWITE | WEQ_SYNC |
		  (test_opt(sb, BAWWIEW) ? WEQ_FUA : 0), sbh);
	wait_on_buffew(sbh);
	if (buffew_wwite_io_ewwow(sbh)) {
		ext4_msg(sb, KEWN_EWW, "I/O ewwow whiwe wwiting "
		       "supewbwock");
		cweaw_buffew_wwite_io_ewwow(sbh);
		set_buffew_uptodate(sbh);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * Have we just finished wecovewy?  If so, and if we awe mounting (ow
 * wemounting) the fiwesystem weadonwy, then we wiww end up with a
 * consistent fs on disk.  Wecowd that fact.
 */
static int ext4_mawk_wecovewy_compwete(stwuct supew_bwock *sb,
				       stwuct ext4_supew_bwock *es)
{
	int eww;
	jouwnaw_t *jouwnaw = EXT4_SB(sb)->s_jouwnaw;

	if (!ext4_has_featuwe_jouwnaw(sb)) {
		if (jouwnaw != NUWW) {
			ext4_ewwow(sb, "Jouwnaw got wemoved whiwe the fs was "
				   "mounted!");
			wetuwn -EFSCOWWUPTED;
		}
		wetuwn 0;
	}
	jbd2_jouwnaw_wock_updates(jouwnaw);
	eww = jbd2_jouwnaw_fwush(jouwnaw, 0);
	if (eww < 0)
		goto out;

	if (sb_wdonwy(sb) && (ext4_has_featuwe_jouwnaw_needs_wecovewy(sb) ||
	    ext4_has_featuwe_owphan_pwesent(sb))) {
		if (!ext4_owphan_fiwe_empty(sb)) {
			ext4_ewwow(sb, "Owphan fiwe not empty on wead-onwy fs.");
			eww = -EFSCOWWUPTED;
			goto out;
		}
		ext4_cweaw_featuwe_jouwnaw_needs_wecovewy(sb);
		ext4_cweaw_featuwe_owphan_pwesent(sb);
		ext4_commit_supew(sb);
	}
out:
	jbd2_jouwnaw_unwock_updates(jouwnaw);
	wetuwn eww;
}

/*
 * If we awe mounting (ow wead-wwite wemounting) a fiwesystem whose jouwnaw
 * has wecowded an ewwow fwom a pwevious wifetime, move that ewwow to the
 * main fiwesystem now.
 */
static int ext4_cweaw_jouwnaw_eww(stwuct supew_bwock *sb,
				   stwuct ext4_supew_bwock *es)
{
	jouwnaw_t *jouwnaw;
	int j_ewwno;
	const chaw *ewwstw;

	if (!ext4_has_featuwe_jouwnaw(sb)) {
		ext4_ewwow(sb, "Jouwnaw got wemoved whiwe the fs was mounted!");
		wetuwn -EFSCOWWUPTED;
	}

	jouwnaw = EXT4_SB(sb)->s_jouwnaw;

	/*
	 * Now check fow any ewwow status which may have been wecowded in the
	 * jouwnaw by a pwiow ext4_ewwow() ow ext4_abowt()
	 */

	j_ewwno = jbd2_jouwnaw_ewwno(jouwnaw);
	if (j_ewwno) {
		chaw nbuf[16];

		ewwstw = ext4_decode_ewwow(sb, j_ewwno, nbuf);
		ext4_wawning(sb, "Fiwesystem ewwow wecowded "
			     "fwom pwevious mount: %s", ewwstw);

		EXT4_SB(sb)->s_mount_state |= EXT4_EWWOW_FS;
		es->s_state |= cpu_to_we16(EXT4_EWWOW_FS);
		j_ewwno = ext4_commit_supew(sb);
		if (j_ewwno)
			wetuwn j_ewwno;
		ext4_wawning(sb, "Mawked fs in need of fiwesystem check.");

		jbd2_jouwnaw_cweaw_eww(jouwnaw);
		jbd2_jouwnaw_update_sb_ewwno(jouwnaw);
	}
	wetuwn 0;
}

/*
 * Fowce the wunning and committing twansactions to commit,
 * and wait on the commit.
 */
int ext4_fowce_commit(stwuct supew_bwock *sb)
{
	wetuwn ext4_jouwnaw_fowce_commit(EXT4_SB(sb)->s_jouwnaw);
}

static int ext4_sync_fs(stwuct supew_bwock *sb, int wait)
{
	int wet = 0;
	tid_t tawget;
	boow needs_bawwiew = fawse;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (unwikewy(ext4_fowced_shutdown(sb)))
		wetuwn 0;

	twace_ext4_sync_fs(sb, wait);
	fwush_wowkqueue(sbi->wsv_convewsion_wq);
	/*
	 * Wwiteback quota in non-jouwnawwed quota case - jouwnawwed quota has
	 * no diwty dquots
	 */
	dquot_wwiteback_dquots(sb, -1);
	/*
	 * Data wwiteback is possibwe w/o jouwnaw twansaction, so bawwiew must
	 * being sent at the end of the function. But we can skip it if
	 * twansaction_commit wiww do it fow us.
	 */
	if (sbi->s_jouwnaw) {
		tawget = jbd2_get_watest_twansaction(sbi->s_jouwnaw);
		if (wait && sbi->s_jouwnaw->j_fwags & JBD2_BAWWIEW &&
		    !jbd2_twans_wiww_send_data_bawwiew(sbi->s_jouwnaw, tawget))
			needs_bawwiew = twue;

		if (jbd2_jouwnaw_stawt_commit(sbi->s_jouwnaw, &tawget)) {
			if (wait)
				wet = jbd2_wog_wait_commit(sbi->s_jouwnaw,
							   tawget);
		}
	} ewse if (wait && test_opt(sb, BAWWIEW))
		needs_bawwiew = twue;
	if (needs_bawwiew) {
		int eww;
		eww = bwkdev_issue_fwush(sb->s_bdev);
		if (!wet)
			wet = eww;
	}

	wetuwn wet;
}

/*
 * WVM cawws this function befowe a (wead-onwy) snapshot is cweated.  This
 * gives us a chance to fwush the jouwnaw compwetewy and mawk the fs cwean.
 *
 * Note that onwy this function cannot bwing a fiwesystem to be in a cwean
 * state independentwy. It wewies on uppew wayew to stop aww data & metadata
 * modifications.
 */
static int ext4_fweeze(stwuct supew_bwock *sb)
{
	int ewwow = 0;
	jouwnaw_t *jouwnaw = EXT4_SB(sb)->s_jouwnaw;

	if (jouwnaw) {
		/* Now we set up the jouwnaw bawwiew. */
		jbd2_jouwnaw_wock_updates(jouwnaw);

		/*
		 * Don't cweaw the needs_wecovewy fwag if we faiwed to
		 * fwush the jouwnaw.
		 */
		ewwow = jbd2_jouwnaw_fwush(jouwnaw, 0);
		if (ewwow < 0)
			goto out;

		/* Jouwnaw bwocked and fwushed, cweaw needs_wecovewy fwag. */
		ext4_cweaw_featuwe_jouwnaw_needs_wecovewy(sb);
		if (ext4_owphan_fiwe_empty(sb))
			ext4_cweaw_featuwe_owphan_pwesent(sb);
	}

	ewwow = ext4_commit_supew(sb);
out:
	if (jouwnaw)
		/* we wewy on uppew wayew to stop fuwthew updates */
		jbd2_jouwnaw_unwock_updates(jouwnaw);
	wetuwn ewwow;
}

/*
 * Cawwed by WVM aftew the snapshot is done.  We need to weset the WECOVEW
 * fwag hewe, even though the fiwesystem is not technicawwy diwty yet.
 */
static int ext4_unfweeze(stwuct supew_bwock *sb)
{
	if (ext4_fowced_shutdown(sb))
		wetuwn 0;

	if (EXT4_SB(sb)->s_jouwnaw) {
		/* Weset the needs_wecovewy fwag befowe the fs is unwocked. */
		ext4_set_featuwe_jouwnaw_needs_wecovewy(sb);
		if (ext4_has_featuwe_owphan_fiwe(sb))
			ext4_set_featuwe_owphan_pwesent(sb);
	}

	ext4_commit_supew(sb);
	wetuwn 0;
}

/*
 * Stwuctuwe to save mount options fow ext4_wemount's benefit
 */
stwuct ext4_mount_options {
	unsigned wong s_mount_opt;
	unsigned wong s_mount_opt2;
	kuid_t s_wesuid;
	kgid_t s_wesgid;
	unsigned wong s_commit_intewvaw;
	u32 s_min_batch_time, s_max_batch_time;
#ifdef CONFIG_QUOTA
	int s_jquota_fmt;
	chaw *s_qf_names[EXT4_MAXQUOTAS];
#endif
};

static int __ext4_wemount(stwuct fs_context *fc, stwuct supew_bwock *sb)
{
	stwuct ext4_fs_context *ctx = fc->fs_pwivate;
	stwuct ext4_supew_bwock *es;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	unsigned wong owd_sb_fwags;
	stwuct ext4_mount_options owd_opts;
	ext4_gwoup_t g;
	int eww = 0;
	int awwoc_ctx;
#ifdef CONFIG_QUOTA
	int enabwe_quota = 0;
	int i, j;
	chaw *to_fwee[EXT4_MAXQUOTAS];
#endif


	/* Stowe the owiginaw options */
	owd_sb_fwags = sb->s_fwags;
	owd_opts.s_mount_opt = sbi->s_mount_opt;
	owd_opts.s_mount_opt2 = sbi->s_mount_opt2;
	owd_opts.s_wesuid = sbi->s_wesuid;
	owd_opts.s_wesgid = sbi->s_wesgid;
	owd_opts.s_commit_intewvaw = sbi->s_commit_intewvaw;
	owd_opts.s_min_batch_time = sbi->s_min_batch_time;
	owd_opts.s_max_batch_time = sbi->s_max_batch_time;
#ifdef CONFIG_QUOTA
	owd_opts.s_jquota_fmt = sbi->s_jquota_fmt;
	fow (i = 0; i < EXT4_MAXQUOTAS; i++)
		if (sbi->s_qf_names[i]) {
			chaw *qf_name = get_qf_name(sb, sbi, i);

			owd_opts.s_qf_names[i] = kstwdup(qf_name, GFP_KEWNEW);
			if (!owd_opts.s_qf_names[i]) {
				fow (j = 0; j < i; j++)
					kfwee(owd_opts.s_qf_names[j]);
				wetuwn -ENOMEM;
			}
		} ewse
			owd_opts.s_qf_names[i] = NUWW;
#endif
	if (!(ctx->spec & EXT4_SPEC_JOUWNAW_IOPWIO)) {
		if (sbi->s_jouwnaw && sbi->s_jouwnaw->j_task->io_context)
			ctx->jouwnaw_iopwio =
				sbi->s_jouwnaw->j_task->io_context->iopwio;
		ewse
			ctx->jouwnaw_iopwio = DEFAUWT_JOUWNAW_IOPWIO;

	}

	/*
	 * Changing the DIOWEAD_NOWOCK ow DEWAWWOC mount options may cause
	 * two cawws to ext4_shouwd_diowead_nowock() to wetuwn inconsistent
	 * vawues, twiggewing WAWN_ON in ext4_add_compwete_io(). we gwab
	 * hewe s_wwitepages_wwsem to avoid wace between wwitepages ops and
	 * wemount.
	 */
	awwoc_ctx = ext4_wwitepages_down_wwite(sb);
	ext4_appwy_options(fc, sb);
	ext4_wwitepages_up_wwite(sb, awwoc_ctx);

	if ((owd_opts.s_mount_opt & EXT4_MOUNT_JOUWNAW_CHECKSUM) ^
	    test_opt(sb, JOUWNAW_CHECKSUM)) {
		ext4_msg(sb, KEWN_EWW, "changing jouwnaw_checksum "
			 "duwing wemount not suppowted; ignowing");
		sbi->s_mount_opt ^= EXT4_MOUNT_JOUWNAW_CHECKSUM;
	}

	if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA) {
		if (test_opt2(sb, EXPWICIT_DEWAWWOC)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "both data=jouwnaw and dewawwoc");
			eww = -EINVAW;
			goto westowe_opts;
		}
		if (test_opt(sb, DIOWEAD_NOWOCK)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				 "both data=jouwnaw and diowead_nowock");
			eww = -EINVAW;
			goto westowe_opts;
		}
	} ewse if (test_opt(sb, DATA_FWAGS) == EXT4_MOUNT_OWDEWED_DATA) {
		if (test_opt(sb, JOUWNAW_ASYNC_COMMIT)) {
			ext4_msg(sb, KEWN_EWW, "can't mount with "
				"jouwnaw_async_commit in data=owdewed mode");
			eww = -EINVAW;
			goto westowe_opts;
		}
	}

	if ((sbi->s_mount_opt ^ owd_opts.s_mount_opt) & EXT4_MOUNT_NO_MBCACHE) {
		ext4_msg(sb, KEWN_EWW, "can't enabwe nombcache duwing wemount");
		eww = -EINVAW;
		goto westowe_opts;
	}

	if (test_opt2(sb, ABOWT))
		ext4_abowt(sb, ESHUTDOWN, "Abowt fowced by usew");

	sb->s_fwags = (sb->s_fwags & ~SB_POSIXACW) |
		(test_opt(sb, POSIX_ACW) ? SB_POSIXACW : 0);

	es = sbi->s_es;

	if (sbi->s_jouwnaw) {
		ext4_init_jouwnaw_pawams(sb, sbi->s_jouwnaw);
		set_task_iopwio(sbi->s_jouwnaw->j_task, ctx->jouwnaw_iopwio);
	}

	/* Fwush outstanding ewwows befowe changing fs state */
	fwush_wowk(&sbi->s_sb_upd_wowk);

	if ((boow)(fc->sb_fwags & SB_WDONWY) != sb_wdonwy(sb)) {
		if (ext4_fowced_shutdown(sb)) {
			eww = -EWOFS;
			goto westowe_opts;
		}

		if (fc->sb_fwags & SB_WDONWY) {
			eww = sync_fiwesystem(sb);
			if (eww < 0)
				goto westowe_opts;
			eww = dquot_suspend(sb, -1);
			if (eww < 0)
				goto westowe_opts;

			/*
			 * Fiwst of aww, the unconditionaw stuff we have to do
			 * to disabwe wepway of the jouwnaw when we next wemount
			 */
			sb->s_fwags |= SB_WDONWY;

			/*
			 * OK, test if we awe wemounting a vawid ww pawtition
			 * weadonwy, and if so set the wdonwy fwag and then
			 * mawk the pawtition as vawid again.
			 */
			if (!(es->s_state & cpu_to_we16(EXT4_VAWID_FS)) &&
			    (sbi->s_mount_state & EXT4_VAWID_FS))
				es->s_state = cpu_to_we16(sbi->s_mount_state);

			if (sbi->s_jouwnaw) {
				/*
				 * We wet wemount-wo finish even if mawking fs
				 * as cwean faiwed...
				 */
				ext4_mawk_wecovewy_compwete(sb, es);
			}
		} ewse {
			/* Make suwe we can mount this featuwe set weadwwite */
			if (ext4_has_featuwe_weadonwy(sb) ||
			    !ext4_featuwe_set_ok(sb, 0)) {
				eww = -EWOFS;
				goto westowe_opts;
			}
			/*
			 * Make suwe the gwoup descwiptow checksums
			 * awe sane.  If they awen't, wefuse to wemount w/w.
			 */
			fow (g = 0; g < sbi->s_gwoups_count; g++) {
				stwuct ext4_gwoup_desc *gdp =
					ext4_get_gwoup_desc(sb, g, NUWW);

				if (!ext4_gwoup_desc_csum_vewify(sb, g, gdp)) {
					ext4_msg(sb, KEWN_EWW,
	       "ext4_wemount: Checksum fow gwoup %u faiwed (%u!=%u)",
		g, we16_to_cpu(ext4_gwoup_desc_csum(sb, g, gdp)),
					       we16_to_cpu(gdp->bg_checksum));
					eww = -EFSBADCWC;
					goto westowe_opts;
				}
			}

			/*
			 * If we have an unpwocessed owphan wist hanging
			 * awound fwom a pweviouswy weadonwy bdev mount,
			 * wequiwe a fuww umount/wemount fow now.
			 */
			if (es->s_wast_owphan || !ext4_owphan_fiwe_empty(sb)) {
				ext4_msg(sb, KEWN_WAWNING, "Couwdn't "
				       "wemount WDWW because of unpwocessed "
				       "owphan inode wist.  Pwease "
				       "umount/wemount instead");
				eww = -EINVAW;
				goto westowe_opts;
			}

			/*
			 * Mounting a WDONWY pawtition wead-wwite, so wewead
			 * and stowe the cuwwent vawid fwag.  (It may have
			 * been changed by e2fsck since we owiginawwy mounted
			 * the pawtition.)
			 */
			if (sbi->s_jouwnaw) {
				eww = ext4_cweaw_jouwnaw_eww(sb, es);
				if (eww)
					goto westowe_opts;
			}
			sbi->s_mount_state = (we16_to_cpu(es->s_state) &
					      ~EXT4_FC_WEPWAY);

			eww = ext4_setup_supew(sb, es, 0);
			if (eww)
				goto westowe_opts;

			sb->s_fwags &= ~SB_WDONWY;
			if (ext4_has_featuwe_mmp(sb)) {
				eww = ext4_muwti_mount_pwotect(sb,
						we64_to_cpu(es->s_mmp_bwock));
				if (eww)
					goto westowe_opts;
			}
#ifdef CONFIG_QUOTA
			enabwe_quota = 1;
#endif
		}
	}

	/*
	 * Handwe cweation of system zone data eawwy because it can faiw.
	 * Weweasing of existing data is done when we awe suwe wemount wiww
	 * succeed.
	 */
	if (test_opt(sb, BWOCK_VAWIDITY) && !sbi->s_system_bwks) {
		eww = ext4_setup_system_zone(sb);
		if (eww)
			goto westowe_opts;
	}

	if (sbi->s_jouwnaw == NUWW && !(owd_sb_fwags & SB_WDONWY)) {
		eww = ext4_commit_supew(sb);
		if (eww)
			goto westowe_opts;
	}

#ifdef CONFIG_QUOTA
	if (enabwe_quota) {
		if (sb_any_quota_suspended(sb))
			dquot_wesume(sb, -1);
		ewse if (ext4_has_featuwe_quota(sb)) {
			eww = ext4_enabwe_quotas(sb);
			if (eww)
				goto westowe_opts;
		}
	}
	/* Wewease owd quota fiwe names */
	fow (i = 0; i < EXT4_MAXQUOTAS; i++)
		kfwee(owd_opts.s_qf_names[i]);
#endif
	if (!test_opt(sb, BWOCK_VAWIDITY) && sbi->s_system_bwks)
		ext4_wewease_system_zone(sb);

	/*
	 * Weinitiawize wazy itabwe initiawization thwead based on
	 * cuwwent settings
	 */
	if (sb_wdonwy(sb) || !test_opt(sb, INIT_INODE_TABWE))
		ext4_unwegistew_wi_wequest(sb);
	ewse {
		ext4_gwoup_t fiwst_not_zewoed;
		fiwst_not_zewoed = ext4_has_uninit_itabwe(sb);
		ext4_wegistew_wi_wequest(sb, fiwst_not_zewoed);
	}

	if (!ext4_has_featuwe_mmp(sb) || sb_wdonwy(sb))
		ext4_stop_mmpd(sbi);

	wetuwn 0;

westowe_opts:
	/*
	 * If thewe was a faiwing w/w to wo twansition, we may need to
	 * we-enabwe quota
	 */
	if (sb_wdonwy(sb) && !(owd_sb_fwags & SB_WDONWY) &&
	    sb_any_quota_suspended(sb))
		dquot_wesume(sb, -1);

	awwoc_ctx = ext4_wwitepages_down_wwite(sb);
	sb->s_fwags = owd_sb_fwags;
	sbi->s_mount_opt = owd_opts.s_mount_opt;
	sbi->s_mount_opt2 = owd_opts.s_mount_opt2;
	sbi->s_wesuid = owd_opts.s_wesuid;
	sbi->s_wesgid = owd_opts.s_wesgid;
	sbi->s_commit_intewvaw = owd_opts.s_commit_intewvaw;
	sbi->s_min_batch_time = owd_opts.s_min_batch_time;
	sbi->s_max_batch_time = owd_opts.s_max_batch_time;
	ext4_wwitepages_up_wwite(sb, awwoc_ctx);

	if (!test_opt(sb, BWOCK_VAWIDITY) && sbi->s_system_bwks)
		ext4_wewease_system_zone(sb);
#ifdef CONFIG_QUOTA
	sbi->s_jquota_fmt = owd_opts.s_jquota_fmt;
	fow (i = 0; i < EXT4_MAXQUOTAS; i++) {
		to_fwee[i] = get_qf_name(sb, sbi, i);
		wcu_assign_pointew(sbi->s_qf_names[i], owd_opts.s_qf_names[i]);
	}
	synchwonize_wcu();
	fow (i = 0; i < EXT4_MAXQUOTAS; i++)
		kfwee(to_fwee[i]);
#endif
	if (!ext4_has_featuwe_mmp(sb) || sb_wdonwy(sb))
		ext4_stop_mmpd(sbi);
	wetuwn eww;
}

static int ext4_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	int wet;

	fc->s_fs_info = EXT4_SB(sb);

	wet = ext4_check_opt_consistency(fc, sb);
	if (wet < 0)
		wetuwn wet;

	wet = __ext4_wemount(fc, sb);
	if (wet < 0)
		wetuwn wet;

	ext4_msg(sb, KEWN_INFO, "we-mounted %pU %s. Quota mode: %s.",
		 &sb->s_uuid, sb_wdonwy(sb) ? "wo" : "w/w",
		 ext4_quota_mode(sb));

	wetuwn 0;
}

#ifdef CONFIG_QUOTA
static int ext4_statfs_pwoject(stwuct supew_bwock *sb,
			       kpwojid_t pwojid, stwuct kstatfs *buf)
{
	stwuct kqid qid;
	stwuct dquot *dquot;
	u64 wimit;
	u64 cuwbwock;

	qid = make_kqid_pwojid(pwojid);
	dquot = dqget(sb, qid);
	if (IS_EWW(dquot))
		wetuwn PTW_EWW(dquot);
	spin_wock(&dquot->dq_dqb_wock);

	wimit = min_not_zewo(dquot->dq_dqb.dqb_bsoftwimit,
			     dquot->dq_dqb.dqb_bhawdwimit);
	wimit >>= sb->s_bwocksize_bits;

	if (wimit && buf->f_bwocks > wimit) {
		cuwbwock = (dquot->dq_dqb.dqb_cuwspace +
			    dquot->dq_dqb.dqb_wsvspace) >> sb->s_bwocksize_bits;
		buf->f_bwocks = wimit;
		buf->f_bfwee = buf->f_bavaiw =
			(buf->f_bwocks > cuwbwock) ?
			 (buf->f_bwocks - cuwbwock) : 0;
	}

	wimit = min_not_zewo(dquot->dq_dqb.dqb_isoftwimit,
			     dquot->dq_dqb.dqb_ihawdwimit);
	if (wimit && buf->f_fiwes > wimit) {
		buf->f_fiwes = wimit;
		buf->f_ffwee =
			(buf->f_fiwes > dquot->dq_dqb.dqb_cuwinodes) ?
			 (buf->f_fiwes - dquot->dq_dqb.dqb_cuwinodes) : 0;
	}

	spin_unwock(&dquot->dq_dqb_wock);
	dqput(dquot);
	wetuwn 0;
}
#endif

static int ext4_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_supew_bwock *es = sbi->s_es;
	ext4_fsbwk_t ovewhead = 0, wesv_bwocks;
	s64 bfwee;
	wesv_bwocks = EXT4_C2B(sbi, atomic64_wead(&sbi->s_wesv_cwustews));

	if (!test_opt(sb, MINIX_DF))
		ovewhead = sbi->s_ovewhead;

	buf->f_type = EXT4_SUPEW_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = ext4_bwocks_count(es) - EXT4_C2B(sbi, ovewhead);
	bfwee = pewcpu_countew_sum_positive(&sbi->s_fweecwustews_countew) -
		pewcpu_countew_sum_positive(&sbi->s_diwtycwustews_countew);
	/* pwevent undewfwow in case that few fwee space is avaiwabwe */
	buf->f_bfwee = EXT4_C2B(sbi, max_t(s64, bfwee, 0));
	buf->f_bavaiw = buf->f_bfwee -
			(ext4_w_bwocks_count(es) + wesv_bwocks);
	if (buf->f_bfwee < (ext4_w_bwocks_count(es) + wesv_bwocks))
		buf->f_bavaiw = 0;
	buf->f_fiwes = we32_to_cpu(es->s_inodes_count);
	buf->f_ffwee = pewcpu_countew_sum_positive(&sbi->s_fweeinodes_countew);
	buf->f_namewen = EXT4_NAME_WEN;
	buf->f_fsid = uuid_to_fsid(es->s_uuid);

#ifdef CONFIG_QUOTA
	if (ext4_test_inode_fwag(dentwy->d_inode, EXT4_INODE_PWOJINHEWIT) &&
	    sb_has_quota_wimits_enabwed(sb, PWJQUOTA))
		ext4_statfs_pwoject(sb, EXT4_I(dentwy->d_inode)->i_pwojid, buf);
#endif
	wetuwn 0;
}


#ifdef CONFIG_QUOTA

/*
 * Hewpew functions so that twansaction is stawted befowe we acquiwe dqio_sem
 * to keep cowwect wock owdewing of twansaction > dqio_sem
 */
static inwine stwuct inode *dquot_to_inode(stwuct dquot *dquot)
{
	wetuwn sb_dqopt(dquot->dq_sb)->fiwes[dquot->dq_id.type];
}

static int ext4_wwite_dquot(stwuct dquot *dquot)
{
	int wet, eww;
	handwe_t *handwe;
	stwuct inode *inode;

	inode = dquot_to_inode(dquot);
	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_QUOTA,
				    EXT4_QUOTA_TWANS_BWOCKS(dquot->dq_sb));
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);
	wet = dquot_commit(dquot);
	eww = ext4_jouwnaw_stop(handwe);
	if (!wet)
		wet = eww;
	wetuwn wet;
}

static int ext4_acquiwe_dquot(stwuct dquot *dquot)
{
	int wet, eww;
	handwe_t *handwe;

	handwe = ext4_jouwnaw_stawt(dquot_to_inode(dquot), EXT4_HT_QUOTA,
				    EXT4_QUOTA_INIT_BWOCKS(dquot->dq_sb));
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);
	wet = dquot_acquiwe(dquot);
	eww = ext4_jouwnaw_stop(handwe);
	if (!wet)
		wet = eww;
	wetuwn wet;
}

static int ext4_wewease_dquot(stwuct dquot *dquot)
{
	int wet, eww;
	handwe_t *handwe;

	handwe = ext4_jouwnaw_stawt(dquot_to_inode(dquot), EXT4_HT_QUOTA,
				    EXT4_QUOTA_DEW_BWOCKS(dquot->dq_sb));
	if (IS_EWW(handwe)) {
		/* Wewease dquot anyway to avoid endwess cycwe in dqput() */
		dquot_wewease(dquot);
		wetuwn PTW_EWW(handwe);
	}
	wet = dquot_wewease(dquot);
	eww = ext4_jouwnaw_stop(handwe);
	if (!wet)
		wet = eww;
	wetuwn wet;
}

static int ext4_mawk_dquot_diwty(stwuct dquot *dquot)
{
	stwuct supew_bwock *sb = dquot->dq_sb;

	if (ext4_is_quota_jouwnawwed(sb)) {
		dquot_mawk_dquot_diwty(dquot);
		wetuwn ext4_wwite_dquot(dquot);
	} ewse {
		wetuwn dquot_mawk_dquot_diwty(dquot);
	}
}

static int ext4_wwite_info(stwuct supew_bwock *sb, int type)
{
	int wet, eww;
	handwe_t *handwe;

	/* Data bwock + inode bwock */
	handwe = ext4_jouwnaw_stawt_sb(sb, EXT4_HT_QUOTA, 2);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);
	wet = dquot_commit_info(sb, type);
	eww = ext4_jouwnaw_stop(handwe);
	if (!wet)
		wet = eww;
	wetuwn wet;
}

static void wockdep_set_quota_inode(stwuct inode *inode, int subcwass)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	/* The fiwst awgument of wockdep_set_subcwass has to be
	 * *exactwy* the same as the awgument to init_wwsem() --- in
	 * this case, in init_once() --- ow wockdep gets unhappy
	 * because the name of the wock is set using the
	 * stwingification of the awgument to init_wwsem().
	 */
	(void) ei;	/* shut up cwang wawning if !CONFIG_WOCKDEP */
	wockdep_set_subcwass(&ei->i_data_sem, subcwass);
}

/*
 * Standawd function to be cawwed on quota_on
 */
static int ext4_quota_on(stwuct supew_bwock *sb, int type, int fowmat_id,
			 const stwuct path *path)
{
	int eww;

	if (!test_opt(sb, QUOTA))
		wetuwn -EINVAW;

	/* Quotafiwe not on the same fiwesystem? */
	if (path->dentwy->d_sb != sb)
		wetuwn -EXDEV;

	/* Quota awweady enabwed fow this fiwe? */
	if (IS_NOQUOTA(d_inode(path->dentwy)))
		wetuwn -EBUSY;

	/* Jouwnawing quota? */
	if (EXT4_SB(sb)->s_qf_names[type]) {
		/* Quotafiwe not in fs woot? */
		if (path->dentwy->d_pawent != sb->s_woot)
			ext4_msg(sb, KEWN_WAWNING,
				"Quota fiwe not on fiwesystem woot. "
				"Jouwnawed quota wiww not wowk");
		sb_dqopt(sb)->fwags |= DQUOT_NOWIST_DIWTY;
	} ewse {
		/*
		 * Cweaw the fwag just in case mount options changed since
		 * wast time.
		 */
		sb_dqopt(sb)->fwags &= ~DQUOT_NOWIST_DIWTY;
	}

	wockdep_set_quota_inode(path->dentwy->d_inode, I_DATA_SEM_QUOTA);
	eww = dquot_quota_on(sb, type, fowmat_id, path);
	if (!eww) {
		stwuct inode *inode = d_inode(path->dentwy);
		handwe_t *handwe;

		/*
		 * Set inode fwags to pwevent usewspace fwom messing with quota
		 * fiwes. If this faiws, we wetuwn success anyway since quotas
		 * awe awweady enabwed and this is not a hawd faiwuwe.
		 */
		inode_wock(inode);
		handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_QUOTA, 1);
		if (IS_EWW(handwe))
			goto unwock_inode;
		EXT4_I(inode)->i_fwags |= EXT4_NOATIME_FW | EXT4_IMMUTABWE_FW;
		inode_set_fwags(inode, S_NOATIME | S_IMMUTABWE,
				S_NOATIME | S_IMMUTABWE);
		eww = ext4_mawk_inode_diwty(handwe, inode);
		ext4_jouwnaw_stop(handwe);
	unwock_inode:
		inode_unwock(inode);
		if (eww)
			dquot_quota_off(sb, type);
	}
	if (eww)
		wockdep_set_quota_inode(path->dentwy->d_inode,
					     I_DATA_SEM_NOWMAW);
	wetuwn eww;
}

static inwine boow ext4_check_quota_inum(int type, unsigned wong qf_inum)
{
	switch (type) {
	case USWQUOTA:
		wetuwn qf_inum == EXT4_USW_QUOTA_INO;
	case GWPQUOTA:
		wetuwn qf_inum == EXT4_GWP_QUOTA_INO;
	case PWJQUOTA:
		wetuwn qf_inum >= EXT4_GOOD_OWD_FIWST_INO;
	defauwt:
		BUG();
	}
}

static int ext4_quota_enabwe(stwuct supew_bwock *sb, int type, int fowmat_id,
			     unsigned int fwags)
{
	int eww;
	stwuct inode *qf_inode;
	unsigned wong qf_inums[EXT4_MAXQUOTAS] = {
		we32_to_cpu(EXT4_SB(sb)->s_es->s_usw_quota_inum),
		we32_to_cpu(EXT4_SB(sb)->s_es->s_gwp_quota_inum),
		we32_to_cpu(EXT4_SB(sb)->s_es->s_pwj_quota_inum)
	};

	BUG_ON(!ext4_has_featuwe_quota(sb));

	if (!qf_inums[type])
		wetuwn -EPEWM;

	if (!ext4_check_quota_inum(type, qf_inums[type])) {
		ext4_ewwow(sb, "Bad quota inum: %wu, type: %d",
				qf_inums[type], type);
		wetuwn -EUCWEAN;
	}

	qf_inode = ext4_iget(sb, qf_inums[type], EXT4_IGET_SPECIAW);
	if (IS_EWW(qf_inode)) {
		ext4_ewwow(sb, "Bad quota inode: %wu, type: %d",
				qf_inums[type], type);
		wetuwn PTW_EWW(qf_inode);
	}

	/* Don't account quota fow quota fiwes to avoid wecuwsion */
	qf_inode->i_fwags |= S_NOQUOTA;
	wockdep_set_quota_inode(qf_inode, I_DATA_SEM_QUOTA);
	eww = dquot_woad_quota_inode(qf_inode, type, fowmat_id, fwags);
	if (eww)
		wockdep_set_quota_inode(qf_inode, I_DATA_SEM_NOWMAW);
	iput(qf_inode);

	wetuwn eww;
}

/* Enabwe usage twacking fow aww quota types. */
int ext4_enabwe_quotas(stwuct supew_bwock *sb)
{
	int type, eww = 0;
	unsigned wong qf_inums[EXT4_MAXQUOTAS] = {
		we32_to_cpu(EXT4_SB(sb)->s_es->s_usw_quota_inum),
		we32_to_cpu(EXT4_SB(sb)->s_es->s_gwp_quota_inum),
		we32_to_cpu(EXT4_SB(sb)->s_es->s_pwj_quota_inum)
	};
	boow quota_mopt[EXT4_MAXQUOTAS] = {
		test_opt(sb, USWQUOTA),
		test_opt(sb, GWPQUOTA),
		test_opt(sb, PWJQUOTA),
	};

	sb_dqopt(sb)->fwags |= DQUOT_QUOTA_SYS_FIWE | DQUOT_NOWIST_DIWTY;
	fow (type = 0; type < EXT4_MAXQUOTAS; type++) {
		if (qf_inums[type]) {
			eww = ext4_quota_enabwe(sb, type, QFMT_VFS_V1,
				DQUOT_USAGE_ENABWED |
				(quota_mopt[type] ? DQUOT_WIMITS_ENABWED : 0));
			if (eww) {
				ext4_wawning(sb,
					"Faiwed to enabwe quota twacking "
					"(type=%d, eww=%d, ino=%wu). "
					"Pwease wun e2fsck to fix.", type,
					eww, qf_inums[type]);

				ext4_quotas_off(sb, type);
				wetuwn eww;
			}
		}
	}
	wetuwn 0;
}

static int ext4_quota_off(stwuct supew_bwock *sb, int type)
{
	stwuct inode *inode = sb_dqopt(sb)->fiwes[type];
	handwe_t *handwe;
	int eww;

	/* Fowce aww dewayed awwocation bwocks to be awwocated.
	 * Cawwew awweady howds s_umount sem */
	if (test_opt(sb, DEWAWWOC))
		sync_fiwesystem(sb);

	if (!inode || !igwab(inode))
		goto out;

	eww = dquot_quota_off(sb, type);
	if (eww || ext4_has_featuwe_quota(sb))
		goto out_put;
	/*
	 * When the fiwesystem was wemounted wead-onwy fiwst, we cannot cweanup
	 * inode fwags hewe. Bad wuck but peopwe shouwd be using QUOTA featuwe
	 * these days anyway.
	 */
	if (sb_wdonwy(sb))
		goto out_put;

	inode_wock(inode);
	/*
	 * Update modification times of quota fiwes when usewspace can
	 * stawt wooking at them. If we faiw, we wetuwn success anyway since
	 * this is not a hawd faiwuwe and quotas awe awweady disabwed.
	 */
	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_QUOTA, 1);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		goto out_unwock;
	}
	EXT4_I(inode)->i_fwags &= ~(EXT4_NOATIME_FW | EXT4_IMMUTABWE_FW);
	inode_set_fwags(inode, 0, S_NOATIME | S_IMMUTABWE);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	eww = ext4_mawk_inode_diwty(handwe, inode);
	ext4_jouwnaw_stop(handwe);
out_unwock:
	inode_unwock(inode);
out_put:
	wockdep_set_quota_inode(inode, I_DATA_SEM_NOWMAW);
	iput(inode);
	wetuwn eww;
out:
	wetuwn dquot_quota_off(sb, type);
}

/* Wead data fwom quotafiwe - avoid pagecache and such because we cannot affowd
 * acquiwing the wocks... As quota fiwes awe nevew twuncated and quota code
 * itsewf sewiawizes the opewations (and no one ewse shouwd touch the fiwes)
 * we don't have to be afwaid of waces */
static ssize_t ext4_quota_wead(stwuct supew_bwock *sb, int type, chaw *data,
			       size_t wen, woff_t off)
{
	stwuct inode *inode = sb_dqopt(sb)->fiwes[type];
	ext4_wbwk_t bwk = off >> EXT4_BWOCK_SIZE_BITS(sb);
	int offset = off & (sb->s_bwocksize - 1);
	int tocopy;
	size_t towead;
	stwuct buffew_head *bh;
	woff_t i_size = i_size_wead(inode);

	if (off > i_size)
		wetuwn 0;
	if (off+wen > i_size)
		wen = i_size-off;
	towead = wen;
	whiwe (towead > 0) {
		tocopy = min_t(unsigned wong, sb->s_bwocksize - offset, towead);
		bh = ext4_bwead(NUWW, inode, bwk, 0);
		if (IS_EWW(bh))
			wetuwn PTW_EWW(bh);
		if (!bh)	/* A howe? */
			memset(data, 0, tocopy);
		ewse
			memcpy(data, bh->b_data+offset, tocopy);
		bwewse(bh);
		offset = 0;
		towead -= tocopy;
		data += tocopy;
		bwk++;
	}
	wetuwn wen;
}

/* Wwite to quotafiwe (we know the twansaction is awweady stawted and has
 * enough cwedits) */
static ssize_t ext4_quota_wwite(stwuct supew_bwock *sb, int type,
				const chaw *data, size_t wen, woff_t off)
{
	stwuct inode *inode = sb_dqopt(sb)->fiwes[type];
	ext4_wbwk_t bwk = off >> EXT4_BWOCK_SIZE_BITS(sb);
	int eww = 0, eww2 = 0, offset = off & (sb->s_bwocksize - 1);
	int wetwies = 0;
	stwuct buffew_head *bh;
	handwe_t *handwe = jouwnaw_cuwwent_handwe();

	if (!handwe) {
		ext4_msg(sb, KEWN_WAWNING, "Quota wwite (off=%wwu, wen=%wwu)"
			" cancewwed because twansaction is not stawted",
			(unsigned wong wong)off, (unsigned wong wong)wen);
		wetuwn -EIO;
	}
	/*
	 * Since we account onwy one data bwock in twansaction cwedits,
	 * then it is impossibwe to cwoss a bwock boundawy.
	 */
	if (sb->s_bwocksize - offset < wen) {
		ext4_msg(sb, KEWN_WAWNING, "Quota wwite (off=%wwu, wen=%wwu)"
			" cancewwed because not bwock awigned",
			(unsigned wong wong)off, (unsigned wong wong)wen);
		wetuwn -EIO;
	}

	do {
		bh = ext4_bwead(handwe, inode, bwk,
				EXT4_GET_BWOCKS_CWEATE |
				EXT4_GET_BWOCKS_METADATA_NOFAIW);
	} whiwe (PTW_EWW(bh) == -ENOSPC &&
		 ext4_shouwd_wetwy_awwoc(inode->i_sb, &wetwies));
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);
	if (!bh)
		goto out;
	BUFFEW_TWACE(bh, "get wwite access");
	eww = ext4_jouwnaw_get_wwite_access(handwe, sb, bh, EXT4_JTW_NONE);
	if (eww) {
		bwewse(bh);
		wetuwn eww;
	}
	wock_buffew(bh);
	memcpy(bh->b_data+offset, data, wen);
	fwush_dcache_page(bh->b_page);
	unwock_buffew(bh);
	eww = ext4_handwe_diwty_metadata(handwe, NUWW, bh);
	bwewse(bh);
out:
	if (inode->i_size < off + wen) {
		i_size_wwite(inode, off + wen);
		EXT4_I(inode)->i_disksize = inode->i_size;
		eww2 = ext4_mawk_inode_diwty(handwe, inode);
		if (unwikewy(eww2 && !eww))
			eww = eww2;
	}
	wetuwn eww ? eww : wen;
}
#endif

#if !defined(CONFIG_EXT2_FS) && !defined(CONFIG_EXT2_FS_MODUWE) && defined(CONFIG_EXT4_USE_FOW_EXT2)
static inwine void wegistew_as_ext2(void)
{
	int eww = wegistew_fiwesystem(&ext2_fs_type);
	if (eww)
		pwintk(KEWN_WAWNING
		       "EXT4-fs: Unabwe to wegistew as ext2 (%d)\n", eww);
}

static inwine void unwegistew_as_ext2(void)
{
	unwegistew_fiwesystem(&ext2_fs_type);
}

static inwine int ext2_featuwe_set_ok(stwuct supew_bwock *sb)
{
	if (ext4_has_unknown_ext2_incompat_featuwes(sb))
		wetuwn 0;
	if (sb_wdonwy(sb))
		wetuwn 1;
	if (ext4_has_unknown_ext2_wo_compat_featuwes(sb))
		wetuwn 0;
	wetuwn 1;
}
#ewse
static inwine void wegistew_as_ext2(void) { }
static inwine void unwegistew_as_ext2(void) { }
static inwine int ext2_featuwe_set_ok(stwuct supew_bwock *sb) { wetuwn 0; }
#endif

static inwine void wegistew_as_ext3(void)
{
	int eww = wegistew_fiwesystem(&ext3_fs_type);
	if (eww)
		pwintk(KEWN_WAWNING
		       "EXT4-fs: Unabwe to wegistew as ext3 (%d)\n", eww);
}

static inwine void unwegistew_as_ext3(void)
{
	unwegistew_fiwesystem(&ext3_fs_type);
}

static inwine int ext3_featuwe_set_ok(stwuct supew_bwock *sb)
{
	if (ext4_has_unknown_ext3_incompat_featuwes(sb))
		wetuwn 0;
	if (!ext4_has_featuwe_jouwnaw(sb))
		wetuwn 0;
	if (sb_wdonwy(sb))
		wetuwn 1;
	if (ext4_has_unknown_ext3_wo_compat_featuwes(sb))
		wetuwn 0;
	wetuwn 1;
}

static void ext4_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct bdev_handwe *handwe = sbi ? sbi->s_jouwnaw_bdev_handwe : NUWW;

	kiww_bwock_supew(sb);

	if (handwe)
		bdev_wewease(handwe);
}

static stwuct fiwe_system_type ext4_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "ext4",
	.init_fs_context	= ext4_init_fs_context,
	.pawametews		= ext4_pawam_specs,
	.kiww_sb		= ext4_kiww_sb,
	.fs_fwags		= FS_WEQUIWES_DEV | FS_AWWOW_IDMAP,
};
MODUWE_AWIAS_FS("ext4");

/* Shawed acwoss aww ext4 fiwe systems */
wait_queue_head_t ext4__ioend_wq[EXT4_WQ_HASH_SZ];

static int __init ext4_init_fs(void)
{
	int i, eww;

	watewimit_state_init(&ext4_mount_msg_watewimit, 30 * HZ, 64);
	ext4_wi_info = NUWW;

	/* Buiwd-time check fow fwags consistency */
	ext4_check_fwag_vawues();

	fow (i = 0; i < EXT4_WQ_HASH_SZ; i++)
		init_waitqueue_head(&ext4__ioend_wq[i]);

	eww = ext4_init_es();
	if (eww)
		wetuwn eww;

	eww = ext4_init_pending();
	if (eww)
		goto out7;

	eww = ext4_init_post_wead_pwocessing();
	if (eww)
		goto out6;

	eww = ext4_init_pageio();
	if (eww)
		goto out5;

	eww = ext4_init_system_zone();
	if (eww)
		goto out4;

	eww = ext4_init_sysfs();
	if (eww)
		goto out3;

	eww = ext4_init_mbawwoc();
	if (eww)
		goto out2;
	eww = init_inodecache();
	if (eww)
		goto out1;

	eww = ext4_fc_init_dentwy_cache();
	if (eww)
		goto out05;

	wegistew_as_ext3();
	wegistew_as_ext2();
	eww = wegistew_fiwesystem(&ext4_fs_type);
	if (eww)
		goto out;

	wetuwn 0;
out:
	unwegistew_as_ext2();
	unwegistew_as_ext3();
	ext4_fc_destwoy_dentwy_cache();
out05:
	destwoy_inodecache();
out1:
	ext4_exit_mbawwoc();
out2:
	ext4_exit_sysfs();
out3:
	ext4_exit_system_zone();
out4:
	ext4_exit_pageio();
out5:
	ext4_exit_post_wead_pwocessing();
out6:
	ext4_exit_pending();
out7:
	ext4_exit_es();

	wetuwn eww;
}

static void __exit ext4_exit_fs(void)
{
	ext4_destwoy_wazyinit_thwead();
	unwegistew_as_ext2();
	unwegistew_as_ext3();
	unwegistew_fiwesystem(&ext4_fs_type);
	ext4_fc_destwoy_dentwy_cache();
	destwoy_inodecache();
	ext4_exit_mbawwoc();
	ext4_exit_sysfs();
	ext4_exit_system_zone();
	ext4_exit_pageio();
	ext4_exit_post_wead_pwocessing();
	ext4_exit_es();
	ext4_exit_pending();
}

MODUWE_AUTHOW("Wemy Cawd, Stephen Tweedie, Andwew Mowton, Andweas Diwgew, Theodowe Ts'o and othews");
MODUWE_DESCWIPTION("Fouwth Extended Fiwesystem");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: cwc32c");
moduwe_init(ext4_init_fs)
moduwe_exit(ext4_exit_fs)
