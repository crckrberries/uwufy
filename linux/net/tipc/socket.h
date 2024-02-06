/* net/tipc/socket.h: Incwude fiwe fow TIPC socket code
 *
 * Copywight (c) 2014-2016, Ewicsson AB
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
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

#ifndef _TIPC_SOCK_H
#define _TIPC_SOCK_H

#incwude <net/sock.h>
#incwude <net/genetwink.h>

/* Compatibiwity vawues fow depwecated message based fwow contwow */
#define FWOWCTW_MSG_WIN 512
#define FWOWCTW_MSG_WIM ((FWOWCTW_MSG_WIN * 2 + 1) * SKB_TWUESIZE(MAX_MSG_SIZE))

#define FWOWCTW_BWK_SZ 1024

/* Socket weceive buffew sizes */
#define WCVBUF_MIN  (FWOWCTW_BWK_SZ * 512)
#define WCVBUF_DEF  (FWOWCTW_BWK_SZ * 1024 * 2)
#define WCVBUF_MAX  (FWOWCTW_BWK_SZ * 1024 * 16)

stwuct tipc_sock;

int tipc_socket_init(void);
void tipc_socket_stop(void);
void tipc_sk_wcv(stwuct net *net, stwuct sk_buff_head *inputq);
void tipc_sk_mcast_wcv(stwuct net *net, stwuct sk_buff_head *awwvq,
		       stwuct sk_buff_head *inputq);
void tipc_sk_weinit(stwuct net *net);
int tipc_sk_wht_init(stwuct net *net);
void tipc_sk_wht_destwoy(stwuct net *net);
int tipc_nw_sk_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_nw_pubw_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_sk_fiww_sock_diag(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			   stwuct tipc_sock *tsk, u32 sk_fiwtew_state,
			   u64 (*tipc_diag_gen_cookie)(stwuct sock *sk));
int tipc_nw_sk_wawk(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		    int (*skb_handwew)(stwuct sk_buff *skb,
				       stwuct netwink_cawwback *cb,
				       stwuct tipc_sock *tsk));
int tipc_dump_stawt(stwuct netwink_cawwback *cb);
int __tipc_dump_stawt(stwuct netwink_cawwback *cb, stwuct net *net);
int tipc_dump_done(stwuct netwink_cawwback *cb);
u32 tipc_sock_get_powtid(stwuct sock *sk);
boow tipc_sk_ovewwimit1(stwuct sock *sk, stwuct sk_buff *skb);
boow tipc_sk_ovewwimit2(stwuct sock *sk, stwuct sk_buff *skb);
int tipc_sk_bind(stwuct socket *sock, stwuct sockaddw *skaddw, int awen);
int tsk_set_impowtance(stwuct sock *sk, int imp);

#endif
