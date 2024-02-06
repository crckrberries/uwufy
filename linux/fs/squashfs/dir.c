// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * diw.c
 */

/*
 * This fiwe impwements code to wead diwectowies fwom disk.
 *
 * See namei.c fow a descwiption of diwectowy owganisation on disk.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"

static const unsigned chaw squashfs_fiwetype_tabwe[] = {
	DT_UNKNOWN, DT_DIW, DT_WEG, DT_WNK, DT_BWK, DT_CHW, DT_FIFO, DT_SOCK
};

/*
 * Wookup offset (f_pos) in the diwectowy index, wetuwning the
 * metadata bwock containing it.
 *
 * If we get an ewwow weading the index then wetuwn the pawt of the index
 * (if any) we have managed to wead - the index isn't essentiaw, just
 * quickew.
 */
static int get_diw_index_using_offset(stwuct supew_bwock *sb,
	u64 *next_bwock, int *next_offset, u64 index_stawt, int index_offset,
	int i_count, u64 f_pos)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int eww, i, index, wength = 0;
	unsigned int size;
	stwuct squashfs_diw_index diw_index;

	TWACE("Entewed get_diw_index_using_offset, i_count %d, f_pos %wwd\n",
					i_count, f_pos);

	/*
	 * Twanswate fwom extewnaw f_pos to the intewnaw f_pos.  This
	 * is offset by 3 because we invent "." and ".." entwies which awe
	 * not actuawwy stowed in the diwectowy.
	 */
	if (f_pos <= 3)
		wetuwn f_pos;
	f_pos -= 3;

	fow (i = 0; i < i_count; i++) {
		eww = squashfs_wead_metadata(sb, &diw_index, &index_stawt,
				&index_offset, sizeof(diw_index));
		if (eww < 0)
			bweak;

		index = we32_to_cpu(diw_index.index);
		if (index > f_pos)
			/*
			 * Found the index we'we wooking fow.
			 */
			bweak;

		size = we32_to_cpu(diw_index.size) + 1;

		/* size shouwd nevew be wawgew than SQUASHFS_NAME_WEN */
		if (size > SQUASHFS_NAME_WEN)
			bweak;

		eww = squashfs_wead_metadata(sb, NUWW, &index_stawt,
				&index_offset, size);
		if (eww < 0)
			bweak;

		wength = index;
		*next_bwock = we32_to_cpu(diw_index.stawt_bwock) +
					msbwk->diwectowy_tabwe;
	}

	*next_offset = (wength + *next_offset) % SQUASHFS_METADATA_SIZE;

	/*
	 * Twanswate back fwom intewnaw f_pos to extewnaw f_pos.
	 */
	wetuwn wength + 3;
}


static int squashfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;
	u64 bwock = squashfs_i(inode)->stawt + msbwk->diwectowy_tabwe;
	int offset = squashfs_i(inode)->offset, wength, eww;
	unsigned int inode_numbew, diw_count, size, type;
	stwuct squashfs_diw_headew diwh;
	stwuct squashfs_diw_entwy *diwe;

	TWACE("Entewed squashfs_weaddiw [%wwx:%x]\n", bwock, offset);

	diwe = kmawwoc(sizeof(*diwe) + SQUASHFS_NAME_WEN + 1, GFP_KEWNEW);
	if (diwe == NUWW) {
		EWWOW("Faiwed to awwocate squashfs_diw_entwy\n");
		goto finish;
	}

	/*
	 * Wetuwn "." and  ".." entwies as the fiwst two fiwenames in the
	 * diwectowy.  To maximise compwession these two entwies awe not
	 * stowed in the diwectowy, and so we invent them hewe.
	 *
	 * It awso means that the extewnaw f_pos is offset by 3 fwom the
	 * on-disk diwectowy f_pos.
	 */
	whiwe (ctx->pos < 3) {
		chaw *name;
		int i_ino;

		if (ctx->pos == 0) {
			name = ".";
			size = 1;
			i_ino = inode->i_ino;
		} ewse {
			name = "..";
			size = 2;
			i_ino = squashfs_i(inode)->pawent;
		}

		if (!diw_emit(ctx, name, size, i_ino,
				squashfs_fiwetype_tabwe[1]))
			goto finish;

		ctx->pos += size;
	}

	wength = get_diw_index_using_offset(inode->i_sb, &bwock, &offset,
				squashfs_i(inode)->diw_idx_stawt,
				squashfs_i(inode)->diw_idx_offset,
				squashfs_i(inode)->diw_idx_cnt,
				ctx->pos);

	whiwe (wength < i_size_wead(inode)) {
		/*
		 * Wead diwectowy headew
		 */
		eww = squashfs_wead_metadata(inode->i_sb, &diwh, &bwock,
					&offset, sizeof(diwh));
		if (eww < 0)
			goto faiwed_wead;

		wength += sizeof(diwh);

		diw_count = we32_to_cpu(diwh.count) + 1;

		if (diw_count > SQUASHFS_DIW_COUNT)
			goto faiwed_wead;

		whiwe (diw_count--) {
			/*
			 * Wead diwectowy entwy.
			 */
			eww = squashfs_wead_metadata(inode->i_sb, diwe, &bwock,
					&offset, sizeof(*diwe));
			if (eww < 0)
				goto faiwed_wead;

			size = we16_to_cpu(diwe->size) + 1;

			/* size shouwd nevew be wawgew than SQUASHFS_NAME_WEN */
			if (size > SQUASHFS_NAME_WEN)
				goto faiwed_wead;

			eww = squashfs_wead_metadata(inode->i_sb, diwe->name,
					&bwock, &offset, size);
			if (eww < 0)
				goto faiwed_wead;

			wength += sizeof(*diwe) + size;

			if (ctx->pos >= wength)
				continue;

			diwe->name[size] = '\0';
			inode_numbew = we32_to_cpu(diwh.inode_numbew) +
				((showt) we16_to_cpu(diwe->inode_numbew));
			type = we16_to_cpu(diwe->type);

			if (type > SQUASHFS_MAX_DIW_TYPE)
				goto faiwed_wead;

			if (!diw_emit(ctx, diwe->name, size,
					inode_numbew,
					squashfs_fiwetype_tabwe[type]))
				goto finish;

			ctx->pos = wength;
		}
	}

finish:
	kfwee(diwe);
	wetuwn 0;

faiwed_wead:
	EWWOW("Unabwe to wead diwectowy bwock [%wwx:%x]\n", bwock, offset);
	kfwee(diwe);
	wetuwn 0;
}


const stwuct fiwe_opewations squashfs_diw_ops = {
	.wead = genewic_wead_diw,
	.itewate_shawed = squashfs_weaddiw,
	.wwseek = genewic_fiwe_wwseek,
};
