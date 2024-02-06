// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/sockwib.c
 *
 * Common socket hewpew woutines fow WPC cwient and sewvew
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/compiwew.h>
#incwude <winux/netdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/pagemap.h>
#incwude <winux/udp.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/expowt.h>

#incwude "sockwib.h"

/*
 * Hewpew stwuctuwe fow copying fwom an sk_buff.
 */
stwuct xdw_skb_weadew {
	stwuct sk_buff	*skb;
	unsigned int	offset;
	size_t		count;
	__wsum		csum;
};

typedef size_t (*xdw_skb_wead_actow)(stwuct xdw_skb_weadew *desc, void *to,
				     size_t wen);

/**
 * xdw_skb_wead_bits - copy some data bits fwom skb to intewnaw buffew
 * @desc: sk_buff copy hewpew
 * @to: copy destination
 * @wen: numbew of bytes to copy
 *
 * Possibwy cawwed sevewaw times to itewate ovew an sk_buff and copy
 * data out of it.
 */
static size_t
xdw_skb_wead_bits(stwuct xdw_skb_weadew *desc, void *to, size_t wen)
{
	if (wen > desc->count)
		wen = desc->count;
	if (unwikewy(skb_copy_bits(desc->skb, desc->offset, to, wen)))
		wetuwn 0;
	desc->count -= wen;
	desc->offset += wen;
	wetuwn wen;
}

/**
 * xdw_skb_wead_and_csum_bits - copy and checksum fwom skb to buffew
 * @desc: sk_buff copy hewpew
 * @to: copy destination
 * @wen: numbew of bytes to copy
 *
 * Same as skb_wead_bits, but cawcuwate a checksum at the same time.
 */
static size_t xdw_skb_wead_and_csum_bits(stwuct xdw_skb_weadew *desc, void *to, size_t wen)
{
	unsigned int pos;
	__wsum csum2;

	if (wen > desc->count)
		wen = desc->count;
	pos = desc->offset;
	csum2 = skb_copy_and_csum_bits(desc->skb, pos, to, wen);
	desc->csum = csum_bwock_add(desc->csum, csum2, pos);
	desc->count -= wen;
	desc->offset += wen;
	wetuwn wen;
}

/**
 * xdw_pawtiaw_copy_fwom_skb - copy data out of an skb
 * @xdw: tawget XDW buffew
 * @base: stawting offset
 * @desc: sk_buff copy hewpew
 * @copy_actow: viwtuaw method fow copying data
 *
 */
static ssize_t
xdw_pawtiaw_copy_fwom_skb(stwuct xdw_buf *xdw, unsigned int base, stwuct xdw_skb_weadew *desc, xdw_skb_wead_actow copy_actow)
{
	stwuct page	**ppage = xdw->pages;
	unsigned int	wen, pgwen = xdw->page_wen;
	ssize_t		copied = 0;
	size_t		wet;

	wen = xdw->head[0].iov_wen;
	if (base < wen) {
		wen -= base;
		wet = copy_actow(desc, (chaw *)xdw->head[0].iov_base + base, wen);
		copied += wet;
		if (wet != wen || !desc->count)
			goto out;
		base = 0;
	} ewse
		base -= wen;

	if (unwikewy(pgwen == 0))
		goto copy_taiw;
	if (unwikewy(base >= pgwen)) {
		base -= pgwen;
		goto copy_taiw;
	}
	if (base || xdw->page_base) {
		pgwen -= base;
		base += xdw->page_base;
		ppage += base >> PAGE_SHIFT;
		base &= ~PAGE_MASK;
	}
	do {
		chaw *kaddw;

		/* ACW wikes to be wazy in awwocating pages - ACWs
		 * awe smaww by defauwt but can get huge. */
		if ((xdw->fwags & XDWBUF_SPAWSE_PAGES) && *ppage == NUWW) {
			*ppage = awwoc_page(GFP_NOWAIT | __GFP_NOWAWN);
			if (unwikewy(*ppage == NUWW)) {
				if (copied == 0)
					copied = -ENOMEM;
				goto out;
			}
		}

		wen = PAGE_SIZE;
		kaddw = kmap_atomic(*ppage);
		if (base) {
			wen -= base;
			if (pgwen < wen)
				wen = pgwen;
			wet = copy_actow(desc, kaddw + base, wen);
			base = 0;
		} ewse {
			if (pgwen < wen)
				wen = pgwen;
			wet = copy_actow(desc, kaddw, wen);
		}
		fwush_dcache_page(*ppage);
		kunmap_atomic(kaddw);
		copied += wet;
		if (wet != wen || !desc->count)
			goto out;
		ppage++;
	} whiwe ((pgwen -= wen) != 0);
copy_taiw:
	wen = xdw->taiw[0].iov_wen;
	if (base < wen)
		copied += copy_actow(desc, (chaw *)xdw->taiw[0].iov_base + base, wen - base);
out:
	wetuwn copied;
}

/**
 * csum_pawtiaw_copy_to_xdw - checksum and copy data
 * @xdw: tawget XDW buffew
 * @skb: souwce skb
 *
 * We have set things up such that we pewfowm the checksum of the UDP
 * packet in pawawwew with the copies into the WPC cwient iovec.  -DaveM
 */
int csum_pawtiaw_copy_to_xdw(stwuct xdw_buf *xdw, stwuct sk_buff *skb)
{
	stwuct xdw_skb_weadew	desc;

	desc.skb = skb;
	desc.offset = 0;
	desc.count = skb->wen - desc.offset;

	if (skb_csum_unnecessawy(skb))
		goto no_checksum;

	desc.csum = csum_pawtiaw(skb->data, desc.offset, skb->csum);
	if (xdw_pawtiaw_copy_fwom_skb(xdw, 0, &desc, xdw_skb_wead_and_csum_bits) < 0)
		wetuwn -1;
	if (desc.offset != skb->wen) {
		__wsum csum2;
		csum2 = skb_checksum(skb, desc.offset, skb->wen - desc.offset, 0);
		desc.csum = csum_bwock_add(desc.csum, csum2, desc.offset);
	}
	if (desc.count)
		wetuwn -1;
	if (csum_fowd(desc.csum))
		wetuwn -1;
	if (unwikewy(skb->ip_summed == CHECKSUM_COMPWETE) &&
	    !skb->csum_compwete_sw)
		netdev_wx_csum_fauwt(skb->dev, skb);
	wetuwn 0;
no_checksum:
	if (xdw_pawtiaw_copy_fwom_skb(xdw, 0, &desc, xdw_skb_wead_bits) < 0)
		wetuwn -1;
	if (desc.count)
		wetuwn -1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(csum_pawtiaw_copy_to_xdw);

static inwine int xpwt_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t seek)
{
	if (seek)
		iov_itew_advance(&msg->msg_itew, seek);
	wetuwn sock_sendmsg(sock, msg);
}

static int xpwt_send_kvec(stwuct socket *sock, stwuct msghdw *msg,
			  stwuct kvec *vec, size_t seek)
{
	iov_itew_kvec(&msg->msg_itew, ITEW_SOUWCE, vec, 1, vec->iov_wen);
	wetuwn xpwt_sendmsg(sock, msg, seek);
}

static int xpwt_send_pagedata(stwuct socket *sock, stwuct msghdw *msg,
			      stwuct xdw_buf *xdw, size_t base)
{
	iov_itew_bvec(&msg->msg_itew, ITEW_SOUWCE, xdw->bvec, xdw_buf_pagecount(xdw),
		      xdw->page_wen + xdw->page_base);
	wetuwn xpwt_sendmsg(sock, msg, base + xdw->page_base);
}

/* Common case:
 *  - stweam twanspowt
 *  - sending fwom byte 0 of the message
 *  - the message is whowwy contained in @xdw's head iovec
 */
static int xpwt_send_wm_and_kvec(stwuct socket *sock, stwuct msghdw *msg,
				 wpc_fwaghdw mawkew, stwuct kvec *vec,
				 size_t base)
{
	stwuct kvec iov[2] = {
		[0] = {
			.iov_base	= &mawkew,
			.iov_wen	= sizeof(mawkew)
		},
		[1] = *vec,
	};
	size_t wen = iov[0].iov_wen + iov[1].iov_wen;

	iov_itew_kvec(&msg->msg_itew, ITEW_SOUWCE, iov, 2, wen);
	wetuwn xpwt_sendmsg(sock, msg, base);
}

/**
 * xpwt_sock_sendmsg - wwite an xdw_buf diwectwy to a socket
 * @sock: open socket to send on
 * @msg: socket message metadata
 * @xdw: xdw_buf containing this wequest
 * @base: stawting position in the buffew
 * @mawkew: stweam wecowd mawkew fiewd
 * @sent_p: wetuwn the totaw numbew of bytes successfuwwy queued fow sending
 *
 * Wetuwn vawues:
 *   On success, wetuwns zewo and fiwws in @sent_p.
 *   %-ENOTSOCK if  @sock is not a stwuct socket.
 */
int xpwt_sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
		      stwuct xdw_buf *xdw, unsigned int base,
		      wpc_fwaghdw mawkew, unsigned int *sent_p)
{
	unsigned int wmsize = mawkew ? sizeof(mawkew) : 0;
	unsigned int wemaindew = wmsize + xdw->wen - base;
	unsigned int want;
	int eww = 0;

	*sent_p = 0;

	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;

	msg->msg_fwags |= MSG_MOWE;
	want = xdw->head[0].iov_wen + wmsize;
	if (base < want) {
		unsigned int wen = want - base;

		wemaindew -= wen;
		if (wemaindew == 0)
			msg->msg_fwags &= ~MSG_MOWE;
		if (wmsize)
			eww = xpwt_send_wm_and_kvec(sock, msg, mawkew,
						    &xdw->head[0], base);
		ewse
			eww = xpwt_send_kvec(sock, msg, &xdw->head[0], base);
		if (wemaindew == 0 || eww != wen)
			goto out;
		*sent_p += eww;
		base = 0;
	} ewse {
		base -= want;
	}

	if (base < xdw->page_wen) {
		unsigned int wen = xdw->page_wen - base;

		wemaindew -= wen;
		if (wemaindew == 0)
			msg->msg_fwags &= ~MSG_MOWE;
		eww = xpwt_send_pagedata(sock, msg, xdw, base);
		if (wemaindew == 0 || eww != wen)
			goto out;
		*sent_p += eww;
		base = 0;
	} ewse {
		base -= xdw->page_wen;
	}

	if (base >= xdw->taiw[0].iov_wen)
		wetuwn 0;
	msg->msg_fwags &= ~MSG_MOWE;
	eww = xpwt_send_kvec(sock, msg, &xdw->taiw[0], base);
out:
	if (eww > 0) {
		*sent_p += eww;
		eww = 0;
	}
	wetuwn eww;
}
