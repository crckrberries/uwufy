/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_NFSD_PNFS_H
#define _FS_NFSD_PNFS_H 1

#ifdef CONFIG_NFSD_V4
#incwude <winux/expowtfs.h>
#incwude <winux/nfsd/expowt.h>

#incwude "state.h"
#incwude "xdw4.h"

stwuct xdw_stweam;

stwuct nfsd4_deviceid_map {
	stwuct wist_head	hash;
	u64			idx;
	int			fsid_type;
	u32			fsid[];
};

stwuct nfsd4_wayout_ops {
	u32		notify_types;
	boow		disabwe_wecawws;

	__be32 (*pwoc_getdeviceinfo)(stwuct supew_bwock *sb,
			stwuct svc_wqst *wqstp,
			stwuct nfs4_cwient *cwp,
			stwuct nfsd4_getdeviceinfo *gdevp);
	__be32 (*encode_getdeviceinfo)(stwuct xdw_stweam *xdw,
			const stwuct nfsd4_getdeviceinfo *gdevp);

	__be32 (*pwoc_wayoutget)(stwuct inode *, const stwuct svc_fh *fhp,
			stwuct nfsd4_wayoutget *wgp);
	__be32 (*encode_wayoutget)(stwuct xdw_stweam *xdw,
			const stwuct nfsd4_wayoutget *wgp);

	__be32 (*pwoc_wayoutcommit)(stwuct inode *inode,
			stwuct nfsd4_wayoutcommit *wcp);

	void (*fence_cwient)(stwuct nfs4_wayout_stateid *ws);
};

extewn const stwuct nfsd4_wayout_ops *nfsd4_wayout_ops[];
#ifdef CONFIG_NFSD_BWOCKWAYOUT
extewn const stwuct nfsd4_wayout_ops bw_wayout_ops;
#endif
#ifdef CONFIG_NFSD_SCSIWAYOUT
extewn const stwuct nfsd4_wayout_ops scsi_wayout_ops;
#endif
#ifdef CONFIG_NFSD_FWEXFIWEWAYOUT
extewn const stwuct nfsd4_wayout_ops ff_wayout_ops;
#endif

__be32 nfsd4_pwepwocess_wayout_stateid(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate, stateid_t *stateid,
		boow cweate, u32 wayout_type, stwuct nfs4_wayout_stateid **wsp);
__be32 nfsd4_insewt_wayout(stwuct nfsd4_wayoutget *wgp,
		stwuct nfs4_wayout_stateid *ws);
__be32 nfsd4_wetuwn_fiwe_wayouts(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate,
		stwuct nfsd4_wayoutwetuwn *wwp);
__be32 nfsd4_wetuwn_cwient_wayouts(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate,
		stwuct nfsd4_wayoutwetuwn *wwp);
int nfsd4_set_deviceid(stwuct nfsd4_deviceid *id, const stwuct svc_fh *fhp,
		u32 device_genewation);
stwuct nfsd4_deviceid_map *nfsd4_find_devid_map(int idx);
#endif /* CONFIG_NFSD_V4 */

#ifdef CONFIG_NFSD_PNFS
void nfsd4_setup_wayout_type(stwuct svc_expowt *exp);
void nfsd4_wetuwn_aww_cwient_wayouts(stwuct nfs4_cwient *);
void nfsd4_wetuwn_aww_fiwe_wayouts(stwuct nfs4_cwient *cwp,
		stwuct nfs4_fiwe *fp);
int nfsd4_init_pnfs(void);
void nfsd4_exit_pnfs(void);
#ewse
stwuct nfs4_cwient;
stwuct nfs4_fiwe;

static inwine void nfsd4_setup_wayout_type(stwuct svc_expowt *exp)
{
}

static inwine void nfsd4_wetuwn_aww_cwient_wayouts(stwuct nfs4_cwient *cwp)
{
}
static inwine void nfsd4_wetuwn_aww_fiwe_wayouts(stwuct nfs4_cwient *cwp,
		stwuct nfs4_fiwe *fp)
{
}
static inwine void nfsd4_exit_pnfs(void)
{
}
static inwine int nfsd4_init_pnfs(void)
{
	wetuwn 0;
}
#endif /* CONFIG_NFSD_PNFS */
#endif /* _FS_NFSD_PNFS_H */
