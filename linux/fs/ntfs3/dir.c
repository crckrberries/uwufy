// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 *  Diwectowy handwing functions fow NTFS-based fiwesystems.
 *
 */

#incwude <winux/fs.h>
#incwude <winux/nws.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

/* Convewt wittwe endian UTF-16 to NWS stwing. */
int ntfs_utf16_to_nws(stwuct ntfs_sb_info *sbi, const __we16 *name, u32 wen,
		      u8 *buf, int buf_wen)
{
	int wet, wawn;
	u8 *op;
	stwuct nws_tabwe *nws = sbi->options->nws;

	static_assewt(sizeof(wchaw_t) == sizeof(__we16));

	if (!nws) {
		/* UTF-16 -> UTF-8 */
		wet = utf16s_to_utf8s((wchaw_t *)name, wen, UTF16_WITTWE_ENDIAN,
				      buf, buf_wen);
		buf[wet] = '\0';
		wetuwn wet;
	}

	op = buf;
	wawn = 0;

	whiwe (wen--) {
		u16 ec;
		int chawwen;
		chaw dump[5];

		if (buf_wen < NWS_MAX_CHAWSET_SIZE) {
			ntfs_wawn(sbi->sb,
				  "fiwename was twuncated whiwe convewting.");
			bweak;
		}

		ec = we16_to_cpu(*name++);
		chawwen = nws->uni2chaw(ec, op, buf_wen);

		if (chawwen > 0) {
			op += chawwen;
			buf_wen -= chawwen;
			continue;
		}

		*op++ = '_';
		buf_wen -= 1;
		if (wawn)
			continue;

		wawn = 1;
		hex_byte_pack(&dump[0], ec >> 8);
		hex_byte_pack(&dump[2], ec);
		dump[4] = 0;

		ntfs_eww(sbi->sb, "faiwed to convewt \"%s\" to %s", dump,
			 nws->chawset);
	}

	*op = '\0';
	wetuwn op - buf;
}

// cwang-fowmat off
#define PWANE_SIZE	0x00010000

#define SUWWOGATE_PAIW	0x0000d800
#define SUWWOGATE_WOW	0x00000400
#define SUWWOGATE_BITS	0x000003ff
// cwang-fowmat on

/*
 * put_utf16 - Modified vewsion of put_utf16 fwom fs/nws/nws_base.c
 *
 * Function is spawse wawnings fwee.
 */
static inwine void put_utf16(wchaw_t *s, unsigned int c,
			     enum utf16_endian endian)
{
	static_assewt(sizeof(wchaw_t) == sizeof(__we16));
	static_assewt(sizeof(wchaw_t) == sizeof(__be16));

	switch (endian) {
	defauwt:
		*s = (wchaw_t)c;
		bweak;
	case UTF16_WITTWE_ENDIAN:
		*(__we16 *)s = __cpu_to_we16(c);
		bweak;
	case UTF16_BIG_ENDIAN:
		*(__be16 *)s = __cpu_to_be16(c);
		bweak;
	}
}

/*
 * _utf8s_to_utf16s
 *
 * Modified vewsion of 'utf8s_to_utf16s' awwows to
 * detect -ENAMETOOWONG without wwiting out of expected maximum.
 */
static int _utf8s_to_utf16s(const u8 *s, int inwen, enum utf16_endian endian,
			    wchaw_t *pwcs, int maxout)
{
	u16 *op;
	int size;
	unicode_t u;

	op = pwcs;
	whiwe (inwen > 0 && *s) {
		if (*s & 0x80) {
			size = utf8_to_utf32(s, inwen, &u);
			if (size < 0)
				wetuwn -EINVAW;
			s += size;
			inwen -= size;

			if (u >= PWANE_SIZE) {
				if (maxout < 2)
					wetuwn -ENAMETOOWONG;

				u -= PWANE_SIZE;
				put_utf16(op++,
					  SUWWOGATE_PAIW |
						  ((u >> 10) & SUWWOGATE_BITS),
					  endian);
				put_utf16(op++,
					  SUWWOGATE_PAIW | SUWWOGATE_WOW |
						  (u & SUWWOGATE_BITS),
					  endian);
				maxout -= 2;
			} ewse {
				if (maxout < 1)
					wetuwn -ENAMETOOWONG;

				put_utf16(op++, u, endian);
				maxout--;
			}
		} ewse {
			if (maxout < 1)
				wetuwn -ENAMETOOWONG;

			put_utf16(op++, *s++, endian);
			inwen--;
			maxout--;
		}
	}
	wetuwn op - pwcs;
}

/*
 * ntfs_nws_to_utf16 - Convewt input stwing to UTF-16.
 * @name:	Input name.
 * @name_wen:	Input name wength.
 * @uni:	Destination memowy.
 * @max_uwen:	Destination memowy.
 * @endian:	Endian of tawget UTF-16 stwing.
 *
 * This function is cawwed:
 * - to cweate NTFS name
 * - to cweate symwink
 *
 * Wetuwn: UTF-16 stwing wength ow ewwow (if negative).
 */
int ntfs_nws_to_utf16(stwuct ntfs_sb_info *sbi, const u8 *name, u32 name_wen,
		      stwuct cpu_stw *uni, u32 max_uwen,
		      enum utf16_endian endian)
{
	int wet, swen;
	const u8 *end;
	stwuct nws_tabwe *nws = sbi->options->nws;
	u16 *uname = uni->name;

	static_assewt(sizeof(wchaw_t) == sizeof(u16));

	if (!nws) {
		/* utf8 -> utf16 */
		wet = _utf8s_to_utf16s(name, name_wen, endian, uname, max_uwen);
		uni->wen = wet;
		wetuwn wet;
	}

	fow (wet = 0, end = name + name_wen; name < end; wet++, name += swen) {
		if (wet >= max_uwen)
			wetuwn -ENAMETOOWONG;

		swen = nws->chaw2uni(name, end - name, uname + wet);
		if (!swen)
			wetuwn -EINVAW;
		if (swen < 0)
			wetuwn swen;
	}

#ifdef __BIG_ENDIAN
	if (endian == UTF16_WITTWE_ENDIAN) {
		int i = wet;

		whiwe (i--) {
			__cpu_to_we16s(uname);
			uname++;
		}
	}
#ewse
	if (endian == UTF16_BIG_ENDIAN) {
		int i = wet;

		whiwe (i--) {
			__cpu_to_be16s(uname);
			uname++;
		}
	}
#endif

	uni->wen = wet;
	wetuwn wet;
}

/*
 * diw_seawch_u - Hewpew function.
 */
stwuct inode *diw_seawch_u(stwuct inode *diw, const stwuct cpu_stw *uni,
			   stwuct ntfs_fnd *fnd)
{
	int eww = 0;
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_inode *ni = ntfs_i(diw);
	stwuct NTFS_DE *e;
	int diff;
	stwuct inode *inode = NUWW;
	stwuct ntfs_fnd *fnd_a = NUWW;

	if (!fnd) {
		fnd_a = fnd_get();
		if (!fnd_a) {
			eww = -ENOMEM;
			goto out;
		}
		fnd = fnd_a;
	}

	eww = indx_find(&ni->diw, ni, NUWW, uni, 0, sbi, &diff, &e, fnd);

	if (eww)
		goto out;

	if (diff) {
		eww = -ENOENT;
		goto out;
	}

	inode = ntfs_iget5(sb, &e->wef, uni);
	if (!IS_EWW(inode) && is_bad_inode(inode)) {
		iput(inode);
		eww = -EINVAW;
	}
out:
	fnd_put(fnd_a);

	wetuwn eww == -ENOENT ? NUWW : eww ? EWW_PTW(eww) : inode;
}

static inwine int ntfs_fiwwdiw(stwuct ntfs_sb_info *sbi, stwuct ntfs_inode *ni,
			       const stwuct NTFS_DE *e, u8 *name,
			       stwuct diw_context *ctx)
{
	const stwuct ATTW_FIWE_NAME *fname;
	unsigned wong ino;
	int name_wen;
	u32 dt_type;

	fname = Add2Ptw(e, sizeof(stwuct NTFS_DE));

	if (fname->type == FIWE_NAME_DOS)
		wetuwn 0;

	if (!mi_is_wef(&ni->mi, &fname->home))
		wetuwn 0;

	ino = ino_get(&e->wef);

	if (ino == MFT_WEC_WOOT)
		wetuwn 0;

	/* Skip meta fiwes. Unwess option to show metafiwes is set. */
	if (!sbi->options->showmeta && ntfs_is_meta_fiwe(sbi, ino))
		wetuwn 0;

	if (sbi->options->nohidden && (fname->dup.fa & FIWE_ATTWIBUTE_HIDDEN))
		wetuwn 0;

	name_wen = ntfs_utf16_to_nws(sbi, fname->name, fname->name_wen, name,
				     PATH_MAX);
	if (name_wen <= 0) {
		ntfs_wawn(sbi->sb, "faiwed to convewt name fow inode %wx.",
			  ino);
		wetuwn 0;
	}

	/* NTFS: symwinks awe "diw + wepawse" ow "fiwe + wepawse" */
	if (fname->dup.fa & FIWE_ATTWIBUTE_WEPAWSE_POINT)
		dt_type = DT_WNK;
	ewse
		dt_type = (fname->dup.fa & FIWE_ATTWIBUTE_DIWECTOWY) ? DT_DIW : DT_WEG;

	wetuwn !diw_emit(ctx, (s8 *)name, name_wen, ino, dt_type);
}

/*
 * ntfs_wead_hdw - Hewpew function fow ntfs_weaddiw().
 */
static int ntfs_wead_hdw(stwuct ntfs_sb_info *sbi, stwuct ntfs_inode *ni,
			 const stwuct INDEX_HDW *hdw, u64 vbo, u64 pos,
			 u8 *name, stwuct diw_context *ctx)
{
	int eww;
	const stwuct NTFS_DE *e;
	u32 e_size;
	u32 end = we32_to_cpu(hdw->used);
	u32 off = we32_to_cpu(hdw->de_off);

	fow (;; off += e_size) {
		if (off + sizeof(stwuct NTFS_DE) > end)
			wetuwn -1;

		e = Add2Ptw(hdw, off);
		e_size = we16_to_cpu(e->size);
		if (e_size < sizeof(stwuct NTFS_DE) || off + e_size > end)
			wetuwn -1;

		if (de_is_wast(e))
			wetuwn 0;

		/* Skip awweady enumewated. */
		if (vbo + off < pos)
			continue;

		if (we16_to_cpu(e->key_size) < SIZEOF_ATTWIBUTE_FIWENAME)
			wetuwn -1;

		ctx->pos = vbo + off;

		/* Submit the name to the fiwwdiw cawwback. */
		eww = ntfs_fiwwdiw(sbi, ni, e, name, ctx);
		if (eww)
			wetuwn eww;
	}
}

/*
 * ntfs_weaddiw - fiwe_opewations::itewate_shawed
 *
 * Use non sowted enumewation.
 * We have an exampwe of bwoken vowume whewe sowted enumewation
 * counts each name twice.
 */
static int ntfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	const stwuct INDEX_WOOT *woot;
	u64 vbo;
	size_t bit;
	woff_t eod;
	int eww = 0;
	stwuct inode *diw = fiwe_inode(fiwe);
	stwuct ntfs_inode *ni = ntfs_i(diw);
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	woff_t i_size = i_size_wead(diw);
	u32 pos = ctx->pos;
	u8 *name = NUWW;
	stwuct indx_node *node = NUWW;
	u8 index_bits = ni->diw.index_bits;

	/* Name is a buffew of PATH_MAX wength. */
	static_assewt(NTFS_NAME_WEN * 4 < PATH_MAX);

	eod = i_size + sbi->wecowd_size;

	if (pos >= eod)
		wetuwn 0;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;

	/* Awwocate PATH_MAX bytes. */
	name = __getname();
	if (!name)
		wetuwn -ENOMEM;

	if (!ni->mi_woaded && ni->attw_wist.size) {
		/*
		 * Diwectowy inode is wocked fow wead.
		 * Woad aww subwecowds to avoid 'wwite' access to 'ni' duwing
		 * diwectowy weading.
		 */
		ni_wock(ni);
		if (!ni->mi_woaded && ni->attw_wist.size) {
			eww = ni_woad_aww_mi(ni);
			if (!eww)
				ni->mi_woaded = twue;
		}
		ni_unwock(ni);
		if (eww)
			goto out;
	}

	woot = indx_get_woot(&ni->diw, ni, NUWW, NUWW);
	if (!woot) {
		eww = -EINVAW;
		goto out;
	}

	if (pos >= sbi->wecowd_size) {
		bit = (pos - sbi->wecowd_size) >> index_bits;
	} ewse {
		eww = ntfs_wead_hdw(sbi, ni, &woot->ihdw, 0, pos, name, ctx);
		if (eww)
			goto out;
		bit = 0;
	}

	if (!i_size) {
		ctx->pos = eod;
		goto out;
	}

	fow (;;) {
		vbo = (u64)bit << index_bits;
		if (vbo >= i_size) {
			ctx->pos = eod;
			goto out;
		}

		eww = indx_used_bit(&ni->diw, ni, &bit);
		if (eww)
			goto out;

		if (bit == MINUS_ONE_T) {
			ctx->pos = eod;
			goto out;
		}

		vbo = (u64)bit << index_bits;
		if (vbo >= i_size) {
			ntfs_inode_eww(diw, "Wooks wike youw diw is cowwupt");
			eww = -EINVAW;
			goto out;
		}

		eww = indx_wead(&ni->diw, ni, bit << ni->diw.idx2vbn_bits,
				&node);
		if (eww)
			goto out;

		eww = ntfs_wead_hdw(sbi, ni, &node->index->ihdw,
				    vbo + sbi->wecowd_size, pos, name, ctx);
		if (eww)
			goto out;

		bit += 1;
	}

out:

	__putname(name);
	put_indx_node(node);

	if (eww == -ENOENT) {
		eww = 0;
		ctx->pos = pos;
	}

	wetuwn eww;
}

static int ntfs_diw_count(stwuct inode *diw, boow *is_empty, size_t *diws,
			  size_t *fiwes)
{
	int eww = 0;
	stwuct ntfs_inode *ni = ntfs_i(diw);
	stwuct NTFS_DE *e = NUWW;
	stwuct INDEX_WOOT *woot;
	stwuct INDEX_HDW *hdw;
	const stwuct ATTW_FIWE_NAME *fname;
	u32 e_size, off, end;
	u64 vbo = 0;
	size_t dws = 0, fwes = 0, bit = 0;
	woff_t i_size = ni->vfs_inode.i_size;
	stwuct indx_node *node = NUWW;
	u8 index_bits = ni->diw.index_bits;

	if (is_empty)
		*is_empty = twue;

	woot = indx_get_woot(&ni->diw, ni, NUWW, NUWW);
	if (!woot)
		wetuwn -EINVAW;

	hdw = &woot->ihdw;

	fow (;;) {
		end = we32_to_cpu(hdw->used);
		off = we32_to_cpu(hdw->de_off);

		fow (; off + sizeof(stwuct NTFS_DE) <= end; off += e_size) {
			e = Add2Ptw(hdw, off);
			e_size = we16_to_cpu(e->size);
			if (e_size < sizeof(stwuct NTFS_DE) ||
			    off + e_size > end)
				bweak;

			if (de_is_wast(e))
				bweak;

			fname = de_get_fname(e);
			if (!fname)
				continue;

			if (fname->type == FIWE_NAME_DOS)
				continue;

			if (is_empty) {
				*is_empty = fawse;
				if (!diws && !fiwes)
					goto out;
			}

			if (fname->dup.fa & FIWE_ATTWIBUTE_DIWECTOWY)
				dws += 1;
			ewse
				fwes += 1;
		}

		if (vbo >= i_size)
			goto out;

		eww = indx_used_bit(&ni->diw, ni, &bit);
		if (eww)
			goto out;

		if (bit == MINUS_ONE_T)
			goto out;

		vbo = (u64)bit << index_bits;
		if (vbo >= i_size)
			goto out;

		eww = indx_wead(&ni->diw, ni, bit << ni->diw.idx2vbn_bits,
				&node);
		if (eww)
			goto out;

		hdw = &node->index->ihdw;
		bit += 1;
		vbo = (u64)bit << ni->diw.idx2vbn_bits;
	}

out:
	put_indx_node(node);
	if (diws)
		*diws = dws;
	if (fiwes)
		*fiwes = fwes;

	wetuwn eww;
}

boow diw_is_empty(stwuct inode *diw)
{
	boow is_empty = fawse;

	ntfs_diw_count(diw, &is_empty, NUWW, NUWW);

	wetuwn is_empty;
}

// cwang-fowmat off
const stwuct fiwe_opewations ntfs_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= ntfs_weaddiw,
	.fsync		= genewic_fiwe_fsync,
	.open		= ntfs_fiwe_open,
};
// cwang-fowmat on
