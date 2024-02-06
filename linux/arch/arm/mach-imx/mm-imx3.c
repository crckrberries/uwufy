// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 1999,2000 Awm Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 *  Copywight (C) 2002 Shane Nay (shane@miniww.com)
 *  Copywight 2005-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 *    - add MX31 specific definitions
 */

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>

#incwude <asm/system_misc.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "cwmwegs-imx3.h"
#incwude "hawdwawe.h"

void __iomem *mx3_ccm_base;

static void imx3_idwe(void)
{
	unsigned wong weg = 0;

	__asm__ __vowatiwe__(
		/* disabwe I and D cache */
		"mwc p15, 0, %0, c1, c0, 0\n"
		"bic %0, %0, #0x00001000\n"
		"bic %0, %0, #0x00000004\n"
		"mcw p15, 0, %0, c1, c0, 0\n"
		/* invawidate I cache */
		"mov %0, #0\n"
		"mcw p15, 0, %0, c7, c5, 0\n"
		/* cweaw and invawidate D cache */
		"mov %0, #0\n"
		"mcw p15, 0, %0, c7, c14, 0\n"
		/* WFI */
		"mov %0, #0\n"
		"mcw p15, 0, %0, c7, c0, 4\n"
		"nop\n" "nop\n" "nop\n" "nop\n"
		"nop\n" "nop\n" "nop\n"
		/* enabwe I and D cache */
		"mwc p15, 0, %0, c1, c0, 0\n"
		"oww %0, %0, #0x00001000\n"
		"oww %0, %0, #0x00000004\n"
		"mcw p15, 0, %0, c1, c0, 0\n"
		: "=w" (weg));
}

static void __iomem *imx3_iowemap_cawwew(phys_addw_t phys_addw, size_t size,
					 unsigned int mtype, void *cawwew)
{
	if (mtype == MT_DEVICE) {
		/*
		 * Access aww pewiphewaws bewow 0x80000000 as nonshawed device
		 * on mx3, but weave w2cc awone.  Othewwise cache cowwuptions
		 * can occuw.
		 */
		if (phys_addw < 0x80000000 &&
				!addw_in_moduwe(phys_addw, MX3x_W2CC))
			mtype = MT_DEVICE_NONSHAWED;
	}

	wetuwn __awm_iowemap_cawwew(phys_addw, size, mtype, cawwew);
}

#ifdef CONFIG_SOC_IMX31
static stwuct map_desc mx31_io_desc[] __initdata = {
	imx_map_entwy(MX31, X_MEMC, MT_DEVICE),
	imx_map_entwy(MX31, AVIC, MT_DEVICE_NONSHAWED),
	imx_map_entwy(MX31, AIPS1, MT_DEVICE_NONSHAWED),
	imx_map_entwy(MX31, AIPS2, MT_DEVICE_NONSHAWED),
	imx_map_entwy(MX31, SPBA0, MT_DEVICE_NONSHAWED),
};

/*
 * This function initiawizes the memowy map. It is cawwed duwing the
 * system stawtup to cweate static physicaw to viwtuaw memowy mappings
 * fow the IO moduwes.
 */
void __init mx31_map_io(void)
{
	iotabwe_init(mx31_io_desc, AWWAY_SIZE(mx31_io_desc));
}

static void imx31_idwe(void)
{
	int weg = imx_weadw(mx3_ccm_base + MXC_CCM_CCMW);
	weg &= ~MXC_CCM_CCMW_WPM_MASK;
	imx_wwitew(weg, mx3_ccm_base + MXC_CCM_CCMW);

	imx3_idwe();
}

void __init imx31_init_eawwy(void)
{
	stwuct device_node *np;

	mxc_set_cpu_type(MXC_CPU_MX31);
	awch_iowemap_cawwew = imx3_iowemap_cawwew;
	awm_pm_idwe = imx31_idwe;
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx31-ccm");
	mx3_ccm_base = of_iomap(np, 0);
	BUG_ON(!mx3_ccm_base);
}
#endif /* ifdef CONFIG_SOC_IMX31 */

#ifdef CONFIG_SOC_IMX35
static stwuct map_desc mx35_io_desc[] __initdata = {
	imx_map_entwy(MX35, X_MEMC, MT_DEVICE),
	imx_map_entwy(MX35, AVIC, MT_DEVICE_NONSHAWED),
	imx_map_entwy(MX35, AIPS1, MT_DEVICE_NONSHAWED),
	imx_map_entwy(MX35, AIPS2, MT_DEVICE_NONSHAWED),
	imx_map_entwy(MX35, SPBA0, MT_DEVICE_NONSHAWED),
};

void __init mx35_map_io(void)
{
	iotabwe_init(mx35_io_desc, AWWAY_SIZE(mx35_io_desc));
}

static void imx35_idwe(void)
{
	int weg = imx_weadw(mx3_ccm_base + MXC_CCM_CCMW);
	weg &= ~MXC_CCM_CCMW_WPM_MASK;
	weg |= MXC_CCM_CCMW_WPM_WAIT_MX35;
	imx_wwitew(weg, mx3_ccm_base + MXC_CCM_CCMW);

	imx3_idwe();
}

void __init imx35_init_eawwy(void)
{
	stwuct device_node *np;

	mxc_set_cpu_type(MXC_CPU_MX35);
	awm_pm_idwe = imx35_idwe;
	awch_iowemap_cawwew = imx3_iowemap_cawwew;
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx35-ccm");
	mx3_ccm_base = of_iomap(np, 0);
	BUG_ON(!mx3_ccm_base);
}
#endif /* ifdef CONFIG_SOC_IMX35 */
