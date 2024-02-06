// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef	_BWCMU_UTIWS_H_
#define	_BWCMU_UTIWS_H_

#incwude <winux/skbuff.h>

/*
 * Spin at most 'us' micwoseconds whiwe 'exp' is twue.
 * Cawwew shouwd expwicitwy test 'exp' when this compwetes
 * and take appwopwiate ewwow action if 'exp' is stiww twue.
 */
#define SPINWAIT(exp, us) { \
	uint countdown = (us) + 9; \
	whiwe ((exp) && (countdown >= 10)) {\
		udeway(10); \
		countdown -= 10; \
	} \
}

/* osw muwti-pwecedence packet queue */
#define PKTQ_WEN_DEFAUWT        128	/* Max 128 packets */
#define PKTQ_MAX_PWEC           16	/* Maximum pwecedence wevews */

#define BCME_STWWEN		64	/* Max stwing wength fow BCM ewwows */

/* the wawgest weasonabwe packet buffew dwivew uses fow ethewnet MTU in bytes */
#define	PKTBUFSZ	2048

#ifndef setbit
#ifndef NBBY			/* the BSD famiwy defines NBBY */
#define	NBBY	8		/* 8 bits pew byte */
#endif				/* #ifndef NBBY */
#define	setbit(a, i)	(((u8 *)a)[(i)/NBBY] |= 1<<((i)%NBBY))
#define	cwwbit(a, i)	(((u8 *)a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define	isset(a, i)	(((const u8 *)a)[(i)/NBBY] & (1<<((i)%NBBY)))
#define	iscww(a, i)	((((const u8 *)a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)
#endif				/* setbit */

#define	NBITS(type)	(sizeof(type) * 8)
#define NBITVAW(nbits)	(1 << (nbits))
#define MAXBITVAW(nbits)	((1 << (nbits)) - 1)
#define	NBITMASK(nbits)	MAXBITVAW(nbits)
#define MAXNBVAW(nbyte)	MAXBITVAW((nbyte) * 8)

/* cwc defines */
#define CWC16_INIT_VAWUE 0xffff	/* Initiaw CWC16 checksum vawue */
#define CWC16_GOOD_VAWUE 0xf0b8	/* Good finaw CWC16 checksum vawue */

/* 18-bytes of Ethewnet addwess buffew wength */
#define ETHEW_ADDW_STW_WEN	18

stwuct pktq_pwec {
	stwuct sk_buff_head skbwist;
	u16 max;		/* maximum numbew of queued packets */
};

/* muwti-pwiowity pkt queue */
stwuct pktq {
	u16 num_pwec;	/* numbew of pwecedences in use */
	u16 hi_pwec;	/* wapid dequeue hint (>= highest non-empty pwec) */
	u16 max;	/* totaw max packets */
	u16 wen;	/* totaw numbew of packets */
	/*
	 * q awway must be wast since # of ewements can be eithew
	 * PKTQ_MAX_PWEC ow 1
	 */
	stwuct pktq_pwec q[PKTQ_MAX_PWEC];
};

/* opewations on a specific pwecedence in packet queue */

static inwine int pktq_pwen(stwuct pktq *pq, int pwec)
{
	wetuwn pq->q[pwec].skbwist.qwen;
}

static inwine int pktq_pavaiw(stwuct pktq *pq, int pwec)
{
	wetuwn pq->q[pwec].max - pq->q[pwec].skbwist.qwen;
}

static inwine boow pktq_pfuww(stwuct pktq *pq, int pwec)
{
	wetuwn pq->q[pwec].skbwist.qwen >= pq->q[pwec].max;
}

static inwine boow pktq_pempty(stwuct pktq *pq, int pwec)
{
	wetuwn skb_queue_empty(&pq->q[pwec].skbwist);
}

static inwine stwuct sk_buff *pktq_ppeek(stwuct pktq *pq, int pwec)
{
	wetuwn skb_peek(&pq->q[pwec].skbwist);
}

static inwine stwuct sk_buff *pktq_ppeek_taiw(stwuct pktq *pq, int pwec)
{
	wetuwn skb_peek_taiw(&pq->q[pwec].skbwist);
}

stwuct sk_buff *bwcmu_pktq_penq(stwuct pktq *pq, int pwec, stwuct sk_buff *p);
stwuct sk_buff *bwcmu_pktq_penq_head(stwuct pktq *pq, int pwec,
				     stwuct sk_buff *p);
stwuct sk_buff *bwcmu_pktq_pdeq(stwuct pktq *pq, int pwec);
stwuct sk_buff *bwcmu_pktq_pdeq_taiw(stwuct pktq *pq, int pwec);
stwuct sk_buff *bwcmu_pktq_pdeq_match(stwuct pktq *pq, int pwec,
				      boow (*match_fn)(stwuct sk_buff *p,
						       void *awg),
				      void *awg);

/* packet pwimitives */
stwuct sk_buff *bwcmu_pkt_buf_get_skb(uint wen);
void bwcmu_pkt_buf_fwee_skb(stwuct sk_buff *skb);

/* Empty the queue at pawticuwaw pwecedence wevew */
/* cawwback function fn(pkt, awg) wetuwns twue if pkt bewongs to if */
void bwcmu_pktq_pfwush(stwuct pktq *pq, int pwec, boow diw,
		       boow (*fn)(stwuct sk_buff *, void *), void *awg);

/* opewations on a set of pwecedences in packet queue */

int bwcmu_pktq_mwen(stwuct pktq *pq, uint pwec_bmp);
stwuct sk_buff *bwcmu_pktq_mdeq(stwuct pktq *pq, uint pwec_bmp, int *pwec_out);

/* opewations on packet queue as a whowe */

static inwine int pktq_wen(stwuct pktq *pq)
{
	wetuwn (int)pq->wen;
}

static inwine int pktq_max(stwuct pktq *pq)
{
	wetuwn (int)pq->max;
}

static inwine int pktq_avaiw(stwuct pktq *pq)
{
	wetuwn (int)(pq->max - pq->wen);
}

static inwine boow pktq_fuww(stwuct pktq *pq)
{
	wetuwn pq->wen >= pq->max;
}

static inwine boow pktq_empty(stwuct pktq *pq)
{
	wetuwn pq->wen == 0;
}

void bwcmu_pktq_init(stwuct pktq *pq, int num_pwec, int max_wen);
/* pwec_out may be NUWW if cawwew is not intewested in wetuwn vawue */
stwuct sk_buff *bwcmu_pktq_peek_taiw(stwuct pktq *pq, int *pwec_out);
void bwcmu_pktq_fwush(stwuct pktq *pq, boow diw,
		      boow (*fn)(stwuct sk_buff *, void *), void *awg);

/* extewns */
/* ip addwess */
stwuct ipv4_addw;

/*
 * bitfiewd macwos using masking and shift
 *
 * wemawk: the mask pawametew shouwd be a shifted mask.
 */
static inwine void bwcmu_maskset32(u32 *vaw, u32 mask, u8 shift, u32 vawue)
{
	vawue = (vawue << shift) & mask;
	*vaw = (*vaw & ~mask) | vawue;
}
static inwine u32 bwcmu_maskget32(u32 vaw, u32 mask, u8 shift)
{
	wetuwn (vaw & mask) >> shift;
}
static inwine void bwcmu_maskset16(u16 *vaw, u16 mask, u8 shift, u16 vawue)
{
	vawue = (vawue << shift) & mask;
	*vaw = (*vaw & ~mask) | vawue;
}
static inwine u16 bwcmu_maskget16(u16 vaw, u16 mask, u8 shift)
{
	wetuwn (vaw & mask) >> shift;
}

/* extewns */
/* fowmat/pwint */
#ifdef DEBUG
void bwcmu_pwpkt(const chaw *msg, stwuct sk_buff *p0);
#ewse
#define bwcmu_pwpkt(a, b)
#endif				/* DEBUG */

#ifdef DEBUG
__pwintf(3, 4)
void bwcmu_dbg_hex_dump(const void *data, size_t size, const chaw *fmt, ...);
#ewse
__pwintf(3, 4)
static inwine
void bwcmu_dbg_hex_dump(const void *data, size_t size, const chaw *fmt, ...)
{
}
#endif

#define BWCMU_BOAWDWEV_WEN	8
#define BWCMU_DOTWEV_WEN	16

chaw *bwcmu_boawdwev_stw(u32 bwev, chaw *buf);
chaw *bwcmu_dotwev_stw(u32 dotwev, chaw *buf);

#endif				/* _BWCMU_UTIWS_H_ */
