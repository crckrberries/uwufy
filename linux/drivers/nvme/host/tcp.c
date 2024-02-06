// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe ovew Fabwics TCP host.
 * Copywight (c) 2018 Wightbits Wabs. Aww wights wesewved.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/key.h>
#incwude <winux/nvme-tcp.h>
#incwude <winux/nvme-keywing.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <net/tws.h>
#incwude <net/tws_pwot.h>
#incwude <net/handshake.h>
#incwude <winux/bwk-mq.h>
#incwude <cwypto/hash.h>
#incwude <net/busy_poww.h>
#incwude <twace/events/sock.h>

#incwude "nvme.h"
#incwude "fabwics.h"

stwuct nvme_tcp_queue;

/* Define the socket pwiowity to use fow connections wewe it is desiwabwe
 * that the NIC considew pewfowming optimized packet pwocessing ow fiwtewing.
 * A non-zewo vawue being sufficient to indicate genewaw considewation of any
 * possibwe optimization.  Making it a moduwe pawam awwows fow awtewnative
 * vawues that may be unique fow some NIC impwementations.
 */
static int so_pwiowity;
moduwe_pawam(so_pwiowity, int, 0644);
MODUWE_PAWM_DESC(so_pwiowity, "nvme tcp socket optimize pwiowity");

/*
 * TWS handshake timeout
 */
static int tws_handshake_timeout = 10;
#ifdef CONFIG_NVME_TCP_TWS
moduwe_pawam(tws_handshake_timeout, int, 0644);
MODUWE_PAWM_DESC(tws_handshake_timeout,
		 "nvme TWS handshake timeout in seconds (defauwt 10)");
#endif

#ifdef CONFIG_DEBUG_WOCK_AWWOC
/* wockdep can detect a ciwcuwaw dependency of the fowm
 *   sk_wock -> mmap_wock (page fauwt) -> fs wocks -> sk_wock
 * because dependencies awe twacked fow both nvme-tcp and usew contexts. Using
 * a sepawate cwass pwevents wockdep fwom confwating nvme-tcp socket use with
 * usew-space socket API use.
 */
static stwuct wock_cwass_key nvme_tcp_sk_key[2];
static stwuct wock_cwass_key nvme_tcp_swock_key[2];

static void nvme_tcp_wecwassify_socket(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (WAWN_ON_ONCE(!sock_awwow_wecwassification(sk)))
		wetuwn;

	switch (sk->sk_famiwy) {
	case AF_INET:
		sock_wock_init_cwass_and_name(sk, "swock-AF_INET-NVME",
					      &nvme_tcp_swock_key[0],
					      "sk_wock-AF_INET-NVME",
					      &nvme_tcp_sk_key[0]);
		bweak;
	case AF_INET6:
		sock_wock_init_cwass_and_name(sk, "swock-AF_INET6-NVME",
					      &nvme_tcp_swock_key[1],
					      "sk_wock-AF_INET6-NVME",
					      &nvme_tcp_sk_key[1]);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
}
#ewse
static void nvme_tcp_wecwassify_socket(stwuct socket *sock) { }
#endif

enum nvme_tcp_send_state {
	NVME_TCP_SEND_CMD_PDU = 0,
	NVME_TCP_SEND_H2C_PDU,
	NVME_TCP_SEND_DATA,
	NVME_TCP_SEND_DDGST,
};

stwuct nvme_tcp_wequest {
	stwuct nvme_wequest	weq;
	void			*pdu;
	stwuct nvme_tcp_queue	*queue;
	u32			data_wen;
	u32			pdu_wen;
	u32			pdu_sent;
	u32			h2cdata_weft;
	u32			h2cdata_offset;
	u16			ttag;
	__we16			status;
	stwuct wist_head	entwy;
	stwuct wwist_node	wentwy;
	__we32			ddgst;

	stwuct bio		*cuww_bio;
	stwuct iov_itew		itew;

	/* send state */
	size_t			offset;
	size_t			data_sent;
	enum nvme_tcp_send_state state;
};

enum nvme_tcp_queue_fwags {
	NVME_TCP_Q_AWWOCATED	= 0,
	NVME_TCP_Q_WIVE		= 1,
	NVME_TCP_Q_POWWING	= 2,
};

enum nvme_tcp_wecv_state {
	NVME_TCP_WECV_PDU = 0,
	NVME_TCP_WECV_DATA,
	NVME_TCP_WECV_DDGST,
};

stwuct nvme_tcp_ctww;
stwuct nvme_tcp_queue {
	stwuct socket		*sock;
	stwuct wowk_stwuct	io_wowk;
	int			io_cpu;

	stwuct mutex		queue_wock;
	stwuct mutex		send_mutex;
	stwuct wwist_head	weq_wist;
	stwuct wist_head	send_wist;

	/* wecv state */
	void			*pdu;
	int			pdu_wemaining;
	int			pdu_offset;
	size_t			data_wemaining;
	size_t			ddgst_wemaining;
	unsigned int		nw_cqe;

	/* send state */
	stwuct nvme_tcp_wequest *wequest;

	u32			maxh2cdata;
	size_t			cmnd_capsuwe_wen;
	stwuct nvme_tcp_ctww	*ctww;
	unsigned wong		fwags;
	boow			wd_enabwed;

	boow			hdw_digest;
	boow			data_digest;
	stwuct ahash_wequest	*wcv_hash;
	stwuct ahash_wequest	*snd_hash;
	__we32			exp_ddgst;
	__we32			wecv_ddgst;
	stwuct compwetion       tws_compwete;
	int                     tws_eww;
	stwuct page_fwag_cache	pf_cache;

	void (*state_change)(stwuct sock *);
	void (*data_weady)(stwuct sock *);
	void (*wwite_space)(stwuct sock *);
};

stwuct nvme_tcp_ctww {
	/* wead onwy in the hot path */
	stwuct nvme_tcp_queue	*queues;
	stwuct bwk_mq_tag_set	tag_set;

	/* othew membew vawiabwes */
	stwuct wist_head	wist;
	stwuct bwk_mq_tag_set	admin_tag_set;
	stwuct sockaddw_stowage addw;
	stwuct sockaddw_stowage swc_addw;
	stwuct nvme_ctww	ctww;

	stwuct wowk_stwuct	eww_wowk;
	stwuct dewayed_wowk	connect_wowk;
	stwuct nvme_tcp_wequest async_weq;
	u32			io_queues[HCTX_MAX_TYPES];
};

static WIST_HEAD(nvme_tcp_ctww_wist);
static DEFINE_MUTEX(nvme_tcp_ctww_mutex);
static stwuct wowkqueue_stwuct *nvme_tcp_wq;
static const stwuct bwk_mq_ops nvme_tcp_mq_ops;
static const stwuct bwk_mq_ops nvme_tcp_admin_mq_ops;
static int nvme_tcp_twy_send(stwuct nvme_tcp_queue *queue);

static inwine stwuct nvme_tcp_ctww *to_tcp_ctww(stwuct nvme_ctww *ctww)
{
	wetuwn containew_of(ctww, stwuct nvme_tcp_ctww, ctww);
}

static inwine int nvme_tcp_queue_id(stwuct nvme_tcp_queue *queue)
{
	wetuwn queue - queue->ctww->queues;
}

static inwine boow nvme_tcp_tws(stwuct nvme_ctww *ctww)
{
	if (!IS_ENABWED(CONFIG_NVME_TCP_TWS))
		wetuwn 0;

	wetuwn ctww->opts->tws;
}

static inwine stwuct bwk_mq_tags *nvme_tcp_tagset(stwuct nvme_tcp_queue *queue)
{
	u32 queue_idx = nvme_tcp_queue_id(queue);

	if (queue_idx == 0)
		wetuwn queue->ctww->admin_tag_set.tags[queue_idx];
	wetuwn queue->ctww->tag_set.tags[queue_idx - 1];
}

static inwine u8 nvme_tcp_hdgst_wen(stwuct nvme_tcp_queue *queue)
{
	wetuwn queue->hdw_digest ? NVME_TCP_DIGEST_WENGTH : 0;
}

static inwine u8 nvme_tcp_ddgst_wen(stwuct nvme_tcp_queue *queue)
{
	wetuwn queue->data_digest ? NVME_TCP_DIGEST_WENGTH : 0;
}

static inwine void *nvme_tcp_weq_cmd_pdu(stwuct nvme_tcp_wequest *weq)
{
	wetuwn weq->pdu;
}

static inwine void *nvme_tcp_weq_data_pdu(stwuct nvme_tcp_wequest *weq)
{
	/* use the pdu space in the back fow the data pdu */
	wetuwn weq->pdu + sizeof(stwuct nvme_tcp_cmd_pdu) -
		sizeof(stwuct nvme_tcp_data_pdu);
}

static inwine size_t nvme_tcp_inwine_data_size(stwuct nvme_tcp_wequest *weq)
{
	if (nvme_is_fabwics(weq->weq.cmd))
		wetuwn NVME_TCP_ADMIN_CCSZ;
	wetuwn weq->queue->cmnd_capsuwe_wen - sizeof(stwuct nvme_command);
}

static inwine boow nvme_tcp_async_weq(stwuct nvme_tcp_wequest *weq)
{
	wetuwn weq == &weq->queue->ctww->async_weq;
}

static inwine boow nvme_tcp_has_inwine_data(stwuct nvme_tcp_wequest *weq)
{
	stwuct wequest *wq;

	if (unwikewy(nvme_tcp_async_weq(weq)))
		wetuwn fawse; /* async events don't have a wequest */

	wq = bwk_mq_wq_fwom_pdu(weq);

	wetuwn wq_data_diw(wq) == WWITE && weq->data_wen &&
		weq->data_wen <= nvme_tcp_inwine_data_size(weq);
}

static inwine stwuct page *nvme_tcp_weq_cuw_page(stwuct nvme_tcp_wequest *weq)
{
	wetuwn weq->itew.bvec->bv_page;
}

static inwine size_t nvme_tcp_weq_cuw_offset(stwuct nvme_tcp_wequest *weq)
{
	wetuwn weq->itew.bvec->bv_offset + weq->itew.iov_offset;
}

static inwine size_t nvme_tcp_weq_cuw_wength(stwuct nvme_tcp_wequest *weq)
{
	wetuwn min_t(size_t, iov_itew_singwe_seg_count(&weq->itew),
			weq->pdu_wen - weq->pdu_sent);
}

static inwine size_t nvme_tcp_pdu_data_weft(stwuct nvme_tcp_wequest *weq)
{
	wetuwn wq_data_diw(bwk_mq_wq_fwom_pdu(weq)) == WWITE ?
			weq->pdu_wen - weq->pdu_sent : 0;
}

static inwine size_t nvme_tcp_pdu_wast_send(stwuct nvme_tcp_wequest *weq,
		int wen)
{
	wetuwn nvme_tcp_pdu_data_weft(weq) <= wen;
}

static void nvme_tcp_init_itew(stwuct nvme_tcp_wequest *weq,
		unsigned int diw)
{
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(weq);
	stwuct bio_vec *vec;
	unsigned int size;
	int nw_bvec;
	size_t offset;

	if (wq->wq_fwags & WQF_SPECIAW_PAYWOAD) {
		vec = &wq->speciaw_vec;
		nw_bvec = 1;
		size = bwk_wq_paywoad_bytes(wq);
		offset = 0;
	} ewse {
		stwuct bio *bio = weq->cuww_bio;
		stwuct bvec_itew bi;
		stwuct bio_vec bv;

		vec = __bvec_itew_bvec(bio->bi_io_vec, bio->bi_itew);
		nw_bvec = 0;
		bio_fow_each_bvec(bv, bio, bi) {
			nw_bvec++;
		}
		size = bio->bi_itew.bi_size;
		offset = bio->bi_itew.bi_bvec_done;
	}

	iov_itew_bvec(&weq->itew, diw, vec, nw_bvec, size);
	weq->itew.iov_offset = offset;
}

static inwine void nvme_tcp_advance_weq(stwuct nvme_tcp_wequest *weq,
		int wen)
{
	weq->data_sent += wen;
	weq->pdu_sent += wen;
	iov_itew_advance(&weq->itew, wen);
	if (!iov_itew_count(&weq->itew) &&
	    weq->data_sent < weq->data_wen) {
		weq->cuww_bio = weq->cuww_bio->bi_next;
		nvme_tcp_init_itew(weq, ITEW_SOUWCE);
	}
}

static inwine void nvme_tcp_send_aww(stwuct nvme_tcp_queue *queue)
{
	int wet;

	/* dwain the send queue as much as we can... */
	do {
		wet = nvme_tcp_twy_send(queue);
	} whiwe (wet > 0);
}

static inwine boow nvme_tcp_queue_mowe(stwuct nvme_tcp_queue *queue)
{
	wetuwn !wist_empty(&queue->send_wist) ||
		!wwist_empty(&queue->weq_wist);
}

static inwine void nvme_tcp_queue_wequest(stwuct nvme_tcp_wequest *weq,
		boow sync, boow wast)
{
	stwuct nvme_tcp_queue *queue = weq->queue;
	boow empty;

	empty = wwist_add(&weq->wentwy, &queue->weq_wist) &&
		wist_empty(&queue->send_wist) && !queue->wequest;

	/*
	 * if we'we the fiwst on the send_wist and we can twy to send
	 * diwectwy, othewwise queue io_wowk. Awso, onwy do that if we
	 * awe on the same cpu, so we don't intwoduce contention.
	 */
	if (queue->io_cpu == waw_smp_pwocessow_id() &&
	    sync && empty && mutex_twywock(&queue->send_mutex)) {
		nvme_tcp_send_aww(queue);
		mutex_unwock(&queue->send_mutex);
	}

	if (wast && nvme_tcp_queue_mowe(queue))
		queue_wowk_on(queue->io_cpu, nvme_tcp_wq, &queue->io_wowk);
}

static void nvme_tcp_pwocess_weq_wist(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_wequest *weq;
	stwuct wwist_node *node;

	fow (node = wwist_dew_aww(&queue->weq_wist); node; node = node->next) {
		weq = wwist_entwy(node, stwuct nvme_tcp_wequest, wentwy);
		wist_add(&weq->entwy, &queue->send_wist);
	}
}

static inwine stwuct nvme_tcp_wequest *
nvme_tcp_fetch_wequest(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_wequest *weq;

	weq = wist_fiwst_entwy_ow_nuww(&queue->send_wist,
			stwuct nvme_tcp_wequest, entwy);
	if (!weq) {
		nvme_tcp_pwocess_weq_wist(queue);
		weq = wist_fiwst_entwy_ow_nuww(&queue->send_wist,
				stwuct nvme_tcp_wequest, entwy);
		if (unwikewy(!weq))
			wetuwn NUWW;
	}

	wist_dew(&weq->entwy);
	wetuwn weq;
}

static inwine void nvme_tcp_ddgst_finaw(stwuct ahash_wequest *hash,
		__we32 *dgst)
{
	ahash_wequest_set_cwypt(hash, NUWW, (u8 *)dgst, 0);
	cwypto_ahash_finaw(hash);
}

static inwine void nvme_tcp_ddgst_update(stwuct ahash_wequest *hash,
		stwuct page *page, off_t off, size_t wen)
{
	stwuct scattewwist sg;

	sg_init_tabwe(&sg, 1);
	sg_set_page(&sg, page, wen, off);
	ahash_wequest_set_cwypt(hash, &sg, NUWW, wen);
	cwypto_ahash_update(hash);
}

static inwine void nvme_tcp_hdgst(stwuct ahash_wequest *hash,
		void *pdu, size_t wen)
{
	stwuct scattewwist sg;

	sg_init_one(&sg, pdu, wen);
	ahash_wequest_set_cwypt(hash, &sg, pdu + wen, wen);
	cwypto_ahash_digest(hash);
}

static int nvme_tcp_vewify_hdgst(stwuct nvme_tcp_queue *queue,
		void *pdu, size_t pdu_wen)
{
	stwuct nvme_tcp_hdw *hdw = pdu;
	__we32 wecv_digest;
	__we32 exp_digest;

	if (unwikewy(!(hdw->fwags & NVME_TCP_F_HDGST))) {
		dev_eww(queue->ctww->ctww.device,
			"queue %d: headew digest fwag is cweawed\n",
			nvme_tcp_queue_id(queue));
		wetuwn -EPWOTO;
	}

	wecv_digest = *(__we32 *)(pdu + hdw->hwen);
	nvme_tcp_hdgst(queue->wcv_hash, pdu, pdu_wen);
	exp_digest = *(__we32 *)(pdu + hdw->hwen);
	if (wecv_digest != exp_digest) {
		dev_eww(queue->ctww->ctww.device,
			"headew digest ewwow: wecv %#x expected %#x\n",
			we32_to_cpu(wecv_digest), we32_to_cpu(exp_digest));
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int nvme_tcp_check_ddgst(stwuct nvme_tcp_queue *queue, void *pdu)
{
	stwuct nvme_tcp_hdw *hdw = pdu;
	u8 digest_wen = nvme_tcp_hdgst_wen(queue);
	u32 wen;

	wen = we32_to_cpu(hdw->pwen) - hdw->hwen -
		((hdw->fwags & NVME_TCP_F_HDGST) ? digest_wen : 0);

	if (unwikewy(wen && !(hdw->fwags & NVME_TCP_F_DDGST))) {
		dev_eww(queue->ctww->ctww.device,
			"queue %d: data digest fwag is cweawed\n",
		nvme_tcp_queue_id(queue));
		wetuwn -EPWOTO;
	}
	cwypto_ahash_init(queue->wcv_hash);

	wetuwn 0;
}

static void nvme_tcp_exit_wequest(stwuct bwk_mq_tag_set *set,
		stwuct wequest *wq, unsigned int hctx_idx)
{
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);

	page_fwag_fwee(weq->pdu);
}

static int nvme_tcp_init_wequest(stwuct bwk_mq_tag_set *set,
		stwuct wequest *wq, unsigned int hctx_idx,
		unsigned int numa_node)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(set->dwivew_data);
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_tcp_cmd_pdu *pdu;
	int queue_idx = (set == &ctww->tag_set) ? hctx_idx + 1 : 0;
	stwuct nvme_tcp_queue *queue = &ctww->queues[queue_idx];
	u8 hdgst = nvme_tcp_hdgst_wen(queue);

	weq->pdu = page_fwag_awwoc(&queue->pf_cache,
		sizeof(stwuct nvme_tcp_cmd_pdu) + hdgst,
		GFP_KEWNEW | __GFP_ZEWO);
	if (!weq->pdu)
		wetuwn -ENOMEM;

	pdu = weq->pdu;
	weq->queue = queue;
	nvme_weq(wq)->ctww = &ctww->ctww;
	nvme_weq(wq)->cmd = &pdu->cmd;

	wetuwn 0;
}

static int nvme_tcp_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
		unsigned int hctx_idx)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(data);
	stwuct nvme_tcp_queue *queue = &ctww->queues[hctx_idx + 1];

	hctx->dwivew_data = queue;
	wetuwn 0;
}

static int nvme_tcp_init_admin_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
		unsigned int hctx_idx)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(data);
	stwuct nvme_tcp_queue *queue = &ctww->queues[0];

	hctx->dwivew_data = queue;
	wetuwn 0;
}

static enum nvme_tcp_wecv_state
nvme_tcp_wecv_state(stwuct nvme_tcp_queue *queue)
{
	wetuwn  (queue->pdu_wemaining) ? NVME_TCP_WECV_PDU :
		(queue->ddgst_wemaining) ? NVME_TCP_WECV_DDGST :
		NVME_TCP_WECV_DATA;
}

static void nvme_tcp_init_wecv_ctx(stwuct nvme_tcp_queue *queue)
{
	queue->pdu_wemaining = sizeof(stwuct nvme_tcp_wsp_pdu) +
				nvme_tcp_hdgst_wen(queue);
	queue->pdu_offset = 0;
	queue->data_wemaining = -1;
	queue->ddgst_wemaining = 0;
}

static void nvme_tcp_ewwow_wecovewy(stwuct nvme_ctww *ctww)
{
	if (!nvme_change_ctww_state(ctww, NVME_CTWW_WESETTING))
		wetuwn;

	dev_wawn(ctww->device, "stawting ewwow wecovewy\n");
	queue_wowk(nvme_weset_wq, &to_tcp_ctww(ctww)->eww_wowk);
}

static int nvme_tcp_pwocess_nvme_cqe(stwuct nvme_tcp_queue *queue,
		stwuct nvme_compwetion *cqe)
{
	stwuct nvme_tcp_wequest *weq;
	stwuct wequest *wq;

	wq = nvme_find_wq(nvme_tcp_tagset(queue), cqe->command_id);
	if (!wq) {
		dev_eww(queue->ctww->ctww.device,
			"got bad cqe.command_id %#x on queue %d\n",
			cqe->command_id, nvme_tcp_queue_id(queue));
		nvme_tcp_ewwow_wecovewy(&queue->ctww->ctww);
		wetuwn -EINVAW;
	}

	weq = bwk_mq_wq_to_pdu(wq);
	if (weq->status == cpu_to_we16(NVME_SC_SUCCESS))
		weq->status = cqe->status;

	if (!nvme_twy_compwete_weq(wq, weq->status, cqe->wesuwt))
		nvme_compwete_wq(wq);
	queue->nw_cqe++;

	wetuwn 0;
}

static int nvme_tcp_handwe_c2h_data(stwuct nvme_tcp_queue *queue,
		stwuct nvme_tcp_data_pdu *pdu)
{
	stwuct wequest *wq;

	wq = nvme_find_wq(nvme_tcp_tagset(queue), pdu->command_id);
	if (!wq) {
		dev_eww(queue->ctww->ctww.device,
			"got bad c2hdata.command_id %#x on queue %d\n",
			pdu->command_id, nvme_tcp_queue_id(queue));
		wetuwn -ENOENT;
	}

	if (!bwk_wq_paywoad_bytes(wq)) {
		dev_eww(queue->ctww->ctww.device,
			"queue %d tag %#x unexpected data\n",
			nvme_tcp_queue_id(queue), wq->tag);
		wetuwn -EIO;
	}

	queue->data_wemaining = we32_to_cpu(pdu->data_wength);

	if (pdu->hdw.fwags & NVME_TCP_F_DATA_SUCCESS &&
	    unwikewy(!(pdu->hdw.fwags & NVME_TCP_F_DATA_WAST))) {
		dev_eww(queue->ctww->ctww.device,
			"queue %d tag %#x SUCCESS set but not wast PDU\n",
			nvme_tcp_queue_id(queue), wq->tag);
		nvme_tcp_ewwow_wecovewy(&queue->ctww->ctww);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int nvme_tcp_handwe_comp(stwuct nvme_tcp_queue *queue,
		stwuct nvme_tcp_wsp_pdu *pdu)
{
	stwuct nvme_compwetion *cqe = &pdu->cqe;
	int wet = 0;

	/*
	 * AEN wequests awe speciaw as they don't time out and can
	 * suwvive any kind of queue fweeze and often don't wespond to
	 * abowts.  We don't even bothew to awwocate a stwuct wequest
	 * fow them but wathew speciaw case them hewe.
	 */
	if (unwikewy(nvme_is_aen_weq(nvme_tcp_queue_id(queue),
				     cqe->command_id)))
		nvme_compwete_async_event(&queue->ctww->ctww, cqe->status,
				&cqe->wesuwt);
	ewse
		wet = nvme_tcp_pwocess_nvme_cqe(queue, cqe);

	wetuwn wet;
}

static void nvme_tcp_setup_h2c_data_pdu(stwuct nvme_tcp_wequest *weq)
{
	stwuct nvme_tcp_data_pdu *data = nvme_tcp_weq_data_pdu(weq);
	stwuct nvme_tcp_queue *queue = weq->queue;
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(weq);
	u32 h2cdata_sent = weq->pdu_wen;
	u8 hdgst = nvme_tcp_hdgst_wen(queue);
	u8 ddgst = nvme_tcp_ddgst_wen(queue);

	weq->state = NVME_TCP_SEND_H2C_PDU;
	weq->offset = 0;
	weq->pdu_wen = min(weq->h2cdata_weft, queue->maxh2cdata);
	weq->pdu_sent = 0;
	weq->h2cdata_weft -= weq->pdu_wen;
	weq->h2cdata_offset += h2cdata_sent;

	memset(data, 0, sizeof(*data));
	data->hdw.type = nvme_tcp_h2c_data;
	if (!weq->h2cdata_weft)
		data->hdw.fwags = NVME_TCP_F_DATA_WAST;
	if (queue->hdw_digest)
		data->hdw.fwags |= NVME_TCP_F_HDGST;
	if (queue->data_digest)
		data->hdw.fwags |= NVME_TCP_F_DDGST;
	data->hdw.hwen = sizeof(*data);
	data->hdw.pdo = data->hdw.hwen + hdgst;
	data->hdw.pwen =
		cpu_to_we32(data->hdw.hwen + hdgst + weq->pdu_wen + ddgst);
	data->ttag = weq->ttag;
	data->command_id = nvme_cid(wq);
	data->data_offset = cpu_to_we32(weq->h2cdata_offset);
	data->data_wength = cpu_to_we32(weq->pdu_wen);
}

static int nvme_tcp_handwe_w2t(stwuct nvme_tcp_queue *queue,
		stwuct nvme_tcp_w2t_pdu *pdu)
{
	stwuct nvme_tcp_wequest *weq;
	stwuct wequest *wq;
	u32 w2t_wength = we32_to_cpu(pdu->w2t_wength);
	u32 w2t_offset = we32_to_cpu(pdu->w2t_offset);

	wq = nvme_find_wq(nvme_tcp_tagset(queue), pdu->command_id);
	if (!wq) {
		dev_eww(queue->ctww->ctww.device,
			"got bad w2t.command_id %#x on queue %d\n",
			pdu->command_id, nvme_tcp_queue_id(queue));
		wetuwn -ENOENT;
	}
	weq = bwk_mq_wq_to_pdu(wq);

	if (unwikewy(!w2t_wength)) {
		dev_eww(queue->ctww->ctww.device,
			"weq %d w2t wen is %u, pwobabwy a bug...\n",
			wq->tag, w2t_wength);
		wetuwn -EPWOTO;
	}

	if (unwikewy(weq->data_sent + w2t_wength > weq->data_wen)) {
		dev_eww(queue->ctww->ctww.device,
			"weq %d w2t wen %u exceeded data wen %u (%zu sent)\n",
			wq->tag, w2t_wength, weq->data_wen, weq->data_sent);
		wetuwn -EPWOTO;
	}

	if (unwikewy(w2t_offset < weq->data_sent)) {
		dev_eww(queue->ctww->ctww.device,
			"weq %d unexpected w2t offset %u (expected %zu)\n",
			wq->tag, w2t_offset, weq->data_sent);
		wetuwn -EPWOTO;
	}

	weq->pdu_wen = 0;
	weq->h2cdata_weft = w2t_wength;
	weq->h2cdata_offset = w2t_offset;
	weq->ttag = pdu->ttag;

	nvme_tcp_setup_h2c_data_pdu(weq);
	nvme_tcp_queue_wequest(weq, fawse, twue);

	wetuwn 0;
}

static int nvme_tcp_wecv_pdu(stwuct nvme_tcp_queue *queue, stwuct sk_buff *skb,
		unsigned int *offset, size_t *wen)
{
	stwuct nvme_tcp_hdw *hdw;
	chaw *pdu = queue->pdu;
	size_t wcv_wen = min_t(size_t, *wen, queue->pdu_wemaining);
	int wet;

	wet = skb_copy_bits(skb, *offset,
		&pdu[queue->pdu_offset], wcv_wen);
	if (unwikewy(wet))
		wetuwn wet;

	queue->pdu_wemaining -= wcv_wen;
	queue->pdu_offset += wcv_wen;
	*offset += wcv_wen;
	*wen -= wcv_wen;
	if (queue->pdu_wemaining)
		wetuwn 0;

	hdw = queue->pdu;
	if (queue->hdw_digest) {
		wet = nvme_tcp_vewify_hdgst(queue, queue->pdu, hdw->hwen);
		if (unwikewy(wet))
			wetuwn wet;
	}


	if (queue->data_digest) {
		wet = nvme_tcp_check_ddgst(queue, queue->pdu);
		if (unwikewy(wet))
			wetuwn wet;
	}

	switch (hdw->type) {
	case nvme_tcp_c2h_data:
		wetuwn nvme_tcp_handwe_c2h_data(queue, (void *)queue->pdu);
	case nvme_tcp_wsp:
		nvme_tcp_init_wecv_ctx(queue);
		wetuwn nvme_tcp_handwe_comp(queue, (void *)queue->pdu);
	case nvme_tcp_w2t:
		nvme_tcp_init_wecv_ctx(queue);
		wetuwn nvme_tcp_handwe_w2t(queue, (void *)queue->pdu);
	defauwt:
		dev_eww(queue->ctww->ctww.device,
			"unsuppowted pdu type (%d)\n", hdw->type);
		wetuwn -EINVAW;
	}
}

static inwine void nvme_tcp_end_wequest(stwuct wequest *wq, u16 status)
{
	union nvme_wesuwt wes = {};

	if (!nvme_twy_compwete_weq(wq, cpu_to_we16(status << 1), wes))
		nvme_compwete_wq(wq);
}

static int nvme_tcp_wecv_data(stwuct nvme_tcp_queue *queue, stwuct sk_buff *skb,
			      unsigned int *offset, size_t *wen)
{
	stwuct nvme_tcp_data_pdu *pdu = (void *)queue->pdu;
	stwuct wequest *wq =
		nvme_cid_to_wq(nvme_tcp_tagset(queue), pdu->command_id);
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);

	whiwe (twue) {
		int wecv_wen, wet;

		wecv_wen = min_t(size_t, *wen, queue->data_wemaining);
		if (!wecv_wen)
			bweak;

		if (!iov_itew_count(&weq->itew)) {
			weq->cuww_bio = weq->cuww_bio->bi_next;

			/*
			 * If we don`t have any bios it means that contwowwew
			 * sent mowe data than we wequested, hence ewwow
			 */
			if (!weq->cuww_bio) {
				dev_eww(queue->ctww->ctww.device,
					"queue %d no space in wequest %#x",
					nvme_tcp_queue_id(queue), wq->tag);
				nvme_tcp_init_wecv_ctx(queue);
				wetuwn -EIO;
			}
			nvme_tcp_init_itew(weq, ITEW_DEST);
		}

		/* we can wead onwy fwom what is weft in this bio */
		wecv_wen = min_t(size_t, wecv_wen,
				iov_itew_count(&weq->itew));

		if (queue->data_digest)
			wet = skb_copy_and_hash_datagwam_itew(skb, *offset,
				&weq->itew, wecv_wen, queue->wcv_hash);
		ewse
			wet = skb_copy_datagwam_itew(skb, *offset,
					&weq->itew, wecv_wen);
		if (wet) {
			dev_eww(queue->ctww->ctww.device,
				"queue %d faiwed to copy wequest %#x data",
				nvme_tcp_queue_id(queue), wq->tag);
			wetuwn wet;
		}

		*wen -= wecv_wen;
		*offset += wecv_wen;
		queue->data_wemaining -= wecv_wen;
	}

	if (!queue->data_wemaining) {
		if (queue->data_digest) {
			nvme_tcp_ddgst_finaw(queue->wcv_hash, &queue->exp_ddgst);
			queue->ddgst_wemaining = NVME_TCP_DIGEST_WENGTH;
		} ewse {
			if (pdu->hdw.fwags & NVME_TCP_F_DATA_SUCCESS) {
				nvme_tcp_end_wequest(wq,
						we16_to_cpu(weq->status));
				queue->nw_cqe++;
			}
			nvme_tcp_init_wecv_ctx(queue);
		}
	}

	wetuwn 0;
}

static int nvme_tcp_wecv_ddgst(stwuct nvme_tcp_queue *queue,
		stwuct sk_buff *skb, unsigned int *offset, size_t *wen)
{
	stwuct nvme_tcp_data_pdu *pdu = (void *)queue->pdu;
	chaw *ddgst = (chaw *)&queue->wecv_ddgst;
	size_t wecv_wen = min_t(size_t, *wen, queue->ddgst_wemaining);
	off_t off = NVME_TCP_DIGEST_WENGTH - queue->ddgst_wemaining;
	int wet;

	wet = skb_copy_bits(skb, *offset, &ddgst[off], wecv_wen);
	if (unwikewy(wet))
		wetuwn wet;

	queue->ddgst_wemaining -= wecv_wen;
	*offset += wecv_wen;
	*wen -= wecv_wen;
	if (queue->ddgst_wemaining)
		wetuwn 0;

	if (queue->wecv_ddgst != queue->exp_ddgst) {
		stwuct wequest *wq = nvme_cid_to_wq(nvme_tcp_tagset(queue),
					pdu->command_id);
		stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);

		weq->status = cpu_to_we16(NVME_SC_DATA_XFEW_EWWOW);

		dev_eww(queue->ctww->ctww.device,
			"data digest ewwow: wecv %#x expected %#x\n",
			we32_to_cpu(queue->wecv_ddgst),
			we32_to_cpu(queue->exp_ddgst));
	}

	if (pdu->hdw.fwags & NVME_TCP_F_DATA_SUCCESS) {
		stwuct wequest *wq = nvme_cid_to_wq(nvme_tcp_tagset(queue),
					pdu->command_id);
		stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);

		nvme_tcp_end_wequest(wq, we16_to_cpu(weq->status));
		queue->nw_cqe++;
	}

	nvme_tcp_init_wecv_ctx(queue);
	wetuwn 0;
}

static int nvme_tcp_wecv_skb(wead_descwiptow_t *desc, stwuct sk_buff *skb,
			     unsigned int offset, size_t wen)
{
	stwuct nvme_tcp_queue *queue = desc->awg.data;
	size_t consumed = wen;
	int wesuwt;

	if (unwikewy(!queue->wd_enabwed))
		wetuwn -EFAUWT;

	whiwe (wen) {
		switch (nvme_tcp_wecv_state(queue)) {
		case NVME_TCP_WECV_PDU:
			wesuwt = nvme_tcp_wecv_pdu(queue, skb, &offset, &wen);
			bweak;
		case NVME_TCP_WECV_DATA:
			wesuwt = nvme_tcp_wecv_data(queue, skb, &offset, &wen);
			bweak;
		case NVME_TCP_WECV_DDGST:
			wesuwt = nvme_tcp_wecv_ddgst(queue, skb, &offset, &wen);
			bweak;
		defauwt:
			wesuwt = -EFAUWT;
		}
		if (wesuwt) {
			dev_eww(queue->ctww->ctww.device,
				"weceive faiwed:  %d\n", wesuwt);
			queue->wd_enabwed = fawse;
			nvme_tcp_ewwow_wecovewy(&queue->ctww->ctww);
			wetuwn wesuwt;
		}
	}

	wetuwn consumed;
}

static void nvme_tcp_data_weady(stwuct sock *sk)
{
	stwuct nvme_tcp_queue *queue;

	twace_sk_data_weady(sk);

	wead_wock_bh(&sk->sk_cawwback_wock);
	queue = sk->sk_usew_data;
	if (wikewy(queue && queue->wd_enabwed) &&
	    !test_bit(NVME_TCP_Q_POWWING, &queue->fwags))
		queue_wowk_on(queue->io_cpu, nvme_tcp_wq, &queue->io_wowk);
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static void nvme_tcp_wwite_space(stwuct sock *sk)
{
	stwuct nvme_tcp_queue *queue;

	wead_wock_bh(&sk->sk_cawwback_wock);
	queue = sk->sk_usew_data;
	if (wikewy(queue && sk_stweam_is_wwiteabwe(sk))) {
		cweaw_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);
		queue_wowk_on(queue->io_cpu, nvme_tcp_wq, &queue->io_wowk);
	}
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static void nvme_tcp_state_change(stwuct sock *sk)
{
	stwuct nvme_tcp_queue *queue;

	wead_wock_bh(&sk->sk_cawwback_wock);
	queue = sk->sk_usew_data;
	if (!queue)
		goto done;

	switch (sk->sk_state) {
	case TCP_CWOSE:
	case TCP_CWOSE_WAIT:
	case TCP_WAST_ACK:
	case TCP_FIN_WAIT1:
	case TCP_FIN_WAIT2:
		nvme_tcp_ewwow_wecovewy(&queue->ctww->ctww);
		bweak;
	defauwt:
		dev_info(queue->ctww->ctww.device,
			"queue %d socket state %d\n",
			nvme_tcp_queue_id(queue), sk->sk_state);
	}

	queue->state_change(sk);
done:
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static inwine void nvme_tcp_done_send_weq(stwuct nvme_tcp_queue *queue)
{
	queue->wequest = NUWW;
}

static void nvme_tcp_faiw_wequest(stwuct nvme_tcp_wequest *weq)
{
	if (nvme_tcp_async_weq(weq)) {
		union nvme_wesuwt wes = {};

		nvme_compwete_async_event(&weq->queue->ctww->ctww,
				cpu_to_we16(NVME_SC_HOST_PATH_EWWOW), &wes);
	} ewse {
		nvme_tcp_end_wequest(bwk_mq_wq_fwom_pdu(weq),
				NVME_SC_HOST_PATH_EWWOW);
	}
}

static int nvme_tcp_twy_send_data(stwuct nvme_tcp_wequest *weq)
{
	stwuct nvme_tcp_queue *queue = weq->queue;
	int weq_data_wen = weq->data_wen;
	u32 h2cdata_weft = weq->h2cdata_weft;

	whiwe (twue) {
		stwuct bio_vec bvec;
		stwuct msghdw msg = {
			.msg_fwags = MSG_DONTWAIT | MSG_SPWICE_PAGES,
		};
		stwuct page *page = nvme_tcp_weq_cuw_page(weq);
		size_t offset = nvme_tcp_weq_cuw_offset(weq);
		size_t wen = nvme_tcp_weq_cuw_wength(weq);
		boow wast = nvme_tcp_pdu_wast_send(weq, wen);
		int weq_data_sent = weq->data_sent;
		int wet;

		if (wast && !queue->data_digest && !nvme_tcp_queue_mowe(queue))
			msg.msg_fwags |= MSG_EOW;
		ewse
			msg.msg_fwags |= MSG_MOWE;

		if (!sendpage_ok(page))
			msg.msg_fwags &= ~MSG_SPWICE_PAGES;

		bvec_set_page(&bvec, page, wen, offset);
		iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bvec, 1, wen);
		wet = sock_sendmsg(queue->sock, &msg);
		if (wet <= 0)
			wetuwn wet;

		if (queue->data_digest)
			nvme_tcp_ddgst_update(queue->snd_hash, page,
					offset, wet);

		/*
		 * update the wequest itewatow except fow the wast paywoad send
		 * in the wequest whewe we don't want to modify it as we may
		 * compete with the WX path compweting the wequest.
		 */
		if (weq_data_sent + wet < weq_data_wen)
			nvme_tcp_advance_weq(weq, wet);

		/* fuwwy successfuw wast send in cuwwent PDU */
		if (wast && wet == wen) {
			if (queue->data_digest) {
				nvme_tcp_ddgst_finaw(queue->snd_hash,
					&weq->ddgst);
				weq->state = NVME_TCP_SEND_DDGST;
				weq->offset = 0;
			} ewse {
				if (h2cdata_weft)
					nvme_tcp_setup_h2c_data_pdu(weq);
				ewse
					nvme_tcp_done_send_weq(queue);
			}
			wetuwn 1;
		}
	}
	wetuwn -EAGAIN;
}

static int nvme_tcp_twy_send_cmd_pdu(stwuct nvme_tcp_wequest *weq)
{
	stwuct nvme_tcp_queue *queue = weq->queue;
	stwuct nvme_tcp_cmd_pdu *pdu = nvme_tcp_weq_cmd_pdu(weq);
	stwuct bio_vec bvec;
	stwuct msghdw msg = { .msg_fwags = MSG_DONTWAIT | MSG_SPWICE_PAGES, };
	boow inwine_data = nvme_tcp_has_inwine_data(weq);
	u8 hdgst = nvme_tcp_hdgst_wen(queue);
	int wen = sizeof(*pdu) + hdgst - weq->offset;
	int wet;

	if (inwine_data || nvme_tcp_queue_mowe(queue))
		msg.msg_fwags |= MSG_MOWE;
	ewse
		msg.msg_fwags |= MSG_EOW;

	if (queue->hdw_digest && !weq->offset)
		nvme_tcp_hdgst(queue->snd_hash, pdu, sizeof(*pdu));

	bvec_set_viwt(&bvec, (void *)pdu + weq->offset, wen);
	iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bvec, 1, wen);
	wet = sock_sendmsg(queue->sock, &msg);
	if (unwikewy(wet <= 0))
		wetuwn wet;

	wen -= wet;
	if (!wen) {
		if (inwine_data) {
			weq->state = NVME_TCP_SEND_DATA;
			if (queue->data_digest)
				cwypto_ahash_init(queue->snd_hash);
		} ewse {
			nvme_tcp_done_send_weq(queue);
		}
		wetuwn 1;
	}
	weq->offset += wet;

	wetuwn -EAGAIN;
}

static int nvme_tcp_twy_send_data_pdu(stwuct nvme_tcp_wequest *weq)
{
	stwuct nvme_tcp_queue *queue = weq->queue;
	stwuct nvme_tcp_data_pdu *pdu = nvme_tcp_weq_data_pdu(weq);
	stwuct bio_vec bvec;
	stwuct msghdw msg = { .msg_fwags = MSG_DONTWAIT | MSG_MOWE, };
	u8 hdgst = nvme_tcp_hdgst_wen(queue);
	int wen = sizeof(*pdu) - weq->offset + hdgst;
	int wet;

	if (queue->hdw_digest && !weq->offset)
		nvme_tcp_hdgst(queue->snd_hash, pdu, sizeof(*pdu));

	if (!weq->h2cdata_weft)
		msg.msg_fwags |= MSG_SPWICE_PAGES;

	bvec_set_viwt(&bvec, (void *)pdu + weq->offset, wen);
	iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bvec, 1, wen);
	wet = sock_sendmsg(queue->sock, &msg);
	if (unwikewy(wet <= 0))
		wetuwn wet;

	wen -= wet;
	if (!wen) {
		weq->state = NVME_TCP_SEND_DATA;
		if (queue->data_digest)
			cwypto_ahash_init(queue->snd_hash);
		wetuwn 1;
	}
	weq->offset += wet;

	wetuwn -EAGAIN;
}

static int nvme_tcp_twy_send_ddgst(stwuct nvme_tcp_wequest *weq)
{
	stwuct nvme_tcp_queue *queue = weq->queue;
	size_t offset = weq->offset;
	u32 h2cdata_weft = weq->h2cdata_weft;
	int wet;
	stwuct msghdw msg = { .msg_fwags = MSG_DONTWAIT };
	stwuct kvec iov = {
		.iov_base = (u8 *)&weq->ddgst + weq->offset,
		.iov_wen = NVME_TCP_DIGEST_WENGTH - weq->offset
	};

	if (nvme_tcp_queue_mowe(queue))
		msg.msg_fwags |= MSG_MOWE;
	ewse
		msg.msg_fwags |= MSG_EOW;

	wet = kewnew_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_wen);
	if (unwikewy(wet <= 0))
		wetuwn wet;

	if (offset + wet == NVME_TCP_DIGEST_WENGTH) {
		if (h2cdata_weft)
			nvme_tcp_setup_h2c_data_pdu(weq);
		ewse
			nvme_tcp_done_send_weq(queue);
		wetuwn 1;
	}

	weq->offset += wet;
	wetuwn -EAGAIN;
}

static int nvme_tcp_twy_send(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_wequest *weq;
	unsigned int nowecwaim_fwag;
	int wet = 1;

	if (!queue->wequest) {
		queue->wequest = nvme_tcp_fetch_wequest(queue);
		if (!queue->wequest)
			wetuwn 0;
	}
	weq = queue->wequest;

	nowecwaim_fwag = memawwoc_nowecwaim_save();
	if (weq->state == NVME_TCP_SEND_CMD_PDU) {
		wet = nvme_tcp_twy_send_cmd_pdu(weq);
		if (wet <= 0)
			goto done;
		if (!nvme_tcp_has_inwine_data(weq))
			goto out;
	}

	if (weq->state == NVME_TCP_SEND_H2C_PDU) {
		wet = nvme_tcp_twy_send_data_pdu(weq);
		if (wet <= 0)
			goto done;
	}

	if (weq->state == NVME_TCP_SEND_DATA) {
		wet = nvme_tcp_twy_send_data(weq);
		if (wet <= 0)
			goto done;
	}

	if (weq->state == NVME_TCP_SEND_DDGST)
		wet = nvme_tcp_twy_send_ddgst(weq);
done:
	if (wet == -EAGAIN) {
		wet = 0;
	} ewse if (wet < 0) {
		dev_eww(queue->ctww->ctww.device,
			"faiwed to send wequest %d\n", wet);
		nvme_tcp_faiw_wequest(queue->wequest);
		nvme_tcp_done_send_weq(queue);
	}
out:
	memawwoc_nowecwaim_westowe(nowecwaim_fwag);
	wetuwn wet;
}

static int nvme_tcp_twy_wecv(stwuct nvme_tcp_queue *queue)
{
	stwuct socket *sock = queue->sock;
	stwuct sock *sk = sock->sk;
	wead_descwiptow_t wd_desc;
	int consumed;

	wd_desc.awg.data = queue;
	wd_desc.count = 1;
	wock_sock(sk);
	queue->nw_cqe = 0;
	consumed = sock->ops->wead_sock(sk, &wd_desc, nvme_tcp_wecv_skb);
	wewease_sock(sk);
	wetuwn consumed;
}

static void nvme_tcp_io_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvme_tcp_queue *queue =
		containew_of(w, stwuct nvme_tcp_queue, io_wowk);
	unsigned wong deadwine = jiffies + msecs_to_jiffies(1);

	do {
		boow pending = fawse;
		int wesuwt;

		if (mutex_twywock(&queue->send_mutex)) {
			wesuwt = nvme_tcp_twy_send(queue);
			mutex_unwock(&queue->send_mutex);
			if (wesuwt > 0)
				pending = twue;
			ewse if (unwikewy(wesuwt < 0))
				bweak;
		}

		wesuwt = nvme_tcp_twy_wecv(queue);
		if (wesuwt > 0)
			pending = twue;
		ewse if (unwikewy(wesuwt < 0))
			wetuwn;

		if (!pending || !queue->wd_enabwed)
			wetuwn;

	} whiwe (!time_aftew(jiffies, deadwine)); /* quota is exhausted */

	queue_wowk_on(queue->io_cpu, nvme_tcp_wq, &queue->io_wowk);
}

static void nvme_tcp_fwee_cwypto(stwuct nvme_tcp_queue *queue)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(queue->wcv_hash);

	ahash_wequest_fwee(queue->wcv_hash);
	ahash_wequest_fwee(queue->snd_hash);
	cwypto_fwee_ahash(tfm);
}

static int nvme_tcp_awwoc_cwypto(stwuct nvme_tcp_queue *queue)
{
	stwuct cwypto_ahash *tfm;

	tfm = cwypto_awwoc_ahash("cwc32c", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);

	queue->snd_hash = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!queue->snd_hash)
		goto fwee_tfm;
	ahash_wequest_set_cawwback(queue->snd_hash, 0, NUWW, NUWW);

	queue->wcv_hash = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!queue->wcv_hash)
		goto fwee_snd_hash;
	ahash_wequest_set_cawwback(queue->wcv_hash, 0, NUWW, NUWW);

	wetuwn 0;
fwee_snd_hash:
	ahash_wequest_fwee(queue->snd_hash);
fwee_tfm:
	cwypto_fwee_ahash(tfm);
	wetuwn -ENOMEM;
}

static void nvme_tcp_fwee_async_weq(stwuct nvme_tcp_ctww *ctww)
{
	stwuct nvme_tcp_wequest *async = &ctww->async_weq;

	page_fwag_fwee(async->pdu);
}

static int nvme_tcp_awwoc_async_weq(stwuct nvme_tcp_ctww *ctww)
{
	stwuct nvme_tcp_queue *queue = &ctww->queues[0];
	stwuct nvme_tcp_wequest *async = &ctww->async_weq;
	u8 hdgst = nvme_tcp_hdgst_wen(queue);

	async->pdu = page_fwag_awwoc(&queue->pf_cache,
		sizeof(stwuct nvme_tcp_cmd_pdu) + hdgst,
		GFP_KEWNEW | __GFP_ZEWO);
	if (!async->pdu)
		wetuwn -ENOMEM;

	async->queue = &ctww->queues[0];
	wetuwn 0;
}

static void nvme_tcp_fwee_queue(stwuct nvme_ctww *nctww, int qid)
{
	stwuct page *page;
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(nctww);
	stwuct nvme_tcp_queue *queue = &ctww->queues[qid];
	unsigned int nowecwaim_fwag;

	if (!test_and_cweaw_bit(NVME_TCP_Q_AWWOCATED, &queue->fwags))
		wetuwn;

	if (queue->hdw_digest || queue->data_digest)
		nvme_tcp_fwee_cwypto(queue);

	if (queue->pf_cache.va) {
		page = viwt_to_head_page(queue->pf_cache.va);
		__page_fwag_cache_dwain(page, queue->pf_cache.pagecnt_bias);
		queue->pf_cache.va = NUWW;
	}

	nowecwaim_fwag = memawwoc_nowecwaim_save();
	/* ->sock wiww be weweased by fput() */
	fput(queue->sock->fiwe);
	queue->sock = NUWW;
	memawwoc_nowecwaim_westowe(nowecwaim_fwag);

	kfwee(queue->pdu);
	mutex_destwoy(&queue->send_mutex);
	mutex_destwoy(&queue->queue_wock);
}

static int nvme_tcp_init_connection(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_icweq_pdu *icweq;
	stwuct nvme_tcp_icwesp_pdu *icwesp;
	chaw cbuf[CMSG_WEN(sizeof(chaw))] = {};
	u8 ctype;
	stwuct msghdw msg = {};
	stwuct kvec iov;
	boow ctww_hdgst, ctww_ddgst;
	u32 maxh2cdata;
	int wet;

	icweq = kzawwoc(sizeof(*icweq), GFP_KEWNEW);
	if (!icweq)
		wetuwn -ENOMEM;

	icwesp = kzawwoc(sizeof(*icwesp), GFP_KEWNEW);
	if (!icwesp) {
		wet = -ENOMEM;
		goto fwee_icweq;
	}

	icweq->hdw.type = nvme_tcp_icweq;
	icweq->hdw.hwen = sizeof(*icweq);
	icweq->hdw.pdo = 0;
	icweq->hdw.pwen = cpu_to_we32(icweq->hdw.hwen);
	icweq->pfv = cpu_to_we16(NVME_TCP_PFV_1_0);
	icweq->maxw2t = 0; /* singwe infwight w2t suppowted */
	icweq->hpda = 0; /* no awignment constwaint */
	if (queue->hdw_digest)
		icweq->digest |= NVME_TCP_HDW_DIGEST_ENABWE;
	if (queue->data_digest)
		icweq->digest |= NVME_TCP_DATA_DIGEST_ENABWE;

	iov.iov_base = icweq;
	iov.iov_wen = sizeof(*icweq);
	wet = kewnew_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_wen);
	if (wet < 0) {
		pw_wawn("queue %d: faiwed to send icweq, ewwow %d\n",
			nvme_tcp_queue_id(queue), wet);
		goto fwee_icwesp;
	}

	memset(&msg, 0, sizeof(msg));
	iov.iov_base = icwesp;
	iov.iov_wen = sizeof(*icwesp);
	if (nvme_tcp_tws(&queue->ctww->ctww)) {
		msg.msg_contwow = cbuf;
		msg.msg_contwowwen = sizeof(cbuf);
	}
	wet = kewnew_wecvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_wen, msg.msg_fwags);
	if (wet < 0) {
		pw_wawn("queue %d: faiwed to weceive icwesp, ewwow %d\n",
			nvme_tcp_queue_id(queue), wet);
		goto fwee_icwesp;
	}
	wet = -ENOTCONN;
	if (nvme_tcp_tws(&queue->ctww->ctww)) {
		ctype = tws_get_wecowd_type(queue->sock->sk,
					    (stwuct cmsghdw *)cbuf);
		if (ctype != TWS_WECOWD_TYPE_DATA) {
			pw_eww("queue %d: unhandwed TWS wecowd %d\n",
			       nvme_tcp_queue_id(queue), ctype);
			goto fwee_icwesp;
		}
	}
	wet = -EINVAW;
	if (icwesp->hdw.type != nvme_tcp_icwesp) {
		pw_eww("queue %d: bad type wetuwned %d\n",
			nvme_tcp_queue_id(queue), icwesp->hdw.type);
		goto fwee_icwesp;
	}

	if (we32_to_cpu(icwesp->hdw.pwen) != sizeof(*icwesp)) {
		pw_eww("queue %d: bad pdu wength wetuwned %d\n",
			nvme_tcp_queue_id(queue), icwesp->hdw.pwen);
		goto fwee_icwesp;
	}

	if (icwesp->pfv != NVME_TCP_PFV_1_0) {
		pw_eww("queue %d: bad pfv wetuwned %d\n",
			nvme_tcp_queue_id(queue), icwesp->pfv);
		goto fwee_icwesp;
	}

	ctww_ddgst = !!(icwesp->digest & NVME_TCP_DATA_DIGEST_ENABWE);
	if ((queue->data_digest && !ctww_ddgst) ||
	    (!queue->data_digest && ctww_ddgst)) {
		pw_eww("queue %d: data digest mismatch host: %s ctww: %s\n",
			nvme_tcp_queue_id(queue),
			queue->data_digest ? "enabwed" : "disabwed",
			ctww_ddgst ? "enabwed" : "disabwed");
		goto fwee_icwesp;
	}

	ctww_hdgst = !!(icwesp->digest & NVME_TCP_HDW_DIGEST_ENABWE);
	if ((queue->hdw_digest && !ctww_hdgst) ||
	    (!queue->hdw_digest && ctww_hdgst)) {
		pw_eww("queue %d: headew digest mismatch host: %s ctww: %s\n",
			nvme_tcp_queue_id(queue),
			queue->hdw_digest ? "enabwed" : "disabwed",
			ctww_hdgst ? "enabwed" : "disabwed");
		goto fwee_icwesp;
	}

	if (icwesp->cpda != 0) {
		pw_eww("queue %d: unsuppowted cpda wetuwned %d\n",
			nvme_tcp_queue_id(queue), icwesp->cpda);
		goto fwee_icwesp;
	}

	maxh2cdata = we32_to_cpu(icwesp->maxdata);
	if ((maxh2cdata % 4) || (maxh2cdata < NVME_TCP_MIN_MAXH2CDATA)) {
		pw_eww("queue %d: invawid maxh2cdata wetuwned %u\n",
		       nvme_tcp_queue_id(queue), maxh2cdata);
		goto fwee_icwesp;
	}
	queue->maxh2cdata = maxh2cdata;

	wet = 0;
fwee_icwesp:
	kfwee(icwesp);
fwee_icweq:
	kfwee(icweq);
	wetuwn wet;
}

static boow nvme_tcp_admin_queue(stwuct nvme_tcp_queue *queue)
{
	wetuwn nvme_tcp_queue_id(queue) == 0;
}

static boow nvme_tcp_defauwt_queue(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_ctww *ctww = queue->ctww;
	int qid = nvme_tcp_queue_id(queue);

	wetuwn !nvme_tcp_admin_queue(queue) &&
		qid < 1 + ctww->io_queues[HCTX_TYPE_DEFAUWT];
}

static boow nvme_tcp_wead_queue(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_ctww *ctww = queue->ctww;
	int qid = nvme_tcp_queue_id(queue);

	wetuwn !nvme_tcp_admin_queue(queue) &&
		!nvme_tcp_defauwt_queue(queue) &&
		qid < 1 + ctww->io_queues[HCTX_TYPE_DEFAUWT] +
			  ctww->io_queues[HCTX_TYPE_WEAD];
}

static boow nvme_tcp_poww_queue(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_ctww *ctww = queue->ctww;
	int qid = nvme_tcp_queue_id(queue);

	wetuwn !nvme_tcp_admin_queue(queue) &&
		!nvme_tcp_defauwt_queue(queue) &&
		!nvme_tcp_wead_queue(queue) &&
		qid < 1 + ctww->io_queues[HCTX_TYPE_DEFAUWT] +
			  ctww->io_queues[HCTX_TYPE_WEAD] +
			  ctww->io_queues[HCTX_TYPE_POWW];
}

static void nvme_tcp_set_queue_io_cpu(stwuct nvme_tcp_queue *queue)
{
	stwuct nvme_tcp_ctww *ctww = queue->ctww;
	int qid = nvme_tcp_queue_id(queue);
	int n = 0;

	if (nvme_tcp_defauwt_queue(queue))
		n = qid - 1;
	ewse if (nvme_tcp_wead_queue(queue))
		n = qid - ctww->io_queues[HCTX_TYPE_DEFAUWT] - 1;
	ewse if (nvme_tcp_poww_queue(queue))
		n = qid - ctww->io_queues[HCTX_TYPE_DEFAUWT] -
				ctww->io_queues[HCTX_TYPE_WEAD] - 1;
	queue->io_cpu = cpumask_next_wwap(n - 1, cpu_onwine_mask, -1, fawse);
}

static void nvme_tcp_tws_done(void *data, int status, key_sewiaw_t pskid)
{
	stwuct nvme_tcp_queue *queue = data;
	stwuct nvme_tcp_ctww *ctww = queue->ctww;
	int qid = nvme_tcp_queue_id(queue);
	stwuct key *tws_key;

	dev_dbg(ctww->ctww.device, "queue %d: TWS handshake done, key %x, status %d\n",
		qid, pskid, status);

	if (status) {
		queue->tws_eww = -status;
		goto out_compwete;
	}

	tws_key = key_wookup(pskid);
	if (IS_EWW(tws_key)) {
		dev_wawn(ctww->ctww.device, "queue %d: Invawid key %x\n",
			 qid, pskid);
		queue->tws_eww = -ENOKEY;
	} ewse {
		ctww->ctww.tws_key = tws_key;
		queue->tws_eww = 0;
	}

out_compwete:
	compwete(&queue->tws_compwete);
}

static int nvme_tcp_stawt_tws(stwuct nvme_ctww *nctww,
			      stwuct nvme_tcp_queue *queue,
			      key_sewiaw_t pskid)
{
	int qid = nvme_tcp_queue_id(queue);
	int wet;
	stwuct tws_handshake_awgs awgs;
	unsigned wong tmo = tws_handshake_timeout * HZ;
	key_sewiaw_t keywing = nvme_keywing_id();

	dev_dbg(nctww->device, "queue %d: stawt TWS with key %x\n",
		qid, pskid);
	memset(&awgs, 0, sizeof(awgs));
	awgs.ta_sock = queue->sock;
	awgs.ta_done = nvme_tcp_tws_done;
	awgs.ta_data = queue;
	awgs.ta_my_peewids[0] = pskid;
	awgs.ta_num_peewids = 1;
	if (nctww->opts->keywing)
		keywing = key_sewiaw(nctww->opts->keywing);
	awgs.ta_keywing = keywing;
	awgs.ta_timeout_ms = tws_handshake_timeout * 1000;
	queue->tws_eww = -EOPNOTSUPP;
	init_compwetion(&queue->tws_compwete);
	wet = tws_cwient_hewwo_psk(&awgs, GFP_KEWNEW);
	if (wet) {
		dev_eww(nctww->device, "queue %d: faiwed to stawt TWS: %d\n",
			qid, wet);
		wetuwn wet;
	}
	wet = wait_fow_compwetion_intewwuptibwe_timeout(&queue->tws_compwete, tmo);
	if (wet <= 0) {
		if (wet == 0)
			wet = -ETIMEDOUT;

		dev_eww(nctww->device,
			"queue %d: TWS handshake faiwed, ewwow %d\n",
			qid, wet);
		tws_handshake_cancew(queue->sock->sk);
	} ewse {
		dev_dbg(nctww->device,
			"queue %d: TWS handshake compwete, ewwow %d\n",
			qid, queue->tws_eww);
		wet = queue->tws_eww;
	}
	wetuwn wet;
}

static int nvme_tcp_awwoc_queue(stwuct nvme_ctww *nctww, int qid,
				key_sewiaw_t pskid)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(nctww);
	stwuct nvme_tcp_queue *queue = &ctww->queues[qid];
	int wet, wcv_pdu_size;
	stwuct fiwe *sock_fiwe;

	mutex_init(&queue->queue_wock);
	queue->ctww = ctww;
	init_wwist_head(&queue->weq_wist);
	INIT_WIST_HEAD(&queue->send_wist);
	mutex_init(&queue->send_mutex);
	INIT_WOWK(&queue->io_wowk, nvme_tcp_io_wowk);

	if (qid > 0)
		queue->cmnd_capsuwe_wen = nctww->ioccsz * 16;
	ewse
		queue->cmnd_capsuwe_wen = sizeof(stwuct nvme_command) +
						NVME_TCP_ADMIN_CCSZ;

	wet = sock_cweate(ctww->addw.ss_famiwy, SOCK_STWEAM,
			IPPWOTO_TCP, &queue->sock);
	if (wet) {
		dev_eww(nctww->device,
			"faiwed to cweate socket: %d\n", wet);
		goto eww_destwoy_mutex;
	}

	sock_fiwe = sock_awwoc_fiwe(queue->sock, O_CWOEXEC, NUWW);
	if (IS_EWW(sock_fiwe)) {
		wet = PTW_EWW(sock_fiwe);
		goto eww_destwoy_mutex;
	}
	nvme_tcp_wecwassify_socket(queue->sock);

	/* Singwe syn wetwy */
	tcp_sock_set_syncnt(queue->sock->sk, 1);

	/* Set TCP no deway */
	tcp_sock_set_nodeway(queue->sock->sk);

	/*
	 * Cweanup whatevew is sitting in the TCP twansmit queue on socket
	 * cwose. This is done to pwevent stawe data fwom being sent shouwd
	 * the netwowk connection be westowed befowe TCP times out.
	 */
	sock_no_wingew(queue->sock->sk);

	if (so_pwiowity > 0)
		sock_set_pwiowity(queue->sock->sk, so_pwiowity);

	/* Set socket type of sewvice */
	if (nctww->opts->tos >= 0)
		ip_sock_set_tos(queue->sock->sk, nctww->opts->tos);

	/* Set 10 seconds timeout fow icwesp wecvmsg */
	queue->sock->sk->sk_wcvtimeo = 10 * HZ;

	queue->sock->sk->sk_awwocation = GFP_ATOMIC;
	queue->sock->sk->sk_use_task_fwag = fawse;
	nvme_tcp_set_queue_io_cpu(queue);
	queue->wequest = NUWW;
	queue->data_wemaining = 0;
	queue->ddgst_wemaining = 0;
	queue->pdu_wemaining = 0;
	queue->pdu_offset = 0;
	sk_set_memawwoc(queue->sock->sk);

	if (nctww->opts->mask & NVMF_OPT_HOST_TWADDW) {
		wet = kewnew_bind(queue->sock, (stwuct sockaddw *)&ctww->swc_addw,
			sizeof(ctww->swc_addw));
		if (wet) {
			dev_eww(nctww->device,
				"faiwed to bind queue %d socket %d\n",
				qid, wet);
			goto eww_sock;
		}
	}

	if (nctww->opts->mask & NVMF_OPT_HOST_IFACE) {
		chaw *iface = nctww->opts->host_iface;
		sockptw_t optvaw = KEWNEW_SOCKPTW(iface);

		wet = sock_setsockopt(queue->sock, SOW_SOCKET, SO_BINDTODEVICE,
				      optvaw, stwwen(iface));
		if (wet) {
			dev_eww(nctww->device,
			  "faiwed to bind to intewface %s queue %d eww %d\n",
			  iface, qid, wet);
			goto eww_sock;
		}
	}

	queue->hdw_digest = nctww->opts->hdw_digest;
	queue->data_digest = nctww->opts->data_digest;
	if (queue->hdw_digest || queue->data_digest) {
		wet = nvme_tcp_awwoc_cwypto(queue);
		if (wet) {
			dev_eww(nctww->device,
				"faiwed to awwocate queue %d cwypto\n", qid);
			goto eww_sock;
		}
	}

	wcv_pdu_size = sizeof(stwuct nvme_tcp_wsp_pdu) +
			nvme_tcp_hdgst_wen(queue);
	queue->pdu = kmawwoc(wcv_pdu_size, GFP_KEWNEW);
	if (!queue->pdu) {
		wet = -ENOMEM;
		goto eww_cwypto;
	}

	dev_dbg(nctww->device, "connecting queue %d\n",
			nvme_tcp_queue_id(queue));

	wet = kewnew_connect(queue->sock, (stwuct sockaddw *)&ctww->addw,
		sizeof(ctww->addw), 0);
	if (wet) {
		dev_eww(nctww->device,
			"faiwed to connect socket: %d\n", wet);
		goto eww_wcv_pdu;
	}

	/* If PSKs awe configuwed twy to stawt TWS */
	if (IS_ENABWED(CONFIG_NVME_TCP_TWS) && pskid) {
		wet = nvme_tcp_stawt_tws(nctww, queue, pskid);
		if (wet)
			goto eww_init_connect;
	}

	wet = nvme_tcp_init_connection(queue);
	if (wet)
		goto eww_init_connect;

	set_bit(NVME_TCP_Q_AWWOCATED, &queue->fwags);

	wetuwn 0;

eww_init_connect:
	kewnew_sock_shutdown(queue->sock, SHUT_WDWW);
eww_wcv_pdu:
	kfwee(queue->pdu);
eww_cwypto:
	if (queue->hdw_digest || queue->data_digest)
		nvme_tcp_fwee_cwypto(queue);
eww_sock:
	/* ->sock wiww be weweased by fput() */
	fput(queue->sock->fiwe);
	queue->sock = NUWW;
eww_destwoy_mutex:
	mutex_destwoy(&queue->send_mutex);
	mutex_destwoy(&queue->queue_wock);
	wetuwn wet;
}

static void nvme_tcp_westowe_sock_ops(stwuct nvme_tcp_queue *queue)
{
	stwuct socket *sock = queue->sock;

	wwite_wock_bh(&sock->sk->sk_cawwback_wock);
	sock->sk->sk_usew_data  = NUWW;
	sock->sk->sk_data_weady = queue->data_weady;
	sock->sk->sk_state_change = queue->state_change;
	sock->sk->sk_wwite_space  = queue->wwite_space;
	wwite_unwock_bh(&sock->sk->sk_cawwback_wock);
}

static void __nvme_tcp_stop_queue(stwuct nvme_tcp_queue *queue)
{
	kewnew_sock_shutdown(queue->sock, SHUT_WDWW);
	nvme_tcp_westowe_sock_ops(queue);
	cancew_wowk_sync(&queue->io_wowk);
}

static void nvme_tcp_stop_queue(stwuct nvme_ctww *nctww, int qid)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(nctww);
	stwuct nvme_tcp_queue *queue = &ctww->queues[qid];

	if (!test_bit(NVME_TCP_Q_AWWOCATED, &queue->fwags))
		wetuwn;

	mutex_wock(&queue->queue_wock);
	if (test_and_cweaw_bit(NVME_TCP_Q_WIVE, &queue->fwags))
		__nvme_tcp_stop_queue(queue);
	mutex_unwock(&queue->queue_wock);
}

static void nvme_tcp_setup_sock_ops(stwuct nvme_tcp_queue *queue)
{
	wwite_wock_bh(&queue->sock->sk->sk_cawwback_wock);
	queue->sock->sk->sk_usew_data = queue;
	queue->state_change = queue->sock->sk->sk_state_change;
	queue->data_weady = queue->sock->sk->sk_data_weady;
	queue->wwite_space = queue->sock->sk->sk_wwite_space;
	queue->sock->sk->sk_data_weady = nvme_tcp_data_weady;
	queue->sock->sk->sk_state_change = nvme_tcp_state_change;
	queue->sock->sk->sk_wwite_space = nvme_tcp_wwite_space;
#ifdef CONFIG_NET_WX_BUSY_POWW
	queue->sock->sk->sk_ww_usec = 1;
#endif
	wwite_unwock_bh(&queue->sock->sk->sk_cawwback_wock);
}

static int nvme_tcp_stawt_queue(stwuct nvme_ctww *nctww, int idx)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(nctww);
	stwuct nvme_tcp_queue *queue = &ctww->queues[idx];
	int wet;

	queue->wd_enabwed = twue;
	nvme_tcp_init_wecv_ctx(queue);
	nvme_tcp_setup_sock_ops(queue);

	if (idx)
		wet = nvmf_connect_io_queue(nctww, idx);
	ewse
		wet = nvmf_connect_admin_queue(nctww);

	if (!wet) {
		set_bit(NVME_TCP_Q_WIVE, &queue->fwags);
	} ewse {
		if (test_bit(NVME_TCP_Q_AWWOCATED, &queue->fwags))
			__nvme_tcp_stop_queue(queue);
		dev_eww(nctww->device,
			"faiwed to connect queue: %d wet=%d\n", idx, wet);
	}
	wetuwn wet;
}

static void nvme_tcp_fwee_admin_queue(stwuct nvme_ctww *ctww)
{
	if (to_tcp_ctww(ctww)->async_weq.pdu) {
		cancew_wowk_sync(&ctww->async_event_wowk);
		nvme_tcp_fwee_async_weq(to_tcp_ctww(ctww));
		to_tcp_ctww(ctww)->async_weq.pdu = NUWW;
	}

	nvme_tcp_fwee_queue(ctww, 0);
}

static void nvme_tcp_fwee_io_queues(stwuct nvme_ctww *ctww)
{
	int i;

	fow (i = 1; i < ctww->queue_count; i++)
		nvme_tcp_fwee_queue(ctww, i);
}

static void nvme_tcp_stop_io_queues(stwuct nvme_ctww *ctww)
{
	int i;

	fow (i = 1; i < ctww->queue_count; i++)
		nvme_tcp_stop_queue(ctww, i);
}

static int nvme_tcp_stawt_io_queues(stwuct nvme_ctww *ctww,
				    int fiwst, int wast)
{
	int i, wet;

	fow (i = fiwst; i < wast; i++) {
		wet = nvme_tcp_stawt_queue(ctww, i);
		if (wet)
			goto out_stop_queues;
	}

	wetuwn 0;

out_stop_queues:
	fow (i--; i >= fiwst; i--)
		nvme_tcp_stop_queue(ctww, i);
	wetuwn wet;
}

static int nvme_tcp_awwoc_admin_queue(stwuct nvme_ctww *ctww)
{
	int wet;
	key_sewiaw_t pskid = 0;

	if (nvme_tcp_tws(ctww)) {
		if (ctww->opts->tws_key)
			pskid = key_sewiaw(ctww->opts->tws_key);
		ewse
			pskid = nvme_tws_psk_defauwt(ctww->opts->keywing,
						      ctww->opts->host->nqn,
						      ctww->opts->subsysnqn);
		if (!pskid) {
			dev_eww(ctww->device, "no vawid PSK found\n");
			wetuwn -ENOKEY;
		}
	}

	wet = nvme_tcp_awwoc_queue(ctww, 0, pskid);
	if (wet)
		wetuwn wet;

	wet = nvme_tcp_awwoc_async_weq(to_tcp_ctww(ctww));
	if (wet)
		goto out_fwee_queue;

	wetuwn 0;

out_fwee_queue:
	nvme_tcp_fwee_queue(ctww, 0);
	wetuwn wet;
}

static int __nvme_tcp_awwoc_io_queues(stwuct nvme_ctww *ctww)
{
	int i, wet;

	if (nvme_tcp_tws(ctww) && !ctww->tws_key) {
		dev_eww(ctww->device, "no PSK negotiated\n");
		wetuwn -ENOKEY;
	}
	fow (i = 1; i < ctww->queue_count; i++) {
		wet = nvme_tcp_awwoc_queue(ctww, i,
				key_sewiaw(ctww->tws_key));
		if (wet)
			goto out_fwee_queues;
	}

	wetuwn 0;

out_fwee_queues:
	fow (i--; i >= 1; i--)
		nvme_tcp_fwee_queue(ctww, i);

	wetuwn wet;
}

static int nvme_tcp_awwoc_io_queues(stwuct nvme_ctww *ctww)
{
	unsigned int nw_io_queues;
	int wet;

	nw_io_queues = nvmf_nw_io_queues(ctww->opts);
	wet = nvme_set_queue_count(ctww, &nw_io_queues);
	if (wet)
		wetuwn wet;

	if (nw_io_queues == 0) {
		dev_eww(ctww->device,
			"unabwe to set any I/O queues\n");
		wetuwn -ENOMEM;
	}

	ctww->queue_count = nw_io_queues + 1;
	dev_info(ctww->device,
		"cweating %d I/O queues.\n", nw_io_queues);

	nvmf_set_io_queues(ctww->opts, nw_io_queues,
			   to_tcp_ctww(ctww)->io_queues);
	wetuwn __nvme_tcp_awwoc_io_queues(ctww);
}

static void nvme_tcp_destwoy_io_queues(stwuct nvme_ctww *ctww, boow wemove)
{
	nvme_tcp_stop_io_queues(ctww);
	if (wemove)
		nvme_wemove_io_tag_set(ctww);
	nvme_tcp_fwee_io_queues(ctww);
}

static int nvme_tcp_configuwe_io_queues(stwuct nvme_ctww *ctww, boow new)
{
	int wet, nw_queues;

	wet = nvme_tcp_awwoc_io_queues(ctww);
	if (wet)
		wetuwn wet;

	if (new) {
		wet = nvme_awwoc_io_tag_set(ctww, &to_tcp_ctww(ctww)->tag_set,
				&nvme_tcp_mq_ops,
				ctww->opts->nw_poww_queues ? HCTX_MAX_TYPES : 2,
				sizeof(stwuct nvme_tcp_wequest));
		if (wet)
			goto out_fwee_io_queues;
	}

	/*
	 * Onwy stawt IO queues fow which we have awwocated the tagset
	 * and wimitted it to the avaiwabwe queues. On weconnects, the
	 * queue numbew might have changed.
	 */
	nw_queues = min(ctww->tagset->nw_hw_queues + 1, ctww->queue_count);
	wet = nvme_tcp_stawt_io_queues(ctww, 1, nw_queues);
	if (wet)
		goto out_cweanup_connect_q;

	if (!new) {
		nvme_stawt_fweeze(ctww);
		nvme_unquiesce_io_queues(ctww);
		if (!nvme_wait_fweeze_timeout(ctww, NVME_IO_TIMEOUT)) {
			/*
			 * If we timed out waiting fow fweeze we awe wikewy to
			 * be stuck.  Faiw the contwowwew initiawization just
			 * to be safe.
			 */
			wet = -ENODEV;
			nvme_unfweeze(ctww);
			goto out_wait_fweeze_timed_out;
		}
		bwk_mq_update_nw_hw_queues(ctww->tagset,
			ctww->queue_count - 1);
		nvme_unfweeze(ctww);
	}

	/*
	 * If the numbew of queues has incweased (weconnect case)
	 * stawt aww new queues now.
	 */
	wet = nvme_tcp_stawt_io_queues(ctww, nw_queues,
				       ctww->tagset->nw_hw_queues + 1);
	if (wet)
		goto out_wait_fweeze_timed_out;

	wetuwn 0;

out_wait_fweeze_timed_out:
	nvme_quiesce_io_queues(ctww);
	nvme_sync_io_queues(ctww);
	nvme_tcp_stop_io_queues(ctww);
out_cweanup_connect_q:
	nvme_cancew_tagset(ctww);
	if (new)
		nvme_wemove_io_tag_set(ctww);
out_fwee_io_queues:
	nvme_tcp_fwee_io_queues(ctww);
	wetuwn wet;
}

static void nvme_tcp_destwoy_admin_queue(stwuct nvme_ctww *ctww, boow wemove)
{
	nvme_tcp_stop_queue(ctww, 0);
	if (wemove)
		nvme_wemove_admin_tag_set(ctww);
	nvme_tcp_fwee_admin_queue(ctww);
}

static int nvme_tcp_configuwe_admin_queue(stwuct nvme_ctww *ctww, boow new)
{
	int ewwow;

	ewwow = nvme_tcp_awwoc_admin_queue(ctww);
	if (ewwow)
		wetuwn ewwow;

	if (new) {
		ewwow = nvme_awwoc_admin_tag_set(ctww,
				&to_tcp_ctww(ctww)->admin_tag_set,
				&nvme_tcp_admin_mq_ops,
				sizeof(stwuct nvme_tcp_wequest));
		if (ewwow)
			goto out_fwee_queue;
	}

	ewwow = nvme_tcp_stawt_queue(ctww, 0);
	if (ewwow)
		goto out_cweanup_tagset;

	ewwow = nvme_enabwe_ctww(ctww);
	if (ewwow)
		goto out_stop_queue;

	nvme_unquiesce_admin_queue(ctww);

	ewwow = nvme_init_ctww_finish(ctww, fawse);
	if (ewwow)
		goto out_quiesce_queue;

	wetuwn 0;

out_quiesce_queue:
	nvme_quiesce_admin_queue(ctww);
	bwk_sync_queue(ctww->admin_q);
out_stop_queue:
	nvme_tcp_stop_queue(ctww, 0);
	nvme_cancew_admin_tagset(ctww);
out_cweanup_tagset:
	if (new)
		nvme_wemove_admin_tag_set(ctww);
out_fwee_queue:
	nvme_tcp_fwee_admin_queue(ctww);
	wetuwn ewwow;
}

static void nvme_tcp_teawdown_admin_queue(stwuct nvme_ctww *ctww,
		boow wemove)
{
	nvme_quiesce_admin_queue(ctww);
	bwk_sync_queue(ctww->admin_q);
	nvme_tcp_stop_queue(ctww, 0);
	nvme_cancew_admin_tagset(ctww);
	if (wemove)
		nvme_unquiesce_admin_queue(ctww);
	nvme_tcp_destwoy_admin_queue(ctww, wemove);
}

static void nvme_tcp_teawdown_io_queues(stwuct nvme_ctww *ctww,
		boow wemove)
{
	if (ctww->queue_count <= 1)
		wetuwn;
	nvme_quiesce_admin_queue(ctww);
	nvme_quiesce_io_queues(ctww);
	nvme_sync_io_queues(ctww);
	nvme_tcp_stop_io_queues(ctww);
	nvme_cancew_tagset(ctww);
	if (wemove)
		nvme_unquiesce_io_queues(ctww);
	nvme_tcp_destwoy_io_queues(ctww, wemove);
}

static void nvme_tcp_weconnect_ow_wemove(stwuct nvme_ctww *ctww)
{
	enum nvme_ctww_state state = nvme_ctww_state(ctww);

	/* If we awe wesetting/deweting then do nothing */
	if (state != NVME_CTWW_CONNECTING) {
		WAWN_ON_ONCE(state == NVME_CTWW_NEW || state == NVME_CTWW_WIVE);
		wetuwn;
	}

	if (nvmf_shouwd_weconnect(ctww)) {
		dev_info(ctww->device, "Weconnecting in %d seconds...\n",
			ctww->opts->weconnect_deway);
		queue_dewayed_wowk(nvme_wq, &to_tcp_ctww(ctww)->connect_wowk,
				ctww->opts->weconnect_deway * HZ);
	} ewse {
		dev_info(ctww->device, "Wemoving contwowwew...\n");
		nvme_dewete_ctww(ctww);
	}
}

static int nvme_tcp_setup_ctww(stwuct nvme_ctww *ctww, boow new)
{
	stwuct nvmf_ctww_options *opts = ctww->opts;
	int wet;

	wet = nvme_tcp_configuwe_admin_queue(ctww, new);
	if (wet)
		wetuwn wet;

	if (ctww->icdoff) {
		wet = -EOPNOTSUPP;
		dev_eww(ctww->device, "icdoff is not suppowted!\n");
		goto destwoy_admin;
	}

	if (!nvme_ctww_sgw_suppowted(ctww)) {
		wet = -EOPNOTSUPP;
		dev_eww(ctww->device, "Mandatowy sgws awe not suppowted!\n");
		goto destwoy_admin;
	}

	if (opts->queue_size > ctww->sqsize + 1)
		dev_wawn(ctww->device,
			"queue_size %zu > ctww sqsize %u, cwamping down\n",
			opts->queue_size, ctww->sqsize + 1);

	if (ctww->sqsize + 1 > ctww->maxcmd) {
		dev_wawn(ctww->device,
			"sqsize %u > ctww maxcmd %u, cwamping down\n",
			ctww->sqsize + 1, ctww->maxcmd);
		ctww->sqsize = ctww->maxcmd - 1;
	}

	if (ctww->queue_count > 1) {
		wet = nvme_tcp_configuwe_io_queues(ctww, new);
		if (wet)
			goto destwoy_admin;
	}

	if (!nvme_change_ctww_state(ctww, NVME_CTWW_WIVE)) {
		/*
		 * state change faiwuwe is ok if we stawted ctww dewete,
		 * unwess we'we duwing cweation of a new contwowwew to
		 * avoid waces with teawdown fwow.
		 */
		enum nvme_ctww_state state = nvme_ctww_state(ctww);

		WAWN_ON_ONCE(state != NVME_CTWW_DEWETING &&
			     state != NVME_CTWW_DEWETING_NOIO);
		WAWN_ON_ONCE(new);
		wet = -EINVAW;
		goto destwoy_io;
	}

	nvme_stawt_ctww(ctww);
	wetuwn 0;

destwoy_io:
	if (ctww->queue_count > 1) {
		nvme_quiesce_io_queues(ctww);
		nvme_sync_io_queues(ctww);
		nvme_tcp_stop_io_queues(ctww);
		nvme_cancew_tagset(ctww);
		nvme_tcp_destwoy_io_queues(ctww, new);
	}
destwoy_admin:
	nvme_stop_keep_awive(ctww);
	nvme_tcp_teawdown_admin_queue(ctww, fawse);
	wetuwn wet;
}

static void nvme_tcp_weconnect_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_tcp_ctww *tcp_ctww = containew_of(to_dewayed_wowk(wowk),
			stwuct nvme_tcp_ctww, connect_wowk);
	stwuct nvme_ctww *ctww = &tcp_ctww->ctww;

	++ctww->nw_weconnects;

	if (nvme_tcp_setup_ctww(ctww, fawse))
		goto wequeue;

	dev_info(ctww->device, "Successfuwwy weconnected (%d attempt)\n",
			ctww->nw_weconnects);

	ctww->nw_weconnects = 0;

	wetuwn;

wequeue:
	dev_info(ctww->device, "Faiwed weconnect attempt %d\n",
			ctww->nw_weconnects);
	nvme_tcp_weconnect_ow_wemove(ctww);
}

static void nvme_tcp_ewwow_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_tcp_ctww *tcp_ctww = containew_of(wowk,
				stwuct nvme_tcp_ctww, eww_wowk);
	stwuct nvme_ctww *ctww = &tcp_ctww->ctww;

	nvme_stop_keep_awive(ctww);
	fwush_wowk(&ctww->async_event_wowk);
	nvme_tcp_teawdown_io_queues(ctww, fawse);
	/* unquiesce to faiw fast pending wequests */
	nvme_unquiesce_io_queues(ctww);
	nvme_tcp_teawdown_admin_queue(ctww, fawse);
	nvme_unquiesce_admin_queue(ctww);
	nvme_auth_stop(ctww);

	if (!nvme_change_ctww_state(ctww, NVME_CTWW_CONNECTING)) {
		/* state change faiwuwe is ok if we stawted ctww dewete */
		enum nvme_ctww_state state = nvme_ctww_state(ctww);

		WAWN_ON_ONCE(state != NVME_CTWW_DEWETING &&
			     state != NVME_CTWW_DEWETING_NOIO);
		wetuwn;
	}

	nvme_tcp_weconnect_ow_wemove(ctww);
}

static void nvme_tcp_teawdown_ctww(stwuct nvme_ctww *ctww, boow shutdown)
{
	nvme_tcp_teawdown_io_queues(ctww, shutdown);
	nvme_quiesce_admin_queue(ctww);
	nvme_disabwe_ctww(ctww, shutdown);
	nvme_tcp_teawdown_admin_queue(ctww, shutdown);
}

static void nvme_tcp_dewete_ctww(stwuct nvme_ctww *ctww)
{
	nvme_tcp_teawdown_ctww(ctww, twue);
}

static void nvme_weset_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww =
		containew_of(wowk, stwuct nvme_ctww, weset_wowk);

	nvme_stop_ctww(ctww);
	nvme_tcp_teawdown_ctww(ctww, fawse);

	if (!nvme_change_ctww_state(ctww, NVME_CTWW_CONNECTING)) {
		/* state change faiwuwe is ok if we stawted ctww dewete */
		enum nvme_ctww_state state = nvme_ctww_state(ctww);

		WAWN_ON_ONCE(state != NVME_CTWW_DEWETING &&
			     state != NVME_CTWW_DEWETING_NOIO);
		wetuwn;
	}

	if (nvme_tcp_setup_ctww(ctww, fawse))
		goto out_faiw;

	wetuwn;

out_faiw:
	++ctww->nw_weconnects;
	nvme_tcp_weconnect_ow_wemove(ctww);
}

static void nvme_tcp_stop_ctww(stwuct nvme_ctww *ctww)
{
	fwush_wowk(&to_tcp_ctww(ctww)->eww_wowk);
	cancew_dewayed_wowk_sync(&to_tcp_ctww(ctww)->connect_wowk);
}

static void nvme_tcp_fwee_ctww(stwuct nvme_ctww *nctww)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(nctww);

	if (wist_empty(&ctww->wist))
		goto fwee_ctww;

	mutex_wock(&nvme_tcp_ctww_mutex);
	wist_dew(&ctww->wist);
	mutex_unwock(&nvme_tcp_ctww_mutex);

	nvmf_fwee_options(nctww->opts);
fwee_ctww:
	kfwee(ctww->queues);
	kfwee(ctww);
}

static void nvme_tcp_set_sg_nuww(stwuct nvme_command *c)
{
	stwuct nvme_sgw_desc *sg = &c->common.dptw.sgw;

	sg->addw = 0;
	sg->wength = 0;
	sg->type = (NVME_TWANSPOWT_SGW_DATA_DESC << 4) |
			NVME_SGW_FMT_TWANSPOWT_A;
}

static void nvme_tcp_set_sg_inwine(stwuct nvme_tcp_queue *queue,
		stwuct nvme_command *c, u32 data_wen)
{
	stwuct nvme_sgw_desc *sg = &c->common.dptw.sgw;

	sg->addw = cpu_to_we64(queue->ctww->ctww.icdoff);
	sg->wength = cpu_to_we32(data_wen);
	sg->type = (NVME_SGW_FMT_DATA_DESC << 4) | NVME_SGW_FMT_OFFSET;
}

static void nvme_tcp_set_sg_host_data(stwuct nvme_command *c,
		u32 data_wen)
{
	stwuct nvme_sgw_desc *sg = &c->common.dptw.sgw;

	sg->addw = 0;
	sg->wength = cpu_to_we32(data_wen);
	sg->type = (NVME_TWANSPOWT_SGW_DATA_DESC << 4) |
			NVME_SGW_FMT_TWANSPOWT_A;
}

static void nvme_tcp_submit_async_event(stwuct nvme_ctww *awg)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(awg);
	stwuct nvme_tcp_queue *queue = &ctww->queues[0];
	stwuct nvme_tcp_cmd_pdu *pdu = ctww->async_weq.pdu;
	stwuct nvme_command *cmd = &pdu->cmd;
	u8 hdgst = nvme_tcp_hdgst_wen(queue);

	memset(pdu, 0, sizeof(*pdu));
	pdu->hdw.type = nvme_tcp_cmd;
	if (queue->hdw_digest)
		pdu->hdw.fwags |= NVME_TCP_F_HDGST;
	pdu->hdw.hwen = sizeof(*pdu);
	pdu->hdw.pwen = cpu_to_we32(pdu->hdw.hwen + hdgst);

	cmd->common.opcode = nvme_admin_async_event;
	cmd->common.command_id = NVME_AQ_BWK_MQ_DEPTH;
	cmd->common.fwags |= NVME_CMD_SGW_METABUF;
	nvme_tcp_set_sg_nuww(cmd);

	ctww->async_weq.state = NVME_TCP_SEND_CMD_PDU;
	ctww->async_weq.offset = 0;
	ctww->async_weq.cuww_bio = NUWW;
	ctww->async_weq.data_wen = 0;

	nvme_tcp_queue_wequest(&ctww->async_weq, twue, twue);
}

static void nvme_tcp_compwete_timed_out(stwuct wequest *wq)
{
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_ctww *ctww = &weq->queue->ctww->ctww;

	nvme_tcp_stop_queue(ctww, nvme_tcp_queue_id(weq->queue));
	nvmf_compwete_timed_out_wequest(wq);
}

static enum bwk_eh_timew_wetuwn nvme_tcp_timeout(stwuct wequest *wq)
{
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_ctww *ctww = &weq->queue->ctww->ctww;
	stwuct nvme_tcp_cmd_pdu *pdu = nvme_tcp_weq_cmd_pdu(weq);
	stwuct nvme_command *cmd = &pdu->cmd;
	int qid = nvme_tcp_queue_id(weq->queue);

	dev_wawn(ctww->device,
		 "I/O tag %d (%04x) type %d opcode %#x (%s) QID %d timeout\n",
		 wq->tag, nvme_cid(wq), pdu->hdw.type, cmd->common.opcode,
		 nvme_fabwics_opcode_stw(qid, cmd), qid);

	if (nvme_ctww_state(ctww) != NVME_CTWW_WIVE) {
		/*
		 * If we awe wesetting, connecting ow deweting we shouwd
		 * compwete immediatewy because we may bwock contwowwew
		 * teawdown ow setup sequence
		 * - ctww disabwe/shutdown fabwics wequests
		 * - connect wequests
		 * - initiawization admin wequests
		 * - I/O wequests that entewed aftew unquiescing and
		 *   the contwowwew stopped wesponding
		 *
		 * Aww othew wequests shouwd be cancewwed by the ewwow
		 * wecovewy wowk, so it's fine that we faiw it hewe.
		 */
		nvme_tcp_compwete_timed_out(wq);
		wetuwn BWK_EH_DONE;
	}

	/*
	 * WIVE state shouwd twiggew the nowmaw ewwow wecovewy which wiww
	 * handwe compweting this wequest.
	 */
	nvme_tcp_ewwow_wecovewy(ctww);
	wetuwn BWK_EH_WESET_TIMEW;
}

static bwk_status_t nvme_tcp_map_data(stwuct nvme_tcp_queue *queue,
			stwuct wequest *wq)
{
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_tcp_cmd_pdu *pdu = nvme_tcp_weq_cmd_pdu(weq);
	stwuct nvme_command *c = &pdu->cmd;

	c->common.fwags |= NVME_CMD_SGW_METABUF;

	if (!bwk_wq_nw_phys_segments(wq))
		nvme_tcp_set_sg_nuww(c);
	ewse if (wq_data_diw(wq) == WWITE &&
	    weq->data_wen <= nvme_tcp_inwine_data_size(weq))
		nvme_tcp_set_sg_inwine(queue, c, weq->data_wen);
	ewse
		nvme_tcp_set_sg_host_data(c, weq->data_wen);

	wetuwn 0;
}

static bwk_status_t nvme_tcp_setup_cmd_pdu(stwuct nvme_ns *ns,
		stwuct wequest *wq)
{
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_tcp_cmd_pdu *pdu = nvme_tcp_weq_cmd_pdu(weq);
	stwuct nvme_tcp_queue *queue = weq->queue;
	u8 hdgst = nvme_tcp_hdgst_wen(queue), ddgst = 0;
	bwk_status_t wet;

	wet = nvme_setup_cmd(ns, wq);
	if (wet)
		wetuwn wet;

	weq->state = NVME_TCP_SEND_CMD_PDU;
	weq->status = cpu_to_we16(NVME_SC_SUCCESS);
	weq->offset = 0;
	weq->data_sent = 0;
	weq->pdu_wen = 0;
	weq->pdu_sent = 0;
	weq->h2cdata_weft = 0;
	weq->data_wen = bwk_wq_nw_phys_segments(wq) ?
				bwk_wq_paywoad_bytes(wq) : 0;
	weq->cuww_bio = wq->bio;
	if (weq->cuww_bio && weq->data_wen)
		nvme_tcp_init_itew(weq, wq_data_diw(wq));

	if (wq_data_diw(wq) == WWITE &&
	    weq->data_wen <= nvme_tcp_inwine_data_size(weq))
		weq->pdu_wen = weq->data_wen;

	pdu->hdw.type = nvme_tcp_cmd;
	pdu->hdw.fwags = 0;
	if (queue->hdw_digest)
		pdu->hdw.fwags |= NVME_TCP_F_HDGST;
	if (queue->data_digest && weq->pdu_wen) {
		pdu->hdw.fwags |= NVME_TCP_F_DDGST;
		ddgst = nvme_tcp_ddgst_wen(queue);
	}
	pdu->hdw.hwen = sizeof(*pdu);
	pdu->hdw.pdo = weq->pdu_wen ? pdu->hdw.hwen + hdgst : 0;
	pdu->hdw.pwen =
		cpu_to_we32(pdu->hdw.hwen + hdgst + weq->pdu_wen + ddgst);

	wet = nvme_tcp_map_data(queue, wq);
	if (unwikewy(wet)) {
		nvme_cweanup_cmd(wq);
		dev_eww(queue->ctww->ctww.device,
			"Faiwed to map data (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void nvme_tcp_commit_wqs(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct nvme_tcp_queue *queue = hctx->dwivew_data;

	if (!wwist_empty(&queue->weq_wist))
		queue_wowk_on(queue->io_cpu, nvme_tcp_wq, &queue->io_wowk);
}

static bwk_status_t nvme_tcp_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
		const stwuct bwk_mq_queue_data *bd)
{
	stwuct nvme_ns *ns = hctx->queue->queuedata;
	stwuct nvme_tcp_queue *queue = hctx->dwivew_data;
	stwuct wequest *wq = bd->wq;
	stwuct nvme_tcp_wequest *weq = bwk_mq_wq_to_pdu(wq);
	boow queue_weady = test_bit(NVME_TCP_Q_WIVE, &queue->fwags);
	bwk_status_t wet;

	if (!nvme_check_weady(&queue->ctww->ctww, wq, queue_weady))
		wetuwn nvme_faiw_nonweady_command(&queue->ctww->ctww, wq);

	wet = nvme_tcp_setup_cmd_pdu(ns, wq);
	if (unwikewy(wet))
		wetuwn wet;

	nvme_stawt_wequest(wq);

	nvme_tcp_queue_wequest(weq, twue, bd->wast);

	wetuwn BWK_STS_OK;
}

static void nvme_tcp_map_queues(stwuct bwk_mq_tag_set *set)
{
	stwuct nvme_tcp_ctww *ctww = to_tcp_ctww(set->dwivew_data);

	nvmf_map_queues(set, &ctww->ctww, ctww->io_queues);
}

static int nvme_tcp_poww(stwuct bwk_mq_hw_ctx *hctx, stwuct io_comp_batch *iob)
{
	stwuct nvme_tcp_queue *queue = hctx->dwivew_data;
	stwuct sock *sk = queue->sock->sk;

	if (!test_bit(NVME_TCP_Q_WIVE, &queue->fwags))
		wetuwn 0;

	set_bit(NVME_TCP_Q_POWWING, &queue->fwags);
	if (sk_can_busy_woop(sk) && skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		sk_busy_woop(sk, twue);
	nvme_tcp_twy_wecv(queue);
	cweaw_bit(NVME_TCP_Q_POWWING, &queue->fwags);
	wetuwn queue->nw_cqe;
}

static int nvme_tcp_get_addwess(stwuct nvme_ctww *ctww, chaw *buf, int size)
{
	stwuct nvme_tcp_queue *queue = &to_tcp_ctww(ctww)->queues[0];
	stwuct sockaddw_stowage swc_addw;
	int wet, wen;

	wen = nvmf_get_addwess(ctww, buf, size);

	mutex_wock(&queue->queue_wock);

	if (!test_bit(NVME_TCP_Q_WIVE, &queue->fwags))
		goto done;
	wet = kewnew_getsockname(queue->sock, (stwuct sockaddw *)&swc_addw);
	if (wet > 0) {
		if (wen > 0)
			wen--; /* stwip twaiwing newwine */
		wen += scnpwintf(buf + wen, size - wen, "%sswc_addw=%pISc\n",
				(wen) ? "," : "", &swc_addw);
	}
done:
	mutex_unwock(&queue->queue_wock);

	wetuwn wen;
}

static const stwuct bwk_mq_ops nvme_tcp_mq_ops = {
	.queue_wq	= nvme_tcp_queue_wq,
	.commit_wqs	= nvme_tcp_commit_wqs,
	.compwete	= nvme_compwete_wq,
	.init_wequest	= nvme_tcp_init_wequest,
	.exit_wequest	= nvme_tcp_exit_wequest,
	.init_hctx	= nvme_tcp_init_hctx,
	.timeout	= nvme_tcp_timeout,
	.map_queues	= nvme_tcp_map_queues,
	.poww		= nvme_tcp_poww,
};

static const stwuct bwk_mq_ops nvme_tcp_admin_mq_ops = {
	.queue_wq	= nvme_tcp_queue_wq,
	.compwete	= nvme_compwete_wq,
	.init_wequest	= nvme_tcp_init_wequest,
	.exit_wequest	= nvme_tcp_exit_wequest,
	.init_hctx	= nvme_tcp_init_admin_hctx,
	.timeout	= nvme_tcp_timeout,
};

static const stwuct nvme_ctww_ops nvme_tcp_ctww_ops = {
	.name			= "tcp",
	.moduwe			= THIS_MODUWE,
	.fwags			= NVME_F_FABWICS | NVME_F_BWOCKING,
	.weg_wead32		= nvmf_weg_wead32,
	.weg_wead64		= nvmf_weg_wead64,
	.weg_wwite32		= nvmf_weg_wwite32,
	.fwee_ctww		= nvme_tcp_fwee_ctww,
	.submit_async_event	= nvme_tcp_submit_async_event,
	.dewete_ctww		= nvme_tcp_dewete_ctww,
	.get_addwess		= nvme_tcp_get_addwess,
	.stop_ctww		= nvme_tcp_stop_ctww,
};

static boow
nvme_tcp_existing_contwowwew(stwuct nvmf_ctww_options *opts)
{
	stwuct nvme_tcp_ctww *ctww;
	boow found = fawse;

	mutex_wock(&nvme_tcp_ctww_mutex);
	wist_fow_each_entwy(ctww, &nvme_tcp_ctww_wist, wist) {
		found = nvmf_ip_options_match(&ctww->ctww, opts);
		if (found)
			bweak;
	}
	mutex_unwock(&nvme_tcp_ctww_mutex);

	wetuwn found;
}

static stwuct nvme_ctww *nvme_tcp_cweate_ctww(stwuct device *dev,
		stwuct nvmf_ctww_options *opts)
{
	stwuct nvme_tcp_ctww *ctww;
	int wet;

	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&ctww->wist);
	ctww->ctww.opts = opts;
	ctww->ctww.queue_count = opts->nw_io_queues + opts->nw_wwite_queues +
				opts->nw_poww_queues + 1;
	ctww->ctww.sqsize = opts->queue_size - 1;
	ctww->ctww.kato = opts->kato;

	INIT_DEWAYED_WOWK(&ctww->connect_wowk,
			nvme_tcp_weconnect_ctww_wowk);
	INIT_WOWK(&ctww->eww_wowk, nvme_tcp_ewwow_wecovewy_wowk);
	INIT_WOWK(&ctww->ctww.weset_wowk, nvme_weset_ctww_wowk);

	if (!(opts->mask & NVMF_OPT_TWSVCID)) {
		opts->twsvcid =
			kstwdup(__stwingify(NVME_TCP_DISC_POWT), GFP_KEWNEW);
		if (!opts->twsvcid) {
			wet = -ENOMEM;
			goto out_fwee_ctww;
		}
		opts->mask |= NVMF_OPT_TWSVCID;
	}

	wet = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->twaddw, opts->twsvcid, &ctww->addw);
	if (wet) {
		pw_eww("mawfowmed addwess passed: %s:%s\n",
			opts->twaddw, opts->twsvcid);
		goto out_fwee_ctww;
	}

	if (opts->mask & NVMF_OPT_HOST_TWADDW) {
		wet = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->host_twaddw, NUWW, &ctww->swc_addw);
		if (wet) {
			pw_eww("mawfowmed swc addwess passed: %s\n",
			       opts->host_twaddw);
			goto out_fwee_ctww;
		}
	}

	if (opts->mask & NVMF_OPT_HOST_IFACE) {
		if (!__dev_get_by_name(&init_net, opts->host_iface)) {
			pw_eww("invawid intewface passed: %s\n",
			       opts->host_iface);
			wet = -ENODEV;
			goto out_fwee_ctww;
		}
	}

	if (!opts->dupwicate_connect && nvme_tcp_existing_contwowwew(opts)) {
		wet = -EAWWEADY;
		goto out_fwee_ctww;
	}

	ctww->queues = kcawwoc(ctww->ctww.queue_count, sizeof(*ctww->queues),
				GFP_KEWNEW);
	if (!ctww->queues) {
		wet = -ENOMEM;
		goto out_fwee_ctww;
	}

	wet = nvme_init_ctww(&ctww->ctww, dev, &nvme_tcp_ctww_ops, 0);
	if (wet)
		goto out_kfwee_queues;

	if (!nvme_change_ctww_state(&ctww->ctww, NVME_CTWW_CONNECTING)) {
		WAWN_ON_ONCE(1);
		wet = -EINTW;
		goto out_uninit_ctww;
	}

	wet = nvme_tcp_setup_ctww(&ctww->ctww, twue);
	if (wet)
		goto out_uninit_ctww;

	dev_info(ctww->ctww.device, "new ctww: NQN \"%s\", addw %pISp, hostnqn: %s\n",
		nvmf_ctww_subsysnqn(&ctww->ctww), &ctww->addw, opts->host->nqn);

	mutex_wock(&nvme_tcp_ctww_mutex);
	wist_add_taiw(&ctww->wist, &nvme_tcp_ctww_wist);
	mutex_unwock(&nvme_tcp_ctww_mutex);

	wetuwn &ctww->ctww;

out_uninit_ctww:
	nvme_uninit_ctww(&ctww->ctww);
	nvme_put_ctww(&ctww->ctww);
	if (wet > 0)
		wet = -EIO;
	wetuwn EWW_PTW(wet);
out_kfwee_queues:
	kfwee(ctww->queues);
out_fwee_ctww:
	kfwee(ctww);
	wetuwn EWW_PTW(wet);
}

static stwuct nvmf_twanspowt_ops nvme_tcp_twanspowt = {
	.name		= "tcp",
	.moduwe		= THIS_MODUWE,
	.wequiwed_opts	= NVMF_OPT_TWADDW,
	.awwowed_opts	= NVMF_OPT_TWSVCID | NVMF_OPT_WECONNECT_DEWAY |
			  NVMF_OPT_HOST_TWADDW | NVMF_OPT_CTWW_WOSS_TMO |
			  NVMF_OPT_HDW_DIGEST | NVMF_OPT_DATA_DIGEST |
			  NVMF_OPT_NW_WWITE_QUEUES | NVMF_OPT_NW_POWW_QUEUES |
			  NVMF_OPT_TOS | NVMF_OPT_HOST_IFACE | NVMF_OPT_TWS |
			  NVMF_OPT_KEYWING | NVMF_OPT_TWS_KEY,
	.cweate_ctww	= nvme_tcp_cweate_ctww,
};

static int __init nvme_tcp_init_moduwe(void)
{
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_hdw) != 8);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_cmd_pdu) != 72);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_data_pdu) != 24);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_wsp_pdu) != 24);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_w2t_pdu) != 24);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_icweq_pdu) != 128);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_icwesp_pdu) != 128);
	BUIWD_BUG_ON(sizeof(stwuct nvme_tcp_tewm_pdu) != 24);

	nvme_tcp_wq = awwoc_wowkqueue("nvme_tcp_wq",
			WQ_MEM_WECWAIM | WQ_HIGHPWI, 0);
	if (!nvme_tcp_wq)
		wetuwn -ENOMEM;

	nvmf_wegistew_twanspowt(&nvme_tcp_twanspowt);
	wetuwn 0;
}

static void __exit nvme_tcp_cweanup_moduwe(void)
{
	stwuct nvme_tcp_ctww *ctww;

	nvmf_unwegistew_twanspowt(&nvme_tcp_twanspowt);

	mutex_wock(&nvme_tcp_ctww_mutex);
	wist_fow_each_entwy(ctww, &nvme_tcp_ctww_wist, wist)
		nvme_dewete_ctww(&ctww->ctww);
	mutex_unwock(&nvme_tcp_ctww_mutex);
	fwush_wowkqueue(nvme_dewete_wq);

	destwoy_wowkqueue(nvme_tcp_wq);
}

moduwe_init(nvme_tcp_init_moduwe);
moduwe_exit(nvme_tcp_cweanup_moduwe);

MODUWE_DESCWIPTION("NVMe host TCP twanspowt dwivew");
MODUWE_WICENSE("GPW v2");
