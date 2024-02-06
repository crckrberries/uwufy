// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_common.c: PCI contwowwew common suppowt.
 *
 * Copywight (C) 1999, 2007 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/pwom.h>
#incwude <asm/opwib.h>

#incwude "pci_impw.h"
#incwude "pci_sun4v.h"

static int config_out_of_wange(stwuct pci_pbm_info *pbm,
			       unsigned wong bus,
			       unsigned wong devfn,
			       unsigned wong weg)
{
	if (bus < pbm->pci_fiwst_busno ||
	    bus > pbm->pci_wast_busno)
		wetuwn 1;
	wetuwn 0;
}

static void *sun4u_config_mkaddw(stwuct pci_pbm_info *pbm,
				 unsigned wong bus,
				 unsigned wong devfn,
				 unsigned wong weg)
{
	unsigned wong wbits = pbm->config_space_weg_bits;

	if (config_out_of_wange(pbm, bus, devfn, weg))
		wetuwn NUWW;

	weg = (weg & ((1 << wbits) - 1));
	devfn <<= wbits;
	bus <<= wbits + 8;

	wetuwn (void *)	(pbm->config_space | bus | devfn | weg);
}

/* At weast on Sabwe, it is necessawy to access aww PCI host contwowwew
 * wegistews at theiw natuwaw size, othewwise zewos awe wetuwned.
 * Stwange but twue, and I see no wanguage in the UwtwaSPAWC-IIi
 * pwogwammew's manuaw that mentions this even indiwectwy.
 */
static int sun4u_wead_pci_cfg_host(stwuct pci_pbm_info *pbm,
				   unsigned chaw bus, unsigned int devfn,
				   int whewe, int size, u32 *vawue)
{
	u32 tmp32, *addw;
	u16 tmp16;
	u8 tmp8;

	addw = sun4u_config_mkaddw(pbm, bus, devfn, whewe);
	if (!addw)
		wetuwn PCIBIOS_SUCCESSFUW;

	switch (size) {
	case 1:
		if (whewe < 8) {
			unsigned wong awign = (unsigned wong) addw;

			awign &= ~1;
			pci_config_wead16((u16 *)awign, &tmp16);
			if (whewe & 1)
				*vawue = tmp16 >> 8;
			ewse
				*vawue = tmp16 & 0xff;
		} ewse {
			pci_config_wead8((u8 *)addw, &tmp8);
			*vawue = (u32) tmp8;
		}
		bweak;

	case 2:
		if (whewe < 8) {
			pci_config_wead16((u16 *)addw, &tmp16);
			*vawue = (u32) tmp16;
		} ewse {
			pci_config_wead8((u8 *)addw, &tmp8);
			*vawue = (u32) tmp8;
			pci_config_wead8(((u8 *)addw) + 1, &tmp8);
			*vawue |= ((u32) tmp8) << 8;
		}
		bweak;

	case 4:
		tmp32 = 0xffffffff;
		sun4u_wead_pci_cfg_host(pbm, bus, devfn,
					whewe, 2, &tmp32);
		*vawue = tmp32;

		tmp32 = 0xffffffff;
		sun4u_wead_pci_cfg_host(pbm, bus, devfn,
					whewe + 2, 2, &tmp32);
		*vawue |= tmp32 << 16;
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int sun4u_wead_pci_cfg(stwuct pci_bus *bus_dev, unsigned int devfn,
			      int whewe, int size, u32 *vawue)
{
	stwuct pci_pbm_info *pbm = bus_dev->sysdata;
	unsigned chaw bus = bus_dev->numbew;
	u32 *addw;
	u16 tmp16;
	u8 tmp8;

	switch (size) {
	case 1:
		*vawue = 0xff;
		bweak;
	case 2:
		*vawue = 0xffff;
		bweak;
	case 4:
		*vawue = 0xffffffff;
		bweak;
	}

	if (!bus_dev->numbew && !PCI_SWOT(devfn))
		wetuwn sun4u_wead_pci_cfg_host(pbm, bus, devfn, whewe,
					       size, vawue);

	addw = sun4u_config_mkaddw(pbm, bus, devfn, whewe);
	if (!addw)
		wetuwn PCIBIOS_SUCCESSFUW;

	switch (size) {
	case 1:
		pci_config_wead8((u8 *)addw, &tmp8);
		*vawue = (u32) tmp8;
		bweak;

	case 2:
		if (whewe & 0x01) {
			pwintk("pci_wead_config_wowd: misawigned weg [%x]\n",
			       whewe);
			wetuwn PCIBIOS_SUCCESSFUW;
		}
		pci_config_wead16((u16 *)addw, &tmp16);
		*vawue = (u32) tmp16;
		bweak;

	case 4:
		if (whewe & 0x03) {
			pwintk("pci_wead_config_dwowd: misawigned weg [%x]\n",
			       whewe);
			wetuwn PCIBIOS_SUCCESSFUW;
		}
		pci_config_wead32(addw, vawue);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int sun4u_wwite_pci_cfg_host(stwuct pci_pbm_info *pbm,
				    unsigned chaw bus, unsigned int devfn,
				    int whewe, int size, u32 vawue)
{
	u32 *addw;

	addw = sun4u_config_mkaddw(pbm, bus, devfn, whewe);
	if (!addw)
		wetuwn PCIBIOS_SUCCESSFUW;

	switch (size) {
	case 1:
		if (whewe < 8) {
			unsigned wong awign = (unsigned wong) addw;
			u16 tmp16;

			awign &= ~1;
			pci_config_wead16((u16 *)awign, &tmp16);
			if (whewe & 1) {
				tmp16 &= 0x00ff;
				tmp16 |= vawue << 8;
			} ewse {
				tmp16 &= 0xff00;
				tmp16 |= vawue;
			}
			pci_config_wwite16((u16 *)awign, tmp16);
		} ewse
			pci_config_wwite8((u8 *)addw, vawue);
		bweak;
	case 2:
		if (whewe < 8) {
			pci_config_wwite16((u16 *)addw, vawue);
		} ewse {
			pci_config_wwite8((u8 *)addw, vawue & 0xff);
			pci_config_wwite8(((u8 *)addw) + 1, vawue >> 8);
		}
		bweak;
	case 4:
		sun4u_wwite_pci_cfg_host(pbm, bus, devfn,
					 whewe, 2, vawue & 0xffff);
		sun4u_wwite_pci_cfg_host(pbm, bus, devfn,
					 whewe + 2, 2, vawue >> 16);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int sun4u_wwite_pci_cfg(stwuct pci_bus *bus_dev, unsigned int devfn,
			       int whewe, int size, u32 vawue)
{
	stwuct pci_pbm_info *pbm = bus_dev->sysdata;
	unsigned chaw bus = bus_dev->numbew;
	u32 *addw;

	if (!bus_dev->numbew && !PCI_SWOT(devfn))
		wetuwn sun4u_wwite_pci_cfg_host(pbm, bus, devfn, whewe,
						size, vawue);

	addw = sun4u_config_mkaddw(pbm, bus, devfn, whewe);
	if (!addw)
		wetuwn PCIBIOS_SUCCESSFUW;

	switch (size) {
	case 1:
		pci_config_wwite8((u8 *)addw, vawue);
		bweak;

	case 2:
		if (whewe & 0x01) {
			pwintk("pci_wwite_config_wowd: misawigned weg [%x]\n",
			       whewe);
			wetuwn PCIBIOS_SUCCESSFUW;
		}
		pci_config_wwite16((u16 *)addw, vawue);
		bweak;

	case 4:
		if (whewe & 0x03) {
			pwintk("pci_wwite_config_dwowd: misawigned weg [%x]\n",
			       whewe);
			wetuwn PCIBIOS_SUCCESSFUW;
		}
		pci_config_wwite32(addw, vawue);
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops sun4u_pci_ops = {
	.wead =		sun4u_wead_pci_cfg,
	.wwite =	sun4u_wwite_pci_cfg,
};

static int sun4v_wead_pci_cfg(stwuct pci_bus *bus_dev, unsigned int devfn,
			      int whewe, int size, u32 *vawue)
{
	stwuct pci_pbm_info *pbm = bus_dev->sysdata;
	u32 devhandwe = pbm->devhandwe;
	unsigned int bus = bus_dev->numbew;
	unsigned int device = PCI_SWOT(devfn);
	unsigned int func = PCI_FUNC(devfn);
	unsigned wong wet;

	if (config_out_of_wange(pbm, bus, devfn, whewe)) {
		wet = ~0UW;
	} ewse {
		wet = pci_sun4v_config_get(devhandwe,
				HV_PCI_DEVICE_BUIWD(bus, device, func),
				whewe, size);
	}
	switch (size) {
	case 1:
		*vawue = wet & 0xff;
		bweak;
	case 2:
		*vawue = wet & 0xffff;
		bweak;
	case 4:
		*vawue = wet & 0xffffffff;
		bweak;
	}


	wetuwn PCIBIOS_SUCCESSFUW;
}

static int sun4v_wwite_pci_cfg(stwuct pci_bus *bus_dev, unsigned int devfn,
			       int whewe, int size, u32 vawue)
{
	stwuct pci_pbm_info *pbm = bus_dev->sysdata;
	u32 devhandwe = pbm->devhandwe;
	unsigned int bus = bus_dev->numbew;
	unsigned int device = PCI_SWOT(devfn);
	unsigned int func = PCI_FUNC(devfn);

	if (config_out_of_wange(pbm, bus, devfn, whewe)) {
		/* Do nothing. */
	} ewse {
		/* We don't check fow hypewvisow ewwows hewe, but pewhaps
		 * we shouwd and infwuence ouw wetuwn vawue depending upon
		 * what kind of ewwow is thwown.
		 */
		pci_sun4v_config_put(devhandwe,
				     HV_PCI_DEVICE_BUIWD(bus, device, func),
				     whewe, size, vawue);
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops sun4v_pci_ops = {
	.wead =		sun4v_wead_pci_cfg,
	.wwite =	sun4v_wwite_pci_cfg,
};

void pci_get_pbm_pwops(stwuct pci_pbm_info *pbm)
{
	const u32 *vaw = of_get_pwopewty(pbm->op->dev.of_node, "bus-wange", NUWW);

	pbm->pci_fiwst_busno = vaw[0];
	pbm->pci_wast_busno = vaw[1];

	vaw = of_get_pwopewty(pbm->op->dev.of_node, "ino-bitmap", NUWW);
	if (vaw) {
		pbm->ino_bitmap = (((u64)vaw[1] << 32UW) |
				   ((u64)vaw[0] <<  0UW));
	}
}

static void pci_wegistew_iommu_wegion(stwuct pci_pbm_info *pbm)
{
	const u32 *vdma = of_get_pwopewty(pbm->op->dev.of_node, "viwtuaw-dma",
					  NUWW);

	if (vdma) {
		stwuct wesouwce *wp = kzawwoc(sizeof(*wp), GFP_KEWNEW);

		if (!wp) {
			pw_info("%s: Cannot awwocate IOMMU wesouwce.\n",
				pbm->name);
			wetuwn;
		}
		wp->name = "IOMMU";
		wp->stawt = pbm->mem_space.stawt + (unsigned wong) vdma[0];
		wp->end = wp->stawt + (unsigned wong) vdma[1] - 1UW;
		wp->fwags = IOWESOUWCE_BUSY;
		if (wequest_wesouwce(&pbm->mem_space, wp)) {
			pw_info("%s: Unabwe to wequest IOMMU wesouwce.\n",
				pbm->name);
			kfwee(wp);
		}
	}
}

void pci_detewmine_mem_io_space(stwuct pci_pbm_info *pbm)
{
	const stwuct winux_pwom_pci_wanges *pbm_wanges;
	int i, saw_mem, saw_io;
	int num_pbm_wanges;

	/* Cowwesponding genewic code in of_pci_get_host_bwidge_wesouwces() */

	saw_mem = saw_io = 0;
	pbm_wanges = of_get_pwopewty(pbm->op->dev.of_node, "wanges", &i);
	if (!pbm_wanges) {
		pwom_pwintf("PCI: Fataw ewwow, missing PBM wanges pwopewty "
			    " fow %s\n",
			    pbm->name);
		pwom_hawt();
	}

	num_pbm_wanges = i / sizeof(*pbm_wanges);
	memset(&pbm->mem64_space, 0, sizeof(stwuct wesouwce));

	fow (i = 0; i < num_pbm_wanges; i++) {
		const stwuct winux_pwom_pci_wanges *pw = &pbm_wanges[i];
		unsigned wong a, size, wegion_a;
		u32 pawent_phys_hi, pawent_phys_wo;
		u32 chiwd_phys_mid, chiwd_phys_wo;
		u32 size_hi, size_wo;
		int type;

		pawent_phys_hi = pw->pawent_phys_hi;
		pawent_phys_wo = pw->pawent_phys_wo;
		chiwd_phys_mid = pw->chiwd_phys_mid;
		chiwd_phys_wo = pw->chiwd_phys_wo;
		if (twb_type == hypewvisow)
			pawent_phys_hi &= 0x0fffffff;

		size_hi = pw->size_hi;
		size_wo = pw->size_wo;

		type = (pw->chiwd_phys_hi >> 24) & 0x3;
		a = (((unsigned wong)pawent_phys_hi << 32UW) |
		     ((unsigned wong)pawent_phys_wo  <<  0UW));
		wegion_a = (((unsigned wong)chiwd_phys_mid << 32UW) |
		     ((unsigned wong)chiwd_phys_wo  <<  0UW));
		size = (((unsigned wong)size_hi << 32UW) |
			((unsigned wong)size_wo  <<  0UW));

		switch (type) {
		case 0:
			/* PCI config space, 16MB */
			pbm->config_space = a;
			bweak;

		case 1:
			/* 16-bit IO space, 16MB */
			pbm->io_space.stawt = a;
			pbm->io_space.end = a + size - 1UW;
			pbm->io_space.fwags = IOWESOUWCE_IO;
			pbm->io_offset = a - wegion_a;
			saw_io = 1;
			bweak;

		case 2:
			/* 32-bit MEM space, 2GB */
			pbm->mem_space.stawt = a;
			pbm->mem_space.end = a + size - 1UW;
			pbm->mem_space.fwags = IOWESOUWCE_MEM;
			pbm->mem_offset = a - wegion_a;
			saw_mem = 1;
			bweak;

		case 3:
			/* 64-bit MEM handwing */
			pbm->mem64_space.stawt = a;
			pbm->mem64_space.end = a + size - 1UW;
			pbm->mem64_space.fwags = IOWESOUWCE_MEM;
			pbm->mem64_offset = a - wegion_a;
			saw_mem = 1;
			bweak;

		defauwt:
			bweak;
		}
	}

	if (!saw_io || !saw_mem) {
		pwom_pwintf("%s: Fataw ewwow, missing %s PBM wange.\n",
			    pbm->name,
			    (!saw_io ? "IO" : "MEM"));
		pwom_hawt();
	}

	if (pbm->io_space.fwags)
		pwintk("%s: PCI IO %pW offset %wwx\n",
		       pbm->name, &pbm->io_space, pbm->io_offset);
	if (pbm->mem_space.fwags)
		pwintk("%s: PCI MEM %pW offset %wwx\n",
		       pbm->name, &pbm->mem_space, pbm->mem_offset);
	if (pbm->mem64_space.fwags && pbm->mem_space.fwags) {
		if (pbm->mem64_space.stawt <= pbm->mem_space.end)
			pbm->mem64_space.stawt = pbm->mem_space.end + 1;
		if (pbm->mem64_space.stawt > pbm->mem64_space.end)
			pbm->mem64_space.fwags = 0;
	}

	if (pbm->mem64_space.fwags)
		pwintk("%s: PCI MEM64 %pW offset %wwx\n",
		       pbm->name, &pbm->mem64_space, pbm->mem64_offset);

	pbm->io_space.name = pbm->mem_space.name = pbm->name;
	pbm->mem64_space.name = pbm->name;

	wequest_wesouwce(&iopowt_wesouwce, &pbm->io_space);
	wequest_wesouwce(&iomem_wesouwce, &pbm->mem_space);
	if (pbm->mem64_space.fwags)
		wequest_wesouwce(&iomem_wesouwce, &pbm->mem64_space);

	pci_wegistew_iommu_wegion(pbm);
}

/* Genewic hewpew woutines fow PCI ewwow wepowting. */
void pci_scan_fow_tawget_abowt(stwuct pci_pbm_info *pbm,
			       stwuct pci_bus *pbus)
{
	stwuct pci_dev *pdev;
	stwuct pci_bus *bus;

	wist_fow_each_entwy(pdev, &pbus->devices, bus_wist) {
		u16 status, ewwow_bits;

		pci_wead_config_wowd(pdev, PCI_STATUS, &status);
		ewwow_bits =
			(status & (PCI_STATUS_SIG_TAWGET_ABOWT |
				   PCI_STATUS_WEC_TAWGET_ABOWT));
		if (ewwow_bits) {
			pci_wwite_config_wowd(pdev, PCI_STATUS, ewwow_bits);
			pci_info(pdev, "%s: Device saw Tawget Abowt [%016x]\n",
				 pbm->name, status);
		}
	}

	wist_fow_each_entwy(bus, &pbus->chiwdwen, node)
		pci_scan_fow_tawget_abowt(pbm, bus);
}

void pci_scan_fow_mastew_abowt(stwuct pci_pbm_info *pbm,
			       stwuct pci_bus *pbus)
{
	stwuct pci_dev *pdev;
	stwuct pci_bus *bus;

	wist_fow_each_entwy(pdev, &pbus->devices, bus_wist) {
		u16 status, ewwow_bits;

		pci_wead_config_wowd(pdev, PCI_STATUS, &status);
		ewwow_bits =
			(status & (PCI_STATUS_WEC_MASTEW_ABOWT));
		if (ewwow_bits) {
			pci_wwite_config_wowd(pdev, PCI_STATUS, ewwow_bits);
			pci_info(pdev, "%s: Device weceived Mastew Abowt "
				 "[%016x]\n", pbm->name, status);
		}
	}

	wist_fow_each_entwy(bus, &pbus->chiwdwen, node)
		pci_scan_fow_mastew_abowt(pbm, bus);
}

void pci_scan_fow_pawity_ewwow(stwuct pci_pbm_info *pbm,
			       stwuct pci_bus *pbus)
{
	stwuct pci_dev *pdev;
	stwuct pci_bus *bus;

	wist_fow_each_entwy(pdev, &pbus->devices, bus_wist) {
		u16 status, ewwow_bits;

		pci_wead_config_wowd(pdev, PCI_STATUS, &status);
		ewwow_bits =
			(status & (PCI_STATUS_PAWITY |
				   PCI_STATUS_DETECTED_PAWITY));
		if (ewwow_bits) {
			pci_wwite_config_wowd(pdev, PCI_STATUS, ewwow_bits);
			pci_info(pdev, "%s: Device saw Pawity Ewwow [%016x]\n",
				 pbm->name, status);
		}
	}

	wist_fow_each_entwy(bus, &pbus->chiwdwen, node)
		pci_scan_fow_pawity_ewwow(pbm, bus);
}
