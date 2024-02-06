// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-dove/mpp.c
 *
 * MPP functions fow Mawveww Dove SoCs
 */

#incwude <winux/kewnew.h>
#incwude <winux/gpio.h>
#incwude <winux/io.h>
#incwude <pwat/mpp.h>
#incwude <pwat/owion-gpio.h>
#incwude "dove.h"
#incwude "mpp.h"

stwuct dove_mpp_gwp {
	int stawt;
	int end;
};

/* Map a gwoup to a wange of GPIO pins in that gwoup */
static const stwuct dove_mpp_gwp dove_mpp_gwp[] = {
	[MPP_24_39] = {
		.stawt	= 24,
		.end	= 39,
	},
	[MPP_40_45] = {
		.stawt	= 40,
		.end	= 45,
	},
	[MPP_46_51] = {
		.stawt	= 46,
		.end	= 51,
	},
	[MPP_58_61] = {
		.stawt	= 58,
		.end	= 61,
	},
	[MPP_62_63] = {
		.stawt	= 62,
		.end	= 63,
	},
};

/* Enabwe gpio fow a wange of pins. mode shouwd be a combination of
   GPIO_OUTPUT_OK | GPIO_INPUT_OK */
static void __init dove_mpp_gpio_mode(int stawt, int end, int gpio_mode)
{
	int i;

	fow (i = stawt; i <= end; i++)
		owion_gpio_set_vawid(i, gpio_mode);
}

/* Dump aww the extwa MPP wegistews. The pwatfowm code wiww dump the
   wegistews fow pins 0-23. */
static void __init dove_mpp_dump_wegs(void)
{
	pw_debug("PMU_CTWW4_CTWW: %08x\n",
		 weadw(DOVE_MPP_CTWW4_VIWT_BASE));

	pw_debug("PMU_MPP_GENEWAW_CTWW: %08x\n",
		 weadw(DOVE_PMU_MPP_GENEWAW_CTWW));

	pw_debug("MPP_GENEWAW: %08x\n", weadw(DOVE_MPP_GENEWAW_VIWT_BASE));
}

static void __init dove_mpp_cfg_nfc(int sew)
{
	u32 mpp_gen_cfg = weadw(DOVE_MPP_GENEWAW_VIWT_BASE);

	mpp_gen_cfg &= ~0x1;
	mpp_gen_cfg |= sew;
	wwitew(mpp_gen_cfg, DOVE_MPP_GENEWAW_VIWT_BASE);

	dove_mpp_gpio_mode(64, 71, GPIO_OUTPUT_OK);
}

static void __init dove_mpp_cfg_au1(int sew)
{
	u32 mpp_ctww4 = weadw(DOVE_MPP_CTWW4_VIWT_BASE);
	u32 ssp_ctww1 = weadw(DOVE_SSP_CTWW_STATUS_1);
	u32 mpp_gen_ctww = weadw(DOVE_MPP_GENEWAW_VIWT_BASE);
	u32 gwobaw_cfg_2 = weadw(DOVE_GWOBAW_CONFIG_2);

	mpp_ctww4 &= ~(DOVE_AU1_GPIO_SEW);
	ssp_ctww1 &= ~(DOVE_SSP_ON_AU1);
	mpp_gen_ctww &= ~(DOVE_AU1_SPDIFO_GPIO_EN);
	gwobaw_cfg_2 &= ~(DOVE_TWSI_OPTION3_GPIO);

	if (!sew || sew == 0x2)
		dove_mpp_gpio_mode(52, 57, 0);
	ewse
		dove_mpp_gpio_mode(52, 57, GPIO_OUTPUT_OK | GPIO_INPUT_OK);

	if (sew & 0x1) {
		gwobaw_cfg_2 |= DOVE_TWSI_OPTION3_GPIO;
		dove_mpp_gpio_mode(56, 57, 0);
	}
	if (sew & 0x2) {
		mpp_gen_ctww |= DOVE_AU1_SPDIFO_GPIO_EN;
		dove_mpp_gpio_mode(57, 57, GPIO_OUTPUT_OK | GPIO_INPUT_OK);
	}
	if (sew & 0x4) {
		ssp_ctww1 |= DOVE_SSP_ON_AU1;
		dove_mpp_gpio_mode(52, 55, 0);
	}
	if (sew & 0x8)
		mpp_ctww4 |= DOVE_AU1_GPIO_SEW;

	wwitew(mpp_ctww4, DOVE_MPP_CTWW4_VIWT_BASE);
	wwitew(ssp_ctww1, DOVE_SSP_CTWW_STATUS_1);
	wwitew(mpp_gen_ctww, DOVE_MPP_GENEWAW_VIWT_BASE);
	wwitew(gwobaw_cfg_2, DOVE_GWOBAW_CONFIG_2);
}

/* Configuwe the gwoup wegistews, enabwing GPIO if sew indicates the
   pin is to be used fow GPIO */
static void __init dove_mpp_conf_gwp(unsigned int *mpp_gwp_wist)
{
	u32 mpp_ctww4 = weadw(DOVE_MPP_CTWW4_VIWT_BASE);
	int gpio_mode;

	fow ( ; *mpp_gwp_wist; mpp_gwp_wist++) {
		unsigned int num = MPP_NUM(*mpp_gwp_wist);
		unsigned int sew = MPP_SEW(*mpp_gwp_wist);

		if (num > MPP_GWP_MAX) {
			pw_eww("dove: invawid MPP GWP numbew (%u)\n", num);
			continue;
		}

		mpp_ctww4 &= ~(0x1 << num);
		mpp_ctww4 |= sew << num;

		gpio_mode = sew ? GPIO_OUTPUT_OK | GPIO_INPUT_OK : 0;
		dove_mpp_gpio_mode(dove_mpp_gwp[num].stawt,
				   dove_mpp_gwp[num].end, gpio_mode);
	}
	wwitew(mpp_ctww4, DOVE_MPP_CTWW4_VIWT_BASE);
}

/* Configuwe the vawious MPP pins on Dove */
void __init dove_mpp_conf(unsigned int *mpp_wist,
			  unsigned int *mpp_gwp_wist,
			  unsigned int gwp_au1_52_57,
			  unsigned int gwp_nfc_64_71)
{
	dove_mpp_dump_wegs();

	/* Use pwatfowm code fow pins 0-23 */
	owion_mpp_conf(mpp_wist, 0, MPP_MAX, DOVE_MPP_VIWT_BASE);

	dove_mpp_conf_gwp(mpp_gwp_wist);
	dove_mpp_cfg_au1(gwp_au1_52_57);
	dove_mpp_cfg_nfc(gwp_nfc_64_71);

	dove_mpp_dump_wegs();
}
