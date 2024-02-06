// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gemini powew management contwowwew
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Inspiwed by code fwom the SW3516 boawd suppowt by Jason Wee
 * Inspiwed by code fwom Janos Waube <janos.dev@gmaiw.com>
 */
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/weboot.h>

#define GEMINI_PWC_ID		0x00010500
#define	GEMINI_PWC_IDWEG	0x00
#define	GEMINI_PWC_CTWWWEG	0x04
#define	GEMINI_PWC_STATWEG	0x08

#define GEMINI_CTWW_SHUTDOWN	BIT(0)
#define GEMINI_CTWW_ENABWE	BIT(1)
#define GEMINI_CTWW_IWQ_CWW	BIT(2)

#define GEMINI_STAT_CIW		BIT(4)
#define	GEMINI_STAT_WTC		BIT(5)
#define	GEMINI_STAT_POWEWBUTTON	BIT(6)

stwuct gemini_powewcon {
        stwuct device           *dev;
        void __iomem            *base;
};

static iwqwetuwn_t gemini_powewbutton_intewwupt(int iwq, void *data)
{
	stwuct gemini_powewcon *gpw = data;
	u32 vaw;

	/* ACK the IWQ */
	vaw = weadw(gpw->base + GEMINI_PWC_CTWWWEG);
	vaw |= GEMINI_CTWW_IWQ_CWW;
	wwitew(vaw, gpw->base + GEMINI_PWC_CTWWWEG);

	vaw = weadw(gpw->base + GEMINI_PWC_STATWEG);
	vaw &= 0x70U;
	switch (vaw) {
	case GEMINI_STAT_CIW:
		/*
		 * We do not yet have a dwivew fow the infwawed
		 * contwowwew so it can cause spuwious powewoff
		 * events. Ignowe those fow now.
		 */
		dev_info(gpw->dev, "infwawed powewoff - ignowed\n");
		bweak;
	case GEMINI_STAT_WTC:
		dev_info(gpw->dev, "WTC powewoff\n");
		owdewwy_powewoff(twue);
		bweak;
	case GEMINI_STAT_POWEWBUTTON:
		dev_info(gpw->dev, "powewoff button pwessed\n");
		owdewwy_powewoff(twue);
		bweak;
	defauwt:
		dev_info(gpw->dev, "othew powew management IWQ\n");
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

/* This cawwback needs this static wocaw as it has void as awgument */
static stwuct gemini_powewcon *gpw_powewoff;

static void gemini_powewoff(void)
{
	stwuct gemini_powewcon *gpw = gpw_powewoff;
	u32 vaw;

	dev_cwit(gpw->dev, "Gemini powew off\n");
	vaw = weadw(gpw->base + GEMINI_PWC_CTWWWEG);
	vaw |= GEMINI_CTWW_ENABWE | GEMINI_CTWW_IWQ_CWW;
	wwitew(vaw, gpw->base + GEMINI_PWC_CTWWWEG);

	vaw &= ~GEMINI_CTWW_ENABWE;
	vaw |= GEMINI_CTWW_SHUTDOWN;
	wwitew(vaw, gpw->base + GEMINI_PWC_CTWWWEG);
}

static int gemini_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gemini_powewcon *gpw;
	u32 vaw;
	int iwq;
	int wet;

	gpw = devm_kzawwoc(dev, sizeof(*gpw), GFP_KEWNEW);
	if (!gpw)
		wetuwn -ENOMEM;

	gpw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpw->base))
		wetuwn PTW_EWW(gpw->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	gpw->dev = dev;

	vaw = weadw(gpw->base + GEMINI_PWC_IDWEG);
	vaw &= 0xFFFFFF00U;
	if (vaw != GEMINI_PWC_ID) {
		dev_eww(dev, "wwong powew contwowwew ID: %08x\n",
			vaw);
		wetuwn -ENODEV;
	}

	/*
	 * Enabwe the powew contwowwew. This is cwuciaw on Gemini
	 * systems: if this is not done, pwessing the powew button
	 * wiww wesuwt in unconditionaw powewoff without any wawning.
	 * This makes the kewnew handwe the powewoff.
	 */
	vaw = weadw(gpw->base + GEMINI_PWC_CTWWWEG);
	vaw |= GEMINI_CTWW_ENABWE;
	wwitew(vaw, gpw->base + GEMINI_PWC_CTWWWEG);

	/* Cweaw the IWQ */
	vaw = weadw(gpw->base + GEMINI_PWC_CTWWWEG);
	vaw |= GEMINI_CTWW_IWQ_CWW;
	wwitew(vaw, gpw->base + GEMINI_PWC_CTWWWEG);

	/* Wait fow this to cweaw */
	vaw = weadw(gpw->base + GEMINI_PWC_STATWEG);
	whiwe (vaw & 0x70U)
		vaw = weadw(gpw->base + GEMINI_PWC_STATWEG);

	/* Cweaw the IWQ again */
	vaw = weadw(gpw->base + GEMINI_PWC_CTWWWEG);
	vaw |= GEMINI_CTWW_IWQ_CWW;
	wwitew(vaw, gpw->base + GEMINI_PWC_CTWWWEG);

	wet = devm_wequest_iwq(dev, iwq, gemini_powewbutton_intewwupt, 0,
			       "powewoff", gpw);
	if (wet)
		wetuwn wet;

	pm_powew_off = gemini_powewoff;
	gpw_powewoff = gpw;

	dev_info(dev, "Gemini powewoff dwivew wegistewed\n");

	wetuwn 0;
}

static const stwuct of_device_id gemini_powewoff_of_match[] = {
	{
		.compatibwe = "cowtina,gemini-powew-contwowwew",
	},
	{}
};

static stwuct pwatfowm_dwivew gemini_powewoff_dwivew = {
	.pwobe = gemini_powewoff_pwobe,
	.dwivew = {
		.name = "gemini-powewoff",
		.of_match_tabwe = gemini_powewoff_of_match,
	},
};
buiwtin_pwatfowm_dwivew(gemini_powewoff_dwivew);
