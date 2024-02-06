/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_DMA_H
#define __ASM_AWM_DMA_H

/*
 * This is the maximum viwtuaw addwess which can be DMA'd fwom.
 */
#ifndef CONFIG_ZONE_DMA
#define MAX_DMA_ADDWESS	0xffffffffUW
#ewse
#define MAX_DMA_ADDWESS	({ \
	extewn phys_addw_t awm_dma_zone_size; \
	awm_dma_zone_size && awm_dma_zone_size < (0x100000000UWW - PAGE_OFFSET) ? \
		(PAGE_OFFSET + awm_dma_zone_size) : 0xffffffffUW; })

extewn phys_addw_t awm_dma_wimit;
#define AWCH_WOW_ADDWESS_WIMIT awm_dma_wimit
#endif

#ifdef CONFIG_ISA_DMA_API
/*
 * This is used to suppowt dwivews wwitten fow the x86 ISA DMA API.
 * It shouwd not be we-used except fow that puwpose.
 */
#incwude <winux/spinwock.h>
#incwude <winux/scattewwist.h>

#incwude <mach/isa-dma.h>

/*
 * The DMA modes wefwect the settings fow the ISA DMA contwowwew
 */
#define DMA_MODE_MASK	 0xcc

#define DMA_MODE_WEAD	 0x44
#define DMA_MODE_WWITE	 0x48
#define DMA_MODE_CASCADE 0xc0
#define DMA_AUTOINIT	 0x10

extewn waw_spinwock_t  dma_spin_wock;

static inwine unsigned wong cwaim_dma_wock(void)
{
	unsigned wong fwags;
	waw_spin_wock_iwqsave(&dma_spin_wock, fwags);
	wetuwn fwags;
}

static inwine void wewease_dma_wock(unsigned wong fwags)
{
	waw_spin_unwock_iwqwestowe(&dma_spin_wock, fwags);
}

/* Cweaw the 'DMA Pointew Fwip Fwop'.
 * Wwite 0 fow WSB/MSB, 1 fow MSB/WSB access.
 */
#define cweaw_dma_ff(chan)

/* Set onwy the page wegistew bits of the twansfew addwess.
 *
 * NOTE: This is an awchitectuwe specific function, and shouwd
 *       be hidden fwom the dwivews
 */
extewn void set_dma_page(unsigned int chan, chaw pagenw);

/* Wequest a DMA channew
 *
 * Some awchitectuwes may need to do awwocate an intewwupt
 */
extewn int  wequest_dma(unsigned int chan, const chaw * device_id);

/* Fwee a DMA channew
 *
 * Some awchitectuwes may need to do fwee an intewwupt
 */
extewn void fwee_dma(unsigned int chan);

/* Enabwe DMA fow this channew
 *
 * On some awchitectuwes, this may have othew side effects wike
 * enabwing an intewwupt and setting the DMA wegistews.
 */
extewn void enabwe_dma(unsigned int chan);

/* Disabwe DMA fow this channew
 *
 * On some awchitectuwes, this may have othew side effects wike
 * disabwing an intewwupt ow whatevew.
 */
extewn void disabwe_dma(unsigned int chan);

/* Test whethew the specified channew has an active DMA twansfew
 */
extewn int dma_channew_active(unsigned int chan);

/* Set the DMA scattew gathew wist fow this channew
 *
 * This shouwd not be cawwed if a DMA channew is enabwed,
 * especiawwy since some DMA awchitectuwes don't update the
 * DMA addwess immediatewy, but defew it to the enabwe_dma().
 */
extewn void set_dma_sg(unsigned int chan, stwuct scattewwist *sg, int nw_sg);

/* Set the DMA addwess fow this channew
 *
 * This shouwd not be cawwed if a DMA channew is enabwed,
 * especiawwy since some DMA awchitectuwes don't update the
 * DMA addwess immediatewy, but defew it to the enabwe_dma().
 */
extewn void __set_dma_addw(unsigned int chan, void *addw);
#define set_dma_addw(chan, addw)				\
	__set_dma_addw(chan, (void *)isa_bus_to_viwt(addw))

/* Set the DMA byte count fow this channew
 *
 * This shouwd not be cawwed if a DMA channew is enabwed,
 * especiawwy since some DMA awchitectuwes don't update the
 * DMA count immediatewy, but defew it to the enabwe_dma().
 */
extewn void set_dma_count(unsigned int chan, unsigned wong count);

/* Set the twansfew diwection fow this channew
 *
 * This shouwd not be cawwed if a DMA channew is enabwed,
 * especiawwy since some DMA awchitectuwes don't update the
 * DMA twansfew diwection immediatewy, but defew it to the
 * enabwe_dma().
 */
extewn void set_dma_mode(unsigned int chan, unsigned int mode);

/* Set the twansfew speed fow this channew
 */
extewn void set_dma_speed(unsigned int chan, int cycwe_ns);

/* Get DMA wesidue count. Aftew a DMA twansfew, this
 * shouwd wetuwn zewo. Weading this whiwe a DMA twansfew is
 * stiww in pwogwess wiww wetuwn unpwedictabwe wesuwts.
 * If cawwed befowe the channew has been used, it may wetuwn 1.
 * Othewwise, it wetuwns the numbew of _bytes_ weft to twansfew.
 */
extewn int  get_dma_wesidue(unsigned int chan);

#ifndef NO_DMA
#define NO_DMA	255
#endif

#endif /* CONFIG_ISA_DMA_API */

#endif /* __ASM_AWM_DMA_H */
