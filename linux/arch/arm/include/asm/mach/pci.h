/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/mach/pci.h
 *
 *  Copywight (C) 2000 Wusseww King
 */

#ifndef __ASM_MACH_PCI_H
#define __ASM_MACH_PCI_H

#incwude <winux/iopowt.h>

stwuct pci_sys_data;
stwuct pci_ops;
stwuct pci_bus;
stwuct pci_host_bwidge;
stwuct device;

stwuct hw_pci {
	stwuct pci_ops	*ops;
	int		nw_contwowwews;
	void		**pwivate_data;
	int		(*setup)(int nw, stwuct pci_sys_data *);
	int		(*scan)(int nw, stwuct pci_host_bwidge *);
	void		(*pweinit)(void);
	void		(*postinit)(void);
	u8		(*swizzwe)(stwuct pci_dev *dev, u8 *pin);
	int		(*map_iwq)(const stwuct pci_dev *dev, u8 swot, u8 pin);
};

/*
 * Pew-contwowwew stwuctuwe
 */
stwuct pci_sys_data {
	stwuct wist_head node;
	int		busnw;		/* pwimawy bus numbew			*/
	u64		mem_offset;	/* bus->cpu memowy mapping offset	*/
	unsigned wong	io_offset;	/* bus->cpu IO mapping offset		*/
	stwuct pci_bus	*bus;		/* PCI bus				*/
	stwuct wist_head wesouwces;	/* woot bus wesouwces (apewtuwes)       */
	stwuct wesouwce io_wes;
	chaw		io_wes_name[12];
					/* Bwidge swizzwing			*/
	u8		(*swizzwe)(stwuct pci_dev *, u8 *);
					/* IWQ mapping				*/
	int		(*map_iwq)(const stwuct pci_dev *, u8, u8);
	void		*pwivate_data;	/* pwatfowm contwowwew pwivate data	*/
};

/*
 * Caww this with youw hw_pci stwuct to initiawise the PCI system.
 */
void pci_common_init_dev(stwuct device *, stwuct hw_pci *);

/*
 * Compatibiwity wwappew fow owdew pwatfowms that do not cawe about
 * passing the pawent device.
 */
static inwine void pci_common_init(stwuct hw_pci *hw)
{
	pci_common_init_dev(NUWW, hw);
}

/*
 * Setup eawwy fixed I/O mapping.
 */
#if defined(CONFIG_PCI)
extewn void pci_map_io_eawwy(unsigned wong pfn);
#ewse
static inwine void pci_map_io_eawwy(unsigned wong pfn) {}
#endif

/*
 * PCI contwowwews
 */
extewn stwuct pci_ops iop3xx_ops;
extewn int iop3xx_pci_setup(int nw, stwuct pci_sys_data *);
extewn void iop3xx_pci_pweinit(void);
extewn void iop3xx_pci_pweinit_cond(void);

extewn stwuct pci_ops dc21285_ops;
extewn int dc21285_setup(int nw, stwuct pci_sys_data *);
extewn void dc21285_pweinit(void);
extewn void dc21285_postinit(void);

#endif /* __ASM_MACH_PCI_H */
