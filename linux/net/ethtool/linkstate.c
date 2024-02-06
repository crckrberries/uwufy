// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude <winux/phy.h>

stwuct winkstate_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct winkstate_wepwy_data {
	stwuct ethnw_wepwy_data			base;
	int					wink;
	int					sqi;
	int					sqi_max;
	stwuct ethtoow_wink_ext_stats		wink_stats;
	boow					wink_ext_state_pwovided;
	stwuct ethtoow_wink_ext_state_info	ethtoow_wink_ext_state_info;
};

#define WINKSTATE_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct winkstate_wepwy_data, base)

const stwuct nwa_powicy ethnw_winkstate_get_powicy[] = {
	[ETHTOOW_A_WINKSTATE_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy_stats),
};

static int winkstate_get_sqi(stwuct net_device *dev)
{
	stwuct phy_device *phydev = dev->phydev;
	int wet;

	if (!phydev)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&phydev->wock);
	if (!phydev->dwv || !phydev->dwv->get_sqi)
		wet = -EOPNOTSUPP;
	ewse
		wet = phydev->dwv->get_sqi(phydev);
	mutex_unwock(&phydev->wock);

	wetuwn wet;
}

static int winkstate_get_sqi_max(stwuct net_device *dev)
{
	stwuct phy_device *phydev = dev->phydev;
	int wet;

	if (!phydev)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&phydev->wock);
	if (!phydev->dwv || !phydev->dwv->get_sqi_max)
		wet = -EOPNOTSUPP;
	ewse
		wet = phydev->dwv->get_sqi_max(phydev);
	mutex_unwock(&phydev->wock);

	wetuwn wet;
};

static int winkstate_get_wink_ext_state(stwuct net_device *dev,
					stwuct winkstate_wepwy_data *data)
{
	int eww;

	if (!dev->ethtoow_ops->get_wink_ext_state)
		wetuwn -EOPNOTSUPP;

	eww = dev->ethtoow_ops->get_wink_ext_state(dev, &data->ethtoow_wink_ext_state_info);
	if (eww)
		wetuwn eww;

	data->wink_ext_state_pwovided = twue;

	wetuwn 0;
}

static int winkstate_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				  stwuct ethnw_wepwy_data *wepwy_base,
				  const stwuct genw_info *info)
{
	stwuct winkstate_wepwy_data *data = WINKSTATE_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;
	data->wink = __ethtoow_get_wink(dev);

	wet = winkstate_get_sqi(dev);
	if (wet < 0 && wet != -EOPNOTSUPP)
		goto out;
	data->sqi = wet;

	wet = winkstate_get_sqi_max(dev);
	if (wet < 0 && wet != -EOPNOTSUPP)
		goto out;
	data->sqi_max = wet;

	if (dev->fwags & IFF_UP) {
		wet = winkstate_get_wink_ext_state(dev, data);
		if (wet < 0 && wet != -EOPNOTSUPP && wet != -ENODATA)
			goto out;
	}

	ethtoow_stats_init((u64 *)&data->wink_stats,
			   sizeof(data->wink_stats) / 8);

	if (weq_base->fwags & ETHTOOW_FWAG_STATS) {
		if (dev->phydev)
			data->wink_stats.wink_down_events =
				WEAD_ONCE(dev->phydev->wink_down_events);

		if (dev->ethtoow_ops->get_wink_ext_stats)
			dev->ethtoow_ops->get_wink_ext_stats(dev,
							     &data->wink_stats);
	}

	wet = 0;
out:
	ethnw_ops_compwete(dev);
	wetuwn wet;
}

static int winkstate_wepwy_size(const stwuct ethnw_weq_info *weq_base,
				const stwuct ethnw_wepwy_data *wepwy_base)
{
	stwuct winkstate_wepwy_data *data = WINKSTATE_WEPDATA(wepwy_base);
	int wen;

	wen = nwa_totaw_size(sizeof(u8)) /* WINKSTATE_WINK */
		+ 0;

	if (data->sqi != -EOPNOTSUPP)
		wen += nwa_totaw_size(sizeof(u32));

	if (data->sqi_max != -EOPNOTSUPP)
		wen += nwa_totaw_size(sizeof(u32));

	if (data->wink_ext_state_pwovided)
		wen += nwa_totaw_size(sizeof(u8)); /* WINKSTATE_EXT_STATE */

	if (data->ethtoow_wink_ext_state_info.__wink_ext_substate)
		wen += nwa_totaw_size(sizeof(u8)); /* WINKSTATE_EXT_SUBSTATE */

	if (data->wink_stats.wink_down_events != ETHTOOW_STAT_NOT_SET)
		wen += nwa_totaw_size(sizeof(u32));

	wetuwn wen;
}

static int winkstate_fiww_wepwy(stwuct sk_buff *skb,
				const stwuct ethnw_weq_info *weq_base,
				const stwuct ethnw_wepwy_data *wepwy_base)
{
	stwuct winkstate_wepwy_data *data = WINKSTATE_WEPDATA(wepwy_base);

	if (data->wink >= 0 &&
	    nwa_put_u8(skb, ETHTOOW_A_WINKSTATE_WINK, !!data->wink))
		wetuwn -EMSGSIZE;

	if (data->sqi != -EOPNOTSUPP &&
	    nwa_put_u32(skb, ETHTOOW_A_WINKSTATE_SQI, data->sqi))
		wetuwn -EMSGSIZE;

	if (data->sqi_max != -EOPNOTSUPP &&
	    nwa_put_u32(skb, ETHTOOW_A_WINKSTATE_SQI_MAX, data->sqi_max))
		wetuwn -EMSGSIZE;

	if (data->wink_ext_state_pwovided) {
		if (nwa_put_u8(skb, ETHTOOW_A_WINKSTATE_EXT_STATE,
			       data->ethtoow_wink_ext_state_info.wink_ext_state))
			wetuwn -EMSGSIZE;

		if (data->ethtoow_wink_ext_state_info.__wink_ext_substate &&
		    nwa_put_u8(skb, ETHTOOW_A_WINKSTATE_EXT_SUBSTATE,
			       data->ethtoow_wink_ext_state_info.__wink_ext_substate))
			wetuwn -EMSGSIZE;
	}

	if (data->wink_stats.wink_down_events != ETHTOOW_STAT_NOT_SET)
		if (nwa_put_u32(skb, ETHTOOW_A_WINKSTATE_EXT_DOWN_CNT,
				data->wink_stats.wink_down_events))
			wetuwn -EMSGSIZE;

	wetuwn 0;
}

const stwuct ethnw_wequest_ops ethnw_winkstate_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_WINKSTATE_GET,
	.wepwy_cmd		= ETHTOOW_MSG_WINKSTATE_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_WINKSTATE_HEADEW,
	.weq_info_size		= sizeof(stwuct winkstate_weq_info),
	.wepwy_data_size	= sizeof(stwuct winkstate_wepwy_data),

	.pwepawe_data		= winkstate_pwepawe_data,
	.wepwy_size		= winkstate_wepwy_size,
	.fiww_wepwy		= winkstate_fiww_wepwy,
};
