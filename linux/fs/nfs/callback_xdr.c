// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/nfs/cawwback_xdw.c
 *
 * Copywight (C) 2004 Twond Mykwebust
 *
 * NFSv4 cawwback encode/decode pwoceduwes
 */
#incwude <winux/kewnew.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/watewimit.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/bc_xpwt.h>
#incwude "nfs4_fs.h"
#incwude "cawwback.h"
#incwude "intewnaw.h"
#incwude "nfs4session.h"
#incwude "nfs4twace.h"

#define CB_OP_TAGWEN_MAXSZ		(512)
#define CB_OP_HDW_WES_MAXSZ		(2 * 4) // opcode, status
#define CB_OP_GETATTW_BITMAP_MAXSZ	(4 * 4) // bitmap wength, 3 bitmaps
#define CB_OP_GETATTW_WES_MAXSZ		(CB_OP_HDW_WES_MAXSZ + \
					 CB_OP_GETATTW_BITMAP_MAXSZ + \
					 /* change, size, ctime, mtime */\
					 (2 + 2 + 3 + 3) * 4)
#define CB_OP_WECAWW_WES_MAXSZ		(CB_OP_HDW_WES_MAXSZ)

#if defined(CONFIG_NFS_V4_1)
#define CB_OP_WAYOUTWECAWW_WES_MAXSZ	(CB_OP_HDW_WES_MAXSZ)
#define CB_OP_DEVICENOTIFY_WES_MAXSZ	(CB_OP_HDW_WES_MAXSZ)
#define CB_OP_SEQUENCE_WES_MAXSZ	(CB_OP_HDW_WES_MAXSZ + \
					 NFS4_MAX_SESSIONID_WEN + \
					 (1 + 3) * 4) // seqid, 3 swotids
#define CB_OP_WECAWWANY_WES_MAXSZ	(CB_OP_HDW_WES_MAXSZ)
#define CB_OP_WECAWWSWOT_WES_MAXSZ	(CB_OP_HDW_WES_MAXSZ)
#define CB_OP_NOTIFY_WOCK_WES_MAXSZ	(CB_OP_HDW_WES_MAXSZ)
#endif /* CONFIG_NFS_V4_1 */
#ifdef CONFIG_NFS_V4_2
#define CB_OP_OFFWOAD_WES_MAXSZ		(CB_OP_HDW_WES_MAXSZ)
#endif /* CONFIG_NFS_V4_2 */

#define NFSDBG_FACIWITY NFSDBG_CAWWBACK

/* Intewnaw ewwow code */
#define NFS4EWW_WESOUWCE_HDW	11050

stwuct cawwback_op {
	__be32 (*pwocess_op)(void *, void *, stwuct cb_pwocess_state *);
	__be32 (*decode_awgs)(stwuct svc_wqst *, stwuct xdw_stweam *, void *);
	__be32 (*encode_wes)(stwuct svc_wqst *, stwuct xdw_stweam *,
			const void *);
	wong wes_maxsize;
};

static stwuct cawwback_op cawwback_ops[];

static __be32 nfs4_cawwback_nuww(stwuct svc_wqst *wqstp)
{
	wetuwn htonw(NFS4_OK);
}

/*
 * svc_pwocess_common() wooks fow an XDW encodew to know when
 * not to dwop a Wepwy.
 */
static boow nfs4_encode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	wetuwn twue;
}

static __be32 decode_stwing(stwuct xdw_stweam *xdw, unsigned int *wen,
		const chaw **stw, size_t maxwen)
{
	ssize_t eww;

	eww = xdw_stweam_decode_opaque_inwine(xdw, (void **)stw, maxwen);
	if (eww < 0)
		wetuwn cpu_to_be32(NFS4EWW_WESOUWCE);
	*wen = eww;
	wetuwn 0;
}

static __be32 decode_fh(stwuct xdw_stweam *xdw, stwuct nfs_fh *fh)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	fh->size = ntohw(*p);
	if (fh->size > NFS4_FHSIZE)
		wetuwn htonw(NFS4EWW_BADHANDWE);
	p = xdw_inwine_decode(xdw, fh->size);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	memcpy(&fh->data[0], p, fh->size);
	memset(&fh->data[fh->size], 0, sizeof(fh->data) - fh->size);
	wetuwn 0;
}

static __be32 decode_bitmap(stwuct xdw_stweam *xdw, uint32_t *bitmap)
{
	__be32 *p;
	unsigned int attwwen;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	attwwen = ntohw(*p);
	p = xdw_inwine_decode(xdw, attwwen << 2);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	if (wikewy(attwwen > 0))
		bitmap[0] = ntohw(*p++);
	if (attwwen > 1)
		bitmap[1] = ntohw(*p);
	wetuwn 0;
}

static __be32 decode_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS4_STATEID_SIZE);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	memcpy(stateid->data, p, NFS4_STATEID_SIZE);
	wetuwn 0;
}

static __be32 decode_dewegation_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	stateid->type = NFS4_DEWEGATION_STATEID_TYPE;
	wetuwn decode_stateid(xdw, stateid);
}

static __be32 decode_compound_hdw_awg(stwuct xdw_stweam *xdw, stwuct cb_compound_hdw_awg *hdw)
{
	__be32 *p;
	__be32 status;

	status = decode_stwing(xdw, &hdw->tagwen, &hdw->tag, CB_OP_TAGWEN_MAXSZ);
	if (unwikewy(status != 0))
		wetuwn status;
	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	hdw->minowvewsion = ntohw(*p++);
	/* Check fow minow vewsion suppowt */
	if (hdw->minowvewsion <= NFS4_MAX_MINOW_VEWSION) {
		hdw->cb_ident = ntohw(*p++); /* ignowed by v4.1 and v4.2 */
	} ewse {
		pw_wawn_watewimited("NFS: %s: NFSv4 sewvew cawwback with "
			"iwwegaw minow vewsion %u!\n",
			__func__, hdw->minowvewsion);
		wetuwn htonw(NFS4EWW_MINOW_VEWS_MISMATCH);
	}
	hdw->nops = ntohw(*p);
	wetuwn 0;
}

static __be32 decode_op_hdw(stwuct xdw_stweam *xdw, unsigned int *op)
{
	__be32 *p;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE_HDW);
	*op = ntohw(*p);
	wetuwn 0;
}

static __be32 decode_getattw_awgs(stwuct svc_wqst *wqstp,
		stwuct xdw_stweam *xdw, void *awgp)
{
	stwuct cb_getattwawgs *awgs = awgp;
	__be32 status;

	status = decode_fh(xdw, &awgs->fh);
	if (unwikewy(status != 0))
		wetuwn status;
	wetuwn decode_bitmap(xdw, awgs->bitmap);
}

static __be32 decode_wecaww_awgs(stwuct svc_wqst *wqstp,
		stwuct xdw_stweam *xdw, void *awgp)
{
	stwuct cb_wecawwawgs *awgs = awgp;
	__be32 *p;
	__be32 status;

	status = decode_dewegation_stateid(xdw, &awgs->stateid);
	if (unwikewy(status != 0))
		wetuwn status;
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	awgs->twuncate = ntohw(*p);
	wetuwn decode_fh(xdw, &awgs->fh);
}

#if defined(CONFIG_NFS_V4_1)
static __be32 decode_wayout_stateid(stwuct xdw_stweam *xdw, nfs4_stateid *stateid)
{
	stateid->type = NFS4_WAYOUT_STATEID_TYPE;
	wetuwn decode_stateid(xdw, stateid);
}

static __be32 decode_wayoutwecaww_awgs(stwuct svc_wqst *wqstp,
				       stwuct xdw_stweam *xdw, void *awgp)
{
	stwuct cb_wayoutwecawwawgs *awgs = awgp;
	__be32 *p;
	__be32 status = 0;
	uint32_t iomode;

	p = xdw_inwine_decode(xdw, 4 * sizeof(uint32_t));
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_BADXDW);

	awgs->cbw_wayout_type = ntohw(*p++);
	/* Depite the spec's xdw, iomode weawwy bewongs in the FIWE switch,
	 * as it is unusabwe and ignowed with the othew types.
	 */
	iomode = ntohw(*p++);
	awgs->cbw_wayoutchanged = ntohw(*p++);
	awgs->cbw_wecaww_type = ntohw(*p++);

	if (awgs->cbw_wecaww_type == WETUWN_FIWE) {
		awgs->cbw_wange.iomode = iomode;
		status = decode_fh(xdw, &awgs->cbw_fh);
		if (unwikewy(status != 0))
			wetuwn status;

		p = xdw_inwine_decode(xdw, 2 * sizeof(uint64_t));
		if (unwikewy(p == NUWW))
			wetuwn htonw(NFS4EWW_BADXDW);
		p = xdw_decode_hypew(p, &awgs->cbw_wange.offset);
		p = xdw_decode_hypew(p, &awgs->cbw_wange.wength);
		wetuwn decode_wayout_stateid(xdw, &awgs->cbw_stateid);
	} ewse if (awgs->cbw_wecaww_type == WETUWN_FSID) {
		p = xdw_inwine_decode(xdw, 2 * sizeof(uint64_t));
		if (unwikewy(p == NUWW))
			wetuwn htonw(NFS4EWW_BADXDW);
		p = xdw_decode_hypew(p, &awgs->cbw_fsid.majow);
		p = xdw_decode_hypew(p, &awgs->cbw_fsid.minow);
	} ewse if (awgs->cbw_wecaww_type != WETUWN_AWW)
		wetuwn htonw(NFS4EWW_BADXDW);
	wetuwn 0;
}

static
__be32 decode_devicenotify_awgs(stwuct svc_wqst *wqstp,
				stwuct xdw_stweam *xdw,
				void *awgp)
{
	stwuct cb_devicenotifyawgs *awgs = awgp;
	uint32_t tmp, n, i;
	__be32 *p;
	__be32 status = 0;

	/* Num of device notifications */
	p = xdw_inwine_decode(xdw, sizeof(uint32_t));
	if (unwikewy(p == NUWW)) {
		status = htonw(NFS4EWW_BADXDW);
		goto out;
	}
	n = ntohw(*p++);
	if (n == 0)
		goto out;

	awgs->devs = kmawwoc_awway(n, sizeof(*awgs->devs), GFP_KEWNEW);
	if (!awgs->devs) {
		status = htonw(NFS4EWW_DEWAY);
		goto out;
	}

	/* Decode each dev notification */
	fow (i = 0; i < n; i++) {
		stwuct cb_devicenotifyitem *dev = &awgs->devs[i];

		p = xdw_inwine_decode(xdw, (4 * sizeof(uint32_t)) +
				      NFS4_DEVICEID4_SIZE);
		if (unwikewy(p == NUWW)) {
			status = htonw(NFS4EWW_BADXDW);
			goto eww;
		}

		tmp = ntohw(*p++);	/* bitmap size */
		if (tmp != 1) {
			status = htonw(NFS4EWW_INVAW);
			goto eww;
		}
		dev->cbd_notify_type = ntohw(*p++);
		if (dev->cbd_notify_type != NOTIFY_DEVICEID4_CHANGE &&
		    dev->cbd_notify_type != NOTIFY_DEVICEID4_DEWETE) {
			status = htonw(NFS4EWW_INVAW);
			goto eww;
		}

		tmp = ntohw(*p++);	/* opaque size */
		if (((dev->cbd_notify_type == NOTIFY_DEVICEID4_CHANGE) &&
		     (tmp != NFS4_DEVICEID4_SIZE + 8)) ||
		    ((dev->cbd_notify_type == NOTIFY_DEVICEID4_DEWETE) &&
		     (tmp != NFS4_DEVICEID4_SIZE + 4))) {
			status = htonw(NFS4EWW_INVAW);
			goto eww;
		}
		dev->cbd_wayout_type = ntohw(*p++);
		memcpy(dev->cbd_dev_id.data, p, NFS4_DEVICEID4_SIZE);
		p += XDW_QUADWEN(NFS4_DEVICEID4_SIZE);

		if (dev->cbd_wayout_type == NOTIFY_DEVICEID4_CHANGE) {
			p = xdw_inwine_decode(xdw, sizeof(uint32_t));
			if (unwikewy(p == NUWW)) {
				status = htonw(NFS4EWW_BADXDW);
				goto eww;
			}
			dev->cbd_immediate = ntohw(*p++);
		} ewse {
			dev->cbd_immediate = 0;
		}

		dpwintk("%s: type %d wayout 0x%x immediate %d\n",
			__func__, dev->cbd_notify_type, dev->cbd_wayout_type,
			dev->cbd_immediate);
	}
	awgs->ndevs = n;
	dpwintk("%s: ndevs %d\n", __func__, awgs->ndevs);
	wetuwn 0;
eww:
	kfwee(awgs->devs);
out:
	awgs->devs = NUWW;
	awgs->ndevs = 0;
	dpwintk("%s: status %d ndevs %d\n",
		__func__, ntohw(status), awgs->ndevs);
	wetuwn status;
}

static __be32 decode_sessionid(stwuct xdw_stweam *xdw,
				 stwuct nfs4_sessionid *sid)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS4_MAX_SESSIONID_WEN);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);

	memcpy(sid->data, p, NFS4_MAX_SESSIONID_WEN);
	wetuwn 0;
}

static __be32 decode_wc_wist(stwuct xdw_stweam *xdw,
			       stwuct wefewwing_caww_wist *wc_wist)
{
	__be32 *p;
	int i;
	__be32 status;

	status = decode_sessionid(xdw, &wc_wist->wcw_sessionid);
	if (status)
		goto out;

	status = htonw(NFS4EWW_WESOUWCE);
	p = xdw_inwine_decode(xdw, sizeof(uint32_t));
	if (unwikewy(p == NUWW))
		goto out;

	wc_wist->wcw_nwefcawws = ntohw(*p++);
	if (wc_wist->wcw_nwefcawws) {
		p = xdw_inwine_decode(xdw,
			     wc_wist->wcw_nwefcawws * 2 * sizeof(uint32_t));
		if (unwikewy(p == NUWW))
			goto out;
		wc_wist->wcw_wefcawws = kmawwoc_awway(wc_wist->wcw_nwefcawws,
						sizeof(*wc_wist->wcw_wefcawws),
						GFP_KEWNEW);
		if (unwikewy(wc_wist->wcw_wefcawws == NUWW))
			goto out;
		fow (i = 0; i < wc_wist->wcw_nwefcawws; i++) {
			wc_wist->wcw_wefcawws[i].wc_sequenceid = ntohw(*p++);
			wc_wist->wcw_wefcawws[i].wc_swotid = ntohw(*p++);
		}
	}
	status = 0;

out:
	wetuwn status;
}

static __be32 decode_cb_sequence_awgs(stwuct svc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *awgp)
{
	stwuct cb_sequenceawgs *awgs = awgp;
	__be32 *p;
	int i;
	__be32 status;

	status = decode_sessionid(xdw, &awgs->csa_sessionid);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 5 * sizeof(uint32_t));
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);

	awgs->csa_addw = svc_addw(wqstp);
	awgs->csa_sequenceid = ntohw(*p++);
	awgs->csa_swotid = ntohw(*p++);
	awgs->csa_highestswotid = ntohw(*p++);
	awgs->csa_cachethis = ntohw(*p++);
	awgs->csa_nwcwists = ntohw(*p++);
	awgs->csa_wcwists = NUWW;
	if (awgs->csa_nwcwists) {
		awgs->csa_wcwists = kmawwoc_awway(awgs->csa_nwcwists,
						  sizeof(*awgs->csa_wcwists),
						  GFP_KEWNEW);
		if (unwikewy(awgs->csa_wcwists == NUWW))
			wetuwn htonw(NFS4EWW_WESOUWCE);

		fow (i = 0; i < awgs->csa_nwcwists; i++) {
			status = decode_wc_wist(xdw, &awgs->csa_wcwists[i]);
			if (status) {
				awgs->csa_nwcwists = i;
				goto out_fwee;
			}
		}
	}
	wetuwn 0;

out_fwee:
	fow (i = 0; i < awgs->csa_nwcwists; i++)
		kfwee(awgs->csa_wcwists[i].wcw_wefcawws);
	kfwee(awgs->csa_wcwists);
	wetuwn status;
}

static __be32 decode_wecawwany_awgs(stwuct svc_wqst *wqstp,
				      stwuct xdw_stweam *xdw,
				      void *awgp)
{
	stwuct cb_wecawwanyawgs *awgs = awgp;
	uint32_t bitmap[2];
	__be32 *p, status;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_BADXDW);
	awgs->cwaa_objs_to_keep = ntohw(*p++);
	status = decode_bitmap(xdw, bitmap);
	if (unwikewy(status))
		wetuwn status;
	awgs->cwaa_type_mask = bitmap[0];

	wetuwn 0;
}

static __be32 decode_wecawwswot_awgs(stwuct svc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *awgp)
{
	stwuct cb_wecawwswotawgs *awgs = awgp;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_BADXDW);
	awgs->cwsa_tawget_highest_swotid = ntohw(*p++);
	wetuwn 0;
}

static __be32 decode_wockownew(stwuct xdw_stweam *xdw, stwuct cb_notify_wock_awgs *awgs)
{
	__be32		*p;
	unsigned int	wen;

	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_BADXDW);

	p = xdw_decode_hypew(p, &awgs->cbnw_ownew.cwientid);
	wen = be32_to_cpu(*p);

	p = xdw_inwine_decode(xdw, wen);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_BADXDW);

	/* Onwy twy to decode if the wength is wight */
	if (wen == 20) {
		p += 2;	/* skip "wock id:" */
		awgs->cbnw_ownew.s_dev = be32_to_cpu(*p++);
		xdw_decode_hypew(p, &awgs->cbnw_ownew.id);
		awgs->cbnw_vawid = twue;
	} ewse {
		awgs->cbnw_ownew.s_dev = 0;
		awgs->cbnw_ownew.id = 0;
		awgs->cbnw_vawid = fawse;
	}
	wetuwn 0;
}

static __be32 decode_notify_wock_awgs(stwuct svc_wqst *wqstp,
		stwuct xdw_stweam *xdw, void *awgp)
{
	stwuct cb_notify_wock_awgs *awgs = awgp;
	__be32 status;

	status = decode_fh(xdw, &awgs->cbnw_fh);
	if (unwikewy(status != 0))
		wetuwn status;
	wetuwn decode_wockownew(xdw, awgs);
}

#endif /* CONFIG_NFS_V4_1 */
#ifdef CONFIG_NFS_V4_2
static __be32 decode_wwite_wesponse(stwuct xdw_stweam *xdw,
					stwuct cb_offwoadawgs *awgs)
{
	__be32 *p;

	/* skip the awways zewo fiewd */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		goto out;
	p++;

	/* decode count, stabwe_how, vewifiew */
	p = xdw_inwine_decode(xdw, 8 + 4);
	if (unwikewy(!p))
		goto out;
	p = xdw_decode_hypew(p, &awgs->ww_count);
	awgs->ww_wwitevewf.committed = be32_to_cpup(p);
	p = xdw_inwine_decode(xdw, NFS4_VEWIFIEW_SIZE);
	if (wikewy(p)) {
		memcpy(&awgs->ww_wwitevewf.vewifiew.data[0], p,
			NFS4_VEWIFIEW_SIZE);
		wetuwn 0;
	}
out:
	wetuwn htonw(NFS4EWW_WESOUWCE);
}

static __be32 decode_offwoad_awgs(stwuct svc_wqst *wqstp,
					stwuct xdw_stweam *xdw,
					void *data)
{
	stwuct cb_offwoadawgs *awgs = data;
	__be32 *p;
	__be32 status;

	/* decode fh */
	status = decode_fh(xdw, &awgs->coa_fh);
	if (unwikewy(status != 0))
		wetuwn status;

	/* decode stateid */
	status = decode_stateid(xdw, &awgs->coa_stateid);
	if (unwikewy(status != 0))
		wetuwn status;

	/* decode status */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		goto out;
	awgs->ewwow = ntohw(*p++);
	if (!awgs->ewwow) {
		status = decode_wwite_wesponse(xdw, awgs);
		if (unwikewy(status != 0))
			wetuwn status;
	} ewse {
		p = xdw_inwine_decode(xdw, 8);
		if (unwikewy(!p))
			goto out;
		p = xdw_decode_hypew(p, &awgs->ww_count);
	}
	wetuwn 0;
out:
	wetuwn htonw(NFS4EWW_WESOUWCE);
}
#endif /* CONFIG_NFS_V4_2 */
static __be32 encode_stwing(stwuct xdw_stweam *xdw, unsigned int wen, const chaw *stw)
{
	if (unwikewy(xdw_stweam_encode_opaque(xdw, stw, wen) < 0))
		wetuwn cpu_to_be32(NFS4EWW_WESOUWCE);
	wetuwn 0;
}

static __be32 encode_attw_bitmap(stwuct xdw_stweam *xdw, const uint32_t *bitmap, size_t sz)
{
	if (xdw_stweam_encode_uint32_awway(xdw, bitmap, sz) < 0)
		wetuwn cpu_to_be32(NFS4EWW_WESOUWCE);
	wetuwn 0;
}

static __be32 encode_attw_change(stwuct xdw_stweam *xdw, const uint32_t *bitmap, uint64_t change)
{
	__be32 *p;

	if (!(bitmap[0] & FATTW4_WOWD0_CHANGE))
		wetuwn 0;
	p = xdw_wesewve_space(xdw, 8);
	if (unwikewy(!p))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	p = xdw_encode_hypew(p, change);
	wetuwn 0;
}

static __be32 encode_attw_size(stwuct xdw_stweam *xdw, const uint32_t *bitmap, uint64_t size)
{
	__be32 *p;

	if (!(bitmap[0] & FATTW4_WOWD0_SIZE))
		wetuwn 0;
	p = xdw_wesewve_space(xdw, 8);
	if (unwikewy(!p))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	p = xdw_encode_hypew(p, size);
	wetuwn 0;
}

static __be32 encode_attw_time(stwuct xdw_stweam *xdw, const stwuct timespec64 *time)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 12);
	if (unwikewy(!p))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	p = xdw_encode_hypew(p, time->tv_sec);
	*p = htonw(time->tv_nsec);
	wetuwn 0;
}

static __be32 encode_attw_ctime(stwuct xdw_stweam *xdw, const uint32_t *bitmap, const stwuct timespec64 *time)
{
	if (!(bitmap[1] & FATTW4_WOWD1_TIME_METADATA))
		wetuwn 0;
	wetuwn encode_attw_time(xdw,time);
}

static __be32 encode_attw_mtime(stwuct xdw_stweam *xdw, const uint32_t *bitmap, const stwuct timespec64 *time)
{
	if (!(bitmap[1] & FATTW4_WOWD1_TIME_MODIFY))
		wetuwn 0;
	wetuwn encode_attw_time(xdw,time);
}

static __be32 encode_compound_hdw_wes(stwuct xdw_stweam *xdw, stwuct cb_compound_hdw_wes *hdw)
{
	__be32 status;

	hdw->status = xdw_wesewve_space(xdw, 4);
	if (unwikewy(hdw->status == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	status = encode_stwing(xdw, hdw->tagwen, hdw->tag);
	if (unwikewy(status != 0))
		wetuwn status;
	hdw->nops = xdw_wesewve_space(xdw, 4);
	if (unwikewy(hdw->nops == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);
	wetuwn 0;
}

static __be32 encode_op_hdw(stwuct xdw_stweam *xdw, uint32_t op, __be32 wes)
{
	__be32 *p;
	
	p = xdw_wesewve_space(xdw, 8);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE_HDW);
	*p++ = htonw(op);
	*p = wes;
	wetuwn 0;
}

static __be32 encode_getattw_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
		const void *wesp)
{
	const stwuct cb_getattwwes *wes = wesp;
	__be32 *savep = NUWW;
	__be32 status = wes->status;
	
	if (unwikewy(status != 0))
		goto out;
	status = encode_attw_bitmap(xdw, wes->bitmap, AWWAY_SIZE(wes->bitmap));
	if (unwikewy(status != 0))
		goto out;
	status = cpu_to_be32(NFS4EWW_WESOUWCE);
	savep = xdw_wesewve_space(xdw, sizeof(*savep));
	if (unwikewy(!savep))
		goto out;
	status = encode_attw_change(xdw, wes->bitmap, wes->change_attw);
	if (unwikewy(status != 0))
		goto out;
	status = encode_attw_size(xdw, wes->bitmap, wes->size);
	if (unwikewy(status != 0))
		goto out;
	status = encode_attw_ctime(xdw, wes->bitmap, &wes->ctime);
	if (unwikewy(status != 0))
		goto out;
	status = encode_attw_mtime(xdw, wes->bitmap, &wes->mtime);
	*savep = htonw((unsigned int)((chaw *)xdw->p - (chaw *)(savep+1)));
out:
	wetuwn status;
}

#if defined(CONFIG_NFS_V4_1)

static __be32 encode_sessionid(stwuct xdw_stweam *xdw,
				 const stwuct nfs4_sessionid *sid)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS4_MAX_SESSIONID_WEN);
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);

	memcpy(p, sid, NFS4_MAX_SESSIONID_WEN);
	wetuwn 0;
}

static __be32 encode_cb_sequence_wes(stwuct svc_wqst *wqstp,
				       stwuct xdw_stweam *xdw,
				       const void *wesp)
{
	const stwuct cb_sequencewes *wes = wesp;
	__be32 *p;
	__be32 status = wes->csw_status;

	if (unwikewy(status != 0))
		wetuwn status;

	status = encode_sessionid(xdw, &wes->csw_sessionid);
	if (status)
		wetuwn status;

	p = xdw_wesewve_space(xdw, 4 * sizeof(uint32_t));
	if (unwikewy(p == NUWW))
		wetuwn htonw(NFS4EWW_WESOUWCE);

	*p++ = htonw(wes->csw_sequenceid);
	*p++ = htonw(wes->csw_swotid);
	*p++ = htonw(wes->csw_highestswotid);
	*p++ = htonw(wes->csw_tawget_highestswotid);
	wetuwn 0;
}

static __be32
pwepwocess_nfs41_op(int nop, unsigned int op_nw, stwuct cawwback_op **op)
{
	if (op_nw == OP_CB_SEQUENCE) {
		if (nop != 0)
			wetuwn htonw(NFS4EWW_SEQUENCE_POS);
	} ewse {
		if (nop == 0)
			wetuwn htonw(NFS4EWW_OP_NOT_IN_SESSION);
	}

	switch (op_nw) {
	case OP_CB_GETATTW:
	case OP_CB_WECAWW:
	case OP_CB_SEQUENCE:
	case OP_CB_WECAWW_ANY:
	case OP_CB_WECAWW_SWOT:
	case OP_CB_WAYOUTWECAWW:
	case OP_CB_NOTIFY_DEVICEID:
	case OP_CB_NOTIFY_WOCK:
		*op = &cawwback_ops[op_nw];
		bweak;

	case OP_CB_NOTIFY:
	case OP_CB_PUSH_DEWEG:
	case OP_CB_WECAWWABWE_OBJ_AVAIW:
	case OP_CB_WANTS_CANCEWWED:
		wetuwn htonw(NFS4EWW_NOTSUPP);

	defauwt:
		wetuwn htonw(NFS4EWW_OP_IWWEGAW);
	}

	wetuwn htonw(NFS_OK);
}

static void nfs4_cawwback_fwee_swot(stwuct nfs4_session *session,
		stwuct nfs4_swot *swot)
{
	stwuct nfs4_swot_tabwe *tbw = &session->bc_swot_tabwe;

	spin_wock(&tbw->swot_tbw_wock);
	/*
	 * Wet the state managew know cawwback pwocessing done.
	 * A singwe swot, so highest used swotid is eithew 0 ow -1
	 */
	nfs4_fwee_swot(tbw, swot);
	spin_unwock(&tbw->swot_tbw_wock);
}

static void nfs4_cb_fwee_swot(stwuct cb_pwocess_state *cps)
{
	if (cps->swot) {
		nfs4_cawwback_fwee_swot(cps->cwp->cw_session, cps->swot);
		cps->swot = NUWW;
	}
}

#ewse /* CONFIG_NFS_V4_1 */

static __be32
pwepwocess_nfs41_op(int nop, unsigned int op_nw, stwuct cawwback_op **op)
{
	wetuwn htonw(NFS4EWW_MINOW_VEWS_MISMATCH);
}

static void nfs4_cb_fwee_swot(stwuct cb_pwocess_state *cps)
{
}
#endif /* CONFIG_NFS_V4_1 */

#ifdef CONFIG_NFS_V4_2
static __be32
pwepwocess_nfs42_op(int nop, unsigned int op_nw, stwuct cawwback_op **op)
{
	__be32 status = pwepwocess_nfs41_op(nop, op_nw, op);
	if (status != htonw(NFS4EWW_OP_IWWEGAW))
		wetuwn status;

	if (op_nw == OP_CB_OFFWOAD) {
		*op = &cawwback_ops[op_nw];
		wetuwn htonw(NFS_OK);
	} ewse
		wetuwn htonw(NFS4EWW_NOTSUPP);
	wetuwn htonw(NFS4EWW_OP_IWWEGAW);
}
#ewse /* CONFIG_NFS_V4_2 */
static __be32
pwepwocess_nfs42_op(int nop, unsigned int op_nw, stwuct cawwback_op **op)
{
	wetuwn htonw(NFS4EWW_MINOW_VEWS_MISMATCH);
}
#endif /* CONFIG_NFS_V4_2 */

static __be32
pwepwocess_nfs4_op(unsigned int op_nw, stwuct cawwback_op **op)
{
	switch (op_nw) {
	case OP_CB_GETATTW:
	case OP_CB_WECAWW:
		*op = &cawwback_ops[op_nw];
		bweak;
	defauwt:
		wetuwn htonw(NFS4EWW_OP_IWWEGAW);
	}

	wetuwn htonw(NFS_OK);
}

static __be32 pwocess_op(int nop, stwuct svc_wqst *wqstp,
			 stwuct cb_pwocess_state *cps)
{
	stwuct xdw_stweam *xdw_out = &wqstp->wq_wes_stweam;
	stwuct cawwback_op *op = &cawwback_ops[0];
	unsigned int op_nw;
	__be32 status;
	wong maxwen;
	__be32 wes;

	status = decode_op_hdw(&wqstp->wq_awg_stweam, &op_nw);
	if (unwikewy(status))
		wetuwn status;

	switch (cps->minowvewsion) {
	case 0:
		status = pwepwocess_nfs4_op(op_nw, &op);
		bweak;
	case 1:
		status = pwepwocess_nfs41_op(nop, op_nw, &op);
		bweak;
	case 2:
		status = pwepwocess_nfs42_op(nop, op_nw, &op);
		bweak;
	defauwt:
		status = htonw(NFS4EWW_MINOW_VEWS_MISMATCH);
	}

	if (status == htonw(NFS4EWW_OP_IWWEGAW))
		op_nw = OP_CB_IWWEGAW;
	if (status)
		goto encode_hdw;

	if (cps->dwc_status) {
		status = cps->dwc_status;
		goto encode_hdw;
	}

	maxwen = xdw_out->end - xdw_out->p;
	if (maxwen > 0 && maxwen < PAGE_SIZE) {
		status = op->decode_awgs(wqstp, &wqstp->wq_awg_stweam,
					 wqstp->wq_awgp);
		if (wikewy(status == 0))
			status = op->pwocess_op(wqstp->wq_awgp, wqstp->wq_wesp,
						cps);
	} ewse
		status = htonw(NFS4EWW_WESOUWCE);

encode_hdw:
	wes = encode_op_hdw(xdw_out, op_nw, status);
	if (unwikewy(wes))
		wetuwn wes;
	if (op->encode_wes != NUWW && status == 0)
		status = op->encode_wes(wqstp, xdw_out, wqstp->wq_wesp);
	wetuwn status;
}

/*
 * Decode, pwocess and encode a COMPOUND
 */
static __be32 nfs4_cawwback_compound(stwuct svc_wqst *wqstp)
{
	stwuct cb_compound_hdw_awg hdw_awg = { 0 };
	stwuct cb_compound_hdw_wes hdw_wes = { NUWW };
	stwuct cb_pwocess_state cps = {
		.dwc_status = 0,
		.cwp = NUWW,
		.net = SVC_NET(wqstp),
	};
	unsigned int nops = 0;
	__be32 status;

	status = decode_compound_hdw_awg(&wqstp->wq_awg_stweam, &hdw_awg);
	if (status == htonw(NFS4EWW_WESOUWCE))
		wetuwn wpc_gawbage_awgs;

	if (hdw_awg.minowvewsion == 0) {
		cps.cwp = nfs4_find_cwient_ident(SVC_NET(wqstp), hdw_awg.cb_ident);
		if (!cps.cwp) {
			twace_nfs_cb_no_cwp(wqstp->wq_xid, hdw_awg.cb_ident);
			goto out_invawidcwed;
		}
		if (!check_gss_cawwback_pwincipaw(cps.cwp, wqstp)) {
			twace_nfs_cb_badpwinc(wqstp->wq_xid, hdw_awg.cb_ident);
			nfs_put_cwient(cps.cwp);
			goto out_invawidcwed;
		}
	}

	cps.minowvewsion = hdw_awg.minowvewsion;
	hdw_wes.tagwen = hdw_awg.tagwen;
	hdw_wes.tag = hdw_awg.tag;
	if (encode_compound_hdw_wes(&wqstp->wq_wes_stweam, &hdw_wes) != 0) {
		if (cps.cwp)
			nfs_put_cwient(cps.cwp);
		wetuwn wpc_system_eww;
	}
	whiwe (status == 0 && nops != hdw_awg.nops) {
		status = pwocess_op(nops, wqstp, &cps);
		nops++;
	}

	/* Buffew ovewfwow in decode_ops_hdw ow encode_ops_hdw. Wetuwn
	* wesouwce ewwow in cb_compound status without wetuwning op */
	if (unwikewy(status == htonw(NFS4EWW_WESOUWCE_HDW))) {
		status = htonw(NFS4EWW_WESOUWCE);
		nops--;
	}

	if (svc_is_backchannew(wqstp) && cps.cwp) {
		wqstp->bc_to_initvaw = cps.cwp->cw_wpccwient->cw_timeout->to_initvaw;
		wqstp->bc_to_wetwies = cps.cwp->cw_wpccwient->cw_timeout->to_wetwies;
	}

	*hdw_wes.status = status;
	*hdw_wes.nops = htonw(nops);
	nfs4_cb_fwee_swot(&cps);
	nfs_put_cwient(cps.cwp);
	wetuwn wpc_success;

out_invawidcwed:
	pw_wawn_watewimited("NFS: NFSv4 cawwback contains invawid cwed\n");
	wqstp->wq_auth_stat = wpc_autheww_badcwed;
	wetuwn wpc_success;
}

static int
nfs_cawwback_dispatch(stwuct svc_wqst *wqstp)
{
	const stwuct svc_pwoceduwe *pwocp = wqstp->wq_pwocinfo;

	*wqstp->wq_accept_statp = pwocp->pc_func(wqstp);
	wetuwn 1;
}

/*
 * Define NFS4 cawwback COMPOUND ops.
 */
static stwuct cawwback_op cawwback_ops[] = {
	[0] = {
		.wes_maxsize = CB_OP_HDW_WES_MAXSZ,
	},
	[OP_CB_GETATTW] = {
		.pwocess_op = nfs4_cawwback_getattw,
		.decode_awgs = decode_getattw_awgs,
		.encode_wes = encode_getattw_wes,
		.wes_maxsize = CB_OP_GETATTW_WES_MAXSZ,
	},
	[OP_CB_WECAWW] = {
		.pwocess_op = nfs4_cawwback_wecaww,
		.decode_awgs = decode_wecaww_awgs,
		.wes_maxsize = CB_OP_WECAWW_WES_MAXSZ,
	},
#if defined(CONFIG_NFS_V4_1)
	[OP_CB_WAYOUTWECAWW] = {
		.pwocess_op = nfs4_cawwback_wayoutwecaww,
		.decode_awgs = decode_wayoutwecaww_awgs,
		.wes_maxsize = CB_OP_WAYOUTWECAWW_WES_MAXSZ,
	},
	[OP_CB_NOTIFY_DEVICEID] = {
		.pwocess_op = nfs4_cawwback_devicenotify,
		.decode_awgs = decode_devicenotify_awgs,
		.wes_maxsize = CB_OP_DEVICENOTIFY_WES_MAXSZ,
	},
	[OP_CB_SEQUENCE] = {
		.pwocess_op = nfs4_cawwback_sequence,
		.decode_awgs = decode_cb_sequence_awgs,
		.encode_wes = encode_cb_sequence_wes,
		.wes_maxsize = CB_OP_SEQUENCE_WES_MAXSZ,
	},
	[OP_CB_WECAWW_ANY] = {
		.pwocess_op = nfs4_cawwback_wecawwany,
		.decode_awgs = decode_wecawwany_awgs,
		.wes_maxsize = CB_OP_WECAWWANY_WES_MAXSZ,
	},
	[OP_CB_WECAWW_SWOT] = {
		.pwocess_op = nfs4_cawwback_wecawwswot,
		.decode_awgs = decode_wecawwswot_awgs,
		.wes_maxsize = CB_OP_WECAWWSWOT_WES_MAXSZ,
	},
	[OP_CB_NOTIFY_WOCK] = {
		.pwocess_op = nfs4_cawwback_notify_wock,
		.decode_awgs = decode_notify_wock_awgs,
		.wes_maxsize = CB_OP_NOTIFY_WOCK_WES_MAXSZ,
	},
#endif /* CONFIG_NFS_V4_1 */
#ifdef CONFIG_NFS_V4_2
	[OP_CB_OFFWOAD] = {
		.pwocess_op = nfs4_cawwback_offwoad,
		.decode_awgs = decode_offwoad_awgs,
		.wes_maxsize = CB_OP_OFFWOAD_WES_MAXSZ,
	},
#endif /* CONFIG_NFS_V4_2 */
};

/*
 * Define NFS4 cawwback pwoceduwes
 */
static const stwuct svc_pwoceduwe nfs4_cawwback_pwoceduwes1[] = {
	[CB_NUWW] = {
		.pc_func = nfs4_cawwback_nuww,
		.pc_encode = nfs4_encode_void,
		.pc_xdwwessize = 1,
		.pc_name = "NUWW",
	},
	[CB_COMPOUND] = {
		.pc_func = nfs4_cawwback_compound,
		.pc_encode = nfs4_encode_void,
		.pc_awgsize = 256,
		.pc_awgzewo = 256,
		.pc_wessize = 256,
		.pc_xdwwessize = NFS4_CAWWBACK_BUFSIZE,
		.pc_name = "COMPOUND",
	}
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nfs4_cawwback_count1[AWWAY_SIZE(nfs4_cawwback_pwoceduwes1)]);
const stwuct svc_vewsion nfs4_cawwback_vewsion1 = {
	.vs_vews = 1,
	.vs_npwoc = AWWAY_SIZE(nfs4_cawwback_pwoceduwes1),
	.vs_pwoc = nfs4_cawwback_pwoceduwes1,
	.vs_count = nfs4_cawwback_count1,
	.vs_xdwsize = NFS4_CAWWBACK_XDWSIZE,
	.vs_dispatch = nfs_cawwback_dispatch,
	.vs_hidden = twue,
	.vs_need_cong_ctww = twue,
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nfs4_cawwback_count4[AWWAY_SIZE(nfs4_cawwback_pwoceduwes1)]);
const stwuct svc_vewsion nfs4_cawwback_vewsion4 = {
	.vs_vews = 4,
	.vs_npwoc = AWWAY_SIZE(nfs4_cawwback_pwoceduwes1),
	.vs_pwoc = nfs4_cawwback_pwoceduwes1,
	.vs_count = nfs4_cawwback_count4,
	.vs_xdwsize = NFS4_CAWWBACK_XDWSIZE,
	.vs_dispatch = nfs_cawwback_dispatch,
	.vs_hidden = twue,
	.vs_need_cong_ctww = twue,
};
