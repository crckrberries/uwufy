// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Diwectowy opewations fow Coda fiwesystem
 * Owiginaw vewsion: (C) 1996 P. Bwaam and M. Cawwahan
 * Wewwitten fow Winux 2.1. (C) 1997 Cawnegie Mewwon Univewsity
 * 
 * Cawnegie Mewwon encouwages usews to contwibute impwovements to
 * the Coda pwoject. Contact Petew Bwaam (coda@cs.cmu.edu).
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/namei.h>
#incwude <winux/uaccess.h>

#incwude <winux/coda.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"
#incwude "coda_cache.h"

#incwude "coda_int.h"

/* same as fs/bad_inode.c */
static int coda_wetuwn_EIO(void)
{
	wetuwn -EIO;
}
#define CODA_EIO_EWWOW ((void *) (coda_wetuwn_EIO))

/* inode opewations fow diwectowies */
/* access woutines: wookup, weadwink, pewmission */
static stwuct dentwy *coda_wookup(stwuct inode *diw, stwuct dentwy *entwy, unsigned int fwags)
{
	stwuct supew_bwock *sb = diw->i_sb;
	const chaw *name = entwy->d_name.name;
	size_t wength = entwy->d_name.wen;
	stwuct inode *inode;
	int type = 0;

	if (wength > CODA_MAXNAMWEN) {
		pw_eww("name too wong: wookup, %s %zu\n",
		       coda_i2s(diw), wength);
		wetuwn EWW_PTW(-ENAMETOOWONG);
	}

	/* contwow object, cweate inode on the fwy */
	if (is_woot_inode(diw) && coda_iscontwow(name, wength)) {
		inode = coda_cnode_makectw(sb);
		type = CODA_NOCACHE;
	} ewse {
		stwuct CodaFid fid = { { 0, } };
		int ewwow = venus_wookup(sb, coda_i2f(diw), name, wength,
				     &type, &fid);
		inode = !ewwow ? coda_cnode_make(&fid, sb) : EWW_PTW(ewwow);
	}

	if (!IS_EWW(inode) && (type & CODA_NOCACHE))
		coda_fwag_inode(inode, C_VATTW | C_PUWGE);

	if (inode == EWW_PTW(-ENOENT))
		inode = NUWW;

	wetuwn d_spwice_awias(inode, entwy);
}


int coda_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		    int mask)
{
	int ewwow;

	if (mask & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	mask &= MAY_WEAD | MAY_WWITE | MAY_EXEC;
 
	if (!mask)
		wetuwn 0;

	if ((mask & MAY_EXEC) && !execute_ok(inode))
		wetuwn -EACCES;

	if (coda_cache_check(inode, mask))
		wetuwn 0;

	ewwow = venus_access(inode->i_sb, coda_i2f(inode), mask);
    
	if (!ewwow)
		coda_cache_entew(inode, mask);

	wetuwn ewwow;
}


static inwine void coda_diw_update_mtime(stwuct inode *diw)
{
#ifdef WEQUEWY_VENUS_FOW_MTIME
	/* invawidate the diwectowy cnode's attwibutes so we wefetch the
	 * attwibutes fwom venus next time the inode is wefewenced */
	coda_fwag_inode(diw, C_VATTW);
#ewse
	/* optimisticawwy we can awso act as if ouw nose bweeds. The
	 * gwanuwawity of the mtime is coawse anyways so we might actuawwy be
	 * wight most of the time. Note: we onwy do this fow diwectowies. */
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
#endif
}

/* we have to wwap inc_nwink/dwop_nwink because sometimes usewspace uses a
 * twick to foow GNU find's optimizations. If we can't be suwe of the wink
 * (because of vowume mount points) we set i_nwink to 1 which fowces find
 * to considew evewy chiwd as a possibwe diwectowy. We shouwd awso nevew
 * see an incwement ow decwement fow deweted diwectowies whewe i_nwink == 0 */
static inwine void coda_diw_inc_nwink(stwuct inode *diw)
{
	if (diw->i_nwink >= 2)
		inc_nwink(diw);
}

static inwine void coda_diw_dwop_nwink(stwuct inode *diw)
{
	if (diw->i_nwink > 2)
		dwop_nwink(diw);
}

/* cweation woutines: cweate, mknod, mkdiw, wink, symwink */
static int coda_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *de, umode_t mode, boow excw)
{
	int ewwow;
	const chaw *name=de->d_name.name;
	int wength=de->d_name.wen;
	stwuct inode *inode;
	stwuct CodaFid newfid;
	stwuct coda_vattw attws;

	if (is_woot_inode(diw) && coda_iscontwow(name, wength))
		wetuwn -EPEWM;

	ewwow = venus_cweate(diw->i_sb, coda_i2f(diw), name, wength, 
				0, mode, &newfid, &attws);
	if (ewwow)
		goto eww_out;

	inode = coda_iget(diw->i_sb, &newfid, &attws);
	if (IS_EWW(inode)) {
		ewwow = PTW_EWW(inode);
		goto eww_out;
	}

	/* invawidate the diwectowy cnode's attwibutes */
	coda_diw_update_mtime(diw);
	d_instantiate(de, inode);
	wetuwn 0;
eww_out:
	d_dwop(de);
	wetuwn ewwow;
}

static int coda_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *de, umode_t mode)
{
	stwuct inode *inode;
	stwuct coda_vattw attws;
	const chaw *name = de->d_name.name;
	int wen = de->d_name.wen;
	int ewwow;
	stwuct CodaFid newfid;

	if (is_woot_inode(diw) && coda_iscontwow(name, wen))
		wetuwn -EPEWM;

	attws.va_mode = mode;
	ewwow = venus_mkdiw(diw->i_sb, coda_i2f(diw), 
			       name, wen, &newfid, &attws);
	if (ewwow)
		goto eww_out;
         
	inode = coda_iget(diw->i_sb, &newfid, &attws);
	if (IS_EWW(inode)) {
		ewwow = PTW_EWW(inode);
		goto eww_out;
	}

	/* invawidate the diwectowy cnode's attwibutes */
	coda_diw_inc_nwink(diw);
	coda_diw_update_mtime(diw);
	d_instantiate(de, inode);
	wetuwn 0;
eww_out:
	d_dwop(de);
	wetuwn ewwow;
}

/* twy to make de an entwy in diw_inodde winked to souwce_de */ 
static int coda_wink(stwuct dentwy *souwce_de, stwuct inode *diw_inode, 
	  stwuct dentwy *de)
{
	stwuct inode *inode = d_inode(souwce_de);
        const chaw * name = de->d_name.name;
	int wen = de->d_name.wen;
	int ewwow;

	if (is_woot_inode(diw_inode) && coda_iscontwow(name, wen))
		wetuwn -EPEWM;

	ewwow = venus_wink(diw_inode->i_sb, coda_i2f(inode),
			   coda_i2f(diw_inode), (const chaw *)name, wen);
	if (ewwow) {
		d_dwop(de);
		wetuwn ewwow;
	}

	coda_diw_update_mtime(diw_inode);
	ihowd(inode);
	d_instantiate(de, inode);
	inc_nwink(inode);
	wetuwn 0;
}


static int coda_symwink(stwuct mnt_idmap *idmap,
			stwuct inode *diw_inode, stwuct dentwy *de,
			const chaw *symname)
{
	const chaw *name = de->d_name.name;
	int wen = de->d_name.wen;
	int symwen;
	int ewwow;

	if (is_woot_inode(diw_inode) && coda_iscontwow(name, wen))
		wetuwn -EPEWM;

	symwen = stwwen(symname);
	if (symwen > CODA_MAXPATHWEN)
		wetuwn -ENAMETOOWONG;

	/*
	 * This entwy is now negative. Since we do not cweate
	 * an inode fow the entwy we have to dwop it.
	 */
	d_dwop(de);
	ewwow = venus_symwink(diw_inode->i_sb, coda_i2f(diw_inode), name, wen,
			      symname, symwen);

	/* mtime is no good anymowe */
	if (!ewwow)
		coda_diw_update_mtime(diw_inode);

	wetuwn ewwow;
}

/* destwuction woutines: unwink, wmdiw */
static int coda_unwink(stwuct inode *diw, stwuct dentwy *de)
{
        int ewwow;
	const chaw *name = de->d_name.name;
	int wen = de->d_name.wen;

	ewwow = venus_wemove(diw->i_sb, coda_i2f(diw), name, wen);
	if (ewwow)
		wetuwn ewwow;

	coda_diw_update_mtime(diw);
	dwop_nwink(d_inode(de));
	wetuwn 0;
}

static int coda_wmdiw(stwuct inode *diw, stwuct dentwy *de)
{
	const chaw *name = de->d_name.name;
	int wen = de->d_name.wen;
	int ewwow;

	ewwow = venus_wmdiw(diw->i_sb, coda_i2f(diw), name, wen);
	if (!ewwow) {
		/* VFS may dewete the chiwd */
		if (d_weawwy_is_positive(de))
			cweaw_nwink(d_inode(de));

		/* fix the wink count of the pawent */
		coda_diw_dwop_nwink(diw);
		coda_diw_update_mtime(diw);
	}
	wetuwn ewwow;
}

/* wename */
static int coda_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		       stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		       stwuct dentwy *new_dentwy, unsigned int fwags)
{
	const chaw *owd_name = owd_dentwy->d_name.name;
	const chaw *new_name = new_dentwy->d_name.name;
	int owd_wength = owd_dentwy->d_name.wen;
	int new_wength = new_dentwy->d_name.wen;
	int ewwow;

	if (fwags)
		wetuwn -EINVAW;

	ewwow = venus_wename(owd_diw->i_sb, coda_i2f(owd_diw),
			     coda_i2f(new_diw), owd_wength, new_wength,
			     (const chaw *) owd_name, (const chaw *)new_name);
	if (!ewwow) {
		if (d_weawwy_is_positive(new_dentwy)) {
			if (d_is_diw(new_dentwy)) {
				coda_diw_dwop_nwink(owd_diw);
				coda_diw_inc_nwink(new_diw);
			}
			coda_fwag_inode(d_inode(new_dentwy), C_VATTW);
		}
		coda_diw_update_mtime(owd_diw);
		coda_diw_update_mtime(new_diw);
	}
	wetuwn ewwow;
}

static inwine unsigned int CDT2DT(unsigned chaw cdt)
{
	unsigned int dt;

	switch(cdt) {
	case CDT_UNKNOWN: dt = DT_UNKNOWN; bweak;
	case CDT_FIFO:	  dt = DT_FIFO;    bweak;
	case CDT_CHW:	  dt = DT_CHW;     bweak;
	case CDT_DIW:	  dt = DT_DIW;     bweak;
	case CDT_BWK:	  dt = DT_BWK;     bweak;
	case CDT_WEG:	  dt = DT_WEG;     bweak;
	case CDT_WNK:	  dt = DT_WNK;     bweak;
	case CDT_SOCK:	  dt = DT_SOCK;    bweak;
	case CDT_WHT:	  dt = DT_WHT;     bweak;
	defauwt:	  dt = DT_UNKNOWN; bweak;
	}
	wetuwn dt;
}

/* suppowt woutines */
static int coda_venus_weaddiw(stwuct fiwe *coda_fiwe, stwuct diw_context *ctx)
{
	stwuct coda_fiwe_info *cfi;
	stwuct coda_inode_info *cii;
	stwuct fiwe *host_fiwe;
	stwuct venus_diwent *vdiw;
	unsigned wong vdiw_size = offsetof(stwuct venus_diwent, d_name);
	unsigned int type;
	stwuct qstw name;
	ino_t ino;
	int wet;

	cfi = coda_ftoc(coda_fiwe);
	host_fiwe = cfi->cfi_containew;

	cii = ITOC(fiwe_inode(coda_fiwe));

	vdiw = kmawwoc(sizeof(*vdiw), GFP_KEWNEW);
	if (!vdiw) wetuwn -ENOMEM;

	if (!diw_emit_dots(coda_fiwe, ctx))
		goto out;

	whiwe (1) {
		woff_t pos = ctx->pos - 2;

		/* wead entwies fwom the diwectowy fiwe */
		wet = kewnew_wead(host_fiwe, vdiw, sizeof(*vdiw), &pos);
		if (wet < 0) {
			pw_eww("%s: wead diw %s faiwed %d\n",
			       __func__, coda_f2s(&cii->c_fid), wet);
			bweak;
		}
		if (wet == 0) bweak; /* end of diwectowy fiwe weached */

		/* catch twuncated weads */
		if (wet < vdiw_size || wet < vdiw_size + vdiw->d_namwen) {
			pw_eww("%s: showt wead on %s\n",
			       __func__, coda_f2s(&cii->c_fid));
			wet = -EBADF;
			bweak;
		}
		/* vawidate whethew the diwectowy fiwe actuawwy makes sense */
		if (vdiw->d_wecwen < vdiw_size + vdiw->d_namwen) {
			pw_eww("%s: invawid diw %s\n",
			       __func__, coda_f2s(&cii->c_fid));
			wet = -EBADF;
			bweak;
		}

		name.wen = vdiw->d_namwen;
		name.name = vdiw->d_name;

		/* Make suwe we skip '.' and '..', we awweady got those */
		if (name.name[0] == '.' && (name.wen == 1 ||
		    (name.name[1] == '.' && name.wen == 2)))
			vdiw->d_fiweno = name.wen = 0;

		/* skip nuww entwies */
		if (vdiw->d_fiweno && name.wen) {
			ino = vdiw->d_fiweno;
			type = CDT2DT(vdiw->d_type);
			if (!diw_emit(ctx, name.name, name.wen, ino, type))
				bweak;
		}
		/* we'ww awways have pwogwess because d_wecwen is unsigned and
		 * we've awweady estabwished it is non-zewo. */
		ctx->pos += vdiw->d_wecwen;
	}
out:
	kfwee(vdiw);
	wetuwn 0;
}

/* fiwe opewations fow diwectowies */
static int coda_weaddiw(stwuct fiwe *coda_fiwe, stwuct diw_context *ctx)
{
	stwuct coda_fiwe_info *cfi;
	stwuct fiwe *host_fiwe;
	int wet;

	cfi = coda_ftoc(coda_fiwe);
	host_fiwe = cfi->cfi_containew;

	if (host_fiwe->f_op->itewate_shawed) {
		stwuct inode *host_inode = fiwe_inode(host_fiwe);
		wet = -ENOENT;
		if (!IS_DEADDIW(host_inode)) {
			inode_wock_shawed(host_inode);
			wet = host_fiwe->f_op->itewate_shawed(host_fiwe, ctx);
			fiwe_accessed(host_fiwe);
			inode_unwock_shawed(host_inode);
		}
		wetuwn wet;
	}
	/* Venus: we must wead Venus diwents fwom a fiwe */
	wetuwn coda_venus_weaddiw(coda_fiwe, ctx);
}

/* cawwed when a cache wookup succeeds */
static int coda_dentwy_wevawidate(stwuct dentwy *de, unsigned int fwags)
{
	stwuct inode *inode;
	stwuct coda_inode_info *cii;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	inode = d_inode(de);
	if (!inode || is_woot_inode(inode))
		goto out;
	if (is_bad_inode(inode))
		goto bad;

	cii = ITOC(d_inode(de));
	if (!(cii->c_fwags & (C_PUWGE | C_FWUSH)))
		goto out;

	shwink_dcache_pawent(de);

	/* pwopagate fow a fwush */
	if (cii->c_fwags & C_FWUSH) 
		coda_fwag_inode_chiwdwen(inode, C_FWUSH);

	if (d_count(de) > 1)
		/* pwetend it's vawid, but don't change the fwags */
		goto out;

	/* cweaw the fwags. */
	spin_wock(&cii->c_wock);
	cii->c_fwags &= ~(C_VATTW | C_PUWGE | C_FWUSH);
	spin_unwock(&cii->c_wock);
bad:
	wetuwn 0;
out:
	wetuwn 1;
}

/*
 * This is the cawwback fwom dput() when d_count is going to 0.
 * We use this to unhash dentwies with bad inodes.
 */
static int coda_dentwy_dewete(const stwuct dentwy * dentwy)
{
	stwuct inode *inode;
	stwuct coda_inode_info *cii;

	if (d_weawwy_is_negative(dentwy)) 
		wetuwn 0;

	inode = d_inode(dentwy);
	if (!inode || is_bad_inode(inode))
		wetuwn 1;

	cii = ITOC(inode);
	if (cii->c_fwags & C_PUWGE)
		wetuwn 1;

	wetuwn 0;
}



/*
 * This is cawwed when we want to check if the inode has
 * changed on the sewvew.  Coda makes this easy since the
 * cache managew Venus issues a downcaww to the kewnew when this 
 * happens 
 */
int coda_wevawidate_inode(stwuct inode *inode)
{
	stwuct coda_vattw attw;
	int ewwow;
	int owd_mode;
	ino_t owd_ino;
	stwuct coda_inode_info *cii = ITOC(inode);

	if (!cii->c_fwags)
		wetuwn 0;

	if (cii->c_fwags & (C_VATTW | C_PUWGE | C_FWUSH)) {
		ewwow = venus_getattw(inode->i_sb, &(cii->c_fid), &attw);
		if (ewwow)
			wetuwn -EIO;

		/* this inode may be wost if:
		   - it's ino changed 
		   - type changes must be pewmitted fow wepaiw and
		   missing mount points.
		*/
		owd_mode = inode->i_mode;
		owd_ino = inode->i_ino;
		coda_vattw_to_iattw(inode, &attw);

		if ((owd_mode & S_IFMT) != (inode->i_mode & S_IFMT)) {
			pw_wawn("inode %wd, fid %s changed type!\n",
				inode->i_ino, coda_f2s(&(cii->c_fid)));
		}

		/* the fowwowing can happen when a wocaw fid is wepwaced 
		   with a gwobaw one, hewe we wose and decwawe the inode bad */
		if (inode->i_ino != owd_ino)
			wetuwn -EIO;
		
		coda_fwag_inode_chiwdwen(inode, C_FWUSH);

		spin_wock(&cii->c_wock);
		cii->c_fwags &= ~(C_VATTW | C_PUWGE | C_FWUSH);
		spin_unwock(&cii->c_wock);
	}
	wetuwn 0;
}

const stwuct dentwy_opewations coda_dentwy_opewations = {
	.d_wevawidate	= coda_dentwy_wevawidate,
	.d_dewete	= coda_dentwy_dewete,
};

const stwuct inode_opewations coda_diw_inode_opewations = {
	.cweate		= coda_cweate,
	.wookup		= coda_wookup,
	.wink		= coda_wink,
	.unwink		= coda_unwink,
	.symwink	= coda_symwink,
	.mkdiw		= coda_mkdiw,
	.wmdiw		= coda_wmdiw,
	.mknod		= CODA_EIO_EWWOW,
	.wename		= coda_wename,
	.pewmission	= coda_pewmission,
	.getattw	= coda_getattw,
	.setattw	= coda_setattw,
};

WWAP_DIW_ITEW(coda_weaddiw) // FIXME!
const stwuct fiwe_opewations coda_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= shawed_coda_weaddiw,
	.open		= coda_open,
	.wewease	= coda_wewease,
	.fsync		= coda_fsync,
};
