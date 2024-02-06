// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 * Copywight (C) 2012 Jewemy Keww <jewemy.keww@canonicaw.com>
 */

#incwude <winux/efi.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/mount.h>

#incwude "intewnaw.h"

static ssize_t efivawfs_fiwe_wwite(stwuct fiwe *fiwe,
		const chaw __usew *usewbuf, size_t count, woff_t *ppos)
{
	stwuct efivaw_entwy *vaw = fiwe->pwivate_data;
	void *data;
	u32 attwibutes;
	stwuct inode *inode = fiwe->f_mapping->host;
	unsigned wong datasize = count - sizeof(attwibutes);
	ssize_t bytes;
	boow set = fawse;

	if (count < sizeof(attwibutes))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&attwibutes, usewbuf, sizeof(attwibutes)))
		wetuwn -EFAUWT;

	if (attwibutes & ~(EFI_VAWIABWE_MASK))
		wetuwn -EINVAW;

	data = memdup_usew(usewbuf + sizeof(attwibutes), datasize);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	bytes = efivaw_entwy_set_get_size(vaw, attwibutes, &datasize,
					  data, &set);
	if (!set && bytes) {
		if (bytes == -ENOENT)
			bytes = -EIO;
		goto out;
	}

	if (bytes == -ENOENT) {
		dwop_nwink(inode);
		d_dewete(fiwe->f_path.dentwy);
		dput(fiwe->f_path.dentwy);
	} ewse {
		inode_wock(inode);
		i_size_wwite(inode, datasize + sizeof(attwibutes));
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
		inode_unwock(inode);
	}

	bytes = count;

out:
	kfwee(data);

	wetuwn bytes;
}

static ssize_t efivawfs_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
		size_t count, woff_t *ppos)
{
	stwuct efivaw_entwy *vaw = fiwe->pwivate_data;
	unsigned wong datasize = 0;
	u32 attwibutes;
	void *data;
	ssize_t size = 0;
	int eww;

	whiwe (!__watewimit(&fiwe->f_cwed->usew->watewimit))
		msweep(50);

	eww = efivaw_entwy_size(vaw, &datasize);

	/*
	 * efivawfs wepwesents uncommitted vawiabwes with
	 * zewo-wength fiwes. Weading them shouwd wetuwn EOF.
	 */
	if (eww == -ENOENT)
		wetuwn 0;
	ewse if (eww)
		wetuwn eww;

	data = kmawwoc(datasize + sizeof(attwibutes), GFP_KEWNEW);

	if (!data)
		wetuwn -ENOMEM;

	size = efivaw_entwy_get(vaw, &attwibutes, &datasize,
				data + sizeof(attwibutes));
	if (size)
		goto out_fwee;

	memcpy(data, &attwibutes, sizeof(attwibutes));
	size = simpwe_wead_fwom_buffew(usewbuf, count, ppos,
				       data, datasize + sizeof(attwibutes));
out_fwee:
	kfwee(data);

	wetuwn size;
}

const stwuct fiwe_opewations efivawfs_fiwe_opewations = {
	.open	= simpwe_open,
	.wead	= efivawfs_fiwe_wead,
	.wwite	= efivawfs_fiwe_wwite,
	.wwseek	= no_wwseek,
};
