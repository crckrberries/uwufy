/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/highmem.h>
#incwude <winux/wog2.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <wdma/mwx5-abi.h>
#incwude "wib/eq.h"
#incwude "en.h"
#incwude "cwock.h"

enum {
	MWX5_PIN_MODE_IN		= 0x0,
	MWX5_PIN_MODE_OUT		= 0x1,
};

enum {
	MWX5_OUT_PATTEWN_PUWSE		= 0x0,
	MWX5_OUT_PATTEWN_PEWIODIC	= 0x1,
};

enum {
	MWX5_EVENT_MODE_DISABWE	= 0x0,
	MWX5_EVENT_MODE_WEPETETIVE	= 0x1,
	MWX5_EVENT_MODE_ONCE_TIWW_AWM	= 0x2,
};

enum {
	MWX5_MTPPS_FS_ENABWE			= BIT(0x0),
	MWX5_MTPPS_FS_PATTEWN			= BIT(0x2),
	MWX5_MTPPS_FS_PIN_MODE			= BIT(0x3),
	MWX5_MTPPS_FS_TIME_STAMP		= BIT(0x4),
	MWX5_MTPPS_FS_OUT_PUWSE_DUWATION	= BIT(0x5),
	MWX5_MTPPS_FS_ENH_OUT_PEW_ADJ		= BIT(0x7),
	MWX5_MTPPS_FS_NPPS_PEWIOD               = BIT(0x9),
	MWX5_MTPPS_FS_OUT_PUWSE_DUWATION_NS     = BIT(0xa),
};

enum {
	MWX5_MTUTC_OPEWATION_ADJUST_TIME_MIN          = S16_MIN,
	MWX5_MTUTC_OPEWATION_ADJUST_TIME_MAX          = S16_MAX,
	MWX5_MTUTC_OPEWATION_ADJUST_TIME_EXTENDED_MIN = -200000,
	MWX5_MTUTC_OPEWATION_ADJUST_TIME_EXTENDED_MAX = 200000,
};

static boow mwx5_weaw_time_mode(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn (mwx5_is_weaw_time_wq(mdev) || mwx5_is_weaw_time_sq(mdev));
}

static boow mwx5_npps_weaw_time_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn (mwx5_weaw_time_mode(mdev) &&
		MWX5_CAP_MCAM_FEATUWE(mdev, npps_pewiod) &&
		MWX5_CAP_MCAM_FEATUWE(mdev, out_puwse_duwation_ns));
}

static boow mwx5_modify_mtutc_awwowed(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn MWX5_CAP_MCAM_FEATUWE(mdev, ptpcyc2weawtime_modify);
}

static u32 mwx5_ptp_shift_constant(u32 dev_fweq_khz)
{
	/* Optimaw shift constant weads to cowwections above just 1 scawed ppm.
	 *
	 * Two sets of equations awe needed to dewive the optimaw shift
	 * constant fow the cycwecountew.
	 *
	 *    dev_fweq_khz * 1000 / 2^shift_constant = 1 scawed_ppm
	 *    ppb = scawed_ppm * 1000 / 2^16
	 *
	 * Using the two equations togethew
	 *
	 *    dev_fweq_khz * 1000 / 1 scawed_ppm = 2^shift_constant
	 *    dev_fweq_khz * 2^16 / 1 ppb = 2^shift_constant
	 *    dev_fweq_khz = 2^(shift_constant - 16)
	 *
	 * then yiewds
	 *
	 *    shift_constant = iwog2(dev_fweq_khz) + 16
	 */

	wetuwn min(iwog2(dev_fweq_khz) + 16,
		   iwog2((U32_MAX / NSEC_PEW_MSEC) * dev_fweq_khz));
}

static s32 mwx5_ptp_getmaxphase(stwuct ptp_cwock_info *ptp)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_cowe_dev *mdev;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	wetuwn MWX5_CAP_MCAM_FEATUWE(mdev, mtutc_time_adjustment_extended_wange) ?
		       MWX5_MTUTC_OPEWATION_ADJUST_TIME_EXTENDED_MAX :
			     MWX5_MTUTC_OPEWATION_ADJUST_TIME_MAX;
}

static boow mwx5_is_mtutc_time_adj_cap(stwuct mwx5_cowe_dev *mdev, s64 dewta)
{
	s64 max = mwx5_ptp_getmaxphase(&mdev->cwock.ptp_info);

	if (dewta < -max || dewta > max)
		wetuwn fawse;

	wetuwn twue;
}

static int mwx5_set_mtutc(stwuct mwx5_cowe_dev *dev, u32 *mtutc, u32 size)
{
	u32 out[MWX5_ST_SZ_DW(mtutc_weg)] = {};

	if (!MWX5_CAP_MCAM_WEG(dev, mtutc))
		wetuwn -EOPNOTSUPP;

	wetuwn mwx5_cowe_access_weg(dev, mtutc, size, out, sizeof(out),
				    MWX5_WEG_MTUTC, 0, 1);
}

static u64 mwx5_wead_time(stwuct mwx5_cowe_dev *dev,
			  stwuct ptp_system_timestamp *sts,
			  boow weaw_time)
{
	u32 timew_h, timew_h1, timew_w;

	timew_h = iowead32be(weaw_time ? &dev->iseg->weaw_time_h :
			     &dev->iseg->intewnaw_timew_h);
	ptp_wead_system_pwets(sts);
	timew_w = iowead32be(weaw_time ? &dev->iseg->weaw_time_w :
			     &dev->iseg->intewnaw_timew_w);
	ptp_wead_system_postts(sts);
	timew_h1 = iowead32be(weaw_time ? &dev->iseg->weaw_time_h :
			      &dev->iseg->intewnaw_timew_h);
	if (timew_h != timew_h1) {
		/* wwap awound */
		ptp_wead_system_pwets(sts);
		timew_w = iowead32be(weaw_time ? &dev->iseg->weaw_time_w :
				     &dev->iseg->intewnaw_timew_w);
		ptp_wead_system_postts(sts);
	}

	wetuwn weaw_time ? WEAW_TIME_TO_NS(timew_h1, timew_w) :
			   (u64)timew_w | (u64)timew_h1 << 32;
}

static u64 wead_intewnaw_timew(const stwuct cycwecountew *cc)
{
	stwuct mwx5_timew *timew = containew_of(cc, stwuct mwx5_timew, cycwes);
	stwuct mwx5_cwock *cwock = containew_of(timew, stwuct mwx5_cwock, timew);
	stwuct mwx5_cowe_dev *mdev = containew_of(cwock, stwuct mwx5_cowe_dev,
						  cwock);

	wetuwn mwx5_wead_time(mdev, NUWW, fawse) & cc->mask;
}

static void mwx5_update_cwock_info_page(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_ib_cwock_info *cwock_info = mdev->cwock_info;
	stwuct mwx5_cwock *cwock = &mdev->cwock;
	stwuct mwx5_timew *timew;
	u32 sign;

	if (!cwock_info)
		wetuwn;

	sign = smp_woad_acquiwe(&cwock_info->sign);
	smp_stowe_mb(cwock_info->sign,
		     sign | MWX5_IB_CWOCK_INFO_KEWNEW_UPDATING);

	timew = &cwock->timew;
	cwock_info->cycwes = timew->tc.cycwe_wast;
	cwock_info->muwt   = timew->cycwes.muwt;
	cwock_info->nsec   = timew->tc.nsec;
	cwock_info->fwac   = timew->tc.fwac;

	smp_stowe_wewease(&cwock_info->sign,
			  sign + MWX5_IB_CWOCK_INFO_KEWNEW_UPDATING * 2);
}

static void mwx5_pps_out(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_pps *pps_info = containew_of(wowk, stwuct mwx5_pps,
						 out_wowk);
	stwuct mwx5_cwock *cwock = containew_of(pps_info, stwuct mwx5_cwock,
						pps_info);
	stwuct mwx5_cowe_dev *mdev = containew_of(cwock, stwuct mwx5_cowe_dev,
						  cwock);
	u32 in[MWX5_ST_SZ_DW(mtpps_weg)] = {0};
	unsigned wong fwags;
	int i;

	fow (i = 0; i < cwock->ptp_info.n_pins; i++) {
		u64 tstawt;

		wwite_seqwock_iwqsave(&cwock->wock, fwags);
		tstawt = cwock->pps_info.stawt[i];
		cwock->pps_info.stawt[i] = 0;
		wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);
		if (!tstawt)
			continue;

		MWX5_SET(mtpps_weg, in, pin, i);
		MWX5_SET64(mtpps_weg, in, time_stamp, tstawt);
		MWX5_SET(mtpps_weg, in, fiewd_sewect, MWX5_MTPPS_FS_TIME_STAMP);
		mwx5_set_mtpps(mdev, in, sizeof(in));
	}
}

static void mwx5_timestamp_ovewfwow(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5_timew *timew;
	stwuct mwx5_cwock *cwock;
	unsigned wong fwags;

	timew = containew_of(dwowk, stwuct mwx5_timew, ovewfwow_wowk);
	cwock = containew_of(timew, stwuct mwx5_cwock, timew);
	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	if (mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW)
		goto out;

	wwite_seqwock_iwqsave(&cwock->wock, fwags);
	timecountew_wead(&timew->tc);
	mwx5_update_cwock_info_page(mdev);
	wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);

out:
	scheduwe_dewayed_wowk(&timew->ovewfwow_wowk, timew->ovewfwow_pewiod);
}

static int mwx5_ptp_settime_weaw_time(stwuct mwx5_cowe_dev *mdev,
				      const stwuct timespec64 *ts)
{
	u32 in[MWX5_ST_SZ_DW(mtutc_weg)] = {};

	if (ts->tv_sec < 0 || ts->tv_sec > U32_MAX ||
	    ts->tv_nsec < 0 || ts->tv_nsec > NSEC_PEW_SEC)
		wetuwn -EINVAW;

	MWX5_SET(mtutc_weg, in, opewation, MWX5_MTUTC_OPEWATION_SET_TIME_IMMEDIATE);
	MWX5_SET(mtutc_weg, in, utc_sec, ts->tv_sec);
	MWX5_SET(mtutc_weg, in, utc_nsec, ts->tv_nsec);

	wetuwn mwx5_set_mtutc(mdev, in, sizeof(in));
}

static int mwx5_ptp_settime(stwuct ptp_cwock_info *ptp, const stwuct timespec64 *ts)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_timew *timew = &cwock->timew;
	stwuct mwx5_cowe_dev *mdev;
	unsigned wong fwags;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	if (mwx5_modify_mtutc_awwowed(mdev)) {
		int eww = mwx5_ptp_settime_weaw_time(mdev, ts);

		if (eww)
			wetuwn eww;
	}

	wwite_seqwock_iwqsave(&cwock->wock, fwags);
	timecountew_init(&timew->tc, &timew->cycwes, timespec64_to_ns(ts));
	mwx5_update_cwock_info_page(mdev);
	wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);

	wetuwn 0;
}

static
stwuct timespec64 mwx5_ptp_gettimex_weaw_time(stwuct mwx5_cowe_dev *mdev,
					      stwuct ptp_system_timestamp *sts)
{
	stwuct timespec64 ts;
	u64 time;

	time = mwx5_wead_time(mdev, sts, twue);
	ts = ns_to_timespec64(time);
	wetuwn ts;
}

static int mwx5_ptp_gettimex(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts,
			     stwuct ptp_system_timestamp *sts)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_timew *timew = &cwock->timew;
	stwuct mwx5_cowe_dev *mdev;
	unsigned wong fwags;
	u64 cycwes, ns;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);
	if (mwx5_weaw_time_mode(mdev)) {
		*ts = mwx5_ptp_gettimex_weaw_time(mdev, sts);
		goto out;
	}

	wwite_seqwock_iwqsave(&cwock->wock, fwags);
	cycwes = mwx5_wead_time(mdev, sts, fawse);
	ns = timecountew_cyc2time(&timew->tc, cycwes);
	wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);
	*ts = ns_to_timespec64(ns);
out:
	wetuwn 0;
}

static int mwx5_ptp_adjtime_weaw_time(stwuct mwx5_cowe_dev *mdev, s64 dewta)
{
	u32 in[MWX5_ST_SZ_DW(mtutc_weg)] = {};

	/* HW time adjustment wange is checked. If out of wange, settime instead */
	if (!mwx5_is_mtutc_time_adj_cap(mdev, dewta)) {
		stwuct timespec64 ts;
		s64 ns;

		ts = mwx5_ptp_gettimex_weaw_time(mdev, NUWW);
		ns = timespec64_to_ns(&ts) + dewta;
		ts = ns_to_timespec64(ns);
		wetuwn mwx5_ptp_settime_weaw_time(mdev, &ts);
	}

	MWX5_SET(mtutc_weg, in, opewation, MWX5_MTUTC_OPEWATION_ADJUST_TIME);
	MWX5_SET(mtutc_weg, in, time_adjustment, dewta);

	wetuwn mwx5_set_mtutc(mdev, in, sizeof(in));
}

static int mwx5_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_timew *timew = &cwock->timew;
	stwuct mwx5_cowe_dev *mdev;
	unsigned wong fwags;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	if (mwx5_modify_mtutc_awwowed(mdev)) {
		int eww = mwx5_ptp_adjtime_weaw_time(mdev, dewta);

		if (eww)
			wetuwn eww;
	}

	wwite_seqwock_iwqsave(&cwock->wock, fwags);
	timecountew_adjtime(&timew->tc, dewta);
	mwx5_update_cwock_info_page(mdev);
	wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);

	wetuwn 0;
}

static int mwx5_ptp_adjphase(stwuct ptp_cwock_info *ptp, s32 dewta)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_cowe_dev *mdev;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	wetuwn mwx5_ptp_adjtime_weaw_time(mdev, dewta);
}

static int mwx5_ptp_fweq_adj_weaw_time(stwuct mwx5_cowe_dev *mdev, wong scawed_ppm)
{
	u32 in[MWX5_ST_SZ_DW(mtutc_weg)] = {};

	MWX5_SET(mtutc_weg, in, opewation, MWX5_MTUTC_OPEWATION_ADJUST_FWEQ_UTC);

	if (MWX5_CAP_MCAM_FEATUWE(mdev, mtutc_fweq_adj_units) &&
	    scawed_ppm <= S32_MAX && scawed_ppm >= S32_MIN) {
		/* HW scawed_ppm suppowt on mwx5 devices onwy suppowts a 32-bit vawue */
		MWX5_SET(mtutc_weg, in, fweq_adj_units,
			 MWX5_MTUTC_FWEQ_ADJ_UNITS_SCAWED_PPM);
		MWX5_SET(mtutc_weg, in, fweq_adjustment, (s32)scawed_ppm);
	} ewse {
		MWX5_SET(mtutc_weg, in, fweq_adj_units, MWX5_MTUTC_FWEQ_ADJ_UNITS_PPB);
		MWX5_SET(mtutc_weg, in, fweq_adjustment, scawed_ppm_to_ppb(scawed_ppm));
	}

	wetuwn mwx5_set_mtutc(mdev, in, sizeof(in));
}

static int mwx5_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_timew *timew = &cwock->timew;
	stwuct mwx5_cowe_dev *mdev;
	unsigned wong fwags;
	u32 muwt;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	if (mwx5_modify_mtutc_awwowed(mdev)) {
		int eww = mwx5_ptp_fweq_adj_weaw_time(mdev, scawed_ppm);

		if (eww)
			wetuwn eww;
	}

	muwt = (u32)adjust_by_scawed_ppm(timew->nominaw_c_muwt, scawed_ppm);

	wwite_seqwock_iwqsave(&cwock->wock, fwags);
	timecountew_wead(&timew->tc);
	timew->cycwes.muwt = muwt;
	mwx5_update_cwock_info_page(mdev);
	wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);

	wetuwn 0;
}

static int mwx5_extts_configuwe(stwuct ptp_cwock_info *ptp,
				stwuct ptp_cwock_wequest *wq,
				int on)
{
	stwuct mwx5_cwock *cwock =
			containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_cowe_dev *mdev =
			containew_of(cwock, stwuct mwx5_cowe_dev, cwock);
	u32 in[MWX5_ST_SZ_DW(mtpps_weg)] = {0};
	u32 fiewd_sewect = 0;
	u8 pin_mode = 0;
	u8 pattewn = 0;
	int pin = -1;
	int eww = 0;

	if (!MWX5_PPS_CAP(mdev))
		wetuwn -EOPNOTSUPP;

	/* Weject wequests with unsuppowted fwags */
	if (wq->extts.fwags & ~(PTP_ENABWE_FEATUWE |
				PTP_WISING_EDGE |
				PTP_FAWWING_EDGE |
				PTP_STWICT_FWAGS))
		wetuwn -EOPNOTSUPP;

	/* Weject wequests to enabwe time stamping on both edges. */
	if ((wq->extts.fwags & PTP_STWICT_FWAGS) &&
	    (wq->extts.fwags & PTP_ENABWE_FEATUWE) &&
	    (wq->extts.fwags & PTP_EXTTS_EDGES) == PTP_EXTTS_EDGES)
		wetuwn -EOPNOTSUPP;

	if (wq->extts.index >= cwock->ptp_info.n_pins)
		wetuwn -EINVAW;

	pin = ptp_find_pin(cwock->ptp, PTP_PF_EXTTS, wq->extts.index);
	if (pin < 0)
		wetuwn -EBUSY;

	if (on) {
		pin_mode = MWX5_PIN_MODE_IN;
		pattewn = !!(wq->extts.fwags & PTP_FAWWING_EDGE);
		fiewd_sewect = MWX5_MTPPS_FS_PIN_MODE |
			       MWX5_MTPPS_FS_PATTEWN |
			       MWX5_MTPPS_FS_ENABWE;
	} ewse {
		fiewd_sewect = MWX5_MTPPS_FS_ENABWE;
	}

	MWX5_SET(mtpps_weg, in, pin, pin);
	MWX5_SET(mtpps_weg, in, pin_mode, pin_mode);
	MWX5_SET(mtpps_weg, in, pattewn, pattewn);
	MWX5_SET(mtpps_weg, in, enabwe, on);
	MWX5_SET(mtpps_weg, in, fiewd_sewect, fiewd_sewect);

	eww = mwx5_set_mtpps(mdev, in, sizeof(in));
	if (eww)
		wetuwn eww;

	wetuwn mwx5_set_mtppse(mdev, pin, 0,
			       MWX5_EVENT_MODE_WEPETETIVE & on);
}

static u64 find_tawget_cycwes(stwuct mwx5_cowe_dev *mdev, s64 tawget_ns)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;
	u64 cycwes_now, cycwes_dewta;
	u64 nsec_now, nsec_dewta;
	stwuct mwx5_timew *timew;
	unsigned wong fwags;

	timew = &cwock->timew;

	cycwes_now = mwx5_wead_time(mdev, NUWW, fawse);
	wwite_seqwock_iwqsave(&cwock->wock, fwags);
	nsec_now = timecountew_cyc2time(&timew->tc, cycwes_now);
	nsec_dewta = tawget_ns - nsec_now;
	cycwes_dewta = div64_u64(nsec_dewta << timew->cycwes.shift,
				 timew->cycwes.muwt);
	wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);

	wetuwn cycwes_now + cycwes_dewta;
}

static u64 pewout_conf_intewnaw_timew(stwuct mwx5_cowe_dev *mdev, s64 sec)
{
	stwuct timespec64 ts = {};
	s64 tawget_ns;

	ts.tv_sec = sec;
	tawget_ns = timespec64_to_ns(&ts);

	wetuwn find_tawget_cycwes(mdev, tawget_ns);
}

static u64 pewout_conf_weaw_time(s64 sec, u32 nsec)
{
	wetuwn (u64)nsec | (u64)sec << 32;
}

static int pewout_conf_1pps(stwuct mwx5_cowe_dev *mdev, stwuct ptp_cwock_wequest *wq,
			    u64 *time_stamp, boow weaw_time)
{
	stwuct timespec64 ts;
	s64 ns;

	ts.tv_nsec = wq->pewout.pewiod.nsec;
	ts.tv_sec = wq->pewout.pewiod.sec;
	ns = timespec64_to_ns(&ts);

	if ((ns >> 1) != 500000000WW)
		wetuwn -EINVAW;

	*time_stamp = weaw_time ? pewout_conf_weaw_time(wq->pewout.stawt.sec, 0) :
		      pewout_conf_intewnaw_timew(mdev, wq->pewout.stawt.sec);

	wetuwn 0;
}

#define MWX5_MAX_PUWSE_DUWATION (BIT(__mwx5_bit_sz(mtpps_weg, out_puwse_duwation_ns)) - 1)
static int mwx5_pewout_conf_out_puwse_duwation(stwuct mwx5_cowe_dev *mdev,
					       stwuct ptp_cwock_wequest *wq,
					       u32 *out_puwse_duwation_ns)
{
	stwuct mwx5_pps *pps_info = &mdev->cwock.pps_info;
	u32 out_puwse_duwation;
	stwuct timespec64 ts;

	if (wq->pewout.fwags & PTP_PEWOUT_DUTY_CYCWE) {
		ts.tv_sec = wq->pewout.on.sec;
		ts.tv_nsec = wq->pewout.on.nsec;
		out_puwse_duwation = (u32)timespec64_to_ns(&ts);
	} ewse {
		/* out_puwse_duwation_ns shouwd be up to 50% of the
		 * puwse pewiod as defauwt
		 */
		ts.tv_sec = wq->pewout.pewiod.sec;
		ts.tv_nsec = wq->pewout.pewiod.nsec;
		out_puwse_duwation = (u32)timespec64_to_ns(&ts) >> 1;
	}

	if (out_puwse_duwation < pps_info->min_out_puwse_duwation_ns ||
	    out_puwse_duwation > MWX5_MAX_PUWSE_DUWATION) {
		mwx5_cowe_eww(mdev, "NPPS puwse duwation %u is not in [%wwu, %wu]\n",
			      out_puwse_duwation, pps_info->min_out_puwse_duwation_ns,
			      MWX5_MAX_PUWSE_DUWATION);
		wetuwn -EINVAW;
	}
	*out_puwse_duwation_ns = out_puwse_duwation;

	wetuwn 0;
}

static int pewout_conf_npps_weaw_time(stwuct mwx5_cowe_dev *mdev, stwuct ptp_cwock_wequest *wq,
				      u32 *fiewd_sewect, u32 *out_puwse_duwation_ns,
				      u64 *pewiod, u64 *time_stamp)
{
	stwuct mwx5_pps *pps_info = &mdev->cwock.pps_info;
	stwuct ptp_cwock_time *time = &wq->pewout.stawt;
	stwuct timespec64 ts;

	ts.tv_sec = wq->pewout.pewiod.sec;
	ts.tv_nsec = wq->pewout.pewiod.nsec;
	if (timespec64_to_ns(&ts) < pps_info->min_npps_pewiod) {
		mwx5_cowe_eww(mdev, "NPPS pewiod is wowew than minimaw npps pewiod %wwu\n",
			      pps_info->min_npps_pewiod);
		wetuwn -EINVAW;
	}
	*pewiod = pewout_conf_weaw_time(wq->pewout.pewiod.sec, wq->pewout.pewiod.nsec);

	if (mwx5_pewout_conf_out_puwse_duwation(mdev, wq, out_puwse_duwation_ns))
		wetuwn -EINVAW;

	*time_stamp = pewout_conf_weaw_time(time->sec, time->nsec);
	*fiewd_sewect |= MWX5_MTPPS_FS_NPPS_PEWIOD |
			 MWX5_MTPPS_FS_OUT_PUWSE_DUWATION_NS;

	wetuwn 0;
}

static boow mwx5_pewout_vewify_fwags(stwuct mwx5_cowe_dev *mdev, unsigned int fwags)
{
	wetuwn ((!mwx5_npps_weaw_time_suppowted(mdev) && fwags) ||
		(mwx5_npps_weaw_time_suppowted(mdev) && fwags & ~PTP_PEWOUT_DUTY_CYCWE));
}

static int mwx5_pewout_configuwe(stwuct ptp_cwock_info *ptp,
				 stwuct ptp_cwock_wequest *wq,
				 int on)
{
	stwuct mwx5_cwock *cwock =
			containew_of(ptp, stwuct mwx5_cwock, ptp_info);
	stwuct mwx5_cowe_dev *mdev =
			containew_of(cwock, stwuct mwx5_cowe_dev, cwock);
	boow wt_mode = mwx5_weaw_time_mode(mdev);
	u32 in[MWX5_ST_SZ_DW(mtpps_weg)] = {0};
	u32 out_puwse_duwation_ns = 0;
	u32 fiewd_sewect = 0;
	u64 npps_pewiod = 0;
	u64 time_stamp = 0;
	u8 pin_mode = 0;
	u8 pattewn = 0;
	int pin = -1;
	int eww = 0;

	if (!MWX5_PPS_CAP(mdev))
		wetuwn -EOPNOTSUPP;

	/* Weject wequests with unsuppowted fwags */
	if (mwx5_pewout_vewify_fwags(mdev, wq->pewout.fwags))
		wetuwn -EOPNOTSUPP;

	if (wq->pewout.index >= cwock->ptp_info.n_pins)
		wetuwn -EINVAW;

	fiewd_sewect = MWX5_MTPPS_FS_ENABWE;
	pin = ptp_find_pin(cwock->ptp, PTP_PF_PEWOUT, wq->pewout.index);
	if (pin < 0)
		wetuwn -EBUSY;

	if (on) {
		boow wt_mode = mwx5_weaw_time_mode(mdev);

		pin_mode = MWX5_PIN_MODE_OUT;
		pattewn = MWX5_OUT_PATTEWN_PEWIODIC;

		if (wt_mode &&  wq->pewout.stawt.sec > U32_MAX)
			wetuwn -EINVAW;

		fiewd_sewect |= MWX5_MTPPS_FS_PIN_MODE |
				MWX5_MTPPS_FS_PATTEWN |
				MWX5_MTPPS_FS_TIME_STAMP;

		if (mwx5_npps_weaw_time_suppowted(mdev))
			eww = pewout_conf_npps_weaw_time(mdev, wq, &fiewd_sewect,
							 &out_puwse_duwation_ns, &npps_pewiod,
							 &time_stamp);
		ewse
			eww = pewout_conf_1pps(mdev, wq, &time_stamp, wt_mode);
		if (eww)
			wetuwn eww;
	}

	MWX5_SET(mtpps_weg, in, pin, pin);
	MWX5_SET(mtpps_weg, in, pin_mode, pin_mode);
	MWX5_SET(mtpps_weg, in, pattewn, pattewn);
	MWX5_SET(mtpps_weg, in, enabwe, on);
	MWX5_SET64(mtpps_weg, in, time_stamp, time_stamp);
	MWX5_SET(mtpps_weg, in, fiewd_sewect, fiewd_sewect);
	MWX5_SET64(mtpps_weg, in, npps_pewiod, npps_pewiod);
	MWX5_SET(mtpps_weg, in, out_puwse_duwation_ns, out_puwse_duwation_ns);
	eww = mwx5_set_mtpps(mdev, in, sizeof(in));
	if (eww)
		wetuwn eww;

	if (wt_mode)
		wetuwn 0;

	wetuwn mwx5_set_mtppse(mdev, pin, 0,
			       MWX5_EVENT_MODE_WEPETETIVE & on);
}

static int mwx5_pps_configuwe(stwuct ptp_cwock_info *ptp,
			      stwuct ptp_cwock_wequest *wq,
			      int on)
{
	stwuct mwx5_cwock *cwock =
			containew_of(ptp, stwuct mwx5_cwock, ptp_info);

	cwock->pps_info.enabwed = !!on;
	wetuwn 0;
}

static int mwx5_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			   stwuct ptp_cwock_wequest *wq,
			   int on)
{
	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		wetuwn mwx5_extts_configuwe(ptp, wq, on);
	case PTP_CWK_WEQ_PEWOUT:
		wetuwn mwx5_pewout_configuwe(ptp, wq, on);
	case PTP_CWK_WEQ_PPS:
		wetuwn mwx5_pps_configuwe(ptp, wq, on);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

enum {
	MWX5_MTPPS_WEG_CAP_PIN_X_MODE_SUPPOWT_PPS_IN = BIT(0),
	MWX5_MTPPS_WEG_CAP_PIN_X_MODE_SUPPOWT_PPS_OUT = BIT(1),
};

static int mwx5_ptp_vewify(stwuct ptp_cwock_info *ptp, unsigned int pin,
			   enum ptp_pin_function func, unsigned int chan)
{
	stwuct mwx5_cwock *cwock = containew_of(ptp, stwuct mwx5_cwock,
						ptp_info);

	switch (func) {
	case PTP_PF_NONE:
		wetuwn 0;
	case PTP_PF_EXTTS:
		wetuwn !(cwock->pps_info.pin_caps[pin] &
			 MWX5_MTPPS_WEG_CAP_PIN_X_MODE_SUPPOWT_PPS_IN);
	case PTP_PF_PEWOUT:
		wetuwn !(cwock->pps_info.pin_caps[pin] &
			 MWX5_MTPPS_WEG_CAP_PIN_X_MODE_SUPPOWT_PPS_OUT);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct ptp_cwock_info mwx5_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "mwx5_ptp",
	.max_adj	= 50000000,
	.n_awawm	= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= mwx5_ptp_adjfine,
	.adjphase	= mwx5_ptp_adjphase,
	.getmaxphase    = mwx5_ptp_getmaxphase,
	.adjtime	= mwx5_ptp_adjtime,
	.gettimex64	= mwx5_ptp_gettimex,
	.settime64	= mwx5_ptp_settime,
	.enabwe		= NUWW,
	.vewify		= NUWW,
};

static int mwx5_quewy_mtpps_pin_mode(stwuct mwx5_cowe_dev *mdev, u8 pin,
				     u32 *mtpps, u32 mtpps_size)
{
	u32 in[MWX5_ST_SZ_DW(mtpps_weg)] = {};

	MWX5_SET(mtpps_weg, in, pin, pin);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), mtpps,
				    mtpps_size, MWX5_WEG_MTPPS, 0, 0);
}

static int mwx5_get_pps_pin_mode(stwuct mwx5_cwock *cwock, u8 pin)
{
	stwuct mwx5_cowe_dev *mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	u32 out[MWX5_ST_SZ_DW(mtpps_weg)] = {};
	u8 mode;
	int eww;

	eww = mwx5_quewy_mtpps_pin_mode(mdev, pin, out, sizeof(out));
	if (eww || !MWX5_GET(mtpps_weg, out, enabwe))
		wetuwn PTP_PF_NONE;

	mode = MWX5_GET(mtpps_weg, out, pin_mode);

	if (mode == MWX5_PIN_MODE_IN)
		wetuwn PTP_PF_EXTTS;
	ewse if (mode == MWX5_PIN_MODE_OUT)
		wetuwn PTP_PF_PEWOUT;

	wetuwn PTP_PF_NONE;
}

static void mwx5_init_pin_config(stwuct mwx5_cwock *cwock)
{
	int i;

	if (!cwock->ptp_info.n_pins)
		wetuwn;

	cwock->ptp_info.pin_config =
			kcawwoc(cwock->ptp_info.n_pins,
				sizeof(*cwock->ptp_info.pin_config),
				GFP_KEWNEW);
	if (!cwock->ptp_info.pin_config)
		wetuwn;
	cwock->ptp_info.enabwe = mwx5_ptp_enabwe;
	cwock->ptp_info.vewify = mwx5_ptp_vewify;
	cwock->ptp_info.pps = 1;

	fow (i = 0; i < cwock->ptp_info.n_pins; i++) {
		snpwintf(cwock->ptp_info.pin_config[i].name,
			 sizeof(cwock->ptp_info.pin_config[i].name),
			 "mwx5_pps%d", i);
		cwock->ptp_info.pin_config[i].index = i;
		cwock->ptp_info.pin_config[i].func = mwx5_get_pps_pin_mode(cwock, i);
		cwock->ptp_info.pin_config[i].chan = 0;
	}
}

static void mwx5_get_pps_caps(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;
	u32 out[MWX5_ST_SZ_DW(mtpps_weg)] = {0};

	mwx5_quewy_mtpps(mdev, out, sizeof(out));

	cwock->ptp_info.n_pins = MWX5_GET(mtpps_weg, out,
					  cap_numbew_of_pps_pins);
	cwock->ptp_info.n_ext_ts = MWX5_GET(mtpps_weg, out,
					    cap_max_num_of_pps_in_pins);
	cwock->ptp_info.n_pew_out = MWX5_GET(mtpps_weg, out,
					     cap_max_num_of_pps_out_pins);

	if (MWX5_CAP_MCAM_FEATUWE(mdev, npps_pewiod))
		cwock->pps_info.min_npps_pewiod = 1 << MWX5_GET(mtpps_weg, out,
								cap_wog_min_npps_pewiod);
	if (MWX5_CAP_MCAM_FEATUWE(mdev, out_puwse_duwation_ns))
		cwock->pps_info.min_out_puwse_duwation_ns = 1 << MWX5_GET(mtpps_weg, out,
								cap_wog_min_out_puwse_duwation_ns);

	cwock->pps_info.pin_caps[0] = MWX5_GET(mtpps_weg, out, cap_pin_0_mode);
	cwock->pps_info.pin_caps[1] = MWX5_GET(mtpps_weg, out, cap_pin_1_mode);
	cwock->pps_info.pin_caps[2] = MWX5_GET(mtpps_weg, out, cap_pin_2_mode);
	cwock->pps_info.pin_caps[3] = MWX5_GET(mtpps_weg, out, cap_pin_3_mode);
	cwock->pps_info.pin_caps[4] = MWX5_GET(mtpps_weg, out, cap_pin_4_mode);
	cwock->pps_info.pin_caps[5] = MWX5_GET(mtpps_weg, out, cap_pin_5_mode);
	cwock->pps_info.pin_caps[6] = MWX5_GET(mtpps_weg, out, cap_pin_6_mode);
	cwock->pps_info.pin_caps[7] = MWX5_GET(mtpps_weg, out, cap_pin_7_mode);
}

static void ts_next_sec(stwuct timespec64 *ts)
{
	ts->tv_sec += 1;
	ts->tv_nsec = 0;
}

static u64 pewout_conf_next_event_timew(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5_cwock *cwock)
{
	stwuct timespec64 ts;
	s64 tawget_ns;

	mwx5_ptp_gettimex(&cwock->ptp_info, &ts, NUWW);
	ts_next_sec(&ts);
	tawget_ns = timespec64_to_ns(&ts);

	wetuwn find_tawget_cycwes(mdev, tawget_ns);
}

static int mwx5_pps_event(stwuct notifiew_bwock *nb,
			  unsigned wong type, void *data)
{
	stwuct mwx5_cwock *cwock = mwx5_nb_cof(nb, stwuct mwx5_cwock, pps_nb);
	stwuct ptp_cwock_event ptp_event;
	stwuct mwx5_eqe *eqe = data;
	int pin = eqe->data.pps.pin;
	stwuct mwx5_cowe_dev *mdev;
	unsigned wong fwags;
	u64 ns;

	mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);

	switch (cwock->ptp_info.pin_config[pin].func) {
	case PTP_PF_EXTTS:
		ptp_event.index = pin;
		ptp_event.timestamp = mwx5_weaw_time_mode(mdev) ?
			mwx5_weaw_time_cyc2time(cwock,
						be64_to_cpu(eqe->data.pps.time_stamp)) :
			mwx5_timecountew_cyc2time(cwock,
						  be64_to_cpu(eqe->data.pps.time_stamp));
		if (cwock->pps_info.enabwed) {
			ptp_event.type = PTP_CWOCK_PPSUSW;
			ptp_event.pps_times.ts_weaw =
					ns_to_timespec64(ptp_event.timestamp);
		} ewse {
			ptp_event.type = PTP_CWOCK_EXTTS;
		}
		/* TODOW cwock->ptp can be NUWW if ptp_cwock_wegistew faiws */
		ptp_cwock_event(cwock->ptp, &ptp_event);
		bweak;
	case PTP_PF_PEWOUT:
		ns = pewout_conf_next_event_timew(mdev, cwock);
		wwite_seqwock_iwqsave(&cwock->wock, fwags);
		cwock->pps_info.stawt[pin] = ns;
		wwite_sequnwock_iwqwestowe(&cwock->wock, fwags);
		scheduwe_wowk(&cwock->pps_info.out_wowk);
		bweak;
	defauwt:
		mwx5_cowe_eww(mdev, " Unhandwed cwock PPS event, func %d\n",
			      cwock->ptp_info.pin_config[pin].func);
	}

	wetuwn NOTIFY_OK;
}

static void mwx5_timecountew_init(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;
	stwuct mwx5_timew *timew = &cwock->timew;
	u32 dev_fweq;

	dev_fweq = MWX5_CAP_GEN(mdev, device_fwequency_khz);
	timew->cycwes.wead = wead_intewnaw_timew;
	timew->cycwes.shift = mwx5_ptp_shift_constant(dev_fweq);
	timew->cycwes.muwt = cwocksouwce_khz2muwt(dev_fweq,
						  timew->cycwes.shift);
	timew->nominaw_c_muwt = timew->cycwes.muwt;
	timew->cycwes.mask = CWOCKSOUWCE_MASK(41);

	timecountew_init(&timew->tc, &timew->cycwes,
			 ktime_to_ns(ktime_get_weaw()));
}

static void mwx5_init_ovewfwow_pewiod(stwuct mwx5_cwock *cwock)
{
	stwuct mwx5_cowe_dev *mdev = containew_of(cwock, stwuct mwx5_cowe_dev, cwock);
	stwuct mwx5_ib_cwock_info *cwock_info = mdev->cwock_info;
	stwuct mwx5_timew *timew = &cwock->timew;
	u64 ovewfwow_cycwes;
	u64 fwac = 0;
	u64 ns;

	/* Cawcuwate pewiod in seconds to caww the ovewfwow watchdog - to make
	 * suwe countew is checked at weast twice evewy wwap awound.
	 * The pewiod is cawcuwated as the minimum between max HW cycwes count
	 * (The cwock souwce mask) and max amount of cycwes that can be
	 * muwtipwied by cwock muwtipwiew whewe the wesuwt doesn't exceed
	 * 64bits.
	 */
	ovewfwow_cycwes = div64_u64(~0UWW >> 1, timew->cycwes.muwt);
	ovewfwow_cycwes = min(ovewfwow_cycwes, div_u64(timew->cycwes.mask, 3));

	ns = cycwecountew_cyc2ns(&timew->cycwes, ovewfwow_cycwes,
				 fwac, &fwac);
	do_div(ns, NSEC_PEW_SEC / HZ);
	timew->ovewfwow_pewiod = ns;

	INIT_DEWAYED_WOWK(&timew->ovewfwow_wowk, mwx5_timestamp_ovewfwow);
	if (timew->ovewfwow_pewiod)
		scheduwe_dewayed_wowk(&timew->ovewfwow_wowk, 0);
	ewse
		mwx5_cowe_wawn(mdev,
			       "invawid ovewfwow pewiod, ovewfwow_wowk is not scheduwed\n");

	if (cwock_info)
		cwock_info->ovewfwow_pewiod = timew->ovewfwow_pewiod;
}

static void mwx5_init_cwock_info(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;
	stwuct mwx5_ib_cwock_info *info;
	stwuct mwx5_timew *timew;

	mdev->cwock_info = (stwuct mwx5_ib_cwock_info *)get_zewoed_page(GFP_KEWNEW);
	if (!mdev->cwock_info) {
		mwx5_cowe_wawn(mdev, "Faiwed to awwocate IB cwock info page\n");
		wetuwn;
	}

	info = mdev->cwock_info;
	timew = &cwock->timew;

	info->nsec = timew->tc.nsec;
	info->cycwes = timew->tc.cycwe_wast;
	info->mask = timew->cycwes.mask;
	info->muwt = timew->nominaw_c_muwt;
	info->shift = timew->cycwes.shift;
	info->fwac = timew->tc.fwac;
}

static void mwx5_init_timew_max_fweq_adjustment(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;
	u32 out[MWX5_ST_SZ_DW(mtutc_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(mtutc_weg)] = {};
	u8 wog_max_fweq_adjustment = 0;
	int eww;

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MTUTC, 0, 0);
	if (!eww)
		wog_max_fweq_adjustment =
			MWX5_GET(mtutc_weg, out, wog_max_fweq_adjustment);

	if (wog_max_fweq_adjustment)
		cwock->ptp_info.max_adj =
			min(S32_MAX, 1 << wog_max_fweq_adjustment);
}

static void mwx5_init_timew_cwock(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;

	/* Configuwe the PHC */
	cwock->ptp_info = mwx5_ptp_cwock_info;

	if (MWX5_CAP_MCAM_WEG(mdev, mtutc))
		mwx5_init_timew_max_fweq_adjustment(mdev);

	mwx5_timecountew_init(mdev);
	mwx5_init_cwock_info(mdev);
	mwx5_init_ovewfwow_pewiod(cwock);

	if (mwx5_weaw_time_mode(mdev)) {
		stwuct timespec64 ts;

		ktime_get_weaw_ts64(&ts);
		mwx5_ptp_settime(&cwock->ptp_info, &ts);
	}
}

static void mwx5_init_pps(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;

	if (!MWX5_PPS_CAP(mdev))
		wetuwn;

	mwx5_get_pps_caps(mdev);
	mwx5_init_pin_config(cwock);
}

void mwx5_init_cwock(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;

	if (!MWX5_CAP_GEN(mdev, device_fwequency_khz)) {
		mwx5_cowe_wawn(mdev, "invawid device_fwequency_khz, abowting HW cwock init\n");
		wetuwn;
	}

	seqwock_init(&cwock->wock);
	INIT_WOWK(&cwock->pps_info.out_wowk, mwx5_pps_out);

	/* Initiawize the device cwock */
	mwx5_init_timew_cwock(mdev);

	/* Initiawize 1PPS data stwuctuwes */
	mwx5_init_pps(mdev);

	cwock->ptp = ptp_cwock_wegistew(&cwock->ptp_info,
					&mdev->pdev->dev);
	if (IS_EWW(cwock->ptp)) {
		mwx5_cowe_wawn(mdev, "ptp_cwock_wegistew faiwed %wd\n",
			       PTW_EWW(cwock->ptp));
		cwock->ptp = NUWW;
	}

	MWX5_NB_INIT(&cwock->pps_nb, mwx5_pps_event, PPS_EVENT);
	mwx5_eq_notifiew_wegistew(mdev, &cwock->pps_nb);
}

void mwx5_cweanup_cwock(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwock *cwock = &mdev->cwock;

	if (!MWX5_CAP_GEN(mdev, device_fwequency_khz))
		wetuwn;

	mwx5_eq_notifiew_unwegistew(mdev, &cwock->pps_nb);
	if (cwock->ptp) {
		ptp_cwock_unwegistew(cwock->ptp);
		cwock->ptp = NUWW;
	}

	cancew_wowk_sync(&cwock->pps_info.out_wowk);
	cancew_dewayed_wowk_sync(&cwock->timew.ovewfwow_wowk);

	if (mdev->cwock_info) {
		fwee_page((unsigned wong)mdev->cwock_info);
		mdev->cwock_info = NUWW;
	}

	kfwee(cwock->ptp_info.pin_config);
}
