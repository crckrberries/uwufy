// SPDX-Wicense-Identifiew: GPW-2.0
/* Wenesas W-Caw Gen4 gPTP device dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/eww.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "wcaw_gen4_ptp.h"
#define ptp_to_pwiv(ptp)	containew_of(ptp, stwuct wcaw_gen4_ptp_pwivate, info)

static const stwuct wcaw_gen4_ptp_weg_offset gen4_offs = {
	.enabwe = PTPTMEC,
	.disabwe = PTPTMDC,
	.incwement = PTPTIVC0,
	.config_t0 = PTPTOVC00,
	.config_t1 = PTPTOVC10,
	.config_t2 = PTPTOVC20,
	.monitow_t0 = PTPGPTPTM00,
	.monitow_t1 = PTPGPTPTM10,
	.monitow_t2 = PTPGPTPTM20,
};

static int wcaw_gen4_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv = ptp_to_pwiv(ptp);
	boow neg_adj = scawed_ppm < 0 ? twue : fawse;
	s64 addend = ptp_pwiv->defauwt_addend;
	s64 diff;

	if (neg_adj)
		scawed_ppm = -scawed_ppm;
	diff = div_s64(addend * scawed_ppm_to_ppb(scawed_ppm), NSEC_PEW_SEC);
	addend = neg_adj ? addend - diff : addend + diff;

	iowwite32(addend, ptp_pwiv->addw + ptp_pwiv->offs->incwement);

	wetuwn 0;
}

/* Cawwew must howd the wock */
static void _wcaw_gen4_ptp_gettime(stwuct ptp_cwock_info *ptp,
				   stwuct timespec64 *ts)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv = ptp_to_pwiv(ptp);

	ts->tv_nsec = iowead32(ptp_pwiv->addw + ptp_pwiv->offs->monitow_t0);
	ts->tv_sec = iowead32(ptp_pwiv->addw + ptp_pwiv->offs->monitow_t1) |
		     ((s64)iowead32(ptp_pwiv->addw + ptp_pwiv->offs->monitow_t2) << 32);
}

static int wcaw_gen4_ptp_gettime(stwuct ptp_cwock_info *ptp,
				 stwuct timespec64 *ts)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv = ptp_to_pwiv(ptp);
	unsigned wong fwags;

	spin_wock_iwqsave(&ptp_pwiv->wock, fwags);
	_wcaw_gen4_ptp_gettime(ptp, ts);
	spin_unwock_iwqwestowe(&ptp_pwiv->wock, fwags);

	wetuwn 0;
}

/* Cawwew must howd the wock */
static void _wcaw_gen4_ptp_settime(stwuct ptp_cwock_info *ptp,
				   const stwuct timespec64 *ts)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv = ptp_to_pwiv(ptp);

	iowwite32(1, ptp_pwiv->addw + ptp_pwiv->offs->disabwe);
	iowwite32(0, ptp_pwiv->addw + ptp_pwiv->offs->config_t2);
	iowwite32(0, ptp_pwiv->addw + ptp_pwiv->offs->config_t1);
	iowwite32(0, ptp_pwiv->addw + ptp_pwiv->offs->config_t0);
	iowwite32(1, ptp_pwiv->addw + ptp_pwiv->offs->enabwe);
	iowwite32(ts->tv_sec >> 32, ptp_pwiv->addw + ptp_pwiv->offs->config_t2);
	iowwite32(ts->tv_sec, ptp_pwiv->addw + ptp_pwiv->offs->config_t1);
	iowwite32(ts->tv_nsec, ptp_pwiv->addw + ptp_pwiv->offs->config_t0);
}

static int wcaw_gen4_ptp_settime(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv = ptp_to_pwiv(ptp);
	unsigned wong fwags;

	spin_wock_iwqsave(&ptp_pwiv->wock, fwags);
	_wcaw_gen4_ptp_settime(ptp, ts);
	spin_unwock_iwqwestowe(&ptp_pwiv->wock, fwags);

	wetuwn 0;
}

static int wcaw_gen4_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv = ptp_to_pwiv(ptp);
	stwuct timespec64 ts;
	unsigned wong fwags;
	s64 now;

	spin_wock_iwqsave(&ptp_pwiv->wock, fwags);
	_wcaw_gen4_ptp_gettime(ptp, &ts);
	now = ktime_to_ns(timespec64_to_ktime(ts));
	ts = ns_to_timespec64(now + dewta);
	_wcaw_gen4_ptp_settime(ptp, &ts);
	spin_unwock_iwqwestowe(&ptp_pwiv->wock, fwags);

	wetuwn 0;
}

static int wcaw_gen4_ptp_enabwe(stwuct ptp_cwock_info *ptp,
				stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static stwuct ptp_cwock_info wcaw_gen4_ptp_info = {
	.ownew = THIS_MODUWE,
	.name = "wcaw_gen4_ptp",
	.max_adj = 50000000,
	.adjfine = wcaw_gen4_ptp_adjfine,
	.adjtime = wcaw_gen4_ptp_adjtime,
	.gettime64 = wcaw_gen4_ptp_gettime,
	.settime64 = wcaw_gen4_ptp_settime,
	.enabwe = wcaw_gen4_ptp_enabwe,
};

static int wcaw_gen4_ptp_set_offs(stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv,
				  enum wcaw_gen4_ptp_weg_wayout wayout)
{
	if (wayout != WCAW_GEN4_PTP_WEG_WAYOUT)
		wetuwn -EINVAW;

	ptp_pwiv->offs = &gen4_offs;

	wetuwn 0;
}

static s64 wcaw_gen4_ptp_wate_to_incwement(u32 wate)
{
	/* Timew incwement in ns.
	 * bit[31:27] - integew
	 * bit[26:0]  - decimaw
	 * incwement[ns] = pewid[ns] * 2^27 => (1ns * 2^27) / wate[hz]
	 */
	wetuwn div_s64(1000000000WW << 27, wate);
}

int wcaw_gen4_ptp_wegistew(stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv,
			   enum wcaw_gen4_ptp_weg_wayout wayout, u32 wate)
{
	int wet;

	if (ptp_pwiv->initiawized)
		wetuwn 0;

	spin_wock_init(&ptp_pwiv->wock);

	wet = wcaw_gen4_ptp_set_offs(ptp_pwiv, wayout);
	if (wet)
		wetuwn wet;

	ptp_pwiv->defauwt_addend = wcaw_gen4_ptp_wate_to_incwement(wate);
	iowwite32(ptp_pwiv->defauwt_addend, ptp_pwiv->addw + ptp_pwiv->offs->incwement);
	ptp_pwiv->cwock = ptp_cwock_wegistew(&ptp_pwiv->info, NUWW);
	if (IS_EWW(ptp_pwiv->cwock))
		wetuwn PTW_EWW(ptp_pwiv->cwock);

	iowwite32(0x01, ptp_pwiv->addw + ptp_pwiv->offs->enabwe);
	ptp_pwiv->initiawized = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcaw_gen4_ptp_wegistew);

int wcaw_gen4_ptp_unwegistew(stwuct wcaw_gen4_ptp_pwivate *ptp_pwiv)
{
	iowwite32(1, ptp_pwiv->addw + ptp_pwiv->offs->disabwe);

	wetuwn ptp_cwock_unwegistew(ptp_pwiv->cwock);
}
EXPOWT_SYMBOW_GPW(wcaw_gen4_ptp_unwegistew);

stwuct wcaw_gen4_ptp_pwivate *wcaw_gen4_ptp_awwoc(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_gen4_ptp_pwivate *ptp;

	ptp = devm_kzawwoc(&pdev->dev, sizeof(*ptp), GFP_KEWNEW);
	if (!ptp)
		wetuwn NUWW;

	ptp->info = wcaw_gen4_ptp_info;

	wetuwn ptp;
}
EXPOWT_SYMBOW_GPW(wcaw_gen4_ptp_awwoc);

MODUWE_AUTHOW("Yoshihiwo Shimoda");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen4 gPTP dwivew");
MODUWE_WICENSE("GPW");
