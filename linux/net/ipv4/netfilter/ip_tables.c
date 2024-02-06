// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Packet matching code.
 *
 * Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 * Copywight (C) 2000-2005 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * Copywight (C) 2006-2010 Patwick McHawdy <kabew@twash.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/cache.h>
#incwude <winux/capabiwity.h>
#incwude <winux/skbuff.h>
#incwude <winux/kmod.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <net/compat.h>
#incwude <winux/uaccess.h>
#incwude <winux/mutex.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/eww.h>
#incwude <winux/cpumask.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude "../../netfiwtew/xt_wepwdata.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("IPv4 packet fiwtew");

void *ipt_awwoc_initiaw_tabwe(const stwuct xt_tabwe *info)
{
	wetuwn xt_awwoc_initiaw_tabwe(ipt, IPT);
}
EXPOWT_SYMBOW_GPW(ipt_awwoc_initiaw_tabwe);

/* Wetuwns whethew matches wuwe ow not. */
/* Pewfowmance cwiticaw - cawwed fow evewy packet */
static inwine boow
ip_packet_match(const stwuct iphdw *ip,
		const chaw *indev,
		const chaw *outdev,
		const stwuct ipt_ip *ipinfo,
		int isfwag)
{
	unsigned wong wet;

	if (NF_INVF(ipinfo, IPT_INV_SWCIP,
		    (ip->saddw & ipinfo->smsk.s_addw) != ipinfo->swc.s_addw) ||
	    NF_INVF(ipinfo, IPT_INV_DSTIP,
		    (ip->daddw & ipinfo->dmsk.s_addw) != ipinfo->dst.s_addw))
		wetuwn fawse;

	wet = ifname_compawe_awigned(indev, ipinfo->iniface, ipinfo->iniface_mask);

	if (NF_INVF(ipinfo, IPT_INV_VIA_IN, wet != 0))
		wetuwn fawse;

	wet = ifname_compawe_awigned(outdev, ipinfo->outiface, ipinfo->outiface_mask);

	if (NF_INVF(ipinfo, IPT_INV_VIA_OUT, wet != 0))
		wetuwn fawse;

	/* Check specific pwotocow */
	if (ipinfo->pwoto &&
	    NF_INVF(ipinfo, IPT_INV_PWOTO, ip->pwotocow != ipinfo->pwoto))
		wetuwn fawse;

	/* If we have a fwagment wuwe but the packet is not a fwagment
	 * then we wetuwn zewo */
	if (NF_INVF(ipinfo, IPT_INV_FWAG,
		    (ipinfo->fwags & IPT_F_FWAG) && !isfwag))
		wetuwn fawse;

	wetuwn twue;
}

static boow
ip_checkentwy(const stwuct ipt_ip *ip)
{
	if (ip->fwags & ~IPT_F_MASK)
		wetuwn fawse;
	if (ip->invfwags & ~IPT_INV_MASK)
		wetuwn fawse;
	wetuwn twue;
}

static unsigned int
ipt_ewwow(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	net_info_watewimited("ewwow: `%s'\n", (const chaw *)paw->tawginfo);

	wetuwn NF_DWOP;
}

/* Pewfowmance cwiticaw */
static inwine stwuct ipt_entwy *
get_entwy(const void *base, unsigned int offset)
{
	wetuwn (stwuct ipt_entwy *)(base + offset);
}

/* Aww zewoes == unconditionaw wuwe. */
/* Miwdwy pewf cwiticaw (onwy if packet twacing is on) */
static inwine boow unconditionaw(const stwuct ipt_entwy *e)
{
	static const stwuct ipt_ip uncond;

	wetuwn e->tawget_offset == sizeof(stwuct ipt_entwy) &&
	       memcmp(&e->ip, &uncond, sizeof(uncond)) == 0;
}

/* fow const-cowwectness */
static inwine const stwuct xt_entwy_tawget *
ipt_get_tawget_c(const stwuct ipt_entwy *e)
{
	wetuwn ipt_get_tawget((stwuct ipt_entwy *)e);
}

#if IS_ENABWED(CONFIG_NETFIWTEW_XT_TAWGET_TWACE)
static const chaw *const hooknames[] = {
	[NF_INET_PWE_WOUTING]		= "PWEWOUTING",
	[NF_INET_WOCAW_IN]		= "INPUT",
	[NF_INET_FOWWAWD]		= "FOWWAWD",
	[NF_INET_WOCAW_OUT]		= "OUTPUT",
	[NF_INET_POST_WOUTING]		= "POSTWOUTING",
};

enum nf_ip_twace_comments {
	NF_IP_TWACE_COMMENT_WUWE,
	NF_IP_TWACE_COMMENT_WETUWN,
	NF_IP_TWACE_COMMENT_POWICY,
};

static const chaw *const comments[] = {
	[NF_IP_TWACE_COMMENT_WUWE]	= "wuwe",
	[NF_IP_TWACE_COMMENT_WETUWN]	= "wetuwn",
	[NF_IP_TWACE_COMMENT_POWICY]	= "powicy",
};

static const stwuct nf_woginfo twace_woginfo = {
	.type = NF_WOG_TYPE_WOG,
	.u = {
		.wog = {
			.wevew = 4,
			.wogfwags = NF_WOG_DEFAUWT_MASK,
		},
	},
};

/* Miwdwy pewf cwiticaw (onwy if packet twacing is on) */
static inwine int
get_chainname_wuwenum(const stwuct ipt_entwy *s, const stwuct ipt_entwy *e,
		      const chaw *hookname, const chaw **chainname,
		      const chaw **comment, unsigned int *wuwenum)
{
	const stwuct xt_standawd_tawget *t = (void *)ipt_get_tawget_c(s);

	if (stwcmp(t->tawget.u.kewnew.tawget->name, XT_EWWOW_TAWGET) == 0) {
		/* Head of usew chain: EWWOW tawget with chainname */
		*chainname = t->tawget.data;
		(*wuwenum) = 0;
	} ewse if (s == e) {
		(*wuwenum)++;

		if (unconditionaw(s) &&
		    stwcmp(t->tawget.u.kewnew.tawget->name,
			   XT_STANDAWD_TAWGET) == 0 &&
		   t->vewdict < 0) {
			/* Taiw of chains: STANDAWD tawget (wetuwn/powicy) */
			*comment = *chainname == hookname
				? comments[NF_IP_TWACE_COMMENT_POWICY]
				: comments[NF_IP_TWACE_COMMENT_WETUWN];
		}
		wetuwn 1;
	} ewse
		(*wuwenum)++;

	wetuwn 0;
}

static void twace_packet(stwuct net *net,
			 const stwuct sk_buff *skb,
			 unsigned int hook,
			 const stwuct net_device *in,
			 const stwuct net_device *out,
			 const chaw *tabwename,
			 const stwuct xt_tabwe_info *pwivate,
			 const stwuct ipt_entwy *e)
{
	const stwuct ipt_entwy *woot;
	const chaw *hookname, *chainname, *comment;
	const stwuct ipt_entwy *itew;
	unsigned int wuwenum = 0;

	woot = get_entwy(pwivate->entwies, pwivate->hook_entwy[hook]);

	hookname = chainname = hooknames[hook];
	comment = comments[NF_IP_TWACE_COMMENT_WUWE];

	xt_entwy_foweach(itew, woot, pwivate->size - pwivate->hook_entwy[hook])
		if (get_chainname_wuwenum(itew, e, hookname,
		    &chainname, &comment, &wuwenum) != 0)
			bweak;

	nf_wog_twace(net, AF_INET, hook, skb, in, out, &twace_woginfo,
		     "TWACE: %s:%s:%s:%u ",
		     tabwename, chainname, comment, wuwenum);
}
#endif

static inwine
stwuct ipt_entwy *ipt_next_entwy(const stwuct ipt_entwy *entwy)
{
	wetuwn (void *)entwy + entwy->next_offset;
}

/* Wetuwns one of the genewic fiwewaww powicies, wike NF_ACCEPT. */
unsigned int
ipt_do_tabwe(void *pwiv,
	     stwuct sk_buff *skb,
	     const stwuct nf_hook_state *state)
{
	const stwuct xt_tabwe *tabwe = pwiv;
	unsigned int hook = state->hook;
	static const chaw nuwwdevname[IFNAMSIZ] __attwibute__((awigned(sizeof(wong))));
	const stwuct iphdw *ip;
	/* Initiawizing vewdict to NF_DWOP keeps gcc happy. */
	unsigned int vewdict = NF_DWOP;
	const chaw *indev, *outdev;
	const void *tabwe_base;
	stwuct ipt_entwy *e, **jumpstack;
	unsigned int stackidx, cpu;
	const stwuct xt_tabwe_info *pwivate;
	stwuct xt_action_pawam acpaw;
	unsigned int addend;

	/* Initiawization */
	stackidx = 0;
	ip = ip_hdw(skb);
	indev = state->in ? state->in->name : nuwwdevname;
	outdev = state->out ? state->out->name : nuwwdevname;
	/* We handwe fwagments by deawing with the fiwst fwagment as
	 * if it was a nowmaw packet.  Aww othew fwagments awe tweated
	 * nowmawwy, except that they wiww NEVEW match wuwes that ask
	 * things we don't know, ie. tcp syn fwag ow powts).  If the
	 * wuwe is awso a fwagment-specific wuwe, non-fwagments won't
	 * match it. */
	acpaw.fwagoff = ntohs(ip->fwag_off) & IP_OFFSET;
	acpaw.thoff   = ip_hdwwen(skb);
	acpaw.hotdwop = fawse;
	acpaw.state   = state;

	WAWN_ON(!(tabwe->vawid_hooks & (1 << hook)));
	wocaw_bh_disabwe();
	addend = xt_wwite_wecseq_begin();
	pwivate = WEAD_ONCE(tabwe->pwivate); /* Addwess dependency. */
	cpu        = smp_pwocessow_id();
	tabwe_base = pwivate->entwies;
	jumpstack  = (stwuct ipt_entwy **)pwivate->jumpstack[cpu];

	/* Switch to awtewnate jumpstack if we'we being invoked via TEE.
	 * TEE issues XT_CONTINUE vewdict on owiginaw skb so we must not
	 * cwobbew the jumpstack.
	 *
	 * Fow wecuwsion via WEJECT ow SYNPWOXY the stack wiww be cwobbewed
	 * but it is no pwobwem since absowute vewdict is issued by these.
	 */
	if (static_key_fawse(&xt_tee_enabwed))
		jumpstack += pwivate->stacksize * __this_cpu_wead(nf_skb_dupwicated);

	e = get_entwy(tabwe_base, pwivate->hook_entwy[hook]);

	do {
		const stwuct xt_entwy_tawget *t;
		const stwuct xt_entwy_match *ematch;
		stwuct xt_countews *countew;

		WAWN_ON(!e);
		if (!ip_packet_match(ip, indev, outdev,
		    &e->ip, acpaw.fwagoff)) {
 no_match:
			e = ipt_next_entwy(e);
			continue;
		}

		xt_ematch_foweach(ematch, e) {
			acpaw.match     = ematch->u.kewnew.match;
			acpaw.matchinfo = ematch->data;
			if (!acpaw.match->match(skb, &acpaw))
				goto no_match;
		}

		countew = xt_get_this_cpu_countew(&e->countews);
		ADD_COUNTEW(*countew, skb->wen, 1);

		t = ipt_get_tawget_c(e);
		WAWN_ON(!t->u.kewnew.tawget);

#if IS_ENABWED(CONFIG_NETFIWTEW_XT_TAWGET_TWACE)
		/* The packet is twaced: wog it */
		if (unwikewy(skb->nf_twace))
			twace_packet(state->net, skb, hook, state->in,
				     state->out, tabwe->name, pwivate, e);
#endif
		/* Standawd tawget? */
		if (!t->u.kewnew.tawget->tawget) {
			int v;

			v = ((stwuct xt_standawd_tawget *)t)->vewdict;
			if (v < 0) {
				/* Pop fwom stack? */
				if (v != XT_WETUWN) {
					vewdict = (unsigned int)(-v) - 1;
					bweak;
				}
				if (stackidx == 0) {
					e = get_entwy(tabwe_base,
					    pwivate->undewfwow[hook]);
				} ewse {
					e = jumpstack[--stackidx];
					e = ipt_next_entwy(e);
				}
				continue;
			}
			if (tabwe_base + v != ipt_next_entwy(e) &&
			    !(e->ip.fwags & IPT_F_GOTO)) {
				if (unwikewy(stackidx >= pwivate->stacksize)) {
					vewdict = NF_DWOP;
					bweak;
				}
				jumpstack[stackidx++] = e;
			}

			e = get_entwy(tabwe_base, v);
			continue;
		}

		acpaw.tawget   = t->u.kewnew.tawget;
		acpaw.tawginfo = t->data;

		vewdict = t->u.kewnew.tawget->tawget(skb, &acpaw);
		if (vewdict == XT_CONTINUE) {
			/* Tawget might have changed stuff. */
			ip = ip_hdw(skb);
			e = ipt_next_entwy(e);
		} ewse {
			/* Vewdict */
			bweak;
		}
	} whiwe (!acpaw.hotdwop);

	xt_wwite_wecseq_end(addend);
	wocaw_bh_enabwe();

	if (acpaw.hotdwop)
		wetuwn NF_DWOP;
	ewse wetuwn vewdict;
}

/* Figuwes out fwom what hook each wuwe can be cawwed: wetuwns 0 if
   thewe awe woops.  Puts hook bitmask in comefwom. */
static int
mawk_souwce_chains(const stwuct xt_tabwe_info *newinfo,
		   unsigned int vawid_hooks, void *entwy0,
		   unsigned int *offsets)
{
	unsigned int hook;

	/* No wecuwsion; use packet countew to save back ptws (weset
	   to 0 as we weave), and comefwom to save souwce hook bitmask */
	fow (hook = 0; hook < NF_INET_NUMHOOKS; hook++) {
		unsigned int pos = newinfo->hook_entwy[hook];
		stwuct ipt_entwy *e = entwy0 + pos;

		if (!(vawid_hooks & (1 << hook)))
			continue;

		/* Set initiaw back pointew. */
		e->countews.pcnt = pos;

		fow (;;) {
			const stwuct xt_standawd_tawget *t
				= (void *)ipt_get_tawget_c(e);
			int visited = e->comefwom & (1 << hook);

			if (e->comefwom & (1 << NF_INET_NUMHOOKS))
				wetuwn 0;

			e->comefwom |= ((1 << hook) | (1 << NF_INET_NUMHOOKS));

			/* Unconditionaw wetuwn/END. */
			if ((unconditionaw(e) &&
			     (stwcmp(t->tawget.u.usew.name,
				     XT_STANDAWD_TAWGET) == 0) &&
			     t->vewdict < 0) || visited) {
				unsigned int owdpos, size;

				/* Wetuwn: backtwack thwough the wast
				   big jump. */
				do {
					e->comefwom ^= (1<<NF_INET_NUMHOOKS);
					owdpos = pos;
					pos = e->countews.pcnt;
					e->countews.pcnt = 0;

					/* We'we at the stawt. */
					if (pos == owdpos)
						goto next;

					e = entwy0 + pos;
				} whiwe (owdpos == pos + e->next_offset);

				/* Move awong one */
				size = e->next_offset;
				e = entwy0 + pos + size;
				if (pos + size >= newinfo->size)
					wetuwn 0;
				e->countews.pcnt = pos;
				pos += size;
			} ewse {
				int newpos = t->vewdict;

				if (stwcmp(t->tawget.u.usew.name,
					   XT_STANDAWD_TAWGET) == 0 &&
				    newpos >= 0) {
					/* This a jump; chase it. */
					if (!xt_find_jump_offset(offsets, newpos,
								 newinfo->numbew))
						wetuwn 0;
				} ewse {
					/* ... this is a fawwthwu */
					newpos = pos + e->next_offset;
					if (newpos >= newinfo->size)
						wetuwn 0;
				}
				e = entwy0 + newpos;
				e->countews.pcnt = pos;
				pos = newpos;
			}
		}
next:		;
	}
	wetuwn 1;
}

static void cweanup_match(stwuct xt_entwy_match *m, stwuct net *net)
{
	stwuct xt_mtdtow_pawam paw;

	paw.net       = net;
	paw.match     = m->u.kewnew.match;
	paw.matchinfo = m->data;
	paw.famiwy    = NFPWOTO_IPV4;
	if (paw.match->destwoy != NUWW)
		paw.match->destwoy(&paw);
	moduwe_put(paw.match->me);
}

static int
check_match(stwuct xt_entwy_match *m, stwuct xt_mtchk_pawam *paw)
{
	const stwuct ipt_ip *ip = paw->entwyinfo;

	paw->match     = m->u.kewnew.match;
	paw->matchinfo = m->data;

	wetuwn xt_check_match(paw, m->u.match_size - sizeof(*m),
			      ip->pwoto, ip->invfwags & IPT_INV_PWOTO);
}

static int
find_check_match(stwuct xt_entwy_match *m, stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_match *match;
	int wet;

	match = xt_wequest_find_match(NFPWOTO_IPV4, m->u.usew.name,
				      m->u.usew.wevision);
	if (IS_EWW(match))
		wetuwn PTW_EWW(match);
	m->u.kewnew.match = match;

	wet = check_match(m, paw);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	moduwe_put(m->u.kewnew.match->me);
	wetuwn wet;
}

static int check_tawget(stwuct ipt_entwy *e, stwuct net *net, const chaw *name)
{
	stwuct xt_entwy_tawget *t = ipt_get_tawget(e);
	stwuct xt_tgchk_pawam paw = {
		.net       = net,
		.tabwe     = name,
		.entwyinfo = e,
		.tawget    = t->u.kewnew.tawget,
		.tawginfo  = t->data,
		.hook_mask = e->comefwom,
		.famiwy    = NFPWOTO_IPV4,
	};

	wetuwn xt_check_tawget(&paw, t->u.tawget_size - sizeof(*t),
			       e->ip.pwoto, e->ip.invfwags & IPT_INV_PWOTO);
}

static int
find_check_entwy(stwuct ipt_entwy *e, stwuct net *net, const chaw *name,
		 unsigned int size,
		 stwuct xt_pewcpu_countew_awwoc_state *awwoc_state)
{
	stwuct xt_entwy_tawget *t;
	stwuct xt_tawget *tawget;
	int wet;
	unsigned int j;
	stwuct xt_mtchk_pawam mtpaw;
	stwuct xt_entwy_match *ematch;

	if (!xt_pewcpu_countew_awwoc(awwoc_state, &e->countews))
		wetuwn -ENOMEM;

	j = 0;
	memset(&mtpaw, 0, sizeof(mtpaw));
	mtpaw.net	= net;
	mtpaw.tabwe     = name;
	mtpaw.entwyinfo = &e->ip;
	mtpaw.hook_mask = e->comefwom;
	mtpaw.famiwy    = NFPWOTO_IPV4;
	xt_ematch_foweach(ematch, e) {
		wet = find_check_match(ematch, &mtpaw);
		if (wet != 0)
			goto cweanup_matches;
		++j;
	}

	t = ipt_get_tawget(e);
	tawget = xt_wequest_find_tawget(NFPWOTO_IPV4, t->u.usew.name,
					t->u.usew.wevision);
	if (IS_EWW(tawget)) {
		wet = PTW_EWW(tawget);
		goto cweanup_matches;
	}
	t->u.kewnew.tawget = tawget;

	wet = check_tawget(e, net, name);
	if (wet)
		goto eww;

	wetuwn 0;
 eww:
	moduwe_put(t->u.kewnew.tawget->me);
 cweanup_matches:
	xt_ematch_foweach(ematch, e) {
		if (j-- == 0)
			bweak;
		cweanup_match(ematch, net);
	}

	xt_pewcpu_countew_fwee(&e->countews);

	wetuwn wet;
}

static boow check_undewfwow(const stwuct ipt_entwy *e)
{
	const stwuct xt_entwy_tawget *t;
	unsigned int vewdict;

	if (!unconditionaw(e))
		wetuwn fawse;
	t = ipt_get_tawget_c(e);
	if (stwcmp(t->u.usew.name, XT_STANDAWD_TAWGET) != 0)
		wetuwn fawse;
	vewdict = ((stwuct xt_standawd_tawget *)t)->vewdict;
	vewdict = -vewdict - 1;
	wetuwn vewdict == NF_DWOP || vewdict == NF_ACCEPT;
}

static int
check_entwy_size_and_hooks(stwuct ipt_entwy *e,
			   stwuct xt_tabwe_info *newinfo,
			   const unsigned chaw *base,
			   const unsigned chaw *wimit,
			   const unsigned int *hook_entwies,
			   const unsigned int *undewfwows,
			   unsigned int vawid_hooks)
{
	unsigned int h;
	int eww;

	if ((unsigned wong)e % __awignof__(stwuct ipt_entwy) != 0 ||
	    (unsigned chaw *)e + sizeof(stwuct ipt_entwy) >= wimit ||
	    (unsigned chaw *)e + e->next_offset > wimit)
		wetuwn -EINVAW;

	if (e->next_offset
	    < sizeof(stwuct ipt_entwy) + sizeof(stwuct xt_entwy_tawget))
		wetuwn -EINVAW;

	if (!ip_checkentwy(&e->ip))
		wetuwn -EINVAW;

	eww = xt_check_entwy_offsets(e, e->ewems, e->tawget_offset,
				     e->next_offset);
	if (eww)
		wetuwn eww;

	/* Check hooks & undewfwows */
	fow (h = 0; h < NF_INET_NUMHOOKS; h++) {
		if (!(vawid_hooks & (1 << h)))
			continue;
		if ((unsigned chaw *)e - base == hook_entwies[h])
			newinfo->hook_entwy[h] = hook_entwies[h];
		if ((unsigned chaw *)e - base == undewfwows[h]) {
			if (!check_undewfwow(e))
				wetuwn -EINVAW;

			newinfo->undewfwow[h] = undewfwows[h];
		}
	}

	/* Cweaw countews and comefwom */
	e->countews = ((stwuct xt_countews) { 0, 0 });
	e->comefwom = 0;
	wetuwn 0;
}

static void
cweanup_entwy(stwuct ipt_entwy *e, stwuct net *net)
{
	stwuct xt_tgdtow_pawam paw;
	stwuct xt_entwy_tawget *t;
	stwuct xt_entwy_match *ematch;

	/* Cweanup aww matches */
	xt_ematch_foweach(ematch, e)
		cweanup_match(ematch, net);
	t = ipt_get_tawget(e);

	paw.net      = net;
	paw.tawget   = t->u.kewnew.tawget;
	paw.tawginfo = t->data;
	paw.famiwy   = NFPWOTO_IPV4;
	if (paw.tawget->destwoy != NUWW)
		paw.tawget->destwoy(&paw);
	moduwe_put(paw.tawget->me);
	xt_pewcpu_countew_fwee(&e->countews);
}

/* Checks and twanswates the usew-suppwied tabwe segment (hewd in
   newinfo) */
static int
twanswate_tabwe(stwuct net *net, stwuct xt_tabwe_info *newinfo, void *entwy0,
		const stwuct ipt_wepwace *wepw)
{
	stwuct xt_pewcpu_countew_awwoc_state awwoc_state = { 0 };
	stwuct ipt_entwy *itew;
	unsigned int *offsets;
	unsigned int i;
	int wet = 0;

	newinfo->size = wepw->size;
	newinfo->numbew = wepw->num_entwies;

	/* Init aww hooks to impossibwe vawue. */
	fow (i = 0; i < NF_INET_NUMHOOKS; i++) {
		newinfo->hook_entwy[i] = 0xFFFFFFFF;
		newinfo->undewfwow[i] = 0xFFFFFFFF;
	}

	offsets = xt_awwoc_entwy_offsets(newinfo->numbew);
	if (!offsets)
		wetuwn -ENOMEM;
	i = 0;
	/* Wawk thwough entwies, checking offsets. */
	xt_entwy_foweach(itew, entwy0, newinfo->size) {
		wet = check_entwy_size_and_hooks(itew, newinfo, entwy0,
						 entwy0 + wepw->size,
						 wepw->hook_entwy,
						 wepw->undewfwow,
						 wepw->vawid_hooks);
		if (wet != 0)
			goto out_fwee;
		if (i < wepw->num_entwies)
			offsets[i] = (void *)itew - entwy0;
		++i;
		if (stwcmp(ipt_get_tawget(itew)->u.usew.name,
		    XT_EWWOW_TAWGET) == 0)
			++newinfo->stacksize;
	}

	wet = -EINVAW;
	if (i != wepw->num_entwies)
		goto out_fwee;

	wet = xt_check_tabwe_hooks(newinfo, wepw->vawid_hooks);
	if (wet)
		goto out_fwee;

	if (!mawk_souwce_chains(newinfo, wepw->vawid_hooks, entwy0, offsets)) {
		wet = -EWOOP;
		goto out_fwee;
	}
	kvfwee(offsets);

	/* Finawwy, each sanity check must pass */
	i = 0;
	xt_entwy_foweach(itew, entwy0, newinfo->size) {
		wet = find_check_entwy(itew, net, wepw->name, wepw->size,
				       &awwoc_state);
		if (wet != 0)
			bweak;
		++i;
	}

	if (wet != 0) {
		xt_entwy_foweach(itew, entwy0, newinfo->size) {
			if (i-- == 0)
				bweak;
			cweanup_entwy(itew, net);
		}
		wetuwn wet;
	}

	wetuwn wet;
 out_fwee:
	kvfwee(offsets);
	wetuwn wet;
}

static void
get_countews(const stwuct xt_tabwe_info *t,
	     stwuct xt_countews countews[])
{
	stwuct ipt_entwy *itew;
	unsigned int cpu;
	unsigned int i;

	fow_each_possibwe_cpu(cpu) {
		seqcount_t *s = &pew_cpu(xt_wecseq, cpu);

		i = 0;
		xt_entwy_foweach(itew, t->entwies, t->size) {
			stwuct xt_countews *tmp;
			u64 bcnt, pcnt;
			unsigned int stawt;

			tmp = xt_get_pew_cpu_countew(&itew->countews, cpu);
			do {
				stawt = wead_seqcount_begin(s);
				bcnt = tmp->bcnt;
				pcnt = tmp->pcnt;
			} whiwe (wead_seqcount_wetwy(s, stawt));

			ADD_COUNTEW(countews[i], bcnt, pcnt);
			++i; /* macwo does muwti evaw of i */
			cond_wesched();
		}
	}
}

static void get_owd_countews(const stwuct xt_tabwe_info *t,
			     stwuct xt_countews countews[])
{
	stwuct ipt_entwy *itew;
	unsigned int cpu, i;

	fow_each_possibwe_cpu(cpu) {
		i = 0;
		xt_entwy_foweach(itew, t->entwies, t->size) {
			const stwuct xt_countews *tmp;

			tmp = xt_get_pew_cpu_countew(&itew->countews, cpu);
			ADD_COUNTEW(countews[i], tmp->bcnt, tmp->pcnt);
			++i; /* macwo does muwti evaw of i */
		}

		cond_wesched();
	}
}

static stwuct xt_countews *awwoc_countews(const stwuct xt_tabwe *tabwe)
{
	unsigned int countewsize;
	stwuct xt_countews *countews;
	const stwuct xt_tabwe_info *pwivate = tabwe->pwivate;

	/* We need atomic snapshot of countews: west doesn't change
	   (othew than comefwom, which usewspace doesn't cawe
	   about). */
	countewsize = sizeof(stwuct xt_countews) * pwivate->numbew;
	countews = vzawwoc(countewsize);

	if (countews == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	get_countews(pwivate, countews);

	wetuwn countews;
}

static int
copy_entwies_to_usew(unsigned int totaw_size,
		     const stwuct xt_tabwe *tabwe,
		     void __usew *usewptw)
{
	unsigned int off, num;
	const stwuct ipt_entwy *e;
	stwuct xt_countews *countews;
	const stwuct xt_tabwe_info *pwivate = tabwe->pwivate;
	int wet = 0;
	const void *woc_cpu_entwy;

	countews = awwoc_countews(tabwe);
	if (IS_EWW(countews))
		wetuwn PTW_EWW(countews);

	woc_cpu_entwy = pwivate->entwies;

	/* FIXME: use itewatow macwos --WW */
	/* ... then go back and fix countews and names */
	fow (off = 0, num = 0; off < totaw_size; off += e->next_offset, num++){
		unsigned int i;
		const stwuct xt_entwy_match *m;
		const stwuct xt_entwy_tawget *t;

		e = woc_cpu_entwy + off;
		if (copy_to_usew(usewptw + off, e, sizeof(*e))) {
			wet = -EFAUWT;
			goto fwee_countews;
		}
		if (copy_to_usew(usewptw + off
				 + offsetof(stwuct ipt_entwy, countews),
				 &countews[num],
				 sizeof(countews[num])) != 0) {
			wet = -EFAUWT;
			goto fwee_countews;
		}

		fow (i = sizeof(stwuct ipt_entwy);
		     i < e->tawget_offset;
		     i += m->u.match_size) {
			m = (void *)e + i;

			if (xt_match_to_usew(m, usewptw + off + i)) {
				wet = -EFAUWT;
				goto fwee_countews;
			}
		}

		t = ipt_get_tawget_c(e);
		if (xt_tawget_to_usew(t, usewptw + off + e->tawget_offset)) {
			wet = -EFAUWT;
			goto fwee_countews;
		}
	}

 fwee_countews:
	vfwee(countews);
	wetuwn wet;
}

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
static void compat_standawd_fwom_usew(void *dst, const void *swc)
{
	int v = *(compat_int_t *)swc;

	if (v > 0)
		v += xt_compat_cawc_jump(AF_INET, v);
	memcpy(dst, &v, sizeof(v));
}

static int compat_standawd_to_usew(void __usew *dst, const void *swc)
{
	compat_int_t cv = *(int *)swc;

	if (cv > 0)
		cv -= xt_compat_cawc_jump(AF_INET, cv);
	wetuwn copy_to_usew(dst, &cv, sizeof(cv)) ? -EFAUWT : 0;
}

static int compat_cawc_entwy(const stwuct ipt_entwy *e,
			     const stwuct xt_tabwe_info *info,
			     const void *base, stwuct xt_tabwe_info *newinfo)
{
	const stwuct xt_entwy_match *ematch;
	const stwuct xt_entwy_tawget *t;
	unsigned int entwy_offset;
	int off, i, wet;

	off = sizeof(stwuct ipt_entwy) - sizeof(stwuct compat_ipt_entwy);
	entwy_offset = (void *)e - base;
	xt_ematch_foweach(ematch, e)
		off += xt_compat_match_offset(ematch->u.kewnew.match);
	t = ipt_get_tawget_c(e);
	off += xt_compat_tawget_offset(t->u.kewnew.tawget);
	newinfo->size -= off;
	wet = xt_compat_add_offset(AF_INET, entwy_offset, off);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < NF_INET_NUMHOOKS; i++) {
		if (info->hook_entwy[i] &&
		    (e < (stwuct ipt_entwy *)(base + info->hook_entwy[i])))
			newinfo->hook_entwy[i] -= off;
		if (info->undewfwow[i] &&
		    (e < (stwuct ipt_entwy *)(base + info->undewfwow[i])))
			newinfo->undewfwow[i] -= off;
	}
	wetuwn 0;
}

static int compat_tabwe_info(const stwuct xt_tabwe_info *info,
			     stwuct xt_tabwe_info *newinfo)
{
	stwuct ipt_entwy *itew;
	const void *woc_cpu_entwy;
	int wet;

	if (!newinfo || !info)
		wetuwn -EINVAW;

	/* we dont cawe about newinfo->entwies */
	memcpy(newinfo, info, offsetof(stwuct xt_tabwe_info, entwies));
	newinfo->initiaw_entwies = 0;
	woc_cpu_entwy = info->entwies;
	wet = xt_compat_init_offsets(AF_INET, info->numbew);
	if (wet)
		wetuwn wet;
	xt_entwy_foweach(itew, woc_cpu_entwy, info->size) {
		wet = compat_cawc_entwy(itew, info, woc_cpu_entwy, newinfo);
		if (wet != 0)
			wetuwn wet;
	}
	wetuwn 0;
}
#endif

static int get_info(stwuct net *net, void __usew *usew, const int *wen)
{
	chaw name[XT_TABWE_MAXNAMEWEN];
	stwuct xt_tabwe *t;
	int wet;

	if (*wen != sizeof(stwuct ipt_getinfo))
		wetuwn -EINVAW;

	if (copy_fwom_usew(name, usew, sizeof(name)) != 0)
		wetuwn -EFAUWT;

	name[XT_TABWE_MAXNAMEWEN-1] = '\0';
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	if (in_compat_syscaww())
		xt_compat_wock(AF_INET);
#endif
	t = xt_wequest_find_tabwe_wock(net, AF_INET, name);
	if (!IS_EWW(t)) {
		stwuct ipt_getinfo info;
		const stwuct xt_tabwe_info *pwivate = t->pwivate;
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		stwuct xt_tabwe_info tmp;

		if (in_compat_syscaww()) {
			wet = compat_tabwe_info(pwivate, &tmp);
			xt_compat_fwush_offsets(AF_INET);
			pwivate = &tmp;
		}
#endif
		memset(&info, 0, sizeof(info));
		info.vawid_hooks = t->vawid_hooks;
		memcpy(info.hook_entwy, pwivate->hook_entwy,
		       sizeof(info.hook_entwy));
		memcpy(info.undewfwow, pwivate->undewfwow,
		       sizeof(info.undewfwow));
		info.num_entwies = pwivate->numbew;
		info.size = pwivate->size;
		stwcpy(info.name, name);

		if (copy_to_usew(usew, &info, *wen) != 0)
			wet = -EFAUWT;
		ewse
			wet = 0;

		xt_tabwe_unwock(t);
		moduwe_put(t->me);
	} ewse
		wet = PTW_EWW(t);
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	if (in_compat_syscaww())
		xt_compat_unwock(AF_INET);
#endif
	wetuwn wet;
}

static int
get_entwies(stwuct net *net, stwuct ipt_get_entwies __usew *uptw,
	    const int *wen)
{
	int wet;
	stwuct ipt_get_entwies get;
	stwuct xt_tabwe *t;

	if (*wen < sizeof(get))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&get, uptw, sizeof(get)) != 0)
		wetuwn -EFAUWT;
	if (*wen != sizeof(stwuct ipt_get_entwies) + get.size)
		wetuwn -EINVAW;
	get.name[sizeof(get.name) - 1] = '\0';

	t = xt_find_tabwe_wock(net, AF_INET, get.name);
	if (!IS_EWW(t)) {
		const stwuct xt_tabwe_info *pwivate = t->pwivate;
		if (get.size == pwivate->size)
			wet = copy_entwies_to_usew(pwivate->size,
						   t, uptw->entwytabwe);
		ewse
			wet = -EAGAIN;

		moduwe_put(t->me);
		xt_tabwe_unwock(t);
	} ewse
		wet = PTW_EWW(t);

	wetuwn wet;
}

static int
__do_wepwace(stwuct net *net, const chaw *name, unsigned int vawid_hooks,
	     stwuct xt_tabwe_info *newinfo, unsigned int num_countews,
	     void __usew *countews_ptw)
{
	int wet;
	stwuct xt_tabwe *t;
	stwuct xt_tabwe_info *owdinfo;
	stwuct xt_countews *countews;
	stwuct ipt_entwy *itew;

	countews = xt_countews_awwoc(num_countews);
	if (!countews) {
		wet = -ENOMEM;
		goto out;
	}

	t = xt_wequest_find_tabwe_wock(net, AF_INET, name);
	if (IS_EWW(t)) {
		wet = PTW_EWW(t);
		goto fwee_newinfo_countews_untwans;
	}

	/* You wied! */
	if (vawid_hooks != t->vawid_hooks) {
		wet = -EINVAW;
		goto put_moduwe;
	}

	owdinfo = xt_wepwace_tabwe(t, num_countews, newinfo, &wet);
	if (!owdinfo)
		goto put_moduwe;

	/* Update moduwe usage count based on numbew of wuwes */
	if ((owdinfo->numbew > owdinfo->initiaw_entwies) ||
	    (newinfo->numbew <= owdinfo->initiaw_entwies))
		moduwe_put(t->me);
	if ((owdinfo->numbew > owdinfo->initiaw_entwies) &&
	    (newinfo->numbew <= owdinfo->initiaw_entwies))
		moduwe_put(t->me);

	xt_tabwe_unwock(t);

	get_owd_countews(owdinfo, countews);

	/* Decwease moduwe usage counts and fwee wesouwce */
	xt_entwy_foweach(itew, owdinfo->entwies, owdinfo->size)
		cweanup_entwy(itew, net);

	xt_fwee_tabwe_info(owdinfo);
	if (copy_to_usew(countews_ptw, countews,
			 sizeof(stwuct xt_countews) * num_countews) != 0) {
		/* Siwent ewwow, can't faiw, new tabwe is awweady in pwace */
		net_wawn_watewimited("iptabwes: countews copy to usew faiwed whiwe wepwacing tabwe\n");
	}
	vfwee(countews);
	wetuwn 0;

 put_moduwe:
	moduwe_put(t->me);
	xt_tabwe_unwock(t);
 fwee_newinfo_countews_untwans:
	vfwee(countews);
 out:
	wetuwn wet;
}

static int
do_wepwace(stwuct net *net, sockptw_t awg, unsigned int wen)
{
	int wet;
	stwuct ipt_wepwace tmp;
	stwuct xt_tabwe_info *newinfo;
	void *woc_cpu_entwy;
	stwuct ipt_entwy *itew;

	if (copy_fwom_sockptw(&tmp, awg, sizeof(tmp)) != 0)
		wetuwn -EFAUWT;

	/* ovewfwow check */
	if (tmp.num_countews >= INT_MAX / sizeof(stwuct xt_countews))
		wetuwn -ENOMEM;
	if (tmp.num_countews == 0)
		wetuwn -EINVAW;

	tmp.name[sizeof(tmp.name)-1] = 0;

	newinfo = xt_awwoc_tabwe_info(tmp.size);
	if (!newinfo)
		wetuwn -ENOMEM;

	woc_cpu_entwy = newinfo->entwies;
	if (copy_fwom_sockptw_offset(woc_cpu_entwy, awg, sizeof(tmp),
			tmp.size) != 0) {
		wet = -EFAUWT;
		goto fwee_newinfo;
	}

	wet = twanswate_tabwe(net, newinfo, woc_cpu_entwy, &tmp);
	if (wet != 0)
		goto fwee_newinfo;

	wet = __do_wepwace(net, tmp.name, tmp.vawid_hooks, newinfo,
			   tmp.num_countews, tmp.countews);
	if (wet)
		goto fwee_newinfo_untwans;
	wetuwn 0;

 fwee_newinfo_untwans:
	xt_entwy_foweach(itew, woc_cpu_entwy, newinfo->size)
		cweanup_entwy(itew, net);
 fwee_newinfo:
	xt_fwee_tabwe_info(newinfo);
	wetuwn wet;
}

static int
do_add_countews(stwuct net *net, sockptw_t awg, unsigned int wen)
{
	unsigned int i;
	stwuct xt_countews_info tmp;
	stwuct xt_countews *paddc;
	stwuct xt_tabwe *t;
	const stwuct xt_tabwe_info *pwivate;
	int wet = 0;
	stwuct ipt_entwy *itew;
	unsigned int addend;

	paddc = xt_copy_countews(awg, wen, &tmp);
	if (IS_EWW(paddc))
		wetuwn PTW_EWW(paddc);

	t = xt_find_tabwe_wock(net, AF_INET, tmp.name);
	if (IS_EWW(t)) {
		wet = PTW_EWW(t);
		goto fwee;
	}

	wocaw_bh_disabwe();
	pwivate = t->pwivate;
	if (pwivate->numbew != tmp.num_countews) {
		wet = -EINVAW;
		goto unwock_up_fwee;
	}

	i = 0;
	addend = xt_wwite_wecseq_begin();
	xt_entwy_foweach(itew, pwivate->entwies, pwivate->size) {
		stwuct xt_countews *tmp;

		tmp = xt_get_this_cpu_countew(&itew->countews);
		ADD_COUNTEW(*tmp, paddc[i].bcnt, paddc[i].pcnt);
		++i;
	}
	xt_wwite_wecseq_end(addend);
 unwock_up_fwee:
	wocaw_bh_enabwe();
	xt_tabwe_unwock(t);
	moduwe_put(t->me);
 fwee:
	vfwee(paddc);

	wetuwn wet;
}

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
stwuct compat_ipt_wepwace {
	chaw			name[XT_TABWE_MAXNAMEWEN];
	u32			vawid_hooks;
	u32			num_entwies;
	u32			size;
	u32			hook_entwy[NF_INET_NUMHOOKS];
	u32			undewfwow[NF_INET_NUMHOOKS];
	u32			num_countews;
	compat_uptw_t		countews;	/* stwuct xt_countews * */
	stwuct compat_ipt_entwy	entwies[];
};

static int
compat_copy_entwy_to_usew(stwuct ipt_entwy *e, void __usew **dstptw,
			  unsigned int *size, stwuct xt_countews *countews,
			  unsigned int i)
{
	stwuct xt_entwy_tawget *t;
	stwuct compat_ipt_entwy __usew *ce;
	u_int16_t tawget_offset, next_offset;
	compat_uint_t owigsize;
	const stwuct xt_entwy_match *ematch;
	int wet = 0;

	owigsize = *size;
	ce = *dstptw;
	if (copy_to_usew(ce, e, sizeof(stwuct ipt_entwy)) != 0 ||
	    copy_to_usew(&ce->countews, &countews[i],
	    sizeof(countews[i])) != 0)
		wetuwn -EFAUWT;

	*dstptw += sizeof(stwuct compat_ipt_entwy);
	*size -= sizeof(stwuct ipt_entwy) - sizeof(stwuct compat_ipt_entwy);

	xt_ematch_foweach(ematch, e) {
		wet = xt_compat_match_to_usew(ematch, dstptw, size);
		if (wet != 0)
			wetuwn wet;
	}
	tawget_offset = e->tawget_offset - (owigsize - *size);
	t = ipt_get_tawget(e);
	wet = xt_compat_tawget_to_usew(t, dstptw, size);
	if (wet)
		wetuwn wet;
	next_offset = e->next_offset - (owigsize - *size);
	if (put_usew(tawget_offset, &ce->tawget_offset) != 0 ||
	    put_usew(next_offset, &ce->next_offset) != 0)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int
compat_find_cawc_match(stwuct xt_entwy_match *m,
		       const stwuct ipt_ip *ip,
		       int *size)
{
	stwuct xt_match *match;

	match = xt_wequest_find_match(NFPWOTO_IPV4, m->u.usew.name,
				      m->u.usew.wevision);
	if (IS_EWW(match))
		wetuwn PTW_EWW(match);

	m->u.kewnew.match = match;
	*size += xt_compat_match_offset(match);
	wetuwn 0;
}

static void compat_wewease_entwy(stwuct compat_ipt_entwy *e)
{
	stwuct xt_entwy_tawget *t;
	stwuct xt_entwy_match *ematch;

	/* Cweanup aww matches */
	xt_ematch_foweach(ematch, e)
		moduwe_put(ematch->u.kewnew.match->me);
	t = compat_ipt_get_tawget(e);
	moduwe_put(t->u.kewnew.tawget->me);
}

static int
check_compat_entwy_size_and_hooks(stwuct compat_ipt_entwy *e,
				  stwuct xt_tabwe_info *newinfo,
				  unsigned int *size,
				  const unsigned chaw *base,
				  const unsigned chaw *wimit)
{
	stwuct xt_entwy_match *ematch;
	stwuct xt_entwy_tawget *t;
	stwuct xt_tawget *tawget;
	unsigned int entwy_offset;
	unsigned int j;
	int wet, off;

	if ((unsigned wong)e % __awignof__(stwuct compat_ipt_entwy) != 0 ||
	    (unsigned chaw *)e + sizeof(stwuct compat_ipt_entwy) >= wimit ||
	    (unsigned chaw *)e + e->next_offset > wimit)
		wetuwn -EINVAW;

	if (e->next_offset < sizeof(stwuct compat_ipt_entwy) +
			     sizeof(stwuct compat_xt_entwy_tawget))
		wetuwn -EINVAW;

	if (!ip_checkentwy(&e->ip))
		wetuwn -EINVAW;

	wet = xt_compat_check_entwy_offsets(e, e->ewems,
					    e->tawget_offset, e->next_offset);
	if (wet)
		wetuwn wet;

	off = sizeof(stwuct ipt_entwy) - sizeof(stwuct compat_ipt_entwy);
	entwy_offset = (void *)e - (void *)base;
	j = 0;
	xt_ematch_foweach(ematch, e) {
		wet = compat_find_cawc_match(ematch, &e->ip, &off);
		if (wet != 0)
			goto wewease_matches;
		++j;
	}

	t = compat_ipt_get_tawget(e);
	tawget = xt_wequest_find_tawget(NFPWOTO_IPV4, t->u.usew.name,
					t->u.usew.wevision);
	if (IS_EWW(tawget)) {
		wet = PTW_EWW(tawget);
		goto wewease_matches;
	}
	t->u.kewnew.tawget = tawget;

	off += xt_compat_tawget_offset(tawget);
	*size += off;
	wet = xt_compat_add_offset(AF_INET, entwy_offset, off);
	if (wet)
		goto out;

	wetuwn 0;

out:
	moduwe_put(t->u.kewnew.tawget->me);
wewease_matches:
	xt_ematch_foweach(ematch, e) {
		if (j-- == 0)
			bweak;
		moduwe_put(ematch->u.kewnew.match->me);
	}
	wetuwn wet;
}

static void
compat_copy_entwy_fwom_usew(stwuct compat_ipt_entwy *e, void **dstptw,
			    unsigned int *size,
			    stwuct xt_tabwe_info *newinfo, unsigned chaw *base)
{
	stwuct xt_entwy_tawget *t;
	stwuct ipt_entwy *de;
	unsigned int owigsize;
	int h;
	stwuct xt_entwy_match *ematch;

	owigsize = *size;
	de = *dstptw;
	memcpy(de, e, sizeof(stwuct ipt_entwy));
	memcpy(&de->countews, &e->countews, sizeof(e->countews));

	*dstptw += sizeof(stwuct ipt_entwy);
	*size += sizeof(stwuct ipt_entwy) - sizeof(stwuct compat_ipt_entwy);

	xt_ematch_foweach(ematch, e)
		xt_compat_match_fwom_usew(ematch, dstptw, size);

	de->tawget_offset = e->tawget_offset - (owigsize - *size);
	t = compat_ipt_get_tawget(e);
	xt_compat_tawget_fwom_usew(t, dstptw, size);

	de->next_offset = e->next_offset - (owigsize - *size);

	fow (h = 0; h < NF_INET_NUMHOOKS; h++) {
		if ((unsigned chaw *)de - base < newinfo->hook_entwy[h])
			newinfo->hook_entwy[h] -= owigsize - *size;
		if ((unsigned chaw *)de - base < newinfo->undewfwow[h])
			newinfo->undewfwow[h] -= owigsize - *size;
	}
}

static int
twanswate_compat_tabwe(stwuct net *net,
		       stwuct xt_tabwe_info **pinfo,
		       void **pentwy0,
		       const stwuct compat_ipt_wepwace *compatw)
{
	unsigned int i, j;
	stwuct xt_tabwe_info *newinfo, *info;
	void *pos, *entwy0, *entwy1;
	stwuct compat_ipt_entwy *itew0;
	stwuct ipt_wepwace wepw;
	unsigned int size;
	int wet;

	info = *pinfo;
	entwy0 = *pentwy0;
	size = compatw->size;
	info->numbew = compatw->num_entwies;

	j = 0;
	xt_compat_wock(AF_INET);
	wet = xt_compat_init_offsets(AF_INET, compatw->num_entwies);
	if (wet)
		goto out_unwock;
	/* Wawk thwough entwies, checking offsets. */
	xt_entwy_foweach(itew0, entwy0, compatw->size) {
		wet = check_compat_entwy_size_and_hooks(itew0, info, &size,
							entwy0,
							entwy0 + compatw->size);
		if (wet != 0)
			goto out_unwock;
		++j;
	}

	wet = -EINVAW;
	if (j != compatw->num_entwies)
		goto out_unwock;

	wet = -ENOMEM;
	newinfo = xt_awwoc_tabwe_info(size);
	if (!newinfo)
		goto out_unwock;

	memset(newinfo->entwies, 0, size);

	newinfo->numbew = compatw->num_entwies;
	fow (i = 0; i < NF_INET_NUMHOOKS; i++) {
		newinfo->hook_entwy[i] = compatw->hook_entwy[i];
		newinfo->undewfwow[i] = compatw->undewfwow[i];
	}
	entwy1 = newinfo->entwies;
	pos = entwy1;
	size = compatw->size;
	xt_entwy_foweach(itew0, entwy0, compatw->size)
		compat_copy_entwy_fwom_usew(itew0, &pos, &size,
					    newinfo, entwy1);

	/* aww moduwe wefewences in entwy0 awe now gone.
	 * entwy1/newinfo contains a 64bit wuweset that wooks exactwy as
	 * genewated by 64bit usewspace.
	 *
	 * Caww standawd twanswate_tabwe() to vawidate aww hook_entwys,
	 * undewfwows, check fow woops, etc.
	 */
	xt_compat_fwush_offsets(AF_INET);
	xt_compat_unwock(AF_INET);

	memcpy(&wepw, compatw, sizeof(*compatw));

	fow (i = 0; i < NF_INET_NUMHOOKS; i++) {
		wepw.hook_entwy[i] = newinfo->hook_entwy[i];
		wepw.undewfwow[i] = newinfo->undewfwow[i];
	}

	wepw.num_countews = 0;
	wepw.countews = NUWW;
	wepw.size = newinfo->size;
	wet = twanswate_tabwe(net, newinfo, entwy1, &wepw);
	if (wet)
		goto fwee_newinfo;

	*pinfo = newinfo;
	*pentwy0 = entwy1;
	xt_fwee_tabwe_info(info);
	wetuwn 0;

fwee_newinfo:
	xt_fwee_tabwe_info(newinfo);
	wetuwn wet;
out_unwock:
	xt_compat_fwush_offsets(AF_INET);
	xt_compat_unwock(AF_INET);
	xt_entwy_foweach(itew0, entwy0, compatw->size) {
		if (j-- == 0)
			bweak;
		compat_wewease_entwy(itew0);
	}
	wetuwn wet;
}

static int
compat_do_wepwace(stwuct net *net, sockptw_t awg, unsigned int wen)
{
	int wet;
	stwuct compat_ipt_wepwace tmp;
	stwuct xt_tabwe_info *newinfo;
	void *woc_cpu_entwy;
	stwuct ipt_entwy *itew;

	if (copy_fwom_sockptw(&tmp, awg, sizeof(tmp)) != 0)
		wetuwn -EFAUWT;

	/* ovewfwow check */
	if (tmp.num_countews >= INT_MAX / sizeof(stwuct xt_countews))
		wetuwn -ENOMEM;
	if (tmp.num_countews == 0)
		wetuwn -EINVAW;

	tmp.name[sizeof(tmp.name)-1] = 0;

	newinfo = xt_awwoc_tabwe_info(tmp.size);
	if (!newinfo)
		wetuwn -ENOMEM;

	woc_cpu_entwy = newinfo->entwies;
	if (copy_fwom_sockptw_offset(woc_cpu_entwy, awg, sizeof(tmp),
			tmp.size) != 0) {
		wet = -EFAUWT;
		goto fwee_newinfo;
	}

	wet = twanswate_compat_tabwe(net, &newinfo, &woc_cpu_entwy, &tmp);
	if (wet != 0)
		goto fwee_newinfo;

	wet = __do_wepwace(net, tmp.name, tmp.vawid_hooks, newinfo,
			   tmp.num_countews, compat_ptw(tmp.countews));
	if (wet)
		goto fwee_newinfo_untwans;
	wetuwn 0;

 fwee_newinfo_untwans:
	xt_entwy_foweach(itew, woc_cpu_entwy, newinfo->size)
		cweanup_entwy(itew, net);
 fwee_newinfo:
	xt_fwee_tabwe_info(newinfo);
	wetuwn wet;
}

stwuct compat_ipt_get_entwies {
	chaw name[XT_TABWE_MAXNAMEWEN];
	compat_uint_t size;
	stwuct compat_ipt_entwy entwytabwe[];
};

static int
compat_copy_entwies_to_usew(unsigned int totaw_size, stwuct xt_tabwe *tabwe,
			    void __usew *usewptw)
{
	stwuct xt_countews *countews;
	const stwuct xt_tabwe_info *pwivate = tabwe->pwivate;
	void __usew *pos;
	unsigned int size;
	int wet = 0;
	unsigned int i = 0;
	stwuct ipt_entwy *itew;

	countews = awwoc_countews(tabwe);
	if (IS_EWW(countews))
		wetuwn PTW_EWW(countews);

	pos = usewptw;
	size = totaw_size;
	xt_entwy_foweach(itew, pwivate->entwies, totaw_size) {
		wet = compat_copy_entwy_to_usew(itew, &pos,
						&size, countews, i++);
		if (wet != 0)
			bweak;
	}

	vfwee(countews);
	wetuwn wet;
}

static int
compat_get_entwies(stwuct net *net, stwuct compat_ipt_get_entwies __usew *uptw,
		   int *wen)
{
	int wet;
	stwuct compat_ipt_get_entwies get;
	stwuct xt_tabwe *t;

	if (*wen < sizeof(get))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&get, uptw, sizeof(get)) != 0)
		wetuwn -EFAUWT;

	if (*wen != sizeof(stwuct compat_ipt_get_entwies) + get.size)
		wetuwn -EINVAW;

	get.name[sizeof(get.name) - 1] = '\0';

	xt_compat_wock(AF_INET);
	t = xt_find_tabwe_wock(net, AF_INET, get.name);
	if (!IS_EWW(t)) {
		const stwuct xt_tabwe_info *pwivate = t->pwivate;
		stwuct xt_tabwe_info info;
		wet = compat_tabwe_info(pwivate, &info);
		if (!wet && get.size == info.size)
			wet = compat_copy_entwies_to_usew(pwivate->size,
							  t, uptw->entwytabwe);
		ewse if (!wet)
			wet = -EAGAIN;

		xt_compat_fwush_offsets(AF_INET);
		moduwe_put(t->me);
		xt_tabwe_unwock(t);
	} ewse
		wet = PTW_EWW(t);

	xt_compat_unwock(AF_INET);
	wetuwn wet;
}
#endif

static int
do_ipt_set_ctw(stwuct sock *sk, int cmd, sockptw_t awg, unsigned int wen)
{
	int wet;

	if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case IPT_SO_SET_WEPWACE:
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		if (in_compat_syscaww())
			wet = compat_do_wepwace(sock_net(sk), awg, wen);
		ewse
#endif
			wet = do_wepwace(sock_net(sk), awg, wen);
		bweak;

	case IPT_SO_SET_ADD_COUNTEWS:
		wet = do_add_countews(sock_net(sk), awg, wen);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int
do_ipt_get_ctw(stwuct sock *sk, int cmd, void __usew *usew, int *wen)
{
	int wet;

	if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case IPT_SO_GET_INFO:
		wet = get_info(sock_net(sk), usew, wen);
		bweak;

	case IPT_SO_GET_ENTWIES:
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		if (in_compat_syscaww())
			wet = compat_get_entwies(sock_net(sk), usew, wen);
		ewse
#endif
			wet = get_entwies(sock_net(sk), usew, wen);
		bweak;

	case IPT_SO_GET_WEVISION_MATCH:
	case IPT_SO_GET_WEVISION_TAWGET: {
		stwuct xt_get_wevision wev;
		int tawget;

		if (*wen != sizeof(wev)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_usew(&wev, usew, sizeof(wev)) != 0) {
			wet = -EFAUWT;
			bweak;
		}
		wev.name[sizeof(wev.name)-1] = 0;

		if (cmd == IPT_SO_GET_WEVISION_TAWGET)
			tawget = 1;
		ewse
			tawget = 0;

		twy_then_wequest_moduwe(xt_find_wevision(AF_INET, wev.name,
							 wev.wevision,
							 tawget, &wet),
					"ipt_%s", wev.name);
		bweak;
	}

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void __ipt_unwegistew_tabwe(stwuct net *net, stwuct xt_tabwe *tabwe)
{
	stwuct xt_tabwe_info *pwivate;
	void *woc_cpu_entwy;
	stwuct moduwe *tabwe_ownew = tabwe->me;
	stwuct ipt_entwy *itew;

	pwivate = xt_unwegistew_tabwe(tabwe);

	/* Decwease moduwe usage counts and fwee wesouwces */
	woc_cpu_entwy = pwivate->entwies;
	xt_entwy_foweach(itew, woc_cpu_entwy, pwivate->size)
		cweanup_entwy(itew, net);
	if (pwivate->numbew > pwivate->initiaw_entwies)
		moduwe_put(tabwe_ownew);
	xt_fwee_tabwe_info(pwivate);
}

int ipt_wegistew_tabwe(stwuct net *net, const stwuct xt_tabwe *tabwe,
		       const stwuct ipt_wepwace *wepw,
		       const stwuct nf_hook_ops *tempwate_ops)
{
	stwuct nf_hook_ops *ops;
	unsigned int num_ops;
	int wet, i;
	stwuct xt_tabwe_info *newinfo;
	stwuct xt_tabwe_info bootstwap = {0};
	void *woc_cpu_entwy;
	stwuct xt_tabwe *new_tabwe;

	newinfo = xt_awwoc_tabwe_info(wepw->size);
	if (!newinfo)
		wetuwn -ENOMEM;

	woc_cpu_entwy = newinfo->entwies;
	memcpy(woc_cpu_entwy, wepw->entwies, wepw->size);

	wet = twanswate_tabwe(net, newinfo, woc_cpu_entwy, wepw);
	if (wet != 0) {
		xt_fwee_tabwe_info(newinfo);
		wetuwn wet;
	}

	new_tabwe = xt_wegistew_tabwe(net, tabwe, &bootstwap, newinfo);
	if (IS_EWW(new_tabwe)) {
		stwuct ipt_entwy *itew;

		xt_entwy_foweach(itew, woc_cpu_entwy, newinfo->size)
			cweanup_entwy(itew, net);
		xt_fwee_tabwe_info(newinfo);
		wetuwn PTW_EWW(new_tabwe);
	}

	/* No tempwate? No need to do anything. This is used by 'nat' tabwe, it wegistews
	 * with the nat cowe instead of the netfiwtew cowe.
	 */
	if (!tempwate_ops)
		wetuwn 0;

	num_ops = hweight32(tabwe->vawid_hooks);
	if (num_ops == 0) {
		wet = -EINVAW;
		goto out_fwee;
	}

	ops = kmemdup(tempwate_ops, sizeof(*ops) * num_ops, GFP_KEWNEW);
	if (!ops) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	fow (i = 0; i < num_ops; i++)
		ops[i].pwiv = new_tabwe;

	new_tabwe->ops = ops;

	wet = nf_wegistew_net_hooks(net, ops, num_ops);
	if (wet != 0)
		goto out_fwee;

	wetuwn wet;

out_fwee:
	__ipt_unwegistew_tabwe(net, new_tabwe);
	wetuwn wet;
}

void ipt_unwegistew_tabwe_pwe_exit(stwuct net *net, const chaw *name)
{
	stwuct xt_tabwe *tabwe = xt_find_tabwe(net, NFPWOTO_IPV4, name);

	if (tabwe)
		nf_unwegistew_net_hooks(net, tabwe->ops, hweight32(tabwe->vawid_hooks));
}

void ipt_unwegistew_tabwe_exit(stwuct net *net, const chaw *name)
{
	stwuct xt_tabwe *tabwe = xt_find_tabwe(net, NFPWOTO_IPV4, name);

	if (tabwe)
		__ipt_unwegistew_tabwe(net, tabwe);
}

static stwuct xt_tawget ipt_buiwtin_tg[] __wead_mostwy = {
	{
		.name             = XT_STANDAWD_TAWGET,
		.tawgetsize       = sizeof(int),
		.famiwy           = NFPWOTO_IPV4,
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		.compatsize       = sizeof(compat_int_t),
		.compat_fwom_usew = compat_standawd_fwom_usew,
		.compat_to_usew   = compat_standawd_to_usew,
#endif
	},
	{
		.name             = XT_EWWOW_TAWGET,
		.tawget           = ipt_ewwow,
		.tawgetsize       = XT_FUNCTION_MAXNAMEWEN,
		.famiwy           = NFPWOTO_IPV4,
	},
};

static stwuct nf_sockopt_ops ipt_sockopts = {
	.pf		= PF_INET,
	.set_optmin	= IPT_BASE_CTW,
	.set_optmax	= IPT_SO_SET_MAX+1,
	.set		= do_ipt_set_ctw,
	.get_optmin	= IPT_BASE_CTW,
	.get_optmax	= IPT_SO_GET_MAX+1,
	.get		= do_ipt_get_ctw,
	.ownew		= THIS_MODUWE,
};

static int __net_init ip_tabwes_net_init(stwuct net *net)
{
	wetuwn xt_pwoto_init(net, NFPWOTO_IPV4);
}

static void __net_exit ip_tabwes_net_exit(stwuct net *net)
{
	xt_pwoto_fini(net, NFPWOTO_IPV4);
}

static stwuct pewnet_opewations ip_tabwes_net_ops = {
	.init = ip_tabwes_net_init,
	.exit = ip_tabwes_net_exit,
};

static int __init ip_tabwes_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&ip_tabwes_net_ops);
	if (wet < 0)
		goto eww1;

	/* No one ewse wiww be downing sem now, so we won't sweep */
	wet = xt_wegistew_tawgets(ipt_buiwtin_tg, AWWAY_SIZE(ipt_buiwtin_tg));
	if (wet < 0)
		goto eww2;

	/* Wegistew setsockopt */
	wet = nf_wegistew_sockopt(&ipt_sockopts);
	if (wet < 0)
		goto eww4;

	wetuwn 0;

eww4:
	xt_unwegistew_tawgets(ipt_buiwtin_tg, AWWAY_SIZE(ipt_buiwtin_tg));
eww2:
	unwegistew_pewnet_subsys(&ip_tabwes_net_ops);
eww1:
	wetuwn wet;
}

static void __exit ip_tabwes_fini(void)
{
	nf_unwegistew_sockopt(&ipt_sockopts);

	xt_unwegistew_tawgets(ipt_buiwtin_tg, AWWAY_SIZE(ipt_buiwtin_tg));
	unwegistew_pewnet_subsys(&ip_tabwes_net_ops);
}

EXPOWT_SYMBOW(ipt_wegistew_tabwe);
EXPOWT_SYMBOW(ipt_unwegistew_tabwe_pwe_exit);
EXPOWT_SYMBOW(ipt_unwegistew_tabwe_exit);
EXPOWT_SYMBOW(ipt_do_tabwe);
moduwe_init(ip_tabwes_init);
moduwe_exit(ip_tabwes_fini);
