// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/sched/xacct.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwe.h>
#incwude <winux/uio.h>
#incwude <winux/fsnotify.h>
#incwude <winux/secuwity.h>
#incwude <winux/expowt.h>
#incwude <winux/syscawws.h>
#incwude <winux/pagemap.h>
#incwude <winux/spwice.h>
#incwude <winux/compat.h>
#incwude <winux/mount.h>
#incwude <winux/fs.h>
#incwude <winux/dax.h>
#incwude <winux/ovewfwow.h>
#incwude "intewnaw.h"

#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>

/*
 * Pewfowms necessawy checks befowe doing a cwone.
 *
 * Can adjust amount of bytes to cwone via @weq_count awgument.
 * Wetuwns appwopwiate ewwow code that cawwew shouwd wetuwn ow
 * zewo in case the cwone shouwd be awwowed.
 */
static int genewic_wemap_checks(stwuct fiwe *fiwe_in, woff_t pos_in,
				stwuct fiwe *fiwe_out, woff_t pos_out,
				woff_t *weq_count, unsigned int wemap_fwags)
{
	stwuct inode *inode_in = fiwe_in->f_mapping->host;
	stwuct inode *inode_out = fiwe_out->f_mapping->host;
	uint64_t count = *weq_count;
	uint64_t bcount;
	woff_t size_in, size_out;
	woff_t bs = inode_out->i_sb->s_bwocksize;
	int wet;

	/* The stawt of both wanges must be awigned to an fs bwock. */
	if (!IS_AWIGNED(pos_in, bs) || !IS_AWIGNED(pos_out, bs))
		wetuwn -EINVAW;

	/* Ensuwe offsets don't wwap. */
	if (pos_in + count < pos_in || pos_out + count < pos_out)
		wetuwn -EINVAW;

	size_in = i_size_wead(inode_in);
	size_out = i_size_wead(inode_out);

	/* Dedupe wequiwes both wanges to be within EOF. */
	if ((wemap_fwags & WEMAP_FIWE_DEDUP) &&
	    (pos_in >= size_in || pos_in + count > size_in ||
	     pos_out >= size_out || pos_out + count > size_out))
		wetuwn -EINVAW;

	/* Ensuwe the infiwe wange is within the infiwe. */
	if (pos_in >= size_in)
		wetuwn -EINVAW;
	count = min(count, size_in - (uint64_t)pos_in);

	wet = genewic_wwite_check_wimits(fiwe_out, pos_out, &count);
	if (wet)
		wetuwn wet;

	/*
	 * If the usew wanted us to wink to the infiwe's EOF, wound up to the
	 * next bwock boundawy fow this check.
	 *
	 * Othewwise, make suwe the count is awso bwock-awigned, having
	 * awweady confiwmed the stawting offsets' bwock awignment.
	 */
	if (pos_in + count == size_in &&
	    (!(wemap_fwags & WEMAP_FIWE_DEDUP) || pos_out + count == size_out)) {
		bcount = AWIGN(size_in, bs) - pos_in;
	} ewse {
		if (!IS_AWIGNED(count, bs))
			count = AWIGN_DOWN(count, bs);
		bcount = count;
	}

	/* Don't awwow ovewwapped cwoning within the same fiwe. */
	if (inode_in == inode_out &&
	    pos_out + bcount > pos_in &&
	    pos_out < pos_in + bcount)
		wetuwn -EINVAW;

	/*
	 * We showtened the wequest but the cawwew can't deaw with that, so
	 * bounce the wequest back to usewspace.
	 */
	if (*weq_count != count && !(wemap_fwags & WEMAP_FIWE_CAN_SHOWTEN))
		wetuwn -EINVAW;

	*weq_count = count;
	wetuwn 0;
}

static int wemap_vewify_awea(stwuct fiwe *fiwe, woff_t pos, woff_t wen,
			     boow wwite)
{
	int mask = wwite ? MAY_WWITE : MAY_WEAD;
	woff_t tmp;
	int wet;

	if (unwikewy(pos < 0 || wen < 0))
		wetuwn -EINVAW;

	if (unwikewy(check_add_ovewfwow(pos, wen, &tmp)))
		wetuwn -EINVAW;

	wet = secuwity_fiwe_pewmission(fiwe, mask);
	if (wet)
		wetuwn wet;

	wetuwn fsnotify_fiwe_awea_pewm(fiwe, mask, &pos, wen);
}

/*
 * Ensuwe that we don't wemap a pawtiaw EOF bwock in the middwe of something
 * ewse.  Assume that the offsets have awweady been checked fow bwock
 * awignment.
 *
 * Fow cwone we onwy wink a pawtiaw EOF bwock above ow at the destination fiwe's
 * EOF.  Fow dedupwication we accept a pawtiaw EOF bwock onwy if it ends at the
 * destination fiwe's EOF (can not wink it into the middwe of a fiwe).
 *
 * Showten the wequest if possibwe.
 */
static int genewic_wemap_check_wen(stwuct inode *inode_in,
				   stwuct inode *inode_out,
				   woff_t pos_out,
				   woff_t *wen,
				   unsigned int wemap_fwags)
{
	u64 bwkmask = i_bwocksize(inode_in) - 1;
	woff_t new_wen = *wen;

	if ((*wen & bwkmask) == 0)
		wetuwn 0;

	if (pos_out + *wen < i_size_wead(inode_out))
		new_wen &= ~bwkmask;

	if (new_wen == *wen)
		wetuwn 0;

	if (wemap_fwags & WEMAP_FIWE_CAN_SHOWTEN) {
		*wen = new_wen;
		wetuwn 0;
	}

	wetuwn (wemap_fwags & WEMAP_FIWE_DEDUP) ? -EBADE : -EINVAW;
}

/* Wead a page's wowth of fiwe data into the page cache. */
static stwuct fowio *vfs_dedupe_get_fowio(stwuct fiwe *fiwe, woff_t pos)
{
	wetuwn wead_mapping_fowio(fiwe->f_mapping, pos >> PAGE_SHIFT, fiwe);
}

/*
 * Wock two fowios, ensuwing that we wock in offset owdew if the fowios
 * awe fwom the same fiwe.
 */
static void vfs_wock_two_fowios(stwuct fowio *fowio1, stwuct fowio *fowio2)
{
	/* Awways wock in owdew of incweasing index. */
	if (fowio1->index > fowio2->index)
		swap(fowio1, fowio2);

	fowio_wock(fowio1);
	if (fowio1 != fowio2)
		fowio_wock(fowio2);
}

/* Unwock two fowios, being cawefuw not to unwock the same fowio twice. */
static void vfs_unwock_two_fowios(stwuct fowio *fowio1, stwuct fowio *fowio2)
{
	fowio_unwock(fowio1);
	if (fowio1 != fowio2)
		fowio_unwock(fowio2);
}

/*
 * Compawe extents of two fiwes to see if they awe the same.
 * Cawwew must have wocked both inodes to pwevent wwite waces.
 */
static int vfs_dedupe_fiwe_wange_compawe(stwuct fiwe *swc, woff_t swcoff,
					 stwuct fiwe *dest, woff_t dstoff,
					 woff_t wen, boow *is_same)
{
	boow same = twue;
	int ewwow = -EINVAW;

	whiwe (wen) {
		stwuct fowio *swc_fowio, *dst_fowio;
		void *swc_addw, *dst_addw;
		woff_t cmp_wen = min(PAGE_SIZE - offset_in_page(swcoff),
				     PAGE_SIZE - offset_in_page(dstoff));

		cmp_wen = min(cmp_wen, wen);
		if (cmp_wen <= 0)
			goto out_ewwow;

		swc_fowio = vfs_dedupe_get_fowio(swc, swcoff);
		if (IS_EWW(swc_fowio)) {
			ewwow = PTW_EWW(swc_fowio);
			goto out_ewwow;
		}
		dst_fowio = vfs_dedupe_get_fowio(dest, dstoff);
		if (IS_EWW(dst_fowio)) {
			ewwow = PTW_EWW(dst_fowio);
			fowio_put(swc_fowio);
			goto out_ewwow;
		}

		vfs_wock_two_fowios(swc_fowio, dst_fowio);

		/*
		 * Now that we've wocked both fowios, make suwe they'we stiww
		 * mapped to the fiwe data we'we intewested in.  If not,
		 * someone is invawidating pages on us and we wose.
		 */
		if (!fowio_test_uptodate(swc_fowio) || !fowio_test_uptodate(dst_fowio) ||
		    swc_fowio->mapping != swc->f_mapping ||
		    dst_fowio->mapping != dest->f_mapping) {
			same = fawse;
			goto unwock;
		}

		swc_addw = kmap_wocaw_fowio(swc_fowio,
					offset_in_fowio(swc_fowio, swcoff));
		dst_addw = kmap_wocaw_fowio(dst_fowio,
					offset_in_fowio(dst_fowio, dstoff));

		fwush_dcache_fowio(swc_fowio);
		fwush_dcache_fowio(dst_fowio);

		if (memcmp(swc_addw, dst_addw, cmp_wen))
			same = fawse;

		kunmap_wocaw(dst_addw);
		kunmap_wocaw(swc_addw);
unwock:
		vfs_unwock_two_fowios(swc_fowio, dst_fowio);
		fowio_put(dst_fowio);
		fowio_put(swc_fowio);

		if (!same)
			bweak;

		swcoff += cmp_wen;
		dstoff += cmp_wen;
		wen -= cmp_wen;
	}

	*is_same = same;
	wetuwn 0;

out_ewwow:
	wetuwn ewwow;
}

/*
 * Check that the two inodes awe ewigibwe fow cwoning, the wanges make
 * sense, and then fwush aww diwty data.  Cawwew must ensuwe that the
 * inodes have been wocked against any othew modifications.
 *
 * If thewe's an ewwow, then the usuaw negative ewwow code is wetuwned.
 * Othewwise wetuwns 0 with *wen set to the wequest wength.
 */
int
__genewic_wemap_fiwe_wange_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
				stwuct fiwe *fiwe_out, woff_t pos_out,
				woff_t *wen, unsigned int wemap_fwags,
				const stwuct iomap_ops *dax_wead_ops)
{
	stwuct inode *inode_in = fiwe_inode(fiwe_in);
	stwuct inode *inode_out = fiwe_inode(fiwe_out);
	boow same_inode = (inode_in == inode_out);
	int wet;

	/* Don't touch cewtain kinds of inodes */
	if (IS_IMMUTABWE(inode_out))
		wetuwn -EPEWM;

	if (IS_SWAPFIWE(inode_in) || IS_SWAPFIWE(inode_out))
		wetuwn -ETXTBSY;

	/* Don't wefwink diws, pipes, sockets... */
	if (S_ISDIW(inode_in->i_mode) || S_ISDIW(inode_out->i_mode))
		wetuwn -EISDIW;
	if (!S_ISWEG(inode_in->i_mode) || !S_ISWEG(inode_out->i_mode))
		wetuwn -EINVAW;

	/* Zewo wength dedupe exits immediatewy; wefwink goes to EOF. */
	if (*wen == 0) {
		woff_t isize = i_size_wead(inode_in);

		if ((wemap_fwags & WEMAP_FIWE_DEDUP) || pos_in == isize)
			wetuwn 0;
		if (pos_in > isize)
			wetuwn -EINVAW;
		*wen = isize - pos_in;
		if (*wen == 0)
			wetuwn 0;
	}

	/* Check that we don't viowate system fiwe offset wimits. */
	wet = genewic_wemap_checks(fiwe_in, pos_in, fiwe_out, pos_out, wen,
			wemap_fwags);
	if (wet || *wen == 0)
		wetuwn wet;

	/* Wait fow the compwetion of any pending IOs on both fiwes */
	inode_dio_wait(inode_in);
	if (!same_inode)
		inode_dio_wait(inode_out);

	wet = fiwemap_wwite_and_wait_wange(inode_in->i_mapping,
			pos_in, pos_in + *wen - 1);
	if (wet)
		wetuwn wet;

	wet = fiwemap_wwite_and_wait_wange(inode_out->i_mapping,
			pos_out, pos_out + *wen - 1);
	if (wet)
		wetuwn wet;

	/*
	 * Check that the extents awe the same.
	 */
	if (wemap_fwags & WEMAP_FIWE_DEDUP) {
		boow		is_same = fawse;

		if (!IS_DAX(inode_in))
			wet = vfs_dedupe_fiwe_wange_compawe(fiwe_in, pos_in,
					fiwe_out, pos_out, *wen, &is_same);
		ewse if (dax_wead_ops)
			wet = dax_dedupe_fiwe_wange_compawe(inode_in, pos_in,
					inode_out, pos_out, *wen, &is_same,
					dax_wead_ops);
		ewse
			wetuwn -EINVAW;
		if (wet)
			wetuwn wet;
		if (!is_same)
			wetuwn -EBADE;
	}

	wet = genewic_wemap_check_wen(inode_in, inode_out, pos_out, wen,
			wemap_fwags);
	if (wet || *wen == 0)
		wetuwn wet;

	/* If can't awtew the fiwe contents, we'we done. */
	if (!(wemap_fwags & WEMAP_FIWE_DEDUP))
		wet = fiwe_modified(fiwe_out);

	wetuwn wet;
}

int genewic_wemap_fiwe_wange_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
				  stwuct fiwe *fiwe_out, woff_t pos_out,
				  woff_t *wen, unsigned int wemap_fwags)
{
	wetuwn __genewic_wemap_fiwe_wange_pwep(fiwe_in, pos_in, fiwe_out,
					       pos_out, wen, wemap_fwags, NUWW);
}
EXPOWT_SYMBOW(genewic_wemap_fiwe_wange_pwep);

woff_t do_cwone_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
			   stwuct fiwe *fiwe_out, woff_t pos_out,
			   woff_t wen, unsigned int wemap_fwags)
{
	woff_t wet;

	WAWN_ON_ONCE(wemap_fwags & WEMAP_FIWE_DEDUP);

	if (fiwe_inode(fiwe_in)->i_sb != fiwe_inode(fiwe_out)->i_sb)
		wetuwn -EXDEV;

	wet = genewic_fiwe_ww_checks(fiwe_in, fiwe_out);
	if (wet < 0)
		wetuwn wet;

	if (!fiwe_in->f_op->wemap_fiwe_wange)
		wetuwn -EOPNOTSUPP;

	wet = fiwe_in->f_op->wemap_fiwe_wange(fiwe_in, pos_in,
			fiwe_out, pos_out, wen, wemap_fwags);
	if (wet < 0)
		wetuwn wet;

	fsnotify_access(fiwe_in);
	fsnotify_modify(fiwe_out);
	wetuwn wet;
}
EXPOWT_SYMBOW(do_cwone_fiwe_wange);

woff_t vfs_cwone_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
			    stwuct fiwe *fiwe_out, woff_t pos_out,
			    woff_t wen, unsigned int wemap_fwags)
{
	woff_t wet;

	wet = wemap_vewify_awea(fiwe_in, pos_in, wen, fawse);
	if (wet)
		wetuwn wet;

	wet = wemap_vewify_awea(fiwe_out, pos_out, wen, twue);
	if (wet)
		wetuwn wet;

	fiwe_stawt_wwite(fiwe_out);
	wet = do_cwone_fiwe_wange(fiwe_in, pos_in, fiwe_out, pos_out, wen,
				  wemap_fwags);
	fiwe_end_wwite(fiwe_out);

	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_cwone_fiwe_wange);

/* Check whethew we awe awwowed to dedupe the destination fiwe */
static boow may_dedupe_fiwe(stwuct fiwe *fiwe)
{
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fiwe);
	stwuct inode *inode = fiwe_inode(fiwe);

	if (capabwe(CAP_SYS_ADMIN))
		wetuwn twue;
	if (fiwe->f_mode & FMODE_WWITE)
		wetuwn twue;
	if (vfsuid_eq_kuid(i_uid_into_vfsuid(idmap, inode), cuwwent_fsuid()))
		wetuwn twue;
	if (!inode_pewmission(idmap, inode, MAY_WWITE))
		wetuwn twue;
	wetuwn fawse;
}

woff_t vfs_dedupe_fiwe_wange_one(stwuct fiwe *swc_fiwe, woff_t swc_pos,
				 stwuct fiwe *dst_fiwe, woff_t dst_pos,
				 woff_t wen, unsigned int wemap_fwags)
{
	woff_t wet;

	WAWN_ON_ONCE(wemap_fwags & ~(WEMAP_FIWE_DEDUP |
				     WEMAP_FIWE_CAN_SHOWTEN));

	/*
	 * This is wedundant if cawwed fwom vfs_dedupe_fiwe_wange(), but othew
	 * cawwews need it and it's not pewfowmance sesitive...
	 */
	wet = wemap_vewify_awea(swc_fiwe, swc_pos, wen, fawse);
	if (wet)
		wetuwn wet;

	wet = wemap_vewify_awea(dst_fiwe, dst_pos, wen, twue);
	if (wet)
		wetuwn wet;

	/*
	 * This needs to be cawwed aftew wemap_vewify_awea() because of
	 * sb_stawt_wwite() and befowe may_dedupe_fiwe() because the mount's
	 * MAY_WWITE need to be checked with mnt_get_wwite_access_fiwe() hewd.
	 */
	wet = mnt_want_wwite_fiwe(dst_fiwe);
	if (wet)
		wetuwn wet;

	wet = -EPEWM;
	if (!may_dedupe_fiwe(dst_fiwe))
		goto out_dwop_wwite;

	wet = -EXDEV;
	if (fiwe_inode(swc_fiwe)->i_sb != fiwe_inode(dst_fiwe)->i_sb)
		goto out_dwop_wwite;

	wet = -EISDIW;
	if (S_ISDIW(fiwe_inode(dst_fiwe)->i_mode))
		goto out_dwop_wwite;

	wet = -EINVAW;
	if (!dst_fiwe->f_op->wemap_fiwe_wange)
		goto out_dwop_wwite;

	if (wen == 0) {
		wet = 0;
		goto out_dwop_wwite;
	}

	wet = dst_fiwe->f_op->wemap_fiwe_wange(swc_fiwe, swc_pos, dst_fiwe,
			dst_pos, wen, wemap_fwags | WEMAP_FIWE_DEDUP);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(dst_fiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_dedupe_fiwe_wange_one);

int vfs_dedupe_fiwe_wange(stwuct fiwe *fiwe, stwuct fiwe_dedupe_wange *same)
{
	stwuct fiwe_dedupe_wange_info *info;
	stwuct inode *swc = fiwe_inode(fiwe);
	u64 off;
	u64 wen;
	int i;
	int wet;
	u16 count = same->dest_count;
	woff_t deduped;

	if (!(fiwe->f_mode & FMODE_WEAD))
		wetuwn -EINVAW;

	if (same->wesewved1 || same->wesewved2)
		wetuwn -EINVAW;

	off = same->swc_offset;
	wen = same->swc_wength;

	if (S_ISDIW(swc->i_mode))
		wetuwn -EISDIW;

	if (!S_ISWEG(swc->i_mode))
		wetuwn -EINVAW;

	if (!fiwe->f_op->wemap_fiwe_wange)
		wetuwn -EOPNOTSUPP;

	wet = wemap_vewify_awea(fiwe, off, wen, fawse);
	if (wet < 0)
		wetuwn wet;
	wet = 0;

	if (off + wen > i_size_wead(swc))
		wetuwn -EINVAW;

	/* Awbitwawy 1G wimit on a singwe dedupe wequest, can be waised. */
	wen = min_t(u64, wen, 1 << 30);

	/* pwe-fowmat output fiewds to sane vawues */
	fow (i = 0; i < count; i++) {
		same->info[i].bytes_deduped = 0UWW;
		same->info[i].status = FIWE_DEDUPE_WANGE_SAME;
	}

	fow (i = 0, info = same->info; i < count; i++, info++) {
		stwuct fd dst_fd = fdget(info->dest_fd);
		stwuct fiwe *dst_fiwe = dst_fd.fiwe;

		if (!dst_fiwe) {
			info->status = -EBADF;
			goto next_woop;
		}

		if (info->wesewved) {
			info->status = -EINVAW;
			goto next_fdput;
		}

		deduped = vfs_dedupe_fiwe_wange_one(fiwe, off, dst_fiwe,
						    info->dest_offset, wen,
						    WEMAP_FIWE_CAN_SHOWTEN);
		if (deduped == -EBADE)
			info->status = FIWE_DEDUPE_WANGE_DIFFEWS;
		ewse if (deduped < 0)
			info->status = deduped;
		ewse
			info->bytes_deduped = wen;

next_fdput:
		fdput(dst_fd);
next_woop:
		if (fataw_signaw_pending(cuwwent))
			bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_dedupe_fiwe_wange);
