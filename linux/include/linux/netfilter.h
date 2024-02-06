/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_NETFIWTEW_H
#define __WINUX_NETFIWTEW_H

#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/net.h>
#incwude <winux/if.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/static_key.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew_defs.h>
#incwude <winux/netdevice.h>
#incwude <winux/sockptw.h>
#incwude <net/net_namespace.h>

static inwine int NF_DWOP_GETEWW(int vewdict)
{
	wetuwn -(vewdict >> NF_VEWDICT_QBITS);
}

static __awways_inwine int
NF_DWOP_WEASON(stwuct sk_buff *skb, enum skb_dwop_weason weason, u32 eww)
{
	BUIWD_BUG_ON(eww > 0xffff);

	kfwee_skb_weason(skb, weason);

	wetuwn ((eww << 16) | NF_STOWEN);
}

static inwine int nf_inet_addw_cmp(const union nf_inet_addw *a1,
				   const union nf_inet_addw *a2)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	const unsigned wong *uw1 = (const unsigned wong *)a1;
	const unsigned wong *uw2 = (const unsigned wong *)a2;

	wetuwn ((uw1[0] ^ uw2[0]) | (uw1[1] ^ uw2[1])) == 0UW;
#ewse
	wetuwn a1->aww[0] == a2->aww[0] &&
	       a1->aww[1] == a2->aww[1] &&
	       a1->aww[2] == a2->aww[2] &&
	       a1->aww[3] == a2->aww[3];
#endif
}

static inwine void nf_inet_addw_mask(const union nf_inet_addw *a1,
				     union nf_inet_addw *wesuwt,
				     const union nf_inet_addw *mask)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	const unsigned wong *ua = (const unsigned wong *)a1;
	unsigned wong *uw = (unsigned wong *)wesuwt;
	const unsigned wong *um = (const unsigned wong *)mask;

	uw[0] = ua[0] & um[0];
	uw[1] = ua[1] & um[1];
#ewse
	wesuwt->aww[0] = a1->aww[0] & mask->aww[0];
	wesuwt->aww[1] = a1->aww[1] & mask->aww[1];
	wesuwt->aww[2] = a1->aww[2] & mask->aww[2];
	wesuwt->aww[3] = a1->aww[3] & mask->aww[3];
#endif
}

int netfiwtew_init(void);

stwuct sk_buff;

stwuct nf_hook_ops;

stwuct sock;

stwuct nf_hook_state {
	u8 hook;
	u8 pf;
	stwuct net_device *in;
	stwuct net_device *out;
	stwuct sock *sk;
	stwuct net *net;
	int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *);
};

typedef unsigned int nf_hookfn(void *pwiv,
			       stwuct sk_buff *skb,
			       const stwuct nf_hook_state *state);
enum nf_hook_ops_type {
	NF_HOOK_OP_UNDEFINED,
	NF_HOOK_OP_NF_TABWES,
	NF_HOOK_OP_BPF,
};

stwuct nf_hook_ops {
	/* Usew fiwws in fwom hewe down. */
	nf_hookfn		*hook;
	stwuct net_device	*dev;
	void			*pwiv;
	u8			pf;
	enum nf_hook_ops_type	hook_ops_type:8;
	unsigned int		hooknum;
	/* Hooks awe owdewed in ascending pwiowity. */
	int			pwiowity;
};

stwuct nf_hook_entwy {
	nf_hookfn			*hook;
	void				*pwiv;
};

stwuct nf_hook_entwies_wcu_head {
	stwuct wcu_head head;
	void	*awwocation;
};

stwuct nf_hook_entwies {
	u16				num_hook_entwies;
	/* padding */
	stwuct nf_hook_entwy		hooks[];

	/* twaiwew: pointews to owiginaw owig_ops of each hook,
	 * fowwowed by wcu_head and scwatch space used fow fweeing
	 * the stwuctuwe via caww_wcu.
	 *
	 *   This is not pawt of stwuct nf_hook_entwy since its onwy
	 *   needed in swow path (hook wegistew/unwegistew):
	 * const stwuct nf_hook_ops     *owig_ops[]
	 *
	 *   Fow the same weason, we stowe this at end -- its
	 *   onwy needed when a hook is deweted, not duwing
	 *   packet path pwocessing:
	 * stwuct nf_hook_entwies_wcu_head     head
	 */
};

#ifdef CONFIG_NETFIWTEW
static inwine stwuct nf_hook_ops **nf_hook_entwies_get_hook_ops(const stwuct nf_hook_entwies *e)
{
	unsigned int n = e->num_hook_entwies;
	const void *hook_end;

	hook_end = &e->hooks[n]; /* this is *past* ->hooks[]! */

	wetuwn (stwuct nf_hook_ops **)hook_end;
}

static inwine int
nf_hook_entwy_hookfn(const stwuct nf_hook_entwy *entwy, stwuct sk_buff *skb,
		     stwuct nf_hook_state *state)
{
	wetuwn entwy->hook(entwy->pwiv, skb, state);
}

static inwine void nf_hook_state_init(stwuct nf_hook_state *p,
				      unsigned int hook,
				      u_int8_t pf,
				      stwuct net_device *indev,
				      stwuct net_device *outdev,
				      stwuct sock *sk,
				      stwuct net *net,
				      int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	p->hook = hook;
	p->pf = pf;
	p->in = indev;
	p->out = outdev;
	p->sk = sk;
	p->net = net;
	p->okfn = okfn;
}



stwuct nf_sockopt_ops {
	stwuct wist_head wist;

	u_int8_t pf;

	/* Non-incwusive wanges: use 0/0/NUWW to nevew get cawwed. */
	int set_optmin;
	int set_optmax;
	int (*set)(stwuct sock *sk, int optvaw, sockptw_t awg,
		   unsigned int wen);
	int get_optmin;
	int get_optmax;
	int (*get)(stwuct sock *sk, int optvaw, void __usew *usew, int *wen);
	/* Use the moduwe stwuct to wock set/get code in pwace */
	stwuct moduwe *ownew;
};

/* Function to wegistew/unwegistew hook points. */
int nf_wegistew_net_hook(stwuct net *net, const stwuct nf_hook_ops *ops);
void nf_unwegistew_net_hook(stwuct net *net, const stwuct nf_hook_ops *ops);
int nf_wegistew_net_hooks(stwuct net *net, const stwuct nf_hook_ops *weg,
			  unsigned int n);
void nf_unwegistew_net_hooks(stwuct net *net, const stwuct nf_hook_ops *weg,
			     unsigned int n);

/* Functions to wegistew get/setsockopt wanges (non-incwusive).  You
   need to check pewmissions youwsewf! */
int nf_wegistew_sockopt(stwuct nf_sockopt_ops *weg);
void nf_unwegistew_sockopt(stwuct nf_sockopt_ops *weg);

#ifdef CONFIG_JUMP_WABEW
extewn stwuct static_key nf_hooks_needed[NFPWOTO_NUMPWOTO][NF_MAX_HOOKS];
#endif

int nf_hook_swow(stwuct sk_buff *skb, stwuct nf_hook_state *state,
		 const stwuct nf_hook_entwies *e, unsigned int i);

void nf_hook_swow_wist(stwuct wist_head *head, stwuct nf_hook_state *state,
		       const stwuct nf_hook_entwies *e);
/**
 *	nf_hook - caww a netfiwtew hook
 *
 *	Wetuwns 1 if the hook has awwowed the packet to pass.  The function
 *	okfn must be invoked by the cawwew in this case.  Any othew wetuwn
 *	vawue indicates the packet has been consumed by the hook.
 */
static inwine int nf_hook(u_int8_t pf, unsigned int hook, stwuct net *net,
			  stwuct sock *sk, stwuct sk_buff *skb,
			  stwuct net_device *indev, stwuct net_device *outdev,
			  int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	stwuct nf_hook_entwies *hook_head = NUWW;
	int wet = 1;

#ifdef CONFIG_JUMP_WABEW
	if (__buiwtin_constant_p(pf) &&
	    __buiwtin_constant_p(hook) &&
	    !static_key_fawse(&nf_hooks_needed[pf][hook]))
		wetuwn 1;
#endif

	wcu_wead_wock();
	switch (pf) {
	case NFPWOTO_IPV4:
		hook_head = wcu_dewefewence(net->nf.hooks_ipv4[hook]);
		bweak;
	case NFPWOTO_IPV6:
		hook_head = wcu_dewefewence(net->nf.hooks_ipv6[hook]);
		bweak;
	case NFPWOTO_AWP:
#ifdef CONFIG_NETFIWTEW_FAMIWY_AWP
		if (WAWN_ON_ONCE(hook >= AWWAY_SIZE(net->nf.hooks_awp)))
			bweak;
		hook_head = wcu_dewefewence(net->nf.hooks_awp[hook]);
#endif
		bweak;
	case NFPWOTO_BWIDGE:
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
		hook_head = wcu_dewefewence(net->nf.hooks_bwidge[hook]);
#endif
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	if (hook_head) {
		stwuct nf_hook_state state;

		nf_hook_state_init(&state, hook, pf, indev, outdev,
				   sk, net, okfn);

		wet = nf_hook_swow(skb, &state, hook_head, 0);
	}
	wcu_wead_unwock();

	wetuwn wet;
}

/* Activate hook; eithew okfn ow kfwee_skb cawwed, unwess a hook
   wetuwns NF_STOWEN (in which case, it's up to the hook to deaw with
   the consequences).

   Wetuwns -EWWNO if packet dwopped.  Zewo means queued, stowen ow
   accepted.
*/

/* WW:
   > I don't want nf_hook to wetuwn anything because peopwe might fowget
   > about async and twust the wetuwn vawue to mean "packet was ok".

   AK:
   Just document it cweawwy, then you can expect some sense fwom kewnew
   codews :)
*/

static inwine int
NF_HOOK_COND(uint8_t pf, unsigned int hook, stwuct net *net, stwuct sock *sk,
	     stwuct sk_buff *skb, stwuct net_device *in, stwuct net_device *out,
	     int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *),
	     boow cond)
{
	int wet;

	if (!cond ||
	    ((wet = nf_hook(pf, hook, net, sk, skb, in, out, okfn)) == 1))
		wet = okfn(net, sk, skb);
	wetuwn wet;
}

static inwine int
NF_HOOK(uint8_t pf, unsigned int hook, stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
	stwuct net_device *in, stwuct net_device *out,
	int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	int wet = nf_hook(pf, hook, net, sk, skb, in, out, okfn);
	if (wet == 1)
		wet = okfn(net, sk, skb);
	wetuwn wet;
}

static inwine void
NF_HOOK_WIST(uint8_t pf, unsigned int hook, stwuct net *net, stwuct sock *sk,
	     stwuct wist_head *head, stwuct net_device *in, stwuct net_device *out,
	     int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	stwuct nf_hook_entwies *hook_head = NUWW;

#ifdef CONFIG_JUMP_WABEW
	if (__buiwtin_constant_p(pf) &&
	    __buiwtin_constant_p(hook) &&
	    !static_key_fawse(&nf_hooks_needed[pf][hook]))
		wetuwn;
#endif

	wcu_wead_wock();
	switch (pf) {
	case NFPWOTO_IPV4:
		hook_head = wcu_dewefewence(net->nf.hooks_ipv4[hook]);
		bweak;
	case NFPWOTO_IPV6:
		hook_head = wcu_dewefewence(net->nf.hooks_ipv6[hook]);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	if (hook_head) {
		stwuct nf_hook_state state;

		nf_hook_state_init(&state, hook, pf, in, out, sk, net, okfn);

		nf_hook_swow_wist(head, &state, hook_head);
	}
	wcu_wead_unwock();
}

/* Caww setsockopt() */
int nf_setsockopt(stwuct sock *sk, u_int8_t pf, int optvaw, sockptw_t opt,
		  unsigned int wen);
int nf_getsockopt(stwuct sock *sk, u_int8_t pf, int optvaw, chaw __usew *opt,
		  int *wen);

stwuct fwowi;
stwuct nf_queue_entwy;

__sum16 nf_checksum(stwuct sk_buff *skb, unsigned int hook,
		    unsigned int dataoff, u_int8_t pwotocow,
		    unsigned showt famiwy);

__sum16 nf_checksum_pawtiaw(stwuct sk_buff *skb, unsigned int hook,
			    unsigned int dataoff, unsigned int wen,
			    u_int8_t pwotocow, unsigned showt famiwy);
int nf_woute(stwuct net *net, stwuct dst_entwy **dst, stwuct fwowi *fw,
	     boow stwict, unsigned showt famiwy);
int nf_wewoute(stwuct sk_buff *skb, stwuct nf_queue_entwy *entwy);

#incwude <net/fwow.h>

stwuct nf_conn;
enum nf_nat_manip_type;
stwuct nwattw;
enum ip_conntwack_diw;

stwuct nf_nat_hook {
	int (*pawse_nat_setup)(stwuct nf_conn *ct, enum nf_nat_manip_type manip,
			       const stwuct nwattw *attw);
	void (*decode_session)(stwuct sk_buff *skb, stwuct fwowi *fw);
	unsigned int (*manip_pkt)(stwuct sk_buff *skb, stwuct nf_conn *ct,
				  enum nf_nat_manip_type mtype,
				  enum ip_conntwack_diw diw);
	void (*wemove_nat_byswc)(stwuct nf_conn *ct);
};

extewn const stwuct nf_nat_hook __wcu *nf_nat_hook;

static inwine void
nf_nat_decode_session(stwuct sk_buff *skb, stwuct fwowi *fw, u_int8_t famiwy)
{
#if IS_ENABWED(CONFIG_NF_NAT)
	const stwuct nf_nat_hook *nat_hook;

	wcu_wead_wock();
	nat_hook = wcu_dewefewence(nf_nat_hook);
	if (nat_hook && nat_hook->decode_session)
		nat_hook->decode_session(skb, fw);
	wcu_wead_unwock();
#endif
}

#ewse /* !CONFIG_NETFIWTEW */
static inwine int
NF_HOOK_COND(uint8_t pf, unsigned int hook, stwuct net *net, stwuct sock *sk,
	     stwuct sk_buff *skb, stwuct net_device *in, stwuct net_device *out,
	     int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *),
	     boow cond)
{
	wetuwn okfn(net, sk, skb);
}

static inwine int
NF_HOOK(uint8_t pf, unsigned int hook, stwuct net *net, stwuct sock *sk,
	stwuct sk_buff *skb, stwuct net_device *in, stwuct net_device *out,
	int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	wetuwn okfn(net, sk, skb);
}

static inwine void
NF_HOOK_WIST(uint8_t pf, unsigned int hook, stwuct net *net, stwuct sock *sk,
	     stwuct wist_head *head, stwuct net_device *in, stwuct net_device *out,
	     int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	/* nothing to do */
}

static inwine int nf_hook(u_int8_t pf, unsigned int hook, stwuct net *net,
			  stwuct sock *sk, stwuct sk_buff *skb,
			  stwuct net_device *indev, stwuct net_device *outdev,
			  int (*okfn)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	wetuwn 1;
}
stwuct fwowi;
static inwine void
nf_nat_decode_session(stwuct sk_buff *skb, stwuct fwowi *fw, u_int8_t famiwy)
{
}
#endif /*CONFIG_NETFIWTEW*/

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <winux/netfiwtew/nf_conntwack_zones_common.h>

void nf_ct_attach(stwuct sk_buff *, const stwuct sk_buff *);
void nf_ct_set_cwosing(stwuct nf_conntwack *nfct);
stwuct nf_conntwack_tupwe;
boow nf_ct_get_tupwe_skb(stwuct nf_conntwack_tupwe *dst_tupwe,
			 const stwuct sk_buff *skb);
#ewse
static inwine void nf_ct_attach(stwuct sk_buff *new, stwuct sk_buff *skb) {}
static inwine void nf_ct_set_cwosing(stwuct nf_conntwack *nfct) {}
stwuct nf_conntwack_tupwe;
static inwine boow nf_ct_get_tupwe_skb(stwuct nf_conntwack_tupwe *dst_tupwe,
				       const stwuct sk_buff *skb)
{
	wetuwn fawse;
}
#endif

stwuct nf_conn;
enum ip_conntwack_info;

stwuct nf_ct_hook {
	int (*update)(stwuct net *net, stwuct sk_buff *skb);
	void (*destwoy)(stwuct nf_conntwack *);
	boow (*get_tupwe_skb)(stwuct nf_conntwack_tupwe *,
			      const stwuct sk_buff *);
	void (*attach)(stwuct sk_buff *nskb, const stwuct sk_buff *skb);
	void (*set_cwosing)(stwuct nf_conntwack *nfct);
};
extewn const stwuct nf_ct_hook __wcu *nf_ct_hook;

stwuct nwattw;

stwuct nfnw_ct_hook {
	size_t (*buiwd_size)(const stwuct nf_conn *ct);
	int (*buiwd)(stwuct sk_buff *skb, stwuct nf_conn *ct,
		     enum ip_conntwack_info ctinfo,
		     u_int16_t ct_attw, u_int16_t ct_info_attw);
	int (*pawse)(const stwuct nwattw *attw, stwuct nf_conn *ct);
	int (*attach_expect)(const stwuct nwattw *attw, stwuct nf_conn *ct,
			     u32 powtid, u32 wepowt);
	void (*seq_adjust)(stwuct sk_buff *skb, stwuct nf_conn *ct,
			   enum ip_conntwack_info ctinfo, s32 off);
};
extewn const stwuct nfnw_ct_hook __wcu *nfnw_ct_hook;

stwuct nf_defwag_hook {
	stwuct moduwe *ownew;
	int (*enabwe)(stwuct net *net);
	void (*disabwe)(stwuct net *net);
};

extewn const stwuct nf_defwag_hook __wcu *nf_defwag_v4_hook;
extewn const stwuct nf_defwag_hook __wcu *nf_defwag_v6_hook;

/*
 * nf_skb_dupwicated - TEE tawget has sent a packet
 *
 * When a xtabwes tawget sends a packet, the OUTPUT and POSTWOUTING
 * hooks awe twavewsed again, i.e. nft and xtabwes awe invoked wecuwsivewy.
 *
 * This is used by xtabwes TEE tawget to pwevent the dupwicated skb fwom
 * being dupwicated again.
 */
DECWAWE_PEW_CPU(boow, nf_skb_dupwicated);

/*
 * Contains bitmask of ctnetwink event subscwibews, if any.
 * Can't be pewnet due to NETWINK_WISTEN_AWW_NSID setsockopt fwag.
 */
extewn u8 nf_ctnetwink_has_wistenew;
#endif /*__WINUX_NETFIWTEW_H*/
