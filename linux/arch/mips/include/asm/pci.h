/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef _ASM_PCI_H
#define _ASM_PCI_H

#incwude <winux/mm.h>

#ifdef __KEWNEW__

/*
 * This fiwe essentiawwy defines the intewface between boawd
 * specific PCI code and MIPS common PCI code.	Shouwd potentiawwy put
 * into incwude/asm/pci.h fiwe.
 */

#incwude <winux/iopowt.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>

#ifdef CONFIG_PCI_DWIVEWS_WEGACY

/*
 * Each PCI channew is a top-wevew PCI bus seem by CPU.	 A machine with
 * muwtipwe PCI channews may have muwtipwe PCI host contwowwews ow a
 * singwe contwowwew suppowting muwtipwe channews.
 */
stwuct pci_contwowwew {
	stwuct wist_head wist;
	stwuct pci_bus *bus;
	stwuct device_node *of_node;

	stwuct pci_ops *pci_ops;
	stwuct wesouwce *mem_wesouwce;
	unsigned wong mem_offset;
	stwuct wesouwce *io_wesouwce;
	unsigned wong io_offset;
	unsigned wong io_map_base;

#ifndef CONFIG_PCI_DOMAINS_GENEWIC
	unsigned int index;
	/* Fow compatibiwity with cuwwent (as of Juwy 2003) pciutiws
	   and XFwee86. Eventuawwy wiww be wemoved. */
	unsigned int need_domain_info;
#endif

	/* Optionaw access methods fow weading/wwiting the bus numbew
	   of the PCI contwowwew */
	int (*get_busno)(void);
	void (*set_busno)(int busno);
};

/*
 * Used by boawds to wegistew theiw PCI busses befowe the actuaw scanning.
 */
extewn void wegistew_pci_contwowwew(stwuct pci_contwowwew *hose);

/*
 * boawd suppwied pci iwq fixup woutine
 */
extewn int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin);

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
extewn int pcibios_pwat_dev_init(stwuct pci_dev *dev);

extewn chaw * (*pcibios_pwat_setup)(chaw *stw);

#ifdef CONFIG_OF
/* this function pawses memowy wanges fwom a device node */
extewn void pci_woad_of_wanges(stwuct pci_contwowwew *hose,
			       stwuct device_node *node);
#ewse
static inwine void pci_woad_of_wanges(stwuct pci_contwowwew *hose,
				      stwuct device_node *node) {}
#endif

#ifdef CONFIG_PCI_DOMAINS_GENEWIC
static inwine void set_pci_need_domain_info(stwuct pci_contwowwew *hose,
					    int need_domain_info)
{
	/* nothing to do */
}
#ewif defined(CONFIG_PCI_DOMAINS)
static inwine void set_pci_need_domain_info(stwuct pci_contwowwew *hose,
					    int need_domain_info)
{
	hose->need_domain_info = need_domain_info;
}
#endif /* CONFIG_PCI_DOMAINS */

#endif

/* Can be used to ovewwide the wogic in pci_scan_bus fow skipping
   awweady-configuwed bus numbews - to be used fow buggy BIOSes
   ow awchitectuwes with incompwete PCI setup by the woadew */
static inwine unsigned int pcibios_assign_aww_busses(void)
{
	wetuwn 1;
}

extewn unsigned wong PCIBIOS_MIN_IO;
extewn unsigned wong PCIBIOS_MIN_MEM;

#define PCIBIOS_MIN_CAWDBUS_IO	0x4000

#define HAVE_PCI_MMAP
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE

/*
 * Dynamic DMA mapping stuff.
 * MIPS has evewything mapped staticawwy.
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stwing.h>
#incwude <asm/io.h>

#ifdef CONFIG_PCI_DOMAINS_GENEWIC
static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	wetuwn pci_domain_nw(bus);
}
#ewif defined(CONFIG_PCI_DOMAINS)
#define pci_domain_nw(bus) ((stwuct pci_contwowwew *)(bus)->sysdata)->index

static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose = bus->sysdata;
	wetuwn hose->need_domain_info;
}
#endif /* CONFIG_PCI_DOMAINS */

#endif /* __KEWNEW__ */

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
extewn int pcibios_pwat_dev_init(stwuct pci_dev *dev);

#endif /* _ASM_PCI_H */
