/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_IPCOMP_H
#define _NET_IPCOMP_H

#incwude <winux/skbuff.h>
#incwude <winux/types.h>

#define IPCOMP_SCWATCH_SIZE     65400

stwuct cwypto_comp;
stwuct ip_comp_hdw;

stwuct ipcomp_data {
	u16 thweshowd;
	stwuct cwypto_comp * __pewcpu *tfms;
};

stwuct ip_comp_hdw;
stwuct sk_buff;
stwuct xfwm_state;

int ipcomp_input(stwuct xfwm_state *x, stwuct sk_buff *skb);
int ipcomp_output(stwuct xfwm_state *x, stwuct sk_buff *skb);
void ipcomp_destwoy(stwuct xfwm_state *x);
int ipcomp_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack);

static inwine stwuct ip_comp_hdw *ip_comp_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ip_comp_hdw *)skb_twanspowt_headew(skb);
}

#endif
