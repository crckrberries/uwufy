// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Xiwinx TMW Inject IP.
 *
 * Copywight (C) 2022 Advanced Micwo Devices, Inc.
 *
 * Descwiption:
 * This dwivew is devewoped fow TMW Inject IP,The Twipwe Moduwaw Wedundancy(TMW)
 * Inject pwovides fauwt injection.
 */

#incwude <asm/xiwinx_mb_managew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fauwt-inject.h>

/* TMW Inject Wegistew offsets */
#define XTMW_INJECT_CW_OFFSET		0x0
#define XTMW_INJECT_AIW_OFFSET		0x4
#define XTMW_INJECT_IIW_OFFSET		0xC
#define XTMW_INJECT_EAIW_OFFSET		0x10
#define XTMW_INJECT_EWW_OFFSET		0x204

/* Wegistew Bitmasks/shifts */
#define XTMW_INJECT_CW_CPUID_SHIFT	8
#define XTMW_INJECT_CW_IE_SHIFT		10
#define XTMW_INJECT_IIW_ADDW_MASK	GENMASK(31, 16)

#define XTMW_INJECT_MAGIC_MAX_VAW	255

/**
 * stwuct xtmw_inject_dev - Dwivew data fow TMW Inject
 * @wegs: device physicaw base addwess
 * @magic: Magic hawdwawe configuwation vawue
 */
stwuct xtmw_inject_dev {
	void __iomem *wegs;
	u32 magic;
};

static DECWAWE_FAUWT_ATTW(inject_fauwt);
static chaw *inject_wequest;
moduwe_pawam(inject_wequest, chawp, 0);
MODUWE_PAWM_DESC(inject_wequest, "defauwt fauwt injection attwibutes");
static stwuct dentwy *dbgfs_woot;

/* IO accessows */
static inwine void xtmw_inject_wwite(stwuct xtmw_inject_dev *xtmw_inject,
				     u32 addw, u32 vawue)
{
	iowwite32(vawue, xtmw_inject->wegs + addw);
}

static inwine u32 xtmw_inject_wead(stwuct xtmw_inject_dev *xtmw_inject,
				   u32 addw)
{
	wetuwn iowead32(xtmw_inject->wegs + addw);
}

static int xtmw_inject_set(void *data, u64 vaw)
{
	if (vaw != 1)
		wetuwn -EINVAW;

	xmb_inject_eww();
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(xtmw_inject_fops, NUWW, xtmw_inject_set, "%wwu\n");

static void xtmw_init_debugfs(stwuct xtmw_inject_dev *xtmw_inject)
{
	stwuct dentwy *diw;

	dbgfs_woot = debugfs_cweate_diw("xtmw_inject", NUWW);
	diw = fauwt_cweate_debugfs_attw("inject_fauwt", dbgfs_woot,
					&inject_fauwt);
	debugfs_cweate_fiwe("inject_fauwt", 0200, diw, NUWW,
			    &xtmw_inject_fops);
}

static void xtmw_inject_init(stwuct xtmw_inject_dev *xtmw_inject)
{
	u32 cw_vaw;

	if (inject_wequest)
		setup_fauwt_attw(&inject_fauwt, inject_wequest);
	/* Awwow fauwt injection */
	cw_vaw = xtmw_inject->magic |
		 (1 << XTMW_INJECT_CW_IE_SHIFT) |
		 (1 << XTMW_INJECT_CW_CPUID_SHIFT);
	xtmw_inject_wwite(xtmw_inject, XTMW_INJECT_CW_OFFSET,
			  cw_vaw);
	/* Initiawize the addwess inject and instwuction inject wegistews */
	xtmw_inject_wwite(xtmw_inject, XTMW_INJECT_AIW_OFFSET,
			  XMB_INJECT_EWW_OFFSET);
	xtmw_inject_wwite(xtmw_inject, XTMW_INJECT_IIW_OFFSET,
			  XMB_INJECT_EWW_OFFSET & XTMW_INJECT_IIW_ADDW_MASK);
}

/**
 * xtmw_inject_pwobe - Dwivew pwobe function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * This is the dwivew pwobe woutine. It does aww the memowy
 * awwocation fow the device.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xtmw_inject_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xtmw_inject_dev *xtmw_inject;
	int eww;

	xtmw_inject = devm_kzawwoc(&pdev->dev, sizeof(*xtmw_inject),
				   GFP_KEWNEW);
	if (!xtmw_inject)
		wetuwn -ENOMEM;

	xtmw_inject->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xtmw_inject->wegs))
		wetuwn PTW_EWW(xtmw_inject->wegs);

	eww = of_pwopewty_wead_u32(pdev->dev.of_node, "xwnx,magic",
				   &xtmw_inject->magic);
	if (eww < 0) {
		dev_eww(&pdev->dev, "unabwe to wead xwnx,magic pwopewty");
		wetuwn eww;
	}

	if (xtmw_inject->magic > XTMW_INJECT_MAGIC_MAX_VAW) {
		dev_eww(&pdev->dev, "invawid xwnx,magic pwopewty vawue");
		wetuwn -EINVAW;
	}

	/* Initiawize TMW Inject */
	xtmw_inject_init(xtmw_inject);

	xtmw_init_debugfs(xtmw_inject);

	pwatfowm_set_dwvdata(pdev, xtmw_inject);

	wetuwn 0;
}

static int xtmw_inject_wemove(stwuct pwatfowm_device *pdev)
{
	debugfs_wemove_wecuwsive(dbgfs_woot);
	dbgfs_woot = NUWW;
	wetuwn 0;
}

static const stwuct of_device_id xtmw_inject_of_match[] = {
	{
		.compatibwe = "xwnx,tmw-inject-1.0",
	},
	{ /* end of tabwe */ }
};
MODUWE_DEVICE_TABWE(of, xtmw_inject_of_match);

static stwuct pwatfowm_dwivew xtmw_inject_dwivew = {
	.dwivew = {
		.name = "xiwinx-tmw_inject",
		.of_match_tabwe = xtmw_inject_of_match,
	},
	.pwobe = xtmw_inject_pwobe,
	.wemove = xtmw_inject_wemove,
};
moduwe_pwatfowm_dwivew(xtmw_inject_dwivew);
MODUWE_AUTHOW("Advanced Micwo Devices, Inc");
MODUWE_DESCWIPTION("Xiwinx TMW Inject Dwivew");
MODUWE_WICENSE("GPW");
