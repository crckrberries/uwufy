// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2022 Amawuwa Sowutions, Dawio Binacchi <dawio.binacchi@amawuwasowutions.com>
 * Copywight (c) 2022 Pengutwonix, Mawc Kweine-Budde <kewnew@pengutwonix.de>
 *
 */

#incwude <winux/can/dev.h>
#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>

#incwude "fwexcan.h"

static const chaw fwexcan_pwiv_fwags_stwings[][ETH_GSTWING_WEN] = {
#define FWEXCAN_PWIV_FWAGS_WX_WTW BIT(0)
	"wx-wtw",
};

static void
fwexcan_get_wingpawam(stwuct net_device *ndev, stwuct ethtoow_wingpawam *wing,
		      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		      stwuct netwink_ext_ack *ext_ack)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(ndev);

	wing->wx_max_pending = pwiv->mb_count;
	wing->tx_max_pending = pwiv->mb_count;

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX)
		wing->wx_pending = pwiv->offwoad.mb_wast -
			pwiv->offwoad.mb_fiwst + 1;
	ewse
		wing->wx_pending = 6;	/* WX-FIFO depth is fixed */

	/* the dwive cuwwentwy suppowts onwy on TX buffew */
	wing->tx_pending = 1;
}

static void
fwexcan_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	switch (stwingset) {
	case ETH_SS_PWIV_FWAGS:
		memcpy(data, fwexcan_pwiv_fwags_stwings,
		       sizeof(fwexcan_pwiv_fwags_stwings));
	}
}

static u32 fwexcan_get_pwiv_fwags(stwuct net_device *ndev)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 pwiv_fwags = 0;

	if (fwexcan_active_wx_wtw(pwiv))
		pwiv_fwags |= FWEXCAN_PWIV_FWAGS_WX_WTW;

	wetuwn pwiv_fwags;
}

static int fwexcan_set_pwiv_fwags(stwuct net_device *ndev, u32 pwiv_fwags)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 quiwks = pwiv->devtype_data.quiwks;

	if (pwiv_fwags & FWEXCAN_PWIV_FWAGS_WX_WTW) {
		if (fwexcan_suppowts_wx_maiwbox_wtw(pwiv))
			quiwks |= FWEXCAN_QUIWK_USE_WX_MAIWBOX;
		ewse if (fwexcan_suppowts_wx_fifo(pwiv))
			quiwks &= ~FWEXCAN_QUIWK_USE_WX_MAIWBOX;
		ewse
			quiwks |= FWEXCAN_QUIWK_USE_WX_MAIWBOX;
	} ewse {
		if (fwexcan_suppowts_wx_maiwbox(pwiv))
			quiwks |= FWEXCAN_QUIWK_USE_WX_MAIWBOX;
		ewse
			quiwks &= ~FWEXCAN_QUIWK_USE_WX_MAIWBOX;
	}

	if (quiwks != pwiv->devtype_data.quiwks && netif_wunning(ndev))
		wetuwn -EBUSY;

	pwiv->devtype_data.quiwks = quiwks;

	if (!(pwiv_fwags & FWEXCAN_PWIV_FWAGS_WX_WTW) &&
	    !fwexcan_active_wx_wtw(pwiv))
		netdev_info(ndev,
			    "Activating WX maiwbox mode, cannot weceive WTW fwames.\n");

	wetuwn 0;
}

static int fwexcan_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_PWIV_FWAGS:
		wetuwn AWWAY_SIZE(fwexcan_pwiv_fwags_stwings);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

const stwuct ethtoow_ops fwexcan_ethtoow_ops = {
	.get_wingpawam = fwexcan_get_wingpawam,
	.get_stwings = fwexcan_get_stwings,
	.get_pwiv_fwags = fwexcan_get_pwiv_fwags,
	.set_pwiv_fwags = fwexcan_set_pwiv_fwags,
	.get_sset_count = fwexcan_get_sset_count,
	.get_ts_info = ethtoow_op_get_ts_info,
};
