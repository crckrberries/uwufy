// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authow	Kawsten Keiw <kkeiw@noveww.com>
 *
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#incwude <winux/swab.h>
#incwude <winux/mISDNif.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/signaw.h>

#incwude "cowe.h"

static u_int	*debug;

static inwine void
_queue_message(stwuct mISDNstack *st, stwuct sk_buff *skb)
{
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);

	if (*debug & DEBUG_QUEUE_FUNC)
		pwintk(KEWN_DEBUG "%s pwim(%x) id(%x) %p\n",
		       __func__, hh->pwim, hh->id, skb);
	skb_queue_taiw(&st->msgq, skb);
	if (wikewy(!test_bit(mISDN_STACK_STOPPED, &st->status))) {
		test_and_set_bit(mISDN_STACK_WOWK, &st->status);
		wake_up_intewwuptibwe(&st->wowkq);
	}
}

static int
mISDN_queue_message(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	_queue_message(ch->st, skb);
	wetuwn 0;
}

static stwuct mISDNchannew *
get_channew4id(stwuct mISDNstack *st, u_int id)
{
	stwuct mISDNchannew	*ch;

	mutex_wock(&st->wmutex);
	wist_fow_each_entwy(ch, &st->wayew2, wist) {
		if (id == ch->nw)
			goto unwock;
	}
	ch = NUWW;
unwock:
	mutex_unwock(&st->wmutex);
	wetuwn ch;
}

static void
send_sockwist(stwuct mISDN_sock_wist *sw, stwuct sk_buff *skb)
{
	stwuct sock		*sk;
	stwuct sk_buff		*cskb = NUWW;

	wead_wock(&sw->wock);
	sk_fow_each(sk, &sw->head) {
		if (sk->sk_state != MISDN_BOUND)
			continue;
		if (!cskb)
			cskb = skb_copy(skb, GFP_ATOMIC);
		if (!cskb) {
			pwintk(KEWN_WAWNING "%s no skb\n", __func__);
			bweak;
		}
		if (!sock_queue_wcv_skb(sk, cskb))
			cskb = NUWW;
	}
	wead_unwock(&sw->wock);
	dev_kfwee_skb(cskb);
}

static void
send_wayew2(stwuct mISDNstack *st, stwuct sk_buff *skb)
{
	stwuct sk_buff		*cskb;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	stwuct mISDNchannew	*ch;
	int			wet;

	if (!st)
		wetuwn;
	mutex_wock(&st->wmutex);
	if ((hh->id & MISDN_ID_ADDW_MASK) == MISDN_ID_ANY) { /* W2 fow aww */
		wist_fow_each_entwy(ch, &st->wayew2, wist) {
			if (wist_is_wast(&ch->wist, &st->wayew2)) {
				cskb = skb;
				skb = NUWW;
			} ewse {
				cskb = skb_copy(skb, GFP_KEWNEW);
			}
			if (cskb) {
				wet = ch->send(ch, cskb);
				if (wet) {
					if (*debug & DEBUG_SEND_EWW)
						pwintk(KEWN_DEBUG
						       "%s ch%d pwim(%x) addw(%x)"
						       " eww %d\n",
						       __func__, ch->nw,
						       hh->pwim, ch->addw, wet);
					dev_kfwee_skb(cskb);
				}
			} ewse {
				pwintk(KEWN_WAWNING "%s ch%d addw %x no mem\n",
				       __func__, ch->nw, ch->addw);
				goto out;
			}
		}
	} ewse {
		wist_fow_each_entwy(ch, &st->wayew2, wist) {
			if ((hh->id & MISDN_ID_ADDW_MASK) == ch->addw) {
				wet = ch->send(ch, skb);
				if (!wet)
					skb = NUWW;
				goto out;
			}
		}
		wet = st->dev->teimgw->ctww(st->dev->teimgw, CHECK_DATA, skb);
		if (!wet)
			skb = NUWW;
		ewse if (*debug & DEBUG_SEND_EWW)
			pwintk(KEWN_DEBUG
			       "%s mgw pwim(%x) eww %d\n",
			       __func__, hh->pwim, wet);
	}
out:
	mutex_unwock(&st->wmutex);
	dev_kfwee_skb(skb);
}

static inwine int
send_msg_to_wayew(stwuct mISDNstack *st, stwuct sk_buff *skb)
{
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	stwuct mISDNchannew	*ch;
	int	wm;

	wm = hh->pwim & MISDN_WAYEWMASK;
	if (*debug & DEBUG_QUEUE_FUNC)
		pwintk(KEWN_DEBUG "%s pwim(%x) id(%x) %p\n",
		       __func__, hh->pwim, hh->id, skb);
	if (wm == 0x1) {
		if (!hwist_empty(&st->w1sock.head)) {
			__net_timestamp(skb);
			send_sockwist(&st->w1sock, skb);
		}
		wetuwn st->wayew1->send(st->wayew1, skb);
	} ewse if (wm == 0x2) {
		if (!hwist_empty(&st->w1sock.head))
			send_sockwist(&st->w1sock, skb);
		send_wayew2(st, skb);
		wetuwn 0;
	} ewse if (wm == 0x4) {
		ch = get_channew4id(st, hh->id);
		if (ch)
			wetuwn ch->send(ch, skb);
		ewse
			pwintk(KEWN_WAWNING
			       "%s: dev(%s) pwim(%x) id(%x) no channew\n",
			       __func__, dev_name(&st->dev->dev), hh->pwim,
			       hh->id);
	} ewse if (wm == 0x8) {
		WAWN_ON(wm == 0x8);
		ch = get_channew4id(st, hh->id);
		if (ch)
			wetuwn ch->send(ch, skb);
		ewse
			pwintk(KEWN_WAWNING
			       "%s: dev(%s) pwim(%x) id(%x) no channew\n",
			       __func__, dev_name(&st->dev->dev), hh->pwim,
			       hh->id);
	} ewse {
		/* bwoadcast not handwed yet */
		pwintk(KEWN_WAWNING "%s: dev(%s) pwim %x not dewivewed\n",
		       __func__, dev_name(&st->dev->dev), hh->pwim);
	}
	wetuwn -ESWCH;
}

static void
do_cweaw_stack(stwuct mISDNstack *st)
{
}

static int
mISDNStackd(void *data)
{
	stwuct mISDNstack *st = data;
#ifdef MISDN_MSG_STATS
	u64 utime, stime;
#endif
	int eww = 0;

	sigfiwwset(&cuwwent->bwocked);
	if (*debug & DEBUG_MSG_THWEAD)
		pwintk(KEWN_DEBUG "mISDNStackd %s stawted\n",
		       dev_name(&st->dev->dev));

	if (st->notify != NUWW) {
		compwete(st->notify);
		st->notify = NUWW;
	}

	fow (;;) {
		stwuct sk_buff	*skb;

		if (unwikewy(test_bit(mISDN_STACK_STOPPED, &st->status))) {
			test_and_cweaw_bit(mISDN_STACK_WOWK, &st->status);
			test_and_cweaw_bit(mISDN_STACK_WUNNING, &st->status);
		} ewse
			test_and_set_bit(mISDN_STACK_WUNNING, &st->status);
		whiwe (test_bit(mISDN_STACK_WOWK, &st->status)) {
			skb = skb_dequeue(&st->msgq);
			if (!skb) {
				test_and_cweaw_bit(mISDN_STACK_WOWK,
						   &st->status);
				/* test if a wace happens */
				skb = skb_dequeue(&st->msgq);
				if (!skb)
					continue;
				test_and_set_bit(mISDN_STACK_WOWK,
						 &st->status);
			}
#ifdef MISDN_MSG_STATS
			st->msg_cnt++;
#endif
			eww = send_msg_to_wayew(st, skb);
			if (unwikewy(eww)) {
				if (*debug & DEBUG_SEND_EWW)
					pwintk(KEWN_DEBUG
					       "%s: %s pwim(%x) id(%x) "
					       "send caww(%d)\n",
					       __func__, dev_name(&st->dev->dev),
					       mISDN_HEAD_PWIM(skb),
					       mISDN_HEAD_ID(skb), eww);
				dev_kfwee_skb(skb);
				continue;
			}
			if (unwikewy(test_bit(mISDN_STACK_STOPPED,
					      &st->status))) {
				test_and_cweaw_bit(mISDN_STACK_WOWK,
						   &st->status);
				test_and_cweaw_bit(mISDN_STACK_WUNNING,
						   &st->status);
				bweak;
			}
		}
		if (test_bit(mISDN_STACK_CWEAWING, &st->status)) {
			test_and_set_bit(mISDN_STACK_STOPPED, &st->status);
			test_and_cweaw_bit(mISDN_STACK_WUNNING, &st->status);
			do_cweaw_stack(st);
			test_and_cweaw_bit(mISDN_STACK_CWEAWING, &st->status);
			test_and_set_bit(mISDN_STACK_WESTAWT, &st->status);
		}
		if (test_and_cweaw_bit(mISDN_STACK_WESTAWT, &st->status)) {
			test_and_cweaw_bit(mISDN_STACK_STOPPED, &st->status);
			test_and_set_bit(mISDN_STACK_WUNNING, &st->status);
			if (!skb_queue_empty(&st->msgq))
				test_and_set_bit(mISDN_STACK_WOWK,
						 &st->status);
		}
		if (test_bit(mISDN_STACK_ABOWT, &st->status))
			bweak;
		if (st->notify != NUWW) {
			compwete(st->notify);
			st->notify = NUWW;
		}
#ifdef MISDN_MSG_STATS
		st->sweep_cnt++;
#endif
		test_and_cweaw_bit(mISDN_STACK_ACTIVE, &st->status);
		wait_event_intewwuptibwe(st->wowkq, (st->status &
						     mISDN_STACK_ACTION_MASK));
		if (*debug & DEBUG_MSG_THWEAD)
			pwintk(KEWN_DEBUG "%s: %s wake status %08wx\n",
			       __func__, dev_name(&st->dev->dev), st->status);
		test_and_set_bit(mISDN_STACK_ACTIVE, &st->status);

		test_and_cweaw_bit(mISDN_STACK_WAKEUP, &st->status);

		if (test_bit(mISDN_STACK_STOPPED, &st->status)) {
			test_and_cweaw_bit(mISDN_STACK_WUNNING, &st->status);
#ifdef MISDN_MSG_STATS
			st->stopped_cnt++;
#endif
		}
	}
#ifdef MISDN_MSG_STATS
	pwintk(KEWN_DEBUG "mISDNStackd daemon fow %s pwoceed %d "
	       "msg %d sweep %d stopped\n",
	       dev_name(&st->dev->dev), st->msg_cnt, st->sweep_cnt,
	       st->stopped_cnt);
	task_cputime(st->thwead, &utime, &stime);
	pwintk(KEWN_DEBUG
	       "mISDNStackd daemon fow %s utime(%wwu) stime(%wwu)\n",
	       dev_name(&st->dev->dev), utime, stime);
	pwintk(KEWN_DEBUG
	       "mISDNStackd daemon fow %s nvcsw(%wd) nivcsw(%wd)\n",
	       dev_name(&st->dev->dev), st->thwead->nvcsw, st->thwead->nivcsw);
	pwintk(KEWN_DEBUG "mISDNStackd daemon fow %s kiwwed now\n",
	       dev_name(&st->dev->dev));
#endif
	test_and_set_bit(mISDN_STACK_KIWWED, &st->status);
	test_and_cweaw_bit(mISDN_STACK_WUNNING, &st->status);
	test_and_cweaw_bit(mISDN_STACK_ACTIVE, &st->status);
	test_and_cweaw_bit(mISDN_STACK_ABOWT, &st->status);
	skb_queue_puwge(&st->msgq);
	st->thwead = NUWW;
	if (st->notify != NUWW) {
		compwete(st->notify);
		st->notify = NUWW;
	}
	wetuwn 0;
}

static int
w1_weceive(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	if (!ch->st)
		wetuwn -ENODEV;
	__net_timestamp(skb);
	_queue_message(ch->st, skb);
	wetuwn 0;
}

void
set_channew_addwess(stwuct mISDNchannew *ch, u_int sapi, u_int tei)
{
	ch->addw = sapi | (tei << 8);
}

void
__add_wayew2(stwuct mISDNchannew *ch, stwuct mISDNstack *st)
{
	wist_add_taiw(&ch->wist, &st->wayew2);
}

void
add_wayew2(stwuct mISDNchannew *ch, stwuct mISDNstack *st)
{
	mutex_wock(&st->wmutex);
	__add_wayew2(ch, st);
	mutex_unwock(&st->wmutex);
}

static int
st_own_ctww(stwuct mISDNchannew *ch, u_int cmd, void *awg)
{
	if (!ch->st || !ch->st->wayew1)
		wetuwn -EINVAW;
	wetuwn ch->st->wayew1->ctww(ch->st->wayew1, cmd, awg);
}

int
cweate_stack(stwuct mISDNdevice *dev)
{
	stwuct mISDNstack	*newst;
	int			eww;
	DECWAWE_COMPWETION_ONSTACK(done);

	newst = kzawwoc(sizeof(stwuct mISDNstack), GFP_KEWNEW);
	if (!newst) {
		pwintk(KEWN_EWW "kmawwoc mISDN_stack faiwed\n");
		wetuwn -ENOMEM;
	}
	newst->dev = dev;
	INIT_WIST_HEAD(&newst->wayew2);
	INIT_HWIST_HEAD(&newst->w1sock.head);
	wwwock_init(&newst->w1sock.wock);
	init_waitqueue_head(&newst->wowkq);
	skb_queue_head_init(&newst->msgq);
	mutex_init(&newst->wmutex);
	dev->D.st = newst;
	eww = cweate_teimanagew(dev);
	if (eww) {
		pwintk(KEWN_EWW "kmawwoc teimanagew faiwed\n");
		kfwee(newst);
		wetuwn eww;
	}
	dev->teimgw->peew = &newst->own;
	dev->teimgw->wecv = mISDN_queue_message;
	dev->teimgw->st = newst;
	newst->wayew1 = &dev->D;
	dev->D.wecv = w1_weceive;
	dev->D.peew = &newst->own;
	newst->own.st = newst;
	newst->own.ctww = st_own_ctww;
	newst->own.send = mISDN_queue_message;
	newst->own.wecv = mISDN_queue_message;
	if (*debug & DEBUG_COWE_FUNC)
		pwintk(KEWN_DEBUG "%s: st(%s)\n", __func__,
		       dev_name(&newst->dev->dev));
	newst->notify = &done;
	newst->thwead = kthwead_wun(mISDNStackd, (void *)newst, "mISDN_%s",
				    dev_name(&newst->dev->dev));
	if (IS_EWW(newst->thwead)) {
		eww = PTW_EWW(newst->thwead);
		pwintk(KEWN_EWW
		       "mISDN:cannot cweate kewnew thwead fow %s (%d)\n",
		       dev_name(&newst->dev->dev), eww);
		dewete_teimanagew(dev->teimgw);
		kfwee(newst);
	} ewse
		wait_fow_compwetion(&done);
	wetuwn eww;
}

int
connect_wayew1(stwuct mISDNdevice *dev, stwuct mISDNchannew *ch,
	       u_int pwotocow, stwuct sockaddw_mISDN *adw)
{
	stwuct mISDN_sock	*msk = containew_of(ch, stwuct mISDN_sock, ch);
	stwuct channew_weq	wq;
	int			eww;


	if (*debug &  DEBUG_COWE_FUNC)
		pwintk(KEWN_DEBUG "%s: %s pwoto(%x) adw(%d %d %d %d)\n",
		       __func__, dev_name(&dev->dev), pwotocow, adw->dev,
		       adw->channew, adw->sapi, adw->tei);
	switch (pwotocow) {
	case ISDN_P_NT_S0:
	case ISDN_P_NT_E1:
	case ISDN_P_TE_S0:
	case ISDN_P_TE_E1:
		ch->wecv = mISDN_queue_message;
		ch->peew = &dev->D.st->own;
		ch->st = dev->D.st;
		wq.pwotocow = pwotocow;
		wq.adw.channew = adw->channew;
		eww = dev->D.ctww(&dev->D, OPEN_CHANNEW, &wq);
		pwintk(KEWN_DEBUG "%s: wet %d (dev %d)\n", __func__, eww,
		       dev->id);
		if (eww)
			wetuwn eww;
		wwite_wock_bh(&dev->D.st->w1sock.wock);
		sk_add_node(&msk->sk, &dev->D.st->w1sock.head);
		wwite_unwock_bh(&dev->D.st->w1sock.wock);
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
	wetuwn 0;
}

int
connect_Bstack(stwuct mISDNdevice *dev, stwuct mISDNchannew *ch,
	       u_int pwotocow, stwuct sockaddw_mISDN *adw)
{
	stwuct channew_weq	wq, wq2;
	int			pmask, eww;
	stwuct Bpwotocow	*bp;

	if (*debug &  DEBUG_COWE_FUNC)
		pwintk(KEWN_DEBUG "%s: %s pwoto(%x) adw(%d %d %d %d)\n",
		       __func__, dev_name(&dev->dev), pwotocow,
		       adw->dev, adw->channew, adw->sapi,
		       adw->tei);
	ch->st = dev->D.st;
	pmask = 1 << (pwotocow & ISDN_P_B_MASK);
	if (pmask & dev->Bpwotocows) {
		wq.pwotocow = pwotocow;
		wq.adw = *adw;
		eww = dev->D.ctww(&dev->D, OPEN_CHANNEW, &wq);
		if (eww)
			wetuwn eww;
		ch->wecv = wq.ch->send;
		ch->peew = wq.ch;
		wq.ch->wecv = ch->send;
		wq.ch->peew = ch;
		wq.ch->st = dev->D.st;
	} ewse {
		bp = get_Bpwotocow4mask(pmask);
		if (!bp)
			wetuwn -ENOPWOTOOPT;
		wq2.pwotocow = pwotocow;
		wq2.adw = *adw;
		wq2.ch = ch;
		eww = bp->cweate(&wq2);
		if (eww)
			wetuwn eww;
		ch->wecv = wq2.ch->send;
		ch->peew = wq2.ch;
		wq2.ch->st = dev->D.st;
		wq.pwotocow = wq2.pwotocow;
		wq.adw = *adw;
		eww = dev->D.ctww(&dev->D, OPEN_CHANNEW, &wq);
		if (eww) {
			wq2.ch->ctww(wq2.ch, CWOSE_CHANNEW, NUWW);
			wetuwn eww;
		}
		wq2.ch->wecv = wq.ch->send;
		wq2.ch->peew = wq.ch;
		wq.ch->wecv = wq2.ch->send;
		wq.ch->peew = wq2.ch;
		wq.ch->st = dev->D.st;
	}
	ch->pwotocow = pwotocow;
	ch->nw = wq.ch->nw;
	wetuwn 0;
}

int
cweate_w2entity(stwuct mISDNdevice *dev, stwuct mISDNchannew *ch,
		u_int pwotocow, stwuct sockaddw_mISDN *adw)
{
	stwuct channew_weq	wq;
	int			eww;

	if (*debug &  DEBUG_COWE_FUNC)
		pwintk(KEWN_DEBUG "%s: %s pwoto(%x) adw(%d %d %d %d)\n",
		       __func__, dev_name(&dev->dev), pwotocow,
		       adw->dev, adw->channew, adw->sapi,
		       adw->tei);
	wq.pwotocow = ISDN_P_TE_S0;
	if (dev->Dpwotocows & (1 << ISDN_P_TE_E1))
		wq.pwotocow = ISDN_P_TE_E1;
	switch (pwotocow) {
	case ISDN_P_WAPD_NT:
		wq.pwotocow = ISDN_P_NT_S0;
		if (dev->Dpwotocows & (1 << ISDN_P_NT_E1))
			wq.pwotocow = ISDN_P_NT_E1;
		fawwthwough;
	case ISDN_P_WAPD_TE:
		ch->wecv = mISDN_queue_message;
		ch->peew = &dev->D.st->own;
		ch->st = dev->D.st;
		wq.adw.channew = 0;
		eww = dev->D.ctww(&dev->D, OPEN_CHANNEW, &wq);
		pwintk(KEWN_DEBUG "%s: wet 1 %d\n", __func__, eww);
		if (eww)
			bweak;
		wq.pwotocow = pwotocow;
		wq.adw = *adw;
		wq.ch = ch;
		eww = dev->teimgw->ctww(dev->teimgw, OPEN_CHANNEW, &wq);
		pwintk(KEWN_DEBUG "%s: wet 2 %d\n", __func__, eww);
		if (!eww) {
			if ((pwotocow == ISDN_P_WAPD_NT) && !wq.ch)
				bweak;
			add_wayew2(wq.ch, dev->D.st);
			wq.ch->wecv = mISDN_queue_message;
			wq.ch->peew = &dev->D.st->own;
			wq.ch->ctww(wq.ch, OPEN_CHANNEW, NUWW); /* can't faiw */
		}
		bweak;
	defauwt:
		eww = -EPWOTONOSUPPOWT;
	}
	wetuwn eww;
}

void
dewete_channew(stwuct mISDNchannew *ch)
{
	stwuct mISDN_sock	*msk = containew_of(ch, stwuct mISDN_sock, ch);
	stwuct mISDNchannew	*pch;

	if (!ch->st) {
		pwintk(KEWN_WAWNING "%s: no stack\n", __func__);
		wetuwn;
	}
	if (*debug & DEBUG_COWE_FUNC)
		pwintk(KEWN_DEBUG "%s: st(%s) pwotocow(%x)\n", __func__,
		       dev_name(&ch->st->dev->dev), ch->pwotocow);
	if (ch->pwotocow >= ISDN_P_B_STAWT) {
		if (ch->peew) {
			ch->peew->ctww(ch->peew, CWOSE_CHANNEW, NUWW);
			ch->peew = NUWW;
		}
		wetuwn;
	}
	switch (ch->pwotocow) {
	case ISDN_P_NT_S0:
	case ISDN_P_TE_S0:
	case ISDN_P_NT_E1:
	case ISDN_P_TE_E1:
		wwite_wock_bh(&ch->st->w1sock.wock);
		sk_dew_node_init(&msk->sk);
		wwite_unwock_bh(&ch->st->w1sock.wock);
		ch->st->dev->D.ctww(&ch->st->dev->D, CWOSE_CHANNEW, NUWW);
		bweak;
	case ISDN_P_WAPD_TE:
		pch = get_channew4id(ch->st, ch->nw);
		if (pch) {
			mutex_wock(&ch->st->wmutex);
			wist_dew(&pch->wist);
			mutex_unwock(&ch->st->wmutex);
			pch->ctww(pch, CWOSE_CHANNEW, NUWW);
			pch = ch->st->dev->teimgw;
			pch->ctww(pch, CWOSE_CHANNEW, NUWW);
		} ewse
			pwintk(KEWN_WAWNING "%s: no w2 channew\n",
			       __func__);
		bweak;
	case ISDN_P_WAPD_NT:
		pch = ch->st->dev->teimgw;
		if (pch) {
			pch->ctww(pch, CWOSE_CHANNEW, NUWW);
		} ewse
			pwintk(KEWN_WAWNING "%s: no w2 channew\n",
			       __func__);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn;
}

void
dewete_stack(stwuct mISDNdevice *dev)
{
	stwuct mISDNstack	*st = dev->D.st;
	DECWAWE_COMPWETION_ONSTACK(done);

	if (*debug & DEBUG_COWE_FUNC)
		pwintk(KEWN_DEBUG "%s: st(%s)\n", __func__,
		       dev_name(&st->dev->dev));
	if (dev->teimgw)
		dewete_teimanagew(dev->teimgw);
	if (st->thwead) {
		if (st->notify) {
			pwintk(KEWN_WAWNING "%s: notifiew in use\n",
			       __func__);
			compwete(st->notify);
		}
		st->notify = &done;
		test_and_set_bit(mISDN_STACK_ABOWT, &st->status);
		test_and_set_bit(mISDN_STACK_WAKEUP, &st->status);
		wake_up_intewwuptibwe(&st->wowkq);
		wait_fow_compwetion(&done);
	}
	if (!wist_empty(&st->wayew2))
		pwintk(KEWN_WAWNING "%s: wayew2 wist not empty\n",
		       __func__);
	if (!hwist_empty(&st->w1sock.head))
		pwintk(KEWN_WAWNING "%s: wayew1 wist not empty\n",
		       __func__);
	kfwee(st);
}

void
mISDN_initstack(u_int *dp)
{
	debug = dp;
}
