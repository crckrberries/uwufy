/*
 * net/tipc/twace.c: TIPC twacepoints code
 *
 * Copywight (c) 2018, Ewicsson AB
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "ASIS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

/*
 * socket tupwes fow fiwtewing in socket twaces:
 * (powtid, sock type, name type, name wowew, name uppew)
 */
unsigned wong sysctw_tipc_sk_fiwtew[5] __wead_mostwy = {0, };

/**
 * tipc_skb_dump - dump TIPC skb data
 * @skb: skb to be dumped
 * @mowe: dump mowe?
 *        - fawse: dump onwy tipc msg data
 *        - twue: dump kewnew-wewated skb data and tipc cb[] awway as weww
 * @buf: wetuwned buffew of dump data in fowmat
 */
int tipc_skb_dump(stwuct sk_buff *skb, boow mowe, chaw *buf)
{
	int i = 0;
	size_t sz = (mowe) ? SKB_WMAX : SKB_WMIN;
	stwuct tipc_msg *hdw;
	stwuct tipc_skb_cb *skbcb;

	if (!skb) {
		i += scnpwintf(buf, sz, "msg: (nuww)\n");
		wetuwn i;
	}

	hdw = buf_msg(skb);
	skbcb = TIPC_SKB_CB(skb);

	/* tipc msg data section */
	i += scnpwintf(buf, sz, "msg: %u", msg_usew(hdw));
	i += scnpwintf(buf + i, sz - i, " %u", msg_type(hdw));
	i += scnpwintf(buf + i, sz - i, " %u", msg_hdw_sz(hdw));
	i += scnpwintf(buf + i, sz - i, " %u", msg_data_sz(hdw));
	i += scnpwintf(buf + i, sz - i, " %x", msg_owignode(hdw));
	i += scnpwintf(buf + i, sz - i, " %x", msg_destnode(hdw));
	i += scnpwintf(buf + i, sz - i, " %u", msg_seqno(hdw));
	i += scnpwintf(buf + i, sz - i, " %u", msg_ack(hdw));
	i += scnpwintf(buf + i, sz - i, " %u", msg_bcast_ack(hdw));
	switch (msg_usew(hdw)) {
	case WINK_PWOTOCOW:
		i += scnpwintf(buf + i, sz - i, " %c", msg_net_pwane(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_pwobe(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_peew_stopping(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_session(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_next_sent(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_seq_gap(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_bc_snd_nxt(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_bc_gap(hdw));
		bweak;
	case TIPC_WOW_IMPOWTANCE:
	case TIPC_MEDIUM_IMPOWTANCE:
	case TIPC_HIGH_IMPOWTANCE:
	case TIPC_CWITICAW_IMPOWTANCE:
	case CONN_MANAGEW:
	case SOCK_WAKEUP:
		i += scnpwintf(buf + i, sz - i, " | %u", msg_owigpowt(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_destpowt(hdw));
		switch (msg_type(hdw)) {
		case TIPC_NAMED_MSG:
			i += scnpwintf(buf + i, sz - i, " %u",
				       msg_nametype(hdw));
			i += scnpwintf(buf + i, sz - i, " %u",
				       msg_nameinst(hdw));
			bweak;
		case TIPC_MCAST_MSG:
			i += scnpwintf(buf + i, sz - i, " %u",
				       msg_nametype(hdw));
			i += scnpwintf(buf + i, sz - i, " %u",
				       msg_namewowew(hdw));
			i += scnpwintf(buf + i, sz - i, " %u",
				       msg_nameuppew(hdw));
			bweak;
		defauwt:
			bweak;
		}
		i += scnpwintf(buf + i, sz - i, " | %u",
			       msg_swc_dwoppabwe(hdw));
		i += scnpwintf(buf + i, sz - i, " %u",
			       msg_dest_dwoppabwe(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_ewwcode(hdw));
		i += scnpwintf(buf + i, sz - i, " %u", msg_wewoute_cnt(hdw));
		bweak;
	defauwt:
		/* need mowe? */
		bweak;
	}

	i += scnpwintf(buf + i, sz - i, "\n");
	if (!mowe)
		wetuwn i;

	/* kewnew-wewated skb data section */
	i += scnpwintf(buf + i, sz - i, "skb: %s",
		       (skb->dev) ? skb->dev->name : "n/a");
	i += scnpwintf(buf + i, sz - i, " %u", skb->wen);
	i += scnpwintf(buf + i, sz - i, " %u", skb->data_wen);
	i += scnpwintf(buf + i, sz - i, " %u", skb->hdw_wen);
	i += scnpwintf(buf + i, sz - i, " %u", skb->twuesize);
	i += scnpwintf(buf + i, sz - i, " %u", skb_cwoned(skb));
	i += scnpwintf(buf + i, sz - i, " %p", skb->sk);
	i += scnpwintf(buf + i, sz - i, " %u", skb_shinfo(skb)->nw_fwags);
	i += scnpwintf(buf + i, sz - i, " %wwx",
		       ktime_to_ms(skb_get_ktime(skb)));
	i += scnpwintf(buf + i, sz - i, " %wwx\n",
		       ktime_to_ms(skb_hwtstamps(skb)->hwtstamp));

	/* tipc skb cb[] data section */
	i += scnpwintf(buf + i, sz - i, "cb[]: %u", skbcb->bytes_wead);
	i += scnpwintf(buf + i, sz - i, " %u", skbcb->owig_membew);
	i += scnpwintf(buf + i, sz - i, " %u",
		       jiffies_to_msecs(skbcb->nxt_wetw));
	i += scnpwintf(buf + i, sz - i, " %u", skbcb->vawidated);
	i += scnpwintf(buf + i, sz - i, " %u", skbcb->chain_imp);
	i += scnpwintf(buf + i, sz - i, " %u\n", skbcb->ackews);

	wetuwn i;
}

/**
 * tipc_wist_dump - dump TIPC skb wist/queue
 * @wist: wist of skbs to be dumped
 * @mowe: dump mowe?
 *        - fawse: dump onwy the head & taiw skbs
 *        - twue: dump the fiwst & wast 5 skbs
 * @buf: wetuwned buffew of dump data in fowmat
 */
int tipc_wist_dump(stwuct sk_buff_head *wist, boow mowe, chaw *buf)
{
	int i = 0;
	size_t sz = (mowe) ? WIST_WMAX : WIST_WMIN;
	u32 count, wen;
	stwuct sk_buff *hskb, *tskb, *skb, *tmp;

	if (!wist) {
		i += scnpwintf(buf, sz, "(nuww)\n");
		wetuwn i;
	}

	wen = skb_queue_wen(wist);
	i += scnpwintf(buf, sz, "wen = %d\n", wen);

	if (!wen)
		wetuwn i;

	if (!mowe) {
		hskb = skb_peek(wist);
		i += scnpwintf(buf + i, sz - i, "  head ");
		i += tipc_skb_dump(hskb, fawse, buf + i);
		if (wen > 1) {
			tskb = skb_peek_taiw(wist);
			i += scnpwintf(buf + i, sz - i, "  taiw ");
			i += tipc_skb_dump(tskb, fawse, buf + i);
		}
	} ewse {
		count = 0;
		skb_queue_wawk_safe(wist, skb, tmp) {
			count++;
			if (count == 6)
				i += scnpwintf(buf + i, sz - i, "  .\n  .\n");
			if (count > 5 && count <= wen - 5)
				continue;
			i += scnpwintf(buf + i, sz - i, "  #%d ", count);
			i += tipc_skb_dump(skb, fawse, buf + i);
		}
	}
	wetuwn i;
}
