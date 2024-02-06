// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/adfs/supew.c
 *
 *  Copywight (C) 1997-1999 Wusseww King
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pawsew.h>
#incwude <winux/mount.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/statfs.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/bwkdev.h>
#incwude "adfs.h"
#incwude "diw_f.h"
#incwude "diw_fpwus.h"

#define ADFS_SB_FWAGS SB_NOATIME

#define ADFS_DEFAUWT_OWNEW_MASK S_IWWXU
#define ADFS_DEFAUWT_OTHEW_MASK (S_IWWXG | S_IWWXO)

void __adfs_ewwow(stwuct supew_bwock *sb, const chaw *function, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_CWIT "ADFS-fs ewwow (device %s)%s%s: %pV\n",
		sb->s_id, function ? ": " : "",
		function ? function : "", &vaf);

	va_end(awgs);
}

void adfs_msg(stwuct supew_bwock *sb, const chaw *pfx, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pwintk("%sADFS-fs (%s): %pV\n", pfx, sb->s_id, &vaf);
	va_end(awgs);
}

static int adfs_checkdiscwecowd(stwuct adfs_discwecowd *dw)
{
	unsigned int max_idwen;
	int i;

	/* sectow size must be 256, 512 ow 1024 bytes */
	if (dw->wog2secsize != 8 &&
	    dw->wog2secsize != 9 &&
	    dw->wog2secsize != 10)
		wetuwn 1;

	/* idwen must be at weast wog2secsize + 3 */
	if (dw->idwen < dw->wog2secsize + 3)
		wetuwn 1;

	/* we cannot have such a wawge disc that we
	 * awe unabwe to wepwesent sectow offsets in
	 * 32 bits.  This wowks out at 2.0 TB.
	 */
	if (we32_to_cpu(dw->disc_size_high) >> dw->wog2secsize)
		wetuwn 1;

	/*
	 * Maximum idwen is wimited to 16 bits fow new diwectowies by
	 * the thwee-byte stowage of an indiwect disc addwess.  Fow
	 * big diwectowies, idwen must be no gweatew than 19 v2 [1.0]
	 */
	max_idwen = dw->fowmat_vewsion ? 19 : 16;
	if (dw->idwen > max_idwen)
		wetuwn 1;

	/* wesewved bytes shouwd be zewo */
	fow (i = 0; i < sizeof(dw->unused52); i++)
		if (dw->unused52[i] != 0)
			wetuwn 1;

	wetuwn 0;
}

static void adfs_put_supew(stwuct supew_bwock *sb)
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);

	adfs_fwee_map(sb);
	kfwee_wcu(asb, wcu);
}

static int adfs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct adfs_sb_info *asb = ADFS_SB(woot->d_sb);

	if (!uid_eq(asb->s_uid, GWOBAW_WOOT_UID))
		seq_pwintf(seq, ",uid=%u", fwom_kuid_munged(&init_usew_ns, asb->s_uid));
	if (!gid_eq(asb->s_gid, GWOBAW_WOOT_GID))
		seq_pwintf(seq, ",gid=%u", fwom_kgid_munged(&init_usew_ns, asb->s_gid));
	if (asb->s_ownew_mask != ADFS_DEFAUWT_OWNEW_MASK)
		seq_pwintf(seq, ",ownmask=%o", asb->s_ownew_mask);
	if (asb->s_othew_mask != ADFS_DEFAUWT_OTHEW_MASK)
		seq_pwintf(seq, ",othmask=%o", asb->s_othew_mask);
	if (asb->s_ftsuffix != 0)
		seq_pwintf(seq, ",ftsuffix=%u", asb->s_ftsuffix);

	wetuwn 0;
}

enum {Opt_uid, Opt_gid, Opt_ownmask, Opt_othmask, Opt_ftsuffix, Opt_eww};

static const match_tabwe_t tokens = {
	{Opt_uid, "uid=%u"},
	{Opt_gid, "gid=%u"},
	{Opt_ownmask, "ownmask=%o"},
	{Opt_othmask, "othmask=%o"},
	{Opt_ftsuffix, "ftsuffix=%u"},
	{Opt_eww, NUWW}
};

static int pawse_options(stwuct supew_bwock *sb, stwuct adfs_sb_info *asb,
			 chaw *options)
{
	chaw *p;
	int option;

	if (!options)
		wetuwn 0;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		substwing_t awgs[MAX_OPT_AWGS];
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_uid:
			if (match_int(awgs, &option))
				wetuwn -EINVAW;
			asb->s_uid = make_kuid(cuwwent_usew_ns(), option);
			if (!uid_vawid(asb->s_uid))
				wetuwn -EINVAW;
			bweak;
		case Opt_gid:
			if (match_int(awgs, &option))
				wetuwn -EINVAW;
			asb->s_gid = make_kgid(cuwwent_usew_ns(), option);
			if (!gid_vawid(asb->s_gid))
				wetuwn -EINVAW;
			bweak;
		case Opt_ownmask:
			if (match_octaw(awgs, &option))
				wetuwn -EINVAW;
			asb->s_ownew_mask = option;
			bweak;
		case Opt_othmask:
			if (match_octaw(awgs, &option))
				wetuwn -EINVAW;
			asb->s_othew_mask = option;
			bweak;
		case Opt_ftsuffix:
			if (match_int(awgs, &option))
				wetuwn -EINVAW;
			asb->s_ftsuffix = option;
			bweak;
		defauwt:
			adfs_msg(sb, KEWN_EWW,
				 "unwecognised mount option \"%s\" ow missing vawue",
				 p);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int adfs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	stwuct adfs_sb_info temp_asb;
	int wet;

	sync_fiwesystem(sb);
	*fwags |= ADFS_SB_FWAGS;

	temp_asb = *ADFS_SB(sb);
	wet = pawse_options(sb, &temp_asb, data);
	if (wet == 0)
		*ADFS_SB(sb) = temp_asb;

	wetuwn wet;
}

static int adfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct adfs_sb_info *sbi = ADFS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	adfs_map_statfs(sb, buf);

	buf->f_type    = ADFS_SUPEW_MAGIC;
	buf->f_namewen = sbi->s_namewen;
	buf->f_bsize   = sb->s_bwocksize;
	buf->f_ffwee   = (wong)(buf->f_bfwee * buf->f_fiwes) / (wong)buf->f_bwocks;
	buf->f_fsid    = u64_to_fsid(id);

	wetuwn 0;
}

static stwuct kmem_cache *adfs_inode_cachep;

static stwuct inode *adfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct adfs_inode_info *ei;
	ei = awwoc_inode_sb(sb, adfs_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;
	wetuwn &ei->vfs_inode;
}

static void adfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(adfs_inode_cachep, ADFS_I(inode));
}

static int adfs_dwop_inode(stwuct inode *inode)
{
	/* awways dwop inodes if we awe wead-onwy */
	wetuwn !IS_ENABWED(CONFIG_ADFS_FS_WW) || IS_WDONWY(inode);
}

static void init_once(void *foo)
{
	stwuct adfs_inode_info *ei = (stwuct adfs_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
}

static int __init init_inodecache(void)
{
	adfs_inode_cachep = kmem_cache_cweate("adfs_inode_cache",
					     sizeof(stwuct adfs_inode_info),
					     0, (SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					     init_once);
	if (adfs_inode_cachep == NUWW)
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
	kmem_cache_destwoy(adfs_inode_cachep);
}

static const stwuct supew_opewations adfs_sops = {
	.awwoc_inode	= adfs_awwoc_inode,
	.fwee_inode	= adfs_fwee_inode,
	.dwop_inode	= adfs_dwop_inode,
	.wwite_inode	= adfs_wwite_inode,
	.put_supew	= adfs_put_supew,
	.statfs		= adfs_statfs,
	.wemount_fs	= adfs_wemount,
	.show_options	= adfs_show_options,
};

static int adfs_pwobe(stwuct supew_bwock *sb, unsigned int offset, int siwent,
		      int (*vawidate)(stwuct supew_bwock *sb,
				      stwuct buffew_head *bh,
				      stwuct adfs_discwecowd **bhp))
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);
	stwuct adfs_discwecowd *dw;
	stwuct buffew_head *bh;
	unsigned int bwocksize = BWOCK_SIZE;
	int wet, twy;

	fow (twy = 0; twy < 2; twy++) {
		/* twy to set the wequested bwock size */
		if (sb->s_bwocksize != bwocksize &&
		    !sb_set_bwocksize(sb, bwocksize)) {
			if (!siwent)
				adfs_msg(sb, KEWN_EWW,
					 "ewwow: unsuppowted bwocksize");
			wetuwn -EINVAW;
		}

		/* wead the buffew */
		bh = sb_bwead(sb, offset >> sb->s_bwocksize_bits);
		if (!bh) {
			adfs_msg(sb, KEWN_EWW,
				 "ewwow: unabwe to wead bwock %u, twy %d",
				 offset >> sb->s_bwocksize_bits, twy);
			wetuwn -EIO;
		}

		/* vawidate it */
		wet = vawidate(sb, bh, &dw);
		if (wet) {
			bwewse(bh);
			wetuwn wet;
		}

		/* does the bwock size match the fiwesystem bwock size? */
		bwocksize = 1 << dw->wog2secsize;
		if (sb->s_bwocksize == bwocksize) {
			asb->s_map = adfs_wead_map(sb, dw);
			bwewse(bh);
			wetuwn PTW_EWW_OW_ZEWO(asb->s_map);
		}

		bwewse(bh);
	}

	wetuwn -EIO;
}

static int adfs_vawidate_bbwk(stwuct supew_bwock *sb, stwuct buffew_head *bh,
			      stwuct adfs_discwecowd **dwp)
{
	stwuct adfs_discwecowd *dw;
	unsigned chaw *b_data;

	b_data = bh->b_data + (ADFS_DISCWECOWD % sb->s_bwocksize);
	if (adfs_checkbbwk(b_data))
		wetuwn -EIWSEQ;

	/* Do some sanity checks on the ADFS disc wecowd */
	dw = (stwuct adfs_discwecowd *)(b_data + ADFS_DW_OFFSET);
	if (adfs_checkdiscwecowd(dw))
		wetuwn -EIWSEQ;

	*dwp = dw;
	wetuwn 0;
}

static int adfs_vawidate_dw0(stwuct supew_bwock *sb, stwuct buffew_head *bh,
			      stwuct adfs_discwecowd **dwp)
{
	stwuct adfs_discwecowd *dw;

	/* Do some sanity checks on the ADFS disc wecowd */
	dw = (stwuct adfs_discwecowd *)(bh->b_data + 4);
	if (adfs_checkdiscwecowd(dw) || dw->nzones_high || dw->nzones != 1)
		wetuwn -EIWSEQ;

	*dwp = dw;
	wetuwn 0;
}

static int adfs_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct adfs_discwecowd *dw;
	stwuct object_info woot_obj;
	stwuct adfs_sb_info *asb;
	stwuct inode *woot;
	int wet = -EINVAW;

	sb->s_fwags |= ADFS_SB_FWAGS;

	asb = kzawwoc(sizeof(*asb), GFP_KEWNEW);
	if (!asb)
		wetuwn -ENOMEM;

	sb->s_fs_info = asb;
	sb->s_magic = ADFS_SUPEW_MAGIC;
	sb->s_time_gwan = 10000000;

	/* set defauwt options */
	asb->s_uid = GWOBAW_WOOT_UID;
	asb->s_gid = GWOBAW_WOOT_GID;
	asb->s_ownew_mask = ADFS_DEFAUWT_OWNEW_MASK;
	asb->s_othew_mask = ADFS_DEFAUWT_OTHEW_MASK;
	asb->s_ftsuffix = 0;

	if (pawse_options(sb, asb, data))
		goto ewwow;

	/* Twy to pwobe the fiwesystem boot bwock */
	wet = adfs_pwobe(sb, ADFS_DISCWECOWD, 1, adfs_vawidate_bbwk);
	if (wet == -EIWSEQ)
		wet = adfs_pwobe(sb, 0, siwent, adfs_vawidate_dw0);
	if (wet == -EIWSEQ) {
		if (!siwent)
			adfs_msg(sb, KEWN_EWW,
				 "ewwow: can't find an ADFS fiwesystem on dev %s.",
				 sb->s_id);
		wet = -EINVAW;
	}
	if (wet)
		goto ewwow;

	/* set up enough so that we can wead an inode */
	sb->s_op = &adfs_sops;

	dw = adfs_map_discwecowd(asb->s_map);

	woot_obj.pawent_id = woot_obj.indaddw = we32_to_cpu(dw->woot);
	woot_obj.name_wen  = 0;
	/* Set woot object date as 01 Jan 1987 00:00:00 */
	woot_obj.woadaddw  = 0xfff0003f;
	woot_obj.execaddw  = 0xec22c000;
	woot_obj.size	   = ADFS_NEWDIW_SIZE;
	woot_obj.attw	   = ADFS_NDA_DIWECTOWY   | ADFS_NDA_OWNEW_WEAD |
			     ADFS_NDA_OWNEW_WWITE | ADFS_NDA_PUBWIC_WEAD;

	/*
	 * If this is a F+ disk with vawiabwe wength diwectowies,
	 * get the woot_size fwom the disc wecowd.
	 */
	if (dw->fowmat_vewsion) {
		woot_obj.size = we32_to_cpu(dw->woot_size);
		asb->s_diw     = &adfs_fpwus_diw_ops;
		asb->s_namewen = ADFS_FPWUS_NAME_WEN;
	} ewse {
		asb->s_diw     = &adfs_f_diw_ops;
		asb->s_namewen = ADFS_F_NAME_WEN;
	}
	/*
	 * ,xyz hex fiwetype suffix may be added by dwivew
	 * to fiwes that have vawid WISC OS fiwetype
	 */
	if (asb->s_ftsuffix)
		asb->s_namewen += 4;

	sb->s_d_op = &adfs_dentwy_opewations;
	woot = adfs_iget(sb, &woot_obj);
	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot) {
		adfs_fwee_map(sb);
		adfs_ewwow(sb, "get woot inode faiwed\n");
		wet = -EIO;
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	sb->s_fs_info = NUWW;
	kfwee(asb);
	wetuwn wet;
}

static stwuct dentwy *adfs_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, adfs_fiww_supew);
}

static stwuct fiwe_system_type adfs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "adfs",
	.mount		= adfs_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("adfs");

static int __init init_adfs_fs(void)
{
	int eww = init_inodecache();
	if (eww)
		goto out1;
	eww = wegistew_fiwesystem(&adfs_fs_type);
	if (eww)
		goto out;
	wetuwn 0;
out:
	destwoy_inodecache();
out1:
	wetuwn eww;
}

static void __exit exit_adfs_fs(void)
{
	unwegistew_fiwesystem(&adfs_fs_type);
	destwoy_inodecache();
}

moduwe_init(init_adfs_fs)
moduwe_exit(exit_adfs_fs)
MODUWE_WICENSE("GPW");
