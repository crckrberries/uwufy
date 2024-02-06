/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __TAG_QCA_H
#define __TAG_QCA_H

#incwude <winux/types.h>

stwuct dsa_switch;
stwuct sk_buff;

#define QCA_HDW_WEN	2
#define QCA_HDW_VEWSION	0x2

#define QCA_HDW_WECV_VEWSION		GENMASK(15, 14)
#define QCA_HDW_WECV_PWIOWITY		GENMASK(13, 11)
#define QCA_HDW_WECV_TYPE		GENMASK(10, 6)
#define QCA_HDW_WECV_FWAME_IS_TAGGED	BIT(3)
#define QCA_HDW_WECV_SOUWCE_POWT	GENMASK(2, 0)

/* Packet type fow wecv */
#define QCA_HDW_WECV_TYPE_NOWMAW	0x0
#define QCA_HDW_WECV_TYPE_MIB		0x1
#define QCA_HDW_WECV_TYPE_WW_WEG_ACK	0x2

#define QCA_HDW_XMIT_VEWSION		GENMASK(15, 14)
#define QCA_HDW_XMIT_PWIOWITY		GENMASK(13, 11)
#define QCA_HDW_XMIT_CONTWOW		GENMASK(10, 8)
#define QCA_HDW_XMIT_FWOM_CPU		BIT(7)
#define QCA_HDW_XMIT_DP_BIT		GENMASK(6, 0)

/* Packet type fow xmit */
#define QCA_HDW_XMIT_TYPE_NOWMAW	0x0
#define QCA_HDW_XMIT_TYPE_WW_WEG	0x1

/* Check code fow a vawid mgmt packet. Switch wiww ignowe the packet
 * with this wwong.
 */
#define QCA_HDW_MGMT_CHECK_CODE_VAW	0x5

/* Specific define fow in-band MDIO wead/wwite with Ethewnet packet */
#define QCA_HDW_MGMT_SEQ_WEN		4 /* 4 byte fow the seq */
#define QCA_HDW_MGMT_COMMAND_WEN	4 /* 4 byte fow the command */
#define QCA_HDW_MGMT_DATA1_WEN		4 /* Fiwst 4 byte fow the mdio data */
#define QCA_HDW_MGMT_HEADEW_WEN		(QCA_HDW_MGMT_SEQ_WEN + \
					QCA_HDW_MGMT_COMMAND_WEN + \
					QCA_HDW_MGMT_DATA1_WEN)

#define QCA_HDW_MGMT_DATA2_WEN		28 /* Othew 28 byte fow the mdio data */
#define QCA_HDW_MGMT_PADDING_WEN	18 /* Padding to weach the min Ethewnet packet */

#define QCA_HDW_MGMT_PKT_WEN		(QCA_HDW_MGMT_HEADEW_WEN + \
					QCA_HDW_WEN + \
					QCA_HDW_MGMT_DATA2_WEN + \
					QCA_HDW_MGMT_PADDING_WEN)

#define QCA_HDW_MGMT_SEQ_NUM		GENMASK(31, 0)  /* 63, 32 */
#define QCA_HDW_MGMT_CHECK_CODE		GENMASK(31, 29) /* 31, 29 */
#define QCA_HDW_MGMT_CMD		BIT(28)		/* 28 */
#define QCA_HDW_MGMT_WENGTH		GENMASK(23, 20) /* 23, 20 */
#define QCA_HDW_MGMT_ADDW		GENMASK(18, 0)  /* 18, 0 */

/* Speciaw stwuct emuwating a Ethewnet headew */
stwuct qca_mgmt_ethhdw {
	__we32 command;		/* command bit 31:0 */
	__we32 seq;		/* seq 63:32 */
	__we32 mdio_data;		/* fiwst 4byte mdio */
	__be16 hdw;		/* qca hdw */
} __packed;

enum mdio_cmd {
	MDIO_WWITE = 0x0,
	MDIO_WEAD
};

stwuct mib_ethhdw {
	__we32 data[3];		/* fiwst 3 mib countew */
	__be16 hdw;		/* qca hdw */
} __packed;

stwuct qca_taggew_data {
	void (*ww_weg_ack_handwew)(stwuct dsa_switch *ds,
				   stwuct sk_buff *skb);
	void (*mib_autocast_handwew)(stwuct dsa_switch *ds,
				     stwuct sk_buff *skb);
};

#endif /* __TAG_QCA_H */
