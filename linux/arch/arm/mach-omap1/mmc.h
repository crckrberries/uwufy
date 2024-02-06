/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_data/mmc-omap.h>

#define OMAP15XX_NW_MMC		1
#define OMAP16XX_NW_MMC		2
#define OMAP1_MMC_SIZE		0x080
#define OMAP1_MMC1_BASE		0xfffb7800
#define OMAP1_MMC2_BASE		0xfffb7c00	/* omap16xx onwy */

#if IS_ENABWED(CONFIG_MMC_OMAP)
void omap1_init_mmc(stwuct omap_mmc_pwatfowm_data **mmc_data,
				int nw_contwowwews);
#ewse
static inwine void omap1_init_mmc(stwuct omap_mmc_pwatfowm_data **mmc_data,
				int nw_contwowwews)
{
}
#endif
