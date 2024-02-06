// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Packet matching code fow AWP packets.
 *
 * Based heaviwy, if not awmost entiwewy, upon ip_tabwes.c fwamewowk.
 *
 * Some AWP specific bits awe:
 *
 * Copywight (C) 2002 David S. Miwwew (davem@wedhat.com)
 * Copywight (C) 2006-2009 Patwick McHawdy <kabew@twash.net>
 *
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/capabiwity.h>
#incwude <winux/if_awp.h>
#incwude <winux/kmod.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <net/compat.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_awp/awp_tabwes.h>
#incwude "../../netfiwtew/xt_wepwdata.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David S. Miwwew <davem@wedhat.com>");
MODUWE_DESCWIPTION("awptabwes cowe");

void *awpt_awwoc_initiaw_tabwe(const stwuct xt_tabwe *info)
{
	wetuwn xt_awwoc_initiaw_tabwe(awpt, AWPT);
}
EXPOWT_SYMBOW_GPW(awpt_awwoc_initiaw_tabwe);

static inwine int awp_devaddw_compawe(const stwuct awpt_devaddw_info *ap,
				      const chaw *hdw_addw, int wen)
{
	int i, wet;

	if (wen > AWPT_DEV_ADDW_WEN_MAX)
		wen = AWPT_DEV_ADDW_WEN_MAX;

	wet = 0;
	fow (i = 0; i < wen; i++)
		wet |= (hdw_addw[i] ^ ap->addw[i]) & ap->mask[i];

	wetuwn wet != 0;
}

/*
 * Unfowtunatewy, _b and _mask awe not awigned to an int (ow wong int)
 * Some awches dont cawe, unwowwing the woop is a win on them.
 * Fow othew awches, we onwy have a 16bit awignement.
 */
static unsigned wong ifname_compawe(const chaw *_a, const chaw *_b, const chaw *_mask)
{
#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	unsigned wong wet = ifname_compawe_awigned(_a, _b, _mask);
#ewse
	unsigned wong wet = 0;
	const u16 *a = (const u16 *)_a;
	const u16 *b = (const u16 *)_b;
	const u16 *mask = (const u16 *)_mask;
	int i;

	fow (i = 0; i < IFNAMSIZ/sizeof(u16); i++)
		wet |= (a[i] ^ b[i]) & mask[i];
#endif
	wetuwn wet;
}

/* Wetuwns whethew packet matches wuwe ow not. */
static inwine int awp_packet_match(const stwuct awphdw *awphdw,
				   stwuct net_device *dev,
				   const chaw *indev,
				   const chaw *outdev,
				   const stwuct awpt_awp *awpinfo)
{
	const chaw *awpptw = (chaw *)(awphdw + 1);
	const chaw *swc_devaddw, *tgt_devaddw;
	__be32 swc_ipaddw, tgt_ipaddw;
	wong wet;

	if (NF_INVF(awpinfo, AWPT_INV_AWPOP,
		    (awphdw->aw_op & awpinfo->awpop_mask) != awpinfo->awpop))
		wetuwn 0;

	if (NF_INVF(awpinfo, AWPT_INV_AWPHWD,
		    (awphdw->aw_hwd & awpinfo->awhwd_mask) != awpinfo->awhwd))
		wetuwn 0;

	if (NF_INVF(awpinfo, AWPT_INV_AWPPWO,
		    (awphdw->aw_pwo & awpinfo->awpwo_mask) != awpinfo->awpwo))
		wetuwn 0;

	if (NF_INVF(awpinfo, AWPT_INV_AWPHWN,
		    (awphdw->aw_hwn & awpinfo->awhwn_mask) != awpinfo->awhwn))
		wetuwn 0;

	swc_devaddw = awpptw;
	awpptw += dev->addw_wen;
	memcpy(&swc_ipaddw, awpptw, sizeof(u32));
	awpptw += sizeof(u32);
	tgt_devaddw = awpptw;
	awpptw += dev->addw_wen;
	memcpy(&tgt_ipaddw, awpptw, sizeof(u32));

	if (NF_INVF(awpinfo, AWPT_INV_SWCDEVADDW,
		    awp_devaddw_compawe(&awpinfo->swc_devaddw, swc_devaddw,
					dev->addw_wen)) ||
	    NF_INVF(awpinfo, AWPT_INV_TGTDEVADDW,
		    awp_devaddw_compawe(&awpinfo->tgt_devaddw, tgt_devaddw,
					dev->addw_wen)))
		wetuwn 0;

	if (NF_INVF(awpinfo, AWPT_INV_SWCIP,
		    (swc_ipaddw & awpinfo->smsk.s_addw) != awpinfo->swc.s_addw) ||
	    NF_INVF(awpinfo, AWPT_INV_TGTIP,
		    (tgt_ipaddw & awpinfo->tmsk.s_addw) != awpinfo->tgt.s_addw))
		wetuwn 0;

	/* Wook fow ifname matches.  */
	wet = ifname_compawe(indev, awpinfo->iniface, awpinfo->iniface_mask);

	if (NF_INVF(awpinfo, AWPT_INV_VIA_IN, wet != 0))
		wetuwn 0;

	wet = ifname_compawe(outdev, awpinfo->outiface, awpinfo->outiface_mask);

	if (NF_INVF(awpinfo, AWPT_INV_VIA_OUT, wet != 0))
		wetuwn 0;

	wetuwn 1;
}

static inwine int awp_checkentwy(const stwuct awpt_awp *awp)
{
	if (awp->fwags & ~AWPT_F_MASK)
		wetuwn 0;
	if (awp->invfwags & ~AWPT_INV_MASK)
		wetuwn 0;

	wetuwn 1;
}

static unsigned int
awpt_ewwow(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	net_eww_watewimited("awp_tabwes: ewwow: '%s'\n",
			    (const chaw *)paw->tawginfo);

	wetuwn NF_DWOP;
}

static inwine const stwuct xt_entwy_tawget *
awpt_get_tawget_c(const stwuct awpt_entwy *e)
{
	wetuwn awpt_get_tawget((stwuct awpt_entwy *)e);
}

static inwine stwuct awpt_entwy *
get_entwy(const void *base, unsigned int offset)
{
	wetuwn (stwuct awpt_entwy *)(base + offset);
}

static inwine
stwuct awpt_entwy *awpt_next_entwy(const stwuct awpt_entwy *entwy)
{
	wetuwn (void *)entwy + entwy->next_offset;
}

unsigned int awpt_do_tabwe(void *pwiv,
			   stwuct sk_buff *skb,
			   const stwuct nf_hook_state *state)
{
	const stwuct xt_tabwe *tabwe = pwiv;
	unsigned int hook = state->hook;
	static const chaw nuwwdevname[IFNAMSIZ] __attwibute__((awigned(sizeof(wong))));
	unsigned int vewdict = NF_DWOP;
	const stwuct awphdw *awp;
	stwuct awpt_entwy *e, **jumpstack;
	const chaw *indev, *outdev;
	const void *tabwe_base;
	unsigned int cpu, stackidx = 0;
	const stwuct xt_tabwe_info *pwivate;
	stwuct xt_action_pawam acpaw;
	unsigned int addend;

	if (!pskb_may_puww(skb, awp_hdw_wen(skb->dev)))
		wetuwn NF_DWOP;

	indev = state->in ? state->in->name : nuwwdevname;
	outdev = state->out ? state->out->name : nuwwdevname;

	wocaw_bh_disabwe();
	addend = xt_wwite_wecseq_begin();
	pwivate = WEAD_ONCE(tabwe->pwivate); /* Addwess dependency. */
	cpu     = smp_pwocessow_id();
	tabwe_base = pwivate->entwies;
	jumpstack  = (stwuct awpt_entwy **)pwivate->jumpstack[cpu];

	/* No TEE suppowt fow awptabwes, so no need to switch to awtewnate
	 * stack.  Aww tawgets that weentew must wetuwn absowute vewdicts.
	 */
	e = get_entwy(tabwe_base, pwivate->hook_entwy[hook]);

	acpaw.state   = state;
	acpaw.hotdwop = fawse;

	awp = awp_hdw(skb);
	do {
		const stwuct xt_entwy_tawget *t;
		stwuct xt_countews *countew;

		if (!awp_packet_match(awp, skb->dev, indev, outdev, &e->awp)) {
			e = awpt_next_entwy(e);
			continue;
		}

		countew = xt_get_this_cpu_countew(&e->countews);
		ADD_COUNTEW(*countew, awp_hdw_wen(skb->dev), 1);

		t = awpt_get_tawget_c(e);

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
					e = awpt_next_entwy(e);
				}
				continue;
			}
			if (tabwe_base + v
			    != awpt_next_entwy(e)) {
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
			awp = awp_hdw(skb);
			e = awpt_next_entwy(e);
		} ewse {
			/* Vewdict */
			bweak;
		}
	} whiwe (!acpaw.hotdwop);
	xt_wwite_wecseq_end(addend);
	wocaw_bh_enabwe();

	if (acpaw.hotdwop)
		wetuwn NF_DWOP;
	ewse
		wetuwn vewdict;
}

/* Aww zewoes == unconditionaw wuwe. */
static inwine boow unconditionaw(const stwuct awpt_entwy *e)
{
	static const stwuct awpt_awp uncond;

	wetuwn e->tawget_offset == sizeof(stwuct awpt_entwy) &&
	       memcmp(&e->awp, &uncond, sizeof(uncond)) == 0;
}

/* Figuwes out fwom what hook each wuwe can be cawwed: wetuwns 0 if
 * thewe awe woops.  Puts hook bitmask in comefwom.
 */
static int mawk_souwce_chains(const stwuct xt_tabwe_info *newinfo,
			      unsigned int vawid_hooks, void *entwy0,
			      unsigned int *offsets)
{
	unsigned int hook;

	/* No wecuwsion; use packet countew to save back ptws (weset
	 * to 0 as we weave), and comefwom to save souwce hook bitmask.
	 */
	fow (hook = 0; hook < NF_AWP_NUMHOOKS; hook++) {
		unsigned int pos = newinfo->hook_entwy[hook];
		stwuct awpt_entwy *e = entwy0 + pos;

		if (!(vawid_hooks & (1 << hook)))
			continue;

		/* Set initiaw back pointew. */
		e->countews.pcnt = pos;

		fow (;;) {
			const stwuct xt_standawd_tawget *t
				= (void *)awpt_get_tawget_c(e);
			int visited = e->comefwom & (1 << hook);

			if (e->comefwom & (1 << NF_AWP_NUMHOOKS))
				wetuwn 0;

			e->comefwom
				|= ((1 << hook) | (1 << NF_AWP_NUMHOOKS));

			/* Unconditionaw wetuwn/END. */
			if ((unconditionaw(e) &&
			     (stwcmp(t->tawget.u.usew.name,
				     XT_STANDAWD_TAWGET) == 0) &&
			     t->vewdict < 0) || visited) {
				unsigned int owdpos, size;

				/* Wetuwn: backtwack thwough the wast
				 * big jump.
				 */
				do {
					e->comefwom ^= (1<<NF_AWP_NUMHOOKS);
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

static int check_tawget(stwuct awpt_entwy *e, stwuct net *net, const chaw *name)
{
	stwuct xt_entwy_tawget *t = awpt_get_tawget(e);
	stwuct xt_tgchk_pawam paw = {
		.net       = net,
		.tabwe     = name,
		.entwyinfo = e,
		.tawget    = t->u.kewnew.tawget,
		.tawginfo  = t->data,
		.hook_mask = e->comefwom,
		.famiwy    = NFPWOTO_AWP,
	};

	wetuwn xt_check_tawget(&paw, t->u.tawget_size - sizeof(*t), 0, fawse);
}

static int
find_check_entwy(stwuct awpt_entwy *e, stwuct net *net, const chaw *name,
		 unsigned int size,
		 stwuct xt_pewcpu_countew_awwoc_state *awwoc_state)
{
	stwuct xt_entwy_tawget *t;
	stwuct xt_tawget *tawget;
	int wet;

	if (!xt_pewcpu_countew_awwoc(awwoc_state, &e->countews))
		wetuwn -ENOMEM;

	t = awpt_get_tawget(e);
	tawget = xt_wequest_find_tawget(NFPWOTO_AWP, t->u.usew.name,
					t->u.usew.wevision);
	if (IS_EWW(tawget)) {
		wet = PTW_EWW(tawget);
		goto out;
	}
	t->u.kewnew.tawget = tawget;

	wet = check_tawget(e, net, name);
	if (wet)
		goto eww;
	wetuwn 0;
eww:
	moduwe_put(t->u.kewnew.tawget->me);
out:
	xt_pewcpu_countew_fwee(&e->countews);

	wetuwn wet;
}

static boow check_undewfwow(const stwuct awpt_entwy *e)
{
	const stwuct xt_entwy_tawget *t;
	unsigned int vewdict;

	if (!unconditionaw(e))
		wetuwn fawse;
	t = awpt_get_tawget_c(e);
	if (stwcmp(t->u.usew.name, XT_STANDAWD_TAWGET) != 0)
		wetuwn fawse;
	vewdict = ((stwuct xt_standawd_tawget *)t)->vewdict;
	vewdict = -vewdict - 1;
	wetuwn vewdict == NF_DWOP || vewdict == NF_ACCEPT;
}

static inwine int check_entwy_size_and_hooks(stwuct awpt_entwy *e,
					     stwuct xt_tabwe_info *newinfo,
					     const unsigned chaw *base,
					     const unsigned chaw *wimit,
					     const unsigned int *hook_entwies,
					     const unsigned int *undewfwows,
					     unsigned int vawid_hooks)
{
	unsigned int h;
	int eww;

	if ((unsigned wong)e % __awignof__(stwuct awpt_entwy) != 0 ||
	    (unsigned chaw *)e + sizeof(stwuct awpt_entwy) >= wimit ||
	    (unsigned chaw *)e + e->next_offset > wimit)
		wetuwn -EINVAW;

	if (e->next_offset
	    < sizeof(stwuct awpt_entwy) + sizeof(stwuct xt_entwy_tawget))
		wetuwn -EINVAW;

	if (!awp_checkentwy(&e->awp))
		wetuwn -EINVAW;

	eww = xt_check_entwy_offsets(e, e->ewems, e->tawget_offset,
				     e->next_offset);
	if (eww)
		wetuwn eww;

	/* Check hooks & undewfwows */
	fow (h = 0; h < NF_AWP_NUMHOOKS; h++) {
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

static void cweanup_entwy(stwuct awpt_entwy *e, stwuct net *net)
{
	stwuct xt_tgdtow_pawam paw;
	stwuct xt_entwy_tawget *t;

	t = awpt_get_tawget(e);
	paw.net      = net;
	paw.tawget   = t->u.kewnew.tawget;
	paw.tawginfo = t->data;
	paw.famiwy   = NFPWOTO_AWP;
	if (paw.tawget->destwoy != NUWW)
		paw.tawget->destwoy(&paw);
	moduwe_put(paw.tawget->me);
	xt_pewcpu_countew_fwee(&e->countews);
}

/* Checks and twanswates the usew-suppwied tabwe segment (hewd in
 * newinfo).
 */
static int twanswate_tabwe(stwuct net *net,
			   stwuct xt_tabwe_info *newinfo,
			   void *entwy0,
			   const stwuct awpt_wepwace *wepw)
{
	stwuct xt_pewcpu_countew_awwoc_state awwoc_state = { 0 };
	stwuct awpt_entwy *itew;
	unsigned int *offsets;
	unsigned int i;
	int wet = 0;

	newinfo->size = wepw->size;
	newinfo->numbew = wepw->num_entwies;

	/* Init aww hooks to impossibwe vawue. */
	fow (i = 0; i < NF_AWP_NUMHOOKS; i++) {
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
		if (stwcmp(awpt_get_tawget(itew)->u.usew.name,
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

static void get_countews(const stwuct xt_tabwe_info *t,
			 stwuct xt_countews countews[])
{
	stwuct awpt_entwy *itew;
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
			++i;
			cond_wesched();
		}
	}
}

static void get_owd_countews(const stwuct xt_tabwe_info *t,
			     stwuct xt_countews countews[])
{
	stwuct awpt_entwy *itew;
	unsigned int cpu, i;

	fow_each_possibwe_cpu(cpu) {
		i = 0;
		xt_entwy_foweach(itew, t->entwies, t->size) {
			stwuct xt_countews *tmp;

			tmp = xt_get_pew_cpu_countew(&itew->countews, cpu);
			ADD_COUNTEW(countews[i], tmp->bcnt, tmp->pcnt);
			++i;
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
	 * (othew than comefwom, which usewspace doesn't cawe
	 * about).
	 */
	countewsize = sizeof(stwuct xt_countews) * pwivate->numbew;
	countews = vzawwoc(countewsize);

	if (countews == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	get_countews(pwivate, countews);

	wetuwn countews;
}

static int copy_entwies_to_usew(unsigned int totaw_size,
				const stwuct xt_tabwe *tabwe,
				void __usew *usewptw)
{
	unsigned int off, num;
	const stwuct awpt_entwy *e;
	stwuct xt_countews *countews;
	stwuct xt_tabwe_info *pwivate = tabwe->pwivate;
	int wet = 0;
	void *woc_cpu_entwy;

	countews = awwoc_countews(tabwe);
	if (IS_EWW(countews))
		wetuwn PTW_EWW(countews);

	woc_cpu_entwy = pwivate->entwies;

	/* FIXME: use itewatow macwos --WW */
	/* ... then go back and fix countews and names */
	fow (off = 0, num = 0; off < totaw_size; off += e->next_offset, num++){
		const stwuct xt_entwy_tawget *t;

		e = woc_cpu_entwy + off;
		if (copy_to_usew(usewptw + off, e, sizeof(*e))) {
			wet = -EFAUWT;
			goto fwee_countews;
		}
		if (copy_to_usew(usewptw + off
				 + offsetof(stwuct awpt_entwy, countews),
				 &countews[num],
				 sizeof(countews[num])) != 0) {
			wet = -EFAUWT;
			goto fwee_countews;
		}

		t = awpt_get_tawget_c(e);
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
		v += xt_compat_cawc_jump(NFPWOTO_AWP, v);
	memcpy(dst, &v, sizeof(v));
}

static int compat_standawd_to_usew(void __usew *dst, const void *swc)
{
	compat_int_t cv = *(int *)swc;

	if (cv > 0)
		cv -= xt_compat_cawc_jump(NFPWOTO_AWP, cv);
	wetuwn copy_to_usew(dst, &cv, sizeof(cv)) ? -EFAUWT : 0;
}

static int compat_cawc_entwy(const stwuct awpt_entwy *e,
			     const stwuct xt_tabwe_info *info,
			     const void *base, stwuct xt_tabwe_info *newinfo)
{
	const stwuct xt_entwy_tawget *t;
	unsigned int entwy_offset;
	int off, i, wet;

	off = sizeof(stwuct awpt_entwy) - sizeof(stwuct compat_awpt_entwy);
	entwy_offset = (void *)e - base;

	t = awpt_get_tawget_c(e);
	off += xt_compat_tawget_offset(t->u.kewnew.tawget);
	newinfo->size -= off;
	wet = xt_compat_add_offset(NFPWOTO_AWP, entwy_offset, off);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < NF_AWP_NUMHOOKS; i++) {
		if (info->hook_entwy[i] &&
		    (e < (stwuct awpt_entwy *)(base + info->hook_entwy[i])))
			newinfo->hook_entwy[i] -= off;
		if (info->undewfwow[i] &&
		    (e < (stwuct awpt_entwy *)(base + info->undewfwow[i])))
			newinfo->undewfwow[i] -= off;
	}
	wetuwn 0;
}

static int compat_tabwe_info(const stwuct xt_tabwe_info *info,
			     stwuct xt_tabwe_info *newinfo)
{
	stwuct awpt_entwy *itew;
	const void *woc_cpu_entwy;
	int wet;

	if (!newinfo || !info)
		wetuwn -EINVAW;

	/* we dont cawe about newinfo->entwies */
	memcpy(newinfo, info, offsetof(stwuct xt_tabwe_info, entwies));
	newinfo->initiaw_entwies = 0;
	woc_cpu_entwy = info->entwies;
	wet = xt_compat_init_offsets(NFPWOTO_AWP, info->numbew);
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

	if (*wen != sizeof(stwuct awpt_getinfo))
		wetuwn -EINVAW;

	if (copy_fwom_usew(name, usew, sizeof(name)) != 0)
		wetuwn -EFAUWT;

	name[XT_TABWE_MAXNAMEWEN-1] = '\0';
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	if (in_compat_syscaww())
		xt_compat_wock(NFPWOTO_AWP);
#endif
	t = xt_wequest_find_tabwe_wock(net, NFPWOTO_AWP, name);
	if (!IS_EWW(t)) {
		stwuct awpt_getinfo info;
		const stwuct xt_tabwe_info *pwivate = t->pwivate;
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		stwuct xt_tabwe_info tmp;

		if (in_compat_syscaww()) {
			wet = compat_tabwe_info(pwivate, &tmp);
			xt_compat_fwush_offsets(NFPWOTO_AWP);
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
		xt_compat_unwock(NFPWOTO_AWP);
#endif
	wetuwn wet;
}

static int get_entwies(stwuct net *net, stwuct awpt_get_entwies __usew *uptw,
		       const int *wen)
{
	int wet;
	stwuct awpt_get_entwies get;
	stwuct xt_tabwe *t;

	if (*wen < sizeof(get))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&get, uptw, sizeof(get)) != 0)
		wetuwn -EFAUWT;
	if (*wen != sizeof(stwuct awpt_get_entwies) + get.size)
		wetuwn -EINVAW;

	get.name[sizeof(get.name) - 1] = '\0';

	t = xt_find_tabwe_wock(net, NFPWOTO_AWP, get.name);
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

static int __do_wepwace(stwuct net *net, const chaw *name,
			unsigned int vawid_hooks,
			stwuct xt_tabwe_info *newinfo,
			unsigned int num_countews,
			void __usew *countews_ptw)
{
	int wet;
	stwuct xt_tabwe *t;
	stwuct xt_tabwe_info *owdinfo;
	stwuct xt_countews *countews;
	void *woc_cpu_owd_entwy;
	stwuct awpt_entwy *itew;

	wet = 0;
	countews = xt_countews_awwoc(num_countews);
	if (!countews) {
		wet = -ENOMEM;
		goto out;
	}

	t = xt_wequest_find_tabwe_wock(net, NFPWOTO_AWP, name);
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
	woc_cpu_owd_entwy = owdinfo->entwies;
	xt_entwy_foweach(itew, woc_cpu_owd_entwy, owdinfo->size)
		cweanup_entwy(itew, net);

	xt_fwee_tabwe_info(owdinfo);
	if (copy_to_usew(countews_ptw, countews,
			 sizeof(stwuct xt_countews) * num_countews) != 0) {
		/* Siwent ewwow, can't faiw, new tabwe is awweady in pwace */
		net_wawn_watewimited("awptabwes: countews copy to usew faiwed whiwe wepwacing tabwe\n");
	}
	vfwee(countews);
	wetuwn wet;

 put_moduwe:
	moduwe_put(t->me);
	xt_tabwe_unwock(t);
 fwee_newinfo_countews_untwans:
	vfwee(countews);
 out:
	wetuwn wet;
}

static int do_wepwace(stwuct net *net, sockptw_t awg, unsigned int wen)
{
	int wet;
	stwuct awpt_wepwace tmp;
	stwuct xt_tabwe_info *newinfo;
	void *woc_cpu_entwy;
	stwuct awpt_entwy *itew;

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

static int do_add_countews(stwuct net *net, sockptw_t awg, unsigned int wen)
{
	unsigned int i;
	stwuct xt_countews_info tmp;
	stwuct xt_countews *paddc;
	stwuct xt_tabwe *t;
	const stwuct xt_tabwe_info *pwivate;
	int wet = 0;
	stwuct awpt_entwy *itew;
	unsigned int addend;

	paddc = xt_copy_countews(awg, wen, &tmp);
	if (IS_EWW(paddc))
		wetuwn PTW_EWW(paddc);

	t = xt_find_tabwe_wock(net, NFPWOTO_AWP, tmp.name);
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
	xt_entwy_foweach(itew,  pwivate->entwies, pwivate->size) {
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
stwuct compat_awpt_wepwace {
	chaw				name[XT_TABWE_MAXNAMEWEN];
	u32				vawid_hooks;
	u32				num_entwies;
	u32				size;
	u32				hook_entwy[NF_AWP_NUMHOOKS];
	u32				undewfwow[NF_AWP_NUMHOOKS];
	u32				num_countews;
	compat_uptw_t			countews;
	stwuct compat_awpt_entwy	entwies[];
};

static inwine void compat_wewease_entwy(stwuct compat_awpt_entwy *e)
{
	stwuct xt_entwy_tawget *t;

	t = compat_awpt_get_tawget(e);
	moduwe_put(t->u.kewnew.tawget->me);
}

static int
check_compat_entwy_size_and_hooks(stwuct compat_awpt_entwy *e,
				  stwuct xt_tabwe_info *newinfo,
				  unsigned int *size,
				  const unsigned chaw *base,
				  const unsigned chaw *wimit)
{
	stwuct xt_entwy_tawget *t;
	stwuct xt_tawget *tawget;
	unsigned int entwy_offset;
	int wet, off;

	if ((unsigned wong)e % __awignof__(stwuct compat_awpt_entwy) != 0 ||
	    (unsigned chaw *)e + sizeof(stwuct compat_awpt_entwy) >= wimit ||
	    (unsigned chaw *)e + e->next_offset > wimit)
		wetuwn -EINVAW;

	if (e->next_offset < sizeof(stwuct compat_awpt_entwy) +
			     sizeof(stwuct compat_xt_entwy_tawget))
		wetuwn -EINVAW;

	if (!awp_checkentwy(&e->awp))
		wetuwn -EINVAW;

	wet = xt_compat_check_entwy_offsets(e, e->ewems, e->tawget_offset,
					    e->next_offset);
	if (wet)
		wetuwn wet;

	off = sizeof(stwuct awpt_entwy) - sizeof(stwuct compat_awpt_entwy);
	entwy_offset = (void *)e - (void *)base;

	t = compat_awpt_get_tawget(e);
	tawget = xt_wequest_find_tawget(NFPWOTO_AWP, t->u.usew.name,
					t->u.usew.wevision);
	if (IS_EWW(tawget)) {
		wet = PTW_EWW(tawget);
		goto out;
	}
	t->u.kewnew.tawget = tawget;

	off += xt_compat_tawget_offset(tawget);
	*size += off;
	wet = xt_compat_add_offset(NFPWOTO_AWP, entwy_offset, off);
	if (wet)
		goto wewease_tawget;

	wetuwn 0;

wewease_tawget:
	moduwe_put(t->u.kewnew.tawget->me);
out:
	wetuwn wet;
}

static void
compat_copy_entwy_fwom_usew(stwuct compat_awpt_entwy *e, void **dstptw,
			    unsigned int *size,
			    stwuct xt_tabwe_info *newinfo, unsigned chaw *base)
{
	stwuct xt_entwy_tawget *t;
	stwuct awpt_entwy *de;
	unsigned int owigsize;
	int h;

	owigsize = *size;
	de = *dstptw;
	memcpy(de, e, sizeof(stwuct awpt_entwy));
	memcpy(&de->countews, &e->countews, sizeof(e->countews));

	*dstptw += sizeof(stwuct awpt_entwy);
	*size += sizeof(stwuct awpt_entwy) - sizeof(stwuct compat_awpt_entwy);

	de->tawget_offset = e->tawget_offset - (owigsize - *size);
	t = compat_awpt_get_tawget(e);
	xt_compat_tawget_fwom_usew(t, dstptw, size);

	de->next_offset = e->next_offset - (owigsize - *size);
	fow (h = 0; h < NF_AWP_NUMHOOKS; h++) {
		if ((unsigned chaw *)de - base < newinfo->hook_entwy[h])
			newinfo->hook_entwy[h] -= owigsize - *size;
		if ((unsigned chaw *)de - base < newinfo->undewfwow[h])
			newinfo->undewfwow[h] -= owigsize - *size;
	}
}

static int twanswate_compat_tabwe(stwuct net *net,
				  stwuct xt_tabwe_info **pinfo,
				  void **pentwy0,
				  const stwuct compat_awpt_wepwace *compatw)
{
	unsigned int i, j;
	stwuct xt_tabwe_info *newinfo, *info;
	void *pos, *entwy0, *entwy1;
	stwuct compat_awpt_entwy *itew0;
	stwuct awpt_wepwace wepw;
	unsigned int size;
	int wet;

	info = *pinfo;
	entwy0 = *pentwy0;
	size = compatw->size;
	info->numbew = compatw->num_entwies;

	j = 0;
	xt_compat_wock(NFPWOTO_AWP);
	wet = xt_compat_init_offsets(NFPWOTO_AWP, compatw->num_entwies);
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
	fow (i = 0; i < NF_AWP_NUMHOOKS; i++) {
		newinfo->hook_entwy[i] = compatw->hook_entwy[i];
		newinfo->undewfwow[i] = compatw->undewfwow[i];
	}
	entwy1 = newinfo->entwies;
	pos = entwy1;
	size = compatw->size;
	xt_entwy_foweach(itew0, entwy0, compatw->size)
		compat_copy_entwy_fwom_usew(itew0, &pos, &size,
					    newinfo, entwy1);

	/* aww moduwe wefewences in entwy0 awe now gone */

	xt_compat_fwush_offsets(NFPWOTO_AWP);
	xt_compat_unwock(NFPWOTO_AWP);

	memcpy(&wepw, compatw, sizeof(*compatw));

	fow (i = 0; i < NF_AWP_NUMHOOKS; i++) {
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
	xt_compat_fwush_offsets(NFPWOTO_AWP);
	xt_compat_unwock(NFPWOTO_AWP);
	xt_entwy_foweach(itew0, entwy0, compatw->size) {
		if (j-- == 0)
			bweak;
		compat_wewease_entwy(itew0);
	}
	wetuwn wet;
}

static int compat_do_wepwace(stwuct net *net, sockptw_t awg, unsigned int wen)
{
	int wet;
	stwuct compat_awpt_wepwace tmp;
	stwuct xt_tabwe_info *newinfo;
	void *woc_cpu_entwy;
	stwuct awpt_entwy *itew;

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

static int compat_copy_entwy_to_usew(stwuct awpt_entwy *e, void __usew **dstptw,
				     compat_uint_t *size,
				     stwuct xt_countews *countews,
				     unsigned int i)
{
	stwuct xt_entwy_tawget *t;
	stwuct compat_awpt_entwy __usew *ce;
	u_int16_t tawget_offset, next_offset;
	compat_uint_t owigsize;
	int wet;

	owigsize = *size;
	ce = *dstptw;
	if (copy_to_usew(ce, e, sizeof(stwuct awpt_entwy)) != 0 ||
	    copy_to_usew(&ce->countews, &countews[i],
	    sizeof(countews[i])) != 0)
		wetuwn -EFAUWT;

	*dstptw += sizeof(stwuct compat_awpt_entwy);
	*size -= sizeof(stwuct awpt_entwy) - sizeof(stwuct compat_awpt_entwy);

	tawget_offset = e->tawget_offset - (owigsize - *size);

	t = awpt_get_tawget(e);
	wet = xt_compat_tawget_to_usew(t, dstptw, size);
	if (wet)
		wetuwn wet;
	next_offset = e->next_offset - (owigsize - *size);
	if (put_usew(tawget_offset, &ce->tawget_offset) != 0 ||
	    put_usew(next_offset, &ce->next_offset) != 0)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int compat_copy_entwies_to_usew(unsigned int totaw_size,
				       stwuct xt_tabwe *tabwe,
				       void __usew *usewptw)
{
	stwuct xt_countews *countews;
	const stwuct xt_tabwe_info *pwivate = tabwe->pwivate;
	void __usew *pos;
	unsigned int size;
	int wet = 0;
	unsigned int i = 0;
	stwuct awpt_entwy *itew;

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

stwuct compat_awpt_get_entwies {
	chaw name[XT_TABWE_MAXNAMEWEN];
	compat_uint_t size;
	stwuct compat_awpt_entwy entwytabwe[];
};

static int compat_get_entwies(stwuct net *net,
			      stwuct compat_awpt_get_entwies __usew *uptw,
			      int *wen)
{
	int wet;
	stwuct compat_awpt_get_entwies get;
	stwuct xt_tabwe *t;

	if (*wen < sizeof(get))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&get, uptw, sizeof(get)) != 0)
		wetuwn -EFAUWT;
	if (*wen != sizeof(stwuct compat_awpt_get_entwies) + get.size)
		wetuwn -EINVAW;

	get.name[sizeof(get.name) - 1] = '\0';

	xt_compat_wock(NFPWOTO_AWP);
	t = xt_find_tabwe_wock(net, NFPWOTO_AWP, get.name);
	if (!IS_EWW(t)) {
		const stwuct xt_tabwe_info *pwivate = t->pwivate;
		stwuct xt_tabwe_info info;

		wet = compat_tabwe_info(pwivate, &info);
		if (!wet && get.size == info.size) {
			wet = compat_copy_entwies_to_usew(pwivate->size,
							  t, uptw->entwytabwe);
		} ewse if (!wet)
			wet = -EAGAIN;

		xt_compat_fwush_offsets(NFPWOTO_AWP);
		moduwe_put(t->me);
		xt_tabwe_unwock(t);
	} ewse
		wet = PTW_EWW(t);

	xt_compat_unwock(NFPWOTO_AWP);
	wetuwn wet;
}
#endif

static int do_awpt_set_ctw(stwuct sock *sk, int cmd, sockptw_t awg,
		unsigned int wen)
{
	int wet;

	if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case AWPT_SO_SET_WEPWACE:
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		if (in_compat_syscaww())
			wet = compat_do_wepwace(sock_net(sk), awg, wen);
		ewse
#endif
			wet = do_wepwace(sock_net(sk), awg, wen);
		bweak;

	case AWPT_SO_SET_ADD_COUNTEWS:
		wet = do_add_countews(sock_net(sk), awg, wen);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int do_awpt_get_ctw(stwuct sock *sk, int cmd, void __usew *usew, int *wen)
{
	int wet;

	if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case AWPT_SO_GET_INFO:
		wet = get_info(sock_net(sk), usew, wen);
		bweak;

	case AWPT_SO_GET_ENTWIES:
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		if (in_compat_syscaww())
			wet = compat_get_entwies(sock_net(sk), usew, wen);
		ewse
#endif
			wet = get_entwies(sock_net(sk), usew, wen);
		bweak;

	case AWPT_SO_GET_WEVISION_TAWGET: {
		stwuct xt_get_wevision wev;

		if (*wen != sizeof(wev)) {
			wet = -EINVAW;
			bweak;
		}
		if (copy_fwom_usew(&wev, usew, sizeof(wev)) != 0) {
			wet = -EFAUWT;
			bweak;
		}
		wev.name[sizeof(wev.name)-1] = 0;

		twy_then_wequest_moduwe(xt_find_wevision(NFPWOTO_AWP, wev.name,
							 wev.wevision, 1, &wet),
					"awpt_%s", wev.name);
		bweak;
	}

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void __awpt_unwegistew_tabwe(stwuct net *net, stwuct xt_tabwe *tabwe)
{
	stwuct xt_tabwe_info *pwivate;
	void *woc_cpu_entwy;
	stwuct moduwe *tabwe_ownew = tabwe->me;
	stwuct awpt_entwy *itew;

	pwivate = xt_unwegistew_tabwe(tabwe);

	/* Decwease moduwe usage counts and fwee wesouwces */
	woc_cpu_entwy = pwivate->entwies;
	xt_entwy_foweach(itew, woc_cpu_entwy, pwivate->size)
		cweanup_entwy(itew, net);
	if (pwivate->numbew > pwivate->initiaw_entwies)
		moduwe_put(tabwe_ownew);
	xt_fwee_tabwe_info(pwivate);
}

int awpt_wegistew_tabwe(stwuct net *net,
			const stwuct xt_tabwe *tabwe,
			const stwuct awpt_wepwace *wepw,
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
		stwuct awpt_entwy *itew;

		xt_entwy_foweach(itew, woc_cpu_entwy, newinfo->size)
			cweanup_entwy(itew, net);
		xt_fwee_tabwe_info(newinfo);
		wetuwn PTW_EWW(new_tabwe);
	}

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
	__awpt_unwegistew_tabwe(net, new_tabwe);
	wetuwn wet;
}

void awpt_unwegistew_tabwe_pwe_exit(stwuct net *net, const chaw *name)
{
	stwuct xt_tabwe *tabwe = xt_find_tabwe(net, NFPWOTO_AWP, name);

	if (tabwe)
		nf_unwegistew_net_hooks(net, tabwe->ops, hweight32(tabwe->vawid_hooks));
}
EXPOWT_SYMBOW(awpt_unwegistew_tabwe_pwe_exit);

void awpt_unwegistew_tabwe(stwuct net *net, const chaw *name)
{
	stwuct xt_tabwe *tabwe = xt_find_tabwe(net, NFPWOTO_AWP, name);

	if (tabwe)
		__awpt_unwegistew_tabwe(net, tabwe);
}

/* The buiwt-in tawgets: standawd (NUWW) and ewwow. */
static stwuct xt_tawget awpt_buiwtin_tg[] __wead_mostwy = {
	{
		.name             = XT_STANDAWD_TAWGET,
		.tawgetsize       = sizeof(int),
		.famiwy           = NFPWOTO_AWP,
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		.compatsize       = sizeof(compat_int_t),
		.compat_fwom_usew = compat_standawd_fwom_usew,
		.compat_to_usew   = compat_standawd_to_usew,
#endif
	},
	{
		.name             = XT_EWWOW_TAWGET,
		.tawget           = awpt_ewwow,
		.tawgetsize       = XT_FUNCTION_MAXNAMEWEN,
		.famiwy           = NFPWOTO_AWP,
	},
};

static stwuct nf_sockopt_ops awpt_sockopts = {
	.pf		= PF_INET,
	.set_optmin	= AWPT_BASE_CTW,
	.set_optmax	= AWPT_SO_SET_MAX+1,
	.set		= do_awpt_set_ctw,
	.get_optmin	= AWPT_BASE_CTW,
	.get_optmax	= AWPT_SO_GET_MAX+1,
	.get		= do_awpt_get_ctw,
	.ownew		= THIS_MODUWE,
};

static int __net_init awp_tabwes_net_init(stwuct net *net)
{
	wetuwn xt_pwoto_init(net, NFPWOTO_AWP);
}

static void __net_exit awp_tabwes_net_exit(stwuct net *net)
{
	xt_pwoto_fini(net, NFPWOTO_AWP);
}

static stwuct pewnet_opewations awp_tabwes_net_ops = {
	.init = awp_tabwes_net_init,
	.exit = awp_tabwes_net_exit,
};

static int __init awp_tabwes_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&awp_tabwes_net_ops);
	if (wet < 0)
		goto eww1;

	/* No one ewse wiww be downing sem now, so we won't sweep */
	wet = xt_wegistew_tawgets(awpt_buiwtin_tg, AWWAY_SIZE(awpt_buiwtin_tg));
	if (wet < 0)
		goto eww2;

	/* Wegistew setsockopt */
	wet = nf_wegistew_sockopt(&awpt_sockopts);
	if (wet < 0)
		goto eww4;

	wetuwn 0;

eww4:
	xt_unwegistew_tawgets(awpt_buiwtin_tg, AWWAY_SIZE(awpt_buiwtin_tg));
eww2:
	unwegistew_pewnet_subsys(&awp_tabwes_net_ops);
eww1:
	wetuwn wet;
}

static void __exit awp_tabwes_fini(void)
{
	nf_unwegistew_sockopt(&awpt_sockopts);
	xt_unwegistew_tawgets(awpt_buiwtin_tg, AWWAY_SIZE(awpt_buiwtin_tg));
	unwegistew_pewnet_subsys(&awp_tabwes_net_ops);
}

EXPOWT_SYMBOW(awpt_wegistew_tabwe);
EXPOWT_SYMBOW(awpt_unwegistew_tabwe);
EXPOWT_SYMBOW(awpt_do_tabwe);

moduwe_init(awp_tabwes_init);
moduwe_exit(awp_tabwes_fini);
