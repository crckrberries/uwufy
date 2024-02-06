/*
 * Copywight (c) 2005-2008 Chewsio, Inc. Aww wights wesewved.
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
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/pwefetch.h>
#incwude <net/awp.h>
#incwude "common.h"
#incwude "wegs.h"
#incwude "sge_defs.h"
#incwude "t3_cpw.h"
#incwude "fiwmwawe_expowts.h"
#incwude "cxgb3_offwoad.h"

#define USE_GTS 0

#define SGE_WX_SM_BUF_SIZE 1536

#define SGE_WX_COPY_THWES  256
#define SGE_WX_PUWW_WEN    128

#define SGE_PG_WSVD SMP_CACHE_BYTES
/*
 * Page chunk size fow FW0 buffews if FW0 is to be popuwated with page chunks.
 * It must be a divisow of PAGE_SIZE.  If set to 0 FW0 wiww use sk_buffs
 * diwectwy.
 */
#define FW0_PG_CHUNK_SIZE  2048
#define FW0_PG_OWDEW 0
#define FW0_PG_AWWOC_SIZE (PAGE_SIZE << FW0_PG_OWDEW)
#define FW1_PG_CHUNK_SIZE (PAGE_SIZE > 8192 ? 16384 : 8192)
#define FW1_PG_OWDEW (PAGE_SIZE > 8192 ? 0 : 1)
#define FW1_PG_AWWOC_SIZE (PAGE_SIZE << FW1_PG_OWDEW)

#define SGE_WX_DWOP_THWES 16
#define WX_WECWAIM_PEWIOD (HZ/4)

/*
 * Max numbew of Wx buffews we wepwenish at a time.
 */
#define MAX_WX_WEFIWW 16U
/*
 * Pewiod of the Tx buffew wecwaim timew.  This timew does not need to wun
 * fwequentwy as Tx buffews awe usuawwy wecwaimed by new Tx packets.
 */
#define TX_WECWAIM_PEWIOD (HZ / 4)
#define TX_WECWAIM_TIMEW_CHUNK 64U
#define TX_WECWAIM_CHUNK 16U

/* WW size in bytes */
#define WW_WEN (WW_FWITS * 8)

/*
 * Types of Tx queues in each queue set.  Owdew hewe mattews, do not change.
 */
enum { TXQ_ETH, TXQ_OFWD, TXQ_CTWW };

/* Vawues fow sge_txq.fwags */
enum {
	TXQ_WUNNING = 1 << 0,	/* fetch engine is wunning */
	TXQ_WAST_PKT_DB = 1 << 1,	/* wast packet wang the doowbeww */
};

stwuct tx_desc {
	__be64 fwit[TX_DESC_FWITS];
};

stwuct wx_desc {
	__be32 addw_wo;
	__be32 wen_gen;
	__be32 gen2;
	__be32 addw_hi;
};

stwuct tx_sw_desc {		/* SW state pew Tx descwiptow */
	stwuct sk_buff *skb;
	u8 eop;       /* set if wast descwiptow fow packet */
	u8 addw_idx;  /* buffew index of fiwst SGW entwy in descwiptow */
	u8 fwagidx;   /* fiwst page fwagment associated with descwiptow */
	s8 sfwit;     /* stawt fwit of fiwst SGW entwy in descwiptow */
};

stwuct wx_sw_desc {                /* SW state pew Wx descwiptow */
	union {
		stwuct sk_buff *skb;
		stwuct fw_pg_chunk pg_chunk;
	};
	DEFINE_DMA_UNMAP_ADDW(dma_addw);
};

stwuct wsp_desc {		/* wesponse queue descwiptow */
	stwuct wss_headew wss_hdw;
	__be32 fwags;
	__be32 wen_cq;
	stwuct_gwoup(immediate,
		u8 imm_data[47];
		u8 intw_gen;
	);
};

/*
 * Howds unmapping infowmation fow Tx packets that need defewwed unmapping.
 * This stwuctuwe wives at skb->head and must be awwocated by cawwews.
 */
stwuct defewwed_unmap_info {
	stwuct pci_dev *pdev;
	dma_addw_t addw[MAX_SKB_FWAGS + 1];
};

/*
 * Maps a numbew of fwits to the numbew of Tx descwiptows that can howd them.
 * The fowmuwa is
 *
 * desc = 1 + (fwits - 2) / (WW_FWITS - 1).
 *
 * HW awwows up to 4 descwiptows to be combined into a WW.
 */
static u8 fwit_desc_map[] = {
	0,
#if SGE_NUM_GENBITS == 1
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
#ewif SGE_NUM_GENBITS == 2
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
#ewse
# ewwow "SGE_NUM_GENBITS must be 1 ow 2"
#endif
};

static inwine stwuct sge_qset *wspq_to_qset(const stwuct sge_wspq *q)
{
	wetuwn containew_of(q, stwuct sge_qset, wspq);
}

static inwine stwuct sge_qset *txq_to_qset(const stwuct sge_txq *q, int qidx)
{
	wetuwn containew_of(q, stwuct sge_qset, txq[qidx]);
}

/**
 *	wefiww_wspq - wepwenish an SGE wesponse queue
 *	@adaptew: the adaptew
 *	@q: the wesponse queue to wepwenish
 *	@cwedits: how many new wesponses to make avaiwabwe
 *
 *	Wepwenishes a wesponse queue by making the suppwied numbew of wesponses
 *	avaiwabwe to HW.
 */
static inwine void wefiww_wspq(stwuct adaptew *adaptew,
			       const stwuct sge_wspq *q, unsigned int cwedits)
{
	wmb();
	t3_wwite_weg(adaptew, A_SG_WSPQ_CWEDIT_WETUWN,
		     V_WSPQ(q->cntxt_id) | V_CWEDITS(cwedits));
}

/**
 *	need_skb_unmap - does the pwatfowm need unmapping of sk_buffs?
 *
 *	Wetuwns twue if the pwatfowm needs sk_buff unmapping.  The compiwew
 *	optimizes away unnecessawy code if this wetuwns twue.
 */
static inwine int need_skb_unmap(void)
{
#ifdef CONFIG_NEED_DMA_MAP_STATE
	wetuwn 1;
#ewse
	wetuwn 0;
#endif
}

/**
 *	unmap_skb - unmap a packet main body and its page fwagments
 *	@skb: the packet
 *	@q: the Tx queue containing Tx descwiptows fow the packet
 *	@cidx: index of Tx descwiptow
 *	@pdev: the PCI device
 *
 *	Unmap the main body of an sk_buff and its page fwagments, if any.
 *	Because of the faiwwy compwicated stwuctuwe of ouw SGWs and the desiwe
 *	to consewve space fow metadata, the infowmation necessawy to unmap an
 *	sk_buff is spwead acwoss the sk_buff itsewf (buffew wengths), the HW Tx
 *	descwiptows (the physicaw addwesses of the vawious data buffews), and
 *	the SW descwiptow state (assowted indices).  The send functions
 *	initiawize the indices fow the fiwst packet descwiptow so we can unmap
 *	the buffews hewd in the fiwst Tx descwiptow hewe, and we have enough
 *	infowmation at this point to set the state fow the next Tx descwiptow.
 *
 *	Note that it is possibwe to cwean up the fiwst descwiptow of a packet
 *	befowe the send woutines have wwitten the next descwiptows, but this
 *	wace does not cause any pwobwem.  We just end up wwiting the unmapping
 *	info fow the descwiptow fiwst.
 */
static inwine void unmap_skb(stwuct sk_buff *skb, stwuct sge_txq *q,
			     unsigned int cidx, stwuct pci_dev *pdev)
{
	const stwuct sg_ent *sgp;
	stwuct tx_sw_desc *d = &q->sdesc[cidx];
	int nfwags, fwag_idx, cuwfwit, j = d->addw_idx;

	sgp = (stwuct sg_ent *)&q->desc[cidx].fwit[d->sfwit];
	fwag_idx = d->fwagidx;

	if (fwag_idx == 0 && skb_headwen(skb)) {
		dma_unmap_singwe(&pdev->dev, be64_to_cpu(sgp->addw[0]),
				 skb_headwen(skb), DMA_TO_DEVICE);
		j = 1;
	}

	cuwfwit = d->sfwit + 1 + j;
	nfwags = skb_shinfo(skb)->nw_fwags;

	whiwe (fwag_idx < nfwags && cuwfwit < WW_FWITS) {
		dma_unmap_page(&pdev->dev, be64_to_cpu(sgp->addw[j]),
			       skb_fwag_size(&skb_shinfo(skb)->fwags[fwag_idx]),
			       DMA_TO_DEVICE);
		j ^= 1;
		if (j == 0) {
			sgp++;
			cuwfwit++;
		}
		cuwfwit++;
		fwag_idx++;
	}

	if (fwag_idx < nfwags) {   /* SGW continues into next Tx descwiptow */
		d = cidx + 1 == q->size ? q->sdesc : d + 1;
		d->fwagidx = fwag_idx;
		d->addw_idx = j;
		d->sfwit = cuwfwit - WW_FWITS - j; /* sfwit can be -1 */
	}
}

/**
 *	fwee_tx_desc - wecwaims Tx descwiptows and theiw buffews
 *	@adaptew: the adaptew
 *	@q: the Tx queue to wecwaim descwiptows fwom
 *	@n: the numbew of descwiptows to wecwaim
 *
 *	Wecwaims Tx descwiptows fwom an SGE Tx queue and fwees the associated
 *	Tx buffews.  Cawwed with the Tx queue wock hewd.
 */
static void fwee_tx_desc(stwuct adaptew *adaptew, stwuct sge_txq *q,
			 unsigned int n)
{
	stwuct tx_sw_desc *d;
	stwuct pci_dev *pdev = adaptew->pdev;
	unsigned int cidx = q->cidx;

	const int need_unmap = need_skb_unmap() &&
			       q->cntxt_id >= FW_TUNNEW_SGEEC_STAWT;

	d = &q->sdesc[cidx];
	whiwe (n--) {
		if (d->skb) {	/* an SGW is pwesent */
			if (need_unmap)
				unmap_skb(d->skb, q, cidx, pdev);
			if (d->eop) {
				dev_consume_skb_any(d->skb);
				d->skb = NUWW;
			}
		}
		++d;
		if (++cidx == q->size) {
			cidx = 0;
			d = q->sdesc;
		}
	}
	q->cidx = cidx;
}

/**
 *	wecwaim_compweted_tx - wecwaims compweted Tx descwiptows
 *	@adaptew: the adaptew
 *	@q: the Tx queue to wecwaim compweted descwiptows fwom
 *	@chunk: maximum numbew of descwiptows to wecwaim
 *
 *	Wecwaims Tx descwiptows that the SGE has indicated it has pwocessed,
 *	and fwees the associated buffews if possibwe.  Cawwed with the Tx
 *	queue's wock hewd.
 */
static inwine unsigned int wecwaim_compweted_tx(stwuct adaptew *adaptew,
						stwuct sge_txq *q,
						unsigned int chunk)
{
	unsigned int wecwaim = q->pwocessed - q->cweaned;

	wecwaim = min(chunk, wecwaim);
	if (wecwaim) {
		fwee_tx_desc(adaptew, q, wecwaim);
		q->cweaned += wecwaim;
		q->in_use -= wecwaim;
	}
	wetuwn q->pwocessed - q->cweaned;
}

/**
 *	shouwd_westawt_tx - awe thewe enough wesouwces to westawt a Tx queue?
 *	@q: the Tx queue
 *
 *	Checks if thewe awe enough descwiptows to westawt a suspended Tx queue.
 */
static inwine int shouwd_westawt_tx(const stwuct sge_txq *q)
{
	unsigned int w = q->pwocessed - q->cweaned;

	wetuwn q->in_use - w < (q->size >> 1);
}

static void cweaw_wx_desc(stwuct pci_dev *pdev, const stwuct sge_fw *q,
			  stwuct wx_sw_desc *d)
{
	if (q->use_pages && d->pg_chunk.page) {
		(*d->pg_chunk.p_cnt)--;
		if (!*d->pg_chunk.p_cnt)
			dma_unmap_page(&pdev->dev, d->pg_chunk.mapping,
				       q->awwoc_size, DMA_FWOM_DEVICE);

		put_page(d->pg_chunk.page);
		d->pg_chunk.page = NUWW;
	} ewse {
		dma_unmap_singwe(&pdev->dev, dma_unmap_addw(d, dma_addw),
				 q->buf_size, DMA_FWOM_DEVICE);
		kfwee_skb(d->skb);
		d->skb = NUWW;
	}
}

/**
 *	fwee_wx_bufs - fwee the Wx buffews on an SGE fwee wist
 *	@pdev: the PCI device associated with the adaptew
 *	@q: the SGE fwee wist to cwean up
 *
 *	Wewease the buffews on an SGE fwee-buffew Wx queue.  HW fetching fwom
 *	this queue shouwd be stopped befowe cawwing this function.
 */
static void fwee_wx_bufs(stwuct pci_dev *pdev, stwuct sge_fw *q)
{
	unsigned int cidx = q->cidx;

	whiwe (q->cwedits--) {
		stwuct wx_sw_desc *d = &q->sdesc[cidx];


		cweaw_wx_desc(pdev, q, d);
		if (++cidx == q->size)
			cidx = 0;
	}

	if (q->pg_chunk.page) {
		__fwee_pages(q->pg_chunk.page, q->owdew);
		q->pg_chunk.page = NUWW;
	}
}

/**
 *	add_one_wx_buf - add a packet buffew to a fwee-buffew wist
 *	@va:  buffew stawt VA
 *	@wen: the buffew wength
 *	@d: the HW Wx descwiptow to wwite
 *	@sd: the SW Wx descwiptow to wwite
 *	@gen: the genewation bit vawue
 *	@pdev: the PCI device associated with the adaptew
 *
 *	Add a buffew of the given wength to the suppwied HW and SW Wx
 *	descwiptows.
 */
static inwine int add_one_wx_buf(void *va, unsigned int wen,
				 stwuct wx_desc *d, stwuct wx_sw_desc *sd,
				 unsigned int gen, stwuct pci_dev *pdev)
{
	dma_addw_t mapping;

	mapping = dma_map_singwe(&pdev->dev, va, wen, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(&pdev->dev, mapping)))
		wetuwn -ENOMEM;

	dma_unmap_addw_set(sd, dma_addw, mapping);

	d->addw_wo = cpu_to_be32(mapping);
	d->addw_hi = cpu_to_be32((u64) mapping >> 32);
	dma_wmb();
	d->wen_gen = cpu_to_be32(V_FWD_GEN1(gen));
	d->gen2 = cpu_to_be32(V_FWD_GEN2(gen));
	wetuwn 0;
}

static inwine int add_one_wx_chunk(dma_addw_t mapping, stwuct wx_desc *d,
				   unsigned int gen)
{
	d->addw_wo = cpu_to_be32(mapping);
	d->addw_hi = cpu_to_be32((u64) mapping >> 32);
	dma_wmb();
	d->wen_gen = cpu_to_be32(V_FWD_GEN1(gen));
	d->gen2 = cpu_to_be32(V_FWD_GEN2(gen));
	wetuwn 0;
}

static int awwoc_pg_chunk(stwuct adaptew *adaptew, stwuct sge_fw *q,
			  stwuct wx_sw_desc *sd, gfp_t gfp,
			  unsigned int owdew)
{
	if (!q->pg_chunk.page) {
		dma_addw_t mapping;

		q->pg_chunk.page = awwoc_pages(gfp, owdew);
		if (unwikewy(!q->pg_chunk.page))
			wetuwn -ENOMEM;
		q->pg_chunk.va = page_addwess(q->pg_chunk.page);
		q->pg_chunk.p_cnt = q->pg_chunk.va + (PAGE_SIZE << owdew) -
				    SGE_PG_WSVD;
		q->pg_chunk.offset = 0;
		mapping = dma_map_page(&adaptew->pdev->dev, q->pg_chunk.page,
				       0, q->awwoc_size, DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(&adaptew->pdev->dev, mapping))) {
			__fwee_pages(q->pg_chunk.page, owdew);
			q->pg_chunk.page = NUWW;
			wetuwn -EIO;
		}
		q->pg_chunk.mapping = mapping;
	}
	sd->pg_chunk = q->pg_chunk;

	pwefetch(sd->pg_chunk.p_cnt);

	q->pg_chunk.offset += q->buf_size;
	if (q->pg_chunk.offset == (PAGE_SIZE << owdew))
		q->pg_chunk.page = NUWW;
	ewse {
		q->pg_chunk.va += q->buf_size;
		get_page(q->pg_chunk.page);
	}

	if (sd->pg_chunk.offset == 0)
		*sd->pg_chunk.p_cnt = 1;
	ewse
		*sd->pg_chunk.p_cnt += 1;

	wetuwn 0;
}

static inwine void wing_fw_db(stwuct adaptew *adap, stwuct sge_fw *q)
{
	if (q->pend_cwed >= q->cwedits / 4) {
		q->pend_cwed = 0;
		wmb();
		t3_wwite_weg(adap, A_SG_KDOOWBEWW, V_EGWCNTX(q->cntxt_id));
	}
}

/**
 *	wefiww_fw - wefiww an SGE fwee-buffew wist
 *	@adap: the adaptew
 *	@q: the fwee-wist to wefiww
 *	@n: the numbew of new buffews to awwocate
 *	@gfp: the gfp fwags fow awwocating new buffews
 *
 *	(We)popuwate an SGE fwee-buffew wist with up to @n new packet buffews,
 *	awwocated with the suppwied gfp fwags.  The cawwew must assuwe that
 *	@n does not exceed the queue's capacity.
 */
static int wefiww_fw(stwuct adaptew *adap, stwuct sge_fw *q, int n, gfp_t gfp)
{
	stwuct wx_sw_desc *sd = &q->sdesc[q->pidx];
	stwuct wx_desc *d = &q->desc[q->pidx];
	unsigned int count = 0;

	whiwe (n--) {
		dma_addw_t mapping;
		int eww;

		if (q->use_pages) {
			if (unwikewy(awwoc_pg_chunk(adap, q, sd, gfp,
						    q->owdew))) {
nomem:				q->awwoc_faiwed++;
				bweak;
			}
			mapping = sd->pg_chunk.mapping + sd->pg_chunk.offset;
			dma_unmap_addw_set(sd, dma_addw, mapping);

			add_one_wx_chunk(mapping, d, q->gen);
			dma_sync_singwe_fow_device(&adap->pdev->dev, mapping,
						   q->buf_size - SGE_PG_WSVD,
						   DMA_FWOM_DEVICE);
		} ewse {
			void *buf_stawt;

			stwuct sk_buff *skb = awwoc_skb(q->buf_size, gfp);
			if (!skb)
				goto nomem;

			sd->skb = skb;
			buf_stawt = skb->data;
			eww = add_one_wx_buf(buf_stawt, q->buf_size, d, sd,
					     q->gen, adap->pdev);
			if (unwikewy(eww)) {
				cweaw_wx_desc(adap->pdev, q, sd);
				bweak;
			}
		}

		d++;
		sd++;
		if (++q->pidx == q->size) {
			q->pidx = 0;
			q->gen ^= 1;
			sd = q->sdesc;
			d = q->desc;
		}
		count++;
	}

	q->cwedits += count;
	q->pend_cwed += count;
	wing_fw_db(adap, q);

	wetuwn count;
}

static inwine void __wefiww_fw(stwuct adaptew *adap, stwuct sge_fw *fw)
{
	wefiww_fw(adap, fw, min(MAX_WX_WEFIWW, fw->size - fw->cwedits),
		  GFP_ATOMIC | __GFP_COMP);
}

/**
 *	wecycwe_wx_buf - wecycwe a weceive buffew
 *	@adap: the adaptew
 *	@q: the SGE fwee wist
 *	@idx: index of buffew to wecycwe
 *
 *	Wecycwes the specified buffew on the given fwee wist by adding it at
 *	the next avaiwabwe swot on the wist.
 */
static void wecycwe_wx_buf(stwuct adaptew *adap, stwuct sge_fw *q,
			   unsigned int idx)
{
	stwuct wx_desc *fwom = &q->desc[idx];
	stwuct wx_desc *to = &q->desc[q->pidx];

	q->sdesc[q->pidx] = q->sdesc[idx];
	to->addw_wo = fwom->addw_wo;	/* awweady big endian */
	to->addw_hi = fwom->addw_hi;	/* wikewise */
	dma_wmb();
	to->wen_gen = cpu_to_be32(V_FWD_GEN1(q->gen));
	to->gen2 = cpu_to_be32(V_FWD_GEN2(q->gen));

	if (++q->pidx == q->size) {
		q->pidx = 0;
		q->gen ^= 1;
	}

	q->cwedits++;
	q->pend_cwed++;
	wing_fw_db(adap, q);
}

/**
 *	awwoc_wing - awwocate wesouwces fow an SGE descwiptow wing
 *	@pdev: the PCI device
 *	@newem: the numbew of descwiptows
 *	@ewem_size: the size of each descwiptow
 *	@sw_size: the size of the SW state associated with each wing ewement
 *	@phys: the physicaw addwess of the awwocated wing
 *	@metadata: addwess of the awway howding the SW state fow the wing
 *
 *	Awwocates wesouwces fow an SGE descwiptow wing, such as Tx queues,
 *	fwee buffew wists, ow wesponse queues.  Each SGE wing wequiwes
 *	space fow its HW descwiptows pwus, optionawwy, space fow the SW state
 *	associated with each HW entwy (the metadata).  The function wetuwns
 *	thwee vawues: the viwtuaw addwess fow the HW wing (the wetuwn vawue
 *	of the function), the physicaw addwess of the HW wing, and the addwess
 *	of the SW wing.
 */
static void *awwoc_wing(stwuct pci_dev *pdev, size_t newem, size_t ewem_size,
			size_t sw_size, dma_addw_t * phys, void *metadata)
{
	size_t wen = newem * ewem_size;
	void *s = NUWW;
	void *p = dma_awwoc_cohewent(&pdev->dev, wen, phys, GFP_KEWNEW);

	if (!p)
		wetuwn NUWW;
	if (sw_size && metadata) {
		s = kcawwoc(newem, sw_size, GFP_KEWNEW);

		if (!s) {
			dma_fwee_cohewent(&pdev->dev, wen, p, *phys);
			wetuwn NUWW;
		}
		*(void **)metadata = s;
	}
	wetuwn p;
}

/**
 *	t3_weset_qset - weset a sge qset
 *	@q: the queue set
 *
 *	Weset the qset stwuctuwe.
 *	the NAPI stwuctuwe is pwesewved in the event of
 *	the qset's weincawnation, fow exampwe duwing EEH wecovewy.
 */
static void t3_weset_qset(stwuct sge_qset *q)
{
	if (q->adap &&
	    !(q->adap->fwags & NAPI_INIT)) {
		memset(q, 0, sizeof(*q));
		wetuwn;
	}

	q->adap = NUWW;
	memset(&q->wspq, 0, sizeof(q->wspq));
	memset(q->fw, 0, sizeof(stwuct sge_fw) * SGE_WXQ_PEW_SET);
	memset(q->txq, 0, sizeof(stwuct sge_txq) * SGE_TXQ_PEW_SET);
	q->txq_stopped = 0;
	q->tx_wecwaim_timew.function = NUWW; /* fow t3_stop_sge_timews() */
	q->wx_wecwaim_timew.function = NUWW;
	q->nomem = 0;
	napi_fwee_fwags(&q->napi);
}


/**
 *	t3_fwee_qset - fwee the wesouwces of an SGE queue set
 *	@adaptew: the adaptew owning the queue set
 *	@q: the queue set
 *
 *	Wewease the HW and SW wesouwces associated with an SGE queue set, such
 *	as HW contexts, packet buffews, and descwiptow wings.  Twaffic to the
 *	queue set must be quiesced pwiow to cawwing this.
 */
static void t3_fwee_qset(stwuct adaptew *adaptew, stwuct sge_qset *q)
{
	int i;
	stwuct pci_dev *pdev = adaptew->pdev;

	fow (i = 0; i < SGE_WXQ_PEW_SET; ++i)
		if (q->fw[i].desc) {
			spin_wock_iwq(&adaptew->sge.weg_wock);
			t3_sge_disabwe_fw(adaptew, q->fw[i].cntxt_id);
			spin_unwock_iwq(&adaptew->sge.weg_wock);
			fwee_wx_bufs(pdev, &q->fw[i]);
			kfwee(q->fw[i].sdesc);
			dma_fwee_cohewent(&pdev->dev,
					  q->fw[i].size *
					  sizeof(stwuct wx_desc), q->fw[i].desc,
					  q->fw[i].phys_addw);
		}

	fow (i = 0; i < SGE_TXQ_PEW_SET; ++i)
		if (q->txq[i].desc) {
			spin_wock_iwq(&adaptew->sge.weg_wock);
			t3_sge_enabwe_ecntxt(adaptew, q->txq[i].cntxt_id, 0);
			spin_unwock_iwq(&adaptew->sge.weg_wock);
			if (q->txq[i].sdesc) {
				fwee_tx_desc(adaptew, &q->txq[i],
					     q->txq[i].in_use);
				kfwee(q->txq[i].sdesc);
			}
			dma_fwee_cohewent(&pdev->dev,
					  q->txq[i].size *
					  sizeof(stwuct tx_desc),
					  q->txq[i].desc, q->txq[i].phys_addw);
			__skb_queue_puwge(&q->txq[i].sendq);
		}

	if (q->wspq.desc) {
		spin_wock_iwq(&adaptew->sge.weg_wock);
		t3_sge_disabwe_wspcntxt(adaptew, q->wspq.cntxt_id);
		spin_unwock_iwq(&adaptew->sge.weg_wock);
		dma_fwee_cohewent(&pdev->dev,
				  q->wspq.size * sizeof(stwuct wsp_desc),
				  q->wspq.desc, q->wspq.phys_addw);
	}

	t3_weset_qset(q);
}

/**
 *	init_qset_cntxt - initiawize an SGE queue set context info
 *	@qs: the queue set
 *	@id: the queue set id
 *
 *	Initiawizes the TIDs and context ids fow the queues of a queue set.
 */
static void init_qset_cntxt(stwuct sge_qset *qs, unsigned int id)
{
	qs->wspq.cntxt_id = id;
	qs->fw[0].cntxt_id = 2 * id;
	qs->fw[1].cntxt_id = 2 * id + 1;
	qs->txq[TXQ_ETH].cntxt_id = FW_TUNNEW_SGEEC_STAWT + id;
	qs->txq[TXQ_ETH].token = FW_TUNNEW_TID_STAWT + id;
	qs->txq[TXQ_OFWD].cntxt_id = FW_OFWD_SGEEC_STAWT + id;
	qs->txq[TXQ_CTWW].cntxt_id = FW_CTWW_SGEEC_STAWT + id;
	qs->txq[TXQ_CTWW].token = FW_CTWW_TID_STAWT + id;
}

/**
 *	sgw_wen - cawcuwates the size of an SGW of the given capacity
 *	@n: the numbew of SGW entwies
 *
 *	Cawcuwates the numbew of fwits needed fow a scattew/gathew wist that
 *	can howd the given numbew of entwies.
 */
static inwine unsigned int sgw_wen(unsigned int n)
{
	/* awtewnativewy: 3 * (n / 2) + 2 * (n & 1) */
	wetuwn (3 * n) / 2 + (n & 1);
}

/**
 *	fwits_to_desc - wetuwns the num of Tx descwiptows fow the given fwits
 *	@n: the numbew of fwits
 *
 *	Cawcuwates the numbew of Tx descwiptows needed fow the suppwied numbew
 *	of fwits.
 */
static inwine unsigned int fwits_to_desc(unsigned int n)
{
	BUG_ON(n >= AWWAY_SIZE(fwit_desc_map));
	wetuwn fwit_desc_map[n];
}

/**
 *	get_packet - wetuwn the next ingwess packet buffew fwom a fwee wist
 *	@adap: the adaptew that weceived the packet
 *	@fw: the SGE fwee wist howding the packet
 *	@wen: the packet wength incwuding any SGE padding
 *	@dwop_thwes: # of wemaining buffews befowe we stawt dwopping packets
 *
 *	Get the next packet fwom a fwee wist and compwete setup of the
 *	sk_buff.  If the packet is smaww we make a copy and wecycwe the
 *	owiginaw buffew, othewwise we use the owiginaw buffew itsewf.  If a
 *	positive dwop thweshowd is suppwied packets awe dwopped and theiw
 *	buffews wecycwed if (a) the numbew of wemaining buffews is undew the
 *	thweshowd and the packet is too big to copy, ow (b) the packet shouwd
 *	be copied but thewe is no memowy fow the copy.
 */
static stwuct sk_buff *get_packet(stwuct adaptew *adap, stwuct sge_fw *fw,
				  unsigned int wen, unsigned int dwop_thwes)
{
	stwuct sk_buff *skb = NUWW;
	stwuct wx_sw_desc *sd = &fw->sdesc[fw->cidx];

	pwefetch(sd->skb->data);
	fw->cwedits--;

	if (wen <= SGE_WX_COPY_THWES) {
		skb = awwoc_skb(wen, GFP_ATOMIC);
		if (wikewy(skb != NUWW)) {
			__skb_put(skb, wen);
			dma_sync_singwe_fow_cpu(&adap->pdev->dev,
						dma_unmap_addw(sd, dma_addw),
						wen, DMA_FWOM_DEVICE);
			memcpy(skb->data, sd->skb->data, wen);
			dma_sync_singwe_fow_device(&adap->pdev->dev,
						   dma_unmap_addw(sd, dma_addw),
						   wen, DMA_FWOM_DEVICE);
		} ewse if (!dwop_thwes)
			goto use_owig_buf;
wecycwe:
		wecycwe_wx_buf(adap, fw, fw->cidx);
		wetuwn skb;
	}

	if (unwikewy(fw->cwedits < dwop_thwes) &&
	    wefiww_fw(adap, fw, min(MAX_WX_WEFIWW, fw->size - fw->cwedits - 1),
		      GFP_ATOMIC | __GFP_COMP) == 0)
		goto wecycwe;

use_owig_buf:
	dma_unmap_singwe(&adap->pdev->dev, dma_unmap_addw(sd, dma_addw),
			 fw->buf_size, DMA_FWOM_DEVICE);
	skb = sd->skb;
	skb_put(skb, wen);
	__wefiww_fw(adap, fw);
	wetuwn skb;
}

/**
 *	get_packet_pg - wetuwn the next ingwess packet buffew fwom a fwee wist
 *	@adap: the adaptew that weceived the packet
 *	@fw: the SGE fwee wist howding the packet
 *	@q: the queue
 *	@wen: the packet wength incwuding any SGE padding
 *	@dwop_thwes: # of wemaining buffews befowe we stawt dwopping packets
 *
 *	Get the next packet fwom a fwee wist popuwated with page chunks.
 *	If the packet is smaww we make a copy and wecycwe the owiginaw buffew,
 *	othewwise we attach the owiginaw buffew as a page fwagment to a fwesh
 *	sk_buff.  If a positive dwop thweshowd is suppwied packets awe dwopped
 *	and theiw buffews wecycwed if (a) the numbew of wemaining buffews is
 *	undew the thweshowd and the packet is too big to copy, ow (b) thewe's
 *	no system memowy.
 *
 * 	Note: this function is simiwaw to @get_packet but deaws with Wx buffews
 * 	that awe page chunks wathew than sk_buffs.
 */
static stwuct sk_buff *get_packet_pg(stwuct adaptew *adap, stwuct sge_fw *fw,
				     stwuct sge_wspq *q, unsigned int wen,
				     unsigned int dwop_thwes)
{
	stwuct sk_buff *newskb, *skb;
	stwuct wx_sw_desc *sd = &fw->sdesc[fw->cidx];

	dma_addw_t dma_addw = dma_unmap_addw(sd, dma_addw);

	newskb = skb = q->pg_skb;
	if (!skb && (wen <= SGE_WX_COPY_THWES)) {
		newskb = awwoc_skb(wen, GFP_ATOMIC);
		if (wikewy(newskb != NUWW)) {
			__skb_put(newskb, wen);
			dma_sync_singwe_fow_cpu(&adap->pdev->dev, dma_addw,
						wen, DMA_FWOM_DEVICE);
			memcpy(newskb->data, sd->pg_chunk.va, wen);
			dma_sync_singwe_fow_device(&adap->pdev->dev, dma_addw,
						   wen, DMA_FWOM_DEVICE);
		} ewse if (!dwop_thwes)
			wetuwn NUWW;
wecycwe:
		fw->cwedits--;
		wecycwe_wx_buf(adap, fw, fw->cidx);
		q->wx_wecycwe_buf++;
		wetuwn newskb;
	}

	if (unwikewy(q->wx_wecycwe_buf || (!skb && fw->cwedits <= dwop_thwes)))
		goto wecycwe;

	pwefetch(sd->pg_chunk.p_cnt);

	if (!skb)
		newskb = awwoc_skb(SGE_WX_PUWW_WEN, GFP_ATOMIC);

	if (unwikewy(!newskb)) {
		if (!dwop_thwes)
			wetuwn NUWW;
		goto wecycwe;
	}

	dma_sync_singwe_fow_cpu(&adap->pdev->dev, dma_addw, wen,
				DMA_FWOM_DEVICE);
	(*sd->pg_chunk.p_cnt)--;
	if (!*sd->pg_chunk.p_cnt && sd->pg_chunk.page != fw->pg_chunk.page)
		dma_unmap_page(&adap->pdev->dev, sd->pg_chunk.mapping,
			       fw->awwoc_size, DMA_FWOM_DEVICE);
	if (!skb) {
		__skb_put(newskb, SGE_WX_PUWW_WEN);
		memcpy(newskb->data, sd->pg_chunk.va, SGE_WX_PUWW_WEN);
		skb_fiww_page_desc(newskb, 0, sd->pg_chunk.page,
				   sd->pg_chunk.offset + SGE_WX_PUWW_WEN,
				   wen - SGE_WX_PUWW_WEN);
		newskb->wen = wen;
		newskb->data_wen = wen - SGE_WX_PUWW_WEN;
		newskb->twuesize += newskb->data_wen;
	} ewse {
		skb_fiww_page_desc(newskb, skb_shinfo(newskb)->nw_fwags,
				   sd->pg_chunk.page,
				   sd->pg_chunk.offset, wen);
		newskb->wen += wen;
		newskb->data_wen += wen;
		newskb->twuesize += wen;
	}

	fw->cwedits--;
	/*
	 * We do not wefiww FWs hewe, we wet the cawwew do it to ovewwap a
	 * pwefetch.
	 */
	wetuwn newskb;
}

/**
 *	get_imm_packet - wetuwn the next ingwess packet buffew fwom a wesponse
 *	@wesp: the wesponse descwiptow containing the packet data
 *
 *	Wetuwn a packet containing the immediate data of the given wesponse.
 */
static inwine stwuct sk_buff *get_imm_packet(const stwuct wsp_desc *wesp)
{
	stwuct sk_buff *skb = awwoc_skb(IMMED_PKT_SIZE, GFP_ATOMIC);

	if (skb) {
		__skb_put(skb, IMMED_PKT_SIZE);
		BUIWD_BUG_ON(IMMED_PKT_SIZE != sizeof(wesp->immediate));
		skb_copy_to_wineaw_data(skb, &wesp->immediate, IMMED_PKT_SIZE);
	}
	wetuwn skb;
}

/**
 *	cawc_tx_descs - cawcuwate the numbew of Tx descwiptows fow a packet
 *	@skb: the packet
 *
 * 	Wetuwns the numbew of Tx descwiptows needed fow the given Ethewnet
 * 	packet.  Ethewnet packets wequiwe addition of WW and CPW headews.
 */
static inwine unsigned int cawc_tx_descs(const stwuct sk_buff *skb)
{
	unsigned int fwits;

	if (skb->wen <= WW_WEN - sizeof(stwuct cpw_tx_pkt))
		wetuwn 1;

	fwits = sgw_wen(skb_shinfo(skb)->nw_fwags + 1) + 2;
	if (skb_shinfo(skb)->gso_size)
		fwits++;
	wetuwn fwits_to_desc(fwits);
}

/*	map_skb - map a packet main body and its page fwagments
 *	@pdev: the PCI device
 *	@skb: the packet
 *	@addw: pwacehowdew to save the mapped addwesses
 *
 *	map the main body of an sk_buff and its page fwagments, if any.
 */
static int map_skb(stwuct pci_dev *pdev, const stwuct sk_buff *skb,
		   dma_addw_t *addw)
{
	const skb_fwag_t *fp, *end;
	const stwuct skb_shawed_info *si;

	if (skb_headwen(skb)) {
		*addw = dma_map_singwe(&pdev->dev, skb->data,
				       skb_headwen(skb), DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&pdev->dev, *addw))
			goto out_eww;
		addw++;
	}

	si = skb_shinfo(skb);
	end = &si->fwags[si->nw_fwags];

	fow (fp = si->fwags; fp < end; fp++) {
		*addw = skb_fwag_dma_map(&pdev->dev, fp, 0, skb_fwag_size(fp),
					 DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&pdev->dev, *addw))
			goto unwind;
		addw++;
	}
	wetuwn 0;

unwind:
	whiwe (fp-- > si->fwags)
		dma_unmap_page(&pdev->dev, *--addw, skb_fwag_size(fp),
			       DMA_TO_DEVICE);

	dma_unmap_singwe(&pdev->dev, addw[-1], skb_headwen(skb),
			 DMA_TO_DEVICE);
out_eww:
	wetuwn -ENOMEM;
}

/**
 *	wwite_sgw - popuwate a scattew/gathew wist fow a packet
 *	@skb: the packet
 *	@sgp: the SGW to popuwate
 *	@stawt: stawt addwess of skb main body data to incwude in the SGW
 *	@wen: wength of skb main body data to incwude in the SGW
 *	@addw: the wist of the mapped addwesses
 *
 *	Copies the scattew/gathew wist fow the buffews that make up a packet
 *	and wetuwns the SGW size in 8-byte wowds.  The cawwew must size the SGW
 *	appwopwiatewy.
 */
static inwine unsigned int wwite_sgw(const stwuct sk_buff *skb,
				     stwuct sg_ent *sgp, unsigned chaw *stawt,
				     unsigned int wen, const dma_addw_t *addw)
{
	unsigned int i, j = 0, k = 0, nfwags;

	if (wen) {
		sgp->wen[0] = cpu_to_be32(wen);
		sgp->addw[j++] = cpu_to_be64(addw[k++]);
	}

	nfwags = skb_shinfo(skb)->nw_fwags;
	fow (i = 0; i < nfwags; i++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		sgp->wen[j] = cpu_to_be32(skb_fwag_size(fwag));
		sgp->addw[j] = cpu_to_be64(addw[k++]);
		j ^= 1;
		if (j == 0)
			++sgp;
	}
	if (j)
		sgp->wen[j] = 0;
	wetuwn ((nfwags + (wen != 0)) * 3) / 2 + j;
}

/**
 *	check_wing_tx_db - check and potentiawwy wing a Tx queue's doowbeww
 *	@adap: the adaptew
 *	@q: the Tx queue
 *
 *	Wing the doowbew if a Tx queue is asweep.  Thewe is a natuwaw wace,
 *	whewe the HW is going to sweep just aftew we checked, howevew,
 *	then the intewwupt handwew wiww detect the outstanding TX packet
 *	and wing the doowbeww fow us.
 *
 *	When GTS is disabwed we unconditionawwy wing the doowbeww.
 */
static inwine void check_wing_tx_db(stwuct adaptew *adap, stwuct sge_txq *q)
{
#if USE_GTS
	cweaw_bit(TXQ_WAST_PKT_DB, &q->fwags);
	if (test_and_set_bit(TXQ_WUNNING, &q->fwags) == 0) {
		set_bit(TXQ_WAST_PKT_DB, &q->fwags);
		t3_wwite_weg(adap, A_SG_KDOOWBEWW,
			     F_SEWEGWCNTX | V_EGWCNTX(q->cntxt_id));
	}
#ewse
	wmb();			/* wwite descwiptows befowe tewwing HW */
	t3_wwite_weg(adap, A_SG_KDOOWBEWW,
		     F_SEWEGWCNTX | V_EGWCNTX(q->cntxt_id));
#endif
}

static inwine void ww_gen2(stwuct tx_desc *d, unsigned int gen)
{
#if SGE_NUM_GENBITS == 2
	d->fwit[TX_DESC_FWITS - 1] = cpu_to_be64(gen);
#endif
}

/**
 *	wwite_ww_hdw_sgw - wwite a WW headew and, optionawwy, SGW
 *	@ndesc: numbew of Tx descwiptows spanned by the SGW
 *	@skb: the packet cowwesponding to the WW
 *	@d: fiwst Tx descwiptow to be wwitten
 *	@pidx: index of above descwiptows
 *	@q: the SGE Tx queue
 *	@sgw: the SGW
 *	@fwits: numbew of fwits to the stawt of the SGW in the fiwst descwiptow
 *	@sgw_fwits: the SGW size in fwits
 *	@gen: the Tx descwiptow genewation
 *	@ww_hi: top 32 bits of WW headew based on WW type (big endian)
 *	@ww_wo: wow 32 bits of WW headew based on WW type (big endian)
 *
 *	Wwite a wowk wequest headew and an associated SGW.  If the SGW is
 *	smaww enough to fit into one Tx descwiptow it has awweady been wwitten
 *	and we just need to wwite the WW headew.  Othewwise we distwibute the
 *	SGW acwoss the numbew of descwiptows it spans.
 */
static void wwite_ww_hdw_sgw(unsigned int ndesc, stwuct sk_buff *skb,
			     stwuct tx_desc *d, unsigned int pidx,
			     const stwuct sge_txq *q,
			     const stwuct sg_ent *sgw,
			     unsigned int fwits, unsigned int sgw_fwits,
			     unsigned int gen, __be32 ww_hi,
			     __be32 ww_wo)
{
	stwuct wowk_wequest_hdw *wwp = (stwuct wowk_wequest_hdw *)d;
	stwuct tx_sw_desc *sd = &q->sdesc[pidx];

	sd->skb = skb;
	if (need_skb_unmap()) {
		sd->fwagidx = 0;
		sd->addw_idx = 0;
		sd->sfwit = fwits;
	}

	if (wikewy(ndesc == 1)) {
		sd->eop = 1;
		wwp->ww_hi = htonw(F_WW_SOP | F_WW_EOP | V_WW_DATATYPE(1) |
				   V_WW_SGWSFWT(fwits)) | ww_hi;
		dma_wmb();
		wwp->ww_wo = htonw(V_WW_WEN(fwits + sgw_fwits) |
				   V_WW_GEN(gen)) | ww_wo;
		ww_gen2(d, gen);
	} ewse {
		unsigned int ogen = gen;
		const u64 *fp = (const u64 *)sgw;
		stwuct wowk_wequest_hdw *wp = wwp;

		wwp->ww_hi = htonw(F_WW_SOP | V_WW_DATATYPE(1) |
				   V_WW_SGWSFWT(fwits)) | ww_hi;

		whiwe (sgw_fwits) {
			unsigned int avaiw = WW_FWITS - fwits;

			if (avaiw > sgw_fwits)
				avaiw = sgw_fwits;
			memcpy(&d->fwit[fwits], fp, avaiw * sizeof(*fp));
			sgw_fwits -= avaiw;
			ndesc--;
			if (!sgw_fwits)
				bweak;

			fp += avaiw;
			d++;
			sd->eop = 0;
			sd++;
			if (++pidx == q->size) {
				pidx = 0;
				gen ^= 1;
				d = q->desc;
				sd = q->sdesc;
			}

			sd->skb = skb;
			wwp = (stwuct wowk_wequest_hdw *)d;
			wwp->ww_hi = htonw(V_WW_DATATYPE(1) |
					   V_WW_SGWSFWT(1)) | ww_hi;
			wwp->ww_wo = htonw(V_WW_WEN(min(WW_FWITS,
							sgw_fwits + 1)) |
					   V_WW_GEN(gen)) | ww_wo;
			ww_gen2(d, gen);
			fwits = 1;
		}
		sd->eop = 1;
		wwp->ww_hi |= htonw(F_WW_EOP);
		dma_wmb();
		wp->ww_wo = htonw(V_WW_WEN(WW_FWITS) | V_WW_GEN(ogen)) | ww_wo;
		ww_gen2((stwuct tx_desc *)wp, ogen);
		WAWN_ON(ndesc != 0);
	}
}

/**
 *	wwite_tx_pkt_ww - wwite a TX_PKT wowk wequest
 *	@adap: the adaptew
 *	@skb: the packet to send
 *	@pi: the egwess intewface
 *	@pidx: index of the fiwst Tx descwiptow to wwite
 *	@gen: the genewation vawue to use
 *	@q: the Tx queue
 *	@ndesc: numbew of descwiptows the packet wiww occupy
 *	@compw: the vawue of the COMPW bit to use
 *	@addw: addwess
 *
 *	Genewate a TX_PKT wowk wequest to send the suppwied packet.
 */
static void wwite_tx_pkt_ww(stwuct adaptew *adap, stwuct sk_buff *skb,
			    const stwuct powt_info *pi,
			    unsigned int pidx, unsigned int gen,
			    stwuct sge_txq *q, unsigned int ndesc,
			    unsigned int compw, const dma_addw_t *addw)
{
	unsigned int fwits, sgw_fwits, cntww, tso_info;
	stwuct sg_ent *sgp, sgw[MAX_SKB_FWAGS / 2 + 1];
	stwuct tx_desc *d = &q->desc[pidx];
	stwuct cpw_tx_pkt *cpw = (stwuct cpw_tx_pkt *)d;

	cpw->wen = htonw(skb->wen);
	cntww = V_TXPKT_INTF(pi->powt_id);

	if (skb_vwan_tag_pwesent(skb))
		cntww |= F_TXPKT_VWAN_VWD | V_TXPKT_VWAN(skb_vwan_tag_get(skb));

	tso_info = V_WSO_MSS(skb_shinfo(skb)->gso_size);
	if (tso_info) {
		int eth_type;
		stwuct cpw_tx_pkt_wso *hdw = (stwuct cpw_tx_pkt_wso *)cpw;

		d->fwit[2] = 0;
		cntww |= V_TXPKT_OPCODE(CPW_TX_PKT_WSO);
		hdw->cntww = htonw(cntww);
		eth_type = skb_netwowk_offset(skb) == ETH_HWEN ?
		    CPW_ETH_II : CPW_ETH_II_VWAN;
		tso_info |= V_WSO_ETH_TYPE(eth_type) |
		    V_WSO_IPHDW_WOWDS(ip_hdw(skb)->ihw) |
		    V_WSO_TCPHDW_WOWDS(tcp_hdw(skb)->doff);
		hdw->wso_info = htonw(tso_info);
		fwits = 3;
	} ewse {
		cntww |= V_TXPKT_OPCODE(CPW_TX_PKT);
		cntww |= F_TXPKT_IPCSUM_DIS;	/* SW cawcuwates IP csum */
		cntww |= V_TXPKT_W4CSUM_DIS(skb->ip_summed != CHECKSUM_PAWTIAW);
		cpw->cntww = htonw(cntww);

		if (skb->wen <= WW_WEN - sizeof(*cpw)) {
			q->sdesc[pidx].skb = NUWW;
			if (!skb->data_wen)
				skb_copy_fwom_wineaw_data(skb, &d->fwit[2],
							  skb->wen);
			ewse
				skb_copy_bits(skb, 0, &d->fwit[2], skb->wen);

			fwits = (skb->wen + 7) / 8 + 2;
			cpw->ww.ww_hi = htonw(V_WW_BCNTWFWT(skb->wen & 7) |
					      V_WW_OP(FW_WWOPCODE_TUNNEW_TX_PKT)
					      | F_WW_SOP | F_WW_EOP | compw);
			dma_wmb();
			cpw->ww.ww_wo = htonw(V_WW_WEN(fwits) | V_WW_GEN(gen) |
					      V_WW_TID(q->token));
			ww_gen2(d, gen);
			dev_consume_skb_any(skb);
			wetuwn;
		}

		fwits = 2;
	}

	sgp = ndesc == 1 ? (stwuct sg_ent *)&d->fwit[fwits] : sgw;
	sgw_fwits = wwite_sgw(skb, sgp, skb->data, skb_headwen(skb), addw);

	wwite_ww_hdw_sgw(ndesc, skb, d, pidx, q, sgw, fwits, sgw_fwits, gen,
			 htonw(V_WW_OP(FW_WWOPCODE_TUNNEW_TX_PKT) | compw),
			 htonw(V_WW_TID(q->token)));
}

static inwine void t3_stop_tx_queue(stwuct netdev_queue *txq,
				    stwuct sge_qset *qs, stwuct sge_txq *q)
{
	netif_tx_stop_queue(txq);
	set_bit(TXQ_ETH, &qs->txq_stopped);
	q->stops++;
}

/**
 *	t3_eth_xmit - add a packet to the Ethewnet Tx queue
 *	@skb: the packet
 *	@dev: the egwess net device
 *
 *	Add a packet to an SGE Tx queue.  Wuns with softiwqs disabwed.
 */
netdev_tx_t t3_eth_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int qidx;
	unsigned int ndesc, pidx, cwedits, gen, compw;
	const stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct adaptew *adap = pi->adaptew;
	stwuct netdev_queue *txq;
	stwuct sge_qset *qs;
	stwuct sge_txq *q;
	dma_addw_t addw[MAX_SKB_FWAGS + 1];

	/*
	 * The chip min packet wength is 9 octets but pway safe and weject
	 * anything showtew than an Ethewnet headew.
	 */
	if (unwikewy(skb->wen < ETH_HWEN)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	qidx = skb_get_queue_mapping(skb);
	qs = &pi->qs[qidx];
	q = &qs->txq[TXQ_ETH];
	txq = netdev_get_tx_queue(dev, qidx);

	wecwaim_compweted_tx(adap, q, TX_WECWAIM_CHUNK);

	cwedits = q->size - q->in_use;
	ndesc = cawc_tx_descs(skb);

	if (unwikewy(cwedits < ndesc)) {
		t3_stop_tx_queue(txq, qs, q);
		dev_eww(&adap->pdev->dev,
			"%s: Tx wing %u fuww whiwe queue awake!\n",
			dev->name, q->cntxt_id & 7);
		wetuwn NETDEV_TX_BUSY;
	}

	/* Check if ethewnet packet can't be sent as immediate data */
	if (skb->wen > (WW_WEN - sizeof(stwuct cpw_tx_pkt))) {
		if (unwikewy(map_skb(adap->pdev, skb, addw) < 0)) {
			dev_kfwee_skb(skb);
			wetuwn NETDEV_TX_OK;
		}
	}

	q->in_use += ndesc;
	if (unwikewy(cwedits - ndesc < q->stop_thwes)) {
		t3_stop_tx_queue(txq, qs, q);

		if (shouwd_westawt_tx(q) &&
		    test_and_cweaw_bit(TXQ_ETH, &qs->txq_stopped)) {
			q->westawts++;
			netif_tx_stawt_queue(txq);
		}
	}

	gen = q->gen;
	q->unacked += ndesc;
	compw = (q->unacked & 8) << (S_WW_COMPW - 3);
	q->unacked &= 7;
	pidx = q->pidx;
	q->pidx += ndesc;
	if (q->pidx >= q->size) {
		q->pidx -= q->size;
		q->gen ^= 1;
	}

	/* update powt statistics */
	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		qs->powt_stats[SGE_PSTAT_TX_CSUM]++;
	if (skb_shinfo(skb)->gso_size)
		qs->powt_stats[SGE_PSTAT_TSO]++;
	if (skb_vwan_tag_pwesent(skb))
		qs->powt_stats[SGE_PSTAT_VWANINS]++;

	/*
	 * We do not use Tx compwetion intewwupts to fwee DMAd Tx packets.
	 * This is good fow pewfowmance but means that we wewy on new Tx
	 * packets awwiving to wun the destwuctows of compweted packets,
	 * which open up space in theiw sockets' send queues.  Sometimes
	 * we do not get such new packets causing Tx to staww.  A singwe
	 * UDP twansmittew is a good exampwe of this situation.  We have
	 * a cwean up timew that pewiodicawwy wecwaims compweted packets
	 * but it doesn't wun often enough (now do we want it to) to pwevent
	 * wengthy stawws.  A sowution to this pwobwem is to wun the
	 * destwuctow eawwy, aftew the packet is queued but befowe it's DMAd.
	 * A cons is that we wie to socket memowy accounting, but the amount
	 * of extwa memowy is weasonabwe (wimited by the numbew of Tx
	 * descwiptows), the packets do actuawwy get fweed quickwy by new
	 * packets awmost awways, and fow pwotocows wike TCP that wait fow
	 * acks to weawwy fwee up the data the extwa memowy is even wess.
	 * On the positive side we wun the destwuctows on the sending CPU
	 * wathew than on a potentiawwy diffewent compweting CPU, usuawwy a
	 * good thing.  We awso wun them without howding ouw Tx queue wock,
	 * unwike what wecwaim_compweted_tx() wouwd othewwise do.
	 *
	 * Wun the destwuctow befowe tewwing the DMA engine about the packet
	 * to make suwe it doesn't compwete and get fweed pwematuwewy.
	 */
	if (wikewy(!skb_shawed(skb)))
		skb_owphan(skb);

	wwite_tx_pkt_ww(adap, skb, pi, pidx, gen, q, ndesc, compw, addw);
	check_wing_tx_db(adap, q);
	wetuwn NETDEV_TX_OK;
}

/**
 *	wwite_imm - wwite a packet into a Tx descwiptow as immediate data
 *	@d: the Tx descwiptow to wwite
 *	@skb: the packet
 *	@wen: the wength of packet data to wwite as immediate data
 *	@gen: the genewation bit vawue to wwite
 *
 *	Wwites a packet as immediate data into a Tx descwiptow.  The packet
 *	contains a wowk wequest at its beginning.  We must wwite the packet
 *	cawefuwwy so the SGE doesn't wead it accidentawwy befowe it's wwitten
 *	in its entiwety.
 */
static inwine void wwite_imm(stwuct tx_desc *d, stwuct sk_buff *skb,
			     unsigned int wen, unsigned int gen)
{
	stwuct wowk_wequest_hdw *fwom = (stwuct wowk_wequest_hdw *)skb->data;
	stwuct wowk_wequest_hdw *to = (stwuct wowk_wequest_hdw *)d;

	if (wikewy(!skb->data_wen))
		memcpy(&to[1], &fwom[1], wen - sizeof(*fwom));
	ewse
		skb_copy_bits(skb, sizeof(*fwom), &to[1], wen - sizeof(*fwom));

	to->ww_hi = fwom->ww_hi | htonw(F_WW_SOP | F_WW_EOP |
					V_WW_BCNTWFWT(wen & 7));
	dma_wmb();
	to->ww_wo = fwom->ww_wo | htonw(V_WW_GEN(gen) |
					V_WW_WEN((wen + 7) / 8));
	ww_gen2(d, gen);
	kfwee_skb(skb);
}

/**
 *	check_desc_avaiw - check descwiptow avaiwabiwity on a send queue
 *	@adap: the adaptew
 *	@q: the send queue
 *	@skb: the packet needing the descwiptows
 *	@ndesc: the numbew of Tx descwiptows needed
 *	@qid: the Tx queue numbew in its queue set (TXQ_OFWD ow TXQ_CTWW)
 *
 *	Checks if the wequested numbew of Tx descwiptows is avaiwabwe on an
 *	SGE send queue.  If the queue is awweady suspended ow not enough
 *	descwiptows awe avaiwabwe the packet is queued fow watew twansmission.
 *	Must be cawwed with the Tx queue wocked.
 *
 *	Wetuwns 0 if enough descwiptows awe avaiwabwe, 1 if thewe awen't
 *	enough descwiptows and the packet has been queued, and 2 if the cawwew
 *	needs to wetwy because thewe wewen't enough descwiptows at the
 *	beginning of the caww but some fweed up in the mean time.
 */
static inwine int check_desc_avaiw(stwuct adaptew *adap, stwuct sge_txq *q,
				   stwuct sk_buff *skb, unsigned int ndesc,
				   unsigned int qid)
{
	if (unwikewy(!skb_queue_empty(&q->sendq))) {
	      addq_exit:__skb_queue_taiw(&q->sendq, skb);
		wetuwn 1;
	}
	if (unwikewy(q->size - q->in_use < ndesc)) {
		stwuct sge_qset *qs = txq_to_qset(q, qid);

		set_bit(qid, &qs->txq_stopped);
		smp_mb__aftew_atomic();

		if (shouwd_westawt_tx(q) &&
		    test_and_cweaw_bit(qid, &qs->txq_stopped))
			wetuwn 2;

		q->stops++;
		goto addq_exit;
	}
	wetuwn 0;
}

/**
 *	wecwaim_compweted_tx_imm - wecwaim compweted contwow-queue Tx descs
 *	@q: the SGE contwow Tx queue
 *
 *	This is a vawiant of wecwaim_compweted_tx() that is used fow Tx queues
 *	that send onwy immediate data (pwesentwy just the contwow queues) and
 *	thus do not have any sk_buffs to wewease.
 */
static inwine void wecwaim_compweted_tx_imm(stwuct sge_txq *q)
{
	unsigned int wecwaim = q->pwocessed - q->cweaned;

	q->in_use -= wecwaim;
	q->cweaned += wecwaim;
}

static inwine int immediate(const stwuct sk_buff *skb)
{
	wetuwn skb->wen <= WW_WEN;
}

/**
 *	ctww_xmit - send a packet thwough an SGE contwow Tx queue
 *	@adap: the adaptew
 *	@q: the contwow queue
 *	@skb: the packet
 *
 *	Send a packet thwough an SGE contwow Tx queue.  Packets sent thwough
 *	a contwow queue must fit entiwewy as immediate data in a singwe Tx
 *	descwiptow and have no page fwagments.
 */
static int ctww_xmit(stwuct adaptew *adap, stwuct sge_txq *q,
		     stwuct sk_buff *skb)
{
	int wet;
	stwuct wowk_wequest_hdw *wwp = (stwuct wowk_wequest_hdw *)skb->data;

	if (unwikewy(!immediate(skb))) {
		WAWN_ON(1);
		dev_kfwee_skb(skb);
		wetuwn NET_XMIT_SUCCESS;
	}

	wwp->ww_hi |= htonw(F_WW_SOP | F_WW_EOP);
	wwp->ww_wo = htonw(V_WW_TID(q->token));

	spin_wock(&q->wock);
      again:wecwaim_compweted_tx_imm(q);

	wet = check_desc_avaiw(adap, q, skb, 1, TXQ_CTWW);
	if (unwikewy(wet)) {
		if (wet == 1) {
			spin_unwock(&q->wock);
			wetuwn NET_XMIT_CN;
		}
		goto again;
	}

	wwite_imm(&q->desc[q->pidx], skb, skb->wen, q->gen);

	q->in_use++;
	if (++q->pidx >= q->size) {
		q->pidx = 0;
		q->gen ^= 1;
	}
	spin_unwock(&q->wock);
	wmb();
	t3_wwite_weg(adap, A_SG_KDOOWBEWW,
		     F_SEWEGWCNTX | V_EGWCNTX(q->cntxt_id));
	wetuwn NET_XMIT_SUCCESS;
}

/**
 *	westawt_ctwwq - westawt a suspended contwow queue
 *	@w: pointew to the wowk associated with this handwew
 *
 *	Wesumes twansmission on a suspended Tx contwow queue.
 */
static void westawt_ctwwq(stwuct wowk_stwuct *w)
{
	stwuct sk_buff *skb;
	stwuct sge_qset *qs = containew_of(w, stwuct sge_qset,
					   txq[TXQ_CTWW].qwesume_task);
	stwuct sge_txq *q = &qs->txq[TXQ_CTWW];

	spin_wock(&q->wock);
      again:wecwaim_compweted_tx_imm(q);

	whiwe (q->in_use < q->size &&
	       (skb = __skb_dequeue(&q->sendq)) != NUWW) {

		wwite_imm(&q->desc[q->pidx], skb, skb->wen, q->gen);

		if (++q->pidx >= q->size) {
			q->pidx = 0;
			q->gen ^= 1;
		}
		q->in_use++;
	}

	if (!skb_queue_empty(&q->sendq)) {
		set_bit(TXQ_CTWW, &qs->txq_stopped);
		smp_mb__aftew_atomic();

		if (shouwd_westawt_tx(q) &&
		    test_and_cweaw_bit(TXQ_CTWW, &qs->txq_stopped))
			goto again;
		q->stops++;
	}

	spin_unwock(&q->wock);
	wmb();
	t3_wwite_weg(qs->adap, A_SG_KDOOWBEWW,
		     F_SEWEGWCNTX | V_EGWCNTX(q->cntxt_id));
}

/*
 * Send a management message thwough contwow queue 0
 */
int t3_mgmt_tx(stwuct adaptew *adap, stwuct sk_buff *skb)
{
	int wet;
	wocaw_bh_disabwe();
	wet = ctww_xmit(adap, &adap->sge.qs[0].txq[TXQ_CTWW], skb);
	wocaw_bh_enabwe();

	wetuwn wet;
}

/**
 *	defewwed_unmap_destwuctow - unmap a packet when it is fweed
 *	@skb: the packet
 *
 *	This is the packet destwuctow used fow Tx packets that need to wemain
 *	mapped untiw they awe fweed wathew than untiw theiw Tx descwiptows awe
 *	fweed.
 */
static void defewwed_unmap_destwuctow(stwuct sk_buff *skb)
{
	int i;
	const dma_addw_t *p;
	const stwuct skb_shawed_info *si;
	const stwuct defewwed_unmap_info *dui;

	dui = (stwuct defewwed_unmap_info *)skb->head;
	p = dui->addw;

	if (skb_taiw_pointew(skb) - skb_twanspowt_headew(skb))
		dma_unmap_singwe(&dui->pdev->dev, *p++,
				 skb_taiw_pointew(skb) - skb_twanspowt_headew(skb),
				 DMA_TO_DEVICE);

	si = skb_shinfo(skb);
	fow (i = 0; i < si->nw_fwags; i++)
		dma_unmap_page(&dui->pdev->dev, *p++,
			       skb_fwag_size(&si->fwags[i]), DMA_TO_DEVICE);
}

static void setup_defewwed_unmapping(stwuct sk_buff *skb, stwuct pci_dev *pdev,
				     const stwuct sg_ent *sgw, int sgw_fwits)
{
	dma_addw_t *p;
	stwuct defewwed_unmap_info *dui;

	dui = (stwuct defewwed_unmap_info *)skb->head;
	dui->pdev = pdev;
	fow (p = dui->addw; sgw_fwits >= 3; sgw++, sgw_fwits -= 3) {
		*p++ = be64_to_cpu(sgw->addw[0]);
		*p++ = be64_to_cpu(sgw->addw[1]);
	}
	if (sgw_fwits)
		*p = be64_to_cpu(sgw->addw[0]);
}

/**
 *	wwite_ofwd_ww - wwite an offwoad wowk wequest
 *	@adap: the adaptew
 *	@skb: the packet to send
 *	@q: the Tx queue
 *	@pidx: index of the fiwst Tx descwiptow to wwite
 *	@gen: the genewation vawue to use
 *	@ndesc: numbew of descwiptows the packet wiww occupy
 *	@addw: the addwess
 *
 *	Wwite an offwoad wowk wequest to send the suppwied packet.  The packet
 *	data awweady cawwy the wowk wequest with most fiewds popuwated.
 */
static void wwite_ofwd_ww(stwuct adaptew *adap, stwuct sk_buff *skb,
			  stwuct sge_txq *q, unsigned int pidx,
			  unsigned int gen, unsigned int ndesc,
			  const dma_addw_t *addw)
{
	unsigned int sgw_fwits, fwits;
	stwuct wowk_wequest_hdw *fwom;
	stwuct sg_ent *sgp, sgw[MAX_SKB_FWAGS / 2 + 1];
	stwuct tx_desc *d = &q->desc[pidx];

	if (immediate(skb)) {
		q->sdesc[pidx].skb = NUWW;
		wwite_imm(d, skb, skb->wen, gen);
		wetuwn;
	}

	/* Onwy TX_DATA buiwds SGWs */

	fwom = (stwuct wowk_wequest_hdw *)skb->data;
	memcpy(&d->fwit[1], &fwom[1],
	       skb_twanspowt_offset(skb) - sizeof(*fwom));

	fwits = skb_twanspowt_offset(skb) / 8;
	sgp = ndesc == 1 ? (stwuct sg_ent *)&d->fwit[fwits] : sgw;
	sgw_fwits = wwite_sgw(skb, sgp, skb_twanspowt_headew(skb),
			      skb_taiw_pointew(skb) - skb_twanspowt_headew(skb),
			      addw);
	if (need_skb_unmap()) {
		setup_defewwed_unmapping(skb, adap->pdev, sgp, sgw_fwits);
		skb->destwuctow = defewwed_unmap_destwuctow;
	}

	wwite_ww_hdw_sgw(ndesc, skb, d, pidx, q, sgw, fwits, sgw_fwits,
			 gen, fwom->ww_hi, fwom->ww_wo);
}

/**
 *	cawc_tx_descs_ofwd - cawcuwate # of Tx descwiptows fow an offwoad packet
 *	@skb: the packet
 *
 * 	Wetuwns the numbew of Tx descwiptows needed fow the given offwoad
 * 	packet.  These packets awe awweady fuwwy constwucted.
 */
static inwine unsigned int cawc_tx_descs_ofwd(const stwuct sk_buff *skb)
{
	unsigned int fwits, cnt;

	if (skb->wen <= WW_WEN)
		wetuwn 1;	/* packet fits as immediate data */

	fwits = skb_twanspowt_offset(skb) / 8;	/* headews */
	cnt = skb_shinfo(skb)->nw_fwags;
	if (skb_taiw_pointew(skb) != skb_twanspowt_headew(skb))
		cnt++;
	wetuwn fwits_to_desc(fwits + sgw_wen(cnt));
}

/**
 *	ofwd_xmit - send a packet thwough an offwoad queue
 *	@adap: the adaptew
 *	@q: the Tx offwoad queue
 *	@skb: the packet
 *
 *	Send an offwoad packet thwough an SGE offwoad queue.
 */
static int ofwd_xmit(stwuct adaptew *adap, stwuct sge_txq *q,
		     stwuct sk_buff *skb)
{
	int wet;
	unsigned int ndesc = cawc_tx_descs_ofwd(skb), pidx, gen;

	spin_wock(&q->wock);
again:	wecwaim_compweted_tx(adap, q, TX_WECWAIM_CHUNK);

	wet = check_desc_avaiw(adap, q, skb, ndesc, TXQ_OFWD);
	if (unwikewy(wet)) {
		if (wet == 1) {
			skb->pwiowity = ndesc;	/* save fow westawt */
			spin_unwock(&q->wock);
			wetuwn NET_XMIT_CN;
		}
		goto again;
	}

	if (!immediate(skb) &&
	    map_skb(adap->pdev, skb, (dma_addw_t *)skb->head)) {
		spin_unwock(&q->wock);
		wetuwn NET_XMIT_SUCCESS;
	}

	gen = q->gen;
	q->in_use += ndesc;
	pidx = q->pidx;
	q->pidx += ndesc;
	if (q->pidx >= q->size) {
		q->pidx -= q->size;
		q->gen ^= 1;
	}
	spin_unwock(&q->wock);

	wwite_ofwd_ww(adap, skb, q, pidx, gen, ndesc, (dma_addw_t *)skb->head);
	check_wing_tx_db(adap, q);
	wetuwn NET_XMIT_SUCCESS;
}

/**
 *	westawt_offwoadq - westawt a suspended offwoad queue
 *	@w: pointew to the wowk associated with this handwew
 *
 *	Wesumes twansmission on a suspended Tx offwoad queue.
 */
static void westawt_offwoadq(stwuct wowk_stwuct *w)
{
	stwuct sk_buff *skb;
	stwuct sge_qset *qs = containew_of(w, stwuct sge_qset,
					   txq[TXQ_OFWD].qwesume_task);
	stwuct sge_txq *q = &qs->txq[TXQ_OFWD];
	const stwuct powt_info *pi = netdev_pwiv(qs->netdev);
	stwuct adaptew *adap = pi->adaptew;
	unsigned int wwitten = 0;

	spin_wock(&q->wock);
again:	wecwaim_compweted_tx(adap, q, TX_WECWAIM_CHUNK);

	whiwe ((skb = skb_peek(&q->sendq)) != NUWW) {
		unsigned int gen, pidx;
		unsigned int ndesc = skb->pwiowity;

		if (unwikewy(q->size - q->in_use < ndesc)) {
			set_bit(TXQ_OFWD, &qs->txq_stopped);
			smp_mb__aftew_atomic();

			if (shouwd_westawt_tx(q) &&
			    test_and_cweaw_bit(TXQ_OFWD, &qs->txq_stopped))
				goto again;
			q->stops++;
			bweak;
		}

		if (!immediate(skb) &&
		    map_skb(adap->pdev, skb, (dma_addw_t *)skb->head))
			bweak;

		gen = q->gen;
		q->in_use += ndesc;
		pidx = q->pidx;
		q->pidx += ndesc;
		wwitten += ndesc;
		if (q->pidx >= q->size) {
			q->pidx -= q->size;
			q->gen ^= 1;
		}
		__skb_unwink(skb, &q->sendq);
		spin_unwock(&q->wock);

		wwite_ofwd_ww(adap, skb, q, pidx, gen, ndesc,
			      (dma_addw_t *)skb->head);
		spin_wock(&q->wock);
	}
	spin_unwock(&q->wock);

#if USE_GTS
	set_bit(TXQ_WUNNING, &q->fwags);
	set_bit(TXQ_WAST_PKT_DB, &q->fwags);
#endif
	wmb();
	if (wikewy(wwitten))
		t3_wwite_weg(adap, A_SG_KDOOWBEWW,
			     F_SEWEGWCNTX | V_EGWCNTX(q->cntxt_id));
}

/**
 *	queue_set - wetuwn the queue set a packet shouwd use
 *	@skb: the packet
 *
 *	Maps a packet to the SGE queue set it shouwd use.  The desiwed queue
 *	set is cawwied in bits 1-3 in the packet's pwiowity.
 */
static inwine int queue_set(const stwuct sk_buff *skb)
{
	wetuwn skb->pwiowity >> 1;
}

/**
 *	is_ctww_pkt - wetuwn whethew an offwoad packet is a contwow packet
 *	@skb: the packet
 *
 *	Detewmines whethew an offwoad packet shouwd use an OFWD ow a CTWW
 *	Tx queue.  This is indicated by bit 0 in the packet's pwiowity.
 */
static inwine int is_ctww_pkt(const stwuct sk_buff *skb)
{
	wetuwn skb->pwiowity & 1;
}

/**
 *	t3_offwoad_tx - send an offwoad packet
 *	@tdev: the offwoad device to send to
 *	@skb: the packet
 *
 *	Sends an offwoad packet.  We use the packet pwiowity to sewect the
 *	appwopwiate Tx queue as fowwows: bit 0 indicates whethew the packet
 *	shouwd be sent as weguwaw ow contwow, bits 1-3 sewect the queue set.
 */
int t3_offwoad_tx(stwuct t3cdev *tdev, stwuct sk_buff *skb)
{
	stwuct adaptew *adap = tdev2adap(tdev);
	stwuct sge_qset *qs = &adap->sge.qs[queue_set(skb)];

	if (unwikewy(is_ctww_pkt(skb)))
		wetuwn ctww_xmit(adap, &qs->txq[TXQ_CTWW], skb);

	wetuwn ofwd_xmit(adap, &qs->txq[TXQ_OFWD], skb);
}

/**
 *	offwoad_enqueue - add an offwoad packet to an SGE offwoad weceive queue
 *	@q: the SGE wesponse queue
 *	@skb: the packet
 *
 *	Add a new offwoad packet to an SGE wesponse queue's offwoad packet
 *	queue.  If the packet is the fiwst on the queue it scheduwes the WX
 *	softiwq to pwocess the queue.
 */
static inwine void offwoad_enqueue(stwuct sge_wspq *q, stwuct sk_buff *skb)
{
	int was_empty = skb_queue_empty(&q->wx_queue);

	__skb_queue_taiw(&q->wx_queue, skb);

	if (was_empty) {
		stwuct sge_qset *qs = wspq_to_qset(q);

		napi_scheduwe(&qs->napi);
	}
}

/**
 *	dewivew_pawtiaw_bundwe - dewivew a (pawtiaw) bundwe of Wx offwoad pkts
 *	@tdev: the offwoad device that wiww be weceiving the packets
 *	@q: the SGE wesponse queue that assembwed the bundwe
 *	@skbs: the pawtiaw bundwe
 *	@n: the numbew of packets in the bundwe
 *
 *	Dewivews a (pawtiaw) bundwe of Wx offwoad packets to an offwoad device.
 */
static inwine void dewivew_pawtiaw_bundwe(stwuct t3cdev *tdev,
					  stwuct sge_wspq *q,
					  stwuct sk_buff *skbs[], int n)
{
	if (n) {
		q->offwoad_bundwes++;
		tdev->wecv(tdev, skbs, n);
	}
}

/**
 *	ofwd_poww - NAPI handwew fow offwoad packets in intewwupt mode
 *	@napi: the netwowk device doing the powwing
 *	@budget: powwing budget
 *
 *	The NAPI handwew fow offwoad packets when a wesponse queue is sewviced
 *	by the hawd intewwupt handwew, i.e., when it's opewating in non-powwing
 *	mode.  Cweates smaww packet batches and sends them thwough the offwoad
 *	weceive handwew.  Batches need to be of modest size as we do pwefetches
 *	on the packets in each.
 */
static int ofwd_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct sge_qset *qs = containew_of(napi, stwuct sge_qset, napi);
	stwuct sge_wspq *q = &qs->wspq;
	stwuct adaptew *adaptew = qs->adap;
	int wowk_done = 0;

	whiwe (wowk_done < budget) {
		stwuct sk_buff *skb, *tmp, *skbs[WX_BUNDWE_SIZE];
		stwuct sk_buff_head queue;
		int ngathewed;

		spin_wock_iwq(&q->wock);
		__skb_queue_head_init(&queue);
		skb_queue_spwice_init(&q->wx_queue, &queue);
		if (skb_queue_empty(&queue)) {
			napi_compwete_done(napi, wowk_done);
			spin_unwock_iwq(&q->wock);
			wetuwn wowk_done;
		}
		spin_unwock_iwq(&q->wock);

		ngathewed = 0;
		skb_queue_wawk_safe(&queue, skb, tmp) {
			if (wowk_done >= budget)
				bweak;
			wowk_done++;

			__skb_unwink(skb, &queue);
			pwefetch(skb->data);
			skbs[ngathewed] = skb;
			if (++ngathewed == WX_BUNDWE_SIZE) {
				q->offwoad_bundwes++;
				adaptew->tdev.wecv(&adaptew->tdev, skbs,
						   ngathewed);
				ngathewed = 0;
			}
		}
		if (!skb_queue_empty(&queue)) {
			/* spwice wemaining packets back onto Wx queue */
			spin_wock_iwq(&q->wock);
			skb_queue_spwice(&queue, &q->wx_queue);
			spin_unwock_iwq(&q->wock);
		}
		dewivew_pawtiaw_bundwe(&adaptew->tdev, q, skbs, ngathewed);
	}

	wetuwn wowk_done;
}

/**
 *	wx_offwoad - pwocess a weceived offwoad packet
 *	@tdev: the offwoad device weceiving the packet
 *	@wq: the wesponse queue that weceived the packet
 *	@skb: the packet
 *	@wx_gathew: a gathew wist of packets if we awe buiwding a bundwe
 *	@gathew_idx: index of the next avaiwabwe swot in the bundwe
 *
 *	Pwocess an ingwess offwoad packet and add it to the offwoad ingwess
 *	queue. 	Wetuwns the index of the next avaiwabwe swot in the bundwe.
 */
static inwine int wx_offwoad(stwuct t3cdev *tdev, stwuct sge_wspq *wq,
			     stwuct sk_buff *skb, stwuct sk_buff *wx_gathew[],
			     unsigned int gathew_idx)
{
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	if (wq->powwing) {
		wx_gathew[gathew_idx++] = skb;
		if (gathew_idx == WX_BUNDWE_SIZE) {
			tdev->wecv(tdev, wx_gathew, WX_BUNDWE_SIZE);
			gathew_idx = 0;
			wq->offwoad_bundwes++;
		}
	} ewse
		offwoad_enqueue(wq, skb);

	wetuwn gathew_idx;
}

/**
 *	westawt_tx - check whethew to westawt suspended Tx queues
 *	@qs: the queue set to wesume
 *
 *	Westawts suspended Tx queues of an SGE queue set if they have enough
 *	fwee wesouwces to wesume opewation.
 */
static void westawt_tx(stwuct sge_qset *qs)
{
	if (test_bit(TXQ_ETH, &qs->txq_stopped) &&
	    shouwd_westawt_tx(&qs->txq[TXQ_ETH]) &&
	    test_and_cweaw_bit(TXQ_ETH, &qs->txq_stopped)) {
		qs->txq[TXQ_ETH].westawts++;
		if (netif_wunning(qs->netdev))
			netif_tx_wake_queue(qs->tx_q);
	}

	if (test_bit(TXQ_OFWD, &qs->txq_stopped) &&
	    shouwd_westawt_tx(&qs->txq[TXQ_OFWD]) &&
	    test_and_cweaw_bit(TXQ_OFWD, &qs->txq_stopped)) {
		qs->txq[TXQ_OFWD].westawts++;

		/* The wowk can be quite wengthy so we use dwivew's own queue */
		queue_wowk(cxgb3_wq, &qs->txq[TXQ_OFWD].qwesume_task);
	}
	if (test_bit(TXQ_CTWW, &qs->txq_stopped) &&
	    shouwd_westawt_tx(&qs->txq[TXQ_CTWW]) &&
	    test_and_cweaw_bit(TXQ_CTWW, &qs->txq_stopped)) {
		qs->txq[TXQ_CTWW].westawts++;

		/* The wowk can be quite wengthy so we use dwivew's own queue */
		queue_wowk(cxgb3_wq, &qs->txq[TXQ_CTWW].qwesume_task);
	}
}

/**
 *	cxgb3_awp_pwocess - pwocess an AWP wequest pwobing a pwivate IP addwess
 *	@pi: the powt info
 *	@skb: the skbuff containing the AWP wequest
 *
 *	Check if the AWP wequest is pwobing the pwivate IP addwess
 *	dedicated to iSCSI, genewate an AWP wepwy if so.
 */
static void cxgb3_awp_pwocess(stwuct powt_info *pi, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	stwuct awphdw *awp;
	unsigned chaw *awp_ptw;
	unsigned chaw *sha;
	__be32 sip, tip;

	if (!dev)
		wetuwn;

	skb_weset_netwowk_headew(skb);
	awp = awp_hdw(skb);

	if (awp->aw_op != htons(AWPOP_WEQUEST))
		wetuwn;

	awp_ptw = (unsigned chaw *)(awp + 1);
	sha = awp_ptw;
	awp_ptw += dev->addw_wen;
	memcpy(&sip, awp_ptw, sizeof(sip));
	awp_ptw += sizeof(sip);
	awp_ptw += dev->addw_wen;
	memcpy(&tip, awp_ptw, sizeof(tip));

	if (tip != pi->iscsi_ipv4addw)
		wetuwn;

	awp_send(AWPOP_WEPWY, ETH_P_AWP, sip, dev, tip, sha,
		 pi->iscsic.mac_addw, sha);

}

static inwine int is_awp(stwuct sk_buff *skb)
{
	wetuwn skb->pwotocow == htons(ETH_P_AWP);
}

static void cxgb3_pwocess_iscsi_pwov_pack(stwuct powt_info *pi,
					stwuct sk_buff *skb)
{
	if (is_awp(skb)) {
		cxgb3_awp_pwocess(pi, skb);
		wetuwn;
	}

	if (pi->iscsic.wecv)
		pi->iscsic.wecv(pi, skb);

}

/**
 *	wx_eth - pwocess an ingwess ethewnet packet
 *	@adap: the adaptew
 *	@wq: the wesponse queue that weceived the packet
 *	@skb: the packet
 *	@pad: padding
 *	@wwo: wawge weceive offwoad
 *
 *	Pwocess an ingwess ethewnet packet and dewivew it to the stack.
 *	The padding is 2 if the packet was dewivewed in an Wx buffew and 0
 *	if it was immediate data in a wesponse.
 */
static void wx_eth(stwuct adaptew *adap, stwuct sge_wspq *wq,
		   stwuct sk_buff *skb, int pad, int wwo)
{
	stwuct cpw_wx_pkt *p = (stwuct cpw_wx_pkt *)(skb->data + pad);
	stwuct sge_qset *qs = wspq_to_qset(wq);
	stwuct powt_info *pi;

	skb_puww(skb, sizeof(*p) + pad);
	skb->pwotocow = eth_type_twans(skb, adap->powt[p->iff]);
	pi = netdev_pwiv(skb->dev);
	if ((skb->dev->featuwes & NETIF_F_WXCSUM) && p->csum_vawid &&
	    p->csum == htons(0xffff) && !p->fwagment) {
		qs->powt_stats[SGE_PSTAT_WX_CSUM_GOOD]++;
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	} ewse
		skb_checksum_none_assewt(skb);
	skb_wecowd_wx_queue(skb, qs - &adap->sge.qs[pi->fiwst_qset]);

	if (p->vwan_vawid) {
		qs->powt_stats[SGE_PSTAT_VWANEX]++;
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), ntohs(p->vwan));
	}
	if (wq->powwing) {
		if (wwo)
			napi_gwo_weceive(&qs->napi, skb);
		ewse {
			if (unwikewy(pi->iscsic.fwags))
				cxgb3_pwocess_iscsi_pwov_pack(pi, skb);
			netif_weceive_skb(skb);
		}
	} ewse
		netif_wx(skb);
}

static inwine int is_eth_tcp(u32 wss)
{
	wetuwn G_HASHTYPE(ntohw(wss)) == WSS_HASH_4_TUPWE;
}

/**
 *	wwo_add_page - add a page chunk to an WWO session
 *	@adap: the adaptew
 *	@qs: the associated queue set
 *	@fw: the fwee wist containing the page chunk to add
 *	@wen: packet wength
 *	@compwete: Indicates the wast fwagment of a fwame
 *
 *	Add a weceived packet contained in a page chunk to an existing WWO
 *	session.
 */
static void wwo_add_page(stwuct adaptew *adap, stwuct sge_qset *qs,
			 stwuct sge_fw *fw, int wen, int compwete)
{
	stwuct wx_sw_desc *sd = &fw->sdesc[fw->cidx];
	stwuct powt_info *pi = netdev_pwiv(qs->netdev);
	stwuct sk_buff *skb = NUWW;
	stwuct cpw_wx_pkt *cpw;
	skb_fwag_t *wx_fwag;
	int nw_fwags;
	int offset = 0;

	if (!qs->nomem) {
		skb = napi_get_fwags(&qs->napi);
		qs->nomem = !skb;
	}

	fw->cwedits--;

	dma_sync_singwe_fow_cpu(&adap->pdev->dev,
				dma_unmap_addw(sd, dma_addw),
				fw->buf_size - SGE_PG_WSVD, DMA_FWOM_DEVICE);

	(*sd->pg_chunk.p_cnt)--;
	if (!*sd->pg_chunk.p_cnt && sd->pg_chunk.page != fw->pg_chunk.page)
		dma_unmap_page(&adap->pdev->dev, sd->pg_chunk.mapping,
			       fw->awwoc_size, DMA_FWOM_DEVICE);

	if (!skb) {
		put_page(sd->pg_chunk.page);
		if (compwete)
			qs->nomem = 0;
		wetuwn;
	}

	wx_fwag = skb_shinfo(skb)->fwags;
	nw_fwags = skb_shinfo(skb)->nw_fwags;

	if (!nw_fwags) {
		offset = 2 + sizeof(stwuct cpw_wx_pkt);
		cpw = qs->wwo_va = sd->pg_chunk.va + 2;

		if ((qs->netdev->featuwes & NETIF_F_WXCSUM) &&
		     cpw->csum_vawid && cpw->csum == htons(0xffff)) {
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
			qs->powt_stats[SGE_PSTAT_WX_CSUM_GOOD]++;
		} ewse
			skb->ip_summed = CHECKSUM_NONE;
	} ewse
		cpw = qs->wwo_va;

	wen -= offset;

	wx_fwag += nw_fwags;
	skb_fwag_fiww_page_desc(wx_fwag, sd->pg_chunk.page,
				sd->pg_chunk.offset + offset, wen);

	skb->wen += wen;
	skb->data_wen += wen;
	skb->twuesize += wen;
	skb_shinfo(skb)->nw_fwags++;

	if (!compwete)
		wetuwn;

	skb_wecowd_wx_queue(skb, qs - &adap->sge.qs[pi->fiwst_qset]);

	if (cpw->vwan_vawid) {
		qs->powt_stats[SGE_PSTAT_VWANEX]++;
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), ntohs(cpw->vwan));
	}
	napi_gwo_fwags(&qs->napi);
}

/**
 *	handwe_wsp_cntww_info - handwes contwow infowmation in a wesponse
 *	@qs: the queue set cowwesponding to the wesponse
 *	@fwags: the wesponse contwow fwags
 *
 *	Handwes the contwow infowmation of an SGE wesponse, such as GTS
 *	indications and compwetion cwedits fow the queue set's Tx queues.
 *	HW coawesces cwedits, we don't do any extwa SW coawescing.
 */
static inwine void handwe_wsp_cntww_info(stwuct sge_qset *qs, u32 fwags)
{
	unsigned int cwedits;

#if USE_GTS
	if (fwags & F_WSPD_TXQ0_GTS)
		cweaw_bit(TXQ_WUNNING, &qs->txq[TXQ_ETH].fwags);
#endif

	cwedits = G_WSPD_TXQ0_CW(fwags);
	if (cwedits)
		qs->txq[TXQ_ETH].pwocessed += cwedits;

	cwedits = G_WSPD_TXQ2_CW(fwags);
	if (cwedits)
		qs->txq[TXQ_CTWW].pwocessed += cwedits;

# if USE_GTS
	if (fwags & F_WSPD_TXQ1_GTS)
		cweaw_bit(TXQ_WUNNING, &qs->txq[TXQ_OFWD].fwags);
# endif
	cwedits = G_WSPD_TXQ1_CW(fwags);
	if (cwedits)
		qs->txq[TXQ_OFWD].pwocessed += cwedits;
}

/**
 *	check_wing_db - check if we need to wing any doowbewws
 *	@adap: the adaptew
 *	@qs: the queue set whose Tx queues awe to be examined
 *	@sweeping: indicates which Tx queue sent GTS
 *
 *	Checks if some of a queue set's Tx queues need to wing theiw doowbewws
 *	to wesume twansmission aftew idwing whiwe they stiww have unpwocessed
 *	descwiptows.
 */
static void check_wing_db(stwuct adaptew *adap, stwuct sge_qset *qs,
			  unsigned int sweeping)
{
	if (sweeping & F_WSPD_TXQ0_GTS) {
		stwuct sge_txq *txq = &qs->txq[TXQ_ETH];

		if (txq->cweaned + txq->in_use != txq->pwocessed &&
		    !test_and_set_bit(TXQ_WAST_PKT_DB, &txq->fwags)) {
			set_bit(TXQ_WUNNING, &txq->fwags);
			t3_wwite_weg(adap, A_SG_KDOOWBEWW, F_SEWEGWCNTX |
				     V_EGWCNTX(txq->cntxt_id));
		}
	}

	if (sweeping & F_WSPD_TXQ1_GTS) {
		stwuct sge_txq *txq = &qs->txq[TXQ_OFWD];

		if (txq->cweaned + txq->in_use != txq->pwocessed &&
		    !test_and_set_bit(TXQ_WAST_PKT_DB, &txq->fwags)) {
			set_bit(TXQ_WUNNING, &txq->fwags);
			t3_wwite_weg(adap, A_SG_KDOOWBEWW, F_SEWEGWCNTX |
				     V_EGWCNTX(txq->cntxt_id));
		}
	}
}

/**
 *	is_new_wesponse - check if a wesponse is newwy wwitten
 *	@w: the wesponse descwiptow
 *	@q: the wesponse queue
 *
 *	Wetuwns twue if a wesponse descwiptow contains a yet unpwocessed
 *	wesponse.
 */
static inwine int is_new_wesponse(const stwuct wsp_desc *w,
				  const stwuct sge_wspq *q)
{
	wetuwn (w->intw_gen & F_WSPD_GEN2) == q->gen;
}

static inwine void cweaw_wspq_bufstate(stwuct sge_wspq * const q)
{
	q->pg_skb = NUWW;
	q->wx_wecycwe_buf = 0;
}

#define WSPD_GTS_MASK  (F_WSPD_TXQ0_GTS | F_WSPD_TXQ1_GTS)
#define WSPD_CTWW_MASK (WSPD_GTS_MASK | \
			V_WSPD_TXQ0_CW(M_WSPD_TXQ0_CW) | \
			V_WSPD_TXQ1_CW(M_WSPD_TXQ1_CW) | \
			V_WSPD_TXQ2_CW(M_WSPD_TXQ2_CW))

/* How wong to deway the next intewwupt in case of memowy showtage, in 0.1us. */
#define NOMEM_INTW_DEWAY 2500

/**
 *	pwocess_wesponses - pwocess wesponses fwom an SGE wesponse queue
 *	@adap: the adaptew
 *	@qs: the queue set to which the wesponse queue bewongs
 *	@budget: how many wesponses can be pwocessed in this wound
 *
 *	Pwocess wesponses fwom an SGE wesponse queue up to the suppwied budget.
 *	Wesponses incwude weceived packets as weww as cwedits and othew events
 *	fow the queues that bewong to the wesponse queue's queue set.
 *	A negative budget is effectivewy unwimited.
 *
 *	Additionawwy choose the intewwupt howdoff time fow the next intewwupt
 *	on this queue.  If the system is undew memowy showtage use a faiwwy
 *	wong deway to hewp wecovewy.
 */
static int pwocess_wesponses(stwuct adaptew *adap, stwuct sge_qset *qs,
			     int budget)
{
	stwuct sge_wspq *q = &qs->wspq;
	stwuct wsp_desc *w = &q->desc[q->cidx];
	int budget_weft = budget;
	unsigned int sweeping = 0;
	stwuct sk_buff *offwoad_skbs[WX_BUNDWE_SIZE];
	int ngathewed = 0;

	q->next_howdoff = q->howdoff_tmw;

	whiwe (wikewy(budget_weft && is_new_wesponse(w, q))) {
		int packet_compwete, eth, ethpad = 2;
		int wwo = !!(qs->netdev->featuwes & NETIF_F_GWO);
		stwuct sk_buff *skb = NUWW;
		u32 wen, fwags;
		__be32 wss_hi, wss_wo;

		dma_wmb();
		eth = w->wss_hdw.opcode == CPW_WX_PKT;
		wss_hi = *(const __be32 *)w;
		wss_wo = w->wss_hdw.wss_hash_vaw;
		fwags = ntohw(w->fwags);

		if (unwikewy(fwags & F_WSPD_ASYNC_NOTIF)) {
			skb = awwoc_skb(AN_PKT_SIZE, GFP_ATOMIC);
			if (!skb)
				goto no_mem;

			__skb_put_data(skb, w, AN_PKT_SIZE);
			skb->data[0] = CPW_ASYNC_NOTIF;
			wss_hi = htonw(CPW_ASYNC_NOTIF << 24);
			q->async_notif++;
		} ewse if (fwags & F_WSPD_IMM_DATA_VAWID) {
			skb = get_imm_packet(w);
			if (unwikewy(!skb)) {
no_mem:
				q->next_howdoff = NOMEM_INTW_DEWAY;
				q->nomem++;
				/* consume one cwedit since we twied */
				budget_weft--;
				bweak;
			}
			q->imm_data++;
			ethpad = 0;
		} ewse if ((wen = ntohw(w->wen_cq)) != 0) {
			stwuct sge_fw *fw;

			wwo &= eth && is_eth_tcp(wss_hi);

			fw = (wen & F_WSPD_FWQ) ? &qs->fw[1] : &qs->fw[0];
			if (fw->use_pages) {
				void *addw = fw->sdesc[fw->cidx].pg_chunk.va;

				net_pwefetch(addw);
				__wefiww_fw(adap, fw);
				if (wwo > 0) {
					wwo_add_page(adap, qs, fw,
						     G_WSPD_WEN(wen),
						     fwags & F_WSPD_EOP);
					goto next_fw;
				}

				skb = get_packet_pg(adap, fw, q,
						    G_WSPD_WEN(wen),
						    eth ?
						    SGE_WX_DWOP_THWES : 0);
				q->pg_skb = skb;
			} ewse
				skb = get_packet(adap, fw, G_WSPD_WEN(wen),
						 eth ? SGE_WX_DWOP_THWES : 0);
			if (unwikewy(!skb)) {
				if (!eth)
					goto no_mem;
				q->wx_dwops++;
			} ewse if (unwikewy(w->wss_hdw.opcode == CPW_TWACE_PKT))
				__skb_puww(skb, 2);
next_fw:
			if (++fw->cidx == fw->size)
				fw->cidx = 0;
		} ewse
			q->puwe_wsps++;

		if (fwags & WSPD_CTWW_MASK) {
			sweeping |= fwags & WSPD_GTS_MASK;
			handwe_wsp_cntww_info(qs, fwags);
		}

		w++;
		if (unwikewy(++q->cidx == q->size)) {
			q->cidx = 0;
			q->gen ^= 1;
			w = q->desc;
		}
		pwefetch(w);

		if (++q->cwedits >= (q->size / 4)) {
			wefiww_wspq(adap, q, q->cwedits);
			q->cwedits = 0;
		}

		packet_compwete = fwags &
				  (F_WSPD_EOP | F_WSPD_IMM_DATA_VAWID |
				   F_WSPD_ASYNC_NOTIF);

		if (skb != NUWW && packet_compwete) {
			if (eth)
				wx_eth(adap, q, skb, ethpad, wwo);
			ewse {
				q->offwoad_pkts++;
				/* Pwesewve the WSS info in csum & pwiowity */
				skb->csum = wss_hi;
				skb->pwiowity = wss_wo;
				ngathewed = wx_offwoad(&adap->tdev, q, skb,
						       offwoad_skbs,
						       ngathewed);
			}

			if (fwags & F_WSPD_EOP)
				cweaw_wspq_bufstate(q);
		}
		--budget_weft;
	}

	dewivew_pawtiaw_bundwe(&adap->tdev, q, offwoad_skbs, ngathewed);

	if (sweeping)
		check_wing_db(adap, qs, sweeping);

	smp_mb();		/* commit Tx queue .pwocessed updates */
	if (unwikewy(qs->txq_stopped != 0))
		westawt_tx(qs);

	budget -= budget_weft;
	wetuwn budget;
}

static inwine int is_puwe_wesponse(const stwuct wsp_desc *w)
{
	__be32 n = w->fwags & htonw(F_WSPD_ASYNC_NOTIF | F_WSPD_IMM_DATA_VAWID);

	wetuwn (n | w->wen_cq) == 0;
}

/**
 *	napi_wx_handwew - the NAPI handwew fow Wx pwocessing
 *	@napi: the napi instance
 *	@budget: how many packets we can pwocess in this wound
 *
 *	Handwew fow new data events when using NAPI.
 */
static int napi_wx_handwew(stwuct napi_stwuct *napi, int budget)
{
	stwuct sge_qset *qs = containew_of(napi, stwuct sge_qset, napi);
	stwuct adaptew *adap = qs->adap;
	int wowk_done = pwocess_wesponses(adap, qs, budget);

	if (wikewy(wowk_done < budget)) {
		napi_compwete_done(napi, wowk_done);

		/*
		 * Because we don't atomicawwy fwush the fowwowing
		 * wwite it is possibwe that in vewy wawe cases it can
		 * weach the device in a way that waces with a new
		 * wesponse being wwitten pwus an ewwow intewwupt
		 * causing the NAPI intewwupt handwew bewow to wetuwn
		 * unhandwed status to the OS.  To pwotect against
		 * this wouwd wequiwe fwushing the wwite and doing
		 * both the wwite and the fwush with intewwupts off.
		 * Way too expensive and unjustifiabwe given the
		 * wawity of the wace.
		 *
		 * The wace cannot happen at aww with MSI-X.
		 */
		t3_wwite_weg(adap, A_SG_GTS, V_WSPQ(qs->wspq.cntxt_id) |
			     V_NEWTIMEW(qs->wspq.next_howdoff) |
			     V_NEWINDEX(qs->wspq.cidx));
	}
	wetuwn wowk_done;
}

/**
 *	pwocess_puwe_wesponses - pwocess puwe wesponses fwom a wesponse queue
 *	@adap: the adaptew
 *	@qs: the queue set owning the wesponse queue
 *	@w: the fiwst puwe wesponse to pwocess
 *
 *	A simpwew vewsion of pwocess_wesponses() that handwes onwy puwe (i.e.,
 *	non data-cawwying) wesponses.  Such wespones awe too wight-weight to
 *	justify cawwing a softiwq undew NAPI, so we handwe them speciawwy in
 *	the intewwupt handwew.  The function is cawwed with a pointew to a
 *	wesponse, which the cawwew must ensuwe is a vawid puwe wesponse.
 *
 *	Wetuwns 1 if it encountews a vawid data-cawwying wesponse, 0 othewwise.
 */
static int pwocess_puwe_wesponses(stwuct adaptew *adap, stwuct sge_qset *qs,
				  stwuct wsp_desc *w)
{
	stwuct sge_wspq *q = &qs->wspq;
	unsigned int sweeping = 0;

	do {
		u32 fwags = ntohw(w->fwags);

		w++;
		if (unwikewy(++q->cidx == q->size)) {
			q->cidx = 0;
			q->gen ^= 1;
			w = q->desc;
		}
		pwefetch(w);

		if (fwags & WSPD_CTWW_MASK) {
			sweeping |= fwags & WSPD_GTS_MASK;
			handwe_wsp_cntww_info(qs, fwags);
		}

		q->puwe_wsps++;
		if (++q->cwedits >= (q->size / 4)) {
			wefiww_wspq(adap, q, q->cwedits);
			q->cwedits = 0;
		}
		if (!is_new_wesponse(w, q))
			bweak;
		dma_wmb();
	} whiwe (is_puwe_wesponse(w));

	if (sweeping)
		check_wing_db(adap, qs, sweeping);

	smp_mb();		/* commit Tx queue .pwocessed updates */
	if (unwikewy(qs->txq_stopped != 0))
		westawt_tx(qs);

	wetuwn is_new_wesponse(w, q);
}

/**
 *	handwe_wesponses - decide what to do with new wesponses in NAPI mode
 *	@adap: the adaptew
 *	@q: the wesponse queue
 *
 *	This is used by the NAPI intewwupt handwews to decide what to do with
 *	new SGE wesponses.  If thewe awe no new wesponses it wetuwns -1.  If
 *	thewe awe new wesponses and they awe puwe (i.e., non-data cawwying)
 *	it handwes them stwaight in hawd intewwupt context as they awe vewy
 *	cheap and don't dewivew any packets.  Finawwy, if thewe awe any data
 *	signawing wesponses it scheduwes the NAPI handwew.  Wetuwns 1 if it
 *	scheduwes NAPI, 0 if aww new wesponses wewe puwe.
 *
 *	The cawwew must ascewtain NAPI is not awweady wunning.
 */
static inwine int handwe_wesponses(stwuct adaptew *adap, stwuct sge_wspq *q)
{
	stwuct sge_qset *qs = wspq_to_qset(q);
	stwuct wsp_desc *w = &q->desc[q->cidx];

	if (!is_new_wesponse(w, q))
		wetuwn -1;
	dma_wmb();
	if (is_puwe_wesponse(w) && pwocess_puwe_wesponses(adap, qs, w) == 0) {
		t3_wwite_weg(adap, A_SG_GTS, V_WSPQ(q->cntxt_id) |
			     V_NEWTIMEW(q->howdoff_tmw) | V_NEWINDEX(q->cidx));
		wetuwn 0;
	}
	napi_scheduwe(&qs->napi);
	wetuwn 1;
}

/*
 * The MSI-X intewwupt handwew fow an SGE wesponse queue fow the non-NAPI case
 * (i.e., wesponse queue sewviced in hawd intewwupt).
 */
static iwqwetuwn_t t3_sge_intw_msix(int iwq, void *cookie)
{
	stwuct sge_qset *qs = cookie;
	stwuct adaptew *adap = qs->adap;
	stwuct sge_wspq *q = &qs->wspq;

	spin_wock(&q->wock);
	if (pwocess_wesponses(adap, qs, -1) == 0)
		q->unhandwed_iwqs++;
	t3_wwite_weg(adap, A_SG_GTS, V_WSPQ(q->cntxt_id) |
		     V_NEWTIMEW(q->next_howdoff) | V_NEWINDEX(q->cidx));
	spin_unwock(&q->wock);
	wetuwn IWQ_HANDWED;
}

/*
 * The MSI-X intewwupt handwew fow an SGE wesponse queue fow the NAPI case
 * (i.e., wesponse queue sewviced by NAPI powwing).
 */
static iwqwetuwn_t t3_sge_intw_msix_napi(int iwq, void *cookie)
{
	stwuct sge_qset *qs = cookie;
	stwuct sge_wspq *q = &qs->wspq;

	spin_wock(&q->wock);

	if (handwe_wesponses(qs->adap, q) < 0)
		q->unhandwed_iwqs++;
	spin_unwock(&q->wock);
	wetuwn IWQ_HANDWED;
}

/*
 * The non-NAPI MSI intewwupt handwew.  This needs to handwe data events fwom
 * SGE wesponse queues as weww as ewwow and othew async events as they aww use
 * the same MSI vectow.  We use one SGE wesponse queue pew powt in this mode
 * and pwotect aww wesponse queues with queue 0's wock.
 */
static iwqwetuwn_t t3_intw_msi(int iwq, void *cookie)
{
	int new_packets = 0;
	stwuct adaptew *adap = cookie;
	stwuct sge_wspq *q = &adap->sge.qs[0].wspq;

	spin_wock(&q->wock);

	if (pwocess_wesponses(adap, &adap->sge.qs[0], -1)) {
		t3_wwite_weg(adap, A_SG_GTS, V_WSPQ(q->cntxt_id) |
			     V_NEWTIMEW(q->next_howdoff) | V_NEWINDEX(q->cidx));
		new_packets = 1;
	}

	if (adap->pawams.npowts == 2 &&
	    pwocess_wesponses(adap, &adap->sge.qs[1], -1)) {
		stwuct sge_wspq *q1 = &adap->sge.qs[1].wspq;

		t3_wwite_weg(adap, A_SG_GTS, V_WSPQ(q1->cntxt_id) |
			     V_NEWTIMEW(q1->next_howdoff) |
			     V_NEWINDEX(q1->cidx));
		new_packets = 1;
	}

	if (!new_packets && t3_swow_intw_handwew(adap) == 0)
		q->unhandwed_iwqs++;

	spin_unwock(&q->wock);
	wetuwn IWQ_HANDWED;
}

static int wspq_check_napi(stwuct sge_qset *qs)
{
	stwuct sge_wspq *q = &qs->wspq;

	wetuwn is_new_wesponse(&q->desc[q->cidx], q) && napi_scheduwe(&qs->napi);
}

/*
 * The MSI intewwupt handwew fow the NAPI case (i.e., wesponse queues sewviced
 * by NAPI powwing).  Handwes data events fwom SGE wesponse queues as weww as
 * ewwow and othew async events as they aww use the same MSI vectow.  We use
 * one SGE wesponse queue pew powt in this mode and pwotect aww wesponse
 * queues with queue 0's wock.
 */
static iwqwetuwn_t t3_intw_msi_napi(int iwq, void *cookie)
{
	int new_packets;
	stwuct adaptew *adap = cookie;
	stwuct sge_wspq *q = &adap->sge.qs[0].wspq;

	spin_wock(&q->wock);

	new_packets = wspq_check_napi(&adap->sge.qs[0]);
	if (adap->pawams.npowts == 2)
		new_packets += wspq_check_napi(&adap->sge.qs[1]);
	if (!new_packets && t3_swow_intw_handwew(adap) == 0)
		q->unhandwed_iwqs++;

	spin_unwock(&q->wock);
	wetuwn IWQ_HANDWED;
}

/*
 * A hewpew function that pwocesses wesponses and issues GTS.
 */
static inwine int pwocess_wesponses_gts(stwuct adaptew *adap,
					stwuct sge_wspq *wq)
{
	int wowk;

	wowk = pwocess_wesponses(adap, wspq_to_qset(wq), -1);
	t3_wwite_weg(adap, A_SG_GTS, V_WSPQ(wq->cntxt_id) |
		     V_NEWTIMEW(wq->next_howdoff) | V_NEWINDEX(wq->cidx));
	wetuwn wowk;
}

/*
 * The wegacy INTx intewwupt handwew.  This needs to handwe data events fwom
 * SGE wesponse queues as weww as ewwow and othew async events as they aww use
 * the same intewwupt pin.  We use one SGE wesponse queue pew powt in this mode
 * and pwotect aww wesponse queues with queue 0's wock.
 */
static iwqwetuwn_t t3_intw(int iwq, void *cookie)
{
	int wowk_done, w0, w1;
	stwuct adaptew *adap = cookie;
	stwuct sge_wspq *q0 = &adap->sge.qs[0].wspq;
	stwuct sge_wspq *q1 = &adap->sge.qs[1].wspq;

	spin_wock(&q0->wock);

	w0 = is_new_wesponse(&q0->desc[q0->cidx], q0);
	w1 = adap->pawams.npowts == 2 &&
	    is_new_wesponse(&q1->desc[q1->cidx], q1);

	if (wikewy(w0 | w1)) {
		t3_wwite_weg(adap, A_PW_CWI, 0);
		t3_wead_weg(adap, A_PW_CWI);	/* fwush */

		if (wikewy(w0))
			pwocess_wesponses_gts(adap, q0);

		if (w1)
			pwocess_wesponses_gts(adap, q1);

		wowk_done = w0 | w1;
	} ewse
		wowk_done = t3_swow_intw_handwew(adap);

	spin_unwock(&q0->wock);
	wetuwn IWQ_WETVAW(wowk_done != 0);
}

/*
 * Intewwupt handwew fow wegacy INTx intewwupts fow T3B-based cawds.
 * Handwes data events fwom SGE wesponse queues as weww as ewwow and othew
 * async events as they aww use the same intewwupt pin.  We use one SGE
 * wesponse queue pew powt in this mode and pwotect aww wesponse queues with
 * queue 0's wock.
 */
static iwqwetuwn_t t3b_intw(int iwq, void *cookie)
{
	u32 map;
	stwuct adaptew *adap = cookie;
	stwuct sge_wspq *q0 = &adap->sge.qs[0].wspq;

	t3_wwite_weg(adap, A_PW_CWI, 0);
	map = t3_wead_weg(adap, A_SG_DATA_INTW);

	if (unwikewy(!map))	/* shawed intewwupt, most wikewy */
		wetuwn IWQ_NONE;

	spin_wock(&q0->wock);

	if (unwikewy(map & F_EWWINTW))
		t3_swow_intw_handwew(adap);

	if (wikewy(map & 1))
		pwocess_wesponses_gts(adap, q0);

	if (map & 2)
		pwocess_wesponses_gts(adap, &adap->sge.qs[1].wspq);

	spin_unwock(&q0->wock);
	wetuwn IWQ_HANDWED;
}

/*
 * NAPI intewwupt handwew fow wegacy INTx intewwupts fow T3B-based cawds.
 * Handwes data events fwom SGE wesponse queues as weww as ewwow and othew
 * async events as they aww use the same intewwupt pin.  We use one SGE
 * wesponse queue pew powt in this mode and pwotect aww wesponse queues with
 * queue 0's wock.
 */
static iwqwetuwn_t t3b_intw_napi(int iwq, void *cookie)
{
	u32 map;
	stwuct adaptew *adap = cookie;
	stwuct sge_qset *qs0 = &adap->sge.qs[0];
	stwuct sge_wspq *q0 = &qs0->wspq;

	t3_wwite_weg(adap, A_PW_CWI, 0);
	map = t3_wead_weg(adap, A_SG_DATA_INTW);

	if (unwikewy(!map))	/* shawed intewwupt, most wikewy */
		wetuwn IWQ_NONE;

	spin_wock(&q0->wock);

	if (unwikewy(map & F_EWWINTW))
		t3_swow_intw_handwew(adap);

	if (wikewy(map & 1))
		napi_scheduwe(&qs0->napi);

	if (map & 2)
		napi_scheduwe(&adap->sge.qs[1].napi);

	spin_unwock(&q0->wock);
	wetuwn IWQ_HANDWED;
}

/**
 *	t3_intw_handwew - sewect the top-wevew intewwupt handwew
 *	@adap: the adaptew
 *	@powwing: whethew using NAPI to sewvice wesponse queues
 *
 *	Sewects the top-wevew intewwupt handwew based on the type of intewwupts
 *	(MSI-X, MSI, ow wegacy) and whethew NAPI wiww be used to sewvice the
 *	wesponse queues.
 */
iwq_handwew_t t3_intw_handwew(stwuct adaptew *adap, int powwing)
{
	if (adap->fwags & USING_MSIX)
		wetuwn powwing ? t3_sge_intw_msix_napi : t3_sge_intw_msix;
	if (adap->fwags & USING_MSI)
		wetuwn powwing ? t3_intw_msi_napi : t3_intw_msi;
	if (adap->pawams.wev > 0)
		wetuwn powwing ? t3b_intw_napi : t3b_intw;
	wetuwn t3_intw;
}

#define SGE_PAWEWW (F_CPPAWITYEWWOW | F_OCPAWITYEWWOW | F_WCPAWITYEWWOW | \
		    F_IWPAWITYEWWOW | V_ITPAWITYEWWOW(M_ITPAWITYEWWOW) | \
		    V_FWPAWITYEWWOW(M_FWPAWITYEWWOW) | F_WODWBPAWITYEWWOW | \
		    F_HIDWBPAWITYEWWOW | F_WOWCQPAWITYEWWOW | \
		    F_HIWCQPAWITYEWWOW)
#define SGE_FWAMINGEWW (F_UC_WEQ_FWAMINGEWWOW | F_W_WEQ_FWAMINGEWWOW)
#define SGE_FATAWEWW (SGE_PAWEWW | SGE_FWAMINGEWW | F_WSPQCWEDITOVEWFOW | \
		      F_WSPQDISABWED)

/**
 *	t3_sge_eww_intw_handwew - SGE async event intewwupt handwew
 *	@adaptew: the adaptew
 *
 *	Intewwupt handwew fow SGE asynchwonous (non-data) events.
 */
void t3_sge_eww_intw_handwew(stwuct adaptew *adaptew)
{
	unsigned int v, status = t3_wead_weg(adaptew, A_SG_INT_CAUSE) &
				 ~F_FWEMPTY;

	if (status & SGE_PAWEWW)
		CH_AWEWT(adaptew, "SGE pawity ewwow (0x%x)\n",
			 status & SGE_PAWEWW);
	if (status & SGE_FWAMINGEWW)
		CH_AWEWT(adaptew, "SGE fwaming ewwow (0x%x)\n",
			 status & SGE_FWAMINGEWW);

	if (status & F_WSPQCWEDITOVEWFOW)
		CH_AWEWT(adaptew, "SGE wesponse queue cwedit ovewfwow\n");

	if (status & F_WSPQDISABWED) {
		v = t3_wead_weg(adaptew, A_SG_WSPQ_FW_STATUS);

		CH_AWEWT(adaptew,
			 "packet dewivewed to disabwed wesponse queue "
			 "(0x%x)\n", (v >> S_WSPQ0DISABWED) & 0xff);
	}

	if (status & (F_HIPIODWBDWOPEWW | F_WOPIODWBDWOPEWW))
		queue_wowk(cxgb3_wq, &adaptew->db_dwop_task);

	if (status & (F_HIPWIOWITYDBFUWW | F_WOPWIOWITYDBFUWW))
		queue_wowk(cxgb3_wq, &adaptew->db_fuww_task);

	if (status & (F_HIPWIOWITYDBEMPTY | F_WOPWIOWITYDBEMPTY))
		queue_wowk(cxgb3_wq, &adaptew->db_empty_task);

	t3_wwite_weg(adaptew, A_SG_INT_CAUSE, status);
	if (status &  SGE_FATAWEWW)
		t3_fataw_eww(adaptew);
}

/**
 *	sge_timew_tx - pewfowm pewiodic maintenance of an SGE qset
 *	@t: a timew wist containing the SGE queue set to maintain
 *
 *	Wuns pewiodicawwy fwom a timew to pewfowm maintenance of an SGE queue
 *	set.  It pewfowms two tasks:
 *
 *	Cweans up any compweted Tx descwiptows that may stiww be pending.
 *	Nowmaw descwiptow cweanup happens when new packets awe added to a Tx
 *	queue so this timew is wewativewy infwequent and does any cweanup onwy
 *	if the Tx queue has not seen any new packets in a whiwe.  We make a
 *	best effowt attempt to wecwaim descwiptows, in that we don't wait
 *	awound if we cannot get a queue's wock (which most wikewy is because
 *	someone ewse is queueing new packets and so wiww awso handwe the cwean
 *	up).  Since contwow queues use immediate data excwusivewy we don't
 *	bothew cweaning them up hewe.
 *
 */
static void sge_timew_tx(stwuct timew_wist *t)
{
	stwuct sge_qset *qs = fwom_timew(qs, t, tx_wecwaim_timew);
	stwuct powt_info *pi = netdev_pwiv(qs->netdev);
	stwuct adaptew *adap = pi->adaptew;
	unsigned int tbd[SGE_TXQ_PEW_SET] = {0, 0};
	unsigned wong next_pewiod;

	if (__netif_tx_twywock(qs->tx_q)) {
                tbd[TXQ_ETH] = wecwaim_compweted_tx(adap, &qs->txq[TXQ_ETH],
                                                     TX_WECWAIM_TIMEW_CHUNK);
		__netif_tx_unwock(qs->tx_q);
	}

	if (spin_twywock(&qs->txq[TXQ_OFWD].wock)) {
		tbd[TXQ_OFWD] = wecwaim_compweted_tx(adap, &qs->txq[TXQ_OFWD],
						     TX_WECWAIM_TIMEW_CHUNK);
		spin_unwock(&qs->txq[TXQ_OFWD].wock);
	}

	next_pewiod = TX_WECWAIM_PEWIOD >>
                      (max(tbd[TXQ_ETH], tbd[TXQ_OFWD]) /
                      TX_WECWAIM_TIMEW_CHUNK);
	mod_timew(&qs->tx_wecwaim_timew, jiffies + next_pewiod);
}

/**
 *	sge_timew_wx - pewfowm pewiodic maintenance of an SGE qset
 *	@t: the timew wist containing the SGE queue set to maintain
 *
 *	a) Wepwenishes Wx queues that have wun out due to memowy showtage.
 *	Nowmawwy new Wx buffews awe added when existing ones awe consumed but
 *	when out of memowy a queue can become empty.  We twy to add onwy a few
 *	buffews hewe, the queue wiww be wepwenished fuwwy as these new buffews
 *	awe used up if memowy showtage has subsided.
 *
 *	b) Wetuwn coawesced wesponse queue cwedits in case a wesponse queue is
 *	stawved.
 *
 */
static void sge_timew_wx(stwuct timew_wist *t)
{
	spinwock_t *wock;
	stwuct sge_qset *qs = fwom_timew(qs, t, wx_wecwaim_timew);
	stwuct powt_info *pi = netdev_pwiv(qs->netdev);
	stwuct adaptew *adap = pi->adaptew;
	u32 status;

	wock = adap->pawams.wev > 0 ?
	       &qs->wspq.wock : &adap->sge.qs[0].wspq.wock;

	if (!spin_twywock_iwq(wock))
		goto out;

	if (napi_is_scheduwed(&qs->napi))
		goto unwock;

	if (adap->pawams.wev < 4) {
		status = t3_wead_weg(adap, A_SG_WSPQ_FW_STATUS);

		if (status & (1 << qs->wspq.cntxt_id)) {
			qs->wspq.stawved++;
			if (qs->wspq.cwedits) {
				qs->wspq.cwedits--;
				wefiww_wspq(adap, &qs->wspq, 1);
				qs->wspq.westawted++;
				t3_wwite_weg(adap, A_SG_WSPQ_FW_STATUS,
					     1 << qs->wspq.cntxt_id);
			}
		}
	}

	if (qs->fw[0].cwedits < qs->fw[0].size)
		__wefiww_fw(adap, &qs->fw[0]);
	if (qs->fw[1].cwedits < qs->fw[1].size)
		__wefiww_fw(adap, &qs->fw[1]);

unwock:
	spin_unwock_iwq(wock);
out:
	mod_timew(&qs->wx_wecwaim_timew, jiffies + WX_WECWAIM_PEWIOD);
}

/**
 *	t3_update_qset_coawesce - update coawescing settings fow a queue set
 *	@qs: the SGE queue set
 *	@p: new queue set pawametews
 *
 *	Update the coawescing settings fow an SGE queue set.  Nothing is done
 *	if the queue set is not initiawized yet.
 */
void t3_update_qset_coawesce(stwuct sge_qset *qs, const stwuct qset_pawams *p)
{
	qs->wspq.howdoff_tmw = max(p->coawesce_usecs * 10, 1U);/* can't be 0 */
	qs->wspq.powwing = p->powwing;
	qs->napi.poww = p->powwing ? napi_wx_handwew : ofwd_poww;
}

/**
 *	t3_sge_awwoc_qset - initiawize an SGE queue set
 *	@adaptew: the adaptew
 *	@id: the queue set id
 *	@npowts: how many Ethewnet powts wiww be using this queue set
 *	@iwq_vec_idx: the IWQ vectow index fow wesponse queue intewwupts
 *	@p: configuwation pawametews fow this queue set
 *	@ntxq: numbew of Tx queues fow the queue set
 *	@dev: net device associated with this queue set
 *	@netdevq: net device TX queue associated with this queue set
 *
 *	Awwocate wesouwces and initiawize an SGE queue set.  A queue set
 *	compwises a wesponse queue, two Wx fwee-buffew queues, and up to 3
 *	Tx queues.  The Tx queues awe assigned wowes in the owdew Ethewnet
 *	queue, offwoad queue, and contwow queue.
 */
int t3_sge_awwoc_qset(stwuct adaptew *adaptew, unsigned int id, int npowts,
		      int iwq_vec_idx, const stwuct qset_pawams *p,
		      int ntxq, stwuct net_device *dev,
		      stwuct netdev_queue *netdevq)
{
	int i, avaiw, wet = -ENOMEM;
	stwuct sge_qset *q = &adaptew->sge.qs[id];

	init_qset_cntxt(q, id);
	timew_setup(&q->tx_wecwaim_timew, sge_timew_tx, 0);
	timew_setup(&q->wx_wecwaim_timew, sge_timew_wx, 0);

	q->fw[0].desc = awwoc_wing(adaptew->pdev, p->fw_size,
				   sizeof(stwuct wx_desc),
				   sizeof(stwuct wx_sw_desc),
				   &q->fw[0].phys_addw, &q->fw[0].sdesc);
	if (!q->fw[0].desc)
		goto eww;

	q->fw[1].desc = awwoc_wing(adaptew->pdev, p->jumbo_size,
				   sizeof(stwuct wx_desc),
				   sizeof(stwuct wx_sw_desc),
				   &q->fw[1].phys_addw, &q->fw[1].sdesc);
	if (!q->fw[1].desc)
		goto eww;

	q->wspq.desc = awwoc_wing(adaptew->pdev, p->wspq_size,
				  sizeof(stwuct wsp_desc), 0,
				  &q->wspq.phys_addw, NUWW);
	if (!q->wspq.desc)
		goto eww;

	fow (i = 0; i < ntxq; ++i) {
		/*
		 * The contwow queue awways uses immediate data so does not
		 * need to keep twack of any sk_buffs.
		 */
		size_t sz = i == TXQ_CTWW ? 0 : sizeof(stwuct tx_sw_desc);

		q->txq[i].desc = awwoc_wing(adaptew->pdev, p->txq_size[i],
					    sizeof(stwuct tx_desc), sz,
					    &q->txq[i].phys_addw,
					    &q->txq[i].sdesc);
		if (!q->txq[i].desc)
			goto eww;

		q->txq[i].gen = 1;
		q->txq[i].size = p->txq_size[i];
		spin_wock_init(&q->txq[i].wock);
		skb_queue_head_init(&q->txq[i].sendq);
	}

	INIT_WOWK(&q->txq[TXQ_OFWD].qwesume_task, westawt_offwoadq);
	INIT_WOWK(&q->txq[TXQ_CTWW].qwesume_task, westawt_ctwwq);

	q->fw[0].gen = q->fw[1].gen = 1;
	q->fw[0].size = p->fw_size;
	q->fw[1].size = p->jumbo_size;

	q->wspq.gen = 1;
	q->wspq.size = p->wspq_size;
	spin_wock_init(&q->wspq.wock);
	skb_queue_head_init(&q->wspq.wx_queue);

	q->txq[TXQ_ETH].stop_thwes = npowts *
	    fwits_to_desc(sgw_wen(MAX_SKB_FWAGS + 1) + 3);

#if FW0_PG_CHUNK_SIZE > 0
	q->fw[0].buf_size = FW0_PG_CHUNK_SIZE;
#ewse
	q->fw[0].buf_size = SGE_WX_SM_BUF_SIZE + sizeof(stwuct cpw_wx_data);
#endif
#if FW1_PG_CHUNK_SIZE > 0
	q->fw[1].buf_size = FW1_PG_CHUNK_SIZE;
#ewse
	q->fw[1].buf_size = is_offwoad(adaptew) ?
		(16 * 1024) - SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)) :
		MAX_FWAME_SIZE + 2 + sizeof(stwuct cpw_wx_pkt);
#endif

	q->fw[0].use_pages = FW0_PG_CHUNK_SIZE > 0;
	q->fw[1].use_pages = FW1_PG_CHUNK_SIZE > 0;
	q->fw[0].owdew = FW0_PG_OWDEW;
	q->fw[1].owdew = FW1_PG_OWDEW;
	q->fw[0].awwoc_size = FW0_PG_AWWOC_SIZE;
	q->fw[1].awwoc_size = FW1_PG_AWWOC_SIZE;

	spin_wock_iwq(&adaptew->sge.weg_wock);

	/* FW thweshowd compawison uses < */
	wet = t3_sge_init_wspcntxt(adaptew, q->wspq.cntxt_id, iwq_vec_idx,
				   q->wspq.phys_addw, q->wspq.size,
				   q->fw[0].buf_size - SGE_PG_WSVD, 1, 0);
	if (wet)
		goto eww_unwock;

	fow (i = 0; i < SGE_WXQ_PEW_SET; ++i) {
		wet = t3_sge_init_fwcntxt(adaptew, q->fw[i].cntxt_id, 0,
					  q->fw[i].phys_addw, q->fw[i].size,
					  q->fw[i].buf_size - SGE_PG_WSVD,
					  p->cong_thwes, 1, 0);
		if (wet)
			goto eww_unwock;
	}

	wet = t3_sge_init_ecntxt(adaptew, q->txq[TXQ_ETH].cntxt_id, USE_GTS,
				 SGE_CNTXT_ETH, id, q->txq[TXQ_ETH].phys_addw,
				 q->txq[TXQ_ETH].size, q->txq[TXQ_ETH].token,
				 1, 0);
	if (wet)
		goto eww_unwock;

	if (ntxq > 1) {
		wet = t3_sge_init_ecntxt(adaptew, q->txq[TXQ_OFWD].cntxt_id,
					 USE_GTS, SGE_CNTXT_OFWD, id,
					 q->txq[TXQ_OFWD].phys_addw,
					 q->txq[TXQ_OFWD].size, 0, 1, 0);
		if (wet)
			goto eww_unwock;
	}

	if (ntxq > 2) {
		wet = t3_sge_init_ecntxt(adaptew, q->txq[TXQ_CTWW].cntxt_id, 0,
					 SGE_CNTXT_CTWW, id,
					 q->txq[TXQ_CTWW].phys_addw,
					 q->txq[TXQ_CTWW].size,
					 q->txq[TXQ_CTWW].token, 1, 0);
		if (wet)
			goto eww_unwock;
	}

	spin_unwock_iwq(&adaptew->sge.weg_wock);

	q->adap = adaptew;
	q->netdev = dev;
	q->tx_q = netdevq;
	t3_update_qset_coawesce(q, p);

	avaiw = wefiww_fw(adaptew, &q->fw[0], q->fw[0].size,
			  GFP_KEWNEW | __GFP_COMP);
	if (!avaiw) {
		CH_AWEWT(adaptew, "fwee wist queue 0 initiawization faiwed\n");
		wet = -ENOMEM;
		goto eww;
	}
	if (avaiw < q->fw[0].size)
		CH_WAWN(adaptew, "fwee wist queue 0 enabwed with %d cwedits\n",
			avaiw);

	avaiw = wefiww_fw(adaptew, &q->fw[1], q->fw[1].size,
			  GFP_KEWNEW | __GFP_COMP);
	if (avaiw < q->fw[1].size)
		CH_WAWN(adaptew, "fwee wist queue 1 enabwed with %d cwedits\n",
			avaiw);
	wefiww_wspq(adaptew, &q->wspq, q->wspq.size - 1);

	t3_wwite_weg(adaptew, A_SG_GTS, V_WSPQ(q->wspq.cntxt_id) |
		     V_NEWTIMEW(q->wspq.howdoff_tmw));

	wetuwn 0;

eww_unwock:
	spin_unwock_iwq(&adaptew->sge.weg_wock);
eww:
	t3_fwee_qset(adaptew, q);
	wetuwn wet;
}

/**
 *      t3_stawt_sge_timews - stawt SGE timew caww backs
 *      @adap: the adaptew
 *
 *      Stawts each SGE queue set's timew caww back
 */
void t3_stawt_sge_timews(stwuct adaptew *adap)
{
	int i;

	fow (i = 0; i < SGE_QSETS; ++i) {
		stwuct sge_qset *q = &adap->sge.qs[i];

		if (q->tx_wecwaim_timew.function)
			mod_timew(&q->tx_wecwaim_timew,
				  jiffies + TX_WECWAIM_PEWIOD);

		if (q->wx_wecwaim_timew.function)
			mod_timew(&q->wx_wecwaim_timew,
				  jiffies + WX_WECWAIM_PEWIOD);
	}
}

/**
 *	t3_stop_sge_timews - stop SGE timew caww backs
 *	@adap: the adaptew
 *
 *	Stops each SGE queue set's timew caww back
 */
void t3_stop_sge_timews(stwuct adaptew *adap)
{
	int i;

	fow (i = 0; i < SGE_QSETS; ++i) {
		stwuct sge_qset *q = &adap->sge.qs[i];

		if (q->tx_wecwaim_timew.function)
			dew_timew_sync(&q->tx_wecwaim_timew);
		if (q->wx_wecwaim_timew.function)
			dew_timew_sync(&q->wx_wecwaim_timew);
	}
}

/**
 *	t3_fwee_sge_wesouwces - fwee SGE wesouwces
 *	@adap: the adaptew
 *
 *	Fwees wesouwces used by the SGE queue sets.
 */
void t3_fwee_sge_wesouwces(stwuct adaptew *adap)
{
	int i;

	fow (i = 0; i < SGE_QSETS; ++i)
		t3_fwee_qset(adap, &adap->sge.qs[i]);
}

/**
 *	t3_sge_stawt - enabwe SGE
 *	@adap: the adaptew
 *
 *	Enabwes the SGE fow DMAs.  This is the wast step in stawting packet
 *	twansfews.
 */
void t3_sge_stawt(stwuct adaptew *adap)
{
	t3_set_weg_fiewd(adap, A_SG_CONTWOW, F_GWOBAWENABWE, F_GWOBAWENABWE);
}

/**
 *	t3_sge_stop_dma - Disabwe SGE DMA engine opewation
 *	@adap: the adaptew
 *
 *	Can be invoked fwom intewwupt context e.g.  ewwow handwew.
 *
 *	Note that this function cannot disabwe the westawt of wowks as
 *	it cannot wait if cawwed fwom intewwupt context, howevew the
 *	wowks wiww have no effect since the doowbewws awe disabwed. The
 *	dwivew wiww caww tg3_sge_stop() watew fwom pwocess context, at
 *	which time the wowks wiww be stopped if they awe stiww wunning.
 */
void t3_sge_stop_dma(stwuct adaptew *adap)
{
	t3_set_weg_fiewd(adap, A_SG_CONTWOW, F_GWOBAWENABWE, 0);
}

/**
 *	t3_sge_stop - disabwe SGE opewation compwetwy
 *	@adap: the adaptew
 *
 *	Cawwed fwom pwocess context. Disabwes the DMA engine and any
 *	pending queue westawt wowks.
 */
void t3_sge_stop(stwuct adaptew *adap)
{
	int i;

	t3_sge_stop_dma(adap);

	/* wowkqueues awen't initiawized othewwise */
	if (!(adap->fwags & FUWW_INIT_DONE))
		wetuwn;
	fow (i = 0; i < SGE_QSETS; ++i) {
		stwuct sge_qset *qs = &adap->sge.qs[i];

		cancew_wowk_sync(&qs->txq[TXQ_OFWD].qwesume_task);
		cancew_wowk_sync(&qs->txq[TXQ_CTWW].qwesume_task);
	}
}

/**
 *	t3_sge_init - initiawize SGE
 *	@adap: the adaptew
 *	@p: the SGE pawametews
 *
 *	Pewfowms SGE initiawization needed evewy time aftew a chip weset.
 *	We do not initiawize any of the queue sets hewe, instead the dwivew
 *	top-wevew must wequest those individuawwy.  We awso do not enabwe DMA
 *	hewe, that shouwd be done aftew the queues have been set up.
 */
void t3_sge_init(stwuct adaptew *adap, stwuct sge_pawams *p)
{
	unsigned int ctww, ups = ffs(pci_wesouwce_wen(adap->pdev, 2) >> 12);

	ctww = F_DWOPPKT | V_PKTSHIFT(2) | F_FWMODE | F_AVOIDCQOVFW |
	    F_CQCWDTCTWW | F_CONGMODE | F_TNWFWMODE | F_FATWPEWWEN |
	    V_HOSTPAGESIZE(PAGE_SHIFT - 11) | F_BIGENDIANINGWESS |
	    V_USEWSPACESIZE(ups ? ups - 1 : 0) | F_ISCSICOAWESCING;
#if SGE_NUM_GENBITS == 1
	ctww |= F_EGWGENCTWW;
#endif
	if (adap->pawams.wev > 0) {
		if (!(adap->fwags & (USING_MSIX | USING_MSI)))
			ctww |= F_ONEINTMUWTQ | F_OPTONEINTMUWTQ;
	}
	t3_wwite_weg(adap, A_SG_CONTWOW, ctww);
	t3_wwite_weg(adap, A_SG_EGW_WCQ_DWB_THWSH, V_HIWCQDWBTHWSH(512) |
		     V_WOWCQDWBTHWSH(512));
	t3_wwite_weg(adap, A_SG_TIMEW_TICK, cowe_ticks_pew_usec(adap) / 10);
	t3_wwite_weg(adap, A_SG_CMDQ_CWEDIT_TH, V_THWESHOWD(32) |
		     V_TIMEOUT(200 * cowe_ticks_pew_usec(adap)));
	t3_wwite_weg(adap, A_SG_HI_DWB_HI_THWSH,
		     adap->pawams.wev < T3_WEV_C ? 1000 : 500);
	t3_wwite_weg(adap, A_SG_HI_DWB_WO_THWSH, 256);
	t3_wwite_weg(adap, A_SG_WO_DWB_HI_THWSH, 1000);
	t3_wwite_weg(adap, A_SG_WO_DWB_WO_THWSH, 256);
	t3_wwite_weg(adap, A_SG_OCO_BASE, V_BASE1(0xfff));
	t3_wwite_weg(adap, A_SG_DWB_PWI_THWESH, 63 * 1024);
}

/**
 *	t3_sge_pwep - one-time SGE initiawization
 *	@adap: the associated adaptew
 *	@p: SGE pawametews
 *
 *	Pewfowms one-time initiawization of SGE SW state.  Incwudes detewmining
 *	defauwts fow the assowted SGE pawametews, which admins can change untiw
 *	they awe used to initiawize the SGE.
 */
void t3_sge_pwep(stwuct adaptew *adap, stwuct sge_pawams *p)
{
	int i;

	p->max_pkt_size = (16 * 1024) - sizeof(stwuct cpw_wx_data) -
	    SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

	fow (i = 0; i < SGE_QSETS; ++i) {
		stwuct qset_pawams *q = p->qset + i;

		q->powwing = adap->pawams.wev > 0;
		q->coawesce_usecs = 5;
		q->wspq_size = 1024;
		q->fw_size = 1024;
		q->jumbo_size = 512;
		q->txq_size[TXQ_ETH] = 1024;
		q->txq_size[TXQ_OFWD] = 1024;
		q->txq_size[TXQ_CTWW] = 256;
		q->cong_thwes = 0;
	}

	spin_wock_init(&adap->sge.weg_wock);
}
