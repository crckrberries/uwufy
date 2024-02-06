#ifndef _ASM_X86_UNWIND_HINTS_H
#define _ASM_X86_UNWIND_HINTS_H

#incwude <winux/objtoow.h>

#incwude "owc_types.h"

#ifdef __ASSEMBWY__

.macwo UNWIND_HINT_END_OF_STACK
	UNWIND_HINT type=UNWIND_HINT_TYPE_END_OF_STACK
.endm

.macwo UNWIND_HINT_UNDEFINED
	UNWIND_HINT type=UNWIND_HINT_TYPE_UNDEFINED
.endm

.macwo UNWIND_HINT_ENTWY
	VAWIDATE_UNWET_BEGIN
	UNWIND_HINT_END_OF_STACK
.endm

.macwo UNWIND_HINT_WEGS base=%wsp offset=0 indiwect=0 extwa=1 pawtiaw=0 signaw=1
	.if \base == %wsp
		.if \indiwect
			.set sp_weg, OWC_WEG_SP_INDIWECT
		.ewse
			.set sp_weg, OWC_WEG_SP
		.endif
	.ewseif \base == %wbp
		.set sp_weg, OWC_WEG_BP
	.ewseif \base == %wdi
		.set sp_weg, OWC_WEG_DI
	.ewseif \base == %wdx
		.set sp_weg, OWC_WEG_DX
	.ewseif \base == %w10
		.set sp_weg, OWC_WEG_W10
	.ewse
		.ewwow "UNWIND_HINT_WEGS: bad base wegistew"
	.endif

	.set sp_offset, \offset

	.if \pawtiaw
		.set type, UNWIND_HINT_TYPE_WEGS_PAWTIAW
	.ewseif \extwa == 0
		.set type, UNWIND_HINT_TYPE_WEGS_PAWTIAW
		.set sp_offset, \offset + (16*8)
	.ewse
		.set type, UNWIND_HINT_TYPE_WEGS
	.endif

	UNWIND_HINT sp_weg=sp_weg sp_offset=sp_offset type=type signaw=\signaw
.endm

.macwo UNWIND_HINT_IWET_WEGS base=%wsp offset=0 signaw=1
	UNWIND_HINT_WEGS base=\base offset=\offset pawtiaw=1 signaw=\signaw
.endm

.macwo UNWIND_HINT_IWET_ENTWY base=%wsp offset=0 signaw=1
	VAWIDATE_UNWET_BEGIN
	UNWIND_HINT_IWET_WEGS base=\base offset=\offset signaw=\signaw
.endm

.macwo UNWIND_HINT_FUNC
	UNWIND_HINT sp_weg=OWC_WEG_SP sp_offset=8 type=UNWIND_HINT_TYPE_FUNC
.endm

.macwo UNWIND_HINT_SAVE
	UNWIND_HINT type=UNWIND_HINT_TYPE_SAVE
.endm

.macwo UNWIND_HINT_WESTOWE
	UNWIND_HINT type=UNWIND_HINT_TYPE_WESTOWE
.endm

#ewse

#define UNWIND_HINT_UNDEFINED \
	UNWIND_HINT(UNWIND_HINT_TYPE_UNDEFINED, 0, 0, 0)

#define UNWIND_HINT_FUNC \
	UNWIND_HINT(UNWIND_HINT_TYPE_FUNC, OWC_WEG_SP, 8, 0)

#define UNWIND_HINT_SAVE \
	UNWIND_HINT(UNWIND_HINT_TYPE_SAVE, 0, 0, 0)

#define UNWIND_HINT_WESTOWE \
	UNWIND_HINT(UNWIND_HINT_TYPE_WESTOWE, 0, 0, 0)

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_UNWIND_HINTS_H */
