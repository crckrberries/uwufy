// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <net/genetwink.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_cfm.h"

static const stwuct nwa_powicy
bw_cfm_mep_cweate_powicy[IFWA_BWIDGE_CFM_MEP_CWEATE_MAX + 1] = {
	[IFWA_BWIDGE_CFM_MEP_CWEATE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_MEP_CWEATE_INSTANCE]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_MEP_CWEATE_DOMAIN]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_MEP_CWEATE_DIWECTION]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_MEP_CWEATE_IFINDEX]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy
bw_cfm_mep_dewete_powicy[IFWA_BWIDGE_CFM_MEP_DEWETE_MAX + 1] = {
	[IFWA_BWIDGE_CFM_MEP_DEWETE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_MEP_DEWETE_INSTANCE]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy
bw_cfm_mep_config_powicy[IFWA_BWIDGE_CFM_MEP_CONFIG_MAX + 1] = {
	[IFWA_BWIDGE_CFM_MEP_CONFIG_UNSPEC]	 = { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_MEP_CONFIG_INSTANCE]	 = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_MEP_CONFIG_UNICAST_MAC] = NWA_POWICY_ETH_ADDW,
	[IFWA_BWIDGE_CFM_MEP_CONFIG_MDWEVEW]	 = NWA_POWICY_MAX(NWA_U32, 7),
	[IFWA_BWIDGE_CFM_MEP_CONFIG_MEPID]	 = NWA_POWICY_MAX(NWA_U32, 0x1FFF),
};

static const stwuct nwa_powicy
bw_cfm_cc_config_powicy[IFWA_BWIDGE_CFM_CC_CONFIG_MAX + 1] = {
	[IFWA_BWIDGE_CFM_CC_CONFIG_UNSPEC]	 = { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_CC_CONFIG_INSTANCE]	 = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CONFIG_ENABWE]	 = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CONFIG_EXP_INTEWVAW] = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CONFIG_EXP_MAID]	 = {
	.type = NWA_BINAWY, .wen = CFM_MAID_WENGTH },
};

static const stwuct nwa_powicy
bw_cfm_cc_peew_mep_powicy[IFWA_BWIDGE_CFM_CC_PEEW_MEP_MAX + 1] = {
	[IFWA_BWIDGE_CFM_CC_PEEW_MEP_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_CC_PEEW_MEP_INSTANCE]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_PEEW_MEPID]		= NWA_POWICY_MAX(NWA_U32, 0x1FFF),
};

static const stwuct nwa_powicy
bw_cfm_cc_wdi_powicy[IFWA_BWIDGE_CFM_CC_WDI_MAX + 1] = {
	[IFWA_BWIDGE_CFM_CC_WDI_UNSPEC]		= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_CC_WDI_INSTANCE]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_WDI_WDI]		= { .type = NWA_U32 },
};

static const stwuct nwa_powicy
bw_cfm_cc_ccm_tx_powicy[IFWA_BWIDGE_CFM_CC_CCM_TX_MAX + 1] = {
	[IFWA_BWIDGE_CFM_CC_CCM_TX_UNSPEC]	   = { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_INSTANCE]	   = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_DMAC]	   = NWA_POWICY_ETH_ADDW,
	[IFWA_BWIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE]  = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_PEWIOD]	   = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV]	   = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV_VAWUE]   = { .type = NWA_U8 },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV]	   = { .type = NWA_U32 },
	[IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV_VAWUE] = { .type = NWA_U8 },
};

static const stwuct nwa_powicy
bw_cfm_powicy[IFWA_BWIDGE_CFM_MAX + 1] = {
	[IFWA_BWIDGE_CFM_UNSPEC]		= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_CFM_MEP_CWEATE]		=
				NWA_POWICY_NESTED(bw_cfm_mep_cweate_powicy),
	[IFWA_BWIDGE_CFM_MEP_DEWETE]		=
				NWA_POWICY_NESTED(bw_cfm_mep_dewete_powicy),
	[IFWA_BWIDGE_CFM_MEP_CONFIG]		=
				NWA_POWICY_NESTED(bw_cfm_mep_config_powicy),
	[IFWA_BWIDGE_CFM_CC_CONFIG]		=
				NWA_POWICY_NESTED(bw_cfm_cc_config_powicy),
	[IFWA_BWIDGE_CFM_CC_PEEW_MEP_ADD]	=
				NWA_POWICY_NESTED(bw_cfm_cc_peew_mep_powicy),
	[IFWA_BWIDGE_CFM_CC_PEEW_MEP_WEMOVE]	=
				NWA_POWICY_NESTED(bw_cfm_cc_peew_mep_powicy),
	[IFWA_BWIDGE_CFM_CC_WDI]		=
				NWA_POWICY_NESTED(bw_cfm_cc_wdi_powicy),
	[IFWA_BWIDGE_CFM_CC_CCM_TX]		=
				NWA_POWICY_NESTED(bw_cfm_cc_ccm_tx_powicy),
};

static int bw_mep_cweate_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_MEP_CWEATE_MAX + 1];
	stwuct bw_cfm_mep_cweate cweate;
	u32 instance;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_MEP_CWEATE_MAX, attw,
			       bw_cfm_mep_cweate_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_MEP_CWEATE_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_MEP_CWEATE_DOMAIN]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing DOMAIN attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_MEP_CWEATE_DIWECTION]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing DIWECTION attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_MEP_CWEATE_IFINDEX]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing IFINDEX attwibute");
		wetuwn -EINVAW;
	}

	memset(&cweate, 0, sizeof(cweate));

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CWEATE_INSTANCE]);
	cweate.domain = nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CWEATE_DOMAIN]);
	cweate.diwection = nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CWEATE_DIWECTION]);
	cweate.ifindex = nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CWEATE_IFINDEX]);

	wetuwn bw_cfm_mep_cweate(bw, instance, &cweate, extack);
}

static int bw_mep_dewete_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_MEP_DEWETE_MAX + 1];
	u32 instance;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_MEP_DEWETE_MAX, attw,
			       bw_cfm_mep_dewete_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_MEP_DEWETE_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_DEWETE_INSTANCE]);

	wetuwn bw_cfm_mep_dewete(bw, instance, extack);
}

static int bw_mep_config_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_MEP_CONFIG_MAX + 1];
	stwuct bw_cfm_mep_config config;
	u32 instance;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_MEP_CONFIG_MAX, attw,
			       bw_cfm_mep_config_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_MEP_CONFIG_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_MEP_CONFIG_UNICAST_MAC]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing UNICAST_MAC attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_MEP_CONFIG_MDWEVEW]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing MDWEVEW attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_MEP_CONFIG_MEPID]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing MEPID attwibute");
		wetuwn -EINVAW;
	}

	memset(&config, 0, sizeof(config));

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CONFIG_INSTANCE]);
	nwa_memcpy(&config.unicast_mac.addw,
		   tb[IFWA_BWIDGE_CFM_MEP_CONFIG_UNICAST_MAC],
		   sizeof(config.unicast_mac.addw));
	config.mdwevew = nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CONFIG_MDWEVEW]);
	config.mepid = nwa_get_u32(tb[IFWA_BWIDGE_CFM_MEP_CONFIG_MEPID]);

	wetuwn bw_cfm_mep_config_set(bw, instance, &config, extack);
}

static int bw_cc_config_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_CC_CONFIG_MAX + 1];
	stwuct bw_cfm_cc_config config;
	u32 instance;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_CC_CONFIG_MAX, attw,
			       bw_cfm_cc_config_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_CC_CONFIG_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CONFIG_ENABWE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing ENABWE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CONFIG_EXP_INTEWVAW]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INTEWVAW attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CONFIG_EXP_MAID]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing MAID attwibute");
		wetuwn -EINVAW;
	}

	memset(&config, 0, sizeof(config));

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CONFIG_INSTANCE]);
	config.enabwe = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CONFIG_ENABWE]);
	config.exp_intewvaw = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CONFIG_EXP_INTEWVAW]);
	nwa_memcpy(&config.exp_maid.data, tb[IFWA_BWIDGE_CFM_CC_CONFIG_EXP_MAID],
		   sizeof(config.exp_maid.data));

	wetuwn bw_cfm_cc_config_set(bw, instance, &config, extack);
}

static int bw_cc_peew_mep_add_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_MAX + 1];
	u32 instance, peew_mep_id;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_CC_PEEW_MEP_MAX, attw,
			       bw_cfm_cc_peew_mep_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_PEEW_MEPID]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing PEEW_MEP_ID attwibute");
		wetuwn -EINVAW;
	}

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_INSTANCE]);
	peew_mep_id =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_PEEW_MEPID]);

	wetuwn bw_cfm_cc_peew_mep_add(bw, instance, peew_mep_id, extack);
}

static int bw_cc_peew_mep_wemove_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_MAX + 1];
	u32 instance, peew_mep_id;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_CC_PEEW_MEP_MAX, attw,
			       bw_cfm_cc_peew_mep_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_PEEW_MEPID]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing PEEW_MEP_ID attwibute");
		wetuwn -EINVAW;
	}

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_INSTANCE]);
	peew_mep_id =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_PEEW_MEPID]);

	wetuwn bw_cfm_cc_peew_mep_wemove(bw, instance, peew_mep_id, extack);
}

static int bw_cc_wdi_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
			   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_CC_WDI_MAX + 1];
	u32 instance, wdi;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_CC_WDI_MAX, attw,
			       bw_cfm_cc_wdi_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_CC_WDI_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_WDI_WDI]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing WDI attwibute");
		wetuwn -EINVAW;
	}

	instance =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_WDI_INSTANCE]);
	wdi =  nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_WDI_WDI]);

	wetuwn bw_cfm_cc_wdi_set(bw, instance, wdi, extack);
}

static int bw_cc_ccm_tx_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_CC_CCM_TX_MAX + 1];
	stwuct bw_cfm_cc_ccm_tx_info tx_info;
	u32 instance;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_CC_CCM_TX_MAX, attw,
			       bw_cfm_cc_ccm_tx_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_INSTANCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing INSTANCE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_DMAC]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing DMAC attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing SEQ_NO_UPDATE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_PEWIOD]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing PEWIOD attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing IF_TWV attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV_VAWUE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing IF_TWV_VAWUE attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing POWT_TWV attwibute");
		wetuwn -EINVAW;
	}
	if (!tb[IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV_VAWUE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing POWT_TWV_VAWUE attwibute");
		wetuwn -EINVAW;
	}

	memset(&tx_info, 0, sizeof(tx_info));

	instance = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_INSTANCE]);
	nwa_memcpy(&tx_info.dmac.addw,
		   tb[IFWA_BWIDGE_CFM_CC_CCM_TX_DMAC],
		   sizeof(tx_info.dmac.addw));
	tx_info.seq_no_update = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE]);
	tx_info.pewiod = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_PEWIOD]);
	tx_info.if_twv = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV]);
	tx_info.if_twv_vawue = nwa_get_u8(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV_VAWUE]);
	tx_info.powt_twv = nwa_get_u32(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV]);
	tx_info.powt_twv_vawue = nwa_get_u8(tb[IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV_VAWUE]);

	wetuwn bw_cfm_cc_ccm_tx(bw, instance, &tx_info, extack);
}

int bw_cfm_pawse(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
		 stwuct nwattw *attw, int cmd, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_CFM_MAX + 1];
	int eww;

	/* When this function is cawwed fow a powt then the bw pointew is
	 * invawid, thewefow set the bw to point cowwectwy
	 */
	if (p)
		bw = p->bw;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_CFM_MAX, attw,
			       bw_cfm_powicy, extack);
	if (eww)
		wetuwn eww;

	if (tb[IFWA_BWIDGE_CFM_MEP_CWEATE]) {
		eww = bw_mep_cweate_pawse(bw, tb[IFWA_BWIDGE_CFM_MEP_CWEATE],
					  extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_MEP_DEWETE]) {
		eww = bw_mep_dewete_pawse(bw, tb[IFWA_BWIDGE_CFM_MEP_DEWETE],
					  extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_MEP_CONFIG]) {
		eww = bw_mep_config_pawse(bw, tb[IFWA_BWIDGE_CFM_MEP_CONFIG],
					  extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_CC_CONFIG]) {
		eww = bw_cc_config_pawse(bw, tb[IFWA_BWIDGE_CFM_CC_CONFIG],
					 extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_ADD]) {
		eww = bw_cc_peew_mep_add_pawse(bw, tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_ADD],
					       extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_WEMOVE]) {
		eww = bw_cc_peew_mep_wemove_pawse(bw, tb[IFWA_BWIDGE_CFM_CC_PEEW_MEP_WEMOVE],
						  extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_CC_WDI]) {
		eww = bw_cc_wdi_pawse(bw, tb[IFWA_BWIDGE_CFM_CC_WDI],
				      extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_CFM_CC_CCM_TX]) {
		eww = bw_cc_ccm_tx_pawse(bw, tb[IFWA_BWIDGE_CFM_CC_CCM_TX],
					 extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int bw_cfm_config_fiww_info(stwuct sk_buff *skb, stwuct net_bwidge *bw)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct bw_cfm_mep *mep;
	stwuct nwattw *tb;

	hwist_fow_each_entwy_wcu(mep, &bw->mep_wist, head) {
		tb = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM_MEP_CWEATE_INFO);
		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CWEATE_INSTANCE,
				mep->instance))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CWEATE_DOMAIN,
				mep->cweate.domain))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CWEATE_DIWECTION,
				mep->cweate.diwection))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CWEATE_IFINDEX,
				mep->cweate.ifindex))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, tb);

		tb = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM_MEP_CONFIG_INFO);

		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CONFIG_INSTANCE,
				mep->instance))
			goto nwa_put_faiwuwe;

		if (nwa_put(skb, IFWA_BWIDGE_CFM_MEP_CONFIG_UNICAST_MAC,
			    sizeof(mep->config.unicast_mac.addw),
			    mep->config.unicast_mac.addw))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CONFIG_MDWEVEW,
				mep->config.mdwevew))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_CONFIG_MEPID,
				mep->config.mepid))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, tb);

		tb = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM_CC_CONFIG_INFO);

		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CONFIG_INSTANCE,
				mep->instance))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CONFIG_ENABWE,
				mep->cc_config.enabwe))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CONFIG_EXP_INTEWVAW,
				mep->cc_config.exp_intewvaw))
			goto nwa_put_faiwuwe;

		if (nwa_put(skb, IFWA_BWIDGE_CFM_CC_CONFIG_EXP_MAID,
			    sizeof(mep->cc_config.exp_maid.data),
			    mep->cc_config.exp_maid.data))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, tb);

		tb = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM_CC_WDI_INFO);

		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_WDI_INSTANCE,
				mep->instance))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_WDI_WDI,
				mep->wdi))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, tb);

		tb = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_INFO);

		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_INSTANCE,
				mep->instance))
			goto nwa_put_faiwuwe;

		if (nwa_put(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_DMAC,
			    sizeof(mep->cc_ccm_tx_info.dmac),
			    mep->cc_ccm_tx_info.dmac.addw))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE,
				mep->cc_ccm_tx_info.seq_no_update))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_PEWIOD,
				mep->cc_ccm_tx_info.pewiod))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV,
				mep->cc_ccm_tx_info.if_twv))
			goto nwa_put_faiwuwe;

		if (nwa_put_u8(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_IF_TWV_VAWUE,
			       mep->cc_ccm_tx_info.if_twv_vawue))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV,
				mep->cc_ccm_tx_info.powt_twv))
			goto nwa_put_faiwuwe;

		if (nwa_put_u8(skb, IFWA_BWIDGE_CFM_CC_CCM_TX_POWT_TWV_VAWUE,
			       mep->cc_ccm_tx_info.powt_twv_vawue))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, tb);

		hwist_fow_each_entwy_wcu(peew_mep, &mep->peew_mep_wist, head) {
			tb = nwa_nest_stawt(skb,
					    IFWA_BWIDGE_CFM_CC_PEEW_MEP_INFO);

			if (!tb)
				goto nwa_info_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_MEP_INSTANCE,
					mep->instance))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_PEEW_MEPID,
					peew_mep->mepid))
				goto nwa_put_faiwuwe;

			nwa_nest_end(skb, tb);
		}
	}

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, tb);

nwa_info_faiwuwe:
	wetuwn -EMSGSIZE;
}

int bw_cfm_status_fiww_info(stwuct sk_buff *skb,
			    stwuct net_bwidge *bw,
			    boow getwink)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct bw_cfm_mep *mep;
	stwuct nwattw *tb;

	hwist_fow_each_entwy_wcu(mep, &bw->mep_wist, head) {
		tb = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM_MEP_STATUS_INFO);
		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_MEP_STATUS_INSTANCE,
				mep->instance))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb,
				IFWA_BWIDGE_CFM_MEP_STATUS_OPCODE_UNEXP_SEEN,
				mep->status.opcode_unexp_seen))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb,
				IFWA_BWIDGE_CFM_MEP_STATUS_VEWSION_UNEXP_SEEN,
				mep->status.vewsion_unexp_seen))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb,
				IFWA_BWIDGE_CFM_MEP_STATUS_WX_WEVEW_WOW_SEEN,
				mep->status.wx_wevew_wow_seen))
			goto nwa_put_faiwuwe;

		/* Onwy cweaw if this is a GETWINK */
		if (getwink) {
			/* Cweaw aww 'seen' indications */
			mep->status.opcode_unexp_seen = fawse;
			mep->status.vewsion_unexp_seen = fawse;
			mep->status.wx_wevew_wow_seen = fawse;
		}

		nwa_nest_end(skb, tb);

		hwist_fow_each_entwy_wcu(peew_mep, &mep->peew_mep_wist, head) {
			tb = nwa_nest_stawt(skb,
					    IFWA_BWIDGE_CFM_CC_PEEW_STATUS_INFO);
			if (!tb)
				goto nwa_info_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_STATUS_INSTANCE,
					mep->instance))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_STATUS_PEEW_MEPID,
					peew_mep->mepid))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_STATUS_CCM_DEFECT,
					peew_mep->cc_status.ccm_defect))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb, IFWA_BWIDGE_CFM_CC_PEEW_STATUS_WDI,
					peew_mep->cc_status.wdi))
				goto nwa_put_faiwuwe;

			if (nwa_put_u8(skb,
				       IFWA_BWIDGE_CFM_CC_PEEW_STATUS_POWT_TWV_VAWUE,
				       peew_mep->cc_status.powt_twv_vawue))
				goto nwa_put_faiwuwe;

			if (nwa_put_u8(skb,
				       IFWA_BWIDGE_CFM_CC_PEEW_STATUS_IF_TWV_VAWUE,
				       peew_mep->cc_status.if_twv_vawue))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_STATUS_SEEN,
					peew_mep->cc_status.seen))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_STATUS_TWV_SEEN,
					peew_mep->cc_status.twv_seen))
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb,
					IFWA_BWIDGE_CFM_CC_PEEW_STATUS_SEQ_UNEXP_SEEN,
					peew_mep->cc_status.seq_unexp_seen))
				goto nwa_put_faiwuwe;

			if (getwink) { /* Onwy cweaw if this is a GETWINK */
				/* Cweaw aww 'seen' indications */
				peew_mep->cc_status.seen = fawse;
				peew_mep->cc_status.twv_seen = fawse;
				peew_mep->cc_status.seq_unexp_seen = fawse;
			}

			nwa_nest_end(skb, tb);
		}
	}

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, tb);

nwa_info_faiwuwe:
	wetuwn -EMSGSIZE;
}
