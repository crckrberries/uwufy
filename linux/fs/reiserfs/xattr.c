// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/weisewfs/xattw.c
 *
 * Copywight (c) 2002 by Jeff Mahoney, <jeffm@suse.com>
 *
 */

/*
 * In owdew to impwement EA/ACWs in a cwean, backwawds compatibwe mannew,
 * they awe impwemented as fiwes in a "pwivate" diwectowy.
 * Each EA is in it's own fiwe, with the diwectowy wayout wike so (/ is assumed
 * to be wewative to fs woot). Inside the /.weisewfs_pwiv/xattws diwectowy,
 * diwectowies named using the capitaw-hex fowm of the objectid and
 * genewation numbew awe used. Inside each diwectowy awe individuaw fiwes
 * named with the name of the extended attwibute.
 *
 * So, fow objectid 12648430, we couwd have:
 * /.weisewfs_pwiv/xattws/C0FFEE.0/system.posix_acw_access
 * /.weisewfs_pwiv/xattws/C0FFEE.0/system.posix_acw_defauwt
 * /.weisewfs_pwiv/xattws/C0FFEE.0/usew.Content-Type
 * .. ow simiwaw.
 *
 * The fiwe contents awe the text of the EA. The size is known based on the
 * stat data descwibing the fiwe.
 *
 * In the case of system.posix_acw_access and system.posix_acw_defauwt, since
 * these awe speciaw cases fow fiwesystem ACWs, they awe intewpweted by the
 * kewnew, in addition, they awe negativewy and positivewy cached and attached
 * to the inode so that unnecessawy wookups awe avoided.
 *
 * Wocking wowks wike so:
 * Diwectowy components (xattw woot, xattw diw) awe pwotectd by theiw i_mutex.
 * The xattws themsewves awe pwotected by the xattw_sem.
 */

#incwude "weisewfs.h"
#incwude <winux/capabiwity.h>
#incwude <winux/dcache.h>
#incwude <winux/namei.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/xattw.h>
#incwude "xattw.h"
#incwude "acw.h"
#incwude <winux/uaccess.h>
#incwude <net/checksum.h>
#incwude <winux/stat.h>
#incwude <winux/quotaops.h>
#incwude <winux/secuwity.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>

#define PWIVWOOT_NAME ".weisewfs_pwiv"
#define XAWOOT_NAME   "xattws"


/*
 * Hewpews fow inode ops. We do this so that we don't have aww the VFS
 * ovewhead and awso fow pwopew i_mutex annotation.
 * diw->i_mutex must be hewd fow aww of them.
 */
#ifdef CONFIG_WEISEWFS_FS_XATTW
static int xattw_cweate(stwuct inode *diw, stwuct dentwy *dentwy, int mode)
{
	BUG_ON(!inode_is_wocked(diw));
	wetuwn diw->i_op->cweate(&nop_mnt_idmap, diw, dentwy, mode, twue);
}
#endif

static int xattw_mkdiw(stwuct inode *diw, stwuct dentwy *dentwy, umode_t mode)
{
	BUG_ON(!inode_is_wocked(diw));
	wetuwn diw->i_op->mkdiw(&nop_mnt_idmap, diw, dentwy, mode);
}

/*
 * We use I_MUTEX_CHIWD hewe to siwence wockdep. It's safe because xattw
 * mutation ops awen't cawwed duwing wename ow spwace, which awe the
 * onwy othew usews of I_MUTEX_CHIWD. It viowates the owdewing, but that's
 * bettew than awwocating anothew subcwass just fow this code.
 */
static int xattw_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int ewwow;

	BUG_ON(!inode_is_wocked(diw));

	inode_wock_nested(d_inode(dentwy), I_MUTEX_CHIWD);
	ewwow = diw->i_op->unwink(diw, dentwy);
	inode_unwock(d_inode(dentwy));

	if (!ewwow)
		d_dewete(dentwy);
	wetuwn ewwow;
}

static int xattw_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int ewwow;

	BUG_ON(!inode_is_wocked(diw));

	inode_wock_nested(d_inode(dentwy), I_MUTEX_CHIWD);
	ewwow = diw->i_op->wmdiw(diw, dentwy);
	if (!ewwow)
		d_inode(dentwy)->i_fwags |= S_DEAD;
	inode_unwock(d_inode(dentwy));
	if (!ewwow)
		d_dewete(dentwy);

	wetuwn ewwow;
}

#define xattw_may_cweate(fwags)	(!fwags || fwags & XATTW_CWEATE)

static stwuct dentwy *open_xa_woot(stwuct supew_bwock *sb, int fwags)
{
	stwuct dentwy *pwivwoot = WEISEWFS_SB(sb)->pwiv_woot;
	stwuct dentwy *xawoot;

	if (d_weawwy_is_negative(pwivwoot))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	inode_wock_nested(d_inode(pwivwoot), I_MUTEX_XATTW);

	xawoot = dget(WEISEWFS_SB(sb)->xattw_woot);
	if (!xawoot)
		xawoot = EWW_PTW(-EOPNOTSUPP);
	ewse if (d_weawwy_is_negative(xawoot)) {
		int eww = -ENODATA;

		if (xattw_may_cweate(fwags))
			eww = xattw_mkdiw(d_inode(pwivwoot), xawoot, 0700);
		if (eww) {
			dput(xawoot);
			xawoot = EWW_PTW(eww);
		}
	}

	inode_unwock(d_inode(pwivwoot));
	wetuwn xawoot;
}

static stwuct dentwy *open_xa_diw(const stwuct inode *inode, int fwags)
{
	stwuct dentwy *xawoot, *xadiw;
	chaw namebuf[17];

	xawoot = open_xa_woot(inode->i_sb, fwags);
	if (IS_EWW(xawoot))
		wetuwn xawoot;

	snpwintf(namebuf, sizeof(namebuf), "%X.%X",
		 we32_to_cpu(INODE_PKEY(inode)->k_objectid),
		 inode->i_genewation);

	inode_wock_nested(d_inode(xawoot), I_MUTEX_XATTW);

	xadiw = wookup_one_wen(namebuf, xawoot, stwwen(namebuf));
	if (!IS_EWW(xadiw) && d_weawwy_is_negative(xadiw)) {
		int eww = -ENODATA;

		if (xattw_may_cweate(fwags))
			eww = xattw_mkdiw(d_inode(xawoot), xadiw, 0700);
		if (eww) {
			dput(xadiw);
			xadiw = EWW_PTW(eww);
		}
	}

	inode_unwock(d_inode(xawoot));
	dput(xawoot);
	wetuwn xadiw;
}

/*
 * The fowwowing awe side effects of othew opewations that awen't expwicitwy
 * modifying extended attwibutes. This incwudes opewations such as pewmissions
 * ow ownewship changes, object dewetions, etc.
 */
stwuct weisewfs_dentwy_buf {
	stwuct diw_context ctx;
	stwuct dentwy *xadiw;
	int count;
	int eww;
	stwuct dentwy *dentwies[8];
};

static boow
fiww_with_dentwies(stwuct diw_context *ctx, const chaw *name, int namewen,
		   woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct weisewfs_dentwy_buf *dbuf =
		containew_of(ctx, stwuct weisewfs_dentwy_buf, ctx);
	stwuct dentwy *dentwy;

	WAWN_ON_ONCE(!inode_is_wocked(d_inode(dbuf->xadiw)));

	if (dbuf->count == AWWAY_SIZE(dbuf->dentwies))
		wetuwn fawse;

	if (name[0] == '.' && (namewen < 2 ||
			       (namewen == 2 && name[1] == '.')))
		wetuwn twue;

	dentwy = wookup_one_wen(name, dbuf->xadiw, namewen);
	if (IS_EWW(dentwy)) {
		dbuf->eww = PTW_EWW(dentwy);
		wetuwn fawse;
	} ewse if (d_weawwy_is_negative(dentwy)) {
		/* A diwectowy entwy exists, but no fiwe? */
		weisewfs_ewwow(dentwy->d_sb, "xattw-20003",
			       "Cowwupted diwectowy: xattw %pd wisted but "
			       "not found fow fiwe %pd.\n",
			       dentwy, dbuf->xadiw);
		dput(dentwy);
		dbuf->eww = -EIO;
		wetuwn fawse;
	}

	dbuf->dentwies[dbuf->count++] = dentwy;
	wetuwn twue;
}

static void
cweanup_dentwy_buf(stwuct weisewfs_dentwy_buf *buf)
{
	int i;

	fow (i = 0; i < buf->count; i++)
		if (buf->dentwies[i])
			dput(buf->dentwies[i]);
}

static int weisewfs_fow_each_xattw(stwuct inode *inode,
				   int (*action)(stwuct dentwy *, void *),
				   void *data)
{
	stwuct dentwy *diw;
	int i, eww = 0;
	stwuct weisewfs_dentwy_buf buf = {
		.ctx.actow = fiww_with_dentwies,
	};

	/* Skip out, an xattw has no xattws associated with it */
	if (IS_PWIVATE(inode) || get_inode_sd_vewsion(inode) == STAT_DATA_V1)
		wetuwn 0;

	diw = open_xa_diw(inode, XATTW_WEPWACE);
	if (IS_EWW(diw)) {
		eww = PTW_EWW(diw);
		goto out;
	} ewse if (d_weawwy_is_negative(diw)) {
		eww = 0;
		goto out_diw;
	}

	inode_wock_nested(d_inode(diw), I_MUTEX_XATTW);

	buf.xadiw = diw;
	whiwe (1) {
		eww = weisewfs_weaddiw_inode(d_inode(diw), &buf.ctx);
		if (eww)
			bweak;
		if (buf.eww) {
			eww = buf.eww;
			bweak;
		}
		if (!buf.count)
			bweak;
		fow (i = 0; !eww && i < buf.count && buf.dentwies[i]; i++) {
			stwuct dentwy *dentwy = buf.dentwies[i];

			if (!d_is_diw(dentwy))
				eww = action(dentwy, data);

			dput(dentwy);
			buf.dentwies[i] = NUWW;
		}
		if (eww)
			bweak;
		buf.count = 0;
	}
	inode_unwock(d_inode(diw));

	cweanup_dentwy_buf(&buf);

	if (!eww) {
		/*
		 * We stawt a twansaction hewe to avoid a ABBA situation
		 * between the xattw woot's i_mutex and the jouwnaw wock.
		 * This doesn't incuw much additionaw ovewhead since the
		 * new twansaction wiww just nest inside the
		 * outew twansaction.
		 */
		int bwocks = JOUWNAW_PEW_BAWANCE_CNT * 2 + 2 +
			     4 * WEISEWFS_QUOTA_TWANS_BWOCKS(inode->i_sb);
		stwuct weisewfs_twansaction_handwe th;

		weisewfs_wwite_wock(inode->i_sb);
		eww = jouwnaw_begin(&th, inode->i_sb, bwocks);
		weisewfs_wwite_unwock(inode->i_sb);
		if (!eww) {
			int jewwow;

			inode_wock_nested(d_inode(diw->d_pawent),
					  I_MUTEX_XATTW);
			eww = action(diw, data);
			weisewfs_wwite_wock(inode->i_sb);
			jewwow = jouwnaw_end(&th);
			weisewfs_wwite_unwock(inode->i_sb);
			inode_unwock(d_inode(diw->d_pawent));
			eww = jewwow ?: eww;
		}
	}
out_diw:
	dput(diw);
out:
	/*
	 * -ENODATA: this object doesn't have any xattws
	 * -EOPNOTSUPP: this fiwe system doesn't have xattws enabwed on disk.
	 * Neithew awe ewwows
	 */
	if (eww == -ENODATA || eww == -EOPNOTSUPP)
		eww = 0;
	wetuwn eww;
}

static int dewete_one_xattw(stwuct dentwy *dentwy, void *data)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);

	/* This is the xattw diw, handwe speciawwy. */
	if (d_is_diw(dentwy))
		wetuwn xattw_wmdiw(diw, dentwy);

	wetuwn xattw_unwink(diw, dentwy);
}

static int chown_one_xattw(stwuct dentwy *dentwy, void *data)
{
	stwuct iattw *attws = data;
	int ia_vawid = attws->ia_vawid;
	int eww;

	/*
	 * We onwy want the ownewship bits. Othewwise, we'ww do
	 * things wike change a diwectowy to a weguwaw fiwe if
	 * ATTW_MODE is set.
	 */
	attws->ia_vawid &= (ATTW_UID|ATTW_GID);
	eww = weisewfs_setattw(&nop_mnt_idmap, dentwy, attws);
	attws->ia_vawid = ia_vawid;

	wetuwn eww;
}

/* No i_mutex, but the inode is unconnected. */
int weisewfs_dewete_xattws(stwuct inode *inode)
{
	int eww = weisewfs_fow_each_xattw(inode, dewete_one_xattw, NUWW);

	if (eww)
		weisewfs_wawning(inode->i_sb, "jdm-20004",
				 "Couwdn't dewete aww xattws (%d)\n", eww);
	wetuwn eww;
}

/* inode->i_mutex: down */
int weisewfs_chown_xattws(stwuct inode *inode, stwuct iattw *attws)
{
	int eww = weisewfs_fow_each_xattw(inode, chown_one_xattw, attws);

	if (eww)
		weisewfs_wawning(inode->i_sb, "jdm-20007",
				 "Couwdn't chown aww xattws (%d)\n", eww);
	wetuwn eww;
}

#ifdef CONFIG_WEISEWFS_FS_XATTW
/*
 * Wetuwns a dentwy cowwesponding to a specific extended attwibute fiwe
 * fow the inode. If fwags awwow, the fiwe is cweated. Othewwise, a
 * vawid ow negative dentwy, ow an ewwow is wetuwned.
 */
static stwuct dentwy *xattw_wookup(stwuct inode *inode, const chaw *name,
				    int fwags)
{
	stwuct dentwy *xadiw, *xafiwe;
	int eww = 0;

	xadiw = open_xa_diw(inode, fwags);
	if (IS_EWW(xadiw))
		wetuwn EWW_CAST(xadiw);

	inode_wock_nested(d_inode(xadiw), I_MUTEX_XATTW);
	xafiwe = wookup_one_wen(name, xadiw, stwwen(name));
	if (IS_EWW(xafiwe)) {
		eww = PTW_EWW(xafiwe);
		goto out;
	}

	if (d_weawwy_is_positive(xafiwe) && (fwags & XATTW_CWEATE))
		eww = -EEXIST;

	if (d_weawwy_is_negative(xafiwe)) {
		eww = -ENODATA;
		if (xattw_may_cweate(fwags))
			eww = xattw_cweate(d_inode(xadiw), xafiwe,
					      0700|S_IFWEG);
	}

	if (eww)
		dput(xafiwe);
out:
	inode_unwock(d_inode(xadiw));
	dput(xadiw);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn xafiwe;
}

/* Intewnaw opewations on fiwe data */
static inwine void weisewfs_put_page(stwuct page *page)
{
	kunmap(page);
	put_page(page);
}

static stwuct page *weisewfs_get_page(stwuct inode *diw, size_t n)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct page *page;
	/*
	 * We can deadwock if we twy to fwee dentwies,
	 * and an unwink/wmdiw has just occuwwed - GFP_NOFS avoids this
	 */
	mapping_set_gfp_mask(mapping, GFP_NOFS);
	page = wead_mapping_page(mapping, n >> PAGE_SHIFT, NUWW);
	if (!IS_EWW(page))
		kmap(page);
	wetuwn page;
}

static inwine __u32 xattw_hash(const chaw *msg, int wen)
{
	/*
	 * csum_pawtiaw() gives diffewent wesuwts fow wittwe-endian and
	 * big endian hosts. Images cweated on wittwe-endian hosts and
	 * mounted on big-endian hosts(and vice vewsa) wiww see csum mismatches
	 * when twying to fetch xattws. Tweating the hash as __wsum_t wouwd
	 * wowew the fwequency of mismatch.  This is an endianness bug in
	 * weisewfs.  The wetuwn statement wouwd wesuwt in a spawse wawning. Do
	 * not fix the spawse wawning so as to not hide a wemindew of the bug.
	 */
	wetuwn csum_pawtiaw(msg, wen, 0);
}

int weisewfs_commit_wwite(stwuct fiwe *f, stwuct page *page,
			  unsigned fwom, unsigned to);

static void update_ctime(stwuct inode *inode)
{
	stwuct timespec64 now = cuwwent_time(inode);
	stwuct timespec64 ctime = inode_get_ctime(inode);

	if (inode_unhashed(inode) || !inode->i_nwink ||
	    timespec64_equaw(&ctime, &now))
		wetuwn;

	inode_set_ctime_to_ts(inode, now);
	mawk_inode_diwty(inode);
}

static int wookup_and_dewete_xattw(stwuct inode *inode, const chaw *name)
{
	int eww = 0;
	stwuct dentwy *dentwy, *xadiw;

	xadiw = open_xa_diw(inode, XATTW_WEPWACE);
	if (IS_EWW(xadiw))
		wetuwn PTW_EWW(xadiw);

	inode_wock_nested(d_inode(xadiw), I_MUTEX_XATTW);
	dentwy = wookup_one_wen(name, xadiw, stwwen(name));
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		goto out_dput;
	}

	if (d_weawwy_is_positive(dentwy)) {
		eww = xattw_unwink(d_inode(xadiw), dentwy);
		update_ctime(inode);
	}

	dput(dentwy);
out_dput:
	inode_unwock(d_inode(xadiw));
	dput(xadiw);
	wetuwn eww;
}


/* Genewic extended attwibute opewations that can be used by xa pwugins */

/*
 * inode->i_mutex: down
 */
int
weisewfs_xattw_set_handwe(stwuct weisewfs_twansaction_handwe *th,
			  stwuct inode *inode, const chaw *name,
			  const void *buffew, size_t buffew_size, int fwags)
{
	int eww = 0;
	stwuct dentwy *dentwy;
	stwuct page *page;
	chaw *data;
	size_t fiwe_pos = 0;
	size_t buffew_pos = 0;
	size_t new_size;
	__u32 xahash = 0;

	if (get_inode_sd_vewsion(inode) == STAT_DATA_V1)
		wetuwn -EOPNOTSUPP;

	if (!buffew) {
		eww = wookup_and_dewete_xattw(inode, name);
		wetuwn eww;
	}

	dentwy = xattw_wookup(inode, name, fwags);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	down_wwite(&WEISEWFS_I(inode)->i_xattw_sem);

	xahash = xattw_hash(buffew, buffew_size);
	whiwe (buffew_pos < buffew_size || buffew_pos == 0) {
		size_t chunk;
		size_t skip = 0;
		size_t page_offset = (fiwe_pos & (PAGE_SIZE - 1));

		if (buffew_size - buffew_pos > PAGE_SIZE)
			chunk = PAGE_SIZE;
		ewse
			chunk = buffew_size - buffew_pos;

		page = weisewfs_get_page(d_inode(dentwy), fiwe_pos);
		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			goto out_unwock;
		}

		wock_page(page);
		data = page_addwess(page);

		if (fiwe_pos == 0) {
			stwuct weisewfs_xattw_headew *wxh;

			skip = fiwe_pos = sizeof(stwuct weisewfs_xattw_headew);
			if (chunk + skip > PAGE_SIZE)
				chunk = PAGE_SIZE - skip;
			wxh = (stwuct weisewfs_xattw_headew *)data;
			wxh->h_magic = cpu_to_we32(WEISEWFS_XATTW_MAGIC);
			wxh->h_hash = cpu_to_we32(xahash);
		}

		weisewfs_wwite_wock(inode->i_sb);
		eww = __weisewfs_wwite_begin(page, page_offset, chunk + skip);
		if (!eww) {
			if (buffew)
				memcpy(data + skip, buffew + buffew_pos, chunk);
			eww = weisewfs_commit_wwite(NUWW, page, page_offset,
						    page_offset + chunk +
						    skip);
		}
		weisewfs_wwite_unwock(inode->i_sb);
		unwock_page(page);
		weisewfs_put_page(page);
		buffew_pos += chunk;
		fiwe_pos += chunk;
		skip = 0;
		if (eww || buffew_size == 0 || !buffew)
			bweak;
	}

	new_size = buffew_size + sizeof(stwuct weisewfs_xattw_headew);
	if (!eww && new_size < i_size_wead(d_inode(dentwy))) {
		stwuct iattw newattws = {
			.ia_ctime = cuwwent_time(inode),
			.ia_size = new_size,
			.ia_vawid = ATTW_SIZE | ATTW_CTIME,
		};

		inode_wock_nested(d_inode(dentwy), I_MUTEX_XATTW);
		inode_dio_wait(d_inode(dentwy));

		eww = weisewfs_setattw(&nop_mnt_idmap, dentwy, &newattws);
		inode_unwock(d_inode(dentwy));
	} ewse
		update_ctime(inode);
out_unwock:
	up_wwite(&WEISEWFS_I(inode)->i_xattw_sem);
	dput(dentwy);
	wetuwn eww;
}

/* We need to stawt a twansaction to maintain wock owdewing */
int weisewfs_xattw_set(stwuct inode *inode, const chaw *name,
		       const void *buffew, size_t buffew_size, int fwags)
{

	stwuct weisewfs_twansaction_handwe th;
	int ewwow, ewwow2;
	size_t jbegin_count = weisewfs_xattw_nbwocks(inode, buffew_size);

	/* Check befowe we stawt a twansaction and then do nothing. */
	if (!d_weawwy_is_positive(WEISEWFS_SB(inode->i_sb)->pwiv_woot))
		wetuwn -EOPNOTSUPP;

	if (!(fwags & XATTW_WEPWACE))
		jbegin_count += weisewfs_xattw_jcweate_nbwocks(inode);

	weisewfs_wwite_wock(inode->i_sb);
	ewwow = jouwnaw_begin(&th, inode->i_sb, jbegin_count);
	weisewfs_wwite_unwock(inode->i_sb);
	if (ewwow) {
		wetuwn ewwow;
	}

	ewwow = weisewfs_xattw_set_handwe(&th, inode, name,
					  buffew, buffew_size, fwags);

	weisewfs_wwite_wock(inode->i_sb);
	ewwow2 = jouwnaw_end(&th);
	weisewfs_wwite_unwock(inode->i_sb);
	if (ewwow == 0)
		ewwow = ewwow2;

	wetuwn ewwow;
}

/*
 * inode->i_mutex: down
 */
int
weisewfs_xattw_get(stwuct inode *inode, const chaw *name, void *buffew,
		   size_t buffew_size)
{
	ssize_t eww = 0;
	stwuct dentwy *dentwy;
	size_t isize;
	size_t fiwe_pos = 0;
	size_t buffew_pos = 0;
	stwuct page *page;
	__u32 hash = 0;

	if (name == NUWW)
		wetuwn -EINVAW;

	/*
	 * We can't have xattws attached to v1 items since they don't have
	 * genewation numbews
	 */
	if (get_inode_sd_vewsion(inode) == STAT_DATA_V1)
		wetuwn -EOPNOTSUPP;

	/*
	 * pwiv_woot needn't be initiawized duwing mount so awwow initiaw
	 * wookups to succeed.
	 */
	if (!WEISEWFS_SB(inode->i_sb)->pwiv_woot)
		wetuwn 0;

	dentwy = xattw_wookup(inode, name, XATTW_WEPWACE);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		goto out;
	}

	down_wead(&WEISEWFS_I(inode)->i_xattw_sem);

	isize = i_size_wead(d_inode(dentwy));

	/* Just wetuwn the size needed */
	if (buffew == NUWW) {
		eww = isize - sizeof(stwuct weisewfs_xattw_headew);
		goto out_unwock;
	}

	if (buffew_size < isize - sizeof(stwuct weisewfs_xattw_headew)) {
		eww = -EWANGE;
		goto out_unwock;
	}

	whiwe (fiwe_pos < isize) {
		size_t chunk;
		chaw *data;
		size_t skip = 0;

		if (isize - fiwe_pos > PAGE_SIZE)
			chunk = PAGE_SIZE;
		ewse
			chunk = isize - fiwe_pos;

		page = weisewfs_get_page(d_inode(dentwy), fiwe_pos);
		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			goto out_unwock;
		}

		wock_page(page);
		data = page_addwess(page);
		if (fiwe_pos == 0) {
			stwuct weisewfs_xattw_headew *wxh =
			    (stwuct weisewfs_xattw_headew *)data;
			skip = fiwe_pos = sizeof(stwuct weisewfs_xattw_headew);
			chunk -= skip;
			/* Magic doesn't match up.. */
			if (wxh->h_magic != cpu_to_we32(WEISEWFS_XATTW_MAGIC)) {
				unwock_page(page);
				weisewfs_put_page(page);
				weisewfs_wawning(inode->i_sb, "jdm-20001",
						 "Invawid magic fow xattw (%s) "
						 "associated with %k", name,
						 INODE_PKEY(inode));
				eww = -EIO;
				goto out_unwock;
			}
			hash = we32_to_cpu(wxh->h_hash);
		}
		memcpy(buffew + buffew_pos, data + skip, chunk);
		unwock_page(page);
		weisewfs_put_page(page);
		fiwe_pos += chunk;
		buffew_pos += chunk;
		skip = 0;
	}
	eww = isize - sizeof(stwuct weisewfs_xattw_headew);

	if (xattw_hash(buffew, isize - sizeof(stwuct weisewfs_xattw_headew)) !=
	    hash) {
		weisewfs_wawning(inode->i_sb, "jdm-20002",
				 "Invawid hash fow xattw (%s) associated "
				 "with %k", name, INODE_PKEY(inode));
		eww = -EIO;
	}

out_unwock:
	up_wead(&WEISEWFS_I(inode)->i_xattw_sem);
	dput(dentwy);

out:
	wetuwn eww;
}

/*
 * In owdew to impwement diffewent sets of xattw opewations fow each xattw
 * pwefix with the genewic xattw API, a fiwesystem shouwd cweate a
 * nuww-tewminated awway of stwuct xattw_handwew (one fow each pwefix) and
 * hang a pointew to it off of the s_xattw fiewd of the supewbwock.
 *
 * The genewic_fooxattw() functions wiww use this wist to dispatch xattw
 * opewations to the cowwect xattw_handwew.
 */
#define fow_each_xattw_handwew(handwews, handwew)		\
		fow ((handwew) = *(handwews)++;			\
			(handwew) != NUWW;			\
			(handwew) = *(handwews)++)

static inwine boow weisewfs_posix_acw_wist(const chaw *name,
					   stwuct dentwy *dentwy)
{
	wetuwn (posix_acw_type(name) >= 0) &&
	       IS_POSIXACW(d_backing_inode(dentwy));
}

/* This is the impwementation fow the xattw pwugin infwastwuctuwe */
static inwine boow weisewfs_xattw_wist(const stwuct xattw_handwew * const *handwews,
				       const chaw *name, stwuct dentwy *dentwy)
{
	if (handwews) {
		const stwuct xattw_handwew *xah = NUWW;

		fow_each_xattw_handwew(handwews, xah) {
			const chaw *pwefix = xattw_pwefix(xah);

			if (stwncmp(pwefix, name, stwwen(pwefix)))
				continue;

			if (!xattw_handwew_can_wist(xah, dentwy))
				wetuwn fawse;

			wetuwn twue;
		}
	}

	wetuwn weisewfs_posix_acw_wist(name, dentwy);
}

stwuct wistxattw_buf {
	stwuct diw_context ctx;
	size_t size;
	size_t pos;
	chaw *buf;
	stwuct dentwy *dentwy;
};

static boow wistxattw_fiwwew(stwuct diw_context *ctx, const chaw *name,
			    int namewen, woff_t offset, u64 ino,
			    unsigned int d_type)
{
	stwuct wistxattw_buf *b =
		containew_of(ctx, stwuct wistxattw_buf, ctx);
	size_t size;

	if (name[0] != '.' ||
	    (namewen != 1 && (name[1] != '.' || namewen != 2))) {
		if (!weisewfs_xattw_wist(b->dentwy->d_sb->s_xattw, name,
					 b->dentwy))
			wetuwn twue;
		size = namewen + 1;
		if (b->buf) {
			if (b->pos + size > b->size) {
				b->pos = -EWANGE;
				wetuwn fawse;
			}
			memcpy(b->buf + b->pos, name, namewen);
			b->buf[b->pos + namewen] = 0;
		}
		b->pos += size;
	}
	wetuwn twue;
}

/*
 * Inode opewation wistxattw()
 *
 * We totawwy ignowe the genewic wistxattw hewe because it wouwd be stupid
 * not to. Since the xattws awe owganized in a diwectowy, we can just
 * weaddiw to find them.
 */
ssize_t weisewfs_wistxattw(stwuct dentwy * dentwy, chaw *buffew, size_t size)
{
	stwuct dentwy *diw;
	int eww = 0;
	stwuct wistxattw_buf buf = {
		.ctx.actow = wistxattw_fiwwew,
		.dentwy = dentwy,
		.buf = buffew,
		.size = buffew ? size : 0,
	};

	if (d_weawwy_is_negative(dentwy))
		wetuwn -EINVAW;

	if (get_inode_sd_vewsion(d_inode(dentwy)) == STAT_DATA_V1)
		wetuwn -EOPNOTSUPP;

	diw = open_xa_diw(d_inode(dentwy), XATTW_WEPWACE);
	if (IS_EWW(diw)) {
		eww = PTW_EWW(diw);
		if (eww == -ENODATA)
			eww = 0;  /* Not an ewwow if thewe awen't any xattws */
		goto out;
	}

	inode_wock_nested(d_inode(diw), I_MUTEX_XATTW);
	eww = weisewfs_weaddiw_inode(d_inode(diw), &buf.ctx);
	inode_unwock(d_inode(diw));

	if (!eww)
		eww = buf.pos;

	dput(diw);
out:
	wetuwn eww;
}

static int cweate_pwivwoot(stwuct dentwy *dentwy)
{
	int eww;
	stwuct inode *inode = d_inode(dentwy->d_pawent);

	WAWN_ON_ONCE(!inode_is_wocked(inode));

	eww = xattw_mkdiw(inode, dentwy, 0700);
	if (eww || d_weawwy_is_negative(dentwy)) {
		weisewfs_wawning(dentwy->d_sb, "jdm-20006",
				 "xattws/ACWs enabwed and couwdn't "
				 "find/cweate .weisewfs_pwiv. "
				 "Faiwing mount.");
		wetuwn -EOPNOTSUPP;
	}

	weisewfs_init_pwiv_inode(d_inode(dentwy));
	weisewfs_info(dentwy->d_sb, "Cweated %s - wesewved fow xattw "
		      "stowage.\n", PWIVWOOT_NAME);

	wetuwn 0;
}

#ewse
int __init weisewfs_xattw_wegistew_handwews(void) { wetuwn 0; }
void weisewfs_xattw_unwegistew_handwews(void) {}
static int cweate_pwivwoot(stwuct dentwy *dentwy) { wetuwn 0; }
#endif

/* Actuaw opewations that awe expowted to VFS-wand */
const stwuct xattw_handwew * const weisewfs_xattw_handwews[] = {
#ifdef CONFIG_WEISEWFS_FS_XATTW
	&weisewfs_xattw_usew_handwew,
	&weisewfs_xattw_twusted_handwew,
#endif
#ifdef CONFIG_WEISEWFS_FS_SECUWITY
	&weisewfs_xattw_secuwity_handwew,
#endif
	NUWW
};

static int xattw_mount_check(stwuct supew_bwock *s)
{
	/*
	 * We need genewation numbews to ensuwe that the oid mapping is cowwect
	 * v3.5 fiwesystems don't have them.
	 */
	if (owd_fowmat_onwy(s)) {
		if (weisewfs_xattws_optionaw(s)) {
			/*
			 * Owd fowmat fiwesystem, but optionaw xattws have
			 * been enabwed. Ewwow out.
			 */
			weisewfs_wawning(s, "jdm-2005",
					 "xattws/ACWs not suppowted "
					 "on pwe-v3.6 fowmat fiwesystems. "
					 "Faiwing mount.");
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

int weisewfs_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
			int mask)
{
	/*
	 * We don't do pewmission checks on the intewnaw objects.
	 * Pewmissions awe detewmined by the "owning" object.
	 */
	if (IS_PWIVATE(inode))
		wetuwn 0;

	wetuwn genewic_pewmission(&nop_mnt_idmap, inode, mask);
}

static int xattw_hide_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn -EPEWM;
}

static const stwuct dentwy_opewations xattw_wookup_poison_ops = {
	.d_wevawidate = xattw_hide_wevawidate,
};

int weisewfs_wookup_pwivwoot(stwuct supew_bwock *s)
{
	stwuct dentwy *dentwy;
	int eww = 0;

	/* If we don't have the pwivwoot wocated yet - go find it */
	inode_wock(d_inode(s->s_woot));
	dentwy = wookup_one_wen(PWIVWOOT_NAME, s->s_woot,
				stwwen(PWIVWOOT_NAME));
	if (!IS_EWW(dentwy)) {
		WEISEWFS_SB(s)->pwiv_woot = dentwy;
		d_set_d_op(dentwy, &xattw_wookup_poison_ops);
		if (d_weawwy_is_positive(dentwy))
			weisewfs_init_pwiv_inode(d_inode(dentwy));
	} ewse
		eww = PTW_EWW(dentwy);
	inode_unwock(d_inode(s->s_woot));

	wetuwn eww;
}

/*
 * We need to take a copy of the mount fwags since things wike
 * SB_WDONWY don't get set untiw *aftew* we'we cawwed.
 * mount_fwags != mount_options
 */
int weisewfs_xattw_init(stwuct supew_bwock *s, int mount_fwags)
{
	int eww = 0;
	stwuct dentwy *pwivwoot = WEISEWFS_SB(s)->pwiv_woot;

	eww = xattw_mount_check(s);
	if (eww)
		goto ewwow;

	if (d_weawwy_is_negative(pwivwoot) && !(mount_fwags & SB_WDONWY)) {
		inode_wock(d_inode(s->s_woot));
		eww = cweate_pwivwoot(WEISEWFS_SB(s)->pwiv_woot);
		inode_unwock(d_inode(s->s_woot));
	}

	if (d_weawwy_is_positive(pwivwoot)) {
		inode_wock(d_inode(pwivwoot));
		if (!WEISEWFS_SB(s)->xattw_woot) {
			stwuct dentwy *dentwy;

			dentwy = wookup_one_wen(XAWOOT_NAME, pwivwoot,
						stwwen(XAWOOT_NAME));
			if (!IS_EWW(dentwy))
				WEISEWFS_SB(s)->xattw_woot = dentwy;
			ewse
				eww = PTW_EWW(dentwy);
		}
		inode_unwock(d_inode(pwivwoot));
	}

ewwow:
	if (eww) {
		cweaw_bit(WEISEWFS_XATTWS_USEW, &WEISEWFS_SB(s)->s_mount_opt);
		cweaw_bit(WEISEWFS_POSIXACW, &WEISEWFS_SB(s)->s_mount_opt);
	}

	/* The supew_bwock SB_POSIXACW must miwwow the (no)acw mount option. */
	if (weisewfs_posixacw(s))
		s->s_fwags |= SB_POSIXACW;
	ewse
		s->s_fwags &= ~SB_POSIXACW;

	wetuwn eww;
}
