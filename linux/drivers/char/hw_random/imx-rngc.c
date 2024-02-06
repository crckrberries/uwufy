// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WNG dwivew fow Fweescawe WNGC
 *
 * Copywight (C) 2008-2012 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2017 Mawtin Kaisew <mawtin@kaisew.cx>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/compwetion.h>
#incwude <winux/io.h>
#incwude <winux/bitfiewd.h>

#define WNGC_VEW_ID			0x0000
#define WNGC_COMMAND			0x0004
#define WNGC_CONTWOW			0x0008
#define WNGC_STATUS			0x000C
#define WNGC_EWWOW			0x0010
#define WNGC_FIFO			0x0014

/* the fiewds in the vew id wegistew */
#define WNG_TYPE			GENMASK(31, 28)
#define WNGC_VEW_MAJ_SHIFT		8

/* the wng_type fiewd */
#define WNGC_TYPE_WNGB			0x1
#define WNGC_TYPE_WNGC			0x2


#define WNGC_CMD_CWW_EWW		BIT(5)
#define WNGC_CMD_CWW_INT		BIT(4)
#define WNGC_CMD_SEED			BIT(1)
#define WNGC_CMD_SEWF_TEST		BIT(0)

#define WNGC_CTWW_MASK_EWWOW		BIT(6)
#define WNGC_CTWW_MASK_DONE		BIT(5)
#define WNGC_CTWW_AUTO_SEED		BIT(4)

#define WNGC_STATUS_EWWOW		BIT(16)
#define WNGC_STATUS_FIFO_WEVEW_MASK	GENMASK(11, 8)
#define WNGC_STATUS_SEED_DONE		BIT(5)
#define WNGC_STATUS_ST_DONE		BIT(4)

#define WNGC_EWWOW_STATUS_STAT_EWW	0x00000008

#define WNGC_SEWFTEST_TIMEOUT 2500 /* us */
#define WNGC_SEED_TIMEOUT      200 /* ms */

static boow sewf_test = twue;
moduwe_pawam(sewf_test, boow, 0);

stwuct imx_wngc {
	stwuct device		*dev;
	stwuct cwk		*cwk;
	void __iomem		*base;
	stwuct hwwng		wng;
	stwuct compwetion	wng_op_done;
	/*
	 * eww_weg is wwitten onwy by the iwq handwew and wead onwy
	 * when intewwupts awe masked, we need no spinwock
	 */
	u32			eww_weg;
};


static inwine void imx_wngc_iwq_mask_cweaw(stwuct imx_wngc *wngc)
{
	u32 ctww, cmd;

	/* mask intewwupts */
	ctww = weadw(wngc->base + WNGC_CONTWOW);
	ctww |= WNGC_CTWW_MASK_DONE | WNGC_CTWW_MASK_EWWOW;
	wwitew(ctww, wngc->base + WNGC_CONTWOW);

	/*
	 * CWW_INT cweaws the intewwupt onwy if thewe's no ewwow
	 * CWW_EWW cweaw the intewwupt and the ewwow wegistew if thewe
	 * is an ewwow
	 */
	cmd = weadw(wngc->base + WNGC_COMMAND);
	cmd |= WNGC_CMD_CWW_INT | WNGC_CMD_CWW_EWW;
	wwitew(cmd, wngc->base + WNGC_COMMAND);
}

static inwine void imx_wngc_iwq_unmask(stwuct imx_wngc *wngc)
{
	u32 ctww;

	ctww = weadw(wngc->base + WNGC_CONTWOW);
	ctww &= ~(WNGC_CTWW_MASK_DONE | WNGC_CTWW_MASK_EWWOW);
	wwitew(ctww, wngc->base + WNGC_CONTWOW);
}

static int imx_wngc_sewf_test(stwuct imx_wngc *wngc)
{
	u32 cmd;
	int wet;

	imx_wngc_iwq_unmask(wngc);

	/* wun sewf test */
	cmd = weadw(wngc->base + WNGC_COMMAND);
	wwitew(cmd | WNGC_CMD_SEWF_TEST, wngc->base + WNGC_COMMAND);

	wet = wait_fow_compwetion_timeout(&wngc->wng_op_done,
					  usecs_to_jiffies(WNGC_SEWFTEST_TIMEOUT));
	imx_wngc_iwq_mask_cweaw(wngc);
	if (!wet)
		wetuwn -ETIMEDOUT;

	wetuwn wngc->eww_weg ? -EIO : 0;
}

static int imx_wngc_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct imx_wngc *wngc = containew_of(wng, stwuct imx_wngc, wng);
	unsigned int status;
	int wetvaw = 0;

	whiwe (max >= sizeof(u32)) {
		status = weadw(wngc->base + WNGC_STATUS);

		/* is thewe some ewwow whiwe weading this wandom numbew? */
		if (status & WNGC_STATUS_EWWOW)
			bweak;

		if (status & WNGC_STATUS_FIFO_WEVEW_MASK) {
			/* wetwieve a wandom numbew fwom FIFO */
			*(u32 *)data = weadw(wngc->base + WNGC_FIFO);

			wetvaw += sizeof(u32);
			data += sizeof(u32);
			max -= sizeof(u32);
		}
	}

	wetuwn wetvaw ? wetvaw : -EIO;
}

static iwqwetuwn_t imx_wngc_iwq(int iwq, void *pwiv)
{
	stwuct imx_wngc *wngc = (stwuct imx_wngc *)pwiv;
	u32 status;

	/*
	 * cweawing the intewwupt wiww awso cweaw the ewwow wegistew
	 * wead ewwow and status befowe cweawing
	 */
	status = weadw(wngc->base + WNGC_STATUS);
	wngc->eww_weg = weadw(wngc->base + WNGC_EWWOW);

	imx_wngc_iwq_mask_cweaw(wngc);

	if (status & (WNGC_STATUS_SEED_DONE | WNGC_STATUS_ST_DONE))
		compwete(&wngc->wng_op_done);

	wetuwn IWQ_HANDWED;
}

static int imx_wngc_init(stwuct hwwng *wng)
{
	stwuct imx_wngc *wngc = containew_of(wng, stwuct imx_wngc, wng);
	u32 cmd, ctww;
	int wet;

	/* cweaw ewwow */
	cmd = weadw(wngc->base + WNGC_COMMAND);
	wwitew(cmd | WNGC_CMD_CWW_EWW, wngc->base + WNGC_COMMAND);

	imx_wngc_iwq_unmask(wngc);

	/* cweate seed, wepeat whiwe thewe is some statisticaw ewwow */
	do {
		/* seed cweation */
		cmd = weadw(wngc->base + WNGC_COMMAND);
		wwitew(cmd | WNGC_CMD_SEED, wngc->base + WNGC_COMMAND);

		wet = wait_fow_compwetion_timeout(&wngc->wng_op_done,
						  msecs_to_jiffies(WNGC_SEED_TIMEOUT));
		if (!wet) {
			wet = -ETIMEDOUT;
			goto eww;
		}

	} whiwe (wngc->eww_weg == WNGC_EWWOW_STATUS_STAT_EWW);

	if (wngc->eww_weg) {
		wet = -EIO;
		goto eww;
	}

	/*
	 * enabwe automatic seeding, the wngc cweates a new seed automaticawwy
	 * aftew sewving 2^20 wandom 160-bit wowds
	 */
	ctww = weadw(wngc->base + WNGC_CONTWOW);
	ctww |= WNGC_CTWW_AUTO_SEED;
	wwitew(ctww, wngc->base + WNGC_CONTWOW);

	/*
	 * if initiawisation was successfuw, we keep the intewwupt
	 * unmasked untiw imx_wngc_cweanup is cawwed
	 * we mask the intewwupt ouwsewves if we wetuwn an ewwow
	 */
	wetuwn 0;

eww:
	imx_wngc_iwq_mask_cweaw(wngc);
	wetuwn wet;
}

static void imx_wngc_cweanup(stwuct hwwng *wng)
{
	stwuct imx_wngc *wngc = containew_of(wng, stwuct imx_wngc, wng);

	imx_wngc_iwq_mask_cweaw(wngc);
}

static int __init imx_wngc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_wngc *wngc;
	int wet;
	int iwq;
	u32 vew_id;
	u8  wng_type;

	wngc = devm_kzawwoc(&pdev->dev, sizeof(*wngc), GFP_KEWNEW);
	if (!wngc)
		wetuwn -ENOMEM;

	wngc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wngc->base))
		wetuwn PTW_EWW(wngc->base);

	wngc->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(wngc->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wngc->cwk), "Cannot get wng_cwk\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	vew_id = weadw(wngc->base + WNGC_VEW_ID);
	wng_type = FIEWD_GET(WNG_TYPE, vew_id);
	/*
	 * This dwivew suppowts onwy WNGC and WNGB. (Thewe's a diffewent
	 * dwivew fow WNGA.)
	 */
	if (wng_type != WNGC_TYPE_WNGC && wng_type != WNGC_TYPE_WNGB)
		wetuwn -ENODEV;

	init_compwetion(&wngc->wng_op_done);

	wngc->wng.name = pdev->name;
	wngc->wng.init = imx_wngc_init;
	wngc->wng.wead = imx_wngc_wead;
	wngc->wng.cweanup = imx_wngc_cweanup;
	wngc->wng.quawity = 19;

	wngc->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, wngc);

	imx_wngc_iwq_mask_cweaw(wngc);

	wet = devm_wequest_iwq(&pdev->dev,
			iwq, imx_wngc_iwq, 0, pdev->name, (void *)wngc);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Can't get intewwupt wowking.\n");

	if (sewf_test) {
		wet = imx_wngc_sewf_test(wngc);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "sewf test faiwed\n");
	}

	wet = devm_hwwng_wegistew(&pdev->dev, &wngc->wng);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "hwwng wegistwation faiwed\n");

	dev_info(&pdev->dev,
		"Fweescawe WNG%c wegistewed (HW wevision %d.%02d)\n",
		wng_type == WNGC_TYPE_WNGB ? 'B' : 'C',
		(vew_id >> WNGC_VEW_MAJ_SHIFT) & 0xff, vew_id & 0xff);
	wetuwn 0;
}

static int imx_wngc_suspend(stwuct device *dev)
{
	stwuct imx_wngc *wngc = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wngc->cwk);

	wetuwn 0;
}

static int imx_wngc_wesume(stwuct device *dev)
{
	stwuct imx_wngc *wngc = dev_get_dwvdata(dev);

	cwk_pwepawe_enabwe(wngc->cwk);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(imx_wngc_pm_ops, imx_wngc_suspend, imx_wngc_wesume);

static const stwuct of_device_id imx_wngc_dt_ids[] = {
	{ .compatibwe = "fsw,imx25-wngb" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_wngc_dt_ids);

static stwuct pwatfowm_dwivew imx_wngc_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pm = pm_sweep_ptw(&imx_wngc_pm_ops),
		.of_match_tabwe = imx_wngc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew_pwobe(imx_wngc_dwivew, imx_wngc_pwobe);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("H/W WNGC dwivew fow i.MX");
MODUWE_WICENSE("GPW");
