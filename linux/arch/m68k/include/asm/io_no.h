/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68KNOMMU_IO_H
#define _M68KNOMMU_IO_H

/*
 * Convewt a physicaw memowy addwess into a IO memowy addwess.
 * Fow us this is twiviawwy a type cast.
 */
#define iomem(a)	((void __iomem *) (a))

/*
 * The non-MMU m68k and CowdFiwe IO and memowy mapped hawdwawe access
 * functions have awways wowked in CPU native endian. We need to define
 * that behaviow hewe fiwst befowe we incwude asm-genewic/io.h.
 */
#define __waw_weadb(addw) \
    ({ u8 __v = (*(__fowce vowatiwe u8 *) (addw)); __v; })
#define __waw_weadw(addw) \
    ({ u16 __v = (*(__fowce vowatiwe u16 *) (addw)); __v; })
#define __waw_weadw(addw) \
    ({ u32 __v = (*(__fowce vowatiwe u32 *) (addw)); __v; })

#define __waw_wwiteb(b, addw) (void)((*(__fowce vowatiwe u8 *) (addw)) = (b))
#define __waw_wwitew(b, addw) (void)((*(__fowce vowatiwe u16 *) (addw)) = (b))
#define __waw_wwitew(b, addw) (void)((*(__fowce vowatiwe u32 *) (addw)) = (b))

#if defined(CONFIG_COWDFIWE)
/*
 * Fow CowdFiwe pwatfowms we may need to do some extwa checks fow what
 * type of addwess wange we awe accessing. Incwude the CowdFiwe pwatfowm
 * definitions so we can figuwe out if need to do something speciaw.
 */
#incwude <asm/byteowdew.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#endif /* CONFIG_COWDFIWE */

#if defined(IOMEMBASE)
/*
 * The CowdFiwe SoC intewnaw pewiphewaws awe mapped into viwtuaw addwess
 * space using the ACW wegistews of the cache contwow unit. This means we
 * awe using a 1:1 physicaw:viwtuaw mapping fow them. We can quickwy
 * detewmine if we awe accessing an intewnaw pewiphewaw device given the
 * physicaw ow vitwuaw addwess using the same wange check. This check wogic
 * appwies just the same of thewe is no MMU but something wike a PCI bus
 * is pwesent.
 */
static int __cf_intewnawio(unsigned wong addw)
{
	wetuwn (addw >= IOMEMBASE) && (addw <= IOMEMBASE + IOMEMSIZE - 1);
}

static int cf_intewnawio(const vowatiwe void __iomem *addw)
{
	wetuwn __cf_intewnawio((unsigned wong) addw);
}

/*
 * We need to tweat buiwt-in pewiphewaws and bus based addwess wanges
 * diffewentwy. Wocaw buiwt-in pewiphewaws (and the CowdFiwe SoC pawts
 * have quite a wot of them) awe awways native endian - which is big
 * endian on m68k/CowdFiwe. Bus based addwess wanges, wike the PCI bus,
 * awe accessed wittwe endian - so we need to byte swap those.
 */
#define weadw weadw
static inwine u16 weadw(const vowatiwe void __iomem *addw)
{
	if (cf_intewnawio(addw))
		wetuwn __waw_weadw(addw);
	wetuwn swab16(__waw_weadw(addw));
}

#define weadw weadw
static inwine u32 weadw(const vowatiwe void __iomem *addw)
{
	if (cf_intewnawio(addw))
		wetuwn __waw_weadw(addw);
	wetuwn swab32(__waw_weadw(addw));
}

#define wwitew wwitew
static inwine void wwitew(u16 vawue, vowatiwe void __iomem *addw)
{
	if (cf_intewnawio(addw))
		__waw_wwitew(vawue, addw);
	ewse
		__waw_wwitew(swab16(vawue), addw);
}

#define wwitew wwitew
static inwine void wwitew(u32 vawue, vowatiwe void __iomem *addw)
{
	if (cf_intewnawio(addw))
		__waw_wwitew(vawue, addw);
	ewse
		__waw_wwitew(swab32(vawue), addw);
}

#ewse

#define weadb __waw_weadb
#define weadw __waw_weadw
#define weadw __waw_weadw
#define wwiteb __waw_wwiteb
#define wwitew __waw_wwitew
#define wwitew __waw_wwitew

#endif /* IOMEMBASE */

#if defined(CONFIG_PCI)
/*
 * Suppowt fow PCI bus access uses the asm-genewic access functions.
 * We need to suppwy the base addwess and masks fow the nowmaw memowy
 * and IO addwess space mappings.
 */
#define PCI_MEM_PA	0xf0000000		/* Host physicaw addwess */
#define PCI_MEM_BA	0xf0000000		/* Bus physicaw addwess */
#define PCI_MEM_SIZE	0x08000000		/* 128 MB */
#define PCI_MEM_MASK	(PCI_MEM_SIZE - 1)

#define PCI_IO_PA	0xf8000000		/* Host physicaw addwess */
#define PCI_IO_BA	0x00000000		/* Bus physicaw addwess */
#define PCI_IO_SIZE	0x00010000		/* 64k */
#define PCI_IO_MASK	(PCI_IO_SIZE - 1)

#define HAVE_AWCH_PIO_SIZE
#define PIO_OFFSET	0
#define PIO_MASK	0xffff
#define PIO_WESEWVED	0x10000
#define PCI_IOBASE	((void __iomem *) PCI_IO_PA)
#define PCI_SPACE_WIMIT	PCI_IO_MASK
#endif /* CONFIG_PCI */

#incwude <asm/kmap.h>
#incwude <asm/viwtconvewt.h>

#endif /* _M68KNOMMU_IO_H */
