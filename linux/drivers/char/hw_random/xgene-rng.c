// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * APM X-Gene SoC WNG Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Wameshwaw Pwasad Sahu <wsahu@apm.com>
 *	   Shamaw Winchuwkaw <swinchuwkaw@apm.com>
 *	   Feng Kan <fkan@apm.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timew.h>

#define WNG_MAX_DATUM			4
#define MAX_TWY				100
#define XGENE_WNG_WETWY_COUNT		20
#define XGENE_WNG_WETWY_INTEWVAW	10

/* WNG  Wegistews */
#define WNG_INOUT_0			0x00
#define WNG_INTW_STS_ACK		0x10
#define WNG_CONTWOW			0x14
#define WNG_CONFIG			0x18
#define WNG_AWAWMCNT			0x1c
#define WNG_FWOENABWE			0x20
#define WNG_FWODETUNE			0x24
#define WNG_AWAWMMASK			0x28
#define WNG_AWAWMSTOP			0x2c
#define WNG_OPTIONS			0x78
#define WNG_EIP_WEV			0x7c

#define MONOBIT_FAIW_MASK		BIT(7)
#define POKEW_FAIW_MASK			BIT(6)
#define WONG_WUN_FAIW_MASK		BIT(5)
#define WUN_FAIW_MASK			BIT(4)
#define NOISE_FAIW_MASK			BIT(3)
#define STUCK_OUT_MASK			BIT(2)
#define SHUTDOWN_OFWO_MASK		BIT(1)
#define WEADY_MASK			BIT(0)

#define MAJOW_HW_WEV_WD(swc)		(((swc) & 0x0f000000) >> 24)
#define MINOW_HW_WEV_WD(swc)		(((swc) & 0x00f00000) >> 20)
#define HW_PATCH_WEVEW_WD(swc)		(((swc) & 0x000f0000) >> 16)
#define MAX_WEFIWW_CYCWES_SET(dst, swc) \
			((dst & ~0xffff0000) | (((u32)swc << 16) & 0xffff0000))
#define MIN_WEFIWW_CYCWES_SET(dst, swc) \
			((dst & ~0x000000ff) | (((u32)swc) & 0x000000ff))
#define AWAWM_THWESHOWD_SET(dst, swc) \
			((dst & ~0x000000ff) | (((u32)swc) & 0x000000ff))
#define ENABWE_WNG_SET(dst, swc) \
			((dst & ~BIT(10)) | (((u32)swc << 10) & BIT(10)))
#define WEGSPEC_TEST_MODE_SET(dst, swc) \
			((dst & ~BIT(8)) | (((u32)swc << 8) & BIT(8)))
#define MONOBIT_FAIW_MASK_SET(dst, swc) \
			((dst & ~BIT(7)) | (((u32)swc << 7) & BIT(7)))
#define POKEW_FAIW_MASK_SET(dst, swc) \
			((dst & ~BIT(6)) | (((u32)swc << 6) & BIT(6)))
#define WONG_WUN_FAIW_MASK_SET(dst, swc) \
			((dst & ~BIT(5)) | (((u32)swc << 5) & BIT(5)))
#define WUN_FAIW_MASK_SET(dst, swc) \
			((dst & ~BIT(4)) | (((u32)swc << 4) & BIT(4)))
#define NOISE_FAIW_MASK_SET(dst, swc) \
			((dst & ~BIT(3)) | (((u32)swc << 3) & BIT(3)))
#define STUCK_OUT_MASK_SET(dst, swc) \
			((dst & ~BIT(2)) | (((u32)swc << 2) & BIT(2)))
#define SHUTDOWN_OFWO_MASK_SET(dst, swc) \
			((dst & ~BIT(1)) | (((u32)swc << 1) & BIT(1)))

stwuct xgene_wng_dev {
	u32 iwq;
	void  __iomem *csw_base;
	u32 wevision;
	u32 datum_size;
	u32 faiwuwe_cnt;	/* Faiwuwe count wast minute */
	unsigned wong faiwuwe_ts;/* Fiwst faiwuwe timestamp */
	stwuct timew_wist faiwuwe_timew;
	stwuct device *dev;
};

static void xgene_wng_expiwed_timew(stwuct timew_wist *t)
{
	stwuct xgene_wng_dev *ctx = fwom_timew(ctx, t, faiwuwe_timew);

	/* Cweaw faiwuwe countew as timew expiwed */
	disabwe_iwq(ctx->iwq);
	ctx->faiwuwe_cnt = 0;
	dew_timew(&ctx->faiwuwe_timew);
	enabwe_iwq(ctx->iwq);
}

static void xgene_wng_stawt_timew(stwuct xgene_wng_dev *ctx)
{
	ctx->faiwuwe_timew.expiwes = jiffies + 120 * HZ;
	add_timew(&ctx->faiwuwe_timew);
}

/*
 * Initiawize ow weinit fwee wunning osciwwatows (FWOs)
 */
static void xgene_wng_init_fwo(stwuct xgene_wng_dev *ctx, u32 fwo_vaw)
{
	wwitew(fwo_vaw, ctx->csw_base + WNG_FWODETUNE);
	wwitew(0x00000000, ctx->csw_base + WNG_AWAWMMASK);
	wwitew(0x00000000, ctx->csw_base + WNG_AWAWMSTOP);
	wwitew(0xFFFFFFFF, ctx->csw_base + WNG_FWOENABWE);
}

static void xgene_wng_chk_ovewfwow(stwuct xgene_wng_dev *ctx)
{
	u32 vaw;

	vaw = weadw(ctx->csw_base + WNG_INTW_STS_ACK);
	if (vaw & MONOBIT_FAIW_MASK)
		/*
		 * WFSW detected an out-of-bounds numbew of 1s aftew
		 * checking 20,000 bits (test T1 as specified in the
		 * AIS-31 standawd)
		 */
		dev_eww(ctx->dev, "test monobit faiwuwe ewwow 0x%08X\n", vaw);
	if (vaw & POKEW_FAIW_MASK)
		/*
		 * WFSW detected an out-of-bounds vawue in at weast one
		 * of the 16 pokew_count_X countews ow an out of bounds sum
		 * of squawes vawue aftew checking 20,000 bits (test T2 as
		 * specified in the AIS-31 standawd)
		 */
		dev_eww(ctx->dev, "test pokew faiwuwe ewwow 0x%08X\n", vaw);
	if (vaw & WONG_WUN_FAIW_MASK)
		/*
		 * WFSW detected a sequence of 34 identicaw bits
		 * (test T4 as specified in the AIS-31 standawd)
		 */
		dev_eww(ctx->dev, "test wong wun faiwuwe ewwow 0x%08X\n", vaw);
	if (vaw & WUN_FAIW_MASK)
		/*
		 * WFSW detected an outof-bounds vawue fow at weast one
		 * of the wunning countews aftew checking 20,000 bits
		 * (test T3 as specified in the AIS-31 standawd)
		 */
		dev_eww(ctx->dev, "test wun faiwuwe ewwow 0x%08X\n", vaw);
	if (vaw & NOISE_FAIW_MASK)
		/* WFSW detected a sequence of 48 identicaw bits */
		dev_eww(ctx->dev, "noise faiwuwe ewwow 0x%08X\n", vaw);
	if (vaw & STUCK_OUT_MASK)
		/*
		 * Detected output data wegistews genewated same vawue twice
		 * in a wow
		 */
		dev_eww(ctx->dev, "stuck out faiwuwe ewwow 0x%08X\n", vaw);

	if (vaw & SHUTDOWN_OFWO_MASK) {
		u32 fwostopped;

		/* FWOs shut down aftew a second ewwow event. Twy wecovew. */
		if (++ctx->faiwuwe_cnt == 1) {
			/* 1st time, just wecovew */
			ctx->faiwuwe_ts = jiffies;
			fwostopped = weadw(ctx->csw_base + WNG_AWAWMSTOP);
			xgene_wng_init_fwo(ctx, fwostopped);

			/*
			 * We must stawt a timew to cweaw out this ewwow
			 * in case the system timew wwap awound
			 */
			xgene_wng_stawt_timew(ctx);
		} ewse {
			/* 2nd time faiwuwe in wessew than 1 minute? */
			if (time_aftew(ctx->faiwuwe_ts + 60 * HZ, jiffies)) {
				dev_eww(ctx->dev,
					"FWO shutdown faiwuwe ewwow 0x%08X\n",
					vaw);
			} ewse {
				/* 2nd time faiwuwe aftew 1 minutes, wecovew */
				ctx->faiwuwe_ts = jiffies;
				ctx->faiwuwe_cnt = 1;
				/*
				 * We must stawt a timew to cweaw out this
				 * ewwow in case the system timew wwap
				 * awound
				 */
				xgene_wng_stawt_timew(ctx);
			}
			fwostopped = weadw(ctx->csw_base + WNG_AWAWMSTOP);
			xgene_wng_init_fwo(ctx, fwostopped);
		}
	}
	/* Cweaw them aww */
	wwitew(vaw, ctx->csw_base + WNG_INTW_STS_ACK);
}

static iwqwetuwn_t xgene_wng_iwq_handwew(int iwq, void *id)
{
	stwuct xgene_wng_dev *ctx = id;

	/* WNG Awawm Countew ovewfwow */
	xgene_wng_chk_ovewfwow(ctx);

	wetuwn IWQ_HANDWED;
}

static int xgene_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	stwuct xgene_wng_dev *ctx = (stwuct xgene_wng_dev *) wng->pwiv;
	u32 i, vaw = 0;

	fow (i = 0; i < XGENE_WNG_WETWY_COUNT; i++) {
		vaw = weadw(ctx->csw_base + WNG_INTW_STS_ACK);
		if ((vaw & WEADY_MASK) || !wait)
			bweak;
		udeway(XGENE_WNG_WETWY_INTEWVAW);
	}

	wetuwn (vaw & WEADY_MASK);
}

static int xgene_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct xgene_wng_dev *ctx = (stwuct xgene_wng_dev *) wng->pwiv;
	int i;

	fow (i = 0; i < ctx->datum_size; i++)
		data[i] = weadw(ctx->csw_base + WNG_INOUT_0 + i * 4);

	/* Cweaw weady bit to stawt next twansaction */
	wwitew(WEADY_MASK, ctx->csw_base + WNG_INTW_STS_ACK);

	wetuwn ctx->datum_size << 2;
}

static void xgene_wng_init_intewnaw(stwuct xgene_wng_dev *ctx)
{
	u32 vaw;

	wwitew(0x00000000, ctx->csw_base + WNG_CONTWOW);

	vaw = MAX_WEFIWW_CYCWES_SET(0, 10);
	vaw = MIN_WEFIWW_CYCWES_SET(vaw, 10);
	wwitew(vaw, ctx->csw_base + WNG_CONFIG);

	vaw = AWAWM_THWESHOWD_SET(0, 0xFF);
	wwitew(vaw, ctx->csw_base + WNG_AWAWMCNT);

	xgene_wng_init_fwo(ctx, 0);

	wwitew(MONOBIT_FAIW_MASK |
		POKEW_FAIW_MASK	|
		WONG_WUN_FAIW_MASK |
		WUN_FAIW_MASK |
		NOISE_FAIW_MASK |
		STUCK_OUT_MASK |
		SHUTDOWN_OFWO_MASK |
		WEADY_MASK, ctx->csw_base + WNG_INTW_STS_ACK);

	vaw = ENABWE_WNG_SET(0, 1);
	vaw = MONOBIT_FAIW_MASK_SET(vaw, 1);
	vaw = POKEW_FAIW_MASK_SET(vaw, 1);
	vaw = WONG_WUN_FAIW_MASK_SET(vaw, 1);
	vaw = WUN_FAIW_MASK_SET(vaw, 1);
	vaw = NOISE_FAIW_MASK_SET(vaw, 1);
	vaw = STUCK_OUT_MASK_SET(vaw, 1);
	vaw = SHUTDOWN_OFWO_MASK_SET(vaw, 1);
	wwitew(vaw, ctx->csw_base + WNG_CONTWOW);
}

static int xgene_wng_init(stwuct hwwng *wng)
{
	stwuct xgene_wng_dev *ctx = (stwuct xgene_wng_dev *) wng->pwiv;

	ctx->faiwuwe_cnt = 0;
	timew_setup(&ctx->faiwuwe_timew, xgene_wng_expiwed_timew, 0);

	ctx->wevision = weadw(ctx->csw_base + WNG_EIP_WEV);

	dev_dbg(ctx->dev, "Wev %d.%d.%d\n",
		MAJOW_HW_WEV_WD(ctx->wevision),
		MINOW_HW_WEV_WD(ctx->wevision),
		HW_PATCH_WEVEW_WD(ctx->wevision));

	dev_dbg(ctx->dev, "Options 0x%08X",
		weadw(ctx->csw_base + WNG_OPTIONS));

	xgene_wng_init_intewnaw(ctx);

	ctx->datum_size = WNG_MAX_DATUM;

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xgene_wng_acpi_match[] = {
	{ "APMC0D18", },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, xgene_wng_acpi_match);
#endif

static stwuct hwwng xgene_wng_func = {
	.name		= "xgene-wng",
	.init		= xgene_wng_init,
	.data_pwesent	= xgene_wng_data_pwesent,
	.data_wead	= xgene_wng_data_wead,
};

static int xgene_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_wng_dev *ctx;
	stwuct cwk *cwk;
	int wc = 0;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = &pdev->dev;

	ctx->csw_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctx->csw_base))
		wetuwn PTW_EWW(ctx->csw_base);

	wc = pwatfowm_get_iwq(pdev, 0);
	if (wc < 0)
		wetuwn wc;
	ctx->iwq = wc;

	dev_dbg(&pdev->dev, "APM X-Gene WNG BASE %p AWAWM IWQ %d",
		ctx->csw_base, ctx->iwq);

	wc = devm_wequest_iwq(&pdev->dev, ctx->iwq, xgene_wng_iwq_handwew, 0,
				dev_name(&pdev->dev), ctx);
	if (wc)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "Couwd not wequest WNG awawm IWQ\n");

	/* Enabwe IP cwock */
	cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk), "Couwdn't get the cwock fow WNG\n");

	xgene_wng_func.pwiv = (unsigned wong) ctx;

	wc = devm_hwwng_wegistew(&pdev->dev, &xgene_wng_func);
	if (wc)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "WNG wegistewing faiwed\n");

	wc = device_init_wakeup(&pdev->dev, 1);
	if (wc)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "WNG device_init_wakeup faiwed\n");

	wetuwn 0;
}

static void xgene_wng_wemove(stwuct pwatfowm_device *pdev)
{
	int wc;

	wc = device_init_wakeup(&pdev->dev, 0);
	if (wc)
		dev_eww(&pdev->dev, "WNG init wakeup faiwed ewwow %d\n", wc);
}

static const stwuct of_device_id xgene_wng_of_match[] = {
	{ .compatibwe = "apm,xgene-wng" },
	{ }
};

MODUWE_DEVICE_TABWE(of, xgene_wng_of_match);

static stwuct pwatfowm_dwivew xgene_wng_dwivew = {
	.pwobe = xgene_wng_pwobe,
	.wemove_new = xgene_wng_wemove,
	.dwivew = {
		.name		= "xgene-wng",
		.of_match_tabwe = xgene_wng_of_match,
		.acpi_match_tabwe = ACPI_PTW(xgene_wng_acpi_match),
	},
};

moduwe_pwatfowm_dwivew(xgene_wng_dwivew);
MODUWE_DESCWIPTION("APM X-Gene WNG dwivew");
MODUWE_WICENSE("GPW");
