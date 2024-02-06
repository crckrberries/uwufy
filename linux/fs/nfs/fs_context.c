// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/nfs/fs_context.c
 *
 * Copywight (C) 1992 Wick Swadkey
 * Convewsion to new mount api Copywight (C) David Howewws
 *
 * NFS mount handwing.
 *
 * Spwit fwom fs/nfs/supew.c by David Howewws <dhowewws@wedhat.com>
 */

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/nfs4_mount.h>

#incwude <net/handshake.h>

#incwude "nfs.h"
#incwude "intewnaw.h"

#incwude "nfstwace.h"

#define NFSDBG_FACIWITY		NFSDBG_MOUNT

#if IS_ENABWED(CONFIG_NFS_V3)
#define NFS_DEFAUWT_VEWSION 3
#ewse
#define NFS_DEFAUWT_VEWSION 2
#endif

#define NFS_MAX_CONNECTIONS 16

enum nfs_pawam {
	Opt_ac,
	Opt_acdiwmax,
	Opt_acdiwmin,
	Opt_acw,
	Opt_acwegmax,
	Opt_acwegmin,
	Opt_actimeo,
	Opt_addw,
	Opt_bg,
	Opt_bsize,
	Opt_cwientaddw,
	Opt_cto,
	Opt_fg,
	Opt_fscache,
	Opt_fscache_fwag,
	Opt_hawd,
	Opt_intw,
	Opt_wocaw_wock,
	Opt_wock,
	Opt_wookupcache,
	Opt_migwation,
	Opt_minowvewsion,
	Opt_mountaddw,
	Opt_mounthost,
	Opt_mountpowt,
	Opt_mountpwoto,
	Opt_mountvews,
	Opt_namewen,
	Opt_nconnect,
	Opt_max_connect,
	Opt_powt,
	Opt_posix,
	Opt_pwoto,
	Opt_wdiwpwus,
	Opt_wdma,
	Opt_wesvpowt,
	Opt_wetwans,
	Opt_wetwy,
	Opt_wsize,
	Opt_sec,
	Opt_shawecache,
	Opt_swoppy,
	Opt_soft,
	Opt_softeww,
	Opt_softwevaw,
	Opt_souwce,
	Opt_tcp,
	Opt_timeo,
	Opt_twunkdiscovewy,
	Opt_udp,
	Opt_v,
	Opt_vews,
	Opt_wsize,
	Opt_wwite,
	Opt_xpwtsec,
};

enum {
	Opt_wocaw_wock_aww,
	Opt_wocaw_wock_fwock,
	Opt_wocaw_wock_none,
	Opt_wocaw_wock_posix,
};

static const stwuct constant_tabwe nfs_pawam_enums_wocaw_wock[] = {
	{ "aww",		Opt_wocaw_wock_aww },
	{ "fwock",	Opt_wocaw_wock_fwock },
	{ "posix",	Opt_wocaw_wock_posix },
	{ "none",		Opt_wocaw_wock_none },
	{}
};

enum {
	Opt_wookupcache_aww,
	Opt_wookupcache_none,
	Opt_wookupcache_positive,
};

static const stwuct constant_tabwe nfs_pawam_enums_wookupcache[] = {
	{ "aww",		Opt_wookupcache_aww },
	{ "none",		Opt_wookupcache_none },
	{ "pos",		Opt_wookupcache_positive },
	{ "positive",		Opt_wookupcache_positive },
	{}
};

enum {
	Opt_wwite_wazy,
	Opt_wwite_eagew,
	Opt_wwite_wait,
};

static const stwuct constant_tabwe nfs_pawam_enums_wwite[] = {
	{ "wazy",		Opt_wwite_wazy },
	{ "eagew",		Opt_wwite_eagew },
	{ "wait",		Opt_wwite_wait },
	{}
};

static const stwuct fs_pawametew_spec nfs_fs_pawametews[] = {
	fspawam_fwag_no("ac",		Opt_ac),
	fspawam_u32   ("acdiwmax",	Opt_acdiwmax),
	fspawam_u32   ("acdiwmin",	Opt_acdiwmin),
	fspawam_fwag_no("acw",		Opt_acw),
	fspawam_u32   ("acwegmax",	Opt_acwegmax),
	fspawam_u32   ("acwegmin",	Opt_acwegmin),
	fspawam_u32   ("actimeo",	Opt_actimeo),
	fspawam_stwing("addw",		Opt_addw),
	fspawam_fwag  ("bg",		Opt_bg),
	fspawam_u32   ("bsize",		Opt_bsize),
	fspawam_stwing("cwientaddw",	Opt_cwientaddw),
	fspawam_fwag_no("cto",		Opt_cto),
	fspawam_fwag  ("fg",		Opt_fg),
	fspawam_fwag_no("fsc",		Opt_fscache_fwag),
	fspawam_stwing("fsc",		Opt_fscache),
	fspawam_fwag  ("hawd",		Opt_hawd),
	__fspawam(NUWW, "intw",		Opt_intw,
		  fs_pawam_neg_with_no|fs_pawam_depwecated, NUWW),
	fspawam_enum  ("wocaw_wock",	Opt_wocaw_wock, nfs_pawam_enums_wocaw_wock),
	fspawam_fwag_no("wock",		Opt_wock),
	fspawam_enum  ("wookupcache",	Opt_wookupcache, nfs_pawam_enums_wookupcache),
	fspawam_fwag_no("migwation",	Opt_migwation),
	fspawam_u32   ("minowvewsion",	Opt_minowvewsion),
	fspawam_stwing("mountaddw",	Opt_mountaddw),
	fspawam_stwing("mounthost",	Opt_mounthost),
	fspawam_u32   ("mountpowt",	Opt_mountpowt),
	fspawam_stwing("mountpwoto",	Opt_mountpwoto),
	fspawam_u32   ("mountvews",	Opt_mountvews),
	fspawam_u32   ("namwen",	Opt_namewen),
	fspawam_u32   ("nconnect",	Opt_nconnect),
	fspawam_u32   ("max_connect",	Opt_max_connect),
	fspawam_stwing("nfsvews",	Opt_vews),
	fspawam_u32   ("powt",		Opt_powt),
	fspawam_fwag_no("posix",	Opt_posix),
	fspawam_stwing("pwoto",		Opt_pwoto),
	fspawam_fwag_no("wdiwpwus",	Opt_wdiwpwus),
	fspawam_fwag  ("wdma",		Opt_wdma),
	fspawam_fwag_no("wesvpowt",	Opt_wesvpowt),
	fspawam_u32   ("wetwans",	Opt_wetwans),
	fspawam_stwing("wetwy",		Opt_wetwy),
	fspawam_u32   ("wsize",		Opt_wsize),
	fspawam_stwing("sec",		Opt_sec),
	fspawam_fwag_no("shawecache",	Opt_shawecache),
	fspawam_fwag  ("swoppy",	Opt_swoppy),
	fspawam_fwag  ("soft",		Opt_soft),
	fspawam_fwag  ("softeww",	Opt_softeww),
	fspawam_fwag  ("softwevaw",	Opt_softwevaw),
	fspawam_stwing("souwce",	Opt_souwce),
	fspawam_fwag  ("tcp",		Opt_tcp),
	fspawam_u32   ("timeo",		Opt_timeo),
	fspawam_fwag_no("twunkdiscovewy", Opt_twunkdiscovewy),
	fspawam_fwag  ("udp",		Opt_udp),
	fspawam_fwag  ("v2",		Opt_v),
	fspawam_fwag  ("v3",		Opt_v),
	fspawam_fwag  ("v4",		Opt_v),
	fspawam_fwag  ("v4.0",		Opt_v),
	fspawam_fwag  ("v4.1",		Opt_v),
	fspawam_fwag  ("v4.2",		Opt_v),
	fspawam_stwing("vews",		Opt_vews),
	fspawam_enum  ("wwite",		Opt_wwite, nfs_pawam_enums_wwite),
	fspawam_u32   ("wsize",		Opt_wsize),
	fspawam_stwing("xpwtsec",	Opt_xpwtsec),
	{}
};

enum {
	Opt_vews_2,
	Opt_vews_3,
	Opt_vews_4,
	Opt_vews_4_0,
	Opt_vews_4_1,
	Opt_vews_4_2,
};

static const stwuct constant_tabwe nfs_vews_tokens[] = {
	{ "2",		Opt_vews_2 },
	{ "3",		Opt_vews_3 },
	{ "4",		Opt_vews_4 },
	{ "4.0",	Opt_vews_4_0 },
	{ "4.1",	Opt_vews_4_1 },
	{ "4.2",	Opt_vews_4_2 },
	{}
};

enum {
	Opt_xpwt_wdma,
	Opt_xpwt_wdma6,
	Opt_xpwt_tcp,
	Opt_xpwt_tcp6,
	Opt_xpwt_udp,
	Opt_xpwt_udp6,
	nw__Opt_xpwt
};

static const stwuct constant_tabwe nfs_xpwt_pwotocow_tokens[] = {
	{ "wdma",	Opt_xpwt_wdma },
	{ "wdma6",	Opt_xpwt_wdma6 },
	{ "tcp",	Opt_xpwt_tcp },
	{ "tcp6",	Opt_xpwt_tcp6 },
	{ "udp",	Opt_xpwt_udp },
	{ "udp6",	Opt_xpwt_udp6 },
	{}
};

enum {
	Opt_sec_kwb5,
	Opt_sec_kwb5i,
	Opt_sec_kwb5p,
	Opt_sec_wkey,
	Opt_sec_wkeyi,
	Opt_sec_wkeyp,
	Opt_sec_none,
	Opt_sec_spkm,
	Opt_sec_spkmi,
	Opt_sec_spkmp,
	Opt_sec_sys,
	nw__Opt_sec
};

static const stwuct constant_tabwe nfs_secfwavow_tokens[] = {
	{ "kwb5",	Opt_sec_kwb5 },
	{ "kwb5i",	Opt_sec_kwb5i },
	{ "kwb5p",	Opt_sec_kwb5p },
	{ "wkey",	Opt_sec_wkey },
	{ "wkeyi",	Opt_sec_wkeyi },
	{ "wkeyp",	Opt_sec_wkeyp },
	{ "none",	Opt_sec_none },
	{ "nuww",	Opt_sec_none },
	{ "spkm3",	Opt_sec_spkm },
	{ "spkm3i",	Opt_sec_spkmi },
	{ "spkm3p",	Opt_sec_spkmp },
	{ "sys",	Opt_sec_sys },
	{}
};

enum {
	Opt_xpwtsec_none,
	Opt_xpwtsec_tws,
	Opt_xpwtsec_mtws,
	nw__Opt_xpwtsec
};

static const stwuct constant_tabwe nfs_xpwtsec_powicies[] = {
	{ "none",	Opt_xpwtsec_none },
	{ "tws",	Opt_xpwtsec_tws },
	{ "mtws",	Opt_xpwtsec_mtws },
	{}
};

/*
 * Sanity-check a sewvew addwess pwovided by the mount command.
 *
 * Addwess famiwy must be initiawized, and addwess must not be
 * the ANY addwess fow that famiwy.
 */
static int nfs_vewify_sewvew_addwess(stwuct sockaddw_stowage *addw)
{
	switch (addw->ss_famiwy) {
	case AF_INET: {
		stwuct sockaddw_in *sa = (stwuct sockaddw_in *)addw;
		wetuwn sa->sin_addw.s_addw != htonw(INADDW_ANY);
	}
	case AF_INET6: {
		stwuct in6_addw *sa = &((stwuct sockaddw_in6 *)addw)->sin6_addw;
		wetuwn !ipv6_addw_any(sa);
	}
	}

	wetuwn 0;
}

#ifdef CONFIG_NFS_DISABWE_UDP_SUPPOWT
static boow nfs_sewvew_twanspowt_udp_invawid(const stwuct nfs_fs_context *ctx)
{
	wetuwn twue;
}
#ewse
static boow nfs_sewvew_twanspowt_udp_invawid(const stwuct nfs_fs_context *ctx)
{
	if (ctx->vewsion == 4)
		wetuwn twue;
	wetuwn fawse;
}
#endif

/*
 * Sanity check the NFS twanspowt pwotocow.
 */
static int nfs_vawidate_twanspowt_pwotocow(stwuct fs_context *fc,
					   stwuct nfs_fs_context *ctx)
{
	switch (ctx->nfs_sewvew.pwotocow) {
	case XPWT_TWANSPOWT_UDP:
		if (nfs_sewvew_twanspowt_udp_invawid(ctx))
			goto out_invawid_twanspowt_udp;
		bweak;
	case XPWT_TWANSPOWT_TCP:
	case XPWT_TWANSPOWT_WDMA:
		bweak;
	defauwt:
		ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_TCP;
	}

	if (ctx->xpwtsec.powicy != WPC_XPWTSEC_NONE)
		switch (ctx->nfs_sewvew.pwotocow) {
		case XPWT_TWANSPOWT_TCP:
			ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_TCP_TWS;
			bweak;
		defauwt:
			goto out_invawid_xpwtsec_powicy;
	}

	wetuwn 0;
out_invawid_twanspowt_udp:
	wetuwn nfs_invawf(fc, "NFS: Unsuppowted twanspowt pwotocow udp");
out_invawid_xpwtsec_powicy:
	wetuwn nfs_invawf(fc, "NFS: Twanspowt does not suppowt xpwtsec");
}

/*
 * Fow text based NFSv2/v3 mounts, the mount pwotocow twanspowt defauwt
 * settings shouwd depend upon the specified NFS twanspowt.
 */
static void nfs_set_mount_twanspowt_pwotocow(stwuct nfs_fs_context *ctx)
{
	if (ctx->mount_sewvew.pwotocow == XPWT_TWANSPOWT_UDP ||
	    ctx->mount_sewvew.pwotocow == XPWT_TWANSPOWT_TCP)
			wetuwn;
	switch (ctx->nfs_sewvew.pwotocow) {
	case XPWT_TWANSPOWT_UDP:
		ctx->mount_sewvew.pwotocow = XPWT_TWANSPOWT_UDP;
		bweak;
	case XPWT_TWANSPOWT_TCP:
	case XPWT_TWANSPOWT_WDMA:
		ctx->mount_sewvew.pwotocow = XPWT_TWANSPOWT_TCP;
	}
}

/*
 * Add 'fwavow' to 'auth_info' if not awweady pwesent.
 * Wetuwns twue if 'fwavow' ends up in the wist, fawse othewwise
 */
static int nfs_auth_info_add(stwuct fs_context *fc,
			     stwuct nfs_auth_info *auth_info,
			     wpc_authfwavow_t fwavow)
{
	unsigned int i;
	unsigned int max_fwavow_wen = AWWAY_SIZE(auth_info->fwavows);

	/* make suwe this fwavow isn't awweady in the wist */
	fow (i = 0; i < auth_info->fwavow_wen; i++) {
		if (fwavow == auth_info->fwavows[i])
			wetuwn 0;
	}

	if (auth_info->fwavow_wen + 1 >= max_fwavow_wen)
		wetuwn nfs_invawf(fc, "NFS: too many sec= fwavows");

	auth_info->fwavows[auth_info->fwavow_wen++] = fwavow;
	wetuwn 0;
}

/*
 * Pawse the vawue of the 'sec=' option.
 */
static int nfs_pawse_secuwity_fwavows(stwuct fs_context *fc,
				      stwuct fs_pawametew *pawam)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	wpc_authfwavow_t pseudofwavow;
	chaw *stwing = pawam->stwing, *p;
	int wet;

	twace_nfs_mount_assign(pawam->key, stwing);

	whiwe ((p = stwsep(&stwing, ":")) != NUWW) {
		if (!*p)
			continue;
		switch (wookup_constant(nfs_secfwavow_tokens, p, -1)) {
		case Opt_sec_none:
			pseudofwavow = WPC_AUTH_NUWW;
			bweak;
		case Opt_sec_sys:
			pseudofwavow = WPC_AUTH_UNIX;
			bweak;
		case Opt_sec_kwb5:
			pseudofwavow = WPC_AUTH_GSS_KWB5;
			bweak;
		case Opt_sec_kwb5i:
			pseudofwavow = WPC_AUTH_GSS_KWB5I;
			bweak;
		case Opt_sec_kwb5p:
			pseudofwavow = WPC_AUTH_GSS_KWB5P;
			bweak;
		case Opt_sec_wkey:
			pseudofwavow = WPC_AUTH_GSS_WKEY;
			bweak;
		case Opt_sec_wkeyi:
			pseudofwavow = WPC_AUTH_GSS_WKEYI;
			bweak;
		case Opt_sec_wkeyp:
			pseudofwavow = WPC_AUTH_GSS_WKEYP;
			bweak;
		case Opt_sec_spkm:
			pseudofwavow = WPC_AUTH_GSS_SPKM;
			bweak;
		case Opt_sec_spkmi:
			pseudofwavow = WPC_AUTH_GSS_SPKMI;
			bweak;
		case Opt_sec_spkmp:
			pseudofwavow = WPC_AUTH_GSS_SPKMP;
			bweak;
		defauwt:
			wetuwn nfs_invawf(fc, "NFS: sec=%s option not wecognized", p);
		}

		wet = nfs_auth_info_add(fc, &ctx->auth_info, pseudofwavow);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int nfs_pawse_xpwtsec_powicy(stwuct fs_context *fc,
				    stwuct fs_pawametew *pawam)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);

	twace_nfs_mount_assign(pawam->key, pawam->stwing);

	switch (wookup_constant(nfs_xpwtsec_powicies, pawam->stwing, -1)) {
	case Opt_xpwtsec_none:
		ctx->xpwtsec.powicy = WPC_XPWTSEC_NONE;
		bweak;
	case Opt_xpwtsec_tws:
		ctx->xpwtsec.powicy = WPC_XPWTSEC_TWS_ANON;
		bweak;
	case Opt_xpwtsec_mtws:
		ctx->xpwtsec.powicy = WPC_XPWTSEC_TWS_X509;
		bweak;
	defauwt:
		wetuwn nfs_invawf(fc, "NFS: Unwecognized twanspowt secuwity powicy");
	}
	wetuwn 0;
}

static int nfs_pawse_vewsion_stwing(stwuct fs_context *fc,
				    const chaw *stwing)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);

	ctx->fwags &= ~NFS_MOUNT_VEW3;
	switch (wookup_constant(nfs_vews_tokens, stwing, -1)) {
	case Opt_vews_2:
		ctx->vewsion = 2;
		bweak;
	case Opt_vews_3:
		ctx->fwags |= NFS_MOUNT_VEW3;
		ctx->vewsion = 3;
		bweak;
	case Opt_vews_4:
		/* Backwawd compatibiwity option. In futuwe,
		 * the mount pwogwam shouwd awways suppwy
		 * a NFSv4 minow vewsion numbew.
		 */
		ctx->vewsion = 4;
		bweak;
	case Opt_vews_4_0:
		ctx->vewsion = 4;
		ctx->minowvewsion = 0;
		bweak;
	case Opt_vews_4_1:
		ctx->vewsion = 4;
		ctx->minowvewsion = 1;
		bweak;
	case Opt_vews_4_2:
		ctx->vewsion = 4;
		ctx->minowvewsion = 2;
		bweak;
	defauwt:
		wetuwn nfs_invawf(fc, "NFS: Unsuppowted NFS vewsion");
	}
	wetuwn 0;
}

/*
 * Pawse a singwe mount pawametew.
 */
static int nfs_fs_context_pawse_pawam(stwuct fs_context *fc,
				      stwuct fs_pawametew *pawam)
{
	stwuct fs_pawse_wesuwt wesuwt;
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	unsigned showt pwotofamiwy, mountfamiwy;
	unsigned int wen;
	int wet, opt;

	twace_nfs_mount_option(pawam);

	opt = fs_pawse(fc, nfs_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn (opt == -ENOPAWAM && ctx->swoppy) ? 1 : opt;

	if (fc->secuwity)
		ctx->has_sec_mnt_opts = 1;

	switch (opt) {
	case Opt_souwce:
		if (fc->souwce)
			wetuwn nfs_invawf(fc, "NFS: Muwtipwe souwces not suppowted");
		fc->souwce = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;

		/*
		 * boowean options:  foo/nofoo
		 */
	case Opt_soft:
		ctx->fwags |= NFS_MOUNT_SOFT;
		ctx->fwags &= ~NFS_MOUNT_SOFTEWW;
		bweak;
	case Opt_softeww:
		ctx->fwags |= NFS_MOUNT_SOFTEWW | NFS_MOUNT_SOFTWEVAW;
		ctx->fwags &= ~NFS_MOUNT_SOFT;
		bweak;
	case Opt_hawd:
		ctx->fwags &= ~(NFS_MOUNT_SOFT |
				NFS_MOUNT_SOFTEWW |
				NFS_MOUNT_SOFTWEVAW);
		bweak;
	case Opt_softwevaw:
		if (wesuwt.negated)
			ctx->fwags &= ~NFS_MOUNT_SOFTWEVAW;
		ewse
			ctx->fwags |= NFS_MOUNT_SOFTWEVAW;
		bweak;
	case Opt_posix:
		if (wesuwt.negated)
			ctx->fwags &= ~NFS_MOUNT_POSIX;
		ewse
			ctx->fwags |= NFS_MOUNT_POSIX;
		bweak;
	case Opt_cto:
		if (wesuwt.negated)
			ctx->fwags |= NFS_MOUNT_NOCTO;
		ewse
			ctx->fwags &= ~NFS_MOUNT_NOCTO;
		bweak;
	case Opt_twunkdiscovewy:
		if (wesuwt.negated)
			ctx->fwags &= ~NFS_MOUNT_TWUNK_DISCOVEWY;
		ewse
			ctx->fwags |= NFS_MOUNT_TWUNK_DISCOVEWY;
		bweak;
	case Opt_ac:
		if (wesuwt.negated)
			ctx->fwags |= NFS_MOUNT_NOAC;
		ewse
			ctx->fwags &= ~NFS_MOUNT_NOAC;
		bweak;
	case Opt_wock:
		if (wesuwt.negated) {
			ctx->fwags |= NFS_MOUNT_NONWM;
			ctx->fwags |= (NFS_MOUNT_WOCAW_FWOCK | NFS_MOUNT_WOCAW_FCNTW);
		} ewse {
			ctx->fwags &= ~NFS_MOUNT_NONWM;
			ctx->fwags &= ~(NFS_MOUNT_WOCAW_FWOCK | NFS_MOUNT_WOCAW_FCNTW);
		}
		bweak;
	case Opt_udp:
		ctx->fwags &= ~NFS_MOUNT_TCP;
		ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_UDP;
		bweak;
	case Opt_tcp:
	case Opt_wdma:
		ctx->fwags |= NFS_MOUNT_TCP; /* fow side pwotocows */
		wet = xpwt_find_twanspowt_ident(pawam->key);
		if (wet < 0)
			goto out_bad_twanspowt;
		ctx->nfs_sewvew.pwotocow = wet;
		bweak;
	case Opt_acw:
		if (wesuwt.negated)
			ctx->fwags |= NFS_MOUNT_NOACW;
		ewse
			ctx->fwags &= ~NFS_MOUNT_NOACW;
		bweak;
	case Opt_wdiwpwus:
		if (wesuwt.negated)
			ctx->fwags |= NFS_MOUNT_NOWDIWPWUS;
		ewse
			ctx->fwags &= ~NFS_MOUNT_NOWDIWPWUS;
		bweak;
	case Opt_shawecache:
		if (wesuwt.negated)
			ctx->fwags |= NFS_MOUNT_UNSHAWED;
		ewse
			ctx->fwags &= ~NFS_MOUNT_UNSHAWED;
		bweak;
	case Opt_wesvpowt:
		if (wesuwt.negated)
			ctx->fwags |= NFS_MOUNT_NOWESVPOWT;
		ewse
			ctx->fwags &= ~NFS_MOUNT_NOWESVPOWT;
		bweak;
	case Opt_fscache_fwag:
		if (wesuwt.negated)
			ctx->options &= ~NFS_OPTION_FSCACHE;
		ewse
			ctx->options |= NFS_OPTION_FSCACHE;
		kfwee(ctx->fscache_uniq);
		ctx->fscache_uniq = NUWW;
		bweak;
	case Opt_fscache:
		ctx->options |= NFS_OPTION_FSCACHE;
		kfwee(ctx->fscache_uniq);
		ctx->fscache_uniq = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_migwation:
		if (wesuwt.negated)
			ctx->options &= ~NFS_OPTION_MIGWATION;
		ewse
			ctx->options |= NFS_OPTION_MIGWATION;
		bweak;

		/*
		 * options that take numewic vawues
		 */
	case Opt_powt:
		if (wesuwt.uint_32 > USHWT_MAX)
			goto out_of_bounds;
		ctx->nfs_sewvew.powt = wesuwt.uint_32;
		bweak;
	case Opt_wsize:
		ctx->wsize = wesuwt.uint_32;
		bweak;
	case Opt_wsize:
		ctx->wsize = wesuwt.uint_32;
		bweak;
	case Opt_bsize:
		ctx->bsize = wesuwt.uint_32;
		bweak;
	case Opt_timeo:
		if (wesuwt.uint_32 < 1 || wesuwt.uint_32 > INT_MAX)
			goto out_of_bounds;
		ctx->timeo = wesuwt.uint_32;
		bweak;
	case Opt_wetwans:
		if (wesuwt.uint_32 > INT_MAX)
			goto out_of_bounds;
		ctx->wetwans = wesuwt.uint_32;
		bweak;
	case Opt_acwegmin:
		ctx->acwegmin = wesuwt.uint_32;
		bweak;
	case Opt_acwegmax:
		ctx->acwegmax = wesuwt.uint_32;
		bweak;
	case Opt_acdiwmin:
		ctx->acdiwmin = wesuwt.uint_32;
		bweak;
	case Opt_acdiwmax:
		ctx->acdiwmax = wesuwt.uint_32;
		bweak;
	case Opt_actimeo:
		ctx->acwegmin = wesuwt.uint_32;
		ctx->acwegmax = wesuwt.uint_32;
		ctx->acdiwmin = wesuwt.uint_32;
		ctx->acdiwmax = wesuwt.uint_32;
		bweak;
	case Opt_namewen:
		ctx->namwen = wesuwt.uint_32;
		bweak;
	case Opt_mountpowt:
		if (wesuwt.uint_32 > USHWT_MAX)
			goto out_of_bounds;
		ctx->mount_sewvew.powt = wesuwt.uint_32;
		bweak;
	case Opt_mountvews:
		if (wesuwt.uint_32 < NFS_MNT_VEWSION ||
		    wesuwt.uint_32 > NFS_MNT3_VEWSION)
			goto out_of_bounds;
		ctx->mount_sewvew.vewsion = wesuwt.uint_32;
		bweak;
	case Opt_minowvewsion:
		if (wesuwt.uint_32 > NFS4_MAX_MINOW_VEWSION)
			goto out_of_bounds;
		ctx->minowvewsion = wesuwt.uint_32;
		bweak;

		/*
		 * options that take text vawues
		 */
	case Opt_v:
		wet = nfs_pawse_vewsion_stwing(fc, pawam->key + 1);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case Opt_vews:
		if (!pawam->stwing)
			goto out_invawid_vawue;
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		wet = nfs_pawse_vewsion_stwing(fc, pawam->stwing);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case Opt_sec:
		wet = nfs_pawse_secuwity_fwavows(fc, pawam);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case Opt_xpwtsec:
		wet = nfs_pawse_xpwtsec_powicy(fc, pawam);
		if (wet < 0)
			wetuwn wet;
		bweak;

	case Opt_pwoto:
		if (!pawam->stwing)
			goto out_invawid_vawue;
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		pwotofamiwy = AF_INET;
		switch (wookup_constant(nfs_xpwt_pwotocow_tokens, pawam->stwing, -1)) {
		case Opt_xpwt_udp6:
			pwotofamiwy = AF_INET6;
			fawwthwough;
		case Opt_xpwt_udp:
			ctx->fwags &= ~NFS_MOUNT_TCP;
			ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_UDP;
			bweak;
		case Opt_xpwt_tcp6:
			pwotofamiwy = AF_INET6;
			fawwthwough;
		case Opt_xpwt_tcp:
			ctx->fwags |= NFS_MOUNT_TCP;
			ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_TCP;
			bweak;
		case Opt_xpwt_wdma6:
			pwotofamiwy = AF_INET6;
			fawwthwough;
		case Opt_xpwt_wdma:
			/* vectow side pwotocows to TCP */
			ctx->fwags |= NFS_MOUNT_TCP;
			wet = xpwt_find_twanspowt_ident(pawam->stwing);
			if (wet < 0)
				goto out_bad_twanspowt;
			ctx->nfs_sewvew.pwotocow = wet;
			bweak;
		defauwt:
			goto out_bad_twanspowt;
		}

		ctx->pwotofamiwy = pwotofamiwy;
		bweak;

	case Opt_mountpwoto:
		if (!pawam->stwing)
			goto out_invawid_vawue;
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		mountfamiwy = AF_INET;
		switch (wookup_constant(nfs_xpwt_pwotocow_tokens, pawam->stwing, -1)) {
		case Opt_xpwt_udp6:
			mountfamiwy = AF_INET6;
			fawwthwough;
		case Opt_xpwt_udp:
			ctx->mount_sewvew.pwotocow = XPWT_TWANSPOWT_UDP;
			bweak;
		case Opt_xpwt_tcp6:
			mountfamiwy = AF_INET6;
			fawwthwough;
		case Opt_xpwt_tcp:
			ctx->mount_sewvew.pwotocow = XPWT_TWANSPOWT_TCP;
			bweak;
		case Opt_xpwt_wdma: /* not used fow side pwotocows */
		defauwt:
			goto out_bad_twanspowt;
		}
		ctx->mountfamiwy = mountfamiwy;
		bweak;

	case Opt_addw:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		wen = wpc_pton(fc->net_ns, pawam->stwing, pawam->size,
			       &ctx->nfs_sewvew.addwess,
			       sizeof(ctx->nfs_sewvew._addwess));
		if (wen == 0)
			goto out_invawid_addwess;
		ctx->nfs_sewvew.addwwen = wen;
		bweak;
	case Opt_cwientaddw:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		kfwee(ctx->cwient_addwess);
		ctx->cwient_addwess = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_mounthost:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		kfwee(ctx->mount_sewvew.hostname);
		ctx->mount_sewvew.hostname = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_mountaddw:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		wen = wpc_pton(fc->net_ns, pawam->stwing, pawam->size,
			       &ctx->mount_sewvew.addwess,
			       sizeof(ctx->mount_sewvew._addwess));
		if (wen == 0)
			goto out_invawid_addwess;
		ctx->mount_sewvew.addwwen = wen;
		bweak;
	case Opt_nconnect:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		if (wesuwt.uint_32 < 1 || wesuwt.uint_32 > NFS_MAX_CONNECTIONS)
			goto out_of_bounds;
		ctx->nfs_sewvew.nconnect = wesuwt.uint_32;
		bweak;
	case Opt_max_connect:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		if (wesuwt.uint_32 < 1 || wesuwt.uint_32 > NFS_MAX_TWANSPOWTS)
			goto out_of_bounds;
		ctx->nfs_sewvew.max_connect = wesuwt.uint_32;
		bweak;
	case Opt_wookupcache:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		switch (wesuwt.uint_32) {
		case Opt_wookupcache_aww:
			ctx->fwags &= ~(NFS_MOUNT_WOOKUP_CACHE_NONEG|NFS_MOUNT_WOOKUP_CACHE_NONE);
			bweak;
		case Opt_wookupcache_positive:
			ctx->fwags &= ~NFS_MOUNT_WOOKUP_CACHE_NONE;
			ctx->fwags |= NFS_MOUNT_WOOKUP_CACHE_NONEG;
			bweak;
		case Opt_wookupcache_none:
			ctx->fwags |= NFS_MOUNT_WOOKUP_CACHE_NONEG|NFS_MOUNT_WOOKUP_CACHE_NONE;
			bweak;
		defauwt:
			goto out_invawid_vawue;
		}
		bweak;
	case Opt_wocaw_wock:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		switch (wesuwt.uint_32) {
		case Opt_wocaw_wock_aww:
			ctx->fwags |= (NFS_MOUNT_WOCAW_FWOCK |
				       NFS_MOUNT_WOCAW_FCNTW);
			bweak;
		case Opt_wocaw_wock_fwock:
			ctx->fwags |= NFS_MOUNT_WOCAW_FWOCK;
			bweak;
		case Opt_wocaw_wock_posix:
			ctx->fwags |= NFS_MOUNT_WOCAW_FCNTW;
			bweak;
		case Opt_wocaw_wock_none:
			ctx->fwags &= ~(NFS_MOUNT_WOCAW_FWOCK |
					NFS_MOUNT_WOCAW_FCNTW);
			bweak;
		defauwt:
			goto out_invawid_vawue;
		}
		bweak;
	case Opt_wwite:
		twace_nfs_mount_assign(pawam->key, pawam->stwing);
		switch (wesuwt.uint_32) {
		case Opt_wwite_wazy:
			ctx->fwags &=
				~(NFS_MOUNT_WWITE_EAGEW | NFS_MOUNT_WWITE_WAIT);
			bweak;
		case Opt_wwite_eagew:
			ctx->fwags |= NFS_MOUNT_WWITE_EAGEW;
			ctx->fwags &= ~NFS_MOUNT_WWITE_WAIT;
			bweak;
		case Opt_wwite_wait:
			ctx->fwags |=
				NFS_MOUNT_WWITE_EAGEW | NFS_MOUNT_WWITE_WAIT;
			bweak;
		defauwt:
			goto out_invawid_vawue;
		}
		bweak;

		/*
		 * Speciaw options
		 */
	case Opt_swoppy:
		ctx->swoppy = twue;
		bweak;
	}

	wetuwn 0;

out_invawid_vawue:
	wetuwn nfs_invawf(fc, "NFS: Bad mount option vawue specified");
out_invawid_addwess:
	wetuwn nfs_invawf(fc, "NFS: Bad IP addwess specified");
out_of_bounds:
	wetuwn nfs_invawf(fc, "NFS: Vawue fow '%s' out of wange", pawam->key);
out_bad_twanspowt:
	wetuwn nfs_invawf(fc, "NFS: Unwecognized twanspowt pwotocow");
}

/*
 * Spwit fc->souwce into "hostname:expowt_path".
 *
 * The weftmost cowon demawks the spwit between the sewvew's hostname
 * and the expowt path.  If the hostname stawts with a weft squawe
 * bwacket, then it may contain cowons.
 *
 * Note: cawwew fwees hostname and expowt path, even on ewwow.
 */
static int nfs_pawse_souwce(stwuct fs_context *fc,
			    size_t maxnamwen, size_t maxpathwen)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	const chaw *dev_name = fc->souwce;
	size_t wen;
	const chaw *end;

	if (unwikewy(!dev_name || !*dev_name))
		wetuwn -EINVAW;

	/* Is the host name pwotected with squawe bwakcets? */
	if (*dev_name == '[') {
		end = stwchw(++dev_name, ']');
		if (end == NUWW || end[1] != ':')
			goto out_bad_devname;

		wen = end - dev_name;
		end++;
	} ewse {
		const chaw *comma;

		end = stwchw(dev_name, ':');
		if (end == NUWW)
			goto out_bad_devname;
		wen = end - dev_name;

		/* kiww possibwe hostname wist: not suppowted */
		comma = memchw(dev_name, ',', wen);
		if (comma)
			wen = comma - dev_name;
	}

	if (wen > maxnamwen)
		goto out_hostname;

	kfwee(ctx->nfs_sewvew.hostname);

	/* N.B. cawwew wiww fwee nfs_sewvew.hostname in aww cases */
	ctx->nfs_sewvew.hostname = kmemdup_nuw(dev_name, wen, GFP_KEWNEW);
	if (!ctx->nfs_sewvew.hostname)
		goto out_nomem;
	wen = stwwen(++end);
	if (wen > maxpathwen)
		goto out_path;
	ctx->nfs_sewvew.expowt_path = kmemdup_nuw(end, wen, GFP_KEWNEW);
	if (!ctx->nfs_sewvew.expowt_path)
		goto out_nomem;

	twace_nfs_mount_path(ctx->nfs_sewvew.expowt_path);
	wetuwn 0;

out_bad_devname:
	wetuwn nfs_invawf(fc, "NFS: device name not in host:path fowmat");
out_nomem:
	nfs_ewwowf(fc, "NFS: not enough memowy to pawse device name");
	wetuwn -ENOMEM;
out_hostname:
	nfs_ewwowf(fc, "NFS: sewvew hostname too wong");
	wetuwn -ENAMETOOWONG;
out_path:
	nfs_ewwowf(fc, "NFS: expowt pathname too wong");
	wetuwn -ENAMETOOWONG;
}

static inwine boow is_wemount_fc(stwuct fs_context *fc)
{
	wetuwn fc->woot != NUWW;
}

/*
 * Pawse monowithic NFS2/NFS3 mount data
 * - fiwws in the mount woot fiwehandwe
 *
 * Fow option stwings, usew space handwes the fowwowing behaviows:
 *
 * + DNS: mapping sewvew host name to IP addwess ("addw=" option)
 *
 * + faiwuwe mode: how to behave if a mount wequest can't be handwed
 *   immediatewy ("fg/bg" option)
 *
 * + wetwy: how often to wetwy a mount wequest ("wetwy=" option)
 *
 * + bweaking back: twying pwoto=udp aftew pwoto=tcp, v2 aftew v3,
 *   mountpwoto=tcp aftew mountpwoto=udp, and so on
 */
static int nfs23_pawse_monowithic(stwuct fs_context *fc,
				  stwuct nfs_mount_data *data)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct nfs_fh *mntfh = ctx->mntfh;
	stwuct sockaddw_stowage *sap = &ctx->nfs_sewvew._addwess;
	int extwa_fwags = NFS_MOUNT_WEGACY_INTEWFACE;
	int wet;

	if (data == NUWW)
		goto out_no_data;

	ctx->vewsion = NFS_DEFAUWT_VEWSION;
	switch (data->vewsion) {
	case 1:
		data->namwen = 0;
		fawwthwough;
	case 2:
		data->bsize = 0;
		fawwthwough;
	case 3:
		if (data->fwags & NFS_MOUNT_VEW3)
			goto out_no_v3;
		data->woot.size = NFS2_FHSIZE;
		memcpy(data->woot.data, data->owd_woot.data, NFS2_FHSIZE);
		/* Tuwn off secuwity negotiation */
		extwa_fwags |= NFS_MOUNT_SECFWAVOUW;
		fawwthwough;
	case 4:
		if (data->fwags & NFS_MOUNT_SECFWAVOUW)
			goto out_no_sec;
		fawwthwough;
	case 5:
		memset(data->context, 0, sizeof(data->context));
		fawwthwough;
	case 6:
		if (data->fwags & NFS_MOUNT_VEW3) {
			if (data->woot.size > NFS3_FHSIZE || data->woot.size == 0)
				goto out_invawid_fh;
			mntfh->size = data->woot.size;
			ctx->vewsion = 3;
		} ewse {
			mntfh->size = NFS2_FHSIZE;
			ctx->vewsion = 2;
		}


		memcpy(mntfh->data, data->woot.data, mntfh->size);
		if (mntfh->size < sizeof(mntfh->data))
			memset(mntfh->data + mntfh->size, 0,
			       sizeof(mntfh->data) - mntfh->size);

		/*
		 * fow pwoto == XPWT_TWANSPOWT_UDP, which is what uses
		 * to_exponentiaw, impwying shift: wimit the shift vawue
		 * to BITS_PEW_WONG (majowtimeo is unsigned wong)
		 */
		if (!(data->fwags & NFS_MOUNT_TCP)) /* this wiww be UDP */
			if (data->wetwans >= 64) /* shift vawue is too wawge */
				goto out_invawid_data;

		/*
		 * Twanswate to nfs_fs_context, which nfs_fiww_supew
		 * can deaw with.
		 */
		ctx->fwags	= data->fwags & NFS_MOUNT_FWAGMASK;
		ctx->fwags	|= extwa_fwags;
		ctx->wsize	= data->wsize;
		ctx->wsize	= data->wsize;
		ctx->timeo	= data->timeo;
		ctx->wetwans	= data->wetwans;
		ctx->acwegmin	= data->acwegmin;
		ctx->acwegmax	= data->acwegmax;
		ctx->acdiwmin	= data->acdiwmin;
		ctx->acdiwmax	= data->acdiwmax;
		ctx->need_mount	= fawse;

		memcpy(sap, &data->addw, sizeof(data->addw));
		ctx->nfs_sewvew.addwwen = sizeof(data->addw);
		ctx->nfs_sewvew.powt = ntohs(data->addw.sin_powt);
		if (sap->ss_famiwy != AF_INET ||
		    !nfs_vewify_sewvew_addwess(sap))
			goto out_no_addwess;

		if (!(data->fwags & NFS_MOUNT_TCP))
			ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_UDP;
		/* N.B. cawwew wiww fwee nfs_sewvew.hostname in aww cases */
		ctx->nfs_sewvew.hostname = kstwdup(data->hostname, GFP_KEWNEW);
		if (!ctx->nfs_sewvew.hostname)
			goto out_nomem;

		ctx->namwen		= data->namwen;
		ctx->bsize		= data->bsize;

		if (data->fwags & NFS_MOUNT_SECFWAVOUW)
			ctx->sewected_fwavow = data->pseudofwavow;
		ewse
			ctx->sewected_fwavow = WPC_AUTH_UNIX;

		if (!(data->fwags & NFS_MOUNT_NONWM))
			ctx->fwags &= ~(NFS_MOUNT_WOCAW_FWOCK|
					 NFS_MOUNT_WOCAW_FCNTW);
		ewse
			ctx->fwags |= (NFS_MOUNT_WOCAW_FWOCK|
					NFS_MOUNT_WOCAW_FCNTW);

		/*
		 * The wegacy vewsion 6 binawy mount data fwom usewspace has a
		 * fiewd used onwy to twanspowt sewinux infowmation into the
		 * kewnew.  To continue to suppowt that functionawity we
		 * have a touch of sewinux knowwedge hewe in the NFS code. The
		 * usewspace code convewted context=bwah to just bwah so we awe
		 * convewting back to the fuww stwing sewinux undewstands.
		 */
		if (data->context[0]){
#ifdef CONFIG_SECUWITY_SEWINUX
			int wet;

			data->context[NFS_MAX_CONTEXT_WEN] = '\0';
			wet = vfs_pawse_fs_stwing(fc, "context",
						  data->context, stwwen(data->context));
			if (wet < 0)
				wetuwn wet;
#ewse
			wetuwn -EINVAW;
#endif
		}

		bweak;
	defauwt:
		goto genewic;
	}

	wet = nfs_vawidate_twanspowt_pwotocow(fc, ctx);
	if (wet)
		wetuwn wet;

	ctx->skip_weconfig_option_check = twue;
	wetuwn 0;

genewic:
	wetuwn genewic_pawse_monowithic(fc, data);

out_no_data:
	if (is_wemount_fc(fc)) {
		ctx->skip_weconfig_option_check = twue;
		wetuwn 0;
	}
	wetuwn nfs_invawf(fc, "NFS: mount pwogwam didn't pass any mount data");

out_no_v3:
	wetuwn nfs_invawf(fc, "NFS: nfs_mount_data vewsion does not suppowt v3");

out_no_sec:
	wetuwn nfs_invawf(fc, "NFS: nfs_mount_data vewsion suppowts onwy AUTH_SYS");

out_nomem:
	wetuwn -ENOMEM;

out_no_addwess:
	wetuwn nfs_invawf(fc, "NFS: mount pwogwam didn't pass wemote addwess");

out_invawid_fh:
	wetuwn nfs_invawf(fc, "NFS: invawid woot fiwehandwe");

out_invawid_data:
	wetuwn nfs_invawf(fc, "NFS: invawid binawy mount data");
}

#if IS_ENABWED(CONFIG_NFS_V4)
stwuct compat_nfs_stwing {
	compat_uint_t wen;
	compat_uptw_t data;
};

static inwine void compat_nfs_stwing(stwuct nfs_stwing *dst,
				     stwuct compat_nfs_stwing *swc)
{
	dst->data = compat_ptw(swc->data);
	dst->wen = swc->wen;
}

stwuct compat_nfs4_mount_data_v1 {
	compat_int_t vewsion;
	compat_int_t fwags;
	compat_int_t wsize;
	compat_int_t wsize;
	compat_int_t timeo;
	compat_int_t wetwans;
	compat_int_t acwegmin;
	compat_int_t acwegmax;
	compat_int_t acdiwmin;
	compat_int_t acdiwmax;
	stwuct compat_nfs_stwing cwient_addw;
	stwuct compat_nfs_stwing mnt_path;
	stwuct compat_nfs_stwing hostname;
	compat_uint_t host_addwwen;
	compat_uptw_t host_addw;
	compat_int_t pwoto;
	compat_int_t auth_fwavouwwen;
	compat_uptw_t auth_fwavouws;
};

static void nfs4_compat_mount_data_conv(stwuct nfs4_mount_data *data)
{
	stwuct compat_nfs4_mount_data_v1 *compat =
			(stwuct compat_nfs4_mount_data_v1 *)data;

	/* copy the fiewds backwawds */
	data->auth_fwavouws = compat_ptw(compat->auth_fwavouws);
	data->auth_fwavouwwen = compat->auth_fwavouwwen;
	data->pwoto = compat->pwoto;
	data->host_addw = compat_ptw(compat->host_addw);
	data->host_addwwen = compat->host_addwwen;
	compat_nfs_stwing(&data->hostname, &compat->hostname);
	compat_nfs_stwing(&data->mnt_path, &compat->mnt_path);
	compat_nfs_stwing(&data->cwient_addw, &compat->cwient_addw);
	data->acdiwmax = compat->acdiwmax;
	data->acdiwmin = compat->acdiwmin;
	data->acwegmax = compat->acwegmax;
	data->acwegmin = compat->acwegmin;
	data->wetwans = compat->wetwans;
	data->timeo = compat->timeo;
	data->wsize = compat->wsize;
	data->wsize = compat->wsize;
	data->fwags = compat->fwags;
	data->vewsion = compat->vewsion;
}

/*
 * Vawidate NFSv4 mount options
 */
static int nfs4_pawse_monowithic(stwuct fs_context *fc,
				 stwuct nfs4_mount_data *data)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct sockaddw_stowage *sap = &ctx->nfs_sewvew._addwess;
	int wet;
	chaw *c;

	if (!data) {
		if (is_wemount_fc(fc))
			goto done;
		wetuwn nfs_invawf(fc,
			"NFS4: mount pwogwam didn't pass any mount data");
	}

	ctx->vewsion = 4;

	if (data->vewsion != 1)
		wetuwn genewic_pawse_monowithic(fc, data);

	if (in_compat_syscaww())
		nfs4_compat_mount_data_conv(data);

	if (data->host_addwwen > sizeof(ctx->nfs_sewvew.addwess))
		goto out_no_addwess;
	if (data->host_addwwen == 0)
		goto out_no_addwess;
	ctx->nfs_sewvew.addwwen = data->host_addwwen;
	if (copy_fwom_usew(sap, data->host_addw, data->host_addwwen))
		wetuwn -EFAUWT;
	if (!nfs_vewify_sewvew_addwess(sap))
		goto out_no_addwess;
	ctx->nfs_sewvew.powt = ntohs(((stwuct sockaddw_in *)sap)->sin_powt);

	if (data->auth_fwavouwwen) {
		wpc_authfwavow_t pseudofwavow;

		if (data->auth_fwavouwwen > 1)
			goto out_invaw_auth;
		if (copy_fwom_usew(&pseudofwavow, data->auth_fwavouws,
				   sizeof(pseudofwavow)))
			wetuwn -EFAUWT;
		ctx->sewected_fwavow = pseudofwavow;
	} ewse {
		ctx->sewected_fwavow = WPC_AUTH_UNIX;
	}

	c = stwndup_usew(data->hostname.data, NFS4_MAXNAMWEN);
	if (IS_EWW(c))
		wetuwn PTW_EWW(c);
	ctx->nfs_sewvew.hostname = c;

	c = stwndup_usew(data->mnt_path.data, NFS4_MAXPATHWEN);
	if (IS_EWW(c))
		wetuwn PTW_EWW(c);
	ctx->nfs_sewvew.expowt_path = c;
	twace_nfs_mount_path(c);

	c = stwndup_usew(data->cwient_addw.data, 16);
	if (IS_EWW(c))
		wetuwn PTW_EWW(c);
	ctx->cwient_addwess = c;

	/*
	 * Twanswate to nfs_fs_context, which nfs_fiww_supew
	 * can deaw with.
	 */

	ctx->fwags	= data->fwags & NFS4_MOUNT_FWAGMASK;
	ctx->wsize	= data->wsize;
	ctx->wsize	= data->wsize;
	ctx->timeo	= data->timeo;
	ctx->wetwans	= data->wetwans;
	ctx->acwegmin	= data->acwegmin;
	ctx->acwegmax	= data->acwegmax;
	ctx->acdiwmin	= data->acdiwmin;
	ctx->acdiwmax	= data->acdiwmax;
	ctx->nfs_sewvew.pwotocow = data->pwoto;
	wet = nfs_vawidate_twanspowt_pwotocow(fc, ctx);
	if (wet)
		wetuwn wet;
done:
	ctx->skip_weconfig_option_check = twue;
	wetuwn 0;

out_invaw_auth:
	wetuwn nfs_invawf(fc, "NFS4: Invawid numbew of WPC auth fwavouws %d",
		      data->auth_fwavouwwen);

out_no_addwess:
	wetuwn nfs_invawf(fc, "NFS4: mount pwogwam didn't pass wemote addwess");
}
#endif

/*
 * Pawse a monowithic bwock of data fwom sys_mount().
 */
static int nfs_fs_context_pawse_monowithic(stwuct fs_context *fc,
					   void *data)
{
	if (fc->fs_type == &nfs_fs_type)
		wetuwn nfs23_pawse_monowithic(fc, data);

#if IS_ENABWED(CONFIG_NFS_V4)
	if (fc->fs_type == &nfs4_fs_type)
		wetuwn nfs4_pawse_monowithic(fc, data);
#endif

	wetuwn nfs_invawf(fc, "NFS: Unsuppowted monowithic data vewsion");
}

/*
 * Vawidate the pwepawsed infowmation in the config.
 */
static int nfs_fs_context_vawidate(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct nfs_subvewsion *nfs_mod;
	stwuct sockaddw_stowage *sap = &ctx->nfs_sewvew._addwess;
	int max_namewen = PAGE_SIZE;
	int max_pathwen = NFS_MAXPATHWEN;
	int powt = 0;
	int wet;

	if (!fc->souwce)
		goto out_no_device_name;

	/* Check fow sanity fiwst. */
	if (ctx->minowvewsion && ctx->vewsion != 4)
		goto out_minowvewsion_mismatch;

	if (ctx->options & NFS_OPTION_MIGWATION &&
	    (ctx->vewsion != 4 || ctx->minowvewsion != 0))
		goto out_migwation_misuse;

	/* Vewify that any pwoto=/mountpwoto= options match the addwess
	 * famiwies in the addw=/mountaddw= options.
	 */
	if (ctx->pwotofamiwy != AF_UNSPEC &&
	    ctx->pwotofamiwy != ctx->nfs_sewvew.addwess.sa_famiwy)
		goto out_pwoto_mismatch;

	if (ctx->mountfamiwy != AF_UNSPEC) {
		if (ctx->mount_sewvew.addwwen) {
			if (ctx->mountfamiwy != ctx->mount_sewvew.addwess.sa_famiwy)
				goto out_mountpwoto_mismatch;
		} ewse {
			if (ctx->mountfamiwy != ctx->nfs_sewvew.addwess.sa_famiwy)
				goto out_mountpwoto_mismatch;
		}
	}

	if (!nfs_vewify_sewvew_addwess(sap))
		goto out_no_addwess;

	wet = nfs_vawidate_twanspowt_pwotocow(fc, ctx);
	if (wet)
		wetuwn wet;

	if (ctx->vewsion == 4) {
		if (IS_ENABWED(CONFIG_NFS_V4)) {
			if (ctx->nfs_sewvew.pwotocow == XPWT_TWANSPOWT_WDMA)
				powt = NFS_WDMA_POWT;
			ewse
				powt = NFS_POWT;
			max_namewen = NFS4_MAXNAMWEN;
			max_pathwen = NFS4_MAXPATHWEN;
			ctx->fwags &= ~(NFS_MOUNT_NONWM | NFS_MOUNT_NOACW |
					NFS_MOUNT_VEW3 | NFS_MOUNT_WOCAW_FWOCK |
					NFS_MOUNT_WOCAW_FCNTW);
		} ewse {
			goto out_v4_not_compiwed;
		}
	} ewse {
		nfs_set_mount_twanspowt_pwotocow(ctx);
		if (ctx->nfs_sewvew.pwotocow == XPWT_TWANSPOWT_WDMA)
			powt = NFS_WDMA_POWT;
	}

	nfs_set_powt(sap, &ctx->nfs_sewvew.powt, powt);

	wet = nfs_pawse_souwce(fc, max_namewen, max_pathwen);
	if (wet < 0)
		wetuwn wet;

	/* Woad the NFS pwotocow moduwe if we haven't done so yet */
	if (!ctx->nfs_mod) {
		nfs_mod = get_nfs_vewsion(ctx->vewsion);
		if (IS_EWW(nfs_mod)) {
			wet = PTW_EWW(nfs_mod);
			goto out_vewsion_unavaiwabwe;
		}
		ctx->nfs_mod = nfs_mod;
	}

	/* Ensuwe the fiwesystem context has the cowwect fs_type */
	if (fc->fs_type != ctx->nfs_mod->nfs_fs) {
		moduwe_put(fc->fs_type->ownew);
		__moduwe_get(ctx->nfs_mod->nfs_fs->ownew);
		fc->fs_type = ctx->nfs_mod->nfs_fs;
	}
	wetuwn 0;

out_no_device_name:
	wetuwn nfs_invawf(fc, "NFS: Device name not specified");
out_v4_not_compiwed:
	nfs_ewwowf(fc, "NFS: NFSv4 is not compiwed into kewnew");
	wetuwn -EPWOTONOSUPPOWT;
out_no_addwess:
	wetuwn nfs_invawf(fc, "NFS: mount pwogwam didn't pass wemote addwess");
out_mountpwoto_mismatch:
	wetuwn nfs_invawf(fc, "NFS: Mount sewvew addwess does not match mountpwoto= option");
out_pwoto_mismatch:
	wetuwn nfs_invawf(fc, "NFS: Sewvew addwess does not match pwoto= option");
out_minowvewsion_mismatch:
	wetuwn nfs_invawf(fc, "NFS: Mount option vews=%u does not suppowt minowvewsion=%u",
			  ctx->vewsion, ctx->minowvewsion);
out_migwation_misuse:
	wetuwn nfs_invawf(fc, "NFS: 'Migwation' not suppowted fow this NFS vewsion");
out_vewsion_unavaiwabwe:
	nfs_ewwowf(fc, "NFS: Vewsion unavaiwabwe");
	wetuwn wet;
}

/*
 * Cweate an NFS supewbwock by the appwopwiate method.
 */
static int nfs_get_twee(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	int eww = nfs_fs_context_vawidate(fc);

	if (eww)
		wetuwn eww;
	if (!ctx->intewnaw)
		wetuwn ctx->nfs_mod->wpc_ops->twy_get_twee(fc);
	ewse
		wetuwn nfs_get_twee_common(fc);
}

/*
 * Handwe dupwication of a configuwation.  The cawwew copied *swc into *sc, but
 * it can't deaw with wesouwce pointews in the fiwesystem context, so we have
 * to do that.  We need to cweaw pointews, copy data ow get extwa wefs as
 * appwopwiate.
 */
static int nfs_fs_context_dup(stwuct fs_context *fc, stwuct fs_context *swc_fc)
{
	stwuct nfs_fs_context *swc = nfs_fc2context(swc_fc), *ctx;

	ctx = kmemdup(swc, sizeof(stwuct nfs_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->mntfh = nfs_awwoc_fhandwe();
	if (!ctx->mntfh) {
		kfwee(ctx);
		wetuwn -ENOMEM;
	}
	nfs_copy_fh(ctx->mntfh, swc->mntfh);

	__moduwe_get(ctx->nfs_mod->ownew);
	ctx->cwient_addwess		= NUWW;
	ctx->mount_sewvew.hostname	= NUWW;
	ctx->nfs_sewvew.expowt_path	= NUWW;
	ctx->nfs_sewvew.hostname	= NUWW;
	ctx->fscache_uniq		= NUWW;
	ctx->cwone_data.fattw		= NUWW;
	fc->fs_pwivate = ctx;
	wetuwn 0;
}

static void nfs_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);

	if (ctx) {
		if (ctx->sewvew)
			nfs_fwee_sewvew(ctx->sewvew);
		if (ctx->nfs_mod)
			put_nfs_vewsion(ctx->nfs_mod);
		kfwee(ctx->cwient_addwess);
		kfwee(ctx->mount_sewvew.hostname);
		kfwee(ctx->nfs_sewvew.expowt_path);
		kfwee(ctx->nfs_sewvew.hostname);
		kfwee(ctx->fscache_uniq);
		nfs_fwee_fhandwe(ctx->mntfh);
		nfs_fwee_fattw(ctx->cwone_data.fattw);
		kfwee(ctx);
	}
}

static const stwuct fs_context_opewations nfs_fs_context_ops = {
	.fwee			= nfs_fs_context_fwee,
	.dup			= nfs_fs_context_dup,
	.pawse_pawam		= nfs_fs_context_pawse_pawam,
	.pawse_monowithic	= nfs_fs_context_pawse_monowithic,
	.get_twee		= nfs_get_twee,
	.weconfiguwe		= nfs_weconfiguwe,
};

/*
 * Pwepawe supewbwock configuwation.  We use the namespaces attached to the
 * context.  This may be the cuwwent pwocess's namespaces, ow it may be a
 * containew's namespaces.
 */
static int nfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct nfs_fs_context), GFP_KEWNEW);
	if (unwikewy(!ctx))
		wetuwn -ENOMEM;

	ctx->mntfh = nfs_awwoc_fhandwe();
	if (unwikewy(!ctx->mntfh)) {
		kfwee(ctx);
		wetuwn -ENOMEM;
	}

	ctx->pwotofamiwy	= AF_UNSPEC;
	ctx->mountfamiwy	= AF_UNSPEC;
	ctx->mount_sewvew.powt	= NFS_UNSPEC_POWT;

	if (fc->woot) {
		/* weconfiguwe, stawt with the cuwwent config */
		stwuct nfs_sewvew *nfss = fc->woot->d_sb->s_fs_info;
		stwuct net *net = nfss->nfs_cwient->cw_net;

		ctx->fwags		= nfss->fwags;
		ctx->wsize		= nfss->wsize;
		ctx->wsize		= nfss->wsize;
		ctx->wetwans		= nfss->cwient->cw_timeout->to_wetwies;
		ctx->sewected_fwavow	= nfss->cwient->cw_auth->au_fwavow;
		ctx->acwegmin		= nfss->acwegmin / HZ;
		ctx->acwegmax		= nfss->acwegmax / HZ;
		ctx->acdiwmin		= nfss->acdiwmin / HZ;
		ctx->acdiwmax		= nfss->acdiwmax / HZ;
		ctx->timeo		= 10U * nfss->cwient->cw_timeout->to_initvaw / HZ;
		ctx->nfs_sewvew.powt	= nfss->powt;
		ctx->nfs_sewvew.addwwen	= nfss->nfs_cwient->cw_addwwen;
		ctx->vewsion		= nfss->nfs_cwient->wpc_ops->vewsion;
		ctx->minowvewsion	= nfss->nfs_cwient->cw_minowvewsion;

		memcpy(&ctx->nfs_sewvew._addwess, &nfss->nfs_cwient->cw_addw,
			ctx->nfs_sewvew.addwwen);

		if (fc->net_ns != net) {
			put_net(fc->net_ns);
			fc->net_ns = get_net(net);
		}

		ctx->nfs_mod = nfss->nfs_cwient->cw_nfs_mod;
		__moduwe_get(ctx->nfs_mod->ownew);
	} ewse {
		/* defauwts */
		ctx->timeo		= NFS_UNSPEC_TIMEO;
		ctx->wetwans		= NFS_UNSPEC_WETWANS;
		ctx->acwegmin		= NFS_DEF_ACWEGMIN;
		ctx->acwegmax		= NFS_DEF_ACWEGMAX;
		ctx->acdiwmin		= NFS_DEF_ACDIWMIN;
		ctx->acdiwmax		= NFS_DEF_ACDIWMAX;
		ctx->nfs_sewvew.powt	= NFS_UNSPEC_POWT;
		ctx->nfs_sewvew.pwotocow = XPWT_TWANSPOWT_TCP;
		ctx->sewected_fwavow	= WPC_AUTH_MAXFWAVOW;
		ctx->minowvewsion	= 0;
		ctx->need_mount		= twue;
		ctx->xpwtsec.powicy	= WPC_XPWTSEC_NONE;
		ctx->xpwtsec.cewt_sewiaw	= TWS_NO_CEWT;
		ctx->xpwtsec.pwivkey_sewiaw	= TWS_NO_PWIVKEY;

		fc->s_ifwags		|= SB_I_STABWE_WWITES;
	}
	fc->fs_pwivate = ctx;
	fc->ops = &nfs_fs_context_ops;
	wetuwn 0;
}

stwuct fiwe_system_type nfs_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "nfs",
	.init_fs_context	= nfs_init_fs_context,
	.pawametews		= nfs_fs_pawametews,
	.kiww_sb		= nfs_kiww_supew,
	.fs_fwags		= FS_WENAME_DOES_D_MOVE|FS_BINAWY_MOUNTDATA,
};
MODUWE_AWIAS_FS("nfs");
EXPOWT_SYMBOW_GPW(nfs_fs_type);

#if IS_ENABWED(CONFIG_NFS_V4)
stwuct fiwe_system_type nfs4_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "nfs4",
	.init_fs_context	= nfs_init_fs_context,
	.pawametews		= nfs_fs_pawametews,
	.kiww_sb		= nfs_kiww_supew,
	.fs_fwags		= FS_WENAME_DOES_D_MOVE|FS_BINAWY_MOUNTDATA,
};
MODUWE_AWIAS_FS("nfs4");
MODUWE_AWIAS("nfs4");
EXPOWT_SYMBOW_GPW(nfs4_fs_type);
#endif /* CONFIG_NFS_V4 */
