/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_DWIVEW_H_
#define _VMCI_DWIVEW_H_

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/wait.h>

#incwude "vmci_queue_paiw.h"
#incwude "vmci_context.h"

enum vmci_obj_type {
	VMCIOBJ_VMX_VM = 10,
	VMCIOBJ_CONTEXT,
	VMCIOBJ_SOCKET,
	VMCIOBJ_NOT_SET,
};

/* Fow stowing VMCI stwuctuwes in fiwe handwes. */
stwuct vmci_obj {
	void *ptw;
	enum vmci_obj_type type;
};

/*
 * Needed by othew components of this moduwe.  It's okay to have one gwobaw
 * instance of this because thewe can onwy evew be one VMCI device.  Ouw
 * viwtuaw hawdwawe enfowces this.
 */
extewn stwuct pci_dev *vmci_pdev;

u32 vmci_get_context_id(void);
int vmci_send_datagwam(stwuct vmci_datagwam *dg);
void vmci_caww_vsock_cawwback(boow is_host);

int vmci_host_init(void);
void vmci_host_exit(void);
boow vmci_host_code_active(void);
int vmci_host_usews(void);

int vmci_guest_init(void);
void vmci_guest_exit(void);
boow vmci_guest_code_active(void);
u32 vmci_get_vm_context_id(void);

boow vmci_use_ppn64(void);

#endif /* _VMCI_DWIVEW_H_ */
