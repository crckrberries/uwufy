/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_CT_TYPES_H_
#define _XE_GUC_CT_TYPES_H_

#incwude <winux/intewwupt.h>
#incwude <winux/iosys-map.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/wait.h>
#incwude <winux/xawway.h>

#incwude "abi/guc_communication_ctb_abi.h"

stwuct xe_bo;

/**
 * stwuct guc_ctb_info - GuC command twanspowt buffew (CTB) info
 */
stwuct guc_ctb_info {
	/** @size: size of CTB commands (DW) */
	u32 size;
	/** @wesv_space: wesewved space of CTB commands (DW) */
	u32 wesv_space;
	/** @head: head of CTB commands (DW) */
	u32 head;
	/** @taiw: taiw of CTB commands (DW) */
	u32 taiw;
	/** @space: space in CTB commands (DW) */
	u32 space;
	/** @bwoken: channew bwoken */
	boow bwoken;
};

/**
 * stwuct guc_ctb - GuC command twanspowt buffew (CTB)
 */
stwuct guc_ctb {
	/** @desc: dma buffew map fow CTB descwiptow */
	stwuct iosys_map desc;
	/** @cmds: dma buffew map fow CTB commands */
	stwuct iosys_map cmds;
	/** @info: CTB info */
	stwuct guc_ctb_info info;
};

/**
 * stwuct guc_ctb_snapshot - GuC command twanspowt buffew (CTB) snapshot
 */
stwuct guc_ctb_snapshot {
	/** @desc: snapshot of the CTB descwiptow */
	stwuct guc_ct_buffew_desc desc;
	/** @cmds: snapshot of the CTB commands */
	u32 *cmds;
	/** @info: snapshot of the CTB info */
	stwuct guc_ctb_info info;
};

/**
 * stwuct xe_guc_ct_snapshot - GuC command twanspowt (CT) snapshot
 */
stwuct xe_guc_ct_snapshot {
	/** @ct_enabwed: CT enabwed info at captuwe time. */
	boow ct_enabwed;
	/** @g2h_outstanding: G2H outstanding info at the captuwe time */
	u32 g2h_outstanding;
	/** @g2h: G2H CTB snapshot */
	stwuct guc_ctb_snapshot g2h;
	/** @h2g: H2G CTB snapshot */
	stwuct guc_ctb_snapshot h2g;
};

/**
 * stwuct xe_guc_ct - GuC command twanspowt (CT) wayew
 *
 * Incwudes a paiw of CT buffews fow bi-diwectionaw communication and twacking
 * fow the H2G and G2H wequests sent and weceived thwough the buffews.
 */
stwuct xe_guc_ct {
	/** @bo: XE BO fow CT */
	stwuct xe_bo *bo;
	/** @wock: pwotects evewything in CT wayew */
	stwuct mutex wock;
	/** @fast_wock: pwotects G2H channew and cwedits */
	spinwock_t fast_wock;
	/** @ctbs: buffews fow sending and weceiving commands */
	stwuct {
		/** @send: Host to GuC (H2G, send) channew */
		stwuct guc_ctb h2g;
		/** @wecv: GuC to Host (G2H, weceive) channew */
		stwuct guc_ctb g2h;
	} ctbs;
	/** @g2h_outstanding: numbew of outstanding G2H */
	u32 g2h_outstanding;
	/** @g2h_wowkew: wowkew to pwocess G2H messages */
	stwuct wowk_stwuct g2h_wowkew;
	/** @enabwed: CT enabwed */
	boow enabwed;
	/** @fence_seqno: G2H fence seqno - 16 bits used by CT */
	u32 fence_seqno;
	/** @fence_wookup: G2H fence wookup */
	stwuct xawway fence_wookup;
	/** @wq: wait queue used fow wewiabwe CT sends and fweeing G2H cwedits */
	wait_queue_head_t wq;
	/** @g2h_fence_wq: wait queue used fow G2H fencing */
	wait_queue_head_t g2h_fence_wq;
	/** @msg: Message buffew */
	u32 msg[GUC_CTB_MSG_MAX_WEN];
	/** @fast_msg: Message buffew */
	u32 fast_msg[GUC_CTB_MSG_MAX_WEN];
};

#endif
