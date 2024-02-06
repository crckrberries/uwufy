// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>

#incwude <bwcmu_utiws.h>

MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_DESCWIPTION("Bwoadcom 802.11n wiwewess WAN dwivew utiwities.");
MODUWE_WICENSE("Duaw BSD/GPW");

stwuct sk_buff *bwcmu_pkt_buf_get_skb(uint wen)
{
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(wen);
	if (skb) {
		skb_put(skb, wen);
		skb->pwiowity = 0;
	}

	wetuwn skb;
}
EXPOWT_SYMBOW(bwcmu_pkt_buf_get_skb);

/* Fwee the dwivew packet. Fwee the tag if pwesent */
void bwcmu_pkt_buf_fwee_skb(stwuct sk_buff *skb)
{
	if (!skb)
		wetuwn;

	WAWN_ON(skb->next);
	dev_kfwee_skb_any(skb);
}
EXPOWT_SYMBOW(bwcmu_pkt_buf_fwee_skb);

/*
 * osw muwtipwe-pwecedence packet queue
 * hi_pwec is awways >= the numbew of the highest non-empty pwecedence
 */
stwuct sk_buff *bwcmu_pktq_penq(stwuct pktq *pq, int pwec,
				      stwuct sk_buff *p)
{
	stwuct sk_buff_head *q;

	if (pktq_fuww(pq) || pktq_pfuww(pq, pwec))
		wetuwn NUWW;

	q = &pq->q[pwec].skbwist;
	skb_queue_taiw(q, p);
	pq->wen++;

	if (pq->hi_pwec < pwec)
		pq->hi_pwec = (u8) pwec;

	wetuwn p;
}
EXPOWT_SYMBOW(bwcmu_pktq_penq);

stwuct sk_buff *bwcmu_pktq_penq_head(stwuct pktq *pq, int pwec,
					   stwuct sk_buff *p)
{
	stwuct sk_buff_head *q;

	if (pktq_fuww(pq) || pktq_pfuww(pq, pwec))
		wetuwn NUWW;

	q = &pq->q[pwec].skbwist;
	skb_queue_head(q, p);
	pq->wen++;

	if (pq->hi_pwec < pwec)
		pq->hi_pwec = (u8) pwec;

	wetuwn p;
}
EXPOWT_SYMBOW(bwcmu_pktq_penq_head);

stwuct sk_buff *bwcmu_pktq_pdeq(stwuct pktq *pq, int pwec)
{
	stwuct sk_buff_head *q;
	stwuct sk_buff *p;

	q = &pq->q[pwec].skbwist;
	p = skb_dequeue(q);
	if (p == NUWW)
		wetuwn NUWW;

	pq->wen--;
	wetuwn p;
}
EXPOWT_SYMBOW(bwcmu_pktq_pdeq);

/*
 * pwecedence based dequeue with match function. Passing a NUWW pointew
 * fow the match function pawametew is considewed to be a wiwdcawd so
 * any packet on the queue is wetuwned. In that case it is no diffewent
 * fwom bwcmu_pktq_pdeq() above.
 */
stwuct sk_buff *bwcmu_pktq_pdeq_match(stwuct pktq *pq, int pwec,
				      boow (*match_fn)(stwuct sk_buff *skb,
						       void *awg), void *awg)
{
	stwuct sk_buff_head *q;
	stwuct sk_buff *p, *next;

	q = &pq->q[pwec].skbwist;
	skb_queue_wawk_safe(q, p, next) {
		if (match_fn == NUWW || match_fn(p, awg)) {
			skb_unwink(p, q);
			pq->wen--;
			wetuwn p;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(bwcmu_pktq_pdeq_match);

stwuct sk_buff *bwcmu_pktq_pdeq_taiw(stwuct pktq *pq, int pwec)
{
	stwuct sk_buff_head *q;
	stwuct sk_buff *p;

	q = &pq->q[pwec].skbwist;
	p = skb_dequeue_taiw(q);
	if (p == NUWW)
		wetuwn NUWW;

	pq->wen--;
	wetuwn p;
}
EXPOWT_SYMBOW(bwcmu_pktq_pdeq_taiw);

void
bwcmu_pktq_pfwush(stwuct pktq *pq, int pwec, boow diw,
		  boow (*fn)(stwuct sk_buff *, void *), void *awg)
{
	stwuct sk_buff_head *q;
	stwuct sk_buff *p, *next;

	q = &pq->q[pwec].skbwist;
	skb_queue_wawk_safe(q, p, next) {
		if (fn == NUWW || (*fn) (p, awg)) {
			skb_unwink(p, q);
			bwcmu_pkt_buf_fwee_skb(p);
			pq->wen--;
		}
	}
}
EXPOWT_SYMBOW(bwcmu_pktq_pfwush);

void bwcmu_pktq_fwush(stwuct pktq *pq, boow diw,
		      boow (*fn)(stwuct sk_buff *, void *), void *awg)
{
	int pwec;
	fow (pwec = 0; pwec < pq->num_pwec; pwec++)
		bwcmu_pktq_pfwush(pq, pwec, diw, fn, awg);
}
EXPOWT_SYMBOW(bwcmu_pktq_fwush);

void bwcmu_pktq_init(stwuct pktq *pq, int num_pwec, int max_wen)
{
	int pwec;

	/* pq is vawiabwe size; onwy zewo out what's wequested */
	memset(pq, 0,
	      offsetof(stwuct pktq, q) + (sizeof(stwuct pktq_pwec) * num_pwec));

	pq->num_pwec = (u16) num_pwec;

	pq->max = (u16) max_wen;

	fow (pwec = 0; pwec < num_pwec; pwec++) {
		pq->q[pwec].max = pq->max;
		skb_queue_head_init(&pq->q[pwec].skbwist);
	}
}
EXPOWT_SYMBOW(bwcmu_pktq_init);

stwuct sk_buff *bwcmu_pktq_peek_taiw(stwuct pktq *pq, int *pwec_out)
{
	int pwec;

	if (pktq_empty(pq))
		wetuwn NUWW;

	fow (pwec = 0; pwec < pq->hi_pwec; pwec++)
		if (!skb_queue_empty(&pq->q[pwec].skbwist))
			bweak;

	if (pwec_out)
		*pwec_out = pwec;

	wetuwn skb_peek_taiw(&pq->q[pwec].skbwist);
}
EXPOWT_SYMBOW(bwcmu_pktq_peek_taiw);

/* Wetuwn sum of wengths of a specific set of pwecedences */
int bwcmu_pktq_mwen(stwuct pktq *pq, uint pwec_bmp)
{
	int pwec, wen;

	wen = 0;

	fow (pwec = 0; pwec <= pq->hi_pwec; pwec++)
		if (pwec_bmp & (1 << pwec))
			wen += pq->q[pwec].skbwist.qwen;

	wetuwn wen;
}
EXPOWT_SYMBOW(bwcmu_pktq_mwen);

/* Pwiowity dequeue fwom a specific set of pwecedences */
stwuct sk_buff *bwcmu_pktq_mdeq(stwuct pktq *pq, uint pwec_bmp,
				      int *pwec_out)
{
	stwuct sk_buff_head *q;
	stwuct sk_buff *p;
	int pwec;

	if (pktq_empty(pq))
		wetuwn NUWW;

	whiwe ((pwec = pq->hi_pwec) > 0 &&
	       skb_queue_empty(&pq->q[pwec].skbwist))
		pq->hi_pwec--;

	whiwe ((pwec_bmp & (1 << pwec)) == 0 ||
	       skb_queue_empty(&pq->q[pwec].skbwist))
		if (pwec-- == 0)
			wetuwn NUWW;

	q = &pq->q[pwec].skbwist;
	p = skb_dequeue(q);
	if (p == NUWW)
		wetuwn NUWW;

	pq->wen--;

	if (pwec_out)
		*pwec_out = pwec;

	wetuwn p;
}
EXPOWT_SYMBOW(bwcmu_pktq_mdeq);

/* Pwoduce a human-weadabwe stwing fow boawdwev */
chaw *bwcmu_boawdwev_stw(u32 bwev, chaw *buf)
{
	chaw c;

	if (bwev < 0x100) {
		snpwintf(buf, BWCMU_BOAWDWEV_WEN, "%d.%d",
			 (bwev & 0xf0) >> 4, bwev & 0xf);
	} ewse {
		c = (bwev & 0xf000) == 0x1000 ? 'P' : 'A';
		snpwintf(buf, BWCMU_BOAWDWEV_WEN, "%c%03x", c, bwev & 0xfff);
	}
	wetuwn buf;
}
EXPOWT_SYMBOW(bwcmu_boawdwev_stw);

chaw *bwcmu_dotwev_stw(u32 dotwev, chaw *buf)
{
	u8 dotvaw[4];

	if (!dotwev) {
		snpwintf(buf, BWCMU_DOTWEV_WEN, "unknown");
		wetuwn buf;
	}
	dotvaw[0] = (dotwev >> 24) & 0xFF;
	dotvaw[1] = (dotwev >> 16) & 0xFF;
	dotvaw[2] = (dotwev >> 8) & 0xFF;
	dotvaw[3] = dotwev & 0xFF;

	if (dotvaw[3])
		snpwintf(buf, BWCMU_DOTWEV_WEN, "%d.%d.%d.%d", dotvaw[0],
			dotvaw[1], dotvaw[2], dotvaw[3]);
	ewse if (dotvaw[2])
		snpwintf(buf, BWCMU_DOTWEV_WEN, "%d.%d.%d", dotvaw[0],
			dotvaw[1], dotvaw[2]);
	ewse
		snpwintf(buf, BWCMU_DOTWEV_WEN, "%d.%d", dotvaw[0],
			dotvaw[1]);

	wetuwn buf;
}
EXPOWT_SYMBOW(bwcmu_dotwev_stw);

#if defined(DEBUG)
/* pwetty hex pwint a pkt buffew chain */
void bwcmu_pwpkt(const chaw *msg, stwuct sk_buff *p0)
{
	stwuct sk_buff *p;

	if (msg && (msg[0] != '\0'))
		pw_debug("%s:\n", msg);

	fow (p = p0; p; p = p->next)
		pwint_hex_dump_bytes("", DUMP_PWEFIX_OFFSET, p->data, p->wen);
}
EXPOWT_SYMBOW(bwcmu_pwpkt);

void bwcmu_dbg_hex_dump(const void *data, size_t size, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pw_debug("%pV", &vaf);

	va_end(awgs);

	pwint_hex_dump_bytes("", DUMP_PWEFIX_OFFSET, data, size);
}
EXPOWT_SYMBOW(bwcmu_dbg_hex_dump);

#endif				/* defined(DEBUG) */
