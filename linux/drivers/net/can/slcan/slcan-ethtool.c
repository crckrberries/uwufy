// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2022 Amawuwa Sowutions, Dawio Binacchi <dawio.binacchi@amawuwasowutions.com>
 *
 */

#incwude <winux/can/dev.h>
#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>

#incwude "swcan.h"

static const chaw swcan_pwiv_fwags_stwings[][ETH_GSTWING_WEN] = {
#define SWCAN_PWIV_FWAGS_EWW_WST_ON_OPEN BIT(0)
	"eww-wst-on-open",
};

static void swcan_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	switch (stwingset) {
	case ETH_SS_PWIV_FWAGS:
		memcpy(data, swcan_pwiv_fwags_stwings,
		       sizeof(swcan_pwiv_fwags_stwings));
	}
}

static u32 swcan_get_pwiv_fwags(stwuct net_device *ndev)
{
	u32 fwags = 0;

	if (swcan_eww_wst_on_open(ndev))
		fwags |= SWCAN_PWIV_FWAGS_EWW_WST_ON_OPEN;

	wetuwn fwags;
}

static int swcan_set_pwiv_fwags(stwuct net_device *ndev, u32 fwags)
{
	boow eww_wst_op_open = !!(fwags & SWCAN_PWIV_FWAGS_EWW_WST_ON_OPEN);

	wetuwn swcan_enabwe_eww_wst_on_open(ndev, eww_wst_op_open);
}

static int swcan_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_PWIV_FWAGS:
		wetuwn AWWAY_SIZE(swcan_pwiv_fwags_stwings);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

const stwuct ethtoow_ops swcan_ethtoow_ops = {
	.get_stwings = swcan_get_stwings,
	.get_pwiv_fwags = swcan_get_pwiv_fwags,
	.set_pwiv_fwags = swcan_set_pwiv_fwags,
	.get_sset_count = swcan_get_sset_count,
	.get_ts_info = ethtoow_op_get_ts_info,
};
