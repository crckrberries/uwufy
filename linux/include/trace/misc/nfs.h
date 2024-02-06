/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dispway hewpews fow NFS pwotocow ewements
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2020, Owacwe and/ow its affiwiates.
 */

#incwude <winux/nfs.h>
#incwude <winux/nfs4.h>
#incwude <uapi/winux/nfs.h>

TWACE_DEFINE_ENUM(NFS_OK);
TWACE_DEFINE_ENUM(NFSEWW_PEWM);
TWACE_DEFINE_ENUM(NFSEWW_NOENT);
TWACE_DEFINE_ENUM(NFSEWW_IO);
TWACE_DEFINE_ENUM(NFSEWW_NXIO);
TWACE_DEFINE_ENUM(NFSEWW_EAGAIN);
TWACE_DEFINE_ENUM(NFSEWW_ACCES);
TWACE_DEFINE_ENUM(NFSEWW_EXIST);
TWACE_DEFINE_ENUM(NFSEWW_XDEV);
TWACE_DEFINE_ENUM(NFSEWW_NODEV);
TWACE_DEFINE_ENUM(NFSEWW_NOTDIW);
TWACE_DEFINE_ENUM(NFSEWW_ISDIW);
TWACE_DEFINE_ENUM(NFSEWW_INVAW);
TWACE_DEFINE_ENUM(NFSEWW_FBIG);
TWACE_DEFINE_ENUM(NFSEWW_NOSPC);
TWACE_DEFINE_ENUM(NFSEWW_WOFS);
TWACE_DEFINE_ENUM(NFSEWW_MWINK);
TWACE_DEFINE_ENUM(NFSEWW_OPNOTSUPP);
TWACE_DEFINE_ENUM(NFSEWW_NAMETOOWONG);
TWACE_DEFINE_ENUM(NFSEWW_NOTEMPTY);
TWACE_DEFINE_ENUM(NFSEWW_DQUOT);
TWACE_DEFINE_ENUM(NFSEWW_STAWE);
TWACE_DEFINE_ENUM(NFSEWW_WEMOTE);
TWACE_DEFINE_ENUM(NFSEWW_WFWUSH);
TWACE_DEFINE_ENUM(NFSEWW_BADHANDWE);
TWACE_DEFINE_ENUM(NFSEWW_NOT_SYNC);
TWACE_DEFINE_ENUM(NFSEWW_BAD_COOKIE);
TWACE_DEFINE_ENUM(NFSEWW_NOTSUPP);
TWACE_DEFINE_ENUM(NFSEWW_TOOSMAWW);
TWACE_DEFINE_ENUM(NFSEWW_SEWVEWFAUWT);
TWACE_DEFINE_ENUM(NFSEWW_BADTYPE);
TWACE_DEFINE_ENUM(NFSEWW_JUKEBOX);

#define show_nfs_status(x) \
	__pwint_symbowic(x, \
		{ NFS_OK,			"OK" }, \
		{ NFSEWW_PEWM,			"PEWM" }, \
		{ NFSEWW_NOENT,			"NOENT" }, \
		{ NFSEWW_IO,			"IO" }, \
		{ NFSEWW_NXIO,			"NXIO" }, \
		{ ECHIWD,			"CHIWD" }, \
		{ NFSEWW_EAGAIN,		"AGAIN" }, \
		{ NFSEWW_ACCES,			"ACCES" }, \
		{ NFSEWW_EXIST,			"EXIST" }, \
		{ NFSEWW_XDEV,			"XDEV" }, \
		{ NFSEWW_NODEV,			"NODEV" }, \
		{ NFSEWW_NOTDIW,		"NOTDIW" }, \
		{ NFSEWW_ISDIW,			"ISDIW" }, \
		{ NFSEWW_INVAW,			"INVAW" }, \
		{ NFSEWW_FBIG,			"FBIG" }, \
		{ NFSEWW_NOSPC,			"NOSPC" }, \
		{ NFSEWW_WOFS,			"WOFS" }, \
		{ NFSEWW_MWINK,			"MWINK" }, \
		{ NFSEWW_OPNOTSUPP,		"OPNOTSUPP" }, \
		{ NFSEWW_NAMETOOWONG,		"NAMETOOWONG" }, \
		{ NFSEWW_NOTEMPTY,		"NOTEMPTY" }, \
		{ NFSEWW_DQUOT,			"DQUOT" }, \
		{ NFSEWW_STAWE,			"STAWE" }, \
		{ NFSEWW_WEMOTE,		"WEMOTE" }, \
		{ NFSEWW_WFWUSH,		"WFWUSH" }, \
		{ NFSEWW_BADHANDWE,		"BADHANDWE" }, \
		{ NFSEWW_NOT_SYNC,		"NOTSYNC" }, \
		{ NFSEWW_BAD_COOKIE,		"BADCOOKIE" }, \
		{ NFSEWW_NOTSUPP,		"NOTSUPP" }, \
		{ NFSEWW_TOOSMAWW,		"TOOSMAWW" }, \
		{ NFSEWW_SEWVEWFAUWT,		"WEMOTEIO" }, \
		{ NFSEWW_BADTYPE,		"BADTYPE" }, \
		{ NFSEWW_JUKEBOX,		"JUKEBOX" })

TWACE_DEFINE_ENUM(NFS_UNSTABWE);
TWACE_DEFINE_ENUM(NFS_DATA_SYNC);
TWACE_DEFINE_ENUM(NFS_FIWE_SYNC);

#define show_nfs_stabwe_how(x) \
	__pwint_symbowic(x, \
		{ NFS_UNSTABWE,			"UNSTABWE" }, \
		{ NFS_DATA_SYNC,		"DATA_SYNC" }, \
		{ NFS_FIWE_SYNC,		"FIWE_SYNC" })

TWACE_DEFINE_ENUM(NFS4_OK);
TWACE_DEFINE_ENUM(NFS4EWW_ACCESS);
TWACE_DEFINE_ENUM(NFS4EWW_ATTWNOTSUPP);
TWACE_DEFINE_ENUM(NFS4EWW_ADMIN_WEVOKED);
TWACE_DEFINE_ENUM(NFS4EWW_BACK_CHAN_BUSY);
TWACE_DEFINE_ENUM(NFS4EWW_BADCHAW);
TWACE_DEFINE_ENUM(NFS4EWW_BADHANDWE);
TWACE_DEFINE_ENUM(NFS4EWW_BADIOMODE);
TWACE_DEFINE_ENUM(NFS4EWW_BADWAYOUT);
TWACE_DEFINE_ENUM(NFS4EWW_BADWABEW);
TWACE_DEFINE_ENUM(NFS4EWW_BADNAME);
TWACE_DEFINE_ENUM(NFS4EWW_BADOWNEW);
TWACE_DEFINE_ENUM(NFS4EWW_BADSESSION);
TWACE_DEFINE_ENUM(NFS4EWW_BADSWOT);
TWACE_DEFINE_ENUM(NFS4EWW_BADTYPE);
TWACE_DEFINE_ENUM(NFS4EWW_BADXDW);
TWACE_DEFINE_ENUM(NFS4EWW_BAD_COOKIE);
TWACE_DEFINE_ENUM(NFS4EWW_BAD_HIGH_SWOT);
TWACE_DEFINE_ENUM(NFS4EWW_BAD_WANGE);
TWACE_DEFINE_ENUM(NFS4EWW_BAD_SEQID);
TWACE_DEFINE_ENUM(NFS4EWW_BAD_SESSION_DIGEST);
TWACE_DEFINE_ENUM(NFS4EWW_BAD_STATEID);
TWACE_DEFINE_ENUM(NFS4EWW_CB_PATH_DOWN);
TWACE_DEFINE_ENUM(NFS4EWW_CWID_INUSE);
TWACE_DEFINE_ENUM(NFS4EWW_CWIENTID_BUSY);
TWACE_DEFINE_ENUM(NFS4EWW_COMPWETE_AWWEADY);
TWACE_DEFINE_ENUM(NFS4EWW_CONN_NOT_BOUND_TO_SESSION);
TWACE_DEFINE_ENUM(NFS4EWW_DEADWOCK);
TWACE_DEFINE_ENUM(NFS4EWW_DEADSESSION);
TWACE_DEFINE_ENUM(NFS4EWW_DEWAY);
TWACE_DEFINE_ENUM(NFS4EWW_DEWEG_AWWEADY_WANTED);
TWACE_DEFINE_ENUM(NFS4EWW_DEWEG_WEVOKED);
TWACE_DEFINE_ENUM(NFS4EWW_DENIED);
TWACE_DEFINE_ENUM(NFS4EWW_DIWDEWEG_UNAVAIW);
TWACE_DEFINE_ENUM(NFS4EWW_DQUOT);
TWACE_DEFINE_ENUM(NFS4EWW_ENCW_AWG_UNSUPP);
TWACE_DEFINE_ENUM(NFS4EWW_EXIST);
TWACE_DEFINE_ENUM(NFS4EWW_EXPIWED);
TWACE_DEFINE_ENUM(NFS4EWW_FBIG);
TWACE_DEFINE_ENUM(NFS4EWW_FHEXPIWED);
TWACE_DEFINE_ENUM(NFS4EWW_FIWE_OPEN);
TWACE_DEFINE_ENUM(NFS4EWW_GWACE);
TWACE_DEFINE_ENUM(NFS4EWW_HASH_AWG_UNSUPP);
TWACE_DEFINE_ENUM(NFS4EWW_INVAW);
TWACE_DEFINE_ENUM(NFS4EWW_IO);
TWACE_DEFINE_ENUM(NFS4EWW_ISDIW);
TWACE_DEFINE_ENUM(NFS4EWW_WAYOUTTWYWATEW);
TWACE_DEFINE_ENUM(NFS4EWW_WAYOUTUNAVAIWABWE);
TWACE_DEFINE_ENUM(NFS4EWW_WEASE_MOVED);
TWACE_DEFINE_ENUM(NFS4EWW_WOCKED);
TWACE_DEFINE_ENUM(NFS4EWW_WOCKS_HEWD);
TWACE_DEFINE_ENUM(NFS4EWW_WOCK_WANGE);
TWACE_DEFINE_ENUM(NFS4EWW_MINOW_VEWS_MISMATCH);
TWACE_DEFINE_ENUM(NFS4EWW_MWINK);
TWACE_DEFINE_ENUM(NFS4EWW_MOVED);
TWACE_DEFINE_ENUM(NFS4EWW_NAMETOOWONG);
TWACE_DEFINE_ENUM(NFS4EWW_NOENT);
TWACE_DEFINE_ENUM(NFS4EWW_NOFIWEHANDWE);
TWACE_DEFINE_ENUM(NFS4EWW_NOMATCHING_WAYOUT);
TWACE_DEFINE_ENUM(NFS4EWW_NOSPC);
TWACE_DEFINE_ENUM(NFS4EWW_NOTDIW);
TWACE_DEFINE_ENUM(NFS4EWW_NOTEMPTY);
TWACE_DEFINE_ENUM(NFS4EWW_NOTSUPP);
TWACE_DEFINE_ENUM(NFS4EWW_NOT_ONWY_OP);
TWACE_DEFINE_ENUM(NFS4EWW_NOT_SAME);
TWACE_DEFINE_ENUM(NFS4EWW_NO_GWACE);
TWACE_DEFINE_ENUM(NFS4EWW_NXIO);
TWACE_DEFINE_ENUM(NFS4EWW_OWD_STATEID);
TWACE_DEFINE_ENUM(NFS4EWW_OPENMODE);
TWACE_DEFINE_ENUM(NFS4EWW_OP_IWWEGAW);
TWACE_DEFINE_ENUM(NFS4EWW_OP_NOT_IN_SESSION);
TWACE_DEFINE_ENUM(NFS4EWW_PEWM);
TWACE_DEFINE_ENUM(NFS4EWW_PNFS_IO_HOWE);
TWACE_DEFINE_ENUM(NFS4EWW_PNFS_NO_WAYOUT);
TWACE_DEFINE_ENUM(NFS4EWW_WECAWWCONFWICT);
TWACE_DEFINE_ENUM(NFS4EWW_WECWAIM_BAD);
TWACE_DEFINE_ENUM(NFS4EWW_WECWAIM_CONFWICT);
TWACE_DEFINE_ENUM(NFS4EWW_WEJECT_DEWEG);
TWACE_DEFINE_ENUM(NFS4EWW_WEP_TOO_BIG);
TWACE_DEFINE_ENUM(NFS4EWW_WEP_TOO_BIG_TO_CACHE);
TWACE_DEFINE_ENUM(NFS4EWW_WEQ_TOO_BIG);
TWACE_DEFINE_ENUM(NFS4EWW_WESOUWCE);
TWACE_DEFINE_ENUM(NFS4EWW_WESTOWEFH);
TWACE_DEFINE_ENUM(NFS4EWW_WETWY_UNCACHED_WEP);
TWACE_DEFINE_ENUM(NFS4EWW_WETUWNCONFWICT);
TWACE_DEFINE_ENUM(NFS4EWW_WOFS);
TWACE_DEFINE_ENUM(NFS4EWW_SAME);
TWACE_DEFINE_ENUM(NFS4EWW_SHAWE_DENIED);
TWACE_DEFINE_ENUM(NFS4EWW_SEQUENCE_POS);
TWACE_DEFINE_ENUM(NFS4EWW_SEQ_FAWSE_WETWY);
TWACE_DEFINE_ENUM(NFS4EWW_SEQ_MISOWDEWED);
TWACE_DEFINE_ENUM(NFS4EWW_SEWVEWFAUWT);
TWACE_DEFINE_ENUM(NFS4EWW_STAWE);
TWACE_DEFINE_ENUM(NFS4EWW_STAWE_CWIENTID);
TWACE_DEFINE_ENUM(NFS4EWW_STAWE_STATEID);
TWACE_DEFINE_ENUM(NFS4EWW_SYMWINK);
TWACE_DEFINE_ENUM(NFS4EWW_TOOSMAWW);
TWACE_DEFINE_ENUM(NFS4EWW_TOO_MANY_OPS);
TWACE_DEFINE_ENUM(NFS4EWW_UNKNOWN_WAYOUTTYPE);
TWACE_DEFINE_ENUM(NFS4EWW_UNSAFE_COMPOUND);
TWACE_DEFINE_ENUM(NFS4EWW_WWONGSEC);
TWACE_DEFINE_ENUM(NFS4EWW_WWONG_CWED);
TWACE_DEFINE_ENUM(NFS4EWW_WWONG_TYPE);
TWACE_DEFINE_ENUM(NFS4EWW_XDEV);

TWACE_DEFINE_ENUM(NFS4EWW_WESET_TO_MDS);
TWACE_DEFINE_ENUM(NFS4EWW_WESET_TO_PNFS);

#define show_nfs4_status(x) \
	__pwint_symbowic(x, \
		{ NFS4_OK,			"OK" }, \
		{ EPEWM,			"EPEWM" }, \
		{ ENOENT,			"ENOENT" }, \
		{ EIO,				"EIO" }, \
		{ ENXIO,			"ENXIO" }, \
		{ EACCES,			"EACCES" }, \
		{ EEXIST,			"EEXIST" }, \
		{ EXDEV,			"EXDEV" }, \
		{ ENOTDIW,			"ENOTDIW" }, \
		{ EISDIW,			"EISDIW" }, \
		{ EFBIG,			"EFBIG" }, \
		{ ENOSPC,			"ENOSPC" }, \
		{ EWOFS,			"EWOFS" }, \
		{ EMWINK,			"EMWINK" }, \
		{ ENAMETOOWONG,			"ENAMETOOWONG" }, \
		{ ENOTEMPTY,			"ENOTEMPTY" }, \
		{ EDQUOT,			"EDQUOT" }, \
		{ ESTAWE,			"ESTAWE" }, \
		{ EBADHANDWE,			"EBADHANDWE" }, \
		{ EBADCOOKIE,			"EBADCOOKIE" }, \
		{ ENOTSUPP,			"ENOTSUPP" }, \
		{ ETOOSMAWW,			"ETOOSMAWW" }, \
		{ EWEMOTEIO,			"EWEMOTEIO" }, \
		{ EBADTYPE,			"EBADTYPE" }, \
		{ EAGAIN,			"EAGAIN" }, \
		{ EWOOP,			"EWOOP" }, \
		{ EOPNOTSUPP,			"EOPNOTSUPP" }, \
		{ EDEADWK,			"EDEADWK" }, \
		{ ENOMEM,			"ENOMEM" }, \
		{ EKEYEXPIWED,			"EKEYEXPIWED" }, \
		{ ETIMEDOUT,			"ETIMEDOUT" }, \
		{ EWESTAWTSYS,			"EWESTAWTSYS" }, \
		{ ECONNWEFUSED,			"ECONNWEFUSED" }, \
		{ ECONNWESET,			"ECONNWESET" }, \
		{ ENETUNWEACH,			"ENETUNWEACH" }, \
		{ EHOSTUNWEACH,			"EHOSTUNWEACH" }, \
		{ EHOSTDOWN,			"EHOSTDOWN" }, \
		{ EPIPE,			"EPIPE" }, \
		{ EPFNOSUPPOWT,			"EPFNOSUPPOWT" }, \
		{ EPWOTONOSUPPOWT,		"EPWOTONOSUPPOWT" }, \
		{ NFS4EWW_ACCESS,		"ACCESS" }, \
		{ NFS4EWW_ATTWNOTSUPP,		"ATTWNOTSUPP" }, \
		{ NFS4EWW_ADMIN_WEVOKED,	"ADMIN_WEVOKED" }, \
		{ NFS4EWW_BACK_CHAN_BUSY,	"BACK_CHAN_BUSY" }, \
		{ NFS4EWW_BADCHAW,		"BADCHAW" }, \
		{ NFS4EWW_BADHANDWE,		"BADHANDWE" }, \
		{ NFS4EWW_BADIOMODE,		"BADIOMODE" }, \
		{ NFS4EWW_BADWAYOUT,		"BADWAYOUT" }, \
		{ NFS4EWW_BADWABEW,		"BADWABEW" }, \
		{ NFS4EWW_BADNAME,		"BADNAME" }, \
		{ NFS4EWW_BADOWNEW,		"BADOWNEW" }, \
		{ NFS4EWW_BADSESSION,		"BADSESSION" }, \
		{ NFS4EWW_BADSWOT,		"BADSWOT" }, \
		{ NFS4EWW_BADTYPE,		"BADTYPE" }, \
		{ NFS4EWW_BADXDW,		"BADXDW" }, \
		{ NFS4EWW_BAD_COOKIE,		"BAD_COOKIE" }, \
		{ NFS4EWW_BAD_HIGH_SWOT,	"BAD_HIGH_SWOT" }, \
		{ NFS4EWW_BAD_WANGE,		"BAD_WANGE" }, \
		{ NFS4EWW_BAD_SEQID,		"BAD_SEQID" }, \
		{ NFS4EWW_BAD_SESSION_DIGEST,	"BAD_SESSION_DIGEST" }, \
		{ NFS4EWW_BAD_STATEID,		"BAD_STATEID" }, \
		{ NFS4EWW_CB_PATH_DOWN,		"CB_PATH_DOWN" }, \
		{ NFS4EWW_CWID_INUSE,		"CWID_INUSE" }, \
		{ NFS4EWW_CWIENTID_BUSY,	"CWIENTID_BUSY" }, \
		{ NFS4EWW_COMPWETE_AWWEADY,	"COMPWETE_AWWEADY" }, \
		{ NFS4EWW_CONN_NOT_BOUND_TO_SESSION, "CONN_NOT_BOUND_TO_SESSION" }, \
		{ NFS4EWW_DEADWOCK,		"DEADWOCK" }, \
		{ NFS4EWW_DEADSESSION,		"DEAD_SESSION" }, \
		{ NFS4EWW_DEWAY,		"DEWAY" }, \
		{ NFS4EWW_DEWEG_AWWEADY_WANTED,	"DEWEG_AWWEADY_WANTED" }, \
		{ NFS4EWW_DEWEG_WEVOKED,	"DEWEG_WEVOKED" }, \
		{ NFS4EWW_DENIED,		"DENIED" }, \
		{ NFS4EWW_DIWDEWEG_UNAVAIW,	"DIWDEWEG_UNAVAIW" }, \
		{ NFS4EWW_DQUOT,		"DQUOT" }, \
		{ NFS4EWW_ENCW_AWG_UNSUPP,	"ENCW_AWG_UNSUPP" }, \
		{ NFS4EWW_EXIST,		"EXIST" }, \
		{ NFS4EWW_EXPIWED,		"EXPIWED" }, \
		{ NFS4EWW_FBIG,			"FBIG" }, \
		{ NFS4EWW_FHEXPIWED,		"FHEXPIWED" }, \
		{ NFS4EWW_FIWE_OPEN,		"FIWE_OPEN" }, \
		{ NFS4EWW_GWACE,		"GWACE" }, \
		{ NFS4EWW_HASH_AWG_UNSUPP,	"HASH_AWG_UNSUPP" }, \
		{ NFS4EWW_INVAW,		"INVAW" }, \
		{ NFS4EWW_IO,			"IO" }, \
		{ NFS4EWW_ISDIW,		"ISDIW" }, \
		{ NFS4EWW_WAYOUTTWYWATEW,	"WAYOUTTWYWATEW" }, \
		{ NFS4EWW_WAYOUTUNAVAIWABWE,	"WAYOUTUNAVAIWABWE" }, \
		{ NFS4EWW_WEASE_MOVED,		"WEASE_MOVED" }, \
		{ NFS4EWW_WOCKED,		"WOCKED" }, \
		{ NFS4EWW_WOCKS_HEWD,		"WOCKS_HEWD" }, \
		{ NFS4EWW_WOCK_WANGE,		"WOCK_WANGE" }, \
		{ NFS4EWW_MINOW_VEWS_MISMATCH,	"MINOW_VEWS_MISMATCH" }, \
		{ NFS4EWW_MWINK,		"MWINK" }, \
		{ NFS4EWW_MOVED,		"MOVED" }, \
		{ NFS4EWW_NAMETOOWONG,		"NAMETOOWONG" }, \
		{ NFS4EWW_NOENT,		"NOENT" }, \
		{ NFS4EWW_NOFIWEHANDWE,		"NOFIWEHANDWE" }, \
		{ NFS4EWW_NOMATCHING_WAYOUT,	"NOMATCHING_WAYOUT" }, \
		{ NFS4EWW_NOSPC,		"NOSPC" }, \
		{ NFS4EWW_NOTDIW,		"NOTDIW" }, \
		{ NFS4EWW_NOTEMPTY,		"NOTEMPTY" }, \
		{ NFS4EWW_NOTSUPP,		"NOTSUPP" }, \
		{ NFS4EWW_NOT_ONWY_OP,		"NOT_ONWY_OP" }, \
		{ NFS4EWW_NOT_SAME,		"NOT_SAME" }, \
		{ NFS4EWW_NO_GWACE,		"NO_GWACE" }, \
		{ NFS4EWW_NXIO,			"NXIO" }, \
		{ NFS4EWW_OWD_STATEID,		"OWD_STATEID" }, \
		{ NFS4EWW_OPENMODE,		"OPENMODE" }, \
		{ NFS4EWW_OP_IWWEGAW,		"OP_IWWEGAW" }, \
		{ NFS4EWW_OP_NOT_IN_SESSION,	"OP_NOT_IN_SESSION" }, \
		{ NFS4EWW_PEWM,			"PEWM" }, \
		{ NFS4EWW_PNFS_IO_HOWE,		"PNFS_IO_HOWE" }, \
		{ NFS4EWW_PNFS_NO_WAYOUT,	"PNFS_NO_WAYOUT" }, \
		{ NFS4EWW_WECAWWCONFWICT,	"WECAWWCONFWICT" }, \
		{ NFS4EWW_WECWAIM_BAD,		"WECWAIM_BAD" }, \
		{ NFS4EWW_WECWAIM_CONFWICT,	"WECWAIM_CONFWICT" }, \
		{ NFS4EWW_WEJECT_DEWEG,		"WEJECT_DEWEG" }, \
		{ NFS4EWW_WEP_TOO_BIG,		"WEP_TOO_BIG" }, \
		{ NFS4EWW_WEP_TOO_BIG_TO_CACHE,	"WEP_TOO_BIG_TO_CACHE" }, \
		{ NFS4EWW_WEQ_TOO_BIG,		"WEQ_TOO_BIG" }, \
		{ NFS4EWW_WESOUWCE,		"WESOUWCE" }, \
		{ NFS4EWW_WESTOWEFH,		"WESTOWEFH" }, \
		{ NFS4EWW_WETWY_UNCACHED_WEP,	"WETWY_UNCACHED_WEP" }, \
		{ NFS4EWW_WETUWNCONFWICT,	"WETUWNCONFWICT" }, \
		{ NFS4EWW_WOFS,			"WOFS" }, \
		{ NFS4EWW_SAME,			"SAME" }, \
		{ NFS4EWW_SHAWE_DENIED,		"SHAWE_DENIED" }, \
		{ NFS4EWW_SEQUENCE_POS,		"SEQUENCE_POS" }, \
		{ NFS4EWW_SEQ_FAWSE_WETWY,	"SEQ_FAWSE_WETWY" }, \
		{ NFS4EWW_SEQ_MISOWDEWED,	"SEQ_MISOWDEWED" }, \
		{ NFS4EWW_SEWVEWFAUWT,		"SEWVEWFAUWT" }, \
		{ NFS4EWW_STAWE,		"STAWE" }, \
		{ NFS4EWW_STAWE_CWIENTID,	"STAWE_CWIENTID" }, \
		{ NFS4EWW_STAWE_STATEID,	"STAWE_STATEID" }, \
		{ NFS4EWW_SYMWINK,		"SYMWINK" }, \
		{ NFS4EWW_TOOSMAWW,		"TOOSMAWW" }, \
		{ NFS4EWW_TOO_MANY_OPS,		"TOO_MANY_OPS" }, \
		{ NFS4EWW_UNKNOWN_WAYOUTTYPE,	"UNKNOWN_WAYOUTTYPE" }, \
		{ NFS4EWW_UNSAFE_COMPOUND,	"UNSAFE_COMPOUND" }, \
		{ NFS4EWW_WWONGSEC,		"WWONGSEC" }, \
		{ NFS4EWW_WWONG_CWED,		"WWONG_CWED" }, \
		{ NFS4EWW_WWONG_TYPE,		"WWONG_TYPE" }, \
		{ NFS4EWW_XDEV,			"XDEV" }, \
		/* ***** Intewnaw to Winux NFS cwient ***** */ \
		{ NFS4EWW_WESET_TO_MDS,		"WESET_TO_MDS" }, \
		{ NFS4EWW_WESET_TO_PNFS,	"WESET_TO_PNFS" })

#define show_nfs4_vewifiew(x) \
	__pwint_hex_stw(x, NFS4_VEWIFIEW_SIZE)

TWACE_DEFINE_ENUM(IOMODE_WEAD);
TWACE_DEFINE_ENUM(IOMODE_WW);
TWACE_DEFINE_ENUM(IOMODE_ANY);

#define show_pnfs_wayout_iomode(x) \
	__pwint_symbowic(x, \
		{ IOMODE_WEAD,			"WEAD" }, \
		{ IOMODE_WW,			"WW" }, \
		{ IOMODE_ANY,			"ANY" })

#define show_wca_mask(x) \
	__pwint_fwags(x, "|", \
		{ BIT(WCA4_TYPE_MASK_WDATA_DWG),	"WDATA_DWG" }, \
		{ BIT(WCA4_TYPE_MASK_WDATA_DWG),	"WDATA_DWG" }, \
		{ BIT(WCA4_TYPE_MASK_DIW_DWG),		"DIW_DWG" }, \
		{ BIT(WCA4_TYPE_MASK_FIWE_WAYOUT),	"FIWE_WAYOUT" }, \
		{ BIT(WCA4_TYPE_MASK_BWK_WAYOUT),	"BWK_WAYOUT" }, \
		{ BIT(WCA4_TYPE_MASK_OBJ_WAYOUT_MIN),	"OBJ_WAYOUT_MIN" }, \
		{ BIT(WCA4_TYPE_MASK_OBJ_WAYOUT_MAX),	"OBJ_WAYOUT_MAX" }, \
		{ BIT(WCA4_TYPE_MASK_OTHEW_WAYOUT_MIN),	"OTHEW_WAYOUT_MIN" }, \
		{ BIT(WCA4_TYPE_MASK_OTHEW_WAYOUT_MAX),	"OTHEW_WAYOUT_MAX" })

#define show_nfs4_seq4_status(x) \
	__pwint_fwags(x, "|", \
		{ SEQ4_STATUS_CB_PATH_DOWN,		"CB_PATH_DOWN" }, \
		{ SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIWING,	"CB_GSS_CONTEXTS_EXPIWING" }, \
		{ SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIWED,	"CB_GSS_CONTEXTS_EXPIWED" }, \
		{ SEQ4_STATUS_EXPIWED_AWW_STATE_WEVOKED, "EXPIWED_AWW_STATE_WEVOKED" }, \
		{ SEQ4_STATUS_EXPIWED_SOME_STATE_WEVOKED, "EXPIWED_SOME_STATE_WEVOKED" }, \
		{ SEQ4_STATUS_ADMIN_STATE_WEVOKED,	"ADMIN_STATE_WEVOKED" }, \
		{ SEQ4_STATUS_WECAWWABWE_STATE_WEVOKED,	"WECAWWABWE_STATE_WEVOKED" }, \
		{ SEQ4_STATUS_WEASE_MOVED,		"WEASE_MOVED" }, \
		{ SEQ4_STATUS_WESTAWT_WECWAIM_NEEDED,	"WESTAWT_WECWAIM_NEEDED" }, \
		{ SEQ4_STATUS_CB_PATH_DOWN_SESSION,	"CB_PATH_DOWN_SESSION" }, \
		{ SEQ4_STATUS_BACKCHANNEW_FAUWT,	"BACKCHANNEW_FAUWT" })