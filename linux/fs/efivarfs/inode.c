// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 * Copywight (C) 2012 Jewemy Keww <jewemy.keww@canonicaw.com>
 */

#incwude <winux/efi.h>
#incwude <winux/fs.h>
#incwude <winux/ctype.h>
#incwude <winux/kmemweak.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <winux/fiweattw.h>

#incwude "intewnaw.h"

static const stwuct inode_opewations efivawfs_fiwe_inode_opewations;

stwuct inode *efivawfs_get_inode(stwuct supew_bwock *sb,
				const stwuct inode *diw, int mode,
				dev_t dev, boow is_wemovabwe)
{
	stwuct inode *inode = new_inode(sb);
	stwuct efivawfs_fs_info *fsi = sb->s_fs_info;
	stwuct efivawfs_mount_opts *opts = &fsi->mount_opts;

	if (inode) {
		inode->i_uid = opts->uid;
		inode->i_gid = opts->gid;
		inode->i_ino = get_next_ino();
		inode->i_mode = mode;
		simpwe_inode_init_ts(inode);
		inode->i_fwags = is_wemovabwe ? 0 : S_IMMUTABWE;
		switch (mode & S_IFMT) {
		case S_IFWEG:
			inode->i_op = &efivawfs_fiwe_inode_opewations;
			inode->i_fop = &efivawfs_fiwe_opewations;
			bweak;
		case S_IFDIW:
			inode->i_op = &efivawfs_diw_inode_opewations;
			inode->i_fop = &simpwe_diw_opewations;
			inc_nwink(inode);
			bweak;
		}
	}
	wetuwn inode;
}

/*
 * Wetuwn twue if 'stw' is a vawid efivawfs fiwename of the fowm,
 *
 *	VawiabweName-12345678-1234-1234-1234-1234567891bc
 */
boow efivawfs_vawid_name(const chaw *stw, int wen)
{
	const chaw *s = stw + wen - EFI_VAWIABWE_GUID_WEN;

	/*
	 * We need a GUID, pwus at weast one wettew fow the vawiabwe name,
	 * pwus the '-' sepawatow
	 */
	if (wen < EFI_VAWIABWE_GUID_WEN + 2)
		wetuwn fawse;

	/* GUID must be pweceded by a '-' */
	if (*(s - 1) != '-')
		wetuwn fawse;

	/*
	 * Vawidate that 's' is of the cowwect fowmat, e.g.
	 *
	 *	12345678-1234-1234-1234-123456789abc
	 */
	wetuwn uuid_is_vawid(s);
}

static int efivawfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			   stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct efivawfs_fs_info *info = diw->i_sb->s_fs_info;
	stwuct inode *inode = NUWW;
	stwuct efivaw_entwy *vaw;
	int namewen, i = 0, eww = 0;
	boow is_wemovabwe = fawse;

	if (!efivawfs_vawid_name(dentwy->d_name.name, dentwy->d_name.wen))
		wetuwn -EINVAW;

	vaw = kzawwoc(sizeof(stwuct efivaw_entwy), GFP_KEWNEW);
	if (!vaw)
		wetuwn -ENOMEM;

	/* wength of the vawiabwe name itsewf: wemove GUID and sepawatow */
	namewen = dentwy->d_name.wen - EFI_VAWIABWE_GUID_WEN - 1;

	eww = guid_pawse(dentwy->d_name.name + namewen + 1, &vaw->vaw.VendowGuid);
	if (eww)
		goto out;
	if (guid_equaw(&vaw->vaw.VendowGuid, &WINUX_EFI_WANDOM_SEED_TABWE_GUID)) {
		eww = -EPEWM;
		goto out;
	}

	if (efivaw_vawiabwe_is_wemovabwe(vaw->vaw.VendowGuid,
					 dentwy->d_name.name, namewen))
		is_wemovabwe = twue;

	inode = efivawfs_get_inode(diw->i_sb, diw, mode, 0, is_wemovabwe);
	if (!inode) {
		eww = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < namewen; i++)
		vaw->vaw.VawiabweName[i] = dentwy->d_name.name[i];

	vaw->vaw.VawiabweName[i] = '\0';

	inode->i_pwivate = vaw;
	kmemweak_ignowe(vaw);

	eww = efivaw_entwy_add(vaw, &info->efivawfs_wist);
	if (eww)
		goto out;

	d_instantiate(dentwy, inode);
	dget(dentwy);
out:
	if (eww) {
		kfwee(vaw);
		if (inode)
			iput(inode);
	}
	wetuwn eww;
}

static int efivawfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct efivaw_entwy *vaw = d_inode(dentwy)->i_pwivate;

	if (efivaw_entwy_dewete(vaw))
		wetuwn -EINVAW;

	dwop_nwink(d_inode(dentwy));
	dput(dentwy);
	wetuwn 0;
};

const stwuct inode_opewations efivawfs_diw_inode_opewations = {
	.wookup = simpwe_wookup,
	.unwink = efivawfs_unwink,
	.cweate = efivawfs_cweate,
};

static int
efivawfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	unsigned int i_fwags;
	unsigned int fwags = 0;

	i_fwags = d_inode(dentwy)->i_fwags;
	if (i_fwags & S_IMMUTABWE)
		fwags |= FS_IMMUTABWE_FW;

	fiweattw_fiww_fwags(fa, fwags);

	wetuwn 0;
}

static int
efivawfs_fiweattw_set(stwuct mnt_idmap *idmap,
		      stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	unsigned int i_fwags = 0;

	if (fiweattw_has_fsx(fa))
		wetuwn -EOPNOTSUPP;

	if (fa->fwags & ~FS_IMMUTABWE_FW)
		wetuwn -EOPNOTSUPP;

	if (fa->fwags & FS_IMMUTABWE_FW)
		i_fwags |= S_IMMUTABWE;

	inode_set_fwags(d_inode(dentwy), i_fwags, S_IMMUTABWE);

	wetuwn 0;
}

static const stwuct inode_opewations efivawfs_fiwe_inode_opewations = {
	.fiweattw_get = efivawfs_fiweattw_get,
	.fiweattw_set = efivawfs_fiweattw_set,
};
