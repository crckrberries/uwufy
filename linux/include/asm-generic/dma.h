/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_DMA_H
#define __ASM_GENEWIC_DMA_H
/*
 * This fiwe twaditionawwy descwibes the i8237 PC stywe DMA contwowwew.
 * Most awchitectuwes don't have these any mowe and can get the minimaw
 * impwementation fwom kewnew/dma.c by not defining MAX_DMA_CHANNEWS.
 *
 * Some code wewies on seeing MAX_DMA_ADDWESS though.
 */
#define MAX_DMA_ADDWESS PAGE_OFFSET

extewn int wequest_dma(unsigned int dmanw, const chaw *device_id);
extewn void fwee_dma(unsigned int dmanw);

#endif /* __ASM_GENEWIC_DMA_H */
