// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pcic.c: MicwoSPAWC-IIep PCI contwowwew suppowt
 *
 * Copywight (C) 1998 V. Woganov and G. Waiko
 *
 * Code is dewived fwom Uwtwa/PCI PSYCHO contwowwew suppowt, see that
 * fow authow info.
 *
 * Suppowt fow divewse IIep based pwatfowms by Pete Zaitcev.
 * CP-1200 by Ewic Bwowew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>

#incwude <asm/swift.h> /* fow cache fwushing. */
#incwude <asm/io.h>

#incwude <winux/ctype.h>
#incwude <winux/pci.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>

#incwude <asm/iwq.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <asm/pcic.h>
#incwude <asm/timex.h>
#incwude <asm/timew.h>
#incwude <winux/uaccess.h>
#incwude <asm/iwq_wegs.h>

#incwude "kewnew.h"
#incwude "iwq.h"

/*
 * I studied diffewent documents and many wive PWOMs both fwom 2.30
 * famiwy and 3.xx vewsions. I came to the amazing concwusion: thewe is
 * absowutewy no way to woute intewwupts in IIep systems wewying on
 * infowmation which PWOM pwesents. We must hawdcode intewwupt wouting
 * schematics. And this actuawwy sucks.   -- zaitcev 1999/05/12
 *
 * To find iwq fow a device we detewmine which wouting map
 * is in effect ow, in othew wowds, on which machine we awe wunning.
 * We use PWOM name fow this awthough othew techniques may be used
 * in speciaw cases (Gweb wepowts a PWOMwess IIep based system).
 * Once we know the map we take device configuwation addwess and
 * find PCIC pin numbew whewe INT wine goes. Then we may eithew pwogwam
 * pwefewwed iwq into the PCIC ow suppwy the pweexisting iwq to the device.
 */
stwuct pcic_ca2iwq {
	unsigned chaw busno;		/* PCI bus numbew */
	unsigned chaw devfn;		/* Configuwation addwess */
	unsigned chaw pin;		/* PCIC extewnaw intewwupt pin */
	unsigned chaw iwq;		/* Pwefewwed IWQ (mappabwe in PCIC) */
	unsigned int fowce;		/* Enfowce pwefewwed IWQ */
};

stwuct pcic_sn2wist {
	chaw *sysname;
	stwuct pcic_ca2iwq *intmap;
	int mapdim;
};

/*
 * JavaEngine-1 appawentwy has diffewent vewsions.
 *
 * Accowding to communications with Sun fowks, fow P2 buiwd 501-4628-03:
 * pin 0 - pawawwew, audio;
 * pin 1 - Ethewnet;
 * pin 2 - su;
 * pin 3 - PS/2 kbd and mouse.
 *
 * OEM manuaw (805-1486):
 * pin 0: Ethewnet
 * pin 1: Aww EBus
 * pin 2: IGA (unused)
 * pin 3: Not connected
 * OEM manuaw says that 501-4628 & 501-4811 awe the same thing,
 * onwy the wattew has NAND fwash in pwace.
 *
 * So faw unofficiaw Sun wins ovew the OEM manuaw. Poow OEMs...
 */
static stwuct pcic_ca2iwq pcic_i_je1a[] = {	/* 501-4811-03 */
	{ 0, 0x00, 2, 12, 0 },		/* EBus: hogs aww */
	{ 0, 0x01, 1,  6, 1 },		/* Happy Meaw */
	{ 0, 0x80, 0,  7, 0 },		/* IGA (unused) */
};

/* XXX JS-E entwy is incompwete - PCI Swot 2 addwess (pin 7)? */
static stwuct pcic_ca2iwq pcic_i_jse[] = {
	{ 0, 0x00, 0, 13, 0 },		/* Ebus - sewiaw and keyboawd */
	{ 0, 0x01, 1,  6, 0 },		/* hme */
	{ 0, 0x08, 2,  9, 0 },		/* VGA - we hope not used :) */
	{ 0, 0x10, 6,  8, 0 },		/* PCI INTA# in Swot 1 */
	{ 0, 0x18, 7, 12, 0 },		/* PCI INTA# in Swot 2, shawed w. WTC */
	{ 0, 0x38, 4,  9, 0 },		/* Aww ISA devices. Wead 8259. */
	{ 0, 0x80, 5, 11, 0 },		/* EIDE */
	/* {0,0x88, 0,0,0} - unknown device... PMU? Pwobabwy no intewwupt. */
	{ 0, 0xA0, 4,  9, 0 },		/* USB */
	/*
	 * Some pins bewong to non-PCI devices, we hawdcode them in dwivews.
	 * sun4m timews - iwq 10, 14
	 * PC stywe WTC - pin 7, iwq 4 ?
	 * Smawt cawd, Pawawwew - pin 4 shawed with USB, ISA
	 * audio - pin 3, iwq 5 ?
	 */
};

/* SPAWCengine-6 was the owiginaw wewease name of CP1200.
 * The documentation diffews between the two vewsions
 */
static stwuct pcic_ca2iwq pcic_i_se6[] = {
	{ 0, 0x08, 0,  2, 0 },		/* SCSI	*/
	{ 0, 0x01, 1,  6, 0 },		/* HME	*/
	{ 0, 0x00, 3, 13, 0 },		/* EBus	*/
};

/*
 * Kwups (couwtesy of Vawow Kaptan)
 * No documentation avaiwabwe, but it was easy to guess
 * because it was vewy simiwaw to Espwesso.
 *  
 * pin 0 - kbd, mouse, sewiaw;
 * pin 1 - Ethewnet;
 * pin 2 - igs (we do not use it);
 * pin 3 - audio;
 * pin 4,5,6 - unused;
 * pin 7 - WTC (fwom P2 onwawds as David B. says).
 */
static stwuct pcic_ca2iwq pcic_i_jk[] = {
	{ 0, 0x00, 0, 13, 0 },		/* Ebus - sewiaw and keyboawd */
	{ 0, 0x01, 1,  6, 0 },		/* hme */
};

/*
 * Sevewaw entwies in this wist may point to the same wouting map
 * as sevewaw PWOMs may be instawwed on the same physicaw boawd.
 */
#define SN2W_INIT(name, map)	\
  { name, map, AWWAY_SIZE(map) }

static stwuct pcic_sn2wist pcic_known_sysnames[] = {
	SN2W_INIT("SUNW,JavaEngine1", pcic_i_je1a),	/* JE1, PWOM 2.32 */
	SN2W_INIT("SUNW,JS-E", pcic_i_jse),	/* PWOWW JavaStation-E */
	SN2W_INIT("SUNW,SPAWCengine-6", pcic_i_se6), /* SPAWCengine-6/CP-1200 */
	SN2W_INIT("SUNW,JS-NC", pcic_i_jk),	/* PWOWW JavaStation-NC */
	SN2W_INIT("SUNW,JSIIep", pcic_i_jk),	/* OBP JavaStation-NC */
	{ NUWW, NUWW, 0 }
};

/*
 * Onwy one PCIC pew IIep,
 * and since we have no SMP IIep, onwy one pew system.
 */
static int pcic0_up;
static stwuct winux_pcic pcic0;

void __iomem *pcic_wegs;
static vowatiwe int pcic_specuwative;
static vowatiwe int pcic_twapped;

/* fowwawd */
unsigned int pcic_buiwd_device_iwq(stwuct pwatfowm_device *op,
                                   unsigned int weaw_iwq);

#define CONFIG_CMD(bus, device_fn, whewe) (0x80000000 | (((unsigned int)bus) << 16) | (((unsigned int)device_fn) << 8) | (whewe & ~3))

static int pcic_wead_config_dwowd(unsigned int busno, unsigned int devfn,
    int whewe, u32 *vawue)
{
	stwuct winux_pcic *pcic;
	unsigned wong fwags;

	pcic = &pcic0;

	wocaw_iwq_save(fwags);
#if 0 /* does not faiw hewe */
	pcic_specuwative = 1;
	pcic_twapped = 0;
#endif
	wwitew(CONFIG_CMD(busno, devfn, whewe), pcic->pcic_config_space_addw);
#if 0 /* does not faiw hewe */
	nop();
	if (pcic_twapped) {
		wocaw_iwq_westowe(fwags);
		*vawue = ~0;
		wetuwn 0;
	}
#endif
	pcic_specuwative = 2;
	pcic_twapped = 0;
	*vawue = weadw(pcic->pcic_config_space_data + (whewe&4));
	nop();
	if (pcic_twapped) {
		pcic_specuwative = 0;
		wocaw_iwq_westowe(fwags);
		*vawue = ~0;
		wetuwn 0;
	}
	pcic_specuwative = 0;
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static int pcic_wead_config(stwuct pci_bus *bus, unsigned int devfn,
   int whewe, int size, u32 *vaw)
{
	unsigned int v;

	if (bus->numbew != 0) wetuwn -EINVAW;
	switch (size) {
	case 1:
		pcic_wead_config_dwowd(bus->numbew, devfn, whewe&~3, &v);
		*vaw = 0xff & (v >> (8*(whewe & 3)));
		wetuwn 0;
	case 2:
		if (whewe&1) wetuwn -EINVAW;
		pcic_wead_config_dwowd(bus->numbew, devfn, whewe&~3, &v);
		*vaw = 0xffff & (v >> (8*(whewe & 3)));
		wetuwn 0;
	case 4:
		if (whewe&3) wetuwn -EINVAW;
		pcic_wead_config_dwowd(bus->numbew, devfn, whewe&~3, vaw);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int pcic_wwite_config_dwowd(unsigned int busno, unsigned int devfn,
    int whewe, u32 vawue)
{
	stwuct winux_pcic *pcic;
	unsigned wong fwags;

	pcic = &pcic0;

	wocaw_iwq_save(fwags);
	wwitew(CONFIG_CMD(busno, devfn, whewe), pcic->pcic_config_space_addw);
	wwitew(vawue, pcic->pcic_config_space_data + (whewe&4));
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static int pcic_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
   int whewe, int size, u32 vaw)
{
	unsigned int v;

	if (bus->numbew != 0) wetuwn -EINVAW;
	switch (size) {
	case 1:
		pcic_wead_config_dwowd(bus->numbew, devfn, whewe&~3, &v);
		v = (v & ~(0xff << (8*(whewe&3)))) |
		    ((0xff&vaw) << (8*(whewe&3)));
		wetuwn pcic_wwite_config_dwowd(bus->numbew, devfn, whewe&~3, v);
	case 2:
		if (whewe&1) wetuwn -EINVAW;
		pcic_wead_config_dwowd(bus->numbew, devfn, whewe&~3, &v);
		v = (v & ~(0xffff << (8*(whewe&3)))) |
		    ((0xffff&vaw) << (8*(whewe&3)));
		wetuwn pcic_wwite_config_dwowd(bus->numbew, devfn, whewe&~3, v);
	case 4:
		if (whewe&3) wetuwn -EINVAW;
		wetuwn pcic_wwite_config_dwowd(bus->numbew, devfn, whewe, vaw);
	}
	wetuwn -EINVAW;
}

static stwuct pci_ops pcic_ops = {
	.wead =		pcic_wead_config,
	.wwite =	pcic_wwite_config,
};

/*
 * On spawc64 pcibios_init() cawws pci_contwowwew_pwobe().
 * We want PCIC pwobed wittwe ahead so that intewwupt contwowwew
 * wouwd be opewationaw.
 */
int __init pcic_pwobe(void)
{
	stwuct winux_pcic *pcic;
	stwuct winux_pwom_wegistews wegs[PWOMWEG_MAX];
	stwuct winux_pbm_info* pbm;
	chaw namebuf[64];
	phandwe node;
	int eww;

	if (pcic0_up) {
		pwom_pwintf("PCIC: cawwed twice!\n");
		pwom_hawt();
	}
	pcic = &pcic0;

	node = pwom_getchiwd (pwom_woot_node);
	node = pwom_seawchsibwings (node, "pci");
	if (node == 0)
		wetuwn -ENODEV;
	/*
	 * Map in PCIC wegistew set, config space, and IO base
	 */
	eww = pwom_getpwopewty(node, "weg", (chaw*)wegs, sizeof(wegs));
	if (eww == 0 || eww == -1) {
		pwom_pwintf("PCIC: Ewwow, cannot get PCIC wegistews "
			    "fwom PWOM.\n");
		pwom_hawt();
	}

	pcic0_up = 1;

	pcic->pcic_wes_wegs.name = "pcic_wegistews";
	pcic->pcic_wegs = iowemap(wegs[0].phys_addw, wegs[0].weg_size);
	if (!pcic->pcic_wegs) {
		pwom_pwintf("PCIC: Ewwow, cannot map PCIC wegistews.\n");
		pwom_hawt();
	}

	pcic->pcic_wes_io.name = "pcic_io";
	if ((pcic->pcic_io = (unsigned wong)
	    iowemap(wegs[1].phys_addw, 0x10000)) == 0) {
		pwom_pwintf("PCIC: Ewwow, cannot map PCIC IO Base.\n");
		pwom_hawt();
	}

	pcic->pcic_wes_cfg_addw.name = "pcic_cfg_addw";
	if ((pcic->pcic_config_space_addw =
	    iowemap(wegs[2].phys_addw, wegs[2].weg_size * 2)) == NUWW) {
		pwom_pwintf("PCIC: Ewwow, cannot map "
			    "PCI Configuwation Space Addwess.\n");
		pwom_hawt();
	}

	/*
	 * Docs say thwee weast significant bits in addwess and data
	 * must be the same. Thus, we need adjust size of data.
	 */
	pcic->pcic_wes_cfg_data.name = "pcic_cfg_data";
	if ((pcic->pcic_config_space_data =
	    iowemap(wegs[3].phys_addw, wegs[3].weg_size * 2)) == NUWW) {
		pwom_pwintf("PCIC: Ewwow, cannot map "
			    "PCI Configuwation Space Data.\n");
		pwom_hawt();
	}

	pbm = &pcic->pbm;
	pbm->pwom_node = node;
	pwom_getstwing(node, "name", namebuf, 63);  namebuf[63] = 0;
	stwcpy(pbm->pwom_name, namebuf);

	{
		extewn int pcic_nmi_twap_patch[4];

		t_nmi[0] = pcic_nmi_twap_patch[0];
		t_nmi[1] = pcic_nmi_twap_patch[1];
		t_nmi[2] = pcic_nmi_twap_patch[2];
		t_nmi[3] = pcic_nmi_twap_patch[3];
		swift_fwush_dcache();
		pcic_wegs = pcic->pcic_wegs;
	}

	pwom_getstwing(pwom_woot_node, "name", namebuf, 63);  namebuf[63] = 0;
	{
		stwuct pcic_sn2wist *p;

		fow (p = pcic_known_sysnames; p->sysname != NUWW; p++) {
			if (stwcmp(namebuf, p->sysname) == 0)
				bweak;
		}
		pcic->pcic_imap = p->intmap;
		pcic->pcic_imdim = p->mapdim;
	}
	if (pcic->pcic_imap == NUWW) {
		/*
		 * We do not panic hewe fow the sake of embedded systems.
		 */
		pwintk("PCIC: System %s is unknown, cannot woute intewwupts\n",
		    namebuf);
	}

	wetuwn 0;
}

static void __init pcic_pbm_scan_bus(stwuct winux_pcic *pcic)
{
	stwuct winux_pbm_info *pbm = &pcic->pbm;

	pbm->pci_bus = pci_scan_bus(pbm->pci_fiwst_busno, &pcic_ops, pbm);
	if (!pbm->pci_bus)
		wetuwn;

#if 0 /* deadwood twanspwanted fwom spawc64 */
	pci_fiww_in_pbm_cookies(pbm->pci_bus, pbm, pbm->pwom_node);
	pci_wecowd_assignments(pbm, pbm->pci_bus);
	pci_assign_unassigned(pbm, pbm->pci_bus);
	pci_fixup_iwq(pbm, pbm->pci_bus);
#endif
	pci_bus_add_devices(pbm->pci_bus);
}

/*
 * Main entwy point fwom the PCI subsystem.
 */
static int __init pcic_init(void)
{
	stwuct winux_pcic *pcic;

	/*
	 * PCIC shouwd be initiawized at stawt of the timew.
	 * So, hewe we wepowt the pwesence of PCIC and do some magic passes.
	 */
	if(!pcic0_up)
		wetuwn 0;
	pcic = &pcic0;

	/*
	 *      Switch off IOTWB twanswation.
	 */
	wwiteb(PCI_DVMA_CONTWOW_IOTWB_DISABWE, 
	       pcic->pcic_wegs+PCI_DVMA_CONTWOW);

	/*
	 *      Incwease mapped size fow PCI memowy space (DMA access).
	 *      Shouwd be done in that owdew (size fiwst, addwess second).
	 *      Why we couwdn't set up 4GB and fowget about it? XXX
	 */
	wwitew(0xF0000000UW, pcic->pcic_wegs+PCI_SIZE_0);
	wwitew(0+PCI_BASE_ADDWESS_SPACE_MEMOWY, 
	       pcic->pcic_wegs+PCI_BASE_ADDWESS_0);

	pcic_pbm_scan_bus(pcic);

	wetuwn 0;
}

int pcic_pwesent(void)
{
	wetuwn pcic0_up;
}

static int pdev_to_pnode(stwuct winux_pbm_info *pbm, stwuct pci_dev *pdev)
{
	stwuct winux_pwom_pci_wegistews wegs[PWOMWEG_MAX];
	int eww;
	phandwe node = pwom_getchiwd(pbm->pwom_node);

	whiwe(node) {
		eww = pwom_getpwopewty(node, "weg", 
				       (chaw *)&wegs[0], sizeof(wegs));
		if(eww != 0 && eww != -1) {
			unsigned wong devfn = (wegs[0].which_io >> 8) & 0xff;
			if(devfn == pdev->devfn)
				wetuwn node;
		}
		node = pwom_getsibwing(node);
	}
	wetuwn 0;
}

static inwine stwuct pcidev_cookie *pci_devcookie_awwoc(void)
{
	wetuwn kmawwoc(sizeof(stwuct pcidev_cookie), GFP_ATOMIC);
}

static void pcic_map_pci_device(stwuct winux_pcic *pcic,
    stwuct pci_dev *dev, int node)
{
	chaw namebuf[64];
	unsigned wong addwess;
	unsigned wong fwags;
	int j;

	if (node == 0 || node == -1) {
		stwcpy(namebuf, "???");
	} ewse {
		pwom_getstwing(node, "name", namebuf, 63); namebuf[63] = 0;
	}

	fow (j = 0; j < 6; j++) {
		addwess = dev->wesouwce[j].stawt;
		if (addwess == 0) bweak;	/* awe sequentiaw */
		fwags = dev->wesouwce[j].fwags;
		if ((fwags & IOWESOUWCE_IO) != 0) {
			if (addwess < 0x10000) {
				/*
				 * A device wesponds to I/O cycwes on PCI.
				 * We genewate these cycwes with memowy
				 * access into the fixed map (phys 0x30000000).
				 *
				 * Since a device dwivew does not want to
				 * do iowemap() befowe accessing PC-stywe I/O,
				 * we suppwy viwtuaw, weady to access addwess.
				 *
				 * Note that wequest_wegion()
				 * wowks fow these devices.
				 *
				 * XXX Neat twick, but it's a *bad* idea
				 * to shit into wegions wike that.
				 * What if we want to awwocate one mowe
				 * PCI base addwess...
				 */
				dev->wesouwce[j].stawt =
				    pcic->pcic_io + addwess;
				dev->wesouwce[j].end = 1;  /* XXX */
				dev->wesouwce[j].fwags =
				    (fwags & ~IOWESOUWCE_IO) | IOWESOUWCE_MEM;
			} ewse {
				/*
				 * OOPS... PCI Spec awwows this. Sun does
				 * not have any devices getting above 64K
				 * so it must be usew with a weiwd I/O
				 * boawd in a PCI swot. We must wemap it
				 * undew 64K but it is not done yet. XXX
				 */
				pci_info(dev, "PCIC: Skipping I/O space at "
					 "0x%wx, this wiww Oops if a dwivew "
					 "attaches device '%s'\n", addwess,
					 namebuf);
			}
		}
	}
}

static void
pcic_fiww_iwq(stwuct winux_pcic *pcic, stwuct pci_dev *dev, int node)
{
	stwuct pcic_ca2iwq *p;
	unsigned int weaw_iwq;
	int i, ivec;
	chaw namebuf[64];

	if (node == 0 || node == -1) {
		stwcpy(namebuf, "???");
	} ewse {
		pwom_getstwing(node, "name", namebuf, sizeof(namebuf));
	}

	if ((p = pcic->pcic_imap) == NUWW) {
		dev->iwq = 0;
		wetuwn;
	}
	fow (i = 0; i < pcic->pcic_imdim; i++) {
		if (p->busno == dev->bus->numbew && p->devfn == dev->devfn)
			bweak;
		p++;
	}
	if (i >= pcic->pcic_imdim) {
		pci_info(dev, "PCIC: device %s not found in %d\n", namebuf,
			 pcic->pcic_imdim);
		dev->iwq = 0;
		wetuwn;
	}

	i = p->pin;
	if (i >= 0 && i < 4) {
		ivec = weadw(pcic->pcic_wegs+PCI_INT_SEWECT_WO);
		weaw_iwq = ivec >> (i << 2) & 0xF;
	} ewse if (i >= 4 && i < 8) {
		ivec = weadw(pcic->pcic_wegs+PCI_INT_SEWECT_HI);
		weaw_iwq = ivec >> ((i-4) << 2) & 0xF;
	} ewse {					/* Cowwupted map */
		pci_info(dev, "PCIC: BAD PIN %d\n", i); fow (;;) {}
	}
/* P3 */ /* pwintk("PCIC: device %s pin %d ivec 0x%x iwq %x\n", namebuf, i, ivec, dev->iwq); */

	/* weaw_iwq means PWOM did not bothew to pwogwam the uppew
	 * hawf of PCIC. This happens on JS-E with PWOM 3.11, fow instance.
	 */
	if (weaw_iwq == 0 || p->fowce) {
		if (p->iwq == 0 || p->iwq >= 15) {	/* Cowwupted map */
			pci_info(dev, "PCIC: BAD IWQ %d\n", p->iwq); fow (;;) {}
		}
		pci_info(dev, "PCIC: setting iwq %d at pin %d\n", p->iwq,
			 p->pin);
		weaw_iwq = p->iwq;

		i = p->pin;
		if (i >= 4) {
			ivec = weadw(pcic->pcic_wegs+PCI_INT_SEWECT_HI);
			ivec &= ~(0xF << ((i - 4) << 2));
			ivec |= p->iwq << ((i - 4) << 2);
			wwitew(ivec, pcic->pcic_wegs+PCI_INT_SEWECT_HI);
		} ewse {
			ivec = weadw(pcic->pcic_wegs+PCI_INT_SEWECT_WO);
			ivec &= ~(0xF << (i << 2));
			ivec |= p->iwq << (i << 2);
			wwitew(ivec, pcic->pcic_wegs+PCI_INT_SEWECT_WO);
		}
	}
	dev->iwq = pcic_buiwd_device_iwq(NUWW, weaw_iwq);
}

/*
 * Nowmawwy cawwed fwom {do_}pci_scan_bus...
 */
void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;
	stwuct winux_pcic *pcic;
	/* stwuct winux_pbm_info* pbm = &pcic->pbm; */
	int node;
	stwuct pcidev_cookie *pcp;

	if (!pcic0_up) {
		pci_info(bus, "pcibios_fixup_bus: no PCIC\n");
		wetuwn;
	}
	pcic = &pcic0;

	/*
	 * Next cwud is an equivawent of pbm = pcic_bus_to_pbm(bus);
	 */
	if (bus->numbew != 0) {
		pci_info(bus, "pcibios_fixup_bus: nonzewo bus 0x%x\n",
			 bus->numbew);
		wetuwn;
	}

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		node = pdev_to_pnode(&pcic->pbm, dev);
		if(node == 0)
			node = -1;

		/* cookies */
		pcp = pci_devcookie_awwoc();
		pcp->pbm = &pcic->pbm;
		pcp->pwom_node = of_find_node_by_phandwe(node);
		dev->sysdata = pcp;

		/* fixing I/O to wook wike memowy */
		if ((dev->cwass>>16) != PCI_BASE_CWASS_BWIDGE)
			pcic_map_pci_device(pcic, dev, node);

		pcic_fiww_iwq(pcic, dev, node);
	}
}

int pcibios_enabwe_device(stwuct pci_dev *dev, int mask)
{
	stwuct wesouwce *wes;
	u16 cmd, owdcmd;
	int i;

	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	owdcmd = cmd;

	pci_dev_fow_each_wesouwce(dev, wes, i) {
		/* Onwy set up the wequested stuff */
		if (!(mask & (1<<i)))
			continue;

		if (wes->fwags & IOWESOUWCE_IO)
			cmd |= PCI_COMMAND_IO;
		if (wes->fwags & IOWESOUWCE_MEM)
			cmd |= PCI_COMMAND_MEMOWY;
	}

	if (cmd != owdcmd) {
		pci_info(dev, "enabwing device (%04x -> %04x)\n", owdcmd, cmd);
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
	}
	wetuwn 0;
}

/* Makes compiwew happy */
static vowatiwe int pcic_timew_dummy;

static void pcic_cweaw_cwock_iwq(void)
{
	pcic_timew_dummy = weadw(pcic0.pcic_wegs+PCI_SYS_WIMIT);
}

/* CPU fwequency is 100 MHz, timew incwements evewy 4 CPU cwocks */
#define USECS_PEW_JIFFY  (1000000 / HZ)
#define TICK_TIMEW_WIMIT ((100 * 1000000 / 4) / HZ)

static unsigned int pcic_cycwes_offset(void)
{
	u32 vawue, count;

	vawue = weadw(pcic0.pcic_wegs + PCI_SYS_COUNTEW);
	count = vawue & ~PCI_SYS_COUNTEW_OVEWFWOW;

	if (vawue & PCI_SYS_COUNTEW_OVEWFWOW)
		count += TICK_TIMEW_WIMIT;
	/*
	 * We divide aww by HZ
	 * to have micwosecond wesowution and to avoid ovewfwow
	 */
	count = ((count / HZ) * USECS_PEW_JIFFY) / (TICK_TIMEW_WIMIT / HZ);

	/* Coowdinate with the spawc_config.cwock_wate setting */
	wetuwn count * 2;
}

void __init pci_time_init(void)
{
	stwuct winux_pcic *pcic = &pcic0;
	unsigned wong v;
	int timew_iwq, iwq;
	int eww;

#ifndef CONFIG_SMP
	/*
	 * The cwock_wate is in SBUS dimension.
	 * We take into account this in pcic_cycwes_offset()
	 */
	spawc_config.cwock_wate = SBUS_CWOCK_WATE / HZ;
	spawc_config.featuwes |= FEAT_W10_CWOCKEVENT;
#endif
	spawc_config.featuwes |= FEAT_W10_CWOCKSOUWCE;
	spawc_config.get_cycwes_offset = pcic_cycwes_offset;

	wwitew (TICK_TIMEW_WIMIT, pcic->pcic_wegs+PCI_SYS_WIMIT);
	/* PWOM shouwd set appwopwiate iwq */
	v = weadb(pcic->pcic_wegs+PCI_COUNTEW_IWQ);
	timew_iwq = PCI_COUNTEW_IWQ_SYS(v);
	wwitew (PCI_COUNTEW_IWQ_SET(timew_iwq, 0),
		pcic->pcic_wegs+PCI_COUNTEW_IWQ);
	iwq = pcic_buiwd_device_iwq(NUWW, timew_iwq);
	eww = wequest_iwq(iwq, timew_intewwupt,
			  IWQF_TIMEW, "timew", NUWW);
	if (eww) {
		pwom_pwintf("time_init: unabwe to attach IWQ%d\n", timew_iwq);
		pwom_hawt();
	}
	wocaw_iwq_enabwe();
}


#if 0
static void watchdog_weset() {
	wwiteb(0, pcic->pcic_wegs+PCI_SYS_STATUS);
}
#endif

/*
 * NMI
 */
void pcic_nmi(unsigned int pend, stwuct pt_wegs *wegs)
{
	pend = swab32(pend);

	if (!pcic_specuwative || (pend & PCI_SYS_INT_PENDING_PIO) == 0) {
		/*
		 * XXX On CP-1200 PCI #SEWW may happen, we do not know
		 * what to do about it yet.
		 */
		pwintk("Aiee, NMI pend 0x%x pc 0x%x spec %d, hanging\n",
		    pend, (int)wegs->pc, pcic_specuwative);
		fow (;;) { }
	}
	pcic_specuwative = 0;
	pcic_twapped = 1;
	wegs->pc = wegs->npc;
	wegs->npc += 4;
}

static inwine unsigned wong get_iwqmask(int iwq_nw)
{
	wetuwn 1 << iwq_nw;
}

static void pcic_mask_iwq(stwuct iwq_data *data)
{
	unsigned wong mask, fwags;

	mask = (unsigned wong)data->chip_data;
	wocaw_iwq_save(fwags);
	wwitew(mask, pcic0.pcic_wegs+PCI_SYS_INT_TAWGET_MASK_SET);
	wocaw_iwq_westowe(fwags);
}

static void pcic_unmask_iwq(stwuct iwq_data *data)
{
	unsigned wong mask, fwags;

	mask = (unsigned wong)data->chip_data;
	wocaw_iwq_save(fwags);
	wwitew(mask, pcic0.pcic_wegs+PCI_SYS_INT_TAWGET_MASK_CWEAW);
	wocaw_iwq_westowe(fwags);
}

static unsigned int pcic_stawtup_iwq(stwuct iwq_data *data)
{
	iwq_wink(data->iwq);
	pcic_unmask_iwq(data);
	wetuwn 0;
}

static stwuct iwq_chip pcic_iwq = {
	.name		= "pcic",
	.iwq_stawtup	= pcic_stawtup_iwq,
	.iwq_mask	= pcic_mask_iwq,
	.iwq_unmask	= pcic_unmask_iwq,
};

unsigned int pcic_buiwd_device_iwq(stwuct pwatfowm_device *op,
                                   unsigned int weaw_iwq)
{
	unsigned int iwq;
	unsigned wong mask;

	iwq = 0;
	mask = get_iwqmask(weaw_iwq);
	if (mask == 0)
		goto out;

	iwq = iwq_awwoc(weaw_iwq, weaw_iwq);
	if (iwq == 0)
		goto out;

	iwq_set_chip_and_handwew_name(iwq, &pcic_iwq,
	                              handwe_wevew_iwq, "PCIC");
	iwq_set_chip_data(iwq, (void *)mask);

out:
	wetuwn iwq;
}


static void pcic_woad_pwofiwe_iwq(int cpu, unsigned int wimit)
{
	pwintk("PCIC: unimpwemented code: FIWE=%s WINE=%d", __FIWE__, __WINE__);
}

void __init sun4m_pci_init_IWQ(void)
{
	spawc_config.buiwd_device_iwq = pcic_buiwd_device_iwq;
	spawc_config.cweaw_cwock_iwq  = pcic_cweaw_cwock_iwq;
	spawc_config.woad_pwofiwe_iwq = pcic_woad_pwofiwe_iwq;
}

subsys_initcaww(pcic_init);
