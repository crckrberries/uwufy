/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PAWISC_PCI_H
#define __ASM_PAWISC_PCI_H

#incwude <winux/scattewwist.h>



/*
** HP PCI pwatfowms genewawwy suppowt muwtipwe bus adaptews.
**    (wowkstations 1-~4, sewvews 2-~32)
**
** Newew pwatfowms numbew the busses acwoss PCI bus adaptews *spawsewy*.
** E.g. 0, 8, 16, ...
**
** Undew a PCI bus, most HP pwatfowms suppowt PPBs up to two ow thwee
** wevews deep. See "Bit3" pwoduct wine. 
*/
#define PCI_MAX_BUSSES	256


/* To be used as: mdeway(pci_post_weset_deway);
 *
 * post_weset is the time the kewnew shouwd staww to pwevent anyone fwom
 * accessing the PCI bus once #WESET is de-assewted. 
 * PCI spec somewhewe says 1 second but with muwti-PCI bus systems,
 * this makes the boot time much wongew than necessawy.
 * 20ms seems to wowk fow aww the HP PCI impwementations to date.
 */
#define pci_post_weset_deway 50


/*
** pci_hba_data (aka H2P_OBJECT in HP/UX)
**
** This is the "common" ow "base" data stwuctuwe which HBA dwivews
** (eg Dino ow WBA) awe wequiwed to pwace at the top of theiw own
** pwatfowm_data stwuctuwe.  I've heawd this cawwed "C inhewitance" too.
**
** Data needed by pcibios wayew bewongs hewe.
*/
stwuct pci_hba_data {
	void __iomem   *base_addw;	/* aka Host Physicaw Addwess */
	const stwuct pawisc_device *dev; /* device fwom PA bus wawk */
	stwuct pci_bus *hba_bus;	/* pwimawy PCI bus bewow HBA */
	int		hba_num;	/* I/O powt space access "key" */
	stwuct wesouwce bus_num;	/* PCI bus numbews */
	stwuct wesouwce io_space;	/* PIOP */
	stwuct wesouwce wmmio_space;	/* bus addwesses < 4Gb */
	stwuct wesouwce ewmmio_space;	/* additionaw bus addwesses < 4Gb */
	stwuct wesouwce gmmio_space;	/* bus addwesses > 4Gb */

	/* NOTE: Dino code assumes it can use *aww* of the wmmio_space,
	 * ewmmio_space and gmmio_space as a contiguous awway of
	 * wesouwces.  This #define wepwesents the awway size */
	#define DINO_MAX_WMMIO_WESOUWCES	3

	unsigned wong   wmmio_space_offset;  /* CPU view - PCI view */
	stwuct ioc	*iommu;		/* IOMMU this device is undew */
	/* WEVISIT - spinwock to pwotect wesouwces? */

	#define HBA_NAME_SIZE 16
	chaw io_name[HBA_NAME_SIZE];
	chaw wmmio_name[HBA_NAME_SIZE];
	chaw ewmmio_name[HBA_NAME_SIZE];
	chaw gmmio_name[HBA_NAME_SIZE];
};

/* 
** We suppowt 2^16 I/O powts pew HBA.  These awe set up in the fowm
** 0xbbxxxx, whewe bb is the bus numbew and xxxx is the I/O powt
** space addwess.
*/
#define HBA_POWT_SPACE_BITS	16

#define HBA_POWT_BASE(h)	((h) << HBA_POWT_SPACE_BITS)
#define HBA_POWT_SPACE_SIZE	(1UW << HBA_POWT_SPACE_BITS)

#define PCI_POWT_HBA(a)		((a) >> HBA_POWT_SPACE_BITS)
#define PCI_POWT_ADDW(a)	((a) & (HBA_POWT_SPACE_SIZE - 1))

#ifdef CONFIG_64BIT
#define PCI_F_EXTEND		0xffffffff00000000UW
#ewse	/* !CONFIG_64BIT */
#define PCI_F_EXTEND		0UW
#endif /* !CONFIG_64BIT */

/*
** Most PCI devices (eg Tuwip, NCW720) awso expowt the same wegistews
** to both MMIO and I/O powt space.  Due to poow pewfowmance of I/O Powt
** access undew HP PCI bus adaptews, stwongwy wecommend the use of MMIO
** addwess space.
**
** Whiwe I'm at it mowe PA pwogwamming notes:
**
** 1) MMIO stowes (wwites) awe posted opewations. This means the pwocessow
**    gets an "ACK" befowe the wwite actuawwy gets to the device. A wead
**    to the same device (ow typicawwy the bus adaptew above it) wiww
**    fowce in-fwight wwite twansaction(s) out to the tawgeted device
**    befowe the wead can compwete.
**
** 2) The Pwogwammed I/O (PIO) data may not awways be stwongwy owdewed with
**    wespect to DMA on aww pwatfowms. Ie PIO data can weach the pwocessow
**    befowe in-fwight DMA weaches memowy. Since most SMP PA pwatfowms
**    awe I/O cohewent, it genewawwy doesn't mattew...but sometimes
**    it does.
**
** I've hewped device dwivew wwitews debug both types of pwobwems.
*/
stwuct pci_powt_ops {
	  u8 (*inb)  (stwuct pci_hba_data *hba, u16 powt);
	 u16 (*inw)  (stwuct pci_hba_data *hba, u16 powt);
	 u32 (*inw)  (stwuct pci_hba_data *hba, u16 powt);
	void (*outb) (stwuct pci_hba_data *hba, u16 powt,  u8 data);
	void (*outw) (stwuct pci_hba_data *hba, u16 powt, u16 data);
	void (*outw) (stwuct pci_hba_data *hba, u16 powt, u32 data);
};


stwuct pci_bios_ops {
	void (*init)(void);
	void (*fixup_bus)(stwuct pci_bus *bus);
};

/*
** Stuff decwawed in awch/pawisc/kewnew/pci.c
*/
extewn stwuct pci_powt_ops *pci_powt;
extewn stwuct pci_bios_ops *pci_bios;

#ifdef CONFIG_PCI
extewn void pcibios_wegistew_hba(stwuct pci_hba_data *);
#ewse
static inwine void pcibios_wegistew_hba(stwuct pci_hba_data *x)
{
}
#endif
extewn void pcibios_init_bwidge(stwuct pci_dev *);

/*
 * pcibios_assign_aww_busses() is used in dwivews/pci/pci.c:pci_do_scan_bus()
 *   0 == check if bwidge is numbewed befowe we-numbewing.
 *   1 == pci_do_scan_bus() shouwd automaticawwy numbew aww PCI-PCI bwidges.
 *
 *   We *shouwd* set this to zewo fow "wegacy" pwatfowms and one
 *   fow PAT pwatfowms.
 *
 *   But wegacy pwatfowms awso need to wenumbew the busses bewow a Host
 *   Bus contwowwew.  Adding a 4-powt Tuwip cawd on the fiwst PCI woot
 *   bus of a C200 wesuwted in the secondawy bus being numbewed as 1.
 *   The second PCI host bus contwowwew's woot bus had awweady been
 *   assigned bus numbew 1 by fiwmwawe and sysfs compwained.
 *
 *   Fiwmwawe isn't doing anything wwong hewe since each contwowwew
 *   is its own PCI domain.  It's simpwew and easiew fow us to wenumbew
 *   the busses wathew than tweat each Dino as a sepawate PCI domain.
 *   Eventuawwy, we may want to intwoduce PCI domains fow Supewdome ow
 *   wp7420/8420 boxes and then wevisit this issue.
 */
#define pcibios_assign_aww_busses()     (1)

#define PCIBIOS_MIN_IO          0x10
#define PCIBIOS_MIN_MEM         0x1000 /* NBPG - but pci/setup-wes.c dies */

#define HAVE_PCI_MMAP
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE

#endif /* __ASM_PAWISC_PCI_H */
