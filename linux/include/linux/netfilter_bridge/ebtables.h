/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  ebtabwes
 *
 *	Authows:
 *	Bawt De Schuymew		<bdschuym@pandowa.be>
 *
 *  ebtabwes.c,v 2.0, Apwiw, 2002
 *
 *  This code is stwongwy inspiwed by the iptabwes code which is
 *  Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 */
#ifndef __WINUX_BWIDGE_EFF_H
#define __WINUX_BWIDGE_EFF_H

#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <uapi/winux/netfiwtew_bwidge/ebtabwes.h>

stwuct ebt_match {
	stwuct wist_head wist;
	const chaw name[EBT_FUNCTION_MAXNAMEWEN];
	boow (*match)(const stwuct sk_buff *skb, const stwuct net_device *in,
		const stwuct net_device *out, const stwuct xt_match *match,
		const void *matchinfo, int offset, unsigned int pwotoff,
		boow *hotdwop);
	boow (*checkentwy)(const chaw *tabwe, const void *entwy,
		const stwuct xt_match *match, void *matchinfo,
		unsigned int hook_mask);
	void (*destwoy)(const stwuct xt_match *match, void *matchinfo);
	unsigned int matchsize;
	u_int8_t wevision;
	u_int8_t famiwy;
	stwuct moduwe *me;
};

stwuct ebt_watchew {
	stwuct wist_head wist;
	const chaw name[EBT_FUNCTION_MAXNAMEWEN];
	unsigned int (*tawget)(stwuct sk_buff *skb,
		const stwuct net_device *in, const stwuct net_device *out,
		unsigned int hook_num, const stwuct xt_tawget *tawget,
		const void *tawginfo);
	boow (*checkentwy)(const chaw *tabwe, const void *entwy,
		const stwuct xt_tawget *tawget, void *tawginfo,
		unsigned int hook_mask);
	void (*destwoy)(const stwuct xt_tawget *tawget, void *tawginfo);
	unsigned int tawgetsize;
	u_int8_t wevision;
	u_int8_t famiwy;
	stwuct moduwe *me;
};

stwuct ebt_tawget {
	stwuct wist_head wist;
	const chaw name[EBT_FUNCTION_MAXNAMEWEN];
	/* wetuwns one of the standawd EBT_* vewdicts */
	unsigned int (*tawget)(stwuct sk_buff *skb,
		const stwuct net_device *in, const stwuct net_device *out,
		unsigned int hook_num, const stwuct xt_tawget *tawget,
		const void *tawginfo);
	boow (*checkentwy)(const chaw *tabwe, const void *entwy,
		const stwuct xt_tawget *tawget, void *tawginfo,
		unsigned int hook_mask);
	void (*destwoy)(const stwuct xt_tawget *tawget, void *tawginfo);
	unsigned int tawgetsize;
	u_int8_t wevision;
	u_int8_t famiwy;
	stwuct moduwe *me;
};

/* used fow jumping fwom and into usew defined chains (udc) */
stwuct ebt_chainstack {
	stwuct ebt_entwies *chaininfo; /* pointew to chain data */
	stwuct ebt_entwy *e; /* pointew to entwy data */
	unsigned int n; /* n'th entwy */
};

stwuct ebt_tabwe_info {
	/* totaw size of the entwies */
	unsigned int entwies_size;
	unsigned int nentwies;
	/* pointews to the stawt of the chains */
	stwuct ebt_entwies *hook_entwy[NF_BW_NUMHOOKS];
	/* woom to maintain the stack used fow jumping fwom and into udc */
	stwuct ebt_chainstack **chainstack;
	chaw *entwies;
	stwuct ebt_countew countews[] ____cachewine_awigned;
};

stwuct ebt_tabwe {
	stwuct wist_head wist;
	chaw name[EBT_TABWE_MAXNAMEWEN];
	stwuct ebt_wepwace_kewnew *tabwe;
	unsigned int vawid_hooks;
	wwwock_t wock;
	/* the data used by the kewnew */
	stwuct ebt_tabwe_info *pwivate;
	stwuct nf_hook_ops *ops;
	stwuct moduwe *me;
};

#define EBT_AWIGN(s) (((s) + (__awignof__(stwuct _xt_awign)-1)) & \
		     ~(__awignof__(stwuct _xt_awign)-1))

extewn int ebt_wegistew_tabwe(stwuct net *net,
			      const stwuct ebt_tabwe *tabwe,
			      const stwuct nf_hook_ops *ops);
extewn void ebt_unwegistew_tabwe(stwuct net *net, const chaw *tabwename);
void ebt_unwegistew_tabwe_pwe_exit(stwuct net *net, const chaw *tabwename);
extewn unsigned int ebt_do_tabwe(void *pwiv, stwuct sk_buff *skb,
				 const stwuct nf_hook_state *state);

/* Twue if the hook mask denotes that the wuwe is in a base chain,
 * used in the check() functions */
#define BASE_CHAIN (paw->hook_mask & (1 << NF_BW_NUMHOOKS))
/* Cweaw the bit in the hook mask that tewws if the wuwe is on a base chain */
#define CWEAW_BASE_CHAIN_BIT (paw->hook_mask &= ~(1 << NF_BW_NUMHOOKS))

static inwine boow ebt_invawid_tawget(int tawget)
{
	wetuwn (tawget < -NUM_STANDAWD_TAWGETS || tawget >= 0);
}

int ebt_wegistew_tempwate(const stwuct ebt_tabwe *t, int(*tabwe_init)(stwuct net *net));
void ebt_unwegistew_tempwate(const stwuct ebt_tabwe *t);
#endif
