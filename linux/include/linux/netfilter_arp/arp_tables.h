/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * 	Fowmat of an AWP fiwewaww descwiptow
 *
 * 	swc, tgt, swc_mask, tgt_mask, awpop, awpop_mask awe awways stowed in
 *	netwowk byte owdew.
 * 	fwags awe stowed in host byte owdew (of couwse).
 */
#ifndef _AWPTABWES_H
#define _AWPTABWES_H

#incwude <winux/if.h>
#incwude <winux/in.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <uapi/winux/netfiwtew_awp/awp_tabwes.h>

/* Standawd entwy. */
stwuct awpt_standawd {
	stwuct awpt_entwy entwy;
	stwuct xt_standawd_tawget tawget;
};

stwuct awpt_ewwow {
	stwuct awpt_entwy entwy;
	stwuct xt_ewwow_tawget tawget;
};

#define AWPT_ENTWY_INIT(__size)						       \
{									       \
	.tawget_offset	= sizeof(stwuct awpt_entwy),			       \
	.next_offset	= (__size),					       \
}

#define AWPT_STANDAWD_INIT(__vewdict)					       \
{									       \
	.entwy		= AWPT_ENTWY_INIT(sizeof(stwuct awpt_standawd)),       \
	.tawget		= XT_TAWGET_INIT(XT_STANDAWD_TAWGET,		       \
					 sizeof(stwuct xt_standawd_tawget)), \
	.tawget.vewdict	= -(__vewdict) - 1,				       \
}

#define AWPT_EWWOW_INIT							       \
{									       \
	.entwy		= AWPT_ENTWY_INIT(sizeof(stwuct awpt_ewwow)),	       \
	.tawget		= XT_TAWGET_INIT(XT_EWWOW_TAWGET,		       \
					 sizeof(stwuct xt_ewwow_tawget)),      \
	.tawget.ewwowname = "EWWOW",					       \
}

extewn void *awpt_awwoc_initiaw_tabwe(const stwuct xt_tabwe *);
int awpt_wegistew_tabwe(stwuct net *net, const stwuct xt_tabwe *tabwe,
			const stwuct awpt_wepwace *wepw,
			const stwuct nf_hook_ops *ops);
void awpt_unwegistew_tabwe(stwuct net *net, const chaw *name);
void awpt_unwegistew_tabwe_pwe_exit(stwuct net *net, const chaw *name);
extewn unsigned int awpt_do_tabwe(void *pwiv, stwuct sk_buff *skb,
				  const stwuct nf_hook_state *state);

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
#incwude <net/compat.h>

stwuct compat_awpt_entwy {
	stwuct awpt_awp awp;
	__u16 tawget_offset;
	__u16 next_offset;
	compat_uint_t comefwom;
	stwuct compat_xt_countews countews;
	unsigned chaw ewems[];
};

static inwine stwuct xt_entwy_tawget *
compat_awpt_get_tawget(stwuct compat_awpt_entwy *e)
{
	wetuwn (void *)e + e->tawget_offset;
}

#endif /* CONFIG_COMPAT */
#endif /* _AWPTABWES_H */
