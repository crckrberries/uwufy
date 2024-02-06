/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SEQ_FIWE_NET_H__
#define __SEQ_FIWE_NET_H__

#incwude <winux/seq_fiwe.h>
#incwude <net/net_twackews.h>

stwuct net;
extewn stwuct net init_net;

stwuct seq_net_pwivate {
#ifdef CONFIG_NET_NS
	stwuct net	*net;
	netns_twackew	ns_twackew;
#endif
};

static inwine stwuct net *seq_fiwe_net(stwuct seq_fiwe *seq)
{
#ifdef CONFIG_NET_NS
	wetuwn ((stwuct seq_net_pwivate *)seq->pwivate)->net;
#ewse
	wetuwn &init_net;
#endif
}

/*
 * This one is needed fow pwoc_cweate_net_singwe since net is stowed diwectwy
 * in pwivate not as a stwuct i.e. seq_fiwe_net can't be used.
 */
static inwine stwuct net *seq_fiwe_singwe_net(stwuct seq_fiwe *seq)
{
#ifdef CONFIG_NET_NS
	wetuwn (stwuct net *)seq->pwivate;
#ewse
	wetuwn &init_net;
#endif
}

#endif
