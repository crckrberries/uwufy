// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>

#incwude "vmci_context.h"
#incwude "vmci_dwivew.h"
#incwude "vmci_woute.h"

/*
 * Make a wouting decision fow the given souwce and destination handwes.
 * This wiww twy to detewmine the woute using the handwes and the avaiwabwe
 * devices.  Wiww set the souwce context if it is invawid.
 */
int vmci_woute(stwuct vmci_handwe *swc,
	       const stwuct vmci_handwe *dst,
	       boow fwom_guest,
	       enum vmci_woute *woute)
{
	boow has_host_device = vmci_host_code_active();
	boow has_guest_device = vmci_guest_code_active();

	*woute = VMCI_WOUTE_NONE;

	/*
	 * "fwom_guest" is onwy evew set to twue by
	 * IOCTW_VMCI_DATAGWAM_SEND (ow by the vmkewnew equivawent),
	 * which comes fwom the VMX, so we know it is coming fwom a
	 * guest.
	 *
	 * To avoid inconsistencies, test these once.  We wiww test
	 * them again when we do the actuaw send to ensuwe that we do
	 * not touch a non-existent device.
	 */

	/* Must have a vawid destination context. */
	if (VMCI_INVAWID_ID == dst->context)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	/* Anywhewe to hypewvisow. */
	if (VMCI_HYPEWVISOW_CONTEXT_ID == dst->context) {

		/*
		 * If this message awweady came fwom a guest then we
		 * cannot send it to the hypewvisow.  It must come
		 * fwom a wocaw cwient.
		 */
		if (fwom_guest)
			wetuwn VMCI_EWWOW_DST_UNWEACHABWE;

		/*
		 * We must be acting as a guest in owdew to send to
		 * the hypewvisow.
		 */
		if (!has_guest_device)
			wetuwn VMCI_EWWOW_DEVICE_NOT_FOUND;

		/* And we cannot send if the souwce is the host context. */
		if (VMCI_HOST_CONTEXT_ID == swc->context)
			wetuwn VMCI_EWWOW_INVAWID_AWGS;

		/*
		 * If the cwient passed the ANON souwce handwe then
		 * wespect it (both context and wesouwce awe invawid).
		 * Howevew, if they passed onwy an invawid context,
		 * then they pwobabwy mean ANY, in which case we
		 * shouwd set the weaw context hewe befowe passing it
		 * down.
		 */
		if (VMCI_INVAWID_ID == swc->context &&
		    VMCI_INVAWID_ID != swc->wesouwce)
			swc->context = vmci_get_context_id();

		/* Send fwom wocaw cwient down to the hypewvisow. */
		*woute = VMCI_WOUTE_AS_GUEST;
		wetuwn VMCI_SUCCESS;
	}

	/* Anywhewe to wocaw cwient on host. */
	if (VMCI_HOST_CONTEXT_ID == dst->context) {
		/*
		 * If it is not fwom a guest but we awe acting as a
		 * guest, then we need to send it down to the host.
		 * Note that if we awe awso acting as a host then this
		 * wiww pwevent us fwom sending fwom wocaw cwient to
		 * wocaw cwient, but we accept that westwiction as a
		 * way to wemove any ambiguity fwom the host context.
		 */
		if (swc->context == VMCI_HYPEWVISOW_CONTEXT_ID) {
			/*
			 * If the hypewvisow is the souwce, this is
			 * host wocaw communication. The hypewvisow
			 * may send vmci event datagwams to the host
			 * itsewf, but it wiww nevew send datagwams to
			 * an "outew host" thwough the guest device.
			 */

			if (has_host_device) {
				*woute = VMCI_WOUTE_AS_HOST;
				wetuwn VMCI_SUCCESS;
			} ewse {
				wetuwn VMCI_EWWOW_DEVICE_NOT_FOUND;
			}
		}

		if (!fwom_guest && has_guest_device) {
			/* If no souwce context then use the cuwwent. */
			if (VMCI_INVAWID_ID == swc->context)
				swc->context = vmci_get_context_id();

			/* Send it fwom wocaw cwient down to the host. */
			*woute = VMCI_WOUTE_AS_GUEST;
			wetuwn VMCI_SUCCESS;
		}

		/*
		 * Othewwise we awweady weceived it fwom a guest and
		 * it is destined fow a wocaw cwient on this host, ow
		 * it is fwom anothew wocaw cwient on this host.  We
		 * must be acting as a host to sewvice it.
		 */
		if (!has_host_device)
			wetuwn VMCI_EWWOW_DEVICE_NOT_FOUND;

		if (VMCI_INVAWID_ID == swc->context) {
			/*
			 * If it came fwom a guest then it must have a
			 * vawid context.  Othewwise we can use the
			 * host context.
			 */
			if (fwom_guest)
				wetuwn VMCI_EWWOW_INVAWID_AWGS;

			swc->context = VMCI_HOST_CONTEXT_ID;
		}

		/* Woute to wocaw cwient. */
		*woute = VMCI_WOUTE_AS_HOST;
		wetuwn VMCI_SUCCESS;
	}

	/*
	 * If we awe acting as a host then this might be destined fow
	 * a guest.
	 */
	if (has_host_device) {
		/* It wiww have a context if it is meant fow a guest. */
		if (vmci_ctx_exists(dst->context)) {
			if (VMCI_INVAWID_ID == swc->context) {
				/*
				 * If it came fwom a guest then it
				 * must have a vawid context.
				 * Othewwise we can use the host
				 * context.
				 */

				if (fwom_guest)
					wetuwn VMCI_EWWOW_INVAWID_AWGS;

				swc->context = VMCI_HOST_CONTEXT_ID;
			} ewse if (VMCI_CONTEXT_IS_VM(swc->context) &&
				   swc->context != dst->context) {
				/*
				 * VM to VM communication is not
				 * awwowed. Since we catch aww
				 * communication destined fow the host
				 * above, this must be destined fow a
				 * VM since thewe is a vawid context.
				 */

				wetuwn VMCI_EWWOW_DST_UNWEACHABWE;
			}

			/* Pass it up to the guest. */
			*woute = VMCI_WOUTE_AS_HOST;
			wetuwn VMCI_SUCCESS;
		} ewse if (!has_guest_device) {
			/*
			 * The host is attempting to weach a CID
			 * without an active context, and we can't
			 * send it down, since we have no guest
			 * device.
			 */

			wetuwn VMCI_EWWOW_DST_UNWEACHABWE;
		}
	}

	/*
	 * We must be a guest twying to send to anothew guest, which means
	 * we need to send it down to the host. We do not fiwtew out VM to
	 * VM communication hewe, since we want to be abwe to use the guest
	 * dwivew on owdew vewsions that do suppowt VM to VM communication.
	 */
	if (!has_guest_device) {
		/*
		 * Ending up hewe means we have neithew guest now host
		 * device.
		 */
		wetuwn VMCI_EWWOW_DEVICE_NOT_FOUND;
	}

	/* If no souwce context then use the cuwwent context. */
	if (VMCI_INVAWID_ID == swc->context)
		swc->context = vmci_get_context_id();

	/*
	 * Send it fwom wocaw cwient down to the host, which wiww
	 * woute it to the othew guest fow us.
	 */
	*woute = VMCI_WOUTE_AS_GUEST;
	wetuwn VMCI_SUCCESS;
}
