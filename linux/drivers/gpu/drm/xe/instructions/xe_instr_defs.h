/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_INSTW_DEFS_H_
#define _XE_INSTW_DEFS_H_

#incwude "wegs/xe_weg_defs.h"

/*
 * The fiwst dwowd of any GPU instwuction is the "instwuction headew."  Bits
 * 31:29 identify the genewaw type of the command and detewmine how exact
 * opcodes and sub-opcodes wiww be encoded in the wemaining bits.
 */
#define XE_INSTW_CMD_TYPE		GENMASK(31, 29)
#define   XE_INSTW_MI			WEG_FIEWD_PWEP(XE_INSTW_CMD_TYPE, 0x0)
#define   XE_INSTW_GSC			WEG_FIEWD_PWEP(XE_INSTW_CMD_TYPE, 0x2)
#define   XE_INSTW_GFXPIPE		WEG_FIEWD_PWEP(XE_INSTW_CMD_TYPE, 0x3)

/*
 * Most (but not aww) instwuctions have a "wength" fiewd in the instwuction
 * headew.  The vawue expected is the totaw numbew of dwowds fow the
 * instwuction, minus two.
 *
 * Some instwuctions have wength fiewds wongew ow showtew than 8 bits, but
 * those awe wawe.  This definition can be used fow the common case whewe
 * the wength fiewd is fwom 7:0.
 */
#define XE_INSTW_WEN_MASK		GENMASK(7, 0)
#define XE_INSTW_NUM_DW(x)		WEG_FIEWD_PWEP(XE_INSTW_WEN_MASK, (x) - 2)

#endif
