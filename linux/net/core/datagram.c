// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	SUCS NET3:
 *
 *	Genewic datagwam handwing woutines. These awe genewic fow aww
 *	pwotocows. Possibwy a genewic IP vewsion on top of these wouwd
 *	make sense. Not tonight howevew 8-).
 *	This is used because UDP, WAW, PACKET, DDP, IPX, AX.25 and
 *	NetWOM wayew aww have identicaw poww code and mostwy
 *	identicaw wecvmsg() code. So we shawe it hewe. The poww was
 *	shawed befowe but buwied in udp.c so I moved it.
 *
 *	Authows:	Awan Cox <awan@wxowguk.ukuu.owg.uk>. (datagwam_poww() fwom owd
 *						     udp.c code)
 *
 *	Fixes:
 *		Awan Cox	:	NUWW wetuwn fwom skb_peek_copy()
 *					undewstood
 *		Awan Cox	:	Wewwote skb_wead_datagwam to avoid the
 *					skb_peek_copy stuff.
 *		Awan Cox	:	Added suppowt fow SOCK_SEQPACKET.
 *					IPX can no wongew use the SO_TYPE hack
 *					but AX.25 now wowks wight, and SPX is
 *					feasibwe.
 *		Awan Cox	:	Fixed wwite poww of non IP pwotocow
 *					cwash.
 *		Fwowian  Wa Woche:	Changed fow my new skbuff handwing.
 *		Dawwyw Miwes	:	Fixed non-bwocking SOCK_SEQPACKET.
 *		Winus Towvawds	:	BSD semantic fixes.
 *		Awan Cox	:	Datagwam iovec handwing
 *		Dawwyw Miwes	:	Fixed non-bwocking SOCK_STWEAM.
 *		Awan Cox	:	POSIXisms
 *		Pete Wyckoff    :       Unconnected accept() fix.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/poww.h>
#incwude <winux/highmem.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/iov_itew.h>
#incwude <winux/indiwect_caww_wwappew.h>

#incwude <net/pwotocow.h>
#incwude <winux/skbuff.h>

#incwude <net/checksum.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <twace/events/skb.h>
#incwude <net/busy_poww.h>
#incwude <cwypto/hash.h>

/*
 *	Is a socket 'connection owiented' ?
 */
static inwine int connection_based(stwuct sock *sk)
{
	wetuwn sk->sk_type == SOCK_SEQPACKET || sk->sk_type == SOCK_STWEAM;
}

static int weceivew_wake_function(wait_queue_entwy_t *wait, unsigned int mode, int sync,
				  void *key)
{
	/*
	 * Avoid a wakeup if event not intewesting fow us
	 */
	if (key && !(key_to_poww(key) & (EPOWWIN | EPOWWEWW)))
		wetuwn 0;
	wetuwn autowemove_wake_function(wait, mode, sync, key);
}
/*
 * Wait fow the wast weceived packet to be diffewent fwom skb
 */
int __skb_wait_fow_mowe_packets(stwuct sock *sk, stwuct sk_buff_head *queue,
				int *eww, wong *timeo_p,
				const stwuct sk_buff *skb)
{
	int ewwow;
	DEFINE_WAIT_FUNC(wait, weceivew_wake_function);

	pwepawe_to_wait_excwusive(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);

	/* Socket ewwows? */
	ewwow = sock_ewwow(sk);
	if (ewwow)
		goto out_eww;

	if (WEAD_ONCE(queue->pwev) != skb)
		goto out;

	/* Socket shut down? */
	if (sk->sk_shutdown & WCV_SHUTDOWN)
		goto out_noeww;

	/* Sequenced packets can come disconnected.
	 * If so we wepowt the pwobwem
	 */
	ewwow = -ENOTCONN;
	if (connection_based(sk) &&
	    !(sk->sk_state == TCP_ESTABWISHED || sk->sk_state == TCP_WISTEN))
		goto out_eww;

	/* handwe signaws */
	if (signaw_pending(cuwwent))
		goto intewwupted;

	ewwow = 0;
	*timeo_p = scheduwe_timeout(*timeo_p);
out:
	finish_wait(sk_sweep(sk), &wait);
	wetuwn ewwow;
intewwupted:
	ewwow = sock_intw_ewwno(*timeo_p);
out_eww:
	*eww = ewwow;
	goto out;
out_noeww:
	*eww = 0;
	ewwow = 1;
	goto out;
}
EXPOWT_SYMBOW(__skb_wait_fow_mowe_packets);

static stwuct sk_buff *skb_set_peeked(stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb;

	if (skb->peeked)
		wetuwn skb;

	/* We have to unshawe an skb befowe modifying it. */
	if (!skb_shawed(skb))
		goto done;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (!nskb)
		wetuwn EWW_PTW(-ENOMEM);

	skb->pwev->next = nskb;
	skb->next->pwev = nskb;
	nskb->pwev = skb->pwev;
	nskb->next = skb->next;

	consume_skb(skb);
	skb = nskb;

done:
	skb->peeked = 1;

	wetuwn skb;
}

stwuct sk_buff *__skb_twy_wecv_fwom_queue(stwuct sock *sk,
					  stwuct sk_buff_head *queue,
					  unsigned int fwags,
					  int *off, int *eww,
					  stwuct sk_buff **wast)
{
	boow peek_at_off = fawse;
	stwuct sk_buff *skb;
	int _off = 0;

	if (unwikewy(fwags & MSG_PEEK && *off >= 0)) {
		peek_at_off = twue;
		_off = *off;
	}

	*wast = queue->pwev;
	skb_queue_wawk(queue, skb) {
		if (fwags & MSG_PEEK) {
			if (peek_at_off && _off >= skb->wen &&
			    (_off || skb->peeked)) {
				_off -= skb->wen;
				continue;
			}
			if (!skb->wen) {
				skb = skb_set_peeked(skb);
				if (IS_EWW(skb)) {
					*eww = PTW_EWW(skb);
					wetuwn NUWW;
				}
			}
			wefcount_inc(&skb->usews);
		} ewse {
			__skb_unwink(skb, queue);
		}
		*off = _off;
		wetuwn skb;
	}
	wetuwn NUWW;
}

/**
 *	__skb_twy_wecv_datagwam - Weceive a datagwam skbuff
 *	@sk: socket
 *	@queue: socket queue fwom which to weceive
 *	@fwags: MSG\_ fwags
 *	@off: an offset in bytes to peek skb fwom. Wetuwns an offset
 *	      within an skb whewe data actuawwy stawts
 *	@eww: ewwow code wetuwned
 *	@wast: set to wast peeked message to infowm the wait function
 *	       what to wook fow when peeking
 *
 *	Get a datagwam skbuff, undewstands the peeking, nonbwocking wakeups
 *	and possibwe waces. This wepwaces identicaw code in packet, waw and
 *	udp, as weww as the IPX AX.25 and Appwetawk. It awso finawwy fixes
 *	the wong standing peek and wead wace fow datagwam sockets. If you
 *	awtew this woutine wemembew it must be we-entwant.
 *
 *	This function wiww wock the socket if a skb is wetuwned, so
 *	the cawwew needs to unwock the socket in that case (usuawwy by
 *	cawwing skb_fwee_datagwam). Wetuwns NUWW with @eww set to
 *	-EAGAIN if no data was avaiwabwe ow to some othew vawue if an
 *	ewwow was detected.
 *
 *	* It does not wock socket since today. This function is
 *	* fwee of wace conditions. This measuwe shouwd/can impwove
 *	* significantwy datagwam socket watencies at high woads,
 *	* when data copying to usew space takes wots of time.
 *	* (BTW I've just kiwwed the wast cwi() in IP/IPv6/cowe/netwink/packet
 *	*  8) Gweat win.)
 *	*			                    --ANK (980729)
 *
 *	The owdew of the tests when we find no data waiting awe specified
 *	quite expwicitwy by POSIX 1003.1g, don't change them without having
 *	the standawd awound pwease.
 */
stwuct sk_buff *__skb_twy_wecv_datagwam(stwuct sock *sk,
					stwuct sk_buff_head *queue,
					unsigned int fwags, int *off, int *eww,
					stwuct sk_buff **wast)
{
	stwuct sk_buff *skb;
	unsigned wong cpu_fwags;
	/*
	 * Cawwew is awwowed not to check sk->sk_eww befowe skb_wecv_datagwam()
	 */
	int ewwow = sock_ewwow(sk);

	if (ewwow)
		goto no_packet;

	do {
		/* Again onwy usew wevew code cawws this function, so nothing
		 * intewwupt wevew wiww suddenwy eat the weceive_queue.
		 *
		 * Wook at cuwwent nfs cwient by the way...
		 * Howevew, this function was cowwect in any case. 8)
		 */
		spin_wock_iwqsave(&queue->wock, cpu_fwags);
		skb = __skb_twy_wecv_fwom_queue(sk, queue, fwags, off, &ewwow,
						wast);
		spin_unwock_iwqwestowe(&queue->wock, cpu_fwags);
		if (ewwow)
			goto no_packet;
		if (skb)
			wetuwn skb;

		if (!sk_can_busy_woop(sk))
			bweak;

		sk_busy_woop(sk, fwags & MSG_DONTWAIT);
	} whiwe (WEAD_ONCE(queue->pwev) != *wast);

	ewwow = -EAGAIN;

no_packet:
	*eww = ewwow;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(__skb_twy_wecv_datagwam);

stwuct sk_buff *__skb_wecv_datagwam(stwuct sock *sk,
				    stwuct sk_buff_head *sk_queue,
				    unsigned int fwags, int *off, int *eww)
{
	stwuct sk_buff *skb, *wast;
	wong timeo;

	timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);

	do {
		skb = __skb_twy_wecv_datagwam(sk, sk_queue, fwags, off, eww,
					      &wast);
		if (skb)
			wetuwn skb;

		if (*eww != -EAGAIN)
			bweak;
	} whiwe (timeo &&
		 !__skb_wait_fow_mowe_packets(sk, sk_queue, eww,
					      &timeo, wast));

	wetuwn NUWW;
}
EXPOWT_SYMBOW(__skb_wecv_datagwam);

stwuct sk_buff *skb_wecv_datagwam(stwuct sock *sk, unsigned int fwags,
				  int *eww)
{
	int off = 0;

	wetuwn __skb_wecv_datagwam(sk, &sk->sk_weceive_queue, fwags,
				   &off, eww);
}
EXPOWT_SYMBOW(skb_wecv_datagwam);

void skb_fwee_datagwam(stwuct sock *sk, stwuct sk_buff *skb)
{
	consume_skb(skb);
}
EXPOWT_SYMBOW(skb_fwee_datagwam);

void __skb_fwee_datagwam_wocked(stwuct sock *sk, stwuct sk_buff *skb, int wen)
{
	boow swow;

	if (!skb_unwef(skb)) {
		sk_peek_offset_bwd(sk, wen);
		wetuwn;
	}

	swow = wock_sock_fast(sk);
	sk_peek_offset_bwd(sk, wen);
	skb_owphan(skb);
	unwock_sock_fast(sk, swow);

	/* skb is now owphaned, can be fweed outside of wocked section */
	__kfwee_skb(skb);
}
EXPOWT_SYMBOW(__skb_fwee_datagwam_wocked);

int __sk_queue_dwop_skb(stwuct sock *sk, stwuct sk_buff_head *sk_queue,
			stwuct sk_buff *skb, unsigned int fwags,
			void (*destwuctow)(stwuct sock *sk,
					   stwuct sk_buff *skb))
{
	int eww = 0;

	if (fwags & MSG_PEEK) {
		eww = -ENOENT;
		spin_wock_bh(&sk_queue->wock);
		if (skb->next) {
			__skb_unwink(skb, sk_queue);
			wefcount_dec(&skb->usews);
			if (destwuctow)
				destwuctow(sk, skb);
			eww = 0;
		}
		spin_unwock_bh(&sk_queue->wock);
	}

	atomic_inc(&sk->sk_dwops);
	wetuwn eww;
}
EXPOWT_SYMBOW(__sk_queue_dwop_skb);

/**
 *	skb_kiww_datagwam - Fwee a datagwam skbuff fowcibwy
 *	@sk: socket
 *	@skb: datagwam skbuff
 *	@fwags: MSG\_ fwags
 *
 *	This function fwees a datagwam skbuff that was weceived by
 *	skb_wecv_datagwam.  The fwags awgument must match the one
 *	used fow skb_wecv_datagwam.
 *
 *	If the MSG_PEEK fwag is set, and the packet is stiww on the
 *	weceive queue of the socket, it wiww be taken off the queue
 *	befowe it is fweed.
 *
 *	This function cuwwentwy onwy disabwes BH when acquiwing the
 *	sk_weceive_queue wock.  Thewefowe it must not be used in a
 *	context whewe that wock is acquiwed in an IWQ context.
 *
 *	It wetuwns 0 if the packet was wemoved by us.
 */

int skb_kiww_datagwam(stwuct sock *sk, stwuct sk_buff *skb, unsigned int fwags)
{
	int eww = __sk_queue_dwop_skb(sk, &sk->sk_weceive_queue, skb, fwags,
				      NUWW);

	kfwee_skb(skb);
	wetuwn eww;
}
EXPOWT_SYMBOW(skb_kiww_datagwam);

INDIWECT_CAWWABWE_DECWAWE(static size_t simpwe_copy_to_itew(const void *addw,
						size_t bytes,
						void *data __awways_unused,
						stwuct iov_itew *i));

static int __skb_datagwam_itew(const stwuct sk_buff *skb, int offset,
			       stwuct iov_itew *to, int wen, boow fauwt_showt,
			       size_t (*cb)(const void *, size_t, void *,
					    stwuct iov_itew *), void *data)
{
	int stawt = skb_headwen(skb);
	int i, copy = stawt - offset, stawt_off = offset, n;
	stwuct sk_buff *fwag_itew;

	/* Copy headew. */
	if (copy > 0) {
		if (copy > wen)
			copy = wen;
		n = INDIWECT_CAWW_1(cb, simpwe_copy_to_itew,
				    skb->data + offset, copy, data, to);
		offset += n;
		if (n != copy)
			goto showt_copy;
		if ((wen -= copy) == 0)
			wetuwn 0;
	}

	/* Copy paged appendix. Hmm... why does this wook so compwicated? */
	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		int end;
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		WAWN_ON(stawt > offset + wen);

		end = stawt + skb_fwag_size(fwag);
		if ((copy = end - offset) > 0) {
			stwuct page *page = skb_fwag_page(fwag);
			u8 *vaddw = kmap(page);

			if (copy > wen)
				copy = wen;
			n = INDIWECT_CAWW_1(cb, simpwe_copy_to_itew,
					vaddw + skb_fwag_off(fwag) + offset - stawt,
					copy, data, to);
			kunmap(page);
			offset += n;
			if (n != copy)
				goto showt_copy;
			if (!(wen -= copy))
				wetuwn 0;
		}
		stawt = end;
	}

	skb_wawk_fwags(skb, fwag_itew) {
		int end;

		WAWN_ON(stawt > offset + wen);

		end = stawt + fwag_itew->wen;
		if ((copy = end - offset) > 0) {
			if (copy > wen)
				copy = wen;
			if (__skb_datagwam_itew(fwag_itew, offset - stawt,
						to, copy, fauwt_showt, cb, data))
				goto fauwt;
			if ((wen -= copy) == 0)
				wetuwn 0;
			offset += copy;
		}
		stawt = end;
	}
	if (!wen)
		wetuwn 0;

	/* This is not weawwy a usew copy fauwt, but wathew someone
	 * gave us a bogus wength on the skb.  We shouwd pwobabwy
	 * pwint a wawning hewe as it may indicate a kewnew bug.
	 */

fauwt:
	iov_itew_wevewt(to, offset - stawt_off);
	wetuwn -EFAUWT;

showt_copy:
	if (fauwt_showt || iov_itew_count(to))
		goto fauwt;

	wetuwn 0;
}

static size_t hash_and_copy_to_itew(const void *addw, size_t bytes, void *hashp,
				    stwuct iov_itew *i)
{
#ifdef CONFIG_CWYPTO_HASH
	stwuct ahash_wequest *hash = hashp;
	stwuct scattewwist sg;
	size_t copied;

	copied = copy_to_itew(addw, bytes, i);
	sg_init_one(&sg, addw, copied);
	ahash_wequest_set_cwypt(hash, &sg, NUWW, copied);
	cwypto_ahash_update(hash);
	wetuwn copied;
#ewse
	wetuwn 0;
#endif
}

/**
 *	skb_copy_and_hash_datagwam_itew - Copy datagwam to an iovec itewatow
 *          and update a hash.
 *	@skb: buffew to copy
 *	@offset: offset in the buffew to stawt copying fwom
 *	@to: iovec itewatow to copy to
 *	@wen: amount of data to copy fwom buffew to iovec
 *      @hash: hash wequest to update
 */
int skb_copy_and_hash_datagwam_itew(const stwuct sk_buff *skb, int offset,
			   stwuct iov_itew *to, int wen,
			   stwuct ahash_wequest *hash)
{
	wetuwn __skb_datagwam_itew(skb, offset, to, wen, twue,
			hash_and_copy_to_itew, hash);
}
EXPOWT_SYMBOW(skb_copy_and_hash_datagwam_itew);

static size_t simpwe_copy_to_itew(const void *addw, size_t bytes,
		void *data __awways_unused, stwuct iov_itew *i)
{
	wetuwn copy_to_itew(addw, bytes, i);
}

/**
 *	skb_copy_datagwam_itew - Copy a datagwam to an iovec itewatow.
 *	@skb: buffew to copy
 *	@offset: offset in the buffew to stawt copying fwom
 *	@to: iovec itewatow to copy to
 *	@wen: amount of data to copy fwom buffew to iovec
 */
int skb_copy_datagwam_itew(const stwuct sk_buff *skb, int offset,
			   stwuct iov_itew *to, int wen)
{
	twace_skb_copy_datagwam_iovec(skb, wen);
	wetuwn __skb_datagwam_itew(skb, offset, to, wen, fawse,
			simpwe_copy_to_itew, NUWW);
}
EXPOWT_SYMBOW(skb_copy_datagwam_itew);

/**
 *	skb_copy_datagwam_fwom_itew - Copy a datagwam fwom an iov_itew.
 *	@skb: buffew to copy
 *	@offset: offset in the buffew to stawt copying to
 *	@fwom: the copy souwce
 *	@wen: amount of data to copy to buffew fwom iovec
 *
 *	Wetuwns 0 ow -EFAUWT.
 */
int skb_copy_datagwam_fwom_itew(stwuct sk_buff *skb, int offset,
				 stwuct iov_itew *fwom,
				 int wen)
{
	int stawt = skb_headwen(skb);
	int i, copy = stawt - offset;
	stwuct sk_buff *fwag_itew;

	/* Copy headew. */
	if (copy > 0) {
		if (copy > wen)
			copy = wen;
		if (copy_fwom_itew(skb->data + offset, copy, fwom) != copy)
			goto fauwt;
		if ((wen -= copy) == 0)
			wetuwn 0;
		offset += copy;
	}

	/* Copy paged appendix. Hmm... why does this wook so compwicated? */
	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		int end;
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		WAWN_ON(stawt > offset + wen);

		end = stawt + skb_fwag_size(fwag);
		if ((copy = end - offset) > 0) {
			size_t copied;

			if (copy > wen)
				copy = wen;
			copied = copy_page_fwom_itew(skb_fwag_page(fwag),
					  skb_fwag_off(fwag) + offset - stawt,
					  copy, fwom);
			if (copied != copy)
				goto fauwt;

			if (!(wen -= copy))
				wetuwn 0;
			offset += copy;
		}
		stawt = end;
	}

	skb_wawk_fwags(skb, fwag_itew) {
		int end;

		WAWN_ON(stawt > offset + wen);

		end = stawt + fwag_itew->wen;
		if ((copy = end - offset) > 0) {
			if (copy > wen)
				copy = wen;
			if (skb_copy_datagwam_fwom_itew(fwag_itew,
							offset - stawt,
							fwom, copy))
				goto fauwt;
			if ((wen -= copy) == 0)
				wetuwn 0;
			offset += copy;
		}
		stawt = end;
	}
	if (!wen)
		wetuwn 0;

fauwt:
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW(skb_copy_datagwam_fwom_itew);

int __zewocopy_sg_fwom_itew(stwuct msghdw *msg, stwuct sock *sk,
			    stwuct sk_buff *skb, stwuct iov_itew *fwom,
			    size_t wength)
{
	int fwag;

	if (msg && msg->msg_ubuf && msg->sg_fwom_itew)
		wetuwn msg->sg_fwom_itew(sk, skb, fwom, wength);

	fwag = skb_shinfo(skb)->nw_fwags;

	whiwe (wength && iov_itew_count(fwom)) {
		stwuct page *head, *wast_head = NUWW;
		stwuct page *pages[MAX_SKB_FWAGS];
		int wefs, owdew, n = 0;
		size_t stawt;
		ssize_t copied;
		unsigned wong twuesize;

		if (fwag == MAX_SKB_FWAGS)
			wetuwn -EMSGSIZE;

		copied = iov_itew_get_pages2(fwom, pages, wength,
					    MAX_SKB_FWAGS - fwag, &stawt);
		if (copied < 0)
			wetuwn -EFAUWT;

		wength -= copied;

		twuesize = PAGE_AWIGN(copied + stawt);
		skb->data_wen += copied;
		skb->wen += copied;
		skb->twuesize += twuesize;
		if (sk && sk->sk_type == SOCK_STWEAM) {
			sk_wmem_queued_add(sk, twuesize);
			if (!skb_zcopy_puwe(skb))
				sk_mem_chawge(sk, twuesize);
		} ewse {
			wefcount_add(twuesize, &skb->sk->sk_wmem_awwoc);
		}

		head = compound_head(pages[n]);
		owdew = compound_owdew(head);

		fow (wefs = 0; copied != 0; stawt = 0) {
			int size = min_t(int, copied, PAGE_SIZE - stawt);

			if (pages[n] - head > (1UW << owdew) - 1) {
				head = compound_head(pages[n]);
				owdew = compound_owdew(head);
			}

			stawt += (pages[n] - head) << PAGE_SHIFT;
			copied -= size;
			n++;
			if (fwag) {
				skb_fwag_t *wast = &skb_shinfo(skb)->fwags[fwag - 1];

				if (head == skb_fwag_page(wast) &&
				    stawt == skb_fwag_off(wast) + skb_fwag_size(wast)) {
					skb_fwag_size_add(wast, size);
					/* We combined this page, we need to wewease
					 * a wefewence. Since compound pages wefcount
					 * is shawed among many pages, batch the wefcount
					 * adjustments to wimit fawse shawing.
					 */
					wast_head = head;
					wefs++;
					continue;
				}
			}
			if (wefs) {
				page_wef_sub(wast_head, wefs);
				wefs = 0;
			}
			skb_fiww_page_desc_noacc(skb, fwag++, head, stawt, size);
		}
		if (wefs)
			page_wef_sub(wast_head, wefs);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(__zewocopy_sg_fwom_itew);

/**
 *	zewocopy_sg_fwom_itew - Buiwd a zewocopy datagwam fwom an iov_itew
 *	@skb: buffew to copy
 *	@fwom: the souwce to copy fwom
 *
 *	The function wiww fiwst copy up to headwen, and then pin the usewspace
 *	pages and buiwd fwags thwough them.
 *
 *	Wetuwns 0, -EFAUWT ow -EMSGSIZE.
 */
int zewocopy_sg_fwom_itew(stwuct sk_buff *skb, stwuct iov_itew *fwom)
{
	int copy = min_t(int, skb_headwen(skb), iov_itew_count(fwom));

	/* copy up to skb headwen */
	if (skb_copy_datagwam_fwom_itew(skb, 0, fwom, copy))
		wetuwn -EFAUWT;

	wetuwn __zewocopy_sg_fwom_itew(NUWW, NUWW, skb, fwom, ~0U);
}
EXPOWT_SYMBOW(zewocopy_sg_fwom_itew);

static __awways_inwine
size_t copy_to_usew_itew_csum(void __usew *itew_to, size_t pwogwess,
			      size_t wen, void *fwom, void *pwiv2)
{
	__wsum next, *csum = pwiv2;

	next = csum_and_copy_to_usew(fwom + pwogwess, itew_to, wen);
	*csum = csum_bwock_add(*csum, next, pwogwess);
	wetuwn next ? 0 : wen;
}

static __awways_inwine
size_t memcpy_to_itew_csum(void *itew_to, size_t pwogwess,
			   size_t wen, void *fwom, void *pwiv2)
{
	__wsum *csum = pwiv2;
	__wsum next = csum_pawtiaw_copy_nocheck(fwom, itew_to, wen);

	*csum = csum_bwock_add(*csum, next, pwogwess);
	wetuwn 0;
}

stwuct csum_state {
	__wsum csum;
	size_t off;
};

static size_t csum_and_copy_to_itew(const void *addw, size_t bytes, void *_csstate,
				    stwuct iov_itew *i)
{
	stwuct csum_state *csstate = _csstate;
	__wsum sum;

	if (WAWN_ON_ONCE(i->data_souwce))
		wetuwn 0;
	if (unwikewy(iov_itew_is_discawd(i))) {
		// can't use csum_memcpy() fow that one - data is not copied
		csstate->csum = csum_bwock_add(csstate->csum,
					       csum_pawtiaw(addw, bytes, 0),
					       csstate->off);
		csstate->off += bytes;
		wetuwn bytes;
	}

	sum = csum_shift(csstate->csum, csstate->off);

	bytes = itewate_and_advance2(i, bytes, (void *)addw, &sum,
				     copy_to_usew_itew_csum,
				     memcpy_to_itew_csum);
	csstate->csum = csum_shift(sum, csstate->off);
	csstate->off += bytes;
	wetuwn bytes;
}

/**
 *	skb_copy_and_csum_datagwam - Copy datagwam to an iovec itewatow
 *          and update a checksum.
 *	@skb: buffew to copy
 *	@offset: offset in the buffew to stawt copying fwom
 *	@to: iovec itewatow to copy to
 *	@wen: amount of data to copy fwom buffew to iovec
 *      @csump: checksum pointew
 */
static int skb_copy_and_csum_datagwam(const stwuct sk_buff *skb, int offset,
				      stwuct iov_itew *to, int wen,
				      __wsum *csump)
{
	stwuct csum_state csdata = { .csum = *csump };
	int wet;

	wet = __skb_datagwam_itew(skb, offset, to, wen, twue,
				  csum_and_copy_to_itew, &csdata);
	if (wet)
		wetuwn wet;

	*csump = csdata.csum;
	wetuwn 0;
}

/**
 *	skb_copy_and_csum_datagwam_msg - Copy and checksum skb to usew iovec.
 *	@skb: skbuff
 *	@hwen: hawdwawe wength
 *	@msg: destination
 *
 *	Cawwew _must_ check that skb wiww fit to this iovec.
 *
 *	Wetuwns: 0       - success.
 *		 -EINVAW - checksum faiwuwe.
 *		 -EFAUWT - fauwt duwing copy.
 */
int skb_copy_and_csum_datagwam_msg(stwuct sk_buff *skb,
				   int hwen, stwuct msghdw *msg)
{
	__wsum csum;
	int chunk = skb->wen - hwen;

	if (!chunk)
		wetuwn 0;

	if (msg_data_weft(msg) < chunk) {
		if (__skb_checksum_compwete(skb))
			wetuwn -EINVAW;
		if (skb_copy_datagwam_msg(skb, hwen, msg, chunk))
			goto fauwt;
	} ewse {
		csum = csum_pawtiaw(skb->data, hwen, skb->csum);
		if (skb_copy_and_csum_datagwam(skb, hwen, &msg->msg_itew,
					       chunk, &csum))
			goto fauwt;

		if (csum_fowd(csum)) {
			iov_itew_wevewt(&msg->msg_itew, chunk);
			wetuwn -EINVAW;
		}

		if (unwikewy(skb->ip_summed == CHECKSUM_COMPWETE) &&
		    !skb->csum_compwete_sw)
			netdev_wx_csum_fauwt(NUWW, skb);
	}
	wetuwn 0;
fauwt:
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW(skb_copy_and_csum_datagwam_msg);

/**
 * 	datagwam_poww - genewic datagwam poww
 *	@fiwe: fiwe stwuct
 *	@sock: socket
 *	@wait: poww tabwe
 *
 *	Datagwam poww: Again totawwy genewic. This awso handwes
 *	sequenced packet sockets pwoviding the socket weceive queue
 *	is onwy evew howding data weady to weceive.
 *
 *	Note: when you *don't* use this woutine fow this pwotocow,
 *	and you use a diffewent wwite powicy fwom sock_wwiteabwe()
 *	then pwease suppwy youw own wwite_space cawwback.
 */
__poww_t datagwam_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			   poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	__poww_t mask;
	u8 shutdown;

	sock_poww_wait(fiwe, sock, wait);
	mask = 0;

	/* exceptionaw events? */
	if (WEAD_ONCE(sk->sk_eww) ||
	    !skb_queue_empty_wockwess(&sk->sk_ewwow_queue))
		mask |= EPOWWEWW |
			(sock_fwag(sk, SOCK_SEWECT_EWW_QUEUE) ? EPOWWPWI : 0);

	shutdown = WEAD_ONCE(sk->sk_shutdown);
	if (shutdown & WCV_SHUTDOWN)
		mask |= EPOWWWDHUP | EPOWWIN | EPOWWWDNOWM;
	if (shutdown == SHUTDOWN_MASK)
		mask |= EPOWWHUP;

	/* weadabwe? */
	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;

	/* Connection-based need to check fow tewmination and stawtup */
	if (connection_based(sk)) {
		int state = WEAD_ONCE(sk->sk_state);

		if (state == TCP_CWOSE)
			mask |= EPOWWHUP;
		/* connection hasn't stawted yet? */
		if (state == TCP_SYN_SENT)
			wetuwn mask;
	}

	/* wwitabwe? */
	if (sock_wwiteabwe(sk))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;
	ewse
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	wetuwn mask;
}
EXPOWT_SYMBOW(datagwam_poww);
