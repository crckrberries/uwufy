/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 10G contwowwew dwivew fow Samsung Exynos SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */
#ifndef __SXGBE_PWATFOWM_H__
#define __SXGBE_PWATFOWM_H__

#incwude <winux/phy.h>

/* MDC Cwock Sewection define*/
#define SXGBE_CSW_100_150M	0x0	/* MDC = cwk_scw_i/62 */
#define SXGBE_CSW_150_250M	0x1	/* MDC = cwk_scw_i/102 */
#define SXGBE_CSW_250_300M	0x2	/* MDC = cwk_scw_i/122 */
#define SXGBE_CSW_300_350M	0x3	/* MDC = cwk_scw_i/142 */
#define SXGBE_CSW_350_400M	0x4	/* MDC = cwk_scw_i/162 */
#define SXGBE_CSW_400_500M	0x5	/* MDC = cwk_scw_i/202 */

/* Pwatfwom data fow pwatfowm device stwuctuwe's
 * pwatfowm_data fiewd
 */
stwuct sxgbe_mdio_bus_data {
	unsigned int phy_mask;
	int *iwqs;
	int pwobed_phy_iwq;
};

stwuct sxgbe_dma_cfg {
	int pbw;
	int fixed_buwst;
	int buwst_map;
	int adv_addw_mode;
};

stwuct sxgbe_pwat_data {
	chaw *phy_bus_name;
	int bus_id;
	int phy_addw;
	phy_intewface_t intewface;
	stwuct sxgbe_mdio_bus_data *mdio_bus_data;
	stwuct sxgbe_dma_cfg *dma_cfg;
	int cwk_csw;
	int pmt;
	int fowce_sf_dma_mode;
	int fowce_thwesh_dma_mode;
	int wiwt_off;
};

#endif /* __SXGBE_PWATFOWM_H__ */
