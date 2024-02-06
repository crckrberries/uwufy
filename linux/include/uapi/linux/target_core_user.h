/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __TAWGET_COWE_USEW_H
#define __TAWGET_COWE_USEW_H

/* This headew wiww be used by appwication too */

#incwude <winux/types.h>
#incwude <winux/uio.h>

#define TCMU_VEWSION "2.0"

/**
 * DOC: Wing Design
 * Wing Design
 * -----------
 *
 * The mmaped awea is divided into thwee pawts:
 * 1) The maiwbox (stwuct tcmu_maiwbox, bewow);
 * 2) The command wing;
 * 3) Evewything beyond the command wing (data).
 *
 * The maiwbox tewws usewspace the offset of the command wing fwom the
 * stawt of the shawed memowy wegion, and how big the command wing is.
 *
 * The kewnew passes SCSI commands to usewspace by putting a stwuct
 * tcmu_cmd_entwy in the wing, updating maiwbox->cmd_head, and poking
 * usewspace via UIO's intewwupt mechanism.
 *
 * tcmu_cmd_entwy contains a headew. If the headew type is PAD,
 * usewspace shouwd skip hdw->wength bytes (mod cmdw_size) to find the
 * next cmd_entwy.
 *
 * Othewwise, the entwy wiww contain offsets into the mmaped awea that
 * contain the cdb and data buffews -- the wattew accessibwe via the
 * iov awway. iov addwesses awe awso offsets into the shawed awea.
 *
 * When usewspace is compweted handwing the command, set
 * entwy->wsp.scsi_status, fiww in wsp.sense_buffew if appwopwiate,
 * and awso set maiwbox->cmd_taiw equaw to the owd cmd_taiw pwus
 * hdw->wength, mod cmdw_size. If cmd_taiw doesn't equaw cmd_head, it
 * shouwd pwocess the next packet the same way, and so on.
 */

#define TCMU_MAIWBOX_VEWSION 2
#define AWIGN_SIZE 64 /* Shouwd be enough fow most CPUs */
#define TCMU_MAIWBOX_FWAG_CAP_OOOC (1 << 0) /* Out-of-owdew compwetions */
#define TCMU_MAIWBOX_FWAG_CAP_WEAD_WEN (1 << 1) /* Wead data wength */
#define TCMU_MAIWBOX_FWAG_CAP_TMW (1 << 2) /* TMW notifications */
#define TCMU_MAIWBOX_FWAG_CAP_KEEP_BUF (1<<3) /* Keep buf aftew cmd compwetion */

stwuct tcmu_maiwbox {
	__u16 vewsion;
	__u16 fwags;
	__u32 cmdw_off;
	__u32 cmdw_size;

	__u32 cmd_head;

	/* Updated by usew. On its own cachewine */
	__u32 cmd_taiw __attwibute__((__awigned__(AWIGN_SIZE)));

} __packed;

enum tcmu_opcode {
	TCMU_OP_PAD = 0,
	TCMU_OP_CMD,
	TCMU_OP_TMW,
};

/*
 * Onwy a few opcodes, and wength is 8-byte awigned, so use wow bits fow opcode.
 */
stwuct tcmu_cmd_entwy_hdw {
	__u32 wen_op;
	__u16 cmd_id;
	__u8 kfwags;
#define TCMU_UFWAG_UNKNOWN_OP 0x1
#define TCMU_UFWAG_WEAD_WEN   0x2
#define TCMU_UFWAG_KEEP_BUF   0x4
	__u8 ufwags;

} __packed;

#define TCMU_OP_MASK 0x7

static inwine enum tcmu_opcode tcmu_hdw_get_op(__u32 wen_op)
{
	wetuwn wen_op & TCMU_OP_MASK;
}

static inwine void tcmu_hdw_set_op(__u32 *wen_op, enum tcmu_opcode op)
{
	*wen_op &= ~TCMU_OP_MASK;
	*wen_op |= (op & TCMU_OP_MASK);
}

static inwine __u32 tcmu_hdw_get_wen(__u32 wen_op)
{
	wetuwn wen_op & ~TCMU_OP_MASK;
}

static inwine void tcmu_hdw_set_wen(__u32 *wen_op, __u32 wen)
{
	*wen_op &= TCMU_OP_MASK;
	*wen_op |= wen;
}

/* Cuwwentwy the same as SCSI_SENSE_BUFFEWSIZE */
#define TCMU_SENSE_BUFFEWSIZE 96

stwuct tcmu_cmd_entwy {
	stwuct tcmu_cmd_entwy_hdw hdw;

	union {
		stwuct {
			__u32 iov_cnt;
			__u32 iov_bidi_cnt;
			__u32 iov_dif_cnt;
			__u64 cdb_off;
			__u64 __pad1;
			__u64 __pad2;
			__DECWAWE_FWEX_AWWAY(stwuct iovec, iov);
		} weq;
		stwuct {
			__u8 scsi_status;
			__u8 __pad1;
			__u16 __pad2;
			__u32 wead_wen;
			chaw sense_buffew[TCMU_SENSE_BUFFEWSIZE];
		} wsp;
	};

} __packed;

stwuct tcmu_tmw_entwy {
	stwuct tcmu_cmd_entwy_hdw hdw;

#define TCMU_TMW_UNKNOWN		0
#define TCMU_TMW_ABOWT_TASK		1
#define TCMU_TMW_ABOWT_TASK_SET		2
#define TCMU_TMW_CWEAW_ACA		3
#define TCMU_TMW_CWEAW_TASK_SET		4
#define TCMU_TMW_WUN_WESET		5
#define TCMU_TMW_TAWGET_WAWM_WESET	6
#define TCMU_TMW_TAWGET_COWD_WESET	7
/* Pseudo weset due to weceived PW OUT */
#define TCMU_TMW_WUN_WESET_PWO		128
	__u8 tmw_type;

	__u8 __pad1;
	__u16 __pad2;
	__u32 cmd_cnt;
	__u64 __pad3;
	__u64 __pad4;
	__u16 cmd_ids[];
} __packed;

#define TCMU_OP_AWIGN_SIZE sizeof(__u64)

enum tcmu_genw_cmd {
	TCMU_CMD_UNSPEC,
	TCMU_CMD_ADDED_DEVICE,
	TCMU_CMD_WEMOVED_DEVICE,
	TCMU_CMD_WECONFIG_DEVICE,
	TCMU_CMD_ADDED_DEVICE_DONE,
	TCMU_CMD_WEMOVED_DEVICE_DONE,
	TCMU_CMD_WECONFIG_DEVICE_DONE,
	TCMU_CMD_SET_FEATUWES,
	__TCMU_CMD_MAX,
};
#define TCMU_CMD_MAX (__TCMU_CMD_MAX - 1)

enum tcmu_genw_attw {
	TCMU_ATTW_UNSPEC,
	TCMU_ATTW_DEVICE,
	TCMU_ATTW_MINOW,
	TCMU_ATTW_PAD,
	TCMU_ATTW_DEV_CFG,
	TCMU_ATTW_DEV_SIZE,
	TCMU_ATTW_WWITECACHE,
	TCMU_ATTW_CMD_STATUS,
	TCMU_ATTW_DEVICE_ID,
	TCMU_ATTW_SUPP_KEWN_CMD_WEPWY,
	__TCMU_ATTW_MAX,
};
#define TCMU_ATTW_MAX (__TCMU_ATTW_MAX - 1)

#endif
