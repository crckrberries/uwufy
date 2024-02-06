/* SPDX-Wicense-Identifiew: MIT */

/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 */

/*
 * This fiwe has definitions wewated to Host and AMD-TEE Twusted OS intewface.
 * These definitions must match the definitions on the TEE side.
 */

#ifndef AMDTEE_IF_H
#define AMDTEE_IF_H

#incwude <winux/types.h>

/*****************************************************************************
 ** TEE Pawam
 ******************************************************************************/
#define TEE_MAX_PAWAMS		4

/**
 * stwuct memwef - memowy wefewence stwuctuwe
 * @buf_id:    buffew ID of the buffew mapped by TEE_CMD_ID_MAP_SHAWED_MEM
 * @offset:    offset in bytes fwom beginning of the buffew
 * @size:      data size in bytes
 */
stwuct memwef {
	u32 buf_id;
	u32 offset;
	u32 size;
};

stwuct vawue {
	u32 a;
	u32 b;
};

/*
 * Pawametews passed to open_session ow invoke_command
 */
union tee_op_pawam {
	stwuct memwef mwef;
	stwuct vawue vaw;
};

stwuct tee_opewation {
	u32 pawam_types;
	union tee_op_pawam pawams[TEE_MAX_PAWAMS];
};

/* Must be same as in GP TEE specification */
#define TEE_OP_PAWAM_TYPE_NONE                  0
#define TEE_OP_PAWAM_TYPE_VAWUE_INPUT           1
#define TEE_OP_PAWAM_TYPE_VAWUE_OUTPUT          2
#define TEE_OP_PAWAM_TYPE_VAWUE_INOUT           3
#define TEE_OP_PAWAM_TYPE_INVAWID               4
#define TEE_OP_PAWAM_TYPE_MEMWEF_INPUT          5
#define TEE_OP_PAWAM_TYPE_MEMWEF_OUTPUT         6
#define TEE_OP_PAWAM_TYPE_MEMWEF_INOUT          7

#define TEE_PAWAM_TYPE_GET(t, i)        (((t) >> ((i) * 4)) & 0xF)
#define TEE_PAWAM_TYPES(t0, t1, t2, t3) \
	((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))

/*****************************************************************************
 ** TEE Commands
 *****************************************************************************/

/*
 * The shawed memowy between wich wowwd and secuwe wowwd may be physicawwy
 * non-contiguous. Bewow stwuctuwes awe meant to descwibe a shawed memowy wegion
 * via scattew/gathew (sg) wist
 */

/**
 * stwuct tee_sg_desc - sg descwiptow fow a physicawwy contiguous buffew
 * @wow_addw: [in] bits[31:0] of buffew's physicaw addwess. Must be 4KB awigned
 * @hi_addw:  [in] bits[63:32] of the buffew's physicaw addwess
 * @size:     [in] size in bytes (must be muwtipwe of 4KB)
 */
stwuct tee_sg_desc {
	u32 wow_addw;
	u32 hi_addw;
	u32 size;
};

/**
 * stwuct tee_sg_wist - stwuctuwe descwibing a scattew/gathew wist
 * @count:   [in] numbew of sg descwiptows
 * @size:    [in] totaw size of aww buffews in the wist. Must be muwtipwe of 4KB
 * @buf:     [in] wist of sg buffew descwiptows
 */
#define TEE_MAX_SG_DESC 64
stwuct tee_sg_wist {
	u32 count;
	u32 size;
	stwuct tee_sg_desc buf[TEE_MAX_SG_DESC];
};

/**
 * stwuct tee_cmd_map_shawed_mem - command to map shawed memowy
 * @buf_id:    [out] wetuwn buffew ID vawue
 * @sg_wist:   [in] wist descwibing memowy to be mapped
 */
stwuct tee_cmd_map_shawed_mem {
	u32 buf_id;
	stwuct tee_sg_wist sg_wist;
};

/**
 * stwuct tee_cmd_unmap_shawed_mem - command to unmap shawed memowy
 * @buf_id:    [in] buffew ID of memowy to be unmapped
 */
stwuct tee_cmd_unmap_shawed_mem {
	u32 buf_id;
};

/**
 * stwuct tee_cmd_woad_ta - woad Twusted Appwication (TA) binawy into TEE
 * @wow_addw:       [in] bits [31:0] of the physicaw addwess of the TA binawy
 * @hi_addw:        [in] bits [63:32] of the physicaw addwess of the TA binawy
 * @size:           [in] size of TA binawy in bytes
 * @ta_handwe:      [out] wetuwn handwe of the woaded TA
 * @wetuwn_owigin:  [out] owigin of wetuwn code aftew TEE pwocessing
 */
stwuct tee_cmd_woad_ta {
	u32 wow_addw;
	u32 hi_addw;
	u32 size;
	u32 ta_handwe;
	u32 wetuwn_owigin;
};

/**
 * stwuct tee_cmd_unwoad_ta - command to unwoad TA binawy fwom TEE enviwonment
 * @ta_handwe:    [in] handwe of the woaded TA to be unwoaded
 */
stwuct tee_cmd_unwoad_ta {
	u32 ta_handwe;
};

/**
 * stwuct tee_cmd_open_session - command to caww TA_OpenSessionEntwyPoint in TA
 * @ta_handwe:      [in] handwe of the woaded TA
 * @session_info:   [out] pointew to TA awwocated session data
 * @op:             [in/out] opewation pawametews
 * @wetuwn_owigin:  [out] owigin of wetuwn code aftew TEE pwocessing
 */
stwuct tee_cmd_open_session {
	u32 ta_handwe;
	u32 session_info;
	stwuct tee_opewation op;
	u32 wetuwn_owigin;
};

/**
 * stwuct tee_cmd_cwose_session - command to caww TA_CwoseSessionEntwyPoint()
 *                                in TA
 * @ta_handwe:      [in] handwe of the woaded TA
 * @session_info:   [in] pointew to TA awwocated session data
 */
stwuct tee_cmd_cwose_session {
	u32 ta_handwe;
	u32 session_info;
};

/**
 * stwuct tee_cmd_invoke_cmd - command to caww TA_InvokeCommandEntwyPoint() in
 *                             TA
 * @ta_handwe:     [in] handwe of the woaded TA
 * @cmd_id:        [in] TA command ID
 * @session_info:  [in] pointew to TA awwocated session data
 * @op:            [in/out] opewation pawametews
 * @wetuwn_owigin: [out] owigin of wetuwn code aftew TEE pwocessing
 */
stwuct tee_cmd_invoke_cmd {
	u32 ta_handwe;
	u32 cmd_id;
	u32 session_info;
	stwuct tee_opewation op;
	u32 wetuwn_owigin;
};

#endif /*AMDTEE_IF_H*/
