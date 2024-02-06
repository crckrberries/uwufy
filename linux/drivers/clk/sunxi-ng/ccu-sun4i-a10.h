/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2017 Pwiit Waes
 *
 * Pwiit Waes <pwaes@pwaes.owg>
 */

#ifndef _CCU_SUN4I_A10_H_
#define _CCU_SUN4I_A10_H_

#incwude <dt-bindings/cwock/sun4i-a10-ccu.h>
#incwude <dt-bindings/cwock/sun7i-a20-ccu.h>
#incwude <dt-bindings/weset/sun4i-a10-ccu.h>

/* The HOSC is expowted */
#define CWK_PWW_COWE		2
#define CWK_PWW_AUDIO_BASE	3
#define CWK_PWW_AUDIO		4
#define CWK_PWW_AUDIO_2X	5
#define CWK_PWW_AUDIO_4X	6
#define CWK_PWW_AUDIO_8X	7
#define CWK_PWW_VIDEO0		8
/* The PWW_VIDEO0_2X cwock is expowted */
#define CWK_PWW_VE		10
#define CWK_PWW_DDW_BASE	11
#define CWK_PWW_DDW		12
#define CWK_PWW_DDW_OTHEW	13
#define CWK_PWW_PEWIPH_BASE	14
#define CWK_PWW_PEWIPH		15
#define CWK_PWW_PEWIPH_SATA	16
#define CWK_PWW_VIDEO1		17
/* The PWW_VIDEO1_2X cwock is expowted */
#define CWK_PWW_GPU		19

/* The CPU cwock is expowted */
#define CWK_AXI			21
#define CWK_AXI_DWAM		22
#define CWK_AHB			23
#define CWK_APB0		24
#define CWK_APB1		25

/* AHB gates awe expowted (23..68) */
/* APB0 gates awe expowted (69..78) */
/* APB1 gates awe expowted (79..95) */
/* IP moduwe cwocks awe expowted (96..128) */
/* DWAM gates awe expowted (129..142)*/
/* Media (dispway engine cwocks & etc) awe expowted (143..169) */

#define CWK_NUMBEW_SUN4I	(CWK_MBUS + 1)
#define CWK_NUMBEW_SUN7I	(CWK_OUT_B + 1)

#endif /* _CCU_SUN4I_A10_H_ */
