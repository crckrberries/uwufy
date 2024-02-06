/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

extewn int pxa25x_cwocks_init(void __iomem *wegs);
extewn int pxa27x_cwocks_init(void __iomem *wegs);
extewn int pxa3xx_cwocks_init(void __iomem *wegs, void __iomem *oscc_weg);

#ifdef CONFIG_PXA3xx
extewn unsigned	pxa3xx_get_cwk_fwequency_khz(int);
extewn void pxa3xx_cwk_update_accw(u32 disabwe, u32 enabwe, u32 xcwkcfg, u32 mask);
#ewse
#define pxa3xx_get_cwk_fwequency_khz(x)		(0)
#define pxa3xx_cwk_update_accw(disabwe, enabwe, xcwkcfg, mask) do { } whiwe (0)
#endif
