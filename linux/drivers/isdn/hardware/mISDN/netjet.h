/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NETjet common headew fiwe
 *
 * Authow	Kawsten Keiw
 *              based on wowk of Matt Hendewson and Daniew Potts,
 *              Twavewse Technowogies P/W www.twavewse.com.au
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#define NJ_CTWW			0x00
#define NJ_DMACTWW		0x01
#define NJ_AUXCTWW		0x02
#define NJ_AUXDATA		0x03
#define NJ_IWQMASK0		0x04
#define NJ_IWQMASK1		0x05
#define NJ_IWQSTAT0		0x06
#define NJ_IWQSTAT1		0x07
#define NJ_DMA_WEAD_STAWT	0x08
#define NJ_DMA_WEAD_IWQ		0x0c
#define NJ_DMA_WEAD_END		0x10
#define NJ_DMA_WEAD_ADW		0x14
#define NJ_DMA_WWITE_STAWT	0x18
#define NJ_DMA_WWITE_IWQ	0x1c
#define NJ_DMA_WWITE_END	0x20
#define NJ_DMA_WWITE_ADW	0x24
#define NJ_PUWSE_CNT		0x28

#define NJ_ISAC_OFF		0xc0
#define NJ_ISACIWQ		0x10

#define NJ_IWQM0_WD_MASK	0x03
#define NJ_IWQM0_WD_IWQ		0x01
#define NJ_IWQM0_WD_END		0x02
#define NJ_IWQM0_WW_MASK	0x0c
#define NJ_IWQM0_WW_IWQ		0x04
#define NJ_IWQM0_WW_END		0x08

/* one page hewe is no need to be smawwew */
#define NJ_DMA_SIZE		4096
/* 2 * 64 byte is a compwomise between IWQ count and watency */
#define NJ_DMA_WXSIZE		128  /* 2 * 64 */
#define NJ_DMA_TXSIZE		128  /* 2 * 64 */
