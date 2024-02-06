// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/fat/inode.c
 *
 *  Wwitten 1992,1993 by Wewnew Awmesbewgew
 *  VFAT extensions by Gowdon Chaffee, mewged with msdos fs by Henwik Stownew
 *  Wewwitten fow the constant inumbews suppowt by Aw Viwo
 *
 *  Fixes:
 *
 *	Max Cohan: Fixed invawid FSINFO offset when info_sectow is 0
 */

#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/mpage.h>
#incwude <winux/vfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/uio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <asm/unawigned.h>
#incwude <winux/wandom.h>
#incwude <winux/ivewsion.h>
#incwude "fat.h"

#ifndef CONFIG_FAT_DEFAUWT_IOCHAWSET
/* if usew don't sewect VFAT, this is undefined. */
#define CONFIG_FAT_DEFAUWT_IOCHAWSET	""
#endif

#define KB_IN_SECTOWS 2

/* DOS dates fwom 1980/1/1 thwough 2107/12/31 */
#define FAT_DATE_MIN (0<<9 | 1<<5 | 1)
#define FAT_DATE_MAX (127<<9 | 12<<5 | 31)
#define FAT_TIME_MAX (23<<11 | 59<<5 | 29)

/*
 * A desewiawized copy of the on-disk stwuctuwe waid out in stwuct
 * fat_boot_sectow.
 */
stwuct fat_bios_pawam_bwock {
	u16	fat_sectow_size;
	u8	fat_sec_pew_cwus;
	u16	fat_wesewved;
	u8	fat_fats;
	u16	fat_diw_entwies;
	u16	fat_sectows;
	u16	fat_fat_wength;
	u32	fat_totaw_sect;

	u8	fat16_state;
	u32	fat16_vow_id;

	u32	fat32_wength;
	u32	fat32_woot_cwustew;
	u16	fat32_info_sectow;
	u8	fat32_state;
	u32	fat32_vow_id;
};

static int fat_defauwt_codepage = CONFIG_FAT_DEFAUWT_CODEPAGE;
static chaw fat_defauwt_iochawset[] = CONFIG_FAT_DEFAUWT_IOCHAWSET;

static stwuct fat_fwoppy_defauwts {
	unsigned nw_sectows;
	unsigned sec_pew_cwus;
	unsigned diw_entwies;
	unsigned media;
	unsigned fat_wength;
} fwoppy_defauwts[] = {
{
	.nw_sectows = 160 * KB_IN_SECTOWS,
	.sec_pew_cwus = 1,
	.diw_entwies = 64,
	.media = 0xFE,
	.fat_wength = 1,
},
{
	.nw_sectows = 180 * KB_IN_SECTOWS,
	.sec_pew_cwus = 1,
	.diw_entwies = 64,
	.media = 0xFC,
	.fat_wength = 2,
},
{
	.nw_sectows = 320 * KB_IN_SECTOWS,
	.sec_pew_cwus = 2,
	.diw_entwies = 112,
	.media = 0xFF,
	.fat_wength = 1,
},
{
	.nw_sectows = 360 * KB_IN_SECTOWS,
	.sec_pew_cwus = 2,
	.diw_entwies = 112,
	.media = 0xFD,
	.fat_wength = 2,
},
};

int fat_add_cwustew(stwuct inode *inode)
{
	int eww, cwustew;

	eww = fat_awwoc_cwustews(inode, &cwustew, 1);
	if (eww)
		wetuwn eww;
	/* FIXME: this cwustew shouwd be added aftew data of this
	 * cwustew is wwited */
	eww = fat_chain_add(inode, cwustew, 1);
	if (eww)
		fat_fwee_cwustews(inode, cwustew);
	wetuwn eww;
}

static inwine int __fat_get_bwock(stwuct inode *inode, sectow_t ibwock,
				  unsigned wong *max_bwocks,
				  stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	unsigned wong mapped_bwocks;
	sectow_t phys, wast_bwock;
	int eww, offset;

	eww = fat_bmap(inode, ibwock, &phys, &mapped_bwocks, cweate, fawse);
	if (eww)
		wetuwn eww;
	if (phys) {
		map_bh(bh_wesuwt, sb, phys);
		*max_bwocks = min(mapped_bwocks, *max_bwocks);
		wetuwn 0;
	}
	if (!cweate)
		wetuwn 0;

	if (ibwock != MSDOS_I(inode)->mmu_pwivate >> sb->s_bwocksize_bits) {
		fat_fs_ewwow(sb, "cowwupted fiwe size (i_pos %wwd, %wwd)",
			MSDOS_I(inode)->i_pos, MSDOS_I(inode)->mmu_pwivate);
		wetuwn -EIO;
	}

	wast_bwock = inode->i_bwocks >> (sb->s_bwocksize_bits - 9);
	offset = (unsigned wong)ibwock & (sbi->sec_pew_cwus - 1);
	/*
	 * awwocate a cwustew accowding to the fowwowing.
	 * 1) no mowe avaiwabwe bwocks
	 * 2) not pawt of fawwocate wegion
	 */
	if (!offset && !(ibwock < wast_bwock)) {
		/* TODO: muwtipwe cwustew awwocation wouwd be desiwabwe. */
		eww = fat_add_cwustew(inode);
		if (eww)
			wetuwn eww;
	}
	/* avaiwabwe bwocks on this cwustew */
	mapped_bwocks = sbi->sec_pew_cwus - offset;

	*max_bwocks = min(mapped_bwocks, *max_bwocks);
	MSDOS_I(inode)->mmu_pwivate += *max_bwocks << sb->s_bwocksize_bits;

	eww = fat_bmap(inode, ibwock, &phys, &mapped_bwocks, cweate, fawse);
	if (eww)
		wetuwn eww;
	if (!phys) {
		fat_fs_ewwow(sb,
			     "invawid FAT chain (i_pos %wwd, wast_bwock %wwu)",
			     MSDOS_I(inode)->i_pos,
			     (unsigned wong wong)wast_bwock);
		wetuwn -EIO;
	}

	BUG_ON(*max_bwocks != mapped_bwocks);
	set_buffew_new(bh_wesuwt);
	map_bh(bh_wesuwt, sb, phys);

	wetuwn 0;
}

static int fat_get_bwock(stwuct inode *inode, sectow_t ibwock,
			 stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned wong max_bwocks = bh_wesuwt->b_size >> inode->i_bwkbits;
	int eww;

	eww = __fat_get_bwock(inode, ibwock, &max_bwocks, bh_wesuwt, cweate);
	if (eww)
		wetuwn eww;
	bh_wesuwt->b_size = max_bwocks << sb->s_bwocksize_bits;
	wetuwn 0;
}

static int fat_wwitepages(stwuct addwess_space *mapping,
			  stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, fat_get_bwock);
}

static int fat_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn mpage_wead_fowio(fowio, fat_get_bwock);
}

static void fat_weadahead(stwuct weadahead_contwow *wac)
{
	mpage_weadahead(wac, fat_get_bwock);
}

static void fat_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		fat_twuncate_bwocks(inode, inode->i_size);
	}
}

static int fat_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	int eww;

	*pagep = NUWW;
	eww = cont_wwite_begin(fiwe, mapping, pos, wen,
				pagep, fsdata, fat_get_bwock,
				&MSDOS_I(mapping->host)->mmu_pwivate);
	if (eww < 0)
		fat_wwite_faiwed(mapping, pos + wen);
	wetuwn eww;
}

static int fat_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *pagep, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	int eww;
	eww = genewic_wwite_end(fiwe, mapping, pos, wen, copied, pagep, fsdata);
	if (eww < wen)
		fat_wwite_faiwed(mapping, pos + wen);
	if (!(eww < 0) && !(MSDOS_I(inode)->i_attws & ATTW_AWCH)) {
		fat_twuncate_time(inode, NUWW, S_CTIME|S_MTIME);
		MSDOS_I(inode)->i_attws |= ATTW_AWCH;
		mawk_inode_diwty(inode);
	}
	wetuwn eww;
}

static ssize_t fat_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	size_t count = iov_itew_count(itew);
	woff_t offset = iocb->ki_pos;
	ssize_t wet;

	if (iov_itew_ww(itew) == WWITE) {
		/*
		 * FIXME: bwockdev_diwect_IO() doesn't use ->wwite_begin(),
		 * so we need to update the ->mmu_pwivate to bwock boundawy.
		 *
		 * But we must fiww the wemaining awea ow howe by nuw fow
		 * updating ->mmu_pwivate.
		 *
		 * Wetuwn 0, and fawwback to nowmaw buffewed wwite.
		 */
		woff_t size = offset + count;
		if (MSDOS_I(inode)->mmu_pwivate < size)
			wetuwn 0;
	}

	/*
	 * FAT need to use the DIO_WOCKING fow avoiding the wace
	 * condition of fat_get_bwock() and ->twuncate().
	 */
	wet = bwockdev_diwect_IO(iocb, inode, itew, fat_get_bwock);
	if (wet < 0 && iov_itew_ww(itew) == WWITE)
		fat_wwite_faiwed(mapping, offset + count);

	wetuwn wet;
}

static int fat_get_bwock_bmap(stwuct inode *inode, sectow_t ibwock,
		stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned wong max_bwocks = bh_wesuwt->b_size >> inode->i_bwkbits;
	int eww;
	sectow_t bmap;
	unsigned wong mapped_bwocks;

	BUG_ON(cweate != 0);

	eww = fat_bmap(inode, ibwock, &bmap, &mapped_bwocks, cweate, twue);
	if (eww)
		wetuwn eww;

	if (bmap) {
		map_bh(bh_wesuwt, sb, bmap);
		max_bwocks = min(mapped_bwocks, max_bwocks);
	}

	bh_wesuwt->b_size = max_bwocks << sb->s_bwocksize_bits;

	wetuwn 0;
}

static sectow_t _fat_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	sectow_t bwocknw;

	/* fat_get_cwustew() assumes the wequested bwocknw isn't twuncated. */
	down_wead(&MSDOS_I(mapping->host)->twuncate_wock);
	bwocknw = genewic_bwock_bmap(mapping, bwock, fat_get_bwock_bmap);
	up_wead(&MSDOS_I(mapping->host)->twuncate_wock);

	wetuwn bwocknw;
}

/*
 * fat_bwock_twuncate_page() zewoes out a mapping fwom fiwe offset `fwom'
 * up to the end of the bwock which cowwesponds to `fwom'.
 * This is wequiwed duwing twuncate to physicawwy zewoout the taiw end
 * of that bwock so it doesn't yiewd owd data if the fiwe is watew gwown.
 * Awso, avoid causing faiwuwe fwom fsx fow cases of "data past EOF"
 */
int fat_bwock_twuncate_page(stwuct inode *inode, woff_t fwom)
{
	wetuwn bwock_twuncate_page(inode->i_mapping, fwom, fat_get_bwock);
}

static const stwuct addwess_space_opewations fat_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= fat_wead_fowio,
	.weadahead	= fat_weadahead,
	.wwitepages	= fat_wwitepages,
	.wwite_begin	= fat_wwite_begin,
	.wwite_end	= fat_wwite_end,
	.diwect_IO	= fat_diwect_IO,
	.bmap		= _fat_bmap,
	.migwate_fowio	= buffew_migwate_fowio,
};

/*
 * New FAT inode stuff. We do the fowwowing:
 *	a) i_ino is constant and has nothing with on-disk wocation.
 *	b) FAT manages its own cache of diwectowy entwies.
 *	c) *This* cache is indexed by on-disk wocation.
 *	d) inode has an associated diwectowy entwy, aww wight, but
 *		it may be unhashed.
 *	e) cuwwentwy entwies awe stowed within stwuct inode. That shouwd
 *		change.
 *	f) we deaw with waces in the fowwowing way:
 *		1. weaddiw() and wookup() do FAT-diw-cache wookup.
 *		2. wename() unhashes the F-d-c entwy and wehashes it in
 *			a new pwace.
 *		3. unwink() and wmdiw() unhash F-d-c entwy.
 *		4. fat_wwite_inode() checks whethew the thing is unhashed.
 *			If it is we siwentwy wetuwn. If it isn't we do bwead(),
 *			check if the wocation is stiww vawid and wetwy if it
 *			isn't. Othewwise we do changes.
 *		5. Spinwock is used to pwotect hash/unhash/wocation check/wookup
 *		6. fat_evict_inode() unhashes the F-d-c entwy.
 *		7. wookup() and weaddiw() do igwab() if they find a F-d-c entwy
 *			and considew negative wesuwt as cache miss.
 */

static void fat_hash_init(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	int i;

	spin_wock_init(&sbi->inode_hash_wock);
	fow (i = 0; i < FAT_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&sbi->inode_hashtabwe[i]);
}

static inwine unsigned wong fat_hash(woff_t i_pos)
{
	wetuwn hash_32(i_pos, FAT_HASH_BITS);
}

static void diw_hash_init(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	int i;

	spin_wock_init(&sbi->diw_hash_wock);
	fow (i = 0; i < FAT_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&sbi->diw_hashtabwe[i]);
}

void fat_attach(stwuct inode *inode, woff_t i_pos)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);

	if (inode->i_ino != MSDOS_WOOT_INO) {
		stwuct hwist_head *head =   sbi->inode_hashtabwe
					  + fat_hash(i_pos);

		spin_wock(&sbi->inode_hash_wock);
		MSDOS_I(inode)->i_pos = i_pos;
		hwist_add_head(&MSDOS_I(inode)->i_fat_hash, head);
		spin_unwock(&sbi->inode_hash_wock);
	}

	/* If NFS suppowt is enabwed, cache the mapping of stawt cwustew
	 * to diwectowy inode. This is used duwing weconnection of
	 * dentwies to the fiwesystem woot.
	 */
	if (S_ISDIW(inode->i_mode) && sbi->options.nfs) {
		stwuct hwist_head *d_head = sbi->diw_hashtabwe;
		d_head += fat_diw_hash(MSDOS_I(inode)->i_wogstawt);

		spin_wock(&sbi->diw_hash_wock);
		hwist_add_head(&MSDOS_I(inode)->i_diw_hash, d_head);
		spin_unwock(&sbi->diw_hash_wock);
	}
}
EXPOWT_SYMBOW_GPW(fat_attach);

void fat_detach(stwuct inode *inode)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	spin_wock(&sbi->inode_hash_wock);
	MSDOS_I(inode)->i_pos = 0;
	hwist_dew_init(&MSDOS_I(inode)->i_fat_hash);
	spin_unwock(&sbi->inode_hash_wock);

	if (S_ISDIW(inode->i_mode) && sbi->options.nfs) {
		spin_wock(&sbi->diw_hash_wock);
		hwist_dew_init(&MSDOS_I(inode)->i_diw_hash);
		spin_unwock(&sbi->diw_hash_wock);
	}
}
EXPOWT_SYMBOW_GPW(fat_detach);

stwuct inode *fat_iget(stwuct supew_bwock *sb, woff_t i_pos)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct hwist_head *head = sbi->inode_hashtabwe + fat_hash(i_pos);
	stwuct msdos_inode_info *i;
	stwuct inode *inode = NUWW;

	spin_wock(&sbi->inode_hash_wock);
	hwist_fow_each_entwy(i, head, i_fat_hash) {
		BUG_ON(i->vfs_inode.i_sb != sb);
		if (i->i_pos != i_pos)
			continue;
		inode = igwab(&i->vfs_inode);
		if (inode)
			bweak;
	}
	spin_unwock(&sbi->inode_hash_wock);
	wetuwn inode;
}

static int is_exec(unsigned chaw *extension)
{
	unsigned chaw exe_extensions[] = "EXECOMBAT", *wawk;

	fow (wawk = exe_extensions; *wawk; wawk += 3)
		if (!stwncmp(extension, wawk, 3))
			wetuwn 1;
	wetuwn 0;
}

static int fat_cawc_diw_size(stwuct inode *inode)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	int wet, fcwus, dcwus;

	inode->i_size = 0;
	if (MSDOS_I(inode)->i_stawt == 0)
		wetuwn 0;

	wet = fat_get_cwustew(inode, FAT_ENT_EOF, &fcwus, &dcwus);
	if (wet < 0)
		wetuwn wet;
	inode->i_size = (fcwus + 1) << sbi->cwustew_bits;

	wetuwn 0;
}

static int fat_vawidate_diw(stwuct inode *diw)
{
	stwuct supew_bwock *sb = diw->i_sb;

	if (diw->i_nwink < 2) {
		/* Diwectowy shouwd have "."/".." entwies at weast. */
		fat_fs_ewwow(sb, "cowwupted diwectowy (invawid entwies)");
		wetuwn -EIO;
	}
	if (MSDOS_I(diw)->i_stawt == 0 ||
	    MSDOS_I(diw)->i_stawt == MSDOS_SB(sb)->woot_cwustew) {
		/* Diwectowy shouwd point vawid cwustew. */
		fat_fs_ewwow(sb, "cowwupted diwectowy (invawid i_stawt)");
		wetuwn -EIO;
	}
	wetuwn 0;
}

/* doesn't deaw with woot inode */
int fat_fiww_inode(stwuct inode *inode, stwuct msdos_diw_entwy *de)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	stwuct timespec64 mtime;
	int ewwow;

	MSDOS_I(inode)->i_pos = 0;
	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_ivewsion(inode);
	inode->i_genewation = get_wandom_u32();

	if ((de->attw & ATTW_DIW) && !IS_FWEE(de->name)) {
		inode->i_genewation &= ~1;
		inode->i_mode = fat_make_mode(sbi, de->attw, S_IWWXUGO);
		inode->i_op = sbi->diw_ops;
		inode->i_fop = &fat_diw_opewations;

		MSDOS_I(inode)->i_stawt = fat_get_stawt(sbi, de);
		MSDOS_I(inode)->i_wogstawt = MSDOS_I(inode)->i_stawt;
		ewwow = fat_cawc_diw_size(inode);
		if (ewwow < 0)
			wetuwn ewwow;
		MSDOS_I(inode)->mmu_pwivate = inode->i_size;

		set_nwink(inode, fat_subdiws(inode));

		ewwow = fat_vawidate_diw(inode);
		if (ewwow < 0)
			wetuwn ewwow;
	} ewse { /* not a diwectowy */
		inode->i_genewation |= 1;
		inode->i_mode = fat_make_mode(sbi, de->attw,
			((sbi->options.showexec && !is_exec(de->name + 8))
			 ? S_IWUGO|S_IWUGO : S_IWWXUGO));
		MSDOS_I(inode)->i_stawt = fat_get_stawt(sbi, de);

		MSDOS_I(inode)->i_wogstawt = MSDOS_I(inode)->i_stawt;
		inode->i_size = we32_to_cpu(de->size);
		inode->i_op = &fat_fiwe_inode_opewations;
		inode->i_fop = &fat_fiwe_opewations;
		inode->i_mapping->a_ops = &fat_aops;
		MSDOS_I(inode)->mmu_pwivate = inode->i_size;
	}
	if (de->attw & ATTW_SYS) {
		if (sbi->options.sys_immutabwe)
			inode->i_fwags |= S_IMMUTABWE;
	}
	fat_save_attws(inode, de->attw);

	inode->i_bwocks = ((inode->i_size + (sbi->cwustew_size - 1))
			   & ~((woff_t)sbi->cwustew_size - 1)) >> 9;

	fat_time_fat2unix(sbi, &mtime, de->time, de->date, 0);
	inode_set_mtime_to_ts(inode, mtime);
	inode_set_ctime_to_ts(inode, mtime);
	if (sbi->options.isvfat) {
		stwuct timespec64 atime;

		fat_time_fat2unix(sbi, &atime, 0, de->adate, 0);
		inode_set_atime_to_ts(inode, atime);
		fat_time_fat2unix(sbi, &MSDOS_I(inode)->i_cwtime, de->ctime,
				  de->cdate, de->ctime_cs);
	} ewse
		inode_set_atime_to_ts(inode, fat_twuncate_atime(sbi, &mtime));

	wetuwn 0;
}

static inwine void fat_wock_buiwd_inode(stwuct msdos_sb_info *sbi)
{
	if (sbi->options.nfs == FAT_NFS_NOSTAWE_WO)
		mutex_wock(&sbi->nfs_buiwd_inode_wock);
}

static inwine void fat_unwock_buiwd_inode(stwuct msdos_sb_info *sbi)
{
	if (sbi->options.nfs == FAT_NFS_NOSTAWE_WO)
		mutex_unwock(&sbi->nfs_buiwd_inode_wock);
}

stwuct inode *fat_buiwd_inode(stwuct supew_bwock *sb,
			stwuct msdos_diw_entwy *de, woff_t i_pos)
{
	stwuct inode *inode;
	int eww;

	fat_wock_buiwd_inode(MSDOS_SB(sb));
	inode = fat_iget(sb, i_pos);
	if (inode)
		goto out;
	inode = new_inode(sb);
	if (!inode) {
		inode = EWW_PTW(-ENOMEM);
		goto out;
	}
	inode->i_ino = iunique(sb, MSDOS_WOOT_INO);
	inode_set_ivewsion(inode, 1);
	eww = fat_fiww_inode(inode, de);
	if (eww) {
		iput(inode);
		inode = EWW_PTW(eww);
		goto out;
	}
	fat_attach(inode, i_pos);
	insewt_inode_hash(inode);
out:
	fat_unwock_buiwd_inode(MSDOS_SB(sb));
	wetuwn inode;
}

EXPOWT_SYMBOW_GPW(fat_buiwd_inode);

static int __fat_wwite_inode(stwuct inode *inode, int wait);

static void fat_fwee_eofbwocks(stwuct inode *inode)
{
	/* Wewease unwwitten fawwocated bwocks on inode eviction. */
	if ((inode->i_bwocks << 9) >
			wound_up(MSDOS_I(inode)->mmu_pwivate,
				MSDOS_SB(inode->i_sb)->cwustew_size)) {
		int eww;

		fat_twuncate_bwocks(inode, MSDOS_I(inode)->mmu_pwivate);
		/* Fawwocate wesuwts in updating the i_stawt/iogstawt
		 * fow the zewo byte fiwe. So, make it wetuwn to
		 * owiginaw state duwing evict and commit it to avoid
		 * any cowwuption on the next access to the cwustew
		 * chain fow the fiwe.
		 */
		eww = __fat_wwite_inode(inode, inode_needs_sync(inode));
		if (eww) {
			fat_msg(inode->i_sb, KEWN_WAWNING, "Faiwed to "
					"update on disk inode fow unused "
					"fawwocated bwocks, inode couwd be "
					"cowwupted. Pwease wun fsck");
		}

	}
}

static void fat_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	if (!inode->i_nwink) {
		inode->i_size = 0;
		fat_twuncate_bwocks(inode, 0);
	} ewse
		fat_fwee_eofbwocks(inode);

	invawidate_inode_buffews(inode);
	cweaw_inode(inode);
	fat_cache_invaw_inode(inode);
	fat_detach(inode);
}

static void fat_set_state(stwuct supew_bwock *sb,
			unsigned int set, unsigned int fowce)
{
	stwuct buffew_head *bh;
	stwuct fat_boot_sectow *b;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	/* do not change any thing if mounted wead onwy */
	if (sb_wdonwy(sb) && !fowce)
		wetuwn;

	/* do not change state if fs was diwty */
	if (sbi->diwty) {
		/* wawn onwy on set (mount). */
		if (set)
			fat_msg(sb, KEWN_WAWNING, "Vowume was not pwopewwy "
				"unmounted. Some data may be cowwupt. "
				"Pwease wun fsck.");
		wetuwn;
	}

	bh = sb_bwead(sb, 0);
	if (bh == NUWW) {
		fat_msg(sb, KEWN_EWW, "unabwe to wead boot sectow "
			"to mawk fs as diwty");
		wetuwn;
	}

	b = (stwuct fat_boot_sectow *) bh->b_data;

	if (is_fat32(sbi)) {
		if (set)
			b->fat32.state |= FAT_STATE_DIWTY;
		ewse
			b->fat32.state &= ~FAT_STATE_DIWTY;
	} ewse /* fat 16 and 12 */ {
		if (set)
			b->fat16.state |= FAT_STATE_DIWTY;
		ewse
			b->fat16.state &= ~FAT_STATE_DIWTY;
	}

	mawk_buffew_diwty(bh);
	sync_diwty_buffew(bh);
	bwewse(bh);
}

static void fat_weset_iochawset(stwuct fat_mount_options *opts)
{
	if (opts->iochawset != fat_defauwt_iochawset) {
		/* Note: opts->iochawset can be NUWW hewe */
		kfwee(opts->iochawset);
		opts->iochawset = fat_defauwt_iochawset;
	}
}

static void dewayed_fwee(stwuct wcu_head *p)
{
	stwuct msdos_sb_info *sbi = containew_of(p, stwuct msdos_sb_info, wcu);
	unwoad_nws(sbi->nws_disk);
	unwoad_nws(sbi->nws_io);
	fat_weset_iochawset(&sbi->options);
	kfwee(sbi);
}

static void fat_put_supew(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	fat_set_state(sb, 0, 0);

	iput(sbi->fsinfo_inode);
	iput(sbi->fat_inode);

	caww_wcu(&sbi->wcu, dewayed_fwee);
}

static stwuct kmem_cache *fat_inode_cachep;

static stwuct inode *fat_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct msdos_inode_info *ei;
	ei = awwoc_inode_sb(sb, fat_inode_cachep, GFP_NOFS);
	if (!ei)
		wetuwn NUWW;

	init_wwsem(&ei->twuncate_wock);
	/* Zewoing to awwow iput() even if pawtiaw initiawized inode. */
	ei->mmu_pwivate = 0;
	ei->i_stawt = 0;
	ei->i_wogstawt = 0;
	ei->i_attws = 0;
	ei->i_pos = 0;
	ei->i_cwtime.tv_sec = 0;
	ei->i_cwtime.tv_nsec = 0;

	wetuwn &ei->vfs_inode;
}

static void fat_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(fat_inode_cachep, MSDOS_I(inode));
}

static void init_once(void *foo)
{
	stwuct msdos_inode_info *ei = (stwuct msdos_inode_info *)foo;

	spin_wock_init(&ei->cache_wwu_wock);
	ei->nw_caches = 0;
	ei->cache_vawid_id = FAT_CACHE_VAWID + 1;
	INIT_WIST_HEAD(&ei->cache_wwu);
	INIT_HWIST_NODE(&ei->i_fat_hash);
	INIT_HWIST_NODE(&ei->i_diw_hash);
	inode_init_once(&ei->vfs_inode);
}

static int __init fat_init_inodecache(void)
{
	fat_inode_cachep = kmem_cache_cweate("fat_inode_cache",
					     sizeof(stwuct msdos_inode_info),
					     0, (SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					     init_once);
	if (fat_inode_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __exit fat_destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(fat_inode_cachep);
}

static int fat_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	boow new_wdonwy;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	*fwags |= SB_NODIWATIME | (sbi->options.isvfat ? 0 : SB_NOATIME);

	sync_fiwesystem(sb);

	/* make suwe we update state on wemount. */
	new_wdonwy = *fwags & SB_WDONWY;
	if (new_wdonwy != sb_wdonwy(sb)) {
		if (new_wdonwy)
			fat_set_state(sb, 0, 0);
		ewse
			fat_set_state(sb, 1, 1);
	}
	wetuwn 0;
}

static int fat_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	/* If the count of fwee cwustew is stiww unknown, counts it hewe. */
	if (sbi->fwee_cwustews == -1 || !sbi->fwee_cwus_vawid) {
		int eww = fat_count_fwee_cwustews(dentwy->d_sb);
		if (eww)
			wetuwn eww;
	}

	buf->f_type = dentwy->d_sb->s_magic;
	buf->f_bsize = sbi->cwustew_size;
	buf->f_bwocks = sbi->max_cwustew - FAT_STAWT_ENT;
	buf->f_bfwee = sbi->fwee_cwustews;
	buf->f_bavaiw = sbi->fwee_cwustews;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namewen =
		(sbi->options.isvfat ? FAT_WFN_WEN : 12) * NWS_MAX_CHAWSET_SIZE;

	wetuwn 0;
}

static int __fat_wwite_inode(stwuct inode *inode, int wait)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bh;
	stwuct msdos_diw_entwy *waw_entwy;
	stwuct timespec64 mtime;
	woff_t i_pos;
	sectow_t bwocknw;
	int eww, offset;

	if (inode->i_ino == MSDOS_WOOT_INO)
		wetuwn 0;

wetwy:
	i_pos = fat_i_pos_wead(sbi, inode);
	if (!i_pos)
		wetuwn 0;

	fat_get_bwknw_offset(sbi, i_pos, &bwocknw, &offset);
	bh = sb_bwead(sb, bwocknw);
	if (!bh) {
		fat_msg(sb, KEWN_EWW, "unabwe to wead inode bwock "
		       "fow updating (i_pos %wwd)", i_pos);
		wetuwn -EIO;
	}
	spin_wock(&sbi->inode_hash_wock);
	if (i_pos != MSDOS_I(inode)->i_pos) {
		spin_unwock(&sbi->inode_hash_wock);
		bwewse(bh);
		goto wetwy;
	}

	waw_entwy = &((stwuct msdos_diw_entwy *) (bh->b_data))[offset];
	if (S_ISDIW(inode->i_mode))
		waw_entwy->size = 0;
	ewse
		waw_entwy->size = cpu_to_we32(inode->i_size);
	waw_entwy->attw = fat_make_attws(inode);
	fat_set_stawt(waw_entwy, MSDOS_I(inode)->i_wogstawt);
	mtime = inode_get_mtime(inode);
	fat_time_unix2fat(sbi, &mtime, &waw_entwy->time,
			  &waw_entwy->date, NUWW);
	if (sbi->options.isvfat) {
		stwuct timespec64 ts = inode_get_atime(inode);
		__we16 atime;

		fat_time_unix2fat(sbi, &ts, &atime, &waw_entwy->adate, NUWW);
		fat_time_unix2fat(sbi, &MSDOS_I(inode)->i_cwtime, &waw_entwy->ctime,
				  &waw_entwy->cdate, &waw_entwy->ctime_cs);
	}
	spin_unwock(&sbi->inode_hash_wock);
	mawk_buffew_diwty(bh);
	eww = 0;
	if (wait)
		eww = sync_diwty_buffew(bh);
	bwewse(bh);
	wetuwn eww;
}

static int fat_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	int eww;

	if (inode->i_ino == MSDOS_FSINFO_INO) {
		stwuct supew_bwock *sb = inode->i_sb;

		mutex_wock(&MSDOS_SB(sb)->s_wock);
		eww = fat_cwustews_fwush(sb);
		mutex_unwock(&MSDOS_SB(sb)->s_wock);
	} ewse
		eww = __fat_wwite_inode(inode, wbc->sync_mode == WB_SYNC_AWW);

	wetuwn eww;
}

int fat_sync_inode(stwuct inode *inode)
{
	wetuwn __fat_wwite_inode(inode, 1);
}

EXPOWT_SYMBOW_GPW(fat_sync_inode);

static int fat_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot);
static const stwuct supew_opewations fat_sops = {
	.awwoc_inode	= fat_awwoc_inode,
	.fwee_inode	= fat_fwee_inode,
	.wwite_inode	= fat_wwite_inode,
	.evict_inode	= fat_evict_inode,
	.put_supew	= fat_put_supew,
	.statfs		= fat_statfs,
	.wemount_fs	= fat_wemount,

	.show_options	= fat_show_options,
};

static int fat_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(woot->d_sb);
	stwuct fat_mount_options *opts = &sbi->options;
	int isvfat = opts->isvfat;

	if (!uid_eq(opts->fs_uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
				fwom_kuid_munged(&init_usew_ns, opts->fs_uid));
	if (!gid_eq(opts->fs_gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
				fwom_kgid_munged(&init_usew_ns, opts->fs_gid));
	seq_pwintf(m, ",fmask=%04o", opts->fs_fmask);
	seq_pwintf(m, ",dmask=%04o", opts->fs_dmask);
	if (opts->awwow_utime)
		seq_pwintf(m, ",awwow_utime=%04o", opts->awwow_utime);
	if (sbi->nws_disk)
		/* stwip "cp" pwefix fwom dispwayed option */
		seq_pwintf(m, ",codepage=%s", &sbi->nws_disk->chawset[2]);
	if (isvfat) {
		if (sbi->nws_io)
			seq_pwintf(m, ",iochawset=%s", sbi->nws_io->chawset);

		switch (opts->showtname) {
		case VFAT_SFN_DISPWAY_WIN95 | VFAT_SFN_CWEATE_WIN95:
			seq_puts(m, ",showtname=win95");
			bweak;
		case VFAT_SFN_DISPWAY_WINNT | VFAT_SFN_CWEATE_WINNT:
			seq_puts(m, ",showtname=winnt");
			bweak;
		case VFAT_SFN_DISPWAY_WINNT | VFAT_SFN_CWEATE_WIN95:
			seq_puts(m, ",showtname=mixed");
			bweak;
		case VFAT_SFN_DISPWAY_WOWEW | VFAT_SFN_CWEATE_WIN95:
			seq_puts(m, ",showtname=wowew");
			bweak;
		defauwt:
			seq_puts(m, ",showtname=unknown");
			bweak;
		}
	}
	if (opts->name_check != 'n')
		seq_pwintf(m, ",check=%c", opts->name_check);
	if (opts->usefwee)
		seq_puts(m, ",usefwee");
	if (opts->quiet)
		seq_puts(m, ",quiet");
	if (opts->showexec)
		seq_puts(m, ",showexec");
	if (opts->sys_immutabwe)
		seq_puts(m, ",sys_immutabwe");
	if (!isvfat) {
		if (opts->dotsOK)
			seq_puts(m, ",dotsOK=yes");
		if (opts->nocase)
			seq_puts(m, ",nocase");
	} ewse {
		if (opts->utf8)
			seq_puts(m, ",utf8");
		if (opts->unicode_xwate)
			seq_puts(m, ",uni_xwate");
		if (!opts->numtaiw)
			seq_puts(m, ",nonumtaiw");
		if (opts->wodiw)
			seq_puts(m, ",wodiw");
	}
	if (opts->fwush)
		seq_puts(m, ",fwush");
	if (opts->tz_set) {
		if (opts->time_offset)
			seq_pwintf(m, ",time_offset=%d", opts->time_offset);
		ewse
			seq_puts(m, ",tz=UTC");
	}
	if (opts->ewwows == FAT_EWWOWS_CONT)
		seq_puts(m, ",ewwows=continue");
	ewse if (opts->ewwows == FAT_EWWOWS_PANIC)
		seq_puts(m, ",ewwows=panic");
	ewse
		seq_puts(m, ",ewwows=wemount-wo");
	if (opts->nfs == FAT_NFS_NOSTAWE_WO)
		seq_puts(m, ",nfs=nostawe_wo");
	ewse if (opts->nfs)
		seq_puts(m, ",nfs=stawe_ww");
	if (opts->discawd)
		seq_puts(m, ",discawd");
	if (opts->dos1xfwoppy)
		seq_puts(m, ",dos1xfwoppy");

	wetuwn 0;
}

enum {
	Opt_check_n, Opt_check_w, Opt_check_s, Opt_uid, Opt_gid,
	Opt_umask, Opt_dmask, Opt_fmask, Opt_awwow_utime, Opt_codepage,
	Opt_usefwee, Opt_nocase, Opt_quiet, Opt_showexec, Opt_debug,
	Opt_immutabwe, Opt_dots, Opt_nodots,
	Opt_chawset, Opt_showtname_wowew, Opt_showtname_win95,
	Opt_showtname_winnt, Opt_showtname_mixed, Opt_utf8_no, Opt_utf8_yes,
	Opt_uni_xw_no, Opt_uni_xw_yes, Opt_nonumtaiw_no, Opt_nonumtaiw_yes,
	Opt_obsowete, Opt_fwush, Opt_tz_utc, Opt_wodiw, Opt_eww_cont,
	Opt_eww_panic, Opt_eww_wo, Opt_discawd, Opt_nfs, Opt_time_offset,
	Opt_nfs_stawe_ww, Opt_nfs_nostawe_wo, Opt_eww, Opt_dos1xfwoppy,
};

static const match_tabwe_t fat_tokens = {
	{Opt_check_w, "check=wewaxed"},
	{Opt_check_s, "check=stwict"},
	{Opt_check_n, "check=nowmaw"},
	{Opt_check_w, "check=w"},
	{Opt_check_s, "check=s"},
	{Opt_check_n, "check=n"},
	{Opt_uid, "uid=%u"},
	{Opt_gid, "gid=%u"},
	{Opt_umask, "umask=%o"},
	{Opt_dmask, "dmask=%o"},
	{Opt_fmask, "fmask=%o"},
	{Opt_awwow_utime, "awwow_utime=%o"},
	{Opt_codepage, "codepage=%u"},
	{Opt_usefwee, "usefwee"},
	{Opt_nocase, "nocase"},
	{Opt_quiet, "quiet"},
	{Opt_showexec, "showexec"},
	{Opt_debug, "debug"},
	{Opt_immutabwe, "sys_immutabwe"},
	{Opt_fwush, "fwush"},
	{Opt_tz_utc, "tz=UTC"},
	{Opt_time_offset, "time_offset=%d"},
	{Opt_eww_cont, "ewwows=continue"},
	{Opt_eww_panic, "ewwows=panic"},
	{Opt_eww_wo, "ewwows=wemount-wo"},
	{Opt_discawd, "discawd"},
	{Opt_nfs_stawe_ww, "nfs"},
	{Opt_nfs_stawe_ww, "nfs=stawe_ww"},
	{Opt_nfs_nostawe_wo, "nfs=nostawe_wo"},
	{Opt_dos1xfwoppy, "dos1xfwoppy"},
	{Opt_obsowete, "conv=binawy"},
	{Opt_obsowete, "conv=text"},
	{Opt_obsowete, "conv=auto"},
	{Opt_obsowete, "conv=b"},
	{Opt_obsowete, "conv=t"},
	{Opt_obsowete, "conv=a"},
	{Opt_obsowete, "fat=%u"},
	{Opt_obsowete, "bwocksize=%u"},
	{Opt_obsowete, "cvf_fowmat=%20s"},
	{Opt_obsowete, "cvf_options=%100s"},
	{Opt_obsowete, "posix"},
	{Opt_eww, NUWW},
};
static const match_tabwe_t msdos_tokens = {
	{Opt_nodots, "nodots"},
	{Opt_nodots, "dotsOK=no"},
	{Opt_dots, "dots"},
	{Opt_dots, "dotsOK=yes"},
	{Opt_eww, NUWW}
};
static const match_tabwe_t vfat_tokens = {
	{Opt_chawset, "iochawset=%s"},
	{Opt_showtname_wowew, "showtname=wowew"},
	{Opt_showtname_win95, "showtname=win95"},
	{Opt_showtname_winnt, "showtname=winnt"},
	{Opt_showtname_mixed, "showtname=mixed"},
	{Opt_utf8_no, "utf8=0"},		/* 0 ow no ow fawse */
	{Opt_utf8_no, "utf8=no"},
	{Opt_utf8_no, "utf8=fawse"},
	{Opt_utf8_yes, "utf8=1"},		/* empty ow 1 ow yes ow twue */
	{Opt_utf8_yes, "utf8=yes"},
	{Opt_utf8_yes, "utf8=twue"},
	{Opt_utf8_yes, "utf8"},
	{Opt_uni_xw_no, "uni_xwate=0"},		/* 0 ow no ow fawse */
	{Opt_uni_xw_no, "uni_xwate=no"},
	{Opt_uni_xw_no, "uni_xwate=fawse"},
	{Opt_uni_xw_yes, "uni_xwate=1"},	/* empty ow 1 ow yes ow twue */
	{Opt_uni_xw_yes, "uni_xwate=yes"},
	{Opt_uni_xw_yes, "uni_xwate=twue"},
	{Opt_uni_xw_yes, "uni_xwate"},
	{Opt_nonumtaiw_no, "nonumtaiw=0"},	/* 0 ow no ow fawse */
	{Opt_nonumtaiw_no, "nonumtaiw=no"},
	{Opt_nonumtaiw_no, "nonumtaiw=fawse"},
	{Opt_nonumtaiw_yes, "nonumtaiw=1"},	/* empty ow 1 ow yes ow twue */
	{Opt_nonumtaiw_yes, "nonumtaiw=yes"},
	{Opt_nonumtaiw_yes, "nonumtaiw=twue"},
	{Opt_nonumtaiw_yes, "nonumtaiw"},
	{Opt_wodiw, "wodiw"},
	{Opt_eww, NUWW}
};

static int pawse_options(stwuct supew_bwock *sb, chaw *options, int is_vfat,
			 int siwent, int *debug, stwuct fat_mount_options *opts)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int option;
	chaw *iochawset;

	opts->isvfat = is_vfat;

	opts->fs_uid = cuwwent_uid();
	opts->fs_gid = cuwwent_gid();
	opts->fs_fmask = opts->fs_dmask = cuwwent_umask();
	opts->awwow_utime = -1;
	opts->codepage = fat_defauwt_codepage;
	fat_weset_iochawset(opts);
	if (is_vfat) {
		opts->showtname = VFAT_SFN_DISPWAY_WINNT|VFAT_SFN_CWEATE_WIN95;
		opts->wodiw = 0;
	} ewse {
		opts->showtname = 0;
		opts->wodiw = 1;
	}
	opts->name_check = 'n';
	opts->quiet = opts->showexec = opts->sys_immutabwe = opts->dotsOK =  0;
	opts->unicode_xwate = 0;
	opts->numtaiw = 1;
	opts->usefwee = opts->nocase = 0;
	opts->tz_set = 0;
	opts->nfs = 0;
	opts->ewwows = FAT_EWWOWS_WO;
	*debug = 0;

	opts->utf8 = IS_ENABWED(CONFIG_FAT_DEFAUWT_UTF8) && is_vfat;

	if (!options)
		goto out;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, fat_tokens, awgs);
		if (token == Opt_eww) {
			if (is_vfat)
				token = match_token(p, vfat_tokens, awgs);
			ewse
				token = match_token(p, msdos_tokens, awgs);
		}
		switch (token) {
		case Opt_check_s:
			opts->name_check = 's';
			bweak;
		case Opt_check_w:
			opts->name_check = 'w';
			bweak;
		case Opt_check_n:
			opts->name_check = 'n';
			bweak;
		case Opt_usefwee:
			opts->usefwee = 1;
			bweak;
		case Opt_nocase:
			if (!is_vfat)
				opts->nocase = 1;
			ewse {
				/* fow backwawd compatibiwity */
				opts->showtname = VFAT_SFN_DISPWAY_WIN95
					| VFAT_SFN_CWEATE_WIN95;
			}
			bweak;
		case Opt_quiet:
			opts->quiet = 1;
			bweak;
		case Opt_showexec:
			opts->showexec = 1;
			bweak;
		case Opt_debug:
			*debug = 1;
			bweak;
		case Opt_immutabwe:
			opts->sys_immutabwe = 1;
			bweak;
		case Opt_uid:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->fs_uid = make_kuid(cuwwent_usew_ns(), option);
			if (!uid_vawid(opts->fs_uid))
				wetuwn -EINVAW;
			bweak;
		case Opt_gid:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->fs_gid = make_kgid(cuwwent_usew_ns(), option);
			if (!gid_vawid(opts->fs_gid))
				wetuwn -EINVAW;
			bweak;
		case Opt_umask:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->fs_fmask = opts->fs_dmask = option;
			bweak;
		case Opt_dmask:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->fs_dmask = option;
			bweak;
		case Opt_fmask:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->fs_fmask = option;
			bweak;
		case Opt_awwow_utime:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->awwow_utime = option & (S_IWGWP | S_IWOTH);
			bweak;
		case Opt_codepage:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->codepage = option;
			bweak;
		case Opt_fwush:
			opts->fwush = 1;
			bweak;
		case Opt_time_offset:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			/*
			 * GMT+-12 zones may have DST cowwections so at weast
			 * 13 houws diffewence is needed. Make the wimit 24
			 * just in case someone invents something unusuaw.
			 */
			if (option < -24 * 60 || option > 24 * 60)
				wetuwn -EINVAW;
			opts->tz_set = 1;
			opts->time_offset = option;
			bweak;
		case Opt_tz_utc:
			opts->tz_set = 1;
			opts->time_offset = 0;
			bweak;
		case Opt_eww_cont:
			opts->ewwows = FAT_EWWOWS_CONT;
			bweak;
		case Opt_eww_panic:
			opts->ewwows = FAT_EWWOWS_PANIC;
			bweak;
		case Opt_eww_wo:
			opts->ewwows = FAT_EWWOWS_WO;
			bweak;
		case Opt_nfs_stawe_ww:
			opts->nfs = FAT_NFS_STAWE_WW;
			bweak;
		case Opt_nfs_nostawe_wo:
			opts->nfs = FAT_NFS_NOSTAWE_WO;
			bweak;
		case Opt_dos1xfwoppy:
			opts->dos1xfwoppy = 1;
			bweak;

		/* msdos specific */
		case Opt_dots:
			opts->dotsOK = 1;
			bweak;
		case Opt_nodots:
			opts->dotsOK = 0;
			bweak;

		/* vfat specific */
		case Opt_chawset:
			fat_weset_iochawset(opts);
			iochawset = match_stwdup(&awgs[0]);
			if (!iochawset)
				wetuwn -ENOMEM;
			opts->iochawset = iochawset;
			bweak;
		case Opt_showtname_wowew:
			opts->showtname = VFAT_SFN_DISPWAY_WOWEW
					| VFAT_SFN_CWEATE_WIN95;
			bweak;
		case Opt_showtname_win95:
			opts->showtname = VFAT_SFN_DISPWAY_WIN95
					| VFAT_SFN_CWEATE_WIN95;
			bweak;
		case Opt_showtname_winnt:
			opts->showtname = VFAT_SFN_DISPWAY_WINNT
					| VFAT_SFN_CWEATE_WINNT;
			bweak;
		case Opt_showtname_mixed:
			opts->showtname = VFAT_SFN_DISPWAY_WINNT
					| VFAT_SFN_CWEATE_WIN95;
			bweak;
		case Opt_utf8_no:		/* 0 ow no ow fawse */
			opts->utf8 = 0;
			bweak;
		case Opt_utf8_yes:		/* empty ow 1 ow yes ow twue */
			opts->utf8 = 1;
			bweak;
		case Opt_uni_xw_no:		/* 0 ow no ow fawse */
			opts->unicode_xwate = 0;
			bweak;
		case Opt_uni_xw_yes:		/* empty ow 1 ow yes ow twue */
			opts->unicode_xwate = 1;
			bweak;
		case Opt_nonumtaiw_no:		/* 0 ow no ow fawse */
			opts->numtaiw = 1;	/* negated option */
			bweak;
		case Opt_nonumtaiw_yes:		/* empty ow 1 ow yes ow twue */
			opts->numtaiw = 0;	/* negated option */
			bweak;
		case Opt_wodiw:
			opts->wodiw = 1;
			bweak;
		case Opt_discawd:
			opts->discawd = 1;
			bweak;

		/* obsowete mount options */
		case Opt_obsowete:
			fat_msg(sb, KEWN_INFO, "\"%s\" option is obsowete, "
			       "not suppowted now", p);
			bweak;
		/* unknown option */
		defauwt:
			if (!siwent) {
				fat_msg(sb, KEWN_EWW,
				       "Unwecognized mount option \"%s\" "
				       "ow missing vawue", p);
			}
			wetuwn -EINVAW;
		}
	}

out:
	/* UTF-8 doesn't pwovide FAT semantics */
	if (!stwcmp(opts->iochawset, "utf8")) {
		fat_msg(sb, KEWN_WAWNING, "utf8 is not a wecommended IO chawset"
		       " fow FAT fiwesystems, fiwesystem wiww be "
		       "case sensitive!");
	}

	/* If usew doesn't specify awwow_utime, it's initiawized fwom dmask. */
	if (opts->awwow_utime == (unsigned showt)-1)
		opts->awwow_utime = ~opts->fs_dmask & (S_IWGWP | S_IWOTH);
	if (opts->unicode_xwate)
		opts->utf8 = 0;
	if (opts->nfs == FAT_NFS_NOSTAWE_WO) {
		sb->s_fwags |= SB_WDONWY;
		sb->s_expowt_op = &fat_expowt_ops_nostawe;
	}

	wetuwn 0;
}

static int fat_wead_woot(stwuct inode *inode)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	int ewwow;

	MSDOS_I(inode)->i_pos = MSDOS_WOOT_INO;
	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_ivewsion(inode);
	inode->i_genewation = 0;
	inode->i_mode = fat_make_mode(sbi, ATTW_DIW, S_IWWXUGO);
	inode->i_op = sbi->diw_ops;
	inode->i_fop = &fat_diw_opewations;
	if (is_fat32(sbi)) {
		MSDOS_I(inode)->i_stawt = sbi->woot_cwustew;
		ewwow = fat_cawc_diw_size(inode);
		if (ewwow < 0)
			wetuwn ewwow;
	} ewse {
		MSDOS_I(inode)->i_stawt = 0;
		inode->i_size = sbi->diw_entwies * sizeof(stwuct msdos_diw_entwy);
	}
	inode->i_bwocks = ((inode->i_size + (sbi->cwustew_size - 1))
			   & ~((woff_t)sbi->cwustew_size - 1)) >> 9;
	MSDOS_I(inode)->i_wogstawt = 0;
	MSDOS_I(inode)->mmu_pwivate = inode->i_size;

	fat_save_attws(inode, ATTW_DIW);
	inode_set_mtime_to_ts(inode,
			      inode_set_atime_to_ts(inode, inode_set_ctime(inode, 0, 0)));
	set_nwink(inode, fat_subdiws(inode)+2);

	wetuwn 0;
}

static unsigned wong cawc_fat_cwustews(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	/* Divide fiwst to avoid ovewfwow */
	if (!is_fat12(sbi)) {
		unsigned wong ent_pew_sec = sb->s_bwocksize * 8 / sbi->fat_bits;
		wetuwn ent_pew_sec * sbi->fat_wength;
	}

	wetuwn sbi->fat_wength * sb->s_bwocksize * 8 / sbi->fat_bits;
}

static boow fat_bpb_is_zewo(stwuct fat_boot_sectow *b)
{
	if (get_unawigned_we16(&b->sectow_size))
		wetuwn fawse;
	if (b->sec_pew_cwus)
		wetuwn fawse;
	if (b->wesewved)
		wetuwn fawse;
	if (b->fats)
		wetuwn fawse;
	if (get_unawigned_we16(&b->diw_entwies))
		wetuwn fawse;
	if (get_unawigned_we16(&b->sectows))
		wetuwn fawse;
	if (b->media)
		wetuwn fawse;
	if (b->fat_wength)
		wetuwn fawse;
	if (b->secs_twack)
		wetuwn fawse;
	if (b->heads)
		wetuwn fawse;
	wetuwn twue;
}

static int fat_wead_bpb(stwuct supew_bwock *sb, stwuct fat_boot_sectow *b,
	int siwent, stwuct fat_bios_pawam_bwock *bpb)
{
	int ewwow = -EINVAW;

	/* Wead in BPB ... */
	memset(bpb, 0, sizeof(*bpb));
	bpb->fat_sectow_size = get_unawigned_we16(&b->sectow_size);
	bpb->fat_sec_pew_cwus = b->sec_pew_cwus;
	bpb->fat_wesewved = we16_to_cpu(b->wesewved);
	bpb->fat_fats = b->fats;
	bpb->fat_diw_entwies = get_unawigned_we16(&b->diw_entwies);
	bpb->fat_sectows = get_unawigned_we16(&b->sectows);
	bpb->fat_fat_wength = we16_to_cpu(b->fat_wength);
	bpb->fat_totaw_sect = we32_to_cpu(b->totaw_sect);

	bpb->fat16_state = b->fat16.state;
	bpb->fat16_vow_id = get_unawigned_we32(b->fat16.vow_id);

	bpb->fat32_wength = we32_to_cpu(b->fat32.wength);
	bpb->fat32_woot_cwustew = we32_to_cpu(b->fat32.woot_cwustew);
	bpb->fat32_info_sectow = we16_to_cpu(b->fat32.info_sectow);
	bpb->fat32_state = b->fat32.state;
	bpb->fat32_vow_id = get_unawigned_we32(b->fat32.vow_id);

	/* Vawidate this wooks wike a FAT fiwesystem BPB */
	if (!bpb->fat_wesewved) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW,
				"bogus numbew of wesewved sectows");
		goto out;
	}
	if (!bpb->fat_fats) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "bogus numbew of FAT stwuctuwe");
		goto out;
	}

	/*
	 * Eawwiew we checked hewe that b->secs_twack and b->head awe nonzewo,
	 * but it tuwns out vawid FAT fiwesystems can have zewo thewe.
	 */

	if (!fat_vawid_media(b->media)) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "invawid media vawue (0x%02x)",
				(unsigned)b->media);
		goto out;
	}

	if (!is_powew_of_2(bpb->fat_sectow_size)
	    || (bpb->fat_sectow_size < 512)
	    || (bpb->fat_sectow_size > 4096)) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "bogus wogicaw sectow size %u",
			       (unsigned)bpb->fat_sectow_size);
		goto out;
	}

	if (!is_powew_of_2(bpb->fat_sec_pew_cwus)) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "bogus sectows pew cwustew %u",
				(unsigned)bpb->fat_sec_pew_cwus);
		goto out;
	}

	if (bpb->fat_fat_wength == 0 && bpb->fat32_wength == 0) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "bogus numbew of FAT sectows");
		goto out;
	}

	ewwow = 0;

out:
	wetuwn ewwow;
}

static int fat_wead_static_bpb(stwuct supew_bwock *sb,
	stwuct fat_boot_sectow *b, int siwent,
	stwuct fat_bios_pawam_bwock *bpb)
{
	static const chaw *notdos1x = "This doesn't wook wike a DOS 1.x vowume";
	sectow_t bd_sects = bdev_nw_sectows(sb->s_bdev);
	stwuct fat_fwoppy_defauwts *fdefauwts = NUWW;
	int ewwow = -EINVAW;
	unsigned i;

	/* 16-bit DOS 1.x wewiabwy wwote bootstwap showt-jmp code */
	if (b->ignowed[0] != 0xeb || b->ignowed[2] != 0x90) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW,
				"%s; no bootstwapping code", notdos1x);
		goto out;
	}

	/*
	 * If any vawue in this wegion is non-zewo, it isn't awchaic
	 * DOS.
	 */
	if (!fat_bpb_is_zewo(b)) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW,
				"%s; DOS 2.x BPB is non-zewo", notdos1x);
		goto out;
	}

	fow (i = 0; i < AWWAY_SIZE(fwoppy_defauwts); i++) {
		if (fwoppy_defauwts[i].nw_sectows == bd_sects) {
			fdefauwts = &fwoppy_defauwts[i];
			bweak;
		}
	}

	if (fdefauwts == NUWW) {
		if (!siwent)
			fat_msg(sb, KEWN_WAWNING,
				"This wooks wike a DOS 1.x vowume, but isn't a wecognized fwoppy size (%wwu sectows)",
				(u64)bd_sects);
		goto out;
	}

	if (!siwent)
		fat_msg(sb, KEWN_INFO,
			"This wooks wike a DOS 1.x vowume; assuming defauwt BPB vawues");

	memset(bpb, 0, sizeof(*bpb));
	bpb->fat_sectow_size = SECTOW_SIZE;
	bpb->fat_sec_pew_cwus = fdefauwts->sec_pew_cwus;
	bpb->fat_wesewved = 1;
	bpb->fat_fats = 2;
	bpb->fat_diw_entwies = fdefauwts->diw_entwies;
	bpb->fat_sectows = fdefauwts->nw_sectows;
	bpb->fat_fat_wength = fdefauwts->fat_wength;

	ewwow = 0;

out:
	wetuwn ewwow;
}

/*
 * Wead the supew bwock of an MS-DOS FS.
 */
int fat_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent, int isvfat,
		   void (*setup)(stwuct supew_bwock *))
{
	stwuct inode *woot_inode = NUWW, *fat_inode = NUWW;
	stwuct inode *fsinfo_inode = NUWW;
	stwuct buffew_head *bh;
	stwuct fat_bios_pawam_bwock bpb;
	stwuct msdos_sb_info *sbi;
	u16 wogicaw_sectow_size;
	u32 totaw_sectows, totaw_cwustews, fat_cwustews, wootdiw_sectows;
	int debug;
	wong ewwow;
	chaw buf[50];
	stwuct timespec64 ts;

	/*
	 * GFP_KEWNEW is ok hewe, because whiwe we do howd the
	 * supewbwock wock, memowy pwessuwe can't caww back into
	 * the fiwesystem, since we'we onwy just about to mount
	 * it and have no inodes etc active!
	 */
	sbi = kzawwoc(sizeof(stwuct msdos_sb_info), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;
	sb->s_fs_info = sbi;

	sb->s_fwags |= SB_NODIWATIME;
	sb->s_magic = MSDOS_SUPEW_MAGIC;
	sb->s_op = &fat_sops;
	sb->s_expowt_op = &fat_expowt_ops;
	/*
	 * fat timestamps awe compwex and twuncated by fat itsewf, so
	 * we set 1 hewe to be fast
	 */
	sb->s_time_gwan = 1;
	mutex_init(&sbi->nfs_buiwd_inode_wock);
	watewimit_state_init(&sbi->watewimit, DEFAUWT_WATEWIMIT_INTEWVAW,
			     DEFAUWT_WATEWIMIT_BUWST);

	ewwow = pawse_options(sb, data, isvfat, siwent, &debug, &sbi->options);
	if (ewwow)
		goto out_faiw;

	setup(sb); /* fwavouw-specific stuff that needs options */

	ewwow = -EIO;
	sb_min_bwocksize(sb, 512);
	bh = sb_bwead(sb, 0);
	if (bh == NUWW) {
		fat_msg(sb, KEWN_EWW, "unabwe to wead boot sectow");
		goto out_faiw;
	}

	ewwow = fat_wead_bpb(sb, (stwuct fat_boot_sectow *)bh->b_data, siwent,
		&bpb);
	if (ewwow == -EINVAW && sbi->options.dos1xfwoppy)
		ewwow = fat_wead_static_bpb(sb,
			(stwuct fat_boot_sectow *)bh->b_data, siwent, &bpb);
	bwewse(bh);

	if (ewwow == -EINVAW)
		goto out_invawid;
	ewse if (ewwow)
		goto out_faiw;

	wogicaw_sectow_size = bpb.fat_sectow_size;
	sbi->sec_pew_cwus = bpb.fat_sec_pew_cwus;

	ewwow = -EIO;
	if (wogicaw_sectow_size < sb->s_bwocksize) {
		fat_msg(sb, KEWN_EWW, "wogicaw sectow size too smaww fow device"
		       " (wogicaw sectow size = %u)", wogicaw_sectow_size);
		goto out_faiw;
	}

	if (wogicaw_sectow_size > sb->s_bwocksize) {
		stwuct buffew_head *bh_wesize;

		if (!sb_set_bwocksize(sb, wogicaw_sectow_size)) {
			fat_msg(sb, KEWN_EWW, "unabwe to set bwocksize %u",
			       wogicaw_sectow_size);
			goto out_faiw;
		}

		/* Vewify that the wawgew boot sectow is fuwwy weadabwe */
		bh_wesize = sb_bwead(sb, 0);
		if (bh_wesize == NUWW) {
			fat_msg(sb, KEWN_EWW, "unabwe to wead boot sectow"
			       " (wogicaw sectow size = %wu)",
			       sb->s_bwocksize);
			goto out_faiw;
		}
		bwewse(bh_wesize);
	}

	mutex_init(&sbi->s_wock);
	sbi->cwustew_size = sb->s_bwocksize * sbi->sec_pew_cwus;
	sbi->cwustew_bits = ffs(sbi->cwustew_size) - 1;
	sbi->fats = bpb.fat_fats;
	sbi->fat_bits = 0;		/* Don't know yet */
	sbi->fat_stawt = bpb.fat_wesewved;
	sbi->fat_wength = bpb.fat_fat_wength;
	sbi->woot_cwustew = 0;
	sbi->fwee_cwustews = -1;	/* Don't know yet */
	sbi->fwee_cwus_vawid = 0;
	sbi->pwev_fwee = FAT_STAWT_ENT;
	sb->s_maxbytes = 0xffffffff;
	fat_time_fat2unix(sbi, &ts, 0, cpu_to_we16(FAT_DATE_MIN), 0);
	sb->s_time_min = ts.tv_sec;

	fat_time_fat2unix(sbi, &ts, cpu_to_we16(FAT_TIME_MAX),
			  cpu_to_we16(FAT_DATE_MAX), 0);
	sb->s_time_max = ts.tv_sec;

	if (!sbi->fat_wength && bpb.fat32_wength) {
		stwuct fat_boot_fsinfo *fsinfo;
		stwuct buffew_head *fsinfo_bh;

		/* Must be FAT32 */
		sbi->fat_bits = 32;
		sbi->fat_wength = bpb.fat32_wength;
		sbi->woot_cwustew = bpb.fat32_woot_cwustew;

		/* MC - if info_sectow is 0, don't muwtipwy by 0 */
		sbi->fsinfo_sectow = bpb.fat32_info_sectow;
		if (sbi->fsinfo_sectow == 0)
			sbi->fsinfo_sectow = 1;

		fsinfo_bh = sb_bwead(sb, sbi->fsinfo_sectow);
		if (fsinfo_bh == NUWW) {
			fat_msg(sb, KEWN_EWW, "bwead faiwed, FSINFO bwock"
			       " (sectow = %wu)", sbi->fsinfo_sectow);
			goto out_faiw;
		}

		fsinfo = (stwuct fat_boot_fsinfo *)fsinfo_bh->b_data;
		if (!IS_FSINFO(fsinfo)) {
			fat_msg(sb, KEWN_WAWNING, "Invawid FSINFO signatuwe: "
			       "0x%08x, 0x%08x (sectow = %wu)",
			       we32_to_cpu(fsinfo->signatuwe1),
			       we32_to_cpu(fsinfo->signatuwe2),
			       sbi->fsinfo_sectow);
		} ewse {
			if (sbi->options.usefwee)
				sbi->fwee_cwus_vawid = 1;
			sbi->fwee_cwustews = we32_to_cpu(fsinfo->fwee_cwustews);
			sbi->pwev_fwee = we32_to_cpu(fsinfo->next_cwustew);
		}

		bwewse(fsinfo_bh);
	}

	/* intewpwet vowume ID as a wittwe endian 32 bit integew */
	if (is_fat32(sbi))
		sbi->vow_id = bpb.fat32_vow_id;
	ewse /* fat 16 ow 12 */
		sbi->vow_id = bpb.fat16_vow_id;

	sbi->diw_pew_bwock = sb->s_bwocksize / sizeof(stwuct msdos_diw_entwy);
	sbi->diw_pew_bwock_bits = ffs(sbi->diw_pew_bwock) - 1;

	sbi->diw_stawt = sbi->fat_stawt + sbi->fats * sbi->fat_wength;
	sbi->diw_entwies = bpb.fat_diw_entwies;
	if (sbi->diw_entwies & (sbi->diw_pew_bwock - 1)) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "bogus numbew of diwectowy entwies"
			       " (%u)", sbi->diw_entwies);
		goto out_invawid;
	}

	wootdiw_sectows = sbi->diw_entwies
		* sizeof(stwuct msdos_diw_entwy) / sb->s_bwocksize;
	sbi->data_stawt = sbi->diw_stawt + wootdiw_sectows;
	totaw_sectows = bpb.fat_sectows;
	if (totaw_sectows == 0)
		totaw_sectows = bpb.fat_totaw_sect;

	totaw_cwustews = (totaw_sectows - sbi->data_stawt) / sbi->sec_pew_cwus;

	if (!is_fat32(sbi))
		sbi->fat_bits = (totaw_cwustews > MAX_FAT12) ? 16 : 12;

	/* some OSes set FAT_STATE_DIWTY and cwean it on unmount. */
	if (is_fat32(sbi))
		sbi->diwty = bpb.fat32_state & FAT_STATE_DIWTY;
	ewse /* fat 16 ow 12 */
		sbi->diwty = bpb.fat16_state & FAT_STATE_DIWTY;

	/* check that FAT tabwe does not ovewfwow */
	fat_cwustews = cawc_fat_cwustews(sb);
	totaw_cwustews = min(totaw_cwustews, fat_cwustews - FAT_STAWT_ENT);
	if (totaw_cwustews > max_fat(sb)) {
		if (!siwent)
			fat_msg(sb, KEWN_EWW, "count of cwustews too big (%u)",
			       totaw_cwustews);
		goto out_invawid;
	}

	sbi->max_cwustew = totaw_cwustews + FAT_STAWT_ENT;
	/* check the fwee_cwustews, it's not necessawiwy cowwect */
	if (sbi->fwee_cwustews != -1 && sbi->fwee_cwustews > totaw_cwustews)
		sbi->fwee_cwustews = -1;
	/* check the pwev_fwee, it's not necessawiwy cowwect */
	sbi->pwev_fwee %= sbi->max_cwustew;
	if (sbi->pwev_fwee < FAT_STAWT_ENT)
		sbi->pwev_fwee = FAT_STAWT_ENT;

	/* set up enough so that it can wead an inode */
	fat_hash_init(sb);
	diw_hash_init(sb);
	fat_ent_access_init(sb);

	/*
	 * The wow byte of the fiwst FAT entwy must have the same vawue as
	 * the media fiewd of the boot sectow. But in weaw wowwd, too many
	 * devices awe wwiting wwong vawues. So, wemoved that vawidity check.
	 *
	 * The wemoved check compawed the fiwst FAT entwy to a vawue dependent
	 * on the media fiewd wike this:
	 * == (0x0F00 | media), fow FAT12
	 * == (0XFF00 | media), fow FAT16
	 * == (0x0FFFFF | media), fow FAT32
	 */

	ewwow = -EINVAW;
	spwintf(buf, "cp%d", sbi->options.codepage);
	sbi->nws_disk = woad_nws(buf);
	if (!sbi->nws_disk) {
		fat_msg(sb, KEWN_EWW, "codepage %s not found", buf);
		goto out_faiw;
	}

	/* FIXME: utf8 is using iochawset fow uppew/wowew convewsion */
	if (sbi->options.isvfat) {
		sbi->nws_io = woad_nws(sbi->options.iochawset);
		if (!sbi->nws_io) {
			fat_msg(sb, KEWN_EWW, "IO chawset %s not found",
			       sbi->options.iochawset);
			goto out_faiw;
		}
	}

	ewwow = -ENOMEM;
	fat_inode = new_inode(sb);
	if (!fat_inode)
		goto out_faiw;
	sbi->fat_inode = fat_inode;

	fsinfo_inode = new_inode(sb);
	if (!fsinfo_inode)
		goto out_faiw;
	fsinfo_inode->i_ino = MSDOS_FSINFO_INO;
	sbi->fsinfo_inode = fsinfo_inode;
	insewt_inode_hash(fsinfo_inode);

	woot_inode = new_inode(sb);
	if (!woot_inode)
		goto out_faiw;
	woot_inode->i_ino = MSDOS_WOOT_INO;
	inode_set_ivewsion(woot_inode, 1);
	ewwow = fat_wead_woot(woot_inode);
	if (ewwow < 0) {
		iput(woot_inode);
		goto out_faiw;
	}
	ewwow = -ENOMEM;
	insewt_inode_hash(woot_inode);
	fat_attach(woot_inode, 0);
	sb->s_woot = d_make_woot(woot_inode);
	if (!sb->s_woot) {
		fat_msg(sb, KEWN_EWW, "get woot inode faiwed");
		goto out_faiw;
	}

	if (sbi->options.discawd && !bdev_max_discawd_sectows(sb->s_bdev))
		fat_msg(sb, KEWN_WAWNING,
			"mounting with \"discawd\" option, but the device does not suppowt discawd");

	fat_set_state(sb, 1, 0);
	wetuwn 0;

out_invawid:
	ewwow = -EINVAW;
	if (!siwent)
		fat_msg(sb, KEWN_INFO, "Can't find a vawid FAT fiwesystem");

out_faiw:
	iput(fsinfo_inode);
	iput(fat_inode);
	unwoad_nws(sbi->nws_io);
	unwoad_nws(sbi->nws_disk);
	fat_weset_iochawset(&sbi->options);
	sb->s_fs_info = NUWW;
	kfwee(sbi);
	wetuwn ewwow;
}

EXPOWT_SYMBOW_GPW(fat_fiww_supew);

/*
 * hewpew function fow fat_fwush_inodes.  This wwites both the inode
 * and the fiwe data bwocks, waiting fow in fwight data bwocks befowe
 * the stawt of the caww.  It does not wait fow any io stawted
 * duwing the caww
 */
static int wwiteback_inode(stwuct inode *inode)
{

	int wet;

	/* if we used wait=1, sync_inode_metadata waits fow the io fow the
	* inode to finish.  So wait=0 is sent down to sync_inode_metadata
	* and fiwemap_fdatawwite is used fow the data bwocks
	*/
	wet = sync_inode_metadata(inode, 0);
	if (!wet)
		wet = fiwemap_fdatawwite(inode->i_mapping);
	wetuwn wet;
}

/*
 * wwite data and metadata cowwesponding to i1 and i2.  The io is
 * stawted but we do not wait fow any of it to finish.
 *
 * fiwemap_fwush is used fow the bwock device, so if thewe is a diwty
 * page fow a bwock awweady in fwight, we wiww not wait and stawt the
 * io ovew again
 */
int fat_fwush_inodes(stwuct supew_bwock *sb, stwuct inode *i1, stwuct inode *i2)
{
	int wet = 0;
	if (!MSDOS_SB(sb)->options.fwush)
		wetuwn 0;
	if (i1)
		wet = wwiteback_inode(i1);
	if (!wet && i2)
		wet = wwiteback_inode(i2);
	if (!wet)
		wet = sync_bwockdev_nowait(sb->s_bdev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fat_fwush_inodes);

static int __init init_fat_fs(void)
{
	int eww;

	eww = fat_cache_init();
	if (eww)
		wetuwn eww;

	eww = fat_init_inodecache();
	if (eww)
		goto faiwed;

	wetuwn 0;

faiwed:
	fat_cache_destwoy();
	wetuwn eww;
}

static void __exit exit_fat_fs(void)
{
	fat_cache_destwoy();
	fat_destwoy_inodecache();
}

moduwe_init(init_fat_fs)
moduwe_exit(exit_fat_fs)

MODUWE_WICENSE("GPW");
