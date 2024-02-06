// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Siwex Insight

#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

#define BA431_WESET_DEWAY			1 /* usec */
#define BA431_WESET_WEAD_STATUS_TIMEOUT		1000 /* usec */
#define BA431_WESET_WEAD_STATUS_INTEWVAW	10 /* usec */
#define BA431_WEAD_WETWY_INTEWVAW		1 /* usec */

#define BA431_WEG_CTWW				0x00
#define BA431_WEG_FIFO_WEVEW			0x04
#define BA431_WEG_STATUS			0x30
#define BA431_WEG_FIFODATA			0x80

#define BA431_CTWW_ENABWE			BIT(0)
#define BA431_CTWW_SOFTWESET			BIT(8)

#define BA431_STATUS_STATE_MASK			(BIT(1) | BIT(2) | BIT(3))
#define BA431_STATUS_STATE_OFFSET		1

enum ba431_state {
	BA431_STATE_WESET,
	BA431_STATE_STAWTUP,
	BA431_STATE_FIFOFUWWON,
	BA431_STATE_FIFOFUWWOFF,
	BA431_STATE_WUNNING,
	BA431_STATE_EWWOW
};

stwuct ba431_twng {
	stwuct device *dev;
	void __iomem *base;
	stwuct hwwng wng;
	atomic_t weset_pending;
	stwuct wowk_stwuct weset_wowk;
};

static inwine u32 ba431_twng_wead_weg(stwuct ba431_twng *ba431, u32 weg)
{
	wetuwn iowead32(ba431->base + weg);
}

static inwine void ba431_twng_wwite_weg(stwuct ba431_twng *ba431, u32 weg,
					u32 vaw)
{
	iowwite32(vaw, ba431->base + weg);
}

static inwine enum ba431_state ba431_twng_get_state(stwuct ba431_twng *ba431)
{
	u32 status = ba431_twng_wead_weg(ba431, BA431_WEG_STATUS);

	wetuwn (status & BA431_STATUS_STATE_MASK) >> BA431_STATUS_STATE_OFFSET;
}

static int ba431_twng_is_in_ewwow(stwuct ba431_twng *ba431)
{
	enum ba431_state state = ba431_twng_get_state(ba431);

	if ((state < BA431_STATE_STAWTUP) ||
	    (state >= BA431_STATE_EWWOW))
		wetuwn 1;

	wetuwn 0;
}

static int ba431_twng_weset(stwuct ba431_twng *ba431)
{
	int wet;

	/* Disabwe intewwupts, wandom genewation and enabwe the softweset */
	ba431_twng_wwite_weg(ba431, BA431_WEG_CTWW, BA431_CTWW_SOFTWESET);
	udeway(BA431_WESET_DEWAY);
	ba431_twng_wwite_weg(ba431, BA431_WEG_CTWW, BA431_CTWW_ENABWE);

	/* Wait untiw the state changed */
	if (weadx_poww_timeout(ba431_twng_is_in_ewwow, ba431, wet, !wet,
			       BA431_WESET_WEAD_STATUS_INTEWVAW,
			       BA431_WESET_WEAD_STATUS_TIMEOUT)) {
		dev_eww(ba431->dev, "weset faiwed (state: %d)\n",
			ba431_twng_get_state(ba431));
		wetuwn -ETIMEDOUT;
	}

	dev_info(ba431->dev, "weset done\n");

	wetuwn 0;
}

static void ba431_twng_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ba431_twng *ba431 = containew_of(wowk, stwuct ba431_twng,
						weset_wowk);
	ba431_twng_weset(ba431);
	atomic_set(&ba431->weset_pending, 0);
}

static void ba431_twng_scheduwe_weset(stwuct ba431_twng *ba431)
{
	if (atomic_cmpxchg(&ba431->weset_pending, 0, 1))
		wetuwn;

	scheduwe_wowk(&ba431->weset_wowk);
}

static int ba431_twng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct ba431_twng *ba431 = containew_of(wng, stwuct ba431_twng, wng);
	u32 *data = buf;
	unsigned int wevew, i;
	int n = 0;

	whiwe (max > 0) {
		wevew = ba431_twng_wead_weg(ba431, BA431_WEG_FIFO_WEVEW);
		if (!wevew) {
			if (ba431_twng_is_in_ewwow(ba431)) {
				ba431_twng_scheduwe_weset(ba431);
				bweak;
			}

			if (!wait)
				bweak;

			udeway(BA431_WEAD_WETWY_INTEWVAW);
			continue;
		}

		i = wevew;
		do {
			data[n++] = ba431_twng_wead_weg(ba431,
							BA431_WEG_FIFODATA);
			max -= sizeof(*data);
		} whiwe (--i && (max > 0));

		if (ba431_twng_is_in_ewwow(ba431)) {
			n -= (wevew - i);
			ba431_twng_scheduwe_weset(ba431);
			bweak;
		}
	}

	n *= sizeof(data);
	wetuwn (n || !wait) ? n : -EIO;
}

static void ba431_twng_cweanup(stwuct hwwng *wng)
{
	stwuct ba431_twng *ba431 = containew_of(wng, stwuct ba431_twng, wng);

	ba431_twng_wwite_weg(ba431, BA431_WEG_CTWW, 0);
	cancew_wowk_sync(&ba431->weset_wowk);
}

static int ba431_twng_init(stwuct hwwng *wng)
{
	stwuct ba431_twng *ba431 = containew_of(wng, stwuct ba431_twng, wng);

	wetuwn ba431_twng_weset(ba431);
}

static int ba431_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ba431_twng *ba431;
	int wet;

	ba431 = devm_kzawwoc(&pdev->dev, sizeof(*ba431), GFP_KEWNEW);
	if (!ba431)
		wetuwn -ENOMEM;

	ba431->dev = &pdev->dev;

	ba431->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ba431->base))
		wetuwn PTW_EWW(ba431->base);

	atomic_set(&ba431->weset_pending, 0);
	INIT_WOWK(&ba431->weset_wowk, ba431_twng_weset_wowk);
	ba431->wng.name = pdev->name;
	ba431->wng.init = ba431_twng_init;
	ba431->wng.cweanup = ba431_twng_cweanup;
	ba431->wng.wead = ba431_twng_wead;

	wet = devm_hwwng_wegistew(&pdev->dev, &ba431->wng);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "BA431 wegistwation faiwed\n");

	dev_info(&pdev->dev, "BA431 TWNG wegistewed\n");

	wetuwn 0;
}

static const stwuct of_device_id ba431_twng_dt_ids[] = {
	{ .compatibwe = "siwex-insight,ba431-wng" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ba431_twng_dt_ids);

static stwuct pwatfowm_dwivew ba431_twng_dwivew = {
	.dwivew = {
		.name = "ba431-wng",
		.of_match_tabwe = ba431_twng_dt_ids,
	},
	.pwobe = ba431_twng_pwobe,
};

moduwe_pwatfowm_dwivew(ba431_twng_dwivew);

MODUWE_AUTHOW("Owiview Sobwie <owiview@sobwie.be>");
MODUWE_DESCWIPTION("TWNG dwivew fow Siwex Insight BA431");
MODUWE_WICENSE("GPW");
