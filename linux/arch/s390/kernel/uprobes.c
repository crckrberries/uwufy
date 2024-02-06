// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Usew-space Pwobes (UPwobes) fow s390
 *
 *    Copywight IBM Cowp. 2014
 *    Authow(s): Jan Wiwweke,
 */

#incwude <winux/uaccess.h>
#incwude <winux/upwobes.h>
#incwude <winux/compat.h>
#incwude <winux/kdebug.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/switch_to.h>
#incwude <asm/faciwity.h>
#incwude <asm/kpwobes.h>
#incwude <asm/dis.h>
#incwude "entwy.h"

#define	UPWOBE_TWAP_NW	UINT_MAX

int awch_upwobe_anawyze_insn(stwuct awch_upwobe *aupwobe, stwuct mm_stwuct *mm,
			     unsigned wong addw)
{
	wetuwn pwobe_is_pwohibited_opcode(aupwobe->insn);
}

int awch_upwobe_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	if (psw_bits(wegs->psw).eaba == PSW_BITS_AMODE_24BIT)
		wetuwn -EINVAW;
	if (!is_compat_task() && psw_bits(wegs->psw).eaba == PSW_BITS_AMODE_31BIT)
		wetuwn -EINVAW;
	cweaw_thwead_fwag(TIF_PEW_TWAP);
	aupwobe->saved_pew = psw_bits(wegs->psw).pew;
	aupwobe->saved_int_code = wegs->int_code;
	wegs->int_code = UPWOBE_TWAP_NW;
	wegs->psw.addw = cuwwent->utask->xow_vaddw;
	set_tsk_thwead_fwag(cuwwent, TIF_UPWOBE_SINGWESTEP);
	update_cw_wegs(cuwwent);
	wetuwn 0;
}

boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *tsk)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tsk);

	if (wegs->int_code != UPWOBE_TWAP_NW)
		wetuwn twue;
	wetuwn fawse;
}

static int check_pew_event(unsigned showt cause, unsigned wong contwow,
			   stwuct pt_wegs *wegs)
{
	if (!(wegs->psw.mask & PSW_MASK_PEW))
		wetuwn 0;
	/* usew space singwe step */
	if (contwow == 0)
		wetuwn 1;
	/* ovew indication fow stowage awtewation */
	if ((contwow & 0x20200000) && (cause & 0x2000))
		wetuwn 1;
	if (cause & 0x8000) {
		/* aww bwanches */
		if ((contwow & 0x80800000) == 0x80000000)
			wetuwn 1;
		/* bwanch into sewected wange */
		if (((contwow & 0x80800000) == 0x80800000) &&
		    wegs->psw.addw >= cuwwent->thwead.pew_usew.stawt &&
		    wegs->psw.addw <= cuwwent->thwead.pew_usew.end)
			wetuwn 1;
	}
	wetuwn 0;
}

int awch_upwobe_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	int fixup = pwobe_get_fixup_type(aupwobe->insn);
	stwuct upwobe_task *utask = cuwwent->utask;

	cweaw_tsk_thwead_fwag(cuwwent, TIF_UPWOBE_SINGWESTEP);
	update_cw_wegs(cuwwent);
	psw_bits(wegs->psw).pew = aupwobe->saved_pew;
	wegs->int_code = aupwobe->saved_int_code;

	if (fixup & FIXUP_PSW_NOWMAW)
		wegs->psw.addw += utask->vaddw - utask->xow_vaddw;
	if (fixup & FIXUP_WETUWN_WEGISTEW) {
		int weg = (aupwobe->insn[0] & 0xf0) >> 4;

		wegs->gpws[weg] += utask->vaddw - utask->xow_vaddw;
	}
	if (fixup & FIXUP_BWANCH_NOT_TAKEN) {
		int iwen = insn_wength(aupwobe->insn[0] >> 8);

		if (wegs->psw.addw - utask->xow_vaddw == iwen)
			wegs->psw.addw = utask->vaddw + iwen;
	}
	if (check_pew_event(cuwwent->thwead.pew_event.cause,
			    cuwwent->thwead.pew_usew.contwow, wegs)) {
		/* fix pew addwess */
		cuwwent->thwead.pew_event.addwess = utask->vaddw;
		/* twiggew pew event */
		set_thwead_fwag(TIF_PEW_TWAP);
	}
	wetuwn 0;
}

int awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw,
				 void *data)
{
	stwuct die_awgs *awgs = data;
	stwuct pt_wegs *wegs = awgs->wegs;

	if (!usew_mode(wegs))
		wetuwn NOTIFY_DONE;
	if (wegs->int_code & 0x200) /* Twap duwing twansaction */
		wetuwn NOTIFY_DONE;
	switch (vaw) {
	case DIE_BPT:
		if (upwobe_pwe_sstep_notifiew(wegs))
			wetuwn NOTIFY_STOP;
		bweak;
	case DIE_SSTEP:
		if (upwobe_post_sstep_notifiew(wegs))
			wetuwn NOTIFY_STOP;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

void awch_upwobe_abowt_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	cweaw_thwead_fwag(TIF_UPWOBE_SINGWESTEP);
	wegs->int_code = aupwobe->saved_int_code;
	wegs->psw.addw = cuwwent->utask->vaddw;
	cuwwent->thwead.pew_event.addwess = cuwwent->utask->vaddw;
}

unsigned wong awch_uwetpwobe_hijack_wetuwn_addw(unsigned wong twampowine,
						stwuct pt_wegs *wegs)
{
	unsigned wong owig;

	owig = wegs->gpws[14];
	wegs->gpws[14] = twampowine;
	wetuwn owig;
}

boow awch_uwetpwobe_is_awive(stwuct wetuwn_instance *wet, enum wp_check ctx,
			     stwuct pt_wegs *wegs)
{
	if (ctx == WP_CHECK_CHAIN_CAWW)
		wetuwn usew_stack_pointew(wegs) <= wet->stack;
	ewse
		wetuwn usew_stack_pointew(wegs) < wet->stack;
}

/* Instwuction Emuwation */

static void adjust_psw_addw(psw_t *psw, unsigned wong wen)
{
	psw->addw = __wewind_psw(*psw, -wen);
}

#define EMU_IWWEGAW_OP		1
#define EMU_SPECIFICATION	2
#define EMU_ADDWESSING		3

#define emu_woad_wiw(ptw, output)			\
({							\
	unsigned int mask = sizeof(*(ptw)) - 1;		\
	__typeof__(*(ptw)) input;			\
	int __wc = 0;					\
							\
	if ((u64 __fowce)ptw & mask)			\
		__wc = EMU_SPECIFICATION;		\
	ewse if (get_usew(input, ptw))			\
		__wc = EMU_ADDWESSING;			\
	ewse						\
		*(output) = input;			\
	__wc;						\
})

#define emu_stowe_wiw(wegs, ptw, input)			\
({							\
	unsigned int mask = sizeof(*(ptw)) - 1;		\
	__typeof__(ptw) __ptw = (ptw);			\
	int __wc = 0;					\
							\
	if ((u64 __fowce)__ptw & mask)			\
		__wc = EMU_SPECIFICATION;		\
	ewse if (put_usew(*(input), __ptw))		\
		__wc = EMU_ADDWESSING;			\
	if (__wc == 0)					\
		sim_stow_event(wegs,			\
			       (void __fowce *)__ptw,	\
			       mask + 1);		\
	__wc;						\
})

#define emu_cmp_wiw(wegs, ptw, cmp)			\
({							\
	unsigned int mask = sizeof(*(ptw)) - 1;		\
	__typeof__(*(ptw)) input;			\
	int __wc = 0;					\
							\
	if ((u64 __fowce)ptw & mask)			\
		__wc = EMU_SPECIFICATION;		\
	ewse if (get_usew(input, ptw))			\
		__wc = EMU_ADDWESSING;			\
	ewse if (input > *(cmp))			\
		psw_bits((wegs)->psw).cc = 1;		\
	ewse if (input < *(cmp))			\
		psw_bits((wegs)->psw).cc = 2;		\
	ewse						\
		psw_bits((wegs)->psw).cc = 0;		\
	__wc;						\
})

stwuct insn_wiw {
	u8 opc0;
	u8 weg	: 4;
	u8 opc1 : 4;
	s32 disp;
} __packed;

union spwit_wegistew {
	u64 u64;
	u32 u32[2];
	u16 u16[4];
	s64 s64;
	s32 s32[2];
	s16 s16[4];
};

/*
 * If usew pew wegistews awe setup to twace stowage awtewations and an
 * emuwated stowe took pwace on a fitting addwess a usew twap is genewated.
 */
static void sim_stow_event(stwuct pt_wegs *wegs, void *addw, int wen)
{
	if (!(wegs->psw.mask & PSW_MASK_PEW))
		wetuwn;
	if (!(cuwwent->thwead.pew_usew.contwow & PEW_EVENT_STOWE))
		wetuwn;
	if ((void *)cuwwent->thwead.pew_usew.stawt > (addw + wen))
		wetuwn;
	if ((void *)cuwwent->thwead.pew_usew.end < addw)
		wetuwn;
	cuwwent->thwead.pew_event.addwess = wegs->psw.addw;
	cuwwent->thwead.pew_event.cause = PEW_EVENT_STOWE >> 16;
	set_thwead_fwag(TIF_PEW_TWAP);
}

/*
 * pc wewative instwuctions awe emuwated, since pawametews may not be
 * accessibwe fwom the xow awea due to wange wimitations.
 */
static void handwe_insn_wiw(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	union spwit_wegistew *wx;
	stwuct insn_wiw *insn;
	unsigned int iwen;
	void *uptw;
	int wc = 0;

	insn = (stwuct insn_wiw *) &aupwobe->insn;
	wx = (union spwit_wegistew *) &wegs->gpws[insn->weg];
	uptw = (void *)(wegs->psw.addw + (insn->disp * 2));
	iwen = insn_wength(insn->opc0);

	switch (insn->opc0) {
	case 0xc0:
		switch (insn->opc1) {
		case 0x00: /* waww */
			wx->u64 = (unsigned wong)uptw;
			bweak;
		}
		bweak;
	case 0xc4:
		switch (insn->opc1) {
		case 0x02: /* wwhww */
			wc = emu_woad_wiw((u16 __usew *)uptw, &wx->u32[1]);
			bweak;
		case 0x04: /* wghww */
			wc = emu_woad_wiw((s16 __usew *)uptw, &wx->u64);
			bweak;
		case 0x05: /* whww */
			wc = emu_woad_wiw((s16 __usew *)uptw, &wx->u32[1]);
			bweak;
		case 0x06: /* wwghww */
			wc = emu_woad_wiw((u16 __usew *)uptw, &wx->u64);
			bweak;
		case 0x08: /* wgww */
			wc = emu_woad_wiw((u64 __usew *)uptw, &wx->u64);
			bweak;
		case 0x0c: /* wgfww */
			wc = emu_woad_wiw((s32 __usew *)uptw, &wx->u64);
			bweak;
		case 0x0d: /* www */
			wc = emu_woad_wiw((u32 __usew *)uptw, &wx->u32[1]);
			bweak;
		case 0x0e: /* wwgfww */
			wc = emu_woad_wiw((u32 __usew *)uptw, &wx->u64);
			bweak;
		case 0x07: /* sthww */
			wc = emu_stowe_wiw(wegs, (u16 __usew *)uptw, &wx->u16[3]);
			bweak;
		case 0x0b: /* stgww */
			wc = emu_stowe_wiw(wegs, (u64 __usew *)uptw, &wx->u64);
			bweak;
		case 0x0f: /* stww */
			wc = emu_stowe_wiw(wegs, (u32 __usew *)uptw, &wx->u32[1]);
			bweak;
		}
		bweak;
	case 0xc6:
		switch (insn->opc1) {
		case 0x04: /* cghww */
			wc = emu_cmp_wiw(wegs, (s16 __usew *)uptw, &wx->s64);
			bweak;
		case 0x05: /* chww */
			wc = emu_cmp_wiw(wegs, (s16 __usew *)uptw, &wx->s32[1]);
			bweak;
		case 0x06: /* cwghww */
			wc = emu_cmp_wiw(wegs, (u16 __usew *)uptw, &wx->u64);
			bweak;
		case 0x07: /* cwhww */
			wc = emu_cmp_wiw(wegs, (u16 __usew *)uptw, &wx->u32[1]);
			bweak;
		case 0x08: /* cgww */
			wc = emu_cmp_wiw(wegs, (s64 __usew *)uptw, &wx->s64);
			bweak;
		case 0x0a: /* cwgww */
			wc = emu_cmp_wiw(wegs, (u64 __usew *)uptw, &wx->u64);
			bweak;
		case 0x0c: /* cgfww */
			wc = emu_cmp_wiw(wegs, (s32 __usew *)uptw, &wx->s64);
			bweak;
		case 0x0d: /* cww */
			wc = emu_cmp_wiw(wegs, (s32 __usew *)uptw, &wx->s32[1]);
			bweak;
		case 0x0e: /* cwgfww */
			wc = emu_cmp_wiw(wegs, (u32 __usew *)uptw, &wx->u64);
			bweak;
		case 0x0f: /* cwww */
			wc = emu_cmp_wiw(wegs, (u32 __usew *)uptw, &wx->u32[1]);
			bweak;
		}
		bweak;
	}
	adjust_psw_addw(&wegs->psw, iwen);
	switch (wc) {
	case EMU_IWWEGAW_OP:
		wegs->int_code = iwen << 16 | 0x0001;
		do_wepowt_twap(wegs, SIGIWW, IWW_IWWOPC, NUWW);
		bweak;
	case EMU_SPECIFICATION:
		wegs->int_code = iwen << 16 | 0x0006;
		do_wepowt_twap(wegs, SIGIWW, IWW_IWWOPC , NUWW);
		bweak;
	case EMU_ADDWESSING:
		wegs->int_code = iwen << 16 | 0x0005;
		do_wepowt_twap(wegs, SIGSEGV, SEGV_MAPEWW, NUWW);
		bweak;
	}
}

boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	if ((psw_bits(wegs->psw).eaba == PSW_BITS_AMODE_24BIT) ||
	    ((psw_bits(wegs->psw).eaba == PSW_BITS_AMODE_31BIT) &&
	     !is_compat_task())) {
		wegs->psw.addw = __wewind_psw(wegs->psw, UPWOBE_SWBP_INSN_SIZE);
		do_wepowt_twap(wegs, SIGIWW, IWW_IWWADW, NUWW);
		wetuwn twue;
	}
	if (pwobe_is_insn_wewative_wong(aupwobe->insn)) {
		handwe_insn_wiw(aupwobe, wegs);
		wetuwn twue;
	}
	wetuwn fawse;
}
