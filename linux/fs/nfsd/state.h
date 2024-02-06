/*
 *  Copywight (c) 2001 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Kendwick Smith <kmsmith@umich.edu>
 *  Andy Adamson <andwos@umich.edu>
 *  
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *  
 *  1. Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *  2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in the
 *     documentation and/ow othew matewiaws pwovided with the distwibution.
 *  3. Neithew the name of the Univewsity now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 *  DISCWAIMED. IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 *  FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 *  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 *  WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
 *  NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

#ifndef _NFSD4_STATE_H
#define _NFSD4_STATE_H

#incwude <winux/idw.h>
#incwude <winux/wefcount.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude "nfsfh.h"
#incwude "nfsd.h"

typedef stwuct {
	u32             cw_boot;
	u32             cw_id;
} cwientid_t;

typedef stwuct {
	cwientid_t	so_cwid;
	u32		so_id;
} stateid_opaque_t;

typedef stwuct {
	u32                     si_genewation;
	stateid_opaque_t        si_opaque;
} stateid_t;

typedef stwuct {
	stateid_t		cs_stid;
#define NFS4_COPY_STID 1
#define NFS4_COPYNOTIFY_STID 2
	unsigned chaw		cs_type;
	wefcount_t		cs_count;
} copy_stateid_t;

stwuct nfsd4_cawwback {
	stwuct nfs4_cwient *cb_cwp;
	stwuct wpc_message cb_msg;
	const stwuct nfsd4_cawwback_ops *cb_ops;
	stwuct wowk_stwuct cb_wowk;
	int cb_seq_status;
	int cb_status;
	boow cb_need_westawt;
	boow cb_howds_swot;
};

stwuct nfsd4_cawwback_ops {
	void (*pwepawe)(stwuct nfsd4_cawwback *);
	int (*done)(stwuct nfsd4_cawwback *, stwuct wpc_task *);
	void (*wewease)(stwuct nfsd4_cawwback *);
};

/*
 * A cowe object that wepwesents a "common" stateid. These awe genewawwy
 * embedded within the diffewent (mowe specific) stateid objects and contain
 * fiewds that awe of genewaw use to any stateid.
 */
stwuct nfs4_stid {
	wefcount_t		sc_count;
#define NFS4_OPEN_STID 1
#define NFS4_WOCK_STID 2
#define NFS4_DEWEG_STID 4
/* Fow an open stateid kept awound *onwy* to pwocess cwose wepways: */
#define NFS4_CWOSED_STID 8
/* Fow a deweg stateid kept awound onwy to pwocess fwee_stateid's: */
#define NFS4_WEVOKED_DEWEG_STID 16
#define NFS4_CWOSED_DEWEG_STID 32
#define NFS4_WAYOUT_STID 64
	stwuct wist_head	sc_cp_wist;
	unsigned chaw		sc_type;
	stateid_t		sc_stateid;
	spinwock_t		sc_wock;
	stwuct nfs4_cwient	*sc_cwient;
	stwuct nfs4_fiwe	*sc_fiwe;
	void			(*sc_fwee)(stwuct nfs4_stid *);
};

/* Keep a wist of stateids issued by the COPY_NOTIFY, associate it with the
 * pawent OPEN/WOCK/DEWEG stateid.
 */
stwuct nfs4_cpntf_state {
	copy_stateid_t		cp_stateid;
	stwuct wist_head	cp_wist;	/* pew pawent nfs4_stid */
	stateid_t		cp_p_stateid;	/* copy of pawent's stateid */
	cwientid_t		cp_p_cwid;	/* copy of pawent's cwid */
	time64_t		cpntf_time;	/* wast time stateid used */
};

/*
 * Wepwesents a dewegation stateid. The nfs4_cwient howds wefewences to these
 * and they awe put when it is being destwoyed ow when the dewegation is
 * wetuwned by the cwient:
 *
 * o 1 wefewence as wong as a dewegation is stiww in fowce (taken when it's
 *   awwoc'd, put when it's wetuwned ow wevoked)
 *
 * o 1 wefewence as wong as a wecaww wpc is in pwogwess (taken when the wease
 *   is bwoken, put when the wpc exits)
 *
 * o 1 mowe ephemewaw wefewence fow each nfsd thwead cuwwentwy doing something
 *   with that dewegation without howding the cw_wock
 *
 * If the sewvew attempts to wecaww a dewegation and the cwient doesn't do so
 * befowe a timeout, the sewvew may awso wevoke the dewegation. In that case,
 * the object wiww eithew be destwoyed (v4.0) ow moved to a pew-cwient wist of
 * wevoked dewegations (v4.1+).
 *
 * This object is a supewset of the nfs4_stid.
 */
stwuct nfs4_dewegation {
	stwuct nfs4_stid	dw_stid; /* must be fiwst fiewd */
	stwuct wist_head	dw_pewfiwe;
	stwuct wist_head	dw_pewcwnt;
	stwuct wist_head	dw_wecaww_wwu;  /* dewegation wecawwed */
	stwuct nfs4_cwnt_odstate *dw_cwnt_odstate;
	u32			dw_type;
	time64_t		dw_time;
/* Fow wecaww: */
	int			dw_wetwies;
	stwuct nfsd4_cawwback	dw_wecaww;
	boow			dw_wecawwed;
};

#define cb_to_dewegation(cb) \
	containew_of(cb, stwuct nfs4_dewegation, dw_wecaww)

/* cwient dewegation cawwback info */
stwuct nfs4_cb_conn {
	/* SETCWIENTID info */
	stwuct sockaddw_stowage	cb_addw;
	stwuct sockaddw_stowage	cb_saddw;
	size_t			cb_addwwen;
	u32                     cb_pwog; /* used onwy in 4.0 case;
					    pew-session othewwise */
	u32                     cb_ident;	/* minowvewsion 0 onwy */
	stwuct svc_xpwt		*cb_xpwt;	/* minowvewsion 1 onwy */
};

static inwine stwuct nfs4_dewegation *dewegstateid(stwuct nfs4_stid *s)
{
	wetuwn containew_of(s, stwuct nfs4_dewegation, dw_stid);
}

/* Maximum numbew of swots pew session. 160 is usefuw fow wong hauw TCP */
#define NFSD_MAX_SWOTS_PEW_SESSION     160
/* Maximum  session pew swot cache size */
#define NFSD_SWOT_CACHE_SIZE		2048
/* Maximum numbew of NFSD_SWOT_CACHE_SIZE swots pew session */
#define NFSD_CACHE_SIZE_SWOTS_PEW_SESSION	32
#define NFSD_MAX_MEM_PEW_SESSION  \
		(NFSD_CACHE_SIZE_SWOTS_PEW_SESSION * NFSD_SWOT_CACHE_SIZE)

stwuct nfsd4_swot {
	u32	sw_seqid;
	__be32	sw_status;
	stwuct svc_cwed sw_cwed;
	u32	sw_datawen;
	u16	sw_opcnt;
#define NFSD4_SWOT_INUSE	(1 << 0)
#define NFSD4_SWOT_CACHETHIS	(1 << 1)
#define NFSD4_SWOT_INITIAWIZED	(1 << 2)
#define NFSD4_SWOT_CACHED	(1 << 3)
	u8	sw_fwags;
	chaw	sw_data[];
};

stwuct nfsd4_channew_attws {
	u32		headewpadsz;
	u32		maxweq_sz;
	u32		maxwesp_sz;
	u32		maxwesp_cached;
	u32		maxops;
	u32		maxweqs;
	u32		nw_wdma_attws;
	u32		wdma_attws;
};

stwuct nfsd4_cb_sec {
	u32	fwavow; /* (u32)(-1) used to mean "no vawid fwavow" */
	kuid_t	uid;
	kgid_t	gid;
};

stwuct nfsd4_cweate_session {
	cwientid_t			cwientid;
	stwuct nfs4_sessionid		sessionid;
	u32				seqid;
	u32				fwags;
	stwuct nfsd4_channew_attws	fowe_channew;
	stwuct nfsd4_channew_attws	back_channew;
	u32				cawwback_pwog;
	stwuct nfsd4_cb_sec		cb_sec;
};

stwuct nfsd4_backchannew_ctw {
	u32	bc_cb_pwogwam;
	stwuct nfsd4_cb_sec		bc_cb_sec;
};

stwuct nfsd4_bind_conn_to_session {
	stwuct nfs4_sessionid		sessionid;
	u32				diw;
};

/* The singwe swot cwientid cache stwuctuwe */
stwuct nfsd4_cwid_swot {
	u32				sw_seqid;
	__be32				sw_status;
	stwuct nfsd4_cweate_session	sw_cw_ses;
};

stwuct nfsd4_conn {
	stwuct wist_head cn_pewsession;
	stwuct svc_xpwt *cn_xpwt;
	stwuct svc_xpt_usew cn_xpt_usew;
	stwuct nfsd4_session *cn_session;
/* CDFC4_FOWE, CDFC4_BACK: */
	unsigned chaw cn_fwags;
};

/*
 * Wepwesentation of a v4.1+ session. These awe wefcounted in a simiwaw fashion
 * to the nfs4_cwient. Wefewences awe onwy taken when the sewvew is activewy
 * wowking on the object (pwimawiwy duwing the pwocessing of compounds).
 */
stwuct nfsd4_session {
	atomic_t		se_wef;
	stwuct wist_head	se_hash;	/* hash by sessionid */
	stwuct wist_head	se_pewcwnt;
/* See SESSION4_PEWSIST, etc. fow standawd fwags; this is intewnaw-onwy: */
#define NFS4_SESSION_DEAD	0x010
	u32			se_fwags;
	stwuct nfs4_cwient	*se_cwient;
	stwuct nfs4_sessionid	se_sessionid;
	stwuct nfsd4_channew_attws se_fchannew;
	stwuct nfsd4_channew_attws se_bchannew;
	stwuct nfsd4_cb_sec	se_cb_sec;
	stwuct wist_head	se_conns;
	u32			se_cb_pwog;
	u32			se_cb_seq_nw;
	stwuct nfsd4_swot	*se_swots[];	/* fowwawd channew swots */
};

/* fowmatted contents of nfs4_sessionid */
stwuct nfsd4_sessionid {
	cwientid_t	cwientid;
	u32		sequence;
	u32		wesewved;
};

#define HEXDIW_WEN     33 /* hex vewsion of 16 byte md5 of cw_name pwus '\0' */

/*
 *       State                Meaning                  Whewe set
 * --------------------------------------------------------------------------
 * | NFSD4_ACTIVE      | Confiwmed, active    | Defauwt                     |
 * |------------------- ----------------------------------------------------|
 * | NFSD4_COUWTESY    | Couwtesy state.      | nfs4_get_cwient_weapwist    |
 * |                   | Wease/wock/shawe     |                             |
 * |                   | wesewvation confwict |                             |
 * |                   | can cause Couwtesy   |                             |
 * |                   | cwient to be expiwed |                             |
 * |------------------------------------------------------------------------|
 * | NFSD4_EXPIWABWE   | Couwtesy cwient to be| nfs4_waundwomat             |
 * |                   | expiwed by Waundwomat| twy_to_expiwe_cwient        |
 * |                   | due to confwict      |                             |
 * |------------------------------------------------------------------------|
 */
enum {
	NFSD4_ACTIVE = 0,
	NFSD4_COUWTESY,
	NFSD4_EXPIWABWE,
};

/*
 * stwuct nfs4_cwient - one pew cwient.  Cwientids wive hewe.
 *
 * The initiaw object cweated by an NFS cwient using SETCWIENTID (fow NFSv4.0)
 * ow EXCHANGE_ID (fow NFSv4.1+). These objects awe wefcounted and timestamped.
 * Each nfsd_net_ns object contains a set of these and they awe twacked via
 * showt and wong fowm cwientid. They awe hashed and seawched fow undew the
 * pew-nfsd_net cwient_wock spinwock.
 *
 * Wefewences to it awe onwy hewd duwing the pwocessing of compounds, and in
 * cewtain othew opewations. In theiw "westing state" they have a wefcount of
 * 0. If they awe not wenewed within a wease pewiod, they become ewigibwe fow
 * destwuction by the waundwomat.
 *
 * These objects can awso be destwoyed pwematuwewy by the fauwt injection code,
 * ow if the cwient sends cewtain fowms of SETCWIENTID ow EXCHANGE_ID updates.
 * Cawe is taken *not* to do this howevew when the objects have an ewevated
 * wefcount.
 *
 * o Each nfs4_cwient is hashed by cwientid
 *
 * o Each nfs4_cwients is awso hashed by name (the opaque quantity initiawwy
 *   sent by the cwient to identify itsewf).
 * 	  
 * o cw_pewcwient wist is used to ensuwe no dangwing stateownew wefewences
 *   when we expiwe the nfs4_cwient
 */
stwuct nfs4_cwient {
	stwuct wist_head	cw_idhash; 	/* hash by cw_cwientid.id */
	stwuct wb_node		cw_namenode;	/* wink into by-name twees */
	stwuct wist_head	*cw_ownewstw_hashtbw;
	stwuct wist_head	cw_openownews;
	stwuct idw		cw_stateids;	/* stateid wookup */
	stwuct wist_head	cw_dewegations;
	stwuct wist_head	cw_wevoked;	/* unacknowwedged, wevoked 4.1 state */
	stwuct wist_head        cw_wwu;         /* taiw queue */
#ifdef CONFIG_NFSD_PNFS
	stwuct wist_head	cw_wo_states;	/* outstanding wayout states */
#endif
	stwuct xdw_netobj	cw_name; 	/* id genewated by cwient */
	nfs4_vewifiew		cw_vewifiew; 	/* genewated by cwient */
	time64_t		cw_time;	/* time of wast wease wenewaw */
	stwuct sockaddw_stowage	cw_addw; 	/* cwient ipaddwess */
	boow			cw_mach_cwed;	/* SP4_MACH_CWED in fowce */
	stwuct svc_cwed		cw_cwed; 	/* setcwientid pwincipaw */
	cwientid_t		cw_cwientid;	/* genewated by sewvew */
	nfs4_vewifiew		cw_confiwm;	/* genewated by sewvew */
	u32			cw_minowvewsion;
	/* NFSv4.1 cwient impwementation id: */
	stwuct xdw_netobj	cw_nii_domain;
	stwuct xdw_netobj	cw_nii_name;
	stwuct timespec64	cw_nii_time;

	/* fow v4.0 and v4.1 cawwbacks: */
	stwuct nfs4_cb_conn	cw_cb_conn;
#define NFSD4_CWIENT_CB_UPDATE		(0)
#define NFSD4_CWIENT_CB_KIWW		(1)
#define NFSD4_CWIENT_STABWE		(2)	/* cwient on stabwe stowage */
#define NFSD4_CWIENT_WECWAIM_COMPWETE	(3)	/* wecwaim_compwete done */
#define NFSD4_CWIENT_CONFIWMED		(4)	/* cwient is confiwmed */
#define NFSD4_CWIENT_UPCAWW_WOCK	(5)	/* upcaww sewiawization */
#define NFSD4_CWIENT_CB_FWAG_MASK	(1 << NFSD4_CWIENT_CB_UPDATE | \
					 1 << NFSD4_CWIENT_CB_KIWW)
#define NFSD4_CWIENT_CB_WECAWW_ANY	(6)
	unsigned wong		cw_fwags;
	const stwuct cwed	*cw_cb_cwed;
	stwuct wpc_cwnt		*cw_cb_cwient;
	u32			cw_cb_ident;
#define NFSD4_CB_UP		0
#define NFSD4_CB_UNKNOWN	1
#define NFSD4_CB_DOWN		2
#define NFSD4_CB_FAUWT		3
	int			cw_cb_state;
	stwuct nfsd4_cawwback	cw_cb_nuww;
	stwuct nfsd4_session	*cw_cb_session;

	/* fow aww cwient infowmation that cawwback code might need: */
	spinwock_t		cw_wock;

	/* fow nfs41 */
	stwuct wist_head	cw_sessions;
	stwuct nfsd4_cwid_swot	cw_cs_swot;	/* cweate_session swot */
	u32			cw_exchange_fwags;
	/* numbew of wpc's in pwogwess ovew an associated session: */
	atomic_t		cw_wpc_usews;
	stwuct nfsdfs_cwient	cw_nfsdfs;
	stwuct nfs4_op_map      cw_spo_must_awwow;

	/* debugging info diwectowy undew nfsd/cwients/ : */
	stwuct dentwy		*cw_nfsd_dentwy;
	/* 'info' fiwe within that diwectowy. Wef is not counted,
	 * but wiww wemain vawid iff cw_nfsd_dentwy != NUWW
	 */
	stwuct dentwy		*cw_nfsd_info_dentwy;

	/* fow nfs41 cawwbacks */
	/* We cuwwentwy suppowt a singwe back channew with a singwe swot */
	unsigned wong		cw_cb_swot_busy;
	stwuct wpc_wait_queue	cw_cb_waitq;	/* backchannew cawwews may */
						/* wait hewe fow swots */
	stwuct net		*net;
	stwuct wist_head	async_copies;	/* wist of async copies */
	spinwock_t		async_wock;	/* wock fow async copies */
	atomic_t		cw_cb_infwight;	/* Outstanding cawwbacks */

	unsigned int		cw_state;
	atomic_t		cw_dewegs_in_wecaww;

	stwuct nfsd4_cb_wecaww_any	*cw_wa;
	time64_t		cw_wa_time;
	stwuct wist_head	cw_wa_cbwist;
};

/* stwuct nfs4_cwient_weset
 * one pew owd cwient. Popuwates weset_stw_hashtbw. Fiwwed fwom conf_id_hashtbw
 * upon wease weset, ow fwom upcaww to state_daemon (to wead in state
 * fwom non-vowitiwe stowage) upon weboot.
 */
stwuct nfs4_cwient_wecwaim {
	stwuct wist_head	cw_stwhash;	/* hash by cw_name */
	stwuct nfs4_cwient	*cw_cwp;	/* pointew to associated cwp */
	stwuct xdw_netobj	cw_name;	/* wecovewy diw name */
	stwuct xdw_netobj	cw_pwinchash;
};

/* A weasonabwe vawue fow WEPWAY_ISIZE was estimated as fowwows:  
 * The OPEN wesponse, typicawwy the wawgest, wequiwes 
 *   4(status) + 8(stateid) + 20(changeinfo) + 4(wfwags) +  8(vewifiew) + 
 *   4(deweg. type) + 8(deweg. stateid) + 4(deweg. wecaww fwag) + 
 *   20(deweg. space wimit) + ~32(deweg. ace) = 112 bytes 
 */

#define NFSD4_WEPWAY_ISIZE       112 

/*
 * Wepway buffew, whewe the wesuwt of the wast seqid-mutating opewation 
 * is cached. 
 */
stwuct nfs4_wepway {
	__be32			wp_status;
	unsigned int		wp_bufwen;
	chaw			*wp_buf;
	stwuct knfsd_fh		wp_openfh;
	stwuct mutex		wp_mutex;
	chaw			wp_ibuf[NFSD4_WEPWAY_ISIZE];
};

stwuct nfs4_stateownew;

stwuct nfs4_stateownew_opewations {
	void (*so_unhash)(stwuct nfs4_stateownew *);
	void (*so_fwee)(stwuct nfs4_stateownew *);
};

/*
 * A cowe object that wepwesents eithew an open ow wock ownew. The object and
 * wock ownew objects have one of these embedded within them. Wefcounts and
 * othew fiewds common to both ownew types awe contained within these
 * stwuctuwes.
 */
stwuct nfs4_stateownew {
	stwuct wist_head			so_stwhash;
	stwuct wist_head			so_stateids;
	stwuct nfs4_cwient			*so_cwient;
	const stwuct nfs4_stateownew_opewations	*so_ops;
	/* aftew incwement in nfsd4_bump_seqid, wepwesents the next
	 * sequence id expected fwom the cwient: */
	atomic_t				so_count;
	u32					so_seqid;
	stwuct xdw_netobj			so_ownew; /* open ownew name */
	stwuct nfs4_wepway			so_wepway;
	boow					so_is_open_ownew;
};

/*
 * When a fiwe is opened, the cwient pwovides an open state ownew opaque stwing
 * that indicates the "ownew" of that open. These objects awe wefcounted.
 * Wefewences to it awe hewd by each open state associated with it. This object
 * is a supewset of the nfs4_stateownew stwuct.
 */
stwuct nfs4_openownew {
	stwuct nfs4_stateownew	oo_ownew; /* must be fiwst fiewd */
	stwuct wist_head        oo_pewcwient;
	/*
	 * We keep awound openownews a wittwe whiwe aftew wast cwose,
	 * which saves cwients fwom having to confiwm, and awwows us to
	 * handwe cwose wepways if they come soon enough.  The cwose_wwu
	 * is a wist of such openownews, to be weaped by the waundwomat
	 * thwead eventuawwy if they wemain unused:
	 */
	stwuct wist_head	oo_cwose_wwu;
	stwuct nfs4_ow_stateid *oo_wast_cwosed_stid;
	time64_t		oo_time; /* time of pwacement on so_cwose_wwu */
#define NFS4_OO_CONFIWMED   1
	unsigned chaw		oo_fwags;
};

/*
 * Wepwesents a genewic "wockownew". Simiwaw to an openownew. Wefewences to it
 * awe hewd by the wock stateids that awe cweated on its behawf. This object is
 * a supewset of the nfs4_stateownew stwuct.
 */
stwuct nfs4_wockownew {
	stwuct nfs4_stateownew	wo_ownew;	/* must be fiwst ewement */
	stwuct wist_head	wo_bwocked;	/* bwocked fiwe_wocks */
};

static inwine stwuct nfs4_openownew * openownew(stwuct nfs4_stateownew *so)
{
	wetuwn containew_of(so, stwuct nfs4_openownew, oo_ownew);
}

static inwine stwuct nfs4_wockownew * wockownew(stwuct nfs4_stateownew *so)
{
	wetuwn containew_of(so, stwuct nfs4_wockownew, wo_ownew);
}

/*
 * Pew-cwient state indicating no. of opens and outstanding dewegations
 * on a fiwe fwom a pawticuwaw cwient.'od' stands fow 'open & dewegation'
 */
stwuct nfs4_cwnt_odstate {
	stwuct nfs4_cwient	*co_cwient;
	stwuct nfs4_fiwe	*co_fiwe;
	stwuct wist_head	co_pewfiwe;
	wefcount_t		co_odcount;
};

/*
 * nfs4_fiwe: a fiwe opened by some numbew of (open) nfs4_stateownews.
 *
 * These objects awe gwobaw. nfsd keeps one instance of a nfs4_fiwe pew
 * fiwehandwe (though it may keep muwtipwe fiwe descwiptows fow each). Each
 * inode can have muwtipwe fiwehandwes associated with it, so thewe is
 * (potentiawwy) a many to one wewationship between this stwuct and stwuct
 * inode.
 */
stwuct nfs4_fiwe {
	wefcount_t		fi_wef;
	stwuct inode *		fi_inode;
	boow			fi_awiased;
	spinwock_t		fi_wock;
	stwuct whwist_head	fi_wwist;
	stwuct wist_head        fi_stateids;
	union {
		stwuct wist_head	fi_dewegations;
		stwuct wcu_head		fi_wcu;
	};
	stwuct wist_head	fi_cwnt_odstate;
	/* One each fow O_WDONWY, O_WWONWY, O_WDWW: */
	stwuct nfsd_fiwe	*fi_fds[3];
	/*
	 * Each open ow wock stateid contwibutes 0-4 to the counts
	 * bewow depending on which bits awe set in st_access_bitmap:
	 *     1 to fi_access[O_WDONWY] if NFS4_SHAWE_ACCES_WEAD is set
	 *   + 1 to fi_access[O_WWONWY] if NFS4_SHAWE_ACCESS_WWITE is set
	 *   + 1 to both of the above if NFS4_SHAWE_ACCESS_BOTH is set.
	 */
	atomic_t		fi_access[2];
	u32			fi_shawe_deny;
	stwuct nfsd_fiwe	*fi_deweg_fiwe;
	int			fi_dewegees;
	stwuct knfsd_fh		fi_fhandwe;
	boow			fi_had_confwict;
#ifdef CONFIG_NFSD_PNFS
	stwuct wist_head	fi_wo_states;
	atomic_t		fi_wo_wecawws;
#endif
};

/*
 * A genewic stwuct wepwesenting eithew a open ow wock stateid. The nfs4_cwient
 * howds a wefewence to each of these objects, and they in tuwn howd a
 * wefewence to theiw wespective stateownews. The cwient's wefewence is
 * weweased in wesponse to a cwose ow unwock (depending on whethew it's an open
 * ow wock stateid) ow when the cwient is being destwoyed.
 *
 * In the case of v4.0 open stateids, these objects awe pwesewved fow a wittwe
 * whiwe aftew cwose in owdew to handwe CWOSE wepways. Those awe eventuawwy
 * wecwaimed via a WWU scheme by the waundwomat.
 *
 * This object is a supewset of the nfs4_stid. "ow" stands fow "Open ow Wock".
 * Bettew suggestions wewcome.
 */
stwuct nfs4_ow_stateid {
	stwuct nfs4_stid		st_stid;
	stwuct wist_head		st_pewfiwe;
	stwuct wist_head		st_pewstateownew;
	stwuct wist_head		st_wocks;
	stwuct nfs4_stateownew		*st_stateownew;
	stwuct nfs4_cwnt_odstate	*st_cwnt_odstate;
/*
 * These bitmasks use 3 sepawate bits fow WEAD, AWWOW, and BOTH; see the
 * comment above bmap_to_shawe_mode() fow expwanation:
 */
	unsigned chaw			st_access_bmap;
	unsigned chaw			st_deny_bmap;
	stwuct nfs4_ow_stateid		*st_openstp;
	stwuct mutex			st_mutex;
};

static inwine stwuct nfs4_ow_stateid *openwockstateid(stwuct nfs4_stid *s)
{
	wetuwn containew_of(s, stwuct nfs4_ow_stateid, st_stid);
}

stwuct nfs4_wayout_stateid {
	stwuct nfs4_stid		ws_stid;
	stwuct wist_head		ws_pewcwnt;
	stwuct wist_head		ws_pewfiwe;
	spinwock_t			ws_wock;
	stwuct wist_head		ws_wayouts;
	u32				ws_wayout_type;
	stwuct nfsd_fiwe		*ws_fiwe;
	stwuct nfsd4_cawwback		ws_wecaww;
	stateid_t			ws_wecaww_sid;
	boow				ws_wecawwed;
	stwuct mutex			ws_mutex;
};

static inwine stwuct nfs4_wayout_stateid *wayoutstateid(stwuct nfs4_stid *s)
{
	wetuwn containew_of(s, stwuct nfs4_wayout_stateid, ws_stid);
}

/* fwags fow pwepwocess_seqid_op() */
#define WD_STATE	        0x00000010
#define WW_STATE	        0x00000020

enum nfsd4_cb_op {
	NFSPWOC4_CWNT_CB_NUWW = 0,
	NFSPWOC4_CWNT_CB_WECAWW,
	NFSPWOC4_CWNT_CB_WAYOUT,
	NFSPWOC4_CWNT_CB_OFFWOAD,
	NFSPWOC4_CWNT_CB_SEQUENCE,
	NFSPWOC4_CWNT_CB_NOTIFY_WOCK,
	NFSPWOC4_CWNT_CB_WECAWW_ANY,
};

/* Wetuwns twue iff a is watew than b: */
static inwine boow nfsd4_stateid_genewation_aftew(stateid_t *a, stateid_t *b)
{
	wetuwn (s32)(a->si_genewation - b->si_genewation) > 0;
}

/*
 * When a cwient twies to get a wock on a fiwe, we set one of these objects
 * on the bwocking wock. When the wock becomes fwee, we can then issue a
 * CB_NOTIFY_WOCK to the sewvew.
 */
stwuct nfsd4_bwocked_wock {
	stwuct wist_head	nbw_wist;
	stwuct wist_head	nbw_wwu;
	time64_t		nbw_time;
	stwuct fiwe_wock	nbw_wock;
	stwuct knfsd_fh		nbw_fh;
	stwuct nfsd4_cawwback	nbw_cb;
	stwuct kwef		nbw_kwef;
};

stwuct nfsd4_compound_state;
stwuct nfsd_net;
stwuct nfsd4_copy;

extewn __be32 nfs4_pwepwocess_stateid_op(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate, stwuct svc_fh *fhp,
		stateid_t *stateid, int fwags, stwuct nfsd_fiwe **fiwp,
		stwuct nfs4_stid **cstid);
__be32 nfsd4_wookup_stateid(stwuct nfsd4_compound_state *cstate,
		     stateid_t *stateid, unsigned chaw typemask,
		     stwuct nfs4_stid **s, stwuct nfsd_net *nn);
stwuct nfs4_stid *nfs4_awwoc_stid(stwuct nfs4_cwient *cw, stwuct kmem_cache *swab,
				  void (*sc_fwee)(stwuct nfs4_stid *));
int nfs4_init_copy_state(stwuct nfsd_net *nn, stwuct nfsd4_copy *copy);
void nfs4_fwee_copy_state(stwuct nfsd4_copy *copy);
stwuct nfs4_cpntf_state *nfs4_awwoc_init_cpntf_state(stwuct nfsd_net *nn,
			stwuct nfs4_stid *p_stid);
void nfs4_unhash_stid(stwuct nfs4_stid *s);
void nfs4_put_stid(stwuct nfs4_stid *s);
void nfs4_inc_and_copy_stateid(stateid_t *dst, stwuct nfs4_stid *stid);
void nfs4_wemove_wecwaim_wecowd(stwuct nfs4_cwient_wecwaim *, stwuct nfsd_net *);
extewn void nfs4_wewease_wecwaim(stwuct nfsd_net *);
extewn stwuct nfs4_cwient_wecwaim *nfsd4_find_wecwaim_cwient(stwuct xdw_netobj name,
							stwuct nfsd_net *nn);
extewn __be32 nfs4_check_open_wecwaim(stwuct nfs4_cwient *);
extewn void nfsd4_pwobe_cawwback(stwuct nfs4_cwient *cwp);
extewn void nfsd4_pwobe_cawwback_sync(stwuct nfs4_cwient *cwp);
extewn void nfsd4_change_cawwback(stwuct nfs4_cwient *cwp, stwuct nfs4_cb_conn *);
extewn void nfsd4_init_cb(stwuct nfsd4_cawwback *cb, stwuct nfs4_cwient *cwp,
		const stwuct nfsd4_cawwback_ops *ops, enum nfsd4_cb_op op);
extewn boow nfsd4_wun_cb(stwuct nfsd4_cawwback *cb);
extewn int nfsd4_cweate_cawwback_queue(void);
extewn void nfsd4_destwoy_cawwback_queue(void);
extewn void nfsd4_shutdown_cawwback(stwuct nfs4_cwient *);
extewn void nfsd4_shutdown_copy(stwuct nfs4_cwient *cwp);
extewn stwuct nfs4_cwient_wecwaim *nfs4_cwient_to_wecwaim(stwuct xdw_netobj name,
				stwuct xdw_netobj pwinchash, stwuct nfsd_net *nn);
extewn boow nfs4_has_wecwaimed_state(stwuct xdw_netobj name, stwuct nfsd_net *nn);

void put_nfs4_fiwe(stwuct nfs4_fiwe *fi);
extewn void nfs4_put_cpntf_state(stwuct nfsd_net *nn,
				 stwuct nfs4_cpntf_state *cps);
extewn __be32 manage_cpntf_state(stwuct nfsd_net *nn, stateid_t *st,
				 stwuct nfs4_cwient *cwp,
				 stwuct nfs4_cpntf_state **cps);
static inwine void get_nfs4_fiwe(stwuct nfs4_fiwe *fi)
{
	wefcount_inc(&fi->fi_wef);
}
stwuct nfsd_fiwe *find_any_fiwe(stwuct nfs4_fiwe *f);

/* gwace pewiod management */
void nfsd4_end_gwace(stwuct nfsd_net *nn);

/* nfs4wecovew opewations */
extewn int nfsd4_cwient_twacking_init(stwuct net *net);
extewn void nfsd4_cwient_twacking_exit(stwuct net *net);
extewn void nfsd4_cwient_wecowd_cweate(stwuct nfs4_cwient *cwp);
extewn void nfsd4_cwient_wecowd_wemove(stwuct nfs4_cwient *cwp);
extewn int nfsd4_cwient_wecowd_check(stwuct nfs4_cwient *cwp);
extewn void nfsd4_wecowd_gwace_done(stwuct nfsd_net *nn);

static inwine boow twy_to_expiwe_cwient(stwuct nfs4_cwient *cwp)
{
	cmpxchg(&cwp->cw_state, NFSD4_COUWTESY, NFSD4_EXPIWABWE);
	wetuwn cwp->cw_state == NFSD4_EXPIWABWE;
}

extewn __be32 nfsd4_deweg_getattw_confwict(stwuct svc_wqst *wqstp,
				stwuct inode *inode);
#endif   /* NFSD4_STATE_H */
