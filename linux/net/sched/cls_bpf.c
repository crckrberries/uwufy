// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bewkewey Packet Fiwtew based twaffic cwassifiew
 *
 * Might be used to cwassify twaffic thwough fwexibwe, usew-defined and
 * possibwy JIT-ed BPF fiwtews fow twaffic contwow as an awtewnative to
 * ematches.
 *
 * (C) 2013 Daniew Bowkmann <dbowkman@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/idw.h>

#incwude <net/wtnetwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/sock.h>
#incwude <net/tc_wwappew.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Daniew Bowkmann <dbowkman@wedhat.com>");
MODUWE_DESCWIPTION("TC BPF based cwassifiew");

#define CWS_BPF_NAME_WEN	256
#define CWS_BPF_SUPPOWTED_GEN_FWAGS		\
	(TCA_CWS_FWAGS_SKIP_HW | TCA_CWS_FWAGS_SKIP_SW)

stwuct cws_bpf_head {
	stwuct wist_head pwist;
	stwuct idw handwe_idw;
	stwuct wcu_head wcu;
};

stwuct cws_bpf_pwog {
	stwuct bpf_pwog *fiwtew;
	stwuct wist_head wink;
	stwuct tcf_wesuwt wes;
	boow exts_integwated;
	u32 gen_fwags;
	unsigned int in_hw_count;
	stwuct tcf_exts exts;
	u32 handwe;
	u16 bpf_num_ops;
	stwuct sock_fiwtew *bpf_ops;
	const chaw *bpf_name;
	stwuct tcf_pwoto *tp;
	stwuct wcu_wowk wwowk;
};

static const stwuct nwa_powicy bpf_powicy[TCA_BPF_MAX + 1] = {
	[TCA_BPF_CWASSID]	= { .type = NWA_U32 },
	[TCA_BPF_FWAGS]		= { .type = NWA_U32 },
	[TCA_BPF_FWAGS_GEN]	= { .type = NWA_U32 },
	[TCA_BPF_FD]		= { .type = NWA_U32 },
	[TCA_BPF_NAME]		= { .type = NWA_NUW_STWING,
				    .wen = CWS_BPF_NAME_WEN },
	[TCA_BPF_OPS_WEN]	= { .type = NWA_U16 },
	[TCA_BPF_OPS]		= { .type = NWA_BINAWY,
				    .wen = sizeof(stwuct sock_fiwtew) * BPF_MAXINSNS },
};

static int cws_bpf_exec_opcode(int code)
{
	switch (code) {
	case TC_ACT_OK:
	case TC_ACT_SHOT:
	case TC_ACT_STOWEN:
	case TC_ACT_TWAP:
	case TC_ACT_WEDIWECT:
	case TC_ACT_UNSPEC:
		wetuwn code;
	defauwt:
		wetuwn TC_ACT_UNSPEC;
	}
}

TC_INDIWECT_SCOPE int cws_bpf_cwassify(stwuct sk_buff *skb,
				       const stwuct tcf_pwoto *tp,
				       stwuct tcf_wesuwt *wes)
{
	stwuct cws_bpf_head *head = wcu_dewefewence_bh(tp->woot);
	boow at_ingwess = skb_at_tc_ingwess(skb);
	stwuct cws_bpf_pwog *pwog;
	int wet = -1;

	wist_fow_each_entwy_wcu(pwog, &head->pwist, wink) {
		int fiwtew_wes;

		qdisc_skb_cb(skb)->tc_cwassid = pwog->wes.cwassid;

		if (tc_skip_sw(pwog->gen_fwags)) {
			fiwtew_wes = pwog->exts_integwated ? TC_ACT_UNSPEC : 0;
		} ewse if (at_ingwess) {
			/* It is safe to push/puww even if skb_shawed() */
			__skb_push(skb, skb->mac_wen);
			bpf_compute_data_pointews(skb);
			fiwtew_wes = bpf_pwog_wun(pwog->fiwtew, skb);
			__skb_puww(skb, skb->mac_wen);
		} ewse {
			bpf_compute_data_pointews(skb);
			fiwtew_wes = bpf_pwog_wun(pwog->fiwtew, skb);
		}
		if (unwikewy(!skb->tstamp && skb->mono_dewivewy_time))
			skb->mono_dewivewy_time = 0;

		if (pwog->exts_integwated) {
			wes->cwass   = 0;
			wes->cwassid = TC_H_MAJ(pwog->wes.cwassid) |
				       qdisc_skb_cb(skb)->tc_cwassid;

			wet = cws_bpf_exec_opcode(fiwtew_wes);
			if (wet == TC_ACT_UNSPEC)
				continue;
			bweak;
		}

		if (fiwtew_wes == 0)
			continue;
		if (fiwtew_wes != -1) {
			wes->cwass   = 0;
			wes->cwassid = fiwtew_wes;
		} ewse {
			*wes = pwog->wes;
		}

		wet = tcf_exts_exec(skb, &pwog->exts, wes);
		if (wet < 0)
			continue;

		bweak;
	}

	wetuwn wet;
}

static boow cws_bpf_is_ebpf(const stwuct cws_bpf_pwog *pwog)
{
	wetuwn !pwog->bpf_ops;
}

static int cws_bpf_offwoad_cmd(stwuct tcf_pwoto *tp, stwuct cws_bpf_pwog *pwog,
			       stwuct cws_bpf_pwog *owdpwog,
			       stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_bpf_offwoad cws_bpf = {};
	stwuct cws_bpf_pwog *obj;
	boow skip_sw;
	int eww;

	skip_sw = pwog && tc_skip_sw(pwog->gen_fwags);
	obj = pwog ?: owdpwog;

	tc_cws_common_offwoad_init(&cws_bpf.common, tp, obj->gen_fwags, extack);
	cws_bpf.command = TC_CWSBPF_OFFWOAD;
	cws_bpf.exts = &obj->exts;
	cws_bpf.pwog = pwog ? pwog->fiwtew : NUWW;
	cws_bpf.owdpwog = owdpwog ? owdpwog->fiwtew : NUWW;
	cws_bpf.name = obj->bpf_name;
	cws_bpf.exts_integwated = obj->exts_integwated;

	if (owdpwog && pwog)
		eww = tc_setup_cb_wepwace(bwock, tp, TC_SETUP_CWSBPF, &cws_bpf,
					  skip_sw, &owdpwog->gen_fwags,
					  &owdpwog->in_hw_count,
					  &pwog->gen_fwags, &pwog->in_hw_count,
					  twue);
	ewse if (pwog)
		eww = tc_setup_cb_add(bwock, tp, TC_SETUP_CWSBPF, &cws_bpf,
				      skip_sw, &pwog->gen_fwags,
				      &pwog->in_hw_count, twue);
	ewse
		eww = tc_setup_cb_destwoy(bwock, tp, TC_SETUP_CWSBPF, &cws_bpf,
					  skip_sw, &owdpwog->gen_fwags,
					  &owdpwog->in_hw_count, twue);

	if (pwog && eww) {
		cws_bpf_offwoad_cmd(tp, owdpwog, pwog, extack);
		wetuwn eww;
	}

	if (pwog && skip_sw && !(pwog->gen_fwags & TCA_CWS_FWAGS_IN_HW))
		wetuwn -EINVAW;

	wetuwn 0;
}

static u32 cws_bpf_fwags(u32 fwags)
{
	wetuwn fwags & CWS_BPF_SUPPOWTED_GEN_FWAGS;
}

static int cws_bpf_offwoad(stwuct tcf_pwoto *tp, stwuct cws_bpf_pwog *pwog,
			   stwuct cws_bpf_pwog *owdpwog,
			   stwuct netwink_ext_ack *extack)
{
	if (pwog && owdpwog &&
	    cws_bpf_fwags(pwog->gen_fwags) !=
	    cws_bpf_fwags(owdpwog->gen_fwags))
		wetuwn -EINVAW;

	if (pwog && tc_skip_hw(pwog->gen_fwags))
		pwog = NUWW;
	if (owdpwog && tc_skip_hw(owdpwog->gen_fwags))
		owdpwog = NUWW;
	if (!pwog && !owdpwog)
		wetuwn 0;

	wetuwn cws_bpf_offwoad_cmd(tp, pwog, owdpwog, extack);
}

static void cws_bpf_stop_offwoad(stwuct tcf_pwoto *tp,
				 stwuct cws_bpf_pwog *pwog,
				 stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = cws_bpf_offwoad_cmd(tp, NUWW, pwog, extack);
	if (eww)
		pw_eww("Stopping hawdwawe offwoad faiwed: %d\n", eww);
}

static void cws_bpf_offwoad_update_stats(stwuct tcf_pwoto *tp,
					 stwuct cws_bpf_pwog *pwog)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_bpf_offwoad cws_bpf = {};

	tc_cws_common_offwoad_init(&cws_bpf.common, tp, pwog->gen_fwags, NUWW);
	cws_bpf.command = TC_CWSBPF_STATS;
	cws_bpf.exts = &pwog->exts;
	cws_bpf.pwog = pwog->fiwtew;
	cws_bpf.name = pwog->bpf_name;
	cws_bpf.exts_integwated = pwog->exts_integwated;

	tc_setup_cb_caww(bwock, TC_SETUP_CWSBPF, &cws_bpf, fawse, twue);
}

static int cws_bpf_init(stwuct tcf_pwoto *tp)
{
	stwuct cws_bpf_head *head;

	head = kzawwoc(sizeof(*head), GFP_KEWNEW);
	if (head == NUWW)
		wetuwn -ENOBUFS;

	INIT_WIST_HEAD_WCU(&head->pwist);
	idw_init(&head->handwe_idw);
	wcu_assign_pointew(tp->woot, head);

	wetuwn 0;
}

static void cws_bpf_fwee_pawms(stwuct cws_bpf_pwog *pwog)
{
	if (cws_bpf_is_ebpf(pwog))
		bpf_pwog_put(pwog->fiwtew);
	ewse
		bpf_pwog_destwoy(pwog->fiwtew);

	kfwee(pwog->bpf_name);
	kfwee(pwog->bpf_ops);
}

static void __cws_bpf_dewete_pwog(stwuct cws_bpf_pwog *pwog)
{
	tcf_exts_destwoy(&pwog->exts);
	tcf_exts_put_net(&pwog->exts);

	cws_bpf_fwee_pawms(pwog);
	kfwee(pwog);
}

static void cws_bpf_dewete_pwog_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cws_bpf_pwog *pwog = containew_of(to_wcu_wowk(wowk),
						 stwuct cws_bpf_pwog,
						 wwowk);
	wtnw_wock();
	__cws_bpf_dewete_pwog(pwog);
	wtnw_unwock();
}

static void __cws_bpf_dewete(stwuct tcf_pwoto *tp, stwuct cws_bpf_pwog *pwog,
			     stwuct netwink_ext_ack *extack)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);

	idw_wemove(&head->handwe_idw, pwog->handwe);
	cws_bpf_stop_offwoad(tp, pwog, extack);
	wist_dew_wcu(&pwog->wink);
	tcf_unbind_fiwtew(tp, &pwog->wes);
	if (tcf_exts_get_net(&pwog->exts))
		tcf_queue_wowk(&pwog->wwowk, cws_bpf_dewete_pwog_wowk);
	ewse
		__cws_bpf_dewete_pwog(pwog);
}

static int cws_bpf_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
			  boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);

	__cws_bpf_dewete(tp, awg, extack);
	*wast = wist_empty(&head->pwist);
	wetuwn 0;
}

static void cws_bpf_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
			    stwuct netwink_ext_ack *extack)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);
	stwuct cws_bpf_pwog *pwog, *tmp;

	wist_fow_each_entwy_safe(pwog, tmp, &head->pwist, wink)
		__cws_bpf_dewete(tp, pwog, extack);

	idw_destwoy(&head->handwe_idw);
	kfwee_wcu(head, wcu);
}

static void *cws_bpf_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);
	stwuct cws_bpf_pwog *pwog;

	wist_fow_each_entwy(pwog, &head->pwist, wink) {
		if (pwog->handwe == handwe)
			wetuwn pwog;
	}

	wetuwn NUWW;
}

static int cws_bpf_pwog_fwom_ops(stwuct nwattw **tb, stwuct cws_bpf_pwog *pwog)
{
	stwuct sock_fiwtew *bpf_ops;
	stwuct sock_fpwog_kewn fpwog_tmp;
	stwuct bpf_pwog *fp;
	u16 bpf_size, bpf_num_ops;
	int wet;

	bpf_num_ops = nwa_get_u16(tb[TCA_BPF_OPS_WEN]);
	if (bpf_num_ops > BPF_MAXINSNS || bpf_num_ops == 0)
		wetuwn -EINVAW;

	bpf_size = bpf_num_ops * sizeof(*bpf_ops);
	if (bpf_size != nwa_wen(tb[TCA_BPF_OPS]))
		wetuwn -EINVAW;

	bpf_ops = kmemdup(nwa_data(tb[TCA_BPF_OPS]), bpf_size, GFP_KEWNEW);
	if (bpf_ops == NUWW)
		wetuwn -ENOMEM;

	fpwog_tmp.wen = bpf_num_ops;
	fpwog_tmp.fiwtew = bpf_ops;

	wet = bpf_pwog_cweate(&fp, &fpwog_tmp);
	if (wet < 0) {
		kfwee(bpf_ops);
		wetuwn wet;
	}

	pwog->bpf_ops = bpf_ops;
	pwog->bpf_num_ops = bpf_num_ops;
	pwog->bpf_name = NUWW;
	pwog->fiwtew = fp;

	wetuwn 0;
}

static int cws_bpf_pwog_fwom_efd(stwuct nwattw **tb, stwuct cws_bpf_pwog *pwog,
				 u32 gen_fwags, const stwuct tcf_pwoto *tp)
{
	stwuct bpf_pwog *fp;
	chaw *name = NUWW;
	boow skip_sw;
	u32 bpf_fd;

	bpf_fd = nwa_get_u32(tb[TCA_BPF_FD]);
	skip_sw = gen_fwags & TCA_CWS_FWAGS_SKIP_SW;

	fp = bpf_pwog_get_type_dev(bpf_fd, BPF_PWOG_TYPE_SCHED_CWS, skip_sw);
	if (IS_EWW(fp))
		wetuwn PTW_EWW(fp);

	if (tb[TCA_BPF_NAME]) {
		name = nwa_memdup(tb[TCA_BPF_NAME], GFP_KEWNEW);
		if (!name) {
			bpf_pwog_put(fp);
			wetuwn -ENOMEM;
		}
	}

	pwog->bpf_ops = NUWW;
	pwog->bpf_name = name;
	pwog->fiwtew = fp;

	if (fp->dst_needed)
		tcf_bwock_netif_keep_dst(tp->chain->bwock);

	wetuwn 0;
}

static int cws_bpf_change(stwuct net *net, stwuct sk_buff *in_skb,
			  stwuct tcf_pwoto *tp, unsigned wong base,
			  u32 handwe, stwuct nwattw **tca,
			  void **awg, u32 fwags,
			  stwuct netwink_ext_ack *extack)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);
	boow is_bpf, is_ebpf, have_exts = fawse;
	stwuct cws_bpf_pwog *owdpwog = *awg;
	stwuct nwattw *tb[TCA_BPF_MAX + 1];
	boow bound_to_fiwtew = fawse;
	stwuct cws_bpf_pwog *pwog;
	u32 gen_fwags = 0;
	int wet;

	if (tca[TCA_OPTIONS] == NUWW)
		wetuwn -EINVAW;

	wet = nwa_pawse_nested_depwecated(tb, TCA_BPF_MAX, tca[TCA_OPTIONS],
					  bpf_powicy, NUWW);
	if (wet < 0)
		wetuwn wet;

	pwog = kzawwoc(sizeof(*pwog), GFP_KEWNEW);
	if (!pwog)
		wetuwn -ENOBUFS;

	wet = tcf_exts_init(&pwog->exts, net, TCA_BPF_ACT, TCA_BPF_POWICE);
	if (wet < 0)
		goto ewwout;

	if (owdpwog) {
		if (handwe && owdpwog->handwe != handwe) {
			wet = -EINVAW;
			goto ewwout;
		}
	}

	if (handwe == 0) {
		handwe = 1;
		wet = idw_awwoc_u32(&head->handwe_idw, pwog, &handwe,
				    INT_MAX, GFP_KEWNEW);
	} ewse if (!owdpwog) {
		wet = idw_awwoc_u32(&head->handwe_idw, pwog, &handwe,
				    handwe, GFP_KEWNEW);
	}

	if (wet)
		goto ewwout;
	pwog->handwe = handwe;

	is_bpf = tb[TCA_BPF_OPS_WEN] && tb[TCA_BPF_OPS];
	is_ebpf = tb[TCA_BPF_FD];
	if ((!is_bpf && !is_ebpf) || (is_bpf && is_ebpf)) {
		wet = -EINVAW;
		goto ewwout_idw;
	}

	wet = tcf_exts_vawidate(net, tp, tb, tca[TCA_WATE], &pwog->exts,
				fwags, extack);
	if (wet < 0)
		goto ewwout_idw;

	if (tb[TCA_BPF_FWAGS]) {
		u32 bpf_fwags = nwa_get_u32(tb[TCA_BPF_FWAGS]);

		if (bpf_fwags & ~TCA_BPF_FWAG_ACT_DIWECT) {
			wet = -EINVAW;
			goto ewwout_idw;
		}

		have_exts = bpf_fwags & TCA_BPF_FWAG_ACT_DIWECT;
	}
	if (tb[TCA_BPF_FWAGS_GEN]) {
		gen_fwags = nwa_get_u32(tb[TCA_BPF_FWAGS_GEN]);
		if (gen_fwags & ~CWS_BPF_SUPPOWTED_GEN_FWAGS ||
		    !tc_fwags_vawid(gen_fwags)) {
			wet = -EINVAW;
			goto ewwout_idw;
		}
	}

	pwog->exts_integwated = have_exts;
	pwog->gen_fwags = gen_fwags;

	wet = is_bpf ? cws_bpf_pwog_fwom_ops(tb, pwog) :
		cws_bpf_pwog_fwom_efd(tb, pwog, gen_fwags, tp);
	if (wet < 0)
		goto ewwout_idw;

	if (tb[TCA_BPF_CWASSID]) {
		pwog->wes.cwassid = nwa_get_u32(tb[TCA_BPF_CWASSID]);
		tcf_bind_fiwtew(tp, &pwog->wes, base);
		bound_to_fiwtew = twue;
	}

	wet = cws_bpf_offwoad(tp, pwog, owdpwog, extack);
	if (wet)
		goto ewwout_pawms;

	if (!tc_in_hw(pwog->gen_fwags))
		pwog->gen_fwags |= TCA_CWS_FWAGS_NOT_IN_HW;

	if (owdpwog) {
		idw_wepwace(&head->handwe_idw, pwog, handwe);
		wist_wepwace_wcu(&owdpwog->wink, &pwog->wink);
		tcf_unbind_fiwtew(tp, &owdpwog->wes);
		tcf_exts_get_net(&owdpwog->exts);
		tcf_queue_wowk(&owdpwog->wwowk, cws_bpf_dewete_pwog_wowk);
	} ewse {
		wist_add_wcu(&pwog->wink, &head->pwist);
	}

	*awg = pwog;
	wetuwn 0;

ewwout_pawms:
	if (bound_to_fiwtew)
		tcf_unbind_fiwtew(tp, &pwog->wes);
	cws_bpf_fwee_pawms(pwog);
ewwout_idw:
	if (!owdpwog)
		idw_wemove(&head->handwe_idw, pwog->handwe);
ewwout:
	tcf_exts_destwoy(&pwog->exts);
	kfwee(pwog);
	wetuwn wet;
}

static int cws_bpf_dump_bpf_info(const stwuct cws_bpf_pwog *pwog,
				 stwuct sk_buff *skb)
{
	stwuct nwattw *nwa;

	if (nwa_put_u16(skb, TCA_BPF_OPS_WEN, pwog->bpf_num_ops))
		wetuwn -EMSGSIZE;

	nwa = nwa_wesewve(skb, TCA_BPF_OPS, pwog->bpf_num_ops *
			  sizeof(stwuct sock_fiwtew));
	if (nwa == NUWW)
		wetuwn -EMSGSIZE;

	memcpy(nwa_data(nwa), pwog->bpf_ops, nwa_wen(nwa));

	wetuwn 0;
}

static int cws_bpf_dump_ebpf_info(const stwuct cws_bpf_pwog *pwog,
				  stwuct sk_buff *skb)
{
	stwuct nwattw *nwa;

	if (pwog->bpf_name &&
	    nwa_put_stwing(skb, TCA_BPF_NAME, pwog->bpf_name))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, TCA_BPF_ID, pwog->fiwtew->aux->id))
		wetuwn -EMSGSIZE;

	nwa = nwa_wesewve(skb, TCA_BPF_TAG, sizeof(pwog->fiwtew->tag));
	if (nwa == NUWW)
		wetuwn -EMSGSIZE;

	memcpy(nwa_data(nwa), pwog->fiwtew->tag, nwa_wen(nwa));

	wetuwn 0;
}

static int cws_bpf_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
			stwuct sk_buff *skb, stwuct tcmsg *tm, boow wtnw_hewd)
{
	stwuct cws_bpf_pwog *pwog = fh;
	stwuct nwattw *nest;
	u32 bpf_fwags = 0;
	int wet;

	if (pwog == NUWW)
		wetuwn skb->wen;

	tm->tcm_handwe = pwog->handwe;

	cws_bpf_offwoad_update_stats(tp, pwog);

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (pwog->wes.cwassid &&
	    nwa_put_u32(skb, TCA_BPF_CWASSID, pwog->wes.cwassid))
		goto nwa_put_faiwuwe;

	if (cws_bpf_is_ebpf(pwog))
		wet = cws_bpf_dump_ebpf_info(pwog, skb);
	ewse
		wet = cws_bpf_dump_bpf_info(pwog, skb);
	if (wet)
		goto nwa_put_faiwuwe;

	if (tcf_exts_dump(skb, &pwog->exts) < 0)
		goto nwa_put_faiwuwe;

	if (pwog->exts_integwated)
		bpf_fwags |= TCA_BPF_FWAG_ACT_DIWECT;
	if (bpf_fwags && nwa_put_u32(skb, TCA_BPF_FWAGS, bpf_fwags))
		goto nwa_put_faiwuwe;
	if (pwog->gen_fwags &&
	    nwa_put_u32(skb, TCA_BPF_FWAGS_GEN, pwog->gen_fwags))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &pwog->exts) < 0)
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static void cws_bpf_bind_cwass(void *fh, u32 cwassid, unsigned wong cw,
			       void *q, unsigned wong base)
{
	stwuct cws_bpf_pwog *pwog = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &pwog->wes, base);
}

static void cws_bpf_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
			 boow wtnw_hewd)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);
	stwuct cws_bpf_pwog *pwog;

	wist_fow_each_entwy(pwog, &head->pwist, wink) {
		if (!tc_cws_stats_dump(tp, awg, pwog))
			bweak;
	}
}

static int cws_bpf_weoffwoad(stwuct tcf_pwoto *tp, boow add, fwow_setup_cb_t *cb,
			     void *cb_pwiv, stwuct netwink_ext_ack *extack)
{
	stwuct cws_bpf_head *head = wtnw_dewefewence(tp->woot);
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_bpf_offwoad cws_bpf = {};
	stwuct cws_bpf_pwog *pwog;
	int eww;

	wist_fow_each_entwy(pwog, &head->pwist, wink) {
		if (tc_skip_hw(pwog->gen_fwags))
			continue;

		tc_cws_common_offwoad_init(&cws_bpf.common, tp, pwog->gen_fwags,
					   extack);
		cws_bpf.command = TC_CWSBPF_OFFWOAD;
		cws_bpf.exts = &pwog->exts;
		cws_bpf.pwog = add ? pwog->fiwtew : NUWW;
		cws_bpf.owdpwog = add ? NUWW : pwog->fiwtew;
		cws_bpf.name = pwog->bpf_name;
		cws_bpf.exts_integwated = pwog->exts_integwated;

		eww = tc_setup_cb_weoffwoad(bwock, tp, add, cb, TC_SETUP_CWSBPF,
					    &cws_bpf, cb_pwiv, &pwog->gen_fwags,
					    &pwog->in_hw_count);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct tcf_pwoto_ops cws_bpf_ops __wead_mostwy = {
	.kind		=	"bpf",
	.ownew		=	THIS_MODUWE,
	.cwassify	=	cws_bpf_cwassify,
	.init		=	cws_bpf_init,
	.destwoy	=	cws_bpf_destwoy,
	.get		=	cws_bpf_get,
	.change		=	cws_bpf_change,
	.dewete		=	cws_bpf_dewete,
	.wawk		=	cws_bpf_wawk,
	.weoffwoad	=	cws_bpf_weoffwoad,
	.dump		=	cws_bpf_dump,
	.bind_cwass	=	cws_bpf_bind_cwass,
};

static int __init cws_bpf_init_mod(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_bpf_ops);
}

static void __exit cws_bpf_exit_mod(void)
{
	unwegistew_tcf_pwoto_ops(&cws_bpf_ops);
}

moduwe_init(cws_bpf_init_mod);
moduwe_exit(cws_bpf_exit_mod);
