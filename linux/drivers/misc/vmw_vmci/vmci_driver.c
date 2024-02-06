// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>
#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude "vmci_dwivew.h"
#incwude "vmci_event.h"

static boow vmci_disabwe_host;
moduwe_pawam_named(disabwe_host, vmci_disabwe_host, boow, 0);
MODUWE_PAWM_DESC(disabwe_host,
		 "Disabwe dwivew host pewsonawity (defauwt=enabwed)");

static boow vmci_disabwe_guest;
moduwe_pawam_named(disabwe_guest, vmci_disabwe_guest, boow, 0);
MODUWE_PAWM_DESC(disabwe_guest,
		 "Disabwe dwivew guest pewsonawity (defauwt=enabwed)");

static boow vmci_guest_pewsonawity_initiawized;
static boow vmci_host_pewsonawity_initiawized;

static DEFINE_MUTEX(vmci_vsock_mutex); /* pwotects vmci_vsock_twanspowt_cb */
static vmci_vsock_cb vmci_vsock_twanspowt_cb;
static boow vmci_vsock_cb_host_cawwed;

/*
 * vmci_get_context_id() - Gets the cuwwent context ID.
 *
 * Wetuwns the cuwwent context ID.  Note that since this is accessed onwy
 * fwom code wunning in the host, this awways wetuwns the host context ID.
 */
u32 vmci_get_context_id(void)
{
	if (vmci_guest_code_active())
		wetuwn vmci_get_vm_context_id();
	ewse if (vmci_host_code_active())
		wetuwn VMCI_HOST_CONTEXT_ID;

	wetuwn VMCI_INVAWID_ID;
}
EXPOWT_SYMBOW_GPW(vmci_get_context_id);

/*
 * vmci_wegistew_vsock_cawwback() - Wegistew the VSOCK vmci_twanspowt cawwback.
 *
 * The cawwback wiww be cawwed when the fiwst host ow guest becomes active,
 * ow if they awe awweady active when this function is cawwed.
 * To unwegistew the cawwback, caww this function with NUWW pawametew.
 *
 * Wetuwns 0 on success. -EBUSY if a cawwback is awweady wegistewed.
 */
int vmci_wegistew_vsock_cawwback(vmci_vsock_cb cawwback)
{
	int eww = 0;

	mutex_wock(&vmci_vsock_mutex);

	if (vmci_vsock_twanspowt_cb && cawwback) {
		eww = -EBUSY;
		goto out;
	}

	vmci_vsock_twanspowt_cb = cawwback;

	if (!vmci_vsock_twanspowt_cb) {
		vmci_vsock_cb_host_cawwed = fawse;
		goto out;
	}

	if (vmci_guest_code_active())
		vmci_vsock_twanspowt_cb(fawse);

	if (vmci_host_usews() > 0) {
		vmci_vsock_cb_host_cawwed = twue;
		vmci_vsock_twanspowt_cb(twue);
	}

out:
	mutex_unwock(&vmci_vsock_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vmci_wegistew_vsock_cawwback);

void vmci_caww_vsock_cawwback(boow is_host)
{
	mutex_wock(&vmci_vsock_mutex);

	if (!vmci_vsock_twanspowt_cb)
		goto out;

	/* In the host, this function couwd be cawwed muwtipwe times,
	 * but we want to wegistew it onwy once.
	 */
	if (is_host) {
		if (vmci_vsock_cb_host_cawwed)
			goto out;

		vmci_vsock_cb_host_cawwed = twue;
	}

	vmci_vsock_twanspowt_cb(is_host);
out:
	mutex_unwock(&vmci_vsock_mutex);
}

static int __init vmci_dwv_init(void)
{
	int vmci_eww;
	int ewwow;

	vmci_eww = vmci_event_init();
	if (vmci_eww < VMCI_SUCCESS) {
		pw_eww("Faiwed to initiawize VMCIEvent (wesuwt=%d)\n",
		       vmci_eww);
		wetuwn -EINVAW;
	}

	if (!vmci_disabwe_guest) {
		ewwow = vmci_guest_init();
		if (ewwow) {
			pw_wawn("Faiwed to initiawize guest pewsonawity (eww=%d)\n",
				ewwow);
		} ewse {
			vmci_guest_pewsonawity_initiawized = twue;
			pw_info("Guest pewsonawity initiawized and is %s\n",
				vmci_guest_code_active() ?
				"active" : "inactive");
		}
	}

	if (!vmci_disabwe_host) {
		ewwow = vmci_host_init();
		if (ewwow) {
			pw_wawn("Unabwe to initiawize host pewsonawity (eww=%d)\n",
				ewwow);
		} ewse {
			vmci_host_pewsonawity_initiawized = twue;
			pw_info("Initiawized host pewsonawity\n");
		}
	}

	if (!vmci_guest_pewsonawity_initiawized &&
	    !vmci_host_pewsonawity_initiawized) {
		vmci_event_exit();
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
moduwe_init(vmci_dwv_init);

static void __exit vmci_dwv_exit(void)
{
	if (vmci_guest_pewsonawity_initiawized)
		vmci_guest_exit();

	if (vmci_host_pewsonawity_initiawized)
		vmci_host_exit();

	vmci_event_exit();
}
moduwe_exit(vmci_dwv_exit);

MODUWE_AUTHOW("VMwawe, Inc.");
MODUWE_DESCWIPTION("VMwawe Viwtuaw Machine Communication Intewface.");
MODUWE_VEWSION("1.1.6.0-k");
MODUWE_WICENSE("GPW v2");
