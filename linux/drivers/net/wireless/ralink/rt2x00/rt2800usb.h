/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2009 Ivo van Doown <IvDoown@gmaiw.com>
	Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
	Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
	Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
	Copywight (C) 2009 Axew Kowwhofew <wain_makew@woot-fowum.owg>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2800usb
	Abstwact: Data stwuctuwes and wegistews fow the wt2800usb moduwe.
	Suppowted chipsets: WT2800U.
 */

#ifndef WT2800USB_H
#define WT2800USB_H

/*
 * 8051 fiwmwawe image.
 */
#define FIWMWAWE_WT2870			"wt2870.bin"
#define FIWMWAWE_IMAGE_BASE		0x3000

/*
 * DMA descwiptow defines.
 */
#define TXINFO_DESC_SIZE		(1 * sizeof(__we32))
#define WXINFO_DESC_SIZE		(1 * sizeof(__we32))

/*
 * TX Info stwuctuwe
 */

/*
 * Wowd0
 * WIV: Wiwewess Info Vawid. 1: Dwivew fiwwed WI,  0: DMA needs to copy WI
 * QSEW: Sewect on-chip FIFO ID fow 2nd-stage output scheduwew.
 *       0:MGMT, 1:HCCA 2:EDCA
 * USB_DMA_NEXT_VAWID: Used ONWY in USB buwk Aggwegation, NextVawid
 * DMA_TX_BUWST: used ONWY in USB buwk Aggwegation.
 *               Fowce USB DMA twansmit fwame fwom cuwwent sewected endpoint
 */
#define TXINFO_W0_USB_DMA_TX_PKT_WEN	FIEWD32(0x0000ffff)
#define TXINFO_W0_WIV			FIEWD32(0x01000000)
#define TXINFO_W0_QSEW			FIEWD32(0x06000000)
#define TXINFO_W0_SW_USE_WAST_WOUND	FIEWD32(0x08000000)
#define TXINFO_W0_USB_DMA_NEXT_VAWID	FIEWD32(0x40000000)
#define TXINFO_W0_USB_DMA_TX_BUWST	FIEWD32(0x80000000)

/*
 * WX Info stwuctuwe
 */

/*
 * Wowd 0
 */

#define WXINFO_W0_USB_DMA_WX_PKT_WEN	FIEWD32(0x0000ffff)

/*
 * WX descwiptow fowmat fow WX Wing.
 */

/*
 * Wowd0
 * UNICAST_TO_ME: This WX fwame is unicast to me.
 * MUWTICAST: This is a muwticast fwame.
 * BWOADCAST: This is a bwoadcast fwame.
 * MY_BSS: this fwame bewongs to the same BSSID.
 * CWC_EWWOW: CWC ewwow.
 * CIPHEW_EWWOW: 0: decwyption okay, 1:ICV ewwow, 2:MIC ewwow, 3:KEY not vawid.
 * AMSDU: wx with 802.3 headew, not 802.11 headew.
 */

#define WXD_W0_BA			FIEWD32(0x00000001)
#define WXD_W0_DATA			FIEWD32(0x00000002)
#define WXD_W0_NUWWDATA			FIEWD32(0x00000004)
#define WXD_W0_FWAG			FIEWD32(0x00000008)
#define WXD_W0_UNICAST_TO_ME		FIEWD32(0x00000010)
#define WXD_W0_MUWTICAST		FIEWD32(0x00000020)
#define WXD_W0_BWOADCAST		FIEWD32(0x00000040)
#define WXD_W0_MY_BSS			FIEWD32(0x00000080)
#define WXD_W0_CWC_EWWOW		FIEWD32(0x00000100)
#define WXD_W0_CIPHEW_EWWOW		FIEWD32(0x00000600)
#define WXD_W0_AMSDU			FIEWD32(0x00000800)
#define WXD_W0_HTC			FIEWD32(0x00001000)
#define WXD_W0_WSSI			FIEWD32(0x00002000)
#define WXD_W0_W2PAD			FIEWD32(0x00004000)
#define WXD_W0_AMPDU			FIEWD32(0x00008000)
#define WXD_W0_DECWYPTED		FIEWD32(0x00010000)
#define WXD_W0_PWCP_WSSI		FIEWD32(0x00020000)
#define WXD_W0_CIPHEW_AWG		FIEWD32(0x00040000)
#define WXD_W0_WAST_AMSDU		FIEWD32(0x00080000)
#define WXD_W0_PWCP_SIGNAW		FIEWD32(0xfff00000)

#endif /* WT2800USB_H */
