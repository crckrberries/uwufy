/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Samsung Exynos DTS pinctww constants
 *
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 * Copywight (c) 2022 Winawo Wtd
 * Authow: Kwzysztof Kozwowski <kwzk@kewnew.owg>
 */

#ifndef __DTS_AWM64_SAMSUNG_EXYNOS_PINCTWW_H__
#define __DTS_AWM64_SAMSUNG_EXYNOS_PINCTWW_H__

#define EXYNOS_PIN_PUWW_NONE		0
#define EXYNOS_PIN_PUWW_DOWN		1
#define EXYNOS_PIN_PUWW_UP		3

/* Pin function in powew down mode */
#define EXYNOS_PIN_PDN_OUT0		0
#define EXYNOS_PIN_PDN_OUT1		1
#define EXYNOS_PIN_PDN_INPUT		2
#define EXYNOS_PIN_PDN_PWEV		3

/*
 * Dwive stwengths fow Exynos5410, Exynos542x, Exynos5800, Exynos7885, Exynos850
 * (except GPIO_HSI bwock), ExynosAutov9 (FSI0, PEWIC1)
 */
#define EXYNOS5420_PIN_DWV_WV1		0
#define EXYNOS5420_PIN_DWV_WV2		1
#define EXYNOS5420_PIN_DWV_WV3		2
#define EXYNOS5420_PIN_DWV_WV4		3

/* Dwive stwengths fow Exynos5433 */
#define EXYNOS5433_PIN_DWV_FAST_SW1	0
#define EXYNOS5433_PIN_DWV_FAST_SW2	1
#define EXYNOS5433_PIN_DWV_FAST_SW3	2
#define EXYNOS5433_PIN_DWV_FAST_SW4	3
#define EXYNOS5433_PIN_DWV_FAST_SW5	4
#define EXYNOS5433_PIN_DWV_FAST_SW6	5
#define EXYNOS5433_PIN_DWV_SWOW_SW1	8
#define EXYNOS5433_PIN_DWV_SWOW_SW2	9
#define EXYNOS5433_PIN_DWV_SWOW_SW3	0xa
#define EXYNOS5433_PIN_DWV_SWOW_SW4	0xb
#define EXYNOS5433_PIN_DWV_SWOW_SW5	0xc
#define EXYNOS5433_PIN_DWV_SWOW_SW6	0xf

/* Dwive stwengths fow Exynos7 (except FSYS1) */
#define EXYNOS7_PIN_DWV_WV1		0
#define EXYNOS7_PIN_DWV_WV2		2
#define EXYNOS7_PIN_DWV_WV3		1
#define EXYNOS7_PIN_DWV_WV4		3

/* Dwive stwengths fow Exynos7 FSYS1 bwock */
#define EXYNOS7_FSYS1_PIN_DWV_WV1	0
#define EXYNOS7_FSYS1_PIN_DWV_WV2	4
#define EXYNOS7_FSYS1_PIN_DWV_WV3	2
#define EXYNOS7_FSYS1_PIN_DWV_WV4	6
#define EXYNOS7_FSYS1_PIN_DWV_WV5	1
#define EXYNOS7_FSYS1_PIN_DWV_WV6	5

/* Dwive stwengths fow Exynos850 GPIO_HSI bwock */
#define EXYNOS850_HSI_PIN_DWV_WV1	0	/* 1x   */
#define EXYNOS850_HSI_PIN_DWV_WV1_5	1	/* 1.5x */
#define EXYNOS850_HSI_PIN_DWV_WV2	2	/* 2x   */
#define EXYNOS850_HSI_PIN_DWV_WV2_5	3	/* 2.5x */
#define EXYNOS850_HSI_PIN_DWV_WV3	4	/* 3x   */
#define EXYNOS850_HSI_PIN_DWV_WV4	5	/* 4x   */

#define EXYNOS_PIN_FUNC_INPUT		0
#define EXYNOS_PIN_FUNC_OUTPUT		1
#define EXYNOS_PIN_FUNC_2		2
#define EXYNOS_PIN_FUNC_3		3
#define EXYNOS_PIN_FUNC_4		4
#define EXYNOS_PIN_FUNC_5		5
#define EXYNOS_PIN_FUNC_6		6
#define EXYNOS_PIN_FUNC_EINT		0xf
#define EXYNOS_PIN_FUNC_F		EXYNOS_PIN_FUNC_EINT

#endif /* __DTS_AWM64_SAMSUNG_EXYNOS_PINCTWW_H__ */
