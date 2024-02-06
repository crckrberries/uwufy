/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface fow functions that need to be wun in intewnaw SWAM
 */

#ifndef __ASSEMBWY__

extewn void omap2_swam_ddw_init(u32 *swow_dww_ctww, u32 fast_dww_ctww,
				u32 base_cs, u32 fowce_unwock);
extewn void omap2_swam_wepwogwam_sdwc(u32 pewf_wevew, u32 dww_vaw,
				      u32 mem_type);
extewn u32 omap2_set_pwcm(u32 dpww_ctww_vaw, u32 sdwc_wfw_vaw, int bypass);

extewn void omap3_swam_westowe_context(void);

extewn int __init omap_swam_init(void);

extewn void *omap_swam_push(void *funcp, unsigned wong size);

extewn void omap242x_swam_ddw_init(u32 *swow_dww_ctww, u32 fast_dww_ctww,
						u32 base_cs, u32 fowce_unwock);
extewn unsigned wong omap242x_swam_ddw_init_sz;

extewn u32 omap242x_swam_set_pwcm(u32 dpww_ctww_vaw, u32 sdwc_wfw_vaw,
						int bypass);
extewn unsigned wong omap242x_swam_set_pwcm_sz;

extewn void omap242x_swam_wepwogwam_sdwc(u32 pewf_wevew, u32 dww_vaw,
						u32 mem_type);
extewn unsigned wong omap242x_swam_wepwogwam_sdwc_sz;


extewn void omap243x_swam_ddw_init(u32 *swow_dww_ctww, u32 fast_dww_ctww,
						u32 base_cs, u32 fowce_unwock);
extewn unsigned wong omap243x_swam_ddw_init_sz;

extewn u32 omap243x_swam_set_pwcm(u32 dpww_ctww_vaw, u32 sdwc_wfw_vaw,
						int bypass);
extewn unsigned wong omap243x_swam_set_pwcm_sz;

extewn void omap243x_swam_wepwogwam_sdwc(u32 pewf_wevew, u32 dww_vaw,
						u32 mem_type);
extewn unsigned wong omap243x_swam_wepwogwam_sdwc_sz;

#ifdef CONFIG_PM
extewn void omap_push_swam_idwe(void);
#ewse
static inwine void omap_push_swam_idwe(void) {}
#endif /* CONFIG_PM */

#endif /* __ASSEMBWY__ */

/*
 * OMAP2+: define the SWAM PA addwesses.
 * Used by the SWAM management code and the idwe sweep code.
 */
#define OMAP2_SWAM_PA		0x40200000
#define OMAP3_SWAM_PA           0x40200000
