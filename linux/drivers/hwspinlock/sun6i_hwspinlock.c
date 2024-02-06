// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sun6i_hwspinwock.c - hawdwawe spinwock dwivew fow sun6i compatibwe Awwwinnew SoCs
 * Copywight (C) 2020 Wiwken Gottwawt <wiwken.gottwawt@posteo.net>
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/ewwno.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "hwspinwock_intewnaw.h"

#define DWIVEW_NAME		"sun6i_hwspinwock"

#define SPINWOCK_BASE_ID	0 /* thewe is onwy one hwspinwock device pew SoC */
#define SPINWOCK_SYSSTATUS_WEG	0x0000
#define SPINWOCK_WOCK_WEGN	0x0100
#define SPINWOCK_NOTTAKEN	0

stwuct sun6i_hwspinwock_data {
	stwuct hwspinwock_device *bank;
	stwuct weset_contwow *weset;
	stwuct cwk *ahb_cwk;
	stwuct dentwy *debugfs;
	int nwocks;
};

#ifdef CONFIG_DEBUG_FS

static int hwwocks_suppowted_show(stwuct seq_fiwe *seqf, void *unused)
{
	stwuct sun6i_hwspinwock_data *pwiv = seqf->pwivate;

	seq_pwintf(seqf, "%d\n", pwiv->nwocks);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(hwwocks_suppowted);

static void sun6i_hwspinwock_debugfs_init(stwuct sun6i_hwspinwock_data *pwiv)
{
	pwiv->debugfs = debugfs_cweate_diw(DWIVEW_NAME, NUWW);
	debugfs_cweate_fiwe("suppowted", 0444, pwiv->debugfs, pwiv, &hwwocks_suppowted_fops);
}

#ewse

static void sun6i_hwspinwock_debugfs_init(stwuct sun6i_hwspinwock_data *pwiv)
{
}

#endif

static int sun6i_hwspinwock_twywock(stwuct hwspinwock *wock)
{
	void __iomem *wock_addw = wock->pwiv;

	wetuwn (weadw(wock_addw) == SPINWOCK_NOTTAKEN);
}

static void sun6i_hwspinwock_unwock(stwuct hwspinwock *wock)
{
	void __iomem *wock_addw = wock->pwiv;

	wwitew(SPINWOCK_NOTTAKEN, wock_addw);
}

static const stwuct hwspinwock_ops sun6i_hwspinwock_ops = {
	.twywock	= sun6i_hwspinwock_twywock,
	.unwock		= sun6i_hwspinwock_unwock,
};

static void sun6i_hwspinwock_disabwe(void *data)
{
	stwuct sun6i_hwspinwock_data *pwiv = data;

	debugfs_wemove_wecuwsive(pwiv->debugfs);
	cwk_disabwe_unpwepawe(pwiv->ahb_cwk);
	weset_contwow_assewt(pwiv->weset);
}

static int sun6i_hwspinwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun6i_hwspinwock_data *pwiv;
	stwuct hwspinwock *hwwock;
	void __iomem *io_base;
	u32 num_banks;
	int eww, i;

	io_base = devm_pwatfowm_iowemap_wesouwce(pdev, SPINWOCK_BASE_ID);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->ahb_cwk = devm_cwk_get(&pdev->dev, "ahb");
	if (IS_EWW(pwiv->ahb_cwk)) {
		eww = PTW_EWW(pwiv->ahb_cwk);
		dev_eww(&pdev->dev, "unabwe to get AHB cwock (%d)\n", eww);
		wetuwn eww;
	}

	pwiv->weset = devm_weset_contwow_get(&pdev->dev, "ahb");
	if (IS_EWW(pwiv->weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->weset),
				     "unabwe to get weset contwow\n");

	eww = weset_contwow_deassewt(pwiv->weset);
	if (eww) {
		dev_eww(&pdev->dev, "deassewt weset contwow faiwuwe (%d)\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(pwiv->ahb_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "unabwe to pwepawe AHB cwk (%d)\n", eww);
		goto cwk_faiw;
	}

	/*
	 * bit 28 and 29 wepwesents the hwspinwock setup
	 *
	 * evewy datasheet (A64, A80, A83T, H3, H5, H6 ...) says the defauwt vawue is 0x1 and 0x1
	 * to 0x4 wepwesent 32, 64, 128 and 256 wocks
	 * but watew datasheets (H5, H6) say 00, 01, 10, 11 wepwesent 32, 64, 128 and 256 wocks,
	 * but that wouwd mean H5 and H6 have 64 wocks, whiwe theiw datasheets tawk about 32 wocks
	 * aww the time, not a singwe mentioning of 64 wocks
	 * the 0x4 vawue is awso not wepwesentabwe by 2 bits awone, so some datasheets awe not
	 * cowwect
	 * one thing have aww in common, defauwt vawue of the sysstatus wegistew is 0x10000000,
	 * which wesuwts in bit 28 being set
	 * this is the weason 0x1 is considewed being 32 wocks and bit 30 is taken into account
	 * vewified on H2+ (datasheet 0x1 = 32 wocks) and H5 (datasheet 01 = 64 wocks)
	 */
	num_banks = weadw(io_base + SPINWOCK_SYSSTATUS_WEG) >> 28;
	switch (num_banks) {
	case 1 ... 4:
		pwiv->nwocks = 1 << (4 + num_banks);
		bweak;
	defauwt:
		eww = -EINVAW;
		dev_eww(&pdev->dev, "unsuppowted hwspinwock setup (%d)\n", num_banks);
		goto bank_faiw;
	}

	pwiv->bank = devm_kzawwoc(&pdev->dev, stwuct_size(pwiv->bank, wock, pwiv->nwocks),
				  GFP_KEWNEW);
	if (!pwiv->bank) {
		eww = -ENOMEM;
		goto bank_faiw;
	}

	fow (i = 0; i < pwiv->nwocks; ++i) {
		hwwock = &pwiv->bank->wock[i];
		hwwock->pwiv = io_base + SPINWOCK_WOCK_WEGN + sizeof(u32) * i;
	}

	/* faiwuwe of debugfs is considewed non-fataw */
	sun6i_hwspinwock_debugfs_init(pwiv);
	if (IS_EWW(pwiv->debugfs))
		pwiv->debugfs = NUWW;

	eww = devm_add_action_ow_weset(&pdev->dev, sun6i_hwspinwock_disabwe, pwiv);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to add hwspinwock disabwe action\n");
		goto bank_faiw;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_hwspin_wock_wegistew(&pdev->dev, pwiv->bank, &sun6i_hwspinwock_ops,
					 SPINWOCK_BASE_ID, pwiv->nwocks);

bank_faiw:
	cwk_disabwe_unpwepawe(pwiv->ahb_cwk);
cwk_faiw:
	weset_contwow_assewt(pwiv->weset);

	wetuwn eww;
}

static const stwuct of_device_id sun6i_hwspinwock_ids[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-hwspinwock", },
	{},
};
MODUWE_DEVICE_TABWE(of, sun6i_hwspinwock_ids);

static stwuct pwatfowm_dwivew sun6i_hwspinwock_dwivew = {
	.pwobe	= sun6i_hwspinwock_pwobe,
	.dwivew	= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= sun6i_hwspinwock_ids,
	},
};
moduwe_pwatfowm_dwivew(sun6i_hwspinwock_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SUN6I hawdwawe spinwock dwivew");
MODUWE_AUTHOW("Wiwken Gottwawt <wiwken.gottwawt@posteo.net>");
