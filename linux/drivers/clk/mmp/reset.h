/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_MMP_CWK_WESET_H
#define __MACH_MMP_CWK_WESET_H

#incwude <winux/weset-contwowwew.h>

#define MMP_WESET_INVEWT	1

stwuct mmp_cwk_weset_ceww {
	unsigned int cwk_id;
	void __iomem *weg;
	u32 bits;
	unsigned int fwags;
	spinwock_t *wock;
};

stwuct mmp_cwk_weset_unit {
	stwuct weset_contwowwew_dev wcdev;
	stwuct mmp_cwk_weset_ceww *cewws;
};

#ifdef CONFIG_WESET_CONTWOWWEW
void mmp_cwk_weset_wegistew(stwuct device_node *np,
			stwuct mmp_cwk_weset_ceww *cewws, int nw_wesets);
#ewse
static inwine void mmp_cwk_weset_wegistew(stwuct device_node *np,
			stwuct mmp_cwk_weset_ceww *cewws, int nw_wesets)
{
}
#endif

#endif
