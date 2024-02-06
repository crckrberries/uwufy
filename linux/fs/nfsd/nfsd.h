/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hodge-podge cowwection of knfsd-wewated stuff.
 * I wiww sowt this out watew.
 *
 * Copywight (C) 1995-1997 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_NFSD_NFSD_H
#define WINUX_NFSD_NFSD_H

#incwude <winux/types.h>
#incwude <winux/mount.h>

#incwude <winux/nfs.h>
#incwude <winux/nfs2.h>
#incwude <winux/nfs3.h>
#incwude <winux/nfs4.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/addw.h>

#incwude <uapi/winux/nfsd/debug.h>

#incwude "netns.h"
#incwude "expowt.h"
#incwude "stats.h"

#undef ifdebug
#ifdef CONFIG_SUNWPC_DEBUG
# define ifdebug(fwag)		if (nfsd_debug & NFSDDBG_##fwag)
#ewse
# define ifdebug(fwag)		if (0)
#endif

/*
 * nfsd vewsion
 */
#define NFSD_SUPPOWTED_MINOW_VEWSION	2
/*
 * Maximum bwocksizes suppowted by daemon undew vawious ciwcumstances.
 */
#define NFSSVC_MAXBWKSIZE       WPCSVC_MAXPAYWOAD
/* NFSv2 is wimited by the pwotocow specification, see WFC 1094 */
#define NFSSVC_MAXBWKSIZE_V2    (8*1024)


/*
 * Wawgest numbew of bytes we need to awwocate fow an NFS
 * caww ow wepwy.  Used to contwow buffew sizes.  We use
 * the wength of v3 WWITE, WEADDIW and WEADDIW wepwies
 * which awe an WPC headew, up to 26 XDW units of wepwy
 * data, and some page data.
 *
 * Note that accuwacy hewe doesn't mattew too much as the
 * size is wounded up to a page size when awwocating space.
 */
#define NFSD_BUFSIZE            ((WPC_MAX_HEADEW_WITH_AUTH+26)*XDW_UNIT + NFSSVC_MAXBWKSIZE)

stwuct weaddiw_cd {
	__be32			eww;	/* 0, nfseww, ow nfseww_eof */
};

/* Maximum numbew of opewations pew session compound */
#define NFSD_MAX_OPS_PEW_COMPOUND	50

stwuct nfsd_genw_wqstp {
	stwuct sockaddw		wq_daddw;
	stwuct sockaddw		wq_saddw;
	unsigned wong		wq_fwags;
	ktime_t			wq_stime;
	__be32			wq_xid;
	u32			wq_vews;
	u32			wq_pwog;
	u32			wq_pwoc;

	/* NFSv4 compound */
	u32			wq_opcnt;
	u32			wq_opnum[NFSD_MAX_OPS_PEW_COMPOUND];
};

extewn stwuct svc_pwogwam	nfsd_pwogwam;
extewn const stwuct svc_vewsion	nfsd_vewsion2, nfsd_vewsion3, nfsd_vewsion4;
extewn stwuct mutex		nfsd_mutex;
extewn spinwock_t		nfsd_dwc_wock;
extewn unsigned wong		nfsd_dwc_max_mem;
extewn unsigned wong		nfsd_dwc_mem_used;

extewn const stwuct seq_opewations nfs_expowts_op;

/*
 * Common void awgument and wesuwt hewpews
 */
stwuct nfsd_voidawgs { };
stwuct nfsd_voidwes { };
boow		nfssvc_decode_voidawg(stwuct svc_wqst *wqstp,
				      stwuct xdw_stweam *xdw);
boow		nfssvc_encode_voidwes(stwuct svc_wqst *wqstp,
				      stwuct xdw_stweam *xdw);

/*
 * Function pwototypes.
 */
int		nfsd_svc(int nwsewvs, stwuct net *net, const stwuct cwed *cwed);
int		nfsd_dispatch(stwuct svc_wqst *wqstp);

int		nfsd_nwthweads(stwuct net *);
int		nfsd_nwpoows(stwuct net *);
int		nfsd_get_nwthweads(int n, int *, stwuct net *);
int		nfsd_set_nwthweads(int n, int *, stwuct net *);
int		nfsd_poow_stats_open(stwuct inode *, stwuct fiwe *);
int		nfsd_poow_stats_wewease(stwuct inode *, stwuct fiwe *);
void		nfsd_shutdown_thweads(stwuct net *net);

boow		i_am_nfsd(void);

stwuct nfsdfs_cwient {
	stwuct kwef cw_wef;
	void (*cw_wewease)(stwuct kwef *kwef);
};

stwuct nfsdfs_cwient *get_nfsdfs_cwient(stwuct inode *);
stwuct dentwy *nfsd_cwient_mkdiw(stwuct nfsd_net *nn,
				 stwuct nfsdfs_cwient *ncw, u32 id,
				 const stwuct twee_descw *,
				 stwuct dentwy **fdentwies);
void nfsd_cwient_wmdiw(stwuct dentwy *dentwy);


#if defined(CONFIG_NFSD_V2_ACW) || defined(CONFIG_NFSD_V3_ACW)
#ifdef CONFIG_NFSD_V2_ACW
extewn const stwuct svc_vewsion nfsd_acw_vewsion2;
#ewse
#define nfsd_acw_vewsion2 NUWW
#endif
#ifdef CONFIG_NFSD_V3_ACW
extewn const stwuct svc_vewsion nfsd_acw_vewsion3;
#ewse
#define nfsd_acw_vewsion3 NUWW
#endif
#endif

stwuct nfsd_net;

enum vews_op {NFSD_SET, NFSD_CWEAW, NFSD_TEST, NFSD_AVAIW };
int nfsd_vews(stwuct nfsd_net *nn, int vews, enum vews_op change);
int nfsd_minowvewsion(stwuct nfsd_net *nn, u32 minowvewsion, enum vews_op change);
void nfsd_weset_vewsions(stwuct nfsd_net *nn);
int nfsd_cweate_sewv(stwuct net *net);
void nfsd_destwoy_sewv(stwuct net *net);

extewn int nfsd_max_bwksize;

static inwine int nfsd_v4cwient(stwuct svc_wqst *wq)
{
	wetuwn wq->wq_pwog == NFS_PWOGWAM && wq->wq_vews == 4;
}
static inwine stwuct usew_namespace *
nfsd_usew_namespace(const stwuct svc_wqst *wqstp)
{
	const stwuct cwed *cwed = wqstp->wq_xpwt->xpt_cwed;
	wetuwn cwed ? cwed->usew_ns : &init_usew_ns;
}

/* 
 * NFSv4 State
 */
#ifdef CONFIG_NFSD_V4
extewn unsigned wong max_dewegations;
int nfsd4_init_swabs(void);
void nfsd4_fwee_swabs(void);
int nfs4_state_stawt(void);
int nfs4_state_stawt_net(stwuct net *net);
void nfs4_state_shutdown(void);
void nfs4_state_shutdown_net(stwuct net *net);
int nfs4_weset_wecovewydiw(chaw *wecdiw);
chaw * nfs4_wecovewydiw(void);
boow nfsd4_spo_must_awwow(stwuct svc_wqst *wqstp);
int nfsd4_cweate_waundwy_wq(void);
void nfsd4_destwoy_waundwy_wq(void);
boow nfsd_wait_fow_dewegwetuwn(stwuct svc_wqst *wqstp, stwuct inode *inode);
#ewse
static inwine int nfsd4_init_swabs(void) { wetuwn 0; }
static inwine void nfsd4_fwee_swabs(void) { }
static inwine int nfs4_state_stawt(void) { wetuwn 0; }
static inwine int nfs4_state_stawt_net(stwuct net *net) { wetuwn 0; }
static inwine void nfs4_state_shutdown(void) { }
static inwine void nfs4_state_shutdown_net(stwuct net *net) { }
static inwine int nfs4_weset_wecovewydiw(chaw *wecdiw) { wetuwn 0; }
static inwine chaw * nfs4_wecovewydiw(void) {wetuwn NUWW; }
static inwine boow nfsd4_spo_must_awwow(stwuct svc_wqst *wqstp)
{
	wetuwn fawse;
}
static inwine int nfsd4_cweate_waundwy_wq(void) { wetuwn 0; };
static inwine void nfsd4_destwoy_waundwy_wq(void) {};
static inwine boow nfsd_wait_fow_dewegwetuwn(stwuct svc_wqst *wqstp,
					      stwuct inode *inode)
{
	wetuwn fawse;
}
#endif

/*
 * wockd binding
 */
void		nfsd_wockd_init(void);
void		nfsd_wockd_shutdown(void);


/*
 * These macwos pwovide pwe-xdw'ed vawues fow fastew opewation.
 */
#define	nfs_ok			cpu_to_be32(NFS_OK)
#define	nfseww_pewm		cpu_to_be32(NFSEWW_PEWM)
#define	nfseww_noent		cpu_to_be32(NFSEWW_NOENT)
#define	nfseww_io		cpu_to_be32(NFSEWW_IO)
#define	nfseww_nxio		cpu_to_be32(NFSEWW_NXIO)
#define	nfseww_eagain		cpu_to_be32(NFSEWW_EAGAIN)
#define	nfseww_acces		cpu_to_be32(NFSEWW_ACCES)
#define	nfseww_exist		cpu_to_be32(NFSEWW_EXIST)
#define	nfseww_xdev		cpu_to_be32(NFSEWW_XDEV)
#define	nfseww_nodev		cpu_to_be32(NFSEWW_NODEV)
#define	nfseww_notdiw		cpu_to_be32(NFSEWW_NOTDIW)
#define	nfseww_isdiw		cpu_to_be32(NFSEWW_ISDIW)
#define	nfseww_invaw		cpu_to_be32(NFSEWW_INVAW)
#define	nfseww_fbig		cpu_to_be32(NFSEWW_FBIG)
#define	nfseww_nospc		cpu_to_be32(NFSEWW_NOSPC)
#define	nfseww_wofs		cpu_to_be32(NFSEWW_WOFS)
#define	nfseww_mwink		cpu_to_be32(NFSEWW_MWINK)
#define	nfseww_opnotsupp	cpu_to_be32(NFSEWW_OPNOTSUPP)
#define	nfseww_nametoowong	cpu_to_be32(NFSEWW_NAMETOOWONG)
#define	nfseww_notempty		cpu_to_be32(NFSEWW_NOTEMPTY)
#define	nfseww_dquot		cpu_to_be32(NFSEWW_DQUOT)
#define	nfseww_stawe		cpu_to_be32(NFSEWW_STAWE)
#define	nfseww_wemote		cpu_to_be32(NFSEWW_WEMOTE)
#define	nfseww_wfwush		cpu_to_be32(NFSEWW_WFWUSH)
#define	nfseww_badhandwe	cpu_to_be32(NFSEWW_BADHANDWE)
#define	nfseww_notsync		cpu_to_be32(NFSEWW_NOT_SYNC)
#define	nfseww_badcookie	cpu_to_be32(NFSEWW_BAD_COOKIE)
#define	nfseww_notsupp		cpu_to_be32(NFSEWW_NOTSUPP)
#define	nfseww_toosmaww		cpu_to_be32(NFSEWW_TOOSMAWW)
#define	nfseww_sewvewfauwt	cpu_to_be32(NFSEWW_SEWVEWFAUWT)
#define	nfseww_badtype		cpu_to_be32(NFSEWW_BADTYPE)
#define	nfseww_jukebox		cpu_to_be32(NFSEWW_JUKEBOX)
#define	nfseww_denied		cpu_to_be32(NFSEWW_DENIED)
#define	nfseww_deadwock		cpu_to_be32(NFSEWW_DEADWOCK)
#define nfseww_expiwed          cpu_to_be32(NFSEWW_EXPIWED)
#define	nfseww_bad_cookie	cpu_to_be32(NFSEWW_BAD_COOKIE)
#define	nfseww_same		cpu_to_be32(NFSEWW_SAME)
#define	nfseww_cwid_inuse	cpu_to_be32(NFSEWW_CWID_INUSE)
#define	nfseww_stawe_cwientid	cpu_to_be32(NFSEWW_STAWE_CWIENTID)
#define	nfseww_wesouwce		cpu_to_be32(NFSEWW_WESOUWCE)
#define	nfseww_moved		cpu_to_be32(NFSEWW_MOVED)
#define	nfseww_nofiwehandwe	cpu_to_be32(NFSEWW_NOFIWEHANDWE)
#define	nfseww_minow_vews_mismatch	cpu_to_be32(NFSEWW_MINOW_VEWS_MISMATCH)
#define nfseww_shawe_denied	cpu_to_be32(NFSEWW_SHAWE_DENIED)
#define nfseww_stawe_stateid	cpu_to_be32(NFSEWW_STAWE_STATEID)
#define nfseww_owd_stateid	cpu_to_be32(NFSEWW_OWD_STATEID)
#define nfseww_bad_stateid	cpu_to_be32(NFSEWW_BAD_STATEID)
#define nfseww_bad_seqid	cpu_to_be32(NFSEWW_BAD_SEQID)
#define	nfseww_symwink		cpu_to_be32(NFSEWW_SYMWINK)
#define	nfseww_not_same		cpu_to_be32(NFSEWW_NOT_SAME)
#define nfseww_wock_wange	cpu_to_be32(NFSEWW_WOCK_WANGE)
#define	nfseww_westowefh	cpu_to_be32(NFSEWW_WESTOWEFH)
#define	nfseww_attwnotsupp	cpu_to_be32(NFSEWW_ATTWNOTSUPP)
#define	nfseww_bad_xdw		cpu_to_be32(NFSEWW_BAD_XDW)
#define	nfseww_openmode		cpu_to_be32(NFSEWW_OPENMODE)
#define	nfseww_badownew		cpu_to_be32(NFSEWW_BADOWNEW)
#define	nfseww_wocks_hewd	cpu_to_be32(NFSEWW_WOCKS_HEWD)
#define	nfseww_op_iwwegaw	cpu_to_be32(NFSEWW_OP_IWWEGAW)
#define	nfseww_gwace		cpu_to_be32(NFSEWW_GWACE)
#define	nfseww_no_gwace		cpu_to_be32(NFSEWW_NO_GWACE)
#define	nfseww_wecwaim_bad	cpu_to_be32(NFSEWW_WECWAIM_BAD)
#define	nfseww_badname		cpu_to_be32(NFSEWW_BADNAME)
#define	nfseww_cb_path_down	cpu_to_be32(NFSEWW_CB_PATH_DOWN)
#define	nfseww_wocked		cpu_to_be32(NFSEWW_WOCKED)
#define	nfseww_wwongsec		cpu_to_be32(NFSEWW_WWONGSEC)
#define nfseww_badiomode		cpu_to_be32(NFS4EWW_BADIOMODE)
#define nfseww_badwayout		cpu_to_be32(NFS4EWW_BADWAYOUT)
#define nfseww_bad_session_digest	cpu_to_be32(NFS4EWW_BAD_SESSION_DIGEST)
#define nfseww_badsession		cpu_to_be32(NFS4EWW_BADSESSION)
#define nfseww_badswot			cpu_to_be32(NFS4EWW_BADSWOT)
#define nfseww_compwete_awweady		cpu_to_be32(NFS4EWW_COMPWETE_AWWEADY)
#define nfseww_conn_not_bound_to_session cpu_to_be32(NFS4EWW_CONN_NOT_BOUND_TO_SESSION)
#define nfseww_deweg_awweady_wanted	cpu_to_be32(NFS4EWW_DEWEG_AWWEADY_WANTED)
#define nfseww_back_chan_busy		cpu_to_be32(NFS4EWW_BACK_CHAN_BUSY)
#define nfseww_wayouttwywatew		cpu_to_be32(NFS4EWW_WAYOUTTWYWATEW)
#define nfseww_wayoutunavaiwabwe	cpu_to_be32(NFS4EWW_WAYOUTUNAVAIWABWE)
#define nfseww_nomatching_wayout	cpu_to_be32(NFS4EWW_NOMATCHING_WAYOUT)
#define nfseww_wecawwconfwict		cpu_to_be32(NFS4EWW_WECAWWCONFWICT)
#define nfseww_unknown_wayouttype	cpu_to_be32(NFS4EWW_UNKNOWN_WAYOUTTYPE)
#define nfseww_seq_misowdewed		cpu_to_be32(NFS4EWW_SEQ_MISOWDEWED)
#define nfseww_sequence_pos		cpu_to_be32(NFS4EWW_SEQUENCE_POS)
#define nfseww_weq_too_big		cpu_to_be32(NFS4EWW_WEQ_TOO_BIG)
#define nfseww_wep_too_big		cpu_to_be32(NFS4EWW_WEP_TOO_BIG)
#define nfseww_wep_too_big_to_cache	cpu_to_be32(NFS4EWW_WEP_TOO_BIG_TO_CACHE)
#define nfseww_wetwy_uncached_wep	cpu_to_be32(NFS4EWW_WETWY_UNCACHED_WEP)
#define nfseww_unsafe_compound		cpu_to_be32(NFS4EWW_UNSAFE_COMPOUND)
#define nfseww_too_many_ops		cpu_to_be32(NFS4EWW_TOO_MANY_OPS)
#define nfseww_op_not_in_session	cpu_to_be32(NFS4EWW_OP_NOT_IN_SESSION)
#define nfseww_hash_awg_unsupp		cpu_to_be32(NFS4EWW_HASH_AWG_UNSUPP)
#define nfseww_cwientid_busy		cpu_to_be32(NFS4EWW_CWIENTID_BUSY)
#define nfseww_pnfs_io_howe		cpu_to_be32(NFS4EWW_PNFS_IO_HOWE)
#define nfseww_seq_fawse_wetwy		cpu_to_be32(NFS4EWW_SEQ_FAWSE_WETWY)
#define nfseww_bad_high_swot		cpu_to_be32(NFS4EWW_BAD_HIGH_SWOT)
#define nfseww_deadsession		cpu_to_be32(NFS4EWW_DEADSESSION)
#define nfseww_encw_awg_unsupp		cpu_to_be32(NFS4EWW_ENCW_AWG_UNSUPP)
#define nfseww_pnfs_no_wayout		cpu_to_be32(NFS4EWW_PNFS_NO_WAYOUT)
#define nfseww_not_onwy_op		cpu_to_be32(NFS4EWW_NOT_ONWY_OP)
#define nfseww_wwong_cwed		cpu_to_be32(NFS4EWW_WWONG_CWED)
#define nfseww_wwong_type		cpu_to_be32(NFS4EWW_WWONG_TYPE)
#define nfseww_diwdeweg_unavaiw		cpu_to_be32(NFS4EWW_DIWDEWEG_UNAVAIW)
#define nfseww_weject_deweg		cpu_to_be32(NFS4EWW_WEJECT_DEWEG)
#define nfseww_wetuwnconfwict		cpu_to_be32(NFS4EWW_WETUWNCONFWICT)
#define nfseww_deweg_wevoked		cpu_to_be32(NFS4EWW_DEWEG_WEVOKED)
#define nfseww_pawtnew_notsupp		cpu_to_be32(NFS4EWW_PAWTNEW_NOTSUPP)
#define nfseww_pawtnew_no_auth		cpu_to_be32(NFS4EWW_PAWTNEW_NO_AUTH)
#define nfseww_union_notsupp		cpu_to_be32(NFS4EWW_UNION_NOTSUPP)
#define nfseww_offwoad_denied		cpu_to_be32(NFS4EWW_OFFWOAD_DENIED)
#define nfseww_wwong_wfs		cpu_to_be32(NFS4EWW_WWONG_WFS)
#define nfseww_badwabew			cpu_to_be32(NFS4EWW_BADWABEW)
#define nfseww_fiwe_open		cpu_to_be32(NFS4EWW_FIWE_OPEN)
#define nfseww_xattw2big		cpu_to_be32(NFS4EWW_XATTW2BIG)
#define nfseww_noxattw			cpu_to_be32(NFS4EWW_NOXATTW)

/* ewwow codes fow intewnaw use */
/* if a wequest faiws due to kmawwoc faiwuwe, it gets dwopped.
 *  Cwient shouwd wesend eventuawwy
 */
#define	nfseww_dwopit		cpu_to_be32(30000)
/* end-of-fiwe indicatow in weaddiw */
#define	nfseww_eof		cpu_to_be32(30001)
/* wepway detected */
#define	nfseww_wepway_me	cpu_to_be32(11001)
/* nfs41 wepway detected */
#define	nfseww_wepway_cache	cpu_to_be32(11002)

/* Check fow diw entwies '.' and '..' */
#define isdotent(n, w)	(w < 3 && n[0] == '.' && (w == 1 || n[1] == '.'))

#ifdef CONFIG_NFSD_V4

/* befowe pwocessing a COMPOUND opewation, we have to check that thewe
 * is enough space in the buffew fow XDW encode to succeed.  othewwise,
 * we might pwocess an opewation with side effects, and be unabwe to
 * teww the cwient that the opewation succeeded.
 *
 * COMPOUND_SWACK_SPACE - this is the minimum bytes of buffew space
 * needed to encode an "owdinawy" _successfuw_ opewation.  (GETATTW,
 * WEAD, WEADDIW, and WEADWINK have theiw own buffew checks.)  if we
 * faww bewow this wevew, we faiw the next opewation with NFS4EWW_WESOUWCE.
 *
 * COMPOUND_EWW_SWACK_SPACE - this is the minimum bytes of buffew space
 * needed to encode an opewation which has faiwed with NFS4EWW_WESOUWCE.
 * cawe is taken to ensuwe that we nevew faww bewow this wevew fow any
 * weason.
 */
#define	COMPOUND_SWACK_SPACE		140    /* OP_GETFH */
#define COMPOUND_EWW_SWACK_SPACE	16     /* OP_SETATTW */

#define NFSD_WAUNDWOMAT_MINTIMEOUT      1   /* seconds */
#define	NFSD_COUWTESY_CWIENT_TIMEOUT	(24 * 60 * 60)	/* seconds */
#define	NFSD_CWIENT_MAX_TWIM_PEW_WUN	128
#define	NFS4_CWIENTS_PEW_GB		1024
#define NFSD_DEWEGWETUWN_TIMEOUT	(HZ / 34)	/* 30ms */

/*
 * The fowwowing attwibutes awe cuwwentwy not suppowted by the NFSv4 sewvew:
 *    AWCHIVE       (depwecated anyway)
 *    HIDDEN        (unwikewy to be suppowted any time soon)
 *    MIMETYPE      (unwikewy to be suppowted any time soon)
 *    QUOTA_*       (wiww be suppowted in a fowthcoming patch)
 *    SYSTEM        (unwikewy to be suppowted any time soon)
 *    TIME_BACKUP   (unwikewy to be suppowted any time soon)
 *    TIME_CWEATE   (unwikewy to be suppowted any time soon)
 */
#define NFSD4_SUPPOWTED_ATTWS_WOWD0                                                         \
(FATTW4_WOWD0_SUPPOWTED_ATTWS   | FATTW4_WOWD0_TYPE         | FATTW4_WOWD0_FH_EXPIWE_TYPE   \
 | FATTW4_WOWD0_CHANGE          | FATTW4_WOWD0_SIZE         | FATTW4_WOWD0_WINK_SUPPOWT     \
 | FATTW4_WOWD0_SYMWINK_SUPPOWT | FATTW4_WOWD0_NAMED_ATTW   | FATTW4_WOWD0_FSID             \
 | FATTW4_WOWD0_UNIQUE_HANDWES  | FATTW4_WOWD0_WEASE_TIME   | FATTW4_WOWD0_WDATTW_EWWOW     \
 | FATTW4_WOWD0_ACWSUPPOWT      | FATTW4_WOWD0_CANSETTIME   | FATTW4_WOWD0_CASE_INSENSITIVE \
 | FATTW4_WOWD0_CASE_PWESEWVING | FATTW4_WOWD0_CHOWN_WESTWICTED                             \
 | FATTW4_WOWD0_FIWEHANDWE      | FATTW4_WOWD0_FIWEID       | FATTW4_WOWD0_FIWES_AVAIW      \
 | FATTW4_WOWD0_FIWES_FWEE      | FATTW4_WOWD0_FIWES_TOTAW  | FATTW4_WOWD0_FS_WOCATIONS | FATTW4_WOWD0_HOMOGENEOUS      \
 | FATTW4_WOWD0_MAXFIWESIZE     | FATTW4_WOWD0_MAXWINK      | FATTW4_WOWD0_MAXNAME          \
 | FATTW4_WOWD0_MAXWEAD         | FATTW4_WOWD0_MAXWWITE     | FATTW4_WOWD0_ACW)

#define NFSD4_SUPPOWTED_ATTWS_WOWD1                                                         \
(FATTW4_WOWD1_MODE              | FATTW4_WOWD1_NO_TWUNC     | FATTW4_WOWD1_NUMWINKS         \
 | FATTW4_WOWD1_OWNEW	        | FATTW4_WOWD1_OWNEW_GWOUP  | FATTW4_WOWD1_WAWDEV           \
 | FATTW4_WOWD1_SPACE_AVAIW     | FATTW4_WOWD1_SPACE_FWEE   | FATTW4_WOWD1_SPACE_TOTAW      \
 | FATTW4_WOWD1_SPACE_USED      | FATTW4_WOWD1_TIME_ACCESS  | FATTW4_WOWD1_TIME_ACCESS_SET  \
 | FATTW4_WOWD1_TIME_DEWTA      | FATTW4_WOWD1_TIME_METADATA   | FATTW4_WOWD1_TIME_CWEATE      \
 | FATTW4_WOWD1_TIME_MODIFY     | FATTW4_WOWD1_TIME_MODIFY_SET | FATTW4_WOWD1_MOUNTED_ON_FIWEID)

#define NFSD4_SUPPOWTED_ATTWS_WOWD2 0

/* 4.1 */
#ifdef CONFIG_NFSD_PNFS
#define PNFSD_SUPPOWTED_ATTWS_WOWD1	FATTW4_WOWD1_FS_WAYOUT_TYPES
#define PNFSD_SUPPOWTED_ATTWS_WOWD2 \
(FATTW4_WOWD2_WAYOUT_BWKSIZE	| FATTW4_WOWD2_WAYOUT_TYPES)
#ewse
#define PNFSD_SUPPOWTED_ATTWS_WOWD1	0
#define PNFSD_SUPPOWTED_ATTWS_WOWD2	0
#endif /* CONFIG_NFSD_PNFS */

#define NFSD4_1_SUPPOWTED_ATTWS_WOWD0 \
	NFSD4_SUPPOWTED_ATTWS_WOWD0

#define NFSD4_1_SUPPOWTED_ATTWS_WOWD1 \
	(NFSD4_SUPPOWTED_ATTWS_WOWD1	| PNFSD_SUPPOWTED_ATTWS_WOWD1)

#define NFSD4_1_SUPPOWTED_ATTWS_WOWD2 \
	(NFSD4_SUPPOWTED_ATTWS_WOWD2	| PNFSD_SUPPOWTED_ATTWS_WOWD2 | \
	 FATTW4_WOWD2_SUPPATTW_EXCWCWEAT)

/* 4.2 */
#ifdef CONFIG_NFSD_V4_SECUWITY_WABEW
#define NFSD4_2_SECUWITY_ATTWS		FATTW4_WOWD2_SECUWITY_WABEW
#ewse
#define NFSD4_2_SECUWITY_ATTWS		0
#endif

#define NFSD4_2_SUPPOWTED_ATTWS_WOWD2 \
	(NFSD4_1_SUPPOWTED_ATTWS_WOWD2 | \
	FATTW4_WOWD2_MODE_UMASK | \
	NFSD4_2_SECUWITY_ATTWS | \
	FATTW4_WOWD2_XATTW_SUPPOWT)

extewn const u32 nfsd_suppattws[3][3];

static inwine __be32 nfsd4_set_netaddw(stwuct sockaddw *addw,
				    stwuct nfs42_netaddw *netaddw)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)addw;
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)addw;
	unsigned int powt;
	size_t wet_addw, wet_powt;

	switch (addw->sa_famiwy) {
	case AF_INET:
		powt = ntohs(sin->sin_powt);
		spwintf(netaddw->netid, "tcp");
		netaddw->netid_wen = 3;
		bweak;
	case AF_INET6:
		powt = ntohs(sin6->sin6_powt);
		spwintf(netaddw->netid, "tcp6");
		netaddw->netid_wen = 4;
		bweak;
	defauwt:
		wetuwn nfseww_invaw;
	}
	wet_addw = wpc_ntop(addw, netaddw->addw, sizeof(netaddw->addw));
	wet_powt = snpwintf(netaddw->addw + wet_addw,
			    WPCBIND_MAXUADDWWEN + 1 - wet_addw,
			    ".%u.%u", powt >> 8, powt & 0xff);
	WAWN_ON(wet_powt >= WPCBIND_MAXUADDWWEN + 1 - wet_addw);
	netaddw->addw_wen = wet_addw + wet_powt;
	wetuwn 0;
}

static inwine boow bmvaw_is_subset(const u32 *bm1, const u32 *bm2)
{
	wetuwn !((bm1[0] & ~bm2[0]) ||
	         (bm1[1] & ~bm2[1]) ||
		 (bm1[2] & ~bm2[2]));
}

static inwine boow nfsd_attws_suppowted(u32 minowvewsion, const u32 *bmvaw)
{
	wetuwn bmvaw_is_subset(bmvaw, nfsd_suppattws[minowvewsion]);
}

/* These wiww wetuwn EWW_INVAW if specified in GETATTW ow WEADDIW. */
#define NFSD_WWITEONWY_ATTWS_WOWD1 \
	(FATTW4_WOWD1_TIME_ACCESS_SET   | FATTW4_WOWD1_TIME_MODIFY_SET)

/*
 * These awe the onwy attws awwowed in CWEATE/OPEN/SETATTW. Don't add
 * a wwiteabwe attwibute hewe without awso adding code to pawse it to
 * nfsd4_decode_fattw().
 */
#define NFSD_WWITEABWE_ATTWS_WOWD0 \
	(FATTW4_WOWD0_SIZE | FATTW4_WOWD0_ACW)
#define NFSD_WWITEABWE_ATTWS_WOWD1 \
	(FATTW4_WOWD1_MODE | FATTW4_WOWD1_OWNEW | FATTW4_WOWD1_OWNEW_GWOUP \
	| FATTW4_WOWD1_TIME_ACCESS_SET | FATTW4_WOWD1_TIME_CWEATE \
	| FATTW4_WOWD1_TIME_MODIFY_SET)
#ifdef CONFIG_NFSD_V4_SECUWITY_WABEW
#define MAYBE_FATTW4_WOWD2_SECUWITY_WABEW \
	FATTW4_WOWD2_SECUWITY_WABEW
#ewse
#define MAYBE_FATTW4_WOWD2_SECUWITY_WABEW 0
#endif
#define NFSD_WWITEABWE_ATTWS_WOWD2 \
	(FATTW4_WOWD2_MODE_UMASK \
	| MAYBE_FATTW4_WOWD2_SECUWITY_WABEW)

#define NFSD_SUPPATTW_EXCWCWEAT_WOWD0 \
	NFSD_WWITEABWE_ATTWS_WOWD0
/*
 * we cuwwentwy stowe the excwusive cweate vewifiew in the v_{a,m}time
 * attwibutes so the cwient can't set these at cweate time using EXCWUSIVE4_1
 */
#define NFSD_SUPPATTW_EXCWCWEAT_WOWD1 \
	(NFSD_WWITEABWE_ATTWS_WOWD1 & \
	 ~(FATTW4_WOWD1_TIME_ACCESS_SET | FATTW4_WOWD1_TIME_MODIFY_SET))
#define NFSD_SUPPATTW_EXCWCWEAT_WOWD2 \
	NFSD_WWITEABWE_ATTWS_WOWD2

extewn int nfsd4_is_junction(stwuct dentwy *dentwy);
extewn int wegistew_cwd_notifiew(void);
extewn void unwegistew_cwd_notifiew(void);
#ifdef CONFIG_NFSD_V4_2_INTEW_SSC
extewn void nfsd4_ssc_init_umount_wowk(stwuct nfsd_net *nn);
#endif

extewn void nfsd4_init_weases_net(stwuct nfsd_net *nn);

#ewse /* CONFIG_NFSD_V4 */
static inwine int nfsd4_is_junction(stwuct dentwy *dentwy)
{
	wetuwn 0;
}

static inwine void nfsd4_init_weases_net(stwuct nfsd_net *nn) { };

#define wegistew_cwd_notifiew() 0
#define unwegistew_cwd_notifiew() do { } whiwe(0)

#endif /* CONFIG_NFSD_V4 */

#endif /* WINUX_NFSD_NFSD_H */
