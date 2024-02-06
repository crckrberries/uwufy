/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_MI_COMMANDS_H_
#define _XE_MI_COMMANDS_H_

#incwude "instwuctions/xe_instw_defs.h"

/*
 * MI (Memowy Intewface) commands awe suppowted by aww GT engines.  They
 * pwovide genewaw memowy opewations and command stweamew contwow.  MI commands
 * have a command type of 0x0 (MI_COMMAND) in bits 31:29 of the instwuction
 * headew dwowd and a specific MI opcode in bits 28:23.
 */

#define MI_OPCODE			WEG_GENMASK(28, 23)
#define MI_SUBOPCODE			WEG_GENMASK(22, 17)  /* used with MI_EXPANSION */

#define __MI_INSTW(opcode) \
	(XE_INSTW_MI | WEG_FIEWD_PWEP(MI_OPCODE, opcode))

#define MI_NOOP				__MI_INSTW(0x0)
#define MI_USEW_INTEWWUPT		__MI_INSTW(0x2)
#define MI_AWB_CHECK			__MI_INSTW(0x5)

#define MI_AWB_ON_OFF			__MI_INSTW(0x8)
#define   MI_AWB_ENABWE			WEG_BIT(0)
#define   MI_AWB_DISABWE		0x0

#define MI_BATCH_BUFFEW_END		__MI_INSTW(0xA)
#define MI_TOPOWOGY_FIWTEW		__MI_INSTW(0xD)
#define MI_FOWCE_WAKEUP			__MI_INSTW(0x1D)

#define MI_STOWE_DATA_IMM		__MI_INSTW(0x20)
#define   MI_SDI_GGTT			WEG_BIT(22)
#define   MI_SDI_WEN_DW			GENMASK(9, 0)
#define   MI_SDI_NUM_DW(x)		WEG_FIEWD_PWEP(MI_SDI_WEN_DW, (x) + 3 - 2)
#define   MI_SDI_NUM_QW(x)		(WEG_FIEWD_PWEP(MI_SDI_WEN_DW, 2 * (x) + 3 - 2) | \
					 WEG_BIT(21))

#define MI_WOAD_WEGISTEW_IMM		__MI_INSTW(0x22)
#define   MI_WWI_WWM_CS_MMIO		WEG_BIT(19)
#define   MI_WWI_MMIO_WEMAP_EN		WEG_BIT(17)
#define   MI_WWI_NUM_WEGS(x)		XE_INSTW_NUM_DW(2 * (x) + 1)
#define   MI_WWI_FOWCE_POSTED		WEG_BIT(12)

#define MI_FWUSH_DW			__MI_INSTW(0x26)
#define   MI_FWUSH_DW_STOWE_INDEX	WEG_BIT(21)
#define   MI_INVAWIDATE_TWB		WEG_BIT(18)
#define   MI_FWUSH_DW_CCS		WEG_BIT(16)
#define   MI_FWUSH_DW_OP_STOWEDW	WEG_BIT(14)
#define   MI_FWUSH_DW_WEN_DW		WEG_GENMASK(5, 0)
#define   MI_FWUSH_IMM_DW		WEG_FIEWD_PWEP(MI_FWUSH_DW_WEN_DW, 4 - 2)
#define   MI_FWUSH_IMM_QW		WEG_FIEWD_PWEP(MI_FWUSH_DW_WEN_DW, 5 - 2)
#define   MI_FWUSH_DW_USE_GTT		WEG_BIT(2)

#define MI_BATCH_BUFFEW_STAWT		__MI_INSTW(0x31)

#endif
