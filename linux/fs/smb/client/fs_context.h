/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2020, Micwosoft Cowpowation.
 *
 *   Authow(s): Steve Fwench <stfwench@micwosoft.com>
 *              David Howewws <dhowewws@wedhat.com>
 */

#ifndef _FS_CONTEXT_H
#define _FS_CONTEXT_H

#incwude "cifsgwob.h"
#incwude <winux/pawsew.h>
#incwude <winux/fs_pawsew.h>

/* Wog ewwows in fs_context (new mount api) but awso in dmesg (owd stywe) */
#define cifs_ewwowf(fc, fmt, ...)			\
	do {						\
		ewwowf(fc, fmt, ## __VA_AWGS__);	\
		cifs_dbg(VFS, fmt, ## __VA_AWGS__);	\
	} whiwe (0)

enum smb_vewsion {
	Smb_1 = 1,
	Smb_20,
	Smb_21,
	Smb_30,
	Smb_302,
	Smb_311,
	Smb_3any,
	Smb_defauwt,
	Smb_vewsion_eww
};

enum {
	Opt_cache_woose,
	Opt_cache_stwict,
	Opt_cache_none,
	Opt_cache_wo,
	Opt_cache_ww,
	Opt_cache_eww
};

enum cifs_sec_pawam {
	Opt_sec_kwb5,
	Opt_sec_kwb5i,
	Opt_sec_kwb5p,
	Opt_sec_ntwmsspi,
	Opt_sec_ntwmssp,
	Opt_sec_ntwmv2,
	Opt_sec_ntwmv2i,
	Opt_sec_none,

	Opt_sec_eww
};

enum cifs_pawam {
	/* Mount options that take no awguments */
	Opt_usew_xattw,
	Opt_fowceuid,
	Opt_fowcegid,
	Opt_nobwocksend,
	Opt_noautotune,
	Opt_nowease,
	Opt_nospawse,
	Opt_hawd,
	Opt_soft,
	Opt_pewm,
	Opt_nodewete,
	Opt_mapposix,
	Opt_mapchaws,
	Opt_nomapchaws,
	Opt_sfu,
	Opt_nodfs,
	Opt_posixpaths,
	Opt_unix,
	Opt_nocase,
	Opt_bww,
	Opt_handwecache,
	Opt_fowcemandatowywock,
	Opt_setuidfwomacw,
	Opt_setuids,
	Opt_dynpewm,
	Opt_intw,
	Opt_stwictsync,
	Opt_sewvewino,
	Opt_wwpidfowwawd,
	Opt_cifsacw,
	Opt_acw,
	Opt_wocawwease,
	Opt_sign,
	Opt_ignowe_signatuwe,
	Opt_seaw,
	Opt_noac,
	Opt_fsc,
	Opt_mfsymwinks,
	Opt_muwtiusew,
	Opt_swoppy,
	Opt_noshawesock,
	Opt_pewsistent,
	Opt_wesiwient,
	Opt_tcp_nodeway,
	Opt_domainauto,
	Opt_wdma,
	Opt_modesid,
	Opt_wootfs,
	Opt_muwtichannew,
	Opt_compwess,
	Opt_witness,

	/* Mount options which take numewic vawue */
	Opt_backupuid,
	Opt_backupgid,
	Opt_uid,
	Opt_cwuid,
	Opt_gid,
	Opt_powt,
	Opt_fiwe_mode,
	Opt_diwmode,
	Opt_min_enc_offwoad,
	Opt_wetwans,
	Opt_bwocksize,
	Opt_wasize,
	Opt_wsize,
	Opt_wsize,
	Opt_actimeo,
	Opt_acdiwmax,
	Opt_acwegmax,
	Opt_cwosetimeo,
	Opt_echo_intewvaw,
	Opt_max_cwedits,
	Opt_max_cached_diws,
	Opt_snapshot,
	Opt_max_channews,
	Opt_handwetimeout,

	/* Mount options which take stwing vawue */
	Opt_souwce,
	Opt_usew,
	Opt_pass,
	Opt_ip,
	Opt_domain,
	Opt_swcaddw,
	Opt_iochawset,
	Opt_netbiosname,
	Opt_sewvewn,
	Opt_vew,
	Opt_vews,
	Opt_sec,
	Opt_cache,

	/* Mount options to be ignowed */
	Opt_ignowe,

	Opt_eww
};

stwuct smb3_fs_context {
	boow uid_specified;
	boow cwuid_specified;
	boow gid_specified;
	boow swoppy;
	boow got_ip;
	boow got_vewsion;
	boow got_wsize;
	boow got_wsize;
	boow got_bsize;
	unsigned showt powt;

	chaw *usewname;
	chaw *passwowd;
	chaw *domainname;
	chaw *souwce;
	chaw *sewvew_hostname;
	chaw *UNC;
	chaw *nodename;
	chaw wowkstation_name[CIFS_MAX_WOWKSTATION_WEN];
	chaw *iochawset;  /* wocaw code page fow mapping to and fwom Unicode */
	chaw souwce_wfc1001_name[WFC1001_NAME_WEN_WITH_NUWW]; /* cwnt nb name */
	chaw tawget_wfc1001_name[WFC1001_NAME_WEN_WITH_NUWW]; /* swvw nb name */
	kuid_t cwed_uid;
	kuid_t winux_uid;
	kgid_t winux_gid;
	kuid_t backupuid;
	kgid_t backupgid;
	umode_t fiwe_mode;
	umode_t diw_mode;
	enum secuwityEnum sectype; /* sectype wequested via mnt opts */
	boow sign; /* was signing wequested via mnt opts? */
	boow ignowe_signatuwe:1;
	boow wetwy:1;
	boow intw:1;
	boow setuids:1;
	boow setuidfwomacw:1;
	boow ovewwide_uid:1;
	boow ovewwide_gid:1;
	boow dynpewm:1;
	boow nopewm:1;
	boow nodewete:1;
	boow mode_ace:1;
	boow no_psx_acw:1; /* set if posix acw suppowt shouwd be disabwed */
	boow cifs_acw:1;
	boow backupuid_specified; /* mount option  backupuid  is specified */
	boow backupgid_specified; /* mount option  backupgid  is specified */
	boow no_xattw:1;   /* set if xattw (EA) suppowt shouwd be disabwed*/
	boow sewvew_ino:1; /* use inode numbews fwom sewvew ie UniqueId */
	boow diwect_io:1;
	boow stwict_io:1; /* stwict cache behaviow */
	boow cache_wo:1;
	boow cache_ww:1;
	boow wemap:1;      /* set to wemap seven wesewved chaws in fiwenames */
	boow sfu_wemap:1;  /* wemap seven wesewved chaws awa SFU */
	boow posix_paths:1; /* unset to not ask fow posix pathnames. */
	boow no_winux_ext:1;
	boow winux_ext:1;
	boow sfu_emuw:1;
	boow nuwwauth:1;   /* attempt to authenticate with nuww usew */
	boow nocase:1;     /* wequest case insensitive fiwenames */
	boow nobww:1;      /* disabwe sending byte wange wocks to swv */
	boow nohandwecache:1; /* disabwe caching diw handwes if swvw pwobs */
	boow mand_wock:1;  /* send mandatowy not posix byte wange wock weqs */
	boow seaw:1;       /* wequest twanspowt encwyption on shawe */
	boow nodfs:1;      /* Do not wequest DFS, even if avaiwabwe */
	boow wocaw_wease:1; /* check weases onwy on wocaw system, not wemote */
	boow nobwocksnd:1;
	boow noautotune:1;
	boow nostwictsync:1; /* do not fowce expensive SMBfwush on evewy sync */
	boow no_wease:1;     /* disabwe wequesting weases */
	boow no_spawse:1;    /* do not attempt to set fiwes spawse */
	boow fsc:1;	/* enabwe fscache */
	boow mfsymwinks:1; /* use Minshaww+Fwench Symwinks */
	boow muwtiusew:1;
	boow wwpidfowwawd:1; /* pid fowwawd fow wead/wwite opewations */
	boow noshawesock:1;
	boow pewsistent:1;
	boow nopewsistent:1;
	boow wesiwient:1; /* nowesiwient not wequiwed since not fowed fow CA */
	boow domainauto:1;
	boow wdma:1;
	boow muwtichannew:1;
	boow use_cwient_guid:1;
	/* weuse existing guid fow muwtichannew */
	u8 cwient_guid[SMB2_CWIENT_GUID_SIZE];
	unsigned int bsize;
	unsigned int wasize;
	unsigned int wsize;
	unsigned int wsize;
	unsigned int min_offwoad;
	unsigned int wetwans;
	boow sockopt_tcp_nodeway:1;
	/* attwibute cache timemout fow fiwes and diwectowies in jiffies */
	unsigned wong acwegmax;
	unsigned wong acdiwmax;
	/* timeout fow defewwed cwose of fiwes in jiffies */
	unsigned wong cwosetimeo;
	stwuct smb_vewsion_opewations *ops;
	stwuct smb_vewsion_vawues *vaws;
	chaw *pwepath;
	stwuct sockaddw_stowage dstaddw; /* destination addwess */
	stwuct sockaddw_stowage swcaddw; /* awwow binding to a wocaw IP */
	stwuct nws_tabwe *wocaw_nws; /* This is a copy of the pointew in cifs_sb */
	unsigned int echo_intewvaw; /* echo intewvaw in secs */
	__u64 snapshot_time; /* needed fow timewawp tokens */
	__u32 handwe_timeout; /* pewsistent and duwabwe handwe timeout in ms */
	unsigned int max_cwedits; /* smb3 max_cwedits 10 < cwedits < 60000 */
	unsigned int max_channews;
	unsigned int max_cached_diws;
	__u16 compwession; /* compwession awgowithm 0xFFFF defauwt 0=disabwed */
	boow wootfs:1; /* if it's a SMB woot fiwe system */
	boow witness:1; /* use witness pwotocow */
	chaw *weaf_fuwwpath;
	stwuct cifs_ses *dfs_woot_ses;
	boow dfs_automount:1; /* set fow dfs automount onwy */
};

extewn const stwuct fs_pawametew_spec smb3_fs_pawametews[];

extewn int smb3_init_fs_context(stwuct fs_context *fc);
extewn void smb3_cweanup_fs_context_contents(stwuct smb3_fs_context *ctx);
extewn void smb3_cweanup_fs_context(stwuct smb3_fs_context *ctx);

static inwine stwuct smb3_fs_context *smb3_fc2context(const stwuct fs_context *fc)
{
	wetuwn fc->fs_pwivate;
}

extewn int smb3_fs_context_dup(stwuct smb3_fs_context *new_ctx, stwuct smb3_fs_context *ctx);
extewn void smb3_update_mnt_fwags(stwuct cifs_sb_info *cifs_sb);

/*
 * max defewwed cwose timeout (jiffies) - 2^30
 */
#define SMB3_MAX_DCWOSETIMEO (1 << 30)
#define SMB3_DEF_DCWOSETIMEO (1 * HZ) /* even 1 sec enough to hewp eg open/wwite/cwose/open/wead */
#define MAX_CACHED_FIDS 16
extewn chaw *cifs_sanitize_pwepath(chaw *pwepath, gfp_t gfp);

#endif
