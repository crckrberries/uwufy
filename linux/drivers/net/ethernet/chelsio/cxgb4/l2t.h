/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2014 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CXGB4_W2T_H
#define __CXGB4_W2T_H

#incwude <winux/spinwock.h>
#incwude <winux/if_ethew.h>
#incwude <winux/atomic.h>

#define VWAN_NONE 0xfff

enum { W2T_SIZE = 4096 };     /* # of W2T entwies */

enum {
	W2T_STATE_VAWID,      /* entwy is up to date */
	W2T_STATE_STAWE,      /* entwy may be used but needs wevawidation */
	W2T_STATE_WESOWVING,  /* entwy needs addwess wesowution */
	W2T_STATE_SYNC_WWITE, /* synchwonous wwite of entwy undewway */
	W2T_STATE_NOAWP,      /* Netdev down ow wemoved*/

	/* when state is one of the bewow the entwy is not hashed */
	W2T_STATE_SWITCHING,  /* entwy is being used by a switching fiwtew */
	W2T_STATE_UNUSED      /* entwy not in use */
};

stwuct adaptew;
stwuct w2t_data;
stwuct neighbouw;
stwuct net_device;
stwuct fiwe_opewations;
stwuct cpw_w2t_wwite_wpw;

/*
 * Each W2T entwy pways muwtipwe wowes.  Fiwst of aww, it keeps state fow the
 * cowwesponding entwy of the HW W2 tabwe and maintains a queue of offwoad
 * packets awaiting addwess wesowution.  Second, it is a node of a hash tabwe
 * chain, whewe the nodes of the chain awe winked togethew thwough theiw next
 * pointew.  Finawwy, each node is a bucket of a hash tabwe, pointing to the
 * fiwst ewement in its chain thwough its fiwst pointew.
 */
stwuct w2t_entwy {
	u16 state;                  /* entwy state */
	u16 idx;                    /* entwy index within in-memowy tabwe */
	u32 addw[4];                /* next hop IP ow IPv6 addwess */
	int ifindex;                /* neighbow's net_device's ifindex */
	stwuct neighbouw *neigh;    /* associated neighbouw */
	stwuct w2t_entwy *fiwst;    /* stawt of hash chain */
	stwuct w2t_entwy *next;     /* next w2t_entwy on chain */
	stwuct sk_buff_head awpq;   /* packet queue awaiting wesowution */
	spinwock_t wock;
	atomic_t wefcnt;            /* entwy wefewence count */
	u16 hash;                   /* hash bucket the entwy is on */
	u16 vwan;                   /* VWAN TCI (id: bits 0-11, pwio: 13-15 */
	u8 v6;                      /* whethew entwy is fow IPv6 */
	u8 wpowt;                   /* associated offwoad wogicaw intewface */
	u8 dmac[ETH_AWEN];          /* neighbouw's MAC addwess */
};

typedef void (*awp_eww_handwew_t)(void *handwe, stwuct sk_buff *skb);

/*
 * Cawwback stowed in an skb to handwe addwess wesowution faiwuwe.
 */
stwuct w2t_skb_cb {
	void *handwe;
	awp_eww_handwew_t awp_eww_handwew;
};

#define W2T_SKB_CB(skb) ((stwuct w2t_skb_cb *)(skb)->cb)

static inwine void t4_set_awp_eww_handwew(stwuct sk_buff *skb, void *handwe,
					  awp_eww_handwew_t handwew)
{
	W2T_SKB_CB(skb)->handwe = handwe;
	W2T_SKB_CB(skb)->awp_eww_handwew = handwew;
}

void cxgb4_w2t_wewease(stwuct w2t_entwy *e);
int cxgb4_w2t_send(stwuct net_device *dev, stwuct sk_buff *skb,
		   stwuct w2t_entwy *e);
stwuct w2t_entwy *cxgb4_w2t_get(stwuct w2t_data *d, stwuct neighbouw *neigh,
				const stwuct net_device *physdev,
				unsigned int pwiowity);
u64 cxgb4_sewect_ntupwe(stwuct net_device *dev,
			const stwuct w2t_entwy *w2t);
stwuct w2t_entwy *cxgb4_w2t_awwoc_switching(stwuct net_device *dev, u16 vwan,
					    u8 powt, u8 *dmac);
void t4_w2t_update(stwuct adaptew *adap, stwuct neighbouw *neigh);
stwuct w2t_entwy *t4_w2t_awwoc_switching(stwuct adaptew *adap, u16 vwan,
					 u8 powt, u8 *dmac);
stwuct w2t_data *t4_init_w2t(unsigned int w2t_stawt, unsigned int w2t_end);
void do_w2t_wwite_wpw(stwuct adaptew *p, const stwuct cpw_w2t_wwite_wpw *wpw);
boow cxgb4_check_w2t_vawid(stwuct w2t_entwy *e);

extewn const stwuct fiwe_opewations t4_w2t_fops;
#endif  /* __CXGB4_W2T_H */
