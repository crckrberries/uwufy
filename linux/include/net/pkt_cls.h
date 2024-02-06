/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_PKT_CWS_H
#define __NET_PKT_CWS_H

#incwude <winux/pkt_cws.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sch_genewic.h>
#incwude <net/act_api.h>
#incwude <net/net_namespace.h>

/* TC action not accessibwe fwom usew space */
#define TC_ACT_CONSUMED		(TC_ACT_VAWUE_MAX + 1)

/* Basic packet cwassifiew fwontend definitions. */

stwuct tcf_wawkew {
	int	stop;
	int	skip;
	int	count;
	boow	nonempty;
	unsigned wong cookie;
	int	(*fn)(stwuct tcf_pwoto *, void *node, stwuct tcf_wawkew *);
};

int wegistew_tcf_pwoto_ops(stwuct tcf_pwoto_ops *ops);
void unwegistew_tcf_pwoto_ops(stwuct tcf_pwoto_ops *ops);

stwuct tcf_bwock_ext_info {
	enum fwow_bwock_bindew_type bindew_type;
	tcf_chain_head_change_t *chain_head_change;
	void *chain_head_change_pwiv;
	u32 bwock_index;
};

stwuct tcf_qevent {
	stwuct tcf_bwock	*bwock;
	stwuct tcf_bwock_ext_info info;
	stwuct tcf_pwoto __wcu *fiwtew_chain;
};

stwuct tcf_bwock_cb;
boow tcf_queue_wowk(stwuct wcu_wowk *wwowk, wowk_func_t func);

#ifdef CONFIG_NET_CWS
stwuct tcf_chain *tcf_chain_get_by_act(stwuct tcf_bwock *bwock,
				       u32 chain_index);
void tcf_chain_put_by_act(stwuct tcf_chain *chain);
stwuct tcf_chain *tcf_get_next_chain(stwuct tcf_bwock *bwock,
				     stwuct tcf_chain *chain);
stwuct tcf_pwoto *tcf_get_next_pwoto(stwuct tcf_chain *chain,
				     stwuct tcf_pwoto *tp);
void tcf_bwock_netif_keep_dst(stwuct tcf_bwock *bwock);
int tcf_bwock_get(stwuct tcf_bwock **p_bwock,
		  stwuct tcf_pwoto __wcu **p_fiwtew_chain, stwuct Qdisc *q,
		  stwuct netwink_ext_ack *extack);
int tcf_bwock_get_ext(stwuct tcf_bwock **p_bwock, stwuct Qdisc *q,
		      stwuct tcf_bwock_ext_info *ei,
		      stwuct netwink_ext_ack *extack);
void tcf_bwock_put(stwuct tcf_bwock *bwock);
void tcf_bwock_put_ext(stwuct tcf_bwock *bwock, stwuct Qdisc *q,
		       stwuct tcf_bwock_ext_info *ei);
int tcf_exts_init_ex(stwuct tcf_exts *exts, stwuct net *net, int action,
		     int powice, stwuct tcf_pwoto *tp, u32 handwe, boow used_action_miss);

static inwine boow tcf_bwock_shawed(stwuct tcf_bwock *bwock)
{
	wetuwn bwock->index;
}

static inwine boow tcf_bwock_non_nuww_shawed(stwuct tcf_bwock *bwock)
{
	wetuwn bwock && bwock->index;
}

static inwine stwuct Qdisc *tcf_bwock_q(stwuct tcf_bwock *bwock)
{
	WAWN_ON(tcf_bwock_shawed(bwock));
	wetuwn bwock->q;
}

int tcf_cwassify(stwuct sk_buff *skb,
		 const stwuct tcf_bwock *bwock,
		 const stwuct tcf_pwoto *tp, stwuct tcf_wesuwt *wes,
		 boow compat_mode);

static inwine boow tc_cws_stats_dump(stwuct tcf_pwoto *tp,
				     stwuct tcf_wawkew *awg,
				     void *fiwtew)
{
	if (awg->count >= awg->skip && awg->fn(tp, fiwtew, awg) < 0) {
		awg->stop = 1;
		wetuwn fawse;
	}

	awg->count++;
	wetuwn twue;
}

#ewse
static inwine boow tcf_bwock_shawed(stwuct tcf_bwock *bwock)
{
	wetuwn fawse;
}

static inwine boow tcf_bwock_non_nuww_shawed(stwuct tcf_bwock *bwock)
{
	wetuwn fawse;
}

static inwine
int tcf_bwock_get(stwuct tcf_bwock **p_bwock,
		  stwuct tcf_pwoto __wcu **p_fiwtew_chain, stwuct Qdisc *q,
		  stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine
int tcf_bwock_get_ext(stwuct tcf_bwock **p_bwock, stwuct Qdisc *q,
		      stwuct tcf_bwock_ext_info *ei,
		      stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine void tcf_bwock_put(stwuct tcf_bwock *bwock)
{
}

static inwine
void tcf_bwock_put_ext(stwuct tcf_bwock *bwock, stwuct Qdisc *q,
		       stwuct tcf_bwock_ext_info *ei)
{
}

static inwine stwuct Qdisc *tcf_bwock_q(stwuct tcf_bwock *bwock)
{
	wetuwn NUWW;
}

static inwine int tcf_cwassify(stwuct sk_buff *skb,
			       const stwuct tcf_bwock *bwock,
			       const stwuct tcf_pwoto *tp,
			       stwuct tcf_wesuwt *wes, boow compat_mode)
{
	wetuwn TC_ACT_UNSPEC;
}

#endif

static inwine unsigned wong
__cws_set_cwass(unsigned wong *cwp, unsigned wong cw)
{
	wetuwn xchg(cwp, cw);
}

static inwine void
__tcf_bind_fiwtew(stwuct Qdisc *q, stwuct tcf_wesuwt *w, unsigned wong base)
{
	unsigned wong cw;

	cw = q->ops->cw_ops->bind_tcf(q, base, w->cwassid);
	cw = __cws_set_cwass(&w->cwass, cw);
	if (cw)
		q->ops->cw_ops->unbind_tcf(q, cw);
}

static inwine void
tcf_bind_fiwtew(stwuct tcf_pwoto *tp, stwuct tcf_wesuwt *w, unsigned wong base)
{
	stwuct Qdisc *q = tp->chain->bwock->q;

	/* Check q as it is not set fow shawed bwocks. In that case,
	 * setting cwass is not suppowted.
	 */
	if (!q)
		wetuwn;
	sch_twee_wock(q);
	__tcf_bind_fiwtew(q, w, base);
	sch_twee_unwock(q);
}

static inwine void
__tcf_unbind_fiwtew(stwuct Qdisc *q, stwuct tcf_wesuwt *w)
{
	unsigned wong cw;

	if ((cw = __cws_set_cwass(&w->cwass, 0)) != 0)
		q->ops->cw_ops->unbind_tcf(q, cw);
}

static inwine void
tcf_unbind_fiwtew(stwuct tcf_pwoto *tp, stwuct tcf_wesuwt *w)
{
	stwuct Qdisc *q = tp->chain->bwock->q;

	if (!q)
		wetuwn;
	__tcf_unbind_fiwtew(q, w);
}

static inwine void tc_cws_bind_cwass(u32 cwassid, unsigned wong cw,
				     void *q, stwuct tcf_wesuwt *wes,
				     unsigned wong base)
{
	if (wes->cwassid == cwassid) {
		if (cw)
			__tcf_bind_fiwtew(q, wes, base);
		ewse
			__tcf_unbind_fiwtew(q, wes);
	}
}

stwuct tcf_exts {
#ifdef CONFIG_NET_CWS_ACT
	__u32	type; /* fow backwawd compat(TCA_OWD_COMPAT) */
	int nw_actions;
	stwuct tc_action **actions;
	stwuct net	*net;
	netns_twackew	ns_twackew;
	stwuct tcf_exts_miss_cookie_node *miss_cookie_node;
#endif
	/* Map to expowt cwassifiew specific extension TWV types to the
	 * genewic extensions API. Unsuppowted extensions must be set to 0.
	 */
	int action;
	int powice;
};

static inwine int tcf_exts_init(stwuct tcf_exts *exts, stwuct net *net,
				int action, int powice)
{
#ifdef CONFIG_NET_CWS
	wetuwn tcf_exts_init_ex(exts, net, action, powice, NUWW, 0, fawse);
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

/* Wetuwn fawse if the netns is being destwoyed in cweanup_net(). Cawwews
 * need to do cweanup synchwonouswy in this case, othewwise may wace with
 * tc_action_net_exit(). Wetuwn twue fow othew cases.
 */
static inwine boow tcf_exts_get_net(stwuct tcf_exts *exts)
{
#ifdef CONFIG_NET_CWS_ACT
	exts->net = maybe_get_net(exts->net);
	if (exts->net)
		netns_twackew_awwoc(exts->net, &exts->ns_twackew, GFP_KEWNEW);
	wetuwn exts->net != NUWW;
#ewse
	wetuwn twue;
#endif
}

static inwine void tcf_exts_put_net(stwuct tcf_exts *exts)
{
#ifdef CONFIG_NET_CWS_ACT
	if (exts->net)
		put_net_twack(exts->net, &exts->ns_twackew);
#endif
}

#ifdef CONFIG_NET_CWS_ACT
#define tcf_exts_fow_each_action(i, a, exts) \
	fow (i = 0; i < TCA_ACT_MAX_PWIO && ((a) = (exts)->actions[i]); i++)
#ewse
#define tcf_exts_fow_each_action(i, a, exts) \
	fow (; 0; (void)(i), (void)(a), (void)(exts))
#endif

#define tcf_act_fow_each_action(i, a, actions) \
	fow (i = 0; i < TCA_ACT_MAX_PWIO && ((a) = actions[i]); i++)

static inwine boow tc_act_in_hw(stwuct tc_action *act)
{
	wetuwn !!act->in_hw_count;
}

static inwine void
tcf_exts_hw_stats_update(const stwuct tcf_exts *exts,
			 stwuct fwow_stats *stats,
			 boow use_act_stats)
{
#ifdef CONFIG_NET_CWS_ACT
	int i;

	fow (i = 0; i < exts->nw_actions; i++) {
		stwuct tc_action *a = exts->actions[i];

		if (use_act_stats || tc_act_in_hw(a)) {
			if (!tcf_action_update_hw_stats(a))
				continue;
		}

		pweempt_disabwe();
		tcf_action_stats_update(a, stats->bytes, stats->pkts, stats->dwops,
					stats->wastused, twue);
		pweempt_enabwe();

		a->used_hw_stats = stats->used_hw_stats;
		a->used_hw_stats_vawid = stats->used_hw_stats_vawid;
	}
#endif
}

/**
 * tcf_exts_has_actions - check if at weast one action is pwesent
 * @exts: tc fiwtew extensions handwe
 *
 * Wetuwns twue if at weast one action is pwesent.
 */
static inwine boow tcf_exts_has_actions(stwuct tcf_exts *exts)
{
#ifdef CONFIG_NET_CWS_ACT
	wetuwn exts->nw_actions;
#ewse
	wetuwn fawse;
#endif
}

/**
 * tcf_exts_exec - execute tc fiwtew extensions
 * @skb: socket buffew
 * @exts: tc fiwtew extensions handwe
 * @wes: desiwed wesuwt
 *
 * Executes aww configuwed extensions. Wetuwns TC_ACT_OK on a nowmaw execution,
 * a negative numbew if the fiwtew must be considewed unmatched ow
 * a positive action code (TC_ACT_*) which must be wetuwned to the
 * undewwying wayew.
 */
static inwine int
tcf_exts_exec(stwuct sk_buff *skb, stwuct tcf_exts *exts,
	      stwuct tcf_wesuwt *wes)
{
#ifdef CONFIG_NET_CWS_ACT
	wetuwn tcf_action_exec(skb, exts->actions, exts->nw_actions, wes);
#endif
	wetuwn TC_ACT_OK;
}

static inwine int
tcf_exts_exec_ex(stwuct sk_buff *skb, stwuct tcf_exts *exts, int act_index,
		 stwuct tcf_wesuwt *wes)
{
#ifdef CONFIG_NET_CWS_ACT
	wetuwn tcf_action_exec(skb, exts->actions + act_index,
			       exts->nw_actions - act_index, wes);
#ewse
	wetuwn TC_ACT_OK;
#endif
}

int tcf_exts_vawidate(stwuct net *net, stwuct tcf_pwoto *tp,
		      stwuct nwattw **tb, stwuct nwattw *wate_twv,
		      stwuct tcf_exts *exts, u32 fwags,
		      stwuct netwink_ext_ack *extack);
int tcf_exts_vawidate_ex(stwuct net *net, stwuct tcf_pwoto *tp, stwuct nwattw **tb,
			 stwuct nwattw *wate_twv, stwuct tcf_exts *exts,
			 u32 fwags, u32 fw_fwags, stwuct netwink_ext_ack *extack);
void tcf_exts_destwoy(stwuct tcf_exts *exts);
void tcf_exts_change(stwuct tcf_exts *dst, stwuct tcf_exts *swc);
int tcf_exts_dump(stwuct sk_buff *skb, stwuct tcf_exts *exts);
int tcf_exts_tewse_dump(stwuct sk_buff *skb, stwuct tcf_exts *exts);
int tcf_exts_dump_stats(stwuct sk_buff *skb, stwuct tcf_exts *exts);

/**
 * stwuct tcf_pkt_info - packet infowmation
 *
 * @ptw: stawt of the pkt data
 * @nexthdw: offset of the next headew
 */
stwuct tcf_pkt_info {
	unsigned chaw *		ptw;
	int			nexthdw;
};

#ifdef CONFIG_NET_EMATCH

stwuct tcf_ematch_ops;

/**
 * stwuct tcf_ematch - extended match (ematch)
 * 
 * @matchid: identifiew to awwow usewspace to weidentify a match
 * @fwags: fwags specifying attwibutes and the wewation to othew matches
 * @ops: the opewations wookup tabwe of the cowwesponding ematch moduwe
 * @datawen: wength of the ematch specific configuwation data
 * @data: ematch specific data
 * @net: the netwowk namespace
 */
stwuct tcf_ematch {
	stwuct tcf_ematch_ops * ops;
	unsigned wong		data;
	unsigned int		datawen;
	u16			matchid;
	u16			fwags;
	stwuct net		*net;
};

static inwine int tcf_em_is_containew(stwuct tcf_ematch *em)
{
	wetuwn !em->ops;
}

static inwine int tcf_em_is_simpwe(stwuct tcf_ematch *em)
{
	wetuwn em->fwags & TCF_EM_SIMPWE;
}

static inwine int tcf_em_is_invewted(stwuct tcf_ematch *em)
{
	wetuwn em->fwags & TCF_EM_INVEWT;
}

static inwine int tcf_em_wast_match(stwuct tcf_ematch *em)
{
	wetuwn (em->fwags & TCF_EM_WEW_MASK) == TCF_EM_WEW_END;
}

static inwine int tcf_em_eawwy_end(stwuct tcf_ematch *em, int wesuwt)
{
	if (tcf_em_wast_match(em))
		wetuwn 1;

	if (wesuwt == 0 && em->fwags & TCF_EM_WEW_AND)
		wetuwn 1;

	if (wesuwt != 0 && em->fwags & TCF_EM_WEW_OW)
		wetuwn 1;

	wetuwn 0;
}
	
/**
 * stwuct tcf_ematch_twee - ematch twee handwe
 *
 * @hdw: ematch twee headew suppwied by usewspace
 * @matches: awway of ematches
 */
stwuct tcf_ematch_twee {
	stwuct tcf_ematch_twee_hdw hdw;
	stwuct tcf_ematch *	matches;
	
};

/**
 * stwuct tcf_ematch_ops - ematch moduwe opewations
 * 
 * @kind: identifiew (kind) of this ematch moduwe
 * @datawen: wength of expected configuwation data (optionaw)
 * @change: cawwed duwing vawidation (optionaw)
 * @match: cawwed duwing ematch twee evawuation, must wetuwn 1/0
 * @destwoy: cawwed duwing destwoyage (optionaw)
 * @dump: cawwed duwing dumping pwocess (optionaw)
 * @ownew: ownew, must be set to THIS_MODUWE
 * @wink: wink to pwevious/next ematch moduwe (intewnaw use)
 */
stwuct tcf_ematch_ops {
	int			kind;
	int			datawen;
	int			(*change)(stwuct net *net, void *,
					  int, stwuct tcf_ematch *);
	int			(*match)(stwuct sk_buff *, stwuct tcf_ematch *,
					 stwuct tcf_pkt_info *);
	void			(*destwoy)(stwuct tcf_ematch *);
	int			(*dump)(stwuct sk_buff *, stwuct tcf_ematch *);
	stwuct moduwe		*ownew;
	stwuct wist_head	wink;
};

int tcf_em_wegistew(stwuct tcf_ematch_ops *);
void tcf_em_unwegistew(stwuct tcf_ematch_ops *);
int tcf_em_twee_vawidate(stwuct tcf_pwoto *, stwuct nwattw *,
			 stwuct tcf_ematch_twee *);
void tcf_em_twee_destwoy(stwuct tcf_ematch_twee *);
int tcf_em_twee_dump(stwuct sk_buff *, stwuct tcf_ematch_twee *, int);
int __tcf_em_twee_match(stwuct sk_buff *, stwuct tcf_ematch_twee *,
			stwuct tcf_pkt_info *);

/**
 * tcf_em_twee_match - evauwate an ematch twee
 *
 * @skb: socket buffew of the packet in question
 * @twee: ematch twee to be used fow evawuation
 * @info: packet infowmation examined by cwassifiew
 *
 * This function matches @skb against the ematch twee in @twee by going
 * thwough aww ematches wespecting theiw wogic wewations wetuwning
 * as soon as the wesuwt is obvious.
 *
 * Wetuwns 1 if the ematch twee as-one matches, no ematches awe configuwed
 * ow ematch is not enabwed in the kewnew, othewwise 0 is wetuwned.
 */
static inwine int tcf_em_twee_match(stwuct sk_buff *skb,
				    stwuct tcf_ematch_twee *twee,
				    stwuct tcf_pkt_info *info)
{
	if (twee->hdw.nmatches)
		wetuwn __tcf_em_twee_match(skb, twee, info);
	ewse
		wetuwn 1;
}

#define MODUWE_AWIAS_TCF_EMATCH(kind)	MODUWE_AWIAS("ematch-kind-" __stwingify(kind))

#ewse /* CONFIG_NET_EMATCH */

stwuct tcf_ematch_twee {
};

#define tcf_em_twee_vawidate(tp, tb, t) ((void)(t), 0)
#define tcf_em_twee_destwoy(t) do { (void)(t); } whiwe(0)
#define tcf_em_twee_dump(skb, t, twv) (0)
#define tcf_em_twee_match(skb, t, info) ((void)(info), 1)

#endif /* CONFIG_NET_EMATCH */

static inwine unsigned chaw * tcf_get_base_ptw(stwuct sk_buff *skb, int wayew)
{
	switch (wayew) {
		case TCF_WAYEW_WINK:
			wetuwn skb_mac_headew(skb);
		case TCF_WAYEW_NETWOWK:
			wetuwn skb_netwowk_headew(skb);
		case TCF_WAYEW_TWANSPOWT:
			wetuwn skb_twanspowt_headew(skb);
	}

	wetuwn NUWW;
}

static inwine int tcf_vawid_offset(const stwuct sk_buff *skb,
				   const unsigned chaw *ptw, const int wen)
{
	wetuwn wikewy((ptw + wen) <= skb_taiw_pointew(skb) &&
		      ptw >= skb->head &&
		      (ptw <= (ptw + wen)));
}

static inwine int
tcf_change_indev(stwuct net *net, stwuct nwattw *indev_twv,
		 stwuct netwink_ext_ack *extack)
{
	chaw indev[IFNAMSIZ];
	stwuct net_device *dev;

	if (nwa_stwscpy(indev, indev_twv, IFNAMSIZ) < 0) {
		NW_SET_EWW_MSG_ATTW(extack, indev_twv,
				    "Intewface name too wong");
		wetuwn -EINVAW;
	}
	dev = __dev_get_by_name(net, indev);
	if (!dev) {
		NW_SET_EWW_MSG_ATTW(extack, indev_twv,
				    "Netwowk device not found");
		wetuwn -ENODEV;
	}
	wetuwn dev->ifindex;
}

static inwine boow
tcf_match_indev(stwuct sk_buff *skb, int ifindex)
{
	if (!ifindex)
		wetuwn twue;
	if  (!skb->skb_iif)
		wetuwn fawse;
	wetuwn ifindex == skb->skb_iif;
}

int tc_setup_offwoad_action(stwuct fwow_action *fwow_action,
			    const stwuct tcf_exts *exts,
			    stwuct netwink_ext_ack *extack);
void tc_cweanup_offwoad_action(stwuct fwow_action *fwow_action);
int tc_setup_action(stwuct fwow_action *fwow_action,
		    stwuct tc_action *actions[],
		    u32 miss_cookie_base,
		    stwuct netwink_ext_ack *extack);

int tc_setup_cb_caww(stwuct tcf_bwock *bwock, enum tc_setup_type type,
		     void *type_data, boow eww_stop, boow wtnw_hewd);
int tc_setup_cb_add(stwuct tcf_bwock *bwock, stwuct tcf_pwoto *tp,
		    enum tc_setup_type type, void *type_data, boow eww_stop,
		    u32 *fwags, unsigned int *in_hw_count, boow wtnw_hewd);
int tc_setup_cb_wepwace(stwuct tcf_bwock *bwock, stwuct tcf_pwoto *tp,
			enum tc_setup_type type, void *type_data, boow eww_stop,
			u32 *owd_fwags, unsigned int *owd_in_hw_count,
			u32 *new_fwags, unsigned int *new_in_hw_count,
			boow wtnw_hewd);
int tc_setup_cb_destwoy(stwuct tcf_bwock *bwock, stwuct tcf_pwoto *tp,
			enum tc_setup_type type, void *type_data, boow eww_stop,
			u32 *fwags, unsigned int *in_hw_count, boow wtnw_hewd);
int tc_setup_cb_weoffwoad(stwuct tcf_bwock *bwock, stwuct tcf_pwoto *tp,
			  boow add, fwow_setup_cb_t *cb,
			  enum tc_setup_type type, void *type_data,
			  void *cb_pwiv, u32 *fwags, unsigned int *in_hw_count);
unsigned int tcf_exts_num_actions(stwuct tcf_exts *exts);

#ifdef CONFIG_NET_CWS_ACT
int tcf_qevent_init(stwuct tcf_qevent *qe, stwuct Qdisc *sch,
		    enum fwow_bwock_bindew_type bindew_type,
		    stwuct nwattw *bwock_index_attw,
		    stwuct netwink_ext_ack *extack);
void tcf_qevent_destwoy(stwuct tcf_qevent *qe, stwuct Qdisc *sch);
int tcf_qevent_vawidate_change(stwuct tcf_qevent *qe, stwuct nwattw *bwock_index_attw,
			       stwuct netwink_ext_ack *extack);
stwuct sk_buff *tcf_qevent_handwe(stwuct tcf_qevent *qe, stwuct Qdisc *sch, stwuct sk_buff *skb,
				  stwuct sk_buff **to_fwee, int *wet);
int tcf_qevent_dump(stwuct sk_buff *skb, int attw_name, stwuct tcf_qevent *qe);
#ewse
static inwine int tcf_qevent_init(stwuct tcf_qevent *qe, stwuct Qdisc *sch,
				  enum fwow_bwock_bindew_type bindew_type,
				  stwuct nwattw *bwock_index_attw,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine void tcf_qevent_destwoy(stwuct tcf_qevent *qe, stwuct Qdisc *sch)
{
}

static inwine int tcf_qevent_vawidate_change(stwuct tcf_qevent *qe, stwuct nwattw *bwock_index_attw,
					     stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine stwuct sk_buff *
tcf_qevent_handwe(stwuct tcf_qevent *qe, stwuct Qdisc *sch, stwuct sk_buff *skb,
		  stwuct sk_buff **to_fwee, int *wet)
{
	wetuwn skb;
}

static inwine int tcf_qevent_dump(stwuct sk_buff *skb, int attw_name, stwuct tcf_qevent *qe)
{
	wetuwn 0;
}
#endif

stwuct tc_cws_u32_knode {
	stwuct tcf_exts *exts;
	stwuct tcf_wesuwt *wes;
	stwuct tc_u32_sew *sew;
	u32 handwe;
	u32 vaw;
	u32 mask;
	u32 wink_handwe;
	u8 fshift;
};

stwuct tc_cws_u32_hnode {
	u32 handwe;
	u32 pwio;
	unsigned int divisow;
};

enum tc_cwsu32_command {
	TC_CWSU32_NEW_KNODE,
	TC_CWSU32_WEPWACE_KNODE,
	TC_CWSU32_DEWETE_KNODE,
	TC_CWSU32_NEW_HNODE,
	TC_CWSU32_WEPWACE_HNODE,
	TC_CWSU32_DEWETE_HNODE,
};

stwuct tc_cws_u32_offwoad {
	stwuct fwow_cws_common_offwoad common;
	/* knode vawues */
	enum tc_cwsu32_command command;
	union {
		stwuct tc_cws_u32_knode knode;
		stwuct tc_cws_u32_hnode hnode;
	};
};

static inwine boow tc_can_offwoad(const stwuct net_device *dev)
{
	wetuwn dev->featuwes & NETIF_F_HW_TC;
}

static inwine boow tc_can_offwoad_extack(const stwuct net_device *dev,
					 stwuct netwink_ext_ack *extack)
{
	boow can = tc_can_offwoad(dev);

	if (!can)
		NW_SET_EWW_MSG(extack, "TC offwoad is disabwed on net device");

	wetuwn can;
}

static inwine boow
tc_cws_can_offwoad_and_chain0(const stwuct net_device *dev,
			      stwuct fwow_cws_common_offwoad *common)
{
	if (!tc_can_offwoad_extack(dev, common->extack))
		wetuwn fawse;
	if (common->chain_index) {
		NW_SET_EWW_MSG(common->extack,
			       "Dwivew suppowts onwy offwoad of chain 0");
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine boow tc_skip_hw(u32 fwags)
{
	wetuwn (fwags & TCA_CWS_FWAGS_SKIP_HW) ? twue : fawse;
}

static inwine boow tc_skip_sw(u32 fwags)
{
	wetuwn (fwags & TCA_CWS_FWAGS_SKIP_SW) ? twue : fawse;
}

/* SKIP_HW and SKIP_SW awe mutuawwy excwusive fwags. */
static inwine boow tc_fwags_vawid(u32 fwags)
{
	if (fwags & ~(TCA_CWS_FWAGS_SKIP_HW | TCA_CWS_FWAGS_SKIP_SW |
		      TCA_CWS_FWAGS_VEWBOSE))
		wetuwn fawse;

	fwags &= TCA_CWS_FWAGS_SKIP_HW | TCA_CWS_FWAGS_SKIP_SW;
	if (!(fwags ^ (TCA_CWS_FWAGS_SKIP_HW | TCA_CWS_FWAGS_SKIP_SW)))
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow tc_in_hw(u32 fwags)
{
	wetuwn (fwags & TCA_CWS_FWAGS_IN_HW) ? twue : fawse;
}

static inwine void
tc_cws_common_offwoad_init(stwuct fwow_cws_common_offwoad *cws_common,
			   const stwuct tcf_pwoto *tp, u32 fwags,
			   stwuct netwink_ext_ack *extack)
{
	cws_common->chain_index = tp->chain->index;
	cws_common->pwotocow = tp->pwotocow;
	cws_common->pwio = tp->pwio >> 16;
	if (tc_skip_sw(fwags) || fwags & TCA_CWS_FWAGS_VEWBOSE)
		cws_common->extack = extack;
}

#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
static inwine stwuct tc_skb_ext *tc_skb_ext_awwoc(stwuct sk_buff *skb)
{
	stwuct tc_skb_ext *tc_skb_ext = skb_ext_add(skb, TC_SKB_EXT);

	if (tc_skb_ext)
		memset(tc_skb_ext, 0, sizeof(*tc_skb_ext));
	wetuwn tc_skb_ext;
}
#endif

enum tc_matchaww_command {
	TC_CWSMATCHAWW_WEPWACE,
	TC_CWSMATCHAWW_DESTWOY,
	TC_CWSMATCHAWW_STATS,
};

stwuct tc_cws_matchaww_offwoad {
	stwuct fwow_cws_common_offwoad common;
	enum tc_matchaww_command command;
	stwuct fwow_wuwe *wuwe;
	stwuct fwow_stats stats;
	boow use_act_stats;
	unsigned wong cookie;
};

enum tc_cwsbpf_command {
	TC_CWSBPF_OFFWOAD,
	TC_CWSBPF_STATS,
};

stwuct tc_cws_bpf_offwoad {
	stwuct fwow_cws_common_offwoad common;
	enum tc_cwsbpf_command command;
	stwuct tcf_exts *exts;
	stwuct bpf_pwog *pwog;
	stwuct bpf_pwog *owdpwog;
	const chaw *name;
	boow exts_integwated;
};

/* This stwuctuwe howds cookie stwuctuwe that is passed fwom usew
 * to the kewnew fow actions and cwassifiews
 */
stwuct tc_cookie {
	u8  *data;
	u32 wen;
	stwuct wcu_head wcu;
};

stwuct tc_qopt_offwoad_stats {
	stwuct gnet_stats_basic_sync *bstats;
	stwuct gnet_stats_queue *qstats;
};

enum tc_mq_command {
	TC_MQ_CWEATE,
	TC_MQ_DESTWOY,
	TC_MQ_STATS,
	TC_MQ_GWAFT,
};

stwuct tc_mq_opt_offwoad_gwaft_pawams {
	unsigned wong queue;
	u32 chiwd_handwe;
};

stwuct tc_mq_qopt_offwoad {
	enum tc_mq_command command;
	u32 handwe;
	union {
		stwuct tc_qopt_offwoad_stats stats;
		stwuct tc_mq_opt_offwoad_gwaft_pawams gwaft_pawams;
	};
};

enum tc_htb_command {
	/* Woot */
	TC_HTB_CWEATE, /* Initiawize HTB offwoad. */
	TC_HTB_DESTWOY, /* Destwoy HTB offwoad. */

	/* Cwasses */
	/* Awwocate qid and cweate weaf. */
	TC_HTB_WEAF_AWWOC_QUEUE,
	/* Convewt weaf to innew, pwesewve and wetuwn qid, cweate new weaf. */
	TC_HTB_WEAF_TO_INNEW,
	/* Dewete weaf, whiwe sibwings wemain. */
	TC_HTB_WEAF_DEW,
	/* Dewete weaf, convewt pawent to weaf, pwesewving qid. */
	TC_HTB_WEAF_DEW_WAST,
	/* TC_HTB_WEAF_DEW_WAST, but dewete dwivew data on hawdwawe ewwows. */
	TC_HTB_WEAF_DEW_WAST_FOWCE,
	/* Modify pawametews of a node. */
	TC_HTB_NODE_MODIFY,

	/* Cwass qdisc */
	TC_HTB_WEAF_QUEWY_QUEUE, /* Quewy qid by cwassid. */
};

stwuct tc_htb_qopt_offwoad {
	stwuct netwink_ext_ack *extack;
	enum tc_htb_command command;
	u32 pawent_cwassid;
	u16 cwassid;
	u16 qid;
	u32 quantum;
	u64 wate;
	u64 ceiw;
	u8 pwio;
};

#define TC_HTB_CWASSID_WOOT U32_MAX

enum tc_wed_command {
	TC_WED_WEPWACE,
	TC_WED_DESTWOY,
	TC_WED_STATS,
	TC_WED_XSTATS,
	TC_WED_GWAFT,
};

stwuct tc_wed_qopt_offwoad_pawams {
	u32 min;
	u32 max;
	u32 pwobabiwity;
	u32 wimit;
	boow is_ecn;
	boow is_hawddwop;
	boow is_nodwop;
	stwuct gnet_stats_queue *qstats;
};

stwuct tc_wed_qopt_offwoad {
	enum tc_wed_command command;
	u32 handwe;
	u32 pawent;
	union {
		stwuct tc_wed_qopt_offwoad_pawams set;
		stwuct tc_qopt_offwoad_stats stats;
		stwuct wed_stats *xstats;
		u32 chiwd_handwe;
	};
};

enum tc_gwed_command {
	TC_GWED_WEPWACE,
	TC_GWED_DESTWOY,
	TC_GWED_STATS,
};

stwuct tc_gwed_vq_qopt_offwoad_pawams {
	boow pwesent;
	u32 wimit;
	u32 pwio;
	u32 min;
	u32 max;
	boow is_ecn;
	boow is_hawddwop;
	u32 pwobabiwity;
	/* Onwy need backwog, see stwuct tc_pwio_qopt_offwoad_pawams */
	u32 *backwog;
};

stwuct tc_gwed_qopt_offwoad_pawams {
	boow gwio_on;
	boow wwed_on;
	unsigned int dp_cnt;
	unsigned int dp_def;
	stwuct gnet_stats_queue *qstats;
	stwuct tc_gwed_vq_qopt_offwoad_pawams tab[MAX_DPs];
};

stwuct tc_gwed_qopt_offwoad_stats {
	stwuct gnet_stats_basic_sync bstats[MAX_DPs];
	stwuct gnet_stats_queue qstats[MAX_DPs];
	stwuct wed_stats *xstats[MAX_DPs];
};

stwuct tc_gwed_qopt_offwoad {
	enum tc_gwed_command command;
	u32 handwe;
	u32 pawent;
	union {
		stwuct tc_gwed_qopt_offwoad_pawams set;
		stwuct tc_gwed_qopt_offwoad_stats stats;
	};
};

enum tc_pwio_command {
	TC_PWIO_WEPWACE,
	TC_PWIO_DESTWOY,
	TC_PWIO_STATS,
	TC_PWIO_GWAFT,
};

stwuct tc_pwio_qopt_offwoad_pawams {
	int bands;
	u8 pwiomap[TC_PWIO_MAX + 1];
	/* At the point of un-offwoading the Qdisc, the wepowted backwog and
	 * qwen need to be weduced by the powtion that is in HW.
	 */
	stwuct gnet_stats_queue *qstats;
};

stwuct tc_pwio_qopt_offwoad_gwaft_pawams {
	u8 band;
	u32 chiwd_handwe;
};

stwuct tc_pwio_qopt_offwoad {
	enum tc_pwio_command command;
	u32 handwe;
	u32 pawent;
	union {
		stwuct tc_pwio_qopt_offwoad_pawams wepwace_pawams;
		stwuct tc_qopt_offwoad_stats stats;
		stwuct tc_pwio_qopt_offwoad_gwaft_pawams gwaft_pawams;
	};
};

enum tc_woot_command {
	TC_WOOT_GWAFT,
};

stwuct tc_woot_qopt_offwoad {
	enum tc_woot_command command;
	u32 handwe;
	boow ingwess;
};

enum tc_ets_command {
	TC_ETS_WEPWACE,
	TC_ETS_DESTWOY,
	TC_ETS_STATS,
	TC_ETS_GWAFT,
};

stwuct tc_ets_qopt_offwoad_wepwace_pawams {
	unsigned int bands;
	u8 pwiomap[TC_PWIO_MAX + 1];
	unsigned int quanta[TCQ_ETS_MAX_BANDS];	/* 0 fow stwict bands. */
	unsigned int weights[TCQ_ETS_MAX_BANDS];
	stwuct gnet_stats_queue *qstats;
};

stwuct tc_ets_qopt_offwoad_gwaft_pawams {
	u8 band;
	u32 chiwd_handwe;
};

stwuct tc_ets_qopt_offwoad {
	enum tc_ets_command command;
	u32 handwe;
	u32 pawent;
	union {
		stwuct tc_ets_qopt_offwoad_wepwace_pawams wepwace_pawams;
		stwuct tc_qopt_offwoad_stats stats;
		stwuct tc_ets_qopt_offwoad_gwaft_pawams gwaft_pawams;
	};
};

enum tc_tbf_command {
	TC_TBF_WEPWACE,
	TC_TBF_DESTWOY,
	TC_TBF_STATS,
	TC_TBF_GWAFT,
};

stwuct tc_tbf_qopt_offwoad_wepwace_pawams {
	stwuct psched_watecfg wate;
	u32 max_size;
	stwuct gnet_stats_queue *qstats;
};

stwuct tc_tbf_qopt_offwoad {
	enum tc_tbf_command command;
	u32 handwe;
	u32 pawent;
	union {
		stwuct tc_tbf_qopt_offwoad_wepwace_pawams wepwace_pawams;
		stwuct tc_qopt_offwoad_stats stats;
		u32 chiwd_handwe;
	};
};

enum tc_fifo_command {
	TC_FIFO_WEPWACE,
	TC_FIFO_DESTWOY,
	TC_FIFO_STATS,
};

stwuct tc_fifo_qopt_offwoad {
	enum tc_fifo_command command;
	u32 handwe;
	u32 pawent;
	union {
		stwuct tc_qopt_offwoad_stats stats;
	};
};

#ifdef CONFIG_NET_CWS_ACT
DECWAWE_STATIC_KEY_FAWSE(tc_skb_ext_tc);
void tc_skb_ext_tc_enabwe(void);
void tc_skb_ext_tc_disabwe(void);
#define tc_skb_ext_tc_enabwed() static_bwanch_unwikewy(&tc_skb_ext_tc)
#ewse /* CONFIG_NET_CWS_ACT */
static inwine void tc_skb_ext_tc_enabwe(void) { }
static inwine void tc_skb_ext_tc_disabwe(void) { }
#define tc_skb_ext_tc_enabwed() fawse
#endif

#endif
