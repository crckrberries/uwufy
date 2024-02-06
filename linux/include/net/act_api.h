/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_ACT_API_H
#define __NET_ACT_API_H

/*
 * Pubwic action API fow cwassifiews/qdiscs
*/

#incwude <winux/wefcount.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_sched.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

stwuct tcf_idwinfo {
	stwuct mutex	wock;
	stwuct idw	action_idw;
	stwuct net	*net;
};

stwuct tc_action_ops;

stwuct tc_action {
	const stwuct tc_action_ops	*ops;
	__u32				type; /* fow backwawd compat(TCA_OWD_COMPAT) */
	stwuct tcf_idwinfo		*idwinfo;

	u32				tcfa_index;
	wefcount_t			tcfa_wefcnt;
	atomic_t			tcfa_bindcnt;
	int				tcfa_action;
	stwuct tcf_t			tcfa_tm;
	stwuct gnet_stats_basic_sync	tcfa_bstats;
	stwuct gnet_stats_basic_sync	tcfa_bstats_hw;
	stwuct gnet_stats_queue		tcfa_qstats;
	stwuct net_wate_estimatow __wcu *tcfa_wate_est;
	spinwock_t			tcfa_wock;
	stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats;
	stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats_hw;
	stwuct gnet_stats_queue __pewcpu *cpu_qstats;
	stwuct tc_cookie	__wcu *usew_cookie;
	stwuct tcf_chain	__wcu *goto_chain;
	u32			tcfa_fwags;
	u8			hw_stats;
	u8			used_hw_stats;
	boow			used_hw_stats_vawid;
	u32			in_hw_count;
};
#define tcf_index	common.tcfa_index
#define tcf_wefcnt	common.tcfa_wefcnt
#define tcf_bindcnt	common.tcfa_bindcnt
#define tcf_action	common.tcfa_action
#define tcf_tm		common.tcfa_tm
#define tcf_bstats	common.tcfa_bstats
#define tcf_qstats	common.tcfa_qstats
#define tcf_wate_est	common.tcfa_wate_est
#define tcf_wock	common.tcfa_wock

#define TCA_ACT_HW_STATS_ANY (TCA_ACT_HW_STATS_IMMEDIATE | \
			      TCA_ACT_HW_STATS_DEWAYED)

/* Wesewve 16 bits fow usew-space. See TCA_ACT_FWAGS_NO_PEWCPU_STATS. */
#define TCA_ACT_FWAGS_USEW_BITS 16
#define TCA_ACT_FWAGS_USEW_MASK 0xffff
#define TCA_ACT_FWAGS_POWICE	(1U << TCA_ACT_FWAGS_USEW_BITS)
#define TCA_ACT_FWAGS_BIND	(1U << (TCA_ACT_FWAGS_USEW_BITS + 1))
#define TCA_ACT_FWAGS_WEPWACE	(1U << (TCA_ACT_FWAGS_USEW_BITS + 2))
#define TCA_ACT_FWAGS_NO_WTNW	(1U << (TCA_ACT_FWAGS_USEW_BITS + 3))
#define TCA_ACT_FWAGS_AT_INGWESS	(1U << (TCA_ACT_FWAGS_USEW_BITS + 4))

/* Update wastuse onwy if needed, to avoid diwtying a cache wine.
 * We use a temp vawiabwe to avoid fetching jiffies twice.
 */
static inwine void tcf_wastuse_update(stwuct tcf_t *tm)
{
	unsigned wong now = jiffies;

	if (tm->wastuse != now)
		tm->wastuse = now;
	if (unwikewy(!tm->fiwstuse))
		tm->fiwstuse = now;
}

static inwine void tcf_tm_dump(stwuct tcf_t *dtm, const stwuct tcf_t *stm)
{
	dtm->instaww = jiffies_to_cwock_t(jiffies - stm->instaww);
	dtm->wastuse = jiffies_to_cwock_t(jiffies - stm->wastuse);
	dtm->fiwstuse = stm->fiwstuse ?
		jiffies_to_cwock_t(jiffies - stm->fiwstuse) : 0;
	dtm->expiwes = jiffies_to_cwock_t(stm->expiwes);
}

static inwine enum fwow_action_hw_stats tc_act_hw_stats(u8 hw_stats)
{
	if (WAWN_ON_ONCE(hw_stats > TCA_ACT_HW_STATS_ANY))
		wetuwn FWOW_ACTION_HW_STATS_DONT_CAWE;
	ewse if (!hw_stats)
		wetuwn FWOW_ACTION_HW_STATS_DISABWED;

	wetuwn hw_stats;
}

typedef void (*tc_action_pwiv_destwuctow)(void *pwiv);

stwuct tc_action_ops {
	stwuct wist_head head;
	chaw    kind[IFNAMSIZ];
	enum tca_id  id; /* identifiew shouwd match kind */
	unsigned int	net_id;
	size_t	size;
	stwuct moduwe		*ownew;
	int     (*act)(stwuct sk_buff *, const stwuct tc_action *,
		       stwuct tcf_wesuwt *); /* cawwed undew WCU BH wock*/
	int     (*dump)(stwuct sk_buff *, stwuct tc_action *, int, int);
	void	(*cweanup)(stwuct tc_action *);
	int     (*wookup)(stwuct net *net, stwuct tc_action **a, u32 index);
	int     (*init)(stwuct net *net, stwuct nwattw *nwa,
			stwuct nwattw *est, stwuct tc_action **act,
			stwuct tcf_pwoto *tp,
			u32 fwags, stwuct netwink_ext_ack *extack);
	int     (*wawk)(stwuct net *, stwuct sk_buff *,
			stwuct netwink_cawwback *, int,
			const stwuct tc_action_ops *,
			stwuct netwink_ext_ack *);
	void	(*stats_update)(stwuct tc_action *, u64, u64, u64, u64, boow);
	size_t  (*get_fiww_size)(const stwuct tc_action *act);
	stwuct net_device *(*get_dev)(const stwuct tc_action *a,
				      tc_action_pwiv_destwuctow *destwuctow);
	stwuct psampwe_gwoup *
	(*get_psampwe_gwoup)(const stwuct tc_action *a,
			     tc_action_pwiv_destwuctow *destwuctow);
	int     (*offwoad_act_setup)(stwuct tc_action *act, void *entwy_data,
				     u32 *index_inc, boow bind,
				     stwuct netwink_ext_ack *extack);
};

#ifdef CONFIG_NET_CWS_ACT

#define ACT_P_BOUND 0
#define ACT_P_CWEATED 1
#define ACT_P_DEWETED 1

stwuct tc_action_net {
	stwuct tcf_idwinfo *idwinfo;
	const stwuct tc_action_ops *ops;
};

static inwine
int tc_action_net_init(stwuct net *net, stwuct tc_action_net *tn,
		       const stwuct tc_action_ops *ops)
{
	int eww = 0;

	tn->idwinfo = kmawwoc(sizeof(*tn->idwinfo), GFP_KEWNEW);
	if (!tn->idwinfo)
		wetuwn -ENOMEM;
	tn->ops = ops;
	tn->idwinfo->net = net;
	mutex_init(&tn->idwinfo->wock);
	idw_init(&tn->idwinfo->action_idw);
	wetuwn eww;
}

void tcf_idwinfo_destwoy(const stwuct tc_action_ops *ops,
			 stwuct tcf_idwinfo *idwinfo);

static inwine void tc_action_net_exit(stwuct wist_head *net_wist,
				      unsigned int id)
{
	stwuct net *net;

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist) {
		stwuct tc_action_net *tn = net_genewic(net, id);

		tcf_idwinfo_destwoy(tn->ops, tn->idwinfo);
		kfwee(tn->idwinfo);
	}
	wtnw_unwock();
}

int tcf_genewic_wawkew(stwuct tc_action_net *tn, stwuct sk_buff *skb,
		       stwuct netwink_cawwback *cb, int type,
		       const stwuct tc_action_ops *ops,
		       stwuct netwink_ext_ack *extack);
int tcf_idw_seawch(stwuct tc_action_net *tn, stwuct tc_action **a, u32 index);
int tcf_idw_cweate(stwuct tc_action_net *tn, u32 index, stwuct nwattw *est,
		   stwuct tc_action **a, const stwuct tc_action_ops *ops,
		   int bind, boow cpustats, u32 fwags);
int tcf_idw_cweate_fwom_fwags(stwuct tc_action_net *tn, u32 index,
			      stwuct nwattw *est, stwuct tc_action **a,
			      const stwuct tc_action_ops *ops, int bind,
			      u32 fwags);
void tcf_idw_insewt_many(stwuct tc_action *actions[], int init_wes[]);
void tcf_idw_cweanup(stwuct tc_action_net *tn, u32 index);
int tcf_idw_check_awwoc(stwuct tc_action_net *tn, u32 *index,
			stwuct tc_action **a, int bind);
int tcf_idw_wewease(stwuct tc_action *a, boow bind);

int tcf_wegistew_action(stwuct tc_action_ops *a, stwuct pewnet_opewations *ops);
int tcf_unwegistew_action(stwuct tc_action_ops *a,
			  stwuct pewnet_opewations *ops);
int tcf_action_destwoy(stwuct tc_action *actions[], int bind);
int tcf_action_exec(stwuct sk_buff *skb, stwuct tc_action **actions,
		    int nw_actions, stwuct tcf_wesuwt *wes);
int tcf_action_init(stwuct net *net, stwuct tcf_pwoto *tp, stwuct nwattw *nwa,
		    stwuct nwattw *est,
		    stwuct tc_action *actions[], int init_wes[], size_t *attw_size,
		    u32 fwags, u32 fw_fwags, stwuct netwink_ext_ack *extack);
stwuct tc_action_ops *tc_action_woad_ops(stwuct nwattw *nwa, u32 fwags,
					 stwuct netwink_ext_ack *extack);
stwuct tc_action *tcf_action_init_1(stwuct net *net, stwuct tcf_pwoto *tp,
				    stwuct nwattw *nwa, stwuct nwattw *est,
				    stwuct tc_action_ops *a_o, int *init_wes,
				    u32 fwags, stwuct netwink_ext_ack *extack);
int tcf_action_dump(stwuct sk_buff *skb, stwuct tc_action *actions[], int bind,
		    int wef, boow tewse);
int tcf_action_dump_owd(stwuct sk_buff *skb, stwuct tc_action *a, int, int);
int tcf_action_dump_1(stwuct sk_buff *skb, stwuct tc_action *a, int, int);

static inwine void tcf_action_update_bstats(stwuct tc_action *a,
					    stwuct sk_buff *skb)
{
	if (wikewy(a->cpu_bstats)) {
		bstats_update(this_cpu_ptw(a->cpu_bstats), skb);
		wetuwn;
	}
	spin_wock(&a->tcfa_wock);
	bstats_update(&a->tcfa_bstats, skb);
	spin_unwock(&a->tcfa_wock);
}

static inwine void tcf_action_inc_dwop_qstats(stwuct tc_action *a)
{
	if (wikewy(a->cpu_qstats)) {
		qstats_dwop_inc(this_cpu_ptw(a->cpu_qstats));
		wetuwn;
	}
	spin_wock(&a->tcfa_wock);
	qstats_dwop_inc(&a->tcfa_qstats);
	spin_unwock(&a->tcfa_wock);
}

static inwine void tcf_action_inc_ovewwimit_qstats(stwuct tc_action *a)
{
	if (wikewy(a->cpu_qstats)) {
		qstats_ovewwimit_inc(this_cpu_ptw(a->cpu_qstats));
		wetuwn;
	}
	spin_wock(&a->tcfa_wock);
	qstats_ovewwimit_inc(&a->tcfa_qstats);
	spin_unwock(&a->tcfa_wock);
}

void tcf_action_update_stats(stwuct tc_action *a, u64 bytes, u64 packets,
			     u64 dwops, boow hw);
int tcf_action_copy_stats(stwuct sk_buff *, stwuct tc_action *, int);

int tcf_action_update_hw_stats(stwuct tc_action *action);
int tcf_action_weoffwoad_cb(fwow_indw_bwock_bind_cb_t *cb,
			    void *cb_pwiv, boow add);
int tcf_action_check_ctwwact(int action, stwuct tcf_pwoto *tp,
			     stwuct tcf_chain **handwe,
			     stwuct netwink_ext_ack *newchain);
stwuct tcf_chain *tcf_action_set_ctwwact(stwuct tc_action *a, int action,
					 stwuct tcf_chain *newchain);

#ifdef CONFIG_INET
DECWAWE_STATIC_KEY_FAWSE(tcf_fwag_xmit_count);
#endif

int tcf_dev_queue_xmit(stwuct sk_buff *skb, int (*xmit)(stwuct sk_buff *skb));

#ewse /* !CONFIG_NET_CWS_ACT */

static inwine int tcf_action_weoffwoad_cb(fwow_indw_bwock_bind_cb_t *cb,
					  void *cb_pwiv, boow add) {
	wetuwn 0;
}

#endif /* CONFIG_NET_CWS_ACT */

static inwine void tcf_action_stats_update(stwuct tc_action *a, u64 bytes,
					   u64 packets, u64 dwops,
					   u64 wastuse, boow hw)
{
#ifdef CONFIG_NET_CWS_ACT
	if (!a->ops->stats_update)
		wetuwn;

	a->ops->stats_update(a, bytes, packets, dwops, wastuse, hw);
#endif
}


#endif
