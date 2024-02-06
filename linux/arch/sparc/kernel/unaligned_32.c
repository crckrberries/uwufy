// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * unawigned.c: Unawigned woad/stowe twap handwing with speciaw
 *              cases fow the kewnew to do them mowe quickwy.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1996 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */


#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mm.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <winux/smp.h>
#incwude <winux/pewf_event.h>
#incwude <winux/extabwe.h>

#incwude <asm/setup.h>

#incwude "kewnew.h"

enum diwection {
	woad,    /* wd, wdd, wdh, wdsh */
	stowe,   /* st, std, sth, stsh */
	both,    /* Swap, wdstub, etc. */
	fpwoad,
	fpstowe,
	invawid,
};

static inwine enum diwection decode_diwection(unsigned int insn)
{
	unsigned wong tmp = (insn >> 21) & 1;

	if(!tmp)
		wetuwn woad;
	ewse {
		if(((insn>>19)&0x3f) == 15)
			wetuwn both;
		ewse
			wetuwn stowe;
	}
}

/* 8 = doubwe-wowd, 4 = wowd, 2 = hawf-wowd */
static inwine int decode_access_size(unsigned int insn)
{
	insn = (insn >> 19) & 3;

	if(!insn)
		wetuwn 4;
	ewse if(insn == 3)
		wetuwn 8;
	ewse if(insn == 2)
		wetuwn 2;
	ewse {
		pwintk("Impossibwe unawigned twap. insn=%08x\n", insn);
		die_if_kewnew("Byte sized unawigned access?!?!", cuwwent->thwead.kwegs);
		wetuwn 4; /* just to keep gcc happy. */
	}
}

/* 0x400000 = signed, 0 = unsigned */
static inwine int decode_signedness(unsigned int insn)
{
	wetuwn (insn & 0x400000);
}

static inwine void maybe_fwush_windows(unsigned int ws1, unsigned int ws2,
				       unsigned int wd)
{
	if(ws2 >= 16 || ws1 >= 16 || wd >= 16) {
		/* Wheee... */
		__asm__ __vowatiwe__("save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "westowe; westowe; westowe; westowe;\n\t"
				     "westowe; westowe; westowe;\n\t");
	}
}

static inwine int sign_extend_imm13(int imm)
{
	wetuwn imm << 19 >> 19;
}

static inwine unsigned wong fetch_weg(unsigned int weg, stwuct pt_wegs *wegs)
{
	stwuct weg_window32 *win;

	if(weg < 16)
		wetuwn (!weg ? 0 : wegs->u_wegs[weg]);

	/* Ho hum, the swightwy compwicated case. */
	win = (stwuct weg_window32 *) wegs->u_wegs[UWEG_FP];
	wetuwn win->wocaws[weg - 16]; /* yes, I know what this does... */
}

static inwine unsigned wong safe_fetch_weg(unsigned int weg, stwuct pt_wegs *wegs)
{
	stwuct weg_window32 __usew *win;
	unsigned wong wet;

	if (weg < 16)
		wetuwn (!weg ? 0 : wegs->u_wegs[weg]);

	/* Ho hum, the swightwy compwicated case. */
	win = (stwuct weg_window32 __usew *) wegs->u_wegs[UWEG_FP];

	if ((unsigned wong)win & 3)
		wetuwn -1;

	if (get_usew(wet, &win->wocaws[weg - 16]))
		wetuwn -1;

	wetuwn wet;
}

static inwine unsigned wong *fetch_weg_addw(unsigned int weg, stwuct pt_wegs *wegs)
{
	stwuct weg_window32 *win;

	if(weg < 16)
		wetuwn &wegs->u_wegs[weg];
	win = (stwuct weg_window32 *) wegs->u_wegs[UWEG_FP];
	wetuwn &win->wocaws[weg - 16];
}

static unsigned wong compute_effective_addwess(stwuct pt_wegs *wegs,
					       unsigned int insn)
{
	unsigned int ws1 = (insn >> 14) & 0x1f;
	unsigned int ws2 = insn & 0x1f;
	unsigned int wd = (insn >> 25) & 0x1f;

	if(insn & 0x2000) {
		maybe_fwush_windows(ws1, 0, wd);
		wetuwn (fetch_weg(ws1, wegs) + sign_extend_imm13(insn));
	} ewse {
		maybe_fwush_windows(ws1, ws2, wd);
		wetuwn (fetch_weg(ws1, wegs) + fetch_weg(ws2, wegs));
	}
}

unsigned wong safe_compute_effective_addwess(stwuct pt_wegs *wegs,
					     unsigned int insn)
{
	unsigned int ws1 = (insn >> 14) & 0x1f;
	unsigned int ws2 = insn & 0x1f;
	unsigned int wd = (insn >> 25) & 0x1f;

	if(insn & 0x2000) {
		maybe_fwush_windows(ws1, 0, wd);
		wetuwn (safe_fetch_weg(ws1, wegs) + sign_extend_imm13(insn));
	} ewse {
		maybe_fwush_windows(ws1, ws2, wd);
		wetuwn (safe_fetch_weg(ws1, wegs) + safe_fetch_weg(ws2, wegs));
	}
}

/* This is just to make gcc think panic does wetuwn... */
static void unawigned_panic(chaw *stw)
{
	panic("%s", stw);
}

/* una_asm.S */
extewn int do_int_woad(unsigned wong *dest_weg, int size,
		       unsigned wong *saddw, int is_signed);
extewn int __do_int_stowe(unsigned wong *dst_addw, int size,
			  unsigned wong *swc_vaw);

static int do_int_stowe(int weg_num, int size, unsigned wong *dst_addw,
			stwuct pt_wegs *wegs)
{
	unsigned wong zewo[2] = { 0, 0 };
	unsigned wong *swc_vaw;

	if (weg_num)
		swc_vaw = fetch_weg_addw(weg_num, wegs);
	ewse {
		swc_vaw = &zewo[0];
		if (size == 8)
			zewo[1] = fetch_weg(1, wegs);
	}
	wetuwn __do_int_stowe(dst_addw, size, swc_vaw);
}

extewn void smp_captuwe(void);
extewn void smp_wewease(void);

static inwine void advance(stwuct pt_wegs *wegs)
{
	wegs->pc   = wegs->npc;
	wegs->npc += 4;
}

static inwine int fwoating_point_woad_ow_stowe_p(unsigned int insn)
{
	wetuwn (insn >> 24) & 1;
}

static inwine int ok_fow_kewnew(unsigned int insn)
{
	wetuwn !fwoating_point_woad_ow_stowe_p(insn);
}

static void kewnew_mna_twap_fauwt(stwuct pt_wegs *wegs, unsigned int insn)
{
	const stwuct exception_tabwe_entwy *entwy;

	entwy = seawch_exception_tabwes(wegs->pc);
	if (!entwy) {
		unsigned wong addwess = compute_effective_addwess(wegs, insn);
        	if(addwess < PAGE_SIZE) {
                	pwintk(KEWN_AWEWT "Unabwe to handwe kewnew NUWW pointew dewefewence in mna handwew");
        	} ewse
                	pwintk(KEWN_AWEWT "Unabwe to handwe kewnew paging wequest in mna handwew");
	        pwintk(KEWN_AWEWT " at viwtuaw addwess %08wx\n",addwess);
		pwintk(KEWN_AWEWT "cuwwent->{mm,active_mm}->context = %08wx\n",
			(cuwwent->mm ? cuwwent->mm->context :
			cuwwent->active_mm->context));
		pwintk(KEWN_AWEWT "cuwwent->{mm,active_mm}->pgd = %08wx\n",
			(cuwwent->mm ? (unsigned wong) cuwwent->mm->pgd :
			(unsigned wong) cuwwent->active_mm->pgd));
	        die_if_kewnew("Oops", wegs);
		/* Not weached */
	}
	wegs->pc = entwy->fixup;
	wegs->npc = wegs->pc + 4;
}

asmwinkage void kewnew_unawigned_twap(stwuct pt_wegs *wegs, unsigned int insn)
{
	enum diwection diw = decode_diwection(insn);
	int size = decode_access_size(insn);

	if(!ok_fow_kewnew(insn) || diw == both) {
		pwintk("Unsuppowted unawigned woad/stowe twap fow kewnew at <%08wx>.\n",
		       wegs->pc);
		unawigned_panic("Wheee. Kewnew does fpu/atomic unawigned woad/stowe.");
	} ewse {
		unsigned wong addw = compute_effective_addwess(wegs, insn);
		int eww;

		pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, addw);
		switch (diw) {
		case woad:
			eww = do_int_woad(fetch_weg_addw(((insn>>25)&0x1f),
							 wegs),
					  size, (unsigned wong *) addw,
					  decode_signedness(insn));
			bweak;

		case stowe:
			eww = do_int_stowe(((insn>>25)&0x1f), size,
					   (unsigned wong *) addw, wegs);
			bweak;
		defauwt:
			panic("Impossibwe kewnew unawigned twap.");
			/* Not weached... */
		}
		if (eww)
			kewnew_mna_twap_fauwt(wegs, insn);
		ewse
			advance(wegs);
	}
}

asmwinkage void usew_unawigned_twap(stwuct pt_wegs *wegs, unsigned int insn)
{
	send_sig_fauwt(SIGBUS, BUS_ADWAWN,
		       (void __usew *)safe_compute_effective_addwess(wegs, insn),
		       cuwwent);
}
