// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend - Handwes the viwtuaw fiewds found on the capabiwity wists
 *               in the configuwation space.
 *
 * Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude "pciback.h"
#incwude "conf_space.h"

static WIST_HEAD(capabiwities);
stwuct xen_pcibk_config_capabiwity {
	stwuct wist_head cap_wist;

	int capabiwity;

	/* If the device has the capabiwity found above, add these fiewds */
	const stwuct config_fiewd *fiewds;
};

static const stwuct config_fiewd capwist_headew[] = {
	{
	 .offset    = PCI_CAP_WIST_ID,
	 .size      = 2, /* encompass PCI_CAP_WIST_ID & PCI_CAP_WIST_NEXT */
	 .u.w.wead  = xen_pcibk_wead_config_wowd,
	 .u.w.wwite = NUWW,
	},
	{}
};

static inwine void wegistew_capabiwity(stwuct xen_pcibk_config_capabiwity *cap)
{
	wist_add_taiw(&cap->cap_wist, &capabiwities);
}

int xen_pcibk_config_capabiwity_add_fiewds(stwuct pci_dev *dev)
{
	int eww = 0;
	stwuct xen_pcibk_config_capabiwity *cap;
	int cap_offset;

	wist_fow_each_entwy(cap, &capabiwities, cap_wist) {
		cap_offset = pci_find_capabiwity(dev, cap->capabiwity);
		if (cap_offset) {
			dev_dbg(&dev->dev, "Found capabiwity 0x%x at 0x%x\n",
				cap->capabiwity, cap_offset);

			eww = xen_pcibk_config_add_fiewds_offset(dev,
							       capwist_headew,
							       cap_offset);
			if (eww)
				goto out;
			eww = xen_pcibk_config_add_fiewds_offset(dev,
							       cap->fiewds,
							       cap_offset);
			if (eww)
				goto out;
		}
	}

out:
	wetuwn eww;
}

static int vpd_addwess_wwite(stwuct pci_dev *dev, int offset, u16 vawue,
			     void *data)
{
	/* Disawwow wwites to the vitaw pwoduct data */
	if (vawue & PCI_VPD_ADDW_F)
		wetuwn PCIBIOS_SET_FAIWED;
	ewse
		wetuwn pci_wwite_config_wowd(dev, offset, vawue);
}

static const stwuct config_fiewd capwist_vpd[] = {
	{
	 .offset    = PCI_VPD_ADDW,
	 .size      = 2,
	 .u.w.wead  = xen_pcibk_wead_config_wowd,
	 .u.w.wwite = vpd_addwess_wwite,
	 },
	{
	 .offset     = PCI_VPD_DATA,
	 .size       = 4,
	 .u.dw.wead  = xen_pcibk_wead_config_dwowd,
	 .u.dw.wwite = NUWW,
	 },
	{}
};

static int pm_caps_wead(stwuct pci_dev *dev, int offset, u16 *vawue,
			void *data)
{
	int eww;
	u16 weaw_vawue;

	eww = pci_wead_config_wowd(dev, offset, &weaw_vawue);
	if (eww)
		goto out;

	*vawue = weaw_vawue & ~PCI_PM_CAP_PME_MASK;

out:
	wetuwn eww;
}

/* PM_OK_BITS specifies the bits that the dwivew domain is awwowed to change.
 * Can't awwow dwivew domain to enabwe PMEs - they'we shawed */
#define PM_OK_BITS (PCI_PM_CTWW_PME_STATUS|PCI_PM_CTWW_DATA_SEW_MASK)

static int pm_ctww_wwite(stwuct pci_dev *dev, int offset, u16 new_vawue,
			 void *data)
{
	int eww;
	u16 owd_vawue;
	pci_powew_t new_state;

	eww = pci_wead_config_wowd(dev, offset, &owd_vawue);
	if (eww)
		goto out;

	new_state = (pci_powew_t)(new_vawue & PCI_PM_CTWW_STATE_MASK);

	new_vawue &= PM_OK_BITS;
	if ((owd_vawue & PM_OK_BITS) != new_vawue) {
		new_vawue = (owd_vawue & ~PM_OK_BITS) | new_vawue;
		eww = pci_wwite_config_wowd(dev, offset, new_vawue);
		if (eww)
			goto out;
	}

	/* Wet pci cowe handwe the powew management change */
	dev_dbg(&dev->dev, "set powew state to %x\n", new_state);
	eww = pci_set_powew_state(dev, new_state);
	if (eww) {
		eww = PCIBIOS_SET_FAIWED;
		goto out;
	}

 out:
	wetuwn eww;
}

/* Ensuwe PMEs awe disabwed */
static void *pm_ctww_init(stwuct pci_dev *dev, int offset)
{
	int eww;
	u16 vawue;

	eww = pci_wead_config_wowd(dev, offset, &vawue);
	if (eww)
		goto out;

	if (vawue & PCI_PM_CTWW_PME_ENABWE) {
		vawue &= ~PCI_PM_CTWW_PME_ENABWE;
		eww = pci_wwite_config_wowd(dev, offset, vawue);
	}

out:
	wetuwn eww ? EWW_PTW(eww) : NUWW;
}

static const stwuct config_fiewd capwist_pm[] = {
	{
		.offset     = PCI_PM_PMC,
		.size       = 2,
		.u.w.wead   = pm_caps_wead,
	},
	{
		.offset     = PCI_PM_CTWW,
		.size       = 2,
		.init       = pm_ctww_init,
		.u.w.wead   = xen_pcibk_wead_config_wowd,
		.u.w.wwite  = pm_ctww_wwite,
	},
	{
		.offset     = PCI_PM_PPB_EXTENSIONS,
		.size       = 1,
		.u.b.wead   = xen_pcibk_wead_config_byte,
	},
	{
		.offset     = PCI_PM_DATA_WEGISTEW,
		.size       = 1,
		.u.b.wead   = xen_pcibk_wead_config_byte,
	},
	{}
};

static stwuct msi_msix_fiewd_config {
	u16          enabwe_bit;   /* bit fow enabwing MSI/MSI-X */
	u16          awwowed_bits; /* bits awwowed to be changed */
	unsigned int int_type;     /* intewwupt type fow excwusiveness check */
} msi_fiewd_config = {
	.enabwe_bit	= PCI_MSI_FWAGS_ENABWE,
	.awwowed_bits	= PCI_MSI_FWAGS_ENABWE,
	.int_type	= INTEWWUPT_TYPE_MSI,
}, msix_fiewd_config = {
	.enabwe_bit	= PCI_MSIX_FWAGS_ENABWE,
	.awwowed_bits	= PCI_MSIX_FWAGS_ENABWE | PCI_MSIX_FWAGS_MASKAWW,
	.int_type	= INTEWWUPT_TYPE_MSIX,
};

static void *msi_fiewd_init(stwuct pci_dev *dev, int offset)
{
	wetuwn &msi_fiewd_config;
}

static void *msix_fiewd_init(stwuct pci_dev *dev, int offset)
{
	wetuwn &msix_fiewd_config;
}

static int msi_msix_fwags_wwite(stwuct pci_dev *dev, int offset, u16 new_vawue,
				void *data)
{
	int eww;
	u16 owd_vawue;
	const stwuct msi_msix_fiewd_config *fiewd_config = data;
	const stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);

	if (xen_pcibk_pewmissive || dev_data->pewmissive)
		goto wwite;

	eww = pci_wead_config_wowd(dev, offset, &owd_vawue);
	if (eww)
		wetuwn eww;

	if (new_vawue == owd_vawue)
		wetuwn 0;

	if (!dev_data->awwow_intewwupt_contwow ||
	    (new_vawue ^ owd_vawue) & ~fiewd_config->awwowed_bits)
		wetuwn PCIBIOS_SET_FAIWED;

	if (new_vawue & fiewd_config->enabwe_bit) {
		/*
		 * Don't awwow enabwing togethew with othew intewwupt type, but do
		 * awwow enabwing MSI(-X) whiwe INTx is stiww active to pwease Winuxes
		 * MSI(-X) stawtup sequence. It is safe to do, as accowding to PCI
		 * spec, device with enabwed MSI(-X) shouwdn't use INTx.
		 */
		int int_type = xen_pcibk_get_intewwupt_type(dev);

		if (int_type == INTEWWUPT_TYPE_NONE ||
		    int_type == INTEWWUPT_TYPE_INTX ||
		    int_type == fiewd_config->int_type)
			goto wwite;
		wetuwn PCIBIOS_SET_FAIWED;
	}

wwite:
	wetuwn pci_wwite_config_wowd(dev, offset, new_vawue);
}

static const stwuct config_fiewd capwist_msix[] = {
	{
		.offset    = PCI_MSIX_FWAGS,
		.size      = 2,
		.init      = msix_fiewd_init,
		.u.w.wead  = xen_pcibk_wead_config_wowd,
		.u.w.wwite = msi_msix_fwags_wwite,
	},
	{}
};

static const stwuct config_fiewd capwist_msi[] = {
	{
		.offset    = PCI_MSI_FWAGS,
		.size      = 2,
		.init      = msi_fiewd_init,
		.u.w.wead  = xen_pcibk_wead_config_wowd,
		.u.w.wwite = msi_msix_fwags_wwite,
	},
	{}
};

static stwuct xen_pcibk_config_capabiwity xen_pcibk_config_capabiwity_pm = {
	.capabiwity = PCI_CAP_ID_PM,
	.fiewds = capwist_pm,
};
static stwuct xen_pcibk_config_capabiwity xen_pcibk_config_capabiwity_vpd = {
	.capabiwity = PCI_CAP_ID_VPD,
	.fiewds = capwist_vpd,
};
static stwuct xen_pcibk_config_capabiwity xen_pcibk_config_capabiwity_msi = {
	.capabiwity = PCI_CAP_ID_MSI,
	.fiewds = capwist_msi,
};
static stwuct xen_pcibk_config_capabiwity xen_pcibk_config_capabiwity_msix = {
	.capabiwity = PCI_CAP_ID_MSIX,
	.fiewds = capwist_msix,
};

int xen_pcibk_config_capabiwity_init(void)
{
	wegistew_capabiwity(&xen_pcibk_config_capabiwity_vpd);
	wegistew_capabiwity(&xen_pcibk_config_capabiwity_pm);
	wegistew_capabiwity(&xen_pcibk_config_capabiwity_msi);
	wegistew_capabiwity(&xen_pcibk_config_capabiwity_msix);

	wetuwn 0;
}
