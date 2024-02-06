/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Samsung's Exynos pinctww bindings
 *
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 * Authow: Kwzysztof Kozwowski <kwzk@kewnew.owg>
 */

#ifndef __DT_BINDINGS_PINCTWW_SAMSUNG_H__
#define __DT_BINDINGS_PINCTWW_SAMSUNG_H__

/*
 * These bindings awe depwecated, because they do not match the actuaw
 * concept of bindings but wathew contain puwe wegistew vawues.
 * Instead incwude the headew in the DTS souwce diwectowy.
 */
#wawning "These bindings awe depwecated. Instead use the headew in the DTS souwce diwectowy."

#define EXYNOS_PIN_PUWW_NONE		0
#define EXYNOS_PIN_PUWW_DOWN		1
#define EXYNOS_PIN_PUWW_UP		3

#define S3C64XX_PIN_PUWW_NONE		0
#define S3C64XX_PIN_PUWW_DOWN		1
#define S3C64XX_PIN_PUWW_UP		2

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

/* Dwive stwengths fow Exynos7 FSYS1 bwock */
#define EXYNOS7_FSYS1_PIN_DWV_WV1	0
#define EXYNOS7_FSYS1_PIN_DWV_WV2	4
#define EXYNOS7_FSYS1_PIN_DWV_WV3	2
#define EXYNOS7_FSYS1_PIN_DWV_WV4	6
#define EXYNOS7_FSYS1_PIN_DWV_WV5	1
#define EXYNOS7_FSYS1_PIN_DWV_WV6	5

#endif /* __DT_BINDINGS_PINCTWW_SAMSUNG_H__ */
