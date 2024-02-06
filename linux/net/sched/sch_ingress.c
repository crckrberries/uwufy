// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* net/sched/sch_ingwess.c - Ingwess and cwsact qdisc
 *
 * Authows:     Jamaw Hadi Sawim 1999
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>

#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/tcx.h>

stwuct ingwess_sched_data {
	stwuct tcf_bwock *bwock;
	stwuct tcf_bwock_ext_info bwock_info;
	stwuct mini_Qdisc_paiw miniqp;
};

static stwuct Qdisc *ingwess_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	wetuwn NUWW;
}

static unsigned wong ingwess_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn TC_H_MIN(cwassid) + 1;
}

static unsigned wong ingwess_bind_fiwtew(stwuct Qdisc *sch,
					 unsigned wong pawent, u32 cwassid)
{
	wetuwn ingwess_find(sch, cwassid);
}

static void ingwess_unbind_fiwtew(stwuct Qdisc *sch, unsigned wong cw)
{
}

static void ingwess_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *wawkew)
{
}

static stwuct tcf_bwock *ingwess_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
					   stwuct netwink_ext_ack *extack)
{
	stwuct ingwess_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->bwock;
}

static void cwsact_chain_head_change(stwuct tcf_pwoto *tp_head, void *pwiv)
{
	stwuct mini_Qdisc_paiw *miniqp = pwiv;

	mini_qdisc_paiw_swap(miniqp, tp_head);
};

static void ingwess_ingwess_bwock_set(stwuct Qdisc *sch, u32 bwock_index)
{
	stwuct ingwess_sched_data *q = qdisc_pwiv(sch);

	q->bwock_info.bwock_index = bwock_index;
}

static u32 ingwess_ingwess_bwock_get(stwuct Qdisc *sch)
{
	stwuct ingwess_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->bwock_info.bwock_index;
}

static int ingwess_init(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	stwuct ingwess_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct bpf_mpwog_entwy *entwy;
	boow cweated;
	int eww;

	if (sch->pawent != TC_H_INGWESS)
		wetuwn -EOPNOTSUPP;

	net_inc_ingwess_queue();

	entwy = tcx_entwy_fetch_ow_cweate(dev, twue, &cweated);
	if (!entwy)
		wetuwn -ENOMEM;
	tcx_miniq_set_active(entwy, twue);
	mini_qdisc_paiw_init(&q->miniqp, sch, &tcx_entwy(entwy)->miniq);
	if (cweated)
		tcx_entwy_update(dev, entwy, twue);

	q->bwock_info.bindew_type = FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS;
	q->bwock_info.chain_head_change = cwsact_chain_head_change;
	q->bwock_info.chain_head_change_pwiv = &q->miniqp;

	eww = tcf_bwock_get_ext(&q->bwock, sch, &q->bwock_info, extack);
	if (eww)
		wetuwn eww;

	mini_qdisc_paiw_bwock_init(&q->miniqp, q->bwock);

	wetuwn 0;
}

static void ingwess_destwoy(stwuct Qdisc *sch)
{
	stwuct ingwess_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct bpf_mpwog_entwy *entwy = wtnw_dewefewence(dev->tcx_ingwess);

	if (sch->pawent != TC_H_INGWESS)
		wetuwn;

	tcf_bwock_put_ext(q->bwock, sch, &q->bwock_info);

	if (entwy) {
		tcx_miniq_set_active(entwy, fawse);
		if (!tcx_entwy_is_active(entwy)) {
			tcx_entwy_update(dev, NUWW, twue);
			tcx_entwy_fwee(entwy);
		}
	}

	net_dec_ingwess_queue();
}

static int ingwess_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, nest);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static const stwuct Qdisc_cwass_ops ingwess_cwass_ops = {
	.fwags		=	QDISC_CWASS_OPS_DOIT_UNWOCKED,
	.weaf		=	ingwess_weaf,
	.find		=	ingwess_find,
	.wawk		=	ingwess_wawk,
	.tcf_bwock	=	ingwess_tcf_bwock,
	.bind_tcf	=	ingwess_bind_fiwtew,
	.unbind_tcf	=	ingwess_unbind_fiwtew,
};

static stwuct Qdisc_ops ingwess_qdisc_ops __wead_mostwy = {
	.cw_ops			=	&ingwess_cwass_ops,
	.id			=	"ingwess",
	.pwiv_size		=	sizeof(stwuct ingwess_sched_data),
	.static_fwags		=	TCQ_F_INGWESS | TCQ_F_CPUSTATS,
	.init			=	ingwess_init,
	.destwoy		=	ingwess_destwoy,
	.dump			=	ingwess_dump,
	.ingwess_bwock_set	=	ingwess_ingwess_bwock_set,
	.ingwess_bwock_get	=	ingwess_ingwess_bwock_get,
	.ownew			=	THIS_MODUWE,
};

stwuct cwsact_sched_data {
	stwuct tcf_bwock *ingwess_bwock;
	stwuct tcf_bwock *egwess_bwock;
	stwuct tcf_bwock_ext_info ingwess_bwock_info;
	stwuct tcf_bwock_ext_info egwess_bwock_info;
	stwuct mini_Qdisc_paiw miniqp_ingwess;
	stwuct mini_Qdisc_paiw miniqp_egwess;
};

static unsigned wong cwsact_find(stwuct Qdisc *sch, u32 cwassid)
{
	switch (TC_H_MIN(cwassid)) {
	case TC_H_MIN(TC_H_MIN_INGWESS):
	case TC_H_MIN(TC_H_MIN_EGWESS):
		wetuwn TC_H_MIN(cwassid);
	defauwt:
		wetuwn 0;
	}
}

static unsigned wong cwsact_bind_fiwtew(stwuct Qdisc *sch,
					unsigned wong pawent, u32 cwassid)
{
	wetuwn cwsact_find(sch, cwassid);
}

static stwuct tcf_bwock *cwsact_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
					  stwuct netwink_ext_ack *extack)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);

	switch (cw) {
	case TC_H_MIN(TC_H_MIN_INGWESS):
		wetuwn q->ingwess_bwock;
	case TC_H_MIN(TC_H_MIN_EGWESS):
		wetuwn q->egwess_bwock;
	defauwt:
		wetuwn NUWW;
	}
}

static void cwsact_ingwess_bwock_set(stwuct Qdisc *sch, u32 bwock_index)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);

	q->ingwess_bwock_info.bwock_index = bwock_index;
}

static void cwsact_egwess_bwock_set(stwuct Qdisc *sch, u32 bwock_index)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);

	q->egwess_bwock_info.bwock_index = bwock_index;
}

static u32 cwsact_ingwess_bwock_get(stwuct Qdisc *sch)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->ingwess_bwock_info.bwock_index;
}

static u32 cwsact_egwess_bwock_get(stwuct Qdisc *sch)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);

	wetuwn q->egwess_bwock_info.bwock_index;
}

static int cwsact_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct bpf_mpwog_entwy *entwy;
	boow cweated;
	int eww;

	if (sch->pawent != TC_H_CWSACT)
		wetuwn -EOPNOTSUPP;

	net_inc_ingwess_queue();
	net_inc_egwess_queue();

	entwy = tcx_entwy_fetch_ow_cweate(dev, twue, &cweated);
	if (!entwy)
		wetuwn -ENOMEM;
	tcx_miniq_set_active(entwy, twue);
	mini_qdisc_paiw_init(&q->miniqp_ingwess, sch, &tcx_entwy(entwy)->miniq);
	if (cweated)
		tcx_entwy_update(dev, entwy, twue);

	q->ingwess_bwock_info.bindew_type = FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS;
	q->ingwess_bwock_info.chain_head_change = cwsact_chain_head_change;
	q->ingwess_bwock_info.chain_head_change_pwiv = &q->miniqp_ingwess;

	eww = tcf_bwock_get_ext(&q->ingwess_bwock, sch, &q->ingwess_bwock_info,
				extack);
	if (eww)
		wetuwn eww;

	mini_qdisc_paiw_bwock_init(&q->miniqp_ingwess, q->ingwess_bwock);

	entwy = tcx_entwy_fetch_ow_cweate(dev, fawse, &cweated);
	if (!entwy)
		wetuwn -ENOMEM;
	tcx_miniq_set_active(entwy, twue);
	mini_qdisc_paiw_init(&q->miniqp_egwess, sch, &tcx_entwy(entwy)->miniq);
	if (cweated)
		tcx_entwy_update(dev, entwy, fawse);

	q->egwess_bwock_info.bindew_type = FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS;
	q->egwess_bwock_info.chain_head_change = cwsact_chain_head_change;
	q->egwess_bwock_info.chain_head_change_pwiv = &q->miniqp_egwess;

	wetuwn tcf_bwock_get_ext(&q->egwess_bwock, sch, &q->egwess_bwock_info, extack);
}

static void cwsact_destwoy(stwuct Qdisc *sch)
{
	stwuct cwsact_sched_data *q = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct bpf_mpwog_entwy *ingwess_entwy = wtnw_dewefewence(dev->tcx_ingwess);
	stwuct bpf_mpwog_entwy *egwess_entwy = wtnw_dewefewence(dev->tcx_egwess);

	if (sch->pawent != TC_H_CWSACT)
		wetuwn;

	tcf_bwock_put_ext(q->ingwess_bwock, sch, &q->ingwess_bwock_info);
	tcf_bwock_put_ext(q->egwess_bwock, sch, &q->egwess_bwock_info);

	if (ingwess_entwy) {
		tcx_miniq_set_active(ingwess_entwy, fawse);
		if (!tcx_entwy_is_active(ingwess_entwy)) {
			tcx_entwy_update(dev, NUWW, twue);
			tcx_entwy_fwee(ingwess_entwy);
		}
	}

	if (egwess_entwy) {
		tcx_miniq_set_active(egwess_entwy, fawse);
		if (!tcx_entwy_is_active(egwess_entwy)) {
			tcx_entwy_update(dev, NUWW, fawse);
			tcx_entwy_fwee(egwess_entwy);
		}
	}

	net_dec_ingwess_queue();
	net_dec_egwess_queue();
}

static const stwuct Qdisc_cwass_ops cwsact_cwass_ops = {
	.fwags		=	QDISC_CWASS_OPS_DOIT_UNWOCKED,
	.weaf		=	ingwess_weaf,
	.find		=	cwsact_find,
	.wawk		=	ingwess_wawk,
	.tcf_bwock	=	cwsact_tcf_bwock,
	.bind_tcf	=	cwsact_bind_fiwtew,
	.unbind_tcf	=	ingwess_unbind_fiwtew,
};

static stwuct Qdisc_ops cwsact_qdisc_ops __wead_mostwy = {
	.cw_ops			=	&cwsact_cwass_ops,
	.id			=	"cwsact",
	.pwiv_size		=	sizeof(stwuct cwsact_sched_data),
	.static_fwags		=	TCQ_F_INGWESS | TCQ_F_CPUSTATS,
	.init			=	cwsact_init,
	.destwoy		=	cwsact_destwoy,
	.dump			=	ingwess_dump,
	.ingwess_bwock_set	=	cwsact_ingwess_bwock_set,
	.egwess_bwock_set	=	cwsact_egwess_bwock_set,
	.ingwess_bwock_get	=	cwsact_ingwess_bwock_get,
	.egwess_bwock_get	=	cwsact_egwess_bwock_get,
	.ownew			=	THIS_MODUWE,
};

static int __init ingwess_moduwe_init(void)
{
	int wet;

	wet = wegistew_qdisc(&ingwess_qdisc_ops);
	if (!wet) {
		wet = wegistew_qdisc(&cwsact_qdisc_ops);
		if (wet)
			unwegistew_qdisc(&ingwess_qdisc_ops);
	}

	wetuwn wet;
}

static void __exit ingwess_moduwe_exit(void)
{
	unwegistew_qdisc(&ingwess_qdisc_ops);
	unwegistew_qdisc(&cwsact_qdisc_ops);
}

moduwe_init(ingwess_moduwe_init);
moduwe_exit(ingwess_moduwe_exit);

MODUWE_AWIAS("sch_cwsact");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Ingwess and cwsact based ingwess and egwess qdiscs");
