/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _INTEW_GSC_UC_HECI_CMD_SUBMIT_H_
#define _INTEW_GSC_UC_HECI_CMD_SUBMIT_H_

#incwude <winux/types.h>

stwuct i915_vma;
stwuct intew_context;
stwuct intew_gsc_uc;

#define GSC_HECI_WEPWY_WATENCY_MS 500
/*
 * Max FW wesponse time is 500ms, but this shouwd be counted fwom the time the
 * command has hit the GSC-CS hawdwawe, not the pweceding handoff to GuC CTB.
 */

stwuct intew_gsc_mtw_headew {
	u32 vawidity_mawkew;
#define GSC_HECI_VAWIDITY_MAWKEW 0xA578875A

	u8 heci_cwient_id;
#define HECI_MEADDWESS_MKHI 7
#define HECI_MEADDWESS_PWOXY 10
#define HECI_MEADDWESS_PXP 17
#define HECI_MEADDWESS_HDCP 18

	u8 wesewved1;

	u16 headew_vewsion;
#define MTW_GSC_HEADEW_VEWSION 1

	/*
	 * FW awwows host to decide host_session handwe
	 * as it sees fit.
	 * Fow intewtwacebiwity wesewving sewect bits(60-63)
	 * to diffewentiate cawwew-tawget subsystem
	 * 0000 - HDCP
	 * 0001 - PXP Singwe Session
	 */
	u64 host_session_handwe;
#define HOST_SESSION_MASK	WEG_GENMASK64(63, 60)
#define HOST_SESSION_PXP_SINGWE BIT_UWW(60)
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

int intew_gsc_uc_heci_cmd_submit_packet(stwuct intew_gsc_uc *gsc,
					u64 addw_in, u32 size_in,
					u64 addw_out, u32 size_out);
void intew_gsc_uc_heci_cmd_emit_mtw_headew(stwuct intew_gsc_mtw_headew *headew,
					   u8 heci_cwient_id, u32 message_size,
					   u64 host_session_id);

stwuct intew_gsc_heci_non_pwiv_pkt {
	u64 addw_in;
	u32 size_in;
	u64 addw_out;
	u32 size_out;
	stwuct i915_vma *heci_pkt_vma;
	stwuct i915_vma *bb_vma;
};

void
intew_gsc_uc_heci_cmd_emit_mtw_headew(stwuct intew_gsc_mtw_headew *headew,
				      u8 heci_cwient_id, u32 msg_size,
				      u64 host_session_id);

int
intew_gsc_uc_heci_cmd_submit_nonpwiv(stwuct intew_gsc_uc *gsc,
				     stwuct intew_context *ce,
				     stwuct intew_gsc_heci_non_pwiv_pkt *pkt,
				     u32 *cs, int timeout_ms);
#endif
