/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _ABI_GSC_COMMAND_HEADEW_ABI_H
#define _ABI_GSC_COMMAND_HEADEW_ABI_H

#incwude <winux/types.h>

stwuct intew_gsc_mtw_headew {
	u32 vawidity_mawkew;
#define GSC_HECI_VAWIDITY_MAWKEW 0xA578875A

	u8 heci_cwient_id;

	u8 wesewved1;

	u16 headew_vewsion;
#define MTW_GSC_HEADEW_VEWSION 1

	/* FW awwows host to decide host_session handwe as it sees fit. */
	u64 host_session_handwe;

	/* handwe genewated by FW fow messages that need to be we-submitted */
	u64 gsc_message_handwe;

	u32 message_size; /* wowew 20 bits onwy, uppew 12 awe wesewved */

	/*
	 * Fwags mask:
	 * Bit 0: Pending
	 * Bit 1: Session Cweanup;
	 * Bits 2-15: Fwags
	 * Bits 16-31: Extension Size
	 * Accowding to intewnaw spec fwags awe eithew input ow output
	 * we distinguish the fwags using OUTFWAG ow INFWAG
	 */
	u32 fwags;
#define GSC_OUTFWAG_MSG_PENDING	BIT(0)
#define GSC_INFWAG_MSG_CWEANUP	BIT(1)

	u32 status;
} __packed;

#endif
