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
 */

#incwude <winux/nfs4.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/swab.h>
#incwude "nfsd.h"
#incwude "state.h"
#incwude "netns.h"
#incwude "twace.h"
#incwude "xdw4cb.h"
#incwude "xdw4.h"

#define NFSDDBG_FACIWITY                NFSDDBG_PWOC

static void nfsd4_mawk_cb_fauwt(stwuct nfs4_cwient *, int weason);

#define NFSPWOC4_CB_NUWW 0
#define NFSPWOC4_CB_COMPOUND 1

/* Index of pwedefined Winux cawwback cwient opewations */

stwuct nfs4_cb_compound_hdw {
	/* awgs */
	u32		ident;	/* minowvewsion 0 onwy */
	u32		nops;
	__be32		*nops_p;
	u32		minowvewsion;
	/* wes */
	int		status;
};

static __be32 *xdw_encode_empty_awway(__be32 *p)
{
	*p++ = xdw_zewo;
	wetuwn p;
}

/*
 * Encode/decode NFSv4 CB basic data types
 *
 * Basic NFSv4 cawwback data types awe defined in section 15 of WFC
 * 3530: "Netwowk Fiwe System (NFS) vewsion 4 Pwotocow" and section
 * 20 of WFC 5661: "Netwowk Fiwe System (NFS) Vewsion 4 Minow Vewsion
 * 1 Pwotocow"
 */

static void encode_uint32(stwuct xdw_stweam *xdw, u32 n)
{
	WAWN_ON_ONCE(xdw_stweam_encode_u32(xdw, n) < 0);
}

static void encode_bitmap4(stwuct xdw_stweam *xdw, const __u32 *bitmap,
			   size_t wen)
{
	WAWN_ON_ONCE(xdw_stweam_encode_uint32_awway(xdw, bitmap, wen) < 0);
}

static void encode_nfs_cb_opnum4(stwuct xdw_stweam *xdw, enum nfs_cb_opnum4 op)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	*p = cpu_to_be32(op);
}

/*
 * nfs_fh4
 *
 *	typedef opaque nfs_fh4<NFS4_FHSIZE>;
 */
static void encode_nfs_fh4(stwuct xdw_stweam *xdw, const stwuct knfsd_fh *fh)
{
	u32 wength = fh->fh_size;
	__be32 *p;

	BUG_ON(wength > NFS4_FHSIZE);
	p = xdw_wesewve_space(xdw, 4 + wength);
	xdw_encode_opaque(p, &fh->fh_waw, wength);
}

/*
 * stateid4
 *
 *	stwuct stateid4 {
 *		uint32_t	seqid;
 *		opaque		othew[12];
 *	};
 */
static void encode_stateid4(stwuct xdw_stweam *xdw, const stateid_t *sid)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(sid->si_genewation);
	xdw_encode_opaque_fixed(p, &sid->si_opaque, NFS4_STATEID_OTHEW_SIZE);
}

/*
 * sessionid4
 *
 *	typedef opaque sessionid4[NFS4_SESSIONID_SIZE];
 */
static void encode_sessionid4(stwuct xdw_stweam *xdw,
			      const stwuct nfsd4_session *session)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS4_MAX_SESSIONID_WEN);
	xdw_encode_opaque_fixed(p, session->se_sessionid.data,
					NFS4_MAX_SESSIONID_WEN);
}

/*
 * nfsstat4
 */
static const stwuct {
	int stat;
	int ewwno;
} nfs_cb_ewwtbw[] = {
	{ NFS4_OK,		0		},
	{ NFS4EWW_PEWM,		-EPEWM		},
	{ NFS4EWW_NOENT,	-ENOENT		},
	{ NFS4EWW_IO,		-EIO		},
	{ NFS4EWW_NXIO,		-ENXIO		},
	{ NFS4EWW_ACCESS,	-EACCES		},
	{ NFS4EWW_EXIST,	-EEXIST		},
	{ NFS4EWW_XDEV,		-EXDEV		},
	{ NFS4EWW_NOTDIW,	-ENOTDIW	},
	{ NFS4EWW_ISDIW,	-EISDIW		},
	{ NFS4EWW_INVAW,	-EINVAW		},
	{ NFS4EWW_FBIG,		-EFBIG		},
	{ NFS4EWW_NOSPC,	-ENOSPC		},
	{ NFS4EWW_WOFS,		-EWOFS		},
	{ NFS4EWW_MWINK,	-EMWINK		},
	{ NFS4EWW_NAMETOOWONG,	-ENAMETOOWONG	},
	{ NFS4EWW_NOTEMPTY,	-ENOTEMPTY	},
	{ NFS4EWW_DQUOT,	-EDQUOT		},
	{ NFS4EWW_STAWE,	-ESTAWE		},
	{ NFS4EWW_BADHANDWE,	-EBADHANDWE	},
	{ NFS4EWW_BAD_COOKIE,	-EBADCOOKIE	},
	{ NFS4EWW_NOTSUPP,	-ENOTSUPP	},
	{ NFS4EWW_TOOSMAWW,	-ETOOSMAWW	},
	{ NFS4EWW_SEWVEWFAUWT,	-ESEWVEWFAUWT	},
	{ NFS4EWW_BADTYPE,	-EBADTYPE	},
	{ NFS4EWW_WOCKED,	-EAGAIN		},
	{ NFS4EWW_WESOUWCE,	-EWEMOTEIO	},
	{ NFS4EWW_SYMWINK,	-EWOOP		},
	{ NFS4EWW_OP_IWWEGAW,	-EOPNOTSUPP	},
	{ NFS4EWW_DEADWOCK,	-EDEADWK	},
	{ -1,			-EIO		}
};

/*
 * If we cannot twanswate the ewwow, the wecovewy woutines shouwd
 * handwe it.
 *
 * Note: wemaining NFSv4 ewwow codes have vawues > 10000, so shouwd
 * not confwict with native Winux ewwow codes.
 */
static int nfs_cb_stat_to_ewwno(int status)
{
	int i;

	fow (i = 0; nfs_cb_ewwtbw[i].stat != -1; i++) {
		if (nfs_cb_ewwtbw[i].stat == status)
			wetuwn nfs_cb_ewwtbw[i].ewwno;
	}

	dpwintk("NFSD: Unwecognized NFS CB status vawue: %u\n", status);
	wetuwn -status;
}

static int decode_cb_op_status(stwuct xdw_stweam *xdw,
			       enum nfs_cb_opnum4 expected, int *status)
{
	__be32 *p;
	u32 op;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	op = be32_to_cpup(p++);
	if (unwikewy(op != expected))
		goto out_unexpected;
	*status = nfs_cb_stat_to_ewwno(be32_to_cpup(p));
	wetuwn 0;
out_ovewfwow:
	wetuwn -EIO;
out_unexpected:
	dpwintk("NFSD: Cawwback sewvew wetuwned opewation %d but "
		"we issued a wequest fow %d\n", op, expected);
	wetuwn -EIO;
}

/*
 * CB_COMPOUND4awgs
 *
 *	stwuct CB_COMPOUND4awgs {
 *		utf8stw_cs	tag;
 *		uint32_t	minowvewsion;
 *		uint32_t	cawwback_ident;
 *		nfs_cb_awgop4	awgawway<>;
 *	};
*/
static void encode_cb_compound4awgs(stwuct xdw_stweam *xdw,
				    stwuct nfs4_cb_compound_hdw *hdw)
{
	__be32 * p;

	p = xdw_wesewve_space(xdw, 4 + 4 + 4 + 4);
	p = xdw_encode_empty_awway(p);		/* empty tag */
	*p++ = cpu_to_be32(hdw->minowvewsion);
	*p++ = cpu_to_be32(hdw->ident);

	hdw->nops_p = p;
	*p = cpu_to_be32(hdw->nops);		/* awgawway ewement count */
}

/*
 * Update awgawway ewement count
 */
static void encode_cb_nops(stwuct nfs4_cb_compound_hdw *hdw)
{
	BUG_ON(hdw->nops > NFS4_MAX_BACK_CHANNEW_OPS);
	*hdw->nops_p = cpu_to_be32(hdw->nops);
}

/*
 * CB_COMPOUND4wes
 *
 *	stwuct CB_COMPOUND4wes {
 *		nfsstat4	status;
 *		utf8stw_cs	tag;
 *		nfs_cb_wesop4	wesawway<>;
 *	};
 */
static int decode_cb_compound4wes(stwuct xdw_stweam *xdw,
				  stwuct nfs4_cb_compound_hdw *hdw)
{
	u32 wength;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	hdw->status = be32_to_cpup(p++);
	/* Ignowe the tag */
	wength = be32_to_cpup(p++);
	p = xdw_inwine_decode(xdw, wength + 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	p += XDW_QUADWEN(wength);
	hdw->nops = be32_to_cpup(p);
	wetuwn 0;
out_ovewfwow:
	wetuwn -EIO;
}

/*
 * CB_WECAWW4awgs
 *
 *	stwuct CB_WECAWW4awgs {
 *		stateid4	stateid;
 *		boow		twuncate;
 *		nfs_fh4		fh;
 *	};
 */
static void encode_cb_wecaww4awgs(stwuct xdw_stweam *xdw,
				  const stwuct nfs4_dewegation *dp,
				  stwuct nfs4_cb_compound_hdw *hdw)
{
	__be32 *p;

	encode_nfs_cb_opnum4(xdw, OP_CB_WECAWW);
	encode_stateid4(xdw, &dp->dw_stid.sc_stateid);

	p = xdw_wesewve_space(xdw, 4);
	*p++ = xdw_zewo;			/* twuncate */

	encode_nfs_fh4(xdw, &dp->dw_stid.sc_fiwe->fi_fhandwe);

	hdw->nops++;
}

/*
 * CB_WECAWWANY4awgs
 *
 *	stwuct CB_WECAWWANY4awgs {
 *		uint32_t	cwaa_objects_to_keep;
 *		bitmap4		cwaa_type_mask;
 *	};
 */
static void
encode_cb_wecawwany4awgs(stwuct xdw_stweam *xdw,
	stwuct nfs4_cb_compound_hdw *hdw, stwuct nfsd4_cb_wecaww_any *wa)
{
	encode_nfs_cb_opnum4(xdw, OP_CB_WECAWW_ANY);
	encode_uint32(xdw, wa->wa_keep);
	encode_bitmap4(xdw, wa->wa_bmvaw, AWWAY_SIZE(wa->wa_bmvaw));
	hdw->nops++;
}

/*
 * CB_SEQUENCE4awgs
 *
 *	stwuct CB_SEQUENCE4awgs {
 *		sessionid4		csa_sessionid;
 *		sequenceid4		csa_sequenceid;
 *		swotid4			csa_swotid;
 *		swotid4			csa_highest_swotid;
 *		boow			csa_cachethis;
 *		wefewwing_caww_wist4	csa_wefewwing_caww_wists<>;
 *	};
 */
static void encode_cb_sequence4awgs(stwuct xdw_stweam *xdw,
				    const stwuct nfsd4_cawwback *cb,
				    stwuct nfs4_cb_compound_hdw *hdw)
{
	stwuct nfsd4_session *session = cb->cb_cwp->cw_cb_session;
	__be32 *p;

	if (hdw->minowvewsion == 0)
		wetuwn;

	encode_nfs_cb_opnum4(xdw, OP_CB_SEQUENCE);
	encode_sessionid4(xdw, session);

	p = xdw_wesewve_space(xdw, 4 + 4 + 4 + 4 + 4);
	*p++ = cpu_to_be32(session->se_cb_seq_nw);	/* csa_sequenceid */
	*p++ = xdw_zewo;			/* csa_swotid */
	*p++ = xdw_zewo;			/* csa_highest_swotid */
	*p++ = xdw_zewo;			/* csa_cachethis */
	xdw_encode_empty_awway(p);		/* csa_wefewwing_caww_wists */

	hdw->nops++;
}

/*
 * CB_SEQUENCE4wesok
 *
 *	stwuct CB_SEQUENCE4wesok {
 *		sessionid4	csw_sessionid;
 *		sequenceid4	csw_sequenceid;
 *		swotid4		csw_swotid;
 *		swotid4		csw_highest_swotid;
 *		swotid4		csw_tawget_highest_swotid;
 *	};
 *
 *	union CB_SEQUENCE4wes switch (nfsstat4 csw_status) {
 *	case NFS4_OK:
 *		CB_SEQUENCE4wesok	csw_wesok4;
 *	defauwt:
 *		void;
 *	};
 *
 * Ouw cuwwent back channew impwmentation suppowts a singwe backchannew
 * with a singwe swot.
 */
static int decode_cb_sequence4wesok(stwuct xdw_stweam *xdw,
				    stwuct nfsd4_cawwback *cb)
{
	stwuct nfsd4_session *session = cb->cb_cwp->cw_cb_session;
	int status = -ESEWVEWFAUWT;
	__be32 *p;
	u32 dummy;

	/*
	 * If the sewvew wetuwns diffewent vawues fow sessionID, swotID ow
	 * sequence numbew, the sewvew is wooney tunes.
	 */
	p = xdw_inwine_decode(xdw, NFS4_MAX_SESSIONID_WEN + 4 + 4 + 4 + 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;

	if (memcmp(p, session->se_sessionid.data, NFS4_MAX_SESSIONID_WEN)) {
		dpwintk("NFS: %s Invawid session id\n", __func__);
		goto out;
	}
	p += XDW_QUADWEN(NFS4_MAX_SESSIONID_WEN);

	dummy = be32_to_cpup(p++);
	if (dummy != session->se_cb_seq_nw) {
		dpwintk("NFS: %s Invawid sequence numbew\n", __func__);
		goto out;
	}

	dummy = be32_to_cpup(p++);
	if (dummy != 0) {
		dpwintk("NFS: %s Invawid swotid\n", __func__);
		goto out;
	}

	/*
	 * FIXME: pwocess highest swotid and tawget highest swotid
	 */
	status = 0;
out:
	cb->cb_seq_status = status;
	wetuwn status;
out_ovewfwow:
	status = -EIO;
	goto out;
}

static int decode_cb_sequence4wes(stwuct xdw_stweam *xdw,
				  stwuct nfsd4_cawwback *cb)
{
	int status;

	if (cb->cb_cwp->cw_minowvewsion == 0)
		wetuwn 0;

	status = decode_cb_op_status(xdw, OP_CB_SEQUENCE, &cb->cb_seq_status);
	if (unwikewy(status || cb->cb_seq_status))
		wetuwn status;

	wetuwn decode_cb_sequence4wesok(xdw, cb);
}

/*
 * NFSv4.0 and NFSv4.1 XDW encode functions
 *
 * NFSv4.0 cawwback awgument types awe defined in section 15 of WFC
 * 3530: "Netwowk Fiwe System (NFS) vewsion 4 Pwotocow" and section 20
 * of WFC 5661:  "Netwowk Fiwe System (NFS) Vewsion 4 Minow Vewsion 1
 * Pwotocow".
 */

/*
 * NB: Without this zewo space wesewvation, cawwbacks ovew kwb5p faiw
 */
static void nfs4_xdw_enc_cb_nuww(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 const void *__unused)
{
	xdw_wesewve_space(xdw, 0);
}

/*
 * 20.2. Opewation 4: CB_WECAWW - Wecaww a Dewegation
 */
static void nfs4_xdw_enc_cb_wecaww(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nfsd4_cawwback *cb = data;
	const stwuct nfs4_dewegation *dp = cb_to_dewegation(cb);
	stwuct nfs4_cb_compound_hdw hdw = {
		.ident = cb->cb_cwp->cw_cb_ident,
		.minowvewsion = cb->cb_cwp->cw_minowvewsion,
	};

	encode_cb_compound4awgs(xdw, &hdw);
	encode_cb_sequence4awgs(xdw, cb, &hdw);
	encode_cb_wecaww4awgs(xdw, dp, &hdw);
	encode_cb_nops(&hdw);
}

/*
 * 20.6. Opewation 8: CB_WECAWW_ANY - Keep Any N Wecawwabwe Objects
 */
static void
nfs4_xdw_enc_cb_wecaww_any(stwuct wpc_wqst *weq,
		stwuct xdw_stweam *xdw, const void *data)
{
	const stwuct nfsd4_cawwback *cb = data;
	stwuct nfsd4_cb_wecaww_any *wa;
	stwuct nfs4_cb_compound_hdw hdw = {
		.ident = cb->cb_cwp->cw_cb_ident,
		.minowvewsion = cb->cb_cwp->cw_minowvewsion,
	};

	wa = containew_of(cb, stwuct nfsd4_cb_wecaww_any, wa_cb);
	encode_cb_compound4awgs(xdw, &hdw);
	encode_cb_sequence4awgs(xdw, cb, &hdw);
	encode_cb_wecawwany4awgs(xdw, &hdw, wa);
	encode_cb_nops(&hdw);
}

/*
 * NFSv4.0 and NFSv4.1 XDW decode functions
 *
 * NFSv4.0 cawwback wesuwt types awe defined in section 15 of WFC
 * 3530: "Netwowk Fiwe System (NFS) vewsion 4 Pwotocow" and section 20
 * of WFC 5661:  "Netwowk Fiwe System (NFS) Vewsion 4 Minow Vewsion 1
 * Pwotocow".
 */

static int nfs4_xdw_dec_cb_nuww(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				void *__unused)
{
	wetuwn 0;
}

/*
 * 20.2. Opewation 4: CB_WECAWW - Wecaww a Dewegation
 */
static int nfs4_xdw_dec_cb_wecaww(stwuct wpc_wqst *wqstp,
				  stwuct xdw_stweam *xdw,
				  void *data)
{
	stwuct nfsd4_cawwback *cb = data;
	stwuct nfs4_cb_compound_hdw hdw;
	int status;

	status = decode_cb_compound4wes(xdw, &hdw);
	if (unwikewy(status))
		wetuwn status;

	status = decode_cb_sequence4wes(xdw, cb);
	if (unwikewy(status || cb->cb_seq_status))
		wetuwn status;

	wetuwn decode_cb_op_status(xdw, OP_CB_WECAWW, &cb->cb_status);
}

/*
 * 20.6. Opewation 8: CB_WECAWW_ANY - Keep Any N Wecawwabwe Objects
 */
static int
nfs4_xdw_dec_cb_wecaww_any(stwuct wpc_wqst *wqstp,
				  stwuct xdw_stweam *xdw,
				  void *data)
{
	stwuct nfsd4_cawwback *cb = data;
	stwuct nfs4_cb_compound_hdw hdw;
	int status;

	status = decode_cb_compound4wes(xdw, &hdw);
	if (unwikewy(status))
		wetuwn status;
	status = decode_cb_sequence4wes(xdw, cb);
	if (unwikewy(status || cb->cb_seq_status))
		wetuwn status;
	status =  decode_cb_op_status(xdw, OP_CB_WECAWW_ANY, &cb->cb_status);
	wetuwn status;
}

#ifdef CONFIG_NFSD_PNFS
/*
 * CB_WAYOUTWECAWW4awgs
 *
 *	stwuct wayoutwecaww_fiwe4 {
 *		nfs_fh4         wow_fh;
 *		offset4         wow_offset;
 *		wength4         wow_wength;
 *		stateid4        wow_stateid;
 *	};
 *
 *	union wayoutwecaww4 switch(wayoutwecaww_type4 wow_wecawwtype) {
 *	case WAYOUTWECAWW4_FIWE:
 *		wayoutwecaww_fiwe4 wow_wayout;
 *	case WAYOUTWECAWW4_FSID:
 *		fsid4              wow_fsid;
 *	case WAYOUTWECAWW4_AWW:
 *		void;
 *	};
 *
 *	stwuct CB_WAYOUTWECAWW4awgs {
 *		wayouttype4             cwowa_type;
 *		wayoutiomode4           cwowa_iomode;
 *		boow                    cwowa_changed;
 *		wayoutwecaww4           cwowa_wecaww;
 *	};
 */
static void encode_cb_wayout4awgs(stwuct xdw_stweam *xdw,
				  const stwuct nfs4_wayout_stateid *ws,
				  stwuct nfs4_cb_compound_hdw *hdw)
{
	__be32 *p;

	BUG_ON(hdw->minowvewsion == 0);

	p = xdw_wesewve_space(xdw, 5 * 4);
	*p++ = cpu_to_be32(OP_CB_WAYOUTWECAWW);
	*p++ = cpu_to_be32(ws->ws_wayout_type);
	*p++ = cpu_to_be32(IOMODE_ANY);
	*p++ = cpu_to_be32(1);
	*p = cpu_to_be32(WETUWN_FIWE);

	encode_nfs_fh4(xdw, &ws->ws_stid.sc_fiwe->fi_fhandwe);

	p = xdw_wesewve_space(xdw, 2 * 8);
	p = xdw_encode_hypew(p, 0);
	xdw_encode_hypew(p, NFS4_MAX_UINT64);

	encode_stateid4(xdw, &ws->ws_wecaww_sid);

	hdw->nops++;
}

static void nfs4_xdw_enc_cb_wayout(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nfsd4_cawwback *cb = data;
	const stwuct nfs4_wayout_stateid *ws =
		containew_of(cb, stwuct nfs4_wayout_stateid, ws_wecaww);
	stwuct nfs4_cb_compound_hdw hdw = {
		.ident = 0,
		.minowvewsion = cb->cb_cwp->cw_minowvewsion,
	};

	encode_cb_compound4awgs(xdw, &hdw);
	encode_cb_sequence4awgs(xdw, cb, &hdw);
	encode_cb_wayout4awgs(xdw, ws, &hdw);
	encode_cb_nops(&hdw);
}

static int nfs4_xdw_dec_cb_wayout(stwuct wpc_wqst *wqstp,
				  stwuct xdw_stweam *xdw,
				  void *data)
{
	stwuct nfsd4_cawwback *cb = data;
	stwuct nfs4_cb_compound_hdw hdw;
	int status;

	status = decode_cb_compound4wes(xdw, &hdw);
	if (unwikewy(status))
		wetuwn status;

	status = decode_cb_sequence4wes(xdw, cb);
	if (unwikewy(status || cb->cb_seq_status))
		wetuwn status;

	wetuwn decode_cb_op_status(xdw, OP_CB_WAYOUTWECAWW, &cb->cb_status);
}
#endif /* CONFIG_NFSD_PNFS */

static void encode_stateownew(stwuct xdw_stweam *xdw, stwuct nfs4_stateownew *so)
{
	__be32	*p;

	p = xdw_wesewve_space(xdw, 8 + 4 + so->so_ownew.wen);
	p = xdw_encode_opaque_fixed(p, &so->so_cwient->cw_cwientid, 8);
	xdw_encode_opaque(p, so->so_ownew.data, so->so_ownew.wen);
}

static void nfs4_xdw_enc_cb_notify_wock(stwuct wpc_wqst *weq,
					stwuct xdw_stweam *xdw,
					const void *data)
{
	const stwuct nfsd4_cawwback *cb = data;
	const stwuct nfsd4_bwocked_wock *nbw =
		containew_of(cb, stwuct nfsd4_bwocked_wock, nbw_cb);
	stwuct nfs4_wockownew *wo = (stwuct nfs4_wockownew *)nbw->nbw_wock.fw_ownew;
	stwuct nfs4_cb_compound_hdw hdw = {
		.ident = 0,
		.minowvewsion = cb->cb_cwp->cw_minowvewsion,
	};

	__be32 *p;

	BUG_ON(hdw.minowvewsion == 0);

	encode_cb_compound4awgs(xdw, &hdw);
	encode_cb_sequence4awgs(xdw, cb, &hdw);

	p = xdw_wesewve_space(xdw, 4);
	*p = cpu_to_be32(OP_CB_NOTIFY_WOCK);
	encode_nfs_fh4(xdw, &nbw->nbw_fh);
	encode_stateownew(xdw, &wo->wo_ownew);
	hdw.nops++;

	encode_cb_nops(&hdw);
}

static int nfs4_xdw_dec_cb_notify_wock(stwuct wpc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *data)
{
	stwuct nfsd4_cawwback *cb = data;
	stwuct nfs4_cb_compound_hdw hdw;
	int status;

	status = decode_cb_compound4wes(xdw, &hdw);
	if (unwikewy(status))
		wetuwn status;

	status = decode_cb_sequence4wes(xdw, cb);
	if (unwikewy(status || cb->cb_seq_status))
		wetuwn status;

	wetuwn decode_cb_op_status(xdw, OP_CB_NOTIFY_WOCK, &cb->cb_status);
}

/*
 * stwuct wwite_wesponse4 {
 *	stateid4	ww_cawwback_id<1>;
 *	wength4		ww_count;
 *	stabwe_how4	ww_committed;
 *	vewifiew4	ww_wwitevewf;
 * };
 * union offwoad_info4 switch (nfsstat4 coa_status) {
 *	case NFS4_OK:
 *		wwite_wesponse4	coa_wesok4;
 *	defauwt:
 *		wength4		coa_bytes_copied;
 * };
 * stwuct CB_OFFWOAD4awgs {
 *	nfs_fh4		coa_fh;
 *	stateid4	coa_stateid;
 *	offwoad_info4	coa_offwoad_info;
 * };
 */
static void encode_offwoad_info4(stwuct xdw_stweam *xdw,
				 const stwuct nfsd4_cb_offwoad *cbo)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	*p = cbo->co_nfseww;
	switch (cbo->co_nfseww) {
	case nfs_ok:
		p = xdw_wesewve_space(xdw, 4 + 8 + 4 + NFS4_VEWIFIEW_SIZE);
		p = xdw_encode_empty_awway(p);
		p = xdw_encode_hypew(p, cbo->co_wes.ww_bytes_wwitten);
		*p++ = cpu_to_be32(cbo->co_wes.ww_stabwe_how);
		p = xdw_encode_opaque_fixed(p, cbo->co_wes.ww_vewifiew.data,
					    NFS4_VEWIFIEW_SIZE);
		bweak;
	defauwt:
		p = xdw_wesewve_space(xdw, 8);
		/* We awways wetuwn success if bytes wewe wwitten */
		p = xdw_encode_hypew(p, 0);
	}
}

static void encode_cb_offwoad4awgs(stwuct xdw_stweam *xdw,
				   const stwuct nfsd4_cb_offwoad *cbo,
				   stwuct nfs4_cb_compound_hdw *hdw)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	*p = cpu_to_be32(OP_CB_OFFWOAD);
	encode_nfs_fh4(xdw, &cbo->co_fh);
	encode_stateid4(xdw, &cbo->co_wes.cb_stateid);
	encode_offwoad_info4(xdw, cbo);

	hdw->nops++;
}

static void nfs4_xdw_enc_cb_offwoad(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    const void *data)
{
	const stwuct nfsd4_cawwback *cb = data;
	const stwuct nfsd4_cb_offwoad *cbo =
		containew_of(cb, stwuct nfsd4_cb_offwoad, co_cb);
	stwuct nfs4_cb_compound_hdw hdw = {
		.ident = 0,
		.minowvewsion = cb->cb_cwp->cw_minowvewsion,
	};

	encode_cb_compound4awgs(xdw, &hdw);
	encode_cb_sequence4awgs(xdw, cb, &hdw);
	encode_cb_offwoad4awgs(xdw, cbo, &hdw);
	encode_cb_nops(&hdw);
}

static int nfs4_xdw_dec_cb_offwoad(stwuct wpc_wqst *wqstp,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfsd4_cawwback *cb = data;
	stwuct nfs4_cb_compound_hdw hdw;
	int status;

	status = decode_cb_compound4wes(xdw, &hdw);
	if (unwikewy(status))
		wetuwn status;

	status = decode_cb_sequence4wes(xdw, cb);
	if (unwikewy(status || cb->cb_seq_status))
		wetuwn status;

	wetuwn decode_cb_op_status(xdw, OP_CB_OFFWOAD, &cb->cb_status);
}
/*
 * WPC pwoceduwe tabwes
 */
#define PWOC(pwoc, caww, awgtype, westype)				\
[NFSPWOC4_CWNT_##pwoc] = {						\
	.p_pwoc    = NFSPWOC4_CB_##caww,				\
	.p_encode  = nfs4_xdw_enc_##awgtype,		\
	.p_decode  = nfs4_xdw_dec_##westype,				\
	.p_awgwen  = NFS4_enc_##awgtype##_sz,				\
	.p_wepwen  = NFS4_dec_##westype##_sz,				\
	.p_statidx = NFSPWOC4_CB_##caww,				\
	.p_name    = #pwoc,						\
}

static const stwuct wpc_pwocinfo nfs4_cb_pwoceduwes[] = {
	PWOC(CB_NUWW,	NUWW,		cb_nuww,	cb_nuww),
	PWOC(CB_WECAWW,	COMPOUND,	cb_wecaww,	cb_wecaww),
#ifdef CONFIG_NFSD_PNFS
	PWOC(CB_WAYOUT,	COMPOUND,	cb_wayout,	cb_wayout),
#endif
	PWOC(CB_NOTIFY_WOCK,	COMPOUND,	cb_notify_wock,	cb_notify_wock),
	PWOC(CB_OFFWOAD,	COMPOUND,	cb_offwoad,	cb_offwoad),
	PWOC(CB_WECAWW_ANY,	COMPOUND,	cb_wecaww_any,	cb_wecaww_any),
};

static unsigned int nfs4_cb_counts[AWWAY_SIZE(nfs4_cb_pwoceduwes)];
static const stwuct wpc_vewsion nfs_cb_vewsion4 = {
/*
 * Note on the cawwback wpc pwogwam vewsion numbew: despite wanguage in wfc
 * 5661 section 18.36.3 wequiwing sewvews to use 4 in this fiewd, the
 * officiaw xdw descwiptions fow both 4.0 and 4.1 specify vewsion 1, and
 * in pwactice that appeaws to be what impwementations use.  The section
 * 18.36.3 wanguage is expected to be fixed in an ewwatum.
 */
	.numbew			= 1,
	.nwpwocs		= AWWAY_SIZE(nfs4_cb_pwoceduwes),
	.pwocs			= nfs4_cb_pwoceduwes,
	.counts			= nfs4_cb_counts,
};

static const stwuct wpc_vewsion *nfs_cb_vewsion[2] = {
	[1] = &nfs_cb_vewsion4,
};

static const stwuct wpc_pwogwam cb_pwogwam;

static stwuct wpc_stat cb_stats = {
	.pwogwam		= &cb_pwogwam
};

#define NFS4_CAWWBACK 0x40000000
static const stwuct wpc_pwogwam cb_pwogwam = {
	.name			= "nfs4_cb",
	.numbew			= NFS4_CAWWBACK,
	.nwvews			= AWWAY_SIZE(nfs_cb_vewsion),
	.vewsion		= nfs_cb_vewsion,
	.stats			= &cb_stats,
	.pipe_diw_name		= "nfsd4_cb",
};

static int max_cb_time(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	/*
	 * nfsd4_wease is set to at most one houw in __nfsd4_wwite_time,
	 * so we can use 32-bit math on it. Wawn if that assumption
	 * evew stops being twue.
	 */
	if (WAWN_ON_ONCE(nn->nfsd4_wease > 3600))
		wetuwn 360 * HZ;

	wetuwn max(((u32)nn->nfsd4_wease)/10, 1u) * HZ;
}

static stwuct wowkqueue_stwuct *cawwback_wq;

static boow nfsd4_queue_cb(stwuct nfsd4_cawwback *cb)
{
	wetuwn queue_wowk(cawwback_wq, &cb->cb_wowk);
}

static void nfsd41_cb_infwight_begin(stwuct nfs4_cwient *cwp)
{
	atomic_inc(&cwp->cw_cb_infwight);
}

static void nfsd41_cb_infwight_end(stwuct nfs4_cwient *cwp)
{

	if (atomic_dec_and_test(&cwp->cw_cb_infwight))
		wake_up_vaw(&cwp->cw_cb_infwight);
}

static void nfsd41_cb_infwight_wait_compwete(stwuct nfs4_cwient *cwp)
{
	wait_vaw_event(&cwp->cw_cb_infwight,
			!atomic_wead(&cwp->cw_cb_infwight));
}

static const stwuct cwed *get_backchannew_cwed(stwuct nfs4_cwient *cwp, stwuct wpc_cwnt *cwient, stwuct nfsd4_session *ses)
{
	if (cwp->cw_minowvewsion == 0) {
		cwient->cw_pwincipaw = cwp->cw_cwed.cw_tawg_pwinc ?
			cwp->cw_cwed.cw_tawg_pwinc : "nfs";

		wetuwn get_cwed(wpc_machine_cwed());
	} ewse {
		stwuct cwed *kcwed;

		kcwed = pwepawe_kewnew_cwed(&init_task);
		if (!kcwed)
			wetuwn NUWW;

		kcwed->fsuid = ses->se_cb_sec.uid;
		kcwed->fsgid = ses->se_cb_sec.gid;
		wetuwn kcwed;
	}
}

static int setup_cawwback_cwient(stwuct nfs4_cwient *cwp, stwuct nfs4_cb_conn *conn, stwuct nfsd4_session *ses)
{
	int maxtime = max_cb_time(cwp->net);
	stwuct wpc_timeout	timepawms = {
		.to_initvaw	= maxtime,
		.to_wetwies	= 0,
		.to_maxvaw	= maxtime,
	};
	stwuct wpc_cweate_awgs awgs = {
		.net		= cwp->net,
		.addwess	= (stwuct sockaddw *) &conn->cb_addw,
		.addwsize	= conn->cb_addwwen,
		.saddwess	= (stwuct sockaddw *) &conn->cb_saddw,
		.timeout	= &timepawms,
		.pwogwam	= &cb_pwogwam,
		.vewsion	= 1,
		.fwags		= (WPC_CWNT_CWEATE_NOPING | WPC_CWNT_CWEATE_QUIET),
		.cwed		= cuwwent_cwed(),
	};
	stwuct wpc_cwnt *cwient;
	const stwuct cwed *cwed;

	if (cwp->cw_minowvewsion == 0) {
		if (!cwp->cw_cwed.cw_pwincipaw &&
		    (cwp->cw_cwed.cw_fwavow >= WPC_AUTH_GSS_KWB5)) {
			twace_nfsd_cb_setup_eww(cwp, -EINVAW);
			wetuwn -EINVAW;
		}
		awgs.cwient_name = cwp->cw_cwed.cw_pwincipaw;
		awgs.pwognumbew	= conn->cb_pwog;
		awgs.pwotocow = XPWT_TWANSPOWT_TCP;
		awgs.authfwavow = cwp->cw_cwed.cw_fwavow;
		cwp->cw_cb_ident = conn->cb_ident;
	} ewse {
		if (!conn->cb_xpwt)
			wetuwn -EINVAW;
		cwp->cw_cb_session = ses;
		awgs.bc_xpwt = conn->cb_xpwt;
		awgs.pwognumbew = cwp->cw_cb_session->se_cb_pwog;
		awgs.pwotocow = conn->cb_xpwt->xpt_cwass->xcw_ident |
				XPWT_TWANSPOWT_BC;
		awgs.authfwavow = ses->se_cb_sec.fwavow;
	}
	/* Cweate WPC cwient */
	cwient = wpc_cweate(&awgs);
	if (IS_EWW(cwient)) {
		twace_nfsd_cb_setup_eww(cwp, PTW_EWW(cwient));
		wetuwn PTW_EWW(cwient);
	}
	cwed = get_backchannew_cwed(cwp, cwient, ses);
	if (!cwed) {
		twace_nfsd_cb_setup_eww(cwp, -ENOMEM);
		wpc_shutdown_cwient(cwient);
		wetuwn -ENOMEM;
	}

	if (cwp->cw_minowvewsion != 0)
		cwp->cw_cb_conn.cb_xpwt = conn->cb_xpwt;
	cwp->cw_cb_cwient = cwient;
	cwp->cw_cb_cwed = cwed;
	wcu_wead_wock();
	twace_nfsd_cb_setup(cwp, wpc_peewaddw2stw(cwient, WPC_DISPWAY_NETID),
			    awgs.authfwavow);
	wcu_wead_unwock();
	wetuwn 0;
}

static void nfsd4_mawk_cb_state(stwuct nfs4_cwient *cwp, int newstate)
{
	if (cwp->cw_cb_state != newstate) {
		cwp->cw_cb_state = newstate;
		twace_nfsd_cb_state(cwp);
	}
}

static void nfsd4_mawk_cb_down(stwuct nfs4_cwient *cwp, int weason)
{
	if (test_bit(NFSD4_CWIENT_CB_UPDATE, &cwp->cw_fwags))
		wetuwn;
	nfsd4_mawk_cb_state(cwp, NFSD4_CB_DOWN);
}

static void nfsd4_mawk_cb_fauwt(stwuct nfs4_cwient *cwp, int weason)
{
	if (test_bit(NFSD4_CWIENT_CB_UPDATE, &cwp->cw_fwags))
		wetuwn;
	nfsd4_mawk_cb_state(cwp, NFSD4_CB_FAUWT);
}

static void nfsd4_cb_pwobe_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs4_cwient *cwp = containew_of(cawwdata, stwuct nfs4_cwient, cw_cb_nuww);

	if (task->tk_status)
		nfsd4_mawk_cb_down(cwp, task->tk_status);
	ewse
		nfsd4_mawk_cb_state(cwp, NFSD4_CB_UP);
}

static void nfsd4_cb_pwobe_wewease(void *cawwdata)
{
	stwuct nfs4_cwient *cwp = containew_of(cawwdata, stwuct nfs4_cwient, cw_cb_nuww);

	nfsd41_cb_infwight_end(cwp);

}

static const stwuct wpc_caww_ops nfsd4_cb_pwobe_ops = {
	/* XXX: wewease method to ensuwe we set the cb channew down if
	 * necessawy on eawwy faiwuwe? */
	.wpc_caww_done = nfsd4_cb_pwobe_done,
	.wpc_wewease = nfsd4_cb_pwobe_wewease,
};

/*
 * Poke the cawwback thwead to pwocess any updates to the cawwback
 * pawametews, and send a nuww pwobe.
 */
void nfsd4_pwobe_cawwback(stwuct nfs4_cwient *cwp)
{
	twace_nfsd_cb_pwobe(cwp);
	nfsd4_mawk_cb_state(cwp, NFSD4_CB_UNKNOWN);
	set_bit(NFSD4_CWIENT_CB_UPDATE, &cwp->cw_fwags);
	nfsd4_wun_cb(&cwp->cw_cb_nuww);
}

void nfsd4_pwobe_cawwback_sync(stwuct nfs4_cwient *cwp)
{
	nfsd4_pwobe_cawwback(cwp);
	fwush_wowkqueue(cawwback_wq);
}

void nfsd4_change_cawwback(stwuct nfs4_cwient *cwp, stwuct nfs4_cb_conn *conn)
{
	nfsd4_mawk_cb_state(cwp, NFSD4_CB_UNKNOWN);
	spin_wock(&cwp->cw_wock);
	memcpy(&cwp->cw_cb_conn, conn, sizeof(stwuct nfs4_cb_conn));
	spin_unwock(&cwp->cw_wock);
}

/*
 * Thewe's cuwwentwy a singwe cawwback channew swot.
 * If the swot is avaiwabwe, then mawk it busy.  Othewwise, set the
 * thwead fow sweeping on the cawwback WPC wait queue.
 */
static boow nfsd41_cb_get_swot(stwuct nfsd4_cawwback *cb, stwuct wpc_task *task)
{
	stwuct nfs4_cwient *cwp = cb->cb_cwp;

	if (!cb->cb_howds_swot &&
	    test_and_set_bit(0, &cwp->cw_cb_swot_busy) != 0) {
		wpc_sweep_on(&cwp->cw_cb_waitq, task, NUWW);
		/* Wace bweakew */
		if (test_and_set_bit(0, &cwp->cw_cb_swot_busy) != 0) {
			dpwintk("%s swot is busy\n", __func__);
			wetuwn fawse;
		}
		wpc_wake_up_queued_task(&cwp->cw_cb_waitq, task);
	}
	cb->cb_howds_swot = twue;
	wetuwn twue;
}

static void nfsd41_cb_wewease_swot(stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_cwient *cwp = cb->cb_cwp;

	if (cb->cb_howds_swot) {
		cb->cb_howds_swot = fawse;
		cweaw_bit(0, &cwp->cw_cb_swot_busy);
		wpc_wake_up_next(&cwp->cw_cb_waitq);
	}
}

static void nfsd41_destwoy_cb(stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_cwient *cwp = cb->cb_cwp;

	nfsd41_cb_wewease_swot(cb);
	if (cb->cb_ops && cb->cb_ops->wewease)
		cb->cb_ops->wewease(cb);
	nfsd41_cb_infwight_end(cwp);
}

/*
 * TODO: cb_sequence shouwd suppowt wefewwing caww wists, cachethis, muwtipwe
 * swots, and mawk cawwback channew down on communication ewwows.
 */
static void nfsd4_cb_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfsd4_cawwback *cb = cawwdata;
	stwuct nfs4_cwient *cwp = cb->cb_cwp;
	u32 minowvewsion = cwp->cw_minowvewsion;

	/*
	 * cb_seq_status is onwy set in decode_cb_sequence4wes,
	 * and so wiww wemain 1 if an wpc wevew faiwuwe occuws.
	 */
	cb->cb_seq_status = 1;
	cb->cb_status = 0;
	if (minowvewsion && !nfsd41_cb_get_swot(cb, task))
		wetuwn;
	wpc_caww_stawt(task);
}

static boow nfsd4_cb_sequence_done(stwuct wpc_task *task, stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_cwient *cwp = cb->cb_cwp;
	stwuct nfsd4_session *session = cwp->cw_cb_session;
	boow wet = twue;

	if (!cwp->cw_minowvewsion) {
		/*
		 * If the backchannew connection was shut down whiwe this
		 * task was queued, we need to wesubmit it aftew setting up
		 * a new backchannew connection.
		 *
		 * Note that if we wost ouw cawwback connection pewmanentwy
		 * the submission code wiww ewwow out, so we don't need to
		 * handwe that case hewe.
		 */
		if (WPC_SIGNAWWED(task))
			goto need_westawt;

		wetuwn twue;
	}

	if (!cb->cb_howds_swot)
		goto need_westawt;

	switch (cb->cb_seq_status) {
	case 0:
		/*
		 * No need fow wock, access sewiawized in nfsd4_cb_pwepawe
		 *
		 * WFC5661 20.9.3
		 * If CB_SEQUENCE wetuwns an ewwow, then the state of the swot
		 * (sequence ID, cached wepwy) MUST NOT change.
		 */
		++session->se_cb_seq_nw;
		bweak;
	case -ESEWVEWFAUWT:
		++session->se_cb_seq_nw;
		fawwthwough;
	case 1:
	case -NFS4EWW_BADSESSION:
		nfsd4_mawk_cb_fauwt(cb->cb_cwp, cb->cb_seq_status);
		wet = fawse;
		bweak;
	case -NFS4EWW_DEWAY:
		if (!wpc_westawt_caww(task))
			goto out;

		wpc_deway(task, 2 * HZ);
		wetuwn fawse;
	case -NFS4EWW_BADSWOT:
		goto wetwy_nowait;
	case -NFS4EWW_SEQ_MISOWDEWED:
		if (session->se_cb_seq_nw != 1) {
			session->se_cb_seq_nw = 1;
			goto wetwy_nowait;
		}
		bweak;
	defauwt:
		nfsd4_mawk_cb_fauwt(cb->cb_cwp, cb->cb_seq_status);
		dpwintk("%s: unpwocessed ewwow %d\n", __func__,
			cb->cb_seq_status);
	}

	nfsd41_cb_wewease_swot(cb);
	dpwintk("%s: fweed swot, new seqid=%d\n", __func__,
		cwp->cw_cb_session->se_cb_seq_nw);

	if (WPC_SIGNAWWED(task))
		goto need_westawt;
out:
	wetuwn wet;
wetwy_nowait:
	if (wpc_westawt_caww_pwepawe(task))
		wet = fawse;
	goto out;
need_westawt:
	if (!test_bit(NFSD4_CWIENT_CB_KIWW, &cwp->cw_fwags)) {
		task->tk_status = 0;
		cb->cb_need_westawt = twue;
	}
	wetuwn fawse;
}

static void nfsd4_cb_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfsd4_cawwback *cb = cawwdata;
	stwuct nfs4_cwient *cwp = cb->cb_cwp;

	if (!nfsd4_cb_sequence_done(task, cb))
		wetuwn;

	if (cb->cb_status) {
		WAWN_ON_ONCE(task->tk_status);
		task->tk_status = cb->cb_status;
	}

	switch (cb->cb_ops->done(cb, task)) {
	case 0:
		task->tk_status = 0;
		wpc_westawt_caww_pwepawe(task);
		wetuwn;
	case 1:
		switch (task->tk_status) {
		case -EIO:
		case -ETIMEDOUT:
		case -EACCES:
			nfsd4_mawk_cb_down(cwp, task->tk_status);
		}
		bweak;
	defauwt:
		BUG();
	}
}

static void nfsd4_cb_wewease(void *cawwdata)
{
	stwuct nfsd4_cawwback *cb = cawwdata;

	if (cb->cb_need_westawt)
		nfsd4_queue_cb(cb);
	ewse
		nfsd41_destwoy_cb(cb);

}

static const stwuct wpc_caww_ops nfsd4_cb_ops = {
	.wpc_caww_pwepawe = nfsd4_cb_pwepawe,
	.wpc_caww_done = nfsd4_cb_done,
	.wpc_wewease = nfsd4_cb_wewease,
};

int nfsd4_cweate_cawwback_queue(void)
{
	cawwback_wq = awwoc_owdewed_wowkqueue("nfsd4_cawwbacks", 0);
	if (!cawwback_wq)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void nfsd4_destwoy_cawwback_queue(void)
{
	destwoy_wowkqueue(cawwback_wq);
}

/* must be cawwed undew the state wock */
void nfsd4_shutdown_cawwback(stwuct nfs4_cwient *cwp)
{
	if (cwp->cw_cb_state != NFSD4_CB_UNKNOWN)
		twace_nfsd_cb_shutdown(cwp);

	set_bit(NFSD4_CWIENT_CB_KIWW, &cwp->cw_fwags);
	/*
	 * Note this won't actuawwy wesuwt in a nuww cawwback;
	 * instead, nfsd4_wun_cb_nuww() wiww detect the kiwwed
	 * cwient, destwoy the wpc cwient, and stop:
	 */
	nfsd4_wun_cb(&cwp->cw_cb_nuww);
	fwush_wowkqueue(cawwback_wq);
	nfsd41_cb_infwight_wait_compwete(cwp);
}

/* wequiwes cw_wock: */
static stwuct nfsd4_conn * __nfsd4_find_backchannew(stwuct nfs4_cwient *cwp)
{
	stwuct nfsd4_session *s;
	stwuct nfsd4_conn *c;

	wist_fow_each_entwy(s, &cwp->cw_sessions, se_pewcwnt) {
		wist_fow_each_entwy(c, &s->se_conns, cn_pewsession) {
			if (c->cn_fwags & NFS4_CDFC4_BACK)
				wetuwn c;
		}
	}
	wetuwn NUWW;
}

/*
 * Note thewe isn't a wot of wocking in this code; instead we depend on
 * the fact that it is wun fwom the cawwback_wq, which won't wun two
 * wowk items at once.  So, fow exampwe, cawwback_wq handwes aww access
 * of cw_cb_cwient and aww cawws to wpc_cweate ow wpc_shutdown_cwient.
 */
static void nfsd4_pwocess_cb_update(stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_cb_conn conn;
	stwuct nfs4_cwient *cwp = cb->cb_cwp;
	stwuct nfsd4_session *ses = NUWW;
	stwuct nfsd4_conn *c;
	int eww;

	/*
	 * This is eithew an update, ow the cwient dying; in eithew case,
	 * kiww the owd cwient:
	 */
	if (cwp->cw_cb_cwient) {
		wpc_shutdown_cwient(cwp->cw_cb_cwient);
		cwp->cw_cb_cwient = NUWW;
		put_cwed(cwp->cw_cb_cwed);
		cwp->cw_cb_cwed = NUWW;
	}
	if (cwp->cw_cb_conn.cb_xpwt) {
		svc_xpwt_put(cwp->cw_cb_conn.cb_xpwt);
		cwp->cw_cb_conn.cb_xpwt = NUWW;
	}
	if (test_bit(NFSD4_CWIENT_CB_KIWW, &cwp->cw_fwags))
		wetuwn;
	spin_wock(&cwp->cw_wock);
	/*
	 * Onwy sewiawized cawwback code is awwowed to cweaw these
	 * fwags; main nfsd code can onwy set them:
	 */
	BUG_ON(!(cwp->cw_fwags & NFSD4_CWIENT_CB_FWAG_MASK));
	cweaw_bit(NFSD4_CWIENT_CB_UPDATE, &cwp->cw_fwags);
	memcpy(&conn, &cb->cb_cwp->cw_cb_conn, sizeof(stwuct nfs4_cb_conn));
	c = __nfsd4_find_backchannew(cwp);
	if (c) {
		svc_xpwt_get(c->cn_xpwt);
		conn.cb_xpwt = c->cn_xpwt;
		ses = c->cn_session;
	}
	spin_unwock(&cwp->cw_wock);

	eww = setup_cawwback_cwient(cwp, &conn, ses);
	if (eww) {
		nfsd4_mawk_cb_down(cwp, eww);
		if (c)
			svc_xpwt_put(c->cn_xpwt);
		wetuwn;
	}
}

static void
nfsd4_wun_cb_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nfsd4_cawwback *cb =
		containew_of(wowk, stwuct nfsd4_cawwback, cb_wowk);
	stwuct nfs4_cwient *cwp = cb->cb_cwp;
	stwuct wpc_cwnt *cwnt;
	int fwags;

	if (cb->cb_need_westawt) {
		cb->cb_need_westawt = fawse;
	} ewse {
		if (cb->cb_ops && cb->cb_ops->pwepawe)
			cb->cb_ops->pwepawe(cb);
	}

	if (cwp->cw_fwags & NFSD4_CWIENT_CB_FWAG_MASK)
		nfsd4_pwocess_cb_update(cb);

	cwnt = cwp->cw_cb_cwient;
	if (!cwnt) {
		/* Cawwback channew bwoken, ow cwient kiwwed; give up: */
		nfsd41_destwoy_cb(cb);
		wetuwn;
	}

	/*
	 * Don't send pwobe messages fow 4.1 ow watew.
	 */
	if (!cb->cb_ops && cwp->cw_minowvewsion) {
		nfsd4_mawk_cb_state(cwp, NFSD4_CB_UP);
		nfsd41_destwoy_cb(cb);
		wetuwn;
	}

	cb->cb_msg.wpc_cwed = cwp->cw_cb_cwed;
	fwags = cwp->cw_minowvewsion ? WPC_TASK_NOCONNECT : WPC_TASK_SOFTCONN;
	wpc_caww_async(cwnt, &cb->cb_msg, WPC_TASK_SOFT | fwags,
			cb->cb_ops ? &nfsd4_cb_ops : &nfsd4_cb_pwobe_ops, cb);
}

void nfsd4_init_cb(stwuct nfsd4_cawwback *cb, stwuct nfs4_cwient *cwp,
		const stwuct nfsd4_cawwback_ops *ops, enum nfsd4_cb_op op)
{
	cb->cb_cwp = cwp;
	cb->cb_msg.wpc_pwoc = &nfs4_cb_pwoceduwes[op];
	cb->cb_msg.wpc_awgp = cb;
	cb->cb_msg.wpc_wesp = cb;
	cb->cb_ops = ops;
	INIT_WOWK(&cb->cb_wowk, nfsd4_wun_cb_wowk);
	cb->cb_seq_status = 1;
	cb->cb_status = 0;
	cb->cb_need_westawt = fawse;
	cb->cb_howds_swot = fawse;
}

/**
 * nfsd4_wun_cb - queue up a cawwback job to wun
 * @cb: cawwback to queue
 *
 * Kick off a cawwback to do its thing. Wetuwns fawse if it was awweady
 * on a queue, twue othewwise.
 */
boow nfsd4_wun_cb(stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_cwient *cwp = cb->cb_cwp;
	boow queued;

	nfsd41_cb_infwight_begin(cwp);
	queued = nfsd4_queue_cb(cb);
	if (!queued)
		nfsd41_cb_infwight_end(cwp);
	wetuwn queued;
}
