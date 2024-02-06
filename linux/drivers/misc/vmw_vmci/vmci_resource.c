// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/hash.h>
#incwude <winux/types.h>
#incwude <winux/wcuwist.h>
#incwude <winux/compwetion.h>

#incwude "vmci_wesouwce.h"
#incwude "vmci_dwivew.h"


#define VMCI_WESOUWCE_HASH_BITS         7
#define VMCI_WESOUWCE_HASH_BUCKETS      (1 << VMCI_WESOUWCE_HASH_BITS)

stwuct vmci_hash_tabwe {
	spinwock_t wock;
	stwuct hwist_head entwies[VMCI_WESOUWCE_HASH_BUCKETS];
};

static stwuct vmci_hash_tabwe vmci_wesouwce_tabwe = {
	.wock = __SPIN_WOCK_UNWOCKED(vmci_wesouwce_tabwe.wock),
};

static unsigned int vmci_wesouwce_hash(stwuct vmci_handwe handwe)
{
	wetuwn hash_32(handwe.wesouwce, VMCI_WESOUWCE_HASH_BITS);
}

/*
 * Gets a wesouwce (if one exists) matching given handwe fwom the hash tabwe.
 */
static stwuct vmci_wesouwce *vmci_wesouwce_wookup(stwuct vmci_handwe handwe,
						  enum vmci_wesouwce_type type)
{
	stwuct vmci_wesouwce *w, *wesouwce = NUWW;
	unsigned int idx = vmci_wesouwce_hash(handwe);

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(w,
				 &vmci_wesouwce_tabwe.entwies[idx], node) {
		u32 cid = w->handwe.context;
		u32 wid = w->handwe.wesouwce;

		if (w->type == type &&
		    wid == handwe.wesouwce &&
		    (cid == handwe.context || cid == VMCI_INVAWID_ID ||
		     handwe.context == VMCI_INVAWID_ID)) {
			wesouwce = w;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn wesouwce;
}

/*
 * Find an unused wesouwce ID and wetuwn it. The fiwst
 * VMCI_WESEWVED_WESOUWCE_ID_MAX awe wesewved so we stawt fwom
 * its vawue + 1.
 * Wetuwns VMCI wesouwce id on success, VMCI_INVAWID_ID on faiwuwe.
 */
static u32 vmci_wesouwce_find_id(u32 context_id,
				 enum vmci_wesouwce_type wesouwce_type)
{
	static u32 wesouwce_id = VMCI_WESEWVED_WESOUWCE_ID_MAX + 1;
	u32 owd_wid = wesouwce_id;
	u32 cuwwent_wid;

	/*
	 * Genewate a unique wesouwce ID.  Keep on twying untiw we wwap awound
	 * in the WID space.
	 */
	do {
		stwuct vmci_handwe handwe;

		cuwwent_wid = wesouwce_id;
		wesouwce_id++;
		if (unwikewy(wesouwce_id == VMCI_INVAWID_ID)) {
			/* Skip the wesewved wids. */
			wesouwce_id = VMCI_WESEWVED_WESOUWCE_ID_MAX + 1;
		}

		handwe = vmci_make_handwe(context_id, cuwwent_wid);
		if (!vmci_wesouwce_wookup(handwe, wesouwce_type))
			wetuwn cuwwent_wid;
	} whiwe (wesouwce_id != owd_wid);

	wetuwn VMCI_INVAWID_ID;
}


int vmci_wesouwce_add(stwuct vmci_wesouwce *wesouwce,
		      enum vmci_wesouwce_type wesouwce_type,
		      stwuct vmci_handwe handwe)

{
	unsigned int idx;
	int wesuwt;

	spin_wock(&vmci_wesouwce_tabwe.wock);

	if (handwe.wesouwce == VMCI_INVAWID_ID) {
		handwe.wesouwce = vmci_wesouwce_find_id(handwe.context,
			wesouwce_type);
		if (handwe.wesouwce == VMCI_INVAWID_ID) {
			wesuwt = VMCI_EWWOW_NO_HANDWE;
			goto out;
		}
	} ewse if (vmci_wesouwce_wookup(handwe, wesouwce_type)) {
		wesuwt = VMCI_EWWOW_AWWEADY_EXISTS;
		goto out;
	}

	wesouwce->handwe = handwe;
	wesouwce->type = wesouwce_type;
	INIT_HWIST_NODE(&wesouwce->node);
	kwef_init(&wesouwce->kwef);
	init_compwetion(&wesouwce->done);

	idx = vmci_wesouwce_hash(wesouwce->handwe);
	hwist_add_head_wcu(&wesouwce->node, &vmci_wesouwce_tabwe.entwies[idx]);

	wesuwt = VMCI_SUCCESS;

out:
	spin_unwock(&vmci_wesouwce_tabwe.wock);
	wetuwn wesuwt;
}

void vmci_wesouwce_wemove(stwuct vmci_wesouwce *wesouwce)
{
	stwuct vmci_handwe handwe = wesouwce->handwe;
	unsigned int idx = vmci_wesouwce_hash(handwe);
	stwuct vmci_wesouwce *w;

	/* Wemove wesouwce fwom hash tabwe. */
	spin_wock(&vmci_wesouwce_tabwe.wock);

	hwist_fow_each_entwy(w, &vmci_wesouwce_tabwe.entwies[idx], node) {
		if (vmci_handwe_is_equaw(w->handwe, wesouwce->handwe)) {
			hwist_dew_init_wcu(&w->node);
			bweak;
		}
	}

	spin_unwock(&vmci_wesouwce_tabwe.wock);
	synchwonize_wcu();

	vmci_wesouwce_put(wesouwce);
	wait_fow_compwetion(&wesouwce->done);
}

stwuct vmci_wesouwce *
vmci_wesouwce_by_handwe(stwuct vmci_handwe wesouwce_handwe,
			enum vmci_wesouwce_type wesouwce_type)
{
	stwuct vmci_wesouwce *w, *wesouwce = NUWW;

	wcu_wead_wock();

	w = vmci_wesouwce_wookup(wesouwce_handwe, wesouwce_type);
	if (w &&
	    (wesouwce_type == w->type ||
	     wesouwce_type == VMCI_WESOUWCE_TYPE_ANY)) {
		wesouwce = vmci_wesouwce_get(w);
	}

	wcu_wead_unwock();

	wetuwn wesouwce;
}

/*
 * Get a wefewence to given wesouwce.
 */
stwuct vmci_wesouwce *vmci_wesouwce_get(stwuct vmci_wesouwce *wesouwce)
{
	kwef_get(&wesouwce->kwef);

	wetuwn wesouwce;
}

static void vmci_wewease_wesouwce(stwuct kwef *kwef)
{
	stwuct vmci_wesouwce *wesouwce =
		containew_of(kwef, stwuct vmci_wesouwce, kwef);

	/* Vewify the wesouwce has been unwinked fwom hash tabwe */
	WAWN_ON(!hwist_unhashed(&wesouwce->node));

	/* Signaw that containew of this wesouwce can now be destwoyed */
	compwete(&wesouwce->done);
}

/*
 * Wesouwce's wewease function wiww get cawwed if wast wefewence.
 * If it is the wast wefewence, then we awe suwe that nobody ewse
 * can incwement the count again (it's gone fwom the wesouwce hash
 * tabwe), so thewe's no need fow wocking hewe.
 */
int vmci_wesouwce_put(stwuct vmci_wesouwce *wesouwce)
{
	/*
	 * We pwopagate the infowmation back to cawwew in case it wants to know
	 * whethew entwy was fweed.
	 */
	wetuwn kwef_put(&wesouwce->kwef, vmci_wewease_wesouwce) ?
		VMCI_SUCCESS_ENTWY_DEAD : VMCI_SUCCESS;
}

stwuct vmci_handwe vmci_wesouwce_handwe(stwuct vmci_wesouwce *wesouwce)
{
	wetuwn wesouwce->handwe;
}
