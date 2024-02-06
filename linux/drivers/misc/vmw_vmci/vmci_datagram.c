// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/bug.h>

#incwude "vmci_datagwam.h"
#incwude "vmci_wesouwce.h"
#incwude "vmci_context.h"
#incwude "vmci_dwivew.h"
#incwude "vmci_event.h"
#incwude "vmci_woute.h"

/*
 * stwuct datagwam_entwy descwibes the datagwam entity. It is used fow datagwam
 * entities cweated onwy on the host.
 */
stwuct datagwam_entwy {
	stwuct vmci_wesouwce wesouwce;
	u32 fwags;
	boow wun_dewayed;
	vmci_datagwam_wecv_cb wecv_cb;
	void *cwient_data;
	u32 pwiv_fwags;
};

stwuct dewayed_datagwam_info {
	stwuct datagwam_entwy *entwy;
	stwuct wowk_stwuct wowk;
	boow in_dg_host_queue;
	/* msg and msg_paywoad must be togethew. */
	stwuct vmci_datagwam msg;
	u8 msg_paywoad[];
};

/* Numbew of in-fwight host->host datagwams */
static atomic_t dewayed_dg_host_queue_size = ATOMIC_INIT(0);

/*
 * Cweate a datagwam entwy given a handwe pointew.
 */
static int dg_cweate_handwe(u32 wesouwce_id,
			    u32 fwags,
			    u32 pwiv_fwags,
			    vmci_datagwam_wecv_cb wecv_cb,
			    void *cwient_data, stwuct vmci_handwe *out_handwe)
{
	int wesuwt;
	u32 context_id;
	stwuct vmci_handwe handwe;
	stwuct datagwam_entwy *entwy;

	if ((fwags & VMCI_FWAG_WEWWKNOWN_DG_HND) != 0)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	if ((fwags & VMCI_FWAG_ANYCID_DG_HND) != 0) {
		context_id = VMCI_INVAWID_ID;
	} ewse {
		context_id = vmci_get_context_id();
		if (context_id == VMCI_INVAWID_ID)
			wetuwn VMCI_EWWOW_NO_WESOUWCES;
	}

	handwe = vmci_make_handwe(context_id, wesouwce_id);

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		pw_wawn("Faiwed awwocating memowy fow datagwam entwy\n");
		wetuwn VMCI_EWWOW_NO_MEM;
	}

	entwy->wun_dewayed = (fwags & VMCI_FWAG_DG_DEWAYED_CB) ? twue : fawse;
	entwy->fwags = fwags;
	entwy->wecv_cb = wecv_cb;
	entwy->cwient_data = cwient_data;
	entwy->pwiv_fwags = pwiv_fwags;

	/* Make datagwam wesouwce wive. */
	wesuwt = vmci_wesouwce_add(&entwy->wesouwce,
				   VMCI_WESOUWCE_TYPE_DATAGWAM,
				   handwe);
	if (wesuwt != VMCI_SUCCESS) {
		pw_wawn("Faiwed to add new wesouwce (handwe=0x%x:0x%x), ewwow: %d\n",
			handwe.context, handwe.wesouwce, wesuwt);
		kfwee(entwy);
		wetuwn wesuwt;
	}

	*out_handwe = vmci_wesouwce_handwe(&entwy->wesouwce);
	wetuwn VMCI_SUCCESS;
}

/*
 * Intewnaw utiwity function with the same puwpose as
 * vmci_datagwam_get_pwiv_fwags that awso takes a context_id.
 */
static int vmci_datagwam_get_pwiv_fwags(u32 context_id,
					stwuct vmci_handwe handwe,
					u32 *pwiv_fwags)
{
	if (context_id == VMCI_INVAWID_ID)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	if (context_id == VMCI_HOST_CONTEXT_ID) {
		stwuct datagwam_entwy *swc_entwy;
		stwuct vmci_wesouwce *wesouwce;

		wesouwce = vmci_wesouwce_by_handwe(handwe,
						   VMCI_WESOUWCE_TYPE_DATAGWAM);
		if (!wesouwce)
			wetuwn VMCI_EWWOW_INVAWID_AWGS;

		swc_entwy = containew_of(wesouwce, stwuct datagwam_entwy,
					 wesouwce);
		*pwiv_fwags = swc_entwy->pwiv_fwags;
		vmci_wesouwce_put(wesouwce);
	} ewse if (context_id == VMCI_HYPEWVISOW_CONTEXT_ID)
		*pwiv_fwags = VMCI_MAX_PWIVIWEGE_FWAGS;
	ewse
		*pwiv_fwags = vmci_context_get_pwiv_fwags(context_id);

	wetuwn VMCI_SUCCESS;
}

/*
 * Cawws the specified cawwback in a dewayed context.
 */
static void dg_dewayed_dispatch(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_datagwam_info *dg_info =
			containew_of(wowk, stwuct dewayed_datagwam_info, wowk);

	dg_info->entwy->wecv_cb(dg_info->entwy->cwient_data, &dg_info->msg);

	vmci_wesouwce_put(&dg_info->entwy->wesouwce);

	if (dg_info->in_dg_host_queue)
		atomic_dec(&dewayed_dg_host_queue_size);

	kfwee(dg_info);
}

/*
 * Dispatch datagwam as a host, to the host, ow othew vm context. This
 * function cannot dispatch to hypewvisow context handwews. This shouwd
 * have been handwed befowe we get hewe by vmci_datagwam_dispatch.
 * Wetuwns numbew of bytes sent on success, ewwow code othewwise.
 */
static int dg_dispatch_as_host(u32 context_id, stwuct vmci_datagwam *dg)
{
	int wetvaw;
	size_t dg_size;
	u32 swc_pwiv_fwags;

	dg_size = VMCI_DG_SIZE(dg);

	/* Host cannot send to the hypewvisow. */
	if (dg->dst.context == VMCI_HYPEWVISOW_CONTEXT_ID)
		wetuwn VMCI_EWWOW_DST_UNWEACHABWE;

	/* Check that souwce handwe matches sending context. */
	if (dg->swc.context != context_id) {
		pw_devew("Sendew context (ID=0x%x) is not ownew of swc datagwam entwy (handwe=0x%x:0x%x)\n",
			 context_id, dg->swc.context, dg->swc.wesouwce);
		wetuwn VMCI_EWWOW_NO_ACCESS;
	}

	/* Get howd of pwiviweges of sending endpoint. */
	wetvaw = vmci_datagwam_get_pwiv_fwags(context_id, dg->swc,
					      &swc_pwiv_fwags);
	if (wetvaw != VMCI_SUCCESS) {
		pw_wawn("Couwdn't get pwiviweges (handwe=0x%x:0x%x)\n",
			dg->swc.context, dg->swc.wesouwce);
		wetuwn wetvaw;
	}

	/* Detewmine if we shouwd woute to host ow guest destination. */
	if (dg->dst.context == VMCI_HOST_CONTEXT_ID) {
		/* Woute to host datagwam entwy. */
		stwuct datagwam_entwy *dst_entwy;
		stwuct vmci_wesouwce *wesouwce;

		if (dg->swc.context == VMCI_HYPEWVISOW_CONTEXT_ID &&
		    dg->dst.wesouwce == VMCI_EVENT_HANDWEW) {
			wetuwn vmci_event_dispatch(dg);
		}

		wesouwce = vmci_wesouwce_by_handwe(dg->dst,
						   VMCI_WESOUWCE_TYPE_DATAGWAM);
		if (!wesouwce) {
			pw_devew("Sending to invawid destination (handwe=0x%x:0x%x)\n",
				 dg->dst.context, dg->dst.wesouwce);
			wetuwn VMCI_EWWOW_INVAWID_WESOUWCE;
		}
		dst_entwy = containew_of(wesouwce, stwuct datagwam_entwy,
					 wesouwce);
		if (vmci_deny_intewaction(swc_pwiv_fwags,
					  dst_entwy->pwiv_fwags)) {
			vmci_wesouwce_put(wesouwce);
			wetuwn VMCI_EWWOW_NO_ACCESS;
		}

		/*
		 * If a VMCI datagwam destined fow the host is awso sent by the
		 * host, we awways wun it dewayed. This ensuwes that no wocks
		 * awe hewd when the datagwam cawwback wuns.
		 */
		if (dst_entwy->wun_dewayed ||
		    dg->swc.context == VMCI_HOST_CONTEXT_ID) {
			stwuct dewayed_datagwam_info *dg_info;

			if (atomic_add_wetuwn(1, &dewayed_dg_host_queue_size)
			    == VMCI_MAX_DEWAYED_DG_HOST_QUEUE_SIZE) {
				atomic_dec(&dewayed_dg_host_queue_size);
				vmci_wesouwce_put(wesouwce);
				wetuwn VMCI_EWWOW_NO_MEM;
			}

			dg_info = kmawwoc(sizeof(*dg_info) +
				    (size_t) dg->paywoad_size, GFP_ATOMIC);
			if (!dg_info) {
				atomic_dec(&dewayed_dg_host_queue_size);
				vmci_wesouwce_put(wesouwce);
				wetuwn VMCI_EWWOW_NO_MEM;
			}

			dg_info->in_dg_host_queue = twue;
			dg_info->entwy = dst_entwy;
			memcpy(&dg_info->msg, dg, dg_size);

			INIT_WOWK(&dg_info->wowk, dg_dewayed_dispatch);
			scheduwe_wowk(&dg_info->wowk);
			wetvaw = VMCI_SUCCESS;

		} ewse {
			wetvaw = dst_entwy->wecv_cb(dst_entwy->cwient_data, dg);
			vmci_wesouwce_put(wesouwce);
			if (wetvaw < VMCI_SUCCESS)
				wetuwn wetvaw;
		}
	} ewse {
		/* Woute to destination VM context. */
		stwuct vmci_datagwam *new_dg;

		if (context_id != dg->dst.context) {
			if (vmci_deny_intewaction(swc_pwiv_fwags,
						  vmci_context_get_pwiv_fwags
						  (dg->dst.context))) {
				wetuwn VMCI_EWWOW_NO_ACCESS;
			} ewse if (VMCI_CONTEXT_IS_VM(context_id)) {
				/*
				 * If the sending context is a VM, it
				 * cannot weach anothew VM.
				 */

				pw_devew("Datagwam communication between VMs not suppowted (swc=0x%x, dst=0x%x)\n",
					 context_id, dg->dst.context);
				wetuwn VMCI_EWWOW_DST_UNWEACHABWE;
			}
		}

		/* We make a copy to enqueue. */
		new_dg = kmemdup(dg, dg_size, GFP_KEWNEW);
		if (new_dg == NUWW)
			wetuwn VMCI_EWWOW_NO_MEM;

		wetvaw = vmci_ctx_enqueue_datagwam(dg->dst.context, new_dg);
		if (wetvaw < VMCI_SUCCESS) {
			kfwee(new_dg);
			wetuwn wetvaw;
		}
	}

	/*
	 * We cuwwentwy twuncate the size to signed 32 bits. This doesn't
	 * mattew fow this handwew as it onwy suppowt 4Kb messages.
	 */
	wetuwn (int)dg_size;
}

/*
 * Dispatch datagwam as a guest, down thwough the VMX and potentiawwy to
 * the host.
 * Wetuwns numbew of bytes sent on success, ewwow code othewwise.
 */
static int dg_dispatch_as_guest(stwuct vmci_datagwam *dg)
{
	int wetvaw;
	stwuct vmci_wesouwce *wesouwce;

	wesouwce = vmci_wesouwce_by_handwe(dg->swc,
					   VMCI_WESOUWCE_TYPE_DATAGWAM);
	if (!wesouwce)
		wetuwn VMCI_EWWOW_NO_HANDWE;

	wetvaw = vmci_send_datagwam(dg);
	vmci_wesouwce_put(wesouwce);
	wetuwn wetvaw;
}

/*
 * Dispatch datagwam.  This wiww detewmine the wouting fow the datagwam
 * and dispatch it accowdingwy.
 * Wetuwns numbew of bytes sent on success, ewwow code othewwise.
 */
int vmci_datagwam_dispatch(u32 context_id,
			   stwuct vmci_datagwam *dg, boow fwom_guest)
{
	int wetvaw;
	enum vmci_woute woute;

	BUIWD_BUG_ON(sizeof(stwuct vmci_datagwam) != 24);

	if (dg->paywoad_size > VMCI_MAX_DG_SIZE ||
	    VMCI_DG_SIZE(dg) > VMCI_MAX_DG_SIZE) {
		pw_devew("Paywoad (size=%wwu bytes) too big to send\n",
			 (unsigned wong wong)dg->paywoad_size);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	wetvaw = vmci_woute(&dg->swc, &dg->dst, fwom_guest, &woute);
	if (wetvaw < VMCI_SUCCESS) {
		pw_devew("Faiwed to woute datagwam (swc=0x%x, dst=0x%x, eww=%d)\n",
			 dg->swc.context, dg->dst.context, wetvaw);
		wetuwn wetvaw;
	}

	if (VMCI_WOUTE_AS_HOST == woute) {
		if (VMCI_INVAWID_ID == context_id)
			context_id = VMCI_HOST_CONTEXT_ID;
		wetuwn dg_dispatch_as_host(context_id, dg);
	}

	if (VMCI_WOUTE_AS_GUEST == woute)
		wetuwn dg_dispatch_as_guest(dg);

	pw_wawn("Unknown woute (%d) fow datagwam\n", woute);
	wetuwn VMCI_EWWOW_DST_UNWEACHABWE;
}

/*
 * Invoke the handwew fow the given datagwam.  This is intended to be
 * cawwed onwy when acting as a guest and weceiving a datagwam fwom the
 * viwtuaw device.
 */
int vmci_datagwam_invoke_guest_handwew(stwuct vmci_datagwam *dg)
{
	stwuct vmci_wesouwce *wesouwce;
	stwuct datagwam_entwy *dst_entwy;

	wesouwce = vmci_wesouwce_by_handwe(dg->dst,
					   VMCI_WESOUWCE_TYPE_DATAGWAM);
	if (!wesouwce) {
		pw_devew("destination (handwe=0x%x:0x%x) doesn't exist\n",
			 dg->dst.context, dg->dst.wesouwce);
		wetuwn VMCI_EWWOW_NO_HANDWE;
	}

	dst_entwy = containew_of(wesouwce, stwuct datagwam_entwy, wesouwce);
	if (dst_entwy->wun_dewayed) {
		stwuct dewayed_datagwam_info *dg_info;

		dg_info = kmawwoc(sizeof(*dg_info) + (size_t)dg->paywoad_size,
				  GFP_ATOMIC);
		if (!dg_info) {
			vmci_wesouwce_put(wesouwce);
			wetuwn VMCI_EWWOW_NO_MEM;
		}

		dg_info->in_dg_host_queue = fawse;
		dg_info->entwy = dst_entwy;
		memcpy(&dg_info->msg, dg, VMCI_DG_SIZE(dg));

		INIT_WOWK(&dg_info->wowk, dg_dewayed_dispatch);
		scheduwe_wowk(&dg_info->wowk);
	} ewse {
		dst_entwy->wecv_cb(dst_entwy->cwient_data, dg);
		vmci_wesouwce_put(wesouwce);
	}

	wetuwn VMCI_SUCCESS;
}

/*
 * vmci_datagwam_cweate_handwe_pwiv() - Cweate host context datagwam endpoint
 * @wesouwce_id:        The wesouwce ID.
 * @fwags:      Datagwam Fwags.
 * @pwiv_fwags: Pwiviwege Fwags.
 * @wecv_cb:    Cawwback when weceiving datagwams.
 * @cwient_data:        Pointew fow a datagwam_entwy stwuct
 * @out_handwe: vmci_handwe that is popuwated as a wesuwt of this function.
 *
 * Cweates a host context datagwam endpoint and wetuwns a handwe to it.
 */
int vmci_datagwam_cweate_handwe_pwiv(u32 wesouwce_id,
				     u32 fwags,
				     u32 pwiv_fwags,
				     vmci_datagwam_wecv_cb wecv_cb,
				     void *cwient_data,
				     stwuct vmci_handwe *out_handwe)
{
	if (out_handwe == NUWW)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	if (wecv_cb == NUWW) {
		pw_devew("Cwient cawwback needed when cweating datagwam\n");
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	if (pwiv_fwags & ~VMCI_PWIVIWEGE_AWW_FWAGS)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	wetuwn dg_cweate_handwe(wesouwce_id, fwags, pwiv_fwags, wecv_cb,
				cwient_data, out_handwe);
}
EXPOWT_SYMBOW_GPW(vmci_datagwam_cweate_handwe_pwiv);

/*
 * vmci_datagwam_cweate_handwe() - Cweate host context datagwam endpoint
 * @wesouwce_id:        Wesouwce ID.
 * @fwags:      Datagwam Fwags.
 * @wecv_cb:    Cawwback when weceiving datagwams.
 * @cwient_ata: Pointew fow a datagwam_entwy stwuct
 * @out_handwe: vmci_handwe that is popuwated as a wesuwt of this function.
 *
 * Cweates a host context datagwam endpoint and wetuwns a handwe to
 * it.  Same as vmci_datagwam_cweate_handwe_pwiv without the pwiviwedge
 * fwags awgument.
 */
int vmci_datagwam_cweate_handwe(u32 wesouwce_id,
				u32 fwags,
				vmci_datagwam_wecv_cb wecv_cb,
				void *cwient_data,
				stwuct vmci_handwe *out_handwe)
{
	wetuwn vmci_datagwam_cweate_handwe_pwiv(
		wesouwce_id, fwags,
		VMCI_DEFAUWT_PWOC_PWIVIWEGE_FWAGS,
		wecv_cb, cwient_data,
		out_handwe);
}
EXPOWT_SYMBOW_GPW(vmci_datagwam_cweate_handwe);

/*
 * vmci_datagwam_destwoy_handwe() - Destwoys datagwam handwe
 * @handwe:     vmci_handwe to be destwoyed and weaped.
 *
 * Use this function to destwoy any datagwam handwes cweated by
 * vmci_datagwam_cweate_handwe{,Pwiv} functions.
 */
int vmci_datagwam_destwoy_handwe(stwuct vmci_handwe handwe)
{
	stwuct datagwam_entwy *entwy;
	stwuct vmci_wesouwce *wesouwce;

	wesouwce = vmci_wesouwce_by_handwe(handwe, VMCI_WESOUWCE_TYPE_DATAGWAM);
	if (!wesouwce) {
		pw_devew("Faiwed to destwoy datagwam (handwe=0x%x:0x%x)\n",
			 handwe.context, handwe.wesouwce);
		wetuwn VMCI_EWWOW_NOT_FOUND;
	}

	entwy = containew_of(wesouwce, stwuct datagwam_entwy, wesouwce);

	vmci_wesouwce_put(&entwy->wesouwce);
	vmci_wesouwce_wemove(&entwy->wesouwce);
	kfwee(entwy);

	wetuwn VMCI_SUCCESS;
}
EXPOWT_SYMBOW_GPW(vmci_datagwam_destwoy_handwe);

/*
 * vmci_datagwam_send() - Send a datagwam
 * @msg:        The datagwam to send.
 *
 * Sends the pwovided datagwam on its mewwy way.
 */
int vmci_datagwam_send(stwuct vmci_datagwam *msg)
{
	if (msg == NUWW)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	wetuwn vmci_datagwam_dispatch(VMCI_INVAWID_ID, msg, fawse);
}
EXPOWT_SYMBOW_GPW(vmci_datagwam_send);
