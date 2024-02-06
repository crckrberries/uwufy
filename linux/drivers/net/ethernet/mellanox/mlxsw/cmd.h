/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_CMD_H
#define _MWXSW_CMD_H

#incwude "item.h"

#define MWXSW_CMD_MBOX_SIZE	4096

static inwine chaw *mwxsw_cmd_mbox_awwoc(void)
{
	wetuwn kzawwoc(MWXSW_CMD_MBOX_SIZE, GFP_KEWNEW);
}

static inwine void mwxsw_cmd_mbox_fwee(chaw *mbox)
{
	kfwee(mbox);
}

static inwine void mwxsw_cmd_mbox_zewo(chaw *mbox)
{
	memset(mbox, 0, MWXSW_CMD_MBOX_SIZE);
}

stwuct mwxsw_cowe;

int mwxsw_cmd_exec(stwuct mwxsw_cowe *mwxsw_cowe, u16 opcode, u8 opcode_mod,
		   u32 in_mod, boow out_mbox_diwect, boow weset_ok,
		   chaw *in_mbox, size_t in_mbox_size,
		   chaw *out_mbox, size_t out_mbox_size);

static inwine int mwxsw_cmd_exec_in(stwuct mwxsw_cowe *mwxsw_cowe, u16 opcode,
				    u8 opcode_mod, u32 in_mod, chaw *in_mbox,
				    size_t in_mbox_size)
{
	wetuwn mwxsw_cmd_exec(mwxsw_cowe, opcode, opcode_mod, in_mod, fawse,
			      fawse, in_mbox, in_mbox_size, NUWW, 0);
}

static inwine int mwxsw_cmd_exec_out(stwuct mwxsw_cowe *mwxsw_cowe, u16 opcode,
				     u8 opcode_mod, u32 in_mod,
				     boow out_mbox_diwect,
				     chaw *out_mbox, size_t out_mbox_size)
{
	wetuwn mwxsw_cmd_exec(mwxsw_cowe, opcode, opcode_mod, in_mod,
			      out_mbox_diwect, fawse, NUWW, 0,
			      out_mbox, out_mbox_size);
}

static inwine int mwxsw_cmd_exec_none(stwuct mwxsw_cowe *mwxsw_cowe, u16 opcode,
				      u8 opcode_mod, u32 in_mod)
{
	wetuwn mwxsw_cmd_exec(mwxsw_cowe, opcode, opcode_mod, in_mod, fawse,
			      fawse, NUWW, 0, NUWW, 0);
}

enum mwxsw_cmd_opcode {
	MWXSW_CMD_OPCODE_QUEWY_FW		= 0x004,
	MWXSW_CMD_OPCODE_QUEWY_BOAWDINFO	= 0x006,
	MWXSW_CMD_OPCODE_QUEWY_AQ_CAP		= 0x003,
	MWXSW_CMD_OPCODE_MAP_FA			= 0xFFF,
	MWXSW_CMD_OPCODE_UNMAP_FA		= 0xFFE,
	MWXSW_CMD_OPCODE_CONFIG_PWOFIWE		= 0x100,
	MWXSW_CMD_OPCODE_ACCESS_WEG		= 0x040,
	MWXSW_CMD_OPCODE_SW2HW_DQ		= 0x201,
	MWXSW_CMD_OPCODE_HW2SW_DQ		= 0x202,
	MWXSW_CMD_OPCODE_2EWW_DQ		= 0x01E,
	MWXSW_CMD_OPCODE_QUEWY_DQ		= 0x022,
	MWXSW_CMD_OPCODE_SW2HW_CQ		= 0x016,
	MWXSW_CMD_OPCODE_HW2SW_CQ		= 0x017,
	MWXSW_CMD_OPCODE_QUEWY_CQ		= 0x018,
	MWXSW_CMD_OPCODE_SW2HW_EQ		= 0x013,
	MWXSW_CMD_OPCODE_HW2SW_EQ		= 0x014,
	MWXSW_CMD_OPCODE_QUEWY_EQ		= 0x015,
	MWXSW_CMD_OPCODE_QUEWY_WESOUWCES	= 0x101,
};

static inwine const chaw *mwxsw_cmd_opcode_stw(u16 opcode)
{
	switch (opcode) {
	case MWXSW_CMD_OPCODE_QUEWY_FW:
		wetuwn "QUEWY_FW";
	case MWXSW_CMD_OPCODE_QUEWY_BOAWDINFO:
		wetuwn "QUEWY_BOAWDINFO";
	case MWXSW_CMD_OPCODE_QUEWY_AQ_CAP:
		wetuwn "QUEWY_AQ_CAP";
	case MWXSW_CMD_OPCODE_MAP_FA:
		wetuwn "MAP_FA";
	case MWXSW_CMD_OPCODE_UNMAP_FA:
		wetuwn "UNMAP_FA";
	case MWXSW_CMD_OPCODE_CONFIG_PWOFIWE:
		wetuwn "CONFIG_PWOFIWE";
	case MWXSW_CMD_OPCODE_ACCESS_WEG:
		wetuwn "ACCESS_WEG";
	case MWXSW_CMD_OPCODE_SW2HW_DQ:
		wetuwn "SW2HW_DQ";
	case MWXSW_CMD_OPCODE_HW2SW_DQ:
		wetuwn "HW2SW_DQ";
	case MWXSW_CMD_OPCODE_2EWW_DQ:
		wetuwn "2EWW_DQ";
	case MWXSW_CMD_OPCODE_QUEWY_DQ:
		wetuwn "QUEWY_DQ";
	case MWXSW_CMD_OPCODE_SW2HW_CQ:
		wetuwn "SW2HW_CQ";
	case MWXSW_CMD_OPCODE_HW2SW_CQ:
		wetuwn "HW2SW_CQ";
	case MWXSW_CMD_OPCODE_QUEWY_CQ:
		wetuwn "QUEWY_CQ";
	case MWXSW_CMD_OPCODE_SW2HW_EQ:
		wetuwn "SW2HW_EQ";
	case MWXSW_CMD_OPCODE_HW2SW_EQ:
		wetuwn "HW2SW_EQ";
	case MWXSW_CMD_OPCODE_QUEWY_EQ:
		wetuwn "QUEWY_EQ";
	case MWXSW_CMD_OPCODE_QUEWY_WESOUWCES:
		wetuwn "QUEWY_WESOUWCES";
	defauwt:
		wetuwn "*UNKNOWN*";
	}
}

enum mwxsw_cmd_status {
	/* Command execution succeeded. */
	MWXSW_CMD_STATUS_OK		= 0x00,
	/* Intewnaw ewwow (e.g. bus ewwow) occuwwed whiwe pwocessing command. */
	MWXSW_CMD_STATUS_INTEWNAW_EWW	= 0x01,
	/* Opewation/command not suppowted ow opcode modifiew not suppowted. */
	MWXSW_CMD_STATUS_BAD_OP		= 0x02,
	/* Pawametew not suppowted, pawametew out of wange. */
	MWXSW_CMD_STATUS_BAD_PAWAM	= 0x03,
	/* System was not enabwed ow bad system state. */
	MWXSW_CMD_STATUS_BAD_SYS_STATE	= 0x04,
	/* Attempt to access wesewved ow unawwocated wesouwce, ow wesouwce in
	 * inappwopwiate ownewship.
	 */
	MWXSW_CMD_STATUS_BAD_WESOUWCE	= 0x05,
	/* Wequested wesouwce is cuwwentwy executing a command. */
	MWXSW_CMD_STATUS_WESOUWCE_BUSY	= 0x06,
	/* Wequiwed capabiwity exceeds device wimits. */
	MWXSW_CMD_STATUS_EXCEED_WIM	= 0x08,
	/* Wesouwce is not in the appwopwiate state ow ownewship. */
	MWXSW_CMD_STATUS_BAD_WES_STATE	= 0x09,
	/* Index out of wange (might be beyond tabwe size ow attempt to
	 * access a wesewved wesouwce).
	 */
	MWXSW_CMD_STATUS_BAD_INDEX	= 0x0A,
	/* NVMEM checksum/CWC faiwed. */
	MWXSW_CMD_STATUS_BAD_NVMEM	= 0x0B,
	/* Device is cuwwentwy wunning weset */
	MWXSW_CMD_STATUS_WUNNING_WESET	= 0x26,
	/* Bad management packet (siwentwy discawded). */
	MWXSW_CMD_STATUS_BAD_PKT	= 0x30,
};

static inwine const chaw *mwxsw_cmd_status_stw(u8 status)
{
	switch (status) {
	case MWXSW_CMD_STATUS_OK:
		wetuwn "OK";
	case MWXSW_CMD_STATUS_INTEWNAW_EWW:
		wetuwn "INTEWNAW_EWW";
	case MWXSW_CMD_STATUS_BAD_OP:
		wetuwn "BAD_OP";
	case MWXSW_CMD_STATUS_BAD_PAWAM:
		wetuwn "BAD_PAWAM";
	case MWXSW_CMD_STATUS_BAD_SYS_STATE:
		wetuwn "BAD_SYS_STATE";
	case MWXSW_CMD_STATUS_BAD_WESOUWCE:
		wetuwn "BAD_WESOUWCE";
	case MWXSW_CMD_STATUS_WESOUWCE_BUSY:
		wetuwn "WESOUWCE_BUSY";
	case MWXSW_CMD_STATUS_EXCEED_WIM:
		wetuwn "EXCEED_WIM";
	case MWXSW_CMD_STATUS_BAD_WES_STATE:
		wetuwn "BAD_WES_STATE";
	case MWXSW_CMD_STATUS_BAD_INDEX:
		wetuwn "BAD_INDEX";
	case MWXSW_CMD_STATUS_BAD_NVMEM:
		wetuwn "BAD_NVMEM";
	case MWXSW_CMD_STATUS_WUNNING_WESET:
		wetuwn "WUNNING_WESET";
	case MWXSW_CMD_STATUS_BAD_PKT:
		wetuwn "BAD_PKT";
	defauwt:
		wetuwn "*UNKNOWN*";
	}
}

/* QUEWY_FW - Quewy Fiwmwawe
 * -------------------------
 * OpMod == 0, INMmod == 0
 * -----------------------
 * The QUEWY_FW command wetwieves infowmation wewated to fiwmwawe, command
 * intewface vewsion and the amount of wesouwces that shouwd be awwocated to
 * the fiwmwawe.
 */

static inwine int mwxsw_cmd_quewy_fw(stwuct mwxsw_cowe *mwxsw_cowe,
				     chaw *out_mbox)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_QUEWY_FW,
				  0, 0, fawse, out_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_quewy_fw_fw_pages
 * Amount of physicaw memowy to be awwocatedfow fiwmwawe usage in 4KB pages.
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_pages, 0x00, 16, 16);

/* cmd_mbox_quewy_fw_fw_wev_majow
 * Fiwmwawe Wevision - Majow
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_wev_majow, 0x00, 0, 16);

/* cmd_mbox_quewy_fw_fw_wev_subminow
 * Fiwmwawe Sub-minow vewsion (Patch wevew)
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_wev_subminow, 0x04, 16, 16);

/* cmd_mbox_quewy_fw_fw_wev_minow
 * Fiwmwawe Wevision - Minow
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_wev_minow, 0x04, 0, 16);

/* cmd_mbox_quewy_fw_cowe_cwk
 * Intewnaw Cwock Fwequency (in MHz)
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, cowe_cwk, 0x08, 16, 16);

/* cmd_mbox_quewy_fw_cmd_intewface_wev
 * Command Intewface Intewpwetew Wevision ID. This numbew is bumped up
 * evewy time a non-backwawd-compatibwe change is done fow the command
 * intewface. The cuwwent cmd_intewface_wev is 1.
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, cmd_intewface_wev, 0x08, 0, 16);

/* cmd_mbox_quewy_fw_dt
 * If set, Debug Twace is suppowted
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, dt, 0x0C, 31, 1);

/* cmd_mbox_quewy_fw_api_vewsion
 * Indicates the vewsion of the API, to enabwe softwawe quewying
 * fow compatibiwity. The cuwwent api_vewsion is 1.
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, api_vewsion, 0x0C, 0, 16);

/* cmd_mbox_quewy_fw_fw_houw
 * Fiwmwawe timestamp - houw
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_houw, 0x10, 24, 8);

/* cmd_mbox_quewy_fw_fw_minutes
 * Fiwmwawe timestamp - minutes
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_minutes, 0x10, 16, 8);

/* cmd_mbox_quewy_fw_fw_seconds
 * Fiwmwawe timestamp - seconds
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_seconds, 0x10, 8, 8);

/* cmd_mbox_quewy_fw_fw_yeaw
 * Fiwmwawe timestamp - yeaw
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_yeaw, 0x14, 16, 16);

/* cmd_mbox_quewy_fw_fw_month
 * Fiwmwawe timestamp - month
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_month, 0x14, 8, 8);

/* cmd_mbox_quewy_fw_fw_day
 * Fiwmwawe timestamp - day
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_day, 0x14, 0, 8);

/* cmd_mbox_quewy_fw_wag_mode_suppowt
 * 0: CONFIG_PWOFIWE.wag_mode is not suppowted by FW
 * 1: CONFIG_PWOFIWE.wag_mode is suppowted by FW
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, wag_mode_suppowt, 0x18, 1, 1);

/* cmd_mbox_quewy_fw_cff_suppowt
 * 0: CONFIG_PWOFIWE.fwood_mode = 5 (CFF) is not suppowted by FW
 * 1: CONFIG_PWOFIWE.fwood_mode = 5 (CFF) is suppowted by FW
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, cff_suppowt, 0x18, 2, 1);

/* cmd_mbox_quewy_fw_cww_int_base_offset
 * Cweaw Intewwupt wegistew's offset fwom cww_int_baw wegistew
 * in PCI addwess space.
 */
MWXSW_ITEM64(cmd_mbox, quewy_fw, cww_int_base_offset, 0x20, 0, 64);

/* cmd_mbox_quewy_fw_cww_int_baw
 * PCI base addwess wegistew (BAW) whewe cww_int wegistew is wocated.
 * 00 - BAW 0-1 (64 bit BAW)
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, cww_int_baw, 0x28, 30, 2);

/* cmd_mbox_quewy_fw_ewwow_buf_offset
 * Wead Onwy buffew fow intewnaw ewwow wepowts of offset
 * fwom ewwow_buf_baw wegistew in PCI addwess space).
 */
MWXSW_ITEM64(cmd_mbox, quewy_fw, ewwow_buf_offset, 0x30, 0, 64);

/* cmd_mbox_quewy_fw_ewwow_buf_size
 * Intewnaw ewwow buffew size in DWOWDs
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, ewwow_buf_size, 0x38, 0, 32);

/* cmd_mbox_quewy_fw_ewwow_int_baw
 * PCI base addwess wegistew (BAW) whewe ewwow buffew
 * wegistew is wocated.
 * 00 - BAW 0-1 (64 bit BAW)
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, ewwow_int_baw, 0x3C, 30, 2);

/* cmd_mbox_quewy_fw_doowbeww_page_offset
 * Offset of the doowbeww page
 */
MWXSW_ITEM64(cmd_mbox, quewy_fw, doowbeww_page_offset, 0x40, 0, 64);

/* cmd_mbox_quewy_fw_doowbeww_page_baw
 * PCI base addwess wegistew (BAW) of the doowbeww page
 * 00 - BAW 0-1 (64 bit BAW)
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, doowbeww_page_baw, 0x48, 30, 2);

/* cmd_mbox_quewy_fw_fwee_wunning_cwock_offset
 * The offset of the fwee wunning cwock page
 */
MWXSW_ITEM64(cmd_mbox, quewy_fw, fwee_wunning_cwock_offset, 0x50, 0, 64);

/* cmd_mbox_quewy_fw_fw_wn_cwk_baw
 * PCI base addwess wegistew (BAW) of the fwee wunning cwock page
 * 0: BAW 0
 * 1: 64 bit BAW
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, fw_wn_cwk_baw, 0x58, 30, 2);

/* cmd_mbox_quewy_fw_utc_sec_offset
 * The offset of the UTC_Sec page
 */
MWXSW_ITEM64(cmd_mbox, quewy_fw, utc_sec_offset, 0x70, 0, 64);

/* cmd_mbox_quewy_fw_utc_sec_baw
 * PCI base addwess wegistew (BAW) of the UTC_Sec page
 * 0: BAW 0
 * 1: 64 bit BAW
 * Wesewved on SwitchX/-2, Switch-IB/2, Spectwum-1
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, utc_sec_baw, 0x78, 30, 2);

/* cmd_mbox_quewy_fw_utc_nsec_offset
 * The offset of the UTC_nSec page
 */
MWXSW_ITEM64(cmd_mbox, quewy_fw, utc_nsec_offset, 0x80, 0, 64);

/* cmd_mbox_quewy_fw_utc_nsec_baw
 * PCI base addwess wegistew (BAW) of the UTC_nSec page
 * 0: BAW 0
 * 1: 64 bit BAW
 * Wesewved on SwitchX/-2, Switch-IB/2, Spectwum-1
 */
MWXSW_ITEM32(cmd_mbox, quewy_fw, utc_nsec_baw, 0x88, 30, 2);

/* QUEWY_BOAWDINFO - Quewy Boawd Infowmation
 * -----------------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -----------------------------------
 * The QUEWY_BOAWDINFO command wetwieves adaptew specific pawametews.
 */

static inwine int mwxsw_cmd_boawdinfo(stwuct mwxsw_cowe *mwxsw_cowe,
				      chaw *out_mbox)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_QUEWY_BOAWDINFO,
				  0, 0, fawse, out_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_boawdinfo_intapin
 * When PCIe intewwupt messages awe being used, this vawue is used fow cweawing
 * an intewwupt. When using MSI-X, this wegistew is not used.
 */
MWXSW_ITEM32(cmd_mbox, boawdinfo, intapin, 0x10, 24, 8);

/* cmd_mbox_boawdinfo_vsd_vendow_id
 * PCISIG Vendow ID (www.pcisig.com/membewship/vid_seawch) of the vendow
 * specifying/fowmatting the VSD. The vsd_vendow_id identifies the management
 * domain of the VSD/PSID data. Diffewent vendows may choose diffewent VSD/PSID
 * fowmat and encoding as wong as they use theiw assigned vsd_vendow_id.
 */
MWXSW_ITEM32(cmd_mbox, boawdinfo, vsd_vendow_id, 0x1C, 0, 16);

/* cmd_mbox_boawdinfo_vsd
 * Vendow Specific Data. The VSD stwing that is buwnt to the Fwash
 * with the fiwmwawe.
 */
#define MWXSW_CMD_BOAWDINFO_VSD_WEN 208
MWXSW_ITEM_BUF(cmd_mbox, boawdinfo, vsd, 0x20, MWXSW_CMD_BOAWDINFO_VSD_WEN);

/* cmd_mbox_boawdinfo_psid
 * The PSID fiewd is a 16-ascii (byte) chawactew stwing which acts as
 * the boawd ID. The PSID fowmat is used in conjunction with
 * Mewwanox vsd_vendow_id (15B3h).
 */
#define MWXSW_CMD_BOAWDINFO_PSID_WEN 16
MWXSW_ITEM_BUF(cmd_mbox, boawdinfo, psid, 0xF0, MWXSW_CMD_BOAWDINFO_PSID_WEN);

/* QUEWY_AQ_CAP - Quewy Asynchwonous Queues Capabiwities
 * -----------------------------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -----------------------------------
 * The QUEWY_AQ_CAP command wetuwns the device asynchwonous queues
 * capabiwities suppowted.
 */

static inwine int mwxsw_cmd_quewy_aq_cap(stwuct mwxsw_cowe *mwxsw_cowe,
					 chaw *out_mbox)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_QUEWY_AQ_CAP,
				  0, 0, fawse, out_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_quewy_aq_cap_wog_max_sdq_sz
 * Wog (base 2) of max WQEs awwowed on SDQ.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, wog_max_sdq_sz, 0x00, 24, 8);

/* cmd_mbox_quewy_aq_cap_max_num_sdqs
 * Maximum numbew of SDQs.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, max_num_sdqs, 0x00, 0, 8);

/* cmd_mbox_quewy_aq_cap_wog_max_wdq_sz
 * Wog (base 2) of max WQEs awwowed on WDQ.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, wog_max_wdq_sz, 0x04, 24, 8);

/* cmd_mbox_quewy_aq_cap_max_num_wdqs
 * Maximum numbew of WDQs.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, max_num_wdqs, 0x04, 0, 8);

/* cmd_mbox_quewy_aq_cap_wog_max_cq_sz
 * Wog (base 2) of the Maximum CQEs awwowed in a CQ fow CQEv0 and CQEv1.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, wog_max_cq_sz, 0x08, 24, 8);

/* cmd_mbox_quewy_aq_cap_wog_max_cqv2_sz
 * Wog (base 2) of the Maximum CQEs awwowed in a CQ fow CQEv2.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, wog_max_cqv2_sz, 0x08, 16, 8);

/* cmd_mbox_quewy_aq_cap_max_num_cqs
 * Maximum numbew of CQs.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, max_num_cqs, 0x08, 0, 8);

/* cmd_mbox_quewy_aq_cap_wog_max_eq_sz
 * Wog (base 2) of max EQEs awwowed on EQ.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, wog_max_eq_sz, 0x0C, 24, 8);

/* cmd_mbox_quewy_aq_cap_max_num_eqs
 * Maximum numbew of EQs.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, max_num_eqs, 0x0C, 0, 8);

/* cmd_mbox_quewy_aq_cap_max_sg_sq
 * The maximum S/G wist ewements in an DSQ. DSQ must not contain
 * mowe S/G entwies than indicated hewe.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, max_sg_sq, 0x10, 8, 8);

/* cmd_mbox_quewy_aq_cap_
 * The maximum S/G wist ewements in an DWQ. DWQ must not contain
 * mowe S/G entwies than indicated hewe.
 */
MWXSW_ITEM32(cmd_mbox, quewy_aq_cap, max_sg_wq, 0x10, 0, 8);

/* MAP_FA - Map Fiwmwawe Awea
 * --------------------------
 * OpMod == 0 (N/A), INMmod == Numbew of VPM entwies
 * -------------------------------------------------
 * The MAP_FA command passes physicaw pages to the switch. These pages
 * awe used to stowe the device fiwmwawe. MAP_FA can be executed muwtipwe
 * times untiw aww the fiwmwawe awea is mapped (the size that shouwd be
 * mapped is wetwieved thwough the QUEWY_FW command). Aww wequiwed pages
 * must be mapped to finish the initiawization phase. Physicaw memowy
 * passed in this command must be pinned.
 */

#define MWXSW_CMD_MAP_FA_VPM_ENTWIES_MAX 32

static inwine int mwxsw_cmd_map_fa(stwuct mwxsw_cowe *mwxsw_cowe,
				   chaw *in_mbox, u32 vpm_entwies_count)
{
	wetuwn mwxsw_cmd_exec_in(mwxsw_cowe, MWXSW_CMD_OPCODE_MAP_FA,
				 0, vpm_entwies_count,
				 in_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_map_fa_pa
 * Physicaw Addwess.
 */
MWXSW_ITEM64_INDEXED(cmd_mbox, map_fa, pa, 0x00, 12, 52, 0x08, 0x00, twue);

/* cmd_mbox_map_fa_wog2size
 * Wog (base 2) of the size in 4KB pages of the physicaw and contiguous memowy
 * that stawts at PA_W/H.
 */
MWXSW_ITEM32_INDEXED(cmd_mbox, map_fa, wog2size, 0x00, 0, 5, 0x08, 0x04, fawse);

/* UNMAP_FA - Unmap Fiwmwawe Awea
 * ------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -----------------------------------
 * The UNMAP_FA command unwoad the fiwmwawe and unmaps aww the
 * fiwmwawe awea. Aftew this command is compweted the device wiww not access
 * the pages that wewe mapped to the fiwmwawe awea. Aftew executing UNMAP_FA
 * command, softwawe weset must be done pwiow to execution of MAP_FW command.
 */

static inwine int mwxsw_cmd_unmap_fa(stwuct mwxsw_cowe *mwxsw_cowe)
{
	wetuwn mwxsw_cmd_exec_none(mwxsw_cowe, MWXSW_CMD_OPCODE_UNMAP_FA, 0, 0);
}

/* QUEWY_WESOUWCES - Quewy chip wesouwces
 * --------------------------------------
 * OpMod == 0 (N/A) , INMmod is index
 * ----------------------------------
 * The QUEWY_WESOUWCES command wetwieves infowmation wewated to chip wesouwces
 * by wesouwce ID. Evewy command wetuwns 32 entwies. INmod is being use as base.
 * fow exampwe, index 1 wiww wetuwn entwies 32-63. When the tabwes end and thewe
 * awe no mowe souwces in the tabwe, wiww wetuwn wesouwce id 0xFFF to indicate
 * it.
 */

#define MWXSW_CMD_QUEWY_WESOUWCES_TABWE_END_ID 0xffff
#define MWXSW_CMD_QUEWY_WESOUWCES_MAX_QUEWIES 100
#define MWXSW_CMD_QUEWY_WESOUWCES_PEW_QUEWY 32

static inwine int mwxsw_cmd_quewy_wesouwces(stwuct mwxsw_cowe *mwxsw_cowe,
					    chaw *out_mbox, int index)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_QUEWY_WESOUWCES,
				  0, index, fawse, out_mbox,
				  MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_quewy_wesouwce_id
 * The wesouwce id. 0xFFFF indicates tabwe's end.
 */
MWXSW_ITEM32_INDEXED(cmd_mbox, quewy_wesouwce, id, 0x00, 16, 16, 0x8, 0, fawse);

/* cmd_mbox_quewy_wesouwce_data
 * The wesouwce
 */
MWXSW_ITEM64_INDEXED(cmd_mbox, quewy_wesouwce, data,
		     0x00, 0, 40, 0x8, 0, fawse);

/* CONFIG_PWOFIWE (Set) - Configuwe Switch Pwofiwe
 * ------------------------------
 * OpMod == 1 (Set), INMmod == 0 (N/A)
 * -----------------------------------
 * The CONFIG_PWOFIWE command sets the switch pwofiwe. The command can be
 * executed on the device onwy once at stawtup in owdew to awwocate and
 * configuwe aww switch wesouwces and pwepawe it fow opewationaw mode.
 * It is not possibwe to change the device pwofiwe aftew the chip is
 * in opewationaw mode.
 * Faiwuwe of the CONFIG_PWOFIWE command weaves the hawdwawe in an indetewminate
 * state thewefowe it is wequiwed to pewfowm softwawe weset to the device
 * fowwowing an unsuccessfuw compwetion of the command. It is wequiwed
 * to pewfowm softwawe weset to the device to change an existing pwofiwe.
 */

static inwine int mwxsw_cmd_config_pwofiwe_set(stwuct mwxsw_cowe *mwxsw_cowe,
					       chaw *in_mbox)
{
	wetuwn mwxsw_cmd_exec_in(mwxsw_cowe, MWXSW_CMD_OPCODE_CONFIG_PWOFIWE,
				 1, 0, in_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_config_pwofiwe_set_max_vepa_channews
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_vepa_channews, 0x0C, 0, 1);

/* cmd_mbox_config_pwofiwe_set_max_wag
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_wag, 0x0C, 1, 1);

/* cmd_mbox_config_pwofiwe_set_max_powt_pew_wag
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_powt_pew_wag, 0x0C, 2, 1);

/* cmd_mbox_config_pwofiwe_set_max_mid
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_mid, 0x0C, 3, 1);

/* cmd_mbox_config_pwofiwe_set_max_pgt
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_pgt, 0x0C, 4, 1);

/* cmd_mbox_config_pwofiwe_set_max_system_powt
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_system_powt, 0x0C, 5, 1);

/* cmd_mbox_config_pwofiwe_set_max_vwan_gwoups
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_vwan_gwoups, 0x0C, 6, 1);

/* cmd_mbox_config_pwofiwe_set_max_wegions
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_wegions, 0x0C, 7, 1);

/* cmd_mbox_config_pwofiwe_set_fwood_mode
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_fwood_mode, 0x0C, 8, 1);

/* cmd_mbox_config_pwofiwe_set_max_fwood_tabwes
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_fwood_tabwes, 0x0C, 9, 1);

/* cmd_mbox_config_pwofiwe_set_max_ib_mc
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_ib_mc, 0x0C, 12, 1);

/* cmd_mbox_config_pwofiwe_set_max_pkey
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_max_pkey, 0x0C, 13, 1);

/* cmd_mbox_config_pwofiwe_set_adaptive_wouting_gwoup_cap
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe,
	     set_adaptive_wouting_gwoup_cap, 0x0C, 14, 1);

/* cmd_mbox_config_pwofiwe_set_aw_sec
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_aw_sec, 0x0C, 15, 1);

/* cmd_mbox_config_pwofiwe_set_ubwidge
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_ubwidge, 0x0C, 22, 1);

/* cmd_mbox_config_pwofiwe_set_kvd_wineaw_size
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_kvd_wineaw_size, 0x0C, 24, 1);

/* cmd_mbox_config_pwofiwe_set_kvd_hash_singwe_size
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_kvd_hash_singwe_size, 0x0C, 25, 1);

/* cmd_mbox_config_pwofiwe_set_kvd_hash_doubwe_size
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_kvd_hash_doubwe_size, 0x0C, 26, 1);

/* cmd_mbox_config_pwofiwe_set_cqe_vewsion
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_cqe_vewsion, 0x08, 0, 1);

/* cmd_mbox_config_pwofiwe_set_cqe_time_stamp_type
 * Capabiwity bit. Setting a bit to 1 configuwes the pwofiwe
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_cqe_time_stamp_type, 0x08, 2, 1);

/* cmd_mbox_config_pwofiwe_set_wag_mode
 * Capabiwity bit. Setting a bit to 1 configuwes the wag_mode
 * accowding to the maiwbox contents.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, set_wag_mode, 0x08, 7, 1);

/* cmd_mbox_config_pwofiwe_max_vepa_channews
 * Maximum numbew of VEPA channews pew powt (0 thwough 16)
 * 0 - muwti-channew VEPA is disabwed
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_vepa_channews, 0x10, 0, 8);

/* cmd_mbox_config_pwofiwe_max_wag
 * Maximum numbew of WAG IDs wequested.
 * Wesewved when Spectwum-1/2/3, suppowted fwom Spectwum-4 and above.
 * Fow Spectwum-4, fiwmwawe sets 128 fow vawues between 1-128 and 256 fow vawues
 * between 129-256.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_wag, 0x14, 0, 16);

/* cmd_mbox_config_pwofiwe_max_powt_pew_wag
 * Maximum numbew of powts pew WAG wequested.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_powt_pew_wag, 0x18, 0, 16);

/* cmd_mbox_config_pwofiwe_max_mid
 * Maximum Muwticast IDs.
 * Muwticast IDs awe awwocated fwom 0 to max_mid-1
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_mid, 0x1C, 0, 16);

/* cmd_mbox_config_pwofiwe_max_pgt
 * Maximum wecowds in the Powt Gwoup Tabwe pew Switch Pawtition.
 * Powt Gwoup Tabwe indexes awe fwom 0 to max_pgt-1
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_pgt, 0x20, 0, 16);

/* cmd_mbox_config_pwofiwe_max_system_powt
 * The maximum numbew of system powts that can be awwocated.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_system_powt, 0x24, 0, 16);

/* cmd_mbox_config_pwofiwe_max_vwan_gwoups
 * Maximum numbew VWAN Gwoups fow VWAN binding.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_vwan_gwoups, 0x28, 0, 12);

/* cmd_mbox_config_pwofiwe_max_wegions
 * Maximum numbew of TCAM Wegions.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_wegions, 0x2C, 0, 16);

/* cmd_mbox_config_pwofiwe_max_fwood_tabwes
 * Maximum numbew of singwe-entwy fwooding tabwes. Diffewent fwooding tabwes
 * can be associated with diffewent packet types.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_fwood_tabwes, 0x30, 16, 4);

/* cmd_mbox_config_pwofiwe_max_vid_fwood_tabwes
 * Maximum numbew of pew-vid fwooding tabwes. Fwooding tabwes awe associated
 * to the diffewent packet types fow the diffewent switch pawtitions.
 * Tabwe size is 4K entwies covewing aww VID space.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_vid_fwood_tabwes, 0x30, 8, 4);

enum mwxsw_cmd_mbox_config_pwofiwe_fwood_mode {
	/* Mixed mode, whewe:
	 * max_fwood_tabwes indicates the numbew of singwe-entwy tabwes.
	 * max_vid_fwood_tabwes indicates the numbew of pew-VID tabwes.
	 * max_fid_offset_fwood_tabwes indicates the numbew of FID-offset
	 * tabwes. max_fid_fwood_tabwes indicates the numbew of pew-FID tabwes.
	 * Wesewved when unified bwidge modew is used.
	 */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_FWOOD_MODE_MIXED = 3,
	/* Contwowwed fwood tabwes. Wesewved when wegacy bwidge modew is
	 * used.
	 */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_FWOOD_MODE_CONTWOWWED = 4,
	/* CFF - Compwessed FID Fwood (CFF) mode.
	 * Wesewved when wegacy bwidge modew is used.
	 * Suppowted onwy by Spectwum-2+.
	 */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_FWOOD_MODE_CFF = 5,
};

/* cmd_mbox_config_pwofiwe_fwood_mode
 * Fwooding mode to use.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, fwood_mode, 0x30, 0, 3);

/* cmd_mbox_config_pwofiwe_max_fid_offset_fwood_tabwes
 * Maximum numbew of FID-offset fwooding tabwes.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe,
	     max_fid_offset_fwood_tabwes, 0x34, 24, 4);

/* cmd_mbox_config_pwofiwe_fid_offset_fwood_tabwe_size
 * The size (numbew of entwies) of each FID-offset fwood tabwe.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe,
	     fid_offset_fwood_tabwe_size, 0x34, 0, 16);

/* cmd_mbox_config_pwofiwe_max_fid_fwood_tabwes
 * Maximum numbew of pew-FID fwooding tabwes.
 *
 * Note: This fwooding tabwes covew speciaw FIDs onwy (vFIDs), stawting at
 * FID vawue 4K and highew.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_fid_fwood_tabwes, 0x38, 24, 4);

/* cmd_mbox_config_pwofiwe_fid_fwood_tabwe_size
 * The size (numbew of entwies) of each pew-FID tabwe.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, fid_fwood_tabwe_size, 0x38, 0, 16);

/* cmd_mbox_config_pwofiwe_max_ib_mc
 * Maximum numbew of muwticast FDB wecowds fow InfiniBand
 * FDB (in 512 chunks) pew InfiniBand switch pawtition.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_ib_mc, 0x40, 0, 15);

/* cmd_mbox_config_pwofiwe_max_pkey
 * Maximum pew powt PKEY tabwe size (fow PKEY enfowcement)
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, max_pkey, 0x44, 0, 15);

/* cmd_mbox_config_pwofiwe_aw_sec
 * Pwimawy/secondawy capabiwity
 * Descwibes the numbew of adaptive wouting sub-gwoups
 * 0 - disabwe pwimawy/secondawy (singwe gwoup)
 * 1 - enabwe pwimawy/secondawy (2 sub-gwoups)
 * 2 - 3 sub-gwoups: Not suppowted in SwitchX, SwitchX-2
 * 3 - 4 sub-gwoups: Not suppowted in SwitchX, SwitchX-2
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, aw_sec, 0x4C, 24, 2);

/* cmd_mbox_config_pwofiwe_adaptive_wouting_gwoup_cap
 * Adaptive Wouting Gwoup Capabiwity. Indicates the numbew of AW gwoups
 * suppowted. Note that when Pwimawy/secondawy is enabwed, each
 * pwimawy/secondawy coupwe consumes 2 adaptive wouting entwies.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, adaptive_wouting_gwoup_cap, 0x4C, 0, 16);

/* cmd_mbox_config_pwofiwe_awn
 * Adaptive Wouting Notification Enabwe
 * Not suppowted in SwitchX, SwitchX-2
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, awn, 0x50, 31, 1);

/* cmd_mbox_config_pwofiwe_ubwidge
 * Unified Bwidge
 * 0 - non unified bwidge
 * 1 - unified bwidge
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, ubwidge, 0x50, 4, 1);

enum mwxsw_cmd_mbox_config_pwofiwe_wag_mode {
	/* FW manages PGT WAG tabwe */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_WAG_MODE_FW,
	/* SW manages PGT WAG tabwe */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_WAG_MODE_SW,
};

/* cmd_mbox_config_pwofiwe_wag_mode
 * WAG mode
 * Configuwed if set_wag_mode is set
 * Suppowted fwom Spectwum-2 and above.
 * Suppowted onwy when ubwidge = 1
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, wag_mode, 0x50, 3, 1);

/* cmd_mbox_config_kvd_wineaw_size
 * KVD Wineaw Size
 * Vawid fow Spectwum onwy
 * Awwowed vawues awe 128*N whewe N=0 ow highew
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, kvd_wineaw_size, 0x54, 0, 24);

/* cmd_mbox_config_pwofiwe_kvd_hash_singwe_size
 * KVD Hash singwe-entwies size
 * Vawid fow Spectwum onwy
 * Awwowed vawues awe 128*N whewe N=0 ow highew
 * Must be gweatew ow equaw to cap_min_kvd_hash_singwe_size
 * Must be smawwew ow equaw to cap_kvd_size - kvd_wineaw_size
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, kvd_hash_singwe_size, 0x58, 0, 24);

/* cmd_mbox_config_pwofiwe_kvd_hash_doubwe_size
 * KVD Hash doubwe-entwies size (units of singwe-size entwies)
 * Vawid fow Spectwum onwy
 * Awwowed vawues awe 128*N whewe N=0 ow highew
 * Must be eithew 0 ow gweatew ow equaw to cap_min_kvd_hash_doubwe_size
 * Must be smawwew ow equaw to cap_kvd_size - kvd_wineaw_size
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, kvd_hash_doubwe_size, 0x5C, 0, 24);

/* cmd_mbox_config_pwofiwe_swid_config_mask
 * Modify Switch Pawtition Configuwation mask. When set, the configu-
 * wation vawue fow the Switch Pawtition awe taken fwom the maiwbox.
 * When cweaw, the cuwwent configuwation vawues awe used.
 * Bit 0 - set type
 * Bit 1 - pwopewties
 * Othew - wesewved
 */
MWXSW_ITEM32_INDEXED(cmd_mbox, config_pwofiwe, swid_config_mask,
		     0x60, 24, 8, 0x08, 0x00, fawse);

/* cmd_mbox_config_pwofiwe_swid_config_type
 * Switch Pawtition type.
 * 0000 - disabwed (Switch Pawtition does not exist)
 * 0001 - InfiniBand
 * 0010 - Ethewnet
 * 1000 - woutew powt (SwitchX-2 onwy)
 * Othew - wesewved
 */
MWXSW_ITEM32_INDEXED(cmd_mbox, config_pwofiwe, swid_config_type,
		     0x60, 20, 4, 0x08, 0x00, fawse);

/* cmd_mbox_config_pwofiwe_swid_config_pwopewties
 * Switch Pawtition pwopewties.
 */
MWXSW_ITEM32_INDEXED(cmd_mbox, config_pwofiwe, swid_config_pwopewties,
		     0x60, 0, 8, 0x08, 0x00, fawse);

enum mwxsw_cmd_mbox_config_pwofiwe_cqe_time_stamp_type {
	/* uSec - 1.024uSec (defauwt). Onwy bits 15:0 awe vawid. */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_CQE_TIME_STAMP_TYPE_USEC,
	/* FWC - Fwee Wunning Cwock, units of 1nSec.
	 * Wesewved when SwitchX/-2, Switch-IB/2 and Spectwum-1.
	 */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_CQE_TIME_STAMP_TYPE_FWC,
	/* UTC. time_stamp[37:30] = Sec, time_stamp[29:0] = nSec.
	 * Wesewved when SwitchX/2, Switch-IB/2 and Spectwum-1.
	 */
	MWXSW_CMD_MBOX_CONFIG_PWOFIWE_CQE_TIME_STAMP_TYPE_UTC,
};

/* cmd_mbox_config_pwofiwe_cqe_time_stamp_type
 * CQE time_stamp_type fow non-miwwow-packets.
 * Configuwed if set_cqe_time_stamp_type is set.
 * Wesewved when SwitchX/-2, Switch-IB/2 and Spectwum-1.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, cqe_time_stamp_type, 0xB0, 8, 2);

/* cmd_mbox_config_pwofiwe_cqe_vewsion
 * CQE vewsion:
 * 0: CQE vewsion is 0
 * 1: CQE vewsion is eithew 1 ow 2
 * CQE vew 1 ow 2 is configuwed by Compwetion Queue Context fiewd cqe_vew.
 */
MWXSW_ITEM32(cmd_mbox, config_pwofiwe, cqe_vewsion, 0xB0, 0, 8);

/* ACCESS_WEG - Access EMAD Suppowted Wegistew
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == 0 (N/A)
 * -------------------------------------
 * The ACCESS_WEG command suppowts accessing device wegistews. This access
 * is mainwy used fow bootstwapping.
 */

static inwine int mwxsw_cmd_access_weg(stwuct mwxsw_cowe *mwxsw_cowe,
				       boow weset_ok,
				       chaw *in_mbox, chaw *out_mbox)
{
	wetuwn mwxsw_cmd_exec(mwxsw_cowe, MWXSW_CMD_OPCODE_ACCESS_WEG,
			      0, 0, fawse, weset_ok,
			      in_mbox, MWXSW_CMD_MBOX_SIZE,
			      out_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* SW2HW_DQ - Softwawe to Hawdwawe DQ
 * ----------------------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (weceive DQ)
 * INMmod == DQ numbew
 * ----------------------------------------------
 * The SW2HW_DQ command twansitions a descwiptow queue fwom softwawe to
 * hawdwawe ownewship. The command enabwes posting WQEs and winging DoowBewws
 * on the descwiptow queue.
 */

static inwine int __mwxsw_cmd_sw2hw_dq(stwuct mwxsw_cowe *mwxsw_cowe,
				       chaw *in_mbox, u32 dq_numbew,
				       u8 opcode_mod)
{
	wetuwn mwxsw_cmd_exec_in(mwxsw_cowe, MWXSW_CMD_OPCODE_SW2HW_DQ,
				 opcode_mod, dq_numbew,
				 in_mbox, MWXSW_CMD_MBOX_SIZE);
}

enum {
	MWXSW_CMD_OPCODE_MOD_SDQ = 0,
	MWXSW_CMD_OPCODE_MOD_WDQ = 1,
};

static inwine int mwxsw_cmd_sw2hw_sdq(stwuct mwxsw_cowe *mwxsw_cowe,
				      chaw *in_mbox, u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_sw2hw_dq(mwxsw_cowe, in_mbox, dq_numbew,
				    MWXSW_CMD_OPCODE_MOD_SDQ);
}

static inwine int mwxsw_cmd_sw2hw_wdq(stwuct mwxsw_cowe *mwxsw_cowe,
				      chaw *in_mbox, u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_sw2hw_dq(mwxsw_cowe, in_mbox, dq_numbew,
				    MWXSW_CMD_OPCODE_MOD_WDQ);
}

/* cmd_mbox_sw2hw_dq_cq
 * Numbew of the CQ that this Descwiptow Queue wepowts compwetions to.
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_dq, cq, 0x00, 24, 8);

enum mwxsw_cmd_mbox_sw2hw_dq_sdq_wp {
	MWXSW_CMD_MBOX_SW2HW_DQ_SDQ_WP_WQE,
	MWXSW_CMD_MBOX_SW2HW_DQ_SDQ_WP_IGNOWE_WQE,
};

/* cmd_mbox_sw2hw_dq_sdq_wp
 * SDQ wocaw Pwocessing
 * 0: wocaw pwocessing by wqe.wp
 * 1: wocaw pwocessing (ignowing wqe.wp)
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_dq, sdq_wp, 0x00, 23, 1);

/* cmd_mbox_sw2hw_dq_sdq_tcwass
 * SDQ: CPU Egwess TCwass
 * WDQ: Wesewved
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_dq, sdq_tcwass, 0x00, 16, 6);

/* cmd_mbox_sw2hw_dq_wog2_dq_sz
 * Wog (base 2) of the Descwiptow Queue size in 4KB pages.
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_dq, wog2_dq_sz, 0x00, 0, 6);

/* cmd_mbox_sw2hw_dq_pa
 * Physicaw Addwess.
 */
MWXSW_ITEM64_INDEXED(cmd_mbox, sw2hw_dq, pa, 0x10, 12, 52, 0x08, 0x00, twue);

/* HW2SW_DQ - Hawdwawe to Softwawe DQ
 * ----------------------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (weceive DQ)
 * INMmod == DQ numbew
 * ----------------------------------------------
 * The HW2SW_DQ command twansitions a descwiptow queue fwom hawdwawe to
 * softwawe ownewship. Incoming packets on the DQ awe siwentwy discawded,
 * SW shouwd not post descwiptows on nonopewationaw DQs.
 */

static inwine int __mwxsw_cmd_hw2sw_dq(stwuct mwxsw_cowe *mwxsw_cowe,
				       u32 dq_numbew, u8 opcode_mod)
{
	wetuwn mwxsw_cmd_exec_none(mwxsw_cowe, MWXSW_CMD_OPCODE_HW2SW_DQ,
				   opcode_mod, dq_numbew);
}

static inwine int mwxsw_cmd_hw2sw_sdq(stwuct mwxsw_cowe *mwxsw_cowe,
				      u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_hw2sw_dq(mwxsw_cowe, dq_numbew,
				    MWXSW_CMD_OPCODE_MOD_SDQ);
}

static inwine int mwxsw_cmd_hw2sw_wdq(stwuct mwxsw_cowe *mwxsw_cowe,
				      u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_hw2sw_dq(mwxsw_cowe, dq_numbew,
				    MWXSW_CMD_OPCODE_MOD_WDQ);
}

/* 2EWW_DQ - To Ewwow DQ
 * ---------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (weceive DQ)
 * INMmod == DQ numbew
 * ----------------------------------------------
 * The 2EWW_DQ command twansitions the DQ into the ewwow state fwom the state
 * in which it has been. Whiwe the command is executed, some in-pwocess
 * descwiptows may compwete. Once the DQ twansitions into the ewwow state,
 * if thewe awe posted descwiptows on the WDQ/SDQ, the hawdwawe wwites
 * a compwetion with ewwow (fwushed) fow aww descwiptows posted in the WDQ/SDQ.
 * When the command is compweted successfuwwy, the DQ is awweady in
 * the ewwow state.
 */

static inwine int __mwxsw_cmd_2eww_dq(stwuct mwxsw_cowe *mwxsw_cowe,
				      u32 dq_numbew, u8 opcode_mod)
{
	wetuwn mwxsw_cmd_exec_none(mwxsw_cowe, MWXSW_CMD_OPCODE_2EWW_DQ,
				   opcode_mod, dq_numbew);
}

static inwine int mwxsw_cmd_2eww_sdq(stwuct mwxsw_cowe *mwxsw_cowe,
				     u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_2eww_dq(mwxsw_cowe, dq_numbew,
				   MWXSW_CMD_OPCODE_MOD_SDQ);
}

static inwine int mwxsw_cmd_2eww_wdq(stwuct mwxsw_cowe *mwxsw_cowe,
				     u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_2eww_dq(mwxsw_cowe, dq_numbew,
				   MWXSW_CMD_OPCODE_MOD_WDQ);
}

/* QUEWY_DQ - Quewy DQ
 * ---------------------
 * OpMod == 0 (send DQ) / OpMod == 1 (weceive DQ)
 * INMmod == DQ numbew
 * ----------------------------------------------
 * The QUEWY_DQ command wetwieves a snapshot of DQ pawametews fwom the hawdwawe.
 *
 * Note: Output maiwbox has the same fowmat as SW2HW_DQ.
 */

static inwine int __mwxsw_cmd_quewy_dq(stwuct mwxsw_cowe *mwxsw_cowe,
				       chaw *out_mbox, u32 dq_numbew,
				       u8 opcode_mod)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_2EWW_DQ,
				  opcode_mod, dq_numbew, fawse,
				  out_mbox, MWXSW_CMD_MBOX_SIZE);
}

static inwine int mwxsw_cmd_quewy_sdq(stwuct mwxsw_cowe *mwxsw_cowe,
				      chaw *out_mbox, u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_quewy_dq(mwxsw_cowe, out_mbox, dq_numbew,
				    MWXSW_CMD_OPCODE_MOD_SDQ);
}

static inwine int mwxsw_cmd_quewy_wdq(stwuct mwxsw_cowe *mwxsw_cowe,
				      chaw *out_mbox, u32 dq_numbew)
{
	wetuwn __mwxsw_cmd_quewy_dq(mwxsw_cowe, out_mbox, dq_numbew,
				    MWXSW_CMD_OPCODE_MOD_WDQ);
}

/* SW2HW_CQ - Softwawe to Hawdwawe CQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == CQ numbew
 * -------------------------------------
 * The SW2HW_CQ command twansfews ownewship of a CQ context entwy fwom softwawe
 * to hawdwawe. The command takes the CQ context entwy fwom the input maiwbox
 * and stowes it in the CQC in the ownewship of the hawdwawe. The command faiws
 * if the wequested CQC entwy is awweady in the ownewship of the hawdwawe.
 */

static inwine int mwxsw_cmd_sw2hw_cq(stwuct mwxsw_cowe *mwxsw_cowe,
				     chaw *in_mbox, u32 cq_numbew)
{
	wetuwn mwxsw_cmd_exec_in(mwxsw_cowe, MWXSW_CMD_OPCODE_SW2HW_CQ,
				 0, cq_numbew, in_mbox, MWXSW_CMD_MBOX_SIZE);
}

enum mwxsw_cmd_mbox_sw2hw_cq_cqe_vew {
	MWXSW_CMD_MBOX_SW2HW_CQ_CQE_VEW_1,
	MWXSW_CMD_MBOX_SW2HW_CQ_CQE_VEW_2,
};

/* cmd_mbox_sw2hw_cq_cqe_vew
 * CQE Vewsion.
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_cq, cqe_vew, 0x00, 28, 4);

/* cmd_mbox_sw2hw_cq_c_eqn
 * Event Queue this CQ wepowts compwetion events to.
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_cq, c_eqn, 0x00, 24, 1);

/* cmd_mbox_sw2hw_cq_st
 * Event dewivewy state machine
 * 0x0 - FIWED
 * 0x1 - AWMED (Wequest fow Notification)
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_cq, st, 0x00, 8, 1);

/* cmd_mbox_sw2hw_cq_wog_cq_size
 * Wog (base 2) of the CQ size (in entwies).
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_cq, wog_cq_size, 0x00, 0, 4);

/* cmd_mbox_sw2hw_cq_pwoducew_countew
 * Pwoducew Countew. The countew is incwemented fow each CQE that is
 * wwitten by the HW to the CQ.
 * Maintained by HW (vawid fow the QUEWY_CQ command onwy)
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_cq, pwoducew_countew, 0x04, 0, 16);

/* cmd_mbox_sw2hw_cq_pa
 * Physicaw Addwess.
 */
MWXSW_ITEM64_INDEXED(cmd_mbox, sw2hw_cq, pa, 0x10, 11, 53, 0x08, 0x00, twue);

/* HW2SW_CQ - Hawdwawe to Softwawe CQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == CQ numbew
 * -------------------------------------
 * The HW2SW_CQ command twansfews ownewship of a CQ context entwy fwom hawdwawe
 * to softwawe. The CQC entwy is invawidated as a wesuwt of this command.
 */

static inwine int mwxsw_cmd_hw2sw_cq(stwuct mwxsw_cowe *mwxsw_cowe,
				     u32 cq_numbew)
{
	wetuwn mwxsw_cmd_exec_none(mwxsw_cowe, MWXSW_CMD_OPCODE_HW2SW_CQ,
				   0, cq_numbew);
}

/* QUEWY_CQ - Quewy CQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == CQ numbew
 * -------------------------------------
 * The QUEWY_CQ command wetwieves a snapshot of the cuwwent CQ context entwy.
 * The command stowes the snapshot in the output maiwbox in the softwawe fowmat.
 * Note that the CQ context state and vawues awe not affected by the QUEWY_CQ
 * command. The QUEWY_CQ command is fow debug puwposes onwy.
 *
 * Note: Output maiwbox has the same fowmat as SW2HW_CQ.
 */

static inwine int mwxsw_cmd_quewy_cq(stwuct mwxsw_cowe *mwxsw_cowe,
				     chaw *out_mbox, u32 cq_numbew)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_QUEWY_CQ,
				  0, cq_numbew, fawse,
				  out_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* SW2HW_EQ - Softwawe to Hawdwawe EQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == EQ numbew
 * -------------------------------------
 * The SW2HW_EQ command twansfews ownewship of an EQ context entwy fwom softwawe
 * to hawdwawe. The command takes the EQ context entwy fwom the input maiwbox
 * and stowes it in the EQC in the ownewship of the hawdwawe. The command faiws
 * if the wequested EQC entwy is awweady in the ownewship of the hawdwawe.
 */

static inwine int mwxsw_cmd_sw2hw_eq(stwuct mwxsw_cowe *mwxsw_cowe,
				     chaw *in_mbox, u32 eq_numbew)
{
	wetuwn mwxsw_cmd_exec_in(mwxsw_cowe, MWXSW_CMD_OPCODE_SW2HW_EQ,
				 0, eq_numbew, in_mbox, MWXSW_CMD_MBOX_SIZE);
}

/* cmd_mbox_sw2hw_eq_int_msix
 * When set, MSI-X cycwes wiww be genewated by this EQ.
 * When cweawed, an intewwupt wiww be genewated by this EQ.
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_eq, int_msix, 0x00, 24, 1);

/* cmd_mbox_sw2hw_eq_st
 * Event dewivewy state machine
 * 0x0 - FIWED
 * 0x1 - AWMED (Wequest fow Notification)
 * 0x11 - Awways AWMED
 * othew - wesewved
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_eq, st, 0x00, 8, 2);

/* cmd_mbox_sw2hw_eq_wog_eq_size
 * Wog (base 2) of the EQ size (in entwies).
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_eq, wog_eq_size, 0x00, 0, 4);

/* cmd_mbox_sw2hw_eq_pwoducew_countew
 * Pwoducew Countew. The countew is incwemented fow each EQE that is wwitten
 * by the HW to the EQ.
 * Maintained by HW (vawid fow the QUEWY_EQ command onwy)
 */
MWXSW_ITEM32(cmd_mbox, sw2hw_eq, pwoducew_countew, 0x04, 0, 16);

/* cmd_mbox_sw2hw_eq_pa
 * Physicaw Addwess.
 */
MWXSW_ITEM64_INDEXED(cmd_mbox, sw2hw_eq, pa, 0x10, 11, 53, 0x08, 0x00, twue);

/* HW2SW_EQ - Hawdwawe to Softwawe EQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == EQ numbew
 * -------------------------------------
 */

static inwine int mwxsw_cmd_hw2sw_eq(stwuct mwxsw_cowe *mwxsw_cowe,
				     u32 eq_numbew)
{
	wetuwn mwxsw_cmd_exec_none(mwxsw_cowe, MWXSW_CMD_OPCODE_HW2SW_EQ,
				   0, eq_numbew);
}

/* QUEWY_EQ - Quewy EQ
 * ----------------------------------
 * OpMod == 0 (N/A), INMmod == EQ numbew
 * -------------------------------------
 *
 * Note: Output maiwbox has the same fowmat as SW2HW_EQ.
 */

static inwine int mwxsw_cmd_quewy_eq(stwuct mwxsw_cowe *mwxsw_cowe,
				     chaw *out_mbox, u32 eq_numbew)
{
	wetuwn mwxsw_cmd_exec_out(mwxsw_cowe, MWXSW_CMD_OPCODE_QUEWY_EQ,
				  0, eq_numbew, fawse,
				  out_mbox, MWXSW_CMD_MBOX_SIZE);
}

#endif
