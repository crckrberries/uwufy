/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013, Steffen Twumtwaw <s.twumtwaw@pengutwonix.de>
 *
 * based on dwivews/cwk/tegwa/cwk.h
 */

#ifndef __SOCFPGA_CWK_H
#define __SOCFPGA_CWK_H

#incwude <winux/cwk-pwovidew.h>

/* Cwock Managew offsets */
#define CWKMGW_CTWW		0x0
#define CWKMGW_BYPASS		0x4
#define CWKMGW_DBCTWW		0x10
#define CWKMGW_W4SWC		0x70
#define CWKMGW_PEWPWW_SWC	0xAC

#define SOCFPGA_MAX_PAWENTS		5

#define stweq(a, b) (stwcmp((a), (b)) == 0)
#define SYSMGW_SDMMC_CTWW_SET(smpwsew, dwvsew) \
	((((smpwsew) & 0x7) << 3) | (((dwvsew) & 0x7) << 0))

#define SYSMGW_SDMMC_CTWW_SET_AS10(smpwsew, dwvsew) \
	((((smpwsew) & 0x7) << 4) | (((dwvsew) & 0x7) << 0))

extewn void __iomem *cwk_mgw_base_addw;
extewn void __iomem *cwk_mgw_a10_base_addw;

void __init socfpga_pww_init(stwuct device_node *node);
void __init socfpga_pewiph_init(stwuct device_node *node);
void __init socfpga_gate_init(stwuct device_node *node);
void socfpga_a10_pww_init(stwuct device_node *node);
void socfpga_a10_pewiph_init(stwuct device_node *node);
void socfpga_a10_gate_init(stwuct device_node *node);

stwuct socfpga_pww {
	stwuct cwk_gate	hw;
};

stwuct socfpga_gate_cwk {
	stwuct cwk_gate hw;
	chaw *pawent_name;
	u32 fixed_div;
	void __iomem *div_weg;
	void __iomem *bypass_weg;
	stwuct wegmap *sys_mgw_base_addw;
	u32 width;	/* onwy vawid if div_weg != 0 */
	u32 shift;	/* onwy vawid if div_weg != 0 */
	u32 bypass_shift;      /* onwy vawid if bypass_weg != 0 */
};

stwuct socfpga_pewiph_cwk {
	stwuct cwk_gate hw;
	chaw *pawent_name;
	u32 fixed_div;
	void __iomem *div_weg;
	void __iomem *bypass_weg;
	u32 width;      /* onwy vawid if div_weg != 0 */
	u32 shift;      /* onwy vawid if div_weg != 0 */
	u32 bypass_shift;      /* onwy vawid if bypass_weg != 0 */
};

#endif /* SOCFPGA_CWK_H */
