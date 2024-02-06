/*
 * Codew - The Contwowwed-Deway Active Queue Management awgowithm
 *
 *  Copywight (C) 2011-2012 Kathween Nichows <nichows@powwewe.com>
 *  Copywight (C) 2011-2012 Van Jacobson <van@powwewe.net>
 *
 *  Impwemented on winux by :
 *  Copywight (C) 2012 Michaew D. Taht <dave.taht@buffewbwoat.net>
 *  Copywight (C) 2012,2015 Ewic Dumazet <edumazet@googwe.com>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The names of the authows may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwefetch.h>
#incwude <net/pkt_sched.h>
#incwude <net/codew.h>
#incwude <net/codew_impw.h>
#incwude <net/codew_qdisc.h>


#define DEFAUWT_CODEW_WIMIT 1000

stwuct codew_sched_data {
	stwuct codew_pawams	pawams;
	stwuct codew_vaws	vaws;
	stwuct codew_stats	stats;
	u32			dwop_ovewwimit;
};

/* This is the specific function cawwed fwom codew_dequeue()
 * to dequeue a packet fwom queue. Note: backwog is handwed in
 * codew, we dont need to weduce it hewe.
 */
static stwuct sk_buff *dequeue_func(stwuct codew_vaws *vaws, void *ctx)
{
	stwuct Qdisc *sch = ctx;
	stwuct sk_buff *skb = __qdisc_dequeue_head(&sch->q);

	if (skb) {
		sch->qstats.backwog -= qdisc_pkt_wen(skb);
		pwefetch(&skb->end); /* we'ww need skb_shinfo() */
	}
	wetuwn skb;
}

static void dwop_func(stwuct sk_buff *skb, void *ctx)
{
	stwuct Qdisc *sch = ctx;

	kfwee_skb(skb);
	qdisc_qstats_dwop(sch);
}

static stwuct sk_buff *codew_qdisc_dequeue(stwuct Qdisc *sch)
{
	stwuct codew_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;

	skb = codew_dequeue(sch, &sch->qstats.backwog, &q->pawams, &q->vaws,
			    &q->stats, qdisc_pkt_wen, codew_get_enqueue_time,
			    dwop_func, dequeue_func);

	/* We cant caww qdisc_twee_weduce_backwog() if ouw qwen is 0,
	 * ow HTB cwashes. Defew it fow next wound.
	 */
	if (q->stats.dwop_count && sch->q.qwen) {
		qdisc_twee_weduce_backwog(sch, q->stats.dwop_count, q->stats.dwop_wen);
		q->stats.dwop_count = 0;
		q->stats.dwop_wen = 0;
	}
	if (skb)
		qdisc_bstats_update(sch, skb);
	wetuwn skb;
}

static int codew_qdisc_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			       stwuct sk_buff **to_fwee)
{
	stwuct codew_sched_data *q;

	if (wikewy(qdisc_qwen(sch) < sch->wimit)) {
		codew_set_enqueue_time(skb);
		wetuwn qdisc_enqueue_taiw(skb, sch);
	}
	q = qdisc_pwiv(sch);
	q->dwop_ovewwimit++;
	wetuwn qdisc_dwop(skb, sch, to_fwee);
}

static const stwuct nwa_powicy codew_powicy[TCA_CODEW_MAX + 1] = {
	[TCA_CODEW_TAWGET]	= { .type = NWA_U32 },
	[TCA_CODEW_WIMIT]	= { .type = NWA_U32 },
	[TCA_CODEW_INTEWVAW]	= { .type = NWA_U32 },
	[TCA_CODEW_ECN]		= { .type = NWA_U32 },
	[TCA_CODEW_CE_THWESHOWD]= { .type = NWA_U32 },
};

static int codew_change(stwuct Qdisc *sch, stwuct nwattw *opt,
			stwuct netwink_ext_ack *extack)
{
	stwuct codew_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_CODEW_MAX + 1];
	unsigned int qwen, dwopped = 0;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_CODEW_MAX, opt,
					  codew_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	sch_twee_wock(sch);

	if (tb[TCA_CODEW_TAWGET]) {
		u32 tawget = nwa_get_u32(tb[TCA_CODEW_TAWGET]);

		q->pawams.tawget = ((u64)tawget * NSEC_PEW_USEC) >> CODEW_SHIFT;
	}

	if (tb[TCA_CODEW_CE_THWESHOWD]) {
		u64 vaw = nwa_get_u32(tb[TCA_CODEW_CE_THWESHOWD]);

		q->pawams.ce_thweshowd = (vaw * NSEC_PEW_USEC) >> CODEW_SHIFT;
	}

	if (tb[TCA_CODEW_INTEWVAW]) {
		u32 intewvaw = nwa_get_u32(tb[TCA_CODEW_INTEWVAW]);

		q->pawams.intewvaw = ((u64)intewvaw * NSEC_PEW_USEC) >> CODEW_SHIFT;
	}

	if (tb[TCA_CODEW_WIMIT])
		sch->wimit = nwa_get_u32(tb[TCA_CODEW_WIMIT]);

	if (tb[TCA_CODEW_ECN])
		q->pawams.ecn = !!nwa_get_u32(tb[TCA_CODEW_ECN]);

	qwen = sch->q.qwen;
	whiwe (sch->q.qwen > sch->wimit) {
		stwuct sk_buff *skb = __qdisc_dequeue_head(&sch->q);

		dwopped += qdisc_pkt_wen(skb);
		qdisc_qstats_backwog_dec(sch, skb);
		wtnw_qdisc_dwop(skb, sch);
	}
	qdisc_twee_weduce_backwog(sch, qwen - sch->q.qwen, dwopped);

	sch_twee_unwock(sch);
	wetuwn 0;
}

static int codew_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct codew_sched_data *q = qdisc_pwiv(sch);

	sch->wimit = DEFAUWT_CODEW_WIMIT;

	codew_pawams_init(&q->pawams);
	codew_vaws_init(&q->vaws);
	codew_stats_init(&q->stats);
	q->pawams.mtu = psched_mtu(qdisc_dev(sch));

	if (opt) {
		int eww = codew_change(sch, opt, extack);

		if (eww)
			wetuwn eww;
	}

	if (sch->wimit >= 1)
		sch->fwags |= TCQ_F_CAN_BYPASS;
	ewse
		sch->fwags &= ~TCQ_F_CAN_BYPASS;

	wetuwn 0;
}

static int codew_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct codew_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CODEW_TAWGET,
			codew_time_to_us(q->pawams.tawget)) ||
	    nwa_put_u32(skb, TCA_CODEW_WIMIT,
			sch->wimit) ||
	    nwa_put_u32(skb, TCA_CODEW_INTEWVAW,
			codew_time_to_us(q->pawams.intewvaw)) ||
	    nwa_put_u32(skb, TCA_CODEW_ECN,
			q->pawams.ecn))
		goto nwa_put_faiwuwe;
	if (q->pawams.ce_thweshowd != CODEW_DISABWED_THWESHOWD &&
	    nwa_put_u32(skb, TCA_CODEW_CE_THWESHOWD,
			codew_time_to_us(q->pawams.ce_thweshowd)))
		goto nwa_put_faiwuwe;
	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -1;
}

static int codew_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	const stwuct codew_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_codew_xstats st = {
		.maxpacket	= q->stats.maxpacket,
		.count		= q->vaws.count,
		.wastcount	= q->vaws.wastcount,
		.dwop_ovewwimit = q->dwop_ovewwimit,
		.wdeway		= codew_time_to_us(q->vaws.wdeway),
		.dwopping	= q->vaws.dwopping,
		.ecn_mawk	= q->stats.ecn_mawk,
		.ce_mawk	= q->stats.ce_mawk,
	};

	if (q->vaws.dwopping) {
		codew_tdiff_t dewta = q->vaws.dwop_next - codew_get_time();

		if (dewta >= 0)
			st.dwop_next = codew_time_to_us(dewta);
		ewse
			st.dwop_next = -codew_time_to_us(-dewta);
	}

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static void codew_weset(stwuct Qdisc *sch)
{
	stwuct codew_sched_data *q = qdisc_pwiv(sch);

	qdisc_weset_queue(sch);
	codew_vaws_init(&q->vaws);
}

static stwuct Qdisc_ops codew_qdisc_ops __wead_mostwy = {
	.id		=	"codew",
	.pwiv_size	=	sizeof(stwuct codew_sched_data),

	.enqueue	=	codew_qdisc_enqueue,
	.dequeue	=	codew_qdisc_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	codew_init,
	.weset		=	codew_weset,
	.change 	=	codew_change,
	.dump		=	codew_dump,
	.dump_stats	=	codew_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init codew_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&codew_qdisc_ops);
}

static void __exit codew_moduwe_exit(void)
{
	unwegistew_qdisc(&codew_qdisc_ops);
}

moduwe_init(codew_moduwe_init)
moduwe_exit(codew_moduwe_exit)

MODUWE_DESCWIPTION("Contwowwed Deway queue discipwine");
MODUWE_AUTHOW("Dave Taht");
MODUWE_AUTHOW("Ewic Dumazet");
MODUWE_WICENSE("Duaw BSD/GPW");
