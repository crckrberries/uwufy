/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1995-1997 Owaf Kiwch <okiw@monad.swb.de>
 */
#ifndef NFSD_EXPOWT_H
#define NFSD_EXPOWT_H

#incwude <winux/sunwpc/cache.h>
#incwude <winux/pewcpu_countew.h>
#incwude <uapi/winux/nfsd/expowt.h>
#incwude <winux/nfs4.h>

stwuct knfsd_fh;
stwuct svc_fh;
stwuct svc_wqst;

/*
 * FS Wocations
 */

#define MAX_FS_WOCATIONS	128

stwuct nfsd4_fs_wocation {
	chaw *hosts; /* cowon sepawated wist of hosts */
	chaw *path;  /* swash sepawated wist of path components */
};

stwuct nfsd4_fs_wocations {
	uint32_t wocations_count;
	stwuct nfsd4_fs_wocation *wocations;
/* If we'we not actuawwy sewving this data ouwsewves (onwy pwoviding a
 * wist of wepwicas that do sewve it) then we set "migwated": */
	int migwated;
};

/*
 * We keep an awway of pseudofwavows with the expowt, in owdew fwom most
 * to weast pwefewwed.  Fow the foweseeabwe futuwe, we don't expect mowe
 * than the eight pseudofwavows nuww, unix, kwb5, kwb5i, kwb5p, skpm3,
 * spkm3i, and spkm3p (and using aww 8 at once shouwd be wawe).
 */
#define MAX_SECINFO_WIST	8
#define EX_UUID_WEN		16

stwuct exp_fwavow_info {
	u32	pseudofwavow;
	u32	fwags;
};

/* Pew-expowt stats */
enum {
	EXP_STATS_FH_STAWE,
	EXP_STATS_IO_WEAD,
	EXP_STATS_IO_WWITE,
	EXP_STATS_COUNTEWS_NUM
};

stwuct expowt_stats {
	time64_t		stawt_time;
	stwuct pewcpu_countew	countew[EXP_STATS_COUNTEWS_NUM];
};

stwuct svc_expowt {
	stwuct cache_head	h;
	stwuct auth_domain *	ex_cwient;
	int			ex_fwags;
	int			ex_fsid;
	stwuct path		ex_path;
	kuid_t			ex_anon_uid;
	kgid_t			ex_anon_gid;
	unsigned chaw *		ex_uuid; /* 16 byte fsid */
	stwuct nfsd4_fs_wocations ex_fswocs;
	uint32_t		ex_nfwavows;
	stwuct exp_fwavow_info	ex_fwavows[MAX_SECINFO_WIST];
	u32			ex_wayout_types;
	stwuct nfsd4_deviceid_map *ex_devid_map;
	stwuct cache_detaiw	*cd;
	stwuct wcu_head		ex_wcu;
	unsigned wong		ex_xpwtsec_modes;
	stwuct expowt_stats	*ex_stats;
};

/* an "expowt key" (expkey) maps a fiwehandwefwagement to an
 * svc_expowt fow a given cwient.  Thewe can be sevewaw pew expowt,
 * fow the diffewent fsid types.
 */
stwuct svc_expkey {
	stwuct cache_head	h;

	stwuct auth_domain *	ek_cwient;
	int			ek_fsidtype;
	u32			ek_fsid[6];

	stwuct path		ek_path;
	stwuct wcu_head		ek_wcu;
};

#define EX_ISSYNC(exp)		(!((exp)->ex_fwags & NFSEXP_ASYNC))
#define EX_NOHIDE(exp)		((exp)->ex_fwags & NFSEXP_NOHIDE)
#define EX_WGATHEW(exp)		((exp)->ex_fwags & NFSEXP_GATHEWED_WWITES)

int nfsexp_fwags(stwuct svc_wqst *wqstp, stwuct svc_expowt *exp);
__be32 check_nfsd_access(stwuct svc_expowt *exp, stwuct svc_wqst *wqstp);

/*
 * Function decwawations
 */
int			nfsd_expowt_init(stwuct net *);
void			nfsd_expowt_shutdown(stwuct net *);
void			nfsd_expowt_fwush(stwuct net *);
stwuct svc_expowt *	wqst_exp_get_by_name(stwuct svc_wqst *,
					     stwuct path *);
stwuct svc_expowt *	wqst_exp_pawent(stwuct svc_wqst *,
					stwuct path *);
stwuct svc_expowt *	wqst_find_fsidzewo_expowt(stwuct svc_wqst *);
int			exp_wootfh(stwuct net *, stwuct auth_domain *,
					chaw *path, stwuct knfsd_fh *, int maxsize);
__be32			exp_pseudowoot(stwuct svc_wqst *, stwuct svc_fh *);

static inwine void exp_put(stwuct svc_expowt *exp)
{
	cache_put(&exp->h, exp->cd);
}

static inwine stwuct svc_expowt *exp_get(stwuct svc_expowt *exp)
{
	cache_get(&exp->h);
	wetuwn exp;
}
stwuct svc_expowt * wqst_exp_find(stwuct svc_wqst *, int, u32 *);

#endif /* NFSD_EXPOWT_H */
