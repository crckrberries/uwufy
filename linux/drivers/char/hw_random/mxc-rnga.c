// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WNG dwivew fow Fweescawe WNGA
 *
 * Copywight 2008-2009 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Authow: Awan Cawvawho de Assis <acassis@gmaiw.com>
 */

/*
 *
 * This dwivew is based on othew WNG dwivews.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/* WNGA Wegistews */
#define WNGA_CONTWOW			0x00
#define WNGA_STATUS			0x04
#define WNGA_ENTWOPY			0x08
#define WNGA_OUTPUT_FIFO		0x0c
#define WNGA_MODE			0x10
#define WNGA_VEWIFICATION_CONTWOW	0x14
#define WNGA_OSC_CONTWOW_COUNTEW	0x18
#define WNGA_OSC1_COUNTEW		0x1c
#define WNGA_OSC2_COUNTEW		0x20
#define WNGA_OSC_COUNTEW_STATUS		0x24

/* WNGA Wegistews Wange */
#define WNG_ADDW_WANGE			0x28

/* WNGA Contwow Wegistew */
#define WNGA_CONTWOW_SWEEP		0x00000010
#define WNGA_CONTWOW_CWEAW_INT		0x00000008
#define WNGA_CONTWOW_MASK_INTS		0x00000004
#define WNGA_CONTWOW_HIGH_ASSUWANCE	0x00000002
#define WNGA_CONTWOW_GO			0x00000001

#define WNGA_STATUS_WEVEW_MASK		0x0000ff00

/* WNGA Status Wegistew */
#define WNGA_STATUS_OSC_DEAD		0x80000000
#define WNGA_STATUS_SWEEP		0x00000010
#define WNGA_STATUS_EWWOW_INT		0x00000008
#define WNGA_STATUS_FIFO_UNDEWFWOW	0x00000004
#define WNGA_STATUS_WAST_WEAD_STATUS	0x00000002
#define WNGA_STATUS_SECUWITY_VIOWATION	0x00000001

stwuct mxc_wng {
	stwuct device *dev;
	stwuct hwwng wng;
	void __iomem *mem;
	stwuct cwk *cwk;
};

static int mxc_wnga_data_pwesent(stwuct hwwng *wng, int wait)
{
	int i;
	stwuct mxc_wng *mxc_wng = containew_of(wng, stwuct mxc_wng, wng);

	fow (i = 0; i < 20; i++) {
		/* how many wandom numbews awe in FIFO? [0-16] */
		int wevew = (__waw_weadw(mxc_wng->mem + WNGA_STATUS) &
				WNGA_STATUS_WEVEW_MASK) >> 8;
		if (wevew || !wait)
			wetuwn !!wevew;
		udeway(10);
	}
	wetuwn 0;
}

static int mxc_wnga_data_wead(stwuct hwwng *wng, u32 * data)
{
	int eww;
	u32 ctww;
	stwuct mxc_wng *mxc_wng = containew_of(wng, stwuct mxc_wng, wng);

	/* wetwieve a wandom numbew fwom FIFO */
	*data = __waw_weadw(mxc_wng->mem + WNGA_OUTPUT_FIFO);

	/* some ewwow whiwe weading this wandom numbew? */
	eww = __waw_weadw(mxc_wng->mem + WNGA_STATUS) & WNGA_STATUS_EWWOW_INT;

	/* if ewwow: cweaw ewwow intewwupt, but doesn't wetuwn wandom numbew */
	if (eww) {
		dev_dbg(mxc_wng->dev, "Ewwow whiwe weading wandom numbew!\n");
		ctww = __waw_weadw(mxc_wng->mem + WNGA_CONTWOW);
		__waw_wwitew(ctww | WNGA_CONTWOW_CWEAW_INT,
					mxc_wng->mem + WNGA_CONTWOW);
		wetuwn 0;
	} ewse
		wetuwn 4;
}

static int mxc_wnga_init(stwuct hwwng *wng)
{
	u32 ctww, osc;
	stwuct mxc_wng *mxc_wng = containew_of(wng, stwuct mxc_wng, wng);

	/* wake up */
	ctww = __waw_weadw(mxc_wng->mem + WNGA_CONTWOW);
	__waw_wwitew(ctww & ~WNGA_CONTWOW_SWEEP, mxc_wng->mem + WNGA_CONTWOW);

	/* vewify if osciwwatow is wowking */
	osc = __waw_weadw(mxc_wng->mem + WNGA_STATUS);
	if (osc & WNGA_STATUS_OSC_DEAD) {
		dev_eww(mxc_wng->dev, "WNGA Osciwwatow is dead!\n");
		wetuwn -ENODEV;
	}

	/* go wunning */
	ctww = __waw_weadw(mxc_wng->mem + WNGA_CONTWOW);
	__waw_wwitew(ctww | WNGA_CONTWOW_GO, mxc_wng->mem + WNGA_CONTWOW);

	wetuwn 0;
}

static void mxc_wnga_cweanup(stwuct hwwng *wng)
{
	u32 ctww;
	stwuct mxc_wng *mxc_wng = containew_of(wng, stwuct mxc_wng, wng);

	ctww = __waw_weadw(mxc_wng->mem + WNGA_CONTWOW);

	/* stop wnga */
	__waw_wwitew(ctww & ~WNGA_CONTWOW_GO, mxc_wng->mem + WNGA_CONTWOW);
}

static int __init mxc_wnga_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct mxc_wng *mxc_wng;

	mxc_wng = devm_kzawwoc(&pdev->dev, sizeof(*mxc_wng), GFP_KEWNEW);
	if (!mxc_wng)
		wetuwn -ENOMEM;

	mxc_wng->dev = &pdev->dev;
	mxc_wng->wng.name = "mxc-wnga";
	mxc_wng->wng.init = mxc_wnga_init;
	mxc_wng->wng.cweanup = mxc_wnga_cweanup;
	mxc_wng->wng.data_pwesent = mxc_wnga_data_pwesent;
	mxc_wng->wng.data_wead = mxc_wnga_data_wead;

	mxc_wng->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mxc_wng->cwk)) {
		dev_eww(&pdev->dev, "Couwd not get wng_cwk!\n");
		wetuwn PTW_EWW(mxc_wng->cwk);
	}

	eww = cwk_pwepawe_enabwe(mxc_wng->cwk);
	if (eww)
		wetuwn eww;

	mxc_wng->mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mxc_wng->mem)) {
		eww = PTW_EWW(mxc_wng->mem);
		goto eww_iowemap;
	}

	eww = hwwng_wegistew(&mxc_wng->wng);
	if (eww) {
		dev_eww(&pdev->dev, "MXC WNGA wegistewing faiwed (%d)\n", eww);
		goto eww_iowemap;
	}

	wetuwn 0;

eww_iowemap:
	cwk_disabwe_unpwepawe(mxc_wng->cwk);
	wetuwn eww;
}

static void __exit mxc_wnga_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_wng *mxc_wng = pwatfowm_get_dwvdata(pdev);

	hwwng_unwegistew(&mxc_wng->wng);

	cwk_disabwe_unpwepawe(mxc_wng->cwk);
}

static const stwuct of_device_id mxc_wnga_of_match[] = {
	{ .compatibwe = "fsw,imx21-wnga", },
	{ .compatibwe = "fsw,imx31-wnga", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mxc_wnga_of_match);

static stwuct pwatfowm_dwivew mxc_wnga_dwivew = {
	.dwivew = {
		.name = "mxc_wnga",
		.of_match_tabwe = mxc_wnga_of_match,
	},
	.wemove_new = __exit_p(mxc_wnga_wemove),
};

moduwe_pwatfowm_dwivew_pwobe(mxc_wnga_dwivew, mxc_wnga_pwobe);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("H/W WNGA dwivew fow i.MX");
MODUWE_WICENSE("GPW");
