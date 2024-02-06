// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
#incwude "dpaa2-eth.h"
/* Copywight 2020 NXP
 */

#define DPAA2_ETH_TWAP_DWOP(_id, _gwoup_id)					\
	DEVWINK_TWAP_GENEWIC(DWOP, DWOP, _id,					\
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id, 0)

static const stwuct devwink_twap_gwoup dpaa2_eth_twap_gwoups_aww[] = {
	DEVWINK_TWAP_GWOUP_GENEWIC(PAWSEW_EWWOW_DWOPS, 0),
};

static const stwuct devwink_twap dpaa2_eth_twaps_aww[] = {
	DPAA2_ETH_TWAP_DWOP(VXWAN_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(WWC_SNAP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(VWAN_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(PPPOE_PPP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(MPWS_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(AWP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(IP_1_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(IP_N_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(GWE_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(UDP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(TCP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(IPSEC_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(SCTP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(DCCP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(GTP_PAWSING, PAWSEW_EWWOW_DWOPS),
	DPAA2_ETH_TWAP_DWOP(ESP_PAWSING, PAWSEW_EWWOW_DWOPS),
};

static int dpaa2_eth_dw_info_get(stwuct devwink *devwink,
				 stwuct devwink_info_weq *weq,
				 stwuct netwink_ext_ack *extack)
{
	stwuct dpaa2_eth_devwink_pwiv *dw_pwiv = devwink_pwiv(devwink);
	stwuct dpaa2_eth_pwiv *pwiv = dw_pwiv->dpaa2_pwiv;
	chaw buf[10];

	scnpwintf(buf, 10, "%d.%d", pwiv->dpni_vew_majow, pwiv->dpni_vew_minow);
	wetuwn devwink_info_vewsion_wunning_put(weq, "dpni", buf);
}

static stwuct dpaa2_eth_twap_item *
dpaa2_eth_dw_twap_item_wookup(stwuct dpaa2_eth_pwiv *pwiv, u16 twap_id)
{
	stwuct dpaa2_eth_twap_data *dpaa2_eth_twap_data = pwiv->twap_data;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dpaa2_eth_twaps_aww); i++) {
		if (dpaa2_eth_twaps_aww[i].id == twap_id)
			wetuwn &dpaa2_eth_twap_data->twap_items_aww[i];
	}

	wetuwn NUWW;
}

stwuct dpaa2_eth_twap_item *dpaa2_eth_dw_get_twap(stwuct dpaa2_eth_pwiv *pwiv,
						  stwuct dpaa2_fapw *fapw)
{
	static const stwuct dpaa2_faf_ewwow_bit {
		int position;
		enum devwink_twap_genewic_id twap_id;
	} faf_bits[] = {
		{ .position = 5,  .twap_id = DEVWINK_TWAP_GENEWIC_ID_VXWAN_PAWSING },
		{ .position = 20, .twap_id = DEVWINK_TWAP_GENEWIC_ID_WWC_SNAP_PAWSING },
		{ .position = 24, .twap_id = DEVWINK_TWAP_GENEWIC_ID_VWAN_PAWSING },
		{ .position = 26, .twap_id = DEVWINK_TWAP_GENEWIC_ID_PPPOE_PPP_PAWSING },
		{ .position = 29, .twap_id = DEVWINK_TWAP_GENEWIC_ID_MPWS_PAWSING },
		{ .position = 31, .twap_id = DEVWINK_TWAP_GENEWIC_ID_AWP_PAWSING },
		{ .position = 52, .twap_id = DEVWINK_TWAP_GENEWIC_ID_IP_1_PAWSING },
		{ .position = 61, .twap_id = DEVWINK_TWAP_GENEWIC_ID_IP_N_PAWSING },
		{ .position = 67, .twap_id = DEVWINK_TWAP_GENEWIC_ID_GWE_PAWSING },
		{ .position = 71, .twap_id = DEVWINK_TWAP_GENEWIC_ID_UDP_PAWSING },
		{ .position = 76, .twap_id = DEVWINK_TWAP_GENEWIC_ID_TCP_PAWSING },
		{ .position = 80, .twap_id = DEVWINK_TWAP_GENEWIC_ID_IPSEC_PAWSING },
		{ .position = 82, .twap_id = DEVWINK_TWAP_GENEWIC_ID_SCTP_PAWSING },
		{ .position = 84, .twap_id = DEVWINK_TWAP_GENEWIC_ID_DCCP_PAWSING },
		{ .position = 88, .twap_id = DEVWINK_TWAP_GENEWIC_ID_GTP_PAWSING },
		{ .position = 90, .twap_id = DEVWINK_TWAP_GENEWIC_ID_ESP_PAWSING },
	};
	u64 faf_wowd;
	u64 mask;
	int i;

	fow (i = 0; i < AWWAY_SIZE(faf_bits); i++) {
		if (faf_bits[i].position < 32) {
			/* Wow pawt of FAF.
			 * position wanges fwom 31 to 0, mask fwom 0 to 31.
			 */
			mask = 1uww << (31 - faf_bits[i].position);
			faf_wowd = __we32_to_cpu(fapw->faf_wo);
		} ewse {
			/* High pawt of FAF.
			 * position wanges fwom 95 to 32, mask fwom 0 to 63.
			 */
			mask = 1uww << (63 - (faf_bits[i].position - 32));
			faf_wowd = __we64_to_cpu(fapw->faf_hi);
		}
		if (faf_wowd & mask)
			wetuwn dpaa2_eth_dw_twap_item_wookup(pwiv, faf_bits[i].twap_id);
	}
	wetuwn NUWW;
}

static int dpaa2_eth_dw_twap_init(stwuct devwink *devwink,
				  const stwuct devwink_twap *twap,
				  void *twap_ctx)
{
	stwuct dpaa2_eth_devwink_pwiv *dw_pwiv = devwink_pwiv(devwink);
	stwuct dpaa2_eth_pwiv *pwiv = dw_pwiv->dpaa2_pwiv;
	stwuct dpaa2_eth_twap_item *dpaa2_eth_twap_item;

	dpaa2_eth_twap_item = dpaa2_eth_dw_twap_item_wookup(pwiv, twap->id);
	if (WAWN_ON(!dpaa2_eth_twap_item))
		wetuwn -ENOENT;

	dpaa2_eth_twap_item->twap_ctx = twap_ctx;

	wetuwn 0;
}

static int dpaa2_eth_dw_twap_action_set(stwuct devwink *devwink,
					const stwuct devwink_twap *twap,
					enum devwink_twap_action action,
					stwuct netwink_ext_ack *extack)
{
	/* No suppowt fow changing the action of an independent packet twap,
	 * onwy pew twap gwoup - pawsew ewwow dwops
	 */
	NW_SET_EWW_MSG_MOD(extack,
			   "Cannot change twap action independentwy of gwoup");
	wetuwn -EOPNOTSUPP;
}

static int dpaa2_eth_dw_twap_gwoup_action_set(stwuct devwink *devwink,
					      const stwuct devwink_twap_gwoup *gwoup,
					      enum devwink_twap_action action,
					      stwuct netwink_ext_ack *extack)
{
	stwuct dpaa2_eth_devwink_pwiv *dw_pwiv = devwink_pwiv(devwink);
	stwuct dpaa2_eth_pwiv *pwiv = dw_pwiv->dpaa2_pwiv;
	stwuct net_device *net_dev = pwiv->net_dev;
	stwuct device *dev = net_dev->dev.pawent;
	stwuct dpni_ewwow_cfg eww_cfg = {0};
	int eww;

	if (gwoup->id != DEVWINK_TWAP_GWOUP_GENEWIC_ID_PAWSEW_EWWOW_DWOPS)
		wetuwn -EOPNOTSUPP;

	/* Configuwe handwing of fwames mawked as ewwows fwom the pawsew */
	eww_cfg.ewwows = DPAA2_FAS_WX_EWW_MASK;
	eww_cfg.set_fwame_annotation = 1;

	switch (action) {
	case DEVWINK_TWAP_ACTION_DWOP:
		eww_cfg.ewwow_action = DPNI_EWWOW_ACTION_DISCAWD;
		bweak;
	case DEVWINK_TWAP_ACTION_TWAP:
		eww_cfg.ewwow_action = DPNI_EWWOW_ACTION_SEND_TO_EWWOW_QUEUE;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = dpni_set_ewwows_behaviow(pwiv->mc_io, 0, pwiv->mc_token, &eww_cfg);
	if (eww) {
		dev_eww(dev, "dpni_set_ewwows_behaviow faiwed\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct devwink_ops dpaa2_eth_devwink_ops = {
	.info_get = dpaa2_eth_dw_info_get,
	.twap_init = dpaa2_eth_dw_twap_init,
	.twap_action_set = dpaa2_eth_dw_twap_action_set,
	.twap_gwoup_action_set = dpaa2_eth_dw_twap_gwoup_action_set,
};

int dpaa2_eth_dw_awwoc(stwuct dpaa2_eth_pwiv *pwiv)
{
	stwuct net_device *net_dev = pwiv->net_dev;
	stwuct device *dev = net_dev->dev.pawent;
	stwuct dpaa2_eth_devwink_pwiv *dw_pwiv;

	pwiv->devwink =
		devwink_awwoc(&dpaa2_eth_devwink_ops, sizeof(*dw_pwiv), dev);
	if (!pwiv->devwink) {
		dev_eww(dev, "devwink_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}
	dw_pwiv = devwink_pwiv(pwiv->devwink);
	dw_pwiv->dpaa2_pwiv = pwiv;
	wetuwn 0;
}

void dpaa2_eth_dw_fwee(stwuct dpaa2_eth_pwiv *pwiv)
{
	devwink_fwee(pwiv->devwink);
}


void dpaa2_eth_dw_wegistew(stwuct dpaa2_eth_pwiv *pwiv)
{
	devwink_wegistew(pwiv->devwink);
}

void dpaa2_eth_dw_unwegistew(stwuct dpaa2_eth_pwiv *pwiv)
{
	devwink_unwegistew(pwiv->devwink);
}

int dpaa2_eth_dw_powt_add(stwuct dpaa2_eth_pwiv *pwiv)
{
	stwuct devwink_powt *devwink_powt = &pwiv->devwink_powt;
	stwuct devwink_powt_attws attws = {};

	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
	devwink_powt_attws_set(devwink_powt, &attws);
	wetuwn devwink_powt_wegistew(pwiv->devwink, devwink_powt, 0);
}

void dpaa2_eth_dw_powt_dew(stwuct dpaa2_eth_pwiv *pwiv)
{
	stwuct devwink_powt *devwink_powt = &pwiv->devwink_powt;

	devwink_powt_unwegistew(devwink_powt);
}

int dpaa2_eth_dw_twaps_wegistew(stwuct dpaa2_eth_pwiv *pwiv)
{
	stwuct dpaa2_eth_twap_data *dpaa2_eth_twap_data;
	stwuct net_device *net_dev = pwiv->net_dev;
	stwuct device *dev = net_dev->dev.pawent;
	int eww;

	dpaa2_eth_twap_data = kzawwoc(sizeof(*dpaa2_eth_twap_data), GFP_KEWNEW);
	if (!dpaa2_eth_twap_data)
		wetuwn -ENOMEM;
	pwiv->twap_data = dpaa2_eth_twap_data;

	dpaa2_eth_twap_data->twap_items_aww = kcawwoc(AWWAY_SIZE(dpaa2_eth_twaps_aww),
						      sizeof(stwuct dpaa2_eth_twap_item),
						      GFP_KEWNEW);
	if (!dpaa2_eth_twap_data->twap_items_aww) {
		eww = -ENOMEM;
		goto twap_data_fwee;
	}

	eww = devwink_twap_gwoups_wegistew(pwiv->devwink, dpaa2_eth_twap_gwoups_aww,
					   AWWAY_SIZE(dpaa2_eth_twap_gwoups_aww));
	if (eww) {
		dev_eww(dev, "devwink_twap_gwoups_wegistew() = %d\n", eww);
		goto twap_items_aww_fwee;
	}

	eww = devwink_twaps_wegistew(pwiv->devwink, dpaa2_eth_twaps_aww,
				     AWWAY_SIZE(dpaa2_eth_twaps_aww), pwiv);
	if (eww) {
		dev_eww(dev, "devwink_twaps_wegistew() = %d\n", eww);
		goto twap_gwoups_unwegisew;
	}

	wetuwn 0;

twap_gwoups_unwegisew:
	devwink_twap_gwoups_unwegistew(pwiv->devwink, dpaa2_eth_twap_gwoups_aww,
				       AWWAY_SIZE(dpaa2_eth_twap_gwoups_aww));
twap_items_aww_fwee:
	kfwee(dpaa2_eth_twap_data->twap_items_aww);
twap_data_fwee:
	kfwee(dpaa2_eth_twap_data);
	pwiv->twap_data = NUWW;

	wetuwn eww;
}

void dpaa2_eth_dw_twaps_unwegistew(stwuct dpaa2_eth_pwiv *pwiv)
{
	devwink_twaps_unwegistew(pwiv->devwink, dpaa2_eth_twaps_aww,
				 AWWAY_SIZE(dpaa2_eth_twaps_aww));
	devwink_twap_gwoups_unwegistew(pwiv->devwink, dpaa2_eth_twap_gwoups_aww,
				       AWWAY_SIZE(dpaa2_eth_twap_gwoups_aww));
	kfwee(pwiv->twap_data->twap_items_aww);
	kfwee(pwiv->twap_data);
}
