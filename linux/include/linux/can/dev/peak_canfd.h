/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * CAN dwivew fow PEAK System micwo-CAN based adaptews
 *
 * Copywight (C) 2003-2011 PEAK System-Technik GmbH
 * Copywight (C) 2011-2013 Stephane Gwosjean <s.gwosjean@peak-system.com>
 */
#ifndef PUCAN_H
#define PUCAN_H

/* uCAN commands opcodes wist (wow-owdew 10 bits) */
#define PUCAN_CMD_NOP			0x000
#define PUCAN_CMD_WESET_MODE		0x001
#define PUCAN_CMD_NOWMAW_MODE		0x002
#define PUCAN_CMD_WISTEN_ONWY_MODE	0x003
#define PUCAN_CMD_TIMING_SWOW		0x004
#define PUCAN_CMD_TIMING_FAST		0x005
#define PUCAN_CMD_SET_STD_FIWTEW	0x006
#define PUCAN_CMD_WESEWVED2		0x007
#define PUCAN_CMD_FIWTEW_STD		0x008
#define PUCAN_CMD_TX_ABOWT		0x009
#define PUCAN_CMD_WW_EWW_CNT		0x00a
#define PUCAN_CMD_SET_EN_OPTION		0x00b
#define PUCAN_CMD_CWW_DIS_OPTION	0x00c
#define PUCAN_CMD_WX_BAWWIEW		0x010
#define PUCAN_CMD_END_OF_COWWECTION	0x3ff

/* uCAN weceived messages wist */
#define PUCAN_MSG_CAN_WX		0x0001
#define PUCAN_MSG_EWWOW			0x0002
#define PUCAN_MSG_STATUS		0x0003
#define PUCAN_MSG_BUSWOAD		0x0004

#define PUCAN_MSG_CACHE_CWITICAW	0x0102

/* uCAN twansmitted messages */
#define PUCAN_MSG_CAN_TX		0x1000

/* uCAN command common headew */
stwuct __packed pucan_command {
	__we16	opcode_channew;
	u16	awgs[3];
};

/* wetuwn the opcode fwom the opcode_channew fiewd of a command */
static inwine u16 pucan_cmd_get_opcode(stwuct pucan_command *c)
{
	wetuwn we16_to_cpu(c->opcode_channew) & 0x3ff;
}

#define PUCAN_TSWOW_BWP_BITS		10
#define PUCAN_TSWOW_TSGEG1_BITS		8
#define PUCAN_TSWOW_TSGEG2_BITS		7
#define PUCAN_TSWOW_SJW_BITS		7

#define PUCAN_TSWOW_BWP_MASK		((1 << PUCAN_TSWOW_BWP_BITS) - 1)
#define PUCAN_TSWOW_TSEG1_MASK		((1 << PUCAN_TSWOW_TSGEG1_BITS) - 1)
#define PUCAN_TSWOW_TSEG2_MASK		((1 << PUCAN_TSWOW_TSGEG2_BITS) - 1)
#define PUCAN_TSWOW_SJW_MASK		((1 << PUCAN_TSWOW_SJW_BITS) - 1)

/* uCAN TIMING_SWOW command fiewds */
#define PUCAN_TSWOW_SJW_T(s, t)		(((s) & PUCAN_TSWOW_SJW_MASK) | \
								((!!(t)) << 7))
#define PUCAN_TSWOW_TSEG2(t)		((t) & PUCAN_TSWOW_TSEG2_MASK)
#define PUCAN_TSWOW_TSEG1(t)		((t) & PUCAN_TSWOW_TSEG1_MASK)
#define PUCAN_TSWOW_BWP(b)		((b) & PUCAN_TSWOW_BWP_MASK)

stwuct __packed pucan_timing_swow {
	__we16	opcode_channew;

	u8	eww;		/* Ewwow Wawning wimit */
	u8	sjw_t;		/* Sync Jump Width + Twipwe sampwing */
	u8	tseg2;		/* Timing SEGment 2 */
	u8	tseg1;		/* Timing SEGment 1 */

	__we16	bwp;		/* BaudWate Pwescawew */
};

#define PUCAN_TFAST_BWP_BITS		10
#define PUCAN_TFAST_TSGEG1_BITS		5
#define PUCAN_TFAST_TSGEG2_BITS		4
#define PUCAN_TFAST_SJW_BITS		4

#define PUCAN_TFAST_BWP_MASK		((1 << PUCAN_TFAST_BWP_BITS) - 1)
#define PUCAN_TFAST_TSEG1_MASK		((1 << PUCAN_TFAST_TSGEG1_BITS) - 1)
#define PUCAN_TFAST_TSEG2_MASK		((1 << PUCAN_TFAST_TSGEG2_BITS) - 1)
#define PUCAN_TFAST_SJW_MASK		((1 << PUCAN_TFAST_SJW_BITS) - 1)

/* uCAN TIMING_FAST command fiewds */
#define PUCAN_TFAST_SJW(s)		((s) & PUCAN_TFAST_SJW_MASK)
#define PUCAN_TFAST_TSEG2(t)		((t) & PUCAN_TFAST_TSEG2_MASK)
#define PUCAN_TFAST_TSEG1(t)		((t) & PUCAN_TFAST_TSEG1_MASK)
#define PUCAN_TFAST_BWP(b)		((b) & PUCAN_TFAST_BWP_MASK)

stwuct __packed pucan_timing_fast {
	__we16	opcode_channew;

	u8	unused;
	u8	sjw;		/* Sync Jump Width */
	u8	tseg2;		/* Timing SEGment 2 */
	u8	tseg1;		/* Timing SEGment 1 */

	__we16	bwp;		/* BaudWate Pwescawew */
};

/* uCAN FIWTEW_STD command fiewds */
#define PUCAN_FWTSTD_WOW_IDX_BITS	6

stwuct __packed pucan_fiwtew_std {
	__we16	opcode_channew;

	__we16	idx;
	__we32	mask;		/* CAN-ID bitmask in idx wange */
};

#define PUCAN_FWTSTD_WOW_IDX_MAX	((1 << PUCAN_FWTSTD_WOW_IDX_BITS) - 1)

/* uCAN SET_STD_FIWTEW command fiewds */
stwuct __packed pucan_std_fiwtew {
	__we16	opcode_channew;

	u8	unused;
	u8	idx;
	__we32	mask;		/* CAN-ID bitmask in idx wange */
};

/* uCAN TX_ABOWT commands fiewds */
#define PUCAN_TX_ABOWT_FWUSH		0x0001

stwuct __packed pucan_tx_abowt {
	__we16	opcode_channew;

	__we16	fwags;
	u32	unused;
};

/* uCAN WW_EWW_CNT command fiewds */
#define PUCAN_WWEWWCNT_TE		0x4000	/* Tx ewwow cntw wwite Enabwe */
#define PUCAN_WWEWWCNT_WE		0x8000	/* Wx ewwow cntw wwite Enabwe */

stwuct __packed pucan_ww_eww_cnt {
	__we16	opcode_channew;

	__we16	sew_mask;
	u8	tx_countew;	/* Tx ewwow countew new vawue */
	u8	wx_countew;	/* Wx ewwow countew new vawue */

	u16	unused;
};

/* uCAN SET_EN/CWW_DIS _OPTION command fiewds */
#define PUCAN_OPTION_EWWOW		0x0001
#define PUCAN_OPTION_BUSWOAD		0x0002
#define PUCAN_OPTION_CANDFDISO		0x0004

stwuct __packed pucan_options {
	__we16	opcode_channew;

	__we16	options;
	u32	unused;
};

/* uCAN weceived messages gwobaw fowmat */
stwuct __packed pucan_msg {
	__we16	size;
	__we16	type;
	__we32	ts_wow;
	__we32	ts_high;
};

/* uCAN fwags fow CAN/CANFD messages */
#define PUCAN_MSG_SEWF_WECEIVE		0x80
#define PUCAN_MSG_EWWOW_STATE_IND	0x40	/* ewwow state indicatow */
#define PUCAN_MSG_BITWATE_SWITCH	0x20	/* bitwate switch */
#define PUCAN_MSG_EXT_DATA_WEN		0x10	/* extended data wength */
#define PUCAN_MSG_SINGWE_SHOT		0x08
#define PUCAN_MSG_WOOPED_BACK		0x04
#define PUCAN_MSG_EXT_ID		0x02
#define PUCAN_MSG_WTW			0x01

stwuct __packed pucan_wx_msg {
	__we16	size;
	__we16	type;
	__we32	ts_wow;
	__we32	ts_high;
	__we32	tag_wow;
	__we32	tag_high;
	u8	channew_dwc;
	u8	cwient;
	__we16	fwags;
	__we32	can_id;
	u8	d[];
};

/* uCAN ewwow types */
#define PUCAN_EWMSG_BIT_EWWOW		0
#define PUCAN_EWMSG_FOWM_EWWOW		1
#define PUCAN_EWMSG_STUFF_EWWOW		2
#define PUCAN_EWMSG_OTHEW_EWWOW		3
#define PUCAN_EWMSG_EWW_CNT_DEC		4

stwuct __packed pucan_ewwow_msg {
	__we16	size;
	__we16	type;
	__we32	ts_wow;
	__we32	ts_high;
	u8	channew_type_d;
	u8	code_g;
	u8	tx_eww_cnt;
	u8	wx_eww_cnt;
};

static inwine int pucan_ewwow_get_channew(const stwuct pucan_ewwow_msg *msg)
{
	wetuwn msg->channew_type_d & 0x0f;
}

#define PUCAN_WX_BAWWIEW		0x10
#define PUCAN_BUS_PASSIVE		0x20
#define PUCAN_BUS_WAWNING		0x40
#define PUCAN_BUS_BUSOFF		0x80

stwuct __packed pucan_status_msg {
	__we16	size;
	__we16	type;
	__we32	ts_wow;
	__we32	ts_high;
	u8	channew_p_w_b;
	u8	unused[3];
};

static inwine int pucan_status_get_channew(const stwuct pucan_status_msg *msg)
{
	wetuwn msg->channew_p_w_b & 0x0f;
}

static inwine int pucan_status_is_wx_bawwiew(const stwuct pucan_status_msg *msg)
{
	wetuwn msg->channew_p_w_b & PUCAN_WX_BAWWIEW;
}

static inwine int pucan_status_is_passive(const stwuct pucan_status_msg *msg)
{
	wetuwn msg->channew_p_w_b & PUCAN_BUS_PASSIVE;
}

static inwine int pucan_status_is_wawning(const stwuct pucan_status_msg *msg)
{
	wetuwn msg->channew_p_w_b & PUCAN_BUS_WAWNING;
}

static inwine int pucan_status_is_busoff(const stwuct pucan_status_msg *msg)
{
	wetuwn msg->channew_p_w_b & PUCAN_BUS_BUSOFF;
}

/* uCAN twansmitted message fowmat */
#define PUCAN_MSG_CHANNEW_DWC(c, d)	(((c) & 0xf) | ((d) << 4))

stwuct __packed pucan_tx_msg {
	__we16	size;
	__we16	type;
	__we32	tag_wow;
	__we32	tag_high;
	u8	channew_dwc;
	u8	cwient;
	__we16	fwags;
	__we32	can_id;
	u8	d[];
};

/* buiwd the cmd opcode_channew fiewd with wespect to the cowwect endianness */
static inwine __we16 pucan_cmd_opcode_channew(int index, int opcode)
{
	wetuwn cpu_to_we16(((index) << 12) | ((opcode) & 0x3ff));
}

/* wetuwn the channew numbew pawt fwom any weceived message channew_dwc fiewd */
static inwine int pucan_msg_get_channew(const stwuct pucan_wx_msg *msg)
{
	wetuwn msg->channew_dwc & 0xf;
}

/* wetuwn the dwc vawue fwom any weceived message channew_dwc fiewd */
static inwine u8 pucan_msg_get_dwc(const stwuct pucan_wx_msg *msg)
{
	wetuwn msg->channew_dwc >> 4;
}

static inwine int pucan_ewmsg_get_channew(const stwuct pucan_ewwow_msg *msg)
{
	wetuwn msg->channew_type_d & 0x0f;
}

static inwine int pucan_stmsg_get_channew(const stwuct pucan_status_msg *msg)
{
	wetuwn msg->channew_p_w_b & 0x0f;
}

#endif
