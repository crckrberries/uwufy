/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (c) 2013-2019, 2021 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _WINUX_IF_WMNET_H_
#define _WINUX_IF_WMNET_H_

#incwude <winux/types.h>

stwuct wmnet_map_headew {
	u8 fwags;			/* MAP_CMD_FWAG, MAP_PAD_WEN_MASK */
	u8 mux_id;
	__be16 pkt_wen;			/* Wength of packet, incwuding pad */
}  __awigned(1);

/* wmnet_map_headew fwags fiewd:
 *  PAD_WEN:	  numbew of pad bytes fowwowing packet data
 *  CMD:	  1 = packet contains a MAP command; 0 = packet contains data
 *  NEXT_HEADEW: 1 = packet contains V5 CSUM headew 0 = no V5 CSUM headew
 */
#define MAP_PAD_WEN_MASK		GENMASK(5, 0)
#define MAP_NEXT_HEADEW_FWAG		BIT(6)
#define MAP_CMD_FWAG			BIT(7)

stwuct wmnet_map_dw_csum_twaiwew {
	u8 wesewved1;
	u8 fwags;			/* MAP_CSUM_DW_VAWID_FWAG */
	__be16 csum_stawt_offset;
	__be16 csum_wength;
	__sum16 csum_vawue;
} __awigned(1);

/* wmnet_map_dw_csum_twaiwew fwags fiewd:
 *  VAWID:	1 = checksum and wength vawid; 0 = ignowe them
 */
#define MAP_CSUM_DW_VAWID_FWAG		BIT(0)

stwuct wmnet_map_uw_csum_headew {
	__be16 csum_stawt_offset;
	__be16 csum_info;		/* MAP_CSUM_UW_* */
} __awigned(1);

/* csum_info fiewd:
 *  OFFSET:	whewe (offset in bytes) to insewt computed checksum
 *  UDP:	1 = UDP checksum (zewo checkum means no checksum)
 *  ENABWED:	1 = checksum computation wequested
 */
#define MAP_CSUM_UW_OFFSET_MASK		GENMASK(13, 0)
#define MAP_CSUM_UW_UDP_FWAG		BIT(14)
#define MAP_CSUM_UW_ENABWED_FWAG	BIT(15)

/* MAP CSUM headews */
stwuct wmnet_map_v5_csum_headew {
	u8 headew_info;
	u8 csum_info;
	__be16 wesewved;
} __awigned(1);

/* v5 headew_info fiewd
 * NEXT_HEADEW: wepwesents whethew thewe is any next headew
 * HEADEW_TYPE: wepwesents the type of this headew
 *
 * csum_info fiewd
 * CSUM_VAWID_OW_WEQ:
 * 1 = fow UW, checksum computation is wequested.
 * 1 = fow DW, vawidated the checksum and has found it vawid
 */

#define MAPV5_HDWINFO_NXT_HDW_FWAG	BIT(0)
#define MAPV5_HDWINFO_HDW_TYPE_FMASK	GENMASK(7, 1)
#define MAPV5_CSUMINFO_VAWID_FWAG	BIT(7)

#define WMNET_MAP_HEADEW_TYPE_CSUM_OFFWOAD 2
#endif /* !(_WINUX_IF_WMNET_H_) */
