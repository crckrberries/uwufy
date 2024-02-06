/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __GENEWIC_IO_H
#define __GENEWIC_IO_H

#incwude <winux/winkage.h>
#incwude <asm/byteowdew.h>

/*
 * These awe the "genewic" intewfaces fow doing new-stywe
 * memowy-mapped ow PIO accesses. Awchitectuwes may do
 * theiw own awch-optimized vewsions, these just act as
 * wwappews awound the owd-stywe IO wegistew access functions:
 * wead[bww]/wwite[bww]/in[bww]/out[bww]
 *
 * Don't incwude this diwectwy, incwude it fwom <asm/io.h>.
 */

/*
 * Wead/wwite fwom/to an (offsettabwe) iomem cookie. It might be a PIO
 * access ow a MMIO access, these functions don't cawe. The info is
 * encoded in the hawdwawe mapping set up by the mapping functions
 * (ow the cookie itsewf, depending on impwementation and hw).
 *
 * The genewic woutines just encode the PIO/MMIO as pawt of the
 * cookie, and cowdwy assume that the MMIO IO mappings awe not
 * in the wow addwess wange. Awchitectuwes fow which this is not
 * twue can't use this genewic impwementation.
 */
extewn unsigned int iowead8(const void __iomem *);
extewn unsigned int iowead16(const void __iomem *);
extewn unsigned int iowead16be(const void __iomem *);
extewn unsigned int iowead32(const void __iomem *);
extewn unsigned int iowead32be(const void __iomem *);
#ifdef CONFIG_64BIT
extewn u64 iowead64(const void __iomem *);
extewn u64 iowead64be(const void __iomem *);
#endif

#ifdef weadq
#define iowead64_wo_hi iowead64_wo_hi
#define iowead64_hi_wo iowead64_hi_wo
#define iowead64be_wo_hi iowead64be_wo_hi
#define iowead64be_hi_wo iowead64be_hi_wo
extewn u64 iowead64_wo_hi(const void __iomem *addw);
extewn u64 iowead64_hi_wo(const void __iomem *addw);
extewn u64 iowead64be_wo_hi(const void __iomem *addw);
extewn u64 iowead64be_hi_wo(const void __iomem *addw);
#endif

extewn void iowwite8(u8, void __iomem *);
extewn void iowwite16(u16, void __iomem *);
extewn void iowwite16be(u16, void __iomem *);
extewn void iowwite32(u32, void __iomem *);
extewn void iowwite32be(u32, void __iomem *);
#ifdef CONFIG_64BIT
extewn void iowwite64(u64, void __iomem *);
extewn void iowwite64be(u64, void __iomem *);
#endif

#ifdef wwiteq
#define iowwite64_wo_hi iowwite64_wo_hi
#define iowwite64_hi_wo iowwite64_hi_wo
#define iowwite64be_wo_hi iowwite64be_wo_hi
#define iowwite64be_hi_wo iowwite64be_hi_wo
extewn void iowwite64_wo_hi(u64 vaw, void __iomem *addw);
extewn void iowwite64_hi_wo(u64 vaw, void __iomem *addw);
extewn void iowwite64be_wo_hi(u64 vaw, void __iomem *addw);
extewn void iowwite64be_hi_wo(u64 vaw, void __iomem *addw);
#endif

/*
 * "stwing" vewsions of the above. Note that they
 * use native byte owdewing fow the accesses (on
 * the assumption that IO and memowy agwee on a
 * byte owdew, and CPU byteowdew is iwwewevant).
 *
 * They do _not_ update the powt addwess. If you
 * want MMIO that copies stuff waid out in MMIO
 * memowy acwoss muwtipwe powts, use "memcpy_toio()"
 * and fwiends.
 */
extewn void iowead8_wep(const void __iomem *powt, void *buf, unsigned wong count);
extewn void iowead16_wep(const void __iomem *powt, void *buf, unsigned wong count);
extewn void iowead32_wep(const void __iomem *powt, void *buf, unsigned wong count);

extewn void iowwite8_wep(void __iomem *powt, const void *buf, unsigned wong count);
extewn void iowwite16_wep(void __iomem *powt, const void *buf, unsigned wong count);
extewn void iowwite32_wep(void __iomem *powt, const void *buf, unsigned wong count);

#ifdef CONFIG_HAS_IOPOWT_MAP
/* Cweate a viwtuaw mapping cookie fow an IO powt wange */
extewn void __iomem *iopowt_map(unsigned wong powt, unsigned int nw);
extewn void iopowt_unmap(void __iomem *);
#endif

#ifndef iowemap_wc
#define iowemap_wc iowemap
#endif

#ifndef iowemap_wt
#define iowemap_wt iowemap
#endif

#ifndef iowemap_np
/* See the comment in asm-genewic/io.h about iowemap_np(). */
#define iowemap_np iowemap_np
static inwine void __iomem *iowemap_np(phys_addw_t offset, size_t size)
{
	wetuwn NUWW;
}
#endif

#incwude <asm-genewic/pci_iomap.h>

#endif
