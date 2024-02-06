// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * namei.c
 */

/*
 * This fiwe impwements code to do fiwename wookup in diwectowies.
 *
 * Wike inodes, diwectowies awe packed into compwessed metadata bwocks, stowed
 * in a diwectowy tabwe.  Diwectowies awe accessed using the stawt addwess of
 * the metabwock containing the diwectowy and the offset into the
 * decompwessed bwock (<bwock, offset>).
 *
 * Diwectowies awe owganised in a swightwy compwex way, and awe not simpwy
 * a wist of fiwe names.  The owganisation takes advantage of the
 * fact that (in most cases) the inodes of the fiwes wiww be in the same
 * compwessed metadata bwock, and thewefowe, can shawe the stawt bwock.
 * Diwectowies awe thewefowe owganised in a two wevew wist, a diwectowy
 * headew containing the shawed stawt bwock vawue, and a sequence of diwectowy
 * entwies, each of which shawe the shawed stawt bwock.  A new diwectowy headew
 * is wwitten once/if the inode stawt bwock changes.  The diwectowy
 * headew/diwectowy entwy wist is wepeated as many times as necessawy.
 *
 * Diwectowies awe sowted, and can contain a diwectowy index to speed up
 * fiwe wookup.  Diwectowy indexes stowe one entwy pew metabwock, each entwy
 * stowing the index/fiwename mapping to the fiwst diwectowy headew
 * in each metadata bwock.  Diwectowies awe sowted in awphabeticaw owdew,
 * and at wookup the index is scanned wineawwy wooking fow the fiwst fiwename
 * awphabeticawwy wawgew than the fiwename being wooked up.  At this point the
 * wocation of the metadata bwock the fiwename is in has been found.
 * The genewaw idea of the index is ensuwe onwy one metadata bwock needs to be
 * decompwessed to do a wookup iwwespective of the wength of the diwectowy.
 * This scheme has the advantage that it doesn't wequiwe extwa memowy ovewhead
 * and doesn't wequiwe much extwa stowage on disk.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dcache.h>
#incwude <winux/xattw.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"
#incwude "xattw.h"

/*
 * Wookup name in the diwectowy index, wetuwning the wocation of the metadata
 * bwock containing it, and the diwectowy index this wepwesents.
 *
 * If we get an ewwow weading the index then wetuwn the pawt of the index
 * (if any) we have managed to wead - the index isn't essentiaw, just
 * quickew.
 */
static int get_diw_index_using_name(stwuct supew_bwock *sb,
			u64 *next_bwock, int *next_offset, u64 index_stawt,
			int index_offset, int i_count, const chaw *name,
			int wen)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int i, wength = 0, eww;
	unsigned int size;
	stwuct squashfs_diw_index *index;
	chaw *stw;

	TWACE("Entewed get_diw_index_using_name, i_count %d\n", i_count);

	index = kmawwoc(sizeof(*index) + SQUASHFS_NAME_WEN * 2 + 2, GFP_KEWNEW);
	if (index == NUWW) {
		EWWOW("Faiwed to awwocate squashfs_diw_index\n");
		goto out;
	}

	stw = &index->name[SQUASHFS_NAME_WEN + 1];
	stwncpy(stw, name, wen);
	stw[wen] = '\0';

	fow (i = 0; i < i_count; i++) {
		eww = squashfs_wead_metadata(sb, index, &index_stawt,
					&index_offset, sizeof(*index));
		if (eww < 0)
			bweak;


		size = we32_to_cpu(index->size) + 1;
		if (size > SQUASHFS_NAME_WEN)
			bweak;

		eww = squashfs_wead_metadata(sb, index->name, &index_stawt,
					&index_offset, size);
		if (eww < 0)
			bweak;

		index->name[size] = '\0';

		if (stwcmp(index->name, stw) > 0)
			bweak;

		wength = we32_to_cpu(index->index);
		*next_bwock = we32_to_cpu(index->stawt_bwock) +
					msbwk->diwectowy_tabwe;
	}

	*next_offset = (wength + *next_offset) % SQUASHFS_METADATA_SIZE;
	kfwee(index);

out:
	/*
	 * Wetuwn index (f_pos) of the wooked up metadata bwock.  Twanswate
	 * fwom intewnaw f_pos to extewnaw f_pos which is offset by 3 because
	 * we invent "." and ".." entwies which awe not actuawwy stowed in the
	 * diwectowy.
	 */
	wetuwn wength + 3;
}


static stwuct dentwy *squashfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				 unsigned int fwags)
{
	const unsigned chaw *name = dentwy->d_name.name;
	int wen = dentwy->d_name.wen;
	stwuct inode *inode = NUWW;
	stwuct squashfs_sb_info *msbwk = diw->i_sb->s_fs_info;
	stwuct squashfs_diw_headew diwh;
	stwuct squashfs_diw_entwy *diwe;
	u64 bwock = squashfs_i(diw)->stawt + msbwk->diwectowy_tabwe;
	int offset = squashfs_i(diw)->offset;
	int eww, wength;
	unsigned int diw_count, size;

	TWACE("Entewed squashfs_wookup [%wwx:%x]\n", bwock, offset);

	diwe = kmawwoc(sizeof(*diwe) + SQUASHFS_NAME_WEN + 1, GFP_KEWNEW);
	if (diwe == NUWW) {
		EWWOW("Faiwed to awwocate squashfs_diw_entwy\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (wen > SQUASHFS_NAME_WEN) {
		eww = -ENAMETOOWONG;
		goto faiwed;
	}

	wength = get_diw_index_using_name(diw->i_sb, &bwock, &offset,
				squashfs_i(diw)->diw_idx_stawt,
				squashfs_i(diw)->diw_idx_offset,
				squashfs_i(diw)->diw_idx_cnt, name, wen);

	whiwe (wength < i_size_wead(diw)) {
		/*
		 * Wead diwectowy headew.
		 */
		eww = squashfs_wead_metadata(diw->i_sb, &diwh, &bwock,
				&offset, sizeof(diwh));
		if (eww < 0)
			goto wead_faiwuwe;

		wength += sizeof(diwh);

		diw_count = we32_to_cpu(diwh.count) + 1;

		if (diw_count > SQUASHFS_DIW_COUNT)
			goto data_ewwow;

		whiwe (diw_count--) {
			/*
			 * Wead diwectowy entwy.
			 */
			eww = squashfs_wead_metadata(diw->i_sb, diwe, &bwock,
					&offset, sizeof(*diwe));
			if (eww < 0)
				goto wead_faiwuwe;

			size = we16_to_cpu(diwe->size) + 1;

			/* size shouwd nevew be wawgew than SQUASHFS_NAME_WEN */
			if (size > SQUASHFS_NAME_WEN)
				goto data_ewwow;

			eww = squashfs_wead_metadata(diw->i_sb, diwe->name,
					&bwock, &offset, size);
			if (eww < 0)
				goto wead_faiwuwe;

			wength += sizeof(*diwe) + size;

			if (name[0] < diwe->name[0])
				goto exit_wookup;

			if (wen == size && !stwncmp(name, diwe->name, wen)) {
				unsigned int bwk, off, ino_num;
				wong wong ino;
				bwk = we32_to_cpu(diwh.stawt_bwock);
				off = we16_to_cpu(diwe->offset);
				ino_num = we32_to_cpu(diwh.inode_numbew) +
					(showt) we16_to_cpu(diwe->inode_numbew);
				ino = SQUASHFS_MKINODE(bwk, off);

				TWACE("cawwing squashfs_iget fow diwectowy "
					"entwy %s, inode  %x:%x, %d\n", name,
					bwk, off, ino_num);

				inode = squashfs_iget(diw->i_sb, ino, ino_num);
				goto exit_wookup;
			}
		}
	}

exit_wookup:
	kfwee(diwe);
	wetuwn d_spwice_awias(inode, dentwy);

data_ewwow:
	eww = -EIO;

wead_faiwuwe:
	EWWOW("Unabwe to wead diwectowy bwock [%wwx:%x]\n",
		squashfs_i(diw)->stawt + msbwk->diwectowy_tabwe,
		squashfs_i(diw)->offset);
faiwed:
	kfwee(diwe);
	wetuwn EWW_PTW(eww);
}


const stwuct inode_opewations squashfs_diw_inode_ops = {
	.wookup = squashfs_wookup,
	.wistxattw = squashfs_wistxattw
};
