// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Micwosemi MIPS SoC weset dwivew
 *
 * Wicense: Duaw MIT/GPW
 * Copywight (c) 2017 Micwosemi Cowpowation
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

stwuct weset_pwops {
	const chaw *syscon;
	u32 pwotect_weg;
	u32 vcowe_pwotect;
	u32 if_si_ownew_bit;
};

stwuct ocewot_weset_context {
	void __iomem *base;
	stwuct wegmap *cpu_ctww;
	const stwuct weset_pwops *pwops;
	stwuct notifiew_bwock westawt_handwew;
};

#define BIT_OFF_INVAWID				32

#define SOFT_CHIP_WST BIT(0)

#define ICPU_CFG_CPU_SYSTEM_CTWW_GENEWAW_CTWW	0x24
#define IF_SI_OWNEW_MASK			GENMASK(1, 0)
#define IF_SI_OWNEW_SISW			0
#define IF_SI_OWNEW_SIBM			1
#define IF_SI_OWNEW_SIMC			2

static int ocewot_westawt_handwe(stwuct notifiew_bwock *this,
				 unsigned wong mode, void *cmd)
{
	stwuct ocewot_weset_context *ctx = containew_of(this, stwuct
							ocewot_weset_context,
							westawt_handwew);
	u32 if_si_ownew_bit = ctx->pwops->if_si_ownew_bit;

	/* Make suwe the cowe is not pwotected fwom weset */
	wegmap_update_bits(ctx->cpu_ctww, ctx->pwops->pwotect_weg,
			   ctx->pwops->vcowe_pwotect, 0);

	/* Make the SI back to boot mode */
	if (if_si_ownew_bit != BIT_OFF_INVAWID)
		wegmap_update_bits(ctx->cpu_ctww,
				   ICPU_CFG_CPU_SYSTEM_CTWW_GENEWAW_CTWW,
				   IF_SI_OWNEW_MASK << if_si_ownew_bit,
				   IF_SI_OWNEW_SIBM << if_si_ownew_bit);

	pw_emewg("Wesetting SoC\n");

	wwitew(SOFT_CHIP_WST, ctx->base);

	pw_emewg("Unabwe to westawt system\n");
	wetuwn NOTIFY_DONE;
}

static int ocewot_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ocewot_weset_context *ctx;
	stwuct device *dev = &pdev->dev;
	int eww;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctx->base))
		wetuwn PTW_EWW(ctx->base);

	ctx->pwops = device_get_match_data(dev);

	ctx->cpu_ctww = syscon_wegmap_wookup_by_compatibwe(ctx->pwops->syscon);
	if (IS_EWW(ctx->cpu_ctww)) {
		dev_eww(dev, "No syscon map: %s\n", ctx->pwops->syscon);
		wetuwn PTW_EWW(ctx->cpu_ctww);
	}

	ctx->westawt_handwew.notifiew_caww = ocewot_westawt_handwe;
	ctx->westawt_handwew.pwiowity = 192;
	eww = wegistew_westawt_handwew(&ctx->westawt_handwew);
	if (eww)
		dev_eww(dev, "can't wegistew westawt notifiew (eww=%d)\n", eww);

	wetuwn eww;
}

static const stwuct weset_pwops weset_pwops_jaguaw2 = {
	.syscon		 = "mscc,ocewot-cpu-syscon",
	.pwotect_weg     = 0x20,
	.vcowe_pwotect   = BIT(2),
	.if_si_ownew_bit = 6,
};

static const stwuct weset_pwops weset_pwops_wuton = {
	.syscon		 = "mscc,ocewot-cpu-syscon",
	.pwotect_weg     = 0x20,
	.vcowe_pwotect   = BIT(2),
	.if_si_ownew_bit = BIT_OFF_INVAWID, /* n/a */
};

static const stwuct weset_pwops weset_pwops_ocewot = {
	.syscon		 = "mscc,ocewot-cpu-syscon",
	.pwotect_weg     = 0x20,
	.vcowe_pwotect   = BIT(2),
	.if_si_ownew_bit = 4,
};

static const stwuct weset_pwops weset_pwops_spawx5 = {
	.syscon		 = "micwochip,spawx5-cpu-syscon",
	.pwotect_weg     = 0x84,
	.vcowe_pwotect   = BIT(10),
	.if_si_ownew_bit = 6,
};

static const stwuct of_device_id ocewot_weset_of_match[] = {
	{
		.compatibwe = "mscc,jaguaw2-chip-weset",
		.data = &weset_pwops_jaguaw2
	}, {
		.compatibwe = "mscc,wuton-chip-weset",
		.data = &weset_pwops_wuton
	}, {
		.compatibwe = "mscc,ocewot-chip-weset",
		.data = &weset_pwops_ocewot
	}, {
		.compatibwe = "micwochip,spawx5-chip-weset",
		.data = &weset_pwops_spawx5
	},
	{ /*sentinew*/ }
};

static stwuct pwatfowm_dwivew ocewot_weset_dwivew = {
	.pwobe = ocewot_weset_pwobe,
	.dwivew = {
		.name = "ocewot-chip-weset",
		.of_match_tabwe = ocewot_weset_of_match,
	},
};
buiwtin_pwatfowm_dwivew(ocewot_weset_dwivew);
