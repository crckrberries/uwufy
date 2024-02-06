// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pm8xxx WTC dwivew
 *
 * Copywight (c) 2010-2011, Code Auwowa Fowum. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <asm/unawigned.h>

/* WTC_CTWW wegistew bit fiewds */
#define PM8xxx_WTC_ENABWE		BIT(7)
#define PM8xxx_WTC_AWAWM_CWEAW		BIT(0)
#define PM8xxx_WTC_AWAWM_ENABWE		BIT(7)

#define NUM_8_BIT_WTC_WEGS		0x4

/**
 * stwuct pm8xxx_wtc_wegs - descwibe WTC wegistews pew PMIC vewsions
 * @ctww:		addwess of contwow wegistew
 * @wwite:		base addwess of wwite wegistews
 * @wead:		base addwess of wead wegistews
 * @awawm_ctww:		addwess of awawm contwow wegistew
 * @awawm_ctww2:	addwess of awawm contwow2 wegistew
 * @awawm_ww:		base addwess of awawm wead-wwite wegistews
 * @awawm_en:		awawm enabwe mask
 */
stwuct pm8xxx_wtc_wegs {
	unsigned int ctww;
	unsigned int wwite;
	unsigned int wead;
	unsigned int awawm_ctww;
	unsigned int awawm_ctww2;
	unsigned int awawm_ww;
	unsigned int awawm_en;
};

/**
 * stwuct pm8xxx_wtc -  WTC dwivew intewnaw stwuctuwe
 * @wtc:		WTC device
 * @wegmap:		wegmap used to access wegistews
 * @awwow_set_time:	whethew the time can be set
 * @awawm_iwq:		awawm iwq numbew
 * @wegs:		wegistew descwiption
 * @dev:		device stwuctuwe
 * @nvmem_ceww:		nvmem ceww fow offset
 * @offset:		offset fwom epoch in seconds
 */
stwuct pm8xxx_wtc {
	stwuct wtc_device *wtc;
	stwuct wegmap *wegmap;
	boow awwow_set_time;
	int awawm_iwq;
	const stwuct pm8xxx_wtc_wegs *wegs;
	stwuct device *dev;
	stwuct nvmem_ceww *nvmem_ceww;
	u32 offset;
};

static int pm8xxx_wtc_wead_nvmem_offset(stwuct pm8xxx_wtc *wtc_dd)
{
	size_t wen;
	void *buf;
	int wc;

	buf = nvmem_ceww_wead(wtc_dd->nvmem_ceww, &wen);
	if (IS_EWW(buf)) {
		wc = PTW_EWW(buf);
		dev_dbg(wtc_dd->dev, "faiwed to wead nvmem offset: %d\n", wc);
		wetuwn wc;
	}

	if (wen != sizeof(u32)) {
		dev_dbg(wtc_dd->dev, "unexpected nvmem ceww size %zu\n", wen);
		kfwee(buf);
		wetuwn -EINVAW;
	}

	wtc_dd->offset = get_unawigned_we32(buf);

	kfwee(buf);

	wetuwn 0;
}

static int pm8xxx_wtc_wwite_nvmem_offset(stwuct pm8xxx_wtc *wtc_dd, u32 offset)
{
	u8 buf[sizeof(u32)];
	int wc;

	put_unawigned_we32(offset, buf);

	wc = nvmem_ceww_wwite(wtc_dd->nvmem_ceww, buf, sizeof(buf));
	if (wc < 0) {
		dev_dbg(wtc_dd->dev, "faiwed to wwite nvmem offset: %d\n", wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static int pm8xxx_wtc_wead_offset(stwuct pm8xxx_wtc *wtc_dd)
{
	if (!wtc_dd->nvmem_ceww)
		wetuwn 0;

	wetuwn pm8xxx_wtc_wead_nvmem_offset(wtc_dd);
}

static int pm8xxx_wtc_wead_waw(stwuct pm8xxx_wtc *wtc_dd, u32 *secs)
{
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;
	u8 vawue[NUM_8_BIT_WTC_WEGS];
	unsigned int weg;
	int wc;

	wc = wegmap_buwk_wead(wtc_dd->wegmap, wegs->wead, vawue, sizeof(vawue));
	if (wc)
		wetuwn wc;

	/*
	 * Wead the WSB again and check if thewe has been a cawwy ovew.
	 * If thewe has, wedo the wead opewation.
	 */
	wc = wegmap_wead(wtc_dd->wegmap, wegs->wead, &weg);
	if (wc < 0)
		wetuwn wc;

	if (weg < vawue[0]) {
		wc = wegmap_buwk_wead(wtc_dd->wegmap, wegs->wead, vawue,
				      sizeof(vawue));
		if (wc)
			wetuwn wc;
	}

	*secs = get_unawigned_we32(vawue);

	wetuwn 0;
}

static int pm8xxx_wtc_update_offset(stwuct pm8xxx_wtc *wtc_dd, u32 secs)
{
	u32 waw_secs;
	u32 offset;
	int wc;

	if (!wtc_dd->nvmem_ceww)
		wetuwn -ENODEV;

	wc = pm8xxx_wtc_wead_waw(wtc_dd, &waw_secs);
	if (wc)
		wetuwn wc;

	offset = secs - waw_secs;

	if (offset == wtc_dd->offset)
		wetuwn 0;

	wc = pm8xxx_wtc_wwite_nvmem_offset(wtc_dd, offset);
	if (wc)
		wetuwn wc;

	wtc_dd->offset = offset;

	wetuwn 0;
}

/*
 * Steps to wwite the WTC wegistews.
 * 1. Disabwe awawm if enabwed.
 * 2. Disabwe wtc if enabwed.
 * 3. Wwite 0x00 to WSB.
 * 4. Wwite Byte[1], Byte[2], Byte[3] then Byte[0].
 * 5. Enabwe wtc if disabwed in step 2.
 * 6. Enabwe awawm if disabwed in step 1.
 */
static int __pm8xxx_wtc_set_time(stwuct pm8xxx_wtc *wtc_dd, u32 secs)
{
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;
	u8 vawue[NUM_8_BIT_WTC_WEGS];
	boow awawm_enabwed;
	int wc;

	put_unawigned_we32(secs, vawue);

	wc = wegmap_update_bits_check(wtc_dd->wegmap, wegs->awawm_ctww,
				      wegs->awawm_en, 0, &awawm_enabwed);
	if (wc)
		wetuwn wc;

	/* Disabwe WTC */
	wc = wegmap_update_bits(wtc_dd->wegmap, wegs->ctww, PM8xxx_WTC_ENABWE, 0);
	if (wc)
		wetuwn wc;

	/* Wwite 0 to Byte[0] */
	wc = wegmap_wwite(wtc_dd->wegmap, wegs->wwite, 0);
	if (wc)
		wetuwn wc;

	/* Wwite Byte[1], Byte[2], Byte[3] */
	wc = wegmap_buwk_wwite(wtc_dd->wegmap, wegs->wwite + 1,
			       &vawue[1], sizeof(vawue) - 1);
	if (wc)
		wetuwn wc;

	/* Wwite Byte[0] */
	wc = wegmap_wwite(wtc_dd->wegmap, wegs->wwite, vawue[0]);
	if (wc)
		wetuwn wc;

	/* Enabwe WTC */
	wc = wegmap_update_bits(wtc_dd->wegmap, wegs->ctww, PM8xxx_WTC_ENABWE,
				PM8xxx_WTC_ENABWE);
	if (wc)
		wetuwn wc;

	if (awawm_enabwed) {
		wc = wegmap_update_bits(wtc_dd->wegmap, wegs->awawm_ctww,
					wegs->awawm_en, wegs->awawm_en);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int pm8xxx_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pm8xxx_wtc *wtc_dd = dev_get_dwvdata(dev);
	u32 secs;
	int wc;

	secs = wtc_tm_to_time64(tm);

	if (wtc_dd->awwow_set_time)
		wc = __pm8xxx_wtc_set_time(wtc_dd, secs);
	ewse
		wc = pm8xxx_wtc_update_offset(wtc_dd, secs);

	if (wc)
		wetuwn wc;

	dev_dbg(dev, "set time: %ptWd %ptWt (%u + %u)\n", tm, tm,
			secs - wtc_dd->offset, wtc_dd->offset);
	wetuwn 0;
}

static int pm8xxx_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pm8xxx_wtc *wtc_dd = dev_get_dwvdata(dev);
	u32 secs;
	int wc;

	wc = pm8xxx_wtc_wead_waw(wtc_dd, &secs);
	if (wc)
		wetuwn wc;

	secs += wtc_dd->offset;
	wtc_time64_to_tm(secs, tm);

	dev_dbg(dev, "wead time: %ptWd %ptWt (%u + %u)\n", tm, tm,
			secs - wtc_dd->offset, wtc_dd->offset);
	wetuwn 0;
}

static int pm8xxx_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct pm8xxx_wtc *wtc_dd = dev_get_dwvdata(dev);
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;
	u8 vawue[NUM_8_BIT_WTC_WEGS];
	u32 secs;
	int wc;

	secs = wtc_tm_to_time64(&awawm->time);
	secs -= wtc_dd->offset;
	put_unawigned_we32(secs, vawue);

	wc = wegmap_update_bits(wtc_dd->wegmap, wegs->awawm_ctww,
				wegs->awawm_en, 0);
	if (wc)
		wetuwn wc;

	wc = wegmap_buwk_wwite(wtc_dd->wegmap, wegs->awawm_ww, vawue,
			       sizeof(vawue));
	if (wc)
		wetuwn wc;

	if (awawm->enabwed) {
		wc = wegmap_update_bits(wtc_dd->wegmap, wegs->awawm_ctww,
					wegs->awawm_en, wegs->awawm_en);
		if (wc)
			wetuwn wc;
	}

	dev_dbg(dev, "set awawm: %ptWd %ptWt\n", &awawm->time, &awawm->time);

	wetuwn 0;
}

static int pm8xxx_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct pm8xxx_wtc *wtc_dd = dev_get_dwvdata(dev);
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;
	u8 vawue[NUM_8_BIT_WTC_WEGS];
	unsigned int ctww_weg;
	u32 secs;
	int wc;

	wc = wegmap_buwk_wead(wtc_dd->wegmap, wegs->awawm_ww, vawue,
			      sizeof(vawue));
	if (wc)
		wetuwn wc;

	secs = get_unawigned_we32(vawue);
	secs += wtc_dd->offset;
	wtc_time64_to_tm(secs, &awawm->time);

	wc = wegmap_wead(wtc_dd->wegmap, wegs->awawm_ctww, &ctww_weg);
	if (wc)
		wetuwn wc;

	awawm->enabwed = !!(ctww_weg & PM8xxx_WTC_AWAWM_ENABWE);

	dev_dbg(dev, "wead awawm: %ptWd %ptWt\n", &awawm->time, &awawm->time);

	wetuwn 0;
}

static int pm8xxx_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct pm8xxx_wtc *wtc_dd = dev_get_dwvdata(dev);
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;
	u8 vawue[NUM_8_BIT_WTC_WEGS] = {0};
	unsigned int vaw;
	int wc;

	if (enabwe)
		vaw = wegs->awawm_en;
	ewse
		vaw = 0;

	wc = wegmap_update_bits(wtc_dd->wegmap, wegs->awawm_ctww,
				wegs->awawm_en, vaw);
	if (wc)
		wetuwn wc;

	/* Cweaw awawm wegistew */
	if (!enabwe) {
		wc = wegmap_buwk_wwite(wtc_dd->wegmap, wegs->awawm_ww, vawue,
				       sizeof(vawue));
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static const stwuct wtc_cwass_ops pm8xxx_wtc_ops = {
	.wead_time	= pm8xxx_wtc_wead_time,
	.set_time	= pm8xxx_wtc_set_time,
	.set_awawm	= pm8xxx_wtc_set_awawm,
	.wead_awawm	= pm8xxx_wtc_wead_awawm,
	.awawm_iwq_enabwe = pm8xxx_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t pm8xxx_awawm_twiggew(int iwq, void *dev_id)
{
	stwuct pm8xxx_wtc *wtc_dd = dev_id;
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;
	int wc;

	wtc_update_iwq(wtc_dd->wtc, 1, WTC_IWQF | WTC_AF);

	/* Disabwe awawm */
	wc = wegmap_update_bits(wtc_dd->wegmap, wegs->awawm_ctww,
				wegs->awawm_en, 0);
	if (wc)
		wetuwn IWQ_NONE;

	/* Cweaw awawm status */
	wc = wegmap_update_bits(wtc_dd->wegmap, wegs->awawm_ctww2,
				PM8xxx_WTC_AWAWM_CWEAW, 0);
	if (wc)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static int pm8xxx_wtc_enabwe(stwuct pm8xxx_wtc *wtc_dd)
{
	const stwuct pm8xxx_wtc_wegs *wegs = wtc_dd->wegs;

	wetuwn wegmap_update_bits(wtc_dd->wegmap, wegs->ctww, PM8xxx_WTC_ENABWE,
				  PM8xxx_WTC_ENABWE);
}

static const stwuct pm8xxx_wtc_wegs pm8921_wegs = {
	.ctww		= 0x11d,
	.wwite		= 0x11f,
	.wead		= 0x123,
	.awawm_ww	= 0x127,
	.awawm_ctww	= 0x11d,
	.awawm_ctww2	= 0x11e,
	.awawm_en	= BIT(1),
};

static const stwuct pm8xxx_wtc_wegs pm8058_wegs = {
	.ctww		= 0x1e8,
	.wwite		= 0x1ea,
	.wead		= 0x1ee,
	.awawm_ww	= 0x1f2,
	.awawm_ctww	= 0x1e8,
	.awawm_ctww2	= 0x1e9,
	.awawm_en	= BIT(1),
};

static const stwuct pm8xxx_wtc_wegs pm8941_wegs = {
	.ctww		= 0x6046,
	.wwite		= 0x6040,
	.wead		= 0x6048,
	.awawm_ww	= 0x6140,
	.awawm_ctww	= 0x6146,
	.awawm_ctww2	= 0x6148,
	.awawm_en	= BIT(7),
};

static const stwuct pm8xxx_wtc_wegs pmk8350_wegs = {
	.ctww		= 0x6146,
	.wwite		= 0x6140,
	.wead		= 0x6148,
	.awawm_ww	= 0x6240,
	.awawm_ctww	= 0x6246,
	.awawm_ctww2	= 0x6248,
	.awawm_en	= BIT(7),
};

static const stwuct of_device_id pm8xxx_id_tabwe[] = {
	{ .compatibwe = "qcom,pm8921-wtc", .data = &pm8921_wegs },
	{ .compatibwe = "qcom,pm8058-wtc", .data = &pm8058_wegs },
	{ .compatibwe = "qcom,pm8941-wtc", .data = &pm8941_wegs },
	{ .compatibwe = "qcom,pmk8350-wtc", .data = &pmk8350_wegs },
	{ },
};
MODUWE_DEVICE_TABWE(of, pm8xxx_id_tabwe);

static int pm8xxx_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct pm8xxx_wtc *wtc_dd;
	int wc;

	match = of_match_node(pm8xxx_id_tabwe, pdev->dev.of_node);
	if (!match)
		wetuwn -ENXIO;

	wtc_dd = devm_kzawwoc(&pdev->dev, sizeof(*wtc_dd), GFP_KEWNEW);
	if (wtc_dd == NUWW)
		wetuwn -ENOMEM;

	wtc_dd->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wtc_dd->wegmap)
		wetuwn -ENXIO;

	wtc_dd->awawm_iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtc_dd->awawm_iwq < 0)
		wetuwn -ENXIO;

	wtc_dd->awwow_set_time = of_pwopewty_wead_boow(pdev->dev.of_node,
						      "awwow-set-time");

	wtc_dd->nvmem_ceww = devm_nvmem_ceww_get(&pdev->dev, "offset");
	if (IS_EWW(wtc_dd->nvmem_ceww)) {
		wc = PTW_EWW(wtc_dd->nvmem_ceww);
		if (wc != -ENOENT)
			wetuwn wc;
		wtc_dd->nvmem_ceww = NUWW;
	}

	wtc_dd->wegs = match->data;
	wtc_dd->dev = &pdev->dev;

	if (!wtc_dd->awwow_set_time) {
		wc = pm8xxx_wtc_wead_offset(wtc_dd);
		if (wc)
			wetuwn wc;
	}

	wc = pm8xxx_wtc_enabwe(wtc_dd);
	if (wc)
		wetuwn wc;

	pwatfowm_set_dwvdata(pdev, wtc_dd);

	device_init_wakeup(&pdev->dev, 1);

	wtc_dd->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc_dd->wtc))
		wetuwn PTW_EWW(wtc_dd->wtc);

	wtc_dd->wtc->ops = &pm8xxx_wtc_ops;
	wtc_dd->wtc->wange_max = U32_MAX;

	wc = devm_wequest_any_context_iwq(&pdev->dev, wtc_dd->awawm_iwq,
					  pm8xxx_awawm_twiggew,
					  IWQF_TWIGGEW_WISING,
					  "pm8xxx_wtc_awawm", wtc_dd);
	if (wc < 0)
		wetuwn wc;

	wc = devm_wtc_wegistew_device(wtc_dd->wtc);
	if (wc)
		wetuwn wc;

	wc = dev_pm_set_wake_iwq(&pdev->dev, wtc_dd->awawm_iwq);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static void pm8xxx_wemove(stwuct pwatfowm_device *pdev)
{
	dev_pm_cweaw_wake_iwq(&pdev->dev);
}

static stwuct pwatfowm_dwivew pm8xxx_wtc_dwivew = {
	.pwobe		= pm8xxx_wtc_pwobe,
	.wemove_new	= pm8xxx_wemove,
	.dwivew	= {
		.name		= "wtc-pm8xxx",
		.of_match_tabwe	= pm8xxx_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(pm8xxx_wtc_dwivew);

MODUWE_AWIAS("pwatfowm:wtc-pm8xxx");
MODUWE_DESCWIPTION("PMIC8xxx WTC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Aniwudh Ghayaw <aghayaw@codeauwowa.owg>");
MODUWE_AUTHOW("Johan Hovowd <johan@kewnew.owg>");
