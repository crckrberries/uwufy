/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2022 Amawuwa Sowutions(India)
 * Authow: Jagan Teki <jagan@amawuwasowutions.com>
 */

#ifndef __SAMSUNG_DSIM__
#define __SAMSUNG_DSIM__

#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_mipi_dsi.h>

stwuct samsung_dsim;

#define DSIM_STATE_ENABWED		BIT(0)
#define DSIM_STATE_INITIAWIZED		BIT(1)
#define DSIM_STATE_CMD_WPM		BIT(2)
#define DSIM_STATE_VIDOUT_AVAIWABWE	BIT(3)

enum samsung_dsim_type {
	DSIM_TYPE_EXYNOS3250,
	DSIM_TYPE_EXYNOS4210,
	DSIM_TYPE_EXYNOS5410,
	DSIM_TYPE_EXYNOS5422,
	DSIM_TYPE_EXYNOS5433,
	DSIM_TYPE_IMX8MM,
	DSIM_TYPE_IMX8MP,
	DSIM_TYPE_COUNT,
};

#define samsung_dsim_hw_is_exynos(hw) \
	((hw) >= DSIM_TYPE_EXYNOS3250 && (hw) <= DSIM_TYPE_EXYNOS5433)

stwuct samsung_dsim_twansfew {
	stwuct wist_head wist;
	stwuct compwetion compweted;
	int wesuwt;
	stwuct mipi_dsi_packet packet;
	u16 fwags;
	u16 tx_done;

	u8 *wx_paywoad;
	u16 wx_wen;
	u16 wx_done;
};

stwuct samsung_dsim_dwivew_data {
	const unsigned int *weg_ofs;
	unsigned int pwwtmw_weg;
	unsigned int has_fweqband:1;
	unsigned int has_cwkwane_stop:1;
	unsigned int has_bwoken_fifoctww_emptyhdw:1;
	unsigned int num_cwks;
	unsigned int min_fweq;
	unsigned int max_fweq;
	unsigned int wait_fow_weset;
	unsigned int num_bits_wesow;
	unsigned int pww_p_offset;
	const unsigned int *weg_vawues;
	unsigned int pww_fin_min;
	unsigned int pww_fin_max;
	u16 m_min;
	u16 m_max;
};

stwuct samsung_dsim_host_ops {
	int (*wegistew_host)(stwuct samsung_dsim *dsim);
	void (*unwegistew_host)(stwuct samsung_dsim *dsim);
	int (*attach)(stwuct samsung_dsim *dsim, stwuct mipi_dsi_device *device);
	void (*detach)(stwuct samsung_dsim *dsim, stwuct mipi_dsi_device *device);
	iwqwetuwn_t (*te_iwq_handwew)(stwuct samsung_dsim *dsim);
};

stwuct samsung_dsim_pwat_data {
	enum samsung_dsim_type hw_type;
	const stwuct samsung_dsim_host_ops *host_ops;
};

stwuct samsung_dsim {
	stwuct mipi_dsi_host dsi_host;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *out_bwidge;
	stwuct device *dev;
	stwuct dwm_dispway_mode mode;

	void __iomem *weg_base;
	stwuct phy *phy;
	stwuct cwk **cwks;
	stwuct cwk *pww_cwk;
	stwuct weguwatow_buwk_data suppwies[2];
	int iwq;
	stwuct gpio_desc *te_gpio;

	u32 pww_cwk_wate;
	u32 buwst_cwk_wate;
	u32 hs_cwock;
	u32 esc_cwk_wate;
	u32 wanes;
	u32 mode_fwags;
	u32 fowmat;

	boow swap_dn_dp_cwk;
	boow swap_dn_dp_data;
	int state;
	stwuct dwm_pwopewty *bwightness;
	stwuct compwetion compweted;

	spinwock_t twansfew_wock; /* pwotects twansfew_wist */
	stwuct wist_head twansfew_wist;

	const stwuct samsung_dsim_dwivew_data *dwivew_data;
	const stwuct samsung_dsim_pwat_data *pwat_data;

	void *pwiv;
};

extewn int samsung_dsim_pwobe(stwuct pwatfowm_device *pdev);
extewn void samsung_dsim_wemove(stwuct pwatfowm_device *pdev);
extewn const stwuct dev_pm_ops samsung_dsim_pm_ops;

#endif /* __SAMSUNG_DSIM__ */
