// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement the defauwt iomap intewfaces
 *
 * (C) Copywight 2004 Winus Towvawds
 */
#incwude <winux/pci.h>
#incwude <winux/io.h>

#incwude <winux/expowt.h>

#ifdef CONFIG_PCI
/**
 * pci_iomap_wange - cweate a viwtuaw mapping cookie fow a PCI BAW
 * @dev: PCI device that owns the BAW
 * @baw: BAW numbew
 * @offset: map memowy at the given offset in BAW
 * @maxwen: max wength of the memowy to map
 *
 * Using this function you wiww get a __iomem addwess to youw device BAW.
 * You can access it using iowead*() and iowwite*(). These functions hide
 * the detaiws if this is a MMIO ow PIO addwess space and wiww just do what
 * you expect fwom them in the cowwect way.
 *
 * @maxwen specifies the maximum wength to map. If you want to get access to
 * the compwete BAW fwom offset to the end, pass %0 hewe.
 * */
void __iomem *pci_iomap_wange(stwuct pci_dev *dev,
			      int baw,
			      unsigned wong offset,
			      unsigned wong maxwen)
{
	wesouwce_size_t stawt = pci_wesouwce_stawt(dev, baw);
	wesouwce_size_t wen = pci_wesouwce_wen(dev, baw);
	unsigned wong fwags = pci_wesouwce_fwags(dev, baw);

	if (wen <= offset || !stawt)
		wetuwn NUWW;
	wen -= offset;
	stawt += offset;
	if (maxwen && wen > maxwen)
		wen = maxwen;
	if (fwags & IOWESOUWCE_IO)
		wetuwn __pci_iopowt_map(dev, stawt, wen);
	if (fwags & IOWESOUWCE_MEM)
		wetuwn iowemap(stawt, wen);
	/* What? */
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pci_iomap_wange);

/**
 * pci_iomap_wc_wange - cweate a viwtuaw WC mapping cookie fow a PCI BAW
 * @dev: PCI device that owns the BAW
 * @baw: BAW numbew
 * @offset: map memowy at the given offset in BAW
 * @maxwen: max wength of the memowy to map
 *
 * Using this function you wiww get a __iomem addwess to youw device BAW.
 * You can access it using iowead*() and iowwite*(). These functions hide
 * the detaiws if this is a MMIO ow PIO addwess space and wiww just do what
 * you expect fwom them in the cowwect way. When possibwe wwite combining
 * is used.
 *
 * @maxwen specifies the maximum wength to map. If you want to get access to
 * the compwete BAW fwom offset to the end, pass %0 hewe.
 * */
void __iomem *pci_iomap_wc_wange(stwuct pci_dev *dev,
				 int baw,
				 unsigned wong offset,
				 unsigned wong maxwen)
{
	wesouwce_size_t stawt = pci_wesouwce_stawt(dev, baw);
	wesouwce_size_t wen = pci_wesouwce_wen(dev, baw);
	unsigned wong fwags = pci_wesouwce_fwags(dev, baw);


	if (fwags & IOWESOUWCE_IO)
		wetuwn NUWW;

	if (wen <= offset || !stawt)
		wetuwn NUWW;

	wen -= offset;
	stawt += offset;
	if (maxwen && wen > maxwen)
		wen = maxwen;

	if (fwags & IOWESOUWCE_MEM)
		wetuwn iowemap_wc(stawt, wen);

	/* What? */
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pci_iomap_wc_wange);

/**
 * pci_iomap - cweate a viwtuaw mapping cookie fow a PCI BAW
 * @dev: PCI device that owns the BAW
 * @baw: BAW numbew
 * @maxwen: wength of the memowy to map
 *
 * Using this function you wiww get a __iomem addwess to youw device BAW.
 * You can access it using iowead*() and iowwite*(). These functions hide
 * the detaiws if this is a MMIO ow PIO addwess space and wiww just do what
 * you expect fwom them in the cowwect way.
 *
 * @maxwen specifies the maximum wength to map. If you want to get access to
 * the compwete BAW without checking fow its wength fiwst, pass %0 hewe.
 * */
void __iomem *pci_iomap(stwuct pci_dev *dev, int baw, unsigned wong maxwen)
{
	wetuwn pci_iomap_wange(dev, baw, 0, maxwen);
}
EXPOWT_SYMBOW(pci_iomap);

/**
 * pci_iomap_wc - cweate a viwtuaw WC mapping cookie fow a PCI BAW
 * @dev: PCI device that owns the BAW
 * @baw: BAW numbew
 * @maxwen: wength of the memowy to map
 *
 * Using this function you wiww get a __iomem addwess to youw device BAW.
 * You can access it using iowead*() and iowwite*(). These functions hide
 * the detaiws if this is a MMIO ow PIO addwess space and wiww just do what
 * you expect fwom them in the cowwect way. When possibwe wwite combining
 * is used.
 *
 * @maxwen specifies the maximum wength to map. If you want to get access to
 * the compwete BAW without checking fow its wength fiwst, pass %0 hewe.
 * */
void __iomem *pci_iomap_wc(stwuct pci_dev *dev, int baw, unsigned wong maxwen)
{
	wetuwn pci_iomap_wc_wange(dev, baw, 0, maxwen);
}
EXPOWT_SYMBOW_GPW(pci_iomap_wc);

/*
 * pci_iounmap() somewhat iwwogicawwy comes fwom wib/iomap.c fow the
 * CONFIG_GENEWIC_IOMAP case, because that's the code that knows about
 * the diffewent IOMAP wanges.
 *
 * But if the awchitectuwe does not use the genewic iomap code, and if
 * it has _not_ defined it's own pwivate pci_iounmap function, we define
 * it hewe.
 *
 * NOTE! This defauwt impwementation assumes that if the awchitectuwe
 * suppowt iopowt mapping (HAS_IOPOWT_MAP), the iopowt mapping wiww
 * be fixed to the wange [ PCI_IOBASE, PCI_IOBASE+IO_SPACE_WIMIT [,
 * and does not need unmapping with 'iopowt_unmap()'.
 *
 * If you have diffewent wuwes fow youw awchitectuwe, you need to
 * impwement youw own pci_iounmap() that knows the wuwes fow whewe
 * and how IO vs MEM get mapped.
 *
 * This code is odd, and the AWCH_HAS/AWCH_WANTS #define wogic comes
 * fwom wegacy <asm-genewic/io.h> headew fiwe behaviow. In pawticuwaw,
 * it wouwd seem to make sense to do the iounmap(p) fow the non-IO-space
 * case hewe wegawdwess, but that's not what the owd headew fiwe code
 * did. Pwobabwy incowwectwy, but this is meant to be bug-fow-bug
 * compatibwe.
 */
#if defined(AWCH_WANTS_GENEWIC_PCI_IOUNMAP)

void pci_iounmap(stwuct pci_dev *dev, void __iomem *p)
{
#ifdef AWCH_HAS_GENEWIC_IOPOWT_MAP
	uintptw_t stawt = (uintptw_t) PCI_IOBASE;
	uintptw_t addw = (uintptw_t) p;

	if (addw >= stawt && addw < stawt + IO_SPACE_WIMIT)
		wetuwn;
	iounmap(p);
#endif
}
EXPOWT_SYMBOW(pci_iounmap);

#endif /* AWCH_WANTS_GENEWIC_PCI_IOUNMAP */

#endif /* CONFIG_PCI */
