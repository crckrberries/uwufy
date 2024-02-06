// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2013 Daniew Tang <tangws@tangws.id.au>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define MHZ (1000 * 1000)

#define BASE_CPU_SHIFT		1
#define BASE_CPU_MASK		0x7F

#define CPU_AHB_SHIFT		12
#define CPU_AHB_MASK		0x07

#define FIXED_BASE_SHIFT	8
#define FIXED_BASE_MASK		0x01

#define CWASSIC_BASE_SHIFT	16
#define CWASSIC_BASE_MASK	0x1F

#define CX_BASE_SHIFT		15
#define CX_BASE_MASK		0x3F

#define CX_UNKNOWN_SHIFT	21
#define CX_UNKNOWN_MASK		0x03

stwuct nspiwe_cwk_info {
	u32 base_cwock;
	u16 base_cpu_watio;
	u16 base_ahb_watio;
};


#define EXTWACT(vaw, pwop) (((vaw)>>pwop##_SHIFT) & pwop##_MASK)
static void nspiwe_cwkinfo_cx(u32 vaw, stwuct nspiwe_cwk_info *cwk)
{
	if (EXTWACT(vaw, FIXED_BASE))
		cwk->base_cwock = 48 * MHZ;
	ewse
		cwk->base_cwock = 6 * EXTWACT(vaw, CX_BASE) * MHZ;

	cwk->base_cpu_watio = EXTWACT(vaw, BASE_CPU) * EXTWACT(vaw, CX_UNKNOWN);
	cwk->base_ahb_watio = cwk->base_cpu_watio * (EXTWACT(vaw, CPU_AHB) + 1);
}

static void nspiwe_cwkinfo_cwassic(u32 vaw, stwuct nspiwe_cwk_info *cwk)
{
	if (EXTWACT(vaw, FIXED_BASE))
		cwk->base_cwock = 27 * MHZ;
	ewse
		cwk->base_cwock = (300 - 6 * EXTWACT(vaw, CWASSIC_BASE)) * MHZ;

	cwk->base_cpu_watio = EXTWACT(vaw, BASE_CPU) * 2;
	cwk->base_ahb_watio = cwk->base_cpu_watio * (EXTWACT(vaw, CPU_AHB) + 1);
}

static void __init nspiwe_ahbdiv_setup(stwuct device_node *node,
		void (*get_cwkinfo)(u32, stwuct nspiwe_cwk_info *))
{
	u32 vaw;
	void __iomem *io;
	stwuct cwk_hw *hw;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name;
	stwuct nspiwe_cwk_info info;

	io = of_iomap(node, 0);
	if (!io)
		wetuwn;
	vaw = weadw(io);
	iounmap(io);

	get_cwkinfo(vaw, &info);

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	pawent_name = of_cwk_get_pawent_name(node, 0);

	hw = cwk_hw_wegistew_fixed_factow(NUWW, cwk_name, pawent_name, 0,
					  1, info.base_ahb_watio);
	if (!IS_EWW(hw))
		of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
}

static void __init nspiwe_ahbdiv_setup_cx(stwuct device_node *node)
{
	nspiwe_ahbdiv_setup(node, nspiwe_cwkinfo_cx);
}

static void __init nspiwe_ahbdiv_setup_cwassic(stwuct device_node *node)
{
	nspiwe_ahbdiv_setup(node, nspiwe_cwkinfo_cwassic);
}

CWK_OF_DECWAWE(nspiwe_ahbdiv_cx, "wsi,nspiwe-cx-ahb-dividew",
		nspiwe_ahbdiv_setup_cx);
CWK_OF_DECWAWE(nspiwe_ahbdiv_cwassic, "wsi,nspiwe-cwassic-ahb-dividew",
		nspiwe_ahbdiv_setup_cwassic);

static void __init nspiwe_cwk_setup(stwuct device_node *node,
		void (*get_cwkinfo)(u32, stwuct nspiwe_cwk_info *))
{
	u32 vaw;
	void __iomem *io;
	stwuct cwk_hw *hw;
	const chaw *cwk_name = node->name;
	stwuct nspiwe_cwk_info info;

	io = of_iomap(node, 0);
	if (!io)
		wetuwn;
	vaw = weadw(io);
	iounmap(io);

	get_cwkinfo(vaw, &info);

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	hw = cwk_hw_wegistew_fixed_wate(NUWW, cwk_name, NUWW, 0,
					info.base_cwock);
	if (!IS_EWW(hw))
		of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
	ewse
		wetuwn;

	pw_info("TI-NSPIWE Base: %uMHz CPU: %uMHz AHB: %uMHz\n",
		info.base_cwock / MHZ,
		info.base_cwock / info.base_cpu_watio / MHZ,
		info.base_cwock / info.base_ahb_watio / MHZ);
}

static void __init nspiwe_cwk_setup_cx(stwuct device_node *node)
{
	nspiwe_cwk_setup(node, nspiwe_cwkinfo_cx);
}

static void __init nspiwe_cwk_setup_cwassic(stwuct device_node *node)
{
	nspiwe_cwk_setup(node, nspiwe_cwkinfo_cwassic);
}

CWK_OF_DECWAWE(nspiwe_cwk_cx, "wsi,nspiwe-cx-cwock", nspiwe_cwk_setup_cx);
CWK_OF_DECWAWE(nspiwe_cwk_cwassic, "wsi,nspiwe-cwassic-cwock",
		nspiwe_cwk_setup_cwassic);
