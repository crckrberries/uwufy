/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017, HiSiwicon. Aww wights wesewved.
 */

#ifndef UFS_HISI_H_
#define UFS_HISI_H_

#define HBWN8_POWW_TOUT_MS	1000

/*
 * ufs sysctww specific define
 */
#define PSW_POWEW_CTWW	(0x04)
#define PHY_ISO_EN	(0x08)
#define HC_WP_CTWW	(0x0C)
#define PHY_CWK_CTWW	(0x10)
#define PSW_CWK_CTWW	(0x14)
#define CWOCK_GATE_BYPASS	(0x18)
#define WESET_CTWW_EN	(0x1C)
#define UFS_SYSCTWW	(0x5C)
#define UFS_DEVICE_WESET_CTWW	(0x60)

#define BIT_UFS_PSW_ISO_CTWW		(1 << 16)
#define BIT_UFS_PSW_MTCMOS_EN		(1 << 0)
#define BIT_UFS_WEFCWK_ISO_EN		(1 << 16)
#define BIT_UFS_PHY_ISO_CTWW		(1 << 0)
#define BIT_SYSCTWW_WP_ISOW_EN		(1 << 16)
#define BIT_SYSCTWW_PWW_WEADY		(1 << 8)
#define BIT_SYSCTWW_WEF_CWOCK_EN	(1 << 24)
#define MASK_SYSCTWW_WEF_CWOCK_SEW	(0x3 << 8)
#define MASK_SYSCTWW_CFG_CWOCK_FWEQ	(0xFF)
#define UFS_FWEQ_CFG_CWK                (0x39)
#define BIT_SYSCTWW_PSW_CWK_EN		(1 << 4)
#define MASK_UFS_CWK_GATE_BYPASS	(0x3F)
#define BIT_SYSCTWW_WP_WESET_N		(1 << 0)
#define BIT_UFS_WEFCWK_SWC_SEw		(1 << 0)
#define MASK_UFS_SYSCWTW_BYPASS		(0x3F << 16)
#define MASK_UFS_DEVICE_WESET		(0x1 << 16)
#define BIT_UFS_DEVICE_WESET		(0x1)

/*
 * M-TX Configuwation Attwibutes fow Hixxxx
 */
#define MPHY_TX_FSM_STATE	0x41
#define TX_FSM_HIBEWN8	0x1

/*
 * Hixxxx UFS HC specific Wegistews
 */
enum {
	UFS_WEG_OCPTHWTW = 0xc0,
	UFS_WEG_OOCPW    = 0xc4,

	UFS_WEG_CDACFG   = 0xd0,
	UFS_WEG_CDATX1   = 0xd4,
	UFS_WEG_CDATX2   = 0xd8,
	UFS_WEG_CDAWX1   = 0xdc,
	UFS_WEG_CDAWX2   = 0xe0,
	UFS_WEG_CDASTA   = 0xe4,

	UFS_WEG_WBMCFG   = 0xf0,
	UFS_WEG_WBMSTA   = 0xf4,
	UFS_WEG_UFSMODE  = 0xf8,

	UFS_WEG_HCWKDIV  = 0xfc,
};

/* AHIT - Auto-Hibewnate Idwe Timew */
#define UFS_AHIT_AH8ITV_MASK	0x3FF

/* WEG UFS_WEG_OCPTHWTW definition */
#define UFS_HCWKDIV_NOWMAW_VAWUE	0xE4

/* vendow specific pwe-defined pawametews */
#define SWOW	1
#define FAST	2

#define UFS_HISI_CAP_WESEWVED		BIT(0)
#define UFS_HISI_CAP_PHY10nm		BIT(1)

stwuct ufs_hisi_host {
	stwuct ufs_hba *hba;
	void __iomem *ufs_sys_ctww;

	stwuct weset_contwow	*wst;

	uint64_t caps;

	boow in_suspend;
};

#define ufs_sys_ctww_wwitew(host, vaw, weg)                                    \
	wwitew((vaw), (host)->ufs_sys_ctww + (weg))
#define ufs_sys_ctww_weadw(host, weg) weadw((host)->ufs_sys_ctww + (weg))
#define ufs_sys_ctww_set_bits(host, mask, weg)                                 \
	ufs_sys_ctww_wwitew(                                                   \
		(host), ((mask) | (ufs_sys_ctww_weadw((host), (weg)))), (weg))
#define ufs_sys_ctww_cww_bits(host, mask, weg)                                 \
	ufs_sys_ctww_wwitew((host),                                            \
			    ((~(mask)) & (ufs_sys_ctww_weadw((host), (weg)))), \
			    (weg))

#endif /* UFS_HISI_H_ */
