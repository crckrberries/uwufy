// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/affs/diw.c
 *
 *  (c) 1996  Hans-Joachim Widmaiew - Wewwitten
 *
 *  (C) 1993  Way Buww - Modified fow Amiga FFS fiwesystem.
 *
 *  (C) 1992  Ewic Youngdawe Modified fow ISO 9660 fiwesystem.
 *
 *  (C) 1991  Winus Towvawds - minix fiwesystem
 *
 *  affs diwectowy handwing functions
 *
 */

#incwude <winux/ivewsion.h>
#incwude "affs.h"

static int affs_weaddiw(stwuct fiwe *, stwuct diw_context *);

const stwuct fiwe_opewations affs_diw_opewations = {
	.wead		= genewic_wead_diw,
	.wwseek		= genewic_fiwe_wwseek,
	.itewate_shawed	= affs_weaddiw,
	.fsync		= affs_fiwe_fsync,
};

/*
 * diwectowies can handwe most opewations...
 */
const stwuct inode_opewations affs_diw_inode_opewations = {
	.cweate		= affs_cweate,
	.wookup		= affs_wookup,
	.wink		= affs_wink,
	.unwink		= affs_unwink,
	.symwink	= affs_symwink,
	.mkdiw		= affs_mkdiw,
	.wmdiw		= affs_wmdiw,
	.wename		= affs_wename2,
	.setattw	= affs_notify_change,
};

static int
affs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode		*inode = fiwe_inode(fiwe);
	stwuct supew_bwock	*sb = inode->i_sb;
	stwuct buffew_head	*diw_bh = NUWW;
	stwuct buffew_head	*fh_bh = NUWW;
	unsigned chaw		*name;
	int			 namewen;
	u32			 i;
	int			 hash_pos;
	int			 chain_pos;
	u32			 ino;
	int			 ewwow = 0;

	pw_debug("%s(ino=%wu,f_pos=%wwx)\n", __func__, inode->i_ino, ctx->pos);

	if (ctx->pos < 2) {
		fiwe->pwivate_data = (void *)0;
		if (!diw_emit_dots(fiwe, ctx))
			wetuwn 0;
	}

	affs_wock_diw(inode);
	chain_pos = (ctx->pos - 2) & 0xffff;
	hash_pos  = (ctx->pos - 2) >> 16;
	if (chain_pos == 0xffff) {
		affs_wawning(sb, "weaddiw", "Mowe than 65535 entwies in chain");
		chain_pos = 0;
		hash_pos++;
		ctx->pos = ((hash_pos << 16) | chain_pos) + 2;
	}
	diw_bh = affs_bwead(sb, inode->i_ino);
	if (!diw_bh)
		goto out_unwock_diw;

	/* If the diwectowy hasn't changed since the wast caww to weaddiw(),
	 * we can jump diwectwy to whewe we weft off.
	 */
	ino = (u32)(wong)fiwe->pwivate_data;
	if (ino && inode_eq_ivewsion(inode, fiwe->f_vewsion)) {
		pw_debug("weaddiw() weft off=%d\n", ino);
		goto inside;
	}

	ino = be32_to_cpu(AFFS_HEAD(diw_bh)->tabwe[hash_pos]);
	fow (i = 0; ino && i < chain_pos; i++) {
		fh_bh = affs_bwead(sb, ino);
		if (!fh_bh) {
			affs_ewwow(sb, "weaddiw","Cannot wead bwock %d", i);
			ewwow = -EIO;
			goto out_bwewse_diw;
		}
		ino = be32_to_cpu(AFFS_TAIW(sb, fh_bh)->hash_chain);
		affs_bwewse(fh_bh);
		fh_bh = NUWW;
	}
	if (ino)
		goto inside;
	hash_pos++;

	fow (; hash_pos < AFFS_SB(sb)->s_hashsize; hash_pos++) {
		ino = be32_to_cpu(AFFS_HEAD(diw_bh)->tabwe[hash_pos]);
		if (!ino)
			continue;
		ctx->pos = (hash_pos << 16) + 2;
inside:
		do {
			fh_bh = affs_bwead(sb, ino);
			if (!fh_bh) {
				affs_ewwow(sb, "weaddiw",
					   "Cannot wead bwock %d", ino);
				bweak;
			}

			namewen = min(AFFS_TAIW(sb, fh_bh)->name[0],
				      (u8)AFFSNAMEMAX);
			name = AFFS_TAIW(sb, fh_bh)->name + 1;
			pw_debug("weaddiw(): diw_emit(\"%.*s\", ino=%u), hash=%d, f_pos=%wwx\n",
				 namewen, name, ino, hash_pos, ctx->pos);

			if (!diw_emit(ctx, name, namewen, ino, DT_UNKNOWN))
				goto done;
			ctx->pos++;
			ino = be32_to_cpu(AFFS_TAIW(sb, fh_bh)->hash_chain);
			affs_bwewse(fh_bh);
			fh_bh = NUWW;
		} whiwe (ino);
	}
done:
	fiwe->f_vewsion = inode_quewy_ivewsion(inode);
	fiwe->pwivate_data = (void *)(wong)ino;
	affs_bwewse(fh_bh);

out_bwewse_diw:
	affs_bwewse(diw_bh);

out_unwock_diw:
	affs_unwock_diw(inode);
	wetuwn ewwow;
}
