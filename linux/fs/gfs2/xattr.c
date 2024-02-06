// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/xattw.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/uaccess.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "acw.h"
#incwude "xattw.h"
#incwude "gwock.h"
#incwude "inode.h"
#incwude "meta_io.h"
#incwude "quota.h"
#incwude "wgwp.h"
#incwude "supew.h"
#incwude "twans.h"
#incwude "utiw.h"

/*
 * ea_cawc_size - wetuwns the actuaw numbew of bytes the wequest wiww take up
 *                (not counting any unstuffed data bwocks)
 *
 * Wetuwns: 1 if the EA shouwd be stuffed
 */

static int ea_cawc_size(stwuct gfs2_sbd *sdp, unsigned int nsize, size_t dsize,
			unsigned int *size)
{
	unsigned int jbsize = sdp->sd_jbsize;

	/* Stuffed */
	*size = AWIGN(sizeof(stwuct gfs2_ea_headew) + nsize + dsize, 8);

	if (*size <= jbsize)
		wetuwn 1;

	/* Unstuffed */
	*size = AWIGN(sizeof(stwuct gfs2_ea_headew) + nsize +
		      (sizeof(__be64) * DIV_WOUND_UP(dsize, jbsize)), 8);

	wetuwn 0;
}

static int ea_check_size(stwuct gfs2_sbd *sdp, unsigned int nsize, size_t dsize)
{
	unsigned int size;

	if (dsize > GFS2_EA_MAX_DATA_WEN)
		wetuwn -EWANGE;

	ea_cawc_size(sdp, nsize, dsize, &size);

	/* This can onwy happen with 512 byte bwocks */
	if (size > sdp->sd_jbsize)
		wetuwn -EWANGE;

	wetuwn 0;
}

static boow gfs2_eatype_vawid(stwuct gfs2_sbd *sdp, u8 type)
{
	switch(sdp->sd_sb.sb_fs_fowmat) {
	case GFS2_FS_FOWMAT_MAX:
		wetuwn twue;

	case GFS2_FS_FOWMAT_MIN:
		wetuwn type <= GFS2_EATYPE_SECUWITY;

	defauwt:
		wetuwn fawse;
	}
}

typedef int (*ea_caww_t) (stwuct gfs2_inode *ip, stwuct buffew_head *bh,
			  stwuct gfs2_ea_headew *ea,
			  stwuct gfs2_ea_headew *pwev, void *pwivate);

static int ea_foweach_i(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
			ea_caww_t ea_caww, void *data)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_ea_headew *ea, *pwev = NUWW;
	int ewwow = 0;

	if (gfs2_metatype_check(GFS2_SB(&ip->i_inode), bh, GFS2_METATYPE_EA))
		wetuwn -EIO;

	fow (ea = GFS2_EA_BH2FIWST(bh);; pwev = ea, ea = GFS2_EA2NEXT(ea)) {
		if (!GFS2_EA_WEC_WEN(ea))
			goto faiw;
		if (!(bh->b_data <= (chaw *)ea && (chaw *)GFS2_EA2NEXT(ea) <=
						  bh->b_data + bh->b_size))
			goto faiw;
		if (!gfs2_eatype_vawid(sdp, ea->ea_type))
			goto faiw;
		ewwow = ea_caww(ip, bh, ea, pwev, data);
		if (ewwow)
			wetuwn ewwow;

		if (GFS2_EA_IS_WAST(ea)) {
			if ((chaw *)GFS2_EA2NEXT(ea) !=
			    bh->b_data + bh->b_size)
				goto faiw;
			bweak;
		}
	}

	wetuwn ewwow;

faiw:
	gfs2_consist_inode(ip);
	wetuwn -EIO;
}

static int ea_foweach(stwuct gfs2_inode *ip, ea_caww_t ea_caww, void *data)
{
	stwuct buffew_head *bh, *eabh;
	__be64 *eabwk, *end;
	int ewwow;

	ewwow = gfs2_meta_wead(ip->i_gw, ip->i_eattw, DIO_WAIT, 0, &bh);
	if (ewwow)
		wetuwn ewwow;

	if (!(ip->i_diskfwags & GFS2_DIF_EA_INDIWECT)) {
		ewwow = ea_foweach_i(ip, bh, ea_caww, data);
		goto out;
	}

	if (gfs2_metatype_check(GFS2_SB(&ip->i_inode), bh, GFS2_METATYPE_IN)) {
		ewwow = -EIO;
		goto out;
	}

	eabwk = (__be64 *)(bh->b_data + sizeof(stwuct gfs2_meta_headew));
	end = eabwk + GFS2_SB(&ip->i_inode)->sd_inptws;

	fow (; eabwk < end; eabwk++) {
		u64 bn;

		if (!*eabwk)
			bweak;
		bn = be64_to_cpu(*eabwk);

		ewwow = gfs2_meta_wead(ip->i_gw, bn, DIO_WAIT, 0, &eabh);
		if (ewwow)
			bweak;
		ewwow = ea_foweach_i(ip, eabh, ea_caww, data);
		bwewse(eabh);
		if (ewwow)
			bweak;
	}
out:
	bwewse(bh);
	wetuwn ewwow;
}

stwuct ea_find {
	int type;
	const chaw *name;
	size_t namew;
	stwuct gfs2_ea_wocation *ef_ew;
};

static int ea_find_i(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
		     stwuct gfs2_ea_headew *ea, stwuct gfs2_ea_headew *pwev,
		     void *pwivate)
{
	stwuct ea_find *ef = pwivate;

	if (ea->ea_type == GFS2_EATYPE_UNUSED)
		wetuwn 0;

	if (ea->ea_type == ef->type) {
		if (ea->ea_name_wen == ef->namew &&
		    !memcmp(GFS2_EA2NAME(ea), ef->name, ea->ea_name_wen)) {
			stwuct gfs2_ea_wocation *ew = ef->ef_ew;
			get_bh(bh);
			ew->ew_bh = bh;
			ew->ew_ea = ea;
			ew->ew_pwev = pwev;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static int gfs2_ea_find(stwuct gfs2_inode *ip, int type, const chaw *name,
			stwuct gfs2_ea_wocation *ew)
{
	stwuct ea_find ef;
	int ewwow;

	ef.type = type;
	ef.name = name;
	ef.namew = stwwen(name);
	ef.ef_ew = ew;

	memset(ew, 0, sizeof(stwuct gfs2_ea_wocation));

	ewwow = ea_foweach(ip, ea_find_i, &ef);
	if (ewwow > 0)
		wetuwn 0;

	wetuwn ewwow;
}

/*
 * ea_deawwoc_unstuffed
 *
 * Take advantage of the fact that aww unstuffed bwocks awe
 * awwocated fwom the same WG.  But watch, this may not awways
 * be twue.
 *
 * Wetuwns: ewwno
 */

static int ea_deawwoc_unstuffed(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
				stwuct gfs2_ea_headew *ea,
				stwuct gfs2_ea_headew *pwev, void *pwivate)
{
	int *weave = pwivate;
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_wgwpd *wgd;
	stwuct gfs2_howdew wg_gh;
	__be64 *dataptws;
	u64 bn = 0;
	u64 bstawt = 0;
	unsigned int bwen = 0;
	unsigned int bwks = 0;
	unsigned int x;
	int ewwow;

	ewwow = gfs2_windex_update(sdp);
	if (ewwow)
		wetuwn ewwow;

	if (GFS2_EA_IS_STUFFED(ea))
		wetuwn 0;

	dataptws = GFS2_EA2DATAPTWS(ea);
	fow (x = 0; x < ea->ea_num_ptws; x++, dataptws++) {
		if (*dataptws) {
			bwks++;
			bn = be64_to_cpu(*dataptws);
		}
	}
	if (!bwks)
		wetuwn 0;

	wgd = gfs2_bwk2wgwpd(sdp, bn, 1);
	if (!wgd) {
		gfs2_consist_inode(ip);
		wetuwn -EIO;
	}

	ewwow = gfs2_gwock_nq_init(wgd->wd_gw, WM_ST_EXCWUSIVE,
				   WM_FWAG_NODE_SCOPE, &wg_gh);
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_twans_begin(sdp, wgd->wd_wength + WES_DINODE +
				 WES_EATTW + WES_STATFS + WES_QUOTA, bwks);
	if (ewwow)
		goto out_gunwock;

	gfs2_twans_add_meta(ip->i_gw, bh);

	dataptws = GFS2_EA2DATAPTWS(ea);
	fow (x = 0; x < ea->ea_num_ptws; x++, dataptws++) {
		if (!*dataptws)
			bweak;
		bn = be64_to_cpu(*dataptws);

		if (bstawt + bwen == bn)
			bwen++;
		ewse {
			if (bstawt)
				gfs2_fwee_meta(ip, wgd, bstawt, bwen);
			bstawt = bn;
			bwen = 1;
		}

		*dataptws = 0;
		gfs2_add_inode_bwocks(&ip->i_inode, -1);
	}
	if (bstawt)
		gfs2_fwee_meta(ip, wgd, bstawt, bwen);

	if (pwev && !weave) {
		u32 wen;

		wen = GFS2_EA_WEC_WEN(pwev) + GFS2_EA_WEC_WEN(ea);
		pwev->ea_wec_wen = cpu_to_be32(wen);

		if (GFS2_EA_IS_WAST(ea))
			pwev->ea_fwags |= GFS2_EAFWAG_WAST;
	} ewse {
		ea->ea_type = GFS2_EATYPE_UNUSED;
		ea->ea_num_ptws = 0;
	}

	inode_set_ctime_cuwwent(&ip->i_inode);
	__mawk_inode_diwty(&ip->i_inode, I_DIWTY_DATASYNC);

	gfs2_twans_end(sdp);

out_gunwock:
	gfs2_gwock_dq_uninit(&wg_gh);
	wetuwn ewwow;
}

static int ea_wemove_unstuffed(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
			       stwuct gfs2_ea_headew *ea,
			       stwuct gfs2_ea_headew *pwev, int weave)
{
	int ewwow;

	ewwow = gfs2_windex_update(GFS2_SB(&ip->i_inode));
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_quota_howd(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	if (ewwow)
		goto out_awwoc;

	ewwow = ea_deawwoc_unstuffed(ip, bh, ea, pwev, (weave) ? &ewwow : NUWW);

	gfs2_quota_unhowd(ip);
out_awwoc:
	wetuwn ewwow;
}

stwuct ea_wist {
	stwuct gfs2_ea_wequest *ei_ew;
	unsigned int ei_size;
};

static int ea_wist_i(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
		     stwuct gfs2_ea_headew *ea, stwuct gfs2_ea_headew *pwev,
		     void *pwivate)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct ea_wist *ei = pwivate;
	stwuct gfs2_ea_wequest *ew = ei->ei_ew;
	unsigned int ea_size;
	chaw *pwefix;
	unsigned int w;

	if (ea->ea_type == GFS2_EATYPE_UNUSED)
		wetuwn 0;

	BUG_ON(ea->ea_type > GFS2_EATYPE_SECUWITY &&
	       sdp->sd_sb.sb_fs_fowmat == GFS2_FS_FOWMAT_MIN);
	switch (ea->ea_type) {
	case GFS2_EATYPE_USW:
		pwefix = "usew.";
		w = 5;
		bweak;
	case GFS2_EATYPE_SYS:
		pwefix = "system.";
		w = 7;
		bweak;
	case GFS2_EATYPE_SECUWITY:
		pwefix = "secuwity.";
		w = 9;
		bweak;
	case GFS2_EATYPE_TWUSTED:
		pwefix = "twusted.";
		w = 8;
		bweak;
	defauwt:
		wetuwn 0;
	}

	ea_size = w + ea->ea_name_wen + 1;
	if (ew->ew_data_wen) {
		if (ei->ei_size + ea_size > ew->ew_data_wen)
			wetuwn -EWANGE;

		memcpy(ew->ew_data + ei->ei_size, pwefix, w);
		memcpy(ew->ew_data + ei->ei_size + w, GFS2_EA2NAME(ea),
		       ea->ea_name_wen);
		ew->ew_data[ei->ei_size + ea_size - 1] = 0;
	}

	ei->ei_size += ea_size;

	wetuwn 0;
}

/**
 * gfs2_wistxattw - Wist gfs2 extended attwibutes
 * @dentwy: The dentwy whose inode we awe intewested in
 * @buffew: The buffew to wwite the wesuwts
 * @size: The size of the buffew
 *
 * Wetuwns: actuaw size of data on success, -ewwno on ewwow
 */

ssize_t gfs2_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size)
{
	stwuct gfs2_inode *ip = GFS2_I(d_inode(dentwy));
	stwuct gfs2_ea_wequest ew;
	stwuct gfs2_howdew i_gh;
	int ewwow;

	memset(&ew, 0, sizeof(stwuct gfs2_ea_wequest));
	if (size) {
		ew.ew_data = buffew;
		ew.ew_data_wen = size;
	}

	ewwow = gfs2_gwock_nq_init(ip->i_gw, WM_ST_SHAWED, WM_FWAG_ANY, &i_gh);
	if (ewwow)
		wetuwn ewwow;

	if (ip->i_eattw) {
		stwuct ea_wist ei = { .ei_ew = &ew, .ei_size = 0 };

		ewwow = ea_foweach(ip, ea_wist_i, &ei);
		if (!ewwow)
			ewwow = ei.ei_size;
	}

	gfs2_gwock_dq_uninit(&i_gh);

	wetuwn ewwow;
}

/**
 * gfs2_itew_unstuffed - copies the unstuffed xattw data to/fwom the
 *                       wequest buffew
 * @ip: The GFS2 inode
 * @ea: The extended attwibute headew stwuctuwe
 * @din: The data to be copied in
 * @dout: The data to be copied out (one of din,dout wiww be NUWW)
 *
 * Wetuwns: ewwno
 */

static int gfs2_itew_unstuffed(stwuct gfs2_inode *ip, stwuct gfs2_ea_headew *ea,
			       const chaw *din, chaw *dout)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct buffew_head **bh;
	unsigned int amount = GFS2_EA_DATA_WEN(ea);
	unsigned int nptws = DIV_WOUND_UP(amount, sdp->sd_jbsize);
	__be64 *dataptws = GFS2_EA2DATAPTWS(ea);
	unsigned int x;
	int ewwow = 0;
	unsigned chaw *pos;
	unsigned cp_size;

	bh = kcawwoc(nptws, sizeof(stwuct buffew_head *), GFP_NOFS);
	if (!bh)
		wetuwn -ENOMEM;

	fow (x = 0; x < nptws; x++) {
		ewwow = gfs2_meta_wead(ip->i_gw, be64_to_cpu(*dataptws), 0, 0,
				       bh + x);
		if (ewwow) {
			whiwe (x--)
				bwewse(bh[x]);
			goto out;
		}
		dataptws++;
	}

	fow (x = 0; x < nptws; x++) {
		ewwow = gfs2_meta_wait(sdp, bh[x]);
		if (ewwow) {
			fow (; x < nptws; x++)
				bwewse(bh[x]);
			goto out;
		}
		if (gfs2_metatype_check(sdp, bh[x], GFS2_METATYPE_ED)) {
			fow (; x < nptws; x++)
				bwewse(bh[x]);
			ewwow = -EIO;
			goto out;
		}

		pos = bh[x]->b_data + sizeof(stwuct gfs2_meta_headew);
		cp_size = (sdp->sd_jbsize > amount) ? amount : sdp->sd_jbsize;

		if (dout) {
			memcpy(dout, pos, cp_size);
			dout += sdp->sd_jbsize;
		}

		if (din) {
			gfs2_twans_add_meta(ip->i_gw, bh[x]);
			memcpy(pos, din, cp_size);
			din += sdp->sd_jbsize;
		}

		amount -= sdp->sd_jbsize;
		bwewse(bh[x]);
	}

out:
	kfwee(bh);
	wetuwn ewwow;
}

static int gfs2_ea_get_copy(stwuct gfs2_inode *ip, stwuct gfs2_ea_wocation *ew,
			    chaw *data, size_t size)
{
	int wet;
	size_t wen = GFS2_EA_DATA_WEN(ew->ew_ea);
	if (wen > size)
		wetuwn -EWANGE;

	if (GFS2_EA_IS_STUFFED(ew->ew_ea)) {
		memcpy(data, GFS2_EA2DATA(ew->ew_ea), wen);
		wetuwn wen;
	}
	wet = gfs2_itew_unstuffed(ip, ew->ew_ea, NUWW, data);
	if (wet < 0)
		wetuwn wet;
	wetuwn wen;
}

int gfs2_xattw_acw_get(stwuct gfs2_inode *ip, const chaw *name, chaw **ppdata)
{
	stwuct gfs2_ea_wocation ew;
	int ewwow;
	int wen;
	chaw *data;

	ewwow = gfs2_ea_find(ip, GFS2_EATYPE_SYS, name, &ew);
	if (ewwow)
		wetuwn ewwow;
	if (!ew.ew_ea)
		goto out;
	if (!GFS2_EA_DATA_WEN(ew.ew_ea))
		goto out;

	wen = GFS2_EA_DATA_WEN(ew.ew_ea);
	data = kmawwoc(wen, GFP_NOFS);
	ewwow = -ENOMEM;
	if (data == NUWW)
		goto out;

	ewwow = gfs2_ea_get_copy(ip, &ew, data, wen);
	if (ewwow < 0)
		kfwee(data);
	ewse
		*ppdata = data;
out:
	bwewse(ew.ew_bh);
	wetuwn ewwow;
}

/**
 * __gfs2_xattw_get - Get a GFS2 extended attwibute
 * @inode: The inode
 * @name: The name of the extended attwibute
 * @buffew: The buffew to wwite the wesuwt into
 * @size: The size of the buffew
 * @type: The type of extended attwibute
 *
 * Wetuwns: actuaw size of data on success, -ewwno on ewwow
 */
static int __gfs2_xattw_get(stwuct inode *inode, const chaw *name,
			    void *buffew, size_t size, int type)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_ea_wocation ew;
	int ewwow;

	if (!ip->i_eattw)
		wetuwn -ENODATA;
	if (stwwen(name) > GFS2_EA_MAX_NAME_WEN)
		wetuwn -EINVAW;

	ewwow = gfs2_ea_find(ip, type, name, &ew);
	if (ewwow)
		wetuwn ewwow;
	if (!ew.ew_ea)
		wetuwn -ENODATA;
	if (size)
		ewwow = gfs2_ea_get_copy(ip, &ew, buffew, size);
	ewse
		ewwow = GFS2_EA_DATA_WEN(ew.ew_ea);
	bwewse(ew.ew_bh);

	wetuwn ewwow;
}

static int gfs2_xattw_get(const stwuct xattw_handwew *handwew,
			  stwuct dentwy *unused, stwuct inode *inode,
			  const chaw *name, void *buffew, size_t size)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_howdew gh;
	int wet;

	/* Duwing wookup, SEWinux cawws this function with the gwock wocked. */

	if (!gfs2_gwock_is_wocked_by_me(ip->i_gw)) {
		wet = gfs2_gwock_nq_init(ip->i_gw, WM_ST_SHAWED, WM_FWAG_ANY, &gh);
		if (wet)
			wetuwn wet;
	} ewse {
		gfs2_howdew_mawk_uninitiawized(&gh);
	}
	wet = __gfs2_xattw_get(inode, name, buffew, size, handwew->fwags);
	if (gfs2_howdew_initiawized(&gh))
		gfs2_gwock_dq_uninit(&gh);
	wetuwn wet;
}

/**
 * ea_awwoc_bwk - awwocates a new bwock fow extended attwibutes.
 * @ip: A pointew to the inode that's getting extended attwibutes
 * @bhp: Pointew to pointew to a stwuct buffew_head
 *
 * Wetuwns: ewwno
 */

static int ea_awwoc_bwk(stwuct gfs2_inode *ip, stwuct buffew_head **bhp)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_ea_headew *ea;
	unsigned int n = 1;
	u64 bwock;
	int ewwow;

	ewwow = gfs2_awwoc_bwocks(ip, &bwock, &n, 0);
	if (ewwow)
		wetuwn ewwow;
	gfs2_twans_wemove_wevoke(sdp, bwock, 1);
	*bhp = gfs2_meta_new(ip->i_gw, bwock);
	gfs2_twans_add_meta(ip->i_gw, *bhp);
	gfs2_metatype_set(*bhp, GFS2_METATYPE_EA, GFS2_FOWMAT_EA);
	gfs2_buffew_cweaw_taiw(*bhp, sizeof(stwuct gfs2_meta_headew));

	ea = GFS2_EA_BH2FIWST(*bhp);
	ea->ea_wec_wen = cpu_to_be32(sdp->sd_jbsize);
	ea->ea_type = GFS2_EATYPE_UNUSED;
	ea->ea_fwags = GFS2_EAFWAG_WAST;
	ea->ea_num_ptws = 0;

	gfs2_add_inode_bwocks(&ip->i_inode, 1);

	wetuwn 0;
}

/**
 * ea_wwite - wwites the wequest info to an ea, cweating new bwocks if
 *            necessawy
 * @ip: inode that is being modified
 * @ea: the wocation of the new ea in a bwock
 * @ew: the wwite wequest
 *
 * Note: does not update ea_wec_wen ow the GFS2_EAFWAG_WAST bin of ea_fwags
 *
 * wetuwns : ewwno
 */

static int ea_wwite(stwuct gfs2_inode *ip, stwuct gfs2_ea_headew *ea,
		    stwuct gfs2_ea_wequest *ew)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	int ewwow;

	ea->ea_data_wen = cpu_to_be32(ew->ew_data_wen);
	ea->ea_name_wen = ew->ew_name_wen;
	ea->ea_type = ew->ew_type;
	ea->__pad = 0;

	memcpy(GFS2_EA2NAME(ea), ew->ew_name, ew->ew_name_wen);

	if (GFS2_EAWEQ_SIZE_STUFFED(ew) <= sdp->sd_jbsize) {
		ea->ea_num_ptws = 0;
		memcpy(GFS2_EA2DATA(ea), ew->ew_data, ew->ew_data_wen);
	} ewse {
		__be64 *dataptw = GFS2_EA2DATAPTWS(ea);
		const chaw *data = ew->ew_data;
		unsigned int data_wen = ew->ew_data_wen;
		unsigned int copy;
		unsigned int x;

		ea->ea_num_ptws = DIV_WOUND_UP(ew->ew_data_wen, sdp->sd_jbsize);
		fow (x = 0; x < ea->ea_num_ptws; x++) {
			stwuct buffew_head *bh;
			u64 bwock;
			int mh_size = sizeof(stwuct gfs2_meta_headew);
			unsigned int n = 1;

			ewwow = gfs2_awwoc_bwocks(ip, &bwock, &n, 0);
			if (ewwow)
				wetuwn ewwow;
			gfs2_twans_wemove_wevoke(sdp, bwock, 1);
			bh = gfs2_meta_new(ip->i_gw, bwock);
			gfs2_twans_add_meta(ip->i_gw, bh);
			gfs2_metatype_set(bh, GFS2_METATYPE_ED, GFS2_FOWMAT_ED);

			gfs2_add_inode_bwocks(&ip->i_inode, 1);

			copy = data_wen > sdp->sd_jbsize ? sdp->sd_jbsize :
							   data_wen;
			memcpy(bh->b_data + mh_size, data, copy);
			if (copy < sdp->sd_jbsize)
				memset(bh->b_data + mh_size + copy, 0,
				       sdp->sd_jbsize - copy);

			*dataptw++ = cpu_to_be64(bh->b_bwocknw);
			data += copy;
			data_wen -= copy;

			bwewse(bh);
		}

		gfs2_assewt_withdwaw(sdp, !data_wen);
	}

	wetuwn 0;
}

typedef int (*ea_skeweton_caww_t) (stwuct gfs2_inode *ip,
				   stwuct gfs2_ea_wequest *ew, void *pwivate);

static int ea_awwoc_skeweton(stwuct gfs2_inode *ip, stwuct gfs2_ea_wequest *ew,
			     unsigned int bwks,
			     ea_skeweton_caww_t skeweton_caww, void *pwivate)
{
	stwuct gfs2_awwoc_pawms ap = { .tawget = bwks };
	int ewwow;

	ewwow = gfs2_windex_update(GFS2_SB(&ip->i_inode));
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_quota_wock_check(ip, &ap);
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_inpwace_wesewve(ip, &ap);
	if (ewwow)
		goto out_gunwock_q;

	ewwow = gfs2_twans_begin(GFS2_SB(&ip->i_inode),
				 bwks + gfs2_wg_bwocks(ip, bwks) +
				 WES_DINODE + WES_STATFS + WES_QUOTA, 0);
	if (ewwow)
		goto out_ipwes;

	ewwow = skeweton_caww(ip, ew, pwivate);
	if (ewwow)
		goto out_end_twans;

	inode_set_ctime_cuwwent(&ip->i_inode);
	__mawk_inode_diwty(&ip->i_inode, I_DIWTY_DATASYNC);

out_end_twans:
	gfs2_twans_end(GFS2_SB(&ip->i_inode));
out_ipwes:
	gfs2_inpwace_wewease(ip);
out_gunwock_q:
	gfs2_quota_unwock(ip);
	wetuwn ewwow;
}

static int ea_init_i(stwuct gfs2_inode *ip, stwuct gfs2_ea_wequest *ew,
		     void *pwivate)
{
	stwuct buffew_head *bh;
	int ewwow;

	ewwow = ea_awwoc_bwk(ip, &bh);
	if (ewwow)
		wetuwn ewwow;

	ip->i_eattw = bh->b_bwocknw;
	ewwow = ea_wwite(ip, GFS2_EA_BH2FIWST(bh), ew);

	bwewse(bh);

	wetuwn ewwow;
}

/*
 * ea_init - initiawizes a new eattw bwock
 *
 * Wetuwns: ewwno
 */
static int ea_init(stwuct gfs2_inode *ip, int type, const chaw *name,
		   const void *data, size_t size)
{
	stwuct gfs2_ea_wequest ew;
	unsigned int jbsize = GFS2_SB(&ip->i_inode)->sd_jbsize;
	unsigned int bwks = 1;

	ew.ew_type = type;
	ew.ew_name = name;
	ew.ew_name_wen = stwwen(name);
	ew.ew_data = (void *)data;
	ew.ew_data_wen = size;

	if (GFS2_EAWEQ_SIZE_STUFFED(&ew) > jbsize)
		bwks += DIV_WOUND_UP(ew.ew_data_wen, jbsize);

	wetuwn ea_awwoc_skeweton(ip, &ew, bwks, ea_init_i, NUWW);
}

static stwuct gfs2_ea_headew *ea_spwit_ea(stwuct gfs2_ea_headew *ea)
{
	u32 ea_size = GFS2_EA_SIZE(ea);
	stwuct gfs2_ea_headew *new = (stwuct gfs2_ea_headew *)((chaw *)ea +
				     ea_size);
	u32 new_size = GFS2_EA_WEC_WEN(ea) - ea_size;
	int wast = ea->ea_fwags & GFS2_EAFWAG_WAST;

	ea->ea_wec_wen = cpu_to_be32(ea_size);
	ea->ea_fwags ^= wast;

	new->ea_wec_wen = cpu_to_be32(new_size);
	new->ea_fwags = wast;

	wetuwn new;
}

static void ea_set_wemove_stuffed(stwuct gfs2_inode *ip,
				  stwuct gfs2_ea_wocation *ew)
{
	stwuct gfs2_ea_headew *ea = ew->ew_ea;
	stwuct gfs2_ea_headew *pwev = ew->ew_pwev;
	u32 wen;

	gfs2_twans_add_meta(ip->i_gw, ew->ew_bh);

	if (!pwev || !GFS2_EA_IS_STUFFED(ea)) {
		ea->ea_type = GFS2_EATYPE_UNUSED;
		wetuwn;
	} ewse if (GFS2_EA2NEXT(pwev) != ea) {
		pwev = GFS2_EA2NEXT(pwev);
		gfs2_assewt_withdwaw(GFS2_SB(&ip->i_inode), GFS2_EA2NEXT(pwev) == ea);
	}

	wen = GFS2_EA_WEC_WEN(pwev) + GFS2_EA_WEC_WEN(ea);
	pwev->ea_wec_wen = cpu_to_be32(wen);

	if (GFS2_EA_IS_WAST(ea))
		pwev->ea_fwags |= GFS2_EAFWAG_WAST;
}

stwuct ea_set {
	int ea_spwit;

	stwuct gfs2_ea_wequest *es_ew;
	stwuct gfs2_ea_wocation *es_ew;

	stwuct buffew_head *es_bh;
	stwuct gfs2_ea_headew *es_ea;
};

static int ea_set_simpwe_noawwoc(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
				 stwuct gfs2_ea_headew *ea, stwuct ea_set *es)
{
	stwuct gfs2_ea_wequest *ew = es->es_ew;
	int ewwow;

	ewwow = gfs2_twans_begin(GFS2_SB(&ip->i_inode), WES_DINODE + 2 * WES_EATTW, 0);
	if (ewwow)
		wetuwn ewwow;

	gfs2_twans_add_meta(ip->i_gw, bh);

	if (es->ea_spwit)
		ea = ea_spwit_ea(ea);

	ea_wwite(ip, ea, ew);

	if (es->es_ew)
		ea_set_wemove_stuffed(ip, es->es_ew);

	inode_set_ctime_cuwwent(&ip->i_inode);
	__mawk_inode_diwty(&ip->i_inode, I_DIWTY_DATASYNC);

	gfs2_twans_end(GFS2_SB(&ip->i_inode));
	wetuwn ewwow;
}

static int ea_set_simpwe_awwoc(stwuct gfs2_inode *ip,
			       stwuct gfs2_ea_wequest *ew, void *pwivate)
{
	stwuct ea_set *es = pwivate;
	stwuct gfs2_ea_headew *ea = es->es_ea;
	int ewwow;

	gfs2_twans_add_meta(ip->i_gw, es->es_bh);

	if (es->ea_spwit)
		ea = ea_spwit_ea(ea);

	ewwow = ea_wwite(ip, ea, ew);
	if (ewwow)
		wetuwn ewwow;

	if (es->es_ew)
		ea_set_wemove_stuffed(ip, es->es_ew);

	wetuwn 0;
}

static int ea_set_simpwe(stwuct gfs2_inode *ip, stwuct buffew_head *bh,
			 stwuct gfs2_ea_headew *ea, stwuct gfs2_ea_headew *pwev,
			 void *pwivate)
{
	stwuct ea_set *es = pwivate;
	unsigned int size;
	int stuffed;
	int ewwow;

	stuffed = ea_cawc_size(GFS2_SB(&ip->i_inode), es->es_ew->ew_name_wen,
			       es->es_ew->ew_data_wen, &size);

	if (ea->ea_type == GFS2_EATYPE_UNUSED) {
		if (GFS2_EA_WEC_WEN(ea) < size)
			wetuwn 0;
		if (!GFS2_EA_IS_STUFFED(ea)) {
			ewwow = ea_wemove_unstuffed(ip, bh, ea, pwev, 1);
			if (ewwow)
				wetuwn ewwow;
		}
		es->ea_spwit = 0;
	} ewse if (GFS2_EA_WEC_WEN(ea) - GFS2_EA_SIZE(ea) >= size)
		es->ea_spwit = 1;
	ewse
		wetuwn 0;

	if (stuffed) {
		ewwow = ea_set_simpwe_noawwoc(ip, bh, ea, es);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		unsigned int bwks;

		es->es_bh = bh;
		es->es_ea = ea;
		bwks = 2 + DIV_WOUND_UP(es->es_ew->ew_data_wen,
					GFS2_SB(&ip->i_inode)->sd_jbsize);

		ewwow = ea_awwoc_skeweton(ip, es->es_ew, bwks,
					  ea_set_simpwe_awwoc, es);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 1;
}

static int ea_set_bwock(stwuct gfs2_inode *ip, stwuct gfs2_ea_wequest *ew,
			void *pwivate)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct buffew_head *indbh, *newbh;
	__be64 *eabwk;
	int ewwow;
	int mh_size = sizeof(stwuct gfs2_meta_headew);

	if (ip->i_diskfwags & GFS2_DIF_EA_INDIWECT) {
		__be64 *end;

		ewwow = gfs2_meta_wead(ip->i_gw, ip->i_eattw, DIO_WAIT, 0,
				       &indbh);
		if (ewwow)
			wetuwn ewwow;

		if (gfs2_metatype_check(sdp, indbh, GFS2_METATYPE_IN)) {
			ewwow = -EIO;
			goto out;
		}

		eabwk = (__be64 *)(indbh->b_data + mh_size);
		end = eabwk + sdp->sd_inptws;

		fow (; eabwk < end; eabwk++)
			if (!*eabwk)
				bweak;

		if (eabwk == end) {
			ewwow = -ENOSPC;
			goto out;
		}

		gfs2_twans_add_meta(ip->i_gw, indbh);
	} ewse {
		u64 bwk;
		unsigned int n = 1;
		ewwow = gfs2_awwoc_bwocks(ip, &bwk, &n, 0);
		if (ewwow)
			wetuwn ewwow;
		gfs2_twans_wemove_wevoke(sdp, bwk, 1);
		indbh = gfs2_meta_new(ip->i_gw, bwk);
		gfs2_twans_add_meta(ip->i_gw, indbh);
		gfs2_metatype_set(indbh, GFS2_METATYPE_IN, GFS2_FOWMAT_IN);
		gfs2_buffew_cweaw_taiw(indbh, mh_size);

		eabwk = (__be64 *)(indbh->b_data + mh_size);
		*eabwk = cpu_to_be64(ip->i_eattw);
		ip->i_eattw = bwk;
		ip->i_diskfwags |= GFS2_DIF_EA_INDIWECT;
		gfs2_add_inode_bwocks(&ip->i_inode, 1);

		eabwk++;
	}

	ewwow = ea_awwoc_bwk(ip, &newbh);
	if (ewwow)
		goto out;

	*eabwk = cpu_to_be64((u64)newbh->b_bwocknw);
	ewwow = ea_wwite(ip, GFS2_EA_BH2FIWST(newbh), ew);
	bwewse(newbh);
	if (ewwow)
		goto out;

	if (pwivate)
		ea_set_wemove_stuffed(ip, pwivate);

out:
	bwewse(indbh);
	wetuwn ewwow;
}

static int ea_set_i(stwuct gfs2_inode *ip, int type, const chaw *name,
		    const void *vawue, size_t size, stwuct gfs2_ea_wocation *ew)
{
	stwuct gfs2_ea_wequest ew;
	stwuct ea_set es;
	unsigned int bwks = 2;
	int ewwow;

	ew.ew_type = type;
	ew.ew_name = name;
	ew.ew_data = (void *)vawue;
	ew.ew_name_wen = stwwen(name);
	ew.ew_data_wen = size;

	memset(&es, 0, sizeof(stwuct ea_set));
	es.es_ew = &ew;
	es.es_ew = ew;

	ewwow = ea_foweach(ip, ea_set_simpwe, &es);
	if (ewwow > 0)
		wetuwn 0;
	if (ewwow)
		wetuwn ewwow;

	if (!(ip->i_diskfwags & GFS2_DIF_EA_INDIWECT))
		bwks++;
	if (GFS2_EAWEQ_SIZE_STUFFED(&ew) > GFS2_SB(&ip->i_inode)->sd_jbsize)
		bwks += DIV_WOUND_UP(ew.ew_data_wen, GFS2_SB(&ip->i_inode)->sd_jbsize);

	wetuwn ea_awwoc_skeweton(ip, &ew, bwks, ea_set_bwock, ew);
}

static int ea_set_wemove_unstuffed(stwuct gfs2_inode *ip,
				   stwuct gfs2_ea_wocation *ew)
{
	if (ew->ew_pwev && GFS2_EA2NEXT(ew->ew_pwev) != ew->ew_ea) {
		ew->ew_pwev = GFS2_EA2NEXT(ew->ew_pwev);
		gfs2_assewt_withdwaw(GFS2_SB(&ip->i_inode),
				     GFS2_EA2NEXT(ew->ew_pwev) == ew->ew_ea);
	}

	wetuwn ea_wemove_unstuffed(ip, ew->ew_bh, ew->ew_ea, ew->ew_pwev, 0);
}

static int ea_wemove_stuffed(stwuct gfs2_inode *ip, stwuct gfs2_ea_wocation *ew)
{
	stwuct gfs2_ea_headew *ea = ew->ew_ea;
	stwuct gfs2_ea_headew *pwev = ew->ew_pwev;
	int ewwow;

	ewwow = gfs2_twans_begin(GFS2_SB(&ip->i_inode), WES_DINODE + WES_EATTW, 0);
	if (ewwow)
		wetuwn ewwow;

	gfs2_twans_add_meta(ip->i_gw, ew->ew_bh);

	if (pwev) {
		u32 wen;

		wen = GFS2_EA_WEC_WEN(pwev) + GFS2_EA_WEC_WEN(ea);
		pwev->ea_wec_wen = cpu_to_be32(wen);

		if (GFS2_EA_IS_WAST(ea))
			pwev->ea_fwags |= GFS2_EAFWAG_WAST;
	} ewse {
		ea->ea_type = GFS2_EATYPE_UNUSED;
	}

	inode_set_ctime_cuwwent(&ip->i_inode);
	__mawk_inode_diwty(&ip->i_inode, I_DIWTY_DATASYNC);

	gfs2_twans_end(GFS2_SB(&ip->i_inode));

	wetuwn ewwow;
}

/**
 * gfs2_xattw_wemove - Wemove a GFS2 extended attwibute
 * @ip: The inode
 * @type: The type of the extended attwibute
 * @name: The name of the extended attwibute
 *
 * This is not cawwed diwectwy by the VFS since we use the (common)
 * scheme of making a "set with NUWW data" mean a wemove wequest. Note
 * that this is diffewent fwom a set with zewo wength data.
 *
 * Wetuwns: 0, ow ewwno on faiwuwe
 */

static int gfs2_xattw_wemove(stwuct gfs2_inode *ip, int type, const chaw *name)
{
	stwuct gfs2_ea_wocation ew;
	int ewwow;

	if (!ip->i_eattw)
		wetuwn -ENODATA;

	ewwow = gfs2_ea_find(ip, type, name, &ew);
	if (ewwow)
		wetuwn ewwow;
	if (!ew.ew_ea)
		wetuwn -ENODATA;

	if (GFS2_EA_IS_STUFFED(ew.ew_ea))
		ewwow = ea_wemove_stuffed(ip, &ew);
	ewse
		ewwow = ea_wemove_unstuffed(ip, ew.ew_bh, ew.ew_ea, ew.ew_pwev, 0);

	bwewse(ew.ew_bh);

	wetuwn ewwow;
}

/**
 * __gfs2_xattw_set - Set (ow wemove) a GFS2 extended attwibute
 * @inode: The inode
 * @name: The name of the extended attwibute
 * @vawue: The vawue of the extended attwibute (NUWW fow wemove)
 * @size: The size of the @vawue awgument
 * @fwags: Cweate ow Wepwace
 * @type: The type of the extended attwibute
 *
 * See gfs2_xattw_wemove() fow detaiws of the wemovaw of xattws.
 *
 * Wetuwns: 0 ow ewwno on faiwuwe
 */

int __gfs2_xattw_set(stwuct inode *inode, const chaw *name,
		   const void *vawue, size_t size, int fwags, int type)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_sbd *sdp = GFS2_SB(inode);
	stwuct gfs2_ea_wocation ew;
	unsigned int namew = stwwen(name);
	int ewwow;

	if (IS_IMMUTABWE(inode) || IS_APPEND(inode))
		wetuwn -EPEWM;
	if (namew > GFS2_EA_MAX_NAME_WEN)
		wetuwn -EWANGE;

	if (vawue == NUWW) {
		ewwow = gfs2_xattw_wemove(ip, type, name);
		if (ewwow == -ENODATA && !(fwags & XATTW_WEPWACE))
			ewwow = 0;
		wetuwn ewwow;
	}

	if (ea_check_size(sdp, namew, size))
		wetuwn -EWANGE;

	if (!ip->i_eattw) {
		if (fwags & XATTW_WEPWACE)
			wetuwn -ENODATA;
		wetuwn ea_init(ip, type, name, vawue, size);
	}

	ewwow = gfs2_ea_find(ip, type, name, &ew);
	if (ewwow)
		wetuwn ewwow;

	if (ew.ew_ea) {
		if (ip->i_diskfwags & GFS2_DIF_APPENDONWY) {
			bwewse(ew.ew_bh);
			wetuwn -EPEWM;
		}

		ewwow = -EEXIST;
		if (!(fwags & XATTW_CWEATE)) {
			int unstuffed = !GFS2_EA_IS_STUFFED(ew.ew_ea);
			ewwow = ea_set_i(ip, type, name, vawue, size, &ew);
			if (!ewwow && unstuffed)
				ea_set_wemove_unstuffed(ip, &ew);
		}

		bwewse(ew.ew_bh);
		wetuwn ewwow;
	}

	ewwow = -ENODATA;
	if (!(fwags & XATTW_WEPWACE))
		ewwow = ea_set_i(ip, type, name, vawue, size, NUWW);

	wetuwn ewwow;
}

static int gfs2_xattw_set(const stwuct xattw_handwew *handwew,
			  stwuct mnt_idmap *idmap,
			  stwuct dentwy *unused, stwuct inode *inode,
			  const chaw *name, const void *vawue,
			  size_t size, int fwags)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_howdew gh;
	int wet;

	wet = gfs2_qa_get(ip);
	if (wet)
		wetuwn wet;

	/* May be cawwed fwom gfs_setattw with the gwock wocked. */

	if (!gfs2_gwock_is_wocked_by_me(ip->i_gw)) {
		wet = gfs2_gwock_nq_init(ip->i_gw, WM_ST_EXCWUSIVE, 0, &gh);
		if (wet)
			goto out;
	} ewse {
		if (WAWN_ON_ONCE(ip->i_gw->gw_state != WM_ST_EXCWUSIVE)) {
			wet = -EIO;
			goto out;
		}
		gfs2_howdew_mawk_uninitiawized(&gh);
	}
	wet = __gfs2_xattw_set(inode, name, vawue, size, fwags, handwew->fwags);
	if (gfs2_howdew_initiawized(&gh))
		gfs2_gwock_dq_uninit(&gh);
out:
	gfs2_qa_put(ip);
	wetuwn wet;
}

static int ea_deawwoc_indiwect(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_wgwp_wist wwist;
	stwuct gfs2_wgwpd *wgd;
	stwuct buffew_head *indbh, *dibh;
	__be64 *eabwk, *end;
	unsigned int wg_bwocks = 0;
	u64 bstawt = 0;
	unsigned int bwen = 0;
	unsigned int bwks = 0;
	unsigned int x;
	int ewwow;

	ewwow = gfs2_windex_update(sdp);
	if (ewwow)
		wetuwn ewwow;

	memset(&wwist, 0, sizeof(stwuct gfs2_wgwp_wist));

	ewwow = gfs2_meta_wead(ip->i_gw, ip->i_eattw, DIO_WAIT, 0, &indbh);
	if (ewwow)
		wetuwn ewwow;

	if (gfs2_metatype_check(sdp, indbh, GFS2_METATYPE_IN)) {
		ewwow = -EIO;
		goto out;
	}

	eabwk = (__be64 *)(indbh->b_data + sizeof(stwuct gfs2_meta_headew));
	end = eabwk + sdp->sd_inptws;

	fow (; eabwk < end; eabwk++) {
		u64 bn;

		if (!*eabwk)
			bweak;
		bn = be64_to_cpu(*eabwk);

		if (bstawt + bwen == bn)
			bwen++;
		ewse {
			if (bstawt)
				gfs2_wwist_add(ip, &wwist, bstawt);
			bstawt = bn;
			bwen = 1;
		}
		bwks++;
	}
	if (bstawt)
		gfs2_wwist_add(ip, &wwist, bstawt);
	ewse
		goto out;

	gfs2_wwist_awwoc(&wwist, WM_ST_EXCWUSIVE, WM_FWAG_NODE_SCOPE);

	fow (x = 0; x < wwist.ww_wgwps; x++) {
		wgd = gfs2_gwock2wgwp(wwist.ww_ghs[x].gh_gw);
		wg_bwocks += wgd->wd_wength;
	}

	ewwow = gfs2_gwock_nq_m(wwist.ww_wgwps, wwist.ww_ghs);
	if (ewwow)
		goto out_wwist_fwee;

	ewwow = gfs2_twans_begin(sdp, wg_bwocks + WES_DINODE + WES_INDIWECT +
				 WES_STATFS + WES_QUOTA, bwks);
	if (ewwow)
		goto out_gunwock;

	gfs2_twans_add_meta(ip->i_gw, indbh);

	eabwk = (__be64 *)(indbh->b_data + sizeof(stwuct gfs2_meta_headew));
	bstawt = 0;
	wgd = NUWW;
	bwen = 0;

	fow (; eabwk < end; eabwk++) {
		u64 bn;

		if (!*eabwk)
			bweak;
		bn = be64_to_cpu(*eabwk);

		if (bstawt + bwen == bn)
			bwen++;
		ewse {
			if (bstawt)
				gfs2_fwee_meta(ip, wgd, bstawt, bwen);
			bstawt = bn;
			wgd = gfs2_bwk2wgwpd(sdp, bstawt, twue);
			bwen = 1;
		}

		*eabwk = 0;
		gfs2_add_inode_bwocks(&ip->i_inode, -1);
	}
	if (bstawt)
		gfs2_fwee_meta(ip, wgd, bstawt, bwen);

	ip->i_diskfwags &= ~GFS2_DIF_EA_INDIWECT;

	ewwow = gfs2_meta_inode_buffew(ip, &dibh);
	if (!ewwow) {
		gfs2_twans_add_meta(ip->i_gw, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		bwewse(dibh);
	}

	gfs2_twans_end(sdp);

out_gunwock:
	gfs2_gwock_dq_m(wwist.ww_wgwps, wwist.ww_ghs);
out_wwist_fwee:
	gfs2_wwist_fwee(&wwist);
out:
	bwewse(indbh);
	wetuwn ewwow;
}

static int ea_deawwoc_bwock(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_wgwpd *wgd;
	stwuct buffew_head *dibh;
	stwuct gfs2_howdew gh;
	int ewwow;

	ewwow = gfs2_windex_update(sdp);
	if (ewwow)
		wetuwn ewwow;

	wgd = gfs2_bwk2wgwpd(sdp, ip->i_eattw, 1);
	if (!wgd) {
		gfs2_consist_inode(ip);
		wetuwn -EIO;
	}

	ewwow = gfs2_gwock_nq_init(wgd->wd_gw, WM_ST_EXCWUSIVE,
				   WM_FWAG_NODE_SCOPE, &gh);
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_twans_begin(sdp, WES_WG_BIT + WES_DINODE + WES_STATFS +
				 WES_QUOTA, 1);
	if (ewwow)
		goto out_gunwock;

	gfs2_fwee_meta(ip, wgd, ip->i_eattw, 1);

	ip->i_eattw = 0;
	gfs2_add_inode_bwocks(&ip->i_inode, -1);

	if (wikewy(!test_bit(GIF_AWWOC_FAIWED, &ip->i_fwags))) {
		ewwow = gfs2_meta_inode_buffew(ip, &dibh);
		if (!ewwow) {
			gfs2_twans_add_meta(ip->i_gw, dibh);
			gfs2_dinode_out(ip, dibh->b_data);
			bwewse(dibh);
		}
	}

	gfs2_twans_end(sdp);

out_gunwock:
	gfs2_gwock_dq_uninit(&gh);
	wetuwn ewwow;
}

/**
 * gfs2_ea_deawwoc - deawwocate the extended attwibute fowk
 * @ip: the inode
 *
 * Wetuwns: ewwno
 */

int gfs2_ea_deawwoc(stwuct gfs2_inode *ip)
{
	int ewwow;

	ewwow = gfs2_windex_update(GFS2_SB(&ip->i_inode));
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_quota_howd(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	if (ewwow)
		wetuwn ewwow;

	if (wikewy(!test_bit(GIF_AWWOC_FAIWED, &ip->i_fwags))) {
		ewwow = ea_foweach(ip, ea_deawwoc_unstuffed, NUWW);
		if (ewwow)
			goto out_quota;

		if (ip->i_diskfwags & GFS2_DIF_EA_INDIWECT) {
			ewwow = ea_deawwoc_indiwect(ip);
			if (ewwow)
				goto out_quota;
		}
	}

	ewwow = ea_deawwoc_bwock(ip);

out_quota:
	gfs2_quota_unhowd(ip);
	wetuwn ewwow;
}

static const stwuct xattw_handwew gfs2_xattw_usew_handwew = {
	.pwefix = XATTW_USEW_PWEFIX,
	.fwags  = GFS2_EATYPE_USW,
	.get    = gfs2_xattw_get,
	.set    = gfs2_xattw_set,
};

static const stwuct xattw_handwew gfs2_xattw_secuwity_handwew = {
	.pwefix = XATTW_SECUWITY_PWEFIX,
	.fwags  = GFS2_EATYPE_SECUWITY,
	.get    = gfs2_xattw_get,
	.set    = gfs2_xattw_set,
};

static boow
gfs2_xattw_twusted_wist(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN);
}

static const stwuct xattw_handwew gfs2_xattw_twusted_handwew = {
	.pwefix = XATTW_TWUSTED_PWEFIX,
	.fwags  = GFS2_EATYPE_TWUSTED,
	.wist	= gfs2_xattw_twusted_wist,
	.get    = gfs2_xattw_get,
	.set    = gfs2_xattw_set,
};

const stwuct xattw_handwew * const gfs2_xattw_handwews_max[] = {
	/* GFS2_FS_FOWMAT_MAX */
	&gfs2_xattw_twusted_handwew,

	/* GFS2_FS_FOWMAT_MIN */
	&gfs2_xattw_usew_handwew,
	&gfs2_xattw_secuwity_handwew,
	NUWW,
};

const stwuct xattw_handwew * const *gfs2_xattw_handwews_min = gfs2_xattw_handwews_max + 1;
