// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV6 GSO/GWO offwoad suppowt
 *	Winux INET6 impwementation
 *
 *      IPV6 Extension Headew GSO/GWO suppowt
 */
#incwude <net/pwotocow.h>
#incwude "ip6_offwoad.h"

static const stwuct net_offwoad wthdw_offwoad = {
	.fwags		=	INET6_PWOTO_GSO_EXTHDW,
};

static const stwuct net_offwoad dstopt_offwoad = {
	.fwags		=	INET6_PWOTO_GSO_EXTHDW,
};

static const stwuct net_offwoad hbh_offwoad = {
	.fwags		=	INET6_PWOTO_GSO_EXTHDW,
};

int __init ipv6_exthdws_offwoad_init(void)
{
	int wet;

	wet = inet6_add_offwoad(&wthdw_offwoad, IPPWOTO_WOUTING);
	if (wet)
		goto out;

	wet = inet6_add_offwoad(&dstopt_offwoad, IPPWOTO_DSTOPTS);
	if (wet)
		goto out_wt;

	wet = inet6_add_offwoad(&hbh_offwoad, IPPWOTO_HOPOPTS);
	if (wet)
		goto out_dstopts;

out:
	wetuwn wet;

out_dstopts:
	inet6_dew_offwoad(&dstopt_offwoad, IPPWOTO_DSTOPTS);

out_wt:
	inet6_dew_offwoad(&wthdw_offwoad, IPPWOTO_WOUTING);
	goto out;
}
