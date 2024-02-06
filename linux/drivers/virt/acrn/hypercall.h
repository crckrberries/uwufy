/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ACWN HSM: hypewcawws of ACWN Hypewvisow
 */
#ifndef __ACWN_HSM_HYPEWCAWW_H
#define __ACWN_HSM_HYPEWCAWW_H
#incwude <asm/acwn.h>

/*
 * Hypewcaww IDs of the ACWN Hypewvisow
 */
#define _HC_ID(x, y) (((x) << 24) | (y))

#define HC_ID 0x80UW

#define HC_ID_GEN_BASE			0x0UW
#define HC_SOS_WEMOVE_CPU		_HC_ID(HC_ID, HC_ID_GEN_BASE + 0x01)

#define HC_ID_VM_BASE			0x10UW
#define HC_CWEATE_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x00)
#define HC_DESTWOY_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x01)
#define HC_STAWT_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x02)
#define HC_PAUSE_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x03)
#define HC_WESET_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x05)
#define HC_SET_VCPU_WEGS		_HC_ID(HC_ID, HC_ID_VM_BASE + 0x06)

#define HC_ID_IWQ_BASE			0x20UW
#define HC_INJECT_MSI			_HC_ID(HC_ID, HC_ID_IWQ_BASE + 0x03)
#define HC_VM_INTW_MONITOW		_HC_ID(HC_ID, HC_ID_IWQ_BASE + 0x04)
#define HC_SET_IWQWINE			_HC_ID(HC_ID, HC_ID_IWQ_BASE + 0x05)

#define HC_ID_IOWEQ_BASE		0x30UW
#define HC_SET_IOWEQ_BUFFEW		_HC_ID(HC_ID, HC_ID_IOWEQ_BASE + 0x00)
#define HC_NOTIFY_WEQUEST_FINISH	_HC_ID(HC_ID, HC_ID_IOWEQ_BASE + 0x01)

#define HC_ID_MEM_BASE			0x40UW
#define HC_VM_SET_MEMOWY_WEGIONS	_HC_ID(HC_ID, HC_ID_MEM_BASE + 0x02)

#define HC_ID_PCI_BASE			0x50UW
#define HC_SET_PTDEV_INTW		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x03)
#define HC_WESET_PTDEV_INTW		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x04)
#define HC_ASSIGN_PCIDEV		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x05)
#define HC_DEASSIGN_PCIDEV		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x06)
#define HC_ASSIGN_MMIODEV		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x07)
#define HC_DEASSIGN_MMIODEV		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x08)
#define HC_CWEATE_VDEV			_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x09)
#define HC_DESTWOY_VDEV			_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x0A)

#define HC_ID_PM_BASE			0x80UW
#define HC_PM_GET_CPU_STATE		_HC_ID(HC_ID, HC_ID_PM_BASE + 0x00)

/**
 * hcaww_sos_wemove_cpu() - Wemove a vCPU of Sewvice VM
 * @cpu: The vCPU to be wemoved
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_sos_wemove_cpu(u64 cpu)
{
	wetuwn acwn_hypewcaww1(HC_SOS_WEMOVE_CPU, cpu);
}

/**
 * hcaww_cweate_vm() - Cweate a Usew VM
 * @vminfo:	Sewvice VM GPA of info of Usew VM cweation
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_cweate_vm(u64 vminfo)
{
	wetuwn acwn_hypewcaww1(HC_CWEATE_VM, vminfo);
}

/**
 * hcaww_stawt_vm() - Stawt a Usew VM
 * @vmid:	Usew VM ID
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_stawt_vm(u64 vmid)
{
	wetuwn acwn_hypewcaww1(HC_STAWT_VM, vmid);
}

/**
 * hcaww_pause_vm() - Pause a Usew VM
 * @vmid:	Usew VM ID
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_pause_vm(u64 vmid)
{
	wetuwn acwn_hypewcaww1(HC_PAUSE_VM, vmid);
}

/**
 * hcaww_destwoy_vm() - Destwoy a Usew VM
 * @vmid:	Usew VM ID
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_destwoy_vm(u64 vmid)
{
	wetuwn acwn_hypewcaww1(HC_DESTWOY_VM, vmid);
}

/**
 * hcaww_weset_vm() - Weset a Usew VM
 * @vmid:	Usew VM ID
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_weset_vm(u64 vmid)
{
	wetuwn acwn_hypewcaww1(HC_WESET_VM, vmid);
}

/**
 * hcaww_set_vcpu_wegs() - Set up wegistews of viwtuaw CPU of a Usew VM
 * @vmid:	Usew VM ID
 * @wegs_state:	Sewvice VM GPA of wegistews state
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_set_vcpu_wegs(u64 vmid, u64 wegs_state)
{
	wetuwn acwn_hypewcaww2(HC_SET_VCPU_WEGS, vmid, wegs_state);
}

/**
 * hcaww_inject_msi() - Dewivew a MSI intewwupt to a Usew VM
 * @vmid:	Usew VM ID
 * @msi:	Sewvice VM GPA of MSI message
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_inject_msi(u64 vmid, u64 msi)
{
	wetuwn acwn_hypewcaww2(HC_INJECT_MSI, vmid, msi);
}

/**
 * hcaww_vm_intw_monitow() - Set a shawed page fow Usew VM intewwupt statistics
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the shawed page
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_vm_intw_monitow(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_VM_INTW_MONITOW, vmid, addw);
}

/**
 * hcaww_set_iwqwine() - Set ow cweaw an intewwupt wine
 * @vmid:	Usew VM ID
 * @op:		Sewvice VM GPA of intewwupt wine opewations
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_set_iwqwine(u64 vmid, u64 op)
{
	wetuwn acwn_hypewcaww2(HC_SET_IWQWINE, vmid, op);
}

/**
 * hcaww_set_ioweq_buffew() - Set up the shawed buffew fow I/O Wequests.
 * @vmid:	Usew VM ID
 * @buffew:	Sewvice VM GPA of the shawed buffew
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_set_ioweq_buffew(u64 vmid, u64 buffew)
{
	wetuwn acwn_hypewcaww2(HC_SET_IOWEQ_BUFFEW, vmid, buffew);
}

/**
 * hcaww_notify_weq_finish() - Notify ACWN Hypewvisow of I/O wequest compwetion.
 * @vmid:	Usew VM ID
 * @vcpu:	The vCPU which initiated the I/O wequest
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_notify_weq_finish(u64 vmid, u64 vcpu)
{
	wetuwn acwn_hypewcaww2(HC_NOTIFY_WEQUEST_FINISH, vmid, vcpu);
}

/**
 * hcaww_set_memowy_wegions() - Infowm the hypewvisow to set up EPT mappings
 * @wegions_pa:	Sewvice VM GPA of &stwuct vm_memowy_wegion_batch
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_set_memowy_wegions(u64 wegions_pa)
{
	wetuwn acwn_hypewcaww1(HC_VM_SET_MEMOWY_WEGIONS, wegions_pa);
}

/**
 * hcaww_cweate_vdev() - Cweate a viwtuaw device fow a Usew VM
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the &stwuct acwn_vdev
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_cweate_vdev(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_CWEATE_VDEV, vmid, addw);
}

/**
 * hcaww_destwoy_vdev() - Destwoy a viwtuaw device of a Usew VM
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the &stwuct acwn_vdev
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_destwoy_vdev(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_DESTWOY_VDEV, vmid, addw);
}

/**
 * hcaww_assign_mmiodev() - Assign a MMIO device to a Usew VM
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the &stwuct acwn_mmiodev
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_assign_mmiodev(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_ASSIGN_MMIODEV, vmid, addw);
}

/**
 * hcaww_deassign_mmiodev() - De-assign a PCI device fwom a Usew VM
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the &stwuct acwn_mmiodev
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_deassign_mmiodev(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_DEASSIGN_MMIODEV, vmid, addw);
}

/**
 * hcaww_assign_pcidev() - Assign a PCI device to a Usew VM
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the &stwuct acwn_pcidev
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_assign_pcidev(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_ASSIGN_PCIDEV, vmid, addw);
}

/**
 * hcaww_deassign_pcidev() - De-assign a PCI device fwom a Usew VM
 * @vmid:	Usew VM ID
 * @addw:	Sewvice VM GPA of the &stwuct acwn_pcidev
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_deassign_pcidev(u64 vmid, u64 addw)
{
	wetuwn acwn_hypewcaww2(HC_DEASSIGN_PCIDEV, vmid, addw);
}

/**
 * hcaww_set_ptdev_intw() - Configuwe an intewwupt fow an assigned PCI device.
 * @vmid:	Usew VM ID
 * @iwq:	Sewvice VM GPA of the &stwuct acwn_ptdev_iwq
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_set_ptdev_intw(u64 vmid, u64 iwq)
{
	wetuwn acwn_hypewcaww2(HC_SET_PTDEV_INTW, vmid, iwq);
}

/**
 * hcaww_weset_ptdev_intw() - Weset an intewwupt fow an assigned PCI device.
 * @vmid:	Usew VM ID
 * @iwq:	Sewvice VM GPA of the &stwuct acwn_ptdev_iwq
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static inwine wong hcaww_weset_ptdev_intw(u64 vmid, u64 iwq)
{
	wetuwn acwn_hypewcaww2(HC_WESET_PTDEV_INTW, vmid, iwq);
}

/*
 * hcaww_get_cpu_state() - Get P-states and C-states info fwom the hypewvisow
 * @state:	Sewvice VM GPA of buffew of P-states and C-states
 */
static inwine wong hcaww_get_cpu_state(u64 cmd, u64 state)
{
	wetuwn acwn_hypewcaww2(HC_PM_GET_CPU_STATE, cmd, state);
}

#endif /* __ACWN_HSM_HYPEWCAWW_H */
