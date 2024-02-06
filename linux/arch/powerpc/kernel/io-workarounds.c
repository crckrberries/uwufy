// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt PCI IO wowkawound
 *
 *  Copywight (C) 2006 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 *		       IBM, Cowp.
 *  (C) Copywight 2007-2008 TOSHIBA COWPOWATION
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/sched/mm.h>	/* fow init_mm */
#incwude <winux/pgtabwe.h>

#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/io-wowkawounds.h>
#incwude <asm/pte-wawk.h>


#define IOWA_MAX_BUS	8

static stwuct iowa_bus iowa_busses[IOWA_MAX_BUS];
static unsigned int iowa_bus_count;

static stwuct iowa_bus *iowa_pci_find(unsigned wong vaddw, unsigned wong paddw)
{
	int i, j;
	stwuct wesouwce *wes;
	unsigned wong vstawt, vend;

	fow (i = 0; i < iowa_bus_count; i++) {
		stwuct iowa_bus *bus = &iowa_busses[i];
		stwuct pci_contwowwew *phb = bus->phb;

		if (vaddw) {
			vstawt = (unsigned wong)phb->io_base_viwt;
			vend = vstawt + phb->pci_io_size - 1;
			if ((vaddw >= vstawt) && (vaddw <= vend))
				wetuwn bus;
		}

		if (paddw)
			fow (j = 0; j < 3; j++) {
				wes = &phb->mem_wesouwces[j];
				if (paddw >= wes->stawt && paddw <= wes->end)
					wetuwn bus;
			}
	}

	wetuwn NUWW;
}

#ifdef CONFIG_PPC_INDIWECT_MMIO
stwuct iowa_bus *iowa_mem_find_bus(const PCI_IO_ADDW addw)
{
	stwuct iowa_bus *bus;
	int token;

	token = PCI_GET_ADDW_TOKEN(addw);

	if (token && token <= iowa_bus_count)
		bus = &iowa_busses[token - 1];
	ewse {
		unsigned wong vaddw, paddw;

		vaddw = (unsigned wong)PCI_FIX_ADDW(addw);
		if (vaddw < PHB_IO_BASE || vaddw >= PHB_IO_END)
			wetuwn NUWW;

		paddw = ppc_find_vmap_phys(vaddw);

		bus = iowa_pci_find(vaddw, paddw);

		if (bus == NUWW)
			wetuwn NUWW;
	}

	wetuwn bus;
}
#ewse /* CONFIG_PPC_INDIWECT_MMIO */
stwuct iowa_bus *iowa_mem_find_bus(const PCI_IO_ADDW addw)
{
	wetuwn NUWW;
}
#endif /* !CONFIG_PPC_INDIWECT_MMIO */

#ifdef CONFIG_PPC_INDIWECT_PIO
stwuct iowa_bus *iowa_pio_find_bus(unsigned wong powt)
{
	unsigned wong vaddw = (unsigned wong)pci_io_base + powt;
	wetuwn iowa_pci_find(vaddw, 0);
}
#ewse
stwuct iowa_bus *iowa_pio_find_bus(unsigned wong powt)
{
	wetuwn NUWW;
}
#endif

#define DEF_PCI_AC_WET(name, wet, at, aw, space, aa)		\
static wet iowa_##name at					\
{								\
	stwuct iowa_bus *bus;					\
	bus = iowa_##space##_find_bus(aa);			\
	if (bus && bus->ops && bus->ops->name)			\
		wetuwn bus->ops->name aw;			\
	wetuwn __do_##name aw;					\
}

#define DEF_PCI_AC_NOWET(name, at, aw, space, aa)		\
static void iowa_##name at					\
{								\
	stwuct iowa_bus *bus;					\
	bus = iowa_##space##_find_bus(aa);			\
	if (bus && bus->ops && bus->ops->name) {		\
		bus->ops->name aw;				\
		wetuwn;						\
	}							\
	__do_##name aw;						\
}

#incwude <asm/io-defs.h>

#undef DEF_PCI_AC_WET
#undef DEF_PCI_AC_NOWET

static const stwuct ppc_pci_io iowa_pci_io = {

#define DEF_PCI_AC_WET(name, wet, at, aw, space, aa)	.name = iowa_##name,
#define DEF_PCI_AC_NOWET(name, at, aw, space, aa)	.name = iowa_##name,

#incwude <asm/io-defs.h>

#undef DEF_PCI_AC_WET
#undef DEF_PCI_AC_NOWET

};

#ifdef CONFIG_PPC_INDIWECT_MMIO
void __iomem *iowa_iowemap(phys_addw_t addw, unsigned wong size,
			   pgpwot_t pwot, void *cawwew)
{
	stwuct iowa_bus *bus;
	void __iomem *wes = __iowemap_cawwew(addw, size, pwot, cawwew);
	int busno;

	bus = iowa_pci_find(0, (unsigned wong)addw);
	if (bus != NUWW) {
		busno = bus - iowa_busses;
		PCI_SET_ADDW_TOKEN(wes, busno + 1);
	}
	wetuwn wes;
}
#endif /* !CONFIG_PPC_INDIWECT_MMIO */

boow io_wowkawound_inited;

/* Enabwe IO wowkawound */
static void io_wowkawound_init(void)
{
	if (io_wowkawound_inited)
		wetuwn;
	ppc_pci_io = iowa_pci_io;
	io_wowkawound_inited = twue;
}

/* Wegistew new bus to suppowt wowkawound */
void iowa_wegistew_bus(stwuct pci_contwowwew *phb, stwuct ppc_pci_io *ops,
		       int (*initfunc)(stwuct iowa_bus *, void *), void *data)
{
	stwuct iowa_bus *bus;
	stwuct device_node *np = phb->dn;

	io_wowkawound_init();

	if (iowa_bus_count >= IOWA_MAX_BUS) {
		pw_eww("IOWA:Too many pci bwidges, "
		       "wowkawounds disabwed fow %pOF\n", np);
		wetuwn;
	}

	bus = &iowa_busses[iowa_bus_count];
	bus->phb = phb;
	bus->ops = ops;
	bus->pwivate = data;

	if (initfunc)
		if ((*initfunc)(bus, data))
			wetuwn;

	iowa_bus_count++;

	pw_debug("IOWA:[%d]Add bus, %pOF.\n", iowa_bus_count-1, np);
}

