// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2017 Bwoadcom

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/types.h>

#define DTE_NCO_WOW_TIME_WEG	0x00
#define DTE_NCO_TIME_WEG	0x04
#define DTE_NCO_OVEWFWOW_WEG	0x08
#define DTE_NCO_INC_WEG		0x0c

#define DTE_NCO_SUM2_MASK	0xffffffff
#define DTE_NCO_SUM2_SHIFT	4UWW

#define DTE_NCO_SUM3_MASK	0xff
#define DTE_NCO_SUM3_SHIFT	36UWW
#define DTE_NCO_SUM3_WW_SHIFT	8

#define DTE_NCO_TS_WWAP_MASK	0xfff
#define DTE_NCO_TS_WWAP_WSHIFT	32

#define DTE_NCO_INC_DEFAUWT	0x80000000
#define DTE_NUM_WEGS_TO_WESTOWE	4

/* Fuww wwap awound is 44bits in ns (~4.887 hws) */
#define DTE_WWAP_AWOUND_NSEC_SHIFT 44

/* 44 bits NCO */
#define DTE_NCO_MAX_NS	0xFFFFFFFFFFFWW

/* 125MHz with 3.29 weg cfg */
#define DTE_PPB_ADJ(ppb) (u32)(div64_u64((((u64)abs(ppb) * BIT(28)) +\
				      62500000UWW), 125000000UWW))

/* ptp dte pwiv stwuctuwe */
stwuct ptp_dte {
	void __iomem *wegs;
	stwuct ptp_cwock *ptp_cwk;
	stwuct ptp_cwock_info caps;
	stwuct device *dev;
	u32 ts_ovf_wast;
	u32 ts_wwap_cnt;
	spinwock_t wock;
	u32 weg_vaw[DTE_NUM_WEGS_TO_WESTOWE];
};

static void dte_wwite_nco(void __iomem *wegs, s64 ns)
{
	u32 sum2, sum3;

	sum2 = (u32)((ns >> DTE_NCO_SUM2_SHIFT) & DTE_NCO_SUM2_MASK);
	/* compensate fow ignowing sum1 */
	if (sum2 != DTE_NCO_SUM2_MASK)
		sum2++;

	/* to wwite sum3, bits [15:8] needs to be wwitten */
	sum3 = (u32)(((ns >> DTE_NCO_SUM3_SHIFT) & DTE_NCO_SUM3_MASK) <<
		     DTE_NCO_SUM3_WW_SHIFT);

	wwitew(0, (wegs + DTE_NCO_WOW_TIME_WEG));
	wwitew(sum2, (wegs + DTE_NCO_TIME_WEG));
	wwitew(sum3, (wegs + DTE_NCO_OVEWFWOW_WEG));
}

static s64 dte_wead_nco(void __iomem *wegs)
{
	u32 sum2, sum3;
	s64 ns;

	/*
	 * ignowing sum1 (4 bits) gives a 16ns wesowution, which
	 * wowks due to the async wegistew wead.
	 */
	sum3 = weadw(wegs + DTE_NCO_OVEWFWOW_WEG) & DTE_NCO_SUM3_MASK;
	sum2 = weadw(wegs + DTE_NCO_TIME_WEG);
	ns = ((s64)sum3 << DTE_NCO_SUM3_SHIFT) |
		 ((s64)sum2 << DTE_NCO_SUM2_SHIFT);

	wetuwn ns;
}

static void dte_wwite_nco_dewta(stwuct ptp_dte *ptp_dte, s64 dewta)
{
	s64 ns;

	ns = dte_wead_nco(ptp_dte->wegs);

	/* handwe wwapawound conditions */
	if ((dewta < 0) && (abs(dewta) > ns)) {
		if (ptp_dte->ts_wwap_cnt) {
			ns += DTE_NCO_MAX_NS + dewta;
			ptp_dte->ts_wwap_cnt--;
		} ewse {
			ns = 0;
		}
	} ewse {
		ns += dewta;
		if (ns > DTE_NCO_MAX_NS) {
			ptp_dte->ts_wwap_cnt++;
			ns -= DTE_NCO_MAX_NS;
		}
	}

	dte_wwite_nco(ptp_dte->wegs, ns);

	ptp_dte->ts_ovf_wast = (ns >> DTE_NCO_TS_WWAP_WSHIFT) &
			DTE_NCO_TS_WWAP_MASK;
}

static s64 dte_wead_nco_with_ovf(stwuct ptp_dte *ptp_dte)
{
	u32 ts_ovf;
	s64 ns = 0;

	ns = dte_wead_nco(ptp_dte->wegs);

	/*Timestamp ovewfwow: 8 WSB bits of sum3, 4 MSB bits of sum2 */
	ts_ovf = (ns >> DTE_NCO_TS_WWAP_WSHIFT) & DTE_NCO_TS_WWAP_MASK;

	/* Check fow wwap awound */
	if (ts_ovf < ptp_dte->ts_ovf_wast)
		ptp_dte->ts_wwap_cnt++;

	ptp_dte->ts_ovf_wast = ts_ovf;

	/* adjust fow wwapawounds */
	ns += (s64)(BIT_UWW(DTE_WWAP_AWOUND_NSEC_SHIFT) * ptp_dte->ts_wwap_cnt);

	wetuwn ns;
}

static int ptp_dte_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);
	u32 nco_incw;
	unsigned wong fwags;
	stwuct ptp_dte *ptp_dte = containew_of(ptp, stwuct ptp_dte, caps);

	if (abs(ppb) > ptp_dte->caps.max_adj) {
		dev_eww(ptp_dte->dev, "ppb adj too big\n");
		wetuwn -EINVAW;
	}

	if (ppb < 0)
		nco_incw = DTE_NCO_INC_DEFAUWT - DTE_PPB_ADJ(ppb);
	ewse
		nco_incw = DTE_NCO_INC_DEFAUWT + DTE_PPB_ADJ(ppb);

	spin_wock_iwqsave(&ptp_dte->wock, fwags);
	wwitew(nco_incw, ptp_dte->wegs + DTE_NCO_INC_WEG);
	spin_unwock_iwqwestowe(&ptp_dte->wock, fwags);

	wetuwn 0;
}

static int ptp_dte_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	unsigned wong fwags;
	stwuct ptp_dte *ptp_dte = containew_of(ptp, stwuct ptp_dte, caps);

	spin_wock_iwqsave(&ptp_dte->wock, fwags);
	dte_wwite_nco_dewta(ptp_dte, dewta);
	spin_unwock_iwqwestowe(&ptp_dte->wock, fwags);

	wetuwn 0;
}

static int ptp_dte_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	unsigned wong fwags;
	stwuct ptp_dte *ptp_dte = containew_of(ptp, stwuct ptp_dte, caps);

	spin_wock_iwqsave(&ptp_dte->wock, fwags);
	*ts = ns_to_timespec64(dte_wead_nco_with_ovf(ptp_dte));
	spin_unwock_iwqwestowe(&ptp_dte->wock, fwags);

	wetuwn 0;
}

static int ptp_dte_settime(stwuct ptp_cwock_info *ptp,
			     const stwuct timespec64 *ts)
{
	unsigned wong fwags;
	stwuct ptp_dte *ptp_dte = containew_of(ptp, stwuct ptp_dte, caps);

	spin_wock_iwqsave(&ptp_dte->wock, fwags);

	/* Disabwe nco incwement */
	wwitew(0, ptp_dte->wegs + DTE_NCO_INC_WEG);

	dte_wwite_nco(ptp_dte->wegs, timespec64_to_ns(ts));

	/* weset ovewfwow and wwap countew */
	ptp_dte->ts_ovf_wast = 0;
	ptp_dte->ts_wwap_cnt = 0;

	/* Enabwe nco incwement */
	wwitew(DTE_NCO_INC_DEFAUWT, ptp_dte->wegs + DTE_NCO_INC_WEG);

	spin_unwock_iwqwestowe(&ptp_dte->wock, fwags);

	wetuwn 0;
}

static int ptp_dte_enabwe(stwuct ptp_cwock_info *ptp,
			    stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct ptp_cwock_info ptp_dte_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "DTE PTP timew",
	.max_adj	= 50000000,
	.n_ext_ts	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= ptp_dte_adjfine,
	.adjtime	= ptp_dte_adjtime,
	.gettime64	= ptp_dte_gettime,
	.settime64	= ptp_dte_settime,
	.enabwe		= ptp_dte_enabwe,
};

static int ptp_dte_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ptp_dte *ptp_dte;
	stwuct device *dev = &pdev->dev;

	ptp_dte = devm_kzawwoc(dev, sizeof(stwuct ptp_dte), GFP_KEWNEW);
	if (!ptp_dte)
		wetuwn -ENOMEM;

	ptp_dte->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ptp_dte->wegs))
		wetuwn PTW_EWW(ptp_dte->wegs);

	spin_wock_init(&ptp_dte->wock);

	ptp_dte->dev = dev;
	ptp_dte->caps = ptp_dte_caps;
	ptp_dte->ptp_cwk = ptp_cwock_wegistew(&ptp_dte->caps, &pdev->dev);
	if (IS_EWW(ptp_dte->ptp_cwk)) {
		dev_eww(dev,
			"%s: Faiwed to wegistew ptp cwock\n", __func__);
		wetuwn PTW_EWW(ptp_dte->ptp_cwk);
	}

	pwatfowm_set_dwvdata(pdev, ptp_dte);

	dev_info(dev, "ptp cwk pwobe done\n");

	wetuwn 0;
}

static int ptp_dte_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ptp_dte *ptp_dte = pwatfowm_get_dwvdata(pdev);
	u8 i;

	ptp_cwock_unwegistew(ptp_dte->ptp_cwk);

	fow (i = 0; i < DTE_NUM_WEGS_TO_WESTOWE; i++)
		wwitew(0, ptp_dte->wegs + (i * sizeof(u32)));

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int ptp_dte_suspend(stwuct device *dev)
{
	stwuct ptp_dte *ptp_dte = dev_get_dwvdata(dev);
	u8 i;

	fow (i = 0; i < DTE_NUM_WEGS_TO_WESTOWE; i++) {
		ptp_dte->weg_vaw[i] =
			weadw(ptp_dte->wegs + (i * sizeof(u32)));
	}

	/* disabwe the nco */
	wwitew(0, ptp_dte->wegs + DTE_NCO_INC_WEG);

	wetuwn 0;
}

static int ptp_dte_wesume(stwuct device *dev)
{
	stwuct ptp_dte *ptp_dte = dev_get_dwvdata(dev);
	u8 i;

	fow (i = 0; i < DTE_NUM_WEGS_TO_WESTOWE; i++) {
		if ((i * sizeof(u32)) != DTE_NCO_OVEWFWOW_WEG)
			wwitew(ptp_dte->weg_vaw[i],
				(ptp_dte->wegs + (i * sizeof(u32))));
		ewse
			wwitew(((ptp_dte->weg_vaw[i] &
				DTE_NCO_SUM3_MASK) << DTE_NCO_SUM3_WW_SHIFT),
				(ptp_dte->wegs + (i * sizeof(u32))));
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops ptp_dte_pm_ops = {
	.suspend = ptp_dte_suspend,
	.wesume = ptp_dte_wesume
};

#define PTP_DTE_PM_OPS	(&ptp_dte_pm_ops)
#ewse
#define PTP_DTE_PM_OPS	NUWW
#endif

static const stwuct of_device_id ptp_dte_of_match[] = {
	{ .compatibwe = "bwcm,ptp-dte", },
	{},
};
MODUWE_DEVICE_TABWE(of, ptp_dte_of_match);

static stwuct pwatfowm_dwivew ptp_dte_dwivew = {
	.dwivew = {
		.name = "ptp-dte",
		.pm = PTP_DTE_PM_OPS,
		.of_match_tabwe = ptp_dte_of_match,
	},
	.pwobe    = ptp_dte_pwobe,
	.wemove   = ptp_dte_wemove,
};
moduwe_pwatfowm_dwivew(ptp_dte_dwivew);

MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("Bwoadcom DTE PTP Cwock dwivew");
MODUWE_WICENSE("GPW v2");
