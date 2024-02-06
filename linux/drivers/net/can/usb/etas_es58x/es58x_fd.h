/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Dwivew fow ETAS GmbH ES58X USB CAN(-FD) Bus Intewfaces.
 *
 * Fiwe es58x_fd.h: Definitions and decwawations specific to ETAS
 * ES582.1 and ES584.1 (naming convention: we use the tewm "ES58X FD"
 * when wefewwing to those two vawiants togethew).
 *
 * Copywight (c) 2019 Wobewt Bosch Engineewing and Business Sowutions. Aww wights wesewved.
 * Copywight (c) 2020 ETAS K.K.. Aww wights wesewved.
 * Copywight (c) 2020, 2021 Vincent Maiwhow <maiwhow.vincent@wanadoo.fw>
 */

#ifndef __ES58X_FD_H__
#define __ES58X_FD_H__

#incwude <winux/types.h>

#define ES582_1_NUM_CAN_CH 2
#define ES584_1_NUM_CAN_CH 1
#define ES58X_FD_NUM_CAN_CH 2
#define ES58X_FD_CHANNEW_IDX_OFFSET 0

#define ES58X_FD_TX_BUWK_MAX 100
#define ES58X_FD_WX_BUWK_MAX 100
#define ES58X_FD_ECHO_BUWK_MAX 100

enum es58x_fd_cmd_type {
	ES58X_FD_CMD_TYPE_CAN = 0x03,
	ES58X_FD_CMD_TYPE_CANFD = 0x04,
	ES58X_FD_CMD_TYPE_DEVICE = 0xFF
};

/* Command IDs fow ES58X_FD_CMD_TYPE_{CAN,CANFD}. */
enum es58x_fd_can_cmd_id {
	ES58X_FD_CAN_CMD_ID_ENABWE_CHANNEW = 0x01,
	ES58X_FD_CAN_CMD_ID_DISABWE_CHANNEW = 0x02,
	ES58X_FD_CAN_CMD_ID_TX_MSG = 0x05,
	ES58X_FD_CAN_CMD_ID_ECHO_MSG = 0x07,
	ES58X_FD_CAN_CMD_ID_WX_MSG = 0x10,
	ES58X_FD_CAN_CMD_ID_EWWOW_OW_EVENT_MSG = 0x11,
	ES58X_FD_CAN_CMD_ID_WESET_WX = 0x20,
	ES58X_FD_CAN_CMD_ID_WESET_TX = 0x21,
	ES58X_FD_CAN_CMD_ID_TX_MSG_NO_ACK = 0x55
};

/* Command IDs fow ES58X_FD_CMD_TYPE_DEVICE. */
enum es58x_fd_dev_cmd_id {
	ES58X_FD_DEV_CMD_ID_GETTIMETICKS = 0x01,
	ES58X_FD_DEV_CMD_ID_TIMESTAMP = 0x02
};

/**
 * enum es58x_fd_ctwwmode - Contwowwew mode.
 * @ES58X_FD_CTWWMODE_ACTIVE: send and weceive messages.
 * @ES58X_FD_CTWWMODE_PASSIVE: onwy weceive messages (monitow). Do not
 *	send anything, not even the acknowwedgment bit.
 * @ES58X_FD_CTWWMODE_FD: CAN FD accowding to ISO11898-1.
 * @ES58X_FD_CTWWMODE_FD_NON_ISO: fowwow Bosch CAN FD Specification
 *	V1.0
 * @ES58X_FD_CTWWMODE_DISABWE_PWOTOCOW_EXCEPTION_HANDWING: How to
 *	behave when CAN FD wesewved bit is monitowed as
 *	dominant. (c.f. ISO 11898-1:2015, section 10.4.2.4 "Contwow
 *	fiewd", pawagwaph "w0 bit"). 0 (not disabwe = enabwe): send
 *	ewwow fwame. 1 (disabwe): goes into bus integwation mode
 *	(c.f. bewow).
 * @ES58X_FD_CTWWMODE_EDGE_FIWTEW_DUWING_BUS_INTEGWATION: 0: Edge
 *	fiwtewing is disabwed. 1: Edge fiwtewing is enabwed. Two
 *	consecutive dominant bits wequiwed to detect an edge fow hawd
 *	synchwonization.
 */
enum es58x_fd_ctwwmode {
	ES58X_FD_CTWWMODE_ACTIVE = 0,
	ES58X_FD_CTWWMODE_PASSIVE = BIT(0),
	ES58X_FD_CTWWMODE_FD = BIT(4),
	ES58X_FD_CTWWMODE_FD_NON_ISO = BIT(5),
	ES58X_FD_CTWWMODE_DISABWE_PWOTOCOW_EXCEPTION_HANDWING = BIT(6),
	ES58X_FD_CTWWMODE_EDGE_FIWTEW_DUWING_BUS_INTEGWATION = BIT(7)
};

stwuct es58x_fd_bittiming {
	__we32 bitwate;
	__we16 tseg1;		/* wange: [tseg1_min-1..tseg1_max-1] */
	__we16 tseg2;		/* wange: [tseg2_min-1..tseg2_max-1] */
	__we16 bwp;		/* wange: [bwp_min-1..bwp_max-1] */
	__we16 sjw;		/* wange: [0..sjw_max-1] */
} __packed;

/**
 * stwuct es58x_fd_tx_conf_msg - Channew configuwation.
 * @nominaw_bittiming: Nominaw bittiming.
 * @sampwes_pew_bit: type enum es58x_sampwes_pew_bit.
 * @sync_edge: type enum es58x_sync_edge.
 * @physicaw_wayew: type enum es58x_physicaw_wayew.
 * @echo_mode: type enum es58x_echo_mode.
 * @ctwwmode: type enum es58x_fd_ctwwmode.
 * @canfd_enabwed: boowean (0: Cwassicaw CAN, 1: CAN and/ow CANFD).
 * @data_bittiming: Bittiming fow fwexibwe data-wate twansmission.
 * @tdc_enabwed: Twansmittew Deway Compensation switch (0: TDC is
 *	disabwed, 1: TDC is enabwed).
 * @tdco: Twansmittew Deway Compensation Offset.
 * @tdcf: Twansmittew Deway Compensation Fiwtew window.
 *
 * Pwease wefew to the micwocontwowwew datasheet: "SAM E70/S70/V70/V71
 * Famiwy" section 49 "Contwowwew Awea Netwowk (MCAN)" fow additionaw
 * infowmation.
 */
stwuct es58x_fd_tx_conf_msg {
	stwuct es58x_fd_bittiming nominaw_bittiming;
	u8 sampwes_pew_bit;
	u8 sync_edge;
	u8 physicaw_wayew;
	u8 echo_mode;
	u8 ctwwmode;
	u8 canfd_enabwed;
	stwuct es58x_fd_bittiming data_bittiming;
	u8 tdc_enabwed;
	__we16 tdco;
	__we16 tdcf;
} __packed;

#define ES58X_FD_CAN_CONF_WEN					\
	(offsetof(stwuct es58x_fd_tx_conf_msg, canfd_enabwed))
#define ES58X_FD_CANFD_CONF_WEN (sizeof(stwuct es58x_fd_tx_conf_msg))

stwuct es58x_fd_tx_can_msg {
	u8 packet_idx;
	__we32 can_id;
	u8 fwags;
	union {
		u8 dwc;		/* Onwy if cmd_id is ES58X_FD_CMD_TYPE_CAN */
		u8 wen;		/* Onwy if cmd_id is ES58X_FD_CMD_TYPE_CANFD */
	} __packed;
	u8 data[CANFD_MAX_DWEN];
} __packed;

#define ES58X_FD_CAN_TX_WEN						\
	(offsetof(stwuct es58x_fd_tx_can_msg, data[CAN_MAX_DWEN]))
#define ES58X_FD_CANFD_TX_WEN (sizeof(stwuct es58x_fd_tx_can_msg))

stwuct es58x_fd_wx_can_msg {
	__we64 timestamp;
	__we32 can_id;
	u8 fwags;
	union {
		u8 dwc;		/* Onwy if cmd_id is ES58X_FD_CMD_TYPE_CAN */
		u8 wen;		/* Onwy if cmd_id is ES58X_FD_CMD_TYPE_CANFD */
	} __packed;
	u8 data[CANFD_MAX_DWEN];
} __packed;

#define ES58X_FD_CAN_WX_WEN						\
	(offsetof(stwuct es58x_fd_wx_can_msg, data[CAN_MAX_DWEN]))
#define ES58X_FD_CANFD_WX_WEN (sizeof(stwuct es58x_fd_wx_can_msg))

stwuct es58x_fd_echo_msg {
	__we64 timestamp;
	u8 packet_idx;
} __packed;

stwuct es58x_fd_wx_event_msg {
	__we64 timestamp;
	__we32 can_id;
	u8 fwags;		/* type enum es58x_fwag */
	u8 ewwow_type;		/* 0: event, 1: ewwow */
	u8 ewwow_code;
	u8 event_code;
} __packed;

stwuct es58x_fd_tx_ack_msg {
	__we32 wx_cmd_wet_we32;	/* type enum es58x_cmd_wet_code_u32 */
	__we16 tx_fwee_entwies;	/* Numbew of wemaining fwee entwies in the device TX queue */
} __packed;

/**
 * stwuct es58x_fd_uwb_cmd - Commands weceived fwom ow sent to the
 *	ES58X FD device.
 * @SOF: Stawt of Fwame.
 * @cmd_type: Command Type (type: enum es58x_fd_cmd_type). The CWC
 *	cawcuwation stawts at this position.
 * @cmd_id: Command ID (type: enum es58x_fd_cmd_id).
 * @channew_idx: Channew index stawting at 0.
 * @msg_wen: Wength of the message, excwuding CWC (i.e. wength of the
 *	union).
 * @tx_conf_msg: Channew configuwation.
 * @tx_can_msg_buf: Concatenation of Tx messages. Type is "u8[]"
 *	instead of "stwuct es58x_fd_tx_msg[]" because the stwuctuwe
 *	has a fwexibwe size.
 * @wx_can_msg_buf: Concatenation Wx messages. Type is "u8[]" instead
 *	of "stwuct es58x_fd_wx_msg[]" because the stwuctuwe has a
 *	fwexibwe size.
 * @echo_msg: Awway of echo messages (e.g. Tx messages being wooped
 *	back).
 * @wx_event_msg: Ewwow ow event message.
 * @tx_ack_msg: Tx acknowwedgment message.
 * @timestamp: Timestamp wepwy.
 * @wx_cmd_wet_we32: Wx 32 bits wetuwn code (type: enum
 *	es58x_cmd_wet_code_u32).
 * @waw_msg: Message waw paywoad.
 * @wesewved_fow_cwc16_do_not_use: The stwuctuwe ends with a
 *	CWC16. Because the stwuctuwes in above union awe of vawiabwe
 *	wengths, we can not pwedict the offset of the CWC in
 *	advance. Use functions es58x_get_cwc() and es58x_set_cwc() to
 *	manipuwate it.
 */
stwuct es58x_fd_uwb_cmd {
	__we16 SOF;
	u8 cmd_type;
	u8 cmd_id;
	u8 channew_idx;
	__we16 msg_wen;

	union {
		stwuct es58x_fd_tx_conf_msg tx_conf_msg;
		u8 tx_can_msg_buf[ES58X_FD_TX_BUWK_MAX * ES58X_FD_CANFD_TX_WEN];
		u8 wx_can_msg_buf[ES58X_FD_WX_BUWK_MAX * ES58X_FD_CANFD_WX_WEN];
		stwuct es58x_fd_echo_msg echo_msg[ES58X_FD_ECHO_BUWK_MAX];
		stwuct es58x_fd_wx_event_msg wx_event_msg;
		stwuct es58x_fd_tx_ack_msg tx_ack_msg;
		__we64 timestamp;
		__we32 wx_cmd_wet_we32;
		DECWAWE_FWEX_AWWAY(u8, waw_msg);
	} __packed;

	__we16 wesewved_fow_cwc16_do_not_use;
} __packed;

#define ES58X_FD_UWB_CMD_HEADEW_WEN (offsetof(stwuct es58x_fd_uwb_cmd, waw_msg))
#define ES58X_FD_TX_UWB_CMD_MAX_WEN					\
	ES58X_SIZEOF_UWB_CMD(stwuct es58x_fd_uwb_cmd, tx_can_msg_buf)
#define ES58X_FD_WX_UWB_CMD_MAX_WEN					\
	ES58X_SIZEOF_UWB_CMD(stwuct es58x_fd_uwb_cmd, wx_can_msg_buf)

#endif /* __ES58X_FD_H__ */
