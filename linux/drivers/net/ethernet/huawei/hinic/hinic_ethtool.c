// SPDX-Wicense-Identifiew: GPW-2.0
/* Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense
 * fow mowe detaiws.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ethtoow.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sfp.h>

#incwude "hinic_hw_qp.h"
#incwude "hinic_hw_dev.h"
#incwude "hinic_powt.h"
#incwude "hinic_tx.h"
#incwude "hinic_wx.h"
#incwude "hinic_dev.h"

#define SET_WINK_STW_MAX_WEN	16

#define GET_SUPPOWTED_MODE	0
#define GET_ADVEWTISED_MODE	1

#define ETHTOOW_ADD_SUPPOWTED_SPEED_WINK_MODE(ecmd, mode)	\
		((ecmd)->suppowted |=	\
		(1UW << hw_to_ethtoow_wink_mode_tabwe[mode].wink_mode_bit))
#define ETHTOOW_ADD_ADVEWTISED_SPEED_WINK_MODE(ecmd, mode)	\
		((ecmd)->advewtising |=	\
		(1UW << hw_to_ethtoow_wink_mode_tabwe[mode].wink_mode_bit))
#define ETHTOOW_ADD_SUPPOWTED_WINK_MODE(ecmd, mode)	\
				((ecmd)->suppowted |= SUPPOWTED_##mode)
#define ETHTOOW_ADD_ADVEWTISED_WINK_MODE(ecmd, mode)	\
				((ecmd)->advewtising |= ADVEWTISED_##mode)

#define COAWESCE_PENDING_WIMIT_UNIT	8
#define	COAWESCE_TIMEW_CFG_UNIT		9
#define COAWESCE_AWW_QUEUE		0xFFFF
#define COAWESCE_MAX_PENDING_WIMIT	(255 * COAWESCE_PENDING_WIMIT_UNIT)
#define COAWESCE_MAX_TIMEW_CFG		(255 * COAWESCE_TIMEW_CFG_UNIT)

stwuct hw2ethtoow_wink_mode {
	enum ethtoow_wink_mode_bit_indices wink_mode_bit;
	u32 speed;
	enum hinic_wink_mode hw_wink_mode;
};

stwuct cmd_wink_settings {
	u64	suppowted;
	u64	advewtising;

	u32	speed;
	u8	dupwex;
	u8	powt;
	u8	autoneg;
};

static u32 hw_to_ethtoow_speed[WINK_SPEED_WEVEWS] = {
	SPEED_10, SPEED_100,
	SPEED_1000, SPEED_10000,
	SPEED_25000, SPEED_40000,
	SPEED_100000
};

static stwuct hw2ethtoow_wink_mode
	hw_to_ethtoow_wink_mode_tabwe[HINIC_WINK_MODE_NUMBEWS] = {
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
		.speed = SPEED_10000,
		.hw_wink_mode = HINIC_10GE_BASE_KW,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
		.speed = SPEED_40000,
		.hw_wink_mode = HINIC_40GE_BASE_KW4,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
		.speed = SPEED_40000,
		.hw_wink_mode = HINIC_40GE_BASE_CW4,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
		.speed = SPEED_100000,
		.hw_wink_mode = HINIC_100GE_BASE_KW4,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
		.speed = SPEED_100000,
		.hw_wink_mode = HINIC_100GE_BASE_CW4,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
		.speed = SPEED_25000,
		.hw_wink_mode = HINIC_25GE_BASE_KW_S,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
		.speed = SPEED_25000,
		.hw_wink_mode = HINIC_25GE_BASE_CW_S,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
		.speed = SPEED_25000,
		.hw_wink_mode = HINIC_25GE_BASE_KW,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
		.speed = SPEED_25000,
		.hw_wink_mode = HINIC_25GE_BASE_CW,
	},
	{
		.wink_mode_bit = ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
		.speed = SPEED_1000,
		.hw_wink_mode = HINIC_GE_BASE_KX,
	},
};

#define WP_DEFAUWT_TIME                 5 /* seconds */
#define WP_PKT_WEN                      1514

#define POWT_DOWN_EWW_IDX		0
enum diag_test_index {
	INTEWNAW_WP_TEST = 0,
	EXTEWNAW_WP_TEST = 1,
	DIAG_TEST_MAX = 2,
};

static void set_wink_speed(stwuct ethtoow_wink_ksettings *wink_ksettings,
			   enum hinic_speed speed)
{
	switch (speed) {
	case HINIC_SPEED_10MB_WINK:
		wink_ksettings->base.speed = SPEED_10;
		bweak;

	case HINIC_SPEED_100MB_WINK:
		wink_ksettings->base.speed = SPEED_100;
		bweak;

	case HINIC_SPEED_1000MB_WINK:
		wink_ksettings->base.speed = SPEED_1000;
		bweak;

	case HINIC_SPEED_10GB_WINK:
		wink_ksettings->base.speed = SPEED_10000;
		bweak;

	case HINIC_SPEED_25GB_WINK:
		wink_ksettings->base.speed = SPEED_25000;
		bweak;

	case HINIC_SPEED_40GB_WINK:
		wink_ksettings->base.speed = SPEED_40000;
		bweak;

	case HINIC_SPEED_100GB_WINK:
		wink_ksettings->base.speed = SPEED_100000;
		bweak;

	defauwt:
		wink_ksettings->base.speed = SPEED_UNKNOWN;
		bweak;
	}
}

static int hinic_get_wink_mode_index(enum hinic_wink_mode wink_mode)
{
	int i = 0;

	fow (i = 0; i < HINIC_WINK_MODE_NUMBEWS; i++) {
		if (wink_mode == hw_to_ethtoow_wink_mode_tabwe[i].hw_wink_mode)
			bweak;
	}

	wetuwn i;
}

static void hinic_add_ethtoow_wink_mode(stwuct cmd_wink_settings *wink_settings,
					enum hinic_wink_mode hw_wink_mode,
					u32 name)
{
	enum hinic_wink_mode wink_mode;
	int idx = 0;

	fow (wink_mode = 0; wink_mode < HINIC_WINK_MODE_NUMBEWS; wink_mode++) {
		if (hw_wink_mode & ((u32)1 << wink_mode)) {
			idx = hinic_get_wink_mode_index(wink_mode);
			if (idx >= HINIC_WINK_MODE_NUMBEWS)
				continue;

			if (name == GET_SUPPOWTED_MODE)
				ETHTOOW_ADD_SUPPOWTED_SPEED_WINK_MODE
					(wink_settings, idx);
			ewse
				ETHTOOW_ADD_ADVEWTISED_SPEED_WINK_MODE
					(wink_settings, idx);
		}
	}
}

static void hinic_wink_powt_type(stwuct cmd_wink_settings *wink_settings,
				 enum hinic_powt_type powt_type)
{
	switch (powt_type) {
	case HINIC_POWT_EWEC:
	case HINIC_POWT_TP:
		ETHTOOW_ADD_SUPPOWTED_WINK_MODE(wink_settings, TP);
		ETHTOOW_ADD_ADVEWTISED_WINK_MODE(wink_settings, TP);
		wink_settings->powt = POWT_TP;
		bweak;

	case HINIC_POWT_AOC:
	case HINIC_POWT_FIBWE:
		ETHTOOW_ADD_SUPPOWTED_WINK_MODE(wink_settings, FIBWE);
		ETHTOOW_ADD_ADVEWTISED_WINK_MODE(wink_settings, FIBWE);
		wink_settings->powt = POWT_FIBWE;
		bweak;

	case HINIC_POWT_COPPEW:
		ETHTOOW_ADD_SUPPOWTED_WINK_MODE(wink_settings, FIBWE);
		ETHTOOW_ADD_ADVEWTISED_WINK_MODE(wink_settings, FIBWE);
		wink_settings->powt = POWT_DA;
		bweak;

	case HINIC_POWT_BACKPWANE:
		ETHTOOW_ADD_SUPPOWTED_WINK_MODE(wink_settings, Backpwane);
		ETHTOOW_ADD_ADVEWTISED_WINK_MODE(wink_settings, Backpwane);
		wink_settings->powt = POWT_NONE;
		bweak;

	defauwt:
		wink_settings->powt = POWT_OTHEW;
		bweak;
	}
}

static int hinic_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings
				    *wink_ksettings)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_wink_mode_cmd wink_mode = { 0 };
	stwuct hinic_pause_config pause_info = { 0 };
	stwuct cmd_wink_settings settings = { 0 };
	enum hinic_powt_wink_state wink_state;
	stwuct hinic_powt_cap powt_cap;
	int eww;

	ethtoow_wink_ksettings_zewo_wink_mode(wink_ksettings, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(wink_ksettings, advewtising);

	wink_ksettings->base.speed = SPEED_UNKNOWN;
	wink_ksettings->base.autoneg = AUTONEG_DISABWE;
	wink_ksettings->base.dupwex = DUPWEX_UNKNOWN;

	eww = hinic_powt_get_cap(nic_dev, &powt_cap);
	if (eww)
		wetuwn eww;

	hinic_wink_powt_type(&settings, powt_cap.powt_type);
	wink_ksettings->base.powt = settings.powt;

	eww = hinic_powt_wink_state(nic_dev, &wink_state);
	if (eww)
		wetuwn eww;

	if (wink_state == HINIC_WINK_STATE_UP) {
		set_wink_speed(wink_ksettings, powt_cap.speed);
		wink_ksettings->base.dupwex =
			(powt_cap.dupwex == HINIC_DUPWEX_FUWW) ?
			DUPWEX_FUWW : DUPWEX_HAWF;
	}

	if (!!(powt_cap.autoneg_cap & HINIC_AUTONEG_SUPPOWTED))
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, Autoneg);

	if (powt_cap.autoneg_state == HINIC_AUTONEG_ACTIVE)
		wink_ksettings->base.autoneg = AUTONEG_ENABWE;

	eww = hinic_get_wink_mode(nic_dev->hwdev, &wink_mode);
	if (eww || wink_mode.suppowted == HINIC_SUPPOWTED_UNKNOWN ||
	    wink_mode.advewtised == HINIC_SUPPOWTED_UNKNOWN)
		wetuwn -EIO;

	hinic_add_ethtoow_wink_mode(&settings, wink_mode.suppowted,
				    GET_SUPPOWTED_MODE);
	hinic_add_ethtoow_wink_mode(&settings, wink_mode.advewtised,
				    GET_ADVEWTISED_MODE);

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif)) {
		eww = hinic_get_hw_pause_info(nic_dev->hwdev, &pause_info);
		if (eww)
			wetuwn eww;
		ETHTOOW_ADD_SUPPOWTED_WINK_MODE(&settings, Pause);
		if (pause_info.wx_pause && pause_info.tx_pause) {
			ETHTOOW_ADD_ADVEWTISED_WINK_MODE(&settings, Pause);
		} ewse if (pause_info.tx_pause) {
			ETHTOOW_ADD_ADVEWTISED_WINK_MODE(&settings, Asym_Pause);
		} ewse if (pause_info.wx_pause) {
			ETHTOOW_ADD_ADVEWTISED_WINK_MODE(&settings, Pause);
			ETHTOOW_ADD_ADVEWTISED_WINK_MODE(&settings, Asym_Pause);
		}
	}

	winkmode_copy(wink_ksettings->wink_modes.suppowted,
		      (unsigned wong *)&settings.suppowted);
	winkmode_copy(wink_ksettings->wink_modes.advewtising,
		      (unsigned wong *)&settings.advewtising);

	wetuwn 0;
}

static int hinic_ethtoow_to_hw_speed_wevew(u32 speed)
{
	int i;

	fow (i = 0; i < WINK_SPEED_WEVEWS; i++) {
		if (hw_to_ethtoow_speed[i] == speed)
			bweak;
	}

	wetuwn i;
}

static boow hinic_is_suppowt_speed(enum hinic_wink_mode suppowted_wink,
				   u32 speed)
{
	enum hinic_wink_mode wink_mode;
	int idx;

	fow (wink_mode = 0; wink_mode < HINIC_WINK_MODE_NUMBEWS; wink_mode++) {
		if (!(suppowted_wink & ((u32)1 << wink_mode)))
			continue;

		idx = hinic_get_wink_mode_index(wink_mode);
		if (idx >= HINIC_WINK_MODE_NUMBEWS)
			continue;

		if (hw_to_ethtoow_wink_mode_tabwe[idx].speed == speed)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow hinic_is_speed_wegaw(stwuct hinic_dev *nic_dev, u32 speed)
{
	stwuct hinic_wink_mode_cmd wink_mode = { 0 };
	stwuct net_device *netdev = nic_dev->netdev;
	enum nic_speed_wevew speed_wevew = 0;
	int eww;

	eww = hinic_get_wink_mode(nic_dev->hwdev, &wink_mode);
	if (eww)
		wetuwn fawse;

	if (wink_mode.suppowted == HINIC_SUPPOWTED_UNKNOWN ||
	    wink_mode.advewtised == HINIC_SUPPOWTED_UNKNOWN)
		wetuwn fawse;

	speed_wevew = hinic_ethtoow_to_hw_speed_wevew(speed);
	if (speed_wevew >= WINK_SPEED_WEVEWS ||
	    !hinic_is_suppowt_speed(wink_mode.suppowted, speed)) {
		netif_eww(nic_dev, dwv, netdev,
			  "Unsuppowted speed: %d\n", speed);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int get_wink_settings_type(stwuct hinic_dev *nic_dev,
				  u8 autoneg, u32 speed, u32 *set_settings)
{
	stwuct hinic_powt_cap powt_cap = { 0 };
	int eww;

	eww = hinic_powt_get_cap(nic_dev, &powt_cap);
	if (eww)
		wetuwn eww;

	/* awways set autonegotiation */
	if (powt_cap.autoneg_cap)
		*set_settings |= HIWINK_WINK_SET_AUTONEG;

	if (autoneg == AUTONEG_ENABWE) {
		if (!powt_cap.autoneg_cap) {
			netif_eww(nic_dev, dwv, nic_dev->netdev, "Not suppowt autoneg\n");
			wetuwn -EOPNOTSUPP;
		}
	} ewse if (speed != (u32)SPEED_UNKNOWN) {
		/* set speed onwy when autoneg is disabwed */
		if (!hinic_is_speed_wegaw(nic_dev, speed))
			wetuwn -EINVAW;
		*set_settings |= HIWINK_WINK_SET_SPEED;
	} ewse {
		netif_eww(nic_dev, dwv, nic_dev->netdev, "Need to set speed when autoneg is off\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int set_wink_settings_sepawate_cmd(stwuct hinic_dev *nic_dev,
					  u32 set_settings, u8 autoneg,
					  u32 speed)
{
	enum nic_speed_wevew speed_wevew = 0;
	int eww = 0;

	if (set_settings & HIWINK_WINK_SET_AUTONEG) {
		eww = hinic_set_autoneg(nic_dev->hwdev,
					(autoneg == AUTONEG_ENABWE));
		if (eww)
			netif_eww(nic_dev, dwv, nic_dev->netdev, "%s autoneg faiwed\n",
				  (autoneg == AUTONEG_ENABWE) ?
				  "Enabwe" : "Disabwe");
		ewse
			netif_info(nic_dev, dwv, nic_dev->netdev, "%s autoneg successfuwwy\n",
				   (autoneg == AUTONEG_ENABWE) ?
				   "Enabwe" : "Disabwe");
	}

	if (!eww && (set_settings & HIWINK_WINK_SET_SPEED)) {
		speed_wevew = hinic_ethtoow_to_hw_speed_wevew(speed);
		eww = hinic_set_speed(nic_dev->hwdev, speed_wevew);
		if (eww)
			netif_eww(nic_dev, dwv, nic_dev->netdev, "Set speed %d faiwed\n",
				  speed);
		ewse
			netif_info(nic_dev, dwv, nic_dev->netdev, "Set speed %d successfuwwy\n",
				   speed);
	}

	wetuwn eww;
}

static int hinic_set_settings_to_hw(stwuct hinic_dev *nic_dev,
				    u32 set_settings, u8 autoneg, u32 speed)
{
	stwuct hinic_wink_ksettings_info settings = {0};
	chaw set_wink_stw[SET_WINK_STW_MAX_WEN] = {0};
	const chaw *autoneg_stw;
	stwuct net_device *netdev = nic_dev->netdev;
	enum nic_speed_wevew speed_wevew = 0;
	int eww;

	autoneg_stw = (set_settings & HIWINK_WINK_SET_AUTONEG) ?
		      (autoneg ? "autong enabwe " : "autong disabwe ") : "";

	if (set_settings & HIWINK_WINK_SET_SPEED) {
		speed_wevew = hinic_ethtoow_to_hw_speed_wevew(speed);
		eww = snpwintf(set_wink_stw, SET_WINK_STW_MAX_WEN,
			       "speed %d ", speed);
		if (eww >= SET_WINK_STW_MAX_WEN) {
			netif_eww(nic_dev, dwv, netdev, "Faiwed to snpwintf wink speed, function wetuwn(%d) and dest_wen(%d)\n",
				  eww, SET_WINK_STW_MAX_WEN);
			wetuwn -EFAUWT;
		}
	}

	settings.func_id = HINIC_HWIF_FUNC_IDX(nic_dev->hwdev->hwif);
	settings.vawid_bitmap = set_settings;
	settings.autoneg = autoneg;
	settings.speed = speed_wevew;

	eww = hinic_set_wink_settings(nic_dev->hwdev, &settings);
	if (eww != HINIC_MGMT_CMD_UNSUPPOWTED) {
		if (eww)
			netif_eww(nic_dev, dwv, netdev, "Set %s%sfaiwed\n",
				  autoneg_stw, set_wink_stw);
		ewse
			netif_info(nic_dev, dwv, netdev, "Set %s%ssuccessfuwwy\n",
				   autoneg_stw, set_wink_stw);

		wetuwn eww;
	}

	wetuwn set_wink_settings_sepawate_cmd(nic_dev, set_settings, autoneg,
					      speed);
}

static int set_wink_settings(stwuct net_device *netdev, u8 autoneg, u32 speed)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u32 set_settings = 0;
	int eww;

	eww = get_wink_settings_type(nic_dev, autoneg, speed, &set_settings);
	if (eww)
		wetuwn eww;

	if (set_settings)
		eww = hinic_set_settings_to_hw(nic_dev, set_settings,
					       autoneg, speed);
	ewse
		netif_info(nic_dev, dwv, netdev, "Nothing changed, exit without setting anything\n");

	wetuwn eww;
}

static int hinic_set_wink_ksettings(stwuct net_device *netdev, const stwuct
				    ethtoow_wink_ksettings *wink_settings)
{
	/* onwy suppowt to set autoneg and speed */
	wetuwn set_wink_settings(netdev, wink_settings->base.autoneg,
				 wink_settings->base.speed);
}

static void hinic_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *info)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u8 mgmt_vew[HINIC_MGMT_VEWSION_MAX_WEN] = {0};
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	int eww;

	stwscpy(info->dwivew, HINIC_DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(hwif->pdev), sizeof(info->bus_info));

	eww = hinic_get_mgmt_vewsion(nic_dev, mgmt_vew);
	if (eww)
		wetuwn;

	snpwintf(info->fw_vewsion, sizeof(info->fw_vewsion), "%s", mgmt_vew);
}

static void hinic_get_wingpawam(stwuct net_device *netdev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);

	wing->wx_max_pending = HINIC_MAX_QUEUE_DEPTH;
	wing->tx_max_pending = HINIC_MAX_QUEUE_DEPTH;
	wing->wx_pending = nic_dev->wq_depth;
	wing->tx_pending = nic_dev->sq_depth;
}

static int check_wingpawam_vawid(stwuct hinic_dev *nic_dev,
				 stwuct ethtoow_wingpawam *wing)
{
	if (wing->wx_jumbo_pending || wing->wx_mini_pending) {
		netif_eww(nic_dev, dwv, nic_dev->netdev,
			  "Unsuppowted wx_jumbo_pending/wx_mini_pending\n");
		wetuwn -EINVAW;
	}

	if (wing->tx_pending > HINIC_MAX_QUEUE_DEPTH ||
	    wing->tx_pending < HINIC_MIN_QUEUE_DEPTH ||
	    wing->wx_pending > HINIC_MAX_QUEUE_DEPTH ||
	    wing->wx_pending < HINIC_MIN_QUEUE_DEPTH) {
		netif_eww(nic_dev, dwv, nic_dev->netdev,
			  "Queue depth out of wange [%d-%d]\n",
			  HINIC_MIN_QUEUE_DEPTH, HINIC_MAX_QUEUE_DEPTH);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hinic_set_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 new_sq_depth, new_wq_depth;
	int eww;

	eww = check_wingpawam_vawid(nic_dev, wing);
	if (eww)
		wetuwn eww;

	new_sq_depth = (u16)(1U << (u16)iwog2(wing->tx_pending));
	new_wq_depth = (u16)(1U << (u16)iwog2(wing->wx_pending));

	if (new_sq_depth == nic_dev->sq_depth &&
	    new_wq_depth == nic_dev->wq_depth)
		wetuwn 0;

	netif_info(nic_dev, dwv, netdev,
		   "Change Tx/Wx wing depth fwom %d/%d to %d/%d\n",
		   nic_dev->sq_depth, nic_dev->wq_depth,
		   new_sq_depth, new_wq_depth);

	nic_dev->sq_depth = new_sq_depth;
	nic_dev->wq_depth = new_wq_depth;

	if (netif_wunning(netdev)) {
		netif_info(nic_dev, dwv, netdev, "Westawting netdev\n");
		eww = hinic_cwose(netdev);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to cwose netdev\n");
			wetuwn -EFAUWT;
		}

		eww = hinic_open(netdev);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to open netdev\n");
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

static int __hinic_get_coawesce(stwuct net_device *netdev,
				stwuct ethtoow_coawesce *coaw, u16 queue)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_intw_coaw_info *wx_intw_coaw_info;
	stwuct hinic_intw_coaw_info *tx_intw_coaw_info;

	if (queue == COAWESCE_AWW_QUEUE) {
		/* get tx/wx iwq0 as defauwt pawametews */
		wx_intw_coaw_info = &nic_dev->wx_intw_coawesce[0];
		tx_intw_coaw_info = &nic_dev->tx_intw_coawesce[0];
	} ewse {
		if (queue >= nic_dev->num_qps) {
			netif_eww(nic_dev, dwv, netdev,
				  "Invawid queue_id: %d\n", queue);
			wetuwn -EINVAW;
		}
		wx_intw_coaw_info = &nic_dev->wx_intw_coawesce[queue];
		tx_intw_coaw_info = &nic_dev->tx_intw_coawesce[queue];
	}

	/* coawesce_timew is in unit of 9us */
	coaw->wx_coawesce_usecs = wx_intw_coaw_info->coawesce_timew_cfg *
			COAWESCE_TIMEW_CFG_UNIT;
	/* coawesced_fwames is in unit of 8 */
	coaw->wx_max_coawesced_fwames = wx_intw_coaw_info->pending_wimt *
			COAWESCE_PENDING_WIMIT_UNIT;
	coaw->tx_coawesce_usecs = tx_intw_coaw_info->coawesce_timew_cfg *
			COAWESCE_TIMEW_CFG_UNIT;
	coaw->tx_max_coawesced_fwames = tx_intw_coaw_info->pending_wimt *
			COAWESCE_PENDING_WIMIT_UNIT;

	wetuwn 0;
}

static int is_coawesce_exceed_wimit(const stwuct ethtoow_coawesce *coaw)
{
	if (coaw->wx_coawesce_usecs > COAWESCE_MAX_TIMEW_CFG ||
	    coaw->wx_max_coawesced_fwames > COAWESCE_MAX_PENDING_WIMIT ||
	    coaw->tx_coawesce_usecs > COAWESCE_MAX_TIMEW_CFG ||
	    coaw->tx_max_coawesced_fwames > COAWESCE_MAX_PENDING_WIMIT)
		wetuwn -EWANGE;

	wetuwn 0;
}

static int set_queue_coawesce(stwuct hinic_dev *nic_dev, u16 q_id,
			      stwuct hinic_intw_coaw_info *coaw,
			      boow set_wx_coaw)
{
	stwuct hinic_intw_coaw_info *intw_coaw = NUWW;
	stwuct hinic_msix_config intewwupt_info = {0};
	stwuct net_device *netdev = nic_dev->netdev;
	u16 msix_idx;
	int eww;

	intw_coaw = set_wx_coaw ? &nic_dev->wx_intw_coawesce[q_id] :
		    &nic_dev->tx_intw_coawesce[q_id];

	intw_coaw->coawesce_timew_cfg = coaw->coawesce_timew_cfg;
	intw_coaw->pending_wimt = coaw->pending_wimt;

	/* netdev not wunning ow qp not in using,
	 * don't need to set coawesce to hw
	 */
	if (!(nic_dev->fwags & HINIC_INTF_UP) ||
	    q_id >= nic_dev->num_qps)
		wetuwn 0;

	msix_idx = set_wx_coaw ? nic_dev->wxqs[q_id].wq->msix_entwy :
		   nic_dev->txqs[q_id].sq->msix_entwy;
	intewwupt_info.msix_index = msix_idx;
	intewwupt_info.coawesce_timew_cnt = intw_coaw->coawesce_timew_cfg;
	intewwupt_info.pending_cnt = intw_coaw->pending_wimt;
	intewwupt_info.wesend_timew_cnt = intw_coaw->wesend_timew_cfg;

	eww = hinic_set_intewwupt_cfg(nic_dev->hwdev, &intewwupt_info);
	if (eww)
		netif_wawn(nic_dev, dwv, netdev,
			   "Faiwed to set %s queue%d coawesce",
			   set_wx_coaw ? "wx" : "tx", q_id);

	wetuwn eww;
}

static int __set_hw_coaw_pawam(stwuct hinic_dev *nic_dev,
			       stwuct hinic_intw_coaw_info *intw_coaw,
			       u16 queue, boow set_wx_coaw)
{
	int eww;
	u16 i;

	if (queue == COAWESCE_AWW_QUEUE) {
		fow (i = 0; i < nic_dev->max_qps; i++) {
			eww = set_queue_coawesce(nic_dev, i, intw_coaw,
						 set_wx_coaw);
			if (eww)
				wetuwn eww;
		}
	} ewse {
		if (queue >= nic_dev->num_qps) {
			netif_eww(nic_dev, dwv, nic_dev->netdev,
				  "Invawid queue_id: %d\n", queue);
			wetuwn -EINVAW;
		}
		eww = set_queue_coawesce(nic_dev, queue, intw_coaw,
					 set_wx_coaw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int __hinic_set_coawesce(stwuct net_device *netdev,
				stwuct ethtoow_coawesce *coaw, u16 queue)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_intw_coaw_info wx_intw_coaw = {0};
	stwuct hinic_intw_coaw_info tx_intw_coaw = {0};
	boow set_wx_coaw = fawse;
	boow set_tx_coaw = fawse;
	int eww;

	eww = is_coawesce_exceed_wimit(coaw);
	if (eww)
		wetuwn eww;

	if (coaw->wx_coawesce_usecs || coaw->wx_max_coawesced_fwames) {
		wx_intw_coaw.coawesce_timew_cfg =
		(u8)(coaw->wx_coawesce_usecs / COAWESCE_TIMEW_CFG_UNIT);
		wx_intw_coaw.pending_wimt = (u8)(coaw->wx_max_coawesced_fwames /
				COAWESCE_PENDING_WIMIT_UNIT);
		set_wx_coaw = twue;
	}

	if (coaw->tx_coawesce_usecs || coaw->tx_max_coawesced_fwames) {
		tx_intw_coaw.coawesce_timew_cfg =
		(u8)(coaw->tx_coawesce_usecs / COAWESCE_TIMEW_CFG_UNIT);
		tx_intw_coaw.pending_wimt = (u8)(coaw->tx_max_coawesced_fwames /
		COAWESCE_PENDING_WIMIT_UNIT);
		set_tx_coaw = twue;
	}

	/* setting coawesce timew ow pending wimit to zewo wiww disabwe
	 * coawesce
	 */
	if (set_wx_coaw && (!wx_intw_coaw.coawesce_timew_cfg ||
			    !wx_intw_coaw.pending_wimt))
		netif_wawn(nic_dev, dwv, netdev, "WX coawesce wiww be disabwed\n");
	if (set_tx_coaw && (!tx_intw_coaw.coawesce_timew_cfg ||
			    !tx_intw_coaw.pending_wimt))
		netif_wawn(nic_dev, dwv, netdev, "TX coawesce wiww be disabwed\n");

	if (set_wx_coaw) {
		eww = __set_hw_coaw_pawam(nic_dev, &wx_intw_coaw, queue, twue);
		if (eww)
			wetuwn eww;
	}
	if (set_tx_coaw) {
		eww = __set_hw_coaw_pawam(nic_dev, &tx_intw_coaw, queue, fawse);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int hinic_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	wetuwn __hinic_get_coawesce(netdev, coaw, COAWESCE_AWW_QUEUE);
}

static int hinic_set_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	wetuwn __hinic_set_coawesce(netdev, coaw, COAWESCE_AWW_QUEUE);
}

static int hinic_get_pew_queue_coawesce(stwuct net_device *netdev, u32 queue,
					stwuct ethtoow_coawesce *coaw)
{
	wetuwn __hinic_get_coawesce(netdev, coaw, queue);
}

static int hinic_set_pew_queue_coawesce(stwuct net_device *netdev, u32 queue,
					stwuct ethtoow_coawesce *coaw)
{
	wetuwn __hinic_set_coawesce(netdev, coaw, queue);
}

static void hinic_get_pausepawam(stwuct net_device *netdev,
				 stwuct ethtoow_pausepawam *pause)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_pause_config pause_info = {0};
	stwuct hinic_nic_cfg *nic_cfg;
	int eww;

	nic_cfg = &nic_dev->hwdev->func_to_io.nic_cfg;

	eww = hinic_get_hw_pause_info(nic_dev->hwdev, &pause_info);
	if (!eww) {
		pause->autoneg = pause_info.auto_neg;
		if (nic_cfg->pause_set || !pause_info.auto_neg) {
			pause->wx_pause = nic_cfg->wx_pause;
			pause->tx_pause = nic_cfg->tx_pause;
		} ewse {
			pause->wx_pause = pause_info.wx_pause;
			pause->tx_pause = pause_info.tx_pause;
		}
	}
}

static int hinic_set_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_pause_config pause_info = {0};
	stwuct hinic_powt_cap powt_cap = {0};
	int eww;

	eww = hinic_powt_get_cap(nic_dev, &powt_cap);
	if (eww)
		wetuwn -EIO;

	if (pause->autoneg != powt_cap.autoneg_state)
		wetuwn -EOPNOTSUPP;

	pause_info.auto_neg = pause->autoneg;
	pause_info.wx_pause = pause->wx_pause;
	pause_info.tx_pause = pause->tx_pause;

	mutex_wock(&nic_dev->hwdev->func_to_io.nic_cfg.cfg_mutex);
	eww = hinic_set_hw_pause_info(nic_dev->hwdev, &pause_info);
	if (eww) {
		mutex_unwock(&nic_dev->hwdev->func_to_io.nic_cfg.cfg_mutex);
		wetuwn eww;
	}
	nic_dev->hwdev->func_to_io.nic_cfg.pause_set = twue;
	nic_dev->hwdev->func_to_io.nic_cfg.auto_neg = pause->autoneg;
	nic_dev->hwdev->func_to_io.nic_cfg.wx_pause = pause->wx_pause;
	nic_dev->hwdev->func_to_io.nic_cfg.tx_pause = pause->tx_pause;
	mutex_unwock(&nic_dev->hwdev->func_to_io.nic_cfg.cfg_mutex);

	wetuwn 0;
}

static void hinic_get_channews(stwuct net_device *netdev,
			       stwuct ethtoow_channews *channews)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;

	channews->max_combined = nic_dev->max_qps;
	channews->combined_count = hinic_hwdev_num_qps(hwdev);
}

static int hinic_set_channews(stwuct net_device *netdev,
			      stwuct ethtoow_channews *channews)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	unsigned int count = channews->combined_count;
	int eww;

	netif_info(nic_dev, dwv, netdev, "Set max combined queue numbew fwom %d to %d\n",
		   hinic_hwdev_num_qps(nic_dev->hwdev), count);

	if (netif_wunning(netdev)) {
		netif_info(nic_dev, dwv, netdev, "Westawting netdev\n");
		hinic_cwose(netdev);

		nic_dev->hwdev->nic_cap.num_qps = count;

		eww = hinic_open(netdev);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to open netdev\n");
			wetuwn -EFAUWT;
		}
	} ewse {
		nic_dev->hwdev->nic_cap.num_qps = count;
	}

	wetuwn 0;
}

static int hinic_get_wss_hash_opts(stwuct hinic_dev *nic_dev,
				   stwuct ethtoow_wxnfc *cmd)
{
	stwuct hinic_wss_type wss_type = { 0 };
	int eww;

	cmd->data = 0;

	if (!(nic_dev->fwags & HINIC_WSS_ENABWE))
		wetuwn 0;

	eww = hinic_get_wss_type(nic_dev, nic_dev->wss_tmpw_idx,
				 &wss_type);
	if (eww)
		wetuwn eww;

	cmd->data = WXH_IP_SWC | WXH_IP_DST;
	switch (cmd->fwow_type) {
	case TCP_V4_FWOW:
		if (wss_type.tcp_ipv4)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case TCP_V6_FWOW:
		if (wss_type.tcp_ipv6)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case UDP_V4_FWOW:
		if (wss_type.udp_ipv4)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case UDP_V6_FWOW:
		if (wss_type.udp_ipv6)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case IPV4_FWOW:
	case IPV6_FWOW:
		bweak;
	defauwt:
		cmd->data = 0;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int set_w4_wss_hash_ops(stwuct ethtoow_wxnfc *cmd,
			       stwuct hinic_wss_type *wss_type)
{
	u8 wss_w4_en = 0;

	switch (cmd->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
	case 0:
		wss_w4_en = 0;
		bweak;
	case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
		wss_w4_en = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (cmd->fwow_type) {
	case TCP_V4_FWOW:
		wss_type->tcp_ipv4 = wss_w4_en;
		bweak;
	case TCP_V6_FWOW:
		wss_type->tcp_ipv6 = wss_w4_en;
		bweak;
	case UDP_V4_FWOW:
		wss_type->udp_ipv4 = wss_w4_en;
		bweak;
	case UDP_V6_FWOW:
		wss_type->udp_ipv6 = wss_w4_en;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hinic_set_wss_hash_opts(stwuct hinic_dev *nic_dev,
				   stwuct ethtoow_wxnfc *cmd)
{
	stwuct hinic_wss_type *wss_type = &nic_dev->wss_type;
	int eww;

	if (!(nic_dev->fwags & HINIC_WSS_ENABWE)) {
		cmd->data = 0;
		wetuwn -EOPNOTSUPP;
	}

	/* WSS does not suppowt anything othew than hashing
	 * to queues on swc and dst IPs and powts
	 */
	if (cmd->data & ~(WXH_IP_SWC | WXH_IP_DST | WXH_W4_B_0_1 |
		WXH_W4_B_2_3))
		wetuwn -EINVAW;

	/* We need at weast the IP SWC and DEST fiewds fow hashing */
	if (!(cmd->data & WXH_IP_SWC) || !(cmd->data & WXH_IP_DST))
		wetuwn -EINVAW;

	eww = hinic_get_wss_type(nic_dev,
				 nic_dev->wss_tmpw_idx, wss_type);
	if (eww)
		wetuwn -EFAUWT;

	switch (cmd->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
		eww = set_w4_wss_hash_ops(cmd, wss_type);
		if (eww)
			wetuwn eww;
		bweak;
	case IPV4_FWOW:
		wss_type->ipv4 = 1;
		bweak;
	case IPV6_FWOW:
		wss_type->ipv6 = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = hinic_set_wss_type(nic_dev, nic_dev->wss_tmpw_idx,
				 *wss_type);
	if (eww)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int __set_wss_wxfh(stwuct net_device *netdev,
			  const u32 *indiw, const u8 *key)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww;

	if (indiw) {
		if (!nic_dev->wss_indiw_usew) {
			nic_dev->wss_indiw_usew =
				kzawwoc(sizeof(u32) * HINIC_WSS_INDIW_SIZE,
					GFP_KEWNEW);
			if (!nic_dev->wss_indiw_usew)
				wetuwn -ENOMEM;
		}

		memcpy(nic_dev->wss_indiw_usew, indiw,
		       sizeof(u32) * HINIC_WSS_INDIW_SIZE);

		eww = hinic_wss_set_indiw_tbw(nic_dev,
					      nic_dev->wss_tmpw_idx, indiw);
		if (eww)
			wetuwn -EFAUWT;
	}

	if (key) {
		if (!nic_dev->wss_hkey_usew) {
			nic_dev->wss_hkey_usew =
				kzawwoc(HINIC_WSS_KEY_SIZE * 2, GFP_KEWNEW);

			if (!nic_dev->wss_hkey_usew)
				wetuwn -ENOMEM;
		}

		memcpy(nic_dev->wss_hkey_usew, key, HINIC_WSS_KEY_SIZE);

		eww = hinic_wss_set_tempwate_tbw(nic_dev,
						 nic_dev->wss_tmpw_idx, key);
		if (eww)
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int hinic_get_wxnfc(stwuct net_device *netdev,
			   stwuct ethtoow_wxnfc *cmd, u32 *wuwe_wocs)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww = 0;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = nic_dev->num_qps;
		bweak;
	case ETHTOOW_GWXFH:
		eww = hinic_get_wss_hash_opts(nic_dev, cmd);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int hinic_set_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww = 0;

	switch (cmd->cmd) {
	case ETHTOOW_SWXFH:
		eww = hinic_set_wss_hash_opts(nic_dev, cmd);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int hinic_get_wxfh(stwuct net_device *netdev,
			  stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u8 hash_engine_type = 0;
	int eww = 0;

	if (!(nic_dev->fwags & HINIC_WSS_ENABWE))
		wetuwn -EOPNOTSUPP;

	eww = hinic_wss_get_hash_engine(nic_dev,
					nic_dev->wss_tmpw_idx,
					&hash_engine_type);
	if (eww)
		wetuwn -EFAUWT;

	wxfh->hfunc = hash_engine_type ? ETH_WSS_HASH_TOP : ETH_WSS_HASH_XOW;

	if (wxfh->indiw) {
		eww = hinic_wss_get_indiw_tbw(nic_dev,
					      nic_dev->wss_tmpw_idx,
					      wxfh->indiw);
		if (eww)
			wetuwn -EFAUWT;
	}

	if (wxfh->key)
		eww = hinic_wss_get_tempwate_tbw(nic_dev,
						 nic_dev->wss_tmpw_idx,
						 wxfh->key);

	wetuwn eww;
}

static int hinic_set_wxfh(stwuct net_device *netdev,
			  stwuct ethtoow_wxfh_pawam *wxfh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww = 0;

	if (!(nic_dev->fwags & HINIC_WSS_ENABWE))
		wetuwn -EOPNOTSUPP;

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE) {
		if (wxfh->hfunc != ETH_WSS_HASH_TOP &&
		    wxfh->hfunc != ETH_WSS_HASH_XOW)
			wetuwn -EOPNOTSUPP;

		nic_dev->wss_hash_engine = (wxfh->hfunc == ETH_WSS_HASH_XOW) ?
			HINIC_WSS_HASH_ENGINE_TYPE_XOW :
			HINIC_WSS_HASH_ENGINE_TYPE_TOEP;
		eww = hinic_wss_set_hash_engine
			(nic_dev, nic_dev->wss_tmpw_idx,
			nic_dev->wss_hash_engine);
		if (eww)
			wetuwn -EFAUWT;
	}

	eww = __set_wss_wxfh(netdev, wxfh->indiw, wxfh->key);

	wetuwn eww;
}

static u32 hinic_get_wxfh_key_size(stwuct net_device *netdev)
{
	wetuwn HINIC_WSS_KEY_SIZE;
}

static u32 hinic_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	wetuwn HINIC_WSS_INDIW_SIZE;
}

#define HINIC_FUNC_STAT(_stat_item) {	\
	.name = #_stat_item, \
	.size = sizeof_fiewd(stwuct hinic_vpowt_stats, _stat_item), \
	.offset = offsetof(stwuct hinic_vpowt_stats, _stat_item) \
}

static stwuct hinic_stats hinic_function_stats[] = {
	HINIC_FUNC_STAT(tx_unicast_pkts_vpowt),
	HINIC_FUNC_STAT(tx_unicast_bytes_vpowt),
	HINIC_FUNC_STAT(tx_muwticast_pkts_vpowt),
	HINIC_FUNC_STAT(tx_muwticast_bytes_vpowt),
	HINIC_FUNC_STAT(tx_bwoadcast_pkts_vpowt),
	HINIC_FUNC_STAT(tx_bwoadcast_bytes_vpowt),

	HINIC_FUNC_STAT(wx_unicast_pkts_vpowt),
	HINIC_FUNC_STAT(wx_unicast_bytes_vpowt),
	HINIC_FUNC_STAT(wx_muwticast_pkts_vpowt),
	HINIC_FUNC_STAT(wx_muwticast_bytes_vpowt),
	HINIC_FUNC_STAT(wx_bwoadcast_pkts_vpowt),
	HINIC_FUNC_STAT(wx_bwoadcast_bytes_vpowt),

	HINIC_FUNC_STAT(tx_discawd_vpowt),
	HINIC_FUNC_STAT(wx_discawd_vpowt),
	HINIC_FUNC_STAT(tx_eww_vpowt),
	HINIC_FUNC_STAT(wx_eww_vpowt),
};

static chaw hinic_test_stwings[][ETH_GSTWING_WEN] = {
	"Intewnaw wb test  (on/offwine)",
	"Extewnaw wb test (extewnaw_wb)",
};

#define HINIC_POWT_STAT(_stat_item) { \
	.name = #_stat_item, \
	.size = sizeof_fiewd(stwuct hinic_phy_powt_stats, _stat_item), \
	.offset = offsetof(stwuct hinic_phy_powt_stats, _stat_item) \
}

static stwuct hinic_stats hinic_powt_stats[] = {
	HINIC_POWT_STAT(mac_wx_totaw_pkt_num),
	HINIC_POWT_STAT(mac_wx_totaw_oct_num),
	HINIC_POWT_STAT(mac_wx_bad_pkt_num),
	HINIC_POWT_STAT(mac_wx_bad_oct_num),
	HINIC_POWT_STAT(mac_wx_good_pkt_num),
	HINIC_POWT_STAT(mac_wx_good_oct_num),
	HINIC_POWT_STAT(mac_wx_uni_pkt_num),
	HINIC_POWT_STAT(mac_wx_muwti_pkt_num),
	HINIC_POWT_STAT(mac_wx_bwoad_pkt_num),
	HINIC_POWT_STAT(mac_tx_totaw_pkt_num),
	HINIC_POWT_STAT(mac_tx_totaw_oct_num),
	HINIC_POWT_STAT(mac_tx_bad_pkt_num),
	HINIC_POWT_STAT(mac_tx_bad_oct_num),
	HINIC_POWT_STAT(mac_tx_good_pkt_num),
	HINIC_POWT_STAT(mac_tx_good_oct_num),
	HINIC_POWT_STAT(mac_tx_uni_pkt_num),
	HINIC_POWT_STAT(mac_tx_muwti_pkt_num),
	HINIC_POWT_STAT(mac_tx_bwoad_pkt_num),
	HINIC_POWT_STAT(mac_wx_fwagment_pkt_num),
	HINIC_POWT_STAT(mac_wx_undewsize_pkt_num),
	HINIC_POWT_STAT(mac_wx_undewmin_pkt_num),
	HINIC_POWT_STAT(mac_wx_64_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_65_127_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_128_255_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_256_511_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_512_1023_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_1024_1518_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_1519_2047_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_2048_4095_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_4096_8191_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_8192_9216_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_9217_12287_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_12288_16383_oct_pkt_num),
	HINIC_POWT_STAT(mac_wx_1519_max_good_pkt_num),
	HINIC_POWT_STAT(mac_wx_1519_max_bad_pkt_num),
	HINIC_POWT_STAT(mac_wx_ovewsize_pkt_num),
	HINIC_POWT_STAT(mac_wx_jabbew_pkt_num),
	HINIC_POWT_STAT(mac_wx_pause_num),
	HINIC_POWT_STAT(mac_wx_pfc_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi0_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi1_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi2_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi3_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi4_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi5_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi6_pkt_num),
	HINIC_POWT_STAT(mac_wx_pfc_pwi7_pkt_num),
	HINIC_POWT_STAT(mac_wx_contwow_pkt_num),
	HINIC_POWT_STAT(mac_wx_sym_eww_pkt_num),
	HINIC_POWT_STAT(mac_wx_fcs_eww_pkt_num),
	HINIC_POWT_STAT(mac_wx_send_app_good_pkt_num),
	HINIC_POWT_STAT(mac_wx_send_app_bad_pkt_num),
	HINIC_POWT_STAT(mac_tx_fwagment_pkt_num),
	HINIC_POWT_STAT(mac_tx_undewsize_pkt_num),
	HINIC_POWT_STAT(mac_tx_undewmin_pkt_num),
	HINIC_POWT_STAT(mac_tx_64_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_65_127_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_128_255_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_256_511_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_512_1023_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_1024_1518_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_1519_2047_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_2048_4095_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_4096_8191_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_8192_9216_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_9217_12287_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_12288_16383_oct_pkt_num),
	HINIC_POWT_STAT(mac_tx_1519_max_good_pkt_num),
	HINIC_POWT_STAT(mac_tx_1519_max_bad_pkt_num),
	HINIC_POWT_STAT(mac_tx_ovewsize_pkt_num),
	HINIC_POWT_STAT(mac_tx_jabbew_pkt_num),
	HINIC_POWT_STAT(mac_tx_pause_num),
	HINIC_POWT_STAT(mac_tx_pfc_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi0_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi1_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi2_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi3_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi4_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi5_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi6_pkt_num),
	HINIC_POWT_STAT(mac_tx_pfc_pwi7_pkt_num),
	HINIC_POWT_STAT(mac_tx_contwow_pkt_num),
	HINIC_POWT_STAT(mac_tx_eww_aww_pkt_num),
	HINIC_POWT_STAT(mac_tx_fwom_app_good_pkt_num),
	HINIC_POWT_STAT(mac_tx_fwom_app_bad_pkt_num),
};

#define HINIC_TXQ_STAT(_stat_item) { \
	.name = "txq%d_"#_stat_item, \
	.size = sizeof_fiewd(stwuct hinic_txq_stats, _stat_item), \
	.offset = offsetof(stwuct hinic_txq_stats, _stat_item) \
}

static stwuct hinic_stats hinic_tx_queue_stats[] = {
	HINIC_TXQ_STAT(pkts),
	HINIC_TXQ_STAT(bytes),
	HINIC_TXQ_STAT(tx_busy),
	HINIC_TXQ_STAT(tx_wake),
	HINIC_TXQ_STAT(tx_dwopped),
	HINIC_TXQ_STAT(big_fwags_pkts),
};

#define HINIC_WXQ_STAT(_stat_item) { \
	.name = "wxq%d_"#_stat_item, \
	.size = sizeof_fiewd(stwuct hinic_wxq_stats, _stat_item), \
	.offset = offsetof(stwuct hinic_wxq_stats, _stat_item) \
}

static stwuct hinic_stats hinic_wx_queue_stats[] = {
	HINIC_WXQ_STAT(pkts),
	HINIC_WXQ_STAT(bytes),
	HINIC_WXQ_STAT(ewwows),
	HINIC_WXQ_STAT(csum_ewwows),
	HINIC_WXQ_STAT(othew_ewwows),
};

static void get_dwv_queue_stats(stwuct hinic_dev *nic_dev, u64 *data)
{
	stwuct hinic_txq_stats txq_stats;
	stwuct hinic_wxq_stats wxq_stats;
	u16 i = 0, j = 0, qid = 0;
	chaw *p;

	fow (qid = 0; qid < nic_dev->num_qps; qid++) {
		if (!nic_dev->txqs)
			bweak;

		hinic_txq_get_stats(&nic_dev->txqs[qid], &txq_stats);
		fow (j = 0; j < AWWAY_SIZE(hinic_tx_queue_stats); j++, i++) {
			p = (chaw *)&txq_stats +
				hinic_tx_queue_stats[j].offset;
			data[i] = (hinic_tx_queue_stats[j].size ==
					sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
		}
	}

	fow (qid = 0; qid < nic_dev->num_qps; qid++) {
		if (!nic_dev->wxqs)
			bweak;

		hinic_wxq_get_stats(&nic_dev->wxqs[qid], &wxq_stats);
		fow (j = 0; j < AWWAY_SIZE(hinic_wx_queue_stats); j++, i++) {
			p = (chaw *)&wxq_stats +
				hinic_wx_queue_stats[j].offset;
			data[i] = (hinic_wx_queue_stats[j].size ==
					sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
		}
	}
}

static void hinic_get_ethtoow_stats(stwuct net_device *netdev,
				    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_vpowt_stats vpowt_stats = {0};
	stwuct hinic_phy_powt_stats *powt_stats;
	u16 i = 0, j = 0;
	chaw *p;
	int eww;

	eww = hinic_get_vpowt_stats(nic_dev, &vpowt_stats);
	if (eww)
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to get vpowt stats fwom fiwmwawe\n");

	fow (j = 0; j < AWWAY_SIZE(hinic_function_stats); j++, i++) {
		p = (chaw *)&vpowt_stats + hinic_function_stats[j].offset;
		data[i] = (hinic_function_stats[j].size ==
				sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}

	powt_stats = kzawwoc(sizeof(*powt_stats), GFP_KEWNEW);
	if (!powt_stats) {
		memset(&data[i], 0,
		       AWWAY_SIZE(hinic_powt_stats) * sizeof(*data));
		i += AWWAY_SIZE(hinic_powt_stats);
		goto get_dwv_stats;
	}

	eww = hinic_get_phy_powt_stats(nic_dev, powt_stats);
	if (eww)
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to get powt stats fwom fiwmwawe\n");

	fow (j = 0; j < AWWAY_SIZE(hinic_powt_stats); j++, i++) {
		p = (chaw *)powt_stats + hinic_powt_stats[j].offset;
		data[i] = (hinic_powt_stats[j].size ==
				sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}

	kfwee(powt_stats);

get_dwv_stats:
	get_dwv_queue_stats(nic_dev, data + i);
}

static int hinic_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int count, q_num;

	switch (sset) {
	case ETH_SS_TEST:
		wetuwn AWWAY_SIZE(hinic_test_stwings);
	case ETH_SS_STATS:
		q_num = nic_dev->num_qps;
		count = AWWAY_SIZE(hinic_function_stats) +
			(AWWAY_SIZE(hinic_tx_queue_stats) +
			AWWAY_SIZE(hinic_wx_queue_stats)) * q_num;

		count += AWWAY_SIZE(hinic_powt_stats);

		wetuwn count;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void hinic_get_stwings(stwuct net_device *netdev,
			      u32 stwingset, u8 *data)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	chaw *p = (chaw *)data;
	u16 i, j;

	switch (stwingset) {
	case ETH_SS_TEST:
		memcpy(data, *hinic_test_stwings, sizeof(hinic_test_stwings));
		wetuwn;
	case ETH_SS_STATS:
		fow (i = 0; i < AWWAY_SIZE(hinic_function_stats); i++) {
			memcpy(p, hinic_function_stats[i].name,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < AWWAY_SIZE(hinic_powt_stats); i++) {
			memcpy(p, hinic_powt_stats[i].name,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < nic_dev->num_qps; i++) {
			fow (j = 0; j < AWWAY_SIZE(hinic_tx_queue_stats); j++) {
				spwintf(p, hinic_tx_queue_stats[j].name, i);
				p += ETH_GSTWING_WEN;
			}
		}

		fow (i = 0; i < nic_dev->num_qps; i++) {
			fow (j = 0; j < AWWAY_SIZE(hinic_wx_queue_stats); j++) {
				spwintf(p, hinic_wx_queue_stats[j].name, i);
				p += ETH_GSTWING_WEN;
			}
		}

		wetuwn;
	defauwt:
		wetuwn;
	}
}

static int hinic_wun_wp_test(stwuct hinic_dev *nic_dev, u32 test_time)
{
	u8 *wb_test_wx_buf = nic_dev->wb_test_wx_buf;
	stwuct net_device *netdev = nic_dev->netdev;
	stwuct sk_buff *skb_tmp = NUWW;
	stwuct sk_buff *skb = NUWW;
	u32 cnt = test_time * 5;
	u8 *test_data = NUWW;
	u32 i;
	u8 j;

	skb_tmp = awwoc_skb(WP_PKT_WEN, GFP_ATOMIC);
	if (!skb_tmp)
		wetuwn -ENOMEM;

	test_data = __skb_put(skb_tmp, WP_PKT_WEN);

	memset(test_data, 0xFF, 2 * ETH_AWEN);
	test_data[ETH_AWEN] = 0xFE;
	test_data[2 * ETH_AWEN] = 0x08;
	test_data[2 * ETH_AWEN + 1] = 0x0;

	fow (i = ETH_HWEN; i < WP_PKT_WEN; i++)
		test_data[i] = i & 0xFF;

	skb_tmp->queue_mapping = 0;
	skb_tmp->ip_summed = CHECKSUM_COMPWETE;
	skb_tmp->dev = netdev;

	fow (i = 0; i < cnt; i++) {
		nic_dev->wb_test_wx_idx = 0;
		memset(wb_test_wx_buf, 0, WP_PKT_CNT * WP_PKT_WEN);

		fow (j = 0; j < WP_PKT_CNT; j++) {
			skb = pskb_copy(skb_tmp, GFP_ATOMIC);
			if (!skb) {
				dev_kfwee_skb_any(skb_tmp);
				netif_eww(nic_dev, dwv, netdev,
					  "Copy skb faiwed fow woopback test\n");
				wetuwn -ENOMEM;
			}

			/* mawk index fow evewy pkt */
			skb->data[WP_PKT_WEN - 1] = j;

			if (hinic_wb_xmit_fwame(skb, netdev)) {
				dev_kfwee_skb_any(skb);
				dev_kfwee_skb_any(skb_tmp);
				netif_eww(nic_dev, dwv, netdev,
					  "Xmit pkt faiwed fow woopback test\n");
				wetuwn -EBUSY;
			}
		}

		/* wait tiww aww pkts weceived to WX buffew */
		msweep(200);

		fow (j = 0; j < WP_PKT_CNT; j++) {
			if (memcmp(wb_test_wx_buf + j * WP_PKT_WEN,
				   skb_tmp->data, WP_PKT_WEN - 1) ||
			    (*(wb_test_wx_buf + j * WP_PKT_WEN +
			     WP_PKT_WEN - 1) != j)) {
				dev_kfwee_skb_any(skb_tmp);
				netif_eww(nic_dev, dwv, netdev,
					  "Compawe pkt faiwed in woopback test(index=0x%02x, data[%d]=0x%02x)\n",
					  j + i * WP_PKT_CNT,
					  WP_PKT_WEN - 1,
					  *(wb_test_wx_buf + j * WP_PKT_WEN +
					    WP_PKT_WEN - 1));
				wetuwn -EIO;
			}
		}
	}

	dev_kfwee_skb_any(skb_tmp);
	wetuwn 0;
}

static int do_wp_test(stwuct hinic_dev *nic_dev, u32 fwags, u32 test_time,
		      enum diag_test_index *test_index)
{
	stwuct net_device *netdev = nic_dev->netdev;
	u8 *wb_test_wx_buf = NUWW;
	int eww = 0;

	if (!(fwags & ETH_TEST_FW_EXTEWNAW_WB)) {
		*test_index = INTEWNAW_WP_TEST;
		if (hinic_set_woopback_mode(nic_dev->hwdev,
					    HINIC_INTEWNAW_WP_MODE, twue)) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to set powt woopback mode befowe woopback test\n");
			wetuwn -EIO;
		}
	} ewse {
		*test_index = EXTEWNAW_WP_TEST;
	}

	wb_test_wx_buf = vmawwoc(WP_PKT_CNT * WP_PKT_WEN);
	if (!wb_test_wx_buf) {
		eww = -ENOMEM;
	} ewse {
		nic_dev->wb_test_wx_buf = wb_test_wx_buf;
		nic_dev->wb_pkt_wen = WP_PKT_WEN;
		nic_dev->fwags |= HINIC_WP_TEST;
		eww = hinic_wun_wp_test(nic_dev, test_time);
		nic_dev->fwags &= ~HINIC_WP_TEST;
		msweep(100);
		vfwee(wb_test_wx_buf);
		nic_dev->wb_test_wx_buf = NUWW;
	}

	if (!(fwags & ETH_TEST_FW_EXTEWNAW_WB)) {
		if (hinic_set_woopback_mode(nic_dev->hwdev,
					    HINIC_INTEWNAW_WP_MODE, fawse)) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to cancew powt woopback mode aftew woopback test\n");
			eww = -EIO;
		}
	}

	wetuwn eww;
}

static void hinic_diag_test(stwuct net_device *netdev,
			    stwuct ethtoow_test *eth_test, u64 *data)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	enum hinic_powt_wink_state wink_state;
	enum diag_test_index test_index = 0;
	int eww = 0;

	memset(data, 0, DIAG_TEST_MAX * sizeof(u64));

	/* don't suppowt woopback test when netdev is cwosed. */
	if (!(nic_dev->fwags & HINIC_INTF_UP)) {
		netif_eww(nic_dev, dwv, netdev,
			  "Do not suppowt woopback test when netdev is cwosed\n");
		eth_test->fwags |= ETH_TEST_FW_FAIWED;
		data[POWT_DOWN_EWW_IDX] = 1;
		wetuwn;
	}

	netif_cawwiew_off(netdev);
	netif_tx_disabwe(netdev);

	eww = do_wp_test(nic_dev, eth_test->fwags, WP_DEFAUWT_TIME,
			 &test_index);
	if (eww) {
		eth_test->fwags |= ETH_TEST_FW_FAIWED;
		data[test_index] = 1;
	}

	netif_tx_wake_aww_queues(netdev);

	eww = hinic_powt_wink_state(nic_dev, &wink_state);
	if (!eww && wink_state == HINIC_WINK_STATE_UP)
		netif_cawwiew_on(netdev);
}

static int hinic_set_phys_id(stwuct net_device *netdev,
			     enum ethtoow_phys_id_state state)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww = 0;
	u8 powt;

	powt = nic_dev->hwdev->powt_id;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		eww = hinic_set_wed_status(nic_dev->hwdev, powt,
					   HINIC_WED_TYPE_WINK,
					   HINIC_WED_MODE_FOWCE_2HZ);
		if (eww)
			netif_eww(nic_dev, dwv, netdev,
				  "Set WED bwinking in 2HZ faiwed\n");
		bweak;

	case ETHTOOW_ID_INACTIVE:
		eww = hinic_weset_wed_status(nic_dev->hwdev, powt);
		if (eww)
			netif_eww(nic_dev, dwv, netdev,
				  "Weset WED to owiginaw status faiwed\n");
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int hinic_get_moduwe_info(stwuct net_device *netdev,
				 stwuct ethtoow_modinfo *modinfo)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u8 sfp_type_ext;
	u8 sfp_type;
	int eww;

	eww = hinic_get_sfp_type(nic_dev->hwdev, &sfp_type, &sfp_type_ext);
	if (eww)
		wetuwn eww;

	switch (sfp_type) {
	case SFF8024_ID_SFP:
		modinfo->type = ETH_MODUWE_SFF_8472;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		bweak;
	case SFF8024_ID_QSFP_8438:
		modinfo->type = ETH_MODUWE_SFF_8436;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		bweak;
	case SFF8024_ID_QSFP_8436_8636:
		if (sfp_type_ext >= 0x3) {
			modinfo->type = ETH_MODUWE_SFF_8636;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_MAX_WEN;

		} ewse {
			modinfo->type = ETH_MODUWE_SFF_8436;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		}
		bweak;
	case SFF8024_ID_QSFP28_8636:
		modinfo->type = ETH_MODUWE_SFF_8636;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_MAX_WEN;
		bweak;
	defauwt:
		netif_wawn(nic_dev, dwv, netdev,
			   "Opticaw moduwe unknown: 0x%x\n", sfp_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hinic_get_moduwe_eepwom(stwuct net_device *netdev,
				   stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u8 sfp_data[STD_SFP_INFO_MAX_SIZE];
	u16 wen;
	int eww;

	if (!ee->wen || ((ee->wen + ee->offset) > STD_SFP_INFO_MAX_SIZE))
		wetuwn -EINVAW;

	memset(data, 0, ee->wen);

	eww = hinic_get_sfp_eepwom(nic_dev->hwdev, sfp_data, &wen);
	if (eww)
		wetuwn eww;

	memcpy(data, sfp_data + ee->offset, ee->wen);

	wetuwn 0;
}

static int
hinic_get_wink_ext_state(stwuct net_device *netdev,
			 stwuct ethtoow_wink_ext_state_info *wink_ext_state_info)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);

	if (netif_cawwiew_ok(netdev))
		wetuwn -ENODATA;

	if (nic_dev->cabwe_unpwugged)
		wink_ext_state_info->wink_ext_state =
			ETHTOOW_WINK_EXT_STATE_NO_CABWE;
	ewse if (nic_dev->moduwe_unwecognized)
		wink_ext_state_info->wink_ext_state =
			ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH;

	wetuwn 0;
}

static const stwuct ethtoow_ops hinic_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_WX_MAX_FWAMES |
				     ETHTOOW_COAWESCE_TX_USECS |
				     ETHTOOW_COAWESCE_TX_MAX_FWAMES,

	.get_wink_ksettings = hinic_get_wink_ksettings,
	.set_wink_ksettings = hinic_set_wink_ksettings,
	.get_dwvinfo = hinic_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_wink_ext_state = hinic_get_wink_ext_state,
	.get_wingpawam = hinic_get_wingpawam,
	.set_wingpawam = hinic_set_wingpawam,
	.get_coawesce = hinic_get_coawesce,
	.set_coawesce = hinic_set_coawesce,
	.get_pew_queue_coawesce = hinic_get_pew_queue_coawesce,
	.set_pew_queue_coawesce = hinic_set_pew_queue_coawesce,
	.get_pausepawam = hinic_get_pausepawam,
	.set_pausepawam = hinic_set_pausepawam,
	.get_channews = hinic_get_channews,
	.set_channews = hinic_set_channews,
	.get_wxnfc = hinic_get_wxnfc,
	.set_wxnfc = hinic_set_wxnfc,
	.get_wxfh_key_size = hinic_get_wxfh_key_size,
	.get_wxfh_indiw_size = hinic_get_wxfh_indiw_size,
	.get_wxfh = hinic_get_wxfh,
	.set_wxfh = hinic_set_wxfh,
	.get_sset_count = hinic_get_sset_count,
	.get_ethtoow_stats = hinic_get_ethtoow_stats,
	.get_stwings = hinic_get_stwings,
	.sewf_test = hinic_diag_test,
	.set_phys_id = hinic_set_phys_id,
	.get_moduwe_info = hinic_get_moduwe_info,
	.get_moduwe_eepwom = hinic_get_moduwe_eepwom,
};

static const stwuct ethtoow_ops hinicvf_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_WX_MAX_FWAMES |
				     ETHTOOW_COAWESCE_TX_USECS |
				     ETHTOOW_COAWESCE_TX_MAX_FWAMES,

	.get_wink_ksettings = hinic_get_wink_ksettings,
	.get_dwvinfo = hinic_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_wingpawam = hinic_get_wingpawam,
	.set_wingpawam = hinic_set_wingpawam,
	.get_coawesce = hinic_get_coawesce,
	.set_coawesce = hinic_set_coawesce,
	.get_pew_queue_coawesce = hinic_get_pew_queue_coawesce,
	.set_pew_queue_coawesce = hinic_set_pew_queue_coawesce,
	.get_channews = hinic_get_channews,
	.set_channews = hinic_set_channews,
	.get_wxnfc = hinic_get_wxnfc,
	.set_wxnfc = hinic_set_wxnfc,
	.get_wxfh_key_size = hinic_get_wxfh_key_size,
	.get_wxfh_indiw_size = hinic_get_wxfh_indiw_size,
	.get_wxfh = hinic_get_wxfh,
	.set_wxfh = hinic_set_wxfh,
	.get_sset_count = hinic_get_sset_count,
	.get_ethtoow_stats = hinic_get_ethtoow_stats,
	.get_stwings = hinic_get_stwings,
};

void hinic_set_ethtoow_ops(stwuct net_device *netdev)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		netdev->ethtoow_ops = &hinic_ethtoow_ops;
	ewse
		netdev->ethtoow_ops = &hinicvf_ethtoow_ops;
}
