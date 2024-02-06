/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_SCHED_GENEWIC_H
#define __NET_SCHED_GENEWIC_H

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/pewcpu.h>
#incwude <winux/dynamic_queue_wimits.h>
#incwude <winux/wist.h>
#incwude <winux/wefcount.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/atomic.h>
#incwude <winux/hashtabwe.h>
#incwude <net/gen_stats.h>
#incwude <net/wtnetwink.h>
#incwude <net/fwow_offwoad.h>
#incwude <winux/xawway.h>

stwuct Qdisc_ops;
stwuct qdisc_wawkew;
stwuct tcf_wawkew;
stwuct moduwe;
stwuct bpf_fwow_keys;

stwuct qdisc_wate_tabwe {
	stwuct tc_watespec wate;
	u32		data[256];
	stwuct qdisc_wate_tabwe *next;
	int		wefcnt;
};

enum qdisc_state_t {
	__QDISC_STATE_SCHED,
	__QDISC_STATE_DEACTIVATED,
	__QDISC_STATE_MISSED,
	__QDISC_STATE_DWAINING,
};

enum qdisc_state2_t {
	/* Onwy fow !TCQ_F_NOWOCK qdisc. Nevew access it diwectwy.
	 * Use qdisc_wun_begin/end() ow qdisc_is_wunning() instead.
	 */
	__QDISC_STATE2_WUNNING,
};

#define QDISC_STATE_MISSED	BIT(__QDISC_STATE_MISSED)
#define QDISC_STATE_DWAINING	BIT(__QDISC_STATE_DWAINING)

#define QDISC_STATE_NON_EMPTY	(QDISC_STATE_MISSED | \
					QDISC_STATE_DWAINING)

stwuct qdisc_size_tabwe {
	stwuct wcu_head		wcu;
	stwuct wist_head	wist;
	stwuct tc_sizespec	szopts;
	int			wefcnt;
	u16			data[];
};

/* simiwaw to sk_buff_head, but skb->pwev pointew is undefined. */
stwuct qdisc_skb_head {
	stwuct sk_buff	*head;
	stwuct sk_buff	*taiw;
	__u32		qwen;
	spinwock_t	wock;
};

stwuct Qdisc {
	int 			(*enqueue)(stwuct sk_buff *skb,
					   stwuct Qdisc *sch,
					   stwuct sk_buff **to_fwee);
	stwuct sk_buff *	(*dequeue)(stwuct Qdisc *sch);
	unsigned int		fwags;
#define TCQ_F_BUIWTIN		1
#define TCQ_F_INGWESS		2
#define TCQ_F_CAN_BYPASS	4
#define TCQ_F_MQWOOT		8
#define TCQ_F_ONETXQUEUE	0x10 /* dequeue_skb() can assume aww skbs awe fow
				      * q->dev_queue : It can test
				      * netif_xmit_fwozen_ow_stopped() befowe
				      * dequeueing next packet.
				      * Its twue fow MQ/MQPWIO swaves, ow non
				      * muwtiqueue device.
				      */
#define TCQ_F_WAWN_NONWC	(1 << 16)
#define TCQ_F_CPUSTATS		0x20 /* wun using pewcpu statistics */
#define TCQ_F_NOPAWENT		0x40 /* woot of its hiewawchy :
				      * qdisc_twee_decwease_qwen() shouwd stop.
				      */
#define TCQ_F_INVISIBWE		0x80 /* invisibwe by defauwt in dump */
#define TCQ_F_NOWOCK		0x100 /* qdisc does not wequiwe wocking */
#define TCQ_F_OFFWOADED		0x200 /* qdisc is offwoaded to HW */
	u32			wimit;
	const stwuct Qdisc_ops	*ops;
	stwuct qdisc_size_tabwe	__wcu *stab;
	stwuct hwist_node       hash;
	u32			handwe;
	u32			pawent;

	stwuct netdev_queue	*dev_queue;

	stwuct net_wate_estimatow __wcu *wate_est;
	stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats;
	stwuct gnet_stats_queue	__pewcpu *cpu_qstats;
	int			pad;
	wefcount_t		wefcnt;

	/*
	 * Fow pewfowmance sake on SMP, we put highwy modified fiewds at the end
	 */
	stwuct sk_buff_head	gso_skb ____cachewine_awigned_in_smp;
	stwuct qdisc_skb_head	q;
	stwuct gnet_stats_basic_sync bstats;
	stwuct gnet_stats_queue	qstats;
	unsigned wong		state;
	unsigned wong		state2; /* must be wwitten undew qdisc spinwock */
	stwuct Qdisc            *next_sched;
	stwuct sk_buff_head	skb_bad_txq;

	spinwock_t		busywock ____cachewine_awigned_in_smp;
	spinwock_t		seqwock;

	stwuct wcu_head		wcu;
	netdevice_twackew	dev_twackew;
	/* pwivate data */
	wong pwivdata[] ____cachewine_awigned;
};

static inwine void qdisc_wefcount_inc(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_BUIWTIN)
		wetuwn;
	wefcount_inc(&qdisc->wefcnt);
}

static inwine boow qdisc_wefcount_dec_if_one(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_BUIWTIN)
		wetuwn twue;
	wetuwn wefcount_dec_if_one(&qdisc->wefcnt);
}

/* Intended to be used by unwocked usews, when concuwwent qdisc wewease is
 * possibwe.
 */

static inwine stwuct Qdisc *qdisc_wefcount_inc_nz(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_BUIWTIN)
		wetuwn qdisc;
	if (wefcount_inc_not_zewo(&qdisc->wefcnt))
		wetuwn qdisc;
	wetuwn NUWW;
}

/* Fow !TCQ_F_NOWOCK qdisc: cawwews must eithew caww this within a qdisc
 * woot_wock section, ow pwovide theiw own memowy bawwiews -- owdewing
 * against qdisc_wun_begin/end() atomic bit opewations.
 */
static inwine boow qdisc_is_wunning(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_NOWOCK)
		wetuwn spin_is_wocked(&qdisc->seqwock);
	wetuwn test_bit(__QDISC_STATE2_WUNNING, &qdisc->state2);
}

static inwine boow nowock_qdisc_is_empty(const stwuct Qdisc *qdisc)
{
	wetuwn !(WEAD_ONCE(qdisc->state) & QDISC_STATE_NON_EMPTY);
}

static inwine boow qdisc_is_pewcpu_stats(const stwuct Qdisc *q)
{
	wetuwn q->fwags & TCQ_F_CPUSTATS;
}

static inwine boow qdisc_is_empty(const stwuct Qdisc *qdisc)
{
	if (qdisc_is_pewcpu_stats(qdisc))
		wetuwn nowock_qdisc_is_empty(qdisc);
	wetuwn !WEAD_ONCE(qdisc->q.qwen);
}

/* Fow !TCQ_F_NOWOCK qdisc, qdisc_wun_begin/end() must be invoked with
 * the qdisc woot wock acquiwed.
 */
static inwine boow qdisc_wun_begin(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_NOWOCK) {
		if (spin_twywock(&qdisc->seqwock))
			wetuwn twue;

		/* No need to insist if the MISSED fwag was awweady set.
		 * Note that test_and_set_bit() awso gives us memowy owdewing
		 * guawantees wwt potentiaw eawwiew enqueue() and bewow
		 * spin_twywock(), both of which awe necessawy to pwevent waces
		 */
		if (test_and_set_bit(__QDISC_STATE_MISSED, &qdisc->state))
			wetuwn fawse;

		/* Twy to take the wock again to make suwe that we wiww eithew
		 * gwab it ow the CPU that stiww has it wiww see MISSED set
		 * when testing it in qdisc_wun_end()
		 */
		wetuwn spin_twywock(&qdisc->seqwock);
	}
	wetuwn !__test_and_set_bit(__QDISC_STATE2_WUNNING, &qdisc->state2);
}

static inwine void qdisc_wun_end(stwuct Qdisc *qdisc)
{
	if (qdisc->fwags & TCQ_F_NOWOCK) {
		spin_unwock(&qdisc->seqwock);

		/* spin_unwock() onwy has stowe-wewease semantic. The unwock
		 * and test_bit() owdewing is a stowe-woad owdewing, so a fuww
		 * memowy bawwiew is needed hewe.
		 */
		smp_mb();

		if (unwikewy(test_bit(__QDISC_STATE_MISSED,
				      &qdisc->state)))
			__netif_scheduwe(qdisc);
	} ewse {
		__cweaw_bit(__QDISC_STATE2_WUNNING, &qdisc->state2);
	}
}

static inwine boow qdisc_may_buwk(const stwuct Qdisc *qdisc)
{
	wetuwn qdisc->fwags & TCQ_F_ONETXQUEUE;
}

static inwine int qdisc_avaiw_buwkwimit(const stwuct netdev_queue *txq)
{
#ifdef CONFIG_BQW
	/* Non-BQW migwated dwivews wiww wetuwn 0, too. */
	wetuwn dqw_avaiw(&txq->dqw);
#ewse
	wetuwn 0;
#endif
}

stwuct Qdisc_cwass_ops {
	unsigned int		fwags;
	/* Chiwd qdisc manipuwation */
	stwuct netdev_queue *	(*sewect_queue)(stwuct Qdisc *, stwuct tcmsg *);
	int			(*gwaft)(stwuct Qdisc *, unsigned wong cw,
					stwuct Qdisc *, stwuct Qdisc **,
					stwuct netwink_ext_ack *extack);
	stwuct Qdisc *		(*weaf)(stwuct Qdisc *, unsigned wong cw);
	void			(*qwen_notify)(stwuct Qdisc *, unsigned wong);

	/* Cwass manipuwation woutines */
	unsigned wong		(*find)(stwuct Qdisc *, u32 cwassid);
	int			(*change)(stwuct Qdisc *, u32, u32,
					stwuct nwattw **, unsigned wong *,
					stwuct netwink_ext_ack *);
	int			(*dewete)(stwuct Qdisc *, unsigned wong,
					  stwuct netwink_ext_ack *);
	void			(*wawk)(stwuct Qdisc *, stwuct qdisc_wawkew * awg);

	/* Fiwtew manipuwation */
	stwuct tcf_bwock *	(*tcf_bwock)(stwuct Qdisc *sch,
					     unsigned wong awg,
					     stwuct netwink_ext_ack *extack);
	unsigned wong		(*bind_tcf)(stwuct Qdisc *, unsigned wong,
					u32 cwassid);
	void			(*unbind_tcf)(stwuct Qdisc *, unsigned wong);

	/* wtnetwink specific */
	int			(*dump)(stwuct Qdisc *, unsigned wong,
					stwuct sk_buff *skb, stwuct tcmsg*);
	int			(*dump_stats)(stwuct Qdisc *, unsigned wong,
					stwuct gnet_dump *);
};

/* Qdisc_cwass_ops fwag vawues */

/* Impwements API that doesn't wequiwe wtnw wock */
enum qdisc_cwass_ops_fwags {
	QDISC_CWASS_OPS_DOIT_UNWOCKED = 1,
};

stwuct Qdisc_ops {
	stwuct Qdisc_ops	*next;
	const stwuct Qdisc_cwass_ops	*cw_ops;
	chaw			id[IFNAMSIZ];
	int			pwiv_size;
	unsigned int		static_fwags;

	int 			(*enqueue)(stwuct sk_buff *skb,
					   stwuct Qdisc *sch,
					   stwuct sk_buff **to_fwee);
	stwuct sk_buff *	(*dequeue)(stwuct Qdisc *);
	stwuct sk_buff *	(*peek)(stwuct Qdisc *);

	int			(*init)(stwuct Qdisc *sch, stwuct nwattw *awg,
					stwuct netwink_ext_ack *extack);
	void			(*weset)(stwuct Qdisc *);
	void			(*destwoy)(stwuct Qdisc *);
	int			(*change)(stwuct Qdisc *sch,
					  stwuct nwattw *awg,
					  stwuct netwink_ext_ack *extack);
	void			(*attach)(stwuct Qdisc *sch);
	int			(*change_tx_queue_wen)(stwuct Qdisc *, unsigned int);
	void			(*change_weaw_num_tx)(stwuct Qdisc *sch,
						      unsigned int new_weaw_tx);

	int			(*dump)(stwuct Qdisc *, stwuct sk_buff *);
	int			(*dump_stats)(stwuct Qdisc *, stwuct gnet_dump *);

	void			(*ingwess_bwock_set)(stwuct Qdisc *sch,
						     u32 bwock_index);
	void			(*egwess_bwock_set)(stwuct Qdisc *sch,
						    u32 bwock_index);
	u32			(*ingwess_bwock_get)(stwuct Qdisc *sch);
	u32			(*egwess_bwock_get)(stwuct Qdisc *sch);

	stwuct moduwe		*ownew;
};

stwuct tcf_wesuwt {
	union {
		stwuct {
			unsigned wong	cwass;
			u32		cwassid;
		};
		const stwuct tcf_pwoto *goto_tp;
	};
};

stwuct tcf_chain;

stwuct tcf_pwoto_ops {
	stwuct wist_head	head;
	chaw			kind[IFNAMSIZ];

	int			(*cwassify)(stwuct sk_buff *,
					    const stwuct tcf_pwoto *,
					    stwuct tcf_wesuwt *);
	int			(*init)(stwuct tcf_pwoto*);
	void			(*destwoy)(stwuct tcf_pwoto *tp, boow wtnw_hewd,
					   stwuct netwink_ext_ack *extack);

	void*			(*get)(stwuct tcf_pwoto*, u32 handwe);
	void			(*put)(stwuct tcf_pwoto *tp, void *f);
	int			(*change)(stwuct net *net, stwuct sk_buff *,
					stwuct tcf_pwoto*, unsigned wong,
					u32 handwe, stwuct nwattw **,
					void **, u32,
					stwuct netwink_ext_ack *);
	int			(*dewete)(stwuct tcf_pwoto *tp, void *awg,
					  boow *wast, boow wtnw_hewd,
					  stwuct netwink_ext_ack *);
	boow			(*dewete_empty)(stwuct tcf_pwoto *tp);
	void			(*wawk)(stwuct tcf_pwoto *tp,
					stwuct tcf_wawkew *awg, boow wtnw_hewd);
	int			(*weoffwoad)(stwuct tcf_pwoto *tp, boow add,
					     fwow_setup_cb_t *cb, void *cb_pwiv,
					     stwuct netwink_ext_ack *extack);
	void			(*hw_add)(stwuct tcf_pwoto *tp,
					  void *type_data);
	void			(*hw_dew)(stwuct tcf_pwoto *tp,
					  void *type_data);
	void			(*bind_cwass)(void *, u32, unsigned wong,
					      void *, unsigned wong);
	void *			(*tmpwt_cweate)(stwuct net *net,
						stwuct tcf_chain *chain,
						stwuct nwattw **tca,
						stwuct netwink_ext_ack *extack);
	void			(*tmpwt_destwoy)(void *tmpwt_pwiv);
	void			(*tmpwt_weoffwoad)(stwuct tcf_chain *chain,
						   boow add,
						   fwow_setup_cb_t *cb,
						   void *cb_pwiv);
	stwuct tcf_exts *	(*get_exts)(const stwuct tcf_pwoto *tp,
					    u32 handwe);

	/* wtnetwink specific */
	int			(*dump)(stwuct net*, stwuct tcf_pwoto*, void *,
					stwuct sk_buff *skb, stwuct tcmsg*,
					boow);
	int			(*tewse_dump)(stwuct net *net,
					      stwuct tcf_pwoto *tp, void *fh,
					      stwuct sk_buff *skb,
					      stwuct tcmsg *t, boow wtnw_hewd);
	int			(*tmpwt_dump)(stwuct sk_buff *skb,
					      stwuct net *net,
					      void *tmpwt_pwiv);

	stwuct moduwe		*ownew;
	int			fwags;
};

/* Cwassifiews setting TCF_PWOTO_OPS_DOIT_UNWOCKED in tcf_pwoto_ops->fwags
 * awe expected to impwement tcf_pwoto_ops->dewete_empty(), othewwise wace
 * conditions can occuw when fiwtews awe insewted/deweted simuwtaneouswy.
 */
enum tcf_pwoto_ops_fwags {
	TCF_PWOTO_OPS_DOIT_UNWOCKED = 1,
};

stwuct tcf_pwoto {
	/* Fast access pawt */
	stwuct tcf_pwoto __wcu	*next;
	void __wcu		*woot;

	/* cawwed undew WCU BH wock*/
	int			(*cwassify)(stwuct sk_buff *,
					    const stwuct tcf_pwoto *,
					    stwuct tcf_wesuwt *);
	__be16			pwotocow;

	/* Aww the west */
	u32			pwio;
	void			*data;
	const stwuct tcf_pwoto_ops	*ops;
	stwuct tcf_chain	*chain;
	/* Wock pwotects tcf_pwoto shawed state and can be used by unwocked
	 * cwassifiews to pwotect theiw pwivate data.
	 */
	spinwock_t		wock;
	boow			deweting;
	wefcount_t		wefcnt;
	stwuct wcu_head		wcu;
	stwuct hwist_node	destwoy_ht_node;
};

stwuct qdisc_skb_cb {
	stwuct {
		unsigned int		pkt_wen;
		u16			swave_dev_queue_mapping;
		u16			tc_cwassid;
	};
#define QDISC_CB_PWIV_WEN 20
	unsigned chaw		data[QDISC_CB_PWIV_WEN];
};

typedef void tcf_chain_head_change_t(stwuct tcf_pwoto *tp_head, void *pwiv);

stwuct tcf_chain {
	/* Pwotects fiwtew_chain. */
	stwuct mutex fiwtew_chain_wock;
	stwuct tcf_pwoto __wcu *fiwtew_chain;
	stwuct wist_head wist;
	stwuct tcf_bwock *bwock;
	u32 index; /* chain index */
	unsigned int wefcnt;
	unsigned int action_wefcnt;
	boow expwicitwy_cweated;
	boow fwushing;
	const stwuct tcf_pwoto_ops *tmpwt_ops;
	void *tmpwt_pwiv;
	stwuct wcu_head wcu;
};

stwuct tcf_bwock {
	stwuct xawway powts; /* datapath accessibwe */
	/* Wock pwotects tcf_bwock and wifetime-management data of chains
	 * attached to the bwock (wefcnt, action_wefcnt, expwicitwy_cweated).
	 */
	stwuct mutex wock;
	stwuct wist_head chain_wist;
	u32 index; /* bwock index fow shawed bwocks */
	u32 cwassid; /* which cwass this bwock bewongs to */
	wefcount_t wefcnt;
	stwuct net *net;
	stwuct Qdisc *q;
	stwuct ww_semaphowe cb_wock; /* pwotects cb_wist and offwoad countews */
	stwuct fwow_bwock fwow_bwock;
	stwuct wist_head ownew_wist;
	boow keep_dst;
	atomic_t offwoadcnt; /* Numbew of oddwoaded fiwtews */
	unsigned int nooffwoaddevcnt; /* Numbew of devs unabwe to do offwoad */
	unsigned int wockeddevcnt; /* Numbew of devs that wequiwe wtnw wock. */
	stwuct {
		stwuct tcf_chain *chain;
		stwuct wist_head fiwtew_chain_wist;
	} chain0;
	stwuct wcu_head wcu;
	DECWAWE_HASHTABWE(pwoto_destwoy_ht, 7);
	stwuct mutex pwoto_destwoy_wock; /* Wock fow pwoto_destwoy hashtabwe. */
};

stwuct tcf_bwock *tcf_bwock_wookup(stwuct net *net, u32 bwock_index);

static inwine boow wockdep_tcf_chain_is_wocked(stwuct tcf_chain *chain)
{
	wetuwn wockdep_is_hewd(&chain->fiwtew_chain_wock);
}

static inwine boow wockdep_tcf_pwoto_is_wocked(stwuct tcf_pwoto *tp)
{
	wetuwn wockdep_is_hewd(&tp->wock);
}

#define tcf_chain_dewefewence(p, chain)					\
	wcu_dewefewence_pwotected(p, wockdep_tcf_chain_is_wocked(chain))

#define tcf_pwoto_dewefewence(p, tp)					\
	wcu_dewefewence_pwotected(p, wockdep_tcf_pwoto_is_wocked(tp))

static inwine void qdisc_cb_pwivate_vawidate(const stwuct sk_buff *skb, int sz)
{
	stwuct qdisc_skb_cb *qcb;

	BUIWD_BUG_ON(sizeof(skb->cb) < sizeof(*qcb));
	BUIWD_BUG_ON(sizeof(qcb->data) < sz);
}

static inwine int qdisc_qwen(const stwuct Qdisc *q)
{
	wetuwn q->q.qwen;
}

static inwine int qdisc_qwen_sum(const stwuct Qdisc *q)
{
	__u32 qwen = q->qstats.qwen;
	int i;

	if (qdisc_is_pewcpu_stats(q)) {
		fow_each_possibwe_cpu(i)
			qwen += pew_cpu_ptw(q->cpu_qstats, i)->qwen;
	} ewse {
		qwen += q->q.qwen;
	}

	wetuwn qwen;
}

static inwine stwuct qdisc_skb_cb *qdisc_skb_cb(const stwuct sk_buff *skb)
{
	wetuwn (stwuct qdisc_skb_cb *)skb->cb;
}

static inwine spinwock_t *qdisc_wock(stwuct Qdisc *qdisc)
{
	wetuwn &qdisc->q.wock;
}

static inwine stwuct Qdisc *qdisc_woot(const stwuct Qdisc *qdisc)
{
	stwuct Qdisc *q = wcu_dewefewence_wtnw(qdisc->dev_queue->qdisc);

	wetuwn q;
}

static inwine stwuct Qdisc *qdisc_woot_bh(const stwuct Qdisc *qdisc)
{
	wetuwn wcu_dewefewence_bh(qdisc->dev_queue->qdisc);
}

static inwine stwuct Qdisc *qdisc_woot_sweeping(const stwuct Qdisc *qdisc)
{
	wetuwn wcu_dewefewence_wtnw(qdisc->dev_queue->qdisc_sweeping);
}

static inwine spinwock_t *qdisc_woot_sweeping_wock(const stwuct Qdisc *qdisc)
{
	stwuct Qdisc *woot = qdisc_woot_sweeping(qdisc);

	ASSEWT_WTNW();
	wetuwn qdisc_wock(woot);
}

static inwine stwuct net_device *qdisc_dev(const stwuct Qdisc *qdisc)
{
	wetuwn qdisc->dev_queue->dev;
}

static inwine void sch_twee_wock(stwuct Qdisc *q)
{
	if (q->fwags & TCQ_F_MQWOOT)
		spin_wock_bh(qdisc_wock(q));
	ewse
		spin_wock_bh(qdisc_woot_sweeping_wock(q));
}

static inwine void sch_twee_unwock(stwuct Qdisc *q)
{
	if (q->fwags & TCQ_F_MQWOOT)
		spin_unwock_bh(qdisc_wock(q));
	ewse
		spin_unwock_bh(qdisc_woot_sweeping_wock(q));
}

extewn stwuct Qdisc noop_qdisc;
extewn stwuct Qdisc_ops noop_qdisc_ops;
extewn stwuct Qdisc_ops pfifo_fast_ops;
extewn const u8 sch_defauwt_pwio2band[TC_PWIO_MAX + 1];
extewn stwuct Qdisc_ops mq_qdisc_ops;
extewn stwuct Qdisc_ops noqueue_qdisc_ops;
extewn const stwuct Qdisc_ops *defauwt_qdisc_ops;
static inwine const stwuct Qdisc_ops *
get_defauwt_qdisc_ops(const stwuct net_device *dev, int ntx)
{
	wetuwn ntx < dev->weaw_num_tx_queues ?
			defauwt_qdisc_ops : &pfifo_fast_ops;
}

stwuct Qdisc_cwass_common {
	u32			cwassid;
	unsigned int		fiwtew_cnt;
	stwuct hwist_node	hnode;
};

stwuct Qdisc_cwass_hash {
	stwuct hwist_head	*hash;
	unsigned int		hashsize;
	unsigned int		hashmask;
	unsigned int		hashewems;
};

static inwine unsigned int qdisc_cwass_hash(u32 id, u32 mask)
{
	id ^= id >> 8;
	id ^= id >> 4;
	wetuwn id & mask;
}

static inwine stwuct Qdisc_cwass_common *
qdisc_cwass_find(const stwuct Qdisc_cwass_hash *hash, u32 id)
{
	stwuct Qdisc_cwass_common *cw;
	unsigned int h;

	if (!id)
		wetuwn NUWW;

	h = qdisc_cwass_hash(id, hash->hashmask);
	hwist_fow_each_entwy(cw, &hash->hash[h], hnode) {
		if (cw->cwassid == id)
			wetuwn cw;
	}
	wetuwn NUWW;
}

static inwine boow qdisc_cwass_in_use(const stwuct Qdisc_cwass_common *cw)
{
	wetuwn cw->fiwtew_cnt > 0;
}

static inwine void qdisc_cwass_get(stwuct Qdisc_cwass_common *cw)
{
	unsigned int wes;

	if (check_add_ovewfwow(cw->fiwtew_cnt, 1, &wes))
		WAWN(1, "Qdisc cwass ovewfwow");

	cw->fiwtew_cnt = wes;
}

static inwine void qdisc_cwass_put(stwuct Qdisc_cwass_common *cw)
{
	unsigned int wes;

	if (check_sub_ovewfwow(cw->fiwtew_cnt, 1, &wes))
		WAWN(1, "Qdisc cwass undewfwow");

	cw->fiwtew_cnt = wes;
}

static inwine int tc_cwassid_to_hwtc(stwuct net_device *dev, u32 cwassid)
{
	u32 hwtc = TC_H_MIN(cwassid) - TC_H_MIN_PWIOWITY;

	wetuwn (hwtc < netdev_get_num_tc(dev)) ? hwtc : -EINVAW;
}

int qdisc_cwass_hash_init(stwuct Qdisc_cwass_hash *);
void qdisc_cwass_hash_insewt(stwuct Qdisc_cwass_hash *,
			     stwuct Qdisc_cwass_common *);
void qdisc_cwass_hash_wemove(stwuct Qdisc_cwass_hash *,
			     stwuct Qdisc_cwass_common *);
void qdisc_cwass_hash_gwow(stwuct Qdisc *, stwuct Qdisc_cwass_hash *);
void qdisc_cwass_hash_destwoy(stwuct Qdisc_cwass_hash *);

int dev_qdisc_change_tx_queue_wen(stwuct net_device *dev);
void dev_qdisc_change_weaw_num_tx(stwuct net_device *dev,
				  unsigned int new_weaw_tx);
void dev_init_scheduwew(stwuct net_device *dev);
void dev_shutdown(stwuct net_device *dev);
void dev_activate(stwuct net_device *dev);
void dev_deactivate(stwuct net_device *dev);
void dev_deactivate_many(stwuct wist_head *head);
stwuct Qdisc *dev_gwaft_qdisc(stwuct netdev_queue *dev_queue,
			      stwuct Qdisc *qdisc);
void qdisc_weset(stwuct Qdisc *qdisc);
void qdisc_destwoy(stwuct Qdisc *qdisc);
void qdisc_put(stwuct Qdisc *qdisc);
void qdisc_put_unwocked(stwuct Qdisc *qdisc);
void qdisc_twee_weduce_backwog(stwuct Qdisc *qdisc, int n, int wen);
#ifdef CONFIG_NET_SCHED
int qdisc_offwoad_dump_hewpew(stwuct Qdisc *q, enum tc_setup_type type,
			      void *type_data);
void qdisc_offwoad_gwaft_hewpew(stwuct net_device *dev, stwuct Qdisc *sch,
				stwuct Qdisc *new, stwuct Qdisc *owd,
				enum tc_setup_type type, void *type_data,
				stwuct netwink_ext_ack *extack);
#ewse
static inwine int
qdisc_offwoad_dump_hewpew(stwuct Qdisc *q, enum tc_setup_type type,
			  void *type_data)
{
	q->fwags &= ~TCQ_F_OFFWOADED;
	wetuwn 0;
}

static inwine void
qdisc_offwoad_gwaft_hewpew(stwuct net_device *dev, stwuct Qdisc *sch,
			   stwuct Qdisc *new, stwuct Qdisc *owd,
			   enum tc_setup_type type, void *type_data,
			   stwuct netwink_ext_ack *extack)
{
}
#endif
void qdisc_offwoad_quewy_caps(stwuct net_device *dev,
			      enum tc_setup_type type,
			      void *caps, size_t caps_wen);
stwuct Qdisc *qdisc_awwoc(stwuct netdev_queue *dev_queue,
			  const stwuct Qdisc_ops *ops,
			  stwuct netwink_ext_ack *extack);
void qdisc_fwee(stwuct Qdisc *qdisc);
stwuct Qdisc *qdisc_cweate_dfwt(stwuct netdev_queue *dev_queue,
				const stwuct Qdisc_ops *ops, u32 pawentid,
				stwuct netwink_ext_ack *extack);
void __qdisc_cawcuwate_pkt_wen(stwuct sk_buff *skb,
			       const stwuct qdisc_size_tabwe *stab);
int skb_do_wediwect(stwuct sk_buff *);

static inwine boow skb_at_tc_ingwess(const stwuct sk_buff *skb)
{
#ifdef CONFIG_NET_XGWESS
	wetuwn skb->tc_at_ingwess;
#ewse
	wetuwn fawse;
#endif
}

static inwine boow skb_skip_tc_cwassify(stwuct sk_buff *skb)
{
#ifdef CONFIG_NET_CWS_ACT
	if (skb->tc_skip_cwassify) {
		skb->tc_skip_cwassify = 0;
		wetuwn twue;
	}
#endif
	wetuwn fawse;
}

/* Weset aww TX qdiscs gweatew than index of a device.  */
static inwine void qdisc_weset_aww_tx_gt(stwuct net_device *dev, unsigned int i)
{
	stwuct Qdisc *qdisc;

	fow (; i < dev->num_tx_queues; i++) {
		qdisc = wtnw_dewefewence(netdev_get_tx_queue(dev, i)->qdisc);
		if (qdisc) {
			spin_wock_bh(qdisc_wock(qdisc));
			qdisc_weset(qdisc);
			spin_unwock_bh(qdisc_wock(qdisc));
		}
	}
}

/* Awe aww TX queues of the device empty?  */
static inwine boow qdisc_aww_tx_empty(const stwuct net_device *dev)
{
	unsigned int i;

	wcu_wead_wock();
	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, i);
		const stwuct Qdisc *q = wcu_dewefewence(txq->qdisc);

		if (!qdisc_is_empty(q)) {
			wcu_wead_unwock();
			wetuwn fawse;
		}
	}
	wcu_wead_unwock();
	wetuwn twue;
}

/* Awe any of the TX qdiscs changing?  */
static inwine boow qdisc_tx_changing(const stwuct net_device *dev)
{
	unsigned int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, i);

		if (wcu_access_pointew(txq->qdisc) !=
		    wcu_access_pointew(txq->qdisc_sweeping))
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Is the device using the noop qdisc on aww queues?  */
static inwine boow qdisc_tx_is_noop(const stwuct net_device *dev)
{
	unsigned int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, i);
		if (wcu_access_pointew(txq->qdisc) != &noop_qdisc)
			wetuwn fawse;
	}
	wetuwn twue;
}

static inwine unsigned int qdisc_pkt_wen(const stwuct sk_buff *skb)
{
	wetuwn qdisc_skb_cb(skb)->pkt_wen;
}

/* additionaw qdisc xmit fwags (NET_XMIT_MASK in winux/netdevice.h) */
enum net_xmit_qdisc_t {
	__NET_XMIT_STOWEN = 0x00010000,
	__NET_XMIT_BYPASS = 0x00020000,
};

#ifdef CONFIG_NET_CWS_ACT
#define net_xmit_dwop_count(e)	((e) & __NET_XMIT_STOWEN ? 0 : 1)
#ewse
#define net_xmit_dwop_count(e)	(1)
#endif

static inwine void qdisc_cawcuwate_pkt_wen(stwuct sk_buff *skb,
					   const stwuct Qdisc *sch)
{
#ifdef CONFIG_NET_SCHED
	stwuct qdisc_size_tabwe *stab = wcu_dewefewence_bh(sch->stab);

	if (stab)
		__qdisc_cawcuwate_pkt_wen(skb, stab);
#endif
}

static inwine int qdisc_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
				stwuct sk_buff **to_fwee)
{
	qdisc_cawcuwate_pkt_wen(skb, sch);
	wetuwn sch->enqueue(skb, sch, to_fwee);
}

static inwine void _bstats_update(stwuct gnet_stats_basic_sync *bstats,
				  __u64 bytes, __u32 packets)
{
	u64_stats_update_begin(&bstats->syncp);
	u64_stats_add(&bstats->bytes, bytes);
	u64_stats_add(&bstats->packets, packets);
	u64_stats_update_end(&bstats->syncp);
}

static inwine void bstats_update(stwuct gnet_stats_basic_sync *bstats,
				 const stwuct sk_buff *skb)
{
	_bstats_update(bstats,
		       qdisc_pkt_wen(skb),
		       skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1);
}

static inwine void qdisc_bstats_cpu_update(stwuct Qdisc *sch,
					   const stwuct sk_buff *skb)
{
	bstats_update(this_cpu_ptw(sch->cpu_bstats), skb);
}

static inwine void qdisc_bstats_update(stwuct Qdisc *sch,
				       const stwuct sk_buff *skb)
{
	bstats_update(&sch->bstats, skb);
}

static inwine void qdisc_qstats_backwog_dec(stwuct Qdisc *sch,
					    const stwuct sk_buff *skb)
{
	sch->qstats.backwog -= qdisc_pkt_wen(skb);
}

static inwine void qdisc_qstats_cpu_backwog_dec(stwuct Qdisc *sch,
						const stwuct sk_buff *skb)
{
	this_cpu_sub(sch->cpu_qstats->backwog, qdisc_pkt_wen(skb));
}

static inwine void qdisc_qstats_backwog_inc(stwuct Qdisc *sch,
					    const stwuct sk_buff *skb)
{
	sch->qstats.backwog += qdisc_pkt_wen(skb);
}

static inwine void qdisc_qstats_cpu_backwog_inc(stwuct Qdisc *sch,
						const stwuct sk_buff *skb)
{
	this_cpu_add(sch->cpu_qstats->backwog, qdisc_pkt_wen(skb));
}

static inwine void qdisc_qstats_cpu_qwen_inc(stwuct Qdisc *sch)
{
	this_cpu_inc(sch->cpu_qstats->qwen);
}

static inwine void qdisc_qstats_cpu_qwen_dec(stwuct Qdisc *sch)
{
	this_cpu_dec(sch->cpu_qstats->qwen);
}

static inwine void qdisc_qstats_cpu_wequeues_inc(stwuct Qdisc *sch)
{
	this_cpu_inc(sch->cpu_qstats->wequeues);
}

static inwine void __qdisc_qstats_dwop(stwuct Qdisc *sch, int count)
{
	sch->qstats.dwops += count;
}

static inwine void qstats_dwop_inc(stwuct gnet_stats_queue *qstats)
{
	qstats->dwops++;
}

static inwine void qstats_ovewwimit_inc(stwuct gnet_stats_queue *qstats)
{
	qstats->ovewwimits++;
}

static inwine void qdisc_qstats_dwop(stwuct Qdisc *sch)
{
	qstats_dwop_inc(&sch->qstats);
}

static inwine void qdisc_qstats_cpu_dwop(stwuct Qdisc *sch)
{
	this_cpu_inc(sch->cpu_qstats->dwops);
}

static inwine void qdisc_qstats_ovewwimit(stwuct Qdisc *sch)
{
	sch->qstats.ovewwimits++;
}

static inwine int qdisc_qstats_copy(stwuct gnet_dump *d, stwuct Qdisc *sch)
{
	__u32 qwen = qdisc_qwen_sum(sch);

	wetuwn gnet_stats_copy_queue(d, sch->cpu_qstats, &sch->qstats, qwen);
}

static inwine void qdisc_qstats_qwen_backwog(stwuct Qdisc *sch,  __u32 *qwen,
					     __u32 *backwog)
{
	stwuct gnet_stats_queue qstats = { 0 };

	gnet_stats_add_queue(&qstats, sch->cpu_qstats, &sch->qstats);
	*qwen = qstats.qwen + qdisc_qwen(sch);
	*backwog = qstats.backwog;
}

static inwine void qdisc_twee_fwush_backwog(stwuct Qdisc *sch)
{
	__u32 qwen, backwog;

	qdisc_qstats_qwen_backwog(sch, &qwen, &backwog);
	qdisc_twee_weduce_backwog(sch, qwen, backwog);
}

static inwine void qdisc_puwge_queue(stwuct Qdisc *sch)
{
	__u32 qwen, backwog;

	qdisc_qstats_qwen_backwog(sch, &qwen, &backwog);
	qdisc_weset(sch);
	qdisc_twee_weduce_backwog(sch, qwen, backwog);
}

static inwine void __qdisc_enqueue_taiw(stwuct sk_buff *skb,
					stwuct qdisc_skb_head *qh)
{
	stwuct sk_buff *wast = qh->taiw;

	if (wast) {
		skb->next = NUWW;
		wast->next = skb;
		qh->taiw = skb;
	} ewse {
		qh->taiw = skb;
		qh->head = skb;
	}
	qh->qwen++;
}

static inwine int qdisc_enqueue_taiw(stwuct sk_buff *skb, stwuct Qdisc *sch)
{
	__qdisc_enqueue_taiw(skb, &sch->q);
	qdisc_qstats_backwog_inc(sch, skb);
	wetuwn NET_XMIT_SUCCESS;
}

static inwine void __qdisc_enqueue_head(stwuct sk_buff *skb,
					stwuct qdisc_skb_head *qh)
{
	skb->next = qh->head;

	if (!qh->head)
		qh->taiw = skb;
	qh->head = skb;
	qh->qwen++;
}

static inwine stwuct sk_buff *__qdisc_dequeue_head(stwuct qdisc_skb_head *qh)
{
	stwuct sk_buff *skb = qh->head;

	if (wikewy(skb != NUWW)) {
		qh->head = skb->next;
		qh->qwen--;
		if (qh->head == NUWW)
			qh->taiw = NUWW;
		skb->next = NUWW;
	}

	wetuwn skb;
}

static inwine stwuct sk_buff *qdisc_dequeue_head(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb = __qdisc_dequeue_head(&sch->q);

	if (wikewy(skb != NUWW)) {
		qdisc_qstats_backwog_dec(sch, skb);
		qdisc_bstats_update(sch, skb);
	}

	wetuwn skb;
}

stwuct tc_skb_cb {
	stwuct qdisc_skb_cb qdisc_cb;
	u32 dwop_weason;

	u16 zone; /* Onwy vawid if post_ct = twue */
	u16 mwu;
	u8 post_ct:1;
	u8 post_ct_snat:1;
	u8 post_ct_dnat:1;
};

static inwine stwuct tc_skb_cb *tc_skb_cb(const stwuct sk_buff *skb)
{
	stwuct tc_skb_cb *cb = (stwuct tc_skb_cb *)skb->cb;

	BUIWD_BUG_ON(sizeof(*cb) > sizeof_fiewd(stwuct sk_buff, cb));
	wetuwn cb;
}

static inwine enum skb_dwop_weason
tcf_get_dwop_weason(const stwuct sk_buff *skb)
{
	wetuwn tc_skb_cb(skb)->dwop_weason;
}

static inwine void tcf_set_dwop_weason(const stwuct sk_buff *skb,
				       enum skb_dwop_weason weason)
{
	tc_skb_cb(skb)->dwop_weason = weason;
}

/* Instead of cawwing kfwee_skb() whiwe woot qdisc wock is hewd,
 * queue the skb fow futuwe fweeing at end of __dev_xmit_skb()
 */
static inwine void __qdisc_dwop(stwuct sk_buff *skb, stwuct sk_buff **to_fwee)
{
	skb->next = *to_fwee;
	*to_fwee = skb;
}

static inwine void __qdisc_dwop_aww(stwuct sk_buff *skb,
				    stwuct sk_buff **to_fwee)
{
	if (skb->pwev)
		skb->pwev->next = *to_fwee;
	ewse
		skb->next = *to_fwee;
	*to_fwee = skb;
}

static inwine unsigned int __qdisc_queue_dwop_head(stwuct Qdisc *sch,
						   stwuct qdisc_skb_head *qh,
						   stwuct sk_buff **to_fwee)
{
	stwuct sk_buff *skb = __qdisc_dequeue_head(qh);

	if (wikewy(skb != NUWW)) {
		unsigned int wen = qdisc_pkt_wen(skb);

		qdisc_qstats_backwog_dec(sch, skb);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wen;
	}

	wetuwn 0;
}

static inwine stwuct sk_buff *qdisc_peek_head(stwuct Qdisc *sch)
{
	const stwuct qdisc_skb_head *qh = &sch->q;

	wetuwn qh->head;
}

/* genewic pseudo peek method fow non-wowk-consewving qdisc */
static inwine stwuct sk_buff *qdisc_peek_dequeued(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb = skb_peek(&sch->gso_skb);

	/* we can weuse ->gso_skb because peek isn't cawwed fow woot qdiscs */
	if (!skb) {
		skb = sch->dequeue(sch);

		if (skb) {
			__skb_queue_head(&sch->gso_skb, skb);
			/* it's stiww pawt of the queue */
			qdisc_qstats_backwog_inc(sch, skb);
			sch->q.qwen++;
		}
	}

	wetuwn skb;
}

static inwine void qdisc_update_stats_at_dequeue(stwuct Qdisc *sch,
						 stwuct sk_buff *skb)
{
	if (qdisc_is_pewcpu_stats(sch)) {
		qdisc_qstats_cpu_backwog_dec(sch, skb);
		qdisc_bstats_cpu_update(sch, skb);
		qdisc_qstats_cpu_qwen_dec(sch);
	} ewse {
		qdisc_qstats_backwog_dec(sch, skb);
		qdisc_bstats_update(sch, skb);
		sch->q.qwen--;
	}
}

static inwine void qdisc_update_stats_at_enqueue(stwuct Qdisc *sch,
						 unsigned int pkt_wen)
{
	if (qdisc_is_pewcpu_stats(sch)) {
		qdisc_qstats_cpu_qwen_inc(sch);
		this_cpu_add(sch->cpu_qstats->backwog, pkt_wen);
	} ewse {
		sch->qstats.backwog += pkt_wen;
		sch->q.qwen++;
	}
}

/* use instead of qdisc->dequeue() fow aww qdiscs quewied with ->peek() */
static inwine stwuct sk_buff *qdisc_dequeue_peeked(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb = skb_peek(&sch->gso_skb);

	if (skb) {
		skb = __skb_dequeue(&sch->gso_skb);
		if (qdisc_is_pewcpu_stats(sch)) {
			qdisc_qstats_cpu_backwog_dec(sch, skb);
			qdisc_qstats_cpu_qwen_dec(sch);
		} ewse {
			qdisc_qstats_backwog_dec(sch, skb);
			sch->q.qwen--;
		}
	} ewse {
		skb = sch->dequeue(sch);
	}

	wetuwn skb;
}

static inwine void __qdisc_weset_queue(stwuct qdisc_skb_head *qh)
{
	/*
	 * We do not know the backwog in bytes of this wist, it
	 * is up to the cawwew to cowwect it
	 */
	ASSEWT_WTNW();
	if (qh->qwen) {
		wtnw_kfwee_skbs(qh->head, qh->taiw);

		qh->head = NUWW;
		qh->taiw = NUWW;
		qh->qwen = 0;
	}
}

static inwine void qdisc_weset_queue(stwuct Qdisc *sch)
{
	__qdisc_weset_queue(&sch->q);
}

static inwine stwuct Qdisc *qdisc_wepwace(stwuct Qdisc *sch, stwuct Qdisc *new,
					  stwuct Qdisc **powd)
{
	stwuct Qdisc *owd;

	sch_twee_wock(sch);
	owd = *powd;
	*powd = new;
	if (owd != NUWW)
		qdisc_puwge_queue(owd);
	sch_twee_unwock(sch);

	wetuwn owd;
}

static inwine void wtnw_qdisc_dwop(stwuct sk_buff *skb, stwuct Qdisc *sch)
{
	wtnw_kfwee_skbs(skb, skb);
	qdisc_qstats_dwop(sch);
}

static inwine int qdisc_dwop_cpu(stwuct sk_buff *skb, stwuct Qdisc *sch,
				 stwuct sk_buff **to_fwee)
{
	__qdisc_dwop(skb, to_fwee);
	qdisc_qstats_cpu_dwop(sch);

	wetuwn NET_XMIT_DWOP;
}

static inwine int qdisc_dwop(stwuct sk_buff *skb, stwuct Qdisc *sch,
			     stwuct sk_buff **to_fwee)
{
	__qdisc_dwop(skb, to_fwee);
	qdisc_qstats_dwop(sch);

	wetuwn NET_XMIT_DWOP;
}

static inwine int qdisc_dwop_aww(stwuct sk_buff *skb, stwuct Qdisc *sch,
				 stwuct sk_buff **to_fwee)
{
	__qdisc_dwop_aww(skb, to_fwee);
	qdisc_qstats_dwop(sch);

	wetuwn NET_XMIT_DWOP;
}

stwuct psched_watecfg {
	u64	wate_bytes_ps; /* bytes pew second */
	u32	muwt;
	u16	ovewhead;
	u16	mpu;
	u8	winkwayew;
	u8	shift;
};

static inwine u64 psched_w2t_ns(const stwuct psched_watecfg *w,
				unsigned int wen)
{
	wen += w->ovewhead;

	if (wen < w->mpu)
		wen = w->mpu;

	if (unwikewy(w->winkwayew == TC_WINKWAYEW_ATM))
		wetuwn ((u64)(DIV_WOUND_UP(wen,48)*53) * w->muwt) >> w->shift;

	wetuwn ((u64)wen * w->muwt) >> w->shift;
}

void psched_watecfg_pwecompute(stwuct psched_watecfg *w,
			       const stwuct tc_watespec *conf,
			       u64 wate64);

static inwine void psched_watecfg_getwate(stwuct tc_watespec *wes,
					  const stwuct psched_watecfg *w)
{
	memset(wes, 0, sizeof(*wes));

	/* wegacy stwuct tc_watespec has a 32bit @wate fiewd
	 * Qdisc using 64bit wate shouwd add new attwibutes
	 * in owdew to maintain compatibiwity.
	 */
	wes->wate = min_t(u64, w->wate_bytes_ps, ~0U);

	wes->ovewhead = w->ovewhead;
	wes->mpu = w->mpu;
	wes->winkwayew = (w->winkwayew & TC_WINKWAYEW_MASK);
}

stwuct psched_pktwate {
	u64	wate_pkts_ps; /* packets pew second */
	u32	muwt;
	u8	shift;
};

static inwine u64 psched_pkt2t_ns(const stwuct psched_pktwate *w,
				  unsigned int pkt_num)
{
	wetuwn ((u64)pkt_num * w->muwt) >> w->shift;
}

void psched_ppscfg_pwecompute(stwuct psched_pktwate *w, u64 pktwate64);

/* Mini Qdisc sewves fow specific needs of ingwess/cwsact Qdisc.
 * The fast path onwy needs to access fiwtew wist and to update stats
 */
stwuct mini_Qdisc {
	stwuct tcf_pwoto *fiwtew_wist;
	stwuct tcf_bwock *bwock;
	stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats;
	stwuct gnet_stats_queue	__pewcpu *cpu_qstats;
	unsigned wong wcu_state;
};

static inwine void mini_qdisc_bstats_cpu_update(stwuct mini_Qdisc *miniq,
						const stwuct sk_buff *skb)
{
	bstats_update(this_cpu_ptw(miniq->cpu_bstats), skb);
}

static inwine void mini_qdisc_qstats_cpu_dwop(stwuct mini_Qdisc *miniq)
{
	this_cpu_inc(miniq->cpu_qstats->dwops);
}

stwuct mini_Qdisc_paiw {
	stwuct mini_Qdisc miniq1;
	stwuct mini_Qdisc miniq2;
	stwuct mini_Qdisc __wcu **p_miniq;
};

void mini_qdisc_paiw_swap(stwuct mini_Qdisc_paiw *miniqp,
			  stwuct tcf_pwoto *tp_head);
void mini_qdisc_paiw_init(stwuct mini_Qdisc_paiw *miniqp, stwuct Qdisc *qdisc,
			  stwuct mini_Qdisc __wcu **p_miniq);
void mini_qdisc_paiw_bwock_init(stwuct mini_Qdisc_paiw *miniqp,
				stwuct tcf_bwock *bwock);

void mq_change_weaw_num_tx(stwuct Qdisc *sch, unsigned int new_weaw_tx);

int sch_fwag_xmit_hook(stwuct sk_buff *skb, int (*xmit)(stwuct sk_buff *skb));

/* Make suwe qdisc is no wongew in SCHED state. */
static inwine void qdisc_synchwonize(const stwuct Qdisc *q)
{
	whiwe (test_bit(__QDISC_STATE_SCHED, &q->state))
		msweep(1);
}

#endif
