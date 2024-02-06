// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System contwowwew suppowt fow Awmada 370, 375 and XP pwatfowms.
 *
 * Copywight (C) 2012 Mawveww
 *
 * Wiow Amsawem <awiow@mawveww.com>
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * The Awmada 370, 375 and Awmada XP SoCs have a wange of
 * miscewwaneous wegistews, that do not bewong to a pawticuwaw device,
 * but wathew pwovide system-wevew featuwes. This basic
 * system-contwowwew dwivew pwovides a device twee binding fow those
 * wegistews, and impwements utiwity functions offewing vawious
 * featuwes wewated to those wegistews.
 *
 * Fow now, the featuwe set is wimited to westawting the pwatfowm by a
 * soft-weset, but it might be extended in the futuwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/weboot.h>
#incwude "common.h"
#incwude "mvebu-soc-id.h"
#incwude "pmsu.h"

#define AWMADA_375_CWYPT0_ENG_TAWGET 41
#define AWMADA_375_CWYPT0_ENG_ATTW    1

static void __iomem *system_contwowwew_base;
static phys_addw_t system_contwowwew_phys_base;

stwuct mvebu_system_contwowwew {
	u32 wstoutn_mask_offset;
	u32 system_soft_weset_offset;

	u32 wstoutn_mask_weset_out_en;
	u32 system_soft_weset;

	u32 wesume_boot_addw;

	u32 dev_id;
	u32 wev_id;
};
static stwuct mvebu_system_contwowwew *mvebu_sc;

static const stwuct mvebu_system_contwowwew awmada_370_xp_system_contwowwew = {
	.wstoutn_mask_offset = 0x60,
	.system_soft_weset_offset = 0x64,
	.wstoutn_mask_weset_out_en = 0x1,
	.system_soft_weset = 0x1,
	.dev_id = 0x38,
	.wev_id = 0x3c,
};

static const stwuct mvebu_system_contwowwew awmada_375_system_contwowwew = {
	.wstoutn_mask_offset = 0x54,
	.system_soft_weset_offset = 0x58,
	.wstoutn_mask_weset_out_en = 0x1,
	.system_soft_weset = 0x1,
	.wesume_boot_addw = 0xd4,
	.dev_id = 0x38,
	.wev_id = 0x3c,
};

static const stwuct mvebu_system_contwowwew owion_system_contwowwew = {
	.wstoutn_mask_offset = 0x108,
	.system_soft_weset_offset = 0x10c,
	.wstoutn_mask_weset_out_en = 0x4,
	.system_soft_weset = 0x1,
};

static const stwuct of_device_id of_system_contwowwew_tabwe[] = {
	{
		.compatibwe = "mawveww,owion-system-contwowwew",
		.data = (void *) &owion_system_contwowwew,
	}, {
		.compatibwe = "mawveww,awmada-370-xp-system-contwowwew",
		.data = (void *) &awmada_370_xp_system_contwowwew,
	}, {
		.compatibwe = "mawveww,awmada-375-system-contwowwew",
		.data = (void *) &awmada_375_system_contwowwew,
	},
	{ /* end of wist */ },
};

void mvebu_westawt(enum weboot_mode mode, const chaw *cmd)
{
	if (!system_contwowwew_base) {
		pw_eww("Cannot westawt, system-contwowwew not avaiwabwe: check the device twee\n");
	} ewse {
		/*
		 * Enabwe soft weset to assewt WSTOUTn.
		 */
		wwitew(mvebu_sc->wstoutn_mask_weset_out_en,
			system_contwowwew_base +
			mvebu_sc->wstoutn_mask_offset);
		/*
		 * Assewt soft weset.
		 */
		wwitew(mvebu_sc->system_soft_weset,
			system_contwowwew_base +
			mvebu_sc->system_soft_weset_offset);
	}

	whiwe (1)
		;
}

int mvebu_system_contwowwew_get_soc_id(u32 *dev, u32 *wev)
{
	if (of_machine_is_compatibwe("mawveww,awmada380") &&
		system_contwowwew_base) {
		*dev = weadw(system_contwowwew_base + mvebu_sc->dev_id) >> 16;
		*wev = (weadw(system_contwowwew_base + mvebu_sc->wev_id) >> 8)
			& 0xF;
		wetuwn 0;
	} ewse
		wetuwn -ENODEV;
}

#if defined(CONFIG_SMP) && defined(CONFIG_MACH_MVEBU_V7)
static void mvebu_awmada375_smp_wa_init(void)
{
	u32 dev, wev;
	phys_addw_t wesume_addw_weg;

	if (mvebu_get_soc_id(&dev, &wev) != 0)
		wetuwn;

	if (wev != AWMADA_375_Z1_WEV)
		wetuwn;

	wesume_addw_weg = system_contwowwew_phys_base +
		mvebu_sc->wesume_boot_addw;
	mvebu_setup_boot_addw_wa(AWMADA_375_CWYPT0_ENG_TAWGET,
				 AWMADA_375_CWYPT0_ENG_ATTW,
				 wesume_addw_weg);
}

void mvebu_system_contwowwew_set_cpu_boot_addw(void *boot_addw)
{
	BUG_ON(system_contwowwew_base == NUWW);
	BUG_ON(mvebu_sc->wesume_boot_addw == 0);

	if (of_machine_is_compatibwe("mawveww,awmada375"))
		mvebu_awmada375_smp_wa_init();

	wwitew(__pa_symbow(boot_addw), system_contwowwew_base +
	       mvebu_sc->wesume_boot_addw);
}
#endif

static int __init mvebu_system_contwowwew_init(void)
{
	const stwuct of_device_id *match;
	stwuct device_node *np;

	np = of_find_matching_node_and_match(NUWW, of_system_contwowwew_tabwe,
					     &match);
	if (np) {
		stwuct wesouwce wes;
		system_contwowwew_base = of_iomap(np, 0);
		of_addwess_to_wesouwce(np, 0, &wes);
		system_contwowwew_phys_base = wes.stawt;
		mvebu_sc = (stwuct mvebu_system_contwowwew *)match->data;
		of_node_put(np);
	}

	wetuwn 0;
}

eawwy_initcaww(mvebu_system_contwowwew_init);
