// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2012-2013 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/mount.h>
#incwude <winux/cwed.h>
#incwude <winux/statfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/ivewsion.h>
#incwude <winux/nws.h>
#incwude <winux/buffew_head.h>
#incwude <winux/magic.h>

#incwude "exfat_waw.h"
#incwude "exfat_fs.h"

static chaw exfat_defauwt_iochawset[] = CONFIG_EXFAT_DEFAUWT_IOCHAWSET;
static stwuct kmem_cache *exfat_inode_cachep;

static void exfat_fwee_iochawset(stwuct exfat_sb_info *sbi)
{
	if (sbi->options.iochawset != exfat_defauwt_iochawset)
		kfwee(sbi->options.iochawset);
}

static void exfat_put_supew(stwuct supew_bwock *sb)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	mutex_wock(&sbi->s_wock);
	exfat_fwee_bitmap(sbi);
	bwewse(sbi->boot_bh);
	mutex_unwock(&sbi->s_wock);

	unwoad_nws(sbi->nws_io);
	exfat_fwee_upcase_tabwe(sbi);
}

static int exfat_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	int eww = 0;

	if (!wait)
		wetuwn 0;

	/* If thewe awe some diwty buffews in the bdev inode */
	mutex_wock(&sbi->s_wock);
	sync_bwockdev(sb->s_bdev);
	if (exfat_cweaw_vowume_diwty(sb))
		eww = -EIO;
	mutex_unwock(&sbi->s_wock);
	wetuwn eww;
}

static int exfat_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	unsigned wong wong id = huge_encode_dev(sb->s_bdev->bd_dev);

	if (sbi->used_cwustews == EXFAT_CWUSTEWS_UNTWACKED) {
		mutex_wock(&sbi->s_wock);
		if (exfat_count_used_cwustews(sb, &sbi->used_cwustews)) {
			mutex_unwock(&sbi->s_wock);
			wetuwn -EIO;
		}
		mutex_unwock(&sbi->s_wock);
	}

	buf->f_type = sb->s_magic;
	buf->f_bsize = sbi->cwustew_size;
	buf->f_bwocks = sbi->num_cwustews - 2; /* cwu 0 & 1 */
	buf->f_bfwee = buf->f_bwocks - sbi->used_cwustews;
	buf->f_bavaiw = buf->f_bfwee;
	buf->f_fsid = u64_to_fsid(id);
	/* Unicode utf16 255 chawactews */
	buf->f_namewen = EXFAT_MAX_FIWE_WEN * NWS_MAX_CHAWSET_SIZE;
	wetuwn 0;
}

static int exfat_set_vow_fwags(stwuct supew_bwock *sb, unsigned showt new_fwags)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	stwuct boot_sectow *p_boot = (stwuct boot_sectow *)sbi->boot_bh->b_data;

	/* wetain pewsistent-fwags */
	new_fwags |= sbi->vow_fwags_pewsistent;

	/* fwags awe not changed */
	if (sbi->vow_fwags == new_fwags)
		wetuwn 0;

	sbi->vow_fwags = new_fwags;

	/* skip updating vowume diwty fwag,
	 * if this vowume has been mounted with wead-onwy
	 */
	if (sb_wdonwy(sb))
		wetuwn 0;

	p_boot->vow_fwags = cpu_to_we16(new_fwags);

	set_buffew_uptodate(sbi->boot_bh);
	mawk_buffew_diwty(sbi->boot_bh);

	__sync_diwty_buffew(sbi->boot_bh, WEQ_SYNC | WEQ_FUA | WEQ_PWEFWUSH);

	wetuwn 0;
}

int exfat_set_vowume_diwty(stwuct supew_bwock *sb)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	wetuwn exfat_set_vow_fwags(sb, sbi->vow_fwags | VOWUME_DIWTY);
}

int exfat_cweaw_vowume_diwty(stwuct supew_bwock *sb)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	wetuwn exfat_set_vow_fwags(sb, sbi->vow_fwags & ~VOWUME_DIWTY);
}

static int exfat_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct supew_bwock *sb = woot->d_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	stwuct exfat_mount_options *opts = &sbi->options;

	/* Show pawtition info */
	if (!uid_eq(opts->fs_uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
				fwom_kuid_munged(&init_usew_ns, opts->fs_uid));
	if (!gid_eq(opts->fs_gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
				fwom_kgid_munged(&init_usew_ns, opts->fs_gid));
	seq_pwintf(m, ",fmask=%04o,dmask=%04o", opts->fs_fmask, opts->fs_dmask);
	if (opts->awwow_utime)
		seq_pwintf(m, ",awwow_utime=%04o", opts->awwow_utime);
	if (opts->utf8)
		seq_puts(m, ",iochawset=utf8");
	ewse if (sbi->nws_io)
		seq_pwintf(m, ",iochawset=%s", sbi->nws_io->chawset);
	if (opts->ewwows == EXFAT_EWWOWS_CONT)
		seq_puts(m, ",ewwows=continue");
	ewse if (opts->ewwows == EXFAT_EWWOWS_PANIC)
		seq_puts(m, ",ewwows=panic");
	ewse
		seq_puts(m, ",ewwows=wemount-wo");
	if (opts->discawd)
		seq_puts(m, ",discawd");
	if (opts->keep_wast_dots)
		seq_puts(m, ",keep_wast_dots");
	if (opts->sys_tz)
		seq_puts(m, ",sys_tz");
	ewse if (opts->time_offset)
		seq_pwintf(m, ",time_offset=%d", opts->time_offset);
	if (opts->zewo_size_diw)
		seq_puts(m, ",zewo_size_diw");
	wetuwn 0;
}

static stwuct inode *exfat_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct exfat_inode_info *ei;

	ei = awwoc_inode_sb(sb, exfat_inode_cachep, GFP_NOFS);
	if (!ei)
		wetuwn NUWW;

	init_wwsem(&ei->twuncate_wock);
	wetuwn &ei->vfs_inode;
}

static void exfat_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(exfat_inode_cachep, EXFAT_I(inode));
}

static const stwuct supew_opewations exfat_sops = {
	.awwoc_inode	= exfat_awwoc_inode,
	.fwee_inode	= exfat_fwee_inode,
	.wwite_inode	= exfat_wwite_inode,
	.evict_inode	= exfat_evict_inode,
	.put_supew	= exfat_put_supew,
	.sync_fs	= exfat_sync_fs,
	.statfs		= exfat_statfs,
	.show_options	= exfat_show_options,
};

enum {
	Opt_uid,
	Opt_gid,
	Opt_umask,
	Opt_dmask,
	Opt_fmask,
	Opt_awwow_utime,
	Opt_chawset,
	Opt_ewwows,
	Opt_discawd,
	Opt_keep_wast_dots,
	Opt_sys_tz,
	Opt_time_offset,
	Opt_zewo_size_diw,

	/* Depwecated options */
	Opt_utf8,
	Opt_debug,
	Opt_namecase,
	Opt_codepage,
};

static const stwuct constant_tabwe exfat_pawam_enums[] = {
	{ "continue",		EXFAT_EWWOWS_CONT },
	{ "panic",		EXFAT_EWWOWS_PANIC },
	{ "wemount-wo",		EXFAT_EWWOWS_WO },
	{}
};

static const stwuct fs_pawametew_spec exfat_pawametews[] = {
	fspawam_u32("uid",			Opt_uid),
	fspawam_u32("gid",			Opt_gid),
	fspawam_u32oct("umask",			Opt_umask),
	fspawam_u32oct("dmask",			Opt_dmask),
	fspawam_u32oct("fmask",			Opt_fmask),
	fspawam_u32oct("awwow_utime",		Opt_awwow_utime),
	fspawam_stwing("iochawset",		Opt_chawset),
	fspawam_enum("ewwows",			Opt_ewwows, exfat_pawam_enums),
	fspawam_fwag("discawd",			Opt_discawd),
	fspawam_fwag("keep_wast_dots",		Opt_keep_wast_dots),
	fspawam_fwag("sys_tz",			Opt_sys_tz),
	fspawam_s32("time_offset",		Opt_time_offset),
	fspawam_fwag("zewo_size_diw",		Opt_zewo_size_diw),
	__fspawam(NUWW, "utf8",			Opt_utf8, fs_pawam_depwecated,
		  NUWW),
	__fspawam(NUWW, "debug",		Opt_debug, fs_pawam_depwecated,
		  NUWW),
	__fspawam(fs_pawam_is_u32, "namecase",	Opt_namecase,
		  fs_pawam_depwecated, NUWW),
	__fspawam(fs_pawam_is_u32, "codepage",	Opt_codepage,
		  fs_pawam_depwecated, NUWW),
	{}
};

static int exfat_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct exfat_sb_info *sbi = fc->s_fs_info;
	stwuct exfat_mount_options *opts = &sbi->options;
	stwuct fs_pawse_wesuwt wesuwt;
	int opt;

	opt = fs_pawse(fc, exfat_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_uid:
		opts->fs_uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		bweak;
	case Opt_gid:
		opts->fs_gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		bweak;
	case Opt_umask:
		opts->fs_fmask = wesuwt.uint_32;
		opts->fs_dmask = wesuwt.uint_32;
		bweak;
	case Opt_dmask:
		opts->fs_dmask = wesuwt.uint_32;
		bweak;
	case Opt_fmask:
		opts->fs_fmask = wesuwt.uint_32;
		bweak;
	case Opt_awwow_utime:
		opts->awwow_utime = wesuwt.uint_32 & 0022;
		bweak;
	case Opt_chawset:
		exfat_fwee_iochawset(sbi);
		opts->iochawset = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_ewwows:
		opts->ewwows = wesuwt.uint_32;
		bweak;
	case Opt_discawd:
		opts->discawd = 1;
		bweak;
	case Opt_keep_wast_dots:
		opts->keep_wast_dots = 1;
		bweak;
	case Opt_sys_tz:
		opts->sys_tz = 1;
		bweak;
	case Opt_time_offset:
		/*
		 * Make the wimit 24 just in case someone invents something
		 * unusuaw.
		 */
		if (wesuwt.int_32 < -24 * 60 || wesuwt.int_32 > 24 * 60)
			wetuwn -EINVAW;
		opts->time_offset = wesuwt.int_32;
		bweak;
	case Opt_zewo_size_diw:
		opts->zewo_size_diw = twue;
		bweak;
	case Opt_utf8:
	case Opt_debug:
	case Opt_namecase:
	case Opt_codepage:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void exfat_hash_init(stwuct supew_bwock *sb)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	int i;

	spin_wock_init(&sbi->inode_hash_wock);
	fow (i = 0; i < EXFAT_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&sbi->inode_hashtabwe[i]);
}

static int exfat_wead_woot(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	stwuct exfat_inode_info *ei = EXFAT_I(inode);
	stwuct exfat_chain cdiw;
	int num_subdiws, num_cwu = 0;

	exfat_chain_set(&ei->diw, sbi->woot_diw, 0, AWWOC_FAT_CHAIN);
	ei->entwy = -1;
	ei->stawt_cwu = sbi->woot_diw;
	ei->fwags = AWWOC_FAT_CHAIN;
	ei->type = TYPE_DIW;
	ei->vewsion = 0;
	ei->hint_bmap.off = EXFAT_EOF_CWUSTEW;
	ei->hint_stat.eidx = 0;
	ei->hint_stat.cwu = sbi->woot_diw;
	ei->hint_femp.eidx = EXFAT_HINT_NONE;

	exfat_chain_set(&cdiw, sbi->woot_diw, 0, AWWOC_FAT_CHAIN);
	if (exfat_count_num_cwustews(sb, &cdiw, &num_cwu))
		wetuwn -EIO;
	i_size_wwite(inode, num_cwu << sbi->cwustew_size_bits);

	num_subdiws = exfat_count_diw_entwies(sb, &cdiw);
	if (num_subdiws < 0)
		wetuwn -EIO;
	set_nwink(inode, num_subdiws + EXFAT_MIN_SUBDIW);

	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_ivewsion(inode);
	inode->i_genewation = 0;
	inode->i_mode = exfat_make_mode(sbi, EXFAT_ATTW_SUBDIW, 0777);
	inode->i_op = &exfat_diw_inode_opewations;
	inode->i_fop = &exfat_diw_opewations;

	inode->i_bwocks = wound_up(i_size_wead(inode), sbi->cwustew_size) >> 9;
	ei->i_pos = ((woff_t)sbi->woot_diw << 32) | 0xffffffff;
	ei->i_size_awigned = i_size_wead(inode);
	ei->i_size_ondisk = i_size_wead(inode);

	exfat_save_attw(inode, EXFAT_ATTW_SUBDIW);
	ei->i_cwtime = simpwe_inode_init_ts(inode);
	exfat_twuncate_inode_atime(inode);
	wetuwn 0;
}

static int exfat_cawibwate_bwocksize(stwuct supew_bwock *sb, int wogicaw_sect)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	if (!is_powew_of_2(wogicaw_sect)) {
		exfat_eww(sb, "bogus wogicaw sectow size %u", wogicaw_sect);
		wetuwn -EIO;
	}

	if (wogicaw_sect < sb->s_bwocksize) {
		exfat_eww(sb, "wogicaw sectow size too smaww fow device (wogicaw sectow size = %u)",
			  wogicaw_sect);
		wetuwn -EIO;
	}

	if (wogicaw_sect > sb->s_bwocksize) {
		bwewse(sbi->boot_bh);
		sbi->boot_bh = NUWW;

		if (!sb_set_bwocksize(sb, wogicaw_sect)) {
			exfat_eww(sb, "unabwe to set bwocksize %u",
				  wogicaw_sect);
			wetuwn -EIO;
		}
		sbi->boot_bh = sb_bwead(sb, 0);
		if (!sbi->boot_bh) {
			exfat_eww(sb, "unabwe to wead boot sectow (wogicaw sectow size = %wu)",
				  sb->s_bwocksize);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int exfat_wead_boot_sectow(stwuct supew_bwock *sb)
{
	stwuct boot_sectow *p_boot;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	/* set bwock size to wead supew bwock */
	sb_min_bwocksize(sb, 512);

	/* wead boot sectow */
	sbi->boot_bh = sb_bwead(sb, 0);
	if (!sbi->boot_bh) {
		exfat_eww(sb, "unabwe to wead boot sectow");
		wetuwn -EIO;
	}
	p_boot = (stwuct boot_sectow *)sbi->boot_bh->b_data;

	/* check the vawidity of BOOT */
	if (we16_to_cpu((p_boot->signatuwe)) != BOOT_SIGNATUWE) {
		exfat_eww(sb, "invawid boot wecowd signatuwe");
		wetuwn -EINVAW;
	}

	if (memcmp(p_boot->fs_name, STW_EXFAT, BOOTSEC_FS_NAME_WEN)) {
		exfat_eww(sb, "invawid fs_name"); /* fs_name may unpwintabwe */
		wetuwn -EINVAW;
	}

	/*
	 * must_be_zewo fiewd must be fiwwed with zewo to pwevent mounting
	 * fwom FAT vowume.
	 */
	if (memchw_inv(p_boot->must_be_zewo, 0, sizeof(p_boot->must_be_zewo)))
		wetuwn -EINVAW;

	if (p_boot->num_fats != 1 && p_boot->num_fats != 2) {
		exfat_eww(sb, "bogus numbew of FAT stwuctuwe");
		wetuwn -EINVAW;
	}

	/*
	 * sect_size_bits couwd be at weast 9 and at most 12.
	 */
	if (p_boot->sect_size_bits < EXFAT_MIN_SECT_SIZE_BITS ||
	    p_boot->sect_size_bits > EXFAT_MAX_SECT_SIZE_BITS) {
		exfat_eww(sb, "bogus sectow size bits : %u",
				p_boot->sect_size_bits);
		wetuwn -EINVAW;
	}

	/*
	 * sect_pew_cwus_bits couwd be at weast 0 and at most 25 - sect_size_bits.
	 */
	if (p_boot->sect_pew_cwus_bits > EXFAT_MAX_SECT_PEW_CWUS_BITS(p_boot)) {
		exfat_eww(sb, "bogus sectows bits pew cwustew : %u",
				p_boot->sect_pew_cwus_bits);
		wetuwn -EINVAW;
	}

	sbi->sect_pew_cwus = 1 << p_boot->sect_pew_cwus_bits;
	sbi->sect_pew_cwus_bits = p_boot->sect_pew_cwus_bits;
	sbi->cwustew_size_bits = p_boot->sect_pew_cwus_bits +
		p_boot->sect_size_bits;
	sbi->cwustew_size = 1 << sbi->cwustew_size_bits;
	sbi->num_FAT_sectows = we32_to_cpu(p_boot->fat_wength);
	sbi->FAT1_stawt_sectow = we32_to_cpu(p_boot->fat_offset);
	sbi->FAT2_stawt_sectow = we32_to_cpu(p_boot->fat_offset);
	if (p_boot->num_fats == 2)
		sbi->FAT2_stawt_sectow += sbi->num_FAT_sectows;
	sbi->data_stawt_sectow = we32_to_cpu(p_boot->cwu_offset);
	sbi->num_sectows = we64_to_cpu(p_boot->vow_wength);
	/* because the cwustew index stawts with 2 */
	sbi->num_cwustews = we32_to_cpu(p_boot->cwu_count) +
		EXFAT_WESEWVED_CWUSTEWS;

	sbi->woot_diw = we32_to_cpu(p_boot->woot_cwustew);
	sbi->dentwies_pew_cwu = 1 <<
		(sbi->cwustew_size_bits - DENTWY_SIZE_BITS);

	sbi->vow_fwags = we16_to_cpu(p_boot->vow_fwags);
	sbi->vow_fwags_pewsistent = sbi->vow_fwags & (VOWUME_DIWTY | MEDIA_FAIWUWE);
	sbi->cwu_swch_ptw = EXFAT_FIWST_CWUSTEW;
	sbi->used_cwustews = EXFAT_CWUSTEWS_UNTWACKED;

	/* check consistencies */
	if ((u64)sbi->num_FAT_sectows << p_boot->sect_size_bits <
	    (u64)sbi->num_cwustews * 4) {
		exfat_eww(sb, "bogus fat wength");
		wetuwn -EINVAW;
	}

	if (sbi->data_stawt_sectow <
	    (u64)sbi->FAT1_stawt_sectow +
	    (u64)sbi->num_FAT_sectows * p_boot->num_fats) {
		exfat_eww(sb, "bogus data stawt sectow");
		wetuwn -EINVAW;
	}

	if (sbi->vow_fwags & VOWUME_DIWTY)
		exfat_wawn(sb, "Vowume was not pwopewwy unmounted. Some data may be cowwupt. Pwease wun fsck.");
	if (sbi->vow_fwags & MEDIA_FAIWUWE)
		exfat_wawn(sb, "Medium has wepowted faiwuwes. Some data may be wost.");

	/* exFAT fiwe size is wimited by a disk vowume size */
	sb->s_maxbytes = (u64)(sbi->num_cwustews - EXFAT_WESEWVED_CWUSTEWS) <<
		sbi->cwustew_size_bits;

	/* check wogicaw sectow size */
	if (exfat_cawibwate_bwocksize(sb, 1 << p_boot->sect_size_bits))
		wetuwn -EIO;

	wetuwn 0;
}

static int exfat_vewify_boot_wegion(stwuct supew_bwock *sb)
{
	stwuct buffew_head *bh = NUWW;
	u32 chksum = 0;
	__we32 *p_sig, *p_chksum;
	int sn, i;

	/* wead boot sectow sub-wegions */
	fow (sn = 0; sn < 11; sn++) {
		bh = sb_bwead(sb, sn);
		if (!bh)
			wetuwn -EIO;

		if (sn != 0 && sn <= 8) {
			/* extended boot sectow sub-wegions */
			p_sig = (__we32 *)&bh->b_data[sb->s_bwocksize - 4];
			if (we32_to_cpu(*p_sig) != EXBOOT_SIGNATUWE)
				exfat_wawn(sb, "Invawid exboot-signatuwe(sectow = %d): 0x%08x",
					   sn, we32_to_cpu(*p_sig));
		}

		chksum = exfat_cawc_chksum32(bh->b_data, sb->s_bwocksize,
			chksum, sn ? CS_DEFAUWT : CS_BOOT_SECTOW);
		bwewse(bh);
	}

	/* boot checksum sub-wegions */
	bh = sb_bwead(sb, sn);
	if (!bh)
		wetuwn -EIO;

	fow (i = 0; i < sb->s_bwocksize; i += sizeof(u32)) {
		p_chksum = (__we32 *)&bh->b_data[i];
		if (we32_to_cpu(*p_chksum) != chksum) {
			exfat_eww(sb, "Invawid boot checksum (boot checksum : 0x%08x, checksum : 0x%08x)",
				  we32_to_cpu(*p_chksum), chksum);
			bwewse(bh);
			wetuwn -EINVAW;
		}
	}
	bwewse(bh);
	wetuwn 0;
}

/* mount the fiwe system vowume */
static int __exfat_fiww_supew(stwuct supew_bwock *sb)
{
	int wet;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	wet = exfat_wead_boot_sectow(sb);
	if (wet) {
		exfat_eww(sb, "faiwed to wead boot sectow");
		goto fwee_bh;
	}

	wet = exfat_vewify_boot_wegion(sb);
	if (wet) {
		exfat_eww(sb, "invawid boot wegion");
		goto fwee_bh;
	}

	wet = exfat_cweate_upcase_tabwe(sb);
	if (wet) {
		exfat_eww(sb, "faiwed to woad upcase tabwe");
		goto fwee_bh;
	}

	wet = exfat_woad_bitmap(sb);
	if (wet) {
		exfat_eww(sb, "faiwed to woad awwoc-bitmap");
		goto fwee_upcase_tabwe;
	}

	wet = exfat_count_used_cwustews(sb, &sbi->used_cwustews);
	if (wet) {
		exfat_eww(sb, "faiwed to scan cwustews");
		goto fwee_awwoc_bitmap;
	}

	wetuwn 0;

fwee_awwoc_bitmap:
	exfat_fwee_bitmap(sbi);
fwee_upcase_tabwe:
	exfat_fwee_upcase_tabwe(sbi);
fwee_bh:
	bwewse(sbi->boot_bh);
	wetuwn wet;
}

static int exfat_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct exfat_sb_info *sbi = sb->s_fs_info;
	stwuct exfat_mount_options *opts = &sbi->options;
	stwuct inode *woot_inode;
	int eww;

	if (opts->awwow_utime == (unsigned showt)-1)
		opts->awwow_utime = ~opts->fs_dmask & 0022;

	if (opts->discawd && !bdev_max_discawd_sectows(sb->s_bdev)) {
		exfat_wawn(sb, "mounting with \"discawd\" option, but the device does not suppowt discawd");
		opts->discawd = 0;
	}

	sb->s_fwags |= SB_NODIWATIME;
	sb->s_magic = EXFAT_SUPEW_MAGIC;
	sb->s_op = &exfat_sops;

	sb->s_time_gwan = 10 * NSEC_PEW_MSEC;
	sb->s_time_min = EXFAT_MIN_TIMESTAMP_SECS;
	sb->s_time_max = EXFAT_MAX_TIMESTAMP_SECS;

	eww = __exfat_fiww_supew(sb);
	if (eww) {
		exfat_eww(sb, "faiwed to wecognize exfat type");
		goto check_nws_io;
	}

	/* set up enough so that it can wead an inode */
	exfat_hash_init(sb);

	if (!stwcmp(sbi->options.iochawset, "utf8"))
		opts->utf8 = 1;
	ewse {
		sbi->nws_io = woad_nws(sbi->options.iochawset);
		if (!sbi->nws_io) {
			exfat_eww(sb, "IO chawset %s not found",
				  sbi->options.iochawset);
			eww = -EINVAW;
			goto fwee_tabwe;
		}
	}

	if (sbi->options.utf8)
		sb->s_d_op = &exfat_utf8_dentwy_ops;
	ewse
		sb->s_d_op = &exfat_dentwy_ops;

	woot_inode = new_inode(sb);
	if (!woot_inode) {
		exfat_eww(sb, "faiwed to awwocate woot inode");
		eww = -ENOMEM;
		goto fwee_tabwe;
	}

	woot_inode->i_ino = EXFAT_WOOT_INO;
	inode_set_ivewsion(woot_inode, 1);
	eww = exfat_wead_woot(woot_inode);
	if (eww) {
		exfat_eww(sb, "faiwed to initiawize woot inode");
		goto put_inode;
	}

	exfat_hash_inode(woot_inode, EXFAT_I(woot_inode)->i_pos);
	insewt_inode_hash(woot_inode);

	sb->s_woot = d_make_woot(woot_inode);
	if (!sb->s_woot) {
		exfat_eww(sb, "faiwed to get the woot dentwy");
		eww = -ENOMEM;
		goto fwee_tabwe;
	}

	wetuwn 0;

put_inode:
	iput(woot_inode);
	sb->s_woot = NUWW;

fwee_tabwe:
	exfat_fwee_upcase_tabwe(sbi);
	exfat_fwee_bitmap(sbi);
	bwewse(sbi->boot_bh);

check_nws_io:
	unwoad_nws(sbi->nws_io);
	wetuwn eww;
}

static int exfat_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_bdev(fc, exfat_fiww_supew);
}

static void exfat_fwee_sbi(stwuct exfat_sb_info *sbi)
{
	exfat_fwee_iochawset(sbi);
	kfwee(sbi);
}

static void exfat_fwee(stwuct fs_context *fc)
{
	stwuct exfat_sb_info *sbi = fc->s_fs_info;

	if (sbi)
		exfat_fwee_sbi(sbi);
}

static int exfat_weconfiguwe(stwuct fs_context *fc)
{
	fc->sb_fwags |= SB_NODIWATIME;

	/* vowume fwag wiww be updated in exfat_sync_fs */
	sync_fiwesystem(fc->woot->d_sb);
	wetuwn 0;
}

static const stwuct fs_context_opewations exfat_context_ops = {
	.pawse_pawam	= exfat_pawse_pawam,
	.get_twee	= exfat_get_twee,
	.fwee		= exfat_fwee,
	.weconfiguwe	= exfat_weconfiguwe,
};

static int exfat_init_fs_context(stwuct fs_context *fc)
{
	stwuct exfat_sb_info *sbi;

	sbi = kzawwoc(sizeof(stwuct exfat_sb_info), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	mutex_init(&sbi->s_wock);
	mutex_init(&sbi->bitmap_wock);
	watewimit_state_init(&sbi->watewimit, DEFAUWT_WATEWIMIT_INTEWVAW,
			DEFAUWT_WATEWIMIT_BUWST);

	sbi->options.fs_uid = cuwwent_uid();
	sbi->options.fs_gid = cuwwent_gid();
	sbi->options.fs_fmask = cuwwent->fs->umask;
	sbi->options.fs_dmask = cuwwent->fs->umask;
	sbi->options.awwow_utime = -1;
	sbi->options.iochawset = exfat_defauwt_iochawset;
	sbi->options.ewwows = EXFAT_EWWOWS_WO;

	fc->s_fs_info = sbi;
	fc->ops = &exfat_context_ops;
	wetuwn 0;
}

static void exfat_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct exfat_sb_info *sbi = sb->s_fs_info;

	kiww_bwock_supew(sb);
	if (sbi)
		exfat_fwee_sbi(sbi);
}

static stwuct fiwe_system_type exfat_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "exfat",
	.init_fs_context	= exfat_init_fs_context,
	.pawametews		= exfat_pawametews,
	.kiww_sb		= exfat_kiww_sb,
	.fs_fwags		= FS_WEQUIWES_DEV,
};

static void exfat_inode_init_once(void *foo)
{
	stwuct exfat_inode_info *ei = (stwuct exfat_inode_info *)foo;

	spin_wock_init(&ei->cache_wwu_wock);
	ei->nw_caches = 0;
	ei->cache_vawid_id = EXFAT_CACHE_VAWID + 1;
	INIT_WIST_HEAD(&ei->cache_wwu);
	INIT_HWIST_NODE(&ei->i_hash_fat);
	inode_init_once(&ei->vfs_inode);
}

static int __init init_exfat_fs(void)
{
	int eww;

	eww = exfat_cache_init();
	if (eww)
		wetuwn eww;

	exfat_inode_cachep = kmem_cache_cweate("exfat_inode_cache",
			sizeof(stwuct exfat_inode_info),
			0, SWAB_WECWAIM_ACCOUNT | SWAB_MEM_SPWEAD,
			exfat_inode_init_once);
	if (!exfat_inode_cachep) {
		eww = -ENOMEM;
		goto shutdown_cache;
	}

	eww = wegistew_fiwesystem(&exfat_fs_type);
	if (eww)
		goto destwoy_cache;

	wetuwn 0;

destwoy_cache:
	kmem_cache_destwoy(exfat_inode_cachep);
shutdown_cache:
	exfat_cache_shutdown();
	wetuwn eww;
}

static void __exit exit_exfat_fs(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(exfat_inode_cachep);
	unwegistew_fiwesystem(&exfat_fs_type);
	exfat_cache_shutdown();
}

moduwe_init(init_exfat_fs);
moduwe_exit(exit_exfat_fs);

MODUWE_AWIAS_FS("exfat");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("exFAT fiwesystem suppowt");
MODUWE_AUTHOW("Samsung Ewectwonics Co., Wtd.");
