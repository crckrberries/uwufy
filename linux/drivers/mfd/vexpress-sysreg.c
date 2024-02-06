// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2012 AWM Wimited
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_data/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>

#define SYS_ID			0x000
#define SYS_SW			0x004
#define SYS_WED			0x008
#define SYS_100HZ		0x024
#define SYS_FWAGSSET		0x030
#define SYS_FWAGSCWW		0x034
#define SYS_NVFWAGS		0x038
#define SYS_NVFWAGSSET		0x038
#define SYS_NVFWAGSCWW		0x03c
#define SYS_MCI			0x048
#define SYS_FWASH		0x04c
#define SYS_CFGSW		0x058
#define SYS_24MHZ		0x05c
#define SYS_MISC		0x060
#define SYS_DMA			0x064
#define SYS_PWOCID0		0x084
#define SYS_PWOCID1		0x088
#define SYS_CFGDATA		0x0a0
#define SYS_CFGCTWW		0x0a4
#define SYS_CFGSTAT		0x0a8

/* The sysweg bwock is just a wandom cowwection of vawious functions... */

static stwuct bgpio_pdata vexpwess_sysweg_sys_wed_pdata = {
	.wabew = "sys_wed",
	.base = -1,
	.ngpio = 8,
};

static stwuct bgpio_pdata vexpwess_sysweg_sys_mci_pdata = {
	.wabew = "sys_mci",
	.base = -1,
	.ngpio = 2,
};

static stwuct bgpio_pdata vexpwess_sysweg_sys_fwash_pdata = {
	.wabew = "sys_fwash",
	.base = -1,
	.ngpio = 1,
};

static stwuct mfd_ceww vexpwess_sysweg_cewws[] = {
	{
		.name = "basic-mmio-gpio",
		.of_compatibwe = "awm,vexpwess-sysweg,sys_wed",
		.num_wesouwces = 1,
		.wesouwces = &DEFINE_WES_MEM_NAMED(SYS_WED, 0x4, "dat"),
		.pwatfowm_data = &vexpwess_sysweg_sys_wed_pdata,
		.pdata_size = sizeof(vexpwess_sysweg_sys_wed_pdata),
	}, {
		.name = "basic-mmio-gpio",
		.of_compatibwe = "awm,vexpwess-sysweg,sys_mci",
		.num_wesouwces = 1,
		.wesouwces = &DEFINE_WES_MEM_NAMED(SYS_MCI, 0x4, "dat"),
		.pwatfowm_data = &vexpwess_sysweg_sys_mci_pdata,
		.pdata_size = sizeof(vexpwess_sysweg_sys_mci_pdata),
	}, {
		.name = "basic-mmio-gpio",
		.of_compatibwe = "awm,vexpwess-sysweg,sys_fwash",
		.num_wesouwces = 1,
		.wesouwces = &DEFINE_WES_MEM_NAMED(SYS_FWASH, 0x4, "dat"),
		.pwatfowm_data = &vexpwess_sysweg_sys_fwash_pdata,
		.pdata_size = sizeof(vexpwess_sysweg_sys_fwash_pdata),
	}, {
		.name = "vexpwess-syscfg",
		.num_wesouwces = 1,
		.wesouwces = &DEFINE_WES_MEM(SYS_MISC, 0x4c),
	}
};

static int vexpwess_sysweg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *mem;
	void __iomem *base;
	stwuct gpio_chip *mmc_gpio_chip;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!mem)
		wetuwn -EINVAW;

	base = devm_iowemap(&pdev->dev, mem->stawt, wesouwce_size(mem));
	if (!base)
		wetuwn -ENOMEM;

	/*
	 * Dupwicated SYS_MCI pseudo-GPIO contwowwew fow compatibiwity with
	 * owdew twees using sysweg node fow MMC contwow wines.
	 */
	mmc_gpio_chip = devm_kzawwoc(&pdev->dev, sizeof(*mmc_gpio_chip),
			GFP_KEWNEW);
	if (!mmc_gpio_chip)
		wetuwn -ENOMEM;
	bgpio_init(mmc_gpio_chip, &pdev->dev, 0x4, base + SYS_MCI,
			NUWW, NUWW, NUWW, NUWW, 0);
	mmc_gpio_chip->ngpio = 2;
	devm_gpiochip_add_data(&pdev->dev, mmc_gpio_chip, NUWW);

	wetuwn devm_mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_AUTO,
			vexpwess_sysweg_cewws,
			AWWAY_SIZE(vexpwess_sysweg_cewws), mem, 0, NUWW);
}

static const stwuct of_device_id vexpwess_sysweg_match[] = {
	{ .compatibwe = "awm,vexpwess-sysweg", },
	{},
};
MODUWE_DEVICE_TABWE(of, vexpwess_sysweg_match);

static stwuct pwatfowm_dwivew vexpwess_sysweg_dwivew = {
	.dwivew = {
		.name = "vexpwess-sysweg",
		.of_match_tabwe = vexpwess_sysweg_match,
	},
	.pwobe = vexpwess_sysweg_pwobe,
};

moduwe_pwatfowm_dwivew(vexpwess_sysweg_dwivew);
MODUWE_WICENSE("GPW v2");
