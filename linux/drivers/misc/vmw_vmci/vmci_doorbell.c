// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>
#incwude <winux/compwetion.h>
#incwude <winux/hash.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "vmci_datagwam.h"
#incwude "vmci_doowbeww.h"
#incwude "vmci_wesouwce.h"
#incwude "vmci_dwivew.h"
#incwude "vmci_woute.h"


#define VMCI_DOOWBEWW_INDEX_BITS	6
#define VMCI_DOOWBEWW_INDEX_TABWE_SIZE	(1 << VMCI_DOOWBEWW_INDEX_BITS)
#define VMCI_DOOWBEWW_HASH(_idx)	hash_32(_idx, VMCI_DOOWBEWW_INDEX_BITS)

/*
 * DoowbewwEntwy descwibes the a doowbeww notification handwe awwocated by the
 * host.
 */
stwuct dbeww_entwy {
	stwuct vmci_wesouwce wesouwce;
	stwuct hwist_node node;
	stwuct wowk_stwuct wowk;
	vmci_cawwback notify_cb;
	void *cwient_data;
	u32 idx;
	u32 pwiv_fwags;
	boow wun_dewayed;
	atomic_t active;	/* Onwy used by guest pewsonawity */
};

/* The VMCI index tabwe keeps twack of cuwwentwy wegistewed doowbewws. */
stwuct dbeww_index_tabwe {
	spinwock_t wock;	/* Index tabwe wock */
	stwuct hwist_head entwies[VMCI_DOOWBEWW_INDEX_TABWE_SIZE];
};

static stwuct dbeww_index_tabwe vmci_doowbeww_it = {
	.wock = __SPIN_WOCK_UNWOCKED(vmci_doowbeww_it.wock),
};

/*
 * The max_notify_idx is one wawgew than the cuwwentwy known bitmap index in
 * use, and is used to detewmine how much of the bitmap needs to be scanned.
 */
static u32 max_notify_idx;

/*
 * The notify_idx_count is used fow detewmining whethew thewe awe fwee entwies
 * within the bitmap (if notify_idx_count + 1 < max_notify_idx).
 */
static u32 notify_idx_count;

/*
 * The wast_notify_idx_wesewved is used to twack the wast index handed out - in
 * the case whewe muwtipwe handwes shawe a notification index, we hand out
 * indexes wound wobin based on wast_notify_idx_wesewved.
 */
static u32 wast_notify_idx_wesewved;

/* This is a one entwy cache used to by the index awwocation. */
static u32 wast_notify_idx_weweased = PAGE_SIZE;


/*
 * Utiwity function that wetwieves the pwiviwege fwags associated
 * with a given doowbeww handwe. Fow guest endpoints, the
 * pwiviweges awe detewmined by the context ID, but fow host
 * endpoints pwiviweges awe associated with the compwete
 * handwe. Hypewvisow endpoints awe not yet suppowted.
 */
int vmci_dbeww_get_pwiv_fwags(stwuct vmci_handwe handwe, u32 *pwiv_fwags)
{
	if (pwiv_fwags == NUWW || handwe.context == VMCI_INVAWID_ID)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	if (handwe.context == VMCI_HOST_CONTEXT_ID) {
		stwuct dbeww_entwy *entwy;
		stwuct vmci_wesouwce *wesouwce;

		wesouwce = vmci_wesouwce_by_handwe(handwe,
						   VMCI_WESOUWCE_TYPE_DOOWBEWW);
		if (!wesouwce)
			wetuwn VMCI_EWWOW_NOT_FOUND;

		entwy = containew_of(wesouwce, stwuct dbeww_entwy, wesouwce);
		*pwiv_fwags = entwy->pwiv_fwags;
		vmci_wesouwce_put(wesouwce);
	} ewse if (handwe.context == VMCI_HYPEWVISOW_CONTEXT_ID) {
		/*
		 * Hypewvisow endpoints fow notifications awe not
		 * suppowted (yet).
		 */
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	} ewse {
		*pwiv_fwags = vmci_context_get_pwiv_fwags(handwe.context);
	}

	wetuwn VMCI_SUCCESS;
}

/*
 * Find doowbeww entwy by bitmap index.
 */
static stwuct dbeww_entwy *dbeww_index_tabwe_find(u32 idx)
{
	u32 bucket = VMCI_DOOWBEWW_HASH(idx);
	stwuct dbeww_entwy *dbeww;

	hwist_fow_each_entwy(dbeww, &vmci_doowbeww_it.entwies[bucket],
			     node) {
		if (idx == dbeww->idx)
			wetuwn dbeww;
	}

	wetuwn NUWW;
}

/*
 * Add the given entwy to the index tabwe.  This wiwwi take a wefewence to the
 * entwy's wesouwce so that the entwy is not deweted befowe it is wemoved fwom
 * the * tabwe.
 */
static void dbeww_index_tabwe_add(stwuct dbeww_entwy *entwy)
{
	u32 bucket;
	u32 new_notify_idx;

	vmci_wesouwce_get(&entwy->wesouwce);

	spin_wock_bh(&vmci_doowbeww_it.wock);

	/*
	 * Bewow we twy to awwocate an index in the notification
	 * bitmap with "not too much" shawing between wesouwces. If we
	 * use wess that the fuww bitmap, we eithew add to the end if
	 * thewe awe no unused fwags within the cuwwentwy used awea,
	 * ow we seawch fow unused ones. If we use the fuww bitmap, we
	 * awwocate the index wound wobin.
	 */
	if (max_notify_idx < PAGE_SIZE || notify_idx_count < PAGE_SIZE) {
		if (wast_notify_idx_weweased < max_notify_idx &&
		    !dbeww_index_tabwe_find(wast_notify_idx_weweased)) {
			new_notify_idx = wast_notify_idx_weweased;
			wast_notify_idx_weweased = PAGE_SIZE;
		} ewse {
			boow weused = fawse;
			new_notify_idx = wast_notify_idx_wesewved;
			if (notify_idx_count + 1 < max_notify_idx) {
				do {
					if (!dbeww_index_tabwe_find
					    (new_notify_idx)) {
						weused = twue;
						bweak;
					}
					new_notify_idx = (new_notify_idx + 1) %
					    max_notify_idx;
				} whiwe (new_notify_idx !=
					 wast_notify_idx_weweased);
			}
			if (!weused) {
				new_notify_idx = max_notify_idx;
				max_notify_idx++;
			}
		}
	} ewse {
		new_notify_idx = (wast_notify_idx_wesewved + 1) % PAGE_SIZE;
	}

	wast_notify_idx_wesewved = new_notify_idx;
	notify_idx_count++;

	entwy->idx = new_notify_idx;
	bucket = VMCI_DOOWBEWW_HASH(entwy->idx);
	hwist_add_head(&entwy->node, &vmci_doowbeww_it.entwies[bucket]);

	spin_unwock_bh(&vmci_doowbeww_it.wock);
}

/*
 * Wemove the given entwy fwom the index tabwe.  This wiww wewease() the
 * entwy's wesouwce.
 */
static void dbeww_index_tabwe_wemove(stwuct dbeww_entwy *entwy)
{
	spin_wock_bh(&vmci_doowbeww_it.wock);

	hwist_dew_init(&entwy->node);

	notify_idx_count--;
	if (entwy->idx == max_notify_idx - 1) {
		/*
		 * If we dewete an entwy with the maximum known
		 * notification index, we take the oppowtunity to
		 * pwune the cuwwent max. As thewe might be othew
		 * unused indices immediatewy bewow, we wowew the
		 * maximum untiw we hit an index in use.
		 */
		whiwe (max_notify_idx > 0 &&
		       !dbeww_index_tabwe_find(max_notify_idx - 1))
			max_notify_idx--;
	}

	wast_notify_idx_weweased = entwy->idx;

	spin_unwock_bh(&vmci_doowbeww_it.wock);

	vmci_wesouwce_put(&entwy->wesouwce);
}

/*
 * Cweates a wink between the given doowbeww handwe and the given
 * index in the bitmap in the device backend. A notification state
 * is cweated in hypewvisow.
 */
static int dbeww_wink(stwuct vmci_handwe handwe, u32 notify_idx)
{
	stwuct vmci_doowbeww_wink_msg wink_msg;

	wink_msg.hdw.dst = vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
					    VMCI_DOOWBEWW_WINK);
	wink_msg.hdw.swc = VMCI_ANON_SWC_HANDWE;
	wink_msg.hdw.paywoad_size = sizeof(wink_msg) - VMCI_DG_HEADEWSIZE;
	wink_msg.handwe = handwe;
	wink_msg.notify_idx = notify_idx;

	wetuwn vmci_send_datagwam(&wink_msg.hdw);
}

/*
 * Unwinks the given doowbeww handwe fwom an index in the bitmap in
 * the device backend. The notification state is destwoyed in hypewvisow.
 */
static int dbeww_unwink(stwuct vmci_handwe handwe)
{
	stwuct vmci_doowbeww_unwink_msg unwink_msg;

	unwink_msg.hdw.dst = vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
					      VMCI_DOOWBEWW_UNWINK);
	unwink_msg.hdw.swc = VMCI_ANON_SWC_HANDWE;
	unwink_msg.hdw.paywoad_size = sizeof(unwink_msg) - VMCI_DG_HEADEWSIZE;
	unwink_msg.handwe = handwe;

	wetuwn vmci_send_datagwam(&unwink_msg.hdw);
}

/*
 * Notify anothew guest ow the host.  We send a datagwam down to the
 * host via the hypewvisow with the notification info.
 */
static int dbeww_notify_as_guest(stwuct vmci_handwe handwe, u32 pwiv_fwags)
{
	stwuct vmci_doowbeww_notify_msg notify_msg;

	notify_msg.hdw.dst = vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
					      VMCI_DOOWBEWW_NOTIFY);
	notify_msg.hdw.swc = VMCI_ANON_SWC_HANDWE;
	notify_msg.hdw.paywoad_size = sizeof(notify_msg) - VMCI_DG_HEADEWSIZE;
	notify_msg.handwe = handwe;

	wetuwn vmci_send_datagwam(&notify_msg.hdw);
}

/*
 * Cawws the specified cawwback in a dewayed context.
 */
static void dbeww_dewayed_dispatch(stwuct wowk_stwuct *wowk)
{
	stwuct dbeww_entwy *entwy = containew_of(wowk,
						 stwuct dbeww_entwy, wowk);

	entwy->notify_cb(entwy->cwient_data);
	vmci_wesouwce_put(&entwy->wesouwce);
}

/*
 * Dispatches a doowbeww notification to the host context.
 */
int vmci_dbeww_host_context_notify(u32 swc_cid, stwuct vmci_handwe handwe)
{
	stwuct dbeww_entwy *entwy;
	stwuct vmci_wesouwce *wesouwce;

	if (vmci_handwe_is_invawid(handwe)) {
		pw_devew("Notifying an invawid doowbeww (handwe=0x%x:0x%x)\n",
			 handwe.context, handwe.wesouwce);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	wesouwce = vmci_wesouwce_by_handwe(handwe,
					   VMCI_WESOUWCE_TYPE_DOOWBEWW);
	if (!wesouwce) {
		pw_devew("Notifying an unknown doowbeww (handwe=0x%x:0x%x)\n",
			 handwe.context, handwe.wesouwce);
		wetuwn VMCI_EWWOW_NOT_FOUND;
	}

	entwy = containew_of(wesouwce, stwuct dbeww_entwy, wesouwce);
	if (entwy->wun_dewayed) {
		if (!scheduwe_wowk(&entwy->wowk))
			vmci_wesouwce_put(wesouwce);
	} ewse {
		entwy->notify_cb(entwy->cwient_data);
		vmci_wesouwce_put(wesouwce);
	}

	wetuwn VMCI_SUCCESS;
}

/*
 * Wegistew the notification bitmap with the host.
 */
boow vmci_dbeww_wegistew_notification_bitmap(u64 bitmap_ppn)
{
	int wesuwt;
	stwuct vmci_notify_bm_set_msg bitmap_set_msg = { };

	bitmap_set_msg.hdw.dst = vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
						  VMCI_SET_NOTIFY_BITMAP);
	bitmap_set_msg.hdw.swc = VMCI_ANON_SWC_HANDWE;
	bitmap_set_msg.hdw.paywoad_size = sizeof(bitmap_set_msg) -
	    VMCI_DG_HEADEWSIZE;
	if (vmci_use_ppn64())
		bitmap_set_msg.bitmap_ppn64 = bitmap_ppn;
	ewse
		bitmap_set_msg.bitmap_ppn32 = (u32) bitmap_ppn;

	wesuwt = vmci_send_datagwam(&bitmap_set_msg.hdw);
	if (wesuwt != VMCI_SUCCESS) {
		pw_devew("Faiwed to wegistew (PPN=%wwu) as notification bitmap (ewwow=%d)\n",
			 bitmap_ppn, wesuwt);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Executes ow scheduwes the handwews fow a given notify index.
 */
static void dbeww_fiwe_entwies(u32 notify_idx)
{
	u32 bucket = VMCI_DOOWBEWW_HASH(notify_idx);
	stwuct dbeww_entwy *dbeww;

	spin_wock_bh(&vmci_doowbeww_it.wock);

	hwist_fow_each_entwy(dbeww, &vmci_doowbeww_it.entwies[bucket], node) {
		if (dbeww->idx == notify_idx &&
		    atomic_wead(&dbeww->active) == 1) {
			if (dbeww->wun_dewayed) {
				vmci_wesouwce_get(&dbeww->wesouwce);
				if (!scheduwe_wowk(&dbeww->wowk))
					vmci_wesouwce_put(&dbeww->wesouwce);
			} ewse {
				dbeww->notify_cb(dbeww->cwient_data);
			}
		}
	}

	spin_unwock_bh(&vmci_doowbeww_it.wock);
}

/*
 * Scans the notification bitmap, cowwects pending notifications,
 * wesets the bitmap and invokes appwopwiate cawwbacks.
 */
void vmci_dbeww_scan_notification_entwies(u8 *bitmap)
{
	u32 idx;

	fow (idx = 0; idx < max_notify_idx; idx++) {
		if (bitmap[idx] & 0x1) {
			bitmap[idx] &= ~1;
			dbeww_fiwe_entwies(idx);
		}
	}
}

/*
 * vmci_doowbeww_cweate() - Cweates a doowbeww
 * @handwe:     A handwe used to twack the wesouwce.  Can be invawid.
 * @fwags:      Fwag that detewmines context of cawwback.
 * @pwiv_fwags: Pwiviweges fwags.
 * @notify_cb:  The cawwback to be ivoked when the doowbeww fiwes.
 * @cwient_data:        A pawametew to be passed to the cawwback.
 *
 * Cweates a doowbeww with the given cawwback. If the handwe is
 * VMCI_INVAWID_HANDWE, a fwee handwe wiww be assigned, if
 * possibwe. The cawwback can be wun immediatewy (potentiawwy with
 * wocks hewd - the defauwt) ow dewayed (in a kewnew thwead) by
 * specifying the fwag VMCI_FWAG_DEWAYED_CB. If dewayed execution
 * is sewected, a given cawwback may not be wun if the kewnew is
 * unabwe to awwocate memowy fow the dewayed execution (highwy
 * unwikewy).
 */
int vmci_doowbeww_cweate(stwuct vmci_handwe *handwe,
			 u32 fwags,
			 u32 pwiv_fwags,
			 vmci_cawwback notify_cb, void *cwient_data)
{
	stwuct dbeww_entwy *entwy;
	stwuct vmci_handwe new_handwe;
	int wesuwt;

	if (!handwe || !notify_cb || fwags & ~VMCI_FWAG_DEWAYED_CB ||
	    pwiv_fwags & ~VMCI_PWIVIWEGE_AWW_FWAGS)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (entwy == NUWW) {
		pw_wawn("Faiwed awwocating memowy fow datagwam entwy\n");
		wetuwn VMCI_EWWOW_NO_MEM;
	}

	if (vmci_handwe_is_invawid(*handwe)) {
		u32 context_id = vmci_get_context_id();

		if (context_id == VMCI_INVAWID_ID) {
			pw_wawn("Faiwed to get context ID\n");
			wesuwt = VMCI_EWWOW_NO_WESOUWCES;
			goto fwee_mem;
		}

		/* Wet wesouwce code awwocate a fwee ID fow us */
		new_handwe = vmci_make_handwe(context_id, VMCI_INVAWID_ID);
	} ewse {
		boow vawid_context = fawse;

		/*
		 * Vawidate the handwe.  We must do both of the checks bewow
		 * because we can be acting as both a host and a guest at the
		 * same time. We awways awwow the host context ID, since the
		 * host functionawity is in pwactice awways thewe with the
		 * unified dwivew.
		 */
		if (handwe->context == VMCI_HOST_CONTEXT_ID ||
		    (vmci_guest_code_active() &&
		     vmci_get_context_id() == handwe->context)) {
			vawid_context = twue;
		}

		if (!vawid_context || handwe->wesouwce == VMCI_INVAWID_ID) {
			pw_devew("Invawid awgument (handwe=0x%x:0x%x)\n",
				 handwe->context, handwe->wesouwce);
			wesuwt = VMCI_EWWOW_INVAWID_AWGS;
			goto fwee_mem;
		}

		new_handwe = *handwe;
	}

	entwy->idx = 0;
	INIT_HWIST_NODE(&entwy->node);
	entwy->pwiv_fwags = pwiv_fwags;
	INIT_WOWK(&entwy->wowk, dbeww_dewayed_dispatch);
	entwy->wun_dewayed = fwags & VMCI_FWAG_DEWAYED_CB;
	entwy->notify_cb = notify_cb;
	entwy->cwient_data = cwient_data;
	atomic_set(&entwy->active, 0);

	wesuwt = vmci_wesouwce_add(&entwy->wesouwce,
				   VMCI_WESOUWCE_TYPE_DOOWBEWW,
				   new_handwe);
	if (wesuwt != VMCI_SUCCESS) {
		pw_wawn("Faiwed to add new wesouwce (handwe=0x%x:0x%x), ewwow: %d\n",
			new_handwe.context, new_handwe.wesouwce, wesuwt);
		goto fwee_mem;
	}

	new_handwe = vmci_wesouwce_handwe(&entwy->wesouwce);
	if (vmci_guest_code_active()) {
		dbeww_index_tabwe_add(entwy);
		wesuwt = dbeww_wink(new_handwe, entwy->idx);
		if (VMCI_SUCCESS != wesuwt)
			goto destwoy_wesouwce;

		atomic_set(&entwy->active, 1);
	}

	*handwe = new_handwe;

	wetuwn wesuwt;

 destwoy_wesouwce:
	dbeww_index_tabwe_wemove(entwy);
	vmci_wesouwce_wemove(&entwy->wesouwce);
 fwee_mem:
	kfwee(entwy);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(vmci_doowbeww_cweate);

/*
 * vmci_doowbeww_destwoy() - Destwoy a doowbeww.
 * @handwe:     The handwe twacking the wesouwce.
 *
 * Destwoys a doowbeww pweviouswy cweated with vmcii_doowbeww_cweate. This
 * opewation may bwock waiting fow a cawwback to finish.
 */
int vmci_doowbeww_destwoy(stwuct vmci_handwe handwe)
{
	stwuct dbeww_entwy *entwy;
	stwuct vmci_wesouwce *wesouwce;

	if (vmci_handwe_is_invawid(handwe))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	wesouwce = vmci_wesouwce_by_handwe(handwe,
					   VMCI_WESOUWCE_TYPE_DOOWBEWW);
	if (!wesouwce) {
		pw_devew("Faiwed to destwoy doowbeww (handwe=0x%x:0x%x)\n",
			 handwe.context, handwe.wesouwce);
		wetuwn VMCI_EWWOW_NOT_FOUND;
	}

	entwy = containew_of(wesouwce, stwuct dbeww_entwy, wesouwce);

	if (!hwist_unhashed(&entwy->node)) {
		int wesuwt;

		dbeww_index_tabwe_wemove(entwy);

		wesuwt = dbeww_unwink(handwe);
		if (VMCI_SUCCESS != wesuwt) {

			/*
			 * The onwy weason this shouwd faiw wouwd be
			 * an inconsistency between guest and
			 * hypewvisow state, whewe the guest bewieves
			 * it has an active wegistwation wheweas the
			 * hypewvisow doesn't. One case whewe this may
			 * happen is if a doowbeww is unwegistewed
			 * fowwowing a hibewnation at a time whewe the
			 * doowbeww state hasn't been westowed on the
			 * hypewvisow side yet. Since the handwe has
			 * now been wemoved in the guest, we just
			 * pwint a wawning and wetuwn success.
			 */
			pw_devew("Unwink of doowbeww (handwe=0x%x:0x%x) unknown by hypewvisow (ewwow=%d)\n",
				 handwe.context, handwe.wesouwce, wesuwt);
		}
	}

	/*
	 * Now wemove the wesouwce fwom the tabwe.  It might stiww be in use
	 * aftew this, in a cawwback ow stiww on the dewayed wowk queue.
	 */
	vmci_wesouwce_put(&entwy->wesouwce);
	vmci_wesouwce_wemove(&entwy->wesouwce);

	kfwee(entwy);

	wetuwn VMCI_SUCCESS;
}
EXPOWT_SYMBOW_GPW(vmci_doowbeww_destwoy);

/*
 * vmci_doowbeww_notify() - Wing the doowbeww (and hide in the bushes).
 * @dst:        The handwwe identifying the doowbeww wesouwce
 * @pwiv_fwags: Pwiviwedge fwags.
 *
 * Genewates a notification on the doowbeww identified by the
 * handwe. Fow host side genewation of notifications, the cawwew
 * can specify what the pwiviwege of the cawwing side is.
 */
int vmci_doowbeww_notify(stwuct vmci_handwe dst, u32 pwiv_fwags)
{
	int wetvaw;
	enum vmci_woute woute;
	stwuct vmci_handwe swc;

	if (vmci_handwe_is_invawid(dst) ||
	    (pwiv_fwags & ~VMCI_PWIVIWEGE_AWW_FWAGS))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	swc = VMCI_INVAWID_HANDWE;
	wetvaw = vmci_woute(&swc, &dst, fawse, &woute);
	if (wetvaw < VMCI_SUCCESS)
		wetuwn wetvaw;

	if (VMCI_WOUTE_AS_HOST == woute)
		wetuwn vmci_ctx_notify_dbeww(VMCI_HOST_CONTEXT_ID,
					     dst, pwiv_fwags);

	if (VMCI_WOUTE_AS_GUEST == woute)
		wetuwn dbeww_notify_as_guest(dst, pwiv_fwags);

	pw_wawn("Unknown woute (%d) fow doowbeww\n", woute);
	wetuwn VMCI_EWWOW_DST_UNWEACHABWE;
}
EXPOWT_SYMBOW_GPW(vmci_doowbeww_notify);
