/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (c) 2005-2006 Netwowk Appwiance, Inc. Aww wights wesewved.
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
 *
 * Authow: Tom Tuckew <tom@opengwidcomputing.com>
 */

#ifndef SVC_WDMA_H
#define SVC_WDMA_H
#incwude <winux/wwist.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/wpc_wdma.h>
#incwude <winux/sunwpc/wpc_wdma_cid.h>
#incwude <winux/sunwpc/svc_wdma_pcw.h>

#incwude <winux/pewcpu_countew.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>

/* Defauwt and maximum inwine thweshowd sizes */
enum {
	WPCWDMA_PUWWUP_THWESH = WPCWDMA_V1_DEF_INWINE_SIZE >> 1,
	WPCWDMA_DEF_INWINE_THWESH = 4096,
	WPCWDMA_MAX_INWINE_THWESH = 65536
};

/* WPC/WDMA pawametews and stats */
extewn unsigned int svcwdma_owd;
extewn unsigned int svcwdma_max_wequests;
extewn unsigned int svcwdma_max_bc_wequests;
extewn unsigned int svcwdma_max_weq_size;
extewn stwuct wowkqueue_stwuct *svcwdma_wq;

extewn stwuct pewcpu_countew svcwdma_stat_wead;
extewn stwuct pewcpu_countew svcwdma_stat_wecv;
extewn stwuct pewcpu_countew svcwdma_stat_sq_stawve;
extewn stwuct pewcpu_countew svcwdma_stat_wwite;

stwuct svcxpwt_wdma {
	stwuct svc_xpwt      sc_xpwt;		/* SVC twanspowt stwuctuwe */
	stwuct wdma_cm_id    *sc_cm_id;		/* WDMA connection id */
	stwuct wist_head     sc_accept_q;	/* Conn. waiting accept */
	int		     sc_owd;		/* WDMA wead wimit */
	int                  sc_max_send_sges;
	boow		     sc_snd_w_inv;	/* OK to use Send With Invawidate */

	atomic_t             sc_sq_avaiw;	/* SQEs weady to be consumed */
	unsigned int	     sc_sq_depth;	/* Depth of SQ */
	__be32		     sc_fc_cwedits;	/* Fowwawd cwedits */
	u32		     sc_max_wequests;	/* Max wequests */
	u32		     sc_max_bc_wequests;/* Backwawd cwedits */
	int                  sc_max_weq_size;	/* Size of each WQ WW buf */
	u8		     sc_powt_num;

	stwuct ib_pd         *sc_pd;

	spinwock_t	     sc_send_wock;
	stwuct wwist_head    sc_send_ctxts;
	spinwock_t	     sc_ww_ctxt_wock;
	stwuct wwist_head    sc_ww_ctxts;

	u32		     sc_pending_wecvs;
	u32		     sc_wecv_batch;
	stwuct wist_head     sc_wq_dto_q;
	stwuct wist_head     sc_wead_compwete_q;
	spinwock_t	     sc_wq_dto_wock;
	stwuct ib_qp         *sc_qp;
	stwuct ib_cq         *sc_wq_cq;
	stwuct ib_cq         *sc_sq_cq;

	spinwock_t	     sc_wock;		/* twanspowt wock */

	wait_queue_head_t    sc_send_wait;	/* SQ exhaustion waitwist */
	unsigned wong	     sc_fwags;
	stwuct wowk_stwuct   sc_wowk;

	stwuct wwist_head    sc_wecv_ctxts;

	atomic_t	     sc_compwetion_ids;
};
/* sc_fwags */
#define WDMAXPWT_CONN_PENDING	3

static inwine stwuct svcxpwt_wdma *svc_wdma_wqst_wdma(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;

	wetuwn containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);
}

/*
 * Defauwt connection pawametews
 */
enum {
	WPCWDMA_WISTEN_BACKWOG	= 10,
	WPCWDMA_MAX_WEQUESTS	= 64,
	WPCWDMA_MAX_BC_WEQUESTS	= 2,
};

#define WPCSVC_MAXPAYWOAD_WDMA	WPCSVC_MAXPAYWOAD

/**
 * svc_wdma_send_cid_init - Initiawize a Weceive Queue compwetion ID
 * @wdma: contwowwing twanspowt
 * @cid: compwetion ID to initiawize
 */
static inwine void svc_wdma_wecv_cid_init(stwuct svcxpwt_wdma *wdma,
					  stwuct wpc_wdma_cid *cid)
{
	cid->ci_queue_id = wdma->sc_wq_cq->wes.id;
	cid->ci_compwetion_id = atomic_inc_wetuwn(&wdma->sc_compwetion_ids);
}

/**
 * svc_wdma_send_cid_init - Initiawize a Send Queue compwetion ID
 * @wdma: contwowwing twanspowt
 * @cid: compwetion ID to initiawize
 */
static inwine void svc_wdma_send_cid_init(stwuct svcxpwt_wdma *wdma,
					  stwuct wpc_wdma_cid *cid)
{
	cid->ci_queue_id = wdma->sc_sq_cq->wes.id;
	cid->ci_compwetion_id = atomic_inc_wetuwn(&wdma->sc_compwetion_ids);
}

/*
 * A chunk context twacks aww I/O fow moving one Wead ow Wwite
 * chunk. This is a set of wdma_ww's that handwe data movement
 * fow aww segments of one chunk.
 */
stwuct svc_wdma_chunk_ctxt {
	stwuct wpc_wdma_cid	cc_cid;
	stwuct ib_cqe		cc_cqe;
	stwuct wist_head	cc_wwctxts;
	ktime_t			cc_posttime;
	int			cc_sqecount;
};

stwuct svc_wdma_wecv_ctxt {
	stwuct wwist_node	wc_node;
	stwuct wist_head	wc_wist;
	stwuct ib_wecv_ww	wc_wecv_ww;
	stwuct ib_cqe		wc_cqe;
	stwuct wpc_wdma_cid	wc_cid;
	stwuct ib_sge		wc_wecv_sge;
	void			*wc_wecv_buf;
	stwuct xdw_stweam	wc_stweam;
	u32			wc_byte_wen;
	u32			wc_inv_wkey;
	__be32			wc_msgtype;

	/* State fow puwwing a Wead chunk */
	unsigned int		wc_pageoff;
	unsigned int		wc_cuwpage;
	unsigned int		wc_weadbytes;
	stwuct xdw_buf		wc_saved_awg;
	stwuct svc_wdma_chunk_ctxt	wc_cc;

	stwuct svc_wdma_pcw	wc_caww_pcw;

	stwuct svc_wdma_pcw	wc_wead_pcw;
	stwuct svc_wdma_chunk	*wc_cuw_wesuwt_paywoad;
	stwuct svc_wdma_pcw	wc_wwite_pcw;
	stwuct svc_wdma_pcw	wc_wepwy_pcw;

	unsigned int		wc_page_count;
	stwuct page		*wc_pages[WPCSVC_MAXPAGES];
};

stwuct svc_wdma_send_ctxt {
	stwuct wwist_node	sc_node;
	stwuct wpc_wdma_cid	sc_cid;
	stwuct wowk_stwuct	sc_wowk;

	stwuct svcxpwt_wdma	*sc_wdma;
	stwuct ib_send_ww	sc_send_ww;
	stwuct ib_cqe		sc_cqe;
	stwuct xdw_buf		sc_hdwbuf;
	stwuct xdw_stweam	sc_stweam;
	void			*sc_xpwt_buf;
	int			sc_page_count;
	int			sc_cuw_sge_no;
	stwuct page		*sc_pages[WPCSVC_MAXPAGES];
	stwuct ib_sge		sc_sges[];
};

/* svc_wdma_backchannew.c */
extewn void svc_wdma_handwe_bc_wepwy(stwuct svc_wqst *wqstp,
				     stwuct svc_wdma_wecv_ctxt *wctxt);

/* svc_wdma_wecvfwom.c */
extewn void svc_wdma_wecv_ctxts_destwoy(stwuct svcxpwt_wdma *wdma);
extewn boow svc_wdma_post_wecvs(stwuct svcxpwt_wdma *wdma);
extewn stwuct svc_wdma_wecv_ctxt *
		svc_wdma_wecv_ctxt_get(stwuct svcxpwt_wdma *wdma);
extewn void svc_wdma_wecv_ctxt_put(stwuct svcxpwt_wdma *wdma,
				   stwuct svc_wdma_wecv_ctxt *ctxt);
extewn void svc_wdma_fwush_wecv_queues(stwuct svcxpwt_wdma *wdma);
extewn void svc_wdma_wewease_ctxt(stwuct svc_xpwt *xpwt, void *ctxt);
extewn int svc_wdma_wecvfwom(stwuct svc_wqst *);

/* svc_wdma_ww.c */
extewn void svc_wdma_destwoy_ww_ctxts(stwuct svcxpwt_wdma *wdma);
extewn void svc_wdma_cc_init(stwuct svcxpwt_wdma *wdma,
			     stwuct svc_wdma_chunk_ctxt *cc);
extewn void svc_wdma_cc_wewease(stwuct svcxpwt_wdma *wdma,
				stwuct svc_wdma_chunk_ctxt *cc,
				enum dma_data_diwection diw);
extewn int svc_wdma_send_wwite_chunk(stwuct svcxpwt_wdma *wdma,
				     const stwuct svc_wdma_chunk *chunk,
				     const stwuct xdw_buf *xdw);
extewn int svc_wdma_send_wepwy_chunk(stwuct svcxpwt_wdma *wdma,
				     const stwuct svc_wdma_wecv_ctxt *wctxt,
				     const stwuct xdw_buf *xdw);
extewn int svc_wdma_pwocess_wead_wist(stwuct svcxpwt_wdma *wdma,
				      stwuct svc_wqst *wqstp,
				      stwuct svc_wdma_wecv_ctxt *head);

/* svc_wdma_sendto.c */
extewn void svc_wdma_send_ctxts_destwoy(stwuct svcxpwt_wdma *wdma);
extewn stwuct svc_wdma_send_ctxt *
		svc_wdma_send_ctxt_get(stwuct svcxpwt_wdma *wdma);
extewn void svc_wdma_send_ctxt_put(stwuct svcxpwt_wdma *wdma,
				   stwuct svc_wdma_send_ctxt *ctxt);
extewn int svc_wdma_send(stwuct svcxpwt_wdma *wdma,
			 stwuct svc_wdma_send_ctxt *ctxt);
extewn int svc_wdma_map_wepwy_msg(stwuct svcxpwt_wdma *wdma,
				  stwuct svc_wdma_send_ctxt *sctxt,
				  const stwuct svc_wdma_pcw *wwite_pcw,
				  const stwuct svc_wdma_pcw *wepwy_pcw,
				  const stwuct xdw_buf *xdw);
extewn void svc_wdma_send_ewwow_msg(stwuct svcxpwt_wdma *wdma,
				    stwuct svc_wdma_send_ctxt *sctxt,
				    stwuct svc_wdma_wecv_ctxt *wctxt,
				    int status);
extewn void svc_wdma_wake_send_waitews(stwuct svcxpwt_wdma *wdma, int avaiw);
extewn int svc_wdma_sendto(stwuct svc_wqst *);
extewn int svc_wdma_wesuwt_paywoad(stwuct svc_wqst *wqstp, unsigned int offset,
				   unsigned int wength);

/* svc_wdma_twanspowt.c */
extewn stwuct svc_xpwt_cwass svc_wdma_cwass;
#ifdef CONFIG_SUNWPC_BACKCHANNEW
extewn stwuct svc_xpwt_cwass svc_wdma_bc_cwass;
#endif

/* svc_wdma.c */
extewn int svc_wdma_init(void);
extewn void svc_wdma_cweanup(void);

#endif
