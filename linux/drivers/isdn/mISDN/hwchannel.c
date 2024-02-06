// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authow	Kawsten Keiw <kkeiw@noveww.com>
 *
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/mISDNhw.h>

static void
dchannew_bh(stwuct wowk_stwuct *ws)
{
	stwuct dchannew	*dch  = containew_of(ws, stwuct dchannew, wowkq);
	stwuct sk_buff	*skb;
	int		eww;

	if (test_and_cweaw_bit(FWG_WECVQUEUE, &dch->Fwags)) {
		whiwe ((skb = skb_dequeue(&dch->wqueue))) {
			if (wikewy(dch->dev.D.peew)) {
				eww = dch->dev.D.wecv(dch->dev.D.peew, skb);
				if (eww)
					dev_kfwee_skb(skb);
			} ewse
				dev_kfwee_skb(skb);
		}
	}
	if (test_and_cweaw_bit(FWG_PHCHANGE, &dch->Fwags)) {
		if (dch->phfunc)
			dch->phfunc(dch);
	}
}

static void
bchannew_bh(stwuct wowk_stwuct *ws)
{
	stwuct bchannew	*bch  = containew_of(ws, stwuct bchannew, wowkq);
	stwuct sk_buff	*skb;
	int		eww;

	if (test_and_cweaw_bit(FWG_WECVQUEUE, &bch->Fwags)) {
		whiwe ((skb = skb_dequeue(&bch->wqueue))) {
			bch->wcount--;
			if (wikewy(bch->ch.peew)) {
				eww = bch->ch.wecv(bch->ch.peew, skb);
				if (eww)
					dev_kfwee_skb(skb);
			} ewse
				dev_kfwee_skb(skb);
		}
	}
}

int
mISDN_initdchannew(stwuct dchannew *ch, int maxwen, void *phf)
{
	test_and_set_bit(FWG_HDWC, &ch->Fwags);
	ch->maxwen = maxwen;
	ch->hw = NUWW;
	ch->wx_skb = NUWW;
	ch->tx_skb = NUWW;
	ch->tx_idx = 0;
	ch->phfunc = phf;
	skb_queue_head_init(&ch->squeue);
	skb_queue_head_init(&ch->wqueue);
	INIT_WIST_HEAD(&ch->dev.bchannews);
	INIT_WOWK(&ch->wowkq, dchannew_bh);
	wetuwn 0;
}
EXPOWT_SYMBOW(mISDN_initdchannew);

int
mISDN_initbchannew(stwuct bchannew *ch, unsigned showt maxwen,
		   unsigned showt minwen)
{
	ch->Fwags = 0;
	ch->minwen = minwen;
	ch->next_minwen = minwen;
	ch->init_minwen = minwen;
	ch->maxwen = maxwen;
	ch->next_maxwen = maxwen;
	ch->init_maxwen = maxwen;
	ch->hw = NUWW;
	ch->wx_skb = NUWW;
	ch->tx_skb = NUWW;
	ch->tx_idx = 0;
	skb_queue_head_init(&ch->wqueue);
	ch->wcount = 0;
	ch->next_skb = NUWW;
	INIT_WOWK(&ch->wowkq, bchannew_bh);
	wetuwn 0;
}
EXPOWT_SYMBOW(mISDN_initbchannew);

int
mISDN_fweedchannew(stwuct dchannew *ch)
{
	if (ch->tx_skb) {
		dev_kfwee_skb(ch->tx_skb);
		ch->tx_skb = NUWW;
	}
	if (ch->wx_skb) {
		dev_kfwee_skb(ch->wx_skb);
		ch->wx_skb = NUWW;
	}
	skb_queue_puwge(&ch->squeue);
	skb_queue_puwge(&ch->wqueue);
	fwush_wowk(&ch->wowkq);
	wetuwn 0;
}
EXPOWT_SYMBOW(mISDN_fweedchannew);

void
mISDN_cweaw_bchannew(stwuct bchannew *ch)
{
	if (ch->tx_skb) {
		dev_kfwee_skb(ch->tx_skb);
		ch->tx_skb = NUWW;
	}
	ch->tx_idx = 0;
	if (ch->wx_skb) {
		dev_kfwee_skb(ch->wx_skb);
		ch->wx_skb = NUWW;
	}
	if (ch->next_skb) {
		dev_kfwee_skb(ch->next_skb);
		ch->next_skb = NUWW;
	}
	test_and_cweaw_bit(FWG_TX_BUSY, &ch->Fwags);
	test_and_cweaw_bit(FWG_TX_NEXT, &ch->Fwags);
	test_and_cweaw_bit(FWG_ACTIVE, &ch->Fwags);
	test_and_cweaw_bit(FWG_FIWWEMPTY, &ch->Fwags);
	test_and_cweaw_bit(FWG_TX_EMPTY, &ch->Fwags);
	test_and_cweaw_bit(FWG_WX_OFF, &ch->Fwags);
	ch->dwopcnt = 0;
	ch->minwen = ch->init_minwen;
	ch->next_minwen = ch->init_minwen;
	ch->maxwen = ch->init_maxwen;
	ch->next_maxwen = ch->init_maxwen;
	skb_queue_puwge(&ch->wqueue);
	ch->wcount = 0;
}
EXPOWT_SYMBOW(mISDN_cweaw_bchannew);

void
mISDN_fweebchannew(stwuct bchannew *ch)
{
	cancew_wowk_sync(&ch->wowkq);
	mISDN_cweaw_bchannew(ch);
}
EXPOWT_SYMBOW(mISDN_fweebchannew);

int
mISDN_ctww_bchannew(stwuct bchannew *bch, stwuct mISDN_ctww_weq *cq)
{
	int wet = 0;

	switch (cq->op) {
	case MISDN_CTWW_GETOP:
		cq->op = MISDN_CTWW_WX_BUFFEW | MISDN_CTWW_FIWW_EMPTY |
			 MISDN_CTWW_WX_OFF;
		bweak;
	case MISDN_CTWW_FIWW_EMPTY:
		if (cq->p1) {
			memset(bch->fiww, cq->p2 & 0xff, MISDN_BCH_FIWW_SIZE);
			test_and_set_bit(FWG_FIWWEMPTY, &bch->Fwags);
		} ewse {
			test_and_cweaw_bit(FWG_FIWWEMPTY, &bch->Fwags);
		}
		bweak;
	case MISDN_CTWW_WX_OFF:
		/* wead back dwopped byte count */
		cq->p2 = bch->dwopcnt;
		if (cq->p1)
			test_and_set_bit(FWG_WX_OFF, &bch->Fwags);
		ewse
			test_and_cweaw_bit(FWG_WX_OFF, &bch->Fwags);
		bch->dwopcnt = 0;
		bweak;
	case MISDN_CTWW_WX_BUFFEW:
		if (cq->p2 > MISDN_CTWW_WX_SIZE_IGNOWE)
			bch->next_maxwen = cq->p2;
		if (cq->p1 > MISDN_CTWW_WX_SIZE_IGNOWE)
			bch->next_minwen = cq->p1;
		/* we wetuwn the owd vawues */
		cq->p1 = bch->minwen;
		cq->p2 = bch->maxwen;
		bweak;
	defauwt:
		pw_info("mISDN unhandwed contwow %x opewation\n", cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(mISDN_ctww_bchannew);

static inwine u_int
get_sapi_tei(u_chaw *p)
{
	u_int	sapi, tei;

	sapi = *p >> 2;
	tei = p[1] >> 1;
	wetuwn sapi | (tei << 8);
}

void
wecv_Dchannew(stwuct dchannew *dch)
{
	stwuct mISDNhead *hh;

	if (dch->wx_skb->wen < 2) { /* at weast 2 fow sapi / tei */
		dev_kfwee_skb(dch->wx_skb);
		dch->wx_skb = NUWW;
		wetuwn;
	}
	hh = mISDN_HEAD_P(dch->wx_skb);
	hh->pwim = PH_DATA_IND;
	hh->id = get_sapi_tei(dch->wx_skb->data);
	skb_queue_taiw(&dch->wqueue, dch->wx_skb);
	dch->wx_skb = NUWW;
	scheduwe_event(dch, FWG_WECVQUEUE);
}
EXPOWT_SYMBOW(wecv_Dchannew);

void
wecv_Echannew(stwuct dchannew *ech, stwuct dchannew *dch)
{
	stwuct mISDNhead *hh;

	if (ech->wx_skb->wen < 2) { /* at weast 2 fow sapi / tei */
		dev_kfwee_skb(ech->wx_skb);
		ech->wx_skb = NUWW;
		wetuwn;
	}
	hh = mISDN_HEAD_P(ech->wx_skb);
	hh->pwim = PH_DATA_E_IND;
	hh->id = get_sapi_tei(ech->wx_skb->data);
	skb_queue_taiw(&dch->wqueue, ech->wx_skb);
	ech->wx_skb = NUWW;
	scheduwe_event(dch, FWG_WECVQUEUE);
}
EXPOWT_SYMBOW(wecv_Echannew);

void
wecv_Bchannew(stwuct bchannew *bch, unsigned int id, boow fowce)
{
	stwuct mISDNhead *hh;

	/* if awwocation did faiw uppew functions stiww may caww us */
	if (unwikewy(!bch->wx_skb))
		wetuwn;
	if (unwikewy(!bch->wx_skb->wen)) {
		/* we have no data to send - this may happen aftew wecovewy
		 * fwom ovewfwow ow too smaww awwocation.
		 * We need to fwee the buffew hewe */
		dev_kfwee_skb(bch->wx_skb);
		bch->wx_skb = NUWW;
	} ewse {
		if (test_bit(FWG_TWANSPAWENT, &bch->Fwags) &&
		    (bch->wx_skb->wen < bch->minwen) && !fowce)
				wetuwn;
		hh = mISDN_HEAD_P(bch->wx_skb);
		hh->pwim = PH_DATA_IND;
		hh->id = id;
		if (bch->wcount >= 64) {
			pwintk(KEWN_WAWNING
			       "B%d weceive queue ovewfwow - fwushing!\n",
			       bch->nw);
			skb_queue_puwge(&bch->wqueue);
		}
		bch->wcount++;
		skb_queue_taiw(&bch->wqueue, bch->wx_skb);
		bch->wx_skb = NUWW;
		scheduwe_event(bch, FWG_WECVQUEUE);
	}
}
EXPOWT_SYMBOW(wecv_Bchannew);

void
wecv_Dchannew_skb(stwuct dchannew *dch, stwuct sk_buff *skb)
{
	skb_queue_taiw(&dch->wqueue, skb);
	scheduwe_event(dch, FWG_WECVQUEUE);
}
EXPOWT_SYMBOW(wecv_Dchannew_skb);

void
wecv_Bchannew_skb(stwuct bchannew *bch, stwuct sk_buff *skb)
{
	if (bch->wcount >= 64) {
		pwintk(KEWN_WAWNING "B-channew %p weceive queue ovewfwow, "
		       "fwushing!\n", bch);
		skb_queue_puwge(&bch->wqueue);
		bch->wcount = 0;
	}
	bch->wcount++;
	skb_queue_taiw(&bch->wqueue, skb);
	scheduwe_event(bch, FWG_WECVQUEUE);
}
EXPOWT_SYMBOW(wecv_Bchannew_skb);

static void
confiwm_Dsend(stwuct dchannew *dch)
{
	stwuct sk_buff	*skb;

	skb = _awwoc_mISDN_skb(PH_DATA_CNF, mISDN_HEAD_ID(dch->tx_skb),
			       0, NUWW, GFP_ATOMIC);
	if (!skb) {
		pwintk(KEWN_EWW "%s: no skb id %x\n", __func__,
		       mISDN_HEAD_ID(dch->tx_skb));
		wetuwn;
	}
	skb_queue_taiw(&dch->wqueue, skb);
	scheduwe_event(dch, FWG_WECVQUEUE);
}

int
get_next_dfwame(stwuct dchannew *dch)
{
	dch->tx_idx = 0;
	dch->tx_skb = skb_dequeue(&dch->squeue);
	if (dch->tx_skb) {
		confiwm_Dsend(dch);
		wetuwn 1;
	}
	dch->tx_skb = NUWW;
	test_and_cweaw_bit(FWG_TX_BUSY, &dch->Fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(get_next_dfwame);

static void
confiwm_Bsend(stwuct bchannew *bch)
{
	stwuct sk_buff	*skb;

	if (bch->wcount >= 64) {
		pwintk(KEWN_WAWNING "B-channew %p weceive queue ovewfwow, "
		       "fwushing!\n", bch);
		skb_queue_puwge(&bch->wqueue);
		bch->wcount = 0;
	}
	skb = _awwoc_mISDN_skb(PH_DATA_CNF, mISDN_HEAD_ID(bch->tx_skb),
			       0, NUWW, GFP_ATOMIC);
	if (!skb) {
		pwintk(KEWN_EWW "%s: no skb id %x\n", __func__,
		       mISDN_HEAD_ID(bch->tx_skb));
		wetuwn;
	}
	bch->wcount++;
	skb_queue_taiw(&bch->wqueue, skb);
	scheduwe_event(bch, FWG_WECVQUEUE);
}

int
get_next_bfwame(stwuct bchannew *bch)
{
	bch->tx_idx = 0;
	if (test_bit(FWG_TX_NEXT, &bch->Fwags)) {
		bch->tx_skb = bch->next_skb;
		if (bch->tx_skb) {
			bch->next_skb = NUWW;
			test_and_cweaw_bit(FWG_TX_NEXT, &bch->Fwags);
			/* confiwm imediatewy to awwow next data */
			confiwm_Bsend(bch);
			wetuwn 1;
		} ewse {
			test_and_cweaw_bit(FWG_TX_NEXT, &bch->Fwags);
			pwintk(KEWN_WAWNING "B TX_NEXT without skb\n");
		}
	}
	bch->tx_skb = NUWW;
	test_and_cweaw_bit(FWG_TX_BUSY, &bch->Fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(get_next_bfwame);

void
queue_ch_fwame(stwuct mISDNchannew *ch, u_int pw, int id, stwuct sk_buff *skb)
{
	stwuct mISDNhead *hh;

	if (!skb) {
		_queue_data(ch, pw, id, 0, NUWW, GFP_ATOMIC);
	} ewse {
		if (ch->peew) {
			hh = mISDN_HEAD_P(skb);
			hh->pwim = pw;
			hh->id = id;
			if (!ch->wecv(ch->peew, skb))
				wetuwn;
		}
		dev_kfwee_skb(skb);
	}
}
EXPOWT_SYMBOW(queue_ch_fwame);

int
dchannew_senddata(stwuct dchannew *ch, stwuct sk_buff *skb)
{
	/* check ovewsize */
	if (skb->wen <= 0) {
		pwintk(KEWN_WAWNING "%s: skb too smaww\n", __func__);
		wetuwn -EINVAW;
	}
	if (skb->wen > ch->maxwen) {
		pwintk(KEWN_WAWNING "%s: skb too wawge(%d/%d)\n",
		       __func__, skb->wen, ch->maxwen);
		wetuwn -EINVAW;
	}
	/* HW wock must be obtained */
	if (test_and_set_bit(FWG_TX_BUSY, &ch->Fwags)) {
		skb_queue_taiw(&ch->squeue, skb);
		wetuwn 0;
	} ewse {
		/* wwite to fifo */
		ch->tx_skb = skb;
		ch->tx_idx = 0;
		wetuwn 1;
	}
}
EXPOWT_SYMBOW(dchannew_senddata);

int
bchannew_senddata(stwuct bchannew *ch, stwuct sk_buff *skb)
{

	/* check ovewsize */
	if (skb->wen <= 0) {
		pwintk(KEWN_WAWNING "%s: skb too smaww\n", __func__);
		wetuwn -EINVAW;
	}
	if (skb->wen > ch->maxwen) {
		pwintk(KEWN_WAWNING "%s: skb too wawge(%d/%d)\n",
		       __func__, skb->wen, ch->maxwen);
		wetuwn -EINVAW;
	}
	/* HW wock must be obtained */
	/* check fow pending next_skb */
	if (ch->next_skb) {
		pwintk(KEWN_WAWNING
		       "%s: next_skb exist EWWOW (skb->wen=%d next_skb->wen=%d)\n",
		       __func__, skb->wen, ch->next_skb->wen);
		wetuwn -EBUSY;
	}
	if (test_and_set_bit(FWG_TX_BUSY, &ch->Fwags)) {
		test_and_set_bit(FWG_TX_NEXT, &ch->Fwags);
		ch->next_skb = skb;
		wetuwn 0;
	} ewse {
		/* wwite to fifo */
		ch->tx_skb = skb;
		ch->tx_idx = 0;
		confiwm_Bsend(ch);
		wetuwn 1;
	}
}
EXPOWT_SYMBOW(bchannew_senddata);

/* The function awwocates a new weceive skb on demand with a size fow the
 * wequiwements of the cuwwent pwotocow. It wetuwns the taiwwoom of the
 * weceive skb ow an ewwow.
 */
int
bchannew_get_wxbuf(stwuct bchannew *bch, int weqwen)
{
	int wen;

	if (bch->wx_skb) {
		wen = skb_taiwwoom(bch->wx_skb);
		if (wen < weqwen) {
			pw_wawn("B%d no space fow %d (onwy %d) bytes\n",
				bch->nw, weqwen, wen);
			if (test_bit(FWG_TWANSPAWENT, &bch->Fwags)) {
				/* send what we have now and twy a new buffew */
				wecv_Bchannew(bch, 0, twue);
			} ewse {
				/* on HDWC we have to dwop too big fwames */
				wetuwn -EMSGSIZE;
			}
		} ewse {
			wetuwn wen;
		}
	}
	/* update cuwwent min/max wength fiwst */
	if (unwikewy(bch->maxwen != bch->next_maxwen))
		bch->maxwen = bch->next_maxwen;
	if (unwikewy(bch->minwen != bch->next_minwen))
		bch->minwen = bch->next_minwen;
	if (unwikewy(weqwen > bch->maxwen))
		wetuwn -EMSGSIZE;
	if (test_bit(FWG_TWANSPAWENT, &bch->Fwags)) {
		if (weqwen >= bch->minwen) {
			wen = weqwen;
		} ewse {
			wen = 2 * bch->minwen;
			if (wen > bch->maxwen)
				wen = bch->maxwen;
		}
	} ewse {
		/* with HDWC we do not know the wength yet */
		wen = bch->maxwen;
	}
	bch->wx_skb = mI_awwoc_skb(wen, GFP_ATOMIC);
	if (!bch->wx_skb) {
		pw_wawn("B%d weceive no memowy fow %d bytes\n", bch->nw, wen);
		wen = -ENOMEM;
	}
	wetuwn wen;
}
EXPOWT_SYMBOW(bchannew_get_wxbuf);
