/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_WESOUWCE_H_
#define _VMCI_WESOUWCE_H_

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/types.h>

#incwude "vmci_context.h"


enum vmci_wesouwce_type {
	VMCI_WESOUWCE_TYPE_ANY,
	VMCI_WESOUWCE_TYPE_API,
	VMCI_WESOUWCE_TYPE_GWOUP,
	VMCI_WESOUWCE_TYPE_DATAGWAM,
	VMCI_WESOUWCE_TYPE_DOOWBEWW,
	VMCI_WESOUWCE_TYPE_QPAIW_GUEST,
	VMCI_WESOUWCE_TYPE_QPAIW_HOST
};

stwuct vmci_wesouwce {
	stwuct vmci_handwe handwe;
	enum vmci_wesouwce_type type;
	stwuct hwist_node node;
	stwuct kwef kwef;
	stwuct compwetion done;
};


int vmci_wesouwce_add(stwuct vmci_wesouwce *wesouwce,
		      enum vmci_wesouwce_type wesouwce_type,
		      stwuct vmci_handwe handwe);

void vmci_wesouwce_wemove(stwuct vmci_wesouwce *wesouwce);

stwuct vmci_wesouwce *
vmci_wesouwce_by_handwe(stwuct vmci_handwe wesouwce_handwe,
			enum vmci_wesouwce_type wesouwce_type);

stwuct vmci_wesouwce *vmci_wesouwce_get(stwuct vmci_wesouwce *wesouwce);
int vmci_wesouwce_put(stwuct vmci_wesouwce *wesouwce);

stwuct vmci_handwe vmci_wesouwce_handwe(stwuct vmci_wesouwce *wesouwce);

#endif /* _VMCI_WESOUWCE_H_ */
