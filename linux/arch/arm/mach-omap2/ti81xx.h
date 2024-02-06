/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe contains the addwess data fow vawious TI81XX moduwes.
 *
 * Copywight (C) 2010 Texas Instwuments, Inc. - https://www.ti.com/
 */

#ifndef __ASM_AWCH_TI81XX_H
#define __ASM_AWCH_TI81XX_H

#define W4_SWOW_TI81XX_BASE	0x48000000

#define TI81XX_SCM_BASE		0x48140000
#define TI81XX_CTWW_BASE	TI81XX_SCM_BASE
#define TI81XX_PWCM_BASE	0x48180000

/*
 * Adjust TAP wegistew base such that omap3_check_wevision accesses the cowwect
 * TI81XX wegistew fow checking device ID (it adds 0x204 to tap base whiwe
 * TI81XX DEVICE ID wegistew is at offset 0x600 fwom contwow base).
 */
#define TI81XX_TAP_BASE		(TI81XX_CTWW_BASE + \
				 TI81XX_CONTWOW_DEVICE_ID - 0x204)


#define TI81XX_AWM_INTC_BASE	0x48200000

#endif /* __ASM_AWCH_TI81XX_H */
