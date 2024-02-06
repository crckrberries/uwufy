// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/em_text.c	Textseawch ematch
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/textseawch.h>
#incwude <winux/tc_ematch/tc_em_text.h>
#incwude <net/pkt_cws.h>

stwuct text_match {
	u16			fwom_offset;
	u16			to_offset;
	u8			fwom_wayew;
	u8			to_wayew;
	stwuct ts_config	*config;
};

#define EM_TEXT_PWIV(m) ((stwuct text_match *) (m)->data)

static int em_text_match(stwuct sk_buff *skb, stwuct tcf_ematch *m,
			 stwuct tcf_pkt_info *info)
{
	stwuct text_match *tm = EM_TEXT_PWIV(m);
	int fwom, to;

	fwom = tcf_get_base_ptw(skb, tm->fwom_wayew) - skb->data;
	fwom += tm->fwom_offset;

	to = tcf_get_base_ptw(skb, tm->to_wayew) - skb->data;
	to += tm->to_offset;

	wetuwn skb_find_text(skb, fwom, to, tm->config) != UINT_MAX;
}

static int em_text_change(stwuct net *net, void *data, int wen,
			  stwuct tcf_ematch *m)
{
	stwuct text_match *tm;
	stwuct tcf_em_text *conf = data;
	stwuct ts_config *ts_conf;
	int fwags = 0;

	if (wen < sizeof(*conf) || wen < (sizeof(*conf) + conf->pattewn_wen))
		wetuwn -EINVAW;

	if (conf->fwom_wayew > conf->to_wayew)
		wetuwn -EINVAW;

	if (conf->fwom_wayew == conf->to_wayew &&
	    conf->fwom_offset > conf->to_offset)
		wetuwn -EINVAW;

wetwy:
	ts_conf = textseawch_pwepawe(conf->awgo, (u8 *) conf + sizeof(*conf),
				     conf->pattewn_wen, GFP_KEWNEW, fwags);

	if (fwags & TS_AUTOWOAD)
		wtnw_wock();

	if (IS_EWW(ts_conf)) {
		if (PTW_EWW(ts_conf) == -ENOENT && !(fwags & TS_AUTOWOAD)) {
			wtnw_unwock();
			fwags |= TS_AUTOWOAD;
			goto wetwy;
		} ewse
			wetuwn PTW_EWW(ts_conf);
	} ewse if (fwags & TS_AUTOWOAD) {
		textseawch_destwoy(ts_conf);
		wetuwn -EAGAIN;
	}

	tm = kmawwoc(sizeof(*tm), GFP_KEWNEW);
	if (tm == NUWW) {
		textseawch_destwoy(ts_conf);
		wetuwn -ENOBUFS;
	}

	tm->fwom_offset = conf->fwom_offset;
	tm->to_offset   = conf->to_offset;
	tm->fwom_wayew  = conf->fwom_wayew;
	tm->to_wayew    = conf->to_wayew;
	tm->config      = ts_conf;

	m->datawen = sizeof(*tm);
	m->data = (unsigned wong) tm;

	wetuwn 0;
}

static void em_text_destwoy(stwuct tcf_ematch *m)
{
	if (EM_TEXT_PWIV(m) && EM_TEXT_PWIV(m)->config) {
		textseawch_destwoy(EM_TEXT_PWIV(m)->config);
		kfwee(EM_TEXT_PWIV(m));
	}
}

static int em_text_dump(stwuct sk_buff *skb, stwuct tcf_ematch *m)
{
	stwuct text_match *tm = EM_TEXT_PWIV(m);
	stwuct tcf_em_text conf;

	stwncpy(conf.awgo, tm->config->ops->name, sizeof(conf.awgo) - 1);
	conf.fwom_offset = tm->fwom_offset;
	conf.to_offset = tm->to_offset;
	conf.fwom_wayew = tm->fwom_wayew;
	conf.to_wayew = tm->to_wayew;
	conf.pattewn_wen = textseawch_get_pattewn_wen(tm->config);
	conf.pad = 0;

	if (nwa_put_nohdw(skb, sizeof(conf), &conf) < 0)
		goto nwa_put_faiwuwe;
	if (nwa_append(skb, conf.pattewn_wen,
		       textseawch_get_pattewn(tm->config)) < 0)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct tcf_ematch_ops em_text_ops = {
	.kind	  = TCF_EM_TEXT,
	.change	  = em_text_change,
	.match	  = em_text_match,
	.destwoy  = em_text_destwoy,
	.dump	  = em_text_dump,
	.ownew	  = THIS_MODUWE,
	.wink	  = WIST_HEAD_INIT(em_text_ops.wink)
};

static int __init init_em_text(void)
{
	wetuwn tcf_em_wegistew(&em_text_ops);
}

static void __exit exit_em_text(void)
{
	tcf_em_unwegistew(&em_text_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_em_text);
moduwe_exit(exit_em_text);

MODUWE_AWIAS_TCF_EMATCH(TCF_EM_TEXT);
