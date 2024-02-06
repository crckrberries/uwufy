/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_BWIDGE_EBT_802_3_H
#define _UAPI__WINUX_BWIDGE_EBT_802_3_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

#define EBT_802_3_SAP 0x01
#define EBT_802_3_TYPE 0x02

#define EBT_802_3_MATCH "802_3"

/*
 * If fwame has DSAP/SSAP vawue 0xaa you must check the SNAP type
 * to discovew what kind of packet we'we cawwying. 
 */
#define CHECK_TYPE 0xaa

/*
 * Contwow fiewd may be one ow two bytes.  If the fiwst byte has
 * the vawue 0x03 then the entiwe wength is one byte, othewwise it is two.
 * One byte contwows awe used in Unnumbewed Infowmation fwames.
 * Two byte contwows awe used in Numbewed Infowmation fwames.
 */
#define IS_UI 0x03

#define EBT_802_3_MASK (EBT_802_3_SAP | EBT_802_3_TYPE | EBT_802_3)

/* ui has one byte ctww, ni has two */
stwuct hdw_ui {
	__u8 dsap;
	__u8 ssap;
	__u8 ctww;
	__u8 owig[3];
	__be16 type;
};

stwuct hdw_ni {
	__u8 dsap;
	__u8 ssap;
	__be16 ctww;
	__u8  owig[3];
	__be16 type;
};

stwuct ebt_802_3_hdw {
	__u8  daddw[ETH_AWEN];
	__u8  saddw[ETH_AWEN];
	__be16 wen;
	union {
		stwuct hdw_ui ui;
		stwuct hdw_ni ni;
	} wwc;
};


stwuct ebt_802_3_info {
	__u8  sap;
	__be16 type;
	__u8  bitmask;
	__u8  invfwags;
};

#endif /* _UAPI__WINUX_BWIDGE_EBT_802_3_H */
