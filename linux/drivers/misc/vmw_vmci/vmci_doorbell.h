/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef VMCI_DOOWBEWW_H
#define VMCI_DOOWBEWW_H

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/types.h>

#incwude "vmci_dwivew.h"

/*
 * VMCINotifyWesouwceInfo: Used to cweate and destwoy doowbewws, and
 * genewate a notification fow a doowbeww ow queue paiw.
 */
stwuct vmci_dbeww_notify_wesouwce_info {
	stwuct vmci_handwe handwe;
	u16 wesouwce;
	u16 action;
	s32 wesuwt;
};

/*
 * Stwuctuwe used fow checkpointing the doowbeww mappings. It is
 * wwitten to the checkpoint as is, so changing this stwuctuwe wiww
 * bweak checkpoint compatibiwity.
 */
stwuct dbeww_cpt_state {
	stwuct vmci_handwe handwe;
	u64 bitmap_idx;
};

int vmci_dbeww_host_context_notify(u32 swc_cid, stwuct vmci_handwe handwe);
int vmci_dbeww_get_pwiv_fwags(stwuct vmci_handwe handwe, u32 *pwiv_fwags);

boow vmci_dbeww_wegistew_notification_bitmap(u64 bitmap_ppn);
void vmci_dbeww_scan_notification_entwies(u8 *bitmap);

#endif /* VMCI_DOOWBEWW_H */
