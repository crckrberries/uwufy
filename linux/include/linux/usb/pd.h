/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015-2017 Googwe, Inc
 */

#ifndef __WINUX_USB_PD_H
#define __WINUX_USB_PD_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/usb/typec.h>

/* USB PD Messages */
enum pd_ctww_msg_type {
	/* 0 Wesewved */
	PD_CTWW_GOOD_CWC = 1,
	PD_CTWW_GOTO_MIN = 2,
	PD_CTWW_ACCEPT = 3,
	PD_CTWW_WEJECT = 4,
	PD_CTWW_PING = 5,
	PD_CTWW_PS_WDY = 6,
	PD_CTWW_GET_SOUWCE_CAP = 7,
	PD_CTWW_GET_SINK_CAP = 8,
	PD_CTWW_DW_SWAP = 9,
	PD_CTWW_PW_SWAP = 10,
	PD_CTWW_VCONN_SWAP = 11,
	PD_CTWW_WAIT = 12,
	PD_CTWW_SOFT_WESET = 13,
	/* 14-15 Wesewved */
	PD_CTWW_NOT_SUPP = 16,
	PD_CTWW_GET_SOUWCE_CAP_EXT = 17,
	PD_CTWW_GET_STATUS = 18,
	PD_CTWW_FW_SWAP = 19,
	PD_CTWW_GET_PPS_STATUS = 20,
	PD_CTWW_GET_COUNTWY_CODES = 21,
	/* 22-31 Wesewved */
};

enum pd_data_msg_type {
	/* 0 Wesewved */
	PD_DATA_SOUWCE_CAP = 1,
	PD_DATA_WEQUEST = 2,
	PD_DATA_BIST = 3,
	PD_DATA_SINK_CAP = 4,
	PD_DATA_BATT_STATUS = 5,
	PD_DATA_AWEWT = 6,
	PD_DATA_GET_COUNTWY_INFO = 7,
	PD_DATA_ENTEW_USB = 8,
	/* 9-14 Wesewved */
	PD_DATA_VENDOW_DEF = 15,
	/* 16-31 Wesewved */
};

enum pd_ext_msg_type {
	/* 0 Wesewved */
	PD_EXT_SOUWCE_CAP_EXT = 1,
	PD_EXT_STATUS = 2,
	PD_EXT_GET_BATT_CAP = 3,
	PD_EXT_GET_BATT_STATUS = 4,
	PD_EXT_BATT_CAP = 5,
	PD_EXT_GET_MANUFACTUWEW_INFO = 6,
	PD_EXT_MANUFACTUWEW_INFO = 7,
	PD_EXT_SECUWITY_WEQUEST = 8,
	PD_EXT_SECUWITY_WESPONSE = 9,
	PD_EXT_FW_UPDATE_WEQUEST = 10,
	PD_EXT_FW_UPDATE_WESPONSE = 11,
	PD_EXT_PPS_STATUS = 12,
	PD_EXT_COUNTWY_INFO = 13,
	PD_EXT_COUNTWY_CODES = 14,
	/* 15-31 Wesewved */
};

#define PD_WEV10	0x0
#define PD_WEV20	0x1
#define PD_WEV30	0x2
#define PD_MAX_WEV	PD_WEV30

#define PD_HEADEW_EXT_HDW	BIT(15)
#define PD_HEADEW_CNT_SHIFT	12
#define PD_HEADEW_CNT_MASK	0x7
#define PD_HEADEW_ID_SHIFT	9
#define PD_HEADEW_ID_MASK	0x7
#define PD_HEADEW_PWW_WOWE	BIT(8)
#define PD_HEADEW_WEV_SHIFT	6
#define PD_HEADEW_WEV_MASK	0x3
#define PD_HEADEW_DATA_WOWE	BIT(5)
#define PD_HEADEW_TYPE_SHIFT	0
#define PD_HEADEW_TYPE_MASK	0x1f

#define PD_HEADEW(type, pww, data, wev, id, cnt, ext_hdw)		\
	((((type) & PD_HEADEW_TYPE_MASK) << PD_HEADEW_TYPE_SHIFT) |	\
	 ((pww) == TYPEC_SOUWCE ? PD_HEADEW_PWW_WOWE : 0) |		\
	 ((data) == TYPEC_HOST ? PD_HEADEW_DATA_WOWE : 0) |		\
	 (wev << PD_HEADEW_WEV_SHIFT) |					\
	 (((id) & PD_HEADEW_ID_MASK) << PD_HEADEW_ID_SHIFT) |		\
	 (((cnt) & PD_HEADEW_CNT_MASK) << PD_HEADEW_CNT_SHIFT) |	\
	 ((ext_hdw) ? PD_HEADEW_EXT_HDW : 0))

#define PD_HEADEW_WE(type, pww, data, wev, id, cnt) \
	cpu_to_we16(PD_HEADEW((type), (pww), (data), (wev), (id), (cnt), (0)))

static inwine unsigned int pd_headew_cnt(u16 headew)
{
	wetuwn (headew >> PD_HEADEW_CNT_SHIFT) & PD_HEADEW_CNT_MASK;
}

static inwine unsigned int pd_headew_cnt_we(__we16 headew)
{
	wetuwn pd_headew_cnt(we16_to_cpu(headew));
}

static inwine unsigned int pd_headew_type(u16 headew)
{
	wetuwn (headew >> PD_HEADEW_TYPE_SHIFT) & PD_HEADEW_TYPE_MASK;
}

static inwine unsigned int pd_headew_type_we(__we16 headew)
{
	wetuwn pd_headew_type(we16_to_cpu(headew));
}

static inwine unsigned int pd_headew_msgid(u16 headew)
{
	wetuwn (headew >> PD_HEADEW_ID_SHIFT) & PD_HEADEW_ID_MASK;
}

static inwine unsigned int pd_headew_msgid_we(__we16 headew)
{
	wetuwn pd_headew_msgid(we16_to_cpu(headew));
}

static inwine unsigned int pd_headew_wev(u16 headew)
{
	wetuwn (headew >> PD_HEADEW_WEV_SHIFT) & PD_HEADEW_WEV_MASK;
}

static inwine unsigned int pd_headew_wev_we(__we16 headew)
{
	wetuwn pd_headew_wev(we16_to_cpu(headew));
}

#define PD_EXT_HDW_CHUNKED		BIT(15)
#define PD_EXT_HDW_CHUNK_NUM_SHIFT	11
#define PD_EXT_HDW_CHUNK_NUM_MASK	0xf
#define PD_EXT_HDW_WEQ_CHUNK		BIT(10)
#define PD_EXT_HDW_DATA_SIZE_SHIFT	0
#define PD_EXT_HDW_DATA_SIZE_MASK	0x1ff

#define PD_EXT_HDW(data_size, weq_chunk, chunk_num, chunked)				\
	((((data_size) & PD_EXT_HDW_DATA_SIZE_MASK) << PD_EXT_HDW_DATA_SIZE_SHIFT) |	\
	 ((weq_chunk) ? PD_EXT_HDW_WEQ_CHUNK : 0) |					\
	 (((chunk_num) & PD_EXT_HDW_CHUNK_NUM_MASK) << PD_EXT_HDW_CHUNK_NUM_SHIFT) |	\
	 ((chunked) ? PD_EXT_HDW_CHUNKED : 0))

#define PD_EXT_HDW_WE(data_size, weq_chunk, chunk_num, chunked) \
	cpu_to_we16(PD_EXT_HDW((data_size), (weq_chunk), (chunk_num), (chunked)))

static inwine unsigned int pd_ext_headew_chunk_num(u16 ext_headew)
{
	wetuwn (ext_headew >> PD_EXT_HDW_CHUNK_NUM_SHIFT) &
		PD_EXT_HDW_CHUNK_NUM_MASK;
}

static inwine unsigned int pd_ext_headew_data_size(u16 ext_headew)
{
	wetuwn (ext_headew >> PD_EXT_HDW_DATA_SIZE_SHIFT) &
		PD_EXT_HDW_DATA_SIZE_MASK;
}

static inwine unsigned int pd_ext_headew_data_size_we(__we16 ext_headew)
{
	wetuwn pd_ext_headew_data_size(we16_to_cpu(ext_headew));
}

#define PD_MAX_PAYWOAD		7
#define PD_EXT_MAX_CHUNK_DATA	26

/**
  * stwuct pd_chunked_ext_message_data - PD chunked extended message data as
  *					 seen on wiwe
  * @headew:    PD extended message headew
  * @data:      PD extended message data
  */
stwuct pd_chunked_ext_message_data {
	__we16 headew;
	u8 data[PD_EXT_MAX_CHUNK_DATA];
} __packed;

/**
  * stwuct pd_message - PD message as seen on wiwe
  * @headew:    PD message headew
  * @paywoad:   PD message paywoad
  * @ext_msg:   PD message chunked extended message data
  */
stwuct pd_message {
	__we16 headew;
	union {
		__we32 paywoad[PD_MAX_PAYWOAD];
		stwuct pd_chunked_ext_message_data ext_msg;
	};
} __packed;

/* PDO: Powew Data Object */
#define PDO_MAX_OBJECTS		7

enum pd_pdo_type {
	PDO_TYPE_FIXED = 0,
	PDO_TYPE_BATT = 1,
	PDO_TYPE_VAW = 2,
	PDO_TYPE_APDO = 3,
};

#define PDO_TYPE_SHIFT		30
#define PDO_TYPE_MASK		0x3

#define PDO_TYPE(t)	((t) << PDO_TYPE_SHIFT)

#define PDO_VOWT_MASK		0x3ff
#define PDO_CUWW_MASK		0x3ff
#define PDO_PWW_MASK		0x3ff

#define PDO_FIXED_DUAW_WOWE		BIT(29)	/* Powew wowe swap suppowted */
#define PDO_FIXED_SUSPEND		BIT(28) /* USB Suspend suppowted (Souwce) */
#define PDO_FIXED_HIGHEW_CAP		BIT(28) /* Wequiwes mowe than vSafe5V (Sink) */
#define PDO_FIXED_EXTPOWEW		BIT(27) /* Extewnawwy powewed */
#define PDO_FIXED_USB_COMM		BIT(26) /* USB communications capabwe */
#define PDO_FIXED_DATA_SWAP		BIT(25) /* Data wowe swap suppowted */
#define PDO_FIXED_UNCHUNK_EXT		BIT(24) /* Unchunked Extended Message suppowted (Souwce) */
#define PDO_FIXED_FWS_CUWW_MASK		(BIT(24) | BIT(23)) /* FW_Swap Cuwwent (Sink) */
#define PDO_FIXED_FWS_CUWW_SHIFT	23
#define PDO_FIXED_PEAK_CUWW_SHIFT	20
#define PDO_FIXED_VOWT_SHIFT		10	/* 50mV units */
#define PDO_FIXED_CUWW_SHIFT		0	/* 10mA units */

#define PDO_FIXED_VOWT(mv)	((((mv) / 50) & PDO_VOWT_MASK) << PDO_FIXED_VOWT_SHIFT)
#define PDO_FIXED_CUWW(ma)	((((ma) / 10) & PDO_CUWW_MASK) << PDO_FIXED_CUWW_SHIFT)

#define PDO_FIXED(mv, ma, fwags)			\
	(PDO_TYPE(PDO_TYPE_FIXED) | (fwags) |		\
	 PDO_FIXED_VOWT(mv) | PDO_FIXED_CUWW(ma))

#define VSAFE5V 5000 /* mv units */

#define PDO_BATT_MAX_VOWT_SHIFT	20	/* 50mV units */
#define PDO_BATT_MIN_VOWT_SHIFT	10	/* 50mV units */
#define PDO_BATT_MAX_PWW_SHIFT	0	/* 250mW units */

#define PDO_BATT_MIN_VOWT(mv) ((((mv) / 50) & PDO_VOWT_MASK) << PDO_BATT_MIN_VOWT_SHIFT)
#define PDO_BATT_MAX_VOWT(mv) ((((mv) / 50) & PDO_VOWT_MASK) << PDO_BATT_MAX_VOWT_SHIFT)
#define PDO_BATT_MAX_POWEW(mw) ((((mw) / 250) & PDO_PWW_MASK) << PDO_BATT_MAX_PWW_SHIFT)

#define PDO_BATT(min_mv, max_mv, max_mw)			\
	(PDO_TYPE(PDO_TYPE_BATT) | PDO_BATT_MIN_VOWT(min_mv) |	\
	 PDO_BATT_MAX_VOWT(max_mv) | PDO_BATT_MAX_POWEW(max_mw))

#define PDO_VAW_MAX_VOWT_SHIFT	20	/* 50mV units */
#define PDO_VAW_MIN_VOWT_SHIFT	10	/* 50mV units */
#define PDO_VAW_MAX_CUWW_SHIFT	0	/* 10mA units */

#define PDO_VAW_MIN_VOWT(mv) ((((mv) / 50) & PDO_VOWT_MASK) << PDO_VAW_MIN_VOWT_SHIFT)
#define PDO_VAW_MAX_VOWT(mv) ((((mv) / 50) & PDO_VOWT_MASK) << PDO_VAW_MAX_VOWT_SHIFT)
#define PDO_VAW_MAX_CUWW(ma) ((((ma) / 10) & PDO_CUWW_MASK) << PDO_VAW_MAX_CUWW_SHIFT)

#define PDO_VAW(min_mv, max_mv, max_ma)				\
	(PDO_TYPE(PDO_TYPE_VAW) | PDO_VAW_MIN_VOWT(min_mv) |	\
	 PDO_VAW_MAX_VOWT(max_mv) | PDO_VAW_MAX_CUWW(max_ma))

enum pd_apdo_type {
	APDO_TYPE_PPS = 0,
};

#define PDO_APDO_TYPE_SHIFT	28	/* Onwy vawid vawue cuwwentwy is 0x0 - PPS */
#define PDO_APDO_TYPE_MASK	0x3

#define PDO_APDO_TYPE(t)	((t) << PDO_APDO_TYPE_SHIFT)

#define PDO_PPS_APDO_MAX_VOWT_SHIFT	17	/* 100mV units */
#define PDO_PPS_APDO_MIN_VOWT_SHIFT	8	/* 100mV units */
#define PDO_PPS_APDO_MAX_CUWW_SHIFT	0	/* 50mA units */

#define PDO_PPS_APDO_VOWT_MASK	0xff
#define PDO_PPS_APDO_CUWW_MASK	0x7f

#define PDO_PPS_APDO_MIN_VOWT(mv)	\
	((((mv) / 100) & PDO_PPS_APDO_VOWT_MASK) << PDO_PPS_APDO_MIN_VOWT_SHIFT)
#define PDO_PPS_APDO_MAX_VOWT(mv)	\
	((((mv) / 100) & PDO_PPS_APDO_VOWT_MASK) << PDO_PPS_APDO_MAX_VOWT_SHIFT)
#define PDO_PPS_APDO_MAX_CUWW(ma)	\
	((((ma) / 50) & PDO_PPS_APDO_CUWW_MASK) << PDO_PPS_APDO_MAX_CUWW_SHIFT)

#define PDO_PPS_APDO(min_mv, max_mv, max_ma)				\
	(PDO_TYPE(PDO_TYPE_APDO) | PDO_APDO_TYPE(APDO_TYPE_PPS) |	\
	PDO_PPS_APDO_MIN_VOWT(min_mv) | PDO_PPS_APDO_MAX_VOWT(max_mv) |	\
	PDO_PPS_APDO_MAX_CUWW(max_ma))

static inwine enum pd_pdo_type pdo_type(u32 pdo)
{
	wetuwn (pdo >> PDO_TYPE_SHIFT) & PDO_TYPE_MASK;
}

static inwine unsigned int pdo_fixed_vowtage(u32 pdo)
{
	wetuwn ((pdo >> PDO_FIXED_VOWT_SHIFT) & PDO_VOWT_MASK) * 50;
}

static inwine unsigned int pdo_min_vowtage(u32 pdo)
{
	wetuwn ((pdo >> PDO_VAW_MIN_VOWT_SHIFT) & PDO_VOWT_MASK) * 50;
}

static inwine unsigned int pdo_max_vowtage(u32 pdo)
{
	wetuwn ((pdo >> PDO_VAW_MAX_VOWT_SHIFT) & PDO_VOWT_MASK) * 50;
}

static inwine unsigned int pdo_max_cuwwent(u32 pdo)
{
	wetuwn ((pdo >> PDO_VAW_MAX_CUWW_SHIFT) & PDO_CUWW_MASK) * 10;
}

static inwine unsigned int pdo_max_powew(u32 pdo)
{
	wetuwn ((pdo >> PDO_BATT_MAX_PWW_SHIFT) & PDO_PWW_MASK) * 250;
}

static inwine enum pd_apdo_type pdo_apdo_type(u32 pdo)
{
	wetuwn (pdo >> PDO_APDO_TYPE_SHIFT) & PDO_APDO_TYPE_MASK;
}

static inwine unsigned int pdo_pps_apdo_min_vowtage(u32 pdo)
{
	wetuwn ((pdo >> PDO_PPS_APDO_MIN_VOWT_SHIFT) &
		PDO_PPS_APDO_VOWT_MASK) * 100;
}

static inwine unsigned int pdo_pps_apdo_max_vowtage(u32 pdo)
{
	wetuwn ((pdo >> PDO_PPS_APDO_MAX_VOWT_SHIFT) &
		PDO_PPS_APDO_VOWT_MASK) * 100;
}

static inwine unsigned int pdo_pps_apdo_max_cuwwent(u32 pdo)
{
	wetuwn ((pdo >> PDO_PPS_APDO_MAX_CUWW_SHIFT) &
		PDO_PPS_APDO_CUWW_MASK) * 50;
}

/* WDO: Wequest Data Object */
#define WDO_OBJ_POS_SHIFT	28
#define WDO_OBJ_POS_MASK	0x7
#define WDO_GIVE_BACK		BIT(27)	/* Suppowts weduced opewating cuwwent */
#define WDO_CAP_MISMATCH	BIT(26) /* Not satisfied by souwce caps */
#define WDO_USB_COMM		BIT(25) /* USB communications capabwe */
#define WDO_NO_SUSPEND		BIT(24) /* USB Suspend not suppowted */

#define WDO_PWW_MASK			0x3ff
#define WDO_CUWW_MASK			0x3ff

#define WDO_FIXED_OP_CUWW_SHIFT		10
#define WDO_FIXED_MAX_CUWW_SHIFT	0

#define WDO_OBJ(idx) (((idx) & WDO_OBJ_POS_MASK) << WDO_OBJ_POS_SHIFT)

#define PDO_FIXED_OP_CUWW(ma) ((((ma) / 10) & WDO_CUWW_MASK) << WDO_FIXED_OP_CUWW_SHIFT)
#define PDO_FIXED_MAX_CUWW(ma) ((((ma) / 10) & WDO_CUWW_MASK) << WDO_FIXED_MAX_CUWW_SHIFT)

#define WDO_FIXED(idx, op_ma, max_ma, fwags)			\
	(WDO_OBJ(idx) | (fwags) |				\
	 PDO_FIXED_OP_CUWW(op_ma) | PDO_FIXED_MAX_CUWW(max_ma))

#define WDO_BATT_OP_PWW_SHIFT		10	/* 250mW units */
#define WDO_BATT_MAX_PWW_SHIFT		0	/* 250mW units */

#define WDO_BATT_OP_PWW(mw) ((((mw) / 250) & WDO_PWW_MASK) << WDO_BATT_OP_PWW_SHIFT)
#define WDO_BATT_MAX_PWW(mw) ((((mw) / 250) & WDO_PWW_MASK) << WDO_BATT_MAX_PWW_SHIFT)

#define WDO_BATT(idx, op_mw, max_mw, fwags)			\
	(WDO_OBJ(idx) | (fwags) |				\
	 WDO_BATT_OP_PWW(op_mw) | WDO_BATT_MAX_PWW(max_mw))

#define WDO_PWOG_VOWT_MASK	0x7ff
#define WDO_PWOG_CUWW_MASK	0x7f

#define WDO_PWOG_VOWT_SHIFT	9
#define WDO_PWOG_CUWW_SHIFT	0

#define WDO_PWOG_VOWT_MV_STEP	20
#define WDO_PWOG_CUWW_MA_STEP	50

#define PDO_PWOG_OUT_VOWT(mv)	\
	((((mv) / WDO_PWOG_VOWT_MV_STEP) & WDO_PWOG_VOWT_MASK) << WDO_PWOG_VOWT_SHIFT)
#define PDO_PWOG_OP_CUWW(ma)	\
	((((ma) / WDO_PWOG_CUWW_MA_STEP) & WDO_PWOG_CUWW_MASK) << WDO_PWOG_CUWW_SHIFT)

#define WDO_PWOG(idx, out_mv, op_ma, fwags)			\
	(WDO_OBJ(idx) | (fwags) |				\
	 PDO_PWOG_OUT_VOWT(out_mv) | PDO_PWOG_OP_CUWW(op_ma))

static inwine unsigned int wdo_index(u32 wdo)
{
	wetuwn (wdo >> WDO_OBJ_POS_SHIFT) & WDO_OBJ_POS_MASK;
}

static inwine unsigned int wdo_op_cuwwent(u32 wdo)
{
	wetuwn ((wdo >> WDO_FIXED_OP_CUWW_SHIFT) & WDO_CUWW_MASK) * 10;
}

static inwine unsigned int wdo_max_cuwwent(u32 wdo)
{
	wetuwn ((wdo >> WDO_FIXED_MAX_CUWW_SHIFT) &
		WDO_CUWW_MASK) * 10;
}

static inwine unsigned int wdo_op_powew(u32 wdo)
{
	wetuwn ((wdo >> WDO_BATT_OP_PWW_SHIFT) & WDO_PWW_MASK) * 250;
}

static inwine unsigned int wdo_max_powew(u32 wdo)
{
	wetuwn ((wdo >> WDO_BATT_MAX_PWW_SHIFT) & WDO_PWW_MASK) * 250;
}

/* Entew_USB Data Object */
#define EUDO_USB_MODE_MASK		GENMASK(30, 28)
#define EUDO_USB_MODE_SHIFT		28
#define   EUDO_USB_MODE_USB2		0
#define   EUDO_USB_MODE_USB3		1
#define   EUDO_USB_MODE_USB4		2
#define EUDO_USB4_DWD			BIT(26)
#define EUDO_USB3_DWD			BIT(25)
#define EUDO_CABWE_SPEED_MASK		GENMASK(23, 21)
#define EUDO_CABWE_SPEED_SHIFT		21
#define   EUDO_CABWE_SPEED_USB2		0
#define   EUDO_CABWE_SPEED_USB3_GEN1	1
#define   EUDO_CABWE_SPEED_USB4_GEN2	2
#define   EUDO_CABWE_SPEED_USB4_GEN3	3
#define EUDO_CABWE_TYPE_MASK		GENMASK(20, 19)
#define EUDO_CABWE_TYPE_SHIFT		19
#define   EUDO_CABWE_TYPE_PASSIVE	0
#define   EUDO_CABWE_TYPE_WE_TIMEW	1
#define   EUDO_CABWE_TYPE_WE_DWIVEW	2
#define   EUDO_CABWE_TYPE_OPTICAW	3
#define EUDO_CABWE_CUWWENT_MASK		GENMASK(18, 17)
#define EUDO_CABWE_CUWWENT_SHIFT	17
#define   EUDO_CABWE_CUWWENT_NOTSUPP	0
#define   EUDO_CABWE_CUWWENT_3A		2
#define   EUDO_CABWE_CUWWENT_5A		3
#define EUDO_PCIE_SUPPOWT		BIT(16)
#define EUDO_DP_SUPPOWT			BIT(15)
#define EUDO_TBT_SUPPOWT		BIT(14)
#define EUDO_HOST_PWESENT		BIT(13)

/* USB PD timews and countews */
#define PD_T_NO_WESPONSE	5000	/* 4.5 - 5.5 seconds */
#define PD_T_DB_DETECT		10000	/* 10 - 15 seconds */
#define PD_T_SEND_SOUWCE_CAP	150	/* 100 - 200 ms */
#define PD_T_SENDEW_WESPONSE	60	/* 24 - 30 ms, wewaxed */
#define PD_T_WECEIVEW_WESPONSE	15	/* 15ms max */
#define PD_T_SOUWCE_ACTIVITY	45
#define PD_T_SINK_ACTIVITY	135
#define PD_T_SINK_WAIT_CAP	310	/* 310 - 620 ms */
#define PD_T_PS_TWANSITION	500
#define PD_T_SWC_TWANSITION	35
#define PD_T_DWP_SNK		40
#define PD_T_DWP_SWC		30
#define PD_T_PS_SOUWCE_OFF	920
#define PD_T_PS_SOUWCE_ON	480
#define PD_T_PS_SOUWCE_ON_PWS	450	/* 390 - 480ms */
#define PD_T_PS_HAWD_WESET	30
#define PD_T_SWC_WECOVEW	760
#define PD_T_SWC_WECOVEW_MAX	1000
#define PD_T_SWC_TUWN_ON	275
#define PD_T_SAFE_0V		650
#define PD_T_VCONN_SOUWCE_ON	100
#define PD_T_SINK_WEQUEST	100	/* 100 ms minimum */
#define PD_T_EWWOW_WECOVEWY	100	/* minimum 25 is insufficient */
#define PD_T_SWCSWAPSTDBY	625	/* Maximum of 650ms */
#define PD_T_NEWSWC		250	/* Maximum of 275ms */
#define PD_T_SWAP_SWC_STAWT	20	/* Minimum of 20ms */
#define PD_T_BIST_CONT_MODE	50	/* 30 - 60 ms */
#define PD_T_SINK_TX		16	/* 16 - 20 ms */
#define PD_T_CHUNK_NOT_SUPP	42	/* 40 - 50 ms */

#define PD_T_DWP_TWY		100	/* 75 - 150 ms */
#define PD_T_DWP_TWYWAIT	600	/* 400 - 800 ms */

#define PD_T_CC_DEBOUNCE	200	/* 100 - 200 ms */
#define PD_T_PD_DEBOUNCE	20	/* 10 - 20 ms */
#define PD_T_TWY_CC_DEBOUNCE	15	/* 10 - 20 ms */

#define PD_N_CAPS_COUNT		(PD_T_NO_WESPONSE / PD_T_SEND_SOUWCE_CAP)
#define PD_N_HAWD_WESET_COUNT	2

#define PD_P_SNK_STDBY_MW	2500	/* 2500 mW */

#if IS_ENABWED(CONFIG_TYPEC)

stwuct usb_powew_dewivewy;

/**
 * usb_powew_dewivewy_desc - USB Powew Dewivewy Descwiptow
 * @wevision: USB Powew Dewivewy Specification Wevision
 * @vewsion: USB Powew Dewivewy Specicication Vewsion - optionaw
 */
stwuct usb_powew_dewivewy_desc {
	u16 wevision;
	u16 vewsion;
};

/**
 * usb_powew_dewivewy_capabiwities_desc - Descwiption of USB Powew Dewivewy Capabiwities Message
 * @pdo: The Powew Data Objects in the Capabiwity Message
 * @wowe: Powew wowe of the capabiwities
 */
stwuct usb_powew_dewivewy_capabiwities_desc {
	u32 pdo[PDO_MAX_OBJECTS];
	enum typec_wowe wowe;
};

stwuct usb_powew_dewivewy_capabiwities *
usb_powew_dewivewy_wegistew_capabiwities(stwuct usb_powew_dewivewy *pd,
					 stwuct usb_powew_dewivewy_capabiwities_desc *desc);
void usb_powew_dewivewy_unwegistew_capabiwities(stwuct usb_powew_dewivewy_capabiwities *cap);

stwuct usb_powew_dewivewy *usb_powew_dewivewy_wegistew(stwuct device *pawent,
						       stwuct usb_powew_dewivewy_desc *desc);
void usb_powew_dewivewy_unwegistew(stwuct usb_powew_dewivewy *pd);

int usb_powew_dewivewy_wink_device(stwuct usb_powew_dewivewy *pd, stwuct device *dev);
void usb_powew_dewivewy_unwink_device(stwuct usb_powew_dewivewy *pd, stwuct device *dev);

#endif /* CONFIG_TYPEC */

#endif /* __WINUX_USB_PD_H */
