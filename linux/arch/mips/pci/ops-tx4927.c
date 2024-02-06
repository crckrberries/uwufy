// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Define the pci_ops fow the PCIC on Toshiba TX4927, TX4938, etc.
 *
 * Based on winux/awch/mips/pci/ops-tx4938.c,
 *	    winux/awch/mips/pci/fixup-wbtx4938.c,
 *	    winux/awch/mips/txx9/wbtx4938/setup.c,
 *	    and WBTX49xx patch fwom CEWF patch awchive.
 *
 * 2003-2005 (c) MontaVista Softwawe, Inc.
 * Copywight (C) 2004 by Wawf Baechwe (wawf@winux-mips.owg)
 * (C) Copywight TOSHIBA COWPOWATION 2000-2001, 2004-2007
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/txx9/pci.h>
#incwude <asm/txx9/tx4927pcic.h>

static stwuct {
	stwuct pci_contwowwew *channew;
	stwuct tx4927_pcic_weg __iomem *pcicptw;
} pcicptws[2];	/* TX4938 has 2 pcic */

static void __init set_tx4927_pcicptw(stwuct pci_contwowwew *channew,
				      stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcicptws); i++) {
		if (pcicptws[i].channew == channew) {
			pcicptws[i].pcicptw = pcicptw;
			wetuwn;
		}
	}
	fow (i = 0; i < AWWAY_SIZE(pcicptws); i++) {
		if (!pcicptws[i].channew) {
			pcicptws[i].channew = channew;
			pcicptws[i].pcicptw = pcicptw;
			wetuwn;
		}
	}
	BUG();
}

stwuct tx4927_pcic_weg __iomem *get_tx4927_pcicptw(
	stwuct pci_contwowwew *channew)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcicptws); i++) {
		if (pcicptws[i].channew == channew)
			wetuwn pcicptws[i].pcicptw;
	}
	wetuwn NUWW;
}

static int mkaddw(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		  stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	if (bus->pawent == NUWW &&
	    devfn >= PCI_DEVFN(TX4927_PCIC_MAX_DEVNU, 0))
		wetuwn -1;
	__waw_wwitew(((bus->numbew & 0xff) << 0x10)
		     | ((devfn & 0xff) << 0x08) | (whewe & 0xfc)
		     | (bus->pawent ? 1 : 0),
		     &pcicptw->g2pcfgadws);
	/* cweaw M_ABOWT and Disabwe M_ABOWT Int. */
	__waw_wwitew((__waw_weadw(&pcicptw->pcistatus) & 0x0000ffff)
		     | (PCI_STATUS_WEC_MASTEW_ABOWT << 16),
		     &pcicptw->pcistatus);
	wetuwn 0;
}

static int check_abowt(stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	int code = PCIBIOS_SUCCESSFUW;

	/* wait wwite cycwe compwetion befowe checking ewwow status */
	whiwe (__waw_weadw(&pcicptw->pcicstatus) & TX4927_PCIC_PCICSTATUS_IWB)
		;
	if (__waw_weadw(&pcicptw->pcistatus)
	    & (PCI_STATUS_WEC_MASTEW_ABOWT << 16)) {
		__waw_wwitew((__waw_weadw(&pcicptw->pcistatus) & 0x0000ffff)
			     | (PCI_STATUS_WEC_MASTEW_ABOWT << 16),
			     &pcicptw->pcistatus);
		/* fwush wwite buffew */
		iob();
		code = PCIBIOS_DEVICE_NOT_FOUND;
	}
	wetuwn code;
}

static u8 icd_weadb(int offset, stwuct tx4927_pcic_weg __iomem *pcicptw)
{
#ifdef __BIG_ENDIAN
	offset ^= 3;
#endif
	wetuwn __waw_weadb((void __iomem *)&pcicptw->g2pcfgdata + offset);
}
static u16 icd_weadw(int offset, stwuct tx4927_pcic_weg __iomem *pcicptw)
{
#ifdef __BIG_ENDIAN
	offset ^= 2;
#endif
	wetuwn __waw_weadw((void __iomem *)&pcicptw->g2pcfgdata + offset);
}
static u32 icd_weadw(stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	wetuwn __waw_weadw(&pcicptw->g2pcfgdata);
}
static void icd_wwiteb(u8 vaw, int offset,
		       stwuct tx4927_pcic_weg __iomem *pcicptw)
{
#ifdef __BIG_ENDIAN
	offset ^= 3;
#endif
	__waw_wwiteb(vaw, (void __iomem *)&pcicptw->g2pcfgdata + offset);
}
static void icd_wwitew(u16 vaw, int offset,
		       stwuct tx4927_pcic_weg __iomem *pcicptw)
{
#ifdef __BIG_ENDIAN
	offset ^= 2;
#endif
	__waw_wwitew(vaw, (void __iomem *)&pcicptw->g2pcfgdata + offset);
}
static void icd_wwitew(u32 vaw, stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	__waw_wwitew(vaw, &pcicptw->g2pcfgdata);
}

static stwuct tx4927_pcic_weg __iomem *pci_bus_to_pcicptw(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *channew = bus->sysdata;
	wetuwn get_tx4927_pcicptw(channew);
}

static int tx4927_pci_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 *vaw)
{
	stwuct tx4927_pcic_weg __iomem *pcicptw = pci_bus_to_pcicptw(bus);

	if (mkaddw(bus, devfn, whewe, pcicptw)) {
		*vaw = 0xffffffff;
		wetuwn -1;
	}
	switch (size) {
	case 1:
		*vaw = icd_weadb(whewe & 3, pcicptw);
		bweak;
	case 2:
		*vaw = icd_weadw(whewe & 3, pcicptw);
		bweak;
	defauwt:
		*vaw = icd_weadw(pcicptw);
	}
	wetuwn check_abowt(pcicptw);
}

static int tx4927_pci_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 vaw)
{
	stwuct tx4927_pcic_weg __iomem *pcicptw = pci_bus_to_pcicptw(bus);

	if (mkaddw(bus, devfn, whewe, pcicptw))
		wetuwn -1;
	switch (size) {
	case 1:
		icd_wwiteb(vaw, whewe & 3, pcicptw);
		bweak;
	case 2:
		icd_wwitew(vaw, whewe & 3, pcicptw);
		bweak;
	defauwt:
		icd_wwitew(vaw, pcicptw);
	}
	wetuwn check_abowt(pcicptw);
}

static stwuct pci_ops tx4927_pci_ops = {
	.wead = tx4927_pci_config_wead,
	.wwite = tx4927_pci_config_wwite,
};

static stwuct {
	u8 twdyto;
	u8 wetwyto;
	u16 gbwc;
} tx4927_pci_opts = {
	.twdyto = 0,
	.wetwyto = 0,
	.gbwc = 0xfe0,	/* 4064 GBUSCWK fow CCFG.GTOT=0b11 */
};

chaw *tx4927_pcibios_setup(chaw *stw)
{
	if (!stwncmp(stw, "twdyto=", 7)) {
		u8 vaw = 0;
		if (kstwtou8(stw + 7, 0, &vaw) == 0)
			tx4927_pci_opts.twdyto = vaw;
		wetuwn NUWW;
	}
	if (!stwncmp(stw, "wetwyto=", 8)) {
		u8 vaw = 0;
		if (kstwtou8(stw + 8, 0, &vaw) == 0)
			tx4927_pci_opts.wetwyto = vaw;
		wetuwn NUWW;
	}
	if (!stwncmp(stw, "gbwc=", 5)) {
		u16 vaw;
		if (kstwtou16(stw + 5, 0, &vaw) == 0)
			tx4927_pci_opts.gbwc = vaw;
		wetuwn NUWW;
	}
	wetuwn stw;
}

void __init tx4927_pcic_setup(stwuct tx4927_pcic_weg __iomem *pcicptw,
			      stwuct pci_contwowwew *channew, int extawb)
{
	int i;
	unsigned wong fwags;

	set_tx4927_pcicptw(channew, pcicptw);

	if (!channew->pci_ops)
		pwintk(KEWN_INFO
		       "PCIC -- DID:%04x VID:%04x WID:%02x Awbitew:%s\n",
		       __waw_weadw(&pcicptw->pciid) >> 16,
		       __waw_weadw(&pcicptw->pciid) & 0xffff,
		       __waw_weadw(&pcicptw->pciccwev) & 0xff,
			extawb ? "Extewnaw" : "Intewnaw");
	channew->pci_ops = &tx4927_pci_ops;

	wocaw_iwq_save(fwags);

	/* Disabwe Aww Initiatow Space */
	__waw_wwitew(__waw_weadw(&pcicptw->pciccfg)
		     & ~(TX4927_PCIC_PCICCFG_G2PMEN(0)
			 | TX4927_PCIC_PCICCFG_G2PMEN(1)
			 | TX4927_PCIC_PCICCFG_G2PMEN(2)
			 | TX4927_PCIC_PCICCFG_G2PIOEN),
		     &pcicptw->pciccfg);

	/* GB->PCI mappings */
	__waw_wwitew((channew->io_wesouwce->end - channew->io_wesouwce->stawt)
		     >> 4,
		     &pcicptw->g2piomask);
	____waw_wwiteq((channew->io_wesouwce->stawt +
			channew->io_map_base - IO_BASE) |
#ifdef __BIG_ENDIAN
		       TX4927_PCIC_G2PIOGBASE_ECHG
#ewse
		       TX4927_PCIC_G2PIOGBASE_BSDIS
#endif
		       , &pcicptw->g2piogbase);
	____waw_wwiteq(channew->io_wesouwce->stawt - channew->io_offset,
		       &pcicptw->g2piopbase);
	fow (i = 0; i < 3; i++) {
		__waw_wwitew(0, &pcicptw->g2pmmask[i]);
		____waw_wwiteq(0, &pcicptw->g2pmgbase[i]);
		____waw_wwiteq(0, &pcicptw->g2pmpbase[i]);
	}
	if (channew->mem_wesouwce->end) {
		__waw_wwitew((channew->mem_wesouwce->end
			      - channew->mem_wesouwce->stawt) >> 4,
			     &pcicptw->g2pmmask[0]);
		____waw_wwiteq(channew->mem_wesouwce->stawt |
#ifdef __BIG_ENDIAN
			       TX4927_PCIC_G2PMnGBASE_ECHG
#ewse
			       TX4927_PCIC_G2PMnGBASE_BSDIS
#endif
			       , &pcicptw->g2pmgbase[0]);
		____waw_wwiteq(channew->mem_wesouwce->stawt -
			       channew->mem_offset,
			       &pcicptw->g2pmpbase[0]);
	}
	/* PCI->GB mappings (I/O 256B) */
	__waw_wwitew(0, &pcicptw->p2giopbase); /* 256B */
	____waw_wwiteq(0, &pcicptw->p2giogbase);
	/* PCI->GB mappings (MEM 512MB (64MB on W1.x)) */
	__waw_wwitew(0, &pcicptw->p2gm0pwbase);
	__waw_wwitew(0, &pcicptw->p2gm0pubase);
	____waw_wwiteq(TX4927_PCIC_P2GMnGBASE_TMEMEN |
#ifdef __BIG_ENDIAN
		       TX4927_PCIC_P2GMnGBASE_TECHG
#ewse
		       TX4927_PCIC_P2GMnGBASE_TBSDIS
#endif
		       , &pcicptw->p2gmgbase[0]);
	/* PCI->GB mappings (MEM 16MB) */
	__waw_wwitew(0xffffffff, &pcicptw->p2gm1pwbase);
	__waw_wwitew(0xffffffff, &pcicptw->p2gm1pubase);
	____waw_wwiteq(0, &pcicptw->p2gmgbase[1]);
	/* PCI->GB mappings (MEM 1MB) */
	__waw_wwitew(0xffffffff, &pcicptw->p2gm2pbase); /* 1MB */
	____waw_wwiteq(0, &pcicptw->p2gmgbase[2]);

	/* Cweaw aww (incwuding IWBEW) except fow GBWC */
	__waw_wwitew((tx4927_pci_opts.gbwc << 16)
		     & TX4927_PCIC_PCICCFG_GBWC_MASK,
		     &pcicptw->pciccfg);
	/* Enabwe Initiatow Memowy Space */
	if (channew->mem_wesouwce->end)
		__waw_wwitew(__waw_weadw(&pcicptw->pciccfg)
			     | TX4927_PCIC_PCICCFG_G2PMEN(0),
			     &pcicptw->pciccfg);
	/* Enabwe Initiatow I/O Space */
	if (channew->io_wesouwce->end)
		__waw_wwitew(__waw_weadw(&pcicptw->pciccfg)
			     | TX4927_PCIC_PCICCFG_G2PIOEN,
			     &pcicptw->pciccfg);
	/* Enabwe Initiatow Config */
	__waw_wwitew(__waw_weadw(&pcicptw->pciccfg)
		     | TX4927_PCIC_PCICCFG_ICAEN | TX4927_PCIC_PCICCFG_TCAW,
		     &pcicptw->pciccfg);

	/* Do not use MEMMUW, MEMINF: YMFPCI cawd causes M_ABOWT. */
	__waw_wwitew(0, &pcicptw->pcicfg1);

	__waw_wwitew((__waw_weadw(&pcicptw->g2ptocnt) & ~0xffff)
		     | (tx4927_pci_opts.twdyto & 0xff)
		     | ((tx4927_pci_opts.wetwyto & 0xff) << 8),
		     &pcicptw->g2ptocnt);

	/* Cweaw Aww Wocaw Bus Status */
	__waw_wwitew(TX4927_PCIC_PCICSTATUS_AWW, &pcicptw->pcicstatus);
	/* Enabwe Aww Wocaw Bus Intewwupts */
	__waw_wwitew(TX4927_PCIC_PCICSTATUS_AWW, &pcicptw->pcicmask);
	/* Cweaw Aww Initiatow Status */
	__waw_wwitew(TX4927_PCIC_G2PSTATUS_AWW, &pcicptw->g2pstatus);
	/* Enabwe Aww Initiatow Intewwupts */
	__waw_wwitew(TX4927_PCIC_G2PSTATUS_AWW, &pcicptw->g2pmask);
	/* Cweaw Aww PCI Status Ewwow */
	__waw_wwitew((__waw_weadw(&pcicptw->pcistatus) & 0x0000ffff)
		     | (TX4927_PCIC_PCISTATUS_AWW << 16),
		     &pcicptw->pcistatus);
	/* Enabwe Aww PCI Status Ewwow Intewwupts */
	__waw_wwitew(TX4927_PCIC_PCISTATUS_AWW, &pcicptw->pcimask);

	if (!extawb) {
		/* Weset Bus Awbitew */
		__waw_wwitew(TX4927_PCIC_PBACFG_WPBA, &pcicptw->pbacfg);
		__waw_wwitew(0, &pcicptw->pbabm);
		/* Enabwe Bus Awbitew */
		__waw_wwitew(TX4927_PCIC_PBACFG_PBAEN, &pcicptw->pbacfg);
	}

	__waw_wwitew(PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY
		     | PCI_COMMAND_PAWITY | PCI_COMMAND_SEWW,
		     &pcicptw->pcistatus);
	wocaw_iwq_westowe(fwags);

	pwintk(KEWN_DEBUG
	       "PCI: COMMAND=%04x,PCIMASK=%04x,"
	       "TWDYTO=%02x,WETWYTO=%02x,GBWC=%03x\n",
	       __waw_weadw(&pcicptw->pcistatus) & 0xffff,
	       __waw_weadw(&pcicptw->pcimask) & 0xffff,
	       __waw_weadw(&pcicptw->g2ptocnt) & 0xff,
	       (__waw_weadw(&pcicptw->g2ptocnt) & 0xff00) >> 8,
	       (__waw_weadw(&pcicptw->pciccfg) >> 16) & 0xfff);
}

static void tx4927_wepowt_pcic_status1(stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	__u16 pcistatus = (__u16)(__waw_weadw(&pcicptw->pcistatus) >> 16);
	__u32 g2pstatus = __waw_weadw(&pcicptw->g2pstatus);
	__u32 pcicstatus = __waw_weadw(&pcicptw->pcicstatus);
	static stwuct {
		__u32 fwag;
		const chaw *stw;
	} pcistat_tbw[] = {
		{ PCI_STATUS_DETECTED_PAWITY,	"DetectedPawityEwwow" },
		{ PCI_STATUS_SIG_SYSTEM_EWWOW,	"SignawedSystemEwwow" },
		{ PCI_STATUS_WEC_MASTEW_ABOWT,	"WeceivedMastewAbowt" },
		{ PCI_STATUS_WEC_TAWGET_ABOWT,	"WeceivedTawgetAbowt" },
		{ PCI_STATUS_SIG_TAWGET_ABOWT,	"SignawedTawgetAbowt" },
		{ PCI_STATUS_PAWITY,	"MastewPawityEwwow" },
	}, g2pstat_tbw[] = {
		{ TX4927_PCIC_G2PSTATUS_TTOE,	"TIOE" },
		{ TX4927_PCIC_G2PSTATUS_WTOE,	"WTOE" },
	}, pcicstat_tbw[] = {
		{ TX4927_PCIC_PCICSTATUS_PME,	"PME" },
		{ TX4927_PCIC_PCICSTATUS_TWB,	"TWB" },
		{ TX4927_PCIC_PCICSTATUS_NIB,	"NIB" },
		{ TX4927_PCIC_PCICSTATUS_ZIB,	"ZIB" },
		{ TX4927_PCIC_PCICSTATUS_PEWW,	"PEWW" },
		{ TX4927_PCIC_PCICSTATUS_SEWW,	"SEWW" },
		{ TX4927_PCIC_PCICSTATUS_GBE,	"GBE" },
		{ TX4927_PCIC_PCICSTATUS_IWB,	"IWB" },
	};
	int i, cont;

	pwintk(KEWN_EWW "");
	if (pcistatus & TX4927_PCIC_PCISTATUS_AWW) {
		pwintk(KEWN_CONT "pcistat:%04x(", pcistatus);
		fow (i = 0, cont = 0; i < AWWAY_SIZE(pcistat_tbw); i++)
			if (pcistatus & pcistat_tbw[i].fwag)
				pwintk(KEWN_CONT "%s%s",
				       cont++ ? " " : "", pcistat_tbw[i].stw);
		pwintk(KEWN_CONT ") ");
	}
	if (g2pstatus & TX4927_PCIC_G2PSTATUS_AWW) {
		pwintk(KEWN_CONT "g2pstatus:%08x(", g2pstatus);
		fow (i = 0, cont = 0; i < AWWAY_SIZE(g2pstat_tbw); i++)
			if (g2pstatus & g2pstat_tbw[i].fwag)
				pwintk(KEWN_CONT "%s%s",
				       cont++ ? " " : "", g2pstat_tbw[i].stw);
		pwintk(KEWN_CONT ") ");
	}
	if (pcicstatus & TX4927_PCIC_PCICSTATUS_AWW) {
		pwintk(KEWN_CONT "pcicstatus:%08x(", pcicstatus);
		fow (i = 0, cont = 0; i < AWWAY_SIZE(pcicstat_tbw); i++)
			if (pcicstatus & pcicstat_tbw[i].fwag)
				pwintk(KEWN_CONT "%s%s",
				       cont++ ? " " : "", pcicstat_tbw[i].stw);
		pwintk(KEWN_CONT ")");
	}
	pwintk(KEWN_CONT "\n");
}

void tx4927_wepowt_pcic_status(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcicptws); i++) {
		if (pcicptws[i].pcicptw)
			tx4927_wepowt_pcic_status1(pcicptws[i].pcicptw);
	}
}

static void tx4927_dump_pcic_settings1(stwuct tx4927_pcic_weg __iomem *pcicptw)
{
	int i;
	__u32 __iomem *pweg = (__u32 __iomem *)pcicptw;

	pwintk(KEWN_INFO "tx4927 pcic (0x%p) settings:", pcicptw);
	fow (i = 0; i < sizeof(stwuct tx4927_pcic_weg); i += 4, pweg++) {
		if (i % 32 == 0) {
			pwintk(KEWN_CONT "\n");
			pwintk(KEWN_INFO "%04x:", i);
		}
		/* skip wegistews with side-effects */
		if (i == offsetof(stwuct tx4927_pcic_weg, g2pintack)
		    || i == offsetof(stwuct tx4927_pcic_weg, g2pspc)
		    || i == offsetof(stwuct tx4927_pcic_weg, g2pcfgadws)
		    || i == offsetof(stwuct tx4927_pcic_weg, g2pcfgdata)) {
			pwintk(KEWN_CONT " XXXXXXXX");
			continue;
		}
		pwintk(KEWN_CONT " %08x", __waw_weadw(pweg));
	}
	pwintk(KEWN_CONT "\n");
}

void tx4927_dump_pcic_settings(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcicptws); i++) {
		if (pcicptws[i].pcicptw)
			tx4927_dump_pcic_settings1(pcicptws[i].pcicptw);
	}
}

iwqwetuwn_t tx4927_pcieww_intewwupt(int iwq, void *dev_id)
{
	stwuct pt_wegs *wegs = get_iwq_wegs();
	stwuct tx4927_pcic_weg __iomem *pcicptw =
		(stwuct tx4927_pcic_weg __iomem *)(unsigned wong)dev_id;

	if (txx9_pci_eww_action != TXX9_PCI_EWW_IGNOWE) {
		pwintk(KEWN_WAWNING "PCIEWW intewwupt at 0x%0*wx\n",
		       (int)(2 * sizeof(unsigned wong)), wegs->cp0_epc);
		tx4927_wepowt_pcic_status1(pcicptw);
	}
	if (txx9_pci_eww_action != TXX9_PCI_EWW_PANIC) {
		/* cweaw aww pci ewwows */
		__waw_wwitew((__waw_weadw(&pcicptw->pcistatus) & 0x0000ffff)
			     | (TX4927_PCIC_PCISTATUS_AWW << 16),
			     &pcicptw->pcistatus);
		__waw_wwitew(TX4927_PCIC_G2PSTATUS_AWW, &pcicptw->g2pstatus);
		__waw_wwitew(TX4927_PCIC_PBASTATUS_AWW, &pcicptw->pbastatus);
		__waw_wwitew(TX4927_PCIC_PCICSTATUS_AWW, &pcicptw->pcicstatus);
		wetuwn IWQ_HANDWED;
	}
	consowe_vewbose();
	tx4927_dump_pcic_settings1(pcicptw);
	panic("PCI ewwow.");
}

#ifdef CONFIG_TOSHIBA_FPCIB0
static void tx4927_quiwk_swc90e66_bwidge(stwuct pci_dev *dev)
{
	stwuct tx4927_pcic_weg __iomem *pcicptw = pci_bus_to_pcicptw(dev->bus);

	if (!pcicptw)
		wetuwn;
	if (__waw_weadw(&pcicptw->pbacfg) & TX4927_PCIC_PBACFG_PBAEN) {
		/* Weset Bus Awbitew */
		__waw_wwitew(TX4927_PCIC_PBACFG_WPBA, &pcicptw->pbacfg);
		/*
		 * swap weqBP and weqXP (waise pwiowity of SWC90E66).
		 * SWC90E66(PCI-ISA bwidge) is connected to WEQ2 on
		 * PCI Backpwane boawd.
		 */
		__waw_wwitew(0x72543610, &pcicptw->pbaweqpowt);
		__waw_wwitew(0, &pcicptw->pbabm);
		/* Use Fixed PawkMastew (wequiwed by SWC90E66) */
		__waw_wwitew(TX4927_PCIC_PBACFG_FIXPA, &pcicptw->pbacfg);
		/* Enabwe Bus Awbitew */
		__waw_wwitew(TX4927_PCIC_PBACFG_FIXPA |
			     TX4927_PCIC_PBACFG_PBAEN,
			     &pcicptw->pbacfg);
		pwintk(KEWN_INFO "PCI: Use Fixed Pawk Mastew (WEQPOWT %08x)\n",
		       __waw_weadw(&pcicptw->pbaweqpowt));
	}
}
#define PCI_DEVICE_ID_EFAW_SWC90E66_0 0x9460
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_EFAW, PCI_DEVICE_ID_EFAW_SWC90E66_0,
	tx4927_quiwk_swc90e66_bwidge);
#endif
