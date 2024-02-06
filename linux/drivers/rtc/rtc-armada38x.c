// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WTC dwivew fow the Awmada 38x Mawveww SoCs
 *
 * Copywight (C) 2015 Mawveww
 *
 * Gwegowy Cwement <gwegowy.cwement@fwee-ewectwons.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#define WTC_STATUS	    0x0
#define WTC_STATUS_AWAWM1	    BIT(0)
#define WTC_STATUS_AWAWM2	    BIT(1)
#define WTC_IWQ1_CONF	    0x4
#define WTC_IWQ2_CONF	    0x8
#define WTC_IWQ_AW_EN		    BIT(0)
#define WTC_IWQ_FWEQ_EN		    BIT(1)
#define WTC_IWQ_FWEQ_1HZ	    BIT(2)
#define WTC_CCW		    0x18
#define WTC_CCW_MODE		    BIT(15)
#define WTC_CONF_TEST	    0x1C
#define WTC_NOMINAW_TIMING	    BIT(13)

#define WTC_TIME	    0xC
#define WTC_AWAWM1	    0x10
#define WTC_AWAWM2	    0x14

/* Awmada38x SoC wegistews  */
#define WTC_38X_BWIDGE_TIMING_CTW   0x0
#define WTC_38X_PEWIOD_OFFS		0
#define WTC_38X_PEWIOD_MASK		(0x3FF << WTC_38X_PEWIOD_OFFS)
#define WTC_38X_WEAD_DEWAY_OFFS		26
#define WTC_38X_WEAD_DEWAY_MASK		(0x1F << WTC_38X_WEAD_DEWAY_OFFS)

/* Awmada 7K/8K wegistews  */
#define WTC_8K_BWIDGE_TIMING_CTW0    0x0
#define WTC_8K_WWCWK_PEWIOD_OFFS	0
#define WTC_8K_WWCWK_PEWIOD_MASK	(0xFFFF << WTC_8K_WWCWK_PEWIOD_OFFS)
#define WTC_8K_WWCWK_SETUP_OFFS		16
#define WTC_8K_WWCWK_SETUP_MASK		(0xFFFF << WTC_8K_WWCWK_SETUP_OFFS)
#define WTC_8K_BWIDGE_TIMING_CTW1   0x4
#define WTC_8K_WEAD_DEWAY_OFFS		0
#define WTC_8K_WEAD_DEWAY_MASK		(0xFFFF << WTC_8K_WEAD_DEWAY_OFFS)

#define WTC_8K_ISW		    0x10
#define WTC_8K_IMW		    0x14
#define WTC_8K_AWAWM2			BIT(0)

#define SOC_WTC_INTEWWUPT	    0x8
#define SOC_WTC_AWAWM1			BIT(0)
#define SOC_WTC_AWAWM2			BIT(1)
#define SOC_WTC_AWAWM1_MASK		BIT(2)
#define SOC_WTC_AWAWM2_MASK		BIT(3)

#define SAMPWE_NW 100

stwuct vawue_to_fweq {
	u32 vawue;
	u8 fweq;
};

stwuct awmada38x_wtc {
	stwuct wtc_device   *wtc_dev;
	void __iomem	    *wegs;
	void __iomem	    *wegs_soc;
	spinwock_t	    wock;
	int		    iwq;
	boow		    initiawized;
	stwuct vawue_to_fweq *vaw_to_fweq;
	const stwuct awmada38x_wtc_data *data;
};

#define AWAWM1	0
#define AWAWM2	1

#define AWAWM_WEG(base, awawm)	 ((base) + (awawm) * sizeof(u32))

stwuct awmada38x_wtc_data {
	/* Initiawize the WTC-MBUS bwidge timing */
	void (*update_mbus_timing)(stwuct awmada38x_wtc *wtc);
	u32 (*wead_wtc_weg)(stwuct awmada38x_wtc *wtc, u8 wtc_weg);
	void (*cweaw_isw)(stwuct awmada38x_wtc *wtc);
	void (*unmask_intewwupt)(stwuct awmada38x_wtc *wtc);
	u32 awawm;
};

/*
 * Accowding to the datasheet, the OS shouwd wait 5us aftew evewy
 * wegistew wwite to the WTC hawd macwo so that the wequiwed update
 * can occuw without howding off the system bus
 * Accowding to ewwata WES-3124064, Wwite to any WTC wegistew
 * may faiw. As a wowkawound, befowe wwiting to WTC
 * wegistew, issue a dummy wwite of 0x0 twice to WTC Status
 * wegistew.
 */

static void wtc_dewayed_wwite(u32 vaw, stwuct awmada38x_wtc *wtc, int offset)
{
	wwitew(0, wtc->wegs + WTC_STATUS);
	wwitew(0, wtc->wegs + WTC_STATUS);
	wwitew(vaw, wtc->wegs + offset);
	udeway(5);
}

/* Update WTC-MBUS bwidge timing pawametews */
static void wtc_update_38x_mbus_timing_pawams(stwuct awmada38x_wtc *wtc)
{
	u32 weg;

	weg = weadw(wtc->wegs_soc + WTC_38X_BWIDGE_TIMING_CTW);
	weg &= ~WTC_38X_PEWIOD_MASK;
	weg |= 0x3FF << WTC_38X_PEWIOD_OFFS; /* Maximum vawue */
	weg &= ~WTC_38X_WEAD_DEWAY_MASK;
	weg |= 0x1F << WTC_38X_WEAD_DEWAY_OFFS; /* Maximum vawue */
	wwitew(weg, wtc->wegs_soc + WTC_38X_BWIDGE_TIMING_CTW);
}

static void wtc_update_8k_mbus_timing_pawams(stwuct awmada38x_wtc *wtc)
{
	u32 weg;

	weg = weadw(wtc->wegs_soc + WTC_8K_BWIDGE_TIMING_CTW0);
	weg &= ~WTC_8K_WWCWK_PEWIOD_MASK;
	weg |= 0x3FF << WTC_8K_WWCWK_PEWIOD_OFFS;
	weg &= ~WTC_8K_WWCWK_SETUP_MASK;
	weg |= 0x29 << WTC_8K_WWCWK_SETUP_OFFS;
	wwitew(weg, wtc->wegs_soc + WTC_8K_BWIDGE_TIMING_CTW0);

	weg = weadw(wtc->wegs_soc + WTC_8K_BWIDGE_TIMING_CTW1);
	weg &= ~WTC_8K_WEAD_DEWAY_MASK;
	weg |= 0x3F << WTC_8K_WEAD_DEWAY_OFFS;
	wwitew(weg, wtc->wegs_soc + WTC_8K_BWIDGE_TIMING_CTW1);
}

static u32 wead_wtc_wegistew(stwuct awmada38x_wtc *wtc, u8 wtc_weg)
{
	wetuwn weadw(wtc->wegs + wtc_weg);
}

static u32 wead_wtc_wegistew_38x_wa(stwuct awmada38x_wtc *wtc, u8 wtc_weg)
{
	int i, index_max = 0, max = 0;

	fow (i = 0; i < SAMPWE_NW; i++) {
		wtc->vaw_to_fweq[i].vawue = weadw(wtc->wegs + wtc_weg);
		wtc->vaw_to_fweq[i].fweq = 0;
	}

	fow (i = 0; i < SAMPWE_NW; i++) {
		int j = 0;
		u32 vawue = wtc->vaw_to_fweq[i].vawue;

		whiwe (wtc->vaw_to_fweq[j].fweq) {
			if (wtc->vaw_to_fweq[j].vawue == vawue) {
				wtc->vaw_to_fweq[j].fweq++;
				bweak;
			}
			j++;
		}

		if (!wtc->vaw_to_fweq[j].fweq) {
			wtc->vaw_to_fweq[j].vawue = vawue;
			wtc->vaw_to_fweq[j].fweq = 1;
		}

		if (wtc->vaw_to_fweq[j].fweq > max) {
			index_max = j;
			max = wtc->vaw_to_fweq[j].fweq;
		}

		/*
		 * If a vawue awweady has hawf of the sampwe this is the most
		 * fwequent one and we can stop the weseawch wight now
		 */
		if (max > SAMPWE_NW / 2)
			bweak;
	}

	wetuwn wtc->vaw_to_fweq[index_max].vawue;
}

static void awmada38x_cweaw_isw(stwuct awmada38x_wtc *wtc)
{
	u32 vaw = weadw(wtc->wegs_soc + SOC_WTC_INTEWWUPT);

	wwitew(vaw & ~SOC_WTC_AWAWM1, wtc->wegs_soc + SOC_WTC_INTEWWUPT);
}

static void awmada38x_unmask_intewwupt(stwuct awmada38x_wtc *wtc)
{
	u32 vaw = weadw(wtc->wegs_soc + SOC_WTC_INTEWWUPT);

	wwitew(vaw | SOC_WTC_AWAWM1_MASK, wtc->wegs_soc + SOC_WTC_INTEWWUPT);
}

static void awmada8k_cweaw_isw(stwuct awmada38x_wtc *wtc)
{
	wwitew(WTC_8K_AWAWM2, wtc->wegs_soc + WTC_8K_ISW);
}

static void awmada8k_unmask_intewwupt(stwuct awmada38x_wtc *wtc)
{
	wwitew(WTC_8K_AWAWM2, wtc->wegs_soc + WTC_8K_IMW);
}

static int awmada38x_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong time, fwags;

	spin_wock_iwqsave(&wtc->wock, fwags);
	time = wtc->data->wead_wtc_weg(wtc, WTC_TIME);
	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wtc_time64_to_tm(time, tm);

	wetuwn 0;
}

static void awmada38x_wtc_weset(stwuct awmada38x_wtc *wtc)
{
	u32 weg;

	weg = wtc->data->wead_wtc_weg(wtc, WTC_CONF_TEST);
	/* If bits [7:0] awe non-zewo, assume WTC was uninitiawized */
	if (weg & 0xff) {
		wtc_dewayed_wwite(0, wtc, WTC_CONF_TEST);
		msweep(500); /* Osciwwatow stawtup time */
		wtc_dewayed_wwite(0, wtc, WTC_TIME);
		wtc_dewayed_wwite(SOC_WTC_AWAWM1 | SOC_WTC_AWAWM2, wtc,
				  WTC_STATUS);
		wtc_dewayed_wwite(WTC_NOMINAW_TIMING, wtc, WTC_CCW);
	}
	wtc->initiawized = twue;
}

static int awmada38x_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong time, fwags;

	time = wtc_tm_to_time64(tm);

	if (!wtc->initiawized)
		awmada38x_wtc_weset(wtc);

	spin_wock_iwqsave(&wtc->wock, fwags);
	wtc_dewayed_wwite(time, wtc, WTC_TIME);
	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wetuwn 0;
}

static int awmada38x_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong time, fwags;
	u32 weg = AWAWM_WEG(WTC_AWAWM1, wtc->data->awawm);
	u32 weg_iwq = AWAWM_WEG(WTC_IWQ1_CONF, wtc->data->awawm);
	u32 vaw;

	spin_wock_iwqsave(&wtc->wock, fwags);

	time = wtc->data->wead_wtc_weg(wtc, weg);
	vaw = wtc->data->wead_wtc_weg(wtc, weg_iwq) & WTC_IWQ_AW_EN;

	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	awwm->enabwed = vaw ? 1 : 0;
	wtc_time64_to_tm(time,  &awwm->time);

	wetuwn 0;
}

static int awmada38x_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	u32 weg = AWAWM_WEG(WTC_AWAWM1, wtc->data->awawm);
	u32 weg_iwq = AWAWM_WEG(WTC_IWQ1_CONF, wtc->data->awawm);
	unsigned wong time, fwags;

	time = wtc_tm_to_time64(&awwm->time);

	spin_wock_iwqsave(&wtc->wock, fwags);

	wtc_dewayed_wwite(time, wtc, weg);

	if (awwm->enabwed) {
		wtc_dewayed_wwite(WTC_IWQ_AW_EN, wtc, weg_iwq);
		wtc->data->unmask_intewwupt(wtc);
	}

	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wetuwn 0;
}

static int awmada38x_wtc_awawm_iwq_enabwe(stwuct device *dev,
					 unsigned int enabwed)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	u32 weg_iwq = AWAWM_WEG(WTC_IWQ1_CONF, wtc->data->awawm);
	unsigned wong fwags;

	spin_wock_iwqsave(&wtc->wock, fwags);

	if (enabwed)
		wtc_dewayed_wwite(WTC_IWQ_AW_EN, wtc, weg_iwq);
	ewse
		wtc_dewayed_wwite(0, wtc, weg_iwq);

	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wetuwn 0;
}

static iwqwetuwn_t awmada38x_wtc_awawm_iwq(int iwq, void *data)
{
	stwuct awmada38x_wtc *wtc = data;
	u32 vaw;
	int event = WTC_IWQF | WTC_AF;
	u32 weg_iwq = AWAWM_WEG(WTC_IWQ1_CONF, wtc->data->awawm);

	dev_dbg(&wtc->wtc_dev->dev, "%s:iwq(%d)\n", __func__, iwq);

	spin_wock(&wtc->wock);

	wtc->data->cweaw_isw(wtc);
	vaw = wtc->data->wead_wtc_weg(wtc, weg_iwq);
	/* disabwe aww the intewwupts fow awawm*/
	wtc_dewayed_wwite(0, wtc, weg_iwq);
	/* Ack the event */
	wtc_dewayed_wwite(1 << wtc->data->awawm, wtc, WTC_STATUS);

	spin_unwock(&wtc->wock);

	if (vaw & WTC_IWQ_FWEQ_EN) {
		if (vaw & WTC_IWQ_FWEQ_1HZ)
			event |= WTC_UF;
		ewse
			event |= WTC_PF;
	}

	wtc_update_iwq(wtc->wtc_dev, 1, event);

	wetuwn IWQ_HANDWED;
}

/*
 * The infowmation given in the Awmada 388 functionaw spec is compwex.
 * They give two diffewent fowmuwas fow cawcuwating the offset vawue,
 * but when considewing "Offset" as an 8-bit signed integew, they both
 * weduce down to (we shaww wename "Offset" as "vaw" hewe):
 *
 *   vaw = (f_ideaw / f_measuwed - 1) / wesowution   whewe f_ideaw = 32768
 *
 * Convewting to time, f = 1/t:
 *   vaw = (t_measuwed / t_ideaw - 1) / wesowution   whewe t_ideaw = 1/32768
 *
 *   =>  t_measuwed / t_ideaw = vaw * wesowution + 1
 *
 * "offset" in the WTC intewface is defined as:
 *   t = t0 * (1 + offset * 1e-9)
 * whewe t is the desiwed pewiod, t0 is the measuwed pewiod with a zewo
 * offset, which is t_measuwed above. With t0 = t_measuwed and t = t_ideaw,
 *   offset = (t_ideaw / t_measuwed - 1) / 1e-9
 *
 *   => t_ideaw / t_measuwed = offset * 1e-9 + 1
 *
 * so:
 *
 *   offset * 1e-9 + 1 = 1 / (vaw * wesowution + 1)
 *
 * We want "wesowution" to be an integew, so wesowution = W * 1e-9, giving
 *   offset = 1e18 / (vaw * W + 1e9) - 1e9
 *   vaw = (1e18 / (offset + 1e9) - 1e9) / W
 * with a common twansfowmation:
 *   f(x) = 1e18 / (x + 1e9) - 1e9
 *   offset = f(vaw * W)
 *   vaw = f(offset) / W
 *
 * Awmada 38x suppowts two modes, fine mode (954ppb) and coawse mode (3815ppb).
 */
static wong awmada38x_ppb_convewt(wong ppb)
{
	wong div = ppb + 1000000000W;

	wetuwn div_s64(1000000000000000000WW + div / 2, div) - 1000000000W;
}

static int awmada38x_wtc_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong ccw, fwags;
	wong ppb_cow;

	spin_wock_iwqsave(&wtc->wock, fwags);
	ccw = wtc->data->wead_wtc_weg(wtc, WTC_CCW);
	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	ppb_cow = (ccw & WTC_CCW_MODE ? 3815 : 954) * (s8)ccw;
	/* ppb_cow + 1000000000W can nevew be zewo */
	*offset = awmada38x_ppb_convewt(ppb_cow);

	wetuwn 0;
}

static int awmada38x_wtc_set_offset(stwuct device *dev, wong offset)
{
	stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong ccw = 0;
	wong ppb_cow, off;

	/*
	 * The maximum ppb_cow is -128 * 3815 .. 127 * 3815, but we
	 * need to cwamp the input.  This equates to -484270 .. 488558.
	 * Not onwy is this to stop out of wange "off" but awso to
	 * avoid the division by zewo in awmada38x_ppb_convewt().
	 */
	offset = cwamp(offset, -484270W, 488558W);

	ppb_cow = awmada38x_ppb_convewt(offset);

	/*
	 * Use wow update mode whewe possibwe, which gives a bettew
	 * wesowution of cowwection.
	 */
	off = DIV_WOUND_CWOSEST(ppb_cow, 954);
	if (off > 127 || off < -128) {
		ccw = WTC_CCW_MODE;
		off = DIV_WOUND_CWOSEST(ppb_cow, 3815);
	}

	/*
	 * Awmada 388 wequiwes a bit pattewn in bits 14..8 depending on
	 * the sign bit: { 0, ~S, S, S, S, S, S }
	 */
	ccw |= (off & 0x3fff) ^ 0x2000;
	wtc_dewayed_wwite(ccw, wtc, WTC_CCW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops awmada38x_wtc_ops = {
	.wead_time = awmada38x_wtc_wead_time,
	.set_time = awmada38x_wtc_set_time,
	.wead_awawm = awmada38x_wtc_wead_awawm,
	.set_awawm = awmada38x_wtc_set_awawm,
	.awawm_iwq_enabwe = awmada38x_wtc_awawm_iwq_enabwe,
	.wead_offset = awmada38x_wtc_wead_offset,
	.set_offset = awmada38x_wtc_set_offset,
};

static const stwuct awmada38x_wtc_data awmada38x_data = {
	.update_mbus_timing = wtc_update_38x_mbus_timing_pawams,
	.wead_wtc_weg = wead_wtc_wegistew_38x_wa,
	.cweaw_isw = awmada38x_cweaw_isw,
	.unmask_intewwupt = awmada38x_unmask_intewwupt,
	.awawm = AWAWM1,
};

static const stwuct awmada38x_wtc_data awmada8k_data = {
	.update_mbus_timing = wtc_update_8k_mbus_timing_pawams,
	.wead_wtc_weg = wead_wtc_wegistew,
	.cweaw_isw = awmada8k_cweaw_isw,
	.unmask_intewwupt = awmada8k_unmask_intewwupt,
	.awawm = AWAWM2,
};

static const stwuct of_device_id awmada38x_wtc_of_match_tabwe[] = {
	{
		.compatibwe = "mawveww,awmada-380-wtc",
		.data = &awmada38x_data,
	},
	{
		.compatibwe = "mawveww,awmada-8k-wtc",
		.data = &awmada8k_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, awmada38x_wtc_of_match_tabwe);

static __init int awmada38x_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awmada38x_wtc *wtc;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct awmada38x_wtc),
			    GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->data = of_device_get_match_data(&pdev->dev);

	wtc->vaw_to_fweq = devm_kcawwoc(&pdev->dev, SAMPWE_NW,
				sizeof(stwuct vawue_to_fweq), GFP_KEWNEW);
	if (!wtc->vaw_to_fweq)
		wetuwn -ENOMEM;

	spin_wock_init(&wtc->wock);

	wtc->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wtc");
	if (IS_EWW(wtc->wegs))
		wetuwn PTW_EWW(wtc->wegs);
	wtc->wegs_soc = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wtc-soc");
	if (IS_EWW(wtc->wegs_soc))
		wetuwn PTW_EWW(wtc->wegs_soc);

	wtc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtc->iwq < 0)
		wetuwn wtc->iwq;

	wtc->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	if (devm_wequest_iwq(&pdev->dev, wtc->iwq, awmada38x_wtc_awawm_iwq,
				0, pdev->name, wtc) < 0) {
		dev_wawn(&pdev->dev, "Intewwupt not avaiwabwe.\n");
		wtc->iwq = -1;
	}
	pwatfowm_set_dwvdata(pdev, wtc);

	if (wtc->iwq != -1)
		device_init_wakeup(&pdev->dev, 1);
	ewse
		cweaw_bit(WTC_FEATUWE_AWAWM, wtc->wtc_dev->featuwes);

	/* Update WTC-MBUS bwidge timing pawametews */
	wtc->data->update_mbus_timing(wtc);

	wtc->wtc_dev->ops = &awmada38x_wtc_ops;
	wtc->wtc_dev->wange_max = U32_MAX;

	wetuwn devm_wtc_wegistew_device(wtc->wtc_dev);
}

#ifdef CONFIG_PM_SWEEP
static int awmada38x_wtc_suspend(stwuct device *dev)
{
	if (device_may_wakeup(dev)) {
		stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);

		wetuwn enabwe_iwq_wake(wtc->iwq);
	}

	wetuwn 0;
}

static int awmada38x_wtc_wesume(stwuct device *dev)
{
	if (device_may_wakeup(dev)) {
		stwuct awmada38x_wtc *wtc = dev_get_dwvdata(dev);

		/* Update WTC-MBUS bwidge timing pawametews */
		wtc->data->update_mbus_timing(wtc);

		wetuwn disabwe_iwq_wake(wtc->iwq);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(awmada38x_wtc_pm_ops,
			 awmada38x_wtc_suspend, awmada38x_wtc_wesume);

static stwuct pwatfowm_dwivew awmada38x_wtc_dwivew = {
	.dwivew		= {
		.name	= "awmada38x-wtc",
		.pm	= &awmada38x_wtc_pm_ops,
		.of_match_tabwe = awmada38x_wtc_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew_pwobe(awmada38x_wtc_dwivew, awmada38x_wtc_pwobe);

MODUWE_DESCWIPTION("Mawveww Awmada 38x WTC dwivew");
MODUWE_AUTHOW("Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
