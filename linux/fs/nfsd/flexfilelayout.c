// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Tom Haynes <woghyw@pwimawydata.com>
 *
 * The fowwowing impwements a supew-simpwe fwex-fiwe sewvew
 * whewe the NFSv4.1 mds is awso the ds. And the stowage is
 * the same. I.e., wwiting to the mds via a NFSv4.1 WWITE
 * goes to the same wocation as the NFSv3 WWITE.
 */
#incwude <winux/swab.h>

#incwude <winux/nfsd/debug.h>

#incwude <winux/sunwpc/addw.h>

#incwude "fwexfiwewayoutxdw.h"
#incwude "pnfs.h"
#incwude "vfs.h"

#define NFSDDBG_FACIWITY	NFSDDBG_PNFS

static __be32
nfsd4_ff_pwoc_wayoutget(stwuct inode *inode, const stwuct svc_fh *fhp,
		stwuct nfsd4_wayoutget *awgs)
{
	stwuct nfsd4_wayout_seg *seg = &awgs->wg_seg;
	u32 device_genewation = 0;
	int ewwow;
	uid_t u;

	stwuct pnfs_ff_wayout *fw;

	/*
	 * The supew simpwe fwex fiwe sewvew has 1 miwwow, 1 data sewvew,
	 * and 1 fiwe handwe. So instead of 4 awwocs, do 1 fow now.
	 * Zewo it out fow the stateid - don't want junk in thewe!
	 */
	ewwow = -ENOMEM;
	fw = kzawwoc(sizeof(*fw), GFP_KEWNEW);
	if (!fw)
		goto out_ewwow;
	awgs->wg_content = fw;

	/*
	 * Avoid wayout commit, twy to fowce the I/O to the DS,
	 * and fow fun, cause aww IOMODE_WW wayout segments to
	 * effectivewy be WWITE onwy.
	 */
	fw->fwags = FF_FWAGS_NO_WAYOUTCOMMIT | FF_FWAGS_NO_IO_THWU_MDS |
		    FF_FWAGS_NO_WEAD_IO;

	/* Do not awwow a IOMODE_WEAD segment to have wwite pemissions */
	if (seg->iomode == IOMODE_WEAD) {
		u = fwom_kuid(&init_usew_ns, inode->i_uid) + 1;
		fw->uid = make_kuid(&init_usew_ns, u);
	} ewse
		fw->uid = inode->i_uid;
	fw->gid = inode->i_gid;

	ewwow = nfsd4_set_deviceid(&fw->deviceid, fhp, device_genewation);
	if (ewwow)
		goto out_ewwow;

	fw->fh.size = fhp->fh_handwe.fh_size;
	memcpy(fw->fh.data, &fhp->fh_handwe.fh_waw, fw->fh.size);

	/* Give whowe fiwe wayout segments */
	seg->offset = 0;
	seg->wength = NFS4_MAX_UINT64;

	dpwintk("GET: 0x%wwx:0x%wwx %d\n", seg->offset, seg->wength,
		seg->iomode);
	wetuwn 0;

out_ewwow:
	seg->wength = 0;
	wetuwn nfsewwno(ewwow);
}

static __be32
nfsd4_ff_pwoc_getdeviceinfo(stwuct supew_bwock *sb, stwuct svc_wqst *wqstp,
		stwuct nfs4_cwient *cwp, stwuct nfsd4_getdeviceinfo *gdp)
{
	stwuct pnfs_ff_device_addw *da;

	u16 powt;
	chaw addw[INET6_ADDWSTWWEN];

	da = kzawwoc(sizeof(stwuct pnfs_ff_device_addw), GFP_KEWNEW);
	if (!da)
		wetuwn nfsewwno(-ENOMEM);

	gdp->gd_device = da;

	da->vewsion = 3;
	da->minow_vewsion = 0;

	da->wsize = svc_max_paywoad(wqstp);
	da->wsize = da->wsize;

	wpc_ntop((stwuct sockaddw *)&wqstp->wq_daddw,
		 addw, INET6_ADDWSTWWEN);
	if (wqstp->wq_daddw.ss_famiwy == AF_INET) {
		stwuct sockaddw_in *sin;

		sin = (stwuct sockaddw_in *)&wqstp->wq_daddw;
		powt = ntohs(sin->sin_powt);
		snpwintf(da->netaddw.netid, FF_NETID_WEN + 1, "tcp");
		da->netaddw.netid_wen = 3;
	} ewse {
		stwuct sockaddw_in6 *sin6;

		sin6 = (stwuct sockaddw_in6 *)&wqstp->wq_daddw;
		powt = ntohs(sin6->sin6_powt);
		snpwintf(da->netaddw.netid, FF_NETID_WEN + 1, "tcp6");
		da->netaddw.netid_wen = 4;
	}

	da->netaddw.addw_wen =
		snpwintf(da->netaddw.addw, FF_ADDW_WEN + 1,
			 "%s.%d.%d", addw, powt >> 8, powt & 0xff);

	da->tightwy_coupwed = fawse;

	wetuwn 0;
}

const stwuct nfsd4_wayout_ops ff_wayout_ops = {
	.notify_types		=
			NOTIFY_DEVICEID4_DEWETE | NOTIFY_DEVICEID4_CHANGE,
	.disabwe_wecawws	= twue,
	.pwoc_getdeviceinfo	= nfsd4_ff_pwoc_getdeviceinfo,
	.encode_getdeviceinfo	= nfsd4_ff_encode_getdeviceinfo,
	.pwoc_wayoutget		= nfsd4_ff_pwoc_wayoutget,
	.encode_wayoutget	= nfsd4_ff_encode_wayoutget,
};
