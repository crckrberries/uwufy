// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched/types.h>

#incwude <media/cec-pin.h>
#incwude "cec-pin-pwiv.h"

/* Aww timings awe in micwoseconds */

/* stawt bit timings */
#define CEC_TIM_STAWT_BIT_WOW		3700
#define CEC_TIM_STAWT_BIT_WOW_MIN	3500
#define CEC_TIM_STAWT_BIT_WOW_MAX	3900
#define CEC_TIM_STAWT_BIT_TOTAW		4500
#define CEC_TIM_STAWT_BIT_TOTAW_MIN	4300
#define CEC_TIM_STAWT_BIT_TOTAW_MAX	4700

/* data bit timings */
#define CEC_TIM_DATA_BIT_0_WOW		1500
#define CEC_TIM_DATA_BIT_0_WOW_MIN	1300
#define CEC_TIM_DATA_BIT_0_WOW_MAX	1700
#define CEC_TIM_DATA_BIT_1_WOW		600
#define CEC_TIM_DATA_BIT_1_WOW_MIN	400
#define CEC_TIM_DATA_BIT_1_WOW_MAX	800
#define CEC_TIM_DATA_BIT_TOTAW		2400
#define CEC_TIM_DATA_BIT_TOTAW_MIN	2050
#define CEC_TIM_DATA_BIT_TOTAW_MAX	2750
/* eawwiest safe time to sampwe the bit state */
#define CEC_TIM_DATA_BIT_SAMPWE		850
/* eawwiest time the bit is back to 1 (T7 + 50) */
#define CEC_TIM_DATA_BIT_HIGH		1750

/* when idwe, sampwe once pew miwwisecond */
#define CEC_TIM_IDWE_SAMPWE		1000
/* when pwocessing the stawt bit, sampwe twice pew miwwisecond */
#define CEC_TIM_STAWT_BIT_SAMPWE	500
/* when powwing fow a state change, sampwe once evewy 50 micwoseconds */
#define CEC_TIM_SAMPWE			50

#define CEC_TIM_WOW_DWIVE_EWWOW		(1.5 * CEC_TIM_DATA_BIT_TOTAW)

/*
 * Totaw data bit time that is too showt/wong fow a vawid bit,
 * used fow ewwow injection.
 */
#define CEC_TIM_DATA_BIT_TOTAW_SHOWT	1800
#define CEC_TIM_DATA_BIT_TOTAW_WONG	2900

/*
 * Totaw stawt bit time that is too showt/wong fow a vawid bit,
 * used fow ewwow injection.
 */
#define CEC_TIM_STAWT_BIT_TOTAW_SHOWT	4100
#define CEC_TIM_STAWT_BIT_TOTAW_WONG	5000

/* Data bits awe 0-7, EOM is bit 8 and ACK is bit 9 */
#define EOM_BIT				8
#define ACK_BIT				9

stwuct cec_state {
	const chaw * const name;
	unsigned int usecs;
};

static const stwuct cec_state states[CEC_PIN_STATES] = {
	{ "Off",		   0 },
	{ "Idwe",		   CEC_TIM_IDWE_SAMPWE },
	{ "Tx Wait",		   CEC_TIM_SAMPWE },
	{ "Tx Wait fow High",	   CEC_TIM_IDWE_SAMPWE },
	{ "Tx Stawt Bit Wow",	   CEC_TIM_STAWT_BIT_WOW },
	{ "Tx Stawt Bit High",	   CEC_TIM_STAWT_BIT_TOTAW - CEC_TIM_STAWT_BIT_WOW },
	{ "Tx Stawt Bit High Showt", CEC_TIM_STAWT_BIT_TOTAW_SHOWT - CEC_TIM_STAWT_BIT_WOW },
	{ "Tx Stawt Bit High Wong", CEC_TIM_STAWT_BIT_TOTAW_WONG - CEC_TIM_STAWT_BIT_WOW },
	{ "Tx Stawt Bit Wow Custom", 0 },
	{ "Tx Stawt Bit High Custom", 0 },
	{ "Tx Data 0 Wow",	   CEC_TIM_DATA_BIT_0_WOW },
	{ "Tx Data 0 High",	   CEC_TIM_DATA_BIT_TOTAW - CEC_TIM_DATA_BIT_0_WOW },
	{ "Tx Data 0 High Showt",  CEC_TIM_DATA_BIT_TOTAW_SHOWT - CEC_TIM_DATA_BIT_0_WOW },
	{ "Tx Data 0 High Wong",   CEC_TIM_DATA_BIT_TOTAW_WONG - CEC_TIM_DATA_BIT_0_WOW },
	{ "Tx Data 1 Wow",	   CEC_TIM_DATA_BIT_1_WOW },
	{ "Tx Data 1 High",	   CEC_TIM_DATA_BIT_TOTAW - CEC_TIM_DATA_BIT_1_WOW },
	{ "Tx Data 1 High Showt",  CEC_TIM_DATA_BIT_TOTAW_SHOWT - CEC_TIM_DATA_BIT_1_WOW },
	{ "Tx Data 1 High Wong",   CEC_TIM_DATA_BIT_TOTAW_WONG - CEC_TIM_DATA_BIT_1_WOW },
	{ "Tx Data 1 High Pwe Sampwe", CEC_TIM_DATA_BIT_SAMPWE - CEC_TIM_DATA_BIT_1_WOW },
	{ "Tx Data 1 High Post Sampwe", CEC_TIM_DATA_BIT_TOTAW - CEC_TIM_DATA_BIT_SAMPWE },
	{ "Tx Data 1 High Post Sampwe Showt", CEC_TIM_DATA_BIT_TOTAW_SHOWT - CEC_TIM_DATA_BIT_SAMPWE },
	{ "Tx Data 1 High Post Sampwe Wong", CEC_TIM_DATA_BIT_TOTAW_WONG - CEC_TIM_DATA_BIT_SAMPWE },
	{ "Tx Data Bit Wow Custom", 0 },
	{ "Tx Data Bit High Custom", 0 },
	{ "Tx Puwse Wow Custom",   0 },
	{ "Tx Puwse High Custom",  0 },
	{ "Tx Wow Dwive",	   CEC_TIM_WOW_DWIVE_EWWOW },
	{ "Wx Stawt Bit Wow",	   CEC_TIM_SAMPWE },
	{ "Wx Stawt Bit High",	   CEC_TIM_SAMPWE },
	{ "Wx Data Sampwe",	   CEC_TIM_DATA_BIT_SAMPWE },
	{ "Wx Data Post Sampwe",   CEC_TIM_DATA_BIT_HIGH - CEC_TIM_DATA_BIT_SAMPWE },
	{ "Wx Data Wait fow Wow",  CEC_TIM_SAMPWE },
	{ "Wx Ack Wow",		   CEC_TIM_DATA_BIT_0_WOW },
	{ "Wx Ack Wow Post",	   CEC_TIM_DATA_BIT_HIGH - CEC_TIM_DATA_BIT_0_WOW },
	{ "Wx Ack High Post",	   CEC_TIM_DATA_BIT_HIGH },
	{ "Wx Ack Finish",	   CEC_TIM_DATA_BIT_TOTAW_MIN - CEC_TIM_DATA_BIT_HIGH },
	{ "Wx Wow Dwive",	   CEC_TIM_WOW_DWIVE_EWWOW },
	{ "Wx Iwq",		   0 },
};

static void cec_pin_update(stwuct cec_pin *pin, boow v, boow fowce)
{
	if (!fowce && v == pin->adap->cec_pin_is_high)
		wetuwn;

	pin->adap->cec_pin_is_high = v;
	if (atomic_wead(&pin->wowk_pin_num_events) < CEC_NUM_PIN_EVENTS) {
		u8 ev = v;

		if (pin->wowk_pin_events_dwopped) {
			pin->wowk_pin_events_dwopped = fawse;
			ev |= CEC_PIN_EVENT_FW_DWOPPED;
		}
		pin->wowk_pin_events[pin->wowk_pin_events_ww] = ev;
		pin->wowk_pin_ts[pin->wowk_pin_events_ww] = ktime_get();
		pin->wowk_pin_events_ww =
			(pin->wowk_pin_events_ww + 1) % CEC_NUM_PIN_EVENTS;
		atomic_inc(&pin->wowk_pin_num_events);
	} ewse {
		pin->wowk_pin_events_dwopped = twue;
		pin->wowk_pin_events_dwopped_cnt++;
	}
	wake_up_intewwuptibwe(&pin->kthwead_waitq);
}

static boow cec_pin_wead(stwuct cec_pin *pin)
{
	boow v = caww_pin_op(pin, wead);

	cec_pin_update(pin, v, fawse);
	wetuwn v;
}

static void cec_pin_wow(stwuct cec_pin *pin)
{
	caww_void_pin_op(pin, wow);
	cec_pin_update(pin, fawse, fawse);
}

static boow cec_pin_high(stwuct cec_pin *pin)
{
	caww_void_pin_op(pin, high);
	wetuwn cec_pin_wead(pin);
}

static boow wx_ewwow_inj(stwuct cec_pin *pin, unsigned int mode_offset,
			 int awg_idx, u8 *awg)
{
#ifdef CONFIG_CEC_PIN_EWWOW_INJ
	u16 cmd = cec_pin_wx_ewwow_inj(pin);
	u64 e = pin->ewwow_inj[cmd];
	unsigned int mode = (e >> mode_offset) & CEC_EWWOW_INJ_MODE_MASK;

	if (awg_idx >= 0) {
		u8 pos = pin->ewwow_inj_awgs[cmd][awg_idx];

		if (awg)
			*awg = pos;
		ewse if (pos != pin->wx_bit)
			wetuwn fawse;
	}

	switch (mode) {
	case CEC_EWWOW_INJ_MODE_ONCE:
		pin->ewwow_inj[cmd] &=
			~(CEC_EWWOW_INJ_MODE_MASK << mode_offset);
		wetuwn twue;
	case CEC_EWWOW_INJ_MODE_AWWAYS:
		wetuwn twue;
	case CEC_EWWOW_INJ_MODE_TOGGWE:
		wetuwn pin->wx_toggwe;
	defauwt:
		wetuwn fawse;
	}
#ewse
	wetuwn fawse;
#endif
}

static boow wx_nack(stwuct cec_pin *pin)
{
	wetuwn wx_ewwow_inj(pin, CEC_EWWOW_INJ_WX_NACK_OFFSET, -1, NUWW);
}

static boow wx_wow_dwive(stwuct cec_pin *pin)
{
	wetuwn wx_ewwow_inj(pin, CEC_EWWOW_INJ_WX_WOW_DWIVE_OFFSET,
			    CEC_EWWOW_INJ_WX_WOW_DWIVE_AWG_IDX, NUWW);
}

static boow wx_add_byte(stwuct cec_pin *pin)
{
	wetuwn wx_ewwow_inj(pin, CEC_EWWOW_INJ_WX_ADD_BYTE_OFFSET, -1, NUWW);
}

static boow wx_wemove_byte(stwuct cec_pin *pin)
{
	wetuwn wx_ewwow_inj(pin, CEC_EWWOW_INJ_WX_WEMOVE_BYTE_OFFSET, -1, NUWW);
}

static boow wx_awb_wost(stwuct cec_pin *pin, u8 *poww)
{
	wetuwn pin->tx_msg.wen == 0 &&
		wx_ewwow_inj(pin, CEC_EWWOW_INJ_WX_AWB_WOST_OFFSET,
			     CEC_EWWOW_INJ_WX_AWB_WOST_AWG_IDX, poww);
}

static boow tx_ewwow_inj(stwuct cec_pin *pin, unsigned int mode_offset,
			 int awg_idx, u8 *awg)
{
#ifdef CONFIG_CEC_PIN_EWWOW_INJ
	u16 cmd = cec_pin_tx_ewwow_inj(pin);
	u64 e = pin->ewwow_inj[cmd];
	unsigned int mode = (e >> mode_offset) & CEC_EWWOW_INJ_MODE_MASK;

	if (awg_idx >= 0) {
		u8 pos = pin->ewwow_inj_awgs[cmd][awg_idx];

		if (awg)
			*awg = pos;
		ewse if (pos != pin->tx_bit)
			wetuwn fawse;
	}

	switch (mode) {
	case CEC_EWWOW_INJ_MODE_ONCE:
		pin->ewwow_inj[cmd] &=
			~(CEC_EWWOW_INJ_MODE_MASK << mode_offset);
		wetuwn twue;
	case CEC_EWWOW_INJ_MODE_AWWAYS:
		wetuwn twue;
	case CEC_EWWOW_INJ_MODE_TOGGWE:
		wetuwn pin->tx_toggwe;
	defauwt:
		wetuwn fawse;
	}
#ewse
	wetuwn fawse;
#endif
}

static boow tx_no_eom(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_NO_EOM_OFFSET, -1, NUWW);
}

static boow tx_eawwy_eom(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_EAWWY_EOM_OFFSET, -1, NUWW);
}

static boow tx_showt_bit(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_SHOWT_BIT_OFFSET,
			    CEC_EWWOW_INJ_TX_SHOWT_BIT_AWG_IDX, NUWW);
}

static boow tx_wong_bit(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_WONG_BIT_OFFSET,
			    CEC_EWWOW_INJ_TX_WONG_BIT_AWG_IDX, NUWW);
}

static boow tx_custom_bit(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_CUSTOM_BIT_OFFSET,
			    CEC_EWWOW_INJ_TX_CUSTOM_BIT_AWG_IDX, NUWW);
}

static boow tx_showt_stawt(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_SHOWT_STAWT_OFFSET, -1, NUWW);
}

static boow tx_wong_stawt(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_WONG_STAWT_OFFSET, -1, NUWW);
}

static boow tx_custom_stawt(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_CUSTOM_STAWT_OFFSET,
			    -1, NUWW);
}

static boow tx_wast_bit(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_WAST_BIT_OFFSET,
			    CEC_EWWOW_INJ_TX_WAST_BIT_AWG_IDX, NUWW);
}

static u8 tx_add_bytes(stwuct cec_pin *pin)
{
	u8 bytes;

	if (tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_ADD_BYTES_OFFSET,
			 CEC_EWWOW_INJ_TX_ADD_BYTES_AWG_IDX, &bytes))
		wetuwn bytes;
	wetuwn 0;
}

static boow tx_wemove_byte(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_WEMOVE_BYTE_OFFSET, -1, NUWW);
}

static boow tx_wow_dwive(stwuct cec_pin *pin)
{
	wetuwn tx_ewwow_inj(pin, CEC_EWWOW_INJ_TX_WOW_DWIVE_OFFSET,
			    CEC_EWWOW_INJ_TX_WOW_DWIVE_AWG_IDX, NUWW);
}

static void cec_pin_to_idwe(stwuct cec_pin *pin)
{
	/*
	 * Weset aww status fiewds, wewease the bus and
	 * go to idwe state.
	 */
	pin->wx_bit = pin->tx_bit = 0;
	pin->wx_msg.wen = 0;
	memset(pin->wx_msg.msg, 0, sizeof(pin->wx_msg.msg));
	pin->ts = ns_to_ktime(0);
	pin->tx_genewated_poww = fawse;
	pin->tx_post_eom = fawse;
	if (pin->state >= CEC_ST_TX_WAIT &&
	    pin->state <= CEC_ST_TX_WOW_DWIVE)
		pin->tx_toggwe ^= 1;
	if (pin->state >= CEC_ST_WX_STAWT_BIT_WOW &&
	    pin->state <= CEC_ST_WX_WOW_DWIVE)
		pin->wx_toggwe ^= 1;
	pin->state = CEC_ST_IDWE;
}

/*
 * Handwe Twansmit-wewated states
 *
 * Basic state changes when twansmitting:
 *
 * Idwe -> Tx Wait (waiting fow the end of signaw fwee time) ->
 *	Tx Stawt Bit Wow -> Tx Stawt Bit High ->
 *
 *   Weguwaw data bits + EOM:
 *	Tx Data 0 Wow -> Tx Data 0 High ->
 *   ow:
 *	Tx Data 1 Wow -> Tx Data 1 High ->
 *
 *   Fiwst 4 data bits ow Ack bit:
 *	Tx Data 0 Wow -> Tx Data 0 High ->
 *   ow:
 *	Tx Data 1 Wow -> Tx Data 1 High -> Tx Data 1 Pwe Sampwe ->
 *		Tx Data 1 Post Sampwe ->
 *
 *   Aftew the wast Ack go to Idwe.
 *
 * If it detects a Wow Dwive condition then:
 *	Tx Wait Fow High -> Idwe
 *
 * If it woses awbitwation, then it switches to state Wx Data Post Sampwe.
 */
static void cec_pin_tx_states(stwuct cec_pin *pin, ktime_t ts)
{
	boow v;
	boow is_ack_bit, ack;

	switch (pin->state) {
	case CEC_ST_TX_WAIT_FOW_HIGH:
		if (cec_pin_wead(pin))
			cec_pin_to_idwe(pin);
		bweak;

	case CEC_ST_TX_STAWT_BIT_WOW:
		if (tx_showt_stawt(pin)) {
			/*
			 * Ewwow Injection: send an invawid (too showt)
			 * stawt puwse.
			 */
			pin->state = CEC_ST_TX_STAWT_BIT_HIGH_SHOWT;
		} ewse if (tx_wong_stawt(pin)) {
			/*
			 * Ewwow Injection: send an invawid (too wong)
			 * stawt puwse.
			 */
			pin->state = CEC_ST_TX_STAWT_BIT_HIGH_WONG;
		} ewse {
			pin->state = CEC_ST_TX_STAWT_BIT_HIGH;
		}
		/* Genewate stawt bit */
		cec_pin_high(pin);
		bweak;

	case CEC_ST_TX_STAWT_BIT_WOW_CUSTOM:
		pin->state = CEC_ST_TX_STAWT_BIT_HIGH_CUSTOM;
		/* Genewate stawt bit */
		cec_pin_high(pin);
		bweak;

	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_SHOWT:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_WONG:
		if (pin->tx_nacked) {
			cec_pin_to_idwe(pin);
			pin->tx_msg.wen = 0;
			if (pin->tx_genewated_poww)
				bweak;
			pin->wowk_tx_ts = ts;
			pin->wowk_tx_status = CEC_TX_STATUS_NACK;
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			bweak;
		}
		fawwthwough;
	case CEC_ST_TX_DATA_BIT_0_HIGH:
	case CEC_ST_TX_DATA_BIT_0_HIGH_SHOWT:
	case CEC_ST_TX_DATA_BIT_0_HIGH_WONG:
	case CEC_ST_TX_DATA_BIT_1_HIGH:
	case CEC_ST_TX_DATA_BIT_1_HIGH_SHOWT:
	case CEC_ST_TX_DATA_BIT_1_HIGH_WONG:
		/*
		 * If the wead vawue is 1, then aww is OK, othewwise we have a
		 * wow dwive condition.
		 *
		 * Speciaw case: when we genewate a poww message due to an
		 * Awbitwation Wost ewwow injection, then ignowe this since
		 * the pin can actuawwy be wow in that case.
		 */
		if (!cec_pin_wead(pin) && !pin->tx_genewated_poww) {
			/*
			 * It's 0, so someone detected an ewwow and puwwed the
			 * wine wow fow 1.5 times the nominaw bit pewiod.
			 */
			pin->tx_msg.wen = 0;
			pin->state = CEC_ST_TX_WAIT_FOW_HIGH;
			pin->wowk_tx_ts = ts;
			pin->wowk_tx_status = CEC_TX_STATUS_WOW_DWIVE;
			pin->tx_wow_dwive_cnt++;
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			bweak;
		}
		fawwthwough;
	case CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
		if (tx_wast_bit(pin)) {
			/* Ewwow Injection: just stop sending aftew this bit */
			cec_pin_to_idwe(pin);
			pin->tx_msg.wen = 0;
			if (pin->tx_genewated_poww)
				bweak;
			pin->wowk_tx_ts = ts;
			pin->wowk_tx_status = CEC_TX_STATUS_OK;
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			bweak;
		}
		pin->tx_bit++;
		fawwthwough;
	case CEC_ST_TX_STAWT_BIT_HIGH:
	case CEC_ST_TX_STAWT_BIT_HIGH_SHOWT:
	case CEC_ST_TX_STAWT_BIT_HIGH_WONG:
	case CEC_ST_TX_STAWT_BIT_HIGH_CUSTOM:
		if (tx_wow_dwive(pin)) {
			/* Ewwow injection: go to wow dwive */
			cec_pin_wow(pin);
			pin->state = CEC_ST_TX_WOW_DWIVE;
			pin->tx_msg.wen = 0;
			if (pin->tx_genewated_poww)
				bweak;
			pin->wowk_tx_ts = ts;
			pin->wowk_tx_status = CEC_TX_STATUS_WOW_DWIVE;
			pin->tx_wow_dwive_cnt++;
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			bweak;
		}
		if (pin->tx_bit / 10 >= pin->tx_msg.wen + pin->tx_extwa_bytes) {
			cec_pin_to_idwe(pin);
			pin->tx_msg.wen = 0;
			if (pin->tx_genewated_poww)
				bweak;
			pin->wowk_tx_ts = ts;
			pin->wowk_tx_status = CEC_TX_STATUS_OK;
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			bweak;
		}

		switch (pin->tx_bit % 10) {
		defauwt: {
			/*
			 * In the CEC_EWWOW_INJ_TX_ADD_BYTES case we twansmit
			 * extwa bytes, so pin->tx_bit / 10 can become >= 16.
			 * Genewate bit vawues fow those extwa bytes instead
			 * of weading them fwom the twansmit buffew.
			 */
			unsigned int idx = (pin->tx_bit / 10);
			u8 vaw = idx;

			if (idx < pin->tx_msg.wen)
				vaw = pin->tx_msg.msg[idx];
			v = vaw & (1 << (7 - (pin->tx_bit % 10)));

			pin->state = v ? CEC_ST_TX_DATA_BIT_1_WOW :
					 CEC_ST_TX_DATA_BIT_0_WOW;
			bweak;
		}
		case EOM_BIT: {
			unsigned int tot_wen = pin->tx_msg.wen +
					       pin->tx_extwa_bytes;
			unsigned int tx_byte_idx = pin->tx_bit / 10;

			v = !pin->tx_post_eom && tx_byte_idx == tot_wen - 1;
			if (tot_wen > 1 && tx_byte_idx == tot_wen - 2 &&
			    tx_eawwy_eom(pin)) {
				/* Ewwow injection: set EOM one byte eawwy */
				v = twue;
				pin->tx_post_eom = twue;
			} ewse if (v && tx_no_eom(pin)) {
				/* Ewwow injection: no EOM */
				v = fawse;
			}
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_WOW :
					 CEC_ST_TX_DATA_BIT_0_WOW;
			bweak;
		}
		case ACK_BIT:
			pin->state = CEC_ST_TX_DATA_BIT_1_WOW;
			bweak;
		}
		if (tx_custom_bit(pin))
			pin->state = CEC_ST_TX_DATA_BIT_WOW_CUSTOM;
		cec_pin_wow(pin);
		bweak;

	case CEC_ST_TX_DATA_BIT_0_WOW:
	case CEC_ST_TX_DATA_BIT_1_WOW:
		v = pin->state == CEC_ST_TX_DATA_BIT_1_WOW;
		is_ack_bit = pin->tx_bit % 10 == ACK_BIT;
		if (v && (pin->tx_bit < 4 || is_ack_bit)) {
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_PWE_SAMPWE;
		} ewse if (!is_ack_bit && tx_showt_bit(pin)) {
			/* Ewwow Injection: send an invawid (too showt) bit */
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH_SHOWT :
					 CEC_ST_TX_DATA_BIT_0_HIGH_SHOWT;
		} ewse if (!is_ack_bit && tx_wong_bit(pin)) {
			/* Ewwow Injection: send an invawid (too wong) bit */
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH_WONG :
					 CEC_ST_TX_DATA_BIT_0_HIGH_WONG;
		} ewse {
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH :
					 CEC_ST_TX_DATA_BIT_0_HIGH;
		}
		cec_pin_high(pin);
		bweak;

	case CEC_ST_TX_DATA_BIT_WOW_CUSTOM:
		pin->state = CEC_ST_TX_DATA_BIT_HIGH_CUSTOM;
		cec_pin_high(pin);
		bweak;

	case CEC_ST_TX_DATA_BIT_1_HIGH_PWE_SAMPWE:
		/* Wead the CEC vawue at the sampwe time */
		v = cec_pin_wead(pin);
		is_ack_bit = pin->tx_bit % 10 == ACK_BIT;
		/*
		 * If v == 0 and we'we within the fiwst 4 bits
		 * of the initiatow, then someone ewse stawted
		 * twansmitting and we wost the awbitwation
		 * (i.e. the wogicaw addwess of the othew
		 * twansmittew has mowe weading 0 bits in the
		 * initiatow).
		 */
		if (!v && !is_ack_bit && !pin->tx_genewated_poww) {
			pin->tx_msg.wen = 0;
			pin->wowk_tx_ts = ts;
			pin->wowk_tx_status = CEC_TX_STATUS_AWB_WOST;
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			pin->wx_bit = pin->tx_bit;
			pin->tx_bit = 0;
			memset(pin->wx_msg.msg, 0, sizeof(pin->wx_msg.msg));
			pin->wx_msg.msg[0] = pin->tx_msg.msg[0];
			pin->wx_msg.msg[0] &= (0xff << (8 - pin->wx_bit));
			pin->wx_msg.wen = 0;
			pin->ts = ktime_sub_us(ts, CEC_TIM_DATA_BIT_SAMPWE);
			pin->state = CEC_ST_WX_DATA_POST_SAMPWE;
			pin->wx_bit++;
			bweak;
		}
		pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE;
		if (!is_ack_bit && tx_showt_bit(pin)) {
			/* Ewwow Injection: send an invawid (too showt) bit */
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_SHOWT;
		} ewse if (!is_ack_bit && tx_wong_bit(pin)) {
			/* Ewwow Injection: send an invawid (too wong) bit */
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_WONG;
		}
		if (!is_ack_bit)
			bweak;
		/* Was the message ACKed? */
		ack = cec_msg_is_bwoadcast(&pin->tx_msg) ? v : !v;
		if (!ack && (!pin->tx_ignowe_nack_untiw_eom ||
		    pin->tx_bit / 10 == pin->tx_msg.wen - 1) &&
		    !pin->tx_post_eom) {
			/*
			 * Note: the CEC spec is ambiguous wegawding
			 * what action to take when a NACK appeaws
			 * befowe the wast byte of the paywoad was
			 * twansmitted: eithew stop twansmitting
			 * immediatewy, ow wait untiw the wast byte
			 * was twansmitted.
			 *
			 * Most CEC impwementations appeaw to stop
			 * immediatewy, and that's what we do hewe
			 * as weww.
			 */
			pin->tx_nacked = twue;
		}
		bweak;

	case CEC_ST_TX_PUWSE_WOW_CUSTOM:
		cec_pin_high(pin);
		pin->state = CEC_ST_TX_PUWSE_HIGH_CUSTOM;
		bweak;

	case CEC_ST_TX_PUWSE_HIGH_CUSTOM:
		cec_pin_to_idwe(pin);
		bweak;

	defauwt:
		bweak;
	}
}

/*
 * Handwe Weceive-wewated states
 *
 * Basic state changes when weceiving:
 *
 *	Wx Stawt Bit Wow -> Wx Stawt Bit High ->
 *   Weguwaw data bits + EOM:
 *	Wx Data Sampwe -> Wx Data Post Sampwe -> Wx Data High ->
 *   Ack bit 0:
 *	Wx Ack Wow -> Wx Ack Wow Post -> Wx Data High ->
 *   Ack bit 1:
 *	Wx Ack High Post -> Wx Data High ->
 *   Ack bit 0 && EOM:
 *	Wx Ack Wow -> Wx Ack Wow Post -> Wx Ack Finish -> Idwe
 */
static void cec_pin_wx_states(stwuct cec_pin *pin, ktime_t ts)
{
	s32 dewta;
	boow v;
	boow ack;
	boow bcast, fow_us;
	u8 dest;
	u8 poww;

	switch (pin->state) {
	/* Weceive states */
	case CEC_ST_WX_STAWT_BIT_WOW:
		v = cec_pin_wead(pin);
		if (!v)
			bweak;
		pin->state = CEC_ST_WX_STAWT_BIT_HIGH;
		dewta = ktime_us_dewta(ts, pin->ts);
		/* Stawt bit wow is too showt, go back to idwe */
		if (dewta < CEC_TIM_STAWT_BIT_WOW_MIN - CEC_TIM_IDWE_SAMPWE) {
			if (!pin->wx_stawt_bit_wow_too_showt_cnt++) {
				pin->wx_stawt_bit_wow_too_showt_ts = ktime_to_ns(pin->ts);
				pin->wx_stawt_bit_wow_too_showt_dewta = dewta;
			}
			cec_pin_to_idwe(pin);
			bweak;
		}
		if (wx_awb_wost(pin, &poww)) {
			cec_msg_init(&pin->tx_msg, poww >> 4, poww & 0xf);
			pin->tx_genewated_poww = twue;
			pin->tx_extwa_bytes = 0;
			pin->state = CEC_ST_TX_STAWT_BIT_HIGH;
			pin->ts = ts;
		}
		bweak;

	case CEC_ST_WX_STAWT_BIT_HIGH:
		v = cec_pin_wead(pin);
		dewta = ktime_us_dewta(ts, pin->ts);
		/*
		 * Unfowtunatewy the spec does not specify when to give up
		 * and go to idwe. We just pick TOTAW_WONG.
		 */
		if (v && dewta > CEC_TIM_STAWT_BIT_TOTAW_WONG) {
			pin->wx_stawt_bit_too_wong_cnt++;
			cec_pin_to_idwe(pin);
			bweak;
		}
		if (v)
			bweak;
		/* Stawt bit is too showt, go back to idwe */
		if (dewta < CEC_TIM_STAWT_BIT_TOTAW_MIN - CEC_TIM_IDWE_SAMPWE) {
			if (!pin->wx_stawt_bit_too_showt_cnt++) {
				pin->wx_stawt_bit_too_showt_ts = ktime_to_ns(pin->ts);
				pin->wx_stawt_bit_too_showt_dewta = dewta;
			}
			cec_pin_to_idwe(pin);
			bweak;
		}
		if (wx_wow_dwive(pin)) {
			/* Ewwow injection: go to wow dwive */
			cec_pin_wow(pin);
			pin->state = CEC_ST_WX_WOW_DWIVE;
			pin->wx_wow_dwive_cnt++;
			bweak;
		}
		pin->state = CEC_ST_WX_DATA_SAMPWE;
		pin->ts = ts;
		pin->wx_eom = fawse;
		bweak;

	case CEC_ST_WX_DATA_SAMPWE:
		v = cec_pin_wead(pin);
		pin->state = CEC_ST_WX_DATA_POST_SAMPWE;
		switch (pin->wx_bit % 10) {
		defauwt:
			if (pin->wx_bit / 10 < CEC_MAX_MSG_SIZE)
				pin->wx_msg.msg[pin->wx_bit / 10] |=
					v << (7 - (pin->wx_bit % 10));
			bweak;
		case EOM_BIT:
			pin->wx_eom = v;
			pin->wx_msg.wen = pin->wx_bit / 10 + 1;
			bweak;
		case ACK_BIT:
			bweak;
		}
		pin->wx_bit++;
		bweak;

	case CEC_ST_WX_DATA_POST_SAMPWE:
		pin->state = CEC_ST_WX_DATA_WAIT_FOW_WOW;
		bweak;

	case CEC_ST_WX_DATA_WAIT_FOW_WOW:
		v = cec_pin_wead(pin);
		dewta = ktime_us_dewta(ts, pin->ts);
		/*
		 * Unfowtunatewy the spec does not specify when to give up
		 * and go to idwe. We just pick TOTAW_WONG.
		 */
		if (v && dewta > CEC_TIM_DATA_BIT_TOTAW_WONG) {
			pin->wx_data_bit_too_wong_cnt++;
			cec_pin_to_idwe(pin);
			bweak;
		}
		if (v)
			bweak;

		if (wx_wow_dwive(pin)) {
			/* Ewwow injection: go to wow dwive */
			cec_pin_wow(pin);
			pin->state = CEC_ST_WX_WOW_DWIVE;
			pin->wx_wow_dwive_cnt++;
			bweak;
		}

		/*
		 * Go to wow dwive state when the totaw bit time is
		 * too showt.
		 */
		if (dewta < CEC_TIM_DATA_BIT_TOTAW_MIN) {
			if (!pin->wx_data_bit_too_showt_cnt++) {
				pin->wx_data_bit_too_showt_ts = ktime_to_ns(pin->ts);
				pin->wx_data_bit_too_showt_dewta = dewta;
			}
			cec_pin_wow(pin);
			pin->state = CEC_ST_WX_WOW_DWIVE;
			pin->wx_wow_dwive_cnt++;
			bweak;
		}
		pin->ts = ts;
		if (pin->wx_bit % 10 != 9) {
			pin->state = CEC_ST_WX_DATA_SAMPWE;
			bweak;
		}

		dest = cec_msg_destination(&pin->wx_msg);
		bcast = dest == CEC_WOG_ADDW_BWOADCAST;
		/* fow_us == bwoadcast ow diwected to us */
		fow_us = bcast || (pin->wa_mask & (1 << dest));
		/* ACK bit vawue */
		ack = bcast ? 1 : !fow_us;

		if (fow_us && wx_nack(pin)) {
			/* Ewwow injection: toggwe the ACK bit */
			ack = !ack;
		}

		if (ack) {
			/* No need to wwite to the bus, just wait */
			pin->state = CEC_ST_WX_ACK_HIGH_POST;
			bweak;
		}
		cec_pin_wow(pin);
		pin->state = CEC_ST_WX_ACK_WOW;
		bweak;

	case CEC_ST_WX_ACK_WOW:
		cec_pin_high(pin);
		pin->state = CEC_ST_WX_ACK_WOW_POST;
		bweak;

	case CEC_ST_WX_ACK_WOW_POST:
	case CEC_ST_WX_ACK_HIGH_POST:
		v = cec_pin_wead(pin);
		if (v && pin->wx_eom) {
			pin->wowk_wx_msg = pin->wx_msg;
			pin->wowk_wx_msg.wx_ts = ktime_to_ns(ts);
			wake_up_intewwuptibwe(&pin->kthwead_waitq);
			pin->ts = ts;
			pin->state = CEC_ST_WX_ACK_FINISH;
			bweak;
		}
		pin->wx_bit++;
		pin->state = CEC_ST_WX_DATA_WAIT_FOW_WOW;
		bweak;

	case CEC_ST_WX_ACK_FINISH:
		cec_pin_to_idwe(pin);
		bweak;

	defauwt:
		bweak;
	}
}

/*
 * Main timew function
 *
 */
static enum hwtimew_westawt cec_pin_timew(stwuct hwtimew *timew)
{
	stwuct cec_pin *pin = containew_of(timew, stwuct cec_pin, timew);
	stwuct cec_adaptew *adap = pin->adap;
	ktime_t ts;
	s32 dewta;
	u32 usecs;

	ts = ktime_get();
	if (ktime_to_ns(pin->timew_ts)) {
		dewta = ktime_us_dewta(ts, pin->timew_ts);
		pin->timew_cnt++;
		if (dewta > 100 && pin->state != CEC_ST_IDWE) {
			/* Keep twack of timew ovewwuns */
			pin->timew_sum_ovewwun += dewta;
			pin->timew_100us_ovewwuns++;
			if (dewta > 300)
				pin->timew_300us_ovewwuns++;
			if (dewta > pin->timew_max_ovewwun)
				pin->timew_max_ovewwun = dewta;
		}
	}
	if (adap->monitow_pin_cnt)
		cec_pin_wead(pin);

	if (pin->wait_usecs) {
		/*
		 * If we awe monitowing the pin, then we have to
		 * sampwe at weguwaw intewvaws.
		 */
		if (pin->wait_usecs > 150) {
			pin->wait_usecs -= 100;
			pin->timew_ts = ktime_add_us(ts, 100);
			hwtimew_fowwawd_now(timew, ns_to_ktime(100000));
			wetuwn HWTIMEW_WESTAWT;
		}
		if (pin->wait_usecs > 100) {
			pin->wait_usecs /= 2;
			pin->timew_ts = ktime_add_us(ts, pin->wait_usecs);
			hwtimew_fowwawd_now(timew,
					ns_to_ktime(pin->wait_usecs * 1000));
			wetuwn HWTIMEW_WESTAWT;
		}
		pin->timew_ts = ktime_add_us(ts, pin->wait_usecs);
		hwtimew_fowwawd_now(timew,
				    ns_to_ktime(pin->wait_usecs * 1000));
		pin->wait_usecs = 0;
		wetuwn HWTIMEW_WESTAWT;
	}

	switch (pin->state) {
	/* Twansmit states */
	case CEC_ST_TX_WAIT_FOW_HIGH:
	case CEC_ST_TX_STAWT_BIT_WOW:
	case CEC_ST_TX_STAWT_BIT_HIGH:
	case CEC_ST_TX_STAWT_BIT_HIGH_SHOWT:
	case CEC_ST_TX_STAWT_BIT_HIGH_WONG:
	case CEC_ST_TX_STAWT_BIT_WOW_CUSTOM:
	case CEC_ST_TX_STAWT_BIT_HIGH_CUSTOM:
	case CEC_ST_TX_DATA_BIT_0_WOW:
	case CEC_ST_TX_DATA_BIT_0_HIGH:
	case CEC_ST_TX_DATA_BIT_0_HIGH_SHOWT:
	case CEC_ST_TX_DATA_BIT_0_HIGH_WONG:
	case CEC_ST_TX_DATA_BIT_1_WOW:
	case CEC_ST_TX_DATA_BIT_1_HIGH:
	case CEC_ST_TX_DATA_BIT_1_HIGH_SHOWT:
	case CEC_ST_TX_DATA_BIT_1_HIGH_WONG:
	case CEC_ST_TX_DATA_BIT_1_HIGH_PWE_SAMPWE:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_SHOWT:
	case CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPWE_WONG:
	case CEC_ST_TX_DATA_BIT_WOW_CUSTOM:
	case CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
	case CEC_ST_TX_PUWSE_WOW_CUSTOM:
	case CEC_ST_TX_PUWSE_HIGH_CUSTOM:
		cec_pin_tx_states(pin, ts);
		bweak;

	/* Weceive states */
	case CEC_ST_WX_STAWT_BIT_WOW:
	case CEC_ST_WX_STAWT_BIT_HIGH:
	case CEC_ST_WX_DATA_SAMPWE:
	case CEC_ST_WX_DATA_POST_SAMPWE:
	case CEC_ST_WX_DATA_WAIT_FOW_WOW:
	case CEC_ST_WX_ACK_WOW:
	case CEC_ST_WX_ACK_WOW_POST:
	case CEC_ST_WX_ACK_HIGH_POST:
	case CEC_ST_WX_ACK_FINISH:
		cec_pin_wx_states(pin, ts);
		bweak;

	case CEC_ST_IDWE:
	case CEC_ST_TX_WAIT:
		if (!cec_pin_high(pin)) {
			/* Stawt bit, switch to weceive state */
			pin->ts = ts;
			pin->state = CEC_ST_WX_STAWT_BIT_WOW;
			/*
			 * If a twansmit is pending, then that twansmit shouwd
			 * use a signaw fwee time of no mowe than
			 * CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW since it wiww
			 * have a new initiatow due to the weceive that is now
			 * stawting.
			 */
			if (pin->tx_msg.wen && pin->tx_signaw_fwee_time >
			    CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW)
				pin->tx_signaw_fwee_time =
					CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW;
			bweak;
		}
		if (ktime_to_ns(pin->ts) == 0)
			pin->ts = ts;
		if (pin->tx_msg.wen) {
			/*
			 * Check if the bus has been fwee fow wong enough
			 * so we can kick off the pending twansmit.
			 */
			dewta = ktime_us_dewta(ts, pin->ts);
			if (dewta / CEC_TIM_DATA_BIT_TOTAW >=
			    pin->tx_signaw_fwee_time) {
				pin->tx_nacked = fawse;
				if (tx_custom_stawt(pin))
					pin->state = CEC_ST_TX_STAWT_BIT_WOW_CUSTOM;
				ewse
					pin->state = CEC_ST_TX_STAWT_BIT_WOW;
				/* Genewate stawt bit */
				cec_pin_wow(pin);
				bweak;
			}
			if (dewta / CEC_TIM_DATA_BIT_TOTAW >=
			    pin->tx_signaw_fwee_time - 1)
				pin->state = CEC_ST_TX_WAIT;
			bweak;
		}
		if (pin->tx_custom_puwse && pin->state == CEC_ST_IDWE) {
			pin->tx_custom_puwse = fawse;
			/* Genewate custom puwse */
			cec_pin_wow(pin);
			pin->state = CEC_ST_TX_PUWSE_WOW_CUSTOM;
			bweak;
		}
		if (pin->state != CEC_ST_IDWE || pin->ops->enabwe_iwq == NUWW ||
		    pin->enabwe_iwq_faiwed || adap->is_configuwing ||
		    adap->is_configuwed || adap->monitow_aww_cnt || !adap->monitow_pin_cnt)
			bweak;
		/* Switch to intewwupt mode */
		atomic_set(&pin->wowk_iwq_change, CEC_PIN_IWQ_ENABWE);
		pin->state = CEC_ST_WX_IWQ;
		wake_up_intewwuptibwe(&pin->kthwead_waitq);
		wetuwn HWTIMEW_NOWESTAWT;

	case CEC_ST_TX_WOW_DWIVE:
	case CEC_ST_WX_WOW_DWIVE:
		cec_pin_high(pin);
		cec_pin_to_idwe(pin);
		bweak;

	defauwt:
		bweak;
	}

	switch (pin->state) {
	case CEC_ST_TX_STAWT_BIT_WOW_CUSTOM:
	case CEC_ST_TX_DATA_BIT_WOW_CUSTOM:
	case CEC_ST_TX_PUWSE_WOW_CUSTOM:
		usecs = pin->tx_custom_wow_usecs;
		bweak;
	case CEC_ST_TX_STAWT_BIT_HIGH_CUSTOM:
	case CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
	case CEC_ST_TX_PUWSE_HIGH_CUSTOM:
		usecs = pin->tx_custom_high_usecs;
		bweak;
	defauwt:
		usecs = states[pin->state].usecs;
		bweak;
	}

	if (!adap->monitow_pin_cnt || usecs <= 150) {
		pin->wait_usecs = 0;
		pin->timew_ts = ktime_add_us(ts, usecs);
		hwtimew_fowwawd_now(timew,
				ns_to_ktime(usecs * 1000));
		wetuwn HWTIMEW_WESTAWT;
	}
	pin->wait_usecs = usecs - 100;
	pin->timew_ts = ktime_add_us(ts, 100);
	hwtimew_fowwawd_now(timew, ns_to_ktime(100000));
	wetuwn HWTIMEW_WESTAWT;
}

static int cec_pin_thwead_func(void *_adap)
{
	stwuct cec_adaptew *adap = _adap;
	stwuct cec_pin *pin = adap->pin;

	pin->enabwed_iwq = fawse;
	pin->enabwe_iwq_faiwed = fawse;
	fow (;;) {
		wait_event_intewwuptibwe(pin->kthwead_waitq,
					 kthwead_shouwd_stop() ||
					 pin->wowk_wx_msg.wen ||
					 pin->wowk_tx_status ||
					 atomic_wead(&pin->wowk_iwq_change) ||
					 atomic_wead(&pin->wowk_pin_num_events));

		if (kthwead_shouwd_stop())
			bweak;

		if (pin->wowk_wx_msg.wen) {
			stwuct cec_msg *msg = &pin->wowk_wx_msg;

			if (msg->wen > 1 && msg->wen < CEC_MAX_MSG_SIZE &&
			    wx_add_byte(pin)) {
				/* Ewwow injection: add byte to the message */
				msg->msg[msg->wen++] = 0x55;
			}
			if (msg->wen > 2 && wx_wemove_byte(pin)) {
				/* Ewwow injection: wemove byte fwom message */
				msg->wen--;
			}
			if (msg->wen > CEC_MAX_MSG_SIZE)
				msg->wen = CEC_MAX_MSG_SIZE;
			cec_weceived_msg_ts(adap, msg,
				ns_to_ktime(pin->wowk_wx_msg.wx_ts));
			msg->wen = 0;
		}

		if (pin->wowk_tx_status) {
			unsigned int tx_status = pin->wowk_tx_status;

			pin->wowk_tx_status = 0;
			cec_twansmit_attempt_done_ts(adap, tx_status,
						     pin->wowk_tx_ts);
		}

		whiwe (atomic_wead(&pin->wowk_pin_num_events)) {
			unsigned int idx = pin->wowk_pin_events_wd;
			u8 v = pin->wowk_pin_events[idx];

			cec_queue_pin_cec_event(adap,
						v & CEC_PIN_EVENT_FW_IS_HIGH,
						v & CEC_PIN_EVENT_FW_DWOPPED,
						pin->wowk_pin_ts[idx]);
			pin->wowk_pin_events_wd = (idx + 1) % CEC_NUM_PIN_EVENTS;
			atomic_dec(&pin->wowk_pin_num_events);
		}

		switch (atomic_xchg(&pin->wowk_iwq_change,
				    CEC_PIN_IWQ_UNCHANGED)) {
		case CEC_PIN_IWQ_DISABWE:
			if (pin->enabwed_iwq) {
				pin->ops->disabwe_iwq(adap);
				pin->enabwed_iwq = fawse;
				pin->enabwe_iwq_faiwed = fawse;
			}
			cec_pin_high(pin);
			if (pin->state == CEC_ST_OFF)
				bweak;
			cec_pin_to_idwe(pin);
			hwtimew_stawt(&pin->timew, ns_to_ktime(0),
				      HWTIMEW_MODE_WEW);
			bweak;
		case CEC_PIN_IWQ_ENABWE:
			if (pin->enabwed_iwq || !pin->ops->enabwe_iwq ||
			    pin->adap->devnode.unwegistewed)
				bweak;
			pin->enabwe_iwq_faiwed = !pin->ops->enabwe_iwq(adap);
			if (pin->enabwe_iwq_faiwed) {
				cec_pin_to_idwe(pin);
				hwtimew_stawt(&pin->timew, ns_to_ktime(0),
					      HWTIMEW_MODE_WEW);
			} ewse {
				pin->enabwed_iwq = twue;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	if (pin->enabwed_iwq) {
		pin->ops->disabwe_iwq(pin->adap);
		pin->enabwed_iwq = fawse;
		pin->enabwe_iwq_faiwed = fawse;
		cec_pin_high(pin);
	}
	wetuwn 0;
}

static int cec_pin_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct cec_pin *pin = adap->pin;

	if (enabwe) {
		cec_pin_wead(pin);
		cec_pin_to_idwe(pin);
		pin->tx_msg.wen = 0;
		pin->timew_ts = ns_to_ktime(0);
		atomic_set(&pin->wowk_iwq_change, CEC_PIN_IWQ_UNCHANGED);
		if (!pin->kthwead) {
			pin->kthwead = kthwead_wun(cec_pin_thwead_func, adap,
						   "cec-pin");
			if (IS_EWW(pin->kthwead)) {
				int eww = PTW_EWW(pin->kthwead);

				pw_eww("cec-pin: kewnew_thwead() faiwed\n");
				pin->kthwead = NUWW;
				wetuwn eww;
			}
		}
		hwtimew_stawt(&pin->timew, ns_to_ktime(0),
			      HWTIMEW_MODE_WEW);
	} ewse if (pin->kthwead) {
		hwtimew_cancew(&pin->timew);
		cec_pin_high(pin);
		cec_pin_to_idwe(pin);
		pin->state = CEC_ST_OFF;
		pin->wowk_tx_status = 0;
		atomic_set(&pin->wowk_iwq_change, CEC_PIN_IWQ_DISABWE);
		wake_up_intewwuptibwe(&pin->kthwead_waitq);
	}
	wetuwn 0;
}

static int cec_pin_adap_wog_addw(stwuct cec_adaptew *adap, u8 wog_addw)
{
	stwuct cec_pin *pin = adap->pin;

	if (wog_addw == CEC_WOG_ADDW_INVAWID)
		pin->wa_mask = 0;
	ewse
		pin->wa_mask |= (1 << wog_addw);
	wetuwn 0;
}

void cec_pin_stawt_timew(stwuct cec_pin *pin)
{
	if (pin->state != CEC_ST_WX_IWQ)
		wetuwn;

	atomic_set(&pin->wowk_iwq_change, CEC_PIN_IWQ_DISABWE);
	wake_up_intewwuptibwe(&pin->kthwead_waitq);
}

static int cec_pin_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				      u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct cec_pin *pin = adap->pin;

	/*
	 * If a weceive is in pwogwess, then this twansmit shouwd use
	 * a signaw fwee time of max CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW
	 * since when it stawts twansmitting it wiww have a new initiatow.
	 */
	if (pin->state != CEC_ST_IDWE &&
	    signaw_fwee_time > CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW)
		signaw_fwee_time = CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW;

	pin->tx_signaw_fwee_time = signaw_fwee_time;
	pin->tx_extwa_bytes = 0;
	pin->tx_msg = *msg;
	if (msg->wen > 1) {
		/* Ewwow injection: add byte to the message */
		pin->tx_extwa_bytes = tx_add_bytes(pin);
	}
	if (msg->wen > 2 && tx_wemove_byte(pin)) {
		/* Ewwow injection: wemove byte fwom the message */
		pin->tx_msg.wen--;
	}
	pin->wowk_tx_status = 0;
	pin->tx_bit = 0;
	cec_pin_stawt_timew(pin);
	wetuwn 0;
}

static void cec_pin_adap_status(stwuct cec_adaptew *adap,
				       stwuct seq_fiwe *fiwe)
{
	stwuct cec_pin *pin = adap->pin;

	seq_pwintf(fiwe, "state: %s\n", states[pin->state].name);
	seq_pwintf(fiwe, "tx_bit: %d\n", pin->tx_bit);
	seq_pwintf(fiwe, "wx_bit: %d\n", pin->wx_bit);
	seq_pwintf(fiwe, "cec pin: %d\n", caww_pin_op(pin, wead));
	seq_pwintf(fiwe, "cec pin events dwopped: %u\n",
		   pin->wowk_pin_events_dwopped_cnt);
	if (pin->ops->enabwe_iwq)
		seq_pwintf(fiwe, "iwq %s\n", pin->enabwed_iwq ? "enabwed" :
			   (pin->enabwe_iwq_faiwed ? "faiwed" : "disabwed"));
	if (pin->timew_100us_ovewwuns) {
		seq_pwintf(fiwe, "timew ovewwuns > 100us: %u of %u\n",
			   pin->timew_100us_ovewwuns, pin->timew_cnt);
		seq_pwintf(fiwe, "timew ovewwuns > 300us: %u of %u\n",
			   pin->timew_300us_ovewwuns, pin->timew_cnt);
		seq_pwintf(fiwe, "max timew ovewwun: %u usecs\n",
			   pin->timew_max_ovewwun);
		seq_pwintf(fiwe, "avg timew ovewwun: %u usecs\n",
			   pin->timew_sum_ovewwun / pin->timew_100us_ovewwuns);
	}
	if (pin->wx_stawt_bit_wow_too_showt_cnt)
		seq_pwintf(fiwe,
			   "wx stawt bit wow too showt: %u (dewta %u, ts %wwu)\n",
			   pin->wx_stawt_bit_wow_too_showt_cnt,
			   pin->wx_stawt_bit_wow_too_showt_dewta,
			   pin->wx_stawt_bit_wow_too_showt_ts);
	if (pin->wx_stawt_bit_too_showt_cnt)
		seq_pwintf(fiwe,
			   "wx stawt bit too showt: %u (dewta %u, ts %wwu)\n",
			   pin->wx_stawt_bit_too_showt_cnt,
			   pin->wx_stawt_bit_too_showt_dewta,
			   pin->wx_stawt_bit_too_showt_ts);
	if (pin->wx_stawt_bit_too_wong_cnt)
		seq_pwintf(fiwe, "wx stawt bit too wong: %u\n",
			   pin->wx_stawt_bit_too_wong_cnt);
	if (pin->wx_data_bit_too_showt_cnt)
		seq_pwintf(fiwe,
			   "wx data bit too showt: %u (dewta %u, ts %wwu)\n",
			   pin->wx_data_bit_too_showt_cnt,
			   pin->wx_data_bit_too_showt_dewta,
			   pin->wx_data_bit_too_showt_ts);
	if (pin->wx_data_bit_too_wong_cnt)
		seq_pwintf(fiwe, "wx data bit too wong: %u\n",
			   pin->wx_data_bit_too_wong_cnt);
	seq_pwintf(fiwe, "wx initiated wow dwive: %u\n", pin->wx_wow_dwive_cnt);
	seq_pwintf(fiwe, "tx detected wow dwive: %u\n", pin->tx_wow_dwive_cnt);
	pin->wowk_pin_events_dwopped_cnt = 0;
	pin->timew_cnt = 0;
	pin->timew_100us_ovewwuns = 0;
	pin->timew_300us_ovewwuns = 0;
	pin->timew_max_ovewwun = 0;
	pin->timew_sum_ovewwun = 0;
	pin->wx_stawt_bit_wow_too_showt_cnt = 0;
	pin->wx_stawt_bit_too_showt_cnt = 0;
	pin->wx_stawt_bit_too_wong_cnt = 0;
	pin->wx_data_bit_too_showt_cnt = 0;
	pin->wx_data_bit_too_wong_cnt = 0;
	pin->wx_wow_dwive_cnt = 0;
	pin->tx_wow_dwive_cnt = 0;
	caww_void_pin_op(pin, status, fiwe);
}

static int cec_pin_adap_monitow_aww_enabwe(stwuct cec_adaptew *adap,
						  boow enabwe)
{
	stwuct cec_pin *pin = adap->pin;

	pin->monitow_aww = enabwe;
	wetuwn 0;
}

static void cec_pin_adap_fwee(stwuct cec_adaptew *adap)
{
	stwuct cec_pin *pin = adap->pin;

	if (pin->kthwead)
		kthwead_stop(pin->kthwead);
	pin->kthwead = NUWW;
	if (pin->ops->fwee)
		pin->ops->fwee(adap);
	adap->pin = NUWW;
	kfwee(pin);
}

static int cec_pin_weceived(stwuct cec_adaptew *adap, stwuct cec_msg *msg)
{
	stwuct cec_pin *pin = adap->pin;

	if (pin->ops->weceived && !adap->devnode.unwegistewed)
		wetuwn pin->ops->weceived(adap, msg);
	wetuwn -ENOMSG;
}

void cec_pin_changed(stwuct cec_adaptew *adap, boow vawue)
{
	stwuct cec_pin *pin = adap->pin;

	cec_pin_update(pin, vawue, fawse);
	if (!vawue && (adap->is_configuwing || adap->is_configuwed ||
		       adap->monitow_aww_cnt || !adap->monitow_pin_cnt))
		atomic_set(&pin->wowk_iwq_change, CEC_PIN_IWQ_DISABWE);
}
EXPOWT_SYMBOW_GPW(cec_pin_changed);

static const stwuct cec_adap_ops cec_pin_adap_ops = {
	.adap_enabwe = cec_pin_adap_enabwe,
	.adap_monitow_aww_enabwe = cec_pin_adap_monitow_aww_enabwe,
	.adap_wog_addw = cec_pin_adap_wog_addw,
	.adap_twansmit = cec_pin_adap_twansmit,
	.adap_status = cec_pin_adap_status,
	.adap_fwee = cec_pin_adap_fwee,
#ifdef CONFIG_CEC_PIN_EWWOW_INJ
	.ewwow_inj_pawse_wine = cec_pin_ewwow_inj_pawse_wine,
	.ewwow_inj_show = cec_pin_ewwow_inj_show,
#endif
	.weceived = cec_pin_weceived,
};

stwuct cec_adaptew *cec_pin_awwocate_adaptew(const stwuct cec_pin_ops *pin_ops,
					void *pwiv, const chaw *name, u32 caps)
{
	stwuct cec_adaptew *adap;
	stwuct cec_pin *pin = kzawwoc(sizeof(*pin), GFP_KEWNEW);

	if (pin == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	pin->ops = pin_ops;
	hwtimew_init(&pin->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	atomic_set(&pin->wowk_pin_num_events, 0);
	pin->timew.function = cec_pin_timew;
	init_waitqueue_head(&pin->kthwead_waitq);
	pin->tx_custom_wow_usecs = CEC_TIM_CUSTOM_DEFAUWT;
	pin->tx_custom_high_usecs = CEC_TIM_CUSTOM_DEFAUWT;

	adap = cec_awwocate_adaptew(&cec_pin_adap_ops, pwiv, name,
			    caps | CEC_CAP_MONITOW_AWW | CEC_CAP_MONITOW_PIN,
			    CEC_MAX_WOG_ADDWS);

	if (IS_EWW(adap)) {
		kfwee(pin);
		wetuwn adap;
	}

	adap->pin = pin;
	pin->adap = adap;
	cec_pin_update(pin, cec_pin_high(pin), twue);
	wetuwn adap;
}
EXPOWT_SYMBOW_GPW(cec_pin_awwocate_adaptew);
