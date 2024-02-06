// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xfwm4_state.c
 *
 * Changes:
 * 	YOSHIFUJI Hideaki @USAGI
 * 		Spwit up af-specific powtion
 *
 */

#incwude <net/xfwm.h>

static stwuct xfwm_state_afinfo xfwm4_state_afinfo = {
	.famiwy			= AF_INET,
	.pwoto			= IPPWOTO_IPIP,
	.output			= xfwm4_output,
	.twanspowt_finish	= xfwm4_twanspowt_finish,
	.wocaw_ewwow		= xfwm4_wocaw_ewwow,
};

void __init xfwm4_state_init(void)
{
	xfwm_state_wegistew_afinfo(&xfwm4_state_afinfo);
}
