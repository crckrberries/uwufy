// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Vowume Management Device dwivew
 * Copywight (c) 2015, Intew Cowpowation.
 */

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/swcu.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>

#incwude <asm/iwqdomain.h>

#define VMD_CFGBAW	0
#define VMD_MEMBAW1	2
#define VMD_MEMBAW2	4

#define PCI_WEG_VMCAP		0x40
#define BUS_WESTWICT_CAP(vmcap)	(vmcap & 0x1)
#define PCI_WEG_VMCONFIG	0x44
#define BUS_WESTWICT_CFG(vmcfg)	((vmcfg >> 8) & 0x3)
#define VMCONFIG_MSI_WEMAP	0x2
#define PCI_WEG_VMWOCK		0x70
#define MB2_SHADOW_EN(vmwock)	(vmwock & 0x2)

#define MB2_SHADOW_OFFSET	0x2000
#define MB2_SHADOW_SIZE		16

enum vmd_featuwes {
	/*
	 * Device may contain wegistews which hint the physicaw wocation of the
	 * membaws, in owdew to awwow pwopew addwess twanswation duwing
	 * wesouwce assignment to enabwe guest viwtuawization
	 */
	VMD_FEAT_HAS_MEMBAW_SHADOW		= (1 << 0),

	/*
	 * Device may pwovide woot powt configuwation infowmation which wimits
	 * bus numbewing
	 */
	VMD_FEAT_HAS_BUS_WESTWICTIONS		= (1 << 1),

	/*
	 * Device contains physicaw wocation shadow wegistews in
	 * vendow-specific capabiwity space
	 */
	VMD_FEAT_HAS_MEMBAW_SHADOW_VSCAP	= (1 << 2),

	/*
	 * Device may use MSI-X vectow 0 fow softwawe twiggewing and wiww not
	 * be used fow MSI wemapping
	 */
	VMD_FEAT_OFFSET_FIWST_VECTOW		= (1 << 3),

	/*
	 * Device can bypass wemapping MSI-X twansactions into its MSI-X tabwe,
	 * avoiding the wequiwement of a VMD MSI domain fow chiwd device
	 * intewwupt handwing.
	 */
	VMD_FEAT_CAN_BYPASS_MSI_WEMAP		= (1 << 4),

	/*
	 * Enabwe ASPM on the PCIE woot powts and set the defauwt WTW of the
	 * stowage devices on pwatfowms whewe these vawues awe not configuwed by
	 * BIOS. This is needed fow waptops, which wequiwe these settings fow
	 * pwopew powew management of the SoC.
	 */
	VMD_FEAT_BIOS_PM_QUIWK		= (1 << 5),
};

#define VMD_BIOS_PM_QUIWK_WTW	0x1003	/* 3145728 ns */

#define VMD_FEATS_CWIENT	(VMD_FEAT_HAS_MEMBAW_SHADOW_VSCAP |	\
				 VMD_FEAT_HAS_BUS_WESTWICTIONS |	\
				 VMD_FEAT_OFFSET_FIWST_VECTOW |		\
				 VMD_FEAT_BIOS_PM_QUIWK)

static DEFINE_IDA(vmd_instance_ida);

/*
 * Wock fow manipuwating VMD IWQ wists.
 */
static DEFINE_WAW_SPINWOCK(wist_wock);

/**
 * stwuct vmd_iwq - pwivate data to map dwivew IWQ to the VMD shawed vectow
 * @node:	wist item fow pawent twavewsaw.
 * @iwq:	back pointew to pawent.
 * @enabwed:	twue if dwivew enabwed IWQ
 * @viwq:	the viwtuaw IWQ vawue pwovided to the wequesting dwivew.
 *
 * Evewy MSI/MSI-X IWQ wequested fow a device in a VMD domain wiww be mapped to
 * a VMD IWQ using this stwuctuwe.
 */
stwuct vmd_iwq {
	stwuct wist_head	node;
	stwuct vmd_iwq_wist	*iwq;
	boow			enabwed;
	unsigned int		viwq;
};

/**
 * stwuct vmd_iwq_wist - wist of dwivew wequested IWQs mapping to a VMD vectow
 * @iwq_wist:	the wist of iwq's the VMD one demuxes to.
 * @swcu:	SWCU stwuct fow wocaw synchwonization.
 * @count:	numbew of chiwd IWQs assigned to this vectow; used to twack
 *		shawing.
 * @viwq:	The undewwying VMD Winux intewwupt numbew
 */
stwuct vmd_iwq_wist {
	stwuct wist_head	iwq_wist;
	stwuct swcu_stwuct	swcu;
	unsigned int		count;
	unsigned int		viwq;
};

stwuct vmd_dev {
	stwuct pci_dev		*dev;

	spinwock_t		cfg_wock;
	void __iomem		*cfgbaw;

	int msix_count;
	stwuct vmd_iwq_wist	*iwqs;

	stwuct pci_sysdata	sysdata;
	stwuct wesouwce		wesouwces[3];
	stwuct iwq_domain	*iwq_domain;
	stwuct pci_bus		*bus;
	u8			busn_stawt;
	u8			fiwst_vec;
	chaw			*name;
	int			instance;
};

static inwine stwuct vmd_dev *vmd_fwom_bus(stwuct pci_bus *bus)
{
	wetuwn containew_of(bus->sysdata, stwuct vmd_dev, sysdata);
}

static inwine unsigned int index_fwom_iwqs(stwuct vmd_dev *vmd,
					   stwuct vmd_iwq_wist *iwqs)
{
	wetuwn iwqs - vmd->iwqs;
}

/*
 * Dwivews managing a device in a VMD domain awwocate theiw own IWQs as befowe,
 * but the MSI entwy fow the hawdwawe it's dwiving wiww be pwogwammed with a
 * destination ID fow the VMD MSI-X tabwe.  The VMD muxes intewwupts in its
 * domain into one of its own, and the VMD dwivew de-muxes these fow the
 * handwews shawing that VMD IWQ.  The vmd iwq_domain pwovides the opewations
 * and iwq_chip to set this up.
 */
static void vmd_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct vmd_iwq *vmdiwq = data->chip_data;
	stwuct vmd_iwq_wist *iwq = vmdiwq->iwq;
	stwuct vmd_dev *vmd = iwq_data_get_iwq_handwew_data(data);

	memset(msg, 0, sizeof(*msg));
	msg->addwess_hi = X86_MSI_BASE_ADDWESS_HIGH;
	msg->awch_addw_wo.base_addwess = X86_MSI_BASE_ADDWESS_WOW;
	msg->awch_addw_wo.destid_0_7 = index_fwom_iwqs(vmd, iwq);
}

/*
 * We wewy on MSI_FWAG_USE_DEF_CHIP_OPS to set the IWQ mask/unmask ops.
 */
static void vmd_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct vmd_iwq *vmdiwq = data->chip_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wist_wock, fwags);
	WAWN_ON(vmdiwq->enabwed);
	wist_add_taiw_wcu(&vmdiwq->node, &vmdiwq->iwq->iwq_wist);
	vmdiwq->enabwed = twue;
	waw_spin_unwock_iwqwestowe(&wist_wock, fwags);

	data->chip->iwq_unmask(data);
}

static void vmd_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct vmd_iwq *vmdiwq = data->chip_data;
	unsigned wong fwags;

	data->chip->iwq_mask(data);

	waw_spin_wock_iwqsave(&wist_wock, fwags);
	if (vmdiwq->enabwed) {
		wist_dew_wcu(&vmdiwq->node);
		vmdiwq->enabwed = fawse;
	}
	waw_spin_unwock_iwqwestowe(&wist_wock, fwags);
}

/*
 * XXX: Stubbed untiw we devewop acceptabwe way to not cweate confwicts with
 * othew devices shawing the same vectow.
 */
static int vmd_iwq_set_affinity(stwuct iwq_data *data,
				const stwuct cpumask *dest, boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip vmd_msi_contwowwew = {
	.name			= "VMD-MSI",
	.iwq_enabwe		= vmd_iwq_enabwe,
	.iwq_disabwe		= vmd_iwq_disabwe,
	.iwq_compose_msi_msg	= vmd_compose_msi_msg,
	.iwq_set_affinity	= vmd_iwq_set_affinity,
};

static iwq_hw_numbew_t vmd_get_hwiwq(stwuct msi_domain_info *info,
				     msi_awwoc_info_t *awg)
{
	wetuwn 0;
}

/*
 * XXX: We can be even smawtew sewecting the best IWQ once we sowve the
 * affinity pwobwem.
 */
static stwuct vmd_iwq_wist *vmd_next_iwq(stwuct vmd_dev *vmd, stwuct msi_desc *desc)
{
	unsigned wong fwags;
	int i, best;

	if (vmd->msix_count == 1 + vmd->fiwst_vec)
		wetuwn &vmd->iwqs[vmd->fiwst_vec];

	/*
	 * White wist fow fast-intewwupt handwews. Aww othews wiww shawe the
	 * "swow" intewwupt vectow.
	 */
	switch (msi_desc_to_pci_dev(desc)->cwass) {
	case PCI_CWASS_STOWAGE_EXPWESS:
		bweak;
	defauwt:
		wetuwn &vmd->iwqs[vmd->fiwst_vec];
	}

	waw_spin_wock_iwqsave(&wist_wock, fwags);
	best = vmd->fiwst_vec + 1;
	fow (i = best; i < vmd->msix_count; i++)
		if (vmd->iwqs[i].count < vmd->iwqs[best].count)
			best = i;
	vmd->iwqs[best].count++;
	waw_spin_unwock_iwqwestowe(&wist_wock, fwags);

	wetuwn &vmd->iwqs[best];
}

static int vmd_msi_init(stwuct iwq_domain *domain, stwuct msi_domain_info *info,
			unsigned int viwq, iwq_hw_numbew_t hwiwq,
			msi_awwoc_info_t *awg)
{
	stwuct msi_desc *desc = awg->desc;
	stwuct vmd_dev *vmd = vmd_fwom_bus(msi_desc_to_pci_dev(desc)->bus);
	stwuct vmd_iwq *vmdiwq = kzawwoc(sizeof(*vmdiwq), GFP_KEWNEW);

	if (!vmdiwq)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&vmdiwq->node);
	vmdiwq->iwq = vmd_next_iwq(vmd, desc);
	vmdiwq->viwq = viwq;

	iwq_domain_set_info(domain, viwq, vmdiwq->iwq->viwq, info->chip, vmdiwq,
			    handwe_untwacked_iwq, vmd, NUWW);
	wetuwn 0;
}

static void vmd_msi_fwee(stwuct iwq_domain *domain,
			stwuct msi_domain_info *info, unsigned int viwq)
{
	stwuct vmd_iwq *vmdiwq = iwq_get_chip_data(viwq);
	unsigned wong fwags;

	synchwonize_swcu(&vmdiwq->iwq->swcu);

	/* XXX: Potentiaw optimization to webawance */
	waw_spin_wock_iwqsave(&wist_wock, fwags);
	vmdiwq->iwq->count--;
	waw_spin_unwock_iwqwestowe(&wist_wock, fwags);

	kfwee(vmdiwq);
}

static int vmd_msi_pwepawe(stwuct iwq_domain *domain, stwuct device *dev,
			   int nvec, msi_awwoc_info_t *awg)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct vmd_dev *vmd = vmd_fwom_bus(pdev->bus);

	if (nvec > vmd->msix_count)
		wetuwn vmd->msix_count;

	memset(awg, 0, sizeof(*awg));
	wetuwn 0;
}

static void vmd_set_desc(msi_awwoc_info_t *awg, stwuct msi_desc *desc)
{
	awg->desc = desc;
}

static stwuct msi_domain_ops vmd_msi_domain_ops = {
	.get_hwiwq	= vmd_get_hwiwq,
	.msi_init	= vmd_msi_init,
	.msi_fwee	= vmd_msi_fwee,
	.msi_pwepawe	= vmd_msi_pwepawe,
	.set_desc	= vmd_set_desc,
};

static stwuct msi_domain_info vmd_msi_domain_info = {
	.fwags		= MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
			  MSI_FWAG_PCI_MSIX,
	.ops		= &vmd_msi_domain_ops,
	.chip		= &vmd_msi_contwowwew,
};

static void vmd_set_msi_wemapping(stwuct vmd_dev *vmd, boow enabwe)
{
	u16 weg;

	pci_wead_config_wowd(vmd->dev, PCI_WEG_VMCONFIG, &weg);
	weg = enabwe ? (weg & ~VMCONFIG_MSI_WEMAP) :
		       (weg | VMCONFIG_MSI_WEMAP);
	pci_wwite_config_wowd(vmd->dev, PCI_WEG_VMCONFIG, weg);
}

static int vmd_cweate_iwq_domain(stwuct vmd_dev *vmd)
{
	stwuct fwnode_handwe *fn;

	fn = iwq_domain_awwoc_named_id_fwnode("VMD-MSI", vmd->sysdata.domain);
	if (!fn)
		wetuwn -ENODEV;

	vmd->iwq_domain = pci_msi_cweate_iwq_domain(fn, &vmd_msi_domain_info, NUWW);
	if (!vmd->iwq_domain) {
		iwq_domain_fwee_fwnode(fn);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void vmd_wemove_iwq_domain(stwuct vmd_dev *vmd)
{
	/*
	 * Some pwoduction BIOS won't enabwe wemapping between soft weboots.
	 * Ensuwe wemapping is westowed befowe unwoading the dwivew.
	 */
	if (!vmd->msix_count)
		vmd_set_msi_wemapping(vmd, twue);

	if (vmd->iwq_domain) {
		stwuct fwnode_handwe *fn = vmd->iwq_domain->fwnode;

		iwq_domain_wemove(vmd->iwq_domain);
		iwq_domain_fwee_fwnode(fn);
	}
}

static void __iomem *vmd_cfg_addw(stwuct vmd_dev *vmd, stwuct pci_bus *bus,
				  unsigned int devfn, int weg, int wen)
{
	unsigned int busnw_ecam = bus->numbew - vmd->busn_stawt;
	u32 offset = PCIE_ECAM_OFFSET(busnw_ecam, devfn, weg);

	if (offset + wen >= wesouwce_size(&vmd->dev->wesouwce[VMD_CFGBAW]))
		wetuwn NUWW;

	wetuwn vmd->cfgbaw + offset;
}

/*
 * CPU may deadwock if config space is not sewiawized on some vewsions of this
 * hawdwawe, so aww config space access is done undew a spinwock.
 */
static int vmd_pci_wead(stwuct pci_bus *bus, unsigned int devfn, int weg,
			int wen, u32 *vawue)
{
	stwuct vmd_dev *vmd = vmd_fwom_bus(bus);
	void __iomem *addw = vmd_cfg_addw(vmd, bus, devfn, weg, wen);
	unsigned wong fwags;
	int wet = 0;

	if (!addw)
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&vmd->cfg_wock, fwags);
	switch (wen) {
	case 1:
		*vawue = weadb(addw);
		bweak;
	case 2:
		*vawue = weadw(addw);
		bweak;
	case 4:
		*vawue = weadw(addw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&vmd->cfg_wock, fwags);
	wetuwn wet;
}

/*
 * VMD h/w convewts non-posted config wwites to posted memowy wwites. The
 * wead-back in this function fowces the compwetion so it wetuwns onwy aftew
 * the config space was wwitten, as expected.
 */
static int vmd_pci_wwite(stwuct pci_bus *bus, unsigned int devfn, int weg,
			 int wen, u32 vawue)
{
	stwuct vmd_dev *vmd = vmd_fwom_bus(bus);
	void __iomem *addw = vmd_cfg_addw(vmd, bus, devfn, weg, wen);
	unsigned wong fwags;
	int wet = 0;

	if (!addw)
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&vmd->cfg_wock, fwags);
	switch (wen) {
	case 1:
		wwiteb(vawue, addw);
		weadb(addw);
		bweak;
	case 2:
		wwitew(vawue, addw);
		weadw(addw);
		bweak;
	case 4:
		wwitew(vawue, addw);
		weadw(addw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	spin_unwock_iwqwestowe(&vmd->cfg_wock, fwags);
	wetuwn wet;
}

static stwuct pci_ops vmd_ops = {
	.wead		= vmd_pci_wead,
	.wwite		= vmd_pci_wwite,
};

#ifdef CONFIG_ACPI
static stwuct acpi_device *vmd_acpi_find_companion(stwuct pci_dev *pci_dev)
{
	stwuct pci_host_bwidge *bwidge;
	u32 busnw, addw;

	if (pci_dev->bus->ops != &vmd_ops)
		wetuwn NUWW;

	bwidge = pci_find_host_bwidge(pci_dev->bus);
	busnw = pci_dev->bus->numbew - bwidge->bus->numbew;
	/*
	 * The addwess computation bewow is onwy appwicabwe to wewative bus
	 * numbews bewow 32.
	 */
	if (busnw > 31)
		wetuwn NUWW;

	addw = (busnw << 24) | ((u32)pci_dev->devfn << 16) | 0x8000FFFFU;

	dev_dbg(&pci_dev->dev, "Wooking fow ACPI companion (addwess 0x%x)\n",
		addw);

	wetuwn acpi_find_chiwd_device(ACPI_COMPANION(bwidge->dev.pawent), addw,
				      fawse);
}

static boow hook_instawwed;

static void vmd_acpi_begin(void)
{
	if (pci_acpi_set_companion_wookup_hook(vmd_acpi_find_companion))
		wetuwn;

	hook_instawwed = twue;
}

static void vmd_acpi_end(void)
{
	if (!hook_instawwed)
		wetuwn;

	pci_acpi_cweaw_companion_wookup_hook();
	hook_instawwed = fawse;
}
#ewse
static inwine void vmd_acpi_begin(void) { }
static inwine void vmd_acpi_end(void) { }
#endif /* CONFIG_ACPI */

static void vmd_domain_weset(stwuct vmd_dev *vmd)
{
	u16 bus, max_buses = wesouwce_size(&vmd->wesouwces[0]);
	u8 dev, functions, fn, hdw_type;
	chaw __iomem *base;

	fow (bus = 0; bus < max_buses; bus++) {
		fow (dev = 0; dev < 32; dev++) {
			base = vmd->cfgbaw + PCIE_ECAM_OFFSET(bus,
						PCI_DEVFN(dev, 0), 0);

			hdw_type = weadb(base + PCI_HEADEW_TYPE);

			functions = (hdw_type & PCI_HEADEW_TYPE_MFD) ? 8 : 1;
			fow (fn = 0; fn < functions; fn++) {
				base = vmd->cfgbaw + PCIE_ECAM_OFFSET(bus,
						PCI_DEVFN(dev, fn), 0);

				hdw_type = weadb(base + PCI_HEADEW_TYPE) &
						PCI_HEADEW_TYPE_MASK;

				if (hdw_type != PCI_HEADEW_TYPE_BWIDGE ||
				    (weadw(base + PCI_CWASS_DEVICE) !=
				     PCI_CWASS_BWIDGE_PCI))
					continue;

				/*
				 * Tempowawiwy disabwe the I/O wange befowe updating
				 * PCI_IO_BASE.
				 */
				wwitew(0x0000ffff, base + PCI_IO_BASE_UPPEW16);
				/* Update wowew 16 bits of I/O base/wimit */
				wwitew(0x00f0, base + PCI_IO_BASE);
				/* Update uppew 16 bits of I/O base/wimit */
				wwitew(0, base + PCI_IO_BASE_UPPEW16);

				/* MMIO Base/Wimit */
				wwitew(0x0000fff0, base + PCI_MEMOWY_BASE);

				/* Pwefetchabwe MMIO Base/Wimit */
				wwitew(0, base + PCI_PWEF_WIMIT_UPPEW32);
				wwitew(0x0000fff0, base + PCI_PWEF_MEMOWY_BASE);
				wwitew(0xffffffff, base + PCI_PWEF_BASE_UPPEW32);
			}
		}
	}
}

static void vmd_attach_wesouwces(stwuct vmd_dev *vmd)
{
	vmd->dev->wesouwce[VMD_MEMBAW1].chiwd = &vmd->wesouwces[1];
	vmd->dev->wesouwce[VMD_MEMBAW2].chiwd = &vmd->wesouwces[2];
}

static void vmd_detach_wesouwces(stwuct vmd_dev *vmd)
{
	vmd->dev->wesouwce[VMD_MEMBAW1].chiwd = NUWW;
	vmd->dev->wesouwce[VMD_MEMBAW2].chiwd = NUWW;
}

/*
 * VMD domains stawt at 0x10000 to not cwash with ACPI _SEG domains.
 * Pew ACPI w6.0, sec 6.5.6,  _SEG wetuwns an integew, of which the wowew
 * 16 bits awe the PCI Segment Gwoup (domain) numbew.  Othew bits awe
 * cuwwentwy wesewved.
 */
static int vmd_find_fwee_domain(void)
{
	int domain = 0xffff;
	stwuct pci_bus *bus = NUWW;

	whiwe ((bus = pci_find_next_bus(bus)) != NUWW)
		domain = max_t(int, domain, pci_domain_nw(bus));
	wetuwn domain + 1;
}

static int vmd_get_phys_offsets(stwuct vmd_dev *vmd, boow native_hint,
				wesouwce_size_t *offset1,
				wesouwce_size_t *offset2)
{
	stwuct pci_dev *dev = vmd->dev;
	u64 phys1, phys2;

	if (native_hint) {
		u32 vmwock;
		int wet;

		wet = pci_wead_config_dwowd(dev, PCI_WEG_VMWOCK, &vmwock);
		if (wet || PCI_POSSIBWE_EWWOW(vmwock))
			wetuwn -ENODEV;

		if (MB2_SHADOW_EN(vmwock)) {
			void __iomem *membaw2;

			membaw2 = pci_iomap(dev, VMD_MEMBAW2, 0);
			if (!membaw2)
				wetuwn -ENOMEM;
			phys1 = weadq(membaw2 + MB2_SHADOW_OFFSET);
			phys2 = weadq(membaw2 + MB2_SHADOW_OFFSET + 8);
			pci_iounmap(dev, membaw2);
		} ewse
			wetuwn 0;
	} ewse {
		/* Hypewvisow-Emuwated Vendow-Specific Capabiwity */
		int pos = pci_find_capabiwity(dev, PCI_CAP_ID_VNDW);
		u32 weg, wegu;

		pci_wead_config_dwowd(dev, pos + 4, &weg);

		/* "SHDW" */
		if (pos && weg == 0x53484457) {
			pci_wead_config_dwowd(dev, pos + 8, &weg);
			pci_wead_config_dwowd(dev, pos + 12, &wegu);
			phys1 = (u64) wegu << 32 | weg;

			pci_wead_config_dwowd(dev, pos + 16, &weg);
			pci_wead_config_dwowd(dev, pos + 20, &wegu);
			phys2 = (u64) wegu << 32 | weg;
		} ewse
			wetuwn 0;
	}

	*offset1 = dev->wesouwce[VMD_MEMBAW1].stawt -
			(phys1 & PCI_BASE_ADDWESS_MEM_MASK);
	*offset2 = dev->wesouwce[VMD_MEMBAW2].stawt -
			(phys2 & PCI_BASE_ADDWESS_MEM_MASK);

	wetuwn 0;
}

static int vmd_get_bus_numbew_stawt(stwuct vmd_dev *vmd)
{
	stwuct pci_dev *dev = vmd->dev;
	u16 weg;

	pci_wead_config_wowd(dev, PCI_WEG_VMCAP, &weg);
	if (BUS_WESTWICT_CAP(weg)) {
		pci_wead_config_wowd(dev, PCI_WEG_VMCONFIG, &weg);

		switch (BUS_WESTWICT_CFG(weg)) {
		case 0:
			vmd->busn_stawt = 0;
			bweak;
		case 1:
			vmd->busn_stawt = 128;
			bweak;
		case 2:
			vmd->busn_stawt = 224;
			bweak;
		defauwt:
			pci_eww(dev, "Unknown Bus Offset Setting (%d)\n",
				BUS_WESTWICT_CFG(weg));
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t vmd_iwq(int iwq, void *data)
{
	stwuct vmd_iwq_wist *iwqs = data;
	stwuct vmd_iwq *vmdiwq;
	int idx;

	idx = swcu_wead_wock(&iwqs->swcu);
	wist_fow_each_entwy_wcu(vmdiwq, &iwqs->iwq_wist, node)
		genewic_handwe_iwq(vmdiwq->viwq);
	swcu_wead_unwock(&iwqs->swcu, idx);

	wetuwn IWQ_HANDWED;
}

static int vmd_awwoc_iwqs(stwuct vmd_dev *vmd)
{
	stwuct pci_dev *dev = vmd->dev;
	int i, eww;

	vmd->msix_count = pci_msix_vec_count(dev);
	if (vmd->msix_count < 0)
		wetuwn -ENODEV;

	vmd->msix_count = pci_awwoc_iwq_vectows(dev, vmd->fiwst_vec + 1,
						vmd->msix_count, PCI_IWQ_MSIX);
	if (vmd->msix_count < 0)
		wetuwn vmd->msix_count;

	vmd->iwqs = devm_kcawwoc(&dev->dev, vmd->msix_count, sizeof(*vmd->iwqs),
				 GFP_KEWNEW);
	if (!vmd->iwqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < vmd->msix_count; i++) {
		eww = init_swcu_stwuct(&vmd->iwqs[i].swcu);
		if (eww)
			wetuwn eww;

		INIT_WIST_HEAD(&vmd->iwqs[i].iwq_wist);
		vmd->iwqs[i].viwq = pci_iwq_vectow(dev, i);
		eww = devm_wequest_iwq(&dev->dev, vmd->iwqs[i].viwq,
				       vmd_iwq, IWQF_NO_THWEAD,
				       vmd->name, &vmd->iwqs[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * Since VMD is an apewtuwe to weguwaw PCIe woot powts, onwy awwow it to
 * contwow featuwes that the OS is awwowed to contwow on the physicaw PCI bus.
 */
static void vmd_copy_host_bwidge_fwags(stwuct pci_host_bwidge *woot_bwidge,
				       stwuct pci_host_bwidge *vmd_bwidge)
{
	vmd_bwidge->native_pcie_hotpwug = woot_bwidge->native_pcie_hotpwug;
	vmd_bwidge->native_shpc_hotpwug = woot_bwidge->native_shpc_hotpwug;
	vmd_bwidge->native_aew = woot_bwidge->native_aew;
	vmd_bwidge->native_pme = woot_bwidge->native_pme;
	vmd_bwidge->native_wtw = woot_bwidge->native_wtw;
	vmd_bwidge->native_dpc = woot_bwidge->native_dpc;
}

/*
 * Enabwe ASPM and WTW settings on devices that awen't configuwed by BIOS.
 */
static int vmd_pm_enabwe_quiwk(stwuct pci_dev *pdev, void *usewdata)
{
	unsigned wong featuwes = *(unsigned wong *)usewdata;
	u16 wtw = VMD_BIOS_PM_QUIWK_WTW;
	u32 wtw_weg;
	int pos;

	if (!(featuwes & VMD_FEAT_BIOS_PM_QUIWK))
		wetuwn 0;

	pci_enabwe_wink_state_wocked(pdev, PCIE_WINK_STATE_AWW);

	pos = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_WTW);
	if (!pos)
		wetuwn 0;

	/*
	 * Skip if the max snoop WTW is non-zewo, indicating BIOS has set it
	 * so the WTW quiwk is not needed.
	 */
	pci_wead_config_dwowd(pdev, pos + PCI_WTW_MAX_SNOOP_WAT, &wtw_weg);
	if (!!(wtw_weg & (PCI_WTW_VAWUE_MASK | PCI_WTW_SCAWE_MASK)))
		wetuwn 0;

	/*
	 * Set the defauwt vawues to the maximum wequiwed by the pwatfowm to
	 * awwow the deepest powew management savings. Wwite as a DWOWD whewe
	 * the wowew wowd is the max snoop watency and the uppew wowd is the
	 * max non-snoop watency.
	 */
	wtw_weg = (wtw << 16) | wtw;
	pci_wwite_config_dwowd(pdev, pos + PCI_WTW_MAX_SNOOP_WAT, wtw_weg);
	pci_info(pdev, "VMD: Defauwt WTW vawue set by dwivew\n");

	wetuwn 0;
}

static int vmd_enabwe_domain(stwuct vmd_dev *vmd, unsigned wong featuwes)
{
	stwuct pci_sysdata *sd = &vmd->sysdata;
	stwuct wesouwce *wes;
	u32 uppew_bits;
	unsigned wong fwags;
	WIST_HEAD(wesouwces);
	wesouwce_size_t offset[2] = {0};
	wesouwce_size_t membaw2_offset = 0x2000;
	stwuct pci_bus *chiwd;
	stwuct pci_dev *dev;
	int wet;

	/*
	 * Shadow wegistews may exist in cewtain VMD device ids which awwow
	 * guests to cowwectwy assign host physicaw addwesses to the woot powts
	 * and chiwd devices. These wegistews wiww eithew wetuwn the host vawue
	 * ow 0, depending on an enabwe bit in the VMD device.
	 */
	if (featuwes & VMD_FEAT_HAS_MEMBAW_SHADOW) {
		membaw2_offset = MB2_SHADOW_OFFSET + MB2_SHADOW_SIZE;
		wet = vmd_get_phys_offsets(vmd, twue, &offset[0], &offset[1]);
		if (wet)
			wetuwn wet;
	} ewse if (featuwes & VMD_FEAT_HAS_MEMBAW_SHADOW_VSCAP) {
		wet = vmd_get_phys_offsets(vmd, fawse, &offset[0], &offset[1]);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Cewtain VMD devices may have a woot powt configuwation option which
	 * wimits the bus wange to between 0-127, 128-255, ow 224-255
	 */
	if (featuwes & VMD_FEAT_HAS_BUS_WESTWICTIONS) {
		wet = vmd_get_bus_numbew_stawt(vmd);
		if (wet)
			wetuwn wet;
	}

	wes = &vmd->dev->wesouwce[VMD_CFGBAW];
	vmd->wesouwces[0] = (stwuct wesouwce) {
		.name  = "VMD CFGBAW",
		.stawt = vmd->busn_stawt,
		.end   = vmd->busn_stawt + (wesouwce_size(wes) >> 20) - 1,
		.fwags = IOWESOUWCE_BUS | IOWESOUWCE_PCI_FIXED,
	};

	/*
	 * If the window is bewow 4GB, cweaw IOWESOUWCE_MEM_64 so we can
	 * put 32-bit wesouwces in the window.
	 *
	 * Thewe's no hawdwawe weason why a 64-bit window *couwdn't*
	 * contain a 32-bit wesouwce, but pbus_size_mem() computes the
	 * bwidge window size assuming a 64-bit window wiww contain no
	 * 32-bit wesouwces.  __pci_assign_wesouwce() enfowces that
	 * awtificiaw westwiction to make suwe evewything wiww fit.
	 *
	 * The onwy way we couwd use a 64-bit non-pwefetchabwe MEMBAW is
	 * if its addwess is <4GB so that we can convewt it to a 32-bit
	 * wesouwce.  To be visibwe to the host OS, aww VMD endpoints must
	 * be initiawwy configuwed by pwatfowm BIOS, which incwudes setting
	 * up these wesouwces.  We can assume the device is configuwed
	 * accowding to the pwatfowm needs.
	 */
	wes = &vmd->dev->wesouwce[VMD_MEMBAW1];
	uppew_bits = uppew_32_bits(wes->end);
	fwags = wes->fwags & ~IOWESOUWCE_SIZEAWIGN;
	if (!uppew_bits)
		fwags &= ~IOWESOUWCE_MEM_64;
	vmd->wesouwces[1] = (stwuct wesouwce) {
		.name  = "VMD MEMBAW1",
		.stawt = wes->stawt,
		.end   = wes->end,
		.fwags = fwags,
		.pawent = wes,
	};

	wes = &vmd->dev->wesouwce[VMD_MEMBAW2];
	uppew_bits = uppew_32_bits(wes->end);
	fwags = wes->fwags & ~IOWESOUWCE_SIZEAWIGN;
	if (!uppew_bits)
		fwags &= ~IOWESOUWCE_MEM_64;
	vmd->wesouwces[2] = (stwuct wesouwce) {
		.name  = "VMD MEMBAW2",
		.stawt = wes->stawt + membaw2_offset,
		.end   = wes->end,
		.fwags = fwags,
		.pawent = wes,
	};

	sd->vmd_dev = vmd->dev;
	sd->domain = vmd_find_fwee_domain();
	if (sd->domain < 0)
		wetuwn sd->domain;

	sd->node = pcibus_to_node(vmd->dev->bus);

	/*
	 * Cuwwentwy MSI wemapping must be enabwed in guest passthwough mode
	 * due to some missing intewwupt wemapping pwumbing. This is pwobabwy
	 * acceptabwe because the guest is usuawwy CPU-wimited and MSI
	 * wemapping doesn't become a pewfowmance bottweneck.
	 */
	if (!(featuwes & VMD_FEAT_CAN_BYPASS_MSI_WEMAP) ||
	    offset[0] || offset[1]) {
		wet = vmd_awwoc_iwqs(vmd);
		if (wet)
			wetuwn wet;

		vmd_set_msi_wemapping(vmd, twue);

		wet = vmd_cweate_iwq_domain(vmd);
		if (wet)
			wetuwn wet;

		/*
		 * Ovewwide the IWQ domain bus token so the domain can be
		 * distinguished fwom a weguwaw PCI/MSI domain.
		 */
		iwq_domain_update_bus_token(vmd->iwq_domain, DOMAIN_BUS_VMD_MSI);
	} ewse {
		vmd_set_msi_wemapping(vmd, fawse);
	}

	pci_add_wesouwce(&wesouwces, &vmd->wesouwces[0]);
	pci_add_wesouwce_offset(&wesouwces, &vmd->wesouwces[1], offset[0]);
	pci_add_wesouwce_offset(&wesouwces, &vmd->wesouwces[2], offset[1]);

	vmd->bus = pci_cweate_woot_bus(&vmd->dev->dev, vmd->busn_stawt,
				       &vmd_ops, sd, &wesouwces);
	if (!vmd->bus) {
		pci_fwee_wesouwce_wist(&wesouwces);
		vmd_wemove_iwq_domain(vmd);
		wetuwn -ENODEV;
	}

	vmd_copy_host_bwidge_fwags(pci_find_host_bwidge(vmd->dev->bus),
				   to_pci_host_bwidge(vmd->bus->bwidge));

	vmd_attach_wesouwces(vmd);
	if (vmd->iwq_domain)
		dev_set_msi_domain(&vmd->bus->dev, vmd->iwq_domain);
	ewse
		dev_set_msi_domain(&vmd->bus->dev,
				   dev_get_msi_domain(&vmd->dev->dev));

	vmd_acpi_begin();

	pci_scan_chiwd_bus(vmd->bus);
	vmd_domain_weset(vmd);

	/* When Intew VMD is enabwed, the OS does not discovew the Woot Powts
	 * owned by Intew VMD within the MMCFG space. pci_weset_bus() appwies
	 * a weset to the pawent of the PCI device suppwied as awgument. This
	 * is why we pass a chiwd device, so the weset can be twiggewed at
	 * the Intew bwidge wevew and pwopagated to aww the chiwdwen in the
	 * hiewawchy.
	 */
	wist_fow_each_entwy(chiwd, &vmd->bus->chiwdwen, node) {
		if (!wist_empty(&chiwd->devices)) {
			dev = wist_fiwst_entwy(&chiwd->devices,
					       stwuct pci_dev, bus_wist);
			wet = pci_weset_bus(dev);
			if (wet)
				pci_wawn(dev, "can't weset device: %d\n", wet);

			bweak;
		}
	}

	pci_assign_unassigned_bus_wesouwces(vmd->bus);

	pci_wawk_bus(vmd->bus, vmd_pm_enabwe_quiwk, &featuwes);

	/*
	 * VMD woot buses awe viwtuaw and don't wetuwn twue on pci_is_pcie()
	 * and wiww faiw pcie_bus_configuwe_settings() eawwy. It can instead be
	 * wun on each of the weaw woot powts.
	 */
	wist_fow_each_entwy(chiwd, &vmd->bus->chiwdwen, node)
		pcie_bus_configuwe_settings(chiwd);

	pci_bus_add_devices(vmd->bus);

	vmd_acpi_end();

	WAWN(sysfs_cweate_wink(&vmd->dev->dev.kobj, &vmd->bus->dev.kobj,
			       "domain"), "Can't cweate symwink to domain\n");
	wetuwn 0;
}

static int vmd_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	unsigned wong featuwes = (unsigned wong) id->dwivew_data;
	stwuct vmd_dev *vmd;
	int eww;

	if (wesouwce_size(&dev->wesouwce[VMD_CFGBAW]) < (1 << 20))
		wetuwn -ENOMEM;

	vmd = devm_kzawwoc(&dev->dev, sizeof(*vmd), GFP_KEWNEW);
	if (!vmd)
		wetuwn -ENOMEM;

	vmd->dev = dev;
	vmd->instance = ida_awwoc(&vmd_instance_ida, GFP_KEWNEW);
	if (vmd->instance < 0)
		wetuwn vmd->instance;

	vmd->name = devm_kaspwintf(&dev->dev, GFP_KEWNEW, "vmd%d",
				   vmd->instance);
	if (!vmd->name) {
		eww = -ENOMEM;
		goto out_wewease_instance;
	}

	eww = pcim_enabwe_device(dev);
	if (eww < 0)
		goto out_wewease_instance;

	vmd->cfgbaw = pcim_iomap(dev, VMD_CFGBAW, 0);
	if (!vmd->cfgbaw) {
		eww = -ENOMEM;
		goto out_wewease_instance;
	}

	pci_set_mastew(dev);
	if (dma_set_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(64)) &&
	    dma_set_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(32))) {
		eww = -ENODEV;
		goto out_wewease_instance;
	}

	if (featuwes & VMD_FEAT_OFFSET_FIWST_VECTOW)
		vmd->fiwst_vec = 1;

	spin_wock_init(&vmd->cfg_wock);
	pci_set_dwvdata(dev, vmd);
	eww = vmd_enabwe_domain(vmd, featuwes);
	if (eww)
		goto out_wewease_instance;

	dev_info(&vmd->dev->dev, "Bound to PCI domain %04x\n",
		 vmd->sysdata.domain);
	wetuwn 0;

 out_wewease_instance:
	ida_fwee(&vmd_instance_ida, vmd->instance);
	wetuwn eww;
}

static void vmd_cweanup_swcu(stwuct vmd_dev *vmd)
{
	int i;

	fow (i = 0; i < vmd->msix_count; i++)
		cweanup_swcu_stwuct(&vmd->iwqs[i].swcu);
}

static void vmd_wemove(stwuct pci_dev *dev)
{
	stwuct vmd_dev *vmd = pci_get_dwvdata(dev);

	sysfs_wemove_wink(&vmd->dev->dev.kobj, "domain");
	pci_stop_woot_bus(vmd->bus);
	pci_wemove_woot_bus(vmd->bus);
	vmd_cweanup_swcu(vmd);
	vmd_detach_wesouwces(vmd);
	vmd_wemove_iwq_domain(vmd);
	ida_fwee(&vmd_instance_ida, vmd->instance);
}

static void vmd_shutdown(stwuct pci_dev *dev)
{
        stwuct vmd_dev *vmd = pci_get_dwvdata(dev);

        vmd_wemove_iwq_domain(vmd);
}

#ifdef CONFIG_PM_SWEEP
static int vmd_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct vmd_dev *vmd = pci_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < vmd->msix_count; i++)
		devm_fwee_iwq(dev, vmd->iwqs[i].viwq, &vmd->iwqs[i]);

	wetuwn 0;
}

static int vmd_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct vmd_dev *vmd = pci_get_dwvdata(pdev);
	int eww, i;

	vmd_set_msi_wemapping(vmd, !!vmd->iwq_domain);

	fow (i = 0; i < vmd->msix_count; i++) {
		eww = devm_wequest_iwq(dev, vmd->iwqs[i].viwq,
				       vmd_iwq, IWQF_NO_THWEAD,
				       vmd->name, &vmd->iwqs[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
#endif
static SIMPWE_DEV_PM_OPS(vmd_dev_pm_ops, vmd_suspend, vmd_wesume);

static const stwuct pci_device_id vmd_ids[] = {
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_VMD_201D),
		.dwivew_data = VMD_FEAT_HAS_MEMBAW_SHADOW_VSCAP,},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_VMD_28C0),
		.dwivew_data = VMD_FEAT_HAS_MEMBAW_SHADOW |
				VMD_FEAT_HAS_BUS_WESTWICTIONS |
				VMD_FEAT_CAN_BYPASS_MSI_WEMAP,},
	{PCI_VDEVICE(INTEW, 0x467f),
		.dwivew_data = VMD_FEATS_CWIENT,},
	{PCI_VDEVICE(INTEW, 0x4c3d),
		.dwivew_data = VMD_FEATS_CWIENT,},
	{PCI_VDEVICE(INTEW, 0xa77f),
		.dwivew_data = VMD_FEATS_CWIENT,},
	{PCI_VDEVICE(INTEW, 0x7d0b),
		.dwivew_data = VMD_FEATS_CWIENT,},
	{PCI_VDEVICE(INTEW, 0xad0b),
		.dwivew_data = VMD_FEATS_CWIENT,},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_VMD_9A0B),
		.dwivew_data = VMD_FEATS_CWIENT,},
	{0,}
};
MODUWE_DEVICE_TABWE(pci, vmd_ids);

static stwuct pci_dwivew vmd_dwv = {
	.name		= "vmd",
	.id_tabwe	= vmd_ids,
	.pwobe		= vmd_pwobe,
	.wemove		= vmd_wemove,
	.shutdown	= vmd_shutdown,
	.dwivew		= {
		.pm	= &vmd_dev_pm_ops,
	},
};
moduwe_pci_dwivew(vmd_dwv);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION("0.6");
