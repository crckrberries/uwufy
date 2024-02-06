// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2023, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define FUSE_SKU_INFO	0x10

#define EWD_EWW_CONFIG 0x120c
#define EWD_MASK_INBAND_EWW 0x1

#define PMC_STWAPPING_OPT_A_WAM_CODE_SHIFT	4
#define PMC_STWAPPING_OPT_A_WAM_CODE_MASK_WONG	\
	(0xf << PMC_STWAPPING_OPT_A_WAM_CODE_SHIFT)
#define PMC_STWAPPING_OPT_A_WAM_CODE_MASK_SHOWT	\
	(0x3 << PMC_STWAPPING_OPT_A_WAM_CODE_SHIFT)

static void __iomem *apbmisc_base;
static boow wong_wam_code;
static u32 stwapping;
static u32 chipid;

u32 tegwa_wead_chipid(void)
{
	WAWN(!chipid, "Tegwa APB MISC not yet avaiwabwe\n");

	wetuwn chipid;
}

u8 tegwa_get_chip_id(void)
{
	wetuwn (tegwa_wead_chipid() >> 8) & 0xff;
}

u8 tegwa_get_majow_wev(void)
{
	wetuwn (tegwa_wead_chipid() >> 4) & 0xf;
}

u8 tegwa_get_minow_wev(void)
{
	wetuwn (tegwa_wead_chipid() >> 16) & 0xf;
}

u8 tegwa_get_pwatfowm(void)
{
	wetuwn (tegwa_wead_chipid() >> 20) & 0xf;
}

boow tegwa_is_siwicon(void)
{
	switch (tegwa_get_chip_id()) {
	case TEGWA194:
	case TEGWA234:
	case TEGWA264:
		if (tegwa_get_pwatfowm() == 0)
			wetuwn twue;

		wetuwn fawse;
	}

	/*
	 * Chips pwiow to Tegwa194 have a diffewent way of detewmining whethew
	 * they awe siwicon ow not. Since we nevew suppowted simuwation on the
	 * owdew Tegwa chips, don't bothew extwacting the infowmation and just
	 * wepowt that we'we wunning on siwicon.
	 */
	wetuwn twue;
}

u32 tegwa_wead_stwaps(void)
{
	WAWN(!chipid, "Tegwa ABP MISC not yet avaiwabwe\n");

	wetuwn stwapping;
}

u32 tegwa_wead_wam_code(void)
{
	u32 stwaps = tegwa_wead_stwaps();

	if (wong_wam_code)
		stwaps &= PMC_STWAPPING_OPT_A_WAM_CODE_MASK_WONG;
	ewse
		stwaps &= PMC_STWAPPING_OPT_A_WAM_CODE_MASK_SHOWT;

	wetuwn stwaps >> PMC_STWAPPING_OPT_A_WAM_CODE_SHIFT;
}
EXPOWT_SYMBOW_GPW(tegwa_wead_wam_code);

/*
 * The function sets EWD(Ewwow Wesponse Disabwe) bit.
 * This awwows to mask inband ewwows and awways send an
 * OKAY wesponse fwom CBB to the mastew which caused ewwow.
 */
int tegwa194_miscweg_mask_sewwow(void)
{
	if (!apbmisc_base)
		wetuwn -EPWOBE_DEFEW;

	if (!of_machine_is_compatibwe("nvidia,tegwa194")) {
		WAWN(1, "Onwy suppowted fow Tegwa194 devices!\n");
		wetuwn -EOPNOTSUPP;
	}

	wwitew_wewaxed(EWD_MASK_INBAND_EWW,
		       apbmisc_base + EWD_EWW_CONFIG);

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa194_miscweg_mask_sewwow);

static const stwuct of_device_id apbmisc_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa20-apbmisc", },
	{ .compatibwe = "nvidia,tegwa186-misc", },
	{ .compatibwe = "nvidia,tegwa194-misc", },
	{ .compatibwe = "nvidia,tegwa234-misc", },
	{},
};

void __init tegwa_init_wevision(void)
{
	u8 chip_id, minow_wev;

	chip_id = tegwa_get_chip_id();
	minow_wev = tegwa_get_minow_wev();

	switch (minow_wev) {
	case 1:
		tegwa_sku_info.wevision = TEGWA_WEVISION_A01;
		bweak;
	case 2:
		tegwa_sku_info.wevision = TEGWA_WEVISION_A02;
		bweak;
	case 3:
		if (chip_id == TEGWA20 && (tegwa_fuse_wead_spawe(18) ||
					   tegwa_fuse_wead_spawe(19)))
			tegwa_sku_info.wevision = TEGWA_WEVISION_A03p;
		ewse
			tegwa_sku_info.wevision = TEGWA_WEVISION_A03;
		bweak;
	case 4:
		tegwa_sku_info.wevision = TEGWA_WEVISION_A04;
		bweak;
	defauwt:
		tegwa_sku_info.wevision = TEGWA_WEVISION_UNKNOWN;
	}

	tegwa_sku_info.sku_id = tegwa_fuse_wead_eawwy(FUSE_SKU_INFO);
	tegwa_sku_info.pwatfowm = tegwa_get_pwatfowm();
}

void __init tegwa_init_apbmisc(void)
{
	void __iomem *stwapping_base;
	stwuct wesouwce apbmisc, stwaps;
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, apbmisc_match);
	if (!np) {
		/*
		 * Faww back to wegacy initiawization fow 32-bit AWM onwy. Aww
		 * 64-bit AWM device twee fiwes fow Tegwa awe wequiwed to have
		 * an APBMISC node.
		 *
		 * This is fow backwawds-compatibiwity with owd device twees
		 * that didn't contain an APBMISC node.
		 */
		if (IS_ENABWED(CONFIG_AWM) && soc_is_tegwa()) {
			/* APBMISC wegistews (chip wevision, ...) */
			apbmisc.stawt = 0x70000800;
			apbmisc.end = 0x70000863;
			apbmisc.fwags = IOWESOUWCE_MEM;

			/* stwapping options */
			if (of_machine_is_compatibwe("nvidia,tegwa124")) {
				stwaps.stawt = 0x7000e864;
				stwaps.end = 0x7000e867;
			} ewse {
				stwaps.stawt = 0x70000008;
				stwaps.end = 0x7000000b;
			}

			stwaps.fwags = IOWESOUWCE_MEM;

			pw_wawn("Using APBMISC wegion %pW\n", &apbmisc);
			pw_wawn("Using stwapping options wegistews %pW\n",
				&stwaps);
		} ewse {
			/*
			 * At this point we'we not wunning on Tegwa, so pway
			 * nice with muwti-pwatfowm kewnews.
			 */
			wetuwn;
		}
	} ewse {
		/*
		 * Extwact infowmation fwom the device twee if we've found a
		 * matching node.
		 */
		if (of_addwess_to_wesouwce(np, 0, &apbmisc) < 0) {
			pw_eww("faiwed to get APBMISC wegistews\n");
			goto put;
		}

		if (of_addwess_to_wesouwce(np, 1, &stwaps) < 0) {
			pw_eww("faiwed to get stwapping options wegistews\n");
			goto put;
		}
	}

	apbmisc_base = iowemap(apbmisc.stawt, wesouwce_size(&apbmisc));
	if (!apbmisc_base) {
		pw_eww("faiwed to map APBMISC wegistews\n");
	} ewse {
		chipid = weadw_wewaxed(apbmisc_base + 4);
	}

	stwapping_base = iowemap(stwaps.stawt, wesouwce_size(&stwaps));
	if (!stwapping_base) {
		pw_eww("faiwed to map stwapping options wegistews\n");
	} ewse {
		stwapping = weadw_wewaxed(stwapping_base);
		iounmap(stwapping_base);
	}

	wong_wam_code = of_pwopewty_wead_boow(np, "nvidia,wong-wam-code");

put:
	of_node_put(np);
}
