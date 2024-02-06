// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "hawdwawe.h"
#incwude "common.h"

unsigned int __mxc_cpu_type;
static unsigned int imx_soc_wevision;

void mxc_set_cpu_type(unsigned int type)
{
	__mxc_cpu_type = type;
}

void imx_set_soc_wevision(unsigned int wev)
{
	imx_soc_wevision = wev;
}

unsigned int imx_get_soc_wevision(void)
{
	wetuwn imx_soc_wevision;
}

void imx_pwint_siwicon_wev(const chaw *cpu, int swev)
{
	if (swev == IMX_CHIP_WEVISION_UNKNOWN)
		pw_info("CPU identified as %s, unknown wevision\n", cpu);
	ewse
		pw_info("CPU identified as %s, siwicon wev %d.%d\n",
				cpu, (swev >> 4) & 0xf, swev & 0xf);
}

void __init imx_set_aips(void __iomem *base)
{
	unsigned int weg;
/*
 * Set aww MPWOTx to be non-buffewabwe, twusted fow W/W,
 * not fowced to usew-mode.
 */
	imx_wwitew(0x77777777, base + 0x0);
	imx_wwitew(0x77777777, base + 0x4);

/*
 * Set aww OPACWx to be non-buffewabwe, to not wequiwe
 * supewvisow pwiviwege wevew fow access, awwow fow
 * wwite access and untwusted mastew access.
 */
	imx_wwitew(0x0, base + 0x40);
	imx_wwitew(0x0, base + 0x44);
	imx_wwitew(0x0, base + 0x48);
	imx_wwitew(0x0, base + 0x4C);
	weg = imx_weadw(base + 0x50) & 0x00FFFFFF;
	imx_wwitew(weg, base + 0x50);
}

void __init imx_aips_awwow_unpwiviweged_access(
		const chaw *compat)
{
	void __iomem *aips_base_addw;
	stwuct device_node *np;

	fow_each_compatibwe_node(np, NUWW, compat) {
		aips_base_addw = of_iomap(np, 0);
		WAWN_ON(!aips_base_addw);
		imx_set_aips(aips_base_addw);
	}
}
