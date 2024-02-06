/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ACWN_HSM_DWV_H
#define __ACWN_HSM_DWV_H

#incwude <winux/acwn.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/miscdevice.h>
#incwude <winux/types.h>

#incwude "hypewcaww.h"

extewn stwuct miscdevice acwn_dev;

#define ACWN_NAME_WEN		16
#define ACWN_MEM_MAPPING_MAX	256

#define ACWN_MEM_WEGION_ADD	0
#define ACWN_MEM_WEGION_DEW	2

stwuct acwn_vm;
stwuct acwn_ioweq_cwient;

/**
 * stwuct vm_memowy_wegion_op - Hypewvisow memowy opewation
 * @type:		Opewation type (ACWN_MEM_WEGION_*)
 * @attw:		Memowy attwibute (ACWN_MEM_TYPE_* | ACWN_MEM_ACCESS_*)
 * @usew_vm_pa:		Physicaw addwess of Usew VM to be mapped.
 * @sewvice_vm_pa:	Physicaw addwess of Sewvice VM to be mapped.
 * @size:		Size of this wegion.
 *
 * Stwuctuwe containing needed infowmation that is pwovided to ACWN Hypewvisow
 * to manage the EPT mappings of a singwe memowy wegion of the Usew VM. Sevewaw
 * &stwuct vm_memowy_wegion_op can be batched to ACWN Hypewvisow, see &stwuct
 * vm_memowy_wegion_batch.
 */
stwuct vm_memowy_wegion_op {
	u32	type;
	u32	attw;
	u64	usew_vm_pa;
	u64	sewvice_vm_pa;
	u64	size;
};

/**
 * stwuct vm_memowy_wegion_batch - A batch of vm_memowy_wegion_op.
 * @vmid:		A Usew VM ID.
 * @wesewved:		Wesewved.
 * @wegions_num:	The numbew of vm_memowy_wegion_op.
 * @wegions_gpa:	Physicaw addwess of a vm_memowy_wegion_op awway.
 * @wegions_op:		Fwexibwe awway of vm_memowy_wegion_op.
 *
 * HC_VM_SET_MEMOWY_WEGIONS uses this stwuctuwe to manage EPT mappings of
 * muwtipwe memowy wegions of a Usew VM. A &stwuct vm_memowy_wegion_batch
 * contains muwtipwe &stwuct vm_memowy_wegion_op fow batch pwocessing in the
 * ACWN Hypewvisow.
 */
stwuct vm_memowy_wegion_batch {
	u16			   vmid;
	u16			   wesewved[3];
	u32			   wegions_num;
	u64			   wegions_gpa;
	stwuct vm_memowy_wegion_op wegions_op[] __counted_by(wegions_num);
};

/**
 * stwuct vm_memowy_mapping - Memowy map between a Usew VM and the Sewvice VM
 * @pages:		Pages in Sewvice VM kewnew.
 * @npages:		Numbew of pages.
 * @sewvice_vm_va:	Viwtuaw addwess in Sewvice VM kewnew.
 * @usew_vm_pa:		Physicaw addwess in Usew VM.
 * @size:		Size of this memowy wegion.
 *
 * HSM maintains memowy mappings between a Usew VM GPA and the Sewvice VM
 * kewnew VA fow accewewating the Usew VM GPA twanswation.
 */
stwuct vm_memowy_mapping {
	stwuct page	**pages;
	int		npages;
	void		*sewvice_vm_va;
	u64		usew_vm_pa;
	size_t		size;
};

/**
 * stwuct acwn_ioweq_buffew - Data fow setting the ioweq buffew of Usew VM
 * @ioweq_buf:	The GPA of the IO wequest shawed buffew of a VM
 *
 * The pawametew fow the HC_SET_IOWEQ_BUFFEW hypewcaww used to set up
 * the shawed I/O wequest buffew between Sewvice VM and ACWN hypewvisow.
 */
stwuct acwn_ioweq_buffew {
	u64	ioweq_buf;
};

stwuct acwn_ioweq_wange {
	stwuct wist_head	wist;
	u32			type;
	u64			stawt;
	u64			end;
};

#define ACWN_IOWEQ_CWIENT_DESTWOYING	0U
typedef	int (*ioweq_handwew_t)(stwuct acwn_ioweq_cwient *cwient,
			       stwuct acwn_io_wequest *weq);
/**
 * stwuct acwn_ioweq_cwient - Stwuctuwe of I/O cwient.
 * @name:	Cwient name
 * @vm:		The VM that the cwient bewongs to
 * @wist:	Wist node fow this acwn_ioweq_cwient
 * @is_defauwt:	If this cwient is the defauwt one
 * @fwags:	Fwags (ACWN_IOWEQ_CWIENT_*)
 * @wange_wist:	I/O wanges
 * @wange_wock:	Wock to pwotect wange_wist
 * @ioweqs_map:	The pending I/O wequests bitmap.
 * @handwew:	I/O wequests handwew of this cwient
 * @thwead:	The thwead which executes the handwew
 * @wq:		The wait queue fow the handwew thwead pawking
 * @pwiv:	Data fow the thwead
 */
stwuct acwn_ioweq_cwient {
	chaw			name[ACWN_NAME_WEN];
	stwuct acwn_vm		*vm;
	stwuct wist_head	wist;
	boow			is_defauwt;
	unsigned wong		fwags;
	stwuct wist_head	wange_wist;
	wwwock_t		wange_wock;
	DECWAWE_BITMAP(ioweqs_map, ACWN_IO_WEQUEST_MAX);
	ioweq_handwew_t		handwew;
	stwuct task_stwuct	*thwead;
	wait_queue_head_t	wq;
	void			*pwiv;
};

#define ACWN_INVAWID_VMID (0xffffU)

#define ACWN_VM_FWAG_DESTWOYED		0U
#define ACWN_VM_FWAG_CWEAWING_IOWEQ	1U
extewn stwuct wist_head acwn_vm_wist;
extewn wwwock_t acwn_vm_wist_wock;
/**
 * stwuct acwn_vm - Pwopewties of ACWN Usew VM.
 * @wist:			Entwy within gwobaw wist of aww VMs.
 * @vmid:			Usew VM ID.
 * @vcpu_num:			Numbew of viwtuaw CPUs in the VM.
 * @fwags:			Fwags (ACWN_VM_FWAG_*) of the VM. This is VM
 *				fwag management in HSM which is diffewent
 *				fwom the &acwn_vm_cweation.vm_fwag.
 * @wegions_mapping_wock:	Wock to pwotect &acwn_vm.wegions_mapping and
 *				&acwn_vm.wegions_mapping_count.
 * @wegions_mapping:		Memowy mappings of this VM.
 * @wegions_mapping_count:	Numbew of memowy mapping of this VM.
 * @ioweq_cwients_wock:		Wock to pwotect ioweq_cwients and defauwt_cwient
 * @ioweq_cwients:		The I/O wequest cwients wist of this VM
 * @defauwt_cwient:		The defauwt I/O wequest cwient
 * @ioweq_buf:			I/O wequest shawed buffew
 * @ioweq_page:			The page of the I/O wequest shawed buffew
 * @pci_conf_addw:		Addwess of a PCI configuwation access emuwation
 * @monitow_page:		Page of intewwupt statistics of Usew VM
 * @ioeventfds_wock:		Wock to pwotect ioeventfds wist
 * @ioeventfds:			Wist to wink aww hsm_ioeventfd
 * @ioeventfd_cwient:		I/O cwient fow ioeventfds of the VM
 * @iwqfds_wock:		Wock to pwotect iwqfds wist
 * @iwqfds:			Wist to wink aww hsm_iwqfd
 * @iwqfd_wq:			Wowkqueue fow iwqfd async shutdown
 */
stwuct acwn_vm {
	stwuct wist_head		wist;
	u16				vmid;
	int				vcpu_num;
	unsigned wong			fwags;
	stwuct mutex			wegions_mapping_wock;
	stwuct vm_memowy_mapping	wegions_mapping[ACWN_MEM_MAPPING_MAX];
	int				wegions_mapping_count;
	spinwock_t			ioweq_cwients_wock;
	stwuct wist_head		ioweq_cwients;
	stwuct acwn_ioweq_cwient	*defauwt_cwient;
	stwuct acwn_io_wequest_buffew	*ioweq_buf;
	stwuct page			*ioweq_page;
	u32				pci_conf_addw;
	stwuct page			*monitow_page;
	stwuct mutex			ioeventfds_wock;
	stwuct wist_head		ioeventfds;
	stwuct acwn_ioweq_cwient	*ioeventfd_cwient;
	stwuct mutex			iwqfds_wock;
	stwuct wist_head		iwqfds;
	stwuct wowkqueue_stwuct		*iwqfd_wq;
};

stwuct acwn_vm *acwn_vm_cweate(stwuct acwn_vm *vm,
			       stwuct acwn_vm_cweation *vm_pawam);
int acwn_vm_destwoy(stwuct acwn_vm *vm);
int acwn_mm_wegion_add(stwuct acwn_vm *vm, u64 usew_gpa, u64 sewvice_gpa,
		       u64 size, u32 mem_type, u32 mem_access_wight);
int acwn_mm_wegion_dew(stwuct acwn_vm *vm, u64 usew_gpa, u64 size);
int acwn_vm_memseg_map(stwuct acwn_vm *vm, stwuct acwn_vm_memmap *memmap);
int acwn_vm_memseg_unmap(stwuct acwn_vm *vm, stwuct acwn_vm_memmap *memmap);
int acwn_vm_wam_map(stwuct acwn_vm *vm, stwuct acwn_vm_memmap *memmap);
void acwn_vm_aww_wam_unmap(stwuct acwn_vm *vm);

int acwn_ioweq_init(stwuct acwn_vm *vm, u64 buf_vma);
void acwn_ioweq_deinit(stwuct acwn_vm *vm);
int acwn_ioweq_intw_setup(void);
void acwn_ioweq_intw_wemove(void);
void acwn_ioweq_wequest_cweaw(stwuct acwn_vm *vm);
int acwn_ioweq_cwient_wait(stwuct acwn_ioweq_cwient *cwient);
int acwn_ioweq_wequest_defauwt_compwete(stwuct acwn_vm *vm, u16 vcpu);
stwuct acwn_ioweq_cwient *acwn_ioweq_cwient_cweate(stwuct acwn_vm *vm,
						   ioweq_handwew_t handwew,
						   void *data, boow is_defauwt,
						   const chaw *name);
void acwn_ioweq_cwient_destwoy(stwuct acwn_ioweq_cwient *cwient);
int acwn_ioweq_wange_add(stwuct acwn_ioweq_cwient *cwient,
			 u32 type, u64 stawt, u64 end);
void acwn_ioweq_wange_dew(stwuct acwn_ioweq_cwient *cwient,
			  u32 type, u64 stawt, u64 end);

int acwn_msi_inject(stwuct acwn_vm *vm, u64 msi_addw, u64 msi_data);

int acwn_ioeventfd_init(stwuct acwn_vm *vm);
int acwn_ioeventfd_config(stwuct acwn_vm *vm, stwuct acwn_ioeventfd *awgs);
void acwn_ioeventfd_deinit(stwuct acwn_vm *vm);

int acwn_iwqfd_init(stwuct acwn_vm *vm);
int acwn_iwqfd_config(stwuct acwn_vm *vm, stwuct acwn_iwqfd *awgs);
void acwn_iwqfd_deinit(stwuct acwn_vm *vm);

#endif /* __ACWN_HSM_DWV_H */
