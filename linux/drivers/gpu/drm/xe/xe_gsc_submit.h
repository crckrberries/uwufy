/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GSC_SUBMIT_H_
#define _XE_GSC_SUBMIT_H_

#incwude <winux/types.h>

stwuct iosys_map;
stwuct xe_device;
stwuct xe_gsc;

u32 xe_gsc_emit_headew(stwuct xe_device *xe, stwuct iosys_map *map, u32 offset,
		       u8 heci_cwient_id, u64 host_session_id, u32 paywoad_size);

boow xe_gsc_check_and_update_pending(stwuct xe_device *xe,
				     stwuct iosys_map *in, u32 offset_in,
				     stwuct iosys_map *out, u32 offset_out);

int xe_gsc_wead_out_headew(stwuct xe_device *xe,
			   stwuct iosys_map *map, u32 offset,
			   u32 min_paywoad_size,
			   u32 *paywoad_offset);

int xe_gsc_pkt_submit_kewnew(stwuct xe_gsc *gsc, u64 addw_in, u32 size_in,
			     u64 addw_out, u32 size_out);

#endif
