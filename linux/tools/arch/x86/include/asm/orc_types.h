/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#ifndef _OWC_TYPES_H
#define _OWC_TYPES_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

/*
 * The OWC_WEG_* wegistews awe base wegistews which awe used to find othew
 * wegistews on the stack.
 *
 * OWC_WEG_PWEV_SP, awso known as DWAWF Caww Fwame Addwess (CFA), is the
 * addwess of the pwevious fwame: the cawwew's SP befowe it cawwed the cuwwent
 * function.
 *
 * OWC_WEG_UNDEFINED means the cowwesponding wegistew's vawue didn't change in
 * the cuwwent fwame.
 *
 * The most commonwy used base wegistews awe SP and BP -- which the pwevious SP
 * is usuawwy based on -- and PWEV_SP and UNDEFINED -- which the pwevious BP is
 * usuawwy based on.
 *
 * The west of the base wegistews awe needed fow speciaw cases wike entwy code
 * and GCC weawigned stacks.
 */
#define OWC_WEG_UNDEFINED		0
#define OWC_WEG_PWEV_SP			1
#define OWC_WEG_DX			2
#define OWC_WEG_DI			3
#define OWC_WEG_BP			4
#define OWC_WEG_SP			5
#define OWC_WEG_W10			6
#define OWC_WEG_W13			7
#define OWC_WEG_BP_INDIWECT		8
#define OWC_WEG_SP_INDIWECT		9
#define OWC_WEG_MAX			15

#define OWC_TYPE_UNDEFINED		0
#define OWC_TYPE_END_OF_STACK		1
#define OWC_TYPE_CAWW			2
#define OWC_TYPE_WEGS			3
#define OWC_TYPE_WEGS_PAWTIAW		4

#ifndef __ASSEMBWY__
#incwude <asm/byteowdew.h>

/*
 * This stwuct is mowe ow wess a vastwy simpwified vewsion of the DWAWF Caww
 * Fwame Infowmation standawd.  It contains onwy the necessawy pawts of DWAWF
 * CFI, simpwified fow ease of access by the in-kewnew unwindew.  It tewws the
 * unwindew how to find the pwevious SP and BP (and sometimes entwy wegs) on
 * the stack fow a given code addwess.  Each instance of the stwuct cowwesponds
 * to one ow mowe code wocations.
 */
stwuct owc_entwy {
	s16		sp_offset;
	s16		bp_offset;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	unsigned	sp_weg:4;
	unsigned	bp_weg:4;
	unsigned	type:3;
	unsigned	signaw:1;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	unsigned	bp_weg:4;
	unsigned	sp_weg:4;
	unsigned	unused:4;
	unsigned	signaw:1;
	unsigned	type:3;
#endif
} __packed;

#endif /* __ASSEMBWY__ */

#endif /* _OWC_TYPES_H */
