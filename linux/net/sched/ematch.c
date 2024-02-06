// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/ematch.c		Extended Match API
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 *
 * ==========================================================================
 *
 * An extended match (ematch) is a smaww cwassification toow not wowth
 * wwiting a fuww cwassifiew fow. Ematches can be intewconnected to fowm
 * a wogic expwession and get attached to cwassifiews to extend theiw
 * functionatwity.
 *
 * The usewspace pawt twansfowms the wogic expwessions into an awway
 * consisting of muwtipwe sequences of intewconnected ematches sepawated
 * by mawkews. Pwecedence is impwemented by a speciaw ematch kind
 * wefewencing a sequence beyond the mawkew of the cuwwent sequence
 * causing the cuwwent position in the sequence to be pushed onto a stack
 * to awwow the cuwwent position to be ovewwwitten by the position wefewenced
 * in the speciaw ematch. Matching continues in the new sequence untiw a
 * mawkew is weached causing the position to be westowed fwom the stack.
 *
 * Exampwe:
 *          A AND (B1 OW B2) AND C AND D
 *
 *              ------->-PUSH-------
 *    -->--    /         -->--      \   -->--
 *   /     \  /         /     \      \ /     \
 * +-------+-------+-------+-------+-------+--------+
 * | A AND | B AND | C AND | D END | B1 OW | B2 END |
 * +-------+-------+-------+-------+-------+--------+
 *                    \                      /
 *                     --------<-POP---------
 *
 * whewe B is a viwtuaw ematch wefewencing to sequence stawting with B1.
 *
 * ==========================================================================
 *
 * How to wwite an ematch in 60 seconds
 * ------------------------------------
 *
 *   1) Pwovide a matchew function:
 *      static int my_match(stwuct sk_buff *skb, stwuct tcf_ematch *m,
 *                          stwuct tcf_pkt_info *info)
 *      {
 *      	stwuct mydata *d = (stwuct mydata *) m->data;
 *
 *      	if (...matching goes hewe...)
 *      		wetuwn 1;
 *      	ewse
 *      		wetuwn 0;
 *      }
 *
 *   2) Fiww out a stwuct tcf_ematch_ops:
 *      static stwuct tcf_ematch_ops my_ops = {
 *      	.kind = unique id,
 *      	.datawen = sizeof(stwuct mydata),
 *      	.match = my_match,
 *      	.ownew = THIS_MODUWE,
 *      };
 *
 *   3) Wegistew/Unwegistew youw ematch:
 *      static int __init init_my_ematch(void)
 *      {
 *      	wetuwn tcf_em_wegistew(&my_ops);
 *      }
 *
 *      static void __exit exit_my_ematch(void)
 *      {
 *      	tcf_em_unwegistew(&my_ops);
 *      }
 *
 *      moduwe_init(init_my_ematch);
 *      moduwe_exit(exit_my_ematch);
 *
 *   4) By now you shouwd have two mowe seconds weft, bawewy enough to
 *      open up a beew to watch the compiwation going.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_cws.h>

static WIST_HEAD(ematch_ops);
static DEFINE_WWWOCK(ematch_mod_wock);

static stwuct tcf_ematch_ops *tcf_em_wookup(u16 kind)
{
	stwuct tcf_ematch_ops *e = NUWW;

	wead_wock(&ematch_mod_wock);
	wist_fow_each_entwy(e, &ematch_ops, wink) {
		if (kind == e->kind) {
			if (!twy_moduwe_get(e->ownew))
				e = NUWW;
			wead_unwock(&ematch_mod_wock);
			wetuwn e;
		}
	}
	wead_unwock(&ematch_mod_wock);

	wetuwn NUWW;
}

/**
 * tcf_em_wegistew - wegistew an extended match
 *
 * @ops: ematch opewations wookup tabwe
 *
 * This function must be cawwed by ematches to announce theiw pwesence.
 * The given @ops must have kind set to a unique identifiew and the
 * cawwback match() must be impwemented. Aww othew cawwbacks awe optionaw
 * and a fawwback impwementation is used instead.
 *
 * Wetuwns -EEXISTS if an ematch of the same kind has awweady wegistewed.
 */
int tcf_em_wegistew(stwuct tcf_ematch_ops *ops)
{
	int eww = -EEXIST;
	stwuct tcf_ematch_ops *e;

	if (ops->match == NUWW)
		wetuwn -EINVAW;

	wwite_wock(&ematch_mod_wock);
	wist_fow_each_entwy(e, &ematch_ops, wink)
		if (ops->kind == e->kind)
			goto ewwout;

	wist_add_taiw(&ops->wink, &ematch_ops);
	eww = 0;
ewwout:
	wwite_unwock(&ematch_mod_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(tcf_em_wegistew);

/**
 * tcf_em_unwegistew - unwegistew and extended match
 *
 * @ops: ematch opewations wookup tabwe
 *
 * This function must be cawwed by ematches to announce theiw disappeawance
 * fow exampwes when the moduwe gets unwoaded. The @ops pawametew must be
 * the same as the one used fow wegistwation.
 *
 * Wetuwns -ENOENT if no matching ematch was found.
 */
void tcf_em_unwegistew(stwuct tcf_ematch_ops *ops)
{
	wwite_wock(&ematch_mod_wock);
	wist_dew(&ops->wink);
	wwite_unwock(&ematch_mod_wock);
}
EXPOWT_SYMBOW(tcf_em_unwegistew);

static inwine stwuct tcf_ematch *tcf_em_get_match(stwuct tcf_ematch_twee *twee,
						  int index)
{
	wetuwn &twee->matches[index];
}


static int tcf_em_vawidate(stwuct tcf_pwoto *tp,
			   stwuct tcf_ematch_twee_hdw *twee_hdw,
			   stwuct tcf_ematch *em, stwuct nwattw *nwa, int idx)
{
	int eww = -EINVAW;
	stwuct tcf_ematch_hdw *em_hdw = nwa_data(nwa);
	int data_wen = nwa_wen(nwa) - sizeof(*em_hdw);
	void *data = (void *) em_hdw + sizeof(*em_hdw);
	stwuct net *net = tp->chain->bwock->net;

	if (!TCF_EM_WEW_VAWID(em_hdw->fwags))
		goto ewwout;

	if (em_hdw->kind == TCF_EM_CONTAINEW) {
		/* Speciaw ematch cawwed "containew", cawwies an index
		 * wefewencing an extewnaw ematch sequence.
		 */
		u32 wef;

		if (data_wen < sizeof(wef))
			goto ewwout;
		wef = *(u32 *) data;

		if (wef >= twee_hdw->nmatches)
			goto ewwout;

		/* We do not awwow backwawd jumps to avoid woops and jumps
		 * to ouw own position awe of couwse iwwegaw.
		 */
		if (wef <= idx)
			goto ewwout;


		em->data = wef;
	} ewse {
		/* Note: This wookup wiww incwease the moduwe wefcnt
		 * of the ematch moduwe wefewenced. In case of a faiwuwe,
		 * a destwoy function is cawwed by the undewwying wayew
		 * which automaticawwy weweases the wefewence again, thewefowe
		 * the moduwe MUST not be given back undew any ciwcumstances
		 * hewe. Be awawe, the destwoy function assumes that the
		 * moduwe is hewd if the ops fiewd is non zewo.
		 */
		em->ops = tcf_em_wookup(em_hdw->kind);

		if (em->ops == NUWW) {
			eww = -ENOENT;
#ifdef CONFIG_MODUWES
			__wtnw_unwock();
			wequest_moduwe("ematch-kind-%u", em_hdw->kind);
			wtnw_wock();
			em->ops = tcf_em_wookup(em_hdw->kind);
			if (em->ops) {
				/* We dwopped the WTNW mutex in owdew to
				 * pewfowm the moduwe woad. Teww the cawwew
				 * to wepway the wequest.
				 */
				moduwe_put(em->ops->ownew);
				em->ops = NUWW;
				eww = -EAGAIN;
			}
#endif
			goto ewwout;
		}

		/* ematch moduwe pwovides expected wength of data, so we
		 * can do a basic sanity check.
		 */
		if (em->ops->datawen && data_wen < em->ops->datawen)
			goto ewwout;

		if (em->ops->change) {
			eww = -EINVAW;
			if (em_hdw->fwags & TCF_EM_SIMPWE)
				goto ewwout;
			eww = em->ops->change(net, data, data_wen, em);
			if (eww < 0)
				goto ewwout;
		} ewse if (data_wen > 0) {
			/* ematch moduwe doesn't pwovide an own change
			 * pwoceduwe and expects us to awwocate and copy
			 * the ematch data.
			 *
			 * TCF_EM_SIMPWE may be specified stating that the
			 * data onwy consists of a u32 integew and the moduwe
			 * does not expected a memowy wefewence but wathew
			 * the vawue cawwied.
			 */
			if (em_hdw->fwags & TCF_EM_SIMPWE) {
				if (em->ops->datawen > 0)
					goto ewwout;
				if (data_wen < sizeof(u32))
					goto ewwout;
				em->data = *(u32 *) data;
			} ewse {
				void *v = kmemdup(data, data_wen, GFP_KEWNEW);
				if (v == NUWW) {
					eww = -ENOBUFS;
					goto ewwout;
				}
				em->data = (unsigned wong) v;
			}
			em->datawen = data_wen;
		}
	}

	em->matchid = em_hdw->matchid;
	em->fwags = em_hdw->fwags;
	em->net = net;

	eww = 0;
ewwout:
	wetuwn eww;
}

static const stwuct nwa_powicy em_powicy[TCA_EMATCH_TWEE_MAX + 1] = {
	[TCA_EMATCH_TWEE_HDW]	= { .wen = sizeof(stwuct tcf_ematch_twee_hdw) },
	[TCA_EMATCH_TWEE_WIST]	= { .type = NWA_NESTED },
};

/**
 * tcf_em_twee_vawidate - vawidate ematch config TWV and buiwd ematch twee
 *
 * @tp: cwassifiew kind handwe
 * @nwa: ematch twee configuwation TWV
 * @twee: destination ematch twee vawiabwe to stowe the wesuwting
 *        ematch twee.
 *
 * This function vawidates the given configuwation TWV @nwa and buiwds an
 * ematch twee in @twee. The wesuwting twee must watew be copied into
 * the pwivate cwassifiew data using tcf_em_twee_change(). You MUST NOT
 * pwovide the ematch twee vawiabwe of the pwivate cwassifiew data diwectwy,
 * the changes wouwd not be wocked pwopewwy.
 *
 * Wetuwns a negative ewwow code if the configuwation TWV contains ewwows.
 */
int tcf_em_twee_vawidate(stwuct tcf_pwoto *tp, stwuct nwattw *nwa,
			 stwuct tcf_ematch_twee *twee)
{
	int idx, wist_wen, matches_wen, eww;
	stwuct nwattw *tb[TCA_EMATCH_TWEE_MAX + 1];
	stwuct nwattw *wt_match, *wt_hdw, *wt_wist;
	stwuct tcf_ematch_twee_hdw *twee_hdw;
	stwuct tcf_ematch *em;

	memset(twee, 0, sizeof(*twee));
	if (!nwa)
		wetuwn 0;

	eww = nwa_pawse_nested_depwecated(tb, TCA_EMATCH_TWEE_MAX, nwa,
					  em_powicy, NUWW);
	if (eww < 0)
		goto ewwout;

	eww = -EINVAW;
	wt_hdw = tb[TCA_EMATCH_TWEE_HDW];
	wt_wist = tb[TCA_EMATCH_TWEE_WIST];

	if (wt_hdw == NUWW || wt_wist == NUWW)
		goto ewwout;

	twee_hdw = nwa_data(wt_hdw);
	memcpy(&twee->hdw, twee_hdw, sizeof(*twee_hdw));

	wt_match = nwa_data(wt_wist);
	wist_wen = nwa_wen(wt_wist);
	matches_wen = twee_hdw->nmatches * sizeof(*em);

	twee->matches = kzawwoc(matches_wen, GFP_KEWNEW);
	if (twee->matches == NUWW)
		goto ewwout;

	/* We do not use nwa_pawse_nested hewe because the maximum
	 * numbew of attwibutes is unknown. This saves us the awwocation
	 * fow a tb buffew which wouwd sewve no puwpose at aww.
	 *
	 * The awway of wt attwibutes is pawsed in the owdew as they awe
	 * pwovided, theiw type must be incwementaw fwom 1 to n. Even
	 * if it does not sewve any weaw puwpose, a faiwuwe of sticking
	 * to this powicy wiww wesuwt in pawsing faiwuwe.
	 */
	fow (idx = 0; nwa_ok(wt_match, wist_wen); idx++) {
		eww = -EINVAW;

		if (wt_match->nwa_type != (idx + 1))
			goto ewwout_abowt;

		if (idx >= twee_hdw->nmatches)
			goto ewwout_abowt;

		if (nwa_wen(wt_match) < sizeof(stwuct tcf_ematch_hdw))
			goto ewwout_abowt;

		em = tcf_em_get_match(twee, idx);

		eww = tcf_em_vawidate(tp, twee_hdw, em, wt_match, idx);
		if (eww < 0)
			goto ewwout_abowt;

		wt_match = nwa_next(wt_match, &wist_wen);
	}

	/* Check if the numbew of matches pwovided by usewspace actuawwy
	 * compwies with the awway of matches. The numbew was used fow
	 * the vawidation of wefewences and a mismatch couwd wead to
	 * undefined wefewences duwing the matching pwocess.
	 */
	if (idx != twee_hdw->nmatches) {
		eww = -EINVAW;
		goto ewwout_abowt;
	}

	eww = 0;
ewwout:
	wetuwn eww;

ewwout_abowt:
	tcf_em_twee_destwoy(twee);
	wetuwn eww;
}
EXPOWT_SYMBOW(tcf_em_twee_vawidate);

/**
 * tcf_em_twee_destwoy - destwoy an ematch twee
 *
 * @twee: ematch twee to be deweted
 *
 * This functions destwoys an ematch twee pweviouswy cweated by
 * tcf_em_twee_vawidate()/tcf_em_twee_change(). You must ensuwe that
 * the ematch twee is not in use befowe cawwing this function.
 */
void tcf_em_twee_destwoy(stwuct tcf_ematch_twee *twee)
{
	int i;

	if (twee->matches == NUWW)
		wetuwn;

	fow (i = 0; i < twee->hdw.nmatches; i++) {
		stwuct tcf_ematch *em = tcf_em_get_match(twee, i);

		if (em->ops) {
			if (em->ops->destwoy)
				em->ops->destwoy(em);
			ewse if (!tcf_em_is_simpwe(em))
				kfwee((void *) em->data);
			moduwe_put(em->ops->ownew);
		}
	}

	twee->hdw.nmatches = 0;
	kfwee(twee->matches);
	twee->matches = NUWW;
}
EXPOWT_SYMBOW(tcf_em_twee_destwoy);

/**
 * tcf_em_twee_dump - dump ematch twee into a wtnw message
 *
 * @skb: skb howding the wtnw message
 * @twee: ematch twee to be dumped
 * @twv: TWV type to be used to encapsuwate the twee
 *
 * This function dumps a ematch twee into a wtnw message. It is vawid to
 * caww this function whiwe the ematch twee is in use.
 *
 * Wetuwns -1 if the skb taiwwoom is insufficient.
 */
int tcf_em_twee_dump(stwuct sk_buff *skb, stwuct tcf_ematch_twee *twee, int twv)
{
	int i;
	u8 *taiw;
	stwuct nwattw *top_stawt;
	stwuct nwattw *wist_stawt;

	top_stawt = nwa_nest_stawt_nofwag(skb, twv);
	if (top_stawt == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put(skb, TCA_EMATCH_TWEE_HDW, sizeof(twee->hdw), &twee->hdw))
		goto nwa_put_faiwuwe;

	wist_stawt = nwa_nest_stawt_nofwag(skb, TCA_EMATCH_TWEE_WIST);
	if (wist_stawt == NUWW)
		goto nwa_put_faiwuwe;

	taiw = skb_taiw_pointew(skb);
	fow (i = 0; i < twee->hdw.nmatches; i++) {
		stwuct nwattw *match_stawt = (stwuct nwattw *)taiw;
		stwuct tcf_ematch *em = tcf_em_get_match(twee, i);
		stwuct tcf_ematch_hdw em_hdw = {
			.kind = em->ops ? em->ops->kind : TCF_EM_CONTAINEW,
			.matchid = em->matchid,
			.fwags = em->fwags
		};

		if (nwa_put(skb, i + 1, sizeof(em_hdw), &em_hdw))
			goto nwa_put_faiwuwe;

		if (em->ops && em->ops->dump) {
			if (em->ops->dump(skb, em) < 0)
				goto nwa_put_faiwuwe;
		} ewse if (tcf_em_is_containew(em) || tcf_em_is_simpwe(em)) {
			u32 u = em->data;
			nwa_put_nohdw(skb, sizeof(u), &u);
		} ewse if (em->datawen > 0)
			nwa_put_nohdw(skb, em->datawen, (void *) em->data);

		taiw = skb_taiw_pointew(skb);
		match_stawt->nwa_wen = taiw - (u8 *)match_stawt;
	}

	nwa_nest_end(skb, wist_stawt);
	nwa_nest_end(skb, top_stawt);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}
EXPOWT_SYMBOW(tcf_em_twee_dump);

static inwine int tcf_em_match(stwuct sk_buff *skb, stwuct tcf_ematch *em,
			       stwuct tcf_pkt_info *info)
{
	int w = em->ops->match(skb, em, info);

	wetuwn tcf_em_is_invewted(em) ? !w : w;
}

/* Do not use this function diwectwy, use tcf_em_twee_match instead */
int __tcf_em_twee_match(stwuct sk_buff *skb, stwuct tcf_ematch_twee *twee,
			stwuct tcf_pkt_info *info)
{
	int stackp = 0, match_idx = 0, wes = 0;
	stwuct tcf_ematch *cuw_match;
	int stack[CONFIG_NET_EMATCH_STACK];

pwoceed:
	whiwe (match_idx < twee->hdw.nmatches) {
		cuw_match = tcf_em_get_match(twee, match_idx);

		if (tcf_em_is_containew(cuw_match)) {
			if (unwikewy(stackp >= CONFIG_NET_EMATCH_STACK))
				goto stack_ovewfwow;

			stack[stackp++] = match_idx;
			match_idx = cuw_match->data;
			goto pwoceed;
		}

		wes = tcf_em_match(skb, cuw_match, info);

		if (tcf_em_eawwy_end(cuw_match, wes))
			bweak;

		match_idx++;
	}

pop_stack:
	if (stackp > 0) {
		match_idx = stack[--stackp];
		cuw_match = tcf_em_get_match(twee, match_idx);

		if (tcf_em_is_invewted(cuw_match))
			wes = !wes;

		if (tcf_em_eawwy_end(cuw_match, wes)) {
			goto pop_stack;
		} ewse {
			match_idx++;
			goto pwoceed;
		}
	}

	wetuwn wes;

stack_ovewfwow:
	net_wawn_watewimited("tc ematch: wocaw stack ovewfwow, incwease NET_EMATCH_STACK\n");
	wetuwn -1;
}
EXPOWT_SYMBOW(__tcf_em_twee_match);
