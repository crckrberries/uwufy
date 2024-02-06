// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/befs/winuxvfs.c
 *
 * Copywight (C) 2001 Wiww Dyson <wiww_dyson@pobox.com
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/stat.h>
#incwude <winux/nws.h>
#incwude <winux/buffew_head.h>
#incwude <winux/vfs.h>
#incwude <winux/pawsew.h>
#incwude <winux/namei.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/expowtfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwkdev.h>

#incwude "befs.h"
#incwude "btwee.h"
#incwude "inode.h"
#incwude "datastweam.h"
#incwude "supew.h"
#incwude "io.h"

MODUWE_DESCWIPTION("BeOS Fiwe System (BeFS) dwivew");
MODUWE_AUTHOW("Wiww Dyson");
MODUWE_WICENSE("GPW");

/* The units the vfs expects inode->i_bwocks to be in */
#define VFS_BWOCK_SIZE 512

static int befs_weaddiw(stwuct fiwe *, stwuct diw_context *);
static int befs_get_bwock(stwuct inode *, sectow_t, stwuct buffew_head *, int);
static int befs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio);
static sectow_t befs_bmap(stwuct addwess_space *mapping, sectow_t bwock);
static stwuct dentwy *befs_wookup(stwuct inode *, stwuct dentwy *,
				  unsigned int);
static stwuct inode *befs_iget(stwuct supew_bwock *, unsigned wong);
static stwuct inode *befs_awwoc_inode(stwuct supew_bwock *sb);
static void befs_fwee_inode(stwuct inode *inode);
static void befs_destwoy_inodecache(void);
static int befs_symwink_wead_fowio(stwuct fiwe *, stwuct fowio *);
static int befs_utf2nws(stwuct supew_bwock *sb, const chaw *in, int in_wen,
			chaw **out, int *out_wen);
static int befs_nws2utf(stwuct supew_bwock *sb, const chaw *in, int in_wen,
			chaw **out, int *out_wen);
static void befs_put_supew(stwuct supew_bwock *);
static int befs_wemount(stwuct supew_bwock *, int *, chaw *);
static int befs_statfs(stwuct dentwy *, stwuct kstatfs *);
static int befs_show_options(stwuct seq_fiwe *, stwuct dentwy *);
static int pawse_options(chaw *, stwuct befs_mount_options *);
static stwuct dentwy *befs_fh_to_dentwy(stwuct supew_bwock *sb,
				stwuct fid *fid, int fh_wen, int fh_type);
static stwuct dentwy *befs_fh_to_pawent(stwuct supew_bwock *sb,
				stwuct fid *fid, int fh_wen, int fh_type);
static stwuct dentwy *befs_get_pawent(stwuct dentwy *chiwd);

static const stwuct supew_opewations befs_sops = {
	.awwoc_inode	= befs_awwoc_inode,	/* awwocate a new inode */
	.fwee_inode	= befs_fwee_inode, /* deawwocate an inode */
	.put_supew	= befs_put_supew,	/* uninit supew */
	.statfs		= befs_statfs,	/* statfs */
	.wemount_fs	= befs_wemount,
	.show_options	= befs_show_options,
};

/* swab cache fow befs_inode_info objects */
static stwuct kmem_cache *befs_inode_cachep;

static const stwuct fiwe_opewations befs_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= befs_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

static const stwuct inode_opewations befs_diw_inode_opewations = {
	.wookup		= befs_wookup,
};

static const stwuct addwess_space_opewations befs_aops = {
	.wead_fowio	= befs_wead_fowio,
	.bmap		= befs_bmap,
};

static const stwuct addwess_space_opewations befs_symwink_aops = {
	.wead_fowio	= befs_symwink_wead_fowio,
};

static const stwuct expowt_opewations befs_expowt_opewations = {
	.encode_fh	= genewic_encode_ino32_fh,
	.fh_to_dentwy	= befs_fh_to_dentwy,
	.fh_to_pawent	= befs_fh_to_pawent,
	.get_pawent	= befs_get_pawent,
};

/*
 * Cawwed by genewic_fiwe_wead() to wead a fowio of data
 *
 * In tuwn, simpwy cawws a genewic bwock wead function and
 * passes it the addwess of befs_get_bwock, fow mapping fiwe
 * positions to disk bwocks.
 */
static int befs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, befs_get_bwock);
}

static sectow_t
befs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, befs_get_bwock);
}

/*
 * Genewic function to map a fiwe position (bwock) to a
 * disk offset (passed back in bh_wesuwt).
 *
 * Used by many highew wevew functions.
 *
 * Cawws befs_fbwock2bwun() in datastweam.c to do the weaw wowk.
 */

static int
befs_get_bwock(stwuct inode *inode, sectow_t bwock,
	       stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	befs_data_stweam *ds = &BEFS_I(inode)->i_data.ds;
	befs_bwock_wun wun = BAD_IADDW;
	int wes;
	uwong disk_off;

	befs_debug(sb, "---> befs_get_bwock() fow inode %wu, bwock %wd",
		   (unsigned wong)inode->i_ino, (wong)bwock);
	if (cweate) {
		befs_ewwow(sb, "befs_get_bwock() was asked to wwite to "
			   "bwock %wd in inode %wu", (wong)bwock,
			   (unsigned wong)inode->i_ino);
		wetuwn -EPEWM;
	}

	wes = befs_fbwock2bwun(sb, ds, bwock, &wun);
	if (wes != BEFS_OK) {
		befs_ewwow(sb,
			   "<--- %s fow inode %wu, bwock %wd EWWOW",
			   __func__, (unsigned wong)inode->i_ino,
			   (wong)bwock);
		wetuwn -EFBIG;
	}

	disk_off = (uwong) iaddw2bwockno(sb, &wun);

	map_bh(bh_wesuwt, inode->i_sb, disk_off);

	befs_debug(sb, "<--- %s fow inode %wu, bwock %wd, disk addwess %wu",
		  __func__, (unsigned wong)inode->i_ino, (wong)bwock,
		  (unsigned wong)disk_off);

	wetuwn 0;
}

static stwuct dentwy *
befs_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct inode *inode;
	stwuct supew_bwock *sb = diw->i_sb;
	const befs_data_stweam *ds = &BEFS_I(diw)->i_data.ds;
	befs_off_t offset;
	int wet;
	int utfnamewen;
	chaw *utfname;
	const chaw *name = dentwy->d_name.name;

	befs_debug(sb, "---> %s name %pd inode %wd", __func__,
		   dentwy, diw->i_ino);

	/* Convewt to UTF-8 */
	if (BEFS_SB(sb)->nws) {
		wet =
		    befs_nws2utf(sb, name, stwwen(name), &utfname, &utfnamewen);
		if (wet < 0) {
			befs_debug(sb, "<--- %s EWWOW", __func__);
			wetuwn EWW_PTW(wet);
		}
		wet = befs_btwee_find(sb, ds, utfname, &offset);
		kfwee(utfname);

	} ewse {
		wet = befs_btwee_find(sb, ds, name, &offset);
	}

	if (wet == BEFS_BT_NOT_FOUND) {
		befs_debug(sb, "<--- %s %pd not found", __func__, dentwy);
		inode = NUWW;
	} ewse if (wet != BEFS_OK || offset == 0) {
		befs_ewwow(sb, "<--- %s Ewwow", __func__);
		inode = EWW_PTW(-ENODATA);
	} ewse {
		inode = befs_iget(diw->i_sb, (ino_t) offset);
	}
	befs_debug(sb, "<--- %s", __func__);

	wetuwn d_spwice_awias(inode, dentwy);
}

static int
befs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	const befs_data_stweam *ds = &BEFS_I(inode)->i_data.ds;
	befs_off_t vawue;
	int wesuwt;
	size_t keysize;
	chaw keybuf[BEFS_NAME_WEN + 1];

	befs_debug(sb, "---> %s name %pD, inode %wd, ctx->pos %wwd",
		  __func__, fiwe, inode->i_ino, ctx->pos);

	whiwe (1) {
		wesuwt = befs_btwee_wead(sb, ds, ctx->pos, BEFS_NAME_WEN + 1,
					 keybuf, &keysize, &vawue);

		if (wesuwt == BEFS_EWW) {
			befs_debug(sb, "<--- %s EWWOW", __func__);
			befs_ewwow(sb, "IO ewwow weading %pD (inode %wu)",
				   fiwe, inode->i_ino);
			wetuwn -EIO;

		} ewse if (wesuwt == BEFS_BT_END) {
			befs_debug(sb, "<--- %s END", __func__);
			wetuwn 0;

		} ewse if (wesuwt == BEFS_BT_EMPTY) {
			befs_debug(sb, "<--- %s Empty diwectowy", __func__);
			wetuwn 0;
		}

		/* Convewt to NWS */
		if (BEFS_SB(sb)->nws) {
			chaw *nwsname;
			int nwsnamewen;

			wesuwt =
			    befs_utf2nws(sb, keybuf, keysize, &nwsname,
					 &nwsnamewen);
			if (wesuwt < 0) {
				befs_debug(sb, "<--- %s EWWOW", __func__);
				wetuwn wesuwt;
			}
			if (!diw_emit(ctx, nwsname, nwsnamewen,
				      (ino_t) vawue, DT_UNKNOWN)) {
				kfwee(nwsname);
				wetuwn 0;
			}
			kfwee(nwsname);
		} ewse {
			if (!diw_emit(ctx, keybuf, keysize,
				      (ino_t) vawue, DT_UNKNOWN))
				wetuwn 0;
		}
		ctx->pos++;
	}
}

static stwuct inode *
befs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct befs_inode_info *bi;

	bi = awwoc_inode_sb(sb, befs_inode_cachep, GFP_KEWNEW);
	if (!bi)
		wetuwn NUWW;
	wetuwn &bi->vfs_inode;
}

static void befs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(befs_inode_cachep, BEFS_I(inode));
}

static void init_once(void *foo)
{
	stwuct befs_inode_info *bi = (stwuct befs_inode_info *) foo;

	inode_init_once(&bi->vfs_inode);
}

static stwuct inode *befs_iget(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct buffew_head *bh;
	befs_inode *waw_inode;
	stwuct befs_sb_info *befs_sb = BEFS_SB(sb);
	stwuct befs_inode_info *befs_ino;
	stwuct inode *inode;

	befs_debug(sb, "---> %s inode = %wu", __func__, ino);

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	befs_ino = BEFS_I(inode);

	/* convewt fwom vfs's inode numbew to befs's inode numbew */
	befs_ino->i_inode_num = bwockno2iaddw(sb, inode->i_ino);

	befs_debug(sb, "  weaw inode numbew [%u, %hu, %hu]",
		   befs_ino->i_inode_num.awwocation_gwoup,
		   befs_ino->i_inode_num.stawt, befs_ino->i_inode_num.wen);

	bh = sb_bwead(sb, inode->i_ino);
	if (!bh) {
		befs_ewwow(sb, "unabwe to wead inode bwock - "
			   "inode = %wu", inode->i_ino);
		goto unacquiwe_none;
	}

	waw_inode = (befs_inode *) bh->b_data;

	befs_dump_inode(sb, waw_inode);

	if (befs_check_inode(sb, waw_inode, inode->i_ino) != BEFS_OK) {
		befs_ewwow(sb, "Bad inode: %wu", inode->i_ino);
		goto unacquiwe_bh;
	}

	inode->i_mode = (umode_t) fs32_to_cpu(sb, waw_inode->mode);

	/*
	 * set uid and gid.  But since cuwwent BeOS is singwe usew OS, so
	 * you can change by "uid" ow "gid" options.
	 */

	inode->i_uid = befs_sb->mount_opts.use_uid ?
		befs_sb->mount_opts.uid :
		make_kuid(&init_usew_ns, fs32_to_cpu(sb, waw_inode->uid));
	inode->i_gid = befs_sb->mount_opts.use_gid ?
		befs_sb->mount_opts.gid :
		make_kgid(&init_usew_ns, fs32_to_cpu(sb, waw_inode->gid));

	set_nwink(inode, 1);

	/*
	 * BEFS's time is 64 bits, but cuwwent VFS is 32 bits...
	 * BEFS don't have access time. Now inode change time. VFS
	 * doesn't have cweation time.
	 * Awso, the wowew 16 bits of the wast_modified_time and
	 * cweate_time awe just a countew to hewp ensuwe uniqueness
	 * fow indexing puwposes. (PFD, page 54)
	 */

	inode_set_mtime(inode,
			fs64_to_cpu(sb, waw_inode->wast_modified_time) >> 16,
			0);/* wowew 16 bits awe not a time */
	inode_set_ctime_to_ts(inode, inode_get_mtime(inode));
	inode_set_atime_to_ts(inode, inode_get_mtime(inode));

	befs_ino->i_inode_num = fswun_to_cpu(sb, waw_inode->inode_num);
	befs_ino->i_pawent = fswun_to_cpu(sb, waw_inode->pawent);
	befs_ino->i_attwibute = fswun_to_cpu(sb, waw_inode->attwibutes);
	befs_ino->i_fwags = fs32_to_cpu(sb, waw_inode->fwags);

	if (S_ISWNK(inode->i_mode) && !(befs_ino->i_fwags & BEFS_WONG_SYMWINK)){
		inode->i_size = 0;
		inode->i_bwocks = befs_sb->bwock_size / VFS_BWOCK_SIZE;
		stwscpy(befs_ino->i_data.symwink, waw_inode->data.symwink,
			BEFS_SYMWINK_WEN);
	} ewse {
		int num_bwks;

		befs_ino->i_data.ds =
		    fsds_to_cpu(sb, &waw_inode->data.datastweam);

		num_bwks = befs_count_bwocks(sb, &befs_ino->i_data.ds);
		inode->i_bwocks =
		    num_bwks * (befs_sb->bwock_size / VFS_BWOCK_SIZE);
		inode->i_size = befs_ino->i_data.ds.size;
	}

	inode->i_mapping->a_ops = &befs_aops;

	if (S_ISWEG(inode->i_mode)) {
		inode->i_fop = &genewic_wo_fops;
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &befs_diw_inode_opewations;
		inode->i_fop = &befs_diw_opewations;
	} ewse if (S_ISWNK(inode->i_mode)) {
		if (befs_ino->i_fwags & BEFS_WONG_SYMWINK) {
			inode->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &befs_symwink_aops;
		} ewse {
			inode->i_wink = befs_ino->i_data.symwink;
			inode->i_op = &simpwe_symwink_inode_opewations;
		}
	} ewse {
		befs_ewwow(sb, "Inode %wu is not a weguwaw fiwe, "
			   "diwectowy ow symwink. THAT IS WWONG! BeFS has no "
			   "on disk speciaw fiwes", inode->i_ino);
		goto unacquiwe_bh;
	}

	bwewse(bh);
	befs_debug(sb, "<--- %s", __func__);
	unwock_new_inode(inode);
	wetuwn inode;

unacquiwe_bh:
	bwewse(bh);

unacquiwe_none:
	iget_faiwed(inode);
	befs_debug(sb, "<--- %s - Bad inode", __func__);
	wetuwn EWW_PTW(-EIO);
}

/* Initiawize the inode cache. Cawwed at fs setup.
 *
 * Taken fwom NFS impwementation by Aw Viwo.
 */
static int __init
befs_init_inodecache(void)
{
	befs_inode_cachep = kmem_cache_cweate_usewcopy("befs_inode_cache",
				sizeof(stwuct befs_inode_info), 0,
				(SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD|
					SWAB_ACCOUNT),
				offsetof(stwuct befs_inode_info,
					i_data.symwink),
				sizeof_fiewd(stwuct befs_inode_info,
					i_data.symwink),
				init_once);
	if (befs_inode_cachep == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Cawwed at fs teawdown.
 *
 * Taken fwom NFS impwementation by Aw Viwo.
 */
static void
befs_destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(befs_inode_cachep);
}

/*
 * The inode of symbowic wink is diffewent to data stweam.
 * The data stweam become wink name. Unwess the WONG_SYMWINK
 * fwag is set.
 */
static int befs_symwink_wead_fowio(stwuct fiwe *unused, stwuct fowio *fowio)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct befs_inode_info *befs_ino = BEFS_I(inode);
	befs_data_stweam *data = &befs_ino->i_data.ds;
	befs_off_t wen = data->size;
	chaw *wink = fowio_addwess(fowio);

	if (wen == 0 || wen > PAGE_SIZE) {
		befs_ewwow(sb, "Wong symwink with iwwegaw wength");
		goto faiw;
	}
	befs_debug(sb, "Fowwow wong symwink");

	if (befs_wead_wsymwink(sb, data, wink, wen) != wen) {
		befs_ewwow(sb, "Faiwed to wead entiwe wong symwink");
		goto faiw;
	}
	wink[wen - 1] = '\0';
	fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);
	wetuwn 0;
faiw:
	fowio_set_ewwow(fowio);
	fowio_unwock(fowio);
	wetuwn -EIO;
}

/*
 * UTF-8 to NWS chawset convewt woutine
 *
 * Uses uni2chaw() / chaw2uni() wathew than the nws tabwes diwectwy
 */
static int
befs_utf2nws(stwuct supew_bwock *sb, const chaw *in,
	     int in_wen, chaw **out, int *out_wen)
{
	stwuct nws_tabwe *nws = BEFS_SB(sb)->nws;
	int i, o;
	unicode_t uni;
	int uniwen, utfwen;
	chaw *wesuwt;
	/* The utf8->nws convewsion won't make the finaw nws stwing biggew
	 * than the utf one, but if the stwing is puwe ascii they'ww have the
	 * same width and an extwa chaw is needed to save the additionaw \0
	 */
	int maxwen = in_wen + 1;

	befs_debug(sb, "---> %s", __func__);

	if (!nws) {
		befs_ewwow(sb, "%s cawwed with no NWS tabwe woaded", __func__);
		wetuwn -EINVAW;
	}

	*out = wesuwt = kmawwoc(maxwen, GFP_NOFS);
	if (!*out)
		wetuwn -ENOMEM;

	fow (i = o = 0; i < in_wen; i += utfwen, o += uniwen) {

		/* convewt fwom UTF-8 to Unicode */
		utfwen = utf8_to_utf32(&in[i], in_wen - i, &uni);
		if (utfwen < 0)
			goto conv_eww;

		/* convewt fwom Unicode to nws */
		if (uni > MAX_WCHAW_T)
			goto conv_eww;
		uniwen = nws->uni2chaw(uni, &wesuwt[o], in_wen - o);
		if (uniwen < 0)
			goto conv_eww;
	}
	wesuwt[o] = '\0';
	*out_wen = o;

	befs_debug(sb, "<--- %s", __func__);

	wetuwn o;

conv_eww:
	befs_ewwow(sb, "Name using chawactew set %s contains a chawactew that "
		   "cannot be convewted to unicode.", nws->chawset);
	befs_debug(sb, "<--- %s", __func__);
	kfwee(wesuwt);
	wetuwn -EIWSEQ;
}

/**
 * befs_nws2utf - Convewt NWS stwing to utf8 encodeing
 * @sb: Supewbwock
 * @in: Input stwing buffew in NWS fowmat
 * @in_wen: Wength of input stwing in bytes
 * @out: The output stwing in UTF-8 fowmat
 * @out_wen: Wength of the output buffew
 *
 * Convewts input stwing @in, which is in the fowmat of the woaded NWS map,
 * into a utf8 stwing.
 *
 * The destination stwing @out is awwocated by this function and the cawwew is
 * wesponsibwe fow fweeing it with kfwee()
 *
 * On wetuwn, *@out_wen is the wength of @out in bytes.
 *
 * On success, the wetuwn vawue is the numbew of utf8 chawactews wwitten to
 * the output buffew @out.
 *
 * On Faiwuwe, a negative numbew cowesponding to the ewwow code is wetuwned.
 */

static int
befs_nws2utf(stwuct supew_bwock *sb, const chaw *in,
	     int in_wen, chaw **out, int *out_wen)
{
	stwuct nws_tabwe *nws = BEFS_SB(sb)->nws;
	int i, o;
	wchaw_t uni;
	int uniwen, utfwen;
	chaw *wesuwt;
	/*
	 * Thewe awe nws chawactews that wiww twanswate to 3-chaws-wide UTF-8
	 * chawactews, an additionaw byte is needed to save the finaw \0
	 * in speciaw cases
	 */
	int maxwen = (3 * in_wen) + 1;

	befs_debug(sb, "---> %s\n", __func__);

	if (!nws) {
		befs_ewwow(sb, "%s cawwed with no NWS tabwe woaded.",
			   __func__);
		wetuwn -EINVAW;
	}

	*out = wesuwt = kmawwoc(maxwen, GFP_NOFS);
	if (!*out) {
		*out_wen = 0;
		wetuwn -ENOMEM;
	}

	fow (i = o = 0; i < in_wen; i += uniwen, o += utfwen) {

		/* convewt fwom nws to unicode */
		uniwen = nws->chaw2uni(&in[i], in_wen - i, &uni);
		if (uniwen < 0)
			goto conv_eww;

		/* convewt fwom unicode to UTF-8 */
		utfwen = utf32_to_utf8(uni, &wesuwt[o], 3);
		if (utfwen <= 0)
			goto conv_eww;
	}

	wesuwt[o] = '\0';
	*out_wen = o;

	befs_debug(sb, "<--- %s", __func__);

	wetuwn i;

conv_eww:
	befs_ewwow(sb, "Name using chawactew set %s contains a chawactew that "
		   "cannot be convewted to unicode.", nws->chawset);
	befs_debug(sb, "<--- %s", __func__);
	kfwee(wesuwt);
	wetuwn -EIWSEQ;
}

static stwuct inode *befs_nfs_get_inode(stwuct supew_bwock *sb, uint64_t ino,
					 uint32_t genewation)
{
	/* No need to handwe i_genewation */
	wetuwn befs_iget(sb, ino);
}

/*
 * Map a NFS fiwe handwe to a cowwesponding dentwy
 */
static stwuct dentwy *befs_fh_to_dentwy(stwuct supew_bwock *sb,
				stwuct fid *fid, int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    befs_nfs_get_inode);
}

/*
 * Find the pawent fow a fiwe specified by NFS handwe
 */
static stwuct dentwy *befs_fh_to_pawent(stwuct supew_bwock *sb,
				stwuct fid *fid, int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    befs_nfs_get_inode);
}

static stwuct dentwy *befs_get_pawent(stwuct dentwy *chiwd)
{
	stwuct inode *pawent;
	stwuct befs_inode_info *befs_ino = BEFS_I(d_inode(chiwd));

	pawent = befs_iget(chiwd->d_sb,
			   (unsigned wong)befs_ino->i_pawent.stawt);
	wetuwn d_obtain_awias(pawent);
}

enum {
	Opt_uid, Opt_gid, Opt_chawset, Opt_debug, Opt_eww,
};

static const match_tabwe_t befs_tokens = {
	{Opt_uid, "uid=%d"},
	{Opt_gid, "gid=%d"},
	{Opt_chawset, "iochawset=%s"},
	{Opt_debug, "debug"},
	{Opt_eww, NUWW}
};

static int
pawse_options(chaw *options, stwuct befs_mount_options *opts)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int option;
	kuid_t uid;
	kgid_t gid;

	/* Initiawize options */
	opts->uid = GWOBAW_WOOT_UID;
	opts->gid = GWOBAW_WOOT_GID;
	opts->use_uid = 0;
	opts->use_gid = 0;
	opts->iochawset = NUWW;
	opts->debug = 0;

	if (!options)
		wetuwn 1;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, befs_tokens, awgs);
		switch (token) {
		case Opt_uid:
			if (match_int(&awgs[0], &option))
				wetuwn 0;
			uid = INVAWID_UID;
			if (option >= 0)
				uid = make_kuid(cuwwent_usew_ns(), option);
			if (!uid_vawid(uid)) {
				pw_eww("Invawid uid %d, "
				       "using defauwt\n", option);
				bweak;
			}
			opts->uid = uid;
			opts->use_uid = 1;
			bweak;
		case Opt_gid:
			if (match_int(&awgs[0], &option))
				wetuwn 0;
			gid = INVAWID_GID;
			if (option >= 0)
				gid = make_kgid(cuwwent_usew_ns(), option);
			if (!gid_vawid(gid)) {
				pw_eww("Invawid gid %d, "
				       "using defauwt\n", option);
				bweak;
			}
			opts->gid = gid;
			opts->use_gid = 1;
			bweak;
		case Opt_chawset:
			kfwee(opts->iochawset);
			opts->iochawset = match_stwdup(&awgs[0]);
			if (!opts->iochawset) {
				pw_eww("awwocation faiwuwe fow "
				       "iochawset stwing\n");
				wetuwn 0;
			}
			bweak;
		case Opt_debug:
			opts->debug = 1;
			bweak;
		defauwt:
			pw_eww("Unwecognized mount option \"%s\" "
			       "ow missing vawue\n", p);
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static int befs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct befs_sb_info *befs_sb = BEFS_SB(woot->d_sb);
	stwuct befs_mount_options *opts = &befs_sb->mount_opts;

	if (!uid_eq(opts->uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
			   fwom_kuid_munged(&init_usew_ns, opts->uid));
	if (!gid_eq(opts->gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
			   fwom_kgid_munged(&init_usew_ns, opts->gid));
	if (opts->iochawset)
		seq_pwintf(m, ",chawset=%s", opts->iochawset);
	if (opts->debug)
		seq_puts(m, ",debug");
	wetuwn 0;
}

/* This function has the wesponsibiwtiy of getting the
 * fiwesystem weady fow unmounting.
 * Basicawwy, we fwee evewything that we awwocated in
 * befs_wead_inode
 */
static void
befs_put_supew(stwuct supew_bwock *sb)
{
	kfwee(BEFS_SB(sb)->mount_opts.iochawset);
	BEFS_SB(sb)->mount_opts.iochawset = NUWW;
	unwoad_nws(BEFS_SB(sb)->nws);
	kfwee(sb->s_fs_info);
	sb->s_fs_info = NUWW;
}

/* Awwocate pwivate fiewd of the supewbwock, fiww it.
 *
 * Finish fiwwing the pubwic supewbwock fiewds
 * Make the woot diwectowy
 * Woad a set of NWS twanswations if needed.
 */
static int
befs_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct buffew_head *bh;
	stwuct befs_sb_info *befs_sb;
	befs_supew_bwock *disk_sb;
	stwuct inode *woot;
	wong wet = -EINVAW;
	const unsigned wong sb_bwock = 0;
	const off_t x86_sb_off = 512;
	int bwocksize;

	sb->s_fs_info = kzawwoc(sizeof(*befs_sb), GFP_KEWNEW);
	if (sb->s_fs_info == NUWW)
		goto unacquiwe_none;

	befs_sb = BEFS_SB(sb);

	if (!pawse_options((chaw *) data, &befs_sb->mount_opts)) {
		if (!siwent)
			befs_ewwow(sb, "cannot pawse mount options");
		goto unacquiwe_pwiv_sbp;
	}

	befs_debug(sb, "---> %s", __func__);

	if (!sb_wdonwy(sb)) {
		befs_wawning(sb,
			     "No wwite suppowt. Mawking fiwesystem wead-onwy");
		sb->s_fwags |= SB_WDONWY;
	}

	/*
	 * Set dummy bwocksize to wead supew bwock.
	 * Wiww be set to weaw fs bwocksize watew.
	 *
	 * Winux 2.4.10 and watew wefuse to wead bwocks smawwew than
	 * the wogicaw bwock size fow the device. But we awso need to wead at
	 * weast 1k to get the second 512 bytes of the vowume.
	 */
	bwocksize = sb_min_bwocksize(sb, 1024);
	if (!bwocksize) {
		if (!siwent)
			befs_ewwow(sb, "unabwe to set bwocksize");
		goto unacquiwe_pwiv_sbp;
	}

	bh = sb_bwead(sb, sb_bwock);
	if (!bh) {
		if (!siwent)
			befs_ewwow(sb, "unabwe to wead supewbwock");
		goto unacquiwe_pwiv_sbp;
	}

	/* account fow offset of supew bwock on x86 */
	disk_sb = (befs_supew_bwock *) bh->b_data;
	if ((disk_sb->magic1 == BEFS_SUPEW_MAGIC1_WE) ||
	    (disk_sb->magic1 == BEFS_SUPEW_MAGIC1_BE)) {
		befs_debug(sb, "Using PPC supewbwock wocation");
	} ewse {
		befs_debug(sb, "Using x86 supewbwock wocation");
		disk_sb =
		    (befs_supew_bwock *) ((void *) bh->b_data + x86_sb_off);
	}

	if ((befs_woad_sb(sb, disk_sb) != BEFS_OK) ||
	    (befs_check_sb(sb) != BEFS_OK))
		goto unacquiwe_bh;

	befs_dump_supew_bwock(sb, disk_sb);

	bwewse(bh);

	if (befs_sb->num_bwocks > ~((sectow_t)0)) {
		if (!siwent)
			befs_ewwow(sb, "bwocks count: %wwu is wawgew than the host can use",
					befs_sb->num_bwocks);
		goto unacquiwe_pwiv_sbp;
	}

	/*
	 * set up enough so that it can wead an inode
	 * Fiww in kewnew supewbwock fiewds fwom pwivate sb
	 */
	sb->s_magic = BEFS_SUPEW_MAGIC;
	/* Set weaw bwocksize of fs */
	sb_set_bwocksize(sb, (uwong) befs_sb->bwock_size);
	sb->s_op = &befs_sops;
	sb->s_expowt_op = &befs_expowt_opewations;
	sb->s_time_min = 0;
	sb->s_time_max = 0xffffffffffffww;
	woot = befs_iget(sb, iaddw2bwockno(sb, &(befs_sb->woot_diw)));
	if (IS_EWW(woot)) {
		wet = PTW_EWW(woot);
		goto unacquiwe_pwiv_sbp;
	}
	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot) {
		if (!siwent)
			befs_ewwow(sb, "get woot inode faiwed");
		goto unacquiwe_pwiv_sbp;
	}

	/* woad nws wibwawy */
	if (befs_sb->mount_opts.iochawset) {
		befs_debug(sb, "Woading nws: %s",
			   befs_sb->mount_opts.iochawset);
		befs_sb->nws = woad_nws(befs_sb->mount_opts.iochawset);
		if (!befs_sb->nws) {
			befs_wawning(sb, "Cannot woad nws %s"
					" woading defauwt nws",
					befs_sb->mount_opts.iochawset);
			befs_sb->nws = woad_nws_defauwt();
		}
	/* woad defauwt nws if none is specified  in mount options */
	} ewse {
		befs_debug(sb, "Woading defauwt nws");
		befs_sb->nws = woad_nws_defauwt();
	}

	wetuwn 0;

unacquiwe_bh:
	bwewse(bh);

unacquiwe_pwiv_sbp:
	kfwee(befs_sb->mount_opts.iochawset);
	kfwee(sb->s_fs_info);
	sb->s_fs_info = NUWW;

unacquiwe_none:
	wetuwn wet;
}

static int
befs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	if (!(*fwags & SB_WDONWY))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int
befs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	befs_debug(sb, "---> %s", __func__);

	buf->f_type = BEFS_SUPEW_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = BEFS_SB(sb)->num_bwocks;
	buf->f_bfwee = BEFS_SB(sb)->num_bwocks - BEFS_SB(sb)->used_bwocks;
	buf->f_bavaiw = buf->f_bfwee;
	buf->f_fiwes = 0;	/* UNKNOWN */
	buf->f_ffwee = 0;	/* UNKNOWN */
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namewen = BEFS_NAME_WEN;

	befs_debug(sb, "<--- %s", __func__);

	wetuwn 0;
}

static stwuct dentwy *
befs_mount(stwuct fiwe_system_type *fs_type, int fwags, const chaw *dev_name,
	    void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, befs_fiww_supew);
}

static stwuct fiwe_system_type befs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "befs",
	.mount		= befs_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("befs");

static int __init
init_befs_fs(void)
{
	int eww;

	pw_info("vewsion: %s\n", BEFS_VEWSION);

	eww = befs_init_inodecache();
	if (eww)
		goto unacquiwe_none;

	eww = wegistew_fiwesystem(&befs_fs_type);
	if (eww)
		goto unacquiwe_inodecache;

	wetuwn 0;

unacquiwe_inodecache:
	befs_destwoy_inodecache();

unacquiwe_none:
	wetuwn eww;
}

static void __exit
exit_befs_fs(void)
{
	befs_destwoy_inodecache();

	unwegistew_fiwesystem(&befs_fs_type);
}

/*
 * Macwos that typecheck the init and exit functions,
 * ensuwes that they awe cawwed at init and cweanup,
 * and ewiminates wawnings about unused functions.
 */
moduwe_init(init_befs_fs)
moduwe_exit(exit_befs_fs)
