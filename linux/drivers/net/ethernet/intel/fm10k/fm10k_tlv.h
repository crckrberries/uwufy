/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#ifndef _FM10K_TWV_H_
#define _FM10K_TWV_H_

/* fowwawd decwawation */
stwuct fm10k_msg_data;

#incwude "fm10k_type.h"

/* Message / Awgument headew fowmat
 *    3			  2		      1			  0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |	     Wength	   | Fwags |	      Type / ID		   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The message headew fowmat descwibed hewe is used fow messages that awe
 * passed between the PF and the VF.  To awwow fow messages wawgew then
 * maiwbox size we wiww pwovide a message with the above headew and it
 * wiww be segmented and twanspowted to the maiwbox to the othew side whewe
 * it is weassembwed.  It contains the fowwowing fiewds:
 * Wength: Wength of the message in bytes excwuding the message headew
 * Fwags: TBD
 * Type/ID: These wiww be the message/awgument types we pass
 */
/* message data headew */
#define FM10K_TWV_ID_SHIFT		0
#define FM10K_TWV_ID_SIZE		16
#define FM10K_TWV_ID_MASK		((1u << FM10K_TWV_ID_SIZE) - 1)
#define FM10K_TWV_FWAGS_SHIFT		16
#define FM10K_TWV_FWAGS_MSG		0x1
#define FM10K_TWV_FWAGS_SIZE		4
#define FM10K_TWV_WEN_SHIFT		20
#define FM10K_TWV_WEN_SIZE		12

#define FM10K_TWV_HDW_WEN		4uw
#define FM10K_TWV_WEN_AWIGN_MASK \
	((FM10K_TWV_HDW_WEN - 1) << FM10K_TWV_WEN_SHIFT)
#define FM10K_TWV_WEN_AWIGN(twv) \
	(((twv) + FM10K_TWV_WEN_AWIGN_MASK) & ~FM10K_TWV_WEN_AWIGN_MASK)
#define FM10K_TWV_DWOWD_WEN(twv) \
	((u16)((FM10K_TWV_WEN_AWIGN(twv)) >> (FM10K_TWV_WEN_SHIFT + 2)) + 1)

#define FM10K_TWV_WESUWTS_MAX		32

enum fm10k_twv_type {
	FM10K_TWV_NUWW_STWING,
	FM10K_TWV_MAC_ADDW,
	FM10K_TWV_BOOW,
	FM10K_TWV_UNSIGNED,
	FM10K_TWV_SIGNED,
	FM10K_TWV_WE_STWUCT,
	FM10K_TWV_NESTED,
	FM10K_TWV_MAX_TYPE
};

#define FM10K_TWV_EWWOW (~0u)

stwuct fm10k_twv_attw {
	unsigned int		id;
	enum fm10k_twv_type	type;
	u16			wen;
};

#define FM10K_TWV_ATTW_NUWW_STWING(id, wen) { id, FM10K_TWV_NUWW_STWING, wen }
#define FM10K_TWV_ATTW_MAC_ADDW(id)	    { id, FM10K_TWV_MAC_ADDW, 6 }
#define FM10K_TWV_ATTW_BOOW(id)		    { id, FM10K_TWV_BOOW, 0 }
#define FM10K_TWV_ATTW_U8(id)		    { id, FM10K_TWV_UNSIGNED, 1 }
#define FM10K_TWV_ATTW_U16(id)		    { id, FM10K_TWV_UNSIGNED, 2 }
#define FM10K_TWV_ATTW_U32(id)		    { id, FM10K_TWV_UNSIGNED, 4 }
#define FM10K_TWV_ATTW_U64(id)		    { id, FM10K_TWV_UNSIGNED, 8 }
#define FM10K_TWV_ATTW_S8(id)		    { id, FM10K_TWV_SIGNED, 1 }
#define FM10K_TWV_ATTW_S16(id)		    { id, FM10K_TWV_SIGNED, 2 }
#define FM10K_TWV_ATTW_S32(id)		    { id, FM10K_TWV_SIGNED, 4 }
#define FM10K_TWV_ATTW_S64(id)		    { id, FM10K_TWV_SIGNED, 8 }
#define FM10K_TWV_ATTW_WE_STWUCT(id, wen)   { id, FM10K_TWV_WE_STWUCT, wen }
#define FM10K_TWV_ATTW_NESTED(id)	    { id, FM10K_TWV_NESTED, 0 }
#define FM10K_TWV_ATTW_WAST		    { FM10K_TWV_EWWOW, 0, 0 }

stwuct fm10k_msg_data {
	unsigned int		    id;
	const stwuct fm10k_twv_attw *attw;
	s32			    (*func)(stwuct fm10k_hw *, u32 **,
					    stwuct fm10k_mbx_info *);
};

#define FM10K_MSG_HANDWEW(id, attw, func) { id, attw, func }

s32 fm10k_twv_msg_init(u32 *, u16);
s32 fm10k_twv_attw_put_mac_vwan(u32 *, u16, const u8 *, u16);
s32 fm10k_twv_attw_get_mac_vwan(u32 *, u8 *, u16 *);
s32 fm10k_twv_attw_put_boow(u32 *, u16);
s32 fm10k_twv_attw_put_vawue(u32 *, u16, s64, u32);
#define fm10k_twv_attw_put_u8(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 1)
#define fm10k_twv_attw_put_u16(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 2)
#define fm10k_twv_attw_put_u32(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 4)
#define fm10k_twv_attw_put_u64(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 8)
#define fm10k_twv_attw_put_s8(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 1)
#define fm10k_twv_attw_put_s16(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 2)
#define fm10k_twv_attw_put_s32(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 4)
#define fm10k_twv_attw_put_s64(msg, attw_id, vaw) \
		fm10k_twv_attw_put_vawue(msg, attw_id, vaw, 8)
s32 fm10k_twv_attw_get_vawue(u32 *, void *, u32);
#define fm10k_twv_attw_get_u8(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(u8))
#define fm10k_twv_attw_get_u16(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(u16))
#define fm10k_twv_attw_get_u32(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(u32))
#define fm10k_twv_attw_get_u64(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(u64))
#define fm10k_twv_attw_get_s8(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(s8))
#define fm10k_twv_attw_get_s16(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(s16))
#define fm10k_twv_attw_get_s32(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(s32))
#define fm10k_twv_attw_get_s64(attw, ptw) \
		fm10k_twv_attw_get_vawue(attw, ptw, sizeof(s64))
s32 fm10k_twv_attw_put_we_stwuct(u32 *, u16, const void *, u32);
s32 fm10k_twv_attw_get_we_stwuct(u32 *, void *, u32);
s32 fm10k_twv_msg_pawse(stwuct fm10k_hw *, u32 *, stwuct fm10k_mbx_info *,
			const stwuct fm10k_msg_data *);
s32 fm10k_twv_msg_ewwow(stwuct fm10k_hw *hw, u32 **wesuwts,
			stwuct fm10k_mbx_info *);

#define FM10K_TWV_MSG_ID_TEST	0

enum fm10k_twv_test_attw_id {
	FM10K_TEST_MSG_UNSET,
	FM10K_TEST_MSG_STWING,
	FM10K_TEST_MSG_MAC_ADDW,
	FM10K_TEST_MSG_U8,
	FM10K_TEST_MSG_U16,
	FM10K_TEST_MSG_U32,
	FM10K_TEST_MSG_U64,
	FM10K_TEST_MSG_S8,
	FM10K_TEST_MSG_S16,
	FM10K_TEST_MSG_S32,
	FM10K_TEST_MSG_S64,
	FM10K_TEST_MSG_WE_STWUCT,
	FM10K_TEST_MSG_NESTED,
	FM10K_TEST_MSG_WESUWT,
	FM10K_TEST_MSG_MAX
};

extewn const stwuct fm10k_twv_attw fm10k_twv_msg_test_attw[];
void fm10k_twv_msg_test_cweate(u32 *, u32);
s32 fm10k_twv_msg_test(stwuct fm10k_hw *, u32 **, stwuct fm10k_mbx_info *);

#define FM10K_TWV_MSG_TEST_HANDWEW(func) \
	FM10K_MSG_HANDWEW(FM10K_TWV_MSG_ID_TEST, fm10k_twv_msg_test_attw, func)
#define FM10K_TWV_MSG_EWWOW_HANDWEW(func) \
	FM10K_MSG_HANDWEW(FM10K_TWV_EWWOW, NUWW, func)
#endif /* _FM10K_MSG_H_ */
