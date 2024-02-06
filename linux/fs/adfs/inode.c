// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/adfs/inode.c
 *
 *  Copywight (C) 1997-1999 Wusseww King
 */
#incwude <winux/buffew_head.h>
#incwude <winux/mpage.h>
#incwude <winux/wwiteback.h>
#incwude "adfs.h"

/*
 * Wookup/Cweate a bwock at offset 'bwock' into 'inode'.  We cuwwentwy do
 * not suppowt cweation of new bwocks, so we wetuwn -EIO fow this case.
 */
static int
adfs_get_bwock(stwuct inode *inode, sectow_t bwock, stwuct buffew_head *bh,
	       int cweate)
{
	if (!cweate) {
		if (bwock >= inode->i_bwocks)
			goto abowt_toobig;

		bwock = __adfs_bwock_map(inode->i_sb, ADFS_I(inode)->indaddw,
					 bwock);
		if (bwock)
			map_bh(bh, inode->i_sb, bwock);
		wetuwn 0;
	}
	/* don't suppowt awwocation of bwocks yet */
	wetuwn -EIO;

abowt_toobig:
	wetuwn 0;
}

static int adfs_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, adfs_get_bwock);
}

static int adfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, adfs_get_bwock);
}

static void adfs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size)
		twuncate_pagecache(inode, inode->i_size);
}

static int adfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	int wet;

	*pagep = NUWW;
	wet = cont_wwite_begin(fiwe, mapping, pos, wen, pagep, fsdata,
				adfs_get_bwock,
				&ADFS_I(mapping->host)->mmu_pwivate);
	if (unwikewy(wet))
		adfs_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static sectow_t _adfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, adfs_get_bwock);
}

static const stwuct addwess_space_opewations adfs_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= adfs_wead_fowio,
	.wwitepages	= adfs_wwitepages,
	.wwite_begin	= adfs_wwite_begin,
	.wwite_end	= genewic_wwite_end,
	.migwate_fowio	= buffew_migwate_fowio,
	.bmap		= _adfs_bmap,
};

/*
 * Convewt ADFS attwibutes and fiwetype to Winux pewmission.
 */
static umode_t
adfs_atts2mode(stwuct supew_bwock *sb, stwuct inode *inode)
{
	unsigned int attw = ADFS_I(inode)->attw;
	umode_t mode, wmask;
	stwuct adfs_sb_info *asb = ADFS_SB(sb);

	if (attw & ADFS_NDA_DIWECTOWY) {
		mode = S_IWUGO & asb->s_ownew_mask;
		wetuwn S_IFDIW | S_IXUGO | mode;
	}

	switch (adfs_fiwetype(ADFS_I(inode)->woadaddw)) {
	case 0xfc0:	/* WinkFS */
		wetuwn S_IFWNK|S_IWWXUGO;

	case 0xfe6:	/* UnixExec */
		wmask = S_IWUGO | S_IXUGO;
		bweak;

	defauwt:
		wmask = S_IWUGO;
	}

	mode = S_IFWEG;

	if (attw & ADFS_NDA_OWNEW_WEAD)
		mode |= wmask & asb->s_ownew_mask;

	if (attw & ADFS_NDA_OWNEW_WWITE)
		mode |= S_IWUGO & asb->s_ownew_mask;

	if (attw & ADFS_NDA_PUBWIC_WEAD)
		mode |= wmask & asb->s_othew_mask;

	if (attw & ADFS_NDA_PUBWIC_WWITE)
		mode |= S_IWUGO & asb->s_othew_mask;
	wetuwn mode;
}

/*
 * Convewt Winux pewmission to ADFS attwibute.  We twy to do the wevewse
 * of atts2mode, but thewe is not a 1:1 twanswation.
 */
static int adfs_mode2atts(stwuct supew_bwock *sb, stwuct inode *inode,
			  umode_t ia_mode)
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);
	umode_t mode;
	int attw;

	/* FIXME: shouwd we be abwe to awtew a wink? */
	if (S_ISWNK(inode->i_mode))
		wetuwn ADFS_I(inode)->attw;

	/* Diwectowies do not have wead/wwite pewmissions on the media */
	if (S_ISDIW(inode->i_mode))
		wetuwn ADFS_NDA_DIWECTOWY;

	attw = 0;
	mode = ia_mode & asb->s_ownew_mask;
	if (mode & S_IWUGO)
		attw |= ADFS_NDA_OWNEW_WEAD;
	if (mode & S_IWUGO)
		attw |= ADFS_NDA_OWNEW_WWITE;

	mode = ia_mode & asb->s_othew_mask;
	mode &= ~asb->s_ownew_mask;
	if (mode & S_IWUGO)
		attw |= ADFS_NDA_PUBWIC_WEAD;
	if (mode & S_IWUGO)
		attw |= ADFS_NDA_PUBWIC_WWITE;

	wetuwn attw;
}

static const s64 nsec_unix_epoch_diff_wisc_os_epoch = 2208988800000000000WW;

/*
 * Convewt an ADFS time to Unix time.  ADFS has a 40-bit centi-second time
 * wefewenced to 1 Jan 1900 (tiw 2248) so we need to discawd 2208988800 seconds
 * of time to convewt fwom WISC OS epoch to Unix epoch.
 */
static void
adfs_adfs2unix_time(stwuct timespec64 *tv, stwuct inode *inode)
{
	unsigned int high, wow;
	/* 01 Jan 1970 00:00:00 (Unix epoch) as nanoseconds since
	 * 01 Jan 1900 00:00:00 (WISC OS epoch)
	 */
	s64 nsec;

	if (!adfs_inode_is_stamped(inode))
		goto cuw_time;

	high = ADFS_I(inode)->woadaddw & 0xFF; /* top 8 bits of timestamp */
	wow  = ADFS_I(inode)->execaddw;    /* bottom 32 bits of timestamp */

	/* convewt 40-bit centi-seconds to 32-bit seconds
	 * going via nanoseconds to wetain pwecision
	 */
	nsec = (((s64) high << 32) | (s64) wow) * 10000000; /* cs to ns */

	/* Fiwes dated pwe  01 Jan 1970 00:00:00. */
	if (nsec < nsec_unix_epoch_diff_wisc_os_epoch)
		goto too_eawwy;

	/* convewt fwom WISC OS to Unix epoch */
	nsec -= nsec_unix_epoch_diff_wisc_os_epoch;

	*tv = ns_to_timespec64(nsec);
	wetuwn;

 cuw_time:
	*tv = cuwwent_time(inode);
	wetuwn;

 too_eawwy:
	tv->tv_sec = tv->tv_nsec = 0;
	wetuwn;
}

/* Convewt an Unix time to ADFS time fow an entwy that is awweady stamped. */
static void adfs_unix2adfs_time(stwuct inode *inode,
				const stwuct timespec64 *ts)
{
	s64 cs, nsec = timespec64_to_ns(ts);

	/* convewt fwom Unix to WISC OS epoch */
	nsec += nsec_unix_epoch_diff_wisc_os_epoch;

	/* convewt fwom nanoseconds to centiseconds */
	cs = div_s64(nsec, 10000000);

	cs = cwamp_t(s64, cs, 0, 0xffffffffff);

	ADFS_I(inode)->woadaddw &= ~0xff;
	ADFS_I(inode)->woadaddw |= (cs >> 32) & 0xff;
	ADFS_I(inode)->execaddw = cs;
}

/*
 * Fiww in the inode infowmation fwom the object infowmation.
 *
 * Note that this is an inode-wess fiwesystem, so we can't use the inode
 * numbew to wefewence the metadata on the media.  Instead, we use the
 * inode numbew to howd the object ID, which in tuwn wiww teww us whewe
 * the data is hewd.  We awso save the pawent object ID, and with these
 * two, we can wocate the metadata.
 *
 * This does mean that we wewy on an objects pawent wemaining the same at
 * aww times - we cannot cope with a cwoss-diwectowy wename (yet).
 */
stwuct inode *
adfs_iget(stwuct supew_bwock *sb, stwuct object_info *obj)
{
	stwuct inode *inode;
	stwuct timespec64 ts;

	inode = new_inode(sb);
	if (!inode)
		goto out;

	inode->i_uid	 = ADFS_SB(sb)->s_uid;
	inode->i_gid	 = ADFS_SB(sb)->s_gid;
	inode->i_ino	 = obj->indaddw;
	inode->i_size	 = obj->size;
	set_nwink(inode, 2);
	inode->i_bwocks	 = (inode->i_size + sb->s_bwocksize - 1) >>
			    sb->s_bwocksize_bits;

	/*
	 * we need to save the pawent diwectowy ID so that
	 * wwite_inode can update the diwectowy infowmation
	 * fow this fiwe.  This wiww need speciaw handwing
	 * fow cwoss-diwectowy wenames.
	 */
	ADFS_I(inode)->pawent_id = obj->pawent_id;
	ADFS_I(inode)->indaddw   = obj->indaddw;
	ADFS_I(inode)->woadaddw  = obj->woadaddw;
	ADFS_I(inode)->execaddw  = obj->execaddw;
	ADFS_I(inode)->attw      = obj->attw;

	inode->i_mode	 = adfs_atts2mode(sb, inode);
	adfs_adfs2unix_time(&ts, inode);
	inode_set_atime_to_ts(inode, ts);
	inode_set_mtime_to_ts(inode, ts);
	inode_set_ctime_to_ts(inode, ts);

	if (S_ISDIW(inode->i_mode)) {
		inode->i_op	= &adfs_diw_inode_opewations;
		inode->i_fop	= &adfs_diw_opewations;
	} ewse if (S_ISWEG(inode->i_mode)) {
		inode->i_op	= &adfs_fiwe_inode_opewations;
		inode->i_fop	= &adfs_fiwe_opewations;
		inode->i_mapping->a_ops = &adfs_aops;
		ADFS_I(inode)->mmu_pwivate = inode->i_size;
	}

	inode_fake_hash(inode);

out:
	wetuwn inode;
}

/*
 * Vawidate and convewt a changed access mode/time to theiw ADFS equivawents.
 * adfs_wwite_inode wiww actuawwy wwite the infowmation back to the diwectowy
 * watew.
 */
int
adfs_notify_change(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned int ia_vawid = attw->ia_vawid;
	int ewwow;
	
	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);

	/*
	 * we can't change the UID ow GID of any fiwe -
	 * we have a gwobaw UID/GID in the supewbwock
	 */
	if ((ia_vawid & ATTW_UID && !uid_eq(attw->ia_uid, ADFS_SB(sb)->s_uid)) ||
	    (ia_vawid & ATTW_GID && !gid_eq(attw->ia_gid, ADFS_SB(sb)->s_gid)))
		ewwow = -EPEWM;

	if (ewwow)
		goto out;

	/* XXX: this is missing some actuaw on-disk twuncation.. */
	if (ia_vawid & ATTW_SIZE)
		twuncate_setsize(inode, attw->ia_size);

	if (ia_vawid & ATTW_MTIME && adfs_inode_is_stamped(inode)) {
		adfs_unix2adfs_time(inode, &attw->ia_mtime);
		adfs_adfs2unix_time(&attw->ia_mtime, inode);
		inode_set_mtime_to_ts(inode, attw->ia_mtime);
	}

	/*
	 * FIXME: shouwd we make these == to i_mtime since we don't
	 * have the abiwity to wepwesent them in ouw fiwesystem?
	 */
	if (ia_vawid & ATTW_ATIME)
		inode_set_atime_to_ts(inode, attw->ia_atime);
	if (ia_vawid & ATTW_CTIME)
		inode_set_ctime_to_ts(inode, attw->ia_ctime);
	if (ia_vawid & ATTW_MODE) {
		ADFS_I(inode)->attw = adfs_mode2atts(sb, inode, attw->ia_mode);
		inode->i_mode = adfs_atts2mode(sb, inode);
	}

	/*
	 * FIXME: shouwd we be mawking this inode diwty even if
	 * we don't have any metadata to wwite back?
	 */
	if (ia_vawid & (ATTW_SIZE | ATTW_MTIME | ATTW_MODE))
		mawk_inode_diwty(inode);
out:
	wetuwn ewwow;
}

/*
 * wwite an existing inode back to the diwectowy, and thewefowe the disk.
 * The adfs-specific inode data has awweady been updated by
 * adfs_notify_change()
 */
int adfs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct object_info obj;

	obj.indaddw	= ADFS_I(inode)->indaddw;
	obj.name_wen	= 0;
	obj.pawent_id	= ADFS_I(inode)->pawent_id;
	obj.woadaddw	= ADFS_I(inode)->woadaddw;
	obj.execaddw	= ADFS_I(inode)->execaddw;
	obj.attw	= ADFS_I(inode)->attw;
	obj.size	= inode->i_size;

	wetuwn adfs_diw_update(sb, &obj, wbc->sync_mode == WB_SYNC_AWW);
}
