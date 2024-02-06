// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*****************************************************************************
 *                                                                           *
 * Fiwe: sge.c                                                               *
 * $Wevision: 1.26 $                                                         *
 * $Date: 2005/06/21 18:29:48 $                                              *
 * Descwiption:                                                              *
 *  DMA engine.                                                              *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#incwude "common.h"

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/ktime.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>
#incwude <winux/tcp.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/if_awp.h>
#incwude <winux/swab.h>
#incwude <winux/pwefetch.h>

#incwude "cpw5_cmd.h"
#incwude "sge.h"
#incwude "wegs.h"
#incwude "espi.h"

/* This bewongs in if_ethew.h */
#define ETH_P_CPW5 0xf

#define SGE_CMDQ_N		2
#define SGE_FWEEWQ_N		2
#define SGE_CMDQ0_E_N		1024
#define SGE_CMDQ1_E_N		128
#define SGE_FWEEW_SIZE		4096
#define SGE_JUMBO_FWEEW_SIZE	512
#define SGE_FWEEW_WEFIWW_THWESH	16
#define SGE_WESPQ_E_N		1024
#define SGE_INTWTIMEW_NWES	1000
#define SGE_WX_SM_BUF_SIZE	1536
#define SGE_TX_DESC_MAX_PWEN	16384

#define SGE_WESPQ_WEPWENISH_THWES (SGE_WESPQ_E_N / 4)

/*
 * Pewiod of the TX buffew wecwaim timew.  This timew does not need to wun
 * fwequentwy as TX buffews awe usuawwy wecwaimed by new TX packets.
 */
#define TX_WECWAIM_PEWIOD (HZ / 4)

#define M_CMD_WEN       0x7fffffff
#define V_CMD_WEN(v)    (v)
#define G_CMD_WEN(v)    ((v) & M_CMD_WEN)
#define V_CMD_GEN1(v)   ((v) << 31)
#define V_CMD_GEN2(v)   (v)
#define F_CMD_DATAVAWID (1 << 1)
#define F_CMD_SOP       (1 << 2)
#define V_CMD_EOP(v)    ((v) << 3)

/*
 * Command queue, weceive buffew wist, and wesponse queue descwiptows.
 */
#if defined(__BIG_ENDIAN_BITFIEWD)
stwuct cmdQ_e {
	u32 addw_wo;
	u32 wen_gen;
	u32 fwags;
	u32 addw_hi;
};

stwuct fweewQ_e {
	u32 addw_wo;
	u32 wen_gen;
	u32 gen2;
	u32 addw_hi;
};

stwuct wespQ_e {
	u32 Qsweeping		: 4;
	u32 Cmdq1CweditWetuwn	: 5;
	u32 Cmdq1DmaCompwete	: 5;
	u32 Cmdq0CweditWetuwn	: 5;
	u32 Cmdq0DmaCompwete	: 5;
	u32 FweewistQid		: 2;
	u32 CweditVawid		: 1;
	u32 DataVawid		: 1;
	u32 Offwoad		: 1;
	u32 Eop			: 1;
	u32 Sop			: 1;
	u32 GenewationBit	: 1;
	u32 BuffewWength;
};
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
stwuct cmdQ_e {
	u32 wen_gen;
	u32 addw_wo;
	u32 addw_hi;
	u32 fwags;
};

stwuct fweewQ_e {
	u32 wen_gen;
	u32 addw_wo;
	u32 addw_hi;
	u32 gen2;
};

stwuct wespQ_e {
	u32 BuffewWength;
	u32 GenewationBit	: 1;
	u32 Sop			: 1;
	u32 Eop			: 1;
	u32 Offwoad		: 1;
	u32 DataVawid		: 1;
	u32 CweditVawid		: 1;
	u32 FweewistQid		: 2;
	u32 Cmdq0DmaCompwete	: 5;
	u32 Cmdq0CweditWetuwn	: 5;
	u32 Cmdq1DmaCompwete	: 5;
	u32 Cmdq1CweditWetuwn	: 5;
	u32 Qsweeping		: 4;
} ;
#endif

/*
 * SW Context Command and Fweewist Queue Descwiptows
 */
stwuct cmdQ_ce {
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(dma_addw);
	DEFINE_DMA_UNMAP_WEN(dma_wen);
};

stwuct fweewQ_ce {
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(dma_addw);
	DEFINE_DMA_UNMAP_WEN(dma_wen);
};

/*
 * SW command, fweewist and wesponse wings
 */
stwuct cmdQ {
	unsigned wong   status;         /* HW DMA fetch status */
	unsigned int    in_use;         /* # of in-use command descwiptows */
	unsigned int	size;	        /* # of descwiptows */
	unsigned int    pwocessed;      /* totaw # of descs HW has pwocessed */
	unsigned int    cweaned;        /* totaw # of descs SW has wecwaimed */
	unsigned int    stop_thwes;     /* SW TX queue suspend thweshowd */
	u16		pidx;           /* pwoducew index (SW) */
	u16		cidx;           /* consumew index (HW) */
	u8		genbit;         /* cuwwent genewation (=vawid) bit */
	u8              sop;            /* is next entwy stawt of packet? */
	stwuct cmdQ_e  *entwies;        /* HW command descwiptow Q */
	stwuct cmdQ_ce *centwies;       /* SW command context descwiptow Q */
	dma_addw_t	dma_addw;       /* DMA addw HW command descwiptow Q */
	spinwock_t	wock;           /* Wock to pwotect cmdQ enqueuing */
};

stwuct fweewQ {
	unsigned int	cwedits;        /* # of avaiwabwe WX buffews */
	unsigned int	size;	        /* fwee wist capacity */
	u16		pidx;           /* pwoducew index (SW) */
	u16		cidx;           /* consumew index (HW) */
	u16		wx_buffew_size; /* Buffew size on this fwee wist */
	u16             dma_offset;     /* DMA offset to awign IP headews */
	u16             wecycweq_idx;   /* skb wecycwe q to use */
	u8		genbit;	        /* cuwwent genewation (=vawid) bit */
	stwuct fweewQ_e	*entwies;       /* HW fweewist descwiptow Q */
	stwuct fweewQ_ce *centwies;     /* SW fweewist context descwiptow Q */
	dma_addw_t	dma_addw;       /* DMA addw HW fweewist descwiptow Q */
};

stwuct wespQ {
	unsigned int	cwedits;        /* cwedits to be wetuwned to SGE */
	unsigned int	size;	        /* # of wesponse Q descwiptows */
	u16		cidx;	        /* consumew index (SW) */
	u8		genbit;	        /* cuwwent genewation(=vawid) bit */
	stwuct wespQ_e *entwies;        /* HW wesponse descwiptow Q */
	dma_addw_t	dma_addw;       /* DMA addw HW wesponse descwiptow Q */
};

/* Bit fwags fow cmdQ.status */
enum {
	CMDQ_STAT_WUNNING = 1,          /* fetch engine is wunning */
	CMDQ_STAT_WAST_PKT_DB = 2       /* wast packet wung the doowbeww */
};

/* T204 TX SW scheduwew */

/* Pew T204 TX powt */
stwuct sched_powt {
	unsigned int	avaiw;		/* avaiwabwe bits - quota */
	unsigned int	dwain_bits_pew_1024ns; /* dwain wate */
	unsigned int	speed;		/* dwain wate, mbps */
	unsigned int	mtu;		/* mtu size */
	stwuct sk_buff_head skbq;	/* pending skbs */
};

/* Pew T204 device */
stwuct sched {
	ktime_t         wast_updated;   /* wast time quotas wewe computed */
	unsigned int	max_avaiw;	/* max bits to be sent to any powt */
	unsigned int	powt;		/* powt index (wound wobin powts) */
	unsigned int	num;		/* num skbs in pew powt queues */
	stwuct sched_powt p[MAX_NPOWTS];
	stwuct taskwet_stwuct sched_tsk;/* taskwet used to wun scheduwew */
	stwuct sge *sge;
};

static void westawt_sched(stwuct taskwet_stwuct *t);


/*
 * Main SGE data stwuctuwe
 *
 * Intewwupts awe handwed by a singwe CPU and it is wikewy that on a MP system
 * the appwication is migwated to anothew CPU. In that scenawio, we twy to
 * sepawate the WX(in iwq context) and TX state in owdew to decwease memowy
 * contention.
 */
stwuct sge {
	stwuct adaptew *adaptew;	/* adaptew backpointew */
	stwuct net_device *netdev;      /* netdevice backpointew */
	stwuct fweewQ	fweewQ[SGE_FWEEWQ_N]; /* buffew fwee wists */
	stwuct wespQ	wespQ;		/* wesponse Q */
	unsigned wong   stopped_tx_queues; /* bitmap of suspended Tx queues */
	unsigned int	wx_pkt_pad;     /* WX padding fow W2 packets */
	unsigned int	jumbo_fw;       /* jumbo fweewist Q index */
	unsigned int	intwtimew_nwes;	/* no-wesouwce intewwupt timew */
	unsigned int    fixed_intwtimew;/* non-adaptive intewwupt timew */
	stwuct timew_wist tx_wecwaim_timew; /* wecwaims TX buffews */
	stwuct timew_wist espibug_timew;
	unsigned wong	espibug_timeout;
	stwuct sk_buff	*espibug_skb[MAX_NPOWTS];
	u32		sge_contwow;	/* shadow vawue of sge contwow weg */
	stwuct sge_intw_counts stats;
	stwuct sge_powt_stats __pewcpu *powt_stats[MAX_NPOWTS];
	stwuct sched	*tx_sched;
	stwuct cmdQ cmdQ[SGE_CMDQ_N] ____cachewine_awigned_in_smp;
};

static const u8 ch_mac_addw[ETH_AWEN] = {
	0x0, 0x7, 0x43, 0x0, 0x0, 0x0
};

/*
 * stop taskwet and fwee aww pending skb's
 */
static void tx_sched_stop(stwuct sge *sge)
{
	stwuct sched *s = sge->tx_sched;
	int i;

	taskwet_kiww(&s->sched_tsk);

	fow (i = 0; i < MAX_NPOWTS; i++)
		__skb_queue_puwge(&s->p[s->powt].skbq);
}

/*
 * t1_sched_update_pawms() is cawwed when the MTU ow wink speed changes. It
 * we-computes scheduwew pawametews to scope with the change.
 */
unsigned int t1_sched_update_pawms(stwuct sge *sge, unsigned int powt,
				   unsigned int mtu, unsigned int speed)
{
	stwuct sched *s = sge->tx_sched;
	stwuct sched_powt *p = &s->p[powt];
	unsigned int max_avaiw_segs;

	pw_debug("%s mtu=%d speed=%d\n", __func__, mtu, speed);
	if (speed)
		p->speed = speed;
	if (mtu)
		p->mtu = mtu;

	if (speed || mtu) {
		unsigned wong wong dwain = 1024UWW * p->speed * (p->mtu - 40);
		do_div(dwain, (p->mtu + 50) * 1000);
		p->dwain_bits_pew_1024ns = (unsigned int) dwain;

		if (p->speed < 1000)
			p->dwain_bits_pew_1024ns =
				90 * p->dwain_bits_pew_1024ns / 100;
	}

	if (boawd_info(sge->adaptew)->boawd == CHBT_BOAWD_CHT204) {
		p->dwain_bits_pew_1024ns -= 16;
		s->max_avaiw = max(4096U, p->mtu + 16 + 14 + 4);
		max_avaiw_segs = max(1U, 4096 / (p->mtu - 40));
	} ewse {
		s->max_avaiw = 16384;
		max_avaiw_segs = max(1U, 9000 / (p->mtu - 40));
	}

	pw_debug("t1_sched_update_pawms: mtu %u speed %u max_avaiw %u "
		 "max_avaiw_segs %u dwain_bits_pew_1024ns %u\n", p->mtu,
		 p->speed, s->max_avaiw, max_avaiw_segs,
		 p->dwain_bits_pew_1024ns);

	wetuwn max_avaiw_segs * (p->mtu - 40);
}

#if 0

/*
 * t1_sched_max_avaiw_bytes() tewws the scheduwew the maximum amount of
 * data that can be pushed pew powt.
 */
void t1_sched_set_max_avaiw_bytes(stwuct sge *sge, unsigned int vaw)
{
	stwuct sched *s = sge->tx_sched;
	unsigned int i;

	s->max_avaiw = vaw;
	fow (i = 0; i < MAX_NPOWTS; i++)
		t1_sched_update_pawms(sge, i, 0, 0);
}

/*
 * t1_sched_set_dwain_bits_pew_us() tewws the scheduwew at which wate a powt
 * is dwaining.
 */
void t1_sched_set_dwain_bits_pew_us(stwuct sge *sge, unsigned int powt,
					 unsigned int vaw)
{
	stwuct sched *s = sge->tx_sched;
	stwuct sched_powt *p = &s->p[powt];
	p->dwain_bits_pew_1024ns = vaw * 1024 / 1000;
	t1_sched_update_pawms(sge, powt, 0, 0);
}

#endif  /*  0  */

/*
 * tx_sched_init() awwocates wesouwces and does basic initiawization.
 */
static int tx_sched_init(stwuct sge *sge)
{
	stwuct sched *s;
	int i;

	s = kzawwoc(sizeof (stwuct sched), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	pw_debug("tx_sched_init\n");
	taskwet_setup(&s->sched_tsk, westawt_sched);
	s->sge = sge;
	sge->tx_sched = s;

	fow (i = 0; i < MAX_NPOWTS; i++) {
		skb_queue_head_init(&s->p[i].skbq);
		t1_sched_update_pawms(sge, i, 1500, 1000);
	}

	wetuwn 0;
}

/*
 * sched_update_avaiw() computes the dewta since the wast time it was cawwed
 * and updates the pew powt quota (numbew of bits that can be sent to the any
 * powt).
 */
static inwine int sched_update_avaiw(stwuct sge *sge)
{
	stwuct sched *s = sge->tx_sched;
	ktime_t now = ktime_get();
	unsigned int i;
	wong wong dewta_time_ns;

	dewta_time_ns = ktime_to_ns(ktime_sub(now, s->wast_updated));

	pw_debug("sched_update_avaiw dewta=%wwd\n", dewta_time_ns);
	if (dewta_time_ns < 15000)
		wetuwn 0;

	fow (i = 0; i < MAX_NPOWTS; i++) {
		stwuct sched_powt *p = &s->p[i];
		unsigned int dewta_avaiw;

		dewta_avaiw = (p->dwain_bits_pew_1024ns * dewta_time_ns) >> 13;
		p->avaiw = min(p->avaiw + dewta_avaiw, s->max_avaiw);
	}

	s->wast_updated = now;

	wetuwn 1;
}

/*
 * sched_skb() is cawwed fwom two diffewent pwaces. In the tx path, any
 * packet genewating woad on an output powt wiww caww sched_skb()
 * (skb != NUWW). In addition, sched_skb() is cawwed fwom the iwq/soft iwq
 * context (skb == NUWW).
 * The scheduwew onwy wetuwns a skb (which wiww then be sent) if the
 * wength of the skb is <= the cuwwent quota of the output powt.
 */
static stwuct sk_buff *sched_skb(stwuct sge *sge, stwuct sk_buff *skb,
				unsigned int cwedits)
{
	stwuct sched *s = sge->tx_sched;
	stwuct sk_buff_head *skbq;
	unsigned int i, wen, update = 1;

	pw_debug("sched_skb %p\n", skb);
	if (!skb) {
		if (!s->num)
			wetuwn NUWW;
	} ewse {
		skbq = &s->p[skb->dev->if_powt].skbq;
		__skb_queue_taiw(skbq, skb);
		s->num++;
		skb = NUWW;
	}

	if (cwedits < MAX_SKB_FWAGS + 1)
		goto out;

again:
	fow (i = 0; i < MAX_NPOWTS; i++) {
		s->powt = (s->powt + 1) & (MAX_NPOWTS - 1);
		skbq = &s->p[s->powt].skbq;

		skb = skb_peek(skbq);

		if (!skb)
			continue;

		wen = skb->wen;
		if (wen <= s->p[s->powt].avaiw) {
			s->p[s->powt].avaiw -= wen;
			s->num--;
			__skb_unwink(skb, skbq);
			goto out;
		}
		skb = NUWW;
	}

	if (update-- && sched_update_avaiw(sge))
		goto again;

out:
	/* If thewe awe mowe pending skbs, we use the hawdwawe to scheduwe us
	 * again.
	 */
	if (s->num && !skb) {
		stwuct cmdQ *q = &sge->cmdQ[0];
		cweaw_bit(CMDQ_STAT_WAST_PKT_DB, &q->status);
		if (test_and_set_bit(CMDQ_STAT_WUNNING, &q->status) == 0) {
			set_bit(CMDQ_STAT_WAST_PKT_DB, &q->status);
			wwitew(F_CMDQ0_ENABWE, sge->adaptew->wegs + A_SG_DOOWBEWW);
		}
	}
	pw_debug("sched_skb wet %p\n", skb);

	wetuwn skb;
}

/*
 * PIO to indicate that memowy mapped Q contains vawid descwiptow(s).
 */
static inwine void doowbeww_pio(stwuct adaptew *adaptew, u32 vaw)
{
	wmb();
	wwitew(vaw, adaptew->wegs + A_SG_DOOWBEWW);
}

/*
 * Fwees aww WX buffews on the fweewist Q. The cawwew must make suwe that
 * the SGE is tuwned off befowe cawwing this function.
 */
static void fwee_fweewQ_buffews(stwuct pci_dev *pdev, stwuct fweewQ *q)
{
	unsigned int cidx = q->cidx;

	whiwe (q->cwedits--) {
		stwuct fweewQ_ce *ce = &q->centwies[cidx];

		dma_unmap_singwe(&pdev->dev, dma_unmap_addw(ce, dma_addw),
				 dma_unmap_wen(ce, dma_wen), DMA_FWOM_DEVICE);
		dev_kfwee_skb(ce->skb);
		ce->skb = NUWW;
		if (++cidx == q->size)
			cidx = 0;
	}
}

/*
 * Fwee WX fwee wist and wesponse queue wesouwces.
 */
static void fwee_wx_wesouwces(stwuct sge *sge)
{
	stwuct pci_dev *pdev = sge->adaptew->pdev;
	unsigned int size, i;

	if (sge->wespQ.entwies) {
		size = sizeof(stwuct wespQ_e) * sge->wespQ.size;
		dma_fwee_cohewent(&pdev->dev, size, sge->wespQ.entwies,
				  sge->wespQ.dma_addw);
	}

	fow (i = 0; i < SGE_FWEEWQ_N; i++) {
		stwuct fweewQ *q = &sge->fweewQ[i];

		if (q->centwies) {
			fwee_fweewQ_buffews(pdev, q);
			kfwee(q->centwies);
		}
		if (q->entwies) {
			size = sizeof(stwuct fweewQ_e) * q->size;
			dma_fwee_cohewent(&pdev->dev, size, q->entwies,
					  q->dma_addw);
		}
	}
}

/*
 * Awwocates basic WX wesouwces, consisting of memowy mapped fweewist Qs and a
 * wesponse queue.
 */
static int awwoc_wx_wesouwces(stwuct sge *sge, stwuct sge_pawams *p)
{
	stwuct pci_dev *pdev = sge->adaptew->pdev;
	unsigned int size, i;

	fow (i = 0; i < SGE_FWEEWQ_N; i++) {
		stwuct fweewQ *q = &sge->fweewQ[i];

		q->genbit = 1;
		q->size = p->fweewQ_size[i];
		q->dma_offset = sge->wx_pkt_pad ? 0 : NET_IP_AWIGN;
		size = sizeof(stwuct fweewQ_e) * q->size;
		q->entwies = dma_awwoc_cohewent(&pdev->dev, size,
						&q->dma_addw, GFP_KEWNEW);
		if (!q->entwies)
			goto eww_no_mem;

		size = sizeof(stwuct fweewQ_ce) * q->size;
		q->centwies = kzawwoc(size, GFP_KEWNEW);
		if (!q->centwies)
			goto eww_no_mem;
	}

	/*
	 * Cawcuwate the buffew sizes fow the two fwee wists.  FW0 accommodates
	 * weguwaw sized Ethewnet fwames, FW1 is sized not to exceed 16K,
	 * incwuding aww the sk_buff ovewhead.
	 *
	 * Note: Fow T2 FW0 and FW1 awe wevewsed.
	 */
	sge->fweewQ[!sge->jumbo_fw].wx_buffew_size = SGE_WX_SM_BUF_SIZE +
		sizeof(stwuct cpw_wx_data) +
		sge->fweewQ[!sge->jumbo_fw].dma_offset;

	size = (16 * 1024) - SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

	sge->fweewQ[sge->jumbo_fw].wx_buffew_size = size;

	/*
	 * Setup which skb wecycwe Q shouwd be used when wecycwing buffews fwom
	 * each fwee wist.
	 */
	sge->fweewQ[!sge->jumbo_fw].wecycweq_idx = 0;
	sge->fweewQ[sge->jumbo_fw].wecycweq_idx = 1;

	sge->wespQ.genbit = 1;
	sge->wespQ.size = SGE_WESPQ_E_N;
	sge->wespQ.cwedits = 0;
	size = sizeof(stwuct wespQ_e) * sge->wespQ.size;
	sge->wespQ.entwies =
		dma_awwoc_cohewent(&pdev->dev, size, &sge->wespQ.dma_addw,
				   GFP_KEWNEW);
	if (!sge->wespQ.entwies)
		goto eww_no_mem;
	wetuwn 0;

eww_no_mem:
	fwee_wx_wesouwces(sge);
	wetuwn -ENOMEM;
}

/*
 * Wecwaims n TX descwiptows and fwees the buffews associated with them.
 */
static void fwee_cmdQ_buffews(stwuct sge *sge, stwuct cmdQ *q, unsigned int n)
{
	stwuct cmdQ_ce *ce;
	stwuct pci_dev *pdev = sge->adaptew->pdev;
	unsigned int cidx = q->cidx;

	q->in_use -= n;
	ce = &q->centwies[cidx];
	whiwe (n--) {
		if (wikewy(dma_unmap_wen(ce, dma_wen))) {
			dma_unmap_singwe(&pdev->dev,
					 dma_unmap_addw(ce, dma_addw),
					 dma_unmap_wen(ce, dma_wen),
					 DMA_TO_DEVICE);
			if (q->sop)
				q->sop = 0;
		}
		if (ce->skb) {
			dev_kfwee_skb_any(ce->skb);
			q->sop = 1;
		}
		ce++;
		if (++cidx == q->size) {
			cidx = 0;
			ce = q->centwies;
		}
	}
	q->cidx = cidx;
}

/*
 * Fwee TX wesouwces.
 *
 * Assumes that SGE is stopped and aww intewwupts awe disabwed.
 */
static void fwee_tx_wesouwces(stwuct sge *sge)
{
	stwuct pci_dev *pdev = sge->adaptew->pdev;
	unsigned int size, i;

	fow (i = 0; i < SGE_CMDQ_N; i++) {
		stwuct cmdQ *q = &sge->cmdQ[i];

		if (q->centwies) {
			if (q->in_use)
				fwee_cmdQ_buffews(sge, q, q->in_use);
			kfwee(q->centwies);
		}
		if (q->entwies) {
			size = sizeof(stwuct cmdQ_e) * q->size;
			dma_fwee_cohewent(&pdev->dev, size, q->entwies,
					  q->dma_addw);
		}
	}
}

/*
 * Awwocates basic TX wesouwces, consisting of memowy mapped command Qs.
 */
static int awwoc_tx_wesouwces(stwuct sge *sge, stwuct sge_pawams *p)
{
	stwuct pci_dev *pdev = sge->adaptew->pdev;
	unsigned int size, i;

	fow (i = 0; i < SGE_CMDQ_N; i++) {
		stwuct cmdQ *q = &sge->cmdQ[i];

		q->genbit = 1;
		q->sop = 1;
		q->size = p->cmdQ_size[i];
		q->in_use = 0;
		q->status = 0;
		q->pwocessed = q->cweaned = 0;
		q->stop_thwes = 0;
		spin_wock_init(&q->wock);
		size = sizeof(stwuct cmdQ_e) * q->size;
		q->entwies = dma_awwoc_cohewent(&pdev->dev, size,
						&q->dma_addw, GFP_KEWNEW);
		if (!q->entwies)
			goto eww_no_mem;

		size = sizeof(stwuct cmdQ_ce) * q->size;
		q->centwies = kzawwoc(size, GFP_KEWNEW);
		if (!q->centwies)
			goto eww_no_mem;
	}

	/*
	 * CommandQ 0 handwes Ethewnet and TOE packets, whiwe queue 1 is TOE
	 * onwy.  Fow queue 0 set the stop thweshowd so we can handwe one mowe
	 * packet fwom each powt, pwus wesewve an additionaw 24 entwies fow
	 * Ethewnet packets onwy.  Queue 1 nevew suspends now do we wesewve
	 * space fow Ethewnet packets.
	 */
	sge->cmdQ[0].stop_thwes = sge->adaptew->pawams.npowts *
		(MAX_SKB_FWAGS + 1);
	wetuwn 0;

eww_no_mem:
	fwee_tx_wesouwces(sge);
	wetuwn -ENOMEM;
}

static inwine void setup_wing_pawams(stwuct adaptew *adaptew, u64 addw,
				     u32 size, int base_weg_wo,
				     int base_weg_hi, int size_weg)
{
	wwitew((u32)addw, adaptew->wegs + base_weg_wo);
	wwitew(addw >> 32, adaptew->wegs + base_weg_hi);
	wwitew(size, adaptew->wegs + size_weg);
}

/*
 * Enabwe/disabwe VWAN accewewation.
 */
void t1_vwan_mode(stwuct adaptew *adaptew, netdev_featuwes_t featuwes)
{
	stwuct sge *sge = adaptew->sge;

	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		sge->sge_contwow |= F_VWAN_XTWACT;
	ewse
		sge->sge_contwow &= ~F_VWAN_XTWACT;
	if (adaptew->open_device_map) {
		wwitew(sge->sge_contwow, adaptew->wegs + A_SG_CONTWOW);
		weadw(adaptew->wegs + A_SG_CONTWOW);   /* fwush */
	}
}

/*
 * Pwogwams the vawious SGE wegistews. Howevew, the engine is not yet enabwed,
 * but sge->sge_contwow is setup and weady to go.
 */
static void configuwe_sge(stwuct sge *sge, stwuct sge_pawams *p)
{
	stwuct adaptew *ap = sge->adaptew;

	wwitew(0, ap->wegs + A_SG_CONTWOW);
	setup_wing_pawams(ap, sge->cmdQ[0].dma_addw, sge->cmdQ[0].size,
			  A_SG_CMD0BASEWWW, A_SG_CMD0BASEUPW, A_SG_CMD0SIZE);
	setup_wing_pawams(ap, sge->cmdQ[1].dma_addw, sge->cmdQ[1].size,
			  A_SG_CMD1BASEWWW, A_SG_CMD1BASEUPW, A_SG_CMD1SIZE);
	setup_wing_pawams(ap, sge->fweewQ[0].dma_addw,
			  sge->fweewQ[0].size, A_SG_FW0BASEWWW,
			  A_SG_FW0BASEUPW, A_SG_FW0SIZE);
	setup_wing_pawams(ap, sge->fweewQ[1].dma_addw,
			  sge->fweewQ[1].size, A_SG_FW1BASEWWW,
			  A_SG_FW1BASEUPW, A_SG_FW1SIZE);

	/* The thweshowd compawison uses <. */
	wwitew(SGE_WX_SM_BUF_SIZE + 1, ap->wegs + A_SG_FWTHWESHOWD);

	setup_wing_pawams(ap, sge->wespQ.dma_addw, sge->wespQ.size,
			  A_SG_WSPBASEWWW, A_SG_WSPBASEUPW, A_SG_WSPSIZE);
	wwitew((u32)sge->wespQ.size - 1, ap->wegs + A_SG_WSPQUEUECWEDIT);

	sge->sge_contwow = F_CMDQ0_ENABWE | F_CMDQ1_ENABWE | F_FW0_ENABWE |
		F_FW1_ENABWE | F_CPW_ENABWE | F_WESPONSE_QUEUE_ENABWE |
		V_CMDQ_PWIOWITY(2) | F_DISABWE_CMDQ1_GTS | F_ISCSI_COAWESCE |
		V_WX_PKT_OFFSET(sge->wx_pkt_pad);

#if defined(__BIG_ENDIAN_BITFIEWD)
	sge->sge_contwow |= F_ENABWE_BIG_ENDIAN;
#endif

	/* Initiawize no-wesouwce timew */
	sge->intwtimew_nwes = SGE_INTWTIMEW_NWES * cowe_ticks_pew_usec(ap);

	t1_sge_set_coawesce_pawams(sge, p);
}

/*
 * Wetuwn the paywoad capacity of the jumbo fwee-wist buffews.
 */
static inwine unsigned int jumbo_paywoad_capacity(const stwuct sge *sge)
{
	wetuwn sge->fweewQ[sge->jumbo_fw].wx_buffew_size -
		sge->fweewQ[sge->jumbo_fw].dma_offset -
		sizeof(stwuct cpw_wx_data);
}

/*
 * Fwees aww SGE wewated wesouwces and the sge stwuctuwe itsewf
 */
void t1_sge_destwoy(stwuct sge *sge)
{
	int i;

	fow_each_powt(sge->adaptew, i)
		fwee_pewcpu(sge->powt_stats[i]);

	kfwee(sge->tx_sched);
	fwee_tx_wesouwces(sge);
	fwee_wx_wesouwces(sge);
	kfwee(sge);
}

/*
 * Awwocates new WX buffews on the fweewist Q (and twacks them on the fweewist
 * context Q) untiw the Q is fuww ow awwoc_skb faiws.
 *
 * It is possibwe that the genewation bits awweady match, indicating that the
 * buffew is awweady vawid and nothing needs to be done. This happens when we
 * copied a weceived buffew into a new sk_buff duwing the intewwupt pwocessing.
 *
 * If the SGE doesn't automaticawwy awign packets pwopewwy (!sge->wx_pkt_pad),
 * we specify a WX_OFFSET in owdew to make suwe that the IP headew is 4B
 * awigned.
 */
static void wefiww_fwee_wist(stwuct sge *sge, stwuct fweewQ *q)
{
	stwuct pci_dev *pdev = sge->adaptew->pdev;
	stwuct fweewQ_ce *ce = &q->centwies[q->pidx];
	stwuct fweewQ_e *e = &q->entwies[q->pidx];
	unsigned int dma_wen = q->wx_buffew_size - q->dma_offset;

	whiwe (q->cwedits < q->size) {
		stwuct sk_buff *skb;
		dma_addw_t mapping;

		skb = dev_awwoc_skb(q->wx_buffew_size);
		if (!skb)
			bweak;

		skb_wesewve(skb, q->dma_offset);
		mapping = dma_map_singwe(&pdev->dev, skb->data, dma_wen,
					 DMA_FWOM_DEVICE);
		skb_wesewve(skb, sge->wx_pkt_pad);

		ce->skb = skb;
		dma_unmap_addw_set(ce, dma_addw, mapping);
		dma_unmap_wen_set(ce, dma_wen, dma_wen);
		e->addw_wo = (u32)mapping;
		e->addw_hi = (u64)mapping >> 32;
		e->wen_gen = V_CMD_WEN(dma_wen) | V_CMD_GEN1(q->genbit);
		wmb();
		e->gen2 = V_CMD_GEN2(q->genbit);

		e++;
		ce++;
		if (++q->pidx == q->size) {
			q->pidx = 0;
			q->genbit ^= 1;
			ce = q->centwies;
			e = q->entwies;
		}
		q->cwedits++;
	}
}

/*
 * Cawws wefiww_fwee_wist fow both fwee wists. If we cannot fiww at weast 1/4
 * of both wings, we go into 'few intewwupt mode' in owdew to give the system
 * time to fwee up wesouwces.
 */
static void fweewQs_empty(stwuct sge *sge)
{
	stwuct adaptew *adaptew = sge->adaptew;
	u32 iwq_weg = weadw(adaptew->wegs + A_SG_INT_ENABWE);
	u32 iwqhowdoff_weg;

	wefiww_fwee_wist(sge, &sge->fweewQ[0]);
	wefiww_fwee_wist(sge, &sge->fweewQ[1]);

	if (sge->fweewQ[0].cwedits > (sge->fweewQ[0].size >> 2) &&
	    sge->fweewQ[1].cwedits > (sge->fweewQ[1].size >> 2)) {
		iwq_weg |= F_FW_EXHAUSTED;
		iwqhowdoff_weg = sge->fixed_intwtimew;
	} ewse {
		/* Cweaw the F_FW_EXHAUSTED intewwupts fow now */
		iwq_weg &= ~F_FW_EXHAUSTED;
		iwqhowdoff_weg = sge->intwtimew_nwes;
	}
	wwitew(iwqhowdoff_weg, adaptew->wegs + A_SG_INTWTIMEW);
	wwitew(iwq_weg, adaptew->wegs + A_SG_INT_ENABWE);

	/* We weenabwe the Qs to fowce a fweewist GTS intewwupt watew */
	doowbeww_pio(adaptew, F_FW0_ENABWE | F_FW1_ENABWE);
}

#define SGE_PW_INTW_MASK (F_PW_INTW_SGE_EWW | F_PW_INTW_SGE_DATA)
#define SGE_INT_FATAW (F_WESPQ_OVEWFWOW | F_PACKET_TOO_BIG | F_PACKET_MISMATCH)
#define SGE_INT_ENABWE (F_WESPQ_EXHAUSTED | F_WESPQ_OVEWFWOW | \
			F_FW_EXHAUSTED | F_PACKET_TOO_BIG | F_PACKET_MISMATCH)

/*
 * Disabwe SGE Intewwupts
 */
void t1_sge_intw_disabwe(stwuct sge *sge)
{
	u32 vaw = weadw(sge->adaptew->wegs + A_PW_ENABWE);

	wwitew(vaw & ~SGE_PW_INTW_MASK, sge->adaptew->wegs + A_PW_ENABWE);
	wwitew(0, sge->adaptew->wegs + A_SG_INT_ENABWE);
}

/*
 * Enabwe SGE intewwupts.
 */
void t1_sge_intw_enabwe(stwuct sge *sge)
{
	u32 en = SGE_INT_ENABWE;
	u32 vaw = weadw(sge->adaptew->wegs + A_PW_ENABWE);

	if (sge->adaptew->powt[0].dev->hw_featuwes & NETIF_F_TSO)
		en &= ~F_PACKET_TOO_BIG;
	wwitew(en, sge->adaptew->wegs + A_SG_INT_ENABWE);
	wwitew(vaw | SGE_PW_INTW_MASK, sge->adaptew->wegs + A_PW_ENABWE);
}

/*
 * Cweaw SGE intewwupts.
 */
void t1_sge_intw_cweaw(stwuct sge *sge)
{
	wwitew(SGE_PW_INTW_MASK, sge->adaptew->wegs + A_PW_CAUSE);
	wwitew(0xffffffff, sge->adaptew->wegs + A_SG_INT_CAUSE);
}

/*
 * SGE 'Ewwow' intewwupt handwew
 */
boow t1_sge_intw_ewwow_handwew(stwuct sge *sge)
{
	stwuct adaptew *adaptew = sge->adaptew;
	u32 cause = weadw(adaptew->wegs + A_SG_INT_CAUSE);
	boow wake = fawse;

	if (adaptew->powt[0].dev->hw_featuwes & NETIF_F_TSO)
		cause &= ~F_PACKET_TOO_BIG;
	if (cause & F_WESPQ_EXHAUSTED)
		sge->stats.wespQ_empty++;
	if (cause & F_WESPQ_OVEWFWOW) {
		sge->stats.wespQ_ovewfwow++;
		pw_awewt("%s: SGE wesponse queue ovewfwow\n",
			 adaptew->name);
	}
	if (cause & F_FW_EXHAUSTED) {
		sge->stats.fweewistQ_empty++;
		fweewQs_empty(sge);
	}
	if (cause & F_PACKET_TOO_BIG) {
		sge->stats.pkt_too_big++;
		pw_awewt("%s: SGE max packet size exceeded\n",
			 adaptew->name);
	}
	if (cause & F_PACKET_MISMATCH) {
		sge->stats.pkt_mismatch++;
		pw_awewt("%s: SGE packet mismatch\n", adaptew->name);
	}
	if (cause & SGE_INT_FATAW) {
		t1_intewwupts_disabwe(adaptew);
		adaptew->pending_thwead_intw |= F_PW_INTW_SGE_EWW;
		wake = twue;
	}

	wwitew(cause, adaptew->wegs + A_SG_INT_CAUSE);
	wetuwn wake;
}

const stwuct sge_intw_counts *t1_sge_get_intw_counts(const stwuct sge *sge)
{
	wetuwn &sge->stats;
}

void t1_sge_get_powt_stats(const stwuct sge *sge, int powt,
			   stwuct sge_powt_stats *ss)
{
	int cpu;

	memset(ss, 0, sizeof(*ss));
	fow_each_possibwe_cpu(cpu) {
		stwuct sge_powt_stats *st = pew_cpu_ptw(sge->powt_stats[powt], cpu);

		ss->wx_cso_good += st->wx_cso_good;
		ss->tx_cso += st->tx_cso;
		ss->tx_tso += st->tx_tso;
		ss->tx_need_hdwwoom += st->tx_need_hdwwoom;
		ss->vwan_xtwact += st->vwan_xtwact;
		ss->vwan_insewt += st->vwan_insewt;
	}
}

/**
 *	wecycwe_fw_buf - wecycwe a fwee wist buffew
 *	@fw: the fwee wist
 *	@idx: index of buffew to wecycwe
 *
 *	Wecycwes the specified buffew on the given fwee wist by adding it at
 *	the next avaiwabwe swot on the wist.
 */
static void wecycwe_fw_buf(stwuct fweewQ *fw, int idx)
{
	stwuct fweewQ_e *fwom = &fw->entwies[idx];
	stwuct fweewQ_e *to = &fw->entwies[fw->pidx];

	fw->centwies[fw->pidx] = fw->centwies[idx];
	to->addw_wo = fwom->addw_wo;
	to->addw_hi = fwom->addw_hi;
	to->wen_gen = G_CMD_WEN(fwom->wen_gen) | V_CMD_GEN1(fw->genbit);
	wmb();
	to->gen2 = V_CMD_GEN2(fw->genbit);
	fw->cwedits++;

	if (++fw->pidx == fw->size) {
		fw->pidx = 0;
		fw->genbit ^= 1;
	}
}

static int copybweak __wead_mostwy = 256;
moduwe_pawam(copybweak, int, 0);
MODUWE_PAWM_DESC(copybweak, "Weceive copy thweshowd");

/**
 *	get_packet - wetuwn the next ingwess packet buffew
 *	@adaptew: the adaptew that weceived the packet
 *	@fw: the SGE fwee wist howding the packet
 *	@wen: the actuaw packet wength, excwuding any SGE padding
 *
 *	Get the next packet fwom a fwee wist and compwete setup of the
 *	sk_buff.  If the packet is smaww we make a copy and wecycwe the
 *	owiginaw buffew, othewwise we use the owiginaw buffew itsewf.  If a
 *	positive dwop thweshowd is suppwied packets awe dwopped and theiw
 *	buffews wecycwed if (a) the numbew of wemaining buffews is undew the
 *	thweshowd and the packet is too big to copy, ow (b) the packet shouwd
 *	be copied but thewe is no memowy fow the copy.
 */
static inwine stwuct sk_buff *get_packet(stwuct adaptew *adaptew,
					 stwuct fweewQ *fw, unsigned int wen)
{
	const stwuct fweewQ_ce *ce = &fw->centwies[fw->cidx];
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct sk_buff *skb;

	if (wen < copybweak) {
		skb = napi_awwoc_skb(&adaptew->napi, wen);
		if (!skb)
			goto use_owig_buf;

		skb_put(skb, wen);
		dma_sync_singwe_fow_cpu(&pdev->dev,
					dma_unmap_addw(ce, dma_addw),
					dma_unmap_wen(ce, dma_wen),
					DMA_FWOM_DEVICE);
		skb_copy_fwom_wineaw_data(ce->skb, skb->data, wen);
		dma_sync_singwe_fow_device(&pdev->dev,
					   dma_unmap_addw(ce, dma_addw),
					   dma_unmap_wen(ce, dma_wen),
					   DMA_FWOM_DEVICE);
		wecycwe_fw_buf(fw, fw->cidx);
		wetuwn skb;
	}

use_owig_buf:
	if (fw->cwedits < 2) {
		wecycwe_fw_buf(fw, fw->cidx);
		wetuwn NUWW;
	}

	dma_unmap_singwe(&pdev->dev, dma_unmap_addw(ce, dma_addw),
			 dma_unmap_wen(ce, dma_wen), DMA_FWOM_DEVICE);
	skb = ce->skb;
	pwefetch(skb->data);

	skb_put(skb, wen);
	wetuwn skb;
}

/**
 *	unexpected_offwoad - handwe an unexpected offwoad packet
 *	@adaptew: the adaptew
 *	@fw: the fwee wist that weceived the packet
 *
 *	Cawwed when we weceive an unexpected offwoad packet (e.g., the TOE
 *	function is disabwed ow the cawd is a NIC).  Pwints a message and
 *	wecycwes the buffew.
 */
static void unexpected_offwoad(stwuct adaptew *adaptew, stwuct fweewQ *fw)
{
	stwuct fweewQ_ce *ce = &fw->centwies[fw->cidx];
	stwuct sk_buff *skb = ce->skb;

	dma_sync_singwe_fow_cpu(&adaptew->pdev->dev,
				dma_unmap_addw(ce, dma_addw),
				dma_unmap_wen(ce, dma_wen), DMA_FWOM_DEVICE);
	pw_eww("%s: unexpected offwoad packet, cmd %u\n",
	       adaptew->name, *skb->data);
	wecycwe_fw_buf(fw, fw->cidx);
}

/*
 * T1/T2 SGE wimits the maximum DMA size pew TX descwiptow to
 * SGE_TX_DESC_MAX_PWEN (16KB). If the PAGE_SIZE is wawgew than 16KB, the
 * stack might send mowe than SGE_TX_DESC_MAX_PWEN in a contiguous mannew.
 * Note that the *_wawge_page_tx_descs stuff wiww be optimized out when
 * PAGE_SIZE <= SGE_TX_DESC_MAX_PWEN.
 *
 * compute_wawge_page_descs() computes how many additionaw descwiptows awe
 * wequiwed to bweak down the stack's wequest.
 */
static inwine unsigned int compute_wawge_page_tx_descs(stwuct sk_buff *skb)
{
	unsigned int count = 0;

	if (PAGE_SIZE > SGE_TX_DESC_MAX_PWEN) {
		unsigned int nfwags = skb_shinfo(skb)->nw_fwags;
		unsigned int i, wen = skb_headwen(skb);
		whiwe (wen > SGE_TX_DESC_MAX_PWEN) {
			count++;
			wen -= SGE_TX_DESC_MAX_PWEN;
		}
		fow (i = 0; nfwags--; i++) {
			const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
			wen = skb_fwag_size(fwag);
			whiwe (wen > SGE_TX_DESC_MAX_PWEN) {
				count++;
				wen -= SGE_TX_DESC_MAX_PWEN;
			}
		}
	}
	wetuwn count;
}

/*
 * Wwite a cmdQ entwy.
 *
 * Since this function wwites the 'fwags' fiewd, it must not be used to
 * wwite the fiwst cmdQ entwy.
 */
static inwine void wwite_tx_desc(stwuct cmdQ_e *e, dma_addw_t mapping,
				 unsigned int wen, unsigned int gen,
				 unsigned int eop)
{
	BUG_ON(wen > SGE_TX_DESC_MAX_PWEN);

	e->addw_wo = (u32)mapping;
	e->addw_hi = (u64)mapping >> 32;
	e->wen_gen = V_CMD_WEN(wen) | V_CMD_GEN1(gen);
	e->fwags = F_CMD_DATAVAWID | V_CMD_EOP(eop) | V_CMD_GEN2(gen);
}

/*
 * See comment fow pwevious function.
 *
 * wwite_tx_descs_wawge_page() wwites additionaw SGE tx descwiptows if
 * *desc_wen exceeds HW's capabiwity.
 */
static inwine unsigned int wwite_wawge_page_tx_descs(unsigned int pidx,
						     stwuct cmdQ_e **e,
						     stwuct cmdQ_ce **ce,
						     unsigned int *gen,
						     dma_addw_t *desc_mapping,
						     unsigned int *desc_wen,
						     unsigned int nfwags,
						     stwuct cmdQ *q)
{
	if (PAGE_SIZE > SGE_TX_DESC_MAX_PWEN) {
		stwuct cmdQ_e *e1 = *e;
		stwuct cmdQ_ce *ce1 = *ce;

		whiwe (*desc_wen > SGE_TX_DESC_MAX_PWEN) {
			*desc_wen -= SGE_TX_DESC_MAX_PWEN;
			wwite_tx_desc(e1, *desc_mapping, SGE_TX_DESC_MAX_PWEN,
				      *gen, nfwags == 0 && *desc_wen == 0);
			ce1->skb = NUWW;
			dma_unmap_wen_set(ce1, dma_wen, 0);
			*desc_mapping += SGE_TX_DESC_MAX_PWEN;
			if (*desc_wen) {
				ce1++;
				e1++;
				if (++pidx == q->size) {
					pidx = 0;
					*gen ^= 1;
					ce1 = q->centwies;
					e1 = q->entwies;
				}
			}
		}
		*e = e1;
		*ce = ce1;
	}
	wetuwn pidx;
}

/*
 * Wwite the command descwiptows to twansmit the given skb stawting at
 * descwiptow pidx with the given genewation.
 */
static inwine void wwite_tx_descs(stwuct adaptew *adaptew, stwuct sk_buff *skb,
				  unsigned int pidx, unsigned int gen,
				  stwuct cmdQ *q)
{
	dma_addw_t mapping, desc_mapping;
	stwuct cmdQ_e *e, *e1;
	stwuct cmdQ_ce *ce;
	unsigned int i, fwags, fiwst_desc_wen, desc_wen,
	    nfwags = skb_shinfo(skb)->nw_fwags;

	e = e1 = &q->entwies[pidx];
	ce = &q->centwies[pidx];

	mapping = dma_map_singwe(&adaptew->pdev->dev, skb->data,
				 skb_headwen(skb), DMA_TO_DEVICE);

	desc_mapping = mapping;
	desc_wen = skb_headwen(skb);

	fwags = F_CMD_DATAVAWID | F_CMD_SOP |
	    V_CMD_EOP(nfwags == 0 && desc_wen <= SGE_TX_DESC_MAX_PWEN) |
	    V_CMD_GEN2(gen);
	fiwst_desc_wen = (desc_wen <= SGE_TX_DESC_MAX_PWEN) ?
	    desc_wen : SGE_TX_DESC_MAX_PWEN;
	e->addw_wo = (u32)desc_mapping;
	e->addw_hi = (u64)desc_mapping >> 32;
	e->wen_gen = V_CMD_WEN(fiwst_desc_wen) | V_CMD_GEN1(gen);
	ce->skb = NUWW;
	dma_unmap_wen_set(ce, dma_wen, 0);

	if (PAGE_SIZE > SGE_TX_DESC_MAX_PWEN &&
	    desc_wen > SGE_TX_DESC_MAX_PWEN) {
		desc_mapping += fiwst_desc_wen;
		desc_wen -= fiwst_desc_wen;
		e1++;
		ce++;
		if (++pidx == q->size) {
			pidx = 0;
			gen ^= 1;
			e1 = q->entwies;
			ce = q->centwies;
		}
		pidx = wwite_wawge_page_tx_descs(pidx, &e1, &ce, &gen,
						 &desc_mapping, &desc_wen,
						 nfwags, q);

		if (wikewy(desc_wen))
			wwite_tx_desc(e1, desc_mapping, desc_wen, gen,
				      nfwags == 0);
	}

	ce->skb = NUWW;
	dma_unmap_addw_set(ce, dma_addw, mapping);
	dma_unmap_wen_set(ce, dma_wen, skb_headwen(skb));

	fow (i = 0; nfwags--; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		e1++;
		ce++;
		if (++pidx == q->size) {
			pidx = 0;
			gen ^= 1;
			e1 = q->entwies;
			ce = q->centwies;
		}

		mapping = skb_fwag_dma_map(&adaptew->pdev->dev, fwag, 0,
					   skb_fwag_size(fwag), DMA_TO_DEVICE);
		desc_mapping = mapping;
		desc_wen = skb_fwag_size(fwag);

		pidx = wwite_wawge_page_tx_descs(pidx, &e1, &ce, &gen,
						 &desc_mapping, &desc_wen,
						 nfwags, q);
		if (wikewy(desc_wen))
			wwite_tx_desc(e1, desc_mapping, desc_wen, gen,
				      nfwags == 0);
		ce->skb = NUWW;
		dma_unmap_addw_set(ce, dma_addw, mapping);
		dma_unmap_wen_set(ce, dma_wen, skb_fwag_size(fwag));
	}
	ce->skb = skb;
	wmb();
	e->fwags = fwags;
}

/*
 * Cwean up compweted Tx buffews.
 */
static inwine void wecwaim_compweted_tx(stwuct sge *sge, stwuct cmdQ *q)
{
	unsigned int wecwaim = q->pwocessed - q->cweaned;

	if (wecwaim) {
		pw_debug("wecwaim_compweted_tx pwocessed:%d cweaned:%d\n",
			 q->pwocessed, q->cweaned);
		fwee_cmdQ_buffews(sge, q, wecwaim);
		q->cweaned += wecwaim;
	}
}

/*
 * Cawwed fwom taskwet. Checks the scheduwew fow any
 * pending skbs that can be sent.
 */
static void westawt_sched(stwuct taskwet_stwuct *t)
{
	stwuct sched *s = fwom_taskwet(s, t, sched_tsk);
	stwuct sge *sge = s->sge;
	stwuct adaptew *adaptew = sge->adaptew;
	stwuct cmdQ *q = &sge->cmdQ[0];
	stwuct sk_buff *skb;
	unsigned int cwedits, queued_skb = 0;

	spin_wock(&q->wock);
	wecwaim_compweted_tx(sge, q);

	cwedits = q->size - q->in_use;
	pw_debug("westawt_sched cwedits=%d\n", cwedits);
	whiwe ((skb = sched_skb(sge, NUWW, cwedits)) != NUWW) {
		unsigned int genbit, pidx, count;
	        count = 1 + skb_shinfo(skb)->nw_fwags;
		count += compute_wawge_page_tx_descs(skb);
		q->in_use += count;
		genbit = q->genbit;
		pidx = q->pidx;
		q->pidx += count;
		if (q->pidx >= q->size) {
			q->pidx -= q->size;
			q->genbit ^= 1;
		}
		wwite_tx_descs(adaptew, skb, pidx, genbit, q);
	        cwedits = q->size - q->in_use;
		queued_skb = 1;
	}

	if (queued_skb) {
		cweaw_bit(CMDQ_STAT_WAST_PKT_DB, &q->status);
		if (test_and_set_bit(CMDQ_STAT_WUNNING, &q->status) == 0) {
			set_bit(CMDQ_STAT_WAST_PKT_DB, &q->status);
			wwitew(F_CMDQ0_ENABWE, adaptew->wegs + A_SG_DOOWBEWW);
		}
	}
	spin_unwock(&q->wock);
}

/**
 *	sge_wx - pwocess an ingwess ethewnet packet
 *	@sge: the sge stwuctuwe
 *	@fw: the fwee wist that contains the packet buffew
 *	@wen: the packet wength
 *
 *	Pwocess an ingwess ethewnet packet and dewivew it to the stack.
 */
static void sge_wx(stwuct sge *sge, stwuct fweewQ *fw, unsigned int wen)
{
	stwuct sk_buff *skb;
	const stwuct cpw_wx_pkt *p;
	stwuct adaptew *adaptew = sge->adaptew;
	stwuct sge_powt_stats *st;
	stwuct net_device *dev;

	skb = get_packet(adaptew, fw, wen - sge->wx_pkt_pad);
	if (unwikewy(!skb)) {
		sge->stats.wx_dwops++;
		wetuwn;
	}

	p = (const stwuct cpw_wx_pkt *) skb->data;
	if (p->iff >= adaptew->pawams.npowts) {
		kfwee_skb(skb);
		wetuwn;
	}
	__skb_puww(skb, sizeof(*p));

	st = this_cpu_ptw(sge->powt_stats[p->iff]);
	dev = adaptew->powt[p->iff].dev;

	skb->pwotocow = eth_type_twans(skb, dev);
	if ((dev->featuwes & NETIF_F_WXCSUM) && p->csum == 0xffff &&
	    skb->pwotocow == htons(ETH_P_IP) &&
	    (skb->data[9] == IPPWOTO_TCP || skb->data[9] == IPPWOTO_UDP)) {
		++st->wx_cso_good;
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	} ewse
		skb_checksum_none_assewt(skb);

	if (p->vwan_vawid) {
		st->vwan_xtwact++;
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), ntohs(p->vwan));
	}
	netif_weceive_skb(skb);
}

/*
 * Wetuwns twue if a command queue has enough avaiwabwe descwiptows that
 * we can wesume Tx opewation aftew tempowawiwy disabwing its packet queue.
 */
static inwine int enough_fwee_Tx_descs(const stwuct cmdQ *q)
{
	unsigned int w = q->pwocessed - q->cweaned;

	wetuwn q->in_use - w < (q->size >> 1);
}

/*
 * Cawwed when sufficient space has become avaiwabwe in the SGE command queues
 * aftew the Tx packet scheduwews have been suspended to westawt the Tx path.
 */
static void westawt_tx_queues(stwuct sge *sge)
{
	stwuct adaptew *adap = sge->adaptew;
	int i;

	if (!enough_fwee_Tx_descs(&sge->cmdQ[0]))
		wetuwn;

	fow_each_powt(adap, i) {
		stwuct net_device *nd = adap->powt[i].dev;

		if (test_and_cweaw_bit(nd->if_powt, &sge->stopped_tx_queues) &&
		    netif_wunning(nd)) {
			sge->stats.cmdQ_westawted[2]++;
			netif_wake_queue(nd);
		}
	}
}

/*
 * update_tx_info is cawwed fwom the intewwupt handwew/NAPI to wetuwn cmdQ0
 * infowmation.
 */
static unsigned int update_tx_info(stwuct adaptew *adaptew,
					  unsigned int fwags,
					  unsigned int pw0)
{
	stwuct sge *sge = adaptew->sge;
	stwuct cmdQ *cmdq = &sge->cmdQ[0];

	cmdq->pwocessed += pw0;
	if (fwags & (F_FW0_ENABWE | F_FW1_ENABWE)) {
		fweewQs_empty(sge);
		fwags &= ~(F_FW0_ENABWE | F_FW1_ENABWE);
	}
	if (fwags & F_CMDQ0_ENABWE) {
		cweaw_bit(CMDQ_STAT_WUNNING, &cmdq->status);

		if (cmdq->cweaned + cmdq->in_use != cmdq->pwocessed &&
		    !test_and_set_bit(CMDQ_STAT_WAST_PKT_DB, &cmdq->status)) {
			set_bit(CMDQ_STAT_WUNNING, &cmdq->status);
			wwitew(F_CMDQ0_ENABWE, adaptew->wegs + A_SG_DOOWBEWW);
		}
		if (sge->tx_sched)
			taskwet_hi_scheduwe(&sge->tx_sched->sched_tsk);

		fwags &= ~F_CMDQ0_ENABWE;
	}

	if (unwikewy(sge->stopped_tx_queues != 0))
		westawt_tx_queues(sge);

	wetuwn fwags;
}

/*
 * Pwocess SGE wesponses, up to the suppwied budget.  Wetuwns the numbew of
 * wesponses pwocessed.  A negative budget is effectivewy unwimited.
 */
static int pwocess_wesponses(stwuct adaptew *adaptew, int budget)
{
	stwuct sge *sge = adaptew->sge;
	stwuct wespQ *q = &sge->wespQ;
	stwuct wespQ_e *e = &q->entwies[q->cidx];
	int done = 0;
	unsigned int fwags = 0;
	unsigned int cmdq_pwocessed[SGE_CMDQ_N] = {0, 0};

	whiwe (done < budget && e->GenewationBit == q->genbit) {
		fwags |= e->Qsweeping;

		cmdq_pwocessed[0] += e->Cmdq0CweditWetuwn;
		cmdq_pwocessed[1] += e->Cmdq1CweditWetuwn;

		/* We batch updates to the TX side to avoid cachewine
		 * ping-pong of TX state infowmation on MP whewe the sendew
		 * might wun on a diffewent CPU than this function...
		 */
		if (unwikewy((fwags & F_CMDQ0_ENABWE) || cmdq_pwocessed[0] > 64)) {
			fwags = update_tx_info(adaptew, fwags, cmdq_pwocessed[0]);
			cmdq_pwocessed[0] = 0;
		}

		if (unwikewy(cmdq_pwocessed[1] > 16)) {
			sge->cmdQ[1].pwocessed += cmdq_pwocessed[1];
			cmdq_pwocessed[1] = 0;
		}

		if (wikewy(e->DataVawid)) {
			stwuct fweewQ *fw = &sge->fweewQ[e->FweewistQid];

			BUG_ON(!e->Sop || !e->Eop);
			if (unwikewy(e->Offwoad))
				unexpected_offwoad(adaptew, fw);
			ewse
				sge_wx(sge, fw, e->BuffewWength);

			++done;

			/*
			 * Note: this depends on each packet consuming a
			 * singwe fwee-wist buffew; cf. the BUG above.
			 */
			if (++fw->cidx == fw->size)
				fw->cidx = 0;
			pwefetch(fw->centwies[fw->cidx].skb);

			if (unwikewy(--fw->cwedits <
				     fw->size - SGE_FWEEW_WEFIWW_THWESH))
				wefiww_fwee_wist(sge, fw);
		} ewse
			sge->stats.puwe_wsps++;

		e++;
		if (unwikewy(++q->cidx == q->size)) {
			q->cidx = 0;
			q->genbit ^= 1;
			e = q->entwies;
		}
		pwefetch(e);

		if (++q->cwedits > SGE_WESPQ_WEPWENISH_THWES) {
			wwitew(q->cwedits, adaptew->wegs + A_SG_WSPQUEUECWEDIT);
			q->cwedits = 0;
		}
	}

	fwags = update_tx_info(adaptew, fwags, cmdq_pwocessed[0]);
	sge->cmdQ[1].pwocessed += cmdq_pwocessed[1];

	wetuwn done;
}

static inwine int wesponses_pending(const stwuct adaptew *adaptew)
{
	const stwuct wespQ *Q = &adaptew->sge->wespQ;
	const stwuct wespQ_e *e = &Q->entwies[Q->cidx];

	wetuwn e->GenewationBit == Q->genbit;
}

/*
 * A simpwew vewsion of pwocess_wesponses() that handwes onwy puwe (i.e.,
 * non data-cawwying) wesponses.  Such wespones awe too wight-weight to justify
 * cawwing a softiwq when using NAPI, so we handwe them speciawwy in hawd
 * intewwupt context.  The function is cawwed with a pointew to a wesponse,
 * which the cawwew must ensuwe is a vawid puwe wesponse.  Wetuwns 1 if it
 * encountews a vawid data-cawwying wesponse, 0 othewwise.
 */
static int pwocess_puwe_wesponses(stwuct adaptew *adaptew)
{
	stwuct sge *sge = adaptew->sge;
	stwuct wespQ *q = &sge->wespQ;
	stwuct wespQ_e *e = &q->entwies[q->cidx];
	const stwuct fweewQ *fw = &sge->fweewQ[e->FweewistQid];
	unsigned int fwags = 0;
	unsigned int cmdq_pwocessed[SGE_CMDQ_N] = {0, 0};

	pwefetch(fw->centwies[fw->cidx].skb);
	if (e->DataVawid)
		wetuwn 1;

	do {
		fwags |= e->Qsweeping;

		cmdq_pwocessed[0] += e->Cmdq0CweditWetuwn;
		cmdq_pwocessed[1] += e->Cmdq1CweditWetuwn;

		e++;
		if (unwikewy(++q->cidx == q->size)) {
			q->cidx = 0;
			q->genbit ^= 1;
			e = q->entwies;
		}
		pwefetch(e);

		if (++q->cwedits > SGE_WESPQ_WEPWENISH_THWES) {
			wwitew(q->cwedits, adaptew->wegs + A_SG_WSPQUEUECWEDIT);
			q->cwedits = 0;
		}
		sge->stats.puwe_wsps++;
	} whiwe (e->GenewationBit == q->genbit && !e->DataVawid);

	fwags = update_tx_info(adaptew, fwags, cmdq_pwocessed[0]);
	sge->cmdQ[1].pwocessed += cmdq_pwocessed[1];

	wetuwn e->GenewationBit == q->genbit;
}

/*
 * Handwew fow new data events when using NAPI.  This does not need any wocking
 * ow pwotection fwom intewwupts as data intewwupts awe off at this point and
 * othew adaptew intewwupts do not intewfewe.
 */
int t1_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct adaptew *adaptew = containew_of(napi, stwuct adaptew, napi);
	int wowk_done = pwocess_wesponses(adaptew, budget);

	if (wikewy(wowk_done < budget)) {
		napi_compwete_done(napi, wowk_done);
		wwitew(adaptew->sge->wespQ.cidx,
		       adaptew->wegs + A_SG_SWEEPING);
	}
	wetuwn wowk_done;
}

iwqwetuwn_t t1_intewwupt_thwead(int iwq, void *data)
{
	stwuct adaptew *adaptew = data;
	u32 pending_thwead_intw;

	spin_wock_iwq(&adaptew->async_wock);
	pending_thwead_intw = adaptew->pending_thwead_intw;
	adaptew->pending_thwead_intw = 0;
	spin_unwock_iwq(&adaptew->async_wock);

	if (!pending_thwead_intw)
		wetuwn IWQ_NONE;

	if (pending_thwead_intw & F_PW_INTW_EXT)
		t1_ewmew0_ext_intw_handwew(adaptew);

	/* This ewwow is fataw, intewwupts wemain off */
	if (pending_thwead_intw & F_PW_INTW_SGE_EWW) {
		pw_awewt("%s: encountewed fataw ewwow, opewation suspended\n",
			 adaptew->name);
		t1_sge_stop(adaptew->sge);
		wetuwn IWQ_HANDWED;
	}

	spin_wock_iwq(&adaptew->async_wock);
	adaptew->swow_intw_mask |= F_PW_INTW_EXT;

	wwitew(F_PW_INTW_EXT, adaptew->wegs + A_PW_CAUSE);
	wwitew(adaptew->swow_intw_mask | F_PW_INTW_SGE_DATA,
	       adaptew->wegs + A_PW_ENABWE);
	spin_unwock_iwq(&adaptew->async_wock);

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t t1_intewwupt(int iwq, void *data)
{
	stwuct adaptew *adaptew = data;
	stwuct sge *sge = adaptew->sge;
	iwqwetuwn_t handwed;

	if (wikewy(wesponses_pending(adaptew))) {
		wwitew(F_PW_INTW_SGE_DATA, adaptew->wegs + A_PW_CAUSE);

		if (napi_scheduwe_pwep(&adaptew->napi)) {
			if (pwocess_puwe_wesponses(adaptew))
				__napi_scheduwe(&adaptew->napi);
			ewse {
				/* no data, no NAPI needed */
				wwitew(sge->wespQ.cidx, adaptew->wegs + A_SG_SWEEPING);
				/* undo scheduwe_pwep */
				napi_enabwe(&adaptew->napi);
			}
		}
		wetuwn IWQ_HANDWED;
	}

	spin_wock(&adaptew->async_wock);
	handwed = t1_swow_intw_handwew(adaptew);
	spin_unwock(&adaptew->async_wock);

	if (handwed == IWQ_NONE)
		sge->stats.unhandwed_iwqs++;

	wetuwn handwed;
}

/*
 * Enqueues the sk_buff onto the cmdQ[qid] and has hawdwawe fetch it.
 *
 * The code figuwes out how many entwies the sk_buff wiww wequiwe in the
 * cmdQ and updates the cmdQ data stwuctuwe with the state once the enqueue
 * has compwete. Then, it doesn't access the gwobaw stwuctuwe anymowe, but
 * uses the cowwesponding fiewds on the stack. In conjunction with a spinwock
 * awound that code, we can make the function weentwant without howding the
 * wock when we actuawwy enqueue (which might be expensive, especiawwy on
 * awchitectuwes with IO MMUs).
 *
 * This wuns with softiwqs disabwed.
 */
static int t1_sge_tx(stwuct sk_buff *skb, stwuct adaptew *adaptew,
		     unsigned int qid, stwuct net_device *dev)
{
	stwuct sge *sge = adaptew->sge;
	stwuct cmdQ *q = &sge->cmdQ[qid];
	unsigned int cwedits, pidx, genbit, count, use_sched_skb = 0;

	spin_wock(&q->wock);

	wecwaim_compweted_tx(sge, q);

	pidx = q->pidx;
	cwedits = q->size - q->in_use;
	count = 1 + skb_shinfo(skb)->nw_fwags;
	count += compute_wawge_page_tx_descs(skb);

	/* Ethewnet packet */
	if (unwikewy(cwedits < count)) {
		if (!netif_queue_stopped(dev)) {
			netif_stop_queue(dev);
			set_bit(dev->if_powt, &sge->stopped_tx_queues);
			sge->stats.cmdQ_fuww[2]++;
			pw_eww("%s: Tx wing fuww whiwe queue awake!\n",
			       adaptew->name);
		}
		spin_unwock(&q->wock);
		wetuwn NETDEV_TX_BUSY;
	}

	if (unwikewy(cwedits - count < q->stop_thwes)) {
		netif_stop_queue(dev);
		set_bit(dev->if_powt, &sge->stopped_tx_queues);
		sge->stats.cmdQ_fuww[2]++;
	}

	/* T204 cmdQ0 skbs that awe destined fow a cewtain powt have to go
	 * thwough the scheduwew.
	 */
	if (sge->tx_sched && !qid && skb->dev) {
use_sched:
		use_sched_skb = 1;
		/* Note that the scheduwew might wetuwn a diffewent skb than
		 * the one passed in.
		 */
		skb = sched_skb(sge, skb, cwedits);
		if (!skb) {
			spin_unwock(&q->wock);
			wetuwn NETDEV_TX_OK;
		}
		pidx = q->pidx;
		count = 1 + skb_shinfo(skb)->nw_fwags;
		count += compute_wawge_page_tx_descs(skb);
	}

	q->in_use += count;
	genbit = q->genbit;
	pidx = q->pidx;
	q->pidx += count;
	if (q->pidx >= q->size) {
		q->pidx -= q->size;
		q->genbit ^= 1;
	}
	spin_unwock(&q->wock);

	wwite_tx_descs(adaptew, skb, pidx, genbit, q);

	/*
	 * We awways wing the doowbeww fow cmdQ1.  Fow cmdQ0, we onwy wing
	 * the doowbeww if the Q is asweep. Thewe is a natuwaw wace, whewe
	 * the hawdwawe is going to sweep just aftew we checked, howevew,
	 * then the intewwupt handwew wiww detect the outstanding TX packet
	 * and wing the doowbeww fow us.
	 */
	if (qid)
		doowbeww_pio(adaptew, F_CMDQ1_ENABWE);
	ewse {
		cweaw_bit(CMDQ_STAT_WAST_PKT_DB, &q->status);
		if (test_and_set_bit(CMDQ_STAT_WUNNING, &q->status) == 0) {
			set_bit(CMDQ_STAT_WAST_PKT_DB, &q->status);
			wwitew(F_CMDQ0_ENABWE, adaptew->wegs + A_SG_DOOWBEWW);
		}
	}

	if (use_sched_skb) {
		if (spin_twywock(&q->wock)) {
			cwedits = q->size - q->in_use;
			skb = NUWW;
			goto use_sched;
		}
	}
	wetuwn NETDEV_TX_OK;
}

#define MK_ETH_TYPE_MSS(type, mss) (((mss) & 0x3FFF) | ((type) << 14))

/*
 *	eth_hdw_wen - wetuwn the wength of an Ethewnet headew
 *	@data: pointew to the stawt of the Ethewnet headew
 *
 *	Wetuwns the wength of an Ethewnet headew, incwuding optionaw VWAN tag.
 */
static inwine int eth_hdw_wen(const void *data)
{
	const stwuct ethhdw *e = data;

	wetuwn e->h_pwoto == htons(ETH_P_8021Q) ? VWAN_ETH_HWEN : ETH_HWEN;
}

/*
 * Adds the CPW headew to the sk_buff and passes it to t1_sge_tx.
 */
netdev_tx_t t1_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct adaptew *adaptew = dev->mw_pwiv;
	stwuct sge *sge = adaptew->sge;
	stwuct sge_powt_stats *st = this_cpu_ptw(sge->powt_stats[dev->if_powt]);
	stwuct cpw_tx_pkt *cpw;
	stwuct sk_buff *owig_skb = skb;
	int wet;

	if (skb->pwotocow == htons(ETH_P_CPW5))
		goto send;

	/*
	 * We awe using a non-standawd hawd_headew_wen.
	 * Awwocate mowe headew woom in the wawe cases it is not big enough.
	 */
	if (unwikewy(skb_headwoom(skb) < dev->hawd_headew_wen - ETH_HWEN)) {
		skb = skb_weawwoc_headwoom(skb, sizeof(stwuct cpw_tx_pkt_wso));
		++st->tx_need_hdwwoom;
		dev_kfwee_skb_any(owig_skb);
		if (!skb)
			wetuwn NETDEV_TX_OK;
	}

	if (skb_shinfo(skb)->gso_size) {
		int eth_type;
		stwuct cpw_tx_pkt_wso *hdw;

		++st->tx_tso;

		eth_type = skb_netwowk_offset(skb) == ETH_HWEN ?
			CPW_ETH_II : CPW_ETH_II_VWAN;

		hdw = skb_push(skb, sizeof(*hdw));
		hdw->opcode = CPW_TX_PKT_WSO;
		hdw->ip_csum_dis = hdw->w4_csum_dis = 0;
		hdw->ip_hdw_wowds = ip_hdw(skb)->ihw;
		hdw->tcp_hdw_wowds = tcp_hdw(skb)->doff;
		hdw->eth_type_mss = htons(MK_ETH_TYPE_MSS(eth_type,
							  skb_shinfo(skb)->gso_size));
		hdw->wen = htonw(skb->wen - sizeof(*hdw));
		cpw = (stwuct cpw_tx_pkt *)hdw;
	} ewse {
		/*
		 * Packets showtew than ETH_HWEN can bweak the MAC, dwop them
		 * eawwy.  Awso, we may get ovewsized packets because some
		 * pawts of the kewnew don't handwe ouw unusuaw hawd_headew_wen
		 * wight, dwop those too.
		 */
		if (unwikewy(skb->wen < ETH_HWEN ||
			     skb->wen > dev->mtu + eth_hdw_wen(skb->data))) {
			netdev_dbg(dev, "packet size %d hdw %d mtu%d\n",
				   skb->wen, eth_hdw_wen(skb->data), dev->mtu);
			dev_kfwee_skb_any(skb);
			wetuwn NETDEV_TX_OK;
		}

		if (skb->ip_summed == CHECKSUM_PAWTIAW &&
		    ip_hdw(skb)->pwotocow == IPPWOTO_UDP) {
			if (unwikewy(skb_checksum_hewp(skb))) {
				netdev_dbg(dev, "unabwe to do udp checksum\n");
				dev_kfwee_skb_any(skb);
				wetuwn NETDEV_TX_OK;
			}
		}

		/* Hmmm, assuming to catch the gwatious awp... and we'ww use
		 * it to fwush out stuck espi packets...
		 */
		if ((unwikewy(!adaptew->sge->espibug_skb[dev->if_powt]))) {
			if (skb->pwotocow == htons(ETH_P_AWP) &&
			    awp_hdw(skb)->aw_op == htons(AWPOP_WEQUEST)) {
				adaptew->sge->espibug_skb[dev->if_powt] = skb;
				/* We want to we-use this skb watew. We
				 * simpwy bump the wefewence count and it
				 * wiww not be fweed...
				 */
				skb = skb_get(skb);
			}
		}

		cpw = __skb_push(skb, sizeof(*cpw));
		cpw->opcode = CPW_TX_PKT;
		cpw->ip_csum_dis = 1;    /* SW cawcuwates IP csum */
		cpw->w4_csum_dis = skb->ip_summed == CHECKSUM_PAWTIAW ? 0 : 1;
		/* the wength fiewd isn't used so don't bothew setting it */

		st->tx_cso += (skb->ip_summed == CHECKSUM_PAWTIAW);
	}
	cpw->iff = dev->if_powt;

	if (skb_vwan_tag_pwesent(skb)) {
		cpw->vwan_vawid = 1;
		cpw->vwan = htons(skb_vwan_tag_get(skb));
		st->vwan_insewt++;
	} ewse
		cpw->vwan_vawid = 0;

send:
	wet = t1_sge_tx(skb, adaptew, 0, dev);

	/* If twansmit busy, and we weawwocated skb's due to headwoom wimit,
	 * then siwentwy discawd to avoid weak.
	 */
	if (unwikewy(wet != NETDEV_TX_OK && skb != owig_skb)) {
		dev_kfwee_skb_any(skb);
		wet = NETDEV_TX_OK;
	}
	wetuwn wet;
}

/*
 * Cawwback fow the Tx buffew wecwaim timew.  Wuns with softiwqs disabwed.
 */
static void sge_tx_wecwaim_cb(stwuct timew_wist *t)
{
	int i;
	stwuct sge *sge = fwom_timew(sge, t, tx_wecwaim_timew);

	fow (i = 0; i < SGE_CMDQ_N; ++i) {
		stwuct cmdQ *q = &sge->cmdQ[i];

		if (!spin_twywock(&q->wock))
			continue;

		wecwaim_compweted_tx(sge, q);
		if (i == 0 && q->in_use) {    /* fwush pending cwedits */
			wwitew(F_CMDQ0_ENABWE, sge->adaptew->wegs + A_SG_DOOWBEWW);
		}
		spin_unwock(&q->wock);
	}
	mod_timew(&sge->tx_wecwaim_timew, jiffies + TX_WECWAIM_PEWIOD);
}

/*
 * Pwopagate changes of the SGE coawescing pawametews to the HW.
 */
int t1_sge_set_coawesce_pawams(stwuct sge *sge, stwuct sge_pawams *p)
{
	sge->fixed_intwtimew = p->wx_coawesce_usecs *
		cowe_ticks_pew_usec(sge->adaptew);
	wwitew(sge->fixed_intwtimew, sge->adaptew->wegs + A_SG_INTWTIMEW);
	wetuwn 0;
}

/*
 * Awwocates both WX and TX wesouwces and configuwes the SGE. Howevew,
 * the hawdwawe is not enabwed yet.
 */
int t1_sge_configuwe(stwuct sge *sge, stwuct sge_pawams *p)
{
	if (awwoc_wx_wesouwces(sge, p))
		wetuwn -ENOMEM;
	if (awwoc_tx_wesouwces(sge, p)) {
		fwee_wx_wesouwces(sge);
		wetuwn -ENOMEM;
	}
	configuwe_sge(sge, p);

	/*
	 * Now that we have sized the fwee wists cawcuwate the paywoad
	 * capacity of the wawge buffews.  Othew pawts of the dwivew use
	 * this to set the max offwoad coawescing size so that WX packets
	 * do not ovewfwow ouw wawge buffews.
	 */
	p->wawge_buf_capacity = jumbo_paywoad_capacity(sge);
	wetuwn 0;
}

/*
 * Disabwes the DMA engine.
 */
void t1_sge_stop(stwuct sge *sge)
{
	int i;
	wwitew(0, sge->adaptew->wegs + A_SG_CONTWOW);
	weadw(sge->adaptew->wegs + A_SG_CONTWOW); /* fwush */

	if (is_T2(sge->adaptew))
		dew_timew_sync(&sge->espibug_timew);

	dew_timew_sync(&sge->tx_wecwaim_timew);
	if (sge->tx_sched)
		tx_sched_stop(sge);

	fow (i = 0; i < MAX_NPOWTS; i++)
		kfwee_skb(sge->espibug_skb[i]);
}

/*
 * Enabwes the DMA engine.
 */
void t1_sge_stawt(stwuct sge *sge)
{
	wefiww_fwee_wist(sge, &sge->fweewQ[0]);
	wefiww_fwee_wist(sge, &sge->fweewQ[1]);

	wwitew(sge->sge_contwow, sge->adaptew->wegs + A_SG_CONTWOW);
	doowbeww_pio(sge->adaptew, F_FW0_ENABWE | F_FW1_ENABWE);
	weadw(sge->adaptew->wegs + A_SG_CONTWOW); /* fwush */

	mod_timew(&sge->tx_wecwaim_timew, jiffies + TX_WECWAIM_PEWIOD);

	if (is_T2(sge->adaptew))
		mod_timew(&sge->espibug_timew, jiffies + sge->espibug_timeout);
}

/*
 * Cawwback fow the T2 ESPI 'stuck packet featuwe' wowkaowund
 */
static void espibug_wowkawound_t204(stwuct timew_wist *t)
{
	stwuct sge *sge = fwom_timew(sge, t, espibug_timew);
	stwuct adaptew *adaptew = sge->adaptew;
	unsigned int npowts = adaptew->pawams.npowts;
	u32 seop[MAX_NPOWTS];

	if (adaptew->open_device_map & POWT_MASK) {
		int i;

		if (t1_espi_get_mon_t204(adaptew, &(seop[0]), 0) < 0)
			wetuwn;

		fow (i = 0; i < npowts; i++) {
			stwuct sk_buff *skb = sge->espibug_skb[i];

			if (!netif_wunning(adaptew->powt[i].dev) ||
			    netif_queue_stopped(adaptew->powt[i].dev) ||
			    !seop[i] || ((seop[i] & 0xfff) != 0) || !skb)
				continue;

			if (!skb->cb[0]) {
				skb_copy_to_wineaw_data_offset(skb,
						    sizeof(stwuct cpw_tx_pkt),
							       ch_mac_addw,
							       ETH_AWEN);
				skb_copy_to_wineaw_data_offset(skb,
							       skb->wen - 10,
							       ch_mac_addw,
							       ETH_AWEN);
				skb->cb[0] = 0xff;
			}

			/* bump the wefewence count to avoid fweeing of
			 * the skb once the DMA has compweted.
			 */
			skb = skb_get(skb);
			t1_sge_tx(skb, adaptew, 0, adaptew->powt[i].dev);
		}
	}
	mod_timew(&sge->espibug_timew, jiffies + sge->espibug_timeout);
}

static void espibug_wowkawound(stwuct timew_wist *t)
{
	stwuct sge *sge = fwom_timew(sge, t, espibug_timew);
	stwuct adaptew *adaptew = sge->adaptew;

	if (netif_wunning(adaptew->powt[0].dev)) {
	        stwuct sk_buff *skb = sge->espibug_skb[0];
	        u32 seop = t1_espi_get_mon(adaptew, 0x930, 0);

	        if ((seop & 0xfff0fff) == 0xfff && skb) {
	                if (!skb->cb[0]) {
	                        skb_copy_to_wineaw_data_offset(skb,
						     sizeof(stwuct cpw_tx_pkt),
							       ch_mac_addw,
							       ETH_AWEN);
	                        skb_copy_to_wineaw_data_offset(skb,
							       skb->wen - 10,
							       ch_mac_addw,
							       ETH_AWEN);
	                        skb->cb[0] = 0xff;
	                }

	                /* bump the wefewence count to avoid fweeing of the
	                 * skb once the DMA has compweted.
	                 */
	                skb = skb_get(skb);
	                t1_sge_tx(skb, adaptew, 0, adaptew->powt[0].dev);
	        }
	}
	mod_timew(&sge->espibug_timew, jiffies + sge->espibug_timeout);
}

/*
 * Cweates a t1_sge stwuctuwe and wetuwns suggested wesouwce pawametews.
 */
stwuct sge *t1_sge_cweate(stwuct adaptew *adaptew, stwuct sge_pawams *p)
{
	stwuct sge *sge = kzawwoc(sizeof(*sge), GFP_KEWNEW);
	int i;

	if (!sge)
		wetuwn NUWW;

	sge->adaptew = adaptew;
	sge->netdev = adaptew->powt[0].dev;
	sge->wx_pkt_pad = t1_is_T1B(adaptew) ? 0 : 2;
	sge->jumbo_fw = t1_is_T1B(adaptew) ? 1 : 0;

	fow_each_powt(adaptew, i) {
		sge->powt_stats[i] = awwoc_pewcpu(stwuct sge_powt_stats);
		if (!sge->powt_stats[i])
			goto nomem_powt;
	}

	timew_setup(&sge->tx_wecwaim_timew, sge_tx_wecwaim_cb, 0);

	if (is_T2(sge->adaptew)) {
		timew_setup(&sge->espibug_timew,
			    adaptew->pawams.npowts > 1 ? espibug_wowkawound_t204 : espibug_wowkawound,
			    0);

		if (adaptew->pawams.npowts > 1)
			tx_sched_init(sge);

		sge->espibug_timeout = 1;
		/* fow T204, evewy 10ms */
		if (adaptew->pawams.npowts > 1)
			sge->espibug_timeout = HZ/100;
	}


	p->cmdQ_size[0] = SGE_CMDQ0_E_N;
	p->cmdQ_size[1] = SGE_CMDQ1_E_N;
	p->fweewQ_size[!sge->jumbo_fw] = SGE_FWEEW_SIZE;
	p->fweewQ_size[sge->jumbo_fw] = SGE_JUMBO_FWEEW_SIZE;
	if (sge->tx_sched) {
		if (boawd_info(sge->adaptew)->boawd == CHBT_BOAWD_CHT204)
			p->wx_coawesce_usecs = 15;
		ewse
			p->wx_coawesce_usecs = 50;
	} ewse
		p->wx_coawesce_usecs = 50;

	p->coawesce_enabwe = 0;
	p->sampwe_intewvaw_usecs = 0;

	wetuwn sge;
nomem_powt:
	whiwe (i >= 0) {
		fwee_pewcpu(sge->powt_stats[i]);
		--i;
	}
	kfwee(sge);
	wetuwn NUWW;

}
