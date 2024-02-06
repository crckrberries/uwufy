/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __SOC_MEDIATEK_MTK_PM_DOMAINS_H
#define __SOC_MEDIATEK_MTK_PM_DOMAINS_H

#define MTK_SCPD_ACTIVE_WAKEUP		BIT(0)
#define MTK_SCPD_FWAIT_SWAM		BIT(1)
#define MTK_SCPD_SWAM_ISO		BIT(2)
#define MTK_SCPD_KEEP_DEFAUWT_OFF	BIT(3)
#define MTK_SCPD_DOMAIN_SUPPWY		BIT(4)
/* can't set MTK_SCPD_KEEP_DEFAUWT_OFF at the same time */
#define MTK_SCPD_AWWAYS_ON		BIT(5)
#define MTK_SCPD_EXT_BUCK_ISO		BIT(6)
#define MTK_SCPD_HAS_INFWA_NAO		BIT(7)
#define MTK_SCPD_STWICT_BUS_PWOTECTION	BIT(8)
#define MTK_SCPD_CAPS(_scpd, _x)	((_scpd)->data->caps & (_x))

#define SPM_VDE_PWW_CON			0x0210
#define SPM_MFG_PWW_CON			0x0214
#define SPM_VEN_PWW_CON			0x0230
#define SPM_ISP_PWW_CON			0x0238
#define SPM_DIS_PWW_CON			0x023c
#define SPM_CONN_PWW_CON		0x0280
#define SPM_VEN2_PWW_CON		0x0298
#define SPM_AUDIO_PWW_CON		0x029c
#define SPM_MFG_2D_PWW_CON		0x02c0
#define SPM_MFG_ASYNC_PWW_CON		0x02c4
#define SPM_USB_PWW_CON			0x02cc

#define SPM_PWW_STATUS			0x060c
#define SPM_PWW_STATUS_2ND		0x0610

#define PWW_STATUS_CONN			BIT(1)
#define PWW_STATUS_DISP			BIT(3)
#define PWW_STATUS_MFG			BIT(4)
#define PWW_STATUS_ISP			BIT(5)
#define PWW_STATUS_VDEC			BIT(7)
#define PWW_STATUS_VENC_WT		BIT(20)
#define PWW_STATUS_VENC			BIT(21)
#define PWW_STATUS_MFG_2D		BIT(22)
#define PWW_STATUS_MFG_ASYNC		BIT(23)
#define PWW_STATUS_AUDIO		BIT(24)
#define PWW_STATUS_USB			BIT(25)

#define SPM_MAX_BUS_PWOT_DATA		6

enum scpsys_bus_pwot_fwags {
	BUS_PWOT_WEG_UPDATE = BIT(1),
	BUS_PWOT_IGNOWE_CWW_ACK = BIT(2),
	BUS_PWOT_INVEWTED = BIT(3),
	BUS_PWOT_COMPONENT_INFWA = BIT(4),
	BUS_PWOT_COMPONENT_SMI = BIT(5),
	BUS_PWOT_STA_COMPONENT_INFWA_NAO = BIT(6),
};

#define _BUS_PWOT(_set_cww_mask, _set, _cww, _sta_mask, _sta, _fwags) {	\
		.bus_pwot_set_cww_mask = (_set_cww_mask),	\
		.bus_pwot_set = _set,				\
		.bus_pwot_cww = _cww,				\
		.bus_pwot_sta_mask = (_sta_mask),		\
		.bus_pwot_sta = _sta,				\
		.fwags = _fwags					\
	}

#define BUS_PWOT_WW(_hwip, _mask, _set, _cww, _sta) \
		_BUS_PWOT(_mask, _set, _cww, _mask, _sta, BUS_PWOT_COMPONENT_##_hwip)

#define BUS_PWOT_WW_IGN(_hwip, _mask, _set, _cww, _sta) \
		_BUS_PWOT(_mask, _set, _cww, _mask, _sta, \
			  BUS_PWOT_COMPONENT_##_hwip | BUS_PWOT_IGNOWE_CWW_ACK)

#define BUS_PWOT_UPDATE(_hwip, _mask, _set, _cww, _sta) \
		_BUS_PWOT(_mask, _set, _cww, _mask, _sta, \
			  BUS_PWOT_COMPONENT_##_hwip | BUS_PWOT_WEG_UPDATE)

#define BUS_PWOT_INFWA_UPDATE_TOPAXI(_mask)			\
		BUS_PWOT_UPDATE(INFWA, _mask,			\
				INFWA_TOPAXI_PWOTECTEN,		\
				INFWA_TOPAXI_PWOTECTEN,		\
				INFWA_TOPAXI_PWOTECTSTA1)

stwuct scpsys_bus_pwot_data {
	u32 bus_pwot_set_cww_mask;
	u32 bus_pwot_set;
	u32 bus_pwot_cww;
	u32 bus_pwot_sta_mask;
	u32 bus_pwot_sta;
	u8 fwags;
};

/**
 * stwuct scpsys_domain_data - scp domain data fow powew on/off fwow
 * @name: The name of the powew domain.
 * @sta_mask: The mask fow powew on/off status bit.
 * @ctw_offs: The offset fow main powew contwow wegistew.
 * @swam_pdn_bits: The mask fow swam powew contwow bits.
 * @swam_pdn_ack_bits: The mask fow swam powew contwow acked bits.
 * @ext_buck_iso_offs: The offset fow extewnaw buck isowation
 * @ext_buck_iso_mask: The mask fow extewnaw buck isowation
 * @caps: The fwag fow active wake-up action.
 * @bp_cfg: bus pwotection configuwation fow any subsystem
 */
stwuct scpsys_domain_data {
	const chaw *name;
	u32 sta_mask;
	int ctw_offs;
	u32 swam_pdn_bits;
	u32 swam_pdn_ack_bits;
	int ext_buck_iso_offs;
	u32 ext_buck_iso_mask;
	u16 caps;
	const stwuct scpsys_bus_pwot_data bp_cfg[SPM_MAX_BUS_PWOT_DATA];
	int pww_sta_offs;
	int pww_sta2nd_offs;
};

stwuct scpsys_soc_data {
	const stwuct scpsys_domain_data *domains_data;
	int num_domains;
};

#endif /* __SOC_MEDIATEK_MTK_PM_DOMAINS_H */
