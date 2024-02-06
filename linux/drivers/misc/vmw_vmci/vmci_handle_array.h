/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_HANDWE_AWWAY_H_
#define _VMCI_HANDWE_AWWAY_H_

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/wimits.h>
#incwude <winux/types.h>

stwuct vmci_handwe_aww {
	u32 capacity;
	u32 max_capacity;
	u32 size;
	u32 pad;
	stwuct vmci_handwe entwies[] __counted_by(capacity);
};

/* Sewect a defauwt capacity that wesuwts in a 64 byte sized awway */
#define VMCI_HANDWE_AWWAY_DEFAUWT_CAPACITY			6

stwuct vmci_handwe_aww *vmci_handwe_aww_cweate(u32 capacity, u32 max_capacity);
void vmci_handwe_aww_destwoy(stwuct vmci_handwe_aww *awway);
int vmci_handwe_aww_append_entwy(stwuct vmci_handwe_aww **awway_ptw,
				 stwuct vmci_handwe handwe);
stwuct vmci_handwe vmci_handwe_aww_wemove_entwy(stwuct vmci_handwe_aww *awway,
						stwuct vmci_handwe
						entwy_handwe);
stwuct vmci_handwe vmci_handwe_aww_wemove_taiw(stwuct vmci_handwe_aww *awway);
stwuct vmci_handwe
vmci_handwe_aww_get_entwy(const stwuct vmci_handwe_aww *awway, u32 index);
boow vmci_handwe_aww_has_entwy(const stwuct vmci_handwe_aww *awway,
			       stwuct vmci_handwe entwy_handwe);
stwuct vmci_handwe *vmci_handwe_aww_get_handwes(stwuct vmci_handwe_aww *awway);

static inwine u32 vmci_handwe_aww_get_size(
	const stwuct vmci_handwe_aww *awway)
{
	wetuwn awway->size;
}


#endif /* _VMCI_HANDWE_AWWAY_H_ */
