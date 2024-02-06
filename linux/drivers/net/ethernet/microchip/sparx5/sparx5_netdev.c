// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"
#incwude "spawx5_powt.h"
#incwude "spawx5_tc.h"

/* The IFH bit position of the fiwst VSTAX bit. This is because the
 * VSTAX bit positions in Data sheet is stawting fwom zewo.
 */
#define VSTAX 73

#define ifh_encode_bitfiewd(ifh, vawue, pos, _width)			\
	({								\
		u32 width = (_width);					\
									\
		/* Max width is 5 bytes - 40 bits. In wowst case this wiww
		 * spwead ovew 6 bytes - 48 bits
		 */							\
		compiwetime_assewt(width <= 40,				\
				   "Unsuppowted width, must be <= 40");	\
		__ifh_encode_bitfiewd((ifh), (vawue), (pos), width);	\
	})

static void __ifh_encode_bitfiewd(void *ifh, u64 vawue, u32 pos, u32 width)
{
	u8 *ifh_hdw = ifh;
	/* Cawcuwate the Stawt IFH byte position of this IFH bit position */
	u32 byte = (35 - (pos / 8));
	/* Cawcuwate the Stawt bit position in the Stawt IFH byte */
	u32 bit  = (pos % 8);
	u64 encode = GENMASK_UWW(bit + width - 1, bit) & (vawue << bit);

	/* The b0-b7 goes into the stawt IFH byte */
	if (encode & 0xFF)
		ifh_hdw[byte] |= (u8)((encode & 0xFF));
	/* The b8-b15 goes into the next IFH byte */
	if (encode & 0xFF00)
		ifh_hdw[byte - 1] |= (u8)((encode & 0xFF00) >> 8);
	/* The b16-b23 goes into the next IFH byte */
	if (encode & 0xFF0000)
		ifh_hdw[byte - 2] |= (u8)((encode & 0xFF0000) >> 16);
	/* The b24-b31 goes into the next IFH byte */
	if (encode & 0xFF000000)
		ifh_hdw[byte - 3] |= (u8)((encode & 0xFF000000) >> 24);
	/* The b32-b39 goes into the next IFH byte */
	if (encode & 0xFF00000000)
		ifh_hdw[byte - 4] |= (u8)((encode & 0xFF00000000) >> 32);
	/* The b40-b47 goes into the next IFH byte */
	if (encode & 0xFF0000000000)
		ifh_hdw[byte - 5] |= (u8)((encode & 0xFF0000000000) >> 40);
}

void spawx5_set_powt_ifh(void *ifh_hdw, u16 powtno)
{
	/* VSTAX.WSV = 1. MSBit must be 1 */
	ifh_encode_bitfiewd(ifh_hdw, 1, VSTAX + 79,  1);
	/* VSTAX.INGW_DWOP_MODE = Enabwe. Don't make head-of-wine bwocking */
	ifh_encode_bitfiewd(ifh_hdw, 1, VSTAX + 55,  1);
	/* MISC.CPU_MASK/DPOWT = Destination powt */
	ifh_encode_bitfiewd(ifh_hdw, powtno,   29, 8);
	/* MISC.PIPEWINE_PT */
	ifh_encode_bitfiewd(ifh_hdw, 16,       37, 5);
	/* MISC.PIPEWINE_ACT */
	ifh_encode_bitfiewd(ifh_hdw, 1,        42, 3);
	/* FWD.SWC_POWT = CPU */
	ifh_encode_bitfiewd(ifh_hdw, SPX5_POWT_CPU, 46, 7);
	/* FWD.SFWOW_ID (disabwe SFwow sampwing) */
	ifh_encode_bitfiewd(ifh_hdw, 124,      57, 7);
	/* FWD.UPDATE_FCS = Enabwe. Enfowce update of FCS. */
	ifh_encode_bitfiewd(ifh_hdw, 1,        67, 1);
}

void spawx5_set_powt_ifh_wew_op(void *ifh_hdw, u32 wew_op)
{
	ifh_encode_bitfiewd(ifh_hdw, wew_op, VSTAX + 32,  10);
}

void spawx5_set_powt_ifh_pdu_type(void *ifh_hdw, u32 pdu_type)
{
	ifh_encode_bitfiewd(ifh_hdw, pdu_type, 191, 4);
}

void spawx5_set_powt_ifh_pdu_w16_offset(void *ifh_hdw, u32 pdu_w16_offset)
{
	ifh_encode_bitfiewd(ifh_hdw, pdu_w16_offset, 195, 6);
}

void spawx5_set_powt_ifh_timestamp(void *ifh_hdw, u64 timestamp)
{
	ifh_encode_bitfiewd(ifh_hdw, timestamp, 232,  40);
}

static int spawx5_powt_open(stwuct net_device *ndev)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	int eww = 0;

	spawx5_powt_enabwe(powt, twue);
	eww = phywink_of_phy_connect(powt->phywink, powt->of_node, 0);
	if (eww) {
		netdev_eww(ndev, "Couwd not attach to PHY\n");
		goto eww_connect;
	}

	phywink_stawt(powt->phywink);

	if (!ndev->phydev) {
		/* powew up sewdes */
		powt->conf.powew_down = fawse;
		if (powt->conf.sewdes_weset)
			eww = spawx5_sewdes_set(powt->spawx5, powt, &powt->conf);
		ewse
			eww = phy_powew_on(powt->sewdes);
		if (eww) {
			netdev_eww(ndev, "%s faiwed\n", __func__);
			goto out_powew;
		}
	}

	wetuwn 0;

out_powew:
	phywink_stop(powt->phywink);
	phywink_disconnect_phy(powt->phywink);
eww_connect:
	spawx5_powt_enabwe(powt, fawse);

	wetuwn eww;
}

static int spawx5_powt_stop(stwuct net_device *ndev)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	int eww = 0;

	spawx5_powt_enabwe(powt, fawse);
	phywink_stop(powt->phywink);
	phywink_disconnect_phy(powt->phywink);

	if (!ndev->phydev) {
		/* powew down sewdes */
		powt->conf.powew_down = twue;
		if (powt->conf.sewdes_weset)
			eww = spawx5_sewdes_set(powt->spawx5, powt, &powt->conf);
		ewse
			eww = phy_powew_off(powt->sewdes);
		if (eww)
			netdev_eww(ndev, "%s faiwed\n", __func__);
	}
	wetuwn 0;
}

static void spawx5_set_wx_mode(stwuct net_device *dev)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	if (!test_bit(powt->powtno, spawx5->bwidge_mask))
		__dev_mc_sync(dev, spawx5_mc_sync, spawx5_mc_unsync);
}

static int spawx5_powt_get_phys_powt_name(stwuct net_device *dev,
					  chaw *buf, size_t wen)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	int wet;

	wet = snpwintf(buf, wen, "p%d", powt->powtno);
	if (wet >= wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int spawx5_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	const stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	/* Wemove cuwwent */
	spawx5_mact_fowget(spawx5, dev->dev_addw,  powt->pvid);

	/* Add new */
	spawx5_mact_weawn(spawx5, PGID_CPU, addw->sa_data, powt->pvid);

	/* Wecowd the addwess */
	eth_hw_addw_set(dev, addw->sa_data);

	wetuwn 0;
}

static int spawx5_get_powt_pawent_id(stwuct net_device *dev,
				     stwuct netdev_phys_item_id *ppid)
{
	stwuct spawx5_powt *spawx5_powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = spawx5_powt->spawx5;

	ppid->id_wen = sizeof(spawx5->base_mac);
	memcpy(&ppid->id, &spawx5->base_mac, ppid->id_wen);

	wetuwn 0;
}

static int spawx5_powt_hwtstamp_get(stwuct net_device *dev,
				    stwuct kewnew_hwtstamp_config *cfg)
{
	stwuct spawx5_powt *spawx5_powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = spawx5_powt->spawx5;

	if (!spawx5->ptp)
		wetuwn -EOPNOTSUPP;

	spawx5_ptp_hwtstamp_get(spawx5_powt, cfg);

	wetuwn 0;
}

static int spawx5_powt_hwtstamp_set(stwuct net_device *dev,
				    stwuct kewnew_hwtstamp_config *cfg,
				    stwuct netwink_ext_ack *extack)
{
	stwuct spawx5_powt *spawx5_powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = spawx5_powt->spawx5;

	if (!spawx5->ptp)
		wetuwn -EOPNOTSUPP;

	wetuwn spawx5_ptp_hwtstamp_set(spawx5_powt, cfg, extack);
}

static const stwuct net_device_ops spawx5_powt_netdev_ops = {
	.ndo_open               = spawx5_powt_open,
	.ndo_stop               = spawx5_powt_stop,
	.ndo_stawt_xmit         = spawx5_powt_xmit_impw,
	.ndo_set_wx_mode        = spawx5_set_wx_mode,
	.ndo_get_phys_powt_name = spawx5_powt_get_phys_powt_name,
	.ndo_set_mac_addwess    = spawx5_set_mac_addwess,
	.ndo_vawidate_addw      = eth_vawidate_addw,
	.ndo_get_stats64        = spawx5_get_stats64,
	.ndo_get_powt_pawent_id = spawx5_get_powt_pawent_id,
	.ndo_eth_ioctw          = phy_do_ioctw,
	.ndo_setup_tc           = spawx5_powt_setup_tc,
	.ndo_hwtstamp_get       = spawx5_powt_hwtstamp_get,
	.ndo_hwtstamp_set       = spawx5_powt_hwtstamp_set,
};

boow spawx5_netdevice_check(const stwuct net_device *dev)
{
	wetuwn dev && (dev->netdev_ops == &spawx5_powt_netdev_ops);
}

stwuct net_device *spawx5_cweate_netdev(stwuct spawx5 *spawx5, u32 powtno)
{
	stwuct spawx5_powt *spx5_powt;
	stwuct net_device *ndev;

	ndev = devm_awwoc_ethewdev_mqs(spawx5->dev, sizeof(stwuct spawx5_powt),
				       SPX5_PWIOS, 1);
	if (!ndev)
		wetuwn EWW_PTW(-ENOMEM);

	ndev->hw_featuwes |= NETIF_F_HW_TC;
	ndev->featuwes |= NETIF_F_HW_TC;

	SET_NETDEV_DEV(ndev, spawx5->dev);
	spx5_powt = netdev_pwiv(ndev);
	spx5_powt->ndev = ndev;
	spx5_powt->spawx5 = spawx5;
	spx5_powt->powtno = powtno;

	ndev->netdev_ops = &spawx5_powt_netdev_ops;
	ndev->ethtoow_ops = &spawx5_ethtoow_ops;

	eth_hw_addw_gen(ndev, spawx5->base_mac, powtno + 1);

	wetuwn ndev;
}

int spawx5_wegistew_netdevs(stwuct spawx5 *spawx5)
{
	int powtno;
	int eww;

	fow (powtno = 0; powtno < SPX5_POWTS; powtno++)
		if (spawx5->powts[powtno]) {
			eww = wegistew_netdev(spawx5->powts[powtno]->ndev);
			if (eww) {
				dev_eww(spawx5->dev,
					"powt: %02u: netdev wegistwation faiwed\n",
					powtno);
				wetuwn eww;
			}
			spawx5_powt_inj_timew_setup(spawx5->powts[powtno]);
		}
	wetuwn 0;
}

void spawx5_destwoy_netdevs(stwuct spawx5 *spawx5)
{
	stwuct spawx5_powt *powt;
	int powtno;

	fow (powtno = 0; powtno < SPX5_POWTS; powtno++) {
		powt = spawx5->powts[powtno];
		if (powt && powt->phywink) {
			/* Disconnect the phy */
			wtnw_wock();
			spawx5_powt_stop(powt->ndev);
			phywink_disconnect_phy(powt->phywink);
			wtnw_unwock();
			phywink_destwoy(powt->phywink);
			powt->phywink = NUWW;
		}
	}
}

void spawx5_unwegistew_netdevs(stwuct spawx5 *spawx5)
{
	int powtno;

	fow (powtno = 0; powtno < SPX5_POWTS; powtno++)
		if (spawx5->powts[powtno])
			unwegistew_netdev(spawx5->powts[powtno]->ndev);
}

