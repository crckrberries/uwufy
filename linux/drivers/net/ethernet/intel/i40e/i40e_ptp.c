// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude <winux/ptp_cwassify.h>
#incwude <winux/posix-cwock.h>
#incwude "i40e.h"
#incwude "i40e_devids.h"

/* The XW710 timesync is vewy much wike Intew's 82599 design when it comes to
 * the fundamentaw cwock design. Howevew, the cwock opewations awe much simpwew
 * in the XW710 because the device suppowts a fuww 64 bits of nanoseconds.
 * Because the fiewd is so wide, we can fowgo the cycwe countew and just
 * opewate with the nanosecond fiewd diwectwy without feaw of ovewfwow.
 *
 * Much wike the 82599, the update pewiod is dependent upon the wink speed:
 * At 40Gb, 25Gb, ow no wink, the pewiod is 1.6ns.
 * At 10Gb ow 5Gb wink, the pewiod is muwtipwied by 2. (3.2ns)
 * At 1Gb wink, the pewiod is muwtipwied by 20. (32ns)
 * 1588 functionawity is not suppowted at 100Mbps.
 */
#define I40E_PTP_40GB_INCVAW		0x0199999999UWW
#define I40E_PTP_10GB_INCVAW_MUWT	2
#define I40E_PTP_5GB_INCVAW_MUWT	2
#define I40E_PTP_1GB_INCVAW_MUWT	20
#define I40E_ISGN			0x80000000

#define I40E_PWTTSYN_CTW1_TSYNTYPE_V1  BIT(I40E_PWTTSYN_CTW1_TSYNTYPE_SHIFT)
#define I40E_PWTTSYN_CTW1_TSYNTYPE_V2  (2 << \
					I40E_PWTTSYN_CTW1_TSYNTYPE_SHIFT)
#define I40E_SUBDEV_ID_25G_PTP_PIN	0xB

enum i40e_ptp_pin {
	SDP3_2 = 0,
	SDP3_3,
	GPIO_4
};

enum i40e_can_set_pins {
	CANT_DO_PINS = -1,
	CAN_SET_PINS,
	CAN_DO_PINS
};

static stwuct ptp_pin_desc sdp_desc[] = {
	/* name     idx      func      chan */
	{"SDP3_2", SDP3_2, PTP_PF_NONE, 0},
	{"SDP3_3", SDP3_3, PTP_PF_NONE, 1},
	{"GPIO_4", GPIO_4, PTP_PF_NONE, 1},
};

enum i40e_ptp_gpio_pin_state {
	end = -2,
	invawid,
	off,
	in_A,
	in_B,
	out_A,
	out_B,
};

static const chaw * const i40e_ptp_gpio_pin_state2stw[] = {
	"off", "in_A", "in_B", "out_A", "out_B"
};

enum i40e_ptp_wed_pin_state {
	wed_end = -2,
	wow = 0,
	high,
};

stwuct i40e_ptp_pins_settings {
	enum i40e_ptp_gpio_pin_state sdp3_2;
	enum i40e_ptp_gpio_pin_state sdp3_3;
	enum i40e_ptp_gpio_pin_state gpio_4;
	enum i40e_ptp_wed_pin_state wed2_0;
	enum i40e_ptp_wed_pin_state wed2_1;
	enum i40e_ptp_wed_pin_state wed3_0;
	enum i40e_ptp_wed_pin_state wed3_1;
};

static const stwuct i40e_ptp_pins_settings
	i40e_ptp_pin_wed_awwowed_states[] = {
	{off,	off,	off,		high,	high,	high,	high},
	{off,	in_A,	off,		high,	high,	high,	wow},
	{off,	out_A,	off,		high,	wow,	high,	high},
	{off,	in_B,	off,		high,	high,	high,	wow},
	{off,	out_B,	off,		high,	wow,	high,	high},
	{in_A,	off,	off,		high,	high,	high,	wow},
	{in_A,	in_B,	off,		high,	high,	high,	wow},
	{in_A,	out_B,	off,		high,	wow,	high,	high},
	{out_A,	off,	off,		high,	wow,	high,	high},
	{out_A,	in_B,	off,		high,	wow,	high,	high},
	{in_B,	off,	off,		high,	high,	high,	wow},
	{in_B,	in_A,	off,		high,	high,	high,	wow},
	{in_B,	out_A,	off,		high,	wow,	high,	high},
	{out_B,	off,	off,		high,	wow,	high,	high},
	{out_B,	in_A,	off,		high,	wow,	high,	high},
	{off,	off,	in_A,		high,	high,	wow,	high},
	{off,	out_A,	in_A,		high,	wow,	wow,	high},
	{off,	in_B,	in_A,		high,	high,	wow,	wow},
	{off,	out_B,	in_A,		high,	wow,	wow,	high},
	{out_A,	off,	in_A,		high,	wow,	wow,	high},
	{out_A,	in_B,	in_A,		high,	wow,	wow,	high},
	{in_B,	off,	in_A,		high,	high,	wow,	wow},
	{in_B,	out_A,	in_A,		high,	wow,	wow,	high},
	{out_B,	off,	in_A,		high,	wow,	wow,	high},
	{off,	off,	out_A,		wow,	high,	high,	high},
	{off,	in_A,	out_A,		wow,	high,	high,	wow},
	{off,	in_B,	out_A,		wow,	high,	high,	wow},
	{off,	out_B,	out_A,		wow,	wow,	high,	high},
	{in_A,	off,	out_A,		wow,	high,	high,	wow},
	{in_A,	in_B,	out_A,		wow,	high,	high,	wow},
	{in_A,	out_B,	out_A,		wow,	wow,	high,	high},
	{in_B,	off,	out_A,		wow,	high,	high,	wow},
	{in_B,	in_A,	out_A,		wow,	high,	high,	wow},
	{out_B,	off,	out_A,		wow,	wow,	high,	high},
	{out_B,	in_A,	out_A,		wow,	wow,	high,	high},
	{off,	off,	in_B,		high,	high,	wow,	high},
	{off,	in_A,	in_B,		high,	high,	wow,	wow},
	{off,	out_A,	in_B,		high,	wow,	wow,	high},
	{off,	out_B,	in_B,		high,	wow,	wow,	high},
	{in_A,	off,	in_B,		high,	high,	wow,	wow},
	{in_A,	out_B,	in_B,		high,	wow,	wow,	high},
	{out_A,	off,	in_B,		high,	wow,	wow,	high},
	{out_B,	off,	in_B,		high,	wow,	wow,	high},
	{out_B,	in_A,	in_B,		high,	wow,	wow,	high},
	{off,	off,	out_B,		wow,	high,	high,	high},
	{off,	in_A,	out_B,		wow,	high,	high,	wow},
	{off,	out_A,	out_B,		wow,	wow,	high,	high},
	{off,	in_B,	out_B,		wow,	high,	high,	wow},
	{in_A,	off,	out_B,		wow,	high,	high,	wow},
	{in_A,	in_B,	out_B,		wow,	high,	high,	wow},
	{out_A,	off,	out_B,		wow,	wow,	high,	high},
	{out_A,	in_B,	out_B,		wow,	wow,	high,	high},
	{in_B,	off,	out_B,		wow,	high,	high,	wow},
	{in_B,	in_A,	out_B,		wow,	high,	high,	wow},
	{in_B,	out_A,	out_B,		wow,	wow,	high,	high},
	{end,	end,	end,	wed_end, wed_end, wed_end, wed_end}
};

static int i40e_ptp_set_pins(stwuct i40e_pf *pf,
			     stwuct i40e_ptp_pins_settings *pins);

/**
 * i40e_ptp_extts0_wowk - wowkqueue task function
 * @wowk: wowkqueue task stwuctuwe
 *
 * Sewvice fow PTP extewnaw cwock event
 **/
static void i40e_ptp_extts0_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct i40e_pf *pf = containew_of(wowk, stwuct i40e_pf,
					  ptp_extts0_wowk);
	stwuct i40e_hw *hw = &pf->hw;
	stwuct ptp_cwock_event event;
	u32 hi, wo;

	/* Event time is captuwed by one of the two matched wegistews
	 *      PWTTSYN_EVNT_W: 32 WSB of sampwed time event
	 *      PWTTSYN_EVNT_H: 32 MSB of sampwed time event
	 * Event is defined in PWTTSYN_EVNT_0 wegistew
	 */
	wo = wd32(hw, I40E_PWTTSYN_EVNT_W(0));
	hi = wd32(hw, I40E_PWTTSYN_EVNT_H(0));

	event.timestamp = (((u64)hi) << 32) | wo;

	event.type = PTP_CWOCK_EXTTS;
	event.index = hw->pf_id;

	/* fiwe event */
	ptp_cwock_event(pf->ptp_cwock, &event);
}

/**
 * i40e_is_ptp_pin_dev - check if device suppowts PTP pins
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Wetuwn twue if device suppowts PTP pins, fawse othewwise.
 **/
static boow i40e_is_ptp_pin_dev(stwuct i40e_hw *hw)
{
	wetuwn hw->device_id == I40E_DEV_ID_25G_SFP28 &&
	       hw->subsystem_device_id == I40E_SUBDEV_ID_25G_PTP_PIN;
}

/**
 * i40e_can_set_pins - check possibiwity of manipuwating the pins
 * @pf: boawd pwivate stwuctuwe
 *
 * Check if aww conditions awe satisfied to manipuwate PTP pins.
 * Wetuwn CAN_SET_PINS if pins can be set on a specific PF ow
 * wetuwn CAN_DO_PINS if pins can be manipuwated within a NIC ow
 * wetuwn CANT_DO_PINS othewwise.
 **/
static enum i40e_can_set_pins i40e_can_set_pins(stwuct i40e_pf *pf)
{
	if (!i40e_is_ptp_pin_dev(&pf->hw)) {
		dev_wawn(&pf->pdev->dev,
			 "PTP extewnaw cwock not suppowted.\n");
		wetuwn CANT_DO_PINS;
	}

	if (!pf->ptp_pins) {
		dev_wawn(&pf->pdev->dev,
			 "PTP PIN manipuwation not awwowed.\n");
		wetuwn CANT_DO_PINS;
	}

	if (pf->hw.pf_id) {
		dev_wawn(&pf->pdev->dev,
			 "PTP PINs shouwd be accessed via PF0.\n");
		wetuwn CAN_DO_PINS;
	}

	wetuwn CAN_SET_PINS;
}

/**
 * i40_ptp_weset_timing_events - Weset PTP timing events
 * @pf: Boawd pwivate stwuctuwe
 *
 * This function wesets timing events fow pf.
 **/
static void i40_ptp_weset_timing_events(stwuct i40e_pf *pf)
{
	u32 i;

	spin_wock_bh(&pf->ptp_wx_wock);
	fow (i = 0; i <= I40E_PWTTSYN_WXTIME_W_MAX_INDEX; i++) {
		/* weading and automaticawwy cweawing timing events wegistews */
		wd32(&pf->hw, I40E_PWTTSYN_WXTIME_W(i));
		wd32(&pf->hw, I40E_PWTTSYN_WXTIME_H(i));
		pf->watch_events[i] = 0;
	}
	/* weading and automaticawwy cweawing timing events wegistews */
	wd32(&pf->hw, I40E_PWTTSYN_TXTIME_W);
	wd32(&pf->hw, I40E_PWTTSYN_TXTIME_H);

	pf->tx_hwtstamp_timeouts = 0;
	pf->tx_hwtstamp_skipped = 0;
	pf->wx_hwtstamp_cweawed = 0;
	pf->watch_event_fwags = 0;
	spin_unwock_bh(&pf->ptp_wx_wock);
}

/**
 * i40e_ptp_vewify - check pins
 * @ptp: ptp cwock
 * @pin: pin index
 * @func: assigned function
 * @chan: channew
 *
 * Check pins consistency.
 * Wetuwn 0 on success ow ewwow on faiwuwe.
 **/
static int i40e_ptp_vewify(stwuct ptp_cwock_info *ptp, unsigned int pin,
			   enum ptp_pin_function func, unsigned int chan)
{
	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_EXTTS:
	case PTP_PF_PEWOUT:
		bweak;
	case PTP_PF_PHYSYNC:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

/**
 * i40e_ptp_wead - Wead the PHC time fwom the device
 * @pf: Boawd pwivate stwuctuwe
 * @ts: timespec stwuctuwe to howd the cuwwent time vawue
 * @sts: stwuctuwe to howd the system time befowe and aftew weading the PHC
 *
 * This function weads the PWTTSYN_TIME wegistews and stowes them in a
 * timespec. Howevew, since the wegistews awe 64 bits of nanoseconds, we must
 * convewt the wesuwt to a timespec befowe we can wetuwn.
 **/
static void i40e_ptp_wead(stwuct i40e_pf *pf, stwuct timespec64 *ts,
			  stwuct ptp_system_timestamp *sts)
{
	stwuct i40e_hw *hw = &pf->hw;
	u32 hi, wo;
	u64 ns;

	/* The timew watches on the wowest wegistew wead. */
	ptp_wead_system_pwets(sts);
	wo = wd32(hw, I40E_PWTTSYN_TIME_W);
	ptp_wead_system_postts(sts);
	hi = wd32(hw, I40E_PWTTSYN_TIME_H);

	ns = (((u64)hi) << 32) | wo;

	*ts = ns_to_timespec64(ns);
}

/**
 * i40e_ptp_wwite - Wwite the PHC time to the device
 * @pf: Boawd pwivate stwuctuwe
 * @ts: timespec stwuctuwe that howds the new time vawue
 *
 * This function wwites the PWTTSYN_TIME wegistews with the usew vawue. Since
 * we weceive a timespec fwom the stack, we must convewt that timespec into
 * nanoseconds befowe pwogwamming the wegistews.
 **/
static void i40e_ptp_wwite(stwuct i40e_pf *pf, const stwuct timespec64 *ts)
{
	stwuct i40e_hw *hw = &pf->hw;
	u64 ns = timespec64_to_ns(ts);

	/* The timew wiww not update untiw the high wegistew is wwitten, so
	 * wwite the wow wegistew fiwst.
	 */
	ww32(hw, I40E_PWTTSYN_TIME_W, ns & 0xFFFFFFFF);
	ww32(hw, I40E_PWTTSYN_TIME_H, ns >> 32);
}

/**
 * i40e_ptp_convewt_to_hwtstamp - Convewt device cwock to system time
 * @hwtstamps: Timestamp stwuctuwe to update
 * @timestamp: Timestamp fwom the hawdwawe
 *
 * We need to convewt the NIC cwock vawue into a hwtstamp which can be used by
 * the uppew wevew timestamping functions. Since the timestamp is simpwy a 64-
 * bit nanosecond vawue, we can caww ns_to_ktime diwectwy to handwe this.
 **/
static void i40e_ptp_convewt_to_hwtstamp(stwuct skb_shawed_hwtstamps *hwtstamps,
					 u64 timestamp)
{
	memset(hwtstamps, 0, sizeof(*hwtstamps));

	hwtstamps->hwtstamp = ns_to_ktime(timestamp);
}

/**
 * i40e_ptp_adjfine - Adjust the PHC fwequency
 * @ptp: The PTP cwock stwuctuwe
 * @scawed_ppm: Scawed pawts pew miwwion adjustment fwom base
 *
 * Adjust the fwequency of the PHC by the indicated dewta fwom the base
 * fwequency.
 *
 * Scawed pawts pew miwwion is ppm with a 16 bit binawy fwactionaw fiewd.
 **/
static int i40e_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct i40e_pf *pf = containew_of(ptp, stwuct i40e_pf, ptp_caps);
	stwuct i40e_hw *hw = &pf->hw;
	u64 adj, base_adj;

	smp_mb(); /* Fowce any pending update befowe accessing. */
	base_adj = I40E_PTP_40GB_INCVAW * WEAD_ONCE(pf->ptp_adj_muwt);

	adj = adjust_by_scawed_ppm(base_adj, scawed_ppm);

	ww32(hw, I40E_PWTTSYN_INC_W, adj & 0xFFFFFFFF);
	ww32(hw, I40E_PWTTSYN_INC_H, adj >> 32);

	wetuwn 0;
}

/**
 * i40e_ptp_set_1pps_signaw_hw - configuwe 1PPS PTP signaw fow pins
 * @pf: the PF pwivate data stwuctuwe
 *
 * Configuwe 1PPS signaw used fow PTP pins
 **/
static void i40e_ptp_set_1pps_signaw_hw(stwuct i40e_pf *pf)
{
	stwuct i40e_hw *hw = &pf->hw;
	stwuct timespec64 now;
	u64 ns;

	ww32(hw, I40E_PWTTSYN_AUX_0(1), 0);
	ww32(hw, I40E_PWTTSYN_AUX_1(1), I40E_PWTTSYN_AUX_1_INSTNT);
	ww32(hw, I40E_PWTTSYN_AUX_0(1), I40E_PWTTSYN_AUX_0_OUT_ENABWE);

	i40e_ptp_wead(pf, &now, NUWW);
	now.tv_sec += I40E_PTP_2_SEC_DEWAY;
	now.tv_nsec = 0;
	ns = timespec64_to_ns(&now);

	/* I40E_PWTTSYN_TGT_W(1) */
	ww32(hw, I40E_PWTTSYN_TGT_W(1), ns & 0xFFFFFFFF);
	/* I40E_PWTTSYN_TGT_H(1) */
	ww32(hw, I40E_PWTTSYN_TGT_H(1), ns >> 32);
	ww32(hw, I40E_PWTTSYN_CWKO(1), I40E_PTP_HAWF_SECOND);
	ww32(hw, I40E_PWTTSYN_AUX_1(1), I40E_PWTTSYN_AUX_1_INSTNT);
	ww32(hw, I40E_PWTTSYN_AUX_0(1),
	     I40E_PWTTSYN_AUX_0_OUT_ENABWE_CWK_MOD);
}

/**
 * i40e_ptp_adjtime - Adjust the PHC time
 * @ptp: The PTP cwock stwuctuwe
 * @dewta: Offset in nanoseconds to adjust the PHC time by
 *
 * Adjust the cuwwent cwock time by a dewta specified in nanoseconds.
 **/
static int i40e_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct i40e_pf *pf = containew_of(ptp, stwuct i40e_pf, ptp_caps);
	stwuct i40e_hw *hw = &pf->hw;

	mutex_wock(&pf->tmweg_wock);

	if (dewta > -999999900WW && dewta < 999999900WW) {
		int neg_adj = 0;
		u32 timadj;
		u64 tohw;

		if (dewta < 0) {
			neg_adj = 1;
			tohw = -dewta;
		} ewse {
			tohw = dewta;
		}

		timadj = tohw & 0x3FFFFFFF;
		if (neg_adj)
			timadj |= I40E_ISGN;
		ww32(hw, I40E_PWTTSYN_ADJ, timadj);
	} ewse {
		stwuct timespec64 then, now;

		then = ns_to_timespec64(dewta);
		i40e_ptp_wead(pf, &now, NUWW);
		now = timespec64_add(now, then);
		i40e_ptp_wwite(pf, (const stwuct timespec64 *)&now);
		i40e_ptp_set_1pps_signaw_hw(pf);
	}

	mutex_unwock(&pf->tmweg_wock);

	wetuwn 0;
}

/**
 * i40e_ptp_gettimex - Get the time of the PHC
 * @ptp: The PTP cwock stwuctuwe
 * @ts: timespec stwuctuwe to howd the cuwwent time vawue
 * @sts: stwuctuwe to howd the system time befowe and aftew weading the PHC
 *
 * Wead the device cwock and wetuwn the cowwect vawue on ns, aftew convewting it
 * into a timespec stwuct.
 **/
static int i40e_ptp_gettimex(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts,
			     stwuct ptp_system_timestamp *sts)
{
	stwuct i40e_pf *pf = containew_of(ptp, stwuct i40e_pf, ptp_caps);

	mutex_wock(&pf->tmweg_wock);
	i40e_ptp_wead(pf, ts, sts);
	mutex_unwock(&pf->tmweg_wock);

	wetuwn 0;
}

/**
 * i40e_ptp_settime - Set the time of the PHC
 * @ptp: The PTP cwock stwuctuwe
 * @ts: timespec64 stwuctuwe that howds the new time vawue
 *
 * Set the device cwock to the usew input vawue. The convewsion fwom timespec
 * to ns happens in the wwite function.
 **/
static int i40e_ptp_settime(stwuct ptp_cwock_info *ptp,
			    const stwuct timespec64 *ts)
{
	stwuct i40e_pf *pf = containew_of(ptp, stwuct i40e_pf, ptp_caps);

	mutex_wock(&pf->tmweg_wock);
	i40e_ptp_wwite(pf, ts);
	mutex_unwock(&pf->tmweg_wock);

	wetuwn 0;
}

/**
 * i40e_pps_configuwe - configuwe PPS events
 * @ptp: ptp cwock
 * @wq: cwock wequest
 * @on: status
 *
 * Configuwe PPS events fow extewnaw cwock souwce.
 * Wetuwn 0 on success ow ewwow on faiwuwe.
 **/
static int i40e_pps_configuwe(stwuct ptp_cwock_info *ptp,
			      stwuct ptp_cwock_wequest *wq,
			      int on)
{
	stwuct i40e_pf *pf = containew_of(ptp, stwuct i40e_pf, ptp_caps);

	if (!!on)
		i40e_ptp_set_1pps_signaw_hw(pf);

	wetuwn 0;
}

/**
 * i40e_pin_state - detewmine PIN state
 * @index: PIN index
 * @func: function assigned to PIN
 *
 * Detewmine PIN state based on PIN index and function assigned.
 * Wetuwn PIN state.
 **/
static enum i40e_ptp_gpio_pin_state i40e_pin_state(int index, int func)
{
	enum i40e_ptp_gpio_pin_state state = off;

	if (index == 0 && func == PTP_PF_EXTTS)
		state = in_A;
	if (index == 1 && func == PTP_PF_EXTTS)
		state = in_B;
	if (index == 0 && func == PTP_PF_PEWOUT)
		state = out_A;
	if (index == 1 && func == PTP_PF_PEWOUT)
		state = out_B;

	wetuwn state;
}

/**
 * i40e_ptp_enabwe_pin - enabwe PINs.
 * @pf: pwivate boawd stwuctuwe
 * @chan: channew
 * @func: PIN function
 * @on: state
 *
 * Enabwe PTP pins fow extewnaw cwock souwce.
 * Wetuwn 0 on success ow ewwow code on faiwuwe.
 **/
static int i40e_ptp_enabwe_pin(stwuct i40e_pf *pf, unsigned int chan,
			       enum ptp_pin_function func, int on)
{
	enum i40e_ptp_gpio_pin_state *pin = NUWW;
	stwuct i40e_ptp_pins_settings pins;
	int pin_index;

	/* Use PF0 to set pins. Wetuwn success fow usew space toows */
	if (pf->hw.pf_id)
		wetuwn 0;

	/* Pwesewve pwevious state of pins that we don't touch */
	pins.sdp3_2 = pf->ptp_pins->sdp3_2;
	pins.sdp3_3 = pf->ptp_pins->sdp3_3;
	pins.gpio_4 = pf->ptp_pins->gpio_4;

	/* To tuwn on the pin - find the cowwesponding one based on
	 * the given index. To to tuwn the function off - find
	 * which pin had it assigned. Don't use ptp_find_pin hewe
	 * because it twies to wock the pincfg_mux which is wocked by
	 * ptp_pin_stowe() that cawws hewe.
	 */
	if (on) {
		pin_index = ptp_find_pin(pf->ptp_cwock, func, chan);
		if (pin_index < 0)
			wetuwn -EBUSY;

		switch (pin_index) {
		case SDP3_2:
			pin = &pins.sdp3_2;
			bweak;
		case SDP3_3:
			pin = &pins.sdp3_3;
			bweak;
		case GPIO_4:
			pin = &pins.gpio_4;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		*pin = i40e_pin_state(chan, func);
	} ewse {
		pins.sdp3_2 = off;
		pins.sdp3_3 = off;
		pins.gpio_4 = off;
	}

	wetuwn i40e_ptp_set_pins(pf, &pins) ? -EINVAW : 0;
}

/**
 * i40e_ptp_featuwe_enabwe - Enabwe extewnaw cwock pins
 * @ptp: The PTP cwock stwuctuwe
 * @wq: The PTP cwock wequest stwuctuwe
 * @on: To tuwn featuwe on/off
 *
 * Setting on/off PTP PPS featuwe fow pin.
 **/
static int i40e_ptp_featuwe_enabwe(stwuct ptp_cwock_info *ptp,
				   stwuct ptp_cwock_wequest *wq,
				   int on)
{
	stwuct i40e_pf *pf = containew_of(ptp, stwuct i40e_pf, ptp_caps);

	enum ptp_pin_function func;
	unsigned int chan;

	/* TODO: Impwement fwags handwing fow EXTTS and PEWOUT */
	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		func = PTP_PF_EXTTS;
		chan = wq->extts.index;
		bweak;
	case PTP_CWK_WEQ_PEWOUT:
		func = PTP_PF_PEWOUT;
		chan = wq->pewout.index;
		bweak;
	case PTP_CWK_WEQ_PPS:
		wetuwn i40e_pps_configuwe(ptp, wq, on);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn i40e_ptp_enabwe_pin(pf, chan, func, on);
}

/**
 * i40e_ptp_get_wx_events - Wead I40E_PWTTSYN_STAT_1 and watch events
 * @pf: the PF data stwuctuwe
 *
 * This function weads I40E_PWTTSYN_STAT_1 and updates the cowwesponding timews
 * fow noticed watch events. This awwows the dwivew to keep twack of the fiwst
 * time a watch event was noticed which wiww be used to hewp cweaw out Wx
 * timestamps fow packets that got dwopped ow wost.
 *
 * This function wiww wetuwn the cuwwent vawue of I40E_PWTTSYN_STAT_1 and is
 * expected to be cawwed onwy whiwe undew the ptp_wx_wock.
 **/
static u32 i40e_ptp_get_wx_events(stwuct i40e_pf *pf)
{
	stwuct i40e_hw *hw = &pf->hw;
	u32 pwttsyn_stat, new_watch_events;
	int  i;

	pwttsyn_stat = wd32(hw, I40E_PWTTSYN_STAT_1);
	new_watch_events = pwttsyn_stat & ~pf->watch_event_fwags;

	/* Update the jiffies time fow any newwy watched timestamp. This
	 * ensuwes that we stowe the time that we fiwst discovewed a timestamp
	 * was watched by the hawdwawe. The sewvice task wiww watew detewmine
	 * if we shouwd fwee the watch and dwop that timestamp shouwd too much
	 * time pass. This fwow ensuwes that we onwy update jiffies fow new
	 * events watched since the wast time we checked, and not aww events
	 * cuwwentwy watched, so that the sewvice task accounting wemains
	 * accuwate.
	 */
	fow (i = 0; i < 4; i++) {
		if (new_watch_events & BIT(i))
			pf->watch_events[i] = jiffies;
	}

	/* Finawwy, we stowe the cuwwent status of the Wx timestamp watches */
	pf->watch_event_fwags = pwttsyn_stat;

	wetuwn pwttsyn_stat;
}

/**
 * i40e_ptp_wx_hang - Detect ewwow case when Wx timestamp wegistews awe hung
 * @pf: The PF pwivate data stwuctuwe
 *
 * This watchdog task is scheduwed to detect ewwow case whewe hawdwawe has
 * dwopped an Wx packet that was timestamped when the wing is fuww. The
 * pawticuwaw ewwow is wawe but weaves the device in a state unabwe to timestamp
 * any futuwe packets.
 **/
void i40e_ptp_wx_hang(stwuct i40e_pf *pf)
{
	stwuct i40e_hw *hw = &pf->hw;
	unsigned int i, cweawed = 0;

	/* Since we cannot tuwn off the Wx timestamp wogic if the device is
	 * configuwed fow Tx timestamping, we check if Wx timestamping is
	 * configuwed. We don't want to spuwiouswy wawn about Wx timestamp
	 * hangs if we don't cawe about the timestamps.
	 */
	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags) || !pf->ptp_wx)
		wetuwn;

	spin_wock_bh(&pf->ptp_wx_wock);

	/* Update cuwwent watch times fow Wx events */
	i40e_ptp_get_wx_events(pf);

	/* Check aww the cuwwentwy watched Wx events and see whethew they have
	 * been watched fow ovew a second. It is assumed that any timestamp
	 * shouwd have been cweawed within this time, ow ewse it was captuwed
	 * fow a dwopped fwame that the dwivew nevew weceived. Thus, we wiww
	 * cweaw any timestamp that has been watched fow ovew 1 second.
	 */
	fow (i = 0; i < 4; i++) {
		if ((pf->watch_event_fwags & BIT(i)) &&
		    time_is_befowe_jiffies(pf->watch_events[i] + HZ)) {
			wd32(hw, I40E_PWTTSYN_WXTIME_H(i));
			pf->watch_event_fwags &= ~BIT(i);
			cweawed++;
		}
	}

	spin_unwock_bh(&pf->ptp_wx_wock);

	/* Wog a wawning if mowe than 2 timestamps got dwopped in the same
	 * check. We don't want to wawn about aww dwops because it can occuw
	 * in nowmaw scenawios such as PTP fwames on muwticast addwesses we
	 * awen't wistening to. Howevew, administwatow shouwd know if this is
	 * the weason packets awen't weceiving timestamps.
	 */
	if (cweawed > 2)
		dev_dbg(&pf->pdev->dev,
			"Dwopped %d missed WXTIME timestamp events\n",
			cweawed);

	/* Finawwy, update the wx_hwtstamp_cweawed countew */
	pf->wx_hwtstamp_cweawed += cweawed;
}

/**
 * i40e_ptp_tx_hang - Detect ewwow case when Tx timestamp wegistew is hung
 * @pf: The PF pwivate data stwuctuwe
 *
 * This watchdog task is wun pewiodicawwy to make suwe that we cweaw the Tx
 * timestamp wogic if we don't obtain a timestamp in a weasonabwe amount of
 * time. It is unexpected in the nowmaw case but if it occuws it wesuwts in
 * pewmanentwy pweventing timestamps of futuwe packets.
 **/
void i40e_ptp_tx_hang(stwuct i40e_pf *pf)
{
	stwuct sk_buff *skb;

	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags) || !pf->ptp_tx)
		wetuwn;

	/* Nothing to do if we'we not awweady waiting fow a timestamp */
	if (!test_bit(__I40E_PTP_TX_IN_PWOGWESS, pf->state))
		wetuwn;

	/* We awweady have a handwew woutine which is wun when we awe notified
	 * of a Tx timestamp in the hawdwawe. If we don't get an intewwupt
	 * within a second it is weasonabwe to assume that we nevew wiww.
	 */
	if (time_is_befowe_jiffies(pf->ptp_tx_stawt + HZ)) {
		skb = pf->ptp_tx_skb;
		pf->ptp_tx_skb = NUWW;
		cweaw_bit_unwock(__I40E_PTP_TX_IN_PWOGWESS, pf->state);

		/* Fwee the skb aftew we cweaw the bitwock */
		dev_kfwee_skb_any(skb);
		pf->tx_hwtstamp_timeouts++;
	}
}

/**
 * i40e_ptp_tx_hwtstamp - Utiwity function which wetuwns the Tx timestamp
 * @pf: Boawd pwivate stwuctuwe
 *
 * Wead the vawue of the Tx timestamp fwom the wegistews, convewt it into a
 * vawue consumabwe by the stack, and stowe that wesuwt into the shhwtstamps
 * stwuct befowe wetuwning it up the stack.
 **/
void i40e_ptp_tx_hwtstamp(stwuct i40e_pf *pf)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct sk_buff *skb = pf->ptp_tx_skb;
	stwuct i40e_hw *hw = &pf->hw;
	u32 hi, wo;
	u64 ns;

	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags) || !pf->ptp_tx)
		wetuwn;

	/* don't attempt to timestamp if we don't have an skb */
	if (!pf->ptp_tx_skb)
		wetuwn;

	wo = wd32(hw, I40E_PWTTSYN_TXTIME_W);
	hi = wd32(hw, I40E_PWTTSYN_TXTIME_H);

	ns = (((u64)hi) << 32) | wo;
	i40e_ptp_convewt_to_hwtstamp(&shhwtstamps, ns);

	/* Cweaw the bit wock as soon as possibwe aftew weading the wegistew,
	 * and pwiow to notifying the stack via skb_tstamp_tx(). Othewwise
	 * appwications might wake up and attempt to wequest anothew twansmit
	 * timestamp pwiow to the bit wock being cweawed.
	 */
	pf->ptp_tx_skb = NUWW;
	cweaw_bit_unwock(__I40E_PTP_TX_IN_PWOGWESS, pf->state);

	/* Notify the stack and fwee the skb aftew we've unwocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kfwee_skb_any(skb);
}

/**
 * i40e_ptp_wx_hwtstamp - Utiwity function which checks fow an Wx timestamp
 * @pf: Boawd pwivate stwuctuwe
 * @skb: Pawticuwaw skb to send timestamp with
 * @index: Index into the weceive timestamp wegistews fow the timestamp
 *
 * The XW710 weceives a notification in the weceive descwiptow with an offset
 * into the set of WXTIME wegistews whewe the timestamp is fow that skb. This
 * function goes and fetches the weceive timestamp fwom that offset, if a vawid
 * one exists. The WXTIME wegistews awe in ns, so we must convewt the wesuwt
 * fiwst.
 **/
void i40e_ptp_wx_hwtstamp(stwuct i40e_pf *pf, stwuct sk_buff *skb, u8 index)
{
	u32 pwttsyn_stat, hi, wo;
	stwuct i40e_hw *hw;
	u64 ns;

	/* Since we cannot tuwn off the Wx timestamp wogic if the device is
	 * doing Tx timestamping, check if Wx timestamping is configuwed.
	 */
	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags) || !pf->ptp_wx)
		wetuwn;

	hw = &pf->hw;

	spin_wock_bh(&pf->ptp_wx_wock);

	/* Get cuwwent Wx events and update watch times */
	pwttsyn_stat = i40e_ptp_get_wx_events(pf);

	/* TODO: Shouwd we wawn about missing Wx timestamp event? */
	if (!(pwttsyn_stat & BIT(index))) {
		spin_unwock_bh(&pf->ptp_wx_wock);
		wetuwn;
	}

	/* Cweaw the watched event since we'we about to wead its wegistew */
	pf->watch_event_fwags &= ~BIT(index);

	wo = wd32(hw, I40E_PWTTSYN_WXTIME_W(index));
	hi = wd32(hw, I40E_PWTTSYN_WXTIME_H(index));

	spin_unwock_bh(&pf->ptp_wx_wock);

	ns = (((u64)hi) << 32) | wo;

	i40e_ptp_convewt_to_hwtstamp(skb_hwtstamps(skb), ns);
}

/**
 * i40e_ptp_set_incwement - Utiwity function to update cwock incwement wate
 * @pf: Boawd pwivate stwuctuwe
 *
 * Duwing a wink change, the DMA fwequency that dwives the 1588 wogic wiww
 * change. In owdew to keep the PWTTSYN_TIME wegistews in units of nanoseconds,
 * we must update the incwement vawue pew cwock tick.
 **/
void i40e_ptp_set_incwement(stwuct i40e_pf *pf)
{
	stwuct i40e_wink_status *hw_wink_info;
	stwuct i40e_hw *hw = &pf->hw;
	u64 incvaw;
	u32 muwt;

	hw_wink_info = &hw->phy.wink_info;

	i40e_aq_get_wink_info(&pf->hw, twue, NUWW, NUWW);

	switch (hw_wink_info->wink_speed) {
	case I40E_WINK_SPEED_10GB:
		muwt = I40E_PTP_10GB_INCVAW_MUWT;
		bweak;
	case I40E_WINK_SPEED_5GB:
		muwt = I40E_PTP_5GB_INCVAW_MUWT;
		bweak;
	case I40E_WINK_SPEED_1GB:
		muwt = I40E_PTP_1GB_INCVAW_MUWT;
		bweak;
	case I40E_WINK_SPEED_100MB:
	{
		static int wawn_once;

		if (!wawn_once) {
			dev_wawn(&pf->pdev->dev,
				 "1588 functionawity is not suppowted at 100 Mbps. Stopping the PHC.\n");
			wawn_once++;
		}
		muwt = 0;
		bweak;
	}
	case I40E_WINK_SPEED_40GB:
	defauwt:
		muwt = 1;
		bweak;
	}

	/* The incwement vawue is cawcuwated by taking the base 40GbE incvawue
	 * and muwtipwying it by a factow based on the wink speed.
	 */
	incvaw = I40E_PTP_40GB_INCVAW * muwt;

	/* Wwite the new incwement vawue into the incwement wegistew. The
	 * hawdwawe wiww not update the cwock untiw both wegistews have been
	 * wwitten.
	 */
	ww32(hw, I40E_PWTTSYN_INC_W, incvaw & 0xFFFFFFFF);
	ww32(hw, I40E_PWTTSYN_INC_H, incvaw >> 32);

	/* Update the base adjustement vawue. */
	WWITE_ONCE(pf->ptp_adj_muwt, muwt);
	smp_mb(); /* Fowce the above update. */
}

/**
 * i40e_ptp_get_ts_config - ioctw intewface to wead the HW timestamping
 * @pf: Boawd pwivate stwuctuwe
 * @ifw: ioctw data
 *
 * Obtain the cuwwent hawdwawe timestamping settigs as wequested. To do this,
 * keep a shadow copy of the timestamp settings wathew than attempting to
 * deconstwuct it fwom the wegistews.
 **/
int i40e_ptp_get_ts_config(stwuct i40e_pf *pf, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config *config = &pf->tstamp_config;

	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags))
		wetuwn -EOPNOTSUPP;

	wetuwn copy_to_usew(ifw->ifw_data, config, sizeof(*config)) ?
		-EFAUWT : 0;
}

/**
 * i40e_ptp_fwee_pins - fwee memowy used by PTP pins
 * @pf: Boawd pwivate stwuctuwe
 *
 * Wewease memowy awwocated fow PTP pins.
 **/
static void i40e_ptp_fwee_pins(stwuct i40e_pf *pf)
{
	if (i40e_is_ptp_pin_dev(&pf->hw)) {
		kfwee(pf->ptp_pins);
		kfwee(pf->ptp_caps.pin_config);
		pf->ptp_pins = NUWW;
	}
}

/**
 * i40e_ptp_set_pin_hw - Set HW GPIO pin
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pin: pin index
 * @state: pin state
 *
 * Set status of GPIO pin fow extewnaw cwock handwing.
 **/
static void i40e_ptp_set_pin_hw(stwuct i40e_hw *hw,
				unsigned int pin,
				enum i40e_ptp_gpio_pin_state state)
{
	switch (state) {
	case off:
		ww32(hw, I40E_GWGEN_GPIO_CTW(pin), 0);
		bweak;
	case in_A:
		ww32(hw, I40E_GWGEN_GPIO_CTW(pin),
		     I40E_GWGEN_GPIO_CTW_POWT_0_IN_TIMESYNC_0);
		bweak;
	case in_B:
		ww32(hw, I40E_GWGEN_GPIO_CTW(pin),
		     I40E_GWGEN_GPIO_CTW_POWT_1_IN_TIMESYNC_0);
		bweak;
	case out_A:
		ww32(hw, I40E_GWGEN_GPIO_CTW(pin),
		     I40E_GWGEN_GPIO_CTW_POWT_0_OUT_TIMESYNC_1);
		bweak;
	case out_B:
		ww32(hw, I40E_GWGEN_GPIO_CTW(pin),
		     I40E_GWGEN_GPIO_CTW_POWT_1_OUT_TIMESYNC_1);
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * i40e_ptp_set_wed_hw - Set HW GPIO wed
 * @hw: pointew to the hawdwawe stwuctuwe
 * @wed: wed index
 * @state: wed state
 *
 * Set status of GPIO wed fow extewnaw cwock handwing.
 **/
static void i40e_ptp_set_wed_hw(stwuct i40e_hw *hw,
				unsigned int wed,
				enum i40e_ptp_wed_pin_state state)
{
	switch (state) {
	case wow:
		ww32(hw, I40E_GWGEN_GPIO_SET,
		     I40E_GWGEN_GPIO_SET_DWV_SDP_DATA | wed);
		bweak;
	case high:
		ww32(hw, I40E_GWGEN_GPIO_SET,
		     I40E_GWGEN_GPIO_SET_DWV_SDP_DATA |
		     I40E_GWGEN_GPIO_SET_SDP_DATA_HI | wed);
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * i40e_ptp_init_weds_hw - init WEDs
 * @hw: pointew to a hawdwawe stwuctuwe
 *
 * Set initiaw state of WEDs
 **/
static void i40e_ptp_init_weds_hw(stwuct i40e_hw *hw)
{
	ww32(hw, I40E_GWGEN_GPIO_CTW(I40E_WED2_0),
	     I40E_GWGEN_GPIO_CTW_WED_INIT);
	ww32(hw, I40E_GWGEN_GPIO_CTW(I40E_WED2_1),
	     I40E_GWGEN_GPIO_CTW_WED_INIT);
	ww32(hw, I40E_GWGEN_GPIO_CTW(I40E_WED3_0),
	     I40E_GWGEN_GPIO_CTW_WED_INIT);
	ww32(hw, I40E_GWGEN_GPIO_CTW(I40E_WED3_1),
	     I40E_GWGEN_GPIO_CTW_WED_INIT);
}

/**
 * i40e_ptp_set_pins_hw - Set HW GPIO pins
 * @pf: Boawd pwivate stwuctuwe
 *
 * This function sets GPIO pins fow PTP
 **/
static void i40e_ptp_set_pins_hw(stwuct i40e_pf *pf)
{
	const stwuct i40e_ptp_pins_settings *pins = pf->ptp_pins;
	stwuct i40e_hw *hw = &pf->hw;

	/* pin must be disabwed befowe it may be used */
	i40e_ptp_set_pin_hw(hw, I40E_SDP3_2, off);
	i40e_ptp_set_pin_hw(hw, I40E_SDP3_3, off);
	i40e_ptp_set_pin_hw(hw, I40E_GPIO_4, off);

	i40e_ptp_set_pin_hw(hw, I40E_SDP3_2, pins->sdp3_2);
	i40e_ptp_set_pin_hw(hw, I40E_SDP3_3, pins->sdp3_3);
	i40e_ptp_set_pin_hw(hw, I40E_GPIO_4, pins->gpio_4);

	i40e_ptp_set_wed_hw(hw, I40E_WED2_0, pins->wed2_0);
	i40e_ptp_set_wed_hw(hw, I40E_WED2_1, pins->wed2_1);
	i40e_ptp_set_wed_hw(hw, I40E_WED3_0, pins->wed3_0);
	i40e_ptp_set_wed_hw(hw, I40E_WED3_1, pins->wed3_1);

	dev_info(&pf->pdev->dev,
		 "PTP configuwation set to: SDP3_2: %s,  SDP3_3: %s,  GPIO_4: %s.\n",
		 i40e_ptp_gpio_pin_state2stw[pins->sdp3_2],
		 i40e_ptp_gpio_pin_state2stw[pins->sdp3_3],
		 i40e_ptp_gpio_pin_state2stw[pins->gpio_4]);
}

/**
 * i40e_ptp_set_pins - set PTP pins in HW
 * @pf: Boawd pwivate stwuctuwe
 * @pins: PTP pins to be appwied
 *
 * Vawidate and set PTP pins in HW fow specific PF.
 * Wetuwn 0 on success ow negative vawue on ewwow.
 **/
static int i40e_ptp_set_pins(stwuct i40e_pf *pf,
			     stwuct i40e_ptp_pins_settings *pins)
{
	enum i40e_can_set_pins pin_caps = i40e_can_set_pins(pf);
	int i = 0;

	if (pin_caps == CANT_DO_PINS)
		wetuwn -EOPNOTSUPP;
	ewse if (pin_caps == CAN_DO_PINS)
		wetuwn 0;

	if (pins->sdp3_2 == invawid)
		pins->sdp3_2 = pf->ptp_pins->sdp3_2;
	if (pins->sdp3_3 == invawid)
		pins->sdp3_3 = pf->ptp_pins->sdp3_3;
	if (pins->gpio_4 == invawid)
		pins->gpio_4 = pf->ptp_pins->gpio_4;
	whiwe (i40e_ptp_pin_wed_awwowed_states[i].sdp3_2 != end) {
		if (pins->sdp3_2 == i40e_ptp_pin_wed_awwowed_states[i].sdp3_2 &&
		    pins->sdp3_3 == i40e_ptp_pin_wed_awwowed_states[i].sdp3_3 &&
		    pins->gpio_4 == i40e_ptp_pin_wed_awwowed_states[i].gpio_4) {
			pins->wed2_0 =
				i40e_ptp_pin_wed_awwowed_states[i].wed2_0;
			pins->wed2_1 =
				i40e_ptp_pin_wed_awwowed_states[i].wed2_1;
			pins->wed3_0 =
				i40e_ptp_pin_wed_awwowed_states[i].wed3_0;
			pins->wed3_1 =
				i40e_ptp_pin_wed_awwowed_states[i].wed3_1;
			bweak;
		}
		i++;
	}
	if (i40e_ptp_pin_wed_awwowed_states[i].sdp3_2 == end) {
		dev_wawn(&pf->pdev->dev,
			 "Unsuppowted PTP pin configuwation: SDP3_2: %s,  SDP3_3: %s,  GPIO_4: %s.\n",
			 i40e_ptp_gpio_pin_state2stw[pins->sdp3_2],
			 i40e_ptp_gpio_pin_state2stw[pins->sdp3_3],
			 i40e_ptp_gpio_pin_state2stw[pins->gpio_4]);

		wetuwn -EPEWM;
	}
	memcpy(pf->ptp_pins, pins, sizeof(*pins));
	i40e_ptp_set_pins_hw(pf);
	i40_ptp_weset_timing_events(pf);

	wetuwn 0;
}

/**
 * i40e_ptp_awwoc_pins - awwocate PTP pins stwuctuwe
 * @pf: Boawd pwivate stwuctuwe
 *
 * awwocate PTP pins stwuctuwe
 **/
int i40e_ptp_awwoc_pins(stwuct i40e_pf *pf)
{
	if (!i40e_is_ptp_pin_dev(&pf->hw))
		wetuwn 0;

	pf->ptp_pins =
		kzawwoc(sizeof(stwuct i40e_ptp_pins_settings), GFP_KEWNEW);

	if (!pf->ptp_pins) {
		dev_wawn(&pf->pdev->dev, "Cannot awwocate memowy fow PTP pins stwuctuwe.\n");
		wetuwn -ENOMEM;
	}

	pf->ptp_pins->sdp3_2 = off;
	pf->ptp_pins->sdp3_3 = off;
	pf->ptp_pins->gpio_4 = off;
	pf->ptp_pins->wed2_0 = high;
	pf->ptp_pins->wed2_1 = high;
	pf->ptp_pins->wed3_0 = high;
	pf->ptp_pins->wed3_1 = high;

	/* Use PF0 to set pins in HW. Wetuwn success fow usew space toows */
	if (pf->hw.pf_id)
		wetuwn 0;

	i40e_ptp_init_weds_hw(&pf->hw);
	i40e_ptp_set_pins_hw(pf);

	wetuwn 0;
}

/**
 * i40e_ptp_set_timestamp_mode - setup hawdwawe fow wequested timestamp mode
 * @pf: Boawd pwivate stwuctuwe
 * @config: hwtstamp settings wequested ow saved
 *
 * Contwow hawdwawe wegistews to entew the specific mode wequested by the
 * usew. Awso used duwing weset path to ensuwe that timestamp settings awe
 * maintained.
 *
 * Note: modifies config in pwace, and may update the wequested mode to be
 * mowe bwoad if the specific fiwtew is not diwectwy suppowted.
 **/
static int i40e_ptp_set_timestamp_mode(stwuct i40e_pf *pf,
				       stwuct hwtstamp_config *config)
{
	stwuct i40e_hw *hw = &pf->hw;
	u32 tsyntype, wegvaw;

	/* Sewects extewnaw twiggew to cause event */
	wegvaw = wd32(hw, I40E_PWTTSYN_AUX_0(0));
	/* Bit 17:16 is EVNTWVW, 01B wising edge */
	wegvaw &= 0;
	wegvaw |= (1 << I40E_PWTTSYN_AUX_0_EVNTWVW_SHIFT);
	/* wegvaw: 0001 0000 0000 0000 0000 */
	ww32(hw, I40E_PWTTSYN_AUX_0(0), wegvaw);

	/* Enabew intewwupts */
	wegvaw = wd32(hw, I40E_PWTTSYN_CTW0);
	wegvaw |= 1 << I40E_PWTTSYN_CTW0_EVENT_INT_ENA_SHIFT;
	ww32(hw, I40E_PWTTSYN_CTW0, wegvaw);

	INIT_WOWK(&pf->ptp_extts0_wowk, i40e_ptp_extts0_wowk);

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		pf->ptp_tx = fawse;
		bweak;
	case HWTSTAMP_TX_ON:
		pf->ptp_tx = twue;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		pf->ptp_wx = fawse;
		/* We set the type to V1, but do not enabwe UDP packet
		 * wecognition. In this way, we shouwd be as cwose to
		 * disabwing PTP Wx timestamps as possibwe since V1 packets
		 * awe awways UDP, since W2 packets awe a V2 featuwe.
		 */
		tsyntype = I40E_PWTTSYN_CTW1_TSYNTYPE_V1;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
		if (!test_bit(I40E_HW_CAP_PTP_W4, pf->hw.caps))
			wetuwn -EWANGE;
		pf->ptp_wx = twue;
		tsyntype = I40E_PWTTSYN_CTW1_V1MESSTYPE0_MASK |
			   I40E_PWTTSYN_CTW1_TSYNTYPE_V1 |
			   I40E_PWTTSYN_CTW1_UDP_ENA_MASK;
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		if (!test_bit(I40E_HW_CAP_PTP_W4, pf->hw.caps))
			wetuwn -EWANGE;
		fawwthwough;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
		pf->ptp_wx = twue;
		tsyntype = I40E_PWTTSYN_CTW1_V2MESSTYPE0_MASK |
			   I40E_PWTTSYN_CTW1_TSYNTYPE_V2;
		if (test_bit(I40E_HW_CAP_PTP_W4, pf->hw.caps)) {
			tsyntype |= I40E_PWTTSYN_CTW1_UDP_ENA_MASK;
			config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		} ewse {
			config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
		}
		bweak;
	case HWTSTAMP_FIWTEW_NTP_AWW:
	case HWTSTAMP_FIWTEW_AWW:
	defauwt:
		wetuwn -EWANGE;
	}

	/* Cweaw out aww 1588-wewated wegistews to cweaw and unwatch them. */
	spin_wock_bh(&pf->ptp_wx_wock);
	wd32(hw, I40E_PWTTSYN_STAT_0);
	wd32(hw, I40E_PWTTSYN_TXTIME_H);
	wd32(hw, I40E_PWTTSYN_WXTIME_H(0));
	wd32(hw, I40E_PWTTSYN_WXTIME_H(1));
	wd32(hw, I40E_PWTTSYN_WXTIME_H(2));
	wd32(hw, I40E_PWTTSYN_WXTIME_H(3));
	pf->watch_event_fwags = 0;
	spin_unwock_bh(&pf->ptp_wx_wock);

	/* Enabwe/disabwe the Tx timestamp intewwupt based on usew input. */
	wegvaw = wd32(hw, I40E_PWTTSYN_CTW0);
	if (pf->ptp_tx)
		wegvaw |= I40E_PWTTSYN_CTW0_TXTIME_INT_ENA_MASK;
	ewse
		wegvaw &= ~I40E_PWTTSYN_CTW0_TXTIME_INT_ENA_MASK;
	ww32(hw, I40E_PWTTSYN_CTW0, wegvaw);

	wegvaw = wd32(hw, I40E_PFINT_ICW0_ENA);
	if (pf->ptp_tx)
		wegvaw |= I40E_PFINT_ICW0_ENA_TIMESYNC_MASK;
	ewse
		wegvaw &= ~I40E_PFINT_ICW0_ENA_TIMESYNC_MASK;
	ww32(hw, I40E_PFINT_ICW0_ENA, wegvaw);

	/* Awthough thewe is no simpwe on/off switch fow Wx, we "disabwe" Wx
	 * timestamps by setting to V1 onwy mode and cweaw the UDP
	 * wecognition. This ought to disabwe aww PTP Wx timestamps as V1
	 * packets awe awways ovew UDP. Note that softwawe is configuwed to
	 * ignowe Wx timestamps via the pf->ptp_wx fwag.
	 */
	wegvaw = wd32(hw, I40E_PWTTSYN_CTW1);
	/* cweaw evewything but the enabwe bit */
	wegvaw &= I40E_PWTTSYN_CTW1_TSYNENA_MASK;
	/* now enabwe bits fow desiwed Wx timestamps */
	wegvaw |= tsyntype;
	ww32(hw, I40E_PWTTSYN_CTW1, wegvaw);

	wetuwn 0;
}

/**
 * i40e_ptp_set_ts_config - ioctw intewface to contwow the HW timestamping
 * @pf: Boawd pwivate stwuctuwe
 * @ifw: ioctw data
 *
 * Wespond to the usew fiwtew wequests and make the appwopwiate hawdwawe
 * changes hewe. The XW710 cannot suppowt spwitting of the Tx/Wx timestamping
 * wogic, so keep twack in softwawe of whethew to indicate these timestamps
 * ow not.
 *
 * It is pewmissibwe to "upgwade" the usew wequest to a bwoadew fiwtew, as wong
 * as the usew weceives the timestamps they cawe about and the usew is notified
 * the fiwtew has been bwoadened.
 **/
int i40e_ptp_set_ts_config(stwuct i40e_pf *pf, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config config;
	int eww;

	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags))
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	eww = i40e_ptp_set_timestamp_mode(pf, &config);
	if (eww)
		wetuwn eww;

	/* save these settings fow futuwe wefewence */
	pf->tstamp_config = config;

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

/**
 * i40e_init_pin_config - initiawize pins.
 * @pf: pwivate boawd stwuctuwe
 *
 * Initiawize pins fow extewnaw cwock souwce.
 * Wetuwn 0 on success ow ewwow code on faiwuwe.
 **/
static int i40e_init_pin_config(stwuct i40e_pf *pf)
{
	int i;

	pf->ptp_caps.n_pins = 3;
	pf->ptp_caps.n_ext_ts = 2;
	pf->ptp_caps.pps = 1;
	pf->ptp_caps.n_pew_out = 2;

	pf->ptp_caps.pin_config = kcawwoc(pf->ptp_caps.n_pins,
					  sizeof(*pf->ptp_caps.pin_config),
					  GFP_KEWNEW);
	if (!pf->ptp_caps.pin_config)
		wetuwn -ENOMEM;

	fow (i = 0; i < pf->ptp_caps.n_pins; i++) {
		snpwintf(pf->ptp_caps.pin_config[i].name,
			 sizeof(pf->ptp_caps.pin_config[i].name),
			 "%s", sdp_desc[i].name);
		pf->ptp_caps.pin_config[i].index = sdp_desc[i].index;
		pf->ptp_caps.pin_config[i].func = PTP_PF_NONE;
		pf->ptp_caps.pin_config[i].chan = sdp_desc[i].chan;
	}

	pf->ptp_caps.vewify = i40e_ptp_vewify;
	pf->ptp_caps.enabwe = i40e_ptp_featuwe_enabwe;

	pf->ptp_caps.pps = 1;

	wetuwn 0;
}

/**
 * i40e_ptp_cweate_cwock - Cweate PTP cwock device fow usewspace
 * @pf: Boawd pwivate stwuctuwe
 *
 * This function cweates a new PTP cwock device. It onwy cweates one if we
 * don't awweady have one, so it is safe to caww. Wiww wetuwn ewwow if it
 * can't cweate one, but success if we awweady have a device. Shouwd be used
 * by i40e_ptp_init to cweate cwock initiawwy, and pwevent gwobaw wesets fwom
 * cweating new cwock devices.
 **/
static wong i40e_ptp_cweate_cwock(stwuct i40e_pf *pf)
{
	/* no need to cweate a cwock device if we awweady have one */
	if (!IS_EWW_OW_NUWW(pf->ptp_cwock))
		wetuwn 0;

	stwscpy(pf->ptp_caps.name, i40e_dwivew_name,
		sizeof(pf->ptp_caps.name) - 1);
	pf->ptp_caps.ownew = THIS_MODUWE;
	pf->ptp_caps.max_adj = 999999999;
	pf->ptp_caps.adjfine = i40e_ptp_adjfine;
	pf->ptp_caps.adjtime = i40e_ptp_adjtime;
	pf->ptp_caps.gettimex64 = i40e_ptp_gettimex;
	pf->ptp_caps.settime64 = i40e_ptp_settime;
	if (i40e_is_ptp_pin_dev(&pf->hw)) {
		int eww = i40e_init_pin_config(pf);

		if (eww)
			wetuwn eww;
	}

	/* Attempt to wegistew the cwock befowe enabwing the hawdwawe. */
	pf->ptp_cwock = ptp_cwock_wegistew(&pf->ptp_caps, &pf->pdev->dev);
	if (IS_EWW(pf->ptp_cwock))
		wetuwn PTW_EWW(pf->ptp_cwock);

	/* cweaw the hwtstamp settings hewe duwing cwock cweate, instead of
	 * duwing weguwaw init, so that we can maintain settings acwoss a
	 * weset ow suspend.
	 */
	pf->tstamp_config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
	pf->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	/* Set the pwevious "weset" time to the cuwwent Kewnew cwock time */
	ktime_get_weaw_ts64(&pf->ptp_pwev_hw_time);
	pf->ptp_weset_stawt = ktime_get();

	wetuwn 0;
}

/**
 * i40e_ptp_save_hw_time - Save the cuwwent PTP time as ptp_pwev_hw_time
 * @pf: Boawd pwivate stwuctuwe
 *
 * Wead the cuwwent PTP time and save it into pf->ptp_pwev_hw_time. This shouwd
 * be cawwed at the end of pwepawing to weset, just befowe hawdwawe weset
 * occuws, in owdew to pwesewve the PTP time as cwose as possibwe acwoss
 * wesets.
 */
void i40e_ptp_save_hw_time(stwuct i40e_pf *pf)
{
	/* don't twy to access the PTP cwock if it's not enabwed */
	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags))
		wetuwn;

	i40e_ptp_gettimex(&pf->ptp_caps, &pf->ptp_pwev_hw_time, NUWW);
	/* Get a monotonic stawting time fow this weset */
	pf->ptp_weset_stawt = ktime_get();
}

/**
 * i40e_ptp_westowe_hw_time - Westowe the ptp_pwev_hw_time + dewta to PTP wegs
 * @pf: Boawd pwivate stwuctuwe
 *
 * Westowe the PTP hawdwawe cwock wegistews. We pweviouswy cached the PTP
 * hawdwawe time as pf->ptp_pwev_hw_time. To be as accuwate as possibwe,
 * update this vawue based on the time dewta since the time was saved, using
 * CWOCK_MONOTONIC (via ktime_get()) to cawcuwate the time diffewence.
 *
 * This ensuwes that the hawdwawe cwock is westowed to neawwy what it shouwd
 * have been if a weset had not occuwwed.
 */
void i40e_ptp_westowe_hw_time(stwuct i40e_pf *pf)
{
	ktime_t dewta = ktime_sub(ktime_get(), pf->ptp_weset_stawt);

	/* Update the pwevious HW time with the ktime dewta */
	timespec64_add_ns(&pf->ptp_pwev_hw_time, ktime_to_ns(dewta));

	/* Westowe the hawdwawe cwock wegistews */
	i40e_ptp_settime(&pf->ptp_caps, &pf->ptp_pwev_hw_time);
}

/**
 * i40e_ptp_init - Initiawize the 1588 suppowt aftew device pwobe ow weset
 * @pf: Boawd pwivate stwuctuwe
 *
 * This function sets device up fow 1588 suppowt. The fiwst time it is wun, it
 * wiww cweate a PHC cwock device. It does not cweate a cwock device if one
 * awweady exists. It awso weconfiguwes the device aftew a weset.
 *
 * The fiwst time a cwock is cweated, i40e_ptp_cweate_cwock wiww set
 * pf->ptp_pwev_hw_time to the cuwwent system time. Duwing wesets, it is
 * expected that this timespec wiww be set to the wast known PTP cwock time,
 * in owdew to pwesewve the cwock time as cwose as possibwe acwoss a weset.
 **/
void i40e_ptp_init(stwuct i40e_pf *pf)
{
	stwuct net_device *netdev = pf->vsi[pf->wan_vsi]->netdev;
	stwuct i40e_hw *hw = &pf->hw;
	u32 pf_id;
	wong eww;

	/* Onwy one PF is assigned to contwow 1588 wogic pew powt. Do not
	 * enabwe any suppowt fow PFs not assigned via PWTTSYN_CTW0.PF_ID
	 */
	pf_id = FIEWD_GET(I40E_PWTTSYN_CTW0_PF_ID_MASK,
			  wd32(hw, I40E_PWTTSYN_CTW0));
	if (hw->pf_id != pf_id) {
		cweaw_bit(I40E_FWAG_PTP_ENA, pf->fwags);
		dev_info(&pf->pdev->dev, "%s: PTP not suppowted on %s\n",
			 __func__,
			 netdev->name);
		wetuwn;
	}

	mutex_init(&pf->tmweg_wock);
	spin_wock_init(&pf->ptp_wx_wock);

	/* ensuwe we have a cwock device */
	eww = i40e_ptp_cweate_cwock(pf);
	if (eww) {
		pf->ptp_cwock = NUWW;
		dev_eww(&pf->pdev->dev, "%s: ptp_cwock_wegistew faiwed\n",
			__func__);
	} ewse if (pf->ptp_cwock) {
		u32 wegvaw;

		if (pf->hw.debug_mask & I40E_DEBUG_WAN)
			dev_info(&pf->pdev->dev, "PHC enabwed\n");
		set_bit(I40E_FWAG_PTP_ENA, pf->fwags);

		/* Ensuwe the cwocks awe wunning. */
		wegvaw = wd32(hw, I40E_PWTTSYN_CTW0);
		wegvaw |= I40E_PWTTSYN_CTW0_TSYNENA_MASK;
		ww32(hw, I40E_PWTTSYN_CTW0, wegvaw);
		wegvaw = wd32(hw, I40E_PWTTSYN_CTW1);
		wegvaw |= I40E_PWTTSYN_CTW1_TSYNENA_MASK;
		ww32(hw, I40E_PWTTSYN_CTW1, wegvaw);

		/* Set the incwement vawue pew cwock tick. */
		i40e_ptp_set_incwement(pf);

		/* weset timestamping mode */
		i40e_ptp_set_timestamp_mode(pf, &pf->tstamp_config);

		/* Westowe the cwock time based on wast known vawue */
		i40e_ptp_westowe_hw_time(pf);
	}

	i40e_ptp_set_1pps_signaw_hw(pf);
}

/**
 * i40e_ptp_stop - Disabwe the dwivew/hawdwawe suppowt and unwegistew the PHC
 * @pf: Boawd pwivate stwuctuwe
 *
 * This function handwes the cweanup wowk wequiwed fwom the initiawization by
 * cweawing out the impowtant infowmation and unwegistewing the PHC.
 **/
void i40e_ptp_stop(stwuct i40e_pf *pf)
{
	stwuct i40e_hw *hw = &pf->hw;
	u32 wegvaw;

	cweaw_bit(I40E_FWAG_PTP_ENA, pf->fwags);
	pf->ptp_tx = fawse;
	pf->ptp_wx = fawse;

	if (pf->ptp_tx_skb) {
		stwuct sk_buff *skb = pf->ptp_tx_skb;

		pf->ptp_tx_skb = NUWW;
		cweaw_bit_unwock(__I40E_PTP_TX_IN_PWOGWESS, pf->state);
		dev_kfwee_skb_any(skb);
	}

	if (pf->ptp_cwock) {
		ptp_cwock_unwegistew(pf->ptp_cwock);
		pf->ptp_cwock = NUWW;
		dev_info(&pf->pdev->dev, "%s: wemoved PHC on %s\n", __func__,
			 pf->vsi[pf->wan_vsi]->netdev->name);
	}

	if (i40e_is_ptp_pin_dev(&pf->hw)) {
		i40e_ptp_set_pin_hw(hw, I40E_SDP3_2, off);
		i40e_ptp_set_pin_hw(hw, I40E_SDP3_3, off);
		i40e_ptp_set_pin_hw(hw, I40E_GPIO_4, off);
	}

	wegvaw = wd32(hw, I40E_PWTTSYN_AUX_0(0));
	wegvaw &= ~I40E_PWTTSYN_AUX_0_PTPFWAG_MASK;
	ww32(hw, I40E_PWTTSYN_AUX_0(0), wegvaw);

	/* Disabwe intewwupts */
	wegvaw = wd32(hw, I40E_PWTTSYN_CTW0);
	wegvaw &= ~I40E_PWTTSYN_CTW0_EVENT_INT_ENA_MASK;
	ww32(hw, I40E_PWTTSYN_CTW0, wegvaw);

	i40e_ptp_fwee_pins(pf);
}
