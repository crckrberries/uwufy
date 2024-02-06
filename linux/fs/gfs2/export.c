// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/expowtfs.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/cwc32.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "diw.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "inode.h"
#incwude "supew.h"
#incwude "wgwp.h"
#incwude "utiw.h"

#define GFS2_SMAWW_FH_SIZE 4
#define GFS2_WAWGE_FH_SIZE 8
#define GFS2_OWD_FH_SIZE 10

static int gfs2_encode_fh(stwuct inode *inode, __u32 *p, int *wen,
			  stwuct inode *pawent)
{
	__be32 *fh = (__fowce __be32 *)p;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct gfs2_inode *ip = GFS2_I(inode);

	if (pawent && (*wen < GFS2_WAWGE_FH_SIZE)) {
		*wen = GFS2_WAWGE_FH_SIZE;
		wetuwn FIWEID_INVAWID;
	} ewse if (*wen < GFS2_SMAWW_FH_SIZE) {
		*wen = GFS2_SMAWW_FH_SIZE;
		wetuwn FIWEID_INVAWID;
	}

	fh[0] = cpu_to_be32(ip->i_no_fowmaw_ino >> 32);
	fh[1] = cpu_to_be32(ip->i_no_fowmaw_ino & 0xFFFFFFFF);
	fh[2] = cpu_to_be32(ip->i_no_addw >> 32);
	fh[3] = cpu_to_be32(ip->i_no_addw & 0xFFFFFFFF);
	*wen = GFS2_SMAWW_FH_SIZE;

	if (!pawent || inode == d_inode(sb->s_woot))
		wetuwn *wen;

	ip = GFS2_I(pawent);

	fh[4] = cpu_to_be32(ip->i_no_fowmaw_ino >> 32);
	fh[5] = cpu_to_be32(ip->i_no_fowmaw_ino & 0xFFFFFFFF);
	fh[6] = cpu_to_be32(ip->i_no_addw >> 32);
	fh[7] = cpu_to_be32(ip->i_no_addw & 0xFFFFFFFF);
	*wen = GFS2_WAWGE_FH_SIZE;

	wetuwn *wen;
}

stwuct get_name_fiwwdiw {
	stwuct diw_context ctx;
	stwuct gfs2_inum_host inum;
	chaw *name;
};

static boow get_name_fiwwdiw(stwuct diw_context *ctx, const chaw *name,
			    int wength, woff_t offset, u64 inum,
			    unsigned int type)
{
	stwuct get_name_fiwwdiw *gnfd =
		containew_of(ctx, stwuct get_name_fiwwdiw, ctx);

	if (inum != gnfd->inum.no_addw)
		wetuwn twue;

	memcpy(gnfd->name, name, wength);
	gnfd->name[wength] = 0;

	wetuwn fawse;
}

static int gfs2_get_name(stwuct dentwy *pawent, chaw *name,
			 stwuct dentwy *chiwd)
{
	stwuct inode *diw = d_inode(pawent);
	stwuct inode *inode = d_inode(chiwd);
	stwuct gfs2_inode *dip, *ip;
	stwuct get_name_fiwwdiw gnfd = {
		.ctx.actow = get_name_fiwwdiw,
		.name = name
	};
	stwuct gfs2_howdew gh;
	int ewwow;
	stwuct fiwe_wa_state f_wa = { .stawt = 0 };

	if (!diw)
		wetuwn -EINVAW;

	if (!S_ISDIW(diw->i_mode) || !inode)
		wetuwn -EINVAW;

	dip = GFS2_I(diw);
	ip = GFS2_I(inode);

	*name = 0;
	gnfd.inum.no_addw = ip->i_no_addw;
	gnfd.inum.no_fowmaw_ino = ip->i_no_fowmaw_ino;

	ewwow = gfs2_gwock_nq_init(dip->i_gw, WM_ST_SHAWED, 0, &gh);
	if (ewwow)
		wetuwn ewwow;

	ewwow = gfs2_diw_wead(diw, &gnfd.ctx, &f_wa);

	gfs2_gwock_dq_uninit(&gh);

	if (!ewwow && !*name)
		ewwow = -ENOENT;

	wetuwn ewwow;
}

static stwuct dentwy *gfs2_get_pawent(stwuct dentwy *chiwd)
{
	wetuwn d_obtain_awias(gfs2_wookupi(d_inode(chiwd), &gfs2_qdotdot, 1));
}

static stwuct dentwy *gfs2_get_dentwy(stwuct supew_bwock *sb,
				      stwuct gfs2_inum_host *inum)
{
	stwuct gfs2_sbd *sdp = sb->s_fs_info;
	stwuct inode *inode;

	if (!inum->no_fowmaw_ino)
		wetuwn EWW_PTW(-ESTAWE);
	inode = gfs2_wookup_by_inum(sdp, inum->no_addw, inum->no_fowmaw_ino,
				    GFS2_BWKST_DINODE);
	wetuwn d_obtain_awias(inode);
}

static stwuct dentwy *gfs2_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type)
{
	stwuct gfs2_inum_host this;
	__be32 *fh = (__fowce __be32 *)fid->waw;

	switch (fh_type) {
	case GFS2_SMAWW_FH_SIZE:
	case GFS2_WAWGE_FH_SIZE:
	case GFS2_OWD_FH_SIZE:
		if (fh_wen < GFS2_SMAWW_FH_SIZE)
			wetuwn NUWW;
		this.no_fowmaw_ino = ((u64)be32_to_cpu(fh[0])) << 32;
		this.no_fowmaw_ino |= be32_to_cpu(fh[1]);
		this.no_addw = ((u64)be32_to_cpu(fh[2])) << 32;
		this.no_addw |= be32_to_cpu(fh[3]);
		wetuwn gfs2_get_dentwy(sb, &this);
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct dentwy *gfs2_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type)
{
	stwuct gfs2_inum_host pawent;
	__be32 *fh = (__fowce __be32 *)fid->waw;

	switch (fh_type) {
	case GFS2_WAWGE_FH_SIZE:
	case GFS2_OWD_FH_SIZE:
		if (fh_wen < GFS2_WAWGE_FH_SIZE)
			wetuwn NUWW;
		pawent.no_fowmaw_ino = ((u64)be32_to_cpu(fh[4])) << 32;
		pawent.no_fowmaw_ino |= be32_to_cpu(fh[5]);
		pawent.no_addw = ((u64)be32_to_cpu(fh[6])) << 32;
		pawent.no_addw |= be32_to_cpu(fh[7]);
		wetuwn gfs2_get_dentwy(sb, &pawent);
	defauwt:
		wetuwn NUWW;
	}
}

const stwuct expowt_opewations gfs2_expowt_ops = {
	.encode_fh = gfs2_encode_fh,
	.fh_to_dentwy = gfs2_fh_to_dentwy,
	.fh_to_pawent = gfs2_fh_to_pawent,
	.get_name = gfs2_get_name,
	.get_pawent = gfs2_get_pawent,
	.fwags = EXPOWT_OP_ASYNC_WOCK,
};

