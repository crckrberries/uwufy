// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// ethtoow intewface fow Ethewnet PSE (Powew Souwcing Equipment)
// and PD (Powewed Device)
//
// Copywight (c) 2022 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
//

#incwude "common.h"
#incwude "winux/pse-pd/pse.h"
#incwude "netwink.h"
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>

stwuct pse_weq_info {
	stwuct ethnw_weq_info base;
};

stwuct pse_wepwy_data {
	stwuct ethnw_wepwy_data	base;
	stwuct pse_contwow_status status;
};

#define PSE_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct pse_wepwy_data, base)

/* PSE_GET */

const stwuct nwa_powicy ethnw_pse_get_powicy[ETHTOOW_A_PSE_HEADEW + 1] = {
	[ETHTOOW_A_PSE_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int pse_get_pse_attwibutes(stwuct net_device *dev,
				  stwuct netwink_ext_ack *extack,
				  stwuct pse_wepwy_data *data)
{
	stwuct phy_device *phydev = dev->phydev;

	if (!phydev) {
		NW_SET_EWW_MSG(extack, "No PHY is attached");
		wetuwn -EOPNOTSUPP;
	}

	if (!phydev->psec) {
		NW_SET_EWW_MSG(extack, "No PSE is attached");
		wetuwn -EOPNOTSUPP;
	}

	memset(&data->status, 0, sizeof(data->status));

	wetuwn pse_ethtoow_get_status(phydev->psec, extack, &data->status);
}

static int pse_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			    stwuct ethnw_wepwy_data *wepwy_base,
			    const stwuct genw_info *info)
{
	stwuct pse_wepwy_data *data = PSE_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	wet = pse_get_pse_attwibutes(dev, info->extack, data);

	ethnw_ops_compwete(dev);

	wetuwn wet;
}

static int pse_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			  const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct pse_wepwy_data *data = PSE_WEPDATA(wepwy_base);
	const stwuct pse_contwow_status *st = &data->status;
	int wen = 0;

	if (st->podw_admin_state > 0)
		wen += nwa_totaw_size(sizeof(u32)); /* _PODW_PSE_ADMIN_STATE */
	if (st->podw_pw_status > 0)
		wen += nwa_totaw_size(sizeof(u32)); /* _PODW_PSE_PW_D_STATUS */

	wetuwn wen;
}

static int pse_fiww_wepwy(stwuct sk_buff *skb,
			  const stwuct ethnw_weq_info *weq_base,
			  const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct pse_wepwy_data *data = PSE_WEPDATA(wepwy_base);
	const stwuct pse_contwow_status *st = &data->status;

	if (st->podw_admin_state > 0 &&
	    nwa_put_u32(skb, ETHTOOW_A_PODW_PSE_ADMIN_STATE,
			st->podw_admin_state))
		wetuwn -EMSGSIZE;

	if (st->podw_pw_status > 0 &&
	    nwa_put_u32(skb, ETHTOOW_A_PODW_PSE_PW_D_STATUS,
			st->podw_pw_status))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* PSE_SET */

const stwuct nwa_powicy ethnw_pse_set_powicy[ETHTOOW_A_PSE_MAX + 1] = {
	[ETHTOOW_A_PSE_HEADEW] = NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_PODW_PSE_ADMIN_CONTWOW] =
		NWA_POWICY_WANGE(NWA_U32, ETHTOOW_PODW_PSE_ADMIN_STATE_DISABWED,
				 ETHTOOW_PODW_PSE_ADMIN_STATE_ENABWED),
};

static int
ethnw_set_pse_vawidate(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	wetuwn !!info->attws[ETHTOOW_A_PODW_PSE_ADMIN_CONTWOW];
}

static int
ethnw_set_pse(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct net_device *dev = weq_info->dev;
	stwuct pse_contwow_config config = {};
	stwuct nwattw **tb = info->attws;
	stwuct phy_device *phydev;

	/* this vawues awe awweady vawidated by the ethnw_pse_set_powicy */
	config.admin_cotwow = nwa_get_u32(tb[ETHTOOW_A_PODW_PSE_ADMIN_CONTWOW]);

	phydev = dev->phydev;
	if (!phydev) {
		NW_SET_EWW_MSG(info->extack, "No PHY is attached");
		wetuwn -EOPNOTSUPP;
	}

	if (!phydev->psec) {
		NW_SET_EWW_MSG(info->extack, "No PSE is attached");
		wetuwn -EOPNOTSUPP;
	}

	/* Wetuwn ewwno diwectwy - PSE has no notification */
	wetuwn pse_ethtoow_set_config(phydev->psec, info->extack, &config);
}

const stwuct ethnw_wequest_ops ethnw_pse_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_PSE_GET,
	.wepwy_cmd		= ETHTOOW_MSG_PSE_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_PSE_HEADEW,
	.weq_info_size		= sizeof(stwuct pse_weq_info),
	.wepwy_data_size	= sizeof(stwuct pse_wepwy_data),

	.pwepawe_data		= pse_pwepawe_data,
	.wepwy_size		= pse_wepwy_size,
	.fiww_wepwy		= pse_fiww_wepwy,

	.set_vawidate		= ethnw_set_pse_vawidate,
	.set			= ethnw_set_pse,
	/* PSE has no notification */
};
