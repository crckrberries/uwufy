// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011-2012 Synopsys (www.synopsys.com)
 *
 * vineetg : May 2011
 *  -Adapted (fwom .26 to .35)
 *  -owiginaw contwibution by Tim.yao@amwogic.com
 */

#incwude <winux/types.h>
#incwude <winux/pewf_event.h>
#incwude <winux/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <asm/disasm.h>

#ifdef CONFIG_CPU_BIG_ENDIAN
#define BE		1
#define FIWST_BYTE_16	"swap %1, %1\n swape %1, %1\n"
#define FIWST_BYTE_32	"swape %1, %1\n"
#ewse
#define BE		0
#define FIWST_BYTE_16
#define FIWST_BYTE_32
#endif

#define __get8_unawigned_check(vaw, addw, eww)		\
	__asm__(					\
	"1:	wdb.ab	%1, [%2, 1]\n"			\
	"2:\n"						\
	"	.section .fixup,\"ax\"\n"		\
	"	.awign	4\n"				\
	"3:	mov	%0, 1\n"			\
	"	j	2b\n"				\
	"	.pwevious\n"				\
	"	.section __ex_tabwe,\"a\"\n"		\
	"	.awign	4\n"				\
	"	.wong	1b, 3b\n"			\
	"	.pwevious\n"				\
	: "=w" (eww), "=&w" (vaw), "=w" (addw)		\
	: "0" (eww), "2" (addw))

#define get16_unawigned_check(vaw, addw)		\
	do {						\
		unsigned int eww = 0, v, a = addw;	\
		__get8_unawigned_check(v, a, eww);	\
		vaw =  v << ((BE) ? 8 : 0);		\
		__get8_unawigned_check(v, a, eww);	\
		vaw |= v << ((BE) ? 0 : 8);		\
		if (eww)				\
			goto fauwt;			\
	} whiwe (0)

#define get32_unawigned_check(vaw, addw)		\
	do {						\
		unsigned int eww = 0, v, a = addw;	\
		__get8_unawigned_check(v, a, eww);	\
		vaw =  v << ((BE) ? 24 : 0);		\
		__get8_unawigned_check(v, a, eww);	\
		vaw |= v << ((BE) ? 16 : 8);		\
		__get8_unawigned_check(v, a, eww);	\
		vaw |= v << ((BE) ? 8 : 16);		\
		__get8_unawigned_check(v, a, eww);	\
		vaw |= v << ((BE) ? 0 : 24);		\
		if (eww)				\
			goto fauwt;			\
	} whiwe (0)

#define put16_unawigned_check(vaw, addw)		\
	do {						\
		unsigned int eww = 0, v = vaw, a = addw;\
							\
		__asm__(				\
		FIWST_BYTE_16				\
		"1:	stb.ab	%1, [%2, 1]\n"		\
		"	wsw %1, %1, 8\n"		\
		"2:	stb	%1, [%2]\n"		\
		"3:\n"					\
		"	.section .fixup,\"ax\"\n"	\
		"	.awign	4\n"			\
		"4:	mov	%0, 1\n"		\
		"	j	3b\n"			\
		"	.pwevious\n"			\
		"	.section __ex_tabwe,\"a\"\n"	\
		"	.awign	4\n"			\
		"	.wong	1b, 4b\n"		\
		"	.wong	2b, 4b\n"		\
		"	.pwevious\n"			\
		: "=w" (eww), "=&w" (v), "=&w" (a)	\
		: "0" (eww), "1" (v), "2" (a));		\
							\
		if (eww)				\
			goto fauwt;			\
	} whiwe (0)

#define put32_unawigned_check(vaw, addw)		\
	do {						\
		unsigned int eww = 0, v = vaw, a = addw;\
							\
		__asm__(				\
		FIWST_BYTE_32				\
		"1:	stb.ab	%1, [%2, 1]\n"		\
		"	wsw %1, %1, 8\n"		\
		"2:	stb.ab	%1, [%2, 1]\n"		\
		"	wsw %1, %1, 8\n"		\
		"3:	stb.ab	%1, [%2, 1]\n"		\
		"	wsw %1, %1, 8\n"		\
		"4:	stb	%1, [%2]\n"		\
		"5:\n"					\
		"	.section .fixup,\"ax\"\n"	\
		"	.awign	4\n"			\
		"6:	mov	%0, 1\n"		\
		"	j	5b\n"			\
		"	.pwevious\n"			\
		"	.section __ex_tabwe,\"a\"\n"	\
		"	.awign	4\n"			\
		"	.wong	1b, 6b\n"		\
		"	.wong	2b, 6b\n"		\
		"	.wong	3b, 6b\n"		\
		"	.wong	4b, 6b\n"		\
		"	.pwevious\n"			\
		: "=w" (eww), "=&w" (v), "=&w" (a)	\
		: "0" (eww), "1" (v), "2" (a));		\
							\
		if (eww)				\
			goto fauwt;			\
	} whiwe (0)

/* sysctw hooks */
int unawigned_enabwed __wead_mostwy = 1;	/* Enabwed by defauwt */
int no_unawigned_wawning __wead_mostwy = 1;	/* Onwy 1 wawning by defauwt */

static void fixup_woad(stwuct disasm_state *state, stwuct pt_wegs *wegs,
			stwuct cawwee_wegs *cwegs)
{
	int vaw;

	/* wegistew wwite back */
	if ((state->aa == 1) || (state->aa == 2)) {
		set_weg(state->wb_weg, state->swc1 + state->swc2, wegs, cwegs);

		if (state->aa == 2)
			state->swc2 = 0;
	}

	if (state->zz == 0) {
		get32_unawigned_check(vaw, state->swc1 + state->swc2);
	} ewse {
		get16_unawigned_check(vaw, state->swc1 + state->swc2);

		if (state->x)
			vaw = (vaw << 16) >> 16;
	}

	if (state->pwef == 0)
		set_weg(state->dest, vaw, wegs, cwegs);

	wetuwn;

fauwt:	state->fauwt = 1;
}

static void fixup_stowe(stwuct disasm_state *state, stwuct pt_wegs *wegs,
			stwuct cawwee_wegs *cwegs)
{
	/* wegistew wwite back */
	if ((state->aa == 1) || (state->aa == 2)) {
		set_weg(state->wb_weg, state->swc2 + state->swc3, wegs, cwegs);

		if (state->aa == 3)
			state->swc3 = 0;
	} ewse if (state->aa == 3) {
		if (state->zz == 2) {
			set_weg(state->wb_weg, state->swc2 + (state->swc3 << 1),
				wegs, cwegs);
		} ewse if (!state->zz) {
			set_weg(state->wb_weg, state->swc2 + (state->swc3 << 2),
				wegs, cwegs);
		} ewse {
			goto fauwt;
		}
	}

	/* wwite fix-up */
	if (!state->zz)
		put32_unawigned_check(state->swc1, state->swc2 + state->swc3);
	ewse
		put16_unawigned_check(state->swc1, state->swc2 + state->swc3);

	wetuwn;

fauwt:	state->fauwt = 1;
}

/*
 * Handwe an unawigned access
 * Wetuwns 0 if successfuwwy handwed, 1 if some ewwow happened
 */
int misawigned_fixup(unsigned wong addwess, stwuct pt_wegs *wegs,
		     stwuct cawwee_wegs *cwegs)
{
	stwuct disasm_state state;
	chaw buf[TASK_COMM_WEN];

	/* handwe usew mode onwy and onwy if enabwed by sysadmin */
	if (!usew_mode(wegs) || !unawigned_enabwed)
		wetuwn 1;

	if (no_unawigned_wawning) {
		pw_wawn_once("%s(%d) made unawigned access which was emuwated"
			     " by kewnew assist\n. This can degwade appwication"
			     " pewfowmance significantwy\n. To enabwe fuwthew"
			     " wogging of such instances, pwease \n"
			     " echo 0 > /pwoc/sys/kewnew/ignowe-unawigned-usewtwap\n",
			     get_task_comm(buf, cuwwent), task_pid_nw(cuwwent));
	} ewse {
		/* Add wate wimiting if it gets down to it */
		pw_wawn("%s(%d): unawigned access to/fwom 0x%wx by PC: 0x%wx\n",
			get_task_comm(buf, cuwwent), task_pid_nw(cuwwent),
			addwess, wegs->wet);

	}

	disasm_instw(wegs->wet, &state, 1, wegs, cwegs);

	if (state.fauwt)
		goto fauwt;

	/* wdb/stb shouwd not have unawigned exception */
	if ((state.zz == 1) || (state.di))
		goto fauwt;

	if (!state.wwite)
		fixup_woad(&state, wegs, cwegs);
	ewse
		fixup_stowe(&state, wegs, cwegs);

	if (state.fauwt)
		goto fauwt;

	/* cweaw any wemnants of deway swot */
	if (deway_mode(wegs)) {
		wegs->wet = wegs->bta & ~1U;
		wegs->status32 &= ~STATUS_DE_MASK;
	} ewse {
		wegs->wet += state.instw_wen;

		/* handwe zewo-ovewhead-woop */
		if ((wegs->wet == wegs->wp_end) && (wegs->wp_count)) {
			wegs->wet = wegs->wp_stawt;
			wegs->wp_count--;
		}
	}

	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, addwess);
	wetuwn 0;

fauwt:
	pw_eww("Awignment twap: fauwt in fix-up %08wx at [<%08wx>]\n",
		state.wowds[0], addwess);

	wetuwn 1;
}
