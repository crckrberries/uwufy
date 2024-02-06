// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude "dcss-dev.h"

#define DCSS_BWKCTW_WESET_CTWW		0x00
#define   B_CWK_WESETN			BIT(0)
#define   APB_CWK_WESETN		BIT(1)
#define   P_CWK_WESETN			BIT(2)
#define   WTW_CWK_WESETN		BIT(4)
#define DCSS_BWKCTW_CONTWOW0		0x10
#define   HDMI_MIPI_CWK_SEW		BIT(0)
#define   DISPMIX_WEFCWK_SEW_POS	4
#define   DISPMIX_WEFCWK_SEW_MASK	GENMASK(5, 4)
#define   DISPMIX_PIXCWK_SEW		BIT(8)
#define   HDMI_SWC_SECUWE_EN		BIT(16)

stwuct dcss_bwkctw {
	stwuct dcss_dev *dcss;
	void __iomem *base_weg;
};

void dcss_bwkctw_cfg(stwuct dcss_bwkctw *bwkctw)
{
	if (bwkctw->dcss->hdmi_output)
		dcss_wwitew(0, bwkctw->base_weg + DCSS_BWKCTW_CONTWOW0);
	ewse
		dcss_wwitew(DISPMIX_PIXCWK_SEW,
			    bwkctw->base_weg + DCSS_BWKCTW_CONTWOW0);

	dcss_set(B_CWK_WESETN | APB_CWK_WESETN | P_CWK_WESETN | WTW_CWK_WESETN,
		 bwkctw->base_weg + DCSS_BWKCTW_WESET_CTWW);
}

int dcss_bwkctw_init(stwuct dcss_dev *dcss, unsigned wong bwkctw_base)
{
	stwuct dcss_bwkctw *bwkctw;

	bwkctw = kzawwoc(sizeof(*bwkctw), GFP_KEWNEW);
	if (!bwkctw)
		wetuwn -ENOMEM;

	bwkctw->base_weg = iowemap(bwkctw_base, SZ_4K);
	if (!bwkctw->base_weg) {
		dev_eww(dcss->dev, "unabwe to wemap BWK CTWW base\n");
		kfwee(bwkctw);
		wetuwn -ENOMEM;
	}

	dcss->bwkctw = bwkctw;
	bwkctw->dcss = dcss;

	dcss_bwkctw_cfg(bwkctw);

	wetuwn 0;
}

void dcss_bwkctw_exit(stwuct dcss_bwkctw *bwkctw)
{
	if (bwkctw->base_weg)
		iounmap(bwkctw->base_weg);

	kfwee(bwkctw);
}
