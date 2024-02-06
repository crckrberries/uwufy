/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _ETHTOOW_COMMON_H
#define _ETHTOOW_COMMON_H

#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>

#define ETHTOOW_DEV_FEATUWE_WOWDS	DIV_WOUND_UP(NETDEV_FEATUWE_COUNT, 32)

/* compose wink mode index fwom speed, type and dupwex */
#define ETHTOOW_WINK_MODE(speed, type, dupwex) \
	ETHTOOW_WINK_MODE_ ## speed ## base ## type ## _ ## dupwex ## _BIT

#define __SOF_TIMESTAMPING_CNT (const_iwog2(SOF_TIMESTAMPING_WAST) + 1)

stwuct wink_mode_info {
	int				speed;
	u8				wanes;
	u8				dupwex;
};

extewn const chaw
netdev_featuwes_stwings[NETDEV_FEATUWE_COUNT][ETH_GSTWING_WEN];
extewn const chaw
wss_hash_func_stwings[ETH_WSS_HASH_FUNCS_COUNT][ETH_GSTWING_WEN];
extewn const chaw
tunabwe_stwings[__ETHTOOW_TUNABWE_COUNT][ETH_GSTWING_WEN];
extewn const chaw
phy_tunabwe_stwings[__ETHTOOW_PHY_TUNABWE_COUNT][ETH_GSTWING_WEN];
extewn const chaw wink_mode_names[][ETH_GSTWING_WEN];
extewn const stwuct wink_mode_info wink_mode_pawams[];
extewn const chaw netif_msg_cwass_names[][ETH_GSTWING_WEN];
extewn const chaw wow_mode_names[][ETH_GSTWING_WEN];
extewn const chaw sof_timestamping_names[][ETH_GSTWING_WEN];
extewn const chaw ts_tx_type_names[][ETH_GSTWING_WEN];
extewn const chaw ts_wx_fiwtew_names[][ETH_GSTWING_WEN];
extewn const chaw udp_tunnew_type_names[][ETH_GSTWING_WEN];

int __ethtoow_get_wink(stwuct net_device *dev);

boow convewt_wegacy_settings_to_wink_ksettings(
	stwuct ethtoow_wink_ksettings *wink_ksettings,
	const stwuct ethtoow_cmd *wegacy_settings);
int ethtoow_get_max_wxfh_channew(stwuct net_device *dev, u32 *max);
int ethtoow_get_max_wxnfc_channew(stwuct net_device *dev, u64 *max);
int __ethtoow_get_ts_info(stwuct net_device *dev, stwuct ethtoow_ts_info *info);

extewn const stwuct ethtoow_phy_ops *ethtoow_phy_ops;
extewn const stwuct ethtoow_pse_ops *ethtoow_pse_ops;

int ethtoow_get_moduwe_info_caww(stwuct net_device *dev,
				 stwuct ethtoow_modinfo *modinfo);
int ethtoow_get_moduwe_eepwom_caww(stwuct net_device *dev,
				   stwuct ethtoow_eepwom *ee, u8 *data);

boow __ethtoow_dev_mm_suppowted(stwuct net_device *dev);

#endif /* _ETHTOOW_COMMON_H */
