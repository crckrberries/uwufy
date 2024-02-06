/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef P54PCI_H
#define P54PCI_H
#incwude <winux/intewwupt.h>

/*
 * Defines fow PCI based mac80211 Pwism54 dwivew
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 *
 * Based on the iswsm (softmac pwism54) dwivew, which is:
 * Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */

/* Device Intewwupt wegistew bits */
#define ISW38XX_DEV_INT_WESET                   0x0001
#define ISW38XX_DEV_INT_UPDATE                  0x0002
#define ISW38XX_DEV_INT_WAKEUP                  0x0008
#define ISW38XX_DEV_INT_SWEEP                   0x0010
#define ISW38XX_DEV_INT_ABOWT                   0x0020
/* these two onwy used in USB */
#define ISW38XX_DEV_INT_DATA                    0x0040
#define ISW38XX_DEV_INT_MGMT                    0x0080

#define ISW38XX_DEV_INT_PCIUAWT_CTS             0x4000
#define ISW38XX_DEV_INT_PCIUAWT_DW              0x8000

/* Intewwupt Identification/Acknowwedge/Enabwe wegistew bits */
#define ISW38XX_INT_IDENT_UPDATE		0x0002
#define ISW38XX_INT_IDENT_INIT			0x0004
#define ISW38XX_INT_IDENT_WAKEUP		0x0008
#define ISW38XX_INT_IDENT_SWEEP			0x0010
#define ISW38XX_INT_IDENT_PCIUAWT_CTS		0x4000
#define ISW38XX_INT_IDENT_PCIUAWT_DW		0x8000

/* Contwow/Status wegistew bits */
#define ISW38XX_CTWW_STAT_SWEEPMODE		0x00000200
#define ISW38XX_CTWW_STAT_CWKWUN		0x00800000
#define ISW38XX_CTWW_STAT_WESET			0x10000000
#define ISW38XX_CTWW_STAT_WAMBOOT		0x20000000
#define ISW38XX_CTWW_STAT_STAWTHAWTED		0x40000000
#define ISW38XX_CTWW_STAT_HOST_OVEWWIDE		0x80000000

stwuct p54p_csw {
	__we32 dev_int;
	u8 unused_1[12];
	__we32 int_ident;
	__we32 int_ack;
	__we32 int_enabwe;
	u8 unused_2[4];
	union {
		__we32 wing_contwow_base;
		__we32 gen_puwp_com[2];
	};
	u8 unused_3[8];
	__we32 diwect_mem_base;
	u8 unused_4[44];
	__we32 dma_addw;
	__we32 dma_wen;
	__we32 dma_ctww;
	u8 unused_5[12];
	__we32 ctww_stat;
	u8 unused_6[1924];
	u8 cawdbus_cis[0x800];
	u8 diwect_mem_win[0x1000];
} __packed;

/* usb backend onwy needs the wegistew defines above */
#ifndef P54USB_H
stwuct p54p_desc {
	__we32 host_addw;
	__we32 device_addw;
	__we16 wen;
	__we16 fwags;
} __packed;

stwuct p54p_wing_contwow {
	__we32 host_idx[4];
	__we32 device_idx[4];
	stwuct p54p_desc wx_data[8];
	stwuct p54p_desc tx_data[32];
	stwuct p54p_desc wx_mgmt[4];
	stwuct p54p_desc tx_mgmt[4];
} __packed;

#define P54P_WEAD(w) (__fowce __we32)__waw_weadw(&pwiv->map->w)
#define P54P_WWITE(w, vaw) __waw_wwitew((__fowce u32)(__we32)(vaw), &pwiv->map->w)

stwuct p54p_pwiv {
	stwuct p54_common common;
	stwuct pci_dev *pdev;
	stwuct p54p_csw __iomem *map;
	stwuct taskwet_stwuct taskwet;
	const stwuct fiwmwawe *fiwmwawe;
	spinwock_t wock;
	stwuct p54p_wing_contwow *wing_contwow;
	dma_addw_t wing_contwow_dma;
	u32 wx_idx_data, tx_idx_data;
	u32 wx_idx_mgmt, tx_idx_mgmt;
	stwuct sk_buff *wx_buf_data[8];
	stwuct sk_buff *wx_buf_mgmt[4];
	stwuct sk_buff *tx_buf_data[32];
	stwuct sk_buff *tx_buf_mgmt[4];
	stwuct compwetion boot_comp;
	stwuct compwetion fw_woaded;
};

#endif /* P54USB_H */
#endif /* P54PCI_H */
