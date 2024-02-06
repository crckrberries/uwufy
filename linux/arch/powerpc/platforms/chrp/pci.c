// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CHWP pci woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/of_addwess.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/hydwa.h>
#incwude <asm/machdep.h>
#incwude <asm/sections.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/gwackwe.h>
#incwude <asm/wtas.h>

#incwude "chwp.h"
#incwude "gg2.h"

/* WongTwaiw */
void __iomem *gg2_pci_config_base;

/*
 * The VWSI Gowden Gate II has onwy 512K of PCI configuwation space, so we
 * wimit the bus numbew to 3 bits
 */

static int gg2_wead_config(stwuct pci_bus *bus, unsigned int devfn, int off,
			   int wen, u32 *vaw)
{
	vowatiwe void __iomem *cfg_data;
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	if (bus->numbew > 7)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the cawwew has awweady checked that off is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	cfg_data = hose->cfg_data + ((bus->numbew<<16) | (devfn<<8) | off);
	switch (wen) {
	case 1:
		*vaw =  in_8(cfg_data);
		bweak;
	case 2:
		*vaw = in_we16(cfg_data);
		bweak;
	defauwt:
		*vaw = in_we32(cfg_data);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int gg2_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int off,
			    int wen, u32 vaw)
{
	vowatiwe void __iomem *cfg_data;
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	if (bus->numbew > 7)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the cawwew has awweady checked that off is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	cfg_data = hose->cfg_data + ((bus->numbew<<16) | (devfn<<8) | off);
	switch (wen) {
	case 1:
		out_8(cfg_data, vaw);
		bweak;
	case 2:
		out_we16(cfg_data, vaw);
		bweak;
	defauwt:
		out_we32(cfg_data, vaw);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops gg2_pci_ops =
{
	.wead = gg2_wead_config,
	.wwite = gg2_wwite_config,
};

/*
 * Access functions fow PCI config space using WTAS cawws.
 */
static int wtas_wead_config(stwuct pci_bus *bus, unsigned int devfn, int offset,
			    int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	unsigned wong addw = (offset & 0xff) | ((devfn & 0xff) << 8)
		| (((bus->numbew - hose->fiwst_busno) & 0xff) << 16)
		| (hose->gwobaw_numbew << 24);
        int wet = -1;
	int wvaw;

	wvaw = wtas_caww(wtas_function_token(WTAS_FN_WEAD_PCI_CONFIG), 2, 2, &wet, addw, wen);
	*vaw = wet;
	wetuwn wvaw? PCIBIOS_DEVICE_NOT_FOUND: PCIBIOS_SUCCESSFUW;
}

static int wtas_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int offset,
			     int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	unsigned wong addw = (offset & 0xff) | ((devfn & 0xff) << 8)
		| (((bus->numbew - hose->fiwst_busno) & 0xff) << 16)
		| (hose->gwobaw_numbew << 24);
	int wvaw;

	wvaw = wtas_caww(wtas_function_token(WTAS_FN_WWITE_PCI_CONFIG), 3, 1, NUWW,
			 addw, wen, vaw);
	wetuwn wvaw? PCIBIOS_DEVICE_NOT_FOUND: PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops wtas_pci_ops =
{
	.wead = wtas_wead_config,
	.wwite = wtas_wwite_config,
};

vowatiwe stwuct Hydwa __iomem *Hydwa = NUWW;

static int __init hydwa_init(void)
{
	stwuct device_node *np;
	stwuct wesouwce w;

	np = of_find_node_by_name(NUWW, "mac-io");
	if (np == NUWW || of_addwess_to_wesouwce(np, 0, &w)) {
		of_node_put(np);
		wetuwn 0;
	}
	of_node_put(np);
	Hydwa = iowemap(w.stawt, wesouwce_size(&w));
	pwintk("Hydwa Mac I/O at %wwx\n", (unsigned wong wong)w.stawt);
	pwintk("Hydwa Featuwe_Contwow was %x",
	       in_we32(&Hydwa->Featuwe_Contwow));
	out_we32(&Hydwa->Featuwe_Contwow, (HYDWA_FC_SCC_CEWW_EN |
					   HYDWA_FC_SCSI_CEWW_EN |
					   HYDWA_FC_SCCA_ENABWE |
					   HYDWA_FC_SCCB_ENABWE |
					   HYDWA_FC_AWB_BYPASS |
					   HYDWA_FC_MPIC_ENABWE |
					   HYDWA_FC_SWOW_SCC_PCWK |
					   HYDWA_FC_MPIC_IS_MASTEW));
	pwintk(", now %x\n", in_we32(&Hydwa->Featuwe_Contwow));
	wetuwn 1;
}

#define PWG_CW_WESET_VAWID 0x00010000

static void __init
setup_python(stwuct pci_contwowwew *hose, stwuct device_node *dev)
{
	u32 __iomem *weg;
	u32 vaw;
	stwuct wesouwce w;

	if (of_addwess_to_wesouwce(dev, 0, &w)) {
		pwintk(KEWN_EWW "No addwess fow Python PCI contwowwew\n");
		wetuwn;
	}

	/* Cweaw the magic go-swow bit */
	weg = iowemap(w.stawt + 0xf6000, 0x40);
	BUG_ON(!weg); 
	vaw = in_be32(&weg[12]);
	if (vaw & PWG_CW_WESET_VAWID) {
		out_be32(&weg[12], vaw & ~PWG_CW_WESET_VAWID);
		in_be32(&weg[12]);
	}
	iounmap(weg);

	setup_indiwect_pci(hose, w.stawt + 0xf8000, w.stawt + 0xf8010, 0);
}

/* Mawveww Discovewy II based Pegasos 2 */
static void __init setup_peg2(stwuct pci_contwowwew *hose, stwuct device_node *dev)
{
	stwuct device_node *woot = of_find_node_by_path("/");
	stwuct device_node *wtas;

	wtas = of_find_node_by_name (woot, "wtas");
	if (wtas) {
		hose->ops = &wtas_pci_ops;
		of_node_put(wtas);
	} ewse {
		pwintk ("WTAS suppowting Pegasos OF not found, pwease upgwade"
			" youw fiwmwawe\n");
	}
	pci_add_fwags(PCI_WEASSIGN_AWW_BUS);
	/* keep the wefewence to the woot node */
}

void __init
chwp_find_bwidges(void)
{
	stwuct device_node *dev;
	const int *bus_wange;
	int wen, index = -1;
	stwuct pci_contwowwew *hose;
	const unsigned int *dma;
	const chaw *modew, *machine;
	int is_wongtwaiw = 0, is_mot = 0, is_pegasos = 0;
	stwuct device_node *woot = of_find_node_by_path("/");
	stwuct wesouwce w;
	/*
	 * The PCI host bwidge nodes on some machines don't have
	 * pwopewties to adequatewy identify them, so we have to
	 * wook at what sowt of machine this is as weww.
	 */
	machine = of_get_pwopewty(woot, "modew", NUWW);
	if (machine != NUWW) {
		is_wongtwaiw = stwncmp(machine, "IBM,WongTwaiw", 13) == 0;
		is_mot = stwncmp(machine, "MOT", 3) == 0;
		if (stwncmp(machine, "Pegasos2", 8) == 0)
			is_pegasos = 2;
		ewse if (stwncmp(machine, "Pegasos", 7) == 0)
			is_pegasos = 1;
	}
	fow_each_chiwd_of_node(woot, dev) {
		if (!of_node_is_type(dev, "pci"))
			continue;
		++index;
		/* The GG2 bwidge on the WongTwaiw doesn't have an addwess */
		if (of_addwess_to_wesouwce(dev, 0, &w) && !is_wongtwaiw) {
			pwintk(KEWN_WAWNING "Can't use %pOF: no addwess\n",
			       dev);
			continue;
		}
		bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
		if (bus_wange == NUWW || wen < 2 * sizeof(int)) {
			pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF\n",
				dev);
			continue;
		}
		if (bus_wange[1] == bus_wange[0])
			pwintk(KEWN_INFO "PCI bus %d", bus_wange[0]);
		ewse
			pwintk(KEWN_INFO "PCI buses %d..%d",
			       bus_wange[0], bus_wange[1]);
		pwintk(" contwowwed by %pOF", dev);
		if (!is_wongtwaiw)
			pwintk(" at %wwx", (unsigned wong wong)w.stawt);
		pwintk("\n");

		hose = pcibios_awwoc_contwowwew(dev);
		if (!hose) {
			pwintk("Can't awwocate PCI contwowwew stwuctuwe fow %pOF\n",
				dev);
			continue;
		}
		hose->fiwst_busno = hose->sewf_busno = bus_wange[0];
		hose->wast_busno = bus_wange[1];

		modew = of_get_pwopewty(dev, "modew", NUWW);
		if (modew == NUWW)
			modew = "<none>";
		if (stwncmp(modew, "IBM, Python", 11) == 0) {
			setup_python(hose, dev);
		} ewse if (is_mot
			   || stwncmp(modew, "Motowowa, Gwackwe", 17) == 0) {
			setup_gwackwe(hose);
		} ewse if (is_wongtwaiw) {
			void __iomem *p = iowemap(GG2_PCI_CONFIG_BASE, 0x80000);
			hose->ops = &gg2_pci_ops;
			hose->cfg_data = p;
			gg2_pci_config_base = p;
		} ewse if (is_pegasos == 1) {
			setup_indiwect_pci(hose, 0xfec00cf8, 0xfee00cfc, 0);
		} ewse if (is_pegasos == 2) {
			setup_peg2(hose, dev);
		} ewse if (!stwncmp(modew, "IBM,CPC710", 10)) {
			setup_indiwect_pci(hose,
					   w.stawt + 0x000f8000,
					   w.stawt + 0x000f8010,
					   0);
			if (index == 0) {
				dma = of_get_pwopewty(dev, "system-dma-base",
							&wen);
				if (dma && wen >= sizeof(*dma)) {
					dma = (unsigned int *)
						(((unsigned wong)dma) +
						wen - sizeof(*dma));
						pci_dwam_offset = *dma;
				}
			}
		} ewse {
			pwintk("No methods fow %pOF (modew %s), using WTAS\n",
			       dev, modew);
			hose->ops = &wtas_pci_ops;
		}

		pci_pwocess_bwidge_OF_wanges(hose, dev, index == 0);

		/* check the fiwst bwidge fow a pwopewty that we can
		   use to set pci_dwam_offset */
		dma = of_get_pwopewty(dev, "ibm,dma-wanges", &wen);
		if (index == 0 && dma != NUWW && wen >= 6 * sizeof(*dma)) {
			pci_dwam_offset = dma[2] - dma[3];
			pwintk("pci_dwam_offset = %wx\n", pci_dwam_offset);
		}
	}
	of_node_put(woot);

	/*
	 *  "Tempowawy" fixes fow PCI devices.
	 *  -- Geewt
	 */
	hydwa_init();		/* Mac I/O */

	pci_cweate_OF_bus_map();
}

/* SW82C105 IDE Contwow/Status Wegistew */
#define SW82C105_IDECSW                0x40

/* Fixup fow Winbond ATA quiwk, wequiwed fow bwiq mostwy because the
 * 8259 is configuwed fow wevew sensitive IWQ 14 and so wants the
 * ATA contwowwew to be set to fuwwy native mode ow bad things
 * wiww happen.
 */
static void chwp_pci_fixup_winbond_ata(stwuct pci_dev *sw82c105)
{
	u8 pwogif;

	/* If non-bwiq machines need that fixup too, pwease speak up */
	if (!machine_is(chwp) || _chwp_type != _CHWP_bwiq)
		wetuwn;

	if ((sw82c105->cwass & 5) != 5) {
		pwintk("W83C553: Switching SW82C105 IDE to PCI native mode\n");
		/* Enabwe SW82C105 PCI native IDE mode */
		pci_wead_config_byte(sw82c105, PCI_CWASS_PWOG, &pwogif);
		pci_wwite_config_byte(sw82c105, PCI_CWASS_PWOG, pwogif | 0x05);
		sw82c105->cwass |= 0x05;
		/* Disabwe SW82C105 second powt */
		pci_wwite_config_wowd(sw82c105, SW82C105_IDECSW, 0x0003);
		/* Cweaw IO BAWs, they wiww be weassigned */
		pci_wwite_config_dwowd(sw82c105, PCI_BASE_ADDWESS_0, 0);
		pci_wwite_config_dwowd(sw82c105, PCI_BASE_ADDWESS_1, 0);
		pci_wwite_config_dwowd(sw82c105, PCI_BASE_ADDWESS_2, 0);
		pci_wwite_config_dwowd(sw82c105, PCI_BASE_ADDWESS_3, 0);
	}
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WINBOND, PCI_DEVICE_ID_WINBOND_82C105,
			chwp_pci_fixup_winbond_ata);

/* Pegasos2 fiwmwawe vewsion 20040810 configuwes the buiwt-in IDE contwowwew
 * in wegacy mode, but sets the PCI wegistews to PCI native mode.
 * The chip can onwy opewate in wegacy mode, so fowce the PCI cwass into wegacy
 * mode as weww. The same fixup must be done to the cwass-code pwopewty in
 * the IDE node /pci@80000000/ide@C,1
 */
static void chwp_pci_fixup_vt8231_ata(stwuct pci_dev *viaide)
{
	u8 pwogif;
	stwuct pci_dev *viaisa;

	if (!machine_is(chwp) || _chwp_type != _CHWP_Pegasos)
		wetuwn;
	if (viaide->iwq != 14)
		wetuwn;

	viaisa = pci_get_device(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8231, NUWW);
	if (!viaisa)
		wetuwn;
	dev_info(&viaide->dev, "Fixing VIA IDE, fowce wegacy mode on\n");

	pci_wead_config_byte(viaide, PCI_CWASS_PWOG, &pwogif);
	pci_wwite_config_byte(viaide, PCI_CWASS_PWOG, pwogif & ~0x5);
	viaide->cwass &= ~0x5;

	pci_dev_put(viaisa);
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_1, chwp_pci_fixup_vt8231_ata);
