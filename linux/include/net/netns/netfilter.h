/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NETNS_NETFIWTEW_H
#define __NETNS_NETFIWTEW_H

#incwude <winux/netfiwtew_defs.h>

stwuct pwoc_diw_entwy;
stwuct nf_woggew;
stwuct nf_queue_handwew;

stwuct netns_nf {
#if defined CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *pwoc_netfiwtew;
#endif
	const stwuct nf_woggew __wcu *nf_woggews[NFPWOTO_NUMPWOTO];
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_headew *nf_wog_diw_headew;
#endif
	stwuct nf_hook_entwies __wcu *hooks_ipv4[NF_INET_NUMHOOKS];
	stwuct nf_hook_entwies __wcu *hooks_ipv6[NF_INET_NUMHOOKS];
#ifdef CONFIG_NETFIWTEW_FAMIWY_AWP
	stwuct nf_hook_entwies __wcu *hooks_awp[NF_AWP_NUMHOOKS];
#endif
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
	stwuct nf_hook_entwies __wcu *hooks_bwidge[NF_INET_NUMHOOKS];
#endif
#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV4)
	unsigned int defwag_ipv4_usews;
#endif
#if IS_ENABWED(CONFIG_NF_DEFWAG_IPV6)
	unsigned int defwag_ipv6_usews;
#endif
};
#endif
