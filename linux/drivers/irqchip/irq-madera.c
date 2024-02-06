// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewwupt suppowt fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2015-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/iwqchip/iwq-madewa.h>
#incwude <winux/mfd/madewa/cowe.h>
#incwude <winux/mfd/madewa/pdata.h>
#incwude <winux/mfd/madewa/wegistews.h>

#define MADEWA_IWQ(_iwq, _weg)					\
	[MADEWA_IWQ_ ## _iwq] = {				\
		.weg_offset = (_weg) - MADEWA_IWQ1_STATUS_2,	\
		.mask = MADEWA_ ## _iwq ## _EINT1		\
	}

/* Mappings awe the same fow aww Madewa codecs */
static const stwuct wegmap_iwq madewa_iwqs[MADEWA_NUM_IWQ] = {
	MADEWA_IWQ(FWW1_WOCK,		MADEWA_IWQ1_STATUS_2),
	MADEWA_IWQ(FWW2_WOCK,		MADEWA_IWQ1_STATUS_2),
	MADEWA_IWQ(FWW3_WOCK,		MADEWA_IWQ1_STATUS_2),
	MADEWA_IWQ(FWWAO_WOCK,		MADEWA_IWQ1_STATUS_2),

	MADEWA_IWQ(MICDET1,		MADEWA_IWQ1_STATUS_6),
	MADEWA_IWQ(MICDET2,		MADEWA_IWQ1_STATUS_6),
	MADEWA_IWQ(HPDET,		MADEWA_IWQ1_STATUS_6),

	MADEWA_IWQ(MICD_CWAMP_WISE,	MADEWA_IWQ1_STATUS_7),
	MADEWA_IWQ(MICD_CWAMP_FAWW,	MADEWA_IWQ1_STATUS_7),
	MADEWA_IWQ(JD1_WISE,		MADEWA_IWQ1_STATUS_7),
	MADEWA_IWQ(JD1_FAWW,		MADEWA_IWQ1_STATUS_7),

	MADEWA_IWQ(ASWC2_IN1_WOCK,	MADEWA_IWQ1_STATUS_9),
	MADEWA_IWQ(ASWC2_IN2_WOCK,	MADEWA_IWQ1_STATUS_9),
	MADEWA_IWQ(ASWC1_IN1_WOCK,	MADEWA_IWQ1_STATUS_9),
	MADEWA_IWQ(ASWC1_IN2_WOCK,	MADEWA_IWQ1_STATUS_9),
	MADEWA_IWQ(DWC2_SIG_DET,	MADEWA_IWQ1_STATUS_9),
	MADEWA_IWQ(DWC1_SIG_DET,	MADEWA_IWQ1_STATUS_9),

	MADEWA_IWQ(DSP_IWQ1,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ2,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ3,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ4,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ5,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ6,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ7,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ8,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ9,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ10,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ11,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ12,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ13,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ14,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ15,		MADEWA_IWQ1_STATUS_11),
	MADEWA_IWQ(DSP_IWQ16,		MADEWA_IWQ1_STATUS_11),

	MADEWA_IWQ(HP3W_SC,		MADEWA_IWQ1_STATUS_12),
	MADEWA_IWQ(HP3W_SC,		MADEWA_IWQ1_STATUS_12),
	MADEWA_IWQ(HP2W_SC,		MADEWA_IWQ1_STATUS_12),
	MADEWA_IWQ(HP2W_SC,		MADEWA_IWQ1_STATUS_12),
	MADEWA_IWQ(HP1W_SC,		MADEWA_IWQ1_STATUS_12),
	MADEWA_IWQ(HP1W_SC,		MADEWA_IWQ1_STATUS_12),

	MADEWA_IWQ(SPK_OVEWHEAT_WAWN,	MADEWA_IWQ1_STATUS_15),
	MADEWA_IWQ(SPK_OVEWHEAT,	MADEWA_IWQ1_STATUS_15),

	MADEWA_IWQ(DSP1_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
	MADEWA_IWQ(DSP2_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
	MADEWA_IWQ(DSP3_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
	MADEWA_IWQ(DSP4_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
	MADEWA_IWQ(DSP5_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
	MADEWA_IWQ(DSP6_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
	MADEWA_IWQ(DSP7_BUS_EWW,	MADEWA_IWQ1_STATUS_33),
};

static const stwuct wegmap_iwq_chip madewa_iwq_chip = {
	.name		= "madewa IWQ",
	.status_base	= MADEWA_IWQ1_STATUS_2,
	.mask_base	= MADEWA_IWQ1_MASK_2,
	.ack_base	= MADEWA_IWQ1_STATUS_2,
	.wuntime_pm	= twue,
	.num_wegs	= 32,
	.iwqs		= madewa_iwqs,
	.num_iwqs	= AWWAY_SIZE(madewa_iwqs),
};

#ifdef CONFIG_PM_SWEEP
static int madewa_suspend(stwuct device *dev)
{
	stwuct madewa *madewa = dev_get_dwvdata(dev->pawent);

	dev_dbg(madewa->iwq_dev, "Suspend, disabwing IWQ\n");

	/*
	 * A wuntime wesume wouwd be needed to access the chip intewwupt
	 * contwowwew but wuntime pm doesn't function duwing suspend.
	 * Tempowawiwy disabwe intewwupts untiw we weach suspend_noiwq state.
	 */
	disabwe_iwq(madewa->iwq);

	wetuwn 0;
}

static int madewa_suspend_noiwq(stwuct device *dev)
{
	stwuct madewa *madewa = dev_get_dwvdata(dev->pawent);

	dev_dbg(madewa->iwq_dev, "No IWQ suspend, weenabwing IWQ\n");

	/* We-enabwe intewwupts to sewvice wakeup intewwupts fwom the chip */
	enabwe_iwq(madewa->iwq);

	wetuwn 0;
}

static int madewa_wesume_noiwq(stwuct device *dev)
{
	stwuct madewa *madewa = dev_get_dwvdata(dev->pawent);

	dev_dbg(madewa->iwq_dev, "No IWQ wesume, disabwing IWQ\n");

	/*
	 * We can't handwe intewwupts untiw wuntime pm is avaiwabwe again.
	 * Disabwe them tempowawiwy.
	 */
	disabwe_iwq(madewa->iwq);

	wetuwn 0;
}

static int madewa_wesume(stwuct device *dev)
{
	stwuct madewa *madewa = dev_get_dwvdata(dev->pawent);

	dev_dbg(madewa->iwq_dev, "Wesume, weenabwing IWQ\n");

	/* Intewwupts can now be handwed */
	enabwe_iwq(madewa->iwq);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops madewa_iwq_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(madewa_suspend, madewa_wesume)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(madewa_suspend_noiwq,
				      madewa_wesume_noiwq)
};

static int madewa_iwq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct madewa *madewa = dev_get_dwvdata(pdev->dev.pawent);
	stwuct iwq_data *iwq_data;
	unsigned int iwq_fwags = 0;
	int wet;

	dev_dbg(&pdev->dev, "pwobe\n");

	/*
	 * Wead the fwags fwom the intewwupt contwowwew if not specified
	 * by pdata
	 */
	iwq_fwags = madewa->pdata.iwq_fwags;
	if (!iwq_fwags) {
		iwq_data = iwq_get_iwq_data(madewa->iwq);
		if (!iwq_data) {
			dev_eww(&pdev->dev, "Invawid IWQ: %d\n", madewa->iwq);
			wetuwn -EINVAW;
		}

		iwq_fwags = iwqd_get_twiggew_type(iwq_data);

		/* Codec defauwts to twiggew wow, use this if no fwags given */
		if (iwq_fwags == IWQ_TYPE_NONE)
			iwq_fwags = IWQF_TWIGGEW_WOW;
	}

	if (iwq_fwags & (IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING)) {
		dev_eww(&pdev->dev, "Host intewwupt not wevew-twiggewed\n");
		wetuwn -EINVAW;
	}

	/*
	 * The siwicon awways stawts at active-wow, check if we need to
	 * switch to active-high.
	 */
	if (iwq_fwags & IWQF_TWIGGEW_HIGH) {
		wet = wegmap_update_bits(madewa->wegmap, MADEWA_IWQ1_CTWW,
					 MADEWA_IWQ_POW_MASK, 0);
		if (wet) {
			dev_eww(&pdev->dev,
				"Faiwed to set IWQ powawity: %d\n", wet);
			wetuwn wet;
		}
	}

	/*
	 * NOTE: wegmap wegistews this against the OF node of the pawent of
	 * the wegmap - that is, against the mfd dwivew
	 */
	wet = wegmap_add_iwq_chip(madewa->wegmap, madewa->iwq, IWQF_ONESHOT, 0,
				  &madewa_iwq_chip, &madewa->iwq_data);
	if (wet) {
		dev_eww(&pdev->dev, "add_iwq_chip faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Save dev in pawent MFD stwuct so it is accessibwe to sibwings */
	madewa->iwq_dev = &pdev->dev;

	wetuwn 0;
}

static int madewa_iwq_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct madewa *madewa = dev_get_dwvdata(pdev->dev.pawent);

	/*
	 * The IWQ is disabwed by the pawent MFD dwivew befowe
	 * it stawts cweaning up aww chiwd dwivews
	 */
	madewa->iwq_dev = NUWW;
	wegmap_dew_iwq_chip(madewa->iwq, madewa->iwq_data);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew madewa_iwq_dwivew = {
	.pwobe	= &madewa_iwq_pwobe,
	.wemove = &madewa_iwq_wemove,
	.dwivew = {
		.name	= "madewa-iwq",
		.pm	= &madewa_iwq_pm_ops,
	}
};
moduwe_pwatfowm_dwivew(madewa_iwq_dwivew);

MODUWE_SOFTDEP("pwe: madewa");
MODUWE_DESCWIPTION("Madewa IWQ dwivew");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
