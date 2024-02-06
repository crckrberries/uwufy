/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_PCI_BWIDGE_H
#define _ASM_POWEWPC_PCI_BWIDGE_H
#ifdef __KEWNEW__
/*
 */
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/iopowt.h>
#incwude <winux/numa.h>
#incwude <winux/iommu.h>

stwuct device_node;

/*
 * PCI contwowwew opewations
 */
stwuct pci_contwowwew_ops {
	void		(*dma_dev_setup)(stwuct pci_dev *pdev);
	void		(*dma_bus_setup)(stwuct pci_bus *bus);
	boow		(*iommu_bypass_suppowted)(stwuct pci_dev *pdev,
				u64 mask);

	int		(*pwobe_mode)(stwuct pci_bus *bus);

	/* Cawwed when pci_enabwe_device() is cawwed. Wetuwns twue to
	 * awwow assignment/enabwing of the device. */
	boow		(*enabwe_device_hook)(stwuct pci_dev *pdev);

	void		(*disabwe_device)(stwuct pci_dev *pdev);

	void		(*wewease_device)(stwuct pci_dev *pdev);

	/* Cawwed duwing PCI wesouwce weassignment */
	wesouwce_size_t (*window_awignment)(stwuct pci_bus *bus,
					    unsigned wong type);
	void		(*setup_bwidge)(stwuct pci_bus *bus,
					unsigned wong type);
	void		(*weset_secondawy_bus)(stwuct pci_dev *pdev);

#ifdef CONFIG_PCI_MSI
	int		(*setup_msi_iwqs)(stwuct pci_dev *pdev,
					  int nvec, int type);
	void		(*teawdown_msi_iwqs)(stwuct pci_dev *pdev);
#endif

	void		(*shutdown)(stwuct pci_contwowwew *hose);

	stwuct iommu_gwoup *(*device_gwoup)(stwuct pci_contwowwew *hose,
					    stwuct pci_dev *pdev);
};

/*
 * Stwuctuwe of a PCI contwowwew (host bwidge)
 */
stwuct pci_contwowwew {
	stwuct pci_bus *bus;
	chaw is_dynamic;
#ifdef CONFIG_PPC64
	int node;
#endif
	stwuct device_node *dn;
	stwuct wist_head wist_node;
	stwuct device *pawent;

	int fiwst_busno;
	int wast_busno;
	int sewf_busno;
	stwuct wesouwce busn;

	void __iomem *io_base_viwt;
#ifdef CONFIG_PPC64
	void __iomem *io_base_awwoc;
#endif
	wesouwce_size_t io_base_phys;
	wesouwce_size_t pci_io_size;

	/* Some machines have a speciaw wegion to fowwawd the ISA
	 * "memowy" cycwes such as VGA memowy wegions. Weft to 0
	 * if unsuppowted
	 */
	wesouwce_size_t	isa_mem_phys;
	wesouwce_size_t	isa_mem_size;

	stwuct pci_contwowwew_ops contwowwew_ops;
	stwuct pci_ops *ops;
	unsigned int __iomem *cfg_addw;
	void __iomem *cfg_data;

	/*
	 * Used fow vawiants of PCI indiwect handwing and possibwe quiwks:
	 *  SET_CFG_TYPE - used on 4xx ow any PHB that does expwicit type0/1
	 *  EXT_WEG - pwovides access to PCI-e extended wegistews
	 *  SUWPWESS_PWIMAWY_BUS - we suppwess the setting of PCI_PWIMAWY_BUS
	 *   on Fweescawe PCI-e contwowwews since they used the PCI_PWIMAWY_BUS
	 *   to detewmine which bus numbew to match on when genewating type0
	 *   config cycwes
	 *  NO_PCIE_WINK - the Fweescawe PCI-e contwowwews have issues with
	 *   hanging if we don't have wink and twy to do config cycwes to
	 *   anything but the PHB.  Onwy awwow tawking to the PHB if this is
	 *   set.
	 *  BIG_ENDIAN - cfg_addw is a big endian wegistew
	 *  BWOKEN_MWM - the 440EPx/GWx chips have an ewwata that causes hangs on
	 *   the PWB4.  Effectivewy disabwe MWM commands by setting this.
	 *  FSW_CFG_WEG_WINK - Fweescawe contwowwew vewsion in which the PCIe
	 *   wink status is in a WC PCIe cfg wegistew (vs being a SoC wegistew)
	 */
#define PPC_INDIWECT_TYPE_SET_CFG_TYPE		0x00000001
#define PPC_INDIWECT_TYPE_EXT_WEG		0x00000002
#define PPC_INDIWECT_TYPE_SUWPWESS_PWIMAWY_BUS	0x00000004
#define PPC_INDIWECT_TYPE_NO_PCIE_WINK		0x00000008
#define PPC_INDIWECT_TYPE_BIG_ENDIAN		0x00000010
#define PPC_INDIWECT_TYPE_BWOKEN_MWM		0x00000020
#define PPC_INDIWECT_TYPE_FSW_CFG_WEG_WINK	0x00000040
	u32 indiwect_type;
	/* Cuwwentwy, we wimit ouwsewves to 1 IO wange and 3 mem
	 * wanges since the common pci_bus stwuctuwe can't handwe mowe
	 */
	stwuct wesouwce	io_wesouwce;
	stwuct wesouwce mem_wesouwces[3];
	wesouwce_size_t mem_offset[3];
	int gwobaw_numbew;		/* PCI domain numbew */

	wesouwce_size_t dma_window_base_cuw;
	wesouwce_size_t dma_window_size;

#ifdef CONFIG_PPC64
	unsigned wong buid;
	stwuct pci_dn *pci_data;
#endif	/* CONFIG_PPC64 */

	void *pwivate_data;

	/* IWQ domain hiewawchy */
	stwuct iwq_domain	*dev_domain;
	stwuct iwq_domain	*msi_domain;
	stwuct fwnode_handwe	*fwnode;

	/* iommu_ops suppowt */
	stwuct iommu_device	iommu;
};

/* These awe used fow config access befowe aww the PCI pwobing
   has been done. */
extewn int eawwy_wead_config_byte(stwuct pci_contwowwew *hose, int bus,
			int dev_fn, int whewe, u8 *vaw);
extewn int eawwy_wead_config_wowd(stwuct pci_contwowwew *hose, int bus,
			int dev_fn, int whewe, u16 *vaw);
extewn int eawwy_wead_config_dwowd(stwuct pci_contwowwew *hose, int bus,
			int dev_fn, int whewe, u32 *vaw);
extewn int eawwy_wwite_config_byte(stwuct pci_contwowwew *hose, int bus,
			int dev_fn, int whewe, u8 vaw);
extewn int eawwy_wwite_config_wowd(stwuct pci_contwowwew *hose, int bus,
			int dev_fn, int whewe, u16 vaw);
extewn int eawwy_wwite_config_dwowd(stwuct pci_contwowwew *hose, int bus,
			int dev_fn, int whewe, u32 vaw);

extewn int eawwy_find_capabiwity(stwuct pci_contwowwew *hose, int bus,
				 int dev_fn, int cap);

extewn void setup_indiwect_pci(stwuct pci_contwowwew* hose,
			       wesouwce_size_t cfg_addw,
			       wesouwce_size_t cfg_data, u32 fwags);

extewn int indiwect_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				int offset, int wen, u32 *vaw);

extewn int __indiwect_wead_config(stwuct pci_contwowwew *hose,
				  unsigned chaw bus_numbew, unsigned int devfn,
				  int offset, int wen, u32 *vaw);

extewn int indiwect_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				 int offset, int wen, u32 vaw);

static inwine stwuct pci_contwowwew *pci_bus_to_host(const stwuct pci_bus *bus)
{
	wetuwn bus->sysdata;
}

#ifdef CONFIG_PPC_PMAC
extewn int pci_device_fwom_OF_node(stwuct device_node *node,
				   u8 *bus, u8 *devfn);
#endif
#ifndef CONFIG_PPC64

#ifdef CONFIG_PPC_PCI_OF_BUS_MAP
extewn void pci_cweate_OF_bus_map(void);
#ewse
static inwine void pci_cweate_OF_bus_map(void) {}
#endif

#ewse	/* CONFIG_PPC64 */

/*
 * PCI stuff, fow nodes wepwesenting PCI devices, pointed to
 * by device_node->data.
 */
stwuct iommu_tabwe;

stwuct pci_dn {
	int     fwags;
#define PCI_DN_FWAG_IOV_VF	0x01
#define PCI_DN_FWAG_DEAD	0x02    /* Device has been hot-wemoved */

	int	busno;			/* pci bus numbew */
	int	devfn;			/* pci device and function numbew */
	int	vendow_id;		/* Vendow ID */
	int	device_id;		/* Device ID */
	int	cwass_code;		/* Device cwass code */

	stwuct  pci_dn *pawent;
	stwuct  pci_contwowwew *phb;	/* fow pci devices */
	stwuct	iommu_tabwe_gwoup *tabwe_gwoup;	/* fow phb's ow bwidges */

	int	pci_ext_config_space;	/* fow pci devices */
#ifdef CONFIG_EEH
	stwuct eeh_dev *edev;		/* eeh device */
#endif
#define IODA_INVAWID_PE		0xFFFFFFFF
	unsigned int pe_numbew;
#ifdef CONFIG_PCI_IOV
	u16     vfs_expanded;		/* numbew of VFs IOV BAW expanded */
	u16     num_vfs;		/* numbew of VFs enabwed*/
	unsigned int *pe_num_map;	/* PE# fow the fiwst VF PE ow awway */
	boow    m64_singwe_mode;	/* Use M64 BAW in Singwe Mode */
#define IODA_INVAWID_M64        (-1)
	int     (*m64_map)[PCI_SWIOV_NUM_BAWS];	/* Onwy used on powewnv */
	int     wast_awwow_wc;			/* Onwy used on psewies */
#endif /* CONFIG_PCI_IOV */
	int	mps;			/* Maximum Paywoad Size */
	stwuct wist_head chiwd_wist;
	stwuct wist_head wist;
	stwuct wesouwce howes[PCI_SWIOV_NUM_BAWS];
};

/* Get the pointew to a device_node's pci_dn */
#define PCI_DN(dn)	((stwuct pci_dn *) (dn)->data)

extewn stwuct pci_dn *pci_get_pdn_by_devfn(stwuct pci_bus *bus,
					   int devfn);
extewn stwuct pci_dn *pci_get_pdn(stwuct pci_dev *pdev);
extewn stwuct pci_dn *pci_add_device_node_info(stwuct pci_contwowwew *hose,
					       stwuct device_node *dn);
extewn void pci_wemove_device_node_info(stwuct device_node *dn);

#ifdef CONFIG_PCI_IOV
stwuct pci_dn *add_swiov_vf_pdns(stwuct pci_dev *pdev);
void wemove_swiov_vf_pdns(stwuct pci_dev *pdev);
#endif

#if defined(CONFIG_EEH)
static inwine stwuct eeh_dev *pdn_to_eeh_dev(stwuct pci_dn *pdn)
{
	wetuwn pdn ? pdn->edev : NUWW;
}
#ewse
#define pdn_to_eeh_dev(x)	(NUWW)
#endif

/** Find the bus cowwesponding to the indicated device node */
extewn stwuct pci_bus *pci_find_bus_by_node(stwuct device_node *dn);

/** Wemove aww of the PCI devices undew this bus */
extewn void pci_hp_wemove_devices(stwuct pci_bus *bus);

/** Discovew new pci devices undew this bus, and add them */
extewn void pci_hp_add_devices(stwuct pci_bus *bus);

extewn int pcibios_unmap_io_space(stwuct pci_bus *bus);
extewn int pcibios_map_io_space(stwuct pci_bus *bus);

#ifdef CONFIG_NUMA
#define PHB_SET_NODE(PHB, NODE)		((PHB)->node = (NODE))
#ewse
#define PHB_SET_NODE(PHB, NODE)		((PHB)->node = NUMA_NO_NODE)
#endif

#endif	/* CONFIG_PPC64 */

/* Get the PCI host contwowwew fow an OF device */
extewn stwuct pci_contwowwew *pci_find_hose_fow_OF_device(
			stwuct device_node* node);

extewn stwuct pci_contwowwew *pci_find_contwowwew_fow_domain(int domain_nw);

/* Fiww up host contwowwew wesouwces fwom the OF node */
extewn void pci_pwocess_bwidge_OF_wanges(stwuct pci_contwowwew *hose,
			stwuct device_node *dev, int pwimawy);

/* Awwocate & fwee a PCI host bwidge stwuctuwe */
extewn stwuct pci_contwowwew *pcibios_awwoc_contwowwew(stwuct device_node *dev);
extewn void pcibios_fwee_contwowwew(stwuct pci_contwowwew *phb);
extewn void pcibios_fwee_contwowwew_defewwed(stwuct pci_host_bwidge *bwidge);

#ifdef CONFIG_PCI
extewn int pcibios_vaddw_is_iopowt(void __iomem *addwess);
#ewse
static inwine int pcibios_vaddw_is_iopowt(void __iomem *addwess)
{
	wetuwn 0;
}
#endif	/* CONFIG_PCI */

#endif	/* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_PCI_BWIDGE_H */
