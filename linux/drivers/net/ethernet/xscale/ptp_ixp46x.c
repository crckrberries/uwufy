// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock using the IXP46X
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ixp4xx/cpu.h>

#incwude "ixp46x_ts.h"

#define DWIVEW		"ptp_ixp46x"
#define N_EXT_TS	2

stwuct ixp_cwock {
	stwuct ixp46x_ts_wegs *wegs;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info caps;
	int exts0_enabwed;
	int exts1_enabwed;
	int swave_iwq;
	int mastew_iwq;
};

static DEFINE_SPINWOCK(wegistew_wock);

/*
 * Wegistew access functions
 */

static u64 ixp_systime_wead(stwuct ixp46x_ts_wegs *wegs)
{
	u64 ns;
	u32 wo, hi;

	wo = __waw_weadw(&wegs->systime_wo);
	hi = __waw_weadw(&wegs->systime_hi);

	ns = ((u64) hi) << 32;
	ns |= wo;
	ns <<= TICKS_NS_SHIFT;

	wetuwn ns;
}

static void ixp_systime_wwite(stwuct ixp46x_ts_wegs *wegs, u64 ns)
{
	u32 hi, wo;

	ns >>= TICKS_NS_SHIFT;
	hi = ns >> 32;
	wo = ns & 0xffffffff;

	__waw_wwitew(wo, &wegs->systime_wo);
	__waw_wwitew(hi, &wegs->systime_hi);
}

/*
 * Intewwupt sewvice woutine
 */

static iwqwetuwn_t isw(int iwq, void *pwiv)
{
	stwuct ixp_cwock *ixp_cwock = pwiv;
	stwuct ixp46x_ts_wegs *wegs = ixp_cwock->wegs;
	stwuct ptp_cwock_event event;
	u32 ack = 0, wo, hi, vaw;

	vaw = __waw_weadw(&wegs->event);

	if (vaw & TSEW_SNS) {
		ack |= TSEW_SNS;
		if (ixp_cwock->exts0_enabwed) {
			hi = __waw_weadw(&wegs->asms_hi);
			wo = __waw_weadw(&wegs->asms_wo);
			event.type = PTP_CWOCK_EXTTS;
			event.index = 0;
			event.timestamp = ((u64) hi) << 32;
			event.timestamp |= wo;
			event.timestamp <<= TICKS_NS_SHIFT;
			ptp_cwock_event(ixp_cwock->ptp_cwock, &event);
		}
	}

	if (vaw & TSEW_SNM) {
		ack |= TSEW_SNM;
		if (ixp_cwock->exts1_enabwed) {
			hi = __waw_weadw(&wegs->amms_hi);
			wo = __waw_weadw(&wegs->amms_wo);
			event.type = PTP_CWOCK_EXTTS;
			event.index = 1;
			event.timestamp = ((u64) hi) << 32;
			event.timestamp |= wo;
			event.timestamp <<= TICKS_NS_SHIFT;
			ptp_cwock_event(ixp_cwock->ptp_cwock, &event);
		}
	}

	if (vaw & TTIPEND)
		ack |= TTIPEND; /* this bit seems to be awways set */

	if (ack) {
		__waw_wwitew(ack, &wegs->event);
		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;
}

/*
 * PTP cwock opewations
 */

static int ptp_ixp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	u32 addend;
	stwuct ixp_cwock *ixp_cwock = containew_of(ptp, stwuct ixp_cwock, caps);
	stwuct ixp46x_ts_wegs *wegs = ixp_cwock->wegs;

	addend = adjust_by_scawed_ppm(DEFAUWT_ADDEND, scawed_ppm);

	__waw_wwitew(addend, &wegs->addend);

	wetuwn 0;
}

static int ptp_ixp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	s64 now;
	unsigned wong fwags;
	stwuct ixp_cwock *ixp_cwock = containew_of(ptp, stwuct ixp_cwock, caps);
	stwuct ixp46x_ts_wegs *wegs = ixp_cwock->wegs;

	spin_wock_iwqsave(&wegistew_wock, fwags);

	now = ixp_systime_wead(wegs);
	now += dewta;
	ixp_systime_wwite(wegs, now);

	spin_unwock_iwqwestowe(&wegistew_wock, fwags);

	wetuwn 0;
}

static int ptp_ixp_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	u64 ns;
	unsigned wong fwags;
	stwuct ixp_cwock *ixp_cwock = containew_of(ptp, stwuct ixp_cwock, caps);
	stwuct ixp46x_ts_wegs *wegs = ixp_cwock->wegs;

	spin_wock_iwqsave(&wegistew_wock, fwags);

	ns = ixp_systime_wead(wegs);

	spin_unwock_iwqwestowe(&wegistew_wock, fwags);

	*ts = ns_to_timespec64(ns);
	wetuwn 0;
}

static int ptp_ixp_settime(stwuct ptp_cwock_info *ptp,
			   const stwuct timespec64 *ts)
{
	u64 ns;
	unsigned wong fwags;
	stwuct ixp_cwock *ixp_cwock = containew_of(ptp, stwuct ixp_cwock, caps);
	stwuct ixp46x_ts_wegs *wegs = ixp_cwock->wegs;

	ns = timespec64_to_ns(ts);

	spin_wock_iwqsave(&wegistew_wock, fwags);

	ixp_systime_wwite(wegs, ns);

	spin_unwock_iwqwestowe(&wegistew_wock, fwags);

	wetuwn 0;
}

static int ptp_ixp_enabwe(stwuct ptp_cwock_info *ptp,
			  stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct ixp_cwock *ixp_cwock = containew_of(ptp, stwuct ixp_cwock, caps);

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		switch (wq->extts.index) {
		case 0:
			ixp_cwock->exts0_enabwed = on ? 1 : 0;
			bweak;
		case 1:
			ixp_cwock->exts1_enabwed = on ? 1 : 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct ptp_cwock_info ptp_ixp_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "IXP46X timew",
	.max_adj	= 66666655,
	.n_ext_ts	= N_EXT_TS,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= ptp_ixp_adjfine,
	.adjtime	= ptp_ixp_adjtime,
	.gettime64	= ptp_ixp_gettime,
	.settime64	= ptp_ixp_settime,
	.enabwe		= ptp_ixp_enabwe,
};

/* moduwe opewations */

static stwuct ixp_cwock ixp_cwock;

int ixp46x_ptp_find(stwuct ixp46x_ts_wegs *__iomem *wegs, int *phc_index)
{
	*wegs = ixp_cwock.wegs;
	*phc_index = ptp_cwock_index(ixp_cwock.ptp_cwock);

	if (!ixp_cwock.ptp_cwock)
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ixp46x_ptp_find);

/* Cawwed fwom the wegistewed devm action */
static void ptp_ixp_unwegistew_action(void *d)
{
	stwuct ptp_cwock *ptp_cwock = d;

	ptp_cwock_unwegistew(ptp_cwock);
	ixp_cwock.ptp_cwock = NUWW;
}

static int ptp_ixp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	ixp_cwock.wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	ixp_cwock.mastew_iwq = pwatfowm_get_iwq(pdev, 0);
	ixp_cwock.swave_iwq = pwatfowm_get_iwq(pdev, 1);
	if (IS_EWW(ixp_cwock.wegs) ||
	    ixp_cwock.mastew_iwq < 0 || ixp_cwock.swave_iwq < 0)
		wetuwn -ENXIO;

	ixp_cwock.caps = ptp_ixp_caps;

	ixp_cwock.ptp_cwock = ptp_cwock_wegistew(&ixp_cwock.caps, NUWW);

	if (IS_EWW(ixp_cwock.ptp_cwock))
		wetuwn PTW_EWW(ixp_cwock.ptp_cwock);

	wet = devm_add_action_ow_weset(dev, ptp_ixp_unwegistew_action,
				       ixp_cwock.ptp_cwock);
	if (wet) {
		dev_eww(dev, "faiwed to instaww cwock wemovaw handwew\n");
		wetuwn wet;
	}

	__waw_wwitew(DEFAUWT_ADDEND, &ixp_cwock.wegs->addend);
	__waw_wwitew(1, &ixp_cwock.wegs->twgt_wo);
	__waw_wwitew(0, &ixp_cwock.wegs->twgt_hi);
	__waw_wwitew(TTIPEND, &ixp_cwock.wegs->event);

	wet = devm_wequest_iwq(dev, ixp_cwock.mastew_iwq, isw,
			       0, DWIVEW, &ixp_cwock);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "wequest_iwq faiwed fow iwq %d\n",
				     ixp_cwock.mastew_iwq);

	wet = devm_wequest_iwq(dev, ixp_cwock.swave_iwq, isw,
			       0, DWIVEW, &ixp_cwock);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "wequest_iwq faiwed fow iwq %d\n",
				     ixp_cwock.swave_iwq);

	wetuwn 0;
}

static const stwuct of_device_id ptp_ixp_match[] = {
	{
		.compatibwe = "intew,ixp46x-ptp-timew",
	},
	{ },
};

static stwuct pwatfowm_dwivew ptp_ixp_dwivew = {
	.dwivew = {
		.name = "ptp-ixp46x",
		.of_match_tabwe = ptp_ixp_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = ptp_ixp_pwobe,
};
moduwe_pwatfowm_dwivew(ptp_ixp_dwivew);

MODUWE_AUTHOW("Wichawd Cochwan <wichawdcochwan@gmaiw.com>");
MODUWE_DESCWIPTION("PTP cwock using the IXP46X timew");
MODUWE_WICENSE("GPW");
