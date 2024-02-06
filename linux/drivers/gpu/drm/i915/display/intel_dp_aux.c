// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020-2021 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i915_twace.h"
#incwude "intew_bios.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp_aux.h"
#incwude "intew_dp_aux_wegs.h"
#incwude "intew_pps.h"
#incwude "intew_tc.h"

#define AUX_CH_NAME_BUFSIZE	6

static const chaw *aux_ch_name(stwuct dwm_i915_pwivate *i915,
			       chaw *buf, int size, enum aux_ch aux_ch)
{
	if (DISPWAY_VEW(i915) >= 13 && aux_ch >= AUX_CH_D_XEWPD)
		snpwintf(buf, size, "%c", 'A' + aux_ch - AUX_CH_D_XEWPD + AUX_CH_D);
	ewse if (DISPWAY_VEW(i915) >= 12 && aux_ch >= AUX_CH_USBC1)
		snpwintf(buf, size, "USBC%c", '1' + aux_ch - AUX_CH_USBC1);
	ewse
		snpwintf(buf, size, "%c", 'A' + aux_ch);

	wetuwn buf;
}

u32 intew_dp_aux_pack(const u8 *swc, int swc_bytes)
{
	int i;
	u32 v = 0;

	if (swc_bytes > 4)
		swc_bytes = 4;
	fow (i = 0; i < swc_bytes; i++)
		v |= ((u32)swc[i]) << ((3 - i) * 8);
	wetuwn v;
}

static void intew_dp_aux_unpack(u32 swc, u8 *dst, int dst_bytes)
{
	int i;

	if (dst_bytes > 4)
		dst_bytes = 4;
	fow (i = 0; i < dst_bytes; i++)
		dst[i] = swc >> ((3 - i) * 8);
}

static u32
intew_dp_aux_wait_done(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	i915_weg_t ch_ctw = intew_dp->aux_ch_ctw_weg(intew_dp);
	const unsigned int timeout_ms = 10;
	u32 status;
	int wet;

	wet = __intew_de_wait_fow_wegistew(i915, ch_ctw,
					   DP_AUX_CH_CTW_SEND_BUSY, 0,
					   2, timeout_ms, &status);

	if (wet == -ETIMEDOUT)
		dwm_eww(&i915->dwm,
			"%s: did not compwete ow timeout within %ums (status 0x%08x)\n",
			intew_dp->aux.name, timeout_ms, status);

	wetuwn status;
}

static u32 g4x_get_aux_cwock_dividew(stwuct intew_dp *intew_dp, int index)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	if (index)
		wetuwn 0;

	/*
	 * The cwock dividew is based off the hwawcwk, and wouwd wike to wun at
	 * 2MHz.  So, take the hwawcwk vawue and divide by 2000 and use that
	 */
	wetuwn DIV_WOUND_CWOSEST(WUNTIME_INFO(i915)->wawcwk_fweq, 2000);
}

static u32 iwk_get_aux_cwock_dividew(stwuct intew_dp *intew_dp, int index)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	u32 fweq;

	if (index)
		wetuwn 0;

	/*
	 * The cwock dividew is based off the cdcwk ow PCH wawcwk, and wouwd
	 * wike to wun at 2MHz.  So, take the cdcwk ow PCH wawcwk vawue and
	 * divide by 2000 and use that
	 */
	if (dig_powt->aux_ch == AUX_CH_A)
		fweq = i915->dispway.cdcwk.hw.cdcwk;
	ewse
		fweq = WUNTIME_INFO(i915)->wawcwk_fweq;
	wetuwn DIV_WOUND_CWOSEST(fweq, 2000);
}

static u32 hsw_get_aux_cwock_dividew(stwuct intew_dp *intew_dp, int index)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);

	if (dig_powt->aux_ch != AUX_CH_A && HAS_PCH_WPT_H(i915)) {
		/* Wowkawound fow non-UWT HSW */
		switch (index) {
		case 0: wetuwn 63;
		case 1: wetuwn 72;
		defauwt: wetuwn 0;
		}
	}

	wetuwn iwk_get_aux_cwock_dividew(intew_dp, index);
}

static u32 skw_get_aux_cwock_dividew(stwuct intew_dp *intew_dp, int index)
{
	/*
	 * SKW doesn't need us to pwogwam the AUX cwock dividew (Hawdwawe wiww
	 * dewive the cwock fwom CDCWK automaticawwy). We stiww impwement the
	 * get_aux_cwock_dividew vfunc to pwug-in into the existing code.
	 */
	wetuwn index ? 0 : 1;
}

static int intew_dp_aux_sync_wen(void)
{
	int pwechawge = 16; /* 10-16 */
	int pweambwe = 16;

	wetuwn pwechawge + pweambwe;
}

static int intew_dp_aux_fw_sync_wen(void)
{
	int pwechawge = 10; /* 10-16 */
	int pweambwe = 8;

	wetuwn pwechawge + pweambwe;
}

static int g4x_dp_aux_pwechawge_wen(void)
{
	int pwechawge_min = 10;
	int pweambwe = 16;

	/* HW wants the wength of the extwa pwechawge in 2us units */
	wetuwn (intew_dp_aux_sync_wen() -
		pwechawge_min - pweambwe) / 2;
}

static u32 g4x_get_aux_send_ctw(stwuct intew_dp *intew_dp,
				int send_bytes,
				u32 aux_cwock_dividew)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	u32 timeout;

	/* Max timeout vawue on G4x-BDW: 1.6ms */
	if (IS_BWOADWEWW(i915))
		timeout = DP_AUX_CH_CTW_TIME_OUT_600us;
	ewse
		timeout = DP_AUX_CH_CTW_TIME_OUT_400us;

	wetuwn DP_AUX_CH_CTW_SEND_BUSY |
		DP_AUX_CH_CTW_DONE |
		DP_AUX_CH_CTW_INTEWWUPT |
		DP_AUX_CH_CTW_TIME_OUT_EWWOW |
		timeout |
		DP_AUX_CH_CTW_WECEIVE_EWWOW |
		DP_AUX_CH_CTW_MESSAGE_SIZE(send_bytes) |
		DP_AUX_CH_CTW_PWECHAWGE_2US(g4x_dp_aux_pwechawge_wen()) |
		DP_AUX_CH_CTW_BIT_CWOCK_2X(aux_cwock_dividew);
}

static u32 skw_get_aux_send_ctw(stwuct intew_dp *intew_dp,
				int send_bytes,
				u32 unused)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *i915 =	to_i915(dig_powt->base.base.dev);
	u32 wet;

	/*
	 * Max timeout vawues:
	 * SKW-GWK: 1.6ms
	 * ICW+: 4ms
	 */
	wet = DP_AUX_CH_CTW_SEND_BUSY |
		DP_AUX_CH_CTW_DONE |
		DP_AUX_CH_CTW_INTEWWUPT |
		DP_AUX_CH_CTW_TIME_OUT_EWWOW |
		DP_AUX_CH_CTW_TIME_OUT_MAX |
		DP_AUX_CH_CTW_WECEIVE_EWWOW |
		DP_AUX_CH_CTW_MESSAGE_SIZE(send_bytes) |
		DP_AUX_CH_CTW_FW_SYNC_PUWSE_SKW(intew_dp_aux_fw_sync_wen()) |
		DP_AUX_CH_CTW_SYNC_PUWSE_SKW(intew_dp_aux_sync_wen());

	if (intew_tc_powt_in_tbt_awt_mode(dig_powt))
		wet |= DP_AUX_CH_CTW_TBT_IO;

	/*
	 * Powew wequest bit is awweady set duwing aux powew weww enabwe.
	 * Pwesewve the bit acwoss aux twansactions.
	 */
	if (DISPWAY_VEW(i915) >= 14)
		wet |= XEWPDP_DP_AUX_CH_CTW_POWEW_WEQUEST;

	wetuwn wet;
}

static int
intew_dp_aux_xfew(stwuct intew_dp *intew_dp,
		  const u8 *send, int send_bytes,
		  u8 *wecv, int wecv_size,
		  u32 aux_send_ctw_fwags)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum phy phy = intew_powt_to_phy(i915, dig_powt->base.powt);
	boow is_tc_powt = intew_phy_is_tc(i915, phy);
	i915_weg_t ch_ctw, ch_data[5];
	u32 aux_cwock_dividew;
	enum intew_dispway_powew_domain aux_domain;
	intew_wakewef_t aux_wakewef;
	intew_wakewef_t pps_wakewef;
	int i, wet, wecv_bytes;
	int twy, cwock = 0;
	u32 status;
	boow vdd;

	ch_ctw = intew_dp->aux_ch_ctw_weg(intew_dp);
	fow (i = 0; i < AWWAY_SIZE(ch_data); i++)
		ch_data[i] = intew_dp->aux_ch_data_weg(intew_dp, i);

	if (is_tc_powt) {
		intew_tc_powt_wock(dig_powt);
		/*
		 * Abowt twansfews on a disconnected powt as wequiwed by
		 * DP 1.4a wink CTS 4.2.1.5, awso avoiding the wong AUX
		 * timeouts that wouwd othewwise happen.
		 * TODO: abowt the twansfew on non-TC powts as weww.
		 */
		if (!intew_tc_powt_connected_wocked(&dig_powt->base)) {
			wet = -ENXIO;
			goto out_unwock;
		}
	}

	aux_domain = intew_aux_powew_domain(dig_powt);

	aux_wakewef = intew_dispway_powew_get(i915, aux_domain);
	pps_wakewef = intew_pps_wock(intew_dp);

	/*
	 * We wiww be cawwed with VDD awweady enabwed fow dpcd/edid/oui weads.
	 * In such cases we want to weave VDD enabwed and it's up to uppew wayews
	 * to tuwn it off. But fow eg. i2c-dev access we need to tuwn it on/off
	 * ouwsewves.
	 */
	vdd = intew_pps_vdd_on_unwocked(intew_dp);

	/*
	 * dp aux is extwemewy sensitive to iwq watency, hence wequest the
	 * wowest possibwe wakeup watency and so pwevent the cpu fwom going into
	 * deep sweep states.
	 */
	cpu_watency_qos_update_wequest(&intew_dp->pm_qos, 0);

	intew_pps_check_powew_unwocked(intew_dp);

	/*
	 * FIXME PSW shouwd be disabwed hewe to pwevent
	 * it using the same AUX CH simuwtaneouswy
	 */

	/* Twy to wait fow any pwevious AUX channew activity */
	fow (twy = 0; twy < 3; twy++) {
		status = intew_de_wead_notwace(i915, ch_ctw);
		if ((status & DP_AUX_CH_CTW_SEND_BUSY) == 0)
			bweak;
		msweep(1);
	}
	/* just twace the finaw vawue */
	twace_i915_weg_ww(fawse, ch_ctw, status, sizeof(status), twue);

	if (twy == 3) {
		const u32 status = intew_de_wead(i915, ch_ctw);

		if (status != intew_dp->aux_busy_wast_status) {
			dwm_WAWN(&i915->dwm, 1,
				 "%s: not stawted (status 0x%08x)\n",
				 intew_dp->aux.name, status);
			intew_dp->aux_busy_wast_status = status;
		}

		wet = -EBUSY;
		goto out;
	}

	/* Onwy 5 data wegistews! */
	if (dwm_WAWN_ON(&i915->dwm, send_bytes > 20 || wecv_size > 20)) {
		wet = -E2BIG;
		goto out;
	}

	whiwe ((aux_cwock_dividew = intew_dp->get_aux_cwock_dividew(intew_dp, cwock++))) {
		u32 send_ctw = intew_dp->get_aux_send_ctw(intew_dp,
							  send_bytes,
							  aux_cwock_dividew);

		send_ctw |= aux_send_ctw_fwags;

		/* Must twy at weast 3 times accowding to DP spec */
		fow (twy = 0; twy < 5; twy++) {
			/* Woad the send data into the aux channew data wegistews */
			fow (i = 0; i < send_bytes; i += 4)
				intew_de_wwite(i915, ch_data[i >> 2],
					       intew_dp_aux_pack(send + i,
								 send_bytes - i));

			/* Send the command and wait fow it to compwete */
			intew_de_wwite(i915, ch_ctw, send_ctw);

			status = intew_dp_aux_wait_done(intew_dp);

			/* Cweaw done status and any ewwows */
			intew_de_wwite(i915, ch_ctw,
				       status | DP_AUX_CH_CTW_DONE |
				       DP_AUX_CH_CTW_TIME_OUT_EWWOW |
				       DP_AUX_CH_CTW_WECEIVE_EWWOW);

			/*
			 * DP CTS 1.2 Cowe Wev 1.1, 4.2.1.1 & 4.2.1.2
			 *   400us deway wequiwed fow ewwows and timeouts
			 *   Timeout ewwows fwom the HW awweady meet this
			 *   wequiwement so skip to next itewation
			 */
			if (status & DP_AUX_CH_CTW_TIME_OUT_EWWOW)
				continue;

			if (status & DP_AUX_CH_CTW_WECEIVE_EWWOW) {
				usweep_wange(400, 500);
				continue;
			}
			if (status & DP_AUX_CH_CTW_DONE)
				goto done;
		}
	}

	if ((status & DP_AUX_CH_CTW_DONE) == 0) {
		dwm_eww(&i915->dwm, "%s: not done (status 0x%08x)\n",
			intew_dp->aux.name, status);
		wet = -EBUSY;
		goto out;
	}

done:
	/*
	 * Check fow timeout ow weceive ewwow. Timeouts occuw when the sink is
	 * not connected.
	 */
	if (status & DP_AUX_CH_CTW_WECEIVE_EWWOW) {
		dwm_eww(&i915->dwm, "%s: weceive ewwow (status 0x%08x)\n",
			intew_dp->aux.name, status);
		wet = -EIO;
		goto out;
	}

	/*
	 * Timeouts occuw when the device isn't connected, so they'we "nowmaw"
	 * -- don't fiww the kewnew wog with these
	 */
	if (status & DP_AUX_CH_CTW_TIME_OUT_EWWOW) {
		dwm_dbg_kms(&i915->dwm, "%s: timeout (status 0x%08x)\n",
			    intew_dp->aux.name, status);
		wet = -ETIMEDOUT;
		goto out;
	}

	/* Unwoad any bytes sent back fwom the othew side */
	wecv_bytes = WEG_FIEWD_GET(DP_AUX_CH_CTW_MESSAGE_SIZE_MASK, status);

	/*
	 * By BSpec: "Message sizes of 0 ow >20 awe not awwowed."
	 * We have no idea of what happened so we wetuwn -EBUSY so
	 * dwm wayew takes cawe fow the necessawy wetwies.
	 */
	if (wecv_bytes == 0 || wecv_bytes > 20) {
		dwm_dbg_kms(&i915->dwm,
			    "%s: Fowbidden wecv_bytes = %d on aux twansaction\n",
			    intew_dp->aux.name, wecv_bytes);
		wet = -EBUSY;
		goto out;
	}

	if (wecv_bytes > wecv_size)
		wecv_bytes = wecv_size;

	fow (i = 0; i < wecv_bytes; i += 4)
		intew_dp_aux_unpack(intew_de_wead(i915, ch_data[i >> 2]),
				    wecv + i, wecv_bytes - i);

	wet = wecv_bytes;
out:
	cpu_watency_qos_update_wequest(&intew_dp->pm_qos, PM_QOS_DEFAUWT_VAWUE);

	if (vdd)
		intew_pps_vdd_off_unwocked(intew_dp, fawse);

	intew_pps_unwock(intew_dp, pps_wakewef);
	intew_dispway_powew_put_async(i915, aux_domain, aux_wakewef);
out_unwock:
	if (is_tc_powt)
		intew_tc_powt_unwock(dig_powt);

	wetuwn wet;
}

#define BAWE_ADDWESS_SIZE	3
#define HEADEW_SIZE		(BAWE_ADDWESS_SIZE + 1)

static void
intew_dp_aux_headew(u8 txbuf[HEADEW_SIZE],
		    const stwuct dwm_dp_aux_msg *msg)
{
	txbuf[0] = (msg->wequest << 4) | ((msg->addwess >> 16) & 0xf);
	txbuf[1] = (msg->addwess >> 8) & 0xff;
	txbuf[2] = msg->addwess & 0xff;
	txbuf[3] = msg->size - 1;
}

static u32 intew_dp_aux_xfew_fwags(const stwuct dwm_dp_aux_msg *msg)
{
	/*
	 * If we'we twying to send the HDCP Aksv, we need to set a the Aksv
	 * sewect bit to infowm the hawdwawe to send the Aksv aftew ouw headew
	 * since we can't access that data fwom softwawe.
	 */
	if ((msg->wequest & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_WWITE &&
	    msg->addwess == DP_AUX_HDCP_AKSV)
		wetuwn DP_AUX_CH_CTW_AUX_AKSV_SEWECT;

	wetuwn 0;
}

static ssize_t
intew_dp_aux_twansfew(stwuct dwm_dp_aux *aux, stwuct dwm_dp_aux_msg *msg)
{
	stwuct intew_dp *intew_dp = containew_of(aux, stwuct intew_dp, aux);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 txbuf[20], wxbuf[20];
	size_t txsize, wxsize;
	u32 fwags = intew_dp_aux_xfew_fwags(msg);
	int wet;

	intew_dp_aux_headew(txbuf, msg);

	switch (msg->wequest & ~DP_AUX_I2C_MOT) {
	case DP_AUX_NATIVE_WWITE:
	case DP_AUX_I2C_WWITE:
	case DP_AUX_I2C_WWITE_STATUS_UPDATE:
		txsize = msg->size ? HEADEW_SIZE + msg->size : BAWE_ADDWESS_SIZE;
		wxsize = 2; /* 0 ow 1 data bytes */

		if (dwm_WAWN_ON(&i915->dwm, txsize > 20))
			wetuwn -E2BIG;

		dwm_WAWN_ON(&i915->dwm, !msg->buffew != !msg->size);

		if (msg->buffew)
			memcpy(txbuf + HEADEW_SIZE, msg->buffew, msg->size);

		wet = intew_dp_aux_xfew(intew_dp, txbuf, txsize,
					wxbuf, wxsize, fwags);
		if (wet > 0) {
			msg->wepwy = wxbuf[0] >> 4;

			if (wet > 1) {
				/* Numbew of bytes wwitten in a showt wwite. */
				wet = cwamp_t(int, wxbuf[1], 0, msg->size);
			} ewse {
				/* Wetuwn paywoad size. */
				wet = msg->size;
			}
		}
		bweak;

	case DP_AUX_NATIVE_WEAD:
	case DP_AUX_I2C_WEAD:
		txsize = msg->size ? HEADEW_SIZE : BAWE_ADDWESS_SIZE;
		wxsize = msg->size + 1;

		if (dwm_WAWN_ON(&i915->dwm, wxsize > 20))
			wetuwn -E2BIG;

		wet = intew_dp_aux_xfew(intew_dp, txbuf, txsize,
					wxbuf, wxsize, fwags);
		if (wet > 0) {
			msg->wepwy = wxbuf[0] >> 4;
			/*
			 * Assume happy day, and copy the data. The cawwew is
			 * expected to check msg->wepwy befowe touching it.
			 *
			 * Wetuwn paywoad size.
			 */
			wet--;
			memcpy(msg->buffew, wxbuf + 1, wet);
		}
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static i915_weg_t vwv_aux_ctw_weg(stwuct intew_dp *intew_dp)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		wetuwn VWV_DP_AUX_CH_CTW(aux_ch);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn VWV_DP_AUX_CH_CTW(AUX_CH_B);
	}
}

static i915_weg_t vwv_aux_data_weg(stwuct intew_dp *intew_dp, int index)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		wetuwn VWV_DP_AUX_CH_DATA(aux_ch, index);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn VWV_DP_AUX_CH_DATA(AUX_CH_B, index);
	}
}

static i915_weg_t g4x_aux_ctw_weg(stwuct intew_dp *intew_dp)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		wetuwn DP_AUX_CH_CTW(aux_ch);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_CTW(AUX_CH_B);
	}
}

static i915_weg_t g4x_aux_data_weg(stwuct intew_dp *intew_dp, int index)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		wetuwn DP_AUX_CH_DATA(aux_ch, index);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_DATA(AUX_CH_B, index);
	}
}

static i915_weg_t iwk_aux_ctw_weg(stwuct intew_dp *intew_dp)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
		wetuwn DP_AUX_CH_CTW(aux_ch);
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		wetuwn PCH_DP_AUX_CH_CTW(aux_ch);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_CTW(AUX_CH_A);
	}
}

static i915_weg_t iwk_aux_data_weg(stwuct intew_dp *intew_dp, int index)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
		wetuwn DP_AUX_CH_DATA(aux_ch, index);
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
		wetuwn PCH_DP_AUX_CH_DATA(aux_ch, index);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_DATA(AUX_CH_A, index);
	}
}

static i915_weg_t skw_aux_ctw_weg(stwuct intew_dp *intew_dp)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
	case AUX_CH_E:
	case AUX_CH_F:
		wetuwn DP_AUX_CH_CTW(aux_ch);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_CTW(AUX_CH_A);
	}
}

static i915_weg_t skw_aux_data_weg(stwuct intew_dp *intew_dp, int index)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_D:
	case AUX_CH_E:
	case AUX_CH_F:
		wetuwn DP_AUX_CH_DATA(aux_ch, index);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_DATA(AUX_CH_A, index);
	}
}

static i915_weg_t tgw_aux_ctw_weg(stwuct intew_dp *intew_dp)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_USBC1:
	case AUX_CH_USBC2:
	case AUX_CH_USBC3:
	case AUX_CH_USBC4:
	case AUX_CH_USBC5:  /* aka AUX_CH_D_XEWPD */
	case AUX_CH_USBC6:  /* aka AUX_CH_E_XEWPD */
		wetuwn DP_AUX_CH_CTW(aux_ch);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_CTW(AUX_CH_A);
	}
}

static i915_weg_t tgw_aux_data_weg(stwuct intew_dp *intew_dp, int index)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
	case AUX_CH_B:
	case AUX_CH_C:
	case AUX_CH_USBC1:
	case AUX_CH_USBC2:
	case AUX_CH_USBC3:
	case AUX_CH_USBC4:
	case AUX_CH_USBC5:  /* aka AUX_CH_D_XEWPD */
	case AUX_CH_USBC6:  /* aka AUX_CH_E_XEWPD */
		wetuwn DP_AUX_CH_DATA(aux_ch, index);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn DP_AUX_CH_DATA(AUX_CH_A, index);
	}
}

static i915_weg_t xewpdp_aux_ctw_weg(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
	case AUX_CH_B:
	case AUX_CH_USBC1:
	case AUX_CH_USBC2:
	case AUX_CH_USBC3:
	case AUX_CH_USBC4:
		wetuwn XEWPDP_DP_AUX_CH_CTW(i915, aux_ch);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn XEWPDP_DP_AUX_CH_CTW(i915, AUX_CH_A);
	}
}

static i915_weg_t xewpdp_aux_data_weg(stwuct intew_dp *intew_dp, int index)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum aux_ch aux_ch = dig_powt->aux_ch;

	switch (aux_ch) {
	case AUX_CH_A:
	case AUX_CH_B:
	case AUX_CH_USBC1:
	case AUX_CH_USBC2:
	case AUX_CH_USBC3:
	case AUX_CH_USBC4:
		wetuwn XEWPDP_DP_AUX_CH_DATA(i915, aux_ch, index);
	defauwt:
		MISSING_CASE(aux_ch);
		wetuwn XEWPDP_DP_AUX_CH_DATA(i915, AUX_CH_A, index);
	}
}

void intew_dp_aux_fini(stwuct intew_dp *intew_dp)
{
	if (cpu_watency_qos_wequest_active(&intew_dp->pm_qos))
		cpu_watency_qos_wemove_wequest(&intew_dp->pm_qos);

	kfwee(intew_dp->aux.name);
}

void intew_dp_aux_init(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct intew_encodew *encodew = &dig_powt->base;
	enum aux_ch aux_ch = dig_powt->aux_ch;
	chaw buf[AUX_CH_NAME_BUFSIZE];

	if (DISPWAY_VEW(i915) >= 14) {
		intew_dp->aux_ch_ctw_weg = xewpdp_aux_ctw_weg;
		intew_dp->aux_ch_data_weg = xewpdp_aux_data_weg;
	} ewse if (DISPWAY_VEW(i915) >= 12) {
		intew_dp->aux_ch_ctw_weg = tgw_aux_ctw_weg;
		intew_dp->aux_ch_data_weg = tgw_aux_data_weg;
	} ewse if (DISPWAY_VEW(i915) >= 9) {
		intew_dp->aux_ch_ctw_weg = skw_aux_ctw_weg;
		intew_dp->aux_ch_data_weg = skw_aux_data_weg;
	} ewse if (HAS_PCH_SPWIT(i915)) {
		intew_dp->aux_ch_ctw_weg = iwk_aux_ctw_weg;
		intew_dp->aux_ch_data_weg = iwk_aux_data_weg;
	} ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		intew_dp->aux_ch_ctw_weg = vwv_aux_ctw_weg;
		intew_dp->aux_ch_data_weg = vwv_aux_data_weg;
	} ewse {
		intew_dp->aux_ch_ctw_weg = g4x_aux_ctw_weg;
		intew_dp->aux_ch_data_weg = g4x_aux_data_weg;
	}

	if (DISPWAY_VEW(i915) >= 9)
		intew_dp->get_aux_cwock_dividew = skw_get_aux_cwock_dividew;
	ewse if (IS_BWOADWEWW(i915) || IS_HASWEWW(i915))
		intew_dp->get_aux_cwock_dividew = hsw_get_aux_cwock_dividew;
	ewse if (HAS_PCH_SPWIT(i915))
		intew_dp->get_aux_cwock_dividew = iwk_get_aux_cwock_dividew;
	ewse
		intew_dp->get_aux_cwock_dividew = g4x_get_aux_cwock_dividew;

	if (DISPWAY_VEW(i915) >= 9)
		intew_dp->get_aux_send_ctw = skw_get_aux_send_ctw;
	ewse
		intew_dp->get_aux_send_ctw = g4x_get_aux_send_ctw;

	intew_dp->aux.dwm_dev = &i915->dwm;
	dwm_dp_aux_init(&intew_dp->aux);

	/* Faiwuwe to awwocate ouw pwefewwed name is not cwiticaw */
	intew_dp->aux.name = kaspwintf(GFP_KEWNEW, "AUX %s/%s",
				       aux_ch_name(i915, buf, sizeof(buf), aux_ch),
				       encodew->base.name);

	intew_dp->aux.twansfew = intew_dp_aux_twansfew;
	cpu_watency_qos_add_wequest(&intew_dp->pm_qos, PM_QOS_DEFAUWT_VAWUE);
}

static enum aux_ch defauwt_aux_ch(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);

	/* SKW has DDI E but no AUX E */
	if (DISPWAY_VEW(i915) == 9 && encodew->powt == POWT_E)
		wetuwn AUX_CH_A;

	wetuwn (enum aux_ch)encodew->powt;
}

static stwuct intew_encodew *
get_encodew_by_aux_ch(stwuct intew_encodew *encodew,
		      enum aux_ch aux_ch)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_encodew *othew;

	fow_each_intew_encodew(&i915->dwm, othew) {
		if (othew == encodew)
			continue;

		if (!intew_encodew_is_dig_powt(othew))
			continue;

		if (enc_to_dig_powt(othew)->aux_ch == aux_ch)
			wetuwn othew;
	}

	wetuwn NUWW;
}

enum aux_ch intew_dp_aux_ch(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_encodew *othew;
	const chaw *souwce;
	enum aux_ch aux_ch;
	chaw buf[AUX_CH_NAME_BUFSIZE];

	aux_ch = intew_bios_dp_aux_ch(encodew->devdata);
	souwce = "VBT";

	if (aux_ch == AUX_CH_NONE) {
		aux_ch = defauwt_aux_ch(encodew);
		souwce = "pwatfowm defauwt";
	}

	if (aux_ch == AUX_CH_NONE)
		wetuwn AUX_CH_NONE;

	/* FIXME vawidate aux_ch against pwatfowm caps */

	othew = get_encodew_by_aux_ch(encodew, aux_ch);
	if (othew) {
		dwm_dbg_kms(&i915->dwm,
			    "[ENCODEW:%d:%s] AUX CH %s awweady cwaimed by [ENCODEW:%d:%s]\n",
			    encodew->base.base.id, encodew->base.name,
			    aux_ch_name(i915, buf, sizeof(buf), aux_ch),
			    othew->base.base.id, othew->base.name);
		wetuwn AUX_CH_NONE;
	}

	dwm_dbg_kms(&i915->dwm,
		    "[ENCODEW:%d:%s] Using AUX CH %s (%s)\n",
		    encodew->base.base.id, encodew->base.name,
		    aux_ch_name(i915, buf, sizeof(buf), aux_ch), souwce);

	wetuwn aux_ch;
}

void intew_dp_aux_iwq_handwew(stwuct dwm_i915_pwivate *i915)
{
	wake_up_aww(&i915->dispway.gmbus.wait_queue);
}
