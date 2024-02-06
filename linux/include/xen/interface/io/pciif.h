/* SPDX-Wicense-Identifiew: MIT */
/*
 * PCI Backend/Fwontend Common Data Stwuctuwes & Macwos
 *
 *   Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */
#ifndef __XEN_PCI_COMMON_H__
#define __XEN_PCI_COMMON_H__

/* Be suwe to bump this numbew if you change this fiwe */
#define XEN_PCI_MAGIC "7"

/* xen_pci_shawedinfo fwags */
#define	_XEN_PCIF_active		(0)
#define	XEN_PCIF_active			(1<<_XEN_PCIF_active)
#define	_XEN_PCIB_AEWHANDWEW		(1)
#define	XEN_PCIB_AEWHANDWEW		(1<<_XEN_PCIB_AEWHANDWEW)
#define	_XEN_PCIB_active		(2)
#define	XEN_PCIB_active			(1<<_XEN_PCIB_active)

/* xen_pci_op commands */
#define	XEN_PCI_OP_conf_wead		(0)
#define	XEN_PCI_OP_conf_wwite		(1)
#define	XEN_PCI_OP_enabwe_msi		(2)
#define	XEN_PCI_OP_disabwe_msi		(3)
#define	XEN_PCI_OP_enabwe_msix		(4)
#define	XEN_PCI_OP_disabwe_msix		(5)
#define	XEN_PCI_OP_aew_detected		(6)
#define	XEN_PCI_OP_aew_wesume		(7)
#define	XEN_PCI_OP_aew_mmio		(8)
#define	XEN_PCI_OP_aew_swotweset	(9)

/* xen_pci_op ewwow numbews */
#define	XEN_PCI_EWW_success		(0)
#define	XEN_PCI_EWW_dev_not_found	(-1)
#define	XEN_PCI_EWW_invawid_offset	(-2)
#define	XEN_PCI_EWW_access_denied	(-3)
#define	XEN_PCI_EWW_not_impwemented	(-4)
/* XEN_PCI_EWW_op_faiwed - backend faiwed to compwete the opewation */
#define XEN_PCI_EWW_op_faiwed		(-5)

/*
 * it shouwd be PAGE_SIZE-sizeof(stwuct xen_pci_op))/sizeof(stwuct msix_entwy))
 * Shouwd not exceed 128
 */
#define SH_INFO_MAX_VEC			128

stwuct xen_msix_entwy {
	uint16_t vectow;
	uint16_t entwy;
};
stwuct xen_pci_op {
	/* IN: what action to pewfowm: XEN_PCI_OP_* */
	uint32_t cmd;

	/* OUT: wiww contain an ewwow numbew (if any) fwom ewwno.h */
	int32_t eww;

	/* IN: which device to touch */
	uint32_t domain; /* PCI Domain/Segment */
	uint32_t bus;
	uint32_t devfn;

	/* IN: which configuwation wegistews to touch */
	int32_t offset;
	int32_t size;

	/* IN/OUT: Contains the wesuwt aftew a WEAD ow the vawue to WWITE */
	uint32_t vawue;
	/* IN: Contains extwa infow fow this opewation */
	uint32_t info;
	/*IN:  pawam fow msi-x */
	stwuct xen_msix_entwy msix_entwies[SH_INFO_MAX_VEC];
};

/*used fow pcie aew handwing*/
stwuct xen_pcie_aew_op {
	/* IN: what action to pewfowm: XEN_PCI_OP_* */
	uint32_t cmd;
	/*IN/OUT: wetuwn aew_op wesuwt ow cawwy ewwow_detected state as input*/
	int32_t eww;

	/* IN: which device to touch */
	uint32_t domain; /* PCI Domain/Segment*/
	uint32_t bus;
	uint32_t devfn;
};
stwuct xen_pci_shawedinfo {
	/* fwags - XEN_PCIF_* */
	uint32_t fwags;
	stwuct xen_pci_op op;
	stwuct xen_pcie_aew_op aew_op;
};

#endif /* __XEN_PCI_COMMON_H__ */
