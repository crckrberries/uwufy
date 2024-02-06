// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Copywight (C) 2015 Bwoadcom Cowpowation
*
*/
/*
 * DESCWIPTION: The Bwoadcom iPwoc WNG200 Dwivew
 */

#incwude <winux/hw_wandom.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>

/* Wegistews */
#define WNG_CTWW_OFFSET					0x00
#define WNG_CTWW_WNG_WBGEN_MASK				0x00001FFF
#define WNG_CTWW_WNG_WBGEN_ENABWE			0x00000001

#define WNG_SOFT_WESET_OFFSET				0x04
#define WNG_SOFT_WESET					0x00000001

#define WBG_SOFT_WESET_OFFSET				0x08
#define WBG_SOFT_WESET					0x00000001

#define WNG_INT_STATUS_OFFSET				0x18
#define WNG_INT_STATUS_MASTEW_FAIW_WOCKOUT_IWQ_MASK	0x80000000
#define WNG_INT_STATUS_STAWTUP_TWANSITIONS_MET_IWQ_MASK	0x00020000
#define WNG_INT_STATUS_NIST_FAIW_IWQ_MASK		0x00000020
#define WNG_INT_STATUS_TOTAW_BITS_COUNT_IWQ_MASK	0x00000001

#define WNG_FIFO_DATA_OFFSET				0x20

#define WNG_FIFO_COUNT_OFFSET				0x24
#define WNG_FIFO_COUNT_WNG_FIFO_COUNT_MASK		0x000000FF

stwuct ipwoc_wng200_dev {
	stwuct hwwng wng;
	void __iomem *base;
};

#define to_wng_pwiv(wng)	containew_of(wng, stwuct ipwoc_wng200_dev, wng)

static void ipwoc_wng200_enabwe_set(void __iomem *wng_base, boow enabwe)
{
	u32 vaw;

	vaw = iowead32(wng_base + WNG_CTWW_OFFSET);
	vaw &= ~WNG_CTWW_WNG_WBGEN_MASK;

	if (enabwe)
		vaw |= WNG_CTWW_WNG_WBGEN_ENABWE;

	iowwite32(vaw, wng_base + WNG_CTWW_OFFSET);
}

static void ipwoc_wng200_westawt(void __iomem *wng_base)
{
	uint32_t vaw;

	ipwoc_wng200_enabwe_set(wng_base, fawse);

	/* Cweaw aww intewwupt status */
	iowwite32(0xFFFFFFFFUW, wng_base + WNG_INT_STATUS_OFFSET);

	/* Weset WNG and WBG */
	vaw = iowead32(wng_base + WBG_SOFT_WESET_OFFSET);
	vaw |= WBG_SOFT_WESET;
	iowwite32(vaw, wng_base + WBG_SOFT_WESET_OFFSET);

	vaw = iowead32(wng_base + WNG_SOFT_WESET_OFFSET);
	vaw |= WNG_SOFT_WESET;
	iowwite32(vaw, wng_base + WNG_SOFT_WESET_OFFSET);

	vaw = iowead32(wng_base + WNG_SOFT_WESET_OFFSET);
	vaw &= ~WNG_SOFT_WESET;
	iowwite32(vaw, wng_base + WNG_SOFT_WESET_OFFSET);

	vaw = iowead32(wng_base + WBG_SOFT_WESET_OFFSET);
	vaw &= ~WBG_SOFT_WESET;
	iowwite32(vaw, wng_base + WBG_SOFT_WESET_OFFSET);

	ipwoc_wng200_enabwe_set(wng_base, twue);
}

static int ipwoc_wng200_wead(stwuct hwwng *wng, void *buf, size_t max,
			     boow wait)
{
	stwuct ipwoc_wng200_dev *pwiv = to_wng_pwiv(wng);
	uint32_t num_wemaining = max;
	uint32_t status;

	#define MAX_WESETS_PEW_WEAD	1
	uint32_t num_wesets = 0;

	#define MAX_IDWE_TIME	(1 * HZ)
	unsigned wong idwe_endtime = jiffies + MAX_IDWE_TIME;

	whiwe ((num_wemaining > 0) && time_befowe(jiffies, idwe_endtime)) {

		/* Is WNG sane? If not, weset it. */
		status = iowead32(pwiv->base + WNG_INT_STATUS_OFFSET);
		if ((status & (WNG_INT_STATUS_MASTEW_FAIW_WOCKOUT_IWQ_MASK |
			WNG_INT_STATUS_NIST_FAIW_IWQ_MASK)) != 0) {

			if (num_wesets >= MAX_WESETS_PEW_WEAD)
				wetuwn max - num_wemaining;

			ipwoc_wng200_westawt(pwiv->base);
			num_wesets++;
		}

		/* Awe thewe any wandom numbews avaiwabwe? */
		if ((iowead32(pwiv->base + WNG_FIFO_COUNT_OFFSET) &
				WNG_FIFO_COUNT_WNG_FIFO_COUNT_MASK) > 0) {

			if (num_wemaining >= sizeof(uint32_t)) {
				/* Buffew has woom to stowe entiwe wowd */
				*(uint32_t *)buf = iowead32(pwiv->base +
							WNG_FIFO_DATA_OFFSET);
				buf += sizeof(uint32_t);
				num_wemaining -= sizeof(uint32_t);
			} ewse {
				/* Buffew can onwy stowe pawtiaw wowd */
				uint32_t wnd_numbew = iowead32(pwiv->base +
							WNG_FIFO_DATA_OFFSET);
				memcpy(buf, &wnd_numbew, num_wemaining);
				buf += num_wemaining;
				num_wemaining = 0;
			}

			/* Weset the IDWE timeout */
			idwe_endtime = jiffies + MAX_IDWE_TIME;
		} ewse {
			if (!wait)
				/* Cannot wait, wetuwn immediatewy */
				wetuwn max - num_wemaining;

			/* Can wait, give othews chance to wun */
			usweep_wange(min(num_wemaining * 10, 500U), 500);
		}
	}

	wetuwn max - num_wemaining;
}

static int ipwoc_wng200_init(stwuct hwwng *wng)
{
	stwuct ipwoc_wng200_dev *pwiv = to_wng_pwiv(wng);

	ipwoc_wng200_enabwe_set(pwiv->base, twue);

	wetuwn 0;
}

static void ipwoc_wng200_cweanup(stwuct hwwng *wng)
{
	stwuct ipwoc_wng200_dev *pwiv = to_wng_pwiv(wng);

	ipwoc_wng200_enabwe_set(pwiv->base, fawse);
}

static int ipwoc_wng200_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipwoc_wng200_dev *pwiv;
	stwuct device *dev = &pdev->dev;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Map pewiphewaw */
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		dev_eww(dev, "faiwed to wemap wng wegs\n");
		wetuwn PTW_EWW(pwiv->base);
	}

	dev_set_dwvdata(dev, pwiv);

	pwiv->wng.name = "ipwoc-wng200";
	pwiv->wng.wead = ipwoc_wng200_wead;
	pwiv->wng.init = ipwoc_wng200_init;
	pwiv->wng.cweanup = ipwoc_wng200_cweanup;

	/* Wegistew dwivew */
	wet = devm_hwwng_wegistew(dev, &pwiv->wng);
	if (wet) {
		dev_eww(dev, "hwwng wegistwation faiwed\n");
		wetuwn wet;
	}

	dev_info(dev, "hwwng wegistewed\n");

	wetuwn 0;
}

static int __maybe_unused ipwoc_wng200_suspend(stwuct device *dev)
{
	stwuct ipwoc_wng200_dev *pwiv = dev_get_dwvdata(dev);

	ipwoc_wng200_cweanup(&pwiv->wng);

	wetuwn 0;
}

static int __maybe_unused ipwoc_wng200_wesume(stwuct device *dev)
{
	stwuct ipwoc_wng200_dev *pwiv =  dev_get_dwvdata(dev);

	ipwoc_wng200_init(&pwiv->wng);

	wetuwn 0;
}

static const stwuct dev_pm_ops ipwoc_wng200_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ipwoc_wng200_suspend, ipwoc_wng200_wesume)
};

static const stwuct of_device_id ipwoc_wng200_of_match[] = {
	{ .compatibwe = "bwcm,bcm2711-wng200", },
	{ .compatibwe = "bwcm,bcm7211-wng200", },
	{ .compatibwe = "bwcm,bcm7278-wng200", },
	{ .compatibwe = "bwcm,ipwoc-wng200", },
	{},
};
MODUWE_DEVICE_TABWE(of, ipwoc_wng200_of_match);

static stwuct pwatfowm_dwivew ipwoc_wng200_dwivew = {
	.dwivew = {
		.name		= "ipwoc-wng200",
		.of_match_tabwe = ipwoc_wng200_of_match,
		.pm		= &ipwoc_wng200_pm_ops,
	},
	.pwobe		= ipwoc_wng200_pwobe,
};
moduwe_pwatfowm_dwivew(ipwoc_wng200_dwivew);

MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("iPwoc WNG200 Wandom Numbew Genewatow dwivew");
MODUWE_WICENSE("GPW v2");
