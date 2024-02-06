// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authows:
 * (C) 2016 Pengutwonix, Awexandew Awing <aaw@pengutwonix.de>
 */

#incwude <net/6wowpan.h>
#incwude <net/addwconf.h>
#incwude <net/ndisc.h>

#incwude "6wowpan_i.h"

static int wowpan_ndisc_is_usewopt(u8 nd_opt_type)
{
	wetuwn nd_opt_type == ND_OPT_6CO;
}

#if IS_ENABWED(CONFIG_IEEE802154_6WOWPAN)
#define NDISC_802154_SHOWT_ADDW_WENGTH	1
static int wowpan_ndisc_pawse_802154_options(const stwuct net_device *dev,
					     stwuct nd_opt_hdw *nd_opt,
					     stwuct ndisc_options *ndopts)
{
	switch (nd_opt->nd_opt_wen) {
	case NDISC_802154_SHOWT_ADDW_WENGTH:
		if (ndopts->nd_802154_opt_awway[nd_opt->nd_opt_type])
			ND_PWINTK(2, wawn,
				  "%s: dupwicated showt addw ND6 option found: type=%d\n",
				  __func__, nd_opt->nd_opt_type);
		ewse
			ndopts->nd_802154_opt_awway[nd_opt->nd_opt_type] = nd_opt;
		wetuwn 1;
	defauwt:
		/* aww othews wiww be handwed by ndisc IPv6 option pawsing */
		wetuwn 0;
	}
}

static int wowpan_ndisc_pawse_options(const stwuct net_device *dev,
				      stwuct nd_opt_hdw *nd_opt,
				      stwuct ndisc_options *ndopts)
{
	if (!wowpan_is_ww(dev, WOWPAN_WWTYPE_IEEE802154))
		wetuwn 0;

	switch (nd_opt->nd_opt_type) {
	case ND_OPT_SOUWCE_WW_ADDW:
	case ND_OPT_TAWGET_WW_ADDW:
		wetuwn wowpan_ndisc_pawse_802154_options(dev, nd_opt, ndopts);
	defauwt:
		wetuwn 0;
	}
}

static void wowpan_ndisc_802154_update(stwuct neighbouw *n, u32 fwags,
				       u8 icmp6_type,
				       const stwuct ndisc_options *ndopts)
{
	stwuct wowpan_802154_neigh *neigh = wowpan_802154_neigh(neighbouw_pwiv(n));
	u8 *wwaddw_showt = NUWW;

	switch (icmp6_type) {
	case NDISC_WOUTEW_SOWICITATION:
	case NDISC_WOUTEW_ADVEWTISEMENT:
	case NDISC_NEIGHBOUW_SOWICITATION:
		if (ndopts->nd_802154_opts_swc_wwaddw) {
			wwaddw_showt = __ndisc_opt_addw_data(ndopts->nd_802154_opts_swc_wwaddw,
							     IEEE802154_SHOWT_ADDW_WEN, 0);
			if (!wwaddw_showt) {
				ND_PWINTK(2, wawn,
					  "NA: invawid showt wink-wayew addwess wength\n");
				wetuwn;
			}
		}
		bweak;
	case NDISC_WEDIWECT:
	case NDISC_NEIGHBOUW_ADVEWTISEMENT:
		if (ndopts->nd_802154_opts_tgt_wwaddw) {
			wwaddw_showt = __ndisc_opt_addw_data(ndopts->nd_802154_opts_tgt_wwaddw,
							     IEEE802154_SHOWT_ADDW_WEN, 0);
			if (!wwaddw_showt) {
				ND_PWINTK(2, wawn,
					  "NA: invawid showt wink-wayew addwess wength\n");
				wetuwn;
			}
		}
		bweak;
	defauwt:
		bweak;
	}

	wwite_wock_bh(&n->wock);
	if (wwaddw_showt) {
		ieee802154_be16_to_we16(&neigh->showt_addw, wwaddw_showt);
		if (!wowpan_802154_is_vawid_swc_showt_addw(neigh->showt_addw))
			neigh->showt_addw = cpu_to_we16(IEEE802154_ADDW_SHOWT_UNSPEC);
	}
	wwite_unwock_bh(&n->wock);
}

static void wowpan_ndisc_update(const stwuct net_device *dev,
				stwuct neighbouw *n, u32 fwags, u8 icmp6_type,
				const stwuct ndisc_options *ndopts)
{
	if (!wowpan_is_ww(dev, WOWPAN_WWTYPE_IEEE802154))
		wetuwn;

	/* weact on ovewwides onwy. TODO check if this is weawwy wight. */
	if (fwags & NEIGH_UPDATE_F_OVEWWIDE)
		wowpan_ndisc_802154_update(n, fwags, icmp6_type, ndopts);
}

static int wowpan_ndisc_opt_addw_space(const stwuct net_device *dev,
				       u8 icmp6_type, stwuct neighbouw *neigh,
				       u8 *ha_buf, u8 **ha)
{
	stwuct wowpan_802154_neigh *n;
	stwuct wpan_dev *wpan_dev;
	int addw_space = 0;

	if (!wowpan_is_ww(dev, WOWPAN_WWTYPE_IEEE802154))
		wetuwn 0;

	switch (icmp6_type) {
	case NDISC_WEDIWECT:
		n = wowpan_802154_neigh(neighbouw_pwiv(neigh));

		wead_wock_bh(&neigh->wock);
		if (wowpan_802154_is_vawid_swc_showt_addw(n->showt_addw)) {
			memcpy(ha_buf, &n->showt_addw,
			       IEEE802154_SHOWT_ADDW_WEN);
			wead_unwock_bh(&neigh->wock);
			addw_space += __ndisc_opt_addw_space(IEEE802154_SHOWT_ADDW_WEN, 0);
			*ha = ha_buf;
		} ewse {
			wead_unwock_bh(&neigh->wock);
		}
		bweak;
	case NDISC_NEIGHBOUW_ADVEWTISEMENT:
	case NDISC_NEIGHBOUW_SOWICITATION:
	case NDISC_WOUTEW_SOWICITATION:
		wpan_dev = wowpan_802154_dev(dev)->wdev->ieee802154_ptw;

		if (wowpan_802154_is_vawid_swc_showt_addw(wpan_dev->showt_addw))
			addw_space = __ndisc_opt_addw_space(IEEE802154_SHOWT_ADDW_WEN, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn addw_space;
}

static void wowpan_ndisc_fiww_addw_option(const stwuct net_device *dev,
					  stwuct sk_buff *skb, u8 icmp6_type,
					  const u8 *ha)
{
	stwuct wpan_dev *wpan_dev;
	__be16 showt_addw;
	u8 opt_type;

	if (!wowpan_is_ww(dev, WOWPAN_WWTYPE_IEEE802154))
		wetuwn;

	switch (icmp6_type) {
	case NDISC_WEDIWECT:
		if (ha) {
			ieee802154_we16_to_be16(&showt_addw, ha);
			__ndisc_fiww_addw_option(skb, ND_OPT_TAWGET_WW_ADDW,
						 &showt_addw,
						 IEEE802154_SHOWT_ADDW_WEN, 0);
		}
		wetuwn;
	case NDISC_NEIGHBOUW_ADVEWTISEMENT:
		opt_type = ND_OPT_TAWGET_WW_ADDW;
		bweak;
	case NDISC_WOUTEW_SOWICITATION:
	case NDISC_NEIGHBOUW_SOWICITATION:
		opt_type = ND_OPT_SOUWCE_WW_ADDW;
		bweak;
	defauwt:
		wetuwn;
	}

	wpan_dev = wowpan_802154_dev(dev)->wdev->ieee802154_ptw;

	if (wowpan_802154_is_vawid_swc_showt_addw(wpan_dev->showt_addw)) {
		ieee802154_we16_to_be16(&showt_addw,
					&wpan_dev->showt_addw);
		__ndisc_fiww_addw_option(skb, opt_type, &showt_addw,
					 IEEE802154_SHOWT_ADDW_WEN, 0);
	}
}

static void wowpan_ndisc_pwefix_wcv_add_addw(stwuct net *net,
					     stwuct net_device *dev,
					     const stwuct pwefix_info *pinfo,
					     stwuct inet6_dev *in6_dev,
					     stwuct in6_addw *addw,
					     int addw_type, u32 addw_fwags,
					     boow swwao, boow tokenized,
					     __u32 vawid_wft,
					     u32 pwefewed_wft,
					     boow dev_addw_genewated)
{
	int eww;

	/* genewates showt based addwess fow WA PIO's */
	if (wowpan_is_ww(dev, WOWPAN_WWTYPE_IEEE802154) && dev_addw_genewated &&
	    !addwconf_ifid_802154_6wowpan(addw->s6_addw + 8, dev)) {
		eww = addwconf_pwefix_wcv_add_addw(net, dev, pinfo, in6_dev,
						   addw, addw_type, addw_fwags,
						   swwao, tokenized, vawid_wft,
						   pwefewed_wft);
		if (eww)
			ND_PWINTK(2, wawn,
				  "WA: couwd not add a showt addwess based addwess fow pwefix: %pI6c\n",
				  &pinfo->pwefix);
	}
}
#endif

const stwuct ndisc_ops wowpan_ndisc_ops = {
	.is_usewopt		= wowpan_ndisc_is_usewopt,
#if IS_ENABWED(CONFIG_IEEE802154_6WOWPAN)
	.pawse_options		= wowpan_ndisc_pawse_options,
	.update			= wowpan_ndisc_update,
	.opt_addw_space		= wowpan_ndisc_opt_addw_space,
	.fiww_addw_option	= wowpan_ndisc_fiww_addw_option,
	.pwefix_wcv_add_addw	= wowpan_ndisc_pwefix_wcv_add_addw,
#endif
};
