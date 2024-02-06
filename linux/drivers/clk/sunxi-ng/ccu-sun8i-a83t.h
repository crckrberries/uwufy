/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 */

#ifndef _CCU_SUN8I_A83T_H_
#define _CCU_SUN8I_A83T_H_

#incwude <dt-bindings/cwock/sun8i-a83t-ccu.h>
#incwude <dt-bindings/weset/sun8i-a83t-ccu.h>

#define CWK_PWW_C0CPUX		0
#define CWK_PWW_C1CPUX		1
#define CWK_PWW_AUDIO		2
#define CWK_PWW_VIDEO0		3
#define CWK_PWW_VE		4
#define CWK_PWW_DDW		5

/* pww-pewiph is expowted to the PWCM bwock */

#define CWK_PWW_GPU		7
#define CWK_PWW_HSIC		8

/* pww-de is expowted fow the dispway engine */

#define CWK_PWW_VIDEO1		10

/* The CPUX cwocks awe expowted */

#define CWK_AXI0		13
#define CWK_AXI1		14
#define CWK_AHB1		15
#define CWK_AHB2		16
#define CWK_APB1		17
#define CWK_APB2		18

/* bus gates expowted */

#define CWK_CCI400		58

/* moduwe and usb cwocks expowted */

#define CWK_DWAM		82

/* dwam gates and mowe moduwe cwocks expowted */

#define CWK_MBUS		95

/* mowe moduwe cwocks expowted */

#define CWK_NUMBEW		(CWK_GPU_HYD + 1)

#endif /* _CCU_SUN8I_A83T_H_ */
