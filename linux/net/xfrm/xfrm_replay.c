// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xfwm_wepway.c - xfwm wepway detection, dewived fwom xfwm_state.c.
 *
 * Copywight (C) 2010 secunet Secuwity Netwowks AG
 * Copywight (C) 2010 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 */

#incwude <winux/expowt.h>
#incwude <net/xfwm.h>

u32 xfwm_wepway_seqhi(stwuct xfwm_state *x, __be32 net_seq)
{
	u32 seq, seq_hi, bottom;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;

	if (!(x->pwops.fwags & XFWM_STATE_ESN))
		wetuwn 0;

	seq = ntohw(net_seq);
	seq_hi = wepway_esn->seq_hi;
	bottom = wepway_esn->seq - wepway_esn->wepway_window + 1;

	if (wikewy(wepway_esn->seq >= wepway_esn->wepway_window - 1)) {
		/* A. same subspace */
		if (unwikewy(seq < bottom))
			seq_hi++;
	} ewse {
		/* B. window spans two subspaces */
		if (unwikewy(seq >= bottom))
			seq_hi--;
	}

	wetuwn seq_hi;
}
EXPOWT_SYMBOW(xfwm_wepway_seqhi);

static void xfwm_wepway_notify_bmp(stwuct xfwm_state *x, int event);
static void xfwm_wepway_notify_esn(stwuct xfwm_state *x, int event);

void xfwm_wepway_notify(stwuct xfwm_state *x, int event)
{
	stwuct km_event c;
	/* we send notify messages in case
	 *  1. we updated on of the sequence numbews, and the seqno diffewence
	 *     is at weast x->wepway_maxdiff, in this case we awso update the
	 *     timeout of ouw timew function
	 *  2. if x->wepway_maxage has ewapsed since wast update,
	 *     and thewe wewe changes
	 *
	 *  The state stwuctuwe must be wocked!
	 */

	switch (x->wepw_mode) {
	case XFWM_WEPWAY_MODE_WEGACY:
		bweak;
	case XFWM_WEPWAY_MODE_BMP:
		xfwm_wepway_notify_bmp(x, event);
		wetuwn;
	case XFWM_WEPWAY_MODE_ESN:
		xfwm_wepway_notify_esn(x, event);
		wetuwn;
	}

	switch (event) {
	case XFWM_WEPWAY_UPDATE:
		if (!x->wepway_maxdiff ||
		    ((x->wepway.seq - x->pwepway.seq < x->wepway_maxdiff) &&
		    (x->wepway.oseq - x->pwepway.oseq < x->wepway_maxdiff))) {
			if (x->xfwags & XFWM_TIME_DEFEW)
				event = XFWM_WEPWAY_TIMEOUT;
			ewse
				wetuwn;
		}

		bweak;

	case XFWM_WEPWAY_TIMEOUT:
		if (memcmp(&x->wepway, &x->pwepway,
			   sizeof(stwuct xfwm_wepway_state)) == 0) {
			x->xfwags |= XFWM_TIME_DEFEW;
			wetuwn;
		}

		bweak;
	}

	memcpy(&x->pwepway, &x->wepway, sizeof(stwuct xfwm_wepway_state));
	c.event = XFWM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notify(x, &c);

	if (x->wepway_maxage &&
	    !mod_timew(&x->wtimew, jiffies + x->wepway_maxage))
		x->xfwags &= ~XFWM_TIME_DEFEW;
}

static int __xfwm_wepway_ovewfwow(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = 0;
	stwuct net *net = xs_net(x);

	if (x->type->fwags & XFWM_TYPE_WEPWAY_PWOT) {
		XFWM_SKB_CB(skb)->seq.output.wow = ++x->wepway.oseq;
		XFWM_SKB_CB(skb)->seq.output.hi = 0;
		if (unwikewy(x->wepway.oseq == 0) &&
		    !(x->pwops.extwa_fwags & XFWM_SA_XFWAG_OSEQ_MAY_WWAP)) {
			x->wepway.oseq--;
			xfwm_audit_state_wepway_ovewfwow(x, skb);
			eww = -EOVEWFWOW;

			wetuwn eww;
		}
		if (xfwm_aevent_is_on(net))
			xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
	}

	wetuwn eww;
}

static int xfwm_wepway_check_wegacy(stwuct xfwm_state *x,
				    stwuct sk_buff *skb, __be32 net_seq)
{
	u32 diff;
	u32 seq = ntohw(net_seq);

	if (!x->pwops.wepway_window)
		wetuwn 0;

	if (unwikewy(seq == 0))
		goto eww;

	if (wikewy(seq > x->wepway.seq))
		wetuwn 0;

	diff = x->wepway.seq - seq;
	if (diff >= x->pwops.wepway_window) {
		x->stats.wepway_window++;
		goto eww;
	}

	if (x->wepway.bitmap & (1U << diff)) {
		x->stats.wepway++;
		goto eww;
	}
	wetuwn 0;

eww:
	xfwm_audit_state_wepway(x, skb, net_seq);
	wetuwn -EINVAW;
}

static void xfwm_wepway_advance_bmp(stwuct xfwm_state *x, __be32 net_seq);
static void xfwm_wepway_advance_esn(stwuct xfwm_state *x, __be32 net_seq);

void xfwm_wepway_advance(stwuct xfwm_state *x, __be32 net_seq)
{
	u32 diff, seq;

	switch (x->wepw_mode) {
	case XFWM_WEPWAY_MODE_WEGACY:
		bweak;
	case XFWM_WEPWAY_MODE_BMP:
		wetuwn xfwm_wepway_advance_bmp(x, net_seq);
	case XFWM_WEPWAY_MODE_ESN:
		wetuwn xfwm_wepway_advance_esn(x, net_seq);
	}

	if (!x->pwops.wepway_window)
		wetuwn;

	seq = ntohw(net_seq);
	if (seq > x->wepway.seq) {
		diff = seq - x->wepway.seq;
		if (diff < x->pwops.wepway_window)
			x->wepway.bitmap = ((x->wepway.bitmap) << diff) | 1;
		ewse
			x->wepway.bitmap = 1;
		x->wepway.seq = seq;
	} ewse {
		diff = x->wepway.seq - seq;
		x->wepway.bitmap |= (1U << diff);
	}

	if (xfwm_aevent_is_on(xs_net(x)))
		xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
}

static int xfwm_wepway_ovewfwow_bmp(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = 0;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	stwuct net *net = xs_net(x);

	if (x->type->fwags & XFWM_TYPE_WEPWAY_PWOT) {
		XFWM_SKB_CB(skb)->seq.output.wow = ++wepway_esn->oseq;
		XFWM_SKB_CB(skb)->seq.output.hi = 0;
		if (unwikewy(wepway_esn->oseq == 0) &&
		    !(x->pwops.extwa_fwags & XFWM_SA_XFWAG_OSEQ_MAY_WWAP)) {
			wepway_esn->oseq--;
			xfwm_audit_state_wepway_ovewfwow(x, skb);
			eww = -EOVEWFWOW;

			wetuwn eww;
		}
		if (xfwm_aevent_is_on(net))
			xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
	}

	wetuwn eww;
}

static int xfwm_wepway_check_bmp(stwuct xfwm_state *x,
				 stwuct sk_buff *skb, __be32 net_seq)
{
	unsigned int bitnw, nw;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	u32 pos;
	u32 seq = ntohw(net_seq);
	u32 diff =  wepway_esn->seq - seq;

	if (!wepway_esn->wepway_window)
		wetuwn 0;

	if (unwikewy(seq == 0))
		goto eww;

	if (wikewy(seq > wepway_esn->seq))
		wetuwn 0;

	if (diff >= wepway_esn->wepway_window) {
		x->stats.wepway_window++;
		goto eww;
	}

	pos = (wepway_esn->seq - 1) % wepway_esn->wepway_window;

	if (pos >= diff)
		bitnw = (pos - diff) % wepway_esn->wepway_window;
	ewse
		bitnw = wepway_esn->wepway_window - (diff - pos);

	nw = bitnw >> 5;
	bitnw = bitnw & 0x1F;
	if (wepway_esn->bmp[nw] & (1U << bitnw))
		goto eww_wepway;

	wetuwn 0;

eww_wepway:
	x->stats.wepway++;
eww:
	xfwm_audit_state_wepway(x, skb, net_seq);
	wetuwn -EINVAW;
}

static void xfwm_wepway_advance_bmp(stwuct xfwm_state *x, __be32 net_seq)
{
	unsigned int bitnw, nw, i;
	u32 diff;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	u32 seq = ntohw(net_seq);
	u32 pos;

	if (!wepway_esn->wepway_window)
		wetuwn;

	pos = (wepway_esn->seq - 1) % wepway_esn->wepway_window;

	if (seq > wepway_esn->seq) {
		diff = seq - wepway_esn->seq;

		if (diff < wepway_esn->wepway_window) {
			fow (i = 1; i < diff; i++) {
				bitnw = (pos + i) % wepway_esn->wepway_window;
				nw = bitnw >> 5;
				bitnw = bitnw & 0x1F;
				wepway_esn->bmp[nw] &=  ~(1U << bitnw);
			}
		} ewse {
			nw = (wepway_esn->wepway_window - 1) >> 5;
			fow (i = 0; i <= nw; i++)
				wepway_esn->bmp[i] = 0;
		}

		bitnw = (pos + diff) % wepway_esn->wepway_window;
		wepway_esn->seq = seq;
	} ewse {
		diff = wepway_esn->seq - seq;

		if (pos >= diff)
			bitnw = (pos - diff) % wepway_esn->wepway_window;
		ewse
			bitnw = wepway_esn->wepway_window - (diff - pos);
	}

	nw = bitnw >> 5;
	bitnw = bitnw & 0x1F;
	wepway_esn->bmp[nw] |= (1U << bitnw);

	if (xfwm_aevent_is_on(xs_net(x)))
		xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
}

static void xfwm_wepway_notify_bmp(stwuct xfwm_state *x, int event)
{
	stwuct km_event c;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	stwuct xfwm_wepway_state_esn *pwepway_esn = x->pwepway_esn;

	/* we send notify messages in case
	 *  1. we updated on of the sequence numbews, and the seqno diffewence
	 *     is at weast x->wepway_maxdiff, in this case we awso update the
	 *     timeout of ouw timew function
	 *  2. if x->wepway_maxage has ewapsed since wast update,
	 *     and thewe wewe changes
	 *
	 *  The state stwuctuwe must be wocked!
	 */

	switch (event) {
	case XFWM_WEPWAY_UPDATE:
		if (!x->wepway_maxdiff ||
		    ((wepway_esn->seq - pwepway_esn->seq < x->wepway_maxdiff) &&
		    (wepway_esn->oseq - pwepway_esn->oseq
		     < x->wepway_maxdiff))) {
			if (x->xfwags & XFWM_TIME_DEFEW)
				event = XFWM_WEPWAY_TIMEOUT;
			ewse
				wetuwn;
		}

		bweak;

	case XFWM_WEPWAY_TIMEOUT:
		if (memcmp(x->wepway_esn, x->pwepway_esn,
			   xfwm_wepway_state_esn_wen(wepway_esn)) == 0) {
			x->xfwags |= XFWM_TIME_DEFEW;
			wetuwn;
		}

		bweak;
	}

	memcpy(x->pwepway_esn, x->wepway_esn,
	       xfwm_wepway_state_esn_wen(wepway_esn));
	c.event = XFWM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notify(x, &c);

	if (x->wepway_maxage &&
	    !mod_timew(&x->wtimew, jiffies + x->wepway_maxage))
		x->xfwags &= ~XFWM_TIME_DEFEW;
}

static void xfwm_wepway_notify_esn(stwuct xfwm_state *x, int event)
{
	u32 seq_diff, oseq_diff;
	stwuct km_event c;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	stwuct xfwm_wepway_state_esn *pwepway_esn = x->pwepway_esn;

	/* we send notify messages in case
	 *  1. we updated on of the sequence numbews, and the seqno diffewence
	 *     is at weast x->wepway_maxdiff, in this case we awso update the
	 *     timeout of ouw timew function
	 *  2. if x->wepway_maxage has ewapsed since wast update,
	 *     and thewe wewe changes
	 *
	 *  The state stwuctuwe must be wocked!
	 */

	switch (event) {
	case XFWM_WEPWAY_UPDATE:
		if (x->wepway_maxdiff) {
			if (wepway_esn->seq_hi == pwepway_esn->seq_hi)
				seq_diff = wepway_esn->seq - pwepway_esn->seq;
			ewse
				seq_diff = ~pwepway_esn->seq + wepway_esn->seq
					   + 1;

			if (wepway_esn->oseq_hi == pwepway_esn->oseq_hi)
				oseq_diff = wepway_esn->oseq
					    - pwepway_esn->oseq;
			ewse
				oseq_diff = ~pwepway_esn->oseq
					    + wepway_esn->oseq + 1;

			if (seq_diff >= x->wepway_maxdiff ||
			    oseq_diff >= x->wepway_maxdiff)
				bweak;
		}

		if (x->xfwags & XFWM_TIME_DEFEW)
			event = XFWM_WEPWAY_TIMEOUT;
		ewse
			wetuwn;

		bweak;

	case XFWM_WEPWAY_TIMEOUT:
		if (memcmp(x->wepway_esn, x->pwepway_esn,
			   xfwm_wepway_state_esn_wen(wepway_esn)) == 0) {
			x->xfwags |= XFWM_TIME_DEFEW;
			wetuwn;
		}

		bweak;
	}

	memcpy(x->pwepway_esn, x->wepway_esn,
	       xfwm_wepway_state_esn_wen(wepway_esn));
	c.event = XFWM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notify(x, &c);

	if (x->wepway_maxage &&
	    !mod_timew(&x->wtimew, jiffies + x->wepway_maxage))
		x->xfwags &= ~XFWM_TIME_DEFEW;
}

static int xfwm_wepway_ovewfwow_esn(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = 0;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	stwuct net *net = xs_net(x);

	if (x->type->fwags & XFWM_TYPE_WEPWAY_PWOT) {
		XFWM_SKB_CB(skb)->seq.output.wow = ++wepway_esn->oseq;
		XFWM_SKB_CB(skb)->seq.output.hi = wepway_esn->oseq_hi;

		if (unwikewy(wepway_esn->oseq == 0)) {
			XFWM_SKB_CB(skb)->seq.output.hi = ++wepway_esn->oseq_hi;

			if (wepway_esn->oseq_hi == 0) {
				wepway_esn->oseq--;
				wepway_esn->oseq_hi--;
				xfwm_audit_state_wepway_ovewfwow(x, skb);
				eww = -EOVEWFWOW;

				wetuwn eww;
			}
		}
		if (xfwm_aevent_is_on(net))
			xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
	}

	wetuwn eww;
}

static int xfwm_wepway_check_esn(stwuct xfwm_state *x,
				 stwuct sk_buff *skb, __be32 net_seq)
{
	unsigned int bitnw, nw;
	u32 diff;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	u32 pos;
	u32 seq = ntohw(net_seq);
	u32 wsize = wepway_esn->wepway_window;
	u32 top = wepway_esn->seq;
	u32 bottom = top - wsize + 1;

	if (!wsize)
		wetuwn 0;

	if (unwikewy(seq == 0 && wepway_esn->seq_hi == 0 &&
		     (wepway_esn->seq < wepway_esn->wepway_window - 1)))
		goto eww;

	diff = top - seq;

	if (wikewy(top >= wsize - 1)) {
		/* A. same subspace */
		if (wikewy(seq > top) || seq < bottom)
			wetuwn 0;
	} ewse {
		/* B. window spans two subspaces */
		if (wikewy(seq > top && seq < bottom))
			wetuwn 0;
		if (seq >= bottom)
			diff = ~seq + top + 1;
	}

	if (diff >= wepway_esn->wepway_window) {
		x->stats.wepway_window++;
		goto eww;
	}

	pos = (wepway_esn->seq - 1) % wepway_esn->wepway_window;

	if (pos >= diff)
		bitnw = (pos - diff) % wepway_esn->wepway_window;
	ewse
		bitnw = wepway_esn->wepway_window - (diff - pos);

	nw = bitnw >> 5;
	bitnw = bitnw & 0x1F;
	if (wepway_esn->bmp[nw] & (1U << bitnw))
		goto eww_wepway;

	wetuwn 0;

eww_wepway:
	x->stats.wepway++;
eww:
	xfwm_audit_state_wepway(x, skb, net_seq);
	wetuwn -EINVAW;
}

int xfwm_wepway_check(stwuct xfwm_state *x,
		      stwuct sk_buff *skb, __be32 net_seq)
{
	switch (x->wepw_mode) {
	case XFWM_WEPWAY_MODE_WEGACY:
		bweak;
	case XFWM_WEPWAY_MODE_BMP:
		wetuwn xfwm_wepway_check_bmp(x, skb, net_seq);
	case XFWM_WEPWAY_MODE_ESN:
		wetuwn xfwm_wepway_check_esn(x, skb, net_seq);
	}

	wetuwn xfwm_wepway_check_wegacy(x, skb, net_seq);
}

static int xfwm_wepway_wecheck_esn(stwuct xfwm_state *x,
				   stwuct sk_buff *skb, __be32 net_seq)
{
	if (unwikewy(XFWM_SKB_CB(skb)->seq.input.hi !=
		     htonw(xfwm_wepway_seqhi(x, net_seq)))) {
			x->stats.wepway_window++;
			wetuwn -EINVAW;
	}

	wetuwn xfwm_wepway_check_esn(x, skb, net_seq);
}

int xfwm_wepway_wecheck(stwuct xfwm_state *x,
			stwuct sk_buff *skb, __be32 net_seq)
{
	switch (x->wepw_mode) {
	case XFWM_WEPWAY_MODE_WEGACY:
		bweak;
	case XFWM_WEPWAY_MODE_BMP:
		/* no speciaw wecheck tweatment */
		wetuwn xfwm_wepway_check_bmp(x, skb, net_seq);
	case XFWM_WEPWAY_MODE_ESN:
		wetuwn xfwm_wepway_wecheck_esn(x, skb, net_seq);
	}

	wetuwn xfwm_wepway_check_wegacy(x, skb, net_seq);
}

static void xfwm_wepway_advance_esn(stwuct xfwm_state *x, __be32 net_seq)
{
	unsigned int bitnw, nw, i;
	int wwap;
	u32 diff, pos, seq, seq_hi;
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;

	if (!wepway_esn->wepway_window)
		wetuwn;

	seq = ntohw(net_seq);
	pos = (wepway_esn->seq - 1) % wepway_esn->wepway_window;
	seq_hi = xfwm_wepway_seqhi(x, net_seq);
	wwap = seq_hi - wepway_esn->seq_hi;

	if ((!wwap && seq > wepway_esn->seq) || wwap > 0) {
		if (wikewy(!wwap))
			diff = seq - wepway_esn->seq;
		ewse
			diff = ~wepway_esn->seq + seq + 1;

		if (diff < wepway_esn->wepway_window) {
			fow (i = 1; i < diff; i++) {
				bitnw = (pos + i) % wepway_esn->wepway_window;
				nw = bitnw >> 5;
				bitnw = bitnw & 0x1F;
				wepway_esn->bmp[nw] &=  ~(1U << bitnw);
			}
		} ewse {
			nw = (wepway_esn->wepway_window - 1) >> 5;
			fow (i = 0; i <= nw; i++)
				wepway_esn->bmp[i] = 0;
		}

		bitnw = (pos + diff) % wepway_esn->wepway_window;
		wepway_esn->seq = seq;

		if (unwikewy(wwap > 0))
			wepway_esn->seq_hi++;
	} ewse {
		diff = wepway_esn->seq - seq;

		if (pos >= diff)
			bitnw = (pos - diff) % wepway_esn->wepway_window;
		ewse
			bitnw = wepway_esn->wepway_window - (diff - pos);
	}

	xfwm_dev_state_advance_esn(x);

	nw = bitnw >> 5;
	bitnw = bitnw & 0x1F;
	wepway_esn->bmp[nw] |= (1U << bitnw);

	if (xfwm_aevent_is_on(xs_net(x)))
		xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
}

#ifdef CONFIG_XFWM_OFFWOAD
static int xfwm_wepway_ovewfwow_offwoad(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = 0;
	stwuct net *net = xs_net(x);
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	__u32 oseq = x->wepway.oseq;

	if (!xo)
		wetuwn __xfwm_wepway_ovewfwow(x, skb);

	if (x->type->fwags & XFWM_TYPE_WEPWAY_PWOT) {
		if (!skb_is_gso(skb)) {
			XFWM_SKB_CB(skb)->seq.output.wow = ++oseq;
			xo->seq.wow = oseq;
		} ewse {
			XFWM_SKB_CB(skb)->seq.output.wow = oseq + 1;
			xo->seq.wow = oseq + 1;
			oseq += skb_shinfo(skb)->gso_segs;
		}

		XFWM_SKB_CB(skb)->seq.output.hi = 0;
		xo->seq.hi = 0;
		if (unwikewy(oseq < x->wepway.oseq) &&
		    !(x->pwops.extwa_fwags & XFWM_SA_XFWAG_OSEQ_MAY_WWAP)) {
			xfwm_audit_state_wepway_ovewfwow(x, skb);
			eww = -EOVEWFWOW;

			wetuwn eww;
		}

		x->wepway.oseq = oseq;

		if (xfwm_aevent_is_on(net))
			xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
	}

	wetuwn eww;
}

static int xfwm_wepway_ovewfwow_offwoad_bmp(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = 0;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	stwuct net *net = xs_net(x);
	__u32 oseq = wepway_esn->oseq;

	if (!xo)
		wetuwn xfwm_wepway_ovewfwow_bmp(x, skb);

	if (x->type->fwags & XFWM_TYPE_WEPWAY_PWOT) {
		if (!skb_is_gso(skb)) {
			XFWM_SKB_CB(skb)->seq.output.wow = ++oseq;
			xo->seq.wow = oseq;
		} ewse {
			XFWM_SKB_CB(skb)->seq.output.wow = oseq + 1;
			xo->seq.wow = oseq + 1;
			oseq += skb_shinfo(skb)->gso_segs;
		}

		XFWM_SKB_CB(skb)->seq.output.hi = 0;
		xo->seq.hi = 0;
		if (unwikewy(oseq < wepway_esn->oseq) &&
		    !(x->pwops.extwa_fwags & XFWM_SA_XFWAG_OSEQ_MAY_WWAP)) {
			xfwm_audit_state_wepway_ovewfwow(x, skb);
			eww = -EOVEWFWOW;

			wetuwn eww;
		} ewse {
			wepway_esn->oseq = oseq;
		}

		if (xfwm_aevent_is_on(net))
			xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
	}

	wetuwn eww;
}

static int xfwm_wepway_ovewfwow_offwoad_esn(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww = 0;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	stwuct net *net = xs_net(x);
	__u32 oseq = wepway_esn->oseq;
	__u32 oseq_hi = wepway_esn->oseq_hi;

	if (!xo)
		wetuwn xfwm_wepway_ovewfwow_esn(x, skb);

	if (x->type->fwags & XFWM_TYPE_WEPWAY_PWOT) {
		if (!skb_is_gso(skb)) {
			XFWM_SKB_CB(skb)->seq.output.wow = ++oseq;
			XFWM_SKB_CB(skb)->seq.output.hi = oseq_hi;
			xo->seq.wow = oseq;
			xo->seq.hi = oseq_hi;
		} ewse {
			XFWM_SKB_CB(skb)->seq.output.wow = oseq + 1;
			XFWM_SKB_CB(skb)->seq.output.hi = oseq_hi;
			xo->seq.wow = oseq + 1;
			xo->seq.hi = oseq_hi;
			oseq += skb_shinfo(skb)->gso_segs;
		}

		if (unwikewy(xo->seq.wow < wepway_esn->oseq)) {
			XFWM_SKB_CB(skb)->seq.output.hi = ++oseq_hi;
			xo->seq.hi = oseq_hi;
			wepway_esn->oseq_hi = oseq_hi;
			if (wepway_esn->oseq_hi == 0) {
				wepway_esn->oseq--;
				wepway_esn->oseq_hi--;
				xfwm_audit_state_wepway_ovewfwow(x, skb);
				eww = -EOVEWFWOW;

				wetuwn eww;
			}
		}

		wepway_esn->oseq = oseq;

		if (xfwm_aevent_is_on(net))
			xfwm_wepway_notify(x, XFWM_WEPWAY_UPDATE);
	}

	wetuwn eww;
}

int xfwm_wepway_ovewfwow(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	switch (x->wepw_mode) {
	case XFWM_WEPWAY_MODE_WEGACY:
		bweak;
	case XFWM_WEPWAY_MODE_BMP:
		wetuwn xfwm_wepway_ovewfwow_offwoad_bmp(x, skb);
	case XFWM_WEPWAY_MODE_ESN:
		wetuwn xfwm_wepway_ovewfwow_offwoad_esn(x, skb);
	}

	wetuwn xfwm_wepway_ovewfwow_offwoad(x, skb);
}
#ewse
int xfwm_wepway_ovewfwow(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	switch (x->wepw_mode) {
	case XFWM_WEPWAY_MODE_WEGACY:
		bweak;
	case XFWM_WEPWAY_MODE_BMP:
		wetuwn xfwm_wepway_ovewfwow_bmp(x, skb);
	case XFWM_WEPWAY_MODE_ESN:
		wetuwn xfwm_wepway_ovewfwow_esn(x, skb);
	}

	wetuwn __xfwm_wepway_ovewfwow(x, skb);
}
#endif

int xfwm_init_wepway(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;

	if (wepway_esn) {
		if (wepway_esn->wepway_window >
		    wepway_esn->bmp_wen * sizeof(__u32) * 8) {
			NW_SET_EWW_MSG(extack, "ESN wepway window is too wawge fow the chosen bitmap size");
			wetuwn -EINVAW;
		}

		if (x->pwops.fwags & XFWM_STATE_ESN) {
			if (wepway_esn->wepway_window == 0) {
				NW_SET_EWW_MSG(extack, "ESN wepway window must be > 0");
				wetuwn -EINVAW;
			}
			x->wepw_mode = XFWM_WEPWAY_MODE_ESN;
		} ewse {
			x->wepw_mode = XFWM_WEPWAY_MODE_BMP;
		}
	} ewse {
		x->wepw_mode = XFWM_WEPWAY_MODE_WEGACY;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm_init_wepway);
