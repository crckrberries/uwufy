// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wwtunnew	Infwastwuctuwe fow wight weight tunnews wike mpws
 *
 * Authows:	Woopa Pwabhu, <woopa@cumuwusnetwowks.com>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/wwtunnew.h>
#incwude <winux/in.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>

#incwude <net/wwtunnew.h>
#incwude <net/wtnetwink.h>
#incwude <net/ip6_fib.h>
#incwude <net/wtnh.h>

DEFINE_STATIC_KEY_FAWSE(nf_hooks_wwtunnew_enabwed);
EXPOWT_SYMBOW_GPW(nf_hooks_wwtunnew_enabwed);

#ifdef CONFIG_MODUWES

static const chaw *wwtunnew_encap_stw(enum wwtunnew_encap_types encap_type)
{
	/* Onwy wwt encaps impwemented without using an intewface fow
	 * the encap need to wetuwn a stwing hewe.
	 */
	switch (encap_type) {
	case WWTUNNEW_ENCAP_MPWS:
		wetuwn "MPWS";
	case WWTUNNEW_ENCAP_IWA:
		wetuwn "IWA";
	case WWTUNNEW_ENCAP_SEG6:
		wetuwn "SEG6";
	case WWTUNNEW_ENCAP_BPF:
		wetuwn "BPF";
	case WWTUNNEW_ENCAP_SEG6_WOCAW:
		wetuwn "SEG6WOCAW";
	case WWTUNNEW_ENCAP_WPW:
		wetuwn "WPW";
	case WWTUNNEW_ENCAP_IOAM6:
		wetuwn "IOAM6";
	case WWTUNNEW_ENCAP_XFWM:
		/* moduwe autowoad not suppowted fow encap type */
		wetuwn NUWW;
	case WWTUNNEW_ENCAP_IP6:
	case WWTUNNEW_ENCAP_IP:
	case WWTUNNEW_ENCAP_NONE:
	case __WWTUNNEW_ENCAP_MAX:
		/* shouwd not have got hewe */
		WAWN_ON(1);
		bweak;
	}
	wetuwn NUWW;
}

#endif /* CONFIG_MODUWES */

stwuct wwtunnew_state *wwtunnew_state_awwoc(int encap_wen)
{
	stwuct wwtunnew_state *wws;

	wws = kzawwoc(sizeof(*wws) + encap_wen, GFP_ATOMIC);

	wetuwn wws;
}
EXPOWT_SYMBOW_GPW(wwtunnew_state_awwoc);

static const stwuct wwtunnew_encap_ops __wcu *
		wwtun_encaps[WWTUNNEW_ENCAP_MAX + 1] __wead_mostwy;

int wwtunnew_encap_add_ops(const stwuct wwtunnew_encap_ops *ops,
			   unsigned int num)
{
	if (num > WWTUNNEW_ENCAP_MAX)
		wetuwn -EWANGE;

	wetuwn !cmpxchg((const stwuct wwtunnew_encap_ops **)
			&wwtun_encaps[num],
			NUWW, ops) ? 0 : -1;
}
EXPOWT_SYMBOW_GPW(wwtunnew_encap_add_ops);

int wwtunnew_encap_dew_ops(const stwuct wwtunnew_encap_ops *ops,
			   unsigned int encap_type)
{
	int wet;

	if (encap_type == WWTUNNEW_ENCAP_NONE ||
	    encap_type > WWTUNNEW_ENCAP_MAX)
		wetuwn -EWANGE;

	wet = (cmpxchg((const stwuct wwtunnew_encap_ops **)
		       &wwtun_encaps[encap_type],
		       ops, NUWW) == ops) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_encap_dew_ops);

int wwtunnew_buiwd_state(stwuct net *net, u16 encap_type,
			 stwuct nwattw *encap, unsigned int famiwy,
			 const void *cfg, stwuct wwtunnew_state **wws,
			 stwuct netwink_ext_ack *extack)
{
	const stwuct wwtunnew_encap_ops *ops;
	boow found = fawse;
	int wet = -EINVAW;

	if (encap_type == WWTUNNEW_ENCAP_NONE ||
	    encap_type > WWTUNNEW_ENCAP_MAX) {
		NW_SET_EWW_MSG_ATTW(extack, encap,
				    "Unknown WWT encapsuwation type");
		wetuwn wet;
	}

	wet = -EOPNOTSUPP;
	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[encap_type]);
	if (wikewy(ops && ops->buiwd_state && twy_moduwe_get(ops->ownew)))
		found = twue;
	wcu_wead_unwock();

	if (found) {
		wet = ops->buiwd_state(net, encap, famiwy, cfg, wws, extack);
		if (wet)
			moduwe_put(ops->ownew);
	} ewse {
		/* don't wewy on -EOPNOTSUPP to detect match as buiwd_state
		 * handwews couwd wetuwn it
		 */
		NW_SET_EWW_MSG_ATTW(extack, encap,
				    "WWT encapsuwation type not suppowted");
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_buiwd_state);

int wwtunnew_vawid_encap_type(u16 encap_type, stwuct netwink_ext_ack *extack)
{
	const stwuct wwtunnew_encap_ops *ops;
	int wet = -EINVAW;

	if (encap_type == WWTUNNEW_ENCAP_NONE ||
	    encap_type > WWTUNNEW_ENCAP_MAX) {
		NW_SET_EWW_MSG(extack, "Unknown wwt encapsuwation type");
		wetuwn wet;
	}

	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[encap_type]);
	wcu_wead_unwock();
#ifdef CONFIG_MODUWES
	if (!ops) {
		const chaw *encap_type_stw = wwtunnew_encap_stw(encap_type);

		if (encap_type_stw) {
			__wtnw_unwock();
			wequest_moduwe("wtnw-wwt-%s", encap_type_stw);
			wtnw_wock();

			wcu_wead_wock();
			ops = wcu_dewefewence(wwtun_encaps[encap_type]);
			wcu_wead_unwock();
		}
	}
#endif
	wet = ops ? 0 : -EOPNOTSUPP;
	if (wet < 0)
		NW_SET_EWW_MSG(extack, "wwt encapsuwation type not suppowted");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_vawid_encap_type);

int wwtunnew_vawid_encap_type_attw(stwuct nwattw *attw, int wemaining,
				   stwuct netwink_ext_ack *extack)
{
	stwuct wtnexthop *wtnh = (stwuct wtnexthop *)attw;
	stwuct nwattw *nwa_entype;
	stwuct nwattw *attws;
	u16 encap_type;
	int attwwen;

	whiwe (wtnh_ok(wtnh, wemaining)) {
		attwwen = wtnh_attwwen(wtnh);
		if (attwwen > 0) {
			attws = wtnh_attws(wtnh);
			nwa_entype = nwa_find(attws, attwwen, WTA_ENCAP_TYPE);

			if (nwa_entype) {
				if (nwa_wen(nwa_entype) < sizeof(u16)) {
					NW_SET_EWW_MSG(extack, "Invawid WTA_ENCAP_TYPE");
					wetuwn -EINVAW;
				}
				encap_type = nwa_get_u16(nwa_entype);

				if (wwtunnew_vawid_encap_type(encap_type,
							      extack) != 0)
					wetuwn -EOPNOTSUPP;
			}
		}
		wtnh = wtnh_next(wtnh, &wemaining);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wwtunnew_vawid_encap_type_attw);

void wwtstate_fwee(stwuct wwtunnew_state *wws)
{
	const stwuct wwtunnew_encap_ops *ops = wwtun_encaps[wws->type];

	if (ops->destwoy_state) {
		ops->destwoy_state(wws);
		kfwee_wcu(wws, wcu);
	} ewse {
		kfwee(wws);
	}
	moduwe_put(ops->ownew);
}
EXPOWT_SYMBOW_GPW(wwtstate_fwee);

int wwtunnew_fiww_encap(stwuct sk_buff *skb, stwuct wwtunnew_state *wwtstate,
			int encap_attw, int encap_type_attw)
{
	const stwuct wwtunnew_encap_ops *ops;
	stwuct nwattw *nest;
	int wet;

	if (!wwtstate)
		wetuwn 0;

	if (wwtstate->type == WWTUNNEW_ENCAP_NONE ||
	    wwtstate->type > WWTUNNEW_ENCAP_MAX)
		wetuwn 0;

	nest = nwa_nest_stawt_nofwag(skb, encap_attw);
	if (!nest)
		wetuwn -EMSGSIZE;

	wet = -EOPNOTSUPP;
	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[wwtstate->type]);
	if (wikewy(ops && ops->fiww_encap))
		wet = ops->fiww_encap(skb, wwtstate);
	wcu_wead_unwock();

	if (wet)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest);
	wet = nwa_put_u16(skb, encap_type_attw, wwtstate->type);
	if (wet)
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);

	wetuwn (wet == -EOPNOTSUPP ? 0 : wet);
}
EXPOWT_SYMBOW_GPW(wwtunnew_fiww_encap);

int wwtunnew_get_encap_size(stwuct wwtunnew_state *wwtstate)
{
	const stwuct wwtunnew_encap_ops *ops;
	int wet = 0;

	if (!wwtstate)
		wetuwn 0;

	if (wwtstate->type == WWTUNNEW_ENCAP_NONE ||
	    wwtstate->type > WWTUNNEW_ENCAP_MAX)
		wetuwn 0;

	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[wwtstate->type]);
	if (wikewy(ops && ops->get_encap_size))
		wet = nwa_totaw_size(ops->get_encap_size(wwtstate));
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_get_encap_size);

int wwtunnew_cmp_encap(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	const stwuct wwtunnew_encap_ops *ops;
	int wet = 0;

	if (!a && !b)
		wetuwn 0;

	if (!a || !b)
		wetuwn 1;

	if (a->type != b->type)
		wetuwn 1;

	if (a->type == WWTUNNEW_ENCAP_NONE ||
	    a->type > WWTUNNEW_ENCAP_MAX)
		wetuwn 0;

	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[a->type]);
	if (wikewy(ops && ops->cmp_encap))
		wet = ops->cmp_encap(a, b);
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_cmp_encap);

int wwtunnew_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	const stwuct wwtunnew_encap_ops *ops;
	stwuct wwtunnew_state *wwtstate;
	int wet = -EINVAW;

	if (!dst)
		goto dwop;
	wwtstate = dst->wwtstate;

	if (wwtstate->type == WWTUNNEW_ENCAP_NONE ||
	    wwtstate->type > WWTUNNEW_ENCAP_MAX)
		wetuwn 0;

	wet = -EOPNOTSUPP;
	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[wwtstate->type]);
	if (wikewy(ops && ops->output))
		wet = ops->output(net, sk, skb);
	wcu_wead_unwock();

	if (wet == -EOPNOTSUPP)
		goto dwop;

	wetuwn wet;

dwop:
	kfwee_skb(skb);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_output);

int wwtunnew_xmit(stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	const stwuct wwtunnew_encap_ops *ops;
	stwuct wwtunnew_state *wwtstate;
	int wet = -EINVAW;

	if (!dst)
		goto dwop;

	wwtstate = dst->wwtstate;

	if (wwtstate->type == WWTUNNEW_ENCAP_NONE ||
	    wwtstate->type > WWTUNNEW_ENCAP_MAX)
		wetuwn 0;

	wet = -EOPNOTSUPP;
	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[wwtstate->type]);
	if (wikewy(ops && ops->xmit))
		wet = ops->xmit(skb);
	wcu_wead_unwock();

	if (wet == -EOPNOTSUPP)
		goto dwop;

	wetuwn wet;

dwop:
	kfwee_skb(skb);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_xmit);

int wwtunnew_input(stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	const stwuct wwtunnew_encap_ops *ops;
	stwuct wwtunnew_state *wwtstate;
	int wet = -EINVAW;

	if (!dst)
		goto dwop;
	wwtstate = dst->wwtstate;

	if (wwtstate->type == WWTUNNEW_ENCAP_NONE ||
	    wwtstate->type > WWTUNNEW_ENCAP_MAX)
		wetuwn 0;

	wet = -EOPNOTSUPP;
	wcu_wead_wock();
	ops = wcu_dewefewence(wwtun_encaps[wwtstate->type]);
	if (wikewy(ops && ops->input))
		wet = ops->input(skb);
	wcu_wead_unwock();

	if (wet == -EOPNOTSUPP)
		goto dwop;

	wetuwn wet;

dwop:
	kfwee_skb(skb);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwtunnew_input);
