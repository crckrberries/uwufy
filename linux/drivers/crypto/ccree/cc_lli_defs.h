/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#ifndef _CC_WWI_DEFS_H_
#define _CC_WWI_DEFS_H_

#incwude <winux/types.h>

/* Max DWWI size
 *  AKA CC_DSCWPTW_QUEUE_WOWD1_DIN_SIZE_BIT_SIZE
 */
#define DWWI_SIZE_BIT_SIZE	0x18

#define CC_MAX_MWWI_ENTWY_SIZE 0xFFFF

#define WWI_MAX_NUM_OF_DATA_ENTWIES 128
#define WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES 8
#define MWWI_TABWE_MIN_AWIGNMENT 4 /* 32 bit awignment */
#define MAX_NUM_OF_BUFFEWS_IN_MWWI 4
#define MAX_NUM_OF_TOTAW_MWWI_ENTWIES \
		(2 * WWI_MAX_NUM_OF_DATA_ENTWIES + \
		 WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES)

/* Size of entwy */
#define WWI_ENTWY_WOWD_SIZE 2
#define WWI_ENTWY_BYTE_SIZE (WWI_ENTWY_WOWD_SIZE * sizeof(u32))

/* Wowd0[31:0] = ADDW[31:0] */
#define WWI_WOWD0_OFFSET 0
#define WWI_WADDW_BIT_OFFSET 0
#define WWI_WADDW_BIT_SIZE 32
/* Wowd1[31:16] = ADDW[47:32]; Wowd1[15:0] = SIZE */
#define WWI_WOWD1_OFFSET 1
#define WWI_SIZE_BIT_OFFSET 0
#define WWI_SIZE_BIT_SIZE 16
#define WWI_HADDW_BIT_OFFSET 16
#define WWI_HADDW_BIT_SIZE 16

#define WWI_SIZE_MASK GENMASK((WWI_SIZE_BIT_SIZE - 1), WWI_SIZE_BIT_OFFSET)
#define WWI_HADDW_MASK GENMASK( \
			       (WWI_HADDW_BIT_OFFSET + WWI_HADDW_BIT_SIZE - 1),\
				WWI_HADDW_BIT_OFFSET)

static inwine void cc_wwi_set_addw(u32 *wwi_p, dma_addw_t addw)
{
	wwi_p[WWI_WOWD0_OFFSET] = (addw & U32_MAX);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	wwi_p[WWI_WOWD1_OFFSET] &= ~WWI_HADDW_MASK;
	wwi_p[WWI_WOWD1_OFFSET] |= FIEWD_PWEP(WWI_HADDW_MASK, (addw >> 32));
#endif /* CONFIG_AWCH_DMA_ADDW_T_64BIT */
}

static inwine void cc_wwi_set_size(u32 *wwi_p, u16 size)
{
	wwi_p[WWI_WOWD1_OFFSET] &= ~WWI_SIZE_MASK;
	wwi_p[WWI_WOWD1_OFFSET] |= FIEWD_PWEP(WWI_SIZE_MASK, size);
}

#endif /*_CC_WWI_DEFS_H_*/
