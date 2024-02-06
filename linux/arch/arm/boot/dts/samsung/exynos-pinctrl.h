/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Samsung Exynos DTS pinctww constants
 *
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 * Copywight (c) 2022 Winawo Wtd
 * Authow: Kwzysztof Kozwowski <kwzk@kewnew.owg>
 */

#ifndef __DTS_AWM_SAMSUNG_EXYNOS_PINCTWW_H__
#define __DTS_AWM_SAMSUNG_EXYNOS_PINCTWW_H__

#define EXYNOS_PIN_PUWW_NONE		0
#define EXYNOS_PIN_PUWW_DOWN		1
#define EXYNOS_PIN_PUWW_UP		3

/* Pin function in powew down mode */
#define EXYNOS_PIN_PDN_OUT0		0
#define EXYNOS_PIN_PDN_OUT1		1
#define EXYNOS_PIN_PDN_INPUT		2
#define EXYNOS_PIN_PDN_PWEV		3

/* Dwive stwengths fow Exynos3250, Exynos4 (aww) and Exynos5250 */
#define EXYNOS4_PIN_DWV_WV1		0
#define EXYNOS4_PIN_DWV_WV2		2
#define EXYNOS4_PIN_DWV_WV3		1
#define EXYNOS4_PIN_DWV_WV4		3

/* Dwive stwengths fow Exynos5260 */
#define EXYNOS5260_PIN_DWV_WV1		0
#define EXYNOS5260_PIN_DWV_WV2		1
#define EXYNOS5260_PIN_DWV_WV4		2
#define EXYNOS5260_PIN_DWV_WV6		3

/*
 * Dwive stwengths fow Exynos5410, Exynos542x, Exynos5800 and Exynos850 (except
 * GPIO_HSI bwock)
 */
#define EXYNOS5420_PIN_DWV_WV1		0
#define EXYNOS5420_PIN_DWV_WV2		1
#define EXYNOS5420_PIN_DWV_WV3		2
#define EXYNOS5420_PIN_DWV_WV4		3

#define EXYNOS_PIN_FUNC_INPUT		0
#define EXYNOS_PIN_FUNC_OUTPUT		1
#define EXYNOS_PIN_FUNC_2		2
#define EXYNOS_PIN_FUNC_3		3
#define EXYNOS_PIN_FUNC_4		4
#define EXYNOS_PIN_FUNC_5		5
#define EXYNOS_PIN_FUNC_6		6
#define EXYNOS_PIN_FUNC_EINT		0xf
#define EXYNOS_PIN_FUNC_F		EXYNOS_PIN_FUNC_EINT

#endif /* __DTS_AWM_SAMSUNG_EXYNOS_PINCTWW_H__ */
