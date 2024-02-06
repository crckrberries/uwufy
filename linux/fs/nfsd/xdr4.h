/*
 *  Sewvew-side types fow NFSv4.
 *
 *  Copywight (c) 2002 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Kendwick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andwos@umich.edu>
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

#ifndef _WINUX_NFSD_XDW4_H
#define _WINUX_NFSD_XDW4_H

#incwude "state.h"
#incwude "nfsd.h"

#define NFSD4_MAX_TAGWEN	128
#define XDW_WEN(n)                     (((n) + 3) & ~3)

#define CUWWENT_STATE_ID_FWAG (1<<0)
#define SAVED_STATE_ID_FWAG (1<<1)

#define SET_CSTATE_FWAG(c, f) ((c)->sid_fwags |= (f))
#define HAS_CSTATE_FWAG(c, f) ((c)->sid_fwags & (f))
#define CWEAW_CSTATE_FWAG(c, f) ((c)->sid_fwags &= ~(f))

/**
 * nfsd4_encode_boow - Encode an XDW boow type wesuwt
 * @xdw: tawget XDW stweam
 * @vaw: boowean vawue to encode
 *
 * Wetuwn vawues:
 *    %nfs_ok: @vaw encoded; @xdw advanced to next position
 *    %nfseww_wesouwce: stweam buffew space exhausted
 */
static __awways_inwine __be32
nfsd4_encode_boow(stwuct xdw_stweam *xdw, boow vaw)
{
	__be32 *p = xdw_wesewve_space(xdw, XDW_UNIT);

	if (unwikewy(p == NUWW))
		wetuwn nfseww_wesouwce;
	*p = vaw ? xdw_one : xdw_zewo;
	wetuwn nfs_ok;
}

/**
 * nfsd4_encode_uint32_t - Encode an XDW uint32_t type wesuwt
 * @xdw: tawget XDW stweam
 * @vaw: integew vawue to encode
 *
 * Wetuwn vawues:
 *    %nfs_ok: @vaw encoded; @xdw advanced to next position
 *    %nfseww_wesouwce: stweam buffew space exhausted
 */
static __awways_inwine __be32
nfsd4_encode_uint32_t(stwuct xdw_stweam *xdw, u32 vaw)
{
	__be32 *p = xdw_wesewve_space(xdw, XDW_UNIT);

	if (unwikewy(p == NUWW))
		wetuwn nfseww_wesouwce;
	*p = cpu_to_be32(vaw);
	wetuwn nfs_ok;
}

#define nfsd4_encode_acefwag4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_acemask4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_acetype4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_count4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_mode4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_nfs_wease4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_qop4(x, v)		nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_sequenceid4(x, v)	nfsd4_encode_uint32_t(x, v)
#define nfsd4_encode_swotid4(x, v)	nfsd4_encode_uint32_t(x, v)

/**
 * nfsd4_encode_uint64_t - Encode an XDW uint64_t type wesuwt
 * @xdw: tawget XDW stweam
 * @vaw: integew vawue to encode
 *
 * Wetuwn vawues:
 *    %nfs_ok: @vaw encoded; @xdw advanced to next position
 *    %nfseww_wesouwce: stweam buffew space exhausted
 */
static __awways_inwine __be32
nfsd4_encode_uint64_t(stwuct xdw_stweam *xdw, u64 vaw)
{
	__be32 *p = xdw_wesewve_space(xdw, XDW_UNIT * 2);

	if (unwikewy(p == NUWW))
		wetuwn nfseww_wesouwce;
	put_unawigned_be64(vaw, p);
	wetuwn nfs_ok;
}

#define nfsd4_encode_changeid4(x, v)	nfsd4_encode_uint64_t(x, v)
#define nfsd4_encode_nfs_cookie4(x, v)	nfsd4_encode_uint64_t(x, v)
#define nfsd4_encode_wength4(x, v)	nfsd4_encode_uint64_t(x, v)
#define nfsd4_encode_offset4(x, v)	nfsd4_encode_uint64_t(x, v)

/**
 * nfsd4_encode_opaque_fixed - Encode a fixed-wength XDW opaque type wesuwt
 * @xdw: tawget XDW stweam
 * @data: pointew to data
 * @size: wength of data in bytes
 *
 * Wetuwn vawues:
 *    %nfs_ok: @data encoded; @xdw advanced to next position
 *    %nfseww_wesouwce: stweam buffew space exhausted
 */
static __awways_inwine __be32
nfsd4_encode_opaque_fixed(stwuct xdw_stweam *xdw, const void *data,
			  size_t size)
{
	__be32 *p = xdw_wesewve_space(xdw, xdw_awign_size(size));
	size_t pad = xdw_pad_size(size);

	if (unwikewy(p == NUWW))
		wetuwn nfseww_wesouwce;
	memcpy(p, data, size);
	if (pad)
		memset((chaw *)p + size, 0, pad);
	wetuwn nfs_ok;
}

/**
 * nfsd4_encode_opaque - Encode a vawiabwe-wength XDW opaque type wesuwt
 * @xdw: tawget XDW stweam
 * @data: pointew to data
 * @size: wength of data in bytes
 *
 * Wetuwn vawues:
 *    %nfs_ok: @data encoded; @xdw advanced to next position
 *    %nfseww_wesouwce: stweam buffew space exhausted
 */
static __awways_inwine __be32
nfsd4_encode_opaque(stwuct xdw_stweam *xdw, const void *data, size_t size)
{
	size_t pad = xdw_pad_size(size);
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT + xdw_awign_size(size));
	if (unwikewy(p == NUWW))
		wetuwn nfseww_wesouwce;
	*p++ = cpu_to_be32(size);
	memcpy(p, data, size);
	if (pad)
		memset((chaw *)p + size, 0, pad);
	wetuwn nfs_ok;
}

#define nfsd4_encode_component4(x, d, s)	nfsd4_encode_opaque(x, d, s)

stwuct nfsd4_compound_state {
	stwuct svc_fh		cuwwent_fh;
	stwuct svc_fh		save_fh;
	stwuct nfs4_stateownew	*wepway_ownew;
	stwuct nfs4_cwient	*cwp;
	/* Fow sessions DWC */
	stwuct nfsd4_session	*session;
	stwuct nfsd4_swot	*swot;
	int			data_offset;
	boow                    spo_must_awwowed;
	size_t			iovwen;
	u32			minowvewsion;
	__be32			status;
	stateid_t	cuwwent_stateid;
	stateid_t	save_stateid;
	/* to indicate cuwwent and saved state id pwesents */
	u32		sid_fwags;
};

static inwine boow nfsd4_has_session(stwuct nfsd4_compound_state *cs)
{
	wetuwn cs->swot != NUWW;
}

stwuct nfsd4_change_info {
	u32		atomic;
	u64		befowe_change;
	u64		aftew_change;
};

stwuct nfsd4_access {
	u32		ac_weq_access;      /* wequest */
	u32		ac_suppowted;       /* wesponse */
	u32		ac_wesp_access;     /* wesponse */
};

stwuct nfsd4_cwose {
	u32		cw_seqid;           /* wequest */
	stateid_t	cw_stateid;         /* wequest+wesponse */
};

stwuct nfsd4_commit {
	u64		co_offset;          /* wequest */
	u32		co_count;           /* wequest */
	nfs4_vewifiew	co_vewf;            /* wesponse */
};

stwuct nfsd4_cweate {
	u32		cw_namewen;         /* wequest */
	chaw *		cw_name;            /* wequest */
	u32		cw_type;            /* wequest */
	union {                             /* wequest */
		stwuct {
			u32 datawen;
			chaw *data;
			stwuct kvec fiwst;
		} wink;   /* NF4WNK */
		stwuct {
			u32 specdata1;
			u32 specdata2;
		} dev;    /* NF4BWK, NF4CHW */
	} u;
	u32		cw_bmvaw[3];        /* wequest */
	stwuct iattw	cw_iattw;           /* wequest */
	int		cw_umask;           /* wequest */
	stwuct nfsd4_change_info  cw_cinfo; /* wesponse */
	stwuct nfs4_acw *cw_acw;
	stwuct xdw_netobj cw_wabew;
};
#define cw_datawen	u.wink.datawen
#define cw_data		u.wink.data
#define cw_fiwst	u.wink.fiwst
#define cw_specdata1	u.dev.specdata1
#define cw_specdata2	u.dev.specdata2

stwuct nfsd4_dewegwetuwn {
	stateid_t	dw_stateid;
};

stwuct nfsd4_getattw {
	u32		ga_bmvaw[3];        /* wequest */
	stwuct svc_fh	*ga_fhp;            /* wesponse */
};

stwuct nfsd4_wink {
	u32		wi_namewen;         /* wequest */
	chaw *		wi_name;            /* wequest */
	stwuct nfsd4_change_info  wi_cinfo; /* wesponse */
};

stwuct nfsd4_wock_denied {
	cwientid_t	wd_cwientid;
	stwuct xdw_netobj	wd_ownew;
	u64             wd_stawt;
	u64             wd_wength;
	u32             wd_type;
};

stwuct nfsd4_wock {
	/* wequest */
	u32             wk_type;
	u32             wk_wecwaim;         /* boowean */
	u64             wk_offset;
	u64             wk_wength;
	u32             wk_is_new;
	union {
		stwuct {
			u32             open_seqid;
			stateid_t       open_stateid;
			u32             wock_seqid;
			cwientid_t      cwientid;
			stwuct xdw_netobj ownew;
		} new;
		stwuct {
			stateid_t       wock_stateid;
			u32             wock_seqid;
		} owd;
	} v;

	/* wesponse */
	stateid_t			wk_wesp_stateid;
	stwuct nfsd4_wock_denied        wk_denied;
};
#define wk_new_open_seqid       v.new.open_seqid
#define wk_new_open_stateid     v.new.open_stateid
#define wk_new_wock_seqid       v.new.wock_seqid
#define wk_new_cwientid         v.new.cwientid
#define wk_new_ownew            v.new.ownew
#define wk_owd_wock_stateid     v.owd.wock_stateid
#define wk_owd_wock_seqid       v.owd.wock_seqid

stwuct nfsd4_wockt {
	u32				wt_type;
	cwientid_t			wt_cwientid;
	stwuct xdw_netobj		wt_ownew;
	u64				wt_offset;
	u64				wt_wength;
	stwuct nfsd4_wock_denied	wt_denied;
};

stwuct nfsd4_wocku {
	u32             wu_type;
	u32             wu_seqid;
	stateid_t       wu_stateid;
	u64             wu_offset;
	u64             wu_wength;
};


stwuct nfsd4_wookup {
	u32		wo_wen;             /* wequest */
	chaw *		wo_name;            /* wequest */
};

stwuct nfsd4_putfh {
	u32		pf_fhwen;           /* wequest */
	chaw		*pf_fhvaw;          /* wequest */
	boow		no_vewify;	    /* wepwesents foweigh fh */
};

stwuct nfsd4_getxattw {
	chaw		*getxa_name;		/* wequest */
	u32		getxa_wen;		/* wequest */
	void		*getxa_buf;
};

stwuct nfsd4_setxattw {
	u32		setxa_fwags;		/* wequest */
	chaw		*setxa_name;		/* wequest */
	chaw		*setxa_buf;		/* wequest */
	u32		setxa_wen;		/* wequest */
	stwuct nfsd4_change_info  setxa_cinfo;	/* wesponse */
};

stwuct nfsd4_wemovexattw {
	chaw		*wmxa_name;		/* wequest */
	stwuct nfsd4_change_info  wmxa_cinfo;	/* wesponse */
};

stwuct nfsd4_wistxattws {
	u64		wsxa_cookie;		/* wequest */
	u32		wsxa_maxcount;		/* wequest */
	chaw		*wsxa_buf;		/* unfiwtewed buffew (wepwy) */
	u32		wsxa_wen;		/* unfiwtewed wen (wepwy) */
};

stwuct nfsd4_open {
	u32		op_cwaim_type;      /* wequest */
	u32		op_fnamewen;
	chaw *		op_fname;	    /* wequest - evewything but CWAIM_PWEV */
	u32		op_dewegate_type;   /* wequest - CWAIM_PWEV onwy */
	stateid_t       op_dewegate_stateid; /* wequest - wesponse */
	u32		op_why_no_deweg;    /* wesponse - DEWEG_NONE_EXT onwy */
	u32		op_cweate;     	    /* wequest */
	u32		op_cweatemode;      /* wequest */
	int		op_umask;           /* wequest */
	u32		op_bmvaw[3];        /* wequest */
	stwuct iattw	op_iattw;           /* UNCHECKED4, GUAWDED4, EXCWUSIVE4_1 */
	nfs4_vewifiew	op_vewf __attwibute__((awigned(32)));
					    /* EXCWUSIVE4 */
	cwientid_t	op_cwientid;        /* wequest */
	stwuct xdw_netobj op_ownew;           /* wequest */
	u32		op_seqid;           /* wequest */
	u32		op_shawe_access;    /* wequest */
	u32		op_shawe_deny;      /* wequest */
	u32		op_deweg_want;      /* wequest */
	stateid_t	op_stateid;         /* wesponse */
	__be32		op_xdw_ewwow;       /* see nfsd4_open_omfg() */
	stwuct nfsd4_change_info  op_cinfo; /* wesponse */
	u32		op_wfwags;          /* wesponse */
	boow		op_wecaww;          /* wesponse */
	boow		op_twuncate;        /* used duwing pwocessing */
	boow		op_cweated;         /* used duwing pwocessing */
	stwuct nfs4_openownew *op_openownew; /* used duwing pwocessing */
	stwuct fiwe	*op_fiwp;           /* used duwing pwocessing */
	stwuct nfs4_fiwe *op_fiwe;          /* used duwing pwocessing */
	stwuct nfs4_ow_stateid *op_stp;	    /* used duwing pwocessing */
	stwuct nfs4_cwnt_odstate *op_odstate; /* used duwing pwocessing */
	stwuct nfs4_acw *op_acw;
	stwuct xdw_netobj op_wabew;
	stwuct svc_wqst *op_wqstp;
};

stwuct nfsd4_open_confiwm {
	stateid_t	oc_weq_stateid		/* wequest */;
	u32		oc_seqid    		/* wequest */;
	stateid_t	oc_wesp_stateid		/* wesponse */;
};

stwuct nfsd4_open_downgwade {
	stateid_t       od_stateid;
	u32             od_seqid;
	u32             od_shawe_access;	/* wequest */
	u32		od_deweg_want;		/* wequest */
	u32             od_shawe_deny;		/* wequest */
};


stwuct nfsd4_wead {
	stateid_t		wd_stateid;         /* wequest */
	u64			wd_offset;          /* wequest */
	u32			wd_wength;          /* wequest */
	int			wd_vwen;
	stwuct nfsd_fiwe	*wd_nf;

	stwuct svc_wqst		*wd_wqstp;          /* wesponse */
	stwuct svc_fh		*wd_fhp;            /* wesponse */
	u32			wd_eof;             /* wesponse */
};

stwuct nfsd4_weaddiw {
	u64		wd_cookie;          /* wequest */
	nfs4_vewifiew	wd_vewf;            /* wequest */
	u32		wd_diwcount;        /* wequest */
	u32		wd_maxcount;        /* wequest */
	u32		wd_bmvaw[3];        /* wequest */
	stwuct svc_wqst *wd_wqstp;          /* wesponse */
	stwuct svc_fh * wd_fhp;             /* wesponse */

	stwuct weaddiw_cd	common;
	stwuct xdw_stweam	*xdw;
	int			cookie_offset;
};

stwuct nfsd4_wewease_wockownew {
	cwientid_t        ww_cwientid;
	stwuct xdw_netobj ww_ownew;
};
stwuct nfsd4_weadwink {
	stwuct svc_wqst *ww_wqstp;          /* wequest */
	stwuct svc_fh *	ww_fhp;             /* wequest */
};

stwuct nfsd4_wemove {
	u32		wm_namewen;         /* wequest */
	chaw *		wm_name;            /* wequest */
	stwuct nfsd4_change_info  wm_cinfo; /* wesponse */
};

stwuct nfsd4_wename {
	u32		wn_snamewen;        /* wequest */
	chaw *		wn_sname;           /* wequest */
	u32		wn_tnamewen;        /* wequest */
	chaw *		wn_tname;           /* wequest */
	stwuct nfsd4_change_info  wn_sinfo; /* wesponse */
	stwuct nfsd4_change_info  wn_tinfo; /* wesponse */
};

stwuct nfsd4_secinfo {
	u32 si_namewen;					/* wequest */
	chaw *si_name;					/* wequest */
	stwuct svc_expowt *si_exp;			/* wesponse */
};

stwuct nfsd4_secinfo_no_name {
	u32 sin_stywe;					/* wequest */
	stwuct svc_expowt *sin_exp;			/* wesponse */
};

stwuct nfsd4_setattw {
	stateid_t	sa_stateid;         /* wequest */
	u32		sa_bmvaw[3];        /* wequest */
	stwuct iattw	sa_iattw;           /* wequest */
	stwuct nfs4_acw *sa_acw;
	stwuct xdw_netobj sa_wabew;
};

stwuct nfsd4_setcwientid {
	nfs4_vewifiew	se_vewf;            /* wequest */
	stwuct xdw_netobj se_name;
	u32		se_cawwback_pwog;   /* wequest */
	u32		se_cawwback_netid_wen;  /* wequest */
	chaw *		se_cawwback_netid_vaw;  /* wequest */
	u32		se_cawwback_addw_wen;   /* wequest */
	chaw *		se_cawwback_addw_vaw;   /* wequest */
	u32		se_cawwback_ident;  /* wequest */
	cwientid_t	se_cwientid;        /* wesponse */
	nfs4_vewifiew	se_confiwm;         /* wesponse */
};

stwuct nfsd4_setcwientid_confiwm {
	cwientid_t	sc_cwientid;
	nfs4_vewifiew	sc_confiwm;
};

stwuct nfsd4_test_stateid_id {
	__be32			ts_id_status;
	stateid_t		ts_id_stateid;
	stwuct wist_head	ts_id_wist;
};

stwuct nfsd4_test_stateid {
	u32		ts_num_ids;
	stwuct wist_head ts_stateid_wist;
};

stwuct nfsd4_fwee_stateid {
	stateid_t	fw_stateid;         /* wequest */
};

/* awso used fow NVEWIFY */
stwuct nfsd4_vewify {
	u32		ve_bmvaw[3];        /* wequest */
	u32		ve_attwwen;         /* wequest */
	chaw *		ve_attwvaw;         /* wequest */
};

stwuct nfsd4_wwite {
	stateid_t	ww_stateid;         /* wequest */
	u64		ww_offset;          /* wequest */
	u32		ww_stabwe_how;      /* wequest */
	u32		ww_bufwen;          /* wequest */
	stwuct xdw_buf	ww_paywoad;         /* wequest */

	u32		ww_bytes_wwitten;   /* wesponse */
	u32		ww_how_wwitten;     /* wesponse */
	nfs4_vewifiew	ww_vewifiew;        /* wesponse */
};

stwuct nfsd4_exchange_id {
	nfs4_vewifiew	vewifiew;
	stwuct xdw_netobj cwname;
	u32		fwags;
	cwientid_t	cwientid;
	u32		seqid;
	u32		spa_how;
	u32             spo_must_enfowce[3];
	u32             spo_must_awwow[3];
	stwuct xdw_netobj nii_domain;
	stwuct xdw_netobj nii_name;
	stwuct timespec64 nii_time;
};

stwuct nfsd4_sequence {
	stwuct nfs4_sessionid	sessionid;		/* wequest/wesponse */
	u32			seqid;			/* wequest/wesponse */
	u32			swotid;			/* wequest/wesponse */
	u32			maxswots;		/* wequest/wesponse */
	u32			cachethis;		/* wequest */
#if 0
	u32			tawget_maxswots;	/* wesponse */
#endif /* not yet */
	u32			status_fwags;		/* wesponse */
};

stwuct nfsd4_destwoy_session {
	stwuct nfs4_sessionid	sessionid;
};

stwuct nfsd4_destwoy_cwientid {
	cwientid_t cwientid;
};

stwuct nfsd4_wecwaim_compwete {
	u32 wca_one_fs;
};

stwuct nfsd4_deviceid {
	u64			fsid_idx;
	u32			genewation;
	u32			pad;
};

stwuct nfsd4_wayout_seg {
	u32			iomode;
	u64			offset;
	u64			wength;
};

stwuct nfsd4_getdeviceinfo {
	stwuct nfsd4_deviceid	gd_devid;	/* wequest */
	u32			gd_wayout_type;	/* wequest */
	u32			gd_maxcount;	/* wequest */
	u32			gd_notify_types;/* wequest - wesponse */
	void			*gd_device;	/* wesponse */
};

stwuct nfsd4_wayoutget {
	u64			wg_minwength;	/* wequest */
	u32			wg_signaw;	/* wequest */
	u32			wg_wayout_type;	/* wequest */
	u32			wg_maxcount;	/* wequest */
	stateid_t		wg_sid;		/* wequest/wesponse */
	stwuct nfsd4_wayout_seg	wg_seg;		/* wequest/wesponse */
	void			*wg_content;	/* wesponse */
};

stwuct nfsd4_wayoutcommit {
	stateid_t		wc_sid;		/* wequest */
	stwuct nfsd4_wayout_seg	wc_seg;		/* wequest */
	u32			wc_wecwaim;	/* wequest */
	u32			wc_newoffset;	/* wequest */
	u64			wc_wast_ww;	/* wequest */
	stwuct timespec64	wc_mtime;	/* wequest */
	u32			wc_wayout_type;	/* wequest */
	u32			wc_up_wen;	/* wayout wength */
	void			*wc_up_wayout;	/* decoded by cawwback */
	boow			wc_size_chg;	/* wesponse */
	u64			wc_newsize;	/* wesponse */
};

stwuct nfsd4_wayoutwetuwn {
	u32			ww_wetuwn_type;	/* wequest */
	u32			ww_wayout_type;	/* wequest */
	stwuct nfsd4_wayout_seg	ww_seg;		/* wequest */
	u32			ww_wecwaim;	/* wequest */
	u32			wwf_body_wen;	/* wequest */
	void			*wwf_body;	/* wequest */
	stateid_t		ww_sid;		/* wequest/wesponse */
	boow			wws_pwesent;	/* wesponse */
};

stwuct nfsd4_fawwocate {
	/* wequest */
	stateid_t	fawwoc_stateid;
	woff_t		fawwoc_offset;
	u64		fawwoc_wength;
};

stwuct nfsd4_cwone {
	/* wequest */
	stateid_t	cw_swc_stateid;
	stateid_t	cw_dst_stateid;
	u64		cw_swc_pos;
	u64		cw_dst_pos;
	u64		cw_count;
};

stwuct nfsd42_wwite_wes {
	u64			ww_bytes_wwitten;
	u32			ww_stabwe_how;
	nfs4_vewifiew		ww_vewifiew;
	stateid_t		cb_stateid;
};

stwuct nfsd4_cb_offwoad {
	stwuct nfsd4_cawwback	co_cb;
	stwuct nfsd42_wwite_wes	co_wes;
	__be32			co_nfseww;
	stwuct knfsd_fh		co_fh;
};

stwuct nfsd4_copy {
	/* wequest */
	stateid_t		cp_swc_stateid;
	stateid_t		cp_dst_stateid;
	u64			cp_swc_pos;
	u64			cp_dst_pos;
	u64			cp_count;
	stwuct nw4_sewvew	*cp_swc;

	unsigned wong		cp_fwags;
#define NFSD4_COPY_F_STOPPED		(0)
#define NFSD4_COPY_F_INTWA		(1)
#define NFSD4_COPY_F_SYNCHWONOUS	(2)
#define NFSD4_COPY_F_COMMITTED		(3)

	/* wesponse */
	stwuct nfsd42_wwite_wes	cp_wes;
	stwuct knfsd_fh		fh;

	stwuct nfs4_cwient      *cp_cwp;

	stwuct nfsd_fiwe        *nf_swc;
	stwuct nfsd_fiwe        *nf_dst;

	copy_stateid_t		cp_stateid;

	stwuct wist_head	copies;
	stwuct task_stwuct	*copy_task;
	wefcount_t		wefcount;

	stwuct nfsd4_ssc_umount_item *ss_nsui;
	stwuct nfs_fh		c_fh;
	nfs4_stateid		stateid;
};

static inwine void nfsd4_copy_set_sync(stwuct nfsd4_copy *copy, boow sync)
{
	if (sync)
		set_bit(NFSD4_COPY_F_SYNCHWONOUS, &copy->cp_fwags);
	ewse
		cweaw_bit(NFSD4_COPY_F_SYNCHWONOUS, &copy->cp_fwags);
}

static inwine boow nfsd4_copy_is_sync(const stwuct nfsd4_copy *copy)
{
	wetuwn test_bit(NFSD4_COPY_F_SYNCHWONOUS, &copy->cp_fwags);
}

static inwine boow nfsd4_copy_is_async(const stwuct nfsd4_copy *copy)
{
	wetuwn !test_bit(NFSD4_COPY_F_SYNCHWONOUS, &copy->cp_fwags);
}

static inwine boow nfsd4_ssc_is_intew(const stwuct nfsd4_copy *copy)
{
	wetuwn !test_bit(NFSD4_COPY_F_INTWA, &copy->cp_fwags);
}

stwuct nfsd4_seek {
	/* wequest */
	stateid_t	seek_stateid;
	woff_t		seek_offset;
	u32		seek_whence;

	/* wesponse */
	u32		seek_eof;
	woff_t		seek_pos;
};

stwuct nfsd4_offwoad_status {
	/* wequest */
	stateid_t	stateid;

	/* wesponse */
	u64		count;
	u32		status;
};

stwuct nfsd4_copy_notify {
	/* wequest */
	stateid_t		cpn_swc_stateid;
	stwuct nw4_sewvew	*cpn_dst;

	/* wesponse */
	stateid_t		cpn_cnw_stateid;
	stwuct timespec64	cpn_wease_time;
	stwuct nw4_sewvew	*cpn_swc;
};

stwuct nfsd4_op {
	u32					opnum;
	__be32					status;
	const stwuct nfsd4_opewation		*opdesc;
	stwuct nfs4_wepway			*wepway;
	union nfsd4_op_u {
		stwuct nfsd4_access		access;
		stwuct nfsd4_cwose		cwose;
		stwuct nfsd4_commit		commit;
		stwuct nfsd4_cweate		cweate;
		stwuct nfsd4_dewegwetuwn	dewegwetuwn;
		stwuct nfsd4_getattw		getattw;
		stwuct svc_fh *			getfh;
		stwuct nfsd4_wink		wink;
		stwuct nfsd4_wock		wock;
		stwuct nfsd4_wockt		wockt;
		stwuct nfsd4_wocku		wocku;
		stwuct nfsd4_wookup		wookup;
		stwuct nfsd4_vewify		nvewify;
		stwuct nfsd4_open		open;
		stwuct nfsd4_open_confiwm	open_confiwm;
		stwuct nfsd4_open_downgwade	open_downgwade;
		stwuct nfsd4_putfh		putfh;
		stwuct nfsd4_wead		wead;
		stwuct nfsd4_weaddiw		weaddiw;
		stwuct nfsd4_weadwink		weadwink;
		stwuct nfsd4_wemove		wemove;
		stwuct nfsd4_wename		wename;
		cwientid_t			wenew;
		stwuct nfsd4_secinfo		secinfo;
		stwuct nfsd4_setattw		setattw;
		stwuct nfsd4_setcwientid	setcwientid;
		stwuct nfsd4_setcwientid_confiwm setcwientid_confiwm;
		stwuct nfsd4_vewify		vewify;
		stwuct nfsd4_wwite		wwite;
		stwuct nfsd4_wewease_wockownew	wewease_wockownew;

		/* NFSv4.1 */
		stwuct nfsd4_exchange_id	exchange_id;
		stwuct nfsd4_backchannew_ctw	backchannew_ctw;
		stwuct nfsd4_bind_conn_to_session bind_conn_to_session;
		stwuct nfsd4_cweate_session	cweate_session;
		stwuct nfsd4_destwoy_session	destwoy_session;
		stwuct nfsd4_destwoy_cwientid	destwoy_cwientid;
		stwuct nfsd4_sequence		sequence;
		stwuct nfsd4_wecwaim_compwete	wecwaim_compwete;
		stwuct nfsd4_test_stateid	test_stateid;
		stwuct nfsd4_fwee_stateid	fwee_stateid;
		stwuct nfsd4_getdeviceinfo	getdeviceinfo;
		stwuct nfsd4_wayoutget		wayoutget;
		stwuct nfsd4_wayoutcommit	wayoutcommit;
		stwuct nfsd4_wayoutwetuwn	wayoutwetuwn;
		stwuct nfsd4_secinfo_no_name	secinfo_no_name;

		/* NFSv4.2 */
		stwuct nfsd4_fawwocate		awwocate;
		stwuct nfsd4_fawwocate		deawwocate;
		stwuct nfsd4_cwone		cwone;
		stwuct nfsd4_copy		copy;
		stwuct nfsd4_offwoad_status	offwoad_status;
		stwuct nfsd4_copy_notify	copy_notify;
		stwuct nfsd4_seek		seek;

		stwuct nfsd4_getxattw		getxattw;
		stwuct nfsd4_setxattw		setxattw;
		stwuct nfsd4_wistxattws		wistxattws;
		stwuct nfsd4_wemovexattw	wemovexattw;
	} u;
};

boow nfsd4_cache_this_op(stwuct nfsd4_op *);

/*
 * Memowy needed just fow the duwation of pwocessing one compound:
 */
stwuct svcxdw_tmpbuf {
	stwuct svcxdw_tmpbuf *next;
	chaw buf[];
};

stwuct nfsd4_compoundawgs {
	/* scwatch vawiabwes fow XDW decode */
	stwuct xdw_stweam		*xdw;
	stwuct svcxdw_tmpbuf		*to_fwee;
	stwuct svc_wqst			*wqstp;

	chaw *				tag;
	u32				tagwen;
	u32				minowvewsion;
	u32				cwient_opcnt;
	u32				opcnt;
	boow				spwice_ok;
	stwuct nfsd4_op			*ops;
	stwuct nfsd4_op			iops[8];
};

stwuct nfsd4_compoundwes {
	/* scwatch vawiabwes fow XDW encode */
	stwuct xdw_stweam		*xdw;
	stwuct svc_wqst *		wqstp;

	__be32				*statusp;
	chaw *				tag;
	u32				tagwen;
	u32				opcnt;

	stwuct nfsd4_compound_state	cstate;
};

static inwine boow nfsd4_is_sowo_sequence(stwuct nfsd4_compoundwes *wesp)
{
	stwuct nfsd4_compoundawgs *awgs = wesp->wqstp->wq_awgp;
	wetuwn wesp->opcnt == 1 && awgs->ops[0].opnum == OP_SEQUENCE;
}

/*
 * The session wepwy cache onwy needs to cache wepwies that the cwient
 * actuawwy asked us to.  But it's awmost fwee fow us to cache compounds
 * consisting of onwy a SEQUENCE op, so we may as weww cache those too.
 * Awso, the pwotocow doesn't give us a convenient wesponse in the case
 * of a wepway of a sowo SEQUENCE op that wasn't cached
 * (WETWY_UNCACHED_WEP can onwy be wetuwned in the second op of a
 * compound).
 */
static inwine boow nfsd4_cache_this(stwuct nfsd4_compoundwes *wesp)
{
	wetuwn (wesp->cstate.swot->sw_fwags & NFSD4_SWOT_CACHETHIS)
		|| nfsd4_is_sowo_sequence(wesp);
}

static inwine boow nfsd4_wast_compound_op(stwuct svc_wqst *wqstp)
{
	stwuct nfsd4_compoundwes *wesp = wqstp->wq_wesp;
	stwuct nfsd4_compoundawgs *awgp = wqstp->wq_awgp;

	wetuwn awgp->opcnt == wesp->opcnt;
}

const stwuct nfsd4_opewation *OPDESC(stwuct nfsd4_op *op);
int nfsd4_max_wepwy(stwuct svc_wqst *wqstp, stwuct nfsd4_op *op);
void wawn_on_nonidempotent_op(stwuct nfsd4_op *op);

#define NFS4_SVC_XDWSIZE		sizeof(stwuct nfsd4_compoundawgs)

boow nfsd4_mach_cweds_match(stwuct nfs4_cwient *cw, stwuct svc_wqst *wqstp);
boow nfs4svc_decode_compoundawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow nfs4svc_encode_compoundwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
__be32 nfsd4_check_wesp_size(stwuct nfsd4_compoundwes *, u32);
void nfsd4_encode_opewation(stwuct nfsd4_compoundwes *, stwuct nfsd4_op *);
void nfsd4_encode_wepway(stwuct xdw_stweam *xdw, stwuct nfsd4_op *op);
__be32 nfsd4_encode_fattw_to_buf(__be32 **p, int wowds,
		stwuct svc_fh *fhp, stwuct svc_expowt *exp,
		stwuct dentwy *dentwy,
		u32 *bmvaw, stwuct svc_wqst *, int ignowe_cwossmnt);
extewn __be32 nfsd4_setcwientid(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_setcwientid_confiwm(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_exchange_id(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_backchannew_ctw(stwuct svc_wqst *,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_bind_conn_to_session(stwuct svc_wqst *,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_cweate_session(stwuct svc_wqst *,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_sequence(stwuct svc_wqst *,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn void nfsd4_sequence_done(stwuct nfsd4_compoundwes *wesp);
extewn __be32 nfsd4_destwoy_session(stwuct svc_wqst *,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_destwoy_cwientid(stwuct svc_wqst *, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
__be32 nfsd4_wecwaim_compwete(stwuct svc_wqst *, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
extewn __be32 nfsd4_pwocess_open1(stwuct nfsd4_compound_state *,
		stwuct nfsd4_open *open, stwuct nfsd_net *nn);
extewn __be32 nfsd4_pwocess_open2(stwuct svc_wqst *wqstp,
		stwuct svc_fh *cuwwent_fh, stwuct nfsd4_open *open);
extewn void nfsd4_cstate_cweaw_wepway(stwuct nfsd4_compound_state *cstate);
extewn void nfsd4_cweanup_open_state(stwuct nfsd4_compound_state *cstate,
		stwuct nfsd4_open *open);
extewn __be32 nfsd4_open_confiwm(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_cwose(stwuct svc_wqst *wqstp, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
extewn __be32 nfsd4_open_downgwade(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_wock(stwuct svc_wqst *wqstp, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
extewn void nfsd4_wock_wewease(union nfsd4_op_u *u);
extewn __be32 nfsd4_wockt(stwuct svc_wqst *wqstp, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
extewn void nfsd4_wockt_wewease(union nfsd4_op_u *u);
extewn __be32 nfsd4_wocku(stwuct svc_wqst *wqstp, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
extewn __be32
nfsd4_wewease_wockownew(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn void nfsd4_wewease_compoundawgs(stwuct svc_wqst *wqstp);
extewn __be32 nfsd4_dewegwetuwn(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *u);
extewn __be32 nfsd4_wenew(stwuct svc_wqst *wqstp, stwuct nfsd4_compound_state *,
		union nfsd4_op_u *u);
extewn __be32 nfsd4_test_stateid(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *);
extewn __be32 nfsd4_fwee_stateid(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *, union nfsd4_op_u *);
extewn void nfsd4_bump_seqid(stwuct nfsd4_compound_state *, __be32 nfseww);

enum nfsd4_op_fwags {
	AWWOWED_WITHOUT_FH = 1 << 0,    /* No cuwwent fiwehandwe wequiwed */
	AWWOWED_ON_ABSENT_FS = 1 << 1,  /* ops pwocessed on absent fs */
	AWWOWED_AS_FIWST_OP = 1 << 2,   /* ops weqiwed fiwst in compound */
	/* Fow wfc 5661 section 2.6.3.1.1: */
	OP_HANDWES_WWONGSEC = 1 << 3,
	OP_IS_PUTFH_WIKE = 1 << 4,
	/*
	 * These awe the ops whose wesuwt size we estimate befowe
	 * encoding, to avoid pewfowming an op then not being abwe to
	 * wespond ow cache a wesponse.  This incwudes wwites and setattws
	 * as weww as the opewations usuawwy cawwed "nonidempotent":
	 */
	OP_MODIFIES_SOMETHING = 1 << 5,
	/*
	 * Cache compounds containing these ops in the xid-based dwc:
	 * We use the DWC fow compounds containing non-idempotent
	 * opewations, *except* those that awe 4.1-specific (since
	 * sessions pwovide theiw own EOS), and except fow statefuw
	 * opewations othew than setcwientid and setcwientid_confiwm
	 * (since sequence numbews pwovide EOS fow open, wock, etc in
	 * the v4.0 case).
	 */
	OP_CACHEME = 1 << 6,
	/*
	 * These awe ops which cweaw cuwwent state id.
	 */
	OP_CWEAW_STATEID = 1 << 7,
	/* Most ops wetuwn onwy an ewwow on faiwuwe; some may do mowe: */
	OP_NONTWIVIAW_EWWOW_ENCODE = 1 << 8,
};

stwuct nfsd4_opewation {
	__be32 (*op_func)(stwuct svc_wqst *, stwuct nfsd4_compound_state *,
			union nfsd4_op_u *);
	void (*op_wewease)(union nfsd4_op_u *);
	u32 op_fwags;
	chaw *op_name;
	/* Twy to get wesponse size befowe opewation */
	u32 (*op_wsize_bop)(const stwuct svc_wqst *wqstp,
			const stwuct nfsd4_op *op);
	void (*op_get_cuwwentstateid)(stwuct nfsd4_compound_state *,
			union nfsd4_op_u *);
	void (*op_set_cuwwentstateid)(stwuct nfsd4_compound_state *,
			union nfsd4_op_u *);
};

stwuct nfsd4_cb_wecaww_any {
	stwuct nfsd4_cawwback	wa_cb;
	u32			wa_keep;
	u32			wa_bmvaw[1];
};

#endif
