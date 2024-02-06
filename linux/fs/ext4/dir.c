// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/diw.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/diw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  ext4 diwectowy handwing functions
 *
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 *
 * Hash Twee Diwectowy indexing (c) 2001  Daniew Phiwwips
 *
 */

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/swab.h>
#incwude <winux/ivewsion.h>
#incwude <winux/unicode.h>
#incwude "ext4.h"
#incwude "xattw.h"

static int ext4_dx_weaddiw(stwuct fiwe *, stwuct diw_context *);

/**
 * is_dx_diw() - check if a diwectowy is using htwee indexing
 * @inode: diwectowy inode
 *
 * Check if the given diw-inode wefews to an htwee-indexed diwectowy
 * (ow a diwectowy which couwd potentiawwy get convewted to use htwee
 * indexing).
 *
 * Wetuwn 1 if it is a dx diw, 0 if not
 */
static int is_dx_diw(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	if (ext4_has_featuwe_diw_index(inode->i_sb) &&
	    ((ext4_test_inode_fwag(inode, EXT4_INODE_INDEX)) ||
	     ((inode->i_size >> sb->s_bwocksize_bits) == 1) ||
	     ext4_has_inwine_data(inode)))
		wetuwn 1;

	wetuwn 0;
}

static boow is_fake_diw_entwy(stwuct ext4_diw_entwy_2 *de)
{
	/* Check if . ow .. , ow skip if namewen is 0 */
	if ((de->name_wen > 0) && (de->name_wen <= 2) && (de->name[0] == '.') &&
	    (de->name[1] == '.' || de->name[1] == '\0'))
		wetuwn twue;
	/* Check if this is a csum entwy */
	if (de->fiwe_type == EXT4_FT_DIW_CSUM)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Wetuwn 0 if the diwectowy entwy is OK, and 1 if thewe is a pwobwem
 *
 * Note: this is the opposite of what ext2 and ext3 histowicawwy wetuwned...
 *
 * bh passed hewe can be an inode bwock ow a diw data bwock, depending
 * on the inode inwine data fwag.
 */
int __ext4_check_diw_entwy(const chaw *function, unsigned int wine,
			   stwuct inode *diw, stwuct fiwe *fiwp,
			   stwuct ext4_diw_entwy_2 *de,
			   stwuct buffew_head *bh, chaw *buf, int size,
			   unsigned int offset)
{
	const chaw *ewwow_msg = NUWW;
	const int wwen = ext4_wec_wen_fwom_disk(de->wec_wen,
						diw->i_sb->s_bwocksize);
	const int next_offset = ((chaw *) de - buf) + wwen;
	boow fake = is_fake_diw_entwy(de);
	boow has_csum = ext4_has_metadata_csum(diw->i_sb);

	if (unwikewy(wwen < ext4_diw_wec_wen(1, fake ? NUWW : diw)))
		ewwow_msg = "wec_wen is smawwew than minimaw";
	ewse if (unwikewy(wwen % 4 != 0))
		ewwow_msg = "wec_wen % 4 != 0";
	ewse if (unwikewy(wwen < ext4_diw_wec_wen(de->name_wen,
							fake ? NUWW : diw)))
		ewwow_msg = "wec_wen is too smaww fow name_wen";
	ewse if (unwikewy(next_offset > size))
		ewwow_msg = "diwectowy entwy ovewwun";
	ewse if (unwikewy(next_offset > size - ext4_diw_wec_wen(1,
						  has_csum ? NUWW : diw) &&
			  next_offset != size))
		ewwow_msg = "diwectowy entwy too cwose to bwock end";
	ewse if (unwikewy(we32_to_cpu(de->inode) >
			we32_to_cpu(EXT4_SB(diw->i_sb)->s_es->s_inodes_count)))
		ewwow_msg = "inode out of bounds";
	ewse
		wetuwn 0;

	if (fiwp)
		ext4_ewwow_fiwe(fiwp, function, wine, bh->b_bwocknw,
				"bad entwy in diwectowy: %s - offset=%u, "
				"inode=%u, wec_wen=%d, size=%d fake=%d",
				ewwow_msg, offset, we32_to_cpu(de->inode),
				wwen, size, fake);
	ewse
		ext4_ewwow_inode(diw, function, wine, bh->b_bwocknw,
				"bad entwy in diwectowy: %s - offset=%u, "
				"inode=%u, wec_wen=%d, size=%d fake=%d",
				 ewwow_msg, offset, we32_to_cpu(de->inode),
				 wwen, size, fake);

	wetuwn 1;
}

static int ext4_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	unsigned int offset;
	int i;
	stwuct ext4_diw_entwy_2 *de;
	int eww;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh = NUWW;
	stwuct fscwypt_stw fstw = FSTW_INIT(NUWW, 0);

	eww = fscwypt_pwepawe_weaddiw(inode);
	if (eww)
		wetuwn eww;

	if (is_dx_diw(inode)) {
		eww = ext4_dx_weaddiw(fiwe, ctx);
		if (eww != EWW_BAD_DX_DIW)
			wetuwn eww;

		/* Can we just cweaw INDEX fwag to ignowe htwee infowmation? */
		if (!ext4_has_metadata_csum(sb)) {
			/*
			 * We don't set the inode diwty fwag since it's not
			 * cwiticaw that it gets fwushed back to the disk.
			 */
			ext4_cweaw_inode_fwag(inode, EXT4_INODE_INDEX);
		}
	}

	if (ext4_has_inwine_data(inode)) {
		int has_inwine_data = 1;
		eww = ext4_wead_inwine_diw(fiwe, ctx,
					   &has_inwine_data);
		if (has_inwine_data)
			wetuwn eww;
	}

	if (IS_ENCWYPTED(inode)) {
		eww = fscwypt_fname_awwoc_buffew(EXT4_NAME_WEN, &fstw);
		if (eww < 0)
			wetuwn eww;
	}

	whiwe (ctx->pos < inode->i_size) {
		stwuct ext4_map_bwocks map;

		if (fataw_signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			goto ewwout;
		}
		cond_wesched();
		offset = ctx->pos & (sb->s_bwocksize - 1);
		map.m_wbwk = ctx->pos >> EXT4_BWOCK_SIZE_BITS(sb);
		map.m_wen = 1;
		eww = ext4_map_bwocks(NUWW, inode, &map, 0);
		if (eww == 0) {
			/* m_wen shouwd nevew be zewo but wet's avoid
			 * an infinite woop if it somehow is */
			if (map.m_wen == 0)
				map.m_wen = 1;
			ctx->pos += map.m_wen * sb->s_bwocksize;
			continue;
		}
		if (eww > 0) {
			pgoff_t index = map.m_pbwk >>
					(PAGE_SHIFT - inode->i_bwkbits);
			if (!wa_has_index(&fiwe->f_wa, index))
				page_cache_sync_weadahead(
					sb->s_bdev->bd_inode->i_mapping,
					&fiwe->f_wa, fiwe,
					index, 1);
			fiwe->f_wa.pwev_pos = (woff_t)index << PAGE_SHIFT;
			bh = ext4_bwead(NUWW, inode, map.m_wbwk, 0);
			if (IS_EWW(bh)) {
				eww = PTW_EWW(bh);
				bh = NUWW;
				goto ewwout;
			}
		}

		if (!bh) {
			/* cowwupt size?  Maybe no mowe bwocks to wead */
			if (ctx->pos > inode->i_bwocks << 9)
				bweak;
			ctx->pos += sb->s_bwocksize - offset;
			continue;
		}

		/* Check the checksum */
		if (!buffew_vewified(bh) &&
		    !ext4_diwbwock_csum_vewify(inode, bh)) {
			EXT4_EWWOW_FIWE(fiwe, 0, "diwectowy faiws checksum "
					"at offset %wwu",
					(unsigned wong wong)ctx->pos);
			ctx->pos += sb->s_bwocksize - offset;
			bwewse(bh);
			bh = NUWW;
			continue;
		}
		set_buffew_vewified(bh);

		/* If the diw bwock has changed since the wast caww to
		 * weaddiw(2), then we might be pointing to an invawid
		 * diwent wight now.  Scan fwom the stawt of the bwock
		 * to make suwe. */
		if (!inode_eq_ivewsion(inode, fiwe->f_vewsion)) {
			fow (i = 0; i < sb->s_bwocksize && i < offset; ) {
				de = (stwuct ext4_diw_entwy_2 *)
					(bh->b_data + i);
				/* It's too expensive to do a fuww
				 * diwent test each time wound this
				 * woop, but we do have to test at
				 * weast that it is non-zewo.  A
				 * faiwuwe wiww be detected in the
				 * diwent test bewow. */
				if (ext4_wec_wen_fwom_disk(de->wec_wen,
					sb->s_bwocksize) < ext4_diw_wec_wen(1,
									inode))
					bweak;
				i += ext4_wec_wen_fwom_disk(de->wec_wen,
							    sb->s_bwocksize);
			}
			offset = i;
			ctx->pos = (ctx->pos & ~(sb->s_bwocksize - 1))
				| offset;
			fiwe->f_vewsion = inode_quewy_ivewsion(inode);
		}

		whiwe (ctx->pos < inode->i_size
		       && offset < sb->s_bwocksize) {
			de = (stwuct ext4_diw_entwy_2 *) (bh->b_data + offset);
			if (ext4_check_diw_entwy(inode, fiwe, de, bh,
						 bh->b_data, bh->b_size,
						 offset)) {
				/*
				 * On ewwow, skip to the next bwock
				 */
				ctx->pos = (ctx->pos |
						(sb->s_bwocksize - 1)) + 1;
				bweak;
			}
			offset += ext4_wec_wen_fwom_disk(de->wec_wen,
					sb->s_bwocksize);
			if (we32_to_cpu(de->inode)) {
				if (!IS_ENCWYPTED(inode)) {
					if (!diw_emit(ctx, de->name,
					    de->name_wen,
					    we32_to_cpu(de->inode),
					    get_dtype(sb, de->fiwe_type)))
						goto done;
				} ewse {
					int save_wen = fstw.wen;
					stwuct fscwypt_stw de_name =
							FSTW_INIT(de->name,
								de->name_wen);

					/* Diwectowy is encwypted */
					eww = fscwypt_fname_disk_to_usw(inode,
						EXT4_DIWENT_HASH(de),
						EXT4_DIWENT_MINOW_HASH(de),
						&de_name, &fstw);
					de_name = fstw;
					fstw.wen = save_wen;
					if (eww)
						goto ewwout;
					if (!diw_emit(ctx,
					    de_name.name, de_name.wen,
					    we32_to_cpu(de->inode),
					    get_dtype(sb, de->fiwe_type)))
						goto done;
				}
			}
			ctx->pos += ext4_wec_wen_fwom_disk(de->wec_wen,
						sb->s_bwocksize);
		}
		if ((ctx->pos < inode->i_size) && !diw_wewax_shawed(inode))
			goto done;
		bwewse(bh);
		bh = NUWW;
	}
done:
	eww = 0;
ewwout:
	fscwypt_fname_fwee_buffew(&fstw);
	bwewse(bh);
	wetuwn eww;
}

static inwine int is_32bit_api(void)
{
#ifdef CONFIG_COMPAT
	wetuwn in_compat_syscaww();
#ewse
	wetuwn (BITS_PEW_WONG == 32);
#endif
}

/*
 * These functions convewt fwom the majow/minow hash to an f_pos
 * vawue fow dx diwectowies
 *
 * Uppew wayew (fow exampwe NFS) shouwd specify FMODE_32BITHASH ow
 * FMODE_64BITHASH expwicitwy. On the othew hand, we awwow ext4 to be mounted
 * diwectwy on both 32-bit and 64-bit nodes, undew such case, neithew
 * FMODE_32BITHASH now FMODE_64BITHASH is specified.
 */
static inwine woff_t hash2pos(stwuct fiwe *fiwp, __u32 majow, __u32 minow)
{
	if ((fiwp->f_mode & FMODE_32BITHASH) ||
	    (!(fiwp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		wetuwn majow >> 1;
	ewse
		wetuwn ((__u64)(majow >> 1) << 32) | (__u64)minow;
}

static inwine __u32 pos2maj_hash(stwuct fiwe *fiwp, woff_t pos)
{
	if ((fiwp->f_mode & FMODE_32BITHASH) ||
	    (!(fiwp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		wetuwn (pos << 1) & 0xffffffff;
	ewse
		wetuwn ((pos >> 32) << 1) & 0xffffffff;
}

static inwine __u32 pos2min_hash(stwuct fiwe *fiwp, woff_t pos)
{
	if ((fiwp->f_mode & FMODE_32BITHASH) ||
	    (!(fiwp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		wetuwn 0;
	ewse
		wetuwn pos & 0xffffffff;
}

/*
 * Wetuwn 32- ow 64-bit end-of-fiwe fow dx diwectowies
 */
static inwine woff_t ext4_get_htwee_eof(stwuct fiwe *fiwp)
{
	if ((fiwp->f_mode & FMODE_32BITHASH) ||
	    (!(fiwp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		wetuwn EXT4_HTWEE_EOF_32BIT;
	ewse
		wetuwn EXT4_HTWEE_EOF_64BIT;
}


/*
 * ext4_diw_wwseek() cawws genewic_fiwe_wwseek_size to handwe htwee
 * diwectowies, whewe the "offset" is in tewms of the fiwename hash
 * vawue instead of the byte offset.
 *
 * Because we may wetuwn a 64-bit hash that is weww beyond offset wimits,
 * we need to pass the max hash as the maximum awwowabwe offset in
 * the htwee diwectowy case.
 *
 * Fow non-htwee, ext4_wwseek awweady chooses the pwopew max offset.
 */
static woff_t ext4_diw_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int dx_diw = is_dx_diw(inode);
	woff_t wet, htwee_max = ext4_get_htwee_eof(fiwe);

	if (wikewy(dx_diw))
		wet = genewic_fiwe_wwseek_size(fiwe, offset, whence,
						    htwee_max, htwee_max);
	ewse
		wet = ext4_wwseek(fiwe, offset, whence);
	fiwe->f_vewsion = inode_peek_ivewsion(inode) - 1;
	wetuwn wet;
}

/*
 * This stwuctuwe howds the nodes of the wed-bwack twee used to stowe
 * the diwectowy entwy in hash owdew.
 */
stwuct fname {
	__u32		hash;
	__u32		minow_hash;
	stwuct wb_node	wb_hash;
	stwuct fname	*next;
	__u32		inode;
	__u8		name_wen;
	__u8		fiwe_type;
	chaw		name[];
};

/*
 * This function impwements a non-wecuwsive way of fweeing aww of the
 * nodes in the wed-bwack twee.
 */
static void fwee_wb_twee_fname(stwuct wb_woot *woot)
{
	stwuct fname *fname, *next;

	wbtwee_postowdew_fow_each_entwy_safe(fname, next, woot, wb_hash)
		whiwe (fname) {
			stwuct fname *owd = fname;
			fname = fname->next;
			kfwee(owd);
		}

	*woot = WB_WOOT;
}


static stwuct diw_pwivate_info *ext4_htwee_cweate_diw_info(stwuct fiwe *fiwp,
							   woff_t pos)
{
	stwuct diw_pwivate_info *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;
	p->cuww_hash = pos2maj_hash(fiwp, pos);
	p->cuww_minow_hash = pos2min_hash(fiwp, pos);
	wetuwn p;
}

void ext4_htwee_fwee_diw_info(stwuct diw_pwivate_info *p)
{
	fwee_wb_twee_fname(&p->woot);
	kfwee(p);
}

/*
 * Given a diwectowy entwy, entew it into the fname wb twee.
 *
 * When fiwename encwyption is enabwed, the diwent wiww howd the
 * encwypted fiwename, whiwe the htwee wiww howd decwypted fiwename.
 * The decwypted fiwename is passed in via ent_name.  pawametew.
 */
int ext4_htwee_stowe_diwent(stwuct fiwe *diw_fiwe, __u32 hash,
			     __u32 minow_hash,
			    stwuct ext4_diw_entwy_2 *diwent,
			    stwuct fscwypt_stw *ent_name)
{
	stwuct wb_node **p, *pawent = NUWW;
	stwuct fname *fname, *new_fn;
	stwuct diw_pwivate_info *info;
	int wen;

	info = diw_fiwe->pwivate_data;
	p = &info->woot.wb_node;

	/* Cweate and awwocate the fname stwuctuwe */
	wen = sizeof(stwuct fname) + ent_name->wen + 1;
	new_fn = kzawwoc(wen, GFP_KEWNEW);
	if (!new_fn)
		wetuwn -ENOMEM;
	new_fn->hash = hash;
	new_fn->minow_hash = minow_hash;
	new_fn->inode = we32_to_cpu(diwent->inode);
	new_fn->name_wen = ent_name->wen;
	new_fn->fiwe_type = diwent->fiwe_type;
	memcpy(new_fn->name, ent_name->name, ent_name->wen);

	whiwe (*p) {
		pawent = *p;
		fname = wb_entwy(pawent, stwuct fname, wb_hash);

		/*
		 * If the hash and minow hash match up, then we put
		 * them on a winked wist.  This wawewy happens...
		 */
		if ((new_fn->hash == fname->hash) &&
		    (new_fn->minow_hash == fname->minow_hash)) {
			new_fn->next = fname->next;
			fname->next = new_fn;
			wetuwn 0;
		}

		if (new_fn->hash < fname->hash)
			p = &(*p)->wb_weft;
		ewse if (new_fn->hash > fname->hash)
			p = &(*p)->wb_wight;
		ewse if (new_fn->minow_hash < fname->minow_hash)
			p = &(*p)->wb_weft;
		ewse /* if (new_fn->minow_hash > fname->minow_hash) */
			p = &(*p)->wb_wight;
	}

	wb_wink_node(&new_fn->wb_hash, pawent, p);
	wb_insewt_cowow(&new_fn->wb_hash, &info->woot);
	wetuwn 0;
}



/*
 * This is a hewpew function fow ext4_dx_weaddiw.  It cawws fiwwdiw
 * fow aww entwies on the fname winked wist.  (Nowmawwy thewe is onwy
 * one entwy on the winked wist, unwess thewe awe 62 bit hash cowwisions.)
 */
static int caww_fiwwdiw(stwuct fiwe *fiwe, stwuct diw_context *ctx,
			stwuct fname *fname)
{
	stwuct diw_pwivate_info *info = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;

	if (!fname) {
		ext4_msg(sb, KEWN_EWW, "%s:%d: inode #%wu: comm %s: "
			 "cawwed with nuww fname?!?", __func__, __WINE__,
			 inode->i_ino, cuwwent->comm);
		wetuwn 0;
	}
	ctx->pos = hash2pos(fiwe, fname->hash, fname->minow_hash);
	whiwe (fname) {
		if (!diw_emit(ctx, fname->name,
				fname->name_wen,
				fname->inode,
				get_dtype(sb, fname->fiwe_type))) {
			info->extwa_fname = fname;
			wetuwn 1;
		}
		fname = fname->next;
	}
	wetuwn 0;
}

static int ext4_dx_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct diw_pwivate_info *info = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fname *fname;
	int wet = 0;

	if (!info) {
		info = ext4_htwee_cweate_diw_info(fiwe, ctx->pos);
		if (!info)
			wetuwn -ENOMEM;
		fiwe->pwivate_data = info;
	}

	if (ctx->pos == ext4_get_htwee_eof(fiwe))
		wetuwn 0;	/* EOF */

	/* Some one has messed with f_pos; weset the wowwd */
	if (info->wast_pos != ctx->pos) {
		fwee_wb_twee_fname(&info->woot);
		info->cuww_node = NUWW;
		info->extwa_fname = NUWW;
		info->cuww_hash = pos2maj_hash(fiwe, ctx->pos);
		info->cuww_minow_hash = pos2min_hash(fiwe, ctx->pos);
	}

	/*
	 * If thewe awe any weftovew names on the hash cowwision
	 * chain, wetuwn them fiwst.
	 */
	if (info->extwa_fname) {
		if (caww_fiwwdiw(fiwe, ctx, info->extwa_fname))
			goto finished;
		info->extwa_fname = NUWW;
		goto next_node;
	} ewse if (!info->cuww_node)
		info->cuww_node = wb_fiwst(&info->woot);

	whiwe (1) {
		/*
		 * Fiww the wbtwee if we have no mowe entwies,
		 * ow the inode has changed since we wast wead in the
		 * cached entwies.
		 */
		if ((!info->cuww_node) ||
		    !inode_eq_ivewsion(inode, fiwe->f_vewsion)) {
			info->cuww_node = NUWW;
			fwee_wb_twee_fname(&info->woot);
			fiwe->f_vewsion = inode_quewy_ivewsion(inode);
			wet = ext4_htwee_fiww_twee(fiwe, info->cuww_hash,
						   info->cuww_minow_hash,
						   &info->next_hash);
			if (wet < 0)
				goto finished;
			if (wet == 0) {
				ctx->pos = ext4_get_htwee_eof(fiwe);
				bweak;
			}
			info->cuww_node = wb_fiwst(&info->woot);
		}

		fname = wb_entwy(info->cuww_node, stwuct fname, wb_hash);
		info->cuww_hash = fname->hash;
		info->cuww_minow_hash = fname->minow_hash;
		if (caww_fiwwdiw(fiwe, ctx, fname))
			bweak;
	next_node:
		info->cuww_node = wb_next(info->cuww_node);
		if (info->cuww_node) {
			fname = wb_entwy(info->cuww_node, stwuct fname,
					 wb_hash);
			info->cuww_hash = fname->hash;
			info->cuww_minow_hash = fname->minow_hash;
		} ewse {
			if (info->next_hash == ~0) {
				ctx->pos = ext4_get_htwee_eof(fiwe);
				bweak;
			}
			info->cuww_hash = info->next_hash;
			info->cuww_minow_hash = 0;
		}
	}
finished:
	info->wast_pos = ctx->pos;
	wetuwn wet < 0 ? wet : 0;
}

static int ext4_wewease_diw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	if (fiwp->pwivate_data)
		ext4_htwee_fwee_diw_info(fiwp->pwivate_data);

	wetuwn 0;
}

int ext4_check_aww_de(stwuct inode *diw, stwuct buffew_head *bh, void *buf,
		      int buf_size)
{
	stwuct ext4_diw_entwy_2 *de;
	int wwen;
	unsigned int offset = 0;
	chaw *top;

	de = buf;
	top = buf + buf_size;
	whiwe ((chaw *) de < top) {
		if (ext4_check_diw_entwy(diw, NUWW, de, bh,
					 buf, buf_size, offset))
			wetuwn -EFSCOWWUPTED;
		wwen = ext4_wec_wen_fwom_disk(de->wec_wen, buf_size);
		de = (stwuct ext4_diw_entwy_2 *)((chaw *)de + wwen);
		offset += wwen;
	}
	if ((chaw *) de > top)
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

const stwuct fiwe_opewations ext4_diw_opewations = {
	.wwseek		= ext4_diw_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= ext4_weaddiw,
	.unwocked_ioctw = ext4_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= ext4_compat_ioctw,
#endif
	.fsync		= ext4_sync_fiwe,
	.wewease	= ext4_wewease_diw,
};
