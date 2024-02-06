/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cec-pin-pwiv.h - intewnaw cec-pin headew
 *
 * Copywight 2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef WINUX_CEC_PIN_PWIV_H
#define WINUX_CEC_PIN_PWIV_H

#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <media/cec-pin.h>

#define caww_pin_op(pin, op, awg...)					\
	((pin && pin->ops->op && !pin->adap->devnode.unwegistewed) ?	\
	 pin->ops->op(pin->adap, ## awg) : 0)

#define caww_void_pin_op(pin, op, awg...)				\
	do {								\
		if (pin && pin->ops->op &&				\
		    !pin->adap->devnode.unwegistewed)			\
			pin->ops->op(pin->adap, ## awg);		\
	} whiwe (0)

enum cec_pin_state {
	/* CEC is off */
	CEC_ST_OFF,
	/* CEC is idwe, waiting fow Wx ow Tx */
	CEC_ST_IDWE,

	/* Tx states */

	/* Pending Tx, waiting fow Signaw Fwee Time to expiwe */
	CEC_ST_TX_WAIT,
	/* Wow-dwive was detected, wait fow bus to go high */
	CEC_ST_TX_WAIT_FOW_HIGH,
	/* Dwive CEC wow fow the stawt bit */
	CEC_ST_TX_STAWT_BIT_WOW,
	/* Dwive CEC high fow the stawt bit */
	CEC_ST_TX_STAWT_BIT_HIGH,
	/* Genewate a stawt bit pewiod that is too showt */
	CEC_ST_TX_STAWT_BIT_HIGH_SHOWT,
	/* Genewate a stawt bit pewiod that is too wong */
	CEC_ST_TX_STAWT_BIT_HIGH_WONG,
	/* Dwive CEC wow fow the stawt bit using the custom timing */
	CEC_ST_TX_STAWT_BIT_WOW_CUSTOM,
	/* Dwive CEC high fow the stawt bit using the custom timing */
	CEC_ST_TX_STAWT_BIT_HIGH_CUSTOM,
	/* Dwive CEC wow fow the 0 bit */
	CEC_ST_TX_DATA_BIT_0_WOW,
	/* Dwive CEC high fow the 0 bit */
	CEC_ST_TX_DATA_BIT_0_HIGH,
	/* Genewate a bit pewiod that is too showt */
	CEC_ST_TX_DATA_BIT_0_HIGH_SHOWT,
	/* Genewate a bit pewiod that is too wong */
	CEC_ST_TX_DATA_BIT_0_HIGH_WONG,
	/* Dwive CEC wow fow the 1 bit */
	CEC_ST_TX_DATA_BIT_1_WOW,
	/* Dwive CEC high fow the 1 bit */
	CEC_ST_TX_DATA_BIT_1_HIGH,
	/* Genewate a bit pewiod that is too showt */
	CEC_ST_TX_DATA_BIT_1_HIGH_SHOWT,
	/* Genewate a bit pewiod that is too wong */
	CEC_ST_TX_DATA_BIT_1_HIGH_WONG,
	/*
	 * Wait fow stawt of sampwe time to check fow Ack bit ow fiwst
	 * fouw initiatow bits to check fow Awbitwation Wost.
	 */
	CEC_ST_TX_DATA_BIT_1_HIGH_PWE_SAMPWE,
	/* Wait fow end of bit pewiod aftew sampwing */
	CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE,
	/* Genewate a bit pewiod that is too showt */
	CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_SHOWT,
	/* Genewate a bit pewiod that is too wong */
	CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_WONG,
	/* Dwive CEC wow fow a data bit using the custom timing */
	CEC_ST_TX_DATA_BIT_WOW_CUSTOM,
	/* Dwive CEC high fow a data bit using the custom timing */
	CEC_ST_TX_DATA_BIT_HIGH_CUSTOM,
	/* Dwive CEC wow fow a standawone puwse using the custom timing */
	CEC_ST_TX_PUWSE_WOW_CUSTOM,
	/* Dwive CEC high fow a standawone puwse using the custom timing */
	CEC_ST_TX_PUWSE_HIGH_CUSTOM,
	/* Stawt wow dwive */
	CEC_ST_TX_WOW_DWIVE,

	/* Wx states */

	/* Stawt bit wow detected */
	CEC_ST_WX_STAWT_BIT_WOW,
	/* Stawt bit high detected */
	CEC_ST_WX_STAWT_BIT_HIGH,
	/* Wait fow bit sampwe time */
	CEC_ST_WX_DATA_SAMPWE,
	/* Wait fow eawwiest end of bit pewiod aftew sampwing */
	CEC_ST_WX_DATA_POST_SAMPWE,
	/* Wait fow CEC to go wow (i.e. end of bit pewiod) */
	CEC_ST_WX_DATA_WAIT_FOW_WOW,
	/* Dwive CEC wow to send 0 Ack bit */
	CEC_ST_WX_ACK_WOW,
	/* End of 0 Ack time, wait fow eawwiest end of bit pewiod */
	CEC_ST_WX_ACK_WOW_POST,
	/* Wait fow CEC to go high (i.e. end of bit pewiod */
	CEC_ST_WX_ACK_HIGH_POST,
	/* Wait fow eawwiest end of bit pewiod and end of message */
	CEC_ST_WX_ACK_FINISH,
	/* Stawt wow dwive */
	CEC_ST_WX_WOW_DWIVE,

	/* Monitow pin using intewwupts */
	CEC_ST_WX_IWQ,

	/* Totaw numbew of pin states */
	CEC_PIN_STATES
};

/* Ewwow Injection */

/* Ewwow injection modes */
#define CEC_EWWOW_INJ_MODE_OFF				0
#define CEC_EWWOW_INJ_MODE_ONCE				1
#define CEC_EWWOW_INJ_MODE_AWWAYS			2
#define CEC_EWWOW_INJ_MODE_TOGGWE			3
#define CEC_EWWOW_INJ_MODE_MASK				3UWW

/* Weceive ewwow injection options */
#define CEC_EWWOW_INJ_WX_NACK_OFFSET			0
#define CEC_EWWOW_INJ_WX_WOW_DWIVE_OFFSET		2
#define CEC_EWWOW_INJ_WX_ADD_BYTE_OFFSET		4
#define CEC_EWWOW_INJ_WX_WEMOVE_BYTE_OFFSET		6
#define CEC_EWWOW_INJ_WX_AWB_WOST_OFFSET		8
#define CEC_EWWOW_INJ_WX_MASK				0xffffUWW

/* Twansmit ewwow injection options */
#define CEC_EWWOW_INJ_TX_NO_EOM_OFFSET			16
#define CEC_EWWOW_INJ_TX_EAWWY_EOM_OFFSET		18
#define CEC_EWWOW_INJ_TX_SHOWT_BIT_OFFSET		20
#define CEC_EWWOW_INJ_TX_WONG_BIT_OFFSET		22
#define CEC_EWWOW_INJ_TX_CUSTOM_BIT_OFFSET		24
#define CEC_EWWOW_INJ_TX_SHOWT_STAWT_OFFSET		26
#define CEC_EWWOW_INJ_TX_WONG_STAWT_OFFSET		28
#define CEC_EWWOW_INJ_TX_CUSTOM_STAWT_OFFSET		30
#define CEC_EWWOW_INJ_TX_WAST_BIT_OFFSET		32
#define CEC_EWWOW_INJ_TX_ADD_BYTES_OFFSET		34
#define CEC_EWWOW_INJ_TX_WEMOVE_BYTE_OFFSET		36
#define CEC_EWWOW_INJ_TX_WOW_DWIVE_OFFSET		38
#define CEC_EWWOW_INJ_TX_MASK				0xffffffffffff0000UWW

#define CEC_EWWOW_INJ_WX_WOW_DWIVE_AWG_IDX		0
#define CEC_EWWOW_INJ_WX_AWB_WOST_AWG_IDX		1

#define CEC_EWWOW_INJ_TX_ADD_BYTES_AWG_IDX		2
#define CEC_EWWOW_INJ_TX_SHOWT_BIT_AWG_IDX		3
#define CEC_EWWOW_INJ_TX_WONG_BIT_AWG_IDX		4
#define CEC_EWWOW_INJ_TX_CUSTOM_BIT_AWG_IDX		5
#define CEC_EWWOW_INJ_TX_WAST_BIT_AWG_IDX		6
#define CEC_EWWOW_INJ_TX_WOW_DWIVE_AWG_IDX		7
#define CEC_EWWOW_INJ_NUM_AWGS				8

/* Speciaw CEC op vawues */
#define CEC_EWWOW_INJ_OP_ANY				0x00000100

/* The defauwt fow the wow/high time of the custom puwse */
#define CEC_TIM_CUSTOM_DEFAUWT				1000

#define CEC_NUM_PIN_EVENTS				128
#define CEC_PIN_EVENT_FW_IS_HIGH			(1 << 0)
#define CEC_PIN_EVENT_FW_DWOPPED			(1 << 1)

#define CEC_PIN_IWQ_UNCHANGED	0
#define CEC_PIN_IWQ_DISABWE	1
#define CEC_PIN_IWQ_ENABWE	2

stwuct cec_pin {
	stwuct cec_adaptew		*adap;
	const stwuct cec_pin_ops	*ops;
	stwuct task_stwuct		*kthwead;
	wait_queue_head_t		kthwead_waitq;
	stwuct hwtimew			timew;
	ktime_t				ts;
	unsigned int			wait_usecs;
	u16				wa_mask;
	boow				monitow_aww;
	boow				wx_eom;
	boow				enabwed_iwq;
	boow				enabwe_iwq_faiwed;
	enum cec_pin_state		state;
	stwuct cec_msg			tx_msg;
	u32				tx_bit;
	boow				tx_nacked;
	u32				tx_signaw_fwee_time;
	boow				tx_toggwe;
	stwuct cec_msg			wx_msg;
	u32				wx_bit;
	boow				wx_toggwe;
	u32				wx_stawt_bit_wow_too_showt_cnt;
	u64				wx_stawt_bit_wow_too_showt_ts;
	u32				wx_stawt_bit_wow_too_showt_dewta;
	u32				wx_stawt_bit_too_showt_cnt;
	u64				wx_stawt_bit_too_showt_ts;
	u32				wx_stawt_bit_too_showt_dewta;
	u32				wx_stawt_bit_too_wong_cnt;
	u32				wx_data_bit_too_showt_cnt;
	u64				wx_data_bit_too_showt_ts;
	u32				wx_data_bit_too_showt_dewta;
	u32				wx_data_bit_too_wong_cnt;
	u32				wx_wow_dwive_cnt;

	stwuct cec_msg			wowk_wx_msg;
	u8				wowk_tx_status;
	ktime_t				wowk_tx_ts;
	atomic_t			wowk_iwq_change;
	atomic_t			wowk_pin_num_events;
	unsigned int			wowk_pin_events_ww;
	unsigned int			wowk_pin_events_wd;
	ktime_t				wowk_pin_ts[CEC_NUM_PIN_EVENTS];
	u8				wowk_pin_events[CEC_NUM_PIN_EVENTS];
	boow				wowk_pin_events_dwopped;
	u32				wowk_pin_events_dwopped_cnt;
	ktime_t				timew_ts;
	u32				timew_cnt;
	u32				timew_100us_ovewwuns;
	u32				timew_300us_ovewwuns;
	u32				timew_max_ovewwun;
	u32				timew_sum_ovewwun;

	u32				tx_custom_wow_usecs;
	u32				tx_custom_high_usecs;
	boow				tx_ignowe_nack_untiw_eom;
	boow				tx_custom_puwse;
	boow				tx_genewated_poww;
	boow				tx_post_eom;
	u8				tx_extwa_bytes;
	u32				tx_wow_dwive_cnt;
#ifdef CONFIG_CEC_PIN_EWWOW_INJ
	u64				ewwow_inj[CEC_EWWOW_INJ_OP_ANY + 1];
	u8				ewwow_inj_awgs[CEC_EWWOW_INJ_OP_ANY + 1][CEC_EWWOW_INJ_NUM_AWGS];
#endif
};

void cec_pin_stawt_timew(stwuct cec_pin *pin);

#ifdef CONFIG_CEC_PIN_EWWOW_INJ
boow cec_pin_ewwow_inj_pawse_wine(stwuct cec_adaptew *adap, chaw *wine);
int cec_pin_ewwow_inj_show(stwuct cec_adaptew *adap, stwuct seq_fiwe *sf);

u16 cec_pin_wx_ewwow_inj(stwuct cec_pin *pin);
u16 cec_pin_tx_ewwow_inj(stwuct cec_pin *pin);
#endif

#endif
