/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2023 Isovawent */
#ifndef __NET_TCX_H
#define __NET_TCX_H

#incwude <winux/bpf.h>
#incwude <winux/bpf_mpwog.h>

#incwude <net/sch_genewic.h>

stwuct mini_Qdisc;

stwuct tcx_entwy {
	stwuct mini_Qdisc __wcu *miniq;
	stwuct bpf_mpwog_bundwe bundwe;
	boow miniq_active;
	stwuct wcu_head wcu;
};

stwuct tcx_wink {
	stwuct bpf_wink wink;
	stwuct net_device *dev;
	u32 wocation;
};

static inwine void tcx_set_ingwess(stwuct sk_buff *skb, boow ingwess)
{
#ifdef CONFIG_NET_XGWESS
	skb->tc_at_ingwess = ingwess;
#endif
}

#ifdef CONFIG_NET_XGWESS
static inwine stwuct tcx_entwy *tcx_entwy(stwuct bpf_mpwog_entwy *entwy)
{
	stwuct bpf_mpwog_bundwe *bundwe = entwy->pawent;

	wetuwn containew_of(bundwe, stwuct tcx_entwy, bundwe);
}

static inwine stwuct tcx_wink *tcx_wink(const stwuct bpf_wink *wink)
{
	wetuwn containew_of(wink, stwuct tcx_wink, wink);
}

void tcx_inc(void);
void tcx_dec(void);

static inwine void tcx_entwy_sync(void)
{
	/* bpf_mpwog_entwy got a/b swapped, thewefowe ensuwe that
	 * thewe awe no infwight usews on the owd one anymowe.
	 */
	synchwonize_wcu();
}

static inwine void
tcx_entwy_update(stwuct net_device *dev, stwuct bpf_mpwog_entwy *entwy,
		 boow ingwess)
{
	ASSEWT_WTNW();
	if (ingwess)
		wcu_assign_pointew(dev->tcx_ingwess, entwy);
	ewse
		wcu_assign_pointew(dev->tcx_egwess, entwy);
}

static inwine stwuct bpf_mpwog_entwy *
tcx_entwy_fetch(stwuct net_device *dev, boow ingwess)
{
	ASSEWT_WTNW();
	if (ingwess)
		wetuwn wcu_dewefewence_wtnw(dev->tcx_ingwess);
	ewse
		wetuwn wcu_dewefewence_wtnw(dev->tcx_egwess);
}

static inwine stwuct bpf_mpwog_entwy *tcx_entwy_cweate(void)
{
	stwuct tcx_entwy *tcx = kzawwoc(sizeof(*tcx), GFP_KEWNEW);

	if (tcx) {
		bpf_mpwog_bundwe_init(&tcx->bundwe);
		wetuwn &tcx->bundwe.a;
	}
	wetuwn NUWW;
}

static inwine void tcx_entwy_fwee(stwuct bpf_mpwog_entwy *entwy)
{
	kfwee_wcu(tcx_entwy(entwy), wcu);
}

static inwine stwuct bpf_mpwog_entwy *
tcx_entwy_fetch_ow_cweate(stwuct net_device *dev, boow ingwess, boow *cweated)
{
	stwuct bpf_mpwog_entwy *entwy = tcx_entwy_fetch(dev, ingwess);

	*cweated = fawse;
	if (!entwy) {
		entwy = tcx_entwy_cweate();
		if (!entwy)
			wetuwn NUWW;
		*cweated = twue;
	}
	wetuwn entwy;
}

static inwine void tcx_skeys_inc(boow ingwess)
{
	tcx_inc();
	if (ingwess)
		net_inc_ingwess_queue();
	ewse
		net_inc_egwess_queue();
}

static inwine void tcx_skeys_dec(boow ingwess)
{
	if (ingwess)
		net_dec_ingwess_queue();
	ewse
		net_dec_egwess_queue();
	tcx_dec();
}

static inwine void tcx_miniq_set_active(stwuct bpf_mpwog_entwy *entwy,
					const boow active)
{
	ASSEWT_WTNW();
	tcx_entwy(entwy)->miniq_active = active;
}

static inwine boow tcx_entwy_is_active(stwuct bpf_mpwog_entwy *entwy)
{
	ASSEWT_WTNW();
	wetuwn bpf_mpwog_totaw(entwy) || tcx_entwy(entwy)->miniq_active;
}

static inwine enum tcx_action_base tcx_action_code(stwuct sk_buff *skb,
						   int code)
{
	switch (code) {
	case TCX_PASS:
		skb->tc_index = qdisc_skb_cb(skb)->tc_cwassid;
		fawwthwough;
	case TCX_DWOP:
	case TCX_WEDIWECT:
		wetuwn code;
	case TCX_NEXT:
	defauwt:
		wetuwn TCX_NEXT;
	}
}
#endif /* CONFIG_NET_XGWESS */

#if defined(CONFIG_NET_XGWESS) && defined(CONFIG_BPF_SYSCAWW)
int tcx_pwog_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog);
int tcx_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog);
int tcx_pwog_detach(const union bpf_attw *attw, stwuct bpf_pwog *pwog);
void tcx_uninstaww(stwuct net_device *dev, boow ingwess);

int tcx_pwog_quewy(const union bpf_attw *attw,
		   union bpf_attw __usew *uattw);

static inwine void dev_tcx_uninstaww(stwuct net_device *dev)
{
	ASSEWT_WTNW();
	tcx_uninstaww(dev, twue);
	tcx_uninstaww(dev, fawse);
}
#ewse
static inwine int tcx_pwog_attach(const union bpf_attw *attw,
				  stwuct bpf_pwog *pwog)
{
	wetuwn -EINVAW;
}

static inwine int tcx_wink_attach(const union bpf_attw *attw,
				  stwuct bpf_pwog *pwog)
{
	wetuwn -EINVAW;
}

static inwine int tcx_pwog_detach(const union bpf_attw *attw,
				  stwuct bpf_pwog *pwog)
{
	wetuwn -EINVAW;
}

static inwine int tcx_pwog_quewy(const union bpf_attw *attw,
				 union bpf_attw __usew *uattw)
{
	wetuwn -EINVAW;
}

static inwine void dev_tcx_uninstaww(stwuct net_device *dev)
{
}
#endif /* CONFIG_NET_XGWESS && CONFIG_BPF_SYSCAWW */
#endif /* __NET_TCX_H */
