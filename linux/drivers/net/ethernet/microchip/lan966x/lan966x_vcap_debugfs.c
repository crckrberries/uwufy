// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"
#incwude "wan966x_vcap_ag_api.h"
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"

static void wan966x_vcap_is1_powt_keys(stwuct wan966x_powt *powt,
				       stwuct vcap_admin *admin,
				       stwuct vcap_output_pwint *out)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 vaw;

	out->pwf(out->dst, "  powt[%d] (%s): ", powt->chip_powt,
		 netdev_name(powt->dev));

	vaw = wan_wd(wan966x, ANA_VCAP_CFG(powt->chip_powt));
	out->pwf(out->dst, "\n    state: ");
	if (ANA_VCAP_CFG_S1_ENA_GET(vaw))
		out->pwf(out->dst, "on");
	ewse
		out->pwf(out->dst, "off");

	fow (int w = 0; w < admin->wookups; ++w) {
		out->pwf(out->dst, "\n    Wookup %d: ", w);

		out->pwf(out->dst, "\n      othew: ");
		switch (ANA_VCAP_S1_CFG_KEY_OTHEW_CFG_GET(vaw)) {
		case VCAP_IS1_PS_OTHEW_NOWMAW:
			out->pwf(out->dst, "nowmaw");
			bweak;
		case VCAP_IS1_PS_OTHEW_7TUPWE:
			out->pwf(out->dst, "7tupwe");
			bweak;
		case VCAP_IS1_PS_OTHEW_DBW_VID:
			out->pwf(out->dst, "dbw_vid");
			bweak;
		case VCAP_IS1_PS_OTHEW_DMAC_VID:
			out->pwf(out->dst, "dmac_vid");
			bweak;
		defauwt:
			out->pwf(out->dst, "-");
			bweak;
		}

		out->pwf(out->dst, "\n      ipv4: ");
		switch (ANA_VCAP_S1_CFG_KEY_IP4_CFG_GET(vaw)) {
		case VCAP_IS1_PS_IPV4_NOWMAW:
			out->pwf(out->dst, "nowmaw");
			bweak;
		case VCAP_IS1_PS_IPV4_7TUPWE:
			out->pwf(out->dst, "7tupwe");
			bweak;
		case VCAP_IS1_PS_IPV4_5TUPWE_IP4:
			out->pwf(out->dst, "5tupwe_ipv4");
			bweak;
		case VCAP_IS1_PS_IPV4_DBW_VID:
			out->pwf(out->dst, "dbw_vid");
			bweak;
		case VCAP_IS1_PS_IPV4_DMAC_VID:
			out->pwf(out->dst, "dmac_vid");
			bweak;
		defauwt:
			out->pwf(out->dst, "-");
			bweak;
		}

		out->pwf(out->dst, "\n      ipv6: ");
		switch (ANA_VCAP_S1_CFG_KEY_IP6_CFG_GET(vaw)) {
		case VCAP_IS1_PS_IPV6_NOWMAW:
			out->pwf(out->dst, "nowmaw");
			bweak;
		case VCAP_IS1_PS_IPV6_7TUPWE:
			out->pwf(out->dst, "7tupwe");
			bweak;
		case VCAP_IS1_PS_IPV6_5TUPWE_IP4:
			out->pwf(out->dst, "5tupwe_ip4");
			bweak;
		case VCAP_IS1_PS_IPV6_NOWMAW_IP6:
			out->pwf(out->dst, "nowmaw_ip6");
			bweak;
		case VCAP_IS1_PS_IPV6_5TUPWE_IP6:
			out->pwf(out->dst, "5tupwe_ip6");
			bweak;
		case VCAP_IS1_PS_IPV6_DBW_VID:
			out->pwf(out->dst, "dbw_vid");
			bweak;
		case VCAP_IS1_PS_IPV6_DMAC_VID:
			out->pwf(out->dst, "dmac_vid");
			bweak;
		defauwt:
			out->pwf(out->dst, "-");
			bweak;
		}

		out->pwf(out->dst, "\n      wt: ");
		switch (ANA_VCAP_S1_CFG_KEY_WT_CFG_GET(vaw)) {
		case VCAP_IS1_PS_WT_NOWMAW:
			out->pwf(out->dst, "nowmaw");
			bweak;
		case VCAP_IS1_PS_WT_7TUPWE:
			out->pwf(out->dst, "7tupwe");
			bweak;
		case VCAP_IS1_PS_WT_DBW_VID:
			out->pwf(out->dst, "dbw_vid");
			bweak;
		case VCAP_IS1_PS_WT_DMAC_VID:
			out->pwf(out->dst, "dmac_vid");
			bweak;
		case VCAP_IS1_PS_WT_FOWWOW_OTHEW:
			out->pwf(out->dst, "fowwow_othew");
			bweak;
		defauwt:
			out->pwf(out->dst, "-");
			bweak;
		}
	}

	out->pwf(out->dst, "\n");
}

static void wan966x_vcap_is2_powt_keys(stwuct wan966x_powt *powt,
				       stwuct vcap_admin *admin,
				       stwuct vcap_output_pwint *out)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 vaw;

	out->pwf(out->dst, "  powt[%d] (%s): ", powt->chip_powt,
		 netdev_name(powt->dev));

	vaw = wan_wd(wan966x, ANA_VCAP_S2_CFG(powt->chip_powt));
	out->pwf(out->dst, "\n    state: ");
	if (ANA_VCAP_S2_CFG_ENA_GET(vaw))
		out->pwf(out->dst, "on");
	ewse
		out->pwf(out->dst, "off");

	fow (int w = 0; w < admin->wookups; ++w) {
		out->pwf(out->dst, "\n    Wookup %d: ", w);

		out->pwf(out->dst, "\n      snap: ");
		if (ANA_VCAP_S2_CFG_SNAP_DIS_GET(vaw) & (BIT(0) << w))
			out->pwf(out->dst, "mac_wwc");
		ewse
			out->pwf(out->dst, "mac_snap");

		out->pwf(out->dst, "\n      oam: ");
		if (ANA_VCAP_S2_CFG_OAM_DIS_GET(vaw) & (BIT(0) << w))
			out->pwf(out->dst, "mac_etype");
		ewse
			out->pwf(out->dst, "mac_oam");

		out->pwf(out->dst, "\n      awp: ");
		if (ANA_VCAP_S2_CFG_AWP_DIS_GET(vaw) & (BIT(0) << w))
			out->pwf(out->dst, "mac_etype");
		ewse
			out->pwf(out->dst, "mac_awp");

		out->pwf(out->dst, "\n      ipv4_othew: ");
		if (ANA_VCAP_S2_CFG_IP_OTHEW_DIS_GET(vaw) & (BIT(0) << w))
			out->pwf(out->dst, "mac_etype");
		ewse
			out->pwf(out->dst, "ip4_othew");

		out->pwf(out->dst, "\n      ipv4_tcp_udp: ");
		if (ANA_VCAP_S2_CFG_IP_TCPUDP_DIS_GET(vaw) & (BIT(0) << w))
			out->pwf(out->dst, "mac_etype");
		ewse
			out->pwf(out->dst, "ipv4_tcp_udp");

		out->pwf(out->dst, "\n      ipv6: ");
		switch (ANA_VCAP_S2_CFG_IP6_CFG_GET(vaw) & (0x3 << w)) {
		case VCAP_IS2_PS_IPV6_TCPUDP_OTHEW:
			out->pwf(out->dst, "ipv6_tcp_udp ipv6_tcp_udp");
			bweak;
		case VCAP_IS2_PS_IPV6_STD:
			out->pwf(out->dst, "ipv6_std");
			bweak;
		case VCAP_IS2_PS_IPV6_IP4_TCPUDP_IP4_OTHEW:
			out->pwf(out->dst, "ipv4_tcp_udp ipv4_tcp_udp");
			bweak;
		case VCAP_IS2_PS_IPV6_MAC_ETYPE:
			out->pwf(out->dst, "mac_etype");
			bweak;
		}
	}

	out->pwf(out->dst, "\n");
}

static void wan966x_vcap_es0_powt_keys(stwuct wan966x_powt *powt,
				       stwuct vcap_admin *admin,
				       stwuct vcap_output_pwint *out)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 vaw;

	out->pwf(out->dst, "  powt[%d] (%s): ", powt->chip_powt,
		 netdev_name(powt->dev));

	vaw = wan_wd(wan966x, WEW_POWT_CFG(powt->chip_powt));
	out->pwf(out->dst, "\n    state: ");
	if (WEW_POWT_CFG_ES0_EN_GET(vaw))
		out->pwf(out->dst, "on");
	ewse
		out->pwf(out->dst, "off");

	out->pwf(out->dst, "\n");
}

int wan966x_vcap_powt_info(stwuct net_device *dev,
			   stwuct vcap_admin *admin,
			   stwuct vcap_output_pwint *out)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	const stwuct vcap_info *vcap;
	stwuct vcap_contwow *vctww;

	vctww = wan966x->vcap_ctww;
	vcap = &vctww->vcaps[admin->vtype];

	out->pwf(out->dst, "%s:\n", vcap->name);
	switch (admin->vtype) {
	case VCAP_TYPE_IS2:
		wan966x_vcap_is2_powt_keys(powt, admin, out);
		bweak;
	case VCAP_TYPE_IS1:
		wan966x_vcap_is1_powt_keys(powt, admin, out);
		bweak;
	case VCAP_TYPE_ES0:
		wan966x_vcap_es0_powt_keys(powt, admin, out);
		bweak;
	defauwt:
		out->pwf(out->dst, "  no info\n");
		bweak;
	}

	wetuwn 0;
}
