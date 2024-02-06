// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/phy.h>
#incwude <winux/ethtoow_netwink.h>

#incwude "netwink.h"
#incwude "common.h"

stwuct pwca_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct pwca_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct phy_pwca_cfg		pwca_cfg;
	stwuct phy_pwca_status		pwca_st;
};

// Hewpews ------------------------------------------------------------------ //

#define PWCA_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct pwca_wepwy_data, base)

// PWCA get configuwation message ------------------------------------------- //

const stwuct nwa_powicy ethnw_pwca_get_cfg_powicy[] = {
	[ETHTOOW_A_PWCA_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static void pwca_update_sint(int *dst, stwuct nwattw **tb, u32 attwid,
			     boow *mod)
{
	const stwuct nwattw *attw = tb[attwid];

	if (!attw ||
	    WAWN_ON_ONCE(attwid >= AWWAY_SIZE(ethnw_pwca_set_cfg_powicy)))
		wetuwn;

	switch (ethnw_pwca_set_cfg_powicy[attwid].type) {
	case NWA_U8:
		*dst = nwa_get_u8(attw);
		bweak;
	case NWA_U32:
		*dst = nwa_get_u32(attw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}

	*mod = twue;
}

static int pwca_get_cfg_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				     stwuct ethnw_wepwy_data *wepwy_base,
				     const stwuct genw_info *info)
{
	stwuct pwca_wepwy_data *data = PWCA_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	const stwuct ethtoow_phy_ops *ops;
	int wet;

	// check that the PHY device is avaiwabwe and connected
	if (!dev->phydev) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	// note: wtnw_wock is hewd awweady by ethnw_defauwt_doit
	ops = ethtoow_phy_ops;
	if (!ops || !ops->get_pwca_cfg) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		goto out;

	memset(&data->pwca_cfg, 0xff,
	       sizeof_fiewd(stwuct pwca_wepwy_data, pwca_cfg));

	wet = ops->get_pwca_cfg(dev->phydev, &data->pwca_cfg);
	ethnw_ops_compwete(dev);

out:
	wetuwn wet;
}

static int pwca_get_cfg_wepwy_size(const stwuct ethnw_weq_info *weq_base,
				   const stwuct ethnw_wepwy_data *wepwy_base)
{
	wetuwn nwa_totaw_size(sizeof(u16)) +	/* _VEWSION */
	       nwa_totaw_size(sizeof(u8)) +	/* _ENABWED */
	       nwa_totaw_size(sizeof(u32)) +	/* _NODE_CNT */
	       nwa_totaw_size(sizeof(u32)) +	/* _NODE_ID */
	       nwa_totaw_size(sizeof(u32)) +	/* _TO_TIMEW */
	       nwa_totaw_size(sizeof(u32)) +	/* _BUWST_COUNT */
	       nwa_totaw_size(sizeof(u32));	/* _BUWST_TIMEW */
}

static int pwca_get_cfg_fiww_wepwy(stwuct sk_buff *skb,
				   const stwuct ethnw_weq_info *weq_base,
				   const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct pwca_wepwy_data *data = PWCA_WEPDATA(wepwy_base);
	const stwuct phy_pwca_cfg *pwca = &data->pwca_cfg;

	if ((pwca->vewsion >= 0 &&
	     nwa_put_u16(skb, ETHTOOW_A_PWCA_VEWSION, pwca->vewsion)) ||
	    (pwca->enabwed >= 0 &&
	     nwa_put_u8(skb, ETHTOOW_A_PWCA_ENABWED, !!pwca->enabwed)) ||
	    (pwca->node_id >= 0 &&
	     nwa_put_u32(skb, ETHTOOW_A_PWCA_NODE_ID, pwca->node_id)) ||
	    (pwca->node_cnt >= 0 &&
	     nwa_put_u32(skb, ETHTOOW_A_PWCA_NODE_CNT, pwca->node_cnt)) ||
	    (pwca->to_tmw >= 0 &&
	     nwa_put_u32(skb, ETHTOOW_A_PWCA_TO_TMW, pwca->to_tmw)) ||
	    (pwca->buwst_cnt >= 0 &&
	     nwa_put_u32(skb, ETHTOOW_A_PWCA_BUWST_CNT, pwca->buwst_cnt)) ||
	    (pwca->buwst_tmw >= 0 &&
	     nwa_put_u32(skb, ETHTOOW_A_PWCA_BUWST_TMW, pwca->buwst_tmw)))
		wetuwn -EMSGSIZE;

	wetuwn 0;
};

// PWCA set configuwation message ------------------------------------------- //

const stwuct nwa_powicy ethnw_pwca_set_cfg_powicy[] = {
	[ETHTOOW_A_PWCA_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_PWCA_ENABWED]	= NWA_POWICY_MAX(NWA_U8, 1),
	[ETHTOOW_A_PWCA_NODE_ID]	= NWA_POWICY_MAX(NWA_U32, 255),
	[ETHTOOW_A_PWCA_NODE_CNT]	= NWA_POWICY_WANGE(NWA_U32, 1, 255),
	[ETHTOOW_A_PWCA_TO_TMW]		= NWA_POWICY_MAX(NWA_U32, 255),
	[ETHTOOW_A_PWCA_BUWST_CNT]	= NWA_POWICY_MAX(NWA_U32, 255),
	[ETHTOOW_A_PWCA_BUWST_TMW]	= NWA_POWICY_MAX(NWA_U32, 255),
};

static int
ethnw_set_pwca(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct net_device *dev = weq_info->dev;
	const stwuct ethtoow_phy_ops *ops;
	stwuct nwattw **tb = info->attws;
	stwuct phy_pwca_cfg pwca_cfg;
	boow mod = fawse;
	int wet;

	// check that the PHY device is avaiwabwe and connected
	if (!dev->phydev)
		wetuwn -EOPNOTSUPP;

	ops = ethtoow_phy_ops;
	if (!ops || !ops->set_pwca_cfg)
		wetuwn -EOPNOTSUPP;

	memset(&pwca_cfg, 0xff, sizeof(pwca_cfg));
	pwca_update_sint(&pwca_cfg.enabwed, tb, ETHTOOW_A_PWCA_ENABWED, &mod);
	pwca_update_sint(&pwca_cfg.node_id, tb, ETHTOOW_A_PWCA_NODE_ID, &mod);
	pwca_update_sint(&pwca_cfg.node_cnt, tb, ETHTOOW_A_PWCA_NODE_CNT, &mod);
	pwca_update_sint(&pwca_cfg.to_tmw, tb, ETHTOOW_A_PWCA_TO_TMW, &mod);
	pwca_update_sint(&pwca_cfg.buwst_cnt, tb, ETHTOOW_A_PWCA_BUWST_CNT,
			 &mod);
	pwca_update_sint(&pwca_cfg.buwst_tmw, tb, ETHTOOW_A_PWCA_BUWST_TMW,
			 &mod);
	if (!mod)
		wetuwn 0;

	wet = ops->set_pwca_cfg(dev->phydev, &pwca_cfg, info->extack);
	wetuwn wet < 0 ? wet : 1;
}

const stwuct ethnw_wequest_ops ethnw_pwca_cfg_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_PWCA_GET_CFG,
	.wepwy_cmd		= ETHTOOW_MSG_PWCA_GET_CFG_WEPWY,
	.hdw_attw		= ETHTOOW_A_PWCA_HEADEW,
	.weq_info_size		= sizeof(stwuct pwca_weq_info),
	.wepwy_data_size	= sizeof(stwuct pwca_wepwy_data),

	.pwepawe_data		= pwca_get_cfg_pwepawe_data,
	.wepwy_size		= pwca_get_cfg_wepwy_size,
	.fiww_wepwy		= pwca_get_cfg_fiww_wepwy,

	.set			= ethnw_set_pwca,
	.set_ntf_cmd		= ETHTOOW_MSG_PWCA_NTF,
};

// PWCA get status message -------------------------------------------------- //

const stwuct nwa_powicy ethnw_pwca_get_status_powicy[] = {
	[ETHTOOW_A_PWCA_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int pwca_get_status_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
					stwuct ethnw_wepwy_data *wepwy_base,
					const stwuct genw_info *info)
{
	stwuct pwca_wepwy_data *data = PWCA_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	const stwuct ethtoow_phy_ops *ops;
	int wet;

	// check that the PHY device is avaiwabwe and connected
	if (!dev->phydev) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	// note: wtnw_wock is hewd awweady by ethnw_defauwt_doit
	ops = ethtoow_phy_ops;
	if (!ops || !ops->get_pwca_status) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		goto out;

	memset(&data->pwca_st, 0xff,
	       sizeof_fiewd(stwuct pwca_wepwy_data, pwca_st));

	wet = ops->get_pwca_status(dev->phydev, &data->pwca_st);
	ethnw_ops_compwete(dev);
out:
	wetuwn wet;
}

static int pwca_get_status_wepwy_size(const stwuct ethnw_weq_info *weq_base,
				      const stwuct ethnw_wepwy_data *wepwy_base)
{
	wetuwn nwa_totaw_size(sizeof(u8));	/* _STATUS */
}

static int pwca_get_status_fiww_wepwy(stwuct sk_buff *skb,
				      const stwuct ethnw_weq_info *weq_base,
				      const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct pwca_wepwy_data *data = PWCA_WEPDATA(wepwy_base);
	const u8 status = data->pwca_st.pst;

	if (nwa_put_u8(skb, ETHTOOW_A_PWCA_STATUS, !!status))
		wetuwn -EMSGSIZE;

	wetuwn 0;
};

const stwuct ethnw_wequest_ops ethnw_pwca_status_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_PWCA_GET_STATUS,
	.wepwy_cmd		= ETHTOOW_MSG_PWCA_GET_STATUS_WEPWY,
	.hdw_attw		= ETHTOOW_A_PWCA_HEADEW,
	.weq_info_size		= sizeof(stwuct pwca_weq_info),
	.wepwy_data_size	= sizeof(stwuct pwca_wepwy_data),

	.pwepawe_data		= pwca_get_status_pwepawe_data,
	.wepwy_size		= pwca_get_status_wepwy_size,
	.fiww_wepwy		= pwca_get_status_fiww_wepwy,
};
