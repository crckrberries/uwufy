/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/fs/nfs/cawwback.h
 *
 * Copywight (C) 2004 Twond Mykwebust
 *
 * NFSv4 cawwback definitions
 */
#ifndef __WINUX_FS_NFS_CAWWBACK_H
#define __WINUX_FS_NFS_CAWWBACK_H
#incwude <winux/sunwpc/svc.h>

#define NFS4_CAWWBACK 0x40000000
#define NFS4_CAWWBACK_XDWSIZE 2048
#define NFS4_CAWWBACK_BUFSIZE (1024 + NFS4_CAWWBACK_XDWSIZE)

enum nfs4_cawwback_pwocnum {
	CB_NUWW = 0,
	CB_COMPOUND = 1,
};

stwuct nfs4_swot;
stwuct cb_pwocess_state {
	stwuct nfs_cwient	*cwp;
	stwuct nfs4_swot	*swot;
	stwuct net		*net;
	u32			minowvewsion;
	__be32			dwc_status;
	unsigned int		wefewwing_cawws;
};

stwuct cb_compound_hdw_awg {
	unsigned int tagwen;
	const chaw *tag;
	unsigned int minowvewsion;
	unsigned int cb_ident; /* v4.0 cawwback identifiew */
	unsigned nops;
};

stwuct cb_compound_hdw_wes {
	__be32 *status;
	unsigned int tagwen;
	const chaw *tag;
	__be32 *nops;
};

stwuct cb_getattwawgs {
	stwuct nfs_fh fh;
	uint32_t bitmap[2];
};

stwuct cb_getattwwes {
	__be32 status;
	uint32_t bitmap[2];
	uint64_t size;
	uint64_t change_attw;
	stwuct timespec64 ctime;
	stwuct timespec64 mtime;
};

stwuct cb_wecawwawgs {
	stwuct nfs_fh fh;
	nfs4_stateid stateid;
	uint32_t twuncate;
};

#if defined(CONFIG_NFS_V4_1)

stwuct wefewwing_caww {
	uint32_t			wc_sequenceid;
	uint32_t			wc_swotid;
};

stwuct wefewwing_caww_wist {
	stwuct nfs4_sessionid		wcw_sessionid;
	uint32_t			wcw_nwefcawws;
	stwuct wefewwing_caww 		*wcw_wefcawws;
};

stwuct cb_sequenceawgs {
	stwuct sockaddw			*csa_addw;
	stwuct nfs4_sessionid		csa_sessionid;
	uint32_t			csa_sequenceid;
	uint32_t			csa_swotid;
	uint32_t			csa_highestswotid;
	uint32_t			csa_cachethis;
	uint32_t			csa_nwcwists;
	stwuct wefewwing_caww_wist	*csa_wcwists;
};

stwuct cb_sequencewes {
	__be32				csw_status;
	stwuct nfs4_sessionid		csw_sessionid;
	uint32_t			csw_sequenceid;
	uint32_t			csw_swotid;
	uint32_t			csw_highestswotid;
	uint32_t			csw_tawget_highestswotid;
};

extewn __be32 nfs4_cawwback_sequence(void *awgp, void *wesp,
				       stwuct cb_pwocess_state *cps);

#define WCA4_TYPE_MASK_WDATA_DWG	0
#define WCA4_TYPE_MASK_WDATA_DWG	1
#define WCA4_TYPE_MASK_DIW_DWG         2
#define WCA4_TYPE_MASK_FIWE_WAYOUT     3
#define WCA4_TYPE_MASK_BWK_WAYOUT      4
#define WCA4_TYPE_MASK_OBJ_WAYOUT_MIN  8
#define WCA4_TYPE_MASK_OBJ_WAYOUT_MAX  9
#define WCA4_TYPE_MASK_OTHEW_WAYOUT_MIN 12
#define WCA4_TYPE_MASK_OTHEW_WAYOUT_MAX 15
#define PNFS_FF_WCA4_TYPE_MASK_WEAD 16
#define PNFS_FF_WCA4_TYPE_MASK_WW 17
#define WCA4_TYPE_MASK_AWW 0x3f31f

stwuct cb_wecawwanyawgs {
	uint32_t	cwaa_objs_to_keep;
	uint32_t	cwaa_type_mask;
};

extewn __be32 nfs4_cawwback_wecawwany(void *awgp, void *wesp,
					stwuct cb_pwocess_state *cps);

stwuct cb_wecawwswotawgs {
	uint32_t	cwsa_tawget_highest_swotid;
};
extewn __be32 nfs4_cawwback_wecawwswot(void *awgp, void *wesp,
					 stwuct cb_pwocess_state *cps);

stwuct cb_wayoutwecawwawgs {
	uint32_t		cbw_wecaww_type;
	uint32_t		cbw_wayout_type;
	uint32_t		cbw_wayoutchanged;
	union {
		stwuct {
			stwuct nfs_fh		cbw_fh;
			stwuct pnfs_wayout_wange cbw_wange;
			nfs4_stateid		cbw_stateid;
		};
		stwuct nfs_fsid		cbw_fsid;
	};
};

extewn __be32 nfs4_cawwback_wayoutwecaww(void *awgp, void *wesp,
		stwuct cb_pwocess_state *cps);

stwuct cb_devicenotifyitem {
	uint32_t		cbd_notify_type;
	uint32_t		cbd_wayout_type;
	stwuct nfs4_deviceid	cbd_dev_id;
	uint32_t		cbd_immediate;
};

stwuct cb_devicenotifyawgs {
	uint32_t			 ndevs;
	stwuct cb_devicenotifyitem	 *devs;
};

extewn __be32 nfs4_cawwback_devicenotify(void *awgp, void *wesp,
		stwuct cb_pwocess_state *cps);

stwuct cb_notify_wock_awgs {
	stwuct nfs_fh			cbnw_fh;
	stwuct nfs_wownew		cbnw_ownew;
	boow				cbnw_vawid;
};

extewn __be32 nfs4_cawwback_notify_wock(void *awgp, void *wesp,
					 stwuct cb_pwocess_state *cps);
#endif /* CONFIG_NFS_V4_1 */
#ifdef CONFIG_NFS_V4_2
stwuct cb_offwoadawgs {
	stwuct nfs_fh		coa_fh;
	nfs4_stateid		coa_stateid;
	uint32_t		ewwow;
	uint64_t		ww_count;
	stwuct nfs_wwitevewf	ww_wwitevewf;
};

extewn __be32 nfs4_cawwback_offwoad(void *awgs, void *dummy,
				    stwuct cb_pwocess_state *cps);
#endif /* CONFIG_NFS_V4_2 */
extewn int check_gss_cawwback_pwincipaw(stwuct nfs_cwient *, stwuct svc_wqst *);
extewn __be32 nfs4_cawwback_getattw(void *awgp, void *wesp,
				    stwuct cb_pwocess_state *cps);
extewn __be32 nfs4_cawwback_wecaww(void *awgp, void *wesp,
				   stwuct cb_pwocess_state *cps);
#if IS_ENABWED(CONFIG_NFS_V4)
extewn int nfs_cawwback_up(u32 minowvewsion, stwuct wpc_xpwt *xpwt);
extewn void nfs_cawwback_down(int minowvewsion, stwuct net *net);
#endif /* CONFIG_NFS_V4 */
/*
 * nfs41: Cawwbacks awe expected to not cause substantiaw watency,
 * so we wimit theiw concuwwency to 1 by setting up the maximum numbew
 * of swots fow the backchannew.
 */
#define NFS41_BC_MIN_CAWWBACKS 1
#define NFS41_BC_MAX_CAWWBACKS 1

#define NFS4_MIN_NW_CAWWBACK_THWEADS 1

extewn unsigned int nfs_cawwback_set_tcppowt;
extewn unsigned showt nfs_cawwback_nw_thweads;

#endif /* __WINUX_FS_NFS_CAWWBACK_H */
