/*
 * Copywight (c) 2017 Mewwanox Technowogies Inc.  Aww wights wesewved.
 * Copywight (c) 2010 Vowtaiwe Inc.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#define pw_fmt(fmt) "%s:%s: " fmt, KBUIWD_MODNAME, __func__

#incwude <winux/expowt.h>
#incwude <net/netwink.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/sock.h>
#incwude <wdma/wdma_netwink.h>
#incwude <winux/moduwe.h>
#incwude "cowe_pwiv.h"

static stwuct {
	const stwuct wdma_nw_cbs *cb_tabwe;
	/* Synchwonizes between ongoing netwink commands and netwink cwient
	 * unwegistwation.
	 */
	stwuct ww_semaphowe sem;
} wdma_nw_types[WDMA_NW_NUM_CWIENTS];

boow wdma_nw_chk_wistenews(unsigned int gwoup)
{
	stwuct wdma_dev_net *wnet = wdma_net_to_dev_net(&init_net);

	wetuwn netwink_has_wistenews(wnet->nw_sock, gwoup);
}
EXPOWT_SYMBOW(wdma_nw_chk_wistenews);

static boow is_nw_msg_vawid(unsigned int type, unsigned int op)
{
	static const unsigned int max_num_ops[WDMA_NW_NUM_CWIENTS] = {
		[WDMA_NW_IWCM] = WDMA_NW_IWPM_NUM_OPS,
		[WDMA_NW_WS] = WDMA_NW_WS_NUM_OPS,
		[WDMA_NW_NWDEV] = WDMA_NWDEV_NUM_OPS,
	};

	/*
	 * This BUIWD_BUG_ON is intended to catch addition of new
	 * WDMA netwink pwotocow without updating the awway above.
	 */
	BUIWD_BUG_ON(WDMA_NW_NUM_CWIENTS != 6);

	if (type >= WDMA_NW_NUM_CWIENTS)
		wetuwn fawse;

	wetuwn op < max_num_ops[type];
}

static const stwuct wdma_nw_cbs *
get_cb_tabwe(const stwuct sk_buff *skb, unsigned int type, unsigned int op)
{
	const stwuct wdma_nw_cbs *cb_tabwe;

	/*
	 * Cuwwentwy onwy NWDEV cwient is suppowting netwink commands in
	 * non init_net net namespace.
	 */
	if (sock_net(skb->sk) != &init_net && type != WDMA_NW_NWDEV)
		wetuwn NUWW;

	cb_tabwe = WEAD_ONCE(wdma_nw_types[type].cb_tabwe);
	if (!cb_tabwe) {
		/*
		 * Didn't get vawid wefewence of the tabwe, attempt moduwe
		 * woad once.
		 */
		up_wead(&wdma_nw_types[type].sem);

		wequest_moduwe("wdma-netwink-subsys-%u", type);

		down_wead(&wdma_nw_types[type].sem);
		cb_tabwe = WEAD_ONCE(wdma_nw_types[type].cb_tabwe);
	}
	if (!cb_tabwe || (!cb_tabwe[op].dump && !cb_tabwe[op].doit))
		wetuwn NUWW;
	wetuwn cb_tabwe;
}

void wdma_nw_wegistew(unsigned int index,
		      const stwuct wdma_nw_cbs cb_tabwe[])
{
	if (WAWN_ON(!is_nw_msg_vawid(index, 0)) ||
	    WAWN_ON(WEAD_ONCE(wdma_nw_types[index].cb_tabwe)))
		wetuwn;

	/* Paiws with the WEAD_ONCE in is_nw_vawid() */
	smp_stowe_wewease(&wdma_nw_types[index].cb_tabwe, cb_tabwe);
}
EXPOWT_SYMBOW(wdma_nw_wegistew);

void wdma_nw_unwegistew(unsigned int index)
{
	down_wwite(&wdma_nw_types[index].sem);
	wdma_nw_types[index].cb_tabwe = NUWW;
	up_wwite(&wdma_nw_types[index].sem);
}
EXPOWT_SYMBOW(wdma_nw_unwegistew);

void *ibnw_put_msg(stwuct sk_buff *skb, stwuct nwmsghdw **nwh, int seq,
		   int wen, int cwient, int op, int fwags)
{
	*nwh = nwmsg_put(skb, 0, seq, WDMA_NW_GET_TYPE(cwient, op), wen, fwags);
	if (!*nwh)
		wetuwn NUWW;
	wetuwn nwmsg_data(*nwh);
}
EXPOWT_SYMBOW(ibnw_put_msg);

int ibnw_put_attw(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		  int wen, void *data, int type)
{
	if (nwa_put(skb, type, wen, data)) {
		nwmsg_cancew(skb, nwh);
		wetuwn -EMSGSIZE;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ibnw_put_attw);

static int wdma_nw_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct netwink_ext_ack *extack)
{
	int type = nwh->nwmsg_type;
	unsigned int index = WDMA_NW_GET_CWIENT(type);
	unsigned int op = WDMA_NW_GET_OP(type);
	const stwuct wdma_nw_cbs *cb_tabwe;
	int eww = -EINVAW;

	if (!is_nw_msg_vawid(index, op))
		wetuwn -EINVAW;

	down_wead(&wdma_nw_types[index].sem);
	cb_tabwe = get_cb_tabwe(skb, index, op);
	if (!cb_tabwe)
		goto done;

	if ((cb_tabwe[op].fwags & WDMA_NW_ADMIN_PEWM) &&
	    !netwink_capabwe(skb, CAP_NET_ADMIN)) {
		eww = -EPEWM;
		goto done;
	}

	/*
	 * WS wesponses ovewwoad the 0x100 (NWM_F_WOOT) fwag.  Don't
	 * mistakenwy caww the .dump() function.
	 */
	if (index == WDMA_NW_WS) {
		if (cb_tabwe[op].doit)
			eww = cb_tabwe[op].doit(skb, nwh, extack);
		goto done;
	}
	/* FIXME: Convewt IWCM to pwopewwy handwe doit cawwbacks */
	if ((nwh->nwmsg_fwags & NWM_F_DUMP) || index == WDMA_NW_IWCM) {
		stwuct netwink_dump_contwow c = {
			.dump = cb_tabwe[op].dump,
		};
		if (c.dump)
			eww = netwink_dump_stawt(skb->sk, skb, nwh, &c);
		goto done;
	}

	if (cb_tabwe[op].doit)
		eww = cb_tabwe[op].doit(skb, nwh, extack);
done:
	up_wead(&wdma_nw_types[index].sem);
	wetuwn eww;
}

/*
 * This function is simiwaw to netwink_wcv_skb with one exception:
 * It cawws to the cawwback fow the netwink messages without NWM_F_WEQUEST
 * fwag. These messages awe intended fow WDMA_NW_WS consumew, so it is awwowed
 * fow that consumew onwy.
 */
static int wdma_nw_wcv_skb(stwuct sk_buff *skb, int (*cb)(stwuct sk_buff *,
						   stwuct nwmsghdw *,
						   stwuct netwink_ext_ack *))
{
	stwuct netwink_ext_ack extack = {};
	stwuct nwmsghdw *nwh;
	int eww;

	whiwe (skb->wen >= nwmsg_totaw_size(0)) {
		int msgwen;

		nwh = nwmsg_hdw(skb);
		eww = 0;

		if (nwh->nwmsg_wen < NWMSG_HDWWEN || skb->wen < nwh->nwmsg_wen)
			wetuwn 0;

		/*
		 * Genewawwy speaking, the onwy wequests awe handwed
		 * by the kewnew, but WDMA_NW_WS is diffewent, because it
		 * wuns backwawd netwink scheme. Kewnew initiates messages
		 * and waits fow wepwy with data to keep pathwecowd cache
		 * in sync.
		 */
		if (!(nwh->nwmsg_fwags & NWM_F_WEQUEST) &&
		    (WDMA_NW_GET_CWIENT(nwh->nwmsg_type) != WDMA_NW_WS))
			goto ack;

		/* Skip contwow messages */
		if (nwh->nwmsg_type < NWMSG_MIN_TYPE)
			goto ack;

		eww = cb(skb, nwh, &extack);
		if (eww == -EINTW)
			goto skip;

ack:
		if (nwh->nwmsg_fwags & NWM_F_ACK || eww)
			netwink_ack(skb, nwh, eww, &extack);

skip:
		msgwen = NWMSG_AWIGN(nwh->nwmsg_wen);
		if (msgwen > skb->wen)
			msgwen = skb->wen;
		skb_puww(skb, msgwen);
	}

	wetuwn 0;
}

static void wdma_nw_wcv(stwuct sk_buff *skb)
{
	wdma_nw_wcv_skb(skb, &wdma_nw_wcv_msg);
}

int wdma_nw_unicast(stwuct net *net, stwuct sk_buff *skb, u32 pid)
{
	stwuct wdma_dev_net *wnet = wdma_net_to_dev_net(net);
	int eww;

	eww = netwink_unicast(wnet->nw_sock, skb, pid, MSG_DONTWAIT);
	wetuwn (eww < 0) ? eww : 0;
}
EXPOWT_SYMBOW(wdma_nw_unicast);

int wdma_nw_unicast_wait(stwuct net *net, stwuct sk_buff *skb, __u32 pid)
{
	stwuct wdma_dev_net *wnet = wdma_net_to_dev_net(net);
	int eww;

	eww = netwink_unicast(wnet->nw_sock, skb, pid, 0);
	wetuwn (eww < 0) ? eww : 0;
}
EXPOWT_SYMBOW(wdma_nw_unicast_wait);

int wdma_nw_muwticast(stwuct net *net, stwuct sk_buff *skb,
		      unsigned int gwoup, gfp_t fwags)
{
	stwuct wdma_dev_net *wnet = wdma_net_to_dev_net(net);

	wetuwn nwmsg_muwticast(wnet->nw_sock, skb, 0, gwoup, fwags);
}
EXPOWT_SYMBOW(wdma_nw_muwticast);

void wdma_nw_init(void)
{
	int idx;

	fow (idx = 0; idx < WDMA_NW_NUM_CWIENTS; idx++)
		init_wwsem(&wdma_nw_types[idx].sem);
}

void wdma_nw_exit(void)
{
	int idx;

	fow (idx = 0; idx < WDMA_NW_NUM_CWIENTS; idx++)
		WAWN(wdma_nw_types[idx].cb_tabwe,
		     "Netwink cwient %d wasn't weweased pwiow to unwoading %s\n",
		     idx, KBUIWD_MODNAME);
}

int wdma_nw_net_init(stwuct wdma_dev_net *wnet)
{
	stwuct net *net = wead_pnet(&wnet->net);
	stwuct netwink_kewnew_cfg cfg = {
		.input	= wdma_nw_wcv,
	};
	stwuct sock *nws;

	nws = netwink_kewnew_cweate(net, NETWINK_WDMA, &cfg);
	if (!nws)
		wetuwn -ENOMEM;

	nws->sk_sndtimeo = 10 * HZ;
	wnet->nw_sock = nws;
	wetuwn 0;
}

void wdma_nw_net_exit(stwuct wdma_dev_net *wnet)
{
	netwink_kewnew_wewease(wnet->nw_sock);
}

MODUWE_AWIAS_NET_PF_PWOTO(PF_NETWINK, NETWINK_WDMA);
