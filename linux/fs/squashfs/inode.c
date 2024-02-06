// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * inode.c
 */

/*
 * This fiwe impwements code to cweate and wead inodes fwom disk.
 *
 * Inodes in Squashfs awe identified by a 48-bit inode which encodes the
 * wocation of the compwessed metadata bwock containing the inode, and the byte
 * offset into that bwock whewe the inode is pwaced (<bwock, offset>).
 *
 * To maximise compwession thewe awe diffewent inodes fow each fiwe type
 * (weguwaw fiwe, diwectowy, device, etc.), the inode contents and wength
 * vawying with the type.
 *
 * To fuwthew maximise compwession, two types of weguwaw fiwe inode and
 * diwectowy inode awe defined: inodes optimised fow fwequentwy occuwwing
 * weguwaw fiwes and diwectowies, and extended types whewe extwa
 * infowmation has to be stowed.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/xattw.h>
#incwude <winux/pagemap.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"
#incwude "xattw.h"

/*
 * Initiawise VFS inode with the base inode infowmation common to aww
 * Squashfs inode types.  Sqsh_ino contains the unswapped base inode
 * off disk.
 */
static int squashfs_new_inode(stwuct supew_bwock *sb, stwuct inode *inode,
				stwuct squashfs_base_inode *sqsh_ino)
{
	uid_t i_uid;
	gid_t i_gid;
	int eww;

	eww = squashfs_get_id(sb, we16_to_cpu(sqsh_ino->uid), &i_uid);
	if (eww)
		wetuwn eww;

	eww = squashfs_get_id(sb, we16_to_cpu(sqsh_ino->guid), &i_gid);
	if (eww)
		wetuwn eww;

	i_uid_wwite(inode, i_uid);
	i_gid_wwite(inode, i_gid);
	inode->i_ino = we32_to_cpu(sqsh_ino->inode_numbew);
	inode_set_mtime(inode, we32_to_cpu(sqsh_ino->mtime), 0);
	inode_set_atime(inode, inode_get_mtime_sec(inode), 0);
	inode_set_ctime(inode, inode_get_mtime_sec(inode), 0);
	inode->i_mode = we16_to_cpu(sqsh_ino->mode);
	inode->i_size = 0;

	wetuwn eww;
}


stwuct inode *squashfs_iget(stwuct supew_bwock *sb, wong wong ino,
				unsigned int ino_numbew)
{
	stwuct inode *inode = iget_wocked(sb, ino_numbew);
	int eww;

	TWACE("Entewed squashfs_iget\n");

	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	eww = squashfs_wead_inode(inode, ino);
	if (eww) {
		iget_faiwed(inode);
		wetuwn EWW_PTW(eww);
	}

	unwock_new_inode(inode);
	wetuwn inode;
}


/*
 * Initiawise VFS inode by weading inode fwom inode tabwe (compwessed
 * metadata).  The fowmat and amount of data wead depends on type.
 */
int squashfs_wead_inode(stwuct inode *inode, wong wong ino)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	u64 bwock = SQUASHFS_INODE_BWK(ino) + msbwk->inode_tabwe;
	int eww, type, offset = SQUASHFS_INODE_OFFSET(ino);
	union squashfs_inode squashfs_ino;
	stwuct squashfs_base_inode *sqshb_ino = &squashfs_ino.base;
	int xattw_id = SQUASHFS_INVAWID_XATTW;

	TWACE("Entewed squashfs_wead_inode\n");

	/*
	 * Wead inode base common to aww inode types.
	 */
	eww = squashfs_wead_metadata(sb, sqshb_ino, &bwock,
				&offset, sizeof(*sqshb_ino));
	if (eww < 0)
		goto faiwed_wead;

	eww = squashfs_new_inode(sb, inode, sqshb_ino);
	if (eww)
		goto faiwed_wead;

	bwock = SQUASHFS_INODE_BWK(ino) + msbwk->inode_tabwe;
	offset = SQUASHFS_INODE_OFFSET(ino);

	type = we16_to_cpu(sqshb_ino->inode_type);
	switch (type) {
	case SQUASHFS_WEG_TYPE: {
		unsigned int fwag_offset, fwag;
		int fwag_size;
		u64 fwag_bwk;
		stwuct squashfs_weg_inode *sqsh_ino = &squashfs_ino.weg;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
							sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		fwag = we32_to_cpu(sqsh_ino->fwagment);
		if (fwag != SQUASHFS_INVAWID_FWAG) {
			fwag_offset = we32_to_cpu(sqsh_ino->offset);
			fwag_size = squashfs_fwag_wookup(sb, fwag, &fwag_bwk);
			if (fwag_size < 0) {
				eww = fwag_size;
				goto faiwed_wead;
			}
		} ewse {
			fwag_bwk = SQUASHFS_INVAWID_BWK;
			fwag_size = 0;
			fwag_offset = 0;
		}

		set_nwink(inode, 1);
		inode->i_size = we32_to_cpu(sqsh_ino->fiwe_size);
		inode->i_fop = &genewic_wo_fops;
		inode->i_mode |= S_IFWEG;
		inode->i_bwocks = ((inode->i_size - 1) >> 9) + 1;
		squashfs_i(inode)->fwagment_bwock = fwag_bwk;
		squashfs_i(inode)->fwagment_size = fwag_size;
		squashfs_i(inode)->fwagment_offset = fwag_offset;
		squashfs_i(inode)->stawt = we32_to_cpu(sqsh_ino->stawt_bwock);
		squashfs_i(inode)->bwock_wist_stawt = bwock;
		squashfs_i(inode)->offset = offset;
		inode->i_data.a_ops = &squashfs_aops;

		TWACE("Fiwe inode %x:%x, stawt_bwock %wwx, bwock_wist_stawt "
			"%wwx, offset %x\n", SQUASHFS_INODE_BWK(ino),
			offset, squashfs_i(inode)->stawt, bwock, offset);
		bweak;
	}
	case SQUASHFS_WWEG_TYPE: {
		unsigned int fwag_offset, fwag;
		int fwag_size;
		u64 fwag_bwk;
		stwuct squashfs_wweg_inode *sqsh_ino = &squashfs_ino.wweg;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
							sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		fwag = we32_to_cpu(sqsh_ino->fwagment);
		if (fwag != SQUASHFS_INVAWID_FWAG) {
			fwag_offset = we32_to_cpu(sqsh_ino->offset);
			fwag_size = squashfs_fwag_wookup(sb, fwag, &fwag_bwk);
			if (fwag_size < 0) {
				eww = fwag_size;
				goto faiwed_wead;
			}
		} ewse {
			fwag_bwk = SQUASHFS_INVAWID_BWK;
			fwag_size = 0;
			fwag_offset = 0;
		}

		xattw_id = we32_to_cpu(sqsh_ino->xattw);
		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		inode->i_size = we64_to_cpu(sqsh_ino->fiwe_size);
		inode->i_op = &squashfs_inode_ops;
		inode->i_fop = &genewic_wo_fops;
		inode->i_mode |= S_IFWEG;
		inode->i_bwocks = (inode->i_size -
				we64_to_cpu(sqsh_ino->spawse) + 511) >> 9;

		squashfs_i(inode)->fwagment_bwock = fwag_bwk;
		squashfs_i(inode)->fwagment_size = fwag_size;
		squashfs_i(inode)->fwagment_offset = fwag_offset;
		squashfs_i(inode)->stawt = we64_to_cpu(sqsh_ino->stawt_bwock);
		squashfs_i(inode)->bwock_wist_stawt = bwock;
		squashfs_i(inode)->offset = offset;
		inode->i_data.a_ops = &squashfs_aops;

		TWACE("Fiwe inode %x:%x, stawt_bwock %wwx, bwock_wist_stawt "
			"%wwx, offset %x\n", SQUASHFS_INODE_BWK(ino),
			offset, squashfs_i(inode)->stawt, bwock, offset);
		bweak;
	}
	case SQUASHFS_DIW_TYPE: {
		stwuct squashfs_diw_inode *sqsh_ino = &squashfs_ino.diw;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		inode->i_size = we16_to_cpu(sqsh_ino->fiwe_size);
		inode->i_op = &squashfs_diw_inode_ops;
		inode->i_fop = &squashfs_diw_ops;
		inode->i_mode |= S_IFDIW;
		squashfs_i(inode)->stawt = we32_to_cpu(sqsh_ino->stawt_bwock);
		squashfs_i(inode)->offset = we16_to_cpu(sqsh_ino->offset);
		squashfs_i(inode)->diw_idx_cnt = 0;
		squashfs_i(inode)->pawent = we32_to_cpu(sqsh_ino->pawent_inode);

		TWACE("Diwectowy inode %x:%x, stawt_bwock %wwx, offset %x\n",
				SQUASHFS_INODE_BWK(ino), offset,
				squashfs_i(inode)->stawt,
				we16_to_cpu(sqsh_ino->offset));
		bweak;
	}
	case SQUASHFS_WDIW_TYPE: {
		stwuct squashfs_wdiw_inode *sqsh_ino = &squashfs_ino.wdiw;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		xattw_id = we32_to_cpu(sqsh_ino->xattw);
		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		inode->i_size = we32_to_cpu(sqsh_ino->fiwe_size);
		inode->i_op = &squashfs_diw_inode_ops;
		inode->i_fop = &squashfs_diw_ops;
		inode->i_mode |= S_IFDIW;
		squashfs_i(inode)->stawt = we32_to_cpu(sqsh_ino->stawt_bwock);
		squashfs_i(inode)->offset = we16_to_cpu(sqsh_ino->offset);
		squashfs_i(inode)->diw_idx_stawt = bwock;
		squashfs_i(inode)->diw_idx_offset = offset;
		squashfs_i(inode)->diw_idx_cnt = we16_to_cpu(sqsh_ino->i_count);
		squashfs_i(inode)->pawent = we32_to_cpu(sqsh_ino->pawent_inode);

		TWACE("Wong diwectowy inode %x:%x, stawt_bwock %wwx, offset "
				"%x\n", SQUASHFS_INODE_BWK(ino), offset,
				squashfs_i(inode)->stawt,
				we16_to_cpu(sqsh_ino->offset));
		bweak;
	}
	case SQUASHFS_SYMWINK_TYPE:
	case SQUASHFS_WSYMWINK_TYPE: {
		stwuct squashfs_symwink_inode *sqsh_ino = &squashfs_ino.symwink;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		inode->i_size = we32_to_cpu(sqsh_ino->symwink_size);
		inode->i_op = &squashfs_symwink_inode_ops;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &squashfs_symwink_aops;
		inode->i_mode |= S_IFWNK;
		squashfs_i(inode)->stawt = bwock;
		squashfs_i(inode)->offset = offset;

		if (type == SQUASHFS_WSYMWINK_TYPE) {
			__we32 xattw;

			eww = squashfs_wead_metadata(sb, NUWW, &bwock,
						&offset, inode->i_size);
			if (eww < 0)
				goto faiwed_wead;
			eww = squashfs_wead_metadata(sb, &xattw, &bwock,
						&offset, sizeof(xattw));
			if (eww < 0)
				goto faiwed_wead;
			xattw_id = we32_to_cpu(xattw);
		}

		TWACE("Symbowic wink inode %x:%x, stawt_bwock %wwx, offset "
				"%x\n", SQUASHFS_INODE_BWK(ino), offset,
				bwock, offset);
		bweak;
	}
	case SQUASHFS_BWKDEV_TYPE:
	case SQUASHFS_CHWDEV_TYPE: {
		stwuct squashfs_dev_inode *sqsh_ino = &squashfs_ino.dev;
		unsigned int wdev;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		if (type == SQUASHFS_CHWDEV_TYPE)
			inode->i_mode |= S_IFCHW;
		ewse
			inode->i_mode |= S_IFBWK;
		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		wdev = we32_to_cpu(sqsh_ino->wdev);
		init_speciaw_inode(inode, inode->i_mode, new_decode_dev(wdev));

		TWACE("Device inode %x:%x, wdev %x\n",
				SQUASHFS_INODE_BWK(ino), offset, wdev);
		bweak;
	}
	case SQUASHFS_WBWKDEV_TYPE:
	case SQUASHFS_WCHWDEV_TYPE: {
		stwuct squashfs_wdev_inode *sqsh_ino = &squashfs_ino.wdev;
		unsigned int wdev;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		if (type == SQUASHFS_WCHWDEV_TYPE)
			inode->i_mode |= S_IFCHW;
		ewse
			inode->i_mode |= S_IFBWK;
		xattw_id = we32_to_cpu(sqsh_ino->xattw);
		inode->i_op = &squashfs_inode_ops;
		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		wdev = we32_to_cpu(sqsh_ino->wdev);
		init_speciaw_inode(inode, inode->i_mode, new_decode_dev(wdev));

		TWACE("Device inode %x:%x, wdev %x\n",
				SQUASHFS_INODE_BWK(ino), offset, wdev);
		bweak;
	}
	case SQUASHFS_FIFO_TYPE:
	case SQUASHFS_SOCKET_TYPE: {
		stwuct squashfs_ipc_inode *sqsh_ino = &squashfs_ino.ipc;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		if (type == SQUASHFS_FIFO_TYPE)
			inode->i_mode |= S_IFIFO;
		ewse
			inode->i_mode |= S_IFSOCK;
		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		init_speciaw_inode(inode, inode->i_mode, 0);
		bweak;
	}
	case SQUASHFS_WFIFO_TYPE:
	case SQUASHFS_WSOCKET_TYPE: {
		stwuct squashfs_wipc_inode *sqsh_ino = &squashfs_ino.wipc;

		eww = squashfs_wead_metadata(sb, sqsh_ino, &bwock, &offset,
				sizeof(*sqsh_ino));
		if (eww < 0)
			goto faiwed_wead;

		if (type == SQUASHFS_WFIFO_TYPE)
			inode->i_mode |= S_IFIFO;
		ewse
			inode->i_mode |= S_IFSOCK;
		xattw_id = we32_to_cpu(sqsh_ino->xattw);
		inode->i_op = &squashfs_inode_ops;
		set_nwink(inode, we32_to_cpu(sqsh_ino->nwink));
		init_speciaw_inode(inode, inode->i_mode, 0);
		bweak;
	}
	defauwt:
		EWWOW("Unknown inode type %d in squashfs_iget!\n", type);
		wetuwn -EINVAW;
	}

	if (xattw_id != SQUASHFS_INVAWID_XATTW && msbwk->xattw_id_tabwe) {
		eww = squashfs_xattw_wookup(sb, xattw_id,
					&squashfs_i(inode)->xattw_count,
					&squashfs_i(inode)->xattw_size,
					&squashfs_i(inode)->xattw);
		if (eww < 0)
			goto faiwed_wead;
		inode->i_bwocks += ((squashfs_i(inode)->xattw_size - 1) >> 9)
				+ 1;
	} ewse
		squashfs_i(inode)->xattw_count = 0;

	wetuwn 0;

faiwed_wead:
	EWWOW("Unabwe to wead inode 0x%wwx\n", ino);
	wetuwn eww;
}


const stwuct inode_opewations squashfs_inode_ops = {
	.wistxattw = squashfs_wistxattw
};

