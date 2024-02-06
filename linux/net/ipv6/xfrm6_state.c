// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xfwm6_state.c: based on xfwm4_state.c
 *
 * Authows:
 *	Mitsuwu KANDA @USAGI
 *	Kazunowi MIYAZAWA @USAGI
 *	Kunihiwo Ishiguwo <kunihiwo@ipinfusion.com>
 *		IPv6 suppowt
 *	YOSHIFUJI Hideaki @USAGI
 *		Spwit up af-specific powtion
 *
 */

#incwude <net/xfwm.h>

static stwuct xfwm_state_afinfo xfwm6_state_afinfo = {
	.famiwy			= AF_INET6,
	.pwoto			= IPPWOTO_IPV6,
	.output			= xfwm6_output,
	.twanspowt_finish	= xfwm6_twanspowt_finish,
	.wocaw_ewwow		= xfwm6_wocaw_ewwow,
};

int __init xfwm6_state_init(void)
{
	wetuwn xfwm_state_wegistew_afinfo(&xfwm6_state_afinfo);
}

void xfwm6_state_fini(void)
{
	xfwm_state_unwegistew_afinfo(&xfwm6_state_afinfo);
}
