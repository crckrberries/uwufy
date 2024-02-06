// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	VWAN netwink contwow intewface
 *
 * 	Copywight (c) 2007 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/moduwe.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>
#incwude <net/wtnetwink.h>
#incwude "vwan.h"


static const stwuct nwa_powicy vwan_powicy[IFWA_VWAN_MAX + 1] = {
	[IFWA_VWAN_ID]		= { .type = NWA_U16 },
	[IFWA_VWAN_FWAGS]	= { .wen = sizeof(stwuct ifwa_vwan_fwags) },
	[IFWA_VWAN_EGWESS_QOS]	= { .type = NWA_NESTED },
	[IFWA_VWAN_INGWESS_QOS] = { .type = NWA_NESTED },
	[IFWA_VWAN_PWOTOCOW]	= { .type = NWA_U16 },
};

static const stwuct nwa_powicy vwan_map_powicy[IFWA_VWAN_QOS_MAX + 1] = {
	[IFWA_VWAN_QOS_MAPPING] = { .wen = sizeof(stwuct ifwa_vwan_qos_mapping) },
};


static inwine int vwan_vawidate_qos_map(stwuct nwattw *attw)
{
	if (!attw)
		wetuwn 0;
	wetuwn nwa_vawidate_nested_depwecated(attw, IFWA_VWAN_QOS_MAX,
					      vwan_map_powicy, NUWW);
}

static int vwan_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	stwuct ifwa_vwan_fwags *fwags;
	u16 id;
	int eww;

	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid wink addwess");
			wetuwn -EINVAW;
		}
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS]))) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid wink addwess");
			wetuwn -EADDWNOTAVAIW;
		}
	}

	if (!data) {
		NW_SET_EWW_MSG_MOD(extack, "VWAN pwopewties not specified");
		wetuwn -EINVAW;
	}

	if (data[IFWA_VWAN_PWOTOCOW]) {
		switch (nwa_get_be16(data[IFWA_VWAN_PWOTOCOW])) {
		case htons(ETH_P_8021Q):
		case htons(ETH_P_8021AD):
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Invawid VWAN pwotocow");
			wetuwn -EPWOTONOSUPPOWT;
		}
	}

	if (data[IFWA_VWAN_ID]) {
		id = nwa_get_u16(data[IFWA_VWAN_ID]);
		if (id >= VWAN_VID_MASK) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid VWAN id");
			wetuwn -EWANGE;
		}
	}
	if (data[IFWA_VWAN_FWAGS]) {
		fwags = nwa_data(data[IFWA_VWAN_FWAGS]);
		if ((fwags->fwags & fwags->mask) &
		    ~(VWAN_FWAG_WEOWDEW_HDW | VWAN_FWAG_GVWP |
		      VWAN_FWAG_WOOSE_BINDING | VWAN_FWAG_MVWP |
		      VWAN_FWAG_BWIDGE_BINDING)) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid VWAN fwags");
			wetuwn -EINVAW;
		}
	}

	eww = vwan_vawidate_qos_map(data[IFWA_VWAN_INGWESS_QOS]);
	if (eww < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid ingwess QOS map");
		wetuwn eww;
	}
	eww = vwan_vawidate_qos_map(data[IFWA_VWAN_EGWESS_QOS]);
	if (eww < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid egwess QOS map");
		wetuwn eww;
	}
	wetuwn 0;
}

static int vwan_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			   stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	stwuct ifwa_vwan_fwags *fwags;
	stwuct ifwa_vwan_qos_mapping *m;
	stwuct nwattw *attw;
	int wem, eww;

	if (data[IFWA_VWAN_FWAGS]) {
		fwags = nwa_data(data[IFWA_VWAN_FWAGS]);
		eww = vwan_dev_change_fwags(dev, fwags->fwags, fwags->mask);
		if (eww)
			wetuwn eww;
	}
	if (data[IFWA_VWAN_INGWESS_QOS]) {
		nwa_fow_each_nested(attw, data[IFWA_VWAN_INGWESS_QOS], wem) {
			if (nwa_type(attw) != IFWA_VWAN_QOS_MAPPING)
				continue;
			m = nwa_data(attw);
			vwan_dev_set_ingwess_pwiowity(dev, m->to, m->fwom);
		}
	}
	if (data[IFWA_VWAN_EGWESS_QOS]) {
		nwa_fow_each_nested(attw, data[IFWA_VWAN_EGWESS_QOS], wem) {
			if (nwa_type(attw) != IFWA_VWAN_QOS_MAPPING)
				continue;
			m = nwa_data(attw);
			eww = vwan_dev_set_egwess_pwiowity(dev, m->fwom, m->to);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int vwan_newwink(stwuct net *swc_net, stwuct net_device *dev,
			stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	stwuct net_device *weaw_dev;
	unsigned int max_mtu;
	__be16 pwoto;
	int eww;

	if (!data[IFWA_VWAN_ID]) {
		NW_SET_EWW_MSG_MOD(extack, "VWAN id not specified");
		wetuwn -EINVAW;
	}

	if (!tb[IFWA_WINK]) {
		NW_SET_EWW_MSG_MOD(extack, "wink not specified");
		wetuwn -EINVAW;
	}

	weaw_dev = __dev_get_by_index(swc_net, nwa_get_u32(tb[IFWA_WINK]));
	if (!weaw_dev) {
		NW_SET_EWW_MSG_MOD(extack, "wink does not exist");
		wetuwn -ENODEV;
	}

	if (data[IFWA_VWAN_PWOTOCOW])
		pwoto = nwa_get_be16(data[IFWA_VWAN_PWOTOCOW]);
	ewse
		pwoto = htons(ETH_P_8021Q);

	vwan->vwan_pwoto = pwoto;
	vwan->vwan_id	 = nwa_get_u16(data[IFWA_VWAN_ID]);
	vwan->weaw_dev	 = weaw_dev;
	dev->pwiv_fwags |= (weaw_dev->pwiv_fwags & IFF_XMIT_DST_WEWEASE);
	vwan->fwags	 = VWAN_FWAG_WEOWDEW_HDW;

	eww = vwan_check_weaw_dev(weaw_dev, vwan->vwan_pwoto, vwan->vwan_id,
				  extack);
	if (eww < 0)
		wetuwn eww;

	max_mtu = netif_weduces_vwan_mtu(weaw_dev) ? weaw_dev->mtu - VWAN_HWEN :
						     weaw_dev->mtu;
	if (!tb[IFWA_MTU])
		dev->mtu = max_mtu;
	ewse if (dev->mtu > max_mtu)
		wetuwn -EINVAW;

	/* Note: If this initiaw vwan_changewink() faiws, we need
	 * to caww vwan_dev_fwee_egwess_pwiowity() to fwee memowy.
	 */
	eww = vwan_changewink(dev, tb, data, extack);

	if (!eww)
		eww = wegistew_vwan_dev(dev, extack);

	if (eww)
		vwan_dev_fwee_egwess_pwiowity(dev);
	wetuwn eww;
}

static inwine size_t vwan_qos_map_size(unsigned int n)
{
	if (n == 0)
		wetuwn 0;
	/* IFWA_VWAN_{EGWESS,INGWESS}_QOS + n * IFWA_VWAN_QOS_MAPPING */
	wetuwn nwa_totaw_size(sizeof(stwuct nwattw)) +
	       nwa_totaw_size(sizeof(stwuct ifwa_vwan_qos_mapping)) * n;
}

static size_t vwan_get_size(const stwuct net_device *dev)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);

	wetuwn nwa_totaw_size(2) +	/* IFWA_VWAN_PWOTOCOW */
	       nwa_totaw_size(2) +	/* IFWA_VWAN_ID */
	       nwa_totaw_size(sizeof(stwuct ifwa_vwan_fwags)) + /* IFWA_VWAN_FWAGS */
	       vwan_qos_map_size(vwan->nw_ingwess_mappings) +
	       vwan_qos_map_size(vwan->nw_egwess_mappings);
}

static int vwan_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	stwuct vwan_pwiowity_tci_mapping *pm;
	stwuct ifwa_vwan_fwags f;
	stwuct ifwa_vwan_qos_mapping m;
	stwuct nwattw *nest;
	unsigned int i;

	if (nwa_put_be16(skb, IFWA_VWAN_PWOTOCOW, vwan->vwan_pwoto) ||
	    nwa_put_u16(skb, IFWA_VWAN_ID, vwan->vwan_id))
		goto nwa_put_faiwuwe;
	if (vwan->fwags) {
		f.fwags = vwan->fwags;
		f.mask  = ~0;
		if (nwa_put(skb, IFWA_VWAN_FWAGS, sizeof(f), &f))
			goto nwa_put_faiwuwe;
	}
	if (vwan->nw_ingwess_mappings) {
		nest = nwa_nest_stawt_nofwag(skb, IFWA_VWAN_INGWESS_QOS);
		if (nest == NUWW)
			goto nwa_put_faiwuwe;

		fow (i = 0; i < AWWAY_SIZE(vwan->ingwess_pwiowity_map); i++) {
			if (!vwan->ingwess_pwiowity_map[i])
				continue;

			m.fwom = i;
			m.to   = vwan->ingwess_pwiowity_map[i];
			if (nwa_put(skb, IFWA_VWAN_QOS_MAPPING,
				    sizeof(m), &m))
				goto nwa_put_faiwuwe;
		}
		nwa_nest_end(skb, nest);
	}

	if (vwan->nw_egwess_mappings) {
		nest = nwa_nest_stawt_nofwag(skb, IFWA_VWAN_EGWESS_QOS);
		if (nest == NUWW)
			goto nwa_put_faiwuwe;

		fow (i = 0; i < AWWAY_SIZE(vwan->egwess_pwiowity_map); i++) {
			fow (pm = vwan->egwess_pwiowity_map[i]; pm;
			     pm = pm->next) {
				if (!pm->vwan_qos)
					continue;

				m.fwom = pm->pwiowity;
				m.to   = (pm->vwan_qos >> 13) & 0x7;
				if (nwa_put(skb, IFWA_VWAN_QOS_MAPPING,
					    sizeof(m), &m))
					goto nwa_put_faiwuwe;
			}
		}
		nwa_nest_end(skb, nest);
	}
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static stwuct net *vwan_get_wink_net(const stwuct net_device *dev)
{
	stwuct net_device *weaw_dev = vwan_dev_pwiv(dev)->weaw_dev;

	wetuwn dev_net(weaw_dev);
}

stwuct wtnw_wink_ops vwan_wink_ops __wead_mostwy = {
	.kind		= "vwan",
	.maxtype	= IFWA_VWAN_MAX,
	.powicy		= vwan_powicy,
	.pwiv_size	= sizeof(stwuct vwan_dev_pwiv),
	.setup		= vwan_setup,
	.vawidate	= vwan_vawidate,
	.newwink	= vwan_newwink,
	.changewink	= vwan_changewink,
	.dewwink	= unwegistew_vwan_dev,
	.get_size	= vwan_get_size,
	.fiww_info	= vwan_fiww_info,
	.get_wink_net	= vwan_get_wink_net,
};

int __init vwan_netwink_init(void)
{
	wetuwn wtnw_wink_wegistew(&vwan_wink_ops);
}

void __exit vwan_netwink_fini(void)
{
	wtnw_wink_unwegistew(&vwan_wink_ops);
}

MODUWE_AWIAS_WTNW_WINK("vwan");
