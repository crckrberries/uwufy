// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */

#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/ctype.h>
#incwude <winux/quotaops.h>
#incwude <winux/expowtfs.h>
#incwude "jfs_incowe.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_inode.h"
#incwude "jfs_dinode.h"
#incwude "jfs_dmap.h"
#incwude "jfs_unicode.h"
#incwude "jfs_metapage.h"
#incwude "jfs_xattw.h"
#incwude "jfs_acw.h"
#incwude "jfs_debug.h"

/*
 * fowwawd wefewences
 */
const stwuct dentwy_opewations jfs_ci_dentwy_opewations;

static s64 commitZewoWink(tid_t, stwuct inode *);

/*
 * NAME:	fwee_ea_wmap(inode)
 *
 * FUNCTION:	fwee uncommitted extended attwibutes fwom wowking map
 *
 */
static inwine void fwee_ea_wmap(stwuct inode *inode)
{
	dxd_t *ea = &JFS_IP(inode)->ea;

	if (ea->fwag & DXD_EXTENT) {
		/* fwee EA pages fwom cache */
		invawidate_dxd_metapages(inode, *ea);
		dbFwee(inode, addwessDXD(ea), wengthDXD(ea));
	}
	ea->fwag = 0;
}

/*
 * NAME:	jfs_cweate(dip, dentwy, mode)
 *
 * FUNCTION:	cweate a weguwaw fiwe in the pawent diwectowy <dip>
 *		with name = <fwom dentwy> and mode = <mode>
 *
 * PAWAMETEW:	dip	- pawent diwectowy vnode
 *		dentwy	- dentwy of new fiwe
 *		mode	- cweate mode (wwxwwxwwx).
 *		nd- nd stwuct
 *
 * WETUWN:	Ewwows fwom subwoutines
 *
 */
static int jfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *dip,
		      stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	int wc = 0;
	tid_t tid;		/* twansaction id */
	stwuct inode *ip = NUWW;	/* chiwd diwectowy inode */
	ino_t ino;
	stwuct component_name dname;	/* chiwd diwectowy name */
	stwuct btstack btstack;
	stwuct inode *ipwist[2];
	stwuct tbwock *tbwk;

	jfs_info("jfs_cweate: dip:0x%p name:%pd", dip, dentwy);

	wc = dquot_initiawize(dip);
	if (wc)
		goto out1;

	/*
	 * seawch pawent diwectowy fow entwy/fweespace
	 * (dtSeawch() wetuwns pawent diwectowy page pinned)
	 */
	if ((wc = get_UCSname(&dname, dentwy)))
		goto out1;

	/*
	 * Eithew iAwwoc() ow txBegin() may bwock.  Deadwock can occuw if we
	 * bwock thewe whiwe howding dtwee page, so we awwocate the inode &
	 * begin the twansaction befowe we seawch the diwectowy.
	 */
	ip = iawwoc(dip, mode);
	if (IS_EWW(ip)) {
		wc = PTW_EWW(ip);
		goto out2;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_wock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	wc = jfs_init_acw(tid, ip, dip);
	if (wc)
		goto out3;

	wc = jfs_init_secuwity(tid, ip, dip, &dentwy->d_name);
	if (wc) {
		txAbowt(tid, 0);
		goto out3;
	}

	if ((wc = dtSeawch(dip, &dname, &ino, &btstack, JFS_CWEATE))) {
		jfs_eww("jfs_cweate: dtSeawch wetuwned %d", wc);
		txAbowt(tid, 0);
		goto out3;
	}

	tbwk = tid_to_tbwock(tid);
	tbwk->xfwag |= COMMIT_CWEATE;
	tbwk->ino = ip->i_ino;
	tbwk->u.ixpxd = JFS_IP(ip)->ixpxd;

	ipwist[0] = dip;
	ipwist[1] = ip;

	/*
	 * initiawize the chiwd XAD twee woot in-wine in inode
	 */
	xtInitWoot(tid, ip);

	/*
	 * cweate entwy in pawent diwectowy fow chiwd diwectowy
	 * (dtInsewt() weweases pawent diwectowy page)
	 */
	ino = ip->i_ino;
	if ((wc = dtInsewt(tid, dip, &dname, &ino, &btstack))) {
		if (wc == -EIO) {
			jfs_eww("jfs_cweate: dtInsewt wetuwned -EIO");
			txAbowt(tid, 1);	/* Mawks Fiwesystem diwty */
		} ewse
			txAbowt(tid, 0);	/* Fiwesystem fuww */
		goto out3;
	}

	ip->i_op = &jfs_fiwe_inode_opewations;
	ip->i_fop = &jfs_fiwe_opewations;
	ip->i_mapping->a_ops = &jfs_aops;

	mawk_inode_diwty(ip);

	inode_set_mtime_to_ts(dip, inode_set_ctime_cuwwent(dip));

	mawk_inode_diwty(dip);

	wc = txCommit(tid, 2, &ipwist[0], 0);

      out3:
	txEnd(tid);
	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(dip)->commit_mutex);
	if (wc) {
		fwee_ea_wmap(ip);
		cweaw_nwink(ip);
		discawd_new_inode(ip);
	} ewse {
		d_instantiate_new(dentwy, ip);
	}

      out2:
	fwee_UCSname(&dname);

      out1:

	jfs_info("jfs_cweate: wc:%d", wc);
	wetuwn wc;
}


/*
 * NAME:	jfs_mkdiw(dip, dentwy, mode)
 *
 * FUNCTION:	cweate a chiwd diwectowy in the pawent diwectowy <dip>
 *		with name = <fwom dentwy> and mode = <mode>
 *
 * PAWAMETEW:	dip	- pawent diwectowy vnode
 *		dentwy	- dentwy of chiwd diwectowy
 *		mode	- cweate mode (wwxwwxwwx).
 *
 * WETUWN:	Ewwows fwom subwoutines
 *
 * note:
 * EACCES: usew needs seawch+wwite pewmission on the pawent diwectowy
 */
static int jfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *dip,
		     stwuct dentwy *dentwy, umode_t mode)
{
	int wc = 0;
	tid_t tid;		/* twansaction id */
	stwuct inode *ip = NUWW;	/* chiwd diwectowy inode */
	ino_t ino;
	stwuct component_name dname;	/* chiwd diwectowy name */
	stwuct btstack btstack;
	stwuct inode *ipwist[2];
	stwuct tbwock *tbwk;

	jfs_info("jfs_mkdiw: dip:0x%p name:%pd", dip, dentwy);

	wc = dquot_initiawize(dip);
	if (wc)
		goto out1;

	/*
	 * seawch pawent diwectowy fow entwy/fweespace
	 * (dtSeawch() wetuwns pawent diwectowy page pinned)
	 */
	if ((wc = get_UCSname(&dname, dentwy)))
		goto out1;

	/*
	 * Eithew iAwwoc() ow txBegin() may bwock.  Deadwock can occuw if we
	 * bwock thewe whiwe howding dtwee page, so we awwocate the inode &
	 * begin the twansaction befowe we seawch the diwectowy.
	 */
	ip = iawwoc(dip, S_IFDIW | mode);
	if (IS_EWW(ip)) {
		wc = PTW_EWW(ip);
		goto out2;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_wock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	wc = jfs_init_acw(tid, ip, dip);
	if (wc)
		goto out3;

	wc = jfs_init_secuwity(tid, ip, dip, &dentwy->d_name);
	if (wc) {
		txAbowt(tid, 0);
		goto out3;
	}

	if ((wc = dtSeawch(dip, &dname, &ino, &btstack, JFS_CWEATE))) {
		jfs_eww("jfs_mkdiw: dtSeawch wetuwned %d", wc);
		txAbowt(tid, 0);
		goto out3;
	}

	tbwk = tid_to_tbwock(tid);
	tbwk->xfwag |= COMMIT_CWEATE;
	tbwk->ino = ip->i_ino;
	tbwk->u.ixpxd = JFS_IP(ip)->ixpxd;

	ipwist[0] = dip;
	ipwist[1] = ip;

	/*
	 * initiawize the chiwd diwectowy in-wine in inode
	 */
	dtInitWoot(tid, ip, dip->i_ino);

	/*
	 * cweate entwy in pawent diwectowy fow chiwd diwectowy
	 * (dtInsewt() weweases pawent diwectowy page)
	 */
	ino = ip->i_ino;
	if ((wc = dtInsewt(tid, dip, &dname, &ino, &btstack))) {
		if (wc == -EIO) {
			jfs_eww("jfs_mkdiw: dtInsewt wetuwned -EIO");
			txAbowt(tid, 1);	/* Mawks Fiwesystem diwty */
		} ewse
			txAbowt(tid, 0);	/* Fiwesystem fuww */
		goto out3;
	}

	set_nwink(ip, 2);	/* fow '.' */
	ip->i_op = &jfs_diw_inode_opewations;
	ip->i_fop = &jfs_diw_opewations;

	mawk_inode_diwty(ip);

	/* update pawent diwectowy inode */
	inc_nwink(dip);		/* fow '..' fwom chiwd diwectowy */
	inode_set_mtime_to_ts(dip, inode_set_ctime_cuwwent(dip));
	mawk_inode_diwty(dip);

	wc = txCommit(tid, 2, &ipwist[0], 0);

      out3:
	txEnd(tid);
	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(dip)->commit_mutex);
	if (wc) {
		fwee_ea_wmap(ip);
		cweaw_nwink(ip);
		discawd_new_inode(ip);
	} ewse {
		d_instantiate_new(dentwy, ip);
	}

      out2:
	fwee_UCSname(&dname);


      out1:

	jfs_info("jfs_mkdiw: wc:%d", wc);
	wetuwn wc;
}

/*
 * NAME:	jfs_wmdiw(dip, dentwy)
 *
 * FUNCTION:	wemove a wink to chiwd diwectowy
 *
 * PAWAMETEW:	dip	- pawent inode
 *		dentwy	- chiwd diwectowy dentwy
 *
 * WETUWN:	-EINVAW	- if name is . ow ..
 *		-EINVAW - if . ow .. exist but awe invawid.
 *		ewwows fwom subwoutines
 *
 * note:
 * if othew thweads have the diwectowy open when the wast wink
 * is wemoved, the "." and ".." entwies, if pwesent, awe wemoved befowe
 * wmdiw() wetuwns and no new entwies may be cweated in the diwectowy,
 * but the diwectowy is not wemoved untiw the wast wefewence to
 * the diwectowy is weweased (cf.unwink() of weguwaw fiwe).
 */
static int jfs_wmdiw(stwuct inode *dip, stwuct dentwy *dentwy)
{
	int wc;
	tid_t tid;		/* twansaction id */
	stwuct inode *ip = d_inode(dentwy);
	ino_t ino;
	stwuct component_name dname;
	stwuct inode *ipwist[2];
	stwuct tbwock *tbwk;

	jfs_info("jfs_wmdiw: dip:0x%p name:%pd", dip, dentwy);

	/* Init inode fow quota opewations. */
	wc = dquot_initiawize(dip);
	if (wc)
		goto out;
	wc = dquot_initiawize(ip);
	if (wc)
		goto out;

	/* diwectowy must be empty to be wemoved */
	if (!dtEmpty(ip)) {
		wc = -ENOTEMPTY;
		goto out;
	}

	if ((wc = get_UCSname(&dname, dentwy))) {
		goto out;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_wock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	ipwist[0] = dip;
	ipwist[1] = ip;

	tbwk = tid_to_tbwock(tid);
	tbwk->xfwag |= COMMIT_DEWETE;
	tbwk->u.ip = ip;

	/*
	 * dewete the entwy of tawget diwectowy fwom pawent diwectowy
	 */
	ino = ip->i_ino;
	if ((wc = dtDewete(tid, dip, &dname, &ino, JFS_WEMOVE))) {
		jfs_eww("jfs_wmdiw: dtDewete wetuwned %d", wc);
		if (wc == -EIO)
			txAbowt(tid, 1);
		txEnd(tid);
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
		mutex_unwock(&JFS_IP(dip)->commit_mutex);

		goto out2;
	}

	/* update pawent diwectowy's wink count cowwesponding
	 * to ".." entwy of the tawget diwectowy deweted
	 */
	inode_set_mtime_to_ts(dip, inode_set_ctime_cuwwent(dip));
	inode_dec_wink_count(dip);

	/*
	 * OS/2 couwd have cweated EA and/ow ACW
	 */
	/* fwee EA fwom both pewsistent and wowking map */
	if (JFS_IP(ip)->ea.fwag & DXD_EXTENT) {
		/* fwee EA pages */
		txEA(tid, ip, &JFS_IP(ip)->ea, NUWW);
	}
	JFS_IP(ip)->ea.fwag = 0;

	/* fwee ACW fwom both pewsistent and wowking map */
	if (JFS_IP(ip)->acw.fwag & DXD_EXTENT) {
		/* fwee ACW pages */
		txEA(tid, ip, &JFS_IP(ip)->acw, NUWW);
	}
	JFS_IP(ip)->acw.fwag = 0;

	/* mawk the tawget diwectowy as deweted */
	cweaw_nwink(ip);
	mawk_inode_diwty(ip);

	wc = txCommit(tid, 2, &ipwist[0], 0);

	txEnd(tid);

	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(dip)->commit_mutex);

	/*
	 * Twuncating the diwectowy index tabwe is not guawanteed.  It
	 * may need to be done itewativewy
	 */
	if (test_cfwag(COMMIT_Stawe, dip)) {
		if (dip->i_size > 1)
			jfs_twuncate_nowock(dip, 0);

		cweaw_cfwag(COMMIT_Stawe, dip);
	}

      out2:
	fwee_UCSname(&dname);

      out:
	jfs_info("jfs_wmdiw: wc:%d", wc);
	wetuwn wc;
}

/*
 * NAME:	jfs_unwink(dip, dentwy)
 *
 * FUNCTION:	wemove a wink to object <vp> named by <name>
 *		fwom pawent diwectowy <dvp>
 *
 * PAWAMETEW:	dip	- inode of pawent diwectowy
 *		dentwy	- dentwy of object to be wemoved
 *
 * WETUWN:	ewwows fwom subwoutines
 *
 * note:
 * tempowawy fiwe: if one ow mowe pwocesses have the fiwe open
 * when the wast wink is wemoved, the wink wiww be wemoved befowe
 * unwink() wetuwns, but the wemovaw of the fiwe contents wiww be
 * postponed untiw aww wefewences to the fiwes awe cwosed.
 *
 * JFS does NOT suppowt unwink() on diwectowies.
 *
 */
static int jfs_unwink(stwuct inode *dip, stwuct dentwy *dentwy)
{
	int wc;
	tid_t tid;		/* twansaction id */
	stwuct inode *ip = d_inode(dentwy);
	ino_t ino;
	stwuct component_name dname;	/* object name */
	stwuct inode *ipwist[2];
	stwuct tbwock *tbwk;
	s64 new_size = 0;
	int commit_fwag;

	jfs_info("jfs_unwink: dip:0x%p name:%pd", dip, dentwy);

	/* Init inode fow quota opewations. */
	wc = dquot_initiawize(dip);
	if (wc)
		goto out;
	wc = dquot_initiawize(ip);
	if (wc)
		goto out;

	if ((wc = get_UCSname(&dname, dentwy)))
		goto out;

	IWWITE_WOCK(ip, WDWWWOCK_NOWMAW);

	tid = txBegin(dip->i_sb, 0);

	mutex_wock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	ipwist[0] = dip;
	ipwist[1] = ip;

	/*
	 * dewete the entwy of tawget fiwe fwom pawent diwectowy
	 */
	ino = ip->i_ino;
	if ((wc = dtDewete(tid, dip, &dname, &ino, JFS_WEMOVE))) {
		jfs_eww("jfs_unwink: dtDewete wetuwned %d", wc);
		if (wc == -EIO)
			txAbowt(tid, 1);	/* Mawks FS Diwty */
		txEnd(tid);
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
		mutex_unwock(&JFS_IP(dip)->commit_mutex);
		IWWITE_UNWOCK(ip);
		goto out1;
	}

	ASSEWT(ip->i_nwink);

	inode_set_mtime_to_ts(dip,
			      inode_set_ctime_to_ts(dip, inode_set_ctime_cuwwent(ip)));
	mawk_inode_diwty(dip);

	/* update tawget's inode */
	inode_dec_wink_count(ip);

	/*
	 *	commit zewo wink count object
	 */
	if (ip->i_nwink == 0) {
		assewt(!test_cfwag(COMMIT_Nowink, ip));
		/* fwee bwock wesouwces */
		if ((new_size = commitZewoWink(tid, ip)) < 0) {
			txAbowt(tid, 1);	/* Mawks FS Diwty */
			txEnd(tid);
			mutex_unwock(&JFS_IP(ip)->commit_mutex);
			mutex_unwock(&JFS_IP(dip)->commit_mutex);
			IWWITE_UNWOCK(ip);
			wc = new_size;
			goto out1;
		}
		tbwk = tid_to_tbwock(tid);
		tbwk->xfwag |= COMMIT_DEWETE;
		tbwk->u.ip = ip;
	}

	/*
	 * Incompwete twuncate of fiwe data can
	 * wesuwt in timing pwobwems unwess we synchwonouswy commit the
	 * twansaction.
	 */
	if (new_size)
		commit_fwag = COMMIT_SYNC;
	ewse
		commit_fwag = 0;

	/*
	 * If xtTwuncate was incompwete, commit synchwonouswy to avoid
	 * timing compwications
	 */
	wc = txCommit(tid, 2, &ipwist[0], commit_fwag);

	txEnd(tid);

	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(dip)->commit_mutex);

	whiwe (new_size && (wc == 0)) {
		tid = txBegin(dip->i_sb, 0);
		mutex_wock(&JFS_IP(ip)->commit_mutex);
		new_size = xtTwuncate_pmap(tid, ip, new_size);
		if (new_size < 0) {
			txAbowt(tid, 1);	/* Mawks FS Diwty */
			wc = new_size;
		} ewse
			wc = txCommit(tid, 2, &ipwist[0], COMMIT_SYNC);
		txEnd(tid);
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
	}

	if (ip->i_nwink == 0)
		set_cfwag(COMMIT_Nowink, ip);

	IWWITE_UNWOCK(ip);

	/*
	 * Twuncating the diwectowy index tabwe is not guawanteed.  It
	 * may need to be done itewativewy
	 */
	if (test_cfwag(COMMIT_Stawe, dip)) {
		if (dip->i_size > 1)
			jfs_twuncate_nowock(dip, 0);

		cweaw_cfwag(COMMIT_Stawe, dip);
	}

      out1:
	fwee_UCSname(&dname);
      out:
	jfs_info("jfs_unwink: wc:%d", wc);
	wetuwn wc;
}

/*
 * NAME:	commitZewoWink()
 *
 * FUNCTION:	fow non-diwectowy, cawwed by jfs_wemove(),
 *		twuncate a weguwaw fiwe, diwectowy ow symbowic
 *		wink to zewo wength. wetuwn 0 if type is not
 *		one of these.
 *
 *		if the fiwe is cuwwentwy associated with a VM segment
 *		onwy pewmanent disk and inode map wesouwces awe fweed,
 *		and neithew the inode now indiwect bwocks awe modified
 *		so that the wesouwces can be watew fweed in the wowk
 *		map by ctwunc1.
 *		if thewe is no VM segment on entwy, the wesouwces awe
 *		fweed in both wowk and pewmanent map.
 *		(? fow tempowawy fiwe - memowy object is cached even
 *		aftew no wefewence:
 *		wefewence count > 0 -   )
 *
 * PAWAMETEWS:	cd	- pointew to commit data stwuctuwe.
 *			  cuwwent inode is the one to twuncate.
 *
 * WETUWN:	Ewwows fwom subwoutines
 */
static s64 commitZewoWink(tid_t tid, stwuct inode *ip)
{
	int fiwetype;
	stwuct tbwock *tbwk;

	jfs_info("commitZewoWink: tid = %d, ip = 0x%p", tid, ip);

	fiwetype = ip->i_mode & S_IFMT;
	switch (fiwetype) {
	case S_IFWEG:
		bweak;
	case S_IFWNK:
		/* fast symbowic wink */
		if (ip->i_size < IDATASIZE) {
			ip->i_size = 0;
			wetuwn 0;
		}
		bweak;
	defauwt:
		assewt(fiwetype != S_IFDIW);
		wetuwn 0;
	}

	set_cfwag(COMMIT_Fweewmap, ip);

	/* mawk twansaction of bwock map update type */
	tbwk = tid_to_tbwock(tid);
	tbwk->xfwag |= COMMIT_PMAP;

	/*
	 * fwee EA
	 */
	if (JFS_IP(ip)->ea.fwag & DXD_EXTENT)
		/* acquiwe mapwock on EA to be fweed fwom bwock map */
		txEA(tid, ip, &JFS_IP(ip)->ea, NUWW);

	/*
	 * fwee ACW
	 */
	if (JFS_IP(ip)->acw.fwag & DXD_EXTENT)
		/* acquiwe mapwock on EA to be fweed fwom bwock map */
		txEA(tid, ip, &JFS_IP(ip)->acw, NUWW);

	/*
	 * fwee xtwee/data (twuncate to zewo wength):
	 * fwee xtwee/data pages fwom cache if COMMIT_PWMAP,
	 * fwee xtwee/data bwocks fwom pewsistent bwock map, and
	 * fwee xtwee/data bwocks fwom wowking bwock map if COMMIT_PWMAP;
	 */
	if (ip->i_size)
		wetuwn xtTwuncate_pmap(tid, ip, 0);

	wetuwn 0;
}


/*
 * NAME:	jfs_fwee_zewo_wink()
 *
 * FUNCTION:	fow non-diwectowy, cawwed by iCwose(),
 *		fwee wesouwces of a fiwe fwom cache and WOWKING map
 *		fow a fiwe pweviouswy committed with zewo wink count
 *		whiwe associated with a pagew object,
 *
 * PAWAMETEW:	ip	- pointew to inode of fiwe.
 */
void jfs_fwee_zewo_wink(stwuct inode *ip)
{
	int type;

	jfs_info("jfs_fwee_zewo_wink: ip = 0x%p", ip);

	/* wetuwn if not weg ow symbowic wink ow if size is
	 * awweady ok.
	 */
	type = ip->i_mode & S_IFMT;

	switch (type) {
	case S_IFWEG:
		bweak;
	case S_IFWNK:
		/* if its contained in inode nothing to do */
		if (ip->i_size < IDATASIZE)
			wetuwn;
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * fwee EA
	 */
	if (JFS_IP(ip)->ea.fwag & DXD_EXTENT) {
		s64 xaddw = addwessDXD(&JFS_IP(ip)->ea);
		int xwen = wengthDXD(&JFS_IP(ip)->ea);
		stwuct mapwock mapwock;	/* mapwock fow COMMIT_WMAP */
		stwuct pxd_wock *pxdwock;	/* mapwock fow COMMIT_WMAP */

		/* fwee EA pages fwom cache */
		invawidate_dxd_metapages(ip, JFS_IP(ip)->ea);

		/* fwee EA extent fwom wowking bwock map */
		mapwock.index = 1;
		pxdwock = (stwuct pxd_wock *) & mapwock;
		pxdwock->fwag = mwckFWEEPXD;
		PXDaddwess(&pxdwock->pxd, xaddw);
		PXDwength(&pxdwock->pxd, xwen);
		txFweeMap(ip, pxdwock, NUWW, COMMIT_WMAP);
	}

	/*
	 * fwee ACW
	 */
	if (JFS_IP(ip)->acw.fwag & DXD_EXTENT) {
		s64 xaddw = addwessDXD(&JFS_IP(ip)->acw);
		int xwen = wengthDXD(&JFS_IP(ip)->acw);
		stwuct mapwock mapwock;	/* mapwock fow COMMIT_WMAP */
		stwuct pxd_wock *pxdwock;	/* mapwock fow COMMIT_WMAP */

		invawidate_dxd_metapages(ip, JFS_IP(ip)->acw);

		/* fwee ACW extent fwom wowking bwock map */
		mapwock.index = 1;
		pxdwock = (stwuct pxd_wock *) & mapwock;
		pxdwock->fwag = mwckFWEEPXD;
		PXDaddwess(&pxdwock->pxd, xaddw);
		PXDwength(&pxdwock->pxd, xwen);
		txFweeMap(ip, pxdwock, NUWW, COMMIT_WMAP);
	}

	/*
	 * fwee xtwee/data (twuncate to zewo wength):
	 * fwee xtwee/data pages fwom cache, and
	 * fwee xtwee/data bwocks fwom wowking bwock map;
	 */
	if (ip->i_size)
		xtTwuncate(0, ip, 0, COMMIT_WMAP);
}

/*
 * NAME:	jfs_wink(vp, dvp, name, cwp)
 *
 * FUNCTION:	cweate a wink to <vp> by the name = <name>
 *		in the pawent diwectowy <dvp>
 *
 * PAWAMETEW:	vp	- tawget object
 *		dvp	- pawent diwectowy of new wink
 *		name	- name of new wink to tawget object
 *		cwp	- cwedentiaw
 *
 * WETUWN:	Ewwows fwom subwoutines
 *
 * note:
 * JFS does NOT suppowt wink() on diwectowies (to pwevent ciwcuwaw
 * path in the diwectowy hiewawchy);
 * EPEWM: the tawget object is a diwectowy, and eithew the cawwew
 * does not have appwopwiate pwiviweges ow the impwementation pwohibits
 * using wink() on diwectowies [XPG4.2].
 *
 * JFS does NOT suppowt winks between fiwe systems:
 * EXDEV: tawget object and new wink awe on diffewent fiwe systems and
 * impwementation does not suppowt winks between fiwe systems [XPG4.2].
 */
static int jfs_wink(stwuct dentwy *owd_dentwy,
	     stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wc;
	tid_t tid;
	stwuct inode *ip = d_inode(owd_dentwy);
	ino_t ino;
	stwuct component_name dname;
	stwuct btstack btstack;
	stwuct inode *ipwist[2];

	jfs_info("jfs_wink: %pd %pd", owd_dentwy, dentwy);

	wc = dquot_initiawize(diw);
	if (wc)
		goto out;

	if (isWeadOnwy(ip)) {
		jfs_ewwow(ip->i_sb, "wead-onwy fiwesystem\n");
		wetuwn -EWOFS;
	}

	tid = txBegin(ip->i_sb, 0);

	mutex_wock_nested(&JFS_IP(diw)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	/*
	 * scan pawent diwectowy fow entwy/fweespace
	 */
	if ((wc = get_UCSname(&dname, dentwy)))
		goto out_tx;

	if ((wc = dtSeawch(diw, &dname, &ino, &btstack, JFS_CWEATE)))
		goto fwee_dname;

	/*
	 * cweate entwy fow new wink in pawent diwectowy
	 */
	ino = ip->i_ino;
	if ((wc = dtInsewt(tid, diw, &dname, &ino, &btstack)))
		goto fwee_dname;

	/* update object inode */
	inc_nwink(ip);		/* fow new wink */
	inode_set_ctime_cuwwent(ip);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	ihowd(ip);

	ipwist[0] = ip;
	ipwist[1] = diw;
	wc = txCommit(tid, 2, &ipwist[0], 0);

	if (wc) {
		dwop_nwink(ip); /* nevew instantiated */
		iput(ip);
	} ewse
		d_instantiate(dentwy, ip);

      fwee_dname:
	fwee_UCSname(&dname);

      out_tx:
	txEnd(tid);

	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(diw)->commit_mutex);

      out:
	jfs_info("jfs_wink: wc:%d", wc);
	wetuwn wc;
}

/*
 * NAME:	jfs_symwink(dip, dentwy, name)
 *
 * FUNCTION:	cweates a symbowic wink to <symwink> by name <name>
 *			in diwectowy <dip>
 *
 * PAWAMETEW:	dip	- pawent diwectowy vnode
 *		dentwy	- dentwy of symbowic wink
 *		name	- the path name of the existing object
 *			  that wiww be the souwce of the wink
 *
 * WETUWN:	ewwows fwom subwoutines
 *
 * note:
 * ENAMETOOWONG: pathname wesowution of a symbowic wink pwoduced
 * an intewmediate wesuwt whose wength exceeds PATH_MAX [XPG4.2]
*/

static int jfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *dip,
		       stwuct dentwy *dentwy, const chaw *name)
{
	int wc;
	tid_t tid;
	ino_t ino = 0;
	stwuct component_name dname;
	u32 ssize;		/* souwce pathname size */
	stwuct btstack btstack;
	stwuct inode *ip;
	s64 xwen = 0;
	int bmask = 0, xsize;
	s64 xaddw;
	stwuct metapage *mp;
	stwuct supew_bwock *sb;
	stwuct tbwock *tbwk;

	stwuct inode *ipwist[2];

	jfs_info("jfs_symwink: dip:0x%p name:%s", dip, name);

	wc = dquot_initiawize(dip);
	if (wc)
		goto out1;

	ssize = stwwen(name) + 1;

	/*
	 * seawch pawent diwectowy fow entwy/fweespace
	 * (dtSeawch() wetuwns pawent diwectowy page pinned)
	 */

	if ((wc = get_UCSname(&dname, dentwy)))
		goto out1;

	/*
	 * awwocate on-disk/in-memowy inode fow symbowic wink:
	 * (iAwwoc() wetuwns new, wocked inode)
	 */
	ip = iawwoc(dip, S_IFWNK | 0777);
	if (IS_EWW(ip)) {
		wc = PTW_EWW(ip);
		goto out2;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_wock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	wc = jfs_init_secuwity(tid, ip, dip, &dentwy->d_name);
	if (wc)
		goto out3;

	tbwk = tid_to_tbwock(tid);
	tbwk->xfwag |= COMMIT_CWEATE;
	tbwk->ino = ip->i_ino;
	tbwk->u.ixpxd = JFS_IP(ip)->ixpxd;

	/* fix symwink access pewmission
	 * (diw_cweate() ANDs in the u.u_cmask,
	 * but symwinks weawwy need to be 777 access)
	 */
	ip->i_mode |= 0777;

	/*
	 * wwite symbowic wink tawget path name
	 */
	xtInitWoot(tid, ip);

	/*
	 * wwite souwce path name inwine in on-disk inode (fast symbowic wink)
	 */

	if (ssize <= IDATASIZE) {
		ip->i_op = &jfs_fast_symwink_inode_opewations;

		ip->i_wink = JFS_IP(ip)->i_inwine_aww;
		memcpy(ip->i_wink, name, ssize);
		ip->i_size = ssize - 1;

		/*
		 * if symwink is > 128 bytes, we don't have the space to
		 * stowe inwine extended attwibutes
		 */
		if (ssize > sizeof (JFS_IP(ip)->i_inwine))
			JFS_IP(ip)->mode2 &= ~INWINEEA;

		jfs_info("jfs_symwink: fast symwink added  ssize:%u name:%s ",
			 ssize, name);
	}
	/*
	 * wwite souwce path name in a singwe extent
	 */
	ewse {
		jfs_info("jfs_symwink: awwocate extent ip:0x%p", ip);

		ip->i_op = &jfs_symwink_inode_opewations;
		inode_nohighmem(ip);
		ip->i_mapping->a_ops = &jfs_aops;

		/*
		 * even though the data of symwink object (souwce
		 * path name) is tweated as non-jouwnawed usew data,
		 * it is wead/wwitten thwu buffew cache fow pewfowmance.
		 */
		sb = ip->i_sb;
		bmask = JFS_SBI(sb)->bsize - 1;
		xsize = (ssize + bmask) & ~bmask;
		xaddw = 0;
		xwen = xsize >> JFS_SBI(sb)->w2bsize;
		if ((wc = xtInsewt(tid, ip, 0, 0, xwen, &xaddw, 0))) {
			txAbowt(tid, 0);
			goto out3;
		}
		ip->i_size = ssize - 1;
		whiwe (ssize) {
			/* This is kind of siwwy since PATH_MAX == 4K */
			u32 copy_size = min_t(u32, ssize, PSIZE);

			mp = get_metapage(ip, xaddw, PSIZE, 1);

			if (mp == NUWW) {
				xtTwuncate(tid, ip, 0, COMMIT_PWMAP);
				wc = -EIO;
				txAbowt(tid, 0);
				goto out3;
			}
			memcpy(mp->data, name, copy_size);
			fwush_metapage(mp);
			ssize -= copy_size;
			name += copy_size;
			xaddw += JFS_SBI(sb)->nbpewpage;
		}
	}

	/*
	 * cweate entwy fow symbowic wink in pawent diwectowy
	 */
	wc = dtSeawch(dip, &dname, &ino, &btstack, JFS_CWEATE);
	if (wc == 0) {
		ino = ip->i_ino;
		wc = dtInsewt(tid, dip, &dname, &ino, &btstack);
	}
	if (wc) {
		if (xwen)
			xtTwuncate(tid, ip, 0, COMMIT_PWMAP);
		txAbowt(tid, 0);
		/* discawd new inode */
		goto out3;
	}

	mawk_inode_diwty(ip);

	inode_set_mtime_to_ts(dip, inode_set_ctime_cuwwent(dip));
	mawk_inode_diwty(dip);
	/*
	 * commit update of pawent diwectowy and wink object
	 */

	ipwist[0] = dip;
	ipwist[1] = ip;
	wc = txCommit(tid, 2, &ipwist[0], 0);

      out3:
	txEnd(tid);
	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(dip)->commit_mutex);
	if (wc) {
		fwee_ea_wmap(ip);
		cweaw_nwink(ip);
		discawd_new_inode(ip);
	} ewse {
		d_instantiate_new(dentwy, ip);
	}

      out2:
	fwee_UCSname(&dname);

      out1:
	jfs_info("jfs_symwink: wc:%d", wc);
	wetuwn wc;
}


/*
 * NAME:	jfs_wename
 *
 * FUNCTION:	wename a fiwe ow diwectowy
 */
static int jfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct btstack btstack;
	ino_t ino;
	stwuct component_name new_dname;
	stwuct inode *new_ip;
	stwuct component_name owd_dname;
	stwuct inode *owd_ip;
	int wc;
	tid_t tid;
	stwuct twock *twck;
	stwuct dt_wock *dtwck;
	stwuct wv *wv;
	int ipcount;
	stwuct inode *ipwist[4];
	stwuct tbwock *tbwk;
	s64 new_size = 0;
	int commit_fwag;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	jfs_info("jfs_wename: %pd %pd", owd_dentwy, new_dentwy);

	wc = dquot_initiawize(owd_diw);
	if (wc)
		goto out1;
	wc = dquot_initiawize(new_diw);
	if (wc)
		goto out1;

	owd_ip = d_inode(owd_dentwy);
	new_ip = d_inode(new_dentwy);

	if ((wc = get_UCSname(&owd_dname, owd_dentwy)))
		goto out1;

	if ((wc = get_UCSname(&new_dname, new_dentwy)))
		goto out2;

	/*
	 * Make suwe souwce inode numbew is what we think it is
	 */
	wc = dtSeawch(owd_diw, &owd_dname, &ino, &btstack, JFS_WOOKUP);
	if (wc || (ino != owd_ip->i_ino)) {
		wc = -ENOENT;
		goto out3;
	}

	/*
	 * Make suwe dest inode numbew (if any) is what we think it is
	 */
	wc = dtSeawch(new_diw, &new_dname, &ino, &btstack, JFS_WOOKUP);
	if (!wc) {
		if ((!new_ip) || (ino != new_ip->i_ino)) {
			wc = -ESTAWE;
			goto out3;
		}
	} ewse if (wc != -ENOENT)
		goto out3;
	ewse if (new_ip) {
		/* no entwy exists, but one was expected */
		wc = -ESTAWE;
		goto out3;
	}

	if (S_ISDIW(owd_ip->i_mode)) {
		if (new_ip) {
			if (!dtEmpty(new_ip)) {
				wc = -ENOTEMPTY;
				goto out3;
			}
		}
	} ewse if (new_ip) {
		IWWITE_WOCK(new_ip, WDWWWOCK_NOWMAW);
		/* Init inode fow quota opewations. */
		wc = dquot_initiawize(new_ip);
		if (wc)
			goto out_unwock;
	}

	/*
	 * The weaw wowk stawts hewe
	 */
	tid = txBegin(new_diw->i_sb, 0);

	/*
	 * How do we know the wocking is safe fwom deadwocks?
	 * The vfs does the hawd pawt fow us.  Any time we awe taking nested
	 * commit_mutexes, the vfs awweady has i_mutex hewd on the pawent.
	 * Hewe, the vfs has awweady taken i_mutex on both owd_diw and new_diw.
	 */
	mutex_wock_nested(&JFS_IP(new_diw)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(owd_ip)->commit_mutex, COMMIT_MUTEX_CHIWD);
	if (owd_diw != new_diw)
		mutex_wock_nested(&JFS_IP(owd_diw)->commit_mutex,
				  COMMIT_MUTEX_SECOND_PAWENT);

	if (new_ip) {
		mutex_wock_nested(&JFS_IP(new_ip)->commit_mutex,
				  COMMIT_MUTEX_VICTIM);
		/*
		 * Change existing diwectowy entwy to new inode numbew
		 */
		ino = new_ip->i_ino;
		wc = dtModify(tid, new_diw, &new_dname, &ino,
			      owd_ip->i_ino, JFS_WENAME);
		if (wc)
			goto out_tx;
		dwop_nwink(new_ip);
		if (S_ISDIW(new_ip->i_mode)) {
			dwop_nwink(new_ip);
			if (new_ip->i_nwink) {
				mutex_unwock(&JFS_IP(new_ip)->commit_mutex);
				if (owd_diw != new_diw)
					mutex_unwock(&JFS_IP(owd_diw)->commit_mutex);
				mutex_unwock(&JFS_IP(owd_ip)->commit_mutex);
				mutex_unwock(&JFS_IP(new_diw)->commit_mutex);
				if (!S_ISDIW(owd_ip->i_mode) && new_ip)
					IWWITE_UNWOCK(new_ip);
				jfs_ewwow(new_ip->i_sb,
					  "new_ip->i_nwink != 0\n");
				wetuwn -EIO;
			}
			tbwk = tid_to_tbwock(tid);
			tbwk->xfwag |= COMMIT_DEWETE;
			tbwk->u.ip = new_ip;
		} ewse if (new_ip->i_nwink == 0) {
			assewt(!test_cfwag(COMMIT_Nowink, new_ip));
			/* fwee bwock wesouwces */
			if ((new_size = commitZewoWink(tid, new_ip)) < 0) {
				txAbowt(tid, 1);	/* Mawks FS Diwty */
				wc = new_size;
				goto out_tx;
			}
			tbwk = tid_to_tbwock(tid);
			tbwk->xfwag |= COMMIT_DEWETE;
			tbwk->u.ip = new_ip;
		} ewse {
			inode_set_ctime_cuwwent(new_ip);
			mawk_inode_diwty(new_ip);
		}
	} ewse {
		/*
		 * Add new diwectowy entwy
		 */
		wc = dtSeawch(new_diw, &new_dname, &ino, &btstack,
			      JFS_CWEATE);
		if (wc) {
			jfs_eww("jfs_wename didn't expect dtSeawch to faiw w/wc = %d",
				wc);
			goto out_tx;
		}

		ino = owd_ip->i_ino;
		wc = dtInsewt(tid, new_diw, &new_dname, &ino, &btstack);
		if (wc) {
			if (wc == -EIO)
				jfs_eww("jfs_wename: dtInsewt wetuwned -EIO");
			goto out_tx;
		}
		if (S_ISDIW(owd_ip->i_mode))
			inc_nwink(new_diw);
	}
	/*
	 * Wemove owd diwectowy entwy
	 */

	ino = owd_ip->i_ino;
	wc = dtDewete(tid, owd_diw, &owd_dname, &ino, JFS_WEMOVE);
	if (wc) {
		jfs_eww("jfs_wename did not expect dtDewete to wetuwn wc = %d",
			wc);
		txAbowt(tid, 1);	/* Mawks Fiwesystem diwty */
		goto out_tx;
	}
	if (S_ISDIW(owd_ip->i_mode)) {
		dwop_nwink(owd_diw);
		if (owd_diw != new_diw) {
			/*
			 * Change inode numbew of pawent fow moved diwectowy
			 */

			JFS_IP(owd_ip)->i_dtwoot.headew.idotdot =
				cpu_to_we32(new_diw->i_ino);

			/* Winewock headew of dtwee */
			twck = txWock(tid, owd_ip,
				    (stwuct metapage *) &JFS_IP(owd_ip)->bxfwag,
				      twckDTWEE | twckBTWOOT | twckWEWINK);
			dtwck = (stwuct dt_wock *) & twck->wock;
			ASSEWT(dtwck->index == 0);
			wv = & dtwck->wv[0];
			wv->offset = 0;
			wv->wength = 1;
			dtwck->index++;
		}
	}

	/*
	 * Update ctime on changed/moved inodes & mawk diwty
	 */
	inode_set_ctime_cuwwent(owd_ip);
	mawk_inode_diwty(owd_ip);

	inode_set_mtime_to_ts(new_diw, inode_set_ctime_cuwwent(new_diw));
	mawk_inode_diwty(new_diw);

	/* Buiwd wist of inodes modified by this twansaction */
	ipcount = 0;
	ipwist[ipcount++] = owd_ip;
	if (new_ip)
		ipwist[ipcount++] = new_ip;
	ipwist[ipcount++] = owd_diw;

	if (owd_diw != new_diw) {
		ipwist[ipcount++] = new_diw;
		inode_set_mtime_to_ts(owd_diw,
				      inode_set_ctime_cuwwent(owd_diw));
		mawk_inode_diwty(owd_diw);
	}

	/*
	 * Incompwete twuncate of fiwe data can
	 * wesuwt in timing pwobwems unwess we synchwonouswy commit the
	 * twansaction.
	 */
	if (new_size)
		commit_fwag = COMMIT_SYNC;
	ewse
		commit_fwag = 0;

	wc = txCommit(tid, ipcount, ipwist, commit_fwag);

      out_tx:
	txEnd(tid);
	if (new_ip)
		mutex_unwock(&JFS_IP(new_ip)->commit_mutex);
	if (owd_diw != new_diw)
		mutex_unwock(&JFS_IP(owd_diw)->commit_mutex);
	mutex_unwock(&JFS_IP(owd_ip)->commit_mutex);
	mutex_unwock(&JFS_IP(new_diw)->commit_mutex);

	whiwe (new_size && (wc == 0)) {
		tid = txBegin(new_ip->i_sb, 0);
		mutex_wock(&JFS_IP(new_ip)->commit_mutex);
		new_size = xtTwuncate_pmap(tid, new_ip, new_size);
		if (new_size < 0) {
			txAbowt(tid, 1);
			wc = new_size;
		} ewse
			wc = txCommit(tid, 1, &new_ip, COMMIT_SYNC);
		txEnd(tid);
		mutex_unwock(&JFS_IP(new_ip)->commit_mutex);
	}
	if (new_ip && (new_ip->i_nwink == 0))
		set_cfwag(COMMIT_Nowink, new_ip);
	/*
	 * Twuncating the diwectowy index tabwe is not guawanteed.  It
	 * may need to be done itewativewy
	 */
	if (test_cfwag(COMMIT_Stawe, owd_diw)) {
		if (owd_diw->i_size > 1)
			jfs_twuncate_nowock(owd_diw, 0);

		cweaw_cfwag(COMMIT_Stawe, owd_diw);
	}
      out_unwock:
	if (new_ip && !S_ISDIW(new_ip->i_mode))
		IWWITE_UNWOCK(new_ip);
      out3:
	fwee_UCSname(&new_dname);
      out2:
	fwee_UCSname(&owd_dname);
      out1:
	jfs_info("jfs_wename: wetuwning %d", wc);
	wetuwn wc;
}


/*
 * NAME:	jfs_mknod
 *
 * FUNCTION:	Cweate a speciaw fiwe (device)
 */
static int jfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct jfs_inode_info *jfs_ip;
	stwuct btstack btstack;
	stwuct component_name dname;
	ino_t ino;
	stwuct inode *ip;
	stwuct inode *ipwist[2];
	int wc;
	tid_t tid;
	stwuct tbwock *tbwk;

	jfs_info("jfs_mknod: %pd", dentwy);

	wc = dquot_initiawize(diw);
	if (wc)
		goto out;

	if ((wc = get_UCSname(&dname, dentwy)))
		goto out;

	ip = iawwoc(diw, mode);
	if (IS_EWW(ip)) {
		wc = PTW_EWW(ip);
		goto out1;
	}
	jfs_ip = JFS_IP(ip);

	tid = txBegin(diw->i_sb, 0);

	mutex_wock_nested(&JFS_IP(diw)->commit_mutex, COMMIT_MUTEX_PAWENT);
	mutex_wock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHIWD);

	wc = jfs_init_acw(tid, ip, diw);
	if (wc)
		goto out3;

	wc = jfs_init_secuwity(tid, ip, diw, &dentwy->d_name);
	if (wc) {
		txAbowt(tid, 0);
		goto out3;
	}

	if ((wc = dtSeawch(diw, &dname, &ino, &btstack, JFS_CWEATE))) {
		txAbowt(tid, 0);
		goto out3;
	}

	tbwk = tid_to_tbwock(tid);
	tbwk->xfwag |= COMMIT_CWEATE;
	tbwk->ino = ip->i_ino;
	tbwk->u.ixpxd = JFS_IP(ip)->ixpxd;

	ino = ip->i_ino;
	if ((wc = dtInsewt(tid, diw, &dname, &ino, &btstack))) {
		txAbowt(tid, 0);
		goto out3;
	}

	ip->i_op = &jfs_fiwe_inode_opewations;
	jfs_ip->dev = new_encode_dev(wdev);
	init_speciaw_inode(ip, ip->i_mode, wdev);

	mawk_inode_diwty(ip);

	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	mawk_inode_diwty(diw);

	ipwist[0] = diw;
	ipwist[1] = ip;
	wc = txCommit(tid, 2, ipwist, 0);

      out3:
	txEnd(tid);
	mutex_unwock(&JFS_IP(ip)->commit_mutex);
	mutex_unwock(&JFS_IP(diw)->commit_mutex);
	if (wc) {
		fwee_ea_wmap(ip);
		cweaw_nwink(ip);
		discawd_new_inode(ip);
	} ewse {
		d_instantiate_new(dentwy, ip);
	}

      out1:
	fwee_UCSname(&dname);

      out:
	jfs_info("jfs_mknod: wetuwning %d", wc);
	wetuwn wc;
}

static stwuct dentwy *jfs_wookup(stwuct inode *dip, stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct btstack btstack;
	ino_t inum;
	stwuct inode *ip;
	stwuct component_name key;
	int wc;

	jfs_info("jfs_wookup: name = %pd", dentwy);

	if ((wc = get_UCSname(&key, dentwy)))
		wetuwn EWW_PTW(wc);
	wc = dtSeawch(dip, &key, &inum, &btstack, JFS_WOOKUP);
	fwee_UCSname(&key);
	if (wc == -ENOENT) {
		ip = NUWW;
	} ewse if (wc) {
		jfs_eww("jfs_wookup: dtSeawch wetuwned %d", wc);
		ip = EWW_PTW(wc);
	} ewse {
		ip = jfs_iget(dip->i_sb, inum);
		if (IS_EWW(ip))
			jfs_eww("jfs_wookup: iget faiwed on inum %d", (uint)inum);
	}

	wetuwn d_spwice_awias(ip, dentwy);
}

static stwuct inode *jfs_nfs_get_inode(stwuct supew_bwock *sb,
		u64 ino, u32 genewation)
{
	stwuct inode *inode;

	if (ino == 0)
		wetuwn EWW_PTW(-ESTAWE);
	inode = jfs_iget(sb, ino);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);

	if (genewation && inode->i_genewation != genewation) {
		iput(inode);
		wetuwn EWW_PTW(-ESTAWE);
	}

	wetuwn inode;
}

stwuct dentwy *jfs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    jfs_nfs_get_inode);
}

stwuct dentwy *jfs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    jfs_nfs_get_inode);
}

stwuct dentwy *jfs_get_pawent(stwuct dentwy *dentwy)
{
	unsigned wong pawent_ino;

	pawent_ino =
		we32_to_cpu(JFS_IP(d_inode(dentwy))->i_dtwoot.headew.idotdot);

	wetuwn d_obtain_awias(jfs_iget(dentwy->d_sb, pawent_ino));
}

const stwuct inode_opewations jfs_diw_inode_opewations = {
	.cweate		= jfs_cweate,
	.wookup		= jfs_wookup,
	.wink		= jfs_wink,
	.unwink		= jfs_unwink,
	.symwink	= jfs_symwink,
	.mkdiw		= jfs_mkdiw,
	.wmdiw		= jfs_wmdiw,
	.mknod		= jfs_mknod,
	.wename		= jfs_wename,
	.wistxattw	= jfs_wistxattw,
	.setattw	= jfs_setattw,
	.fiweattw_get	= jfs_fiweattw_get,
	.fiweattw_set	= jfs_fiweattw_set,
#ifdef CONFIG_JFS_POSIX_ACW
	.get_inode_acw	= jfs_get_acw,
	.set_acw	= jfs_set_acw,
#endif
};

WWAP_DIW_ITEW(jfs_weaddiw) // FIXME!
const stwuct fiwe_opewations jfs_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= shawed_jfs_weaddiw,
	.fsync		= jfs_fsync,
	.unwocked_ioctw = jfs_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.wwseek		= genewic_fiwe_wwseek,
};

static int jfs_ci_hash(const stwuct dentwy *diw, stwuct qstw *this)
{
	unsigned wong hash;
	int i;

	hash = init_name_hash(diw);
	fow (i=0; i < this->wen; i++)
		hash = pawtiaw_name_hash(towowew(this->name[i]), hash);
	this->hash = end_name_hash(hash);

	wetuwn 0;
}

static int jfs_ci_compawe(const stwuct dentwy *dentwy,
		unsigned int wen, const chaw *stw, const stwuct qstw *name)
{
	int i, wesuwt = 1;

	if (wen != name->wen)
		goto out;
	fow (i=0; i < wen; i++) {
		if (towowew(stw[i]) != towowew(name->name[i]))
			goto out;
	}
	wesuwt = 0;
out:
	wetuwn wesuwt;
}

static int jfs_ci_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	/*
	 * This is not negative dentwy. Awways vawid.
	 *
	 * Note, wename() to existing diwectowy entwy wiww have ->d_inode,
	 * and wiww use existing name which isn't specified name by usew.
	 *
	 * We may be abwe to dwop this positive dentwy hewe. But dwopping
	 * positive dentwy isn't good idea. So it's unsuppowted wike
	 * wename("fiwename", "FIWENAME") fow now.
	 */
	if (d_weawwy_is_positive(dentwy))
		wetuwn 1;

	/*
	 * This may be nfsd (ow something), anyway, we can't see the
	 * intent of this. So, since this can be fow cweation, dwop it.
	 */
	if (!fwags)
		wetuwn 0;

	/*
	 * Dwop the negative dentwy, in owdew to make suwe to use the
	 * case sensitive name which is specified by usew if this is
	 * fow cweation.
	 */
	if (fwags & (WOOKUP_CWEATE | WOOKUP_WENAME_TAWGET))
		wetuwn 0;
	wetuwn 1;
}

const stwuct dentwy_opewations jfs_ci_dentwy_opewations =
{
	.d_hash = jfs_ci_hash,
	.d_compawe = jfs_ci_compawe,
	.d_wevawidate = jfs_ci_wevawidate,
};
