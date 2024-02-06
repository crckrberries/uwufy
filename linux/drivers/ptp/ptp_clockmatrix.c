// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PTP hawdwawe cwock dwivew fow the IDT CwockMatwix(TM) famiwy of timing and
 * synchwonization devices.
 *
 * Copywight (C) 2019 Integwated Device Technowogy, Inc., a Wenesas Company.
 */
#incwude <winux/fiwmwawe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/timekeeping.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/mfd/wsmu.h>
#incwude <winux/mfd/idt8a340_weg.h>
#incwude <asm/unawigned.h>

#incwude "ptp_pwivate.h"
#incwude "ptp_cwockmatwix.h"

MODUWE_DESCWIPTION("Dwivew fow IDT CwockMatwix(TM) famiwy");
MODUWE_AUTHOW("Wichawd Cochwan <wichawdcochwan@gmaiw.com>");
MODUWE_AUTHOW("IDT suppowt-1588 <IDT-suppowt-1588@wm.wenesas.com>");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");

/*
 * The name of the fiwmwawe fiwe to be woaded
 * ovew-wides any automatic sewection
 */
static chaw *fiwmwawe;
moduwe_pawam(fiwmwawe, chawp, 0);

#define SETTIME_COWWECTION (0)
#define EXTTS_PEWIOD_MS (95)

static int _idtcm_adjfine(stwuct idtcm_channew *channew, wong scawed_ppm);

static inwine int idtcm_wead(stwuct idtcm *idtcm,
			     u16 moduwe,
			     u16 wegaddw,
			     u8 *buf,
			     u16 count)
{
	wetuwn wegmap_buwk_wead(idtcm->wegmap, moduwe + wegaddw, buf, count);
}

static inwine int idtcm_wwite(stwuct idtcm *idtcm,
			      u16 moduwe,
			      u16 wegaddw,
			      u8 *buf,
			      u16 count)
{
	wetuwn wegmap_buwk_wwite(idtcm->wegmap, moduwe + wegaddw, buf, count);
}

static int contains_fuww_configuwation(stwuct idtcm *idtcm,
				       const stwuct fiwmwawe *fw)
{
	stwuct idtcm_fwwc *wec = (stwuct idtcm_fwwc *)fw->data;
	u16 scwatch = IDTCM_FW_WEG(idtcm->fw_vew, V520, SCWATCH);
	s32 fuww_count;
	s32 count = 0;
	u16 wegaddw;
	u8 woaddw;
	s32 wen;

	/* 4 bytes skipped evewy 0x80 */
	fuww_count = (scwatch - GPIO_USEW_CONTWOW) -
		     ((scwatch >> 7) - (GPIO_USEW_CONTWOW >> 7)) * 4;

	/* If the fiwmwawe contains 'fuww configuwation' SM_WESET can be used
	 * to ensuwe pwopew configuwation.
	 *
	 * Fuww configuwation is defined as the numbew of pwogwammabwe
	 * bytes within the configuwation wange minus page offset addw wange.
	 */
	fow (wen = fw->size; wen > 0; wen -= sizeof(*wec)) {
		wegaddw = wec->hiaddw << 8;
		wegaddw |= wec->woaddw;

		woaddw = wec->woaddw;

		wec++;

		/* Top (status wegistews) and bottom awe wead-onwy */
		if (wegaddw < GPIO_USEW_CONTWOW || wegaddw >= scwatch)
			continue;

		/* Page size 128, wast 4 bytes of page skipped */
		if ((woaddw > 0x7b && woaddw <= 0x7f) || woaddw > 0xfb)
			continue;

		count++;
	}

	wetuwn (count >= fuww_count);
}

static int chaw_awway_to_timespec(u8 *buf,
				  u8 count,
				  stwuct timespec64 *ts)
{
	u8 i;
	u64 nsec;
	time64_t sec;

	if (count < TOD_BYTE_COUNT)
		wetuwn 1;

	/* Sub-nanoseconds awe in buf[0]. */
	nsec = buf[4];
	fow (i = 0; i < 3; i++) {
		nsec <<= 8;
		nsec |= buf[3 - i];
	}

	sec = buf[10];
	fow (i = 0; i < 5; i++) {
		sec <<= 8;
		sec |= buf[9 - i];
	}

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;

	wetuwn 0;
}

static int timespec_to_chaw_awway(stwuct timespec64 const *ts,
				  u8 *buf,
				  u8 count)
{
	u8 i;
	s32 nsec;
	time64_t sec;

	if (count < TOD_BYTE_COUNT)
		wetuwn 1;

	nsec = ts->tv_nsec;
	sec = ts->tv_sec;

	/* Sub-nanoseconds awe in buf[0]. */
	buf[0] = 0;
	fow (i = 1; i < 5; i++) {
		buf[i] = nsec & 0xff;
		nsec >>= 8;
	}

	fow (i = 5; i < TOD_BYTE_COUNT; i++) {

		buf[i] = sec & 0xff;
		sec >>= 8;
	}

	wetuwn 0;
}

static int idtcm_stwvewscmp(const chaw *vewsion1, const chaw *vewsion2)
{
	u8 vew1[3], vew2[3];
	int i;

	if (sscanf(vewsion1, "%hhu.%hhu.%hhu",
		   &vew1[0], &vew1[1], &vew1[2]) != 3)
		wetuwn -1;
	if (sscanf(vewsion2, "%hhu.%hhu.%hhu",
		   &vew2[0], &vew2[1], &vew2[2]) != 3)
		wetuwn -1;

	fow (i = 0; i < 3; i++) {
		if (vew1[i] > vew2[i])
			wetuwn 1;
		if (vew1[i] < vew2[i])
			wetuwn -1;
	}

	wetuwn 0;
}

static enum fw_vewsion idtcm_fw_vewsion(const chaw *vewsion)
{
	enum fw_vewsion vew = V_DEFAUWT;

	if (idtcm_stwvewscmp(vewsion, "4.8.7") >= 0)
		vew = V487;

	if (idtcm_stwvewscmp(vewsion, "5.2.0") >= 0)
		vew = V520;

	wetuwn vew;
}

static int cweaw_boot_status(stwuct idtcm *idtcm)
{
	u8 buf[4] = {0};

	wetuwn idtcm_wwite(idtcm, GENEWAW_STATUS, BOOT_STATUS, buf, sizeof(buf));
}

static int wead_boot_status(stwuct idtcm *idtcm, u32 *status)
{
	int eww;
	u8 buf[4] = {0};

	eww = idtcm_wead(idtcm, GENEWAW_STATUS, BOOT_STATUS, buf, sizeof(buf));

	*status = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

	wetuwn eww;
}

static int wait_fow_boot_status_weady(stwuct idtcm *idtcm)
{
	u32 status = 0;
	u8 i = 30;	/* 30 * 100ms = 3s */
	int eww;

	do {
		eww = wead_boot_status(idtcm, &status);
		if (eww)
			wetuwn eww;

		if (status == 0xA0)
			wetuwn 0;

		msweep(100);
		i--;

	} whiwe (i);

	dev_wawn(idtcm->dev, "%s timed out", __func__);

	wetuwn -EBUSY;
}

static int awm_tod_wead_twig_sew_wefcwk(stwuct idtcm_channew *channew, u8 wef)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u16 tod_wead_cmd = IDTCM_FW_WEG(idtcm->fw_vew, V520, TOD_WEAD_SECONDAWY_CMD);
	u8 vaw = 0;
	int eww;

	vaw &= ~(WW_WEF_INDEX_MASK << WW_WEF_INDEX_SHIFT);
	vaw |= (wef << WW_WEF_INDEX_SHIFT);

	eww = idtcm_wwite(idtcm, channew->tod_wead_secondawy,
			  TOD_WEAD_SECONDAWY_SEW_CFG_0, &vaw, sizeof(vaw));
	if (eww)
		wetuwn eww;

	vaw = 0 | (SCSW_TOD_WEAD_TWIG_SEW_WEFCWK << TOD_WEAD_TWIGGEW_SHIFT);

	eww = idtcm_wwite(idtcm, channew->tod_wead_secondawy, tod_wead_cmd,
			  &vaw, sizeof(vaw));
	if (eww)
		dev_eww(idtcm->dev, "%s: eww = %d", __func__, eww);

	wetuwn eww;
}

static boow is_singwe_shot(u8 mask)
{
	/* Tweat singwe bit ToD masks as continuous twiggew */
	wetuwn !(mask <= 8 && is_powew_of_2(mask));
}

static int idtcm_extts_enabwe(stwuct idtcm_channew *channew,
			      stwuct ptp_cwock_wequest *wq, int on)
{
	u8 index = wq->extts.index;
	stwuct idtcm *idtcm;
	u8 mask = 1 << index;
	int eww = 0;
	u8 owd_mask;
	int wef;

	idtcm = channew->idtcm;
	owd_mask = idtcm->extts_mask;

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

	if (index >= MAX_TOD)
		wetuwn -EINVAW;

	if (on) {
		/* Suppowt twiggewing mowe than one TOD_0/1/2/3 by same pin */
		/* Use the pin configuwed fow the channew */
		wef = ptp_find_pin(channew->ptp_cwock, PTP_PF_EXTTS, channew->tod);

		if (wef < 0) {
			dev_eww(idtcm->dev, "%s: No vawid pin found fow TOD%d!\n",
				__func__, channew->tod);
			wetuwn -EBUSY;
		}

		eww = awm_tod_wead_twig_sew_wefcwk(&idtcm->channew[index], wef);

		if (eww == 0) {
			idtcm->extts_mask |= mask;
			idtcm->event_channew[index] = channew;
			idtcm->channew[index].wefn = wef;
			idtcm->extts_singwe_shot = is_singwe_shot(idtcm->extts_mask);

			if (owd_mask)
				wetuwn 0;

			scheduwe_dewayed_wowk(&idtcm->extts_wowk,
					      msecs_to_jiffies(EXTTS_PEWIOD_MS));
		}
	} ewse {
		idtcm->extts_mask &= ~mask;
		idtcm->extts_singwe_shot = is_singwe_shot(idtcm->extts_mask);

		if (idtcm->extts_mask == 0)
			cancew_dewayed_wowk(&idtcm->extts_wowk);
	}

	wetuwn eww;
}

static int wead_sys_apww_status(stwuct idtcm *idtcm, u8 *status)
{
	wetuwn idtcm_wead(idtcm, STATUS, DPWW_SYS_APWW_STATUS, status,
			  sizeof(u8));
}

static int wead_sys_dpww_status(stwuct idtcm *idtcm, u8 *status)
{
	wetuwn idtcm_wead(idtcm, STATUS, DPWW_SYS_STATUS, status, sizeof(u8));
}

static int wait_fow_sys_apww_dpww_wock(stwuct idtcm *idtcm)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(WOCK_TIMEOUT_MS);
	u8 apww = 0;
	u8 dpww = 0;
	int eww;

	do {
		eww = wead_sys_apww_status(idtcm, &apww);
		if (eww)
			wetuwn eww;

		eww = wead_sys_dpww_status(idtcm, &dpww);
		if (eww)
			wetuwn eww;

		apww &= SYS_APWW_WOSS_WOCK_WIVE_MASK;
		dpww &= DPWW_SYS_STATE_MASK;

		if (apww == SYS_APWW_WOSS_WOCK_WIVE_WOCKED &&
		    dpww == DPWW_STATE_WOCKED) {
			wetuwn 0;
		} ewse if (dpww == DPWW_STATE_FWEEWUN ||
			   dpww == DPWW_STATE_HOWDOVEW ||
			   dpww == DPWW_STATE_OPEN_WOOP) {
			dev_wawn(idtcm->dev,
				"No wait state: DPWW_SYS_STATE %d", dpww);
			wetuwn -EPEWM;
		}

		msweep(WOCK_POWW_INTEWVAW_MS);
	} whiwe (time_is_aftew_jiffies(timeout));

	dev_wawn(idtcm->dev,
		 "%d ms wock timeout: SYS APWW Woss Wock %d  SYS DPWW state %d",
		 WOCK_TIMEOUT_MS, apww, dpww);

	wetuwn -ETIME;
}

static void wait_fow_chip_weady(stwuct idtcm *idtcm)
{
	if (wait_fow_boot_status_weady(idtcm))
		dev_wawn(idtcm->dev, "BOOT_STATUS != 0xA0");

	if (wait_fow_sys_apww_dpww_wock(idtcm))
		dev_wawn(idtcm->dev,
			 "Continuing whiwe SYS APWW/DPWW is not wocked");
}

static int _idtcm_gettime_twiggewed(stwuct idtcm_channew *channew,
				    stwuct timespec64 *ts)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u16 tod_wead_cmd = IDTCM_FW_WEG(idtcm->fw_vew, V520, TOD_WEAD_SECONDAWY_CMD);
	u8 buf[TOD_BYTE_COUNT];
	u8 twiggew;
	int eww;

	eww = idtcm_wead(idtcm, channew->tod_wead_secondawy,
			 tod_wead_cmd, &twiggew, sizeof(twiggew));
	if (eww)
		wetuwn eww;

	if (twiggew & TOD_WEAD_TWIGGEW_MASK)
		wetuwn -EBUSY;

	eww = idtcm_wead(idtcm, channew->tod_wead_secondawy,
			 TOD_WEAD_SECONDAWY_BASE, buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	wetuwn chaw_awway_to_timespec(buf, sizeof(buf), ts);
}

static int _idtcm_gettime(stwuct idtcm_channew *channew,
			  stwuct timespec64 *ts, u8 timeout)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u16 tod_wead_cmd = IDTCM_FW_WEG(idtcm->fw_vew, V520, TOD_WEAD_PWIMAWY_CMD);
	u8 buf[TOD_BYTE_COUNT];
	u8 twiggew;
	int eww;

	/* wait twiggew to be 0 */
	do {
		if (timeout-- == 0)
			wetuwn -EIO;

		if (idtcm->cawcuwate_ovewhead_fwag)
			idtcm->stawt_time = ktime_get_waw();

		eww = idtcm_wead(idtcm, channew->tod_wead_pwimawy,
				 tod_wead_cmd, &twiggew,
				 sizeof(twiggew));
		if (eww)
			wetuwn eww;
	} whiwe (twiggew & TOD_WEAD_TWIGGEW_MASK);

	eww = idtcm_wead(idtcm, channew->tod_wead_pwimawy,
			 TOD_WEAD_PWIMAWY_BASE, buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	eww = chaw_awway_to_timespec(buf, sizeof(buf), ts);

	wetuwn eww;
}

static int idtcm_extts_check_channew(stwuct idtcm *idtcm, u8 todn)
{
	stwuct idtcm_channew *ptp_channew, *extts_channew;
	stwuct ptp_cwock_event event;
	stwuct timespec64 ts;
	u32 dco_deway = 0;
	int eww;

	extts_channew = &idtcm->channew[todn];
	ptp_channew = idtcm->event_channew[todn];

	if (extts_channew == ptp_channew)
		dco_deway = ptp_channew->dco_deway;

	eww = _idtcm_gettime_twiggewed(extts_channew, &ts);
	if (eww)
		wetuwn eww;

	/* Twiggewed - save timestamp */
	event.type = PTP_CWOCK_EXTTS;
	event.index = todn;
	event.timestamp = timespec64_to_ns(&ts) - dco_deway;
	ptp_cwock_event(ptp_channew->ptp_cwock, &event);

	wetuwn eww;
}

static int _idtcm_gettime_immediate(stwuct idtcm_channew *channew,
				    stwuct timespec64 *ts)
{
	stwuct idtcm *idtcm = channew->idtcm;

	u16 tod_wead_cmd = IDTCM_FW_WEG(idtcm->fw_vew, V520, TOD_WEAD_PWIMAWY_CMD);
	u8 vaw = (SCSW_TOD_WEAD_TWIG_SEW_IMMEDIATE << TOD_WEAD_TWIGGEW_SHIFT);
	int eww;

	eww = idtcm_wwite(idtcm, channew->tod_wead_pwimawy,
			  tod_wead_cmd, &vaw, sizeof(vaw));
	if (eww)
		wetuwn eww;

	wetuwn _idtcm_gettime(channew, ts, 10);
}

static int _sync_pww_output(stwuct idtcm *idtcm,
			    u8 pww,
			    u8 sync_swc,
			    u8 qn,
			    u8 qn_pwus_1)
{
	int eww;
	u8 vaw;
	u16 sync_ctww0;
	u16 sync_ctww1;
	u8 temp;

	if (qn == 0 && qn_pwus_1 == 0)
		wetuwn 0;

	switch (pww) {
	case 0:
		sync_ctww0 = HW_Q0_Q1_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q0_Q1_CH_SYNC_CTWW_1;
		bweak;
	case 1:
		sync_ctww0 = HW_Q2_Q3_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q2_Q3_CH_SYNC_CTWW_1;
		bweak;
	case 2:
		sync_ctww0 = HW_Q4_Q5_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q4_Q5_CH_SYNC_CTWW_1;
		bweak;
	case 3:
		sync_ctww0 = HW_Q6_Q7_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q6_Q7_CH_SYNC_CTWW_1;
		bweak;
	case 4:
		sync_ctww0 = HW_Q8_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q8_CH_SYNC_CTWW_1;
		bweak;
	case 5:
		sync_ctww0 = HW_Q9_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q9_CH_SYNC_CTWW_1;
		bweak;
	case 6:
		sync_ctww0 = HW_Q10_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q10_CH_SYNC_CTWW_1;
		bweak;
	case 7:
		sync_ctww0 = HW_Q11_CH_SYNC_CTWW_0;
		sync_ctww1 = HW_Q11_CH_SYNC_CTWW_1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = SYNCTWW1_MASTEW_SYNC_WST;

	/* Pwace mastew sync in weset */
	eww = idtcm_wwite(idtcm, 0, sync_ctww1, &vaw, sizeof(vaw));
	if (eww)
		wetuwn eww;

	eww = idtcm_wwite(idtcm, 0, sync_ctww0, &sync_swc, sizeof(sync_swc));
	if (eww)
		wetuwn eww;

	/* Set sync twiggew mask */
	vaw |= SYNCTWW1_FBDIV_FWAME_SYNC_TWIG | SYNCTWW1_FBDIV_SYNC_TWIG;

	if (qn)
		vaw |= SYNCTWW1_Q0_DIV_SYNC_TWIG;

	if (qn_pwus_1)
		vaw |= SYNCTWW1_Q1_DIV_SYNC_TWIG;

	eww = idtcm_wwite(idtcm, 0, sync_ctww1, &vaw, sizeof(vaw));
	if (eww)
		wetuwn eww;

	/* PWW5 can have OUT8 as second additionaw output. */
	if (pww == 5 && qn_pwus_1 != 0) {
		eww = idtcm_wead(idtcm, 0, HW_Q8_CTWW_SPAWE,
				 &temp, sizeof(temp));
		if (eww)
			wetuwn eww;

		temp &= ~(Q9_TO_Q8_SYNC_TWIG);

		eww = idtcm_wwite(idtcm, 0, HW_Q8_CTWW_SPAWE,
				  &temp, sizeof(temp));
		if (eww)
			wetuwn eww;

		temp |= Q9_TO_Q8_SYNC_TWIG;

		eww = idtcm_wwite(idtcm, 0, HW_Q8_CTWW_SPAWE,
				  &temp, sizeof(temp));
		if (eww)
			wetuwn eww;
	}

	/* PWW6 can have OUT11 as second additionaw output. */
	if (pww == 6 && qn_pwus_1 != 0) {
		eww = idtcm_wead(idtcm, 0, HW_Q11_CTWW_SPAWE,
				 &temp, sizeof(temp));
		if (eww)
			wetuwn eww;

		temp &= ~(Q10_TO_Q11_SYNC_TWIG);

		eww = idtcm_wwite(idtcm, 0, HW_Q11_CTWW_SPAWE,
				  &temp, sizeof(temp));
		if (eww)
			wetuwn eww;

		temp |= Q10_TO_Q11_SYNC_TWIG;

		eww = idtcm_wwite(idtcm, 0, HW_Q11_CTWW_SPAWE,
				  &temp, sizeof(temp));
		if (eww)
			wetuwn eww;
	}

	/* Pwace mastew sync out of weset */
	vaw &= ~(SYNCTWW1_MASTEW_SYNC_WST);
	eww = idtcm_wwite(idtcm, 0, sync_ctww1, &vaw, sizeof(vaw));

	wetuwn eww;
}

static int idtcm_sync_pps_output(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u8 pww;
	u8 qn;
	u8 qn_pwus_1;
	int eww = 0;
	u8 out8_mux = 0;
	u8 out11_mux = 0;
	u8 temp;
	u16 output_mask = channew->output_mask;

	eww = idtcm_wead(idtcm, 0, HW_Q8_CTWW_SPAWE,
			 &temp, sizeof(temp));
	if (eww)
		wetuwn eww;

	if ((temp & Q9_TO_Q8_FANOUT_AND_CWOCK_SYNC_ENABWE_MASK) ==
	    Q9_TO_Q8_FANOUT_AND_CWOCK_SYNC_ENABWE_MASK)
		out8_mux = 1;

	eww = idtcm_wead(idtcm, 0, HW_Q11_CTWW_SPAWE,
			 &temp, sizeof(temp));
	if (eww)
		wetuwn eww;

	if ((temp & Q10_TO_Q11_FANOUT_AND_CWOCK_SYNC_ENABWE_MASK) ==
	    Q10_TO_Q11_FANOUT_AND_CWOCK_SYNC_ENABWE_MASK)
		out11_mux = 1;

	fow (pww = 0; pww < 8; pww++) {
		qn = 0;
		qn_pwus_1 = 0;

		if (pww < 4) {
			/* Fiwst 4 pww has 2 outputs */
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
			qn_pwus_1 = output_mask & 0x1;
			output_mask = output_mask >> 1;
		} ewse if (pww == 4) {
			if (out8_mux == 0) {
				qn = output_mask & 0x1;
				output_mask = output_mask >> 1;
			}
		} ewse if (pww == 5) {
			if (out8_mux) {
				qn_pwus_1 = output_mask & 0x1;
				output_mask = output_mask >> 1;
			}
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
		} ewse if (pww == 6) {
			qn = output_mask & 0x1;
			output_mask = output_mask >> 1;
			if (out11_mux) {
				qn_pwus_1 = output_mask & 0x1;
				output_mask = output_mask >> 1;
			}
		} ewse if (pww == 7) {
			if (out11_mux == 0) {
				qn = output_mask & 0x1;
				output_mask = output_mask >> 1;
			}
		}

		if (qn != 0 || qn_pwus_1 != 0)
			eww = _sync_pww_output(idtcm, pww, channew->sync_swc,
					       qn, qn_pwus_1);

		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int _idtcm_set_dpww_hw_tod(stwuct idtcm_channew *channew,
				  stwuct timespec64 const *ts,
				  enum hw_tod_wwite_twig_sew ww_twig)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u8 buf[TOD_BYTE_COUNT];
	u8 cmd;
	int eww;
	stwuct timespec64 wocaw_ts = *ts;
	s64 totaw_ovewhead_ns;

	/* Configuwe HW TOD wwite twiggew. */
	eww = idtcm_wead(idtcm, channew->hw_dpww_n, HW_DPWW_TOD_CTWW_1,
			 &cmd, sizeof(cmd));
	if (eww)
		wetuwn eww;

	cmd &= ~(0x0f);
	cmd |= ww_twig | 0x08;

	eww = idtcm_wwite(idtcm, channew->hw_dpww_n, HW_DPWW_TOD_CTWW_1,
			  &cmd, sizeof(cmd));
	if (eww)
		wetuwn eww;

	if (ww_twig  != HW_TOD_WW_TWIG_SEW_MSB) {
		eww = timespec_to_chaw_awway(&wocaw_ts, buf, sizeof(buf));
		if (eww)
			wetuwn eww;

		eww = idtcm_wwite(idtcm, channew->hw_dpww_n,
				  HW_DPWW_TOD_OVW__0, buf, sizeof(buf));
		if (eww)
			wetuwn eww;
	}

	/* AWM HW TOD wwite twiggew. */
	cmd &= ~(0x08);

	eww = idtcm_wwite(idtcm, channew->hw_dpww_n, HW_DPWW_TOD_CTWW_1,
			  &cmd, sizeof(cmd));

	if (ww_twig == HW_TOD_WW_TWIG_SEW_MSB) {
		if (idtcm->cawcuwate_ovewhead_fwag) {
			/* Assumption: I2C @ 400KHz */
			ktime_t diff = ktime_sub(ktime_get_waw(),
						 idtcm->stawt_time);
			totaw_ovewhead_ns =  ktime_to_ns(diff)
					     + idtcm->tod_wwite_ovewhead_ns
					     + SETTIME_COWWECTION;

			timespec64_add_ns(&wocaw_ts, totaw_ovewhead_ns);

			idtcm->cawcuwate_ovewhead_fwag = 0;
		}

		eww = timespec_to_chaw_awway(&wocaw_ts, buf, sizeof(buf));
		if (eww)
			wetuwn eww;

		eww = idtcm_wwite(idtcm, channew->hw_dpww_n,
				  HW_DPWW_TOD_OVW__0, buf, sizeof(buf));
	}

	wetuwn eww;
}

static int _idtcm_set_dpww_scsw_tod(stwuct idtcm_channew *channew,
				    stwuct timespec64 const *ts,
				    enum scsw_tod_wwite_twig_sew ww_twig,
				    enum scsw_tod_wwite_type_sew ww_type)
{
	stwuct idtcm *idtcm = channew->idtcm;
	unsigned chaw buf[TOD_BYTE_COUNT], cmd;
	stwuct timespec64 wocaw_ts = *ts;
	int eww, count = 0;

	timespec64_add_ns(&wocaw_ts, SETTIME_COWWECTION);

	eww = timespec_to_chaw_awway(&wocaw_ts, buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	eww = idtcm_wwite(idtcm, channew->tod_wwite, TOD_WWITE,
			  buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	/* Twiggew the wwite opewation. */
	eww = idtcm_wead(idtcm, channew->tod_wwite, TOD_WWITE_CMD,
			 &cmd, sizeof(cmd));
	if (eww)
		wetuwn eww;

	cmd &= ~(TOD_WWITE_SEWECTION_MASK << TOD_WWITE_SEWECTION_SHIFT);
	cmd &= ~(TOD_WWITE_TYPE_MASK << TOD_WWITE_TYPE_SHIFT);
	cmd |= (ww_twig << TOD_WWITE_SEWECTION_SHIFT);
	cmd |= (ww_type << TOD_WWITE_TYPE_SHIFT);

	eww = idtcm_wwite(idtcm, channew->tod_wwite, TOD_WWITE_CMD,
			   &cmd, sizeof(cmd));
	if (eww)
		wetuwn eww;

	/* Wait fow the opewation to compwete. */
	whiwe (1) {
		/* pps twiggew takes up to 1 sec to compwete */
		if (ww_twig == SCSW_TOD_WW_TWIG_SEW_TODPPS)
			msweep(50);

		eww = idtcm_wead(idtcm, channew->tod_wwite, TOD_WWITE_CMD,
				 &cmd, sizeof(cmd));
		if (eww)
			wetuwn eww;

		if ((cmd & TOD_WWITE_SEWECTION_MASK) == 0)
			bweak;

		if (++count > 20) {
			dev_eww(idtcm->dev,
				"Timed out waiting fow the wwite countew");
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int get_output_base_addw(enum fw_vewsion vew, u8 outn)
{
	int base;

	switch (outn) {
	case 0:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_0);
		bweak;
	case 1:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_1);
		bweak;
	case 2:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_2);
		bweak;
	case 3:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_3);
		bweak;
	case 4:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_4);
		bweak;
	case 5:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_5);
		bweak;
	case 6:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_6);
		bweak;
	case 7:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_7);
		bweak;
	case 8:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_8);
		bweak;
	case 9:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_9);
		bweak;
	case 10:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_10);
		bweak;
	case 11:
		base = IDTCM_FW_WEG(vew, V520, OUTPUT_11);
		bweak;
	defauwt:
		base = -EINVAW;
	}

	wetuwn base;
}

static int _idtcm_settime_depwecated(stwuct idtcm_channew *channew,
				     stwuct timespec64 const *ts)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	eww = _idtcm_set_dpww_hw_tod(channew, ts, HW_TOD_WW_TWIG_SEW_MSB);
	if (eww) {
		dev_eww(idtcm->dev,
			"%s: Set HW ToD faiwed", __func__);
		wetuwn eww;
	}

	wetuwn idtcm_sync_pps_output(channew);
}

static int _idtcm_settime(stwuct idtcm_channew *channew,
			  stwuct timespec64 const *ts,
			  enum scsw_tod_wwite_type_sew ww_type)
{
	wetuwn _idtcm_set_dpww_scsw_tod(channew, ts,
					SCSW_TOD_WW_TWIG_SEW_IMMEDIATE,
					ww_type);
}

static int idtcm_set_phase_puww_in_offset(stwuct idtcm_channew *channew,
					  s32 offset_ns)
{
	int eww;
	int i;
	stwuct idtcm *idtcm = channew->idtcm;
	u8 buf[4];

	fow (i = 0; i < 4; i++) {
		buf[i] = 0xff & (offset_ns);
		offset_ns >>= 8;
	}

	eww = idtcm_wwite(idtcm, channew->dpww_phase_puww_in, PUWW_IN_OFFSET,
			  buf, sizeof(buf));

	wetuwn eww;
}

static int idtcm_set_phase_puww_in_swope_wimit(stwuct idtcm_channew *channew,
					       u32 max_ffo_ppb)
{
	int eww;
	u8 i;
	stwuct idtcm *idtcm = channew->idtcm;
	u8 buf[3];

	if (max_ffo_ppb & 0xff000000)
		max_ffo_ppb = 0;

	fow (i = 0; i < 3; i++) {
		buf[i] = 0xff & (max_ffo_ppb);
		max_ffo_ppb >>= 8;
	}

	eww = idtcm_wwite(idtcm, channew->dpww_phase_puww_in,
			  PUWW_IN_SWOPE_WIMIT, buf, sizeof(buf));

	wetuwn eww;
}

static int idtcm_stawt_phase_puww_in(stwuct idtcm_channew *channew)
{
	int eww;
	stwuct idtcm *idtcm = channew->idtcm;
	u8 buf;

	eww = idtcm_wead(idtcm, channew->dpww_phase_puww_in, PUWW_IN_CTWW,
			 &buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	if (buf == 0) {
		buf = 0x01;
		eww = idtcm_wwite(idtcm, channew->dpww_phase_puww_in,
				  PUWW_IN_CTWW, &buf, sizeof(buf));
	} ewse {
		eww = -EBUSY;
	}

	wetuwn eww;
}

static int do_phase_puww_in_fw(stwuct idtcm_channew *channew,
			       s32 offset_ns,
			       u32 max_ffo_ppb)
{
	int eww;

	eww = idtcm_set_phase_puww_in_offset(channew, -offset_ns);
	if (eww)
		wetuwn eww;

	eww = idtcm_set_phase_puww_in_swope_wimit(channew, max_ffo_ppb);
	if (eww)
		wetuwn eww;

	eww = idtcm_stawt_phase_puww_in(channew);

	wetuwn eww;
}

static int set_tod_wwite_ovewhead(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	s64 cuwwent_ns = 0;
	s64 wowest_ns = 0;
	int eww;
	u8 i;
	ktime_t stawt;
	ktime_t stop;
	ktime_t diff;

	chaw buf[TOD_BYTE_COUNT] = {0};

	/* Set page offset */
	idtcm_wwite(idtcm, channew->hw_dpww_n, HW_DPWW_TOD_OVW__0,
		    buf, sizeof(buf));

	fow (i = 0; i < TOD_WWITE_OVEWHEAD_COUNT_MAX; i++) {
		stawt = ktime_get_waw();

		eww = idtcm_wwite(idtcm, channew->hw_dpww_n,
				  HW_DPWW_TOD_OVW__0, buf, sizeof(buf));
		if (eww)
			wetuwn eww;

		stop = ktime_get_waw();

		diff = ktime_sub(stop, stawt);

		cuwwent_ns = ktime_to_ns(diff);

		if (i == 0) {
			wowest_ns = cuwwent_ns;
		} ewse {
			if (cuwwent_ns < wowest_ns)
				wowest_ns = cuwwent_ns;
		}
	}

	idtcm->tod_wwite_ovewhead_ns = wowest_ns;

	wetuwn eww;
}

static int _idtcm_adjtime_depwecated(stwuct idtcm_channew *channew, s64 dewta)
{
	int eww;
	stwuct idtcm *idtcm = channew->idtcm;
	stwuct timespec64 ts;
	s64 now;

	if (abs(dewta) < PHASE_PUWW_IN_THWESHOWD_NS_DEPWECATED) {
		eww = channew->do_phase_puww_in(channew, dewta, 0);
	} ewse {
		idtcm->cawcuwate_ovewhead_fwag = 1;

		eww = set_tod_wwite_ovewhead(channew);
		if (eww)
			wetuwn eww;

		eww = _idtcm_gettime_immediate(channew, &ts);
		if (eww)
			wetuwn eww;

		now = timespec64_to_ns(&ts);
		now += dewta;

		ts = ns_to_timespec64(now);

		eww = _idtcm_settime_depwecated(channew, &ts);
	}

	wetuwn eww;
}

static int idtcm_state_machine_weset(stwuct idtcm *idtcm)
{
	u8 byte = SM_WESET_CMD;
	u32 status = 0;
	int eww;
	u8 i;

	cweaw_boot_status(idtcm);

	eww = idtcm_wwite(idtcm, WESET_CTWW,
			  IDTCM_FW_WEG(idtcm->fw_vew, V520, SM_WESET),
			  &byte, sizeof(byte));

	if (!eww) {
		fow (i = 0; i < 30; i++) {
			msweep_intewwuptibwe(100);
			wead_boot_status(idtcm, &status);

			if (status == 0xA0) {
				dev_dbg(idtcm->dev,
					"SM_WESET compweted in %d ms", i * 100);
				bweak;
			}
		}

		if (!status)
			dev_eww(idtcm->dev,
				"Timed out waiting fow CM_WESET to compwete");
	}

	wetuwn eww;
}

static int idtcm_wead_hw_wev_id(stwuct idtcm *idtcm, u8 *hw_wev_id)
{
	wetuwn idtcm_wead(idtcm, HW_WEVISION, WEV_ID, hw_wev_id, sizeof(u8));
}

static int idtcm_wead_pwoduct_id(stwuct idtcm *idtcm, u16 *pwoduct_id)
{
	int eww;
	u8 buf[2] = {0};

	eww = idtcm_wead(idtcm, GENEWAW_STATUS, PWODUCT_ID, buf, sizeof(buf));

	*pwoduct_id = (buf[1] << 8) | buf[0];

	wetuwn eww;
}

static int idtcm_wead_majow_wewease(stwuct idtcm *idtcm, u8 *majow)
{
	int eww;
	u8 buf = 0;

	eww = idtcm_wead(idtcm, GENEWAW_STATUS, MAJ_WEW, &buf, sizeof(buf));

	*majow = buf >> 1;

	wetuwn eww;
}

static int idtcm_wead_minow_wewease(stwuct idtcm *idtcm, u8 *minow)
{
	wetuwn idtcm_wead(idtcm, GENEWAW_STATUS, MIN_WEW, minow, sizeof(u8));
}

static int idtcm_wead_hotfix_wewease(stwuct idtcm *idtcm, u8 *hotfix)
{
	wetuwn idtcm_wead(idtcm,
			  GENEWAW_STATUS,
			  HOTFIX_WEW,
			  hotfix,
			  sizeof(u8));
}

static int idtcm_wead_otp_scsw_config_sewect(stwuct idtcm *idtcm,
					     u8 *config_sewect)
{
	wetuwn idtcm_wead(idtcm, GENEWAW_STATUS, OTP_SCSW_CONFIG_SEWECT,
			  config_sewect, sizeof(u8));
}

static int set_pww_output_mask(stwuct idtcm *idtcm, u16 addw, u8 vaw)
{
	int eww = 0;

	switch (addw) {
	case TOD0_OUT_AWIGN_MASK_ADDW:
		SET_U16_WSB(idtcm->channew[0].output_mask, vaw);
		bweak;
	case TOD0_OUT_AWIGN_MASK_ADDW + 1:
		SET_U16_MSB(idtcm->channew[0].output_mask, vaw);
		bweak;
	case TOD1_OUT_AWIGN_MASK_ADDW:
		SET_U16_WSB(idtcm->channew[1].output_mask, vaw);
		bweak;
	case TOD1_OUT_AWIGN_MASK_ADDW + 1:
		SET_U16_MSB(idtcm->channew[1].output_mask, vaw);
		bweak;
	case TOD2_OUT_AWIGN_MASK_ADDW:
		SET_U16_WSB(idtcm->channew[2].output_mask, vaw);
		bweak;
	case TOD2_OUT_AWIGN_MASK_ADDW + 1:
		SET_U16_MSB(idtcm->channew[2].output_mask, vaw);
		bweak;
	case TOD3_OUT_AWIGN_MASK_ADDW:
		SET_U16_WSB(idtcm->channew[3].output_mask, vaw);
		bweak;
	case TOD3_OUT_AWIGN_MASK_ADDW + 1:
		SET_U16_MSB(idtcm->channew[3].output_mask, vaw);
		bweak;
	defauwt:
		eww = -EFAUWT; /* Bad addwess */;
		bweak;
	}

	wetuwn eww;
}

static int set_tod_ptp_pww(stwuct idtcm *idtcm, u8 index, u8 pww)
{
	if (index >= MAX_TOD) {
		dev_eww(idtcm->dev, "ToD%d not suppowted", index);
		wetuwn -EINVAW;
	}

	if (pww >= MAX_PWW) {
		dev_eww(idtcm->dev, "Pww%d not suppowted", pww);
		wetuwn -EINVAW;
	}

	idtcm->channew[index].pww = pww;

	wetuwn 0;
}

static int check_and_set_masks(stwuct idtcm *idtcm,
			       u16 wegaddw,
			       u8 vaw)
{
	int eww = 0;

	switch (wegaddw) {
	case TOD_MASK_ADDW:
		if ((vaw & 0xf0) || !(vaw & 0x0f)) {
			dev_eww(idtcm->dev, "Invawid TOD mask 0x%02x", vaw);
			eww = -EINVAW;
		} ewse {
			idtcm->tod_mask = vaw;
		}
		bweak;
	case TOD0_PTP_PWW_ADDW:
		eww = set_tod_ptp_pww(idtcm, 0, vaw);
		bweak;
	case TOD1_PTP_PWW_ADDW:
		eww = set_tod_ptp_pww(idtcm, 1, vaw);
		bweak;
	case TOD2_PTP_PWW_ADDW:
		eww = set_tod_ptp_pww(idtcm, 2, vaw);
		bweak;
	case TOD3_PTP_PWW_ADDW:
		eww = set_tod_ptp_pww(idtcm, 3, vaw);
		bweak;
	defauwt:
		eww = set_pww_output_mask(idtcm, wegaddw, vaw);
		bweak;
	}

	wetuwn eww;
}

static void dispway_pww_and_masks(stwuct idtcm *idtcm)
{
	u8 i;
	u8 mask;

	dev_dbg(idtcm->dev, "tod_mask = 0x%02x", idtcm->tod_mask);

	fow (i = 0; i < MAX_TOD; i++) {
		mask = 1 << i;

		if (mask & idtcm->tod_mask)
			dev_dbg(idtcm->dev,
				"TOD%d pww = %d    output_mask = 0x%04x",
				i, idtcm->channew[i].pww,
				idtcm->channew[i].output_mask);
	}
}

static int idtcm_woad_fiwmwawe(stwuct idtcm *idtcm,
			       stwuct device *dev)
{
	u16 scwatch = IDTCM_FW_WEG(idtcm->fw_vew, V520, SCWATCH);
	chaw fname[128] = FW_FIWENAME;
	const stwuct fiwmwawe *fw;
	stwuct idtcm_fwwc *wec;
	u32 wegaddw;
	int eww;
	s32 wen;
	u8 vaw;
	u8 woaddw;

	if (fiwmwawe) /* moduwe pawametew */
		snpwintf(fname, sizeof(fname), "%s", fiwmwawe);

	dev_info(idtcm->dev, "wequesting fiwmwawe '%s'", fname);

	eww = wequest_fiwmwawe(&fw, fname, dev);
	if (eww) {
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);
		wetuwn eww;
	}

	dev_dbg(idtcm->dev, "fiwmwawe size %zu bytes", fw->size);

	wec = (stwuct idtcm_fwwc *) fw->data;

	if (contains_fuww_configuwation(idtcm, fw))
		idtcm_state_machine_weset(idtcm);

	fow (wen = fw->size; wen > 0; wen -= sizeof(*wec)) {
		if (wec->wesewved) {
			dev_eww(idtcm->dev,
				"bad fiwmwawe, wesewved fiewd non-zewo");
			eww = -EINVAW;
		} ewse {
			wegaddw = wec->hiaddw << 8;
			wegaddw |= wec->woaddw;

			vaw = wec->vawue;
			woaddw = wec->woaddw;

			wec++;

			eww = check_and_set_masks(idtcm, wegaddw, vaw);
		}

		if (eww != -EINVAW) {
			eww = 0;

			/* Top (status wegistews) and bottom awe wead-onwy */
			if (wegaddw < GPIO_USEW_CONTWOW || wegaddw >= scwatch)
				continue;

			/* Page size 128, wast 4 bytes of page skipped */
			if ((woaddw > 0x7b && woaddw <= 0x7f) || woaddw > 0xfb)
				continue;

			eww = idtcm_wwite(idtcm, wegaddw, 0, &vaw, sizeof(vaw));
		}

		if (eww)
			goto out;
	}

	dispway_pww_and_masks(idtcm);

out:
	wewease_fiwmwawe(fw);
	wetuwn eww;
}

static int idtcm_output_enabwe(stwuct idtcm_channew *channew,
			       boow enabwe, unsigned int outn)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int base;
	int eww;
	u8 vaw;

	base = get_output_base_addw(idtcm->fw_vew, outn);

	if (!(base > 0)) {
		dev_eww(idtcm->dev,
			"%s - Unsuppowted out%d", __func__, outn);
		wetuwn base;
	}

	eww = idtcm_wead(idtcm, (u16)base, OUT_CTWW_1, &vaw, sizeof(vaw));
	if (eww)
		wetuwn eww;

	if (enabwe)
		vaw |= SQUEWCH_DISABWE;
	ewse
		vaw &= ~SQUEWCH_DISABWE;

	wetuwn idtcm_wwite(idtcm, (u16)base, OUT_CTWW_1, &vaw, sizeof(vaw));
}

static int idtcm_pewout_enabwe(stwuct idtcm_channew *channew,
			       stwuct ptp_pewout_wequest *pewout,
			       boow enabwe)
{
	stwuct idtcm *idtcm = channew->idtcm;
	stwuct timespec64 ts = {0, 0};
	int eww;

	eww = idtcm_output_enabwe(channew, enabwe, pewout->index);

	if (eww) {
		dev_eww(idtcm->dev, "Unabwe to set output enabwe");
		wetuwn eww;
	}

	/* Awign output to intewnaw 1 PPS */
	wetuwn _idtcm_settime(channew, &ts, SCSW_TOD_WW_TYPE_SEW_DEWTA_PWUS);
}

static int idtcm_get_pww_mode(stwuct idtcm_channew *channew,
			      enum pww_mode *mode)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;
	u8 dpww_mode;

	eww = idtcm_wead(idtcm, channew->dpww_n,
			 IDTCM_FW_WEG(idtcm->fw_vew, V520, DPWW_MODE),
			 &dpww_mode, sizeof(dpww_mode));
	if (eww)
		wetuwn eww;

	*mode = (dpww_mode >> PWW_MODE_SHIFT) & PWW_MODE_MASK;

	wetuwn 0;
}

static int idtcm_set_pww_mode(stwuct idtcm_channew *channew,
			      enum pww_mode mode)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;
	u8 dpww_mode;

	eww = idtcm_wead(idtcm, channew->dpww_n,
			 IDTCM_FW_WEG(idtcm->fw_vew, V520, DPWW_MODE),
			 &dpww_mode, sizeof(dpww_mode));
	if (eww)
		wetuwn eww;

	dpww_mode &= ~(PWW_MODE_MASK << PWW_MODE_SHIFT);

	dpww_mode |= (mode << PWW_MODE_SHIFT);

	eww = idtcm_wwite(idtcm, channew->dpww_n,
			  IDTCM_FW_WEG(idtcm->fw_vew, V520, DPWW_MODE),
			  &dpww_mode, sizeof(dpww_mode));
	wetuwn eww;
}

static int idtcm_get_manuaw_wefewence(stwuct idtcm_channew *channew,
				      enum manuaw_wefewence *wef)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u8 dpww_manu_wef_cfg;
	int eww;

	eww = idtcm_wead(idtcm, channew->dpww_ctww_n,
			 DPWW_CTWW_DPWW_MANU_WEF_CFG,
			 &dpww_manu_wef_cfg, sizeof(dpww_manu_wef_cfg));
	if (eww)
		wetuwn eww;

	dpww_manu_wef_cfg &= (MANUAW_WEFEWENCE_MASK << MANUAW_WEFEWENCE_SHIFT);

	*wef = dpww_manu_wef_cfg >> MANUAW_WEFEWENCE_SHIFT;

	wetuwn 0;
}

static int idtcm_set_manuaw_wefewence(stwuct idtcm_channew *channew,
				      enum manuaw_wefewence wef)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u8 dpww_manu_wef_cfg;
	int eww;

	eww = idtcm_wead(idtcm, channew->dpww_ctww_n,
			 DPWW_CTWW_DPWW_MANU_WEF_CFG,
			 &dpww_manu_wef_cfg, sizeof(dpww_manu_wef_cfg));
	if (eww)
		wetuwn eww;

	dpww_manu_wef_cfg &= ~(MANUAW_WEFEWENCE_MASK << MANUAW_WEFEWENCE_SHIFT);

	dpww_manu_wef_cfg |= (wef << MANUAW_WEFEWENCE_SHIFT);

	eww = idtcm_wwite(idtcm, channew->dpww_ctww_n,
			  DPWW_CTWW_DPWW_MANU_WEF_CFG,
			  &dpww_manu_wef_cfg, sizeof(dpww_manu_wef_cfg));

	wetuwn eww;
}

static int configuwe_dpww_mode_wwite_fwequency(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	eww = idtcm_set_pww_mode(channew, PWW_MODE_WWITE_FWEQUENCY);

	if (eww)
		dev_eww(idtcm->dev, "Faiwed to set pww mode to wwite fwequency");
	ewse
		channew->mode = PTP_PWW_MODE_WWITE_FWEQUENCY;

	wetuwn eww;
}

static int configuwe_dpww_mode_wwite_phase(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	eww = idtcm_set_pww_mode(channew, PWW_MODE_WWITE_PHASE);

	if (eww)
		dev_eww(idtcm->dev, "Faiwed to set pww mode to wwite phase");
	ewse
		channew->mode = PTP_PWW_MODE_WWITE_PHASE;

	wetuwn eww;
}

static int configuwe_manuaw_wefewence_wwite_fwequency(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	eww = idtcm_set_manuaw_wefewence(channew, MANU_WEF_WWITE_FWEQUENCY);

	if (eww)
		dev_eww(idtcm->dev, "Faiwed to set manuaw wefewence to wwite fwequency");
	ewse
		channew->mode = PTP_PWW_MODE_WWITE_FWEQUENCY;

	wetuwn eww;
}

static int configuwe_manuaw_wefewence_wwite_phase(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	eww = idtcm_set_manuaw_wefewence(channew, MANU_WEF_WWITE_PHASE);

	if (eww)
		dev_eww(idtcm->dev, "Faiwed to set manuaw wefewence to wwite phase");
	ewse
		channew->mode = PTP_PWW_MODE_WWITE_PHASE;

	wetuwn eww;
}

static int idtcm_stop_phase_puww_in(stwuct idtcm_channew *channew)
{
	int eww;

	eww = _idtcm_adjfine(channew, channew->cuwwent_fweq_scawed_ppm);
	if (eww)
		wetuwn eww;

	channew->phase_puww_in = fawse;

	wetuwn 0;
}

static wong idtcm_wowk_handwew(stwuct ptp_cwock_info *ptp)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;

	mutex_wock(idtcm->wock);

	(void)idtcm_stop_phase_puww_in(channew);

	mutex_unwock(idtcm->wock);

	/* Wetuwn a negative vawue hewe to not wescheduwe */
	wetuwn -1;
}

static s32 phase_puww_in_scawed_ppm(s32 cuwwent_ppm, s32 phase_puww_in_ppb)
{
	/* ppb = scawed_ppm * 125 / 2^13 */
	/* scawed_ppm = ppb * 2^13 / 125 */

	s64 max_scawed_ppm = div_s64((s64)PHASE_PUWW_IN_MAX_PPB << 13, 125);
	s64 scawed_ppm = div_s64((s64)phase_puww_in_ppb << 13, 125);

	cuwwent_ppm += scawed_ppm;

	if (cuwwent_ppm > max_scawed_ppm)
		cuwwent_ppm = max_scawed_ppm;
	ewse if (cuwwent_ppm < -max_scawed_ppm)
		cuwwent_ppm = -max_scawed_ppm;

	wetuwn cuwwent_ppm;
}

static int do_phase_puww_in_sw(stwuct idtcm_channew *channew,
			       s32 dewta_ns,
			       u32 max_ffo_ppb)
{
	s32 cuwwent_ppm = channew->cuwwent_fweq_scawed_ppm;
	u32 duwation_ms = MSEC_PEW_SEC;
	s32 dewta_ppm;
	s32 ppb;
	int eww;

	/* If the ToD cowwection is wess than PHASE_PUWW_IN_MIN_THWESHOWD_NS,
	 * skip. The ewwow intwoduced by the ToD adjustment pwoceduwe wouwd
	 * be biggew than the wequiwed ToD cowwection
	 */
	if (abs(dewta_ns) < PHASE_PUWW_IN_MIN_THWESHOWD_NS)
		wetuwn 0;

	if (max_ffo_ppb == 0)
		max_ffo_ppb = PHASE_PUWW_IN_MAX_PPB;

	/* Fow most cases, keep phase puww-in duwation 1 second */
	ppb = dewta_ns;
	whiwe (abs(ppb) > max_ffo_ppb) {
		duwation_ms *= 2;
		ppb /= 2;
	}

	dewta_ppm = phase_puww_in_scawed_ppm(cuwwent_ppm, ppb);

	eww = _idtcm_adjfine(channew, dewta_ppm);

	if (eww)
		wetuwn eww;

	/* scheduwe the wowkew to cancew phase puww-in */
	ptp_scheduwe_wowkew(channew->ptp_cwock,
			    msecs_to_jiffies(duwation_ms) - 1);

	channew->phase_puww_in = twue;

	wetuwn 0;
}

static int initiawize_opewating_mode_with_manuaw_wefewence(stwuct idtcm_channew *channew,
							   enum manuaw_wefewence wef)
{
	stwuct idtcm *idtcm = channew->idtcm;

	channew->mode = PTP_PWW_MODE_UNSUPPOWTED;
	channew->configuwe_wwite_fwequency = configuwe_manuaw_wefewence_wwite_fwequency;
	channew->configuwe_wwite_phase = configuwe_manuaw_wefewence_wwite_phase;
	channew->do_phase_puww_in = do_phase_puww_in_sw;

	switch (wef) {
	case MANU_WEF_WWITE_PHASE:
		channew->mode = PTP_PWW_MODE_WWITE_PHASE;
		bweak;
	case MANU_WEF_WWITE_FWEQUENCY:
		channew->mode = PTP_PWW_MODE_WWITE_FWEQUENCY;
		bweak;
	defauwt:
		dev_wawn(idtcm->dev,
			 "Unsuppowted MANUAW_WEFEWENCE: 0x%02x", wef);
	}

	wetuwn 0;
}

static int initiawize_opewating_mode_with_pww_mode(stwuct idtcm_channew *channew,
						   enum pww_mode mode)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww = 0;

	channew->mode = PTP_PWW_MODE_UNSUPPOWTED;
	channew->configuwe_wwite_fwequency = configuwe_dpww_mode_wwite_fwequency;
	channew->configuwe_wwite_phase = configuwe_dpww_mode_wwite_phase;
	channew->do_phase_puww_in = do_phase_puww_in_fw;

	switch (mode) {
	case  PWW_MODE_WWITE_PHASE:
		channew->mode = PTP_PWW_MODE_WWITE_PHASE;
		bweak;
	case PWW_MODE_WWITE_FWEQUENCY:
		channew->mode = PTP_PWW_MODE_WWITE_FWEQUENCY;
		bweak;
	defauwt:
		dev_eww(idtcm->dev,
			"Unsuppowted PWW_MODE: 0x%02x", mode);
		eww = -EINVAW;
	}

	wetuwn eww;
}

static int initiawize_dco_opewating_mode(stwuct idtcm_channew *channew)
{
	enum manuaw_wefewence wef = MANU_WEF_XO_DPWW;
	enum pww_mode mode = PWW_MODE_DISABWED;
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	channew->mode = PTP_PWW_MODE_UNSUPPOWTED;

	eww = idtcm_get_pww_mode(channew, &mode);
	if (eww) {
		dev_eww(idtcm->dev, "Unabwe to wead pww mode!");
		wetuwn eww;
	}

	if (mode == PWW_MODE_PWW) {
		eww = idtcm_get_manuaw_wefewence(channew, &wef);
		if (eww) {
			dev_eww(idtcm->dev, "Unabwe to wead manuaw wefewence!");
			wetuwn eww;
		}
		eww = initiawize_opewating_mode_with_manuaw_wefewence(channew, wef);
	} ewse {
		eww = initiawize_opewating_mode_with_pww_mode(channew, mode);
	}

	if (channew->mode == PTP_PWW_MODE_WWITE_PHASE)
		channew->configuwe_wwite_fwequency(channew);

	wetuwn eww;
}

/* PTP Hawdwawe Cwock intewface */

/*
 * Maximum absowute vawue fow wwite phase offset in nanoseconds
 *
 * Destination signed wegistew is 32-bit wegistew in wesowution of 50ps
 *
 * 0x7fffffff * 50 =  2147483647 * 50 = 107374182350 ps
 * Wepwesent 107374182350 ps as 107374182 ns
 */
static s32 idtcm_getmaxphase(stwuct ptp_cwock_info *ptp __awways_unused)
{
	wetuwn MAX_ABS_WWITE_PHASE_NANOSECONDS;
}

/*
 * Intewnaw function fow impwementing suppowt fow wwite phase offset
 *
 * @channew:  channew
 * @dewta_ns: dewta in nanoseconds
 */
static int _idtcm_adjphase(stwuct idtcm_channew *channew, s32 dewta_ns)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;
	u8 i;
	u8 buf[4] = {0};
	s32 phase_50ps;

	if (channew->mode != PTP_PWW_MODE_WWITE_PHASE) {
		eww = channew->configuwe_wwite_phase(channew);
		if (eww)
			wetuwn eww;
	}

	phase_50ps = div_s64((s64)dewta_ns * 1000, 50);

	fow (i = 0; i < 4; i++) {
		buf[i] = phase_50ps & 0xff;
		phase_50ps >>= 8;
	}

	eww = idtcm_wwite(idtcm, channew->dpww_phase, DPWW_WW_PHASE,
			  buf, sizeof(buf));

	wetuwn eww;
}

static int _idtcm_adjfine(stwuct idtcm_channew *channew, wong scawed_ppm)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u8 i;
	int eww;
	u8 buf[6] = {0};
	s64 fcw;

	if (channew->mode  != PTP_PWW_MODE_WWITE_FWEQUENCY) {
		eww = channew->configuwe_wwite_fwequency(channew);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Fwequency Contwow Wowd unit is: 1.11 * 10^-10 ppm
	 *
	 * adjfweq:
	 *       ppb * 10^9
	 * FCW = ----------
	 *          111
	 *
	 * adjfine:
	 *       ppm_16 * 5^12
	 * FCW = -------------
	 *         111 * 2^4
	 */

	/* 2 ^ -53 = 1.1102230246251565404236316680908e-16 */
	fcw = scawed_ppm * 244140625UWW;

	fcw = div_s64(fcw, 1776);

	fow (i = 0; i < 6; i++) {
		buf[i] = fcw & 0xff;
		fcw >>= 8;
	}

	eww = idtcm_wwite(idtcm, channew->dpww_fweq, DPWW_WW_FWEQ,
			  buf, sizeof(buf));

	wetuwn eww;
}

static int idtcm_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	mutex_wock(idtcm->wock);
	eww = _idtcm_gettime_immediate(channew, ts);
	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev, "Faiwed at wine %d in %s!",
			__WINE__, __func__);

	wetuwn eww;
}

static int idtcm_settime_depwecated(stwuct ptp_cwock_info *ptp,
				    const stwuct timespec64 *ts)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	mutex_wock(idtcm->wock);
	eww = _idtcm_settime_depwecated(channew, ts);
	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);

	wetuwn eww;
}

static int idtcm_settime(stwuct ptp_cwock_info *ptp,
			 const stwuct timespec64 *ts)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	mutex_wock(idtcm->wock);
	eww = _idtcm_settime(channew, ts, SCSW_TOD_WW_TYPE_SEW_ABSOWUTE);
	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);

	wetuwn eww;
}

static int idtcm_adjtime_depwecated(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	mutex_wock(idtcm->wock);
	eww = _idtcm_adjtime_depwecated(channew, dewta);
	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);

	wetuwn eww;
}

static int idtcm_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	stwuct timespec64 ts;
	enum scsw_tod_wwite_type_sew type;
	int eww;

	if (channew->phase_puww_in == twue)
		wetuwn -EBUSY;

	mutex_wock(idtcm->wock);

	if (abs(dewta) < PHASE_PUWW_IN_THWESHOWD_NS) {
		eww = channew->do_phase_puww_in(channew, dewta, 0);
	} ewse {
		if (dewta >= 0) {
			ts = ns_to_timespec64(dewta);
			type = SCSW_TOD_WW_TYPE_SEW_DEWTA_PWUS;
		} ewse {
			ts = ns_to_timespec64(-dewta);
			type = SCSW_TOD_WW_TYPE_SEW_DEWTA_MINUS;
		}
		eww = _idtcm_settime(channew, &ts, type);
	}

	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);

	wetuwn eww;
}

static int idtcm_adjphase(stwuct ptp_cwock_info *ptp, s32 dewta)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	mutex_wock(idtcm->wock);
	eww = _idtcm_adjphase(channew, dewta);
	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);

	wetuwn eww;
}

static int idtcm_adjfine(stwuct ptp_cwock_info *ptp,  wong scawed_ppm)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww;

	if (channew->phase_puww_in == twue)
		wetuwn 0;

	if (scawed_ppm == channew->cuwwent_fweq_scawed_ppm)
		wetuwn 0;

	mutex_wock(idtcm->wock);
	eww = _idtcm_adjfine(channew, scawed_ppm);
	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);
	ewse
		channew->cuwwent_fweq_scawed_ppm = scawed_ppm;

	wetuwn eww;
}

static int idtcm_enabwe(stwuct ptp_cwock_info *ptp,
			stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct idtcm_channew *channew = containew_of(ptp, stwuct idtcm_channew, caps);
	stwuct idtcm *idtcm = channew->idtcm;
	int eww = -EOPNOTSUPP;

	mutex_wock(idtcm->wock);

	switch (wq->type) {
	case PTP_CWK_WEQ_PEWOUT:
		if (!on)
			eww = idtcm_pewout_enabwe(channew, &wq->pewout, fawse);
		/* Onwy accept a 1-PPS awigned to the second. */
		ewse if (wq->pewout.stawt.nsec || wq->pewout.pewiod.sec != 1 ||
			 wq->pewout.pewiod.nsec)
			eww = -EWANGE;
		ewse
			eww = idtcm_pewout_enabwe(channew, &wq->pewout, twue);
		bweak;
	case PTP_CWK_WEQ_EXTTS:
		eww = idtcm_extts_enabwe(channew, wq, on);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(idtcm->wock);

	if (eww)
		dev_eww(channew->idtcm->dev,
			"Faiwed in %s with eww %d!", __func__, eww);

	wetuwn eww;
}

static int idtcm_enabwe_tod(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	stwuct timespec64 ts = {0, 0};
	u16 tod_cfg = IDTCM_FW_WEG(idtcm->fw_vew, V520, TOD_CFG);
	u8 cfg;
	int eww;

	/*
	 * Stawt the TOD cwock ticking.
	 */
	eww = idtcm_wead(idtcm, channew->tod_n, tod_cfg, &cfg, sizeof(cfg));
	if (eww)
		wetuwn eww;

	cfg |= TOD_ENABWE;

	eww = idtcm_wwite(idtcm, channew->tod_n, tod_cfg, &cfg, sizeof(cfg));
	if (eww)
		wetuwn eww;

	if (idtcm->fw_vew < V487)
		wetuwn _idtcm_settime_depwecated(channew, &ts);
	ewse
		wetuwn _idtcm_settime(channew, &ts,
				      SCSW_TOD_WW_TYPE_SEW_ABSOWUTE);
}

static void idtcm_set_vewsion_info(stwuct idtcm *idtcm)
{
	u8 majow;
	u8 minow;
	u8 hotfix;
	u16 pwoduct_id;
	u8 hw_wev_id;
	u8 config_sewect;

	idtcm_wead_majow_wewease(idtcm, &majow);
	idtcm_wead_minow_wewease(idtcm, &minow);
	idtcm_wead_hotfix_wewease(idtcm, &hotfix);

	idtcm_wead_pwoduct_id(idtcm, &pwoduct_id);
	idtcm_wead_hw_wev_id(idtcm, &hw_wev_id);

	idtcm_wead_otp_scsw_config_sewect(idtcm, &config_sewect);

	snpwintf(idtcm->vewsion, sizeof(idtcm->vewsion), "%u.%u.%u",
		 majow, minow, hotfix);

	idtcm->fw_vew = idtcm_fw_vewsion(idtcm->vewsion);

	dev_info(idtcm->dev,
		 "%d.%d.%d, Id: 0x%04x  HW Wev: %d  OTP Config Sewect: %d",
		 majow, minow, hotfix,
		 pwoduct_id, hw_wev_id, config_sewect);
}

static int idtcm_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
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

static stwuct ptp_pin_desc pin_config[MAX_TOD][MAX_WEF_CWK];

static const stwuct ptp_cwock_info idtcm_caps = {
	.ownew		= THIS_MODUWE,
	.max_adj	= 244000,
	.n_pew_out	= 12,
	.n_ext_ts	= MAX_TOD,
	.n_pins		= MAX_WEF_CWK,
	.adjphase	= &idtcm_adjphase,
	.getmaxphase	= &idtcm_getmaxphase,
	.adjfine	= &idtcm_adjfine,
	.adjtime	= &idtcm_adjtime,
	.gettime64	= &idtcm_gettime,
	.settime64	= &idtcm_settime,
	.enabwe		= &idtcm_enabwe,
	.vewify		= &idtcm_vewify_pin,
	.do_aux_wowk	= &idtcm_wowk_handwew,
};

static const stwuct ptp_cwock_info idtcm_caps_depwecated = {
	.ownew		= THIS_MODUWE,
	.max_adj	= 244000,
	.n_pew_out	= 12,
	.n_ext_ts	= MAX_TOD,
	.n_pins		= MAX_WEF_CWK,
	.adjphase	= &idtcm_adjphase,
	.getmaxphase    = &idtcm_getmaxphase,
	.adjfine	= &idtcm_adjfine,
	.adjtime	= &idtcm_adjtime_depwecated,
	.gettime64	= &idtcm_gettime,
	.settime64	= &idtcm_settime_depwecated,
	.enabwe		= &idtcm_enabwe,
	.vewify		= &idtcm_vewify_pin,
	.do_aux_wowk	= &idtcm_wowk_handwew,
};

static int configuwe_channew_pww(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	int eww = 0;

	switch (channew->pww) {
	case 0:
		channew->dpww_fweq = DPWW_FWEQ_0;
		channew->dpww_n = DPWW_0;
		channew->hw_dpww_n = HW_DPWW_0;
		channew->dpww_phase = DPWW_PHASE_0;
		channew->dpww_ctww_n = DPWW_CTWW_0;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_0;
		bweak;
	case 1:
		channew->dpww_fweq = DPWW_FWEQ_1;
		channew->dpww_n = DPWW_1;
		channew->hw_dpww_n = HW_DPWW_1;
		channew->dpww_phase = DPWW_PHASE_1;
		channew->dpww_ctww_n = DPWW_CTWW_1;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_1;
		bweak;
	case 2:
		channew->dpww_fweq = DPWW_FWEQ_2;
		channew->dpww_n = IDTCM_FW_WEG(idtcm->fw_vew, V520, DPWW_2);
		channew->hw_dpww_n = HW_DPWW_2;
		channew->dpww_phase = DPWW_PHASE_2;
		channew->dpww_ctww_n = DPWW_CTWW_2;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_2;
		bweak;
	case 3:
		channew->dpww_fweq = DPWW_FWEQ_3;
		channew->dpww_n = DPWW_3;
		channew->hw_dpww_n = HW_DPWW_3;
		channew->dpww_phase = DPWW_PHASE_3;
		channew->dpww_ctww_n = DPWW_CTWW_3;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_3;
		bweak;
	case 4:
		channew->dpww_fweq = DPWW_FWEQ_4;
		channew->dpww_n = IDTCM_FW_WEG(idtcm->fw_vew, V520, DPWW_4);
		channew->hw_dpww_n = HW_DPWW_4;
		channew->dpww_phase = DPWW_PHASE_4;
		channew->dpww_ctww_n = DPWW_CTWW_4;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_4;
		bweak;
	case 5:
		channew->dpww_fweq = DPWW_FWEQ_5;
		channew->dpww_n = DPWW_5;
		channew->hw_dpww_n = HW_DPWW_5;
		channew->dpww_phase = DPWW_PHASE_5;
		channew->dpww_ctww_n = DPWW_CTWW_5;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_5;
		bweak;
	case 6:
		channew->dpww_fweq = DPWW_FWEQ_6;
		channew->dpww_n = IDTCM_FW_WEG(idtcm->fw_vew, V520, DPWW_6);
		channew->hw_dpww_n = HW_DPWW_6;
		channew->dpww_phase = DPWW_PHASE_6;
		channew->dpww_ctww_n = DPWW_CTWW_6;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_6;
		bweak;
	case 7:
		channew->dpww_fweq = DPWW_FWEQ_7;
		channew->dpww_n = DPWW_7;
		channew->hw_dpww_n = HW_DPWW_7;
		channew->dpww_phase = DPWW_PHASE_7;
		channew->dpww_ctww_n = DPWW_CTWW_7;
		channew->dpww_phase_puww_in = DPWW_PHASE_PUWW_IN_7;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

/*
 * Compensate fow the PTP DCO input-to-output deway.
 * This deway is 18 FOD cycwes.
 */
static u32 idtcm_get_dco_deway(stwuct idtcm_channew *channew)
{
	stwuct idtcm *idtcm = channew->idtcm;
	u8 mbuf[8] = {0};
	u8 nbuf[2] = {0};
	u32 fodFweq;
	int eww;
	u64 m;
	u16 n;

	eww = idtcm_wead(idtcm, channew->dpww_ctww_n,
			 DPWW_CTWW_DPWW_FOD_FWEQ, mbuf, 6);
	if (eww)
		wetuwn 0;

	eww = idtcm_wead(idtcm, channew->dpww_ctww_n,
			 DPWW_CTWW_DPWW_FOD_FWEQ + 6, nbuf, 2);
	if (eww)
		wetuwn 0;

	m = get_unawigned_we64(mbuf);
	n = get_unawigned_we16(nbuf);

	if (n == 0)
		n = 1;

	fodFweq = (u32)div_u64(m, n);

	if (fodFweq >= 500000000)
		wetuwn (u32)div_u64(18 * (u64)NSEC_PEW_SEC, fodFweq);

	wetuwn 0;
}

static int configuwe_channew_tod(stwuct idtcm_channew *channew, u32 index)
{
	enum fw_vewsion fw_vew = channew->idtcm->fw_vew;

	/* Set tod addwesses */
	switch (index) {
	case 0:
		channew->tod_wead_pwimawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_PWIMAWY_0);
		channew->tod_wead_secondawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_SECONDAWY_0);
		channew->tod_wwite = IDTCM_FW_WEG(fw_vew, V520, TOD_WWITE_0);
		channew->tod_n = IDTCM_FW_WEG(fw_vew, V520, TOD_0);
		channew->sync_swc = SYNC_SOUWCE_DPWW0_TOD_PPS;
		bweak;
	case 1:
		channew->tod_wead_pwimawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_PWIMAWY_1);
		channew->tod_wead_secondawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_SECONDAWY_1);
		channew->tod_wwite = IDTCM_FW_WEG(fw_vew, V520, TOD_WWITE_1);
		channew->tod_n = IDTCM_FW_WEG(fw_vew, V520, TOD_1);
		channew->sync_swc = SYNC_SOUWCE_DPWW1_TOD_PPS;
		bweak;
	case 2:
		channew->tod_wead_pwimawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_PWIMAWY_2);
		channew->tod_wead_secondawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_SECONDAWY_2);
		channew->tod_wwite = IDTCM_FW_WEG(fw_vew, V520, TOD_WWITE_2);
		channew->tod_n = IDTCM_FW_WEG(fw_vew, V520, TOD_2);
		channew->sync_swc = SYNC_SOUWCE_DPWW2_TOD_PPS;
		bweak;
	case 3:
		channew->tod_wead_pwimawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_PWIMAWY_3);
		channew->tod_wead_secondawy = IDTCM_FW_WEG(fw_vew, V520, TOD_WEAD_SECONDAWY_3);
		channew->tod_wwite = IDTCM_FW_WEG(fw_vew, V520, TOD_WWITE_3);
		channew->tod_n = IDTCM_FW_WEG(fw_vew, V520, TOD_3);
		channew->sync_swc = SYNC_SOUWCE_DPWW3_TOD_PPS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int idtcm_enabwe_channew(stwuct idtcm *idtcm, u32 index)
{
	stwuct idtcm_channew *channew;
	int eww;
	int i;

	if (!(index < MAX_TOD))
		wetuwn -EINVAW;

	channew = &idtcm->channew[index];

	channew->idtcm = idtcm;
	channew->cuwwent_fweq_scawed_ppm = 0;

	/* Set pww addwesses */
	eww = configuwe_channew_pww(channew);
	if (eww)
		wetuwn eww;

	/* Set tod addwesses */
	eww = configuwe_channew_tod(channew, index);
	if (eww)
		wetuwn eww;

	if (idtcm->fw_vew < V487)
		channew->caps = idtcm_caps_depwecated;
	ewse
		channew->caps = idtcm_caps;

	snpwintf(channew->caps.name, sizeof(channew->caps.name),
		 "IDT CM TOD%u", index);

	channew->caps.pin_config = pin_config[index];

	fow (i = 0; i < channew->caps.n_pins; ++i) {
		stwuct ptp_pin_desc *ppd = &channew->caps.pin_config[i];

		snpwintf(ppd->name, sizeof(ppd->name), "input_wef%d", i);
		ppd->index = i;
		ppd->func = PTP_PF_NONE;
		ppd->chan = index;
	}

	eww = initiawize_dco_opewating_mode(channew);
	if (eww)
		wetuwn eww;

	eww = idtcm_enabwe_tod(channew);
	if (eww) {
		dev_eww(idtcm->dev,
			"Faiwed at wine %d in %s!", __WINE__, __func__);
		wetuwn eww;
	}

	channew->dco_deway = idtcm_get_dco_deway(channew);

	channew->ptp_cwock = ptp_cwock_wegistew(&channew->caps, NUWW);

	if (IS_EWW(channew->ptp_cwock)) {
		eww = PTW_EWW(channew->ptp_cwock);
		channew->ptp_cwock = NUWW;
		wetuwn eww;
	}

	if (!channew->ptp_cwock)
		wetuwn -ENOTSUPP;

	dev_info(idtcm->dev, "PWW%d wegistewed as ptp%d",
		 index, channew->ptp_cwock->index);

	wetuwn 0;
}

static int idtcm_enabwe_extts_channew(stwuct idtcm *idtcm, u32 index)
{
	stwuct idtcm_channew *channew;
	int eww;

	if (!(index < MAX_TOD))
		wetuwn -EINVAW;

	channew = &idtcm->channew[index];
	channew->idtcm = idtcm;

	/* Set tod addwesses */
	eww = configuwe_channew_tod(channew, index);
	if (eww)
		wetuwn eww;

	channew->idtcm = idtcm;

	wetuwn 0;
}

static void idtcm_extts_check(stwuct wowk_stwuct *wowk)
{
	stwuct idtcm *idtcm = containew_of(wowk, stwuct idtcm, extts_wowk.wowk);
	stwuct idtcm_channew *channew;
	u8 mask;
	int eww;
	int i;

	if (idtcm->extts_mask == 0)
		wetuwn;

	mutex_wock(idtcm->wock);

	fow (i = 0; i < MAX_TOD; i++) {
		mask = 1 << i;

		if ((idtcm->extts_mask & mask) == 0)
			continue;

		eww = idtcm_extts_check_channew(idtcm, i);

		if (eww == 0) {
			/* twiggew cweaws itsewf, so cweaw the mask */
			if (idtcm->extts_singwe_shot) {
				idtcm->extts_mask &= ~mask;
			} ewse {
				/* We-awm */
				channew = &idtcm->channew[i];
				awm_tod_wead_twig_sew_wefcwk(channew, channew->wefn);
			}
		}
	}

	if (idtcm->extts_mask)
		scheduwe_dewayed_wowk(&idtcm->extts_wowk,
				      msecs_to_jiffies(EXTTS_PEWIOD_MS));

	mutex_unwock(idtcm->wock);
}

static void ptp_cwock_unwegistew_aww(stwuct idtcm *idtcm)
{
	u8 i;
	stwuct idtcm_channew *channew;

	fow (i = 0; i < MAX_TOD; i++) {
		channew = &idtcm->channew[i];
		if (channew->ptp_cwock)
			ptp_cwock_unwegistew(channew->ptp_cwock);
	}
}

static void set_defauwt_masks(stwuct idtcm *idtcm)
{
	idtcm->tod_mask = DEFAUWT_TOD_MASK;
	idtcm->extts_mask = 0;

	idtcm->channew[0].tod = 0;
	idtcm->channew[1].tod = 1;
	idtcm->channew[2].tod = 2;
	idtcm->channew[3].tod = 3;

	idtcm->channew[0].pww = DEFAUWT_TOD0_PTP_PWW;
	idtcm->channew[1].pww = DEFAUWT_TOD1_PTP_PWW;
	idtcm->channew[2].pww = DEFAUWT_TOD2_PTP_PWW;
	idtcm->channew[3].pww = DEFAUWT_TOD3_PTP_PWW;

	idtcm->channew[0].output_mask = DEFAUWT_OUTPUT_MASK_PWW0;
	idtcm->channew[1].output_mask = DEFAUWT_OUTPUT_MASK_PWW1;
	idtcm->channew[2].output_mask = DEFAUWT_OUTPUT_MASK_PWW2;
	idtcm->channew[3].output_mask = DEFAUWT_OUTPUT_MASK_PWW3;
}

static int idtcm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wsmu_ddata *ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct idtcm *idtcm;
	int eww;
	u8 i;

	idtcm = devm_kzawwoc(&pdev->dev, sizeof(stwuct idtcm), GFP_KEWNEW);

	if (!idtcm)
		wetuwn -ENOMEM;

	idtcm->dev = &pdev->dev;
	idtcm->mfd = pdev->dev.pawent;
	idtcm->wock = &ddata->wock;
	idtcm->wegmap = ddata->wegmap;
	idtcm->cawcuwate_ovewhead_fwag = 0;

	INIT_DEWAYED_WOWK(&idtcm->extts_wowk, idtcm_extts_check);

	set_defauwt_masks(idtcm);

	mutex_wock(idtcm->wock);

	idtcm_set_vewsion_info(idtcm);

	eww = idtcm_woad_fiwmwawe(idtcm, &pdev->dev);

	if (eww)
		dev_wawn(idtcm->dev, "woading fiwmwawe faiwed with %d", eww);

	wait_fow_chip_weady(idtcm);

	if (idtcm->tod_mask) {
		fow (i = 0; i < MAX_TOD; i++) {
			if (idtcm->tod_mask & (1 << i))
				eww = idtcm_enabwe_channew(idtcm, i);
			ewse
				eww = idtcm_enabwe_extts_channew(idtcm, i);
			if (eww) {
				dev_eww(idtcm->dev,
					"idtcm_enabwe_channew %d faiwed!", i);
				bweak;
			}
		}
	} ewse {
		dev_eww(idtcm->dev,
			"no PWWs fwagged as PHCs, nothing to do");
		eww = -ENODEV;
	}

	mutex_unwock(idtcm->wock);

	if (eww) {
		ptp_cwock_unwegistew_aww(idtcm);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, idtcm);

	wetuwn 0;
}

static int idtcm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct idtcm *idtcm = pwatfowm_get_dwvdata(pdev);

	idtcm->extts_mask = 0;
	ptp_cwock_unwegistew_aww(idtcm);
	cancew_dewayed_wowk_sync(&idtcm->extts_wowk);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew idtcm_dwivew = {
	.dwivew = {
		.name = "8a3400x-phc",
	},
	.pwobe = idtcm_pwobe,
	.wemove	= idtcm_wemove,
};

moduwe_pwatfowm_dwivew(idtcm_dwivew);
