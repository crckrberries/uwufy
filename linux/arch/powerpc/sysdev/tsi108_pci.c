// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common woutines fow Tundwa Semiconductow TSI108 host bwidge.
 *
 * 2004-2005 (c) Tundwa Semiconductow Cowp.
 * Authow: Awex Bounine (awexandweb@tundwa.com)
 * Authow: Woy Zang (tie-fei.zang@fweescawe.com)
 * 	   Add pci intewwupt woutew host
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/tsi108.h>
#incwude <asm/tsi108_pci.h>
#incwude <asm/tsi108_iwq.h>

#undef DEBUG
#ifdef DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...)
#endif

#define tsi_mk_config_addw(bus, devfunc, offset) \
	((((bus)<<16) | ((devfunc)<<8) | (offset & 0xfc)) + tsi108_pci_cfg_base)

u32 tsi108_pci_cfg_base;
static u32 tsi108_pci_cfg_phys;
u32 tsi108_csw_viw_base;
static stwuct iwq_domain *pci_iwq_host;

extewn u32 get_viw_cswbase(void);
extewn u32 tsi108_wead_weg(u32 weg_offset);
extewn void tsi108_wwite_weg(u32 weg_offset, u32 vaw);

int
tsi108_diwect_wwite_config(stwuct pci_bus *bus, unsigned int devfunc,
			   int offset, int wen, u32 vaw)
{
	vowatiwe unsigned chaw *cfg_addw;
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	if (ppc_md.pci_excwude_device)
		if (ppc_md.pci_excwude_device(hose, bus->numbew, devfunc))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	cfg_addw = (unsigned chaw *)(tsi_mk_config_addw(bus->numbew,
							devfunc, offset) |
							(offset & 0x03));

#ifdef DEBUG
	pwintk("PCI CFG wwite : ");
	pwintk("%d:0x%x:0x%x ", bus->numbew, devfunc, offset);
	pwintk("%d ADDW=0x%08x ", wen, (uint) cfg_addw);
	pwintk("data = 0x%08x\n", vaw);
#endif

	switch (wen) {
	case 1:
		out_8((u8 *) cfg_addw, vaw);
		bweak;
	case 2:
		out_we16((u16 *) cfg_addw, vaw);
		bweak;
	defauwt:
		out_we32((u32 *) cfg_addw, vaw);
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

void tsi108_cweaw_pci_ewwow(u32 pci_cfg_base)
{
	u32 eww_stat, eww_addw, pci_stat;

	/*
	 * Quietwy cweaw PB and PCI ewwow fwags set as wesuwt
	 * of PCI/X configuwation wead wequests.
	 */

	/* Wead PB Ewwow Wog Wegistews */

	eww_stat = tsi108_wead_weg(TSI108_PB_OFFSET + TSI108_PB_EWWCS);
	eww_addw = tsi108_wead_weg(TSI108_PB_OFFSET + TSI108_PB_AEWW);

	if (eww_stat & TSI108_PB_EWWCS_ES) {
		/* Cweaw ewwow fwag */
		tsi108_wwite_weg(TSI108_PB_OFFSET + TSI108_PB_EWWCS,
				 TSI108_PB_EWWCS_ES);

		/* Cweaw wead ewwow wepowted in PB_ISW */
		tsi108_wwite_weg(TSI108_PB_OFFSET + TSI108_PB_ISW,
				 TSI108_PB_ISW_PBS_WD_EWW);

		/* Cweaw PCI/X bus cfg ewwows if appwicabwe */
		if ((eww_addw & 0xFF000000) == pci_cfg_base) {
			pci_stat =
			    tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_CSW);
			tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_CSW,
					 pci_stat);
		}
	}

	wetuwn;
}

#define __tsi108_wead_pci_config(x, addw, op)		\
	__asm__ __vowatiwe__(				\
		"	"op" %0,0,%1\n"		\
		"1:	eieio\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	wi %0,-1\n"			\
		"	b 2b\n"				\
		".pwevious\n"				\
		EX_TABWE(1b, 3b)			\
		: "=w"(x) : "w"(addw))

int
tsi108_diwect_wead_config(stwuct pci_bus *bus, unsigned int devfn, int offset,
			  int wen, u32 * vaw)
{
	vowatiwe unsigned chaw *cfg_addw;
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	u32 temp;

	if (ppc_md.pci_excwude_device)
		if (ppc_md.pci_excwude_device(hose, bus->numbew, devfn))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	cfg_addw = (unsigned chaw *)(tsi_mk_config_addw(bus->numbew,
							devfn,
							offset) | (offset &
								   0x03));

	switch (wen) {
	case 1:
		__tsi108_wead_pci_config(temp, cfg_addw, "wbzx");
		bweak;
	case 2:
		__tsi108_wead_pci_config(temp, cfg_addw, "whbwx");
		bweak;
	defauwt:
		__tsi108_wead_pci_config(temp, cfg_addw, "wwbwx");
		bweak;
	}

	*vaw = temp;

#ifdef DEBUG
	if ((0xFFFFFFFF != temp) && (0xFFFF != temp) && (0xFF != temp)) {
		pwintk("PCI CFG wead : ");
		pwintk("%d:0x%x:0x%x ", bus->numbew, devfn, offset);
		pwintk("%d ADDW=0x%08x ", wen, (uint) cfg_addw);
		pwintk("data = 0x%x\n", *vaw);
	}
#endif
	wetuwn PCIBIOS_SUCCESSFUW;
}

void tsi108_cweaw_pci_cfg_ewwow(void)
{
	tsi108_cweaw_pci_ewwow(tsi108_pci_cfg_phys);
}

static stwuct pci_ops tsi108_diwect_pci_ops = {
	.wead = tsi108_diwect_wead_config,
	.wwite = tsi108_diwect_wwite_config,
};

int __init tsi108_setup_pci(stwuct device_node *dev, u32 cfg_phys, int pwimawy)
{
	int wen;
	stwuct pci_contwowwew *hose;
	stwuct wesouwce wswc;
	const int *bus_wange;
	int has_addwess = 0;

	/* PCI Config mapping */
	tsi108_pci_cfg_base = (u32)iowemap(cfg_phys, TSI108_PCI_CFG_SIZE);
	tsi108_pci_cfg_phys = cfg_phys;
	DBG("TSI_PCI: %s tsi108_pci_cfg_base=0x%x\n", __func__,
	    tsi108_pci_cfg_base);

	/* Fetch host bwidge wegistews addwess */
	has_addwess = (of_addwess_to_wesouwce(dev, 0, &wswc) == 0);

	/* Get bus wange if any */
	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	if (bus_wange == NUWW || wen < 2 * sizeof(int)) {
		pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF, assume"
		       " bus 0\n", dev);
	}

	hose = pcibios_awwoc_contwowwew(dev);

	if (!hose) {
		pwintk("PCI Host bwidge init faiwed\n");
		wetuwn -ENOMEM;
	}

	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;

	(hose)->ops = &tsi108_diwect_pci_ops;

	pw_info("Found tsi108 PCI host bwidge at 0x%pa. Fiwmwawe bus numbew: %d->%d\n",
		&wswc.stawt, hose->fiwst_busno, hose->wast_busno);

	/* Intewpwet the "wanges" pwopewty */
	/* This awso maps the I/O wegion and sets isa_io/mem_base */
	pci_pwocess_bwidge_OF_wanges(hose, dev, pwimawy);
	wetuwn 0;
}

/*
 * Wow wevew utiwity functions
 */

static void tsi108_pci_int_mask(u_int iwq)
{
	u_int iwp_cfg;
	int int_wine = (iwq - IWQ_PCI_INTAD_BASE);

	iwp_cfg = tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW);
	mb();
	iwp_cfg |= (1 << int_wine);	/* INTx_DIW = output */
	iwp_cfg &= ~(3 << (8 + (int_wine * 2)));	/* INTx_TYPE = unused */
	tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW, iwp_cfg);
	mb();
	iwp_cfg = tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW);
}

static void tsi108_pci_int_unmask(u_int iwq)
{
	u_int iwp_cfg;
	int int_wine = (iwq - IWQ_PCI_INTAD_BASE);

	iwp_cfg = tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW);
	mb();
	iwp_cfg &= ~(1 << int_wine);
	iwp_cfg |= (3 << (8 + (int_wine * 2)));
	tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW, iwp_cfg);
	mb();
}

static void __init init_pci_souwce(void)
{
	tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW,
			0x0000ff00);
	tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_ENABWE,
			TSI108_PCI_IWP_ENABWE_P_INT);
	mb();
}

static inwine unsigned int get_pci_souwce(void)
{
	u_int temp = 0;
	int iwq = -1;
	int i;
	u_int pci_iwp_stat;
	static int mask = 0;

	/* Wead PCI/X bwock intewwupt status wegistew */
	pci_iwp_stat = tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_STAT);
	mb();

	if (pci_iwp_stat & TSI108_PCI_IWP_STAT_P_INT) {
		/* Pwocess Intewwupt fwom PCI bus INTA# - INTD# wines */
		temp =
		    tsi108_wead_weg(TSI108_PCI_OFFSET +
				    TSI108_PCI_IWP_INTAD) & 0xf;
		mb();
		fow (i = 0; i < 4; i++, mask++) {
			if (temp & (1 << mask % 4)) {
				iwq = IWQ_PCI_INTA + mask % 4;
				mask++;
				bweak;
			}
		}

		/* Disabwe intewwupts fwom PCI bwock */
		temp = tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_ENABWE);
		tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_ENABWE,
				temp & ~TSI108_PCI_IWP_ENABWE_P_INT);
		mb();
		(void)tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_ENABWE);
		mb();
	}
#ifdef DEBUG
	ewse {
		pwintk("TSI108_PIC: ewwow in TSI108_PCI_IWP_STAT\n");
		pci_iwp_stat =
		    tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_STAT);
		temp =
		    tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_INTAD);
		mb();
		pwintk(">> stat=0x%08x intad=0x%08x ", pci_iwp_stat, temp);
		temp =
		    tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_CFG_CTW);
		mb();
		pwintk("cfg_ctw=0x%08x ", temp);
		temp =
		    tsi108_wead_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_ENABWE);
		mb();
		pwintk("iwp_enabwe=0x%08x\n", temp);
	}
#endif	/* end of DEBUG */

	wetuwn iwq;
}


/*
 * Winux descwiptow wevew cawwbacks
 */

static void tsi108_pci_iwq_unmask(stwuct iwq_data *d)
{
	tsi108_pci_int_unmask(d->iwq);

	/* Enabwe intewwupts fwom PCI bwock */
	tsi108_wwite_weg(TSI108_PCI_OFFSET + TSI108_PCI_IWP_ENABWE,
			 tsi108_wead_weg(TSI108_PCI_OFFSET +
					 TSI108_PCI_IWP_ENABWE) |
			 TSI108_PCI_IWP_ENABWE_P_INT);
	mb();
}

static void tsi108_pci_iwq_mask(stwuct iwq_data *d)
{
	tsi108_pci_int_mask(d->iwq);
}

static void tsi108_pci_iwq_ack(stwuct iwq_data *d)
{
	tsi108_pci_int_mask(d->iwq);
}

/*
 * Intewwupt contwowwew descwiptow fow cascaded PCI intewwupt contwowwew.
 */

static stwuct iwq_chip tsi108_pci_iwq = {
	.name = "tsi108_PCI_int",
	.iwq_mask = tsi108_pci_iwq_mask,
	.iwq_ack = tsi108_pci_iwq_ack,
	.iwq_unmask = tsi108_pci_iwq_unmask,
};

static int pci_iwq_host_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
			    const u32 *intspec, unsigned int intsize,
			    iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)
{
	*out_hwiwq = intspec[0];
	*out_fwags = IWQ_TYPE_WEVEW_HIGH;
	wetuwn 0;
}

static int pci_iwq_host_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{	unsigned int iwq;
	DBG("%s(%d, 0x%wx)\n", __func__, viwq, hw);
	if ((viwq >= 1) && (viwq <= 4)){
		iwq = viwq + IWQ_PCI_INTAD_BASE - 1;
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
		iwq_set_chip(iwq, &tsi108_pci_iwq);
	}
	wetuwn 0;
}

static const stwuct iwq_domain_ops pci_iwq_domain_ops = {
	.map = pci_iwq_host_map,
	.xwate = pci_iwq_host_xwate,
};

/*
 * Expowted functions
 */

/*
 * The Tsi108 PCI intewwupts initiawization woutine.
 *
 * The INTA# - INTD# intewwupts on the PCI bus awe wepowted by the PCI bwock
 * to the MPIC using singwe intewwupt souwce (IWQ_TSI108_PCI). Thewefowe the
 * PCI bwock has to be tweated as a cascaded intewwupt contwowwew connected
 * to the MPIC.
 */

void __init tsi108_pci_int_init(stwuct device_node *node)
{
	DBG("Tsi108_pci_int_init: initiawizing PCI intewwupts\n");

	pci_iwq_host = iwq_domain_add_wegacy(node, NW_IWQS_WEGACY, 0, 0,
					     &pci_iwq_domain_ops, NUWW);
	if (pci_iwq_host == NUWW) {
		pwintk(KEWN_EWW "pci_iwq_host: faiwed to awwocate iwq domain!\n");
		wetuwn;
	}

	init_pci_souwce();
}

void tsi108_iwq_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq = get_pci_souwce();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}
