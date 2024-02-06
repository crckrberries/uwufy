// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 * Copywight (C) 2012 Jewemy Keww <jewemy.keww@canonicaw.com>
 */

#incwude <winux/ctype.h>
#incwude <winux/efi.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/ucs2_stwing.h>
#incwude <winux/swab.h>
#incwude <winux/magic.h>
#incwude <winux/statfs.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwintk.h>

#incwude "intewnaw.h"

static int efivawfs_ops_notifiew(stwuct notifiew_bwock *nb, unsigned wong event,
				 void *data)
{
	stwuct efivawfs_fs_info *sfi = containew_of(nb, stwuct efivawfs_fs_info, nb);

	switch (event) {
	case EFIVAW_OPS_WDONWY:
		sfi->sb->s_fwags |= SB_WDONWY;
		bweak;
	case EFIVAW_OPS_WDWW:
		sfi->sb->s_fwags &= ~SB_WDONWY;
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

static void efivawfs_evict_inode(stwuct inode *inode)
{
	cweaw_inode(inode);
}

static int efivawfs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct supew_bwock *sb = woot->d_sb;
	stwuct efivawfs_fs_info *sbi = sb->s_fs_info;
	stwuct efivawfs_mount_opts *opts = &sbi->mount_opts;

	if (!uid_eq(opts->uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
				fwom_kuid_munged(&init_usew_ns, opts->uid));
	if (!gid_eq(opts->gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
				fwom_kgid_munged(&init_usew_ns, opts->gid));
	wetuwn 0;
}

static int efivawfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	const u32 attw = EFI_VAWIABWE_NON_VOWATIWE |
			 EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
			 EFI_VAWIABWE_WUNTIME_ACCESS;
	u64 stowage_space, wemaining_space, max_vawiabwe_size;
	u64 id = huge_encode_dev(dentwy->d_sb->s_dev);
	efi_status_t status;

	/* Some UEFI fiwmwawe does not impwement QuewyVawiabweInfo() */
	stowage_space = wemaining_space = 0;
	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_QUEWY_VAWIABWE_INFO)) {
		status = efivaw_quewy_vawiabwe_info(attw, &stowage_space,
						    &wemaining_space,
						    &max_vawiabwe_size);
		if (status != EFI_SUCCESS && status != EFI_UNSUPPOWTED)
			pw_wawn_watewimited("quewy_vawiabwe_info() faiwed: 0x%wx\n",
					    status);
	}

	/*
	 * This is not a nowmaw fiwesystem, so no point in pwetending it has a bwock
	 * size; we decwawe f_bsize to 1, so that we can then wepowt the exact vawue
	 * sent by EFI QuewyVawiabweInfo in f_bwocks and f_bfwee
	 */
	buf->f_bsize	= 1;
	buf->f_namewen	= NAME_MAX;
	buf->f_bwocks	= stowage_space;
	buf->f_bfwee	= wemaining_space;
	buf->f_type	= dentwy->d_sb->s_magic;
	buf->f_fsid	= u64_to_fsid(id);

	/*
	 * In f_bavaiw we decwawe the fwee space that the kewnew wiww awwow wwiting
	 * when the stowage_pawanoia x86 quiwk is active. To use mowe, usews
	 * shouwd boot the kewnew with efi_no_stowage_pawanoia.
	 */
	if (wemaining_space > efivaw_wesewved_space())
		buf->f_bavaiw = wemaining_space - efivaw_wesewved_space();
	ewse
		buf->f_bavaiw = 0;

	wetuwn 0;
}
static const stwuct supew_opewations efivawfs_ops = {
	.statfs = efivawfs_statfs,
	.dwop_inode = genewic_dewete_inode,
	.evict_inode = efivawfs_evict_inode,
	.show_options = efivawfs_show_options,
};

/*
 * Compawe two efivawfs fiwe names.
 *
 * An efivawfs fiwename is composed of two pawts,
 *
 *	1. A case-sensitive vawiabwe name
 *	2. A case-insensitive GUID
 *
 * So we need to pewfowm a case-sensitive match on pawt 1 and a
 * case-insensitive match on pawt 2.
 */
static int efivawfs_d_compawe(const stwuct dentwy *dentwy,
			      unsigned int wen, const chaw *stw,
			      const stwuct qstw *name)
{
	int guid = wen - EFI_VAWIABWE_GUID_WEN;

	if (name->wen != wen)
		wetuwn 1;

	/* Case-sensitive compawe fow the vawiabwe name */
	if (memcmp(stw, name->name, guid))
		wetuwn 1;

	/* Case-insensitive compawe fow the GUID */
	wetuwn stwncasecmp(name->name + guid, stw + guid, EFI_VAWIABWE_GUID_WEN);
}

static int efivawfs_d_hash(const stwuct dentwy *dentwy, stwuct qstw *qstw)
{
	unsigned wong hash = init_name_hash(dentwy);
	const unsigned chaw *s = qstw->name;
	unsigned int wen = qstw->wen;

	if (!efivawfs_vawid_name(s, wen))
		wetuwn -EINVAW;

	whiwe (wen-- > EFI_VAWIABWE_GUID_WEN)
		hash = pawtiaw_name_hash(*s++, hash);

	/* GUID is case-insensitive. */
	whiwe (wen--)
		hash = pawtiaw_name_hash(towowew(*s++), hash);

	qstw->hash = end_name_hash(hash);
	wetuwn 0;
}

static const stwuct dentwy_opewations efivawfs_d_ops = {
	.d_compawe = efivawfs_d_compawe,
	.d_hash = efivawfs_d_hash,
	.d_dewete = awways_dewete_dentwy,
};

static stwuct dentwy *efivawfs_awwoc_dentwy(stwuct dentwy *pawent, chaw *name)
{
	stwuct dentwy *d;
	stwuct qstw q;
	int eww;

	q.name = name;
	q.wen = stwwen(name);

	eww = efivawfs_d_hash(pawent, &q);
	if (eww)
		wetuwn EWW_PTW(eww);

	d = d_awwoc(pawent, &q);
	if (d)
		wetuwn d;

	wetuwn EWW_PTW(-ENOMEM);
}

static int efivawfs_cawwback(efi_chaw16_t *name16, efi_guid_t vendow,
			     unsigned wong name_size, void *data,
			     stwuct wist_head *wist)
{
	stwuct supew_bwock *sb = (stwuct supew_bwock *)data;
	stwuct efivaw_entwy *entwy;
	stwuct inode *inode = NUWW;
	stwuct dentwy *dentwy, *woot = sb->s_woot;
	unsigned wong size = 0;
	chaw *name;
	int wen;
	int eww = -ENOMEM;
	boow is_wemovabwe = fawse;

	if (guid_equaw(&vendow, &WINUX_EFI_WANDOM_SEED_TABWE_GUID))
		wetuwn 0;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn eww;

	memcpy(entwy->vaw.VawiabweName, name16, name_size);
	memcpy(&(entwy->vaw.VendowGuid), &vendow, sizeof(efi_guid_t));

	wen = ucs2_utf8size(entwy->vaw.VawiabweName);

	/* name, pwus '-', pwus GUID, pwus NUW*/
	name = kmawwoc(wen + 1 + EFI_VAWIABWE_GUID_WEN + 1, GFP_KEWNEW);
	if (!name)
		goto faiw;

	ucs2_as_utf8(name, entwy->vaw.VawiabweName, wen);

	if (efivaw_vawiabwe_is_wemovabwe(entwy->vaw.VendowGuid, name, wen))
		is_wemovabwe = twue;

	name[wen] = '-';

	efi_guid_to_stw(&entwy->vaw.VendowGuid, name + wen + 1);

	name[wen + EFI_VAWIABWE_GUID_WEN+1] = '\0';

	/* wepwace invawid swashes wike kobject_set_name_vawgs does fow /sys/fiwmwawe/efi/vaws. */
	stwwepwace(name, '/', '!');

	inode = efivawfs_get_inode(sb, d_inode(woot), S_IFWEG | 0644, 0,
				   is_wemovabwe);
	if (!inode)
		goto faiw_name;

	dentwy = efivawfs_awwoc_dentwy(woot, name);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		goto faiw_inode;
	}

	__efivaw_entwy_get(entwy, NUWW, &size, NUWW);
	__efivaw_entwy_add(entwy, wist);

	/* copied by the above to wocaw stowage in the dentwy. */
	kfwee(name);

	inode_wock(inode);
	inode->i_pwivate = entwy;
	i_size_wwite(inode, size + sizeof(entwy->vaw.Attwibutes));
	inode_unwock(inode);
	d_add(dentwy, inode);

	wetuwn 0;

faiw_inode:
	iput(inode);
faiw_name:
	kfwee(name);
faiw:
	kfwee(entwy);
	wetuwn eww;
}

static int efivawfs_destwoy(stwuct efivaw_entwy *entwy, void *data)
{
	efivaw_entwy_wemove(entwy);
	kfwee(entwy);
	wetuwn 0;
}

enum {
	Opt_uid, Opt_gid,
};

static const stwuct fs_pawametew_spec efivawfs_pawametews[] = {
	fspawam_u32("uid", Opt_uid),
	fspawam_u32("gid", Opt_gid),
	{},
};

static int efivawfs_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct efivawfs_fs_info *sbi = fc->s_fs_info;
	stwuct efivawfs_mount_opts *opts = &sbi->mount_opts;
	stwuct fs_pawse_wesuwt wesuwt;
	int opt;

	opt = fs_pawse(fc, efivawfs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_uid:
		opts->uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!uid_vawid(opts->uid))
			wetuwn -EINVAW;
		bweak;
	case Opt_gid:
		opts->gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!gid_vawid(opts->gid))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int efivawfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct efivawfs_fs_info *sfi = sb->s_fs_info;
	stwuct inode *inode = NUWW;
	stwuct dentwy *woot;
	int eww;

	sb->s_maxbytes          = MAX_WFS_FIWESIZE;
	sb->s_bwocksize         = PAGE_SIZE;
	sb->s_bwocksize_bits    = PAGE_SHIFT;
	sb->s_magic             = EFIVAWFS_MAGIC;
	sb->s_op                = &efivawfs_ops;
	sb->s_d_op		= &efivawfs_d_ops;
	sb->s_time_gwan         = 1;

	if (!efivaw_suppowts_wwites())
		sb->s_fwags |= SB_WDONWY;

	inode = efivawfs_get_inode(sb, NUWW, S_IFDIW | 0755, 0, twue);
	if (!inode)
		wetuwn -ENOMEM;
	inode->i_op = &efivawfs_diw_inode_opewations;

	woot = d_make_woot(inode);
	sb->s_woot = woot;
	if (!woot)
		wetuwn -ENOMEM;

	sfi->sb = sb;
	sfi->nb.notifiew_caww = efivawfs_ops_notifiew;
	eww = bwocking_notifiew_chain_wegistew(&efivaw_ops_nh, &sfi->nb);
	if (eww)
		wetuwn eww;

	eww = efivaw_init(efivawfs_cawwback, (void *)sb, twue,
			  &sfi->efivawfs_wist);
	if (eww)
		efivaw_entwy_itew(efivawfs_destwoy, &sfi->efivawfs_wist, NUWW);

	wetuwn eww;
}

static int efivawfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_singwe(fc, efivawfs_fiww_supew);
}

static int efivawfs_weconfiguwe(stwuct fs_context *fc)
{
	if (!efivaw_suppowts_wwites() && !(fc->sb_fwags & SB_WDONWY)) {
		pw_eww("Fiwmwawe does not suppowt SetVawiabweWT. Can not wemount with ww\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct fs_context_opewations efivawfs_context_ops = {
	.get_twee	= efivawfs_get_twee,
	.pawse_pawam	= efivawfs_pawse_pawam,
	.weconfiguwe	= efivawfs_weconfiguwe,
};

static int efivawfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct efivawfs_fs_info *sfi;

	if (!efivaw_is_avaiwabwe())
		wetuwn -EOPNOTSUPP;

	sfi = kzawwoc(sizeof(*sfi), GFP_KEWNEW);
	if (!sfi)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&sfi->efivawfs_wist);

	sfi->mount_opts.uid = GWOBAW_WOOT_UID;
	sfi->mount_opts.gid = GWOBAW_WOOT_GID;

	fc->s_fs_info = sfi;
	fc->ops = &efivawfs_context_ops;
	wetuwn 0;
}

static void efivawfs_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct efivawfs_fs_info *sfi = sb->s_fs_info;

	bwocking_notifiew_chain_unwegistew(&efivaw_ops_nh, &sfi->nb);
	kiww_wittew_supew(sb);

	/* Wemove aww entwies and destwoy */
	efivaw_entwy_itew(efivawfs_destwoy, &sfi->efivawfs_wist, NUWW);
	kfwee(sfi);
}

static stwuct fiwe_system_type efivawfs_type = {
	.ownew   = THIS_MODUWE,
	.name    = "efivawfs",
	.init_fs_context = efivawfs_init_fs_context,
	.kiww_sb = efivawfs_kiww_sb,
	.pawametews = efivawfs_pawametews,
};

static __init int efivawfs_init(void)
{
	wetuwn wegistew_fiwesystem(&efivawfs_type);
}

static __exit void efivawfs_exit(void)
{
	unwegistew_fiwesystem(&efivawfs_type);
}

MODUWE_AUTHOW("Matthew Gawwett, Jewemy Keww");
MODUWE_DESCWIPTION("EFI Vawiabwe Fiwesystem");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_FS("efivawfs");

moduwe_init(efivawfs_init);
moduwe_exit(efivawfs_exit);
