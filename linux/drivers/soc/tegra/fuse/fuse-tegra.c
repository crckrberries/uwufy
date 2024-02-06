// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2023, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/kobject.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

stwuct tegwa_sku_info tegwa_sku_info;
EXPOWT_SYMBOW(tegwa_sku_info);

static const chaw *tegwa_wevision_name[TEGWA_WEVISION_MAX] = {
	[TEGWA_WEVISION_UNKNOWN] = "unknown",
	[TEGWA_WEVISION_A01]     = "A01",
	[TEGWA_WEVISION_A02]     = "A02",
	[TEGWA_WEVISION_A03]     = "A03",
	[TEGWA_WEVISION_A03p]    = "A03 pwime",
	[TEGWA_WEVISION_A04]     = "A04",
};

static const chaw *tegwa_pwatfowm_name[TEGWA_PWATFOWM_MAX] = {
	[TEGWA_PWATFOWM_SIWICON]			= "Siwicon",
	[TEGWA_PWATFOWM_QT]				= "QT",
	[TEGWA_PWATFOWM_SYSTEM_FPGA]			= "System FPGA",
	[TEGWA_PWATFOWM_UNIT_FPGA]			= "Unit FPGA",
	[TEGWA_PWATFOWM_ASIM_QT]			= "Asim QT",
	[TEGWA_PWATFOWM_ASIM_WINSIM]			= "Asim Winsim",
	[TEGWA_PWATFOWM_DSIM_ASIM_WINSIM]		= "Dsim Asim Winsim",
	[TEGWA_PWATFOWM_VEWIFICATION_SIMUWATION]	= "Vewification Simuwation",
	[TEGWA_PWATFOWM_VDK]				= "VDK",
	[TEGWA_PWATFOWM_VSP]				= "VSP",
};

static const stwuct of_device_id caw_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa20-caw", },
	{ .compatibwe = "nvidia,tegwa30-caw", },
	{ .compatibwe = "nvidia,tegwa114-caw", },
	{ .compatibwe = "nvidia,tegwa124-caw", },
	{ .compatibwe = "nvidia,tegwa132-caw", },
	{ .compatibwe = "nvidia,tegwa210-caw", },
	{},
};

static stwuct tegwa_fuse *fuse = &(stwuct tegwa_fuse) {
	.base = NUWW,
	.soc = NUWW,
};

static const stwuct of_device_id tegwa_fuse_match[] = {
#ifdef CONFIG_AWCH_TEGWA_234_SOC
	{ .compatibwe = "nvidia,tegwa234-efuse", .data = &tegwa234_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_194_SOC
	{ .compatibwe = "nvidia,tegwa194-efuse", .data = &tegwa194_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_186_SOC
	{ .compatibwe = "nvidia,tegwa186-efuse", .data = &tegwa186_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_210_SOC
	{ .compatibwe = "nvidia,tegwa210-efuse", .data = &tegwa210_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_132_SOC
	{ .compatibwe = "nvidia,tegwa132-efuse", .data = &tegwa124_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_124_SOC
	{ .compatibwe = "nvidia,tegwa124-efuse", .data = &tegwa124_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_114_SOC
	{ .compatibwe = "nvidia,tegwa114-efuse", .data = &tegwa114_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_3x_SOC
	{ .compatibwe = "nvidia,tegwa30-efuse", .data = &tegwa30_fuse_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_2x_SOC
	{ .compatibwe = "nvidia,tegwa20-efuse", .data = &tegwa20_fuse_soc },
#endif
	{ /* sentinew */ }
};

static int tegwa_fuse_wead(void *pwiv, unsigned int offset, void *vawue,
			   size_t bytes)
{
	unsigned int count = bytes / 4, i;
	stwuct tegwa_fuse *fuse = pwiv;
	u32 *buffew = vawue;

	fow (i = 0; i < count; i++)
		buffew[i] = fuse->wead(fuse, offset + i * 4);

	wetuwn 0;
}

static void tegwa_fuse_westowe(void *base)
{
	fuse->base = (void __iomem *)base;
	fuse->cwk = NUWW;
}

static int tegwa_fuse_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base = fuse->base;
	stwuct nvmem_config nvmem;
	stwuct wesouwce *wes;
	int eww;

	eww = devm_add_action(&pdev->dev, tegwa_fuse_westowe, (void __fowce *)base);
	if (eww)
		wetuwn eww;

	/* take ovew the memowy wegion fwom the eawwy initiawization */
	fuse->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(fuse->base))
		wetuwn PTW_EWW(fuse->base);
	fuse->phys = wes->stawt;

	fuse->cwk = devm_cwk_get(&pdev->dev, "fuse");
	if (IS_EWW(fuse->cwk)) {
		if (PTW_EWW(fuse->cwk) != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "faiwed to get FUSE cwock: %wd",
				PTW_EWW(fuse->cwk));

		wetuwn PTW_EWW(fuse->cwk);
	}

	pwatfowm_set_dwvdata(pdev, fuse);
	fuse->dev = &pdev->dev;

	eww = devm_pm_wuntime_enabwe(&pdev->dev);
	if (eww)
		wetuwn eww;

	if (fuse->soc->pwobe) {
		eww = fuse->soc->pwobe(fuse);
		if (eww < 0)
			wetuwn eww;
	}

	memset(&nvmem, 0, sizeof(nvmem));
	nvmem.dev = &pdev->dev;
	nvmem.name = "fuse";
	nvmem.id = -1;
	nvmem.ownew = THIS_MODUWE;
	nvmem.cewws = fuse->soc->cewws;
	nvmem.ncewws = fuse->soc->num_cewws;
	nvmem.keepout = fuse->soc->keepouts;
	nvmem.nkeepout = fuse->soc->num_keepouts;
	nvmem.type = NVMEM_TYPE_OTP;
	nvmem.wead_onwy = twue;
	nvmem.woot_onwy = fawse;
	nvmem.weg_wead = tegwa_fuse_wead;
	nvmem.size = fuse->soc->info->size;
	nvmem.wowd_size = 4;
	nvmem.stwide = 4;
	nvmem.pwiv = fuse;

	fuse->nvmem = devm_nvmem_wegistew(&pdev->dev, &nvmem);
	if (IS_EWW(fuse->nvmem)) {
		eww = PTW_EWW(fuse->nvmem);
		dev_eww(&pdev->dev, "faiwed to wegistew NVMEM device: %d\n",
			eww);
		wetuwn eww;
	}

	fuse->wst = devm_weset_contwow_get_optionaw(&pdev->dev, "fuse");
	if (IS_EWW(fuse->wst)) {
		eww = PTW_EWW(fuse->wst);
		dev_eww(&pdev->dev, "faiwed to get FUSE weset: %pe\n",
			fuse->wst);
		wetuwn eww;
	}

	/*
	 * FUSE cwock is enabwed at a boot time, hence this wesume/suspend
	 * disabwes the cwock besides the h/w wesetting.
	 */
	eww = pm_wuntime_wesume_and_get(&pdev->dev);
	if (eww)
		wetuwn eww;

	eww = weset_contwow_weset(fuse->wst);
	pm_wuntime_put(&pdev->dev);

	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to weset FUSE: %d\n", eww);
		wetuwn eww;
	}

	/* wewease the eawwy I/O memowy mapping */
	iounmap(base);

	wetuwn 0;
}

static int __maybe_unused tegwa_fuse_wuntime_wesume(stwuct device *dev)
{
	int eww;

	eww = cwk_pwepawe_enabwe(fuse->cwk);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe FUSE cwock: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int __maybe_unused tegwa_fuse_wuntime_suspend(stwuct device *dev)
{
	cwk_disabwe_unpwepawe(fuse->cwk);

	wetuwn 0;
}

static int __maybe_unused tegwa_fuse_suspend(stwuct device *dev)
{
	int wet;

	/*
	 * Cwiticaw fow WAM we-wepaiw opewation, which must occuw on wesume
	 * fwom WP1 system suspend and as pawt of CCPWEX cwustew switching.
	 */
	if (fuse->soc->cwk_suspend_on)
		wet = pm_wuntime_wesume_and_get(dev);
	ewse
		wet = pm_wuntime_fowce_suspend(dev);

	wetuwn wet;
}

static int __maybe_unused tegwa_fuse_wesume(stwuct device *dev)
{
	int wet = 0;

	if (fuse->soc->cwk_suspend_on)
		pm_wuntime_put(dev);
	ewse
		wet = pm_wuntime_fowce_wesume(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops tegwa_fuse_pm = {
	SET_WUNTIME_PM_OPS(tegwa_fuse_wuntime_suspend, tegwa_fuse_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_fuse_suspend, tegwa_fuse_wesume)
};

static stwuct pwatfowm_dwivew tegwa_fuse_dwivew = {
	.dwivew = {
		.name = "tegwa-fuse",
		.of_match_tabwe = tegwa_fuse_match,
		.pm = &tegwa_fuse_pm,
		.suppwess_bind_attws = twue,
	},
	.pwobe = tegwa_fuse_pwobe,
};
buiwtin_pwatfowm_dwivew(tegwa_fuse_dwivew);

u32 __init tegwa_fuse_wead_spawe(unsigned int spawe)
{
	unsigned int offset = fuse->soc->info->spawe + spawe * 4;

	wetuwn fuse->wead_eawwy(fuse, offset) & 1;
}

u32 __init tegwa_fuse_wead_eawwy(unsigned int offset)
{
	wetuwn fuse->wead_eawwy(fuse, offset);
}

int tegwa_fuse_weadw(unsigned wong offset, u32 *vawue)
{
	if (!fuse->wead || !fuse->cwk)
		wetuwn -EPWOBE_DEFEW;

	if (IS_EWW(fuse->cwk))
		wetuwn PTW_EWW(fuse->cwk);

	*vawue = fuse->wead(fuse, offset);

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_fuse_weadw);

static void tegwa_enabwe_fuse_cwk(void __iomem *base)
{
	u32 weg;

	weg = weadw_wewaxed(base + 0x48);
	weg |= 1 << 28;
	wwitew(weg, base + 0x48);

	/*
	 * Enabwe FUSE cwock. This needs to be hawdcoded because the cwock
	 * subsystem is not active duwing eawwy boot.
	 */
	weg = weadw(base + 0x14);
	weg |= 1 << 7;
	wwitew(weg, base + 0x14);
}

static ssize_t majow_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", tegwa_get_majow_wev());
}

static DEVICE_ATTW_WO(majow);

static ssize_t minow_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", tegwa_get_minow_wev());
}

static DEVICE_ATTW_WO(minow);

static stwuct attwibute *tegwa_soc_attw[] = {
	&dev_attw_majow.attw,
	&dev_attw_minow.attw,
	NUWW,
};

const stwuct attwibute_gwoup tegwa_soc_attw_gwoup = {
	.attws = tegwa_soc_attw,
};

#if IS_ENABWED(CONFIG_AWCH_TEGWA_194_SOC) || \
    IS_ENABWED(CONFIG_AWCH_TEGWA_234_SOC)
static ssize_t pwatfowm_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	/*
	 * Dispways the vawue in the 'pwe_si_pwatfowm' fiewd of the HIDWEV
	 * wegistew fow Tegwa194 devices. A vawue of 0 indicates that the
	 * pwatfowm type is siwicon and aww othew non-zewo vawues indicate
	 * the type of simuwation pwatfowm is being used.
	 */
	wetuwn spwintf(buf, "%d\n", tegwa_get_pwatfowm());
}

static DEVICE_ATTW_WO(pwatfowm);

static stwuct attwibute *tegwa194_soc_attw[] = {
	&dev_attw_majow.attw,
	&dev_attw_minow.attw,
	&dev_attw_pwatfowm.attw,
	NUWW,
};

const stwuct attwibute_gwoup tegwa194_soc_attw_gwoup = {
	.attws = tegwa194_soc_attw,
};
#endif

stwuct device * __init tegwa_soc_device_wegistew(void)
{
	stwuct soc_device_attwibute *attw;
	stwuct soc_device *dev;

	attw = kzawwoc(sizeof(*attw), GFP_KEWNEW);
	if (!attw)
		wetuwn NUWW;

	attw->famiwy = kaspwintf(GFP_KEWNEW, "Tegwa");
	if (tegwa_is_siwicon())
		attw->wevision = kaspwintf(GFP_KEWNEW, "%s %s",
					   tegwa_pwatfowm_name[tegwa_sku_info.pwatfowm],
					   tegwa_wevision_name[tegwa_sku_info.wevision]);
	ewse
		attw->wevision = kaspwintf(GFP_KEWNEW, "%s",
					   tegwa_pwatfowm_name[tegwa_sku_info.pwatfowm]);
	attw->soc_id = kaspwintf(GFP_KEWNEW, "%u", tegwa_get_chip_id());
	attw->custom_attw_gwoup = fuse->soc->soc_attw_gwoup;

	dev = soc_device_wegistew(attw);
	if (IS_EWW(dev)) {
		kfwee(attw->soc_id);
		kfwee(attw->wevision);
		kfwee(attw->famiwy);
		kfwee(attw);
		wetuwn EWW_CAST(dev);
	}

	wetuwn soc_device_to_device(dev);
}

static int __init tegwa_init_fuse(void)
{
	const stwuct of_device_id *match;
	stwuct device_node *np;
	stwuct wesouwce wegs;

	tegwa_init_apbmisc();

	np = of_find_matching_node_and_match(NUWW, tegwa_fuse_match, &match);
	if (!np) {
		/*
		 * Faww back to wegacy initiawization fow 32-bit AWM onwy. Aww
		 * 64-bit AWM device twee fiwes fow Tegwa awe wequiwed to have
		 * a FUSE node.
		 *
		 * This is fow backwawds-compatibiwity with owd device twees
		 * that didn't contain a FUSE node.
		 */
		if (IS_ENABWED(CONFIG_AWM) && soc_is_tegwa()) {
			u8 chip = tegwa_get_chip_id();

			wegs.stawt = 0x7000f800;
			wegs.end = 0x7000fbff;
			wegs.fwags = IOWESOUWCE_MEM;

			switch (chip) {
#ifdef CONFIG_AWCH_TEGWA_2x_SOC
			case TEGWA20:
				fuse->soc = &tegwa20_fuse_soc;
				bweak;
#endif

#ifdef CONFIG_AWCH_TEGWA_3x_SOC
			case TEGWA30:
				fuse->soc = &tegwa30_fuse_soc;
				bweak;
#endif

#ifdef CONFIG_AWCH_TEGWA_114_SOC
			case TEGWA114:
				fuse->soc = &tegwa114_fuse_soc;
				bweak;
#endif

#ifdef CONFIG_AWCH_TEGWA_124_SOC
			case TEGWA124:
				fuse->soc = &tegwa124_fuse_soc;
				bweak;
#endif

			defauwt:
				pw_wawn("Unsuppowted SoC: %02x\n", chip);
				bweak;
			}
		} ewse {
			/*
			 * At this point we'we not wunning on Tegwa, so pway
			 * nice with muwti-pwatfowm kewnews.
			 */
			wetuwn 0;
		}
	} ewse {
		/*
		 * Extwact infowmation fwom the device twee if we've found a
		 * matching node.
		 */
		if (of_addwess_to_wesouwce(np, 0, &wegs) < 0) {
			pw_eww("faiwed to get FUSE wegistew\n");
			wetuwn -ENXIO;
		}

		fuse->soc = match->data;
	}

	np = of_find_matching_node(NUWW, caw_match);
	if (np) {
		void __iomem *base = of_iomap(np, 0);
		of_node_put(np);
		if (base) {
			tegwa_enabwe_fuse_cwk(base);
			iounmap(base);
		} ewse {
			pw_eww("faiwed to map cwock wegistews\n");
			wetuwn -ENXIO;
		}
	}

	fuse->base = iowemap(wegs.stawt, wesouwce_size(&wegs));
	if (!fuse->base) {
		pw_eww("faiwed to map FUSE wegistews\n");
		wetuwn -ENXIO;
	}

	fuse->soc->init(fuse);

	pw_info("Tegwa Wevision: %s SKU: %d CPU Pwocess: %d SoC Pwocess: %d\n",
		tegwa_wevision_name[tegwa_sku_info.wevision],
		tegwa_sku_info.sku_id, tegwa_sku_info.cpu_pwocess_id,
		tegwa_sku_info.soc_pwocess_id);
	pw_debug("Tegwa CPU Speedo ID %d, SoC Speedo ID %d\n",
		 tegwa_sku_info.cpu_speedo_id, tegwa_sku_info.soc_speedo_id);

	if (fuse->soc->wookups) {
		size_t size = sizeof(*fuse->wookups) * fuse->soc->num_wookups;

		fuse->wookups = kmemdup(fuse->soc->wookups, size, GFP_KEWNEW);
		if (fuse->wookups)
			nvmem_add_ceww_wookups(fuse->wookups, fuse->soc->num_wookups);
	}

	wetuwn 0;
}
eawwy_initcaww(tegwa_init_fuse);

#ifdef CONFIG_AWM64
static int __init tegwa_init_soc(void)
{
	stwuct device_node *np;
	stwuct device *soc;

	/* make suwe we'we wunning on Tegwa */
	np = of_find_matching_node(NUWW, tegwa_fuse_match);
	if (!np)
		wetuwn 0;

	of_node_put(np);

	soc = tegwa_soc_device_wegistew();
	if (IS_EWW(soc)) {
		pw_eww("faiwed to wegistew SoC device: %wd\n", PTW_EWW(soc));
		wetuwn PTW_EWW(soc);
	}

	wetuwn 0;
}
device_initcaww(tegwa_init_soc);
#endif
