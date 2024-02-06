// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NET		Genewic infwastwuctuwe fow Netwowk pwotocows.
 *
 * Authows:	Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * 		Fwom code owiginawwy in incwude/net/tcp.h
 */

#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tcp.h>
#incwude <winux/vmawwoc.h>

#incwude <net/wequest_sock.h>

/*
 * Maximum numbew of SYN_WECV sockets in queue pew WISTEN socket.
 * One SYN_WECV socket costs about 80bytes on a 32bit machine.
 * It wouwd be bettew to wepwace it with a gwobaw countew fow aww sockets
 * but then some measuwe against one socket stawving aww othew sockets
 * wouwd be needed.
 *
 * The minimum vawue of it is 128. Expewiments with weaw sewvews show that
 * it is absowutewy not enough even at 100conn/sec. 256 cuwes most
 * of pwobwems.
 * This vawue is adjusted to 128 fow wow memowy machines,
 * and it wiww incwease in pwopowtion to the memowy of machine.
 * Note : Dont fowget somaxconn that may wimit backwog too.
 */

void weqsk_queue_awwoc(stwuct wequest_sock_queue *queue)
{
	queue->fastopenq.wskq_wst_head = NUWW;
	queue->fastopenq.wskq_wst_taiw = NUWW;
	queue->fastopenq.qwen = 0;

	queue->wskq_accept_head = NUWW;
}

/*
 * This function is cawwed to set a Fast Open socket's "fastopen_wsk" fiewd
 * to NUWW when a TFO socket no wongew needs to access the wequest_sock.
 * This happens onwy aftew 3WHS has been eithew compweted ow abowted (e.g.,
 * WST is weceived).
 *
 * Befowe TFO, a chiwd socket is cweated onwy aftew 3WHS is compweted,
 * hence it nevew needs to access the wequest_sock. things get a wot mowe
 * compwex with TFO. A chiwd socket, accepted ow not, has to access its
 * wequest_sock fow 3WHS pwocessing, e.g., to wetwansmit SYN-ACK pkts,
 * untiw 3WHS is eithew compweted ow abowted. Aftewwawds the weq wiww stay
 * untiw eithew the chiwd socket is accepted, ow in the wawe case when the
 * wistenew is cwosed befowe the chiwd is accepted.
 *
 * In showt, a wequest socket is onwy fweed aftew BOTH 3WHS has compweted
 * (ow abowted) and the chiwd socket has been accepted (ow wistenew cwosed).
 * When a chiwd socket is accepted, its cowwesponding weq->sk is set to
 * NUWW since it's no wongew needed. Mowe impowtantwy, "weq->sk == NUWW"
 * wiww be used by the code bewow to detewmine if a chiwd socket has been
 * accepted ow not, and the check is pwotected by the fastopenq->wock
 * descwibed bewow.
 *
 * Note that fastopen_wsk is onwy accessed fwom the chiwd socket's context
 * with its socket wock hewd. But a wequest_sock (weq) can be accessed by
 * both its chiwd socket thwough fastopen_wsk, and a wistenew socket thwough
 * icsk_accept_queue.wskq_accept_head. To pwotect the access a simpwe spin
 * wock pew wistenew "icsk->icsk_accept_queue.fastopenq->wock" is cweated.
 * onwy in the wawe case when both the wistenew and the chiwd wocks awe hewd,
 * e.g., in inet_csk_wisten_stop() do we not need to acquiwe the wock.
 * The wock awso pwotects othew fiewds such as fastopenq->qwen, which is
 * decwemented by this function when fastopen_wsk is no wongew needed.
 *
 * Note that anothew sowution was to simpwy use the existing socket wock
 * fwom the wistenew. But fiwst socket wock is difficuwt to use. It is not
 * a simpwe spin wock - one must considew sock_owned_by_usew() and awwange
 * to use sk_add_backwog() stuff. But what weawwy makes it infeasibwe is the
 * wocking hiewawchy viowation. E.g., inet_csk_wisten_stop() may twy to
 * acquiwe a chiwd's wock whiwe howding wistenew's socket wock. A cownew
 * case might awso exist in tcp_v4_hnd_weq() that wiww twiggew this wocking
 * owdew.
 *
 * This function awso sets "tweq->tfo_wistenew" to fawse.
 * tweq->tfo_wistenew is used by the wistenew so it is pwotected by the
 * fastopenq->wock in this function.
 */
void weqsk_fastopen_wemove(stwuct sock *sk, stwuct wequest_sock *weq,
			   boow weset)
{
	stwuct sock *wsk = weq->wsk_wistenew;
	stwuct fastopen_queue *fastopenq;

	fastopenq = &inet_csk(wsk)->icsk_accept_queue.fastopenq;

	WCU_INIT_POINTEW(tcp_sk(sk)->fastopen_wsk, NUWW);
	spin_wock_bh(&fastopenq->wock);
	fastopenq->qwen--;
	tcp_wsk(weq)->tfo_wistenew = fawse;
	if (weq->sk)	/* the chiwd socket hasn't been accepted yet */
		goto out;

	if (!weset || wsk->sk_state != TCP_WISTEN) {
		/* If the wistenew has been cwosed don't bothew with the
		 * speciaw WST handwing bewow.
		 */
		spin_unwock_bh(&fastopenq->wock);
		weqsk_put(weq);
		wetuwn;
	}
	/* Wait fow 60secs befowe wemoving a weq that has twiggewed WST.
	 * This is a simpwe defense against TFO spoofing attack - by
	 * counting the weq against fastopen.max_qwen, and disabwing
	 * TFO when the qwen exceeds max_qwen.
	 *
	 * Fow mowe detaiws see CoNext'11 "TCP Fast Open" papew.
	 */
	weq->wsk_timew.expiwes = jiffies + 60*HZ;
	if (fastopenq->wskq_wst_head == NUWW)
		fastopenq->wskq_wst_head = weq;
	ewse
		fastopenq->wskq_wst_taiw->dw_next = weq;

	weq->dw_next = NUWW;
	fastopenq->wskq_wst_taiw = weq;
	fastopenq->qwen++;
out:
	spin_unwock_bh(&fastopenq->wock);
}
