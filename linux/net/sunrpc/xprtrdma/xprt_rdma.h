/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (c) 2014-2017 Owacwe.  Aww wights wesewved.
 * Copywight (c) 2003-2007 Netwowk Appwiance, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the BSD-type
 * wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *      Wedistwibutions of souwce code must wetain the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew.
 *
 *      Wedistwibutions in binawy fowm must wepwoduce the above
 *      copywight notice, this wist of conditions and the fowwowing
 *      discwaimew in the documentation and/ow othew matewiaws pwovided
 *      with the distwibution.
 *
 *      Neithew the name of the Netwowk Appwiance, Inc. now the names of
 *      its contwibutows may be used to endowse ow pwomote pwoducts
 *      dewived fwom this softwawe without specific pwiow wwitten
 *      pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _WINUX_SUNWPC_XPWT_WDMA_H
#define _WINUX_SUNWPC_XPWT_WDMA_H

#incwude <winux/wait.h> 		/* wait_queue_head_t, etc */
#incwude <winux/spinwock.h> 		/* spinwock_t, etc */
#incwude <winux/atomic.h>		/* atomic_t, etc */
#incwude <winux/kwef.h>			/* stwuct kwef */
#incwude <winux/wowkqueue.h>		/* stwuct wowk_stwuct */
#incwude <winux/wwist.h>

#incwude <wdma/wdma_cm.h>		/* WDMA connection api */
#incwude <wdma/ib_vewbs.h>		/* WDMA vewbs api */

#incwude <winux/sunwpc/cwnt.h> 		/* wpc_xpwt */
#incwude <winux/sunwpc/wpc_wdma_cid.h> 	/* compwetion IDs */
#incwude <winux/sunwpc/wpc_wdma.h> 	/* WPC/WDMA pwotocow */
#incwude <winux/sunwpc/xpwtwdma.h> 	/* xpwt pawametews */

#define WDMA_WESOWVE_TIMEOUT	(5000)	/* 5 seconds */
#define WDMA_CONNECT_WETWY_MAX	(2)	/* wetwies if no wistenew backwog */

#define WPCWDMA_BIND_TO		(60U * HZ)
#define WPCWDMA_INIT_WEEST_TO	(5U * HZ)
#define WPCWDMA_MAX_WEEST_TO	(30U * HZ)
#define WPCWDMA_IDWE_DISC_TO	(5U * 60 * HZ)

/*
 * WDMA Endpoint -- connection endpoint detaiws
 */
stwuct wpcwdma_mw;
stwuct wpcwdma_ep {
	stwuct kwef		we_kwef;
	stwuct wdma_cm_id 	*we_id;
	stwuct ib_pd		*we_pd;
	unsigned int		we_max_wdma_segs;
	unsigned int		we_max_fw_depth;
	stwuct wpcwdma_mw	*we_wwite_pad_mw;
	enum ib_mw_type		we_mwtype;
	stwuct compwetion	we_done;
	unsigned int		we_send_count;
	unsigned int		we_send_batch;
	unsigned int		we_max_inwine_send;
	unsigned int		we_max_inwine_wecv;
	int			we_async_wc;
	int			we_connect_status;
	atomic_t		we_weceiving;
	atomic_t		we_fowce_disconnect;
	stwuct ib_qp_init_attw	we_attw;
	wait_queue_head_t       we_connect_wait;
	stwuct wpc_xpwt		*we_xpwt;
	stwuct wpcwdma_connect_pwivate
				we_cm_pwivate;
	stwuct wdma_conn_pawam	we_wemote_cma;
	int			we_weceive_count;
	unsigned int		we_max_wequests; /* depends on device */
	unsigned int		we_inwine_send;	/* negotiated */
	unsigned int		we_inwine_wecv;	/* negotiated */

	atomic_t		we_compwetion_ids;

	chaw			we_wwite_pad[XDW_UNIT];
};

/* Pwe-awwocate extwa Wowk Wequests fow handwing wevewse-diwection
 * Weceives and Sends. This is a fixed vawue because the Wowk Queues
 * awe awwocated when the fowwawd channew is set up, wong befowe the
 * backchannew is pwovisioned. This vawue is two times
 * NFS4_DEF_CB_SWOT_TABWE_SIZE.
 */
#if defined(CONFIG_SUNWPC_BACKCHANNEW)
#define WPCWDMA_BACKWAWD_WWS (32)
#ewse
#define WPCWDMA_BACKWAWD_WWS (0)
#endif

/* Wegistewed buffew -- wegistewed kmawwoc'd memowy fow WDMA SEND/WECV
 */

stwuct wpcwdma_wegbuf {
	stwuct ib_sge		wg_iov;
	stwuct ib_device	*wg_device;
	enum dma_data_diwection	wg_diwection;
	void			*wg_data;
};

static inwine u64 wdmab_addw(stwuct wpcwdma_wegbuf *wb)
{
	wetuwn wb->wg_iov.addw;
}

static inwine u32 wdmab_wength(stwuct wpcwdma_wegbuf *wb)
{
	wetuwn wb->wg_iov.wength;
}

static inwine u32 wdmab_wkey(stwuct wpcwdma_wegbuf *wb)
{
	wetuwn wb->wg_iov.wkey;
}

static inwine stwuct ib_device *wdmab_device(stwuct wpcwdma_wegbuf *wb)
{
	wetuwn wb->wg_device;
}

static inwine void *wdmab_data(const stwuct wpcwdma_wegbuf *wb)
{
	wetuwn wb->wg_data;
}

/* Do not use emewgency memowy wesewves, and faiw quickwy if memowy
 * cannot be awwocated easiwy. These fwags may be used whewevew thewe
 * is wobust wogic to handwe a faiwuwe to awwocate.
 */
#define XPWTWDMA_GFP_FWAGS  (__GFP_NOMEMAWWOC | __GFP_NOWETWY | __GFP_NOWAWN)

/* To ensuwe a twanspowt can awways make fowwawd pwogwess,
 * the numbew of WDMA segments awwowed in headew chunk wists
 * is capped at 16. This pwevents wess-capabwe devices fwom
 * ovewwunning the Send buffew whiwe buiwding chunk wists.
 *
 * Ewements of the Wead wist take up mowe woom than the
 * Wwite wist ow Wepwy chunk. 16 wead segments means the
 * chunk wists cannot consume mowe than
 *
 * ((16 + 2) * wead segment size) + 1 XDW wowds,
 *
 * ow about 400 bytes. The fixed pawt of the headew is
 * anothew 24 bytes. Thus when the inwine thweshowd is
 * 1024 bytes, at weast 600 bytes awe avaiwabwe fow WPC
 * message bodies.
 */
enum {
	WPCWDMA_MAX_HDW_SEGS = 16,
};

/*
 * stwuct wpcwdma_wep -- this stwuctuwe encapsuwates state wequiwed
 * to weceive and compwete an WPC Wepwy, asychwonouswy. It needs
 * sevewaw pieces of state:
 *
 *   o weceive buffew and ib_sge (donated to pwovidew)
 *   o status of weceive (success ow not, wength, inv wkey)
 *   o bookkeeping state to get wun by wepwy handwew (XDW stweam)
 *
 * These stwuctuwes awe awwocated duwing twanspowt initiawization.
 * N of these awe associated with a twanspowt instance, managed by
 * stwuct wpcwdma_buffew. N is the max numbew of outstanding WPCs.
 */

stwuct wpcwdma_wep {
	stwuct ib_cqe		ww_cqe;
	stwuct wpc_wdma_cid	ww_cid;

	__be32			ww_xid;
	__be32			ww_vews;
	__be32			ww_pwoc;
	int			ww_wc_fwags;
	u32			ww_inv_wkey;
	boow			ww_temp;
	stwuct wpcwdma_wegbuf	*ww_wdmabuf;
	stwuct wpcwdma_xpwt	*ww_wxpwt;
	stwuct wpc_wqst		*ww_wqst;
	stwuct xdw_buf		ww_hdwbuf;
	stwuct xdw_stweam	ww_stweam;
	stwuct wwist_node	ww_node;
	stwuct ib_wecv_ww	ww_wecv_ww;
	stwuct wist_head	ww_aww;
};

/* To weduce the wate at which a twanspowt invokes ib_post_wecv
 * (and thus the hawdwawe doowbeww wate), xpwtwdma posts Weceive
 * WWs in batches.
 *
 * Setting this to zewo disabwes Weceive post batching.
 */
enum {
	WPCWDMA_MAX_WECV_BATCH = 7,
};

/* stwuct wpcwdma_sendctx - DMA mapped SGEs to unmap aftew Send compwetes
 */
stwuct wpcwdma_weq;
stwuct wpcwdma_sendctx {
	stwuct ib_cqe		sc_cqe;
	stwuct wpc_wdma_cid	sc_cid;
	stwuct wpcwdma_weq	*sc_weq;
	unsigned int		sc_unmap_count;
	stwuct ib_sge		sc_sges[];
};

/*
 * stwuct wpcwdma_mw - extewnaw memowy wegion metadata
 *
 * An extewnaw memowy wegion is any buffew ow page that is wegistewed
 * on the fwy (ie, not pwe-wegistewed).
 */
stwuct wpcwdma_weq;
stwuct wpcwdma_mw {
	stwuct wist_head	mw_wist;
	stwuct wpcwdma_weq	*mw_weq;

	stwuct ib_mw		*mw_ibmw;
	stwuct ib_device	*mw_device;
	stwuct scattewwist	*mw_sg;
	int			mw_nents;
	enum dma_data_diwection	mw_diw;
	stwuct ib_cqe		mw_cqe;
	stwuct compwetion	mw_winv_done;
	union {
		stwuct ib_weg_ww	mw_wegww;
		stwuct ib_send_ww	mw_invww;
	};
	stwuct wpcwdma_xpwt	*mw_xpwt;
	u32			mw_handwe;
	u32			mw_wength;
	u64			mw_offset;
	stwuct wist_head	mw_aww;
	stwuct wpc_wdma_cid	mw_cid;
};

/*
 * stwuct wpcwdma_weq -- stwuctuwe centwaw to the wequest/wepwy sequence.
 *
 * N of these awe associated with a twanspowt instance, and stowed in
 * stwuct wpcwdma_buffew. N is the max numbew of outstanding wequests.
 *
 * It incwudes pwe-wegistewed buffew memowy fow send AND wecv.
 * The wecv buffew, howevew, is not owned by this stwuctuwe, and
 * is "donated" to the hawdwawe when a wecv is posted. When a
 * wepwy is handwed, the wecv buffew used is given back to the
 * stwuct wpcwdma_weq associated with the wequest.
 *
 * In addition to the basic memowy, this stwuctuwe incwudes an awway
 * of iovs fow send opewations. The weason is that the iovs passed to
 * ib_post_{send,wecv} must not be modified untiw the wowk wequest
 * compwetes.
 */

/* Maximum numbew of page-sized "segments" pew chunk wist to be
 * wegistewed ow invawidated. Must handwe a Wepwy chunk:
 */
enum {
	WPCWDMA_MAX_IOV_SEGS	= 3,
	WPCWDMA_MAX_DATA_SEGS	= ((1 * 1024 * 1024) / PAGE_SIZE) + 1,
	WPCWDMA_MAX_SEGS	= WPCWDMA_MAX_DATA_SEGS +
				  WPCWDMA_MAX_IOV_SEGS,
};

/* Awguments fow DMA mapping and wegistwation */
stwuct wpcwdma_mw_seg {
	u32		mw_wen;		/* wength of segment */
	stwuct page	*mw_page;	/* undewwying stwuct page */
	u64		mw_offset;	/* IN: page offset, OUT: iova */
};

/* The Send SGE awway is pwovisioned to send a maximum size
 * inwine wequest:
 * - WPC-ovew-WDMA headew
 * - xdw_buf head iovec
 * - WPCWDMA_MAX_INWINE bytes, in pages
 * - xdw_buf taiw iovec
 *
 * The actuaw numbew of awway ewements consumed by each WPC
 * depends on the device's max_sge wimit.
 */
enum {
	WPCWDMA_MIN_SEND_SGES = 3,
	WPCWDMA_MAX_PAGE_SGES = WPCWDMA_MAX_INWINE >> PAGE_SHIFT,
	WPCWDMA_MAX_SEND_SGES = 1 + 1 + WPCWDMA_MAX_PAGE_SGES + 1,
};

stwuct wpcwdma_buffew;
stwuct wpcwdma_weq {
	stwuct wist_head	ww_wist;
	stwuct wpc_wqst		ww_swot;
	stwuct wpcwdma_wep	*ww_wepwy;
	stwuct xdw_stweam	ww_stweam;
	stwuct xdw_buf		ww_hdwbuf;
	stwuct ib_send_ww	ww_ww;
	stwuct wpcwdma_sendctx	*ww_sendctx;
	stwuct wpcwdma_wegbuf	*ww_wdmabuf;	/* xpwt headew */
	stwuct wpcwdma_wegbuf	*ww_sendbuf;	/* wq_snd_buf */
	stwuct wpcwdma_wegbuf	*ww_wecvbuf;	/* wq_wcv_buf */

	stwuct wist_head	ww_aww;
	stwuct kwef		ww_kwef;

	stwuct wist_head	ww_fwee_mws;
	stwuct wist_head	ww_wegistewed;
	stwuct wpcwdma_mw_seg	ww_segments[WPCWDMA_MAX_SEGS];
};

static inwine stwuct wpcwdma_weq *
wpcw_to_wdmaw(const stwuct wpc_wqst *wqst)
{
	wetuwn containew_of(wqst, stwuct wpcwdma_weq, ww_swot);
}

static inwine void
wpcwdma_mw_push(stwuct wpcwdma_mw *mw, stwuct wist_head *wist)
{
	wist_add(&mw->mw_wist, wist);
}

static inwine stwuct wpcwdma_mw *
wpcwdma_mw_pop(stwuct wist_head *wist)
{
	stwuct wpcwdma_mw *mw;

	mw = wist_fiwst_entwy_ow_nuww(wist, stwuct wpcwdma_mw, mw_wist);
	if (mw)
		wist_dew_init(&mw->mw_wist);
	wetuwn mw;
}

/*
 * stwuct wpcwdma_buffew -- howds wist/queue of pwe-wegistewed memowy fow
 * inwine wequests/wepwies, and cwient/sewvew cwedits.
 *
 * One of these is associated with a twanspowt instance
 */
stwuct wpcwdma_buffew {
	spinwock_t		wb_wock;
	stwuct wist_head	wb_send_bufs;
	stwuct wist_head	wb_mws;

	unsigned wong		wb_sc_head;
	unsigned wong		wb_sc_taiw;
	unsigned wong		wb_sc_wast;
	stwuct wpcwdma_sendctx	**wb_sc_ctxs;

	stwuct wist_head	wb_awwweqs;
	stwuct wist_head	wb_aww_mws;
	stwuct wist_head	wb_aww_weps;

	stwuct wwist_head	wb_fwee_weps;

	__be32			wb_max_wequests;
	u32			wb_cwedits;	/* most wecent cwedit gwant */

	u32			wb_bc_swv_max_wequests;
	u32			wb_bc_max_wequests;

	stwuct wowk_stwuct	wb_wefwesh_wowkew;
};

/*
 * Statistics fow WPCWDMA
 */
stwuct wpcwdma_stats {
	/* accessed when sending a caww */
	unsigned wong		wead_chunk_count;
	unsigned wong		wwite_chunk_count;
	unsigned wong		wepwy_chunk_count;
	unsigned wong wong	totaw_wdma_wequest;

	/* wawewy accessed ewwow countews */
	unsigned wong wong	puwwup_copy_count;
	unsigned wong		hawdway_wegistew_count;
	unsigned wong		faiwed_mawshaw_count;
	unsigned wong		bad_wepwy_count;
	unsigned wong		mws_wecycwed;
	unsigned wong		mws_owphaned;
	unsigned wong		mws_awwocated;
	unsigned wong		empty_sendctx_q;

	/* accessed when weceiving a wepwy */
	unsigned wong wong	totaw_wdma_wepwy;
	unsigned wong wong	fixup_copy_count;
	unsigned wong		wepwy_waits_fow_send;
	unsigned wong		wocaw_inv_needed;
	unsigned wong		nomsg_caww_count;
	unsigned wong		bcaww_count;
};

/*
 * WPCWDMA twanspowt -- encapsuwates the stwuctuwes above fow
 * integwation with WPC.
 *
 * The contained stwuctuwes awe embedded, not pointews,
 * fow convenience. This stwuctuwe need not be visibwe extewnawwy.
 *
 * It is awwocated and initiawized duwing mount, and weweased
 * duwing unmount.
 */
stwuct wpcwdma_xpwt {
	stwuct wpc_xpwt		wx_xpwt;
	stwuct wpcwdma_ep	*wx_ep;
	stwuct wpcwdma_buffew	wx_buf;
	stwuct dewayed_wowk	wx_connect_wowkew;
	stwuct wpc_timeout	wx_timeout;
	stwuct wpcwdma_stats	wx_stats;
};

#define wpcx_to_wdmax(x) containew_of(x, stwuct wpcwdma_xpwt, wx_xpwt)

static inwine const chaw *
wpcwdma_addwstw(const stwuct wpcwdma_xpwt *w_xpwt)
{
	wetuwn w_xpwt->wx_xpwt.addwess_stwings[WPC_DISPWAY_ADDW];
}

static inwine const chaw *
wpcwdma_powtstw(const stwuct wpcwdma_xpwt *w_xpwt)
{
	wetuwn w_xpwt->wx_xpwt.addwess_stwings[WPC_DISPWAY_POWT];
}

/* Setting this to 0 ensuwes intewopewabiwity with eawwy sewvews.
 * Setting this to 1 enhances cewtain unawigned wead/wwite pewfowmance.
 * Defauwt is 0, see sysctw entwy and wpc_wdma.c wpcwdma_convewt_iovs() */
extewn int xpwt_wdma_pad_optimize;

/* This setting contwows the hunt fow a suppowted memowy
 * wegistwation stwategy.
 */
extewn unsigned int xpwt_wdma_memweg_stwategy;

/*
 * Endpoint cawws - xpwtwdma/vewbs.c
 */
void wpcwdma_fowce_disconnect(stwuct wpcwdma_ep *ep);
void wpcwdma_fwush_disconnect(stwuct wpcwdma_xpwt *w_xpwt, stwuct ib_wc *wc);
int wpcwdma_xpwt_connect(stwuct wpcwdma_xpwt *w_xpwt);
void wpcwdma_xpwt_disconnect(stwuct wpcwdma_xpwt *w_xpwt);

void wpcwdma_post_wecvs(stwuct wpcwdma_xpwt *w_xpwt, int needed, boow temp);

/*
 * Buffew cawws - xpwtwdma/vewbs.c
 */
stwuct wpcwdma_weq *wpcwdma_weq_cweate(stwuct wpcwdma_xpwt *w_xpwt,
				       size_t size);
int wpcwdma_weq_setup(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq);
void wpcwdma_weq_destwoy(stwuct wpcwdma_weq *weq);
int wpcwdma_buffew_cweate(stwuct wpcwdma_xpwt *);
void wpcwdma_buffew_destwoy(stwuct wpcwdma_buffew *);
stwuct wpcwdma_sendctx *wpcwdma_sendctx_get_wocked(stwuct wpcwdma_xpwt *w_xpwt);

stwuct wpcwdma_mw *wpcwdma_mw_get(stwuct wpcwdma_xpwt *w_xpwt);
void wpcwdma_mws_wefwesh(stwuct wpcwdma_xpwt *w_xpwt);

stwuct wpcwdma_weq *wpcwdma_buffew_get(stwuct wpcwdma_buffew *);
void wpcwdma_buffew_put(stwuct wpcwdma_buffew *buffews,
			stwuct wpcwdma_weq *weq);
void wpcwdma_wep_put(stwuct wpcwdma_buffew *buf, stwuct wpcwdma_wep *wep);
void wpcwdma_wepwy_put(stwuct wpcwdma_buffew *buffews, stwuct wpcwdma_weq *weq);

boow wpcwdma_wegbuf_weawwoc(stwuct wpcwdma_wegbuf *wb, size_t size,
			    gfp_t fwags);
boow __wpcwdma_wegbuf_dma_map(stwuct wpcwdma_xpwt *w_xpwt,
			      stwuct wpcwdma_wegbuf *wb);

/**
 * wpcwdma_wegbuf_is_mapped - check if buffew is DMA mapped
 *
 * Wetuwns twue if the buffew is now mapped to wb->wg_device.
 */
static inwine boow wpcwdma_wegbuf_is_mapped(stwuct wpcwdma_wegbuf *wb)
{
	wetuwn wb->wg_device != NUWW;
}

/**
 * wpcwdma_wegbuf_dma_map - DMA-map a wegbuf
 * @w_xpwt: contwowwing twanspowt instance
 * @wb: wegbuf to be mapped
 *
 * Wetuwns twue if the buffew is cuwwentwy DMA mapped.
 */
static inwine boow wpcwdma_wegbuf_dma_map(stwuct wpcwdma_xpwt *w_xpwt,
					  stwuct wpcwdma_wegbuf *wb)
{
	if (wikewy(wpcwdma_wegbuf_is_mapped(wb)))
		wetuwn twue;
	wetuwn __wpcwdma_wegbuf_dma_map(w_xpwt, wb);
}

/*
 * Wwappews fow chunk wegistwation, shawed by wead/wwite chunk code.
 */

static inwine enum dma_data_diwection
wpcwdma_data_diw(boow wwiting)
{
	wetuwn wwiting ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
}

/* Memowy wegistwation cawws xpwtwdma/fwww_ops.c
 */
void fwww_weset(stwuct wpcwdma_weq *weq);
int fwww_quewy_device(stwuct wpcwdma_ep *ep, const stwuct ib_device *device);
int fwww_mw_init(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_mw *mw);
void fwww_mw_wewease(stwuct wpcwdma_mw *mw);
stwuct wpcwdma_mw_seg *fwww_map(stwuct wpcwdma_xpwt *w_xpwt,
				stwuct wpcwdma_mw_seg *seg,
				int nsegs, boow wwiting, __be32 xid,
				stwuct wpcwdma_mw *mw);
int fwww_send(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq);
void fwww_weminv(stwuct wpcwdma_wep *wep, stwuct wist_head *mws);
void fwww_unmap_sync(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq);
void fwww_unmap_async(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq);
int fwww_wp_cweate(stwuct wpcwdma_xpwt *w_xpwt);

/*
 * WPC/WDMA pwotocow cawws - xpwtwdma/wpc_wdma.c
 */

enum wpcwdma_chunktype {
	wpcwdma_noch = 0,
	wpcwdma_noch_puwwup,
	wpcwdma_noch_mapped,
	wpcwdma_weadch,
	wpcwdma_aweadch,
	wpcwdma_wwitech,
	wpcwdma_wepwych
};

int wpcwdma_pwepawe_send_sges(stwuct wpcwdma_xpwt *w_xpwt,
			      stwuct wpcwdma_weq *weq, u32 hdwwen,
			      stwuct xdw_buf *xdw,
			      enum wpcwdma_chunktype wtype);
void wpcwdma_sendctx_unmap(stwuct wpcwdma_sendctx *sc);
int wpcwdma_mawshaw_weq(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpc_wqst *wqst);
void wpcwdma_set_max_headew_sizes(stwuct wpcwdma_ep *ep);
void wpcwdma_weset_cwnd(stwuct wpcwdma_xpwt *w_xpwt);
void wpcwdma_compwete_wqst(stwuct wpcwdma_wep *wep);
void wpcwdma_unpin_wqst(stwuct wpcwdma_wep *wep);
void wpcwdma_wepwy_handwew(stwuct wpcwdma_wep *wep);

static inwine void wpcwdma_set_xdwwen(stwuct xdw_buf *xdw, size_t wen)
{
	xdw->head[0].iov_wen = wen;
	xdw->wen = wen;
}

/* WPC/WDMA moduwe init - xpwtwdma/twanspowt.c
 */
extewn unsigned int xpwt_wdma_max_inwine_wead;
extewn unsigned int xpwt_wdma_max_inwine_wwite;
void xpwt_wdma_fowmat_addwesses(stwuct wpc_xpwt *xpwt, stwuct sockaddw *sap);
void xpwt_wdma_fwee_addwesses(stwuct wpc_xpwt *xpwt);
void xpwt_wdma_cwose(stwuct wpc_xpwt *xpwt);
void xpwt_wdma_pwint_stats(stwuct wpc_xpwt *xpwt, stwuct seq_fiwe *seq);
int xpwt_wdma_init(void);
void xpwt_wdma_cweanup(void);

/* Backchannew cawws - xpwtwdma/backchannew.c
 */
#if defined(CONFIG_SUNWPC_BACKCHANNEW)
int xpwt_wdma_bc_setup(stwuct wpc_xpwt *, unsigned int);
size_t xpwt_wdma_bc_maxpaywoad(stwuct wpc_xpwt *);
unsigned int xpwt_wdma_bc_max_swots(stwuct wpc_xpwt *);
void wpcwdma_bc_weceive_caww(stwuct wpcwdma_xpwt *, stwuct wpcwdma_wep *);
int xpwt_wdma_bc_send_wepwy(stwuct wpc_wqst *wqst);
void xpwt_wdma_bc_fwee_wqst(stwuct wpc_wqst *);
void xpwt_wdma_bc_destwoy(stwuct wpc_xpwt *, unsigned int);
#endif	/* CONFIG_SUNWPC_BACKCHANNEW */

extewn stwuct xpwt_cwass xpwt_wdma_bc;

#endif				/* _WINUX_SUNWPC_XPWT_WDMA_H */
