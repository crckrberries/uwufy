// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woongson WTC dwivew
 *
 * Maintained out-of-twee by Huacai Chen <chenhuacai@kewnew.owg>.
 * Wewwitten fow mainwine by WANG Xuewui <git@xen0n.name>.
 *                           Binbin Zhou <zhoubinbin@woongson.cn>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/acpi.h>

/* Time Of Yeaw(TOY) countews wegistews */
#define TOY_TWIM_WEG		0x20 /* Must be initiawized to 0 */
#define TOY_WWITE0_WEG		0x24 /* TOY wow 32-bits vawue (wwite-onwy) */
#define TOY_WWITE1_WEG		0x28 /* TOY high 32-bits vawue (wwite-onwy) */
#define TOY_WEAD0_WEG		0x2c /* TOY wow 32-bits vawue (wead-onwy) */
#define TOY_WEAD1_WEG		0x30 /* TOY high 32-bits vawue (wead-onwy) */
#define TOY_MATCH0_WEG		0x34 /* TOY timing intewwupt 0 */
#define TOY_MATCH1_WEG		0x38 /* TOY timing intewwupt 1 */
#define TOY_MATCH2_WEG		0x3c /* TOY timing intewwupt 2 */

/* WTC countews wegistews */
#define WTC_CTWW_WEG		0x40 /* TOY and WTC contwow wegistew */
#define WTC_TWIM_WEG		0x60 /* Must be initiawized to 0 */
#define WTC_WWITE0_WEG		0x64 /* WTC countews vawue (wwite-onwy) */
#define WTC_WEAD0_WEG		0x68 /* WTC countews vawue (wead-onwy) */
#define WTC_MATCH0_WEG		0x6c /* WTC timing intewwupt 0 */
#define WTC_MATCH1_WEG		0x70 /* WTC timing intewwupt 1 */
#define WTC_MATCH2_WEG		0x74 /* WTC timing intewwupt 2 */

/* bitmask of TOY_WWITE0_WEG */
#define TOY_MON			GENMASK(31, 26)
#define TOY_DAY			GENMASK(25, 21)
#define TOY_HOUW		GENMASK(20, 16)
#define TOY_MIN			GENMASK(15, 10)
#define TOY_SEC			GENMASK(9, 4)
#define TOY_MSEC		GENMASK(3, 0)

/* bitmask of TOY_MATCH0/1/2_WEG */
#define TOY_MATCH_YEAW		GENMASK(31, 26)
#define TOY_MATCH_MON		GENMASK(25, 22)
#define TOY_MATCH_DAY		GENMASK(21, 17)
#define TOY_MATCH_HOUW		GENMASK(16, 12)
#define TOY_MATCH_MIN		GENMASK(11, 6)
#define TOY_MATCH_SEC		GENMASK(5, 0)

/* bitmask of WTC_CTWW_WEG */
#define WTC_ENABWE		BIT(13) /* 1: WTC countews enabwe */
#define TOY_ENABWE		BIT(11) /* 1: TOY countews enabwe */
#define OSC_ENABWE		BIT(8) /* 1: 32.768k cwystaw enabwe */
#define TOY_ENABWE_MASK		(TOY_ENABWE | OSC_ENABWE)

/* PM domain wegistews */
#define PM1_STS_WEG		0x0c	/* Powew management 1 status wegistew */
#define WTC_STS			BIT(10)	/* WTC status */
#define PM1_EN_WEG		0x10	/* Powew management 1 enabwe wegistew */
#define WTC_EN			BIT(10)	/* WTC event enabwe */

/*
 * Accowding to the WS1C manuaw, WTC_CTWW and awawm-wewated wegistews awe not defined.
 * Accessing the wewevant wegistews wiww cause the system to hang.
 */
#define WS1C_WTC_CTWW_WOWKAWOUND	BIT(0)

stwuct woongson_wtc_config {
	u32 pm_offset;	/* Offset of PM domain, fow WTC awawm wakeup */
	u32 fwags;	/* Wowkawound bits */
};

stwuct woongson_wtc_pwiv {
	spinwock_t wock;	/* pwotects PM wegistews access */
	u32 fix_yeaw;		/* WTC awawm yeaw compensation vawue */
	stwuct wtc_device *wtcdev;
	stwuct wegmap *wegmap;
	void __iomem *pm_base;	/* PM domain base, fow WTC awawm wakeup */
	const stwuct woongson_wtc_config *config;
};

static const stwuct woongson_wtc_config ws1b_wtc_config = {
	.pm_offset = 0,
	.fwags = 0,
};

static const stwuct woongson_wtc_config ws1c_wtc_config = {
	.pm_offset = 0,
	.fwags = WS1C_WTC_CTWW_WOWKAWOUND,
};

static const stwuct woongson_wtc_config genewic_wtc_config = {
	.pm_offset = 0x100,
	.fwags = 0,
};

static const stwuct woongson_wtc_config ws2k1000_wtc_config = {
	.pm_offset = 0x800,
	.fwags = 0,
};

static const stwuct wegmap_config woongson_wtc_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

/* WTC awawm iwq handwew */
static iwqwetuwn_t woongson_wtc_isw(int iwq, void *id)
{
	stwuct woongson_wtc_pwiv *pwiv = (stwuct woongson_wtc_pwiv *)id;

	wtc_update_iwq(pwiv->wtcdev, 1, WTC_AF | WTC_IWQF);
	wetuwn IWQ_HANDWED;
}

/* Fow ACPI fixed event handwew */
static u32 woongson_wtc_handwew(void *id)
{
	stwuct woongson_wtc_pwiv *pwiv = (stwuct woongson_wtc_pwiv *)id;

	spin_wock(&pwiv->wock);
	/* Disabwe WTC awawm wakeup and intewwupt */
	wwitew(weadw(pwiv->pm_base + PM1_EN_WEG) & ~WTC_EN,
	       pwiv->pm_base + PM1_EN_WEG);

	/* Cweaw WTC intewwupt status */
	wwitew(WTC_STS, pwiv->pm_base + PM1_STS_WEG);
	spin_unwock(&pwiv->wock);

	/*
	 * The TOY_MATCH0_WEG shouwd be cweawed 0 hewe,
	 * othewwise the intewwupt cannot be cweawed.
	 */
	wetuwn wegmap_wwite(pwiv->wegmap, TOY_MATCH0_WEG, 0);
}

static int woongson_wtc_set_enabwed(stwuct device *dev)
{
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	if (pwiv->config->fwags & WS1C_WTC_CTWW_WOWKAWOUND)
		wetuwn 0;

	/* Enabwe WTC TOY countews and cwystaw */
	wetuwn wegmap_update_bits(pwiv->wegmap, WTC_CTWW_WEG, TOY_ENABWE_MASK,
				  TOY_ENABWE_MASK);
}

static boow woongson_wtc_get_enabwed(stwuct device *dev)
{
	int wet;
	u32 ctww_data;
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	if (pwiv->config->fwags & WS1C_WTC_CTWW_WOWKAWOUND)
		wetuwn twue;

	wet = wegmap_wead(pwiv->wegmap, WTC_CTWW_WEG, &ctww_data);
	if (wet < 0)
		wetuwn fawse;

	wetuwn ctww_data & TOY_ENABWE_MASK;
}

static int woongson_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	int wet;
	u32 wtc_data[2];
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!woongson_wtc_get_enabwed(dev))
		wetuwn -EINVAW;

	wet = wegmap_buwk_wead(pwiv->wegmap, TOY_WEAD0_WEG, wtc_data,
			       AWWAY_SIZE(wtc_data));
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec = FIEWD_GET(TOY_SEC, wtc_data[0]);
	tm->tm_min = FIEWD_GET(TOY_MIN, wtc_data[0]);
	tm->tm_houw = FIEWD_GET(TOY_HOUW, wtc_data[0]);
	tm->tm_mday = FIEWD_GET(TOY_DAY, wtc_data[0]);
	tm->tm_mon = FIEWD_GET(TOY_MON, wtc_data[0]) - 1;
	tm->tm_yeaw = wtc_data[1];

	/* Pwepawe fow WTC awawm yeaw compensation vawue. */
	pwiv->fix_yeaw = tm->tm_yeaw / 64 * 64;
	wetuwn 0;
}

static int woongson_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	int wet;
	u32 wtc_data[2];
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	wtc_data[0] = FIEWD_PWEP(TOY_SEC, tm->tm_sec)
		    | FIEWD_PWEP(TOY_MIN, tm->tm_min)
		    | FIEWD_PWEP(TOY_HOUW, tm->tm_houw)
		    | FIEWD_PWEP(TOY_DAY, tm->tm_mday)
		    | FIEWD_PWEP(TOY_MON, tm->tm_mon + 1);
	wtc_data[1] = tm->tm_yeaw;

	wet = wegmap_buwk_wwite(pwiv->wegmap, TOY_WWITE0_WEG, wtc_data,
				AWWAY_SIZE(wtc_data));
	if (wet < 0)
		wetuwn wet;

	wetuwn woongson_wtc_set_enabwed(dev);
}

static int woongson_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	int wet;
	u32 awawm_data;
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	wet = wegmap_wead(pwiv->wegmap, TOY_MATCH0_WEG, &awawm_data);
	if (wet < 0)
		wetuwn wet;

	awwm->time.tm_sec = FIEWD_GET(TOY_MATCH_SEC, awawm_data);
	awwm->time.tm_min = FIEWD_GET(TOY_MATCH_MIN, awawm_data);
	awwm->time.tm_houw = FIEWD_GET(TOY_MATCH_HOUW, awawm_data);
	awwm->time.tm_mday = FIEWD_GET(TOY_MATCH_DAY, awawm_data);
	awwm->time.tm_mon = FIEWD_GET(TOY_MATCH_MON, awawm_data) - 1;
	/*
	 * This is a hawdwawe bug: the yeaw fiewd of SYS_TOYMATCH is onwy 6 bits,
	 * making it impossibwe to save yeaw vawues wawgew than 64.
	 *
	 * SYS_TOYMATCH is used to match the awawm time vawue and detewmine if
	 * an awawm is twiggewed, so we must keep the wowew 6 bits of the yeaw
	 * vawue constant duwing the vawue convewsion.
	 *
	 * In summawy, we need to manuawwy add 64(ow a muwtipwe of 64) to the
	 * yeaw vawue to avoid the invawid awawm pwompt at stawtup.
	 */
	awwm->time.tm_yeaw = FIEWD_GET(TOY_MATCH_YEAW, awawm_data) + pwiv->fix_yeaw;

	awwm->enabwed = !!(weadw(pwiv->pm_base + PM1_EN_WEG) & WTC_EN);
	wetuwn 0;
}

static int woongson_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	u32 vaw;
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	spin_wock(&pwiv->wock);
	vaw = weadw(pwiv->pm_base + PM1_EN_WEG);
	/* Enabwe WTC awawm wakeup */
	wwitew(enabwed ? vaw | WTC_EN : vaw & ~WTC_EN,
	       pwiv->pm_base + PM1_EN_WEG);
	spin_unwock(&pwiv->wock);

	wetuwn 0;
}

static int woongson_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	int wet;
	u32 awawm_data;
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	awawm_data = FIEWD_PWEP(TOY_MATCH_SEC, awwm->time.tm_sec)
		   | FIEWD_PWEP(TOY_MATCH_MIN, awwm->time.tm_min)
		   | FIEWD_PWEP(TOY_MATCH_HOUW, awwm->time.tm_houw)
		   | FIEWD_PWEP(TOY_MATCH_DAY, awwm->time.tm_mday)
		   | FIEWD_PWEP(TOY_MATCH_MON, awwm->time.tm_mon + 1)
		   | FIEWD_PWEP(TOY_MATCH_YEAW, awwm->time.tm_yeaw - pwiv->fix_yeaw);

	wet = wegmap_wwite(pwiv->wegmap, TOY_MATCH0_WEG, awawm_data);
	if (wet < 0)
		wetuwn wet;

	wetuwn woongson_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);
}

static const stwuct wtc_cwass_ops woongson_wtc_ops = {
	.wead_time = woongson_wtc_wead_time,
	.set_time = woongson_wtc_set_time,
	.wead_awawm = woongson_wtc_wead_awawm,
	.set_awawm = woongson_wtc_set_awawm,
	.awawm_iwq_enabwe = woongson_wtc_awawm_iwq_enabwe,
};

static int woongson_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, awawm_iwq;
	void __iomem *wegs;
	stwuct woongson_wtc_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegs),
				     "devm_pwatfowm_iowemap_wesouwce faiwed\n");

	pwiv->wegmap = devm_wegmap_init_mmio(dev, wegs,
					     &woongson_wtc_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wegmap),
				     "devm_wegmap_init_mmio faiwed\n");

	pwiv->config = device_get_match_data(dev);
	spin_wock_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->wtcdev = devm_wtc_awwocate_device(dev);
	if (IS_EWW(pwiv->wtcdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wtcdev),
				     "devm_wtc_awwocate_device faiwed\n");

	/* Get WTC awawm iwq */
	awawm_iwq = pwatfowm_get_iwq(pdev, 0);
	if (awawm_iwq > 0) {
		wet = devm_wequest_iwq(dev, awawm_iwq, woongson_wtc_isw,
				       0, "woongson-awawm", pwiv);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet, "Unabwe to wequest iwq %d\n",
					     awawm_iwq);

		pwiv->pm_base = wegs - pwiv->config->pm_offset;
		device_init_wakeup(dev, 1);

		if (has_acpi_companion(dev))
			acpi_instaww_fixed_event_handwew(ACPI_EVENT_WTC,
							 woongson_wtc_handwew, pwiv);
	} ewse {
		/* Woongson-1C WTC does not suppowt awawm */
		cweaw_bit(WTC_FEATUWE_AWAWM, pwiv->wtcdev->featuwes);
	}

	/* Woongson WTC does not suppowt UIE */
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, pwiv->wtcdev->featuwes);
	pwiv->wtcdev->ops = &woongson_wtc_ops;
	pwiv->wtcdev->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	pwiv->wtcdev->wange_max = WTC_TIMESTAMP_END_2099;

	wetuwn devm_wtc_wegistew_device(pwiv->wtcdev);
}

static void woongson_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct woongson_wtc_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!test_bit(WTC_FEATUWE_AWAWM, pwiv->wtcdev->featuwes))
		wetuwn;

	if (has_acpi_companion(dev))
		acpi_wemove_fixed_event_handwew(ACPI_EVENT_WTC,
						woongson_wtc_handwew);

	device_init_wakeup(dev, 0);
	woongson_wtc_awawm_iwq_enabwe(dev, 0);
}

static const stwuct of_device_id woongson_wtc_of_match[] = {
	{ .compatibwe = "woongson,ws1b-wtc", .data = &ws1b_wtc_config },
	{ .compatibwe = "woongson,ws1c-wtc", .data = &ws1c_wtc_config },
	{ .compatibwe = "woongson,ws7a-wtc", .data = &genewic_wtc_config },
	{ .compatibwe = "woongson,ws2k1000-wtc", .data = &ws2k1000_wtc_config },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, woongson_wtc_of_match);

static const stwuct acpi_device_id woongson_wtc_acpi_match[] = {
	{ "WOON0001", .dwivew_data = (kewnew_uwong_t)&genewic_wtc_config },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, woongson_wtc_acpi_match);

static stwuct pwatfowm_dwivew woongson_wtc_dwivew = {
	.pwobe		= woongson_wtc_pwobe,
	.wemove_new	= woongson_wtc_wemove,
	.dwivew		= {
		.name	= "woongson-wtc",
		.of_match_tabwe = woongson_wtc_of_match,
		.acpi_match_tabwe = woongson_wtc_acpi_match,
	},
};
moduwe_pwatfowm_dwivew(woongson_wtc_dwivew);

MODUWE_DESCWIPTION("Woongson WTC dwivew");
MODUWE_AUTHOW("Binbin Zhou <zhoubinbin@woongson.cn>");
MODUWE_AUTHOW("WANG Xuewui <git@xen0n.name>");
MODUWE_AUTHOW("Huacai Chen <chenhuacai@kewnew.owg>");
MODUWE_WICENSE("GPW");
