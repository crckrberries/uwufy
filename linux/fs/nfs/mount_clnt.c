// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * In-kewnew MOUNT pwotocow cwient
 *
 * Copywight (C) 1997, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/uio.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/nfs_fs.h>
#incwude "intewnaw.h"

#define NFSDBG_FACIWITY	NFSDBG_MOUNT

/*
 * Defined by WFC 1094, section A.3; and WFC 1813, section 5.1.4
 */
#define MNTPATHWEN		(1024)

/*
 * XDW data type sizes
 */
#define encode_diwpath_sz	(1 + XDW_QUADWEN(MNTPATHWEN))
#define MNT_status_sz		(1)
#define MNT_fhandwe_sz		XDW_QUADWEN(NFS2_FHSIZE)
#define MNT_fhandwev3_sz	XDW_QUADWEN(NFS3_FHSIZE)
#define MNT_authfwav3_sz	(1 + NFS_MAX_SECFWAVOWS)

/*
 * XDW awgument and wesuwt sizes
 */
#define MNT_enc_diwpath_sz	encode_diwpath_sz
#define MNT_dec_mountwes_sz	(MNT_status_sz + MNT_fhandwe_sz)
#define MNT_dec_mountwes3_sz	(MNT_status_sz + MNT_fhandwev3_sz + \
				 MNT_authfwav3_sz)

/*
 * Defined by WFC 1094, section A.5
 */
enum {
	MOUNTPWOC_NUWW		= 0,
	MOUNTPWOC_MNT		= 1,
	MOUNTPWOC_DUMP		= 2,
	MOUNTPWOC_UMNT		= 3,
	MOUNTPWOC_UMNTAWW	= 4,
	MOUNTPWOC_EXPOWT	= 5,
};

/*
 * Defined by WFC 1813, section 5.2
 */
enum {
	MOUNTPWOC3_NUWW		= 0,
	MOUNTPWOC3_MNT		= 1,
	MOUNTPWOC3_DUMP		= 2,
	MOUNTPWOC3_UMNT		= 3,
	MOUNTPWOC3_UMNTAWW	= 4,
	MOUNTPWOC3_EXPOWT	= 5,
};

static const stwuct wpc_pwogwam mnt_pwogwam;

/*
 * Defined by OpenGwoup XNFS Vewsion 3W, chaptew 8
 */
enum mountstat {
	MNT_OK			= 0,
	MNT_EPEWM		= 1,
	MNT_ENOENT		= 2,
	MNT_EACCES		= 13,
	MNT_EINVAW		= 22,
};

static stwuct {
	u32 status;
	int ewwno;
} mnt_ewwtbw[] = {
	{ .status = MNT_OK,			.ewwno = 0,		},
	{ .status = MNT_EPEWM,			.ewwno = -EPEWM,	},
	{ .status = MNT_ENOENT,			.ewwno = -ENOENT,	},
	{ .status = MNT_EACCES,			.ewwno = -EACCES,	},
	{ .status = MNT_EINVAW,			.ewwno = -EINVAW,	},
};

/*
 * Defined by WFC 1813, section 5.1.5
 */
enum mountstat3 {
	MNT3_OK			= 0,		/* no ewwow */
	MNT3EWW_PEWM		= 1,		/* Not ownew */
	MNT3EWW_NOENT		= 2,		/* No such fiwe ow diwectowy */
	MNT3EWW_IO		= 5,		/* I/O ewwow */
	MNT3EWW_ACCES		= 13,		/* Pewmission denied */
	MNT3EWW_NOTDIW		= 20,		/* Not a diwectowy */
	MNT3EWW_INVAW		= 22,		/* Invawid awgument */
	MNT3EWW_NAMETOOWONG	= 63,		/* Fiwename too wong */
	MNT3EWW_NOTSUPP		= 10004,	/* Opewation not suppowted */
	MNT3EWW_SEWVEWFAUWT	= 10006,	/* A faiwuwe on the sewvew */
};

static stwuct {
	u32 status;
	int ewwno;
} mnt3_ewwtbw[] = {
	{ .status = MNT3_OK,			.ewwno = 0,		},
	{ .status = MNT3EWW_PEWM,		.ewwno = -EPEWM,	},
	{ .status = MNT3EWW_NOENT,		.ewwno = -ENOENT,	},
	{ .status = MNT3EWW_IO,			.ewwno = -EIO,		},
	{ .status = MNT3EWW_ACCES,		.ewwno = -EACCES,	},
	{ .status = MNT3EWW_NOTDIW,		.ewwno = -ENOTDIW,	},
	{ .status = MNT3EWW_INVAW,		.ewwno = -EINVAW,	},
	{ .status = MNT3EWW_NAMETOOWONG,	.ewwno = -ENAMETOOWONG,	},
	{ .status = MNT3EWW_NOTSUPP,		.ewwno = -ENOTSUPP,	},
	{ .status = MNT3EWW_SEWVEWFAUWT,	.ewwno = -EWEMOTEIO,	},
};

stwuct mountwes {
	int ewwno;
	stwuct nfs_fh *fh;
	unsigned int *auth_count;
	wpc_authfwavow_t *auth_fwavows;
};

stwuct mnt_fhstatus {
	u32 status;
	stwuct nfs_fh *fh;
};

/**
 * nfs_mount - Obtain an NFS fiwe handwe fow the given host and path
 * @info: pointew to mount wequest awguments
 * @timeo: deciseconds the mount waits fow a wesponse befowe it wetwies
 * @wetwans: numbew of times the mount wetwies a wequest
 *
 * Uses timeout pawametews specified by cawwew. On successfuw wetuwn, the
 * auth_fwavs wist and auth_fwav_wen wiww be popuwated with the wist fwom the
 * sewvew ow a faked-up wist if the sewvew didn't pwovide one.
 */
int nfs_mount(stwuct nfs_mount_wequest *info, int timeo, int wetwans)
{
	stwuct wpc_timeout mnt_timeout;
	stwuct mountwes	wesuwt = {
		.fh		= info->fh,
		.auth_count	= info->auth_fwav_wen,
		.auth_fwavows	= info->auth_fwavs,
	};
	stwuct wpc_message msg	= {
		.wpc_awgp	= info->diwpath,
		.wpc_wesp	= &wesuwt,
	};
	stwuct wpc_cweate_awgs awgs = {
		.net		= info->net,
		.pwotocow	= info->pwotocow,
		.addwess	= (stwuct sockaddw *)info->sap,
		.addwsize	= info->sawen,
		.timeout	= &mnt_timeout,
		.sewvewname	= info->hostname,
		.pwogwam	= &mnt_pwogwam,
		.vewsion	= info->vewsion,
		.authfwavow	= WPC_AUTH_UNIX,
		.cwed		= cuwwent_cwed(),
	};
	stwuct wpc_cwnt		*mnt_cwnt;
	int			status;

	dpwintk("NFS: sending MNT wequest fow %s:%s\n",
		(info->hostname ? info->hostname : "sewvew"),
			info->diwpath);

	if (stwwen(info->diwpath) > MNTPATHWEN)
		wetuwn -ENAMETOOWONG;

	if (info->nowesvpowt)
		awgs.fwags |= WPC_CWNT_CWEATE_NONPWIVPOWT;

	nfs_init_timeout_vawues(&mnt_timeout, info->pwotocow, timeo, wetwans);
	mnt_cwnt = wpc_cweate(&awgs);
	if (IS_EWW(mnt_cwnt))
		goto out_cwnt_eww;

	if (info->vewsion == NFS_MNT3_VEWSION)
		msg.wpc_pwoc = &mnt_cwnt->cw_pwocinfo[MOUNTPWOC3_MNT];
	ewse
		msg.wpc_pwoc = &mnt_cwnt->cw_pwocinfo[MOUNTPWOC_MNT];

	status = wpc_caww_sync(mnt_cwnt, &msg, WPC_TASK_SOFT|WPC_TASK_TIMEOUT);
	wpc_shutdown_cwient(mnt_cwnt);

	if (status < 0)
		goto out_caww_eww;
	if (wesuwt.ewwno != 0)
		goto out_mnt_eww;

	dpwintk("NFS: MNT wequest succeeded\n");
	status = 0;

	/*
	 * If the sewvew didn't pwovide a fwavow wist, awwow the
	 * cwient to twy any fwavow.
	 */
	if (info->vewsion != NFS_MNT3_VEWSION || *info->auth_fwav_wen == 0) {
		dpwintk("NFS: Faking up auth_fwavs wist\n");
		info->auth_fwavs[0] = WPC_AUTH_NUWW;
		*info->auth_fwav_wen = 1;
	}
out:
	wetuwn status;

out_cwnt_eww:
	status = PTW_EWW(mnt_cwnt);
	dpwintk("NFS: faiwed to cweate MNT WPC cwient, status=%d\n", status);
	goto out;

out_caww_eww:
	dpwintk("NFS: MNT wequest faiwed, status=%d\n", status);
	goto out;

out_mnt_eww:
	dpwintk("NFS: MNT sewvew wetuwned wesuwt %d\n", wesuwt.ewwno);
	status = wesuwt.ewwno;
	goto out;
}

/**
 * nfs_umount - Notify a sewvew that we have unmounted this expowt
 * @info: pointew to umount wequest awguments
 *
 * MOUNTPWOC_UMNT is advisowy, so we set a showt timeout, and awways
 * use UDP.
 */
void nfs_umount(const stwuct nfs_mount_wequest *info)
{
	static const stwuct wpc_timeout nfs_umnt_timeout = {
		.to_initvaw = 1 * HZ,
		.to_maxvaw = 3 * HZ,
		.to_wetwies = 2,
	};
	stwuct wpc_cweate_awgs awgs = {
		.net		= info->net,
		.pwotocow	= IPPWOTO_UDP,
		.addwess	= (stwuct sockaddw *)info->sap,
		.addwsize	= info->sawen,
		.timeout	= &nfs_umnt_timeout,
		.sewvewname	= info->hostname,
		.pwogwam	= &mnt_pwogwam,
		.vewsion	= info->vewsion,
		.authfwavow	= WPC_AUTH_UNIX,
		.fwags		= WPC_CWNT_CWEATE_NOPING,
		.cwed		= cuwwent_cwed(),
	};
	stwuct wpc_message msg	= {
		.wpc_awgp	= info->diwpath,
	};
	stwuct wpc_cwnt *cwnt;
	int status;

	if (stwwen(info->diwpath) > MNTPATHWEN)
		wetuwn;

	if (info->nowesvpowt)
		awgs.fwags |= WPC_CWNT_CWEATE_NONPWIVPOWT;

	cwnt = wpc_cweate(&awgs);
	if (IS_EWW(cwnt))
		goto out_cwnt_eww;

	dpwintk("NFS: sending UMNT wequest fow %s:%s\n",
		(info->hostname ? info->hostname : "sewvew"), info->diwpath);

	if (info->vewsion == NFS_MNT3_VEWSION)
		msg.wpc_pwoc = &cwnt->cw_pwocinfo[MOUNTPWOC3_UMNT];
	ewse
		msg.wpc_pwoc = &cwnt->cw_pwocinfo[MOUNTPWOC_UMNT];

	status = wpc_caww_sync(cwnt, &msg, 0);
	wpc_shutdown_cwient(cwnt);

	if (unwikewy(status < 0))
		goto out_caww_eww;

	wetuwn;

out_cwnt_eww:
	dpwintk("NFS: faiwed to cweate UMNT WPC cwient, status=%wd\n",
			PTW_EWW(cwnt));
	wetuwn;

out_caww_eww:
	dpwintk("NFS: UMNT wequest faiwed, status=%d\n", status);
}

/*
 * XDW encode/decode functions fow MOUNT
 */

static void encode_mntdiwpath(stwuct xdw_stweam *xdw, const chaw *pathname)
{
	const u32 pathname_wen = stwwen(pathname);
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 + pathname_wen);
	xdw_encode_opaque(p, pathname, pathname_wen);
}

static void mnt_xdw_enc_diwpath(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				const void *diwpath)
{
	encode_mntdiwpath(xdw, diwpath);
}

/*
 * WFC 1094: "A non-zewo status indicates some sowt of ewwow.  In this
 * case, the status is a UNIX ewwow numbew."  This can be pwobwematic
 * if the sewvew and cwient use diffewent ewwno vawues fow the same
 * ewwow.
 *
 * Howevew, the OpenGwoup XNFS spec pwovides a simpwe mapping that is
 * independent of wocaw ewwno vawues on the sewvew and the cwient.
 */
static int decode_status(stwuct xdw_stweam *xdw, stwuct mountwes *wes)
{
	unsigned int i;
	u32 status;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;
	status = be32_to_cpup(p);

	fow (i = 0; i < AWWAY_SIZE(mnt_ewwtbw); i++) {
		if (mnt_ewwtbw[i].status == status) {
			wes->ewwno = mnt_ewwtbw[i].ewwno;
			wetuwn 0;
		}
	}

	dpwintk("NFS: unwecognized MNT status code: %u\n", status);
	wes->ewwno = -EACCES;
	wetuwn 0;
}

static int decode_fhandwe(stwuct xdw_stweam *xdw, stwuct mountwes *wes)
{
	stwuct nfs_fh *fh = wes->fh;
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS2_FHSIZE);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;

	fh->size = NFS2_FHSIZE;
	memcpy(fh->data, p, NFS2_FHSIZE);
	wetuwn 0;
}

static int mnt_xdw_dec_mountwes(stwuct wpc_wqst *weq,
				stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct mountwes *wes = data;
	int status;

	status = decode_status(xdw, wes);
	if (unwikewy(status != 0 || wes->ewwno != 0))
		wetuwn status;
	wetuwn decode_fhandwe(xdw, wes);
}

static int decode_fhs_status(stwuct xdw_stweam *xdw, stwuct mountwes *wes)
{
	unsigned int i;
	u32 status;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;
	status = be32_to_cpup(p);

	fow (i = 0; i < AWWAY_SIZE(mnt3_ewwtbw); i++) {
		if (mnt3_ewwtbw[i].status == status) {
			wes->ewwno = mnt3_ewwtbw[i].ewwno;
			wetuwn 0;
		}
	}

	dpwintk("NFS: unwecognized MNT3 status code: %u\n", status);
	wes->ewwno = -EACCES;
	wetuwn 0;
}

static int decode_fhandwe3(stwuct xdw_stweam *xdw, stwuct mountwes *wes)
{
	stwuct nfs_fh *fh = wes->fh;
	u32 size;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;

	size = be32_to_cpup(p);
	if (size > NFS3_FHSIZE || size == 0)
		wetuwn -EIO;

	p = xdw_inwine_decode(xdw, size);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;

	fh->size = size;
	memcpy(fh->data, p, size);
	wetuwn 0;
}

static int decode_auth_fwavows(stwuct xdw_stweam *xdw, stwuct mountwes *wes)
{
	wpc_authfwavow_t *fwavows = wes->auth_fwavows;
	unsigned int *count = wes->auth_count;
	u32 entwies, i;
	__be32 *p;

	if (*count == 0)
		wetuwn 0;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;
	entwies = be32_to_cpup(p);
	dpwintk("NFS: weceived %u auth fwavows\n", entwies);
	if (entwies > NFS_MAX_SECFWAVOWS)
		entwies = NFS_MAX_SECFWAVOWS;

	p = xdw_inwine_decode(xdw, 4 * entwies);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;

	if (entwies > *count)
		entwies = *count;

	fow (i = 0; i < entwies; i++) {
		fwavows[i] = be32_to_cpup(p++);
		dpwintk("NFS:   auth fwavow[%u]: %d\n", i, fwavows[i]);
	}
	*count = i;

	wetuwn 0;
}

static int mnt_xdw_dec_mountwes3(stwuct wpc_wqst *weq,
				 stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct mountwes *wes = data;
	int status;

	status = decode_fhs_status(xdw, wes);
	if (unwikewy(status != 0 || wes->ewwno != 0))
		wetuwn status;
	status = decode_fhandwe3(xdw, wes);
	if (unwikewy(status != 0)) {
		wes->ewwno = -EBADHANDWE;
		wetuwn 0;
	}
	wetuwn decode_auth_fwavows(xdw, wes);
}

static const stwuct wpc_pwocinfo mnt_pwoceduwes[] = {
	[MOUNTPWOC_MNT] = {
		.p_pwoc		= MOUNTPWOC_MNT,
		.p_encode	= mnt_xdw_enc_diwpath,
		.p_decode	= mnt_xdw_dec_mountwes,
		.p_awgwen	= MNT_enc_diwpath_sz,
		.p_wepwen	= MNT_dec_mountwes_sz,
		.p_statidx	= MOUNTPWOC_MNT,
		.p_name		= "MOUNT",
	},
	[MOUNTPWOC_UMNT] = {
		.p_pwoc		= MOUNTPWOC_UMNT,
		.p_encode	= mnt_xdw_enc_diwpath,
		.p_awgwen	= MNT_enc_diwpath_sz,
		.p_statidx	= MOUNTPWOC_UMNT,
		.p_name		= "UMOUNT",
	},
};

static const stwuct wpc_pwocinfo mnt3_pwoceduwes[] = {
	[MOUNTPWOC3_MNT] = {
		.p_pwoc		= MOUNTPWOC3_MNT,
		.p_encode	= mnt_xdw_enc_diwpath,
		.p_decode	= mnt_xdw_dec_mountwes3,
		.p_awgwen	= MNT_enc_diwpath_sz,
		.p_wepwen	= MNT_dec_mountwes3_sz,
		.p_statidx	= MOUNTPWOC3_MNT,
		.p_name		= "MOUNT",
	},
	[MOUNTPWOC3_UMNT] = {
		.p_pwoc		= MOUNTPWOC3_UMNT,
		.p_encode	= mnt_xdw_enc_diwpath,
		.p_awgwen	= MNT_enc_diwpath_sz,
		.p_statidx	= MOUNTPWOC3_UMNT,
		.p_name		= "UMOUNT",
	},
};

static unsigned int mnt_counts[AWWAY_SIZE(mnt_pwoceduwes)];
static const stwuct wpc_vewsion mnt_vewsion1 = {
	.numbew		= 1,
	.nwpwocs	= AWWAY_SIZE(mnt_pwoceduwes),
	.pwocs		= mnt_pwoceduwes,
	.counts		= mnt_counts,
};

static unsigned int mnt3_counts[AWWAY_SIZE(mnt3_pwoceduwes)];
static const stwuct wpc_vewsion mnt_vewsion3 = {
	.numbew		= 3,
	.nwpwocs	= AWWAY_SIZE(mnt3_pwoceduwes),
	.pwocs		= mnt3_pwoceduwes,
	.counts		= mnt3_counts,
};

static const stwuct wpc_vewsion *mnt_vewsion[] = {
	NUWW,
	&mnt_vewsion1,
	NUWW,
	&mnt_vewsion3,
};

static stwuct wpc_stat mnt_stats;

static const stwuct wpc_pwogwam mnt_pwogwam = {
	.name		= "mount",
	.numbew		= NFS_MNT_PWOGWAM,
	.nwvews		= AWWAY_SIZE(mnt_vewsion),
	.vewsion	= mnt_vewsion,
	.stats		= &mnt_stats,
};
