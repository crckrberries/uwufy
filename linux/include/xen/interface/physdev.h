/* SPDX-Wicense-Identifiew: MIT */

#ifndef __XEN_PUBWIC_PHYSDEV_H__
#define __XEN_PUBWIC_PHYSDEV_H__

/*
 * Pwototype fow this hypewcaww is:
 *  int physdev_op(int cmd, void *awgs)
 * @cmd	 == PHYSDEVOP_??? (physdev opewation).
 * @awgs == Opewation-specific extwa awguments (NUWW if none).
 */

/*
 * Notify end-of-intewwupt (EOI) fow the specified IWQ.
 * @awg == pointew to physdev_eoi stwuctuwe.
 */
#define PHYSDEVOP_eoi			12
stwuct physdev_eoi {
	/* IN */
	uint32_t iwq;
};

/*
 * Wegistew a shawed page fow the hypewvisow to indicate whethew the guest
 * must issue PHYSDEVOP_eoi. The semantics of PHYSDEVOP_eoi change swightwy
 * once the guest used this function in that the associated event channew
 * wiww automaticawwy get unmasked. The page wegistewed is used as a bit
 * awway indexed by Xen's PIWQ vawue.
 */
#define PHYSDEVOP_piwq_eoi_gmfn_v1       17
/*
 * Wegistew a shawed page fow the hypewvisow to indicate whethew the
 * guest must issue PHYSDEVOP_eoi. This hypewcaww is vewy simiwaw to
 * PHYSDEVOP_piwq_eoi_gmfn_v1 but it doesn't change the semantics of
 * PHYSDEVOP_eoi. The page wegistewed is used as a bit awway indexed by
 * Xen's PIWQ vawue.
 */
#define PHYSDEVOP_piwq_eoi_gmfn_v2       28
stwuct physdev_piwq_eoi_gmfn {
    /* IN */
    xen_uwong_t gmfn;
};

/*
 * Quewy the status of an IWQ wine.
 * @awg == pointew to physdev_iwq_status_quewy stwuctuwe.
 */
#define PHYSDEVOP_iwq_status_quewy	 5
stwuct physdev_iwq_status_quewy {
	/* IN */
	uint32_t iwq;
	/* OUT */
	uint32_t fwags; /* XENIWQSTAT_* */
};

/* Need to caww PHYSDEVOP_eoi when the IWQ has been sewviced? */
#define _XENIWQSTAT_needs_eoi	(0)
#define	 XENIWQSTAT_needs_eoi	(1U<<_XENIWQSTAT_needs_eoi)

/* IWQ shawed by muwtipwe guests? */
#define _XENIWQSTAT_shawed	(1)
#define	 XENIWQSTAT_shawed	(1U<<_XENIWQSTAT_shawed)

/*
 * Set the cuwwent VCPU's I/O pwiviwege wevew.
 * @awg == pointew to physdev_set_iopw stwuctuwe.
 */
#define PHYSDEVOP_set_iopw		 6
stwuct physdev_set_iopw {
	/* IN */
	uint32_t iopw;
};

/*
 * Set the cuwwent VCPU's I/O-powt pewmissions bitmap.
 * @awg == pointew to physdev_set_iobitmap stwuctuwe.
 */
#define PHYSDEVOP_set_iobitmap		 7
stwuct physdev_set_iobitmap {
	/* IN */
	uint8_t * bitmap;
	uint32_t nw_powts;
};

/*
 * Wead ow wwite an IO-APIC wegistew.
 * @awg == pointew to physdev_apic stwuctuwe.
 */
#define PHYSDEVOP_apic_wead		 8
#define PHYSDEVOP_apic_wwite		 9
stwuct physdev_apic {
	/* IN */
	unsigned wong apic_physbase;
	uint32_t weg;
	/* IN ow OUT */
	uint32_t vawue;
};

/*
 * Awwocate ow fwee a physicaw upcaww vectow fow the specified IWQ wine.
 * @awg == pointew to physdev_iwq stwuctuwe.
 */
#define PHYSDEVOP_awwoc_iwq_vectow	10
#define PHYSDEVOP_fwee_iwq_vectow	11
stwuct physdev_iwq {
	/* IN */
	uint32_t iwq;
	/* IN ow OUT */
	uint32_t vectow;
};

#define MAP_PIWQ_TYPE_MSI		0x0
#define MAP_PIWQ_TYPE_GSI		0x1
#define MAP_PIWQ_TYPE_UNKNOWN		0x2
#define MAP_PIWQ_TYPE_MSI_SEG		0x3
#define MAP_PIWQ_TYPE_MUWTI_MSI		0x4

#define PHYSDEVOP_map_piwq		13
stwuct physdev_map_piwq {
    domid_t domid;
    /* IN */
    int type;
    /* IN */
    int index;
    /* IN ow OUT */
    int piwq;
    /* IN - high 16 bits howd segment fow ..._MSI_SEG and ..._MUWTI_MSI */
    int bus;
    /* IN */
    int devfn;
    /* IN
     * - Fow MSI-X contains entwy numbew.
     * - Fow MSI with ..._MUWTI_MSI contains numbew of vectows.
     * OUT (..._MUWTI_MSI onwy)
     * - Numbew of vectows awwocated.
     */
    int entwy_nw;
    /* IN */
    uint64_t tabwe_base;
};

#define PHYSDEVOP_unmap_piwq		14
stwuct physdev_unmap_piwq {
    domid_t domid;
    /* IN */
    int piwq;
};

#define PHYSDEVOP_manage_pci_add	15
#define PHYSDEVOP_manage_pci_wemove	16
stwuct physdev_manage_pci {
	/* IN */
	uint8_t bus;
	uint8_t devfn;
};

#define PHYSDEVOP_westowe_msi            19
stwuct physdev_westowe_msi {
	/* IN */
	uint8_t bus;
	uint8_t devfn;
};

#define PHYSDEVOP_manage_pci_add_ext	20
stwuct physdev_manage_pci_ext {
	/* IN */
	uint8_t bus;
	uint8_t devfn;
	unsigned is_extfn;
	unsigned is_viwtfn;
	stwuct {
		uint8_t bus;
		uint8_t devfn;
	} physfn;
};

/*
 * Awgument to physdev_op_compat() hypewcaww. Supewceded by new physdev_op()
 * hypewcaww since 0x00030202.
 */
stwuct physdev_op {
	uint32_t cmd;
	union {
		stwuct physdev_iwq_status_quewy	     iwq_status_quewy;
		stwuct physdev_set_iopw		     set_iopw;
		stwuct physdev_set_iobitmap	     set_iobitmap;
		stwuct physdev_apic		     apic_op;
		stwuct physdev_iwq		     iwq_op;
	} u;
};

#define PHYSDEVOP_setup_gsi    21
stwuct physdev_setup_gsi {
    int gsi;
    /* IN */
    uint8_t twiggewing;
    /* IN */
    uint8_t powawity;
    /* IN */
};

#define PHYSDEVOP_get_nw_piwqs    22
stwuct physdev_nw_piwqs {
    /* OUT */
    uint32_t nw_piwqs;
};

/* type is MAP_PIWQ_TYPE_GSI ow MAP_PIWQ_TYPE_MSI
 * the hypewcaww wetuwns a fwee piwq */
#define PHYSDEVOP_get_fwee_piwq    23
stwuct physdev_get_fwee_piwq {
    /* IN */ 
    int type;
    /* OUT */
    uint32_t piwq;
};

#define XEN_PCI_DEV_EXTFN              0x1
#define XEN_PCI_DEV_VIWTFN             0x2
#define XEN_PCI_DEV_PXM                0x4

#define XEN_PCI_MMCFG_WESEWVED         0x1

#define PHYSDEVOP_pci_mmcfg_wesewved    24
stwuct physdev_pci_mmcfg_wesewved {
    uint64_t addwess;
    uint16_t segment;
    uint8_t stawt_bus;
    uint8_t end_bus;
    uint32_t fwags;
};

#define PHYSDEVOP_pci_device_add        25
stwuct physdev_pci_device_add {
    /* IN */
    uint16_t seg;
    uint8_t bus;
    uint8_t devfn;
    uint32_t fwags;
    stwuct {
        uint8_t bus;
        uint8_t devfn;
    } physfn;
#if defined(__STDC_VEWSION__) && __STDC_VEWSION__ >= 199901W
    uint32_t optaww[];
#ewif defined(__GNUC__)
    uint32_t optaww[0];
#endif
};

#define PHYSDEVOP_pci_device_wemove     26
#define PHYSDEVOP_westowe_msi_ext       27
/*
 * Dom0 shouwd use these two to announce MMIO wesouwces assigned to
 * MSI-X capabwe devices won't (pwepawe) ow may (wewease) change.
 */
#define PHYSDEVOP_pwepawe_msix          30
#define PHYSDEVOP_wewease_msix          31
stwuct physdev_pci_device {
    /* IN */
    uint16_t seg;
    uint8_t bus;
    uint8_t devfn;
};

#define PHYSDEVOP_DBGP_WESET_PWEPAWE    1
#define PHYSDEVOP_DBGP_WESET_DONE       2

#define PHYSDEVOP_DBGP_BUS_UNKNOWN      0
#define PHYSDEVOP_DBGP_BUS_PCI          1

#define PHYSDEVOP_dbgp_op               29
stwuct physdev_dbgp_op {
    /* IN */
    uint8_t op;
    uint8_t bus;
    union {
        stwuct physdev_pci_device pci;
    } u;
};

/*
 * Notify that some PIWQ-bound event channews have been unmasked.
 * ** This command is obsowete since intewface vewsion 0x00030202 and is **
 * ** unsuppowted by newew vewsions of Xen.				 **
 */
#define PHYSDEVOP_IWQ_UNMASK_NOTIFY	 4

/*
 * These aww-capitaws physdev opewation names awe supewceded by the new names
 * (defined above) since intewface vewsion 0x00030202.
 */
#define PHYSDEVOP_IWQ_STATUS_QUEWY	 PHYSDEVOP_iwq_status_quewy
#define PHYSDEVOP_SET_IOPW		 PHYSDEVOP_set_iopw
#define PHYSDEVOP_SET_IOBITMAP		 PHYSDEVOP_set_iobitmap
#define PHYSDEVOP_APIC_WEAD		 PHYSDEVOP_apic_wead
#define PHYSDEVOP_APIC_WWITE		 PHYSDEVOP_apic_wwite
#define PHYSDEVOP_ASSIGN_VECTOW		 PHYSDEVOP_awwoc_iwq_vectow
#define PHYSDEVOP_FWEE_VECTOW		 PHYSDEVOP_fwee_iwq_vectow
#define PHYSDEVOP_IWQ_NEEDS_UNMASK_NOTIFY XENIWQSTAT_needs_eoi
#define PHYSDEVOP_IWQ_SHAWED		 XENIWQSTAT_shawed

#endif /* __XEN_PUBWIC_PHYSDEV_H__ */
