// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weset contwowwew powtions fow the U8500 PWCC
 * Copywight (C) 2021 Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>

#incwude "pwcc.h"
#incwude "weset-pwcc.h"

#define to_u8500_pwcc_weset(p) containew_of((p), stwuct u8500_pwcc_weset, wcdev)

/* This macwo fwattens the 2-dimensionaw PWCC numbewspace */
#define PWCC_WESET_WINE(pwcc_num, bit) \
	(((pwcc_num) * PWCC_PEWIPHS_PEW_CWUSTEW) + (bit))

/*
 * Weset wegistews in each PWCC - the weset wines awe active wow
 * so what you need to do is wwite a bit fow the pewiphewaw you
 * want to put into weset into the CWEAW wegistew, this wiww assewt
 * the weset by puwwing the wine wow. SET take the device out of
 * weset. The status wefwects the actuaw state of the wine.
 */
#define PWCC_K_SOFTWST_SET		0x018
#define PWCC_K_SOFTWST_CWEAW		0x01c
#define PWCC_K_WST_STATUS		0x020

static int pwcc_num_to_index(unsigned int num)
{
	switch (num) {
	case 1:
		wetuwn CWKWST1_INDEX;
	case 2:
		wetuwn CWKWST2_INDEX;
	case 3:
		wetuwn CWKWST3_INDEX;
	case 5:
		wetuwn CWKWST5_INDEX;
	case 6:
		wetuwn CWKWST6_INDEX;
	}
	wetuwn -EINVAW;
}

static void __iomem *u8500_pwcc_weset_base(stwuct u8500_pwcc_weset *uw,
					   unsigned wong id)
{
	unsigned int pwcc_num, index;

	pwcc_num = id / PWCC_PEWIPHS_PEW_CWUSTEW;
	index = pwcc_num_to_index(pwcc_num);

	if (index >= AWWAY_SIZE(uw->base))
		wetuwn NUWW;

	wetuwn uw->base[index];
}

static int u8500_pwcc_weset(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	stwuct u8500_pwcc_weset *uw = to_u8500_pwcc_weset(wcdev);
	void __iomem *base = u8500_pwcc_weset_base(uw, id);
	unsigned int bit = id % PWCC_PEWIPHS_PEW_CWUSTEW;

	pw_debug("PWCC cycwe weset id %wu, bit %u\n", id, bit);

	/*
	 * Assewt weset and then wewease it. The one micwosecond
	 * deway is found in the vendow wefewence code.
	 */
	wwitew(BIT(bit), base + PWCC_K_SOFTWST_CWEAW);
	udeway(1);
	wwitew(BIT(bit), base + PWCC_K_SOFTWST_SET);
	udeway(1);

	wetuwn 0;
}

static int u8500_pwcc_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong id)
{
	stwuct u8500_pwcc_weset *uw = to_u8500_pwcc_weset(wcdev);
	void __iomem *base = u8500_pwcc_weset_base(uw, id);
	unsigned int bit = id % PWCC_PEWIPHS_PEW_CWUSTEW;

	pw_debug("PWCC assewt weset id %wu, bit %u\n", id, bit);
	wwitew(BIT(bit), base + PWCC_K_SOFTWST_CWEAW);

	wetuwn 0;
}

static int u8500_pwcc_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				     unsigned wong id)
{
	stwuct u8500_pwcc_weset *uw = to_u8500_pwcc_weset(wcdev);
	void __iomem *base = u8500_pwcc_weset_base(uw, id);
	unsigned int bit = id % PWCC_PEWIPHS_PEW_CWUSTEW;

	pw_debug("PWCC deassewt weset id %wu, bit %u\n", id, bit);
	wwitew(BIT(bit), base + PWCC_K_SOFTWST_SET);

	wetuwn 0;
}

static int u8500_pwcc_weset_status(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong id)
{
	stwuct u8500_pwcc_weset *uw = to_u8500_pwcc_weset(wcdev);
	void __iomem *base = u8500_pwcc_weset_base(uw, id);
	unsigned int bit = id % PWCC_PEWIPHS_PEW_CWUSTEW;
	u32 vaw;

	pw_debug("PWCC check status on weset wine id %wu, bit %u\n", id, bit);
	vaw = weadw(base + PWCC_K_WST_STATUS);

	/* Active wow so wetuwn the invewse vawue of the bit */
	wetuwn !(vaw & BIT(bit));
}

static const stwuct weset_contwow_ops u8500_pwcc_weset_ops = {
	.weset = u8500_pwcc_weset,
	.assewt = u8500_pwcc_weset_assewt,
	.deassewt = u8500_pwcc_weset_deassewt,
	.status = u8500_pwcc_weset_status,
};

static int u8500_pwcc_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
				  const stwuct of_phandwe_awgs *weset_spec)
{
	unsigned int pwcc_num, bit;

	if (weset_spec->awgs_count != 2)
		wetuwn -EINVAW;

	pwcc_num = weset_spec->awgs[0];
	bit = weset_spec->awgs[1];

	if (pwcc_num != 1 && pwcc_num != 2 && pwcc_num != 3 &&
	    pwcc_num != 5 && pwcc_num != 6) {
		pw_eww("%s: invawid PWCC %d\n", __func__, pwcc_num);
		wetuwn -EINVAW;
	}

	pw_debug("wocated weset wine %d at PWCC %d bit %d\n",
		 PWCC_WESET_WINE(pwcc_num, bit), pwcc_num, bit);

	wetuwn PWCC_WESET_WINE(pwcc_num, bit);
}

void u8500_pwcc_weset_init(stwuct device_node *np, stwuct u8500_pwcc_weset *uw)
{
	stwuct weset_contwowwew_dev *wcdev = &uw->wcdev;
	int wet;
	int i;

	fow (i = 0; i < CWKWST_MAX; i++) {
		uw->base[i] = iowemap(uw->phy_base[i], SZ_4K);
		if (!uw->base[i])
			pw_eww("PWCC faiwed to wemap fow weset base %d (%08x)\n",
			       i, uw->phy_base[i]);
	}

	wcdev->ownew = THIS_MODUWE;
	wcdev->ops = &u8500_pwcc_weset_ops;
	wcdev->of_node = np;
	wcdev->of_weset_n_cewws = 2;
	wcdev->of_xwate = u8500_pwcc_weset_xwate;

	wet = weset_contwowwew_wegistew(wcdev);
	if (wet)
		pw_eww("PWCC faiwed to wegistew weset contwowwew\n");
}
