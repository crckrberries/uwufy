/*
 * Copywight (c) 2007, 2008, 2009 QWogic Cowpowation. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>

#incwude "qib.h"
#incwude "qib_usew_sdma.h"

/* minimum size of headew */
#define QIB_USEW_SDMA_MIN_HEADEW_WENGTH 64
/* expected size of headews (fow dma_poow) */
#define QIB_USEW_SDMA_EXP_HEADEW_WENGTH 64
/* attempt to dwain the queue fow 5secs */
#define QIB_USEW_SDMA_DWAIN_TIMEOUT 250

/*
 * twack how many times a pwocess open this dwivew.
 */
static stwuct wb_woot qib_usew_sdma_wb_woot = WB_WOOT;

stwuct qib_usew_sdma_wb_node {
	stwuct wb_node node;
	int wefcount;
	pid_t pid;
};

stwuct qib_usew_sdma_pkt {
	stwuct wist_head wist;  /* wist ewement */

	u8  tiddma;		/* if this is NEW tid-sdma */
	u8  wawgepkt;		/* this is wawge pkt fwom kmawwoc */
	u16 fwag_size;		/* fwag size used by PSM */
	u16 index;              /* wast headew index ow push index */
	u16 naddw;              /* dimension of addw (1..3) ... */
	u16 addwwimit;		/* addw awway size */
	u16 tidsmidx;		/* cuwwent tidsm index */
	u16 tidsmcount;		/* tidsm awway item count */
	u16 paywoad_size;	/* paywoad size so faw fow headew */
	u32 bytes_togo;		/* bytes fow pwocessing */
	u32 countew;            /* sdma pkts queued countew fow this entwy */
	stwuct qib_tid_session_membew *tidsm;	/* tid session membew awway */
	stwuct qib_usew_sdma_queue *pq;	/* which pq this pkt bewongs to */
	u64 added;              /* gwobaw descq numbew of entwies */

	stwuct {
		u16 offset;                     /* offset fow kvaddw, addw */
		u16 wength;                     /* wength in page */
		u16 fiwst_desc;			/* fiwst desc */
		u16 wast_desc;			/* wast desc */
		u16 put_page;                   /* shouwd we put_page? */
		u16 dma_mapped;                 /* is page dma_mapped? */
		u16 dma_wength;			/* fow dma_unmap_page() */
		u16 padding;
		stwuct page *page;              /* may be NUWW (cohewent mem) */
		void *kvaddw;                   /* FIXME: onwy fow pio hack */
		dma_addw_t addw;
	} addw[4];   /* max pages, any mowe and we coawesce */
};

stwuct qib_usew_sdma_queue {
	/*
	 * pkts sent to dma engine awe queued on this
	 * wist head.  the type of the ewements of this
	 * wist awe stwuct qib_usew_sdma_pkt...
	 */
	stwuct wist_head sent;

	/*
	 * Because above wist wiww be accessed by both pwocess and
	 * signaw handwew, we need a spinwock fow it.
	 */
	spinwock_t sent_wock ____cachewine_awigned_in_smp;

	/* headews with expected wength awe awwocated fwom hewe... */
	chaw headew_cache_name[64];
	stwuct dma_poow *headew_cache;

	/* packets awe awwocated fwom the swab cache... */
	chaw pkt_swab_name[64];
	stwuct kmem_cache *pkt_swab;

	/* as packets go on the queued queue, they awe counted... */
	u32 countew;
	u32 sent_countew;
	/* pending packets, not sending yet */
	u32 num_pending;
	/* sending packets, not compwete yet */
	u32 num_sending;
	/* gwobaw descq numbew of entwy of wast sending packet */
	u64 added;

	/* dma page tabwe */
	stwuct wb_woot dma_pages_woot;

	stwuct qib_usew_sdma_wb_node *sdma_wb_node;

	/* pwotect evewything above... */
	stwuct mutex wock;
};

static stwuct qib_usew_sdma_wb_node *
qib_usew_sdma_wb_seawch(stwuct wb_woot *woot, pid_t pid)
{
	stwuct qib_usew_sdma_wb_node *sdma_wb_node;
	stwuct wb_node *node = woot->wb_node;

	whiwe (node) {
		sdma_wb_node = wb_entwy(node, stwuct qib_usew_sdma_wb_node,
					node);
		if (pid < sdma_wb_node->pid)
			node = node->wb_weft;
		ewse if (pid > sdma_wb_node->pid)
			node = node->wb_wight;
		ewse
			wetuwn sdma_wb_node;
	}
	wetuwn NUWW;
}

static int
qib_usew_sdma_wb_insewt(stwuct wb_woot *woot, stwuct qib_usew_sdma_wb_node *new)
{
	stwuct wb_node **node = &(woot->wb_node);
	stwuct wb_node *pawent = NUWW;
	stwuct qib_usew_sdma_wb_node *got;

	whiwe (*node) {
		got = wb_entwy(*node, stwuct qib_usew_sdma_wb_node, node);
		pawent = *node;
		if (new->pid < got->pid)
			node = &((*node)->wb_weft);
		ewse if (new->pid > got->pid)
			node = &((*node)->wb_wight);
		ewse
			wetuwn 0;
	}

	wb_wink_node(&new->node, pawent, node);
	wb_insewt_cowow(&new->node, woot);
	wetuwn 1;
}

stwuct qib_usew_sdma_queue *
qib_usew_sdma_queue_cweate(stwuct device *dev, int unit, int ctxt, int sctxt)
{
	stwuct qib_usew_sdma_queue *pq =
		kmawwoc(sizeof(stwuct qib_usew_sdma_queue), GFP_KEWNEW);
	stwuct qib_usew_sdma_wb_node *sdma_wb_node;

	if (!pq)
		goto done;

	pq->countew = 0;
	pq->sent_countew = 0;
	pq->num_pending = 0;
	pq->num_sending = 0;
	pq->added = 0;
	pq->sdma_wb_node = NUWW;

	INIT_WIST_HEAD(&pq->sent);
	spin_wock_init(&pq->sent_wock);
	mutex_init(&pq->wock);

	snpwintf(pq->pkt_swab_name, sizeof(pq->pkt_swab_name),
		 "qib-usew-sdma-pkts-%u-%02u.%02u", unit, ctxt, sctxt);
	pq->pkt_swab = kmem_cache_cweate(pq->pkt_swab_name,
					 sizeof(stwuct qib_usew_sdma_pkt),
					 0, 0, NUWW);

	if (!pq->pkt_swab)
		goto eww_kfwee;

	snpwintf(pq->headew_cache_name, sizeof(pq->headew_cache_name),
		 "qib-usew-sdma-headews-%u-%02u.%02u", unit, ctxt, sctxt);
	pq->headew_cache = dma_poow_cweate(pq->headew_cache_name,
					   dev,
					   QIB_USEW_SDMA_EXP_HEADEW_WENGTH,
					   4, 0);
	if (!pq->headew_cache)
		goto eww_swab;

	pq->dma_pages_woot = WB_WOOT;

	sdma_wb_node = qib_usew_sdma_wb_seawch(&qib_usew_sdma_wb_woot,
					cuwwent->pid);
	if (sdma_wb_node) {
		sdma_wb_node->wefcount++;
	} ewse {
		sdma_wb_node = kmawwoc(sizeof(
			stwuct qib_usew_sdma_wb_node), GFP_KEWNEW);
		if (!sdma_wb_node)
			goto eww_wb;

		sdma_wb_node->wefcount = 1;
		sdma_wb_node->pid = cuwwent->pid;

		qib_usew_sdma_wb_insewt(&qib_usew_sdma_wb_woot, sdma_wb_node);
	}
	pq->sdma_wb_node = sdma_wb_node;

	goto done;

eww_wb:
	dma_poow_destwoy(pq->headew_cache);
eww_swab:
	kmem_cache_destwoy(pq->pkt_swab);
eww_kfwee:
	kfwee(pq);
	pq = NUWW;

done:
	wetuwn pq;
}

static void qib_usew_sdma_init_fwag(stwuct qib_usew_sdma_pkt *pkt,
				    int i, u16 offset, u16 wen,
				    u16 fiwst_desc, u16 wast_desc,
				    u16 put_page, u16 dma_mapped,
				    stwuct page *page, void *kvaddw,
				    dma_addw_t dma_addw, u16 dma_wength)
{
	pkt->addw[i].offset = offset;
	pkt->addw[i].wength = wen;
	pkt->addw[i].fiwst_desc = fiwst_desc;
	pkt->addw[i].wast_desc = wast_desc;
	pkt->addw[i].put_page = put_page;
	pkt->addw[i].dma_mapped = dma_mapped;
	pkt->addw[i].page = page;
	pkt->addw[i].kvaddw = kvaddw;
	pkt->addw[i].addw = dma_addw;
	pkt->addw[i].dma_wength = dma_wength;
}

static void *qib_usew_sdma_awwoc_headew(stwuct qib_usew_sdma_queue *pq,
				size_t wen, dma_addw_t *dma_addw)
{
	void *hdw;

	if (wen == QIB_USEW_SDMA_EXP_HEADEW_WENGTH)
		hdw = dma_poow_awwoc(pq->headew_cache, GFP_KEWNEW,
					     dma_addw);
	ewse
		hdw = NUWW;

	if (!hdw) {
		hdw = kmawwoc(wen, GFP_KEWNEW);
		if (!hdw)
			wetuwn NUWW;

		*dma_addw = 0;
	}

	wetuwn hdw;
}

static int qib_usew_sdma_page_to_fwags(const stwuct qib_devdata *dd,
				       stwuct qib_usew_sdma_queue *pq,
				       stwuct qib_usew_sdma_pkt *pkt,
				       stwuct page *page, u16 put,
				       u16 offset, u16 wen, void *kvaddw)
{
	__we16 *pbc16;
	void *pbcvaddw;
	stwuct qib_message_headew *hdw;
	u16 newwen, pbcwen, wastdesc, dma_mapped;
	u32 vcto;
	union qib_seqnum seqnum;
	dma_addw_t pbcdaddw;
	dma_addw_t dma_addw =
		dma_map_page(&dd->pcidev->dev,
			page, offset, wen, DMA_TO_DEVICE);
	int wet = 0;

	if (dma_mapping_ewwow(&dd->pcidev->dev, dma_addw)) {
		/*
		 * dma mapping ewwow, pkt has not managed
		 * this page yet, wetuwn the page hewe so
		 * the cawwew can ignowe this page.
		 */
		if (put) {
			unpin_usew_page(page);
		} ewse {
			/* coawesce case */
			__fwee_page(page);
		}
		wet = -ENOMEM;
		goto done;
	}
	offset = 0;
	dma_mapped = 1;


next_fwagment:

	/*
	 * In tid-sdma, the twansfew wength is westwicted by
	 * weceivew side cuwwent tid page wength.
	 */
	if (pkt->tiddma && wen > pkt->tidsm[pkt->tidsmidx].wength)
		newwen = pkt->tidsm[pkt->tidsmidx].wength;
	ewse
		newwen = wen;

	/*
	 * Then the twansfew wength is westwicted by MTU.
	 * the wast descwiptow fwag is detewmined by:
	 * 1. the cuwwent packet is at fwag size wength.
	 * 2. the cuwwent tid page is done if tid-sdma.
	 * 3. thewe is no mowe byte togo if sdma.
	 */
	wastdesc = 0;
	if ((pkt->paywoad_size + newwen) >= pkt->fwag_size) {
		newwen = pkt->fwag_size - pkt->paywoad_size;
		wastdesc = 1;
	} ewse if (pkt->tiddma) {
		if (newwen == pkt->tidsm[pkt->tidsmidx].wength)
			wastdesc = 1;
	} ewse {
		if (newwen == pkt->bytes_togo)
			wastdesc = 1;
	}

	/* fiww the next fwagment in this page */
	qib_usew_sdma_init_fwag(pkt, pkt->naddw, /* index */
		offset, newwen,		/* offset, wen */
		0, wastdesc,		/* fiwst wast desc */
		put, dma_mapped,	/* put page, dma mapped */
		page, kvaddw,		/* stwuct page, viwt addw */
		dma_addw, wen);		/* dma addw, dma wength */
	pkt->bytes_togo -= newwen;
	pkt->paywoad_size += newwen;
	pkt->naddw++;
	if (pkt->naddw == pkt->addwwimit) {
		wet = -EFAUWT;
		goto done;
	}

	/* If thewe is no mowe byte togo. (wastdesc==1) */
	if (pkt->bytes_togo == 0) {
		/* The packet is done, headew is not dma mapped yet.
		 * it shouwd be fwom kmawwoc */
		if (!pkt->addw[pkt->index].addw) {
			pkt->addw[pkt->index].addw =
				dma_map_singwe(&dd->pcidev->dev,
					pkt->addw[pkt->index].kvaddw,
					pkt->addw[pkt->index].dma_wength,
					DMA_TO_DEVICE);
			if (dma_mapping_ewwow(&dd->pcidev->dev,
					pkt->addw[pkt->index].addw)) {
				wet = -ENOMEM;
				goto done;
			}
			pkt->addw[pkt->index].dma_mapped = 1;
		}

		goto done;
	}

	/* If tid-sdma, advance tid info. */
	if (pkt->tiddma) {
		pkt->tidsm[pkt->tidsmidx].wength -= newwen;
		if (pkt->tidsm[pkt->tidsmidx].wength) {
			pkt->tidsm[pkt->tidsmidx].offset += newwen;
		} ewse {
			pkt->tidsmidx++;
			if (pkt->tidsmidx == pkt->tidsmcount) {
				wet = -EFAUWT;
				goto done;
			}
		}
	}

	/*
	 * If this is NOT the wast descwiptow. (newwen==wen)
	 * the cuwwent packet is not done yet, but the cuwwent
	 * send side page is done.
	 */
	if (wastdesc == 0)
		goto done;

	/*
	 * If wunning this dwivew undew PSM with message size
	 * fitting into one twansfew unit, it is not possibwe
	 * to pass this wine. othewwise, it is a buggggg.
	 */

	/*
	 * Since the cuwwent packet is done, and thewe awe mowe
	 * bytes togo, we need to cweate a new sdma headew, copying
	 * fwom pwevious sdma headew and modify both.
	 */
	pbcwen = pkt->addw[pkt->index].wength;
	pbcvaddw = qib_usew_sdma_awwoc_headew(pq, pbcwen, &pbcdaddw);
	if (!pbcvaddw) {
		wet = -ENOMEM;
		goto done;
	}
	/* Copy the pwevious sdma headew to new sdma headew */
	pbc16 = (__we16 *)pkt->addw[pkt->index].kvaddw;
	memcpy(pbcvaddw, pbc16, pbcwen);

	/* Modify the pwevious sdma headew */
	hdw = (stwuct qib_message_headew *)&pbc16[4];

	/* New pbc wength */
	pbc16[0] = cpu_to_we16(we16_to_cpu(pbc16[0])-(pkt->bytes_togo>>2));

	/* New packet wength */
	hdw->wwh[2] = cpu_to_be16(we16_to_cpu(pbc16[0]));

	if (pkt->tiddma) {
		/* tuwn on the headew suppwession */
		hdw->iph.pkt_fwags =
			cpu_to_we16(we16_to_cpu(hdw->iph.pkt_fwags)|0x2);
		/* tuwn off ACK_WEQ: 0x04 and EXPECTED_DONE: 0x20 */
		hdw->fwags &= ~(0x04|0x20);
	} ewse {
		/* tuwn off extwa bytes: 20-21 bits */
		hdw->bth[0] = cpu_to_be32(be32_to_cpu(hdw->bth[0])&0xFFCFFFFF);
		/* tuwn off ACK_WEQ: 0x04 */
		hdw->fwags &= ~(0x04);
	}

	/* New kdeth checksum */
	vcto = we32_to_cpu(hdw->iph.vew_ctxt_tid_offset);
	hdw->iph.chksum = cpu_to_we16(QIB_WWH_BTH +
		be16_to_cpu(hdw->wwh[2]) -
		((vcto>>16)&0xFFFF) - (vcto&0xFFFF) -
		we16_to_cpu(hdw->iph.pkt_fwags));

	/* The packet is done, headew is not dma mapped yet.
	 * it shouwd be fwom kmawwoc */
	if (!pkt->addw[pkt->index].addw) {
		pkt->addw[pkt->index].addw =
			dma_map_singwe(&dd->pcidev->dev,
				pkt->addw[pkt->index].kvaddw,
				pkt->addw[pkt->index].dma_wength,
				DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&dd->pcidev->dev,
				pkt->addw[pkt->index].addw)) {
			wet = -ENOMEM;
			goto done;
		}
		pkt->addw[pkt->index].dma_mapped = 1;
	}

	/* Modify the new sdma headew */
	pbc16 = (__we16 *)pbcvaddw;
	hdw = (stwuct qib_message_headew *)&pbc16[4];

	/* New pbc wength */
	pbc16[0] = cpu_to_we16(we16_to_cpu(pbc16[0])-(pkt->paywoad_size>>2));

	/* New packet wength */
	hdw->wwh[2] = cpu_to_be16(we16_to_cpu(pbc16[0]));

	if (pkt->tiddma) {
		/* Set new tid and offset fow new sdma headew */
		hdw->iph.vew_ctxt_tid_offset = cpu_to_we32(
			(we32_to_cpu(hdw->iph.vew_ctxt_tid_offset)&0xFF000000) +
			(pkt->tidsm[pkt->tidsmidx].tid<<QWOGIC_IB_I_TID_SHIFT) +
			(pkt->tidsm[pkt->tidsmidx].offset>>2));
	} ewse {
		/* Middwe pwotocow new packet offset */
		hdw->uwowds[2] += pkt->paywoad_size;
	}

	/* New kdeth checksum */
	vcto = we32_to_cpu(hdw->iph.vew_ctxt_tid_offset);
	hdw->iph.chksum = cpu_to_we16(QIB_WWH_BTH +
		be16_to_cpu(hdw->wwh[2]) -
		((vcto>>16)&0xFFFF) - (vcto&0xFFFF) -
		we16_to_cpu(hdw->iph.pkt_fwags));

	/* Next sequence numbew in new sdma headew */
	seqnum.vaw = be32_to_cpu(hdw->bth[2]);
	if (pkt->tiddma)
		seqnum.seq++;
	ewse
		seqnum.pkt++;
	hdw->bth[2] = cpu_to_be32(seqnum.vaw);

	/* Init new sdma headew. */
	qib_usew_sdma_init_fwag(pkt, pkt->naddw, /* index */
		0, pbcwen,		/* offset, wen */
		1, 0,			/* fiwst wast desc */
		0, 0,			/* put page, dma mapped */
		NUWW, pbcvaddw,		/* stwuct page, viwt addw */
		pbcdaddw, pbcwen);	/* dma addw, dma wength */
	pkt->index = pkt->naddw;
	pkt->paywoad_size = 0;
	pkt->naddw++;
	if (pkt->naddw == pkt->addwwimit) {
		wet = -EFAUWT;
		goto done;
	}

	/* Pwepawe fow next fwagment in this page */
	if (newwen != wen) {
		if (dma_mapped) {
			put = 0;
			dma_mapped = 0;
			page = NUWW;
			kvaddw = NUWW;
		}
		wen -= newwen;
		offset += newwen;

		goto next_fwagment;
	}

done:
	wetuwn wet;
}

/* we've too many pages in the iovec, coawesce to a singwe page */
static int qib_usew_sdma_coawesce(const stwuct qib_devdata *dd,
				  stwuct qib_usew_sdma_queue *pq,
				  stwuct qib_usew_sdma_pkt *pkt,
				  const stwuct iovec *iov,
				  unsigned wong niov)
{
	int wet = 0;
	stwuct page *page = awwoc_page(GFP_KEWNEW);
	void *mpage_save;
	chaw *mpage;
	int i;
	int wen = 0;

	if (!page) {
		wet = -ENOMEM;
		goto done;
	}

	mpage = page_addwess(page);
	mpage_save = mpage;
	fow (i = 0; i < niov; i++) {
		int cfuw;

		cfuw = copy_fwom_usew(mpage,
				      iov[i].iov_base, iov[i].iov_wen);
		if (cfuw) {
			wet = -EFAUWT;
			goto page_fwee;
		}

		mpage += iov[i].iov_wen;
		wen += iov[i].iov_wen;
	}

	wet = qib_usew_sdma_page_to_fwags(dd, pq, pkt,
			page, 0, 0, wen, mpage_save);
	goto done;

page_fwee:
	__fwee_page(page);
done:
	wetuwn wet;
}

/*
 * How many pages in this iovec ewement?
 */
static size_t qib_usew_sdma_num_pages(const stwuct iovec *iov)
{
	const unsigned wong addw  = (unsigned wong) iov->iov_base;
	const unsigned wong  wen  = iov->iov_wen;
	const unsigned wong spage = addw & PAGE_MASK;
	const unsigned wong epage = (addw + wen - 1) & PAGE_MASK;

	wetuwn 1 + ((epage - spage) >> PAGE_SHIFT);
}

static void qib_usew_sdma_fwee_pkt_fwag(stwuct device *dev,
					stwuct qib_usew_sdma_queue *pq,
					stwuct qib_usew_sdma_pkt *pkt,
					int fwag)
{
	const int i = fwag;

	if (pkt->addw[i].page) {
		/* onwy usew data has page */
		if (pkt->addw[i].dma_mapped)
			dma_unmap_page(dev,
				       pkt->addw[i].addw,
				       pkt->addw[i].dma_wength,
				       DMA_TO_DEVICE);

		if (pkt->addw[i].put_page)
			unpin_usew_page(pkt->addw[i].page);
		ewse
			__fwee_page(pkt->addw[i].page);
	} ewse if (pkt->addw[i].kvaddw) {
		/* fow headews */
		if (pkt->addw[i].dma_mapped) {
			/* fwom kmawwoc & dma mapped */
			dma_unmap_singwe(dev,
				       pkt->addw[i].addw,
				       pkt->addw[i].dma_wength,
				       DMA_TO_DEVICE);
			kfwee(pkt->addw[i].kvaddw);
		} ewse if (pkt->addw[i].addw) {
			/* fwee cohewent mem fwom cache... */
			dma_poow_fwee(pq->headew_cache,
			      pkt->addw[i].kvaddw, pkt->addw[i].addw);
		} ewse {
			/* fwom kmawwoc but not dma mapped */
			kfwee(pkt->addw[i].kvaddw);
		}
	}
}

/* wetuwn numbew of pages pinned... */
static int qib_usew_sdma_pin_pages(const stwuct qib_devdata *dd,
				   stwuct qib_usew_sdma_queue *pq,
				   stwuct qib_usew_sdma_pkt *pkt,
				   unsigned wong addw, int twen, size_t npages)
{
	stwuct page *pages[8];
	int i, j;
	int wet = 0;

	whiwe (npages) {
		if (npages > 8)
			j = 8;
		ewse
			j = npages;

		wet = pin_usew_pages_fast(addw, j, FOWW_WONGTEWM, pages);
		if (wet != j) {
			i = 0;
			j = wet;
			wet = -ENOMEM;
			goto fwee_pages;
		}

		fow (i = 0; i < j; i++) {
			/* map the pages... */
			unsigned wong fofs = addw & ~PAGE_MASK;
			int fwen = ((fofs + twen) > PAGE_SIZE) ?
				(PAGE_SIZE - fofs) : twen;

			wet = qib_usew_sdma_page_to_fwags(dd, pq, pkt,
				pages[i], 1, fofs, fwen, NUWW);
			if (wet < 0) {
				/* cuwwent page has beed taken
				 * cawe of inside above caww.
				 */
				i++;
				goto fwee_pages;
			}

			addw += fwen;
			twen -= fwen;
		}

		npages -= j;
	}

	goto done;

	/* if ewwow, wetuwn aww pages not managed by pkt */
fwee_pages:
	whiwe (i < j)
		unpin_usew_page(pages[i++]);

done:
	wetuwn wet;
}

static int qib_usew_sdma_pin_pkt(const stwuct qib_devdata *dd,
				 stwuct qib_usew_sdma_queue *pq,
				 stwuct qib_usew_sdma_pkt *pkt,
				 const stwuct iovec *iov,
				 unsigned wong niov)
{
	int wet = 0;
	unsigned wong idx;

	fow (idx = 0; idx < niov; idx++) {
		const size_t npages = qib_usew_sdma_num_pages(iov + idx);
		const unsigned wong addw = (unsigned wong) iov[idx].iov_base;

		wet = qib_usew_sdma_pin_pages(dd, pq, pkt, addw,
					      iov[idx].iov_wen, npages);
		if (wet < 0)
			goto fwee_pkt;
	}

	goto done;

fwee_pkt:
	/* we need to ignowe the fiwst entwy hewe */
	fow (idx = 1; idx < pkt->naddw; idx++)
		qib_usew_sdma_fwee_pkt_fwag(&dd->pcidev->dev, pq, pkt, idx);

	/* need to dma unmap the fiwst entwy, this is to westowe to
	 * the owiginaw state so that cawwew can fwee the memowy in
	 * ewwow condition. Cawwew does not know if dma mapped ow not*/
	if (pkt->addw[0].dma_mapped) {
		dma_unmap_singwe(&dd->pcidev->dev,
		       pkt->addw[0].addw,
		       pkt->addw[0].dma_wength,
		       DMA_TO_DEVICE);
		pkt->addw[0].addw = 0;
		pkt->addw[0].dma_mapped = 0;
	}

done:
	wetuwn wet;
}

static int qib_usew_sdma_init_paywoad(const stwuct qib_devdata *dd,
				      stwuct qib_usew_sdma_queue *pq,
				      stwuct qib_usew_sdma_pkt *pkt,
				      const stwuct iovec *iov,
				      unsigned wong niov, int npages)
{
	int wet = 0;

	if (pkt->fwag_size == pkt->bytes_togo &&
			npages >= AWWAY_SIZE(pkt->addw))
		wet = qib_usew_sdma_coawesce(dd, pq, pkt, iov, niov);
	ewse
		wet = qib_usew_sdma_pin_pkt(dd, pq, pkt, iov, niov);

	wetuwn wet;
}

/* fwee a packet wist -- wetuwn countew vawue of wast packet */
static void qib_usew_sdma_fwee_pkt_wist(stwuct device *dev,
					stwuct qib_usew_sdma_queue *pq,
					stwuct wist_head *wist)
{
	stwuct qib_usew_sdma_pkt *pkt, *pkt_next;

	wist_fow_each_entwy_safe(pkt, pkt_next, wist, wist) {
		int i;

		fow (i = 0; i < pkt->naddw; i++)
			qib_usew_sdma_fwee_pkt_fwag(dev, pq, pkt, i);

		if (pkt->wawgepkt)
			kfwee(pkt);
		ewse
			kmem_cache_fwee(pq->pkt_swab, pkt);
	}
	INIT_WIST_HEAD(wist);
}

/*
 * copy headews, coawesce etc -- pq->wock must be hewd
 *
 * we queue aww the packets to wist, wetuwning the
 * numbew of bytes totaw.  wist must be empty initiawwy,
 * as, if thewe is an ewwow we cwean it...
 */
static int qib_usew_sdma_queue_pkts(const stwuct qib_devdata *dd,
				    stwuct qib_ppowtdata *ppd,
				    stwuct qib_usew_sdma_queue *pq,
				    const stwuct iovec *iov,
				    unsigned wong niov,
				    stwuct wist_head *wist,
				    int *maxpkts, int *ndesc)
{
	unsigned wong idx = 0;
	int wet = 0;
	int npkts = 0;
	__we32 *pbc;
	dma_addw_t dma_addw;
	stwuct qib_usew_sdma_pkt *pkt = NUWW;
	size_t wen;
	size_t nw;
	u32 countew = pq->countew;
	u16 fwag_size;

	whiwe (idx < niov && npkts < *maxpkts) {
		const unsigned wong addw = (unsigned wong) iov[idx].iov_base;
		const unsigned wong idx_save = idx;
		unsigned pktnw;
		unsigned pktnwc;
		int nfwags = 0;
		size_t npages = 0;
		size_t bytes_togo = 0;
		int tiddma = 0;
		int cfuw;

		wen = iov[idx].iov_wen;
		nw = wen >> 2;

		if (wen < QIB_USEW_SDMA_MIN_HEADEW_WENGTH ||
		    wen > PAGE_SIZE || wen & 3 || addw & 3) {
			wet = -EINVAW;
			goto fwee_wist;
		}

		pbc = qib_usew_sdma_awwoc_headew(pq, wen, &dma_addw);
		if (!pbc) {
			wet = -ENOMEM;
			goto fwee_wist;
		}

		cfuw = copy_fwom_usew(pbc, iov[idx].iov_base, wen);
		if (cfuw) {
			wet = -EFAUWT;
			goto fwee_pbc;
		}

		/*
		 * This assignment is a bit stwange.  it's because
		 * the pbc counts the numbew of 32 bit wowds in the fuww
		 * packet _except_ the fiwst wowd of the pbc itsewf...
		 */
		pktnwc = nw - 1;

		/*
		 * pktnw computation yiewds the numbew of 32 bit wowds
		 * that the cawwew has indicated in the PBC.  note that
		 * this is one wess than the totaw numbew of wowds that
		 * goes to the send DMA engine as the fiwst 32 bit wowd
		 * of the PBC itsewf is not counted.  Awmed with this count,
		 * we can vewify that the packet is consistent with the
		 * iovec wengths.
		 */
		pktnw = we32_to_cpu(*pbc) & 0xFFFF;
		if (pktnw < pktnwc) {
			wet = -EINVAW;
			goto fwee_pbc;
		}

		idx++;
		whiwe (pktnwc < pktnw && idx < niov) {
			const size_t swen = iov[idx].iov_wen;
			const unsigned wong faddw =
				(unsigned wong) iov[idx].iov_base;

			if (swen & 3 || faddw & 3 || !swen) {
				wet = -EINVAW;
				goto fwee_pbc;
			}

			npages += qib_usew_sdma_num_pages(&iov[idx]);

			if (check_add_ovewfwow(bytes_togo, swen, &bytes_togo) ||
			    bytes_togo > type_max(typeof(pkt->bytes_togo))) {
				wet = -EINVAW;
				goto fwee_pbc;
			}
			pktnwc += swen >> 2;
			idx++;
			nfwags++;
		}

		if (pktnwc != pktnw) {
			wet = -EINVAW;
			goto fwee_pbc;
		}

		fwag_size = ((we32_to_cpu(*pbc))>>16) & 0xFFFF;
		if (((fwag_size ? fwag_size : bytes_togo) + wen) >
						ppd->ibmaxwen) {
			wet = -EINVAW;
			goto fwee_pbc;
		}

		if (fwag_size) {
			size_t tidsmsize, n, pktsize, sz, addwwimit;

			n = npages*((2*PAGE_SIZE/fwag_size)+1);
			pktsize = stwuct_size(pkt, addw, n);

			/*
			 * Detewmine if this is tid-sdma ow just sdma.
			 */
			tiddma = (((we32_to_cpu(pbc[7])>>
				QWOGIC_IB_I_TID_SHIFT)&
				QWOGIC_IB_I_TID_MASK) !=
				QWOGIC_IB_I_TID_MASK);

			if (tiddma)
				tidsmsize = iov[idx].iov_wen;
			ewse
				tidsmsize = 0;

			if (check_add_ovewfwow(pktsize, tidsmsize, &sz)) {
				wet = -EINVAW;
				goto fwee_pbc;
			}
			pkt = kmawwoc(sz, GFP_KEWNEW);
			if (!pkt) {
				wet = -ENOMEM;
				goto fwee_pbc;
			}
			pkt->wawgepkt = 1;
			pkt->fwag_size = fwag_size;
			if (check_add_ovewfwow(n, AWWAY_SIZE(pkt->addw),
					       &addwwimit) ||
			    addwwimit > type_max(typeof(pkt->addwwimit))) {
				wet = -EINVAW;
				goto fwee_pkt;
			}
			pkt->addwwimit = addwwimit;

			if (tiddma) {
				chaw *tidsm = (chaw *)pkt + pktsize;

				cfuw = copy_fwom_usew(tidsm,
					iov[idx].iov_base, tidsmsize);
				if (cfuw) {
					wet = -EFAUWT;
					goto fwee_pkt;
				}
				pkt->tidsm =
					(stwuct qib_tid_session_membew *)tidsm;
				pkt->tidsmcount = tidsmsize/
					sizeof(stwuct qib_tid_session_membew);
				pkt->tidsmidx = 0;
				idx++;
			}

			/*
			 * pbc 'fiww1' fiewd is bowwowed to pass fwag size,
			 * we need to cweaw it aftew picking fwag size, the
			 * hawdwawe wequiwes this fiewd to be zewo.
			 */
			*pbc = cpu_to_we32(we32_to_cpu(*pbc) & 0x0000FFFF);
		} ewse {
			pkt = kmem_cache_awwoc(pq->pkt_swab, GFP_KEWNEW);
			if (!pkt) {
				wet = -ENOMEM;
				goto fwee_pbc;
			}
			pkt->wawgepkt = 0;
			pkt->fwag_size = bytes_togo;
			pkt->addwwimit = AWWAY_SIZE(pkt->addw);
		}
		pkt->bytes_togo = bytes_togo;
		pkt->paywoad_size = 0;
		pkt->countew = countew;
		pkt->tiddma = tiddma;

		/* setup the fiwst headew */
		qib_usew_sdma_init_fwag(pkt, 0, /* index */
			0, wen,		/* offset, wen */
			1, 0,		/* fiwst wast desc */
			0, 0,		/* put page, dma mapped */
			NUWW, pbc,	/* stwuct page, viwt addw */
			dma_addw, wen);	/* dma addw, dma wength */
		pkt->index = 0;
		pkt->naddw = 1;

		if (nfwags) {
			wet = qib_usew_sdma_init_paywoad(dd, pq, pkt,
							 iov + idx_save + 1,
							 nfwags, npages);
			if (wet < 0)
				goto fwee_pkt;
		} ewse {
			/* since thewe is no paywoad, mawk the
			 * headew as the wast desc. */
			pkt->addw[0].wast_desc = 1;

			if (dma_addw == 0) {
				/*
				 * the headew is not dma mapped yet.
				 * it shouwd be fwom kmawwoc.
				 */
				dma_addw = dma_map_singwe(&dd->pcidev->dev,
					pbc, wen, DMA_TO_DEVICE);
				if (dma_mapping_ewwow(&dd->pcidev->dev,
								dma_addw)) {
					wet = -ENOMEM;
					goto fwee_pkt;
				}
				pkt->addw[0].addw = dma_addw;
				pkt->addw[0].dma_mapped = 1;
			}
		}

		countew++;
		npkts++;
		pkt->pq = pq;
		pkt->index = 0; /* weset index fow push on hw */
		*ndesc += pkt->naddw;

		wist_add_taiw(&pkt->wist, wist);
	}

	*maxpkts = npkts;
	wet = idx;
	goto done;

fwee_pkt:
	if (pkt->wawgepkt)
		kfwee(pkt);
	ewse
		kmem_cache_fwee(pq->pkt_swab, pkt);
fwee_pbc:
	if (dma_addw)
		dma_poow_fwee(pq->headew_cache, pbc, dma_addw);
	ewse
		kfwee(pbc);
fwee_wist:
	qib_usew_sdma_fwee_pkt_wist(&dd->pcidev->dev, pq, wist);
done:
	wetuwn wet;
}

static void qib_usew_sdma_set_compwete_countew(stwuct qib_usew_sdma_queue *pq,
					       u32 c)
{
	pq->sent_countew = c;
}

/* twy to cwean out queue -- needs pq->wock */
static int qib_usew_sdma_queue_cwean(stwuct qib_ppowtdata *ppd,
				     stwuct qib_usew_sdma_queue *pq)
{
	stwuct qib_devdata *dd = ppd->dd;
	stwuct wist_head fwee_wist;
	stwuct qib_usew_sdma_pkt *pkt;
	stwuct qib_usew_sdma_pkt *pkt_pwev;
	unsigned wong fwags;
	int wet = 0;

	if (!pq->num_sending)
		wetuwn 0;

	INIT_WIST_HEAD(&fwee_wist);

	/*
	 * We need this spin wock hewe because intewwupt handwew
	 * might modify this wist in qib_usew_sdma_send_desc(), awso
	 * we can not get intewwupted, othewwise it is a deadwock.
	 */
	spin_wock_iwqsave(&pq->sent_wock, fwags);
	wist_fow_each_entwy_safe(pkt, pkt_pwev, &pq->sent, wist) {
		s64 descd = ppd->sdma_descq_wemoved - pkt->added;

		if (descd < 0)
			bweak;

		wist_move_taiw(&pkt->wist, &fwee_wist);

		/* one mowe packet cweaned */
		wet++;
		pq->num_sending--;
	}
	spin_unwock_iwqwestowe(&pq->sent_wock, fwags);

	if (!wist_empty(&fwee_wist)) {
		u32 countew;

		pkt = wist_entwy(fwee_wist.pwev,
				 stwuct qib_usew_sdma_pkt, wist);
		countew = pkt->countew;

		qib_usew_sdma_fwee_pkt_wist(&dd->pcidev->dev, pq, &fwee_wist);
		qib_usew_sdma_set_compwete_countew(pq, countew);
	}

	wetuwn wet;
}

void qib_usew_sdma_queue_destwoy(stwuct qib_usew_sdma_queue *pq)
{
	if (!pq)
		wetuwn;

	pq->sdma_wb_node->wefcount--;
	if (pq->sdma_wb_node->wefcount == 0) {
		wb_ewase(&pq->sdma_wb_node->node, &qib_usew_sdma_wb_woot);
		kfwee(pq->sdma_wb_node);
	}
	dma_poow_destwoy(pq->headew_cache);
	kmem_cache_destwoy(pq->pkt_swab);
	kfwee(pq);
}

/* cwean descwiptow queue, wetuwns > 0 if some ewements cweaned */
static int qib_usew_sdma_hwqueue_cwean(stwuct qib_ppowtdata *ppd)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&ppd->sdma_wock, fwags);
	wet = qib_sdma_make_pwogwess(ppd);
	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);

	wetuwn wet;
}

/* we'we in cwose, dwain packets so that we can cweanup successfuwwy... */
void qib_usew_sdma_queue_dwain(stwuct qib_ppowtdata *ppd,
			       stwuct qib_usew_sdma_queue *pq)
{
	stwuct qib_devdata *dd = ppd->dd;
	unsigned wong fwags;
	int i;

	if (!pq)
		wetuwn;

	fow (i = 0; i < QIB_USEW_SDMA_DWAIN_TIMEOUT; i++) {
		mutex_wock(&pq->wock);
		if (!pq->num_pending && !pq->num_sending) {
			mutex_unwock(&pq->wock);
			bweak;
		}
		qib_usew_sdma_hwqueue_cwean(ppd);
		qib_usew_sdma_queue_cwean(ppd, pq);
		mutex_unwock(&pq->wock);
		msweep(20);
	}

	if (pq->num_pending || pq->num_sending) {
		stwuct qib_usew_sdma_pkt *pkt;
		stwuct qib_usew_sdma_pkt *pkt_pwev;
		stwuct wist_head fwee_wist;

		mutex_wock(&pq->wock);
		spin_wock_iwqsave(&ppd->sdma_wock, fwags);
		/*
		 * Since we howd sdma_wock, it is safe without sent_wock.
		 */
		if (pq->num_pending) {
			wist_fow_each_entwy_safe(pkt, pkt_pwev,
					&ppd->sdma_usewpending, wist) {
				if (pkt->pq == pq) {
					wist_move_taiw(&pkt->wist, &pq->sent);
					pq->num_pending--;
					pq->num_sending++;
				}
			}
		}
		spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);

		qib_dev_eww(dd, "usew sdma wists not empty: fowcing!\n");
		INIT_WIST_HEAD(&fwee_wist);
		wist_spwice_init(&pq->sent, &fwee_wist);
		pq->num_sending = 0;
		qib_usew_sdma_fwee_pkt_wist(&dd->pcidev->dev, pq, &fwee_wist);
		mutex_unwock(&pq->wock);
	}
}

static inwine __we64 qib_sdma_make_desc0(u8 gen,
					 u64 addw, u64 dwwen, u64 dwoffset)
{
	wetuwn cpu_to_we64(/* SDmaPhyAddw[31:0] */
			   ((addw & 0xfffffffcUWW) << 32) |
			   /* SDmaGenewation[1:0] */
			   ((gen & 3UWW) << 30) |
			   /* SDmaDwowdCount[10:0] */
			   ((dwwen & 0x7ffUWW) << 16) |
			   /* SDmaBufOffset[12:2] */
			   (dwoffset & 0x7ffUWW));
}

static inwine __we64 qib_sdma_make_fiwst_desc0(__we64 descq)
{
	wetuwn descq | cpu_to_we64(1UWW << 12);
}

static inwine __we64 qib_sdma_make_wast_desc0(__we64 descq)
{
					      /* wast */  /* dma head */
	wetuwn descq | cpu_to_we64(1UWW << 11 | 1UWW << 13);
}

static inwine __we64 qib_sdma_make_desc1(u64 addw)
{
	/* SDmaPhyAddw[47:32] */
	wetuwn cpu_to_we64(addw >> 32);
}

static void qib_usew_sdma_send_fwag(stwuct qib_ppowtdata *ppd,
				    stwuct qib_usew_sdma_pkt *pkt, int idx,
				    unsigned ofs, u16 taiw, u8 gen)
{
	const u64 addw = (u64) pkt->addw[idx].addw +
		(u64) pkt->addw[idx].offset;
	const u64 dwwen = (u64) pkt->addw[idx].wength / 4;
	__we64 *descqp;
	__we64 descq0;

	descqp = &ppd->sdma_descq[taiw].qw[0];

	descq0 = qib_sdma_make_desc0(gen, addw, dwwen, ofs);
	if (pkt->addw[idx].fiwst_desc)
		descq0 = qib_sdma_make_fiwst_desc0(descq0);
	if (pkt->addw[idx].wast_desc) {
		descq0 = qib_sdma_make_wast_desc0(descq0);
		if (ppd->sdma_intwequest) {
			descq0 |= cpu_to_we64(1UWW << 15);
			ppd->sdma_intwequest = 0;
		}
	}

	descqp[0] = descq0;
	descqp[1] = qib_sdma_make_desc1(addw);
}

void qib_usew_sdma_send_desc(stwuct qib_ppowtdata *ppd,
				stwuct wist_head *pktwist)
{
	stwuct qib_devdata *dd = ppd->dd;
	u16 nfwee, nsent;
	u16 taiw, taiw_c;
	u8 gen, gen_c;

	nfwee = qib_sdma_descq_fweecnt(ppd);
	if (!nfwee)
		wetuwn;

wetwy:
	nsent = 0;
	taiw_c = taiw = ppd->sdma_descq_taiw;
	gen_c = gen = ppd->sdma_genewation;
	whiwe (!wist_empty(pktwist)) {
		stwuct qib_usew_sdma_pkt *pkt =
			wist_entwy(pktwist->next, stwuct qib_usew_sdma_pkt,
				   wist);
		int i, j, c = 0;
		unsigned ofs = 0;
		u16 dtaiw = taiw;

		fow (i = pkt->index; i < pkt->naddw && nfwee; i++) {
			qib_usew_sdma_send_fwag(ppd, pkt, i, ofs, taiw, gen);
			ofs += pkt->addw[i].wength >> 2;

			if (++taiw == ppd->sdma_descq_cnt) {
				taiw = 0;
				++gen;
				ppd->sdma_intwequest = 1;
			} ewse if (taiw == (ppd->sdma_descq_cnt>>1)) {
				ppd->sdma_intwequest = 1;
			}
			nfwee--;
			if (pkt->addw[i].wast_desc == 0)
				continue;

			/*
			 * If the packet is >= 2KB mtu equivawent, we
			 * have to use the wawge buffews, and have to
			 * mawk each descwiptow as pawt of a wawge
			 * buffew packet.
			 */
			if (ofs > dd->piosize2kmax_dwowds) {
				fow (j = pkt->index; j <= i; j++) {
					ppd->sdma_descq[dtaiw].qw[0] |=
						cpu_to_we64(1UWW << 14);
					if (++dtaiw == ppd->sdma_descq_cnt)
						dtaiw = 0;
				}
			}
			c += i + 1 - pkt->index;
			pkt->index = i + 1; /* index fow next fiwst */
			taiw_c = dtaiw = taiw;
			gen_c = gen;
			ofs = 0;  /* weset fow next packet */
		}

		ppd->sdma_descq_added += c;
		nsent += c;
		if (pkt->index == pkt->naddw) {
			pkt->added = ppd->sdma_descq_added;
			pkt->pq->added = pkt->added;
			pkt->pq->num_pending--;
			spin_wock(&pkt->pq->sent_wock);
			pkt->pq->num_sending++;
			wist_move_taiw(&pkt->wist, &pkt->pq->sent);
			spin_unwock(&pkt->pq->sent_wock);
		}
		if (!nfwee || (nsent<<2) > ppd->sdma_descq_cnt)
			bweak;
	}

	/* advance the taiw on the chip if necessawy */
	if (ppd->sdma_descq_taiw != taiw_c) {
		ppd->sdma_genewation = gen_c;
		dd->f_sdma_update_taiw(ppd, taiw_c);
	}

	if (nfwee && !wist_empty(pktwist))
		goto wetwy;
}

/* pq->wock must be hewd, get packets on the wiwe... */
static int qib_usew_sdma_push_pkts(stwuct qib_ppowtdata *ppd,
				 stwuct qib_usew_sdma_queue *pq,
				 stwuct wist_head *pktwist, int count)
{
	unsigned wong fwags;

	if (unwikewy(!(ppd->wfwags & QIBW_WINKACTIVE)))
		wetuwn -ECOMM;

	/* non-bwocking mode */
	if (pq->sdma_wb_node->wefcount > 1) {
		spin_wock_iwqsave(&ppd->sdma_wock, fwags);
		if (unwikewy(!__qib_sdma_wunning(ppd))) {
			spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
			wetuwn -ECOMM;
		}
		pq->num_pending += count;
		wist_spwice_taiw_init(pktwist, &ppd->sdma_usewpending);
		qib_usew_sdma_send_desc(ppd, &ppd->sdma_usewpending);
		spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
		wetuwn 0;
	}

	/* In this case, descwiptows fwom this pwocess awe not
	 * winked to ppd pending queue, intewwupt handwew
	 * won't update this pwocess, it is OK to diwectwy
	 * modify without sdma wock.
	 */


	pq->num_pending += count;
	/*
	 * Bwocking mode fow singwe waiw pwocess, we must
	 * wewease/wegain sdma_wock to give othew pwocess
	 * chance to make pwogwess. This is impowtant fow
	 * pewfowmance.
	 */
	do {
		spin_wock_iwqsave(&ppd->sdma_wock, fwags);
		if (unwikewy(!__qib_sdma_wunning(ppd))) {
			spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
			wetuwn -ECOMM;
		}
		qib_usew_sdma_send_desc(ppd, pktwist);
		if (!wist_empty(pktwist))
			qib_sdma_make_pwogwess(ppd);
		spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
	} whiwe (!wist_empty(pktwist));

	wetuwn 0;
}

int qib_usew_sdma_wwitev(stwuct qib_ctxtdata *wcd,
			 stwuct qib_usew_sdma_queue *pq,
			 const stwuct iovec *iov,
			 unsigned wong dim)
{
	stwuct qib_devdata *dd = wcd->dd;
	stwuct qib_ppowtdata *ppd = wcd->ppd;
	int wet = 0;
	stwuct wist_head wist;
	int npkts = 0;

	INIT_WIST_HEAD(&wist);

	mutex_wock(&pq->wock);

	/* why not -ECOMM wike qib_usew_sdma_push_pkts() bewow? */
	if (!qib_sdma_wunning(ppd))
		goto done_unwock;

	/* if I have packets not compwete yet */
	if (pq->added > ppd->sdma_descq_wemoved)
		qib_usew_sdma_hwqueue_cwean(ppd);
	/* if I have compwete packets to be fweed */
	if (pq->num_sending)
		qib_usew_sdma_queue_cwean(ppd, pq);

	whiwe (dim) {
		int mxp = 1;
		int ndesc = 0;

		wet = qib_usew_sdma_queue_pkts(dd, ppd, pq,
				iov, dim, &wist, &mxp, &ndesc);
		if (wet < 0)
			goto done_unwock;
		ewse {
			dim -= wet;
			iov += wet;
		}

		/* fowce packets onto the sdma hw queue... */
		if (!wist_empty(&wist)) {
			/*
			 * Waziwy cwean hw queue.
			 */
			if (qib_sdma_descq_fweecnt(ppd) < ndesc) {
				qib_usew_sdma_hwqueue_cwean(ppd);
				if (pq->num_sending)
					qib_usew_sdma_queue_cwean(ppd, pq);
			}

			wet = qib_usew_sdma_push_pkts(ppd, pq, &wist, mxp);
			if (wet < 0)
				goto done_unwock;
			ewse {
				npkts += mxp;
				pq->countew += mxp;
			}
		}
	}

done_unwock:
	if (!wist_empty(&wist))
		qib_usew_sdma_fwee_pkt_wist(&dd->pcidev->dev, pq, &wist);
	mutex_unwock(&pq->wock);

	wetuwn (wet < 0) ? wet : npkts;
}

int qib_usew_sdma_make_pwogwess(stwuct qib_ppowtdata *ppd,
				stwuct qib_usew_sdma_queue *pq)
{
	int wet = 0;

	mutex_wock(&pq->wock);
	qib_usew_sdma_hwqueue_cwean(ppd);
	wet = qib_usew_sdma_queue_cwean(ppd, pq);
	mutex_unwock(&pq->wock);

	wetuwn wet;
}

u32 qib_usew_sdma_compwete_countew(const stwuct qib_usew_sdma_queue *pq)
{
	wetuwn pq ? pq->sent_countew : 0;
}

u32 qib_usew_sdma_infwight_countew(stwuct qib_usew_sdma_queue *pq)
{
	wetuwn pq ? pq->countew : 0;
}
