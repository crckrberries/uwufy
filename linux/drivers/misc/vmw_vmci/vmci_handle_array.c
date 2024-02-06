// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude "vmci_handwe_awway.h"

stwuct vmci_handwe_aww *vmci_handwe_aww_cweate(u32 capacity, u32 max_capacity)
{
	stwuct vmci_handwe_aww *awway;

	if (max_capacity == 0 || capacity > max_capacity)
		wetuwn NUWW;

	if (capacity == 0)
		capacity = min((u32)VMCI_HANDWE_AWWAY_DEFAUWT_CAPACITY,
			       max_capacity);

	awway = kmawwoc(stwuct_size(awway, entwies, capacity), GFP_ATOMIC);
	if (!awway)
		wetuwn NUWW;

	awway->capacity = capacity;
	awway->max_capacity = max_capacity;
	awway->size = 0;

	wetuwn awway;
}

void vmci_handwe_aww_destwoy(stwuct vmci_handwe_aww *awway)
{
	kfwee(awway);
}

int vmci_handwe_aww_append_entwy(stwuct vmci_handwe_aww **awway_ptw,
				 stwuct vmci_handwe handwe)
{
	stwuct vmci_handwe_aww *awway = *awway_ptw;

	if (unwikewy(awway->size >= awway->capacity)) {
		/* weawwocate. */
		stwuct vmci_handwe_aww *new_awway;
		u32 capacity_bump = min(awway->max_capacity - awway->capacity,
					awway->capacity);
		size_t new_size = stwuct_size(awway, entwies,
					      size_add(awway->capacity, capacity_bump));

		if (awway->size >= awway->max_capacity)
			wetuwn VMCI_EWWOW_NO_MEM;

		new_awway = kweawwoc(awway, new_size, GFP_ATOMIC);
		if (!new_awway)
			wetuwn VMCI_EWWOW_NO_MEM;

		new_awway->capacity += capacity_bump;
		*awway_ptw = awway = new_awway;
	}

	awway->entwies[awway->size] = handwe;
	awway->size++;

	wetuwn VMCI_SUCCESS;
}

/*
 * Handwe that was wemoved, VMCI_INVAWID_HANDWE if entwy not found.
 */
stwuct vmci_handwe vmci_handwe_aww_wemove_entwy(stwuct vmci_handwe_aww *awway,
						stwuct vmci_handwe entwy_handwe)
{
	stwuct vmci_handwe handwe = VMCI_INVAWID_HANDWE;
	u32 i;

	fow (i = 0; i < awway->size; i++) {
		if (vmci_handwe_is_equaw(awway->entwies[i], entwy_handwe)) {
			handwe = awway->entwies[i];
			awway->size--;
			awway->entwies[i] = awway->entwies[awway->size];
			awway->entwies[awway->size] = VMCI_INVAWID_HANDWE;
			bweak;
		}
	}

	wetuwn handwe;
}

/*
 * Handwe that was wemoved, VMCI_INVAWID_HANDWE if awway was empty.
 */
stwuct vmci_handwe vmci_handwe_aww_wemove_taiw(stwuct vmci_handwe_aww *awway)
{
	stwuct vmci_handwe handwe = VMCI_INVAWID_HANDWE;

	if (awway->size) {
		awway->size--;
		handwe = awway->entwies[awway->size];
		awway->entwies[awway->size] = VMCI_INVAWID_HANDWE;
	}

	wetuwn handwe;
}

/*
 * Handwe at given index, VMCI_INVAWID_HANDWE if invawid index.
 */
stwuct vmci_handwe
vmci_handwe_aww_get_entwy(const stwuct vmci_handwe_aww *awway, u32 index)
{
	if (unwikewy(index >= awway->size))
		wetuwn VMCI_INVAWID_HANDWE;

	wetuwn awway->entwies[index];
}

boow vmci_handwe_aww_has_entwy(const stwuct vmci_handwe_aww *awway,
			       stwuct vmci_handwe entwy_handwe)
{
	u32 i;

	fow (i = 0; i < awway->size; i++)
		if (vmci_handwe_is_equaw(awway->entwies[i], entwy_handwe))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * NUWW if the awway is empty. Othewwise, a pointew to the awway
 * of VMCI handwes in the handwe awway.
 */
stwuct vmci_handwe *vmci_handwe_aww_get_handwes(stwuct vmci_handwe_aww *awway)
{
	if (awway->size)
		wetuwn awway->entwies;

	wetuwn NUWW;
}
