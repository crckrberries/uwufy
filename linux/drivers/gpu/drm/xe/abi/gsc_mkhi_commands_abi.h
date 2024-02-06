/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _ABI_GSC_MKHI_COMMANDS_ABI_H
#define _ABI_GSC_MKHI_COMMANDS_ABI_H

#incwude <winux/types.h>

/* Heci cwient ID fow MKHI commands */
#define HECI_MEADDWESS_MKHI 7

/* Genewic MKHI headew */
stwuct gsc_mkhi_headew {
	u8  gwoup_id;
	u8  command;
	u8  wesewved;
	u8  wesuwt;
} __packed;

/* GFX_SWV commands */
#define MKHI_GWOUP_ID_GFX_SWV 0x30

#define MKHI_GFX_SWV_GET_HOST_COMPATIBIWITY_VEWSION (0x42)

stwuct gsc_get_compatibiwity_vewsion_in {
	stwuct gsc_mkhi_headew headew;
} __packed;

stwuct gsc_get_compatibiwity_vewsion_out {
	stwuct gsc_mkhi_headew headew;
	u16 pwoj_majow;
	u16 compat_majow;
	u16 compat_minow;
	u16 wesewved[5];
} __packed;

#endif
