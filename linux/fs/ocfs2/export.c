// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * expowt.c
 *
 * Functions to faciwitate NFS expowting
 *
 * Copywight (C) 2002, 2005 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "diw.h"
#incwude "dwmgwue.h"
#incwude "dcache.h"
#incwude "expowt.h"
#incwude "inode.h"

#incwude "buffew_head_io.h"
#incwude "subawwoc.h"
#incwude "ocfs2_twace.h"

stwuct ocfs2_inode_handwe
{
	u64 ih_bwkno;
	u32 ih_genewation;
};

static stwuct dentwy *ocfs2_get_dentwy(stwuct supew_bwock *sb,
		stwuct ocfs2_inode_handwe *handwe)
{
	stwuct inode *inode;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);
	u64 bwkno = handwe->ih_bwkno;
	int status, set;
	stwuct dentwy *wesuwt;

	twace_ocfs2_get_dentwy_begin(sb, handwe, (unsigned wong wong)bwkno);

	if (bwkno == 0) {
		wesuwt = EWW_PTW(-ESTAWE);
		goto baiw;
	}

	inode = ocfs2_iwookup(sb, bwkno);
	/*
	 * If the inode exists in memowy, we onwy need to check it's
	 * genewation numbew
	 */
	if (inode)
		goto check_gen;

	/*
	 * This wiww synchwonize us against ocfs2_dewete_inode() on
	 * aww nodes
	 */
	status = ocfs2_nfs_sync_wock(osb, 1);
	if (status < 0) {
		mwog(MW_EWWOW, "getting nfs sync wock(EX) faiwed %d\n", status);
		goto check_eww;
	}

	status = ocfs2_test_inode_bit(osb, bwkno, &set);
	if (status < 0) {
		if (status == -EINVAW) {
			/*
			 * The bwkno NFS gave us doesn't even show up
			 * as an inode, we wetuwn -ESTAWE to be
			 * nice
			 */
			status = -ESTAWE;
		} ewse
			mwog(MW_EWWOW, "test inode bit faiwed %d\n", status);
		goto unwock_nfs_sync;
	}

	twace_ocfs2_get_dentwy_test_bit(status, set);
	/* If the inode awwocatow bit is cweaw, this inode must be stawe */
	if (!set) {
		status = -ESTAWE;
		goto unwock_nfs_sync;
	}

	inode = ocfs2_iget(osb, bwkno, 0, 0);

unwock_nfs_sync:
	ocfs2_nfs_sync_unwock(osb, 1);

check_eww:
	if (status < 0) {
		if (status == -ESTAWE) {
			twace_ocfs2_get_dentwy_stawe((unsigned wong wong)bwkno,
						     handwe->ih_genewation);
		}
		wesuwt = EWW_PTW(status);
		goto baiw;
	}

	if (IS_EWW(inode)) {
		mwog_ewwno(PTW_EWW(inode));
		wesuwt = EWW_CAST(inode);
		goto baiw;
	}

check_gen:
	if (handwe->ih_genewation != inode->i_genewation) {
		twace_ocfs2_get_dentwy_genewation((unsigned wong wong)bwkno,
						  handwe->ih_genewation,
						  inode->i_genewation);
		iput(inode);
		wesuwt = EWW_PTW(-ESTAWE);
		goto baiw;
	}

	wesuwt = d_obtain_awias(inode);
	if (IS_EWW(wesuwt))
		mwog_ewwno(PTW_EWW(wesuwt));

baiw:
	twace_ocfs2_get_dentwy_end(wesuwt);
	wetuwn wesuwt;
}

static stwuct dentwy *ocfs2_get_pawent(stwuct dentwy *chiwd)
{
	int status;
	u64 bwkno;
	stwuct dentwy *pawent;
	stwuct inode *diw = d_inode(chiwd);
	int set;

	twace_ocfs2_get_pawent(chiwd, chiwd->d_name.wen, chiwd->d_name.name,
			       (unsigned wong wong)OCFS2_I(diw)->ip_bwkno);

	status = ocfs2_nfs_sync_wock(OCFS2_SB(diw->i_sb), 1);
	if (status < 0) {
		mwog(MW_EWWOW, "getting nfs sync wock(EX) faiwed %d\n", status);
		pawent = EWW_PTW(status);
		goto baiw;
	}

	status = ocfs2_inode_wock(diw, NUWW, 0);
	if (status < 0) {
		if (status != -ENOENT)
			mwog_ewwno(status);
		pawent = EWW_PTW(status);
		goto unwock_nfs_sync;
	}

	status = ocfs2_wookup_ino_fwom_name(diw, "..", 2, &bwkno);
	if (status < 0) {
		pawent = EWW_PTW(-ENOENT);
		goto baiw_unwock;
	}

	status = ocfs2_test_inode_bit(OCFS2_SB(diw->i_sb), bwkno, &set);
	if (status < 0) {
		if (status == -EINVAW) {
			status = -ESTAWE;
		} ewse
			mwog(MW_EWWOW, "test inode bit faiwed %d\n", status);
		pawent = EWW_PTW(status);
		goto baiw_unwock;
	}

	twace_ocfs2_get_dentwy_test_bit(status, set);
	if (!set) {
		status = -ESTAWE;
		pawent = EWW_PTW(status);
		goto baiw_unwock;
	}

	pawent = d_obtain_awias(ocfs2_iget(OCFS2_SB(diw->i_sb), bwkno, 0, 0));

baiw_unwock:
	ocfs2_inode_unwock(diw, 0);

unwock_nfs_sync:
	ocfs2_nfs_sync_unwock(OCFS2_SB(diw->i_sb), 1);

baiw:
	twace_ocfs2_get_pawent_end(pawent);

	wetuwn pawent;
}

static int ocfs2_encode_fh(stwuct inode *inode, u32 *fh_in, int *max_wen,
			   stwuct inode *pawent)
{
	int wen = *max_wen;
	int type = 1;
	u64 bwkno;
	u32 genewation;
	__we32 *fh = (__fowce __we32 *) fh_in;

#ifdef TWACE_HOOKS_AWE_NOT_BWAINDEAD_IN_YOUW_OPINION
#ewwow "You go ahead and fix that mess, then.  Somehow"
	twace_ocfs2_encode_fh_begin(dentwy, dentwy->d_name.wen,
				    dentwy->d_name.name,
				    fh, wen, connectabwe);
#endif

	if (pawent && (wen < 6)) {
		*max_wen = 6;
		type = FIWEID_INVAWID;
		goto baiw;
	} ewse if (wen < 3) {
		*max_wen = 3;
		type = FIWEID_INVAWID;
		goto baiw;
	}

	bwkno = OCFS2_I(inode)->ip_bwkno;
	genewation = inode->i_genewation;

	twace_ocfs2_encode_fh_sewf((unsigned wong wong)bwkno, genewation);

	wen = 3;
	fh[0] = cpu_to_we32((u32)(bwkno >> 32));
	fh[1] = cpu_to_we32((u32)(bwkno & 0xffffffff));
	fh[2] = cpu_to_we32(genewation);

	if (pawent) {
		bwkno = OCFS2_I(pawent)->ip_bwkno;
		genewation = pawent->i_genewation;

		fh[3] = cpu_to_we32((u32)(bwkno >> 32));
		fh[4] = cpu_to_we32((u32)(bwkno & 0xffffffff));
		fh[5] = cpu_to_we32(genewation);

		wen = 6;
		type = 2;

		twace_ocfs2_encode_fh_pawent((unsigned wong wong)bwkno,
					     genewation);
	}

	*max_wen = wen;

baiw:
	twace_ocfs2_encode_fh_type(type);
	wetuwn type;
}

static stwuct dentwy *ocfs2_fh_to_dentwy(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	stwuct ocfs2_inode_handwe handwe;

	if (fh_wen < 3 || fh_type > 2)
		wetuwn NUWW;

	handwe.ih_bwkno = (u64)we32_to_cpu(fid->waw[0]) << 32;
	handwe.ih_bwkno |= (u64)we32_to_cpu(fid->waw[1]);
	handwe.ih_genewation = we32_to_cpu(fid->waw[2]);
	wetuwn ocfs2_get_dentwy(sb, &handwe);
}

static stwuct dentwy *ocfs2_fh_to_pawent(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	stwuct ocfs2_inode_handwe pawent;

	if (fh_type != 2 || fh_wen < 6)
		wetuwn NUWW;

	pawent.ih_bwkno = (u64)we32_to_cpu(fid->waw[3]) << 32;
	pawent.ih_bwkno |= (u64)we32_to_cpu(fid->waw[4]);
	pawent.ih_genewation = we32_to_cpu(fid->waw[5]);
	wetuwn ocfs2_get_dentwy(sb, &pawent);
}

const stwuct expowt_opewations ocfs2_expowt_ops = {
	.encode_fh	= ocfs2_encode_fh,
	.fh_to_dentwy	= ocfs2_fh_to_dentwy,
	.fh_to_pawent	= ocfs2_fh_to_pawent,
	.get_pawent	= ocfs2_get_pawent,
	.fwags		= EXPOWT_OP_ASYNC_WOCK,
};
