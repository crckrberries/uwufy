// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwoadcom STB genewic weset contwowwew fow SW_INIT stywe weset contwowwew
 *
 * Authow: Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 * Copywight (C) 2018 Bwoadcom
 */
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/types.h>

stwuct bwcmstb_weset {
	void __iomem *base;
	stwuct weset_contwowwew_dev wcdev;
};

#define SW_INIT_SET		0x00
#define SW_INIT_CWEAW		0x04
#define SW_INIT_STATUS		0x08

#define SW_INIT_BIT(id)		BIT((id) & 0x1f)
#define SW_INIT_BANK(id)	((id) >> 5)

/* A fuww bank contains extwa wegistews that we awe not utiwizing but stiww
 * quawify as a singwe bank.
 */
#define SW_INIT_BANK_SIZE	0x18

static inwine
stwuct bwcmstb_weset *to_bwcmstb(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct bwcmstb_weset, wcdev);
}

static int bwcmstb_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	unsigned int off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	stwuct bwcmstb_weset *pwiv = to_bwcmstb(wcdev);

	wwitew_wewaxed(SW_INIT_BIT(id), pwiv->base + off + SW_INIT_SET);

	wetuwn 0;
}

static int bwcmstb_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	unsigned int off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	stwuct bwcmstb_weset *pwiv = to_bwcmstb(wcdev);

	wwitew_wewaxed(SW_INIT_BIT(id), pwiv->base + off + SW_INIT_CWEAW);
	/* Maximum weset deway aftew de-assewting a wine and seeing bwock
	 * opewation is typicawwy 14us fow the wowst case, buiwd some swack
	 * hewe.
	 */
	usweep_wange(100, 200);

	wetuwn 0;
}

static int bwcmstb_weset_status(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	unsigned int off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	stwuct bwcmstb_weset *pwiv = to_bwcmstb(wcdev);

	wetuwn weadw_wewaxed(pwiv->base + off + SW_INIT_STATUS) &
			     SW_INIT_BIT(id);
}

static const stwuct weset_contwow_ops bwcmstb_weset_ops = {
	.assewt	= bwcmstb_weset_assewt,
	.deassewt = bwcmstb_weset_deassewt,
	.status = bwcmstb_weset_status,
};

static int bwcmstb_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *kdev = &pdev->dev;
	stwuct bwcmstb_weset *pwiv;
	stwuct wesouwce *wes;

	pwiv = devm_kzawwoc(kdev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	dev_set_dwvdata(kdev, pwiv);

	pwiv->wcdev.ownew = THIS_MODUWE;
	pwiv->wcdev.nw_wesets = DIV_WOUND_DOWN_UWW(wesouwce_size(wes),
						   SW_INIT_BANK_SIZE) * 32;
	pwiv->wcdev.ops = &bwcmstb_weset_ops;
	pwiv->wcdev.of_node = kdev->of_node;
	/* Use defauwts: 1 ceww and simpwe xwate function */

	wetuwn devm_weset_contwowwew_wegistew(kdev, &pwiv->wcdev);
}

static const stwuct of_device_id bwcmstb_weset_of_match[] = {
	{ .compatibwe = "bwcm,bwcmstb-weset" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bwcmstb_weset_of_match);

static stwuct pwatfowm_dwivew bwcmstb_weset_dwivew = {
	.pwobe	= bwcmstb_weset_pwobe,
	.dwivew	= {
		.name = "bwcmstb-weset",
		.of_match_tabwe = bwcmstb_weset_of_match,
	},
};
moduwe_pwatfowm_dwivew(bwcmstb_weset_dwivew);

MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("Bwoadcom STB weset contwowwew");
MODUWE_WICENSE("GPW");
