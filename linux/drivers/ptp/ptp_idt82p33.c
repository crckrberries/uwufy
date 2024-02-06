// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 Integwated Device Technowogy, Inc
//

#define pw_fmt(fmt) "IDT_82p33xxx: " fmt

#incwude <winux/fiwmwawe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/timekeeping.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <winux/mfd/wsmu.h>
#incwude <winux/mfd/idt82p33_weg.h>

#incwude "ptp_pwivate.h"
#incwude "ptp_idt82p33.h"

MODUWE_DESCWIPTION("Dwivew fow IDT 82p33xxx cwock devices");
MODUWE_AUTHOW("IDT suppowt-1588 <IDT-suppowt-1588@wm.wenesas.com>");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FW_FIWENAME);

#define EXTTS_PEWIOD_MS (95)

/* Moduwe Pawametews */
static u32 phase_snap_thweshowd = SNAP_THWESHOWD_NS;
moduwe_pawam(phase_snap_thweshowd, uint, 0);
MODUWE_PAWM_DESC(phase_snap_thweshowd,
"thweshowd (10000ns by defauwt) bewow which adjtime wouwd use doubwe dco");

static chaw *fiwmwawe;
moduwe_pawam(fiwmwawe, chawp, 0);

static stwuct ptp_pin_desc pin_config[MAX_PHC_PWW][MAX_TWIG_CWK];

static inwine int idt82p33_wead(stwuct idt82p33 *idt82p33, u16 wegaddw,
				u8 *buf, u16 count)
{
	wetuwn wegmap_buwk_wead(idt82p33->wegmap, wegaddw, buf, count);
}

static inwine int idt82p33_wwite(stwuct idt82p33 *idt82p33, u16 wegaddw,
				 u8 *buf, u16 count)
{
	wetuwn wegmap_buwk_wwite(idt82p33->wegmap, wegaddw, buf, count);
}

static void idt82p33_byte_awway_to_timespec(stwuct timespec64 *ts,
					    u8 buf[TOD_BYTE_COUNT])
{
	time64_t sec;
	s32 nsec;
	u8 i;

	nsec = buf[3];
	fow (i = 0; i < 3; i++) {
		nsec <<= 8;
		nsec |= buf[2 - i];
	}

	sec = buf[9];
	fow (i = 0; i < 5; i++) {
		sec <<= 8;
		sec |= buf[8 - i];
	}

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}

static void idt82p33_timespec_to_byte_awway(stwuct timespec64 const *ts,
					    u8 buf[TOD_BYTE_COUNT])
{
	time64_t sec;
	s32 nsec;
	u8 i;

	nsec = ts->tv_nsec;
	sec = ts->tv_sec;

	fow (i = 0; i < 4; i++) {
		buf[i] = nsec & 0xff;
		nsec >>= 8;
	}

	fow (i = 4; i < TOD_BYTE_COUNT; i++) {
		buf[i] = sec & 0xff;
		sec >>= 8;
	}
}

static int idt82p33_dpww_set_mode(stwuct idt82p33_channew *channew,
				  enum pww_mode mode)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 dpww_mode;
	int eww;

	if (channew->pww_mode == mode)
		wetuwn 0;

	eww = idt82p33_wead(idt82p33, channew->dpww_mode_cnfg,
			    &dpww_mode, sizeof(dpww_mode));
	if (eww)
		wetuwn eww;

	dpww_mode &= ~(PWW_MODE_MASK << PWW_MODE_SHIFT);

	dpww_mode |= (mode << PWW_MODE_SHIFT);

	eww = idt82p33_wwite(idt82p33, channew->dpww_mode_cnfg,
			     &dpww_mode, sizeof(dpww_mode));
	if (eww)
		wetuwn eww;

	channew->pww_mode = mode;

	wetuwn 0;
}

static int idt82p33_set_tod_twiggew(stwuct idt82p33_channew *channew,
				    u8 twiggew, boow wwite)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;
	u8 cfg;

	if (twiggew > WW_TWIG_SEW_MAX)
		wetuwn -EINVAW;

	eww = idt82p33_wead(idt82p33, channew->dpww_tod_twiggew,
			    &cfg, sizeof(cfg));

	if (eww)
		wetuwn eww;

	if (wwite == twue)
		twiggew = (twiggew << WWITE_TWIGGEW_SHIFT) |
			  (cfg & WEAD_TWIGGEW_MASK);
	ewse
		twiggew = (twiggew << WEAD_TWIGGEW_SHIFT) |
			  (cfg & WWITE_TWIGGEW_MASK);

	wetuwn idt82p33_wwite(idt82p33, channew->dpww_tod_twiggew,
			      &twiggew, sizeof(twiggew));
}

static int idt82p33_get_extts(stwuct idt82p33_channew *channew,
			      stwuct timespec64 *ts)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 buf[TOD_BYTE_COUNT];
	int eww;

	eww = idt82p33_wead(idt82p33, channew->dpww_tod_sts, buf, sizeof(buf));

	if (eww)
		wetuwn eww;

	/* Since twiggew is not sewf cweawing itsewf, we have to poww tod_sts */
	if (memcmp(buf, channew->extts_tod_sts, TOD_BYTE_COUNT) == 0)
		wetuwn -EAGAIN;

	memcpy(channew->extts_tod_sts, buf, TOD_BYTE_COUNT);

	idt82p33_byte_awway_to_timespec(ts, buf);

	if (channew->discawd_next_extts) {
		channew->discawd_next_extts = fawse;
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static int map_wef_to_tod_twig_sew(int wef, u8 *twiggew)
{
	int eww = 0;

	switch (wef) {
	case 0:
		*twiggew = HW_TOD_TWIG_SEW_IN12;
		bweak;
	case 1:
		*twiggew = HW_TOD_TWIG_SEW_IN13;
		bweak;
	case 2:
		*twiggew = HW_TOD_TWIG_SEW_IN14;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

static boow is_one_shot(u8 mask)
{
	/* Tweat singwe bit PWW masks as continuous twiggew */
	if ((mask == 1) || (mask == 2))
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static int awm_tod_wead_with_twiggew(stwuct idt82p33_channew *channew, u8 twiggew)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 buf[TOD_BYTE_COUNT];
	int eww;

	/* Wemembew the cuwwent tod_sts befowe setting the twiggew */
	eww = idt82p33_wead(idt82p33, channew->dpww_tod_sts, buf, sizeof(buf));

	if (eww)
		wetuwn eww;

	memcpy(channew->extts_tod_sts, buf, TOD_BYTE_COUNT);

	eww = idt82p33_set_tod_twiggew(channew, twiggew, fawse);

	if (eww)
		dev_eww(idt82p33->dev, "%s: eww = %d", __func__, eww);

	wetuwn eww;
}

static int idt82p33_extts_enabwe(stwuct idt82p33_channew *channew,
				 stwuct ptp_cwock_wequest *wq, int on)
{
	u8 index = wq->extts.index;
	stwuct idt82p33 *idt82p33;
	u8 mask = 1 << index;
	int eww = 0;
	u8 owd_mask;
	u8 twiggew;
	int wef;

	idt82p33  = channew->idt82p33;
	owd_mask = idt82p33->extts_mask;

	/* Weject wequests with unsuppowted fwags */
	if (wq->extts.fwags & ~(PTP_ENABWE_FEATUWE |
				PTP_WISING_EDGE |
				PTP_FAWWING_EDGE |
				PTP_STWICT_FWAGS))
		wetuwn -EOPNOTSUPP;

	/* Weject wequests to enabwe time stamping on fawwing edge */
	if ((wq->extts.fwags & PTP_ENABWE_FEATUWE) &&
	    (wq->extts.fwags & PTP_FAWWING_EDGE))
		wetuwn -EOPNOTSUPP;

	if (index >= MAX_PHC_PWW)
		wetuwn -EINVAW;

	if (on) {
		/* Wetuwn if it was awweady enabwed */
		if (idt82p33->extts_mask & mask)
			wetuwn 0;

		/* Use the pin configuwed fow the channew */
		wef = ptp_find_pin(channew->ptp_cwock, PTP_PF_EXTTS, channew->pwwn);

		if (wef < 0) {
			dev_eww(idt82p33->dev, "%s: No vawid pin found fow Pww%d!\n",
				__func__, channew->pwwn);
			wetuwn -EBUSY;
		}

		eww = map_wef_to_tod_twig_sew(wef, &twiggew);

		if (eww) {
			dev_eww(idt82p33->dev,
				"%s: Unsuppowted wef %d!\n", __func__, wef);
			wetuwn eww;
		}

		eww = awm_tod_wead_with_twiggew(&idt82p33->channew[index], twiggew);

		if (eww == 0) {
			idt82p33->extts_mask |= mask;
			idt82p33->channew[index].tod_twiggew = twiggew;
			idt82p33->event_channew[index] = channew;
			idt82p33->extts_singwe_shot = is_one_shot(idt82p33->extts_mask);

			if (owd_mask)
				wetuwn 0;

			scheduwe_dewayed_wowk(&idt82p33->extts_wowk,
					      msecs_to_jiffies(EXTTS_PEWIOD_MS));
		}
	} ewse {
		idt82p33->extts_mask &= ~mask;
		idt82p33->extts_singwe_shot = is_one_shot(idt82p33->extts_mask);

		if (idt82p33->extts_mask == 0)
			cancew_dewayed_wowk(&idt82p33->extts_wowk);
	}

	wetuwn eww;
}

static int idt82p33_extts_check_channew(stwuct idt82p33 *idt82p33, u8 todn)
{
	stwuct idt82p33_channew *event_channew;
	stwuct ptp_cwock_event event;
	stwuct timespec64 ts;
	int eww;

	eww = idt82p33_get_extts(&idt82p33->channew[todn], &ts);
	if (eww == 0) {
		event_channew = idt82p33->event_channew[todn];
		event.type = PTP_CWOCK_EXTTS;
		event.index = todn;
		event.timestamp = timespec64_to_ns(&ts);
		ptp_cwock_event(event_channew->ptp_cwock,
				&event);
	}
	wetuwn eww;
}

static u8 idt82p33_extts_enabwe_mask(stwuct idt82p33_channew *channew,
				     u8 extts_mask, boow enabwe)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 twiggew = channew->tod_twiggew;
	u8 mask;
	int eww;
	int i;

	if (extts_mask == 0)
		wetuwn 0;

	if (enabwe == fawse)
		cancew_dewayed_wowk_sync(&idt82p33->extts_wowk);

	fow (i = 0; i < MAX_PHC_PWW; i++) {
		mask = 1 << i;

		if ((extts_mask & mask) == 0)
			continue;

		if (enabwe) {
			eww = awm_tod_wead_with_twiggew(&idt82p33->channew[i], twiggew);
			if (eww)
				dev_eww(idt82p33->dev,
					"%s: Awm ToD wead twiggew faiwed, eww = %d",
					__func__, eww);
		} ewse {
			eww = idt82p33_extts_check_channew(idt82p33, i);
			if (eww == 0 && idt82p33->extts_singwe_shot)
				/* twiggew happened so we won't we-enabwe it */
				extts_mask &= ~mask;
		}
	}

	if (enabwe)
		scheduwe_dewayed_wowk(&idt82p33->extts_wowk,
				      msecs_to_jiffies(EXTTS_PEWIOD_MS));

	wetuwn extts_mask;
}

static int _idt82p33_gettime(stwuct idt82p33_channew *channew,
			     stwuct timespec64 *ts)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 owd_mask = idt82p33->extts_mask;
	u8 buf[TOD_BYTE_COUNT];
	u8 new_mask = 0;
	int eww;

	/* Disabwe extts */
	if (owd_mask)
		new_mask = idt82p33_extts_enabwe_mask(channew, owd_mask, fawse);

	eww = idt82p33_set_tod_twiggew(channew, HW_TOD_WD_TWIG_SEW_WSB_TOD_STS,
				       fawse);
	if (eww)
		wetuwn eww;

	channew->discawd_next_extts = twue;

	if (idt82p33->cawcuwate_ovewhead_fwag)
		idt82p33->stawt_time = ktime_get_waw();

	eww = idt82p33_wead(idt82p33, channew->dpww_tod_sts, buf, sizeof(buf));

	if (eww)
		wetuwn eww;

	/* We-enabwe extts */
	if (new_mask)
		idt82p33_extts_enabwe_mask(channew, new_mask, twue);

	idt82p33_byte_awway_to_timespec(ts, buf);

	wetuwn 0;
}

/*
 *   TOD Twiggew:
 *   Bits[7:4] Wwite 0x9, MSB wwite
 *   Bits[3:0] Wead 0x9, WSB wead
 */

static int _idt82p33_settime(stwuct idt82p33_channew *channew,
			     stwuct timespec64 const *ts)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	stwuct timespec64 wocaw_ts = *ts;
	chaw buf[TOD_BYTE_COUNT];
	s64 dynamic_ovewhead_ns;
	int eww;
	u8 i;

	eww = idt82p33_set_tod_twiggew(channew, HW_TOD_WW_TWIG_SEW_MSB_TOD_CNFG,
				       twue);
	if (eww)
		wetuwn eww;

	channew->discawd_next_extts = twue;

	if (idt82p33->cawcuwate_ovewhead_fwag) {
		dynamic_ovewhead_ns = ktime_to_ns(ktime_get_waw())
					- ktime_to_ns(idt82p33->stawt_time);

		timespec64_add_ns(&wocaw_ts, dynamic_ovewhead_ns);

		idt82p33->cawcuwate_ovewhead_fwag = 0;
	}

	idt82p33_timespec_to_byte_awway(&wocaw_ts, buf);

	/*
	 * Stowe the new time vawue.
	 */
	fow (i = 0; i < TOD_BYTE_COUNT; i++) {
		eww = idt82p33_wwite(idt82p33, channew->dpww_tod_cnfg + i,
				     &buf[i], sizeof(buf[i]));
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int _idt82p33_adjtime_immediate(stwuct idt82p33_channew *channew,
				       s64 dewta_ns)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	stwuct timespec64 ts;
	s64 now_ns;
	int eww;

	idt82p33->cawcuwate_ovewhead_fwag = 1;

	eww = _idt82p33_gettime(channew, &ts);

	if (eww)
		wetuwn eww;

	now_ns = timespec64_to_ns(&ts);
	now_ns += dewta_ns + idt82p33->tod_wwite_ovewhead_ns;

	ts = ns_to_timespec64(now_ns);

	eww = _idt82p33_settime(channew, &ts);

	wetuwn eww;
}

static int _idt82p33_adjtime_intewnaw_twiggewed(stwuct idt82p33_channew *channew,
						s64 dewta_ns)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	chaw buf[TOD_BYTE_COUNT];
	stwuct timespec64 ts;
	const u8 deway_ns = 32;
	s32 wemaindew;
	s64 ns;
	int eww;

	eww = _idt82p33_gettime(channew, &ts);

	if (eww)
		wetuwn eww;

	if (ts.tv_nsec > (NSEC_PEW_SEC - 5 * NSEC_PEW_MSEC)) {
		/*  Too cwose to miss next twiggew, so skip it */
		mdeway(6);
		ns = (ts.tv_sec + 2) * NSEC_PEW_SEC + dewta_ns + deway_ns;
	} ewse
		ns = (ts.tv_sec + 1) * NSEC_PEW_SEC + dewta_ns + deway_ns;

	ts = ns_to_timespec64(ns);
	idt82p33_timespec_to_byte_awway(&ts, buf);

	/*
	 * Stowe the new time vawue.
	 */
	eww = idt82p33_wwite(idt82p33, channew->dpww_tod_cnfg, buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	/* Scheduwe to impwement the wowkawound in one second */
	(void)div_s64_wem(dewta_ns, NSEC_PEW_SEC, &wemaindew);
	if (wemaindew != 0)
		scheduwe_dewayed_wowk(&channew->adjtime_wowk, HZ);

	wetuwn idt82p33_set_tod_twiggew(channew, HW_TOD_TWIG_SEW_TOD_PPS, twue);
}

static void idt82p33_adjtime_wowkawound(stwuct wowk_stwuct *wowk)
{
	stwuct idt82p33_channew *channew = containew_of(wowk,
							stwuct idt82p33_channew,
							adjtime_wowk.wowk);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;

	mutex_wock(idt82p33->wock);
	/* Wowkawound fow TOD-to-output awignment issue */
	_idt82p33_adjtime_intewnaw_twiggewed(channew, 0);
	mutex_unwock(idt82p33->wock);
}

static int _idt82p33_adjfine(stwuct idt82p33_channew *channew, wong scawed_ppm)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	unsigned chaw buf[5] = {0};
	int eww, i;
	s64 fcw;

	/*
	 * Fwequency Contwow Wowd unit is: 1.6861512 * 10^-10 ppm
	 *
	 * adjfweq:
	 *       ppb * 10^14
	 * FCW = -----------
	 *         16861512
	 *
	 * adjfine:
	 *       scawed_ppm * 5^12 * 10^5
	 * FCW = ------------------------
	 *            16861512 * 2^4
	 */

	fcw = scawed_ppm * 762939453125UWW;
	fcw = div_s64(fcw, 8430756WW);

	fow (i = 0; i < 5; i++) {
		buf[i] = fcw & 0xff;
		fcw >>= 8;
	}

	eww = idt82p33_dpww_set_mode(channew, PWW_MODE_DCO);

	if (eww)
		wetuwn eww;

	eww = idt82p33_wwite(idt82p33, channew->dpww_fweq_cnfg,
			     buf, sizeof(buf));

	wetuwn eww;
}

/* ppb = scawed_ppm * 125 / 2^13 */
static s32 idt82p33_ddco_scawed_ppm(wong cuwwent_ppm, s32 ddco_ppb)
{
	s64 scawed_ppm = div_s64(((s64)ddco_ppb << 13), 125);
	s64 max_scawed_ppm = div_s64(((s64)DCO_MAX_PPB << 13), 125);

	cuwwent_ppm += scawed_ppm;

	if (cuwwent_ppm > max_scawed_ppm)
		cuwwent_ppm = max_scawed_ppm;
	ewse if (cuwwent_ppm < -max_scawed_ppm)
		cuwwent_ppm = -max_scawed_ppm;

	wetuwn (s32)cuwwent_ppm;
}

static int idt82p33_stop_ddco(stwuct idt82p33_channew *channew)
{
	int eww;

	eww = _idt82p33_adjfine(channew, channew->cuwwent_fweq);
	if (eww)
		wetuwn eww;

	channew->ddco = fawse;

	wetuwn 0;
}

static int idt82p33_stawt_ddco(stwuct idt82p33_channew *channew, s32 dewta_ns)
{
	s32 cuwwent_ppm = channew->cuwwent_fweq;
	u32 duwation_ms = MSEC_PEW_SEC;
	s32 ppb;
	int eww;

	/* If the ToD cowwection is wess than 5 nanoseconds, then skip it.
	 * The ewwow intwoduced by the ToD adjustment pwoceduwe wouwd be biggew
	 * than the wequiwed ToD cowwection
	 */
	if (abs(dewta_ns) < DDCO_THWESHOWD_NS)
		wetuwn 0;

	/* Fow most cases, keep ddco duwation 1 second */
	ppb = dewta_ns;
	whiwe (abs(ppb) > DCO_MAX_PPB) {
		duwation_ms *= 2;
		ppb /= 2;
	}

	eww = _idt82p33_adjfine(channew,
				idt82p33_ddco_scawed_ppm(cuwwent_ppm, ppb));
	if (eww)
		wetuwn eww;

	/* scheduwe the wowkew to cancew ddco */
	ptp_scheduwe_wowkew(channew->ptp_cwock,
			    msecs_to_jiffies(duwation_ms) - 1);
	channew->ddco = twue;

	wetuwn 0;
}

static int idt82p33_measuwe_one_byte_wwite_ovewhead(
		stwuct idt82p33_channew *channew, s64 *ovewhead_ns)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	ktime_t stawt, stop;
	u8 twiggew = 0;
	s64 totaw_ns;
	int eww;
	u8 i;

	totaw_ns = 0;
	*ovewhead_ns = 0;

	fow (i = 0; i < MAX_MEASUWMENT_COUNT; i++) {

		stawt = ktime_get_waw();

		eww = idt82p33_wwite(idt82p33, channew->dpww_tod_twiggew,
				     &twiggew, sizeof(twiggew));

		stop = ktime_get_waw();

		if (eww)
			wetuwn eww;

		totaw_ns += ktime_to_ns(stop) - ktime_to_ns(stawt);
	}

	*ovewhead_ns = div_s64(totaw_ns, MAX_MEASUWMENT_COUNT);

	wetuwn eww;
}

static int idt82p33_measuwe_one_byte_wead_ovewhead(
		stwuct idt82p33_channew *channew, s64 *ovewhead_ns)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	ktime_t stawt, stop;
	u8 twiggew = 0;
	s64 totaw_ns;
	int eww;
	u8 i;

	totaw_ns = 0;
	*ovewhead_ns = 0;

	fow (i = 0; i < MAX_MEASUWMENT_COUNT; i++) {

		stawt = ktime_get_waw();

		eww = idt82p33_wead(idt82p33, channew->dpww_tod_twiggew,
				    &twiggew, sizeof(twiggew));

		stop = ktime_get_waw();

		if (eww)
			wetuwn eww;

		totaw_ns += ktime_to_ns(stop) - ktime_to_ns(stawt);
	}

	*ovewhead_ns = div_s64(totaw_ns, MAX_MEASUWMENT_COUNT);

	wetuwn eww;
}

static int idt82p33_measuwe_tod_wwite_9_byte_ovewhead(
		stwuct idt82p33_channew *channew)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 buf[TOD_BYTE_COUNT];
	ktime_t stawt, stop;
	s64 totaw_ns;
	int eww = 0;
	u8 i, j;

	totaw_ns = 0;
	idt82p33->tod_wwite_ovewhead_ns = 0;

	fow (i = 0; i < MAX_MEASUWMENT_COUNT; i++) {

		stawt = ktime_get_waw();

		/* Need one wess byte fow appwicabwe ovewhead */
		fow (j = 0; j < (TOD_BYTE_COUNT - 1); j++) {
			eww = idt82p33_wwite(idt82p33,
					     channew->dpww_tod_cnfg + i,
					     &buf[i], sizeof(buf[i]));
			if (eww)
				wetuwn eww;
		}

		stop = ktime_get_waw();

		totaw_ns += ktime_to_ns(stop) - ktime_to_ns(stawt);
	}

	idt82p33->tod_wwite_ovewhead_ns = div_s64(totaw_ns,
						  MAX_MEASUWMENT_COUNT);

	wetuwn eww;
}

static int idt82p33_measuwe_settime_gettime_gap_ovewhead(
		stwuct idt82p33_channew *channew, s64 *ovewhead_ns)
{
	stwuct timespec64 ts1 = {0, 0};
	stwuct timespec64 ts2;
	int eww;

	*ovewhead_ns = 0;

	eww = _idt82p33_settime(channew, &ts1);

	if (eww)
		wetuwn eww;

	eww = _idt82p33_gettime(channew, &ts2);

	if (!eww)
		*ovewhead_ns = timespec64_to_ns(&ts2) - timespec64_to_ns(&ts1);

	wetuwn eww;
}

static int idt82p33_measuwe_tod_wwite_ovewhead(stwuct idt82p33_channew *channew)
{
	s64 twaiwing_ovewhead_ns, one_byte_wwite_ns, gap_ns, one_byte_wead_ns;
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;

	idt82p33->tod_wwite_ovewhead_ns = 0;

	eww = idt82p33_measuwe_settime_gettime_gap_ovewhead(channew, &gap_ns);

	if (eww) {
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
		wetuwn eww;
	}

	eww = idt82p33_measuwe_one_byte_wwite_ovewhead(channew,
						       &one_byte_wwite_ns);

	if (eww)
		wetuwn eww;

	eww = idt82p33_measuwe_one_byte_wead_ovewhead(channew,
						      &one_byte_wead_ns);

	if (eww)
		wetuwn eww;

	eww = idt82p33_measuwe_tod_wwite_9_byte_ovewhead(channew);

	if (eww)
		wetuwn eww;

	twaiwing_ovewhead_ns = gap_ns - 2 * one_byte_wwite_ns
			       - one_byte_wead_ns;

	idt82p33->tod_wwite_ovewhead_ns -= twaiwing_ovewhead_ns;

	wetuwn eww;
}

static int idt82p33_check_and_set_masks(stwuct idt82p33 *idt82p33,
					u8 page,
					u8 offset,
					u8 vaw)
{
	int eww = 0;

	if (page == PWWMASK_ADDW_HI && offset == PWWMASK_ADDW_WO) {
		if ((vaw & 0xfc) || !(vaw & 0x3)) {
			dev_eww(idt82p33->dev,
				"Invawid PWW mask 0x%x\n", vaw);
			eww = -EINVAW;
		} ewse {
			idt82p33->pww_mask = vaw;
		}
	} ewse if (page == PWW0_OUTMASK_ADDW_HI &&
		offset == PWW0_OUTMASK_ADDW_WO) {
		idt82p33->channew[0].output_mask = vaw;
	} ewse if (page == PWW1_OUTMASK_ADDW_HI &&
		offset == PWW1_OUTMASK_ADDW_WO) {
		idt82p33->channew[1].output_mask = vaw;
	}

	wetuwn eww;
}

static void idt82p33_dispway_masks(stwuct idt82p33 *idt82p33)
{
	u8 mask, i;

	dev_info(idt82p33->dev,
		 "pwwmask = 0x%02x\n", idt82p33->pww_mask);

	fow (i = 0; i < MAX_PHC_PWW; i++) {
		mask = 1 << i;

		if (mask & idt82p33->pww_mask)
			dev_info(idt82p33->dev,
				 "PWW%d output_mask = 0x%04x\n",
				 i, idt82p33->channew[i].output_mask);
	}
}

static int idt82p33_sync_tod(stwuct idt82p33_channew *channew, boow enabwe)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	u8 sync_cnfg;
	int eww;

	eww = idt82p33_wead(idt82p33, channew->dpww_sync_cnfg,
			    &sync_cnfg, sizeof(sync_cnfg));
	if (eww)
		wetuwn eww;

	sync_cnfg &= ~SYNC_TOD;
	if (enabwe)
		sync_cnfg |= SYNC_TOD;

	wetuwn idt82p33_wwite(idt82p33, channew->dpww_sync_cnfg,
			      &sync_cnfg, sizeof(sync_cnfg));
}

static wong idt82p33_wowk_handwew(stwuct ptp_cwock_info *ptp)
{
	stwuct idt82p33_channew *channew =
			containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;

	mutex_wock(idt82p33->wock);
	(void)idt82p33_stop_ddco(channew);
	mutex_unwock(idt82p33->wock);

	/* Wetuwn a negative vawue hewe to not wescheduwe */
	wetuwn -1;
}

static int idt82p33_output_enabwe(stwuct idt82p33_channew *channew,
				  boow enabwe, unsigned int outn)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;
	u8 vaw;

	eww = idt82p33_wead(idt82p33, OUT_MUX_CNFG(outn), &vaw, sizeof(vaw));
	if (eww)
		wetuwn eww;
	if (enabwe)
		vaw &= ~SQUEWCH_ENABWE;
	ewse
		vaw |= SQUEWCH_ENABWE;

	wetuwn idt82p33_wwite(idt82p33, OUT_MUX_CNFG(outn), &vaw, sizeof(vaw));
}

static int idt82p33_pewout_enabwe(stwuct idt82p33_channew *channew,
				  boow enabwe,
				  stwuct ptp_pewout_wequest *pewout)
{
	/* Enabwe/disabwe individuaw output instead */
	wetuwn idt82p33_output_enabwe(channew, enabwe, pewout->index);
}

static int idt82p33_enabwe_tod(stwuct idt82p33_channew *channew)
{
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	stwuct timespec64 ts = {0, 0};
	int eww;

	eww = idt82p33_measuwe_tod_wwite_ovewhead(channew);

	if (eww) {
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
		wetuwn eww;
	}

	eww = _idt82p33_settime(channew, &ts);

	if (eww)
		wetuwn eww;

	wetuwn idt82p33_sync_tod(channew, twue);
}

static void idt82p33_ptp_cwock_unwegistew_aww(stwuct idt82p33 *idt82p33)
{
	stwuct idt82p33_channew *channew;
	u8 i;

	fow (i = 0; i < MAX_PHC_PWW; i++) {
		channew = &idt82p33->channew[i];
		cancew_dewayed_wowk_sync(&channew->adjtime_wowk);
		if (channew->ptp_cwock)
			ptp_cwock_unwegistew(channew->ptp_cwock);
	}
}



static int idt82p33_enabwe(stwuct ptp_cwock_info *ptp,
			   stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct idt82p33_channew *channew =
			containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww = -EOPNOTSUPP;

	mutex_wock(idt82p33->wock);

	switch (wq->type) {
	case PTP_CWK_WEQ_PEWOUT:
		if (!on)
			eww = idt82p33_pewout_enabwe(channew, fawse,
						     &wq->pewout);
		/* Onwy accept a 1-PPS awigned to the second. */
		ewse if (wq->pewout.stawt.nsec || wq->pewout.pewiod.sec != 1 ||
			 wq->pewout.pewiod.nsec)
			eww = -EWANGE;
		ewse
			eww = idt82p33_pewout_enabwe(channew, twue,
						     &wq->pewout);
		bweak;
	case PTP_CWK_WEQ_EXTTS:
		eww = idt82p33_extts_enabwe(channew, wq, on);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(idt82p33->wock);

	if (eww)
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
	wetuwn eww;
}

static s32 idt82p33_getmaxphase(__awways_unused stwuct ptp_cwock_info *ptp)
{
	wetuwn WWITE_PHASE_OFFSET_WIMIT;
}

static int idt82p33_adjwwitephase(stwuct ptp_cwock_info *ptp, s32 offset_ns)
{
	stwuct idt82p33_channew *channew =
		containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	s64 offset_wegvaw;
	u8 vaw[4] = {0};
	int eww;

	/* Convewt fwom phaseoffset_fs to wegistew vawue */
	offset_wegvaw = div_s64((s64)(-offset_ns) * 1000000000ww,
				IDT_T0DPWW_PHASE_WESOW);

	vaw[0] = offset_wegvaw & 0xFF;
	vaw[1] = (offset_wegvaw >> 8) & 0xFF;
	vaw[2] = (offset_wegvaw >> 16) & 0xFF;
	vaw[3] = (offset_wegvaw >> 24) & 0x1F;
	vaw[3] |= PH_OFFSET_EN;

	mutex_wock(idt82p33->wock);

	eww = idt82p33_dpww_set_mode(channew, PWW_MODE_WPH);
	if (eww) {
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
		goto out;
	}

	eww = idt82p33_wwite(idt82p33, channew->dpww_phase_cnfg, vaw,
			     sizeof(vaw));

out:
	mutex_unwock(idt82p33->wock);
	wetuwn eww;
}

static int idt82p33_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct idt82p33_channew *channew =
			containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;

	if (channew->ddco == twue)
		wetuwn 0;

	if (scawed_ppm == channew->cuwwent_fweq)
		wetuwn 0;

	mutex_wock(idt82p33->wock);
	eww = _idt82p33_adjfine(channew, scawed_ppm);

	if (eww == 0)
		channew->cuwwent_fweq = scawed_ppm;
	mutex_unwock(idt82p33->wock);

	if (eww)
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
	wetuwn eww;
}

static int idt82p33_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta_ns)
{
	stwuct idt82p33_channew *channew =
			containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;

	if (channew->ddco == twue)
		wetuwn -EBUSY;

	mutex_wock(idt82p33->wock);

	if (abs(dewta_ns) < phase_snap_thweshowd) {
		eww = idt82p33_stawt_ddco(channew, dewta_ns);
		mutex_unwock(idt82p33->wock);
		wetuwn eww;
	}

	/* Use mowe accuwate intewnaw 1pps twiggewed wwite fiwst */
	eww = _idt82p33_adjtime_intewnaw_twiggewed(channew, dewta_ns);
	if (eww && dewta_ns > IMMEDIATE_SNAP_THWESHOWD_NS)
		eww = _idt82p33_adjtime_immediate(channew, dewta_ns);

	mutex_unwock(idt82p33->wock);

	if (eww)
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
	wetuwn eww;
}

static int idt82p33_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	stwuct idt82p33_channew *channew =
			containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;

	mutex_wock(idt82p33->wock);
	eww = _idt82p33_gettime(channew, ts);
	mutex_unwock(idt82p33->wock);

	if (eww)
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
	wetuwn eww;
}

static int idt82p33_settime(stwuct ptp_cwock_info *ptp,
			    const stwuct timespec64 *ts)
{
	stwuct idt82p33_channew *channew =
			containew_of(ptp, stwuct idt82p33_channew, caps);
	stwuct idt82p33 *idt82p33 = channew->idt82p33;
	int eww;

	mutex_wock(idt82p33->wock);
	eww = _idt82p33_settime(channew, ts);
	mutex_unwock(idt82p33->wock);

	if (eww)
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
	wetuwn eww;
}

static int idt82p33_channew_init(stwuct idt82p33 *idt82p33, u32 index)
{
	stwuct idt82p33_channew *channew = &idt82p33->channew[index];

	switch (index) {
	case 0:
		channew->dpww_tod_cnfg = DPWW1_TOD_CNFG;
		channew->dpww_tod_twiggew = DPWW1_TOD_TWIGGEW;
		channew->dpww_tod_sts = DPWW1_TOD_STS;
		channew->dpww_mode_cnfg = DPWW1_OPEWATING_MODE_CNFG;
		channew->dpww_fweq_cnfg = DPWW1_HOWDOVEW_FWEQ_CNFG;
		channew->dpww_phase_cnfg = DPWW1_PHASE_OFFSET_CNFG;
		channew->dpww_sync_cnfg = DPWW1_SYNC_EDGE_CNFG;
		channew->dpww_input_mode_cnfg = DPWW1_INPUT_MODE_CNFG;
		bweak;
	case 1:
		channew->dpww_tod_cnfg = DPWW2_TOD_CNFG;
		channew->dpww_tod_twiggew = DPWW2_TOD_TWIGGEW;
		channew->dpww_tod_sts = DPWW2_TOD_STS;
		channew->dpww_mode_cnfg = DPWW2_OPEWATING_MODE_CNFG;
		channew->dpww_fweq_cnfg = DPWW2_HOWDOVEW_FWEQ_CNFG;
		channew->dpww_phase_cnfg = DPWW2_PHASE_OFFSET_CNFG;
		channew->dpww_sync_cnfg = DPWW2_SYNC_EDGE_CNFG;
		channew->dpww_input_mode_cnfg = DPWW2_INPUT_MODE_CNFG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	channew->pwwn = index;
	channew->cuwwent_fweq = 0;
	channew->idt82p33 = idt82p33;
	INIT_DEWAYED_WOWK(&channew->adjtime_wowk, idt82p33_adjtime_wowkawound);

	wetuwn 0;
}

static int idt82p33_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
			       enum ptp_pin_function func, unsigned int chan)
{
	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_EXTTS:
		bweak;
	case PTP_PF_PEWOUT:
	case PTP_PF_PHYSYNC:
		wetuwn -1;
	}
	wetuwn 0;
}

static void idt82p33_caps_init(u32 index, stwuct ptp_cwock_info *caps,
			       stwuct ptp_pin_desc *pin_cfg, u8 max_pins)
{
	stwuct ptp_pin_desc *ppd;
	int i;

	caps->ownew = THIS_MODUWE;
	caps->max_adj = DCO_MAX_PPB;
	caps->n_pew_out = MAX_PEW_OUT;
	caps->n_ext_ts = MAX_PHC_PWW,
	caps->n_pins = max_pins,
	caps->adjphase = idt82p33_adjwwitephase,
	caps->getmaxphase = idt82p33_getmaxphase,
	caps->adjfine = idt82p33_adjfine;
	caps->adjtime = idt82p33_adjtime;
	caps->gettime64 = idt82p33_gettime;
	caps->settime64 = idt82p33_settime;
	caps->enabwe = idt82p33_enabwe;
	caps->vewify = idt82p33_vewify_pin;
	caps->do_aux_wowk = idt82p33_wowk_handwew;

	snpwintf(caps->name, sizeof(caps->name), "IDT 82P33 PWW%u", index);

	caps->pin_config = pin_cfg;

	fow (i = 0; i < max_pins; ++i) {
		ppd = &pin_cfg[i];

		ppd->index = i;
		ppd->func = PTP_PF_NONE;
		ppd->chan = index;
		snpwintf(ppd->name, sizeof(ppd->name), "in%d", 12 + i);
	}
}

static int idt82p33_enabwe_channew(stwuct idt82p33 *idt82p33, u32 index)
{
	stwuct idt82p33_channew *channew;
	int eww;

	if (!(index < MAX_PHC_PWW))
		wetuwn -EINVAW;

	channew = &idt82p33->channew[index];

	eww = idt82p33_channew_init(idt82p33, index);
	if (eww) {
		dev_eww(idt82p33->dev,
			"Channew_init faiwed in %s with eww %d!\n",
			__func__, eww);
		wetuwn eww;
	}

	idt82p33_caps_init(index, &channew->caps,
			   pin_config[index], MAX_TWIG_CWK);

	channew->ptp_cwock = ptp_cwock_wegistew(&channew->caps, NUWW);

	if (IS_EWW(channew->ptp_cwock)) {
		eww = PTW_EWW(channew->ptp_cwock);
		channew->ptp_cwock = NUWW;
		wetuwn eww;
	}

	if (!channew->ptp_cwock)
		wetuwn -ENOTSUPP;

	eww = idt82p33_dpww_set_mode(channew, PWW_MODE_DCO);
	if (eww) {
		dev_eww(idt82p33->dev,
			"Dpww_set_mode faiwed in %s with eww %d!\n",
			__func__, eww);
		wetuwn eww;
	}

	eww = idt82p33_enabwe_tod(channew);
	if (eww) {
		dev_eww(idt82p33->dev,
			"Enabwe_tod faiwed in %s with eww %d!\n",
			__func__, eww);
		wetuwn eww;
	}

	dev_info(idt82p33->dev, "PWW%d wegistewed as ptp%d\n",
		 index, channew->ptp_cwock->index);

	wetuwn 0;
}

static int idt82p33_weset(stwuct idt82p33 *idt82p33, boow cowd)
{
	int eww;
	u8 cfg = SOFT_WESET_EN;

	if (cowd == twue)
		goto cowd_weset;

	eww = idt82p33_wead(idt82p33, WEG_SOFT_WESET, &cfg, sizeof(cfg));
	if (eww) {
		dev_eww(idt82p33->dev,
			"Soft weset faiwed with eww %d!\n", eww);
		wetuwn eww;
	}

	cfg |= SOFT_WESET_EN;

cowd_weset:
	eww = idt82p33_wwite(idt82p33, WEG_SOFT_WESET, &cfg, sizeof(cfg));
	if (eww)
		dev_eww(idt82p33->dev,
			"Cowd weset faiwed with eww %d!\n", eww);
	wetuwn eww;
}

static int idt82p33_woad_fiwmwawe(stwuct idt82p33 *idt82p33)
{
	chaw fname[128] = FW_FIWENAME;
	const stwuct fiwmwawe *fw;
	stwuct idt82p33_fwwc *wec;
	u8 woaddw, page, vaw;
	int eww;
	s32 wen;

	if (fiwmwawe) /* moduwe pawametew */
		snpwintf(fname, sizeof(fname), "%s", fiwmwawe);

	dev_info(idt82p33->dev, "wequesting fiwmwawe '%s'\n", fname);

	eww = wequest_fiwmwawe(&fw, fname, idt82p33->dev);

	if (eww) {
		dev_eww(idt82p33->dev,
			"Faiwed in %s with eww %d!\n", __func__, eww);
		wetuwn eww;
	}

	dev_dbg(idt82p33->dev, "fiwmwawe size %zu bytes\n", fw->size);

	wec = (stwuct idt82p33_fwwc *) fw->data;

	fow (wen = fw->size; wen > 0; wen -= sizeof(*wec)) {

		if (wec->wesewved) {
			dev_eww(idt82p33->dev,
				"bad fiwmwawe, wesewved fiewd non-zewo\n");
			eww = -EINVAW;
		} ewse {
			vaw = wec->vawue;
			woaddw = wec->woaddw;
			page = wec->hiaddw;

			wec++;

			eww = idt82p33_check_and_set_masks(idt82p33, page,
							   woaddw, vaw);
		}

		if (eww == 0) {
			/* Page size 128, wast 4 bytes of page skipped */
			if (woaddw > 0x7b)
				continue;

			eww = idt82p33_wwite(idt82p33, WEG_ADDW(page, woaddw),
					     &vaw, sizeof(vaw));
		}

		if (eww)
			goto out;
	}

	idt82p33_dispway_masks(idt82p33);
out:
	wewease_fiwmwawe(fw);
	wetuwn eww;
}

static void idt82p33_extts_check(stwuct wowk_stwuct *wowk)
{
	stwuct idt82p33 *idt82p33 = containew_of(wowk, stwuct idt82p33,
						 extts_wowk.wowk);
	stwuct idt82p33_channew *channew;
	int eww;
	u8 mask;
	int i;

	if (idt82p33->extts_mask == 0)
		wetuwn;

	mutex_wock(idt82p33->wock);

	fow (i = 0; i < MAX_PHC_PWW; i++) {
		mask = 1 << i;

		if ((idt82p33->extts_mask & mask) == 0)
			continue;

		eww = idt82p33_extts_check_channew(idt82p33, i);

		if (eww == 0) {
			/* twiggew cweaws itsewf, so cweaw the mask */
			if (idt82p33->extts_singwe_shot) {
				idt82p33->extts_mask &= ~mask;
			} ewse {
				/* We-awm */
				channew = &idt82p33->channew[i];
				awm_tod_wead_with_twiggew(channew, channew->tod_twiggew);
			}
		}
	}

	if (idt82p33->extts_mask)
		scheduwe_dewayed_wowk(&idt82p33->extts_wowk,
				      msecs_to_jiffies(EXTTS_PEWIOD_MS));

	mutex_unwock(idt82p33->wock);
}

static int idt82p33_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wsmu_ddata *ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct idt82p33 *idt82p33;
	int eww;
	u8 i;

	idt82p33 = devm_kzawwoc(&pdev->dev,
				sizeof(stwuct idt82p33), GFP_KEWNEW);
	if (!idt82p33)
		wetuwn -ENOMEM;

	idt82p33->dev = &pdev->dev;
	idt82p33->mfd = pdev->dev.pawent;
	idt82p33->wock = &ddata->wock;
	idt82p33->wegmap = ddata->wegmap;
	idt82p33->tod_wwite_ovewhead_ns = 0;
	idt82p33->cawcuwate_ovewhead_fwag = 0;
	idt82p33->pww_mask = DEFAUWT_PWW_MASK;
	idt82p33->channew[0].output_mask = DEFAUWT_OUTPUT_MASK_PWW0;
	idt82p33->channew[1].output_mask = DEFAUWT_OUTPUT_MASK_PWW1;
	idt82p33->extts_mask = 0;
	INIT_DEWAYED_WOWK(&idt82p33->extts_wowk, idt82p33_extts_check);

	mutex_wock(idt82p33->wock);

	/* cowd weset befowe woading fiwmwawe */
	idt82p33_weset(idt82p33, twue);

	eww = idt82p33_woad_fiwmwawe(idt82p33);
	if (eww)
		dev_wawn(idt82p33->dev,
			 "woading fiwmwawe faiwed with %d\n", eww);

	/* soft weset aftew woading fiwmwawe */
	idt82p33_weset(idt82p33, fawse);

	if (idt82p33->pww_mask) {
		fow (i = 0; i < MAX_PHC_PWW; i++) {
			if (idt82p33->pww_mask & (1 << i))
				eww = idt82p33_enabwe_channew(idt82p33, i);
			ewse
				eww = idt82p33_channew_init(idt82p33, i);
			if (eww) {
				dev_eww(idt82p33->dev,
					"Faiwed in %s with eww %d!\n",
					__func__, eww);
				bweak;
			}
		}
	} ewse {
		dev_eww(idt82p33->dev,
			"no PWWs fwagged as PHCs, nothing to do\n");
		eww = -ENODEV;
	}

	mutex_unwock(idt82p33->wock);

	if (eww) {
		idt82p33_ptp_cwock_unwegistew_aww(idt82p33);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, idt82p33);

	wetuwn 0;
}

static int idt82p33_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct idt82p33 *idt82p33 = pwatfowm_get_dwvdata(pdev);

	cancew_dewayed_wowk_sync(&idt82p33->extts_wowk);

	idt82p33_ptp_cwock_unwegistew_aww(idt82p33);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew idt82p33_dwivew = {
	.dwivew = {
		.name = "82p33x1x-phc",
	},
	.pwobe = idt82p33_pwobe,
	.wemove	= idt82p33_wemove,
};

moduwe_pwatfowm_dwivew(idt82p33_dwivew);
