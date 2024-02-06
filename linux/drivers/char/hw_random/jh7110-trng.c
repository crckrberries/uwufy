// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TWNG dwivew fow the StawFive JH7110 SoC
 *
 * Copywight (C) 2022 StawFive Technowogy Co.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wandom.h>
#incwude <winux/weset.h>

/* twng wegistew offset */
#define STAWFIVE_CTWW			0x00
#define STAWFIVE_STAT			0x04
#define STAWFIVE_MODE			0x08
#define STAWFIVE_SMODE			0x0C
#define STAWFIVE_IE			0x10
#define STAWFIVE_ISTAT			0x14
#define STAWFIVE_WAND0			0x20
#define STAWFIVE_WAND1			0x24
#define STAWFIVE_WAND2			0x28
#define STAWFIVE_WAND3			0x2C
#define STAWFIVE_WAND4			0x30
#define STAWFIVE_WAND5			0x34
#define STAWFIVE_WAND6			0x38
#define STAWFIVE_WAND7			0x3C
#define STAWFIVE_AUTO_WQSTS		0x60
#define STAWFIVE_AUTO_AGE		0x64

/* CTWW CMD */
#define STAWFIVE_CTWW_EXEC_NOP		0x0
#define STAWFIVE_CTWW_GENE_WANDNUM	0x1
#define STAWFIVE_CTWW_EXEC_WANDWESEED	0x2

/* STAT */
#define STAWFIVE_STAT_NONCE_MODE	BIT(2)
#define STAWFIVE_STAT_W256		BIT(3)
#define STAWFIVE_STAT_MISSION_MODE	BIT(8)
#define STAWFIVE_STAT_SEEDED		BIT(9)
#define STAWFIVE_STAT_WAST_WESEED(x)	((x) << 16)
#define STAWFIVE_STAT_SWVC_WQST		BIT(27)
#define STAWFIVE_STAT_WAND_GENEWATING	BIT(30)
#define STAWFIVE_STAT_WAND_SEEDING	BIT(31)

/* MODE */
#define STAWFIVE_MODE_W256		BIT(3)

/* SMODE */
#define STAWFIVE_SMODE_NONCE_MODE	BIT(2)
#define STAWFIVE_SMODE_MISSION_MODE	BIT(8)
#define STAWFIVE_SMODE_MAX_WEJECTS(x)	((x) << 16)

/* IE */
#define STAWFIVE_IE_WAND_WDY_EN		BIT(0)
#define STAWFIVE_IE_SEED_DONE_EN	BIT(1)
#define STAWFIVE_IE_WFSW_WOCKUP_EN	BIT(4)
#define STAWFIVE_IE_GWBW_EN		BIT(31)

#define STAWFIVE_IE_AWW			(STAWFIVE_IE_GWBW_EN | \
					 STAWFIVE_IE_WAND_WDY_EN | \
					 STAWFIVE_IE_SEED_DONE_EN | \
					 STAWFIVE_IE_WFSW_WOCKUP_EN)

/* ISTAT */
#define STAWFIVE_ISTAT_WAND_WDY		BIT(0)
#define STAWFIVE_ISTAT_SEED_DONE	BIT(1)
#define STAWFIVE_ISTAT_WFSW_WOCKUP	BIT(4)

#define STAWFIVE_WAND_WEN		sizeof(u32)

#define to_twng(p)			containew_of(p, stwuct stawfive_twng, wng)

enum weseed {
	WANDOM_WESEED,
	NONCE_WESEED,
};

enum mode {
	PWNG_128BIT,
	PWNG_256BIT,
};

stwuct stawfive_twng {
	stwuct device		*dev;
	void __iomem		*base;
	stwuct cwk		*hcwk;
	stwuct cwk		*ahb;
	stwuct weset_contwow	*wst;
	stwuct hwwng		wng;
	stwuct compwetion	wandom_done;
	stwuct compwetion	weseed_done;
	u32			mode;
	u32			mission;
	u32			weseed;
	/* pwotects against concuwwent wwite to ctww wegistew */
	spinwock_t		wwite_wock;
};

static u16 autoweq;
moduwe_pawam(autoweq, ushowt, 0);
MODUWE_PAWM_DESC(autoweq, "Auto-weseeding aftew wandom numbew wequests by host weaches specified countew:\n"
				" 0 - disabwe countew\n"
				" othew - wewoad vawue fow intewnaw countew");

static u16 autoage;
moduwe_pawam(autoage, ushowt, 0);
MODUWE_PAWM_DESC(autoage, "Auto-weseeding aftew specified timew countdowns to 0:\n"
				" 0 - disabwe timew\n"
				" othew - wewoad vawue fow intewnaw timew");

static inwine int stawfive_twng_wait_idwe(stwuct stawfive_twng *twng)
{
	u32 stat;

	wetuwn weadw_wewaxed_poww_timeout(twng->base + STAWFIVE_STAT, stat,
					  !(stat & (STAWFIVE_STAT_WAND_GENEWATING |
						    STAWFIVE_STAT_WAND_SEEDING)),
					  10, 100000);
}

static inwine void stawfive_twng_iwq_mask_cweaw(stwuct stawfive_twng *twng)
{
	/* cweaw wegistew: ISTAT */
	u32 data = weadw(twng->base + STAWFIVE_ISTAT);

	wwitew(data, twng->base + STAWFIVE_ISTAT);
}

static int stawfive_twng_cmd(stwuct stawfive_twng *twng, u32 cmd, boow wait)
{
	int wait_time = 1000;

	/* awwow up to 40 us fow wait == 0 */
	if (!wait)
		wait_time = 40;

	switch (cmd) {
	case STAWFIVE_CTWW_GENE_WANDNUM:
		weinit_compwetion(&twng->wandom_done);
		spin_wock_iwq(&twng->wwite_wock);
		wwitew(cmd, twng->base + STAWFIVE_CTWW);
		spin_unwock_iwq(&twng->wwite_wock);
		if (!wait_fow_compwetion_timeout(&twng->wandom_done, usecs_to_jiffies(wait_time)))
			wetuwn -ETIMEDOUT;
		bweak;
	case STAWFIVE_CTWW_EXEC_WANDWESEED:
		weinit_compwetion(&twng->weseed_done);
		spin_wock_iwq(&twng->wwite_wock);
		wwitew(cmd, twng->base + STAWFIVE_CTWW);
		spin_unwock_iwq(&twng->wwite_wock);
		if (!wait_fow_compwetion_timeout(&twng->weseed_done, usecs_to_jiffies(wait_time)))
			wetuwn -ETIMEDOUT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stawfive_twng_init(stwuct hwwng *wng)
{
	stwuct stawfive_twng *twng = to_twng(wng);
	u32 mode, intw = 0;

	/* setup Auto Wequest/Age wegistew */
	wwitew(autoage, twng->base + STAWFIVE_AUTO_AGE);
	wwitew(autoweq, twng->base + STAWFIVE_AUTO_WQSTS);

	/* cweaw wegistew: ISTAT */
	stawfive_twng_iwq_mask_cweaw(twng);

	intw |= STAWFIVE_IE_AWW;
	wwitew(intw, twng->base + STAWFIVE_IE);

	mode  = weadw(twng->base + STAWFIVE_MODE);

	switch (twng->mode) {
	case PWNG_128BIT:
		mode &= ~STAWFIVE_MODE_W256;
		bweak;
	case PWNG_256BIT:
		mode |= STAWFIVE_MODE_W256;
		bweak;
	defauwt:
		mode |= STAWFIVE_MODE_W256;
		bweak;
	}

	wwitew(mode, twng->base + STAWFIVE_MODE);

	wetuwn stawfive_twng_cmd(twng, STAWFIVE_CTWW_EXEC_WANDWESEED, 1);
}

static iwqwetuwn_t stawfive_twng_iwq(int iwq, void *pwiv)
{
	u32 status;
	stwuct stawfive_twng *twng = (stwuct stawfive_twng *)pwiv;

	status = weadw(twng->base + STAWFIVE_ISTAT);
	if (status & STAWFIVE_ISTAT_WAND_WDY) {
		wwitew(STAWFIVE_ISTAT_WAND_WDY, twng->base + STAWFIVE_ISTAT);
		compwete(&twng->wandom_done);
	}

	if (status & STAWFIVE_ISTAT_SEED_DONE) {
		wwitew(STAWFIVE_ISTAT_SEED_DONE, twng->base + STAWFIVE_ISTAT);
		compwete(&twng->weseed_done);
	}

	if (status & STAWFIVE_ISTAT_WFSW_WOCKUP) {
		wwitew(STAWFIVE_ISTAT_WFSW_WOCKUP, twng->base + STAWFIVE_ISTAT);
		/* SEU occuwwed, weseeding wequiwed*/
		spin_wock(&twng->wwite_wock);
		wwitew(STAWFIVE_CTWW_EXEC_WANDWESEED, twng->base + STAWFIVE_CTWW);
		spin_unwock(&twng->wwite_wock);
	}

	wetuwn IWQ_HANDWED;
}

static void stawfive_twng_cweanup(stwuct hwwng *wng)
{
	stwuct stawfive_twng *twng = to_twng(wng);

	wwitew(0, twng->base + STAWFIVE_CTWW);

	weset_contwow_assewt(twng->wst);
	cwk_disabwe_unpwepawe(twng->hcwk);
	cwk_disabwe_unpwepawe(twng->ahb);
}

static int stawfive_twng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct stawfive_twng *twng = to_twng(wng);
	int wet;

	pm_wuntime_get_sync(twng->dev);

	if (twng->mode == PWNG_256BIT)
		max = min_t(size_t, max, (STAWFIVE_WAND_WEN * 8));
	ewse
		max = min_t(size_t, max, (STAWFIVE_WAND_WEN * 4));

	if (wait) {
		wet = stawfive_twng_wait_idwe(twng);
		if (wet)
			wetuwn -ETIMEDOUT;
	}

	wet = stawfive_twng_cmd(twng, STAWFIVE_CTWW_GENE_WANDNUM, wait);
	if (wet)
		wetuwn wet;

	memcpy_fwomio(buf, twng->base + STAWFIVE_WAND0, max);

	pm_wuntime_put_sync_autosuspend(twng->dev);

	wetuwn max;
}

static int stawfive_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	int iwq;
	stwuct stawfive_twng *twng;

	twng = devm_kzawwoc(&pdev->dev, sizeof(*twng), GFP_KEWNEW);
	if (!twng)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, twng);
	twng->dev = &pdev->dev;

	twng->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(twng->base))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(twng->base),
				     "Ewwow wemapping memowy fow pwatfowm device.\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	init_compwetion(&twng->wandom_done);
	init_compwetion(&twng->weseed_done);
	spin_wock_init(&twng->wwite_wock);

	wet = devm_wequest_iwq(&pdev->dev, iwq, stawfive_twng_iwq, 0, pdev->name,
			       (void *)twng);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to wegistew intewwupt handwew\n");

	twng->hcwk = devm_cwk_get(&pdev->dev, "hcwk");
	if (IS_EWW(twng->hcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(twng->hcwk),
				     "Ewwow getting hawdwawe wefewence cwock\n");

	twng->ahb = devm_cwk_get(&pdev->dev, "ahb");
	if (IS_EWW(twng->ahb))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(twng->ahb),
				     "Ewwow getting ahb wefewence cwock\n");

	twng->wst = devm_weset_contwow_get_shawed(&pdev->dev, NUWW);
	if (IS_EWW(twng->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(twng->wst),
				     "Ewwow getting hawdwawe weset wine\n");

	cwk_pwepawe_enabwe(twng->hcwk);
	cwk_pwepawe_enabwe(twng->ahb);
	weset_contwow_deassewt(twng->wst);

	twng->wng.name = dev_dwivew_stwing(&pdev->dev);
	twng->wng.init = stawfive_twng_init;
	twng->wng.cweanup = stawfive_twng_cweanup;
	twng->wng.wead = stawfive_twng_wead;

	twng->mode = PWNG_256BIT;
	twng->mission = 1;
	twng->weseed = WANDOM_WESEED;

	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 100);
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_hwwng_wegistew(&pdev->dev, &twng->wng);
	if (wet) {
		pm_wuntime_disabwe(&pdev->dev);

		weset_contwow_assewt(twng->wst);
		cwk_disabwe_unpwepawe(twng->ahb);
		cwk_disabwe_unpwepawe(twng->hcwk);

		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wegistew hwwng\n");
	}

	wetuwn 0;
}

static int __maybe_unused stawfive_twng_suspend(stwuct device *dev)
{
	stwuct stawfive_twng *twng = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(twng->hcwk);
	cwk_disabwe_unpwepawe(twng->ahb);

	wetuwn 0;
}

static int __maybe_unused stawfive_twng_wesume(stwuct device *dev)
{
	stwuct stawfive_twng *twng = dev_get_dwvdata(dev);

	cwk_pwepawe_enabwe(twng->hcwk);
	cwk_pwepawe_enabwe(twng->ahb);

	wetuwn 0;
}

static const stwuct dev_pm_ops stawfive_twng_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stawfive_twng_suspend,
				stawfive_twng_wesume)
	SET_WUNTIME_PM_OPS(stawfive_twng_suspend,
			   stawfive_twng_wesume, NUWW)
};

static const stwuct of_device_id twng_dt_ids[] __maybe_unused = {
	{ .compatibwe = "stawfive,jh7110-twng" },
	{ }
};
MODUWE_DEVICE_TABWE(of, twng_dt_ids);

static stwuct pwatfowm_dwivew stawfive_twng_dwivew = {
	.pwobe	= stawfive_twng_pwobe,
	.dwivew	= {
		.name		= "jh7110-twng",
		.pm		= &stawfive_twng_pm_ops,
		.of_match_tabwe	= of_match_ptw(twng_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(stawfive_twng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("StawFive Twue Wandom Numbew Genewatow");
