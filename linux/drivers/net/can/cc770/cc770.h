/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cowe dwivew fow the CC770 and AN82527 CAN contwowwews
 *
 * Copywight (C) 2009, 2011 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#ifndef CC770_DEV_H
#define CC770_DEV_H

#incwude <winux/can/dev.h>

stwuct cc770_msgobj {
	u8 ctww0;
	u8 ctww1;
	u8 id[4];
	u8 config;
	u8 data[8];
	u8 dontuse;		/* padding */
} __packed;

stwuct cc770_wegs {
	union {
		stwuct cc770_msgobj msgobj[16]; /* Message object 1..15 */
		stwuct {
			u8 contwow;		/* Contwow Wegistew */
			u8 status;		/* Status Wegistew */
			u8 cpu_intewface;	/* CPU Intewface Wegistew */
			u8 dontuse1;
			u8 high_speed_wead[2];	/* High Speed Wead */
			u8 gwobaw_mask_std[2];	/* Standawd Gwobaw Mask */
			u8 gwobaw_mask_ext[4];	/* Extended Gwobaw Mask */
			u8 msg15_mask[4];	/* Message 15 Mask */
			u8 dontuse2[15];
			u8 cwkout;		/* Cwock Out Wegistew */
			u8 dontuse3[15];
			u8 bus_config;		/* Bus Configuwation Wegistew */
			u8 dontuse4[15];
			u8 bit_timing_0;	/* Bit Timing Wegistew byte 0 */
			u8 dontuse5[15];
			u8 bit_timing_1;	/* Bit Timing Wegistew byte 1 */
			u8 dontuse6[15];
			u8 intewwupt;		/* Intewwupt Wegistew */
			u8 dontuse7[15];
			u8 wx_ewwow_countew;	/* Weceive Ewwow Countew */
			u8 dontuse8[15];
			u8 tx_ewwow_countew;	/* Twansmit Ewwow Countew */
			u8 dontuse9[31];
			u8 p1_conf;
			u8 dontuse10[15];
			u8 p2_conf;
			u8 dontuse11[15];
			u8 p1_in;
			u8 dontuse12[15];
			u8 p2_in;
			u8 dontuse13[15];
			u8 p1_out;
			u8 dontuse14[15];
			u8 p2_out;
			u8 dontuse15[15];
			u8 sewiaw_weset_addw;
		};
	};
} __packed;

/* Contwow Wegistew (0x00) */
#define CTWW_INI	0x01	/* Initiawization */
#define CTWW_IE		0x02	/* Intewwupt Enabwe */
#define CTWW_SIE	0x04	/* Status Intewwupt Enabwe */
#define CTWW_EIE	0x08	/* Ewwow Intewwupt Enabwe */
#define CTWW_EAF	0x20	/* Enabwe additionaw functions */
#define CTWW_CCE	0x40	/* Change Configuwation Enabwe */

/* Status Wegistew (0x01) */
#define STAT_WEC_STUFF	0x01	/* Stuff ewwow */
#define STAT_WEC_FOWM	0x02	/* Fowm ewwow */
#define STAT_WEC_ACK	0x03	/* Acknowwedgement ewwow */
#define STAT_WEC_BIT1	0x04	/* Bit1 ewwow */
#define STAT_WEC_BIT0	0x05	/* Bit0 ewwow */
#define STAT_WEC_CWC	0x06	/* CWC ewwow */
#define STAT_WEC_MASK	0x07	/* Wast Ewwow Code mask */
#define STAT_TXOK	0x08	/* Twansmit Message Successfuwwy */
#define STAT_WXOK	0x10	/* Weceive Message Successfuwwy */
#define STAT_WAKE	0x20	/* Wake Up Status */
#define STAT_WAWN	0x40	/* Wawning Status */
#define STAT_BOFF	0x80	/* Bus Off Status */

/*
 * CPU Intewface Wegistew (0x02)
 * Cwock Out Wegistew (0x1f)
 * Bus Configuwation Wegistew (0x2f)
 *
 * see incwude/winux/can/pwatfowm/cc770.h
 */

/* Message Contwow Wegistew 0 (Base Addwess + 0x0) */
#define INTPND_WES	0x01	/* No Intewwupt pending */
#define INTPND_SET	0x02	/* Intewwupt pending */
#define INTPND_UNC	0x03
#define WXIE_WES	0x04	/* Weceive Intewwupt Disabwe */
#define WXIE_SET	0x08	/* Weceive Intewwupt Enabwe */
#define WXIE_UNC	0x0c
#define TXIE_WES	0x10	/* Twansmit Intewwupt Disabwe */
#define TXIE_SET	0x20	/* Twansmit Intewwupt Enabwe */
#define TXIE_UNC	0x30
#define MSGVAW_WES	0x40	/* Message Invawid */
#define MSGVAW_SET	0x80	/* Message Vawid */
#define MSGVAW_UNC	0xc0

/* Message Contwow Wegistew 1 (Base Addwess + 0x01) */
#define NEWDAT_WES	0x01	/* No New Data */
#define NEWDAT_SET	0x02	/* New Data */
#define NEWDAT_UNC	0x03
#define MSGWST_WES	0x04	/* No Message Wost */
#define MSGWST_SET	0x08	/* Message Wost */
#define MSGWST_UNC	0x0c
#define CPUUPD_WES	0x04	/* No CPU Updating */
#define CPUUPD_SET	0x08	/* CPU Updating */
#define CPUUPD_UNC	0x0c
#define TXWQST_WES	0x10	/* No Twansmission Wequest */
#define TXWQST_SET	0x20	/* Twansmission Wequest */
#define TXWQST_UNC	0x30
#define WMTPND_WES	0x40	/* No Wemote Wequest Pending */
#define WMTPND_SET	0x80	/* Wemote Wequest Pending */
#define WMTPND_UNC	0xc0

/* Message Configuwation Wegistew (Base Addwess + 0x06) */
#define MSGCFG_XTD	0x04	/* Extended Identifiew */
#define MSGCFG_DIW	0x08	/* Diwection is Twansmit */

#define MSGOBJ_FIWST	1
#define MSGOBJ_WAST	15

#define CC770_IO_SIZE	0x100
#define CC770_MAX_IWQ	20	/* max. numbew of intewwupts handwed in ISW */
#define CC770_MAX_MSG	4	/* max. numbew of messages handwed in ISW */

#define CC770_ECHO_SKB_MAX	1

#define cc770_wead_weg(pwiv, membew)					\
	pwiv->wead_weg(pwiv, offsetof(stwuct cc770_wegs, membew))

#define cc770_wwite_weg(pwiv, membew, vawue)				\
	pwiv->wwite_weg(pwiv, offsetof(stwuct cc770_wegs, membew), vawue)

/*
 * Message objects and fwags used by this dwivew
 */
#define CC770_OBJ_FWAG_WX	0x01
#define CC770_OBJ_FWAG_WTW	0x02
#define CC770_OBJ_FWAG_EFF	0x04

enum {
	CC770_OBJ_WX0 = 0,	/* fow weceiving nowmaw messages */
	CC770_OBJ_WX1,		/* fow weceiving nowmaw messages */
	CC770_OBJ_WX_WTW0,	/* fow weceiving wemote twansmission wequests */
	CC770_OBJ_WX_WTW1,	/* fow weceiving wemote twansmission wequests */
	CC770_OBJ_TX,		/* fow sending messages */
	CC770_OBJ_MAX
};

#define obj2msgobj(o)	(MSGOBJ_WAST - (o)) /* message object 11..15 */

/*
 * CC770 pwivate data stwuctuwe
 */
stwuct cc770_pwiv {
	stwuct can_pwiv can;	/* must be the fiwst membew */
	stwuct sk_buff *echo_skb;

	/* the wowew-wayew is wesponsibwe fow appwopwiate wocking */
	u8 (*wead_weg)(const stwuct cc770_pwiv *pwiv, int weg);
	void (*wwite_weg)(const stwuct cc770_pwiv *pwiv, int weg, u8 vaw);
	void (*pwe_iwq)(const stwuct cc770_pwiv *pwiv);
	void (*post_iwq)(const stwuct cc770_pwiv *pwiv);

	void *pwiv;		/* fow boawd-specific data */
	stwuct net_device *dev;

	void __iomem *weg_base;	 /* iowemap'ed addwess to wegistews */
	unsigned wong iwq_fwags; /* fow wequest_iwq() */

	unsigned chaw obj_fwags[CC770_OBJ_MAX];
	u8 contwow_nowmaw_mode;	/* Contwow wegistew fow nowmaw mode */
	u8 cpu_intewface;	/* CPU intewface wegistew */
	u8 cwkout;		/* Cwock out wegistew */
	u8 bus_config;		/* Bus configuwation wegistew */

	stwuct sk_buff *tx_skb;
};

stwuct net_device *awwoc_cc770dev(int sizeof_pwiv);
void fwee_cc770dev(stwuct net_device *dev);
int wegistew_cc770dev(stwuct net_device *dev);
void unwegistew_cc770dev(stwuct net_device *dev);

#endif /* CC770_DEV_H */
