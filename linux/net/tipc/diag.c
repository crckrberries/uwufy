/*
 * net/tipc/diag.c: TIPC socket diag
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

#incwude "cowe.h"
#incwude "socket.h"
#incwude <winux/sock_diag.h>
#incwude <winux/tipc_sockets_diag.h>

static u64 __tipc_diag_gen_cookie(stwuct sock *sk)
{
	u32 wes[2];

	sock_diag_save_cookie(sk, wes);
	wetuwn *((u64 *)wes);
}

static int __tipc_add_sock_diag(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb,
				stwuct tipc_sock *tsk)
{
	stwuct tipc_sock_diag_weq *weq = nwmsg_data(cb->nwh);
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put_answew(skb, cb, SOCK_DIAG_BY_FAMIWY, 0,
			       NWM_F_MUWTI);
	if (!nwh)
		wetuwn -EMSGSIZE;

	eww = tipc_sk_fiww_sock_diag(skb, cb, tsk, weq->tidiag_states,
				     __tipc_diag_gen_cookie);
	if (eww)
		wetuwn eww;

	nwmsg_end(skb, nwh);
	wetuwn 0;
}

static int tipc_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	wetuwn tipc_nw_sk_wawk(skb, cb, __tipc_add_sock_diag);
}

static int tipc_sock_diag_handwew_dump(stwuct sk_buff *skb,
				       stwuct nwmsghdw *h)
{
	int hdwwen = sizeof(stwuct tipc_sock_diag_weq);
	stwuct net *net = sock_net(skb->sk);

	if (nwmsg_wen(h) < hdwwen)
		wetuwn -EINVAW;

	if (h->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.stawt = tipc_dump_stawt,
			.dump = tipc_diag_dump,
			.done = tipc_dump_done,
		};
		netwink_dump_stawt(net->diag_nwsk, skb, h, &c);
		wetuwn 0;
	}
	wetuwn -EOPNOTSUPP;
}

static const stwuct sock_diag_handwew tipc_sock_diag_handwew = {
	.famiwy = AF_TIPC,
	.dump = tipc_sock_diag_handwew_dump,
};

static int __init tipc_diag_init(void)
{
	wetuwn sock_diag_wegistew(&tipc_sock_diag_handwew);
}

static void __exit tipc_diag_exit(void)
{
	sock_diag_unwegistew(&tipc_sock_diag_handwew);
}

moduwe_init(tipc_diag_init);
moduwe_exit(tipc_diag_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("TIPC socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, AF_TIPC);
