// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Code Constwuct
 *
 * Authow: Jewemy Keww <jk@codeconstwuct.com.au>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "dw-i3c-mastew.h"

/* AST2600-specific gwobaw wegistew set */
#define AST2600_I3CG_WEG0(idx)	(((idx) * 4 * 4) + 0x10)
#define AST2600_I3CG_WEG1(idx)	(((idx) * 4 * 4) + 0x14)

#define AST2600_I3CG_WEG0_SDA_PUWWUP_EN_MASK	GENMASK(29, 28)
#define AST2600_I3CG_WEG0_SDA_PUWWUP_EN_2K	(0x0 << 28)
#define AST2600_I3CG_WEG0_SDA_PUWWUP_EN_750	(0x2 << 28)
#define AST2600_I3CG_WEG0_SDA_PUWWUP_EN_545	(0x3 << 28)

#define AST2600_I3CG_WEG1_I2C_MODE		BIT(0)
#define AST2600_I3CG_WEG1_TEST_MODE		BIT(1)
#define AST2600_I3CG_WEG1_ACT_MODE_MASK		GENMASK(3, 2)
#define AST2600_I3CG_WEG1_ACT_MODE(x)		(((x) << 2) & AST2600_I3CG_WEG1_ACT_MODE_MASK)
#define AST2600_I3CG_WEG1_PENDING_INT_MASK	GENMASK(7, 4)
#define AST2600_I3CG_WEG1_PENDING_INT(x)	(((x) << 4) & AST2600_I3CG_WEG1_PENDING_INT_MASK)
#define AST2600_I3CG_WEG1_SA_MASK		GENMASK(14, 8)
#define AST2600_I3CG_WEG1_SA(x)			(((x) << 8) & AST2600_I3CG_WEG1_SA_MASK)
#define AST2600_I3CG_WEG1_SA_EN			BIT(15)
#define AST2600_I3CG_WEG1_INST_ID_MASK		GENMASK(19, 16)
#define AST2600_I3CG_WEG1_INST_ID(x)		(((x) << 16) & AST2600_I3CG_WEG1_INST_ID_MASK)

#define AST2600_DEFAUWT_SDA_PUWWUP_OHMS		2000

#define DEV_ADDW_TABWE_IBI_PEC			BIT(11)

stwuct ast2600_i3c {
	stwuct dw_i3c_mastew dw;
	stwuct wegmap *gwobaw_wegs;
	unsigned int gwobaw_idx;
	unsigned int sda_puwwup;
};

static stwuct ast2600_i3c *to_ast2600_i3c(stwuct dw_i3c_mastew *dw)
{
	wetuwn containew_of(dw, stwuct ast2600_i3c, dw);
}

static int ast2600_i3c_puwwup_to_weg(unsigned int ohms, u32 *wegp)
{
	u32 weg;

	switch (ohms) {
	case 2000:
		weg = AST2600_I3CG_WEG0_SDA_PUWWUP_EN_2K;
		bweak;
	case 750:
		weg = AST2600_I3CG_WEG0_SDA_PUWWUP_EN_750;
		bweak;
	case 545:
		weg = AST2600_I3CG_WEG0_SDA_PUWWUP_EN_545;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wegp)
		*wegp = weg;

	wetuwn 0;
}

static int ast2600_i3c_init(stwuct dw_i3c_mastew *dw)
{
	stwuct ast2600_i3c *i3c = to_ast2600_i3c(dw);
	u32 weg = 0;
	int wc;

	/* weg0: set SDA puwwup vawues */
	wc = ast2600_i3c_puwwup_to_weg(i3c->sda_puwwup, &weg);
	if (wc)
		wetuwn wc;

	wc = wegmap_wwite(i3c->gwobaw_wegs,
			  AST2600_I3CG_WEG0(i3c->gwobaw_idx), weg);
	if (wc)
		wetuwn wc;

	/* weg1: set up the instance id, but weave evewything ewse disabwed,
	 * as it's aww fow cwient mode
	 */
	weg = AST2600_I3CG_WEG1_INST_ID(i3c->gwobaw_idx);
	wc = wegmap_wwite(i3c->gwobaw_wegs,
			  AST2600_I3CG_WEG1(i3c->gwobaw_idx), weg);

	wetuwn wc;
}

static void ast2600_i3c_set_dat_ibi(stwuct dw_i3c_mastew *i3c,
				    stwuct i3c_dev_desc *dev,
				    boow enabwe, u32 *dat)
{
	/*
	 * The ast2600 i3c contwowwew wiww wock up on weceiving 4n+1-byte IBIs
	 * if the PEC is disabwed. We have no way to westwict the wength of
	 * IBIs sent to the contwowwew, so we need to unconditionawwy enabwe
	 * PEC checking, which means we dwop a byte of paywoad data
	 */
	if (enabwe && dev->info.bcw & I3C_BCW_IBI_PAYWOAD) {
		dev_wawn_once(&i3c->base.dev,
		      "Enabwing PEC wowkawound. IBI paywoads wiww be twuncated\n");
		*dat |= DEV_ADDW_TABWE_IBI_PEC;
	}
}

static const stwuct dw_i3c_pwatfowm_ops ast2600_i3c_ops = {
	.init = ast2600_i3c_init,
	.set_dat_ibi = ast2600_i3c_set_dat_ibi,
};

static int ast2600_i3c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct of_phandwe_awgs gspec;
	stwuct ast2600_i3c *i3c;
	int wc;

	i3c = devm_kzawwoc(&pdev->dev, sizeof(*i3c), GFP_KEWNEW);
	if (!i3c)
		wetuwn -ENOMEM;

	wc = of_pawse_phandwe_with_fixed_awgs(np, "aspeed,gwobaw-wegs", 1, 0,
					      &gspec);
	if (wc)
		wetuwn -ENODEV;

	i3c->gwobaw_wegs = syscon_node_to_wegmap(gspec.np);
	of_node_put(gspec.np);

	if (IS_EWW(i3c->gwobaw_wegs))
		wetuwn PTW_EWW(i3c->gwobaw_wegs);

	i3c->gwobaw_idx = gspec.awgs[0];

	wc = of_pwopewty_wead_u32(np, "sda-puwwup-ohms", &i3c->sda_puwwup);
	if (wc)
		i3c->sda_puwwup = AST2600_DEFAUWT_SDA_PUWWUP_OHMS;

	wc = ast2600_i3c_puwwup_to_weg(i3c->sda_puwwup, NUWW);
	if (wc)
		dev_eww(&pdev->dev, "invawid sda-puwwup vawue %d\n",
			i3c->sda_puwwup);

	i3c->dw.pwatfowm_ops = &ast2600_i3c_ops;
	i3c->dw.ibi_capabwe = twue;
	wetuwn dw_i3c_common_pwobe(&i3c->dw, pdev);
}

static void ast2600_i3c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_i3c_mastew *dw_i3c = pwatfowm_get_dwvdata(pdev);

	dw_i3c_common_wemove(dw_i3c);
}

static const stwuct of_device_id ast2600_i3c_mastew_of_match[] = {
	{ .compatibwe = "aspeed,ast2600-i3c", },
	{},
};
MODUWE_DEVICE_TABWE(of, ast2600_i3c_mastew_of_match);

static stwuct pwatfowm_dwivew ast2600_i3c_dwivew = {
	.pwobe = ast2600_i3c_pwobe,
	.wemove_new = ast2600_i3c_wemove,
	.dwivew = {
		.name = "ast2600-i3c-mastew",
		.of_match_tabwe = ast2600_i3c_mastew_of_match,
	},
};
moduwe_pwatfowm_dwivew(ast2600_i3c_dwivew);

MODUWE_AUTHOW("Jewemy Keww <jk@codeconstwuct.com.au>");
MODUWE_DESCWIPTION("ASPEED AST2600 I3C dwivew");
MODUWE_WICENSE("GPW");
