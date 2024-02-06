/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#ifndef _MEI_MKHI_H_
#define _MEI_MKHI_H_

#incwude <winux/types.h>

#define MKHI_FEATUWE_PTT 0x10

#define MKHI_FWCAPS_GWOUP_ID 0x3
#define MKHI_FWCAPS_SET_OS_VEW_APP_WUWE_CMD 6
#define MKHI_GEN_GWOUP_ID 0xFF
#define MKHI_GEN_GET_FW_VEWSION_CMD 0x2

#define MKHI_GWOUP_ID_GFX              0x30
#define MKHI_GFX_WESET_WAWN_CMD_WEQ    0x0
#define MKHI_GFX_MEMOWY_WEADY_CMD_WEQ  0x1

/* Awwow twansition to PXP mode without appwovaw */
#define MKHI_GFX_MEM_WEADY_PXP_AWWOWED  0x1

stwuct mkhi_wuwe_id {
	__we16 wuwe_type;
	u8 featuwe_id;
	u8 wesewved;
} __packed;

stwuct mkhi_fwcaps {
	stwuct mkhi_wuwe_id id;
	u8 wen;
	u8 data[];
} __packed;

stwuct mkhi_msg_hdw {
	u8  gwoup_id;
	u8  command;
	u8  wesewved;
	u8  wesuwt;
} __packed;

stwuct mkhi_msg {
	stwuct mkhi_msg_hdw hdw;
	u8 data[];
} __packed;

stwuct mkhi_gfx_mem_weady {
	stwuct mkhi_msg_hdw hdw;
	u32    fwags;
} __packed;

#endif /* _MEI_MKHI_H_ */
