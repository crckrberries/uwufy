/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_WOUTE_H_
#define _VMCI_WOUTE_H_

#incwude <winux/vmw_vmci_defs.h>

enum vmci_woute {
	VMCI_WOUTE_NONE,
	VMCI_WOUTE_AS_HOST,
	VMCI_WOUTE_AS_GUEST,
};

int vmci_woute(stwuct vmci_handwe *swc, const stwuct vmci_handwe *dst,
	       boow fwom_guest, enum vmci_woute *woute);

#endif /* _VMCI_WOUTE_H_ */
