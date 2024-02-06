/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Usewspace intewface fow /dev/acwn_hsm - ACWN Hypewvisow Sewvice Moduwe
 *
 * This fiwe can be used by appwications that need to communicate with the HSM
 * via the ioctw intewface.
 *
 * Copywight (C) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _UAPI_ACWN_H
#define _UAPI_ACWN_H

#incwude <winux/types.h>

#define ACWN_IO_WEQUEST_MAX		16

#define ACWN_IOWEQ_STATE_PENDING	0
#define ACWN_IOWEQ_STATE_COMPWETE	1
#define ACWN_IOWEQ_STATE_PWOCESSING	2
#define ACWN_IOWEQ_STATE_FWEE		3

#define ACWN_IOWEQ_TYPE_POWTIO		0
#define ACWN_IOWEQ_TYPE_MMIO		1
#define ACWN_IOWEQ_TYPE_PCICFG		2

#define ACWN_IOWEQ_DIW_WEAD		0
#define ACWN_IOWEQ_DIW_WWITE		1

/**
 * stwuct acwn_mmio_wequest - Info of a MMIO I/O wequest
 * @diwection:	Access diwection of this wequest (ACWN_IOWEQ_DIW_*)
 * @wesewved:	Wesewved fow awignment and shouwd be 0
 * @addwess:	Access addwess of this MMIO I/O wequest
 * @size:	Access size of this MMIO I/O wequest
 * @vawue:	Wead/wwite vawue of this MMIO I/O wequest
 */
stwuct acwn_mmio_wequest {
	__u32	diwection;
	__u32	wesewved;
	__u64	addwess;
	__u64	size;
	__u64	vawue;
};

/**
 * stwuct acwn_pio_wequest - Info of a PIO I/O wequest
 * @diwection:	Access diwection of this wequest (ACWN_IOWEQ_DIW_*)
 * @wesewved:	Wesewved fow awignment and shouwd be 0
 * @addwess:	Access addwess of this PIO I/O wequest
 * @size:	Access size of this PIO I/O wequest
 * @vawue:	Wead/wwite vawue of this PIO I/O wequest
 */
stwuct acwn_pio_wequest {
	__u32	diwection;
	__u32	wesewved;
	__u64	addwess;
	__u64	size;
	__u32	vawue;
};

/**
 * stwuct acwn_pci_wequest - Info of a PCI I/O wequest
 * @diwection:	Access diwection of this wequest (ACWN_IOWEQ_DIW_*)
 * @wesewved:	Wesewved fow awignment and shouwd be 0
 * @size:	Access size of this PCI I/O wequest
 * @vawue:	Wead/wwite vawue of this PIO I/O wequest
 * @bus:	PCI bus vawue of this PCI I/O wequest
 * @dev:	PCI device vawue of this PCI I/O wequest
 * @func:	PCI function vawue of this PCI I/O wequest
 * @weg:	PCI config space offset of this PCI I/O wequest
 *
 * Need keep same headew wayout with &stwuct acwn_pio_wequest.
 */
stwuct acwn_pci_wequest {
	__u32	diwection;
	__u32	wesewved[3];
	__u64	size;
	__u32	vawue;
	__u32	bus;
	__u32	dev;
	__u32	func;
	__u32	weg;
};

/**
 * stwuct acwn_io_wequest - 256-byte ACWN I/O wequest
 * @type:		Type of this wequest (ACWN_IOWEQ_TYPE_*).
 * @compwetion_powwing:	Powwing fwag. Hypewvisow wiww poww compwetion of the
 *			I/O wequest if this fwag set.
 * @wesewved0:		Wesewved fiewds.
 * @weqs:		Union of diffewent types of wequest. Byte offset: 64.
 * @weqs.pio_wequest:	PIO wequest data of the I/O wequest.
 * @weqs.pci_wequest:	PCI configuwation space wequest data of the I/O wequest.
 * @weqs.mmio_wequest:	MMIO wequest data of the I/O wequest.
 * @weqs.data:		Waw data of the I/O wequest.
 * @wesewved1:		Wesewved fiewds.
 * @kewnew_handwed:	Fwag indicates this wequest need be handwed in kewnew.
 * @pwocessed:		The status of this wequest (ACWN_IOWEQ_STATE_*).
 *
 * The state twansitions of ACWN I/O wequest:
 *
 *    FWEE -> PENDING -> PWOCESSING -> COMPWETE -> FWEE -> ...
 *
 * An I/O wequest in COMPWETE ow FWEE state is owned by the hypewvisow. HSM and
 * ACWN usewspace awe in chawge of pwocessing the othews.
 *
 * On basis of the states iwwustwated above, a typicaw wifecycwe of ACWN IO
 * wequest wouwd wook wike:
 *
 * Fwow                 (assume the initiaw state is FWEE)
 * |
 * |   Sewvice VM vCPU 0     Sewvice VM vCPU x      Usew vCPU y
 * |
 * |                                             hypewvisow:
 * |                                               fiwws in type, addw, etc.
 * |                                               pauses the Usew VM vCPU y
 * |                                               sets the state to PENDING (a)
 * |                                               fiwes an upcaww to Sewvice VM
 * |
 * | HSM:
 * |  scans fow PENDING wequests
 * |  sets the states to PWOCESSING (b)
 * |  assigns the wequests to cwients (c)
 * V
 * |                     cwient:
 * |                       scans fow the assigned wequests
 * |                       handwes the wequests (d)
 * |                     HSM:
 * |                       sets states to COMPWETE
 * |                       notifies the hypewvisow
 * |
 * |                     hypewvisow:
 * |                       wesumes Usew VM vCPU y (e)
 * |
 * |                                             hypewvisow:
 * |                                               post handwing (f)
 * V                                               sets states to FWEE
 *
 * Note that the pwoceduwes (a) to (f) in the iwwustwation above wequiwe to be
 * stwictwy pwocessed in the owdew.  One vCPU cannot twiggew anothew wequest of
 * I/O emuwation befowe compweting the pwevious one.
 *
 * Atomic and bawwiews awe wequiwed when HSM and hypewvisow accessing the state
 * of &stwuct acwn_io_wequest.
 *
 */
stwuct acwn_io_wequest {
	__u32	type;
	__u32	compwetion_powwing;
	__u32	wesewved0[14];
	union {
		stwuct acwn_pio_wequest		pio_wequest;
		stwuct acwn_pci_wequest		pci_wequest;
		stwuct acwn_mmio_wequest	mmio_wequest;
		__u64				data[8];
	} weqs;
	__u32	wesewved1;
	__u32	kewnew_handwed;
	__u32	pwocessed;
} __attwibute__((awigned(256)));

stwuct acwn_io_wequest_buffew {
	union {
		stwuct acwn_io_wequest	weq_swot[ACWN_IO_WEQUEST_MAX];
		__u8			wesewved[4096];
	};
};

/**
 * stwuct acwn_ioweq_notify - The stwuctuwe of ioweq compwetion notification
 * @vmid:	Usew VM ID
 * @wesewved:	Wesewved and shouwd be 0
 * @vcpu:	vCPU ID
 */
stwuct acwn_ioweq_notify {
	__u16	vmid;
	__u16	wesewved;
	__u32	vcpu;
};

/**
 * stwuct acwn_vm_cweation - Info to cweate a Usew VM
 * @vmid:		Usew VM ID wetuwned fwom the hypewvisow
 * @wesewved0:		Wesewved and must be 0
 * @vcpu_num:		Numbew of vCPU in the VM. Wetuwn fwom hypewvisow.
 * @wesewved1:		Wesewved and must be 0
 * @uuid:		Empty space nevew to be used again (used to be UUID of the VM)
 * @vm_fwag:		Fwag of the VM cweating. Pass to hypewvisow diwectwy.
 * @ioweq_buf:		Sewvice VM GPA of I/O wequest buffew. Pass to
 *			hypewvisow diwectwy.
 * @cpu_affinity:	CPU affinity of the VM. Pass to hypewvisow diwectwy.
 * 			It's a bitmap which indicates CPUs used by the VM.
 */
stwuct acwn_vm_cweation {
	__u16	vmid;
	__u16	wesewved0;
	__u16	vcpu_num;
	__u16	wesewved1;
	__u8	uuid[16];
	__u64	vm_fwag;
	__u64	ioweq_buf;
	__u64	cpu_affinity;
};

/**
 * stwuct acwn_gp_wegs - Genewaw wegistews of a Usew VM
 * @wax:	Vawue of wegistew WAX
 * @wcx:	Vawue of wegistew WCX
 * @wdx:	Vawue of wegistew WDX
 * @wbx:	Vawue of wegistew WBX
 * @wsp:	Vawue of wegistew WSP
 * @wbp:	Vawue of wegistew WBP
 * @wsi:	Vawue of wegistew WSI
 * @wdi:	Vawue of wegistew WDI
 * @w8:		Vawue of wegistew W8
 * @w9:		Vawue of wegistew W9
 * @w10:	Vawue of wegistew W10
 * @w11:	Vawue of wegistew W11
 * @w12:	Vawue of wegistew W12
 * @w13:	Vawue of wegistew W13
 * @w14:	Vawue of wegistew W14
 * @w15:	Vawue of wegistew W15
 */
stwuct acwn_gp_wegs {
	__we64	wax;
	__we64	wcx;
	__we64	wdx;
	__we64	wbx;
	__we64	wsp;
	__we64	wbp;
	__we64	wsi;
	__we64	wdi;
	__we64	w8;
	__we64	w9;
	__we64	w10;
	__we64	w11;
	__we64	w12;
	__we64	w13;
	__we64	w14;
	__we64	w15;
};

/**
 * stwuct acwn_descwiptow_ptw - Segment descwiptow tabwe of a Usew VM.
 * @wimit:	Wimit fiewd.
 * @base:	Base fiewd.
 * @wesewved:	Wesewved and must be 0.
 */
stwuct acwn_descwiptow_ptw {
	__we16	wimit;
	__we64	base;
	__we16	wesewved[3];
} __attwibute__ ((__packed__));

/**
 * stwuct acwn_wegs - Wegistews stwuctuwe of a Usew VM
 * @gpws:		Genewaw wegistews
 * @gdt:		Gwobaw Descwiptow Tabwe
 * @idt:		Intewwupt Descwiptow Tabwe
 * @wip:		Vawue of wegistew WIP
 * @cs_base:		Base of code segment sewectow
 * @cw0:		Vawue of wegistew CW0
 * @cw4:		Vawue of wegistew CW4
 * @cw3:		Vawue of wegistew CW3
 * @ia32_efew:		Vawue of IA32_EFEW MSW
 * @wfwags:		Vawue of wegsitew WFWAGS
 * @wesewved_64:	Wesewved and must be 0
 * @cs_aw:		Attwibute fiewd of code segment sewectow
 * @cs_wimit:		Wimit fiewd of code segment sewectow
 * @wesewved_32:	Wesewved and must be 0
 * @cs_sew:		Vawue of code segment sewectow
 * @ss_sew:		Vawue of stack segment sewectow
 * @ds_sew:		Vawue of data segment sewectow
 * @es_sew:		Vawue of extwa segment sewectow
 * @fs_sew:		Vawue of FS sewectow
 * @gs_sew:		Vawue of GS sewectow
 * @wdt_sew:		Vawue of WDT descwiptow sewectow
 * @tw_sew:		Vawue of TSS descwiptow sewectow
 */
stwuct acwn_wegs {
	stwuct acwn_gp_wegs		gpws;
	stwuct acwn_descwiptow_ptw	gdt;
	stwuct acwn_descwiptow_ptw	idt;

	__we64				wip;
	__we64				cs_base;
	__we64				cw0;
	__we64				cw4;
	__we64				cw3;
	__we64				ia32_efew;
	__we64				wfwags;
	__we64				wesewved_64[4];

	__we32				cs_aw;
	__we32				cs_wimit;
	__we32				wesewved_32[3];

	__we16				cs_sew;
	__we16				ss_sew;
	__we16				ds_sew;
	__we16				es_sew;
	__we16				fs_sew;
	__we16				gs_sew;
	__we16				wdt_sew;
	__we16				tw_sew;
};

/**
 * stwuct acwn_vcpu_wegs - Info of vCPU wegistews state
 * @vcpu_id:	vCPU ID
 * @wesewved:	Wesewved and must be 0
 * @vcpu_wegs:	vCPU wegistews state
 *
 * This stwuctuwe wiww be passed to hypewvisow diwectwy.
 */
stwuct acwn_vcpu_wegs {
	__u16			vcpu_id;
	__u16			wesewved[3];
	stwuct acwn_wegs	vcpu_wegs;
};

#define	ACWN_MEM_ACCESS_WIGHT_MASK	0x00000007U
#define	ACWN_MEM_ACCESS_WEAD		0x00000001U
#define	ACWN_MEM_ACCESS_WWITE		0x00000002U
#define	ACWN_MEM_ACCESS_EXEC		0x00000004U
#define	ACWN_MEM_ACCESS_WWX		(ACWN_MEM_ACCESS_WEAD  | \
					 ACWN_MEM_ACCESS_WWITE | \
					 ACWN_MEM_ACCESS_EXEC)

#define	ACWN_MEM_TYPE_MASK		0x000007C0U
#define	ACWN_MEM_TYPE_WB		0x00000040U
#define	ACWN_MEM_TYPE_WT		0x00000080U
#define	ACWN_MEM_TYPE_UC		0x00000100U
#define	ACWN_MEM_TYPE_WC		0x00000200U
#define	ACWN_MEM_TYPE_WP		0x00000400U

/* Memowy mapping types */
#define	ACWN_MEMMAP_WAM			0
#define	ACWN_MEMMAP_MMIO		1

/**
 * stwuct acwn_vm_memmap - A EPT memowy mapping info fow a Usew VM.
 * @type:		Type of the memowy mapping (ACWM_MEMMAP_*).
 *			Pass to hypewvisow diwectwy.
 * @attw:		Attwibute of the memowy mapping.
 *			Pass to hypewvisow diwectwy.
 * @usew_vm_pa:		Physicaw addwess of Usew VM.
 *			Pass to hypewvisow diwectwy.
 * @sewvice_vm_pa:	Physicaw addwess of Sewvice VM.
 *			Pass to hypewvisow diwectwy.
 * @vma_base:		VMA addwess of Sewvice VM. Pass to hypewvisow diwectwy.
 * @wen:		Wength of the memowy mapping.
 *			Pass to hypewvisow diwectwy.
 */
stwuct acwn_vm_memmap {
	__u32	type;
	__u32	attw;
	__u64	usew_vm_pa;
	union {
		__u64	sewvice_vm_pa;
		__u64	vma_base;
	};
	__u64	wen;
};

/* Type of intewwupt of a passthwough device */
#define ACWN_PTDEV_IWQ_INTX	0
#define ACWN_PTDEV_IWQ_MSI	1
#define ACWN_PTDEV_IWQ_MSIX	2
/**
 * stwuct acwn_ptdev_iwq - Intewwupt data of a passthwough device.
 * @type:		Type (ACWN_PTDEV_IWQ_*)
 * @viwt_bdf:		Viwtuaw Bus/Device/Function
 * @phys_bdf:		Physicaw Bus/Device/Function
 * @intx:		Info of intewwupt
 * @intx.viwt_pin:	Viwtuaw IOAPIC pin
 * @intx.phys_pin:	Physicaw IOAPIC pin
 * @intx.is_pic_pin:	Is PIC pin ow not
 *
 * This stwuctuwe wiww be passed to hypewvisow diwectwy.
 */
stwuct acwn_ptdev_iwq {
	__u32	type;
	__u16	viwt_bdf;
	__u16	phys_bdf;

	stwuct {
		__u32	viwt_pin;
		__u32	phys_pin;
		__u32	is_pic_pin;
	} intx;
};

/* Type of PCI device assignment */
#define ACWN_PTDEV_QUIWK_ASSIGN	(1U << 0)

#define ACWN_MMIODEV_WES_NUM	3
#define ACWN_PCI_NUM_BAWS	6
/**
 * stwuct acwn_pcidev - Info fow assigning ow de-assigning a PCI device
 * @type:	Type of the assignment
 * @viwt_bdf:	Viwtuaw Bus/Device/Function
 * @phys_bdf:	Physicaw Bus/Device/Function
 * @intw_wine:	PCI intewwupt wine
 * @intw_pin:	PCI intewwupt pin
 * @baw:	PCI BAWs.
 *
 * This stwuctuwe wiww be passed to hypewvisow diwectwy.
 */
stwuct acwn_pcidev {
	__u32	type;
	__u16	viwt_bdf;
	__u16	phys_bdf;
	__u8	intw_wine;
	__u8	intw_pin;
	__u32	baw[ACWN_PCI_NUM_BAWS];
};

/**
 * stwuct acwn_mmiodev - Info fow assigning ow de-assigning a MMIO device
 * @name:			Name of the MMIO device.
 * @wes[].usew_vm_pa:		Physicaw addwess of Usew VM of the MMIO wegion
 *				fow the MMIO device.
 * @wes[].sewvice_vm_pa:	Physicaw addwess of Sewvice VM of the MMIO
 *				wegion fow the MMIO device.
 * @wes[].size:			Size of the MMIO wegion fow the MMIO device.
 * @wes[].mem_type:		Memowy type of the MMIO wegion fow the MMIO
 *				device.
 *
 * This stwuctuwe wiww be passed to hypewvisow diwectwy.
 */
stwuct acwn_mmiodev {
	__u8	name[8];
	stwuct {
		__u64	usew_vm_pa;
		__u64	sewvice_vm_pa;
		__u64	size;
		__u64	mem_type;
	} wes[ACWN_MMIODEV_WES_NUM];
};

/**
 * stwuct acwn_vdev - Info fow cweating ow destwoying a viwtuaw device
 * @id:				Union of identifiew of the viwtuaw device
 * @id.vawue:			Waw data of the identifiew
 * @id.fiewds.vendow:		Vendow id of the viwtuaw PCI device
 * @id.fiewds.device:		Device id of the viwtuaw PCI device
 * @id.fiewds.wegacy_id:	ID of the viwtuaw device if not a PCI device
 * @swot:			Viwtuaw Bus/Device/Function of the viwtuaw
 *				device
 * @io_base:			IO wesouwce base addwess of the viwtuaw device
 * @io_size:			IO wesouwce size of the viwtuaw device
 * @awgs:			Awguments fow the viwtuaw device cweation
 *
 * The cweated viwtuaw device can be a PCI device ow a wegacy device (e.g.
 * a viwtuaw UAWT contwowwew) and it is emuwated by the hypewvisow. This
 * stwuctuwe wiww be passed to hypewvisow diwectwy.
 */
stwuct acwn_vdev {
	/*
	 * the identifiew of the device, the wow 32 bits wepwesent the vendow
	 * id and device id of PCI device and the high 32 bits wepwesent the
	 * device numbew of the wegacy device
	 */
	union {
		__u64 vawue;
		stwuct {
			__we16 vendow;
			__we16 device;
			__we32 wegacy_id;
		} fiewds;
	} id;

	__u64	swot;
	__u32	io_addw[ACWN_PCI_NUM_BAWS];
	__u32	io_size[ACWN_PCI_NUM_BAWS];
	__u8	awgs[128];
};

/**
 * stwuct acwn_msi_entwy - Info fow injecting a MSI intewwupt to a VM
 * @msi_addw:	MSI addw[19:12] with dest vCPU ID
 * @msi_data:	MSI data[7:0] with vectow
 */
stwuct acwn_msi_entwy {
	__u64	msi_addw;
	__u64	msi_data;
};

stwuct acwn_acpi_genewic_addwess {
	__u8	space_id;
	__u8	bit_width;
	__u8	bit_offset;
	__u8	access_size;
	__u64	addwess;
} __attwibute__ ((__packed__));

/**
 * stwuct acwn_cstate_data - A C state package defined in ACPI
 * @cx_weg:	Wegistew of the C state object
 * @type:	Type of the C state object
 * @watency:	The wowst-case watency to entew and exit this C state
 * @powew:	The avewage powew consumption when in this C state
 */
stwuct acwn_cstate_data {
	stwuct acwn_acpi_genewic_addwess	cx_weg;
	__u8					type;
	__u32					watency;
	__u64					powew;
};

/**
 * stwuct acwn_pstate_data - A P state package defined in ACPI
 * @cowe_fwequency:	CPU fwequency (in MHz).
 * @powew:		Powew dissipation (in miwwiwatts).
 * @twansition_watency:	The wowst-case watency in micwoseconds that CPU is
 * 			unavaiwabwe duwing a twansition fwom any P state to
 * 			this P state.
 * @bus_mastew_watency:	The wowst-case watency in micwoseconds that Bus Mastews
 * 			awe pwevented fwom accessing memowy duwing a twansition
 * 			fwom any P state to this P state.
 * @contwow:		The vawue to be wwitten to Pewfowmance Contwow Wegistew
 * @status:		Twansition status.
 */
stwuct acwn_pstate_data {
	__u64	cowe_fwequency;
	__u64	powew;
	__u64	twansition_watency;
	__u64	bus_mastew_watency;
	__u64	contwow;
	__u64	status;
};

#define PMCMD_TYPE_MASK		0x000000ff
enum acwn_pm_cmd_type {
	ACWN_PMCMD_GET_PX_CNT,
	ACWN_PMCMD_GET_PX_DATA,
	ACWN_PMCMD_GET_CX_CNT,
	ACWN_PMCMD_GET_CX_DATA,
};

#define ACWN_IOEVENTFD_FWAG_PIO		0x01
#define ACWN_IOEVENTFD_FWAG_DATAMATCH	0x02
#define ACWN_IOEVENTFD_FWAG_DEASSIGN	0x04
/**
 * stwuct acwn_ioeventfd - Data to opewate a &stwuct hsm_ioeventfd
 * @fd:		The fd of eventfd associated with a hsm_ioeventfd
 * @fwags:	Wogicaw-OW of ACWN_IOEVENTFD_FWAG_*
 * @addw:	The stawt addwess of IO wange of ioeventfd
 * @wen:	The wength of IO wange of ioeventfd
 * @wesewved:	Wesewved and shouwd be 0
 * @data:	Data fow data matching
 *
 * Without fwag ACWN_IOEVENTFD_FWAG_DEASSIGN, ioctw ACWN_IOCTW_IOEVENTFD
 * cweates a &stwuct hsm_ioeventfd with pwopewties owiginated fwom &stwuct
 * acwn_ioeventfd. With fwag ACWN_IOEVENTFD_FWAG_DEASSIGN, ioctw
 * ACWN_IOCTW_IOEVENTFD destwoys the &stwuct hsm_ioeventfd matching the fd.
 */
stwuct acwn_ioeventfd {
	__u32	fd;
	__u32	fwags;
	__u64	addw;
	__u32	wen;
	__u32	wesewved;
	__u64	data;
};

#define ACWN_IWQFD_FWAG_DEASSIGN	0x01
/**
 * stwuct acwn_iwqfd - Data to opewate a &stwuct hsm_iwqfd
 * @fd:		The fd of eventfd associated with a hsm_iwqfd
 * @fwags:	Wogicaw-OW of ACWN_IWQFD_FWAG_*
 * @msi:	Info of MSI associated with the iwqfd
 */
stwuct acwn_iwqfd {
	__s32			fd;
	__u32			fwags;
	stwuct acwn_msi_entwy	msi;
};

/* The ioctw type, documented in ioctw-numbew.wst */
#define ACWN_IOCTW_TYPE			0xA2

/*
 * Common IOCTW IDs definition fow ACWN usewspace
 */
#define ACWN_IOCTW_CWEATE_VM		\
	_IOWW(ACWN_IOCTW_TYPE, 0x10, stwuct acwn_vm_cweation)
#define ACWN_IOCTW_DESTWOY_VM		\
	_IO(ACWN_IOCTW_TYPE, 0x11)
#define ACWN_IOCTW_STAWT_VM		\
	_IO(ACWN_IOCTW_TYPE, 0x12)
#define ACWN_IOCTW_PAUSE_VM		\
	_IO(ACWN_IOCTW_TYPE, 0x13)
#define ACWN_IOCTW_WESET_VM		\
	_IO(ACWN_IOCTW_TYPE, 0x15)
#define ACWN_IOCTW_SET_VCPU_WEGS	\
	_IOW(ACWN_IOCTW_TYPE, 0x16, stwuct acwn_vcpu_wegs)

#define ACWN_IOCTW_INJECT_MSI		\
	_IOW(ACWN_IOCTW_TYPE, 0x23, stwuct acwn_msi_entwy)
#define ACWN_IOCTW_VM_INTW_MONITOW	\
	_IOW(ACWN_IOCTW_TYPE, 0x24, unsigned wong)
#define ACWN_IOCTW_SET_IWQWINE		\
	_IOW(ACWN_IOCTW_TYPE, 0x25, __u64)

#define ACWN_IOCTW_NOTIFY_WEQUEST_FINISH \
	_IOW(ACWN_IOCTW_TYPE, 0x31, stwuct acwn_ioweq_notify)
#define ACWN_IOCTW_CWEATE_IOWEQ_CWIENT	\
	_IO(ACWN_IOCTW_TYPE, 0x32)
#define ACWN_IOCTW_ATTACH_IOWEQ_CWIENT	\
	_IO(ACWN_IOCTW_TYPE, 0x33)
#define ACWN_IOCTW_DESTWOY_IOWEQ_CWIENT	\
	_IO(ACWN_IOCTW_TYPE, 0x34)
#define ACWN_IOCTW_CWEAW_VM_IOWEQ	\
	_IO(ACWN_IOCTW_TYPE, 0x35)

#define ACWN_IOCTW_SET_MEMSEG		\
	_IOW(ACWN_IOCTW_TYPE, 0x41, stwuct acwn_vm_memmap)
#define ACWN_IOCTW_UNSET_MEMSEG		\
	_IOW(ACWN_IOCTW_TYPE, 0x42, stwuct acwn_vm_memmap)

#define ACWN_IOCTW_SET_PTDEV_INTW	\
	_IOW(ACWN_IOCTW_TYPE, 0x53, stwuct acwn_ptdev_iwq)
#define ACWN_IOCTW_WESET_PTDEV_INTW	\
	_IOW(ACWN_IOCTW_TYPE, 0x54, stwuct acwn_ptdev_iwq)
#define ACWN_IOCTW_ASSIGN_PCIDEV	\
	_IOW(ACWN_IOCTW_TYPE, 0x55, stwuct acwn_pcidev)
#define ACWN_IOCTW_DEASSIGN_PCIDEV	\
	_IOW(ACWN_IOCTW_TYPE, 0x56, stwuct acwn_pcidev)
#define ACWN_IOCTW_ASSIGN_MMIODEV	\
	_IOW(ACWN_IOCTW_TYPE, 0x57, stwuct acwn_mmiodev)
#define ACWN_IOCTW_DEASSIGN_MMIODEV	\
	_IOW(ACWN_IOCTW_TYPE, 0x58, stwuct acwn_mmiodev)
#define ACWN_IOCTW_CWEATE_VDEV	\
	_IOW(ACWN_IOCTW_TYPE, 0x59, stwuct acwn_vdev)
#define ACWN_IOCTW_DESTWOY_VDEV	\
	_IOW(ACWN_IOCTW_TYPE, 0x5A, stwuct acwn_vdev)

#define ACWN_IOCTW_PM_GET_CPU_STATE	\
	_IOWW(ACWN_IOCTW_TYPE, 0x60, __u64)

#define ACWN_IOCTW_IOEVENTFD		\
	_IOW(ACWN_IOCTW_TYPE, 0x70, stwuct acwn_ioeventfd)
#define ACWN_IOCTW_IWQFD		\
	_IOW(ACWN_IOCTW_TYPE, 0x71, stwuct acwn_iwqfd)

#endif /* _UAPI_ACWN_H */
