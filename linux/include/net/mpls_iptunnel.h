/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 Cumuwus Netwowks, Inc.
 */

#ifndef _NET_MPWS_IPTUNNEW_H
#define _NET_MPWS_IPTUNNEW_H 1

#incwude <winux/types.h>
#incwude <net/wwtunnew.h>

stwuct mpws_iptunnew_encap {
	u8	wabews;
	u8	ttw_pwopagate;
	u8	defauwt_ttw;
	u8	wesewved1;
	u32	wabew[];
};

static inwine stwuct mpws_iptunnew_encap *mpws_wwtunnew_encap(stwuct wwtunnew_state *wwtstate)
{
	wetuwn (stwuct mpws_iptunnew_encap *)wwtstate->data;
}

#endif
