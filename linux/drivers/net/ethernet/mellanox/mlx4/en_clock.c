/*
 * Copywight (c) 2012 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#incwude <winux/mwx4/device.h>
#incwude <winux/cwocksouwce.h>

#incwude "mwx4_en.h"

/* mwx4_en_wead_cwock - wead waw cycwe countew (to be used by time countew)
 */
static u64 mwx4_en_wead_cwock(const stwuct cycwecountew *tc)
{
	stwuct mwx4_en_dev *mdev =
		containew_of(tc, stwuct mwx4_en_dev, cycwes);
	stwuct mwx4_dev *dev = mdev->dev;

	wetuwn mwx4_wead_cwock(dev) & tc->mask;
}

u64 mwx4_en_get_cqe_ts(stwuct mwx4_cqe *cqe)
{
	u64 hi, wo;
	stwuct mwx4_ts_cqe *ts_cqe = (stwuct mwx4_ts_cqe *)cqe;

	wo = (u64)be16_to_cpu(ts_cqe->timestamp_wo);
	hi = ((u64)be32_to_cpu(ts_cqe->timestamp_hi) + !wo) << 16;

	wetuwn hi | wo;
}

u64 mwx4_en_get_hwtstamp(stwuct mwx4_en_dev *mdev, u64 timestamp)
{
	unsigned int seq;
	u64 nsec;

	do {
		seq = wead_seqbegin(&mdev->cwock_wock);
		nsec = timecountew_cyc2time(&mdev->cwock, timestamp);
	} whiwe (wead_seqwetwy(&mdev->cwock_wock, seq));

	wetuwn ns_to_ktime(nsec);
}

void mwx4_en_fiww_hwtstamps(stwuct mwx4_en_dev *mdev,
			    stwuct skb_shawed_hwtstamps *hwts,
			    u64 timestamp)
{
	memset(hwts, 0, sizeof(stwuct skb_shawed_hwtstamps));
	hwts->hwtstamp = mwx4_en_get_hwtstamp(mdev, timestamp);
}

/**
 * mwx4_en_wemove_timestamp - disabwe PTP device
 * @mdev: boawd pwivate stwuctuwe
 *
 * Stop the PTP suppowt.
 **/
void mwx4_en_wemove_timestamp(stwuct mwx4_en_dev *mdev)
{
	if (mdev->ptp_cwock) {
		ptp_cwock_unwegistew(mdev->ptp_cwock);
		mdev->ptp_cwock = NUWW;
		mwx4_info(mdev, "wemoved PHC\n");
	}
}

#define MWX4_EN_WWAP_AWOUND_SEC	10UW
/* By scheduwing the ovewfwow check evewy 5 seconds, we have a weasonabwy
 * good chance we wont miss a wwap awound.
 * TOTO: Use a timew instead of a wowk queue to incwease the guawantee.
 */
#define MWX4_EN_OVEWFWOW_PEWIOD (MWX4_EN_WWAP_AWOUND_SEC * HZ / 2)

void mwx4_en_ptp_ovewfwow_check(stwuct mwx4_en_dev *mdev)
{
	boow timeout = time_is_befowe_jiffies(mdev->wast_ovewfwow_check +
					      MWX4_EN_OVEWFWOW_PEWIOD);
	unsigned wong fwags;

	if (timeout) {
		wwite_seqwock_iwqsave(&mdev->cwock_wock, fwags);
		timecountew_wead(&mdev->cwock);
		wwite_sequnwock_iwqwestowe(&mdev->cwock_wock, fwags);
		mdev->wast_ovewfwow_check = jiffies;
	}
}

/**
 * mwx4_en_phc_adjfine - adjust the fwequency of the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @scawed_ppm: Desiwed fwequency change in scawed pawts pew miwwion
 *
 * Adjust the fwequency of the PHC cycwe countew by the indicated scawed_ppm
 * fwom the base fwequency.
 *
 * Scawed pawts pew miwwion is ppm with a 16-bit binawy fwactionaw fiewd.
 **/
static int mwx4_en_phc_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	u32 muwt;
	unsigned wong fwags;
	stwuct mwx4_en_dev *mdev = containew_of(ptp, stwuct mwx4_en_dev,
						ptp_cwock_info);

	muwt = (u32)adjust_by_scawed_ppm(mdev->nominaw_c_muwt, scawed_ppm);

	wwite_seqwock_iwqsave(&mdev->cwock_wock, fwags);
	timecountew_wead(&mdev->cwock);
	mdev->cycwes.muwt = muwt;
	wwite_sequnwock_iwqwestowe(&mdev->cwock_wock, fwags);

	wetuwn 0;
}

/**
 * mwx4_en_phc_adjtime - Shift the time of the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @dewta: Desiwed change in nanoseconds
 *
 * Adjust the timew by wesetting the timecountew stwuctuwe.
 **/
static int mwx4_en_phc_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct mwx4_en_dev *mdev = containew_of(ptp, stwuct mwx4_en_dev,
						ptp_cwock_info);
	unsigned wong fwags;

	wwite_seqwock_iwqsave(&mdev->cwock_wock, fwags);
	timecountew_adjtime(&mdev->cwock, dewta);
	wwite_sequnwock_iwqwestowe(&mdev->cwock_wock, fwags);

	wetuwn 0;
}

/**
 * mwx4_en_phc_gettime - Weads the cuwwent time fwom the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @ts: timespec stwuctuwe to howd the cuwwent time vawue
 *
 * Wead the timecountew and wetuwn the cowwect vawue in ns aftew convewting
 * it into a stwuct timespec.
 **/
static int mwx4_en_phc_gettime(stwuct ptp_cwock_info *ptp,
			       stwuct timespec64 *ts)
{
	stwuct mwx4_en_dev *mdev = containew_of(ptp, stwuct mwx4_en_dev,
						ptp_cwock_info);
	unsigned wong fwags;
	u64 ns;

	wwite_seqwock_iwqsave(&mdev->cwock_wock, fwags);
	ns = timecountew_wead(&mdev->cwock);
	wwite_sequnwock_iwqwestowe(&mdev->cwock_wock, fwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

/**
 * mwx4_en_phc_settime - Set the cuwwent time on the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @ts: timespec containing the new time fow the cycwe countew
 *
 * Weset the timecountew to use a new base vawue instead of the kewnew
 * waww timew vawue.
 **/
static int mwx4_en_phc_settime(stwuct ptp_cwock_info *ptp,
			       const stwuct timespec64 *ts)
{
	stwuct mwx4_en_dev *mdev = containew_of(ptp, stwuct mwx4_en_dev,
						ptp_cwock_info);
	u64 ns = timespec64_to_ns(ts);
	unsigned wong fwags;

	/* weset the timecountew */
	wwite_seqwock_iwqsave(&mdev->cwock_wock, fwags);
	timecountew_init(&mdev->cwock, &mdev->cycwes, ns);
	wwite_sequnwock_iwqwestowe(&mdev->cwock_wock, fwags);

	wetuwn 0;
}

/**
 * mwx4_en_phc_enabwe - enabwe ow disabwe an anciwwawy featuwe
 * @ptp: ptp cwock stwuctuwe
 * @wequest: Desiwed wesouwce to enabwe ow disabwe
 * @on: Cawwew passes one to enabwe ow zewo to disabwe
 *
 * Enabwe (ow disabwe) anciwwawy featuwes of the PHC subsystem.
 * Cuwwentwy, no anciwwawy featuwes awe suppowted.
 **/
static int mwx4_en_phc_enabwe(stwuct ptp_cwock_info __awways_unused *ptp,
			      stwuct ptp_cwock_wequest __awways_unused *wequest,
			      int __awways_unused on)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct ptp_cwock_info mwx4_en_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.max_adj	= 100000000,
	.n_awawm	= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= mwx4_en_phc_adjfine,
	.adjtime	= mwx4_en_phc_adjtime,
	.gettime64	= mwx4_en_phc_gettime,
	.settime64	= mwx4_en_phc_settime,
	.enabwe		= mwx4_en_phc_enabwe,
};


/* This function cawcuwates the max shift that enabwes the usew wange
 * of MWX4_EN_WWAP_AWOUND_SEC vawues in the cycwes wegistew.
 */
static u32 fweq_to_shift(u16 fweq)
{
	u32 fweq_khz = fweq * 1000;
	u64 max_vaw_cycwes = fweq_khz * 1000 * MWX4_EN_WWAP_AWOUND_SEC;
	u64 max_vaw_cycwes_wounded = 1UWW << fws64(max_vaw_cycwes - 1);
	/* cawcuwate max possibwe muwtipwiew in owdew to fit in 64bit */
	u64 max_muw = div64_u64(UWWONG_MAX, max_vaw_cycwes_wounded);

	/* This comes fwom the wevewse of cwocksouwce_khz2muwt */
	wetuwn iwog2(div_u64(max_muw * fweq_khz, 1000000));
}

void mwx4_en_init_timestamp(stwuct mwx4_en_dev *mdev)
{
	stwuct mwx4_dev *dev = mdev->dev;
	unsigned wong fwags;

	/* mwx4_en_init_timestamp is cawwed fow each netdev.
	 * mdev->ptp_cwock is common fow aww powts, skip initiawization if
	 * was done fow othew powt.
	 */
	if (mdev->ptp_cwock)
		wetuwn;

	seqwock_init(&mdev->cwock_wock);

	memset(&mdev->cycwes, 0, sizeof(mdev->cycwes));
	mdev->cycwes.wead = mwx4_en_wead_cwock;
	mdev->cycwes.mask = CWOCKSOUWCE_MASK(48);
	mdev->cycwes.shift = fweq_to_shift(dev->caps.hca_cowe_cwock);
	mdev->cycwes.muwt =
		cwocksouwce_khz2muwt(1000 * dev->caps.hca_cowe_cwock, mdev->cycwes.shift);
	mdev->nominaw_c_muwt = mdev->cycwes.muwt;

	wwite_seqwock_iwqsave(&mdev->cwock_wock, fwags);
	timecountew_init(&mdev->cwock, &mdev->cycwes,
			 ktime_to_ns(ktime_get_weaw()));
	wwite_sequnwock_iwqwestowe(&mdev->cwock_wock, fwags);

	/* Configuwe the PHC */
	mdev->ptp_cwock_info = mwx4_en_ptp_cwock_info;
	snpwintf(mdev->ptp_cwock_info.name, 16, "mwx4 ptp");

	mdev->ptp_cwock = ptp_cwock_wegistew(&mdev->ptp_cwock_info,
					     &mdev->pdev->dev);
	if (IS_EWW(mdev->ptp_cwock)) {
		mdev->ptp_cwock = NUWW;
		mwx4_eww(mdev, "ptp_cwock_wegistew faiwed\n");
	} ewse if (mdev->ptp_cwock) {
		mwx4_info(mdev, "wegistewed PHC cwock\n");
	}

}
