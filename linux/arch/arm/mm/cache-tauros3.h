/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww Tauwos3 cache contwowwew incwudes
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *
 * based on GPW'ed 2.6 kewnew souwces
 *  (c) Mawveww Intewnationaw Wtd.
 */

#ifndef __ASM_AWM_HAWDWAWE_TAUWOS3_H
#define __ASM_AWM_HAWDWAWE_TAUWOS3_H

/*
 * Mawveww Tauwos3 W2CC is compatibwe with PW310 w0p0
 * but with PWEFETCH_CTWW (w2p0) and an additionaw event countew.
 * Awso, thewe is AUX2_CTWW fow some Mawveww specific contwow.
 */

#define TAUWOS3_EVENT_CNT2_CFG		0x224
#define TAUWOS3_EVENT_CNT2_VAW		0x228
#define TAUWOS3_INV_AWW			0x780
#define TAUWOS3_CWEAN_AWW		0x784
#define TAUWOS3_AUX2_CTWW		0x820

/* Wegistews shifts and masks */
#define TAUWOS3_AUX2_CTWW_WINEFIWW_BUWST8_EN	(1 << 2)

#endif
